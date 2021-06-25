<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <hyp/sysreg-sr.h>

#समावेश <linux/compiler.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>

/*
 * Non-VHE: Both host and guest must save everything.
 */

व्योम __sysreg_save_state_nvhe(काष्ठा kvm_cpu_context *ctxt)
अणु
	__sysreg_save_el1_state(ctxt);
	__sysreg_save_common_state(ctxt);
	__sysreg_save_user_state(ctxt);
	__sysreg_save_el2_वापस_state(ctxt);
पूर्ण

व्योम __sysreg_restore_state_nvhe(काष्ठा kvm_cpu_context *ctxt)
अणु
	__sysreg_restore_el1_state(ctxt);
	__sysreg_restore_common_state(ctxt);
	__sysreg_restore_user_state(ctxt);
	__sysreg_restore_el2_वापस_state(ctxt);
पूर्ण
