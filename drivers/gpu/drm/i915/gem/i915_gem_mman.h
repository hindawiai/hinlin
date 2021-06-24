<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_MMAN_H__
#घोषणा __I915_GEM_MMAN_H__

#समावेश <linux/mm_types.h>
#समावेश <linux/types.h>

काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_i915_gem_object;
काष्ठा file;
काष्ठा i915_mmap_offset;
काष्ठा mutex;

पूर्णांक i915_gem_mmap_gtt_version(व्योम);
पूर्णांक i915_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);

पूर्णांक i915_gem_dumb_mmap_offset(काष्ठा drm_file *file_priv,
			      काष्ठा drm_device *dev,
			      u32 handle, u64 *offset);

व्योम __i915_gem_object_release_mmap_gtt(काष्ठा drm_i915_gem_object *obj);
व्योम i915_gem_object_release_mmap_gtt(काष्ठा drm_i915_gem_object *obj);

व्योम i915_gem_object_release_mmap_offset(काष्ठा drm_i915_gem_object *obj);

#पूर्ण_अगर
