<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  GPIO पूर्णांकerface क्रम IT87xx Super I/O chips
 *
 *  Author: Diego Elio Pettenथऑ <flameeyes@flameeyes.eu>
 *  Copyright (c) 2017 Google, Inc.
 *
 *  Based on it87_wdt.c     by Oliver Schuster
 *           gpio-it8761e.c by Denis Turischev
 *           gpio-sपंचांगpe.c   by Rabin Vincent
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>

/* Chip Id numbers */
#घोषणा NO_DEV_ID	0xffff
#घोषणा IT8613_ID	0x8613
#घोषणा IT8620_ID	0x8620
#घोषणा IT8628_ID	0x8628
#घोषणा IT8718_ID       0x8718
#घोषणा IT8728_ID	0x8728
#घोषणा IT8732_ID	0x8732
#घोषणा IT8761_ID	0x8761
#घोषणा IT8772_ID	0x8772
#घोषणा IT8786_ID	0x8786

/* IO Ports */
#घोषणा REG		0x2e
#घोषणा VAL		0x2f

/* Logical device Numbers LDN */
#घोषणा GPIO		0x07

/* Configuration Registers and Functions */
#घोषणा LDNREG		0x07
#घोषणा CHIPID		0x20
#घोषणा CHIPREV		0x22

/**
 * काष्ठा it87_gpio - it87-specअगरic GPIO chip
 * @chip: the underlying gpio_chip काष्ठाure
 * @lock: a lock to aव्योम races between operations
 * @io_base: base address क्रम gpio ports
 * @io_size: size of the port rage starting from io_base.
 * @output_base: Super I/O रेजिस्टर address क्रम Output Enable रेजिस्टर
 * @simple_base: Super I/O 'Simple I/O' Enable रेजिस्टर
 * @simple_size: Super IO 'Simple I/O' Enable रेजिस्टर size; this is
 *	required because IT87xx chips might only provide Simple I/O
 *	चयनes on a subset of lines, whereas the others keep the
 *	same status all समय.
 */
काष्ठा it87_gpio अणु
	काष्ठा gpio_chip chip;
	spinlock_t lock;
	u16 io_base;
	u16 io_size;
	u8 output_base;
	u8 simple_base;
	u8 simple_size;
पूर्ण;

अटल काष्ठा it87_gpio it87_gpio_chip = अणु
	.lock = __SPIN_LOCK_UNLOCKED(it87_gpio_chip.lock),
पूर्ण;

/* Superio chip access functions; copied from wdt_it87 */

अटल अंतरभूत पूर्णांक superio_enter(व्योम)
अणु
	/*
	 * Try to reserve REG and REG + 1 क्रम exclusive access.
	 */
	अगर (!request_muxed_region(REG, 2, KBUILD_MODNAME))
		वापस -EBUSY;

	outb(0x87, REG);
	outb(0x01, REG);
	outb(0x55, REG);
	outb(0x55, REG);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम superio_निकास(व्योम)
अणु
	outb(0x02, REG);
	outb(0x02, VAL);
	release_region(REG, 2);
पूर्ण

अटल अंतरभूत व्योम superio_select(पूर्णांक ldn)
अणु
	outb(LDNREG, REG);
	outb(ldn, VAL);
पूर्ण

अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक reg)
अणु
	outb(reg, REG);
	वापस inb(VAL);
पूर्ण

अटल अंतरभूत व्योम superio_outb(पूर्णांक val, पूर्णांक reg)
अणु
	outb(reg, REG);
	outb(val, VAL);
पूर्ण

अटल अंतरभूत पूर्णांक superio_inw(पूर्णांक reg)
अणु
	पूर्णांक val;

	outb(reg++, REG);
	val = inb(VAL) << 8;
	outb(reg, REG);
	val |= inb(VAL);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम superio_set_mask(पूर्णांक mask, पूर्णांक reg)
अणु
	u8 curr_val = superio_inb(reg);
	u8 new_val = curr_val | mask;

	अगर (curr_val != new_val)
		superio_outb(new_val, reg);
पूर्ण

अटल अंतरभूत व्योम superio_clear_mask(पूर्णांक mask, पूर्णांक reg)
अणु
	u8 curr_val = superio_inb(reg);
	u8 new_val = curr_val & ~mask;

	अगर (curr_val != new_val)
		superio_outb(new_val, reg);
