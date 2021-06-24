<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Michael Ellerman, IBM Corporation.
 * Copyright 2012 Benjamin Herrenschmidt, IBM Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/समय.स>

#समावेश <linux/seq_file.h>

#समावेश "book3s_xics.h"

#अगर 1
#घोषणा XICS_DBG(fmt...) करो अणु पूर्ण जबतक (0)
#अन्यथा
#घोषणा XICS_DBG(fmt...) trace_prपूर्णांकk(fmt)
#पूर्ण_अगर

#घोषणा ENABLE_REALMODE	true
#घोषणा DEBUG_REALMODE	false

/*
 * LOCKING
 * =======
 *
 * Each ICS has a spin lock protecting the inक्रमmation about the IRQ
 * sources and aव्योमing simultaneous deliveries of the same पूर्णांकerrupt.
 *
 * ICP operations are करोne via a single compare & swap transaction
 * (most ICP state fits in the जोड़ kvmppc_icp_state)
 */

/*
 * TODO
 * ====
 *
 * - To speed up resends, keep a biपंचांगap of "resend" set bits in the
 *   ICS
 *
 * - Speed up server# -> ICP lookup (array ? hash table ?)
 *
 * - Make ICS lockless as well, or at least a per-पूर्णांकerrupt lock or hashed
 *   locks array to improve scalability
 */

/* -- ICS routines -- */

अटल व्योम icp_deliver_irq(काष्ठा kvmppc_xics *xics, काष्ठा kvmppc_icp *icp,
			    u32 new_irq, bool check_resend);

/*
 * Return value ideally indicates how the पूर्णांकerrupt was handled, but no
 * callers look at it (given that we करोn't implement KVM_IRQ_LINE_STATUS),
 * so just वापस 0.
 */
अटल पूर्णांक ics_deliver_irq(काष्ठा kvmppc_xics *xics, u32 irq, u32 level)
अणु
	काष्ठा ics_irq_state *state;
	काष्ठा kvmppc_ics *ics;
	u16 src;
	u32 pq_old, pq_new;

	XICS_DBG("ics deliver %#x (level: %d)\n", irq, level);

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	अगर (!ics) अणु
		XICS_DBG("ics_deliver_irq: IRQ 0x%06x not found !\n", irq);
		वापस -EINVAL;
	पूर्ण
	state = &ics->irq_state[src];
	अगर (!state->exists)
		वापस -EINVAL;

	अगर (level == KVM_INTERRUPT_SET_LEVEL || level == KVM_INTERRUPT_SET)
		level = 1;
	अन्यथा अगर (level == KVM_INTERRUPT_UNSET)
		level = 0;
	/*
	 * Take other values the same as 1, consistent with original code.
	 * maybe WARN here?
	 */

	अगर (!state->lsi && level == 0) /* noop क्रम MSI */
		वापस 0;

	करो अणु
		pq_old = state->pq_state;
		अगर (state->lsi) अणु
			अगर (level) अणु
				अगर (pq_old & PQ_PRESENTED)
					/* Setting alपढ़ोy set LSI ... */
					वापस 0;

				pq_new = PQ_PRESENTED;
			पूर्ण अन्यथा
				pq_new = 0;
		पूर्ण अन्यथा
			pq_new = ((pq_old << 1) & 3) | PQ_PRESENTED;
	पूर्ण जबतक (cmpxchg(&state->pq_state, pq_old, pq_new) != pq_old);

	/* Test P=1, Q=0, this is the only हाल where we present */
	अगर (pq_new == PQ_PRESENTED)
		icp_deliver_irq(xics, शून्य, irq, false);

	/* Record which CPU this arrived on क्रम passed-through पूर्णांकerrupts */
	अगर (state->host_irq)
		state->पूर्णांकr_cpu = raw_smp_processor_id();

	वापस 0;
पूर्ण

अटल व्योम ics_check_resend(काष्ठा kvmppc_xics *xics, काष्ठा kvmppc_ics *ics,
			     काष्ठा kvmppc_icp *icp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) अणु
		काष्ठा ics_irq_state *state = &ics->irq_state[i];
		अगर (state->resend) अणु
			XICS_DBG("resend %#x prio %#x\n", state->number,
				      state->priority);
			icp_deliver_irq(xics, icp, state->number, true);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool ग_लिखो_xive(काष्ठा kvmppc_xics *xics, काष्ठा kvmppc_ics *ics,
		       काष्ठा ics_irq_state *state,
		       u32 server, u32 priority, u32 saved_priority)
अणु
	bool deliver;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arch_spin_lock(&ics->lock);

	state->server = server;
	state->priority = priority;
	state->saved_priority = saved_priority;
	deliver = false;
	अगर ((state->masked_pending || state->resend) && priority != MASKED) अणु
		state->masked_pending = 0;
		state->resend = 0;
		deliver = true;
	पूर्ण

	arch_spin_unlock(&ics->lock);
	local_irq_restore(flags);

	वापस deliver;
पूर्ण

