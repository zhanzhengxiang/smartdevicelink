//
// Copyright (c) 2013, Ford Motor Company
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following
// disclaimer in the documentation and/or other materials provided with the
// distribution.
//
// Neither the name of the Ford Motor Company nor the names of its contributors
// may be used to endorse or promote products derived from this software
// without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef NSSMARTDEVICELINKKRPCV2_GETDTCS_REQUEST_INCLUDE
#define NSSMARTDEVICELINKKRPCV2_GETDTCS_REQUEST_INCLUDE


#include "JSONHandler/SDLRPCMessage.h"


/*
  interface	Ford Sync RAPI
  version	2.0O
  date		2012-11-02
  generated at	Thu Jan 24 06:36:23 2013
  source stamp	Thu Jan 24 06:35:41 2013
  author	RC
*/

namespace NsSmartDeviceLinkRPCV2
{

///  Vehicle module diagnostic trouble code request.

  class GetDTCs_request : public NsSmartDeviceLinkRPC::SDLRPCMessage
  {
  public:
  
    GetDTCs_request(const GetDTCs_request& c);
    GetDTCs_request(void);
    
    virtual ~GetDTCs_request(void);
  
    GetDTCs_request& operator =(const GetDTCs_request&);
  
    bool checkIntegrity(void);

    unsigned int get_ecuName(void) const;
    const bool* get_encrypted(void) const;

    bool set_ecuName(unsigned int ecuName_);
    void reset_encrypted(void);
    bool set_encrypted(bool encrypted_);

  private:
  
    friend class GetDTCs_requestMarshaller;


///  Name of ECU.
      unsigned int ecuName;	//!<  (0,65535)

/**
     If not provided, the default is equal to False"
     Indicates if the DTC data requested should be returned as encrypted through an OnEncodedSYNCPData response.
     If set to true, the data will return instead through OnEncodedSYNCPData and be passed through the proxy to the designated server URL.
*/
      bool* encrypted;
  };

}

#endif
