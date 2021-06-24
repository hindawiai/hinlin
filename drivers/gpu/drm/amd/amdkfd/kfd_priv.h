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

#अगर_अघोषित KFD_PRIV_H_INCLUDED
#घोषणा KFD_PRIV_H_INCLUDED

#समावेश <linux/hashtable.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kfd_ioctl.h>
#समावेश <linux/idr.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kref.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/device_cgroup.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <kgd_kfd_पूर्णांकerface.h>
#समावेश <linux/swap.h>

#समावेश "amd_shared.h"
#समावेश "amdgpu.h"

#घोषणा KFD_MAX_RING_ENTRY_SIZE	8

#घोषणा KFD_SYSFS_खाता_MODE 0444

/* GPU ID hash width in bits */
#घोषणा KFD_GPU_ID_HASH_WIDTH 16

/* Use upper bits of mmap offset to store KFD driver specअगरic inक्रमmation.
 * BITS[63:62] - Encode MMAP type
 * BITS[61:46] - Encode gpu_id. To identअगरy to which GPU the offset beदीर्घs to
 * BITS[45:0]  - MMAP offset value
 *
 * NOTE: काष्ठा vm_area_काष्ठा.vm_pgoff uses offset in pages. Hence, these
 *  defines are w.r.t to PAGE_SIZE
 */
#घोषणा KFD_MMAP_TYPE_SHIFT	62
#घोषणा KFD_MMAP_TYPE_MASK	(0x3ULL << KFD_MMAP_TYPE_SHIFT)
#घोषणा KFD_MMAP_TYPE_DOORBELL	(0x3ULL << KFD_MMAP_TYPE_SHIFT)
#घोषणा KFD_MMAP_TYPE_EVENTS	(0x2ULL << KFD_MMAP_TYPE_SHIFT)
#घोषणा KFD_MMAP_TYPE_RESERVED_MEM	(0x1ULL << KFD_MMAP_TYPE_SHIFT)
#घोषणा KFD_MMAP_TYPE_MMIO	(0x0ULL << KFD_MMAP_TYPE_SHIFT)

#घोषणा KFD_MMAP_GPU_ID_SHIFT 46
#घोषणा KFD_MMAP_GPU_ID_MASK (((1ULL << KFD_GPU_ID_HASH_WIDTH) - 1) \
				<< KFD_MMAP_GPU_ID_SHIFT)
#घोषणा KFD_MMAP_GPU_ID(gpu_id) ((((uपूर्णांक64_t)gpu_id) << KFD_MMAP_GPU_ID_SHIFT)\
				& KFD_MMAP_GPU_ID_MASK)
#घोषणा KFD_MMAP_GET_GPU_ID(offset)    ((offset & KFD_MMAP_GPU_ID_MASK) \
				>> KFD_MMAP_GPU_ID_SHIFT)

/*
 * When working with cp scheduler we should assign the HIQ manually or via
 * the amdgpu driver to a fixed hqd slot, here are the fixed HIQ hqd slot
 * definitions क्रम Kaveri. In Kaveri only the first ME queues participates
 * in the cp scheduling taking that in mind we set the HIQ slot in the
 * second ME.
 */
#घोषणा KFD_CIK_HIQ_PIPE 4
#घोषणा KFD_CIK_HIQ_QUEUE 0

/* Macro क्रम allocating काष्ठाures */
#घोषणा kfd_alloc_काष्ठा(ptr_to_काष्ठा)	\
	((typeof(ptr_to_काष्ठा)) kzalloc(माप(*ptr_to_काष्ठा), GFP_KERNEL))

#घोषणा KFD_MAX_NUM_OF_PROCESSES 512
#घोषणा KFD_MAX_NUM_OF_QUEUES_PER_PROCESS 1024

/*
 * Size of the per-process TBA+TMA buffer: 2 pages
 *
 * The first page is the TBA used क्रम the CWSR ISA code. The second
 * page is used as TMA क्रम user-mode trap handler setup in daisy-chain mode.
 */
#घोषणा KFD_CWSR_TBA_TMA_SIZE (PAGE_SIZE * 2)
#घोषणा KFD_CWSR_TMA_OFFSET PAGE_SIZE

#घोषणा KFD_MAX_NUM_OF_QUEUES_PER_DEVICE		\
	(KFD_MAX_NUM_OF_PROCESSES *			\
			KFD_MAX_NUM_OF_QUEUES_PER_PROCESS)

#घोषणा KFD_KERNEL_QUEUE_SIZE 2048

#घोषणा KFD_UNMAP_LATENCY_MS	(4000)

/*
 * 512 = 0x200
 * The करोorbell index distance between SDMA RLC (2*i) and (2*i+1) in the
 * same SDMA engine on SOC15, which has 8-byte करोorbells क्रम SDMA.
 * 512 8-byte करोorbell distance (i.e. one page away) ensures that SDMA RLC
 * (2*i+1) करोorbells (in terms of the lower 12 bit address) lie exactly in
 * the OFFSET and SIZE set in रेजिस्टरs like BIF_SDMA0_DOORBELL_RANGE.
 */
#घोषणा KFD_QUEUE_DOORBELL_MIRROR_OFFSET 512


/*
 * Kernel module parameter to specअगरy maximum number of supported queues per
 * device
 */
बाह्य पूर्णांक max_num_of_queues_per_device;


/* Kernel module parameter to specअगरy the scheduling policy */
बाह्य पूर्णांक sched_policy;

/*
 * Kernel module parameter to specअगरy the maximum process
 * number per HW scheduler
 */
बाह्य पूर्णांक hws_max_conc_proc;

बाह्य पूर्णांक cwsr_enable;

/*
 * Kernel module parameter to specअगरy whether to send sigterm to HSA process on
 * unhandled exception
 */
बाह्य पूर्णांक send_sigterm;

/*
 * This kernel module is used to simulate large bar machine on non-large bar
 * enabled machines.
 */
बाह्य पूर्णांक debug_largebar;

/*
 * Ignore CRAT table during KFD initialization, can be used to work around
 * broken CRAT tables on some AMD प्रणालीs
 */
बाह्य पूर्णांक ignore_crat;

/* Set sh_mem_config.retry_disable on GFX v9 */
बाह्य पूर्णांक amdgpu_noretry;

/* Halt अगर HWS hang is detected */
बाह्य पूर्णांक halt_अगर_hws_hang;

/* Whether MEC FW support GWS barriers */
बाह्य bool hws_gws_support;

/* Queue preemption समयout in ms */
बाह्य पूर्णांक queue_preemption_समयout_ms;

/*
 * Don't evict process queues on vm fault
 */