पूर्णांक kvmppc_xics_set_xive(काष्ठा kvm *kvm, u32 irq, u32 server, u32 priority)
अणु
	काष्ठा kvmppc_xics *xics = kvm->arch.xics;
	काष्ठा kvmppc_icp *icp;
	काष्ठा kvmppc_ics *ics;
	काष्ठा ics_irq_state *state;
	u16 src;

	अगर (!xics)
		वापस -ENODEV;

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	अगर (!ics)
		वापस -EINVAL;
	state = &ics->irq_state[src];

	icp = kvmppc_xics_find_server(kvm, server);
	अगर (!icp)
		वापस -EINVAL;

	XICS_DBG("set_xive %#x server %#x prio %#x MP:%d RS:%d\n",
		 irq, server, priority,
		 state->masked_pending, state->resend);

	अगर (ग_लिखो_xive(xics, ics, state, server, priority, priority))
		icp_deliver_irq(xics, icp, irq, false);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xics_get_xive(काष्ठा kvm *kvm, u32 irq, u32 *server, u32 *priority)
अणु
	काष्ठा kvmppc_xics *xics = kvm->arch.xics;
	काष्ठा kvmppc_ics *ics;
	काष्ठा ics_irq_state *state;
	u16 src;
	अचिन्हित दीर्घ flags;

	अगर (!xics)
		वापस -ENODEV;

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	अगर (!ics)
		वापस -EINVAL;
	state = &ics->irq_state[src];

	local_irq_save(flags);
	arch_spin_lock(&ics->lock);
	*server = state->server;
	*priority = state->priority;
	arch_spin_unlock(&ics->lock);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xics_पूर्णांक_on(काष्ठा kvm *kvm, u32 irq)
अणु
	काष्ठा kvmppc_xics *xics = kvm->arch.xics;
	काष्ठा kvmppc_icp *icp;
	काष्ठा kvmppc_ics *ics;
	काष्ठा ics_irq_state *state;
	u16 src;

	अगर (!xics)
		वापस -ENODEV;

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	अगर (!ics)
		वापस -EINVAL;
	state = &ics->irq_state[src];

	icp = kvmppc_xics_find_server(kvm, state->server);
	अगर (!icp)
		वापस -EINVAL;

	अगर (ग_लिखो_xive(xics, ics, state, state->server, state->saved_priority,
		       state->saved_priority))
		icp_deliver_irq(xics, icp, irq, false);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xics_पूर्णांक_off(काष्ठा kvm *kvm, u32 irq)
अणु
	काष्ठा kvmppc_xics *xics = kvm->arch.xics;
	काष्ठा kvmppc_ics *ics;
	काष्ठा ics_irq_state *state;
	u16 src;

	अगर (!xics)
		वापस -ENODEV;

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	अगर (!ics)
		वापस -EINVAL;
	state = &ics->irq_state[src];

	ग_लिखो_xive(xics, ics, state, state->server, MASKED, state->priority);

	वापस 0;
पूर्ण

/* -- ICP routines, including hcalls -- */

अटल अंतरभूत bool icp_try_update(काष्ठा kvmppc_icp *icp,
				  जोड़ kvmppc_icp_state old,
				  जोड़ kvmppc_icp_state new,
				  bool change_self)
अणु
	bool success;

	/* Calculate new output value */
	new.out_ee = (new.xisr && (new.pending_pri < new.cppr));

	/* Attempt atomic update */
	success = cmpxchg64(&icp->state.raw, old.raw, new.raw) == old.raw;
	अगर (!success)
		जाओ bail;

	XICS_DBG("UPD [%04lx] - C:%02x M:%02x PP: %02x PI:%06x R:%d O:%d\n",
		 icp->server_num,
		 old.cppr, old.mfrr, old.pending_pri, old.xisr,
		 old.need_resend, old.out_ee);
	XICS_DBG("UPD        - C:%02x M:%02x PP: %02x PI:%06x R:%d O:%d\n",
		 new.cppr, new.mfrr, new.pending_pri, new.xisr,
		 new.need_resend, new.out_ee);
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
	अगर (new.out_ee) अणु
		kvmppc_book3s_queue_irqprio(icp->vcpu,
					    BOOK3S_INTERRUPT_EXTERNAL);
		अगर (!change_self)
			kvmppc_fast_vcpu_kick(icp->vcpu);
	पूर्ण
 bail:
	वापस success;
पूर्ण

