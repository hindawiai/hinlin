<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_ENGINE_USER_H
#घोषणा INTEL_ENGINE_USER_H

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_engine_cs;

काष्ठा पूर्णांकel_engine_cs *
पूर्णांकel_engine_lookup_user(काष्ठा drm_i915_निजी *i915, u8 class, u8 instance);

अचिन्हित पूर्णांक पूर्णांकel_engines_has_context_isolation(काष्ठा drm_i915_निजी *i915);

व्योम पूर्णांकel_engine_add_user(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम पूर्णांकel_engines_driver_रेजिस्टर(काष्ठा drm_i915_निजी *i915);

स्थिर अक्षर *पूर्णांकel_engine_class_repr(u8 class);

#पूर्ण_अगर /* INTEL_ENGINE_USER_H */
