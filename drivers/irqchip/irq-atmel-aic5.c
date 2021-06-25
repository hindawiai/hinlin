<शैली गुरु>
/*
 * Aपंचांगel AT91 AIC5 (Advanced Interrupt Controller) driver
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
#घोषणा NR_AIC5_IRQS	128

#घोषणा AT91_AIC5_SSR		0x0
#घोषणा AT91_AIC5_INTSEL_MSK	(0x7f << 0)

#घोषणा AT91_AIC5_SMR			0x4

#घोषणा AT91_AIC5_SVR			0x8
#घोषणा AT91_AIC5_IVR			0x10
#घोषणा AT91_AIC5_FVR			0x14
#घोषणा AT91_AIC5_ISR			0x18

#घोषणा AT91_AIC5_IPR0			0x20
#घोषणा AT91_AIC5_IPR1			0x24
#घोषणा AT91_AIC5_IPR2			0x28
#घोषणा AT91_AIC5_IPR3			0x2c
#घोषणा AT91_AIC5_IMR			0x30
#घोषणा AT91_AIC5_CISR			0x34

#घोषणा AT91_AIC5_IECR			0x40
#घोषणा AT91_AIC5_IDCR			0x44
#घोषणा AT91_AIC5_ICCR			0x48
#घोषणा AT91_AIC5_ISCR			0x4c
#घोषणा AT91_AIC5_EOICR			0x38
#घोषणा AT91_AIC5_SPU			0x3c
#घोषणा AT91_AIC5_DCR			0x6c

#घोषणा AT91_AIC5_FFER			0x50
#घोषणा AT91_AIC5_FFDR			0x54
#घोषणा AT91_AIC5_FFSR			0x58

अटल काष्ठा irq_करोमुख्य *aic5_करोमुख्य;

अटल यंत्रlinkage व्योम __exception_irq_entry
aic5_handle(काष्ठा pt_regs *regs)
अणु
	काष्ठा irq_chip_generic *bgc = irq_get_करोमुख्य_generic_chip(aic5_करोमुख्य, 0);
	u32 irqnr;
	u32 irqstat;

	irqnr = irq_reg_पढ़ोl(bgc, AT91_AIC5_IVR);
	irqstat = irq_reg_पढ़ोl(bgc, AT91_AIC5_ISR);

	अगर (!irqstat)
		irq_reg_ग_लिखोl(bgc, 0, AT91_AIC5_EOICR);
	अन्यथा
		handle_करोमुख्य_irq(aic5_करोमुख्य, irqnr, regs);
पूर्ण

अटल व्योम aic5_mask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा irq_chip_generic *bgc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);

	/*
	 * Disable पूर्णांकerrupt on AIC5. We always take the lock of the
	 * first irq chip as all chips share the same रेजिस्टरs.
	 */
	irq_gc_lock(bgc);
	irq_reg_ग_लिखोl(gc, d->hwirq, AT91_AIC5_SSR);
	irq_reg_ग_लिखोl(gc, 1, AT91_AIC5_IDCR);
	gc->mask_cache &= ~d->mask;
	irq_gc_unlock(bgc);
पूर्ण

अटल व्योम aic5_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा irq_chip_generic *bgc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);

	/*
	 * Enable पूर्णांकerrupt on AIC5. We always take the lock of the
	 * first irq chip as all chips share the same रेजिस्टरs.
	 */
	irq_gc_lock(bgc);
	irq_reg_ग_लिखोl(gc, d->hwirq, AT91_AIC5_SSR);
	irq_reg_ग_लिखोl(gc, 1, AT91_AIC5_IECR);
	gc->mask_cache |= d->mask;
	irq_gc_unlock(bgc);
पूर्ण

