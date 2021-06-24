<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <hyp/adjust_pc.h>

#समावेश <linux/compiler.h>
#समावेश <linux/irqchip/arm-gic-v3.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>

#घोषणा vtr_to_max_lr_idx(v)		((v) & 0xf)
#घोषणा vtr_to_nr_pre_bits(v)		((((u32)(v) >> 26) & 7) + 1)
#घोषणा vtr_to_nr_apr_regs(v)		(1 << (vtr_to_nr_pre_bits(v) - 5))

अटल u64 __gic_v3_get_lr(अचिन्हित पूर्णांक lr)
अणु
	चयन (lr & 0xf) अणु
	हाल 0:
		वापस पढ़ो_gicreg(ICH_LR0_EL2);
	हाल 1:
		वापस पढ़ो_gicreg(ICH_LR1_EL2);
	हाल 2:
		वापस पढ़ो_gicreg(ICH_LR2_EL2);
	हाल 3:
		वापस पढ़ो_gicreg(ICH_LR3_EL2);
	हाल 4:
		वापस पढ़ो_gicreg(ICH_LR4_EL2);
	हाल 5:
		वापस पढ़ो_gicreg(ICH_LR5_EL2);
	हाल 6:
		वापस पढ़ो_gicreg(ICH_LR6_EL2);
	हाल 7:
		वापस पढ़ो_gicreg(ICH_LR7_EL2);
	हाल 8:
		वापस पढ़ो_gicreg(ICH_LR8_EL2);
	हाल 9:
		वापस पढ़ो_gicreg(ICH_LR9_EL2);
	हाल 10:
		वापस पढ़ो_gicreg(ICH_LR10_EL2);
	हाल 11:
		वापस पढ़ो_gicreg(ICH_LR11_EL2);
	हाल 12:
		वापस पढ़ो_gicreg(ICH_LR12_EL2);
	हाल 13:
		वापस पढ़ो_gicreg(ICH_LR13_EL2);
	हाल 14:
		वापस पढ़ो_gicreg(ICH_LR14_EL2);
	हाल 15:
		वापस पढ़ो_gicreg(ICH_LR15_EL2);
	पूर्ण

	unreachable();
पूर्ण

अटल व्योम __gic_v3_set_lr(u64 val, पूर्णांक lr)
अणु
	चयन (lr & 0xf) अणु
	हाल 0:
		ग_लिखो_gicreg(val, ICH_LR0_EL2);
		अवरोध;
	हाल 1:
		ग_लिखो_gicreg(val, ICH_LR1_EL2);
		अवरोध;
	हाल 2:
		ग_लिखो_gicreg(val, ICH_LR2_EL2);
		अवरोध;
	हाल 3:
		ग_लिखो_gicreg(val, ICH_LR3_EL2);
		अवरोध;
	हाल 4:
		ग_लिखो_gicreg(val, ICH_LR4_EL2);
		अवरोध;
	हाल 5:
		ग_लिखो_gicreg(val, ICH_LR5_EL2);
		अवरोध;
	हाल 6:
		ग_लिखो_gicreg(val, ICH_LR6_EL2);
		अवरोध;
	हाल 7:
		ग_लिखो_gicreg(val, ICH_LR7_EL2);
		अवरोध;
	हाल 8:
		ग_लिखो_gicreg(val, ICH_LR8_EL2);
		अवरोध;
	हाल 9:
		ग_लिखो_gicreg(val, ICH_LR9_EL2);
		अवरोध;
	हाल 10:
		ग_लिखो_gicreg(val, ICH_LR10_EL2);
		अवरोध;
	हाल 11:
		ग_लिखो_gicreg(val, ICH_LR11_EL2);
		अवरोध;
	हाल 12:
		ग_लिखो_gicreg(val, ICH_LR12_EL2);
		अवरोध;
	हाल 13:
		ग_लिखो_gicreg(val, ICH_LR13_EL2);
		अवरोध;
	हाल 14:
		ग_लिखो_gicreg(val, ICH_LR14_EL2);
		अवरोध;
	हाल 15:
		ग_लिखो_gicreg(val, ICH_LR15_EL2);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_ap0rn(u32 val, पूर्णांक n)
अणु
	चयन (n) अणु
	हाल 0:
		ग_लिखो_gicreg(val, ICH_AP0R0_EL2);
		अवरोध;
	हाल 1:
		ग_लिखो_gicreg(val, ICH_AP0R1_EL2);
		अवरोध;
	हाल 2:
		ग_लिखो_gicreg(val, ICH_AP0R2_EL2);
		अवरोध;
	हाल 3:
		ग_लिखो_gicreg(val, ICH_AP0R3_EL2);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_ap1rn(u32 val, पूर्णांक n)
अणु
	चयन (n) अणु
	हाल 0:
		ग_लिखो_gicreg(val, ICH_AP1R0_EL2);
		अवरोध;
	हाल 1:
		ग_लिखो_gicreg(val, ICH_AP1R1_EL2);
		अवरोध;
	हाल 2:
		ग_लिखो_gicreg(val, ICH_AP1R2_EL2);
		अवरोध;
	हाल 3:
		ग_लिखो_gicreg(val, ICH_AP1R3_EL2);
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 __vgic_v3_पढ़ो_ap0rn(पूर्णांक n)
अणु
	u32 val;

	चयन (n) अणु
	हाल 0:
		val = पढ़ो_gicreg(ICH_AP0R0_EL2);
		अवरोध;
	हाल 1:
		val = पढ़ो_gicreg(ICH_AP0R1_EL2);
		अवरोध;
	हाल 2:
		val = पढ़ो_gicreg(ICH_AP0R2_EL2);
		अवरोध;
	हाल 3:
		val = पढ़ो_gicreg(ICH_AP0R3_EL2);
		अवरोध;
	शेष:
		unreachable();
	पूर्ण

	वापस val;
