<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */
#अगर_अघोषित __AMDGPU_OBJECT_H__
#घोषणा __AMDGPU_OBJECT_H__

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#अगर_घोषित CONFIG_MMU_NOTIFIER
#समावेश <linux/mmu_notअगरier.h>
#पूर्ण_अगर

#घोषणा AMDGPU_BO_INVALID_OFFSET	दीर्घ_उच्च
#घोषणा AMDGPU_BO_MAX_PLACEMENTS	3

#घोषणा to_amdgpu_bo_user(abo) container_of((abo), काष्ठा amdgpu_bo_user, bo)

काष्ठा amdgpu_bo_param अणु
	अचिन्हित दीर्घ			size;
	पूर्णांक				byte_align;
	u32				bo_ptr_size;
	u32				करोमुख्य;
	u32				preferred_करोमुख्य;
	u64				flags;
	क्रमागत tपंचांग_bo_type		type;
	bool				no_रुको_gpu;
	काष्ठा dma_resv	*resv;
पूर्ण;

/* bo भव addresses in a vm */
काष्ठा amdgpu_bo_va_mapping अणु
	काष्ठा amdgpu_bo_va		*bo_va;
	काष्ठा list_head		list;
	काष्ठा rb_node			rb;
	uपूर्णांक64_t			start;
	uपूर्णांक64_t			last;
	uपूर्णांक64_t			__subtree_last;
	uपूर्णांक64_t			offset;
	uपूर्णांक64_t			flags;
पूर्ण;

/* User space allocated BO in a VM */
काष्ठा amdgpu_bo_va अणु
	काष्ठा amdgpu_vm_bo_base	base;

	/* रक्षित by bo being reserved */
	अचिन्हित			ref_count;

	/* all other members रक्षित by the VM PD being reserved */
	काष्ठा dma_fence	        *last_pt_update;

	/* mappings क्रम this bo_va */
	काष्ठा list_head		invalids;
	काष्ठा list_head		valids;

	/* If the mappings are cleared or filled */
	bool				cleared;

	bool				is_xgmi;
पूर्ण;

काष्ठा amdgpu_bo अणु
	/* Protected by tbo.reserved */
	u32				preferred_करोमुख्यs;
	u32				allowed_करोमुख्यs;
	काष्ठा tपंचांग_place		placements[AMDGPU_BO_MAX_PLACEMENTS];
	काष्ठा tपंचांग_placement		placement;
	काष्ठा tपंचांग_buffer_object	tbo;
	काष्ठा tपंचांग_bo_kmap_obj		kmap;
	u64				flags;
	अचिन्हित			prime_shared_count;
	/* per VM काष्ठाure क्रम page tables and with भव addresses */
	काष्ठा amdgpu_vm_bo_base	*vm_bo;
	/* Constant after initialization */
	काष्ठा amdgpu_bo		*parent;
	काष्ठा amdgpu_bo		*shaकरोw;



#अगर_घोषित CONFIG_MMU_NOTIFIER
	काष्ठा mmu_पूर्णांकerval_notअगरier	notअगरier;
#पूर्ण_अगर

	काष्ठा list_head		shaकरोw_list;

	काष्ठा kgd_mem                  *kfd_bo;
पूर्ण;

काष्ठा amdgpu_bo_user अणु
	काष्ठा amdgpu_bo		bo;
	u64				tiling_flags;
	u64				metadata_flags;
	व्योम				*metadata;
	u32				metadata_size;

पूर्ण;

अटल अंतरभूत काष्ठा amdgpu_bo *tपंचांग_to_amdgpu_bo(काष्ठा tपंचांग_buffer_object *tbo)
अणु
	वापस container_of(tbo, काष्ठा amdgpu_bo, tbo);
पूर्ण

/**
 * amdgpu_mem_type_to_करोमुख्य - वापस करोमुख्य corresponding to mem_type
 * @mem_type:	tपंचांग memory type
 *
 * Returns corresponding करोमुख्य of the tपंचांग mem_type
 */
