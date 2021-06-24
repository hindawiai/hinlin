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

#अगर_अघोषित KFD_IOCTL_H_INCLUDED
#घोषणा KFD_IOCTL_H_INCLUDED

#समावेश <drm/drm.h>
#समावेश <linux/ioctl.h>

/*
 * - 1.1 - initial version
 * - 1.3 - Add SMI events support
 * - 1.4 - Indicate new SRAM EDC bit in device properties
 */
#घोषणा KFD_IOCTL_MAJOR_VERSION 1
#घोषणा KFD_IOCTL_MINOR_VERSION 4

काष्ठा kfd_ioctl_get_version_args अणु
	__u32 major_version;	/* from KFD */
	__u32 minor_version;	/* from KFD */
पूर्ण;

/* For kfd_ioctl_create_queue_args.queue_type. */
#घोषणा KFD_IOC_QUEUE_TYPE_COMPUTE		0x0
#घोषणा KFD_IOC_QUEUE_TYPE_SDMA			0x1
#घोषणा KFD_IOC_QUEUE_TYPE_COMPUTE_AQL		0x2
#घोषणा KFD_IOC_QUEUE_TYPE_SDMA_XGMI		0x3

#घोषणा KFD_MAX_QUEUE_PERCENTAGE	100
#घोषणा KFD_MAX_QUEUE_PRIORITY		15

काष्ठा kfd_ioctl_create_queue_args अणु
	__u64 ring_base_address;	/* to KFD */
	__u64 ग_लिखो_poपूर्णांकer_address;	/* from KFD */
	__u64 पढ़ो_poपूर्णांकer_address;	/* from KFD */
	__u64 करोorbell_offset;	/* from KFD */

	__u32 ring_size;		/* to KFD */
	__u32 gpu_id;		/* to KFD */
	__u32 queue_type;		/* to KFD */
	__u32 queue_percentage;	/* to KFD */
	__u32 queue_priority;	/* to KFD */
	__u32 queue_id;		/* from KFD */

	__u64 eop_buffer_address;	/* to KFD */
	__u64 eop_buffer_size;	/* to KFD */
	__u64 ctx_save_restore_address; /* to KFD */
	__u32 ctx_save_restore_size;	/* to KFD */
	__u32 ctl_stack_size;		/* to KFD */
पूर्ण;

काष्ठा kfd_ioctl_destroy_queue_args अणु
	__u32 queue_id;		/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_update_queue_args अणु
	__u64 ring_base_address;	/* to KFD */

	__u32 queue_id;		/* to KFD */
	__u32 ring_size;		/* to KFD */
	__u32 queue_percentage;	/* to KFD */
	__u32 queue_priority;	/* to KFD */
पूर्ण;

काष्ठा kfd_ioctl_set_cu_mask_args अणु
	__u32 queue_id;		/* to KFD */
	__u32 num_cu_mask;		/* to KFD */
	__u64 cu_mask_ptr;		/* to KFD */
पूर्ण;

काष्ठा kfd_ioctl_get_queue_wave_state_args अणु
	__u64 ctl_stack_address;	/* to KFD */
	__u32 ctl_stack_used_size;	/* from KFD */
	__u32 save_area_used_size;	/* from KFD */
	__u32 queue_id;			/* to KFD */
	__u32 pad;
पूर्ण;

/* For kfd_ioctl_set_memory_policy_args.शेष_policy and alternate_policy */
#घोषणा KFD_IOC_CACHE_POLICY_COHERENT 0
#घोषणा KFD_IOC_CACHE_POLICY_NONCOHERENT 1

काष्ठा kfd_ioctl_set_memory_policy_args अणु
	__u64 alternate_aperture_base;	/* to KFD */
	__u64 alternate_aperture_size;	/* to KFD */

	__u32 gpu_id;			/* to KFD */
	__u32 शेष_policy;		/* to KFD */
	__u32 alternate_policy;		/* to KFD */
	__u32 pad;
पूर्ण;

/*
 * All counters are monotonic. They are used क्रम profiling of compute jobs.
 * The profiling is करोne by userspace.
 *
 * In हाल of GPU reset, the counter should not be affected.
 */

