/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

#import <ReactABI19_0_0/ABI19_0_0RCTDefines.h>

@protocol ABI19_0_0RCTReloadListener
- (void)didReceiveReloadCommand;
@end

/** Registers a weakly-held observer of the Command+R reload key command. */
ABI19_0_0RCT_EXTERN void ABI19_0_0RCTRegisterReloadCommandListener(id<ABI19_0_0RCTReloadListener> listener);
