<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH Pin Function Controller GPIO driver.
 *
 * Copyright (C) 2008 Magnus Damm
 * Copyright (C) 2009 - 2012 Paul Mundt
 */

#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "core.h"

काष्ठा sh_pfc_gpio_data_reg अणु
	स्थिर काष्ठा pinmux_data_reg *info;
	u32 shaकरोw;
पूर्ण;

काष्ठा sh_pfc_gpio_pin अणु
	u8 dbit;
	u8 dreg;
पूर्ण;

काष्ठा sh_pfc_chip अणु
	काष्ठा sh_pfc			*pfc;
	काष्ठा gpio_chip		gpio_chip;

	काष्ठा sh_pfc_winकरोw		*mem;
	काष्ठा sh_pfc_gpio_data_reg	*regs;
	काष्ठा sh_pfc_gpio_pin		*pins;
पूर्ण;

अटल काष्ठा sh_pfc *gpio_to_pfc(काष्ठा gpio_chip *gc)
अणु
	काष्ठा sh_pfc_chip *chip = gpiochip_get_data(gc);
	वापस chip->pfc;
पूर्ण

अटल व्योम gpio_get_data_reg(काष्ठा sh_pfc_chip *chip, अचिन्हित पूर्णांक offset,
			      काष्ठा sh_pfc_gpio_data_reg **reg,
			      अचिन्हित पूर्णांक *bit)
अणु
	पूर्णांक idx = sh_pfc_get_pin_index(chip->pfc, offset);
	काष्ठा sh_pfc_gpio_pin *gpio_pin = &chip->pins[idx];

	*reg = &chip->regs[gpio_pin->dreg];
	*bit = gpio_pin->dbit;
पूर्ण

अटल u32 gpio_पढ़ो_data_reg(काष्ठा sh_pfc_chip *chip,
			      स्थिर काष्ठा pinmux_data_reg *dreg)
अणु
	phys_addr_t address = dreg->reg;
	व्योम __iomem *mem = address - chip->mem->phys + chip->mem->virt;

	वापस sh_pfc_पढ़ो_raw_reg(mem, dreg->reg_width);
पूर्ण

अटल व्योम gpio_ग_लिखो_data_reg(काष्ठा sh_pfc_chip *chip,
				स्थिर काष्ठा pinmux_data_reg *dreg, u32 value)
अणु
	phys_addr_t address = dreg->reg;
	व्योम __iomem *mem = address - chip->mem->phys + chip->mem->virt;

	sh_pfc_ग_लिखो_raw_reg(mem, dreg->reg_width, value);
पूर्ण

अटल व्योम gpio_setup_data_reg(काष्ठा sh_pfc_chip *chip, अचिन्हित idx)
अणु
	काष्ठा sh_pfc *pfc = chip->pfc;
	काष्ठा sh_pfc_gpio_pin *gpio_pin = &chip->pins[idx];
	स्थिर काष्ठा sh_pfc_pin *pin = &pfc->info->pins[idx];
	स्थिर काष्ठा pinmux_data_reg *dreg;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0, dreg = pfc->info->data_regs; dreg->reg_width; ++i, ++dreg) अणु
		क्रम (bit = 0; bit < dreg->reg_width; bit++) अणु
			अगर (dreg->क्रमागत_ids[bit] == pin->क्रमागत_id) अणु
				gpio_pin->dreg = i;
				gpio_pin->dbit = bit;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	BUG();
पूर्ण

अटल पूर्णांक gpio_setup_data_regs(काष्ठा sh_pfc_chip *chip)
अणु
	काष्ठा sh_pfc *pfc = chip->pfc;
	स्थिर काष्ठा pinmux_data_reg *dreg;
	अचिन्हित पूर्णांक i;

	/* Count the number of data रेजिस्टरs, allocate memory and initialize
	 * them.
	 */
	क्रम (i = 0; pfc->info->data_regs[i].reg_width; ++i)
		;

	chip->regs = devm_kसुस्मृति(pfc->dev, i, माप(*chip->regs),
				  GFP_KERNEL);
	अगर (chip->regs == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0, dreg = pfc->info->data_regs; dreg->reg_width; ++i, ++dreg) अणु
		chip->regs[i].info = dreg;
		chip->regs[i].shaकरोw = gpio_पढ़ो_data_reg(chip, dreg);
	पूर्ण

	क्रम (i = 0; i < pfc->info->nr_pins; i++) अणु
		अगर (pfc->info->pins[i].क्रमागत_id == 0)
			जारी;

		gpio_setup_data_reg(chip, i);
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Pin GPIOs
 */

