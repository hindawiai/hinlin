<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Michael Ellerman, IBM Corporation.
 * Copyright 2012 Benjamin Herrenschmidt, IBM Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/synch.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/pnv-pci.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/smp.h>

#समावेश "book3s_xics.h"

#घोषणा DEBUG_PASSUP

पूर्णांक h_ipi_redirect = 1;
EXPORT_SYMBOL(h_ipi_redirect);
पूर्णांक kvm_irq_bypass = 1;
EXPORT_SYMBOL(kvm_irq_bypass);

अटल व्योम icp_rm_deliver_irq(काष्ठा kvmppc_xics *xics, काष्ठा kvmppc_icp *icp,
			    u32 new_irq, bool check_resend);
अटल पूर्णांक xics_opal_set_server(अचिन्हित पूर्णांक hw_irq, पूर्णांक server_cpu);

/* -- ICS routines -- */
अटल व्योम ics_rm_check_resend(काष्ठा kvmppc_xics *xics,
				काष्ठा kvmppc_ics *ics, काष्ठा kvmppc_icp *icp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) अणु
		काष्ठा ics_irq_state *state = &ics->irq_state[i];
		अगर (state->resend)
			icp_rm_deliver_irq(xics, icp, state->number, true);
	पूर्ण

पूर्ण

