<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KVM page table test
 *
 * Copyright (C) 2021, Huawei, Inc.
 *
 * Make sure that THP has been enabled or enough HUGETLB pages with specअगरic
 * page size have been pre-allocated on your प्रणाली, अगर you are planning to
 * use hugepages to back the guest memory क्रम testing.
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_name */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <pthपढ़ो.h>
#समावेश <semaphore.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"
#समावेश "guest_modes.h"

#घोषणा TEST_MEM_SLOT_INDEX             1

/* Default size(1GB) of the memory क्रम testing */
#घोषणा DEFAULT_TEST_MEM_SIZE		(1 << 30)

/* Default guest test भव memory offset */
#घोषणा DEFAULT_GUEST_TEST_MEM		0xc0000000

/* Dअगरferent guest memory accessing stages */
क्रमागत test_stage अणु
	KVM_BEFORE_MAPPINGS,
	KVM_CREATE_MAPPINGS,
	KVM_UPDATE_MAPPINGS,
	KVM_ADJUST_MAPPINGS,
	NUM_TEST_STAGES,
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_stage_string[] = अणु
	"KVM_BEFORE_MAPPINGS",
	"KVM_CREATE_MAPPINGS",
	"KVM_UPDATE_MAPPINGS",
	"KVM_ADJUST_MAPPINGS",
पूर्ण;

काष्ठा vcpu_args अणु
	पूर्णांक vcpu_id;
	bool vcpu_ग_लिखो;
पूर्ण;

काष्ठा test_args अणु
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t guest_test_virt_mem;
	uपूर्णांक64_t host_page_size;
	uपूर्णांक64_t host_num_pages;
	uपूर्णांक64_t large_page_size;
	uपूर्णांक64_t large_num_pages;
	uपूर्णांक64_t host_pages_per_lpage;
	क्रमागत vm_mem_backing_src_type src_type;
	काष्ठा vcpu_args vcpu_args[KVM_MAX_VCPUS];
पूर्ण;

/*
 * Guest variables. Use addr_gva2hva() अगर these variables need
 * to be changed in host.
 */
अटल क्रमागत test_stage guest_test_stage;

/* Host variables */
अटल uपूर्णांक32_t nr_vcpus = 1;
अटल काष्ठा test_args test_args;
अटल क्रमागत test_stage *current_stage;
अटल bool host_quit;

/* Whether the test stage is updated, or completed */
अटल sem_t test_stage_updated;
अटल sem_t test_stage_completed;

/*
 * Guest physical memory offset of the testing memory slot.
 * This will be set to the topmost valid physical address minus
 * the test memory size.
 */
अटल uपूर्णांक64_t guest_test_phys_mem;

/*
 * Guest भव memory offset of the testing memory slot.
 * Must not conflict with identity mapped test code.
 */
अटल uपूर्णांक64_t guest_test_virt_mem = DEFAULT_GUEST_TEST_MEM;