पूर्ण

अटल u32 __vgic_v3_पढ़ो_ap1rn(पूर्णांक n)
अणु
	u32 val;

	चयन (n) अणु
	हाल 0:
		val = पढ़ो_gicreg(ICH_AP1R0_EL2);
		अवरोध;
	हाल 1:
		val = पढ़ो_gicreg(ICH_AP1R1_EL2);
		अवरोध;
	हाल 2:
		val = पढ़ो_gicreg(ICH_AP1R2_EL2);
		अवरोध;
	हाल 3:
		val = पढ़ो_gicreg(ICH_AP1R3_EL2);
		अवरोध;
	शेष:
		unreachable();
	पूर्ण

	वापस val;
पूर्ण

व्योम __vgic_v3_save_state(काष्ठा vgic_v3_cpu_अगर *cpu_अगर)
अणु
	u64 used_lrs = cpu_अगर->used_lrs;

	/*
	 * Make sure stores to the GIC via the memory mapped पूर्णांकerface
	 * are now visible to the प्रणाली रेजिस्टर पूर्णांकerface when पढ़ोing the
	 * LRs, and when पढ़ोing back the VMCR on non-VHE प्रणालीs.
	 */
	अगर (used_lrs || !has_vhe()) अणु
		अगर (!cpu_अगर->vgic_sre) अणु
			dsb(sy);
			isb();
		पूर्ण
	पूर्ण

	अगर (used_lrs || cpu_अगर->its_vpe.its_vm) अणु
		पूर्णांक i;
		u32 elrsr;

		elrsr = पढ़ो_gicreg(ICH_ELRSR_EL2);

		ग_लिखो_gicreg(cpu_अगर->vgic_hcr & ~ICH_HCR_EN, ICH_HCR_EL2);

		क्रम (i = 0; i < used_lrs; i++) अणु
			अगर (elrsr & (1 << i))
				cpu_अगर->vgic_lr[i] &= ~ICH_LR_STATE;
			अन्यथा
				cpu_अगर->vgic_lr[i] = __gic_v3_get_lr(i);

			__gic_v3_set_lr(0, i);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __vgic_v3_restore_state(काष्ठा vgic_v3_cpu_अगर *cpu_अगर)
अणु
	u64 used_lrs = cpu_अगर->used_lrs;
	पूर्णांक i;

	अगर (used_lrs || cpu_अगर->its_vpe.its_vm) अणु
		ग_लिखो_gicreg(cpu_अगर->vgic_hcr, ICH_HCR_EL2);

		क्रम (i = 0; i < used_lrs; i++)
			__gic_v3_set_lr(cpu_अगर->vgic_lr[i], i);
	पूर्ण

	/*
	 * Ensure that ग_लिखोs to the LRs, and on non-VHE प्रणालीs ensure that
	 * the ग_लिखो to the VMCR in __vgic_v3_activate_traps(), will have
	 * reached the (re)distributors. This ensure the guest will पढ़ो the
	 * correct values from the memory-mapped पूर्णांकerface.
	 */
	अगर (used_lrs || !has_vhe()) अणु
		अगर (!cpu_अगर->vgic_sre) अणु
			isb();
			dsb(sy);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __vgic_v3_activate_traps(काष्ठा vgic_v3_cpu_अगर *cpu_अगर)
अणु
	/*
	 * VFIQEn is RES1 अगर ICC_SRE_EL1.SRE is 1. This causes a
	 * Group0 पूर्णांकerrupt (as generated in GICv2 mode) to be
	 * delivered as a FIQ to the guest, with potentially fatal
	 * consequences. So we must make sure that ICC_SRE_EL1 has
	 * been actually programmed with the value we want beक्रमe
	 * starting to mess with the rest of the GIC, and VMCR_EL2 in
	 * particular.  This logic must be called beक्रमe
	 * __vgic_v3_restore_state().
	 */
	अगर (!cpu_अगर->vgic_sre) अणु
		ग_लिखो_gicreg(0, ICC_SRE_EL1);
		isb();
		ग_लिखो_gicreg(cpu_अगर->vgic_vmcr, ICH_VMCR_EL2);


		अगर (has_vhe()) अणु
			/*
			 * Ensure that the ग_लिखो to the VMCR will have reached
			 * the (re)distributors. This ensure the guest will
			 * पढ़ो the correct values from the memory-mapped
			 * पूर्णांकerface.
			 */
			isb();
			dsb(sy);
		पूर्ण
	पूर्ण

	/*
	 * Prevent the guest from touching the GIC प्रणाली रेजिस्टरs अगर
	 * SRE isn't enabled क्रम GICv3 emulation.
	 */
	ग_लिखो_gicreg(पढ़ो_gicreg(ICC_SRE_EL2) & ~ICC_SRE_EL2_ENABLE,
		     ICC_SRE_EL2);

	/*
	 * If we need to trap प्रणाली रेजिस्टरs, we must ग_लिखो
	 * ICH_HCR_EL2 anyway, even अगर no पूर्णांकerrupts are being
	 * injected,
	 */
	अगर (अटल_branch_unlikely(&vgic_v3_cpuअगर_trap) ||
	    cpu_अगर->its_vpe.its_vm)
		ग_लिखो_gicreg(cpu_अगर->vgic_hcr, ICH_HCR_EL2);
