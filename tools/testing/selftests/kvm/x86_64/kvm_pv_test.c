<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020, Google LLC.
 *
 * Tests क्रम KVM paraभव feature disablement
 */
#समावेश <यंत्र/kvm_para.h>
#समावेश <linux/kvm_para.h>
#समावेश <मानक_निवेशt.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"

बाह्य अचिन्हित अक्षर rdmsr_start;
बाह्य अचिन्हित अक्षर rdmsr_end;

अटल u64 करो_rdmsr(u32 idx)
अणु
	u32 lo, hi;

	यंत्र अस्थिर("rdmsr_start: rdmsr;"
		     "rdmsr_end:"
		     : "=a"(lo), "=c"(hi)
		     : "c"(idx));

	वापस (((u64) hi) << 32) | lo;
पूर्ण

बाह्य अचिन्हित अक्षर wrmsr_start;
बाह्य अचिन्हित अक्षर wrmsr_end;

अटल व्योम करो_wrmsr(u32 idx, u64 val)
अणु
	u32 lo, hi;

	lo = val;
	hi = val >> 32;

	यंत्र अस्थिर("wrmsr_start: wrmsr;"
		     "wrmsr_end:"
		     : : "a"(lo), "c"(idx), "d"(hi));
पूर्ण

अटल पूर्णांक nr_gp;

अटल व्योम guest_gp_handler(काष्ठा ex_regs *regs)
अणु
	अचिन्हित अक्षर *rip = (अचिन्हित अक्षर *)regs->rip;
	bool r, w;

	r = rip == &rdmsr_start;
	w = rip == &wrmsr_start;
	GUEST_ASSERT(r || w);

	nr_gp++;

	अगर (r)
		regs->rip = (uपूर्णांक64_t)&rdmsr_end;
	अन्यथा
		regs->rip = (uपूर्णांक64_t)&wrmsr_end;
पूर्ण

काष्ठा msr_data अणु
	uपूर्णांक32_t idx;
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा TEST_MSR(msr) अणु .idx = msr, .name = #msr पूर्ण
#घोषणा UCALL_PR_MSR 0xdeadbeef
#घोषणा PR_MSR(msr) ucall(UCALL_PR_MSR, 1, msr)

/*
 * KVM paraभव msrs to test. Expect a #GP अगर any of these msrs are पढ़ो or
 * written, as the KVM_CPUID_FEATURES leaf is cleared.
 */
अटल काष्ठा msr_data msrs_to_test[] = अणु
	TEST_MSR(MSR_KVM_SYSTEM_TIME),
	TEST_MSR(MSR_KVM_SYSTEM_TIME_NEW),
	TEST_MSR(MSR_KVM_WALL_CLOCK),
	TEST_MSR(MSR_KVM_WALL_CLOCK_NEW),
	TEST_MSR(MSR_KVM_ASYNC_PF_EN),
	TEST_MSR(MSR_KVM_STEAL_TIME),
	TEST_MSR(MSR_KVM_PV_EOI_EN),
	TEST_MSR(MSR_KVM_POLL_CONTROL),
	TEST_MSR(MSR_KVM_ASYNC_PF_INT),
	TEST_MSR(MSR_KVM_ASYNC_PF_ACK),
पूर्ण;

अटल व्योम test_msr(काष्ठा msr_data *msr)
अणु
	PR_MSR(msr);
	करो_rdmsr(msr->idx);
	GUEST_ASSERT(READ_ONCE(nr_gp) == 1);

	nr_gp = 0;
	करो_wrmsr(msr->idx, 0);
	GUEST_ASSERT(READ_ONCE(nr_gp) == 1);
	nr_gp = 0;
पूर्ण

काष्ठा hcall_data अणु
	uपूर्णांक64_t nr;
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा TEST_HCALL(hc) अणु .nr = hc, .name = #hc पूर्ण
#घोषणा UCALL_PR_HCALL 0xdeadc0de
#घोषणा PR_HCALL(hc) ucall(UCALL_PR_HCALL, 1, hc)

/*
 * KVM hypercalls to test. Expect -KVM_ENOSYS when called, as the corresponding
 * features have been cleared in KVM_CPUID_FEATURES.
 */
