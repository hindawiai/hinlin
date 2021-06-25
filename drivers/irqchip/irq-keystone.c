<शैली गुरु>
/*
 * Texas Instruments Keystone IRQ controller IP driver
 *
 * Copyright (C) 2014 Texas Instruments, Inc.
 * Author: Sajesh Kumar Saran <sajesh@ti.com>
 *	   Grygorii Strashko <grygorii.strashko@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/irq.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

/* The source ID bits start from 4 to 31 (total 28 bits)*/
#घोषणा BIT_OFS			4
#घोषणा KEYSTONE_N_IRQ		(32 - BIT_OFS)

काष्ठा keystone_irq_device अणु
	काष्ठा device		*dev;
	काष्ठा irq_chip		 chip;
	u32			 mask;
	पूर्णांक			 irq;
	काष्ठा irq_करोमुख्य	*irqd;
	काष्ठा regmap		*devctrl_regs;
	u32			devctrl_offset;
	raw_spinlock_t		wa_lock;
पूर्ण;

अटल अंतरभूत u32 keystone_irq_पढ़ोl(काष्ठा keystone_irq_device *kirq)
अणु
	पूर्णांक ret;
	u32 val = 0;

	ret = regmap_पढ़ो(kirq->devctrl_regs, kirq->devctrl_offset, &val);
	अगर (ret < 0)
		dev_dbg(kirq->dev, "irq read failed ret(%d)\n", ret);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम
keystone_irq_ग_लिखोl(काष्ठा keystone_irq_device *kirq, u32 value)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(kirq->devctrl_regs, kirq->devctrl_offset, value);
	अगर (ret < 0)
		dev_dbg(kirq->dev, "irq write failed ret(%d)\n", ret);
पूर्ण

अटल व्योम keystone_irq_seपंचांगask(काष्ठा irq_data *d)
अणु
	काष्ठा keystone_irq_device *kirq = irq_data_get_irq_chip_data(d);

	kirq->mask |= BIT(d->hwirq);
	dev_dbg(kirq->dev, "mask %lu [%x]\n", d->hwirq, kirq->mask);
पूर्ण

अटल व्योम keystone_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा keystone_irq_device *kirq = irq_data_get_irq_chip_data(d);

	kirq->mask &= ~BIT(d->hwirq);
	dev_dbg(kirq->dev, "unmask %lu [%x]\n", d->hwirq, kirq->mask);
पूर्ण

अटल व्योम keystone_irq_ack(काष्ठा irq_data *d)
अणु
	/* nothing to करो here */
पूर्ण

अटल irqवापस_t keystone_irq_handler(पूर्णांक irq, व्योम *keystone_irq)
अणु
	काष्ठा keystone_irq_device *kirq = keystone_irq;
	अचिन्हित दीर्घ wa_lock_flags;
	अचिन्हित दीर्घ pending;
	पूर्णांक src, virq;

	dev_dbg(kirq->dev, "start irq %d\n", irq);

	pending = keystone_irq_पढ़ोl(kirq);
	keystone_irq_ग_लिखोl(kirq, pending);

	dev_dbg(kirq->dev, "pending 0x%lx, mask 0x%x\n", pending, kirq->mask);

	pending = (pending >> BIT_OFS) & ~kirq->mask;

	dev_dbg(kirq->dev, "pending after mask 0x%lx\n", pending);

	क्रम (src = 0; src < KEYSTONE_N_IRQ; src++) अणु
		अगर (BIT(src) & pending) अणु
			virq = irq_find_mapping(kirq->irqd, src);
			dev_dbg(kirq->dev, "dispatch bit %d, virq %d\n",
				src, virq);
			अगर (!virq)
				dev_warn(kirq->dev, "spurious irq detected hwirq %d, virq %d\n",
					 src, virq);
			raw_spin_lock_irqsave(&kirq->wa_lock, wa_lock_flags);
			generic_handle_irq(virq);
			raw_spin_unlock_irqrestore(&kirq->wa_lock,
						   wa_lock_flags);
		पूर्ण
	पूर्ण

	dev_dbg(kirq->dev, "end irq %d\n", irq);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक keystone_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hw)
