//
//  ApiTransaction.m
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
#import "APITransaction.h"
#import "RespokeVersion.h"

#define HTTP_TIMEOUT 10.0f


@implementation APITransaction

+ (NSString*)getSDKHeader
{
    const NSString *osName = [UIDevice currentDevice].systemName;
    const NSString *osVersion = [UIDevice currentDevice].systemVersion;
    const NSString *sdkVersion = getSDKVersion();
    return [NSString stringWithFormat:@"Respoke-iOS/%@ (%@ %@)", sdkVersion, osName, osVersion];
}

- (instancetype)initWithBaseUrl:(NSString*)newBaseURL
{
    if (self = [super init])
    {
        self.baseURL = newBaseURL;
        params = @"";
        httpMethod = @"POST";
    }

    return self;
}


- (void)goWithSuccessHandler:(void (^)())successHandler errorHandler:(void (^)(NSString*))errorHandler
{
    self.successHandler = successHandler;
    self.errorHandler = errorHandler;

    NSString *contentType;
    NSData *data;
    if (jsonParams)
    {
        contentType = @"application/json";
        data = jsonParams;
    }
    else
    {
        contentType = @"application/x-www-form-urlencoded";
        data = [params dataUsingEncoding:NSUTF8StringEncoding];
    }

    if  ([data length] > BODY_SIZE_LIMIT)
    {
        self.errorHandler(@"Invalid message size");
    }
    else
    {
        NSString *sdkHeader = [APITransaction getSDKHeader];
        NSURL *theURL = [NSURL URLWithString:self.baseURL];
        NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:theURL cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData timeoutInterval:HTTP_TIMEOUT];
        [request setHTTPMethod:httpMethod];
        [request setValue:@"application/xml" forHTTPHeaderField:@"Accept"];
        [request setValue:contentType forHTTPHeaderField:@"Content-Type"];
        [request setValue:sdkHeader forHTTPHeaderField:@"Respoke-SDK"];
        [request setValue:[NSString stringWithFormat:@"%lu", (unsigned long)[data length]] forHTTPHeaderField:@"Content-length"];
        [request setHTTPBody:data];
        connection = [NSURLConnection connectionWithRequest:request delegate:self];
    }
}


- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    NSInteger httpStatus = ((NSHTTPURLResponse*)response).statusCode;

    if (401 == httpStatus)
    {
        self.errorMessage = @"API authentication error";
    }
    else if (httpStatus == 429)
    {
        self.errorMessage = @"API rate limit was exceeded";
    }
    else if (httpStatus == 503)
    {
        self.errorMessage = @"Server is down for maintenance";
    }
    else if (httpStatus >= 400)
    {
        self.errorMessage = [NSString stringWithFormat:@"Failed with server error %ld!", (long)httpStatus];
    }
    else
    {
        self.success = YES;
    }
}


- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    if (!self.receivedData)
    {
        self.receivedData = [NSMutableData dataWithData:data];
    }
    else
    {
        [self.receivedData appendData:data];
    }
}


- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    [self transactionComplete];
}


- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    if ((error.code == NSURLErrorUserCancelledAuthentication) || (error.code == NSURLErrorUserAuthenticationRequired))
    {
        self.errorMessage = @"API authentication error";
    }
    else if (error.code == NSURLErrorBadServerResponse)
    {
        self.errorMessage = @"Failed with status code 500";
    }
    else
    {
        self.errorMessage = @"Unable to reach server";
    }

    self.success = NO;

    [self transactionComplete];
}


- (void)transactionComplete
{
    // overridden by child classes

    if (self.success)
    {
        NSError *error;
        self.jsonResult = [NSJSONSerialization JSONObjectWithData:self.receivedData options:0 error:&error];

        if (error)
        {
            NSLog(@"------%@: error deserializing response: %@", [self class], [error localizedDescription]);
            self.errorMessage = @"Unexpected response from server";
            self.success = NO;
        }
    }
}


- (void)cancel
{
    abort = YES;
    [connection cancel];
}


@end
