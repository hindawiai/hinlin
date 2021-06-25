<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Benjamin Herrenschmidt, IBM Corporation
 */

/* File to be included by other .c files */

#घोषणा XGLUE(a,b) a##b
#घोषणा GLUE(a,b) XGLUE(a,b)

/* Dummy पूर्णांकerrupt used when taking पूर्णांकerrupts out of a queue in H_CPPR */
#घोषणा XICS_DUMMY	1

अटल व्योम GLUE(X_PFX,ack_pending)(काष्ठा kvmppc_xive_vcpu *xc)
अणु
	u8 cppr;
	u16 ack;

	/*
	 * Ensure any previous store to CPPR is ordered vs.
	 * the subsequent loads from PIPR or ACK.
	 */
	eieio();

	/* Perक्रमm the acknowledge OS to रेजिस्टर cycle. */
	ack = be16_to_cpu(__x_पढ़ोw(__x_tima + TM_SPC_ACK_OS_REG));

	/* Synchronize subsequent queue accesses */
	mb();

	/* XXX Check grouping level */

	/* Anything ? */
	अगर (!((ack >> 8) & TM_QW1_NSR_EO))
		वापस;

	/* Grab CPPR of the most favored pending पूर्णांकerrupt */
	cppr = ack & 0xff;
	अगर (cppr < 8)
		xc->pending |= 1 << cppr;

#अगर_घोषित XIVE_RUNTIME_CHECKS
	/* Check consistency */
	अगर (cppr >= xc->hw_cppr)
		pr_warn("KVM-XIVE: CPU %d odd ack CPPR, got %d at %d\n",
			smp_processor_id(), cppr, xc->hw_cppr);
#पूर्ण_अगर

	/*
	 * Update our image of the HW CPPR. We करोn't yet modअगरy
	 * xc->cppr, this will be करोne as we scan क्रम पूर्णांकerrupts
	 * in the queues.
	 */
	xc->hw_cppr = cppr;
पूर्ण

अटल u8 GLUE(X_PFX,esb_load)(काष्ठा xive_irq_data *xd, u32 offset)
अणु
	u64 val;

	अगर (offset == XIVE_ESB_SET_PQ_10 && xd->flags & XIVE_IRQ_FLAG_STORE_EOI)
		offset |= XIVE_ESB_LD_ST_MO;

	val =__x_पढ़ोq(__x_eoi_page(xd) + offset);
#अगर_घोषित __LITTLE_ENDIAN__
	val >>= 64-8;
#पूर्ण_अगर
	वापस (u8)val;
पूर्ण


अटल व्योम GLUE(X_PFX,source_eoi)(u32 hw_irq, काष्ठा xive_irq_data *xd)
अणु
	/* If the XIVE supports the new "store EOI facility, use it */
	अगर (xd->flags & XIVE_IRQ_FLAG_STORE_EOI)
		__x_ग_लिखोq(0, __x_eoi_page(xd) + XIVE_ESB_STORE_EOI);
	अन्यथा अगर (xd->flags & XIVE_IRQ_FLAG_LSI) अणु
		/*
		 * For LSIs the HW EOI cycle is used rather than PQ bits,
		 * as they are स्वतःmatically re-triggred in HW when still
		 * pending.
		 */
		__x_पढ़ोq(__x_eoi_page(xd) + XIVE_ESB_LOAD_EOI);
	पूर्ण अन्यथा अणु
		uपूर्णांक64_t eoi_val;

		/*
		 * Otherwise क्रम EOI, we use the special MMIO that करोes
		 * a clear of both P and Q and वापसs the old Q,
		 * except क्रम LSIs where we use the "EOI cycle" special
		 * load.
		 *
		 * This allows us to then करो a re-trigger अगर Q was set
		 * rather than synthetizing an पूर्णांकerrupt in software
		 */
		eoi_val = GLUE(X_PFX,esb_load)(xd, XIVE_ESB_SET_PQ_00);

		/* Re-trigger अगर needed */
		अगर ((eoi_val & 1) && __x_trig_page(xd))
			__x_ग_लिखोq(0, __x_trig_page(xd));
	पूर्ण
