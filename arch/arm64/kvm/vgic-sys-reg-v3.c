<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VGIC प्रणाली रेजिस्टरs handling functions क्रम AArch64 mode
 */

#समावेश <linux/irqchip/arm-gic-v3.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश "vgic/vgic.h"
#समावेश "sys_regs.h"

अटल bool access_gic_ctlr(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			    स्थिर काष्ठा sys_reg_desc *r)
अणु
	u32 host_pri_bits, host_id_bits, host_seis, host_a3v, seis, a3v;
	काष्ठा vgic_cpu *vgic_v3_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_vmcr vmcr;
	u64 val;

	vgic_get_vmcr(vcpu, &vmcr);
	अगर (p->is_ग_लिखो) अणु
		val = p->regval;

		/*
		 * Disallow restoring VM state अगर not supported by this
		 * hardware.
		 */
		host_pri_bits = ((val & ICC_CTLR_EL1_PRI_BITS_MASK) >>
				 ICC_CTLR_EL1_PRI_BITS_SHIFT) + 1;
		अगर (host_pri_bits > vgic_v3_cpu->num_pri_bits)
			वापस false;

		vgic_v3_cpu->num_pri_bits = host_pri_bits;

		host_id_bits = (val & ICC_CTLR_EL1_ID_BITS_MASK) >>
				ICC_CTLR_EL1_ID_BITS_SHIFT;
		अगर (host_id_bits > vgic_v3_cpu->num_id_bits)
			वापस false;

		vgic_v3_cpu->num_id_bits = host_id_bits;

		host_seis = ((kvm_vgic_global_state.ich_vtr_el2 &
			     ICH_VTR_SEIS_MASK) >> ICH_VTR_SEIS_SHIFT);
		seis = (val & ICC_CTLR_EL1_SEIS_MASK) >>
			ICC_CTLR_EL1_SEIS_SHIFT;
		अगर (host_seis != seis)
			वापस false;

		host_a3v = ((kvm_vgic_global_state.ich_vtr_el2 &
			    ICH_VTR_A3V_MASK) >> ICH_VTR_A3V_SHIFT);
		a3v = (val & ICC_CTLR_EL1_A3V_MASK) >> ICC_CTLR_EL1_A3V_SHIFT;
		अगर (host_a3v != a3v)
			वापस false;

		/*
		 * Here set VMCR.CTLR in ICC_CTLR_EL1 layout.
		 * The vgic_set_vmcr() will convert to ICH_VMCR layout.
		 */
		vmcr.cbpr = (val & ICC_CTLR_EL1_CBPR_MASK) >> ICC_CTLR_EL1_CBPR_SHIFT;
		vmcr.eoim = (val & ICC_CTLR_EL1_EOImode_MASK) >> ICC_CTLR_EL1_EOImode_SHIFT;
		vgic_set_vmcr(vcpu, &vmcr);
	पूर्ण अन्यथा अणु
		val = 0;
		val |= (vgic_v3_cpu->num_pri_bits - 1) <<
			ICC_CTLR_EL1_PRI_BITS_SHIFT;
		val |= vgic_v3_cpu->num_id_bits << ICC_CTLR_EL1_ID_BITS_SHIFT;
		val |= ((kvm_vgic_global_state.ich_vtr_el2 &
			ICH_VTR_SEIS_MASK) >> ICH_VTR_SEIS_SHIFT) <<
			ICC_CTLR_EL1_SEIS_SHIFT;
		val |= ((kvm_vgic_global_state.ich_vtr_el2 &
			ICH_VTR_A3V_MASK) >> ICH_VTR_A3V_SHIFT) <<
			ICC_CTLR_EL1_A3V_SHIFT;
		/*
		 * The VMCR.CTLR value is in ICC_CTLR_EL1 layout.
		 * Extract it directly using ICC_CTLR_EL1 reg definitions.
		 */
		val |= (vmcr.cbpr << ICC_CTLR_EL1_CBPR_SHIFT) & ICC_CTLR_EL1_CBPR_MASK;
		val |= (vmcr.eoim << ICC_CTLR_EL1_EOImode_SHIFT) & ICC_CTLR_EL1_EOImode_MASK;

		p->regval = val;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_gic_pmr(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			   स्थिर काष्ठा sys_reg_desc *r)
