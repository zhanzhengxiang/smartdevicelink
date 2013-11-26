//  SDLProtocolMessage.m
//  SmartDeviceLink
//  Copyright (c) 2013 Ford Motor Company

#import <SmartDeviceLink/SDLProtocolMessage.h>

@implementation SDLProtocolMessage

@synthesize _version;
@synthesize _sessionType;
@synthesize _messageType;
@synthesize _sessionID;
@synthesize _rpcType;
@synthesize _functionID;
@synthesize _correlationID;
@synthesize _jsonSize;
@synthesize _data;
@synthesize _bulkData;

-(id) init {
	if (self = [super init]) {
        _version = 1;
		_sessionType = SDLSessionType_RPC;
		_messageType = SDLMessageType_UNDEFINED;
		_sessionID = 0;
        _rpcType = 0;
        _functionID = 0;
        _correlationID = 0;
        _jsonSize = 0;
        _data = nil;
        _bulkData = nil;
	}
	return self;
}

-(void) dealloc {
    [_data release];
    [_bulkData release];
    [super dealloc];
}
				
@end
