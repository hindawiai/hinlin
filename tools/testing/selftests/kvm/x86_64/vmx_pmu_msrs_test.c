<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * VMX-pmu related msrs test
 *
 * Copyright (C) 2021 Intel Corporation
 *
 * Test to check the effect of various CPUID settings
 * on the MSR_IA32_PERF_CAPABILITIES MSR, and check that
 * whatever we ग_लिखो with KVM_SET_MSR is _not_ modअगरied
 * in the guest and test it can be retrieved with KVM_GET_MSR.
 *
 * Test to check that invalid LBR क्रमmats are rejected.
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <sys/ioctl.h>

#समावेश "kvm_util.h"
#समावेश "vmx.h"

#घोषणा VCPU_ID	      0

#घोषणा X86_FEATURE_PDCM	(1<<15)
#घोषणा PMU_CAP_FW_WRITES	(1ULL << 13)
#घोषणा PMU_CAP_LBR_FMT		0x3f

जोड़ cpuid10_eax अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक version_id:8;
		अचिन्हित पूर्णांक num_counters:8;
		अचिन्हित पूर्णांक bit_width:8;
		अचिन्हित पूर्णांक mask_length:8;
	पूर्ण split;
	अचिन्हित पूर्णांक full;
पूर्ण;

जोड़ perf_capabilities अणु
	काष्ठा अणु
		u64	lbr_क्रमmat:6;
		u64	pebs_trap:1;
		u64	pebs_arch_reg:1;
		u64	pebs_क्रमmat:4;
		u64	smm_मुक्तze:1;
		u64	full_width_ग_लिखो:1;
		u64 pebs_baseline:1;
		u64	perf_metrics:1;
		u64	pebs_output_pt_available:1;
		u64	anythपढ़ो_deprecated:1;
	पूर्ण;
	u64	capabilities;
पूर्ण;

अटल व्योम guest_code(व्योम)
अणु
	wrmsr(MSR_IA32_PERF_CAPABILITIES, PMU_CAP_LBR_FMT);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा kvm_cpuid2 *cpuid;
	काष्ठा kvm_cpuid_entry2 *entry_1_0;
	काष्ठा kvm_cpuid_entry2 *entry_a_0;
	bool pdcm_supported = false;
	काष्ठा kvm_vm *vm;
	पूर्णांक ret;
	जोड़ cpuid10_eax eax;
	जोड़ perf_capabilities host_cap;

	host_cap.capabilities = kvm_get_feature_msr(MSR_IA32_PERF_CAPABILITIES);
	host_cap.capabilities &= (PMU_CAP_FW_WRITES | PMU_CAP_LBR_FMT);

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code);
	cpuid = kvm_get_supported_cpuid();

	अगर (kvm_get_cpuid_max_basic() >= 0xa) अणु
		entry_1_0 = kvm_get_supported_cpuid_index(1, 0);
		entry_a_0 = kvm_get_supported_cpuid_index(0xa, 0);
		pdcm_supported = entry_1_0 && !!(entry_1_0->ecx & X86_FEATURE_PDCM);
		eax.full = entry_a_0->eax;
	पूर्ण
	अगर (!pdcm_supported) अणु
		prपूर्णांक_skip("MSR_IA32_PERF_CAPABILITIES is not supported by the vCPU");
		निकास(KSFT_SKIP);
	पूर्ण
	अगर (!eax.split.version_id) अणु
		prपूर्णांक_skip("PMU is not supported by the vCPU");
		निकास(KSFT_SKIP);
	पूर्ण

	/* testहाल 1, set capabilities when we have PDCM bit */
	vcpu_set_cpuid(vm, VCPU_ID, cpuid);
	vcpu_set_msr(vm, 0, MSR_IA32_PERF_CAPABILITIES, PMU_CAP_FW_WRITES);

	/* check capabilities can be retrieved with KVM_GET_MSR */
	ASSERT_EQ(vcpu_get_msr(vm, VCPU_ID, MSR_IA32_PERF_CAPABILITIES), PMU_CAP_FW_WRITES);

	/* check whatever we ग_लिखो with KVM_SET_MSR is _not_ modअगरied */
	vcpu_run(vm, VCPU_ID);
	ASSERT_EQ(vcpu_get_msr(vm, VCPU_ID, MSR_IA32_PERF_CAPABILITIES), PMU_CAP_FW_WRITES);

	/* testहाल 2, check valid LBR क्रमmats are accepted */
	vcpu_set_msr(vm, 0, MSR_IA32_PERF_CAPABILITIES, 0);
	ASSERT_EQ(vcpu_get_msr(vm, VCPU_ID, MSR_IA32_PERF_CAPABILITIES), 0);

	vcpu_set_msr(vm, 0, MSR_IA32_PERF_CAPABILITIES, host_cap.lbr_क्रमmat);
	ASSERT_EQ(vcpu_get_msr(vm, VCPU_ID, MSR_IA32_PERF_CAPABILITIES), (u64)host_cap.lbr_क्रमmat);

	/* testहाल 3, check invalid LBR क्रमmat is rejected */
	ret = _vcpu_set_msr(vm, 0, MSR_IA32_PERF_CAPABILITIES, PMU_CAP_LBR_FMT);
	TEST_ASSERT(ret == 0, "Bad PERF_CAPABILITIES didn't fail.");

	/* testहाल 4, set capabilities when we करोn't have PDCM bit */
	entry_1_0->ecx &= ~X86_FEATURE_PDCM;
	vcpu_set_cpuid(vm, VCPU_ID, cpuid);
	ret = _vcpu_set_msr(vm, 0, MSR_IA32_PERF_CAPABILITIES, host_cap.capabilities);
	TEST_ASSERT(ret == 0, "Bad PERF_CAPABILITIES didn't fail.");

	/* testहाल 5, set capabilities when we करोn't have PMU version bits */
	entry_1_0->ecx |= X86_FEATURE_PDCM;
	eax.split.version_id = 0;
	entry_1_0->ecx = eax.full;
	vcpu_set_cpuid(vm, VCPU_ID, cpuid);
	ret = _vcpu_set_msr(vm, 0, MSR_IA32_PERF_CAPABILITIES, PMU_CAP_FW_WRITES);
	TEST_ASSERT(ret == 0, "Bad PERF_CAPABILITIES didn't fail.");

	vcpu_set_msr(vm, 0, MSR_IA32_PERF_CAPABILITIES, 0);
	ASSERT_EQ(vcpu_get_msr(vm, VCPU_ID, MSR_IA32_PERF_CAPABILITIES), 0);

	kvm_vm_मुक्त(vm);
पूर्ण