काष्ठा kfd_ioctl_get_घड़ी_counters_args अणु
	__u64 gpu_घड़ी_counter;	/* from KFD */
	__u64 cpu_घड़ी_counter;	/* from KFD */
	__u64 प्रणाली_घड़ी_counter;	/* from KFD */
	__u64 प्रणाली_घड़ी_freq;	/* from KFD */

	__u32 gpu_id;		/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_process_device_apertures अणु
	__u64 lds_base;		/* from KFD */
	__u64 lds_limit;		/* from KFD */
	__u64 scratch_base;		/* from KFD */
	__u64 scratch_limit;		/* from KFD */
	__u64 gpuvm_base;		/* from KFD */
	__u64 gpuvm_limit;		/* from KFD */
	__u32 gpu_id;		/* from KFD */
	__u32 pad;
पूर्ण;

/*
 * AMDKFD_IOC_GET_PROCESS_APERTURES is deprecated. Use
 * AMDKFD_IOC_GET_PROCESS_APERTURES_NEW instead, which supports an
 * unlimited number of GPUs.
 */
#घोषणा NUM_OF_SUPPORTED_GPUS 7
काष्ठा kfd_ioctl_get_process_apertures_args अणु
	काष्ठा kfd_process_device_apertures
			process_apertures[NUM_OF_SUPPORTED_GPUS];/* from KFD */

	/* from KFD, should be in the range [1 - NUM_OF_SUPPORTED_GPUS] */
	__u32 num_of_nodes;
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_get_process_apertures_new_args अणु
	/* User allocated. Poपूर्णांकer to काष्ठा kfd_process_device_apertures
	 * filled in by Kernel
	 */
	__u64 kfd_process_device_apertures_ptr;
	/* to KFD - indicates amount of memory present in
	 *  kfd_process_device_apertures_ptr
	 * from KFD - Number of entries filled by KFD.
	 */
	__u32 num_of_nodes;
	__u32 pad;
पूर्ण;

#घोषणा MAX_ALLOWED_NUM_POINTS    100
#घोषणा MAX_ALLOWED_AW_BUFF_SIZE 4096
#घोषणा MAX_ALLOWED_WAC_BUFF_SIZE  128

काष्ठा kfd_ioctl_dbg_रेजिस्टर_args अणु
	__u32 gpu_id;		/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_dbg_unरेजिस्टर_args अणु
	__u32 gpu_id;		/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_dbg_address_watch_args अणु
	__u64 content_ptr;		/* a poपूर्णांकer to the actual content */
	__u32 gpu_id;		/* to KFD */
	__u32 buf_size_in_bytes;	/*including gpu_id and buf_size */
पूर्ण;

काष्ठा kfd_ioctl_dbg_wave_control_args अणु
	__u64 content_ptr;		/* a poपूर्णांकer to the actual content */
	__u32 gpu_id;		/* to KFD */
	__u32 buf_size_in_bytes;	/*including gpu_id and buf_size */
पूर्ण;

/* Matching HSA_EVENTTYPE */
#घोषणा KFD_IOC_EVENT_SIGNAL			0
#घोषणा KFD_IOC_EVENT_NODECHANGE		1
#घोषणा KFD_IOC_EVENT_DEVICESTATECHANGE		2
#घोषणा KFD_IOC_EVENT_HW_EXCEPTION		3
#घोषणा KFD_IOC_EVENT_SYSTEM_EVENT		4
#घोषणा KFD_IOC_EVENT_DEBUG_EVENT		5
#घोषणा KFD_IOC_EVENT_PROखाता_EVENT		6
#घोषणा KFD_IOC_EVENT_QUEUE_EVENT		7
#घोषणा KFD_IOC_EVENT_MEMORY			8

#घोषणा KFD_IOC_WAIT_RESULT_COMPLETE		0
#घोषणा KFD_IOC_WAIT_RESULT_TIMEOUT		1
#घोषणा KFD_IOC_WAIT_RESULT_FAIL		2

#घोषणा KFD_SIGNAL_EVENT_LIMIT			4096

/* For kfd_event_data.hw_exception_data.reset_type. */
#घोषणा KFD_HW_EXCEPTION_WHOLE_GPU_RESET	0
#घोषणा KFD_HW_EXCEPTION_PER_ENGINE_RESET	1

