<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * svm_vmcall_test
 *
 * Copyright तऊ 2021 Amazon.com, Inc. or its affiliates.
 *
 * Xen shared_info / pvघड़ी testing
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"

#समावेश <मानक_निवेशt.h>
#समावेश <समय.स>
#समावेश <sched.h>
#समावेश <sys/syscall.h>

#घोषणा VCPU_ID		5

#घोषणा SHINFO_REGION_GVA	0xc0000000ULL
#घोषणा SHINFO_REGION_GPA	0xc0000000ULL
#घोषणा SHINFO_REGION_SLOT	10
#घोषणा PAGE_SIZE		4096

#घोषणा PVTIME_ADDR	(SHINFO_REGION_GPA + PAGE_SIZE)
#घोषणा RUNSTATE_ADDR	(SHINFO_REGION_GPA + PAGE_SIZE + 0x20)

#घोषणा RUNSTATE_VADDR	(SHINFO_REGION_GVA + PAGE_SIZE + 0x20)

अटल काष्ठा kvm_vm *vm;

#घोषणा XEN_HYPERCALL_MSR	0x40000000

#घोषणा MIN_STEAL_TIME		50000

काष्ठा pvघड़ी_vcpu_समय_info अणु
        u32   version;
        u32   pad0;
        u64   tsc_बारtamp;
        u64   प्रणाली_समय;
        u32   tsc_to_प्रणाली_mul;
        s8    tsc_shअगरt;
        u8    flags;
        u8    pad[2];
पूर्ण __attribute__((__packed__)); /* 32 bytes */

काष्ठा pvघड़ी_wall_घड़ी अणु
        u32   version;
        u32   sec;
        u32   nsec;
पूर्ण __attribute__((__packed__));

काष्ठा vcpu_runstate_info अणु
    uपूर्णांक32_t state;
    uपूर्णांक64_t state_entry_समय;
    uपूर्णांक64_t समय[4];
पूर्ण;

#घोषणा RUNSTATE_running  0
#घोषणा RUNSTATE_runnable 1
#घोषणा RUNSTATE_blocked  2
#घोषणा RUNSTATE_offline  3

अटल व्योम guest_code(व्योम)
अणु
	काष्ठा vcpu_runstate_info *rs = (व्योम *)RUNSTATE_VADDR;

	/* Test having the host set runstates manually */
	GUEST_SYNC(RUNSTATE_runnable);
	GUEST_ASSERT(rs->समय[RUNSTATE_runnable] != 0);
	GUEST_ASSERT(rs->state == 0);

	GUEST_SYNC(RUNSTATE_blocked);
	GUEST_ASSERT(rs->समय[RUNSTATE_blocked] != 0);
	GUEST_ASSERT(rs->state == 0);

	GUEST_SYNC(RUNSTATE_offline);
	GUEST_ASSERT(rs->समय[RUNSTATE_offline] != 0);
	GUEST_ASSERT(rs->state == 0);

	/* Test runstate समय adjust */
	GUEST_SYNC(4);
	GUEST_ASSERT(rs->समय[RUNSTATE_blocked] == 0x5a);
	GUEST_ASSERT(rs->समय[RUNSTATE_offline] == 0x6b6b);

	/* Test runstate समय set */
	GUEST_SYNC(5);
	GUEST_ASSERT(rs->state_entry_समय >= 0x8000);
	GUEST_ASSERT(rs->समय[RUNSTATE_runnable] == 0);
	GUEST_ASSERT(rs->समय[RUNSTATE_blocked] == 0x6b6b);
	GUEST_ASSERT(rs->समय[RUNSTATE_offline] == 0x5a);

	/* sched_yield() should result in some 'runnable' समय */
	GUEST_SYNC(6);
	GUEST_ASSERT(rs->समय[RUNSTATE_runnable] >= MIN_STEAL_TIME);

	GUEST_DONE();
पूर्ण

अटल दीर्घ get_run_delay(व्योम)
अणु
        अक्षर path[64];
        दीर्घ val[2];
        खाता *fp;

        प्र_लिखो(path, "/proc/%ld/schedstat", syscall(SYS_gettid));
        fp = ख_खोलो(path, "r");
        ख_पूछो(fp, "%ld %ld ", &val[0], &val[1]);
        ख_बंद(fp);

        वापस val[1];
पूर्ण

