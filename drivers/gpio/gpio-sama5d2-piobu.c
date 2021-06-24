<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SAMA5D2 PIOBU GPIO controller
 *
 * Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
 *
 * Author: Andrei Stefanescu <andrei.stefanescu@microchip.com>
 *
 */
#समावेश <linux/bits.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा PIOBU_NUM 8
#घोषणा PIOBU_REG_SIZE 4

/*
 * backup mode protection रेजिस्टर क्रम tamper detection
 * normal mode protection रेजिस्टर क्रम tamper detection
 * wakeup संकेत generation
 */
#घोषणा PIOBU_BMPR 0x7C
#घोषणा PIOBU_NMPR 0x80
#घोषणा PIOBU_WKPR 0x90

#घोषणा PIOBU_BASE 0x18 /* PIOBU offset from SECUMOD base रेजिस्टर address. */

#घोषणा PIOBU_DET_OFFSET 16

/* In the datasheet this bit is called OUTPUT */
#घोषणा PIOBU_सूचीECTION BIT(8)
#घोषणा PIOBU_OUT BIT(8)
#घोषणा PIOBU_IN 0

#घोषणा PIOBU_SOD BIT(9)
#घोषणा PIOBU_PDS BIT(10)

#घोषणा PIOBU_HIGH BIT(9)
#घोषणा PIOBU_LOW 0

काष्ठा sama5d2_piobu अणु
	काष्ठा gpio_chip chip;
	काष्ठा regmap *regmap;
पूर्ण;

/*
 * sama5d2_piobu_setup_pin() - prepares a pin क्रम set_direction call
 *
 * Do not consider pin क्रम tamper detection (normal and backup modes)
 * Do not consider pin as tamper wakeup पूर्णांकerrupt source
 */
अटल पूर्णांक sama5d2_piobu_setup_pin(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक ret;
	काष्ठा sama5d2_piobu *piobu = container_of(chip, काष्ठा sama5d2_piobu,
						   chip);
	अचिन्हित पूर्णांक mask = BIT(PIOBU_DET_OFFSET + pin);

	ret = regmap_update_bits(piobu->regmap, PIOBU_BMPR, mask, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(piobu->regmap, PIOBU_NMPR, mask, 0);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(piobu->regmap, PIOBU_WKPR, mask, 0);
पूर्ण

/*
 * sama5d2_piobu_ग_लिखो_value() - ग_लिखोs value & mask at the pin's PIOBU रेजिस्टर
 */
अटल पूर्णांक sama5d2_piobu_ग_लिखो_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin,
				     अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक value)
अणु
	पूर्णांक reg;
	काष्ठा sama5d2_piobu *piobu = container_of(chip, काष्ठा sama5d2_piobu,
						   chip);

	reg = PIOBU_BASE + pin * PIOBU_REG_SIZE;

	वापस regmap_update_bits(piobu->regmap, reg, mask, value);
पूर्ण

/*
 * sama5d2_piobu_पढ़ो_value() - पढ़ो the value with masking from the pin's PIOBU
 *			      रेजिस्टर
 */
अटल पूर्णांक sama5d2_piobu_पढ़ो_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin,
				    अचिन्हित पूर्णांक mask)
