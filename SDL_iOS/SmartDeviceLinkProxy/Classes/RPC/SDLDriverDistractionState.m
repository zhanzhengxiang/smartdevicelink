//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLDriverDistractionState.h"

SDLDriverDistractionState* SDLDriverDistractionState_DD_ON = nil;
SDLDriverDistractionState* SDLDriverDistractionState_DD_OFF = nil;

NSMutableArray* SDLDriverDistractionState_values = nil; 

@implementation SDLDriverDistractionState

+(SDLDriverDistractionState*) valueOf:(NSString*) value {
	for (SDLDriverDistractionState* item in SDLDriverDistractionState.values) {
		if ([item.value isEqualToString:value]) { 
			return item; 
		} 
	} 
	return nil; 
}

+(NSMutableArray *) values {
	if (SDLDriverDistractionState_values == nil) {                               
		SDLDriverDistractionState_values = [[NSMutableArray alloc] initWithObjects: 
							 SDLDriverDistractionState.DD_ON,          
							 SDLDriverDistractionState.DD_OFF, 
							 nil];                                                   
		
	} 
	return SDLDriverDistractionState_values; 
}

+(SDLDriverDistractionState*) DD_ON {                                                                        	
	if (SDLDriverDistractionState_DD_ON == nil) {     
		SDLDriverDistractionState_DD_ON = [[SDLDriverDistractionState alloc] initWithValue:@"DD_ON"];
	} 
	return SDLDriverDistractionState_DD_ON;                                                     
	
}

+(SDLDriverDistractionState*) DD_OFF {                                                                        	
	if (SDLDriverDistractionState_DD_OFF == nil) {   
		SDLDriverDistractionState_DD_OFF = [[SDLDriverDistractionState alloc] initWithValue:@"DD_OFF"];     
	} 
	return SDLDriverDistractionState_DD_OFF;      
}

@end


