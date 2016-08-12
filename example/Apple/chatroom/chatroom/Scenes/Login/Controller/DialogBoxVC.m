/*******************************************************************************\
** chatroom:DialogBoxVC.m
** Created by CZ(cz.devnet@gmail.com) on 16/8/10
**
**  Copyright © 2016年 projm. All rights reserved.
\*******************************************************************************/


#import "DialogBoxVC.h"
#import "InputView.h"

@interface DialogBoxVC (){
    CGFloat keyboardHeight;
    NSTimeInterval keyboardHeightTime;
}

@property (nonatomic, strong) DialogView *dialogView;
@property (nonatomic, strong) NSArray *msgs;
@property (nonatomic, strong) InputView *inputView;
@end

@implementation DialogBoxVC

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    
    // Do any additional setup after loading the view.
    _dialogView = [[DialogView alloc] initWithFrame: self.view.frame];
    _dialogView.backgroundColor = [UIColor lightGrayColor];
    //_dialogView.contentSize = CGSizeMake(self.view.frame.size.width, self.view.frame.size.height *2);
    _dialogView.maxHeight = self.view.frame.size.height;
    _dialogView.delegate = self;
    [_dialogView layoutMessage];

    _inputView = [[InputView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height-50, self.view.frame.size.width, 50)];
    [self.view addSubview:_dialogView];
    
    [self.view addSubview:_inputView];
    [_dialogView addMessage:@"cz" msg:@"nimei!"];
}

- (void) keyboardWillShow: (NSNotification *) noti {
    NSDictionary *info = noti.userInfo;
    NSValue *heightValue = info[UIKeyboardFrameBeginUserInfoKey];
    keyboardHeight = [heightValue CGRectValue].size.height +25;
    
    keyboardHeightTime = 0;
    NSNumber *timeDur = info[UIKeyboardAnimationDurationUserInfoKey];
    
    [timeDur getValue:&keyboardHeightTime];
    [UIView animateWithDuration:keyboardHeightTime animations:^{
        [_inputView setFrame:CGRectMake(_inputView.frame.origin.x, _inputView.frame.origin.y-keyboardHeight, _inputView.frame.size.width, _inputView.frame.size.height)];
        [_dialogView setFrame:CGRectMake(_dialogView.frame.origin.x, self.view.frame.origin.y, _dialogView.frame.size.width, _dialogView.frame.size.height-keyboardHeight)];
        [_dialogView layoutMessage];
    }];
}

- (void) keyboardWillHide: (NSNotification *) sender {
    [UIView animateWithDuration:keyboardHeightTime animations:^{
        [_inputView setFrame:CGRectMake(_inputView.frame.origin.x, self.view.frame.size.height-50, _inputView.frame.size.width, _inputView.frame.size.height)];
        [_dialogView setFrame:CGRectMake(_dialogView.frame.origin.x, self.view.frame.origin.y, _dialogView.frame.size.width, self.view.frame.size.height)];
        [_dialogView layoutMessage];
    }];
}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark UIScrollViewDelegate

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    [[[UIApplication sharedApplication] keyWindow] endEditing:YES];
    [_dialogView layoutMessage];
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
