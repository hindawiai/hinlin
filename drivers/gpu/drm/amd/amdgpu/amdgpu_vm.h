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
 * Authors: Christian Kथघnig
 */
#अगर_अघोषित __AMDGPU_VM_H__
#घोषणा __AMDGPU_VM_H__

#समावेश <linux/idr.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/rbtree.h>
#समावेश <drm/gpu_scheduler.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <linux/sched/mm.h>

#समावेश "amdgpu_sync.h"
#समावेश "amdgpu_ring.h"
#समावेश "amdgpu_ids.h"

काष्ठा amdgpu_bo_va;
काष्ठा amdgpu_job;
काष्ठा amdgpu_bo_list_entry;

/*
 * GPUVM handling
 */

/* Maximum number of PTEs the hardware can ग_लिखो with one command */
#घोषणा AMDGPU_VM_MAX_UPDATE_SIZE	0x3FFFF

/* number of entries in page table */
#घोषणा AMDGPU_VM_PTE_COUNT(adev) (1 << (adev)->vm_manager.block_size)

#घोषणा AMDGPU_PTE_VALID	(1ULL << 0)
#घोषणा AMDGPU_PTE_SYSTEM	(1ULL << 1)
#घोषणा AMDGPU_PTE_SNOOPED	(1ULL << 2)

/* RV+ */
#घोषणा AMDGPU_PTE_TMZ		(1ULL << 3)

/* VI only */
#घोषणा AMDGPU_PTE_EXECUTABLE	(1ULL << 4)

#घोषणा AMDGPU_PTE_READABLE	(1ULL << 5)
#घोषणा AMDGPU_PTE_WRITEABLE	(1ULL << 6)

#घोषणा AMDGPU_PTE_FRAG(x)	((x & 0x1fULL) << 7)

/* TILED क्रम VEGA10, reserved क्रम older ASICs  */
#घोषणा AMDGPU_PTE_PRT		(1ULL << 51)

/* PDE is handled as PTE क्रम VEGA10 */
#घोषणा AMDGPU_PDE_PTE		(1ULL << 54)

#घोषणा AMDGPU_PTE_LOG          (1ULL << 55)

/* PTE is handled as PDE क्रम VEGA10 (Translate Further) */
#घोषणा AMDGPU_PTE_TF		(1ULL << 56)

/* MALL noalloc क्रम sienna_cichlid, reserved क्रम older ASICs  */
#घोषणा AMDGPU_PTE_NOALLOC	(1ULL << 58)

/* PDE Block Fragment Size क्रम VEGA10 */
#घोषणा AMDGPU_PDE_BFS(a)	((uपूर्णांक64_t)a << 59)


/* For GFX9 */
#घोषणा AMDGPU_PTE_MTYPE_VG10(a)	((uपूर्णांक64_t)(a) << 57)
#घोषणा AMDGPU_PTE_MTYPE_VG10_MASK	AMDGPU_PTE_MTYPE_VG10(3ULL)

#घोषणा AMDGPU_MTYPE_NC 0
#घोषणा AMDGPU_MTYPE_CC 2

#घोषणा AMDGPU_PTE_DEFAULT_ATC  (AMDGPU_PTE_SYSTEM      \
                                | AMDGPU_PTE_SNOOPED    \
                                | AMDGPU_PTE_EXECUTABLE \
                                | AMDGPU_PTE_READABLE   \
                                | AMDGPU_PTE_WRITEABLE  \
                                | AMDGPU_PTE_MTYPE_VG10(AMDGPU_MTYPE_CC))

/* gfx10 */
#घोषणा AMDGPU_PTE_MTYPE_NV10(a)       ((uपूर्णांक64_t)(a) << 48)
#घोषणा AMDGPU_PTE_MTYPE_NV10_MASK     AMDGPU_PTE_MTYPE_NV10(7ULL)

/* How to program VM fault handling */
#घोषणा AMDGPU_VM_FAULT_STOP_NEVER	0
#घोषणा AMDGPU_VM_FAULT_STOP_FIRST	1
#घोषणा AMDGPU_VM_FAULT_STOP_ALWAYS	2