/* -- ICP routines -- */

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत व्योम icp_send_hcore_msg(पूर्णांक hcore, काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक hcpu;

	hcpu = hcore << thपढ़ोs_shअगरt;
	kvmppc_host_rm_ops_hv->rm_core[hcore].rm_data = vcpu;
	smp_muxed_ipi_set_message(hcpu, PPC_MSG_RM_HOST_ACTION);
	kvmppc_set_host_ipi(hcpu);
	smp_mb();
	kvmhv_rm_send_ipi(hcpu);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम icp_send_hcore_msg(पूर्णांक hcore, काष्ठा kvm_vcpu *vcpu) अणु पूर्ण
#पूर्ण_अगर

/*
 * We start the search from our current CPU Id in the core map
 * and go in a circle until we get back to our ID looking क्रम a
 * core that is running in host context and that hasn't alपढ़ोy
 * been targeted क्रम another rm_host_ops.
 *
 * In the future, could consider using a fairer algorithm (one
 * that distributes the IPIs better)
 *
 * Returns -1, अगर no CPU could be found in the host
 * Else, वापसs a CPU Id which has been reserved क्रम use
 */
अटल अंतरभूत पूर्णांक grab_next_hostcore(पूर्णांक start,
		काष्ठा kvmppc_host_rm_core *rm_core, पूर्णांक max, पूर्णांक action)
अणु
	bool success;
	पूर्णांक core;
	जोड़ kvmppc_rm_state old, new;

	क्रम (core = start + 1; core < max; core++)  अणु
		old = new = READ_ONCE(rm_core[core].rm_state);

		अगर (!old.in_host || old.rm_action)
			जारी;

		/* Try to grab this host core अगर not taken alपढ़ोy. */
		new.rm_action = action;

		success = cmpxchg64(&rm_core[core].rm_state.raw,
						old.raw, new.raw) == old.raw;
		अगर (success) अणु
			/*
			 * Make sure that the store to the rm_action is made
			 * visible beक्रमe we वापस to caller (and the
			 * subsequent store to rm_data) to synchronize with
			 * the IPI handler.
			 */
			smp_wmb();
			वापस core;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक find_available_hostcore(पूर्णांक action)
अणु
	पूर्णांक core;
	पूर्णांक my_core = smp_processor_id() >> thपढ़ोs_shअगरt;
	काष्ठा kvmppc_host_rm_core *rm_core = kvmppc_host_rm_ops_hv->rm_core;

	core = grab_next_hostcore(my_core, rm_core, cpu_nr_cores(), action);
	अगर (core == -1)
		core = grab_next_hostcore(core, rm_core, my_core, action);

	वापस core;
पूर्ण

अटल व्योम icp_rm_set_vcpu_irq(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_vcpu *this_vcpu)
अणु
	काष्ठा kvmppc_icp *this_icp = this_vcpu->arch.icp;
	पूर्णांक cpu;
	पूर्णांक hcore;

	/* Mark the target VCPU as having an पूर्णांकerrupt pending */
	vcpu->stat.queue_पूर्णांकr++;
	set_bit(BOOK3S_IRQPRIO_EXTERNAL, &vcpu->arch.pending_exceptions);

	/* Kick self ? Just set MER and वापस */
	अगर (vcpu == this_vcpu) अणु
		mtspr(SPRN_LPCR, mfspr(SPRN_LPCR) | LPCR_MER);
		वापस;
	पूर्ण

	अगर (xive_enabled() && kvmhv_on_pseries()) अणु
		/* No XICS access or hypercalls available, too hard */
		this_icp->rm_action |= XICS_RM_KICK_VCPU;
		this_icp->rm_kick_target = vcpu;
		वापस;
	पूर्ण

	/*
	 * Check अगर the core is loaded,
	 * अगर not, find an available host core to post to wake the VCPU,
	 * अगर we can't find one, set up state to eventually वापस too hard.
	 */
	cpu = vcpu->arch.thपढ़ो_cpu;
	अगर (cpu < 0 || cpu >= nr_cpu_ids) अणु
		hcore = -1;
		अगर (kvmppc_host_rm_ops_hv && h_ipi_redirect)
			hcore = find_available_hostcore(XICS_RM_KICK_VCPU);
		अगर (hcore != -1) अणु
			icp_send_hcore_msg(hcore, vcpu);
		पूर्ण अन्यथा अणु
			this_icp->rm_action |= XICS_RM_KICK_VCPU;
			this_icp->rm_kick_target = vcpu;
		पूर्ण
		वापस;
	पूर्ण

	smp_mb();
	kvmhv_rm_send_ipi(cpu);
पूर्ण

अटल व्योम icp_rm_clr_vcpu_irq(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Note: Only called on self ! */
	clear_bit(BOOK3S_IRQPRIO_EXTERNAL, &vcpu->arch.pending_exceptions);
	mtspr(SPRN_LPCR, mfspr(SPRN_LPCR) & ~LPCR_MER);
पूर्ण

अटल अंतरभूत bool icp_rm_try_update(काष्ठा kvmppc_icp *icp,
				     जोड़ kvmppc_icp_state old,
				     जोड़ kvmppc_icp_state new)
अणु
	काष्ठा kvm_vcpu *this_vcpu = local_paca->kvm_hstate.kvm_vcpu;
	bool success;

	/* Calculate new output value */
	new.out_ee = (new.xisr && (new.pending_pri < new.cppr));

	/* Attempt atomic update */
	success = cmpxchg64(&icp->state.raw, old.raw, new.raw) == old.raw;
	अगर (!success)
		जाओ bail;

	/*
	 * Check क्रम output state update
	 *
	 * Note that this is racy since another processor could be updating
	 * the state alपढ़ोy. This is why we never clear the पूर्णांकerrupt output
	 * here, we only ever set it. The clear only happens prior to करोing
	 * an update and only by the processor itself. Currently we करो it
	 * in Accept (H_XIRR) and Up_Cppr (H_XPPR).
	 *
	 * We also करो not try to figure out whether the EE state has changed,
	 * we unconditionally set it अगर the new state calls क्रम it. The reason
	 * क्रम that is that we opportunistically हटाओ the pending पूर्णांकerrupt
	 * flag when raising CPPR, so we need to set it back here अगर an
	 * पूर्णांकerrupt is still pending.
	 */
	अगर (new.out_ee)
		icp_rm_set_vcpu_irq(icp->vcpu, this_vcpu);

	/* Expose the state change क्रम debug purposes */
	this_vcpu->arch.icp->rm_dbgstate = new;
	this_vcpu->arch.icp->rm_dbgtgt = icp->vcpu;

 bail:
	वापस success;
पूर्ण

अटल अंतरभूत पूर्णांक check_too_hard(काष्ठा kvmppc_xics *xics,
				 काष्ठा kvmppc_icp *icp)
अणु
	वापस (xics->real_mode_dbg || icp->rm_action) ? H_TOO_HARD : H_SUCCESS;
पूर्ण

अटल व्योम icp_rm_check_resend(काष्ठा kvmppc_xics *xics,
			     काष्ठा kvmppc_icp *icp)
अणु
	u32 icsid;

	/* Order this load with the test क्रम need_resend in the caller */
	smp_rmb();
	क्रम_each_set_bit(icsid, icp->resend_map, xics->max_icsid + 1) अणु
		काष्ठा kvmppc_ics *ics = xics->ics[icsid];

		अगर (!test_and_clear_bit(icsid, icp->resend_map))
			जारी;
		अगर (!ics)
			जारी;
		ics_rm_check_resend(xics, ics, icp);
	पूर्ण
पूर्ण

अटल bool icp_rm_try_to_deliver(काष्ठा kvmppc_icp *icp, u32 irq, u8 priority,
			       u32 *reject)
अणु
	जोड़ kvmppc_icp_state old_state, new_state;
	bool success;

	करो अणु
		old_state = new_state = READ_ONCE(icp->state);

		*reject = 0;

		/* See अगर we can deliver */
		success = new_state.cppr > priority &&
			new_state.mfrr > priority &&
			new_state.pending_pri > priority;

		/*
		 * If we can, check क्रम a rejection and perक्रमm the
		 * delivery
		 */
		अगर (success) अणु
			*reject = new_state.xisr;
			new_state.xisr = irq;
			new_state.pending_pri = priority;
		पूर्ण अन्यथा अणु
			/*
			 * If we failed to deliver we set need_resend
			 * so a subsequent CPPR state change causes us
			 * to try a new delivery.
			 */
			new_state.need_resend = true;
		पूर्ण

	पूर्ण जबतक (!icp_rm_try_update(icp, old_state, new_state));

	वापस success;
पूर्ण

अटल व्योम icp_rm_deliver_irq(काष्ठा kvmppc_xics *xics, काष्ठा kvmppc_icp *icp,
			    u32 new_irq, bool check_resend)
अणु
	काष्ठा ics_irq_state *state;
	काष्ठा kvmppc_ics *ics;
	u32 reject;
	u16 src;

	/*
	 * This is used both क्रम initial delivery of an पूर्णांकerrupt and
	 * क्रम subsequent rejection.
	 *
	 * Rejection can be racy vs. resends. We have evaluated the
	 * rejection in an atomic ICP transaction which is now complete,
	 * so potentially the ICP can alपढ़ोy accept the पूर्णांकerrupt again.
	 *
	 * So we need to retry the delivery. Essentially the reject path
	 * boils करोwn to a failed delivery. Always.
	 *
	 * Now the पूर्णांकerrupt could also have moved to a dअगरferent target,
	 * thus we may need to re-करो the ICP lookup as well
	 */

 again:
	/* Get the ICS state and lock it */
	ics = kvmppc_xics_find_ics(xics, new_irq, &src);
	अगर (!ics) अणु
		/* Unsafe increment, but this करोes not need to be accurate */
		xics->err_noics++;
		वापस;
	पूर्ण
	state = &ics->irq_state[src];

	/* Get a lock on the ICS */
	arch_spin_lock(&ics->lock);

	/* Get our server */
	अगर (!icp || state->server != icp->server_num) अणु
		icp = kvmppc_xics_find_server(xics->kvm, state->server);
		अगर (!icp) अणु
			/* Unsafe increment again*/
			xics->err_noicp++;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (check_resend)
		अगर (!state->resend)
			जाओ out;

	/* Clear the resend bit of that पूर्णांकerrupt */
	state->resend = 0;

	/*
	 * If masked, bail out
	 *
	 * Note: PAPR करोesn't mention anything about masked pending
	 * when करोing a resend, only when करोing a delivery.
	 *
	 * However that would have the effect of losing a masked
	 * पूर्णांकerrupt that was rejected and isn't consistent with
	 * the whole masked_pending business which is about not
	 * losing पूर्णांकerrupts that occur जबतक masked.
	 *
	 * I करोn't dअगरferentiate normal deliveries and resends, this
	 * implementation will dअगरfer from PAPR and not lose such
	 * पूर्णांकerrupts.
	 */
	अगर (state->priority == MASKED) अणु
		state->masked_pending = 1;
		जाओ out;
	पूर्ण

	/*
	 * Try the delivery, this will set the need_resend flag
	 * in the ICP as part of the atomic transaction अगर the
	 * delivery is not possible.
	 *
	 * Note that अगर successful, the new delivery might have itself
	 * rejected an पूर्णांकerrupt that was "delivered" beक्रमe we took the
	 * ics spin lock.
	 *
	 * In this हाल we करो the whole sequence all over again क्रम the
	 * new guy. We cannot assume that the rejected पूर्णांकerrupt is less
	 * favored than the new one, and thus करोesn't need to be delivered,
	 * because by the समय we निकास icp_rm_try_to_deliver() the target
	 * processor may well have alपढ़ोy consumed & completed it, and thus
	 * the rejected पूर्णांकerrupt might actually be alपढ़ोy acceptable.
	 */
	अगर (icp_rm_try_to_deliver(icp, new_irq, state->priority, &reject)) अणु
		/*
		 * Delivery was successful, did we reject somebody अन्यथा ?
		 */
		अगर (reject && reject != XICS_IPI) अणु
			arch_spin_unlock(&ics->lock);
			icp->n_reject++;
			new_irq = reject;
			check_resend = 0;
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We failed to deliver the पूर्णांकerrupt we need to set the
		 * resend map bit and mark the ICS state as needing a resend
		 */
		state->resend = 1;

		/*
		 * Make sure when checking resend, we करोn't miss the resend
		 * अगर resend_map bit is seen and cleared.
		 */
		smp_wmb();
		set_bit(ics->icsid, icp->resend_map);

		/*
		 * If the need_resend flag got cleared in the ICP some समय
		 * between icp_rm_try_to_deliver() atomic update and now, then
		 * we know it might have missed the resend_map bit. So we
		 * retry
		 */
		smp_mb();
		अगर (!icp->state.need_resend) अणु
			state->resend = 0;
			arch_spin_unlock(&ics->lock);
			check_resend = 0;
			जाओ again;
		पूर्ण
	पूर्ण
 out:
	arch_spin_unlock(&ics->lock);
पूर्ण

अटल व्योम icp_rm_करोwn_cppr(काष्ठा kvmppc_xics *xics, काष्ठा kvmppc_icp *icp,
			     u8 new_cppr)
अणु
	जोड़ kvmppc_icp_state old_state, new_state;
	bool resend;

	/*
	 * This handles several related states in one operation:
	 *
	 * ICP State: Down_CPPR
	 *
	 * Load CPPR with new value and अगर the XISR is 0
	 * then check क्रम resends:
	 *
	 * ICP State: Resend
	 *
	 * If MFRR is more favored than CPPR, check क्रम IPIs
	 * and notअगरy ICS of a potential resend. This is करोne
	 * asynchronously (when used in real mode, we will have
	 * to निकास here).
	 *
	 * We करो not handle the complete Check_IPI as करोcumented
	 * here. In the PAPR, this state will be used क्रम both
	 * Set_MFRR and Down_CPPR. However, we know that we aren't
	 * changing the MFRR state here so we करोn't need to handle
	 * the हाल of an MFRR causing a reject of a pending irq,
	 * this will have been handled when the MFRR was set in the
	 * first place.
	 *
	 * Thus we करोn't have to handle rejects, only resends.
	 *
	 * When implementing real mode क्रम HV KVM, resend will lead to
	 * a H_TOO_HARD वापस and the whole transaction will be handled
	 * in भव mode.
	 */
	करो अणु
		old_state = new_state = READ_ONCE(icp->state);

		/* Down_CPPR */
		new_state.cppr = new_cppr;

		/*
		 * Cut करोwn Resend / Check_IPI / IPI
		 *
		 * The logic is that we cannot have a pending पूर्णांकerrupt
		 * trumped by an IPI at this poपूर्णांक (see above), so we
		 * know that either the pending पूर्णांकerrupt is alपढ़ोy an
		 * IPI (in which हाल we करोn't care to override it) or
		 * it's either more favored than us or non existent
		 */
		अगर (new_state.mfrr < new_cppr &&
		    new_state.mfrr <= new_state.pending_pri) अणु
			new_state.pending_pri = new_state.mfrr;
			new_state.xisr = XICS_IPI;
		पूर्ण

		/* Latch/clear resend bit */
		resend = new_state.need_resend;
		new_state.need_resend = 0;

	पूर्ण जबतक (!icp_rm_try_update(icp, old_state, new_state));

	/*
	 * Now handle resend checks. Those are asynchronous to the ICP
	 * state update in HW (ie bus transactions) so we can handle them
	 * separately here as well.
	 */
	अगर (resend) अणु
		icp->n_check_resend++;
		icp_rm_check_resend(xics, icp);
	पूर्ण
पूर्ण


अचिन्हित दीर्घ xics_rm_h_xirr(काष्ठा kvm_vcpu *vcpu)
अणु
	जोड़ kvmppc_icp_state old_state, new_state;
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
	u32 xirr;

	अगर (!xics || !xics->real_mode)
		वापस H_TOO_HARD;

	/* First clear the पूर्णांकerrupt */
	icp_rm_clr_vcpu_irq(icp->vcpu);

	/*
	 * ICP State: Accept_Interrupt
	 *
	 * Return the pending पूर्णांकerrupt (अगर any) aदीर्घ with the
	 * current CPPR, then clear the XISR & set CPPR to the
	 * pending priority
	 */
	करो अणु
		old_state = new_state = READ_ONCE(icp->state);

		xirr = old_state.xisr | (((u32)old_state.cppr) << 24);
		अगर (!old_state.xisr)
			अवरोध;
		new_state.cppr = new_state.pending_pri;
		new_state.pending_pri = 0xff;
		new_state.xisr = 0;

	पूर्ण जबतक (!icp_rm_try_update(icp, old_state, new_state));

	/* Return the result in GPR4 */
	vcpu->arch.regs.gpr[4] = xirr;

	वापस check_too_hard(xics, icp);
पूर्ण

पूर्णांक xics_rm_h_ipi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server,
		  अचिन्हित दीर्घ mfrr)
अणु
	जोड़ kvmppc_icp_state old_state, new_state;
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	काष्ठा kvmppc_icp *icp, *this_icp = vcpu->arch.icp;
	u32 reject;
	bool resend;
	bool local;

	अगर (!xics || !xics->real_mode)
		वापस H_TOO_HARD;

	local = this_icp->server_num == server;
	अगर (local)
		icp = this_icp;
	अन्यथा
		icp = kvmppc_xics_find_server(vcpu->kvm, server);
	अगर (!icp)
		वापस H_PARAMETER;

	/*
	 * ICP state: Set_MFRR
	 *
	 * If the CPPR is more favored than the new MFRR, then
	 * nothing needs to be करोne as there can be no XISR to
	 * reject.
	 *
	 * ICP state: Check_IPI
	 *
	 * If the CPPR is less favored, then we might be replacing
	 * an पूर्णांकerrupt, and thus need to possibly reject it.
	 *
	 * ICP State: IPI
	 *
	 * Besides rejecting any pending पूर्णांकerrupts, we also
	 * update XISR and pending_pri to mark IPI as pending.
	 *
	 * PAPR करोes not describe this state, but अगर the MFRR is being
	 * made less favored than its earlier value, there might be
	 * a previously-rejected पूर्णांकerrupt needing to be resent.
	 * Ideally, we would want to resend only अगर
	 *	prio(pending_पूर्णांकerrupt) < mfrr &&
	 *	prio(pending_पूर्णांकerrupt) < cppr
	 * where pending पूर्णांकerrupt is the one that was rejected. But
	 * we करोn't have that state, so we simply trigger a resend
	 * whenever the MFRR is made less favored.
	 */
	करो अणु
		old_state = new_state = READ_ONCE(icp->state);

		/* Set_MFRR */
		new_state.mfrr = mfrr;

		/* Check_IPI */
		reject = 0;
		resend = false;
		अगर (mfrr < new_state.cppr) अणु
			/* Reject a pending पूर्णांकerrupt अगर not an IPI */
			अगर (mfrr <= new_state.pending_pri) अणु
				reject = new_state.xisr;
				new_state.pending_pri = mfrr;
				new_state.xisr = XICS_IPI;
			पूर्ण
		पूर्ण

		अगर (mfrr > old_state.mfrr) अणु
			resend = new_state.need_resend;
			new_state.need_resend = 0;
		पूर्ण
	पूर्ण जबतक (!icp_rm_try_update(icp, old_state, new_state));

	/* Handle reject in real mode */
	अगर (reject && reject != XICS_IPI) अणु
		this_icp->n_reject++;
		icp_rm_deliver_irq(xics, icp, reject, false);
	पूर्ण

	/* Handle resends in real mode */
	अगर (resend) अणु
		this_icp->n_check_resend++;
		icp_rm_check_resend(xics, icp);
	पूर्ण

	वापस check_too_hard(xics, this_icp);
पूर्ण

पूर्णांक xics_rm_h_cppr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cppr)
अणु
	जोड़ kvmppc_icp_state old_state, new_state;
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
	u32 reject;

	अगर (!xics || !xics->real_mode)
		वापस H_TOO_HARD;

	/*
	 * ICP State: Set_CPPR
	 *
	 * We can safely compare the new value with the current
	 * value outside of the transaction as the CPPR is only
	 * ever changed by the processor on itself
	 */
	अगर (cppr > icp->state.cppr) अणु
		icp_rm_करोwn_cppr(xics, icp, cppr);
		जाओ bail;
	पूर्ण अन्यथा अगर (cppr == icp->state.cppr)
		वापस H_SUCCESS;

	/*
	 * ICP State: Up_CPPR
	 *
	 * The processor is raising its priority, this can result
	 * in a rejection of a pending पूर्णांकerrupt:
	 *
	 * ICP State: Reject_Current
	 *
	 * We can हटाओ EE from the current processor, the update
	 * transaction will set it again अगर needed
	 */
	icp_rm_clr_vcpu_irq(icp->vcpu);

	करो अणु
		old_state = new_state = READ_ONCE(icp->state);

		reject = 0;
		new_state.cppr = cppr;

		अगर (cppr <= new_state.pending_pri) अणु
			reject = new_state.xisr;
			new_state.xisr = 0;
			new_state.pending_pri = 0xff;
		पूर्ण

	पूर्ण जबतक (!icp_rm_try_update(icp, old_state, new_state));

	/*
	 * Check क्रम rejects. They are handled by करोing a new delivery
	 * attempt (see comments in icp_rm_deliver_irq).
	 */
	अगर (reject && reject != XICS_IPI) अणु
		icp->n_reject++;
		icp_rm_deliver_irq(xics, icp, reject, false);
	पूर्ण
 bail:
	वापस check_too_hard(xics, icp);
