<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tests क्रम MSR_IA32_TSC and MSR_IA32_TSC_ADJUST.
 *
 * Copyright (C) 2020, Red Hat, Inc.
 */
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश "kvm_util.h"
#समावेश "processor.h"

#घोषणा VCPU_ID 0

#घोषणा UNITY                  (1ull << 30)
#घोषणा HOST_ADJUST            (UNITY * 64)
#घोषणा GUEST_STEP             (UNITY * 4)
#घोषणा ROUND(x)               ((x + UNITY / 2) & -UNITY)
#घोषणा rounded_rdmsr(x)       ROUND(rdmsr(x))
#घोषणा rounded_host_rdmsr(x)  ROUND(vcpu_get_msr(vm, 0, x))

#घोषणा GUEST_ASSERT_EQ(a, b) करो अणु				\
	__typeof(a) _a = (a);					\
	__typeof(b) _b = (b);					\
	अगर (_a != _b)						\
                ucall(UCALL_ABORT, 4,				\
                        "Failed guest assert: "			\
                        #a " == " #b, __LINE__, _a, _b);	\
  पूर्ण जबतक(0)

अटल व्योम guest_code(व्योम)
अणु
	u64 val = 0;

	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC), val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/* Guest: ग_लिखोs to MSR_IA32_TSC affect both MSRs.  */
	val = 1ull * GUEST_STEP;
	wrmsr(MSR_IA32_TSC, val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC), val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/* Guest: ग_लिखोs to MSR_IA32_TSC_ADJUST affect both MSRs.  */
	GUEST_SYNC(2);
	val = 2ull * GUEST_STEP;
	wrmsr(MSR_IA32_TSC_ADJUST, val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC), val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/* Host: setting the TSC offset.  */
	GUEST_SYNC(3);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC), HOST_ADJUST + val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/*
	 * Guest: ग_लिखोs to MSR_IA32_TSC_ADJUST करो not destroy the
	 * host-side offset and affect both MSRs.
	 */
	GUEST_SYNC(4);
	val = 3ull * GUEST_STEP;
	wrmsr(MSR_IA32_TSC_ADJUST, val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC), HOST_ADJUST + val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/*
	 * Guest: ग_लिखोs to MSR_IA32_TSC affect both MSRs, so the host-side
	 * offset is now visible in MSR_IA32_TSC_ADJUST.
	 */
	GUEST_SYNC(5);
	val = 4ull * GUEST_STEP;
	wrmsr(MSR_IA32_TSC, val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC), val);
	GUEST_ASSERT_EQ(rounded_rdmsr(MSR_IA32_TSC_ADJUST), val - HOST_ADJUST);

	GUEST_DONE();
पूर्ण

अटल व्योम run_vcpu(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, पूर्णांक stage)
अणु
	काष्ठा ucall uc;

	vcpu_args_set(vm, vcpuid, 1, vcpuid);

	vcpu_ioctl(vm, vcpuid, KVM_RUN, शून्य);

	चयन (get_ucall(vm, vcpuid, &uc)) अणु
	हाल UCALL_SYNC:
		TEST_ASSERT(!म_भेद((स्थिर अक्षर *)uc.args[0], "hello") &&
                            uc.args[1] == stage + 1, "Stage %d: Unexpected register values vmexit, got %lx",
                            stage + 1, (uदीर्घ)uc.args[1]);
		वापस;
	हाल UCALL_DONE:
		वापस;
	हाल UCALL_ABORT:
		TEST_ASSERT(false, "%s at %s:%ld\n" \
			    "\tvalues: %#lx, %#lx", (स्थिर अक्षर *)uc.args[0],
			    __खाता__, uc.args[1], uc.args[2], uc.args[3]);
	शेष:
		TEST_ASSERT(false, "Unexpected exit: %s",
			    निकास_reason_str(vcpu_state(vm, vcpuid)->निकास_reason));
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t val;

	vm = vm_create_शेष(VCPU_ID, 0, guest_code);

	val = 0;
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC), val);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/* Guest: ग_लिखोs to MSR_IA32_TSC affect both MSRs.  */
	run_vcpu(vm, VCPU_ID, 1);
	val = 1ull * GUEST_STEP;
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC), val);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/* Guest: ग_लिखोs to MSR_IA32_TSC_ADJUST affect both MSRs.  */
	run_vcpu(vm, VCPU_ID, 2);
	val = 2ull * GUEST_STEP;
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC), val);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/*
	 * Host: ग_लिखोs to MSR_IA32_TSC set the host-side offset
	 * and thereक्रमe करो not change MSR_IA32_TSC_ADJUST.
	 */
	vcpu_set_msr(vm, 0, MSR_IA32_TSC, HOST_ADJUST + val);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC), HOST_ADJUST + val);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC_ADJUST), val);
	run_vcpu(vm, VCPU_ID, 3);

	/* Host: ग_लिखोs to MSR_IA32_TSC_ADJUST करो not modअगरy the TSC.  */
	vcpu_set_msr(vm, 0, MSR_IA32_TSC_ADJUST, UNITY * 123456);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC), HOST_ADJUST + val);
	ASSERT_EQ(vcpu_get_msr(vm, 0, MSR_IA32_TSC_ADJUST), UNITY * 123456);

	/* Restore previous value.  */
	vcpu_set_msr(vm, 0, MSR_IA32_TSC_ADJUST, val);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC), HOST_ADJUST + val);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/*
	 * Guest: ग_लिखोs to MSR_IA32_TSC_ADJUST करो not destroy the
	 * host-side offset and affect both MSRs.
	 */
	run_vcpu(vm, VCPU_ID, 4);
	val = 3ull * GUEST_STEP;
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC), HOST_ADJUST + val);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC_ADJUST), val);

	/*
	 * Guest: ग_लिखोs to MSR_IA32_TSC affect both MSRs, so the host-side
	 * offset is now visible in MSR_IA32_TSC_ADJUST.
	 */
	run_vcpu(vm, VCPU_ID, 5);
	val = 4ull * GUEST_STEP;
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC), val);
	ASSERT_EQ(rounded_host_rdmsr(MSR_IA32_TSC_ADJUST), val - HOST_ADJUST);

	kvm_vm_मुक्त(vm);

	वापस 0;
पूर्ण
