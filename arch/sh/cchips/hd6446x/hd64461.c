<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Copyright (C) 2000 YAEGASHI Takeshi
 *	Hitachi HD64461 companion chip support
 */

#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hd64461.h>

/* This beदीर्घs in cpu specअगरic */
#घोषणा INTC_ICR1 0xA4140010UL

अटल व्योम hd64461_mask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	अचिन्हित लघु nimr;
	अचिन्हित लघु mask = 1 << (irq - HD64461_IRQBASE);

	nimr = __raw_पढ़ोw(HD64461_NIMR);
	nimr |= mask;
	__raw_ग_लिखोw(nimr, HD64461_NIMR);
पूर्ण

अटल व्योम hd64461_unmask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	अचिन्हित लघु nimr;
	अचिन्हित लघु mask = 1 << (irq - HD64461_IRQBASE);

	nimr = __raw_पढ़ोw(HD64461_NIMR);
	nimr &= ~mask;
	__raw_ग_लिखोw(nimr, HD64461_NIMR);
पूर्ण

अटल व्योम hd64461_mask_and_ack_irq(काष्ठा irq_data *data)
अणु
	hd64461_mask_irq(data);

#अगर_घोषित CONFIG_HD64461_ENABLER
	अगर (data->irq == HD64461_IRQBASE + 13)
		__raw_ग_लिखोb(0x00, HD64461_PCC1CSCR);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा irq_chip hd64461_irq_chip = अणु
	.name		= "HD64461-IRQ",
	.irq_mask	= hd64461_mask_irq,
	.irq_mask_ack	= hd64461_mask_and_ack_irq,
	.irq_unmask	= hd64461_unmask_irq,
पूर्ण;

अटल व्योम hd64461_irq_demux(काष्ठा irq_desc *desc)
अणु
	अचिन्हित लघु पूर्णांकv = __raw_पढ़ोw(HD64461_NIRR);
	अचिन्हित पूर्णांक ext_irq = HD64461_IRQBASE;

	पूर्णांकv &= (1 << HD64461_IRQ_NUM) - 1;

	क्रम (; पूर्णांकv; पूर्णांकv >>= 1, ext_irq++) अणु
		अगर (!(पूर्णांकv & 1))
			जारी;

		generic_handle_irq(ext_irq);
	पूर्ण
पूर्ण

पूर्णांक __init setup_hd64461(व्योम)
अणु
	पूर्णांक irq_base, i;

	prपूर्णांकk(KERN_INFO
	       "HD64461 configured at 0x%x on irq %d(mapped into %d to %d)\n",
	       HD64461_IOBASE, CONFIG_HD64461_IRQ, HD64461_IRQBASE,
	       HD64461_IRQBASE + 15);

/* Should be at processor specअगरic part.. */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7709)
	__raw_ग_लिखोw(0x2240, INTC_ICR1);
#पूर्ण_अगर
	__raw_ग_लिखोw(0xffff, HD64461_NIMR);

	irq_base = irq_alloc_descs(HD64461_IRQBASE, HD64461_IRQBASE, 16, -1);
	अगर (IS_ERR_VALUE(irq_base)) अणु
		pr_err("%s: failed hooking irqs for HD64461\n", __func__);
		वापस irq_base;
	पूर्ण

	क्रम (i = 0; i < 16; i++)
		irq_set_chip_and_handler(irq_base + i, &hd64461_irq_chip,
					 handle_level_irq);

	irq_set_chained_handler(CONFIG_HD64461_IRQ, hd64461_irq_demux);
	irq_set_irq_type(CONFIG_HD64461_IRQ, IRQ_TYPE_LEVEL_LOW);

#अगर_घोषित CONFIG_HD64461_ENABLER
	prपूर्णांकk(KERN_INFO "HD64461: enabling PCMCIA devices\n");
	__raw_ग_लिखोb(0x4c, HD64461_PCC1CSCIER);
	__raw_ग_लिखोb(0x00, HD64461_PCC1CSCR);
#पूर्ण_अगर

	वापस 0;
पूर्ण

module_init(setup_hd64461);
