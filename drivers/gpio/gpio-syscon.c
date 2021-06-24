<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  SYSCON GPIO driver
 *
 *  Copyright (C) 2014 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#घोषणा GPIO_SYSCON_FEAT_IN	BIT(0)
#घोषणा GPIO_SYSCON_FEAT_OUT	BIT(1)
#घोषणा GPIO_SYSCON_FEAT_सूची	BIT(2)

/* SYSCON driver is deचिन्हित to use 32-bit wide रेजिस्टरs */
#घोषणा SYSCON_REG_SIZE		(4)
#घोषणा SYSCON_REG_BITS		(SYSCON_REG_SIZE * 8)

/**
 * काष्ठा syscon_gpio_data - Configuration क्रम the device.
 * @compatible:		SYSCON driver compatible string.
 * @flags:		Set of GPIO_SYSCON_FEAT_ flags:
 *			GPIO_SYSCON_FEAT_IN:	GPIOs supports input,
 *			GPIO_SYSCON_FEAT_OUT:	GPIOs supports output,
 *			GPIO_SYSCON_FEAT_सूची:	GPIOs supports चयन direction.
 * @bit_count:		Number of bits used as GPIOs.
 * @dat_bit_offset:	Offset (in bits) to the first GPIO bit.
 * @dir_bit_offset:	Optional offset (in bits) to the first bit to चयन
 *			GPIO direction (Used with GPIO_SYSCON_FEAT_सूची flag).
 * @set:		HW specअगरic callback to assigns output value
 *			क्रम संकेत "offset"
 */

काष्ठा syscon_gpio_data अणु
	स्थिर अक्षर	*compatible;
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	bit_count;
	अचिन्हित पूर्णांक	dat_bit_offset;
	अचिन्हित पूर्णांक	dir_bit_offset;
	व्योम		(*set)(काष्ठा gpio_chip *chip,
			       अचिन्हित offset, पूर्णांक value);
पूर्ण;

काष्ठा syscon_gpio_priv अणु
	काष्ठा gpio_chip		chip;
	काष्ठा regmap			*syscon;
	स्थिर काष्ठा syscon_gpio_data	*data;
	u32				dreg_offset;
	u32				dir_reg_offset;
पूर्ण;