अणु
	काष्ठा vgic_vmcr vmcr;

	vgic_get_vmcr(vcpu, &vmcr);
	अगर (p->is_ग_लिखो) अणु
		vmcr.pmr = (p->regval & ICC_PMR_EL1_MASK) >> ICC_PMR_EL1_SHIFT;
		vgic_set_vmcr(vcpu, &vmcr);
	पूर्ण अन्यथा अणु
		p->regval = (vmcr.pmr << ICC_PMR_EL1_SHIFT) & ICC_PMR_EL1_MASK;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_gic_bpr0(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			    स्थिर काष्ठा sys_reg_desc *r)
अणु
	काष्ठा vgic_vmcr vmcr;

	vgic_get_vmcr(vcpu, &vmcr);
	अगर (p->is_ग_लिखो) अणु
		vmcr.bpr = (p->regval & ICC_BPR0_EL1_MASK) >>
			    ICC_BPR0_EL1_SHIFT;
		vgic_set_vmcr(vcpu, &vmcr);
	पूर्ण अन्यथा अणु
		p->regval = (vmcr.bpr << ICC_BPR0_EL1_SHIFT) &
			     ICC_BPR0_EL1_MASK;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_gic_bpr1(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			    स्थिर काष्ठा sys_reg_desc *r)
अणु
	काष्ठा vgic_vmcr vmcr;

	अगर (!p->is_ग_लिखो)
		p->regval = 0;

	vgic_get_vmcr(vcpu, &vmcr);
	अगर (!vmcr.cbpr) अणु
		अगर (p->is_ग_लिखो) अणु
			vmcr.abpr = (p->regval & ICC_BPR1_EL1_MASK) >>
				     ICC_BPR1_EL1_SHIFT;
			vgic_set_vmcr(vcpu, &vmcr);
		पूर्ण अन्यथा अणु
			p->regval = (vmcr.abpr << ICC_BPR1_EL1_SHIFT) &
				     ICC_BPR1_EL1_MASK;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!p->is_ग_लिखो)
			p->regval = min((vmcr.bpr + 1), 7U);
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_gic_grpen0(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			      स्थिर काष्ठा sys_reg_desc *r)
अणु
	काष्ठा vgic_vmcr vmcr;

	vgic_get_vmcr(vcpu, &vmcr);
	अगर (p->is_ग_लिखो) अणु
		vmcr.grpen0 = (p->regval & ICC_IGRPEN0_EL1_MASK) >>
			       ICC_IGRPEN0_EL1_SHIFT;
		vgic_set_vmcr(vcpu, &vmcr);
	पूर्ण अन्यथा अणु
		p->regval = (vmcr.grpen0 << ICC_IGRPEN0_EL1_SHIFT) &
			     ICC_IGRPEN0_EL1_MASK;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_gic_grpen1(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			      स्थिर काष्ठा sys_reg_desc *r)
अणु
	काष्ठा vgic_vmcr vmcr;

	vgic_get_vmcr(vcpu, &vmcr);
	अगर (p->is_ग_लिखो) अणु
		vmcr.grpen1 = (p->regval & ICC_IGRPEN1_EL1_MASK) >>
			       ICC_IGRPEN1_EL1_SHIFT;
		vgic_set_vmcr(vcpu, &vmcr);
	पूर्ण अन्यथा अणु
		p->regval = (vmcr.grpen1 << ICC_IGRPEN1_EL1_SHIFT) &
			     ICC_IGRPEN1_EL1_MASK;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम vgic_v3_access_apr_reg(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा sys_reg_params *p, u8 apr, u8 idx)
अणु
	काष्ठा vgic_v3_cpu_अगर *vgicv3 = &vcpu->arch.vgic_cpu.vgic_v3;
	uपूर्णांक32_t *ap_reg;

	अगर (apr)
		ap_reg = &vgicv3->vgic_ap1r[idx];
	अन्यथा
		ap_reg = &vgicv3->vgic_ap0r[idx];

	अगर (p->is_ग_लिखो)
		*ap_reg = p->regval;
	अन्यथा
		p->regval = *ap_reg;
पूर्ण

अटल bool access_gic_aprn(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			    स्थिर काष्ठा sys_reg_desc *r, u8 apr)
अणु
	u8 idx = r->Op2 & 3;

	अगर (idx > vgic_v3_max_apr_idx(vcpu))
		जाओ err;

	vgic_v3_access_apr_reg(vcpu, p, apr, idx);
	वापस true;
err:
	अगर (!p->is_ग_लिखो)
		p->regval = 0;

	वापस false;
