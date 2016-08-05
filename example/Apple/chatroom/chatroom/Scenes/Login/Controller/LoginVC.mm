/*******************************************************************************\
** chatroom:LoginVC.m
** Created by CZ(cz.devnet@gmail.com) on 8/4/16
**
**  Copyright © 2016 projm. All rights reserved.
\*******************************************************************************/

#include "magnode.h"

#import "LoginVC.h"
#include "chatroom.pb.h"
#include <string>



@interface LoginVC () {
    mn_node *node;
}
@property (weak, nonatomic) IBOutlet UITextField *roomNameLbl;
@property (weak, nonatomic) IBOutlet UITextField *nickNameLbl;

@end

@implementation LoginVC

- (void)viewDidLoad {
    int rst = 0;
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self->node = mn_new();
    if (NULL == self->node) {
        NSLog(@"new magnode error");
        return ;
    }
    rst = mn_init(self->node);
    if (rst) {
        NSLog(@"mn_init error with %d", rst);
        return ;
    }

    rst = mn_connect(self->node, "tcp://127.0.0.1:8084", 3000);
    if (rst) {
        NSLog(@"mn_connect error with %d", rst);
        return ;
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)onEnter:(id)sender {
    std::string roomName = [[_roomNameLbl text] cStringUsingEncoding:NSUTF8StringEncoding];
    std::string nickName = [[_nickNameLbl text] cStringUsingEncoding:NSUTF8StringEncoding];
    NSLog(@"enter room %s with %s", roomName.c_str(), nickName.c_str());
    
    proto::EnterRoomReq *enterReq  = new proto::EnterRoomReq();
    enterReq->set_roomname(roomName);
    enterReq->set_nickname(nickName);
    
    proto::Message msg;
    msg.set_type(proto::Message_MessageType_ENTER_ROOM_REQ);
    msg.set_allocated_enterroomreq(enterReq);
    
    std::string buf  = msg.SerializeAsString();
    mn_send(self->node, buf.c_str(), buf.length(), 3000);
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
