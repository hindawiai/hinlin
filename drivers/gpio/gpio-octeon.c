<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2011, 2012 Cavium Inc.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-gpio-defs.h>

#घोषणा RX_DAT 0x80
#घोषणा TX_SET 0x88
#घोषणा TX_CLEAR 0x90
/*
 * The address offset of the GPIO configuration रेजिस्टर क्रम a given
 * line.
 */
अटल अचिन्हित पूर्णांक bit_cfg_reg(अचिन्हित पूर्णांक offset)
अणु
	/*
	 * The रेजिस्टर stride is 8, with a discontinuity after the
	 * first 16.
	 */
	अगर (offset < 16)
		वापस 8 * offset;
	अन्यथा
		वापस 8 * (offset - 16) + 0x100;
पूर्ण

काष्ठा octeon_gpio अणु
	काष्ठा gpio_chip chip;
	u64 रेजिस्टर_base;
पूर्ण;

अटल पूर्णांक octeon_gpio_dir_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा octeon_gpio *gpio = gpiochip_get_data(chip);

	cvmx_ग_लिखो_csr(gpio->रेजिस्टर_base + bit_cfg_reg(offset), 0);
	वापस 0;
पूर्ण

अटल व्योम octeon_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा octeon_gpio *gpio = gpiochip_get_data(chip);
	u64 mask = 1ull << offset;
	u64 reg = gpio->रेजिस्टर_base + (value ? TX_SET : TX_CLEAR);
	cvmx_ग_लिखो_csr(reg, mask);
पूर्ण

अटल पूर्णांक octeon_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित offset,
			       पूर्णांक value)
अणु
	काष्ठा octeon_gpio *gpio = gpiochip_get_data(chip);
	जोड़ cvmx_gpio_bit_cfgx cfgx;

	octeon_gpio_set(chip, offset, value);

	cfgx.u64 = 0;
	cfgx.s.tx_oe = 1;

	cvmx_ग_लिखो_csr(gpio->रेजिस्टर_base + bit_cfg_reg(offset), cfgx.u64);
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा octeon_gpio *gpio = gpiochip_get_data(chip);
	u64 पढ़ो_bits = cvmx_पढ़ो_csr(gpio->रेजिस्टर_base + RX_DAT);

	वापस ((1ull << offset) & पढ़ो_bits) != 0;
पूर्ण

अटल पूर्णांक octeon_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा octeon_gpio *gpio;
	काष्ठा gpio_chip *chip;
	व्योम __iomem *reg_base;
	पूर्णांक err = 0;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;
	chip = &gpio->chip;

	reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);

	gpio->रेजिस्टर_base = (u64)reg_base;
	pdev->dev.platक्रमm_data = chip;
	chip->label = "octeon-gpio";
	chip->parent = &pdev->dev;
	chip->owner = THIS_MODULE;
	chip->base = 0;
	chip->can_sleep = false;
	chip->ngpio = 20;
	chip->direction_input = octeon_gpio_dir_in;
	chip->get = octeon_gpio_get;
	chip->direction_output = octeon_gpio_dir_out;
	chip->set = octeon_gpio_set;
	err = devm_gpiochip_add_data(&pdev->dev, chip, gpio);
	अगर (err)
		वापस err;

	dev_info(&pdev->dev, "OCTEON GPIO driver probed.\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id octeon_gpio_match[] = अणु
	अणु
		.compatible = "cavium,octeon-3860-gpio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, octeon_gpio_match);

अटल काष्ठा platक्रमm_driver octeon_gpio_driver = अणु
	.driver = अणु
		.name		= "octeon_gpio",
		.of_match_table = octeon_gpio_match,
	पूर्ण,
	.probe		= octeon_gpio_probe,
पूर्ण;

module_platक्रमm_driver(octeon_gpio_driver);

MODULE_DESCRIPTION("Cavium Inc. OCTEON GPIO Driver");
MODULE_AUTHOR("David Daney");
MODULE_LICENSE("GPL");
