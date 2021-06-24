<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright 2012 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/hmi.h>
#समावेश <यंत्र/kvm_ppc.h>

/* SRR1 bits क्रम machine check on POWER7 */
#घोषणा SRR1_MC_LDSTERR		(1ul << (63-42))
#घोषणा SRR1_MC_IFETCH_SH	(63-45)
#घोषणा SRR1_MC_IFETCH_MASK	0x7
#घोषणा SRR1_MC_IFETCH_SLBPAR		2	/* SLB parity error */
#घोषणा SRR1_MC_IFETCH_SLBMULTI		3	/* SLB multi-hit */
#घोषणा SRR1_MC_IFETCH_SLBPARMULTI	4	/* SLB parity + multi-hit */
#घोषणा SRR1_MC_IFETCH_TLBMULTI		5	/* I-TLB multi-hit */

/* DSISR bits क्रम machine check on POWER7 */
#घोषणा DSISR_MC_DERAT_MULTI	0x800		/* D-ERAT multi-hit */
#घोषणा DSISR_MC_TLB_MULTI	0x400		/* D-TLB multi-hit */
#घोषणा DSISR_MC_SLB_PARITY	0x100		/* SLB parity error */
#घोषणा DSISR_MC_SLB_MULTI	0x080		/* SLB multi-hit */
#घोषणा DSISR_MC_SLB_PARMULTI	0x040		/* SLB parity + multi-hit */