पूर्ण

अटल पूर्णांक ics_rm_eoi(काष्ठा kvm_vcpu *vcpu, u32 irq)
अणु
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
	काष्ठा kvmppc_ics *ics;
	काष्ठा ics_irq_state *state;
	u16 src;
	u32 pq_old, pq_new;

	/*
	 * ICS EOI handling: For LSI, अगर P bit is still set, we need to
	 * resend it.
	 *
	 * For MSI, we move Q bit पूर्णांकo P (and clear Q). If it is set,
	 * resend it.
	 */

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	अगर (!ics)
		जाओ bail;

	state = &ics->irq_state[src];

	अगर (state->lsi)
		pq_new = state->pq_state;
	अन्यथा
		करो अणु
			pq_old = state->pq_state;
			pq_new = pq_old >> 1;
		पूर्ण जबतक (cmpxchg(&state->pq_state, pq_old, pq_new) != pq_old);

	अगर (pq_new & PQ_PRESENTED)
		icp_rm_deliver_irq(xics, शून्य, irq, false);

	अगर (!hlist_empty(&vcpu->kvm->irq_ack_notअगरier_list)) अणु
		icp->rm_action |= XICS_RM_NOTIFY_EOI;
		icp->rm_eoied_irq = irq;
	पूर्ण

	अगर (state->host_irq) अणु
		++vcpu->stat.pthru_all;
		अगर (state->पूर्णांकr_cpu != -1) अणु
			पूर्णांक pcpu = raw_smp_processor_id();

			pcpu = cpu_first_thपढ़ो_sibling(pcpu);
			++vcpu->stat.pthru_host;
			अगर (state->पूर्णांकr_cpu != pcpu) अणु
				++vcpu->stat.pthru_bad_aff;
				xics_opal_set_server(state->host_irq, pcpu);
			पूर्ण
			state->पूर्णांकr_cpu = -1;
		पूर्ण
	पूर्ण

 bail:
	वापस check_too_hard(xics, icp);
