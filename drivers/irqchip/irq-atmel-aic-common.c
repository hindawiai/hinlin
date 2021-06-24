<शैली गुरु>
/*
 * Aपंचांगel AT91 common AIC (Advanced Interrupt Controller) code shared by
 * irq-aपंचांगel-aic and irq-aपंचांगel-aic5 drivers
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

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश "irq-atmel-aic-common.h"

#घोषणा AT91_AIC_PRIOR			GENMASK(2, 0)
#घोषणा AT91_AIC_IRQ_MIN_PRIORITY	0
#घोषणा AT91_AIC_IRQ_MAX_PRIORITY	7

#घोषणा AT91_AIC_SRCTYPE		GENMASK(6, 5)
#घोषणा AT91_AIC_SRCTYPE_LOW		(0 << 5)
#घोषणा AT91_AIC_SRCTYPE_FALLING	(1 << 5)
#घोषणा AT91_AIC_SRCTYPE_HIGH		(2 << 5)
#घोषणा AT91_AIC_SRCTYPE_RISING		(3 << 5)

काष्ठा aic_chip_data अणु
	u32 ext_irqs;
पूर्ण;

अटल व्योम aic_common_shutकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);

	ct->chip.irq_mask(d);
पूर्ण

पूर्णांक aic_common_set_type(काष्ठा irq_data *d, अचिन्हित type, अचिन्हित *val)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा aic_chip_data *aic = gc->निजी;
	अचिन्हित aic_type;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		aic_type = AT91_AIC_SRCTYPE_HIGH;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		aic_type = AT91_AIC_SRCTYPE_RISING;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		अगर (!(d->mask & aic->ext_irqs))
			वापस -EINVAL;

		aic_type = AT91_AIC_SRCTYPE_LOW;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		अगर (!(d->mask & aic->ext_irqs))
			वापस -EINVAL;

		aic_type = AT91_AIC_SRCTYPE_FALLING;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*val &= ~AT91_AIC_SRCTYPE;
	*val |= aic_type;

	वापस 0;
पूर्ण

व्योम aic_common_set_priority(पूर्णांक priority, अचिन्हित *val)
अणु
	*val &= ~AT91_AIC_PRIOR;
	*val |= priority;
पूर्ण

पूर्णांक aic_common_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
				काष्ठा device_node *ctrlr,
				स्थिर u32 *पूर्णांकspec,
				अचिन्हित पूर्णांक पूर्णांकsize,
				irq_hw_number_t *out_hwirq,
				अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(पूर्णांकsize < 3))
		वापस -EINVAL;

	अगर (WARN_ON((पूर्णांकspec[2] < AT91_AIC_IRQ_MIN_PRIORITY) ||
		    (पूर्णांकspec[2] > AT91_AIC_IRQ_MAX_PRIORITY)))
		वापस -EINVAL;

	*out_hwirq = पूर्णांकspec[0];
	*out_type = पूर्णांकspec[1] & IRQ_TYPE_SENSE_MASK;

	वापस 0;
पूर्ण

अटल व्योम __init aic_common_ext_irq_of_init(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा device_node *node = irq_करोमुख्य_get_of_node(करोमुख्य);
	काष्ठा irq_chip_generic *gc;
	काष्ठा aic_chip_data *aic;
	काष्ठा property *prop;
	स्थिर __be32 *p;
	u32 hwirq;

	gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);

	aic = gc->निजी;
	aic->ext_irqs |= 1;

	of_property_क्रम_each_u32(node, "atmel,external-irqs", prop, p, hwirq) अणु
		gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, hwirq);
		अगर (!gc) अणु
			pr_warn("AIC: external irq %d >= %d skip it\n",
				hwirq, करोमुख्य->revmap_size);
			जारी;
		पूर्ण

		aic = gc->निजी;
		aic->ext_irqs |= (1 << (hwirq % 32));
	पूर्ण
पूर्ण

#घोषणा AT91_RTC_IDR           0x24
#घोषणा AT91_RTC_IMR           0x28
#घोषणा AT91_RTC_IRQ_MASK      0x1f

व्योम __init aic_common_rtc_irq_fixup(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *regs;

	np = of_find_compatible_node(शून्य, शून्य, "atmel,at91rm9200-rtc");
	अगर (!np)
		np = of_find_compatible_node(शून्य, शून्य,
					     "atmel,at91sam9x5-rtc");

	अगर (!np)
		वापस;

	regs = of_iomap(np, 0);
	of_node_put(np);

	अगर (!regs)
		वापस;

	ग_लिखोl(AT91_RTC_IRQ_MASK, regs + AT91_RTC_IDR);

	iounmap(regs);
पूर्ण

#घोषणा AT91_RTT_MR		0x00			/* Real-समय Mode Register */
#घोषणा AT91_RTT_ALMIEN		(1 << 16)		/* Alarm Interrupt Enable */
#घोषणा AT91_RTT_RTTINCIEN	(1 << 17)		/* Real Time Timer Increment Interrupt Enable */

