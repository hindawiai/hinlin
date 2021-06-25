<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019, Google LLC.
 *
 * Tests क्रम the IA32_XSS MSR.
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "vmx.h"

#घोषणा VCPU_ID	      1
#घोषणा MSR_BITS      64

#घोषणा X86_FEATURE_XSAVES	(1<<3)

bool is_supported_msr(u32 msr_index)
अणु
	काष्ठा kvm_msr_list *list;
	bool found = false;
	पूर्णांक i;

	list = kvm_get_msr_index_list();
	क्रम (i = 0; i < list->nmsrs; ++i) अणु
		अगर (list->indices[i] == msr_index) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	मुक्त(list);
	वापस found;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा kvm_cpuid_entry2 *entry;
	bool xss_supported = false;
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t xss_val;
	पूर्णांक i, r;

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, 0);

	अगर (kvm_get_cpuid_max_basic() >= 0xd) अणु
		entry = kvm_get_supported_cpuid_index(0xd, 1);
		xss_supported = entry && !!(entry->eax & X86_FEATURE_XSAVES);
	पूर्ण
	अगर (!xss_supported) अणु
		prपूर्णांक_skip("IA32_XSS is not supported by the vCPU");
		निकास(KSFT_SKIP);
	पूर्ण

	xss_val = vcpu_get_msr(vm, VCPU_ID, MSR_IA32_XSS);
	TEST_ASSERT(xss_val == 0,
		    "MSR_IA32_XSS should be initialized to zero\n");

	vcpu_set_msr(vm, VCPU_ID, MSR_IA32_XSS, xss_val);
	/*
	 * At present, KVM only supports a guest IA32_XSS value of 0. Verअगरy
	 * that trying to set the guest IA32_XSS to an unsupported value fails.
	 * Also, in the future when a non-zero value succeeds check that
	 * IA32_XSS is in the KVM_GET_MSR_INDEX_LIST.
	 */
	क्रम (i = 0; i < MSR_BITS; ++i) अणु
		r = _vcpu_set_msr(vm, VCPU_ID, MSR_IA32_XSS, 1ull << i);
		TEST_ASSERT(r == 0 || is_supported_msr(MSR_IA32_XSS),
			    "IA32_XSS was able to be set, but was not found in KVM_GET_MSR_INDEX_LIST.\n");
	पूर्ण

	kvm_vm_मुक्त(vm);
पूर्ण
