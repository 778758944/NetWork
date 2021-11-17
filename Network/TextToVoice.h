//
//  TextToVoice.h
//  Network
//
//  Created by WENTAO XING on 2019/4/12.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TextToVoice : NSObject
-(void) spell: (NSString *) s;
@end

NS_ASSUME_NONNULL_END
