<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#अगर_अघोषित __ETNAVIV_GEM_H__
#घोषणा __ETNAVIV_GEM_H__

#समावेश <linux/dma-resv.h>
#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_drv.h"

काष्ठा dma_fence;
काष्ठा etnaviv_gem_ops;
काष्ठा etnaviv_gem_object;

काष्ठा etnaviv_gem_userptr अणु
	uपूर्णांकptr_t ptr;
	काष्ठा mm_काष्ठा *mm;
	bool ro;
पूर्ण;

काष्ठा etnaviv_vram_mapping अणु
	काष्ठा list_head obj_node;
	काष्ठा list_head scan_node;
	काष्ठा list_head mmu_node;
	काष्ठा etnaviv_gem_object *object;
	काष्ठा etnaviv_iommu_context *context;
	काष्ठा drm_mm_node vram_node;
	अचिन्हित पूर्णांक use;
	u32 iova;
पूर्ण;

काष्ठा etnaviv_gem_object अणु
	काष्ठा drm_gem_object base;
	स्थिर काष्ठा etnaviv_gem_ops *ops;
	काष्ठा mutex lock;

	u32 flags;

	काष्ठा list_head gem_node;
	काष्ठा etnaviv_gpu *gpu;     /* non-null अगर active */
	atomic_t gpu_active;
	u32 access;

	काष्ठा page **pages;
	काष्ठा sg_table *sgt;
	व्योम *vaddr;

	काष्ठा list_head vram_list;

	/* cache मुख्यtenance */
	u32 last_cpu_prep_op;

	काष्ठा etnaviv_gem_userptr userptr;
पूर्ण;

अटल अंतरभूत
काष्ठा etnaviv_gem_object *to_etnaviv_bo(काष्ठा drm_gem_object *obj)
अणु
	वापस container_of(obj, काष्ठा etnaviv_gem_object, base);
पूर्ण

काष्ठा etnaviv_gem_ops अणु
	पूर्णांक (*get_pages)(काष्ठा etnaviv_gem_object *);
	व्योम (*release)(काष्ठा etnaviv_gem_object *);
	व्योम *(*vmap)(काष्ठा etnaviv_gem_object *);
	पूर्णांक (*mmap)(काष्ठा etnaviv_gem_object *, काष्ठा vm_area_काष्ठा *);
पूर्ण;

अटल अंतरभूत bool is_active(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	वापस atomic_पढ़ो(&etnaviv_obj->gpu_active) != 0;
पूर्ण

#घोषणा MAX_CMDS 4

काष्ठा etnaviv_gem_submit_bo अणु
	u32 flags;
	u64 va;
	काष्ठा etnaviv_gem_object *obj;
	काष्ठा etnaviv_vram_mapping *mapping;
	काष्ठा dma_fence *excl;
	अचिन्हित पूर्णांक nr_shared;
	काष्ठा dma_fence **shared;
पूर्ण;

/* Created per submit-ioctl, to track bo's and cmdstream bufs, etc,
 * associated with the cmdstream submission क्रम synchronization (and
 * make it easier to unwind when things go wrong, etc).
 */
काष्ठा etnaviv_gem_submit अणु
	काष्ठा drm_sched_job sched_job;
	काष्ठा kref refcount;
	काष्ठा etnaviv_file_निजी *ctx;
	काष्ठा etnaviv_gpu *gpu;
	काष्ठा etnaviv_iommu_context *mmu_context, *prev_mmu_context;
	काष्ठा dma_fence *out_fence, *in_fence;
	पूर्णांक out_fence_id;
	काष्ठा list_head node; /* GPU active submit list */
	काष्ठा etnaviv_cmdbuf cmdbuf;
	bool runसमय_resumed;
	u32 exec_state;
	u32 flags;
	अचिन्हित पूर्णांक nr_pmrs;
	काष्ठा etnaviv_perfmon_request *pmrs;
	अचिन्हित पूर्णांक nr_bos;
	काष्ठा etnaviv_gem_submit_bo bos[];
	/* No new members here, the previous one is variable-length! */
पूर्ण;

व्योम etnaviv_submit_put(काष्ठा etnaviv_gem_submit * submit);

पूर्णांक etnaviv_gem_रुको_bo(काष्ठा etnaviv_gpu *gpu, काष्ठा drm_gem_object *obj,
	काष्ठा drm_etnaviv_बारpec *समयout);
पूर्णांक etnaviv_gem_new_निजी(काष्ठा drm_device *dev, माप_प्रकार size, u32 flags,
	स्थिर काष्ठा etnaviv_gem_ops *ops, काष्ठा etnaviv_gem_object **res);
व्योम etnaviv_gem_obj_add(काष्ठा drm_device *dev, काष्ठा drm_gem_object *obj);
काष्ठा page **etnaviv_gem_get_pages(काष्ठा etnaviv_gem_object *obj);
व्योम etnaviv_gem_put_pages(काष्ठा etnaviv_gem_object *obj);

काष्ठा etnaviv_vram_mapping *etnaviv_gem_mapping_get(
	काष्ठा drm_gem_object *obj, काष्ठा etnaviv_iommu_context *mmu_context,
	u64 va);
व्योम etnaviv_gem_mapping_unreference(काष्ठा etnaviv_vram_mapping *mapping);

#पूर्ण_अगर /* __ETNAVIV_GEM_H__ */
