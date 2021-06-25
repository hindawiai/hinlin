<शैली गुरु>
/*
 * Aपंचांगel AT91 AIC (Advanced Interrupt Controller) driver
 *
 *  Copyright (C) 2004 SAN People
 *  Copyright (C) 2004 ATMEL
 *  Copyright (C) Rick Bronson
 *  Copyright (C) 2014 Free Electrons
 *
 *  Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/types.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "irq-atmel-aic-common.h"

/* Number of irq lines managed by AIC */
#घोषणा NR_AIC_IRQS	32

#घोषणा AT91_AIC_SMR(n)			((n) * 4)

#घोषणा AT91_AIC_SVR(n)			(0x80 + ((n) * 4))
#घोषणा AT91_AIC_IVR			0x100
#घोषणा AT91_AIC_FVR			0x104
#घोषणा AT91_AIC_ISR			0x108

#घोषणा AT91_AIC_IPR			0x10c
#घोषणा AT91_AIC_IMR			0x110
#घोषणा AT91_AIC_CISR			0x114

#घोषणा AT91_AIC_IECR			0x120
#घोषणा AT91_AIC_IDCR			0x124
#घोषणा AT91_AIC_ICCR			0x128
#घोषणा AT91_AIC_ISCR			0x12c
#घोषणा AT91_AIC_EOICR			0x130
#घोषणा AT91_AIC_SPU			0x134
#घोषणा AT91_AIC_DCR			0x138

अटल काष्ठा irq_करोमुख्य *aic_करोमुख्य;

अटल यंत्रlinkage व्योम __exception_irq_entry
aic_handle(काष्ठा pt_regs *regs)
अणु
	काष्ठा irq_करोमुख्य_chip_generic *dgc = aic_करोमुख्य->gc;
	काष्ठा irq_chip_generic *gc = dgc->gc[0];
	u32 irqnr;
	u32 irqstat;

	irqnr = irq_reg_पढ़ोl(gc, AT91_AIC_IVR);
	irqstat = irq_reg_पढ़ोl(gc, AT91_AIC_ISR);

	अगर (!irqstat)
		irq_reg_ग_लिखोl(gc, 0, AT91_AIC_EOICR);
	अन्यथा
		handle_करोमुख्य_irq(aic_करोमुख्य, irqnr, regs);
पूर्ण

अटल पूर्णांक aic_retrigger(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);

	/* Enable पूर्णांकerrupt on AIC5 */
	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, d->mask, AT91_AIC_ISCR);
	irq_gc_unlock(gc);

	वापस 1;
पूर्ण

अटल पूर्णांक aic_set_type(काष्ठा irq_data *d, अचिन्हित type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक smr;
	पूर्णांक ret;

	smr = irq_reg_पढ़ोl(gc, AT91_AIC_SMR(d->hwirq));
	ret = aic_common_set_type(d, type, &smr);
	अगर (ret)
		वापस ret;

	irq_reg_ग_लिखोl(gc, smr, AT91_AIC_SMR(d->hwirq));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम aic_suspend(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, gc->mask_cache, AT91_AIC_IDCR);
	irq_reg_ग_लिखोl(gc, gc->wake_active, AT91_AIC_IECR);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम aic_resume(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, gc->wake_active, AT91_AIC_IDCR);
	irq_reg_ग_लिखोl(gc, gc->mask_cache, AT91_AIC_IECR);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम aic_pm_shutकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, 0xffffffff, AT91_AIC_IDCR);
	irq_reg_ग_लिखोl(gc, 0xffffffff, AT91_AIC_ICCR);
	irq_gc_unlock(gc);
पूर्ण
#अन्यथा
#घोषणा aic_suspend		शून्य
#घोषणा aic_resume		शून्य
#घोषणा aic_pm_shutकरोwn		शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम __init aic_hw_init(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा irq_chip_generic *gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	पूर्णांक i;

	/*
	 * Perक्रमm 8 End Of Interrupt Command to make sure AIC
	 * will not Lock out nIRQ
	 */
	क्रम (i = 0; i < 8; i++)
		irq_reg_ग_लिखोl(gc, 0, AT91_AIC_EOICR);

	/*
	 * Spurious Interrupt ID in Spurious Vector Register.
	 * When there is no current पूर्णांकerrupt, the IRQ Vector Register
	 * पढ़ोs the value stored in AIC_SPU
	 */
	irq_reg_ग_लिखोl(gc, 0xffffffff, AT91_AIC_SPU);

	/* No debugging in AIC: Debug (Protect) Control Register */
	irq_reg_ग_लिखोl(gc, 0, AT91_AIC_DCR);

	/* Disable and clear all पूर्णांकerrupts initially */
	irq_reg_ग_लिखोl(gc, 0xffffffff, AT91_AIC_IDCR);
	irq_reg_ग_लिखोl(gc, 0xffffffff, AT91_AIC_ICCR);

	क्रम (i = 0; i < 32; i++)
		irq_reg_ग_लिखोl(gc, i, AT91_AIC_SVR(i));
