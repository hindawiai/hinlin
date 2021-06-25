<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C)2004-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/exception.h>

#समावेश "common.h"
#समावेश "hardware.h"
#समावेश "irq-common.h"

/*
 *****************************************
 * TZIC Registers                        *
 *****************************************
 */

#घोषणा TZIC_INTCNTL	0x0000	/* Control रेजिस्टर */
#घोषणा TZIC_INTTYPE	0x0004	/* Controller Type रेजिस्टर */
#घोषणा TZIC_IMPID	0x0008	/* Distributor Implementer Identअगरication */
#घोषणा TZIC_PRIOMASK	0x000C	/* Priority Mask Reg */
#घोषणा TZIC_SYNCCTRL	0x0010	/* Synchronizer Control रेजिस्टर */
#घोषणा TZIC_DSMINT	0x0014	/* DSM पूर्णांकerrupt Holकरोffरेजिस्टर */
#घोषणा TZIC_INTSEC0(i)	(0x0080 + ((i) << 2)) /* Interrupt Security Reg 0 */
#घोषणा TZIC_ENSET0(i)	(0x0100 + ((i) << 2)) /* Enable Set Reg 0 */
#घोषणा TZIC_ENCLEAR0(i) (0x0180 + ((i) << 2)) /* Enable Clear Reg 0 */
#घोषणा TZIC_SRCSET0	0x0200	/* Source Set Register 0 */
#घोषणा TZIC_SRCCLAR0	0x0280	/* Source Clear Register 0 */
#घोषणा TZIC_PRIORITY0	0x0400	/* Priority Register 0 */
#घोषणा TZIC_PND0	0x0D00	/* Pending Register 0 */
#घोषणा TZIC_HIPND(i)	(0x0D80+ ((i) << 2))	/* High Priority Pending Register */
#घोषणा TZIC_WAKEUP0(i)	(0x0E00 + ((i) << 2))	/* Wakeup Config Register */
#घोषणा TZIC_SWINT	0x0F00	/* Software Interrupt Rigger Register */
#घोषणा TZIC_ID0	0x0FD0	/* Indentअगरication Register 0 */

अटल व्योम __iomem *tzic_base;
अटल काष्ठा irq_करोमुख्य *करोमुख्य;

#घोषणा TZIC_NUM_IRQS 128

