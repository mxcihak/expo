// Copyright 2016-present 650 Industries. All rights reserved.

#import "ABI19_0_0EXRemoteNotificationRequester.h"
#import "ABI19_0_0EXUnversioned.h"

#import <ReactABI19_0_0/ABI19_0_0RCTUtils.h>

@interface ABI19_0_0EXRemoteNotificationRequester ()

@property (nonatomic, strong) ABI19_0_0RCTPromiseResolveBlock resolve;
@property (nonatomic, strong) ABI19_0_0RCTPromiseRejectBlock reject;
@property (nonatomic, weak) id<ABI19_0_0EXPermissionRequesterDelegate> delegate;

@end

@implementation ABI19_0_0EXRemoteNotificationRequester

+ (NSDictionary *)permissions
{
  ABI19_0_0EXPermissionStatus status = (ABI19_0_0RCTSharedApplication().isRegisteredForRemoteNotifications) ?
    ABI19_0_0EXPermissionStatusGranted :
    ABI19_0_0EXPermissionStatusUndetermined;
  return @{
           @"status": [ABI19_0_0EXPermissions permissionStringForStatus:status],
           @"expires": ABI19_0_0EXPermissionExpiresNever,
           };
}

- (void)requestPermissionsWithResolver:(ABI19_0_0RCTPromiseResolveBlock)resolve rejecter:(ABI19_0_0RCTPromiseRejectBlock)reject
{
  _resolve = resolve;
  _reject = reject;
  
  if (ABI19_0_0RCTSharedApplication().isRegisteredForRemoteNotifications) {
    // resolve immediately if already registered
    [self _consumeResolverWithCurrentPermissions];
  } else {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(_handleDidRegisterForRemoteNotifications:)
                                                 name:@"EXAppDidRegisterForRemoteNotificationsNotification"
                                               object:nil];
    UIUserNotificationType types = UIUserNotificationTypeBadge | UIUserNotificationTypeSound | UIUserNotificationTypeAlert;
    [ABI19_0_0RCTSharedApplication() registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:types categories:nil]];
    [ABI19_0_0RCTSharedApplication() registerForRemoteNotifications];
  }
}

- (void)setDelegate:(id<ABI19_0_0EXPermissionRequesterDelegate>)delegate
{
  _delegate = delegate;
}

- (void)_handleDidRegisterForRemoteNotifications:(__unused NSNotification *)notif
{
  [[NSNotificationCenter defaultCenter] removeObserver:self];
  [self _consumeResolverWithCurrentPermissions];
}

- (void)_consumeResolverWithCurrentPermissions
{
  if (_resolve) {
    _resolve([[self class] permissions]);
    _resolve = nil;
    _reject = nil;
  }
  if (_delegate) {
    [_delegate permissionRequesterDidFinish:self];
  }
}

@end
