//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLSubscribeButton.h"
#import "SDLNames.h"

@implementation SDLSubscribeButton

-(id) init {
    if (self = [super initWithName:NAMES_SubscribeButton]) {}
    return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
    if (self = [super initWithDictionary:dict]) {}
    return self;
}

-(void) setButtonName:(SDLButtonName*) buttonName {
    if (buttonName != nil) {
        [parameters setObject:buttonName forKey:NAMES_buttonName];
    } else {
        [parameters removeObjectForKey:NAMES_buttonName];
    }
}

-(SDLButtonName*) buttonName {
    NSObject* obj = [parameters objectForKey:NAMES_buttonName];
    if ([obj isKindOfClass:SDLButtonName.class]) {
        return (SDLButtonName*)obj;
    } else { 
        return [SDLButtonName valueOf:(NSString*)obj];
    }
}

@end
