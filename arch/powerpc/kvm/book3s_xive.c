<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Benjamin Herrenschmidt, IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "xive-kvm: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/xive-regs.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/opal.h>

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश "book3s_xive.h"


/*
 * Virtual mode variants of the hcalls क्रम use on radix/radix
 * with AIL. They require the VCPU's VP to be "pushed"
 *
 * We still instantiate them here because we use some of the
 * generated utility functions as well in this file.
 */
#घोषणा XIVE_RUNTIME_CHECKS
#घोषणा X_PFX xive_vm_
#घोषणा X_STATIC अटल
#घोषणा X_STAT_PFX stat_vm_
#घोषणा __x_tima		xive_tima
#घोषणा __x_eoi_page(xd)	((व्योम __iomem *)((xd)->eoi_mmio))
#घोषणा __x_trig_page(xd)	((व्योम __iomem *)((xd)->trig_mmio))
#घोषणा __x_ग_लिखोb	__raw_ग_लिखोb
#घोषणा __x_पढ़ोw	__raw_पढ़ोw
#घोषणा __x_पढ़ोq	__raw_पढ़ोq
#घोषणा __x_ग_लिखोq	__raw_ग_लिखोq

#समावेश "book3s_xive_template.c"

/*
 * We leave a gap of a couple of पूर्णांकerrupts in the queue to
 * account क्रम the IPI and additional safety guard.
 */
#घोषणा XIVE_Q_GAP	2

/*
 * Push a vcpu's context to the XIVE on guest entry.
 * This assumes we are in भव mode (MMU on)
 */
व्योम kvmppc_xive_push_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	व्योम __iomem *tima = local_paca->kvm_hstate.xive_tima_virt;
	u64 pq;

	/*
	 * Nothing to करो अगर the platक्रमm करोesn't have a XIVE
	 * or this vCPU करोesn't have its own XIVE context
	 * (e.g. because it's not using an in-kernel पूर्णांकerrupt controller).
	 */
	अगर (!tima || !vcpu->arch.xive_cam_word)
		वापस;

	eieio();
	__raw_ग_लिखोq(vcpu->arch.xive_saved_state.w01, tima + TM_QW1_OS);
	__raw_ग_लिखोl(vcpu->arch.xive_cam_word, tima + TM_QW1_OS + TM_WORD2);
	vcpu->arch.xive_pushed = 1;
	eieio();

	/*
	 * We clear the irq_pending flag. There is a small chance of a
	 * race vs. the escalation पूर्णांकerrupt happening on another
	 * processor setting it again, but the only consequence is to
	 * cause a spurious wakeup on the next H_CEDE, which is not an
	 * issue.
	 */
	vcpu->arch.irq_pending = 0;

	/*
	 * In single escalation mode, अगर the escalation पूर्णांकerrupt is
	 * on, we mask it.
	 */
	अगर (vcpu->arch.xive_esc_on) अणु
		pq = __raw_पढ़ोq((व्योम __iomem *)(vcpu->arch.xive_esc_vaddr +
						  XIVE_ESB_SET_PQ_01));
		mb();

		/*
		 * We have a possible subtle race here: The escalation
		 * पूर्णांकerrupt might have fired and be on its way to the
		 * host queue जबतक we mask it, and अगर we unmask it
		 * early enough (re-cede right away), there is a
		 * theorical possibility that it fires again, thus
		 * landing in the target queue more than once which is
		 * a big no-no.
		 *
		 * Fortunately, solving this is rather easy. If the
		 * above load setting PQ to 01 वापसs a previous
		 * value where P is set, then we know the escalation
		 * पूर्णांकerrupt is somewhere on its way to the host. In
		 * that हाल we simply करोn't clear the xive_esc_on
		 * flag below. It will be eventually cleared by the
		 * handler क्रम the escalation पूर्णांकerrupt.
		 *
		 * Then, when करोing a cede, we check that flag again
		 * beक्रमe re-enabling the escalation पूर्णांकerrupt, and अगर
		 * set, we पात the cede.
		 */
		अगर (!(pq & XIVE_ESB_VAL_P))
			/* Now P is 0, we can clear the flag */
			vcpu->arch.xive_esc_on = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_xive_push_vcpu);

/*
 * This is a simple trigger क्रम a generic XIVE IRQ. This must
 * only be called क्रम पूर्णांकerrupts that support a trigger page
 */
अटल bool xive_irq_trigger(काष्ठा xive_irq_data *xd)
अणु
	/* This should be only क्रम MSIs */
	अगर (WARN_ON(xd->flags & XIVE_IRQ_FLAG_LSI))
		वापस false;

	/* Those पूर्णांकerrupts should always have a trigger page */
	अगर (WARN_ON(!xd->trig_mmio))
		वापस false;

	out_be64(xd->trig_mmio, 0);

	वापस true;
पूर्ण

अटल irqवापस_t xive_esc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा kvm_vcpu *vcpu = data;

	vcpu->arch.irq_pending = 1;
	smp_mb();
	अगर (vcpu->arch.ceded)
		kvmppc_fast_vcpu_kick(vcpu);

	/* Since we have the no-EOI flag, the पूर्णांकerrupt is effectively
	 * disabled now. Clearing xive_esc_on means we won't bother
	 * करोing so on the next entry.
	 *
	 * This also allows the entry code to know that अगर a PQ combination
	 * of 10 is observed जबतक xive_esc_on is true, it means the queue
	 * contains an unprocessed escalation पूर्णांकerrupt. We करोn't make use of
	 * that knowledge today but might (see comment in book3s_hv_rmhandler.S)
	 */
	vcpu->arch.xive_esc_on = false;

	/* This orders xive_esc_on = false vs. subsequent stale_p = true */
	smp_wmb();	/* goes with smp_mb() in cleanup_single_escalation */

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक kvmppc_xive_attach_escalation(काष्ठा kvm_vcpu *vcpu, u8 prio,
				  bool single_escalation)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा xive_q *q = &xc->queues[prio];
	अक्षर *name = शून्य;
	पूर्णांक rc;

	/* Alपढ़ोy there ? */
	अगर (xc->esc_virq[prio])
		वापस 0;

	/* Hook up the escalation पूर्णांकerrupt */
	xc->esc_virq[prio] = irq_create_mapping(शून्य, q->esc_irq);
	अगर (!xc->esc_virq[prio]) अणु
		pr_err("Failed to map escalation interrupt for queue %d of VCPU %d\n",
		       prio, xc->server_num);
		वापस -EIO;
	पूर्ण

	अगर (single_escalation)
		name = kaप्र_लिखो(GFP_KERNEL, "kvm-%d-%d",
				 vcpu->kvm->arch.lpid, xc->server_num);
	अन्यथा
		name = kaप्र_लिखो(GFP_KERNEL, "kvm-%d-%d-%d",
				 vcpu->kvm->arch.lpid, xc->server_num, prio);
	अगर (!name) अणु
		pr_err("Failed to allocate escalation irq name for queue %d of VCPU %d\n",
		       prio, xc->server_num);
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

	pr_devel("Escalation %s irq %d (prio %d)\n", name, xc->esc_virq[prio], prio);

	rc = request_irq(xc->esc_virq[prio], xive_esc_irq,
			 IRQF_NO_THREAD, name, vcpu);
	अगर (rc) अणु
		pr_err("Failed to request escalation interrupt for queue %d of VCPU %d\n",
		       prio, xc->server_num);
		जाओ error;
	पूर्ण
	xc->esc_virq_names[prio] = name;

	/* In single escalation mode, we grab the ESB MMIO of the
	 * पूर्णांकerrupt and mask it. Also populate the VCPU v/raddr
	 * of the ESB page क्रम use by यंत्र entry/निकास code. Finally
	 * set the XIVE_IRQ_FLAG_NO_EOI flag which will prevent the
	 * core code from perक्रमming an EOI on the escalation
	 * पूर्णांकerrupt, thus leaving it effectively masked after
	 * it fires once.
	 */
	अगर (single_escalation) अणु
		काष्ठा irq_data *d = irq_get_irq_data(xc->esc_virq[prio]);
		काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);

		xive_vm_esb_load(xd, XIVE_ESB_SET_PQ_01);
		vcpu->arch.xive_esc_raddr = xd->eoi_page;
		vcpu->arch.xive_esc_vaddr = (__क्रमce u64)xd->eoi_mmio;
		xd->flags |= XIVE_IRQ_FLAG_NO_EOI;
	पूर्ण

	वापस 0;
error:
	irq_dispose_mapping(xc->esc_virq[prio]);
	xc->esc_virq[prio] = 0;
	kमुक्त(name);
	वापस rc;
पूर्ण

अटल पूर्णांक xive_provision_queue(काष्ठा kvm_vcpu *vcpu, u8 prio)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा kvmppc_xive *xive = xc->xive;
	काष्ठा xive_q *q =  &xc->queues[prio];
	व्योम *qpage;
	पूर्णांक rc;

	अगर (WARN_ON(q->qpage))
		वापस 0;

	/* Allocate the queue and retrieve infos on current node क्रम now */
	qpage = (__be32 *)__get_मुक्त_pages(GFP_KERNEL, xive->q_page_order);
	अगर (!qpage) अणु
		pr_err("Failed to allocate queue %d for VCPU %d\n",
		       prio, xc->server_num);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(qpage, 0, 1 << xive->q_order);

	/*
	 * Reconfigure the queue. This will set q->qpage only once the
	 * queue is fully configured. This is a requirement क्रम prio 0
	 * as we will stop करोing EOIs क्रम every IPI as soon as we observe
	 * qpage being non-शून्य, and instead will only EOI when we receive
	 * corresponding queue 0 entries
	 */
	rc = xive_native_configure_queue(xc->vp_id, q, prio, qpage,
					 xive->q_order, true);
	अगर (rc)
		pr_err("Failed to configure queue %d for VCPU %d\n",
		       prio, xc->server_num);
	वापस rc;
