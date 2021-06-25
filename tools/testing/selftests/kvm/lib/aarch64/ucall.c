<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ucall support. A ucall is a "hypercall to userspace".
 *
 * Copyright (C) 2018, Red Hat, Inc.
 */
#समावेश "kvm_util.h"
#समावेश "../kvm_util_internal.h"

अटल vm_vaddr_t *ucall_निकास_mmio_addr;

अटल bool ucall_mmio_init(काष्ठा kvm_vm *vm, vm_paddr_t gpa)
अणु
	अगर (kvm_userspace_memory_region_find(vm, gpa, gpa + 1))
		वापस false;

	virt_pg_map(vm, gpa, gpa, 0);

	ucall_निकास_mmio_addr = (vm_vaddr_t *)gpa;
	sync_global_to_guest(vm, ucall_निकास_mmio_addr);

	वापस true;
पूर्ण

व्योम ucall_init(काष्ठा kvm_vm *vm, व्योम *arg)
अणु
	vm_paddr_t gpa, start, end, step, offset;
	अचिन्हित पूर्णांक bits;
	bool ret;

	अगर (arg) अणु
		gpa = (vm_paddr_t)arg;
		ret = ucall_mmio_init(vm, gpa);
		TEST_ASSERT(ret, "Can't set ucall mmio address to %lx", gpa);
		वापस;
	पूर्ण

	/*
	 * Find an address within the allowed physical and भव address
	 * spaces, that करोes _not_ have a KVM memory region associated with
	 * it. Identity mapping an address like this allows the guest to
	 * access it, but as KVM करोesn't know what to करो with it, it
	 * will assume it's something userspace handles and निकास with
	 * KVM_EXIT_MMIO. Well, at least that's how it works क्रम AArch64.
	 * Here we start with a guess that the addresses around 5/8th
	 * of the allowed space are unmapped and then work both करोwn and
	 * up from there in 1/16th allowed space sized steps.
	 *
	 * Note, we need to use VA-bits - 1 when calculating the allowed
	 * भव address space क्रम an identity mapping because the upper
	 * half of the भव address space is the two's complement of the
	 * lower and won't match physical addresses.
	 */
	bits = vm->va_bits - 1;
	bits = vm->pa_bits < bits ? vm->pa_bits : bits;
	end = 1ul << bits;
	start = end * 5 / 8;
	step = end / 16;
	क्रम (offset = 0; offset < end - start; offset += step) अणु
		अगर (ucall_mmio_init(vm, start - offset))
			वापस;
		अगर (ucall_mmio_init(vm, start + offset))
			वापस;
	पूर्ण
	TEST_FAIL("Can't find a ucall mmio address");
पूर्ण

व्योम ucall_uninit(काष्ठा kvm_vm *vm)
अणु
	ucall_निकास_mmio_addr = 0;
	sync_global_to_guest(vm, ucall_निकास_mmio_addr);
पूर्ण

व्योम ucall(uपूर्णांक64_t cmd, पूर्णांक nargs, ...)
अणु
	काष्ठा ucall uc = अणु
		.cmd = cmd,
	पूर्ण;
	बहु_सूची va;
	पूर्णांक i;

	nargs = nargs <= UCALL_MAX_ARGS ? nargs : UCALL_MAX_ARGS;

	बहु_शुरू(va, nargs);
	क्रम (i = 0; i < nargs; ++i)
		uc.args[i] = बहु_तर्क(va, uपूर्णांक64_t);
	बहु_पूर्ण(va);

	*ucall_निकास_mmio_addr = (vm_vaddr_t)&uc;
पूर्ण

uपूर्णांक64_t get_ucall(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpu_id, काष्ठा ucall *uc)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, vcpu_id);
	काष्ठा ucall ucall = अणुपूर्ण;

	अगर (uc)
		स_रखो(uc, 0, माप(*uc));

	अगर (run->निकास_reason == KVM_EXIT_MMIO &&
	    run->mmio.phys_addr == (uपूर्णांक64_t)ucall_निकास_mmio_addr) अणु
		vm_vaddr_t gva;

		TEST_ASSERT(run->mmio.is_ग_लिखो && run->mmio.len == 8,
			    "Unexpected ucall exit mmio address access");
		स_नकल(&gva, run->mmio.data, माप(gva));
		स_नकल(&ucall, addr_gva2hva(vm, gva), माप(ucall));

		vcpu_run_complete_io(vm, vcpu_id);
		अगर (uc)
			स_नकल(uc, &ucall, माप(ucall));
	पूर्ण

	वापस ucall.cmd;
पूर्ण