/* For kfd_event_data.hw_exception_data.reset_cause. */
#घोषणा KFD_HW_EXCEPTION_GPU_HANG	0
#घोषणा KFD_HW_EXCEPTION_ECC		1

/* For kfd_hsa_memory_exception_data.ErrorType */
#घोषणा KFD_MEM_ERR_NO_RAS		0
#घोषणा KFD_MEM_ERR_SRAM_ECC		1
#घोषणा KFD_MEM_ERR_POISON_CONSUMED	2
#घोषणा KFD_MEM_ERR_GPU_HANG		3

काष्ठा kfd_ioctl_create_event_args अणु
	__u64 event_page_offset;	/* from KFD */
	__u32 event_trigger_data;	/* from KFD - संकेत events only */
	__u32 event_type;		/* to KFD */
	__u32 स्वतः_reset;		/* to KFD */
	__u32 node_id;		/* to KFD - only valid क्रम certain
							event types */
	__u32 event_id;		/* from KFD */
	__u32 event_slot_index;	/* from KFD */
पूर्ण;

काष्ठा kfd_ioctl_destroy_event_args अणु
	__u32 event_id;		/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_set_event_args अणु
	__u32 event_id;		/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_reset_event_args अणु
	__u32 event_id;		/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_memory_exception_failure अणु
	__u32 NotPresent;	/* Page not present or supervisor privilege */
	__u32 ReadOnly;	/* Write access to a पढ़ो-only page */
	__u32 NoExecute;	/* Execute access to a page marked NX */
	__u32 imprecise;	/* Can't determine the	exact fault address */
पूर्ण;

/* memory exception data */
काष्ठा kfd_hsa_memory_exception_data अणु
	काष्ठा kfd_memory_exception_failure failure;
	__u64 va;
	__u32 gpu_id;
	__u32 ErrorType; /* 0 = no RAS error,
			  * 1 = ECC_SRAM,
			  * 2 = Link_SYNFLOOD (poison),
			  * 3 = GPU hang (not attributable to a specअगरic cause),
			  * other values reserved
			  */
पूर्ण;

/* hw exception data */
काष्ठा kfd_hsa_hw_exception_data अणु
	__u32 reset_type;
	__u32 reset_cause;
	__u32 memory_lost;
	__u32 gpu_id;
पूर्ण;

/* Event data */
काष्ठा kfd_event_data अणु
	जोड़ अणु
		काष्ठा kfd_hsa_memory_exception_data memory_exception_data;
		काष्ठा kfd_hsa_hw_exception_data hw_exception_data;
	पूर्ण;				/* From KFD */
	__u64 kfd_event_data_ext;	/* poपूर्णांकer to an extension काष्ठाure
					   क्रम future exception types */
	__u32 event_id;		/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_रुको_events_args अणु
	__u64 events_ptr;		/* poपूर्णांकed to काष्ठा
					   kfd_event_data array, to KFD */
	__u32 num_events;		/* to KFD */
	__u32 रुको_क्रम_all;		/* to KFD */
	__u32 समयout;		/* to KFD */
	__u32 रुको_result;		/* from KFD */
पूर्ण;

काष्ठा kfd_ioctl_set_scratch_backing_बहु_तर्कs अणु
	__u64 va_addr;	/* to KFD */
	__u32 gpu_id;	/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_get_tile_config_args अणु
	/* to KFD: poपूर्णांकer to tile array */
	__u64 tile_config_ptr;
	/* to KFD: poपूर्णांकer to macro tile array */
	__u64 macro_tile_config_ptr;
	/* to KFD: array size allocated by user mode
	 * from KFD: array size filled by kernel
	 */
	__u32 num_tile_configs;
	/* to KFD: array size allocated by user mode
	 * from KFD: array size filled by kernel
	 */
	__u32 num_macro_tile_configs;

	__u32 gpu_id;		/* to KFD */
	__u32 gb_addr_config;	/* from KFD */
	__u32 num_banks;		/* from KFD */
	__u32 num_ranks;		/* from KFD */
	/* काष्ठा size can be extended later अगर needed
	 * without अवरोधing ABI compatibility
	 */
पूर्ण;

