<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corporation, 2018
 * Authors Suraj Jitindar Singh <sjitindarsingh@gmail.com>
 *	   Paul Mackerras <paulus@ozद_असल.org>
 *
 * Description: KVM functions specअगरic to running nested KVM-HV guests
 * on Book3S processors (specअगरically POWER9 and later).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/llist.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/pte-walk.h>
#समावेश <यंत्र/reg.h>

अटल काष्ठा patb_entry *pseries_partition_tb;

अटल व्योम kvmhv_update_ptbl_cache(काष्ठा kvm_nested_guest *gp);
अटल व्योम kvmhv_मुक्त_memslot_nest_rmap(काष्ठा kvm_memory_slot *मुक्त);

व्योम kvmhv_save_hv_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा hv_guest_state *hr)
अणु
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;

	hr->pcr = vc->pcr | PCR_MASK;
	hr->dpdes = vc->dpdes;
	hr->hfscr = vcpu->arch.hfscr;
	hr->tb_offset = vc->tb_offset;
	hr->dawr0 = vcpu->arch.dawr0;
	hr->dawrx0 = vcpu->arch.dawrx0;
	hr->ciabr = vcpu->arch.ciabr;
	hr->purr = vcpu->arch.purr;
	hr->spurr = vcpu->arch.spurr;
	hr->ic = vcpu->arch.ic;
	hr->vtb = vc->vtb;
	hr->srr0 = vcpu->arch.shregs.srr0;
	hr->srr1 = vcpu->arch.shregs.srr1;
	hr->sprg[0] = vcpu->arch.shregs.sprg0;
	hr->sprg[1] = vcpu->arch.shregs.sprg1;
	hr->sprg[2] = vcpu->arch.shregs.sprg2;
	hr->sprg[3] = vcpu->arch.shregs.sprg3;
	hr->pidr = vcpu->arch.pid;
	hr->cfar = vcpu->arch.cfar;
	hr->ppr = vcpu->arch.ppr;
	hr->dawr1 = vcpu->arch.dawr1;
	hr->dawrx1 = vcpu->arch.dawrx1;
पूर्ण

अटल व्योम byteswap_pt_regs(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *) regs;

	क्रम (; addr < ((अचिन्हित दीर्घ *) (regs + 1)); addr++)
		*addr = swab64(*addr);
पूर्ण

अटल व्योम byteswap_hv_regs(काष्ठा hv_guest_state *hr)
अणु
	hr->version = swab64(hr->version);
	hr->lpid = swab32(hr->lpid);
	hr->vcpu_token = swab32(hr->vcpu_token);
	hr->lpcr = swab64(hr->lpcr);
	hr->pcr = swab64(hr->pcr) | PCR_MASK;
	hr->amor = swab64(hr->amor);
	hr->dpdes = swab64(hr->dpdes);
	hr->hfscr = swab64(hr->hfscr);
	hr->tb_offset = swab64(hr->tb_offset);
	hr->dawr0 = swab64(hr->dawr0);
	hr->dawrx0 = swab64(hr->dawrx0);
	hr->ciabr = swab64(hr->ciabr);
	hr->hdec_expiry = swab64(hr->hdec_expiry);
	hr->purr = swab64(hr->purr);
	hr->spurr = swab64(hr->spurr);
	hr->ic = swab64(hr->ic);
	hr->vtb = swab64(hr->vtb);
	hr->hdar = swab64(hr->hdar);
	hr->hdsisr = swab64(hr->hdsisr);
	hr->heir = swab64(hr->heir);
	hr->asdr = swab64(hr->asdr);
	hr->srr0 = swab64(hr->srr0);
	hr->srr1 = swab64(hr->srr1);
	hr->sprg[0] = swab64(hr->sprg[0]);
	hr->sprg[1] = swab64(hr->sprg[1]);
	hr->sprg[2] = swab64(hr->sprg[2]);
	hr->sprg[3] = swab64(hr->sprg[3]);
	hr->pidr = swab64(hr->pidr);
	hr->cfar = swab64(hr->cfar);
	hr->ppr = swab64(hr->ppr);
	hr->dawr1 = swab64(hr->dawr1);
	hr->dawrx1 = swab64(hr->dawrx1);
पूर्ण

अटल व्योम save_hv_वापस_state(काष्ठा kvm_vcpu *vcpu, पूर्णांक trap,
				 काष्ठा hv_guest_state *hr)
अणु
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;

	hr->dpdes = vc->dpdes;
	hr->hfscr = vcpu->arch.hfscr;
	hr->purr = vcpu->arch.purr;
	hr->spurr = vcpu->arch.spurr;
	hr->ic = vcpu->arch.ic;
	hr->vtb = vc->vtb;
	hr->srr0 = vcpu->arch.shregs.srr0;
	hr->srr1 = vcpu->arch.shregs.srr1;
	hr->sprg[0] = vcpu->arch.shregs.sprg0;
	hr->sprg[1] = vcpu->arch.shregs.sprg1;
	hr->sprg[2] = vcpu->arch.shregs.sprg2;
	hr->sprg[3] = vcpu->arch.shregs.sprg3;
	hr->pidr = vcpu->arch.pid;
	hr->cfar = vcpu->arch.cfar;
	hr->ppr = vcpu->arch.ppr;
	चयन (trap) अणु
	हाल BOOK3S_INTERRUPT_H_DATA_STORAGE:
		hr->hdar = vcpu->arch.fault_dar;
		hr->hdsisr = vcpu->arch.fault_dsisr;
		hr->asdr = vcpu->arch.fault_gpa;
		अवरोध;
	हाल BOOK3S_INTERRUPT_H_INST_STORAGE:
		hr->asdr = vcpu->arch.fault_gpa;
		अवरोध;
	हाल BOOK3S_INTERRUPT_H_EMUL_ASSIST:
		hr->heir = vcpu->arch.emul_inst;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * This can result in some L0 HV रेजिस्टर state being leaked to an L1
 * hypervisor when the hv_guest_state is copied back to the guest after
 * being modअगरied here.
 *
 * There is no known problem with such a leak, and in many हालs these
 * रेजिस्टर settings could be derived by the guest by observing behaviour
 * and timing, पूर्णांकerrupts, etc., but it is an issue to consider.
 */
अटल व्योम sanitise_hv_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा hv_guest_state *hr)
अणु
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;
	u64 mask;

	/*
	 * Don't let L1 change LPCR bits क्रम the L2 except these:
	 */
	mask = LPCR_DPFD | LPCR_ILE | LPCR_TC | LPCR_AIL | LPCR_LD |
		LPCR_LPES | LPCR_MER;

	/*
	 * Additional filtering is required depending on hardware
	 * and configuration.
	 */
	hr->lpcr = kvmppc_filter_lpcr_hv(vcpu->kvm,
			(vc->lpcr & ~mask) | (hr->lpcr & mask));

	/*
	 * Don't let L1 enable features for L2 which we've disabled क्रम L1,
	 * but preserve the पूर्णांकerrupt cause field.
	 */
	hr->hfscr &= (HFSCR_INTR_CAUSE | vcpu->arch.hfscr);

	/* Don't let data address watchpoपूर्णांक match in hypervisor state */
	hr->dawrx0 &= ~DAWRX_HYP;
	hr->dawrx1 &= ~DAWRX_HYP;

	/* Don't let completed inकाष्ठाion address अवरोधpt match in HV state */
	अगर ((hr->ciabr & CIABR_PRIV) == CIABR_PRIV_HYPER)
		hr->ciabr &= ~CIABR_PRIV;
पूर्ण

