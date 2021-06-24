<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_SHRINKER_H__
#घोषणा __I915_GEM_SHRINKER_H__

#समावेश <linux/bits.h>

काष्ठा drm_i915_निजी;
काष्ठा i915_gem_ww_ctx;
काष्ठा mutex;

/* i915_gem_shrinker.c */
अचिन्हित दीर्घ i915_gem_shrink(काष्ठा i915_gem_ww_ctx *ww,
			      काष्ठा drm_i915_निजी *i915,
			      अचिन्हित दीर्घ target,
			      अचिन्हित दीर्घ *nr_scanned,
			      अचिन्हित flags);
#घोषणा I915_SHRINK_UNBOUND	BIT(0)
#घोषणा I915_SHRINK_BOUND	BIT(1)
#घोषणा I915_SHRINK_ACTIVE	BIT(2)
#घोषणा I915_SHRINK_VMAPS	BIT(3)
#घोषणा I915_SHRINK_WRITEBACK	BIT(4)

अचिन्हित दीर्घ i915_gem_shrink_all(काष्ठा drm_i915_निजी *i915);
व्योम i915_gem_driver_रेजिस्टर__shrinker(काष्ठा drm_i915_निजी *i915);
व्योम i915_gem_driver_unरेजिस्टर__shrinker(काष्ठा drm_i915_निजी *i915);
व्योम i915_gem_shrinker_taपूर्णांकs_mutex(काष्ठा drm_i915_निजी *i915,
				    काष्ठा mutex *mutex);

#पूर्ण_अगर /* __I915_GEM_SHRINKER_H__ */
