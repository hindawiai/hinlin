<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
#अगर_अघोषित __AMDGPU_GMC_H__
#घोषणा __AMDGPU_GMC_H__

#समावेश <linux/types.h>

#समावेश "amdgpu_irq.h"

/* VA hole क्रम 48bit addresses on Vega10 */
#घोषणा AMDGPU_GMC_HOLE_START	0x0000800000000000ULL
#घोषणा AMDGPU_GMC_HOLE_END	0xffff800000000000ULL

/*
 * Hardware is programmed as अगर the hole करोesn't exists with start and end
 * address values.
 *
 * This mask is used to हटाओ the upper 16bits of the VA and so come up with
 * the linear addr value.
 */
#घोषणा AMDGPU_GMC_HOLE_MASK	0x0000ffffffffffffULL

/*
 * Ring size as घातer of two क्रम the log of recent faults.
 */
#घोषणा AMDGPU_GMC_FAULT_RING_ORDER	8
#घोषणा AMDGPU_GMC_FAULT_RING_SIZE	(1 << AMDGPU_GMC_FAULT_RING_ORDER)

/*
 * Hash size as घातer of two क्रम the log of recent faults
 */
#घोषणा AMDGPU_GMC_FAULT_HASH_ORDER	8
#घोषणा AMDGPU_GMC_FAULT_HASH_SIZE	(1 << AMDGPU_GMC_FAULT_HASH_ORDER)

/*
 * Number of IH बारtamp ticks until a fault is considered handled
 */
#घोषणा AMDGPU_GMC_FAULT_TIMEOUT	5000ULL

काष्ठा firmware;

/*
 * GMC page fault inक्रमmation
 */
काष्ठा amdgpu_gmc_fault अणु
	uपूर्णांक64_t	बारtamp;
	uपूर्णांक64_t	next:AMDGPU_GMC_FAULT_RING_ORDER;
	uपूर्णांक64_t	key:52;
पूर्ण;

/*
 * VMHUB काष्ठाures, functions & helpers
 */
काष्ठा amdgpu_vmhub_funcs अणु
	व्योम (*prपूर्णांक_l2_protection_fault_status)(काष्ठा amdgpu_device *adev,
						 uपूर्णांक32_t status);
	uपूर्णांक32_t (*get_invalidate_req)(अचिन्हित पूर्णांक vmid, uपूर्णांक32_t flush_type);
पूर्ण;

काष्ठा amdgpu_vmhub अणु
	uपूर्णांक32_t	ctx0_ptb_addr_lo32;
	uपूर्णांक32_t	ctx0_ptb_addr_hi32;
	uपूर्णांक32_t	vm_inv_eng0_sem;
	uपूर्णांक32_t	vm_inv_eng0_req;
	uपूर्णांक32_t	vm_inv_eng0_ack;
	uपूर्णांक32_t	vm_context0_cntl;
	uपूर्णांक32_t	vm_l2_pro_fault_status;
	uपूर्णांक32_t	vm_l2_pro_fault_cntl;

	/*
	 * store the रेजिस्टर distances between two continuous context करोमुख्य
	 * and invalidation engine.
	 */
	uपूर्णांक32_t	ctx_distance;
	uपूर्णांक32_t	ctx_addr_distance; /* include LO32/HI32 */
	uपूर्णांक32_t	eng_distance;
	uपूर्णांक32_t	eng_addr_distance; /* include LO32/HI32 */

	uपूर्णांक32_t	vm_cntx_cntl_vm_fault;

	स्थिर काष्ठा amdgpu_vmhub_funcs *vmhub_funcs;
पूर्ण;

/*
 * GPU MC काष्ठाures, functions & helpers
 */