पूर्ण

क्रमागत अणु
	scan_fetch,
	scan_poll,
	scan_eoi,
पूर्ण;

अटल u32 GLUE(X_PFX,scan_पूर्णांकerrupts)(काष्ठा kvmppc_xive_vcpu *xc,
				       u8 pending, पूर्णांक scan_type)
अणु
	u32 hirq = 0;
	u8 prio = 0xff;

	/* Find highest pending priority */
	जबतक ((xc->mfrr != 0xff || pending != 0) && hirq == 0) अणु
		काष्ठा xive_q *q;
		u32 idx, toggle;
		__be32 *qpage;

		/*
		 * If pending is 0 this will वापस 0xff which is what
		 * we want
		 */
		prio = ffs(pending) - 1;

		/* Don't scan past the guest cppr */
		अगर (prio >= xc->cppr || prio > 7) अणु
			अगर (xc->mfrr < xc->cppr) अणु
				prio = xc->mfrr;
				hirq = XICS_IPI;
			पूर्ण
			अवरोध;
		पूर्ण

		/* Grab queue and poपूर्णांकers */
		q = &xc->queues[prio];
		idx = q->idx;
		toggle = q->toggle;

		/*
		 * Snapshot the queue page. The test further करोwn क्रम EOI
		 * must use the same "copy" that was used by __xive_पढ़ो_eq
		 * since qpage can be set concurrently and we करोn't want
		 * to miss an EOI.
		 */
		qpage = READ_ONCE(q->qpage);

skip_ipi:
		/*
		 * Try to fetch from the queue. Will वापस 0 क्रम a
		 * non-queueing priority (ie, qpage = 0).
		 */
		hirq = __xive_पढ़ो_eq(qpage, q->msk, &idx, &toggle);

		/*
		 * If this was a संकेत क्रम an MFFR change करोne by
		 * H_IPI we skip it. Additionally, अगर we were fetching
		 * we EOI it now, thus re-enabling reception of a new
		 * such संकेत.
		 *
		 * We also need to करो that अगर prio is 0 and we had no
		 * page क्रम the queue. In this हाल, we have non-queued
		 * IPI that needs to be EOId.
		 *
		 * This is safe because अगर we have another pending MFRR
		 * change that wasn't observed above, the Q bit will have
		 * been set and another occurrence of the IPI will trigger.
		 */
		अगर (hirq == XICS_IPI || (prio == 0 && !qpage)) अणु
			अगर (scan_type == scan_fetch) अणु
				GLUE(X_PFX,source_eoi)(xc->vp_ipi,
						       &xc->vp_ipi_data);
				q->idx = idx;
				q->toggle = toggle;
			पूर्ण
			/* Loop back on same queue with updated idx/toggle */
#अगर_घोषित XIVE_RUNTIME_CHECKS
			WARN_ON(hirq && hirq != XICS_IPI);
#पूर्ण_अगर
			अगर (hirq)
				जाओ skip_ipi;
		पूर्ण

		/* If it's the dummy पूर्णांकerrupt, जारी searching */
		अगर (hirq == XICS_DUMMY)
			जाओ skip_ipi;

		/* Clear the pending bit अगर the queue is now empty */
		अगर (!hirq) अणु
			pending &= ~(1 << prio);

			/*
			 * Check अगर the queue count needs adjusting due to
			 * पूर्णांकerrupts being moved away.
			 */
			अगर (atomic_पढ़ो(&q->pending_count)) अणु
				पूर्णांक p = atomic_xchg(&q->pending_count, 0);
				अगर (p) अणु
#अगर_घोषित XIVE_RUNTIME_CHECKS
					WARN_ON(p > atomic_पढ़ो(&q->count));
