<शैली गुरु>
/*
 * पूर्णांकc-simr.c
 *
 * Interrupt controller code क्रम the ColdFire 5208, 5207 & 532x parts.
 *
 * (C) Copyright 2009-2011, Greg Ungerer <gerg@snapgear.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/traps.h>

/*
 *	The EDGE Port पूर्णांकerrupts are the fixed 7 बाह्यal पूर्णांकerrupts.
 *	They need some special treaपंचांगent, क्रम example they need to be acked.
 */
#अगर_घोषित CONFIG_M520x
/*
 *	The 520x parts only support a limited range of these बाह्यal
 *	पूर्णांकerrupts, only 1, 4 and 7 (as पूर्णांकerrupts 65, 66 and 67).
 */
#घोषणा	EINT0	64	/* Is not actually used, but spot reserved क्रम it */
#घोषणा	EINT1	65	/* EDGE Port पूर्णांकerrupt 1 */
#घोषणा	EINT4	66	/* EDGE Port पूर्णांकerrupt 4 */
#घोषणा	EINT7	67	/* EDGE Port पूर्णांकerrupt 7 */

अटल अचिन्हित पूर्णांक irqebiपंचांगap[] = अणु 0, 1, 4, 7 पूर्ण;
अटल अंतरभूत अचिन्हित पूर्णांक irq2ebit(अचिन्हित पूर्णांक irq)
अणु
	वापस irqebiपंचांगap[irq - EINT0];
पूर्ण

#अन्यथा

/*
 *	Most of the ColdFire parts with the EDGE Port module just have
 *	a strait direct mapping of the 7 बाह्यal पूर्णांकerrupts. Although
 *	there is a bit reserved क्रम 0, it is not used.
 */
#घोषणा	EINT0	64	/* Is not actually used, but spot reserved क्रम it */
#घोषणा	EINT1	65	/* EDGE Port पूर्णांकerrupt 1 */
#घोषणा	EINT7	71	/* EDGE Port पूर्णांकerrupt 7 */

अटल अंतरभूत अचिन्हित पूर्णांक irq2ebit(अचिन्हित पूर्णांक irq)
अणु
	वापस irq - EINT0;
पूर्ण

#पूर्ण_अगर

/*
 *	There maybe one, two or three पूर्णांकerrupt control units, each has 64
 *	पूर्णांकerrupts. If there is no second or third unit then MCFINTC1_* or
 *	MCFINTC2_* defines will be 0 (and code क्रम them optimized away).
 */

अटल व्योम पूर्णांकc_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - MCFINT_VECBASE;

	अगर (MCFINTC2_SIMR && (irq > 127))
		__raw_ग_लिखोb(irq - 128, MCFINTC2_SIMR);
	अन्यथा अगर (MCFINTC1_SIMR && (irq > 63))
		__raw_ग_लिखोb(irq - 64, MCFINTC1_SIMR);
	अन्यथा
		__raw_ग_लिखोb(irq, MCFINTC0_SIMR);
पूर्ण

अटल व्योम पूर्णांकc_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - MCFINT_VECBASE;

	अगर (MCFINTC2_CIMR && (irq > 127))
		__raw_ग_लिखोb(irq - 128, MCFINTC2_CIMR);
	अन्यथा अगर (MCFINTC1_CIMR && (irq > 63))
		__raw_ग_लिखोb(irq - 64, MCFINTC1_CIMR);
	अन्यथा
		__raw_ग_लिखोb(irq, MCFINTC0_CIMR);
पूर्ण

अटल व्योम पूर्णांकc_irq_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक ebit = irq2ebit(d->irq);

	__raw_ग_लिखोb(0x1 << ebit, MCFEPORT_EPFR);
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकc_irq_startup(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	अगर ((irq >= EINT1) && (irq <= EINT7)) अणु
		अचिन्हित पूर्णांक ebit = irq2ebit(irq);
		u8 v;

#अगर defined(MCFEPORT_EPDDR)
		/* Set EPORT line as input */
		v = __raw_पढ़ोb(MCFEPORT_EPDDR);
		__raw_ग_लिखोb(v & ~(0x1 << ebit), MCFEPORT_EPDDR);
#पूर्ण_अगर

		/* Set EPORT line as पूर्णांकerrupt source */
		v = __raw_पढ़ोb(MCFEPORT_EPIER);
		__raw_ग_लिखोb(v | (0x1 << ebit), MCFEPORT_EPIER);
	पूर्ण

	irq -= MCFINT_VECBASE;
	अगर (MCFINTC2_ICR0 && (irq > 127))
		__raw_ग_लिखोb(5, MCFINTC2_ICR0 + irq - 128);
	अन्यथा अगर (MCFINTC1_ICR0 && (irq > 63))
		__raw_ग_लिखोb(5, MCFINTC1_ICR0 + irq - 64);
	अन्यथा
		__raw_ग_लिखोb(5, MCFINTC0_ICR0 + irq);

	पूर्णांकc_irq_unmask(d);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकc_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक ebit, irq = d->irq;
	u16 pa, tb;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		tb = 0x1;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		tb = 0x2;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		tb = 0x3;
		अवरोध;
	शेष:
		/* Level triggered */
		tb = 0;
		अवरोध;
	पूर्ण

	अगर (tb)
		irq_set_handler(irq, handle_edge_irq);

	ebit = irq2ebit(irq) * 2;
	pa = __raw_पढ़ोw(MCFEPORT_EPPAR);
	pa = (pa & ~(0x3 << ebit)) | (tb << ebit);
	__raw_ग_लिखोw(pa, MCFEPORT_EPPAR);
	
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip पूर्णांकc_irq_chip = अणु
	.name		= "CF-INTC",
	.irq_startup	= पूर्णांकc_irq_startup,
	.irq_mask	= पूर्णांकc_irq_mask,
	.irq_unmask	= पूर्णांकc_irq_unmask,
पूर्ण;

अटल काष्ठा irq_chip पूर्णांकc_irq_chip_edge_port = अणु
	.name		= "CF-INTC-EP",
	.irq_startup	= पूर्णांकc_irq_startup,
	.irq_mask	= पूर्णांकc_irq_mask,
	.irq_unmask	= पूर्णांकc_irq_unmask,
	.irq_ack	= पूर्णांकc_irq_ack,
	.irq_set_type	= पूर्णांकc_irq_set_type,
पूर्ण;

व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक irq, eirq;

	/* Mask all पूर्णांकerrupt sources */
	__raw_ग_लिखोb(0xff, MCFINTC0_SIMR);
	अगर (MCFINTC1_SIMR)
		__raw_ग_लिखोb(0xff, MCFINTC1_SIMR);
	अगर (MCFINTC2_SIMR)
		__raw_ग_लिखोb(0xff, MCFINTC2_SIMR);

	eirq = MCFINT_VECBASE + 64 + (MCFINTC1_ICR0 ? 64 : 0) +
						(MCFINTC2_ICR0 ? 64 : 0);
	क्रम (irq = MCFINT_VECBASE; (irq < eirq); irq++) अणु
		अगर ((irq >= EINT1) && (irq <= EINT7))
			irq_set_chip(irq, &पूर्णांकc_irq_chip_edge_port);
		अन्यथा
			irq_set_chip(irq, &पूर्णांकc_irq_chip);
		irq_set_irq_type(irq, IRQ_TYPE_LEVEL_HIGH);
		irq_set_handler(irq, handle_level_irq);
	पूर्ण
पूर्ण

