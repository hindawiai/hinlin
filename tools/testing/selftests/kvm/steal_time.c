<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * steal/stolen समय test
 *
 * Copyright (C) 2020, Red Hat, Inc.
 */
#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <समय.स>
#समावेश <sched.h>
#समावेश <pthपढ़ो.h>
#समावेश <linux/kernel.h>
#समावेश <sys/syscall.h>
#समावेश <यंत्र/kvm.h>
#समावेश <यंत्र/kvm_para.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"

#घोषणा NR_VCPUS		4
#घोषणा ST_GPA_BASE		(1 << 30)
#घोषणा MIN_RUN_DELAY_NS	200000UL

अटल व्योम *st_gva[NR_VCPUS];
अटल uपूर्णांक64_t guest_stolen_समय[NR_VCPUS];

#अगर defined(__x86_64__)

/* steal_समय must have 64-byte alignment */
#घोषणा STEAL_TIME_SIZE		((माप(काष्ठा kvm_steal_समय) + 63) & ~63)

अटल व्योम check_status(काष्ठा kvm_steal_समय *st)
अणु
	GUEST_ASSERT(!(READ_ONCE(st->version) & 1));
	GUEST_ASSERT(READ_ONCE(st->flags) == 0);
	GUEST_ASSERT(READ_ONCE(st->preempted) == 0);
पूर्ण

अटल व्योम guest_code(पूर्णांक cpu)
अणु
	काष्ठा kvm_steal_समय *st = st_gva[cpu];
	uपूर्णांक32_t version;

	GUEST_ASSERT(rdmsr(MSR_KVM_STEAL_TIME) == ((uपूर्णांक64_t)st_gva[cpu] | KVM_MSR_ENABLED));

	स_रखो(st, 0, माप(*st));
	GUEST_SYNC(0);

	check_status(st);
	WRITE_ONCE(guest_stolen_समय[cpu], st->steal);
	version = READ_ONCE(st->version);
	check_status(st);
	GUEST_SYNC(1);

	check_status(st);
	GUEST_ASSERT(version < READ_ONCE(st->version));
	WRITE_ONCE(guest_stolen_समय[cpu], st->steal);
	check_status(st);
	GUEST_DONE();
पूर्ण

अटल व्योम steal_समय_init(काष्ठा kvm_vm *vm)
अणु
	पूर्णांक i;

	अगर (!(kvm_get_supported_cpuid_entry(KVM_CPUID_FEATURES)->eax &
	      KVM_FEATURE_STEAL_TIME)) अणु
		prपूर्णांक_skip("steal-time not supported");
		निकास(KSFT_SKIP);
	पूर्ण

	क्रम (i = 0; i < NR_VCPUS; ++i) अणु
		पूर्णांक ret;

		vcpu_set_cpuid(vm, i, kvm_get_supported_cpuid());

		/* ST_GPA_BASE is identity mapped */
		st_gva[i] = (व्योम *)(ST_GPA_BASE + i * STEAL_TIME_SIZE);
		sync_global_to_guest(vm, st_gva[i]);

		ret = _vcpu_set_msr(vm, i, MSR_KVM_STEAL_TIME, (uदीर्घ)st_gva[i] | KVM_STEAL_RESERVED_MASK);
		TEST_ASSERT(ret == 0, "Bad GPA didn't fail");

		vcpu_set_msr(vm, i, MSR_KVM_STEAL_TIME, (uदीर्घ)st_gva[i] | KVM_MSR_ENABLED);
	पूर्ण
पूर्ण