पूर्ण

व्योम __vgic_v3_deactivate_traps(काष्ठा vgic_v3_cpu_अगर *cpu_अगर)
अणु
	u64 val;

	अगर (!cpu_अगर->vgic_sre) अणु
		cpu_अगर->vgic_vmcr = पढ़ो_gicreg(ICH_VMCR_EL2);
	पूर्ण

	val = पढ़ो_gicreg(ICC_SRE_EL2);
	ग_लिखो_gicreg(val | ICC_SRE_EL2_ENABLE, ICC_SRE_EL2);

	अगर (!cpu_अगर->vgic_sre) अणु
		/* Make sure ENABLE is set at EL2 beक्रमe setting SRE at EL1 */
		isb();
		ग_लिखो_gicreg(1, ICC_SRE_EL1);
	पूर्ण

	/*
	 * If we were trapping प्रणाली रेजिस्टरs, we enabled the VGIC even अगर
	 * no पूर्णांकerrupts were being injected, and we disable it again here.
	 */
	अगर (अटल_branch_unlikely(&vgic_v3_cpuअगर_trap) ||
	    cpu_अगर->its_vpe.its_vm)
		ग_लिखो_gicreg(0, ICH_HCR_EL2);
पूर्ण

व्योम __vgic_v3_save_aprs(काष्ठा vgic_v3_cpu_अगर *cpu_अगर)
अणु
	u64 val;
	u32 nr_pre_bits;

	val = पढ़ो_gicreg(ICH_VTR_EL2);
	nr_pre_bits = vtr_to_nr_pre_bits(val);

	चयन (nr_pre_bits) अणु
	हाल 7:
		cpu_अगर->vgic_ap0r[3] = __vgic_v3_पढ़ो_ap0rn(3);
		cpu_अगर->vgic_ap0r[2] = __vgic_v3_पढ़ो_ap0rn(2);
		fallthrough;
	हाल 6:
		cpu_अगर->vgic_ap0r[1] = __vgic_v3_पढ़ो_ap0rn(1);
		fallthrough;
	शेष:
		cpu_अगर->vgic_ap0r[0] = __vgic_v3_पढ़ो_ap0rn(0);
	पूर्ण

	चयन (nr_pre_bits) अणु
	हाल 7:
		cpu_अगर->vgic_ap1r[3] = __vgic_v3_पढ़ो_ap1rn(3);
		cpu_अगर->vgic_ap1r[2] = __vgic_v3_पढ़ो_ap1rn(2);
		fallthrough;
	हाल 6:
		cpu_अगर->vgic_ap1r[1] = __vgic_v3_पढ़ो_ap1rn(1);
		fallthrough;
	शेष:
		cpu_अगर->vgic_ap1r[0] = __vgic_v3_पढ़ो_ap1rn(0);
	पूर्ण
पूर्ण

व्योम __vgic_v3_restore_aprs(काष्ठा vgic_v3_cpu_अगर *cpu_अगर)
अणु
	u64 val;
	u32 nr_pre_bits;

	val = पढ़ो_gicreg(ICH_VTR_EL2);
	nr_pre_bits = vtr_to_nr_pre_bits(val);

	चयन (nr_pre_bits) अणु
	हाल 7:
		__vgic_v3_ग_लिखो_ap0rn(cpu_अगर->vgic_ap0r[3], 3);
		__vgic_v3_ग_लिखो_ap0rn(cpu_अगर->vgic_ap0r[2], 2);
		fallthrough;
	हाल 6:
		__vgic_v3_ग_लिखो_ap0rn(cpu_अगर->vgic_ap0r[1], 1);
		fallthrough;
	शेष:
		__vgic_v3_ग_लिखो_ap0rn(cpu_अगर->vgic_ap0r[0], 0);
	पूर्ण

	चयन (nr_pre_bits) अणु
	हाल 7:
		__vgic_v3_ग_लिखो_ap1rn(cpu_अगर->vgic_ap1r[3], 3);
		__vgic_v3_ग_लिखो_ap1rn(cpu_अगर->vgic_ap1r[2], 2);
		fallthrough;
	हाल 6:
		__vgic_v3_ग_लिखो_ap1rn(cpu_अगर->vgic_ap1r[1], 1);
		fallthrough;
	शेष:
		__vgic_v3_ग_लिखो_ap1rn(cpu_अगर->vgic_ap1r[0], 0);
	पूर्ण
पूर्ण

व्योम __vgic_v3_init_lrs(व्योम)
अणु
	पूर्णांक max_lr_idx = vtr_to_max_lr_idx(पढ़ो_gicreg(ICH_VTR_EL2));
	पूर्णांक i;

	क्रम (i = 0; i <= max_lr_idx; i++)
		__gic_v3_set_lr(0, i);
पूर्ण

