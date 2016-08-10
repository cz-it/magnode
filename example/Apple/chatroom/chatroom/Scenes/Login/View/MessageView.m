//
//  MessageView.m
//  chatroom
//
//  Created by apollo on 16/8/10.
//  Copyright © 2016年 projm. All rights reserved.
//

#import "MessageView.h"

@interface MessageView()
@property (nonatomic, strong) UILabel *nameLbl;
@property (nonatomic, strong) UITextView *msgTV;
@end

@implementation MessageView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    self.backgroundColor = [UIColor redColor];
    return self;
}

- (void) setName:(NSString *)name {
    _nameLbl.text = name;
}

- (void) setMessage:(NSString *)message {
    _msgTV.text = message;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