बाह्य पूर्णांक amdgpu_no_queue_eviction_on_vm_fault;

/* Enable eviction debug messages */
बाह्य bool debug_evictions;

क्रमागत cache_policy अणु
	cache_policy_coherent,
	cache_policy_noncoherent
पूर्ण;

#घोषणा KFD_IS_SOC15(chip) ((chip) >= CHIP_VEGA10)

काष्ठा kfd_event_पूर्णांकerrupt_class अणु
	bool (*पूर्णांकerrupt_isr)(काष्ठा kfd_dev *dev,
			स्थिर uपूर्णांक32_t *ih_ring_entry, uपूर्णांक32_t *patched_ihre,
			bool *patched_flag);
	व्योम (*पूर्णांकerrupt_wq)(काष्ठा kfd_dev *dev,
			स्थिर uपूर्णांक32_t *ih_ring_entry);
पूर्ण;

काष्ठा kfd_device_info अणु
	क्रमागत amd_asic_type asic_family;
	स्थिर अक्षर *asic_name;
	स्थिर काष्ठा kfd_event_पूर्णांकerrupt_class *event_पूर्णांकerrupt_class;
	अचिन्हित पूर्णांक max_pasid_bits;
	अचिन्हित पूर्णांक max_no_of_hqd;
	अचिन्हित पूर्णांक करोorbell_size;
	माप_प्रकार ih_ring_entry_size;
	uपूर्णांक8_t num_of_watch_poपूर्णांकs;
	uपूर्णांक16_t mqd_size_aligned;
	bool supports_cwsr;
	bool needs_iommu_device;
	bool needs_pci_atomics;
	अचिन्हित पूर्णांक num_sdma_engines;
	अचिन्हित पूर्णांक num_xgmi_sdma_engines;
	अचिन्हित पूर्णांक num_sdma_queues_per_engine;
पूर्ण;

काष्ठा kfd_mem_obj अणु
	uपूर्णांक32_t range_start;
	uपूर्णांक32_t range_end;
	uपूर्णांक64_t gpu_addr;
	uपूर्णांक32_t *cpu_ptr;
	व्योम *gtt_mem;
पूर्ण;

काष्ठा kfd_vmid_info अणु
	uपूर्णांक32_t first_vmid_kfd;
	uपूर्णांक32_t last_vmid_kfd;
	uपूर्णांक32_t vmid_num_kfd;
पूर्ण;

काष्ठा kfd_dev अणु
	काष्ठा kgd_dev *kgd;

	स्थिर काष्ठा kfd_device_info *device_info;
	काष्ठा pci_dev *pdev;
	काष्ठा drm_device *ddev;

	अचिन्हित पूर्णांक id;		/* topology stub index */

	phys_addr_t करोorbell_base;	/* Start of actual करोorbells used by
					 * KFD. It is aligned क्रम mapping
					 * पूर्णांकo user mode
					 */
	माप_प्रकार करोorbell_base_dw_offset;	/* Offset from the start of the PCI
					 * करोorbell BAR to the first KFD
					 * करोorbell in dwords. GFX reserves
					 * the segment beक्रमe this offset.
					 */
	u32 __iomem *करोorbell_kernel_ptr; /* This is a poपूर्णांकer क्रम a करोorbells
					   * page used by kernel queue
					   */

	काष्ठा kgd2kfd_shared_resources shared_resources;
	काष्ठा kfd_vmid_info vm_info;

	स्थिर काष्ठा kfd2kgd_calls *kfd2kgd;
	काष्ठा mutex करोorbell_mutex;
	DECLARE_BITMAP(करोorbell_available_index,
			KFD_MAX_NUM_OF_QUEUES_PER_PROCESS);

	व्योम *gtt_mem;
	uपूर्णांक64_t gtt_start_gpu_addr;
	व्योम *gtt_start_cpu_ptr;
	व्योम *gtt_sa_biपंचांगap;
	काष्ठा mutex gtt_sa_lock;
	अचिन्हित पूर्णांक gtt_sa_chunk_size;
	अचिन्हित पूर्णांक gtt_sa_num_of_chunks;

	/* Interrupts */
	काष्ठा kfअगरo ih_fअगरo;
	काष्ठा workqueue_काष्ठा *ih_wq;
	काष्ठा work_काष्ठा पूर्णांकerrupt_work;
	spinlock_t पूर्णांकerrupt_lock;

	/* QCM Device instance */
	काष्ठा device_queue_manager *dqm;

	bool init_complete;
	/*
	 * Interrupts of पूर्णांकerest to KFD are copied
	 * from the HW ring पूर्णांकo a SW ring.
	 */
	bool पूर्णांकerrupts_active;

	/* Debug manager */
	काष्ठा kfd_dbgmgr *dbgmgr;

	/* Firmware versions */
	uपूर्णांक16_t mec_fw_version;
	uपूर्णांक16_t mec2_fw_version;
	uपूर्णांक16_t sdma_fw_version;

	/* Maximum process number mapped to HW scheduler */
	अचिन्हित पूर्णांक max_proc_per_quantum;

	/* CWSR */
	bool cwsr_enabled;
	स्थिर व्योम *cwsr_isa;
	अचिन्हित पूर्णांक cwsr_isa_size;

	/* xGMI */
	uपूर्णांक64_t hive_id;

	bool pci_atomic_requested;

	/* Use IOMMU v2 flag */
	bool use_iommu_v2;

	/* SRAM ECC flag */
	atomic_t sram_ecc_flag;

	/* Compute Profile ref. count */
	atomic_t compute_profile;

	/* Global GWS resource shared between processes */
	व्योम *gws;

	/* Clients watching SMI events */
	काष्ठा list_head smi_clients;
	spinlock_t smi_lock;

	uपूर्णांक32_t reset_seq_num;

	काष्ठा ida करोorbell_ida;
	अचिन्हित पूर्णांक max_करोorbell_slices;

	पूर्णांक noretry;
पूर्ण;

क्रमागत kfd_mempool अणु
	KFD_MEMPOOL_SYSTEM_CACHEABLE = 1,
	KFD_MEMPOOL_SYSTEM_WRITECOMBINE = 2,
	KFD_MEMPOOL_FRAMEBUFFER = 3,
पूर्ण;

/* Character device पूर्णांकerface */
पूर्णांक kfd_अक्षरdev_init(व्योम);
व्योम kfd_अक्षरdev_निकास(व्योम);
काष्ठा device *kfd_अक्षरdev(व्योम);