पूर्ण

/* Called with xive->lock held */
अटल पूर्णांक xive_check_provisioning(काष्ठा kvm *kvm, u8 prio)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i, rc;

	lockdep_निश्चित_held(&xive->lock);

	/* Alपढ़ोy provisioned ? */
	अगर (xive->qmap & (1 << prio))
		वापस 0;

	pr_devel("Provisioning prio... %d\n", prio);

	/* Provision each VCPU and enable escalations अगर needed */
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (!vcpu->arch.xive_vcpu)
			जारी;
		rc = xive_provision_queue(vcpu, prio);
		अगर (rc == 0 && !xive->single_escalation)
			kvmppc_xive_attach_escalation(vcpu, prio,
						      xive->single_escalation);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* Order previous stores and mark it as provisioned */
	mb();
	xive->qmap |= (1 << prio);
	वापस 0;
पूर्ण

अटल व्योम xive_inc_q_pending(काष्ठा kvm *kvm, u32 server, u8 prio)
अणु
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा kvmppc_xive_vcpu *xc;
	काष्ठा xive_q *q;

	/* Locate target server */
	vcpu = kvmppc_xive_find_server(kvm, server);
	अगर (!vcpu) अणु
		pr_warn("%s: Can't find server %d\n", __func__, server);
		वापस;
	पूर्ण
	xc = vcpu->arch.xive_vcpu;
	अगर (WARN_ON(!xc))
		वापस;

	q = &xc->queues[prio];
	atomic_inc(&q->pending_count);
पूर्ण

अटल पूर्णांक xive_try_pick_queue(काष्ठा kvm_vcpu *vcpu, u8 prio)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा xive_q *q;
	u32 max;

	अगर (WARN_ON(!xc))
		वापस -ENXIO;
	अगर (!xc->valid)
		वापस -ENXIO;

	q = &xc->queues[prio];
	अगर (WARN_ON(!q->qpage))
		वापस -ENXIO;

	/* Calculate max number of पूर्णांकerrupts in that queue. */
	max = (q->msk + 1) - XIVE_Q_GAP;
	वापस atomic_add_unless(&q->count, 1, max) ? 0 : -EBUSY;
पूर्ण

पूर्णांक kvmppc_xive_select_target(काष्ठा kvm *kvm, u32 *server, u8 prio)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i, rc;

	/* Locate target server */
	vcpu = kvmppc_xive_find_server(kvm, *server);
	अगर (!vcpu) अणु
		pr_devel("Can't find server %d\n", *server);
		वापस -EINVAL;
	पूर्ण

	pr_devel("Finding irq target on 0x%x/%d...\n", *server, prio);

	/* Try pick it */
	rc = xive_try_pick_queue(vcpu, prio);
	अगर (rc == 0)
		वापस rc;

	pr_devel(" .. failed, looking up candidate...\n");

	/* Failed, pick another VCPU */
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (!vcpu->arch.xive_vcpu)
			जारी;
		rc = xive_try_pick_queue(vcpu, prio);
		अगर (rc == 0) अणु
			*server = vcpu->arch.xive_vcpu->server_num;
			pr_devel("  found on 0x%x/%d\n", *server, prio);
			वापस rc;
		पूर्ण
	पूर्ण
	pr_devel("  no available target !\n");

	/* No available target ! */
	वापस -EBUSY;
पूर्ण

अटल u8 xive_lock_and_mask(काष्ठा kvmppc_xive *xive,
			     काष्ठा kvmppc_xive_src_block *sb,
			     काष्ठा kvmppc_xive_irq_state *state)
अणु
	काष्ठा xive_irq_data *xd;
	u32 hw_num;
	u8 old_prio;
	u64 val;

	/*
	 * Take the lock, set masked, try again अगर racing
	 * with H_EOI
	 */
	क्रम (;;) अणु
		arch_spin_lock(&sb->lock);
		old_prio = state->guest_priority;
		state->guest_priority = MASKED;
		mb();
		अगर (!state->in_eoi)
			अवरोध;
		state->guest_priority = old_prio;
		arch_spin_unlock(&sb->lock);
	पूर्ण

	/* No change ? Bail */
	अगर (old_prio == MASKED)
		वापस old_prio;

	/* Get the right irq */
	kvmppc_xive_select_irq(state, &hw_num, &xd);

	/* Set PQ to 10, वापस old P and old Q and remember them */
	val = xive_vm_esb_load(xd, XIVE_ESB_SET_PQ_10);
	state->old_p = !!(val & 2);
	state->old_q = !!(val & 1);

	/*
	 * Synchronize hardware to sensure the queues are updated when
	 * masking
	 */
	xive_native_sync_source(hw_num);

	वापस old_prio;
पूर्ण

अटल व्योम xive_lock_क्रम_unmask(काष्ठा kvmppc_xive_src_block *sb,
				 काष्ठा kvmppc_xive_irq_state *state)
अणु
	/*
	 * Take the lock try again अगर racing with H_EOI
	 */
	क्रम (;;) अणु
		arch_spin_lock(&sb->lock);
		अगर (!state->in_eoi)
			अवरोध;
		arch_spin_unlock(&sb->lock);
	पूर्ण
पूर्ण

अटल व्योम xive_finish_unmask(काष्ठा kvmppc_xive *xive,
			       काष्ठा kvmppc_xive_src_block *sb,
			       काष्ठा kvmppc_xive_irq_state *state,
			       u8 prio)
अणु
	काष्ठा xive_irq_data *xd;
	u32 hw_num;

	/* If we aren't changing a thing, move on */
	अगर (state->guest_priority != MASKED)
		जाओ bail;

	/* Get the right irq */
	kvmppc_xive_select_irq(state, &hw_num, &xd);

	/* Old Q set, set PQ to 11 */
	अगर (state->old_q)
		xive_vm_esb_load(xd, XIVE_ESB_SET_PQ_11);

	/*
	 * If not old P, then perक्रमm an "effective" EOI,
	 * on the source. This will handle the हालs where
	 * FW EOI is needed.
	 */
	अगर (!state->old_p)
		xive_vm_source_eoi(hw_num, xd);

	/* Synchronize ordering and mark unmasked */
	mb();
bail:
	state->guest_priority = prio;
पूर्ण

/*
 * Target an पूर्णांकerrupt to a given server/prio, this will fallback
 * to another server अगर necessary and perक्रमm the HW targetting
 * updates as needed
 *
 * NOTE: Must be called with the state lock held
 */
अटल पूर्णांक xive_target_पूर्णांकerrupt(काष्ठा kvm *kvm,
				 काष्ठा kvmppc_xive_irq_state *state,
				 u32 server, u8 prio)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	u32 hw_num;
	पूर्णांक rc;

	/*
	 * This will वापस a tentative server and actual
	 * priority. The count क्रम that new target will have
	 * alपढ़ोy been incremented.
	 */
	rc = kvmppc_xive_select_target(kvm, &server, prio);

	/*
	 * We failed to find a target ? Not much we can करो
	 * at least until we support the GIQ.
	 */
	अगर (rc)
		वापस rc;

	/*
	 * Increment the old queue pending count अगर there
	 * was one so that the old queue count माला_लो adjusted later
	 * when observed to be empty.
	 */
	अगर (state->act_priority != MASKED)
		xive_inc_q_pending(kvm,
				   state->act_server,
				   state->act_priority);
	/*
	 * Update state and HW
	 */
	state->act_priority = prio;
	state->act_server = server;

	/* Get the right irq */
	kvmppc_xive_select_irq(state, &hw_num, शून्य);

	वापस xive_native_configure_irq(hw_num,
					 kvmppc_xive_vp(xive, server),
					 prio, state->number);
पूर्ण

/*
 * Targetting rules: In order to aव्योम losing track of
 * pending पूर्णांकerrupts accross mask and unmask, which would
 * allow queue overflows, we implement the following rules:
 *
 *  - Unless it was never enabled (or we run out of capacity)
 *    an पूर्णांकerrupt is always targetted at a valid server/queue
 *    pair even when "masked" by the guest. This pair tends to
 *    be the last one used but it can be changed under some
 *    circumstances. That allows us to separate targetting
 *    from masking, we only handle accounting during (re)targetting,
 *    this also allows us to let an पूर्णांकerrupt drain पूर्णांकo its target
 *    queue after masking, aव्योमing complex schemes to हटाओ
 *    पूर्णांकerrupts out of remote processor queues.
 *
 *  - When masking, we set PQ to 10 and save the previous value
 *    of P and Q.
 *
 *  - When unmasking, अगर saved Q was set, we set PQ to 11
 *    otherwise we leave PQ to the HW state which will be either
 *    10 अगर nothing happened or 11 अगर the पूर्णांकerrupt fired जबतक
 *    masked. Effectively we are OR'ing the previous Q पूर्णांकo the
 *    HW Q.
 *
 *    Then अगर saved P is clear, we करो an effective EOI (Q->P->Trigger)
 *    which will unmask the पूर्णांकerrupt and shoot a new one अगर Q was
 *    set.
 *
 *    Otherwise (saved P is set) we leave PQ unchanged (so 10 or 11,
 *    effectively meaning an H_EOI from the guest is still expected
 *    क्रम that पूर्णांकerrupt).
 *
 *  - If H_EOI occurs जबतक masked, we clear the saved P.
 *
 *  - When changing target, we account on the new target and
 *    increment a separate "pending" counter on the old one.
 *    This pending counter will be used to decrement the old
 *    target's count when its queue has been observed empty.
 */

