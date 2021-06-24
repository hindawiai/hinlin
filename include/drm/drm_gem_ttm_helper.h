<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

#अगर_अघोषित DRM_GEM_TTM_HELPER_H
#घोषणा DRM_GEM_TTM_HELPER_H

#समावेश <linux/kernel.h>

#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>

काष्ठा dma_buf_map;

#घोषणा drm_gem_tपंचांग_of_gem(gem_obj) \
	container_of(gem_obj, काष्ठा tपंचांग_buffer_object, base)

व्योम drm_gem_tपंचांग_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
			    स्थिर काष्ठा drm_gem_object *gem);
पूर्णांक drm_gem_tपंचांग_vmap(काष्ठा drm_gem_object *gem,
		     काष्ठा dma_buf_map *map);
व्योम drm_gem_tपंचांग_vunmap(काष्ठा drm_gem_object *gem,
			काष्ठा dma_buf_map *map);
पूर्णांक drm_gem_tपंचांग_mmap(काष्ठा drm_gem_object *gem,
		     काष्ठा vm_area_काष्ठा *vma);

#पूर्ण_अगर
