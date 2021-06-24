<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test क्रम x86 KVM_CAP_HYPERV_CPUID
 *
 * Copyright (C) 2018, Red Hat, Inc.
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 *
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"
#समावेश "vmx.h"

#घोषणा VCPU_ID 0

अटल व्योम guest_code(व्योम)
अणु
पूर्ण

अटल bool smt_possible(व्योम)
अणु
	अक्षर buf[16];
	खाता *f;
	bool res = true;

	f = ख_खोलो("/sys/devices/system/cpu/smt/control", "r");
	अगर (f) अणु
		अगर (ख_पढ़ो(buf, माप(*buf), माप(buf), f) > 0) अणु
			अगर (!म_भेदन(buf, "forceoff", 8) ||
			    !म_भेदन(buf, "notsupported", 12))
				res = false;
		पूर्ण
		ख_बंद(f);
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम test_hv_cpuid(काष्ठा kvm_cpuid2 *hv_cpuid_entries,
			  bool evmcs_expected)
अणु
	पूर्णांक i;
	पूर्णांक nent = 9;
	u32 test_val;

	अगर (evmcs_expected)
		nent += 1; /* 0x4000000A */

	TEST_ASSERT(hv_cpuid_entries->nent == nent,
		    "KVM_GET_SUPPORTED_HV_CPUID should return %d entries"
		    " with evmcs=%d (returned %d)",
		    nent, evmcs_expected, hv_cpuid_entries->nent);

	क्रम (i = 0; i < hv_cpuid_entries->nent; i++) अणु
		काष्ठा kvm_cpuid_entry2 *entry = &hv_cpuid_entries->entries[i];

		TEST_ASSERT((entry->function >= 0x40000000) &&
			    (entry->function <= 0x40000082),
			    "function %x is our of supported range",
			    entry->function);

		TEST_ASSERT(evmcs_expected || (entry->function != 0x4000000A),
			    "0x4000000A leaf should not be reported");

		TEST_ASSERT(entry->index == 0,
			    ".index field should be zero");

		TEST_ASSERT(entry->flags == 0,
			    ".flags field should be zero");

		TEST_ASSERT(!entry->padding[0] && !entry->padding[1] &&
			    !entry->padding[2], "padding should be zero");

		चयन (entry->function) अणु
		हाल 0x40000000:
			test_val = 0x40000082;

			TEST_ASSERT(entry->eax == test_val,
				    "Wrong max leaf report in 0x40000000.EAX: %x"
				    " (evmcs=%d)",
				    entry->eax, evmcs_expected
				);
			अवरोध;
		हाल 0x40000004:
			test_val = entry->eax & (1UL << 18);

			TEST_ASSERT(!!test_val == !smt_possible(),
				    "NoNonArchitecturalCoreSharing bit"
				    " doesn't reflect SMT setting");
			अवरोध;
		पूर्ण

		/*
		 * If needed क्रम debug:
		 * ख_लिखो(मानक_निकास,
		 *	"CPUID%lx EAX=0x%lx EBX=0x%lx ECX=0x%lx EDX=0x%lx\n",
		 *	entry->function, entry->eax, entry->ebx, entry->ecx,
		 *	entry->edx);
		 */
	पूर्ण

पूर्ण

व्योम test_hv_cpuid_e2big(काष्ठा kvm_vm *vm, bool प्रणाली)
अणु
	अटल काष्ठा kvm_cpuid2 cpuid = अणु.nent = 0पूर्ण;
	पूर्णांक ret;

	अगर (!प्रणाली)
		ret = _vcpu_ioctl(vm, VCPU_ID, KVM_GET_SUPPORTED_HV_CPUID, &cpuid);
	अन्यथा
		ret = _kvm_ioctl(vm, KVM_GET_SUPPORTED_HV_CPUID, &cpuid);

	TEST_ASSERT(ret == -1 && त्रुटि_सं == E2BIG,
		    "%s KVM_GET_SUPPORTED_HV_CPUID didn't fail with -E2BIG when"
		    " it should have: %d %d", प्रणाली ? "KVM" : "vCPU", ret, त्रुटि_सं);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_cpuid2 *hv_cpuid_entries;

	/* Tell मानक_निकास not to buffer its content */
	रखो_बफ(मानक_निकास, शून्य);

	अगर (!kvm_check_cap(KVM_CAP_HYPERV_CPUID)) अणु
		prपूर्णांक_skip("KVM_CAP_HYPERV_CPUID not supported");
		निकास(KSFT_SKIP);
	पूर्ण

	vm = vm_create_शेष(VCPU_ID, 0, guest_code);

	/* Test vCPU ioctl version */
	test_hv_cpuid_e2big(vm, false);

	hv_cpuid_entries = vcpu_get_supported_hv_cpuid(vm, VCPU_ID);
	test_hv_cpuid(hv_cpuid_entries, false);
	मुक्त(hv_cpuid_entries);

	अगर (!nested_vmx_supported() ||
	    !kvm_check_cap(KVM_CAP_HYPERV_ENLIGHTENED_VMCS)) अणु
		prपूर्णांक_skip("Enlightened VMCS is unsupported");
		जाओ करो_sys;
	पूर्ण
	vcpu_enable_evmcs(vm, VCPU_ID);
	hv_cpuid_entries = vcpu_get_supported_hv_cpuid(vm, VCPU_ID);
	test_hv_cpuid(hv_cpuid_entries, true);
	मुक्त(hv_cpuid_entries);

करो_sys:
	/* Test प्रणाली ioctl version */
	अगर (!kvm_check_cap(KVM_CAP_SYS_HYPERV_CPUID)) अणु
		prपूर्णांक_skip("KVM_CAP_SYS_HYPERV_CPUID not supported");
		जाओ out;
	पूर्ण

	test_hv_cpuid_e2big(vm, true);

	hv_cpuid_entries = kvm_get_supported_hv_cpuid();
	test_hv_cpuid(hv_cpuid_entries, nested_vmx_supported());

out:
	kvm_vm_मुक्त(vm);

	वापस 0;
पूर्ण
