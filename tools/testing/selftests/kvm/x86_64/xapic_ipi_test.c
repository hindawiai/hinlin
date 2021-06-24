<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xapic_ipi_test
 *
 * Copyright (C) 2020, Google LLC.
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 *
 * Test that when the APIC is in xAPIC mode, a vCPU can send an IPI to wake
 * another vCPU that is halted when KVM's backing page क्रम the APIC access
 * address has been moved by mm.
 *
 * The test starts two vCPUs: one that sends IPIs and one that continually
 * executes HLT. The sender checks that the halter has woken from the HLT and
 * has reentered HLT beक्रमe sending the next IPI. While the vCPUs are running,
 * the host continually calls migrate_pages to move all of the process' pages
 * amongst the available numa nodes on the machine.
 *
 * Migration is a command line option. When used on non-numa machines will 
 * निकास with error. Test is still usefull on non-numa क्रम testing IPIs.
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <getopt.h>
#समावेश <pthपढ़ो.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <माला.स>
#समावेश <समय.स>

#समावेश "kvm_util.h"
#समावेश "numaif.h"
#समावेश "processor.h"
#समावेश "test_util.h"
#समावेश "vmx.h"

/* Default running समय क्रम the test */
#घोषणा DEFAULT_RUN_SECS 3

/* Default delay between migrate_pages calls (microseconds) */
#घोषणा DEFAULT_DELAY_USECS 500000

#घोषणा HALTER_VCPU_ID 0
#घोषणा SENDER_VCPU_ID 1

अस्थिर uपूर्णांक32_t *apic_base = (अस्थिर uपूर्णांक32_t *)APIC_DEFAULT_GPA;

/*
 * Vector क्रम IPI from sender vCPU to halting vCPU.
 * Value is arbitrary and was chosen क्रम the alternating bit pattern. Any
 * value should work.
 */
#घोषणा IPI_VECTOR	 0xa5

/*
 * Incremented in the IPI handler. Provides evidence to the sender that the IPI
 * arrived at the destination
 */
अटल अस्थिर uपूर्णांक64_t ipis_rcvd;

/* Data काष्ठा shared between host मुख्य thपढ़ो and vCPUs */
काष्ठा test_data_page अणु
	uपूर्णांक32_t halter_apic_id;
	अस्थिर uपूर्णांक64_t hlt_count;
	अस्थिर uपूर्णांक64_t wake_count;
	uपूर्णांक64_t ipis_sent;
	uपूर्णांक64_t migrations_attempted;
	uपूर्णांक64_t migrations_completed;
	uपूर्णांक32_t icr;
	uपूर्णांक32_t icr2;
	uपूर्णांक32_t halter_tpr;
	uपूर्णांक32_t halter_ppr;

	/*
	 *  Record local version रेजिस्टर as a cross-check that APIC access
	 *  worked. Value should match what KVM reports (APIC_VERSION in
	 *  arch/x86/kvm/lapic.c). If test is failing, check that values match
	 *  to determine whether APIC access निकासs are working.
	 */
	uपूर्णांक32_t halter_lvr;
पूर्ण;

काष्ठा thपढ़ो_params अणु
	काष्ठा test_data_page *data;
	काष्ठा kvm_vm *vm;
	uपूर्णांक32_t vcpu_id;
	uपूर्णांक64_t *pipis_rcvd; /* host address of ipis_rcvd global */
पूर्ण;

uपूर्णांक32_t पढ़ो_apic_reg(uपूर्णांक reg)
अणु
	वापस apic_base[reg >> 2];
पूर्ण

व्योम ग_लिखो_apic_reg(uपूर्णांक reg, uपूर्णांक32_t val)
अणु
	apic_base[reg >> 2] = val;
पूर्ण

व्योम disable_apic(व्योम)
अणु
	wrmsr(MSR_IA32_APICBASE,
	      rdmsr(MSR_IA32_APICBASE) &
		~(MSR_IA32_APICBASE_ENABLE | MSR_IA32_APICBASE_EXTD));