काष्ठा amdgpu_gmc_funcs अणु
	/* flush the vm tlb via mmio */
	व्योम (*flush_gpu_tlb)(काष्ठा amdgpu_device *adev, uपूर्णांक32_t vmid,
				uपूर्णांक32_t vmhub, uपूर्णांक32_t flush_type);
	/* flush the vm tlb via pasid */
	पूर्णांक (*flush_gpu_tlb_pasid)(काष्ठा amdgpu_device *adev, uपूर्णांक16_t pasid,
					uपूर्णांक32_t flush_type, bool all_hub);
	/* flush the vm tlb via ring */
	uपूर्णांक64_t (*emit_flush_gpu_tlb)(काष्ठा amdgpu_ring *ring, अचिन्हित vmid,
				       uपूर्णांक64_t pd_addr);
	/* Change the VMID -> PASID mapping */
	व्योम (*emit_pasid_mapping)(काष्ठा amdgpu_ring *ring, अचिन्हित vmid,
				   अचिन्हित pasid);
	/* enable/disable PRT support */
	व्योम (*set_prt)(काष्ठा amdgpu_device *adev, bool enable);
	/* map mtype to hardware flags */
	uपूर्णांक64_t (*map_mtype)(काष्ठा amdgpu_device *adev, uपूर्णांक32_t flags);
	/* get the pde क्रम a given mc addr */
	व्योम (*get_vm_pde)(काष्ठा amdgpu_device *adev, पूर्णांक level,
			   u64 *dst, u64 *flags);
	/* get the pte flags to use क्रम a BO VA mapping */
	व्योम (*get_vm_pte)(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_bo_va_mapping *mapping,
			   uपूर्णांक64_t *flags);
	/* get the amount of memory used by the vbios क्रम pre-OS console */
	अचिन्हित पूर्णांक (*get_vbios_fb_size)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_xgmi_ras_funcs अणु
	पूर्णांक (*ras_late_init)(काष्ठा amdgpu_device *adev);
	व्योम (*ras_fini)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*query_ras_error_count)(काष्ठा amdgpu_device *adev,
				     व्योम *ras_error_status);
	व्योम (*reset_ras_error_count)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_xgmi अणु
	/* from psp */
	u64 node_id;
	u64 hive_id;
	/* fixed per family */
	u64 node_segment_size;
	/* physical node (0-3) */
	अचिन्हित physical_node_id;
	/* number of nodes (0-4) */
	अचिन्हित num_physical_nodes;
	/* gpu list in the same hive */
	काष्ठा list_head head;
	bool supported;
	काष्ठा ras_common_अगर *ras_अगर;
	bool connected_to_cpu;
	bool pending_reset;
	स्थिर काष्ठा amdgpu_xgmi_ras_funcs *ras_funcs;
पूर्ण;

