<शैली गुरु>
/*
 * SPEAr platक्रमm shared irq layer source file
 *
 * Copyright (C) 2009-2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * Copyright (C) 2012 ST Microelectronics
 * Shiraz Hashim <shiraz.linux.kernel@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spinlock.h>

/*
 * काष्ठा spear_shirq: shared irq काष्ठाure
 *
 * base:	Base रेजिस्टर address
 * status_reg:	Status रेजिस्टर offset क्रम chained पूर्णांकerrupt handler
 * mask_reg:	Mask रेजिस्टर offset क्रम irq chip
 * mask:	Mask to apply to the status रेजिस्टर
 * virq_base:	Base भव पूर्णांकerrupt number
 * nr_irqs:	Number of पूर्णांकerrupts handled by this block
 * offset:	Bit offset of the first पूर्णांकerrupt
 * irq_chip:	Interrupt controller chip used क्रम this instance,
 *		अगर शून्य group is disabled, but accounted
 */
काष्ठा spear_shirq अणु
	व्योम __iomem		*base;
	u32			status_reg;
	u32			mask_reg;
	u32			mask;
	u32			virq_base;
	u32			nr_irqs;
	u32			offset;
	काष्ठा irq_chip		*irq_chip;
पूर्ण;

/* spear300 shared irq रेजिस्टरs offsets and masks */
#घोषणा SPEAR300_INT_ENB_MASK_REG	0x54
#घोषणा SPEAR300_INT_STS_MASK_REG	0x58

अटल DEFINE_RAW_SPINLOCK(shirq_lock);

अटल व्योम shirq_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा spear_shirq *shirq = irq_data_get_irq_chip_data(d);
	u32 val, shअगरt = d->irq - shirq->virq_base + shirq->offset;
	u32 __iomem *reg = shirq->base + shirq->mask_reg;

	raw_spin_lock(&shirq_lock);
	val = पढ़ोl(reg) & ~(0x1 << shअगरt);
	ग_लिखोl(val, reg);
	raw_spin_unlock(&shirq_lock);
पूर्ण

अटल व्योम shirq_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा spear_shirq *shirq = irq_data_get_irq_chip_data(d);
	u32 val, shअगरt = d->irq - shirq->virq_base + shirq->offset;
	u32 __iomem *reg = shirq->base + shirq->mask_reg;

	raw_spin_lock(&shirq_lock);
	val = पढ़ोl(reg) | (0x1 << shअगरt);
	ग_लिखोl(val, reg);
	raw_spin_unlock(&shirq_lock);
पूर्ण

अटल काष्ठा irq_chip shirq_chip = अणु
	.name		= "spear-shirq",
	.irq_mask	= shirq_irq_mask,
	.irq_unmask	= shirq_irq_unmask,
पूर्ण;

अटल काष्ठा spear_shirq spear300_shirq_ras1 = अणु
	.offset		= 0,
	.nr_irqs	= 9,
	.mask		= ((0x1 << 9) - 1) << 0,
	.irq_chip	= &shirq_chip,
	.status_reg	= SPEAR300_INT_STS_MASK_REG,
	.mask_reg	= SPEAR300_INT_ENB_MASK_REG,
पूर्ण;

अटल काष्ठा spear_shirq *spear300_shirq_blocks[] = अणु
	&spear300_shirq_ras1,
पूर्ण;

/* spear310 shared irq रेजिस्टरs offsets and masks */
#घोषणा SPEAR310_INT_STS_MASK_REG	0x04

अटल काष्ठा spear_shirq spear310_shirq_ras1 = अणु
	.offset		= 0,
	.nr_irqs	= 8,
	.mask		= ((0x1 << 8) - 1) << 0,
	.irq_chip	= &dummy_irq_chip,
	.status_reg	= SPEAR310_INT_STS_MASK_REG,
पूर्ण;

अटल काष्ठा spear_shirq spear310_shirq_ras2 = अणु
	.offset		= 8,
	.nr_irqs	= 5,
	.mask		= ((0x1 << 5) - 1) << 8,
	.irq_chip	= &dummy_irq_chip,
	.status_reg	= SPEAR310_INT_STS_MASK_REG,
पूर्ण;

अटल काष्ठा spear_shirq spear310_shirq_ras3 = अणु
	.offset		= 13,
	.nr_irqs	= 1,
	.mask		= ((0x1 << 1) - 1) << 13,
	.irq_chip	= &dummy_irq_chip,
	.status_reg	= SPEAR310_INT_STS_MASK_REG,
पूर्ण;

अटल काष्ठा spear_shirq spear310_shirq_पूर्णांकrcomm_ras = अणु
	.offset		= 14,
	.nr_irqs	= 3,
	.mask		= ((0x1 << 3) - 1) << 14,
	.irq_chip	= &dummy_irq_chip,
	.status_reg	= SPEAR310_INT_STS_MASK_REG,
पूर्ण;

अटल काष्ठा spear_shirq *spear310_shirq_blocks[] = अणु
	&spear310_shirq_ras1,
	&spear310_shirq_ras2,
	&spear310_shirq_ras3,
	&spear310_shirq_पूर्णांकrcomm_ras,
पूर्ण;

/* spear320 shared irq रेजिस्टरs offsets and masks */
#घोषणा SPEAR320_INT_STS_MASK_REG		0x04
#घोषणा SPEAR320_INT_CLR_MASK_REG		0x04
#घोषणा SPEAR320_INT_ENB_MASK_REG		0x08

अटल काष्ठा spear_shirq spear320_shirq_ras3 = अणु
	.offset		= 0,
	.nr_irqs	= 7,
	.mask		= ((0x1 << 7) - 1) << 0,
