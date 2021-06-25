<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/7206/irq.c
 *
 * Copyright (C) 2005,2006 Yoshinori Sato
 *
 * Hitachi SolutionEngine Support.
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <mach-se/mach/se7206.h>

#घोषणा INTSTS0 0x31800000
#घोषणा INTSTS1 0x31800002
#घोषणा INTMSK0 0x31800004
#घोषणा INTMSK1 0x31800006
#घोषणा INTSEL  0x31800008

#घोषणा IRQ0_IRQ 64
#घोषणा IRQ1_IRQ 65
#घोषणा IRQ3_IRQ 67

#घोषणा INTC_IPR01 0xfffe0818
#घोषणा INTC_ICR1  0xfffe0802

अटल व्योम disable_se7206_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	अचिन्हित लघु val;
	अचिन्हित लघु mask = 0xffff ^ (0x0f << 4 * (3 - (IRQ0_IRQ - irq)));
	अचिन्हित लघु msk0,msk1;

	/* Set the priority in IPR to 0 */
	val = __raw_पढ़ोw(INTC_IPR01);
	val &= mask;
	__raw_ग_लिखोw(val, INTC_IPR01);
	/* FPGA mask set */
	msk0 = __raw_पढ़ोw(INTMSK0);
	msk1 = __raw_पढ़ोw(INTMSK1);

	चयन (irq) अणु
	हाल IRQ0_IRQ:
		msk0 |= 0x0010;
		अवरोध;
	हाल IRQ1_IRQ:
		msk0 |= 0x000f;
		अवरोध;
	हाल IRQ3_IRQ:
		msk0 |= 0x0f00;
		msk1 |= 0x00ff;
		अवरोध;
	पूर्ण
	__raw_ग_लिखोw(msk0, INTMSK0);
	__raw_ग_लिखोw(msk1, INTMSK1);
पूर्ण

अटल व्योम enable_se7206_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	अचिन्हित लघु val;
	अचिन्हित लघु value = (0x0001 << 4 * (3 - (IRQ0_IRQ - irq)));
	अचिन्हित लघु msk0,msk1;

	/* Set priority in IPR back to original value */
	val = __raw_पढ़ोw(INTC_IPR01);
	val |= value;
	__raw_ग_लिखोw(val, INTC_IPR01);

	/* FPGA mask reset */
	msk0 = __raw_पढ़ोw(INTMSK0);
	msk1 = __raw_पढ़ोw(INTMSK1);

	चयन (irq) अणु
	हाल IRQ0_IRQ:
		msk0 &= ~0x0010;
		अवरोध;
	हाल IRQ1_IRQ:
		msk0 &= ~0x000f;
		अवरोध;
	हाल IRQ3_IRQ:
		msk0 &= ~0x0f00;
		msk1 &= ~0x00ff;
		अवरोध;
	पूर्ण
	__raw_ग_लिखोw(msk0, INTMSK0);
	__raw_ग_लिखोw(msk1, INTMSK1);
पूर्ण

अटल व्योम eoi_se7206_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित लघु sts0,sts1;
	अचिन्हित पूर्णांक irq = data->irq;

	अगर (!irqd_irq_disabled(data) && !irqd_irq_inprogress(data))
		enable_se7206_irq(data);
	/* FPGA isr clear */
	sts0 = __raw_पढ़ोw(INTSTS0);
	sts1 = __raw_पढ़ोw(INTSTS1);

	चयन (irq) अणु
	हाल IRQ0_IRQ:
		sts0 &= ~0x0010;
		अवरोध;
	हाल IRQ1_IRQ:
		sts0 &= ~0x000f;
		अवरोध;
	हाल IRQ3_IRQ:
		sts0 &= ~0x0f00;
		sts1 &= ~0x00ff;
		अवरोध;
	पूर्ण
	__raw_ग_लिखोw(sts0, INTSTS0);
	__raw_ग_लिखोw(sts1, INTSTS1);
पूर्ण

अटल काष्ठा irq_chip se7206_irq_chip __पढ़ो_mostly = अणु
	.name		= "SE7206-FPGA",
	.irq_mask	= disable_se7206_irq,
	.irq_unmask	= enable_se7206_irq,
	.irq_eoi	= eoi_se7206_irq,
पूर्ण;

अटल व्योम make_se7206_irq(अचिन्हित पूर्णांक irq)
अणु
	disable_irq_nosync(irq);
	irq_set_chip_and_handler_name(irq, &se7206_irq_chip,
				      handle_level_irq, "level");
	disable_se7206_irq(irq_get_irq_data(irq));
पूर्ण

/*
 * Initialize IRQ setting
 */
व्योम __init init_se7206_IRQ(व्योम)
अणु
	make_se7206_irq(IRQ0_IRQ); /* SMC91C111 */
	make_se7206_irq(IRQ1_IRQ); /* ATA */
	make_se7206_irq(IRQ3_IRQ); /* SLOT / PCM */

	__raw_ग_लिखोw(__raw_पढ़ोw(INTC_ICR1) | 0x000b, INTC_ICR1); /* ICR1 */

	/* FPGA System रेजिस्टर setup*/
	__raw_ग_लिखोw(0x0000,INTSTS0); /* Clear INTSTS0 */
	__raw_ग_लिखोw(0x0000,INTSTS1); /* Clear INTSTS1 */

	/* IRQ0=LAN, IRQ1=ATA, IRQ3=SLT,PCM */
	__raw_ग_लिखोw(0x0001,INTSEL);
पूर्ण
