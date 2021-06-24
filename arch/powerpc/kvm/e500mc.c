<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010,2012 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Varun Sethi, <varun.sethi@मुक्तscale.com>
 *
 * Description:
 * This file is derived from arch/घातerpc/kvm/e500.c,
 * by Yu Liu <yu.liu@मुक्तscale.com>.
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/dbell.h>

#समावेश "booke.h"
#समावेश "e500.h"

व्योम kvmppc_set_pending_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, क्रमागत पूर्णांक_class type)
अणु
	क्रमागत ppc_dbell dbell_type;
	अचिन्हित दीर्घ tag;

	चयन (type) अणु
	हाल INT_CLASS_NONCRIT:
		dbell_type = PPC_G_DBELL;
		अवरोध;
	हाल INT_CLASS_CRIT:
		dbell_type = PPC_G_DBELL_CRIT;
		अवरोध;
	हाल INT_CLASS_MC:
		dbell_type = PPC_G_DBELL_MC;
		अवरोध;
	शेष:
		WARN_ONCE(1, "%s: unknown int type %d\n", __func__, type);
		वापस;
	पूर्ण

	preempt_disable();
	tag = PPC_DBELL_LPID(get_lpid(vcpu)) | vcpu->vcpu_id;
	mb();
	ppc_msgsnd(dbell_type, 0, tag);
	preempt_enable();
पूर्ण

/* gtlbe must not be mapped by more than one host tlb entry */
व्योम kvmppc_e500_tlbil_one(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
			   काष्ठा kvm_book3e_206_tlb_entry *gtlbe)
अणु
	अचिन्हित पूर्णांक tid, ts;
	gva_t eaddr;
	u32 val;
	अचिन्हित दीर्घ flags;

	ts = get_tlb_ts(gtlbe);
	tid = get_tlb_tid(gtlbe);

	/* We search the host TLB to invalidate its shaकरोw TLB entry */
	val = (tid << 16) | ts;
	eaddr = get_tlb_eaddr(gtlbe);

	local_irq_save(flags);

	mtspr(SPRN_MAS6, val);
	mtspr(SPRN_MAS5, MAS5_SGS | get_lpid(&vcpu_e500->vcpu));

	यंत्र अस्थिर("tlbsx 0, %[eaddr]\n" : : [eaddr] "r" (eaddr));
	val = mfspr(SPRN_MAS1);
	अगर (val & MAS1_VALID) अणु
		mtspr(SPRN_MAS1, val & ~MAS1_VALID);
		यंत्र अस्थिर("tlbwe");
	पूर्ण
	mtspr(SPRN_MAS5, 0);
	/* NOTE: tlbsx also updates mas8, so clear it क्रम host tlbwe */
	mtspr(SPRN_MAS8, 0);
	isync();

	local_irq_restore(flags);
पूर्ण