अणु
	काष्ठा keystone_irq_device *kirq = h->host_data;

	irq_set_chip_data(virq, kirq);
	irq_set_chip_and_handler(virq, &kirq->chip, handle_level_irq);
	irq_set_probe(virq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops keystone_irq_ops = अणु
	.map	= keystone_irq_map,
	.xlate	= irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक keystone_irq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा keystone_irq_device *kirq;
	पूर्णांक ret;

	अगर (np == शून्य)
		वापस -EINVAL;

	kirq = devm_kzalloc(dev, माप(*kirq), GFP_KERNEL);
	अगर (!kirq)
		वापस -ENOMEM;

	kirq->devctrl_regs =
		syscon_regmap_lookup_by_phandle(np, "ti,syscon-dev");
	अगर (IS_ERR(kirq->devctrl_regs))
		वापस PTR_ERR(kirq->devctrl_regs);

	ret = of_property_पढ़ो_u32_index(np, "ti,syscon-dev", 1,
					 &kirq->devctrl_offset);
	अगर (ret) अणु
		dev_err(dev, "couldn't read the devctrl_offset offset!\n");
		वापस ret;
	पूर्ण

	kirq->irq = platक्रमm_get_irq(pdev, 0);
	अगर (kirq->irq < 0)
		वापस kirq->irq;

	kirq->dev = dev;
	kirq->mask = ~0x0;
	kirq->chip.name		= "keystone-irq";
	kirq->chip.irq_ack	= keystone_irq_ack;
	kirq->chip.irq_mask	= keystone_irq_seपंचांगask;
	kirq->chip.irq_unmask	= keystone_irq_unmask;

	kirq->irqd = irq_करोमुख्य_add_linear(np, KEYSTONE_N_IRQ,
					   &keystone_irq_ops, kirq);
	अगर (!kirq->irqd) अणु
		dev_err(dev, "IRQ domain registration failed\n");
		वापस -ENODEV;
	पूर्ण

	raw_spin_lock_init(&kirq->wa_lock);

	platक्रमm_set_drvdata(pdev, kirq);

	ret = request_irq(kirq->irq, keystone_irq_handler,
			  0, dev_name(dev), kirq);
	अगर (ret) अणु
		irq_करोमुख्य_हटाओ(kirq->irqd);
		वापस ret;
	पूर्ण

	/* clear all source bits */
	keystone_irq_ग_लिखोl(kirq, ~0x0);

	dev_info(dev, "irqchip registered, nr_irqs %u\n", KEYSTONE_N_IRQ);

	वापस 0;
पूर्ण

अटल पूर्णांक keystone_irq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा keystone_irq_device *kirq = platक्रमm_get_drvdata(pdev);
	पूर्णांक hwirq;

	मुक्त_irq(kirq->irq, kirq);

	क्रम (hwirq = 0; hwirq < KEYSTONE_N_IRQ; hwirq++)
		irq_dispose_mapping(irq_find_mapping(kirq->irqd, hwirq));

	irq_करोमुख्य_हटाओ(kirq->irqd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id keystone_irq_dt_ids[] = अणु
	अणु .compatible = "ti,keystone-irq", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, keystone_irq_dt_ids);

अटल काष्ठा platक्रमm_driver keystone_irq_device_driver = अणु
	.probe		= keystone_irq_probe,
	.हटाओ		= keystone_irq_हटाओ,
	.driver		= अणु
		.name	= "keystone_irq",
		.of_match_table	= of_match_ptr(keystone_irq_dt_ids),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(keystone_irq_device_driver);

MODULE_AUTHOR("Texas Instruments");
MODULE_AUTHOR("Sajesh Kumar Saran");
MODULE_AUTHOR("Grygorii Strashko");
MODULE_DESCRIPTION("Keystone IRQ chip");
MODULE_LICENSE("GPL v2");
