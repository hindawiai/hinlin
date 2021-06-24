<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Conexant Digicolor General Purpose Pin Mapping
 *
 * Author: Baruch Siach <baruch@tkos.co.il>
 *
 * Copyright (C) 2015 Paraकरोx Innovation Ltd.
 *
 * TODO:
 * - GPIO पूर्णांकerrupt support
 * - Pin pad configuration (pull up/करोwn, strength)
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश "pinctrl-utils.h"

#घोषणा DRIVER_NAME	"pinctrl-digicolor"

#घोषणा GP_CLIENTSEL(clct)	((clct)*8 + 0x20)
#घोषणा GP_DRIVE0(clct)		(GP_CLIENTSEL(clct) + 2)
#घोषणा GP_OUTPUT0(clct)	(GP_CLIENTSEL(clct) + 3)
#घोषणा GP_INPUT(clct)		(GP_CLIENTSEL(clct) + 6)

#घोषणा PIN_COLLECTIONS		('R' - 'A' + 1)
#घोषणा PINS_PER_COLLECTION	8
#घोषणा PINS_COUNT		(PIN_COLLECTIONS * PINS_PER_COLLECTION)

काष्ठा dc_pinmap अणु
	व्योम __iomem		*regs;
	काष्ठा device		*dev;
	काष्ठा pinctrl_dev	*pctl;

	काष्ठा pinctrl_desc	*desc;
	स्थिर अक्षर		*pin_names[PINS_COUNT];

	काष्ठा gpio_chip	chip;
	spinlock_t		lock;
पूर्ण;

अटल पूर्णांक dc_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस PINS_COUNT;
पूर्ण

अटल स्थिर अक्षर *dc_get_group_name(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित selector)
अणु
	काष्ठा dc_pinmap *pmap = pinctrl_dev_get_drvdata(pctldev);

	/* Exactly one group per pin */
	वापस pmap->desc->pins[selector].name;
पूर्ण

अटल पूर्णांक dc_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			     स्थिर अचिन्हित **pins,
			     अचिन्हित *num_pins)
अणु
	काष्ठा dc_pinmap *pmap = pinctrl_dev_get_drvdata(pctldev);

	*pins = &pmap->desc->pins[selector].number;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops dc_pinctrl_ops = अणु
	.get_groups_count	= dc_get_groups_count,
	.get_group_name		= dc_get_group_name,
	.get_group_pins		= dc_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

अटल स्थिर अक्षर *स्थिर dc_functions[] = अणु
	"gpio",
	"client_a",
	"client_b",
	"client_c",
पूर्ण;

अटल पूर्णांक dc_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(dc_functions);
पूर्ण

अटल स्थिर अक्षर *dc_get_fname(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector)
अणु
	वापस dc_functions[selector];
पूर्ण

अटल पूर्णांक dc_get_groups(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			 स्थिर अक्षर * स्थिर **groups,
			 अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा dc_pinmap *pmap = pinctrl_dev_get_drvdata(pctldev);

	*groups = pmap->pin_names;
	*num_groups = PINS_COUNT;

	वापस 0;
पूर्ण

अटल व्योम dc_client_sel(पूर्णांक pin_num, पूर्णांक *reg, पूर्णांक *bit)
अणु
	*bit = (pin_num % PINS_PER_COLLECTION) * 2;
	*reg = GP_CLIENTSEL(pin_num/PINS_PER_COLLECTION);

	अगर (*bit >= PINS_PER_COLLECTION) अणु
		*bit -= PINS_PER_COLLECTION;
		*reg += 1;
	पूर्ण
पूर्ण

अटल पूर्णांक dc_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
		      अचिन्हित group)
अणु
	काष्ठा dc_pinmap *pmap = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक bit_off, reg_off;
	u8 reg;

	dc_client_sel(group, &reg_off, &bit_off);

	reg = पढ़ोb_relaxed(pmap->regs + reg_off);
	reg &= ~(3 << bit_off);
	reg |= (selector << bit_off);
	ग_लिखोb_relaxed(reg, pmap->regs + reg_off);

	वापस 0;
पूर्ण

अटल पूर्णांक dc_pmx_request_gpio(काष्ठा pinctrl_dev *pcdev,
			       काष्ठा pinctrl_gpio_range *range,
			       अचिन्हित offset)
अणु
	काष्ठा dc_pinmap *pmap = pinctrl_dev_get_drvdata(pcdev);
	पूर्णांक bit_off, reg_off;
	u8 reg;

	dc_client_sel(offset, &reg_off, &bit_off);

	reg = पढ़ोb_relaxed(pmap->regs + reg_off);
	अगर ((reg & (3 << bit_off)) != 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops dc_pmxops = अणु
	.get_functions_count	= dc_get_functions_count,
	.get_function_name	= dc_get_fname,
	.get_function_groups	= dc_get_groups,
	.set_mux		= dc_set_mux,
	.gpio_request_enable	= dc_pmx_request_gpio,
पूर्ण;

अटल पूर्णांक dc_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा dc_pinmap *pmap = gpiochip_get_data(chip);
	पूर्णांक reg_off = GP_DRIVE0(gpio/PINS_PER_COLLECTION);
	पूर्णांक bit_off = gpio % PINS_PER_COLLECTION;
	u8 drive;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pmap->lock, flags);
	drive = पढ़ोb_relaxed(pmap->regs + reg_off);
	drive &= ~BIT(bit_off);
	ग_लिखोb_relaxed(drive, pmap->regs + reg_off);
	spin_unlock_irqrestore(&pmap->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम dc_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित gpio, पूर्णांक value);

