//
//  RespokeEndpoint.h
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

#import <UIKit/UIKit.h>


@class RespokeCall;
@class RespokeDirectConnection;
@protocol RespokeEndpointDelegate;
@protocol RespokeCallDelegate;


/**
 *  Represents remote Endpoints. Endpoints are users of this application that are not the one logged into this
 *  instance of the application. An Endpoint could be logged in from multiple other instances of this app, each of
 *  which is represented by a Connection. The client can interact with endpoints by calling them or
 *  sending them messages. An endpoint can be a person using an app from a browser or a script using the APIs on
 *  a server.
 */
@interface RespokeEndpoint : NSObject


/**
 *  The ID of this endpoint
 */
@property (readonly) NSString *endpointID;


/**
 *  The connections associated with this endpoint
 */
@property (readonly) NSArray *connections;


/**
 *  A direct connection to this endpoint. This can be used to send direct messages.
 */
@property (readonly) RespokeDirectConnection *directConnection;


/**
 *  The delegate that should receive notifications from the RespokeEndpointDelegate protocol
 */
@property (weak) id <RespokeEndpointDelegate> delegate;


/**
 *  Send a message to the endpoint through the infrastructure.
 *
 *  @param message        The message to send
 *  @param push           A flag indicating if a push notification should be sent for this message
 *  @param successHandler A block called when the message is sent successfully
 *  @param errorHandler   A block called when an error occurred, passing a description of the error
 */
- (void)sendMessage:(NSString*)message push:(BOOL)push successHandler:(void (^)(void))successHandler errorHandler:(void (^)(NSString*))errorHandler;


/**
 *  Create a new call with audio and video.
 *
 *  @param delegate      The delegate to receive notifications about the new call
 *  @param newRemoteView A UIView on which to project the remote video
 *  @param newLocalView  A UIView on which to project the local video
 *
 *  @return A reference to the new RespokeCall object representing this call
 */
- (RespokeCall*)startVideoCallWithDelegate:(id <RespokeCallDelegate>)delegate remoteVideoView:(UIView*)newRemoteView localVideoView:(UIView*)newLocalView;


/**
 *  Create a new audio-only call.
 *
 *  @param delegate The delegate to receive notifications about the new call
 *
 *  @return A reference to the new RespokeCall object representing this call
 */
- (RespokeCall*)startAudioCallWithDelegate:(id <RespokeCallDelegate>)delegate;


/**
 *  Register with the infrastructure to receive presence update notification messages for this endpoint
 *
 *  @param successHandler A block called when the operation is successful
 *  @param errorHandler   A block called when an error occurred, passing a description of the error
 */
- (void)registerPresenceWithSuccessHandler:(void (^)())successHandler errorHandler:(void (^)(NSString*))errorHandler;


/**
 *  Get the current presence of this client
 *
 *  @return The current presence value
 */
- (NSObject*)getPresence;


/**
 *  Create a new DirectConnection.  This method creates a new Call as well, attaching this DirectConnection to
 *  it for the purposes of creating a peer-to-peer link for sending data such as messages to the other endpoint.
 *  Information sent through a DirectConnection is not handled by the cloud infrastructure.  
 *
 *  @return The DirectConnection which can be used to send data and messages directly to the other endpoint.
 */
- (RespokeDirectConnection*)startDirectConnection;


@end


/**
 *  A delegate protocol to notify the receiver of events occurring with the endpoint
 */
@protocol RespokeEndpointDelegate <NSObject>


/**
 *  Handle messages sent to the logged-in user from this one Endpoint.
 *
 *  @param message   The message
 *  @param sender    The remote endpoint that sent the message
 *  @param timestamp The message timestamp
 */
- (void)onMessage:(NSString*)message sender:(RespokeEndpoint*)sender timestamp:(NSDate*)timestamp;


/**
 *  A notification that the presence for an endpoint has changed
 *
 *  @param presence The new presence
 *  @param sender   The endpoint
 */
- (void)onPresence:(NSObject*)presence sender:(RespokeEndpoint*)sender;


@end
