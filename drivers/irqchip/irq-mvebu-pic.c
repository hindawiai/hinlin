<शैली गुरु>
/*
 * Copyright (C) 2016 Marvell
 *
 * Yehuda Yitschak <yehuday@marvell.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा PIC_CAUSE	       0x0
#घोषणा PIC_MASK	       0x4

#घोषणा PIC_MAX_IRQS		32
#घोषणा PIC_MAX_IRQ_MASK	((1UL << PIC_MAX_IRQS) - 1)

काष्ठा mvebu_pic अणु
	व्योम __iomem *base;
	u32 parent_irq;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip irq_chip;
पूर्ण;

अटल व्योम mvebu_pic_reset(काष्ठा mvebu_pic *pic)
अणु
	/* ACK and mask all पूर्णांकerrupts */
	ग_लिखोl(0, pic->base + PIC_MASK);
	ग_लिखोl(PIC_MAX_IRQ_MASK, pic->base + PIC_CAUSE);
पूर्ण

अटल व्योम mvebu_pic_eoi_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mvebu_pic *pic = irq_data_get_irq_chip_data(d);

	ग_लिखोl(1 << d->hwirq, pic->base + PIC_CAUSE);
पूर्ण

अटल व्योम mvebu_pic_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mvebu_pic *pic = irq_data_get_irq_chip_data(d);
	u32 reg;

	reg =  पढ़ोl(pic->base + PIC_MASK);
	reg |= (1 << d->hwirq);
	ग_लिखोl(reg, pic->base + PIC_MASK);
पूर्ण

अटल व्योम mvebu_pic_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mvebu_pic *pic = irq_data_get_irq_chip_data(d);
	u32 reg;

	reg = पढ़ोl(pic->base + PIC_MASK);
	reg &= ~(1 << d->hwirq);
	ग_लिखोl(reg, pic->base + PIC_MASK);
पूर्ण

अटल पूर्णांक mvebu_pic_irq_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			     irq_hw_number_t hwirq)
अणु
	काष्ठा mvebu_pic *pic = करोमुख्य->host_data;

	irq_set_percpu_devid(virq);
	irq_set_chip_data(virq, pic);
	irq_set_chip_and_handler(virq, &pic->irq_chip,
				 handle_percpu_devid_irq);
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_probe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mvebu_pic_करोमुख्य_ops = अणु
	.map = mvebu_pic_irq_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल व्योम mvebu_pic_handle_cascade_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा mvebu_pic *pic = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ irqmap, irqn;
	अचिन्हित पूर्णांक cascade_irq;

	irqmap = पढ़ोl_relaxed(pic->base + PIC_CAUSE);
	chained_irq_enter(chip, desc);

	क्रम_each_set_bit(irqn, &irqmap, BITS_PER_LONG) अणु
		cascade_irq = irq_find_mapping(pic->करोमुख्य, irqn);
		generic_handle_irq(cascade_irq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम mvebu_pic_enable_percpu_irq(व्योम *data)
अणु
	काष्ठा mvebu_pic *pic = data;

	mvebu_pic_reset(pic);
	enable_percpu_irq(pic->parent_irq, IRQ_TYPE_NONE);
पूर्ण

अटल व्योम mvebu_pic_disable_percpu_irq(व्योम *data)
अणु
	काष्ठा mvebu_pic *pic = data;

	disable_percpu_irq(pic->parent_irq);
पूर्ण

अटल पूर्णांक mvebu_pic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा mvebu_pic *pic;
	काष्ठा irq_chip *irq_chip;
	काष्ठा resource *res;

	pic = devm_kzalloc(&pdev->dev, माप(काष्ठा mvebu_pic), GFP_KERNEL);
	अगर (!pic)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pic->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(pic->base))
		वापस PTR_ERR(pic->base);

	irq_chip = &pic->irq_chip;
	irq_chip->name = dev_name(&pdev->dev);
	irq_chip->irq_mask = mvebu_pic_mask_irq;
	irq_chip->irq_unmask = mvebu_pic_unmask_irq;
	irq_chip->irq_eoi = mvebu_pic_eoi_irq;

	pic->parent_irq = irq_of_parse_and_map(node, 0);
	अगर (pic->parent_irq <= 0) अणु
		dev_err(&pdev->dev, "Failed to parse parent interrupt\n");
		वापस -EINVAL;
	पूर्ण

	pic->करोमुख्य = irq_करोमुख्य_add_linear(node, PIC_MAX_IRQS,
					    &mvebu_pic_करोमुख्य_ops, pic);
	अगर (!pic->करोमुख्य) अणु
		dev_err(&pdev->dev, "Failed to allocate irq domain\n");
		वापस -ENOMEM;
	पूर्ण

	irq_set_chained_handler(pic->parent_irq, mvebu_pic_handle_cascade_irq);
	irq_set_handler_data(pic->parent_irq, pic);

	on_each_cpu(mvebu_pic_enable_percpu_irq, pic, 1);

	platक्रमm_set_drvdata(pdev, pic);

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_pic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_pic *pic = platक्रमm_get_drvdata(pdev);

	on_each_cpu(mvebu_pic_disable_percpu_irq, pic, 1);
	irq_करोमुख्य_हटाओ(pic->करोमुख्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mvebu_pic_of_match[] = अणु
	अणु .compatible = "marvell,armada-8k-pic", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mvebu_pic_of_match);

अटल काष्ठा platक्रमm_driver mvebu_pic_driver = अणु
	.probe  = mvebu_pic_probe,
	.हटाओ = mvebu_pic_हटाओ,
	.driver = अणु
		.name = "mvebu-pic",
		.of_match_table = mvebu_pic_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mvebu_pic_driver);

MODULE_AUTHOR("Yehuda Yitschak <yehuday@marvell.com>");
MODULE_AUTHOR("Thomas Petazzoni <thomas.petazzoni@free-electrons.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:mvebu_pic");