पूर्ण

अटल पूर्णांक aic_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
				काष्ठा device_node *ctrlr,
				स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				irq_hw_number_t *out_hwirq,
				अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा irq_करोमुख्य_chip_generic *dgc = d->gc;
	काष्ठा irq_chip_generic *gc;
	अचिन्हित दीर्घ flags;
	अचिन्हित smr;
	पूर्णांक idx;
	पूर्णांक ret;

	अगर (!dgc)
		वापस -EINVAL;

	ret = aic_common_irq_करोमुख्य_xlate(d, ctrlr, पूर्णांकspec, पूर्णांकsize,
					  out_hwirq, out_type);
	अगर (ret)
		वापस ret;

	idx = पूर्णांकspec[0] / dgc->irqs_per_chip;
	अगर (idx >= dgc->num_chips)
		वापस -EINVAL;

	gc = dgc->gc[idx];

	irq_gc_lock_irqsave(gc, flags);
	smr = irq_reg_पढ़ोl(gc, AT91_AIC_SMR(*out_hwirq));
	aic_common_set_priority(पूर्णांकspec[2], &smr);
	irq_reg_ग_लिखोl(gc, smr, AT91_AIC_SMR(*out_hwirq));
	irq_gc_unlock_irqrestore(gc, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops aic_irq_ops = अणु
	.map	= irq_map_generic_chip,
	.xlate	= aic_irq_करोमुख्य_xlate,
पूर्ण;

अटल व्योम __init at91rm9200_aic_irq_fixup(व्योम)
अणु
	aic_common_rtc_irq_fixup();
पूर्ण

अटल व्योम __init at91sam9260_aic_irq_fixup(व्योम)
अणु
	aic_common_rtt_irq_fixup();
पूर्ण

अटल व्योम __init at91sam9g45_aic_irq_fixup(व्योम)
अणु
	aic_common_rtc_irq_fixup();
	aic_common_rtt_irq_fixup();
पूर्ण

अटल स्थिर काष्ठा of_device_id aic_irq_fixups[] __initस्थिर = अणु
	अणु .compatible = "atmel,at91rm9200", .data = at91rm9200_aic_irq_fixup पूर्ण,
	अणु .compatible = "atmel,at91sam9g45", .data = at91sam9g45_aic_irq_fixup पूर्ण,
	अणु .compatible = "atmel,at91sam9n12", .data = at91rm9200_aic_irq_fixup पूर्ण,
	अणु .compatible = "atmel,at91sam9rl", .data = at91sam9g45_aic_irq_fixup पूर्ण,
	अणु .compatible = "atmel,at91sam9x5", .data = at91rm9200_aic_irq_fixup पूर्ण,
	अणु .compatible = "atmel,at91sam9260", .data = at91sam9260_aic_irq_fixup पूर्ण,
	अणु .compatible = "atmel,at91sam9261", .data = at91sam9260_aic_irq_fixup पूर्ण,
	अणु .compatible = "atmel,at91sam9263", .data = at91sam9260_aic_irq_fixup पूर्ण,
	अणु .compatible = "atmel,at91sam9g20", .data = at91sam9260_aic_irq_fixup पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक __init aic_of_init(काष्ठा device_node *node,
			      काष्ठा device_node *parent)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (aic_करोमुख्य)
		वापस -EEXIST;

	करोमुख्य = aic_common_of_init(node, &aic_irq_ops, "atmel-aic",
				    NR_AIC_IRQS, aic_irq_fixups);
	अगर (IS_ERR(करोमुख्य))
		वापस PTR_ERR(करोमुख्य);

	aic_करोमुख्य = करोमुख्य;
	gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);

	gc->chip_types[0].regs.eoi = AT91_AIC_EOICR;
	gc->chip_types[0].regs.enable = AT91_AIC_IECR;
	gc->chip_types[0].regs.disable = AT91_AIC_IDCR;
	gc->chip_types[0].chip.irq_mask = irq_gc_mask_disable_reg;
	gc->chip_types[0].chip.irq_unmask = irq_gc_unmask_enable_reg;
	gc->chip_types[0].chip.irq_retrigger = aic_retrigger;
	gc->chip_types[0].chip.irq_set_type = aic_set_type;
	gc->chip_types[0].chip.irq_suspend = aic_suspend;
	gc->chip_types[0].chip.irq_resume = aic_resume;
	gc->chip_types[0].chip.irq_pm_shutकरोwn = aic_pm_shutकरोwn;

	aic_hw_init(करोमुख्य);
	set_handle_irq(aic_handle);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(at91rm9200_aic, "atmel,at91rm9200-aic", aic_of_init);
