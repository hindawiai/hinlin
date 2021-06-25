<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

#अगर_अघोषित _UAPI_LINUX_NITRO_ENCLAVES_H_
#घोषणा _UAPI_LINUX_NITRO_ENCLAVES_H_

#समावेश <linux/types.h>

/**
 * DOC: Nitro Enclaves (NE) Kernel Driver Interface
 */

/**
 * NE_CREATE_VM - The command is used to create a slot that is associated with
 *		  an enclave VM.
 *		  The generated unique slot id is an output parameter.
 *		  The ioctl can be invoked on the /dev/nitro_enclaves fd, beक्रमe
 *		  setting any resources, such as memory and vCPUs, क्रम an
 *		  enclave. Memory and vCPUs are set क्रम the slot mapped to an enclave.
 *		  A NE CPU pool has to be set beक्रमe calling this function. The
 *		  pool can be set after the NE driver load, using
 *		  /sys/module/nitro_enclaves/parameters/ne_cpus.
 *		  Its क्रमmat is the detailed in the cpu-lists section:
 *		  https://www.kernel.org/करोc/hपंचांगl/latest/admin-guide/kernel-parameters.hपंचांगl
 *		  CPU 0 and its siblings have to reमुख्य available क्रम the
 *		  primary / parent VM, so they cannot be set क्रम enclaves. Full
 *		  CPU core(s), from the same NUMA node, need(s) to be included
 *		  in the CPU pool.
 *
 * Context: Process context.
 * Return:
 * * Enclave file descriptor		- Enclave file descriptor used with
 *					  ioctl calls to set vCPUs and memory
 *					  regions, then start the enclave.
 * *  -1				- There was a failure in the ioctl logic.
 * On failure, त्रुटि_सं is set to:
 * * EFAULT				- copy_to_user() failure.
 * * ENOMEM				- Memory allocation failure क्रम पूर्णांकernal
 *					  bookkeeping variables.
 * * NE_ERR_NO_CPUS_AVAIL_IN_POOL	- No NE CPU pool set / no CPUs available
 *					  in the pool.
 * * Error codes from get_unused_fd_flags() and anon_inode_getfile().
 * * Error codes from the NE PCI device request.
 */
#घोषणा NE_CREATE_VM			_IOR(0xAE, 0x20, __u64)

/**
 * NE_ADD_VCPU - The command is used to set a vCPU क्रम an enclave. The vCPU can
 *		 be स्वतः-chosen from the NE CPU pool or it can be set by the
 *		 caller, with the note that it needs to be available in the NE
 *		 CPU pool. Full CPU core(s), from the same NUMA node, need(s) to
 *		 be associated with an enclave.
 *		 The vCPU id is an input / output parameter. If its value is 0,
 *		 then a CPU is chosen from the enclave CPU pool and वापसed via
 *		 this parameter.
 *		 The ioctl can be invoked on the enclave fd, beक्रमe an enclave
 *		 is started.
 *
 * Context: Process context.
 * Return:
 * * 0					- Logic succesfully completed.
 * *  -1				- There was a failure in the ioctl logic.
 * On failure, त्रुटि_सं is set to:
 * * EFAULT				- copy_from_user() / copy_to_user() failure.
 * * ENOMEM				- Memory allocation failure क्रम पूर्णांकernal
 *					  bookkeeping variables.
 * * EIO				- Current task mm is not the same as the one
 *					  that created the enclave.
 * * NE_ERR_NO_CPUS_AVAIL_IN_POOL	- No CPUs available in the NE CPU pool.
 * * NE_ERR_VCPU_ALREADY_USED		- The provided vCPU is alपढ़ोy used.
 * * NE_ERR_VCPU_NOT_IN_CPU_POOL	- The provided vCPU is not available in the
 *					  NE CPU pool.
 * * NE_ERR_VCPU_INVALID_CPU_CORE	- The core id of the provided vCPU is invalid
 *					  or out of range.
 * * NE_ERR_NOT_IN_INIT_STATE		- The enclave is not in init state
 *					  (init = beक्रमe being started).
 * * NE_ERR_INVALID_VCPU		- The provided vCPU is not in the available
 *					  CPUs range.
 * * Error codes from the NE PCI device request.
 */
#घोषणा NE_ADD_VCPU			_IOWR(0xAE, 0x21, __u32)