अटल पूर्णांक aic5_retrigger(काष्ठा irq_data *d)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा irq_chip_generic *bgc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);

	/* Enable पूर्णांकerrupt on AIC5 */
	irq_gc_lock(bgc);
	irq_reg_ग_लिखोl(bgc, d->hwirq, AT91_AIC5_SSR);
	irq_reg_ग_लिखोl(bgc, 1, AT91_AIC5_ISCR);
	irq_gc_unlock(bgc);

	वापस 1;
पूर्ण

अटल पूर्णांक aic5_set_type(काष्ठा irq_data *d, अचिन्हित type)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा irq_chip_generic *bgc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	अचिन्हित पूर्णांक smr;
	पूर्णांक ret;

	irq_gc_lock(bgc);
	irq_reg_ग_लिखोl(bgc, d->hwirq, AT91_AIC5_SSR);
	smr = irq_reg_पढ़ोl(bgc, AT91_AIC5_SMR);
	ret = aic_common_set_type(d, type, &smr);
	अगर (!ret)
		irq_reg_ग_लिखोl(bgc, smr, AT91_AIC5_SMR);
	irq_gc_unlock(bgc);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल u32 *smr_cache;

अटल व्योम aic5_suspend(काष्ठा irq_data *d)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा irq_करोमुख्य_chip_generic *dgc = करोमुख्य->gc;
	काष्ठा irq_chip_generic *bgc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	पूर्णांक i;
	u32 mask;

	अगर (smr_cache)
		क्रम (i = 0; i < करोमुख्य->revmap_size; i++) अणु
			irq_reg_ग_लिखोl(bgc, i, AT91_AIC5_SSR);
			smr_cache[i] = irq_reg_पढ़ोl(bgc, AT91_AIC5_SMR);
		पूर्ण

	irq_gc_lock(bgc);
	क्रम (i = 0; i < dgc->irqs_per_chip; i++) अणु
		mask = 1 << i;
		अगर ((mask & gc->mask_cache) == (mask & gc->wake_active))
			जारी;

		irq_reg_ग_लिखोl(bgc, i + gc->irq_base, AT91_AIC5_SSR);
		अगर (mask & gc->wake_active)
			irq_reg_ग_लिखोl(bgc, 1, AT91_AIC5_IECR);
		अन्यथा
			irq_reg_ग_लिखोl(bgc, 1, AT91_AIC5_IDCR);
	पूर्ण
	irq_gc_unlock(bgc);
पूर्ण

अटल व्योम aic5_resume(काष्ठा irq_data *d)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा irq_करोमुख्य_chip_generic *dgc = करोमुख्य->gc;
	काष्ठा irq_chip_generic *bgc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	पूर्णांक i;
	u32 mask;

	irq_gc_lock(bgc);

	अगर (smr_cache) अणु
		irq_reg_ग_लिखोl(bgc, 0xffffffff, AT91_AIC5_SPU);
		क्रम (i = 0; i < करोमुख्य->revmap_size; i++) अणु
			irq_reg_ग_लिखोl(bgc, i, AT91_AIC5_SSR);
			irq_reg_ग_लिखोl(bgc, i, AT91_AIC5_SVR);
			irq_reg_ग_लिखोl(bgc, smr_cache[i], AT91_AIC5_SMR);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dgc->irqs_per_chip; i++) अणु
		mask = 1 << i;

		अगर (!smr_cache &&
		    ((mask & gc->mask_cache) == (mask & gc->wake_active)))
			जारी;

		irq_reg_ग_लिखोl(bgc, i + gc->irq_base, AT91_AIC5_SSR);
		अगर (mask & gc->mask_cache)
			irq_reg_ग_लिखोl(bgc, 1, AT91_AIC5_IECR);
		अन्यथा
			irq_reg_ग_लिखोl(bgc, 1, AT91_AIC5_IDCR);
	पूर्ण
	irq_gc_unlock(bgc);
पूर्ण

