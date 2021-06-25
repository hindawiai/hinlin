<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Fault injection क्रम both 32 and 64bit guests.
 *
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Based on arch/arm/kvm/emulate.c
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <hyp/adjust_pc.h>
#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_emulate.h>

#अगर !defined (__KVM_NVHE_HYPERVISOR__) && !defined (__KVM_VHE_HYPERVISOR__)
#त्रुटि Hypervisor code only!
#पूर्ण_अगर

अटल अंतरभूत u64 __vcpu_पढ़ो_sys_reg(स्थिर काष्ठा kvm_vcpu *vcpu, पूर्णांक reg)
अणु
	u64 val;

	अगर (__vcpu_पढ़ो_sys_reg_from_cpu(reg, &val))
		वापस val;

	वापस __vcpu_sys_reg(vcpu, reg);
पूर्ण

अटल अंतरभूत व्योम __vcpu_ग_लिखो_sys_reg(काष्ठा kvm_vcpu *vcpu, u64 val, पूर्णांक reg)
अणु
	अगर (__vcpu_ग_लिखो_sys_reg_to_cpu(val, reg))
		वापस;

	 __vcpu_sys_reg(vcpu, reg) = val;
पूर्ण

अटल व्योम __vcpu_ग_लिखो_spsr(काष्ठा kvm_vcpu *vcpu, u64 val)
अणु
	ग_लिखो_sysreg_el1(val, SYS_SPSR);
पूर्ण

अटल व्योम __vcpu_ग_लिखो_spsr_abt(काष्ठा kvm_vcpu *vcpu, u64 val)
अणु
	अगर (has_vhe())
		ग_लिखो_sysreg(val, spsr_abt);
	अन्यथा
		vcpu->arch.ctxt.spsr_abt = val;
पूर्ण

अटल व्योम __vcpu_ग_लिखो_spsr_und(काष्ठा kvm_vcpu *vcpu, u64 val)
अणु
	अगर (has_vhe())
		ग_लिखो_sysreg(val, spsr_und);
	अन्यथा
		vcpu->arch.ctxt.spsr_und = val;
पूर्ण

/*
 * This perक्रमms the exception entry at a given EL (@target_mode), stashing PC
 * and PSTATE पूर्णांकo ELR and SPSR respectively, and compute the new PC/PSTATE.
 * The EL passed to this function *must* be a non-secure, privileged mode with
 * bit 0 being set (PSTATE.SP == 1).
 *
 * When an exception is taken, most PSTATE fields are left unchanged in the
 * handler. However, some are explicitly overridden (e.g. M[4:0]). Luckily all
 * of the inherited bits have the same position in the AArch64/AArch32 SPSR_ELx
 * layouts, so we करोn't need to shuffle these क्रम exceptions from AArch32 EL0.
 *
 * For the SPSR_ELx layout क्रम AArch64, see ARM DDI 0487E.a page C5-429.
 * For the SPSR_ELx layout क्रम AArch32, see ARM DDI 0487E.a page C5-426.
 *
 * Here we manipulate the fields in order of the AArch64 SPSR_ELx layout, from
 * MSB to LSB.
 */
अटल व्योम enter_exception64(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ target_mode,
			      क्रमागत exception_type type)
