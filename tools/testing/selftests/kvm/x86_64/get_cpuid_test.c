<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2021, Red Hat Inc.
 *
 * Generic tests क्रम KVM CPUID set/get ioctls
 */
#समावेश <यंत्र/kvm_para.h>
#समावेश <linux/kvm_para.h>
#समावेश <मानक_निवेशt.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"

#घोषणा VCPU_ID 0

/* CPUIDs known to dअगरfer */
काष्ठा अणु
	u32 function;
	u32 index;
पूर्ण mangled_cpuids[] = अणु
	/*
	 * These entries depend on the vCPU's XCR0 रेजिस्टर and IA32_XSS MSR,
	 * which are not controlled क्रम by this test.
	 */
	अणु.function = 0xd, .index = 0पूर्ण,
	अणु.function = 0xd, .index = 1पूर्ण,
पूर्ण;

अटल व्योम test_guest_cpuids(काष्ठा kvm_cpuid2 *guest_cpuid)
अणु
	पूर्णांक i;
	u32 eax, ebx, ecx, edx;

	क्रम (i = 0; i < guest_cpuid->nent; i++) अणु
		eax = guest_cpuid->entries[i].function;
		ecx = guest_cpuid->entries[i].index;

		cpuid(&eax, &ebx, &ecx, &edx);

		GUEST_ASSERT(eax == guest_cpuid->entries[i].eax &&
			     ebx == guest_cpuid->entries[i].ebx &&
			     ecx == guest_cpuid->entries[i].ecx &&
			     edx == guest_cpuid->entries[i].edx);
	पूर्ण

पूर्ण

अटल व्योम test_cpuid_40000000(काष्ठा kvm_cpuid2 *guest_cpuid)
अणु
	u32 eax = 0x40000000, ebx, ecx = 0, edx;

	cpuid(&eax, &ebx, &ecx, &edx);

	GUEST_ASSERT(eax == 0x40000001);
पूर्ण

अटल व्योम guest_मुख्य(काष्ठा kvm_cpuid2 *guest_cpuid)
अणु
	GUEST_SYNC(1);

	test_guest_cpuids(guest_cpuid);

	GUEST_SYNC(2);

	test_cpuid_40000000(guest_cpuid);

	GUEST_DONE();
पूर्ण

अटल bool is_cpuid_mangled(काष्ठा kvm_cpuid_entry2 *entrie)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < माप(mangled_cpuids); i++) अणु
		अगर (mangled_cpuids[i].function == entrie->function &&
		    mangled_cpuids[i].index == entrie->index)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम check_cpuid(काष्ठा kvm_cpuid2 *cpuid, काष्ठा kvm_cpuid_entry2 *entrie)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cpuid->nent; i++) अणु
		अगर (cpuid->entries[i].function == entrie->function &&
		    cpuid->entries[i].index == entrie->index) अणु
			अगर (is_cpuid_mangled(entrie))
				वापस;

			TEST_ASSERT(cpuid->entries[i].eax == entrie->eax &&
				    cpuid->entries[i].ebx == entrie->ebx &&
				    cpuid->entries[i].ecx == entrie->ecx &&
				    cpuid->entries[i].edx == entrie->edx,
				    "CPUID 0x%x.%x differ: 0x%x:0x%x:0x%x:0x%x vs 0x%x:0x%x:0x%x:0x%x",
				    entrie->function, entrie->index,
				    cpuid->entries[i].eax, cpuid->entries[i].ebx,
				    cpuid->entries[i].ecx, cpuid->entries[i].edx,
				    entrie->eax, entrie->ebx, entrie->ecx, entrie->edx);
			वापस;
		पूर्ण
	पूर्ण

	TEST_ASSERT(false, "CPUID 0x%x.%x not found", entrie->function, entrie->index);
पूर्ण

अटल व्योम compare_cpuids(काष्ठा kvm_cpuid2 *cpuid1, काष्ठा kvm_cpuid2 *cpuid2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cpuid1->nent; i++)
		check_cpuid(cpuid2, &cpuid1->entries[i]);

	क्रम (i = 0; i < cpuid2->nent; i++)
		check_cpuid(cpuid1, &cpuid2->entries[i]);
पूर्ण

अटल व्योम run_vcpu(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, पूर्णांक stage)
अणु
	काष्ठा ucall uc;

	_vcpu_run(vm, vcpuid);

	चयन (get_ucall(vm, vcpuid, &uc)) अणु
	हाल UCALL_SYNC:
		TEST_ASSERT(!म_भेद((स्थिर अक्षर *)uc.args[0], "hello") &&
			    uc.args[1] == stage + 1,
			    "Stage %d: Unexpected register values vmexit, got %lx",
			    stage + 1, (uदीर्घ)uc.args[1]);
		वापस;
	हाल UCALL_DONE:
		वापस;
	हाल UCALL_ABORT:
		TEST_ASSERT(false, "%s at %s:%ld\n\tvalues: %#lx, %#lx", (स्थिर अक्षर *)uc.args[0],
			    __खाता__, uc.args[1], uc.args[2], uc.args[3]);
	शेष:
		TEST_ASSERT(false, "Unexpected exit: %s",
			    निकास_reason_str(vcpu_state(vm, vcpuid)->निकास_reason));
	पूर्ण
पूर्ण

काष्ठा kvm_cpuid2 *vcpu_alloc_cpuid(काष्ठा kvm_vm *vm, vm_vaddr_t *p_gva, काष्ठा kvm_cpuid2 *cpuid)
अणु
	पूर्णांक size = माप(*cpuid) + cpuid->nent * माप(cpuid->entries[0]);
	vm_vaddr_t gva = vm_vaddr_alloc(vm, size,
					getpagesize(), 0, 0);
	काष्ठा kvm_cpuid2 *guest_cpuids = addr_gva2hva(vm, gva);

	स_नकल(guest_cpuids, cpuid, size);

	*p_gva = gva;
	वापस guest_cpuids;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा kvm_cpuid2 *supp_cpuid, *cpuid2;
	vm_vaddr_t cpuid_gva;
	काष्ठा kvm_vm *vm;
	पूर्णांक stage;

	vm = vm_create_शेष(VCPU_ID, 0, guest_मुख्य);

	supp_cpuid = kvm_get_supported_cpuid();
	cpuid2 = vcpu_get_cpuid(vm, VCPU_ID);

	compare_cpuids(supp_cpuid, cpuid2);

	vcpu_alloc_cpuid(vm, &cpuid_gva, cpuid2);

	vcpu_args_set(vm, VCPU_ID, 1, cpuid_gva);

	क्रम (stage = 0; stage < 3; stage++)
		run_vcpu(vm, VCPU_ID, stage);

	kvm_vm_मुक्त(vm);
पूर्ण
