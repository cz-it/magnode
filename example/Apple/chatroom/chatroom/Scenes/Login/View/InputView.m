//
//  InputView.m
//  chatroom
//
//  Created by apollo on 16/8/10.
//  Copyright © 2016年 projm. All rights reserved.
//

#import "InputView.h"

@interface InputView() @property (nonatomic, strong) UITextField *inputTF;
@end

@implementation InputView

- (instancetype)initWithFrame:(CGRect)frame {

    
    self = [super initWithFrame:frame];
    _inputTF = [[UITextField alloc] initWithFrame:CGRectMake(10, 5, frame.size.width-20, frame.size.height-10)];
    _inputTF.layer.cornerRadius = 10.0;
    _inputTF.backgroundColor = [UIColor whiteColor];
    _inputTF.delegate = self;
    _inputTF.returnKeyType = UIReturnKeySend;
    [self addSubview:_inputTF];
    return self;
}



#pragma mark UITextFieldDelegate
- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField {
    NSLog(@"textFieldShouldBeginEditing");
    return YES;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField {
    NSLog(@"textFieldDidBeginEditing");
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    NSLog(@"textFieldShouldReturn");
    return [_inputTF resignFirstResponder];
}

@end
