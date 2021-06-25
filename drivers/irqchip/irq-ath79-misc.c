<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Atheros AR71xx/AR724x/AR913x MISC पूर्णांकerrupt controller
 *
 *  Copyright (C) 2015 Alban Bedel <albeu@मुक्त.fr>
 *  Copyright (C) 2010-2011 Jaiganesh Narayanan <jnarayanan@atheros.com>
 *  Copyright (C) 2008-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 *
 *  Parts of this file are based on Atheros' 2.6.15/2.6.31 BSP
 */

#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा AR71XX_RESET_REG_MISC_INT_STATUS	0
#घोषणा AR71XX_RESET_REG_MISC_INT_ENABLE	4

#घोषणा ATH79_MISC_IRQ_COUNT			32
#घोषणा ATH79_MISC_PERF_IRQ			5

अटल पूर्णांक ath79_perfcount_irq;

पूर्णांक get_c0_perfcount_पूर्णांक(व्योम)
अणु
	वापस ath79_perfcount_irq;
पूर्ण
EXPORT_SYMBOL_GPL(get_c0_perfcount_पूर्णांक);

अटल व्योम ath79_misc_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	व्योम __iomem *base = करोमुख्य->host_data;
	u32 pending;

	chained_irq_enter(chip, desc);

	pending = __raw_पढ़ोl(base + AR71XX_RESET_REG_MISC_INT_STATUS) &
		  __raw_पढ़ोl(base + AR71XX_RESET_REG_MISC_INT_ENABLE);

	अगर (!pending) अणु
		spurious_पूर्णांकerrupt();
		chained_irq_निकास(chip, desc);
		वापस;
	पूर्ण

	जबतक (pending) अणु
		पूर्णांक bit = __ffs(pending);

		generic_handle_irq(irq_linear_revmap(करोमुख्य, bit));
		pending &= ~BIT(bit);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम ar71xx_misc_irq_unmask(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक irq = d->hwirq;
	u32 t;

	t = __raw_पढ़ोl(base + AR71XX_RESET_REG_MISC_INT_ENABLE);
	__raw_ग_लिखोl(t | BIT(irq), base + AR71XX_RESET_REG_MISC_INT_ENABLE);

	/* flush ग_लिखो */
	__raw_पढ़ोl(base + AR71XX_RESET_REG_MISC_INT_ENABLE);
पूर्ण

अटल व्योम ar71xx_misc_irq_mask(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक irq = d->hwirq;
	u32 t;

	t = __raw_पढ़ोl(base + AR71XX_RESET_REG_MISC_INT_ENABLE);
	__raw_ग_लिखोl(t & ~BIT(irq), base + AR71XX_RESET_REG_MISC_INT_ENABLE);

	/* flush ग_लिखो */
	__raw_पढ़ोl(base + AR71XX_RESET_REG_MISC_INT_ENABLE);
पूर्ण

अटल व्योम ar724x_misc_irq_ack(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक irq = d->hwirq;
	u32 t;

	t = __raw_पढ़ोl(base + AR71XX_RESET_REG_MISC_INT_STATUS);
	__raw_ग_लिखोl(t & ~BIT(irq), base + AR71XX_RESET_REG_MISC_INT_STATUS);

	/* flush ग_लिखो */
	__raw_पढ़ोl(base + AR71XX_RESET_REG_MISC_INT_STATUS);
पूर्ण

अटल काष्ठा irq_chip ath79_misc_irq_chip = अणु
	.name		= "MISC",
	.irq_unmask	= ar71xx_misc_irq_unmask,
	.irq_mask	= ar71xx_misc_irq_mask,
पूर्ण;

अटल पूर्णांक misc_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq, irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(irq, &ath79_misc_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, d->host_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops misc_irq_करोमुख्य_ops = अणु
	.xlate = irq_करोमुख्य_xlate_onecell,
	.map = misc_map,
पूर्ण;

अटल व्योम __init ath79_misc_पूर्णांकc_करोमुख्य_init(
	काष्ठा irq_करोमुख्य *करोमुख्य, पूर्णांक irq)
अणु
	व्योम __iomem *base = करोमुख्य->host_data;

	ath79_perfcount_irq = irq_create_mapping(करोमुख्य, ATH79_MISC_PERF_IRQ);

	/* Disable and clear all पूर्णांकerrupts */
	__raw_ग_लिखोl(0, base + AR71XX_RESET_REG_MISC_INT_ENABLE);
	__raw_ग_लिखोl(0, base + AR71XX_RESET_REG_MISC_INT_STATUS);

	irq_set_chained_handler_and_data(irq, ath79_misc_irq_handler, करोमुख्य);
पूर्ण

अटल पूर्णांक __init ath79_misc_पूर्णांकc_of_init(
	काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	व्योम __iomem *base;
	पूर्णांक irq;

	irq = irq_of_parse_and_map(node, 0);
	अगर (!irq) अणु
		pr_err("Failed to get MISC IRQ\n");
		वापस -EINVAL;
	पूर्ण

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("Failed to get MISC IRQ registers\n");
		वापस -ENOMEM;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_linear(node, ATH79_MISC_IRQ_COUNT,
				&misc_irq_करोमुख्य_ops, base);
	अगर (!करोमुख्य) अणु
		pr_err("Failed to add MISC irqdomain\n");
		वापस -EINVAL;
	पूर्ण

	ath79_misc_पूर्णांकc_करोमुख्य_init(करोमुख्य, irq);
	वापस 0;
पूर्ण

अटल पूर्णांक __init ar7100_misc_पूर्णांकc_of_init(
	काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	ath79_misc_irq_chip.irq_mask_ack = ar71xx_misc_irq_mask;
	वापस ath79_misc_पूर्णांकc_of_init(node, parent);
पूर्ण

IRQCHIP_DECLARE(ar7100_misc_पूर्णांकc, "qca,ar7100-misc-intc",
		ar7100_misc_पूर्णांकc_of_init);

अटल पूर्णांक __init ar7240_misc_पूर्णांकc_of_init(
	काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	ath79_misc_irq_chip.irq_ack = ar724x_misc_irq_ack;
	वापस ath79_misc_पूर्णांकc_of_init(node, parent);
पूर्ण

IRQCHIP_DECLARE(ar7240_misc_पूर्णांकc, "qca,ar7240-misc-intc",
		ar7240_misc_पूर्णांकc_of_init);

व्योम __init ath79_misc_irq_init(व्योम __iomem *regs, पूर्णांक irq,
				पूर्णांक irq_base, bool is_ar71xx)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (is_ar71xx)
		ath79_misc_irq_chip.irq_mask_ack = ar71xx_misc_irq_mask;
	अन्यथा
		ath79_misc_irq_chip.irq_ack = ar724x_misc_irq_ack;

	करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, ATH79_MISC_IRQ_COUNT,
			irq_base, 0, &misc_irq_करोमुख्य_ops, regs);
	अगर (!करोमुख्य)
		panic("Failed to create MISC irqdomain");

	ath79_misc_पूर्णांकc_करोमुख्य_init(करोमुख्य, irq);
पूर्ण
