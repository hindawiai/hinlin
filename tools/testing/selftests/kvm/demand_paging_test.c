<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KVM demand paging test
 * Adapted from dirty_log_test.c
 *
 * Copyright (C) 2018, Red Hat, Inc.
 * Copyright (C) 2019, Google, Inc.
 */

#घोषणा _GNU_SOURCE /* क्रम pipe2 */

#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <poll.h>
#समावेश <pthपढ़ो.h>
#समावेश <linux/userfaultfd.h>
#समावेश <sys/syscall.h>

#समावेश "kvm_util.h"
#समावेश "test_util.h"
#समावेश "perf_test_util.h"
#समावेश "guest_modes.h"

#अगर_घोषित __NR_userfaultfd

#अगर_घोषित PRINT_PER_PAGE_UPDATES
#घोषणा PER_PAGE_DEBUG(...) म_लिखो(__VA_ARGS__)
#अन्यथा
#घोषणा PER_PAGE_DEBUG(...) _no_म_लिखो(__VA_ARGS__)
#पूर्ण_अगर

#अगर_घोषित PRINT_PER_VCPU_UPDATES
#घोषणा PER_VCPU_DEBUG(...) म_लिखो(__VA_ARGS__)
#अन्यथा
#घोषणा PER_VCPU_DEBUG(...) _no_म_लिखो(__VA_ARGS__)
#पूर्ण_अगर

अटल पूर्णांक nr_vcpus = 1;
अटल uपूर्णांक64_t guest_percpu_mem_size = DEFAULT_PER_VCPU_MEM_SIZE;
अटल माप_प्रकार demand_paging_size;
अटल अक्षर *guest_data_prototype;

अटल व्योम *vcpu_worker(व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा perf_test_vcpu_args *vcpu_args = (काष्ठा perf_test_vcpu_args *)data;
	पूर्णांक vcpu_id = vcpu_args->vcpu_id;
	काष्ठा kvm_vm *vm = perf_test_args.vm;
	काष्ठा kvm_run *run;
	काष्ठा बारpec start;
	काष्ठा बारpec ts_dअगरf;

	vcpu_args_set(vm, vcpu_id, 1, vcpu_id);
	run = vcpu_state(vm, vcpu_id);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);

	/* Let the guest access its memory */
	ret = _vcpu_run(vm, vcpu_id);
	TEST_ASSERT(ret == 0, "vcpu_run failed: %d\n", ret);
	अगर (get_ucall(vm, vcpu_id, शून्य) != UCALL_SYNC) अणु
		TEST_ASSERT(false,
			    "Invalid guest sync status: exit_reason=%s\n",
			    निकास_reason_str(run->निकास_reason));
	पूर्ण

	ts_dअगरf = बारpec_elapsed(start);
	PER_VCPU_DEBUG("vCPU %d execution time: %ld.%.9lds\n", vcpu_id,
		       ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);

	वापस शून्य;
पूर्ण

अटल पूर्णांक handle_uffd_page_request(पूर्णांक uffd_mode, पूर्णांक uffd, uपूर्णांक64_t addr)
अणु
	pid_t tid = syscall(__NR_gettid);
	काष्ठा बारpec start;
	काष्ठा बारpec ts_dअगरf;
	पूर्णांक r;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);

	अगर (uffd_mode == UFFDIO_REGISTER_MODE_MISSING) अणु
		काष्ठा uffdio_copy copy;

		copy.src = (uपूर्णांक64_t)guest_data_prototype;
		copy.dst = addr;
		copy.len = demand_paging_size;
		copy.mode = 0;

		r = ioctl(uffd, UFFDIO_COPY, &copy);
		अगर (r == -1) अणु
			pr_info("Failed UFFDIO_COPY in 0x%lx from thread %d with errno: %d\n",
				addr, tid, त्रुटि_सं);
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अगर (uffd_mode == UFFDIO_REGISTER_MODE_MINOR) अणु
		काष्ठा uffdio_जारी cont = अणु0पूर्ण;

		cont.range.start = addr;
		cont.range.len = demand_paging_size;

		r = ioctl(uffd, UFFDIO_CONTINUE, &cont);
		अगर (r == -1) अणु
			pr_info("Failed UFFDIO_CONTINUE in 0x%lx from thread %d with errno: %d\n",
				addr, tid, त्रुटि_सं);
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अणु
		TEST_FAIL("Invalid uffd mode %d", uffd_mode);
	पूर्ण

	ts_dअगरf = बारpec_elapsed(start);

	PER_PAGE_DEBUG("UFFD page-in %d \t%ld ns\n", tid,
		       बारpec_to_ns(ts_dअगरf));
	PER_PAGE_DEBUG("Paged in %ld bytes at 0x%lx from thread %d\n",
		       demand_paging_size, addr, tid);

	वापस 0;
