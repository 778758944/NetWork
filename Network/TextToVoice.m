//
//  TextToVoice.m
//  Network
//
//  Created by WENTAO XING on 2019/4/12.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#import "TextToVoice.h"

@implementation TextToVoice
-(void) spell: (NSString *) s
{
    AVSpeechUtterance * utterance = [[AVSpeechUtterance alloc] initWithString: s];
    [utterance setVoice:[AVSpeechSynthesisVoice voiceWithLanguage:@"en-GB"]];
    [utterance setRate: 0.3];
    
    AVSpeechSynthesizer * speaker = [[AVSpeechSynthesizer alloc] init];
    [speaker stopSpeakingAtBoundary:(AVSpeechBoundaryImmediate)];
    [speaker speakUtterance:utterance];
    
    
}
@end
