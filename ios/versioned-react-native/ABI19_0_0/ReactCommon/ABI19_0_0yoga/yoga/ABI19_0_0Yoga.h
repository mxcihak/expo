/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

// Not defined in MSVC++
#ifndef NAN
static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
#define NAN (*(const float *) __nan)
#endif

#define ABI19_0_0YGUndefined NAN

#include "ABI19_0_0YGEnums.h"
#include "ABI19_0_0YGMacros.h"

ABI19_0_0YG_EXTERN_C_BEGIN

typedef struct ABI19_0_0YGSize {
  float width;
  float height;
} ABI19_0_0YGSize;

typedef struct ABI19_0_0YGValue {
  float value;
  ABI19_0_0YGUnit unit;
} ABI19_0_0YGValue;

static const ABI19_0_0YGValue ABI19_0_0YGValueUndefined = {ABI19_0_0YGUndefined, ABI19_0_0YGUnitUndefined};
static const ABI19_0_0YGValue ABI19_0_0YGValueAuto = {ABI19_0_0YGUndefined, ABI19_0_0YGUnitAuto};

typedef struct ABI19_0_0YGConfig *ABI19_0_0YGConfigRef;
typedef struct ABI19_0_0YGNode *ABI19_0_0YGNodeRef;
typedef ABI19_0_0YGSize (*ABI19_0_0YGMeasureFunc)(ABI19_0_0YGNodeRef node,
                                float width,
                                ABI19_0_0YGMeasureMode widthMode,
                                float height,
                                ABI19_0_0YGMeasureMode heightMode);
typedef float (*ABI19_0_0YGBaselineFunc)(ABI19_0_0YGNodeRef node, const float width, const float height);
typedef void (*ABI19_0_0YGPrintFunc)(ABI19_0_0YGNodeRef node);
typedef int (*ABI19_0_0YGLogger)(const ABI19_0_0YGConfigRef config,
                        const ABI19_0_0YGNodeRef node,
                        ABI19_0_0YGLogLevel level,
                        const char *format,
                        va_list args);

typedef void *(*ABI19_0_0YGMalloc)(size_t size);
typedef void *(*ABI19_0_0YGCalloc)(size_t count, size_t size);
typedef void *(*ABI19_0_0YGRealloc)(void *ptr, size_t size);
typedef void (*ABI19_0_0YGFree)(void *ptr);

// ABI19_0_0YGNode
WIN_EXPORT ABI19_0_0YGNodeRef ABI19_0_0YGNodeNew(void);
WIN_EXPORT ABI19_0_0YGNodeRef ABI19_0_0YGNodeNewWithConfig(const ABI19_0_0YGConfigRef config);
WIN_EXPORT void ABI19_0_0YGNodeFree(const ABI19_0_0YGNodeRef node);
WIN_EXPORT void ABI19_0_0YGNodeFreeRecursive(const ABI19_0_0YGNodeRef node);
WIN_EXPORT void ABI19_0_0YGNodeReset(const ABI19_0_0YGNodeRef node);
WIN_EXPORT int32_t ABI19_0_0YGNodeGetInstanceCount(void);

WIN_EXPORT void ABI19_0_0YGNodeInsertChild(const ABI19_0_0YGNodeRef node,
                                  const ABI19_0_0YGNodeRef child,
                                  const uint32_t index);
WIN_EXPORT void ABI19_0_0YGNodeRemoveChild(const ABI19_0_0YGNodeRef node, const ABI19_0_0YGNodeRef child);
WIN_EXPORT ABI19_0_0YGNodeRef ABI19_0_0YGNodeGetChild(const ABI19_0_0YGNodeRef node, const uint32_t index);
WIN_EXPORT ABI19_0_0YGNodeRef ABI19_0_0YGNodeGetParent(const ABI19_0_0YGNodeRef node);
WIN_EXPORT uint32_t ABI19_0_0YGNodeGetChildCount(const ABI19_0_0YGNodeRef node);

WIN_EXPORT void ABI19_0_0YGNodeCalculateLayout(const ABI19_0_0YGNodeRef node,
                                      const float availableWidth,
                                      const float availableHeight,
                                      const ABI19_0_0YGDirection parentDirection);

