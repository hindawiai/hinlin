<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KVM memslot modअगरication stress test
 * Adapted from demand_paging_test.c
 *
 * Copyright (C) 2018, Red Hat, Inc.
 * Copyright (C) 2020, Google, Inc.
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_name */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>
#समावेश <यंत्र/unistd.h>
#समावेश <समय.स>
#समावेश <poll.h>
#समावेश <pthपढ़ो.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/userfaultfd.h>

#समावेश "perf_test_util.h"
#समावेश "processor.h"
#समावेश "test_util.h"
#समावेश "guest_modes.h"

#घोषणा DUMMY_MEMSLOT_INDEX 7

#घोषणा DEFAULT_MEMSLOT_MODIFICATION_ITERATIONS 10


अटल पूर्णांक nr_vcpus = 1;
अटल uपूर्णांक64_t guest_percpu_mem_size = DEFAULT_PER_VCPU_MEM_SIZE;

अटल bool run_vcpus = true;

अटल व्योम *vcpu_worker(व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा perf_test_vcpu_args *vcpu_args =
		(काष्ठा perf_test_vcpu_args *)data;
	पूर्णांक vcpu_id = vcpu_args->vcpu_id;
	काष्ठा kvm_vm *vm = perf_test_args.vm;
	काष्ठा kvm_run *run;

	vcpu_args_set(vm, vcpu_id, 1, vcpu_id);
	run = vcpu_state(vm, vcpu_id);

	/* Let the guest access its memory until a stop संकेत is received */
	जबतक (READ_ONCE(run_vcpus)) अणु
		ret = _vcpu_run(vm, vcpu_id);
		TEST_ASSERT(ret == 0, "vcpu_run failed: %d\n", ret);

		अगर (get_ucall(vm, vcpu_id, शून्य) == UCALL_SYNC)
			जारी;

		TEST_ASSERT(false,
			    "Invalid guest sync status: exit_reason=%s\n",
			    निकास_reason_str(run->निकास_reason));
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा memslot_antagonist_args अणु
	काष्ठा kvm_vm *vm;
	useconds_t delay;
	uपूर्णांक64_t nr_modअगरications;
पूर्ण;

अटल व्योम add_हटाओ_memslot(काष्ठा kvm_vm *vm, useconds_t delay,
			       uपूर्णांक64_t nr_modअगरications)
अणु
	स्थिर uपूर्णांक64_t pages = 1;
	uपूर्णांक64_t gpa;
	पूर्णांक i;

	/*
	 * Add the dummy memslot just below the perf_test_util memslot, which is
	 * at the top of the guest physical address space.
	 */
	gpa = guest_test_phys_mem - pages * vm_get_page_size(vm);

	क्रम (i = 0; i < nr_modअगरications; i++) अणु
		usleep(delay);
		vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS, gpa,
					    DUMMY_MEMSLOT_INDEX, pages, 0);

		vm_mem_region_delete(vm, DUMMY_MEMSLOT_INDEX);
	पूर्ण
पूर्ण

काष्ठा test_params अणु
	useconds_t memslot_modअगरication_delay;
	uपूर्णांक64_t nr_memslot_modअगरications;
	bool partition_vcpu_memory_access;
पूर्ण;

अटल व्योम run_test(क्रमागत vm_guest_mode mode, व्योम *arg)
अणु
	काष्ठा test_params *p = arg;
	pthपढ़ो_t *vcpu_thपढ़ोs;
	काष्ठा kvm_vm *vm;
	पूर्णांक vcpu_id;

	vm = perf_test_create_vm(mode, nr_vcpus, guest_percpu_mem_size,
				 VM_MEM_SRC_ANONYMOUS);

	perf_test_args.wr_fract = 1;

	vcpu_thपढ़ोs = दो_स्मृति(nr_vcpus * माप(*vcpu_thपढ़ोs));
	TEST_ASSERT(vcpu_thपढ़ोs, "Memory allocation failed");

	perf_test_setup_vcpus(vm, nr_vcpus, guest_percpu_mem_size,
			      p->partition_vcpu_memory_access);

	/* Export the shared variables to the guest */
	sync_global_to_guest(vm, perf_test_args);

	pr_info("Finished creating vCPUs\n");

	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++)
		pthपढ़ो_create(&vcpu_thपढ़ोs[vcpu_id], शून्य, vcpu_worker,
			       &perf_test_args.vcpu_args[vcpu_id]);

	pr_info("Started all vCPUs\n");

	add_हटाओ_memslot(vm, p->memslot_modअगरication_delay,
			   p->nr_memslot_modअगरications);

	run_vcpus = false;

	/* Wait क्रम the vcpu thपढ़ोs to quit */
	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++)
		pthपढ़ो_join(vcpu_thपढ़ोs[vcpu_id], शून्य);

	pr_info("All vCPU threads joined\n");

	ucall_uninit(vm);
	kvm_vm_मुक्त(vm);

	मुक्त(vcpu_thपढ़ोs);
पूर्ण

अटल व्योम help(अक्षर *name)
अणु
	माला_दो("");
	म_लिखो("usage: %s [-h] [-m mode] [-d delay_usec]\n"
	       "          [-b memory] [-v vcpus] [-o] [-i iterations]\n", name);
	guest_modes_help();
	म_लिखो(" -d: add a delay between each iteration of adding and\n"
	       "     deleting a memslot in usec.\n");
	म_लिखो(" -b: specify the size of the memory region which should be\n"
	       "     accessed by each vCPU. e.g. 10M or 3G.\n"
	       "     Default: 1G\n");
	म_लिखो(" -v: specify the number of vCPUs to run.\n");
	म_लिखो(" -o: Overlap guest memory accesses instead of partitioning\n"
	       "     them into a separate region of memory for each vCPU.\n");
	म_लिखो(" -i: specify the number of iterations of adding and removing\n"
	       "     a memslot.\n"
	       "     Default: %d\n", DEFAULT_MEMSLOT_MODIFICATION_ITERATIONS);
	माला_दो("");
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक max_vcpus = kvm_check_cap(KVM_CAP_MAX_VCPUS);
	पूर्णांक opt;
	काष्ठा test_params p = अणु
		.memslot_modअगरication_delay = 0,
		.nr_memslot_modअगरications =
			DEFAULT_MEMSLOT_MODIFICATION_ITERATIONS,
		.partition_vcpu_memory_access = true
	पूर्ण;

	guest_modes_append_शेष();

	जबतक ((opt = getopt(argc, argv, "hm:d:b:v:oi:")) != -1) अणु
		चयन (opt) अणु
		हाल 'm':
			guest_modes_cmdline(optarg);
			अवरोध;
		हाल 'd':
			p.memslot_modअगरication_delay = म_से_अदीर्घ(optarg, शून्य, 0);
			TEST_ASSERT(p.memslot_modअगरication_delay >= 0,
				    "A negative delay is not supported.");
			अवरोध;
		हाल 'b':
			guest_percpu_mem_size = parse_size(optarg);
			अवरोध;
		हाल 'v':
			nr_vcpus = म_से_प(optarg);
			TEST_ASSERT(nr_vcpus > 0 && nr_vcpus <= max_vcpus,
				    "Invalid number of vcpus, must be between 1 and %d",
				    max_vcpus);
			अवरोध;
		हाल 'o':
			p.partition_vcpu_memory_access = false;
			अवरोध;
		हाल 'i':
			p.nr_memslot_modअगरications = म_से_प(optarg);
			अवरोध;
		हाल 'h':
		शेष:
			help(argv[0]);
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम_each_guest_mode(run_test, &p);

	वापस 0;
पूर्ण
