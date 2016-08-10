/*******************************************************************************\
** chatroom:LoginVC.m
** Created by CZ(cz.devnet@gmail.com) on 8/4/16
**
**  Copyright © 2016 projm. All rights reserved.
\*******************************************************************************/

#include "magnode.h"

#import "LoginVC.h"
#include "chatroom.pb.h"
#include "DialogBoxVC.h"


#include <MBProgressHUD/MBProgressHUD.h>
#include <string>

#define BUF_SIZE 10240

@interface LoginVC () {
    mn_node *node;
}
@property (weak, nonatomic) IBOutlet UITextField *roomNameLbl;
@property (weak, nonatomic) IBOutlet UITextField *nickNameLbl;

@end

@implementation LoginVC

- (void)viewDidLoad {

    [super viewDidLoad];
    // Do any additional setup after loading the view.

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)  connect2server {
    int rst = 0;
    self->node = mn_new();
    if (NULL == self->node) {
        NSLog(@"new magnode error");
        return NO;
    }
    rst = mn_init(self->node);
    if (rst) {
        NSLog(@"mn_init error with %d", rst);
        return NO;
    }
    
    rst = mn_connect(self->node, "tcp://127.0.0.1:8084", 3000);
    if (rst) {
        NSLog(@"mn_connect error with %d", rst);
        return NO;
    }
    return YES;
}

- (BOOL) enterRoom {

    std::string roomName = [[_roomNameLbl text] cStringUsingEncoding:NSUTF8StringEncoding];
    std::string nickName = [[_nickNameLbl text] cStringUsingEncoding:NSUTF8StringEncoding];
    NSLog(@"enter room %s with %s", roomName.c_str(), nickName.c_str());
    
    proto::EnterRoomReq *enterReq  = new proto::EnterRoomReq();
    enterReq->set_roomname(roomName);
    enterReq->set_nickname(nickName);
    
    proto::Message msg;
    msg.set_type(proto::Message_MessageType_ENTER_ROOM_REQ);
    msg.set_allocated_enterroomreq(enterReq);
    
    std::string sbuf  = msg.SerializeAsString();
    mn_send(self->node, sbuf.c_str(), sbuf.length(), 3000);
    char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);
    size_t len = BUF_SIZE;
    mn_recv(self->node, buf, &len, 30000);
    
    msg.Clear();
    msg.ParseFromArray(buf, (int)len);
    NSLog(@"enter result %d", msg.type());
    [self sendAndRecv];
    return YES;
}


- (IBAction)onEnter:(id)sender {
    
    
    
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    hud.labelText = NSLocalizedString(@"Connecting to server...", @"HUD preparing title");
    hud.minSize = CGSizeMake(150.f, 100.f);
    
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), ^{
        //[self connect2server];
        hud.labelText = NSLocalizedString(@"Enter room...", @"HUD preparing title");
        //[self enterRoom];
        
        [self.parentViewController performSegueWithIdentifier:@"pushDialogBox" sender:self];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [hud hide:YES];
        });
    });
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    
    if ([[segue identifier] isEqualToString:@"pushDialogBox"]) {
        NSLog(@"pushDialogBox");
    }
}

- (void) sendAndRecv {
    static int seq = 0;
    std::string payload = "hello";
    proto::UpMessage *upMsg  = new proto::UpMessage();
    upMsg->set_message(payload);
    upMsg->set_length(payload.length());
    
    proto::Message msg;
    msg.set_type(proto::Message_MessageType_UP_MESSAGE);
    msg.set_allocated_upmessage(upMsg);
    
    std::string sbuf  = msg.SerializeAsString();
    mn_send(self->node, sbuf.c_str(), sbuf.length(), 3000);
    
    sleep(1);
    
    char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);
    size_t len = BUF_SIZE;
    mn_recv(self->node, buf, &len, 3000);
    
    msg.Clear();
    msg.ParseFromArray(buf, len);
    NSLog(@"msg type", msg.type());
    if (msg.type() != proto::Message_MessageType_DOWN_MESSAGE) {
        NSLog(@"not download message");
    }
    NSLog(@"get message %s", msg.downmessage().message().c_str());

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
