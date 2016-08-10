//
//  DialogView.m
//  chatroom
//
//  Created by apollo on 16/8/10.
//  Copyright © 2016年 projm. All rights reserved.
//

#import "DialogView.h"
#import "MessageView.h"

@implementation DialogView


- (void) addMessage: (NSString *)name msg:(NSString *)msg {
    MessageView *msgView = [[MessageView alloc] initWithFrame:CGRectMake(0, 0, 500, 80)];
    [self addSubview: msgView];
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