पूर्णांक kvmppc_xive_set_xive(काष्ठा kvm *kvm, u32 irq, u32 server,
			 u32 priority)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u8 new_act_prio;
	पूर्णांक rc = 0;
	u16 idx;

	अगर (!xive)
		वापस -ENODEV;

	pr_devel("set_xive ! irq 0x%x server 0x%x prio %d\n",
		 irq, server, priority);

	/* First, check provisioning of queues */
	अगर (priority != MASKED) अणु
		mutex_lock(&xive->lock);
		rc = xive_check_provisioning(xive->kvm,
			      xive_prio_from_guest(priority));
		mutex_unlock(&xive->lock);
	पूर्ण
	अगर (rc) अणु
		pr_devel("  provisioning failure %d !\n", rc);
		वापस rc;
	पूर्ण

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb)
		वापस -EINVAL;
	state = &sb->irq_state[idx];

	/*
	 * We first handle masking/unmasking since the locking
	 * might need to be retried due to EOIs, we'll handle
	 * targetting changes later. These functions will वापस
	 * with the SB lock held.
	 *
	 * xive_lock_and_mask() will also set state->guest_priority
	 * but won't otherwise change other fields of the state.
	 *
	 * xive_lock_क्रम_unmask will not actually unmask, this will
	 * be करोne later by xive_finish_unmask() once the targetting
	 * has been करोne, so we करोn't try to unmask an पूर्णांकerrupt
	 * that hasn't yet been targetted.
	 */
	अगर (priority == MASKED)
		xive_lock_and_mask(xive, sb, state);
	अन्यथा
		xive_lock_क्रम_unmask(sb, state);


	/*
	 * Then we handle targetting.
	 *
	 * First calculate a new "actual priority"
	 */
	new_act_prio = state->act_priority;
	अगर (priority != MASKED)
		new_act_prio = xive_prio_from_guest(priority);

	pr_devel(" new_act_prio=%x act_server=%x act_prio=%x\n",
		 new_act_prio, state->act_server, state->act_priority);

	/*
	 * Then check अगर we actually need to change anything,
	 *
	 * The condition क्रम re-targetting the पूर्णांकerrupt is that
	 * we have a valid new priority (new_act_prio is not 0xff)
	 * and either the server or the priority changed.
	 *
	 * Note: If act_priority was ff and the new priority is
	 *       also ff, we करोn't करो anything and leave the पूर्णांकerrupt
	 *       untargetted. An attempt of करोing an पूर्णांक_on on an
	 *       untargetted पूर्णांकerrupt will fail. If that is a problem
	 *       we could initialize पूर्णांकerrupts with valid शेष
	 */

	अगर (new_act_prio != MASKED &&
	    (state->act_server != server ||
	     state->act_priority != new_act_prio))
		rc = xive_target_पूर्णांकerrupt(kvm, state, server, new_act_prio);

	/*
	 * Perक्रमm the final unmasking of the पूर्णांकerrupt source
	 * अगर necessary
	 */
	अगर (priority != MASKED)
		xive_finish_unmask(xive, sb, state, priority);

	/*
	 * Finally Update saved_priority to match. Only पूर्णांक_on/off
	 * set this field to a dअगरferent value.
	 */
	state->saved_priority = priority;

	arch_spin_unlock(&sb->lock);
	वापस rc;
पूर्ण

पूर्णांक kvmppc_xive_get_xive(काष्ठा kvm *kvm, u32 irq, u32 *server,
			 u32 *priority)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u16 idx;

	अगर (!xive)
		वापस -ENODEV;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb)
		वापस -EINVAL;
	state = &sb->irq_state[idx];
	arch_spin_lock(&sb->lock);
	*server = state->act_server;
	*priority = state->guest_priority;
	arch_spin_unlock(&sb->lock);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xive_पूर्णांक_on(काष्ठा kvm *kvm, u32 irq)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u16 idx;

	अगर (!xive)
		वापस -ENODEV;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb)
		वापस -EINVAL;
	state = &sb->irq_state[idx];

	pr_devel("int_on(irq=0x%x)\n", irq);

	/*
	 * Check अगर पूर्णांकerrupt was not targetted
	 */
	अगर (state->act_priority == MASKED) अणु
		pr_devel("int_on on untargetted interrupt\n");
		वापस -EINVAL;
	पूर्ण

	/* If saved_priority is 0xff, करो nothing */
	अगर (state->saved_priority == MASKED)
		वापस 0;

	/*
	 * Lock and unmask it.
	 */
	xive_lock_क्रम_unmask(sb, state);
	xive_finish_unmask(xive, sb, state, state->saved_priority);
	arch_spin_unlock(&sb->lock);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xive_पूर्णांक_off(काष्ठा kvm *kvm, u32 irq)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u16 idx;

	अगर (!xive)
		वापस -ENODEV;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb)
		वापस -EINVAL;
	state = &sb->irq_state[idx];

	pr_devel("int_off(irq=0x%x)\n", irq);

	/*
	 * Lock and mask
	 */
	state->saved_priority = xive_lock_and_mask(xive, sb, state);
	arch_spin_unlock(&sb->lock);

	वापस 0;
पूर्ण

अटल bool xive_restore_pending_irq(काष्ठा kvmppc_xive *xive, u32 irq)
अणु
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u16 idx;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb)
		वापस false;
	state = &sb->irq_state[idx];
	अगर (!state->valid)
		वापस false;

	/*
	 * Trigger the IPI. This assumes we never restore a pass-through
	 * पूर्णांकerrupt which should be safe enough
	 */
	xive_irq_trigger(&state->ipi_data);

	वापस true;
पूर्ण

u64 kvmppc_xive_get_icp(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;

	अगर (!xc)
		वापस 0;

	/* Return the per-cpu state क्रम state saving/migration */
	वापस (u64)xc->cppr << KVM_REG_PPC_ICP_CPPR_SHIFT |
	       (u64)xc->mfrr << KVM_REG_PPC_ICP_MFRR_SHIFT |
	       (u64)0xff << KVM_REG_PPC_ICP_PPRI_SHIFT;
पूर्ण

पूर्णांक kvmppc_xive_set_icp(काष्ठा kvm_vcpu *vcpu, u64 icpval)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा kvmppc_xive *xive = vcpu->kvm->arch.xive;
	u8 cppr, mfrr;
	u32 xisr;

	अगर (!xc || !xive)
		वापस -ENOENT;

	/* Grab inभागidual state fields. We करोn't use pending_pri */
	cppr = icpval >> KVM_REG_PPC_ICP_CPPR_SHIFT;
	xisr = (icpval >> KVM_REG_PPC_ICP_XISR_SHIFT) &
		KVM_REG_PPC_ICP_XISR_MASK;
	mfrr = icpval >> KVM_REG_PPC_ICP_MFRR_SHIFT;

	pr_devel("set_icp vcpu %d cppr=0x%x mfrr=0x%x xisr=0x%x\n",
		 xc->server_num, cppr, mfrr, xisr);

	/*
	 * We can't update the state of a "pushed" VCPU, but that
	 * shouldn't happen because the vcpu->mutex makes running a
	 * vcpu mutually exclusive with करोing one_reg get/set on it.
	 */
	अगर (WARN_ON(vcpu->arch.xive_pushed))
		वापस -EIO;

	/* Update VCPU HW saved state */
	vcpu->arch.xive_saved_state.cppr = cppr;
	xc->hw_cppr = xc->cppr = cppr;

	/*
	 * Update MFRR state. If it's not 0xff, we mark the VCPU as
	 * having a pending MFRR change, which will re-evaluate the
	 * target. The VCPU will thus potentially get a spurious
	 * पूर्णांकerrupt but that's not a big deal.
	 */
	xc->mfrr = mfrr;
	अगर (mfrr < cppr)
		xive_irq_trigger(&xc->vp_ipi_data);

	/*
	 * Now saved XIRR is "interesting". It means there's something in
	 * the legacy "1 element" queue... क्रम an IPI we simply ignore it,
	 * as the MFRR restore will handle that. For anything अन्यथा we need
	 * to क्रमce a resend of the source.
	 * However the source may not have been setup yet. If that's the
	 * हाल, we keep that info and increment a counter in the xive to
	 * tell subsequent xive_set_source() to go look.
	 */
	अगर (xisr > XICS_IPI && !xive_restore_pending_irq(xive, xisr)) अणु
		xc->delayed_irq = xisr;
		xive->delayed_irqs++;
		pr_devel("  xisr restore delayed\n");
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xive_set_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ guest_irq,
			   काष्ठा irq_desc *host_desc)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	काष्ठा irq_data *host_data = irq_desc_get_irq_data(host_desc);
	अचिन्हित पूर्णांक host_irq = irq_desc_get_irq(host_desc);
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(host_data);
	u16 idx;
	u8 prio;
	पूर्णांक rc;

	अगर (!xive)
		वापस -ENODEV;

	pr_devel("set_mapped girq 0x%lx host HW irq 0x%x...\n",guest_irq, hw_irq);

	sb = kvmppc_xive_find_source(xive, guest_irq, &idx);
	अगर (!sb)
		वापस -EINVAL;
	state = &sb->irq_state[idx];

	/*
	 * Mark the passed-through पूर्णांकerrupt as going to a VCPU,
	 * this will prevent further EOIs and similar operations
	 * from the XIVE code. It will also mask the पूर्णांकerrupt
	 * to either PQ=10 or 11 state, the latter अगर the पूर्णांकerrupt
	 * is pending. This will allow us to unmask or retrigger it
	 * after routing it to the guest with a simple EOI.
	 *
	 * The "state" argument is a "token", all it needs is to be
	 * non-शून्य to चयन to passed-through or शून्य क्रम the
	 * other way around. We may not yet have an actual VCPU
	 * target here and we करोn't really care.
	 */
	rc = irq_set_vcpu_affinity(host_irq, state);
	अगर (rc) अणु
		pr_err("Failed to set VCPU affinity for irq %d\n", host_irq);
		वापस rc;
	पूर्ण

	/*
	 * Mask and पढ़ो state of IPI. We need to know अगर its P bit
	 * is set as that means it's potentially alपढ़ोy using a
	 * queue entry in the target
	 */
	prio = xive_lock_and_mask(xive, sb, state);
	pr_devel(" old IPI prio %02x P:%d Q:%d\n", prio,
		 state->old_p, state->old_q);

	/* Turn the IPI hard off */
	xive_vm_esb_load(&state->ipi_data, XIVE_ESB_SET_PQ_01);

	/*
	 * Reset ESB guest mapping. Needed when ESB pages are exposed
	 * to the guest in XIVE native mode
	 */
	अगर (xive->ops && xive->ops->reset_mapped)
		xive->ops->reset_mapped(kvm, guest_irq);

	/* Grab info about irq */
	state->pt_number = hw_irq;
	state->pt_data = irq_data_get_irq_handler_data(host_data);

	/*
	 * Configure the IRQ to match the existing configuration of
	 * the IPI अगर it was alपढ़ोy targetted. Otherwise this will
	 * mask the पूर्णांकerrupt in a lossy way (act_priority is 0xff)
	 * which is fine क्रम a never started पूर्णांकerrupt.
	 */
	xive_native_configure_irq(hw_irq,
				  kvmppc_xive_vp(xive, state->act_server),
				  state->act_priority, state->number);

	/*
	 * We करो an EOI to enable the पूर्णांकerrupt (and retrigger अगर needed)
	 * अगर the guest has the पूर्णांकerrupt unmasked and the P bit was *not*
	 * set in the IPI. If it was set, we know a slot may still be in
	 * use in the target queue thus we have to रुको क्रम a guest
	 * originated EOI
	 */
	अगर (prio != MASKED && !state->old_p)
		xive_vm_source_eoi(hw_irq, state->pt_data);

	/* Clear old_p/old_q as they are no दीर्घer relevant */
	state->old_p = state->old_q = false;

	/* Restore guest prio (unlocks EOI) */
	mb();
	state->guest_priority = prio;
	arch_spin_unlock(&sb->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_xive_set_mapped);

