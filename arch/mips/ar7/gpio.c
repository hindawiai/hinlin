<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2007 Eugene Konev <ejka@खोलोwrt.org>
 * Copyright (C) 2009-2010 Florian Fainelli <florian@खोलोwrt.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/gpपन.स>

#समावेश <यंत्र/mach-ar7/ar7.h>

#घोषणा AR7_GPIO_MAX 32
#घोषणा TITAN_GPIO_MAX 51

काष्ठा ar7_gpio_chip अणु
	व्योम __iomem		*regs;
	काष्ठा gpio_chip	chip;
पूर्ण;

अटल पूर्णांक ar7_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा ar7_gpio_chip *gpch = gpiochip_get_data(chip);
	व्योम __iomem *gpio_in = gpch->regs + AR7_GPIO_INPUT;

	वापस !!(पढ़ोl(gpio_in) & (1 << gpio));
पूर्ण

अटल पूर्णांक titan_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा ar7_gpio_chip *gpch = gpiochip_get_data(chip);
	व्योम __iomem *gpio_in0 = gpch->regs + TITAN_GPIO_INPUT_0;
	व्योम __iomem *gpio_in1 = gpch->regs + TITAN_GPIO_INPUT_1;

	वापस पढ़ोl(gpio >> 5 ? gpio_in1 : gpio_in0) & (1 << (gpio & 0x1f));
पूर्ण