पूर्ण

अटल bool access_gic_ap0r(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			    स्थिर काष्ठा sys_reg_desc *r)

अणु
	वापस access_gic_aprn(vcpu, p, r, 0);
पूर्ण

अटल bool access_gic_ap1r(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			    स्थिर काष्ठा sys_reg_desc *r)
अणु
	वापस access_gic_aprn(vcpu, p, r, 1);
पूर्ण

अटल bool access_gic_sre(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			   स्थिर काष्ठा sys_reg_desc *r)
अणु
	काष्ठा vgic_v3_cpu_अगर *vgicv3 = &vcpu->arch.vgic_cpu.vgic_v3;

	/* Validate SRE bit */
	अगर (p->is_ग_लिखो) अणु
		अगर (!(p->regval & ICC_SRE_EL1_SRE))
			वापस false;
	पूर्ण अन्यथा अणु
		p->regval = vgicv3->vgic_sre;
	पूर्ण

	वापस true;
पूर्ण
अटल स्थिर काष्ठा sys_reg_desc gic_v3_icc_reg_descs[] = अणु
	अणु SYS_DESC(SYS_ICC_PMR_EL1), access_gic_pmr पूर्ण,
	अणु SYS_DESC(SYS_ICC_BPR0_EL1), access_gic_bpr0 पूर्ण,
	अणु SYS_DESC(SYS_ICC_AP0R0_EL1), access_gic_ap0r पूर्ण,
	अणु SYS_DESC(SYS_ICC_AP0R1_EL1), access_gic_ap0r पूर्ण,
	अणु SYS_DESC(SYS_ICC_AP0R2_EL1), access_gic_ap0r पूर्ण,
	अणु SYS_DESC(SYS_ICC_AP0R3_EL1), access_gic_ap0r पूर्ण,
	अणु SYS_DESC(SYS_ICC_AP1R0_EL1), access_gic_ap1r पूर्ण,
	अणु SYS_DESC(SYS_ICC_AP1R1_EL1), access_gic_ap1r पूर्ण,
	अणु SYS_DESC(SYS_ICC_AP1R2_EL1), access_gic_ap1r पूर्ण,
	अणु SYS_DESC(SYS_ICC_AP1R3_EL1), access_gic_ap1r पूर्ण,
	अणु SYS_DESC(SYS_ICC_BPR1_EL1), access_gic_bpr1 पूर्ण,
	अणु SYS_DESC(SYS_ICC_CTLR_EL1), access_gic_ctlr पूर्ण,
	अणु SYS_DESC(SYS_ICC_SRE_EL1), access_gic_sre पूर्ण,
	अणु SYS_DESC(SYS_ICC_IGRPEN0_EL1), access_gic_grpen0 पूर्ण,
	अणु SYS_DESC(SYS_ICC_IGRPEN1_EL1), access_gic_grpen1 पूर्ण,
पूर्ण;

पूर्णांक vgic_v3_has_cpu_sysregs_attr(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो, u64 id,
				u64 *reg)
अणु
	काष्ठा sys_reg_params params;
	u64 sysreg = (id & KVM_DEV_ARM_VGIC_SYSREG_MASK) | KVM_REG_SIZE_U64;

	params.regval = *reg;
	params.is_ग_लिखो = is_ग_लिखो;

	अगर (find_reg_by_id(sysreg, &params, gic_v3_icc_reg_descs,
			      ARRAY_SIZE(gic_v3_icc_reg_descs)))
		वापस 0;

	वापस -ENXIO;
पूर्ण

पूर्णांक vgic_v3_cpu_sysregs_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो, u64 id,
				u64 *reg)
अणु
	काष्ठा sys_reg_params params;
	स्थिर काष्ठा sys_reg_desc *r;
	u64 sysreg = (id & KVM_DEV_ARM_VGIC_SYSREG_MASK) | KVM_REG_SIZE_U64;

	अगर (is_ग_लिखो)
		params.regval = *reg;
	params.is_ग_लिखो = is_ग_लिखो;

	r = find_reg_by_id(sysreg, &params, gic_v3_icc_reg_descs,
			   ARRAY_SIZE(gic_v3_icc_reg_descs));
	अगर (!r)
		वापस -ENXIO;

	अगर (!r->access(vcpu, &params, r))
		वापस -EINVAL;

	अगर (!is_ग_लिखो)
		*reg = params.regval;

	वापस 0;
पूर्ण