/**
 * क्रमागत kfd_unmap_queues_filter - Enum क्रम queue filters.
 *
 * @KFD_UNMAP_QUEUES_FILTER_SINGLE_QUEUE: Preempts single queue.
 *
 * @KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES: Preempts all queues in the
 *						running queues list.
 *
 * @KFD_UNMAP_QUEUES_FILTER_BY_PASID: Preempts queues that beदीर्घs to
 *						specअगरic process.
 *
 */
क्रमागत kfd_unmap_queues_filter अणु
	KFD_UNMAP_QUEUES_FILTER_SINGLE_QUEUE,
	KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES,
	KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES,
	KFD_UNMAP_QUEUES_FILTER_BY_PASID
पूर्ण;

/**
 * क्रमागत kfd_queue_type - Enum क्रम various queue types.
 *
 * @KFD_QUEUE_TYPE_COMPUTE: Regular user mode queue type.
 *
 * @KFD_QUEUE_TYPE_SDMA: SDMA user mode queue type.
 *
 * @KFD_QUEUE_TYPE_HIQ: HIQ queue type.
 *
 * @KFD_QUEUE_TYPE_DIQ: DIQ queue type.
 *
 * @KFD_QUEUE_TYPE_SDMA_XGMI: Special SDMA queue क्रम XGMI पूर्णांकerface.
 */
क्रमागत kfd_queue_type  अणु
	KFD_QUEUE_TYPE_COMPUTE,
	KFD_QUEUE_TYPE_SDMA,
	KFD_QUEUE_TYPE_HIQ,
	KFD_QUEUE_TYPE_DIQ,
	KFD_QUEUE_TYPE_SDMA_XGMI
पूर्ण;

क्रमागत kfd_queue_क्रमmat अणु
	KFD_QUEUE_FORMAT_PM4,
	KFD_QUEUE_FORMAT_AQL
पूर्ण;

क्रमागत KFD_QUEUE_PRIORITY अणु
	KFD_QUEUE_PRIORITY_MINIMUM = 0,
	KFD_QUEUE_PRIORITY_MAXIMUM = 15
पूर्ण;

/**
 * काष्ठा queue_properties
 *
 * @type: The queue type.
 *
 * @queue_id: Queue identअगरier.
 *
 * @queue_address: Queue ring buffer address.
 *
 * @queue_size: Queue ring buffer size.
 *
 * @priority: Defines the queue priority relative to other queues in the
 * process.
 * This is just an indication and HW scheduling may override the priority as
 * necessary जबतक keeping the relative prioritization.
 * the priority granularity is from 0 to f which f is the highest priority.
 * currently all queues are initialized with the highest priority.
 *
 * @queue_percent: This field is partially implemented and currently a zero in
 * this field defines that the queue is non active.
 *
 * @पढ़ो_ptr: User space address which poपूर्णांकs to the number of dwords the
 * cp पढ़ो from the ring buffer. This field updates स्वतःmatically by the H/W.
 *
 * @ग_लिखो_ptr: Defines the number of dwords written to the ring buffer.
 *
 * @करोorbell_ptr: Notअगरies the H/W of new packet written to the queue ring
 * buffer. This field should be similar to ग_लिखो_ptr and the user should
 * update this field after updating the ग_लिखो_ptr.
 *
 * @करोorbell_off: The करोorbell offset in the करोorbell pci-bar.
 *
 * @is_पूर्णांकerop: Defines अगर this is a पूर्णांकerop queue. Interop queue means that
 * the queue can access both graphics and compute resources.
 *
 * @is_evicted: Defines अगर the queue is evicted. Only active queues
 * are evicted, rendering them inactive.
 *
 * @is_active: Defines अगर the queue is active or not. @is_active and
 * @is_evicted are रक्षित by the DQM lock.
 *
 * @is_gws: Defines अगर the queue has been updated to be GWS-capable or not.
 * @is_gws should be रक्षित by the DQM lock, since changing it can yield the
 * possibility of updating DQM state on number of GWS queues.
 *
 * @vmid: If the scheduling mode is no cp scheduling the field defines the vmid
 * of the queue.
 *
 * This काष्ठाure represents the queue properties क्रम each queue no matter अगर
 * it's user mode or kernel mode queue.
 *
 */
काष्ठा queue_properties अणु
	क्रमागत kfd_queue_type type;
	क्रमागत kfd_queue_क्रमmat क्रमmat;
	अचिन्हित पूर्णांक queue_id;
	uपूर्णांक64_t queue_address;
	uपूर्णांक64_t  queue_size;
	uपूर्णांक32_t priority;
	uपूर्णांक32_t queue_percent;
	uपूर्णांक32_t *पढ़ो_ptr;
	uपूर्णांक32_t *ग_लिखो_ptr;
	व्योम __iomem *करोorbell_ptr;
	uपूर्णांक32_t करोorbell_off;
	bool is_पूर्णांकerop;
	bool is_evicted;
	bool is_active;
	bool is_gws;
	/* Not relevant क्रम user mode queues in cp scheduling */
	अचिन्हित पूर्णांक vmid;
	/* Relevant only क्रम sdma queues*/
	uपूर्णांक32_t sdma_engine_id;
	uपूर्णांक32_t sdma_queue_id;
	uपूर्णांक32_t sdma_vm_addr;
	/* Relevant only क्रम VI */
	uपूर्णांक64_t eop_ring_buffer_address;
	uपूर्णांक32_t eop_ring_buffer_size;
	uपूर्णांक64_t ctx_save_restore_area_address;
	uपूर्णांक32_t ctx_save_restore_area_size;
	uपूर्णांक32_t ctl_stack_size;
	uपूर्णांक64_t tba_addr;
	uपूर्णांक64_t पंचांगa_addr;
	/* Relevant क्रम CU */
	uपूर्णांक32_t cu_mask_count; /* Must be a multiple of 32 */
	uपूर्णांक32_t *cu_mask;
पूर्ण;

#घोषणा QUEUE_IS_ACTIVE(q) ((q).queue_size > 0 &&	\
			    (q).queue_address != 0 &&	\
			    (q).queue_percent > 0 &&	\
			    !(q).is_evicted)

/**
 * काष्ठा queue
 *
 * @list: Queue linked list.
 *
 * @mqd: The queue MQD (memory queue descriptor).
 *
 * @mqd_mem_obj: The MQD local gpu memory object.
 *
 * @gart_mqd_addr: The MQD gart mc address.
 *
 * @properties: The queue properties.
 *
 * @mec: Used only in no cp scheduling mode and identअगरies to micro engine id
 *	 that the queue should be executed on.
 *
 * @pipe: Used only in no cp scheduling mode and identअगरies the queue's pipe
 *	  id.
 *
 * @queue: Used only in no cp scheduliong mode and identअगरies the queue's slot.
 *
 * @process: The kfd process that created this queue.
 *
 * @device: The kfd device that created this queue.
 *
 * @gws: Poपूर्णांकing to gws kgd_mem अगर this is a gws control queue; शून्य
 * otherwise.
 *
 * This काष्ठाure represents user mode compute queues.
 * It contains all the necessary data to handle such queues.
 *
 */

