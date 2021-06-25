<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2011 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Yu Liu, <yu.liu@मुक्तscale.com>
 *
 * Description:
 * This file is derived from arch/घातerpc/kvm/44x.c,
 * by Hollis Blanअक्षरd <hollisb@us.ibm.com>.
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/kvm_ppc.h>

#समावेश "../mm/mmu_decl.h"
#समावेश "booke.h"
#समावेश "e500.h"

काष्ठा id अणु
	अचिन्हित दीर्घ val;
	काष्ठा id **pentry;
पूर्ण;

#घोषणा NUM_TIDS 256

/*
 * This table provide mappings from:
 * (guestAS,guestTID,guestPR) --> ID of physical cpu
 * guestAS	[0..1]
 * guestTID	[0..255]
 * guestPR	[0..1]
 * ID		[1..255]
 * Each vcpu keeps one vcpu_id_table.
 */
काष्ठा vcpu_id_table अणु
	काष्ठा id id[2][NUM_TIDS][2];
पूर्ण;

/*
 * This table provide reversed mappings of vcpu_id_table:
 * ID --> address of vcpu_id_table item.
 * Each physical core has one pcpu_id_table.
 */
काष्ठा pcpu_id_table अणु
	काष्ठा id *entry[NUM_TIDS];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा pcpu_id_table, pcpu_sids);

/* This variable keeps last used shaकरोw ID on local core.
 * The valid range of shaकरोw ID is [1..255] */
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, pcpu_last_used_sid);

/*
 * Allocate a मुक्त shaकरोw id and setup a valid sid mapping in given entry.
 * A mapping is only valid when vcpu_id_table and pcpu_id_table are match.
 *
 * The caller must have preemption disabled, and keep it that way until
 * it has finished with the वापसed shaकरोw id (either written पूर्णांकo the
 * TLB or arch.shaकरोw_pid, or discarded).
 */
अटल अंतरभूत पूर्णांक local_sid_setup_one(काष्ठा id *entry)
अणु
	अचिन्हित दीर्घ sid;
	पूर्णांक ret = -1;

	sid = __this_cpu_inc_वापस(pcpu_last_used_sid);
	अगर (sid < NUM_TIDS) अणु
		__this_cpu_ग_लिखो(pcpu_sids.entry[sid], entry);
		entry->val = sid;
		entry->pentry = this_cpu_ptr(&pcpu_sids.entry[sid]);
		ret = sid;
	पूर्ण

	/*
	 * If sid == NUM_TIDS, we've run out of sids.  We वापस -1, and
	 * the caller will invalidate everything and start over.
	 *
	 * sid > NUM_TIDS indicates a race, which we disable preemption to
	 * aव्योम.
	 */
	WARN_ON(sid > NUM_TIDS);

	वापस ret;
पूर्ण

/*
 * Check अगर given entry contain a valid shaकरोw id mapping.
 * An ID mapping is considered valid only अगर
 * both vcpu and pcpu know this mapping.
 *
 * The caller must have preemption disabled, and keep it that way until
 * it has finished with the वापसed shaकरोw id (either written पूर्णांकo the
 * TLB or arch.shaकरोw_pid, or discarded).
 */
अटल अंतरभूत पूर्णांक local_sid_lookup(काष्ठा id *entry)
अणु
	अगर (entry && entry->val != 0 &&
	    __this_cpu_पढ़ो(pcpu_sids.entry[entry->val]) == entry &&
	    entry->pentry == this_cpu_ptr(&pcpu_sids.entry[entry->val]))
		वापस entry->val;
	वापस -1;
पूर्ण

/* Invalidate all id mappings on local core -- call with preempt disabled */
अटल अंतरभूत व्योम local_sid_destroy_all(व्योम)
अणु
	__this_cpu_ग_लिखो(pcpu_last_used_sid, 0);
	स_रखो(this_cpu_ptr(&pcpu_sids), 0, माप(pcpu_sids));
पूर्ण

