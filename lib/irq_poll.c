<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions related to पूर्णांकerrupt-poll handling in the block layer. This
 * is similar to NAPI क्रम network devices.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpu.h>
#समावेश <linux/irq_poll.h>
#समावेश <linux/delay.h>

अटल अचिन्हित पूर्णांक irq_poll_budget __पढ़ो_mostly = 256;

अटल DEFINE_PER_CPU(काष्ठा list_head, blk_cpu_iopoll);

/**
 * irq_poll_sched - Schedule a run of the iopoll handler
 * @iop:      The parent iopoll काष्ठाure
 *
 * Description:
 *     Add this irq_poll काष्ठाure to the pending poll list and trigger the
 *     उठाओ of the blk iopoll softirq.
 **/
व्योम irq_poll_sched(काष्ठा irq_poll *iop)
अणु
	अचिन्हित दीर्घ flags;

	अगर (test_bit(IRQ_POLL_F_DISABLE, &iop->state))
		वापस;
	अगर (test_and_set_bit(IRQ_POLL_F_SCHED, &iop->state))
		वापस;

	local_irq_save(flags);
	list_add_tail(&iop->list, this_cpu_ptr(&blk_cpu_iopoll));
	उठाओ_softirq_irqoff(IRQ_POLL_SOFTIRQ);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(irq_poll_sched);

/**
 * __irq_poll_complete - Mark this @iop as un-polled again
 * @iop:      The parent iopoll काष्ठाure
 *
 * Description:
 *     See irq_poll_complete(). This function must be called with पूर्णांकerrupts
 *     disabled.
 **/
अटल व्योम __irq_poll_complete(काष्ठा irq_poll *iop)
अणु
	list_del(&iop->list);
	smp_mb__beक्रमe_atomic();
	clear_bit_unlock(IRQ_POLL_F_SCHED, &iop->state);
पूर्ण

/**
 * irq_poll_complete - Mark this @iop as un-polled again
 * @iop:      The parent iopoll काष्ठाure
 *
 * Description:
 *     If a driver consumes less than the asचिन्हित budget in its run of the
 *     iopoll handler, it'll end the polled mode by calling this function. The
 *     iopoll handler will not be invoked again beक्रमe irq_poll_sched()
 *     is called.
 **/
व्योम irq_poll_complete(काष्ठा irq_poll *iop)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__irq_poll_complete(iop);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(irq_poll_complete);

अटल व्योम __latent_entropy irq_poll_softirq(काष्ठा softirq_action *h)
अणु
	काष्ठा list_head *list = this_cpu_ptr(&blk_cpu_iopoll);
	पूर्णांक rearm = 0, budget = irq_poll_budget;
	अचिन्हित दीर्घ start_समय = jअगरfies;

	local_irq_disable();

	जबतक (!list_empty(list)) अणु
		काष्ठा irq_poll *iop;
		पूर्णांक work, weight;

		/*
		 * If softirq winकरोw is exhausted then punt.
		 */
		अगर (budget <= 0 || समय_after(jअगरfies, start_समय)) अणु
			rearm = 1;
			अवरोध;
		पूर्ण

		local_irq_enable();

		/* Even though पूर्णांकerrupts have been re-enabled, this
		 * access is safe because पूर्णांकerrupts can only add new
		 * entries to the tail of this list, and only ->poll()
		 * calls can हटाओ this head entry from the list.
		 */
		iop = list_entry(list->next, काष्ठा irq_poll, list);

		weight = iop->weight;
		work = 0;
		अगर (test_bit(IRQ_POLL_F_SCHED, &iop->state))
			work = iop->poll(iop, weight);

		budget -= work;

		local_irq_disable();

		/*
		 * Drivers must not modअगरy the iopoll state, अगर they
		 * consume their asचिन्हित weight (or more, some drivers can't
		 * easily just stop processing, they have to complete an
		 * entire mask of commands).In such हालs this code
		 * still "owns" the iopoll instance and thereक्रमe can
		 * move the instance around on the list at-will.
		 */
		अगर (work >= weight) अणु
			अगर (test_bit(IRQ_POLL_F_DISABLE, &iop->state))
				__irq_poll_complete(iop);
			अन्यथा
				list_move_tail(&iop->list, list);
		पूर्ण
	पूर्ण

	अगर (rearm)
		__उठाओ_softirq_irqoff(IRQ_POLL_SOFTIRQ);

	local_irq_enable();
पूर्ण

/**
 * irq_poll_disable - Disable iopoll on this @iop
 * @iop:      The parent iopoll काष्ठाure
 *
 * Description:
 *     Disable io polling and रुको क्रम any pending callbacks to have completed.
 **/
व्योम irq_poll_disable(काष्ठा irq_poll *iop)
अणु
	set_bit(IRQ_POLL_F_DISABLE, &iop->state);
	जबतक (test_and_set_bit(IRQ_POLL_F_SCHED, &iop->state))
		msleep(1);
	clear_bit(IRQ_POLL_F_DISABLE, &iop->state);
पूर्ण
EXPORT_SYMBOL(irq_poll_disable);

/**
 * irq_poll_enable - Enable iopoll on this @iop
 * @iop:      The parent iopoll काष्ठाure
 *
 * Description:
 *     Enable iopoll on this @iop. Note that the handler run will not be
 *     scheduled, it will only mark it as active.
 **/
व्योम irq_poll_enable(काष्ठा irq_poll *iop)
अणु
	BUG_ON(!test_bit(IRQ_POLL_F_SCHED, &iop->state));
	smp_mb__beक्रमe_atomic();
	clear_bit_unlock(IRQ_POLL_F_SCHED, &iop->state);
पूर्ण
EXPORT_SYMBOL(irq_poll_enable);

/**
 * irq_poll_init - Initialize this @iop
 * @iop:      The parent iopoll काष्ठाure
 * @weight:   The शेष weight (or command completion budget)
 * @poll_fn:  The handler to invoke
 *
 * Description:
 *     Initialize and enable this irq_poll काष्ठाure.
 **/
व्योम irq_poll_init(काष्ठा irq_poll *iop, पूर्णांक weight, irq_poll_fn *poll_fn)
अणु
	स_रखो(iop, 0, माप(*iop));
	INIT_LIST_HEAD(&iop->list);
	iop->weight = weight;
	iop->poll = poll_fn;
पूर्ण
EXPORT_SYMBOL(irq_poll_init);

अटल पूर्णांक irq_poll_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * If a CPU goes away, splice its entries to the current CPU
	 * and trigger a run of the softirq
	 */
	local_irq_disable();
	list_splice_init(&per_cpu(blk_cpu_iopoll, cpu),
			 this_cpu_ptr(&blk_cpu_iopoll));
	__उठाओ_softirq_irqoff(IRQ_POLL_SOFTIRQ);
	local_irq_enable();

	वापस 0;
पूर्ण

अटल __init पूर्णांक irq_poll_setup(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		INIT_LIST_HEAD(&per_cpu(blk_cpu_iopoll, i));

	खोलो_softirq(IRQ_POLL_SOFTIRQ, irq_poll_softirq);
	cpuhp_setup_state_nocalls(CPUHP_IRQ_POLL_DEAD, "irq_poll:dead", शून्य,
				  irq_poll_cpu_dead);
	वापस 0;
पूर्ण
subsys_initcall(irq_poll_setup);
