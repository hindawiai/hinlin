<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2021, Red Hat, Inc.
 *
 * Tests क्रम Hyper-V घड़ीsources
 */
#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"

काष्ठा ms_hyperv_tsc_page अणु
	अस्थिर u32 tsc_sequence;
	u32 reserved1;
	अस्थिर u64 tsc_scale;
	अस्थिर s64 tsc_offset;
पूर्ण __packed;

#घोषणा HV_X64_MSR_GUEST_OS_ID			0x40000000
#घोषणा HV_X64_MSR_TIME_REF_COUNT		0x40000020
#घोषणा HV_X64_MSR_REFERENCE_TSC		0x40000021
#घोषणा HV_X64_MSR_TSC_FREQUENCY		0x40000022
#घोषणा HV_X64_MSR_REENLIGHTENMENT_CONTROL	0x40000106
#घोषणा HV_X64_MSR_TSC_EMULATION_CONTROL	0x40000107

/* Simplअगरied mul_u64_u64_shr() */
अटल अंतरभूत u64 mul_u64_u64_shr64(u64 a, u64 b)
अणु
	जोड़ अणु
		u64 ll;
		काष्ठा अणु
			u32 low, high;
		पूर्ण l;
	पूर्ण rm, rn, rh, a0, b0;
	u64 c;

	a0.ll = a;
	b0.ll = b;

	rm.ll = (u64)a0.l.low * b0.l.high;
	rn.ll = (u64)a0.l.high * b0.l.low;
	rh.ll = (u64)a0.l.high * b0.l.high;

	rh.l.low = c = rm.l.high + rn.l.high + rh.l.low;
	rh.l.high = (c >> 32) + rh.l.high;

	वापस rh.ll;
पूर्ण

अटल अंतरभूत व्योम nop_loop(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 1000000; i++)
		यंत्र अस्थिर("nop");
पूर्ण

अटल अंतरभूत व्योम check_tsc_msr_rdtsc(व्योम)
अणु
	u64 tsc_freq, r1, r2, t1, t2;
	s64 delta_ns;

	tsc_freq = rdmsr(HV_X64_MSR_TSC_FREQUENCY);
	GUEST_ASSERT(tsc_freq > 0);

	/* First, check MSR-based घड़ीsource */
	r1 = rdtsc();
	t1 = rdmsr(HV_X64_MSR_TIME_REF_COUNT);
	nop_loop();
	r2 = rdtsc();
	t2 = rdmsr(HV_X64_MSR_TIME_REF_COUNT);

	GUEST_ASSERT(r2 > r1 && t2 > t1);

	/* HV_X64_MSR_TIME_REF_COUNT is in 100ns */
	delta_ns = ((t2 - t1) * 100) - ((r2 - r1) * 1000000000 / tsc_freq);
	अगर (delta_ns < 0)
		delta_ns = -delta_ns;

	/* 1% tolerance */
	GUEST_ASSERT(delta_ns * 100 < (t2 - t1) * 100);
पूर्ण

अटल अंतरभूत u64 get_tscpage_ts(काष्ठा ms_hyperv_tsc_page *tsc_page)
अणु
	वापस mul_u64_u64_shr64(rdtsc(), tsc_page->tsc_scale) + tsc_page->tsc_offset;
पूर्ण

अटल अंतरभूत व्योम check_tsc_msr_tsc_page(काष्ठा ms_hyperv_tsc_page *tsc_page)
अणु
	u64 r1, r2, t1, t2;

	/* Compare TSC page घड़ीsource with HV_X64_MSR_TIME_REF_COUNT */
	t1 = get_tscpage_ts(tsc_page);
	r1 = rdmsr(HV_X64_MSR_TIME_REF_COUNT);

	/* 10 ms tolerance */
	GUEST_ASSERT(r1 >= t1 && r1 - t1 < 100000);
	nop_loop();

	t2 = get_tscpage_ts(tsc_page);
	r2 = rdmsr(HV_X64_MSR_TIME_REF_COUNT);
	GUEST_ASSERT(r2 >= t1 && r2 - t2 < 100000);
पूर्ण