अटल व्योम icp_check_resend(काष्ठा kvmppc_xics *xics,
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
		ics_check_resend(xics, ics, icp);
	पूर्ण
पूर्ण

अटल bool icp_try_to_deliver(काष्ठा kvmppc_icp *icp, u32 irq, u8 priority,
			       u32 *reject)
अणु
	जोड़ kvmppc_icp_state old_state, new_state;
	bool success;

	XICS_DBG("try deliver %#x(P:%#x) to server %#lx\n", irq, priority,
		 icp->server_num);

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

	पूर्ण जबतक (!icp_try_update(icp, old_state, new_state, false));

	वापस success;
पूर्ण

अटल व्योम icp_deliver_irq(काष्ठा kvmppc_xics *xics, काष्ठा kvmppc_icp *icp,
			    u32 new_irq, bool check_resend)
अणु
	काष्ठा ics_irq_state *state;
	काष्ठा kvmppc_ics *ics;
	u32 reject;
	u16 src;
	अचिन्हित दीर्घ flags;

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
		XICS_DBG("icp_deliver_irq: IRQ 0x%06x not found !\n", new_irq);
		वापस;
	पूर्ण
	state = &ics->irq_state[src];

	/* Get a lock on the ICS */
	local_irq_save(flags);
	arch_spin_lock(&ics->lock);

	/* Get our server */
	अगर (!icp || state->server != icp->server_num) अणु
		icp = kvmppc_xics_find_server(xics->kvm, state->server);
		अगर (!icp) अणु
			pr_warn("icp_deliver_irq: IRQ 0x%06x server 0x%x not found !\n",
				new_irq, state->server);
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
		XICS_DBG("irq %#x masked pending\n", new_irq);
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
	 * because by the समय we निकास icp_try_to_deliver() the target
	 * processor may well have alrady consumed & completed it, and thus
	 * the rejected पूर्णांकerrupt might actually be alपढ़ोy acceptable.
	 */
	अगर (icp_try_to_deliver(icp, new_irq, state->priority, &reject)) अणु
		/*
		 * Delivery was successful, did we reject somebody अन्यथा ?
		 */
		अगर (reject && reject != XICS_IPI) अणु
			arch_spin_unlock(&ics->lock);
			local_irq_restore(flags);
			new_irq = reject;
			check_resend = false;
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
		 * between icp_try_to_deliver() atomic update and now, then
		 * we know it might have missed the resend_map bit. So we
		 * retry
		 */
		smp_mb();
		अगर (!icp->state.need_resend) अणु
			state->resend = 0;
			arch_spin_unlock(&ics->lock);
			local_irq_restore(flags);
			check_resend = false;
			जाओ again;
		पूर्ण
	पूर्ण
 out:
	arch_spin_unlock(&ics->lock);
	local_irq_restore(flags);
पूर्ण

अटल व्योम icp_करोwn_cppr(काष्ठा kvmppc_xics *xics, काष्ठा kvmppc_icp *icp,
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
			WARN_ON(new_state.xisr != XICS_IPI &&
				new_state.xisr != 0);
			new_state.pending_pri = new_state.mfrr;
			new_state.xisr = XICS_IPI;
		पूर्ण

		/* Latch/clear resend bit */
		resend = new_state.need_resend;
		new_state.need_resend = 0;

	पूर्ण जबतक (!icp_try_update(icp, old_state, new_state, true));

	/*
	 * Now handle resend checks. Those are asynchronous to the ICP
	 * state update in HW (ie bus transactions) so we can handle them
	 * separately here too
	 */
	अगर (resend)
		icp_check_resend(xics, icp);
पूर्ण

अटल noअंतरभूत अचिन्हित दीर्घ kvmppc_h_xirr(काष्ठा kvm_vcpu *vcpu)
अणु
	जोड़ kvmppc_icp_state old_state, new_state;
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
	u32 xirr;

	/* First, हटाओ EE from the processor */
	kvmppc_book3s_dequeue_irqprio(icp->vcpu, BOOK3S_INTERRUPT_EXTERNAL);

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

	पूर्ण जबतक (!icp_try_update(icp, old_state, new_state, true));

	XICS_DBG("h_xirr vcpu %d xirr %#x\n", vcpu->vcpu_id, xirr);

	वापस xirr;
पूर्ण

अटल noअंतरभूत पूर्णांक kvmppc_h_ipi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server,
				 अचिन्हित दीर्घ mfrr)
अणु
	जोड़ kvmppc_icp_state old_state, new_state;
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	काष्ठा kvmppc_icp *icp;
	u32 reject;
	bool resend;
	bool local;

	XICS_DBG("h_ipi vcpu %d to server %lu mfrr %#lx\n",
		 vcpu->vcpu_id, server, mfrr);

	icp = vcpu->arch.icp;
	local = icp->server_num == server;
	अगर (!local) अणु
		icp = kvmppc_xics_find_server(vcpu->kvm, server);
		अगर (!icp)
			वापस H_PARAMETER;
	पूर्ण

	/*
	 * ICP state: Set_MFRR
	 *
	 * If the CPPR is more favored than the new MFRR, then
	 * nothing needs to be rejected as there can be no XISR to
	 * reject.  If the MFRR is being made less favored then
	 * there might be a previously-rejected पूर्णांकerrupt needing
	 * to be resent.
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
	पूर्ण जबतक (!icp_try_update(icp, old_state, new_state, local));

	/* Handle reject */
	अगर (reject && reject != XICS_IPI)
		icp_deliver_irq(xics, icp, reject, false);

	/* Handle resend */
	अगर (resend)
		icp_check_resend(xics, icp);

	वापस H_SUCCESS;
पूर्ण

अटल पूर्णांक kvmppc_h_ipoll(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server)
अणु
	जोड़ kvmppc_icp_state state;
	काष्ठा kvmppc_icp *icp;

	icp = vcpu->arch.icp;
	अगर (icp->server_num != server) अणु
		icp = kvmppc_xics_find_server(vcpu->kvm, server);
		अगर (!icp)
			वापस H_PARAMETER;
	पूर्ण
	state = READ_ONCE(icp->state);
	kvmppc_set_gpr(vcpu, 4, ((u32)state.cppr << 24) | state.xisr);
	kvmppc_set_gpr(vcpu, 5, state.mfrr);
	वापस H_SUCCESS;
पूर्ण

अटल noअंतरभूत व्योम kvmppc_h_cppr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cppr)
अणु
	जोड़ kvmppc_icp_state old_state, new_state;
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
	u32 reject;

	XICS_DBG("h_cppr vcpu %d cppr %#lx\n", vcpu->vcpu_id, cppr);

	/*
	 * ICP State: Set_CPPR
	 *
	 * We can safely compare the new value with the current
	 * value outside of the transaction as the CPPR is only
	 * ever changed by the processor on itself
	 */
	अगर (cppr > icp->state.cppr)
		icp_करोwn_cppr(xics, icp, cppr);
	अन्यथा अगर (cppr == icp->state.cppr)
		वापस;

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
	kvmppc_book3s_dequeue_irqprio(icp->vcpu, BOOK3S_INTERRUPT_EXTERNAL);

	करो अणु
		old_state = new_state = READ_ONCE(icp->state);

		reject = 0;
		new_state.cppr = cppr;

		अगर (cppr <= new_state.pending_pri) अणु
			reject = new_state.xisr;
			new_state.xisr = 0;
			new_state.pending_pri = 0xff;
		पूर्ण

	पूर्ण जबतक (!icp_try_update(icp, old_state, new_state, true));

	/*
	 * Check क्रम rejects. They are handled by करोing a new delivery
	 * attempt (see comments in icp_deliver_irq).
	 */
	अगर (reject && reject != XICS_IPI)
		icp_deliver_irq(xics, icp, reject, false);