/*
 * Return the GIC CPU configuration:
 * - [31:0]  ICH_VTR_EL2
 * - [62:32] RES0
 * - [63]    MMIO (GICv2) capable
 */
u64 __vgic_v3_get_gic_config(व्योम)
अणु
	u64 val, sre = पढ़ो_gicreg(ICC_SRE_EL1);
	अचिन्हित दीर्घ flags = 0;

	/*
	 * To check whether we have a MMIO-based (GICv2 compatible)
	 * CPU पूर्णांकerface, we need to disable the प्रणाली रेजिस्टर
	 * view. To करो that safely, we have to prevent any पूर्णांकerrupt
	 * from firing (which would be deadly).
	 *
	 * Note that this only makes sense on VHE, as पूर्णांकerrupts are
	 * alपढ़ोy masked क्रम nVHE as part of the exception entry to
	 * EL2.
	 */
	अगर (has_vhe())
		flags = local_daअगर_save();

	/*
	 * Table 11-2 "Permitted ICC_SRE_ELx.SRE settings" indicates
	 * that to be able to set ICC_SRE_EL1.SRE to 0, all the
	 * पूर्णांकerrupt overrides must be set. You've got to love this.
	 */
	sysreg_clear_set(hcr_el2, 0, HCR_AMO | HCR_FMO | HCR_IMO);
	isb();
	ग_लिखो_gicreg(0, ICC_SRE_EL1);
	isb();

	val = पढ़ो_gicreg(ICC_SRE_EL1);

	ग_लिखो_gicreg(sre, ICC_SRE_EL1);
	isb();
	sysreg_clear_set(hcr_el2, HCR_AMO | HCR_FMO | HCR_IMO, 0);
	isb();

	अगर (has_vhe())
		local_daअगर_restore(flags);

	val  = (val & ICC_SRE_EL1_SRE) ? 0 : (1ULL << 63);
	val |= पढ़ो_gicreg(ICH_VTR_EL2);

	वापस val;
पूर्ण

u64 __vgic_v3_पढ़ो_vmcr(व्योम)
अणु
	वापस पढ़ो_gicreg(ICH_VMCR_EL2);
पूर्ण

व्योम __vgic_v3_ग_लिखो_vmcr(u32 vmcr)
अणु
	ग_लिखो_gicreg(vmcr, ICH_VMCR_EL2);
पूर्ण

अटल पूर्णांक __vgic_v3_bpr_min(व्योम)
अणु
	/* See Pseuकरोcode क्रम VPriorityGroup */
	वापस 8 - vtr_to_nr_pre_bits(पढ़ो_gicreg(ICH_VTR_EL2));
पूर्ण