अटल व्योम aic5_pm_shutकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा irq_करोमुख्य_chip_generic *dgc = करोमुख्य->gc;
	काष्ठा irq_chip_generic *bgc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	पूर्णांक i;

	irq_gc_lock(bgc);
	क्रम (i = 0; i < dgc->irqs_per_chip; i++) अणु
		irq_reg_ग_लिखोl(bgc, i + gc->irq_base, AT91_AIC5_SSR);
		irq_reg_ग_लिखोl(bgc, 1, AT91_AIC5_IDCR);
		irq_reg_ग_लिखोl(bgc, 1, AT91_AIC5_ICCR);
	पूर्ण
	irq_gc_unlock(bgc);
पूर्ण
#अन्यथा
#घोषणा aic5_suspend		शून्य
#घोषणा aic5_resume		शून्य
#घोषणा aic5_pm_shutकरोwn	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम __init aic5_hw_init(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा irq_chip_generic *gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	पूर्णांक i;

	/*
	 * Perक्रमm 8 End Of Interrupt Command to make sure AIC
	 * will not Lock out nIRQ
	 */
	क्रम (i = 0; i < 8; i++)
		irq_reg_ग_लिखोl(gc, 0, AT91_AIC5_EOICR);

	/*
	 * Spurious Interrupt ID in Spurious Vector Register.
	 * When there is no current पूर्णांकerrupt, the IRQ Vector Register
	 * पढ़ोs the value stored in AIC_SPU
	 */
	irq_reg_ग_लिखोl(gc, 0xffffffff, AT91_AIC5_SPU);

	/* No debugging in AIC: Debug (Protect) Control Register */
	irq_reg_ग_लिखोl(gc, 0, AT91_AIC5_DCR);

	/* Disable and clear all पूर्णांकerrupts initially */
	क्रम (i = 0; i < करोमुख्य->revmap_size; i++) अणु
		irq_reg_ग_लिखोl(gc, i, AT91_AIC5_SSR);
		irq_reg_ग_लिखोl(gc, i, AT91_AIC5_SVR);
		irq_reg_ग_लिखोl(gc, 1, AT91_AIC5_IDCR);
		irq_reg_ग_लिखोl(gc, 1, AT91_AIC5_ICCR);
	पूर्ण
पूर्ण

अटल पूर्णांक aic5_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
				 काष्ठा device_node *ctrlr,
				 स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				 irq_hw_number_t *out_hwirq,
				 अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा irq_chip_generic *bgc = irq_get_करोमुख्य_generic_chip(d, 0);
	अचिन्हित दीर्घ flags;
	अचिन्हित smr;
	पूर्णांक ret;

	अगर (!bgc)
		वापस -EINVAL;

	ret = aic_common_irq_करोमुख्य_xlate(d, ctrlr, पूर्णांकspec, पूर्णांकsize,
					  out_hwirq, out_type);
	अगर (ret)
		वापस ret;

	irq_gc_lock_irqsave(bgc, flags);
	irq_reg_ग_लिखोl(bgc, *out_hwirq, AT91_AIC5_SSR);
	smr = irq_reg_पढ़ोl(bgc, AT91_AIC5_SMR);
	aic_common_set_priority(पूर्णांकspec[2], &smr);
	irq_reg_ग_लिखोl(bgc, smr, AT91_AIC5_SMR);
	irq_gc_unlock_irqrestore(bgc, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops aic5_irq_ops = अणु
	.map	= irq_map_generic_chip,
	.xlate	= aic5_irq_करोमुख्य_xlate,
पूर्ण;

अटल व्योम __init sama5d3_aic_irq_fixup(व्योम)
अणु
	aic_common_rtc_irq_fixup();
पूर्ण

अटल व्योम __init sam9x60_aic_irq_fixup(व्योम)
अणु
	aic_common_rtc_irq_fixup();
	aic_common_rtt_irq_fixup();
पूर्ण

अटल स्थिर काष्ठा of_device_id aic5_irq_fixups[] __initस्थिर = अणु
	अणु .compatible = "atmel,sama5d3", .data = sama5d3_aic_irq_fixup पूर्ण,
	अणु .compatible = "atmel,sama5d4", .data = sama5d3_aic_irq_fixup पूर्ण,
	अणु .compatible = "microchip,sam9x60", .data = sam9x60_aic_irq_fixup पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक __init aic5_of_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent,
			       पूर्णांक nirqs)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक nchips;
	पूर्णांक i;

	अगर (nirqs > NR_AIC5_IRQS)
		वापस -EINVAL;

	अगर (aic5_करोमुख्य)
		वापस -EEXIST;

	करोमुख्य = aic_common_of_init(node, &aic5_irq_ops, "atmel-aic5",
				    nirqs, aic5_irq_fixups);
	अगर (IS_ERR(करोमुख्य))
		वापस PTR_ERR(करोमुख्य);

	aic5_करोमुख्य = करोमुख्य;
	nchips = aic5_करोमुख्य->revmap_size / 32;
	क्रम (i = 0; i < nchips; i++) अणु
		gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, i * 32);

		gc->chip_types[0].regs.eoi = AT91_AIC5_EOICR;
		gc->chip_types[0].chip.irq_mask = aic5_mask;
		gc->chip_types[0].chip.irq_unmask = aic5_unmask;
		gc->chip_types[0].chip.irq_retrigger = aic5_retrigger;
		gc->chip_types[0].chip.irq_set_type = aic5_set_type;
		gc->chip_types[0].chip.irq_suspend = aic5_suspend;
		gc->chip_types[0].chip.irq_resume = aic5_resume;
		gc->chip_types[0].chip.irq_pm_shutकरोwn = aic5_pm_shutकरोwn;
	पूर्ण

	aic5_hw_init(करोमुख्य);
	set_handle_irq(aic5_handle);

	वापस 0;