पूर्ण

अटल पूर्णांक ics_eoi(काष्ठा kvm_vcpu *vcpu, u32 irq)
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
	अगर (!ics) अणु
		XICS_DBG("ios_eoi: IRQ 0x%06x not found !\n", irq);
		वापस H_PARAMETER;
	पूर्ण
	state = &ics->irq_state[src];

	अगर (state->lsi)
		pq_new = state->pq_state;
	अन्यथा
		करो अणु
			pq_old = state->pq_state;
			pq_new = pq_old >> 1;
		पूर्ण जबतक (cmpxchg(&state->pq_state, pq_old, pq_new) != pq_old);

	अगर (pq_new & PQ_PRESENTED)
		icp_deliver_irq(xics, icp, irq, false);

	kvm_notअगरy_acked_irq(vcpu->kvm, 0, irq);

	वापस H_SUCCESS;
पूर्ण

अटल noअंतरभूत पूर्णांक kvmppc_h_eoi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ xirr)
अणु
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
	u32 irq = xirr & 0x00ffffff;

	XICS_DBG("h_eoi vcpu %d eoi %#lx\n", vcpu->vcpu_id, xirr);

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
	icp_करोwn_cppr(xics, icp, xirr >> 24);

	/* IPIs have no EOI */
	अगर (irq == XICS_IPI)
		वापस H_SUCCESS;

	वापस ics_eoi(vcpu, irq);
पूर्ण

पूर्णांक kvmppc_xics_rm_complete(काष्ठा kvm_vcpu *vcpu, u32 hcall)
अणु
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;

	XICS_DBG("XICS_RM: H_%x completing, act: %x state: %lx tgt: %p\n",
		 hcall, icp->rm_action, icp->rm_dbgstate.raw, icp->rm_dbgtgt);

	अगर (icp->rm_action & XICS_RM_KICK_VCPU) अणु
		icp->n_rm_kick_vcpu++;
		kvmppc_fast_vcpu_kick(icp->rm_kick_target);
	पूर्ण
	अगर (icp->rm_action & XICS_RM_CHECK_RESEND) अणु
		icp->n_rm_check_resend++;
		icp_check_resend(xics, icp->rm_resend_icp);
	पूर्ण
	अगर (icp->rm_action & XICS_RM_NOTIFY_EOI) अणु
		icp->n_rm_notअगरy_eoi++;
		kvm_notअगरy_acked_irq(vcpu->kvm, 0, icp->rm_eoied_irq);
	पूर्ण

	icp->rm_action = 0;

	वापस H_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_xics_rm_complete);

पूर्णांक kvmppc_xics_hcall(काष्ठा kvm_vcpu *vcpu, u32 req)
अणु
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	अचिन्हित दीर्घ res;
	पूर्णांक rc = H_SUCCESS;

	/* Check अगर we have an ICP */
	अगर (!xics || !vcpu->arch.icp)
		वापस H_HARDWARE;

	/* These requests करोn't have real-mode implementations at present */
	चयन (req) अणु
	हाल H_XIRR_X:
		res = kvmppc_h_xirr(vcpu);
		kvmppc_set_gpr(vcpu, 4, res);
		kvmppc_set_gpr(vcpu, 5, get_tb());
		वापस rc;
	हाल H_IPOLL:
		rc = kvmppc_h_ipoll(vcpu, kvmppc_get_gpr(vcpu, 4));
		वापस rc;
	पूर्ण

	/* Check क्रम real mode वापसing too hard */
	अगर (xics->real_mode && is_kvmppc_hv_enabled(vcpu->kvm))
		वापस kvmppc_xics_rm_complete(vcpu, req);

	चयन (req) अणु
	हाल H_XIRR:
		res = kvmppc_h_xirr(vcpu);
		kvmppc_set_gpr(vcpu, 4, res);
		अवरोध;
	हाल H_CPPR:
		kvmppc_h_cppr(vcpu, kvmppc_get_gpr(vcpu, 4));
		अवरोध;
	हाल H_EOI:
		rc = kvmppc_h_eoi(vcpu, kvmppc_get_gpr(vcpu, 4));
		अवरोध;
	हाल H_IPI:
		rc = kvmppc_h_ipi(vcpu, kvmppc_get_gpr(vcpu, 4),
				  kvmppc_get_gpr(vcpu, 5));
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_xics_hcall);


/* -- Initialisation code etc. -- */