/* Reserve 4MB VRAM क्रम page tables */
#घोषणा AMDGPU_VM_RESERVED_VRAM		(8ULL << 20)

/* max number of VMHUB */
#घोषणा AMDGPU_MAX_VMHUBS			3
#घोषणा AMDGPU_GFXHUB_0				0
#घोषणा AMDGPU_MMHUB_0				1
#घोषणा AMDGPU_MMHUB_1				2

/* Reserve 2MB at top/bottom of address space क्रम kernel use */
#घोषणा AMDGPU_VA_RESERVED_SIZE			(2ULL << 20)

/* max vmids dedicated क्रम process */
#घोषणा AMDGPU_VM_MAX_RESERVED_VMID	1

#घोषणा AMDGPU_VM_CONTEXT_GFX 0
#घोषणा AMDGPU_VM_CONTEXT_COMPUTE 1

/* See vm_update_mode */
#घोषणा AMDGPU_VM_USE_CPU_FOR_GFX (1 << 0)
#घोषणा AMDGPU_VM_USE_CPU_FOR_COMPUTE (1 << 1)

/* VMPT level क्रमागतerate, and the hiberachy is:
 * PDB2->PDB1->PDB0->PTB
 */
क्रमागत amdgpu_vm_level अणु
	AMDGPU_VM_PDB2,
	AMDGPU_VM_PDB1,
	AMDGPU_VM_PDB0,
	AMDGPU_VM_PTB
पूर्ण;

/* base काष्ठाure क्रम tracking BO usage in a VM */
काष्ठा amdgpu_vm_bo_base अणु
	/* स्थिरant after initialization */
	काष्ठा amdgpu_vm		*vm;
	काष्ठा amdgpu_bo		*bo;

	/* रक्षित by bo being reserved */
	काष्ठा amdgpu_vm_bo_base	*next;

	/* रक्षित by spinlock */
	काष्ठा list_head		vm_status;

	/* रक्षित by the BO being reserved */
	bool				moved;
पूर्ण;

काष्ठा amdgpu_vm_pt अणु
	काष्ठा amdgpu_vm_bo_base	base;

	/* array of page tables, one क्रम each directory entry */
	काष्ठा amdgpu_vm_pt		*entries;
पूर्ण;

/* provided by hw blocks that can ग_लिखो ptes, e.g., sdma */
काष्ठा amdgpu_vm_pte_funcs अणु
	/* number of dw to reserve per operation */
	अचिन्हित	copy_pte_num_dw;

	/* copy pte entries from GART */
	व्योम (*copy_pte)(काष्ठा amdgpu_ib *ib,
			 uपूर्णांक64_t pe, uपूर्णांक64_t src,
			 अचिन्हित count);

	/* ग_लिखो pte one entry at a समय with addr mapping */
	व्योम (*ग_लिखो_pte)(काष्ठा amdgpu_ib *ib, uपूर्णांक64_t pe,
			  uपूर्णांक64_t value, अचिन्हित count,
			  uपूर्णांक32_t incr);
	/* क्रम linear pte/pde updates without addr mapping */
	व्योम (*set_pte_pde)(काष्ठा amdgpu_ib *ib,
			    uपूर्णांक64_t pe,
			    uपूर्णांक64_t addr, अचिन्हित count,
			    uपूर्णांक32_t incr, uपूर्णांक64_t flags);
पूर्ण;

काष्ठा amdgpu_task_info अणु
	अक्षर	process_name[TASK_COMM_LEN];
	अक्षर	task_name[TASK_COMM_LEN];
	pid_t	pid;
	pid_t	tgid;
पूर्ण;

/**
 * काष्ठा amdgpu_vm_update_params
 *
 * Encapsulate some VM table update parameters to reduce
 * the number of function parameters
 *
 */
