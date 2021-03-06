//
//  RespokeGroupTests.m
//  RespokeSDK
//
//  Copyright 2015, Digium, Inc.
//  All rights reserved.
//
//  This source code is licensed under The MIT License found in the
//  LICENSE file in the root directory of this source tree.
//
//  For all details and documentation:  https://www.respoke.io
//

#import "RespokeTestCase.h"
#import "RespokeGroup+private.h"
#import "Respoke+private.h"


@interface RespokeGroupTests : RespokeTestCase {
    BOOL callbackSucceeded;
}

@end


@implementation RespokeGroupTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}


- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}


- (void)testUnconnectedGroupBehaviour
{
    RespokeClient *client = [[Respoke sharedInstance] createClient];
    XCTAssertNotNil(client);

    NSString *testGroupID = @"myGroupID";
    RespokeGroup *group = [[RespokeGroup alloc] initWithGroupID:testGroupID signalingChannel:nil client:client];

    XCTAssertNotNil(group, @"Group should not be nil");
    XCTAssertTrue(![group isJoined], @"Should indicate group is not joined");

    callbackSucceeded = NO;
    [group sendMessage:@"A message" push:NO successHandler:^{
        XCTAssertTrue(NO, @"Should not send a message to a group that is not joined");
    } errorHandler:^(NSString *errorMessage){
        XCTAssertTrue([errorMessage isEqualToString:@"Not a member of this group anymore."]);
        callbackSucceeded = YES;
    }];

    XCTAssertTrue(callbackSucceeded, @"Should have called the error handler");

    callbackSucceeded = NO;
    [group leaveWithSuccessHandler:^{
        XCTAssertTrue(NO, @"Leaving an unjoined group should fail");
    } errorHandler:^(NSString *errorMessage){
        XCTAssertTrue([errorMessage isEqualToString:@"Not a member of this group anymore."]);
        callbackSucceeded = YES;
    }];

    XCTAssertTrue(callbackSucceeded, @"Should have called the error handler");

    callbackSucceeded = NO;
    [group getMembersWithSuccessHandler:^(NSArray *members){
        XCTAssertTrue(NO, @"Getting members of an unjoined group should fail");
    } errorHandler:^(NSString *errorMessage){
        XCTAssertTrue([errorMessage isEqualToString:@"Not a member of this group anymore."]);
        callbackSucceeded = YES;
    }];

    XCTAssertTrue(callbackSucceeded, @"Should have called the error handler");
}


@end