#अगर_घोषित CONFIG_FIQ
अटल पूर्णांक tzic_set_irq_fiq(अचिन्हित पूर्णांक hwirq, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक index, mask, value;

	index = hwirq >> 5;
	अगर (unlikely(index >= 4))
		वापस -EINVAL;
	mask = 1U << (hwirq & 0x1F);

	value = imx_पढ़ोl(tzic_base + TZIC_INTSEC0(index)) | mask;
	अगर (type)
		value &= ~mask;
	imx_ग_लिखोl(value, tzic_base + TZIC_INTSEC0(index));

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा tzic_set_irq_fiq शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल व्योम tzic_irq_suspend(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	पूर्णांक idx = d->hwirq >> 5;

	imx_ग_लिखोl(gc->wake_active, tzic_base + TZIC_WAKEUP0(idx));
पूर्ण

अटल व्योम tzic_irq_resume(काष्ठा irq_data *d)
अणु
	पूर्णांक idx = d->hwirq >> 5;

	imx_ग_लिखोl(imx_पढ़ोl(tzic_base + TZIC_ENSET0(idx)),
		   tzic_base + TZIC_WAKEUP0(idx));
पूर्ण

#अन्यथा
#घोषणा tzic_irq_suspend शून्य
#घोषणा tzic_irq_resume शून्य
#पूर्ण_अगर

अटल काष्ठा mxc_extra_irq tzic_extra_irq = अणु
#अगर_घोषित CONFIG_FIQ
	.set_irq_fiq = tzic_set_irq_fiq,
#पूर्ण_अगर
पूर्ण;

अटल __init व्योम tzic_init_gc(पूर्णांक idx, अचिन्हित पूर्णांक irq_start)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;

	gc = irq_alloc_generic_chip("tzic", 1, irq_start, tzic_base,
				    handle_level_irq);
	gc->निजी = &tzic_extra_irq;
	gc->wake_enabled = IRQ_MSK(32);

	ct = gc->chip_types;
	ct->chip.irq_mask = irq_gc_mask_disable_reg;
	ct->chip.irq_unmask = irq_gc_unmask_enable_reg;
	ct->chip.irq_set_wake = irq_gc_set_wake;
	ct->chip.irq_suspend = tzic_irq_suspend;
	ct->chip.irq_resume = tzic_irq_resume;
	ct->regs.disable = TZIC_ENCLEAR0(idx);
	ct->regs.enable = TZIC_ENSET0(idx);

	irq_setup_generic_chip(gc, IRQ_MSK(32), 0, IRQ_NOREQUEST, 0);
पूर्ण

अटल व्योम __exception_irq_entry tzic_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 stat;
	पूर्णांक i, irqofs, handled;

	करो अणु
		handled = 0;

		क्रम (i = 0; i < 4; i++) अणु
			stat = imx_पढ़ोl(tzic_base + TZIC_HIPND(i)) &
				imx_पढ़ोl(tzic_base + TZIC_INTSEC0(i));

			जबतक (stat) अणु
				handled = 1;
				irqofs = fls(stat) - 1;
				handle_करोमुख्य_irq(करोमुख्य, irqofs + i * 32, regs);
				stat &= ~(1 << irqofs);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (handled);
पूर्ण

/*
 * This function initializes the TZIC hardware and disables all the
 * पूर्णांकerrupts. It रेजिस्टरs the पूर्णांकerrupt enable and disable functions
 * to the kernel क्रम each पूर्णांकerrupt source.
 */
अटल पूर्णांक __init tzic_init_dt(काष्ठा device_node *np, काष्ठा device_node *p)
अणु
	पूर्णांक irq_base;
	पूर्णांक i;

	tzic_base = of_iomap(np, 0);
	WARN_ON(!tzic_base);

	/* put the TZIC पूर्णांकo the reset value with
	 * all पूर्णांकerrupts disabled
	 */
	i = imx_पढ़ोl(tzic_base + TZIC_INTCNTL);

	imx_ग_लिखोl(0x80010001, tzic_base + TZIC_INTCNTL);
	imx_ग_लिखोl(0x1f, tzic_base + TZIC_PRIOMASK);
	imx_ग_लिखोl(0x02, tzic_base + TZIC_SYNCCTRL);

	क्रम (i = 0; i < 4; i++)
		imx_ग_लिखोl(0xFFFFFFFF, tzic_base + TZIC_INTSEC0(i));

	/* disable all पूर्णांकerrupts */
	क्रम (i = 0; i < 4; i++)
		imx_ग_लिखोl(0xFFFFFFFF, tzic_base + TZIC_ENCLEAR0(i));

	/* all IRQ no FIQ Warning :: No selection */

	irq_base = irq_alloc_descs(-1, 0, TZIC_NUM_IRQS, numa_node_id());
	WARN_ON(irq_base < 0);

	करोमुख्य = irq_करोमुख्य_add_legacy(np, TZIC_NUM_IRQS, irq_base, 0,
				       &irq_करोमुख्य_simple_ops, शून्य);
	WARN_ON(!करोमुख्य);

	क्रम (i = 0; i < 4; i++, irq_base += 32)
		tzic_init_gc(i, irq_base);

	set_handle_irq(tzic_handle_irq);

#अगर_घोषित CONFIG_FIQ
	/* Initialize FIQ */
	init_FIQ(FIQ_START);
#पूर्ण_अगर

	pr_info("TrustZone Interrupt Controller (TZIC) initialized\n");

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(tzic, "fsl,tzic", tzic_init_dt);

/**
 * tzic_enable_wake() - enable wakeup पूर्णांकerrupt
 *
 * @वापस			0 अगर successful; non-zero otherwise
 *
 * This function provides an पूर्णांकerrupt synchronization poपूर्णांक that is required
 * by tzic enabled platक्रमms beक्रमe entering imx specअगरic low घातer modes (ie,
 * those low घातer modes beyond the WAIT_CLOCKED basic ARM WFI only mode).
 */
पूर्णांक tzic_enable_wake(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	imx_ग_लिखोl(1, tzic_base + TZIC_DSMINT);
	अगर (unlikely(imx_पढ़ोl(tzic_base + TZIC_DSMINT) == 0))
		वापस -EAGAIN;

	क्रम (i = 0; i < 4; i++)
		imx_ग_लिखोl(imx_पढ़ोl(tzic_base + TZIC_ENSET0(i)),
			   tzic_base + TZIC_WAKEUP0(i));

	वापस 0;
पूर्ण