अटल व्योम guest_code(पूर्णांक vcpu_id)
अणु
	काष्ठा test_args *p = &test_args;
	काष्ठा vcpu_args *vcpu_args = &p->vcpu_args[vcpu_id];
	क्रमागत test_stage *current_stage = &guest_test_stage;
	uपूर्णांक64_t addr;
	पूर्णांक i, j;

	/* Make sure vCPU args data काष्ठाure is not corrupt */
	GUEST_ASSERT(vcpu_args->vcpu_id == vcpu_id);

	जबतक (true) अणु
		addr = p->guest_test_virt_mem;

		चयन (READ_ONCE(*current_stage)) अणु
		/*
		 * All vCPU thपढ़ोs will be started in this stage,
		 * where guest code of each vCPU will करो nothing.
		 */
		हाल KVM_BEFORE_MAPPINGS:
			अवरोध;

		/*
		 * Beक्रमe dirty logging, vCPUs concurrently access the first
		 * 8 bytes of each page (host page/large page) within the same
		 * memory region with dअगरferent accessing types (पढ़ो/ग_लिखो).
		 * Then KVM will create normal page mappings or huge block
		 * mappings क्रम them.
		 */
		हाल KVM_CREATE_MAPPINGS:
			क्रम (i = 0; i < p->large_num_pages; i++) अणु
				अगर (vcpu_args->vcpu_ग_लिखो)
					*(uपूर्णांक64_t *)addr = 0x0123456789ABCDEF;
				अन्यथा
					READ_ONCE(*(uपूर्णांक64_t *)addr);

				addr += p->large_page_size;
			पूर्ण
			अवरोध;

		/*
		 * During dirty logging, KVM will only update attributes of the
		 * normal page mappings from RO to RW अगर memory backing src type
		 * is anonymous. In other हालs, KVM will split the huge block
		 * mappings पूर्णांकo normal page mappings अगर memory backing src type
		 * is THP or HUGETLB.
		 */
		हाल KVM_UPDATE_MAPPINGS:
			अगर (p->src_type == VM_MEM_SRC_ANONYMOUS) अणु
				क्रम (i = 0; i < p->host_num_pages; i++) अणु
					*(uपूर्णांक64_t *)addr = 0x0123456789ABCDEF;
					addr += p->host_page_size;
				पूर्ण
				अवरोध;
			पूर्ण

			क्रम (i = 0; i < p->large_num_pages; i++) अणु
				/*
				 * Write to the first host page in each large
				 * page region, and triger अवरोध of large pages.
				 */
				*(uपूर्णांक64_t *)addr = 0x0123456789ABCDEF;

				/*
				 * Access the middle host pages in each large
				 * page region. Since dirty logging is enabled,
				 * this will create new mappings at the smallest
				 * granularity.
				 */
				addr += p->large_page_size / 2;
				क्रम (j = 0; j < p->host_pages_per_lpage / 2; j++) अणु
					READ_ONCE(*(uपूर्णांक64_t *)addr);
					addr += p->host_page_size;
				पूर्ण
			पूर्ण
			अवरोध;

		/*
		 * After dirty logging is stopped, vCPUs concurrently पढ़ो
		 * from every single host page. Then KVM will coalesce the
		 * split page mappings back to block mappings. And a TLB
		 * conflict पात could occur here अगर TLB entries of the
		 * page mappings are not fully invalidated.
		 */
		हाल KVM_ADJUST_MAPPINGS:
			क्रम (i = 0; i < p->host_num_pages; i++) अणु
				READ_ONCE(*(uपूर्णांक64_t *)addr);
				addr += p->host_page_size;
			पूर्ण
			अवरोध;

		शेष:
			GUEST_ASSERT(0);
		पूर्ण

		GUEST_SYNC(1);
	पूर्ण
पूर्ण

