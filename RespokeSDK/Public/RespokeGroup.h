//
//  RespokeGroup.h
//  Respoke SDK
//
//  Copyright 2015, Digium, Inc.
//  All rights reserved.
//
//  This source code is licensed under The MIT License found in the
//  LICENSE file in the root directory of this source tree.
//
//  For all details and documentation:  https://www.respoke.io
//

#import <Foundation/Foundation.h>


@class RespokeConnection;
@class RespokeEndpoint;
@protocol RespokeGroupDelegate;


/**
 *  A group, representing a collection of connections and the method by which to communicate with them.
 */
@interface RespokeGroup : NSObject


/**
 *  The delegate that should receive notifications from the RespokeGroupDelegate protocol
 */
@property (weak) id <RespokeGroupDelegate> delegate;


/**
 *  Get an array containing the members of the group.
 *
 *  @param successHandler A block called when the action is successful, passing the array of members as RespokeConnection objects
 *  @param errorHandler   A block called when an error occurs, passing a string describing the error
 */
- (void)getMembersWithSuccessHandler:(void (^)(NSArray*))successHandler errorHandler:(void (^)(NSString*))errorHandler;


/**
 *  Leave this group
 *
 *  @param successHandler A block called when the action is successful
 *  @param errorHandler   A block called when an error occurs, passing a string describing the error
 */
- (void)leaveWithSuccessHandler:(void (^)(void))successHandler errorHandler:(void (^)(NSString*))errorHandler;


/**
 *  Return true if the logged-in user is a member of this group and false if not.
 *
 *  @return The membership status
 */
- (BOOL)isJoined;


/**
 *  Get the ID of this group
 *
 *  @return The ID
 */
- (NSString*)getGroupID;


/**
 *  Send a message to the entire group.
 *
 *  @param message        The message to send
 *  @param successHandler A block called when the action is successful
 *  @param errorHandler   A block called when an error occurs, passing a string describing the error
 */
- (void)sendMessage:(NSString*)message successHandler:(void (^)(void))successHandler errorHandler:(void (^)(NSString*))errorHandler;


@end


/**
 *  A delegate protocol to notify the receiver of events occurring with the group
 */
@protocol RespokeGroupDelegate <NSObject>


/**
 *  Receive a notification that an connection has joined this group.
 *
 *  @param connection The RespokeConnection that joined the group
 *  @param sender     The RespokeGroup that the connection has joined
 */
- (void)onJoin:(RespokeConnection*)connection sender:(RespokeGroup*)sender;


/**
 *  Receive a notification that an connection has left this group.
 *
 *  @param connection The RespokeConnection that left the group
 *  @param sender     The RespokeGroup that the connection has left
 */
- (void)onLeave:(RespokeConnection*)connection sender:(RespokeGroup*)sender;


/**
 *  Receive a notification that a group message has been received
 *
 *  @param message      The body of the message
 *  @param endpoint     The endpoint that sent the message
 *  @param sender       The group that received the message
 *  @param timestamp    The message timestamp
 */
- (void)onGroupMessage:(NSString*)message fromEndpoint:(RespokeEndpoint*)endpoint sender:(RespokeGroup*)sender timestamp:(NSDate*)timestamp;


@end