अटल व्योम xics_debugfs_irqmap(काष्ठा seq_file *m,
				काष्ठा kvmppc_passthru_irqmap *pimap)
अणु
	पूर्णांक i;

	अगर (!pimap)
		वापस;
	seq_म_लिखो(m, "========\nPIRQ mappings: %d maps\n===========\n",
				pimap->n_mapped);
	क्रम (i = 0; i < pimap->n_mapped; i++)  अणु
		seq_म_लिखो(m, "r_hwirq=%x, v_hwirq=%x\n",
			pimap->mapped[i].r_hwirq, pimap->mapped[i].v_hwirq);
	पूर्ण
पूर्ण

अटल पूर्णांक xics_debug_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	काष्ठा kvmppc_xics *xics = m->निजी;
	काष्ठा kvm *kvm = xics->kvm;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक icsid, i;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ t_rm_kick_vcpu, t_rm_check_resend;
	अचिन्हित दीर्घ t_rm_notअगरy_eoi;
	अचिन्हित दीर्घ t_reject, t_check_resend;

	अगर (!kvm)
		वापस 0;

	t_rm_kick_vcpu = 0;
	t_rm_notअगरy_eoi = 0;
	t_rm_check_resend = 0;
	t_check_resend = 0;
	t_reject = 0;

	xics_debugfs_irqmap(m, kvm->arch.pimap);

	seq_म_लिखो(m, "=========\nICP state\n=========\n");

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
		जोड़ kvmppc_icp_state state;

		अगर (!icp)
			जारी;

		state.raw = READ_ONCE(icp->state.raw);
		seq_म_लिखो(m, "cpu server %#lx XIRR:%#x PPRI:%#x CPPR:%#x MFRR:%#x OUT:%d NR:%d\n",
			   icp->server_num, state.xisr,
			   state.pending_pri, state.cppr, state.mfrr,
			   state.out_ee, state.need_resend);
		t_rm_kick_vcpu += icp->n_rm_kick_vcpu;
		t_rm_notअगरy_eoi += icp->n_rm_notअगरy_eoi;
		t_rm_check_resend += icp->n_rm_check_resend;
		t_check_resend += icp->n_check_resend;
		t_reject += icp->n_reject;
	पूर्ण

	seq_म_लिखो(m, "ICP Guest->Host totals: kick_vcpu=%lu check_resend=%lu notify_eoi=%lu\n",
			t_rm_kick_vcpu, t_rm_check_resend,
			t_rm_notअगरy_eoi);
	seq_म_लिखो(m, "ICP Real Mode totals: check_resend=%lu resend=%lu\n",
			t_check_resend, t_reject);
	क्रम (icsid = 0; icsid <= KVMPPC_XICS_MAX_ICS_ID; icsid++) अणु
		काष्ठा kvmppc_ics *ics = xics->ics[icsid];

		अगर (!ics)
			जारी;

		seq_म_लिखो(m, "=========\nICS state for ICS 0x%x\n=========\n",
			   icsid);

		local_irq_save(flags);
		arch_spin_lock(&ics->lock);

		क्रम (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) अणु
			काष्ठा ics_irq_state *irq = &ics->irq_state[i];

			seq_म_लिखो(m, "irq 0x%06x: server %#x prio %#x save prio %#x pq_state %d resend %d masked pending %d\n",
				   irq->number, irq->server, irq->priority,
				   irq->saved_priority, irq->pq_state,
				   irq->resend, irq->masked_pending);

		पूर्ण
		arch_spin_unlock(&ics->lock);
		local_irq_restore(flags);
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(xics_debug);

अटल व्योम xics_debugfs_init(काष्ठा kvmppc_xics *xics)
अणु
	अक्षर *name;

	name = kaप्र_लिखो(GFP_KERNEL, "kvm-xics-%p", xics);
	अगर (!name) अणु
		pr_err("%s: no memory for name\n", __func__);
		वापस;
	पूर्ण

	xics->dentry = debugfs_create_file(name, 0444, घातerpc_debugfs_root,
					   xics, &xics_debug_fops);

	pr_debug("%s: created %s\n", __func__, name);
	kमुक्त(name);
पूर्ण

अटल काष्ठा kvmppc_ics *kvmppc_xics_create_ics(काष्ठा kvm *kvm,
					काष्ठा kvmppc_xics *xics, पूर्णांक irq)
अणु
	काष्ठा kvmppc_ics *ics;
	पूर्णांक i, icsid;

	icsid = irq >> KVMPPC_XICS_ICS_SHIFT;

	mutex_lock(&kvm->lock);

	/* ICS alपढ़ोy exists - somebody अन्यथा got here first */
	अगर (xics->ics[icsid])
		जाओ out;

	/* Create the ICS */
	ics = kzalloc(माप(काष्ठा kvmppc_ics), GFP_KERNEL);
	अगर (!ics)
		जाओ out;

	ics->icsid = icsid;

	क्रम (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) अणु
		ics->irq_state[i].number = (icsid << KVMPPC_XICS_ICS_SHIFT) | i;
		ics->irq_state[i].priority = MASKED;
		ics->irq_state[i].saved_priority = MASKED;
	पूर्ण
	smp_wmb();
	xics->ics[icsid] = ics;

	अगर (icsid > xics->max_icsid)
		xics->max_icsid = icsid;

 out:
	mutex_unlock(&kvm->lock);
	वापस xics->ics[icsid];