पूर्ण

bool quit_uffd_thपढ़ो;

काष्ठा uffd_handler_args अणु
	पूर्णांक uffd_mode;
	पूर्णांक uffd;
	पूर्णांक pipefd;
	useconds_t delay;
पूर्ण;

अटल व्योम *uffd_handler_thपढ़ो_fn(व्योम *arg)
अणु
	काष्ठा uffd_handler_args *uffd_args = (काष्ठा uffd_handler_args *)arg;
	पूर्णांक uffd = uffd_args->uffd;
	पूर्णांक pipefd = uffd_args->pipefd;
	useconds_t delay = uffd_args->delay;
	पूर्णांक64_t pages = 0;
	काष्ठा बारpec start;
	काष्ठा बारpec ts_dअगरf;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
	जबतक (!quit_uffd_thपढ़ो) अणु
		काष्ठा uffd_msg msg;
		काष्ठा pollfd pollfd[2];
		अक्षर पंचांगp_chr;
		पूर्णांक r;
		uपूर्णांक64_t addr;

		pollfd[0].fd = uffd;
		pollfd[0].events = POLLIN;
		pollfd[1].fd = pipefd;
		pollfd[1].events = POLLIN;

		r = poll(pollfd, 2, -1);
		चयन (r) अणु
		हाल -1:
			pr_info("poll err");
			जारी;
		हाल 0:
			जारी;
		हाल 1:
			अवरोध;
		शेष:
			pr_info("Polling uffd returned %d", r);
			वापस शून्य;
		पूर्ण

		अगर (pollfd[0].revents & POLLERR) अणु
			pr_info("uffd revents has POLLERR");
			वापस शून्य;
		पूर्ण

		अगर (pollfd[1].revents & POLLIN) अणु
			r = पढ़ो(pollfd[1].fd, &पंचांगp_chr, 1);
			TEST_ASSERT(r == 1,
				    "Error reading pipefd in UFFD thread\n");
			वापस शून्य;
		पूर्ण

		अगर (!pollfd[0].revents & POLLIN)
			जारी;

		r = पढ़ो(uffd, &msg, माप(msg));
		अगर (r == -1) अणु
			अगर (त्रुटि_सं == EAGAIN)
				जारी;
			pr_info("Read of uffd got errno %d\n", त्रुटि_सं);
			वापस शून्य;
		पूर्ण

		अगर (r != माप(msg)) अणु
			pr_info("Read on uffd returned unexpected size: %d bytes", r);
			वापस शून्य;
		पूर्ण

		अगर (!(msg.event & UFFD_EVENT_PAGEFAULT))
			जारी;

		अगर (delay)
			usleep(delay);
		addr =  msg.arg.pagefault.address;
		r = handle_uffd_page_request(uffd_args->uffd_mode, uffd, addr);
		अगर (r < 0)
			वापस शून्य;
		pages++;
	पूर्ण

	ts_dअगरf = बारpec_elapsed(start);
	PER_VCPU_DEBUG("userfaulted %ld pages over %ld.%.9lds. (%f/sec)\n",
		       pages, ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec,
		       pages / ((द्विगुन)ts_dअगरf.tv_sec + (द्विगुन)ts_dअगरf.tv_nsec / 100000000.0));

	वापस शून्य;
पूर्ण

अटल व्योम setup_demand_paging(काष्ठा kvm_vm *vm,
				pthपढ़ो_t *uffd_handler_thपढ़ो, पूर्णांक pipefd,
				पूर्णांक uffd_mode, useconds_t uffd_delay,
				काष्ठा uffd_handler_args *uffd_args,
				व्योम *hva, व्योम *alias, uपूर्णांक64_t len)
