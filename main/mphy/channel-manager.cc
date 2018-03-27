/* -*-	Mode:C++ -*- */
/*
 * Copyright (c) 2007 Regents of the SIGNET lab, University of Padova.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Padova (SIGNET lab) nor the 
 *    names of its contributors may be used to endorse or promote products 
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/**
 * @file   channel-manager.cc
 * @author Baldo Nicola
 * @date   Mon Dec  3 16:38:09 2007
 * 
 * @brief  
 * 
 * 
 */



#include"channel-manager.h"
#include<assert.h>
#include<iostream>



ChannelManager::ChannelManager()
{
  bind("startFreq_", &startFreq);
  bind("endFreq_", &endFreq);
}

ChannelManager::~ChannelManager()
{
}


static class ChannelManagerClass : public TclClass {
public:
  ChannelManagerClass() : TclClass("ChannelManager") {}
  TclObject* create(int, const char*const*) { return (new ChannelManager);  }
} class_ChannelManager;




void ChannelManager::addChannel(MSpectralMask* sm)
{
  chlist.push_back(sm);
  reallocateChannels();
}



void ChannelManager::reallocateChannels()
{
  int numchs = chlist.size();
  double totbw = endFreq - startFreq; 
  assert(totbw>0);
  assert(numchs>0);
  double chbw = totbw / numchs;

  std::list<MSpectralMask*>::iterator iter = chlist.begin();

  // carrier frequency 
  double fc = startFreq + chbw/2;

  int chid = 0;

  while (iter != chlist.end())
    {
      MSpectralMask* sm = *iter;
      sm->setFreq(fc);
      sm->setBandwidth(chbw);
      fc += chbw;
      iter++;      
    }
}

int ChannelManager::command(int argc, const char*const* argv)
{ 
  Tcl& tcl = Tcl::instance();

  if(argc == 2)
    {
      if(strcasecmp(argv[1], "print")==0)
	{
	  printChannels();
	  return TCL_OK;
	}
    }
  
  if(argc == 3)
    {
      if(strcasecmp(argv[1], "addChannel")==0)
	{	 
	  MSpectralMask* msm = dynamic_cast<MSpectralMask*>(TclObject::lookup(argv[2]));
	  if (!msm)
	    return TCL_ERROR;
	  addChannel(msm);
	  return TCL_OK;
	}
    }

  return TclObject::command(argc, argv); 
}


void ChannelManager::printChannels()
{
  int chid = 0;
  std::list<MSpectralMask*>::iterator iter = chlist.begin() ;
  while (iter != chlist.end())
    {
      chid++;
      std::cout << " Channel " << chid
		<< ":  freq " <<  (*iter)->getFreq()
		<< "   bw "   <<  (*iter)->getBandwidth()
		<< std::endl;
      iter++;      
    }
}
