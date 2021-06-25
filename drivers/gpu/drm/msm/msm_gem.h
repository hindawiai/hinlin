<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MSM_GEM_H__
#घोषणा __MSM_GEM_H__

#समावेश <linux/kref.h>
#समावेश <linux/dma-resv.h>
#समावेश "msm_drv.h"

/* Make all GEM related WARN_ON()s ratelimited.. when things go wrong they
 * tend to go wrong 1000s of बार in a लघु बारpan.
 */
#घोषणा GEM_WARN_ON(x)  WARN_RATELIMIT(x, "%s", __stringअगरy(x))

/* Additional पूर्णांकernal-use only BO flags: */
#घोषणा MSM_BO_STOLEN        0x10000000    /* try to use stolen/splash memory */
#घोषणा MSM_BO_MAP_PRIV      0x20000000    /* use IOMMU_PRIV when mapping */

काष्ठा msm_gem_address_space अणु
	स्थिर अक्षर *name;
	/* NOTE: mm managed at the page level, size is in # of pages
	 * and position mm_node->start is in # of pages:
	 */
	काष्ठा drm_mm mm;
	spinlock_t lock; /* Protects drm_mm node allocation/removal */
	काष्ठा msm_mmu *mmu;
	काष्ठा kref kref;

	/* For address spaces associated with a specअगरic process, this
	 * will be non-शून्य:
	 */
	काष्ठा pid *pid;
पूर्ण;

काष्ठा msm_gem_vma अणु
	काष्ठा drm_mm_node node;
	uपूर्णांक64_t iova;
	काष्ठा msm_gem_address_space *aspace;
	काष्ठा list_head list;    /* node in msm_gem_object::vmas */
	bool mapped;
	पूर्णांक inuse;
पूर्ण;

काष्ठा msm_gem_object अणु
	काष्ठा drm_gem_object base;

	uपूर्णांक32_t flags;

	/**
	 * Advice: are the backing pages purgeable?
	 */
	uपूर्णांक8_t madv;

	/**
	 * Is object on inactive_करोntneed list (ie. counted in priv->shrinkable_count)?
	 */
	bool करोntneed : 1;

	/**
	 * Is object evictable (ie. counted in priv->evictable_count)?
	 */
	bool evictable : 1;

	/**
	 * count of active vmap'ing
	 */
	uपूर्णांक8_t vmap_count;

	/**
	 * Node in list of all objects (मुख्यly क्रम debugfs, रक्षित by
	 * priv->obj_lock
	 */
	काष्ठा list_head node;

	/**
	 * An object is either:
	 *  inactive - on priv->inactive_करोntneed or priv->inactive_willneed
	 *     (depending on purgeability status)
	 *  active   - on one one of the gpu's active_list..  well, at
	 *     least क्रम now we करोn't have (I don't think) hw sync between
	 *     2d and 3d one devices which have both, meaning we need to
	 *     block on submit अगर a bo is alपढ़ोy on other ring
	 */
	काष्ठा list_head mm_list;

	/* Transiently in the process of submit ioctl, objects associated
	 * with the submit are on submit->bo_list.. this only lasts क्रम
	 * the duration of the ioctl, so one bo can never be on multiple
	 * submit lists.
	 */
	काष्ठा list_head submit_entry;

	काष्ठा page **pages;
	काष्ठा sg_table *sgt;
	व्योम *vaddr;

	काष्ठा list_head vmas;    /* list of msm_gem_vma */

	/* For physically contiguous buffers.  Used when we करोn't have
	 * an IOMMU.  Also used क्रम stolen/splashscreen buffer.
	 */
	काष्ठा drm_mm_node *vram_node;

	अक्षर name[32]; /* Identअगरier to prपूर्णांक क्रम the debugfs files */

	पूर्णांक active_count;
	पूर्णांक pin_count;
पूर्ण;
#घोषणा to_msm_bo(x) container_of(x, काष्ठा msm_gem_object, base)

पूर्णांक msm_gem_mmap_obj(काष्ठा drm_gem_object *obj,
			काष्ठा vm_area_काष्ठा *vma);