अणु
	bool is_minor = (uffd_mode == UFFDIO_REGISTER_MODE_MINOR);
	पूर्णांक uffd;
	काष्ठा uffdio_api uffdio_api;
	काष्ठा uffdio_रेजिस्टर uffdio_रेजिस्टर;
	uपूर्णांक64_t expected_ioctls = ((uपूर्णांक64_t) 1) << _UFFDIO_COPY;

	PER_PAGE_DEBUG("Userfaultfd %s mode, faults resolved with %s\n",
		       is_minor ? "MINOR" : "MISSING",
		       is_minor ? "UFFDIO_CONINUE" : "UFFDIO_COPY");

	/* In order to get minor faults, prefault via the alias. */
	अगर (is_minor) अणु
		माप_प्रकार p;

		expected_ioctls = ((uपूर्णांक64_t) 1) << _UFFDIO_CONTINUE;

		TEST_ASSERT(alias != शून्य, "Alias required for minor faults");
		क्रम (p = 0; p < (len / demand_paging_size); ++p) अणु
			स_नकल(alias + (p * demand_paging_size),
			       guest_data_prototype, demand_paging_size);
		पूर्ण
	पूर्ण

	uffd = syscall(__NR_userfaultfd, O_CLOEXEC | O_NONBLOCK);
	TEST_ASSERT(uffd >= 0, "uffd creation failed, errno: %d", त्रुटि_सं);

	uffdio_api.api = UFFD_API;
	uffdio_api.features = 0;
	TEST_ASSERT(ioctl(uffd, UFFDIO_API, &uffdio_api) != -1,
		    "ioctl UFFDIO_API failed: %" PRIu64,
		    (uपूर्णांक64_t)uffdio_api.api);

	uffdio_रेजिस्टर.range.start = (uपूर्णांक64_t)hva;
	uffdio_रेजिस्टर.range.len = len;
	uffdio_रेजिस्टर.mode = uffd_mode;
	TEST_ASSERT(ioctl(uffd, UFFDIO_REGISTER, &uffdio_रेजिस्टर) != -1,
		    "ioctl UFFDIO_REGISTER failed");
	TEST_ASSERT((uffdio_रेजिस्टर.ioctls & expected_ioctls) ==
		    expected_ioctls, "missing userfaultfd ioctls");

	uffd_args->uffd_mode = uffd_mode;
	uffd_args->uffd = uffd;
	uffd_args->pipefd = pipefd;
	uffd_args->delay = uffd_delay;
	pthपढ़ो_create(uffd_handler_thपढ़ो, शून्य, uffd_handler_thपढ़ो_fn,
		       uffd_args);

	PER_VCPU_DEBUG("Created uffd thread for HVA range [%p, %p)\n",
		       hva, hva + len);
पूर्ण

काष्ठा test_params अणु
	पूर्णांक uffd_mode;
	useconds_t uffd_delay;
	क्रमागत vm_mem_backing_src_type src_type;
	bool partition_vcpu_memory_access;
पूर्ण;