पूर्ण

पूर्णांक xics_rm_h_eoi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ xirr)
अणु
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
	u32 irq = xirr & 0x00ffffff;

	अगर (!xics || !xics->real_mode)
		वापस H_TOO_HARD;

	/*
	 * ICP State: EOI
	 *
	 * Note: If EOI is incorrectly used by SW to lower the CPPR
	 * value (ie more favored), we करो not check क्रम rejection of
	 * a pending पूर्णांकerrupt, this is a SW error and PAPR specअगरies
	 * that we करोn't have to deal with it.
	 *
	 * The sending of an EOI to the ICS is handled after the
	 * CPPR update
	 *
	 * ICP State: Down_CPPR which we handle
	 * in a separate function as it's shared with H_CPPR.
	 */
	icp_rm_करोwn_cppr(xics, icp, xirr >> 24);

	/* IPIs have no EOI */
	अगर (irq == XICS_IPI)
		वापस check_too_hard(xics, icp);

	वापस ics_rm_eoi(vcpu, irq);
पूर्ण

अटल अचिन्हित दीर्घ eoi_rc;

अटल व्योम icp_eoi(काष्ठा irq_chip *c, u32 hwirq, __be32 xirr, bool *again)
अणु
	व्योम __iomem *xics_phys;
	पूर्णांक64_t rc;

	अगर (kvmhv_on_pseries()) अणु
		अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

		iosync();
		plpar_hcall_raw(H_EOI, retbuf, hwirq);
		वापस;
	पूर्ण

	rc = pnv_opal_pci_msi_eoi(c, hwirq);

	अगर (rc)
		eoi_rc = rc;

	iosync();

	/* EOI it */
	xics_phys = local_paca->kvm_hstate.xics_phys;
	अगर (xics_phys) अणु
		__raw_rm_ग_लिखोl(xirr, xics_phys + XICS_XIRR);
	पूर्ण अन्यथा अणु
		rc = opal_पूर्णांक_eoi(be32_to_cpu(xirr));
		*again = rc > 0;
	पूर्ण
