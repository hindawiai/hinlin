<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Juergen Beisert, kernel@pengutronix.de
 */

#समावेश <linux/module.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/exception.h>

#समावेश "common.h"
#समावेश "hardware.h"
#समावेश "irq-common.h"

#घोषणा AVIC_INTCNTL		0x00	/* पूर्णांक control reg */
#घोषणा AVIC_NIMASK		0x04	/* पूर्णांक mask reg */
#घोषणा AVIC_INTENNUM		0x08	/* पूर्णांक enable number reg */
#घोषणा AVIC_INTDISNUM		0x0C	/* पूर्णांक disable number reg */
#घोषणा AVIC_INTENABLEH		0x10	/* पूर्णांक enable reg high */
#घोषणा AVIC_INTENABLEL		0x14	/* पूर्णांक enable reg low */
#घोषणा AVIC_INTTYPEH		0x18	/* पूर्णांक type reg high */
#घोषणा AVIC_INTTYPEL		0x1C	/* पूर्णांक type reg low */
#घोषणा AVIC_NIPRIORITY(x)	(0x20 + 4 * (7 - (x))) /* पूर्णांक priority */
#घोषणा AVIC_NIVECSR		0x40	/* norm पूर्णांक vector/status */
#घोषणा AVIC_FIVECSR		0x44	/* fast पूर्णांक vector/status */
#घोषणा AVIC_INTSRCH		0x48	/* पूर्णांक source reg high */
#घोषणा AVIC_INTSRCL		0x4C	/* पूर्णांक source reg low */
#घोषणा AVIC_INTFRCH		0x50	/* पूर्णांक क्रमce reg high */
#घोषणा AVIC_INTFRCL		0x54	/* पूर्णांक क्रमce reg low */
#घोषणा AVIC_NIPNDH		0x58	/* norm पूर्णांक pending high */
#घोषणा AVIC_NIPNDL		0x5C	/* norm पूर्णांक pending low */
#घोषणा AVIC_FIPNDH		0x60	/* fast पूर्णांक pending high */
#घोषणा AVIC_FIPNDL		0x64	/* fast पूर्णांक pending low */

#घोषणा AVIC_NUM_IRQS 64

/* low घातer पूर्णांकerrupt mask रेजिस्टरs */
#घोषणा MX25_CCM_LPIMR0	0x68
#घोषणा MX25_CCM_LPIMR1	0x6C

अटल व्योम __iomem *avic_base;
अटल व्योम __iomem *mx25_ccm_base;
अटल काष्ठा irq_करोमुख्य *करोमुख्य;