अटल व्योम run_test(क्रमागत vm_guest_mode mode, व्योम *arg)
अणु
	काष्ठा test_params *p = arg;
	pthपढ़ो_t *vcpu_thपढ़ोs;
	pthपढ़ो_t *uffd_handler_thपढ़ोs = शून्य;
	काष्ठा uffd_handler_args *uffd_args = शून्य;
	काष्ठा बारpec start;
	काष्ठा बारpec ts_dअगरf;
	पूर्णांक *pipefds = शून्य;
	काष्ठा kvm_vm *vm;
	पूर्णांक vcpu_id;
	पूर्णांक r;

	vm = perf_test_create_vm(mode, nr_vcpus, guest_percpu_mem_size,
				 p->src_type);

	perf_test_args.wr_fract = 1;

	demand_paging_size = get_backing_src_pagesz(p->src_type);

	guest_data_prototype = दो_स्मृति(demand_paging_size);
	TEST_ASSERT(guest_data_prototype,
		    "Failed to allocate buffer for guest data pattern");
	स_रखो(guest_data_prototype, 0xAB, demand_paging_size);

	vcpu_thपढ़ोs = दो_स्मृति(nr_vcpus * माप(*vcpu_thपढ़ोs));
	TEST_ASSERT(vcpu_thपढ़ोs, "Memory allocation failed");

	perf_test_setup_vcpus(vm, nr_vcpus, guest_percpu_mem_size,
			      p->partition_vcpu_memory_access);

	अगर (p->uffd_mode) अणु
		uffd_handler_thपढ़ोs =
			दो_स्मृति(nr_vcpus * माप(*uffd_handler_thपढ़ोs));
		TEST_ASSERT(uffd_handler_thपढ़ोs, "Memory allocation failed");

		uffd_args = दो_स्मृति(nr_vcpus * माप(*uffd_args));
		TEST_ASSERT(uffd_args, "Memory allocation failed");

		pipefds = दो_स्मृति(माप(पूर्णांक) * nr_vcpus * 2);
		TEST_ASSERT(pipefds, "Unable to allocate memory for pipefd");

		क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++) अणु
			vm_paddr_t vcpu_gpa;
			व्योम *vcpu_hva;
			व्योम *vcpu_alias;
			uपूर्णांक64_t vcpu_mem_size;


			अगर (p->partition_vcpu_memory_access) अणु
				vcpu_gpa = guest_test_phys_mem +
					   (vcpu_id * guest_percpu_mem_size);
				vcpu_mem_size = guest_percpu_mem_size;
			पूर्ण अन्यथा अणु
				vcpu_gpa = guest_test_phys_mem;
				vcpu_mem_size = guest_percpu_mem_size * nr_vcpus;
			पूर्ण
			PER_VCPU_DEBUG("Added VCPU %d with test mem gpa [%lx, %lx)\n",
				       vcpu_id, vcpu_gpa, vcpu_gpa + vcpu_mem_size);

			/* Cache the host addresses of the region */
			vcpu_hva = addr_gpa2hva(vm, vcpu_gpa);
			vcpu_alias = addr_gpa2alias(vm, vcpu_gpa);

			/*
			 * Set up user fault fd to handle demand paging
			 * requests.
			 */
			r = pipe2(&pipefds[vcpu_id * 2],
				  O_CLOEXEC | O_NONBLOCK);
			TEST_ASSERT(!r, "Failed to set up pipefd");

			setup_demand_paging(vm, &uffd_handler_thपढ़ोs[vcpu_id],
					    pipefds[vcpu_id * 2], p->uffd_mode,
					    p->uffd_delay, &uffd_args[vcpu_id],
					    vcpu_hva, vcpu_alias,
					    vcpu_mem_size);
		पूर्ण
	पूर्ण

	/* Export the shared variables to the guest */
	sync_global_to_guest(vm, perf_test_args);

	pr_info("Finished creating vCPUs and starting uffd threads\n");

	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);

	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++) अणु
		pthपढ़ो_create(&vcpu_thपढ़ोs[vcpu_id], शून्य, vcpu_worker,
			       &perf_test_args.vcpu_args[vcpu_id]);
	पूर्ण

	pr_info("Started all vCPUs\n");

	/* Wait क्रम the vcpu thपढ़ोs to quit */
	क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++) अणु
		pthपढ़ो_join(vcpu_thपढ़ोs[vcpu_id], शून्य);
		PER_VCPU_DEBUG("Joined thread for vCPU %d\n", vcpu_id);
	पूर्ण

	ts_dअगरf = बारpec_elapsed(start);

	pr_info("All vCPU threads joined\n");

	अगर (p->uffd_mode) अणु
		अक्षर c;

		/* Tell the user fault fd handler thपढ़ोs to quit */
		क्रम (vcpu_id = 0; vcpu_id < nr_vcpus; vcpu_id++) अणु
			r = ग_लिखो(pipefds[vcpu_id * 2 + 1], &c, 1);
			TEST_ASSERT(r == 1, "Unable to write to pipefd");

			pthपढ़ो_join(uffd_handler_thपढ़ोs[vcpu_id], शून्य);
		पूर्ण
	पूर्ण

	pr_info("Total guest execution time: %ld.%.9lds\n",
		ts_dअगरf.tv_sec, ts_dअगरf.tv_nsec);
	pr_info("Overall demand paging rate: %f pgs/sec\n",
		perf_test_args.vcpu_args[0].pages * nr_vcpus /
		((द्विगुन)ts_dअगरf.tv_sec + (द्विगुन)ts_dअगरf.tv_nsec / 100000000.0));

	perf_test_destroy_vm(vm);

	मुक्त(guest_data_prototype);
	मुक्त(vcpu_thपढ़ोs);
	अगर (p->uffd_mode) अणु
		मुक्त(uffd_handler_thपढ़ोs);
		मुक्त(uffd_args);
		मुक्त(pipefds);
	पूर्ण
