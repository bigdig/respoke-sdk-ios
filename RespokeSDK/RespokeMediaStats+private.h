//
//  RespokeMediaStats+Private.h
//  RespokeSDK
//
//  Created by Rob Crabtree on 1/15/15.
//  Copyright (c) 2015 Digium, Inc. All rights reserved.
//

#import "RespokeMediaStats.h"
#import "RTCTypes.h"


@interface RespokeConnectionStats (private)
-(instancetype)initWithChannelId:(NSString*)channelId foundOutgoingNetworkPaths:(BOOL)foundOutgoingNetworkPaths foundIncomingNetworkPaths:(BOOL)foundIncomingNetworkPaths transport:(NSString*)transport localMediaPath:(NSString*)localMediaPath remoteMediaPath:(NSString*)remoteMediaPath remoteHost:(NSString*)remoteHost localHost:(NSString*)localHost roundTripTime:(NSString*)roundTripTime;
@end


@interface RespokeLocalAudioStats (private)
-(instancetype)initWithAudioInputLevel:(NSString*)audioInputLevel codec:(NSString*)codec totalBytesSent:(NSInteger)totalBytesSent periodBytesSent:(NSInteger)periodBytesSent totalPacketsSent:(NSInteger)totalPacketsSent periodPacketsSent:(NSInteger)periodPacketsSent transportId:(NSString*)transportId;
@end


@interface RespokeLocalVideoStats (private)
-(instancetype)initWithCodec:(NSString*)codec totalBytesSent:(NSInteger)totalBytesSent periodBytesSent:(NSInteger)periodBytesSent totalPacketsSent:(NSInteger)totalPacketsSent periodPacketsSent:(NSInteger)periodPacketsSent transportId:(NSString*)transportId;

@end


@interface RespokeRemoteAudioStats (private)
-(instancetype)initWithAudioOutputLevel:(NSString*)audioOutputLevel totalBytesReceived:(NSInteger)totalBytesReceived periodBytesReceived:(NSInteger)periodBytesReceived packetsLost:(NSInteger)packetsLost totalPacketsReceived:(NSInteger)totalPacketsReceived periodPacketsReceived:(NSInteger)periodPacketsReceived transportId:(NSString*)transportId;
@end


@interface RespokeRemoteVideoStats (private)
-(instancetype)initWithTotalBytesReceived:(NSInteger)totalBytesReceived periodBytesReceived:(NSInteger)periodBytesReceived packetsLost:(NSInteger)packetsLost totalPacketsReceived:(NSInteger)totalPacketsReceived periodPacketsReceived:(NSInteger)periodPacketsReceived transportId:(NSString*)transportId;
@end


@interface RespokeMediaStats (private)
- (instancetype)initWithData:(NSArray*)stats iceGatheringState:(RTCICEGatheringState)gatheringState iceConnectionState:(RTCICEConnectionState)connectionState timestamp:(NSDate*)timestamp oldMediaStats:(RespokeMediaStats*)oldMediaStats;
@end