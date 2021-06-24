<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

/**
 * DOC: Sample flow of using the ioctl पूर्णांकerface provided by the Nitro Enclaves (NE)
 * kernel driver.
 *
 * Usage
 * -----
 *
 * Load the nitro_enclaves module, setting also the enclave CPU pool. The
 * enclave CPUs need to be full cores from the same NUMA node. CPU 0 and its
 * siblings have to reमुख्य available क्रम the primary / parent VM, so they
 * cannot be included in the enclave CPU pool.
 *
 * See the cpu list section from the kernel करोcumentation.
 * https://www.kernel.org/करोc/hपंचांगl/latest/admin-guide/kernel-parameters.hपंचांगl#cpu-lists
 *
 *	insmod drivers/virt/nitro_enclaves/nitro_enclaves.ko
 *	lsmod
 *
 *	The CPU pool can be set at runसमय, after the kernel module is loaded.
 *
 *	echo <cpu-list> > /sys/module/nitro_enclaves/parameters/ne_cpus
 *
 *	NUMA and CPU siblings inक्रमmation can be found using:
 *
 *	lscpu
 *	/proc/cpuinfo
 *
 * Check the online / offline CPU list. The CPUs from the pool should be
 * offlined.
 *
 *	lscpu
 *
 * Check dmesg क्रम any warnings / errors through the NE driver lअगरeसमय / usage.
 * The NE logs contain the "nitro_enclaves" or "pci 0000:00:02.0" pattern.
 *
 *	dmesg
 *
 * Setup hugetlbfs huge pages. The memory needs to be from the same NUMA node as
 * the enclave CPUs.
 *
 * https://www.kernel.org/करोc/hपंचांगl/latest/admin-guide/mm/hugetlbpage.hपंचांगl
 *
 * By शेष, the allocation of hugetlb pages are distributed on all possible
 * NUMA nodes. Use the following configuration files to set the number of huge
 * pages from a NUMA node:
 *
 *	/sys/devices/प्रणाली/node/node<X>/hugepages/hugepages-2048kB/nr_hugepages
 *	/sys/devices/प्रणाली/node/node<X>/hugepages/hugepages-1048576kB/nr_hugepages
 *
 *	or, अगर not on a प्रणाली with multiple NUMA nodes, can also set the number
 *	of 2 MiB / 1 GiB huge pages using
 *
 *	/sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
 *	/sys/kernel/mm/hugepages/hugepages-1048576kB/nr_hugepages
 *
 *	In this example 256 hugepages of 2 MiB are used.
 *
 * Build and run the NE sample.
 *
 *	make -C samples/nitro_enclaves clean
 *	make -C samples/nitro_enclaves
 *	./samples/nitro_enclaves/ne_ioctl_sample <path_to_enclave_image>
 *
 * Unload the nitro_enclaves module.
 *
 *	rmmod nitro_enclaves
 *	lsmod
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <poll.h>
#समावेश <pthपढ़ो.h>
#समावेश <माला.स>
#समावेश <sys/eventfd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#समावेश <linux/mman.h>
#समावेश <linux/nitro_enclaves.h>
#समावेश <linux/vm_sockets.h>

/**
 * NE_DEV_NAME - Nitro Enclaves (NE) misc device that provides the ioctl पूर्णांकerface.
 */
#घोषणा NE_DEV_NAME			"/dev/nitro_enclaves"

/**
 * NE_POLL_WAIT_TIME - Timeout in seconds क्रम each poll event.
 */
#घोषणा NE_POLL_WAIT_TIME		(60)
/**
 * NE_POLL_WAIT_TIME_MS - Timeout in milliseconds क्रम each poll event.
 */
#घोषणा NE_POLL_WAIT_TIME_MS		(NE_POLL_WAIT_TIME * 1000)

/**
 * NE_SLEEP_TIME - Amount of समय in seconds क्रम the process to keep the enclave alive.
 */
#घोषणा NE_SLEEP_TIME			(300)

/**
 * NE_DEFAULT_NR_VCPUS - Default number of vCPUs set क्रम an enclave.
 */
