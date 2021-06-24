<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vmx_set_nested_state_test
 *
 * Copyright (C) 2019, Google LLC.
 *
 * This test verअगरies the पूर्णांकegrity of calling the ioctl KVM_SET_NESTED_STATE.
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"
#समावेश "vmx.h"

#समावेश <त्रुटिसं.स>
#समावेश <linux/kvm.h>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <unistd.h>

/*
 * Mirror of VMCS12_REVISION in arch/x86/kvm/vmx/vmcs12.h. If that value
 * changes this should be updated.
 */
#घोषणा VMCS12_REVISION 0x11e57ed0
#घोषणा VCPU_ID 5

bool have_evmcs;

व्योम test_nested_state(काष्ठा kvm_vm *vm, काष्ठा kvm_nested_state *state)
अणु
	vcpu_nested_state_set(vm, VCPU_ID, state, false);
पूर्ण

व्योम test_nested_state_expect_त्रुटि_सं(काष्ठा kvm_vm *vm,
				    काष्ठा kvm_nested_state *state,
				    पूर्णांक expected_त्रुटि_सं)
अणु
	पूर्णांक rv;

	rv = vcpu_nested_state_set(vm, VCPU_ID, state, true);
	TEST_ASSERT(rv == -1 && त्रुटि_सं == expected_त्रुटि_सं,
		"Expected %s (%d) from vcpu_nested_state_set but got rv: %i errno: %s (%d)",
		म_त्रुटि(expected_त्रुटि_सं), expected_त्रुटि_सं, rv, म_त्रुटि(त्रुटि_सं),
		त्रुटि_सं);
पूर्ण

व्योम test_nested_state_expect_einval(काष्ठा kvm_vm *vm,
				     काष्ठा kvm_nested_state *state)
अणु
	test_nested_state_expect_त्रुटि_सं(vm, state, EINVAL);
पूर्ण

व्योम test_nested_state_expect_efault(काष्ठा kvm_vm *vm,
				     काष्ठा kvm_nested_state *state)
अणु
	test_nested_state_expect_त्रुटि_सं(vm, state, EFAULT);
पूर्ण

व्योम set_revision_id_क्रम_vmcs12(काष्ठा kvm_nested_state *state,
				u32 vmcs12_revision)
अणु
	/* Set revision_id in vmcs12 to vmcs12_revision. */
	स_नकल(&state->data, &vmcs12_revision, माप(u32));
पूर्ण

व्योम set_शेष_state(काष्ठा kvm_nested_state *state)
अणु
	स_रखो(state, 0, माप(*state));
	state->flags = KVM_STATE_NESTED_RUN_PENDING |
		       KVM_STATE_NESTED_GUEST_MODE;
	state->क्रमmat = 0;
	state->size = माप(*state);
पूर्ण

व्योम set_शेष_vmx_state(काष्ठा kvm_nested_state *state, पूर्णांक size)
अणु
	स_रखो(state, 0, size);
	अगर (have_evmcs)
		state->flags = KVM_STATE_NESTED_EVMCS;
	state->क्रमmat = 0;
	state->size = size;
	state->hdr.vmx.vmxon_pa = 0x1000;
	state->hdr.vmx.vmcs12_pa = 0x2000;
	state->hdr.vmx.smm.flags = 0;
	set_revision_id_क्रम_vmcs12(state, VMCS12_REVISION);
पूर्ण