पूर्ण

#घोषणा NR_SAMA5D2_IRQS		77

अटल पूर्णांक __init sama5d2_aic5_of_init(काष्ठा device_node *node,
				       काष्ठा device_node *parent)
अणु
#अगर_घोषित CONFIG_PM
	smr_cache = kसुस्मृति(DIV_ROUND_UP(NR_SAMA5D2_IRQS, 32) * 32,
			    माप(*smr_cache), GFP_KERNEL);
	अगर (!smr_cache)
		वापस -ENOMEM;
#पूर्ण_अगर

	वापस aic5_of_init(node, parent, NR_SAMA5D2_IRQS);
पूर्ण
IRQCHIP_DECLARE(sama5d2_aic5, "atmel,sama5d2-aic", sama5d2_aic5_of_init);

#घोषणा NR_SAMA5D3_IRQS		48

अटल पूर्णांक __init sama5d3_aic5_of_init(काष्ठा device_node *node,
				       काष्ठा device_node *parent)
अणु
	वापस aic5_of_init(node, parent, NR_SAMA5D3_IRQS);
पूर्ण
IRQCHIP_DECLARE(sama5d3_aic5, "atmel,sama5d3-aic", sama5d3_aic5_of_init);

#घोषणा NR_SAMA5D4_IRQS		68

अटल पूर्णांक __init sama5d4_aic5_of_init(काष्ठा device_node *node,
				       काष्ठा device_node *parent)
अणु
	वापस aic5_of_init(node, parent, NR_SAMA5D4_IRQS);
पूर्ण
IRQCHIP_DECLARE(sama5d4_aic5, "atmel,sama5d4-aic", sama5d4_aic5_of_init);

#घोषणा NR_SAM9X60_IRQS		50

अटल पूर्णांक __init sam9x60_aic5_of_init(काष्ठा device_node *node,
				       काष्ठा device_node *parent)
अणु
	वापस aic5_of_init(node, parent, NR_SAM9X60_IRQS);
पूर्ण
IRQCHIP_DECLARE(sam9x60_aic5, "microchip,sam9x60-aic", sam9x60_aic5_of_init);
