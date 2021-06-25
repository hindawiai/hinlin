<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_GEM_H__
#घोषणा __LIMA_GEM_H__

#समावेश <drm/drm_gem_shmem_helper.h>

काष्ठा lima_submit;
काष्ठा lima_vm;

काष्ठा lima_bo अणु
	काष्ठा drm_gem_shmem_object base;

	काष्ठा mutex lock;
	काष्ठा list_head va;

	माप_प्रकार heap_size;
पूर्ण;

अटल अंतरभूत काष्ठा lima_bo *
to_lima_bo(काष्ठा drm_gem_object *obj)
अणु
	वापस container_of(to_drm_gem_shmem_obj(obj), काष्ठा lima_bo, base);
पूर्ण

अटल अंतरभूत माप_प्रकार lima_bo_size(काष्ठा lima_bo *bo)
अणु
	वापस bo->base.base.size;
पूर्ण

अटल अंतरभूत काष्ठा dma_resv *lima_bo_resv(काष्ठा lima_bo *bo)
अणु
	वापस bo->base.base.resv;
पूर्ण

पूर्णांक lima_heap_alloc(काष्ठा lima_bo *bo, काष्ठा lima_vm *vm);
काष्ठा drm_gem_object *lima_gem_create_object(काष्ठा drm_device *dev, माप_प्रकार size);
पूर्णांक lima_gem_create_handle(काष्ठा drm_device *dev, काष्ठा drm_file *file,
			   u32 size, u32 flags, u32 *handle);
पूर्णांक lima_gem_get_info(काष्ठा drm_file *file, u32 handle, u32 *va, u64 *offset);
पूर्णांक lima_gem_submit(काष्ठा drm_file *file, काष्ठा lima_submit *submit);
पूर्णांक lima_gem_रुको(काष्ठा drm_file *file, u32 handle, u32 op, s64 समयout_ns);

व्योम lima_set_vma_flags(काष्ठा vm_area_काष्ठा *vma);

#पूर्ण_अगर
