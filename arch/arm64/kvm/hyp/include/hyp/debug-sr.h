<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ARM64_KVM_HYP_DEBUG_SR_H__
#घोषणा __ARM64_KVM_HYP_DEBUG_SR_H__

#समावेश <linux/compiler.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>

#घोषणा पढ़ो_debug(r,n)		पढ़ो_sysreg(r##n##_el1)
#घोषणा ग_लिखो_debug(v,r,n)	ग_लिखो_sysreg(v, r##n##_el1)

#घोषणा save_debug(ptr,reg,nr)						\
	चयन (nr) अणु							\
	हाल 15:	ptr[15] = पढ़ो_debug(reg, 15);			\
			fallthrough;					\
	हाल 14:	ptr[14] = पढ़ो_debug(reg, 14);			\
			fallthrough;					\
	हाल 13:	ptr[13] = पढ़ो_debug(reg, 13);			\
			fallthrough;					\
	हाल 12:	ptr[12] = पढ़ो_debug(reg, 12);			\
			fallthrough;					\
	हाल 11:	ptr[11] = पढ़ो_debug(reg, 11);			\
			fallthrough;					\
	हाल 10:	ptr[10] = पढ़ो_debug(reg, 10);			\
			fallthrough;					\
	हाल 9:		ptr[9] = पढ़ो_debug(reg, 9);			\
			fallthrough;					\
	हाल 8:		ptr[8] = पढ़ो_debug(reg, 8);			\
			fallthrough;					\
	हाल 7:		ptr[7] = पढ़ो_debug(reg, 7);			\
			fallthrough;					\
	हाल 6:		ptr[6] = पढ़ो_debug(reg, 6);			\
			fallthrough;					\
	हाल 5:		ptr[5] = पढ़ो_debug(reg, 5);			\
			fallthrough;					\
	हाल 4:		ptr[4] = पढ़ो_debug(reg, 4);			\
			fallthrough;					\
	हाल 3:		ptr[3] = पढ़ो_debug(reg, 3);			\
			fallthrough;					\
	हाल 2:		ptr[2] = पढ़ो_debug(reg, 2);			\
			fallthrough;					\
	हाल 1:		ptr[1] = पढ़ो_debug(reg, 1);			\
			fallthrough;					\
	शेष:	ptr[0] = पढ़ो_debug(reg, 0);			\
	पूर्ण

#घोषणा restore_debug(ptr,reg,nr)					\
	चयन (nr) अणु							\
	हाल 15:	ग_लिखो_debug(ptr[15], reg, 15);			\
			fallthrough;					\
	हाल 14:	ग_लिखो_debug(ptr[14], reg, 14);			\
			fallthrough;					\
	हाल 13:	ग_लिखो_debug(ptr[13], reg, 13);			\
			fallthrough;					\
	हाल 12:	ग_लिखो_debug(ptr[12], reg, 12);			\
			fallthrough;					\
	हाल 11:	ग_लिखो_debug(ptr[11], reg, 11);			\
			fallthrough;					\
	हाल 10:	ग_लिखो_debug(ptr[10], reg, 10);			\
			fallthrough;					\
	हाल 9:		ग_लिखो_debug(ptr[9], reg, 9);			\
			fallthrough;					\
	हाल 8:		ग_लिखो_debug(ptr[8], reg, 8);			\
			fallthrough;					\
	हाल 7:		ग_लिखो_debug(ptr[7], reg, 7);			\
			fallthrough;					\
	हाल 6:		ग_लिखो_debug(ptr[6], reg, 6);			\
			fallthrough;					\
	हाल 5:		ग_लिखो_debug(ptr[5], reg, 5);			\
			fallthrough;					\
	हाल 4:		ग_लिखो_debug(ptr[4], reg, 4);			\
			fallthrough;					\
	हाल 3:		ग_लिखो_debug(ptr[3], reg, 3);			\
			fallthrough;					\
	हाल 2:		ग_लिखो_debug(ptr[2], reg, 2);			\
			fallthrough;					\
	हाल 1:		ग_लिखो_debug(ptr[1], reg, 1);			\
			fallthrough;					\
	शेष:	ग_लिखो_debug(ptr[0], reg, 0);			\
	पूर्ण