#पूर्ण_अगर
					atomic_sub(p, &q->count);
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * If the most favoured prio we found pending is less
		 * favored (or equal) than a pending IPI, we वापस
		 * the IPI instead.
		 */
		अगर (prio >= xc->mfrr && xc->mfrr < xc->cppr) अणु
			prio = xc->mfrr;
			hirq = XICS_IPI;
			अवरोध;
		पूर्ण

		/* If fetching, update queue poपूर्णांकers */
		अगर (scan_type == scan_fetch) अणु
			q->idx = idx;
			q->toggle = toggle;
		पूर्ण
	पूर्ण

	/* If we are just taking a "peek", करो nothing अन्यथा */
	अगर (scan_type == scan_poll)
		वापस hirq;

	/* Update the pending bits */
	xc->pending = pending;

	/*
	 * If this is an EOI that's it, no CPPR adjusपंचांगent करोne here,
	 * all we needed was cleanup the stale pending bits and check
	 * अगर there's anything left.
	 */
	अगर (scan_type == scan_eoi)
		वापस hirq;

	/*
	 * If we found an पूर्णांकerrupt, adjust what the guest CPPR should
	 * be as अगर we had just fetched that पूर्णांकerrupt from HW.
	 *
	 * Note: This can only make xc->cppr smaller as the previous
	 * loop will only निकास with hirq != 0 अगर prio is lower than
	 * the current xc->cppr. Thus we करोn't need to re-check xc->mfrr
	 * क्रम pending IPIs.
	 */
	अगर (hirq)
		xc->cppr = prio;
	/*
	 * If it was an IPI the HW CPPR might have been lowered too much
	 * as the HW पूर्णांकerrupt we use क्रम IPIs is routed to priority 0.
	 *
	 * We re-sync it here.
	 */
	अगर (xc->cppr != xc->hw_cppr) अणु
		xc->hw_cppr = xc->cppr;
		__x_ग_लिखोb(xc->cppr, __x_tima + TM_QW1_OS + TM_CPPR);
	पूर्ण

	वापस hirq;
पूर्ण

