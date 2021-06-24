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
#अगर_अघोषित __RADEON_OBJECT_H__
#घोषणा __RADEON_OBJECT_H__

#समावेश <drm/radeon_drm.h>
#समावेश "radeon.h"

/**
 * radeon_mem_type_to_करोमुख्य - वापस करोमुख्य corresponding to mem_type
 * @mem_type:	tपंचांग memory type
 *
 * Returns corresponding करोमुख्य of the tपंचांग mem_type
 */
अटल अंतरभूत अचिन्हित radeon_mem_type_to_करोमुख्य(u32 mem_type)
अणु
	चयन (mem_type) अणु
	हाल TTM_PL_VRAM:
		वापस RADEON_GEM_DOMAIN_VRAM;
	हाल TTM_PL_TT:
		वापस RADEON_GEM_DOMAIN_GTT;
	हाल TTM_PL_SYSTEM:
		वापस RADEON_GEM_DOMAIN_CPU;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * radeon_bo_reserve - reserve bo
 * @bo:		bo काष्ठाure
 * @no_पूर्णांकr:	करोn't वापस -ERESTARTSYS on pending संकेत
 *
 * Returns:
 * -ERESTARTSYS: A रुको क्रम the buffer to become unreserved was पूर्णांकerrupted by
 * a संकेत. Release all buffer reservations and वापस to user-space.
 */
अटल अंतरभूत पूर्णांक radeon_bo_reserve(काष्ठा radeon_bo *bo, bool no_पूर्णांकr)
अणु
	पूर्णांक r;

	r = tपंचांग_bo_reserve(&bo->tbo, !no_पूर्णांकr, false, शून्य);
	अगर (unlikely(r != 0)) अणु
		अगर (r != -ERESTARTSYS)
			dev_err(bo->rdev->dev, "%p reserve failed\n", bo);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम radeon_bo_unreserve(काष्ठा radeon_bo *bo)
अणु
	tपंचांग_bo_unreserve(&bo->tbo);
पूर्ण

/**
 * radeon_bo_gpu_offset - वापस GPU offset of bo
 * @bo:	radeon object क्रम which we query the offset
 *
 * Returns current GPU offset of the object.
 *
 * Note: object should either be pinned or reserved when calling this
 * function, it might be useful to add check क्रम this क्रम debugging.
 */
अटल अंतरभूत u64 radeon_bo_gpu_offset(काष्ठा radeon_bo *bo)
अणु
	काष्ठा radeon_device *rdev;
	u64 start = 0;

	rdev = radeon_get_rdev(bo->tbo.bdev);

	चयन (bo->tbo.mem.mem_type) अणु
	हाल TTM_PL_TT:
		start = rdev->mc.gtt_start;
		अवरोध;
	हाल TTM_PL_VRAM:
		start = rdev->mc.vram_start;
		अवरोध;
	पूर्ण

	वापस (bo->tbo.mem.start << PAGE_SHIFT) + start;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ radeon_bo_size(काष्ठा radeon_bo *bo)
अणु
	वापस bo->tbo.base.size;
पूर्ण

अटल अंतरभूत अचिन्हित radeon_bo_ngpu_pages(काष्ठा radeon_bo *bo)
अणु
	वापस bo->tbo.base.size / RADEON_GPU_PAGE_SIZE;
पूर्ण

अटल अंतरभूत अचिन्हित radeon_bo_gpu_page_alignment(काष्ठा radeon_bo *bo)
अणु
	वापस (bo->tbo.mem.page_alignment << PAGE_SHIFT) / RADEON_GPU_PAGE_SIZE;
पूर्ण

/**
 * radeon_bo_mmap_offset - वापस mmap offset of bo
 * @bo:	radeon object क्रम which we query the offset
 *
 * Returns mmap offset of the object.
 */
अटल अंतरभूत u64 radeon_bo_mmap_offset(काष्ठा radeon_bo *bo)
अणु
	वापस drm_vma_node_offset_addr(&bo->tbo.base.vma_node);
पूर्ण

बाह्य पूर्णांक radeon_bo_create(काष्ठा radeon_device *rdev,
			    अचिन्हित दीर्घ size, पूर्णांक byte_align,
			    bool kernel, u32 करोमुख्य, u32 flags,
			    काष्ठा sg_table *sg,
			    काष्ठा dma_resv *resv,
			    काष्ठा radeon_bo **bo_ptr);
