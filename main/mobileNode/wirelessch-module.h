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

#ifndef _WIRELESSCHMODULE_
#define _WIRELESSCHMODULE_

#include "channel-module.h"

#define SPEED_OF_LIGHT     300000000               // 3 * 10^8 m/s
#define PI		3.1415926535897

class ChSAP;

class WirelessChModule : public ChannelModule
{
	public:
		WirelessChModule();
		virtual ~WirelessChModule();
		//virtual void recv(Packet *p);
		virtual void recv(Packet *p, ChSAP *chsap);
		
		virtual int command(int argc, const char*const* argv);

	protected:
		double getPropDelay(Position *source, Position* dest);
		int* getInfluencedNodes(Position *p, double radius,  int *numInfluencedNodes);		// virtual ?
		void sortChSAPList();		// sort list by position of the node attached
		void sendUpPhy(Packet *p,ChSAP *chsap);

	private:
		bool sorted_;
		
		double CSThresh_;		// carrier sense threshold (W)
		double freq_;			// frequency
		double L_;				// system loss factor
		double lambda_;		// wavelenght (m)


};

#endif