अटल व्योम guest_मुख्य(काष्ठा ms_hyperv_tsc_page *tsc_page, vm_paddr_t tsc_page_gpa)
अणु
	u64 tsc_scale, tsc_offset;

	/* Set Guest OS id to enable Hyper-V emulation */
	GUEST_SYNC(1);
	wrmsr(HV_X64_MSR_GUEST_OS_ID, (u64)0x8100 << 48);
	GUEST_SYNC(2);

	check_tsc_msr_rdtsc();

	GUEST_SYNC(3);

	/* Set up TSC page is disabled state, check that it's clean */
	wrmsr(HV_X64_MSR_REFERENCE_TSC, tsc_page_gpa);
	GUEST_ASSERT(tsc_page->tsc_sequence == 0);
	GUEST_ASSERT(tsc_page->tsc_scale == 0);
	GUEST_ASSERT(tsc_page->tsc_offset == 0);

	GUEST_SYNC(4);

	/* Set up TSC page is enabled state */
	wrmsr(HV_X64_MSR_REFERENCE_TSC, tsc_page_gpa | 0x1);
	GUEST_ASSERT(tsc_page->tsc_sequence != 0);

	GUEST_SYNC(5);

	check_tsc_msr_tsc_page(tsc_page);

	GUEST_SYNC(6);

	tsc_offset = tsc_page->tsc_offset;
	/* Call KVM_SET_CLOCK from userspace, check that TSC page was updated */

	GUEST_SYNC(7);
	/* Sanity check TSC page बारtamp, it should be बंद to 0 */
	GUEST_ASSERT(get_tscpage_ts(tsc_page) < 100000);

	GUEST_ASSERT(tsc_page->tsc_offset != tsc_offset);

	nop_loop();

	/*
	 * Enable Re-enlightenment and check that TSC page stays स्थिरant across
	 * KVM_SET_CLOCK.
	 */
	wrmsr(HV_X64_MSR_REENLIGHTENMENT_CONTROL, 0x1 << 16 | 0xff);
	wrmsr(HV_X64_MSR_TSC_EMULATION_CONTROL, 0x1);
	tsc_offset = tsc_page->tsc_offset;
	tsc_scale = tsc_page->tsc_scale;
	GUEST_SYNC(8);
	GUEST_ASSERT(tsc_page->tsc_offset == tsc_offset);
	GUEST_ASSERT(tsc_page->tsc_scale == tsc_scale);

	GUEST_SYNC(9);

	check_tsc_msr_tsc_page(tsc_page);

	/*
	 * Disable re-enlightenment and TSC page, check that KVM करोesn't update
	 * it anymore.
	 */
	wrmsr(HV_X64_MSR_REENLIGHTENMENT_CONTROL, 0);
	wrmsr(HV_X64_MSR_TSC_EMULATION_CONTROL, 0);
	wrmsr(HV_X64_MSR_REFERENCE_TSC, 0);
	स_रखो(tsc_page, 0, माप(*tsc_page));

	GUEST_SYNC(10);
	GUEST_ASSERT(tsc_page->tsc_sequence == 0);
	GUEST_ASSERT(tsc_page->tsc_offset == 0);
	GUEST_ASSERT(tsc_page->tsc_scale == 0);

	GUEST_DONE();
पूर्ण

#घोषणा VCPU_ID 0

अटल व्योम host_check_tsc_msr_rdtsc(काष्ठा kvm_vm *vm)
अणु
	u64 tsc_freq, r1, r2, t1, t2;
	s64 delta_ns;

	tsc_freq = vcpu_get_msr(vm, VCPU_ID, HV_X64_MSR_TSC_FREQUENCY);
	TEST_ASSERT(tsc_freq > 0, "TSC frequency must be nonzero");

	/* First, check MSR-based घड़ीsource */
	r1 = rdtsc();
	t1 = vcpu_get_msr(vm, VCPU_ID, HV_X64_MSR_TIME_REF_COUNT);
	nop_loop();
	r2 = rdtsc();
	t2 = vcpu_get_msr(vm, VCPU_ID, HV_X64_MSR_TIME_REF_COUNT);

	TEST_ASSERT(t2 > t1, "Time reference MSR is not monotonic (%ld <= %ld)", t1, t2);

	/* HV_X64_MSR_TIME_REF_COUNT is in 100ns */
	delta_ns = ((t2 - t1) * 100) - ((r2 - r1) * 1000000000 / tsc_freq);
	अगर (delta_ns < 0)
		delta_ns = -delta_ns;

	/* 1% tolerance */
	TEST_ASSERT(delta_ns * 100 < (t2 - t1) * 100,
		    "Elapsed time does not match (MSR=%ld, TSC=%ld)",
		    (t2 - t1) * 100, (r2 - r1) * 1000000000 / tsc_freq);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_run *run;
	काष्ठा ucall uc;
	vm_vaddr_t tsc_page_gva;
	पूर्णांक stage;

	vm = vm_create_शेष(VCPU_ID, 0, guest_मुख्य);
	run = vcpu_state(vm, VCPU_ID);

	vcpu_set_hv_cpuid(vm, VCPU_ID);

	tsc_page_gva = vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	स_रखो(addr_gpa2hva(vm, tsc_page_gva), 0x0, getpagesize());
	TEST_ASSERT((addr_gva2gpa(vm, tsc_page_gva) & (getpagesize() - 1)) == 0,
		"TSC page has to be page aligned\n");
	vcpu_args_set(vm, VCPU_ID, 2, tsc_page_gva, addr_gva2gpa(vm, tsc_page_gva));

	host_check_tsc_msr_rdtsc(vm);

	क्रम (stage = 1;; stage++) अणु
		_vcpu_run(vm, VCPU_ID);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "Stage %d: unexpected exit reason: %u (%s),\n",
			    stage, run->निकास_reason,
			    निकास_reason_str(run->निकास_reason));

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_ABORT:
			TEST_FAIL("%s at %s:%ld", (स्थिर अक्षर *)uc.args[0],
				  __खाता__, uc.args[1]);
			/* NOT REACHED */
		हाल UCALL_SYNC:
			अवरोध;
		हाल UCALL_DONE:
			/* Keep in sync with guest_मुख्य() */
			TEST_ASSERT(stage == 11, "Testing ended prematurely, stage %d\n",
				    stage);
			जाओ out;
		शेष:
			TEST_FAIL("Unknown ucall %lu", uc.cmd);
		पूर्ण

		TEST_ASSERT(!म_भेद((स्थिर अक्षर *)uc.args[0], "hello") &&
			    uc.args[1] == stage,
			    "Stage %d: Unexpected register values vmexit, got %lx",
			    stage, (uदीर्घ)uc.args[1]);

		/* Reset kvmघड़ी triggering TSC page update */
		अगर (stage == 7 || stage == 8 || stage == 10) अणु
			काष्ठा kvm_घड़ी_data घड़ी = अणु0पूर्ण;

			vm_ioctl(vm, KVM_SET_CLOCK, &घड़ी);
		पूर्ण
	पूर्ण

out:
	kvm_vm_मुक्त(vm);
पूर्ण
