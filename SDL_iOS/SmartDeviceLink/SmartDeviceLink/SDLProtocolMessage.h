//  SDLProtocolMessage.h
//  SmartDeviceLink
//  Copyright (c) 2013 Ford Motor Company

#import <Foundation/Foundation.h>
#import <SmartDeviceLink/SDLProtocolFrameHeader.h>

typedef enum SDLMessageType {
	SDLMessageType_UNDEFINED = 0x01,
	SDLMessageType_BULK = 0x02,
	SDLMessageType_RPC = 0x03
} SDLMessageType;

@interface SDLProtocolMessage : NSObject {
    Byte _version;
	SDLSessionType _sessionType;
	SDLMessageType _messageType;
	Byte _sessionID;
    Byte _rpcType;
    UInt32 _functionID;
    UInt32 _correlationID;
    UInt32 _jsonSize;
	
	NSData* _data;
	NSData* _bulkData;
}

@property(assign) Byte _version;
@property(assign) SDLSessionType _sessionType;
@property(assign) SDLMessageType _messageType;
@property(assign) Byte _sessionID;
@property(assign) Byte _rpcType;
@property(assign) UInt32 _functionID;
@property(assign) UInt32 _correlationID;
@property(assign) UInt32 _jsonSize;

@property(retain) NSData* _data;
@property(retain) NSData* _bulkData;

@end