अटल पूर्णांक syscon_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा syscon_gpio_priv *priv = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val, offs;
	पूर्णांक ret;

	offs = priv->dreg_offset + priv->data->dat_bit_offset + offset;

	ret = regmap_पढ़ो(priv->syscon,
			  (offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & BIT(offs % SYSCON_REG_BITS));
पूर्ण

अटल व्योम syscon_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा syscon_gpio_priv *priv = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक offs;

	offs = priv->dreg_offset + priv->data->dat_bit_offset + offset;

	regmap_update_bits(priv->syscon,
			   (offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE,
			   BIT(offs % SYSCON_REG_BITS),
			   val ? BIT(offs % SYSCON_REG_BITS) : 0);
पूर्ण

अटल पूर्णांक syscon_gpio_dir_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा syscon_gpio_priv *priv = gpiochip_get_data(chip);

	अगर (priv->data->flags & GPIO_SYSCON_FEAT_सूची) अणु
		अचिन्हित पूर्णांक offs;

		offs = priv->dir_reg_offset +
		       priv->data->dir_bit_offset + offset;

		regmap_update_bits(priv->syscon,
				   (offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE,
				   BIT(offs % SYSCON_REG_BITS), 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक syscon_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा syscon_gpio_priv *priv = gpiochip_get_data(chip);

	अगर (priv->data->flags & GPIO_SYSCON_FEAT_सूची) अणु
		अचिन्हित पूर्णांक offs;

		offs = priv->dir_reg_offset +
		       priv->data->dir_bit_offset + offset;

		regmap_update_bits(priv->syscon,
				   (offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE,
				   BIT(offs % SYSCON_REG_BITS),
				   BIT(offs % SYSCON_REG_BITS));
	पूर्ण

	chip->set(chip, offset, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा syscon_gpio_data clps711x_mctrl_gpio = अणु
	/* ARM CLPS711X SYSFLG1 Bits 8-10 */
	.compatible	= "cirrus,ep7209-syscon1",
	.flags		= GPIO_SYSCON_FEAT_IN,
	.bit_count	= 3,
	.dat_bit_offset	= 0x40 * 8 + 8,
पूर्ण;

अटल व्योम rockchip_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			      पूर्णांक val)
अणु
	काष्ठा syscon_gpio_priv *priv = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक offs;
	u8 bit;
	u32 data;
	पूर्णांक ret;

	offs = priv->dreg_offset + priv->data->dat_bit_offset + offset;
	bit = offs % SYSCON_REG_BITS;
	data = (val ? BIT(bit) : 0) | BIT(bit + 16);
	ret = regmap_ग_लिखो(priv->syscon,
			   (offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE,
			   data);
	अगर (ret < 0)
		dev_err(chip->parent, "gpio write failed ret(%d)\n", ret);
पूर्ण

अटल स्थिर काष्ठा syscon_gpio_data rockchip_rk3328_gpio_mute = अणु
	/* RK3328 GPIO_MUTE is an output only pin at GRF_SOC_CON10[1] */
	.flags		= GPIO_SYSCON_FEAT_OUT,
	.bit_count	= 1,
	.dat_bit_offset = 0x0428 * 8 + 1,
	.set		= rockchip_gpio_set,
पूर्ण;

#घोषणा KEYSTONE_LOCK_BIT BIT(0)

अटल व्योम keystone_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा syscon_gpio_priv *priv = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक offs;
	पूर्णांक ret;

	offs = priv->dreg_offset + priv->data->dat_bit_offset + offset;

	अगर (!val)
		वापस;

	ret = regmap_update_bits(
			priv->syscon,
			(offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE,
			BIT(offs % SYSCON_REG_BITS) | KEYSTONE_LOCK_BIT,
			BIT(offs % SYSCON_REG_BITS) | KEYSTONE_LOCK_BIT);
	अगर (ret < 0)
		dev_err(chip->parent, "gpio write failed ret(%d)\n", ret);
पूर्ण

अटल स्थिर काष्ठा syscon_gpio_data keystone_dsp_gpio = अणु
	/* ARM Keystone 2 */
	.compatible	= शून्य,
	.flags		= GPIO_SYSCON_FEAT_OUT,
	.bit_count	= 28,
	.dat_bit_offset	= 4,
	.set		= keystone_gpio_set,
पूर्ण;

अटल स्थिर काष्ठा of_device_id syscon_gpio_ids[] = अणु
	अणु
		.compatible	= "cirrus,ep7209-mctrl-gpio",
		.data		= &clps711x_mctrl_gpio,
	पूर्ण,
	अणु
		.compatible	= "ti,keystone-dsp-gpio",
		.data		= &keystone_dsp_gpio,
	पूर्ण,
	अणु
		.compatible	= "rockchip,rk3328-grf-gpio",
		.data		= &rockchip_rk3328_gpio_mute,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, syscon_gpio_ids);

अटल पूर्णांक syscon_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा syscon_gpio_priv *priv;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->data = of_device_get_match_data(dev);

	अगर (priv->data->compatible) अणु
		priv->syscon = syscon_regmap_lookup_by_compatible(
					priv->data->compatible);
		अगर (IS_ERR(priv->syscon))
			वापस PTR_ERR(priv->syscon);
	पूर्ण अन्यथा अणु
		priv->syscon =
			syscon_regmap_lookup_by_phandle(np, "gpio,syscon-dev");
		अगर (IS_ERR(priv->syscon) && np->parent)
			priv->syscon = syscon_node_to_regmap(np->parent);
		अगर (IS_ERR(priv->syscon))
			वापस PTR_ERR(priv->syscon);

		ret = of_property_पढ़ो_u32_index(np, "gpio,syscon-dev", 1,
						 &priv->dreg_offset);
		अगर (ret)
			dev_err(dev, "can't read the data register offset!\n");

		priv->dreg_offset <<= 3;

		ret = of_property_पढ़ो_u32_index(np, "gpio,syscon-dev", 2,
						 &priv->dir_reg_offset);
		अगर (ret)
			dev_dbg(dev, "can't read the dir register offset!\n");

		priv->dir_reg_offset <<= 3;
	पूर्ण

	priv->chip.parent = dev;
	priv->chip.owner = THIS_MODULE;
	priv->chip.label = dev_name(dev);
	priv->chip.base = -1;
	priv->chip.ngpio = priv->data->bit_count;
	priv->chip.get = syscon_gpio_get;
	अगर (priv->data->flags & GPIO_SYSCON_FEAT_IN)
		priv->chip.direction_input = syscon_gpio_dir_in;
	अगर (priv->data->flags & GPIO_SYSCON_FEAT_OUT) अणु
		priv->chip.set = priv->data->set ? : syscon_gpio_set;
		priv->chip.direction_output = syscon_gpio_dir_out;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	वापस devm_gpiochip_add_data(&pdev->dev, &priv->chip, priv);
पूर्ण

अटल काष्ठा platक्रमm_driver syscon_gpio_driver = अणु
	.driver	= अणु
		.name		= "gpio-syscon",
		.of_match_table	= syscon_gpio_ids,
	पूर्ण,
	.probe	= syscon_gpio_probe,
पूर्ण;
module_platक्रमm_driver(syscon_gpio_driver);

MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("SYSCON GPIO driver");
MODULE_LICENSE("GPL");
