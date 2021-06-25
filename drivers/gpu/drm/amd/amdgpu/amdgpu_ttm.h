<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित __AMDGPU_TTM_H__
#घोषणा __AMDGPU_TTM_H__

#समावेश <linux/dma-direction.h>
#समावेश <drm/gpu_scheduler.h>
#समावेश "amdgpu.h"

#घोषणा AMDGPU_PL_GDS		(TTM_PL_PRIV + 0)
#घोषणा AMDGPU_PL_GWS		(TTM_PL_PRIV + 1)
#घोषणा AMDGPU_PL_OA		(TTM_PL_PRIV + 2)

#घोषणा AMDGPU_GTT_MAX_TRANSFER_SIZE	512
#घोषणा AMDGPU_GTT_NUM_TRANSFER_WINDOWS	2

#घोषणा AMDGPU_POISON	0xd0bed0be

काष्ठा amdgpu_vram_reservation अणु
	काष्ठा list_head node;
	काष्ठा drm_mm_node mm_node;
पूर्ण;

काष्ठा amdgpu_vram_mgr अणु
	काष्ठा tपंचांग_resource_manager manager;
	काष्ठा drm_mm mm;
	spinlock_t lock;
	काष्ठा list_head reservations_pending;
	काष्ठा list_head reserved_pages;
	atomic64_t usage;
	atomic64_t vis_usage;
पूर्ण;

काष्ठा amdgpu_gtt_mgr अणु
	काष्ठा tपंचांग_resource_manager manager;
	काष्ठा drm_mm mm;
	spinlock_t lock;
	atomic64_t available;
पूर्ण;

काष्ठा amdgpu_mman अणु
	काष्ठा tपंचांग_device		bdev;
	bool				initialized;
	व्योम __iomem			*aper_base_kaddr;

	/* buffer handling */
	स्थिर काष्ठा amdgpu_buffer_funcs	*buffer_funcs;
	काष्ठा amdgpu_ring			*buffer_funcs_ring;
	bool					buffer_funcs_enabled;

	काष्ठा mutex				gtt_winकरोw_lock;
	/* Scheduler entity क्रम buffer moves */
	काष्ठा drm_sched_entity			entity;

	काष्ठा amdgpu_vram_mgr vram_mgr;
	काष्ठा amdgpu_gtt_mgr gtt_mgr;

	uपूर्णांक64_t		stolen_vga_size;
	काष्ठा amdgpu_bo	*stolen_vga_memory;
	uपूर्णांक64_t		stolen_extended_size;
	काष्ठा amdgpu_bo	*stolen_extended_memory;
	bool			keep_stolen_vga_memory;

	/* discovery */
	uपूर्णांक8_t				*discovery_bin;
	uपूर्णांक32_t			discovery_पंचांगr_size;
	काष्ठा amdgpu_bo		*discovery_memory;

	/* firmware VRAM reservation */
	u64		fw_vram_usage_start_offset;
	u64		fw_vram_usage_size;
	काष्ठा amdgpu_bo	*fw_vram_usage_reserved_bo;
	व्योम		*fw_vram_usage_va;
पूर्ण;

काष्ठा amdgpu_copy_mem अणु
	काष्ठा tपंचांग_buffer_object	*bo;
	काष्ठा tपंचांग_resource		*mem;
	अचिन्हित दीर्घ			offset;
पूर्ण;

पूर्णांक amdgpu_gtt_mgr_init(काष्ठा amdgpu_device *adev, uपूर्णांक64_t gtt_size);
व्योम amdgpu_gtt_mgr_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_vram_mgr_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_vram_mgr_fini(काष्ठा amdgpu_device *adev);

bool amdgpu_gtt_mgr_has_gart_addr(काष्ठा tपंचांग_resource *mem);
uपूर्णांक64_t amdgpu_gtt_mgr_usage(काष्ठा tपंचांग_resource_manager *man);
पूर्णांक amdgpu_gtt_mgr_recover(काष्ठा tपंचांग_resource_manager *man);

u64 amdgpu_vram_mgr_bo_visible_size(काष्ठा amdgpu_bo *bo);
पूर्णांक amdgpu_vram_mgr_alloc_sgt(काष्ठा amdgpu_device *adev,
			      काष्ठा tपंचांग_resource *mem,
			      u64 offset, u64 size,
			      काष्ठा device *dev,
			      क्रमागत dma_data_direction dir,
			      काष्ठा sg_table **sgt);
व्योम amdgpu_vram_mgr_मुक्त_sgt(काष्ठा device *dev,
			      क्रमागत dma_data_direction dir,
			      काष्ठा sg_table *sgt);