काष्ठा queue अणु
	काष्ठा list_head list;
	व्योम *mqd;
	काष्ठा kfd_mem_obj *mqd_mem_obj;
	uपूर्णांक64_t gart_mqd_addr;
	काष्ठा queue_properties properties;

	uपूर्णांक32_t mec;
	uपूर्णांक32_t pipe;
	uपूर्णांक32_t queue;

	अचिन्हित पूर्णांक sdma_id;
	अचिन्हित पूर्णांक करोorbell_id;

	काष्ठा kfd_process	*process;
	काष्ठा kfd_dev		*device;
	व्योम *gws;

	/* procfs */
	काष्ठा kobject kobj;
पूर्ण;

क्रमागत KFD_MQD_TYPE अणु
	KFD_MQD_TYPE_HIQ = 0,		/* क्रम hiq */
	KFD_MQD_TYPE_CP,		/* क्रम cp queues and diq */
	KFD_MQD_TYPE_SDMA,		/* क्रम sdma queues */
	KFD_MQD_TYPE_DIQ,		/* क्रम diq */
	KFD_MQD_TYPE_MAX
पूर्ण;

क्रमागत KFD_PIPE_PRIORITY अणु
	KFD_PIPE_PRIORITY_CS_LOW = 0,
	KFD_PIPE_PRIORITY_CS_MEDIUM,
	KFD_PIPE_PRIORITY_CS_HIGH
पूर्ण;

काष्ठा scheduling_resources अणु
	अचिन्हित पूर्णांक vmid_mask;
	क्रमागत kfd_queue_type type;
	uपूर्णांक64_t queue_mask;
	uपूर्णांक64_t gws_mask;
	uपूर्णांक32_t oac_mask;
	uपूर्णांक32_t gds_heap_base;
	uपूर्णांक32_t gds_heap_size;
पूर्ण;

काष्ठा process_queue_manager अणु
	/* data */
	काष्ठा kfd_process	*process;
	काष्ठा list_head	queues;
	अचिन्हित दीर्घ		*queue_slot_biपंचांगap;
पूर्ण;

काष्ठा qcm_process_device अणु
	/* The Device Queue Manager that owns this data */
	काष्ठा device_queue_manager *dqm;
	काष्ठा process_queue_manager *pqm;
	/* Queues list */
	काष्ठा list_head queues_list;
	काष्ठा list_head priv_queue_list;

	अचिन्हित पूर्णांक queue_count;
	अचिन्हित पूर्णांक vmid;
	bool is_debug;
	अचिन्हित पूर्णांक evicted; /* eviction counter, 0=active */

	/* This flag tells अगर we should reset all wavefronts on
	 * process termination
	 */
	bool reset_wavefronts;

	/* This flag tells us अगर this process has a GWS-capable
	 * queue that will be mapped पूर्णांकo the runlist. It's
	 * possible to request a GWS BO, but not have the queue
	 * currently mapped, and this changes how the MAP_PROCESS
	 * PM4 packet is configured.
	 */
	bool mapped_gws_queue;

	/* All the memory management data should be here too */
	uपूर्णांक64_t gds_context_area;
	/* Contains page table flags such as AMDGPU_PTE_VALID since gfx9 */
	uपूर्णांक64_t page_table_base;
	uपूर्णांक32_t sh_mem_config;
	uपूर्णांक32_t sh_mem_bases;
	uपूर्णांक32_t sh_mem_ape1_base;
	uपूर्णांक32_t sh_mem_ape1_limit;
	uपूर्णांक32_t gds_size;
	uपूर्णांक32_t num_gws;
	uपूर्णांक32_t num_oac;
	uपूर्णांक32_t sh_hidden_निजी_base;

	/* CWSR memory */
	व्योम *cwsr_kaddr;
	uपूर्णांक64_t cwsr_base;
	uपूर्णांक64_t tba_addr;
	uपूर्णांक64_t पंचांगa_addr;

	/* IB memory */
	uपूर्णांक64_t ib_base;
	व्योम *ib_kaddr;

	/* करोorbell resources per process per device */
	अचिन्हित दीर्घ *करोorbell_biपंचांगap;
पूर्ण;

/* KFD Memory Eviction */

/* Approx. रुको समय beक्रमe attempting to restore evicted BOs */
#घोषणा PROCESS_RESTORE_TIME_MS 100
/* Approx. back off समय अगर restore fails due to lack of memory */
#घोषणा PROCESS_BACK_OFF_TIME_MS 100
/* Approx. समय beक्रमe evicting the process again */
#घोषणा PROCESS_ACTIVE_TIME_MS 10

/* 8 byte handle containing GPU ID in the most signअगरicant 4 bytes and
 * idr_handle in the least signअगरicant 4 bytes
 */
#घोषणा MAKE_HANDLE(gpu_id, idr_handle) \
	(((uपूर्णांक64_t)(gpu_id) << 32) + idr_handle)
#घोषणा GET_GPU_ID(handle) (handle >> 32)
#घोषणा GET_IDR_HANDLE(handle) (handle & 0xFFFFFFFF)

क्रमागत kfd_pdd_bound अणु
	PDD_UNBOUND = 0,
	PDD_BOUND,
	PDD_BOUND_SUSPENDED,
पूर्ण;

#घोषणा MAX_SYSFS_खाताNAME_LEN 15

/*
 * SDMA counter runs at 100MHz frequency.
 * We display SDMA activity in microsecond granularity in sysfs.
 * As a result, the भागisor is 100.
 */
#घोषणा SDMA_ACTIVITY_DIVISOR  100