/* POWER7 SLB flush and reload */
अटल व्योम reload_slb(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा slb_shaकरोw *slb;
	अचिन्हित दीर्घ i, n;

	/* First clear out SLB */
	यंत्र अस्थिर("slbmte %0,%0; slbia" : : "r" (0));

	/* Do they have an SLB shaकरोw buffer रेजिस्टरed? */
	slb = vcpu->arch.slb_shaकरोw.pinned_addr;
	अगर (!slb)
		वापस;

	/* Sanity check */
	n = min_t(u32, be32_to_cpu(slb->persistent), SLB_MIN_SIZE);
	अगर ((व्योम *) &slb->save_area[n] > vcpu->arch.slb_shaकरोw.pinned_end)
		वापस;

	/* Load up the SLB from that */
	क्रम (i = 0; i < n; ++i) अणु
		अचिन्हित दीर्घ rb = be64_to_cpu(slb->save_area[i].esid);
		अचिन्हित दीर्घ rs = be64_to_cpu(slb->save_area[i].vsid);

		rb = (rb & ~0xFFFul) | i;	/* insert entry number */
		यंत्र अस्थिर("slbmte %0,%1" : : "r" (rs), "r" (rb));
	पूर्ण
पूर्ण

/*
 * On POWER7, see अगर we can handle a machine check that occurred inside
 * the guest in real mode, without चयनing to the host partition.
 */
अटल दीर्घ kvmppc_realmode_mc_घातer7(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ srr1 = vcpu->arch.shregs.msr;
	दीर्घ handled = 1;

	अगर (srr1 & SRR1_MC_LDSTERR) अणु
		/* error on load/store */
		अचिन्हित दीर्घ dsisr = vcpu->arch.shregs.dsisr;

		अगर (dsisr & (DSISR_MC_SLB_PARMULTI | DSISR_MC_SLB_MULTI |
			     DSISR_MC_SLB_PARITY | DSISR_MC_DERAT_MULTI)) अणु
			/* flush and reload SLB; flushes D-ERAT too */
			reload_slb(vcpu);
			dsisr &= ~(DSISR_MC_SLB_PARMULTI | DSISR_MC_SLB_MULTI |
				   DSISR_MC_SLB_PARITY | DSISR_MC_DERAT_MULTI);
		पूर्ण
		अगर (dsisr & DSISR_MC_TLB_MULTI) अणु
			tlbiel_all_lpid(vcpu->kvm->arch.radix);
			dsisr &= ~DSISR_MC_TLB_MULTI;
		पूर्ण
		/* Any other errors we करोn't understand? */
		अगर (dsisr & 0xffffffffUL)
			handled = 0;
	पूर्ण

	चयन ((srr1 >> SRR1_MC_IFETCH_SH) & SRR1_MC_IFETCH_MASK) अणु
	हाल 0:
		अवरोध;
	हाल SRR1_MC_IFETCH_SLBPAR:
	हाल SRR1_MC_IFETCH_SLBMULTI:
	हाल SRR1_MC_IFETCH_SLBPARMULTI:
		reload_slb(vcpu);
		अवरोध;
	हाल SRR1_MC_IFETCH_TLBMULTI:
		tlbiel_all_lpid(vcpu->kvm->arch.radix);
		अवरोध;
	शेष:
		handled = 0;
	पूर्ण

	वापस handled;
पूर्ण

व्योम kvmppc_realmode_machine_check(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा machine_check_event mce_evt;
	दीर्घ handled;

	अगर (vcpu->kvm->arch.fwnmi_enabled) अणु
		/* FWNMI guests handle their own recovery */
		handled = 0;
	पूर्ण अन्यथा अणु
		handled = kvmppc_realmode_mc_घातer7(vcpu);
	पूर्ण

	/*
	 * Now get the event and stash it in the vcpu काष्ठा so it can
	 * be handled by the primary thपढ़ो in भव mode.  We can't
	 * call machine_check_queue_event() here अगर we are running on
	 * an offline secondary thपढ़ो.
	 */
	अगर (get_mce_event(&mce_evt, MCE_EVENT_RELEASE)) अणु
		अगर (handled && mce_evt.version == MCE_V1)
			mce_evt.disposition = MCE_DISPOSITION_RECOVERED;
	पूर्ण अन्यथा अणु
		स_रखो(&mce_evt, 0, माप(mce_evt));
	पूर्ण

	vcpu->arch.mce_evt = mce_evt;
पूर्ण

/* Check अगर dynamic split is in क्रमce and वापस subcore size accordingly. */
अटल अंतरभूत पूर्णांक kvmppc_cur_subcore_size(व्योम)
अणु
	अगर (local_paca->kvm_hstate.kvm_split_mode)
		वापस local_paca->kvm_hstate.kvm_split_mode->subcore_size;

	वापस thपढ़ोs_per_subcore;
पूर्ण

व्योम kvmppc_subcore_enter_guest(व्योम)
अणु
	पूर्णांक thपढ़ो_id, subcore_id;

	thपढ़ो_id = cpu_thपढ़ो_in_core(local_paca->paca_index);
	subcore_id = thपढ़ो_id / kvmppc_cur_subcore_size();

	local_paca->sibling_subcore_state->in_guest[subcore_id] = 1;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_subcore_enter_guest);

व्योम kvmppc_subcore_निकास_guest(व्योम)
अणु
	पूर्णांक thपढ़ो_id, subcore_id;

	thपढ़ो_id = cpu_thपढ़ो_in_core(local_paca->paca_index);
	subcore_id = thपढ़ो_id / kvmppc_cur_subcore_size();

	local_paca->sibling_subcore_state->in_guest[subcore_id] = 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_subcore_निकास_guest);

अटल bool kvmppc_tb_resync_required(व्योम)
अणु
	अगर (test_and_set_bit(CORE_TB_RESYNC_REQ_BIT,
				&local_paca->sibling_subcore_state->flags))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम kvmppc_tb_resync_करोne(व्योम)
अणु
	clear_bit(CORE_TB_RESYNC_REQ_BIT,
			&local_paca->sibling_subcore_state->flags);
पूर्ण

/*
 * kvmppc_realmode_hmi_handler() is called only by primary thपढ़ो during
 * guest निकास path.
 *
 * There are multiple reasons why HMI could occur, one of them is
 * Timebase (TB) error. If this HMI is due to TB error, then TB would
 * have been in stopped state. The opal hmi handler Will fix it and
 * restore the TB value with host समयbase value. For HMI caused due
 * to non-TB errors, opal hmi handler will not touch/restore TB रेजिस्टर
 * and hence there won't be any change in TB value.
 *
 * Since we are not sure about the cause of this HMI, we can't be sure
 * about the content of TB रेजिस्टर whether it holds guest or host समयbase
 * value. Hence the idea is to resync the TB on every HMI, so that we
 * know about the exact state of the TB value. Resync TB call will
 * restore TB to host समयbase.
 *
 * Things to consider:
 * - On TB error, HMI पूर्णांकerrupt is reported on all the thपढ़ोs of the core
 *   that has encountered TB error irrespective of split-core mode.
 * - The very first thपढ़ो on the core that get chance to fix TB error
 *   would rsync the TB with local chipTOD value.
 * - The resync TB is a core level action i.e. it will sync all the TBs
 *   in that core independent of split-core mode. This means अगर we trigger
 *   TB sync from a thपढ़ो from one subcore, it would affect TB values of
 *   sibling subcores of the same core.
 *
 * All thपढ़ोs need to co-ordinate beक्रमe making opal hmi handler.
 * All thपढ़ोs will use sibling_subcore_state->in_guest[] (shared by all
 * thपढ़ोs in the core) in paca which holds inक्रमmation about whether
 * sibling subcores are in Guest mode or host mode. The in_guest[] array
 * is of size MAX_SUBCORE_PER_CORE=4, indexed using subcore id to set/unset
 * subcore status. Only primary thपढ़ोs from each subcore is responsible
 * to set/unset its designated array element जबतक entering/निकासing the
 * guset.
 *
 * After invoking opal hmi handler call, one of the thपढ़ो (of entire core)
 * will need to resync the TB. Bit 63 from subcore state biपंचांगap flags
 * (sibling_subcore_state->flags) will be used to co-ordinate between
 * primary thपढ़ोs to decide who takes up the responsibility.
 *
 * This is what we करो:
 * - Primary thपढ़ो from each subcore tries to set resync required bit[63]
 *   of paca->sibling_subcore_state->flags.
 * - The first primary thपढ़ो that is able to set the flag takes the
 *   responsibility of TB resync. (Let us call it as thपढ़ो leader)
 * - All other thपढ़ोs which are in host will call
 *   रुको_क्रम_subcore_guest_निकास() and रुको क्रम in_guest[0-3] from
 *   paca->sibling_subcore_state to get cleared.
 * - All the primary thपढ़ो will clear its subcore status from subcore
 *   state in_guest[] array respectively.
 * - Once all primary thपढ़ोs clear in_guest[0-3], all of them will invoke
 *   opal hmi handler.
 * - Now all thपढ़ोs will रुको क्रम TB resync to complete by invoking
 *   रुको_क्रम_tb_resync() except the thपढ़ो leader.
 * - Thपढ़ो leader will करो a TB resync by invoking opal_resync_समयbase()
 *   call and the it will clear the resync required bit.
 * - All other thपढ़ोs will now come out of resync रुको loop and proceed
 *   with inभागidual execution.
 * - On वापस of this function, primary thपढ़ो will संकेत all
 *   secondary thपढ़ोs to proceed.
 * - All secondary thपढ़ोs will eventually call opal hmi handler on
 *   their निकास path.
 *
 * Returns 1 अगर the समयbase offset should be applied, 0 अगर not.
 */

दीर्घ kvmppc_realmode_hmi_handler(व्योम)
अणु
	bool resync_req;

	local_paca->hmi_irqs++;

	अगर (hmi_handle_debugtrig(शून्य) >= 0)
		वापस 1;

	/*
	 * By now primary thपढ़ो has alपढ़ोy completed guest->host
	 * partition चयन but haven't संकेतed secondaries yet.
	 * All the secondary thपढ़ोs on this subcore is रुकोing
	 * क्रम primary thपढ़ो to संकेत them to go ahead.
	 *
	 * For thपढ़ोs from subcore which isn't in guest, they all will
	 * रुको until all other subcores on this core निकास the guest.
	 *
	 * Now set the resync required bit. If you are the first to
	 * set this bit then kvmppc_tb_resync_required() function will
	 * वापस true. For rest all other subcores
	 * kvmppc_tb_resync_required() will वापस false.
	 *
	 * If resync_req == true, then this thपढ़ो is responsible to
	 * initiate TB resync after hmi handler has completed.
	 * All other thपढ़ोs on this core will रुको until this thपढ़ो
	 * clears the resync required bit flag.
	 */
	resync_req = kvmppc_tb_resync_required();

	/* Reset the subcore status to indicate it has निकासed guest */
	kvmppc_subcore_निकास_guest();

	/*
	 * Wait क्रम other subcores on this core to निकास the guest.
	 * All the primary thपढ़ोs and thपढ़ोs from subcore that are
	 * not in guest will रुको here until all subcores are out
	 * of guest context.
	 */
	रुको_क्रम_subcore_guest_निकास();

	/*
	 * At this poपूर्णांक we are sure that primary thपढ़ोs from each
	 * subcore on this core have completed guest->host partition
	 * चयन. Now it is safe to call HMI handler.
	 */
	अगर (ppc_md.hmi_exception_early)
		ppc_md.hmi_exception_early(शून्य);

	/*
	 * Check अगर this thपढ़ो is responsible to resync TB.
	 * All other thपढ़ोs will रुको until this thपढ़ो completes the
	 * TB resync.
	 */
	अगर (resync_req) अणु
		opal_resync_समयbase();
		/* Reset TB resync req bit */
		kvmppc_tb_resync_करोne();
	पूर्ण अन्यथा अणु
		रुको_क्रम_tb_resync();
	पूर्ण

	/*
	 * Reset tb_offset_applied so the guest निकास code won't try
	 * to subtract the previous समयbase offset from the समयbase.
	 */
	अगर (local_paca->kvm_hstate.kvm_vcore)
		local_paca->kvm_hstate.kvm_vcore->tb_offset_applied = 0;

	वापस 0;
पूर्ण
