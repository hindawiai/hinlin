<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Amlogic Meson Reset Controller driver
 *
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/of_device.h>

#घोषणा BITS_PER_REG	32

काष्ठा meson_reset_param अणु
	पूर्णांक reg_count;
	पूर्णांक level_offset;
पूर्ण;

काष्ठा meson_reset अणु
	व्योम __iomem *reg_base;
	स्थिर काष्ठा meson_reset_param *param;
	काष्ठा reset_controller_dev rcdev;
	spinlock_t lock;
पूर्ण;

अटल पूर्णांक meson_reset_reset(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा meson_reset *data =
		container_of(rcdev, काष्ठा meson_reset, rcdev);
	अचिन्हित पूर्णांक bank = id / BITS_PER_REG;
	अचिन्हित पूर्णांक offset = id % BITS_PER_REG;
	व्योम __iomem *reg_addr = data->reg_base + (bank << 2);

	ग_लिखोl(BIT(offset), reg_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_reset_level(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा meson_reset *data =
		container_of(rcdev, काष्ठा meson_reset, rcdev);
	अचिन्हित पूर्णांक bank = id / BITS_PER_REG;
	अचिन्हित पूर्णांक offset = id % BITS_PER_REG;
	व्योम __iomem *reg_addr;
	अचिन्हित दीर्घ flags;
	u32 reg;

	reg_addr = data->reg_base + data->param->level_offset + (bank << 2);

	spin_lock_irqsave(&data->lock, flags);

	reg = पढ़ोl(reg_addr);
	अगर (निश्चित)
		ग_लिखोl(reg & ~BIT(offset), reg_addr);
	अन्यथा
		ग_लिखोl(reg | BIT(offset), reg_addr);

	spin_unlock_irqrestore(&data->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	वापस meson_reset_level(rcdev, id, true);
पूर्ण

अटल पूर्णांक meson_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	वापस meson_reset_level(rcdev, id, false);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops meson_reset_ops = अणु
	.reset		= meson_reset_reset,
	.निश्चित		= meson_reset_निश्चित,
	.deनिश्चित	= meson_reset_deनिश्चित,
पूर्ण;

अटल स्थिर काष्ठा meson_reset_param meson8b_param = अणु
	.reg_count	= 8,
	.level_offset	= 0x7c,
पूर्ण;

अटल स्थिर काष्ठा meson_reset_param meson_a1_param = अणु
	.reg_count	= 3,
	.level_offset	= 0x40,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_reset_dt_ids[] = अणु
	 अणु .compatible = "amlogic,meson8b-reset",    .data = &meson8b_paramपूर्ण,
	 अणु .compatible = "amlogic,meson-gxbb-reset", .data = &meson8b_paramपूर्ण,
	 अणु .compatible = "amlogic,meson-axg-reset",  .data = &meson8b_paramपूर्ण,
	 अणु .compatible = "amlogic,meson-a1-reset",   .data = &meson_a1_paramपूर्ण,
	 अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_reset_dt_ids);

अटल पूर्णांक meson_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_reset *data;
	काष्ठा resource *res;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->reg_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(data->reg_base))
		वापस PTR_ERR(data->reg_base);

	data->param = of_device_get_match_data(&pdev->dev);
	अगर (!data->param)
		वापस -ENODEV;

	platक्रमm_set_drvdata(pdev, data);

	spin_lock_init(&data->lock);

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = data->param->reg_count * BITS_PER_REG;
	data->rcdev.ops = &meson_reset_ops;
	data->rcdev.of_node = pdev->dev.of_node;

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev, &data->rcdev);
पूर्ण

अटल काष्ठा platक्रमm_driver meson_reset_driver = अणु
	.probe	= meson_reset_probe,
	.driver = अणु
		.name		= "meson_reset",
		.of_match_table	= meson_reset_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_reset_driver);

MODULE_DESCRIPTION("Amlogic Meson Reset Controller driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("Dual BSD/GPL");