// Mark a node as dirty. Only valid for nodes with a custom measure function
// set.
// ABI19_0_0YG knows when to mark all other nodes as dirty but because nodes with
// measure functions
// depends on information not known to ABI19_0_0YG they must perform this dirty
// marking manually.
WIN_EXPORT void ABI19_0_0YGNodeMarkDirty(const ABI19_0_0YGNodeRef node);
WIN_EXPORT bool ABI19_0_0YGNodeIsDirty(const ABI19_0_0YGNodeRef node);

WIN_EXPORT void ABI19_0_0YGNodePrint(const ABI19_0_0YGNodeRef node, const ABI19_0_0YGPrintOptions options);

WIN_EXPORT bool ABI19_0_0YGFloatIsUndefined(const float value);

WIN_EXPORT bool ABI19_0_0YGNodeCanUseCachedMeasurement(const ABI19_0_0YGMeasureMode widthMode,
                                              const float width,
                                              const ABI19_0_0YGMeasureMode heightMode,
                                              const float height,
                                              const ABI19_0_0YGMeasureMode lastWidthMode,
                                              const float lastWidth,
                                              const ABI19_0_0YGMeasureMode lastHeightMode,
                                              const float lastHeight,
                                              const float lastComputedWidth,
                                              const float lastComputedHeight,
                                              const float marginRow,
                                              const float marginColumn,
                                              ABI19_0_0YGConfigRef config);

WIN_EXPORT void ABI19_0_0YGNodeCopyStyle(const ABI19_0_0YGNodeRef dstNode, const ABI19_0_0YGNodeRef srcNode);

#define ABI19_0_0YG_NODE_PROPERTY(type, name, paramName)                          \
  WIN_EXPORT void ABI19_0_0YGNodeSet##name(const ABI19_0_0YGNodeRef node, type paramName); \
  WIN_EXPORT type ABI19_0_0YGNodeGet##name(const ABI19_0_0YGNodeRef node);

#define ABI19_0_0YG_NODE_STYLE_PROPERTY(type, name, paramName)                               \
  WIN_EXPORT void ABI19_0_0YGNodeStyleSet##name(const ABI19_0_0YGNodeRef node, const type paramName); \
  WIN_EXPORT type ABI19_0_0YGNodeStyleGet##name(const ABI19_0_0YGNodeRef node);

#define ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT(type, name, paramName)                                    \
  WIN_EXPORT void ABI19_0_0YGNodeStyleSet##name(const ABI19_0_0YGNodeRef node, const float paramName);          \
  WIN_EXPORT void ABI19_0_0YGNodeStyleSet##name##Percent(const ABI19_0_0YGNodeRef node, const float paramName); \
  WIN_EXPORT type ABI19_0_0YGNodeStyleGet##name(const ABI19_0_0YGNodeRef node);

#define ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT_AUTO(type, name, paramName) \
  ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT(type, name, paramName)            \
  WIN_EXPORT void ABI19_0_0YGNodeStyleSet##name##Auto(const ABI19_0_0YGNodeRef node);

#define ABI19_0_0YG_NODE_STYLE_EDGE_PROPERTY(type, name, paramName)    \
  WIN_EXPORT void ABI19_0_0YGNodeStyleSet##name(const ABI19_0_0YGNodeRef node,  \
                                       const ABI19_0_0YGEdge edge,     \
                                       const type paramName); \
  WIN_EXPORT type ABI19_0_0YGNodeStyleGet##name(const ABI19_0_0YGNodeRef node, const ABI19_0_0YGEdge edge);

#define ABI19_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT(type, name, paramName)         \
  WIN_EXPORT void ABI19_0_0YGNodeStyleSet##name(const ABI19_0_0YGNodeRef node,            \
                                       const ABI19_0_0YGEdge edge,               \
                                       const float paramName);          \
  WIN_EXPORT void ABI19_0_0YGNodeStyleSet##name##Percent(const ABI19_0_0YGNodeRef node,   \
                                                const ABI19_0_0YGEdge edge,      \
                                                const float paramName); \
  WIN_EXPORT WIN_STRUCT(type) ABI19_0_0YGNodeStyleGet##name(const ABI19_0_0YGNodeRef node, const ABI19_0_0YGEdge edge);

#define ABI19_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT_AUTO(type, name) \
  WIN_EXPORT void ABI19_0_0YGNodeStyleSet##name##Auto(const ABI19_0_0YGNodeRef node, const ABI19_0_0YGEdge edge);

