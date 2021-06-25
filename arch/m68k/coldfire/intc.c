<शैली गुरु>
/*
 * पूर्णांकc.c  -- support क्रम the old ColdFire पूर्णांकerrupt controller
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
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>

/*
 * The mapping of irq number to a mask रेजिस्टर bit is not one-to-one.
 * The irq numbers are either based on "level" of पूर्णांकerrupt or fixed
 * क्रम an स्वतःvector-able पूर्णांकerrupt. So we keep a local data काष्ठाure
 * that maps from irq to mask रेजिस्टर. Not all पूर्णांकerrupts will have
 * an IMR bit.
 */
अचिन्हित अक्षर mcf_irq2imr[NR_IRQS];

/*
 * Define the miniumun and maximum बाह्यal पूर्णांकerrupt numbers.
 * This is also used as the "level" पूर्णांकerrupt numbers.
 */
#घोषणा	EIRQ1	25
#घोषणा	EIRQ7	31

/*
 * In the early version 2 core ColdFire parts the IMR रेजिस्टर was 16 bits
 * in size. Version 3 (and later version 2) core parts have a 32 bit
 * sized IMR रेजिस्टर. Provide some size independent methods to access the
 * IMR रेजिस्टर.
 */
#अगर_घोषित MCFSIM_IMR_IS_16BITS

व्योम mcf_setimr(पूर्णांक index)
अणु
	u16 imr;
	imr = __raw_पढ़ोw(MCFSIM_IMR);
	__raw_ग_लिखोw(imr | (0x1 << index), MCFSIM_IMR);
पूर्ण

व्योम mcf_clrimr(पूर्णांक index)
अणु
	u16 imr;
	imr = __raw_पढ़ोw(MCFSIM_IMR);
	__raw_ग_लिखोw(imr & ~(0x1 << index), MCFSIM_IMR);
पूर्ण

व्योम mcf_maskimr(अचिन्हित पूर्णांक mask)
अणु
	u16 imr;
	imr = __raw_पढ़ोw(MCFSIM_IMR);
	imr |= mask;
	__raw_ग_लिखोw(imr, MCFSIM_IMR);
पूर्ण

#अन्यथा

व्योम mcf_setimr(पूर्णांक index)
अणु
	u32 imr;
	imr = __raw_पढ़ोl(MCFSIM_IMR);
	__raw_ग_लिखोl(imr | (0x1 << index), MCFSIM_IMR);
पूर्ण

व्योम mcf_clrimr(पूर्णांक index)
अणु
	u32 imr;
	imr = __raw_पढ़ोl(MCFSIM_IMR);
	__raw_ग_लिखोl(imr & ~(0x1 << index), MCFSIM_IMR);
पूर्ण

व्योम mcf_maskimr(अचिन्हित पूर्णांक mask)
अणु
	u32 imr;
	imr = __raw_पढ़ोl(MCFSIM_IMR);
	imr |= mask;
	__raw_ग_लिखोl(imr, MCFSIM_IMR);
पूर्ण

#पूर्ण_अगर

/*
 * Interrupts can be "vectored" on the ColdFire cores that support this old
 * पूर्णांकerrupt controller. That is, the device raising the पूर्णांकerrupt can also
 * supply the vector number to पूर्णांकerrupt through. The AVR रेजिस्टर of the
 * पूर्णांकerrupt controller enables or disables this क्रम each बाह्यal पूर्णांकerrupt,
 * so provide generic support क्रम this. Setting this up is out-of-band क्रम
 * the पूर्णांकerrupt प्रणाली API's, and needs to be करोne by the driver that
 * supports this device. Very few devices actually use this.
 */
व्योम mcf_स्वतःvector(पूर्णांक irq)
अणु
#अगर_घोषित MCFSIM_AVR
	अगर ((irq >= EIRQ1) && (irq <= EIRQ7)) अणु
		u8 avec;
		avec = __raw_पढ़ोb(MCFSIM_AVR);
		avec |= (0x1 << (irq - EIRQ1 + 1));
		__raw_ग_लिखोb(avec, MCFSIM_AVR);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम पूर्णांकc_irq_mask(काष्ठा irq_data *d)
अणु
	अगर (mcf_irq2imr[d->irq])
		mcf_setimr(mcf_irq2imr[d->irq]);
पूर्ण

अटल व्योम पूर्णांकc_irq_unmask(काष्ठा irq_data *d)
अणु
	अगर (mcf_irq2imr[d->irq])
		mcf_clrimr(mcf_irq2imr[d->irq]);
पूर्ण

अटल पूर्णांक पूर्णांकc_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip पूर्णांकc_irq_chip = अणु
	.name		= "CF-INTC",
	.irq_mask	= पूर्णांकc_irq_mask,
	.irq_unmask	= पूर्णांकc_irq_unmask,
	.irq_set_type	= पूर्णांकc_irq_set_type,
पूर्ण;

व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक irq;

	mcf_maskimr(0xffffffff);

	क्रम (irq = 0; (irq < NR_IRQS); irq++) अणु
		irq_set_chip(irq, &पूर्णांकc_irq_chip);
		irq_set_irq_type(irq, IRQ_TYPE_LEVEL_HIGH);
		irq_set_handler(irq, handle_level_irq);
	पूर्ण
पूर्ण

