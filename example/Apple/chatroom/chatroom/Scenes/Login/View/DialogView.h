//
//  DialogView.h
//  chatroom
//
//  Created by apollo on 16/8/10.
//  Copyright © 2016年 projm. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DialogView : UIScrollView
- (void) addMessage: (NSString *)name msg:(NSString *)msg;
@end