अणु
	अचिन्हित दीर्घ sctlr, vbar, old, new, mode;
	u64 exc_offset;

	mode = *vcpu_cpsr(vcpu) & (PSR_MODE_MASK | PSR_MODE32_BIT);

	अगर      (mode == target_mode)
		exc_offset = CURRENT_EL_SP_ELx_VECTOR;
	अन्यथा अगर ((mode | PSR_MODE_THREAD_BIT) == target_mode)
		exc_offset = CURRENT_EL_SP_EL0_VECTOR;
	अन्यथा अगर (!(mode & PSR_MODE32_BIT))
		exc_offset = LOWER_EL_AArch64_VECTOR;
	अन्यथा
		exc_offset = LOWER_EL_AArch32_VECTOR;

	चयन (target_mode) अणु
	हाल PSR_MODE_EL1h:
		vbar = __vcpu_पढ़ो_sys_reg(vcpu, VBAR_EL1);
		sctlr = __vcpu_पढ़ो_sys_reg(vcpu, SCTLR_EL1);
		__vcpu_ग_लिखो_sys_reg(vcpu, *vcpu_pc(vcpu), ELR_EL1);
		अवरोध;
	शेष:
		/* Don't करो that */
		BUG();
	पूर्ण

	*vcpu_pc(vcpu) = vbar + exc_offset + type;

	old = *vcpu_cpsr(vcpu);
	new = 0;

	new |= (old & PSR_N_BIT);
	new |= (old & PSR_Z_BIT);
	new |= (old & PSR_C_BIT);
	new |= (old & PSR_V_BIT);

	// TODO: TCO (अगर/when ARMv8.5-MemTag is exposed to guests)

	new |= (old & PSR_DIT_BIT);

	// PSTATE.UAO is set to zero upon any exception to AArch64
	// See ARM DDI 0487E.a, page D5-2579.

	// PSTATE.PAN is unchanged unless SCTLR_ELx.SPAN == 0b0
	// SCTLR_ELx.SPAN is RES1 when ARMv8.1-PAN is not implemented
	// See ARM DDI 0487E.a, page D5-2578.
	new |= (old & PSR_PAN_BIT);
	अगर (!(sctlr & SCTLR_EL1_SPAN))
		new |= PSR_PAN_BIT;

	// PSTATE.SS is set to zero upon any exception to AArch64
	// See ARM DDI 0487E.a, page D2-2452.

	// PSTATE.IL is set to zero upon any exception to AArch64
	// See ARM DDI 0487E.a, page D1-2306.

	// PSTATE.SSBS is set to SCTLR_ELx.DSSBS upon any exception to AArch64
	// See ARM DDI 0487E.a, page D13-3258
	अगर (sctlr & SCTLR_ELx_DSSBS)
		new |= PSR_SSBS_BIT;

	// PSTATE.BTYPE is set to zero upon any exception to AArch64
	// See ARM DDI 0487E.a, pages D1-2293 to D1-2294.

	new |= PSR_D_BIT;
	new |= PSR_A_BIT;
	new |= PSR_I_BIT;
	new |= PSR_F_BIT;

	new |= target_mode;

	*vcpu_cpsr(vcpu) = new;
	__vcpu_ग_लिखो_spsr(vcpu, old);
पूर्ण

/*
 * When an exception is taken, most CPSR fields are left unchanged in the
 * handler. However, some are explicitly overridden (e.g. M[4:0]).
 *
 * The SPSR/SPSR_ELx layouts dअगरfer, and the below is पूर्णांकended to work with
 * either क्रमmat. Note: SPSR.J bit करोesn't exist in SPSR_ELx, but this bit was
 * obsoleted by the ARMv7 भवization extensions and is RES0.
 *
 * For the SPSR layout seen from AArch32, see:
 * - ARM DDI 0406C.d, page B1-1148
 * - ARM DDI 0487E.a, page G8-6264
 *
 * For the SPSR_ELx layout क्रम AArch32 seen from AArch64, see:
 * - ARM DDI 0487E.a, page C5-426
 *
 * Here we manipulate the fields in order of the AArch32 SPSR_ELx layout, from
 * MSB to LSB.
 */