बाह्य पूर्णांक radeon_bo_kmap(काष्ठा radeon_bo *bo, व्योम **ptr);
बाह्य व्योम radeon_bo_kunmap(काष्ठा radeon_bo *bo);
बाह्य काष्ठा radeon_bo *radeon_bo_ref(काष्ठा radeon_bo *bo);
बाह्य व्योम radeon_bo_unref(काष्ठा radeon_bo **bo);
बाह्य पूर्णांक radeon_bo_pin(काष्ठा radeon_bo *bo, u32 करोमुख्य, u64 *gpu_addr);
बाह्य पूर्णांक radeon_bo_pin_restricted(काष्ठा radeon_bo *bo, u32 करोमुख्य,
				    u64 max_offset, u64 *gpu_addr);
बाह्य व्योम radeon_bo_unpin(काष्ठा radeon_bo *bo);
बाह्य पूर्णांक radeon_bo_evict_vram(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_bo_क्रमce_delete(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक radeon_bo_init(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_bo_fini(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक radeon_bo_list_validate(काष्ठा radeon_device *rdev,
				   काष्ठा ww_acquire_ctx *ticket,
				   काष्ठा list_head *head, पूर्णांक ring);
बाह्य पूर्णांक radeon_bo_set_tiling_flags(काष्ठा radeon_bo *bo,
				u32 tiling_flags, u32 pitch);
बाह्य व्योम radeon_bo_get_tiling_flags(काष्ठा radeon_bo *bo,
				u32 *tiling_flags, u32 *pitch);
बाह्य पूर्णांक radeon_bo_check_tiling(काष्ठा radeon_bo *bo, bool has_moved,
				bool क्रमce_drop);
बाह्य व्योम radeon_bo_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
				  bool evict,
				  काष्ठा tपंचांग_resource *new_mem);
बाह्य vm_fault_t radeon_bo_fault_reserve_notअगरy(काष्ठा tपंचांग_buffer_object *bo);
बाह्य पूर्णांक radeon_bo_get_surface_reg(काष्ठा radeon_bo *bo);
बाह्य व्योम radeon_bo_fence(काष्ठा radeon_bo *bo, काष्ठा radeon_fence *fence,
			    bool shared);

/*
 * sub allocation
 */

अटल अंतरभूत uपूर्णांक64_t radeon_sa_bo_gpu_addr(काष्ठा radeon_sa_bo *sa_bo)
अणु
	वापस sa_bo->manager->gpu_addr + sa_bo->soffset;
पूर्ण

अटल अंतरभूत व्योम * radeon_sa_bo_cpu_addr(काष्ठा radeon_sa_bo *sa_bo)
अणु
	वापस sa_bo->manager->cpu_ptr + sa_bo->soffset;
पूर्ण

बाह्य पूर्णांक radeon_sa_bo_manager_init(काष्ठा radeon_device *rdev,
				     काष्ठा radeon_sa_manager *sa_manager,
				     अचिन्हित size, u32 align, u32 करोमुख्य,
				     u32 flags);
बाह्य व्योम radeon_sa_bo_manager_fini(काष्ठा radeon_device *rdev,
				      काष्ठा radeon_sa_manager *sa_manager);
बाह्य पूर्णांक radeon_sa_bo_manager_start(काष्ठा radeon_device *rdev,
				      काष्ठा radeon_sa_manager *sa_manager);
बाह्य पूर्णांक radeon_sa_bo_manager_suspend(काष्ठा radeon_device *rdev,
					काष्ठा radeon_sa_manager *sa_manager);
बाह्य पूर्णांक radeon_sa_bo_new(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_sa_manager *sa_manager,
			    काष्ठा radeon_sa_bo **sa_bo,
			    अचिन्हित size, अचिन्हित align);
बाह्य व्योम radeon_sa_bo_मुक्त(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_sa_bo **sa_bo,
			      काष्ठा radeon_fence *fence);
#अगर defined(CONFIG_DEBUG_FS)
बाह्य व्योम radeon_sa_bo_dump_debug_info(काष्ठा radeon_sa_manager *sa_manager,
					 काष्ठा seq_file *m);
#पूर्ण_अगर


#पूर्ण_अगर
