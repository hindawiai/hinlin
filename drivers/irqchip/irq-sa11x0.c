<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Dmitry Eremin-Solenikov
 * Copyright (C) 1999-2001 Nicolas Pitre
 *
 * Generic IRQ handling क्रम the SA11x0.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/irqchip/irq-sa11x0.h>

#समावेश <soc/sa1100/pwer.h>

#समावेश <यंत्र/exception.h>

#घोषणा ICIP	0x00  /* IC IRQ Pending reg. */
#घोषणा ICMR	0x04  /* IC Mask Reg.        */
#घोषणा ICLR	0x08  /* IC Level Reg.       */
#घोषणा ICCR	0x0C  /* IC Control Reg.     */
#घोषणा ICFP	0x10  /* IC FIQ Pending reg. */
#घोषणा ICPR	0x20  /* IC Pending Reg.     */

अटल व्योम __iomem *iobase;

/*
 * We करोn't need to ACK IRQs on the SA1100 unless they're GPIOs
 * this is क्रम पूर्णांकernal IRQs i.e. from IRQ LCD to RTCAlrm.
 */
अटल व्योम sa1100_mask_irq(काष्ठा irq_data *d)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(iobase + ICMR);
	reg &= ~BIT(d->hwirq);
	ग_लिखोl_relaxed(reg, iobase + ICMR);
पूर्ण

अटल व्योम sa1100_unmask_irq(काष्ठा irq_data *d)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(iobase + ICMR);
	reg |= BIT(d->hwirq);
	ग_लिखोl_relaxed(reg, iobase + ICMR);
पूर्ण

अटल पूर्णांक sa1100_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	वापस sa11x0_sc_set_wake(d->hwirq, on);
पूर्ण

अटल काष्ठा irq_chip sa1100_normal_chip = अणु
	.name		= "SC",
	.irq_ack	= sa1100_mask_irq,
	.irq_mask	= sa1100_mask_irq,
	.irq_unmask	= sa1100_unmask_irq,
	.irq_set_wake	= sa1100_set_wake,
पूर्ण;

अटल पूर्णांक sa1100_normal_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d,
		अचिन्हित पूर्णांक irq, irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &sa1100_normal_chip,
				 handle_level_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sa1100_normal_irqकरोमुख्य_ops = अणु
	.map = sa1100_normal_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

अटल काष्ठा irq_करोमुख्य *sa1100_normal_irqकरोमुख्य;

अटल काष्ठा sa1100irq_state अणु
	अचिन्हित पूर्णांक	saved;
	अचिन्हित पूर्णांक	icmr;
	अचिन्हित पूर्णांक	iclr;
	अचिन्हित पूर्णांक	iccr;
पूर्ण sa1100irq_state;

अटल पूर्णांक sa1100irq_suspend(व्योम)
अणु
	काष्ठा sa1100irq_state *st = &sa1100irq_state;

	st->saved = 1;
	st->icmr = पढ़ोl_relaxed(iobase + ICMR);
	st->iclr = पढ़ोl_relaxed(iobase + ICLR);
	st->iccr = पढ़ोl_relaxed(iobase + ICCR);

	/*
	 * Disable all GPIO-based पूर्णांकerrupts.
	 */
	ग_लिखोl_relaxed(st->icmr & 0xfffff000, iobase + ICMR);

	वापस 0;
पूर्ण

अटल व्योम sa1100irq_resume(व्योम)
अणु
	काष्ठा sa1100irq_state *st = &sa1100irq_state;

	अगर (st->saved) अणु
		ग_लिखोl_relaxed(st->iccr, iobase + ICCR);
		ग_लिखोl_relaxed(st->iclr, iobase + ICLR);

		ग_लिखोl_relaxed(st->icmr, iobase + ICMR);
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops sa1100irq_syscore_ops = अणु
	.suspend	= sa1100irq_suspend,
	.resume		= sa1100irq_resume,
पूर्ण;

अटल पूर्णांक __init sa1100irq_init_devicefs(व्योम)
अणु
	रेजिस्टर_syscore_ops(&sa1100irq_syscore_ops);
	वापस 0;
पूर्ण

device_initcall(sa1100irq_init_devicefs);

अटल यंत्रlinkage व्योम __exception_irq_entry
sa1100_handle_irq(काष्ठा pt_regs *regs)
अणु
	uपूर्णांक32_t icip, icmr, mask;

	करो अणु
		icip = पढ़ोl_relaxed(iobase + ICIP);
		icmr = पढ़ोl_relaxed(iobase + ICMR);
		mask = icip & icmr;

		अगर (mask == 0)
			अवरोध;

		handle_करोमुख्य_irq(sa1100_normal_irqकरोमुख्य,
				ffs(mask) - 1, regs);
	पूर्ण जबतक (1);
पूर्ण

व्योम __init sa11x0_init_irq_nodt(पूर्णांक irq_start, resource_माप_प्रकार io_start)
अणु
	iobase = ioremap(io_start, SZ_64K);
	अगर (WARN_ON(!iobase))
		वापस;

	/* disable all IRQs */
	ग_लिखोl_relaxed(0, iobase + ICMR);

	/* all IRQs are IRQ, not FIQ */
	ग_लिखोl_relaxed(0, iobase + ICLR);

	/*
	 * Whatever the करोc says, this has to be set क्रम the रुको-on-irq
	 * inकाष्ठाion to work... on a SA1100 rev 9 at least.
	 */
	ग_लिखोl_relaxed(1, iobase + ICCR);

	sa1100_normal_irqकरोमुख्य = irq_करोमुख्य_add_simple(शून्य,
			32, irq_start,
			&sa1100_normal_irqकरोमुख्य_ops, शून्य);

	set_handle_irq(sa1100_handle_irq);
पूर्ण