व्योम test_vmx_nested_state(काष्ठा kvm_vm *vm)
अणु
	/* Add a page क्रम VMCS12. */
	स्थिर पूर्णांक state_sz = माप(काष्ठा kvm_nested_state) + getpagesize();
	काष्ठा kvm_nested_state *state =
		(काष्ठा kvm_nested_state *)दो_स्मृति(state_sz);

	/* The क्रमmat must be set to 0. 0 क्रम VMX, 1 क्रम SVM. */
	set_शेष_vmx_state(state, state_sz);
	state->क्रमmat = 1;
	test_nested_state_expect_einval(vm, state);

	/*
	 * We cannot भवize anything अगर the guest करोes not have VMX
	 * enabled.
	 */
	set_शेष_vmx_state(state, state_sz);
	test_nested_state_expect_einval(vm, state);

	/*
	 * We cannot भवize anything अगर the guest करोes not have VMX
	 * enabled.  We expect KVM_SET_NESTED_STATE to वापस 0 अगर vmxon_pa
	 * is set to -1ull, but the flags must be zero.
	 */
	set_शेष_vmx_state(state, state_sz);
	state->hdr.vmx.vmxon_pa = -1ull;
	test_nested_state_expect_einval(vm, state);

	state->hdr.vmx.vmcs12_pa = -1ull;
	state->flags = KVM_STATE_NESTED_EVMCS;
	test_nested_state_expect_einval(vm, state);

	state->flags = 0;
	test_nested_state(vm, state);

	/* Enable VMX in the guest CPUID. */
	vcpu_set_cpuid(vm, VCPU_ID, kvm_get_supported_cpuid());

	/*
	 * Setting vmxon_pa == -1ull and vmcs_pa == -1ull निकासs early without
	 * setting the nested state but flags other than eVMCS must be clear.
	 * The eVMCS flag can be set अगर the enlightened VMCS capability has
	 * been enabled.
	 */
	set_शेष_vmx_state(state, state_sz);
	state->hdr.vmx.vmxon_pa = -1ull;
	state->hdr.vmx.vmcs12_pa = -1ull;
	test_nested_state_expect_einval(vm, state);

	state->flags &= KVM_STATE_NESTED_EVMCS;
	अगर (have_evmcs) अणु
		test_nested_state_expect_einval(vm, state);
		vcpu_enable_evmcs(vm, VCPU_ID);
	पूर्ण
	test_nested_state(vm, state);

	/* It is invalid to have vmxon_pa == -1ull and SMM flags non-zero. */
	state->hdr.vmx.smm.flags = 1;
	test_nested_state_expect_einval(vm, state);

	/* Invalid flags are rejected. */
	set_शेष_vmx_state(state, state_sz);
	state->hdr.vmx.flags = ~0;
	test_nested_state_expect_einval(vm, state);

	/* It is invalid to have vmxon_pa == -1ull and vmcs_pa != -1ull. */
	set_शेष_vmx_state(state, state_sz);
	state->hdr.vmx.vmxon_pa = -1ull;
	state->flags = 0;
	test_nested_state_expect_einval(vm, state);

	/* It is invalid to have vmxon_pa set to a non-page aligned address. */
	set_शेष_vmx_state(state, state_sz);
	state->hdr.vmx.vmxon_pa = 1;
	test_nested_state_expect_einval(vm, state);

	/*
	 * It is invalid to have KVM_STATE_NESTED_SMM_GUEST_MODE and
	 * KVM_STATE_NESTED_GUEST_MODE set together.
	 */
	set_शेष_vmx_state(state, state_sz);
	state->flags = KVM_STATE_NESTED_GUEST_MODE  |
		      KVM_STATE_NESTED_RUN_PENDING;
	state->hdr.vmx.smm.flags = KVM_STATE_NESTED_SMM_GUEST_MODE;
	test_nested_state_expect_einval(vm, state);

	/*
	 * It is invalid to have any of the SMM flags set besides:
	 *	KVM_STATE_NESTED_SMM_GUEST_MODE
	 *	KVM_STATE_NESTED_SMM_VMXON
	 */
	set_शेष_vmx_state(state, state_sz);
	state->hdr.vmx.smm.flags = ~(KVM_STATE_NESTED_SMM_GUEST_MODE |
				KVM_STATE_NESTED_SMM_VMXON);
	test_nested_state_expect_einval(vm, state);

	/* Outside SMM, SMM flags must be zero. */
	set_शेष_vmx_state(state, state_sz);
	state->flags = 0;
	state->hdr.vmx.smm.flags = KVM_STATE_NESTED_SMM_GUEST_MODE;
	test_nested_state_expect_einval(vm, state);

	/*
	 * Size must be large enough to fit kvm_nested_state and vmcs12
	 * अगर VMCS12 physical address is set
	 */
	set_शेष_vmx_state(state, state_sz);
	state->size = माप(*state);
	state->flags = 0;
	test_nested_state_expect_einval(vm, state);

	set_शेष_vmx_state(state, state_sz);
	state->size = माप(*state);
	state->flags = 0;
	state->hdr.vmx.vmcs12_pa = -1;
	test_nested_state(vm, state);

	/*
	 * KVM_SET_NESTED_STATE succeeds with invalid VMCS
	 * contents but L2 not running.
	 */
	set_शेष_vmx_state(state, state_sz);
	state->flags = 0;
	test_nested_state(vm, state);

	/* Invalid flags are rejected, even अगर no VMCS loaded. */
	set_शेष_vmx_state(state, state_sz);
	state->size = माप(*state);
	state->flags = 0;
	state->hdr.vmx.vmcs12_pa = -1;
	state->hdr.vmx.flags = ~0;
	test_nested_state_expect_einval(vm, state);

	/* vmxon_pa cannot be the same address as vmcs_pa. */
	set_शेष_vmx_state(state, state_sz);
	state->hdr.vmx.vmxon_pa = 0;
	state->hdr.vmx.vmcs12_pa = 0;
	test_nested_state_expect_einval(vm, state);

	/*
	 * Test that अगर we leave nesting the state reflects that when we get
	 * it again.
	 */
	set_शेष_vmx_state(state, state_sz);
	state->hdr.vmx.vmxon_pa = -1ull;
	state->hdr.vmx.vmcs12_pa = -1ull;
	state->flags = 0;
	test_nested_state(vm, state);
	vcpu_nested_state_get(vm, VCPU_ID, state);
	TEST_ASSERT(state->size >= माप(*state) && state->size <= state_sz,
		    "Size must be between %ld and %d.  The size returned was %d.",
		    माप(*state), state_sz, state->size);
	TEST_ASSERT(state->hdr.vmx.vmxon_pa == -1ull, "vmxon_pa must be -1ull.");
	TEST_ASSERT(state->hdr.vmx.vmcs12_pa == -1ull, "vmcs_pa must be -1ull.");

	मुक्त(state);
