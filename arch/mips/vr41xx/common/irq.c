<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Interrupt handing routines क्रम NEC VR4100 series.
 *
 *  Copyright (C) 2005-2007  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/vr41xx/irq.h>

प्रकार काष्ठा irq_cascade अणु
	पूर्णांक (*get_irq)(अचिन्हित पूर्णांक);
पूर्ण irq_cascade_t;

अटल irq_cascade_t irq_cascade[NR_IRQS] __cacheline_aligned;

पूर्णांक cascade_irq(अचिन्हित पूर्णांक irq, पूर्णांक (*get_irq)(अचिन्हित पूर्णांक))
अणु
	पूर्णांक retval = 0;

	अगर (irq >= NR_IRQS)
		वापस -EINVAL;

	अगर (irq_cascade[irq].get_irq != शून्य)
		मुक्त_irq(irq, शून्य);

	irq_cascade[irq].get_irq = get_irq;

	अगर (get_irq != शून्य) अणु
		retval = request_irq(irq, no_action, IRQF_NO_THREAD,
				     "cascade", शून्य);
		अगर (retval < 0)
			irq_cascade[irq].get_irq = शून्य;
	पूर्ण

	वापस retval;
पूर्ण

EXPORT_SYMBOL_GPL(cascade_irq);

अटल व्योम irq_dispatch(अचिन्हित पूर्णांक irq)
अणु
	irq_cascade_t *cascade;

	अगर (irq >= NR_IRQS) अणु
		atomic_inc(&irq_err_count);
		वापस;
	पूर्ण

	cascade = irq_cascade + irq;
	अगर (cascade->get_irq != शून्य) अणु
		काष्ठा irq_desc *desc = irq_to_desc(irq);
		काष्ठा irq_data *idata = irq_desc_get_irq_data(desc);
		काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
		पूर्णांक ret;

		अगर (chip->irq_mask_ack)
			chip->irq_mask_ack(idata);
		अन्यथा अणु
			chip->irq_mask(idata);
			chip->irq_ack(idata);
		पूर्ण
		ret = cascade->get_irq(irq);
		irq = ret;
		अगर (ret < 0)
			atomic_inc(&irq_err_count);
		अन्यथा
			irq_dispatch(irq);
		अगर (!irqd_irq_disabled(idata) && chip->irq_unmask)
			chip->irq_unmask(idata);
	पूर्ण अन्यथा
		करो_IRQ(irq);
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक pending = पढ़ो_c0_cause() & पढ़ो_c0_status() & ST0_IM;

	अगर (pending & CAUSEF_IP7)
		करो_IRQ(TIMER_IRQ);
	अन्यथा अगर (pending & 0x7800) अणु
		अगर (pending & CAUSEF_IP3)
			irq_dispatch(INT1_IRQ);
		अन्यथा अगर (pending & CAUSEF_IP4)
			irq_dispatch(INT2_IRQ);
		अन्यथा अगर (pending & CAUSEF_IP5)
			irq_dispatch(INT3_IRQ);
		अन्यथा अगर (pending & CAUSEF_IP6)
			irq_dispatch(INT4_IRQ);
	पूर्ण अन्यथा अगर (pending & CAUSEF_IP2)
		irq_dispatch(INT0_IRQ);
	अन्यथा अगर (pending & CAUSEF_IP0)
		करो_IRQ(MIPS_SOFTINT0_IRQ);
	अन्यथा अगर (pending & CAUSEF_IP1)
		करो_IRQ(MIPS_SOFTINT1_IRQ);
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	mips_cpu_irq_init();
पूर्ण