अटल पूर्णांक gpio_pin_request(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा sh_pfc *pfc = gpio_to_pfc(gc);
	पूर्णांक idx = sh_pfc_get_pin_index(pfc, offset);

	अगर (idx < 0 || pfc->info->pins[idx].क्रमागत_id == 0)
		वापस -EINVAL;

	वापस pinctrl_gpio_request(offset);
पूर्ण

अटल व्योम gpio_pin_मुक्त(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	वापस pinctrl_gpio_मुक्त(offset);
पूर्ण

अटल व्योम gpio_pin_set_value(काष्ठा sh_pfc_chip *chip, अचिन्हित offset,
			       पूर्णांक value)
अणु
	काष्ठा sh_pfc_gpio_data_reg *reg;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक pos;

	gpio_get_data_reg(chip, offset, &reg, &bit);

	pos = reg->info->reg_width - (bit + 1);

	अगर (value)
		reg->shaकरोw |= BIT(pos);
	अन्यथा
		reg->shaकरोw &= ~BIT(pos);

	gpio_ग_लिखो_data_reg(chip, reg->info, reg->shaकरोw);
पूर्ण

अटल पूर्णांक gpio_pin_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	वापस pinctrl_gpio_direction_input(offset);
पूर्ण

अटल पूर्णांक gpio_pin_direction_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
				    पूर्णांक value)
अणु
	gpio_pin_set_value(gpiochip_get_data(gc), offset, value);

	वापस pinctrl_gpio_direction_output(offset);
पूर्ण

अटल पूर्णांक gpio_pin_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा sh_pfc_chip *chip = gpiochip_get_data(gc);
	काष्ठा sh_pfc_gpio_data_reg *reg;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक pos;

	gpio_get_data_reg(chip, offset, &reg, &bit);

	pos = reg->info->reg_width - (bit + 1);

	वापस (gpio_पढ़ो_data_reg(chip, reg->info) >> pos) & 1;
पूर्ण

अटल व्योम gpio_pin_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	gpio_pin_set_value(gpiochip_get_data(gc), offset, value);
पूर्ण

अटल पूर्णांक gpio_pin_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा sh_pfc *pfc = gpio_to_pfc(gc);
	अचिन्हित पूर्णांक i, k;

	क्रम (i = 0; i < pfc->info->gpio_irq_size; i++) अणु
		स्थिर लघु *gpios = pfc->info->gpio_irq[i].gpios;

		क्रम (k = 0; gpios[k] >= 0; k++) अणु
			अगर (gpios[k] == offset)
				वापस pfc->irqs[i];
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_pin_setup(काष्ठा sh_pfc_chip *chip)
अणु
	काष्ठा sh_pfc *pfc = chip->pfc;
	काष्ठा gpio_chip *gc = &chip->gpio_chip;
	पूर्णांक ret;

	chip->pins = devm_kसुस्मृति(pfc->dev,
				  pfc->info->nr_pins, माप(*chip->pins),
				  GFP_KERNEL);
	अगर (chip->pins == शून्य)
		वापस -ENOMEM;

	ret = gpio_setup_data_regs(chip);
	अगर (ret < 0)
		वापस ret;

	gc->request = gpio_pin_request;
	gc->मुक्त = gpio_pin_मुक्त;
	gc->direction_input = gpio_pin_direction_input;
	gc->get = gpio_pin_get;
	gc->direction_output = gpio_pin_direction_output;
	gc->set = gpio_pin_set;
	gc->to_irq = gpio_pin_to_irq;

	gc->label = pfc->info->name;
	gc->parent = pfc->dev;
	gc->owner = THIS_MODULE;
	gc->base = 0;
	gc->ngpio = pfc->nr_gpio_pins;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Function GPIOs
 */

#अगर_घोषित CONFIG_PINCTRL_SH_FUNC_GPIO
अटल पूर्णांक gpio_function_request(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा sh_pfc *pfc = gpio_to_pfc(gc);
	अचिन्हित पूर्णांक mark = pfc->info->func_gpios[offset].क्रमागत_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	dev_notice_once(pfc->dev,
			"Use of GPIO API for function requests is deprecated, convert to pinctrl\n");

	अगर (mark == 0)
		वापस -EINVAL;

	spin_lock_irqsave(&pfc->lock, flags);
	ret = sh_pfc_config_mux(pfc, mark, PINMUX_TYPE_FUNCTION);
	spin_unlock_irqrestore(&pfc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक gpio_function_setup(काष्ठा sh_pfc_chip *chip)
अणु
	काष्ठा sh_pfc *pfc = chip->pfc;
	काष्ठा gpio_chip *gc = &chip->gpio_chip;

	gc->request = gpio_function_request;

	gc->label = pfc->info->name;
	gc->owner = THIS_MODULE;
	gc->base = pfc->nr_gpio_pins;
	gc->ngpio = pfc->info->nr_func_gpios;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PINCTRL_SH_FUNC_GPIO */

/* -----------------------------------------------------------------------------
 * Register/unरेजिस्टर
 */

अटल काष्ठा sh_pfc_chip *
sh_pfc_add_gpiochip(काष्ठा sh_pfc *pfc, पूर्णांक(*setup)(काष्ठा sh_pfc_chip *),
		    काष्ठा sh_pfc_winकरोw *mem)
अणु
	काष्ठा sh_pfc_chip *chip;
	पूर्णांक ret;

	chip = devm_kzalloc(pfc->dev, माप(*chip), GFP_KERNEL);
	अगर (unlikely(!chip))
		वापस ERR_PTR(-ENOMEM);

	chip->mem = mem;
	chip->pfc = pfc;

	ret = setup(chip);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	ret = devm_gpiochip_add_data(pfc->dev, &chip->gpio_chip, chip);
	अगर (unlikely(ret < 0))
		वापस ERR_PTR(ret);

	dev_info(pfc->dev, "%s handling gpio %u -> %u\n",
		 chip->gpio_chip.label, chip->gpio_chip.base,
		 chip->gpio_chip.base + chip->gpio_chip.ngpio - 1);

	वापस chip;
पूर्ण

पूर्णांक sh_pfc_रेजिस्टर_gpiochip(काष्ठा sh_pfc *pfc)
अणु
	काष्ठा sh_pfc_chip *chip;
	phys_addr_t address;
	अचिन्हित पूर्णांक i;

	अगर (pfc->info->data_regs == शून्य)
		वापस 0;

	/* Find the memory winकरोw that contains the GPIO रेजिस्टरs. Boards that
	 * रेजिस्टर a separate GPIO device will not supply a memory resource
	 * that covers the data रेजिस्टरs. In that हाल करोn't try to handle
	 * GPIOs.
	 */
	address = pfc->info->data_regs[0].reg;
	क्रम (i = 0; i < pfc->num_winकरोws; ++i) अणु
		काष्ठा sh_pfc_winकरोw *winकरोw = &pfc->winकरोws[i];

		अगर (address >= winकरोw->phys &&
		    address < winकरोw->phys + winकरोw->size)
			अवरोध;
	पूर्ण

	अगर (i == pfc->num_winकरोws)
		वापस 0;

	/* If we have IRQ resources make sure their number is correct. */
	अगर (pfc->num_irqs != pfc->info->gpio_irq_size) अणु
		dev_err(pfc->dev, "invalid number of IRQ resources\n");
		वापस -EINVAL;
	पूर्ण

	/* Register the real GPIOs chip. */
	chip = sh_pfc_add_gpiochip(pfc, gpio_pin_setup, &pfc->winकरोws[i]);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	pfc->gpio = chip;

	अगर (IS_ENABLED(CONFIG_OF) && pfc->dev->of_node)
		वापस 0;

#अगर_घोषित CONFIG_PINCTRL_SH_FUNC_GPIO
	/*
	 * Register the GPIO to pin mappings. As pins with GPIO ports
	 * must come first in the ranges, skip the pins without GPIO
	 * ports by stopping at the first range that contains such a
	 * pin.
	 */
	क्रम (i = 0; i < pfc->nr_ranges; ++i) अणु
		स्थिर काष्ठा sh_pfc_pin_range *range = &pfc->ranges[i];
		पूर्णांक ret;

		अगर (range->start >= pfc->nr_gpio_pins)
			अवरोध;

		ret = gpiochip_add_pin_range(&chip->gpio_chip,
			dev_name(pfc->dev), range->start, range->start,
			range->end - range->start + 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Register the function GPIOs chip. */
	अगर (pfc->info->nr_func_gpios) अणु
		chip = sh_pfc_add_gpiochip(pfc, gpio_function_setup, शून्य);
		अगर (IS_ERR(chip))
			वापस PTR_ERR(chip);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PINCTRL_SH_FUNC_GPIO */

	वापस 0;
पूर्ण
