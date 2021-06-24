<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KVM dirty page logging perक्रमmance test
 *
 * Based on dirty_log_test.c
 *
 * Copyright (C) 2018, Red Hat, Inc.
 * Copyright (C) 2020, Google, Inc.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <pthपढ़ो.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "kvm_util.h"
#समावेश "test_util.h"
#समावेश "perf_test_util.h"
#समावेश "guest_modes.h"

/* How many host loops to run by शेष (one KVM_GET_सूचीTY_LOG क्रम each loop)*/
#घोषणा TEST_HOST_LOOP_N		2UL

अटल पूर्णांक nr_vcpus = 1;
अटल uपूर्णांक64_t guest_percpu_mem_size = DEFAULT_PER_VCPU_MEM_SIZE;

/* Host variables */
अटल u64 dirty_log_manual_caps;
अटल bool host_quit;
अटल पूर्णांक iteration;
अटल पूर्णांक vcpu_last_completed_iteration[KVM_MAX_VCPUS];

अटल व्योम *vcpu_worker(व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा kvm_vm *vm = perf_test_args.vm;
	uपूर्णांक64_t pages_count = 0;
	काष्ठा kvm_run *run;
	काष्ठा बारpec start;
	काष्ठा बारpec ts_dअगरf;
	काष्ठा बारpec total = (काष्ठा बारpec)अणु0पूर्ण;
	काष्ठा बारpec avg;
	काष्ठा perf_test_vcpu_args *vcpu_args = (काष्ठा perf_test_vcpu_args *)data;
	पूर्णांक vcpu_id = vcpu_args->vcpu_id;

	vcpu_args_set(vm, vcpu_id, 1, vcpu_id);
	run = vcpu_state(vm, vcpu_id);

	जबतक (!READ_ONCE(host_quit)) अणु
		पूर्णांक current_iteration = READ_ONCE(iteration);

		घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
		ret = _vcpu_run(vm, vcpu_id);
		ts_dअगरf = बारpec_elapsed(start);

		TEST_ASSERT(ret == 0, "vcpu_run failed: %d\n", ret);
		TEST_ASSERT(get_ucall(vm, vcpu_id, शून्य) == UCALL_SYNC,
			    "Invalid guest sync status: exit_reason=%s\n",
			    निकास_reason_str(run->निकास_reason));

		pr_debug("Got sync event from vCPU %d\n", vcpu_id);
		vcpu_last_completed_iteration[vcpu_id] = current_iteration;
		pr_debug("vCPU %d updated last completed iteration to %d\n",
			 vcpu_id, vcpu_last_completed_iteration[vcpu_id]);

		अगर (current_iteration) अणु
			pages_count += vcpu_args->pages;
			total = बारpec_add(total, ts_dअगरf);
			pr_debug("vCPU %d iteration %d dirty memory time: %ld.%.9lds\n",
				vcpu_id, current_iteration, ts_dअगरf.tv_sec,
				ts_dअगरf.tv_nsec);
		पूर्ण अन्यथा अणु
			pr_debug("vCPU %d iteration %d populate memory time: %ld.%.9lds\n",
				vcpu_id, current_iteration, ts_dअगरf.tv_sec,
				ts_dअगरf.tv_nsec);
		पूर्ण

		जबतक (current_iteration == READ_ONCE(iteration) &&
		       !READ_ONCE(host_quit)) अणुपूर्ण
	पूर्ण

	avg = बारpec_भाग(total, vcpu_last_completed_iteration[vcpu_id]);
	pr_debug("\nvCPU %d dirtied 0x%lx pages over %d iterations in %ld.%.9lds. (Avg %ld.%.9lds/iteration)\n",
		vcpu_id, pages_count, vcpu_last_completed_iteration[vcpu_id],
		total.tv_sec, total.tv_nsec, avg.tv_sec, avg.tv_nsec);

	वापस शून्य;
पूर्ण

काष्ठा test_params अणु
	अचिन्हित दीर्घ iterations;
	uपूर्णांक64_t phys_offset;
	पूर्णांक wr_fract;
	bool partition_vcpu_memory_access;
	क्रमागत vm_mem_backing_src_type backing_src;
पूर्ण;

अटल व्योम run_test(क्रमागत vm_guest_mode mode, व्योम *arg)
अणु
	काष्ठा test_params *p = arg;
	pthपढ़ो_t *vcpu_thपढ़ोs;
	काष्ठा kvm_vm *vm;
	अचिन्हित दीर्घ *bmap;
	uपूर्णांक64_t guest_num_pages;
	uपूर्णांक64_t host_num_pages;
	पूर्णांक vcpu_id;
	काष्ठा बारpec start;
	काष्ठा बारpec ts_dअगरf;
	काष्ठा बारpec get_dirty_log_total = (काष्ठा बारpec)अणु0पूर्ण;
	काष्ठा बारpec vcpu_dirty_total = (काष्ठा बारpec)अणु0पूर्ण;
	काष्ठा बारpec avg;
	काष्ठा kvm_enable_cap cap = अणुपूर्ण;
	काष्ठा बारpec clear_dirty_log_total = (काष्ठा बारpec)अणु0पूर्ण;

	vm = perf_test_create_vm(mode, nr_vcpus, guest_percpu_mem_size,
				 p->backing_src);

	perf_test_args.wr_fract = p->wr_fract;

	guest_num_pages = (nr_vcpus * guest_percpu_mem_size) >> vm_get_page_shअगरt(vm);
	guest_num_pages = vm_adjust_num_guest_pages(mode, guest_num_pages);
	host_num_pages = vm_num_host_pages(mode, guest_num_pages);
	bmap = biपंचांगap_alloc(host_num_pages);

	अगर (dirty_log_manual_caps) अणु
		cap.cap = KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT2;
		cap.args[0] = dirty_log_manual_caps;
		vm_enable_cap(vm, &cap);
	पूर्ण

	vcpu_thपढ़ोs = दो_स्मृति(nr_vcpus * माप(*vcpu_thपढ़ोs));
	TEST_ASSERT(vcpu_thपढ़ोs, "Memory allocation failed");

	perf_test_setup_vcpus(vm, nr_vcpus, guest_percpu_mem_size,
			      p->partition_vcpu_memory_access);

	sync_global_to_guest(vm, perf_test_args);

	/* Start the iterations */
	iteration = 0;
	host_quit = false;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++) अणु
		vcpu_last_completed_iteration[vcpu_id] = -1;

		pthपढ़ो_create(&vcpu_thपढ़ोs[vcpu_id], शून्य, vcpu_worker,
			       &perf_test_args.vcpu_args[vcpu_id]);
	पूर्ण

	/* Allow the vCPUs to populate memory */
	pr_debug("Starting iteration %d - Populating\n", iteration);
	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++) अणु
		जबतक (READ_ONCE(vcpu_last_completed_iteration[vcpu_id]) !=
		       iteration)
			;
	पूर्ण

	ts_dअगरf = बारpec_elapsed(start);
	pr_info("Populate memory time: %ld.%.9lds\n",
		ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

	/* Enable dirty logging */
	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
	vm_mem_region_set_flags(vm, PERF_TEST_MEM_SLOT_INDEX,
				KVM_MEM_LOG_सूचीTY_PAGES);
	ts_dअगरf = बारpec_elapsed(start);
	pr_info("Enabling dirty logging time: %ld.%.9lds\n\n",
		ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

	जबतक (iteration < p->iterations) अणु
		/*
		 * Incrementing the iteration number will start the vCPUs
		 * dirtying memory again.
		 */
		घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
		iteration++;

		pr_debug("Starting iteration %d\n", iteration);
		क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++) अणु
			जबतक (READ_ONCE(vcpu_last_completed_iteration[vcpu_id])
			       != iteration)
				;
		पूर्ण

		ts_dअगरf = बारpec_elapsed(start);
		vcpu_dirty_total = बारpec_add(vcpu_dirty_total, ts_dअगरf);
		pr_info("Iteration %d dirty memory time: %ld.%.9lds\n",
			iteration, ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

		घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
		kvm_vm_get_dirty_log(vm, PERF_TEST_MEM_SLOT_INDEX, bmap);

		ts_dअगरf = बारpec_elapsed(start);
		get_dirty_log_total = बारpec_add(get_dirty_log_total,
						   ts_dअगरf);
		pr_info("Iteration %d get dirty log time: %ld.%.9lds\n",
			iteration, ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

		अगर (dirty_log_manual_caps) अणु
			घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
			kvm_vm_clear_dirty_log(vm, PERF_TEST_MEM_SLOT_INDEX, bmap, 0,
					       host_num_pages);

			ts_dअगरf = बारpec_elapsed(start);
			clear_dirty_log_total = बारpec_add(clear_dirty_log_total,
							     ts_dअगरf);
			pr_info("Iteration %d clear dirty log time: %ld.%.9lds\n",
				iteration, ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);
		पूर्ण
	पूर्ण

	/* Disable dirty logging */
	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
	vm_mem_region_set_flags(vm, PERF_TEST_MEM_SLOT_INDEX, 0);
	ts_dअगरf = बारpec_elapsed(start);
	pr_info("Disabling dirty logging time: %ld.%.9lds\n",
		ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

	/* Tell the vcpu thपढ़ो to quit */
	host_quit = true;
	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++)
		pthपढ़ो_join(vcpu_thपढ़ोs[vcpu_id], शून्य);

	avg = बारpec_भाग(get_dirty_log_total, p->iterations);
	pr_info("Get dirty log over %lu iterations took %ld.%.9lds. (Avg %ld.%.9lds/iteration)\n",
		p->iterations, get_dirty_log_total.tv_sec,
		get_dirty_log_total.tv_nsec, avg.tv_sec, avg.tv_nsec);

	अगर (dirty_log_manual_caps) अणु
		avg = बारpec_भाग(clear_dirty_log_total, p->iterations);
		pr_info("Clear dirty log over %lu iterations took %ld.%.9lds. (Avg %ld.%.9lds/iteration)\n",
			p->iterations, clear_dirty_log_total.tv_sec,
			clear_dirty_log_total.tv_nsec, avg.tv_sec, avg.tv_nsec);
	पूर्ण

	मुक्त(bmap);
	मुक्त(vcpu_thपढ़ोs);
	perf_test_destroy_vm(vm);
पूर्ण

अटल व्योम help(अक्षर *name)
अणु
	माला_दो("");
	म_लिखो("usage: %s [-h] [-i iterations] [-p offset] "
	       "[-m mode] [-b vcpu bytes] [-v vcpus] [-o] [-s mem type]\n", name);
	माला_दो("");
	म_लिखो(" -i: specify iteration counts (default: %"PRIu64")\n",
	       TEST_HOST_LOOP_N);
	म_लिखो(" -p: specify guest physical test memory offset\n"
	       "     Warning: a low offset can conflict with the loaded test code.\n");
	guest_modes_help();
	म_लिखो(" -b: specify the size of the memory region which should be\n"
	       "     dirtied by each vCPU. e.g. 10M or 3G.\n"
	       "     (default: 1G)\n");
	म_लिखो(" -f: specify the fraction of pages which should be written to\n"
	       "     as opposed to simply read, in the form\n"
	       "     1/<fraction of pages to write>.\n"
	       "     (default: 1 i.e. all pages are written to.)\n");
	म_लिखो(" -v: specify the number of vCPUs to run.\n");
	म_लिखो(" -o: Overlap guest memory accesses instead of partitioning\n"
	       "     them into a separate region of memory for each vCPU.\n");
	म_लिखो(" -s: specify the type of memory that should be used to\n"
	       "     back the guest data region.\n\n");
	backing_src_help();
	माला_दो("");
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक max_vcpus = kvm_check_cap(KVM_CAP_MAX_VCPUS);
	काष्ठा test_params p = अणु
		.iterations = TEST_HOST_LOOP_N,
		.wr_fract = 1,
		.partition_vcpu_memory_access = true,
		.backing_src = VM_MEM_SRC_ANONYMOUS,
	पूर्ण;
	पूर्णांक opt;

	dirty_log_manual_caps =
		kvm_check_cap(KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT2);
	dirty_log_manual_caps &= (KVM_सूचीTY_LOG_MANUAL_PROTECT_ENABLE |
				  KVM_सूचीTY_LOG_INITIALLY_SET);

	guest_modes_append_शेष();

	जबतक ((opt = getopt(argc, argv, "hi:p:m:b:f:v:os:")) != -1) अणु
		चयन (opt) अणु
		हाल 'i':
			p.iterations = म_से_प(optarg);
			अवरोध;
		हाल 'p':
			p.phys_offset = म_से_अदीर्घl(optarg, शून्य, 0);
			अवरोध;
		हाल 'm':
			guest_modes_cmdline(optarg);
			अवरोध;
		हाल 'b':
			guest_percpu_mem_size = parse_size(optarg);
			अवरोध;
		हाल 'f':
			p.wr_fract = म_से_प(optarg);
			TEST_ASSERT(p.wr_fract >= 1,
				    "Write fraction cannot be less than one");
			अवरोध;
		हाल 'v':
			nr_vcpus = म_से_प(optarg);
			TEST_ASSERT(nr_vcpus > 0 && nr_vcpus <= max_vcpus,
				    "Invalid number of vcpus, must be between 1 and %d", max_vcpus);
			अवरोध;
		हाल 'o':
			p.partition_vcpu_memory_access = false;
		हाल 's':
			p.backing_src = parse_backing_src_type(optarg);
			अवरोध;
		हाल 'h':
		शेष:
			help(argv[0]);
			अवरोध;
		पूर्ण
	पूर्ण

	TEST_ASSERT(p.iterations >= 2, "The test should have at least two iterations");

	pr_info("Test iterations: %"PRIu64"\n",	p.iterations);

	क्रम_each_guest_mode(run_test, &p);

	वापस 0;
पूर्ण