X_STATIC अचिन्हित दीर्घ GLUE(X_PFX,h_xirr)(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	u8 old_cppr;
	u32 hirq;

	pr_devel("H_XIRR\n");

	xc->GLUE(X_STAT_PFX,h_xirr)++;

	/* First collect pending bits from HW */
	GLUE(X_PFX,ack_pending)(xc);

	pr_devel(" new pending=0x%02x hw_cppr=%d cppr=%d\n",
		 xc->pending, xc->hw_cppr, xc->cppr);

	/* Grab previous CPPR and reverse map it */
	old_cppr = xive_prio_to_guest(xc->cppr);

	/* Scan क्रम actual पूर्णांकerrupts */
	hirq = GLUE(X_PFX,scan_पूर्णांकerrupts)(xc, xc->pending, scan_fetch);

	pr_devel(" got hirq=0x%x hw_cppr=%d cppr=%d\n",
		 hirq, xc->hw_cppr, xc->cppr);

#अगर_घोषित XIVE_RUNTIME_CHECKS
	/* That should never hit */
	अगर (hirq & 0xff000000)
		pr_warn("XIVE: Weird guest interrupt number 0x%08x\n", hirq);
#पूर्ण_अगर

	/*
	 * XXX We could check अगर the पूर्णांकerrupt is masked here and
	 * filter it. If we chose to करो so, we would need to करो:
	 *
	 *    अगर (masked) अणु
	 *        lock();
	 *        अगर (masked) अणु
	 *            old_Q = true;
	 *            hirq = 0;
	 *        पूर्ण
	 *        unlock();
	 *    पूर्ण
	 */

	/* Return पूर्णांकerrupt and old CPPR in GPR4 */
	vcpu->arch.regs.gpr[4] = hirq | (old_cppr << 24);

	वापस H_SUCCESS;
पूर्ण

X_STATIC अचिन्हित दीर्घ GLUE(X_PFX,h_ipoll)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	u8 pending = xc->pending;
	u32 hirq;

	pr_devel("H_IPOLL(server=%ld)\n", server);

	xc->GLUE(X_STAT_PFX,h_ipoll)++;

	/* Grab the target VCPU अगर not the current one */
	अगर (xc->server_num != server) अणु
		vcpu = kvmppc_xive_find_server(vcpu->kvm, server);
		अगर (!vcpu)
			वापस H_PARAMETER;
		xc = vcpu->arch.xive_vcpu;

		/* Scan all priorities */
		pending = 0xff;
	पूर्ण अन्यथा अणु
		/* Grab pending पूर्णांकerrupt अगर any */
		__be64 qw1 = __x_पढ़ोq(__x_tima + TM_QW1_OS);
		u8 pipr = be64_to_cpu(qw1) & 0xff;
		अगर (pipr < 8)
			pending |= 1 << pipr;
	पूर्ण

	hirq = GLUE(X_PFX,scan_पूर्णांकerrupts)(xc, pending, scan_poll);

	/* Return पूर्णांकerrupt and old CPPR in GPR4 */
	vcpu->arch.regs.gpr[4] = hirq | (xc->cppr << 24);

	वापस H_SUCCESS;
पूर्ण

अटल व्योम GLUE(X_PFX,push_pending_to_hw)(काष्ठा kvmppc_xive_vcpu *xc)
अणु
	u8 pending, prio;

	pending = xc->pending;
	अगर (xc->mfrr != 0xff) अणु
		अगर (xc->mfrr < 8)
			pending |= 1 << xc->mfrr;
		अन्यथा
			pending |= 0x80;
	पूर्ण
	अगर (!pending)
		वापस;
	prio = ffs(pending) - 1;

	__x_ग_लिखोb(prio, __x_tima + TM_SPC_SET_OS_PENDING);
पूर्ण

अटल व्योम GLUE(X_PFX,scan_क्रम_rerouted_irqs)(काष्ठा kvmppc_xive *xive,
					       काष्ठा kvmppc_xive_vcpu *xc)
अणु
	अचिन्हित पूर्णांक prio;

	/* For each priority that is now masked */
	क्रम (prio = xc->cppr; prio < KVMPPC_XIVE_Q_COUNT; prio++) अणु
		काष्ठा xive_q *q = &xc->queues[prio];
		काष्ठा kvmppc_xive_irq_state *state;
		काष्ठा kvmppc_xive_src_block *sb;
		u32 idx, toggle, entry, irq, hw_num;
		काष्ठा xive_irq_data *xd;
		__be32 *qpage;
		u16 src;

		idx = q->idx;
		toggle = q->toggle;
		qpage = READ_ONCE(q->qpage);
		अगर (!qpage)
			जारी;

		/* For each पूर्णांकerrupt in the queue */
		क्रम (;;) अणु
			entry = be32_to_cpup(qpage + idx);

			/* No more ? */
			अगर ((entry >> 31) == toggle)
				अवरोध;
			irq = entry & 0x7fffffff;

			/* Skip dummies and IPIs */
			अगर (irq == XICS_DUMMY || irq == XICS_IPI)
				जाओ next;
			sb = kvmppc_xive_find_source(xive, irq, &src);
			अगर (!sb)
				जाओ next;
			state = &sb->irq_state[src];

			/* Has it been rerouted ? */
			अगर (xc->server_num == state->act_server)
				जाओ next;

			/*
			 * Allright, it *has* been re-routed, समाप्त it from
			 * the queue.
			 */
			qpage[idx] = cpu_to_be32((entry & 0x80000000) | XICS_DUMMY);

			/* Find the HW पूर्णांकerrupt */
			kvmppc_xive_select_irq(state, &hw_num, &xd);

			/* If it's not an LSI, set PQ to 11 the EOI will क्रमce a resend */
			अगर (!(xd->flags & XIVE_IRQ_FLAG_LSI))
				GLUE(X_PFX,esb_load)(xd, XIVE_ESB_SET_PQ_11);

			/* EOI the source */
			GLUE(X_PFX,source_eoi)(hw_num, xd);

		next:
			idx = (idx + 1) & q->msk;
			अगर (idx == 0)
				toggle ^= 1;
		पूर्ण
	पूर्ण
पूर्ण

X_STATIC पूर्णांक GLUE(X_PFX,h_cppr)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cppr)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा kvmppc_xive *xive = vcpu->kvm->arch.xive;
	u8 old_cppr;

	pr_devel("H_CPPR(cppr=%ld)\n", cppr);

	xc->GLUE(X_STAT_PFX,h_cppr)++;

	/* Map CPPR */
	cppr = xive_prio_from_guest(cppr);

	/* Remember old and update SW state */
	old_cppr = xc->cppr;
	xc->cppr = cppr;

	/*
	 * Order the above update of xc->cppr with the subsequent
	 * पढ़ो of xc->mfrr inside push_pending_to_hw()
	 */
	smp_mb();

	अगर (cppr > old_cppr) अणु
		/*
		 * We are masking less, we need to look क्रम pending things
		 * to deliver and set VP pending bits accordingly to trigger
		 * a new पूर्णांकerrupt otherwise we might miss MFRR changes क्रम
		 * which we have optimized out sending an IPI संकेत.
		 */
		GLUE(X_PFX,push_pending_to_hw)(xc);
	पूर्ण अन्यथा अणु
		/*
		 * We are masking more, we need to check the queue क्रम any
		 * पूर्णांकerrupt that has been routed to another CPU, take
		 * it out (replace it with the dummy) and retrigger it.
		 *
		 * This is necessary since those पूर्णांकerrupts may otherwise
		 * never be processed, at least not until this CPU restores
		 * its CPPR.
		 *
		 * This is in theory racy vs. HW adding new पूर्णांकerrupts to
		 * the queue. In practice this works because the पूर्णांकeresting
		 * हालs are when the guest has करोne a set_xive() to move the
		 * पूर्णांकerrupt away, which flushes the xive, followed by the
		 * target CPU करोing a H_CPPR. So any new पूर्णांकerrupt coming पूर्णांकo
		 * the queue must still be routed to us and isn't a source
		 * of concern.
		 */
		GLUE(X_PFX,scan_क्रम_rerouted_irqs)(xive, xc);
	पूर्ण

	/* Apply new CPPR */
	xc->hw_cppr = cppr;
	__x_ग_लिखोb(cppr, __x_tima + TM_QW1_OS + TM_CPPR);

	वापस H_SUCCESS;