#define ABI19_0_0YG_NODE_LAYOUT_PROPERTY(type, name) \
  WIN_EXPORT type ABI19_0_0YGNodeLayoutGet##name(const ABI19_0_0YGNodeRef node);

#define ABI19_0_0YG_NODE_LAYOUT_EDGE_PROPERTY(type, name) \
  WIN_EXPORT type ABI19_0_0YGNodeLayoutGet##name(const ABI19_0_0YGNodeRef node, const ABI19_0_0YGEdge edge);

ABI19_0_0YG_NODE_PROPERTY(void *, Context, context);
ABI19_0_0YG_NODE_PROPERTY(ABI19_0_0YGMeasureFunc, MeasureFunc, measureFunc);
ABI19_0_0YG_NODE_PROPERTY(ABI19_0_0YGBaselineFunc, BaselineFunc, baselineFunc)
ABI19_0_0YG_NODE_PROPERTY(ABI19_0_0YGPrintFunc, PrintFunc, printFunc);
ABI19_0_0YG_NODE_PROPERTY(bool, HasNewLayout, hasNewLayout);
ABI19_0_0YG_NODE_PROPERTY(ABI19_0_0YGNodeType, NodeType, nodeType);

ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGDirection, Direction, direction);
ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGFlexDirection, FlexDirection, flexDirection);
ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGJustify, JustifyContent, justifyContent);
ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGAlign, AlignContent, alignContent);
ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGAlign, AlignItems, alignItems);
ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGAlign, AlignSelf, alignSelf);
ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGPositionType, PositionType, positionType);
ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGWrap, FlexWrap, flexWrap);
ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGOverflow, Overflow, overflow);
ABI19_0_0YG_NODE_STYLE_PROPERTY(ABI19_0_0YGDisplay, Display, display);

ABI19_0_0YG_NODE_STYLE_PROPERTY(float, Flex, flex);
ABI19_0_0YG_NODE_STYLE_PROPERTY(float, FlexGrow, flexGrow);
ABI19_0_0YG_NODE_STYLE_PROPERTY(float, FlexShrink, flexShrink);
ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT_AUTO(ABI19_0_0YGValue, FlexBasis, flexBasis);

ABI19_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT(ABI19_0_0YGValue, Position, position);
ABI19_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT(ABI19_0_0YGValue, Margin, margin);
ABI19_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT_AUTO(ABI19_0_0YGValue, Margin);
ABI19_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT(ABI19_0_0YGValue, Padding, padding);
ABI19_0_0YG_NODE_STYLE_EDGE_PROPERTY(float, Border, border);

ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT_AUTO(ABI19_0_0YGValue, Width, width);
ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT_AUTO(ABI19_0_0YGValue, Height, height);
ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT(ABI19_0_0YGValue, MinWidth, minWidth);
ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT(ABI19_0_0YGValue, MinHeight, minHeight);
ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT(ABI19_0_0YGValue, MaxWidth, maxWidth);
ABI19_0_0YG_NODE_STYLE_PROPERTY_UNIT(ABI19_0_0YGValue, MaxHeight, maxHeight);

// Yoga specific properties, not compatible with flexbox specification
// Aspect ratio control the size of the undefined dimension of a node.
// Aspect ratio is encoded as a floating point value width/height. e.g. A value of 2 leads to a node
// with a width twice the size of its height while a value of 0.5 gives the opposite effect.
//
// - On a node with a set width/height aspect ratio control the size of the unset dimension
// - On a node with a set flex basis aspect ratio controls the size of the node in the cross axis if
// unset
// - On a node with a measure function aspect ratio works as though the measure function measures
// the flex basis
// - On a node with flex grow/shrink aspect ratio controls the size of the node in the cross axis if
// unset
// - Aspect ratio takes min/max dimensions into account
ABI19_0_0YG_NODE_STYLE_PROPERTY(float, AspectRatio, aspectRatio);

ABI19_0_0YG_NODE_LAYOUT_PROPERTY(float, Left);
ABI19_0_0YG_NODE_LAYOUT_PROPERTY(float, Top);
ABI19_0_0YG_NODE_LAYOUT_PROPERTY(float, Right);
ABI19_0_0YG_NODE_LAYOUT_PROPERTY(float, Bottom);
ABI19_0_0YG_NODE_LAYOUT_PROPERTY(float, Width);
ABI19_0_0YG_NODE_LAYOUT_PROPERTY(float, Height);
ABI19_0_0YG_NODE_LAYOUT_PROPERTY(ABI19_0_0YGDirection, Direction);