अटल व्योम ar7_gpio_set_value(काष्ठा gpio_chip *chip,
				अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा ar7_gpio_chip *gpch = gpiochip_get_data(chip);
	व्योम __iomem *gpio_out = gpch->regs + AR7_GPIO_OUTPUT;
	अचिन्हित पंचांगp;

	पंचांगp = पढ़ोl(gpio_out) & ~(1 << gpio);
	अगर (value)
		पंचांगp |= 1 << gpio;
	ग_लिखोl(पंचांगp, gpio_out);
पूर्ण

अटल व्योम titan_gpio_set_value(काष्ठा gpio_chip *chip,
				अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा ar7_gpio_chip *gpch = gpiochip_get_data(chip);
	व्योम __iomem *gpio_out0 = gpch->regs + TITAN_GPIO_OUTPUT_0;
	व्योम __iomem *gpio_out1 = gpch->regs + TITAN_GPIO_OUTPUT_1;
	अचिन्हित पंचांगp;

	पंचांगp = पढ़ोl(gpio >> 5 ? gpio_out1 : gpio_out0) & ~(1 << (gpio & 0x1f));
	अगर (value)
		पंचांगp |= 1 << (gpio & 0x1f);
	ग_लिखोl(पंचांगp, gpio >> 5 ? gpio_out1 : gpio_out0);
पूर्ण

अटल पूर्णांक ar7_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा ar7_gpio_chip *gpch = gpiochip_get_data(chip);
	व्योम __iomem *gpio_dir = gpch->regs + AR7_GPIO_सूची;

	ग_लिखोl(पढ़ोl(gpio_dir) | (1 << gpio), gpio_dir);

	वापस 0;
पूर्ण

अटल पूर्णांक titan_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा ar7_gpio_chip *gpch = gpiochip_get_data(chip);
	व्योम __iomem *gpio_dir0 = gpch->regs + TITAN_GPIO_सूची_0;
	व्योम __iomem *gpio_dir1 = gpch->regs + TITAN_GPIO_सूची_1;

	अगर (gpio >= TITAN_GPIO_MAX)
		वापस -EINVAL;

	ग_लिखोl(पढ़ोl(gpio >> 5 ? gpio_dir1 : gpio_dir0) | (1 << (gpio & 0x1f)),
			gpio >> 5 ? gpio_dir1 : gpio_dir0);
	वापस 0;
पूर्ण

अटल पूर्णांक ar7_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा ar7_gpio_chip *gpch = gpiochip_get_data(chip);
	व्योम __iomem *gpio_dir = gpch->regs + AR7_GPIO_सूची;

	ar7_gpio_set_value(chip, gpio, value);
	ग_लिखोl(पढ़ोl(gpio_dir) & ~(1 << gpio), gpio_dir);

	वापस 0;
पूर्ण

अटल पूर्णांक titan_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा ar7_gpio_chip *gpch = gpiochip_get_data(chip);
	व्योम __iomem *gpio_dir0 = gpch->regs + TITAN_GPIO_सूची_0;
	व्योम __iomem *gpio_dir1 = gpch->regs + TITAN_GPIO_सूची_1;

	अगर (gpio >= TITAN_GPIO_MAX)
		वापस -EINVAL;

	titan_gpio_set_value(chip, gpio, value);
	ग_लिखोl(पढ़ोl(gpio >> 5 ? gpio_dir1 : gpio_dir0) & ~(1 <<
		(gpio & 0x1f)), gpio >> 5 ? gpio_dir1 : gpio_dir0);

	वापस 0;
पूर्ण

अटल काष्ठा ar7_gpio_chip ar7_gpio_chip = अणु
	.chip = अणु
		.label			= "ar7-gpio",
		.direction_input	= ar7_gpio_direction_input,
		.direction_output	= ar7_gpio_direction_output,
		.set			= ar7_gpio_set_value,
		.get			= ar7_gpio_get_value,
		.base			= 0,
		.ngpio			= AR7_GPIO_MAX,
	पूर्ण
पूर्ण;

अटल काष्ठा ar7_gpio_chip titan_gpio_chip = अणु
	.chip = अणु
		.label			= "titan-gpio",
		.direction_input	= titan_gpio_direction_input,
		.direction_output	= titan_gpio_direction_output,
		.set			= titan_gpio_set_value,
		.get			= titan_gpio_get_value,
		.base			= 0,
		.ngpio			= TITAN_GPIO_MAX,
	पूर्ण
पूर्ण;

अटल अंतरभूत पूर्णांक ar7_gpio_enable_ar7(अचिन्हित gpio)
अणु
	व्योम __iomem *gpio_en = ar7_gpio_chip.regs + AR7_GPIO_ENABLE;

	ग_लिखोl(पढ़ोl(gpio_en) | (1 << gpio), gpio_en);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ar7_gpio_enable_titan(अचिन्हित gpio)
अणु
	व्योम __iomem *gpio_en0 = titan_gpio_chip.regs  + TITAN_GPIO_ENBL_0;
	व्योम __iomem *gpio_en1 = titan_gpio_chip.regs  + TITAN_GPIO_ENBL_1;

	ग_लिखोl(पढ़ोl(gpio >> 5 ? gpio_en1 : gpio_en0) | (1 << (gpio & 0x1f)),
		gpio >> 5 ? gpio_en1 : gpio_en0);

	वापस 0;
पूर्ण

पूर्णांक ar7_gpio_enable(अचिन्हित gpio)
अणु
	वापस ar7_is_titan() ? ar7_gpio_enable_titan(gpio) :
				ar7_gpio_enable_ar7(gpio);
पूर्ण
EXPORT_SYMBOL(ar7_gpio_enable);

अटल अंतरभूत पूर्णांक ar7_gpio_disable_ar7(अचिन्हित gpio)
अणु
	व्योम __iomem *gpio_en = ar7_gpio_chip.regs + AR7_GPIO_ENABLE;

	ग_लिखोl(पढ़ोl(gpio_en) & ~(1 << gpio), gpio_en);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ar7_gpio_disable_titan(अचिन्हित gpio)
अणु
	व्योम __iomem *gpio_en0 = titan_gpio_chip.regs + TITAN_GPIO_ENBL_0;
	व्योम __iomem *gpio_en1 = titan_gpio_chip.regs + TITAN_GPIO_ENBL_1;

	ग_लिखोl(पढ़ोl(gpio >> 5 ? gpio_en1 : gpio_en0) & ~(1 << (gpio & 0x1f)),
			gpio >> 5 ? gpio_en1 : gpio_en0);

	वापस 0;
पूर्ण

पूर्णांक ar7_gpio_disable(अचिन्हित gpio)
अणु
	वापस ar7_is_titan() ? ar7_gpio_disable_titan(gpio) :
				ar7_gpio_disable_ar7(gpio);
पूर्ण
EXPORT_SYMBOL(ar7_gpio_disable);

काष्ठा titan_gpio_cfg अणु
	u32 reg;
	u32 shअगरt;
	u32 func;
पूर्ण;

अटल स्थिर काष्ठा titan_gpio_cfg titan_gpio_table[] = अणु
	/* reg, start bit, mux value */
	अणु4, 24, 1पूर्ण,
	अणु4, 26, 1पूर्ण,
	अणु4, 28, 1पूर्ण,
	अणु4, 30, 1पूर्ण,
	अणु5, 6, 1पूर्ण,
	अणु5, 8, 1पूर्ण,
	अणु5, 10, 1पूर्ण,
	अणु5, 12, 1पूर्ण,
	अणु7, 14, 3पूर्ण,
	अणु7, 16, 3पूर्ण,
	अणु7, 18, 3पूर्ण,
	अणु7, 20, 3पूर्ण,
	अणु7, 22, 3पूर्ण,
	अणु7, 26, 3पूर्ण,
	अणु7, 28, 3पूर्ण,
	अणु7, 30, 3पूर्ण,
	अणु8, 0, 3पूर्ण,
	अणु8, 2, 3पूर्ण,
	अणु8, 4, 3पूर्ण,
	अणु8, 10, 3पूर्ण,
	अणु8, 14, 3पूर्ण,
	अणु8, 16, 3पूर्ण,
	अणु8, 18, 3पूर्ण,
	अणु8, 20, 3पूर्ण,
	अणु9, 8, 3पूर्ण,
	अणु9, 10, 3पूर्ण,
	अणु9, 12, 3पूर्ण,
	अणु9, 14, 3पूर्ण,
	अणु9, 18, 3पूर्ण,
	अणु9, 20, 3पूर्ण,
	अणु9, 24, 3पूर्ण,
	अणु9, 26, 3पूर्ण,
	अणु9, 28, 3पूर्ण,
	अणु9, 30, 3पूर्ण,
	अणु10, 0, 3पूर्ण,
	अणु10, 2, 3पूर्ण,
	अणु10, 8, 3पूर्ण,
	अणु10, 10, 3पूर्ण,
	अणु10, 12, 3पूर्ण,
	अणु10, 14, 3पूर्ण,
	अणु13, 12, 3पूर्ण,
	अणु13, 14, 3पूर्ण,
	अणु13, 16, 3पूर्ण,
	अणु13, 18, 3पूर्ण,
	अणु13, 24, 3पूर्ण,
	अणु13, 26, 3पूर्ण,
	अणु13, 28, 3पूर्ण,
	अणु13, 30, 3पूर्ण,
	अणु14, 2, 3पूर्ण,
	अणु14, 6, 3पूर्ण,
	अणु14, 8, 3पूर्ण,
	अणु14, 12, 3पूर्ण
पूर्ण;

अटल पूर्णांक titan_gpio_pinsel(अचिन्हित gpio)
अणु
	काष्ठा titan_gpio_cfg gpio_cfg;
	u32 mux_status, pin_sel_reg, पंचांगp;
	व्योम __iomem *pin_sel = (व्योम __iomem *)KSEG1ADDR(AR7_REGS_PINSEL);

	अगर (gpio >= ARRAY_SIZE(titan_gpio_table))
		वापस -EINVAL;

	gpio_cfg = titan_gpio_table[gpio];
	pin_sel_reg = gpio_cfg.reg - 1;

	mux_status = (पढ़ोl(pin_sel + pin_sel_reg) >> gpio_cfg.shअगरt) & 0x3;

	/* Check the mux status */
	अगर (!((mux_status == 0) || (mux_status == gpio_cfg.func)))
		वापस 0;

	/* Set the pin sel value */
	पंचांगp = पढ़ोl(pin_sel + pin_sel_reg);
	पंचांगp |= ((gpio_cfg.func & 0x3) << gpio_cfg.shअगरt);
	ग_लिखोl(पंचांगp, pin_sel + pin_sel_reg);

	वापस 0;
पूर्ण

/* Perक्रमm minimal Titan GPIO configuration */
अटल व्योम titan_gpio_init(व्योम)
अणु
	अचिन्हित i;

	क्रम (i = 44; i < 48; i++) अणु
		titan_gpio_pinsel(i);
		ar7_gpio_enable_titan(i);
		titan_gpio_direction_input(&titan_gpio_chip.chip, i);
	पूर्ण
पूर्ण

पूर्णांक __init ar7_gpio_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा ar7_gpio_chip *gpch;
	अचिन्हित size;

	अगर (!ar7_is_titan()) अणु
		gpch = &ar7_gpio_chip;
		size = 0x10;
	पूर्ण अन्यथा अणु
		gpch = &titan_gpio_chip;
		size = 0x1f;
	पूर्ण

	gpch->regs = ioremap(AR7_REGS_GPIO, size);
	अगर (!gpch->regs) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to ioremap regs\n",
					gpch->chip.label);
		वापस -ENOMEM;
	पूर्ण

	ret = gpiochip_add_data(&gpch->chip, gpch);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to add gpiochip\n",
					gpch->chip.label);
		iounmap(gpch->regs);
		वापस ret;
	पूर्ण
	prपूर्णांकk(KERN_INFO "%s: registered %d GPIOs\n",
				gpch->chip.label, gpch->chip.ngpio);

	अगर (ar7_is_titan())
		titan_gpio_init();

	वापस ret;
पूर्ण