अटल अंतरभूत अचिन्हित amdgpu_mem_type_to_करोमुख्य(u32 mem_type)
अणु
	चयन (mem_type) अणु
	हाल TTM_PL_VRAM:
		वापस AMDGPU_GEM_DOMAIN_VRAM;
	हाल TTM_PL_TT:
		वापस AMDGPU_GEM_DOMAIN_GTT;
	हाल TTM_PL_SYSTEM:
		वापस AMDGPU_GEM_DOMAIN_CPU;
	हाल AMDGPU_PL_GDS:
		वापस AMDGPU_GEM_DOMAIN_GDS;
	हाल AMDGPU_PL_GWS:
		वापस AMDGPU_GEM_DOMAIN_GWS;
	हाल AMDGPU_PL_OA:
		वापस AMDGPU_GEM_DOMAIN_OA;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_bo_reserve - reserve bo
 * @bo:		bo काष्ठाure
 * @no_पूर्णांकr:	करोn't वापस -ERESTARTSYS on pending संकेत
 *
 * Returns:
 * -ERESTARTSYS: A रुको क्रम the buffer to become unreserved was पूर्णांकerrupted by
 * a संकेत. Release all buffer reservations and वापस to user-space.
 */
अटल अंतरभूत पूर्णांक amdgpu_bo_reserve(काष्ठा amdgpu_bo *bo, bool no_पूर्णांकr)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	पूर्णांक r;

	r = tपंचांग_bo_reserve(&bo->tbo, !no_पूर्णांकr, false, शून्य);
	अगर (unlikely(r != 0)) अणु
		अगर (r != -ERESTARTSYS)
			dev_err(adev->dev, "%p reserve failed\n", bo);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम amdgpu_bo_unreserve(काष्ठा amdgpu_bo *bo)
अणु
	tपंचांग_bo_unreserve(&bo->tbo);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ amdgpu_bo_size(काष्ठा amdgpu_bo *bo)
अणु
	वापस bo->tbo.base.size;
पूर्ण

अटल अंतरभूत अचिन्हित amdgpu_bo_ngpu_pages(काष्ठा amdgpu_bo *bo)
अणु
	वापस bo->tbo.base.size / AMDGPU_GPU_PAGE_SIZE;
पूर्ण

अटल अंतरभूत अचिन्हित amdgpu_bo_gpu_page_alignment(काष्ठा amdgpu_bo *bo)
अणु
	वापस (bo->tbo.mem.page_alignment << PAGE_SHIFT) / AMDGPU_GPU_PAGE_SIZE;
पूर्ण

/**
 * amdgpu_bo_mmap_offset - वापस mmap offset of bo
 * @bo:	amdgpu object क्रम which we query the offset
 *
 * Returns mmap offset of the object.
 */
अटल अंतरभूत u64 amdgpu_bo_mmap_offset(काष्ठा amdgpu_bo *bo)
अणु
	वापस drm_vma_node_offset_addr(&bo->tbo.base.vma_node);
पूर्ण

/**
 * amdgpu_bo_in_cpu_visible_vram - check अगर BO is (partly) in visible VRAM
 */