#अगर_घोषित CONFIG_FIQ
अटल पूर्णांक avic_set_irq_fiq(अचिन्हित पूर्णांक hwirq, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक irqt;

	अगर (hwirq >= AVIC_NUM_IRQS)
		वापस -EINVAL;

	अगर (hwirq < AVIC_NUM_IRQS / 2) अणु
		irqt = imx_पढ़ोl(avic_base + AVIC_INTTYPEL) & ~(1 << hwirq);
		imx_ग_लिखोl(irqt | (!!type << hwirq), avic_base + AVIC_INTTYPEL);
	पूर्ण अन्यथा अणु
		hwirq -= AVIC_NUM_IRQS / 2;
		irqt = imx_पढ़ोl(avic_base + AVIC_INTTYPEH) & ~(1 << hwirq);
		imx_ग_लिखोl(irqt | (!!type << hwirq), avic_base + AVIC_INTTYPEH);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_FIQ */


अटल काष्ठा mxc_extra_irq avic_extra_irq = अणु
#अगर_घोषित CONFIG_FIQ
	.set_irq_fiq = avic_set_irq_fiq,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल u32 avic_saved_mask_reg[2];

अटल व्योम avic_irq_suspend(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = gc->chip_types;
	पूर्णांक idx = d->hwirq >> 5;

	avic_saved_mask_reg[idx] = imx_पढ़ोl(avic_base + ct->regs.mask);
	imx_ग_लिखोl(gc->wake_active, avic_base + ct->regs.mask);

	अगर (mx25_ccm_base) अणु
		u8 offs = d->hwirq < AVIC_NUM_IRQS / 2 ?
			MX25_CCM_LPIMR0 : MX25_CCM_LPIMR1;
		/*
		 * The पूर्णांकerrupts which are still enabled will be used as wakeup
		 * sources. Allow those पूर्णांकerrupts in low-घातer mode.
		 * The LPIMR रेजिस्टरs use 0 to allow an पूर्णांकerrupt, the AVIC
		 * रेजिस्टरs use 1.
		 */
		imx_ग_लिखोl(~gc->wake_active, mx25_ccm_base + offs);
	पूर्ण
पूर्ण

अटल व्योम avic_irq_resume(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = gc->chip_types;
	पूर्णांक idx = d->hwirq >> 5;

	imx_ग_लिखोl(avic_saved_mask_reg[idx], avic_base + ct->regs.mask);

	अगर (mx25_ccm_base) अणु
		u8 offs = d->hwirq < AVIC_NUM_IRQS / 2 ?
			MX25_CCM_LPIMR0 : MX25_CCM_LPIMR1;

		imx_ग_लिखोl(0xffffffff, mx25_ccm_base + offs);
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा avic_irq_suspend शून्य
#घोषणा avic_irq_resume शून्य
#पूर्ण_अगर

अटल __init व्योम avic_init_gc(पूर्णांक idx, अचिन्हित पूर्णांक irq_start)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;

	gc = irq_alloc_generic_chip("mxc-avic", 1, irq_start, avic_base,
				    handle_level_irq);
	gc->निजी = &avic_extra_irq;
	gc->wake_enabled = IRQ_MSK(32);

	ct = gc->chip_types;
	ct->chip.irq_mask = irq_gc_mask_clr_bit;
	ct->chip.irq_unmask = irq_gc_mask_set_bit;
	ct->chip.irq_ack = irq_gc_mask_clr_bit;
	ct->chip.irq_set_wake = irq_gc_set_wake;
	ct->chip.irq_suspend = avic_irq_suspend;
	ct->chip.irq_resume = avic_irq_resume;
	ct->regs.mask = !idx ? AVIC_INTENABLEL : AVIC_INTENABLEH;
	ct->regs.ack = ct->regs.mask;

	irq_setup_generic_chip(gc, IRQ_MSK(32), 0, IRQ_NOREQUEST, 0);
पूर्ण

अटल व्योम __exception_irq_entry avic_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 nivector;

	करो अणु
		nivector = imx_पढ़ोl(avic_base + AVIC_NIVECSR) >> 16;
		अगर (nivector == 0xffff)
			अवरोध;

		handle_करोमुख्य_irq(करोमुख्य, nivector, regs);
	पूर्ण जबतक (1);
पूर्ण

/*
 * This function initializes the AVIC hardware and disables all the
 * पूर्णांकerrupts. It रेजिस्टरs the पूर्णांकerrupt enable and disable functions
 * to the kernel क्रम each पूर्णांकerrupt source.
 */
अटल व्योम __init mxc_init_irq(व्योम __iomem *irqbase)
अणु
	काष्ठा device_node *np;
	पूर्णांक irq_base;
	पूर्णांक i;

	avic_base = irqbase;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx25-ccm");
	mx25_ccm_base = of_iomap(np, 0);

	अगर (mx25_ccm_base) अणु
		/*
		 * By शेष, we mask all पूर्णांकerrupts. We set the actual mask
		 * beक्रमe we go पूर्णांकo low-घातer mode.
		 */
		imx_ग_लिखोl(0xffffffff, mx25_ccm_base + MX25_CCM_LPIMR0);
		imx_ग_लिखोl(0xffffffff, mx25_ccm_base + MX25_CCM_LPIMR1);
	पूर्ण

	/* put the AVIC पूर्णांकo the reset value with
	 * all पूर्णांकerrupts disabled
	 */
	imx_ग_लिखोl(0, avic_base + AVIC_INTCNTL);
	imx_ग_लिखोl(0x1f, avic_base + AVIC_NIMASK);

	/* disable all पूर्णांकerrupts */
	imx_ग_लिखोl(0, avic_base + AVIC_INTENABLEH);
	imx_ग_लिखोl(0, avic_base + AVIC_INTENABLEL);

	/* all IRQ no FIQ */
	imx_ग_लिखोl(0, avic_base + AVIC_INTTYPEH);
	imx_ग_लिखोl(0, avic_base + AVIC_INTTYPEL);

	irq_base = irq_alloc_descs(-1, 0, AVIC_NUM_IRQS, numa_node_id());
	WARN_ON(irq_base < 0);

	np = of_find_compatible_node(शून्य, शून्य, "fsl,avic");
	करोमुख्य = irq_करोमुख्य_add_legacy(np, AVIC_NUM_IRQS, irq_base, 0,
				       &irq_करोमुख्य_simple_ops, शून्य);
	WARN_ON(!करोमुख्य);

	क्रम (i = 0; i < AVIC_NUM_IRQS / 32; i++, irq_base += 32)
		avic_init_gc(i, irq_base);

	/* Set शेष priority value (0) क्रम all IRQ's */
	क्रम (i = 0; i < 8; i++)
		imx_ग_लिखोl(0, avic_base + AVIC_NIPRIORITY(i));

	set_handle_irq(avic_handle_irq);

#अगर_घोषित CONFIG_FIQ
	/* Initialize FIQ */
	init_FIQ(FIQ_START);
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO "MXC IRQ initialized\n");
पूर्ण

अटल पूर्णांक __init imx_avic_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	व्योम __iomem *avic_base;

	avic_base = of_iomap(node, 0);
	BUG_ON(!avic_base);
	mxc_init_irq(avic_base);
	वापस 0;
पूर्ण

IRQCHIP_DECLARE(imx_avic, "fsl,avic", imx_avic_init);
