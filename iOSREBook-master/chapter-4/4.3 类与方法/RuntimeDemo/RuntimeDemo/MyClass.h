//
//  MyClass.h
//  ClassDemo
//
//  Created by AloneMonkey on 2017/8/25.
//  Copyright © 2017年 AloneMonkey. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyClass : NSObject

@property NSString * myProperty;

- (void)myMethod;

@end
//xcrun -sdk iphoneos clang -rewrite-objc -F UIKit -fobjc-arc -arch arm64 ClassAndMethod.m