पूर्ण

व्योम enable_xapic(व्योम)
अणु
	uपूर्णांक64_t val = rdmsr(MSR_IA32_APICBASE);

	/* Per SDM: to enable xAPIC when in x2APIC must first disable APIC */
	अगर (val & MSR_IA32_APICBASE_EXTD) अणु
		disable_apic();
		wrmsr(MSR_IA32_APICBASE,
		      rdmsr(MSR_IA32_APICBASE) | MSR_IA32_APICBASE_ENABLE);
	पूर्ण अन्यथा अगर (!(val & MSR_IA32_APICBASE_ENABLE)) अणु
		wrmsr(MSR_IA32_APICBASE, val | MSR_IA32_APICBASE_ENABLE);
	पूर्ण

	/*
	 * Per SDM: reset value of spurious पूर्णांकerrupt vector रेजिस्टर has the
	 * APIC software enabled bit=0. It must be enabled in addition to the
	 * enable bit in the MSR.
	 */
	val = पढ़ो_apic_reg(APIC_SPIV) | APIC_SPIV_APIC_ENABLED;
	ग_लिखो_apic_reg(APIC_SPIV, val);
पूर्ण

व्योम verअगरy_apic_base_addr(व्योम)
अणु
	uपूर्णांक64_t msr = rdmsr(MSR_IA32_APICBASE);
	uपूर्णांक64_t base = GET_APIC_BASE(msr);

	GUEST_ASSERT(base == APIC_DEFAULT_GPA);
पूर्ण

अटल व्योम halter_guest_code(काष्ठा test_data_page *data)
अणु
	verअगरy_apic_base_addr();
	enable_xapic();

	data->halter_apic_id = GET_APIC_ID_FIELD(पढ़ो_apic_reg(APIC_ID));
	data->halter_lvr = पढ़ो_apic_reg(APIC_LVR);

	/*
	 * Loop क्रमever HLTing and recording halts & wakes. Disable पूर्णांकerrupts
	 * each समय around to minimize winकरोw between संकेतing the pending
	 * halt to the sender vCPU and executing the halt. No need to disable on
	 * first run as this vCPU executes first and the host रुकोs क्रम it to
	 * संकेत going पूर्णांकo first halt beक्रमe starting the sender vCPU. Record
	 * TPR and PPR क्रम diagnostic purposes in हाल the test fails.
	 */
	क्रम (;;) अणु
		data->halter_tpr = पढ़ो_apic_reg(APIC_TASKPRI);
		data->halter_ppr = पढ़ो_apic_reg(APIC_PROCPRI);
		data->hlt_count++;
		यंत्र अस्थिर("sti; hlt; cli");
		data->wake_count++;
	पूर्ण
पूर्ण

/*
 * Runs on halter vCPU when IPI arrives. Write an arbitrary non-zero value to
 * enable diagnosing errant ग_लिखोs to the APIC access address backing page in
 * हाल of test failure.
 */
अटल व्योम guest_ipi_handler(काष्ठा ex_regs *regs)
अणु
	ipis_rcvd++;
	ग_लिखो_apic_reg(APIC_EOI, 77);
पूर्ण