अटल व्योम restore_hv_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा hv_guest_state *hr)
अणु
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;

	vc->pcr = hr->pcr | PCR_MASK;
	vc->dpdes = hr->dpdes;
	vcpu->arch.hfscr = hr->hfscr;
	vcpu->arch.dawr0 = hr->dawr0;
	vcpu->arch.dawrx0 = hr->dawrx0;
	vcpu->arch.ciabr = hr->ciabr;
	vcpu->arch.purr = hr->purr;
	vcpu->arch.spurr = hr->spurr;
	vcpu->arch.ic = hr->ic;
	vc->vtb = hr->vtb;
	vcpu->arch.shregs.srr0 = hr->srr0;
	vcpu->arch.shregs.srr1 = hr->srr1;
	vcpu->arch.shregs.sprg0 = hr->sprg[0];
	vcpu->arch.shregs.sprg1 = hr->sprg[1];
	vcpu->arch.shregs.sprg2 = hr->sprg[2];
	vcpu->arch.shregs.sprg3 = hr->sprg[3];
	vcpu->arch.pid = hr->pidr;
	vcpu->arch.cfar = hr->cfar;
	vcpu->arch.ppr = hr->ppr;
	vcpu->arch.dawr1 = hr->dawr1;
	vcpu->arch.dawrx1 = hr->dawrx1;
पूर्ण

व्योम kvmhv_restore_hv_वापस_state(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा hv_guest_state *hr)
अणु
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;

	vc->dpdes = hr->dpdes;
	vcpu->arch.hfscr = hr->hfscr;
	vcpu->arch.purr = hr->purr;
	vcpu->arch.spurr = hr->spurr;
	vcpu->arch.ic = hr->ic;
	vc->vtb = hr->vtb;
	vcpu->arch.fault_dar = hr->hdar;
	vcpu->arch.fault_dsisr = hr->hdsisr;
	vcpu->arch.fault_gpa = hr->asdr;
	vcpu->arch.emul_inst = hr->heir;
	vcpu->arch.shregs.srr0 = hr->srr0;
	vcpu->arch.shregs.srr1 = hr->srr1;
	vcpu->arch.shregs.sprg0 = hr->sprg[0];
	vcpu->arch.shregs.sprg1 = hr->sprg[1];
	vcpu->arch.shregs.sprg2 = hr->sprg[2];
	vcpu->arch.shregs.sprg3 = hr->sprg[3];
	vcpu->arch.pid = hr->pidr;
	vcpu->arch.cfar = hr->cfar;
	vcpu->arch.ppr = hr->ppr;
पूर्ण

अटल व्योम kvmhv_nested_mmio_needed(काष्ठा kvm_vcpu *vcpu, u64 regs_ptr)
अणु
	/* No need to reflect the page fault to L1, we've handled it */
	vcpu->arch.trap = 0;

	/*
	 * Since the L2 gprs have alपढ़ोy been written back पूर्णांकo L1 memory when
	 * we complete the mmio, store the L1 memory location of the L2 gpr
	 * being loaded पूर्णांकo by the mmio so that the loaded value can be
	 * written there in kvmppc_complete_mmio_load()
	 */
	अगर (((vcpu->arch.io_gpr & KVM_MMIO_REG_EXT_MASK) == KVM_MMIO_REG_GPR)
	    && (vcpu->mmio_is_ग_लिखो == 0)) अणु
		vcpu->arch.nested_io_gpr = (gpa_t) regs_ptr +
					   दुरत्व(काष्ठा pt_regs,
						    gpr[vcpu->arch.io_gpr]);
		vcpu->arch.io_gpr = KVM_MMIO_REG_NESTED_GPR;
	पूर्ण
पूर्ण

अटल पूर्णांक kvmhv_पढ़ो_guest_state_and_regs(काष्ठा kvm_vcpu *vcpu,
					   काष्ठा hv_guest_state *l2_hv,
					   काष्ठा pt_regs *l2_regs,
					   u64 hv_ptr, u64 regs_ptr)
अणु
	पूर्णांक size;

	अगर (kvm_vcpu_पढ़ो_guest(vcpu, hv_ptr, &l2_hv->version,
				माप(l2_hv->version)))
		वापस -1;

	अगर (kvmppc_need_byteswap(vcpu))
		l2_hv->version = swab64(l2_hv->version);

	size = hv_guest_state_size(l2_hv->version);
	अगर (size < 0)
		वापस -1;

	वापस kvm_vcpu_पढ़ो_guest(vcpu, hv_ptr, l2_hv, size) ||
		kvm_vcpu_पढ़ो_guest(vcpu, regs_ptr, l2_regs,
				    माप(काष्ठा pt_regs));
पूर्ण

अटल पूर्णांक kvmhv_ग_लिखो_guest_state_and_regs(काष्ठा kvm_vcpu *vcpu,
					    काष्ठा hv_guest_state *l2_hv,
					    काष्ठा pt_regs *l2_regs,
					    u64 hv_ptr, u64 regs_ptr)
अणु
	पूर्णांक size;

	size = hv_guest_state_size(l2_hv->version);
	अगर (size < 0)
		वापस -1;

	वापस kvm_vcpu_ग_लिखो_guest(vcpu, hv_ptr, l2_hv, size) ||
		kvm_vcpu_ग_लिखो_guest(vcpu, regs_ptr, l2_regs,
				     माप(काष्ठा pt_regs));
पूर्ण

दीर्घ kvmhv_enter_nested_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	दीर्घ पूर्णांक err, r;
	काष्ठा kvm_nested_guest *l2;
	काष्ठा pt_regs l2_regs, saved_l1_regs;
	काष्ठा hv_guest_state l2_hv = अणु0पूर्ण, saved_l1_hv;
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;
	u64 hv_ptr, regs_ptr;
	u64 hdec_exp;
	s64 delta_purr, delta_spurr, delta_ic, delta_vtb;

	अगर (vcpu->kvm->arch.l1_ptcr == 0)
		वापस H_NOT_AVAILABLE;

	/* copy parameters in */
	hv_ptr = kvmppc_get_gpr(vcpu, 4);
	regs_ptr = kvmppc_get_gpr(vcpu, 5);
	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	err = kvmhv_पढ़ो_guest_state_and_regs(vcpu, &l2_hv, &l2_regs,
					      hv_ptr, regs_ptr);
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	अगर (err)
		वापस H_PARAMETER;

	अगर (kvmppc_need_byteswap(vcpu))
		byteswap_hv_regs(&l2_hv);
	अगर (l2_hv.version > HV_GUEST_STATE_VERSION)
		वापस H_P2;

	अगर (kvmppc_need_byteswap(vcpu))
		byteswap_pt_regs(&l2_regs);
	अगर (l2_hv.vcpu_token >= NR_CPUS)
		वापस H_PARAMETER;

	/* translate lpid */
	l2 = kvmhv_get_nested(vcpu->kvm, l2_hv.lpid, true);
	अगर (!l2)
		वापस H_PARAMETER;
	अगर (!l2->l1_gr_to_hr) अणु
		mutex_lock(&l2->tlb_lock);
		kvmhv_update_ptbl_cache(l2);
		mutex_unlock(&l2->tlb_lock);
	पूर्ण

	/* save l1 values of things */
	vcpu->arch.regs.msr = vcpu->arch.shregs.msr;
	saved_l1_regs = vcpu->arch.regs;
	kvmhv_save_hv_regs(vcpu, &saved_l1_hv);

	/* convert TB values/offsets to host (L0) values */
	hdec_exp = l2_hv.hdec_expiry - vc->tb_offset;
	vc->tb_offset += l2_hv.tb_offset;

	/* set L1 state to L2 state */
	vcpu->arch.nested = l2;
	vcpu->arch.nested_vcpu_id = l2_hv.vcpu_token;
	vcpu->arch.regs = l2_regs;

	/* Guest must always run with ME enabled, HV disabled. */
	vcpu->arch.shregs.msr = (vcpu->arch.regs.msr | MSR_ME) & ~MSR_HV;

	sanitise_hv_regs(vcpu, &l2_hv);
	restore_hv_regs(vcpu, &l2_hv);

	vcpu->arch.ret = RESUME_GUEST;
	vcpu->arch.trap = 0;
	करो अणु
		अगर (mftb() >= hdec_exp) अणु
			vcpu->arch.trap = BOOK3S_INTERRUPT_HV_DECREMENTER;
			r = RESUME_HOST;
			अवरोध;
		पूर्ण
		r = kvmhv_run_single_vcpu(vcpu, hdec_exp, l2_hv.lpcr);
	पूर्ण जबतक (is_kvmppc_resume_guest(r));

	/* save L2 state क्रम वापस */
	l2_regs = vcpu->arch.regs;
	l2_regs.msr = vcpu->arch.shregs.msr;
	delta_purr = vcpu->arch.purr - l2_hv.purr;
	delta_spurr = vcpu->arch.spurr - l2_hv.spurr;
	delta_ic = vcpu->arch.ic - l2_hv.ic;
	delta_vtb = vc->vtb - l2_hv.vtb;
	save_hv_वापस_state(vcpu, vcpu->arch.trap, &l2_hv);

	/* restore L1 state */
	vcpu->arch.nested = शून्य;
	vcpu->arch.regs = saved_l1_regs;
	vcpu->arch.shregs.msr = saved_l1_regs.msr & ~MSR_TS_MASK;
	/* set L1 MSR TS field according to L2 transaction state */
	अगर (l2_regs.msr & MSR_TS_MASK)
		vcpu->arch.shregs.msr |= MSR_TS_S;
	vc->tb_offset = saved_l1_hv.tb_offset;
	restore_hv_regs(vcpu, &saved_l1_hv);
	vcpu->arch.purr += delta_purr;
	vcpu->arch.spurr += delta_spurr;
	vcpu->arch.ic += delta_ic;
	vc->vtb += delta_vtb;

	kvmhv_put_nested(l2);

	/* copy l2_hv_state and regs back to guest */
	अगर (kvmppc_need_byteswap(vcpu)) अणु
		byteswap_hv_regs(&l2_hv);
		byteswap_pt_regs(&l2_regs);
	पूर्ण
	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	err = kvmhv_ग_लिखो_guest_state_and_regs(vcpu, &l2_hv, &l2_regs,
					       hv_ptr, regs_ptr);
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	अगर (err)
		वापस H_AUTHORITY;

	अगर (r == -EINTR)
		वापस H_INTERRUPT;

	अगर (vcpu->mmio_needed) अणु
		kvmhv_nested_mmio_needed(vcpu, regs_ptr);
		वापस H_TOO_HARD;
	पूर्ण

	वापस vcpu->arch.trap;
