<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015-2016 Vladimir Zapolskiy <vz@mleia.com>
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/exception.h>

#घोषणा LPC32XX_INTC_MASK		0x00
#घोषणा LPC32XX_INTC_RAW		0x04
#घोषणा LPC32XX_INTC_STAT		0x08
#घोषणा LPC32XX_INTC_POL		0x0C
#घोषणा LPC32XX_INTC_TYPE		0x10
#घोषणा LPC32XX_INTC_FIQ		0x14

#घोषणा NR_LPC32XX_IC_IRQS		32

काष्ठा lpc32xx_irq_chip अणु
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip chip;
पूर्ण;

अटल काष्ठा lpc32xx_irq_chip *lpc32xx_mic_irqc;

अटल अंतरभूत u32 lpc32xx_ic_पढ़ो(काष्ठा lpc32xx_irq_chip *ic, u32 reg)
अणु
	वापस पढ़ोl_relaxed(ic->base + reg);
पूर्ण

अटल अंतरभूत व्योम lpc32xx_ic_ग_लिखो(काष्ठा lpc32xx_irq_chip *ic,
				    u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, ic->base + reg);
पूर्ण

अटल व्योम lpc32xx_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा lpc32xx_irq_chip *ic = irq_data_get_irq_chip_data(d);
	u32 val, mask = BIT(d->hwirq);

	val = lpc32xx_ic_पढ़ो(ic, LPC32XX_INTC_MASK) & ~mask;
	lpc32xx_ic_ग_लिखो(ic, LPC32XX_INTC_MASK, val);
पूर्ण

अटल व्योम lpc32xx_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा lpc32xx_irq_chip *ic = irq_data_get_irq_chip_data(d);
	u32 val, mask = BIT(d->hwirq);

	val = lpc32xx_ic_पढ़ो(ic, LPC32XX_INTC_MASK) | mask;
	lpc32xx_ic_ग_लिखो(ic, LPC32XX_INTC_MASK, val);
पूर्ण

अटल व्योम lpc32xx_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा lpc32xx_irq_chip *ic = irq_data_get_irq_chip_data(d);
	u32 mask = BIT(d->hwirq);

	lpc32xx_ic_ग_लिखो(ic, LPC32XX_INTC_RAW, mask);
पूर्ण

अटल पूर्णांक lpc32xx_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा lpc32xx_irq_chip *ic = irq_data_get_irq_chip_data(d);
	u32 val, mask = BIT(d->hwirq);
	bool high, edge;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		edge = true;
		high = true;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		edge = true;
		high = false;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		edge = false;
		high = true;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		edge = false;
		high = false;
		अवरोध;
	शेष:
		pr_info("unsupported irq type %d\n", type);
		वापस -EINVAL;
	पूर्ण

	irqd_set_trigger_type(d, type);

	val = lpc32xx_ic_पढ़ो(ic, LPC32XX_INTC_POL);
	अगर (high)
		val |= mask;
	अन्यथा
		val &= ~mask;
	lpc32xx_ic_ग_लिखो(ic, LPC32XX_INTC_POL, val);

	val = lpc32xx_ic_पढ़ो(ic, LPC32XX_INTC_TYPE);
	अगर (edge) अणु
		val |= mask;
		irq_set_handler_locked(d, handle_edge_irq);
	पूर्ण अन्यथा अणु
		val &= ~mask;
		irq_set_handler_locked(d, handle_level_irq);
	पूर्ण
	lpc32xx_ic_ग_लिखो(ic, LPC32XX_INTC_TYPE, val);

	वापस 0;
पूर्ण

अटल व्योम __exception_irq_entry lpc32xx_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा lpc32xx_irq_chip *ic = lpc32xx_mic_irqc;
	u32 hwirq = lpc32xx_ic_पढ़ो(ic, LPC32XX_INTC_STAT), irq;

	जबतक (hwirq) अणु
		irq = __ffs(hwirq);
		hwirq &= ~BIT(irq);
		handle_करोमुख्य_irq(lpc32xx_mic_irqc->करोमुख्य, irq, regs);
	पूर्ण
पूर्ण