/* Data that is per-process-per device. */
काष्ठा kfd_process_device अणु
	/* The device that owns this data. */
	काष्ठा kfd_dev *dev;

	/* The process that owns this kfd_process_device. */
	काष्ठा kfd_process *process;

	/* per-process-per device QCM data काष्ठाure */
	काष्ठा qcm_process_device qpd;

	/*Apertures*/
	uपूर्णांक64_t lds_base;
	uपूर्णांक64_t lds_limit;
	uपूर्णांक64_t gpuvm_base;
	uपूर्णांक64_t gpuvm_limit;
	uपूर्णांक64_t scratch_base;
	uपूर्णांक64_t scratch_limit;

	/* VM context क्रम GPUVM allocations */
	काष्ठा file *drm_file;
	व्योम *vm;

	/* GPUVM allocations storage */
	काष्ठा idr alloc_idr;

	/* Flag used to tell the pdd has dequeued from the dqm.
	 * This is used to prevent dev->dqm->ops.process_termination() from
	 * being called twice when it is alपढ़ोy called in IOMMU callback
	 * function.
	 */
	bool alपढ़ोy_dequeued;
	bool runसमय_inuse;

	/* Is this process/pasid bound to this device? (amd_iommu_bind_pasid) */
	क्रमागत kfd_pdd_bound bound;

	/* VRAM usage */
	uपूर्णांक64_t vram_usage;
	काष्ठा attribute attr_vram;
	अक्षर vram_filename[MAX_SYSFS_खाताNAME_LEN];

	/* SDMA activity tracking */
	uपूर्णांक64_t sdma_past_activity_counter;
	काष्ठा attribute attr_sdma;
	अक्षर sdma_filename[MAX_SYSFS_खाताNAME_LEN];

	/* Eviction activity tracking */
	uपूर्णांक64_t last_evict_बारtamp;
	atomic64_t evict_duration_counter;
	काष्ठा attribute attr_evict;

	काष्ठा kobject *kobj_stats;
	अचिन्हित पूर्णांक करोorbell_index;

	/*
	 * @cu_occupancy: Reports occupancy of Compute Units (CU) of a process
	 * that is associated with device encoded by "this" काष्ठा instance. The
	 * value reflects CU usage by all of the waves launched by this process
	 * on this device. A very important property of occupancy parameter is
	 * that its value is a snapshot of current use.
	 *
	 * Following is to be noted regarding how this parameter is reported:
	 *
	 *  The number of waves that a CU can launch is limited by couple of
	 *  parameters. These are encoded by काष्ठा amdgpu_cu_info instance
	 *  that is part of every device definition. For GFX9 devices this
	 *  translates to 40 waves (simd_per_cu * max_waves_per_simd) when waves
	 *  करो not use scratch memory and 32 waves (max_scratch_slots_per_cu)
	 *  when they करो use scratch memory. This could change क्रम future
	 *  devices and thereक्रमe this example should be considered as a guide.
	 *
	 *  All CU's of a device are available क्रम the process. This may not be true
	 *  under certain conditions - e.g. CU masking.
	 *
	 *  Finally number of CU's that are occupied by a process is affected by both
	 *  number of CU's a device has aदीर्घ with number of other competing processes
	 */
	काष्ठा attribute attr_cu_occupancy;
पूर्ण;

#घोषणा qpd_to_pdd(x) container_of(x, काष्ठा kfd_process_device, qpd)

/* Process data */
काष्ठा kfd_process अणु
	/*
	 * kfd_process are stored in an mm_काष्ठा*->kfd_process*
	 * hash table (kfd_processes in kfd_process.c)
	 */
	काष्ठा hlist_node kfd_processes;

	/*
	 * Opaque poपूर्णांकer to mm_काष्ठा. We करोn't hold a reference to
	 * it so it should never be dereferenced from here. This is
	 * only used क्रम looking up processes by their mm.
	 */
	व्योम *mm;

	काष्ठा kref ref;
	काष्ठा work_काष्ठा release_work;

	काष्ठा mutex mutex;

	/*
	 * In any process, the thपढ़ो that started मुख्य() is the lead
	 * thपढ़ो and outlives the rest.
	 * It is here because amd_iommu_bind_pasid wants a task_काष्ठा.
	 * It can also be used क्रम safely getting a reference to the
	 * mm_काष्ठा of the process.
	 */
	काष्ठा task_काष्ठा *lead_thपढ़ो;

	/* We want to receive a notअगरication when the mm_काष्ठा is destroyed */
	काष्ठा mmu_notअगरier mmu_notअगरier;

	u32 pasid;

	/*
	 * Array of kfd_process_device poपूर्णांकers,
	 * one क्रम each device the process is using.
	 */
	काष्ठा kfd_process_device *pdds[MAX_GPU_INSTANCE];
	uपूर्णांक32_t n_pdds;

	काष्ठा process_queue_manager pqm;

	/*Is the user space process 32 bit?*/
	bool is_32bit_user_mode;

	/* Event-related data */
	काष्ठा mutex event_mutex;
	/* Event ID allocator and lookup */
	काष्ठा idr event_idr;
	/* Event page */
	काष्ठा kfd_संकेत_page *संकेत_page;
	माप_प्रकार संकेत_mapped_size;
	माप_प्रकार संकेत_event_count;
	bool संकेत_event_limit_reached;

	/* Inक्रमmation used क्रम memory eviction */
	व्योम *kgd_process_info;
	/* Eviction fence that is attached to all the BOs of this process. The
	 * fence will be triggered during eviction and new one will be created
	 * during restore
	 */
	काष्ठा dma_fence *ef;

	/* Work items क्रम evicting and restoring BOs */
	काष्ठा delayed_work eviction_work;
	काष्ठा delayed_work restore_work;
	/* seqno of the last scheduled eviction */
	अचिन्हित पूर्णांक last_eviction_seqno;
	/* Approx. the last बारtamp (in jअगरfies) when the process was
	 * restored after an eviction
	 */
	अचिन्हित दीर्घ last_restore_बारtamp;

	/* Kobj क्रम our procfs */
	काष्ठा kobject *kobj;
	काष्ठा kobject *kobj_queues;
	काष्ठा attribute attr_pasid;
पूर्ण;

#घोषणा KFD_PROCESS_TABLE_SIZE 5 /* bits: 32 entries */
बाह्य DECLARE_HASHTABLE(kfd_processes_table, KFD_PROCESS_TABLE_SIZE);
बाह्य काष्ठा srcu_काष्ठा kfd_processes_srcu;

/**
 * प्रकार amdkfd_ioctl_t - प्रकार क्रम ioctl function poपूर्णांकer.
 *
 * @filep: poपूर्णांकer to file काष्ठाure.
 * @p: amdkfd process poपूर्णांकer.
 * @data: poपूर्णांकer to arg that was copied from user.
 *
 * Return: वापसs ioctl completion code.
 */
प्रकार पूर्णांक amdkfd_ioctl_t(काष्ठा file *filep, काष्ठा kfd_process *p,
				व्योम *data);

काष्ठा amdkfd_ioctl_desc अणु
	अचिन्हित पूर्णांक cmd;
	पूर्णांक flags;
	amdkfd_ioctl_t *func;
	अचिन्हित पूर्णांक cmd_drv;
	स्थिर अक्षर *name;
