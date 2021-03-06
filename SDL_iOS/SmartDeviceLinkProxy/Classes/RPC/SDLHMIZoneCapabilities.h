//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"

@interface SDLHMIZoneCapabilities : SDLEnum {}

+(SDLHMIZoneCapabilities*) valueOf:(NSString*) value;
+(NSMutableArray*) values;

+(SDLHMIZoneCapabilities*) FRONT;
+(SDLHMIZoneCapabilities*) BACK;

@end