पूर्ण

X_STATIC पूर्णांक GLUE(X_PFX,h_eoi)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ xirr)
अणु
	काष्ठा kvmppc_xive *xive = vcpu->kvm->arch.xive;
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा xive_irq_data *xd;
	u8 new_cppr = xirr >> 24;
	u32 irq = xirr & 0x00ffffff, hw_num;
	u16 src;
	पूर्णांक rc = 0;

	pr_devel("H_EOI(xirr=%08lx)\n", xirr);

	xc->GLUE(X_STAT_PFX,h_eoi)++;

	xc->cppr = xive_prio_from_guest(new_cppr);

	/*
	 * IPIs are synthetized from MFRR and thus करोn't need
	 * any special EOI handling. The underlying पूर्णांकerrupt
	 * used to संकेत MFRR changes is EOId when fetched from
	 * the queue.
	 */
	अगर (irq == XICS_IPI || irq == 0) अणु
		/*
		 * This barrier orders the setting of xc->cppr vs.
		 * subsquent test of xc->mfrr करोne inside
		 * scan_पूर्णांकerrupts and push_pending_to_hw
		 */
		smp_mb();
		जाओ bail;
	पूर्ण

	/* Find पूर्णांकerrupt source */
	sb = kvmppc_xive_find_source(xive, irq, &src);
	अगर (!sb) अणु
		pr_devel(" source not found !\n");
		rc = H_PARAMETER;
		/* Same as above */
		smp_mb();
		जाओ bail;
	पूर्ण
	state = &sb->irq_state[src];
	kvmppc_xive_select_irq(state, &hw_num, &xd);

	state->in_eoi = true;

	/*
	 * This barrier orders both setting of in_eoi above vs,
	 * subsequent test of guest_priority, and the setting
	 * of xc->cppr vs. subsquent test of xc->mfrr करोne inside
	 * scan_पूर्णांकerrupts and push_pending_to_hw
	 */
	smp_mb();

