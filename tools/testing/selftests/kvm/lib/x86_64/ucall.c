<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ucall support. A ucall is a "hypercall to userspace".
 *
 * Copyright (C) 2018, Red Hat, Inc.
 */
#समावेश "kvm_util.h"

#घोषणा UCALL_PIO_PORT ((uपूर्णांक16_t)0x1000)

व्योम ucall_init(काष्ठा kvm_vm *vm, व्योम *arg)
अणु
पूर्ण

व्योम ucall_uninit(काष्ठा kvm_vm *vm)
अणु
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

	यंत्र अस्थिर("in %[port], %%al"
		: : [port] "d" (UCALL_PIO_PORT), "D" (&uc) : "rax", "memory");
पूर्ण

uपूर्णांक64_t get_ucall(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpu_id, काष्ठा ucall *uc)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, vcpu_id);
	काष्ठा ucall ucall = अणुपूर्ण;

	अगर (uc)
		स_रखो(uc, 0, माप(*uc));

	अगर (run->निकास_reason == KVM_EXIT_IO && run->io.port == UCALL_PIO_PORT) अणु
		काष्ठा kvm_regs regs;

		vcpu_regs_get(vm, vcpu_id, &regs);
		स_नकल(&ucall, addr_gva2hva(vm, (vm_vaddr_t)regs.rdi),
		       माप(ucall));

		vcpu_run_complete_io(vm, vcpu_id);
		अगर (uc)
			स_नकल(uc, &ucall, माप(ucall));
	पूर्ण

	वापस ucall.cmd;
पूर्ण