पूर्ण

व्योम disable_vmx(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_cpuid2 *cpuid = kvm_get_supported_cpuid();
	पूर्णांक i;

	क्रम (i = 0; i < cpuid->nent; ++i)
		अगर (cpuid->entries[i].function == 1 &&
		    cpuid->entries[i].index == 0)
			अवरोध;
	TEST_ASSERT(i != cpuid->nent, "CPUID function 1 not found");

	cpuid->entries[i].ecx &= ~CPUID_VMX;
	vcpu_set_cpuid(vm, VCPU_ID, cpuid);
	cpuid->entries[i].ecx |= CPUID_VMX;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_nested_state state;

	have_evmcs = kvm_check_cap(KVM_CAP_HYPERV_ENLIGHTENED_VMCS);

	अगर (!kvm_check_cap(KVM_CAP_NESTED_STATE)) अणु
		prपूर्णांक_skip("KVM_CAP_NESTED_STATE not available");
		निकास(KSFT_SKIP);
	पूर्ण

	/*
	 * AMD currently करोes not implement set_nested_state, so क्रम now we
	 * just early out.
	 */
	nested_vmx_check_supported();

	vm = vm_create_शेष(VCPU_ID, 0, 0);

	/*
	 * First run tests with VMX disabled to check error handling.
	 */
	disable_vmx(vm);

	/* Passing a शून्य kvm_nested_state causes a EFAULT. */
	test_nested_state_expect_efault(vm, शून्य);

	/* 'size' cannot be smaller than माप(kvm_nested_state). */
	set_शेष_state(&state);
	state.size = 0;
	test_nested_state_expect_einval(vm, &state);

	/*
	 * Setting the flags 0xf fails the flags check.  The only flags that
	 * can be used are:
	 *     KVM_STATE_NESTED_GUEST_MODE
	 *     KVM_STATE_NESTED_RUN_PENDING
	 *     KVM_STATE_NESTED_EVMCS
	 */
	set_शेष_state(&state);
	state.flags = 0xf;
	test_nested_state_expect_einval(vm, &state);

	/*
	 * If KVM_STATE_NESTED_RUN_PENDING is set then
	 * KVM_STATE_NESTED_GUEST_MODE has to be set as well.
	 */
	set_शेष_state(&state);
	state.flags = KVM_STATE_NESTED_RUN_PENDING;
	test_nested_state_expect_einval(vm, &state);

	test_vmx_nested_state(vm);

	kvm_vm_मुक्त(vm);
	वापस 0;
पूर्ण