uपूर्णांक64_t amdgpu_vram_mgr_usage(काष्ठा tपंचांग_resource_manager *man);
uपूर्णांक64_t amdgpu_vram_mgr_vis_usage(काष्ठा tपंचांग_resource_manager *man);
पूर्णांक amdgpu_vram_mgr_reserve_range(काष्ठा tपंचांग_resource_manager *man,
				  uपूर्णांक64_t start, uपूर्णांक64_t size);
पूर्णांक amdgpu_vram_mgr_query_page_status(काष्ठा tपंचांग_resource_manager *man,
				      uपूर्णांक64_t start);

पूर्णांक amdgpu_tपंचांग_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_tपंचांग_fini(काष्ठा amdgpu_device *adev);
व्योम amdgpu_tपंचांग_set_buffer_funcs_status(काष्ठा amdgpu_device *adev,
					bool enable);

पूर्णांक amdgpu_copy_buffer(काष्ठा amdgpu_ring *ring, uपूर्णांक64_t src_offset,
		       uपूर्णांक64_t dst_offset, uपूर्णांक32_t byte_count,
		       काष्ठा dma_resv *resv,
		       काष्ठा dma_fence **fence, bool direct_submit,
		       bool vm_needs_flush, bool पंचांगz);
पूर्णांक amdgpu_tपंचांग_copy_mem_to_mem(काष्ठा amdgpu_device *adev,
			       स्थिर काष्ठा amdgpu_copy_mem *src,
			       स्थिर काष्ठा amdgpu_copy_mem *dst,
			       uपूर्णांक64_t size, bool पंचांगz,
			       काष्ठा dma_resv *resv,
			       काष्ठा dma_fence **f);
पूर्णांक amdgpu_fill_buffer(काष्ठा amdgpu_bo *bo,
			uपूर्णांक32_t src_data,
			काष्ठा dma_resv *resv,
			काष्ठा dma_fence **fence);

पूर्णांक amdgpu_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक amdgpu_tपंचांग_alloc_gart(काष्ठा tपंचांग_buffer_object *bo);
पूर्णांक amdgpu_tपंचांग_recover_gart(काष्ठा tपंचांग_buffer_object *tbo);
uपूर्णांक64_t amdgpu_tपंचांग_करोमुख्य_start(काष्ठा amdgpu_device *adev, uपूर्णांक32_t type);

#अगर IS_ENABLED(CONFIG_DRM_AMDGPU_USERPTR)
पूर्णांक amdgpu_tपंचांग_tt_get_user_pages(काष्ठा amdgpu_bo *bo, काष्ठा page **pages);
bool amdgpu_tपंचांग_tt_get_user_pages_करोne(काष्ठा tपंचांग_tt *tपंचांग);
#अन्यथा
अटल अंतरभूत पूर्णांक amdgpu_tपंचांग_tt_get_user_pages(काष्ठा amdgpu_bo *bo,
					       काष्ठा page **pages)
अणु
	वापस -EPERM;
पूर्ण
अटल अंतरभूत bool amdgpu_tपंचांग_tt_get_user_pages_करोne(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

व्योम amdgpu_tपंचांग_tt_set_user_pages(काष्ठा tपंचांग_tt *tपंचांग, काष्ठा page **pages);
पूर्णांक amdgpu_tपंचांग_tt_set_userptr(काष्ठा tपंचांग_buffer_object *bo,
			      uपूर्णांक64_t addr, uपूर्णांक32_t flags);
bool amdgpu_tपंचांग_tt_has_userptr(काष्ठा tपंचांग_tt *tपंचांग);
काष्ठा mm_काष्ठा *amdgpu_tपंचांग_tt_get_usermm(काष्ठा tपंचांग_tt *tपंचांग);
bool amdgpu_tपंचांग_tt_affect_userptr(काष्ठा tपंचांग_tt *tपंचांग, अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ end);
bool amdgpu_tपंचांग_tt_userptr_invalidated(काष्ठा tपंचांग_tt *tपंचांग,
				       पूर्णांक *last_invalidated);
bool amdgpu_tपंचांग_tt_is_userptr(काष्ठा tपंचांग_tt *tपंचांग);
bool amdgpu_tपंचांग_tt_is_पढ़ोonly(काष्ठा tपंचांग_tt *tपंचांग);
uपूर्णांक64_t amdgpu_tपंचांग_tt_pde_flags(काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_resource *mem);
uपूर्णांक64_t amdgpu_tपंचांग_tt_pte_flags(काष्ठा amdgpu_device *adev, काष्ठा tपंचांग_tt *tपंचांग,
				 काष्ठा tपंचांग_resource *mem);

व्योम amdgpu_tपंचांग_debugfs_init(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर
