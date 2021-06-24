<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Aspeed AST24XX, AST25XX, and AST26XX SCU Interrupt Controller
 * Copyright 2019 IBM Corporation
 *
 * Eddie James <eajames@linux.ibm.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>

#घोषणा ASPEED_SCU_IC_REG		0x018
#घोषणा ASPEED_SCU_IC_SHIFT		0
#घोषणा ASPEED_SCU_IC_ENABLE		GENMASK(6, ASPEED_SCU_IC_SHIFT)
#घोषणा ASPEED_SCU_IC_NUM_IRQS		7
#घोषणा ASPEED_SCU_IC_STATUS_SHIFT	16

#घोषणा ASPEED_AST2600_SCU_IC0_REG	0x560
#घोषणा ASPEED_AST2600_SCU_IC0_SHIFT	0
#घोषणा ASPEED_AST2600_SCU_IC0_ENABLE	\
	GENMASK(5, ASPEED_AST2600_SCU_IC0_SHIFT)
#घोषणा ASPEED_AST2600_SCU_IC0_NUM_IRQS	6

#घोषणा ASPEED_AST2600_SCU_IC1_REG	0x570
#घोषणा ASPEED_AST2600_SCU_IC1_SHIFT	4
#घोषणा ASPEED_AST2600_SCU_IC1_ENABLE	\
	GENMASK(5, ASPEED_AST2600_SCU_IC1_SHIFT)
#घोषणा ASPEED_AST2600_SCU_IC1_NUM_IRQS	2

काष्ठा aspeed_scu_ic अणु
	अचिन्हित दीर्घ irq_enable;
	अचिन्हित दीर्घ irq_shअगरt;
	अचिन्हित पूर्णांक num_irqs;
	अचिन्हित पूर्णांक reg;
	काष्ठा regmap *scu;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
पूर्ण;

अटल व्योम aspeed_scu_ic_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक sts;
	अचिन्हित दीर्घ bit;
	अचिन्हित दीर्घ enabled;
	अचिन्हित दीर्घ max;
	अचिन्हित दीर्घ status;
	काष्ठा aspeed_scu_ic *scu_ic = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक mask = scu_ic->irq_enable << ASPEED_SCU_IC_STATUS_SHIFT;

	chained_irq_enter(chip, desc);

	/*
	 * The SCU IC has just one रेजिस्टर to control its operation and पढ़ो
	 * status. The पूर्णांकerrupt enable bits occupy the lower 16 bits of the
	 * रेजिस्टर, जबतक the पूर्णांकerrupt status bits occupy the upper 16 bits.
	 * The status bit क्रम a given पूर्णांकerrupt is always 16 bits shअगरted from
	 * the enable bit क्रम the same पूर्णांकerrupt.
	 * Thereक्रमe, perक्रमm the IRQ operations in the enable bit space by
	 * shअगरting the status करोwn to get the mapping and then back up to
	 * clear the bit.
	 */
	regmap_पढ़ो(scu_ic->scu, scu_ic->reg, &sts);
	enabled = sts & scu_ic->irq_enable;
	status = (sts >> ASPEED_SCU_IC_STATUS_SHIFT) & enabled;

	bit = scu_ic->irq_shअगरt;
	max = scu_ic->num_irqs + bit;

	क्रम_each_set_bit_from(bit, &status, max) अणु
		irq = irq_find_mapping(scu_ic->irq_करोमुख्य,
				       bit - scu_ic->irq_shअगरt);
		generic_handle_irq(irq);

		regmap_update_bits(scu_ic->scu, scu_ic->reg, mask,
				   BIT(bit + ASPEED_SCU_IC_STATUS_SHIFT));
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम aspeed_scu_ic_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा aspeed_scu_ic *scu_ic = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक mask = BIT(data->hwirq + scu_ic->irq_shअगरt) |
		(scu_ic->irq_enable << ASPEED_SCU_IC_STATUS_SHIFT);

	/*
	 * Status bits are cleared by writing 1. In order to prevent the mask
	 * operation from clearing the status bits, they should be under the
	 * mask and written with 0.
	 */
	regmap_update_bits(scu_ic->scu, scu_ic->reg, mask, 0);
पूर्ण

अटल व्योम aspeed_scu_ic_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा aspeed_scu_ic *scu_ic = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक bit = BIT(data->hwirq + scu_ic->irq_shअगरt);
	अचिन्हित पूर्णांक mask = bit |
		(scu_ic->irq_enable << ASPEED_SCU_IC_STATUS_SHIFT);

	/*
	 * Status bits are cleared by writing 1. In order to prevent the unmask
	 * operation from clearing the status bits, they should be under the
	 * mask and written with 0.
	 */
	regmap_update_bits(scu_ic->scu, scu_ic->reg, mask, bit);
पूर्ण

अटल पूर्णांक aspeed_scu_ic_irq_set_affinity(काष्ठा irq_data *data,
					  स्थिर काष्ठा cpumask *dest,
					  bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल काष्ठा irq_chip aspeed_scu_ic_chip = अणु
	.name			= "aspeed-scu-ic",
	.irq_mask		= aspeed_scu_ic_irq_mask,
	.irq_unmask		= aspeed_scu_ic_irq_unmask,
	.irq_set_affinity	= aspeed_scu_ic_irq_set_affinity,
पूर्ण;

अटल पूर्णांक aspeed_scu_ic_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
			     irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &aspeed_scu_ic_chip, handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops aspeed_scu_ic_करोमुख्य_ops = अणु
	.map = aspeed_scu_ic_map,
पूर्ण;

अटल पूर्णांक aspeed_scu_ic_of_init_common(काष्ठा aspeed_scu_ic *scu_ic,
					काष्ठा device_node *node)
अणु
	पूर्णांक irq;
	पूर्णांक rc = 0;

	अगर (!node->parent) अणु
		rc = -ENODEV;
		जाओ err;
	पूर्ण

	scu_ic->scu = syscon_node_to_regmap(node->parent);
	अगर (IS_ERR(scu_ic->scu)) अणु
		rc = PTR_ERR(scu_ic->scu);
		जाओ err;
	पूर्ण

	irq = irq_of_parse_and_map(node, 0);
	अगर (irq < 0) अणु
		rc = irq;
		जाओ err;
	पूर्ण

	scu_ic->irq_करोमुख्य = irq_करोमुख्य_add_linear(node, scu_ic->num_irqs,
						   &aspeed_scu_ic_करोमुख्य_ops,
						   scu_ic);
	अगर (!scu_ic->irq_करोमुख्य) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	irq_set_chained_handler_and_data(irq, aspeed_scu_ic_irq_handler,
					 scu_ic);

	वापस 0;

err:
	kमुक्त(scu_ic);

	वापस rc;
पूर्ण

अटल पूर्णांक __init aspeed_scu_ic_of_init(काष्ठा device_node *node,
					काष्ठा device_node *parent)
अणु
	काष्ठा aspeed_scu_ic *scu_ic = kzalloc(माप(*scu_ic), GFP_KERNEL);

	अगर (!scu_ic)
		वापस -ENOMEM;

	scu_ic->irq_enable = ASPEED_SCU_IC_ENABLE;
	scu_ic->irq_shअगरt = ASPEED_SCU_IC_SHIFT;
	scu_ic->num_irqs = ASPEED_SCU_IC_NUM_IRQS;
	scu_ic->reg = ASPEED_SCU_IC_REG;

	वापस aspeed_scu_ic_of_init_common(scu_ic, node);
पूर्ण

अटल पूर्णांक __init aspeed_ast2600_scu_ic0_of_init(काष्ठा device_node *node,
						 काष्ठा device_node *parent)
अणु
	काष्ठा aspeed_scu_ic *scu_ic = kzalloc(माप(*scu_ic), GFP_KERNEL);

	अगर (!scu_ic)
		वापस -ENOMEM;

	scu_ic->irq_enable = ASPEED_AST2600_SCU_IC0_ENABLE;
	scu_ic->irq_shअगरt = ASPEED_AST2600_SCU_IC0_SHIFT;
	scu_ic->num_irqs = ASPEED_AST2600_SCU_IC0_NUM_IRQS;
	scu_ic->reg = ASPEED_AST2600_SCU_IC0_REG;

	वापस aspeed_scu_ic_of_init_common(scu_ic, node);
पूर्ण

अटल पूर्णांक __init aspeed_ast2600_scu_ic1_of_init(काष्ठा device_node *node,
						 काष्ठा device_node *parent)
अणु
	काष्ठा aspeed_scu_ic *scu_ic = kzalloc(माप(*scu_ic), GFP_KERNEL);

	अगर (!scu_ic)
		वापस -ENOMEM;

	scu_ic->irq_enable = ASPEED_AST2600_SCU_IC1_ENABLE;
	scu_ic->irq_shअगरt = ASPEED_AST2600_SCU_IC1_SHIFT;
	scu_ic->num_irqs = ASPEED_AST2600_SCU_IC1_NUM_IRQS;
	scu_ic->reg = ASPEED_AST2600_SCU_IC1_REG;

	वापस aspeed_scu_ic_of_init_common(scu_ic, node);
पूर्ण

IRQCHIP_DECLARE(ast2400_scu_ic, "aspeed,ast2400-scu-ic", aspeed_scu_ic_of_init);
IRQCHIP_DECLARE(ast2500_scu_ic, "aspeed,ast2500-scu-ic", aspeed_scu_ic_of_init);
IRQCHIP_DECLARE(ast2600_scu_ic0, "aspeed,ast2600-scu-ic0",
		aspeed_ast2600_scu_ic0_of_init);
IRQCHIP_DECLARE(ast2600_scu_ic1, "aspeed,ast2600-scu-ic1",
		aspeed_ast2600_scu_ic1_of_init);