अटल अचिन्हित दीर्घ get_except32_cpsr(काष्ठा kvm_vcpu *vcpu, u32 mode)
अणु
	u32 sctlr = __vcpu_पढ़ो_sys_reg(vcpu, SCTLR_EL1);
	अचिन्हित दीर्घ old, new;

	old = *vcpu_cpsr(vcpu);
	new = 0;

	new |= (old & PSR_AA32_N_BIT);
	new |= (old & PSR_AA32_Z_BIT);
	new |= (old & PSR_AA32_C_BIT);
	new |= (old & PSR_AA32_V_BIT);
	new |= (old & PSR_AA32_Q_BIT);

	// CPSR.IT[7:0] are set to zero upon any exception
	// See ARM DDI 0487E.a, section G1.12.3
	// See ARM DDI 0406C.d, section B1.8.3

	new |= (old & PSR_AA32_DIT_BIT);

	// CPSR.SSBS is set to SCTLR.DSSBS upon any exception
	// See ARM DDI 0487E.a, page G8-6244
	अगर (sctlr & BIT(31))
		new |= PSR_AA32_SSBS_BIT;

	// CPSR.PAN is unchanged unless SCTLR.SPAN == 0b0
	// SCTLR.SPAN is RES1 when ARMv8.1-PAN is not implemented
	// See ARM DDI 0487E.a, page G8-6246
	new |= (old & PSR_AA32_PAN_BIT);
	अगर (!(sctlr & BIT(23)))
		new |= PSR_AA32_PAN_BIT;

	// SS करोes not exist in AArch32, so ignore

	// CPSR.IL is set to zero upon any exception
	// See ARM DDI 0487E.a, page G1-5527

	new |= (old & PSR_AA32_GE_MASK);

	// CPSR.IT[7:0] are set to zero upon any exception
	// See prior comment above

	// CPSR.E is set to SCTLR.EE upon any exception
	// See ARM DDI 0487E.a, page G8-6245
	// See ARM DDI 0406C.d, page B4-1701
	अगर (sctlr & BIT(25))
		new |= PSR_AA32_E_BIT;

	// CPSR.A is unchanged upon an exception to Undefined, Supervisor
	// CPSR.A is set upon an exception to other modes
	// See ARM DDI 0487E.a, pages G1-5515 to G1-5516
	// See ARM DDI 0406C.d, page B1-1182
	new |= (old & PSR_AA32_A_BIT);
	अगर (mode != PSR_AA32_MODE_UND && mode != PSR_AA32_MODE_SVC)
		new |= PSR_AA32_A_BIT;

	// CPSR.I is set upon any exception
	// See ARM DDI 0487E.a, pages G1-5515 to G1-5516
	// See ARM DDI 0406C.d, page B1-1182
	new |= PSR_AA32_I_BIT;

	// CPSR.F is set upon an exception to FIQ
	// CPSR.F is unchanged upon an exception to other modes
	// See ARM DDI 0487E.a, pages G1-5515 to G1-5516
	// See ARM DDI 0406C.d, page B1-1182
	new |= (old & PSR_AA32_F_BIT);
	अगर (mode == PSR_AA32_MODE_FIQ)
		new |= PSR_AA32_F_BIT;

	// CPSR.T is set to SCTLR.TE upon any exception
	// See ARM DDI 0487E.a, page G8-5514
	// See ARM DDI 0406C.d, page B1-1181
	अगर (sctlr & BIT(30))
		new |= PSR_AA32_T_BIT;

	new |= mode;

	वापस new;
पूर्ण

/*
 * Table taken from ARMv8 ARM DDI0487B-B, table G1-10.
 */
अटल स्थिर u8 वापस_offsets[8][2] = अणु
	[0] = अणु 0, 0 पूर्ण,		/* Reset, unused */
	[1] = अणु 4, 2 पूर्ण,		/* Undefined */
	[2] = अणु 0, 0 पूर्ण,		/* SVC, unused */
	[3] = अणु 4, 4 पूर्ण,		/* Prefetch पात */
	[4] = अणु 8, 8 पूर्ण,		/* Data पात */
	[5] = अणु 0, 0 पूर्ण,		/* HVC, unused */
	[6] = अणु 4, 4 पूर्ण,		/* IRQ, unused */
	[7] = अणु 4, 4 पूर्ण,		/* FIQ, unused */
