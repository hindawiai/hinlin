<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Synopsys CREG (Control REGisters) GPIO driver
//
// Copyright (C) 2018 Synopsys
// Author: Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा MAX_GPIO	32

काष्ठा creg_layout अणु
	u8 ngpio;
	u8 shअगरt[MAX_GPIO];
	u8 on[MAX_GPIO];
	u8 off[MAX_GPIO];
	u8 bit_per_gpio[MAX_GPIO];
पूर्ण;

काष्ठा creg_gpio अणु
	काष्ठा gpio_chip gc;
	व्योम __iomem *regs;
	spinlock_t lock;
	स्थिर काष्ठा creg_layout *layout;
पूर्ण;

अटल व्योम creg_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा creg_gpio *hcg = gpiochip_get_data(gc);
	स्थिर काष्ठा creg_layout *layout = hcg->layout;
	u32 reg, reg_shअगरt, value;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	value = val ? hcg->layout->on[offset] : hcg->layout->off[offset];

	reg_shअगरt = layout->shअगरt[offset];
	क्रम (i = 0; i < offset; i++)
		reg_shअगरt += layout->bit_per_gpio[i] + layout->shअगरt[i];

	spin_lock_irqsave(&hcg->lock, flags);
	reg = पढ़ोl(hcg->regs);
	reg &= ~(GENMASK(layout->bit_per_gpio[i] - 1, 0) << reg_shअगरt);
	reg |=  (value << reg_shअगरt);
	ग_लिखोl(reg, hcg->regs);
	spin_unlock_irqrestore(&hcg->lock, flags);
पूर्ण

अटल पूर्णांक creg_gpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	creg_gpio_set(gc, offset, val);

	वापस 0;
पूर्ण

अटल पूर्णांक creg_gpio_validate_pg(काष्ठा device *dev, काष्ठा creg_gpio *hcg,
				 पूर्णांक i)
अणु
	स्थिर काष्ठा creg_layout *layout = hcg->layout;

	अगर (layout->bit_per_gpio[i] < 1 || layout->bit_per_gpio[i] > 8)
		वापस -EINVAL;

	/* Check that on value fits its placeholder */
	अगर (GENMASK(31, layout->bit_per_gpio[i]) & layout->on[i])
		वापस -EINVAL;

	/* Check that off value fits its placeholder */
	अगर (GENMASK(31, layout->bit_per_gpio[i]) & layout->off[i])
		वापस -EINVAL;

	अगर (layout->on[i] == layout->off[i])
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक creg_gpio_validate(काष्ठा device *dev, काष्ठा creg_gpio *hcg,
			      u32 ngpios)
अणु
	u32 reg_len = 0;
	पूर्णांक i;

	अगर (hcg->layout->ngpio < 1 || hcg->layout->ngpio > MAX_GPIO)
		वापस -EINVAL;

	अगर (ngpios < 1 || ngpios > hcg->layout->ngpio) अणु
		dev_err(dev, "ngpios must be in [1:%u]\n", hcg->layout->ngpio);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < hcg->layout->ngpio; i++) अणु
		अगर (creg_gpio_validate_pg(dev, hcg, i))
			वापस -EINVAL;

		reg_len += hcg->layout->shअगरt[i] + hcg->layout->bit_per_gpio[i];
	पूर्ण

	/* Check that we fit in 32 bit रेजिस्टर */
	अगर (reg_len > 32)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा creg_layout hsdk_cs_ctl = अणु
	.ngpio		= 10,
	.shअगरt		= अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	.off		= अणु 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 पूर्ण,
	.on		= अणु 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 पूर्ण,
	.bit_per_gpio	= अणु 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा creg_layout axs10x_flsh_cs_ctl = अणु
	.ngpio		= 1,
	.shअगरt		= अणु 0 पूर्ण,
	.off		= अणु 1 पूर्ण,
	.on		= अणु 3 पूर्ण,
	.bit_per_gpio	= अणु 2 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id creg_gpio_ids[] = अणु
	अणु
		.compatible = "snps,creg-gpio-axs10x",
		.data = &axs10x_flsh_cs_ctl
	पूर्ण, अणु
		.compatible = "snps,creg-gpio-hsdk",
		.data = &hsdk_cs_ctl
	पूर्ण, अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक creg_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा creg_gpio *hcg;
	u32 ngpios;
	पूर्णांक ret;

	hcg = devm_kzalloc(dev, माप(काष्ठा creg_gpio), GFP_KERNEL);
	अगर (!hcg)
		वापस -ENOMEM;

	hcg->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hcg->regs))
		वापस PTR_ERR(hcg->regs);

	match = of_match_node(creg_gpio_ids, pdev->dev.of_node);
	hcg->layout = match->data;
	अगर (!hcg->layout)
		वापस -EINVAL;

	ret = of_property_पढ़ो_u32(dev->of_node, "ngpios", &ngpios);
	अगर (ret)
		वापस ret;

	ret = creg_gpio_validate(dev, hcg, ngpios);
	अगर (ret)
		वापस ret;

	spin_lock_init(&hcg->lock);

	hcg->gc.label = dev_name(dev);
	hcg->gc.base = -1;
	hcg->gc.ngpio = ngpios;
	hcg->gc.set = creg_gpio_set;
	hcg->gc.direction_output = creg_gpio_dir_out;
	hcg->gc.of_node = dev->of_node;

	ret = devm_gpiochip_add_data(dev, &hcg->gc, hcg);
	अगर (ret)
		वापस ret;

	dev_info(dev, "GPIO controller with %d gpios probed\n", ngpios);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver creg_gpio_snps_driver = अणु
	.driver = अणु
		.name = "snps-creg-gpio",
		.of_match_table = creg_gpio_ids,
	पूर्ण,
	.probe  = creg_gpio_probe,
पूर्ण;
builtin_platक्रमm_driver(creg_gpio_snps_driver);
