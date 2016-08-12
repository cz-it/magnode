//
//  DialogView.m
//  chatroom
//
//  Created by apollo on 16/8/10.
//  Copyright © 2016年 projm. All rights reserved.
//

#import "DialogView.h"
#import "MessageView.h"

@interface DialogView() {
    CGFloat msgHeight;
}

@end

@implementation DialogView


- (void) addMessage: (NSString *)name msg:(NSString *)msg {
    self.directionalLockEnabled = NO;
}

- (void) layoutMessage {
    if (msgHeight < self.frame.size.height) {
        self.contentSize = CGSizeMake(self.contentSize.width, self.frame.size.height);
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
