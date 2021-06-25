<शैली गुरु>
/*
 * GPIO driver क्रम the TS-4800 board
 *
 * Copyright (c) 2016 - Savoir-faire Linux
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DEFAULT_PIN_NUMBER      16
#घोषणा INPUT_REG_OFFSET        0x00
#घोषणा OUTPUT_REG_OFFSET       0x02
#घोषणा सूचीECTION_REG_OFFSET    0x04

अटल पूर्णांक ts4800_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node;
	काष्ठा gpio_chip *chip;
	व्योम __iomem *base_addr;
	पूर्णांक retval;
	u32 ngpios;

	chip = devm_kzalloc(&pdev->dev, माप(काष्ठा gpio_chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base_addr))
		वापस PTR_ERR(base_addr);

	node = pdev->dev.of_node;
	अगर (!node)
		वापस -EINVAL;

	retval = of_property_पढ़ो_u32(node, "ngpios", &ngpios);
	अगर (retval == -EINVAL)
		ngpios = DEFAULT_PIN_NUMBER;
	अन्यथा अगर (retval)
		वापस retval;

	retval = bgpio_init(chip, &pdev->dev, 2, base_addr + INPUT_REG_OFFSET,
			    base_addr + OUTPUT_REG_OFFSET, शून्य,
			    base_addr + सूचीECTION_REG_OFFSET, शून्य, 0);
	अगर (retval) अणु
		dev_err(&pdev->dev, "bgpio_init failed\n");
		वापस retval;
	पूर्ण

	chip->ngpio = ngpios;

	platक्रमm_set_drvdata(pdev, chip);

	वापस devm_gpiochip_add_data(&pdev->dev, chip, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id ts4800_gpio_of_match[] = अणु
	अणु .compatible = "technologic,ts4800-gpio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ts4800_gpio_of_match);

अटल काष्ठा platक्रमm_driver ts4800_gpio_driver = अणु
	.driver = अणु
		   .name = "ts4800-gpio",
		   .of_match_table = ts4800_gpio_of_match,
		   पूर्ण,
	.probe = ts4800_gpio_probe,
पूर्ण;

module_platक्रमm_driver_probe(ts4800_gpio_driver, ts4800_gpio_probe);

MODULE_AUTHOR("Julien Grossholtz <julien.grossholtz@savoirfairelinux.com>");
MODULE_DESCRIPTION("TS4800 FPGA GPIO driver");
MODULE_LICENSE("GPL v2");