काष्ठा kfd_ioctl_set_trap_handler_args अणु
	__u64 tba_addr;		/* to KFD */
	__u64 पंचांगa_addr;		/* to KFD */
	__u32 gpu_id;		/* to KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_acquire_vm_args अणु
	__u32 drm_fd;	/* to KFD */
	__u32 gpu_id;	/* to KFD */
पूर्ण;

/* Allocation flags: memory types */
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_VRAM		(1 << 0)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_GTT		(1 << 1)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_USERPTR		(1 << 2)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_DOORBELL	(1 << 3)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_MMIO_REMAP	(1 << 4)
/* Allocation flags: attributes/access options */
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_WRITABLE	(1 << 31)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_EXECUTABLE	(1 << 30)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_PUBLIC		(1 << 29)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_NO_SUBSTITUTE	(1 << 28)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_AQL_QUEUE_MEM	(1 << 27)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_COHERENT	(1 << 26)
#घोषणा KFD_IOC_ALLOC_MEM_FLAGS_UNCACHED	(1 << 25)

/* Allocate memory क्रम later SVM (shared भव memory) mapping.
 *
 * @va_addr:     भव address of the memory to be allocated
 *               all later mappings on all GPUs will use this address
 * @size:        size in bytes
 * @handle:      buffer handle वापसed to user mode, used to refer to
 *               this allocation क्रम mapping, unmapping and मुक्तing
 * @mmap_offset: क्रम CPU-mapping the allocation by mmapping a render node
 *               क्रम userptrs this is overloaded to specअगरy the CPU address
 * @gpu_id:      device identअगरier
 * @flags:       memory type and attributes. See KFD_IOC_ALLOC_MEM_FLAGS above
 */
काष्ठा kfd_ioctl_alloc_memory_of_gpu_args अणु
	__u64 va_addr;		/* to KFD */
	__u64 size;		/* to KFD */
	__u64 handle;		/* from KFD */
	__u64 mmap_offset;	/* to KFD (userptr), from KFD (mmap offset) */
	__u32 gpu_id;		/* to KFD */
	__u32 flags;
पूर्ण;

/* Free memory allocated with kfd_ioctl_alloc_memory_of_gpu
 *
 * @handle: memory handle वापसed by alloc
 */
काष्ठा kfd_ioctl_मुक्त_memory_of_gpu_args अणु
	__u64 handle;		/* to KFD */
पूर्ण;

/* Map memory to one or more GPUs
 *
 * @handle:                memory handle वापसed by alloc
 * @device_ids_array_ptr:  array of gpu_ids (__u32 per device)
 * @n_devices:             number of devices in the array
 * @n_success:             number of devices mapped successfully
 *
 * @n_success वापसs inक्रमmation to the caller how many devices from
 * the start of the array have mapped the buffer successfully. It can
 * be passed पूर्णांकo a subsequent retry call to skip those devices. For
 * the first call the caller should initialize it to 0.
 *
 * If the ioctl completes with वापस code 0 (success), n_success ==
 * n_devices.
 */
काष्ठा kfd_ioctl_map_memory_to_gpu_args अणु
	__u64 handle;			/* to KFD */
	__u64 device_ids_array_ptr;	/* to KFD */
	__u32 n_devices;		/* to KFD */
	__u32 n_success;		/* to/from KFD */
पूर्ण;

/* Unmap memory from one or more GPUs
 *
 * same arguments as क्रम mapping
 */
काष्ठा kfd_ioctl_unmap_memory_from_gpu_args अणु
	__u64 handle;			/* to KFD */
	__u64 device_ids_array_ptr;	/* to KFD */
	__u32 n_devices;		/* to KFD */
	__u32 n_success;		/* to/from KFD */
पूर्ण;

/* Allocate GWS क्रम specअगरic queue
 *
 * @queue_id:    queue's id that GWS is allocated क्रम
 * @num_gws:     how many GWS to allocate
 * @first_gws:   index of the first GWS allocated.
 *               only support contiguous GWS allocation
 */
काष्ठा kfd_ioctl_alloc_queue_gws_args अणु
	__u32 queue_id;		/* to KFD */
	__u32 num_gws;		/* to KFD */
	__u32 first_gws;	/* from KFD */
	__u32 pad;
पूर्ण;

