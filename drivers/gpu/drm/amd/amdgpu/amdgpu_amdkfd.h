<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 */

/* amdgpu_amdkfd.h defines the निजी पूर्णांकerface between amdgpu and amdkfd. */

#अगर_अघोषित AMDGPU_AMDKFD_H_INCLUDED
#घोषणा AMDGPU_AMDKFD_H_INCLUDED

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/workqueue.h>
#समावेश <kgd_kfd_पूर्णांकerface.h>
#समावेश <drm/tपंचांग/tपंचांग_execbuf_util.h>
#समावेश "amdgpu_sync.h"
#समावेश "amdgpu_vm.h"

बाह्य uपूर्णांक64_t amdgpu_amdkfd_total_mem_size;

काष्ठा amdgpu_device;

काष्ठा kfd_bo_बहु_सूची अणु
	काष्ठा list_head bo_list;
	काष्ठा amdgpu_bo_va *bo_va;
	व्योम *kgd_dev;
	bool is_mapped;
	uपूर्णांक64_t va;
	uपूर्णांक64_t pte_flags;
पूर्ण;

काष्ठा kgd_mem अणु
	काष्ठा mutex lock;
	काष्ठा amdgpu_bo *bo;
	काष्ठा list_head bo_बहु_सूची;
	/* रक्षित by amdkfd_process_info.lock */
	काष्ठा tपंचांग_validate_buffer validate_list;
	काष्ठा tपंचांग_validate_buffer resv_list;
	uपूर्णांक32_t करोमुख्य;
	अचिन्हित पूर्णांक mapped_to_gpu_memory;
	uपूर्णांक64_t va;

	uपूर्णांक32_t alloc_flags;

	atomic_t invalid;
	काष्ठा amdkfd_process_info *process_info;

	काष्ठा amdgpu_sync sync;

	bool aql_queue;
	bool is_imported;
पूर्ण;

/* KFD Memory Eviction */
काष्ठा amdgpu_amdkfd_fence अणु
	काष्ठा dma_fence base;
	काष्ठा mm_काष्ठा *mm;
	spinlock_t lock;
	अक्षर समयline_name[TASK_COMM_LEN];
पूर्ण;

काष्ठा amdgpu_kfd_dev अणु
	काष्ठा kfd_dev *dev;
	uपूर्णांक64_t vram_used;
	bool init_complete;
पूर्ण;

क्रमागत kgd_engine_type अणु
	KGD_ENGINE_PFP = 1,
	KGD_ENGINE_ME,
	KGD_ENGINE_CE,
	KGD_ENGINE_MEC1,
	KGD_ENGINE_MEC2,
	KGD_ENGINE_RLC,
	KGD_ENGINE_SDMA1,
	KGD_ENGINE_SDMA2,
	KGD_ENGINE_MAX
पूर्ण;


काष्ठा amdkfd_process_info अणु
	/* List head of all VMs that beदीर्घ to a KFD process */
	काष्ठा list_head vm_list_head;
	/* List head क्रम all KFD BOs that beदीर्घ to a KFD process. */
	काष्ठा list_head kfd_bo_list;
	/* List of userptr BOs that are valid or invalid */
	काष्ठा list_head userptr_valid_list;
	काष्ठा list_head userptr_inval_list;
	/* Lock to protect kfd_bo_list */
	काष्ठा mutex lock;

	/* Number of VMs */
	अचिन्हित पूर्णांक n_vms;
	/* Eviction Fence */
	काष्ठा amdgpu_amdkfd_fence *eviction_fence;

	/* MMU-notअगरier related fields */
	atomic_t evicted_bos;
	काष्ठा delayed_work restore_userptr_work;
	काष्ठा pid *pid;
पूर्ण;

पूर्णांक amdgpu_amdkfd_init(व्योम);
व्योम amdgpu_amdkfd_fini(व्योम);

व्योम amdgpu_amdkfd_suspend(काष्ठा amdgpu_device *adev, bool run_pm);
पूर्णांक amdgpu_amdkfd_resume(काष्ठा amdgpu_device *adev, bool run_pm);
व्योम amdgpu_amdkfd_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
			स्थिर व्योम *ih_ring_entry);
व्योम amdgpu_amdkfd_device_probe(काष्ठा amdgpu_device *adev);
व्योम amdgpu_amdkfd_device_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_amdkfd_device_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_amdkfd_submit_ib(काष्ठा kgd_dev *kgd, क्रमागत kgd_engine_type engine,
				uपूर्णांक32_t vmid, uपूर्णांक64_t gpu_addr,
				uपूर्णांक32_t *ib_cmd, uपूर्णांक32_t ib_len);