पूर्ण

अटल पूर्णांक it87_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित gpio_num)
अणु
	u8 mask, group;
	पूर्णांक rc = 0;
	काष्ठा it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	group = (gpio_num / 8);

	spin_lock(&it87_gpio->lock);

	rc = superio_enter();
	अगर (rc)
		जाओ निकास;

	/* not all the IT87xx chips support Simple I/O and not all of
	 * them allow all the lines to be set/unset to Simple I/O.
	 */
	अगर (group < it87_gpio->simple_size)
		superio_set_mask(mask, group + it87_gpio->simple_base);

	/* clear output enable, setting the pin to input, as all the
	 * newly-exported GPIO पूर्णांकerfaces are set to input.
	 */
	superio_clear_mask(mask, group + it87_gpio->output_base);

	superio_निकास();

निकास:
	spin_unlock(&it87_gpio->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक it87_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित gpio_num)
अणु
	u16 reg;
	u8 mask;
	काष्ठा it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	reg = (gpio_num / 8) + it87_gpio->io_base;

	वापस !!(inb(reg) & mask);
पूर्ण

अटल पूर्णांक it87_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित gpio_num)
अणु
	u8 mask, group;
	पूर्णांक rc = 0;
	काष्ठा it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	group = (gpio_num / 8);

	spin_lock(&it87_gpio->lock);

	rc = superio_enter();
	अगर (rc)
		जाओ निकास;

	/* clear the output enable bit */
	superio_clear_mask(mask, group + it87_gpio->output_base);

	superio_निकास();

निकास:
	spin_unlock(&it87_gpio->lock);
	वापस rc;
पूर्ण

अटल व्योम it87_gpio_set(काष्ठा gpio_chip *chip,
			  अचिन्हित gpio_num, पूर्णांक val)
अणु
	u8 mask, curr_vals;
	u16 reg;
	काष्ठा it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	reg = (gpio_num / 8) + it87_gpio->io_base;

	curr_vals = inb(reg);
	अगर (val)
		outb(curr_vals | mask, reg);
	अन्यथा
		outb(curr_vals & ~mask, reg);
पूर्ण

अटल पूर्णांक it87_gpio_direction_out(काष्ठा gpio_chip *chip,
				   अचिन्हित gpio_num, पूर्णांक val)
अणु
	u8 mask, group;
	पूर्णांक rc = 0;
	काष्ठा it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	group = (gpio_num / 8);

	spin_lock(&it87_gpio->lock);

	rc = superio_enter();
	अगर (rc)
		जाओ निकास;

	/* set the output enable bit */
	superio_set_mask(mask, group + it87_gpio->output_base);

	it87_gpio_set(chip, gpio_num, val);

	superio_निकास();

निकास:
	spin_unlock(&it87_gpio->lock);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा gpio_chip it87_ढाँचा_chip = अणु
	.label			= KBUILD_MODNAME,
	.owner			= THIS_MODULE,
	.request		= it87_gpio_request,
	.get			= it87_gpio_get,
	.direction_input	= it87_gpio_direction_in,
	.set			= it87_gpio_set,
	.direction_output	= it87_gpio_direction_out,
	.base			= -1
पूर्ण;

