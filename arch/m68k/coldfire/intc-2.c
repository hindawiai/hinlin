<शैली गुरु>
/*
 * पूर्णांकc-2.c
 *
 * General पूर्णांकerrupt controller code क्रम the many ColdFire cores that use
 * पूर्णांकerrupt controllers with 63 पूर्णांकerrupt sources, organized as 56 fully-
 * programmable + 7 fixed-level पूर्णांकerrupt sources. This includes the 523x
 * family, the 5270, 5271, 5274, 5275, and the 528x family which have two such
 * controllers, and the 547x and 548x families which have only one of them.
 *
 * The बाह्यal 7 fixed पूर्णांकerrupts are part the the Edge Port unit of these
 * ColdFire parts. They can be configured as level or edge triggered.
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
 * Bit definitions क्रम the ICR family of रेजिस्टरs.
 */
#घोषणा MCFSIM_ICR_LEVEL(l)	((l)<<3)	/* Level l पूर्णांकr */
#घोषणा MCFSIM_ICR_PRI(p)	(p)		/* Priority p पूर्णांकr */

/*
 *	The EDGE Port पूर्णांकerrupts are the fixed 7 बाह्यal पूर्णांकerrupts.
 *	They need some special treaपंचांगent, क्रम example they need to be acked.
 */
#घोषणा	EINT0	64	/* Is not actually used, but spot reserved क्रम it */
#घोषणा	EINT1	65	/* EDGE Port पूर्णांकerrupt 1 */
#घोषणा	EINT7	71	/* EDGE Port पूर्णांकerrupt 7 */

#अगर_घोषित MCFICM_INTC1
#घोषणा NR_VECS	128
#अन्यथा
#घोषणा NR_VECS	64
#पूर्ण_अगर

अटल व्योम पूर्णांकc_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - MCFINT_VECBASE;
	अचिन्हित दीर्घ imraddr;
	u32 val, imrbit;

#अगर_घोषित MCFICM_INTC1
	imraddr = (irq & 0x40) ? MCFICM_INTC1 : MCFICM_INTC0;
#अन्यथा
	imraddr = MCFICM_INTC0;
#पूर्ण_अगर
	imraddr += (irq & 0x20) ? MCFINTC_IMRH : MCFINTC_IMRL;
	imrbit = 0x1 << (irq & 0x1f);

	val = __raw_पढ़ोl(imraddr);
	__raw_ग_लिखोl(val | imrbit, imraddr);
पूर्ण

अटल व्योम पूर्णांकc_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - MCFINT_VECBASE;
	अचिन्हित दीर्घ imraddr;
	u32 val, imrbit;

#अगर_घोषित MCFICM_INTC1
	imraddr = (irq & 0x40) ? MCFICM_INTC1 : MCFICM_INTC0;
#अन्यथा
	imraddr = MCFICM_INTC0;
#पूर्ण_अगर
	imraddr += ((irq & 0x20) ? MCFINTC_IMRH : MCFINTC_IMRL);
	imrbit = 0x1 << (irq & 0x1f);

	/* Don't set the "maskall" bit! */
	अगर ((irq & 0x20) == 0)
		imrbit |= 0x1;

	val = __raw_पढ़ोl(imraddr);
	__raw_ग_लिखोl(val & ~imrbit, imraddr);
पूर्ण

/*
 *	Only the बाह्यal (or EDGE Port) पूर्णांकerrupts need to be acknowledged
 *	here, as part of the IRQ handler. They only really need to be ack'ed
 *	अगर they are in edge triggered mode, but there is no harm in करोing it
 *	क्रम all types.
 */
अटल व्योम पूर्णांकc_irq_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	__raw_ग_लिखोb(0x1 << (irq - EINT0), MCFEPORT_EPFR);
पूर्ण

/*
 *	Each vector needs a unique priority and level associated with it.
 *	We करोn't really care so much what they are, we don't rely on the
 *	traditional priority पूर्णांकerrupt scheme of the m68k/ColdFire. This
 *	only needs to be set once क्रम an पूर्णांकerrupt, and we will never change
 *	these values once we have set them.
 */
अटल u8 पूर्णांकc_पूर्णांकpri = MCFSIM_ICR_LEVEL(6) | MCFSIM_ICR_PRI(6);

अटल अचिन्हित पूर्णांक पूर्णांकc_irq_startup(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - MCFINT_VECBASE;
	अचिन्हित दीर्घ icraddr;

#अगर_घोषित MCFICM_INTC1
	icraddr = (irq & 0x40) ? MCFICM_INTC1 : MCFICM_INTC0;
#अन्यथा
	icraddr = MCFICM_INTC0;
#पूर्ण_अगर
	icraddr += MCFINTC_ICR0 + (irq & 0x3f);
	अगर (__raw_पढ़ोb(icraddr) == 0)
		__raw_ग_लिखोb(पूर्णांकc_पूर्णांकpri--, icraddr);

	irq = d->irq;
	अगर ((irq >= EINT1) && (irq <= EINT7)) अणु
		u8 v;

		irq -= EINT0;

		/* Set EPORT line as input */
		v = __raw_पढ़ोb(MCFEPORT_EPDDR);
		__raw_ग_लिखोb(v & ~(0x1 << irq), MCFEPORT_EPDDR);

		/* Set EPORT line as पूर्णांकerrupt source */
		v = __raw_पढ़ोb(MCFEPORT_EPIER);
		__raw_ग_लिखोb(v | (0x1 << irq), MCFEPORT_EPIER);
	पूर्ण

	पूर्णांकc_irq_unmask(d);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकc_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
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

	irq -= EINT0;
	pa = __raw_पढ़ोw(MCFEPORT_EPPAR);
	pa = (pa & ~(0x3 << (irq * 2))) | (tb << (irq * 2));
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
	पूर्णांक irq;

	/* Mask all पूर्णांकerrupt sources */
	__raw_ग_लिखोl(0x1, MCFICM_INTC0 + MCFINTC_IMRL);
#अगर_घोषित MCFICM_INTC1
	__raw_ग_लिखोl(0x1, MCFICM_INTC1 + MCFINTC_IMRL);
#पूर्ण_अगर

	क्रम (irq = MCFINT_VECBASE; (irq < MCFINT_VECBASE + NR_VECS); irq++) अणु
		अगर ((irq >= EINT1) && (irq <=EINT7))
			irq_set_chip(irq, &पूर्णांकc_irq_chip_edge_port);
		अन्यथा
			irq_set_chip(irq, &पूर्णांकc_irq_chip);
		irq_set_irq_type(irq, IRQ_TYPE_LEVEL_HIGH);
		irq_set_handler(irq, handle_level_irq);
	पूर्ण
पूर्ण

