<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_PM_H__
#घोषणा __I915_GEM_PM_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा work_काष्ठा;

व्योम i915_gem_resume(काष्ठा drm_i915_निजी *i915);

व्योम i915_gem_idle_work_handler(काष्ठा work_काष्ठा *work);

व्योम i915_gem_suspend(काष्ठा drm_i915_निजी *i915);
व्योम i915_gem_suspend_late(काष्ठा drm_i915_निजी *i915);

पूर्णांक i915_gem_मुक्तze(काष्ठा drm_i915_निजी *i915);
पूर्णांक i915_gem_मुक्तze_late(काष्ठा drm_i915_निजी *i915);

#पूर्ण_अगर /* __I915_GEM_PM_H__ */
