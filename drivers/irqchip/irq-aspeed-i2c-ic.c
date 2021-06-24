<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Aspeed 24XX/25XX I2C Interrupt Controller.
 *
 *  Copyright (C) 2012-2017 ASPEED Technology Inc.
 *  Copyright 2017 IBM Corporation
 *  Copyright 2017 Google, Inc.
 */

#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पन.स>


#घोषणा ASPEED_I2C_IC_NUM_BUS 14

काष्ठा aspeed_i2c_ic अणु
	व्योम __iomem		*base;
	पूर्णांक			parent_irq;
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
पूर्ण;

/*
 * The aspeed chip provides a single hardware पूर्णांकerrupt क्रम all of the I2C
 * busses, so we use a dummy पूर्णांकerrupt chip to translate this single पूर्णांकerrupt
 * पूर्णांकo multiple पूर्णांकerrupts, each associated with a single I2C bus.
 */
अटल व्योम aspeed_i2c_ic_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा aspeed_i2c_ic *i2c_ic = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ bit, status;
	अचिन्हित पूर्णांक bus_irq;

	chained_irq_enter(chip, desc);
	status = पढ़ोl(i2c_ic->base);
	क्रम_each_set_bit(bit, &status, ASPEED_I2C_IC_NUM_BUS) अणु
		bus_irq = irq_find_mapping(i2c_ic->irq_करोमुख्य, bit);
		generic_handle_irq(bus_irq);
	पूर्ण
	chained_irq_निकास(chip, desc);
पूर्ण

/*
 * Set simple handler and mark IRQ as valid. Nothing पूर्णांकeresting to करो here
 * since we are using a dummy पूर्णांकerrupt chip.
 */
अटल पूर्णांक aspeed_i2c_ic_map_irq_करोमुख्य(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक irq, irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &dummy_irq_chip, handle_simple_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops aspeed_i2c_ic_irq_करोमुख्य_ops = अणु
	.map = aspeed_i2c_ic_map_irq_करोमुख्य,
पूर्ण;

अटल पूर्णांक __init aspeed_i2c_ic_of_init(काष्ठा device_node *node,
					काष्ठा device_node *parent)
अणु
	काष्ठा aspeed_i2c_ic *i2c_ic;
	पूर्णांक ret = 0;

	i2c_ic = kzalloc(माप(*i2c_ic), GFP_KERNEL);
	अगर (!i2c_ic)
		वापस -ENOMEM;

	i2c_ic->base = of_iomap(node, 0);
	अगर (!i2c_ic->base) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_ic;
	पूर्ण

	i2c_ic->parent_irq = irq_of_parse_and_map(node, 0);
	अगर (i2c_ic->parent_irq < 0) अणु
		ret = i2c_ic->parent_irq;
		जाओ err_iounmap;
	पूर्ण

	i2c_ic->irq_करोमुख्य = irq_करोमुख्य_add_linear(node, ASPEED_I2C_IC_NUM_BUS,
						   &aspeed_i2c_ic_irq_करोमुख्य_ops,
						   शून्य);
	अगर (!i2c_ic->irq_करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ err_iounmap;
	पूर्ण

	i2c_ic->irq_करोमुख्य->name = "aspeed-i2c-domain";

	irq_set_chained_handler_and_data(i2c_ic->parent_irq,
					 aspeed_i2c_ic_irq_handler, i2c_ic);

	pr_info("i2c controller registered, irq %d\n", i2c_ic->parent_irq);

	वापस 0;

err_iounmap:
	iounmap(i2c_ic->base);
err_मुक्त_ic:
	kमुक्त(i2c_ic);
	वापस ret;
पूर्ण

IRQCHIP_DECLARE(ast2400_i2c_ic, "aspeed,ast2400-i2c-ic", aspeed_i2c_ic_of_init);
IRQCHIP_DECLARE(ast2500_i2c_ic, "aspeed,ast2500-i2c-ic", aspeed_i2c_ic_of_init);