पूर्णांक kvmppc_xive_clr_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ guest_irq,
			   काष्ठा irq_desc *host_desc)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	अचिन्हित पूर्णांक host_irq = irq_desc_get_irq(host_desc);
	u16 idx;
	u8 prio;
	पूर्णांक rc;

	अगर (!xive)
		वापस -ENODEV;

	pr_devel("clr_mapped girq 0x%lx...\n", guest_irq);

	sb = kvmppc_xive_find_source(xive, guest_irq, &idx);
	अगर (!sb)
		वापस -EINVAL;
	state = &sb->irq_state[idx];

	/*
	 * Mask and पढ़ो state of IRQ. We need to know अगर its P bit
	 * is set as that means it's potentially alपढ़ोy using a
	 * queue entry in the target
	 */
	prio = xive_lock_and_mask(xive, sb, state);
	pr_devel(" old IRQ prio %02x P:%d Q:%d\n", prio,
		 state->old_p, state->old_q);

	/*
	 * If old_p is set, the पूर्णांकerrupt is pending, we चयन it to
	 * PQ=11. This will क्रमce a resend in the host so the पूर्णांकerrupt
	 * isn't lost to whatver host driver may pick it up
	 */
	अगर (state->old_p)
		xive_vm_esb_load(state->pt_data, XIVE_ESB_SET_PQ_11);

	/* Release the passed-through पूर्णांकerrupt to the host */
	rc = irq_set_vcpu_affinity(host_irq, शून्य);
	अगर (rc) अणु
		pr_err("Failed to clr VCPU affinity for irq %d\n", host_irq);
		वापस rc;
	पूर्ण

	/* Forget about the IRQ */
	state->pt_number = 0;
	state->pt_data = शून्य;

	/*
	 * Reset ESB guest mapping. Needed when ESB pages are exposed
	 * to the guest in XIVE native mode
	 */
	अगर (xive->ops && xive->ops->reset_mapped) अणु
		xive->ops->reset_mapped(kvm, guest_irq);
	पूर्ण

	/* Reconfigure the IPI */
	xive_native_configure_irq(state->ipi_number,
				  kvmppc_xive_vp(xive, state->act_server),
				  state->act_priority, state->number);

	/*
	 * If old_p is set (we have a queue entry potentially
	 * occupied) or the पूर्णांकerrupt is masked, we set the IPI
	 * to PQ=10 state. Otherwise we just re-enable it (PQ=00).
	 */
	अगर (prio == MASKED || state->old_p)
		xive_vm_esb_load(&state->ipi_data, XIVE_ESB_SET_PQ_10);
	अन्यथा
		xive_vm_esb_load(&state->ipi_data, XIVE_ESB_SET_PQ_00);

	/* Restore guest prio (unlocks EOI) */
	mb();
	state->guest_priority = prio;
	arch_spin_unlock(&sb->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_xive_clr_mapped);

व्योम kvmppc_xive_disable_vcpu_पूर्णांकerrupts(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	पूर्णांक i, j;

	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		काष्ठा kvmppc_xive_src_block *sb = xive->src_blocks[i];

		अगर (!sb)
			जारी;
		क्रम (j = 0; j < KVMPPC_XICS_IRQ_PER_ICS; j++) अणु
			काष्ठा kvmppc_xive_irq_state *state = &sb->irq_state[j];

			अगर (!state->valid)
				जारी;
			अगर (state->act_priority == MASKED)
				जारी;
			अगर (state->act_server != xc->server_num)
				जारी;

			/* Clean it up */
			arch_spin_lock(&sb->lock);
			state->act_priority = MASKED;
			xive_vm_esb_load(&state->ipi_data, XIVE_ESB_SET_PQ_01);
			xive_native_configure_irq(state->ipi_number, 0, MASKED, 0);
			अगर (state->pt_number) अणु
				xive_vm_esb_load(state->pt_data, XIVE_ESB_SET_PQ_01);
				xive_native_configure_irq(state->pt_number, 0, MASKED, 0);
			पूर्ण
			arch_spin_unlock(&sb->lock);
		पूर्ण
	पूर्ण

	/* Disable vcpu's escalation पूर्णांकerrupt */
	अगर (vcpu->arch.xive_esc_on) अणु
		__raw_पढ़ोq((व्योम __iomem *)(vcpu->arch.xive_esc_vaddr +
					     XIVE_ESB_SET_PQ_01));
		vcpu->arch.xive_esc_on = false;
	पूर्ण

	/*
	 * Clear poपूर्णांकers to escalation पूर्णांकerrupt ESB.
	 * This is safe because the vcpu->mutex is held, preventing
	 * any other CPU from concurrently executing a KVM_RUN ioctl.
	 */
	vcpu->arch.xive_esc_vaddr = 0;
	vcpu->arch.xive_esc_raddr = 0;
पूर्ण

/*
 * In single escalation mode, the escalation पूर्णांकerrupt is marked so
 * that EOI करोesn't re-enable it, but just sets the stale_p flag to
 * indicate that the P bit has alपढ़ोy been dealt with.  However, the
 * assembly code that enters the guest sets PQ to 00 without clearing
 * stale_p (because it has no easy way to address it).  Hence we have
 * to adjust stale_p beक्रमe shutting करोwn the पूर्णांकerrupt.
 */
व्योम xive_cleanup_single_escalation(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvmppc_xive_vcpu *xc, पूर्णांक irq)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(irq);
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);

	/*
	 * This slightly odd sequence gives the right result
	 * (i.e. stale_p set अगर xive_esc_on is false) even अगर
	 * we race with xive_esc_irq() and xive_irq_eoi().
	 */
	xd->stale_p = false;
	smp_mb();		/* paired with smb_wmb in xive_esc_irq */
	अगर (!vcpu->arch.xive_esc_on)
		xd->stale_p = true;
पूर्ण

व्योम kvmppc_xive_cleanup_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा kvmppc_xive *xive = vcpu->kvm->arch.xive;
	पूर्णांक i;

	अगर (!kvmppc_xics_enabled(vcpu))
		वापस;

	अगर (!xc)
		वापस;

	pr_devel("cleanup_vcpu(cpu=%d)\n", xc->server_num);

	/* Ensure no पूर्णांकerrupt is still routed to that VP */
	xc->valid = false;
	kvmppc_xive_disable_vcpu_पूर्णांकerrupts(vcpu);

	/* Mask the VP IPI */
	xive_vm_esb_load(&xc->vp_ipi_data, XIVE_ESB_SET_PQ_01);

	/* Free escalations */
	क्रम (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) अणु
		अगर (xc->esc_virq[i]) अणु
			अगर (xc->xive->single_escalation)
				xive_cleanup_single_escalation(vcpu, xc,
							xc->esc_virq[i]);
			मुक्त_irq(xc->esc_virq[i], vcpu);
			irq_dispose_mapping(xc->esc_virq[i]);
			kमुक्त(xc->esc_virq_names[i]);
		पूर्ण
	पूर्ण

	/* Disable the VP */
	xive_native_disable_vp(xc->vp_id);

	/* Clear the cam word so guest entry won't try to push context */
	vcpu->arch.xive_cam_word = 0;

	/* Free the queues */
	क्रम (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) अणु
		काष्ठा xive_q *q = &xc->queues[i];

		xive_native_disable_queue(xc->vp_id, q, i);
		अगर (q->qpage) अणु
			मुक्त_pages((अचिन्हित दीर्घ)q->qpage,
				   xive->q_page_order);
			q->qpage = शून्य;
		पूर्ण
	पूर्ण

	/* Free the IPI */
	अगर (xc->vp_ipi) अणु
		xive_cleanup_irq_data(&xc->vp_ipi_data);
		xive_native_मुक्त_irq(xc->vp_ipi);
	पूर्ण
	/* Free the VP */
	kमुक्त(xc);

	/* Cleanup the vcpu */
	vcpu->arch.irq_type = KVMPPC_IRQ_DEFAULT;
	vcpu->arch.xive_vcpu = शून्य;
