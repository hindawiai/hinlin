<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __MOCK_CONTEXT_H
#घोषणा __MOCK_CONTEXT_H

काष्ठा file;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_engine_cs;

व्योम mock_init_contexts(काष्ठा drm_i915_निजी *i915);

काष्ठा i915_gem_context *
mock_context(काष्ठा drm_i915_निजी *i915,
	     स्थिर अक्षर *name);

व्योम mock_context_बंद(काष्ठा i915_gem_context *ctx);

काष्ठा i915_gem_context *
live_context(काष्ठा drm_i915_निजी *i915, काष्ठा file *file);

काष्ठा i915_gem_context *
live_context_क्रम_engine(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा file *file);

काष्ठा i915_gem_context *kernel_context(काष्ठा drm_i915_निजी *i915);
व्योम kernel_context_बंद(काष्ठा i915_gem_context *ctx);

#पूर्ण_अगर /* !__MOCK_CONTEXT_H */