अटल पूर्णांक cmp_बारpec(काष्ठा बारpec *a, काष्ठा बारpec *b)
अणु
	अगर (a->tv_sec > b->tv_sec)
		वापस 1;
	अन्यथा अगर (a->tv_sec < b->tv_sec)
		वापस -1;
	अन्यथा अगर (a->tv_nsec > b->tv_nsec)
		वापस 1;
	अन्यथा अगर (a->tv_nsec < b->tv_nsec)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा बारpec min_ts, max_ts, vm_ts;

	पूर्णांक xen_caps = kvm_check_cap(KVM_CAP_XEN_HVM);
	अगर (!(xen_caps & KVM_XEN_HVM_CONFIG_SHARED_INFO) ) अणु
		prपूर्णांक_skip("KVM_XEN_HVM_CONFIG_SHARED_INFO not available");
		निकास(KSFT_SKIP);
	पूर्ण

	bool करो_runstate_tests = !!(xen_caps & KVM_XEN_HVM_CONFIG_RUNSTATE);

	घड़ी_समय_लो(CLOCK_REALTIME, &min_ts);

	vm = vm_create_शेष(VCPU_ID, 0, (व्योम *) guest_code);
	vcpu_set_cpuid(vm, VCPU_ID, kvm_get_supported_cpuid());

	/* Map a region क्रम the shared_info page */
	vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS,
				    SHINFO_REGION_GPA, SHINFO_REGION_SLOT, 2, 0);
	virt_map(vm, SHINFO_REGION_GVA, SHINFO_REGION_GPA, 2, 0);

	काष्ठा kvm_xen_hvm_config hvmc = अणु
		.flags = KVM_XEN_HVM_CONFIG_INTERCEPT_HCALL,
		.msr = XEN_HYPERCALL_MSR,
	पूर्ण;
	vm_ioctl(vm, KVM_XEN_HVM_CONFIG, &hvmc);

	काष्ठा kvm_xen_hvm_attr lm = अणु
		.type = KVM_XEN_ATTR_TYPE_LONG_MODE,
		.u.दीर्घ_mode = 1,
	पूर्ण;
	vm_ioctl(vm, KVM_XEN_HVM_SET_ATTR, &lm);

	काष्ठा kvm_xen_hvm_attr ha = अणु
		.type = KVM_XEN_ATTR_TYPE_SHARED_INFO,
		.u.shared_info.gfn = SHINFO_REGION_GPA / PAGE_SIZE,
	पूर्ण;
	vm_ioctl(vm, KVM_XEN_HVM_SET_ATTR, &ha);

	काष्ठा kvm_xen_vcpu_attr vi = अणु
		.type = KVM_XEN_VCPU_ATTR_TYPE_VCPU_INFO,
		.u.gpa = SHINFO_REGION_GPA + 0x40,
	पूर्ण;
	vcpu_ioctl(vm, VCPU_ID, KVM_XEN_VCPU_SET_ATTR, &vi);

	काष्ठा kvm_xen_vcpu_attr pvघड़ी = अणु
		.type = KVM_XEN_VCPU_ATTR_TYPE_VCPU_TIME_INFO,
		.u.gpa = PVTIME_ADDR,
	पूर्ण;
	vcpu_ioctl(vm, VCPU_ID, KVM_XEN_VCPU_SET_ATTR, &pvघड़ी);

	अगर (करो_runstate_tests) अणु
		काष्ठा kvm_xen_vcpu_attr st = अणु
			.type = KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_ADDR,
			.u.gpa = RUNSTATE_ADDR,
		पूर्ण;
		vcpu_ioctl(vm, VCPU_ID, KVM_XEN_VCPU_SET_ATTR, &st);
	पूर्ण

	काष्ठा vcpu_runstate_info *rs = addr_gpa2hva(vm, RUNSTATE_ADDR);
	rs->state = 0x5a;

	क्रम (;;) अणु
		अस्थिर काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);
		काष्ठा ucall uc;

		vcpu_run(vm, VCPU_ID);

		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "Got exit_reason other than KVM_EXIT_IO: %u (%s)\n",
			    run->निकास_reason,
			    निकास_reason_str(run->निकास_reason));

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_ABORT:
			TEST_FAIL("%s", (स्थिर अक्षर *)uc.args[0]);
			/* NOT REACHED */
		हाल UCALL_SYNC: अणु
			काष्ठा kvm_xen_vcpu_attr rst;
			दीर्घ rundelay;

			/* If no runstate support, bail out early */
			अगर (!करो_runstate_tests)
				जाओ करोne;

			TEST_ASSERT(rs->state_entry_समय == rs->समय[0] +
				    rs->समय[1] + rs->समय[2] + rs->समय[3],
				    "runstate times don't add up");

			चयन (uc.args[1]) अणु
			हाल RUNSTATE_running...RUNSTATE_offline:
				rst.type = KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_CURRENT;
				rst.u.runstate.state = uc.args[1];
				vcpu_ioctl(vm, VCPU_ID, KVM_XEN_VCPU_SET_ATTR, &rst);
				अवरोध;
			हाल 4:
				rst.type = KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_ADJUST;
				स_रखो(&rst.u, 0, माप(rst.u));
				rst.u.runstate.state = (uपूर्णांक64_t)-1;
				rst.u.runstate.समय_blocked =
					0x5a - rs->समय[RUNSTATE_blocked];
				rst.u.runstate.समय_offline =
					0x6b6b - rs->समय[RUNSTATE_offline];
				rst.u.runstate.समय_runnable = -rst.u.runstate.समय_blocked -
					rst.u.runstate.समय_offline;
				vcpu_ioctl(vm, VCPU_ID, KVM_XEN_VCPU_SET_ATTR, &rst);
				अवरोध;

			हाल 5:
				rst.type = KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_DATA;
				स_रखो(&rst.u, 0, माप(rst.u));
				rst.u.runstate.state = RUNSTATE_running;
				rst.u.runstate.state_entry_समय = 0x6b6b + 0x5a;
				rst.u.runstate.समय_blocked = 0x6b6b;
				rst.u.runstate.समय_offline = 0x5a;
				vcpu_ioctl(vm, VCPU_ID, KVM_XEN_VCPU_SET_ATTR, &rst);
				अवरोध;
			हाल 6:
				/* Yield until scheduler delay exceeds target */
				rundelay = get_run_delay() + MIN_STEAL_TIME;
				करो अणु
					sched_yield();
				पूर्ण जबतक (get_run_delay() < rundelay);
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		हाल UCALL_DONE:
			जाओ करोne;
		शेष:
			TEST_FAIL("Unknown ucall 0x%lx.", uc.cmd);
		पूर्ण
	पूर्ण

 करोne:
	घड़ी_समय_लो(CLOCK_REALTIME, &max_ts);

	/*
	 * Just a *really* basic check that things are being put in the
	 * right place. The actual calculations are much the same क्रम
	 * Xen as they are क्रम the KVM variants, so no need to check.
	 */
	काष्ठा pvघड़ी_wall_घड़ी *wc;
	काष्ठा pvघड़ी_vcpu_समय_info *ti, *ti2;

	wc = addr_gpa2hva(vm, SHINFO_REGION_GPA + 0xc00);
	ti = addr_gpa2hva(vm, SHINFO_REGION_GPA + 0x40 + 0x20);
	ti2 = addr_gpa2hva(vm, PVTIME_ADDR);

	vm_ts.tv_sec = wc->sec;
	vm_ts.tv_nsec = wc->nsec;
        TEST_ASSERT(wc->version && !(wc->version & 1),
		    "Bad wallclock version %x", wc->version);
	TEST_ASSERT(cmp_बारpec(&min_ts, &vm_ts) <= 0, "VM time too old");
	TEST_ASSERT(cmp_बारpec(&max_ts, &vm_ts) >= 0, "VM time too new");

	TEST_ASSERT(ti->version && !(ti->version & 1),
		    "Bad time_info version %x", ti->version);
	TEST_ASSERT(ti2->version && !(ti2->version & 1),
		    "Bad time_info version %x", ti->version);

	अगर (करो_runstate_tests) अणु
		/*
		 * Fetch runstate and check sanity. Strictly speaking in the
		 * general हाल we might not expect the numbers to be identical
		 * but in this हाल we know we aren't running the vCPU any more.
		 */
		काष्ठा kvm_xen_vcpu_attr rst = अणु
			.type = KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_DATA,
		पूर्ण;
		vcpu_ioctl(vm, VCPU_ID, KVM_XEN_VCPU_GET_ATTR, &rst);

		TEST_ASSERT(rs->state == rst.u.runstate.state, "Runstate mismatch");
		TEST_ASSERT(rs->state_entry_समय == rst.u.runstate.state_entry_समय,
			    "State entry time mismatch");
		TEST_ASSERT(rs->समय[RUNSTATE_running] == rst.u.runstate.समय_running,
			    "Running time mismatch");
		TEST_ASSERT(rs->समय[RUNSTATE_runnable] == rst.u.runstate.समय_runnable,
			    "Runnable time mismatch");
		TEST_ASSERT(rs->समय[RUNSTATE_blocked] == rst.u.runstate.समय_blocked,
			    "Blocked time mismatch");
		TEST_ASSERT(rs->समय[RUNSTATE_offline] == rst.u.runstate.समय_offline,
			    "Offline time mismatch");

		TEST_ASSERT(rs->state_entry_समय == rs->समय[0] +
			    rs->समय[1] + rs->समय[2] + rs->समय[3],
			    "runstate times don't add up");
	पूर्ण
	kvm_vm_मुक्त(vm);
	वापस 0;
पूर्ण