/**
 * NE_GET_IMAGE_LOAD_INFO - The command is used to get inक्रमmation needed क्रम
 *			    in-memory enclave image loading e.g. offset in
 *			    enclave memory to start placing the enclave image.
 *			    The image load info is an input / output parameter.
 *			    It includes info provided by the caller - flags -
 *			    and वापसs the offset in enclave memory where to
 *			    start placing the enclave image.
 *			    The ioctl can be invoked on the enclave fd, beक्रमe
 *			    an enclave is started.
 *
 * Context: Process context.
 * Return:
 * * 0				- Logic succesfully completed.
 * *  -1			- There was a failure in the ioctl logic.
 * On failure, त्रुटि_सं is set to:
 * * EFAULT			- copy_from_user() / copy_to_user() failure.
 * * NE_ERR_NOT_IN_INIT_STATE	- The enclave is not in init state (init =
 *				  beक्रमe being started).
 * * NE_ERR_INVALID_FLAG_VALUE	- The value of the provided flag is invalid.
 */
#घोषणा NE_GET_IMAGE_LOAD_INFO		_IOWR(0xAE, 0x22, काष्ठा ne_image_load_info)

/**
 * NE_SET_USER_MEMORY_REGION - The command is used to set a memory region क्रम an
 *			       enclave, given the allocated memory from the
 *			       userspace. Enclave memory needs to be from the
 *			       same NUMA node as the enclave CPUs.
 *			       The user memory region is an input parameter. It
 *			       includes info provided by the caller - flags,
 *			       memory size and userspace address.
 *			       The ioctl can be invoked on the enclave fd,
 *			       beक्रमe an enclave is started.
 *
 * Context: Process context.
 * Return:
 * * 0					- Logic succesfully completed.
 * *  -1				- There was a failure in the ioctl logic.
 * On failure, त्रुटि_सं is set to:
 * * EFAULT				- copy_from_user() failure.
 * * EINVAL				- Invalid physical memory region(s) e.g.
 *					  unaligned address.
 * * EIO				- Current task mm is not the same as
 *					  the one that created the enclave.
 * * ENOMEM				- Memory allocation failure क्रम पूर्णांकernal
 *					  bookkeeping variables.
 * * NE_ERR_NOT_IN_INIT_STATE		- The enclave is not in init state
 *					  (init = beक्रमe being started).
 * * NE_ERR_INVALID_MEM_REGION_SIZE	- The memory size of the region is not
 *					  multiple of 2 MiB.
 * * NE_ERR_INVALID_MEM_REGION_ADDR	- Invalid user space address given.
 * * NE_ERR_UNALIGNED_MEM_REGION_ADDR	- Unaligned user space address given.
 * * NE_ERR_MEM_REGION_ALREADY_USED	- The memory region is alपढ़ोy used.
 * * NE_ERR_MEM_NOT_HUGE_PAGE		- The memory region is not backed by
 *					  huge pages.
 * * NE_ERR_MEM_DIFFERENT_NUMA_NODE	- The memory region is not from the same
 *					  NUMA node as the CPUs.
 * * NE_ERR_MEM_MAX_REGIONS		- The number of memory regions set क्रम
 *					  the enclave reached maximum.
 * * NE_ERR_INVALID_PAGE_SIZE		- The memory region is not backed by
 *					  pages multiple of 2 MiB.
 * * NE_ERR_INVALID_FLAG_VALUE		- The value of the provided flag is invalid.
 * * Error codes from get_user_pages().
 * * Error codes from the NE PCI device request.
 */
#घोषणा NE_SET_USER_MEMORY_REGION	_IOW(0xAE, 0x23, काष्ठा ne_user_memory_region)

