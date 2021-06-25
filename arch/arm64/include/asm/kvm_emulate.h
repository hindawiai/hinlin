<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Derived from arch/arm/include/kvm_emulate.h
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#अगर_अघोषित __ARM64_KVM_EMULATE_H__
#घोषणा __ARM64_KVM_EMULATE_H__

#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/kvm_arm.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/virt.h>

#घोषणा CURRENT_EL_SP_EL0_VECTOR	0x0
#घोषणा CURRENT_EL_SP_ELx_VECTOR	0x200
#घोषणा LOWER_EL_AArch64_VECTOR		0x400
#घोषणा LOWER_EL_AArch32_VECTOR		0x600

क्रमागत exception_type अणु
	except_type_sync	= 0,
	except_type_irq		= 0x80,
	except_type_fiq		= 0x100,
	except_type_serror	= 0x180,
पूर्ण;

bool kvm_condition_valid32(स्थिर काष्ठा kvm_vcpu *vcpu);
व्योम kvm_skip_instr32(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_inject_undefined(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_inject_vabt(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_inject_dabt(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ addr);
व्योम kvm_inject_pabt(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ addr);

अटल __always_अंतरभूत bool vcpu_el1_is_32bit(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !(vcpu->arch.hcr_el2 & HCR_RW);
पूर्ण

अटल अंतरभूत व्योम vcpu_reset_hcr(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.hcr_el2 = HCR_GUEST_FLAGS;
	अगर (is_kernel_in_hyp_mode())
		vcpu->arch.hcr_el2 |= HCR_E2H;
	अगर (cpus_have_स्थिर_cap(ARM64_HAS_RAS_EXTN)) अणु
		/* route synchronous बाह्यal पात exceptions to EL2 */
		vcpu->arch.hcr_el2 |= HCR_TEA;
		/* trap error record accesses */
		vcpu->arch.hcr_el2 |= HCR_TERR;
	पूर्ण

	अगर (cpus_have_स्थिर_cap(ARM64_HAS_STAGE2_FWB)) अणु
		vcpu->arch.hcr_el2 |= HCR_FWB;
	पूर्ण अन्यथा अणु
		/*
		 * For non-FWB CPUs, we trap VM ops (HCR_EL2.TVM) until M+C
		 * get set in SCTLR_EL1 such that we can detect when the guest
		 * MMU माला_लो turned on and करो the necessary cache मुख्यtenance
		 * then.
		 */
		vcpu->arch.hcr_el2 |= HCR_TVM;
	पूर्ण

	अगर (test_bit(KVM_ARM_VCPU_EL1_32BIT, vcpu->arch.features))
		vcpu->arch.hcr_el2 &= ~HCR_RW;

	/*
	 * TID3: trap feature रेजिस्टर accesses that we भवise.
	 * For now this is conditional, since no AArch32 feature regs
	 * are currently भवised.
	 */
	अगर (!vcpu_el1_is_32bit(vcpu))
		vcpu->arch.hcr_el2 |= HCR_TID3;

	अगर (cpus_have_स्थिर_cap(ARM64_MISMATCHED_CACHE_TYPE) ||
	    vcpu_el1_is_32bit(vcpu))
		vcpu->arch.hcr_el2 |= HCR_TID2;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *vcpu_hcr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (अचिन्हित दीर्घ *)&vcpu->arch.hcr_el2;
पूर्ण

अटल अंतरभूत व्योम vcpu_clear_wfx_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.hcr_el2 &= ~HCR_TWE;
	अगर (atomic_पढ़ो(&vcpu->arch.vgic_cpu.vgic_v3.its_vpe.vlpi_count) ||
	    vcpu->kvm->arch.vgic.nassgireq)
		vcpu->arch.hcr_el2 &= ~HCR_TWI;
	अन्यथा
		vcpu->arch.hcr_el2 |= HCR_TWI;
पूर्ण

अटल अंतरभूत व्योम vcpu_set_wfx_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.hcr_el2 |= HCR_TWE;
	vcpu->arch.hcr_el2 |= HCR_TWI;
पूर्ण

अटल अंतरभूत व्योम vcpu_ptrauth_enable(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.hcr_el2 |= (HCR_API | HCR_APK);
पूर्ण

अटल अंतरभूत व्योम vcpu_ptrauth_disable(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.hcr_el2 &= ~(HCR_API | HCR_APK);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vcpu_get_vsesr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.vsesr_el2;
पूर्ण

अटल अंतरभूत व्योम vcpu_set_vsesr(काष्ठा kvm_vcpu *vcpu, u64 vsesr)
अणु
	vcpu->arch.vsesr_el2 = vsesr;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ *vcpu_pc(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (अचिन्हित दीर्घ *)&vcpu_gp_regs(vcpu)->pc;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ *vcpu_cpsr(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (अचिन्हित दीर्घ *)&vcpu_gp_regs(vcpu)->pstate;
पूर्ण

अटल __always_अंतरभूत bool vcpu_mode_is_32bit(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(*vcpu_cpsr(vcpu) & PSR_MODE32_BIT);
पूर्ण

अटल __always_अंतरभूत bool kvm_condition_valid(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu_mode_is_32bit(vcpu))
		वापस kvm_condition_valid32(vcpu);

	वापस true;
पूर्ण

अटल अंतरभूत व्योम vcpu_set_thumb(काष्ठा kvm_vcpu *vcpu)
अणु
	*vcpu_cpsr(vcpu) |= PSR_AA32_T_BIT;
पूर्ण

/*
 * vcpu_get_reg and vcpu_set_reg should always be passed a रेजिस्टर number
 * coming from a पढ़ो of ESR_EL2. Otherwise, it may give the wrong result on
 * AArch32 with banked रेजिस्टरs.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ vcpu_get_reg(स्थिर काष्ठा kvm_vcpu *vcpu,
					 u8 reg_num)
अणु
	वापस (reg_num == 31) ? 0 : vcpu_gp_regs(vcpu)->regs[reg_num];
पूर्ण

अटल __always_अंतरभूत व्योम vcpu_set_reg(काष्ठा kvm_vcpu *vcpu, u8 reg_num,
				अचिन्हित दीर्घ val)
अणु
	अगर (reg_num != 31)
		vcpu_gp_regs(vcpu)->regs[reg_num] = val;
पूर्ण

/*
 * The layout of SPSR क्रम an AArch32 state is dअगरferent when observed from an
 * AArch64 SPSR_ELx or an AArch32 SPSR_*. This function generates the AArch32
 * view given an AArch64 view.
 *
 * In ARM DDI 0487E.a see:
 *
 * - The AArch64 view (SPSR_EL2) in section C5.2.18, page C5-426
 * - The AArch32 view (SPSR_abt) in section G8.2.126, page G8-6256
 * - The AArch32 view (SPSR_und) in section G8.2.132, page G8-6280
 *
 * Which show the following dअगरferences:
 *
 * | Bit | AA64 | AA32 | Notes                       |
 * +-----+------+------+-----------------------------|
 * | 24  | DIT  | J    | J is RES0 in ARMv8          |
 * | 21  | SS   | DIT  | SS करोesn't exist in AArch32 |
 *
 * ... and all other bits are (currently) common.
 */
अटल अंतरभूत अचिन्हित दीर्घ host_spsr_to_spsr32(अचिन्हित दीर्घ spsr)
अणु
	स्थिर अचिन्हित दीर्घ overlap = BIT(24) | BIT(21);
	अचिन्हित दीर्घ dit = !!(spsr & PSR_AA32_DIT_BIT);

	spsr &= ~overlap;

	spsr |= dit << 21;

	वापस spsr;
पूर्ण

अटल अंतरभूत bool vcpu_mode_priv(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	u32 mode;

	अगर (vcpu_mode_is_32bit(vcpu)) अणु
		mode = *vcpu_cpsr(vcpu) & PSR_AA32_MODE_MASK;
		वापस mode > PSR_AA32_MODE_USR;
	पूर्ण

	mode = *vcpu_cpsr(vcpu) & PSR_MODE_MASK;

	वापस mode != PSR_MODE_EL0t;
पूर्ण

अटल __always_अंतरभूत u32 kvm_vcpu_get_esr(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.fault.esr_el2;
पूर्ण

अटल __always_अंतरभूत पूर्णांक kvm_vcpu_get_condition(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	u32 esr = kvm_vcpu_get_esr(vcpu);

	अगर (esr & ESR_ELx_CV)
		वापस (esr & ESR_ELx_COND_MASK) >> ESR_ELx_COND_SHIFT;

	वापस -1;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ kvm_vcpu_get_hfar(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.fault.far_el2;
पूर्ण

अटल __always_अंतरभूत phys_addr_t kvm_vcpu_get_fault_ipa(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस ((phys_addr_t)vcpu->arch.fault.hpfar_el2 & HPFAR_MASK) << 8;
पूर्ण

अटल अंतरभूत u64 kvm_vcpu_get_disr(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.fault.disr_el1;
पूर्ण

अटल अंतरभूत u32 kvm_vcpu_hvc_get_imm(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_get_esr(vcpu) & ESR_ELx_xVC_IMM_MASK;
पूर्ण

अटल __always_अंतरभूत bool kvm_vcpu_dabt_isvalid(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(kvm_vcpu_get_esr(vcpu) & ESR_ELx_ISV);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvm_vcpu_dabt_iss_nisv_sanitized(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_get_esr(vcpu) & (ESR_ELx_CM | ESR_ELx_WNR | ESR_ELx_FSC);
पूर्ण

अटल अंतरभूत bool kvm_vcpu_dabt_issext(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(kvm_vcpu_get_esr(vcpu) & ESR_ELx_SSE);
पूर्ण

अटल अंतरभूत bool kvm_vcpu_dabt_issf(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(kvm_vcpu_get_esr(vcpu) & ESR_ELx_SF);
पूर्ण

अटल __always_अंतरभूत पूर्णांक kvm_vcpu_dabt_get_rd(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (kvm_vcpu_get_esr(vcpu) & ESR_ELx_SRT_MASK) >> ESR_ELx_SRT_SHIFT;
पूर्ण

अटल __always_अंतरभूत bool kvm_vcpu_abt_iss1tw(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(kvm_vcpu_get_esr(vcpu) & ESR_ELx_S1PTW);
पूर्ण

/* Always check क्रम S1PTW *beक्रमe* using this. */
अटल __always_अंतरभूत bool kvm_vcpu_dabt_isग_लिखो(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_get_esr(vcpu) & ESR_ELx_WNR;
पूर्ण

अटल अंतरभूत bool kvm_vcpu_dabt_is_cm(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(kvm_vcpu_get_esr(vcpu) & ESR_ELx_CM);
पूर्ण

अटल __always_अंतरभूत अचिन्हित पूर्णांक kvm_vcpu_dabt_get_as(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 1 << ((kvm_vcpu_get_esr(vcpu) & ESR_ELx_SAS) >> ESR_ELx_SAS_SHIFT);
पूर्ण

/* This one is not specअगरic to Data Abort */
अटल __always_अंतरभूत bool kvm_vcpu_trap_il_is32bit(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(kvm_vcpu_get_esr(vcpu) & ESR_ELx_IL);
पूर्ण

अटल __always_अंतरभूत u8 kvm_vcpu_trap_get_class(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस ESR_ELx_EC(kvm_vcpu_get_esr(vcpu));
पूर्ण

अटल अंतरभूत bool kvm_vcpu_trap_is_iabt(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_trap_get_class(vcpu) == ESR_ELx_EC_IABT_LOW;
पूर्ण

अटल अंतरभूत bool kvm_vcpu_trap_is_exec_fault(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_trap_is_iabt(vcpu) && !kvm_vcpu_abt_iss1tw(vcpu);
पूर्ण

अटल __always_अंतरभूत u8 kvm_vcpu_trap_get_fault(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_get_esr(vcpu) & ESR_ELx_FSC;
पूर्ण

अटल __always_अंतरभूत u8 kvm_vcpu_trap_get_fault_type(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_get_esr(vcpu) & ESR_ELx_FSC_TYPE;
पूर्ण

अटल __always_अंतरभूत u8 kvm_vcpu_trap_get_fault_level(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_get_esr(vcpu) & ESR_ELx_FSC_LEVEL;
पूर्ण

अटल __always_अंतरभूत bool kvm_vcpu_abt_issea(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	चयन (kvm_vcpu_trap_get_fault(vcpu)) अणु
	हाल FSC_SEA:
	हाल FSC_SEA_TTW0:
	हाल FSC_SEA_TTW1:
	हाल FSC_SEA_TTW2:
	हाल FSC_SEA_TTW3:
	हाल FSC_SECC:
	हाल FSC_SECC_TTW0:
	हाल FSC_SECC_TTW1:
	हाल FSC_SECC_TTW2:
	हाल FSC_SECC_TTW3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल __always_अंतरभूत पूर्णांक kvm_vcpu_sys_get_rt(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 esr = kvm_vcpu_get_esr(vcpu);
	वापस ESR_ELx_SYS64_ISS_RT(esr);
पूर्ण

अटल अंतरभूत bool kvm_is_ग_लिखो_fault(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_vcpu_abt_iss1tw(vcpu))
		वापस true;

	अगर (kvm_vcpu_trap_is_iabt(vcpu))
		वापस false;

	वापस kvm_vcpu_dabt_isग_लिखो(vcpu);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvm_vcpu_get_mpidr_aff(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu_पढ़ो_sys_reg(vcpu, MPIDR_EL1) & MPIDR_HWID_BITMASK;
पूर्ण

अटल अंतरभूत व्योम kvm_vcpu_set_be(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu_mode_is_32bit(vcpu)) अणु
		*vcpu_cpsr(vcpu) |= PSR_AA32_E_BIT;
	पूर्ण अन्यथा अणु
		u64 sctlr = vcpu_पढ़ो_sys_reg(vcpu, SCTLR_EL1);
		sctlr |= (1 << 25);
		vcpu_ग_लिखो_sys_reg(vcpu, sctlr, SCTLR_EL1);
	पूर्ण
पूर्ण

अटल अंतरभूत bool kvm_vcpu_is_be(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu_mode_is_32bit(vcpu))
		वापस !!(*vcpu_cpsr(vcpu) & PSR_AA32_E_BIT);

	वापस !!(vcpu_पढ़ो_sys_reg(vcpu, SCTLR_EL1) & (1 << 25));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vcpu_data_guest_to_host(काष्ठा kvm_vcpu *vcpu,
						    अचिन्हित दीर्घ data,
						    अचिन्हित पूर्णांक len)
अणु
	अगर (kvm_vcpu_is_be(vcpu)) अणु
		चयन (len) अणु
		हाल 1:
			वापस data & 0xff;
		हाल 2:
			वापस be16_to_cpu(data & 0xffff);
		हाल 4:
			वापस be32_to_cpu(data & 0xffffffff);
		शेष:
			वापस be64_to_cpu(data);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (len) अणु
		हाल 1:
			वापस data & 0xff;
		हाल 2:
			वापस le16_to_cpu(data & 0xffff);
		हाल 4:
			वापस le32_to_cpu(data & 0xffffffff);
		शेष:
			वापस le64_to_cpu(data);
		पूर्ण
	पूर्ण

	वापस data;		/* Leave LE untouched */
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vcpu_data_host_to_guest(काष्ठा kvm_vcpu *vcpu,
						    अचिन्हित दीर्घ data,
						    अचिन्हित पूर्णांक len)
अणु
	अगर (kvm_vcpu_is_be(vcpu)) अणु
		चयन (len) अणु
		हाल 1:
			वापस data & 0xff;
		हाल 2:
			वापस cpu_to_be16(data & 0xffff);
		हाल 4:
			वापस cpu_to_be32(data & 0xffffffff);
		शेष:
			वापस cpu_to_be64(data);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (len) अणु
		हाल 1:
			वापस data & 0xff;
		हाल 2:
			वापस cpu_to_le16(data & 0xffff);
		हाल 4:
			वापस cpu_to_le32(data & 0xffffffff);
		शेष:
			वापस cpu_to_le64(data);
		पूर्ण
	पूर्ण

	वापस data;		/* Leave LE untouched */
पूर्ण

अटल __always_अंतरभूत व्योम kvm_incr_pc(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.flags |= KVM_ARM64_INCREMENT_PC;
पूर्ण

अटल अंतरभूत bool vcpu_has_feature(काष्ठा kvm_vcpu *vcpu, पूर्णांक feature)
अणु
	वापस test_bit(feature, vcpu->arch.features);
पूर्ण

#पूर्ण_अगर /* __ARM64_KVM_EMULATE_H__ */