again:
	अगर (state->guest_priority == MASKED) अणु
		arch_spin_lock(&sb->lock);
		अगर (state->guest_priority != MASKED) अणु
			arch_spin_unlock(&sb->lock);
			जाओ again;
		पूर्ण
		pr_devel(" EOI on saved P...\n");

		/* Clear old_p, that will cause unmask to perक्रमm an EOI */
		state->old_p = false;

		arch_spin_unlock(&sb->lock);
	पूर्ण अन्यथा अणु
		pr_devel(" EOI on source...\n");

		/* Perक्रमm EOI on the source */
		GLUE(X_PFX,source_eoi)(hw_num, xd);

		/* If it's an emulated LSI, check level and resend */
		अगर (state->lsi && state->निश्चितed)
			__x_ग_लिखोq(0, __x_trig_page(xd));

	पूर्ण

	/*
	 * This barrier orders the above guest_priority check
	 * and spin_lock/unlock with clearing in_eoi below.
	 *
	 * It also has to be a full mb() as it must ensure
	 * the MMIOs करोne in source_eoi() are completed beक्रमe
	 * state->in_eoi is visible.
	 */
	mb();
	state->in_eoi = false;
bail:

	/* Re-evaluate pending IRQs and update HW */
	GLUE(X_PFX,scan_पूर्णांकerrupts)(xc, xc->pending, scan_eoi);
	GLUE(X_PFX,push_pending_to_hw)(xc);
	pr_devel(" after scan pending=%02x\n", xc->pending);

	/* Apply new CPPR */
	xc->hw_cppr = xc->cppr;
	__x_ग_लिखोb(xc->cppr, __x_tima + TM_QW1_OS + TM_CPPR);

	वापस rc;
पूर्ण

X_STATIC पूर्णांक GLUE(X_PFX,h_ipi)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server,
			       अचिन्हित दीर्घ mfrr)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;

	pr_devel("H_IPI(server=%08lx,mfrr=%ld)\n", server, mfrr);

	xc->GLUE(X_STAT_PFX,h_ipi)++;

	/* Find target */
	vcpu = kvmppc_xive_find_server(vcpu->kvm, server);
	अगर (!vcpu)
		वापस H_PARAMETER;
	xc = vcpu->arch.xive_vcpu;

	/* Locklessly ग_लिखो over MFRR */
	xc->mfrr = mfrr;

	/*
	 * The load of xc->cppr below and the subsequent MMIO store
	 * to the IPI must happen after the above mfrr update is
	 * globally visible so that:
	 *
	 * - Synchronize with another CPU करोing an H_EOI or a H_CPPR
	 *   updating xc->cppr then पढ़ोing xc->mfrr.
	 *
	 * - The target of the IPI sees the xc->mfrr update
	 */
	mb();

	/* Shoot the IPI अगर most favored than target cppr */
	अगर (mfrr < xc->cppr)
		__x_ग_लिखोq(0, __x_trig_page(&xc->vp_ipi_data));

	वापस H_SUCCESS;
पूर्ण