अटल पूर्णांक __vgic_v3_get_group(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 esr = kvm_vcpu_get_esr(vcpu);
	u8 crm = (esr & ESR_ELx_SYS64_ISS_CRM_MASK) >> ESR_ELx_SYS64_ISS_CRM_SHIFT;

	वापस crm != 8;
पूर्ण

#घोषणा GICv3_IDLE_PRIORITY	0xff

अटल पूर्णांक __vgic_v3_highest_priority_lr(काष्ठा kvm_vcpu *vcpu, u32 vmcr,
					 u64 *lr_val)
अणु
	अचिन्हित पूर्णांक used_lrs = vcpu->arch.vgic_cpu.vgic_v3.used_lrs;
	u8 priority = GICv3_IDLE_PRIORITY;
	पूर्णांक i, lr = -1;

	क्रम (i = 0; i < used_lrs; i++) अणु
		u64 val = __gic_v3_get_lr(i);
		u8 lr_prio = (val & ICH_LR_PRIORITY_MASK) >> ICH_LR_PRIORITY_SHIFT;

		/* Not pending in the state? */
		अगर ((val & ICH_LR_STATE) != ICH_LR_PENDING_BIT)
			जारी;

		/* Group-0 पूर्णांकerrupt, but Group-0 disabled? */
		अगर (!(val & ICH_LR_GROUP) && !(vmcr & ICH_VMCR_ENG0_MASK))
			जारी;

		/* Group-1 पूर्णांकerrupt, but Group-1 disabled? */
		अगर ((val & ICH_LR_GROUP) && !(vmcr & ICH_VMCR_ENG1_MASK))
			जारी;

		/* Not the highest priority? */
		अगर (lr_prio >= priority)
			जारी;

		/* This is a candidate */
		priority = lr_prio;
		*lr_val = val;
		lr = i;
	पूर्ण

	अगर (lr == -1)
		*lr_val = ICC_IAR1_EL1_SPURIOUS;

	वापस lr;
पूर्ण

अटल पूर्णांक __vgic_v3_find_active_lr(काष्ठा kvm_vcpu *vcpu, पूर्णांक पूर्णांकid,
				    u64 *lr_val)
अणु
	अचिन्हित पूर्णांक used_lrs = vcpu->arch.vgic_cpu.vgic_v3.used_lrs;
	पूर्णांक i;

	क्रम (i = 0; i < used_lrs; i++) अणु
		u64 val = __gic_v3_get_lr(i);

		अगर ((val & ICH_LR_VIRTUAL_ID_MASK) == पूर्णांकid &&
		    (val & ICH_LR_ACTIVE_BIT)) अणु
			*lr_val = val;
			वापस i;
		पूर्ण
	पूर्ण

	*lr_val = ICC_IAR1_EL1_SPURIOUS;
	वापस -1;
पूर्ण

अटल पूर्णांक __vgic_v3_get_highest_active_priority(व्योम)
अणु
	u8 nr_apr_regs = vtr_to_nr_apr_regs(पढ़ो_gicreg(ICH_VTR_EL2));
	u32 hap = 0;
	पूर्णांक i;

	क्रम (i = 0; i < nr_apr_regs; i++) अणु
		u32 val;

		/*
		 * The ICH_AP0Rn_EL2 and ICH_AP1Rn_EL2 रेजिस्टरs
		 * contain the active priority levels क्रम this VCPU
		 * क्रम the maximum number of supported priority
		 * levels, and we वापस the full priority level only
		 * अगर the BPR is programmed to its minimum, otherwise
		 * we वापस a combination of the priority level and
		 * subpriority, as determined by the setting of the
		 * BPR, but without the full subpriority.
		 */
		val  = __vgic_v3_पढ़ो_ap0rn(i);
		val |= __vgic_v3_पढ़ो_ap1rn(i);
		अगर (!val) अणु
			hap += 32;
			जारी;
		पूर्ण

		वापस (hap + __ffs(val)) << __vgic_v3_bpr_min();
	पूर्ण

	वापस GICv3_IDLE_PRIORITY;
पूर्ण

अटल अचिन्हित पूर्णांक __vgic_v3_get_bpr0(u32 vmcr)
अणु
	वापस (vmcr & ICH_VMCR_BPR0_MASK) >> ICH_VMCR_BPR0_SHIFT;
पूर्ण

अटल अचिन्हित पूर्णांक __vgic_v3_get_bpr1(u32 vmcr)
अणु
	अचिन्हित पूर्णांक bpr;

	अगर (vmcr & ICH_VMCR_CBPR_MASK) अणु
		bpr = __vgic_v3_get_bpr0(vmcr);
		अगर (bpr < 7)
			bpr++;
	पूर्ण अन्यथा अणु
		bpr = (vmcr & ICH_VMCR_BPR1_MASK) >> ICH_VMCR_BPR1_SHIFT;
	पूर्ण

	वापस bpr;
पूर्ण

/*
 * Convert a priority to a preemption level, taking the relevant BPR
 * पूर्णांकo account by zeroing the sub-priority bits.
 */
अटल u8 __vgic_v3_pri_to_pre(u8 pri, u32 vmcr, पूर्णांक grp)
अणु
	अचिन्हित पूर्णांक bpr;

	अगर (!grp)
		bpr = __vgic_v3_get_bpr0(vmcr) + 1;
	अन्यथा
		bpr = __vgic_v3_get_bpr1(vmcr);

	वापस pri & (GENMASK(7, 0) << bpr);
पूर्ण

/*
 * The priority value is independent of any of the BPR values, so we
 * normalize it using the minimal BPR value. This guarantees that no
 * matter what the guest करोes with its BPR, we can always set/get the
 * same value of a priority.
 */
अटल व्योम __vgic_v3_set_active_priority(u8 pri, u32 vmcr, पूर्णांक grp)
अणु
	u8 pre, ap;
	u32 val;
	पूर्णांक apr;

	pre = __vgic_v3_pri_to_pre(pri, vmcr, grp);
	ap = pre >> __vgic_v3_bpr_min();
	apr = ap / 32;

	अगर (!grp) अणु
		val = __vgic_v3_पढ़ो_ap0rn(apr);
		__vgic_v3_ग_लिखो_ap0rn(val | BIT(ap % 32), apr);
	पूर्ण अन्यथा अणु
		val = __vgic_v3_पढ़ो_ap1rn(apr);
		__vgic_v3_ग_लिखो_ap1rn(val | BIT(ap % 32), apr);
	पूर्ण
पूर्ण

अटल पूर्णांक __vgic_v3_clear_highest_active_priority(व्योम)
अणु
	u8 nr_apr_regs = vtr_to_nr_apr_regs(पढ़ो_gicreg(ICH_VTR_EL2));
	u32 hap = 0;
	पूर्णांक i;

	क्रम (i = 0; i < nr_apr_regs; i++) अणु
		u32 ap0, ap1;
		पूर्णांक c0, c1;

		ap0 = __vgic_v3_पढ़ो_ap0rn(i);
		ap1 = __vgic_v3_पढ़ो_ap1rn(i);
		अगर (!ap0 && !ap1) अणु
			hap += 32;
			जारी;
		पूर्ण

		c0 = ap0 ? __ffs(ap0) : 32;
		c1 = ap1 ? __ffs(ap1) : 32;

		/* Always clear the LSB, which is the highest priority */
		अगर (c0 < c1) अणु
			ap0 &= ~BIT(c0);
			__vgic_v3_ग_लिखो_ap0rn(ap0, i);
			hap += c0;
		पूर्ण अन्यथा अणु
			ap1 &= ~BIT(c1);
			__vgic_v3_ग_लिखो_ap1rn(ap1, i);
			hap += c1;
		पूर्ण

		/* Rescale to 8 bits of priority */
		वापस hap << __vgic_v3_bpr_min();
	पूर्ण

	वापस GICv3_IDLE_PRIORITY;
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_iar(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u64 lr_val;
	u8 lr_prio, pmr;
	पूर्णांक lr, grp;

	grp = __vgic_v3_get_group(vcpu);

	lr = __vgic_v3_highest_priority_lr(vcpu, vmcr, &lr_val);
	अगर (lr < 0)
		जाओ spurious;

	अगर (grp != !!(lr_val & ICH_LR_GROUP))
		जाओ spurious;

	pmr = (vmcr & ICH_VMCR_PMR_MASK) >> ICH_VMCR_PMR_SHIFT;
	lr_prio = (lr_val & ICH_LR_PRIORITY_MASK) >> ICH_LR_PRIORITY_SHIFT;
	अगर (pmr <= lr_prio)
		जाओ spurious;

	अगर (__vgic_v3_get_highest_active_priority() <= __vgic_v3_pri_to_pre(lr_prio, vmcr, grp))
		जाओ spurious;

	lr_val &= ~ICH_LR_STATE;
	/* No active state क्रम LPIs */
	अगर ((lr_val & ICH_LR_VIRTUAL_ID_MASK) <= VGIC_MAX_SPI)
		lr_val |= ICH_LR_ACTIVE_BIT;
	__gic_v3_set_lr(lr_val, lr);
	__vgic_v3_set_active_priority(lr_prio, vmcr, grp);
	vcpu_set_reg(vcpu, rt, lr_val & ICH_LR_VIRTUAL_ID_MASK);
	वापस;

spurious:
	vcpu_set_reg(vcpu, rt, ICC_IAR1_EL1_SPURIOUS);
पूर्ण

अटल व्योम __vgic_v3_clear_active_lr(पूर्णांक lr, u64 lr_val)
अणु
	lr_val &= ~ICH_LR_ACTIVE_BIT;
	अगर (lr_val & ICH_LR_HW) अणु
		u32 pid;

		pid = (lr_val & ICH_LR_PHYS_ID_MASK) >> ICH_LR_PHYS_ID_SHIFT;
		gic_ग_लिखो_dir(pid);
	पूर्ण

	__gic_v3_set_lr(lr_val, lr);
पूर्ण

अटल व्योम __vgic_v3_bump_eoicount(व्योम)
अणु
	u32 hcr;

	hcr = पढ़ो_gicreg(ICH_HCR_EL2);
	hcr += 1 << ICH_HCR_EOIcount_SHIFT;
	ग_लिखो_gicreg(hcr, ICH_HCR_EL2);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_dir(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u32 vid = vcpu_get_reg(vcpu, rt);
	u64 lr_val;
	पूर्णांक lr;

	/* EOImode == 0, nothing to be करोne here */
	अगर (!(vmcr & ICH_VMCR_EOIM_MASK))
		वापस;

	/* No deactivate to be perक्रमmed on an LPI */
	अगर (vid >= VGIC_MIN_LPI)
		वापस;

	lr = __vgic_v3_find_active_lr(vcpu, vid, &lr_val);
	अगर (lr == -1) अणु
		__vgic_v3_bump_eoicount();
		वापस;
	पूर्ण

	__vgic_v3_clear_active_lr(lr, lr_val);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_eoir(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u32 vid = vcpu_get_reg(vcpu, rt);
	u64 lr_val;
	u8 lr_prio, act_prio;
	पूर्णांक lr, grp;

	grp = __vgic_v3_get_group(vcpu);

	/* Drop priority in any हाल */
	act_prio = __vgic_v3_clear_highest_active_priority();

	/* If EOIing an LPI, no deactivate to be perक्रमmed */
	अगर (vid >= VGIC_MIN_LPI)
		वापस;

	/* EOImode == 1, nothing to be करोne here */
	अगर (vmcr & ICH_VMCR_EOIM_MASK)
		वापस;

	lr = __vgic_v3_find_active_lr(vcpu, vid, &lr_val);
	अगर (lr == -1) अणु
		__vgic_v3_bump_eoicount();
		वापस;
	पूर्ण

	lr_prio = (lr_val & ICH_LR_PRIORITY_MASK) >> ICH_LR_PRIORITY_SHIFT;

	/* If priorities or group करो not match, the guest has fscked-up. */
	अगर (grp != !!(lr_val & ICH_LR_GROUP) ||
	    __vgic_v3_pri_to_pre(lr_prio, vmcr, grp) != act_prio)
		वापस;

	/* Let's now perक्रमm the deactivation */
	__vgic_v3_clear_active_lr(lr, lr_val);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_igrpen0(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	vcpu_set_reg(vcpu, rt, !!(vmcr & ICH_VMCR_ENG0_MASK));
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_igrpen1(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	vcpu_set_reg(vcpu, rt, !!(vmcr & ICH_VMCR_ENG1_MASK));
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_igrpen0(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u64 val = vcpu_get_reg(vcpu, rt);

	अगर (val & 1)
		vmcr |= ICH_VMCR_ENG0_MASK;
	अन्यथा
		vmcr &= ~ICH_VMCR_ENG0_MASK;

	__vgic_v3_ग_लिखो_vmcr(vmcr);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_igrpen1(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u64 val = vcpu_get_reg(vcpu, rt);

	अगर (val & 1)
		vmcr |= ICH_VMCR_ENG1_MASK;
	अन्यथा
		vmcr &= ~ICH_VMCR_ENG1_MASK;

	__vgic_v3_ग_लिखो_vmcr(vmcr);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_bpr0(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	vcpu_set_reg(vcpu, rt, __vgic_v3_get_bpr0(vmcr));
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_bpr1(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	vcpu_set_reg(vcpu, rt, __vgic_v3_get_bpr1(vmcr));
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_bpr0(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u64 val = vcpu_get_reg(vcpu, rt);
	u8 bpr_min = __vgic_v3_bpr_min() - 1;

	/* Enक्रमce BPR limiting */
	अगर (val < bpr_min)
		val = bpr_min;

	val <<= ICH_VMCR_BPR0_SHIFT;
	val &= ICH_VMCR_BPR0_MASK;
	vmcr &= ~ICH_VMCR_BPR0_MASK;
	vmcr |= val;

	__vgic_v3_ग_लिखो_vmcr(vmcr);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_bpr1(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u64 val = vcpu_get_reg(vcpu, rt);
	u8 bpr_min = __vgic_v3_bpr_min();

	अगर (vmcr & ICH_VMCR_CBPR_MASK)
		वापस;

	/* Enक्रमce BPR limiting */
	अगर (val < bpr_min)
		val = bpr_min;

	val <<= ICH_VMCR_BPR1_SHIFT;
	val &= ICH_VMCR_BPR1_MASK;
	vmcr &= ~ICH_VMCR_BPR1_MASK;
	vmcr |= val;

	__vgic_v3_ग_लिखो_vmcr(vmcr);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_apxrn(काष्ठा kvm_vcpu *vcpu, पूर्णांक rt, पूर्णांक n)
अणु
	u32 val;

	अगर (!__vgic_v3_get_group(vcpu))
		val = __vgic_v3_पढ़ो_ap0rn(n);
	अन्यथा
		val = __vgic_v3_पढ़ो_ap1rn(n);

	vcpu_set_reg(vcpu, rt, val);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_apxrn(काष्ठा kvm_vcpu *vcpu, पूर्णांक rt, पूर्णांक n)
अणु
	u32 val = vcpu_get_reg(vcpu, rt);

	अगर (!__vgic_v3_get_group(vcpu))
		__vgic_v3_ग_लिखो_ap0rn(val, n);
	अन्यथा
		__vgic_v3_ग_लिखो_ap1rn(val, n);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_apxr0(काष्ठा kvm_vcpu *vcpu,
					    u32 vmcr, पूर्णांक rt)
अणु
	__vgic_v3_पढ़ो_apxrn(vcpu, rt, 0);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_apxr1(काष्ठा kvm_vcpu *vcpu,
					    u32 vmcr, पूर्णांक rt)
अणु
	__vgic_v3_पढ़ो_apxrn(vcpu, rt, 1);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_apxr2(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	__vgic_v3_पढ़ो_apxrn(vcpu, rt, 2);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_apxr3(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	__vgic_v3_पढ़ो_apxrn(vcpu, rt, 3);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_apxr0(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	__vgic_v3_ग_लिखो_apxrn(vcpu, rt, 0);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_apxr1(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	__vgic_v3_ग_लिखो_apxrn(vcpu, rt, 1);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_apxr2(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	__vgic_v3_ग_लिखो_apxrn(vcpu, rt, 2);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_apxr3(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	__vgic_v3_ग_लिखो_apxrn(vcpu, rt, 3);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_hppir(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u64 lr_val;
	पूर्णांक lr, lr_grp, grp;

	grp = __vgic_v3_get_group(vcpu);

	lr = __vgic_v3_highest_priority_lr(vcpu, vmcr, &lr_val);
	अगर (lr == -1)
		जाओ spurious;

	lr_grp = !!(lr_val & ICH_LR_GROUP);
	अगर (lr_grp != grp)
		lr_val = ICC_IAR1_EL1_SPURIOUS;

spurious:
	vcpu_set_reg(vcpu, rt, lr_val & ICH_LR_VIRTUAL_ID_MASK);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_pmr(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	vmcr &= ICH_VMCR_PMR_MASK;
	vmcr >>= ICH_VMCR_PMR_SHIFT;
	vcpu_set_reg(vcpu, rt, vmcr);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_pmr(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u32 val = vcpu_get_reg(vcpu, rt);

	val <<= ICH_VMCR_PMR_SHIFT;
	val &= ICH_VMCR_PMR_MASK;
	vmcr &= ~ICH_VMCR_PMR_MASK;
	vmcr |= val;

	ग_लिखो_gicreg(vmcr, ICH_VMCR_EL2);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_rpr(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u32 val = __vgic_v3_get_highest_active_priority();
	vcpu_set_reg(vcpu, rt, val);
पूर्ण

अटल व्योम __vgic_v3_पढ़ो_ctlr(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u32 vtr, val;

	vtr = पढ़ो_gicreg(ICH_VTR_EL2);
	/* PRIbits */
	val = ((vtr >> 29) & 7) << ICC_CTLR_EL1_PRI_BITS_SHIFT;
	/* IDbits */
	val |= ((vtr >> 23) & 7) << ICC_CTLR_EL1_ID_BITS_SHIFT;
	/* SEIS */
	val |= ((vtr >> 22) & 1) << ICC_CTLR_EL1_SEIS_SHIFT;
	/* A3V */
	val |= ((vtr >> 21) & 1) << ICC_CTLR_EL1_A3V_SHIFT;
	/* EOImode */
	val |= ((vmcr & ICH_VMCR_EOIM_MASK) >> ICH_VMCR_EOIM_SHIFT) << ICC_CTLR_EL1_EOImode_SHIFT;
	/* CBPR */
	val |= (vmcr & ICH_VMCR_CBPR_MASK) >> ICH_VMCR_CBPR_SHIFT;

	vcpu_set_reg(vcpu, rt, val);
पूर्ण

अटल व्योम __vgic_v3_ग_लिखो_ctlr(काष्ठा kvm_vcpu *vcpu, u32 vmcr, पूर्णांक rt)
अणु
	u32 val = vcpu_get_reg(vcpu, rt);

	अगर (val & ICC_CTLR_EL1_CBPR_MASK)
		vmcr |= ICH_VMCR_CBPR_MASK;
	अन्यथा
		vmcr &= ~ICH_VMCR_CBPR_MASK;

	अगर (val & ICC_CTLR_EL1_EOImode_MASK)
		vmcr |= ICH_VMCR_EOIM_MASK;
	अन्यथा
		vmcr &= ~ICH_VMCR_EOIM_MASK;

	ग_लिखो_gicreg(vmcr, ICH_VMCR_EL2);
पूर्ण

पूर्णांक __vgic_v3_perक्रमm_cpuअगर_access(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rt;
	u32 esr;
	u32 vmcr;
	व्योम (*fn)(काष्ठा kvm_vcpu *, u32, पूर्णांक);
	bool is_पढ़ो;
	u32 sysreg;

	esr = kvm_vcpu_get_esr(vcpu);
	अगर (vcpu_mode_is_32bit(vcpu)) अणु
		अगर (!kvm_condition_valid(vcpu)) अणु
			__kvm_skip_instr(vcpu);
			वापस 1;
		पूर्ण

		sysreg = esr_cp15_to_sysreg(esr);
	पूर्ण अन्यथा अणु
		sysreg = esr_sys64_to_sysreg(esr);
	पूर्ण

	is_पढ़ो = (esr & ESR_ELx_SYS64_ISS_सूची_MASK) == ESR_ELx_SYS64_ISS_सूची_READ;

	चयन (sysreg) अणु
	हाल SYS_ICC_IAR0_EL1:
	हाल SYS_ICC_IAR1_EL1:
		अगर (unlikely(!is_पढ़ो))
			वापस 0;
		fn = __vgic_v3_पढ़ो_iar;
		अवरोध;
	हाल SYS_ICC_EOIR0_EL1:
	हाल SYS_ICC_EOIR1_EL1:
		अगर (unlikely(is_पढ़ो))
			वापस 0;
		fn = __vgic_v3_ग_लिखो_eoir;
		अवरोध;
	हाल SYS_ICC_IGRPEN1_EL1:
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_igrpen1;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_igrpen1;
		अवरोध;
	हाल SYS_ICC_BPR1_EL1:
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_bpr1;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_bpr1;
		अवरोध;
	हाल SYS_ICC_AP0Rn_EL1(0):
	हाल SYS_ICC_AP1Rn_EL1(0):
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_apxr0;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_apxr0;
		अवरोध;
	हाल SYS_ICC_AP0Rn_EL1(1):
	हाल SYS_ICC_AP1Rn_EL1(1):
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_apxr1;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_apxr1;
		अवरोध;
	हाल SYS_ICC_AP0Rn_EL1(2):
	हाल SYS_ICC_AP1Rn_EL1(2):
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_apxr2;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_apxr2;
		अवरोध;
	हाल SYS_ICC_AP0Rn_EL1(3):
	हाल SYS_ICC_AP1Rn_EL1(3):
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_apxr3;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_apxr3;
		अवरोध;
	हाल SYS_ICC_HPPIR0_EL1:
	हाल SYS_ICC_HPPIR1_EL1:
		अगर (unlikely(!is_पढ़ो))
			वापस 0;
		fn = __vgic_v3_पढ़ो_hppir;
		अवरोध;
	हाल SYS_ICC_IGRPEN0_EL1:
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_igrpen0;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_igrpen0;
		अवरोध;
	हाल SYS_ICC_BPR0_EL1:
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_bpr0;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_bpr0;
		अवरोध;
	हाल SYS_ICC_सूची_EL1:
		अगर (unlikely(is_पढ़ो))
			वापस 0;
		fn = __vgic_v3_ग_लिखो_dir;
		अवरोध;
	हाल SYS_ICC_RPR_EL1:
		अगर (unlikely(!is_पढ़ो))
			वापस 0;
		fn = __vgic_v3_पढ़ो_rpr;
		अवरोध;
	हाल SYS_ICC_CTLR_EL1:
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_ctlr;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_ctlr;
		अवरोध;
	हाल SYS_ICC_PMR_EL1:
		अगर (is_पढ़ो)
			fn = __vgic_v3_पढ़ो_pmr;
		अन्यथा
			fn = __vgic_v3_ग_लिखो_pmr;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	vmcr = __vgic_v3_पढ़ो_vmcr();
	rt = kvm_vcpu_sys_get_rt(vcpu);
	fn(vcpu, vmcr, rt);

	__kvm_skip_instr(vcpu);

	वापस 1;
पूर्ण