काष्ठा kfd_ioctl_get_dmabuf_info_args अणु
	__u64 size;		/* from KFD */
	__u64 metadata_ptr;	/* to KFD */
	__u32 metadata_size;	/* to KFD (space allocated by user)
				 * from KFD (actual metadata size)
				 */
	__u32 gpu_id;	/* from KFD */
	__u32 flags;		/* from KFD (KFD_IOC_ALLOC_MEM_FLAGS) */
	__u32 dmabuf_fd;	/* to KFD */
पूर्ण;

काष्ठा kfd_ioctl_import_dmabuf_args अणु
	__u64 va_addr;	/* to KFD */
	__u64 handle;	/* from KFD */
	__u32 gpu_id;	/* to KFD */
	__u32 dmabuf_fd;	/* to KFD */
पूर्ण;

/*
 * KFD SMI(System Management Interface) events
 */
क्रमागत kfd_smi_event अणु
	KFD_SMI_EVENT_NONE = 0, /* not used */
	KFD_SMI_EVENT_VMFAULT = 1, /* event start counting at 1 */
	KFD_SMI_EVENT_THERMAL_THROTTLE = 2,
	KFD_SMI_EVENT_GPU_PRE_RESET = 3,
	KFD_SMI_EVENT_GPU_POST_RESET = 4,
पूर्ण;

#घोषणा KFD_SMI_EVENT_MASK_FROM_INDEX(i) (1ULL << ((i) - 1))

काष्ठा kfd_ioctl_smi_events_args अणु
	__u32 gpuid;	/* to KFD */
	__u32 anon_fd;	/* from KFD */
पूर्ण;

/* Register offset inside the remapped mmio page
 */
क्रमागत kfd_mmio_remap अणु
	KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL = 0,
	KFD_MMIO_REMAP_HDP_REG_FLUSH_CNTL = 4,
पूर्ण;

#घोषणा AMDKFD_IOCTL_BASE 'K'
#घोषणा AMDKFD_IO(nr)			_IO(AMDKFD_IOCTL_BASE, nr)
#घोषणा AMDKFD_IOR(nr, type)		_IOR(AMDKFD_IOCTL_BASE, nr, type)
#घोषणा AMDKFD_IOW(nr, type)		_IOW(AMDKFD_IOCTL_BASE, nr, type)
#घोषणा AMDKFD_IOWR(nr, type)		_IOWR(AMDKFD_IOCTL_BASE, nr, type)

#घोषणा AMDKFD_IOC_GET_VERSION			\
		AMDKFD_IOR(0x01, काष्ठा kfd_ioctl_get_version_args)

#घोषणा AMDKFD_IOC_CREATE_QUEUE			\
		AMDKFD_IOWR(0x02, काष्ठा kfd_ioctl_create_queue_args)

#घोषणा AMDKFD_IOC_DESTROY_QUEUE		\
		AMDKFD_IOWR(0x03, काष्ठा kfd_ioctl_destroy_queue_args)

#घोषणा AMDKFD_IOC_SET_MEMORY_POLICY		\
		AMDKFD_IOW(0x04, काष्ठा kfd_ioctl_set_memory_policy_args)

#घोषणा AMDKFD_IOC_GET_CLOCK_COUNTERS		\
		AMDKFD_IOWR(0x05, काष्ठा kfd_ioctl_get_घड़ी_counters_args)

#घोषणा AMDKFD_IOC_GET_PROCESS_APERTURES	\
		AMDKFD_IOR(0x06, काष्ठा kfd_ioctl_get_process_apertures_args)

#घोषणा AMDKFD_IOC_UPDATE_QUEUE			\
		AMDKFD_IOW(0x07, काष्ठा kfd_ioctl_update_queue_args)

#घोषणा AMDKFD_IOC_CREATE_EVENT			\
		AMDKFD_IOWR(0x08, काष्ठा kfd_ioctl_create_event_args)

#घोषणा AMDKFD_IOC_DESTROY_EVENT		\
		AMDKFD_IOW(0x09, काष्ठा kfd_ioctl_destroy_event_args)

#घोषणा AMDKFD_IOC_SET_EVENT			\
		AMDKFD_IOW(0x0A, काष्ठा kfd_ioctl_set_event_args)