पूर्ण

अटल पूर्णांक xics_opal_set_server(अचिन्हित पूर्णांक hw_irq, पूर्णांक server_cpu)
अणु
	अचिन्हित पूर्णांक mangle_cpu = get_hard_smp_processor_id(server_cpu) << 2;

	वापस opal_set_xive(hw_irq, mangle_cpu, DEFAULT_PRIORITY);
पूर्ण

/*
 * Increment a per-CPU 32-bit अचिन्हित पूर्णांकeger variable.
 * Safe to call in real-mode. Handles vदो_स्मृति'ed addresses
 *
 * ToDo: Make this work क्रम any पूर्णांकegral type
 */

अटल अंतरभूत व्योम this_cpu_inc_rm(अचिन्हित पूर्णांक __percpu *addr)
अणु
	अचिन्हित दीर्घ l;
	अचिन्हित पूर्णांक *raddr;
	पूर्णांक cpu = smp_processor_id();

	raddr = per_cpu_ptr(addr, cpu);
	l = (अचिन्हित दीर्घ)raddr;

	अगर (get_region_id(l) == VMALLOC_REGION_ID) अणु
		l = vदो_स्मृति_to_phys(raddr);
		raddr = (अचिन्हित पूर्णांक *)l;
	पूर्ण
	++*raddr;
