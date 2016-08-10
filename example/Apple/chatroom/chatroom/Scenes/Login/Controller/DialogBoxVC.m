/*******************************************************************************\
** chatroom:DialogBoxVC.m
** Created by CZ(cz.devnet@gmail.com) on 16/8/10
**
**  Copyright © 2016年 projm. All rights reserved.
\*******************************************************************************/


#import "DialogBoxVC.h"

@interface DialogBoxVC ()
@property (nonatomic, strong) DialogView *dialogView;
@property (nonatomic, strong) NSArray *msgs;
@property (nonatomic, strong) UITextView *inputView;
@end

@implementation DialogBoxVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    _dialogView = [[DialogView alloc] initWithFrame: self.view.frame];
    _dialogView.backgroundColor = [UIColor grayColor];
    _dialogView.contentSize = CGSizeMake(self.view.frame.size.width, self.view.frame.size.height *2);
    
    _inputView = [[UITextView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height-50, self.view.frame.size.width, 50)];
    
    [self.view addSubview:_dialogView];
    
    [self.view addSubview:_inputView];
    [_dialogView addMessage:@"cz" msg:@"nimei!"];
}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