काष्ठा amdgpu_vm_update_params अणु

	/**
	 * @adev: amdgpu device we करो this update क्रम
	 */
	काष्ठा amdgpu_device *adev;

	/**
	 * @vm: optional amdgpu_vm we करो this update क्रम
	 */
	काष्ठा amdgpu_vm *vm;

	/**
	 * @immediate: अगर changes should be made immediately
	 */
	bool immediate;

	/**
	 * @unlocked: true अगर the root BO is not locked
	 */
	bool unlocked;

	/**
	 * @pages_addr:
	 *
	 * DMA addresses to use क्रम mapping
	 */
	dma_addr_t *pages_addr;

	/**
	 * @job: job to used क्रम hw submission
	 */
	काष्ठा amdgpu_job *job;

	/**
	 * @num_dw_left: number of dw left क्रम the IB
	 */
	अचिन्हित पूर्णांक num_dw_left;
पूर्ण;

काष्ठा amdgpu_vm_update_funcs अणु
	पूर्णांक (*map_table)(काष्ठा amdgpu_bo *bo);
	पूर्णांक (*prepare)(काष्ठा amdgpu_vm_update_params *p, काष्ठा dma_resv *resv,
		       क्रमागत amdgpu_sync_mode sync_mode);
	पूर्णांक (*update)(काष्ठा amdgpu_vm_update_params *p,
		      काष्ठा amdgpu_bo *bo, uपूर्णांक64_t pe, uपूर्णांक64_t addr,
		      अचिन्हित count, uपूर्णांक32_t incr, uपूर्णांक64_t flags);
	पूर्णांक (*commit)(काष्ठा amdgpu_vm_update_params *p,
		      काष्ठा dma_fence **fence);
पूर्ण;

काष्ठा amdgpu_vm अणु
	/* tree of भव addresses mapped */
	काष्ठा rb_root_cached	va;

	/* Lock to prevent eviction जबतक we are updating page tables
	 * use vm_eviction_lock/unlock(vm)
	 */
	काष्ठा mutex		eviction_lock;
	bool			evicting;
	अचिन्हित पूर्णांक		saved_flags;

	/* BOs who needs a validation */
	काष्ठा list_head	evicted;

	/* PT BOs which relocated and their parent need an update */
	काष्ठा list_head	relocated;

	/* per VM BOs moved, but not yet updated in the PT */
	काष्ठा list_head	moved;

	/* All BOs of this VM not currently in the state machine */
	काष्ठा list_head	idle;

	/* regular invalidated BOs, but not yet updated in the PT */
	काष्ठा list_head	invalidated;
	spinlock_t		invalidated_lock;

	/* BO mappings मुक्तd, but not yet updated in the PT */
	काष्ठा list_head	मुक्तd;

	/* BOs which are invalidated, has been updated in the PTs */
	काष्ठा list_head        करोne;

	/* contains the page directory */
	काष्ठा amdgpu_vm_pt     root;
	काष्ठा dma_fence	*last_update;

	/* Scheduler entities क्रम page table updates */
	काष्ठा drm_sched_entity	immediate;
	काष्ठा drm_sched_entity	delayed;

	/* Last unlocked submission to the scheduler entities */
	काष्ठा dma_fence	*last_unlocked;

	अचिन्हित पूर्णांक		pasid;
	/* dedicated to vm */
	काष्ठा amdgpu_vmid	*reserved_vmid[AMDGPU_MAX_VMHUBS];

	/* Flag to indicate अगर VM tables are updated by CPU or GPU (SDMA) */
	bool					use_cpu_क्रम_update;

	/* Functions to use क्रम VM table updates */
	स्थिर काष्ठा amdgpu_vm_update_funcs	*update_funcs;

	/* Flag to indicate ATS support from PTE क्रम GFX9 */
	bool			pte_support_ats;

	/* Up to 128 pending retry page faults */
	DECLARE_KFIFO(faults, u64, 128);

	/* Poपूर्णांकs to the KFD process VM info */
	काष्ठा amdkfd_process_info *process_info;

	/* List node in amdkfd_process_info.vm_list_head */
	काष्ठा list_head	vm_list_node;

	/* Valid जबतक the PD is reserved or fenced */
	uपूर्णांक64_t		pd_phys_addr;

	/* Some basic info about the task */
	काष्ठा amdgpu_task_info task_info;

	/* Store positions of group of BOs */
	काष्ठा tपंचांग_lru_bulk_move lru_bulk_move;
	/* mark whether can करो the bulk move */
	bool			bulk_moveable;
	/* Flag to indicate अगर VM is used क्रम compute */
	bool			is_compute_context;