// Get the computed values for these nodes after performing layout. If they were set using
// point values then the returned value will be the same as ABI19_0_0YGNodeStyleGetXXX. However if
// they were set using a percentage value then the returned value is the computed value used
// during layout.
ABI19_0_0YG_NODE_LAYOUT_EDGE_PROPERTY(float, Margin);
ABI19_0_0YG_NODE_LAYOUT_EDGE_PROPERTY(float, Border);
ABI19_0_0YG_NODE_LAYOUT_EDGE_PROPERTY(float, Padding);

WIN_EXPORT void ABI19_0_0YGConfigSetLogger(const ABI19_0_0YGConfigRef config, ABI19_0_0YGLogger logger);
WIN_EXPORT void ABI19_0_0YGLog(const ABI19_0_0YGNodeRef node, ABI19_0_0YGLogLevel level, const char *message, ...);
WIN_EXPORT void ABI19_0_0YGLogWithConfig(const ABI19_0_0YGConfigRef config, ABI19_0_0YGLogLevel level, const char *format, ...);
WIN_EXPORT void ABI19_0_0YGAssert(const bool condition, const char *message);
WIN_EXPORT void ABI19_0_0YGAssertWithNode(const ABI19_0_0YGNodeRef node, const bool condition, const char *message);
WIN_EXPORT void ABI19_0_0YGAssertWithConfig(const ABI19_0_0YGConfigRef config,
                                   const bool condition,
                                   const char *message);

// Set this to number of pixels in 1 point to round calculation results
// If you want to avoid rounding - set PointScaleFactor to 0
WIN_EXPORT void ABI19_0_0YGConfigSetPointScaleFactor(const ABI19_0_0YGConfigRef config, const float pixelsInPoint);

// Yoga previously had an error where containers would take the maximum space possible instead of
// the minimum
// like they are supposed to. In practice this resulted in implicit behaviour similar to align-self:
// stretch;
// Because this was such a long-standing bug we must allow legacy users to switch back to this
// behaviour.
WIN_EXPORT void ABI19_0_0YGConfigSetUseLegacyStretchBehaviour(const ABI19_0_0YGConfigRef config,
                                                     const bool useLegacyStretchBehaviour);

// ABI19_0_0YGConfig
WIN_EXPORT ABI19_0_0YGConfigRef ABI19_0_0YGConfigNew(void);
WIN_EXPORT void ABI19_0_0YGConfigFree(const ABI19_0_0YGConfigRef config);
WIN_EXPORT void ABI19_0_0YGConfigCopy(const ABI19_0_0YGConfigRef dest, const ABI19_0_0YGConfigRef src);
WIN_EXPORT int32_t ABI19_0_0YGConfigGetInstanceCount(void);

WIN_EXPORT void ABI19_0_0YGConfigSetExperimentalFeatureEnabled(const ABI19_0_0YGConfigRef config,
                                                      const ABI19_0_0YGExperimentalFeature feature,
                                                      const bool enabled);
WIN_EXPORT bool ABI19_0_0YGConfigIsExperimentalFeatureEnabled(const ABI19_0_0YGConfigRef config,
                                                     const ABI19_0_0YGExperimentalFeature feature);

// Using the web defaults is the prefered configuration for new projects.
// Usage of non web defaults should be considered as legacy.
WIN_EXPORT void ABI19_0_0YGConfigSetUseWebDefaults(const ABI19_0_0YGConfigRef config, const bool enabled);
WIN_EXPORT bool ABI19_0_0YGConfigGetUseWebDefaults(const ABI19_0_0YGConfigRef config);

// Export only for C#
WIN_EXPORT ABI19_0_0YGConfigRef ABI19_0_0YGConfigGetDefault(void);

WIN_EXPORT void ABI19_0_0YGConfigSetContext(const ABI19_0_0YGConfigRef config, void *context);
WIN_EXPORT void *ABI19_0_0YGConfigGetContext(const ABI19_0_0YGConfigRef config);

WIN_EXPORT void
ABI19_0_0YGSetMemoryFuncs(ABI19_0_0YGMalloc ygmalloc, ABI19_0_0YGCalloc yccalloc, ABI19_0_0YGRealloc ygrealloc, ABI19_0_0YGFree ygfree);

ABI19_0_0YG_EXTERN_C_END