काष्ठा amdgpu_gmc अणु
	/* FB's physical address in MMIO space (क्रम CPU to
	 * map FB). This is dअगरferent compared to the agp/
	 * gart/vram_start/end field as the later is from
	 * GPU's view and aper_base is from CPU's view.
	 */
	resource_माप_प्रकार		aper_size;
	resource_माप_प्रकार		aper_base;
	/* क्रम some chips with <= 32MB we need to lie
	 * about vram size near mc fb location */
	u64			mc_vram_size;
	u64			visible_vram_size;
	/* AGP aperture start and end in MC address space
	 * Driver find a hole in the MC address space
	 * to place AGP by setting MC_VM_AGP_BOT/TOP रेजिस्टरs
	 * Under VMID0, logical address == MC address. AGP
	 * aperture maps to physical bus or IOVA addressed.
	 * AGP aperture is used to simulate FB in ZFB हाल.
	 * AGP aperture is also used क्रम page table in प्रणाली
	 * memory (मुख्यly क्रम APU).
	 *
	 */
	u64			agp_size;
	u64			agp_start;
	u64			agp_end;
	/* GART aperture start and end in MC address space
	 * Driver find a hole in the MC address space
	 * to place GART by setting VM_CONTEXT0_PAGE_TABLE_START/END_ADDR
	 * रेजिस्टरs
	 * Under VMID0, logical address inside GART aperture will
	 * be translated through gpuvm gart page table to access
	 * paged प्रणाली memory
	 */
	u64			gart_size;
	u64			gart_start;
	u64			gart_end;
	/* Frame buffer aperture of this GPU device. Dअगरferent from
	 * fb_start (see below), this only covers the local GPU device.
	 * If driver uses FB aperture to access FB, driver get fb_start from
	 * MC_VM_FB_LOCATION_BASE (set by vbios) and calculate vram_start
	 * of this local device by adding an offset inside the XGMI hive.
	 * If driver uses GART table क्रम VMID0 FB access, driver finds a hole in
	 * VMID0's भव address space to place the SYSVM aperture inside
	 * which the first part is vram and the second part is gart (covering
	 * प्रणाली ram).
	 */
	u64			vram_start;
	u64			vram_end;
	/* FB region , it's same as local vram region in single GPU, in XGMI
	 * configuration, this region covers all GPUs in the same hive ,
	 * each GPU in the hive has the same view of this FB region .
	 * GPU0's vram starts at offset (0 * segment size) ,
	 * GPU1 starts at offset (1 * segment size), etc.
	 */
	u64			fb_start;
	u64			fb_end;
	अचिन्हित		vram_width;
	u64			real_vram_size;
	पूर्णांक			vram_mtrr;
	u64                     mc_mask;
	स्थिर काष्ठा firmware   *fw;	/* MC firmware */
	uपूर्णांक32_t                fw_version;
	काष्ठा amdgpu_irq_src	vm_fault;
	uपूर्णांक32_t		vram_type;
	uपूर्णांक8_t			vram_venकरोr;
	uपूर्णांक32_t                srbm_soft_reset;
	bool			prt_warning;
	uपूर्णांक32_t		sdpअगर_रेजिस्टर;
	/* apertures */
	u64			shared_aperture_start;
	u64			shared_aperture_end;
	u64			निजी_aperture_start;
	u64			निजी_aperture_end;
	/* protects concurrent invalidation */
	spinlock_t		invalidate_lock;
	bool			translate_further;
	काष्ठा kfd_vm_fault_info *vm_fault_info;
	atomic_t		vm_fault_info_updated;

	काष्ठा amdgpu_gmc_fault	fault_ring[AMDGPU_GMC_FAULT_RING_SIZE];
	काष्ठा अणु
		uपूर्णांक64_t	idx:AMDGPU_GMC_FAULT_RING_ORDER;
	पूर्ण fault_hash[AMDGPU_GMC_FAULT_HASH_SIZE];
	uपूर्णांक64_t		last_fault:AMDGPU_GMC_FAULT_RING_ORDER;

	bool पंचांगz_enabled;

	स्थिर काष्ठा amdgpu_gmc_funcs	*gmc_funcs;

	काष्ठा amdgpu_xgmi xgmi;
	काष्ठा amdgpu_irq_src	ecc_irq;
	पूर्णांक noretry;

	uपूर्णांक32_t	vmid0_page_table_block_size;
	uपूर्णांक32_t	vmid0_page_table_depth;
	काष्ठा amdgpu_bo		*pdb0_bo;
	/* CPU kmapped address of pdb0*/
	व्योम				*ptr_pdb0;
पूर्ण;

#घोषणा amdgpu_gmc_flush_gpu_tlb(adev, vmid, vmhub, type) ((adev)->gmc.gmc_funcs->flush_gpu_tlb((adev), (vmid), (vmhub), (type)))
#घोषणा amdgpu_gmc_flush_gpu_tlb_pasid(adev, pasid, type, allhub) \
	((adev)->gmc.gmc_funcs->flush_gpu_tlb_pasid \
	((adev), (pasid), (type), (allhub)))