#घोषणा AMDKFD_IOC_RESET_EVENT			\
		AMDKFD_IOW(0x0B, काष्ठा kfd_ioctl_reset_event_args)

#घोषणा AMDKFD_IOC_WAIT_EVENTS			\
		AMDKFD_IOWR(0x0C, काष्ठा kfd_ioctl_रुको_events_args)

#घोषणा AMDKFD_IOC_DBG_REGISTER			\
		AMDKFD_IOW(0x0D, काष्ठा kfd_ioctl_dbg_रेजिस्टर_args)

#घोषणा AMDKFD_IOC_DBG_UNREGISTER		\
		AMDKFD_IOW(0x0E, काष्ठा kfd_ioctl_dbg_unरेजिस्टर_args)

#घोषणा AMDKFD_IOC_DBG_ADDRESS_WATCH		\
		AMDKFD_IOW(0x0F, काष्ठा kfd_ioctl_dbg_address_watch_args)

#घोषणा AMDKFD_IOC_DBG_WAVE_CONTROL		\
		AMDKFD_IOW(0x10, काष्ठा kfd_ioctl_dbg_wave_control_args)

#घोषणा AMDKFD_IOC_SET_SCRATCH_BACKING_VA	\
		AMDKFD_IOWR(0x11, काष्ठा kfd_ioctl_set_scratch_backing_बहु_तर्कs)

#घोषणा AMDKFD_IOC_GET_TILE_CONFIG                                      \
		AMDKFD_IOWR(0x12, काष्ठा kfd_ioctl_get_tile_config_args)

#घोषणा AMDKFD_IOC_SET_TRAP_HANDLER		\
		AMDKFD_IOW(0x13, काष्ठा kfd_ioctl_set_trap_handler_args)

#घोषणा AMDKFD_IOC_GET_PROCESS_APERTURES_NEW	\
		AMDKFD_IOWR(0x14,		\
			काष्ठा kfd_ioctl_get_process_apertures_new_args)

#घोषणा AMDKFD_IOC_ACQUIRE_VM			\
		AMDKFD_IOW(0x15, काष्ठा kfd_ioctl_acquire_vm_args)

#घोषणा AMDKFD_IOC_ALLOC_MEMORY_OF_GPU		\
		AMDKFD_IOWR(0x16, काष्ठा kfd_ioctl_alloc_memory_of_gpu_args)

#घोषणा AMDKFD_IOC_FREE_MEMORY_OF_GPU		\
		AMDKFD_IOW(0x17, काष्ठा kfd_ioctl_मुक्त_memory_of_gpu_args)

#घोषणा AMDKFD_IOC_MAP_MEMORY_TO_GPU		\
		AMDKFD_IOWR(0x18, काष्ठा kfd_ioctl_map_memory_to_gpu_args)

#घोषणा AMDKFD_IOC_UNMAP_MEMORY_FROM_GPU	\
		AMDKFD_IOWR(0x19, काष्ठा kfd_ioctl_unmap_memory_from_gpu_args)

#घोषणा AMDKFD_IOC_SET_CU_MASK		\
		AMDKFD_IOW(0x1A, काष्ठा kfd_ioctl_set_cu_mask_args)

#घोषणा AMDKFD_IOC_GET_QUEUE_WAVE_STATE		\
		AMDKFD_IOWR(0x1B, काष्ठा kfd_ioctl_get_queue_wave_state_args)

#घोषणा AMDKFD_IOC_GET_DMABUF_INFO		\
		AMDKFD_IOWR(0x1C, काष्ठा kfd_ioctl_get_dmabuf_info_args)

#घोषणा AMDKFD_IOC_IMPORT_DMABUF		\
		AMDKFD_IOWR(0x1D, काष्ठा kfd_ioctl_import_dmabuf_args)

#घोषणा AMDKFD_IOC_ALLOC_QUEUE_GWS		\
		AMDKFD_IOWR(0x1E, काष्ठा kfd_ioctl_alloc_queue_gws_args)

#घोषणा AMDKFD_IOC_SMI_EVENTS			\
		AMDKFD_IOWR(0x1F, काष्ठा kfd_ioctl_smi_events_args)

#घोषणा AMDKFD_COMMAND_START		0x01
#घोषणा AMDKFD_COMMAND_END		0x20

#पूर्ण_अगर
