<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020, Google LLC.
 */
#समावेश <पूर्णांकtypes.h>

#समावेश "kvm_util.h"
#समावेश "perf_test_util.h"
#समावेश "processor.h"

काष्ठा perf_test_args perf_test_args;

uपूर्णांक64_t guest_test_phys_mem;

/*
 * Guest भव memory offset of the testing memory slot.
 * Must not conflict with identity mapped test code.
 */
अटल uपूर्णांक64_t guest_test_virt_mem = DEFAULT_GUEST_TEST_MEM;

/*
 * Continuously ग_लिखो to the first 8 bytes of each page in the
 * specअगरied region.
 */
अटल व्योम guest_code(uपूर्णांक32_t vcpu_id)
अणु
	काष्ठा perf_test_vcpu_args *vcpu_args = &perf_test_args.vcpu_args[vcpu_id];
	uपूर्णांक64_t gva;
	uपूर्णांक64_t pages;
	पूर्णांक i;

	/* Make sure vCPU args data काष्ठाure is not corrupt. */
	GUEST_ASSERT(vcpu_args->vcpu_id == vcpu_id);

	gva = vcpu_args->gva;
	pages = vcpu_args->pages;

	जबतक (true) अणु
		क्रम (i = 0; i < pages; i++) अणु
			uपूर्णांक64_t addr = gva + (i * perf_test_args.guest_page_size);

			अगर (i % perf_test_args.wr_fract == 0)
				*(uपूर्णांक64_t *)addr = 0x0123456789ABCDEF;
			अन्यथा
				READ_ONCE(*(uपूर्णांक64_t *)addr);
		पूर्ण

		GUEST_SYNC(1);
	पूर्ण
पूर्ण

काष्ठा kvm_vm *perf_test_create_vm(क्रमागत vm_guest_mode mode, पूर्णांक vcpus,
				   uपूर्णांक64_t vcpu_memory_bytes,
				   क्रमागत vm_mem_backing_src_type backing_src)
अणु
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t guest_num_pages;

	pr_info("Testing guest mode: %s\n", vm_guest_mode_string(mode));

	perf_test_args.host_page_size = getpagesize();
	perf_test_args.guest_page_size = vm_guest_mode_params[mode].page_size;

	guest_num_pages = vm_adjust_num_guest_pages(mode,
				(vcpus * vcpu_memory_bytes) / perf_test_args.guest_page_size);

	TEST_ASSERT(vcpu_memory_bytes % perf_test_args.host_page_size == 0,
		    "Guest memory size is not host page size aligned.");
	TEST_ASSERT(vcpu_memory_bytes % perf_test_args.guest_page_size == 0,
		    "Guest memory size is not guest page size aligned.");

	vm = vm_create_with_vcpus(mode, vcpus, DEFAULT_GUEST_PHY_PAGES,
				  (vcpus * vcpu_memory_bytes) / perf_test_args.guest_page_size,
				  0, guest_code, शून्य);

	perf_test_args.vm = vm;

	/*
	 * If there should be more memory in the guest test region than there
	 * can be pages in the guest, it will definitely cause problems.
	 */
	TEST_ASSERT(guest_num_pages < vm_get_max_gfn(vm),
		    "Requested more guest memory than address space allows.\n"
		    "    guest pages: %" PRIx64 " max gfn: %" PRIx64
		    " vcpus: %d wss: %" PRIx64 "]\n",
		    guest_num_pages, vm_get_max_gfn(vm), vcpus,
		    vcpu_memory_bytes);

	guest_test_phys_mem = (vm_get_max_gfn(vm) - guest_num_pages) *
			      perf_test_args.guest_page_size;
	guest_test_phys_mem &= ~(perf_test_args.host_page_size - 1);
#अगर_घोषित __s390x__
	/* Align to 1M (segment size) */
	guest_test_phys_mem &= ~((1 << 20) - 1);
#पूर्ण_अगर
	pr_info("guest physical test memory offset: 0x%lx\n", guest_test_phys_mem);

	/* Add an extra memory slot क्रम testing */
	vm_userspace_mem_region_add(vm, backing_src, guest_test_phys_mem,
				    PERF_TEST_MEM_SLOT_INDEX,
				    guest_num_pages, 0);

	/* Do mapping क्रम the demand paging memory slot */
	virt_map(vm, guest_test_virt_mem, guest_test_phys_mem, guest_num_pages, 0);

	ucall_init(vm, शून्य);

	वापस vm;
पूर्ण

व्योम perf_test_destroy_vm(काष्ठा kvm_vm *vm)
अणु
	ucall_uninit(vm);
	kvm_vm_मुक्त(vm);
पूर्ण

व्योम perf_test_setup_vcpus(काष्ठा kvm_vm *vm, पूर्णांक vcpus,
			   uपूर्णांक64_t vcpu_memory_bytes,
			   bool partition_vcpu_memory_access)
अणु
	vm_paddr_t vcpu_gpa;
	काष्ठा perf_test_vcpu_args *vcpu_args;
	पूर्णांक vcpu_id;

	क्रम (vcpu_id = 0; vcpu_id < vcpus; vcpu_id++) अणु
		vcpu_args = &perf_test_args.vcpu_args[vcpu_id];

		vcpu_args->vcpu_id = vcpu_id;
		अगर (partition_vcpu_memory_access) अणु
			vcpu_args->gva = guest_test_virt_mem +
					 (vcpu_id * vcpu_memory_bytes);
			vcpu_args->pages = vcpu_memory_bytes /
					   perf_test_args.guest_page_size;
			vcpu_gpa = guest_test_phys_mem +
				   (vcpu_id * vcpu_memory_bytes);
		पूर्ण अन्यथा अणु
			vcpu_args->gva = guest_test_virt_mem;
			vcpu_args->pages = (vcpus * vcpu_memory_bytes) /
					   perf_test_args.guest_page_size;
			vcpu_gpa = guest_test_phys_mem;
		पूर्ण

		pr_debug("Added VCPU %d with test mem gpa [%lx, %lx)\n",
			 vcpu_id, vcpu_gpa, vcpu_gpa +
			 (vcpu_args->pages * perf_test_args.guest_page_size));
	पूर्ण
पूर्ण