/**
 * NE_START_ENCLAVE - The command is used to trigger enclave start after the
 *		      enclave resources, such as memory and CPU, have been set.
 *		      The enclave start info is an input / output parameter. It
 *		      includes info provided by the caller - enclave cid and
 *		      flags - and वापसs the cid (अगर input cid is 0).
 *		      The ioctl can be invoked on the enclave fd, after an
 *		      enclave slot is created and resources, such as memory and
 *		      vCPUs are set क्रम an enclave.
 *
 * Context: Process context.
 * Return:
 * * 0					- Logic succesfully completed.
 * *  -1				- There was a failure in the ioctl logic.
 * On failure, त्रुटि_सं is set to:
 * * EFAULT				- copy_from_user() / copy_to_user() failure.
 * * NE_ERR_NOT_IN_INIT_STATE		- The enclave is not in init state
 *					  (init = beक्रमe being started).
 * * NE_ERR_NO_MEM_REGIONS_ADDED	- No memory regions are set.
 * * NE_ERR_NO_VCPUS_ADDED		- No vCPUs are set.
 * *  NE_ERR_FULL_CORES_NOT_USED	- Full core(s) not set क्रम the enclave.
 * * NE_ERR_ENCLAVE_MEM_MIN_SIZE	- Enclave memory is less than minimum
 *					  memory size (64 MiB).
 * * NE_ERR_INVALID_FLAG_VALUE		- The value of the provided flag is invalid.
 * *  NE_ERR_INVALID_ENCLAVE_CID	- The provided enclave CID is invalid.
 * * Error codes from the NE PCI device request.
 */
#घोषणा NE_START_ENCLAVE		_IOWR(0xAE, 0x24, काष्ठा ne_enclave_start_info)

/**
 * DOC: NE specअगरic error codes
 */

/**
 * NE_ERR_VCPU_ALREADY_USED - The provided vCPU is alपढ़ोy used.
 */
#घोषणा NE_ERR_VCPU_ALREADY_USED		(256)
/**
 * NE_ERR_VCPU_NOT_IN_CPU_POOL - The provided vCPU is not available in the
 *				 NE CPU pool.
 */
#घोषणा NE_ERR_VCPU_NOT_IN_CPU_POOL		(257)
/**
 * NE_ERR_VCPU_INVALID_CPU_CORE - The core id of the provided vCPU is invalid
 *				  or out of range of the NE CPU pool.
 */
#घोषणा NE_ERR_VCPU_INVALID_CPU_CORE		(258)
/**
 * NE_ERR_INVALID_MEM_REGION_SIZE - The user space memory region size is not
 *				    multiple of 2 MiB.
 */
#घोषणा NE_ERR_INVALID_MEM_REGION_SIZE		(259)
/**
 * NE_ERR_INVALID_MEM_REGION_ADDR - The user space memory region address range
 *				    is invalid.
 */
#घोषणा NE_ERR_INVALID_MEM_REGION_ADDR		(260)
/**
 * NE_ERR_UNALIGNED_MEM_REGION_ADDR - The user space memory region address is
 *				      not aligned.
 */
#घोषणा NE_ERR_UNALIGNED_MEM_REGION_ADDR	(261)
/**
 * NE_ERR_MEM_REGION_ALREADY_USED - The user space memory region is alपढ़ोy used.
 */
#घोषणा NE_ERR_MEM_REGION_ALREADY_USED		(262)
/**
 * NE_ERR_MEM_NOT_HUGE_PAGE - The user space memory region is not backed by
 *			      contiguous physical huge page(s).
 */
#घोषणा NE_ERR_MEM_NOT_HUGE_PAGE		(263)
/**
 * NE_ERR_MEM_DIFFERENT_NUMA_NODE - The user space memory region is backed by
 *				    pages from dअगरferent NUMA nodes than the CPUs.
 */
#घोषणा NE_ERR_MEM_DIFFERENT_NUMA_NODE		(264)
/**
 * NE_ERR_MEM_MAX_REGIONS - The supported max memory regions per enclaves has
 *			    been reached.
 */
#घोषणा NE_ERR_MEM_MAX_REGIONS			(265)
/**
 * NE_ERR_NO_MEM_REGIONS_ADDED - The command to start an enclave is triggered
 *				 and no memory regions are added.
 */
#घोषणा NE_ERR_NO_MEM_REGIONS_ADDED		(266)
/**
 * NE_ERR_NO_VCPUS_ADDED - The command to start an enclave is triggered and no
 *			   vCPUs are added.
 */
#घोषणा NE_ERR_NO_VCPUS_ADDED			(267)
/**
 * NE_ERR_ENCLAVE_MEM_MIN_SIZE - The enclave memory size is lower than the
 *				 minimum supported.
 */
#घोषणा NE_ERR_ENCLAVE_MEM_MIN_SIZE		(268)
/**
 * NE_ERR_FULL_CORES_NOT_USED - The command to start an enclave is triggered and
 *				full CPU cores are not set.
 */