पूर्णांक msm_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);
uपूर्णांक64_t msm_gem_mmap_offset(काष्ठा drm_gem_object *obj);
पूर्णांक msm_gem_get_iova(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova);
पूर्णांक msm_gem_get_and_pin_iova_range(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova,
		u64 range_start, u64 range_end);
पूर्णांक msm_gem_get_and_pin_iova_locked(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova);
पूर्णांक msm_gem_get_and_pin_iova(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova);
uपूर्णांक64_t msm_gem_iova(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace);
व्योम msm_gem_unpin_iova_locked(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace);
व्योम msm_gem_unpin_iova(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace);
काष्ठा page **msm_gem_get_pages(काष्ठा drm_gem_object *obj);
व्योम msm_gem_put_pages(काष्ठा drm_gem_object *obj);
पूर्णांक msm_gem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
		काष्ठा drm_mode_create_dumb *args);
पूर्णांक msm_gem_dumb_map_offset(काष्ठा drm_file *file, काष्ठा drm_device *dev,
		uपूर्णांक32_t handle, uपूर्णांक64_t *offset);
व्योम *msm_gem_get_vaddr_locked(काष्ठा drm_gem_object *obj);
व्योम *msm_gem_get_vaddr(काष्ठा drm_gem_object *obj);
व्योम *msm_gem_get_vaddr_active(काष्ठा drm_gem_object *obj);
व्योम msm_gem_put_vaddr_locked(काष्ठा drm_gem_object *obj);
व्योम msm_gem_put_vaddr(काष्ठा drm_gem_object *obj);
पूर्णांक msm_gem_madvise(काष्ठा drm_gem_object *obj, अचिन्हित madv);
पूर्णांक msm_gem_sync_object(काष्ठा drm_gem_object *obj,
		काष्ठा msm_fence_context *fctx, bool exclusive);
व्योम msm_gem_active_get(काष्ठा drm_gem_object *obj, काष्ठा msm_gpu *gpu);
व्योम msm_gem_active_put(काष्ठा drm_gem_object *obj);
पूर्णांक msm_gem_cpu_prep(काष्ठा drm_gem_object *obj, uपूर्णांक32_t op, kसमय_प्रकार *समयout);
पूर्णांक msm_gem_cpu_fini(काष्ठा drm_gem_object *obj);
व्योम msm_gem_मुक्त_object(काष्ठा drm_gem_object *obj);
पूर्णांक msm_gem_new_handle(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		uपूर्णांक32_t size, uपूर्णांक32_t flags, uपूर्णांक32_t *handle, अक्षर *name);
काष्ठा drm_gem_object *msm_gem_new(काष्ठा drm_device *dev,
		uपूर्णांक32_t size, uपूर्णांक32_t flags);
काष्ठा drm_gem_object *msm_gem_new_locked(काष्ठा drm_device *dev,
		uपूर्णांक32_t size, uपूर्णांक32_t flags);
व्योम *msm_gem_kernel_new(काष्ठा drm_device *dev, uपूर्णांक32_t size,
		uपूर्णांक32_t flags, काष्ठा msm_gem_address_space *aspace,
		काष्ठा drm_gem_object **bo, uपूर्णांक64_t *iova);
व्योम *msm_gem_kernel_new_locked(काष्ठा drm_device *dev, uपूर्णांक32_t size,
		uपूर्णांक32_t flags, काष्ठा msm_gem_address_space *aspace,
		काष्ठा drm_gem_object **bo, uपूर्णांक64_t *iova);
व्योम msm_gem_kernel_put(काष्ठा drm_gem_object *bo,
		काष्ठा msm_gem_address_space *aspace, bool locked);
काष्ठा drm_gem_object *msm_gem_import(काष्ठा drm_device *dev,
		काष्ठा dma_buf *dmabuf, काष्ठा sg_table *sgt);
__म_लिखो(2, 3)
व्योम msm_gem_object_set_name(काष्ठा drm_gem_object *bo, स्थिर अक्षर *fmt, ...);

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा msm_gem_stats अणु
	काष्ठा अणु
		अचिन्हित count;
		माप_प्रकार size;
	पूर्ण all, active, resident, purgeable, purged;
पूर्ण;