अटल व्योम sender_guest_code(काष्ठा test_data_page *data)
अणु
	uपूर्णांक64_t last_wake_count;
	uपूर्णांक64_t last_hlt_count;
	uपूर्णांक64_t last_ipis_rcvd_count;
	uपूर्णांक32_t icr_val;
	uपूर्णांक32_t icr2_val;
	uपूर्णांक64_t tsc_start;

	verअगरy_apic_base_addr();
	enable_xapic();

	/*
	 * Init पूर्णांकerrupt command रेजिस्टर क्रम sending IPIs
	 *
	 * Delivery mode=fixed, per SDM:
	 *   "Delivers the पूर्णांकerrupt specअगरied in the vector field to the target
	 *    processor."
	 *
	 * Destination mode=physical i.e. specअगरy target by its local APIC
	 * ID. This vCPU assumes that the halter vCPU has alपढ़ोy started and
	 * set data->halter_apic_id.
	 */
	icr_val = (APIC_DEST_PHYSICAL | APIC_DM_FIXED | IPI_VECTOR);
	icr2_val = SET_APIC_DEST_FIELD(data->halter_apic_id);
	data->icr = icr_val;
	data->icr2 = icr2_val;

	last_wake_count = data->wake_count;
	last_hlt_count = data->hlt_count;
	last_ipis_rcvd_count = ipis_rcvd;
	क्रम (;;) अणु
		/*
		 * Send IPI to halter vCPU.
		 * First IPI can be sent unconditionally because halter vCPU
		 * starts earlier.
		 */
		ग_लिखो_apic_reg(APIC_ICR2, icr2_val);
		ग_लिखो_apic_reg(APIC_ICR, icr_val);
		data->ipis_sent++;

		/*
		 * Wait up to ~1 sec क्रम halter to indicate that it has:
		 * 1. Received the IPI
		 * 2. Woken up from the halt
		 * 3. Gone back पूर्णांकo halt
		 * Current CPUs typically run at 2.x Ghz which is ~2
		 * billion ticks per second.
		 */
		tsc_start = rdtsc();
		जबतक (rdtsc() - tsc_start < 2000000000) अणु
			अगर ((ipis_rcvd != last_ipis_rcvd_count) &&
			    (data->wake_count != last_wake_count) &&
			    (data->hlt_count != last_hlt_count))
				अवरोध;
		पूर्ण

		GUEST_ASSERT((ipis_rcvd != last_ipis_rcvd_count) &&
			     (data->wake_count != last_wake_count) &&
			     (data->hlt_count != last_hlt_count));

		last_wake_count = data->wake_count;
		last_hlt_count = data->hlt_count;
		last_ipis_rcvd_count = ipis_rcvd;
	पूर्ण
पूर्ण

अटल व्योम *vcpu_thपढ़ो(व्योम *arg)
अणु
	काष्ठा thपढ़ो_params *params = (काष्ठा thपढ़ो_params *)arg;
	काष्ठा ucall uc;
	पूर्णांक old;
	पूर्णांक r;
	अचिन्हित पूर्णांक निकास_reason;

	r = pthपढ़ो_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old);
	TEST_ASSERT(r == 0,
		    "pthread_setcanceltype failed on vcpu_id=%u with errno=%d",
		    params->vcpu_id, r);

	ख_लिखो(मानक_त्रुटि, "vCPU thread running vCPU %u\n", params->vcpu_id);
	vcpu_run(params->vm, params->vcpu_id);
	निकास_reason = vcpu_state(params->vm, params->vcpu_id)->निकास_reason;

	TEST_ASSERT(निकास_reason == KVM_EXIT_IO,
		    "vCPU %u exited with unexpected exit reason %u-%s, expected KVM_EXIT_IO",
		    params->vcpu_id, निकास_reason, निकास_reason_str(निकास_reason));

	अगर (get_ucall(params->vm, params->vcpu_id, &uc) == UCALL_ABORT) अणु
		TEST_ASSERT(false,
			    "vCPU %u exited with error: %s.\n"
			    "Sending vCPU sent %lu IPIs to halting vCPU\n"
			    "Halting vCPU halted %lu times, woke %lu times, received %lu IPIs.\n"
			    "Halter TPR=%#x PPR=%#x LVR=%#x\n"
			    "Migrations attempted: %lu\n"
			    "Migrations completed: %lu\n",
			    params->vcpu_id, (स्थिर अक्षर *)uc.args[0],
			    params->data->ipis_sent, params->data->hlt_count,
			    params->data->wake_count,
			    *params->pipis_rcvd, params->data->halter_tpr,
			    params->data->halter_ppr, params->data->halter_lvr,
			    params->data->migrations_attempted,
			    params->data->migrations_completed);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम cancel_join_vcpu_thपढ़ो(pthपढ़ो_t thपढ़ो, uपूर्णांक32_t vcpu_id)
