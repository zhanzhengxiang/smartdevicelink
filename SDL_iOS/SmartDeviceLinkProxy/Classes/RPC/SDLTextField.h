//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCMessage.h"

#import "SDLTextFieldName.h"
#import "SDLCharacterSet.h"

@interface SDLTextField : SDLRPCStruct {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLTextFieldName* name;
@property(assign) SDLCharacterSet* characterSet;
@property(assign) NSNumber* width;
@property(assign) NSNumber* rows;

@end
