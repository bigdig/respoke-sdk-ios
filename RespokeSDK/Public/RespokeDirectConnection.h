//
//  RespokeDirectConnection.h
//  RespokeSDKBuilder
//
//  Created by Jason Adams on 10/23/14.
//  Copyright (c) 2014 Digium, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@protocol RespokeDirectConnectionDelegate;
@class RespokeCall;


@interface RespokeDirectConnection : NSObject


/**
 *  The delegate that should receive notifications from the RespokeDirectConnection protocol
 */
@property (weak) id <RespokeDirectConnectionDelegate> delegate;


/**
 *  Accept the direct connection and start the process of obtaining media. 
 */
- (void)accept;


/**
 *  Indicate whether a datachannel is being setup or is in progress.
 */
- (BOOL)isActive;


/**
 *  Get the call object associated with this direct connection
 */
- (RespokeCall*)getCall;


/**
 *  Send a message to the remote client through the direct connection.
 */
- (void)sendMessage:(NSString*)message successHandler:(void (^)(void))successHandler errorHandler:(void (^)(NSString*))errorHandler;


@end


@protocol RespokeDirectConnectionDelegate <NSObject>


/**
 *  The direct connection setup has begun. This does NOT mean it's ready to send messages yet. Listen to
 *  onOpen for that notification.
 */
- (void)onStart:(RespokeDirectConnection*)sender;


/**
 *  Called when the direct connection is opened.
 */
- (void)onOpen:(RespokeDirectConnection*)sender;


/**
 *  Called when the direct connection is closed.
 */
- (void)onClose:(RespokeDirectConnection*)sender;


/**
 *  Called when a message is received over the direct connection.
 */
 - (void)onMessage:(id)message sender:(RespokeDirectConnection*)sender;


@end