पूर्ण;

काष्ठा amdgpu_vm_manager अणु
	/* Handling of VMIDs */
	काष्ठा amdgpu_vmid_mgr			id_mgr[AMDGPU_MAX_VMHUBS];
	अचिन्हित पूर्णांक				first_kfd_vmid;
	bool					concurrent_flush;

	/* Handling of VM fences */
	u64					fence_context;
	अचिन्हित				seqno[AMDGPU_MAX_RINGS];

	uपूर्णांक64_t				max_pfn;
	uपूर्णांक32_t				num_level;
	uपूर्णांक32_t				block_size;
	uपूर्णांक32_t				fragment_size;
	क्रमागत amdgpu_vm_level			root_level;
	/* vram base address क्रम page table entry  */
	u64					vram_base_offset;
	/* vm pte handling */
	स्थिर काष्ठा amdgpu_vm_pte_funcs	*vm_pte_funcs;
	काष्ठा drm_gpu_scheduler		*vm_pte_scheds[AMDGPU_MAX_RINGS];
	अचिन्हित				vm_pte_num_scheds;
	काष्ठा amdgpu_ring			*page_fault;

	/* partial resident texture handling */
	spinlock_t				prt_lock;
	atomic_t				num_prt_users;

	/* controls how VM page tables are updated क्रम Graphics and Compute.
	 * BIT0[= 0] Graphics updated by SDMA [= 1] by CPU
	 * BIT1[= 0] Compute updated by SDMA [= 1] by CPU
	 */
	पूर्णांक					vm_update_mode;

	/* PASID to VM mapping, will be used in पूर्णांकerrupt context to
	 * look up VM of a page fault
	 */
	काष्ठा idr				pasid_idr;
	spinlock_t				pasid_lock;
पूर्ण;

#घोषणा amdgpu_vm_copy_pte(adev, ib, pe, src, count) ((adev)->vm_manager.vm_pte_funcs->copy_pte((ib), (pe), (src), (count)))
#घोषणा amdgpu_vm_ग_लिखो_pte(adev, ib, pe, value, count, incr) ((adev)->vm_manager.vm_pte_funcs->ग_लिखो_pte((ib), (pe), (value), (count), (incr)))
#घोषणा amdgpu_vm_set_pte_pde(adev, ib, pe, addr, count, incr, flags) ((adev)->vm_manager.vm_pte_funcs->set_pte_pde((ib), (pe), (addr), (count), (incr), (flags)))

बाह्य स्थिर काष्ठा amdgpu_vm_update_funcs amdgpu_vm_cpu_funcs;
बाह्य स्थिर काष्ठा amdgpu_vm_update_funcs amdgpu_vm_sdma_funcs;

व्योम amdgpu_vm_manager_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_vm_manager_fini(काष्ठा amdgpu_device *adev);

दीर्घ amdgpu_vm_रुको_idle(काष्ठा amdgpu_vm *vm, दीर्घ समयout);
पूर्णांक amdgpu_vm_init(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
		   पूर्णांक vm_context, u32 pasid);
पूर्णांक amdgpu_vm_make_compute(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm, u32 pasid);
व्योम amdgpu_vm_release_compute(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm);
व्योम amdgpu_vm_fini(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm);
व्योम amdgpu_vm_get_pd_bo(काष्ठा amdgpu_vm *vm,
			 काष्ठा list_head *validated,
			 काष्ठा amdgpu_bo_list_entry *entry);
bool amdgpu_vm_पढ़ोy(काष्ठा amdgpu_vm *vm);
पूर्णांक amdgpu_vm_validate_pt_bos(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
			      पूर्णांक (*callback)(व्योम *p, काष्ठा amdgpu_bo *bo),
			      व्योम *param);
पूर्णांक amdgpu_vm_flush(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_job *job, bool need_pipe_sync);
पूर्णांक amdgpu_vm_update_pdes(काष्ठा amdgpu_device *adev,
			  काष्ठा amdgpu_vm *vm, bool immediate);