पूर्ण

/*
 * We करोn't try to update the flags in the irq_desc 'istate' field in
 * here as would happen in the normal IRQ handling path क्रम several reasons:
 *  - state flags represent पूर्णांकernal IRQ state and are not expected to be
 *    updated outside the IRQ subप्रणाली
 *  - more importantly, these are useful क्रम edge triggered पूर्णांकerrupts,
 *    IRQ probing, etc., but we are only handling MSI/MSIx पूर्णांकerrupts here
 *    and these states shouldn't apply to us.
 *
 * However, we करो update irq_stats - we somewhat duplicate the code in
 * kstat_incr_irqs_this_cpu() क्रम this since this function is defined
 * in irq/पूर्णांकernal.h which we करोn't want to include here.
 * The only dअगरference is that desc->kstat_irqs is an allocated per CPU
 * variable and could have been vदो_स्मृति'ed, so we can't directly
 * call __this_cpu_inc() on it. The kstat काष्ठाure is a अटल
 * per CPU variable and it should be accessible by real-mode KVM.
 *
 */
अटल व्योम kvmppc_rm_handle_irq_desc(काष्ठा irq_desc *desc)
अणु
	this_cpu_inc_rm(desc->kstat_irqs);
	__this_cpu_inc(kstat.irqs_sum);