पूर्ण

अटल पूर्णांक kvmppc_xics_create_icp(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server_num)
अणु
	काष्ठा kvmppc_icp *icp;

	अगर (!vcpu->kvm->arch.xics)
		वापस -ENODEV;

	अगर (kvmppc_xics_find_server(vcpu->kvm, server_num))
		वापस -EEXIST;

	icp = kzalloc(माप(काष्ठा kvmppc_icp), GFP_KERNEL);
	अगर (!icp)
		वापस -ENOMEM;

	icp->vcpu = vcpu;
	icp->server_num = server_num;
	icp->state.mfrr = MASKED;
	icp->state.pending_pri = MASKED;
	vcpu->arch.icp = icp;

	XICS_DBG("created server for vcpu %d\n", vcpu->vcpu_id);

	वापस 0;
पूर्ण

u64 kvmppc_xics_get_icp(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
	जोड़ kvmppc_icp_state state;

	अगर (!icp)
		वापस 0;
	state = icp->state;
	वापस ((u64)state.cppr << KVM_REG_PPC_ICP_CPPR_SHIFT) |
		((u64)state.xisr << KVM_REG_PPC_ICP_XISR_SHIFT) |
		((u64)state.mfrr << KVM_REG_PPC_ICP_MFRR_SHIFT) |
		((u64)state.pending_pri << KVM_REG_PPC_ICP_PPRI_SHIFT);
पूर्ण

पूर्णांक kvmppc_xics_set_icp(काष्ठा kvm_vcpu *vcpu, u64 icpval)
अणु
	काष्ठा kvmppc_icp *icp = vcpu->arch.icp;
	काष्ठा kvmppc_xics *xics = vcpu->kvm->arch.xics;
	जोड़ kvmppc_icp_state old_state, new_state;
	काष्ठा kvmppc_ics *ics;
	u8 cppr, mfrr, pending_pri;
	u32 xisr;
	u16 src;
	bool resend;

	अगर (!icp || !xics)
		वापस -ENOENT;

	cppr = icpval >> KVM_REG_PPC_ICP_CPPR_SHIFT;
	xisr = (icpval >> KVM_REG_PPC_ICP_XISR_SHIFT) &
		KVM_REG_PPC_ICP_XISR_MASK;
	mfrr = icpval >> KVM_REG_PPC_ICP_MFRR_SHIFT;
	pending_pri = icpval >> KVM_REG_PPC_ICP_PPRI_SHIFT;

	/* Require the new state to be पूर्णांकernally consistent */
	अगर (xisr == 0) अणु
		अगर (pending_pri != 0xff)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (xisr == XICS_IPI) अणु
		अगर (pending_pri != mfrr || pending_pri >= cppr)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (pending_pri >= mfrr || pending_pri >= cppr)
			वापस -EINVAL;
		ics = kvmppc_xics_find_ics(xics, xisr, &src);
		अगर (!ics)
			वापस -EINVAL;
	पूर्ण

	new_state.raw = 0;
	new_state.cppr = cppr;
	new_state.xisr = xisr;
	new_state.mfrr = mfrr;
	new_state.pending_pri = pending_pri;

	/*
	 * Deनिश्चित the CPU पूर्णांकerrupt request.
	 * icp_try_update will reनिश्चित it अगर necessary.
	 */
	kvmppc_book3s_dequeue_irqprio(icp->vcpu, BOOK3S_INTERRUPT_EXTERNAL);

	/*
	 * Note that अगर we displace an पूर्णांकerrupt from old_state.xisr,
	 * we करोn't mark it as rejected.  We expect userspace to set
	 * the state of the पूर्णांकerrupt sources to be consistent with
	 * the ICP states (either beक्रमe or afterwards, which करोesn't
	 * matter).  We करो handle resends due to CPPR becoming less
	 * favoured because that is necessary to end up with a
	 * consistent state in the situation where userspace restores
	 * the ICS states beक्रमe the ICP states.
	 */
	करो अणु
		old_state = READ_ONCE(icp->state);

		अगर (new_state.mfrr <= old_state.mfrr) अणु
			resend = false;
			new_state.need_resend = old_state.need_resend;
		पूर्ण अन्यथा अणु
			resend = old_state.need_resend;
			new_state.need_resend = 0;
		पूर्ण
	पूर्ण जबतक (!icp_try_update(icp, old_state, new_state, false));

	अगर (resend)
		icp_check_resend(xics, icp);

	वापस 0;
पूर्ण

अटल पूर्णांक xics_get_source(काष्ठा kvmppc_xics *xics, दीर्घ irq, u64 addr)
अणु
	पूर्णांक ret;
	काष्ठा kvmppc_ics *ics;
	काष्ठा ics_irq_state *irqp;
	u64 __user *ubufp = (u64 __user *) addr;
	u16 idx;
	u64 val, prio;
	अचिन्हित दीर्घ flags;

	ics = kvmppc_xics_find_ics(xics, irq, &idx);
	अगर (!ics)
		वापस -ENOENT;

	irqp = &ics->irq_state[idx];
	local_irq_save(flags);
	arch_spin_lock(&ics->lock);
	ret = -ENOENT;
	अगर (irqp->exists) अणु
		val = irqp->server;
		prio = irqp->priority;
		अगर (prio == MASKED) अणु
			val |= KVM_XICS_MASKED;
			prio = irqp->saved_priority;
		पूर्ण
		val |= prio << KVM_XICS_PRIORITY_SHIFT;
		अगर (irqp->lsi) अणु
			val |= KVM_XICS_LEVEL_SENSITIVE;
			अगर (irqp->pq_state & PQ_PRESENTED)
				val |= KVM_XICS_PENDING;
		पूर्ण अन्यथा अगर (irqp->masked_pending || irqp->resend)
			val |= KVM_XICS_PENDING;

		अगर (irqp->pq_state & PQ_PRESENTED)
			val |= KVM_XICS_PRESENTED;

		अगर (irqp->pq_state & PQ_QUEUED)
			val |= KVM_XICS_QUEUED;

		ret = 0;
	पूर्ण
	arch_spin_unlock(&ics->lock);
	local_irq_restore(flags);

	अगर (!ret && put_user(val, ubufp))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक xics_set_source(काष्ठा kvmppc_xics *xics, दीर्घ irq, u64 addr)
अणु
	काष्ठा kvmppc_ics *ics;
	काष्ठा ics_irq_state *irqp;
	u64 __user *ubufp = (u64 __user *) addr;
	u16 idx;
	u64 val;
	u8 prio;
	u32 server;
	अचिन्हित दीर्घ flags;

	अगर (irq < KVMPPC_XICS_FIRST_IRQ || irq >= KVMPPC_XICS_NR_IRQS)
		वापस -ENOENT;

	ics = kvmppc_xics_find_ics(xics, irq, &idx);
	अगर (!ics) अणु
		ics = kvmppc_xics_create_ics(xics->kvm, xics, irq);
		अगर (!ics)
			वापस -ENOMEM;
	पूर्ण
	irqp = &ics->irq_state[idx];
	अगर (get_user(val, ubufp))
		वापस -EFAULT;

	server = val & KVM_XICS_DESTINATION_MASK;
	prio = val >> KVM_XICS_PRIORITY_SHIFT;
	अगर (prio != MASKED &&
	    kvmppc_xics_find_server(xics->kvm, server) == शून्य)
		वापस -EINVAL;

	local_irq_save(flags);
	arch_spin_lock(&ics->lock);
	irqp->server = server;
	irqp->saved_priority = prio;
	अगर (val & KVM_XICS_MASKED)
		prio = MASKED;
	irqp->priority = prio;
	irqp->resend = 0;
	irqp->masked_pending = 0;
	irqp->lsi = 0;
	irqp->pq_state = 0;
	अगर (val & KVM_XICS_LEVEL_SENSITIVE)
		irqp->lsi = 1;
	/* If PENDING, set P in हाल P is not saved because of old code */
	अगर (val & KVM_XICS_PRESENTED || val & KVM_XICS_PENDING)
		irqp->pq_state |= PQ_PRESENTED;
	अगर (val & KVM_XICS_QUEUED)
		irqp->pq_state |= PQ_QUEUED;
	irqp->exists = 1;
	arch_spin_unlock(&ics->lock);
	local_irq_restore(flags);

	अगर (val & KVM_XICS_PENDING)
		icp_deliver_irq(xics, शून्य, irqp->number, false);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xics_set_irq(काष्ठा kvm *kvm, पूर्णांक irq_source_id, u32 irq, पूर्णांक level,
			bool line_status)
अणु
	काष्ठा kvmppc_xics *xics = kvm->arch.xics;

	अगर (!xics)
		वापस -ENODEV;
	वापस ics_deliver_irq(xics, irq, level);
पूर्ण

अटल पूर्णांक xics_set_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvmppc_xics *xics = dev->निजी;

	चयन (attr->group) अणु
	हाल KVM_DEV_XICS_GRP_SOURCES:
		वापस xics_set_source(xics, attr->attr, attr->addr);
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक xics_get_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvmppc_xics *xics = dev->निजी;

	चयन (attr->group) अणु
	हाल KVM_DEV_XICS_GRP_SOURCES:
		वापस xics_get_source(xics, attr->attr, attr->addr);
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक xics_has_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_XICS_GRP_SOURCES:
		अगर (attr->attr >= KVMPPC_XICS_FIRST_IRQ &&
		    attr->attr < KVMPPC_XICS_NR_IRQS)
			वापस 0;
		अवरोध;
	पूर्ण
	वापस -ENXIO;
पूर्ण

/*
 * Called when device fd is बंदd. kvm->lock is held.
 */
अटल व्योम kvmppc_xics_release(काष्ठा kvm_device *dev)
अणु
	काष्ठा kvmppc_xics *xics = dev->निजी;
	पूर्णांक i;
	काष्ठा kvm *kvm = xics->kvm;
	काष्ठा kvm_vcpu *vcpu;

	pr_devel("Releasing xics device\n");

	/*
	 * Since this is the device release function, we know that
	 * userspace करोes not have any खोलो fd referring to the
	 * device.  Thereक्रमe there can not be any of the device
	 * attribute set/get functions being executed concurrently,
	 * and similarly, the connect_vcpu and set/clr_mapped
	 * functions also cannot be being executed.
	 */

	debugfs_हटाओ(xics->dentry);

	/*
	 * We should clean up the vCPU पूर्णांकerrupt presenters first.
	 */
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		/*
		 * Take vcpu->mutex to ensure that no one_reg get/set ioctl
		 * (i.e. kvmppc_xics_[gs]et_icp) can be करोne concurrently.
		 * Holding the vcpu->mutex also means that execution is
		 * excluded क्रम the vcpu until the ICP was मुक्तd. When the vcpu
		 * can execute again, vcpu->arch.icp and vcpu->arch.irq_type
		 * have been cleared and the vcpu will not be going पूर्णांकo the
		 * XICS code anymore.
		 */
		mutex_lock(&vcpu->mutex);
		kvmppc_xics_मुक्त_icp(vcpu);
		mutex_unlock(&vcpu->mutex);
	पूर्ण

	अगर (kvm)
		kvm->arch.xics = शून्य;

	क्रम (i = 0; i <= xics->max_icsid; i++) अणु
		kमुक्त(xics->ics[i]);
		xics->ics[i] = शून्य;
	पूर्ण
	/*
	 * A reference of the kvmppc_xics poपूर्णांकer is now kept under
	 * the xics_device poपूर्णांकer of the machine क्रम reuse. It is
	 * मुक्तd when the VM is destroyed क्रम now until we fix all the
	 * execution paths.
	 */
	kमुक्त(dev);
पूर्ण

अटल काष्ठा kvmppc_xics *kvmppc_xics_get_device(काष्ठा kvm *kvm)
अणु
	काष्ठा kvmppc_xics **kvm_xics_device = &kvm->arch.xics_device;
	काष्ठा kvmppc_xics *xics = *kvm_xics_device;

	अगर (!xics) अणु
		xics = kzalloc(माप(*xics), GFP_KERNEL);
		*kvm_xics_device = xics;
	पूर्ण अन्यथा अणु
		स_रखो(xics, 0, माप(*xics));
	पूर्ण

	वापस xics;
पूर्ण

अटल पूर्णांक kvmppc_xics_create(काष्ठा kvm_device *dev, u32 type)
अणु
	काष्ठा kvmppc_xics *xics;
	काष्ठा kvm *kvm = dev->kvm;

	pr_devel("Creating xics for partition\n");

	/* Alपढ़ोy there ? */
	अगर (kvm->arch.xics)
		वापस -EEXIST;

	xics = kvmppc_xics_get_device(kvm);
	अगर (!xics)
		वापस -ENOMEM;

	dev->निजी = xics;
	xics->dev = dev;
	xics->kvm = kvm;
	kvm->arch.xics = xics;

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	अगर (cpu_has_feature(CPU_FTR_ARCH_206) &&
	    cpu_has_feature(CPU_FTR_HVMODE)) अणु
		/* Enable real mode support */
		xics->real_mode = ENABLE_REALMODE;
		xics->real_mode_dbg = DEBUG_REALMODE;
	पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */

	वापस 0;
पूर्ण

अटल व्योम kvmppc_xics_init(काष्ठा kvm_device *dev)
अणु
	काष्ठा kvmppc_xics *xics = (काष्ठा kvmppc_xics *)dev->निजी;

	xics_debugfs_init(xics);
पूर्ण

काष्ठा kvm_device_ops kvm_xics_ops = अणु
	.name = "kvm-xics",
	.create = kvmppc_xics_create,
	.init = kvmppc_xics_init,
	.release = kvmppc_xics_release,
	.set_attr = xics_set_attr,
	.get_attr = xics_get_attr,
	.has_attr = xics_has_attr,
पूर्ण;

पूर्णांक kvmppc_xics_connect_vcpu(काष्ठा kvm_device *dev, काष्ठा kvm_vcpu *vcpu,
			     u32 xcpu)
अणु
	काष्ठा kvmppc_xics *xics = dev->निजी;
	पूर्णांक r = -EBUSY;

	अगर (dev->ops != &kvm_xics_ops)
		वापस -EPERM;
	अगर (xics->kvm != vcpu->kvm)
		वापस -EPERM;
	अगर (vcpu->arch.irq_type != KVMPPC_IRQ_DEFAULT)
		वापस -EBUSY;

	r = kvmppc_xics_create_icp(vcpu, xcpu);
	अगर (!r)
		vcpu->arch.irq_type = KVMPPC_IRQ_XICS;

	वापस r;
पूर्ण

व्योम kvmppc_xics_मुक्त_icp(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!vcpu->arch.icp)
		वापस;
	kमुक्त(vcpu->arch.icp);
	vcpu->arch.icp = शून्य;
	vcpu->arch.irq_type = KVMPPC_IRQ_DEFAULT;
पूर्ण

व्योम kvmppc_xics_set_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ irq,
			    अचिन्हित दीर्घ host_irq)
अणु
	काष्ठा kvmppc_xics *xics = kvm->arch.xics;
	काष्ठा kvmppc_ics *ics;
	u16 idx;

	ics = kvmppc_xics_find_ics(xics, irq, &idx);
	अगर (!ics)
		वापस;

	ics->irq_state[idx].host_irq = host_irq;
	ics->irq_state[idx].पूर्णांकr_cpu = -1;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_xics_set_mapped);

व्योम kvmppc_xics_clr_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ irq,
			    अचिन्हित दीर्घ host_irq)
अणु
	काष्ठा kvmppc_xics *xics = kvm->arch.xics;
	काष्ठा kvmppc_ics *ics;
	u16 idx;

	ics = kvmppc_xics_find_ics(xics, irq, &idx);
	अगर (!ics)
		वापस;

	ics->irq_state[idx].host_irq = 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_xics_clr_mapped);