पूर्णांक amdgpu_vm_clear_मुक्तd(काष्ठा amdgpu_device *adev,
			  काष्ठा amdgpu_vm *vm,
			  काष्ठा dma_fence **fence);
पूर्णांक amdgpu_vm_handle_moved(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_vm *vm);
पूर्णांक amdgpu_vm_bo_update(काष्ठा amdgpu_device *adev,
			काष्ठा amdgpu_bo_va *bo_va,
			bool clear);
bool amdgpu_vm_evictable(काष्ठा amdgpu_bo *bo);
व्योम amdgpu_vm_bo_invalidate(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_bo *bo, bool evicted);
uपूर्णांक64_t amdgpu_vm_map_gart(स्थिर dma_addr_t *pages_addr, uपूर्णांक64_t addr);
काष्ठा amdgpu_bo_va *amdgpu_vm_bo_find(काष्ठा amdgpu_vm *vm,
				       काष्ठा amdgpu_bo *bo);
काष्ठा amdgpu_bo_va *amdgpu_vm_bo_add(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_vm *vm,
				      काष्ठा amdgpu_bo *bo);
पूर्णांक amdgpu_vm_bo_map(काष्ठा amdgpu_device *adev,
		     काष्ठा amdgpu_bo_va *bo_va,
		     uपूर्णांक64_t addr, uपूर्णांक64_t offset,
		     uपूर्णांक64_t size, uपूर्णांक64_t flags);
पूर्णांक amdgpu_vm_bo_replace_map(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_bo_va *bo_va,
			     uपूर्णांक64_t addr, uपूर्णांक64_t offset,
			     uपूर्णांक64_t size, uपूर्णांक64_t flags);
पूर्णांक amdgpu_vm_bo_unmap(काष्ठा amdgpu_device *adev,
		       काष्ठा amdgpu_bo_va *bo_va,
		       uपूर्णांक64_t addr);
पूर्णांक amdgpu_vm_bo_clear_mappings(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_vm *vm,
				uपूर्णांक64_t saddr, uपूर्णांक64_t size);
काष्ठा amdgpu_bo_va_mapping *amdgpu_vm_bo_lookup_mapping(काष्ठा amdgpu_vm *vm,
							 uपूर्णांक64_t addr);
व्योम amdgpu_vm_bo_trace_cs(काष्ठा amdgpu_vm *vm, काष्ठा ww_acquire_ctx *ticket);
व्योम amdgpu_vm_bo_rmv(काष्ठा amdgpu_device *adev,
		      काष्ठा amdgpu_bo_va *bo_va);
व्योम amdgpu_vm_adjust_size(काष्ठा amdgpu_device *adev, uपूर्णांक32_t min_vm_size,
			   uपूर्णांक32_t fragment_size_शेष, अचिन्हित max_level,
			   अचिन्हित max_bits);
पूर्णांक amdgpu_vm_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp);
bool amdgpu_vm_need_pipeline_sync(काष्ठा amdgpu_ring *ring,
				  काष्ठा amdgpu_job *job);
व्योम amdgpu_vm_check_compute_bug(काष्ठा amdgpu_device *adev);

व्योम amdgpu_vm_get_task_info(काष्ठा amdgpu_device *adev, u32 pasid,
			     काष्ठा amdgpu_task_info *task_info);
bool amdgpu_vm_handle_fault(काष्ठा amdgpu_device *adev, u32 pasid,
			    uपूर्णांक64_t addr);

व्योम amdgpu_vm_set_task_info(काष्ठा amdgpu_vm *vm);

व्योम amdgpu_vm_move_to_lru_tail(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_vm *vm);
व्योम amdgpu_vm_del_from_lru_notअगरy(काष्ठा tपंचांग_buffer_object *bo);

#अगर defined(CONFIG_DEBUG_FS)
व्योम amdgpu_debugfs_vm_bo_info(काष्ठा amdgpu_vm *vm, काष्ठा seq_file *m);
#पूर्ण_अगर

#पूर्ण_अगर