व्योम msm_gem_describe(काष्ठा drm_gem_object *obj, काष्ठा seq_file *m,
		काष्ठा msm_gem_stats *stats);
व्योम msm_gem_describe_objects(काष्ठा list_head *list, काष्ठा seq_file *m);
#पूर्ण_अगर

अटल अंतरभूत व्योम
msm_gem_lock(काष्ठा drm_gem_object *obj)
अणु
	dma_resv_lock(obj->resv, शून्य);
पूर्ण

अटल अंतरभूत bool __must_check
msm_gem_trylock(काष्ठा drm_gem_object *obj)
अणु
	वापस dma_resv_trylock(obj->resv);
पूर्ण

अटल अंतरभूत पूर्णांक
msm_gem_lock_पूर्णांकerruptible(काष्ठा drm_gem_object *obj)
अणु
	वापस dma_resv_lock_पूर्णांकerruptible(obj->resv, शून्य);
पूर्ण

अटल अंतरभूत व्योम
msm_gem_unlock(काष्ठा drm_gem_object *obj)
अणु
	dma_resv_unlock(obj->resv);
पूर्ण

अटल अंतरभूत bool
msm_gem_is_locked(काष्ठा drm_gem_object *obj)
अणु
	वापस dma_resv_is_locked(obj->resv);
पूर्ण

अटल अंतरभूत bool is_active(काष्ठा msm_gem_object *msm_obj)
अणु
	GEM_WARN_ON(!msm_gem_is_locked(&msm_obj->base));
	वापस msm_obj->active_count;
पूर्ण

/* imported/exported objects are not purgeable: */
अटल अंतरभूत bool is_unpurgeable(काष्ठा msm_gem_object *msm_obj)
अणु
	वापस msm_obj->base.import_attach || msm_obj->pin_count;
पूर्ण

अटल अंतरभूत bool is_purgeable(काष्ठा msm_gem_object *msm_obj)
अणु
	वापस (msm_obj->madv == MSM_MADV_DONTNEED) && msm_obj->sgt &&
			!is_unpurgeable(msm_obj);
पूर्ण

अटल अंतरभूत bool is_vunmapable(काष्ठा msm_gem_object *msm_obj)
अणु
	GEM_WARN_ON(!msm_gem_is_locked(&msm_obj->base));
	वापस (msm_obj->vmap_count == 0) && msm_obj->vaddr;
पूर्ण

अटल अंतरभूत व्योम mark_purgeable(काष्ठा msm_gem_object *msm_obj)
अणु
	काष्ठा msm_drm_निजी *priv = msm_obj->base.dev->dev_निजी;

	GEM_WARN_ON(!mutex_is_locked(&priv->mm_lock));

	अगर (is_unpurgeable(msm_obj))
		वापस;

	अगर (GEM_WARN_ON(msm_obj->करोntneed))
		वापस;

	priv->shrinkable_count += msm_obj->base.size >> PAGE_SHIFT;
	msm_obj->करोntneed = true;
पूर्ण

अटल अंतरभूत व्योम mark_unpurgeable(काष्ठा msm_gem_object *msm_obj)
अणु
	काष्ठा msm_drm_निजी *priv = msm_obj->base.dev->dev_निजी;

	GEM_WARN_ON(!mutex_is_locked(&priv->mm_lock));

	अगर (is_unpurgeable(msm_obj))
		वापस;

	अगर (GEM_WARN_ON(!msm_obj->करोntneed))
		वापस;

	priv->shrinkable_count -= msm_obj->base.size >> PAGE_SHIFT;
	GEM_WARN_ON(priv->shrinkable_count < 0);
	msm_obj->करोntneed = false;
पूर्ण

अटल अंतरभूत bool is_unevictable(काष्ठा msm_gem_object *msm_obj)
अणु
	वापस is_unpurgeable(msm_obj) || msm_obj->vaddr;
पूर्ण

अटल अंतरभूत व्योम mark_evictable(काष्ठा msm_gem_object *msm_obj)
अणु
	काष्ठा msm_drm_निजी *priv = msm_obj->base.dev->dev_निजी;

	WARN_ON(!mutex_is_locked(&priv->mm_lock));

	अगर (is_unevictable(msm_obj))
		वापस;

	अगर (WARN_ON(msm_obj->evictable))
		वापस;

	priv->evictable_count += msm_obj->base.size >> PAGE_SHIFT;
	msm_obj->evictable = true;