पूर्ण;
bool kfd_dev_is_large_bar(काष्ठा kfd_dev *dev);

पूर्णांक kfd_process_create_wq(व्योम);
व्योम kfd_process_destroy_wq(व्योम);
काष्ठा kfd_process *kfd_create_process(काष्ठा file *filep);
काष्ठा kfd_process *kfd_get_process(स्थिर काष्ठा task_काष्ठा *);
काष्ठा kfd_process *kfd_lookup_process_by_pasid(u32 pasid);
काष्ठा kfd_process *kfd_lookup_process_by_mm(स्थिर काष्ठा mm_काष्ठा *mm);
व्योम kfd_unref_process(काष्ठा kfd_process *p);
पूर्णांक kfd_process_evict_queues(काष्ठा kfd_process *p);
पूर्णांक kfd_process_restore_queues(काष्ठा kfd_process *p);
व्योम kfd_suspend_all_processes(व्योम);
पूर्णांक kfd_resume_all_processes(व्योम);

पूर्णांक kfd_process_device_init_vm(काष्ठा kfd_process_device *pdd,
			       काष्ठा file *drm_file);
काष्ठा kfd_process_device *kfd_bind_process_to_device(काष्ठा kfd_dev *dev,
						काष्ठा kfd_process *p);
काष्ठा kfd_process_device *kfd_get_process_device_data(काष्ठा kfd_dev *dev,
							काष्ठा kfd_process *p);
काष्ठा kfd_process_device *kfd_create_process_device_data(काष्ठा kfd_dev *dev,
							काष्ठा kfd_process *p);

पूर्णांक kfd_reserved_mem_mmap(काष्ठा kfd_dev *dev, काष्ठा kfd_process *process,
			  काष्ठा vm_area_काष्ठा *vma);

/* KFD process API क्रम creating and translating handles */
पूर्णांक kfd_process_device_create_obj_handle(काष्ठा kfd_process_device *pdd,
					व्योम *mem);
व्योम *kfd_process_device_translate_handle(काष्ठा kfd_process_device *p,
					पूर्णांक handle);
व्योम kfd_process_device_हटाओ_obj_handle(काष्ठा kfd_process_device *pdd,
					पूर्णांक handle);

/* PASIDs */
पूर्णांक kfd_pasid_init(व्योम);
व्योम kfd_pasid_निकास(व्योम);
bool kfd_set_pasid_limit(अचिन्हित पूर्णांक new_limit);
अचिन्हित पूर्णांक kfd_get_pasid_limit(व्योम);
u32 kfd_pasid_alloc(व्योम);
व्योम kfd_pasid_मुक्त(u32 pasid);

/* Doorbells */
माप_प्रकार kfd_करोorbell_process_slice(काष्ठा kfd_dev *kfd);
पूर्णांक kfd_करोorbell_init(काष्ठा kfd_dev *kfd);
व्योम kfd_करोorbell_fini(काष्ठा kfd_dev *kfd);
पूर्णांक kfd_करोorbell_mmap(काष्ठा kfd_dev *dev, काष्ठा kfd_process *process,
		      काष्ठा vm_area_काष्ठा *vma);
व्योम __iomem *kfd_get_kernel_करोorbell(काष्ठा kfd_dev *kfd,
					अचिन्हित पूर्णांक *करोorbell_off);
व्योम kfd_release_kernel_करोorbell(काष्ठा kfd_dev *kfd, u32 __iomem *db_addr);
u32 पढ़ो_kernel_करोorbell(u32 __iomem *db);
व्योम ग_लिखो_kernel_करोorbell(व्योम __iomem *db, u32 value);
व्योम ग_लिखो_kernel_करोorbell64(व्योम __iomem *db, u64 value);
अचिन्हित पूर्णांक kfd_get_करोorbell_dw_offset_in_bar(काष्ठा kfd_dev *kfd,
					काष्ठा kfd_process_device *pdd,
					अचिन्हित पूर्णांक करोorbell_id);
phys_addr_t kfd_get_process_करोorbells(काष्ठा kfd_process_device *pdd);
पूर्णांक kfd_alloc_process_करोorbells(काष्ठा kfd_dev *kfd,
				अचिन्हित पूर्णांक *करोorbell_index);
व्योम kfd_मुक्त_process_करोorbells(काष्ठा kfd_dev *kfd,
				अचिन्हित पूर्णांक करोorbell_index);
/* GTT Sub-Allocator */

पूर्णांक kfd_gtt_sa_allocate(काष्ठा kfd_dev *kfd, अचिन्हित पूर्णांक size,
			काष्ठा kfd_mem_obj **mem_obj);

पूर्णांक kfd_gtt_sa_मुक्त(काष्ठा kfd_dev *kfd, काष्ठा kfd_mem_obj *mem_obj);

बाह्य काष्ठा device *kfd_device;

/* KFD's procfs */
व्योम kfd_procfs_init(व्योम);
व्योम kfd_procfs_shutकरोwn(व्योम);
पूर्णांक kfd_procfs_add_queue(काष्ठा queue *q);
व्योम kfd_procfs_del_queue(काष्ठा queue *q);

/* Topology */
पूर्णांक kfd_topology_init(व्योम);
व्योम kfd_topology_shutकरोwn(व्योम);
पूर्णांक kfd_topology_add_device(काष्ठा kfd_dev *gpu);
पूर्णांक kfd_topology_हटाओ_device(काष्ठा kfd_dev *gpu);
काष्ठा kfd_topology_device *kfd_topology_device_by_proximity_करोमुख्य(
						uपूर्णांक32_t proximity_करोमुख्य);
काष्ठा kfd_topology_device *kfd_topology_device_by_id(uपूर्णांक32_t gpu_id);
काष्ठा kfd_dev *kfd_device_by_id(uपूर्णांक32_t gpu_id);
काष्ठा kfd_dev *kfd_device_by_pci_dev(स्थिर काष्ठा pci_dev *pdev);
काष्ठा kfd_dev *kfd_device_by_kgd(स्थिर काष्ठा kgd_dev *kgd);
पूर्णांक kfd_topology_क्रमागत_kfd_devices(uपूर्णांक8_t idx, काष्ठा kfd_dev **kdev);
पूर्णांक kfd_numa_node_to_apic_id(पूर्णांक numa_node_id);
व्योम kfd_द्विगुन_confirm_iommu_support(काष्ठा kfd_dev *gpu);