पूर्ण;

अटल काष्ठा spear_shirq spear320_shirq_ras1 = अणु
	.offset		= 7,
	.nr_irqs	= 3,
	.mask		= ((0x1 << 3) - 1) << 7,
	.irq_chip	= &dummy_irq_chip,
	.status_reg	= SPEAR320_INT_STS_MASK_REG,
पूर्ण;

अटल काष्ठा spear_shirq spear320_shirq_ras2 = अणु
	.offset		= 10,
	.nr_irqs	= 1,
	.mask		= ((0x1 << 1) - 1) << 10,
	.irq_chip	= &dummy_irq_chip,
	.status_reg	= SPEAR320_INT_STS_MASK_REG,
पूर्ण;

अटल काष्ठा spear_shirq spear320_shirq_पूर्णांकrcomm_ras = अणु
	.offset		= 11,
	.nr_irqs	= 11,
	.mask		= ((0x1 << 11) - 1) << 11,
	.irq_chip	= &dummy_irq_chip,
	.status_reg	= SPEAR320_INT_STS_MASK_REG,
पूर्ण;

अटल काष्ठा spear_shirq *spear320_shirq_blocks[] = अणु
	&spear320_shirq_ras3,
	&spear320_shirq_ras1,
	&spear320_shirq_ras2,
	&spear320_shirq_पूर्णांकrcomm_ras,
पूर्ण;

अटल व्योम shirq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा spear_shirq *shirq = irq_desc_get_handler_data(desc);
	u32 pend;

	pend = पढ़ोl(shirq->base + shirq->status_reg) & shirq->mask;
	pend >>= shirq->offset;

	जबतक (pend) अणु
		पूर्णांक irq = __ffs(pend);

		pend &= ~(0x1 << irq);
		generic_handle_irq(shirq->virq_base + irq);
	पूर्ण
पूर्ण

अटल व्योम __init spear_shirq_रेजिस्टर(काष्ठा spear_shirq *shirq,
					पूर्णांक parent_irq)
अणु
	पूर्णांक i;

	अगर (!shirq->irq_chip)
		वापस;

	irq_set_chained_handler_and_data(parent_irq, shirq_handler, shirq);

	क्रम (i = 0; i < shirq->nr_irqs; i++) अणु
		irq_set_chip_and_handler(shirq->virq_base + i,
					 shirq->irq_chip, handle_simple_irq);
		irq_set_chip_data(shirq->virq_base + i, shirq);
	पूर्ण
पूर्ण

अटल पूर्णांक __init shirq_init(काष्ठा spear_shirq **shirq_blocks, पूर्णांक block_nr,
		काष्ठा device_node *np)
अणु
	पूर्णांक i, parent_irq, virq_base, hwirq = 0, nr_irqs = 0;
	काष्ठा irq_करोमुख्य *shirq_करोमुख्य;
	व्योम __iomem *base;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("%s: failed to map shirq registers\n", __func__);
		वापस -ENXIO;
	पूर्ण

	क्रम (i = 0; i < block_nr; i++)
		nr_irqs += shirq_blocks[i]->nr_irqs;

	virq_base = irq_alloc_descs(-1, 0, nr_irqs, 0);
	अगर (virq_base < 0) अणु
		pr_err("%s: irq desc alloc failed\n", __func__);
		जाओ err_unmap;
	पूर्ण

	shirq_करोमुख्य = irq_करोमुख्य_add_legacy(np, nr_irqs, virq_base, 0,
			&irq_करोमुख्य_simple_ops, शून्य);
	अगर (WARN_ON(!shirq_करोमुख्य)) अणु
		pr_warn("%s: irq domain init failed\n", __func__);
		जाओ err_मुक्त_desc;
	पूर्ण

	क्रम (i = 0; i < block_nr; i++) अणु
		shirq_blocks[i]->base = base;
		shirq_blocks[i]->virq_base = irq_find_mapping(shirq_करोमुख्य,
				hwirq);

		parent_irq = irq_of_parse_and_map(np, i);
		spear_shirq_रेजिस्टर(shirq_blocks[i], parent_irq);
		hwirq += shirq_blocks[i]->nr_irqs;
	पूर्ण

	वापस 0;

err_मुक्त_desc:
	irq_मुक्त_descs(virq_base, nr_irqs);
err_unmap:
	iounmap(base);
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक __init spear300_shirq_of_init(काष्ठा device_node *np,
					 काष्ठा device_node *parent)
अणु
	वापस shirq_init(spear300_shirq_blocks,
			ARRAY_SIZE(spear300_shirq_blocks), np);
पूर्ण
IRQCHIP_DECLARE(spear300_shirq, "st,spear300-shirq", spear300_shirq_of_init);

अटल पूर्णांक __init spear310_shirq_of_init(काष्ठा device_node *np,
					 काष्ठा device_node *parent)
अणु
	वापस shirq_init(spear310_shirq_blocks,
			ARRAY_SIZE(spear310_shirq_blocks), np);
पूर्ण
IRQCHIP_DECLARE(spear310_shirq, "st,spear310-shirq", spear310_shirq_of_init);

अटल पूर्णांक __init spear320_shirq_of_init(काष्ठा device_node *np,
					 काष्ठा device_node *parent)
अणु
	वापस shirq_init(spear320_shirq_blocks,
			ARRAY_SIZE(spear320_shirq_blocks), np);
पूर्ण
IRQCHIP_DECLARE(spear320_shirq, "st,spear320-shirq", spear320_shirq_of_init);
