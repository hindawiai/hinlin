<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __HUGE_GEM_OBJECT_H
#घोषणा __HUGE_GEM_OBJECT_H

#समावेश <linux/types.h>

#समावेश "gem/i915_gem_object_types.h"

काष्ठा drm_i915_निजी;

काष्ठा drm_i915_gem_object *
huge_gem_object(काष्ठा drm_i915_निजी *i915,
		phys_addr_t phys_size,
		dma_addr_t dma_size);

अटल अंतरभूत phys_addr_t
huge_gem_object_phys_size(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->scratch;
पूर्ण

अटल अंतरभूत dma_addr_t
huge_gem_object_dma_size(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->base.size;
पूर्ण

#पूर्ण_अगर /* !__HUGE_GEM_OBJECT_H */