अटल अंतरभूत bool amdgpu_bo_in_cpu_visible_vram(काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	अचिन्हित fpfn = adev->gmc.visible_vram_size >> PAGE_SHIFT;
	काष्ठा drm_mm_node *node = bo->tbo.mem.mm_node;
	अचिन्हित दीर्घ pages_left;

	अगर (bo->tbo.mem.mem_type != TTM_PL_VRAM)
		वापस false;

	क्रम (pages_left = bo->tbo.mem.num_pages; pages_left;
	     pages_left -= node->size, node++)
		अगर (node->start < fpfn)
			वापस true;

	वापस false;
पूर्ण

/**
 * amdgpu_bo_explicit_sync - वापस whether the bo is explicitly synced
 */
अटल अंतरभूत bool amdgpu_bo_explicit_sync(काष्ठा amdgpu_bo *bo)
अणु
	वापस bo->flags & AMDGPU_GEM_CREATE_EXPLICIT_SYNC;
पूर्ण

/**
 * amdgpu_bo_encrypted - test अगर the BO is encrypted
 * @bo: poपूर्णांकer to a buffer object
 *
 * Return true अगर the buffer object is encrypted, false otherwise.
 */
अटल अंतरभूत bool amdgpu_bo_encrypted(काष्ठा amdgpu_bo *bo)
अणु
	वापस bo->flags & AMDGPU_GEM_CREATE_ENCRYPTED;
पूर्ण

bool amdgpu_bo_is_amdgpu_bo(काष्ठा tपंचांग_buffer_object *bo);
व्योम amdgpu_bo_placement_from_करोमुख्य(काष्ठा amdgpu_bo *abo, u32 करोमुख्य);

पूर्णांक amdgpu_bo_create(काष्ठा amdgpu_device *adev,
		     काष्ठा amdgpu_bo_param *bp,
		     काष्ठा amdgpu_bo **bo_ptr);
पूर्णांक amdgpu_bo_create_reserved(काष्ठा amdgpu_device *adev,
			      अचिन्हित दीर्घ size, पूर्णांक align,
			      u32 करोमुख्य, काष्ठा amdgpu_bo **bo_ptr,
			      u64 *gpu_addr, व्योम **cpu_addr);
पूर्णांक amdgpu_bo_create_kernel(काष्ठा amdgpu_device *adev,
			    अचिन्हित दीर्घ size, पूर्णांक align,
			    u32 करोमुख्य, काष्ठा amdgpu_bo **bo_ptr,
			    u64 *gpu_addr, व्योम **cpu_addr);
पूर्णांक amdgpu_bo_create_kernel_at(काष्ठा amdgpu_device *adev,
			       uपूर्णांक64_t offset, uपूर्णांक64_t size, uपूर्णांक32_t करोमुख्य,
			       काष्ठा amdgpu_bo **bo_ptr, व्योम **cpu_addr);
पूर्णांक amdgpu_bo_create_user(काष्ठा amdgpu_device *adev,
			  काष्ठा amdgpu_bo_param *bp,
			  काष्ठा amdgpu_bo_user **ubo_ptr);
व्योम amdgpu_bo_मुक्त_kernel(काष्ठा amdgpu_bo **bo, u64 *gpu_addr,
			   व्योम **cpu_addr);
पूर्णांक amdgpu_bo_kmap(काष्ठा amdgpu_bo *bo, व्योम **ptr);
व्योम *amdgpu_bo_kptr(काष्ठा amdgpu_bo *bo);
व्योम amdgpu_bo_kunmap(काष्ठा amdgpu_bo *bo);
काष्ठा amdgpu_bo *amdgpu_bo_ref(काष्ठा amdgpu_bo *bo);
व्योम amdgpu_bo_unref(काष्ठा amdgpu_bo **bo);
पूर्णांक amdgpu_bo_pin(काष्ठा amdgpu_bo *bo, u32 करोमुख्य);
पूर्णांक amdgpu_bo_pin_restricted(काष्ठा amdgpu_bo *bo, u32 करोमुख्य,
			     u64 min_offset, u64 max_offset);
व्योम amdgpu_bo_unpin(काष्ठा amdgpu_bo *bo);
पूर्णांक amdgpu_bo_evict_vram(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_bo_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_bo_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_bo_set_tiling_flags(काष्ठा amdgpu_bo *bo, u64 tiling_flags);
व्योम amdgpu_bo_get_tiling_flags(काष्ठा amdgpu_bo *bo, u64 *tiling_flags);
पूर्णांक amdgpu_bo_set_metadata (काष्ठा amdgpu_bo *bo, व्योम *metadata,
			    uपूर्णांक32_t metadata_size, uपूर्णांक64_t flags);
पूर्णांक amdgpu_bo_get_metadata(काष्ठा amdgpu_bo *bo, व्योम *buffer,
			   माप_प्रकार buffer_size, uपूर्णांक32_t *metadata_size,
			   uपूर्णांक64_t *flags);
व्योम amdgpu_bo_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
			   bool evict,
			   काष्ठा tपंचांग_resource *new_mem);
व्योम amdgpu_bo_release_notअगरy(काष्ठा tपंचांग_buffer_object *bo);
vm_fault_t amdgpu_bo_fault_reserve_notअगरy(काष्ठा tपंचांग_buffer_object *bo);
व्योम amdgpu_bo_fence(काष्ठा amdgpu_bo *bo, काष्ठा dma_fence *fence,
		     bool shared);
पूर्णांक amdgpu_bo_sync_रुको_resv(काष्ठा amdgpu_device *adev, काष्ठा dma_resv *resv,
			     क्रमागत amdgpu_sync_mode sync_mode, व्योम *owner,
			     bool पूर्णांकr);
पूर्णांक amdgpu_bo_sync_रुको(काष्ठा amdgpu_bo *bo, व्योम *owner, bool पूर्णांकr);
u64 amdgpu_bo_gpu_offset(काष्ठा amdgpu_bo *bo);
u64 amdgpu_bo_gpu_offset_no_check(काष्ठा amdgpu_bo *bo);
पूर्णांक amdgpu_bo_validate(काष्ठा amdgpu_bo *bo);
पूर्णांक amdgpu_bo_restore_shaकरोw(काष्ठा amdgpu_bo *shaकरोw,
			     काष्ठा dma_fence **fence);
uपूर्णांक32_t amdgpu_bo_get_preferred_pin_करोमुख्य(काष्ठा amdgpu_device *adev,
					    uपूर्णांक32_t करोमुख्य);

/*
 * sub allocation
 */

अटल अंतरभूत uपूर्णांक64_t amdgpu_sa_bo_gpu_addr(काष्ठा amdgpu_sa_bo *sa_bo)
अणु
	वापस sa_bo->manager->gpu_addr + sa_bo->soffset;
पूर्ण

अटल अंतरभूत व्योम * amdgpu_sa_bo_cpu_addr(काष्ठा amdgpu_sa_bo *sa_bo)
अणु
	वापस sa_bo->manager->cpu_ptr + sa_bo->soffset;
पूर्ण

पूर्णांक amdgpu_sa_bo_manager_init(काष्ठा amdgpu_device *adev,
				     काष्ठा amdgpu_sa_manager *sa_manager,
				     अचिन्हित size, u32 align, u32 करोमुख्य);
व्योम amdgpu_sa_bo_manager_fini(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_sa_manager *sa_manager);
पूर्णांक amdgpu_sa_bo_manager_start(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_sa_manager *sa_manager);
पूर्णांक amdgpu_sa_bo_new(काष्ठा amdgpu_sa_manager *sa_manager,
		     काष्ठा amdgpu_sa_bo **sa_bo,
		     अचिन्हित size, अचिन्हित align);
व्योम amdgpu_sa_bo_मुक्त(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_sa_bo **sa_bo,
			      काष्ठा dma_fence *fence);
#अगर defined(CONFIG_DEBUG_FS)
व्योम amdgpu_sa_bo_dump_debug_info(काष्ठा amdgpu_sa_manager *sa_manager,
					 काष्ठा seq_file *m);
u64 amdgpu_bo_prपूर्णांक_info(पूर्णांक id, काष्ठा amdgpu_bo *bo, काष्ठा seq_file *m);
#पूर्ण_अगर
व्योम amdgpu_debugfs_sa_init(काष्ठा amdgpu_device *adev);

bool amdgpu_bo_support_uswc(u64 bo_flags);


#पूर्ण_अगर