#घोषणा NE_DEFAULT_NR_VCPUS		(2)

/**
 * NE_MIN_MEM_REGION_SIZE - Minimum size of a memory region - 2 MiB.
 */
#घोषणा NE_MIN_MEM_REGION_SIZE		(2 * 1024 * 1024)

/**
 * NE_DEFAULT_NR_MEM_REGIONS - Default number of memory regions of 2 MiB set क्रम
 *			       an enclave.
 */
#घोषणा NE_DEFAULT_NR_MEM_REGIONS	(256)

/**
 * NE_IMAGE_LOAD_HEARTBEAT_CID - Vsock CID क्रम enclave image loading heartbeat logic.
 */
#घोषणा NE_IMAGE_LOAD_HEARTBEAT_CID	(3)
/**
 * NE_IMAGE_LOAD_HEARTBEAT_PORT - Vsock port क्रम enclave image loading heartbeat logic.
 */
#घोषणा NE_IMAGE_LOAD_HEARTBEAT_PORT	(9000)
/**
 * NE_IMAGE_LOAD_HEARTBEAT_VALUE - Heartbeat value क्रम enclave image loading.
 */
#घोषणा NE_IMAGE_LOAD_HEARTBEAT_VALUE	(0xb7)

/**
 * काष्ठा ne_user_mem_region - User space memory region set क्रम an enclave.
 * @userspace_addr:	Address of the user space memory region.
 * @memory_size:	Size of the user space memory region.
 */
काष्ठा ne_user_mem_region अणु
	व्योम	*userspace_addr;
	माप_प्रकार	memory_size;
पूर्ण;

/**
 * ne_create_vm() - Create a slot क्रम the enclave VM.
 * @ne_dev_fd:		The file descriptor of the NE misc device.
 * @slot_uid:		The generated slot uid क्रम the enclave.
 * @enclave_fd :	The generated file descriptor क्रम the enclave.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_create_vm(पूर्णांक ne_dev_fd, अचिन्हित दीर्घ *slot_uid, पूर्णांक *enclave_fd)
अणु
	पूर्णांक rc = -EINVAL;
	*enclave_fd = ioctl(ne_dev_fd, NE_CREATE_VM, slot_uid);

	अगर (*enclave_fd < 0) अणु
		rc = *enclave_fd;
		चयन (त्रुटि_सं) अणु
		हाल NE_ERR_NO_CPUS_AVAIL_IN_POOL: अणु
			म_लिखो("Error in create VM, no CPUs available in the NE CPU pool\n");

			अवरोध;
		पूर्ण

		शेष:
			म_लिखो("Error in create VM [%m]\n");
		पूर्ण

		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * ne_poll_enclave_fd() - Thपढ़ो function क्रम polling the enclave fd.
 * @data:	Argument provided क्रम the polling function.
 *
 * Context: Process context.
 * Return:
 * * शून्य on success / failure.
 */
व्योम *ne_poll_enclave_fd(व्योम *data)
अणु
	पूर्णांक enclave_fd = *(पूर्णांक *)data;
	काष्ठा pollfd fds[1] = अणुपूर्ण;
	पूर्णांक i = 0;
	पूर्णांक rc = -EINVAL;

	म_लिखो("Running from poll thread, enclave fd %d\n", enclave_fd);

	fds[0].fd = enclave_fd;
	fds[0].events = POLLIN | POLLERR | POLLHUP;

	/* Keep on polling until the current process is terminated. */
	जबतक (1) अणु
		म_लिखो("[iter %d] Polling ...\n", i);

		rc = poll(fds, 1, NE_POLL_WAIT_TIME_MS);
		अगर (rc < 0) अणु
			म_लिखो("Error in poll [%m]\n");

			वापस शून्य;
		पूर्ण

		i++;

		अगर (!rc) अणु
			म_लिखो("Poll: %d seconds elapsed\n",
			       i * NE_POLL_WAIT_TIME);

			जारी;
		पूर्ण

		म_लिखो("Poll received value 0x%x\n", fds[0].revents);

		अगर (fds[0].revents & POLLHUP) अणु
			म_लिखो("Received POLLHUP\n");

			वापस शून्य;
		पूर्ण

		अगर (fds[0].revents & POLLNVAL) अणु
			म_लिखो("Received POLLNVAL\n");

			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ne_alloc_user_mem_region() - Allocate a user space memory region क्रम an enclave.
 * @ne_user_mem_region:	User space memory region allocated using hugetlbfs.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_alloc_user_mem_region(काष्ठा ne_user_mem_region *ne_user_mem_region)
