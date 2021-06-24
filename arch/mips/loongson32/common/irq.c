<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 Zhang, Keguang <keguang.zhang@gmail.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/irq_cpu.h>

#समावेश <loongson1.h>
#समावेश <irq.h>

#घोषणा LS1X_INTC_REG(n, x) \
		((व्योम __iomem *)KSEG1ADDR(LS1X_INTC_BASE + (n * 0x18) + (x)))

#घोषणा LS1X_INTC_INTISR(n)		LS1X_INTC_REG(n, 0x0)
#घोषणा LS1X_INTC_INTIEN(n)		LS1X_INTC_REG(n, 0x4)
#घोषणा LS1X_INTC_INTSET(n)		LS1X_INTC_REG(n, 0x8)
#घोषणा LS1X_INTC_INTCLR(n)		LS1X_INTC_REG(n, 0xc)
#घोषणा LS1X_INTC_INTPOL(n)		LS1X_INTC_REG(n, 0x10)
#घोषणा LS1X_INTC_INTEDGE(n)		LS1X_INTC_REG(n, 0x14)

अटल व्योम ls1x_irq_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = (d->irq - LS1X_IRQ_BASE) & 0x1f;
	अचिन्हित पूर्णांक n = (d->irq - LS1X_IRQ_BASE) >> 5;

	__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTCLR(n))
			| (1 << bit), LS1X_INTC_INTCLR(n));
पूर्ण

अटल व्योम ls1x_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = (d->irq - LS1X_IRQ_BASE) & 0x1f;
	अचिन्हित पूर्णांक n = (d->irq - LS1X_IRQ_BASE) >> 5;

	__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTIEN(n))
			& ~(1 << bit), LS1X_INTC_INTIEN(n));
पूर्ण

अटल व्योम ls1x_irq_mask_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = (d->irq - LS1X_IRQ_BASE) & 0x1f;
	अचिन्हित पूर्णांक n = (d->irq - LS1X_IRQ_BASE) >> 5;

	__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTIEN(n))
			& ~(1 << bit), LS1X_INTC_INTIEN(n));
	__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTCLR(n))
			| (1 << bit), LS1X_INTC_INTCLR(n));
पूर्ण

अटल व्योम ls1x_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = (d->irq - LS1X_IRQ_BASE) & 0x1f;
	अचिन्हित पूर्णांक n = (d->irq - LS1X_IRQ_BASE) >> 5;

	__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTIEN(n))
			| (1 << bit), LS1X_INTC_INTIEN(n));
पूर्ण

अटल पूर्णांक ls1x_irq_settype(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक bit = (d->irq - LS1X_IRQ_BASE) & 0x1f;
	अचिन्हित पूर्णांक n = (d->irq - LS1X_IRQ_BASE) >> 5;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTPOL(n))
			| (1 << bit), LS1X_INTC_INTPOL(n));
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTEDGE(n))
			& ~(1 << bit), LS1X_INTC_INTEDGE(n));
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTPOL(n))
			& ~(1 << bit), LS1X_INTC_INTPOL(n));
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTEDGE(n))
			& ~(1 << bit), LS1X_INTC_INTEDGE(n));
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTPOL(n))
			| (1 << bit), LS1X_INTC_INTPOL(n));
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTEDGE(n))
			| (1 << bit), LS1X_INTC_INTEDGE(n));
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTPOL(n))
			& ~(1 << bit), LS1X_INTC_INTPOL(n));
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTEDGE(n))
			| (1 << bit), LS1X_INTC_INTEDGE(n));
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTPOL(n))
			& ~(1 << bit), LS1X_INTC_INTPOL(n));
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_INTC_INTEDGE(n))
			| (1 << bit), LS1X_INTC_INTEDGE(n));
		अवरोध;
	हाल IRQ_TYPE_NONE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip ls1x_irq_chip = अणु
	.name		= "LS1X-INTC",
	.irq_ack	= ls1x_irq_ack,
	.irq_mask	= ls1x_irq_mask,
	.irq_mask_ack	= ls1x_irq_mask_ack,
	.irq_unmask	= ls1x_irq_unmask,
	.irq_set_type   = ls1x_irq_settype,