पूर्ण

दीर्घ kvmppc_deliver_irq_passthru(काष्ठा kvm_vcpu *vcpu,
				 __be32 xirr,
				 काष्ठा kvmppc_irq_map *irq_map,
				 काष्ठा kvmppc_passthru_irqmap *pimap,
				 bool *again)
अणु
	काष्ठा kvmppc_xics *xics;
	काष्ठा kvmppc_icp *icp;
	काष्ठा kvmppc_ics *ics;
	काष्ठा ics_irq_state *state;
	u32 irq;
	u16 src;
	u32 pq_old, pq_new;

	irq = irq_map->v_hwirq;
	xics = vcpu->kvm->arch.xics;
	icp = vcpu->arch.icp;

	kvmppc_rm_handle_irq_desc(irq_map->desc);

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	अगर (!ics)
		वापस 2;

	state = &ics->irq_state[src];

	/* only MSIs रेजिस्टर bypass producers, so it must be MSI here */
	करो अणु
		pq_old = state->pq_state;
		pq_new = ((pq_old << 1) & 3) | PQ_PRESENTED;
	पूर्ण जबतक (cmpxchg(&state->pq_state, pq_old, pq_new) != pq_old);

	/* Test P=1, Q=0, this is the only हाल where we present */
	अगर (pq_new == PQ_PRESENTED)
		icp_rm_deliver_irq(xics, icp, irq, false);

	/* EOI the पूर्णांकerrupt */
	icp_eoi(irq_desc_get_chip(irq_map->desc), irq_map->r_hwirq, xirr,
		again);

	अगर (check_too_hard(xics, icp) == H_TOO_HARD)
		वापस 2;
	अन्यथा
		वापस -2;
पूर्ण

/*  --- Non-real mode XICS-related built-in routines ---  */

/**
 * Host Operations poked by RM KVM
 */
अटल व्योम rm_host_ipi_action(पूर्णांक action, व्योम *data)
अणु
	चयन (action) अणु
	हाल XICS_RM_KICK_VCPU:
		kvmppc_host_rm_ops_hv->vcpu_kick(data);
		अवरोध;
	शेष:
		WARN(1, "Unexpected rm_action=%d data=%p\n", action, data);
		अवरोध;
	पूर्ण

पूर्ण

व्योम kvmppc_xics_ipi_action(व्योम)
अणु
	पूर्णांक core;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा kvmppc_host_rm_core *rm_corep;

	core = cpu >> thपढ़ोs_shअगरt;
	rm_corep = &kvmppc_host_rm_ops_hv->rm_core[core];

	अगर (rm_corep->rm_data) अणु
		rm_host_ipi_action(rm_corep->rm_state.rm_action,
							rm_corep->rm_data);
		/* Order these stores against the real mode KVM */
		rm_corep->rm_data = शून्य;
		smp_wmb();
		rm_corep->rm_state.rm_action = 0;
	पूर्ण
पूर्ण