व्योम kvmppc_e500_tlbil_all(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	mtspr(SPRN_MAS5, MAS5_SGS | get_lpid(&vcpu_e500->vcpu));
	यंत्र अस्थिर("tlbilxlpid");
	mtspr(SPRN_MAS5, 0);
	local_irq_restore(flags);
पूर्ण

व्योम kvmppc_set_pid(काष्ठा kvm_vcpu *vcpu, u32 pid)
अणु
	vcpu->arch.pid = pid;
पूर्ण

व्योम kvmppc_mmu_msr_notअगरy(काष्ठा kvm_vcpu *vcpu, u32 old_msr)
अणु
पूर्ण

/* We use two lpids per VM */
अटल DEFINE_PER_CPU(काष्ठा kvm_vcpu *[KVMPPC_NR_LPIDS], last_vcpu_of_lpid);

अटल व्योम kvmppc_core_vcpu_load_e500mc(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	kvmppc_booke_vcpu_load(vcpu, cpu);

	mtspr(SPRN_LPID, get_lpid(vcpu));
	mtspr(SPRN_EPCR, vcpu->arch.shaकरोw_epcr);
	mtspr(SPRN_GPIR, vcpu->vcpu_id);
	mtspr(SPRN_MSRP, vcpu->arch.shaकरोw_msrp);
	vcpu->arch.eplc = EPC_EGS | (get_lpid(vcpu) << EPC_ELPID_SHIFT);
	vcpu->arch.epsc = vcpu->arch.eplc;
	mtspr(SPRN_EPLC, vcpu->arch.eplc);
	mtspr(SPRN_EPSC, vcpu->arch.epsc);

	mtspr(SPRN_GIVPR, vcpu->arch.ivpr);
	mtspr(SPRN_GIVOR2, vcpu->arch.ivor[BOOKE_IRQPRIO_DATA_STORAGE]);
	mtspr(SPRN_GIVOR8, vcpu->arch.ivor[BOOKE_IRQPRIO_SYSCALL]);
	mtspr(SPRN_GSPRG0, (अचिन्हित दीर्घ)vcpu->arch.shared->sprg0);
	mtspr(SPRN_GSPRG1, (अचिन्हित दीर्घ)vcpu->arch.shared->sprg1);
	mtspr(SPRN_GSPRG2, (अचिन्हित दीर्घ)vcpu->arch.shared->sprg2);
	mtspr(SPRN_GSPRG3, (अचिन्हित दीर्घ)vcpu->arch.shared->sprg3);

	mtspr(SPRN_GSRR0, vcpu->arch.shared->srr0);
	mtspr(SPRN_GSRR1, vcpu->arch.shared->srr1);

	mtspr(SPRN_GEPR, vcpu->arch.epr);
	mtspr(SPRN_GDEAR, vcpu->arch.shared->dar);
	mtspr(SPRN_GESR, vcpu->arch.shared->esr);

	अगर (vcpu->arch.oldpir != mfspr(SPRN_PIR) ||
	    __this_cpu_पढ़ो(last_vcpu_of_lpid[get_lpid(vcpu)]) != vcpu) अणु
		kvmppc_e500_tlbil_all(vcpu_e500);
		__this_cpu_ग_लिखो(last_vcpu_of_lpid[get_lpid(vcpu)], vcpu);
	पूर्ण
पूर्ण

अटल व्योम kvmppc_core_vcpu_put_e500mc(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.eplc = mfspr(SPRN_EPLC);
	vcpu->arch.epsc = mfspr(SPRN_EPSC);

	vcpu->arch.shared->sprg0 = mfspr(SPRN_GSPRG0);
	vcpu->arch.shared->sprg1 = mfspr(SPRN_GSPRG1);
	vcpu->arch.shared->sprg2 = mfspr(SPRN_GSPRG2);
	vcpu->arch.shared->sprg3 = mfspr(SPRN_GSPRG3);

	vcpu->arch.shared->srr0 = mfspr(SPRN_GSRR0);
	vcpu->arch.shared->srr1 = mfspr(SPRN_GSRR1);

	vcpu->arch.epr = mfspr(SPRN_GEPR);
	vcpu->arch.shared->dar = mfspr(SPRN_GDEAR);
	vcpu->arch.shared->esr = mfspr(SPRN_GESR);

	vcpu->arch.oldpir = mfspr(SPRN_PIR);

	kvmppc_booke_vcpu_put(vcpu);
पूर्ण

पूर्णांक kvmppc_core_check_processor_compat(व्योम)
अणु
	पूर्णांक r;

	अगर (म_भेद(cur_cpu_spec->cpu_name, "e500mc") == 0)
		r = 0;
	अन्यथा अगर (म_भेद(cur_cpu_spec->cpu_name, "e5500") == 0)
		r = 0;
#अगर_घोषित CONFIG_ALTIVEC
	/*
	 * Since guests have the privilege to enable AltiVec, we need AltiVec
	 * support in the host to save/restore their context.
	 * Don't use CPU_FTR_ALTIVEC to identअगरy cores with AltiVec unit
	 * because it's cleared in the असलence of CONFIG_ALTIVEC!
	 */
	अन्यथा अगर (म_भेद(cur_cpu_spec->cpu_name, "e6500") == 0)
		r = 0;
#पूर्ण_अगर
	अन्यथा
		r = -ENOTSUPP;

	वापस r;
पूर्ण

पूर्णांक kvmppc_core_vcpu_setup(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	vcpu->arch.shaकरोw_epcr = SPRN_EPCR_DSIGS | SPRN_EPCR_DGTMI | \
				 SPRN_EPCR_DUVD;
#अगर_घोषित CONFIG_64BIT
	vcpu->arch.shaकरोw_epcr |= SPRN_EPCR_ICM;
#पूर्ण_अगर
	vcpu->arch.shaकरोw_msrp = MSRP_UCLEP | MSRP_PMMP;

	vcpu->arch.pvr = mfspr(SPRN_PVR);
	vcpu_e500->svr = mfspr(SPRN_SVR);

	vcpu->arch.cpu_type = KVM_CPU_E500MC;

	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_core_get_sregs_e500mc(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_sregs *sregs)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	sregs->u.e.features |= KVM_SREGS_E_ARCH206_MMU | KVM_SREGS_E_PM |
			       KVM_SREGS_E_PC;
	sregs->u.e.impl_id = KVM_SREGS_E_IMPL_FSL;

	sregs->u.e.impl.fsl.features = 0;
	sregs->u.e.impl.fsl.svr = vcpu_e500->svr;
	sregs->u.e.impl.fsl.hid0 = vcpu_e500->hid0;
	sregs->u.e.impl.fsl.mcar = vcpu_e500->mcar;

	kvmppc_get_sregs_e500_tlb(vcpu, sregs);

	sregs->u.e.ivor_high[3] =
		vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR];
	sregs->u.e.ivor_high[4] = vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL];
	sregs->u.e.ivor_high[5] = vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL_CRIT];

	वापस kvmppc_get_sregs_ivor(vcpu, sregs);
पूर्ण

अटल पूर्णांक kvmppc_core_set_sregs_e500mc(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_sregs *sregs)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	पूर्णांक ret;

	अगर (sregs->u.e.impl_id == KVM_SREGS_E_IMPL_FSL) अणु
		vcpu_e500->svr = sregs->u.e.impl.fsl.svr;
		vcpu_e500->hid0 = sregs->u.e.impl.fsl.hid0;
		vcpu_e500->mcar = sregs->u.e.impl.fsl.mcar;
	पूर्ण

	ret = kvmppc_set_sregs_e500_tlb(vcpu, sregs);
	अगर (ret < 0)
		वापस ret;

	अगर (!(sregs->u.e.features & KVM_SREGS_E_IVOR))
		वापस 0;

	अगर (sregs->u.e.features & KVM_SREGS_E_PM) अणु
		vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR] =
			sregs->u.e.ivor_high[3];
	पूर्ण

	अगर (sregs->u.e.features & KVM_SREGS_E_PC) अणु
		vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL] =
			sregs->u.e.ivor_high[4];
		vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL_CRIT] =
			sregs->u.e.ivor_high[5];
	पूर्ण

	वापस kvmppc_set_sregs_ivor(vcpu, sregs);