पूर्ण

दीर्घ kvmhv_nested_init(व्योम)
अणु
	दीर्घ पूर्णांक ptb_order;
	अचिन्हित दीर्घ ptcr;
	दीर्घ rc;

	अगर (!kvmhv_on_pseries())
		वापस 0;
	अगर (!radix_enabled())
		वापस -ENODEV;

	/* find log base 2 of KVMPPC_NR_LPIDS, rounding up */
	ptb_order = __ilog2(KVMPPC_NR_LPIDS - 1) + 1;
	अगर (ptb_order < 8)
		ptb_order = 8;
	pseries_partition_tb = kदो_स्मृति(माप(काष्ठा patb_entry) << ptb_order,
				       GFP_KERNEL);
	अगर (!pseries_partition_tb) अणु
		pr_err("kvm-hv: failed to allocated nested partition table\n");
		वापस -ENOMEM;
	पूर्ण

	ptcr = __pa(pseries_partition_tb) | (ptb_order - 8);
	rc = plpar_hcall_norets(H_SET_PARTITION_TABLE, ptcr);
	अगर (rc != H_SUCCESS) अणु
		pr_err("kvm-hv: Parent hypervisor does not support nesting (rc=%ld)\n",
		       rc);
		kमुक्त(pseries_partition_tb);
		pseries_partition_tb = शून्य;
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

व्योम kvmhv_nested_निकास(व्योम)
अणु
	/*
	 * N.B. the kvmhv_on_pseries() test is there because it enables
	 * the compiler to हटाओ the call to plpar_hcall_norets()
	 * when CONFIG_PPC_PSERIES=n.
	 */
	अगर (kvmhv_on_pseries() && pseries_partition_tb) अणु
		plpar_hcall_norets(H_SET_PARTITION_TABLE, 0);
		kमुक्त(pseries_partition_tb);
		pseries_partition_tb = शून्य;
	पूर्ण
पूर्ण

अटल व्योम kvmhv_flush_lpid(अचिन्हित पूर्णांक lpid)
अणु
	दीर्घ rc;

	अगर (!kvmhv_on_pseries()) अणु
		radix__flush_all_lpid(lpid);
		वापस;
	पूर्ण

	rc = plpar_hcall_norets(H_TLB_INVALIDATE, H_TLBIE_P1_ENC(2, 0, 1),
				lpid, TLBIEL_INVAL_SET_LPID);
	अगर (rc)
		pr_err("KVM: TLB LPID invalidation hcall failed, rc=%ld\n", rc);
पूर्ण

व्योम kvmhv_set_ptbl_entry(अचिन्हित पूर्णांक lpid, u64 dw0, u64 dw1)
अणु
	अगर (!kvmhv_on_pseries()) अणु
		mmu_partition_table_set_entry(lpid, dw0, dw1, true);
		वापस;
	पूर्ण

	pseries_partition_tb[lpid].patb0 = cpu_to_be64(dw0);
	pseries_partition_tb[lpid].patb1 = cpu_to_be64(dw1);
	/* L0 will करो the necessary barriers */
	kvmhv_flush_lpid(lpid);
पूर्ण

अटल व्योम kvmhv_set_nested_ptbl(काष्ठा kvm_nested_guest *gp)
अणु
	अचिन्हित दीर्घ dw0;

	dw0 = PATB_HR | radix__get_tree_size() |
		__pa(gp->shaकरोw_pgtable) | RADIX_PGD_INDEX_SIZE;
	kvmhv_set_ptbl_entry(gp->shaकरोw_lpid, dw0, gp->process_table);
पूर्ण

व्योम kvmhv_vm_nested_init(काष्ठा kvm *kvm)
अणु
	kvm->arch.max_nested_lpid = -1;
पूर्ण

/*
 * Handle the H_SET_PARTITION_TABLE hcall.
 * r4 = guest real address of partition table + log_2(size) - 12
 * (क्रमmatted as क्रम the PTCR).
 */