अटल पूर्णांक __init it87_gpio_init(व्योम)
अणु
	पूर्णांक rc = 0, i;
	u16 chip_type;
	u8 chip_rev, gpio_ba_reg;
	अक्षर *labels, **labels_table;

	काष्ठा it87_gpio *it87_gpio = &it87_gpio_chip;

	rc = superio_enter();
	अगर (rc)
		वापस rc;

	chip_type = superio_inw(CHIPID);
	chip_rev  = superio_inb(CHIPREV) & 0x0f;
	superio_निकास();

	it87_gpio->chip = it87_ढाँचा_chip;

	चयन (chip_type) अणु
	हाल IT8613_ID:
		gpio_ba_reg = 0x62;
		it87_gpio->io_size = 8;  /* it8613 only needs 6, use 8 क्रम alignment */
		it87_gpio->output_base = 0xc8;
		it87_gpio->simple_base = 0xc0;
		it87_gpio->simple_size = 6;
		it87_gpio->chip.ngpio = 64;  /* has 48, use 64 क्रम convenient calc */
		अवरोध;
	हाल IT8620_ID:
	हाल IT8628_ID:
		gpio_ba_reg = 0x62;
		it87_gpio->io_size = 11;
		it87_gpio->output_base = 0xc8;
		it87_gpio->simple_size = 0;
		it87_gpio->chip.ngpio = 64;
		अवरोध;
	हाल IT8718_ID:
	हाल IT8728_ID:
	हाल IT8732_ID:
	हाल IT8772_ID:
	हाल IT8786_ID:
		gpio_ba_reg = 0x62;
		it87_gpio->io_size = 8;
		it87_gpio->output_base = 0xc8;
		it87_gpio->simple_base = 0xc0;
		it87_gpio->simple_size = 5;
		it87_gpio->chip.ngpio = 64;
		अवरोध;
	हाल IT8761_ID:
		gpio_ba_reg = 0x60;
		it87_gpio->io_size = 4;
		it87_gpio->output_base = 0xf0;
		it87_gpio->simple_size = 0;
		it87_gpio->chip.ngpio = 16;
		अवरोध;
	हाल NO_DEV_ID:
		pr_err("no device\n");
		वापस -ENODEV;
	शेष:
		pr_err("Unknown Chip found, Chip %04x Revision %x\n",
		       chip_type, chip_rev);
		वापस -ENODEV;
	पूर्ण

	rc = superio_enter();
	अगर (rc)
		वापस rc;

	superio_select(GPIO);

	/* fetch GPIO base address */
	it87_gpio->io_base = superio_inw(gpio_ba_reg);

	superio_निकास();

	pr_info("Found Chip IT%04x rev %x. %u GPIO lines starting at %04xh\n",
		chip_type, chip_rev, it87_gpio->chip.ngpio,
		it87_gpio->io_base);

	अगर (!request_region(it87_gpio->io_base, it87_gpio->io_size,
							KBUILD_MODNAME))
		वापस -EBUSY;

	/* Set up aliases क्रम the GPIO connection.
	 *
	 * ITE करोcumentation क्रम recent chips such as the IT8728F
	 * refers to the GPIO lines as GPxy, with a coordinates प्रणाली
	 * where x is the GPIO group (starting from 1) and y is the
	 * bit within the group.
	 *
	 * By creating these aliases, we make it easier to understand
	 * to which GPIO pin we're referring to.
	 */
	labels = kसुस्मृति(it87_gpio->chip.ngpio, माप("it87_gpXY"),
								GFP_KERNEL);
	labels_table = kसुस्मृति(it87_gpio->chip.ngpio, माप(स्थिर अक्षर *),
								GFP_KERNEL);

	अगर (!labels || !labels_table) अणु
		rc = -ENOMEM;
		जाओ labels_मुक्त;
	पूर्ण

	क्रम (i = 0; i < it87_gpio->chip.ngpio; i++) अणु
		अक्षर *label = &labels[i * माप("it87_gpXY")];

		प्र_लिखो(label, "it87_gp%u%u", 1+(i/8), i%8);
		labels_table[i] = label;
	पूर्ण

	it87_gpio->chip.names = (स्थिर अक्षर *स्थिर*)labels_table;

	rc = gpiochip_add_data(&it87_gpio->chip, it87_gpio);
	अगर (rc)
		जाओ labels_मुक्त;

	वापस 0;

labels_मुक्त:
	kमुक्त(labels_table);
	kमुक्त(labels);
	release_region(it87_gpio->io_base, it87_gpio->io_size);
	वापस rc;
पूर्ण

अटल व्योम __निकास it87_gpio_निकास(व्योम)
अणु
	काष्ठा it87_gpio *it87_gpio = &it87_gpio_chip;

	gpiochip_हटाओ(&it87_gpio->chip);
	release_region(it87_gpio->io_base, it87_gpio->io_size);
	kमुक्त(it87_gpio->chip.names[0]);
	kमुक्त(it87_gpio->chip.names);
पूर्ण

module_init(it87_gpio_init);
module_निकास(it87_gpio_निकास);

MODULE_AUTHOR("Diego Elio Pettenथऑ <flameeyes@flameeyes.eu>");
MODULE_DESCRIPTION("GPIO interface for IT87xx Super I/O chips");
MODULE_LICENSE("GPL");