पूर्ण

अटल bool kvmppc_xive_vcpu_id_valid(काष्ठा kvmppc_xive *xive, u32 cpu)
अणु
	/* We have a block of xive->nr_servers VPs. We just need to check
	 * packed vCPU ids are below that.
	 */
	वापस kvmppc_pack_vcpu_id(xive->kvm, cpu) < xive->nr_servers;
पूर्ण

पूर्णांक kvmppc_xive_compute_vp_id(काष्ठा kvmppc_xive *xive, u32 cpu, u32 *vp)
अणु
	u32 vp_id;

	अगर (!kvmppc_xive_vcpu_id_valid(xive, cpu)) अणु
		pr_devel("Out of bounds !\n");
		वापस -EINVAL;
	पूर्ण

	अगर (xive->vp_base == XIVE_INVALID_VP) अणु
		xive->vp_base = xive_native_alloc_vp_block(xive->nr_servers);
		pr_devel("VP_Base=%x nr_servers=%d\n", xive->vp_base, xive->nr_servers);

		अगर (xive->vp_base == XIVE_INVALID_VP)
			वापस -ENOSPC;
	पूर्ण

	vp_id = kvmppc_xive_vp(xive, cpu);
	अगर (kvmppc_xive_vp_in_use(xive->kvm, vp_id)) अणु
		pr_devel("Duplicate !\n");
		वापस -EEXIST;
	पूर्ण

	*vp = vp_id;

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xive_connect_vcpu(काष्ठा kvm_device *dev,
			     काष्ठा kvm_vcpu *vcpu, u32 cpu)
अणु
	काष्ठा kvmppc_xive *xive = dev->निजी;
	काष्ठा kvmppc_xive_vcpu *xc;
	पूर्णांक i, r = -EBUSY;
	u32 vp_id;

	pr_devel("connect_vcpu(cpu=%d)\n", cpu);

	अगर (dev->ops != &kvm_xive_ops) अणु
		pr_devel("Wrong ops !\n");
		वापस -EPERM;
	पूर्ण
	अगर (xive->kvm != vcpu->kvm)
		वापस -EPERM;
	अगर (vcpu->arch.irq_type != KVMPPC_IRQ_DEFAULT)
		वापस -EBUSY;

	/* We need to synchronize with queue provisioning */
	mutex_lock(&xive->lock);

	r = kvmppc_xive_compute_vp_id(xive, cpu, &vp_id);
	अगर (r)
		जाओ bail;

	xc = kzalloc(माप(*xc), GFP_KERNEL);
	अगर (!xc) अणु
		r = -ENOMEM;
		जाओ bail;
	पूर्ण

	vcpu->arch.xive_vcpu = xc;
	xc->xive = xive;
	xc->vcpu = vcpu;
	xc->server_num = cpu;
	xc->vp_id = vp_id;
	xc->mfrr = 0xff;
	xc->valid = true;

	r = xive_native_get_vp_info(xc->vp_id, &xc->vp_cam, &xc->vp_chip_id);
	अगर (r)
		जाओ bail;

	/* Configure VCPU fields क्रम use by assembly push/pull */
	vcpu->arch.xive_saved_state.w01 = cpu_to_be64(0xff000000);
	vcpu->arch.xive_cam_word = cpu_to_be32(xc->vp_cam | TM_QW1W2_VO);

	/* Allocate IPI */
	xc->vp_ipi = xive_native_alloc_irq();
	अगर (!xc->vp_ipi) अणु
		pr_err("Failed to allocate xive irq for VCPU IPI\n");
		r = -EIO;
		जाओ bail;
	पूर्ण
	pr_devel(" IPI=0x%x\n", xc->vp_ipi);

	r = xive_native_populate_irq_data(xc->vp_ipi, &xc->vp_ipi_data);
	अगर (r)
		जाओ bail;

	/*
	 * Enable the VP first as the single escalation mode will
	 * affect escalation पूर्णांकerrupts numbering
	 */
	r = xive_native_enable_vp(xc->vp_id, xive->single_escalation);
	अगर (r) अणु
		pr_err("Failed to enable VP in OPAL, err %d\n", r);
		जाओ bail;
	पूर्ण

	/*
	 * Initialize queues. Initially we set them all क्रम no queueing
	 * and we enable escalation क्रम queue 0 only which we'll use क्रम
	 * our mfrr change notअगरications. If the VCPU is hot-plugged, we
	 * करो handle provisioning however based on the existing "map"
	 * of enabled queues.
	 */
	क्रम (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) अणु
		काष्ठा xive_q *q = &xc->queues[i];

		/* Single escalation, no queue 7 */
		अगर (i == 7 && xive->single_escalation)
			अवरोध;

		/* Is queue alपढ़ोy enabled ? Provision it */
		अगर (xive->qmap & (1 << i)) अणु
			r = xive_provision_queue(vcpu, i);
			अगर (r == 0 && !xive->single_escalation)
				kvmppc_xive_attach_escalation(
					vcpu, i, xive->single_escalation);
			अगर (r)
				जाओ bail;
		पूर्ण अन्यथा अणु
			r = xive_native_configure_queue(xc->vp_id,
							q, i, शून्य, 0, true);
			अगर (r) अणु
				pr_err("Failed to configure queue %d for VCPU %d\n",
				       i, cpu);
				जाओ bail;
			पूर्ण
		पूर्ण
	पूर्ण

	/* If not करोne above, attach priority 0 escalation */
	r = kvmppc_xive_attach_escalation(vcpu, 0, xive->single_escalation);
	अगर (r)
		जाओ bail;

	/* Route the IPI */
	r = xive_native_configure_irq(xc->vp_ipi, xc->vp_id, 0, XICS_IPI);
	अगर (!r)
		xive_vm_esb_load(&xc->vp_ipi_data, XIVE_ESB_SET_PQ_00);

bail:
	mutex_unlock(&xive->lock);
	अगर (r) अणु
		kvmppc_xive_cleanup_vcpu(vcpu);
		वापस r;
	पूर्ण

	vcpu->arch.irq_type = KVMPPC_IRQ_XICS;
	वापस 0;
पूर्ण

/*
 * Scanning of queues beक्रमe/after migration save
 */
अटल व्योम xive_pre_save_set_queued(काष्ठा kvmppc_xive *xive, u32 irq)
अणु
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u16 idx;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb)
		वापस;

	state = &sb->irq_state[idx];

	/* Some sanity checking */
	अगर (!state->valid) अणु
		pr_err("invalid irq 0x%x in cpu queue!\n", irq);
		वापस;
	पूर्ण

	/*
	 * If the पूर्णांकerrupt is in a queue it should have P set.
	 * We warn so that माला_लो reported. A backtrace isn't useful
	 * so no need to use a WARN_ON.
	 */
	अगर (!state->saved_p)
		pr_err("Interrupt 0x%x is marked in a queue but P not set !\n", irq);

	/* Set flag */
	state->in_queue = true;
पूर्ण

अटल व्योम xive_pre_save_mask_irq(काष्ठा kvmppc_xive *xive,
				   काष्ठा kvmppc_xive_src_block *sb,
				   u32 irq)
अणु
	काष्ठा kvmppc_xive_irq_state *state = &sb->irq_state[irq];

	अगर (!state->valid)
		वापस;

	/* Mask and save state, this will also sync HW queues */
	state->saved_scan_prio = xive_lock_and_mask(xive, sb, state);

	/* Transfer P and Q */
	state->saved_p = state->old_p;
	state->saved_q = state->old_q;

	/* Unlock */
	arch_spin_unlock(&sb->lock);
पूर्ण

अटल व्योम xive_pre_save_unmask_irq(काष्ठा kvmppc_xive *xive,
				     काष्ठा kvmppc_xive_src_block *sb,
				     u32 irq)
अणु
	काष्ठा kvmppc_xive_irq_state *state = &sb->irq_state[irq];

	अगर (!state->valid)
		वापस;

	/*
	 * Lock / exclude EOI (not technically necessary अगर the
	 * guest isn't running concurrently. If this becomes a
	 * perक्रमmance issue we can probably हटाओ the lock.
	 */
	xive_lock_क्रम_unmask(sb, state);

	/* Restore mask/prio अगर it wasn't masked */
	अगर (state->saved_scan_prio != MASKED)
		xive_finish_unmask(xive, sb, state, state->saved_scan_prio);

	/* Unlock */
	arch_spin_unlock(&sb->lock);
पूर्ण

अटल व्योम xive_pre_save_queue(काष्ठा kvmppc_xive *xive, काष्ठा xive_q *q)
अणु
	u32 idx = q->idx;
	u32 toggle = q->toggle;
	u32 irq;

	करो अणु
		irq = __xive_पढ़ो_eq(q->qpage, q->msk, &idx, &toggle);
		अगर (irq > XICS_IPI)
			xive_pre_save_set_queued(xive, irq);
	पूर्ण जबतक(irq);
पूर्ण

अटल व्योम xive_pre_save_scan(काष्ठा kvmppc_xive *xive)
अणु
	काष्ठा kvm_vcpu *vcpu = शून्य;
	पूर्णांक i, j;

	/*
	 * See comment in xive_get_source() about how this
	 * work. Collect a stable state क्रम all पूर्णांकerrupts
	 */
	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		काष्ठा kvmppc_xive_src_block *sb = xive->src_blocks[i];
		अगर (!sb)
			जारी;
		क्रम (j = 0;  j < KVMPPC_XICS_IRQ_PER_ICS; j++)
			xive_pre_save_mask_irq(xive, sb, j);
	पूर्ण

	/* Then scan the queues and update the "in_queue" flag */
	kvm_क्रम_each_vcpu(i, vcpu, xive->kvm) अणु
		काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
		अगर (!xc)
			जारी;
		क्रम (j = 0; j < KVMPPC_XIVE_Q_COUNT; j++) अणु
			अगर (xc->queues[j].qpage)
				xive_pre_save_queue(xive, &xc->queues[j]);
		पूर्ण
	पूर्ण

	/* Finally restore पूर्णांकerrupt states */
	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		काष्ठा kvmppc_xive_src_block *sb = xive->src_blocks[i];
		अगर (!sb)
			जारी;
		क्रम (j = 0;  j < KVMPPC_XICS_IRQ_PER_ICS; j++)
			xive_pre_save_unmask_irq(xive, sb, j);
	पूर्ण