अटल व्योम *kvmppc_e500_id_table_alloc(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	vcpu_e500->idt = kzalloc(माप(काष्ठा vcpu_id_table), GFP_KERNEL);
	वापस vcpu_e500->idt;
पूर्ण

अटल व्योम kvmppc_e500_id_table_मुक्त(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	kमुक्त(vcpu_e500->idt);
	vcpu_e500->idt = शून्य;
पूर्ण

/* Map guest pid to shaकरोw.
 * We use PID to keep shaकरोw of current guest non-zero PID,
 * and use PID1 to keep shaकरोw of guest zero PID.
 * So that guest tlbe with TID=0 can be accessed at any समय */
अटल व्योम kvmppc_e500_recalc_shaकरोw_pid(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	preempt_disable();
	vcpu_e500->vcpu.arch.shaकरोw_pid = kvmppc_e500_get_sid(vcpu_e500,
			get_cur_as(&vcpu_e500->vcpu),
			get_cur_pid(&vcpu_e500->vcpu),
			get_cur_pr(&vcpu_e500->vcpu), 1);
	vcpu_e500->vcpu.arch.shaकरोw_pid1 = kvmppc_e500_get_sid(vcpu_e500,
			get_cur_as(&vcpu_e500->vcpu), 0,
			get_cur_pr(&vcpu_e500->vcpu), 1);
	preempt_enable();
पूर्ण

/* Invalidate all mappings on vcpu */
अटल व्योम kvmppc_e500_id_table_reset_all(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	स_रखो(vcpu_e500->idt, 0, माप(काष्ठा vcpu_id_table));

	/* Update shaकरोw pid when mappings are changed */
	kvmppc_e500_recalc_shaकरोw_pid(vcpu_e500);
पूर्ण

/* Invalidate one ID mapping on vcpu */
अटल अंतरभूत व्योम kvmppc_e500_id_table_reset_one(
			       काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
			       पूर्णांक as, पूर्णांक pid, पूर्णांक pr)
अणु
	काष्ठा vcpu_id_table *idt = vcpu_e500->idt;

	BUG_ON(as >= 2);
	BUG_ON(pid >= NUM_TIDS);
	BUG_ON(pr >= 2);

	idt->id[as][pid][pr].val = 0;
	idt->id[as][pid][pr].pentry = शून्य;

	/* Update shaकरोw pid when mappings are changed */
	kvmppc_e500_recalc_shaकरोw_pid(vcpu_e500);
पूर्ण

/*
 * Map guest (vcpu,AS,ID,PR) to physical core shaकरोw id.
 * This function first lookup अगर a valid mapping exists,
 * अगर not, then creates a new one.
 *
 * The caller must have preemption disabled, and keep it that way until
 * it has finished with the वापसed shaकरोw id (either written पूर्णांकo the
 * TLB or arch.shaकरोw_pid, or discarded).
 */
अचिन्हित पूर्णांक kvmppc_e500_get_sid(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
				 अचिन्हित पूर्णांक as, अचिन्हित पूर्णांक gid,
				 अचिन्हित पूर्णांक pr, पूर्णांक aव्योम_recursion)
अणु
	काष्ठा vcpu_id_table *idt = vcpu_e500->idt;
	पूर्णांक sid;

	BUG_ON(as >= 2);
	BUG_ON(gid >= NUM_TIDS);
	BUG_ON(pr >= 2);

	sid = local_sid_lookup(&idt->id[as][gid][pr]);

	जबतक (sid <= 0) अणु
		/* No mapping yet */
		sid = local_sid_setup_one(&idt->id[as][gid][pr]);
		अगर (sid <= 0) अणु
			_tlbil_all();
			local_sid_destroy_all();
		पूर्ण

		/* Update shaकरोw pid when mappings are changed */
		अगर (!aव्योम_recursion)
			kvmppc_e500_recalc_shaकरोw_pid(vcpu_e500);
	पूर्ण

	वापस sid;
पूर्ण

अचिन्हित पूर्णांक kvmppc_e500_get_tlb_stid(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा kvm_book3e_206_tlb_entry *gtlbe)
अणु
	वापस kvmppc_e500_get_sid(to_e500(vcpu), get_tlb_ts(gtlbe),
				   get_tlb_tid(gtlbe), get_cur_pr(vcpu), 0);
पूर्ण

व्योम kvmppc_set_pid(काष्ठा kvm_vcpu *vcpu, u32 pid)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	अगर (vcpu->arch.pid != pid) अणु
		vcpu_e500->pid[0] = vcpu->arch.pid = pid;
		kvmppc_e500_recalc_shaकरोw_pid(vcpu_e500);
	पूर्ण
पूर्ण

/* gtlbe must not be mapped by more than one host tlbe */
व्योम kvmppc_e500_tlbil_one(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
                           काष्ठा kvm_book3e_206_tlb_entry *gtlbe)
अणु
	काष्ठा vcpu_id_table *idt = vcpu_e500->idt;
	अचिन्हित पूर्णांक pr, tid, ts;
	पूर्णांक pid;
	u32 val, eaddr;
	अचिन्हित दीर्घ flags;

	ts = get_tlb_ts(gtlbe);
	tid = get_tlb_tid(gtlbe);

	preempt_disable();

	/* One guest ID may be mapped to two shaकरोw IDs */
	क्रम (pr = 0; pr < 2; pr++) अणु
		/*
		 * The shaकरोw PID can have a valid mapping on at most one
		 * host CPU.  In the common हाल, it will be valid on this
		 * CPU, in which हाल we करो a local invalidation of the
		 * specअगरic address.
		 *
		 * If the shaकरोw PID is not valid on the current host CPU,
		 * we invalidate the entire shaकरोw PID.
		 */
		pid = local_sid_lookup(&idt->id[ts][tid][pr]);
		अगर (pid <= 0) अणु
			kvmppc_e500_id_table_reset_one(vcpu_e500, ts, tid, pr);
			जारी;
		पूर्ण

		/*
		 * The guest is invalidating a 4K entry which is in a PID
		 * that has a valid shaकरोw mapping on this host CPU.  We
		 * search host TLB to invalidate it's shaकरोw TLB entry,
		 * similar to __tlbil_va except that we need to look in AS1.
		 */
		val = (pid << MAS6_SPID_SHIFT) | MAS6_SAS;
		eaddr = get_tlb_eaddr(gtlbe);

		local_irq_save(flags);

		mtspr(SPRN_MAS6, val);
		यंत्र अस्थिर("tlbsx 0, %[eaddr]" : : [eaddr] "r" (eaddr));
		val = mfspr(SPRN_MAS1);
		अगर (val & MAS1_VALID) अणु
			mtspr(SPRN_MAS1, val & ~MAS1_VALID);
			यंत्र अस्थिर("tlbwe");
		पूर्ण

		local_irq_restore(flags);
	पूर्ण

	preempt_enable();
पूर्ण

व्योम kvmppc_e500_tlbil_all(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	kvmppc_e500_id_table_reset_all(vcpu_e500);
पूर्ण

व्योम kvmppc_mmu_msr_notअगरy(काष्ठा kvm_vcpu *vcpu, u32 old_msr)
अणु
	/* Recalc shaकरोw pid since MSR changes */
	kvmppc_e500_recalc_shaकरोw_pid(to_e500(vcpu));
पूर्ण

अटल व्योम kvmppc_core_vcpu_load_e500(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	kvmppc_booke_vcpu_load(vcpu, cpu);

	/* Shaकरोw PID may be expired on local core */
	kvmppc_e500_recalc_shaकरोw_pid(to_e500(vcpu));
पूर्ण

अटल व्योम kvmppc_core_vcpu_put_e500(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_SPE
	अगर (vcpu->arch.shaकरोw_msr & MSR_SPE)
		kvmppc_vcpu_disable_spe(vcpu);
#पूर्ण_अगर

	kvmppc_booke_vcpu_put(vcpu);
पूर्ण

पूर्णांक kvmppc_core_check_processor_compat(व्योम)
अणु
	पूर्णांक r;

	अगर (म_भेद(cur_cpu_spec->cpu_name, "e500v2") == 0)
		r = 0;
	अन्यथा
		r = -ENOTSUPP;

	वापस r;
पूर्ण

अटल व्योम kvmppc_e500_tlb_setup(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	काष्ठा kvm_book3e_206_tlb_entry *tlbe;

	/* Insert large initial mapping क्रम guest. */
	tlbe = get_entry(vcpu_e500, 1, 0);
	tlbe->mas1 = MAS1_VALID | MAS1_TSIZE(BOOK3E_PAGESZ_256M);
	tlbe->mas2 = 0;
	tlbe->mas7_3 = E500_TLB_SUPER_PERM_MASK;

	/* 4K map क्रम serial output. Used by kernel wrapper. */
	tlbe = get_entry(vcpu_e500, 1, 1);
	tlbe->mas1 = MAS1_VALID | MAS1_TSIZE(BOOK3E_PAGESZ_4K);
	tlbe->mas2 = (0xe0004500 & 0xFFFFF000) | MAS2_I | MAS2_G;
	tlbe->mas7_3 = (0xe0004500 & 0xFFFFF000) | E500_TLB_SUPER_PERM_MASK;
पूर्ण

पूर्णांक kvmppc_core_vcpu_setup(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	kvmppc_e500_tlb_setup(vcpu_e500);

	/* Registers init */
	vcpu->arch.pvr = mfspr(SPRN_PVR);
	vcpu_e500->svr = mfspr(SPRN_SVR);

	vcpu->arch.cpu_type = KVM_CPU_E500V2;

	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_core_get_sregs_e500(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा kvm_sregs *sregs)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	sregs->u.e.features |= KVM_SREGS_E_ARCH206_MMU | KVM_SREGS_E_SPE |
	                       KVM_SREGS_E_PM;
	sregs->u.e.impl_id = KVM_SREGS_E_IMPL_FSL;

	sregs->u.e.impl.fsl.features = 0;
	sregs->u.e.impl.fsl.svr = vcpu_e500->svr;
	sregs->u.e.impl.fsl.hid0 = vcpu_e500->hid0;
	sregs->u.e.impl.fsl.mcar = vcpu_e500->mcar;

	sregs->u.e.ivor_high[0] = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_UNAVAIL];
	sregs->u.e.ivor_high[1] = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_DATA];
	sregs->u.e.ivor_high[2] = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_ROUND];
	sregs->u.e.ivor_high[3] =
		vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR];

	kvmppc_get_sregs_ivor(vcpu, sregs);
	kvmppc_get_sregs_e500_tlb(vcpu, sregs);
	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_core_set_sregs_e500(काष्ठा kvm_vcpu *vcpu,
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

	अगर (sregs->u.e.features & KVM_SREGS_E_SPE) अणु
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_UNAVAIL] =
			sregs->u.e.ivor_high[0];
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_DATA] =
			sregs->u.e.ivor_high[1];
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_ROUND] =
			sregs->u.e.ivor_high[2];
	पूर्ण

	अगर (sregs->u.e.features & KVM_SREGS_E_PM) अणु
		vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR] =
			sregs->u.e.ivor_high[3];
	पूर्ण

	वापस kvmppc_set_sregs_ivor(vcpu, sregs);
पूर्ण

अटल पूर्णांक kvmppc_get_one_reg_e500(काष्ठा kvm_vcpu *vcpu, u64 id,
				   जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = kvmppc_get_one_reg_e500_tlb(vcpu, id, val);
	वापस r;
पूर्ण

अटल पूर्णांक kvmppc_set_one_reg_e500(काष्ठा kvm_vcpu *vcpu, u64 id,
				   जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = kvmppc_get_one_reg_e500_tlb(vcpu, id, val);
	वापस r;
पूर्ण

अटल पूर्णांक kvmppc_core_vcpu_create_e500(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500;
	पूर्णांक err;

	BUILD_BUG_ON(दुरत्व(काष्ठा kvmppc_vcpu_e500, vcpu) != 0);
	vcpu_e500 = to_e500(vcpu);

	अगर (kvmppc_e500_id_table_alloc(vcpu_e500) == शून्य)
		वापस -ENOMEM;

	err = kvmppc_e500_tlb_init(vcpu_e500);
	अगर (err)
		जाओ uninit_id;

	vcpu->arch.shared = (व्योम*)__get_मुक्त_page(GFP_KERNEL|__GFP_ZERO);
	अगर (!vcpu->arch.shared) अणु
		err = -ENOMEM;
		जाओ uninit_tlb;
	पूर्ण

	वापस 0;

uninit_tlb:
	kvmppc_e500_tlb_uninit(vcpu_e500);
uninit_id:
	kvmppc_e500_id_table_मुक्त(vcpu_e500);
	वापस err;
पूर्ण

अटल व्योम kvmppc_core_vcpu_मुक्त_e500(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	मुक्त_page((अचिन्हित दीर्घ)vcpu->arch.shared);
	kvmppc_e500_tlb_uninit(vcpu_e500);
	kvmppc_e500_id_table_मुक्त(vcpu_e500);
पूर्ण

अटल पूर्णांक kvmppc_core_init_vm_e500(काष्ठा kvm *kvm)
अणु
	वापस 0;
पूर्ण

अटल व्योम kvmppc_core_destroy_vm_e500(काष्ठा kvm *kvm)
अणु
पूर्ण

अटल काष्ठा kvmppc_ops kvm_ops_e500 = अणु
	.get_sregs = kvmppc_core_get_sregs_e500,
	.set_sregs = kvmppc_core_set_sregs_e500,
	.get_one_reg = kvmppc_get_one_reg_e500,
	.set_one_reg = kvmppc_set_one_reg_e500,
	.vcpu_load   = kvmppc_core_vcpu_load_e500,
	.vcpu_put    = kvmppc_core_vcpu_put_e500,
	.vcpu_create = kvmppc_core_vcpu_create_e500,
	.vcpu_मुक्त   = kvmppc_core_vcpu_मुक्त_e500,
	.init_vm = kvmppc_core_init_vm_e500,
	.destroy_vm = kvmppc_core_destroy_vm_e500,
	.emulate_op = kvmppc_core_emulate_op_e500,
	.emulate_mtspr = kvmppc_core_emulate_mtspr_e500,
	.emulate_mfspr = kvmppc_core_emulate_mfspr_e500,
पूर्ण;

अटल पूर्णांक __init kvmppc_e500_init(व्योम)
अणु
	पूर्णांक r, i;
	अचिन्हित दीर्घ ivor[3];
	/* Process reमुख्यing handlers above the generic first 16 */
	अचिन्हित दीर्घ *handler = &kvmppc_booke_handler_addr[16];
	अचिन्हित दीर्घ handler_len;
	अचिन्हित दीर्घ max_ivor = 0;

	r = kvmppc_core_check_processor_compat();
	अगर (r)
		जाओ err_out;

	r = kvmppc_booke_init();
	अगर (r)
		जाओ err_out;

	/* copy extra E500 exception handlers */
	ivor[0] = mfspr(SPRN_IVOR32);
	ivor[1] = mfspr(SPRN_IVOR33);
	ivor[2] = mfspr(SPRN_IVOR34);
	क्रम (i = 0; i < 3; i++) अणु
		अगर (ivor[i] > ivor[max_ivor])
			max_ivor = i;

		handler_len = handler[i + 1] - handler[i];
		स_नकल((व्योम *)kvmppc_booke_handlers + ivor[i],
		       (व्योम *)handler[i], handler_len);
	पूर्ण
	handler_len = handler[max_ivor + 1] - handler[max_ivor];
	flush_icache_range(kvmppc_booke_handlers, kvmppc_booke_handlers +
			   ivor[max_ivor] + handler_len);

	r = kvm_init(शून्य, माप(काष्ठा kvmppc_vcpu_e500), 0, THIS_MODULE);
	अगर (r)
		जाओ err_out;
	kvm_ops_e500.owner = THIS_MODULE;
	kvmppc_pr_ops = &kvm_ops_e500;

err_out:
	वापस r;
पूर्ण

अटल व्योम __निकास kvmppc_e500_निकास(व्योम)
अणु
	kvmppc_pr_ops = शून्य;
	kvmppc_booke_निकास();
पूर्ण

module_init(kvmppc_e500_init);
module_निकास(kvmppc_e500_निकास);
MODULE_ALIAS_MISCDEV(KVM_MINOR);
MODULE_ALIAS("devname:kvm");