अणु
	/**
	 * Check available hugetlb encodings क्रम dअगरferent huge page sizes in
	 * include/uapi/linux/mman.h.
	 */
	ne_user_mem_region->userspace_addr = mmap(शून्य, ne_user_mem_region->memory_size,
						  PROT_READ | PROT_WRITE,
						  MAP_PRIVATE | MAP_ANONYMOUS |
						  MAP_HUGETLB | MAP_HUGE_2MB, -1, 0);
	अगर (ne_user_mem_region->userspace_addr == MAP_FAILED) अणु
		म_लिखो("Error in mmap memory [%m]\n");

		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ne_load_enclave_image() - Place the enclave image in the enclave memory.
 * @enclave_fd :		The file descriptor associated with the enclave.
 * @ne_user_mem_regions:	User space memory regions allocated क्रम the enclave.
 * @enclave_image_path :	The file path of the enclave image.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_load_enclave_image(पूर्णांक enclave_fd, काष्ठा ne_user_mem_region ne_user_mem_regions[],
				 अक्षर *enclave_image_path)
अणु
	अचिन्हित अक्षर *enclave_image = शून्य;
	पूर्णांक enclave_image_fd = -1;
	माप_प्रकार enclave_image_size = 0;
	माप_प्रकार enclave_memory_size = 0;
	अचिन्हित दीर्घ i = 0;
	माप_प्रकार image_written_bytes = 0;
	काष्ठा ne_image_load_info image_load_info = अणु
		.flags = NE_EIF_IMAGE,
	पूर्ण;
	काष्ठा stat image_stat_buf = अणुपूर्ण;
	पूर्णांक rc = -EINVAL;
	माप_प्रकार temp_image_offset = 0;

	क्रम (i = 0; i < NE_DEFAULT_NR_MEM_REGIONS; i++)
		enclave_memory_size += ne_user_mem_regions[i].memory_size;

	rc = stat(enclave_image_path, &image_stat_buf);
	अगर (rc < 0) अणु
		म_लिखो("Error in get image stat info [%m]\n");

		वापस rc;
	पूर्ण

	enclave_image_size = image_stat_buf.st_size;

	अगर (enclave_memory_size < enclave_image_size) अणु
		म_लिखो("The enclave memory is smaller than the enclave image size\n");

		वापस -ENOMEM;
	पूर्ण

	rc = ioctl(enclave_fd, NE_GET_IMAGE_LOAD_INFO, &image_load_info);
	अगर (rc < 0) अणु
		चयन (त्रुटि_सं) अणु
		हाल NE_ERR_NOT_IN_INIT_STATE: अणु
			म_लिखो("Error in get image load info, enclave not in init state\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_INVALID_FLAG_VALUE: अणु
			म_लिखो("Error in get image load info, provided invalid flag\n");

			अवरोध;
		पूर्ण

		शेष:
			म_लिखो("Error in get image load info [%m]\n");
		पूर्ण

		वापस rc;
	पूर्ण

	म_लिखो("Enclave image offset in enclave memory is %lld\n",
	       image_load_info.memory_offset);

	enclave_image_fd = खोलो(enclave_image_path, O_RDONLY);
	अगर (enclave_image_fd < 0) अणु
		म_लिखो("Error in open enclave image file [%m]\n");

		वापस enclave_image_fd;
	पूर्ण

	enclave_image = mmap(शून्य, enclave_image_size, PROT_READ,
			     MAP_PRIVATE, enclave_image_fd, 0);
	अगर (enclave_image == MAP_FAILED) अणु
		म_लिखो("Error in mmap enclave image [%m]\n");

		वापस -1;
	पूर्ण

	temp_image_offset = image_load_info.memory_offset;

	क्रम (i = 0; i < NE_DEFAULT_NR_MEM_REGIONS; i++) अणु
		माप_प्रकार bytes_to_ग_लिखो = 0;
		माप_प्रकार memory_offset = 0;
		माप_प्रकार memory_size = ne_user_mem_regions[i].memory_size;
		माप_प्रकार reमुख्यing_bytes = 0;
		व्योम *userspace_addr = ne_user_mem_regions[i].userspace_addr;

		अगर (temp_image_offset >= memory_size) अणु
			temp_image_offset -= memory_size;

			जारी;
		पूर्ण अन्यथा अगर (temp_image_offset != 0) अणु
			memory_offset = temp_image_offset;
			memory_size -= temp_image_offset;
			temp_image_offset = 0;
		पूर्ण

		reमुख्यing_bytes = enclave_image_size - image_written_bytes;
		bytes_to_ग_लिखो = memory_size < reमुख्यing_bytes ?
				 memory_size : reमुख्यing_bytes;

		स_नकल(userspace_addr + memory_offset,
		       enclave_image + image_written_bytes, bytes_to_ग_लिखो);

		image_written_bytes += bytes_to_ग_लिखो;

		अगर (image_written_bytes == enclave_image_size)
			अवरोध;
	पूर्ण

	munmap(enclave_image, enclave_image_size);

	बंद(enclave_image_fd);

	वापस 0;
पूर्ण

/**
 * ne_set_user_mem_region() - Set a user space memory region क्रम the given enclave.
 * @enclave_fd :		The file descriptor associated with the enclave.
 * @ne_user_mem_region :	User space memory region to be set क्रम the enclave.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_set_user_mem_region(पूर्णांक enclave_fd, काष्ठा ne_user_mem_region ne_user_mem_region)
अणु
	काष्ठा ne_user_memory_region mem_region = अणु
		.flags = NE_DEFAULT_MEMORY_REGION,
		.memory_size = ne_user_mem_region.memory_size,
		.userspace_addr = (__u64)ne_user_mem_region.userspace_addr,
	पूर्ण;
	पूर्णांक rc = -EINVAL;

	rc = ioctl(enclave_fd, NE_SET_USER_MEMORY_REGION, &mem_region);
	अगर (rc < 0) अणु
		चयन (त्रुटि_सं) अणु
		हाल NE_ERR_NOT_IN_INIT_STATE: अणु
			म_लिखो("Error in set user memory region, enclave not in init state\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_INVALID_MEM_REGION_SIZE: अणु
			म_लिखो("Error in set user memory region, mem size not multiple of 2 MiB\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_INVALID_MEM_REGION_ADDR: अणु
			म_लिखो("Error in set user memory region, invalid user space address\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_UNALIGNED_MEM_REGION_ADDR: अणु
			म_लिखो("Error in set user memory region, unaligned user space address\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_MEM_REGION_ALREADY_USED: अणु
			म_लिखो("Error in set user memory region, memory region already used\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_MEM_NOT_HUGE_PAGE: अणु
			म_लिखो("Error in set user memory region, not backed by huge pages\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_MEM_DIFFERENT_NUMA_NODE: अणु
			म_लिखो("Error in set user memory region, different NUMA node than CPUs\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_MEM_MAX_REGIONS: अणु
			म_लिखो("Error in set user memory region, max memory regions reached\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_INVALID_PAGE_SIZE: अणु
			म_लिखो("Error in set user memory region, has page not multiple of 2 MiB\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_INVALID_FLAG_VALUE: अणु
			म_लिखो("Error in set user memory region, provided invalid flag\n");

			अवरोध;
		पूर्ण

		शेष:
			म_लिखो("Error in set user memory region [%m]\n");
		पूर्ण

		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ne_मुक्त_mem_regions() - Unmap all the user space memory regions that were set
 *			   aside क्रम the enclave.
 * @ne_user_mem_regions:	The user space memory regions associated with an enclave.
 *
 * Context: Process context.
 */
अटल व्योम ne_मुक्त_mem_regions(काष्ठा ne_user_mem_region ne_user_mem_regions[])
अणु
	अचिन्हित पूर्णांक i = 0;

	क्रम (i = 0; i < NE_DEFAULT_NR_MEM_REGIONS; i++)
		munmap(ne_user_mem_regions[i].userspace_addr,
		       ne_user_mem_regions[i].memory_size);
पूर्ण

/**
 * ne_add_vcpu() - Add a vCPU to the given enclave.
 * @enclave_fd :	The file descriptor associated with the enclave.
 * @vcpu_id:		vCPU id to be set क्रम the enclave, either provided or
 *			स्वतः-generated (अगर provided vCPU id is 0).
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_add_vcpu(पूर्णांक enclave_fd, अचिन्हित पूर्णांक *vcpu_id)
अणु
	पूर्णांक rc = -EINVAL;

	rc = ioctl(enclave_fd, NE_ADD_VCPU, vcpu_id);
	अगर (rc < 0) अणु
		चयन (त्रुटि_सं) अणु
		हाल NE_ERR_NO_CPUS_AVAIL_IN_POOL: अणु
			म_लिखो("Error in add vcpu, no CPUs available in the NE CPU pool\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_VCPU_ALREADY_USED: अणु
			म_लिखो("Error in add vcpu, the provided vCPU is already used\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_VCPU_NOT_IN_CPU_POOL: अणु
			म_लिखो("Error in add vcpu, the provided vCPU is not in the NE CPU pool\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_VCPU_INVALID_CPU_CORE: अणु
			म_लिखो("Error in add vcpu, the core id of the provided vCPU is invalid\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_NOT_IN_INIT_STATE: अणु
			म_लिखो("Error in add vcpu, enclave not in init state\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_INVALID_VCPU: अणु
			म_लिखो("Error in add vcpu, the provided vCPU is out of avail CPUs range\n");

			अवरोध;
		पूर्ण

		शेष:
			म_लिखो("Error in add vcpu [%m]\n");

		पूर्ण
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ne_start_enclave() - Start the given enclave.
 * @enclave_fd :		The file descriptor associated with the enclave.
 * @enclave_start_info :	Enclave metadata used क्रम starting e.g. vsock CID.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_start_enclave(पूर्णांक enclave_fd,  काष्ठा ne_enclave_start_info *enclave_start_info)
अणु
	पूर्णांक rc = -EINVAL;

	rc = ioctl(enclave_fd, NE_START_ENCLAVE, enclave_start_info);
	अगर (rc < 0) अणु
		चयन (त्रुटि_सं) अणु
		हाल NE_ERR_NOT_IN_INIT_STATE: अणु
			म_लिखो("Error in start enclave, enclave not in init state\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_NO_MEM_REGIONS_ADDED: अणु
			म_लिखो("Error in start enclave, no memory regions have been added\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_NO_VCPUS_ADDED: अणु
			म_लिखो("Error in start enclave, no vCPUs have been added\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_FULL_CORES_NOT_USED: अणु
			म_लिखो("Error in start enclave, enclave has no full cores set\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_ENCLAVE_MEM_MIN_SIZE: अणु
			म_लिखो("Error in start enclave, enclave memory is less than min size\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_INVALID_FLAG_VALUE: अणु
			म_लिखो("Error in start enclave, provided invalid flag\n");

			अवरोध;
		पूर्ण

		हाल NE_ERR_INVALID_ENCLAVE_CID: अणु
			म_लिखो("Error in start enclave, provided invalid enclave CID\n");

			अवरोध;
		पूर्ण

		शेष:
			म_लिखो("Error in start enclave [%m]\n");
		पूर्ण

		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ne_start_enclave_check_booted() - Start the enclave and रुको क्रम a hearbeat
 *				     from it, on a newly created vsock channel,
 *				     to check it has booted.
 * @enclave_fd :	The file descriptor associated with the enclave.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_start_enclave_check_booted(पूर्णांक enclave_fd)
अणु
	काष्ठा sockaddr_vm client_vsock_addr = अणुपूर्ण;
	पूर्णांक client_vsock_fd = -1;
	socklen_t client_vsock_len = माप(client_vsock_addr);
	काष्ठा ne_enclave_start_info enclave_start_info = अणुपूर्ण;
	काष्ठा pollfd fds[1] = अणुपूर्ण;
	पूर्णांक rc = -EINVAL;
	अचिन्हित अक्षर recv_buf = 0;
	काष्ठा sockaddr_vm server_vsock_addr = अणु
		.svm_family = AF_VSOCK,
		.svm_cid = NE_IMAGE_LOAD_HEARTBEAT_CID,
		.svm_port = NE_IMAGE_LOAD_HEARTBEAT_PORT,
	पूर्ण;
	पूर्णांक server_vsock_fd = -1;

	server_vsock_fd = socket(AF_VSOCK, SOCK_STREAM, 0);
	अगर (server_vsock_fd < 0) अणु
		rc = server_vsock_fd;

		म_लिखो("Error in socket [%m]\n");

		वापस rc;
	पूर्ण

	rc = bind(server_vsock_fd, (काष्ठा sockaddr *)&server_vsock_addr,
		  माप(server_vsock_addr));
	अगर (rc < 0) अणु
		म_लिखो("Error in bind [%m]\n");

		जाओ out;
	पूर्ण

	rc = listen(server_vsock_fd, 1);
	अगर (rc < 0) अणु
		म_लिखो("Error in listen [%m]\n");

		जाओ out;
	पूर्ण

	rc = ne_start_enclave(enclave_fd, &enclave_start_info);
	अगर (rc < 0)
		जाओ out;

	म_लिखो("Enclave started, CID %llu\n", enclave_start_info.enclave_cid);

	fds[0].fd = server_vsock_fd;
	fds[0].events = POLLIN;

	rc = poll(fds, 1, NE_POLL_WAIT_TIME_MS);
	अगर (rc < 0) अणु
		म_लिखो("Error in poll [%m]\n");

		जाओ out;
	पूर्ण

	अगर (!rc) अणु
		म_लिखो("Poll timeout, %d seconds elapsed\n", NE_POLL_WAIT_TIME);

		rc = -ETIMEDOUT;

		जाओ out;
	पूर्ण

	अगर ((fds[0].revents & POLLIN) == 0) अणु
		म_लिखो("Poll received value %d\n", fds[0].revents);

		rc = -EINVAL;

		जाओ out;
	पूर्ण

	rc = accept(server_vsock_fd, (काष्ठा sockaddr *)&client_vsock_addr,
		    &client_vsock_len);
	अगर (rc < 0) अणु
		म_लिखो("Error in accept [%m]\n");

		जाओ out;
	पूर्ण

	client_vsock_fd = rc;

	/*
	 * Read the heartbeat value that the init process in the enclave sends
	 * after vsock connect.
	 */
	rc = पढ़ो(client_vsock_fd, &recv_buf, माप(recv_buf));
	अगर (rc < 0) अणु
		म_लिखो("Error in read [%m]\n");

		जाओ out;
	पूर्ण

	अगर (rc != माप(recv_buf) || recv_buf != NE_IMAGE_LOAD_HEARTBEAT_VALUE) अणु
		म_लिखो("Read %d instead of %d\n", recv_buf,
		       NE_IMAGE_LOAD_HEARTBEAT_VALUE);

		जाओ out;
	पूर्ण

	/* Write the heartbeat value back. */
	rc = ग_लिखो(client_vsock_fd, &recv_buf, माप(recv_buf));
	अगर (rc < 0) अणु
		म_लिखो("Error in write [%m]\n");

		जाओ out;
	पूर्ण

	rc = 0;

out:
	बंद(server_vsock_fd);

	वापस rc;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक enclave_fd = -1;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक ne_dev_fd = -1;
	काष्ठा ne_user_mem_region ne_user_mem_regions[NE_DEFAULT_NR_MEM_REGIONS] = अणुपूर्ण;
	अचिन्हित पूर्णांक ne_vcpus[NE_DEFAULT_NR_VCPUS] = अणुपूर्ण;
	पूर्णांक rc = -EINVAL;
	pthपढ़ो_t thपढ़ो_id = 0;
	अचिन्हित दीर्घ slot_uid = 0;

	अगर (argc != 2) अणु
		म_लिखो("Usage: %s <path_to_enclave_image>\n", argv[0]);

		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (म_माप(argv[1]) >= PATH_MAX) अणु
		म_लिखो("The size of the path to enclave image is higher than max path\n");

		निकास(निकास_त्रुटि);
	पूर्ण

	ne_dev_fd = खोलो(NE_DEV_NAME, O_RDWR | O_CLOEXEC);
	अगर (ne_dev_fd < 0) अणु
		म_लिखो("Error in open NE device [%m]\n");

		निकास(निकास_त्रुटि);
	पूर्ण

	म_लिखो("Creating enclave slot ...\n");

	rc = ne_create_vm(ne_dev_fd, &slot_uid, &enclave_fd);

	बंद(ne_dev_fd);

	अगर (rc < 0)
		निकास(निकास_त्रुटि);

	म_लिखो("Enclave fd %d\n", enclave_fd);

	rc = pthपढ़ो_create(&thपढ़ो_id, शून्य, ne_poll_enclave_fd, (व्योम *)&enclave_fd);
	अगर (rc < 0) अणु
		म_लिखो("Error in thread create [%m]\n");

		बंद(enclave_fd);

		निकास(निकास_त्रुटि);
	पूर्ण

	क्रम (i = 0; i < NE_DEFAULT_NR_MEM_REGIONS; i++) अणु
		ne_user_mem_regions[i].memory_size = NE_MIN_MEM_REGION_SIZE;

		rc = ne_alloc_user_mem_region(&ne_user_mem_regions[i]);
		अगर (rc < 0) अणु
			म_लिखो("Error in alloc userspace memory region, iter %d\n", i);

			जाओ release_enclave_fd;
		पूर्ण
	पूर्ण

	rc = ne_load_enclave_image(enclave_fd, ne_user_mem_regions, argv[1]);
	अगर (rc < 0)
		जाओ release_enclave_fd;

	क्रम (i = 0; i < NE_DEFAULT_NR_MEM_REGIONS; i++) अणु
		rc = ne_set_user_mem_region(enclave_fd, ne_user_mem_regions[i]);
		अगर (rc < 0) अणु
			म_लिखो("Error in set memory region, iter %d\n", i);

			जाओ release_enclave_fd;
		पूर्ण
	पूर्ण

	म_लिखो("Enclave memory regions were added\n");

	क्रम (i = 0; i < NE_DEFAULT_NR_VCPUS; i++) अणु
		/*
		 * The vCPU is chosen from the enclave vCPU pool, अगर the value
		 * of the vcpu_id is 0.
		 */
		ne_vcpus[i] = 0;
		rc = ne_add_vcpu(enclave_fd, &ne_vcpus[i]);
		अगर (rc < 0) अणु
			म_लिखो("Error in add vcpu, iter %d\n", i);

			जाओ release_enclave_fd;
		पूर्ण

		म_लिखो("Added vCPU %d to the enclave\n", ne_vcpus[i]);
	पूर्ण

	म_लिखो("Enclave vCPUs were added\n");

	rc = ne_start_enclave_check_booted(enclave_fd);
	अगर (rc < 0) अणु
		म_लिखो("Error in the enclave start / image loading heartbeat logic [rc=%d]\n", rc);

		जाओ release_enclave_fd;
	पूर्ण

	म_लिखो("Entering sleep for %d seconds ...\n", NE_SLEEP_TIME);

	sleep(NE_SLEEP_TIME);

	बंद(enclave_fd);

	ne_मुक्त_mem_regions(ne_user_mem_regions);

	निकास(निकास_सफल);

release_enclave_fd:
	बंद(enclave_fd);
	ne_मुक्त_mem_regions(ne_user_mem_regions);

	निकास(निकास_त्रुटि);
पूर्ण