पूर्ण

अटल व्योम xive_post_save_scan(काष्ठा kvmppc_xive *xive)
अणु
	u32 i, j;

	/* Clear all the in_queue flags */
	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		काष्ठा kvmppc_xive_src_block *sb = xive->src_blocks[i];
		अगर (!sb)
			जारी;
		क्रम (j = 0;  j < KVMPPC_XICS_IRQ_PER_ICS; j++)
			sb->irq_state[j].in_queue = false;
	पूर्ण

	/* Next get_source() will करो a new scan */
	xive->saved_src_count = 0;
पूर्ण

/*
 * This वापसs the source configuration and state to user space.
 */
अटल पूर्णांक xive_get_source(काष्ठा kvmppc_xive *xive, दीर्घ irq, u64 addr)
अणु
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u64 __user *ubufp = (u64 __user *) addr;
	u64 val, prio;
	u16 idx;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb)
		वापस -ENOENT;

	state = &sb->irq_state[idx];

	अगर (!state->valid)
		वापस -ENOENT;

	pr_devel("get_source(%ld)...\n", irq);

	/*
	 * So to properly save the state पूर्णांकo something that looks like a
	 * XICS migration stream we cannot treat पूर्णांकerrupts inभागidually.
	 *
	 * We need, instead, mask them all (& save their previous PQ state)
	 * to get a stable state in the HW, then sync them to ensure that
	 * any पूर्णांकerrupt that had alपढ़ोy fired hits its queue, and finally
	 * scan all the queues to collect which पूर्णांकerrupts are still present
	 * in the queues, so we can set the "pending" flag on them and
	 * they can be resent on restore.
	 *
	 * So we करो it all when the "first" पूर्णांकerrupt माला_लो saved, all the
	 * state is collected at that poपूर्णांक, the rest of xive_get_source()
	 * will merely collect and convert that state to the expected
	 * userspace bit mask.
	 */
	अगर (xive->saved_src_count == 0)
		xive_pre_save_scan(xive);
	xive->saved_src_count++;

	/* Convert saved state पूर्णांकo something compatible with xics */
	val = state->act_server;
	prio = state->saved_scan_prio;

	अगर (prio == MASKED) अणु
		val |= KVM_XICS_MASKED;
		prio = state->saved_priority;
	पूर्ण
	val |= prio << KVM_XICS_PRIORITY_SHIFT;
	अगर (state->lsi) अणु
		val |= KVM_XICS_LEVEL_SENSITIVE;
		अगर (state->saved_p)
			val |= KVM_XICS_PENDING;
	पूर्ण अन्यथा अणु
		अगर (state->saved_p)
			val |= KVM_XICS_PRESENTED;

		अगर (state->saved_q)
			val |= KVM_XICS_QUEUED;

		/*
		 * We mark it pending (which will attempt a re-delivery)
		 * अगर we are in a queue *or* we were masked and had
		 * Q set which is equivalent to the XICS "masked pending"
		 * state
		 */
		अगर (state->in_queue || (prio == MASKED && state->saved_q))
			val |= KVM_XICS_PENDING;
	पूर्ण

	/*
	 * If that was the last पूर्णांकerrupt saved, reset the
	 * in_queue flags
	 */
	अगर (xive->saved_src_count == xive->src_count)
		xive_post_save_scan(xive);

	/* Copy the result to userspace */
	अगर (put_user(val, ubufp))
		वापस -EFAULT;

	वापस 0;
पूर्ण

काष्ठा kvmppc_xive_src_block *kvmppc_xive_create_src_block(
	काष्ठा kvmppc_xive *xive, पूर्णांक irq)
अणु
	काष्ठा kvmppc_xive_src_block *sb;
	पूर्णांक i, bid;

	bid = irq >> KVMPPC_XICS_ICS_SHIFT;

	mutex_lock(&xive->lock);

	/* block alपढ़ोy exists - somebody अन्यथा got here first */
	अगर (xive->src_blocks[bid])
		जाओ out;

	/* Create the ICS */
	sb = kzalloc(माप(*sb), GFP_KERNEL);
	अगर (!sb)
		जाओ out;

	sb->id = bid;

	क्रम (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) अणु
		sb->irq_state[i].number = (bid << KVMPPC_XICS_ICS_SHIFT) | i;
		sb->irq_state[i].eisn = 0;
		sb->irq_state[i].guest_priority = MASKED;
		sb->irq_state[i].saved_priority = MASKED;
		sb->irq_state[i].act_priority = MASKED;
	पूर्ण
	smp_wmb();
	xive->src_blocks[bid] = sb;

	अगर (bid > xive->max_sbid)
		xive->max_sbid = bid;

out:
	mutex_unlock(&xive->lock);
	वापस xive->src_blocks[bid];
पूर्ण

अटल bool xive_check_delayed_irq(काष्ठा kvmppc_xive *xive, u32 irq)
अणु
	काष्ठा kvm *kvm = xive->kvm;
	काष्ठा kvm_vcpu *vcpu = शून्य;
	पूर्णांक i;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;

		अगर (!xc)
			जारी;

		अगर (xc->delayed_irq == irq) अणु
			xc->delayed_irq = 0;
			xive->delayed_irqs--;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक xive_set_source(काष्ठा kvmppc_xive *xive, दीर्घ irq, u64 addr)
अणु
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u64 __user *ubufp = (u64 __user *) addr;
	u16 idx;
	u64 val;
	u8 act_prio, guest_prio;
	u32 server;
	पूर्णांक rc = 0;

	अगर (irq < KVMPPC_XICS_FIRST_IRQ || irq >= KVMPPC_XICS_NR_IRQS)
		वापस -ENOENT;

	pr_devel("set_source(irq=0x%lx)\n", irq);

	/* Find the source */
	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb) अणु
		pr_devel("No source, creating source block...\n");
		sb = kvmppc_xive_create_src_block(xive, irq);
		अगर (!sb) अणु
			pr_devel("Failed to create block...\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	state = &sb->irq_state[idx];

	/* Read user passed data */
	अगर (get_user(val, ubufp)) अणु
		pr_devel("fault getting user info !\n");
		वापस -EFAULT;
	पूर्ण

	server = val & KVM_XICS_DESTINATION_MASK;
	guest_prio = val >> KVM_XICS_PRIORITY_SHIFT;

	pr_devel("  val=0x016%llx (server=0x%x, guest_prio=%d)\n",
		 val, server, guest_prio);

	/*
	 * If the source करोesn't alपढ़ोy have an IPI, allocate
	 * one and get the corresponding data
	 */
	अगर (!state->ipi_number) अणु
		state->ipi_number = xive_native_alloc_irq();
		अगर (state->ipi_number == 0) अणु
			pr_devel("Failed to allocate IPI !\n");
			वापस -ENOMEM;
		पूर्ण
		xive_native_populate_irq_data(state->ipi_number, &state->ipi_data);
		pr_devel(" src_ipi=0x%x\n", state->ipi_number);
	पूर्ण

	/*
	 * We use lock_and_mask() to set us in the right masked
	 * state. We will override that state from the saved state
	 * further करोwn, but this will handle the हालs of पूर्णांकerrupts
	 * that need FW masking. We set the initial guest_priority to
	 * 0 beक्रमe calling it to ensure it actually perक्रमms the masking.
	 */
	state->guest_priority = 0;
	xive_lock_and_mask(xive, sb, state);

	/*
	 * Now, we select a target अगर we have one. If we करोn't we
	 * leave the पूर्णांकerrupt untargetted. It means that an पूर्णांकerrupt
	 * can become "untargetted" accross migration अगर it was masked
	 * by set_xive() but there is little we can करो about it.
	 */

	/* First convert prio and mark पूर्णांकerrupt as untargetted */
	act_prio = xive_prio_from_guest(guest_prio);
	state->act_priority = MASKED;

	/*
	 * We need to drop the lock due to the mutex below. Hopefully
	 * nothing is touching that पूर्णांकerrupt yet since it hasn't been
	 * advertized to a running guest yet
	 */
	arch_spin_unlock(&sb->lock);

	/* If we have a priority target the पूर्णांकerrupt */
	अगर (act_prio != MASKED) अणु
		/* First, check provisioning of queues */
		mutex_lock(&xive->lock);
		rc = xive_check_provisioning(xive->kvm, act_prio);
		mutex_unlock(&xive->lock);

		/* Target पूर्णांकerrupt */
		अगर (rc == 0)
			rc = xive_target_पूर्णांकerrupt(xive->kvm, state,
						   server, act_prio);
		/*
		 * If provisioning or targetting failed, leave it
		 * alone and masked. It will reमुख्य disabled until
		 * the guest re-tarमाला_लो it.
		 */
	पूर्ण

	/*
	 * Find out अगर this was a delayed irq stashed in an ICP,
	 * in which हाल, treat it as pending
	 */
	अगर (xive->delayed_irqs && xive_check_delayed_irq(xive, irq)) अणु
		val |= KVM_XICS_PENDING;
		pr_devel("  Found delayed ! forcing PENDING !\n");
	पूर्ण

	/* Cleanup the SW state */
	state->old_p = false;
	state->old_q = false;
	state->lsi = false;
	state->निश्चितed = false;

	/* Restore LSI state */
	अगर (val & KVM_XICS_LEVEL_SENSITIVE) अणु
		state->lsi = true;
		अगर (val & KVM_XICS_PENDING)
			state->निश्चितed = true;
		pr_devel("  LSI ! Asserted=%d\n", state->निश्चितed);
	पूर्ण

	/*
	 * Restore P and Q. If the पूर्णांकerrupt was pending, we
	 * क्रमce Q and !P, which will trigger a resend.
	 *
	 * That means that a guest that had both an पूर्णांकerrupt
	 * pending (queued) and Q set will restore with only
	 * one instance of that पूर्णांकerrupt instead of 2, but that
	 * is perfectly fine as coalescing पूर्णांकerrupts that haven't
	 * been presented yet is always allowed.
	 */
	अगर (val & KVM_XICS_PRESENTED && !(val & KVM_XICS_PENDING))
		state->old_p = true;
	अगर (val & KVM_XICS_QUEUED || val & KVM_XICS_PENDING)
		state->old_q = true;

	pr_devel("  P=%d, Q=%d\n", state->old_p, state->old_q);

	/*
	 * If the पूर्णांकerrupt was unmasked, update guest priority and
	 * perक्रमm the appropriate state transition and करो a
	 * re-trigger अगर necessary.
	 */
	अगर (val & KVM_XICS_MASKED) अणु
		pr_devel("  masked, saving prio\n");
		state->guest_priority = MASKED;
		state->saved_priority = guest_prio;
	पूर्ण अन्यथा अणु
		pr_devel("  unmasked, restoring to prio %d\n", guest_prio);
		xive_finish_unmask(xive, sb, state, guest_prio);
		state->saved_priority = guest_prio;
	पूर्ण

	/* Increment the number of valid sources and mark this one valid */
	अगर (!state->valid)
		xive->src_count++;
	state->valid = true;

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xive_set_irq(काष्ठा kvm *kvm, पूर्णांक irq_source_id, u32 irq, पूर्णांक level,
			bool line_status)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u16 idx;

	अगर (!xive)
		वापस -ENODEV;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb)
		वापस -EINVAL;

	/* Perक्रमm locklessly .... (we need to करो some RCUisms here...) */
	state = &sb->irq_state[idx];
	अगर (!state->valid)
		वापस -EINVAL;

	/* We करोn't allow a trigger on a passed-through पूर्णांकerrupt */
	अगर (state->pt_number)
		वापस -EINVAL;

	अगर ((level == 1 && state->lsi) || level == KVM_INTERRUPT_SET_LEVEL)
		state->निश्चितed = true;
	अन्यथा अगर (level == 0 || level == KVM_INTERRUPT_UNSET) अणु
		state->निश्चितed = false;
		वापस 0;
	पूर्ण

	/* Trigger the IPI */
	xive_irq_trigger(&state->ipi_data);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xive_set_nr_servers(काष्ठा kvmppc_xive *xive, u64 addr)