पूर्ण

अटल पूर्णांक kvmppc_get_one_reg_e500mc(काष्ठा kvm_vcpu *vcpu, u64 id,
			      जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;

	चयन (id) अणु
	हाल KVM_REG_PPC_SPRG9:
		*val = get_reg_val(id, vcpu->arch.sprg9);
		अवरोध;
	शेष:
		r = kvmppc_get_one_reg_e500_tlb(vcpu, id, val);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvmppc_set_one_reg_e500mc(काष्ठा kvm_vcpu *vcpu, u64 id,
			      जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;

	चयन (id) अणु
	हाल KVM_REG_PPC_SPRG9:
		vcpu->arch.sprg9 = set_reg_val(id, *val);
		अवरोध;
	शेष:
		r = kvmppc_set_one_reg_e500_tlb(vcpu, id, val);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvmppc_core_vcpu_create_e500mc(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500;
	पूर्णांक err;

	BUILD_BUG_ON(दुरत्व(काष्ठा kvmppc_vcpu_e500, vcpu) != 0);
	vcpu_e500 = to_e500(vcpu);

	/* Invalid PIR value -- this LPID करोsn't have valid state on any cpu */
	vcpu->arch.oldpir = 0xffffffff;

	err = kvmppc_e500_tlb_init(vcpu_e500);
	अगर (err)
		वापस err;

	vcpu->arch.shared = (व्योम *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);
	अगर (!vcpu->arch.shared) अणु
		err = -ENOMEM;
		जाओ uninit_tlb;
	पूर्ण

	वापस 0;

uninit_tlb:
	kvmppc_e500_tlb_uninit(vcpu_e500);
	वापस err;
पूर्ण

अटल व्योम kvmppc_core_vcpu_मुक्त_e500mc(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	मुक्त_page((अचिन्हित दीर्घ)vcpu->arch.shared);
	kvmppc_e500_tlb_uninit(vcpu_e500);
पूर्ण

अटल पूर्णांक kvmppc_core_init_vm_e500mc(काष्ठा kvm *kvm)
अणु
	पूर्णांक lpid;

	lpid = kvmppc_alloc_lpid();
	अगर (lpid < 0)
		वापस lpid;

	/*
	 * Use two lpids per VM on cores with two thपढ़ोs like e6500. Use
	 * even numbers to speedup vcpu lpid computation with consecutive lpids
	 * per VM. vm1 will use lpids 2 and 3, vm2 lpids 4 and 5, and so on.
	 */
	अगर (thपढ़ोs_per_core == 2)
		lpid <<= 1;

	kvm->arch.lpid = lpid;
	वापस 0;
पूर्ण

अटल व्योम kvmppc_core_destroy_vm_e500mc(काष्ठा kvm *kvm)
अणु
	पूर्णांक lpid = kvm->arch.lpid;

	अगर (thपढ़ोs_per_core == 2)
		lpid >>= 1;

	kvmppc_मुक्त_lpid(lpid);
पूर्ण

अटल काष्ठा kvmppc_ops kvm_ops_e500mc = अणु
	.get_sregs = kvmppc_core_get_sregs_e500mc,
	.set_sregs = kvmppc_core_set_sregs_e500mc,
	.get_one_reg = kvmppc_get_one_reg_e500mc,
	.set_one_reg = kvmppc_set_one_reg_e500mc,
	.vcpu_load   = kvmppc_core_vcpu_load_e500mc,
	.vcpu_put    = kvmppc_core_vcpu_put_e500mc,
	.vcpu_create = kvmppc_core_vcpu_create_e500mc,
	.vcpu_मुक्त   = kvmppc_core_vcpu_मुक्त_e500mc,
	.init_vm = kvmppc_core_init_vm_e500mc,
	.destroy_vm = kvmppc_core_destroy_vm_e500mc,
	.emulate_op = kvmppc_core_emulate_op_e500,
	.emulate_mtspr = kvmppc_core_emulate_mtspr_e500,
	.emulate_mfspr = kvmppc_core_emulate_mfspr_e500,
पूर्ण;

अटल पूर्णांक __init kvmppc_e500mc_init(व्योम)
अणु
	पूर्णांक r;

	r = kvmppc_booke_init();
	अगर (r)
		जाओ err_out;

	/*
	 * Use two lpids per VM on dual thपढ़ोed processors like e6500
	 * to workarround the lack of tlb ग_लिखो conditional inकाष्ठाion.
	 * Expose half the number of available hardware lpids to the lpid
	 * allocator.
	 */
	kvmppc_init_lpid(KVMPPC_NR_LPIDS/thपढ़ोs_per_core);
	kvmppc_claim_lpid(0); /* host */

	r = kvm_init(शून्य, माप(काष्ठा kvmppc_vcpu_e500), 0, THIS_MODULE);
	अगर (r)
		जाओ err_out;
	kvm_ops_e500mc.owner = THIS_MODULE;
	kvmppc_pr_ops = &kvm_ops_e500mc;

err_out:
	वापस r;
पूर्ण

अटल व्योम __निकास kvmppc_e500mc_निकास(व्योम)
अणु
	kvmppc_pr_ops = शून्य;
	kvmppc_booke_निकास();
पूर्ण

module_init(kvmppc_e500mc_init);
module_निकास(kvmppc_e500mc_निकास);
MODULE_ALIAS_MISCDEV(KVM_MINOR);
MODULE_ALIAS("devname:kvm");
