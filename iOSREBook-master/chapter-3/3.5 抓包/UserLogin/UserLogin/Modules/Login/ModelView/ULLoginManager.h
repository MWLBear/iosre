//
//  ULLoginManager.h
//  UserLogin
//
//  Created by monkey on 2017/7/22.
//  Copyright © 2017年 Coder. All rights reserved.
//

#import <Foundation/Foundation.h>

#define URL_BASE @"http://192.168.204.22:8000"

#define SOCKET_IP @"192.168.204.22"
#define SOCKET_PORT 7777

@interface ULLoginManager : NSObject

+ (instancetype)sharedManager;

-(void)loginWithUserName:(NSString*) username passWord:(NSString*) password successBlock:(void(^)(void)) successBlock failedBlock:(void(^)(void)) failedBlock;

-(void)getLoginWithUserName:(NSString *)username passWord:(NSString *)password successBlock:(void (^)(void))successBlock failedBlock:(void (^)(void))failedBlock;
    
-(void)postLoginWithUserName:(NSString *)username passWord:(NSString *)password successBlock:(void (^)(void))successBlock failedBlock:(void (^)(void))failedBlock;

@end