अटल व्योम steal_समय_dump(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा kvm_steal_समय *st = addr_gva2hva(vm, (uदीर्घ)st_gva[vcpuid]);
	पूर्णांक i;

	pr_info("VCPU%d:\n", vcpuid);
	pr_info("    steal:     %lld\n", st->steal);
	pr_info("    version:   %d\n", st->version);
	pr_info("    flags:     %d\n", st->flags);
	pr_info("    preempted: %d\n", st->preempted);
	pr_info("    u8_pad:    ");
	क्रम (i = 0; i < 3; ++i)
		pr_info("%d", st->u8_pad[i]);
	pr_info("\n    pad:       ");
	क्रम (i = 0; i < 11; ++i)
		pr_info("%d", st->pad[i]);
	pr_info("\n");
पूर्ण

#या_अगर defined(__aarch64__)

/* PV_TIME_ST must have 64-byte alignment */
#घोषणा STEAL_TIME_SIZE		((माप(काष्ठा st_समय) + 63) & ~63)

#घोषणा SMCCC_ARCH_FEATURES	0x80000001
#घोषणा PV_TIME_FEATURES	0xc5000020
#घोषणा PV_TIME_ST		0xc5000021

काष्ठा st_समय अणु
	uपूर्णांक32_t rev;
	uपूर्णांक32_t attr;
	uपूर्णांक64_t st_समय;
पूर्ण;

अटल पूर्णांक64_t smccc(uपूर्णांक32_t func, uपूर्णांक32_t arg)
अणु
	अचिन्हित दीर्घ ret;

	यंत्र अस्थिर(
		"mov	x0, %1\n"
		"mov	x1, %2\n"
		"hvc	#0\n"
		"mov	%0, x0\n"
	: "=r" (ret) : "r" (func), "r" (arg) :
	  "x0", "x1", "x2", "x3");

	वापस ret;
पूर्ण

अटल व्योम check_status(काष्ठा st_समय *st)
अणु
	GUEST_ASSERT(READ_ONCE(st->rev) == 0);
	GUEST_ASSERT(READ_ONCE(st->attr) == 0);
पूर्ण

अटल व्योम guest_code(पूर्णांक cpu)
अणु
	काष्ठा st_समय *st;
	पूर्णांक64_t status;

	status = smccc(SMCCC_ARCH_FEATURES, PV_TIME_FEATURES);
	GUEST_ASSERT(status == 0);
	status = smccc(PV_TIME_FEATURES, PV_TIME_FEATURES);
	GUEST_ASSERT(status == 0);
	status = smccc(PV_TIME_FEATURES, PV_TIME_ST);
	GUEST_ASSERT(status == 0);

	status = smccc(PV_TIME_ST, 0);
	GUEST_ASSERT(status != -1);
	GUEST_ASSERT(status == (uदीर्घ)st_gva[cpu]);

	st = (काष्ठा st_समय *)status;
	GUEST_SYNC(0);

	check_status(st);
	WRITE_ONCE(guest_stolen_समय[cpu], st->st_समय);
	GUEST_SYNC(1);

	check_status(st);
	WRITE_ONCE(guest_stolen_समय[cpu], st->st_समय);
	GUEST_DONE();
पूर्ण

अटल व्योम steal_समय_init(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_device_attr dev = अणु
		.group = KVM_ARM_VCPU_PVTIME_CTRL,
		.attr = KVM_ARM_VCPU_PVTIME_IPA,
	पूर्ण;
	पूर्णांक i, ret;

	ret = _vcpu_ioctl(vm, 0, KVM_HAS_DEVICE_ATTR, &dev);
	अगर (ret != 0 && त्रुटि_सं == ENXIO) अणु
		prपूर्णांक_skip("steal-time not supported");
		निकास(KSFT_SKIP);
	पूर्ण

	क्रम (i = 0; i < NR_VCPUS; ++i) अणु
		uपूर्णांक64_t st_ipa;

		vcpu_ioctl(vm, i, KVM_HAS_DEVICE_ATTR, &dev);

		dev.addr = (uपूर्णांक64_t)&st_ipa;

		/* ST_GPA_BASE is identity mapped */
		st_gva[i] = (व्योम *)(ST_GPA_BASE + i * STEAL_TIME_SIZE);
		sync_global_to_guest(vm, st_gva[i]);

		st_ipa = (uदीर्घ)st_gva[i] | 1;
		ret = _vcpu_ioctl(vm, i, KVM_SET_DEVICE_ATTR, &dev);
		TEST_ASSERT(ret == -1 && त्रुटि_सं == EINVAL, "Bad IPA didn't report EINVAL");

		st_ipa = (uदीर्घ)st_gva[i];
		vcpu_ioctl(vm, i, KVM_SET_DEVICE_ATTR, &dev);

		ret = _vcpu_ioctl(vm, i, KVM_SET_DEVICE_ATTR, &dev);
		TEST_ASSERT(ret == -1 && त्रुटि_सं == EEXIST, "Set IPA twice without EEXIST");

	पूर्ण
पूर्ण

अटल व्योम steal_समय_dump(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा st_समय *st = addr_gva2hva(vm, (uदीर्घ)st_gva[vcpuid]);

	pr_info("VCPU%d:\n", vcpuid);
	pr_info("    rev:     %d\n", st->rev);
	pr_info("    attr:    %d\n", st->attr);
	pr_info("    st_time: %ld\n", st->st_समय);
पूर्ण

#पूर्ण_अगर

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

अटल व्योम *करो_steal_समय(व्योम *arg)
अणु
	काष्ठा बारpec ts, stop;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
	stop = बारpec_add_ns(ts, MIN_RUN_DELAY_NS);

	जबतक (1) अणु
		घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
		अगर (बारpec_to_ns(बारpec_sub(ts, stop)) >= 0)
			अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम run_vcpu(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा ucall uc;

	vcpu_args_set(vm, vcpuid, 1, vcpuid);

	vcpu_ioctl(vm, vcpuid, KVM_RUN, शून्य);

	चयन (get_ucall(vm, vcpuid, &uc)) अणु
	हाल UCALL_SYNC:
	हाल UCALL_DONE:
		अवरोध;
	हाल UCALL_ABORT:
		TEST_ASSERT(false, "%s at %s:%ld", (स्थिर अक्षर *)uc.args[0],
			    __खाता__, uc.args[1]);
	शेष:
		TEST_ASSERT(false, "Unexpected exit: %s",
			    निकास_reason_str(vcpu_state(vm, vcpuid)->निकास_reason));
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **av)
अणु
	काष्ठा kvm_vm *vm;
	pthपढ़ो_attr_t attr;
	pthपढ़ो_t thपढ़ो;
	cpu_set_t cpuset;
	अचिन्हित पूर्णांक gpages;
	दीर्घ stolen_समय;
	दीर्घ run_delay;
	bool verbose;
	पूर्णांक i;

	verbose = ac > 1 && (!म_भेदन(av[1], "-v", 3) || !म_भेदन(av[1], "--verbose", 10));

	/* Set CPU affinity so we can क्रमce preemption of the VCPU */
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	pthपढ़ो_attr_init(&attr);
	pthपढ़ो_attr_setaffinity_np(&attr, माप(cpu_set_t), &cpuset);
	pthपढ़ो_setaffinity_np(pthपढ़ो_self(), माप(cpu_set_t), &cpuset);

	/* Create a one VCPU guest and an identity mapped memslot क्रम the steal समय काष्ठाure */
	vm = vm_create_शेष(0, 0, guest_code);
	gpages = vm_calc_num_guest_pages(VM_MODE_DEFAULT, STEAL_TIME_SIZE * NR_VCPUS);
	vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS, ST_GPA_BASE, 1, gpages, 0);
	virt_map(vm, ST_GPA_BASE, ST_GPA_BASE, gpages, 0);
	ucall_init(vm, शून्य);

	/* Add the rest of the VCPUs */
	क्रम (i = 1; i < NR_VCPUS; ++i)
		vm_vcpu_add_शेष(vm, i, guest_code);

	steal_समय_init(vm);

	/* Run test on each VCPU */
	क्रम (i = 0; i < NR_VCPUS; ++i) अणु
		/* First VCPU run initializes steal-समय */
		run_vcpu(vm, i);

		/* Second VCPU run, expect guest stolen समय to be <= run_delay */
		run_vcpu(vm, i);
		sync_global_from_guest(vm, guest_stolen_समय[i]);
		stolen_समय = guest_stolen_समय[i];
		run_delay = get_run_delay();
		TEST_ASSERT(stolen_समय <= run_delay,
			    "Expected stolen time <= %ld, got %ld",
			    run_delay, stolen_समय);

		/* Steal समय from the VCPU. The steal समय thपढ़ो has the same CPU affinity as the VCPUs. */
		run_delay = get_run_delay();
		pthपढ़ो_create(&thपढ़ो, &attr, करो_steal_समय, शून्य);
		करो
			pthपढ़ो_yield();
		जबतक (get_run_delay() - run_delay < MIN_RUN_DELAY_NS);
		pthपढ़ो_join(thपढ़ो, शून्य);
		run_delay = get_run_delay() - run_delay;
		TEST_ASSERT(run_delay >= MIN_RUN_DELAY_NS,
			    "Expected run_delay >= %ld, got %ld",
			    MIN_RUN_DELAY_NS, run_delay);

		/* Run VCPU again to confirm stolen समय is consistent with run_delay */
		run_vcpu(vm, i);
		sync_global_from_guest(vm, guest_stolen_समय[i]);
		stolen_समय = guest_stolen_समय[i] - stolen_समय;
		TEST_ASSERT(stolen_समय >= run_delay,
			    "Expected stolen time >= %ld, got %ld",
			    run_delay, stolen_समय);

		अगर (verbose) अणु
			pr_info("VCPU%d: total-stolen-time=%ld test-stolen-time=%ld", i,
				guest_stolen_समय[i], stolen_समय);
			अगर (stolen_समय == run_delay)
				pr_info(" (BONUS: guest test-stolen-time even exactly matches test-run_delay)");
			pr_info("\n");
			steal_समय_dump(vm, i);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