अटल व्योम *vcpu_worker(व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा vcpu_args *vcpu_args = data;
	काष्ठा kvm_vm *vm = test_args.vm;
	पूर्णांक vcpu_id = vcpu_args->vcpu_id;
	काष्ठा kvm_run *run;
	काष्ठा बारpec start;
	काष्ठा बारpec ts_dअगरf;
	क्रमागत test_stage stage;

	vcpu_args_set(vm, vcpu_id, 1, vcpu_id);
	run = vcpu_state(vm, vcpu_id);

	जबतक (!READ_ONCE(host_quit)) अणु
		ret = sem_रुको(&test_stage_updated);
		TEST_ASSERT(ret == 0, "Error in sem_wait");

		अगर (READ_ONCE(host_quit))
			वापस शून्य;

		घड़ी_समय_लो(CLOCK_MONOTONIC_RAW, &start);
		ret = _vcpu_run(vm, vcpu_id);
		ts_dअगरf = बारpec_elapsed(start);

		TEST_ASSERT(ret == 0, "vcpu_run failed: %d\n", ret);
		TEST_ASSERT(get_ucall(vm, vcpu_id, शून्य) == UCALL_SYNC,
			    "Invalid guest sync status: exit_reason=%s\n",
			    निकास_reason_str(run->निकास_reason));

		pr_debug("Got sync event from vCPU %d\n", vcpu_id);
		stage = READ_ONCE(*current_stage);

		/*
		 * Here we can know the execution समय of every
		 * single vcpu running in dअगरferent test stages.
		 */
		pr_debug("vCPU %d has completed stage %s\n"
			 "execution time is: %ld.%.9lds\n\n",
			 vcpu_id, test_stage_string[stage],
			 ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

		ret = sem_post(&test_stage_completed);
		TEST_ASSERT(ret == 0, "Error in sem_post");
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा test_params अणु
	uपूर्णांक64_t phys_offset;
	uपूर्णांक64_t test_mem_size;
	क्रमागत vm_mem_backing_src_type src_type;
पूर्ण;

अटल काष्ठा kvm_vm *pre_init_beक्रमe_test(क्रमागत vm_guest_mode mode, व्योम *arg)
अणु
	पूर्णांक ret;
	काष्ठा test_params *p = arg;
	काष्ठा vcpu_args *vcpu_args;
	क्रमागत vm_mem_backing_src_type src_type = p->src_type;
	uपूर्णांक64_t large_page_size = get_backing_src_pagesz(src_type);
	uपूर्णांक64_t guest_page_size = vm_guest_mode_params[mode].page_size;
	uपूर्णांक64_t host_page_size = getpagesize();
	uपूर्णांक64_t test_mem_size = p->test_mem_size;
	uपूर्णांक64_t guest_num_pages;
	uपूर्णांक64_t alignment;
	व्योम *host_test_mem;
	काष्ठा kvm_vm *vm;
	पूर्णांक vcpu_id;

	/* Align up the test memory size */
	alignment = max(large_page_size, guest_page_size);
	test_mem_size = (test_mem_size + alignment - 1) & ~(alignment - 1);

	/* Create a VM with enough guest pages */
	guest_num_pages = test_mem_size / guest_page_size;
	vm = vm_create_with_vcpus(mode, nr_vcpus, DEFAULT_GUEST_PHY_PAGES,
				  guest_num_pages, 0, guest_code, शून्य);

	/* Align करोwn GPA of the testing memslot */
	अगर (!p->phys_offset)
		guest_test_phys_mem = (vm_get_max_gfn(vm) - guest_num_pages) *
				       guest_page_size;
	अन्यथा
		guest_test_phys_mem = p->phys_offset;
#अगर_घोषित __s390x__
	alignment = max(0x100000, alignment);
#पूर्ण_अगर
	guest_test_phys_mem &= ~(alignment - 1);

	/* Set up the shared data काष्ठाure test_args */
	test_args.vm = vm;
	test_args.guest_test_virt_mem = guest_test_virt_mem;
	test_args.host_page_size = host_page_size;
	test_args.host_num_pages = test_mem_size / host_page_size;
	test_args.large_page_size = large_page_size;
	test_args.large_num_pages = test_mem_size / large_page_size;
	test_args.host_pages_per_lpage = large_page_size / host_page_size;
	test_args.src_type = src_type;

	क्रम (vcpu_id = 0; vcpu_id < KVM_MAX_VCPUS; vcpu_id++) अणु
		vcpu_args = &test_args.vcpu_args[vcpu_id];
		vcpu_args->vcpu_id = vcpu_id;
		vcpu_args->vcpu_ग_लिखो = !(vcpu_id % 2);
	पूर्ण

	/* Add an extra memory slot with specअगरied backing src type */
	vm_userspace_mem_region_add(vm, src_type, guest_test_phys_mem,
				    TEST_MEM_SLOT_INDEX, guest_num_pages, 0);

	/* Do mapping(GVA->GPA) क्रम the testing memory slot */
	virt_map(vm, guest_test_virt_mem, guest_test_phys_mem, guest_num_pages, 0);

	/* Cache the HVA poपूर्णांकer of the region */
	host_test_mem = addr_gpa2hva(vm, (vm_paddr_t)guest_test_phys_mem);

	/* Export shared काष्ठाure test_args to guest */
	ucall_init(vm, शून्य);
	sync_global_to_guest(vm, test_args);

	ret = sem_init(&test_stage_updated, 0, 0);
	TEST_ASSERT(ret == 0, "Error in sem_init");

	ret = sem_init(&test_stage_completed, 0, 0);
	TEST_ASSERT(ret == 0, "Error in sem_init");

	current_stage = addr_gva2hva(vm, (vm_vaddr_t)(&guest_test_stage));
	*current_stage = NUM_TEST_STAGES;

	pr_info("Testing guest mode: %s\n", vm_guest_mode_string(mode));
	pr_info("Testing memory backing src type: %s\n",
		vm_mem_backing_src_alias(src_type)->name);
	pr_info("Testing memory backing src granularity: 0x%lx\n",
		large_page_size);
	pr_info("Testing memory size(aligned): 0x%lx\n", test_mem_size);
	pr_info("Guest physical test memory offset: 0x%lx\n",
		guest_test_phys_mem);
	pr_info("Host  virtual  test memory offset: 0x%lx\n",
		(uपूर्णांक64_t)host_test_mem);
	pr_info("Number of testing vCPUs: %d\n", nr_vcpus);

	वापस vm;
पूर्ण

अटल व्योम vcpus_complete_new_stage(क्रमागत test_stage stage)
अणु
	पूर्णांक ret;
	पूर्णांक vcpus;

	/* Wake up all the vcpus to run new test stage */
	क्रम (vcpus = 0; vcpus < nr_vcpus; vcpus++) अणु
		ret = sem_post(&test_stage_updated);
		TEST_ASSERT(ret == 0, "Error in sem_post");
	पूर्ण
	pr_debug("All vcpus have been notified to continue\n");

	/* Wait क्रम all the vcpus to complete new test stage */
	क्रम (vcpus = 0; vcpus < nr_vcpus; vcpus++) अणु
		ret = sem_रुको(&test_stage_completed);
		TEST_ASSERT(ret == 0, "Error in sem_wait");

		pr_debug("%d vcpus have completed stage %s\n",
			 vcpus + 1, test_stage_string[stage]);
	पूर्ण

	pr_debug("All vcpus have completed stage %s\n",
		 test_stage_string[stage]);
पूर्ण

अटल व्योम run_test(क्रमागत vm_guest_mode mode, व्योम *arg)
अणु
	पूर्णांक ret;
	pthपढ़ो_t *vcpu_thपढ़ोs;
	काष्ठा kvm_vm *vm;
	पूर्णांक vcpu_id;
	काष्ठा बारpec start;
	काष्ठा बारpec ts_dअगरf;

	/* Create VM with vCPUs and make some pre-initialization */
	vm = pre_init_beक्रमe_test(mode, arg);

	vcpu_thपढ़ोs = दो_स्मृति(nr_vcpus * माप(*vcpu_thपढ़ोs));
	TEST_ASSERT(vcpu_thपढ़ोs, "Memory allocation failed");

	host_quit = false;
	*current_stage = KVM_BEFORE_MAPPINGS;

	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++) अणु
		pthपढ़ो_create(&vcpu_thपढ़ोs[vcpu_id], शून्य, vcpu_worker,
			       &test_args.vcpu_args[vcpu_id]);
	पूर्ण

	vcpus_complete_new_stage(*current_stage);
	pr_info("Started all vCPUs successfully\n");

	/* Test the stage of KVM creating mappings */
	*current_stage = KVM_CREATE_MAPPINGS;

	घड़ी_समय_लो(CLOCK_MONOTONIC_RAW, &start);
	vcpus_complete_new_stage(*current_stage);
	ts_dअगरf = बारpec_elapsed(start);

	pr_info("KVM_CREATE_MAPPINGS: total execution time: %ld.%.9lds\n\n",
		ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

	/* Test the stage of KVM updating mappings */
	vm_mem_region_set_flags(vm, TEST_MEM_SLOT_INDEX,
				KVM_MEM_LOG_सूचीTY_PAGES);

	*current_stage = KVM_UPDATE_MAPPINGS;

	घड़ी_समय_लो(CLOCK_MONOTONIC_RAW, &start);
	vcpus_complete_new_stage(*current_stage);
	ts_dअगरf = बारpec_elapsed(start);

	pr_info("KVM_UPDATE_MAPPINGS: total execution time: %ld.%.9lds\n\n",
		ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

	/* Test the stage of KVM adjusting mappings */
	vm_mem_region_set_flags(vm, TEST_MEM_SLOT_INDEX, 0);

	*current_stage = KVM_ADJUST_MAPPINGS;

	घड़ी_समय_लो(CLOCK_MONOTONIC_RAW, &start);
	vcpus_complete_new_stage(*current_stage);
	ts_dअगरf = बारpec_elapsed(start);

	pr_info("KVM_ADJUST_MAPPINGS: total execution time: %ld.%.9lds\n\n",
		ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

	/* Tell the vcpu thपढ़ो to quit */
	host_quit = true;
	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++) अणु
		ret = sem_post(&test_stage_updated);
		TEST_ASSERT(ret == 0, "Error in sem_post");
	पूर्ण

	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++)
		pthपढ़ो_join(vcpu_thपढ़ोs[vcpu_id], शून्य);

	ret = sem_destroy(&test_stage_updated);
	TEST_ASSERT(ret == 0, "Error in sem_destroy");

	ret = sem_destroy(&test_stage_completed);
	TEST_ASSERT(ret == 0, "Error in sem_destroy");

	मुक्त(vcpu_thपढ़ोs);
	ucall_uninit(vm);
	kvm_vm_मुक्त(vm);
पूर्ण

अटल व्योम help(अक्षर *name)
अणु
	माला_दो("");
	म_लिखो("usage: %s [-h] [-p offset] [-m mode] "
	       "[-b mem-size] [-v vcpus] [-s mem-type]\n", name);
	माला_दो("");
	म_लिखो(" -p: specify guest physical test memory offset\n"
	       "     Warning: a low offset can conflict with the loaded test code.\n");
	guest_modes_help();
	म_लिखो(" -b: specify size of the memory region for testing. e.g. 10M or 3G.\n"
	       "     (default: 1G)\n");
	म_लिखो(" -v: specify the number of vCPUs to run\n"
	       "     (default: 1)\n");
	म_लिखो(" -s: specify the type of memory that should be used to\n"
	       "     back the guest data region.\n"
	       "     (default: anonymous)\n\n");
	backing_src_help();
	माला_दो("");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक max_vcpus = kvm_check_cap(KVM_CAP_MAX_VCPUS);
	काष्ठा test_params p = अणु
		.test_mem_size = DEFAULT_TEST_MEM_SIZE,
		.src_type = VM_MEM_SRC_ANONYMOUS,
	पूर्ण;
	पूर्णांक opt;

	guest_modes_append_शेष();

	जबतक ((opt = getopt(argc, argv, "hp:m:b:v:s:")) != -1) अणु
		चयन (opt) अणु
		हाल 'p':
			p.phys_offset = म_से_अदीर्घl(optarg, शून्य, 0);
			अवरोध;
		हाल 'm':
			guest_modes_cmdline(optarg);
			अवरोध;
		हाल 'b':
			p.test_mem_size = parse_size(optarg);
			अवरोध;
		हाल 'v':
			nr_vcpus = म_से_प(optarg);
			TEST_ASSERT(nr_vcpus > 0 && nr_vcpus <= max_vcpus,
				    "Invalid number of vcpus, must be between 1 and %d", max_vcpus);
			अवरोध;
		हाल 's':
			p.src_type = parse_backing_src_type(optarg);
			अवरोध;
		हाल 'h':
		शेष:
			help(argv[0]);
			निकास(0);
		पूर्ण
	पूर्ण

	क्रम_each_guest_mode(run_test, &p);

	वापस 0;
पूर्ण
