<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम EXAR XRA1403 16-bit GPIO expander
 *
 * Copyright (c) 2017, General Electric Company
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>

/* XRA1403 रेजिस्टरs */
#घोषणा XRA_GSR   0x00 /* GPIO State */
#घोषणा XRA_OCR   0x02 /* Output Control */
#घोषणा XRA_PIR   0x04 /* Input Polarity Inversion */
#घोषणा XRA_GCR   0x06 /* GPIO Configuration */
#घोषणा XRA_PUR   0x08 /* Input Internal Pull-up Resistor Enable/Disable */
#घोषणा XRA_IER   0x0A /* Input Interrupt Enable */
#घोषणा XRA_TSCR  0x0C /* Output Three-State Control */
#घोषणा XRA_ISR   0x0E /* Input Interrupt Status */
#घोषणा XRA_REIR  0x10 /* Input Rising Edge Interrupt Enable */
#घोषणा XRA_FEIR  0x12 /* Input Falling Edge Interrupt Enable */
#घोषणा XRA_IFR   0x14 /* Input Filter Enable/Disable */
#घोषणा XRA_LAST  0x15 /* Bounds */

काष्ठा xra1403 अणु
	काष्ठा gpio_chip  chip;
	काष्ठा regmap     *regmap;
पूर्ण;

अटल स्थिर काष्ठा regmap_config xra1403_regmap_cfg = अणु
		.reg_bits = 7,
		.pad_bits = 1,
		.val_bits = 8,

		.max_रेजिस्टर = XRA_LAST,
पूर्ण;

अटल अचिन्हित पूर्णांक to_reg(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक offset)
अणु
	वापस reg + (offset > 7);
पूर्ण

अटल पूर्णांक xra1403_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा xra1403 *xra = gpiochip_get_data(chip);

	वापस regmap_update_bits(xra->regmap, to_reg(XRA_GCR, offset),
			BIT(offset % 8), BIT(offset % 8));
पूर्ण

अटल पूर्णांक xra1403_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				    पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा xra1403 *xra = gpiochip_get_data(chip);

	ret = regmap_update_bits(xra->regmap, to_reg(XRA_GCR, offset),
			BIT(offset % 8), 0);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(xra->regmap, to_reg(XRA_OCR, offset),
			BIT(offset % 8), value ? BIT(offset % 8) : 0);

	वापस ret;
पूर्ण

अटल पूर्णांक xra1403_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा xra1403 *xra = gpiochip_get_data(chip);

	ret = regmap_पढ़ो(xra->regmap, to_reg(XRA_GCR, offset), &val);
	अगर (ret)
		वापस ret;

	अगर (val & BIT(offset % 8))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक xra1403_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा xra1403 *xra = gpiochip_get_data(chip);

	ret = regmap_पढ़ो(xra->regmap, to_reg(XRA_GSR, offset), &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & BIT(offset % 8));
पूर्ण

अटल व्योम xra1403_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा xra1403 *xra = gpiochip_get_data(chip);

	ret = regmap_update_bits(xra->regmap, to_reg(XRA_OCR, offset),
			BIT(offset % 8), value ? BIT(offset % 8) : 0);
	अगर (ret)
		dev_err(chip->parent, "Failed to set pin: %d, ret: %d\n",
				offset, ret);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम xra1403_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	पूर्णांक reg;
	काष्ठा xra1403 *xra = gpiochip_get_data(chip);
	पूर्णांक value[XRA_LAST];
	पूर्णांक i;
	स्थिर अक्षर *label;
	अचिन्हित पूर्णांक gcr;
	अचिन्हित पूर्णांक gsr;

	seq_माला_दो(s, "xra reg:");
	क्रम (reg = 0; reg <= XRA_LAST; reg++)
		seq_म_लिखो(s, " %2.2x", reg);
	seq_माला_दो(s, "\n  value:");
	क्रम (reg = 0; reg < XRA_LAST; reg++) अणु
		regmap_पढ़ो(xra->regmap, reg, &value[reg]);
		seq_म_लिखो(s, " %2.2x", value[reg]);
	पूर्ण
	seq_माला_दो(s, "\n");

	gcr = value[XRA_GCR + 1] << 8 | value[XRA_GCR];
	gsr = value[XRA_GSR + 1] << 8 | value[XRA_GSR];
	क्रम_each_requested_gpio(chip, i, label) अणु
		seq_म_लिखो(s, " gpio-%-3d (%-12s) %s %s\n",
			   chip->base + i, label,
			   (gcr & BIT(i)) ? "in" : "out",
			   (gsr & BIT(i)) ? "hi" : "lo");
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा xra1403_dbg_show शून्य
#पूर्ण_अगर

अटल पूर्णांक xra1403_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा xra1403 *xra;
	काष्ठा gpio_desc *reset_gpio;
	पूर्णांक ret;

	xra = devm_kzalloc(&spi->dev, माप(*xra), GFP_KERNEL);
	अगर (!xra)
		वापस -ENOMEM;

	/* bring the chip out of reset अगर reset pin is provided*/
	reset_gpio = devm_gpiod_get_optional(&spi->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(reset_gpio))
		dev_warn(&spi->dev, "Could not get reset-gpios\n");

	xra->chip.direction_input = xra1403_direction_input;
	xra->chip.direction_output = xra1403_direction_output;
	xra->chip.get_direction = xra1403_get_direction;
	xra->chip.get = xra1403_get;
	xra->chip.set = xra1403_set;

	xra->chip.dbg_show = xra1403_dbg_show;

	xra->chip.ngpio = 16;
	xra->chip.label = "xra1403";

	xra->chip.base = -1;
	xra->chip.can_sleep = true;
	xra->chip.parent = &spi->dev;
	xra->chip.owner = THIS_MODULE;

	xra->regmap = devm_regmap_init_spi(spi, &xra1403_regmap_cfg);
	अगर (IS_ERR(xra->regmap)) अणु
		ret = PTR_ERR(xra->regmap);
		dev_err(&spi->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_gpiochip_add_data(&spi->dev, &xra->chip, xra);
पूर्ण

अटल स्थिर काष्ठा spi_device_id xra1403_ids[] = अणु
	अणु "xra1403" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, xra1403_ids);

अटल स्थिर काष्ठा of_device_id xra1403_spi_of_match[] = अणु
	अणु .compatible = "exar,xra1403" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xra1403_spi_of_match);

अटल काष्ठा spi_driver xra1403_driver = अणु
	.probe    = xra1403_probe,
	.id_table = xra1403_ids,
	.driver   = अणु
		.name           = "xra1403",
		.of_match_table = of_match_ptr(xra1403_spi_of_match),
	पूर्ण,
पूर्ण;

module_spi_driver(xra1403_driver);

MODULE_AUTHOR("Nandor Han <nandor.han@ge.com>");
MODULE_AUTHOR("Semi Malinen <semi.malinen@ge.com>");
MODULE_DESCRIPTION("GPIO expander driver for EXAR XRA1403");
MODULE_LICENSE("GPL v2");
