<शैली गुरु>
/*
 * पूर्णांकc.c  --  पूर्णांकerrupt controller or ColdFire 5272 SoC
 *
 * (C) Copyright 2009, Greg Ungerer <gerg@snapgear.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/traps.h>

/*
 * The 5272 ColdFire पूर्णांकerrupt controller is nothing like any other
 * ColdFire पूर्णांकerrupt controller - it truly is completely dअगरferent.
 * Given its age it is unlikely to be used on any other ColdFire CPU.
 */

/*
 * The masking and priproty setting of पूर्णांकerrupts on the 5272 is करोne
 * via a set of 4 "Interrupt Controller Registers" (ICR). There is a
 * loose mapping of vector number to रेजिस्टर and पूर्णांकernal bits, but
 * a table is the easiest and quickest way to map them.
 *
 * Note that the बाह्यal पूर्णांकerrupts are edge triggered (unlike the
 * पूर्णांकernal पूर्णांकerrupt sources which are level triggered). Which means
 * they also need acknowledging via acknowledge bits.
 */
काष्ठा irqmap अणु
	अचिन्हित पूर्णांक	icr;
	अचिन्हित अक्षर	index;
	अचिन्हित अक्षर	ack;
पूर्ण;

अटल काष्ठा irqmap पूर्णांकc_irqmap[MCFINT_VECMAX - MCFINT_VECBASE] = अणु
	/*MCF_IRQ_SPURIOUS*/	अणु .icr = 0,           .index = 0,  .ack = 0, पूर्ण,
	/*MCF_IRQ_EINT1*/	अणु .icr = MCFSIM_ICR1, .index = 28, .ack = 1, पूर्ण,
	/*MCF_IRQ_EINT2*/	अणु .icr = MCFSIM_ICR1, .index = 24, .ack = 1, पूर्ण,
	/*MCF_IRQ_EINT3*/	अणु .icr = MCFSIM_ICR1, .index = 20, .ack = 1, पूर्ण,
	/*MCF_IRQ_EINT4*/	अणु .icr = MCFSIM_ICR1, .index = 16, .ack = 1, पूर्ण,
	/*MCF_IRQ_TIMER1*/	अणु .icr = MCFSIM_ICR1, .index = 12, .ack = 0, पूर्ण,
	/*MCF_IRQ_TIMER2*/	अणु .icr = MCFSIM_ICR1, .index = 8,  .ack = 0, पूर्ण,
	/*MCF_IRQ_TIMER3*/	अणु .icr = MCFSIM_ICR1, .index = 4,  .ack = 0, पूर्ण,
	/*MCF_IRQ_TIMER4*/	अणु .icr = MCFSIM_ICR1, .index = 0,  .ack = 0, पूर्ण,
	/*MCF_IRQ_UART1*/	अणु .icr = MCFSIM_ICR2, .index = 28, .ack = 0, पूर्ण,
	/*MCF_IRQ_UART2*/	अणु .icr = MCFSIM_ICR2, .index = 24, .ack = 0, पूर्ण,
	/*MCF_IRQ_PLIP*/	अणु .icr = MCFSIM_ICR2, .index = 20, .ack = 0, पूर्ण,
	/*MCF_IRQ_PLIA*/	अणु .icr = MCFSIM_ICR2, .index = 16, .ack = 0, पूर्ण,
	/*MCF_IRQ_USB0*/	अणु .icr = MCFSIM_ICR2, .index = 12, .ack = 0, पूर्ण,
	/*MCF_IRQ_USB1*/	अणु .icr = MCFSIM_ICR2, .index = 8,  .ack = 0, पूर्ण,
	/*MCF_IRQ_USB2*/	अणु .icr = MCFSIM_ICR2, .index = 4,  .ack = 0, पूर्ण,
	/*MCF_IRQ_USB3*/	अणु .icr = MCFSIM_ICR2, .index = 0,  .ack = 0, पूर्ण,
	/*MCF_IRQ_USB4*/	अणु .icr = MCFSIM_ICR3, .index = 28, .ack = 0, पूर्ण,
	/*MCF_IRQ_USB5*/	अणु .icr = MCFSIM_ICR3, .index = 24, .ack = 0, पूर्ण,
	/*MCF_IRQ_USB6*/	अणु .icr = MCFSIM_ICR3, .index = 20, .ack = 0, पूर्ण,
	/*MCF_IRQ_USB7*/	अणु .icr = MCFSIM_ICR3, .index = 16, .ack = 0, पूर्ण,
	/*MCF_IRQ_DMA*/		अणु .icr = MCFSIM_ICR3, .index = 12, .ack = 0, पूर्ण,
	/*MCF_IRQ_ERX*/		अणु .icr = MCFSIM_ICR3, .index = 8,  .ack = 0, पूर्ण,
	/*MCF_IRQ_ETX*/		अणु .icr = MCFSIM_ICR3, .index = 4,  .ack = 0, पूर्ण,
	/*MCF_IRQ_ENTC*/	अणु .icr = MCFSIM_ICR3, .index = 0,  .ack = 0, पूर्ण,
	/*MCF_IRQ_QSPI*/	अणु .icr = MCFSIM_ICR4, .index = 28, .ack = 0, पूर्ण,
	/*MCF_IRQ_EINT5*/	अणु .icr = MCFSIM_ICR4, .index = 24, .ack = 1, पूर्ण,
	/*MCF_IRQ_EINT6*/	अणु .icr = MCFSIM_ICR4, .index = 20, .ack = 1, पूर्ण,
	/*MCF_IRQ_SWTO*/	अणु .icr = MCFSIM_ICR4, .index = 16, .ack = 0, पूर्ण,