अणु
	व्योम *retval;
	पूर्णांक r;

	r = pthपढ़ो_cancel(thपढ़ो);
	TEST_ASSERT(r == 0,
		    "pthread_cancel on vcpu_id=%d failed with errno=%d",
		    vcpu_id, r);

	r = pthपढ़ो_join(thपढ़ो, &retval);
	TEST_ASSERT(r == 0,
		    "pthread_join on vcpu_id=%d failed with errno=%d",
		    vcpu_id, r);
	TEST_ASSERT(retval == PTHREAD_CANCELED,
		    "expected retval=%p, got %p", PTHREAD_CANCELED,
		    retval);
पूर्ण

व्योम करो_migrations(काष्ठा test_data_page *data, पूर्णांक run_secs, पूर्णांक delay_usecs,
		   uपूर्णांक64_t *pipis_rcvd)
अणु
	दीर्घ pages_not_moved;
	अचिन्हित दीर्घ nodemask = 0;
	अचिन्हित दीर्घ nodemasks[माप(nodemask) * 8];
	पूर्णांक nodes = 0;
	समय_प्रकार start_समय, last_update, now;
	समय_प्रकार पूर्णांकerval_secs = 1;
	पूर्णांक i, r;
	पूर्णांक from, to;
	अचिन्हित दीर्घ bit;
	uपूर्णांक64_t hlt_count;
	uपूर्णांक64_t wake_count;
	uपूर्णांक64_t ipis_sent;

	ख_लिखो(मानक_त्रुटि, "Calling migrate_pages every %d microseconds\n",
		delay_usecs);

	/* Get set of first 64 numa nodes available */
	r = get_mempolicy(शून्य, &nodemask, माप(nodemask) * 8,
			  0, MPOL_F_MEMS_ALLOWED);
	TEST_ASSERT(r == 0, "get_mempolicy failed errno=%d", त्रुटि_सं);

	ख_लिखो(मानक_त्रुटि, "Numa nodes found amongst first %lu possible nodes "
		"(each 1-bit indicates node is present): %#lx\n",
		माप(nodemask) * 8, nodemask);

	/* Init array of masks containing a single-bit in each, one क्रम each
	 * available node. migrate_pages called below requires specअगरying nodes
	 * as bit masks.
	 */
	क्रम (i = 0, bit = 1; i < माप(nodemask) * 8; i++, bit <<= 1) अणु
		अगर (nodemask & bit) अणु
			nodemasks[nodes] = nodemask & bit;
			nodes++;
		पूर्ण
	पूर्ण

	TEST_ASSERT(nodes > 1,
		    "Did not find at least 2 numa nodes. Can't do migration\n");

	ख_लिखो(मानक_त्रुटि, "Migrating amongst %d nodes found\n", nodes);

	from = 0;
	to = 1;
	start_समय = समय(शून्य);
	last_update = start_समय;

	ipis_sent = data->ipis_sent;
	hlt_count = data->hlt_count;
	wake_count = data->wake_count;

	जबतक ((पूर्णांक)(समय(शून्य) - start_समय) < run_secs) अणु
		data->migrations_attempted++;

		/*
		 * migrate_pages with PID=0 will migrate all pages of this
		 * process between the nodes specअगरied as biपंचांगasks. The page
		 * backing the APIC access address beदीर्घs to this process
		 * because it is allocated by KVM in the context of the
		 * KVM_CREATE_VCPU ioctl. If that assumption ever changes this
		 * test may अवरोध or give a false positive संकेत.
		 */
		pages_not_moved = migrate_pages(0, माप(nodemasks[from]),
						&nodemasks[from],
						&nodemasks[to]);
		अगर (pages_not_moved < 0)
			ख_लिखो(मानक_त्रुटि,
				"migrate_pages failed, errno=%d\n", त्रुटि_सं);
		अन्यथा अगर (pages_not_moved > 0)
			ख_लिखो(मानक_त्रुटि,
				"migrate_pages could not move %ld pages\n",
				pages_not_moved);
		अन्यथा
			data->migrations_completed++;

		from = to;
		to++;
		अगर (to == nodes)
			to = 0;

		now = समय(शून्य);
		अगर (((now - start_समय) % पूर्णांकerval_secs == 0) &&
		    (now != last_update)) अणु
			last_update = now;
			ख_लिखो(मानक_त्रुटि,
				"%lu seconds: Migrations attempted=%lu completed=%lu, "
				"IPIs sent=%lu received=%lu, HLTs=%lu wakes=%lu\n",
				now - start_समय, data->migrations_attempted,
				data->migrations_completed,
				data->ipis_sent, *pipis_rcvd,
				data->hlt_count, data->wake_count);

			TEST_ASSERT(ipis_sent != data->ipis_sent &&
				    hlt_count != data->hlt_count &&
				    wake_count != data->wake_count,
				    "IPI, HLT and wake count have not increased "
				    "in the last %lu seconds. "
				    "HLTer is likely hung.\n", पूर्णांकerval_secs);

			ipis_sent = data->ipis_sent;
			hlt_count = data->hlt_count;
			wake_count = data->wake_count;
		पूर्ण
		usleep(delay_usecs);
	पूर्ण