पूर्ण;

अटल व्योम enter_exception32(काष्ठा kvm_vcpu *vcpu, u32 mode, u32 vect_offset)
अणु
	अचिन्हित दीर्घ spsr = *vcpu_cpsr(vcpu);
	bool is_thumb = (spsr & PSR_AA32_T_BIT);
	u32 sctlr = __vcpu_पढ़ो_sys_reg(vcpu, SCTLR_EL1);
	u32 वापस_address;

	*vcpu_cpsr(vcpu) = get_except32_cpsr(vcpu, mode);
	वापस_address   = *vcpu_pc(vcpu);
	वापस_address  += वापस_offsets[vect_offset >> 2][is_thumb];

	/* KVM only enters the ABT and UND modes, so only deal with those */
	चयन(mode) अणु
	हाल PSR_AA32_MODE_ABT:
		__vcpu_ग_लिखो_spsr_abt(vcpu, host_spsr_to_spsr32(spsr));
		vcpu_gp_regs(vcpu)->compat_lr_abt = वापस_address;
		अवरोध;

	हाल PSR_AA32_MODE_UND:
		__vcpu_ग_लिखो_spsr_und(vcpu, host_spsr_to_spsr32(spsr));
		vcpu_gp_regs(vcpu)->compat_lr_und = वापस_address;
		अवरोध;
	पूर्ण

	/* Branch to exception vector */
	अगर (sctlr & (1 << 13))
		vect_offset += 0xffff0000;
	अन्यथा /* always have security exceptions */
		vect_offset += __vcpu_पढ़ो_sys_reg(vcpu, VBAR_EL1);

	*vcpu_pc(vcpu) = vect_offset;
पूर्ण

अटल व्योम kvm_inject_exception(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu_el1_is_32bit(vcpu)) अणु
		चयन (vcpu->arch.flags & KVM_ARM64_EXCEPT_MASK) अणु
		हाल KVM_ARM64_EXCEPT_AA32_UND:
			enter_exception32(vcpu, PSR_AA32_MODE_UND, 4);
			अवरोध;
		हाल KVM_ARM64_EXCEPT_AA32_IABT:
			enter_exception32(vcpu, PSR_AA32_MODE_ABT, 12);
			अवरोध;
		हाल KVM_ARM64_EXCEPT_AA32_DABT:
			enter_exception32(vcpu, PSR_AA32_MODE_ABT, 16);
			अवरोध;
		शेष:
			/* Err... */
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (vcpu->arch.flags & KVM_ARM64_EXCEPT_MASK) अणु
		हाल (KVM_ARM64_EXCEPT_AA64_ELx_SYNC |
		      KVM_ARM64_EXCEPT_AA64_EL1):
			enter_exception64(vcpu, PSR_MODE_EL1h, except_type_sync);
			अवरोध;
		शेष:
			/*
			 * Only EL1_SYNC makes sense so far, EL2_अणुSYNC,IRQपूर्ण
			 * will be implemented at some poपूर्णांक. Everything
			 * अन्यथा माला_लो silently ignored.
			 */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Adjust the guest PC (and potentially exception state) depending on
 * flags provided by the emulation code.
 */
व्योम __kvm_adjust_pc(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.flags & KVM_ARM64_PENDING_EXCEPTION) अणु
		kvm_inject_exception(vcpu);
		vcpu->arch.flags &= ~(KVM_ARM64_PENDING_EXCEPTION |
				      KVM_ARM64_EXCEPT_MASK);
	पूर्ण अन्यथा 	अगर (vcpu->arch.flags & KVM_ARM64_INCREMENT_PC) अणु
		kvm_skip_instr(vcpu);
		vcpu->arch.flags &= ~KVM_ARM64_INCREMENT_PC;
	पूर्ण
पूर्ण