दीर्घ kvmhv_set_partition_table(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	अचिन्हित दीर्घ ptcr = kvmppc_get_gpr(vcpu, 4);
	पूर्णांक srcu_idx;
	दीर्घ ret = H_SUCCESS;

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	/*
	 * Limit the partition table to 4096 entries (because that's what
	 * hardware supports), and check the base address.
	 */
	अगर ((ptcr & PRTS_MASK) > 12 - 8 ||
	    !kvm_is_visible_gfn(vcpu->kvm, (ptcr & PRTB_MASK) >> PAGE_SHIFT))
		ret = H_PARAMETER;
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	अगर (ret == H_SUCCESS)
		kvm->arch.l1_ptcr = ptcr;
	वापस ret;
पूर्ण

/*
 * Handle the H_COPY_TOFROM_GUEST hcall.
 * r4 = L1 lpid of nested guest
 * r5 = pid
 * r6 = eaddr to access
 * r7 = to buffer (L1 gpa)
 * r8 = from buffer (L1 gpa)
 * r9 = n bytes to copy
 */
दीर्घ kvmhv_copy_tofrom_guest_nested(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_nested_guest *gp;
	पूर्णांक l1_lpid = kvmppc_get_gpr(vcpu, 4);
	पूर्णांक pid = kvmppc_get_gpr(vcpu, 5);
	gva_t eaddr = kvmppc_get_gpr(vcpu, 6);
	gpa_t gp_to = (gpa_t) kvmppc_get_gpr(vcpu, 7);
	gpa_t gp_from = (gpa_t) kvmppc_get_gpr(vcpu, 8);
	व्योम *buf;
	अचिन्हित दीर्घ n = kvmppc_get_gpr(vcpu, 9);
	bool is_load = !!gp_to;
	दीर्घ rc;

	अगर (gp_to && gp_from) /* One must be शून्य to determine the direction */
		वापस H_PARAMETER;

	अगर (eaddr & (0xFFFUL << 52))
		वापस H_PARAMETER;

	buf = kzalloc(n, GFP_KERNEL);
	अगर (!buf)
		वापस H_NO_MEM;

	gp = kvmhv_get_nested(vcpu->kvm, l1_lpid, false);
	अगर (!gp) अणु
		rc = H_PARAMETER;
		जाओ out_मुक्त;
	पूर्ण

	mutex_lock(&gp->tlb_lock);

	अगर (is_load) अणु
		/* Load from the nested guest पूर्णांकo our buffer */
		rc = __kvmhv_copy_tofrom_guest_radix(gp->shaकरोw_lpid, pid,
						     eaddr, buf, शून्य, n);
		अगर (rc)
			जाओ not_found;

		/* Write what was loaded पूर्णांकo our buffer back to the L1 guest */
		vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		rc = kvm_vcpu_ग_लिखो_guest(vcpu, gp_to, buf, n);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
		अगर (rc)
			जाओ not_found;
	पूर्ण अन्यथा अणु
		/* Load the data to be stored from the L1 guest पूर्णांकo our buf */
		vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		rc = kvm_vcpu_पढ़ो_guest(vcpu, gp_from, buf, n);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
		अगर (rc)
			जाओ not_found;

		/* Store from our buffer पूर्णांकo the nested guest */
		rc = __kvmhv_copy_tofrom_guest_radix(gp->shaकरोw_lpid, pid,
						     eaddr, शून्य, buf, n);
		अगर (rc)
			जाओ not_found;
	पूर्ण

out_unlock:
	mutex_unlock(&gp->tlb_lock);
	kvmhv_put_nested(gp);
out_मुक्त:
	kमुक्त(buf);
	वापस rc;
not_found:
	rc = H_NOT_FOUND;
	जाओ out_unlock;
पूर्ण

/*
 * Reload the partition table entry क्रम a guest.
 * Caller must hold gp->tlb_lock.
 */
अटल व्योम kvmhv_update_ptbl_cache(काष्ठा kvm_nested_guest *gp)
अणु
	पूर्णांक ret;
	काष्ठा patb_entry ptbl_entry;
	अचिन्हित दीर्घ ptbl_addr;
	काष्ठा kvm *kvm = gp->l1_host;

	ret = -EFAULT;
	ptbl_addr = (kvm->arch.l1_ptcr & PRTB_MASK) + (gp->l1_lpid << 4);
	अगर (gp->l1_lpid < (1ul << ((kvm->arch.l1_ptcr & PRTS_MASK) + 8))) अणु
		पूर्णांक srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
		ret = kvm_पढ़ो_guest(kvm, ptbl_addr,
				     &ptbl_entry, माप(ptbl_entry));
		srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	पूर्ण
	अगर (ret) अणु
		gp->l1_gr_to_hr = 0;
		gp->process_table = 0;
	पूर्ण अन्यथा अणु
		gp->l1_gr_to_hr = be64_to_cpu(ptbl_entry.patb0);
		gp->process_table = be64_to_cpu(ptbl_entry.patb1);
	पूर्ण
	kvmhv_set_nested_ptbl(gp);
पूर्ण

अटल काष्ठा kvm_nested_guest *kvmhv_alloc_nested(काष्ठा kvm *kvm, अचिन्हित पूर्णांक lpid)
अणु
	काष्ठा kvm_nested_guest *gp;
	दीर्घ shaकरोw_lpid;

	gp = kzalloc(माप(*gp), GFP_KERNEL);
	अगर (!gp)
		वापस शून्य;
	gp->l1_host = kvm;
	gp->l1_lpid = lpid;
	mutex_init(&gp->tlb_lock);
	gp->shaकरोw_pgtable = pgd_alloc(kvm->mm);
	अगर (!gp->shaकरोw_pgtable)
		जाओ out_मुक्त;
	shaकरोw_lpid = kvmppc_alloc_lpid();
	अगर (shaकरोw_lpid < 0)
		जाओ out_मुक्त2;
	gp->shaकरोw_lpid = shaकरोw_lpid;
	gp->radix = 1;

	स_रखो(gp->prev_cpu, -1, माप(gp->prev_cpu));

	वापस gp;

 out_मुक्त2:
	pgd_मुक्त(kvm->mm, gp->shaकरोw_pgtable);
 out_मुक्त:
	kमुक्त(gp);
	वापस शून्य;
पूर्ण

/*
 * Free up any resources allocated क्रम a nested guest.
 */
अटल व्योम kvmhv_release_nested(काष्ठा kvm_nested_guest *gp)
अणु
	काष्ठा kvm *kvm = gp->l1_host;

	अगर (gp->shaकरोw_pgtable) अणु
		/*
		 * No vcpu is using this काष्ठा and no call to
		 * kvmhv_get_nested can find this काष्ठा,
		 * so we करोn't need to hold kvm->mmu_lock.
		 */
		kvmppc_मुक्त_pgtable_radix(kvm, gp->shaकरोw_pgtable,
					  gp->shaकरोw_lpid);
		pgd_मुक्त(kvm->mm, gp->shaकरोw_pgtable);
	पूर्ण
	kvmhv_set_ptbl_entry(gp->shaकरोw_lpid, 0, 0);
	kvmppc_मुक्त_lpid(gp->shaकरोw_lpid);
	kमुक्त(gp);
पूर्ण

अटल व्योम kvmhv_हटाओ_nested(काष्ठा kvm_nested_guest *gp)
अणु
	काष्ठा kvm *kvm = gp->l1_host;
	पूर्णांक lpid = gp->l1_lpid;
	दीर्घ ref;

	spin_lock(&kvm->mmu_lock);
	अगर (gp == kvm->arch.nested_guests[lpid]) अणु
		kvm->arch.nested_guests[lpid] = शून्य;
		अगर (lpid == kvm->arch.max_nested_lpid) अणु
			जबतक (--lpid >= 0 && !kvm->arch.nested_guests[lpid])
				;
			kvm->arch.max_nested_lpid = lpid;
		पूर्ण
		--gp->refcnt;
	पूर्ण
	ref = gp->refcnt;
	spin_unlock(&kvm->mmu_lock);
	अगर (ref == 0)
		kvmhv_release_nested(gp);
पूर्ण

/*
 * Free up all nested resources allocated क्रम this guest.
 * This is called with no vcpus of the guest running, when
 * चयनing the guest to HPT mode or when destroying the
 * guest.
 */
व्योम kvmhv_release_all_nested(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;
	काष्ठा kvm_nested_guest *gp;
	काष्ठा kvm_nested_guest *मुक्तlist = शून्य;
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक srcu_idx;

	spin_lock(&kvm->mmu_lock);
	क्रम (i = 0; i <= kvm->arch.max_nested_lpid; i++) अणु
		gp = kvm->arch.nested_guests[i];
		अगर (!gp)
			जारी;
		kvm->arch.nested_guests[i] = शून्य;
		अगर (--gp->refcnt == 0) अणु
			gp->next = मुक्तlist;
			मुक्तlist = gp;
		पूर्ण
	पूर्ण
	kvm->arch.max_nested_lpid = -1;
	spin_unlock(&kvm->mmu_lock);
	जबतक ((gp = मुक्तlist) != शून्य) अणु
		मुक्तlist = gp->next;
		kvmhv_release_nested(gp);
	पूर्ण

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	kvm_क्रम_each_memslot(memslot, kvm_memslots(kvm))
		kvmhv_मुक्त_memslot_nest_rmap(memslot);
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
पूर्ण

/* caller must hold gp->tlb_lock */
अटल व्योम kvmhv_flush_nested(काष्ठा kvm_nested_guest *gp)
अणु
	काष्ठा kvm *kvm = gp->l1_host;

	spin_lock(&kvm->mmu_lock);
	kvmppc_मुक्त_pgtable_radix(kvm, gp->shaकरोw_pgtable, gp->shaकरोw_lpid);
	spin_unlock(&kvm->mmu_lock);
	kvmhv_flush_lpid(gp->shaकरोw_lpid);
	kvmhv_update_ptbl_cache(gp);
	अगर (gp->l1_gr_to_hr == 0)
		kvmhv_हटाओ_nested(gp);
पूर्ण

काष्ठा kvm_nested_guest *kvmhv_get_nested(काष्ठा kvm *kvm, पूर्णांक l1_lpid,
					  bool create)
अणु
	काष्ठा kvm_nested_guest *gp, *newgp;

	अगर (l1_lpid >= KVM_MAX_NESTED_GUESTS ||
	    l1_lpid >= (1ul << ((kvm->arch.l1_ptcr & PRTS_MASK) + 12 - 4)))
		वापस शून्य;

	spin_lock(&kvm->mmu_lock);
	gp = kvm->arch.nested_guests[l1_lpid];
	अगर (gp)
		++gp->refcnt;
	spin_unlock(&kvm->mmu_lock);

	अगर (gp || !create)
		वापस gp;

	newgp = kvmhv_alloc_nested(kvm, l1_lpid);
	अगर (!newgp)
		वापस शून्य;
	spin_lock(&kvm->mmu_lock);
	अगर (kvm->arch.nested_guests[l1_lpid]) अणु
		/* someone अन्यथा beat us to it */
		gp = kvm->arch.nested_guests[l1_lpid];
	पूर्ण अन्यथा अणु
		kvm->arch.nested_guests[l1_lpid] = newgp;
		++newgp->refcnt;
		gp = newgp;
		newgp = शून्य;
		अगर (l1_lpid > kvm->arch.max_nested_lpid)
			kvm->arch.max_nested_lpid = l1_lpid;
	पूर्ण
	++gp->refcnt;
	spin_unlock(&kvm->mmu_lock);

	अगर (newgp)
		kvmhv_release_nested(newgp);

	वापस gp;
पूर्ण

व्योम kvmhv_put_nested(काष्ठा kvm_nested_guest *gp)
अणु
	काष्ठा kvm *kvm = gp->l1_host;
	दीर्घ ref;

	spin_lock(&kvm->mmu_lock);
	ref = --gp->refcnt;
	spin_unlock(&kvm->mmu_lock);
	अगर (ref == 0)
		kvmhv_release_nested(gp);
पूर्ण

अटल काष्ठा kvm_nested_guest *kvmhv_find_nested(काष्ठा kvm *kvm, पूर्णांक lpid)
अणु
	अगर (lpid > kvm->arch.max_nested_lpid)
		वापस शून्य;
	वापस kvm->arch.nested_guests[lpid];
पूर्ण

pte_t *find_kvm_nested_guest_pte(काष्ठा kvm *kvm, अचिन्हित दीर्घ lpid,
				 अचिन्हित दीर्घ ea, अचिन्हित *hshअगरt)
अणु
	काष्ठा kvm_nested_guest *gp;
	pte_t *pte;

	gp = kvmhv_find_nested(kvm, lpid);
	अगर (!gp)
		वापस शून्य;

	VM_WARN(!spin_is_locked(&kvm->mmu_lock),
		"%s called with kvm mmu_lock not held \n", __func__);
	pte = __find_linux_pte(gp->shaकरोw_pgtable, ea, शून्य, hshअगरt);

	वापस pte;
पूर्ण

अटल अंतरभूत bool kvmhv_n_rmap_is_equal(u64 rmap_1, u64 rmap_2)
अणु
	वापस !((rmap_1 ^ rmap_2) & (RMAP_NESTED_LPID_MASK |
				       RMAP_NESTED_GPA_MASK));
पूर्ण

व्योम kvmhv_insert_nest_rmap(काष्ठा kvm *kvm, अचिन्हित दीर्घ *rmapp,
			    काष्ठा rmap_nested **n_rmap)
अणु
	काष्ठा llist_node *entry = ((काष्ठा llist_head *) rmapp)->first;
	काष्ठा rmap_nested *cursor;
	u64 rmap, new_rmap = (*n_rmap)->rmap;

	/* Are there any existing entries? */
	अगर (!(*rmapp)) अणु
		/* No -> use the rmap as a single entry */
		*rmapp = new_rmap | RMAP_NESTED_IS_SINGLE_ENTRY;
		वापस;
	पूर्ण

	/* Do any entries match what we're trying to insert? */
	क्रम_each_nest_rmap_safe(cursor, entry, &rmap) अणु
		अगर (kvmhv_n_rmap_is_equal(rmap, new_rmap))
			वापस;
	पूर्ण

	/* Do we need to create a list or just add the new entry? */
	rmap = *rmapp;
	अगर (rmap & RMAP_NESTED_IS_SINGLE_ENTRY) /* Not previously a list */
		*rmapp = 0UL;
	llist_add(&((*n_rmap)->list), (काष्ठा llist_head *) rmapp);
	अगर (rmap & RMAP_NESTED_IS_SINGLE_ENTRY) /* Not previously a list */
		(*n_rmap)->list.next = (काष्ठा llist_node *) rmap;

	/* Set शून्य so not मुक्तd by caller */
	*n_rmap = शून्य;
पूर्ण

अटल व्योम kvmhv_update_nest_rmap_rc(काष्ठा kvm *kvm, u64 n_rmap,
				      अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set,
				      अचिन्हित दीर्घ hpa, अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ gpa;
	अचिन्हित पूर्णांक shअगरt, lpid;
	pte_t *ptep;

	gpa = n_rmap & RMAP_NESTED_GPA_MASK;
	lpid = (n_rmap & RMAP_NESTED_LPID_MASK) >> RMAP_NESTED_LPID_SHIFT;

	/* Find the pte */
	ptep = find_kvm_nested_guest_pte(kvm, lpid, gpa, &shअगरt);
	/*
	 * If the pte is present and the pfn is still the same, update the pte.
	 * If the pfn has changed then this is a stale rmap entry, the nested
	 * gpa actually poपूर्णांकs somewhere अन्यथा now, and there is nothing to करो.
	 * XXX A future optimisation would be to हटाओ the rmap entry here.
	 */
	अगर (ptep && pte_present(*ptep) && ((pte_val(*ptep) & mask) == hpa)) अणु
		__radix_pte_update(ptep, clr, set);
		kvmppc_radix_tlbie_page(kvm, gpa, shअगरt, lpid);
	पूर्ण
पूर्ण

/*
 * For a given list of rmap entries, update the rc bits in all ptes in shaकरोw
 * page tables क्रम nested guests which are referenced by the rmap list.
 */
व्योम kvmhv_update_nest_rmap_rc_list(काष्ठा kvm *kvm, अचिन्हित दीर्घ *rmapp,
				    अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set,
				    अचिन्हित दीर्घ hpa, अचिन्हित दीर्घ nbytes)
अणु
	काष्ठा llist_node *entry = ((काष्ठा llist_head *) rmapp)->first;
	काष्ठा rmap_nested *cursor;
	अचिन्हित दीर्घ rmap, mask;

	अगर ((clr | set) & ~(_PAGE_सूचीTY | _PAGE_ACCESSED))
		वापस;

	mask = PTE_RPN_MASK & ~(nbytes - 1);
	hpa &= mask;

	क्रम_each_nest_rmap_safe(cursor, entry, &rmap)
		kvmhv_update_nest_rmap_rc(kvm, rmap, clr, set, hpa, mask);
पूर्ण

अटल व्योम kvmhv_हटाओ_nest_rmap(काष्ठा kvm *kvm, u64 n_rmap,
				   अचिन्हित दीर्घ hpa, अचिन्हित दीर्घ mask)
अणु
	काष्ठा kvm_nested_guest *gp;
	अचिन्हित दीर्घ gpa;
	अचिन्हित पूर्णांक shअगरt, lpid;
	pte_t *ptep;

	gpa = n_rmap & RMAP_NESTED_GPA_MASK;
	lpid = (n_rmap & RMAP_NESTED_LPID_MASK) >> RMAP_NESTED_LPID_SHIFT;
	gp = kvmhv_find_nested(kvm, lpid);
	अगर (!gp)
		वापस;

	/* Find and invalidate the pte */
	ptep = find_kvm_nested_guest_pte(kvm, lpid, gpa, &shअगरt);
	/* Don't spuriously invalidate ptes अगर the pfn has changed */
	अगर (ptep && pte_present(*ptep) && ((pte_val(*ptep) & mask) == hpa))
		kvmppc_unmap_pte(kvm, ptep, gpa, shअगरt, शून्य, gp->shaकरोw_lpid);
पूर्ण

अटल व्योम kvmhv_हटाओ_nest_rmap_list(काष्ठा kvm *kvm, अचिन्हित दीर्घ *rmapp,
					अचिन्हित दीर्घ hpa, अचिन्हित दीर्घ mask)
अणु
	काष्ठा llist_node *entry = llist_del_all((काष्ठा llist_head *) rmapp);
	काष्ठा rmap_nested *cursor;
	अचिन्हित दीर्घ rmap;

	क्रम_each_nest_rmap_safe(cursor, entry, &rmap) अणु
		kvmhv_हटाओ_nest_rmap(kvm, rmap, hpa, mask);
		kमुक्त(cursor);
	पूर्ण
पूर्ण

/* called with kvm->mmu_lock held */
व्योम kvmhv_हटाओ_nest_rmap_range(काष्ठा kvm *kvm,
				  स्थिर काष्ठा kvm_memory_slot *memslot,
				  अचिन्हित दीर्घ gpa, अचिन्हित दीर्घ hpa,
				  अचिन्हित दीर्घ nbytes)
अणु
	अचिन्हित दीर्घ gfn, end_gfn;
	अचिन्हित दीर्घ addr_mask;

	अगर (!memslot)
		वापस;
	gfn = (gpa >> PAGE_SHIFT) - memslot->base_gfn;
	end_gfn = gfn + (nbytes >> PAGE_SHIFT);

	addr_mask = PTE_RPN_MASK & ~(nbytes - 1);
	hpa &= addr_mask;

	क्रम (; gfn < end_gfn; gfn++) अणु
		अचिन्हित दीर्घ *rmap = &memslot->arch.rmap[gfn];
		kvmhv_हटाओ_nest_rmap_list(kvm, rmap, hpa, addr_mask);
	पूर्ण
पूर्ण

अटल व्योम kvmhv_मुक्त_memslot_nest_rmap(काष्ठा kvm_memory_slot *मुक्त)
अणु
	अचिन्हित दीर्घ page;

	क्रम (page = 0; page < मुक्त->npages; page++) अणु
		अचिन्हित दीर्घ rmap, *rmapp = &मुक्त->arch.rmap[page];
		काष्ठा rmap_nested *cursor;
		काष्ठा llist_node *entry;

		entry = llist_del_all((काष्ठा llist_head *) rmapp);
		क्रम_each_nest_rmap_safe(cursor, entry, &rmap)
			kमुक्त(cursor);
	पूर्ण
पूर्ण

अटल bool kvmhv_invalidate_shaकरोw_pte(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_nested_guest *gp,
					दीर्घ gpa, पूर्णांक *shअगरt_ret)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	bool ret = false;
	pte_t *ptep;
	पूर्णांक shअगरt;

	spin_lock(&kvm->mmu_lock);
	ptep = find_kvm_nested_guest_pte(kvm, gp->l1_lpid, gpa, &shअगरt);
	अगर (!shअगरt)
		shअगरt = PAGE_SHIFT;
	अगर (ptep && pte_present(*ptep)) अणु
		kvmppc_unmap_pte(kvm, ptep, gpa, shअगरt, शून्य, gp->shaकरोw_lpid);
		ret = true;
	पूर्ण
	spin_unlock(&kvm->mmu_lock);

	अगर (shअगरt_ret)
		*shअगरt_ret = shअगरt;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक get_ric(अचिन्हित पूर्णांक instr)
अणु
	वापस (instr >> 18) & 0x3;
पूर्ण

अटल अंतरभूत पूर्णांक get_prs(अचिन्हित पूर्णांक instr)
अणु
	वापस (instr >> 17) & 0x1;
पूर्ण

अटल अंतरभूत पूर्णांक get_r(अचिन्हित पूर्णांक instr)
अणु
	वापस (instr >> 16) & 0x1;
पूर्ण

अटल अंतरभूत पूर्णांक get_lpid(अचिन्हित दीर्घ r_val)
अणु
	वापस r_val & 0xffffffff;
पूर्ण

अटल अंतरभूत पूर्णांक get_is(अचिन्हित दीर्घ r_val)
अणु
	वापस (r_val >> 10) & 0x3;
पूर्ण

अटल अंतरभूत पूर्णांक get_ap(अचिन्हित दीर्घ r_val)
अणु
	वापस (r_val >> 5) & 0x7;
पूर्ण

अटल अंतरभूत दीर्घ get_epn(अचिन्हित दीर्घ r_val)
अणु
	वापस r_val >> 12;
पूर्ण

अटल पूर्णांक kvmhv_emulate_tlbie_tlb_addr(काष्ठा kvm_vcpu *vcpu, पूर्णांक lpid,
					पूर्णांक ap, दीर्घ epn)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_nested_guest *gp;
	दीर्घ npages;
	पूर्णांक shअगरt, shaकरोw_shअगरt;
	अचिन्हित दीर्घ addr;

	shअगरt = ap_to_shअगरt(ap);
	addr = epn << 12;
	अगर (shअगरt < 0)
		/* Invalid ap encoding */
		वापस -EINVAL;

	addr &= ~((1UL << shअगरt) - 1);
	npages = 1UL << (shअगरt - PAGE_SHIFT);

	gp = kvmhv_get_nested(kvm, lpid, false);
	अगर (!gp) /* No such guest -> nothing to करो */
		वापस 0;
	mutex_lock(&gp->tlb_lock);

	/* There may be more than one host page backing this single guest pte */
	करो अणु
		kvmhv_invalidate_shaकरोw_pte(vcpu, gp, addr, &shaकरोw_shअगरt);

		npages -= 1UL << (shaकरोw_shअगरt - PAGE_SHIFT);
		addr += 1UL << shaकरोw_shअगरt;
	पूर्ण जबतक (npages > 0);

	mutex_unlock(&gp->tlb_lock);
	kvmhv_put_nested(gp);
	वापस 0;
पूर्ण

अटल व्योम kvmhv_emulate_tlbie_lpid(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_nested_guest *gp, पूर्णांक ric)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;

	mutex_lock(&gp->tlb_lock);
	चयन (ric) अणु
	हाल 0:
		/* Invalidate TLB */
		spin_lock(&kvm->mmu_lock);
		kvmppc_मुक्त_pgtable_radix(kvm, gp->shaकरोw_pgtable,
					  gp->shaकरोw_lpid);
		kvmhv_flush_lpid(gp->shaकरोw_lpid);
		spin_unlock(&kvm->mmu_lock);
		अवरोध;
	हाल 1:
		/*
		 * Invalidate PWC
		 * We करोn't cache this -> nothing to करो
		 */
		अवरोध;
	हाल 2:
		/* Invalidate TLB, PWC and caching of partition table entries */
		kvmhv_flush_nested(gp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&gp->tlb_lock);
पूर्ण

अटल व्योम kvmhv_emulate_tlbie_all_lpid(काष्ठा kvm_vcpu *vcpu, पूर्णांक ric)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_nested_guest *gp;
	पूर्णांक i;

	spin_lock(&kvm->mmu_lock);
	क्रम (i = 0; i <= kvm->arch.max_nested_lpid; i++) अणु
		gp = kvm->arch.nested_guests[i];
		अगर (gp) अणु
			spin_unlock(&kvm->mmu_lock);
			kvmhv_emulate_tlbie_lpid(vcpu, gp, ric);
			spin_lock(&kvm->mmu_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&kvm->mmu_lock);
पूर्ण

अटल पूर्णांक kvmhv_emulate_priv_tlbie(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक instr,
				    अचिन्हित दीर्घ rsval, अचिन्हित दीर्घ rbval)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_nested_guest *gp;
	पूर्णांक r, ric, prs, is, ap;
	पूर्णांक lpid;
	दीर्घ epn;
	पूर्णांक ret = 0;

	ric = get_ric(instr);
	prs = get_prs(instr);
	r = get_r(instr);
	lpid = get_lpid(rsval);
	is = get_is(rbval);

	/*
	 * These हालs are invalid and are not handled:
	 * r   != 1 -> Only radix supported
	 * prs == 1 -> Not HV privileged
	 * ric == 3 -> No cluster bombs क्रम radix
	 * is  == 1 -> Partition scoped translations not associated with pid
	 * (!is) && (ric == 1 || ric == 2) -> Not supported by ISA
	 */
	अगर ((!r) || (prs) || (ric == 3) || (is == 1) ||
	    ((!is) && (ric == 1 || ric == 2)))
		वापस -EINVAL;

	चयन (is) अणु
	हाल 0:
		/*
		 * We know ric == 0
		 * Invalidate TLB क्रम a given target address
		 */
		epn = get_epn(rbval);
		ap = get_ap(rbval);
		ret = kvmhv_emulate_tlbie_tlb_addr(vcpu, lpid, ap, epn);
		अवरोध;
	हाल 2:
		/* Invalidate matching LPID */
		gp = kvmhv_get_nested(kvm, lpid, false);
		अगर (gp) अणु
			kvmhv_emulate_tlbie_lpid(vcpu, gp, ric);
			kvmhv_put_nested(gp);
		पूर्ण
		अवरोध;
	हाल 3:
		/* Invalidate ALL LPIDs */
		kvmhv_emulate_tlbie_all_lpid(vcpu, ric);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This handles the H_TLB_INVALIDATE hcall.
 * Parameters are (r4) tlbie inकाष्ठाion code, (r5) rS contents,
 * (r6) rB contents.
 */
दीर्घ kvmhv_करो_nested_tlbie(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret;

	ret = kvmhv_emulate_priv_tlbie(vcpu, kvmppc_get_gpr(vcpu, 4),
			kvmppc_get_gpr(vcpu, 5), kvmppc_get_gpr(vcpu, 6));
	अगर (ret)
		वापस H_PARAMETER;
	वापस H_SUCCESS;
पूर्ण

/* Used to convert a nested guest real address to a L1 guest real address */
अटल पूर्णांक kvmhv_translate_addr_nested(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा kvm_nested_guest *gp,
				       अचिन्हित दीर्घ n_gpa, अचिन्हित दीर्घ dsisr,
				       काष्ठा kvmppc_pte *gpte_p)
अणु
	u64 fault_addr, flags = dsisr & DSISR_ISSTORE;
	पूर्णांक ret;

	ret = kvmppc_mmu_walk_radix_tree(vcpu, n_gpa, gpte_p, gp->l1_gr_to_hr,
					 &fault_addr);

	अगर (ret) अणु
		/* We didn't find a pte */
		अगर (ret == -EINVAL) अणु
			/* Unsupported mmu config */
			flags |= DSISR_UNSUPP_MMU;
		पूर्ण अन्यथा अगर (ret == -ENOENT) अणु
			/* No translation found */
			flags |= DSISR_NOHPTE;
		पूर्ण अन्यथा अगर (ret == -EFAULT) अणु
			/* Couldn't access L1 real address */
			flags |= DSISR_PRTABLE_FAULT;
			vcpu->arch.fault_gpa = fault_addr;
		पूर्ण अन्यथा अणु
			/* Unknown error */
			वापस ret;
		पूर्ण
		जाओ क्रमward_to_l1;
	पूर्ण अन्यथा अणु
		/* We found a pte -> check permissions */
		अगर (dsisr & DSISR_ISSTORE) अणु
			/* Can we ग_लिखो? */
			अगर (!gpte_p->may_ग_लिखो) अणु
				flags |= DSISR_PROTFAULT;
				जाओ क्रमward_to_l1;
			पूर्ण
		पूर्ण अन्यथा अगर (vcpu->arch.trap == BOOK3S_INTERRUPT_H_INST_STORAGE) अणु
			/* Can we execute? */
			अगर (!gpte_p->may_execute) अणु
				flags |= SRR1_ISI_N_G_OR_CIP;
				जाओ क्रमward_to_l1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Can we पढ़ो? */
			अगर (!gpte_p->may_पढ़ो && !gpte_p->may_ग_लिखो) अणु
				flags |= DSISR_PROTFAULT;
				जाओ क्रमward_to_l1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

क्रमward_to_l1:
	vcpu->arch.fault_dsisr = flags;
	अगर (vcpu->arch.trap == BOOK3S_INTERRUPT_H_INST_STORAGE) अणु
		vcpu->arch.shregs.msr &= SRR1_MSR_BITS;
		vcpu->arch.shregs.msr |= flags;
	पूर्ण
	वापस RESUME_HOST;
पूर्ण

अटल दीर्घ kvmhv_handle_nested_set_rc(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा kvm_nested_guest *gp,
				       अचिन्हित दीर्घ n_gpa,
				       काष्ठा kvmppc_pte gpte,
				       अचिन्हित दीर्घ dsisr)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	bool writing = !!(dsisr & DSISR_ISSTORE);
	u64 pgflags;
	दीर्घ ret;

	/* Are the rc bits set in the L1 partition scoped pte? */
	pgflags = _PAGE_ACCESSED;
	अगर (writing)
		pgflags |= _PAGE_सूचीTY;
	अगर (pgflags & ~gpte.rc)
		वापस RESUME_HOST;

	spin_lock(&kvm->mmu_lock);
	/* Set the rc bit in the pte of our (L0) pgtable क्रम the L1 guest */
	ret = kvmppc_hv_handle_set_rc(kvm, false, writing,
				      gpte.raddr, kvm->arch.lpid);
	अगर (!ret) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* Set the rc bit in the pte of the shaकरोw_pgtable क्रम the nest guest */
	ret = kvmppc_hv_handle_set_rc(kvm, true, writing,
				      n_gpa, gp->l1_lpid);
	अगर (!ret)
		ret = -EINVAL;
	अन्यथा
		ret = 0;

out_unlock:
	spin_unlock(&kvm->mmu_lock);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_radix_level_to_shअगरt(पूर्णांक level)
अणु
	चयन (level) अणु
	हाल 2:
		वापस PUD_SHIFT;
	हाल 1:
		वापस PMD_SHIFT;
	शेष:
		वापस PAGE_SHIFT;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_radix_shअगरt_to_level(पूर्णांक shअगरt)
अणु
	अगर (shअगरt == PUD_SHIFT)
		वापस 2;
	अगर (shअगरt == PMD_SHIFT)
		वापस 1;
	अगर (shअगरt == PAGE_SHIFT)
		वापस 0;
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

/* called with gp->tlb_lock held */
अटल दीर्घ पूर्णांक __kvmhv_nested_page_fault(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा kvm_nested_guest *gp)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_memory_slot *memslot;
	काष्ठा rmap_nested *n_rmap;
	काष्ठा kvmppc_pte gpte;
	pte_t pte, *pte_p;
	अचिन्हित दीर्घ mmu_seq;
	अचिन्हित दीर्घ dsisr = vcpu->arch.fault_dsisr;
	अचिन्हित दीर्घ ea = vcpu->arch.fault_dar;
	अचिन्हित दीर्घ *rmapp;
	अचिन्हित दीर्घ n_gpa, gpa, gfn, perm = 0UL;
	अचिन्हित पूर्णांक shअगरt, l1_shअगरt, level;
	bool writing = !!(dsisr & DSISR_ISSTORE);
	bool kvm_ro = false;
	दीर्घ पूर्णांक ret;

	अगर (!gp->l1_gr_to_hr) अणु
		kvmhv_update_ptbl_cache(gp);
		अगर (!gp->l1_gr_to_hr)
			वापस RESUME_HOST;
	पूर्ण

	/* Convert the nested guest real address पूर्णांकo a L1 guest real address */

	n_gpa = vcpu->arch.fault_gpa & ~0xF000000000000FFFULL;
	अगर (!(dsisr & DSISR_PRTABLE_FAULT))
		n_gpa |= ea & 0xFFF;
	ret = kvmhv_translate_addr_nested(vcpu, gp, n_gpa, dsisr, &gpte);

	/*
	 * If the hardware found a translation but we करोn't now have a usable
	 * translation in the l1 partition-scoped tree, हटाओ the shaकरोw pte
	 * and let the guest retry.
	 */
	अगर (ret == RESUME_HOST &&
	    (dsisr & (DSISR_PROTFAULT | DSISR_BADACCESS | DSISR_NOEXEC_OR_G |
		      DSISR_BAD_COPYPASTE)))
		जाओ inval;
	अगर (ret)
		वापस ret;

	/* Failed to set the reference/change bits */
	अगर (dsisr & DSISR_SET_RC) अणु
		ret = kvmhv_handle_nested_set_rc(vcpu, gp, n_gpa, gpte, dsisr);
		अगर (ret == RESUME_HOST)
			वापस ret;
		अगर (ret)
			जाओ inval;
		dsisr &= ~DSISR_SET_RC;
		अगर (!(dsisr & (DSISR_BAD_FAULT_64S | DSISR_NOHPTE |
			       DSISR_PROTFAULT)))
			वापस RESUME_GUEST;
	पूर्ण

	/*
	 * We took an HISI or HDSI जबतक we were running a nested guest which
	 * means we have no partition scoped translation क्रम that. This means
	 * we need to insert a pte क्रम the mapping पूर्णांकo our shaकरोw_pgtable.
	 */

	l1_shअगरt = gpte.page_shअगरt;
	अगर (l1_shअगरt < PAGE_SHIFT) अणु
		/* We करोn't support l1 using a page size smaller than our own */
		pr_err("KVM: L1 guest page shift (%d) less than our own (%d)\n",
			l1_shअगरt, PAGE_SHIFT);
		वापस -EINVAL;
	पूर्ण
	gpa = gpte.raddr;
	gfn = gpa >> PAGE_SHIFT;

	/* 1. Get the corresponding host memslot */

	memslot = gfn_to_memslot(kvm, gfn);
	अगर (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID)) अणु
		अगर (dsisr & (DSISR_PRTABLE_FAULT | DSISR_BADACCESS)) अणु
			/* unusual error -> reflect to the guest as a DSI */
			kvmppc_core_queue_data_storage(vcpu, ea, dsisr);
			वापस RESUME_GUEST;
		पूर्ण

		/* passthrough of emulated MMIO हाल */
		वापस kvmppc_hv_emulate_mmio(vcpu, gpa, ea, writing);
	पूर्ण
	अगर (memslot->flags & KVM_MEM_READONLY) अणु
		अगर (writing) अणु
			/* Give the guest a DSI */
			kvmppc_core_queue_data_storage(vcpu, ea,
					DSISR_ISSTORE | DSISR_PROTFAULT);
			वापस RESUME_GUEST;
		पूर्ण
		kvm_ro = true;
	पूर्ण

	/* 2. Find the host pte क्रम this L1 guest real address */

	/* Used to check क्रम invalidations in progress */
	mmu_seq = kvm->mmu_notअगरier_seq;
	smp_rmb();

	/* See अगर can find translation in our partition scoped tables क्रम L1 */
	pte = __pte(0);
	spin_lock(&kvm->mmu_lock);
	pte_p = find_kvm_secondary_pte(kvm, gpa, &shअगरt);
	अगर (!shअगरt)
		shअगरt = PAGE_SHIFT;
	अगर (pte_p)
		pte = *pte_p;
	spin_unlock(&kvm->mmu_lock);

	अगर (!pte_present(pte) || (writing && !(pte_val(pte) & _PAGE_WRITE))) अणु
		/* No suitable pte found -> try to insert a mapping */
		ret = kvmppc_book3s_instantiate_page(vcpu, gpa, memslot,
					writing, kvm_ro, &pte, &level);
		अगर (ret == -EAGAIN)
			वापस RESUME_GUEST;
		अन्यथा अगर (ret)
			वापस ret;
		shअगरt = kvmppc_radix_level_to_shअगरt(level);
	पूर्ण
	/* Align gfn to the start of the page */
	gfn = (gpa & ~((1UL << shअगरt) - 1)) >> PAGE_SHIFT;

	/* 3. Compute the pte we need to insert क्रम nest_gpa -> host r_addr */

	/* The permissions is the combination of the host and l1 guest ptes */
	perm |= gpte.may_पढ़ो ? 0UL : _PAGE_READ;
	perm |= gpte.may_ग_लिखो ? 0UL : _PAGE_WRITE;
	perm |= gpte.may_execute ? 0UL : _PAGE_EXEC;
	/* Only set accessed/dirty (rc) bits अगर set in host and l1 guest ptes */
	perm |= (gpte.rc & _PAGE_ACCESSED) ? 0UL : _PAGE_ACCESSED;
	perm |= ((gpte.rc & _PAGE_सूचीTY) && writing) ? 0UL : _PAGE_सूचीTY;
	pte = __pte(pte_val(pte) & ~perm);

	/* What size pte can we insert? */
	अगर (shअगरt > l1_shअगरt) अणु
		u64 mask;
		अचिन्हित पूर्णांक actual_shअगरt = PAGE_SHIFT;
		अगर (PMD_SHIFT < l1_shअगरt)
			actual_shअगरt = PMD_SHIFT;
		mask = (1UL << shअगरt) - (1UL << actual_shअगरt);
		pte = __pte(pte_val(pte) | (gpa & mask));
		shअगरt = actual_shअगरt;
	पूर्ण
	level = kvmppc_radix_shअगरt_to_level(shअगरt);
	n_gpa &= ~((1UL << shअगरt) - 1);

	/* 4. Insert the pte पूर्णांकo our shaकरोw_pgtable */

	n_rmap = kzalloc(माप(*n_rmap), GFP_KERNEL);
	अगर (!n_rmap)
		वापस RESUME_GUEST; /* Let the guest try again */
	n_rmap->rmap = (n_gpa & RMAP_NESTED_GPA_MASK) |
		(((अचिन्हित दीर्घ) gp->l1_lpid) << RMAP_NESTED_LPID_SHIFT);
	rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
	ret = kvmppc_create_pte(kvm, gp->shaकरोw_pgtable, pte, n_gpa, level,
				mmu_seq, gp->shaकरोw_lpid, rmapp, &n_rmap);
	kमुक्त(n_rmap);
	अगर (ret == -EAGAIN)
		ret = RESUME_GUEST;	/* Let the guest try again */

	वापस ret;

 inval:
	kvmhv_invalidate_shaकरोw_pte(vcpu, gp, n_gpa, शून्य);
	वापस RESUME_GUEST;
पूर्ण

दीर्घ पूर्णांक kvmhv_nested_page_fault(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_nested_guest *gp = vcpu->arch.nested;
	दीर्घ पूर्णांक ret;

	mutex_lock(&gp->tlb_lock);
	ret = __kvmhv_nested_page_fault(vcpu, gp);
	mutex_unlock(&gp->tlb_lock);
	वापस ret;
पूर्ण

पूर्णांक kvmhv_nested_next_lpid(काष्ठा kvm *kvm, पूर्णांक lpid)
अणु
	पूर्णांक ret = -1;

	spin_lock(&kvm->mmu_lock);
	जबतक (++lpid <= kvm->arch.max_nested_lpid) अणु
		अगर (kvm->arch.nested_guests[lpid]) अणु
			ret = lpid;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&kvm->mmu_lock);
	वापस ret;
पूर्ण