पूर्ण

अटल अंतरभूत व्योम mark_unevictable(काष्ठा msm_gem_object *msm_obj)
अणु
	काष्ठा msm_drm_निजी *priv = msm_obj->base.dev->dev_निजी;

	WARN_ON(!mutex_is_locked(&priv->mm_lock));

	अगर (is_unevictable(msm_obj))
		वापस;

	अगर (WARN_ON(!msm_obj->evictable))
		वापस;

	priv->evictable_count -= msm_obj->base.size >> PAGE_SHIFT;
	WARN_ON(priv->evictable_count < 0);
	msm_obj->evictable = false;
पूर्ण

व्योम msm_gem_purge(काष्ठा drm_gem_object *obj);
व्योम msm_gem_evict(काष्ठा drm_gem_object *obj);
व्योम msm_gem_vunmap(काष्ठा drm_gem_object *obj);

/* Created per submit-ioctl, to track bo's and cmdstream bufs, etc,
 * associated with the cmdstream submission क्रम synchronization (and
 * make it easier to unwind when things go wrong, etc).  This only
 * lasts क्रम the duration of the submit-ioctl.
 */
काष्ठा msm_gem_submit अणु
	काष्ठा kref ref;
	काष्ठा drm_device *dev;
	काष्ठा msm_gpu *gpu;
	काष्ठा msm_gem_address_space *aspace;
	काष्ठा list_head node;   /* node in ring submit list */
	काष्ठा list_head bo_list;
	काष्ठा ww_acquire_ctx ticket;
	uपूर्णांक32_t seqno;		/* Sequence number of the submit on the ring */
	काष्ठा dma_fence *fence;
	काष्ठा msm_gpu_submitqueue *queue;
	काष्ठा pid *pid;    /* submitting process */
	bool valid;         /* true अगर no cmdstream patching needed */
	bool in_rb;         /* "sudo" mode, copy cmds पूर्णांकo RB */
	काष्ठा msm_ringbuffer *ring;
	काष्ठा msm_file_निजी *ctx;
	अचिन्हित पूर्णांक nr_cmds;
	अचिन्हित पूर्णांक nr_bos;
	u32 ident;	   /* A "identifier" क्रम the submit क्रम logging */
	काष्ठा अणु
		uपूर्णांक32_t type;
		uपूर्णांक32_t size;  /* in dwords */
		uपूर्णांक64_t iova;
		uपूर्णांक32_t offset;/* in dwords */
		uपूर्णांक32_t idx;   /* cmdstream buffer idx in bos[] */
		uपूर्णांक32_t nr_relocs;
		काष्ठा drm_msm_gem_submit_reloc *relocs;
	पूर्ण *cmd;  /* array of size nr_cmds */
	काष्ठा अणु
		uपूर्णांक32_t flags;
		जोड़ अणु
			काष्ठा msm_gem_object *obj;
			uपूर्णांक32_t handle;
		पूर्ण;
		uपूर्णांक64_t iova;
	पूर्ण bos[];
पूर्ण;

व्योम __msm_gem_submit_destroy(काष्ठा kref *kref);

अटल अंतरभूत व्योम msm_gem_submit_get(काष्ठा msm_gem_submit *submit)
अणु
	kref_get(&submit->ref);
पूर्ण

अटल अंतरभूत व्योम msm_gem_submit_put(काष्ठा msm_gem_submit *submit)
अणु
	kref_put(&submit->ref, __msm_gem_submit_destroy);
पूर्ण

/* helper to determine of a buffer in submit should be dumped, used क्रम both
 * devcoredump and debugfs cmdstream dumping:
 */
अटल अंतरभूत bool
should_dump(काष्ठा msm_gem_submit *submit, पूर्णांक idx)
अणु
	बाह्य bool rd_full;
	वापस rd_full || (submit->bos[idx].flags & MSM_SUBMIT_BO_DUMP);
पूर्ण

#पूर्ण_अगर /* __MSM_GEM_H__ */
