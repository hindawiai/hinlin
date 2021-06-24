<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __VLV_SUSPEND_H__
#घोषणा __VLV_SUSPEND_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;

पूर्णांक vlv_suspend_init(काष्ठा drm_i915_निजी *i915);
व्योम vlv_suspend_cleanup(काष्ठा drm_i915_निजी *i915);
पूर्णांक vlv_suspend_complete(काष्ठा drm_i915_निजी *i915);
पूर्णांक vlv_resume_prepare(काष्ठा drm_i915_निजी *i915, bool rpm_resume);

#पूर्ण_अगर /* __VLV_SUSPEND_H__ */