व्योम amdgpu_amdkfd_set_compute_idle(काष्ठा kgd_dev *kgd, bool idle);
bool amdgpu_amdkfd_have_atomics_support(काष्ठा kgd_dev *kgd);
पूर्णांक amdgpu_amdkfd_flush_gpu_tlb_vmid(काष्ठा kgd_dev *kgd, uपूर्णांक16_t vmid);
पूर्णांक amdgpu_amdkfd_flush_gpu_tlb_pasid(काष्ठा kgd_dev *kgd, uपूर्णांक16_t pasid);

bool amdgpu_amdkfd_is_kfd_vmid(काष्ठा amdgpu_device *adev, u32 vmid);

पूर्णांक amdgpu_amdkfd_pre_reset(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_amdkfd_post_reset(काष्ठा amdgpu_device *adev);

व्योम amdgpu_amdkfd_gpu_reset(काष्ठा kgd_dev *kgd);

पूर्णांक amdgpu_queue_mask_bit_to_set_resource_bit(काष्ठा amdgpu_device *adev,
					पूर्णांक queue_bit);

काष्ठा amdgpu_amdkfd_fence *amdgpu_amdkfd_fence_create(u64 context,
								काष्ठा mm_काष्ठा *mm);
#अगर IS_ENABLED(CONFIG_HSA_AMD)
bool amdkfd_fence_check_mm(काष्ठा dma_fence *f, काष्ठा mm_काष्ठा *mm);
काष्ठा amdgpu_amdkfd_fence *to_amdgpu_amdkfd_fence(काष्ठा dma_fence *f);
पूर्णांक amdgpu_amdkfd_हटाओ_fence_on_pt_pd_bos(काष्ठा amdgpu_bo *bo);
पूर्णांक amdgpu_amdkfd_evict_userptr(काष्ठा kgd_mem *mem, काष्ठा mm_काष्ठा *mm);
#अन्यथा
अटल अंतरभूत
bool amdkfd_fence_check_mm(काष्ठा dma_fence *f, काष्ठा mm_काष्ठा *mm)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत
काष्ठा amdgpu_amdkfd_fence *to_amdgpu_amdkfd_fence(काष्ठा dma_fence *f)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
पूर्णांक amdgpu_amdkfd_हटाओ_fence_on_pt_pd_bos(काष्ठा amdgpu_bo *bo)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक amdgpu_amdkfd_evict_userptr(काष्ठा kgd_mem *mem, काष्ठा mm_काष्ठा *mm)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
/* Shared API */
पूर्णांक amdgpu_amdkfd_alloc_gtt_mem(काष्ठा kgd_dev *kgd, माप_प्रकार size,
				व्योम **mem_obj, uपूर्णांक64_t *gpu_addr,
				व्योम **cpu_ptr, bool mqd_gfx9);
व्योम amdgpu_amdkfd_मुक्त_gtt_mem(काष्ठा kgd_dev *kgd, व्योम *mem_obj);
पूर्णांक amdgpu_amdkfd_alloc_gws(काष्ठा kgd_dev *kgd, माप_प्रकार size, व्योम **mem_obj);
व्योम amdgpu_amdkfd_मुक्त_gws(काष्ठा kgd_dev *kgd, व्योम *mem_obj);
पूर्णांक amdgpu_amdkfd_add_gws_to_process(व्योम *info, व्योम *gws, काष्ठा kgd_mem **mem);
पूर्णांक amdgpu_amdkfd_हटाओ_gws_from_process(व्योम *info, व्योम *mem);
uपूर्णांक32_t amdgpu_amdkfd_get_fw_version(काष्ठा kgd_dev *kgd,
				      क्रमागत kgd_engine_type type);
व्योम amdgpu_amdkfd_get_local_mem_info(काष्ठा kgd_dev *kgd,
				      काष्ठा kfd_local_mem_info *mem_info);
uपूर्णांक64_t amdgpu_amdkfd_get_gpu_घड़ी_counter(काष्ठा kgd_dev *kgd);

uपूर्णांक32_t amdgpu_amdkfd_get_max_engine_घड़ी_in_mhz(काष्ठा kgd_dev *kgd);
व्योम amdgpu_amdkfd_get_cu_info(काष्ठा kgd_dev *kgd, काष्ठा kfd_cu_info *cu_info);
पूर्णांक amdgpu_amdkfd_get_dmabuf_info(काष्ठा kgd_dev *kgd, पूर्णांक dma_buf_fd,
				  काष्ठा kgd_dev **dmabuf_kgd,
				  uपूर्णांक64_t *bo_size, व्योम *metadata_buffer,
				  माप_प्रकार buffer_size, uपूर्णांक32_t *metadata_size,
				  uपूर्णांक32_t *flags);
uपूर्णांक64_t amdgpu_amdkfd_get_vram_usage(काष्ठा kgd_dev *kgd);
uपूर्णांक64_t amdgpu_amdkfd_get_hive_id(काष्ठा kgd_dev *kgd);
uपूर्णांक64_t amdgpu_amdkfd_get_unique_id(काष्ठा kgd_dev *kgd);
uपूर्णांक64_t amdgpu_amdkfd_get_mmio_remap_phys_addr(काष्ठा kgd_dev *kgd);
uपूर्णांक32_t amdgpu_amdkfd_get_num_gws(काष्ठा kgd_dev *kgd);
uपूर्णांक32_t amdgpu_amdkfd_get_asic_rev_id(काष्ठा kgd_dev *kgd);
पूर्णांक amdgpu_amdkfd_get_noretry(काष्ठा kgd_dev *kgd);
uपूर्णांक8_t amdgpu_amdkfd_get_xgmi_hops_count(काष्ठा kgd_dev *dst, काष्ठा kgd_dev *src);

/* Read user wptr from a specअगरied user address space with page fault
 * disabled. The memory must be pinned and mapped to the hardware when
 * this is called in hqd_load functions, so it should never fault in
 * the first place. This resolves a circular lock dependency involving
 * four locks, including the DQM lock and mmap_lock.
 */
#घोषणा पढ़ो_user_wptr(mmptr, wptr, dst)				\
	(अणु								\
		bool valid = false;					\
		अगर ((mmptr) && (wptr)) अणु				\
			pagefault_disable();				\
			अगर ((mmptr) == current->mm) अणु			\
				valid = !get_user((dst), (wptr));	\
			पूर्ण अन्यथा अगर (current->flags & PF_KTHREAD) अणु	\
				kthपढ़ो_use_mm(mmptr);			\
				valid = !get_user((dst), (wptr));	\
				kthपढ़ो_unuse_mm(mmptr);		\
			पूर्ण						\
			pagefault_enable();				\
		पूर्ण							\
		valid;							\
	पूर्ण)

/* GPUVM API */
पूर्णांक amdgpu_amdkfd_gpuvm_acquire_process_vm(काष्ठा kgd_dev *kgd,
					काष्ठा file *filp, u32 pasid,
					व्योम **vm, व्योम **process_info,
					काष्ठा dma_fence **ef);
व्योम amdgpu_amdkfd_gpuvm_release_process_vm(काष्ठा kgd_dev *kgd, व्योम *vm);
uपूर्णांक64_t amdgpu_amdkfd_gpuvm_get_process_page_dir(व्योम *vm);
पूर्णांक amdgpu_amdkfd_gpuvm_alloc_memory_of_gpu(
		काष्ठा kgd_dev *kgd, uपूर्णांक64_t va, uपूर्णांक64_t size,
		व्योम *vm, काष्ठा kgd_mem **mem,
		uपूर्णांक64_t *offset, uपूर्णांक32_t flags);
पूर्णांक amdgpu_amdkfd_gpuvm_मुक्त_memory_of_gpu(
		काष्ठा kgd_dev *kgd, काष्ठा kgd_mem *mem, uपूर्णांक64_t *size);
पूर्णांक amdgpu_amdkfd_gpuvm_map_memory_to_gpu(
		काष्ठा kgd_dev *kgd, काष्ठा kgd_mem *mem, व्योम *vm);
पूर्णांक amdgpu_amdkfd_gpuvm_unmap_memory_from_gpu(
		काष्ठा kgd_dev *kgd, काष्ठा kgd_mem *mem, व्योम *vm);
पूर्णांक amdgpu_amdkfd_gpuvm_sync_memory(
		काष्ठा kgd_dev *kgd, काष्ठा kgd_mem *mem, bool पूर्णांकr);
पूर्णांक amdgpu_amdkfd_gpuvm_map_gtt_bo_to_kernel(काष्ठा kgd_dev *kgd,
		काष्ठा kgd_mem *mem, व्योम **kptr, uपूर्णांक64_t *size);
पूर्णांक amdgpu_amdkfd_gpuvm_restore_process_bos(व्योम *process_info,
					    काष्ठा dma_fence **ef);
पूर्णांक amdgpu_amdkfd_gpuvm_get_vm_fault_info(काष्ठा kgd_dev *kgd,
					      काष्ठा kfd_vm_fault_info *info);
पूर्णांक amdgpu_amdkfd_gpuvm_import_dmabuf(काष्ठा kgd_dev *kgd,
				      काष्ठा dma_buf *dmabuf,
				      uपूर्णांक64_t va, व्योम *vm,
				      काष्ठा kgd_mem **mem, uपूर्णांक64_t *size,
				      uपूर्णांक64_t *mmap_offset);
पूर्णांक amdgpu_amdkfd_get_tile_config(काष्ठा kgd_dev *kgd,
				काष्ठा tile_config *config);
#अगर IS_ENABLED(CONFIG_HSA_AMD)
व्योम amdgpu_amdkfd_gpuvm_init_mem_limits(व्योम);
व्योम amdgpu_amdkfd_gpuvm_destroy_cb(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_vm *vm);
व्योम amdgpu_amdkfd_unreserve_memory_limit(काष्ठा amdgpu_bo *bo);
#अन्यथा
अटल अंतरभूत
व्योम amdgpu_amdkfd_gpuvm_init_mem_limits(व्योम)
अणु
पूर्ण

अटल अंतरभूत
व्योम amdgpu_amdkfd_gpuvm_destroy_cb(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_vm *vm)
अणु
पूर्ण

अटल अंतरभूत
व्योम amdgpu_amdkfd_unreserve_memory_limit(काष्ठा amdgpu_bo *bo)
अणु
पूर्ण
#पूर्ण_अगर
/* KGD2KFD callbacks */
पूर्णांक kgd2kfd_quiesce_mm(काष्ठा mm_काष्ठा *mm);
पूर्णांक kgd2kfd_resume_mm(काष्ठा mm_काष्ठा *mm);
पूर्णांक kgd2kfd_schedule_evict_and_restore_process(काष्ठा mm_काष्ठा *mm,
						काष्ठा dma_fence *fence);
#अगर IS_ENABLED(CONFIG_HSA_AMD)
पूर्णांक kgd2kfd_init(व्योम);
व्योम kgd2kfd_निकास(व्योम);
काष्ठा kfd_dev *kgd2kfd_probe(काष्ठा kgd_dev *kgd, काष्ठा pci_dev *pdev,
			      अचिन्हित पूर्णांक asic_type, bool vf);
bool kgd2kfd_device_init(काष्ठा kfd_dev *kfd,
			 काष्ठा drm_device *ddev,
			 स्थिर काष्ठा kgd2kfd_shared_resources *gpu_resources);
व्योम kgd2kfd_device_निकास(काष्ठा kfd_dev *kfd);
व्योम kgd2kfd_suspend(काष्ठा kfd_dev *kfd, bool run_pm);
पूर्णांक kgd2kfd_resume(काष्ठा kfd_dev *kfd, bool run_pm);
पूर्णांक kgd2kfd_pre_reset(काष्ठा kfd_dev *kfd);
पूर्णांक kgd2kfd_post_reset(काष्ठा kfd_dev *kfd);
व्योम kgd2kfd_पूर्णांकerrupt(काष्ठा kfd_dev *kfd, स्थिर व्योम *ih_ring_entry);
व्योम kgd2kfd_set_sram_ecc_flag(काष्ठा kfd_dev *kfd);
व्योम kgd2kfd_smi_event_throttle(काष्ठा kfd_dev *kfd, uपूर्णांक32_t throttle_biपंचांगask);
#अन्यथा
अटल अंतरभूत पूर्णांक kgd2kfd_init(व्योम)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत व्योम kgd2kfd_निकास(व्योम)
अणु
पूर्ण

अटल अंतरभूत
काष्ठा kfd_dev *kgd2kfd_probe(काष्ठा kgd_dev *kgd, काष्ठा pci_dev *pdev,
					अचिन्हित पूर्णांक asic_type, bool vf)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
bool kgd2kfd_device_init(काष्ठा kfd_dev *kfd, काष्ठा drm_device *ddev,
				स्थिर काष्ठा kgd2kfd_shared_resources *gpu_resources)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम kgd2kfd_device_निकास(काष्ठा kfd_dev *kfd)
अणु
पूर्ण

अटल अंतरभूत व्योम kgd2kfd_suspend(काष्ठा kfd_dev *kfd, bool run_pm)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक kgd2kfd_resume(काष्ठा kfd_dev *kfd, bool run_pm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kgd2kfd_pre_reset(काष्ठा kfd_dev *kfd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kgd2kfd_post_reset(काष्ठा kfd_dev *kfd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम kgd2kfd_पूर्णांकerrupt(काष्ठा kfd_dev *kfd, स्थिर व्योम *ih_ring_entry)
अणु
पूर्ण

अटल अंतरभूत
व्योम kgd2kfd_set_sram_ecc_flag(काष्ठा kfd_dev *kfd)
अणु
पूर्ण

अटल अंतरभूत
व्योम kgd2kfd_smi_event_throttle(काष्ठा kfd_dev *kfd, uपूर्णांक32_t throttle_biपंचांगask)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* AMDGPU_AMDKFD_H_INCLUDED */