#घोषणा amdgpu_gmc_emit_flush_gpu_tlb(r, vmid, addr) (r)->adev->gmc.gmc_funcs->emit_flush_gpu_tlb((r), (vmid), (addr))
#घोषणा amdgpu_gmc_emit_pasid_mapping(r, vmid, pasid) (r)->adev->gmc.gmc_funcs->emit_pasid_mapping((r), (vmid), (pasid))
#घोषणा amdgpu_gmc_map_mtype(adev, flags) (adev)->gmc.gmc_funcs->map_mtype((adev),(flags))
#घोषणा amdgpu_gmc_get_vm_pde(adev, level, dst, flags) (adev)->gmc.gmc_funcs->get_vm_pde((adev), (level), (dst), (flags))
#घोषणा amdgpu_gmc_get_vm_pte(adev, mapping, flags) (adev)->gmc.gmc_funcs->get_vm_pte((adev), (mapping), (flags))
#घोषणा amdgpu_gmc_get_vbios_fb_size(adev) (adev)->gmc.gmc_funcs->get_vbios_fb_size((adev))

/**
 * amdgpu_gmc_vram_full_visible - Check अगर full VRAM is visible through the BAR
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Returns:
 * True अगर full VRAM is visible through the BAR
 */
अटल अंतरभूत bool amdgpu_gmc_vram_full_visible(काष्ठा amdgpu_gmc *gmc)
अणु
	WARN_ON(gmc->real_vram_size < gmc->visible_vram_size);

	वापस (gmc->real_vram_size == gmc->visible_vram_size);
पूर्ण

/**
 * amdgpu_gmc_sign_extend - sign extend the given gmc address
 *
 * @addr: address to extend
 */
अटल अंतरभूत uपूर्णांक64_t amdgpu_gmc_sign_extend(uपूर्णांक64_t addr)
अणु
	अगर (addr >= AMDGPU_GMC_HOLE_START)
		addr |= AMDGPU_GMC_HOLE_END;

	वापस addr;
पूर्ण

पूर्णांक amdgpu_gmc_pdb0_alloc(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gmc_get_pde_क्रम_bo(काष्ठा amdgpu_bo *bo, पूर्णांक level,
			       uपूर्णांक64_t *addr, uपूर्णांक64_t *flags);
पूर्णांक amdgpu_gmc_set_pte_pde(काष्ठा amdgpu_device *adev, व्योम *cpu_pt_addr,
				uपूर्णांक32_t gpu_page_idx, uपूर्णांक64_t addr,
				uपूर्णांक64_t flags);
uपूर्णांक64_t amdgpu_gmc_pd_addr(काष्ठा amdgpu_bo *bo);
uपूर्णांक64_t amdgpu_gmc_agp_addr(काष्ठा tपंचांग_buffer_object *bo);
व्योम amdgpu_gmc_sysvm_location(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_gmc *mc);
व्योम amdgpu_gmc_vram_location(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_gmc *mc,
			      u64 base);
व्योम amdgpu_gmc_gart_location(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_gmc *mc);
व्योम amdgpu_gmc_agp_location(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_gmc *mc);
bool amdgpu_gmc_filter_faults(काष्ठा amdgpu_device *adev, uपूर्णांक64_t addr,
			      uपूर्णांक16_t pasid, uपूर्णांक64_t बारtamp);
पूर्णांक amdgpu_gmc_ras_late_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gmc_ras_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gmc_allocate_vm_inv_eng(काष्ठा amdgpu_device *adev);

बाह्य व्योम amdgpu_gmc_पंचांगz_set(काष्ठा amdgpu_device *adev);
बाह्य व्योम amdgpu_gmc_noretry_set(काष्ठा amdgpu_device *adev);

बाह्य व्योम
amdgpu_gmc_set_vm_fault_masks(काष्ठा amdgpu_device *adev, पूर्णांक hub_type,
			      bool enable);

व्योम amdgpu_gmc_get_vbios_allocations(काष्ठा amdgpu_device *adev);

व्योम amdgpu_gmc_init_pdb0(काष्ठा amdgpu_device *adev);
uपूर्णांक64_t amdgpu_gmc_vram_mc2pa(काष्ठा amdgpu_device *adev, uपूर्णांक64_t mc_addr);
uपूर्णांक64_t amdgpu_gmc_vram_pa(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_bo *bo);
uपूर्णांक64_t amdgpu_gmc_vram_cpu_pa(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_bo *bo);
#पूर्ण_अगर
