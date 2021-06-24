<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ucall support. A ucall is a "hypercall to userspace".
 *
 * Copyright (C) 2019 Red Hat, Inc.
 */
#समावेश "kvm_util.h"

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

	/* Exit via DIAGNOSE 0x501 (normally used क्रम अवरोधpoपूर्णांकs) */
	यंत्र अस्थिर ("diag 0,%0,0x501" : : "a"(&uc) : "memory");
पूर्ण

uपूर्णांक64_t get_ucall(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpu_id, काष्ठा ucall *uc)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, vcpu_id);
	काष्ठा ucall ucall = अणुपूर्ण;

	अगर (uc)
		स_रखो(uc, 0, माप(*uc));

	अगर (run->निकास_reason == KVM_EXIT_S390_SIEIC &&
	    run->s390_sieic.icptcode == 4 &&
	    (run->s390_sieic.ipa >> 8) == 0x83 &&    /* 0x83 means DIAGNOSE */
	    (run->s390_sieic.ipb >> 16) == 0x501) अणु
		पूर्णांक reg = run->s390_sieic.ipa & 0xf;

		स_नकल(&ucall, addr_gva2hva(vm, run->s.regs.gprs[reg]),
		       माप(ucall));

		vcpu_run_complete_io(vm, vcpu_id);
		अगर (uc)
			स_नकल(uc, &ucall, माप(ucall));
	पूर्ण

	वापस ucall.cmd;
पूर्ण
