<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Debugging prपूर्णांकout:
 */

#घोषणा ___P(f) अगर (desc->status_use_accessors & f) prपूर्णांकk("%14s set\n", #f)
#घोषणा ___PS(f) अगर (desc->istate & f) prपूर्णांकk("%14s set\n", #f)
/* FIXME */
#घोषणा ___PD(f) करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम prपूर्णांक_irq_desc(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc)
अणु
	अटल DEFINE_RATELIMIT_STATE(ratelimit, 5 * HZ, 5);

	अगर (!__ratelimit(&ratelimit))
		वापस;

	prपूर्णांकk("irq %d, desc: %p, depth: %d, count: %d, unhandled: %d\n",
		irq, desc, desc->depth, desc->irq_count, desc->irqs_unhandled);
	prपूर्णांकk("->handle_irq():  %p, %pS\n",
		desc->handle_irq, desc->handle_irq);
	prपूर्णांकk("->irq_data.chip(): %p, %pS\n",
		desc->irq_data.chip, desc->irq_data.chip);
	prपूर्णांकk("->action(): %p\n", desc->action);
	अगर (desc->action) अणु
		prपूर्णांकk("->action->handler(): %p, %pS\n",
			desc->action->handler, desc->action->handler);
	पूर्ण

	___P(IRQ_LEVEL);
	___P(IRQ_PER_CPU);
	___P(IRQ_NOPROBE);
	___P(IRQ_NOREQUEST);
	___P(IRQ_NOTHREAD);
	___P(IRQ_NOAUTOEN);

	___PS(IRQS_AUTODETECT);
	___PS(IRQS_REPLAY);
	___PS(IRQS_WAITING);
	___PS(IRQS_PENDING);

	___PD(IRQS_INPROGRESS);
	___PD(IRQS_DISABLED);
	___PD(IRQS_MASKED);
पूर्ण

#अघोषित ___P
#अघोषित ___PS
#अघोषित ___PD