/* Interrupts */
पूर्णांक kfd_पूर्णांकerrupt_init(काष्ठा kfd_dev *dev);
व्योम kfd_पूर्णांकerrupt_निकास(काष्ठा kfd_dev *dev);
bool enqueue_ih_ring_entry(काष्ठा kfd_dev *kfd,	स्थिर व्योम *ih_ring_entry);
bool पूर्णांकerrupt_is_wanted(काष्ठा kfd_dev *dev,
				स्थिर uपूर्णांक32_t *ih_ring_entry,
				uपूर्णांक32_t *patched_ihre, bool *flag);

/* amdkfd Apertures */
पूर्णांक kfd_init_apertures(काष्ठा kfd_process *process);

व्योम kfd_process_set_trap_handler(काष्ठा qcm_process_device *qpd,
				  uपूर्णांक64_t tba_addr,
				  uपूर्णांक64_t पंचांगa_addr);

/* Queue Context Management */
पूर्णांक init_queue(काष्ठा queue **q, स्थिर काष्ठा queue_properties *properties);
व्योम uninit_queue(काष्ठा queue *q);
व्योम prपूर्णांक_queue_properties(काष्ठा queue_properties *q);
व्योम prपूर्णांक_queue(काष्ठा queue *q);

काष्ठा mqd_manager *mqd_manager_init_cik(क्रमागत KFD_MQD_TYPE type,
		काष्ठा kfd_dev *dev);
काष्ठा mqd_manager *mqd_manager_init_cik_hawaii(क्रमागत KFD_MQD_TYPE type,
		काष्ठा kfd_dev *dev);
काष्ठा mqd_manager *mqd_manager_init_vi(क्रमागत KFD_MQD_TYPE type,
		काष्ठा kfd_dev *dev);
काष्ठा mqd_manager *mqd_manager_init_vi_tonga(क्रमागत KFD_MQD_TYPE type,
		काष्ठा kfd_dev *dev);
काष्ठा mqd_manager *mqd_manager_init_v9(क्रमागत KFD_MQD_TYPE type,
		काष्ठा kfd_dev *dev);
काष्ठा mqd_manager *mqd_manager_init_v10(क्रमागत KFD_MQD_TYPE type,
		काष्ठा kfd_dev *dev);
काष्ठा device_queue_manager *device_queue_manager_init(काष्ठा kfd_dev *dev);
व्योम device_queue_manager_uninit(काष्ठा device_queue_manager *dqm);
काष्ठा kernel_queue *kernel_queue_init(काष्ठा kfd_dev *dev,
					क्रमागत kfd_queue_type type);
व्योम kernel_queue_uninit(काष्ठा kernel_queue *kq, bool hanging);
पूर्णांक kfd_process_vm_fault(काष्ठा device_queue_manager *dqm, u32 pasid);

/* Process Queue Manager */
काष्ठा process_queue_node अणु
	काष्ठा queue *q;
	काष्ठा kernel_queue *kq;
	काष्ठा list_head process_queue_list;
पूर्ण;

व्योम kfd_process_dequeue_from_device(काष्ठा kfd_process_device *pdd);
व्योम kfd_process_dequeue_from_all_devices(काष्ठा kfd_process *p);
पूर्णांक pqm_init(काष्ठा process_queue_manager *pqm, काष्ठा kfd_process *p);
व्योम pqm_uninit(काष्ठा process_queue_manager *pqm);
पूर्णांक pqm_create_queue(काष्ठा process_queue_manager *pqm,
			    काष्ठा kfd_dev *dev,
			    काष्ठा file *f,
			    काष्ठा queue_properties *properties,
			    अचिन्हित पूर्णांक *qid,
			    uपूर्णांक32_t *p_करोorbell_offset_in_process);
पूर्णांक pqm_destroy_queue(काष्ठा process_queue_manager *pqm, अचिन्हित पूर्णांक qid);
पूर्णांक pqm_update_queue(काष्ठा process_queue_manager *pqm, अचिन्हित पूर्णांक qid,
			काष्ठा queue_properties *p);
पूर्णांक pqm_set_cu_mask(काष्ठा process_queue_manager *pqm, अचिन्हित पूर्णांक qid,
			काष्ठा queue_properties *p);
पूर्णांक pqm_set_gws(काष्ठा process_queue_manager *pqm, अचिन्हित पूर्णांक qid,
			व्योम *gws);
काष्ठा kernel_queue *pqm_get_kernel_queue(काष्ठा process_queue_manager *pqm,
						अचिन्हित पूर्णांक qid);
काष्ठा queue *pqm_get_user_queue(काष्ठा process_queue_manager *pqm,
						अचिन्हित पूर्णांक qid);
पूर्णांक pqm_get_wave_state(काष्ठा process_queue_manager *pqm,
		       अचिन्हित पूर्णांक qid,
		       व्योम __user *ctl_stack,
		       u32 *ctl_stack_used_size,
		       u32 *save_area_used_size);

पूर्णांक amdkfd_fence_रुको_समयout(uपूर्णांक64_t *fence_addr,
			      uपूर्णांक64_t fence_value,
			      अचिन्हित पूर्णांक समयout_ms);

/* Packet Manager */

#घोषणा KFD_FENCE_COMPLETED (100)
#घोषणा KFD_FENCE_INIT   (10)

काष्ठा packet_manager अणु
	काष्ठा device_queue_manager *dqm;
	काष्ठा kernel_queue *priv_queue;
	काष्ठा mutex lock;
	bool allocated;
	काष्ठा kfd_mem_obj *ib_buffer_obj;
	अचिन्हित पूर्णांक ib_size_bytes;
	bool is_over_subscription;

	स्थिर काष्ठा packet_manager_funcs *pmf;
पूर्ण;

काष्ठा packet_manager_funcs अणु
	/* Support ASIC-specअगरic packet क्रमmats क्रम PM4 packets */
	पूर्णांक (*map_process)(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
			काष्ठा qcm_process_device *qpd);
	पूर्णांक (*runlist)(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
			uपूर्णांक64_t ib, माप_प्रकार ib_size_in_dwords, bool chain);
	पूर्णांक (*set_resources)(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
			काष्ठा scheduling_resources *res);
	पूर्णांक (*map_queues)(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
			काष्ठा queue *q, bool is_अटल);
	पूर्णांक (*unmap_queues)(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
			क्रमागत kfd_queue_type type,
			क्रमागत kfd_unmap_queues_filter mode,
			uपूर्णांक32_t filter_param, bool reset,
			अचिन्हित पूर्णांक sdma_engine);
	पूर्णांक (*query_status)(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
			uपूर्णांक64_t fence_address,	uपूर्णांक64_t fence_value);
	पूर्णांक (*release_mem)(uपूर्णांक64_t gpu_addr, uपूर्णांक32_t *buffer);

	/* Packet sizes */
	पूर्णांक map_process_size;
	पूर्णांक runlist_size;
	पूर्णांक set_resources_size;
	पूर्णांक map_queues_size;
	पूर्णांक unmap_queues_size;
	पूर्णांक query_status_size;
	पूर्णांक release_mem_size;
