<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2003-2005 Simtec Electronics
//   Ben Dooks <ben@simtec.co.uk>
//
// http://www.simtec.co.uk/products/EB2410ITX/

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "regs-irq.h"
#समावेश <mach/irqs.h>

#समावेश "bast.h"

#घोषणा irqdbf(x...)
#घोषणा irqdbf2(x...)

/* handle PC104 ISA पूर्णांकerrupts from the प्रणाली CPLD */

/* table of ISA irq nos to the relevant mask... zero means
 * the irq is not implemented
*/
अटल स्थिर अचिन्हित अक्षर bast_pc104_irqmasks[] = अणु
	0,   /* 0 */
	0,   /* 1 */
	0,   /* 2 */
	1,   /* 3 */
	0,   /* 4 */
	2,   /* 5 */
	0,   /* 6 */
	4,   /* 7 */
	0,   /* 8 */
	0,   /* 9 */
	8,   /* 10 */
	0,   /* 11 */
	0,   /* 12 */
	0,   /* 13 */
	0,   /* 14 */
	0,   /* 15 */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर bast_pc104_irqs[] = अणु 3, 5, 7, 10 पूर्ण;

अटल व्योम
bast_pc104_mask(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ temp;

	temp = __raw_पढ़ोb(BAST_VA_PC104_IRQMASK);
	temp &= ~bast_pc104_irqmasks[data->irq];
	__raw_ग_लिखोb(temp, BAST_VA_PC104_IRQMASK);
पूर्ण

अटल व्योम
bast_pc104_maskack(काष्ठा irq_data *data)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(BAST_IRQ_ISA);

	bast_pc104_mask(data);
	desc->irq_data.chip->irq_ack(&desc->irq_data);
पूर्ण

अटल व्योम
bast_pc104_unmask(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ temp;

	temp = __raw_पढ़ोb(BAST_VA_PC104_IRQMASK);
	temp |= bast_pc104_irqmasks[data->irq];
	__raw_ग_लिखोb(temp, BAST_VA_PC104_IRQMASK);
पूर्ण

अटल काष्ठा irq_chip  bast_pc104_chip = अणु
	.irq_mask	= bast_pc104_mask,
	.irq_unmask	= bast_pc104_unmask,
	.irq_ack	= bast_pc104_maskack
पूर्ण;

अटल व्योम bast_irq_pc104_demux(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक stat;
	अचिन्हित पूर्णांक irqno;
	पूर्णांक i;

	stat = __raw_पढ़ोb(BAST_VA_PC104_IRQREQ) & 0xf;

	अगर (unlikely(stat == 0)) अणु
		/* ack अगर we get an irq with nothing (ie, startup) */
		desc->irq_data.chip->irq_ack(&desc->irq_data);
	पूर्ण अन्यथा अणु
		/* handle the IRQ */

		क्रम (i = 0; stat != 0; i++, stat >>= 1) अणु
			अगर (stat & 1) अणु
				irqno = bast_pc104_irqs[i];
				generic_handle_irq(irqno);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल __init पूर्णांक bast_irq_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	अगर (machine_is_bast()) अणु
		prपूर्णांकk(KERN_INFO "BAST PC104 IRQ routing, Copyright 2005 Simtec Electronics\n");

		/* zap all the IRQs */

		__raw_ग_लिखोb(0x0, BAST_VA_PC104_IRQMASK);

		irq_set_chained_handler(BAST_IRQ_ISA, bast_irq_pc104_demux);

		/* रेजिस्टर our IRQs */

		क्रम (i = 0; i < 4; i++) अणु
			अचिन्हित पूर्णांक irqno = bast_pc104_irqs[i];

			irq_set_chip_and_handler(irqno, &bast_pc104_chip,
						 handle_level_irq);
			irq_clear_status_flags(irqno, IRQ_NOREQUEST);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

arch_initcall(bast_irq_init);
