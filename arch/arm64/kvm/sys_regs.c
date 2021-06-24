<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Derived from arch/arm/kvm/coproc.c:
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Authors: Rusty Russell <rusty@rustcorp.com.au>
 *          Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/mm.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/kvm_arm.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/sysreg.h>

#समावेश <trace/events/kvm.h>

#समावेश "sys_regs.h"

#समावेश "trace.h"

/*
 * All of this file is extremely similar to the ARM coproc.c, but the
 * types are dअगरferent. My gut feeling is that it should be pretty
 * easy to merge, but that would be an ABI अवरोधage -- again. VFP
 * would also need to be असलtracted.
 *
 * For AArch32, we only take care of what is being trapped. Anything
 * that has to करो with init and userspace access has to go via the
 * 64bit पूर्णांकerface.
 */

#घोषणा reg_to_encoding(x)						\
	sys_reg((u32)(x)->Op0, (u32)(x)->Op1,				\
		(u32)(x)->CRn, (u32)(x)->CRm, (u32)(x)->Op2)

अटल bool पढ़ो_from_ग_लिखो_only(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा sys_reg_params *params,
				 स्थिर काष्ठा sys_reg_desc *r)
अणु
	WARN_ONCE(1, "Unexpected sys_reg read to write-only register\n");
	prपूर्णांक_sys_reg_instr(params);
	kvm_inject_undefined(vcpu);
	वापस false;
पूर्ण

अटल bool ग_लिखो_to_पढ़ो_only(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा sys_reg_params *params,
			       स्थिर काष्ठा sys_reg_desc *r)
अणु
	WARN_ONCE(1, "Unexpected sys_reg write to read-only register\n");
	prपूर्णांक_sys_reg_instr(params);
	kvm_inject_undefined(vcpu);
	वापस false;
पूर्ण

u64 vcpu_पढ़ो_sys_reg(स्थिर काष्ठा kvm_vcpu *vcpu, पूर्णांक reg)
अणु
	u64 val = 0x8badf00d8badf00d;

	अगर (vcpu->arch.sysregs_loaded_on_cpu &&
	    __vcpu_पढ़ो_sys_reg_from_cpu(reg, &val))
		वापस val;

	वापस __vcpu_sys_reg(vcpu, reg);
पूर्ण

व्योम vcpu_ग_लिखो_sys_reg(काष्ठा kvm_vcpu *vcpu, u64 val, पूर्णांक reg)
अणु
	अगर (vcpu->arch.sysregs_loaded_on_cpu &&
	    __vcpu_ग_लिखो_sys_reg_to_cpu(val, reg))
		वापस;

	 __vcpu_sys_reg(vcpu, reg) = val;
पूर्ण

/* 3 bits per cache level, as per CLIDR, but non-existent caches always 0 */
अटल u32 cache_levels;

/* CSSELR values; used to index KVM_REG_ARM_DEMUX_ID_CCSIDR */
#घोषणा CSSELR_MAX 14

/* Which cache CCSIDR represents depends on CSSELR value. */
अटल u32 get_ccsidr(u32 csselr)
अणु
	u32 ccsidr;

	/* Make sure noone अन्यथा changes CSSELR during this! */
	local_irq_disable();
	ग_लिखो_sysreg(csselr, csselr_el1);
	isb();
	ccsidr = पढ़ो_sysreg(ccsidr_el1);
	local_irq_enable();

	वापस ccsidr;
पूर्ण

/*
 * See note at ARMv7 ARM B1.14.4 (TL;DR: S/W ops are not easily भवized).
 */