पूर्ण;

/*
 * The act of masking the पूर्णांकerrupt also has a side effect of 'ack'ing
 * an पूर्णांकerrupt on this irq (क्रम the बाह्यal irqs). So this mask function
 * is also an ack_mask function.
 */
अटल व्योम पूर्णांकc_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	अगर ((irq >= MCFINT_VECBASE) && (irq <= MCFINT_VECMAX)) अणु
		u32 v;
		irq -= MCFINT_VECBASE;
		v = 0x8 << पूर्णांकc_irqmap[irq].index;
		ग_लिखोl(v, पूर्णांकc_irqmap[irq].icr);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकc_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	अगर ((irq >= MCFINT_VECBASE) && (irq <= MCFINT_VECMAX)) अणु
		u32 v;
		irq -= MCFINT_VECBASE;
		v = 0xd << पूर्णांकc_irqmap[irq].index;
		ग_लिखोl(v, पूर्णांकc_irqmap[irq].icr);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकc_irq_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	/* Only बाह्यal पूर्णांकerrupts are acked */
	अगर ((irq >= MCFINT_VECBASE) && (irq <= MCFINT_VECMAX)) अणु
		irq -= MCFINT_VECBASE;
		अगर (पूर्णांकc_irqmap[irq].ack) अणु
			u32 v;
			v = पढ़ोl(पूर्णांकc_irqmap[irq].icr);
			v &= (0x7 << पूर्णांकc_irqmap[irq].index);
			v |= (0x8 << पूर्णांकc_irqmap[irq].index);
			ग_लिखोl(v, पूर्णांकc_irqmap[irq].icr);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकc_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	अगर ((irq >= MCFINT_VECBASE) && (irq <= MCFINT_VECMAX)) अणु
		irq -= MCFINT_VECBASE;
		अगर (पूर्णांकc_irqmap[irq].ack) अणु
			u32 v;
			v = पढ़ोl(MCFSIM_PITR);
			अगर (type == IRQ_TYPE_EDGE_FALLING)
				v &= ~(0x1 << (32 - irq));
			अन्यथा
				v |= (0x1 << (32 - irq));
			ग_लिखोl(v, MCFSIM_PITR);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Simple flow handler to deal with the बाह्यal edge triggered पूर्णांकerrupts.
 * We need to be careful with the masking/acking due to the side effects
 * of masking an पूर्णांकerrupt.
 */
अटल व्योम पूर्णांकc_बाह्यal_irq(काष्ठा irq_desc *desc)
अणु
	irq_desc_get_chip(desc)->irq_ack(&desc->irq_data);
	handle_simple_irq(desc);
पूर्ण

अटल काष्ठा irq_chip पूर्णांकc_irq_chip = अणु
	.name		= "CF-INTC",
	.irq_mask	= पूर्णांकc_irq_mask,
	.irq_unmask	= पूर्णांकc_irq_unmask,
	.irq_mask_ack	= पूर्णांकc_irq_mask,
	.irq_ack	= पूर्णांकc_irq_ack,
	.irq_set_type	= पूर्णांकc_irq_set_type,
पूर्ण;

व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक irq, edge;

	/* Mask all पूर्णांकerrupt sources */
	ग_लिखोl(0x88888888, MCFSIM_ICR1);
	ग_लिखोl(0x88888888, MCFSIM_ICR2);
	ग_लिखोl(0x88888888, MCFSIM_ICR3);
	ग_लिखोl(0x88888888, MCFSIM_ICR4);

	क्रम (irq = 0; (irq < NR_IRQS); irq++) अणु
		irq_set_chip(irq, &पूर्णांकc_irq_chip);
		edge = 0;
		अगर ((irq >= MCFINT_VECBASE) && (irq <= MCFINT_VECMAX))
			edge = पूर्णांकc_irqmap[irq - MCFINT_VECBASE].ack;
		अगर (edge) अणु
			irq_set_irq_type(irq, IRQ_TYPE_EDGE_RISING);
			irq_set_handler(irq, पूर्णांकc_बाह्यal_irq);
		पूर्ण अन्यथा अणु
			irq_set_irq_type(irq, IRQ_TYPE_LEVEL_HIGH);
			irq_set_handler(irq, handle_level_irq);
		पूर्ण
	पूर्ण
पूर्ण