पूर्ण

व्योम get_cmdline_args(पूर्णांक argc, अक्षर *argv[], पूर्णांक *run_secs,
		      bool *migrate, पूर्णांक *delay_usecs)
अणु
	क्रम (;;) अणु
		पूर्णांक opt = getopt(argc, argv, "s:d:m");

		अगर (opt == -1)
			अवरोध;
		चयन (opt) अणु
		हाल 's':
			*run_secs = parse_size(optarg);
			अवरोध;
		हाल 'm':
			*migrate = true;
			अवरोध;
		हाल 'd':
			*delay_usecs = parse_size(optarg);
			अवरोध;
		शेष:
			TEST_ASSERT(false,
				    "Usage: -s <runtime seconds>. Default is %d seconds.\n"
				    "-m adds calls to migrate_pages while vCPUs are running."
				    " Default is no migrations.\n"
				    "-d <delay microseconds> - delay between migrate_pages() calls."
				    " Default is %d microseconds.\n",
				    DEFAULT_RUN_SECS, DEFAULT_DELAY_USECS);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक r;
	पूर्णांक रुको_secs;
	स्थिर पूर्णांक max_halter_रुको = 10;
	पूर्णांक run_secs = 0;
	पूर्णांक delay_usecs = 0;
	काष्ठा test_data_page *data;
	vm_vaddr_t test_data_page_vaddr;
	bool migrate = false;
	pthपढ़ो_t thपढ़ोs[2];
	काष्ठा thपढ़ो_params params[2];
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t *pipis_rcvd;

	get_cmdline_args(argc, argv, &run_secs, &migrate, &delay_usecs);
	अगर (run_secs <= 0)
		run_secs = DEFAULT_RUN_SECS;
	अगर (delay_usecs <= 0)
		delay_usecs = DEFAULT_DELAY_USECS;

	vm = vm_create_शेष(HALTER_VCPU_ID, 0, halter_guest_code);
	params[0].vm = vm;
	params[1].vm = vm;

	vm_init_descriptor_tables(vm);
	vcpu_init_descriptor_tables(vm, HALTER_VCPU_ID);
	vm_handle_exception(vm, IPI_VECTOR, guest_ipi_handler);

	virt_pg_map(vm, APIC_DEFAULT_GPA, APIC_DEFAULT_GPA, 0);

	vm_vcpu_add_शेष(vm, SENDER_VCPU_ID, sender_guest_code);

	test_data_page_vaddr = vm_vaddr_alloc(vm, 0x1000, 0x1000, 0, 0);
	data =
	   (काष्ठा test_data_page *)addr_gva2hva(vm, test_data_page_vaddr);
	स_रखो(data, 0, माप(*data));
	params[0].data = data;
	params[1].data = data;

	vcpu_args_set(vm, HALTER_VCPU_ID, 1, test_data_page_vaddr);
	vcpu_args_set(vm, SENDER_VCPU_ID, 1, test_data_page_vaddr);

	pipis_rcvd = (uपूर्णांक64_t *)addr_gva2hva(vm, (uपूर्णांक64_t)&ipis_rcvd);
	params[0].pipis_rcvd = pipis_rcvd;
	params[1].pipis_rcvd = pipis_rcvd;

	/* Start halter vCPU thपढ़ो and रुको क्रम it to execute first HLT. */
	params[0].vcpu_id = HALTER_VCPU_ID;
	r = pthपढ़ो_create(&thपढ़ोs[0], शून्य, vcpu_thपढ़ो, &params[0]);
	TEST_ASSERT(r == 0,
		    "pthread_create halter failed errno=%d", त्रुटि_सं);
	ख_लिखो(मानक_त्रुटि, "Halter vCPU thread started\n");

	रुको_secs = 0;
	जबतक ((रुको_secs < max_halter_रुको) && !data->hlt_count) अणु
		sleep(1);
		रुको_secs++;
	पूर्ण

	TEST_ASSERT(data->hlt_count,
		    "Halter vCPU did not execute first HLT within %d seconds",
		    max_halter_रुको);

	ख_लिखो(मानक_त्रुटि,
		"Halter vCPU thread reported its APIC ID: %u after %d seconds.\n",
		data->halter_apic_id, रुको_secs);

	params[1].vcpu_id = SENDER_VCPU_ID;
	r = pthपढ़ो_create(&thपढ़ोs[1], शून्य, vcpu_thपढ़ो, &params[1]);
	TEST_ASSERT(r == 0, "pthread_create sender failed errno=%d", त्रुटि_सं);

	ख_लिखो(मानक_त्रुटि,
		"IPI sender vCPU thread started. Letting vCPUs run for %d seconds.\n",
		run_secs);

	अगर (!migrate)
		sleep(run_secs);
	अन्यथा
		करो_migrations(data, run_secs, delay_usecs, pipis_rcvd);

	/*
	 * Cancel thपढ़ोs and रुको क्रम them to stop.
	 */
	cancel_join_vcpu_thपढ़ो(thपढ़ोs[0], HALTER_VCPU_ID);
	cancel_join_vcpu_thपढ़ो(thपढ़ोs[1], SENDER_VCPU_ID);

	ख_लिखो(मानक_त्रुटि,
		"Test successful after running for %d seconds.\n"
		"Sending vCPU sent %lu IPIs to halting vCPU\n"
		"Halting vCPU halted %lu times, woke %lu times, received %lu IPIs.\n"
		"Halter APIC ID=%#x\n"
		"Sender ICR value=%#x ICR2 value=%#x\n"
		"Halter TPR=%#x PPR=%#x LVR=%#x\n"
		"Migrations attempted: %lu\n"
		"Migrations completed: %lu\n",
		run_secs, data->ipis_sent,
		data->hlt_count, data->wake_count, *pipis_rcvd,
		data->halter_apic_id,
		data->icr, data->icr2,
		data->halter_tpr, data->halter_ppr, data->halter_lvr,
		data->migrations_attempted, data->migrations_completed);

	kvm_vm_मुक्त(vm);

	वापस 0;
पूर्ण