व्योम __init aic_common_rtt_irq_fixup(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *regs;

	/*
	 * The at91sam9263 SoC has 2 instances of the RTT block, hence we
	 * iterate over the DT to find each occurrence.
	 */
	क्रम_each_compatible_node(np, शून्य, "atmel,at91sam9260-rtt") अणु
		regs = of_iomap(np, 0);
		अगर (!regs)
			जारी;

		ग_लिखोl(पढ़ोl(regs + AT91_RTT_MR) &
		       ~(AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN),
		       regs + AT91_RTT_MR);

		iounmap(regs);
	पूर्ण
पूर्ण

अटल व्योम __init aic_common_irq_fixup(स्थिर काष्ठा of_device_id *matches)
अणु
	काष्ठा device_node *root = of_find_node_by_path("/");
	स्थिर काष्ठा of_device_id *match;

	अगर (!root)
		वापस;

	match = of_match_node(matches, root);

	अगर (match) अणु
		व्योम (*fixup)(व्योम) = match->data;
		fixup();
	पूर्ण

	of_node_put(root);
पूर्ण

काष्ठा irq_करोमुख्य *__init aic_common_of_init(काष्ठा device_node *node,
					     स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					     स्थिर अक्षर *name, पूर्णांक nirqs,
					     स्थिर काष्ठा of_device_id *matches)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा aic_chip_data *aic;
	व्योम __iomem *reg_base;
	पूर्णांक nchips;
	पूर्णांक ret;
	पूर्णांक i;

	nchips = DIV_ROUND_UP(nirqs, 32);

	reg_base = of_iomap(node, 0);
	अगर (!reg_base)
		वापस ERR_PTR(-ENOMEM);

	aic = kसुस्मृति(nchips, माप(*aic), GFP_KERNEL);
	अगर (!aic) अणु
		ret = -ENOMEM;
		जाओ err_iounmap;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_linear(node, nchips * 32, ops, aic);
	अगर (!करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_aic;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, 32, 1, name,
					     handle_fasteoi_irq,
					     IRQ_NOREQUEST | IRQ_NOPROBE |
					     IRQ_NOAUTOEN, 0, 0);
	अगर (ret)
		जाओ err_करोमुख्य_हटाओ;

	क्रम (i = 0; i < nchips; i++) अणु
		gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, i * 32);

		gc->reg_base = reg_base;

		gc->unused = 0;
		gc->wake_enabled = ~0;
		gc->chip_types[0].type = IRQ_TYPE_SENSE_MASK;
		gc->chip_types[0].chip.irq_eoi = irq_gc_eoi;
		gc->chip_types[0].chip.irq_set_wake = irq_gc_set_wake;
		gc->chip_types[0].chip.irq_shutकरोwn = aic_common_shutकरोwn;
		gc->निजी = &aic[i];
	पूर्ण

	aic_common_ext_irq_of_init(करोमुख्य);
	aic_common_irq_fixup(matches);

	वापस करोमुख्य;

err_करोमुख्य_हटाओ:
	irq_करोमुख्य_हटाओ(करोमुख्य);

err_मुक्त_aic:
	kमुक्त(aic);

err_iounmap:
	iounmap(reg_base);

	वापस ERR_PTR(ret);
पूर्ण