पूर्ण

अटल व्योम help(अक्षर *name)
अणु
	माला_दो("");
	म_लिखो("usage: %s [-h] [-m vm_mode] [-u uffd_mode] [-d uffd_delay_usec]\n"
	       "          [-b memory] [-t type] [-v vcpus] [-o]\n", name);
	guest_modes_help();
	म_लिखो(" -u: use userfaultfd to handle vCPU page faults. Mode is a\n"
	       "     UFFD registration mode: 'MISSING' or 'MINOR'.\n");
	म_लिखो(" -d: add a delay in usec to the User Fault\n"
	       "     FD handler to simulate demand paging\n"
	       "     overheads. Ignored without -u.\n");
	म_लिखो(" -b: specify the size of the memory region which should be\n"
	       "     demand paged by each vCPU. e.g. 10M or 3G.\n"
	       "     Default: 1G\n");
	म_लिखो(" -t: The type of backing memory to use. Default: anonymous\n");
	backing_src_help();
	म_लिखो(" -v: specify the number of vCPUs to run.\n");
	म_लिखो(" -o: Overlap guest memory accesses instead of partitioning\n"
	       "     them into a separate region of memory for each vCPU.\n");
	माला_दो("");
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक max_vcpus = kvm_check_cap(KVM_CAP_MAX_VCPUS);
	काष्ठा test_params p = अणु
		.src_type = VM_MEM_SRC_ANONYMOUS,
		.partition_vcpu_memory_access = true,
	पूर्ण;
	पूर्णांक opt;

	guest_modes_append_शेष();

	जबतक ((opt = getopt(argc, argv, "hm:u:d:b:t:v:o")) != -1) अणु
		चयन (opt) अणु
		हाल 'm':
			guest_modes_cmdline(optarg);
			अवरोध;
		हाल 'u':
			अगर (!म_भेद("MISSING", optarg))
				p.uffd_mode = UFFDIO_REGISTER_MODE_MISSING;
			अन्यथा अगर (!म_भेद("MINOR", optarg))
				p.uffd_mode = UFFDIO_REGISTER_MODE_MINOR;
			TEST_ASSERT(p.uffd_mode, "UFFD mode must be 'MISSING' or 'MINOR'.");
			अवरोध;
		हाल 'd':
			p.uffd_delay = म_से_अदीर्घ(optarg, शून्य, 0);
			TEST_ASSERT(p.uffd_delay >= 0, "A negative UFFD delay is not supported.");
			अवरोध;
		हाल 'b':
			guest_percpu_mem_size = parse_size(optarg);
			अवरोध;
		हाल 't':
			p.src_type = parse_backing_src_type(optarg);
			अवरोध;
		हाल 'v':
			nr_vcpus = म_से_प(optarg);
			TEST_ASSERT(nr_vcpus > 0 && nr_vcpus <= max_vcpus,
				    "Invalid number of vcpus, must be between 1 and %d", max_vcpus);
			अवरोध;
		हाल 'o':
			p.partition_vcpu_memory_access = false;
			अवरोध;
		हाल 'h':
		शेष:
			help(argv[0]);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (p.uffd_mode == UFFDIO_REGISTER_MODE_MINOR &&
	    !backing_src_is_shared(p.src_type)) अणु
		TEST_FAIL("userfaultfd MINOR mode requires shared memory; pick a different -t");
	पूर्ण

	क्रम_each_guest_mode(run_test, &p);

	वापस 0;
पूर्ण

#अन्यथा /* __NR_userfaultfd */

#warning "missing __NR_userfaultfd definition"

पूर्णांक मुख्य(व्योम)
अणु
	prपूर्णांक_skip("__NR_userfaultfd must be present for userfaultfd test");
	वापस KSFT_SKIP;
पूर्ण

#पूर्ण_अगर /* __NR_userfaultfd */