अटल पूर्णांक dc_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित gpio,
				    पूर्णांक value)
अणु
	काष्ठा dc_pinmap *pmap = gpiochip_get_data(chip);
	पूर्णांक reg_off = GP_DRIVE0(gpio/PINS_PER_COLLECTION);
	पूर्णांक bit_off = gpio % PINS_PER_COLLECTION;
	u8 drive;
	अचिन्हित दीर्घ flags;

	dc_gpio_set(chip, gpio, value);

	spin_lock_irqsave(&pmap->lock, flags);
	drive = पढ़ोb_relaxed(pmap->regs + reg_off);
	drive |= BIT(bit_off);
	ग_लिखोb_relaxed(drive, pmap->regs + reg_off);
	spin_unlock_irqrestore(&pmap->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dc_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा dc_pinmap *pmap = gpiochip_get_data(chip);
	पूर्णांक reg_off = GP_INPUT(gpio/PINS_PER_COLLECTION);
	पूर्णांक bit_off = gpio % PINS_PER_COLLECTION;
	u8 input;

	input = पढ़ोb_relaxed(pmap->regs + reg_off);

	वापस !!(input & BIT(bit_off));
पूर्ण

अटल व्योम dc_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा dc_pinmap *pmap = gpiochip_get_data(chip);
	पूर्णांक reg_off = GP_OUTPUT0(gpio/PINS_PER_COLLECTION);
	पूर्णांक bit_off = gpio % PINS_PER_COLLECTION;
	u8 output;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pmap->lock, flags);
	output = पढ़ोb_relaxed(pmap->regs + reg_off);
	अगर (value)
		output |= BIT(bit_off);
	अन्यथा
		output &= ~BIT(bit_off);
	ग_लिखोb_relaxed(output, pmap->regs + reg_off);
	spin_unlock_irqrestore(&pmap->lock, flags);
पूर्ण

अटल पूर्णांक dc_gpiochip_add(काष्ठा dc_pinmap *pmap, काष्ठा device_node *np)
अणु
	काष्ठा gpio_chip *chip = &pmap->chip;
	पूर्णांक ret;

	chip->label		= DRIVER_NAME;
	chip->parent		= pmap->dev;
	chip->request		= gpiochip_generic_request;
	chip->मुक्त		= gpiochip_generic_मुक्त;
	chip->direction_input	= dc_gpio_direction_input;
	chip->direction_output	= dc_gpio_direction_output;
	chip->get		= dc_gpio_get;
	chip->set		= dc_gpio_set;
	chip->base		= -1;
	chip->ngpio		= PINS_COUNT;
	chip->of_node		= np;
	chip->of_gpio_n_cells	= 2;

	spin_lock_init(&pmap->lock);

	ret = gpiochip_add_data(chip, pmap);
	अगर (ret < 0)
		वापस ret;

	ret = gpiochip_add_pin_range(chip, dev_name(pmap->dev), 0, 0,
				     PINS_COUNT);
	अगर (ret < 0) अणु
		gpiochip_हटाओ(chip);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dc_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dc_pinmap *pmap;
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा pinctrl_desc *pctl_desc;
	अक्षर *pin_names;
	पूर्णांक name_len = म_माप("GP_xx") + 1;
	पूर्णांक i, j;

	pmap = devm_kzalloc(&pdev->dev, माप(*pmap), GFP_KERNEL);
	अगर (!pmap)
		वापस -ENOMEM;

	pmap->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pmap->regs))
		वापस PTR_ERR(pmap->regs);

	pins = devm_kसुस्मृति(&pdev->dev, PINS_COUNT, माप(*pins),
			    GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;
	pin_names = devm_kसुस्मृति(&pdev->dev, PINS_COUNT, name_len,
				 GFP_KERNEL);
	अगर (!pin_names)
		वापस -ENOMEM;

	क्रम (i = 0; i < PIN_COLLECTIONS; i++) अणु
		क्रम (j = 0; j < PINS_PER_COLLECTION; j++) अणु
			पूर्णांक pin_id = i*PINS_PER_COLLECTION + j;
			अक्षर *name = &pin_names[pin_id * name_len];

			snम_लिखो(name, name_len, "GP_%c%c", 'A'+i, '0'+j);

			pins[pin_id].number = pin_id;
			pins[pin_id].name = name;
			pmap->pin_names[pin_id] = name;
		पूर्ण
	पूर्ण

	pctl_desc = devm_kzalloc(&pdev->dev, माप(*pctl_desc), GFP_KERNEL);
	अगर (!pctl_desc)
		वापस -ENOMEM;

	pctl_desc->name	= DRIVER_NAME,
	pctl_desc->owner = THIS_MODULE,
	pctl_desc->pctlops = &dc_pinctrl_ops,
	pctl_desc->pmxops = &dc_pmxops,
	pctl_desc->npins = PINS_COUNT;
	pctl_desc->pins = pins;
	pmap->desc = pctl_desc;

	pmap->dev = &pdev->dev;

	pmap->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, pctl_desc, pmap);
	अगर (IS_ERR(pmap->pctl)) अणु
		dev_err(&pdev->dev, "pinctrl driver registration failed\n");
		वापस PTR_ERR(pmap->pctl);
	पूर्ण

	वापस dc_gpiochip_add(pmap, pdev->dev.of_node);
पूर्ण

अटल स्थिर काष्ठा of_device_id dc_pinctrl_ids[] = अणु
	अणु .compatible = "cnxt,cx92755-pinctrl" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver dc_pinctrl_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = dc_pinctrl_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = dc_pinctrl_probe,
पूर्ण;
builtin_platक्रमm_driver(dc_pinctrl_driver);