#घोषणा NE_ERR_FULL_CORES_NOT_USED		(269)
/**
 * NE_ERR_NOT_IN_INIT_STATE - The enclave is not in init state when setting
 *			      resources or triggering start.
 */
#घोषणा NE_ERR_NOT_IN_INIT_STATE		(270)
/**
 * NE_ERR_INVALID_VCPU - The provided vCPU is out of range of the available CPUs.
 */
#घोषणा NE_ERR_INVALID_VCPU			(271)
/**
 * NE_ERR_NO_CPUS_AVAIL_IN_POOL - The command to create an enclave is triggered
 *				  and no CPUs are available in the pool.
 */
#घोषणा NE_ERR_NO_CPUS_AVAIL_IN_POOL		(272)
/**
 * NE_ERR_INVALID_PAGE_SIZE - The user space memory region is not backed by pages
 *			      multiple of 2 MiB.
 */
#घोषणा NE_ERR_INVALID_PAGE_SIZE		(273)
/**
 * NE_ERR_INVALID_FLAG_VALUE - The provided flag value is invalid.
 */
#घोषणा NE_ERR_INVALID_FLAG_VALUE		(274)
/**
 * NE_ERR_INVALID_ENCLAVE_CID - The provided enclave CID is invalid, either
 *				being a well-known value or the CID of the
 *				parent / primary VM.
 */
#घोषणा NE_ERR_INVALID_ENCLAVE_CID		(275)

/**
 * DOC: Image load info flags
 */

/**
 * NE_EIF_IMAGE - Enclave Image Format (EIF)
 */
#घोषणा NE_EIF_IMAGE			(0x01)

#घोषणा NE_IMAGE_LOAD_MAX_FLAG_VAL	(0x02)

/**
 * काष्ठा ne_image_load_info - Info necessary क्रम in-memory enclave image
 *			       loading (in / out).
 * @flags:		Flags to determine the enclave image type
 *			(e.g. Enclave Image Format - EIF) (in).
 * @memory_offset:	Offset in enclave memory where to start placing the
 *			enclave image (out).
 */
काष्ठा ne_image_load_info अणु
	__u64	flags;
	__u64	memory_offset;
पूर्ण;

/**
 * DOC: User memory region flags
 */

/**
 * NE_DEFAULT_MEMORY_REGION - Memory region क्रम enclave general usage.
 */
#घोषणा NE_DEFAULT_MEMORY_REGION	(0x00)

#घोषणा NE_MEMORY_REGION_MAX_FLAG_VAL	(0x01)

/**
 * काष्ठा ne_user_memory_region - Memory region to be set क्रम an enclave (in).
 * @flags:		Flags to determine the usage क्रम the memory region (in).
 * @memory_size:	The size, in bytes, of the memory region to be set क्रम
 *			an enclave (in).
 * @userspace_addr:	The start address of the userspace allocated memory of
 *			the memory region to set क्रम an enclave (in).
 */
काष्ठा ne_user_memory_region अणु
	__u64	flags;
	__u64	memory_size;
	__u64	userspace_addr;
पूर्ण;

/**
 * DOC: Enclave start info flags
 */

/**
 * NE_ENCLAVE_PRODUCTION_MODE - Start enclave in production mode.
 */
#घोषणा NE_ENCLAVE_PRODUCTION_MODE	(0x00)
/**
 * NE_ENCLAVE_DEBUG_MODE - Start enclave in debug mode.
 */
#घोषणा NE_ENCLAVE_DEBUG_MODE		(0x01)

#घोषणा NE_ENCLAVE_START_MAX_FLAG_VAL	(0x02)

/**
 * काष्ठा ne_enclave_start_info - Setup info necessary क्रम enclave start (in / out).
 * @flags:		Flags क्रम the enclave to start with (e.g. debug mode) (in).
 * @enclave_cid:	Context ID (CID) क्रम the enclave vsock device. If 0 as
 *			input, the CID is स्वतःgenerated by the hypervisor and
 *			वापसed back as output by the driver (in / out).
 */
काष्ठा ne_enclave_start_info अणु
	__u64	flags;
	__u64	enclave_cid;
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_NITRO_ENCLAVES_H_ */