अटल व्योम lpc32xx_sic_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा lpc32xx_irq_chip *ic = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	u32 hwirq = lpc32xx_ic_पढ़ो(ic, LPC32XX_INTC_STAT), irq;

	chained_irq_enter(chip, desc);

	जबतक (hwirq) अणु
		irq = __ffs(hwirq);
		hwirq &= ~BIT(irq);
		generic_handle_irq(irq_find_mapping(ic->करोमुख्य, irq));
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक lpc32xx_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *id, अचिन्हित पूर्णांक virq,
				  irq_hw_number_t hw)
अणु
	काष्ठा lpc32xx_irq_chip *ic = id->host_data;

	irq_set_chip_data(virq, ic);
	irq_set_chip_and_handler(virq, &ic->chip, handle_level_irq);
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल व्योम lpc32xx_irq_करोमुख्य_unmap(काष्ठा irq_करोमुख्य *id, अचिन्हित पूर्णांक virq)
अणु
	irq_set_chip_and_handler(virq, शून्य, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops lpc32xx_irq_करोमुख्य_ops = अणु
	.map    = lpc32xx_irq_करोमुख्य_map,
	.unmap	= lpc32xx_irq_करोमुख्य_unmap,
	.xlate  = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल पूर्णांक __init lpc32xx_of_ic_init(काष्ठा device_node *node,
				     काष्ठा device_node *parent)
अणु
	काष्ठा lpc32xx_irq_chip *irqc;
	bool is_mic = of_device_is_compatible(node, "nxp,lpc3220-mic");
	स्थिर __be32 *reg = of_get_property(node, "reg", शून्य);
	u32 parent_irq, i, addr = reg ? be32_to_cpu(*reg) : 0;

	irqc = kzalloc(माप(*irqc), GFP_KERNEL);
	अगर (!irqc)
		वापस -ENOMEM;

	irqc->base = of_iomap(node, 0);
	अगर (!irqc->base) अणु
		pr_err("%pOF: unable to map registers\n", node);
		kमुक्त(irqc);
		वापस -EINVAL;
	पूर्ण

	irqc->chip.irq_ack = lpc32xx_irq_ack;
	irqc->chip.irq_mask = lpc32xx_irq_mask;
	irqc->chip.irq_unmask = lpc32xx_irq_unmask;
	irqc->chip.irq_set_type = lpc32xx_irq_set_type;
	अगर (is_mic)
		irqc->chip.name = kaप्र_लिखो(GFP_KERNEL, "%08x.mic", addr);
	अन्यथा
		irqc->chip.name = kaप्र_लिखो(GFP_KERNEL, "%08x.sic", addr);

	irqc->करोमुख्य = irq_करोमुख्य_add_linear(node, NR_LPC32XX_IC_IRQS,
					     &lpc32xx_irq_करोमुख्य_ops, irqc);
	अगर (!irqc->करोमुख्य) अणु
		pr_err("unable to add irq domain\n");
		iounmap(irqc->base);
		kमुक्त(irqc->chip.name);
		kमुक्त(irqc);
		वापस -ENODEV;
	पूर्ण

	अगर (is_mic) अणु
		lpc32xx_mic_irqc = irqc;
		set_handle_irq(lpc32xx_handle_irq);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < of_irq_count(node); i++) अणु
			parent_irq = irq_of_parse_and_map(node, i);
			अगर (parent_irq)
				irq_set_chained_handler_and_data(parent_irq,
						 lpc32xx_sic_handler, irqc);
		पूर्ण
	पूर्ण

	lpc32xx_ic_ग_लिखो(irqc, LPC32XX_INTC_MASK, 0x00);
	lpc32xx_ic_ग_लिखो(irqc, LPC32XX_INTC_POL,  0x00);
	lpc32xx_ic_ग_लिखो(irqc, LPC32XX_INTC_TYPE, 0x00);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(nxp_lpc32xx_mic, "nxp,lpc3220-mic", lpc32xx_of_ic_init);
IRQCHIP_DECLARE(nxp_lpc32xx_sic, "nxp,lpc3220-sic", lpc32xx_of_ic_init);