अणु
	काष्ठा sama5d2_piobu *piobu = container_of(chip, काष्ठा sama5d2_piobu,
						   chip);
	अचिन्हित पूर्णांक val, reg;
	पूर्णांक ret;

	reg = PIOBU_BASE + pin * PIOBU_REG_SIZE;
	ret = regmap_पढ़ो(piobu->regmap, reg, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val & mask;
पूर्ण

/*
 * sama5d2_piobu_get_direction() - gpiochip get_direction
 */
अटल पूर्णांक sama5d2_piobu_get_direction(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक ret = sama5d2_piobu_पढ़ो_value(chip, pin, PIOBU_सूचीECTION);

	अगर (ret < 0)
		वापस ret;

	वापस (ret == PIOBU_IN) ? GPIO_LINE_सूचीECTION_IN :
				   GPIO_LINE_सूचीECTION_OUT;
पूर्ण

/*
 * sama5d2_piobu_direction_input() - gpiochip direction_input
 */
अटल पूर्णांक sama5d2_piobu_direction_input(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक pin)
अणु
	वापस sama5d2_piobu_ग_लिखो_value(chip, pin, PIOBU_सूचीECTION, PIOBU_IN);
पूर्ण

/*
 * sama5d2_piobu_direction_output() - gpiochip direction_output
 */
अटल पूर्णांक sama5d2_piobu_direction_output(काष्ठा gpio_chip *chip,
					  अचिन्हित पूर्णांक pin, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक val = PIOBU_OUT;

	अगर (value)
		val |= PIOBU_HIGH;

	वापस sama5d2_piobu_ग_लिखो_value(chip, pin, PIOBU_सूचीECTION | PIOBU_SOD,
					 val);
पूर्ण

/*
 * sama5d2_piobu_get() - gpiochip get
 */
अटल पूर्णांक sama5d2_piobu_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	/* अगर pin is input, पढ़ो value from PDS अन्यथा पढ़ो from SOD */
	पूर्णांक ret = sama5d2_piobu_get_direction(chip, pin);

	अगर (ret == GPIO_LINE_सूचीECTION_IN)
		ret = sama5d2_piobu_पढ़ो_value(chip, pin, PIOBU_PDS);
	अन्यथा अगर (ret == GPIO_LINE_सूचीECTION_OUT)
		ret = sama5d2_piobu_पढ़ो_value(chip, pin, PIOBU_SOD);

	अगर (ret < 0)
		वापस ret;

	वापस !!ret;
पूर्ण

/*
 * sama5d2_piobu_set() - gpiochip set
 */
अटल व्योम sama5d2_piobu_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin,
			      पूर्णांक value)
अणु
	अगर (!value)
		value = PIOBU_LOW;
	अन्यथा
		value = PIOBU_HIGH;

	sama5d2_piobu_ग_लिखो_value(chip, pin, PIOBU_SOD, value);
पूर्ण

अटल पूर्णांक sama5d2_piobu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sama5d2_piobu *piobu;
	पूर्णांक ret, i;

	piobu = devm_kzalloc(&pdev->dev, माप(*piobu), GFP_KERNEL);
	अगर (!piobu)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, piobu);
	piobu->chip.label = pdev->name;
	piobu->chip.parent = &pdev->dev;
	piobu->chip.of_node = pdev->dev.of_node;
	piobu->chip.owner = THIS_MODULE,
	piobu->chip.get_direction = sama5d2_piobu_get_direction,
	piobu->chip.direction_input = sama5d2_piobu_direction_input,
	piobu->chip.direction_output = sama5d2_piobu_direction_output,
	piobu->chip.get = sama5d2_piobu_get,
	piobu->chip.set = sama5d2_piobu_set,
	piobu->chip.base = -1,
	piobu->chip.ngpio = PIOBU_NUM,
	piobu->chip.can_sleep = 0,

	piobu->regmap = syscon_node_to_regmap(pdev->dev.of_node);
	अगर (IS_ERR(piobu->regmap)) अणु
		dev_err(&pdev->dev, "Failed to get syscon regmap %ld\n",
			PTR_ERR(piobu->regmap));
		वापस PTR_ERR(piobu->regmap);
	पूर्ण

	ret = devm_gpiochip_add_data(&pdev->dev, &piobu->chip, piobu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add gpiochip %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < PIOBU_NUM; ++i) अणु
		ret = sama5d2_piobu_setup_pin(&piobu->chip, i);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to setup pin: %d %d\n",
				i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sama5d2_piobu_ids[] = अणु
	अणु .compatible = "atmel,sama5d2-secumod" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sama5d2_piobu_ids);

अटल काष्ठा platक्रमm_driver sama5d2_piobu_driver = अणु
	.driver = अणु
		.name		= "sama5d2-piobu",
		.of_match_table	= of_match_ptr(sama5d2_piobu_ids)
	पूर्ण,
	.probe = sama5d2_piobu_probe,
पूर्ण;

module_platक्रमm_driver(sama5d2_piobu_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SAMA5D2 PIOBU controller driver");
MODULE_AUTHOR("Andrei Stefanescu <andrei.stefanescu@microchip.com>");