अणु
	u32 __user *ubufp = (u32 __user *) addr;
	u32 nr_servers;
	पूर्णांक rc = 0;

	अगर (get_user(nr_servers, ubufp))
		वापस -EFAULT;

	pr_devel("%s nr_servers=%u\n", __func__, nr_servers);

	अगर (!nr_servers || nr_servers > KVM_MAX_VCPU_ID)
		वापस -EINVAL;

	mutex_lock(&xive->lock);
	अगर (xive->vp_base != XIVE_INVALID_VP)
		/* The VP block is allocated once and मुक्तd when the device
		 * is released. Better not allow to change its size since its
		 * used by connect_vcpu to validate vCPU ids are valid (eg,
		 * setting it back to a higher value could allow connect_vcpu
		 * to come up with a VP id that goes beyond the VP block, which
		 * is likely to cause a crash in OPAL).
		 */
		rc = -EBUSY;
	अन्यथा अगर (nr_servers > KVM_MAX_VCPUS)
		/* We करोn't need more servers. Higher vCPU ids get packed
		 * करोwn below KVM_MAX_VCPUS by kvmppc_pack_vcpu_id().
		 */
		xive->nr_servers = KVM_MAX_VCPUS;
	अन्यथा
		xive->nr_servers = nr_servers;

	mutex_unlock(&xive->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक xive_set_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvmppc_xive *xive = dev->निजी;

	/* We honor the existing XICS ioctl */
	चयन (attr->group) अणु
	हाल KVM_DEV_XICS_GRP_SOURCES:
		वापस xive_set_source(xive, attr->attr, attr->addr);
	हाल KVM_DEV_XICS_GRP_CTRL:
		चयन (attr->attr) अणु
		हाल KVM_DEV_XICS_NR_SERVERS:
			वापस kvmppc_xive_set_nr_servers(xive, attr->addr);
		पूर्ण
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक xive_get_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvmppc_xive *xive = dev->निजी;

	/* We honor the existing XICS ioctl */
	चयन (attr->group) अणु
	हाल KVM_DEV_XICS_GRP_SOURCES:
		वापस xive_get_source(xive, attr->attr, attr->addr);
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक xive_has_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	/* We honor the same limits as XICS, at least क्रम now */
	चयन (attr->group) अणु
	हाल KVM_DEV_XICS_GRP_SOURCES:
		अगर (attr->attr >= KVMPPC_XICS_FIRST_IRQ &&
		    attr->attr < KVMPPC_XICS_NR_IRQS)
			वापस 0;
		अवरोध;
	हाल KVM_DEV_XICS_GRP_CTRL:
		चयन (attr->attr) अणु
		हाल KVM_DEV_XICS_NR_SERVERS:
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल व्योम kvmppc_xive_cleanup_irq(u32 hw_num, काष्ठा xive_irq_data *xd)
अणु
	xive_vm_esb_load(xd, XIVE_ESB_SET_PQ_01);
	xive_native_configure_irq(hw_num, 0, MASKED, 0);
पूर्ण

व्योम kvmppc_xive_मुक्त_sources(काष्ठा kvmppc_xive_src_block *sb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) अणु
		काष्ठा kvmppc_xive_irq_state *state = &sb->irq_state[i];

		अगर (!state->valid)
			जारी;

		kvmppc_xive_cleanup_irq(state->ipi_number, &state->ipi_data);
		xive_cleanup_irq_data(&state->ipi_data);
		xive_native_मुक्त_irq(state->ipi_number);

		/* Pass-through, cleanup too but keep IRQ hw data */
		अगर (state->pt_number)
			kvmppc_xive_cleanup_irq(state->pt_number, state->pt_data);

		state->valid = false;
	पूर्ण
पूर्ण

/*
 * Called when device fd is बंदd.  kvm->lock is held.
 */
अटल व्योम kvmppc_xive_release(काष्ठा kvm_device *dev)
अणु
	काष्ठा kvmppc_xive *xive = dev->निजी;
	काष्ठा kvm *kvm = xive->kvm;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	pr_devel("Releasing xive device\n");

	/*
	 * Since this is the device release function, we know that
	 * userspace करोes not have any खोलो fd referring to the
	 * device.  Thereक्रमe there can not be any of the device
	 * attribute set/get functions being executed concurrently,
	 * and similarly, the connect_vcpu and set/clr_mapped
	 * functions also cannot be being executed.
	 */

	debugfs_हटाओ(xive->dentry);

	/*
	 * We should clean up the vCPU पूर्णांकerrupt presenters first.
	 */
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		/*
		 * Take vcpu->mutex to ensure that no one_reg get/set ioctl
		 * (i.e. kvmppc_xive_[gs]et_icp) can be करोne concurrently.
		 * Holding the vcpu->mutex also means that the vcpu cannot
		 * be executing the KVM_RUN ioctl, and thereक्रमe it cannot
		 * be executing the XIVE push or pull code or accessing
		 * the XIVE MMIO regions.
		 */
		mutex_lock(&vcpu->mutex);
		kvmppc_xive_cleanup_vcpu(vcpu);
		mutex_unlock(&vcpu->mutex);
	पूर्ण

	/*
	 * Now that we have cleared vcpu->arch.xive_vcpu, vcpu->arch.irq_type
	 * and vcpu->arch.xive_esc_[vr]addr on each vcpu, we are safe
	 * against xive code getting called during vcpu execution or
	 * set/get one_reg operations.
	 */
	kvm->arch.xive = शून्य;

	/* Mask and मुक्त पूर्णांकerrupts */
	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		अगर (xive->src_blocks[i])
			kvmppc_xive_मुक्त_sources(xive->src_blocks[i]);
		kमुक्त(xive->src_blocks[i]);
		xive->src_blocks[i] = शून्य;
	पूर्ण

	अगर (xive->vp_base != XIVE_INVALID_VP)
		xive_native_मुक्त_vp_block(xive->vp_base);

	/*
	 * A reference of the kvmppc_xive poपूर्णांकer is now kept under
	 * the xive_devices काष्ठा of the machine क्रम reuse. It is
	 * मुक्तd when the VM is destroyed क्रम now until we fix all the
	 * execution paths.
	 */

	kमुक्त(dev);
पूर्ण

/*
 * When the guest chooses the पूर्णांकerrupt mode (XICS legacy or XIVE
 * native), the VM will चयन of KVM device. The previous device will
 * be "released" beक्रमe the new one is created.
 *
 * Until we are sure all execution paths are well रक्षित, provide a
 * fail safe (transitional) method क्रम device deकाष्ठाion, in which
 * the XIVE device poपूर्णांकer is recycled and not directly मुक्तd.
 */
काष्ठा kvmppc_xive *kvmppc_xive_get_device(काष्ठा kvm *kvm, u32 type)
अणु
	काष्ठा kvmppc_xive **kvm_xive_device = type == KVM_DEV_TYPE_XIVE ?
		&kvm->arch.xive_devices.native :
		&kvm->arch.xive_devices.xics_on_xive;
	काष्ठा kvmppc_xive *xive = *kvm_xive_device;

	अगर (!xive) अणु
		xive = kzalloc(माप(*xive), GFP_KERNEL);
		*kvm_xive_device = xive;
	पूर्ण अन्यथा अणु
		स_रखो(xive, 0, माप(*xive));
	पूर्ण

	वापस xive;
पूर्ण

/*
 * Create a XICS device with XIVE backend.  kvm->lock is held.
 */
अटल पूर्णांक kvmppc_xive_create(काष्ठा kvm_device *dev, u32 type)
अणु
	काष्ठा kvmppc_xive *xive;
	काष्ठा kvm *kvm = dev->kvm;

	pr_devel("Creating xive for partition\n");

	/* Alपढ़ोy there ? */
	अगर (kvm->arch.xive)
		वापस -EEXIST;

	xive = kvmppc_xive_get_device(kvm, type);
	अगर (!xive)
		वापस -ENOMEM;

	dev->निजी = xive;
	xive->dev = dev;
	xive->kvm = kvm;
	mutex_init(&xive->lock);

	/* We use the शेष queue size set by the host */
	xive->q_order = xive_native_शेष_eq_shअगरt();
	अगर (xive->q_order < PAGE_SHIFT)
		xive->q_page_order = 0;
	अन्यथा
		xive->q_page_order = xive->q_order - PAGE_SHIFT;

	/* VP allocation is delayed to the first call to connect_vcpu */
	xive->vp_base = XIVE_INVALID_VP;
	/* KVM_MAX_VCPUS limits the number of VMs to roughly 64 per sockets
	 * on a POWER9 प्रणाली.
	 */
	xive->nr_servers = KVM_MAX_VCPUS;

	xive->single_escalation = xive_native_has_single_escalation();

	kvm->arch.xive = xive;
	वापस 0;
पूर्ण

पूर्णांक kvmppc_xive_debug_show_queues(काष्ठा seq_file *m, काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) अणु
		काष्ठा xive_q *q = &xc->queues[i];
		u32 i0, i1, idx;

		अगर (!q->qpage && !xc->esc_virq[i])
			जारी;

		अगर (q->qpage) अणु
			seq_म_लिखो(m, "    q[%d]: ", i);
			idx = q->idx;
			i0 = be32_to_cpup(q->qpage + idx);
			idx = (idx + 1) & q->msk;
			i1 = be32_to_cpup(q->qpage + idx);
			seq_म_लिखो(m, "T=%d %08x %08x...\n", q->toggle,
				   i0, i1);
		पूर्ण
		अगर (xc->esc_virq[i]) अणु
			काष्ठा irq_data *d = irq_get_irq_data(xc->esc_virq[i]);
			काष्ठा xive_irq_data *xd =
				irq_data_get_irq_handler_data(d);
			u64 pq = xive_vm_esb_load(xd, XIVE_ESB_GET);

			seq_म_लिखो(m, "    ESC %d %c%c EOI @%llx",
				   xc->esc_virq[i],
				   (pq & XIVE_ESB_VAL_P) ? 'P' : '-',
				   (pq & XIVE_ESB_VAL_Q) ? 'Q' : '-',
				   xd->eoi_page);
			seq_माला_दो(m, "\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम kvmppc_xive_debug_show_sources(काष्ठा seq_file *m,
				    काष्ठा kvmppc_xive_src_block *sb)
अणु
	पूर्णांक i;

	seq_माला_दो(m, "    LISN      HW/CHIP   TYPE    PQ      EISN    CPU/PRIO\n");
	क्रम (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) अणु
		काष्ठा kvmppc_xive_irq_state *state = &sb->irq_state[i];
		काष्ठा xive_irq_data *xd;
		u64 pq;
		u32 hw_num;

		अगर (!state->valid)
			जारी;

		kvmppc_xive_select_irq(state, &hw_num, &xd);

		pq = xive_vm_esb_load(xd, XIVE_ESB_GET);

		seq_म_लिखो(m, "%08x  %08x/%02x", state->number, hw_num,
			   xd->src_chip);
		अगर (state->lsi)
			seq_म_लिखो(m, " %cLSI", state->निश्चितed ? '^' : ' ');
		अन्यथा
			seq_माला_दो(m, "  MSI");

		seq_म_लिखो(m, " %s  %c%c  %08x   % 4d/%d",
			   state->ipi_number == hw_num ? "IPI" : " PT",
			   pq & XIVE_ESB_VAL_P ? 'P' : '-',
			   pq & XIVE_ESB_VAL_Q ? 'Q' : '-',
			   state->eisn, state->act_server,
			   state->act_priority);

		seq_माला_दो(m, "\n");
	पूर्ण
पूर्ण

अटल पूर्णांक xive_debug_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	काष्ठा kvmppc_xive *xive = m->निजी;
	काष्ठा kvm *kvm = xive->kvm;
	काष्ठा kvm_vcpu *vcpu;
	u64 t_rm_h_xirr = 0;
	u64 t_rm_h_ipoll = 0;
	u64 t_rm_h_cppr = 0;
	u64 t_rm_h_eoi = 0;
	u64 t_rm_h_ipi = 0;
	u64 t_vm_h_xirr = 0;
	u64 t_vm_h_ipoll = 0;
	u64 t_vm_h_cppr = 0;
	u64 t_vm_h_eoi = 0;
	u64 t_vm_h_ipi = 0;
	अचिन्हित पूर्णांक i;

	अगर (!kvm)
		वापस 0;

	seq_माला_दो(m, "=========\nVCPU state\n=========\n");

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;

		अगर (!xc)
			जारी;

		seq_म_लिखो(m, "VCPU %d: VP:%#x/%02x\n"
			 "    CPPR:%#x HWCPPR:%#x MFRR:%#x PEND:%#x h_xirr: R=%lld V=%lld\n",
			 xc->server_num, xc->vp_id, xc->vp_chip_id,
			 xc->cppr, xc->hw_cppr,
			 xc->mfrr, xc->pending,
			 xc->stat_rm_h_xirr, xc->stat_vm_h_xirr);

		kvmppc_xive_debug_show_queues(m, vcpu);

		t_rm_h_xirr += xc->stat_rm_h_xirr;
		t_rm_h_ipoll += xc->stat_rm_h_ipoll;
		t_rm_h_cppr += xc->stat_rm_h_cppr;
		t_rm_h_eoi += xc->stat_rm_h_eoi;
		t_rm_h_ipi += xc->stat_rm_h_ipi;
		t_vm_h_xirr += xc->stat_vm_h_xirr;
		t_vm_h_ipoll += xc->stat_vm_h_ipoll;
		t_vm_h_cppr += xc->stat_vm_h_cppr;
		t_vm_h_eoi += xc->stat_vm_h_eoi;
		t_vm_h_ipi += xc->stat_vm_h_ipi;
	पूर्ण

	seq_माला_दो(m, "Hcalls totals\n");
	seq_म_लिखो(m, " H_XIRR  R=%10lld V=%10lld\n", t_rm_h_xirr, t_vm_h_xirr);
	seq_म_लिखो(m, " H_IPOLL R=%10lld V=%10lld\n", t_rm_h_ipoll, t_vm_h_ipoll);
	seq_म_लिखो(m, " H_CPPR  R=%10lld V=%10lld\n", t_rm_h_cppr, t_vm_h_cppr);
	seq_म_लिखो(m, " H_EOI   R=%10lld V=%10lld\n", t_rm_h_eoi, t_vm_h_eoi);
	seq_म_लिखो(m, " H_IPI   R=%10lld V=%10lld\n", t_rm_h_ipi, t_vm_h_ipi);

	seq_माला_दो(m, "=========\nSources\n=========\n");

	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		काष्ठा kvmppc_xive_src_block *sb = xive->src_blocks[i];

		अगर (sb) अणु
			arch_spin_lock(&sb->lock);
			kvmppc_xive_debug_show_sources(m, sb);
			arch_spin_unlock(&sb->lock);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(xive_debug);

अटल व्योम xive_debugfs_init(काष्ठा kvmppc_xive *xive)
अणु
	अक्षर *name;

	name = kaप्र_लिखो(GFP_KERNEL, "kvm-xive-%p", xive);
	अगर (!name) अणु
		pr_err("%s: no memory for name\n", __func__);
		वापस;
	पूर्ण

	xive->dentry = debugfs_create_file(name, S_IRUGO, घातerpc_debugfs_root,
					   xive, &xive_debug_fops);

	pr_debug("%s: created %s\n", __func__, name);
	kमुक्त(name);
पूर्ण

अटल व्योम kvmppc_xive_init(काष्ठा kvm_device *dev)
अणु
	काष्ठा kvmppc_xive *xive = (काष्ठा kvmppc_xive *)dev->निजी;

	/* Register some debug पूर्णांकerfaces */
	xive_debugfs_init(xive);
पूर्ण

काष्ठा kvm_device_ops kvm_xive_ops = अणु
	.name = "kvm-xive",
	.create = kvmppc_xive_create,
	.init = kvmppc_xive_init,
	.release = kvmppc_xive_release,
	.set_attr = xive_set_attr,
	.get_attr = xive_get_attr,
	.has_attr = xive_has_attr,
पूर्ण;

व्योम kvmppc_xive_init_module(व्योम)
अणु
	__xive_vm_h_xirr = xive_vm_h_xirr;
	__xive_vm_h_ipoll = xive_vm_h_ipoll;
	__xive_vm_h_ipi = xive_vm_h_ipi;
	__xive_vm_h_cppr = xive_vm_h_cppr;
	__xive_vm_h_eoi = xive_vm_h_eoi;
पूर्ण

व्योम kvmppc_xive_निकास_module(व्योम)
अणु
	__xive_vm_h_xirr = शून्य;
	__xive_vm_h_ipoll = शून्य;
	__xive_vm_h_ipi = शून्य;
	__xive_vm_h_cppr = शून्य;
	__xive_vm_h_eoi = शून्य;
पूर्ण