अटल काष्ठा hcall_data hcalls_to_test[] = अणु
	TEST_HCALL(KVM_HC_KICK_CPU),
	TEST_HCALL(KVM_HC_SEND_IPI),
	TEST_HCALL(KVM_HC_SCHED_YIELD),
पूर्ण;

अटल व्योम test_hcall(काष्ठा hcall_data *hc)
अणु
	uपूर्णांक64_t r;

	PR_HCALL(hc);
	r = kvm_hypercall(hc->nr, 0, 0, 0, 0);
	GUEST_ASSERT(r == -KVM_ENOSYS);
पूर्ण

अटल व्योम guest_मुख्य(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(msrs_to_test); i++) अणु
		test_msr(&msrs_to_test[i]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(hcalls_to_test); i++) अणु
		test_hcall(&hcalls_to_test[i]);
	पूर्ण

	GUEST_DONE();
पूर्ण

अटल व्योम clear_kvm_cpuid_features(काष्ठा kvm_cpuid2 *cpuid)
अणु
	काष्ठा kvm_cpuid_entry2 ent = अणु0पूर्ण;

	ent.function = KVM_CPUID_FEATURES;
	TEST_ASSERT(set_cpuid(cpuid, &ent),
		    "failed to clear KVM_CPUID_FEATURES leaf");
पूर्ण

अटल व्योम pr_msr(काष्ठा ucall *uc)
अणु
	काष्ठा msr_data *msr = (काष्ठा msr_data *)uc->args[0];

	pr_info("testing msr: %s (%#x)\n", msr->name, msr->idx);
पूर्ण

अटल व्योम pr_hcall(काष्ठा ucall *uc)
अणु
	काष्ठा hcall_data *hc = (काष्ठा hcall_data *)uc->args[0];

	pr_info("testing hcall: %s (%lu)\n", hc->name, hc->nr);
पूर्ण

अटल व्योम handle_पात(काष्ठा ucall *uc)
अणु
	TEST_FAIL("%s at %s:%ld", (स्थिर अक्षर *)uc->args[0],
		  __खाता__, uc->args[1]);
पूर्ण

#घोषणा VCPU_ID 0

अटल व्योम enter_guest(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_run *run;
	काष्ठा ucall uc;
	पूर्णांक r;

	run = vcpu_state(vm, VCPU_ID);

	जबतक (true) अणु
		r = _vcpu_run(vm, VCPU_ID);
		TEST_ASSERT(!r, "vcpu_run failed: %d\n", r);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "unexpected exit reason: %u (%s)",
			    run->निकास_reason, निकास_reason_str(run->निकास_reason));

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_PR_MSR:
			pr_msr(&uc);
			अवरोध;
		हाल UCALL_PR_HCALL:
			pr_hcall(&uc);
			अवरोध;
		हाल UCALL_ABORT:
			handle_पात(&uc);
			वापस;
		हाल UCALL_DONE:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा kvm_enable_cap cap = अणु0पूर्ण;
	काष्ठा kvm_cpuid2 *best;
	काष्ठा kvm_vm *vm;

	अगर (!kvm_check_cap(KVM_CAP_ENFORCE_PV_FEATURE_CPUID)) अणु
		prपूर्णांक_skip("KVM_CAP_ENFORCE_PV_FEATURE_CPUID not supported");
		निकास(KSFT_SKIP);
	पूर्ण

	vm = vm_create_शेष(VCPU_ID, 0, guest_मुख्य);

	cap.cap = KVM_CAP_ENFORCE_PV_FEATURE_CPUID;
	cap.args[0] = 1;
	vcpu_enable_cap(vm, VCPU_ID, &cap);

	best = kvm_get_supported_cpuid();
	clear_kvm_cpuid_features(best);
	vcpu_set_cpuid(vm, VCPU_ID, best);

	vm_init_descriptor_tables(vm);
	vcpu_init_descriptor_tables(vm, VCPU_ID);
	vm_handle_exception(vm, GP_VECTOR, guest_gp_handler);

	enter_guest(vm);
	kvm_vm_मुक्त(vm);
पूर्ण