पूर्ण;

अटल व्योम ls1x_irq_dispatch(पूर्णांक n)
अणु
	u32 पूर्णांक_status, irq;

	/* Get pending sources, masked by current enables */
	पूर्णांक_status = __raw_पढ़ोl(LS1X_INTC_INTISR(n)) &
			__raw_पढ़ोl(LS1X_INTC_INTIEN(n));

	अगर (पूर्णांक_status) अणु
		irq = LS1X_IRQ(n, __ffs(पूर्णांक_status));
		करो_IRQ(irq);
	पूर्ण
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक pending;

	pending = पढ़ो_c0_cause() & पढ़ो_c0_status() & ST0_IM;

	अगर (pending & CAUSEF_IP7)
		करो_IRQ(TIMER_IRQ);
	अन्यथा अगर (pending & CAUSEF_IP2)
		ls1x_irq_dispatch(0); /* INT0 */
	अन्यथा अगर (pending & CAUSEF_IP3)
		ls1x_irq_dispatch(1); /* INT1 */
	अन्यथा अगर (pending & CAUSEF_IP4)
		ls1x_irq_dispatch(2); /* INT2 */
	अन्यथा अगर (pending & CAUSEF_IP5)
		ls1x_irq_dispatch(3); /* INT3 */
	अन्यथा अगर (pending & CAUSEF_IP6)
		ls1x_irq_dispatch(4); /* INT4 */
	अन्यथा
		spurious_पूर्णांकerrupt();

पूर्ण

अटल व्योम __init ls1x_irq_init(पूर्णांक base)
अणु
	पूर्णांक n;

	/* Disable पूर्णांकerrupts and clear pending,
	 * setup all IRQs as high level triggered
	 */
	क्रम (n = 0; n < INTN; n++) अणु
		__raw_ग_लिखोl(0x0, LS1X_INTC_INTIEN(n));
		__raw_ग_लिखोl(0xffffffff, LS1X_INTC_INTCLR(n));
		__raw_ग_लिखोl(0xffffffff, LS1X_INTC_INTPOL(n));
		/* set DMA0, DMA1 and DMA2 to edge trigger */
		__raw_ग_लिखोl(n ? 0x0 : 0xe000, LS1X_INTC_INTEDGE(n));
	पूर्ण


	क्रम (n = base; n < NR_IRQS; n++) अणु
		irq_set_chip_and_handler(n, &ls1x_irq_chip,
					 handle_level_irq);
	पूर्ण

	अगर (request_irq(INT0_IRQ, no_action, IRQF_NO_THREAD, "cascade", शून्य))
		pr_err("Failed to request irq %d (cascade)\n", INT0_IRQ);
	अगर (request_irq(INT1_IRQ, no_action, IRQF_NO_THREAD, "cascade", शून्य))
		pr_err("Failed to request irq %d (cascade)\n", INT1_IRQ);
	अगर (request_irq(INT2_IRQ, no_action, IRQF_NO_THREAD, "cascade", शून्य))
		pr_err("Failed to request irq %d (cascade)\n", INT2_IRQ);
	अगर (request_irq(INT3_IRQ, no_action, IRQF_NO_THREAD, "cascade", शून्य))
		pr_err("Failed to request irq %d (cascade)\n", INT3_IRQ);
#अगर defined(CONFIG_LOONGSON1_LS1C)
	अगर (request_irq(INT4_IRQ, no_action, IRQF_NO_THREAD, "cascade", शून्य))
		pr_err("Failed to request irq %d (cascade)\n", INT4_IRQ);
#पूर्ण_अगर
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	mips_cpu_irq_init();
	ls1x_irq_init(LS1X_IRQ_BASE);
पूर्ण