अटल व्योम __debug_save_state(काष्ठा kvm_guest_debug_arch *dbg,
			       काष्ठा kvm_cpu_context *ctxt)
अणु
	u64 aa64dfr0;
	पूर्णांक brps, wrps;

	aa64dfr0 = पढ़ो_sysreg(id_aa64dfr0_el1);
	brps = (aa64dfr0 >> 12) & 0xf;
	wrps = (aa64dfr0 >> 20) & 0xf;

	save_debug(dbg->dbg_bcr, dbgbcr, brps);
	save_debug(dbg->dbg_bvr, dbgbvr, brps);
	save_debug(dbg->dbg_wcr, dbgwcr, wrps);
	save_debug(dbg->dbg_wvr, dbgwvr, wrps);

	ctxt_sys_reg(ctxt, MDCCINT_EL1) = पढ़ो_sysreg(mdccपूर्णांक_el1);
पूर्ण

अटल व्योम __debug_restore_state(काष्ठा kvm_guest_debug_arch *dbg,
				  काष्ठा kvm_cpu_context *ctxt)
अणु
	u64 aa64dfr0;
	पूर्णांक brps, wrps;

	aa64dfr0 = पढ़ो_sysreg(id_aa64dfr0_el1);

	brps = (aa64dfr0 >> 12) & 0xf;
	wrps = (aa64dfr0 >> 20) & 0xf;

	restore_debug(dbg->dbg_bcr, dbgbcr, brps);
	restore_debug(dbg->dbg_bvr, dbgbvr, brps);
	restore_debug(dbg->dbg_wcr, dbgwcr, wrps);
	restore_debug(dbg->dbg_wvr, dbgwvr, wrps);

	ग_लिखो_sysreg(ctxt_sys_reg(ctxt, MDCCINT_EL1), mdccपूर्णांक_el1);
पूर्ण

अटल अंतरभूत व्योम __debug_चयन_to_guest_common(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpu_context *host_ctxt;
	काष्ठा kvm_cpu_context *guest_ctxt;
	काष्ठा kvm_guest_debug_arch *host_dbg;
	काष्ठा kvm_guest_debug_arch *guest_dbg;

	अगर (!(vcpu->arch.flags & KVM_ARM64_DEBUG_सूचीTY))
		वापस;

	host_ctxt = &this_cpu_ptr(&kvm_host_data)->host_ctxt;
	guest_ctxt = &vcpu->arch.ctxt;
	host_dbg = &vcpu->arch.host_debug_state.regs;
	guest_dbg = kern_hyp_va(vcpu->arch.debug_ptr);

	__debug_save_state(host_dbg, host_ctxt);
	__debug_restore_state(guest_dbg, guest_ctxt);
पूर्ण

अटल अंतरभूत व्योम __debug_चयन_to_host_common(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpu_context *host_ctxt;
	काष्ठा kvm_cpu_context *guest_ctxt;
	काष्ठा kvm_guest_debug_arch *host_dbg;
	काष्ठा kvm_guest_debug_arch *guest_dbg;

	अगर (!(vcpu->arch.flags & KVM_ARM64_DEBUG_सूचीTY))
		वापस;

	host_ctxt = &this_cpu_ptr(&kvm_host_data)->host_ctxt;
	guest_ctxt = &vcpu->arch.ctxt;
	host_dbg = &vcpu->arch.host_debug_state.regs;
	guest_dbg = kern_hyp_va(vcpu->arch.debug_ptr);

	__debug_save_state(guest_dbg, guest_ctxt);
	__debug_restore_state(host_dbg, host_ctxt);

	vcpu->arch.flags &= ~KVM_ARM64_DEBUG_सूचीTY;
पूर्ण

#पूर्ण_अगर /* __ARM64_KVM_HYP_DEBUG_SR_H__ */