अटल bool access_dcsw(काष्ठा kvm_vcpu *vcpu,
			काष्ठा sys_reg_params *p,
			स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (!p->is_ग_लिखो)
		वापस पढ़ो_from_ग_लिखो_only(vcpu, p, r);

	/*
	 * Only track S/W ops अगर we करोn't have FWB. It still indicates
	 * that the guest is a bit broken (S/W operations should only
	 * be करोne by firmware, knowing that there is only a single
	 * CPU left in the प्रणाली, and certainly not from non-secure
	 * software).
	 */
	अगर (!cpus_have_स्थिर_cap(ARM64_HAS_STAGE2_FWB))
		kvm_set_way_flush(vcpu);

	वापस true;
पूर्ण

अटल व्योम get_access_mask(स्थिर काष्ठा sys_reg_desc *r, u64 *mask, u64 *shअगरt)
अणु
	चयन (r->aarch32_map) अणु
	हाल AA32_LO:
		*mask = GENMASK_ULL(31, 0);
		*shअगरt = 0;
		अवरोध;
	हाल AA32_HI:
		*mask = GENMASK_ULL(63, 32);
		*shअगरt = 32;
		अवरोध;
	शेष:
		*mask = GENMASK_ULL(63, 0);
		*shअगरt = 0;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Generic accessor क्रम VM रेजिस्टरs. Only called as दीर्घ as HCR_TVM
 * is set. If the guest enables the MMU, we stop trapping the VM
 * sys_regs and leave it in complete control of the caches.
 */
अटल bool access_vm_reg(काष्ठा kvm_vcpu *vcpu,
			  काष्ठा sys_reg_params *p,
			  स्थिर काष्ठा sys_reg_desc *r)
अणु
	bool was_enabled = vcpu_has_cache_enabled(vcpu);
	u64 val, mask, shअगरt;

	BUG_ON(!p->is_ग_लिखो);

	get_access_mask(r, &mask, &shअगरt);

	अगर (~mask) अणु
		val = vcpu_पढ़ो_sys_reg(vcpu, r->reg);
		val &= ~mask;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	val |= (p->regval & (mask >> shअगरt)) << shअगरt;
	vcpu_ग_लिखो_sys_reg(vcpu, val, r->reg);

	kvm_toggle_cache(vcpu, was_enabled);
	वापस true;
पूर्ण

अटल bool access_actlr(काष्ठा kvm_vcpu *vcpu,
			 काष्ठा sys_reg_params *p,
			 स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 mask, shअगरt;

	अगर (p->is_ग_लिखो)
		वापस ignore_ग_लिखो(vcpu, p);

	get_access_mask(r, &mask, &shअगरt);
	p->regval = (vcpu_पढ़ो_sys_reg(vcpu, r->reg) & mask) >> shअगरt;

	वापस true;
पूर्ण

/*
 * Trap handler क्रम the GICv3 SGI generation प्रणाली रेजिस्टर.
 * Forward the request to the VGIC emulation.
 * The cp15_64 code makes sure this स्वतःmatically works
 * क्रम both AArch64 and AArch32 accesses.
 */
अटल bool access_gic_sgi(काष्ठा kvm_vcpu *vcpu,
			   काष्ठा sys_reg_params *p,
			   स्थिर काष्ठा sys_reg_desc *r)
अणु
	bool g1;

	अगर (!p->is_ग_लिखो)
		वापस पढ़ो_from_ग_लिखो_only(vcpu, p, r);

	/*
	 * In a प्रणाली where GICD_CTLR.DS=1, a ICC_SGI0R_EL1 access generates
	 * Group0 SGIs only, जबतक ICC_SGI1R_EL1 can generate either group,
	 * depending on the SGI configuration. ICC_ASGI1R_EL1 is effectively
	 * equivalent to ICC_SGI0R_EL1, as there is no "alternative" secure
	 * group.
	 */
	अगर (p->Op0 == 0) अणु		/* AArch32 */
		चयन (p->Op1) अणु
		शेष:		/* Keep GCC quiet */
		हाल 0:			/* ICC_SGI1R */
			g1 = true;
			अवरोध;
		हाल 1:			/* ICC_ASGI1R */
		हाल 2:			/* ICC_SGI0R */
			g1 = false;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु			/* AArch64 */
		चयन (p->Op2) अणु
		शेष:		/* Keep GCC quiet */
		हाल 5:			/* ICC_SGI1R_EL1 */
			g1 = true;
			अवरोध;
		हाल 6:			/* ICC_ASGI1R_EL1 */
		हाल 7:			/* ICC_SGI0R_EL1 */
			g1 = false;
			अवरोध;
		पूर्ण
	पूर्ण

	vgic_v3_dispatch_sgi(vcpu, p->regval, g1);

	वापस true;
पूर्ण

अटल bool access_gic_sre(काष्ठा kvm_vcpu *vcpu,
			   काष्ठा sys_reg_params *p,
			   स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (p->is_ग_लिखो)
		वापस ignore_ग_लिखो(vcpu, p);

	p->regval = vcpu->arch.vgic_cpu.vgic_v3.vgic_sre;
	वापस true;
पूर्ण

अटल bool trap_raz_wi(काष्ठा kvm_vcpu *vcpu,
			काष्ठा sys_reg_params *p,
			स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (p->is_ग_लिखो)
		वापस ignore_ग_लिखो(vcpu, p);
	अन्यथा
		वापस पढ़ो_zero(vcpu, p);
पूर्ण

/*
 * ARMv8.1 mandates at least a trivial LORegion implementation, where all the
 * RW रेजिस्टरs are RES0 (which we can implement as RAZ/WI). On an ARMv8.0
 * प्रणाली, these रेजिस्टरs should UNDEF. LORID_EL1 being a RO रेजिस्टर, we
 * treat it separately.
 */
अटल bool trap_loregion(काष्ठा kvm_vcpu *vcpu,
			  काष्ठा sys_reg_params *p,
			  स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 val = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR1_EL1);
	u32 sr = reg_to_encoding(r);

	अगर (!(val & (0xfUL << ID_AA64MMFR1_LOR_SHIFT))) अणु
		kvm_inject_undefined(vcpu);
		वापस false;
	पूर्ण

	अगर (p->is_ग_लिखो && sr == SYS_LORID_EL1)
		वापस ग_लिखो_to_पढ़ो_only(vcpu, p, r);

	वापस trap_raz_wi(vcpu, p, r);
पूर्ण

अटल bool trap_oslsr_el1(काष्ठा kvm_vcpu *vcpu,
			   काष्ठा sys_reg_params *p,
			   स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (p->is_ग_लिखो) अणु
		वापस ignore_ग_लिखो(vcpu, p);
	पूर्ण अन्यथा अणु
		p->regval = (1 << 3);
		वापस true;
	पूर्ण
पूर्ण

अटल bool trap_dbgauthstatus_el1(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा sys_reg_params *p,
				   स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (p->is_ग_लिखो) अणु
		वापस ignore_ग_लिखो(vcpu, p);
	पूर्ण अन्यथा अणु
		p->regval = पढ़ो_sysreg(dbgauthstatus_el1);
		वापस true;
	पूर्ण
पूर्ण

/*
 * We want to aव्योम world-चयनing all the DBG रेजिस्टरs all the
 * समय:
 * 
 * - If we've touched any debug register, it is likely that we're
 *   going to touch more of them. It then makes sense to disable the
 *   traps and start करोing the save/restore dance
 * - If debug is active (DBG_MDSCR_KDE or DBG_MDSCR_MDE set), it is
 *   then mandatory to save/restore the रेजिस्टरs, as the guest
 *   depends on them.
 * 
 * For this, we use a सूचीTY bit, indicating the guest has modअगरied the
 * debug रेजिस्टरs, used as follow:
 *
 * On guest entry:
 * - If the dirty bit is set (because we're coming back from trapping),
 *   disable the traps, save host रेजिस्टरs, restore guest रेजिस्टरs.
 * - If debug is actively in use (DBG_MDSCR_KDE or DBG_MDSCR_MDE set),
 *   set the dirty bit, disable the traps, save host रेजिस्टरs,
 *   restore guest रेजिस्टरs.
 * - Otherwise, enable the traps
 *
 * On guest निकास:
 * - If the dirty bit is set, save guest रेजिस्टरs, restore host
 *   रेजिस्टरs and clear the dirty bit. This ensure that the host can
 *   now use the debug रेजिस्टरs.
 */
अटल bool trap_debug_regs(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा sys_reg_params *p,
			    स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (p->is_ग_लिखो) अणु
		vcpu_ग_लिखो_sys_reg(vcpu, p->regval, r->reg);
		vcpu->arch.flags |= KVM_ARM64_DEBUG_सूचीTY;
	पूर्ण अन्यथा अणु
		p->regval = vcpu_पढ़ो_sys_reg(vcpu, r->reg);
	पूर्ण

	trace_trap_reg(__func__, r->reg, p->is_ग_लिखो, p->regval);

	वापस true;
पूर्ण

/*
 * reg_to_dbg/dbg_to_reg
 *
 * A 32 bit ग_लिखो to a debug रेजिस्टर leave top bits alone
 * A 32 bit पढ़ो from a debug रेजिस्टर only वापसs the bottom bits
 *
 * All ग_लिखोs will set the KVM_ARM64_DEBUG_सूचीTY flag to ensure the
 * hyp.S code चयनes between host and guest values in future.
 */
अटल व्योम reg_to_dbg(काष्ठा kvm_vcpu *vcpu,
		       काष्ठा sys_reg_params *p,
		       स्थिर काष्ठा sys_reg_desc *rd,
		       u64 *dbg_reg)
अणु
	u64 mask, shअगरt, val;

	get_access_mask(rd, &mask, &shअगरt);

	val = *dbg_reg;
	val &= ~mask;
	val |= (p->regval & (mask >> shअगरt)) << shअगरt;
	*dbg_reg = val;

	vcpu->arch.flags |= KVM_ARM64_DEBUG_सूचीTY;
पूर्ण

अटल व्योम dbg_to_reg(काष्ठा kvm_vcpu *vcpu,
		       काष्ठा sys_reg_params *p,
		       स्थिर काष्ठा sys_reg_desc *rd,
		       u64 *dbg_reg)
अणु
	u64 mask, shअगरt;

	get_access_mask(rd, &mask, &shअगरt);
	p->regval = (*dbg_reg & mask) >> shअगरt;
पूर्ण

अटल bool trap_bvr(काष्ठा kvm_vcpu *vcpu,
		     काष्ठा sys_reg_params *p,
		     स्थिर काष्ठा sys_reg_desc *rd)
अणु
	u64 *dbg_reg = &vcpu->arch.vcpu_debug_state.dbg_bvr[rd->CRm];

	अगर (p->is_ग_लिखो)
		reg_to_dbg(vcpu, p, rd, dbg_reg);
	अन्यथा
		dbg_to_reg(vcpu, p, rd, dbg_reg);

	trace_trap_reg(__func__, rd->CRm, p->is_ग_लिखो, *dbg_reg);

	वापस true;
पूर्ण

अटल पूर्णांक set_bvr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
		स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	__u64 *r = &vcpu->arch.vcpu_debug_state.dbg_bvr[rd->CRm];

	अगर (copy_from_user(r, uaddr, KVM_REG_SIZE(reg->id)) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक get_bvr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
	स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	__u64 *r = &vcpu->arch.vcpu_debug_state.dbg_bvr[rd->CRm];

	अगर (copy_to_user(uaddr, r, KVM_REG_SIZE(reg->id)) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम reset_bvr(काष्ठा kvm_vcpu *vcpu,
		      स्थिर काष्ठा sys_reg_desc *rd)
अणु
	vcpu->arch.vcpu_debug_state.dbg_bvr[rd->CRm] = rd->val;
पूर्ण

अटल bool trap_bcr(काष्ठा kvm_vcpu *vcpu,
		     काष्ठा sys_reg_params *p,
		     स्थिर काष्ठा sys_reg_desc *rd)
अणु
	u64 *dbg_reg = &vcpu->arch.vcpu_debug_state.dbg_bcr[rd->CRm];

	अगर (p->is_ग_लिखो)
		reg_to_dbg(vcpu, p, rd, dbg_reg);
	अन्यथा
		dbg_to_reg(vcpu, p, rd, dbg_reg);

	trace_trap_reg(__func__, rd->CRm, p->is_ग_लिखो, *dbg_reg);

	वापस true;
पूर्ण

अटल पूर्णांक set_bcr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
		स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	__u64 *r = &vcpu->arch.vcpu_debug_state.dbg_bcr[rd->CRm];

	अगर (copy_from_user(r, uaddr, KVM_REG_SIZE(reg->id)) != 0)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_bcr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
	स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	__u64 *r = &vcpu->arch.vcpu_debug_state.dbg_bcr[rd->CRm];

	अगर (copy_to_user(uaddr, r, KVM_REG_SIZE(reg->id)) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम reset_bcr(काष्ठा kvm_vcpu *vcpu,
		      स्थिर काष्ठा sys_reg_desc *rd)
अणु
	vcpu->arch.vcpu_debug_state.dbg_bcr[rd->CRm] = rd->val;
पूर्ण

अटल bool trap_wvr(काष्ठा kvm_vcpu *vcpu,
		     काष्ठा sys_reg_params *p,
		     स्थिर काष्ठा sys_reg_desc *rd)
अणु
	u64 *dbg_reg = &vcpu->arch.vcpu_debug_state.dbg_wvr[rd->CRm];

	अगर (p->is_ग_लिखो)
		reg_to_dbg(vcpu, p, rd, dbg_reg);
	अन्यथा
		dbg_to_reg(vcpu, p, rd, dbg_reg);

	trace_trap_reg(__func__, rd->CRm, p->is_ग_लिखो,
		vcpu->arch.vcpu_debug_state.dbg_wvr[rd->CRm]);

	वापस true;
पूर्ण

अटल पूर्णांक set_wvr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
		स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	__u64 *r = &vcpu->arch.vcpu_debug_state.dbg_wvr[rd->CRm];

	अगर (copy_from_user(r, uaddr, KVM_REG_SIZE(reg->id)) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक get_wvr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
	स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	__u64 *r = &vcpu->arch.vcpu_debug_state.dbg_wvr[rd->CRm];

	अगर (copy_to_user(uaddr, r, KVM_REG_SIZE(reg->id)) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम reset_wvr(काष्ठा kvm_vcpu *vcpu,
		      स्थिर काष्ठा sys_reg_desc *rd)
अणु
	vcpu->arch.vcpu_debug_state.dbg_wvr[rd->CRm] = rd->val;
पूर्ण

अटल bool trap_wcr(काष्ठा kvm_vcpu *vcpu,
		     काष्ठा sys_reg_params *p,
		     स्थिर काष्ठा sys_reg_desc *rd)
अणु
	u64 *dbg_reg = &vcpu->arch.vcpu_debug_state.dbg_wcr[rd->CRm];

	अगर (p->is_ग_लिखो)
		reg_to_dbg(vcpu, p, rd, dbg_reg);
	अन्यथा
		dbg_to_reg(vcpu, p, rd, dbg_reg);

	trace_trap_reg(__func__, rd->CRm, p->is_ग_लिखो, *dbg_reg);

	वापस true;
पूर्ण

अटल पूर्णांक set_wcr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
		स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	__u64 *r = &vcpu->arch.vcpu_debug_state.dbg_wcr[rd->CRm];

	अगर (copy_from_user(r, uaddr, KVM_REG_SIZE(reg->id)) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक get_wcr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
	स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	__u64 *r = &vcpu->arch.vcpu_debug_state.dbg_wcr[rd->CRm];

	अगर (copy_to_user(uaddr, r, KVM_REG_SIZE(reg->id)) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम reset_wcr(काष्ठा kvm_vcpu *vcpu,
		      स्थिर काष्ठा sys_reg_desc *rd)
अणु
	vcpu->arch.vcpu_debug_state.dbg_wcr[rd->CRm] = rd->val;
पूर्ण

अटल व्योम reset_amair_el1(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 amair = पढ़ो_sysreg(amair_el1);
	vcpu_ग_लिखो_sys_reg(vcpu, amair, AMAIR_EL1);
पूर्ण

अटल व्योम reset_actlr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 actlr = पढ़ो_sysreg(actlr_el1);
	vcpu_ग_लिखो_sys_reg(vcpu, actlr, ACTLR_EL1);
पूर्ण

अटल व्योम reset_mpidr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 mpidr;

	/*
	 * Map the vcpu_id पूर्णांकo the first three affinity level fields of
	 * the MPIDR. We limit the number of VCPUs in level 0 due to a
	 * limitation to 16 CPUs in that level in the ICC_SGIxR रेजिस्टरs
	 * of the GICv3 to be able to address each CPU directly when
	 * sending IPIs.
	 */
	mpidr = (vcpu->vcpu_id & 0x0f) << MPIDR_LEVEL_SHIFT(0);
	mpidr |= ((vcpu->vcpu_id >> 4) & 0xff) << MPIDR_LEVEL_SHIFT(1);
	mpidr |= ((vcpu->vcpu_id >> 12) & 0xff) << MPIDR_LEVEL_SHIFT(2);
	vcpu_ग_लिखो_sys_reg(vcpu, (1ULL << 31) | mpidr, MPIDR_EL1);
पूर्ण

अटल अचिन्हित पूर्णांक pmu_visibility(स्थिर काष्ठा kvm_vcpu *vcpu,
				   स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (kvm_vcpu_has_pmu(vcpu))
		वापस 0;

	वापस REG_HIDDEN;
पूर्ण

अटल व्योम reset_pmcr(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 pmcr, val;

	/* No PMU available, PMCR_EL0 may UNDEF... */
	अगर (!kvm_arm_support_pmu_v3())
		वापस;

	pmcr = पढ़ो_sysreg(pmcr_el0);
	/*
	 * Writable bits of PMCR_EL0 (ARMV8_PMU_PMCR_MASK) are reset to UNKNOWN
	 * except PMCR.E resetting to zero.
	 */
	val = ((pmcr & ~ARMV8_PMU_PMCR_MASK)
	       | (ARMV8_PMU_PMCR_MASK & 0xdecafbad)) & (~ARMV8_PMU_PMCR_E);
	अगर (!प्रणाली_supports_32bit_el0())
		val |= ARMV8_PMU_PMCR_LC;
	__vcpu_sys_reg(vcpu, r->reg) = val;
पूर्ण

अटल bool check_pmu_access_disabled(काष्ठा kvm_vcpu *vcpu, u64 flags)
अणु
	u64 reg = __vcpu_sys_reg(vcpu, PMUSERENR_EL0);
	bool enabled = (reg & flags) || vcpu_mode_priv(vcpu);

	अगर (!enabled)
		kvm_inject_undefined(vcpu);

	वापस !enabled;
पूर्ण

अटल bool pmu_access_el0_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस check_pmu_access_disabled(vcpu, ARMV8_PMU_USERENR_EN);
पूर्ण

अटल bool pmu_ग_लिखो_swinc_el0_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस check_pmu_access_disabled(vcpu, ARMV8_PMU_USERENR_SW | ARMV8_PMU_USERENR_EN);
पूर्ण

अटल bool pmu_access_cycle_counter_el0_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस check_pmu_access_disabled(vcpu, ARMV8_PMU_USERENR_CR | ARMV8_PMU_USERENR_EN);
पूर्ण

अटल bool pmu_access_event_counter_el0_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस check_pmu_access_disabled(vcpu, ARMV8_PMU_USERENR_ER | ARMV8_PMU_USERENR_EN);
पूर्ण

अटल bool access_pmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 val;

	अगर (pmu_access_el0_disabled(vcpu))
		वापस false;

	अगर (p->is_ग_लिखो) अणु
		/* Only update ग_लिखोable bits of PMCR */
		val = __vcpu_sys_reg(vcpu, PMCR_EL0);
		val &= ~ARMV8_PMU_PMCR_MASK;
		val |= p->regval & ARMV8_PMU_PMCR_MASK;
		अगर (!प्रणाली_supports_32bit_el0())
			val |= ARMV8_PMU_PMCR_LC;
		__vcpu_sys_reg(vcpu, PMCR_EL0) = val;
		kvm_pmu_handle_pmcr(vcpu, val);
		kvm_vcpu_pmu_restore_guest(vcpu);
	पूर्ण अन्यथा अणु
		/* PMCR.P & PMCR.C are RAZ */
		val = __vcpu_sys_reg(vcpu, PMCR_EL0)
		      & ~(ARMV8_PMU_PMCR_P | ARMV8_PMU_PMCR_C);
		p->regval = val;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_pmselr(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			  स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (pmu_access_event_counter_el0_disabled(vcpu))
		वापस false;

	अगर (p->is_ग_लिखो)
		__vcpu_sys_reg(vcpu, PMSELR_EL0) = p->regval;
	अन्यथा
		/* वापस PMSELR.SEL field */
		p->regval = __vcpu_sys_reg(vcpu, PMSELR_EL0)
			    & ARMV8_PMU_COUNTER_MASK;

	वापस true;
पूर्ण

अटल bool access_pmceid(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			  स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 pmceid, mask, shअगरt;

	BUG_ON(p->is_ग_लिखो);

	अगर (pmu_access_el0_disabled(vcpu))
		वापस false;

	get_access_mask(r, &mask, &shअगरt);

	pmceid = kvm_pmu_get_pmceid(vcpu, (p->Op2 & 1));
	pmceid &= mask;
	pmceid >>= shअगरt;

	p->regval = pmceid;

	वापस true;
पूर्ण

अटल bool pmu_counter_idx_valid(काष्ठा kvm_vcpu *vcpu, u64 idx)
अणु
	u64 pmcr, val;

	pmcr = __vcpu_sys_reg(vcpu, PMCR_EL0);
	val = (pmcr >> ARMV8_PMU_PMCR_N_SHIFT) & ARMV8_PMU_PMCR_N_MASK;
	अगर (idx >= val && idx != ARMV8_PMU_CYCLE_IDX) अणु
		kvm_inject_undefined(vcpu);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_pmu_evcntr(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा sys_reg_params *p,
			      स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 idx = ~0UL;

	अगर (r->CRn == 9 && r->CRm == 13) अणु
		अगर (r->Op2 == 2) अणु
			/* PMXEVCNTR_EL0 */
			अगर (pmu_access_event_counter_el0_disabled(vcpu))
				वापस false;

			idx = __vcpu_sys_reg(vcpu, PMSELR_EL0)
			      & ARMV8_PMU_COUNTER_MASK;
		पूर्ण अन्यथा अगर (r->Op2 == 0) अणु
			/* PMCCNTR_EL0 */
			अगर (pmu_access_cycle_counter_el0_disabled(vcpu))
				वापस false;

			idx = ARMV8_PMU_CYCLE_IDX;
		पूर्ण
	पूर्ण अन्यथा अगर (r->CRn == 0 && r->CRm == 9) अणु
		/* PMCCNTR */
		अगर (pmu_access_event_counter_el0_disabled(vcpu))
			वापस false;

		idx = ARMV8_PMU_CYCLE_IDX;
	पूर्ण अन्यथा अगर (r->CRn == 14 && (r->CRm & 12) == 8) अणु
		/* PMEVCNTRn_EL0 */
		अगर (pmu_access_event_counter_el0_disabled(vcpu))
			वापस false;

		idx = ((r->CRm & 3) << 3) | (r->Op2 & 7);
	पूर्ण

	/* Catch any decoding mistake */
	WARN_ON(idx == ~0UL);

	अगर (!pmu_counter_idx_valid(vcpu, idx))
		वापस false;

	अगर (p->is_ग_लिखो) अणु
		अगर (pmu_access_el0_disabled(vcpu))
			वापस false;

		kvm_pmu_set_counter_value(vcpu, idx, p->regval);
	पूर्ण अन्यथा अणु
		p->regval = kvm_pmu_get_counter_value(vcpu, idx);
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_pmu_evtyper(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			       स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 idx, reg;

	अगर (pmu_access_el0_disabled(vcpu))
		वापस false;

	अगर (r->CRn == 9 && r->CRm == 13 && r->Op2 == 1) अणु
		/* PMXEVTYPER_EL0 */
		idx = __vcpu_sys_reg(vcpu, PMSELR_EL0) & ARMV8_PMU_COUNTER_MASK;
		reg = PMEVTYPER0_EL0 + idx;
	पूर्ण अन्यथा अगर (r->CRn == 14 && (r->CRm & 12) == 12) अणु
		idx = ((r->CRm & 3) << 3) | (r->Op2 & 7);
		अगर (idx == ARMV8_PMU_CYCLE_IDX)
			reg = PMCCFILTR_EL0;
		अन्यथा
			/* PMEVTYPERn_EL0 */
			reg = PMEVTYPER0_EL0 + idx;
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	अगर (!pmu_counter_idx_valid(vcpu, idx))
		वापस false;

	अगर (p->is_ग_लिखो) अणु
		kvm_pmu_set_counter_event_type(vcpu, p->regval, idx);
		__vcpu_sys_reg(vcpu, reg) = p->regval & ARMV8_PMU_EVTYPE_MASK;
		kvm_vcpu_pmu_restore_guest(vcpu);
	पूर्ण अन्यथा अणु
		p->regval = __vcpu_sys_reg(vcpu, reg) & ARMV8_PMU_EVTYPE_MASK;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_pmcnten(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			   स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 val, mask;

	अगर (pmu_access_el0_disabled(vcpu))
		वापस false;

	mask = kvm_pmu_valid_counter_mask(vcpu);
	अगर (p->is_ग_लिखो) अणु
		val = p->regval & mask;
		अगर (r->Op2 & 0x1) अणु
			/* accessing PMCNTENSET_EL0 */
			__vcpu_sys_reg(vcpu, PMCNTENSET_EL0) |= val;
			kvm_pmu_enable_counter_mask(vcpu, val);
			kvm_vcpu_pmu_restore_guest(vcpu);
		पूर्ण अन्यथा अणु
			/* accessing PMCNTENCLR_EL0 */
			__vcpu_sys_reg(vcpu, PMCNTENSET_EL0) &= ~val;
			kvm_pmu_disable_counter_mask(vcpu, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		p->regval = __vcpu_sys_reg(vcpu, PMCNTENSET_EL0) & mask;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_pmपूर्णांकen(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			   स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 mask = kvm_pmu_valid_counter_mask(vcpu);

	अगर (check_pmu_access_disabled(vcpu, 0))
		वापस false;

	अगर (p->is_ग_लिखो) अणु
		u64 val = p->regval & mask;

		अगर (r->Op2 & 0x1)
			/* accessing PMINTENSET_EL1 */
			__vcpu_sys_reg(vcpu, PMINTENSET_EL1) |= val;
		अन्यथा
			/* accessing PMINTENCLR_EL1 */
			__vcpu_sys_reg(vcpu, PMINTENSET_EL1) &= ~val;
	पूर्ण अन्यथा अणु
		p->regval = __vcpu_sys_reg(vcpu, PMINTENSET_EL1) & mask;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_pmovs(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			 स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 mask = kvm_pmu_valid_counter_mask(vcpu);

	अगर (pmu_access_el0_disabled(vcpu))
		वापस false;

	अगर (p->is_ग_लिखो) अणु
		अगर (r->CRm & 0x2)
			/* accessing PMOVSSET_EL0 */
			__vcpu_sys_reg(vcpu, PMOVSSET_EL0) |= (p->regval & mask);
		अन्यथा
			/* accessing PMOVSCLR_EL0 */
			__vcpu_sys_reg(vcpu, PMOVSSET_EL0) &= ~(p->regval & mask);
	पूर्ण अन्यथा अणु
		p->regval = __vcpu_sys_reg(vcpu, PMOVSSET_EL0) & mask;
	पूर्ण

	वापस true;
पूर्ण

अटल bool access_pmswinc(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			   स्थिर काष्ठा sys_reg_desc *r)
अणु
	u64 mask;

	अगर (!p->is_ग_लिखो)
		वापस पढ़ो_from_ग_लिखो_only(vcpu, p, r);

	अगर (pmu_ग_लिखो_swinc_el0_disabled(vcpu))
		वापस false;

	mask = kvm_pmu_valid_counter_mask(vcpu);
	kvm_pmu_software_increment(vcpu, p->regval & mask);
	वापस true;
पूर्ण

अटल bool access_pmuserenr(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			     स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (p->is_ग_लिखो) अणु
		अगर (!vcpu_mode_priv(vcpu)) अणु
			kvm_inject_undefined(vcpu);
			वापस false;
		पूर्ण

		__vcpu_sys_reg(vcpu, PMUSERENR_EL0) =
			       p->regval & ARMV8_PMU_USERENR_MASK;
	पूर्ण अन्यथा अणु
		p->regval = __vcpu_sys_reg(vcpu, PMUSERENR_EL0)
			    & ARMV8_PMU_USERENR_MASK;
	पूर्ण

	वापस true;
पूर्ण

/* Silly macro to expand the DBGअणुBCR,BVR,WVR,WCRपूर्णn_EL1 रेजिस्टरs in one go */
#घोषणा DBG_BCR_BVR_WCR_WVR_EL1(n)					\
	अणु SYS_DESC(SYS_DBGBVRn_EL1(n)),					\
	  trap_bvr, reset_bvr, 0, 0, get_bvr, set_bvr पूर्ण,		\
	अणु SYS_DESC(SYS_DBGBCRn_EL1(n)),					\
	  trap_bcr, reset_bcr, 0, 0, get_bcr, set_bcr पूर्ण,		\
	अणु SYS_DESC(SYS_DBGWVRn_EL1(n)),					\
	  trap_wvr, reset_wvr, 0, 0,  get_wvr, set_wvr पूर्ण,		\
	अणु SYS_DESC(SYS_DBGWCRn_EL1(n)),					\
	  trap_wcr, reset_wcr, 0, 0,  get_wcr, set_wcr पूर्ण

#घोषणा PMU_SYS_REG(r)						\
	SYS_DESC(r), .reset = reset_unknown, .visibility = pmu_visibility

/* Macro to expand the PMEVCNTRn_EL0 रेजिस्टर */
#घोषणा PMU_PMEVCNTR_EL0(n)						\
	अणु PMU_SYS_REG(SYS_PMEVCNTRn_EL0(n)),				\
	  .access = access_pmu_evcntr, .reg = (PMEVCNTR0_EL0 + n), पूर्ण

/* Macro to expand the PMEVTYPERn_EL0 रेजिस्टर */
#घोषणा PMU_PMEVTYPER_EL0(n)						\
	अणु PMU_SYS_REG(SYS_PMEVTYPERn_EL0(n)),				\
	  .access = access_pmu_evtyper, .reg = (PMEVTYPER0_EL0 + n), पूर्ण

अटल bool undef_access(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			 स्थिर काष्ठा sys_reg_desc *r)
अणु
	kvm_inject_undefined(vcpu);

	वापस false;
पूर्ण

/* Macro to expand the AMU counter and type रेजिस्टरs*/
#घोषणा AMU_AMEVCNTR0_EL0(n) अणु SYS_DESC(SYS_AMEVCNTR0_EL0(n)), undef_access पूर्ण
#घोषणा AMU_AMEVTYPER0_EL0(n) अणु SYS_DESC(SYS_AMEVTYPER0_EL0(n)), undef_access पूर्ण
#घोषणा AMU_AMEVCNTR1_EL0(n) अणु SYS_DESC(SYS_AMEVCNTR1_EL0(n)), undef_access पूर्ण
#घोषणा AMU_AMEVTYPER1_EL0(n) अणु SYS_DESC(SYS_AMEVTYPER1_EL0(n)), undef_access पूर्ण

अटल अचिन्हित पूर्णांक ptrauth_visibility(स्थिर काष्ठा kvm_vcpu *vcpu,
			स्थिर काष्ठा sys_reg_desc *rd)
अणु
	वापस vcpu_has_ptrauth(vcpu) ? 0 : REG_HIDDEN;
पूर्ण

/*
 * If we land here on a PtrAuth access, that is because we didn't
 * fixup the access on निकास by allowing the PtrAuth sysregs. The only
 * way this happens is when the guest करोes not have PtrAuth support
 * enabled.
 */
#घोषणा __PTRAUTH_KEY(k)						\
	अणु SYS_DESC(SYS_## k), undef_access, reset_unknown, k,		\
	.visibility = ptrauth_visibilityपूर्ण

#घोषणा PTRAUTH_KEY(k)							\
	__PTRAUTH_KEY(k ## KEYLO_EL1),					\
	__PTRAUTH_KEY(k ## KEYHI_EL1)

अटल bool access_arch_समयr(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा sys_reg_params *p,
			      स्थिर काष्ठा sys_reg_desc *r)
अणु
	क्रमागत kvm_arch_समयrs पंचांगr;
	क्रमागत kvm_arch_समयr_regs treg;
	u64 reg = reg_to_encoding(r);

	चयन (reg) अणु
	हाल SYS_CNTP_TVAL_EL0:
	हाल SYS_AARCH32_CNTP_TVAL:
		पंचांगr = TIMER_PTIMER;
		treg = TIMER_REG_TVAL;
		अवरोध;
	हाल SYS_CNTP_CTL_EL0:
	हाल SYS_AARCH32_CNTP_CTL:
		पंचांगr = TIMER_PTIMER;
		treg = TIMER_REG_CTL;
		अवरोध;
	हाल SYS_CNTP_CVAL_EL0:
	हाल SYS_AARCH32_CNTP_CVAL:
		पंचांगr = TIMER_PTIMER;
		treg = TIMER_REG_CVAL;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (p->is_ग_लिखो)
		kvm_arm_समयr_ग_लिखो_sysreg(vcpu, पंचांगr, treg, p->regval);
	अन्यथा
		p->regval = kvm_arm_समयr_पढ़ो_sysreg(vcpu, पंचांगr, treg);

	वापस true;
पूर्ण

#घोषणा FEATURE(x)	(GENMASK_ULL(x##_SHIFT + 3, x##_SHIFT))

/* Read a sanitised cpufeature ID रेजिस्टर by sys_reg_desc */
अटल u64 पढ़ो_id_reg(स्थिर काष्ठा kvm_vcpu *vcpu,
		काष्ठा sys_reg_desc स्थिर *r, bool raz)
अणु
	u32 id = reg_to_encoding(r);
	u64 val = raz ? 0 : पढ़ो_sanitised_ftr_reg(id);

	चयन (id) अणु
	हाल SYS_ID_AA64PFR0_EL1:
		अगर (!vcpu_has_sve(vcpu))
			val &= ~FEATURE(ID_AA64PFR0_SVE);
		val &= ~FEATURE(ID_AA64PFR0_AMU);
		val &= ~FEATURE(ID_AA64PFR0_CSV2);
		val |= FIELD_PREP(FEATURE(ID_AA64PFR0_CSV2), (u64)vcpu->kvm->arch.pfr0_csv2);
		val &= ~FEATURE(ID_AA64PFR0_CSV3);
		val |= FIELD_PREP(FEATURE(ID_AA64PFR0_CSV3), (u64)vcpu->kvm->arch.pfr0_csv3);
		अवरोध;
	हाल SYS_ID_AA64PFR1_EL1:
		val &= ~FEATURE(ID_AA64PFR1_MTE);
		अवरोध;
	हाल SYS_ID_AA64ISAR1_EL1:
		अगर (!vcpu_has_ptrauth(vcpu))
			val &= ~(FEATURE(ID_AA64ISAR1_APA) |
				 FEATURE(ID_AA64ISAR1_API) |
				 FEATURE(ID_AA64ISAR1_GPA) |
				 FEATURE(ID_AA64ISAR1_GPI));
		अवरोध;
	हाल SYS_ID_AA64DFR0_EL1:
		/* Limit debug to ARMv8.0 */
		val &= ~FEATURE(ID_AA64DFR0_DEBUGVER);
		val |= FIELD_PREP(FEATURE(ID_AA64DFR0_DEBUGVER), 6);
		/* Limit guests to PMUv3 क्रम ARMv8.4 */
		val = cpuid_feature_cap_perfmon_field(val,
						      ID_AA64DFR0_PMUVER_SHIFT,
						      kvm_vcpu_has_pmu(vcpu) ? ID_AA64DFR0_PMUVER_8_4 : 0);
		/* Hide SPE from guests */
		val &= ~FEATURE(ID_AA64DFR0_PMSVER);
		अवरोध;
	हाल SYS_ID_DFR0_EL1:
		/* Limit guests to PMUv3 क्रम ARMv8.4 */
		val = cpuid_feature_cap_perfmon_field(val,
						      ID_DFR0_PERFMON_SHIFT,
						      kvm_vcpu_has_pmu(vcpu) ? ID_DFR0_PERFMON_8_4 : 0);
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक id_visibility(स्थिर काष्ठा kvm_vcpu *vcpu,
				  स्थिर काष्ठा sys_reg_desc *r)
अणु
	u32 id = reg_to_encoding(r);

	चयन (id) अणु
	हाल SYS_ID_AA64ZFR0_EL1:
		अगर (!vcpu_has_sve(vcpu))
			वापस REG_RAZ;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* cpufeature ID रेजिस्टर access trap handlers */

अटल bool __access_id_reg(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा sys_reg_params *p,
			    स्थिर काष्ठा sys_reg_desc *r,
			    bool raz)
अणु
	अगर (p->is_ग_लिखो)
		वापस ग_लिखो_to_पढ़ो_only(vcpu, p, r);

	p->regval = पढ़ो_id_reg(vcpu, r, raz);
	वापस true;
पूर्ण

अटल bool access_id_reg(काष्ठा kvm_vcpu *vcpu,
			  काष्ठा sys_reg_params *p,
			  स्थिर काष्ठा sys_reg_desc *r)
अणु
	bool raz = sysreg_visible_as_raz(vcpu, r);

	वापस __access_id_reg(vcpu, p, r, raz);
पूर्ण

अटल bool access_raz_id_reg(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा sys_reg_params *p,
			      स्थिर काष्ठा sys_reg_desc *r)
अणु
	वापस __access_id_reg(vcpu, p, r, true);
पूर्ण

अटल पूर्णांक reg_from_user(u64 *val, स्थिर व्योम __user *uaddr, u64 id);
अटल पूर्णांक reg_to_user(व्योम __user *uaddr, स्थिर u64 *val, u64 id);
अटल u64 sys_reg_to_index(स्थिर काष्ठा sys_reg_desc *reg);

/* Visibility overrides क्रम SVE-specअगरic control रेजिस्टरs */
अटल अचिन्हित पूर्णांक sve_visibility(स्थिर काष्ठा kvm_vcpu *vcpu,
				   स्थिर काष्ठा sys_reg_desc *rd)
अणु
	अगर (vcpu_has_sve(vcpu))
		वापस 0;

	वापस REG_HIDDEN;
पूर्ण

अटल पूर्णांक set_id_aa64pfr0_el1(काष्ठा kvm_vcpu *vcpu,
			       स्थिर काष्ठा sys_reg_desc *rd,
			       स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	स्थिर u64 id = sys_reg_to_index(rd);
	u8 csv2, csv3;
	पूर्णांक err;
	u64 val;

	err = reg_from_user(&val, uaddr, id);
	अगर (err)
		वापस err;

	/*
	 * Allow AA64PFR0_EL1.CSV2 to be set from userspace as दीर्घ as
	 * it करोesn't promise more than what is actually provided (the
	 * guest could otherwise be covered in ectoplयंत्रic residue).
	 */
	csv2 = cpuid_feature_extract_अचिन्हित_field(val, ID_AA64PFR0_CSV2_SHIFT);
	अगर (csv2 > 1 ||
	    (csv2 && arm64_get_spectre_v2_state() != SPECTRE_UNAFFECTED))
		वापस -EINVAL;

	/* Same thing क्रम CSV3 */
	csv3 = cpuid_feature_extract_अचिन्हित_field(val, ID_AA64PFR0_CSV3_SHIFT);
	अगर (csv3 > 1 ||
	    (csv3 && arm64_get_meltकरोwn_state() != SPECTRE_UNAFFECTED))
		वापस -EINVAL;

	/* We can only dअगरfer with CSV[23], and anything अन्यथा is an error */
	val ^= पढ़ो_id_reg(vcpu, rd, false);
	val &= ~((0xFUL << ID_AA64PFR0_CSV2_SHIFT) |
		 (0xFUL << ID_AA64PFR0_CSV3_SHIFT));
	अगर (val)
		वापस -EINVAL;

	vcpu->kvm->arch.pfr0_csv2 = csv2;
	vcpu->kvm->arch.pfr0_csv3 = csv3 ;

	वापस 0;
पूर्ण

/*
 * cpufeature ID रेजिस्टर user accessors
 *
 * For now, these रेजिस्टरs are immutable क्रम userspace, so no values
 * are stored, and क्रम set_id_reg() we करोn't allow the effective value
 * to be changed.
 */
अटल पूर्णांक __get_id_reg(स्थिर काष्ठा kvm_vcpu *vcpu,
			स्थिर काष्ठा sys_reg_desc *rd, व्योम __user *uaddr,
			bool raz)
अणु
	स्थिर u64 id = sys_reg_to_index(rd);
	स्थिर u64 val = पढ़ो_id_reg(vcpu, rd, raz);

	वापस reg_to_user(uaddr, &val, id);
पूर्ण

अटल पूर्णांक __set_id_reg(स्थिर काष्ठा kvm_vcpu *vcpu,
			स्थिर काष्ठा sys_reg_desc *rd, व्योम __user *uaddr,
			bool raz)
अणु
	स्थिर u64 id = sys_reg_to_index(rd);
	पूर्णांक err;
	u64 val;

	err = reg_from_user(&val, uaddr, id);
	अगर (err)
		वापस err;

	/* This is what we mean by invariant: you can't change it. */
	अगर (val != पढ़ो_id_reg(vcpu, rd, raz))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक get_id_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
		      स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	bool raz = sysreg_visible_as_raz(vcpu, rd);

	वापस __get_id_reg(vcpu, rd, uaddr, raz);
पूर्ण

अटल पूर्णांक set_id_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
		      स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	bool raz = sysreg_visible_as_raz(vcpu, rd);

	वापस __set_id_reg(vcpu, rd, uaddr, raz);
पूर्ण

अटल पूर्णांक get_raz_id_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
			  स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	वापस __get_id_reg(vcpu, rd, uaddr, true);
पूर्ण

अटल पूर्णांक set_raz_id_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
			  स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr)
अणु
	वापस __set_id_reg(vcpu, rd, uaddr, true);
पूर्ण

अटल bool access_ctr(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
		       स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (p->is_ग_लिखो)
		वापस ग_लिखो_to_पढ़ो_only(vcpu, p, r);

	p->regval = पढ़ो_sanitised_ftr_reg(SYS_CTR_EL0);
	वापस true;
पूर्ण

अटल bool access_clidr(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			 स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (p->is_ग_लिखो)
		वापस ग_लिखो_to_पढ़ो_only(vcpu, p, r);

	p->regval = पढ़ो_sysreg(clidr_el1);
	वापस true;
पूर्ण

अटल bool access_csselr(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			  स्थिर काष्ठा sys_reg_desc *r)
अणु
	पूर्णांक reg = r->reg;

	अगर (p->is_ग_लिखो)
		vcpu_ग_लिखो_sys_reg(vcpu, p->regval, reg);
	अन्यथा
		p->regval = vcpu_पढ़ो_sys_reg(vcpu, reg);
	वापस true;
पूर्ण

अटल bool access_ccsidr(काष्ठा kvm_vcpu *vcpu, काष्ठा sys_reg_params *p,
			  स्थिर काष्ठा sys_reg_desc *r)
अणु
	u32 csselr;

	अगर (p->is_ग_लिखो)
		वापस ग_लिखो_to_पढ़ो_only(vcpu, p, r);

	csselr = vcpu_पढ़ो_sys_reg(vcpu, CSSELR_EL1);
	p->regval = get_ccsidr(csselr);

	/*
	 * Guests should not be करोing cache operations by set/way at all, and
	 * क्रम this reason, we trap them and attempt to infer the पूर्णांकent, so
	 * that we can flush the entire guest's address space at the appropriate
	 * समय.
	 * To prevent this trapping from causing perक्रमmance problems, let's
	 * expose the geometry of all data and unअगरied caches (which are
	 * guaranteed to be PIPT and thus non-aliasing) as 1 set and 1 way.
	 * [If guests should attempt to infer aliasing properties from the
	 * geometry (which is not permitted by the architecture), they would
	 * only करो so क्रम भवly indexed caches.]
	 */
	अगर (!(csselr & 1)) // data or unअगरied cache
		p->regval &= ~GENMASK(27, 3);
	वापस true;
पूर्ण

/* sys_reg_desc initialiser क्रम known cpufeature ID रेजिस्टरs */
#घोषणा ID_SANITISED(name) अणु			\
	SYS_DESC(SYS_##name),			\
	.access	= access_id_reg,		\
	.get_user = get_id_reg,			\
	.set_user = set_id_reg,			\
	.visibility = id_visibility,		\
पूर्ण

/*
 * sys_reg_desc initialiser क्रम architecturally unallocated cpufeature ID
 * रेजिस्टर with encoding Op0=3, Op1=0, CRn=0, CRm=crm, Op2=op2
 * (1 <= crm < 8, 0 <= Op2 < 8).
 */
#घोषणा ID_UNALLOCATED(crm, op2) अणु			\
	Op0(3), Op1(0), CRn(0), CRm(crm), Op2(op2),	\
	.access = access_raz_id_reg,			\
	.get_user = get_raz_id_reg,			\
	.set_user = set_raz_id_reg,			\
पूर्ण

/*
 * sys_reg_desc initialiser क्रम known ID रेजिस्टरs that we hide from guests.
 * For now, these are exposed just like unallocated ID regs: they appear
 * RAZ क्रम the guest.
 */
#घोषणा ID_HIDDEN(name) अणु			\
	SYS_DESC(SYS_##name),			\
	.access = access_raz_id_reg,		\
	.get_user = get_raz_id_reg,		\
	.set_user = set_raz_id_reg,		\
पूर्ण

/*
 * Architected प्रणाली रेजिस्टरs.
 * Important: Must be sorted ascending by Op0, Op1, CRn, CRm, Op2
 *
 * Debug handling: We करो trap most, अगर not all debug related प्रणाली
 * रेजिस्टरs. The implementation is good enough to ensure that a guest
 * can use these with minimal perक्रमmance degradation. The drawback is
 * that we करोn't implement any of the बाह्यal debug, none of the
 * OSlock protocol. This should be revisited अगर we ever encounter a
 * more demanding guest...
 */
अटल स्थिर काष्ठा sys_reg_desc sys_reg_descs[] = अणु
	अणु SYS_DESC(SYS_DC_ISW), access_dcsw पूर्ण,
	अणु SYS_DESC(SYS_DC_CSW), access_dcsw पूर्ण,
	अणु SYS_DESC(SYS_DC_CISW), access_dcsw पूर्ण,

	DBG_BCR_BVR_WCR_WVR_EL1(0),
	DBG_BCR_BVR_WCR_WVR_EL1(1),
	अणु SYS_DESC(SYS_MDCCINT_EL1), trap_debug_regs, reset_val, MDCCINT_EL1, 0 पूर्ण,
	अणु SYS_DESC(SYS_MDSCR_EL1), trap_debug_regs, reset_val, MDSCR_EL1, 0 पूर्ण,
	DBG_BCR_BVR_WCR_WVR_EL1(2),
	DBG_BCR_BVR_WCR_WVR_EL1(3),
	DBG_BCR_BVR_WCR_WVR_EL1(4),
	DBG_BCR_BVR_WCR_WVR_EL1(5),
	DBG_BCR_BVR_WCR_WVR_EL1(6),
	DBG_BCR_BVR_WCR_WVR_EL1(7),
	DBG_BCR_BVR_WCR_WVR_EL1(8),
	DBG_BCR_BVR_WCR_WVR_EL1(9),
	DBG_BCR_BVR_WCR_WVR_EL1(10),
	DBG_BCR_BVR_WCR_WVR_EL1(11),
	DBG_BCR_BVR_WCR_WVR_EL1(12),
	DBG_BCR_BVR_WCR_WVR_EL1(13),
	DBG_BCR_BVR_WCR_WVR_EL1(14),
	DBG_BCR_BVR_WCR_WVR_EL1(15),

	अणु SYS_DESC(SYS_MDRAR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_OSLAR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_OSLSR_EL1), trap_oslsr_el1 पूर्ण,
	अणु SYS_DESC(SYS_OSDLR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_DBGPRCR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_DBGCLAIMSET_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_DBGCLAIMCLR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_DBGAUTHSTATUS_EL1), trap_dbgauthstatus_el1 पूर्ण,

	अणु SYS_DESC(SYS_MDCCSR_EL0), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_DBGDTR_EL0), trap_raz_wi पूर्ण,
	// DBGDTR[TR]X_EL0 share the same encoding
	अणु SYS_DESC(SYS_DBGDTRTX_EL0), trap_raz_wi पूर्ण,

	अणु SYS_DESC(SYS_DBGVCR32_EL2), शून्य, reset_val, DBGVCR32_EL2, 0 पूर्ण,

	अणु SYS_DESC(SYS_MPIDR_EL1), शून्य, reset_mpidr, MPIDR_EL1 पूर्ण,

	/*
	 * ID regs: all ID_SANITISED() entries here must have corresponding
	 * entries in arm64_ftr_regs[].
	 */

	/* AArch64 mappings of the AArch32 ID रेजिस्टरs */
	/* CRm=1 */
	ID_SANITISED(ID_PFR0_EL1),
	ID_SANITISED(ID_PFR1_EL1),
	ID_SANITISED(ID_DFR0_EL1),
	ID_HIDDEN(ID_AFR0_EL1),
	ID_SANITISED(ID_MMFR0_EL1),
	ID_SANITISED(ID_MMFR1_EL1),
	ID_SANITISED(ID_MMFR2_EL1),
	ID_SANITISED(ID_MMFR3_EL1),

	/* CRm=2 */
	ID_SANITISED(ID_ISAR0_EL1),
	ID_SANITISED(ID_ISAR1_EL1),
	ID_SANITISED(ID_ISAR2_EL1),
	ID_SANITISED(ID_ISAR3_EL1),
	ID_SANITISED(ID_ISAR4_EL1),
	ID_SANITISED(ID_ISAR5_EL1),
	ID_SANITISED(ID_MMFR4_EL1),
	ID_SANITISED(ID_ISAR6_EL1),

	/* CRm=3 */
	ID_SANITISED(MVFR0_EL1),
	ID_SANITISED(MVFR1_EL1),
	ID_SANITISED(MVFR2_EL1),
	ID_UNALLOCATED(3,3),
	ID_SANITISED(ID_PFR2_EL1),
	ID_HIDDEN(ID_DFR1_EL1),
	ID_SANITISED(ID_MMFR5_EL1),
	ID_UNALLOCATED(3,7),

	/* AArch64 ID रेजिस्टरs */
	/* CRm=4 */
	अणु SYS_DESC(SYS_ID_AA64PFR0_EL1), .access = access_id_reg,
	  .get_user = get_id_reg, .set_user = set_id_aa64pfr0_el1, पूर्ण,
	ID_SANITISED(ID_AA64PFR1_EL1),
	ID_UNALLOCATED(4,2),
	ID_UNALLOCATED(4,3),
	ID_SANITISED(ID_AA64ZFR0_EL1),
	ID_UNALLOCATED(4,5),
	ID_UNALLOCATED(4,6),
	ID_UNALLOCATED(4,7),

	/* CRm=5 */
	ID_SANITISED(ID_AA64DFR0_EL1),
	ID_SANITISED(ID_AA64DFR1_EL1),
	ID_UNALLOCATED(5,2),
	ID_UNALLOCATED(5,3),
	ID_HIDDEN(ID_AA64AFR0_EL1),
	ID_HIDDEN(ID_AA64AFR1_EL1),
	ID_UNALLOCATED(5,6),
	ID_UNALLOCATED(5,7),

	/* CRm=6 */
	ID_SANITISED(ID_AA64ISAR0_EL1),
	ID_SANITISED(ID_AA64ISAR1_EL1),
	ID_UNALLOCATED(6,2),
	ID_UNALLOCATED(6,3),
	ID_UNALLOCATED(6,4),
	ID_UNALLOCATED(6,5),
	ID_UNALLOCATED(6,6),
	ID_UNALLOCATED(6,7),

	/* CRm=7 */
	ID_SANITISED(ID_AA64MMFR0_EL1),
	ID_SANITISED(ID_AA64MMFR1_EL1),
	ID_SANITISED(ID_AA64MMFR2_EL1),
	ID_UNALLOCATED(7,3),
	ID_UNALLOCATED(7,4),
	ID_UNALLOCATED(7,5),
	ID_UNALLOCATED(7,6),
	ID_UNALLOCATED(7,7),

	अणु SYS_DESC(SYS_SCTLR_EL1), access_vm_reg, reset_val, SCTLR_EL1, 0x00C50078 पूर्ण,
	अणु SYS_DESC(SYS_ACTLR_EL1), access_actlr, reset_actlr, ACTLR_EL1 पूर्ण,
	अणु SYS_DESC(SYS_CPACR_EL1), शून्य, reset_val, CPACR_EL1, 0 पूर्ण,

	अणु SYS_DESC(SYS_RGSR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_GCR_EL1), undef_access पूर्ण,

	अणु SYS_DESC(SYS_ZCR_EL1), शून्य, reset_val, ZCR_EL1, 0, .visibility = sve_visibility पूर्ण,
	अणु SYS_DESC(SYS_TRFCR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_TTBR0_EL1), access_vm_reg, reset_unknown, TTBR0_EL1 पूर्ण,
	अणु SYS_DESC(SYS_TTBR1_EL1), access_vm_reg, reset_unknown, TTBR1_EL1 पूर्ण,
	अणु SYS_DESC(SYS_TCR_EL1), access_vm_reg, reset_val, TCR_EL1, 0 पूर्ण,

	PTRAUTH_KEY(APIA),
	PTRAUTH_KEY(APIB),
	PTRAUTH_KEY(APDA),
	PTRAUTH_KEY(APDB),
	PTRAUTH_KEY(APGA),

	अणु SYS_DESC(SYS_AFSR0_EL1), access_vm_reg, reset_unknown, AFSR0_EL1 पूर्ण,
	अणु SYS_DESC(SYS_AFSR1_EL1), access_vm_reg, reset_unknown, AFSR1_EL1 पूर्ण,
	अणु SYS_DESC(SYS_ESR_EL1), access_vm_reg, reset_unknown, ESR_EL1 पूर्ण,

	अणु SYS_DESC(SYS_ERRIDR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_ERRSELR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_ERXFR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_ERXCTLR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_ERXSTATUS_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_ERXADDR_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_ERXMISC0_EL1), trap_raz_wi पूर्ण,
	अणु SYS_DESC(SYS_ERXMISC1_EL1), trap_raz_wi पूर्ण,

	अणु SYS_DESC(SYS_TFSR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_TFSRE0_EL1), undef_access पूर्ण,

	अणु SYS_DESC(SYS_FAR_EL1), access_vm_reg, reset_unknown, FAR_EL1 पूर्ण,
	अणु SYS_DESC(SYS_PAR_EL1), शून्य, reset_unknown, PAR_EL1 पूर्ण,

	अणु SYS_DESC(SYS_PMSCR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMSNEVFR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMSICR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMSIRR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMSFCR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMSEVFR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMSLATFR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMSIDR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMBLIMITR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMBPTR_EL1), undef_access पूर्ण,
	अणु SYS_DESC(SYS_PMBSR_EL1), undef_access पूर्ण,
	/* PMBIDR_EL1 is not trapped */

	अणु PMU_SYS_REG(SYS_PMINTENSET_EL1),
	  .access = access_pmपूर्णांकen, .reg = PMINTENSET_EL1 पूर्ण,
	अणु PMU_SYS_REG(SYS_PMINTENCLR_EL1),
	  .access = access_pmपूर्णांकen, .reg = PMINTENSET_EL1 पूर्ण,
	अणु SYS_DESC(SYS_PMMIR_EL1), trap_raz_wi पूर्ण,

	अणु SYS_DESC(SYS_MAIR_EL1), access_vm_reg, reset_unknown, MAIR_EL1 पूर्ण,
	अणु SYS_DESC(SYS_AMAIR_EL1), access_vm_reg, reset_amair_el1, AMAIR_EL1 पूर्ण,

	अणु SYS_DESC(SYS_LORSA_EL1), trap_loregion पूर्ण,
	अणु SYS_DESC(SYS_LOREA_EL1), trap_loregion पूर्ण,
	अणु SYS_DESC(SYS_LORN_EL1), trap_loregion पूर्ण,
	अणु SYS_DESC(SYS_LORC_EL1), trap_loregion पूर्ण,
	अणु SYS_DESC(SYS_LORID_EL1), trap_loregion पूर्ण,

	अणु SYS_DESC(SYS_VBAR_EL1), शून्य, reset_val, VBAR_EL1, 0 पूर्ण,
	अणु SYS_DESC(SYS_DISR_EL1), शून्य, reset_val, DISR_EL1, 0 पूर्ण,

	अणु SYS_DESC(SYS_ICC_IAR0_EL1), ग_लिखो_to_पढ़ो_only पूर्ण,
	अणु SYS_DESC(SYS_ICC_EOIR0_EL1), पढ़ो_from_ग_लिखो_only पूर्ण,
	अणु SYS_DESC(SYS_ICC_HPPIR0_EL1), ग_लिखो_to_पढ़ो_only पूर्ण,
	अणु SYS_DESC(SYS_ICC_सूची_EL1), पढ़ो_from_ग_लिखो_only पूर्ण,
	अणु SYS_DESC(SYS_ICC_RPR_EL1), ग_लिखो_to_पढ़ो_only पूर्ण,
	अणु SYS_DESC(SYS_ICC_SGI1R_EL1), access_gic_sgi पूर्ण,
	अणु SYS_DESC(SYS_ICC_ASGI1R_EL1), access_gic_sgi पूर्ण,
	अणु SYS_DESC(SYS_ICC_SGI0R_EL1), access_gic_sgi पूर्ण,
	अणु SYS_DESC(SYS_ICC_IAR1_EL1), ग_लिखो_to_पढ़ो_only पूर्ण,
	अणु SYS_DESC(SYS_ICC_EOIR1_EL1), पढ़ो_from_ग_लिखो_only पूर्ण,
	अणु SYS_DESC(SYS_ICC_HPPIR1_EL1), ग_लिखो_to_पढ़ो_only पूर्ण,
	अणु SYS_DESC(SYS_ICC_SRE_EL1), access_gic_sre पूर्ण,

	अणु SYS_DESC(SYS_CONTEXTIDR_EL1), access_vm_reg, reset_val, CONTEXTIDR_EL1, 0 पूर्ण,
	अणु SYS_DESC(SYS_TPIDR_EL1), शून्य, reset_unknown, TPIDR_EL1 पूर्ण,

	अणु SYS_DESC(SYS_SCXTNUM_EL1), undef_access पूर्ण,

	अणु SYS_DESC(SYS_CNTKCTL_EL1), शून्य, reset_val, CNTKCTL_EL1, 0पूर्ण,

	अणु SYS_DESC(SYS_CCSIDR_EL1), access_ccsidr पूर्ण,
	अणु SYS_DESC(SYS_CLIDR_EL1), access_clidr पूर्ण,
	अणु SYS_DESC(SYS_CSSELR_EL1), access_csselr, reset_unknown, CSSELR_EL1 पूर्ण,
	अणु SYS_DESC(SYS_CTR_EL0), access_ctr पूर्ण,

	अणु PMU_SYS_REG(SYS_PMCR_EL0), .access = access_pmcr,
	  .reset = reset_pmcr, .reg = PMCR_EL0 पूर्ण,
	अणु PMU_SYS_REG(SYS_PMCNTENSET_EL0),
	  .access = access_pmcnten, .reg = PMCNTENSET_EL0 पूर्ण,
	अणु PMU_SYS_REG(SYS_PMCNTENCLR_EL0),
	  .access = access_pmcnten, .reg = PMCNTENSET_EL0 पूर्ण,
	अणु PMU_SYS_REG(SYS_PMOVSCLR_EL0),
	  .access = access_pmovs, .reg = PMOVSSET_EL0 पूर्ण,
	अणु PMU_SYS_REG(SYS_PMSWINC_EL0),
	  .access = access_pmswinc, .reg = PMSWINC_EL0 पूर्ण,
	अणु PMU_SYS_REG(SYS_PMSELR_EL0),
	  .access = access_pmselr, .reg = PMSELR_EL0 पूर्ण,
	अणु PMU_SYS_REG(SYS_PMCEID0_EL0),
	  .access = access_pmceid, .reset = शून्य पूर्ण,
	अणु PMU_SYS_REG(SYS_PMCEID1_EL0),
	  .access = access_pmceid, .reset = शून्य पूर्ण,
	अणु PMU_SYS_REG(SYS_PMCCNTR_EL0),
	  .access = access_pmu_evcntr, .reg = PMCCNTR_EL0 पूर्ण,
	अणु PMU_SYS_REG(SYS_PMXEVTYPER_EL0),
	  .access = access_pmu_evtyper, .reset = शून्य पूर्ण,
	अणु PMU_SYS_REG(SYS_PMXEVCNTR_EL0),
	  .access = access_pmu_evcntr, .reset = शून्य पूर्ण,
	/*
	 * PMUSERENR_EL0 resets as unknown in 64bit mode जबतक it resets as zero
	 * in 32bit mode. Here we choose to reset it as zero क्रम consistency.
	 */
	अणु PMU_SYS_REG(SYS_PMUSERENR_EL0), .access = access_pmuserenr,
	  .reset = reset_val, .reg = PMUSERENR_EL0, .val = 0 पूर्ण,
	अणु PMU_SYS_REG(SYS_PMOVSSET_EL0),
	  .access = access_pmovs, .reg = PMOVSSET_EL0 पूर्ण,

	अणु SYS_DESC(SYS_TPIDR_EL0), शून्य, reset_unknown, TPIDR_EL0 पूर्ण,
	अणु SYS_DESC(SYS_TPIDRRO_EL0), शून्य, reset_unknown, TPIDRRO_EL0 पूर्ण,

	अणु SYS_DESC(SYS_SCXTNUM_EL0), undef_access पूर्ण,

	अणु SYS_DESC(SYS_AMCR_EL0), undef_access पूर्ण,
	अणु SYS_DESC(SYS_AMCFGR_EL0), undef_access पूर्ण,
	अणु SYS_DESC(SYS_AMCGCR_EL0), undef_access पूर्ण,
	अणु SYS_DESC(SYS_AMUSERENR_EL0), undef_access पूर्ण,
	अणु SYS_DESC(SYS_AMCNTENCLR0_EL0), undef_access पूर्ण,
	अणु SYS_DESC(SYS_AMCNTENSET0_EL0), undef_access पूर्ण,
	अणु SYS_DESC(SYS_AMCNTENCLR1_EL0), undef_access पूर्ण,
	अणु SYS_DESC(SYS_AMCNTENSET1_EL0), undef_access पूर्ण,
	AMU_AMEVCNTR0_EL0(0),
	AMU_AMEVCNTR0_EL0(1),
	AMU_AMEVCNTR0_EL0(2),
	AMU_AMEVCNTR0_EL0(3),
	AMU_AMEVCNTR0_EL0(4),
	AMU_AMEVCNTR0_EL0(5),
	AMU_AMEVCNTR0_EL0(6),
	AMU_AMEVCNTR0_EL0(7),
	AMU_AMEVCNTR0_EL0(8),
	AMU_AMEVCNTR0_EL0(9),
	AMU_AMEVCNTR0_EL0(10),
	AMU_AMEVCNTR0_EL0(11),
	AMU_AMEVCNTR0_EL0(12),
	AMU_AMEVCNTR0_EL0(13),
	AMU_AMEVCNTR0_EL0(14),
	AMU_AMEVCNTR0_EL0(15),
	AMU_AMEVTYPER0_EL0(0),
	AMU_AMEVTYPER0_EL0(1),
	AMU_AMEVTYPER0_EL0(2),
	AMU_AMEVTYPER0_EL0(3),
	AMU_AMEVTYPER0_EL0(4),
	AMU_AMEVTYPER0_EL0(5),
	AMU_AMEVTYPER0_EL0(6),
	AMU_AMEVTYPER0_EL0(7),
	AMU_AMEVTYPER0_EL0(8),
	AMU_AMEVTYPER0_EL0(9),
	AMU_AMEVTYPER0_EL0(10),
	AMU_AMEVTYPER0_EL0(11),
	AMU_AMEVTYPER0_EL0(12),
	AMU_AMEVTYPER0_EL0(13),
	AMU_AMEVTYPER0_EL0(14),
	AMU_AMEVTYPER0_EL0(15),
	AMU_AMEVCNTR1_EL0(0),
	AMU_AMEVCNTR1_EL0(1),
	AMU_AMEVCNTR1_EL0(2),
	AMU_AMEVCNTR1_EL0(3),
	AMU_AMEVCNTR1_EL0(4),
	AMU_AMEVCNTR1_EL0(5),
	AMU_AMEVCNTR1_EL0(6),
	AMU_AMEVCNTR1_EL0(7),
	AMU_AMEVCNTR1_EL0(8),
	AMU_AMEVCNTR1_EL0(9),
	AMU_AMEVCNTR1_EL0(10),
	AMU_AMEVCNTR1_EL0(11),
	AMU_AMEVCNTR1_EL0(12),
	AMU_AMEVCNTR1_EL0(13),
	AMU_AMEVCNTR1_EL0(14),
	AMU_AMEVCNTR1_EL0(15),
	AMU_AMEVTYPER1_EL0(0),
	AMU_AMEVTYPER1_EL0(1),
	AMU_AMEVTYPER1_EL0(2),
	AMU_AMEVTYPER1_EL0(3),
	AMU_AMEVTYPER1_EL0(4),
	AMU_AMEVTYPER1_EL0(5),
	AMU_AMEVTYPER1_EL0(6),
	AMU_AMEVTYPER1_EL0(7),
	AMU_AMEVTYPER1_EL0(8),
	AMU_AMEVTYPER1_EL0(9),
	AMU_AMEVTYPER1_EL0(10),
	AMU_AMEVTYPER1_EL0(11),
	AMU_AMEVTYPER1_EL0(12),
	AMU_AMEVTYPER1_EL0(13),
	AMU_AMEVTYPER1_EL0(14),
	AMU_AMEVTYPER1_EL0(15),

	अणु SYS_DESC(SYS_CNTP_TVAL_EL0), access_arch_समयr पूर्ण,
	अणु SYS_DESC(SYS_CNTP_CTL_EL0), access_arch_समयr पूर्ण,
	अणु SYS_DESC(SYS_CNTP_CVAL_EL0), access_arch_समयr पूर्ण,

	/* PMEVCNTRn_EL0 */
	PMU_PMEVCNTR_EL0(0),
	PMU_PMEVCNTR_EL0(1),
	PMU_PMEVCNTR_EL0(2),
	PMU_PMEVCNTR_EL0(3),
	PMU_PMEVCNTR_EL0(4),
	PMU_PMEVCNTR_EL0(5),
	PMU_PMEVCNTR_EL0(6),
	PMU_PMEVCNTR_EL0(7),
	PMU_PMEVCNTR_EL0(8),
	PMU_PMEVCNTR_EL0(9),
	PMU_PMEVCNTR_EL0(10),
	PMU_PMEVCNTR_EL0(11),
	PMU_PMEVCNTR_EL0(12),
	PMU_PMEVCNTR_EL0(13),
	PMU_PMEVCNTR_EL0(14),
	PMU_PMEVCNTR_EL0(15),
	PMU_PMEVCNTR_EL0(16),
	PMU_PMEVCNTR_EL0(17),
	PMU_PMEVCNTR_EL0(18),
	PMU_PMEVCNTR_EL0(19),
	PMU_PMEVCNTR_EL0(20),
	PMU_PMEVCNTR_EL0(21),
	PMU_PMEVCNTR_EL0(22),
	PMU_PMEVCNTR_EL0(23),
	PMU_PMEVCNTR_EL0(24),
	PMU_PMEVCNTR_EL0(25),
	PMU_PMEVCNTR_EL0(26),
	PMU_PMEVCNTR_EL0(27),
	PMU_PMEVCNTR_EL0(28),
	PMU_PMEVCNTR_EL0(29),
	PMU_PMEVCNTR_EL0(30),
	/* PMEVTYPERn_EL0 */
	PMU_PMEVTYPER_EL0(0),
	PMU_PMEVTYPER_EL0(1),
	PMU_PMEVTYPER_EL0(2),
	PMU_PMEVTYPER_EL0(3),
	PMU_PMEVTYPER_EL0(4),
	PMU_PMEVTYPER_EL0(5),
	PMU_PMEVTYPER_EL0(6),
	PMU_PMEVTYPER_EL0(7),
	PMU_PMEVTYPER_EL0(8),
	PMU_PMEVTYPER_EL0(9),
	PMU_PMEVTYPER_EL0(10),
	PMU_PMEVTYPER_EL0(11),
	PMU_PMEVTYPER_EL0(12),
	PMU_PMEVTYPER_EL0(13),
	PMU_PMEVTYPER_EL0(14),
	PMU_PMEVTYPER_EL0(15),
	PMU_PMEVTYPER_EL0(16),
	PMU_PMEVTYPER_EL0(17),
	PMU_PMEVTYPER_EL0(18),
	PMU_PMEVTYPER_EL0(19),
	PMU_PMEVTYPER_EL0(20),
	PMU_PMEVTYPER_EL0(21),
	PMU_PMEVTYPER_EL0(22),
	PMU_PMEVTYPER_EL0(23),
	PMU_PMEVTYPER_EL0(24),
	PMU_PMEVTYPER_EL0(25),
	PMU_PMEVTYPER_EL0(26),
	PMU_PMEVTYPER_EL0(27),
	PMU_PMEVTYPER_EL0(28),
	PMU_PMEVTYPER_EL0(29),
	PMU_PMEVTYPER_EL0(30),
	/*
	 * PMCCFILTR_EL0 resets as unknown in 64bit mode जबतक it resets as zero
	 * in 32bit mode. Here we choose to reset it as zero क्रम consistency.
	 */
	अणु PMU_SYS_REG(SYS_PMCCFILTR_EL0), .access = access_pmu_evtyper,
	  .reset = reset_val, .reg = PMCCFILTR_EL0, .val = 0 पूर्ण,

	अणु SYS_DESC(SYS_DACR32_EL2), शून्य, reset_unknown, DACR32_EL2 पूर्ण,
	अणु SYS_DESC(SYS_IFSR32_EL2), शून्य, reset_unknown, IFSR32_EL2 पूर्ण,
	अणु SYS_DESC(SYS_FPEXC32_EL2), शून्य, reset_val, FPEXC32_EL2, 0x700 पूर्ण,
पूर्ण;

अटल bool trap_dbgdidr(काष्ठा kvm_vcpu *vcpu,
			काष्ठा sys_reg_params *p,
			स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (p->is_ग_लिखो) अणु
		वापस ignore_ग_लिखो(vcpu, p);
	पूर्ण अन्यथा अणु
		u64 dfr = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64DFR0_EL1);
		u64 pfr = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64PFR0_EL1);
		u32 el3 = !!cpuid_feature_extract_अचिन्हित_field(pfr, ID_AA64PFR0_EL3_SHIFT);

		p->regval = ((((dfr >> ID_AA64DFR0_WRPS_SHIFT) & 0xf) << 28) |
			     (((dfr >> ID_AA64DFR0_BRPS_SHIFT) & 0xf) << 24) |
			     (((dfr >> ID_AA64DFR0_CTX_CMPS_SHIFT) & 0xf) << 20)
			     | (6 << 16) | (1 << 15) | (el3 << 14) | (el3 << 12));
		वापस true;
	पूर्ण
पूर्ण

/*
 * AArch32 debug रेजिस्टर mappings
 *
 * AArch32 DBGBVRn is mapped to DBGBVRn_EL1[31:0]
 * AArch32 DBGBXVRn is mapped to DBGBVRn_EL1[63:32]
 *
 * None of the other रेजिस्टरs share their location, so treat them as
 * अगर they were 64bit.
 */
#घोषणा DBG_BCR_BVR_WCR_WVR(n)						      \
	/* DBGBVRn */							      \
	अणु AA32(LO), Op1( 0), CRn( 0), CRm((n)), Op2( 4), trap_bvr, शून्य, n पूर्ण, \
	/* DBGBCRn */							      \
	अणु Op1( 0), CRn( 0), CRm((n)), Op2( 5), trap_bcr, शून्य, n पूर्ण,	      \
	/* DBGWVRn */							      \
	अणु Op1( 0), CRn( 0), CRm((n)), Op2( 6), trap_wvr, शून्य, n पूर्ण,	      \
	/* DBGWCRn */							      \
	अणु Op1( 0), CRn( 0), CRm((n)), Op2( 7), trap_wcr, शून्य, n पूर्ण

#घोषणा DBGBXVR(n)							      \
	अणु AA32(HI), Op1( 0), CRn( 1), CRm((n)), Op2( 1), trap_bvr, शून्य, n पूर्ण

/*
 * Trapped cp14 रेजिस्टरs. We generally ignore most of the बाह्यal
 * debug, on the principle that they करोn't really make sense to a
 * guest. Revisit this one day, would this principle change.
 */
अटल स्थिर काष्ठा sys_reg_desc cp14_regs[] = अणु
	/* DBGDIDR */
	अणु Op1( 0), CRn( 0), CRm( 0), Op2( 0), trap_dbgdidr पूर्ण,
	/* DBGDTRRXext */
	अणु Op1( 0), CRn( 0), CRm( 0), Op2( 2), trap_raz_wi पूर्ण,

	DBG_BCR_BVR_WCR_WVR(0),
	/* DBGDSCRपूर्णांक */
	अणु Op1( 0), CRn( 0), CRm( 1), Op2( 0), trap_raz_wi पूर्ण,
	DBG_BCR_BVR_WCR_WVR(1),
	/* DBGDCCINT */
	अणु Op1( 0), CRn( 0), CRm( 2), Op2( 0), trap_debug_regs, शून्य, MDCCINT_EL1 पूर्ण,
	/* DBGDSCRext */
	अणु Op1( 0), CRn( 0), CRm( 2), Op2( 2), trap_debug_regs, शून्य, MDSCR_EL1 पूर्ण,
	DBG_BCR_BVR_WCR_WVR(2),
	/* DBGDTR[RT]Xपूर्णांक */
	अणु Op1( 0), CRn( 0), CRm( 3), Op2( 0), trap_raz_wi पूर्ण,
	/* DBGDTR[RT]Xext */
	अणु Op1( 0), CRn( 0), CRm( 3), Op2( 2), trap_raz_wi पूर्ण,
	DBG_BCR_BVR_WCR_WVR(3),
	DBG_BCR_BVR_WCR_WVR(4),
	DBG_BCR_BVR_WCR_WVR(5),
	/* DBGWFAR */
	अणु Op1( 0), CRn( 0), CRm( 6), Op2( 0), trap_raz_wi पूर्ण,
	/* DBGOSECCR */
	अणु Op1( 0), CRn( 0), CRm( 6), Op2( 2), trap_raz_wi पूर्ण,
	DBG_BCR_BVR_WCR_WVR(6),
	/* DBGVCR */
	अणु Op1( 0), CRn( 0), CRm( 7), Op2( 0), trap_debug_regs, शून्य, DBGVCR32_EL2 पूर्ण,
	DBG_BCR_BVR_WCR_WVR(7),
	DBG_BCR_BVR_WCR_WVR(8),
	DBG_BCR_BVR_WCR_WVR(9),
	DBG_BCR_BVR_WCR_WVR(10),
	DBG_BCR_BVR_WCR_WVR(11),
	DBG_BCR_BVR_WCR_WVR(12),
	DBG_BCR_BVR_WCR_WVR(13),
	DBG_BCR_BVR_WCR_WVR(14),
	DBG_BCR_BVR_WCR_WVR(15),

	/* DBGDRAR (32bit) */
	अणु Op1( 0), CRn( 1), CRm( 0), Op2( 0), trap_raz_wi पूर्ण,

	DBGBXVR(0),
	/* DBGOSLAR */
	अणु Op1( 0), CRn( 1), CRm( 0), Op2( 4), trap_raz_wi पूर्ण,
	DBGBXVR(1),
	/* DBGOSLSR */
	अणु Op1( 0), CRn( 1), CRm( 1), Op2( 4), trap_oslsr_el1 पूर्ण,
	DBGBXVR(2),
	DBGBXVR(3),
	/* DBGOSDLR */
	अणु Op1( 0), CRn( 1), CRm( 3), Op2( 4), trap_raz_wi पूर्ण,
	DBGBXVR(4),
	/* DBGPRCR */
	अणु Op1( 0), CRn( 1), CRm( 4), Op2( 4), trap_raz_wi पूर्ण,
	DBGBXVR(5),
	DBGBXVR(6),
	DBGBXVR(7),
	DBGBXVR(8),
	DBGBXVR(9),
	DBGBXVR(10),
	DBGBXVR(11),
	DBGBXVR(12),
	DBGBXVR(13),
	DBGBXVR(14),
	DBGBXVR(15),

	/* DBGDSAR (32bit) */
	अणु Op1( 0), CRn( 2), CRm( 0), Op2( 0), trap_raz_wi पूर्ण,

	/* DBGDEVID2 */
	अणु Op1( 0), CRn( 7), CRm( 0), Op2( 7), trap_raz_wi पूर्ण,
	/* DBGDEVID1 */
	अणु Op1( 0), CRn( 7), CRm( 1), Op2( 7), trap_raz_wi पूर्ण,
	/* DBGDEVID */
	अणु Op1( 0), CRn( 7), CRm( 2), Op2( 7), trap_raz_wi पूर्ण,
	/* DBGCLAIMSET */
	अणु Op1( 0), CRn( 7), CRm( 8), Op2( 6), trap_raz_wi पूर्ण,
	/* DBGCLAIMCLR */
	अणु Op1( 0), CRn( 7), CRm( 9), Op2( 6), trap_raz_wi पूर्ण,
	/* DBGAUTHSTATUS */
	अणु Op1( 0), CRn( 7), CRm(14), Op2( 6), trap_dbgauthstatus_el1 पूर्ण,
पूर्ण;

/* Trapped cp14 64bit रेजिस्टरs */
अटल स्थिर काष्ठा sys_reg_desc cp14_64_regs[] = अणु
	/* DBGDRAR (64bit) */
	अणु Op1( 0), CRm( 1), .access = trap_raz_wi पूर्ण,

	/* DBGDSAR (64bit) */
	अणु Op1( 0), CRm( 2), .access = trap_raz_wi पूर्ण,
पूर्ण;

/* Macro to expand the PMEVCNTRn रेजिस्टर */
#घोषणा PMU_PMEVCNTR(n)							\
	/* PMEVCNTRn */							\
	अणु Op1(0), CRn(0b1110),						\
	  CRm((0b1000 | (((n) >> 3) & 0x3))), Op2(((n) & 0x7)),		\
	  access_pmu_evcntr पूर्ण

/* Macro to expand the PMEVTYPERn रेजिस्टर */
#घोषणा PMU_PMEVTYPER(n)						\
	/* PMEVTYPERn */						\
	अणु Op1(0), CRn(0b1110),						\
	  CRm((0b1100 | (((n) >> 3) & 0x3))), Op2(((n) & 0x7)),		\
	  access_pmu_evtyper पूर्ण

/*
 * Trapped cp15 रेजिस्टरs. TTBR0/TTBR1 get a द्विगुन encoding,
 * depending on the way they are accessed (as a 32bit or a 64bit
 * रेजिस्टर).
 */
अटल स्थिर काष्ठा sys_reg_desc cp15_regs[] = अणु
	अणु Op1( 0), CRn( 0), CRm( 0), Op2( 1), access_ctr पूर्ण,
	अणु Op1( 0), CRn( 1), CRm( 0), Op2( 0), access_vm_reg, शून्य, SCTLR_EL1 पूर्ण,
	/* ACTLR */
	अणु AA32(LO), Op1( 0), CRn( 1), CRm( 0), Op2( 1), access_actlr, शून्य, ACTLR_EL1 पूर्ण,
	/* ACTLR2 */
	अणु AA32(HI), Op1( 0), CRn( 1), CRm( 0), Op2( 3), access_actlr, शून्य, ACTLR_EL1 पूर्ण,
	अणु Op1( 0), CRn( 2), CRm( 0), Op2( 0), access_vm_reg, शून्य, TTBR0_EL1 पूर्ण,
	अणु Op1( 0), CRn( 2), CRm( 0), Op2( 1), access_vm_reg, शून्य, TTBR1_EL1 पूर्ण,
	/* TTBCR */
	अणु AA32(LO), Op1( 0), CRn( 2), CRm( 0), Op2( 2), access_vm_reg, शून्य, TCR_EL1 पूर्ण,
	/* TTBCR2 */
	अणु AA32(HI), Op1( 0), CRn( 2), CRm( 0), Op2( 3), access_vm_reg, शून्य, TCR_EL1 पूर्ण,
	अणु Op1( 0), CRn( 3), CRm( 0), Op2( 0), access_vm_reg, शून्य, DACR32_EL2 पूर्ण,
	/* DFSR */
	अणु Op1( 0), CRn( 5), CRm( 0), Op2( 0), access_vm_reg, शून्य, ESR_EL1 पूर्ण,
	अणु Op1( 0), CRn( 5), CRm( 0), Op2( 1), access_vm_reg, शून्य, IFSR32_EL2 पूर्ण,
	/* ADFSR */
	अणु Op1( 0), CRn( 5), CRm( 1), Op2( 0), access_vm_reg, शून्य, AFSR0_EL1 पूर्ण,
	/* AIFSR */
	अणु Op1( 0), CRn( 5), CRm( 1), Op2( 1), access_vm_reg, शून्य, AFSR1_EL1 पूर्ण,
	/* DFAR */
	अणु AA32(LO), Op1( 0), CRn( 6), CRm( 0), Op2( 0), access_vm_reg, शून्य, FAR_EL1 पूर्ण,
	/* IFAR */
	अणु AA32(HI), Op1( 0), CRn( 6), CRm( 0), Op2( 2), access_vm_reg, शून्य, FAR_EL1 पूर्ण,

	/*
	 * DCअणुC,I,CIपूर्णSW operations:
	 */
	अणु Op1( 0), CRn( 7), CRm( 6), Op2( 2), access_dcsw पूर्ण,
	अणु Op1( 0), CRn( 7), CRm(10), Op2( 2), access_dcsw पूर्ण,
	अणु Op1( 0), CRn( 7), CRm(14), Op2( 2), access_dcsw पूर्ण,

	/* PMU */
	अणु Op1( 0), CRn( 9), CRm(12), Op2( 0), access_pmcr पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(12), Op2( 1), access_pmcnten पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(12), Op2( 2), access_pmcnten पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(12), Op2( 3), access_pmovs पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(12), Op2( 4), access_pmswinc पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(12), Op2( 5), access_pmselr पूर्ण,
	अणु AA32(LO), Op1( 0), CRn( 9), CRm(12), Op2( 6), access_pmceid पूर्ण,
	अणु AA32(LO), Op1( 0), CRn( 9), CRm(12), Op2( 7), access_pmceid पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(13), Op2( 0), access_pmu_evcntr पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(13), Op2( 1), access_pmu_evtyper पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(13), Op2( 2), access_pmu_evcntr पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(14), Op2( 0), access_pmuserenr पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(14), Op2( 1), access_pmपूर्णांकen पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(14), Op2( 2), access_pmपूर्णांकen पूर्ण,
	अणु Op1( 0), CRn( 9), CRm(14), Op2( 3), access_pmovs पूर्ण,
	अणु AA32(HI), Op1( 0), CRn( 9), CRm(14), Op2( 4), access_pmceid पूर्ण,
	अणु AA32(HI), Op1( 0), CRn( 9), CRm(14), Op2( 5), access_pmceid पूर्ण,
	/* PMMIR */
	अणु Op1( 0), CRn( 9), CRm(14), Op2( 6), trap_raz_wi पूर्ण,

	/* PRRR/MAIR0 */
	अणु AA32(LO), Op1( 0), CRn(10), CRm( 2), Op2( 0), access_vm_reg, शून्य, MAIR_EL1 पूर्ण,
	/* NMRR/MAIR1 */
	अणु AA32(HI), Op1( 0), CRn(10), CRm( 2), Op2( 1), access_vm_reg, शून्य, MAIR_EL1 पूर्ण,
	/* AMAIR0 */
	अणु AA32(LO), Op1( 0), CRn(10), CRm( 3), Op2( 0), access_vm_reg, शून्य, AMAIR_EL1 पूर्ण,
	/* AMAIR1 */
	अणु AA32(HI), Op1( 0), CRn(10), CRm( 3), Op2( 1), access_vm_reg, शून्य, AMAIR_EL1 पूर्ण,

	/* ICC_SRE */
	अणु Op1( 0), CRn(12), CRm(12), Op2( 5), access_gic_sre पूर्ण,

	अणु Op1( 0), CRn(13), CRm( 0), Op2( 1), access_vm_reg, शून्य, CONTEXTIDR_EL1 पूर्ण,

	/* Arch Tmers */
	अणु SYS_DESC(SYS_AARCH32_CNTP_TVAL), access_arch_समयr पूर्ण,
	अणु SYS_DESC(SYS_AARCH32_CNTP_CTL), access_arch_समयr पूर्ण,

	/* PMEVCNTRn */
	PMU_PMEVCNTR(0),
	PMU_PMEVCNTR(1),
	PMU_PMEVCNTR(2),
	PMU_PMEVCNTR(3),
	PMU_PMEVCNTR(4),
	PMU_PMEVCNTR(5),
	PMU_PMEVCNTR(6),
	PMU_PMEVCNTR(7),
	PMU_PMEVCNTR(8),
	PMU_PMEVCNTR(9),
	PMU_PMEVCNTR(10),
	PMU_PMEVCNTR(11),
	PMU_PMEVCNTR(12),
	PMU_PMEVCNTR(13),
	PMU_PMEVCNTR(14),
	PMU_PMEVCNTR(15),
	PMU_PMEVCNTR(16),
	PMU_PMEVCNTR(17),
	PMU_PMEVCNTR(18),
	PMU_PMEVCNTR(19),
	PMU_PMEVCNTR(20),
	PMU_PMEVCNTR(21),
	PMU_PMEVCNTR(22),
	PMU_PMEVCNTR(23),
	PMU_PMEVCNTR(24),
	PMU_PMEVCNTR(25),
	PMU_PMEVCNTR(26),
	PMU_PMEVCNTR(27),
	PMU_PMEVCNTR(28),
	PMU_PMEVCNTR(29),
	PMU_PMEVCNTR(30),
	/* PMEVTYPERn */
	PMU_PMEVTYPER(0),
	PMU_PMEVTYPER(1),
	PMU_PMEVTYPER(2),
	PMU_PMEVTYPER(3),
	PMU_PMEVTYPER(4),
	PMU_PMEVTYPER(5),
	PMU_PMEVTYPER(6),
	PMU_PMEVTYPER(7),
	PMU_PMEVTYPER(8),
	PMU_PMEVTYPER(9),
	PMU_PMEVTYPER(10),
	PMU_PMEVTYPER(11),
	PMU_PMEVTYPER(12),
	PMU_PMEVTYPER(13),
	PMU_PMEVTYPER(14),
	PMU_PMEVTYPER(15),
	PMU_PMEVTYPER(16),
	PMU_PMEVTYPER(17),
	PMU_PMEVTYPER(18),
	PMU_PMEVTYPER(19),
	PMU_PMEVTYPER(20),
	PMU_PMEVTYPER(21),
	PMU_PMEVTYPER(22),
	PMU_PMEVTYPER(23),
	PMU_PMEVTYPER(24),
	PMU_PMEVTYPER(25),
	PMU_PMEVTYPER(26),
	PMU_PMEVTYPER(27),
	PMU_PMEVTYPER(28),
	PMU_PMEVTYPER(29),
	PMU_PMEVTYPER(30),
	/* PMCCFILTR */
	अणु Op1(0), CRn(14), CRm(15), Op2(7), access_pmu_evtyper पूर्ण,

	अणु Op1(1), CRn( 0), CRm( 0), Op2(0), access_ccsidr पूर्ण,
	अणु Op1(1), CRn( 0), CRm( 0), Op2(1), access_clidr पूर्ण,
	अणु Op1(2), CRn( 0), CRm( 0), Op2(0), access_csselr, शून्य, CSSELR_EL1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sys_reg_desc cp15_64_regs[] = अणु
	अणु Op1( 0), CRn( 0), CRm( 2), Op2( 0), access_vm_reg, शून्य, TTBR0_EL1 पूर्ण,
	अणु Op1( 0), CRn( 0), CRm( 9), Op2( 0), access_pmu_evcntr पूर्ण,
	अणु Op1( 0), CRn( 0), CRm(12), Op2( 0), access_gic_sgi पूर्ण, /* ICC_SGI1R */
	अणु Op1( 1), CRn( 0), CRm( 2), Op2( 0), access_vm_reg, शून्य, TTBR1_EL1 पूर्ण,
	अणु Op1( 1), CRn( 0), CRm(12), Op2( 0), access_gic_sgi पूर्ण, /* ICC_ASGI1R */
	अणु Op1( 2), CRn( 0), CRm(12), Op2( 0), access_gic_sgi पूर्ण, /* ICC_SGI0R */
	अणु SYS_DESC(SYS_AARCH32_CNTP_CVAL),    access_arch_समयr पूर्ण,
पूर्ण;

अटल पूर्णांक check_sysreg_table(स्थिर काष्ठा sys_reg_desc *table, अचिन्हित पूर्णांक n,
			      bool is_32)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		अगर (!is_32 && table[i].reg && !table[i].reset) अणु
			kvm_err("sys_reg table %p entry %d has lacks reset\n",
				table, i);
			वापस 1;
		पूर्ण

		अगर (i && cmp_sys_reg(&table[i-1], &table[i]) >= 0) अणु
			kvm_err("sys_reg table %p out of order (%d)\n", table, i - 1);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक match_sys_reg(स्थिर व्योम *key, स्थिर व्योम *elt)
अणु
	स्थिर अचिन्हित दीर्घ pval = (अचिन्हित दीर्घ)key;
	स्थिर काष्ठा sys_reg_desc *r = elt;

	वापस pval - reg_to_encoding(r);
पूर्ण

अटल स्थिर काष्ठा sys_reg_desc *find_reg(स्थिर काष्ठा sys_reg_params *params,
					 स्थिर काष्ठा sys_reg_desc table[],
					 अचिन्हित पूर्णांक num)
अणु
	अचिन्हित दीर्घ pval = reg_to_encoding(params);

	वापस द्वा_खोज((व्योम *)pval, table, num, माप(table[0]), match_sys_reg);
पूर्ण

पूर्णांक kvm_handle_cp14_load_store(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_inject_undefined(vcpu);
	वापस 1;
पूर्ण

अटल व्योम perक्रमm_access(काष्ठा kvm_vcpu *vcpu,
			   काष्ठा sys_reg_params *params,
			   स्थिर काष्ठा sys_reg_desc *r)
अणु
	trace_kvm_sys_access(*vcpu_pc(vcpu), params, r);

	/* Check क्रम regs disabled by runसमय config */
	अगर (sysreg_hidden(vcpu, r)) अणु
		kvm_inject_undefined(vcpu);
		वापस;
	पूर्ण

	/*
	 * Not having an accessor means that we have configured a trap
	 * that we करोn't know how to handle. This certainly qualअगरies
	 * as a gross bug that should be fixed right away.
	 */
	BUG_ON(!r->access);

	/* Skip inकाष्ठाion अगर inकाष्ठाed so */
	अगर (likely(r->access(vcpu, params, r)))
		kvm_incr_pc(vcpu);
पूर्ण

/*
 * emulate_cp --  tries to match a sys_reg access in a handling table, and
 *                call the corresponding trap handler.
 *
 * @params: poपूर्णांकer to the descriptor of the access
 * @table: array of trap descriptors
 * @num: size of the trap descriptor array
 *
 * Return 0 अगर the access has been handled, and -1 अगर not.
 */
अटल पूर्णांक emulate_cp(काष्ठा kvm_vcpu *vcpu,
		      काष्ठा sys_reg_params *params,
		      स्थिर काष्ठा sys_reg_desc *table,
		      माप_प्रकार num)
अणु
	स्थिर काष्ठा sys_reg_desc *r;

	अगर (!table)
		वापस -1;	/* Not handled */

	r = find_reg(params, table, num);

	अगर (r) अणु
		perक्रमm_access(vcpu, params, r);
		वापस 0;
	पूर्ण

	/* Not handled */
	वापस -1;
पूर्ण

अटल व्योम unhandled_cp_access(काष्ठा kvm_vcpu *vcpu,
				काष्ठा sys_reg_params *params)
अणु
	u8 esr_ec = kvm_vcpu_trap_get_class(vcpu);
	पूर्णांक cp = -1;

	चयन (esr_ec) अणु
	हाल ESR_ELx_EC_CP15_32:
	हाल ESR_ELx_EC_CP15_64:
		cp = 15;
		अवरोध;
	हाल ESR_ELx_EC_CP14_MR:
	हाल ESR_ELx_EC_CP14_64:
		cp = 14;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	prपूर्णांक_sys_reg_msg(params,
			  "Unsupported guest CP%d access at: %08lx [%08lx]\n",
			  cp, *vcpu_pc(vcpu), *vcpu_cpsr(vcpu));
	kvm_inject_undefined(vcpu);
पूर्ण

/**
 * kvm_handle_cp_64 -- handles a mrrc/mcrr trap on a guest CP14/CP15 access
 * @vcpu: The VCPU poपूर्णांकer
 * @run:  The kvm_run काष्ठा
 */
अटल पूर्णांक kvm_handle_cp_64(काष्ठा kvm_vcpu *vcpu,
			    स्थिर काष्ठा sys_reg_desc *global,
			    माप_प्रकार nr_global)
अणु
	काष्ठा sys_reg_params params;
	u32 esr = kvm_vcpu_get_esr(vcpu);
	पूर्णांक Rt = kvm_vcpu_sys_get_rt(vcpu);
	पूर्णांक Rt2 = (esr >> 10) & 0x1f;

	params.CRm = (esr >> 1) & 0xf;
	params.is_ग_लिखो = ((esr & 1) == 0);

	params.Op0 = 0;
	params.Op1 = (esr >> 16) & 0xf;
	params.Op2 = 0;
	params.CRn = 0;

	/*
	 * Make a 64-bit value out of Rt and Rt2. As we use the same trap
	 * backends between AArch32 and AArch64, we get away with it.
	 */
	अगर (params.is_ग_लिखो) अणु
		params.regval = vcpu_get_reg(vcpu, Rt) & 0xffffffff;
		params.regval |= vcpu_get_reg(vcpu, Rt2) << 32;
	पूर्ण

	/*
	 * If the table contains a handler, handle the
	 * potential रेजिस्टर operation in the हाल of a पढ़ो and वापस
	 * with success.
	 */
	अगर (!emulate_cp(vcpu, &params, global, nr_global)) अणु
		/* Split up the value between रेजिस्टरs क्रम the पढ़ो side */
		अगर (!params.is_ग_लिखो) अणु
			vcpu_set_reg(vcpu, Rt, lower_32_bits(params.regval));
			vcpu_set_reg(vcpu, Rt2, upper_32_bits(params.regval));
		पूर्ण

		वापस 1;
	पूर्ण

	unhandled_cp_access(vcpu, &params);
	वापस 1;
पूर्ण

/**
 * kvm_handle_cp_32 -- handles a mrc/mcr trap on a guest CP14/CP15 access
 * @vcpu: The VCPU poपूर्णांकer
 * @run:  The kvm_run काष्ठा
 */
अटल पूर्णांक kvm_handle_cp_32(काष्ठा kvm_vcpu *vcpu,
			    स्थिर काष्ठा sys_reg_desc *global,
			    माप_प्रकार nr_global)
अणु
	काष्ठा sys_reg_params params;
	u32 esr = kvm_vcpu_get_esr(vcpu);
	पूर्णांक Rt  = kvm_vcpu_sys_get_rt(vcpu);

	params.CRm = (esr >> 1) & 0xf;
	params.regval = vcpu_get_reg(vcpu, Rt);
	params.is_ग_लिखो = ((esr & 1) == 0);
	params.CRn = (esr >> 10) & 0xf;
	params.Op0 = 0;
	params.Op1 = (esr >> 14) & 0x7;
	params.Op2 = (esr >> 17) & 0x7;

	अगर (!emulate_cp(vcpu, &params, global, nr_global)) अणु
		अगर (!params.is_ग_लिखो)
			vcpu_set_reg(vcpu, Rt, params.regval);
		वापस 1;
	पूर्ण

	unhandled_cp_access(vcpu, &params);
	वापस 1;
पूर्ण

पूर्णांक kvm_handle_cp15_64(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_handle_cp_64(vcpu, cp15_64_regs, ARRAY_SIZE(cp15_64_regs));
पूर्ण

पूर्णांक kvm_handle_cp15_32(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_handle_cp_32(vcpu, cp15_regs, ARRAY_SIZE(cp15_regs));
पूर्ण

पूर्णांक kvm_handle_cp14_64(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_handle_cp_64(vcpu, cp14_64_regs, ARRAY_SIZE(cp14_64_regs));
पूर्ण

पूर्णांक kvm_handle_cp14_32(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_handle_cp_32(vcpu, cp14_regs, ARRAY_SIZE(cp14_regs));
पूर्ण

अटल bool is_imp_def_sys_reg(काष्ठा sys_reg_params *params)
अणु
	// See ARM DDI 0487E.a, section D12.3.2
	वापस params->Op0 == 3 && (params->CRn & 0b1011) == 0b1011;
पूर्ण

अटल पूर्णांक emulate_sys_reg(काष्ठा kvm_vcpu *vcpu,
			   काष्ठा sys_reg_params *params)
अणु
	स्थिर काष्ठा sys_reg_desc *r;

	r = find_reg(params, sys_reg_descs, ARRAY_SIZE(sys_reg_descs));

	अगर (likely(r)) अणु
		perक्रमm_access(vcpu, params, r);
	पूर्ण अन्यथा अगर (is_imp_def_sys_reg(params)) अणु
		kvm_inject_undefined(vcpu);
	पूर्ण अन्यथा अणु
		prपूर्णांक_sys_reg_msg(params,
				  "Unsupported guest sys_reg access at: %lx [%08lx]\n",
				  *vcpu_pc(vcpu), *vcpu_cpsr(vcpu));
		kvm_inject_undefined(vcpu);
	पूर्ण
	वापस 1;
पूर्ण

/**
 * kvm_reset_sys_regs - sets प्रणाली रेजिस्टरs to reset value
 * @vcpu: The VCPU poपूर्णांकer
 *
 * This function finds the right table above and sets the रेजिस्टरs on the
 * भव CPU काष्ठा to their architecturally defined reset values.
 */
व्योम kvm_reset_sys_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < ARRAY_SIZE(sys_reg_descs); i++)
		अगर (sys_reg_descs[i].reset)
			sys_reg_descs[i].reset(vcpu, &sys_reg_descs[i]);
पूर्ण

/**
 * kvm_handle_sys_reg -- handles a mrs/msr trap on a guest sys_reg access
 * @vcpu: The VCPU poपूर्णांकer
 */
पूर्णांक kvm_handle_sys_reg(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा sys_reg_params params;
	अचिन्हित दीर्घ esr = kvm_vcpu_get_esr(vcpu);
	पूर्णांक Rt = kvm_vcpu_sys_get_rt(vcpu);
	पूर्णांक ret;

	trace_kvm_handle_sys_reg(esr);

	params.Op0 = (esr >> 20) & 3;
	params.Op1 = (esr >> 14) & 0x7;
	params.CRn = (esr >> 10) & 0xf;
	params.CRm = (esr >> 1) & 0xf;
	params.Op2 = (esr >> 17) & 0x7;
	params.regval = vcpu_get_reg(vcpu, Rt);
	params.is_ग_लिखो = !(esr & 1);

	ret = emulate_sys_reg(vcpu, &params);

	अगर (!params.is_ग_लिखो)
		vcpu_set_reg(vcpu, Rt, params.regval);
	वापस ret;
पूर्ण

/******************************************************************************
 * Userspace API
 *****************************************************************************/

अटल bool index_to_params(u64 id, काष्ठा sys_reg_params *params)
अणु
	चयन (id & KVM_REG_SIZE_MASK) अणु
	हाल KVM_REG_SIZE_U64:
		/* Any unused index bits means it's not valid. */
		अगर (id & ~(KVM_REG_ARCH_MASK | KVM_REG_SIZE_MASK
			      | KVM_REG_ARM_COPROC_MASK
			      | KVM_REG_ARM64_SYSREG_OP0_MASK
			      | KVM_REG_ARM64_SYSREG_OP1_MASK
			      | KVM_REG_ARM64_SYSREG_CRN_MASK
			      | KVM_REG_ARM64_SYSREG_CRM_MASK
			      | KVM_REG_ARM64_SYSREG_OP2_MASK))
			वापस false;
		params->Op0 = ((id & KVM_REG_ARM64_SYSREG_OP0_MASK)
			       >> KVM_REG_ARM64_SYSREG_OP0_SHIFT);
		params->Op1 = ((id & KVM_REG_ARM64_SYSREG_OP1_MASK)
			       >> KVM_REG_ARM64_SYSREG_OP1_SHIFT);
		params->CRn = ((id & KVM_REG_ARM64_SYSREG_CRN_MASK)
			       >> KVM_REG_ARM64_SYSREG_CRN_SHIFT);
		params->CRm = ((id & KVM_REG_ARM64_SYSREG_CRM_MASK)
			       >> KVM_REG_ARM64_SYSREG_CRM_SHIFT);
		params->Op2 = ((id & KVM_REG_ARM64_SYSREG_OP2_MASK)
			       >> KVM_REG_ARM64_SYSREG_OP2_SHIFT);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

स्थिर काष्ठा sys_reg_desc *find_reg_by_id(u64 id,
					  काष्ठा sys_reg_params *params,
					  स्थिर काष्ठा sys_reg_desc table[],
					  अचिन्हित पूर्णांक num)
अणु
	अगर (!index_to_params(id, params))
		वापस शून्य;

	वापस find_reg(params, table, num);
पूर्ण

/* Decode an index value, and find the sys_reg_desc entry. */
अटल स्थिर काष्ठा sys_reg_desc *index_to_sys_reg_desc(काष्ठा kvm_vcpu *vcpu,
						    u64 id)
अणु
	स्थिर काष्ठा sys_reg_desc *r;
	काष्ठा sys_reg_params params;

	/* We only करो sys_reg क्रम now. */
	अगर ((id & KVM_REG_ARM_COPROC_MASK) != KVM_REG_ARM64_SYSREG)
		वापस शून्य;

	अगर (!index_to_params(id, &params))
		वापस शून्य;

	r = find_reg(&params, sys_reg_descs, ARRAY_SIZE(sys_reg_descs));

	/* Not saved in the sys_reg array and not otherwise accessible? */
	अगर (r && !(r->reg || r->get_user))
		r = शून्य;

	वापस r;
पूर्ण

/*
 * These are the invariant sys_reg रेजिस्टरs: we let the guest see the
 * host versions of these, so they're part of the guest state.
 *
 * A future CPU may provide a mechanism to present dअगरferent values to
 * the guest, or a future kvm may trap them.
 */

#घोषणा FUNCTION_INVARIANT(reg)						\
	अटल व्योम get_##reg(काष्ठा kvm_vcpu *v,			\
			      स्थिर काष्ठा sys_reg_desc *r)		\
	अणु								\
		((काष्ठा sys_reg_desc *)r)->val = पढ़ो_sysreg(reg);	\
	पूर्ण

FUNCTION_INVARIANT(midr_el1)
FUNCTION_INVARIANT(revidr_el1)
FUNCTION_INVARIANT(clidr_el1)
FUNCTION_INVARIANT(aidr_el1)

अटल व्योम get_ctr_el0(काष्ठा kvm_vcpu *v, स्थिर काष्ठा sys_reg_desc *r)
अणु
	((काष्ठा sys_reg_desc *)r)->val = पढ़ो_sanitised_ftr_reg(SYS_CTR_EL0);
पूर्ण

/* ->val is filled in by kvm_sys_reg_table_init() */
अटल काष्ठा sys_reg_desc invariant_sys_regs[] = अणु
	अणु SYS_DESC(SYS_MIDR_EL1), शून्य, get_midr_el1 पूर्ण,
	अणु SYS_DESC(SYS_REVIDR_EL1), शून्य, get_revidr_el1 पूर्ण,
	अणु SYS_DESC(SYS_CLIDR_EL1), शून्य, get_clidr_el1 पूर्ण,
	अणु SYS_DESC(SYS_AIDR_EL1), शून्य, get_aidr_el1 पूर्ण,
	अणु SYS_DESC(SYS_CTR_EL0), शून्य, get_ctr_el0 पूर्ण,
पूर्ण;

अटल पूर्णांक reg_from_user(u64 *val, स्थिर व्योम __user *uaddr, u64 id)
अणु
	अगर (copy_from_user(val, uaddr, KVM_REG_SIZE(id)) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक reg_to_user(व्योम __user *uaddr, स्थिर u64 *val, u64 id)
अणु
	अगर (copy_to_user(uaddr, val, KVM_REG_SIZE(id)) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक get_invariant_sys_reg(u64 id, व्योम __user *uaddr)
अणु
	काष्ठा sys_reg_params params;
	स्थिर काष्ठा sys_reg_desc *r;

	r = find_reg_by_id(id, &params, invariant_sys_regs,
			   ARRAY_SIZE(invariant_sys_regs));
	अगर (!r)
		वापस -ENOENT;

	वापस reg_to_user(uaddr, &r->val, id);
पूर्ण

अटल पूर्णांक set_invariant_sys_reg(u64 id, व्योम __user *uaddr)
अणु
	काष्ठा sys_reg_params params;
	स्थिर काष्ठा sys_reg_desc *r;
	पूर्णांक err;
	u64 val = 0; /* Make sure high bits are 0 क्रम 32-bit regs */

	r = find_reg_by_id(id, &params, invariant_sys_regs,
			   ARRAY_SIZE(invariant_sys_regs));
	अगर (!r)
		वापस -ENOENT;

	err = reg_from_user(&val, uaddr, id);
	अगर (err)
		वापस err;

	/* This is what we mean by invariant: you can't change it. */
	अगर (r->val != val)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल bool is_valid_cache(u32 val)
अणु
	u32 level, ctype;

	अगर (val >= CSSELR_MAX)
		वापस false;

	/* Bottom bit is Inकाष्ठाion or Data bit.  Next 3 bits are level. */
	level = (val >> 1);
	ctype = (cache_levels >> (level * 3)) & 7;

	चयन (ctype) अणु
	हाल 0: /* No cache */
		वापस false;
	हाल 1: /* Inकाष्ठाion cache only */
		वापस (val & 1);
	हाल 2: /* Data cache only */
	हाल 4: /* Unअगरied cache */
		वापस !(val & 1);
	हाल 3: /* Separate inकाष्ठाion and data caches */
		वापस true;
	शेष: /* Reserved: we can't know inकाष्ठाion or data. */
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक demux_c15_get(u64 id, व्योम __user *uaddr)
अणु
	u32 val;
	u32 __user *uval = uaddr;

	/* Fail अगर we have unknown bits set. */
	अगर (id & ~(KVM_REG_ARCH_MASK|KVM_REG_SIZE_MASK|KVM_REG_ARM_COPROC_MASK
		   | ((1 << KVM_REG_ARM_COPROC_SHIFT)-1)))
		वापस -ENOENT;

	चयन (id & KVM_REG_ARM_DEMUX_ID_MASK) अणु
	हाल KVM_REG_ARM_DEMUX_ID_CCSIDR:
		अगर (KVM_REG_SIZE(id) != 4)
			वापस -ENOENT;
		val = (id & KVM_REG_ARM_DEMUX_VAL_MASK)
			>> KVM_REG_ARM_DEMUX_VAL_SHIFT;
		अगर (!is_valid_cache(val))
			वापस -ENOENT;

		वापस put_user(get_ccsidr(val), uval);
	शेष:
		वापस -ENOENT;
	पूर्ण
पूर्ण

अटल पूर्णांक demux_c15_set(u64 id, व्योम __user *uaddr)
अणु
	u32 val, newval;
	u32 __user *uval = uaddr;

	/* Fail अगर we have unknown bits set. */
	अगर (id & ~(KVM_REG_ARCH_MASK|KVM_REG_SIZE_MASK|KVM_REG_ARM_COPROC_MASK
		   | ((1 << KVM_REG_ARM_COPROC_SHIFT)-1)))
		वापस -ENOENT;

	चयन (id & KVM_REG_ARM_DEMUX_ID_MASK) अणु
	हाल KVM_REG_ARM_DEMUX_ID_CCSIDR:
		अगर (KVM_REG_SIZE(id) != 4)
			वापस -ENOENT;
		val = (id & KVM_REG_ARM_DEMUX_VAL_MASK)
			>> KVM_REG_ARM_DEMUX_VAL_SHIFT;
		अगर (!is_valid_cache(val))
			वापस -ENOENT;

		अगर (get_user(newval, uval))
			वापस -EFAULT;

		/* This is also invariant: you can't change it. */
		अगर (newval != get_ccsidr(val))
			वापस -EINVAL;
		वापस 0;
	शेष:
		वापस -ENOENT;
	पूर्ण
पूर्ण

पूर्णांक kvm_arm_sys_reg_get_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	स्थिर काष्ठा sys_reg_desc *r;
	व्योम __user *uaddr = (व्योम __user *)(अचिन्हित दीर्घ)reg->addr;

	अगर ((reg->id & KVM_REG_ARM_COPROC_MASK) == KVM_REG_ARM_DEMUX)
		वापस demux_c15_get(reg->id, uaddr);

	अगर (KVM_REG_SIZE(reg->id) != माप(__u64))
		वापस -ENOENT;

	r = index_to_sys_reg_desc(vcpu, reg->id);
	अगर (!r)
		वापस get_invariant_sys_reg(reg->id, uaddr);

	/* Check क्रम regs disabled by runसमय config */
	अगर (sysreg_hidden(vcpu, r))
		वापस -ENOENT;

	अगर (r->get_user)
		वापस (r->get_user)(vcpu, r, reg, uaddr);

	वापस reg_to_user(uaddr, &__vcpu_sys_reg(vcpu, r->reg), reg->id);
पूर्ण

पूर्णांक kvm_arm_sys_reg_set_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	स्थिर काष्ठा sys_reg_desc *r;
	व्योम __user *uaddr = (व्योम __user *)(अचिन्हित दीर्घ)reg->addr;

	अगर ((reg->id & KVM_REG_ARM_COPROC_MASK) == KVM_REG_ARM_DEMUX)
		वापस demux_c15_set(reg->id, uaddr);

	अगर (KVM_REG_SIZE(reg->id) != माप(__u64))
		वापस -ENOENT;

	r = index_to_sys_reg_desc(vcpu, reg->id);
	अगर (!r)
		वापस set_invariant_sys_reg(reg->id, uaddr);

	/* Check क्रम regs disabled by runसमय config */
	अगर (sysreg_hidden(vcpu, r))
		वापस -ENOENT;

	अगर (r->set_user)
		वापस (r->set_user)(vcpu, r, reg, uaddr);

	वापस reg_from_user(&__vcpu_sys_reg(vcpu, r->reg), uaddr, reg->id);
पूर्ण

अटल अचिन्हित पूर्णांक num_demux_regs(व्योम)
अणु
	अचिन्हित पूर्णांक i, count = 0;

	क्रम (i = 0; i < CSSELR_MAX; i++)
		अगर (is_valid_cache(i))
			count++;

	वापस count;
पूर्ण

अटल पूर्णांक ग_लिखो_demux_regids(u64 __user *uindices)
अणु
	u64 val = KVM_REG_ARM64 | KVM_REG_SIZE_U32 | KVM_REG_ARM_DEMUX;
	अचिन्हित पूर्णांक i;

	val |= KVM_REG_ARM_DEMUX_ID_CCSIDR;
	क्रम (i = 0; i < CSSELR_MAX; i++) अणु
		अगर (!is_valid_cache(i))
			जारी;
		अगर (put_user(val | i, uindices))
			वापस -EFAULT;
		uindices++;
	पूर्ण
	वापस 0;
पूर्ण

अटल u64 sys_reg_to_index(स्थिर काष्ठा sys_reg_desc *reg)
अणु
	वापस (KVM_REG_ARM64 | KVM_REG_SIZE_U64 |
		KVM_REG_ARM64_SYSREG |
		(reg->Op0 << KVM_REG_ARM64_SYSREG_OP0_SHIFT) |
		(reg->Op1 << KVM_REG_ARM64_SYSREG_OP1_SHIFT) |
		(reg->CRn << KVM_REG_ARM64_SYSREG_CRN_SHIFT) |
		(reg->CRm << KVM_REG_ARM64_SYSREG_CRM_SHIFT) |
		(reg->Op2 << KVM_REG_ARM64_SYSREG_OP2_SHIFT));
पूर्ण

अटल bool copy_reg_to_user(स्थिर काष्ठा sys_reg_desc *reg, u64 __user **uind)
अणु
	अगर (!*uind)
		वापस true;

	अगर (put_user(sys_reg_to_index(reg), *uind))
		वापस false;

	(*uind)++;
	वापस true;
पूर्ण

अटल पूर्णांक walk_one_sys_reg(स्थिर काष्ठा kvm_vcpu *vcpu,
			    स्थिर काष्ठा sys_reg_desc *rd,
			    u64 __user **uind,
			    अचिन्हित पूर्णांक *total)
अणु
	/*
	 * Ignore रेजिस्टरs we trap but करोn't save,
	 * and क्रम which no custom user accessor is provided.
	 */
	अगर (!(rd->reg || rd->get_user))
		वापस 0;

	अगर (sysreg_hidden(vcpu, rd))
		वापस 0;

	अगर (!copy_reg_to_user(rd, uind))
		वापस -EFAULT;

	(*total)++;
	वापस 0;
पूर्ण

/* Assumed ordered tables, see kvm_sys_reg_table_init. */
अटल पूर्णांक walk_sys_regs(काष्ठा kvm_vcpu *vcpu, u64 __user *uind)
अणु
	स्थिर काष्ठा sys_reg_desc *i2, *end2;
	अचिन्हित पूर्णांक total = 0;
	पूर्णांक err;

	i2 = sys_reg_descs;
	end2 = sys_reg_descs + ARRAY_SIZE(sys_reg_descs);

	जबतक (i2 != end2) अणु
		err = walk_one_sys_reg(vcpu, i2++, &uind, &total);
		अगर (err)
			वापस err;
	पूर्ण
	वापस total;
पूर्ण

अचिन्हित दीर्घ kvm_arm_num_sys_reg_descs(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस ARRAY_SIZE(invariant_sys_regs)
		+ num_demux_regs()
		+ walk_sys_regs(vcpu, (u64 __user *)शून्य);
पूर्ण

पूर्णांक kvm_arm_copy_sys_reg_indices(काष्ठा kvm_vcpu *vcpu, u64 __user *uindices)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/* Then give them all the invariant रेजिस्टरs' indices. */
	क्रम (i = 0; i < ARRAY_SIZE(invariant_sys_regs); i++) अणु
		अगर (put_user(sys_reg_to_index(&invariant_sys_regs[i]), uindices))
			वापस -EFAULT;
		uindices++;
	पूर्ण

	err = walk_sys_regs(vcpu, uindices);
	अगर (err < 0)
		वापस err;
	uindices += err;

	वापस ग_लिखो_demux_regids(uindices);
पूर्ण

व्योम kvm_sys_reg_table_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा sys_reg_desc clidr;

	/* Make sure tables are unique and in order. */
	BUG_ON(check_sysreg_table(sys_reg_descs, ARRAY_SIZE(sys_reg_descs), false));
	BUG_ON(check_sysreg_table(cp14_regs, ARRAY_SIZE(cp14_regs), true));
	BUG_ON(check_sysreg_table(cp14_64_regs, ARRAY_SIZE(cp14_64_regs), true));
	BUG_ON(check_sysreg_table(cp15_regs, ARRAY_SIZE(cp15_regs), true));
	BUG_ON(check_sysreg_table(cp15_64_regs, ARRAY_SIZE(cp15_64_regs), true));
	BUG_ON(check_sysreg_table(invariant_sys_regs, ARRAY_SIZE(invariant_sys_regs), false));

	/* We abuse the reset function to overग_लिखो the table itself. */
	क्रम (i = 0; i < ARRAY_SIZE(invariant_sys_regs); i++)
		invariant_sys_regs[i].reset(शून्य, &invariant_sys_regs[i]);

	/*
	 * CLIDR क्रमmat is awkward, so clean it up.  See ARM B4.1.20:
	 *
	 *   If software पढ़ोs the Cache Type fields from Ctype1
	 *   upwards, once it has seen a value of 0b000, no caches
	 *   exist at further-out levels of the hierarchy. So, क्रम
	 *   example, अगर Ctype3 is the first Cache Type field with a
	 *   value of 0b000, the values of Ctype4 to Ctype7 must be
	 *   ignored.
	 */
	get_clidr_el1(शून्य, &clidr); /* Ugly... */
	cache_levels = clidr.val;
	क्रम (i = 0; i < 7; i++)
		अगर (((cache_levels >> (i*3)) & 7) == 0)
			अवरोध;
	/* Clear all higher bits. */
	cache_levels &= (1 << (i*3))-1;
पूर्ण