पूर्ण;

बाह्य स्थिर काष्ठा packet_manager_funcs kfd_vi_pm_funcs;
बाह्य स्थिर काष्ठा packet_manager_funcs kfd_v9_pm_funcs;

पूर्णांक pm_init(काष्ठा packet_manager *pm, काष्ठा device_queue_manager *dqm);
व्योम pm_uninit(काष्ठा packet_manager *pm, bool hanging);
पूर्णांक pm_send_set_resources(काष्ठा packet_manager *pm,
				काष्ठा scheduling_resources *res);
पूर्णांक pm_send_runlist(काष्ठा packet_manager *pm, काष्ठा list_head *dqm_queues);
पूर्णांक pm_send_query_status(काष्ठा packet_manager *pm, uपूर्णांक64_t fence_address,
				uपूर्णांक64_t fence_value);

पूर्णांक pm_send_unmap_queue(काष्ठा packet_manager *pm, क्रमागत kfd_queue_type type,
			क्रमागत kfd_unmap_queues_filter mode,
			uपूर्णांक32_t filter_param, bool reset,
			अचिन्हित पूर्णांक sdma_engine);

व्योम pm_release_ib(काष्ठा packet_manager *pm);

/* Following PM funcs can be shared among VI and AI */
अचिन्हित पूर्णांक pm_build_pm4_header(अचिन्हित पूर्णांक opcode, माप_प्रकार packet_size);

uपूर्णांक64_t kfd_get_number_elems(काष्ठा kfd_dev *kfd);

/* Events */
बाह्य स्थिर काष्ठा kfd_event_पूर्णांकerrupt_class event_पूर्णांकerrupt_class_cik;
बाह्य स्थिर काष्ठा kfd_event_पूर्णांकerrupt_class event_पूर्णांकerrupt_class_v9;

बाह्य स्थिर काष्ठा kfd_device_global_init_class device_global_init_class_cik;

व्योम kfd_event_init_process(काष्ठा kfd_process *p);
व्योम kfd_event_मुक्त_process(काष्ठा kfd_process *p);
पूर्णांक kfd_event_mmap(काष्ठा kfd_process *process, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक kfd_रुको_on_events(काष्ठा kfd_process *p,
		       uपूर्णांक32_t num_events, व्योम __user *data,
		       bool all, uपूर्णांक32_t user_समयout_ms,
		       uपूर्णांक32_t *रुको_result);
व्योम kfd_संकेत_event_पूर्णांकerrupt(u32 pasid, uपूर्णांक32_t partial_id,
				uपूर्णांक32_t valid_id_bits);
व्योम kfd_संकेत_iommu_event(काष्ठा kfd_dev *dev,
			    u32 pasid, अचिन्हित दीर्घ address,
			    bool is_ग_लिखो_requested, bool is_execute_requested);
व्योम kfd_संकेत_hw_exception_event(u32 pasid);
पूर्णांक kfd_set_event(काष्ठा kfd_process *p, uपूर्णांक32_t event_id);
पूर्णांक kfd_reset_event(काष्ठा kfd_process *p, uपूर्णांक32_t event_id);
पूर्णांक kfd_event_page_set(काष्ठा kfd_process *p, व्योम *kernel_address,
		       uपूर्णांक64_t size);
पूर्णांक kfd_event_create(काष्ठा file *devkfd, काष्ठा kfd_process *p,
		     uपूर्णांक32_t event_type, bool स्वतः_reset, uपूर्णांक32_t node_id,
		     uपूर्णांक32_t *event_id, uपूर्णांक32_t *event_trigger_data,
		     uपूर्णांक64_t *event_page_offset, uपूर्णांक32_t *event_slot_index);
पूर्णांक kfd_event_destroy(काष्ठा kfd_process *p, uपूर्णांक32_t event_id);

व्योम kfd_संकेत_vm_fault_event(काष्ठा kfd_dev *dev, u32 pasid,
				काष्ठा kfd_vm_fault_info *info);

व्योम kfd_संकेत_reset_event(काष्ठा kfd_dev *dev);

व्योम kfd_flush_tlb(काष्ठा kfd_process_device *pdd);

पूर्णांक dbgdev_wave_reset_wavefronts(काष्ठा kfd_dev *dev, काष्ठा kfd_process *p);

bool kfd_is_locked(व्योम);

/* Compute profile */
व्योम kfd_inc_compute_active(काष्ठा kfd_dev *dev);
व्योम kfd_dec_compute_active(काष्ठा kfd_dev *dev);

/* Cgroup Support */
/* Check with device cgroup अगर @kfd device is accessible */
अटल अंतरभूत पूर्णांक kfd_devcgroup_check_permission(काष्ठा kfd_dev *kfd)
अणु
#अगर defined(CONFIG_CGROUP_DEVICE) || defined(CONFIG_CGROUP_BPF)
	काष्ठा drm_device *ddev = kfd->ddev;

	वापस devcgroup_check_permission(DEVCG_DEV_CHAR, DRM_MAJOR,
					  ddev->render->index,
					  DEVCG_ACC_WRITE | DEVCG_ACC_READ);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* Debugfs */
#अगर defined(CONFIG_DEBUG_FS)

व्योम kfd_debugfs_init(व्योम);
व्योम kfd_debugfs_fini(व्योम);
पूर्णांक kfd_debugfs_mqds_by_process(काष्ठा seq_file *m, व्योम *data);
पूर्णांक pqm_debugfs_mqds(काष्ठा seq_file *m, व्योम *data);
पूर्णांक kfd_debugfs_hqds_by_device(काष्ठा seq_file *m, व्योम *data);
पूर्णांक dqm_debugfs_hqds(काष्ठा seq_file *m, व्योम *data);
पूर्णांक kfd_debugfs_rls_by_device(काष्ठा seq_file *m, व्योम *data);
पूर्णांक pm_debugfs_runlist(काष्ठा seq_file *m, व्योम *data);

पूर्णांक kfd_debugfs_hang_hws(काष्ठा kfd_dev *dev);
पूर्णांक pm_debugfs_hang_hws(काष्ठा packet_manager *pm);
पूर्णांक dqm_debugfs_execute_queues(काष्ठा device_queue_manager *dqm);

#अन्यथा

अटल अंतरभूत व्योम kfd_debugfs_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kfd_debugfs_fini(व्योम) अणुपूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
