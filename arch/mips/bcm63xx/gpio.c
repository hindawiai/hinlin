<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 * Copyright (C) 2008-2011 Florian Fainelli <florian@खोलोwrt.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>

#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_gpपन.स>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>

अटल u32 gpio_out_low_reg;

अटल व्योम bcm63xx_gpio_out_low_reg_init(व्योम)
अणु
	चयन (bcm63xx_get_cpu_id()) अणु
	हाल BCM6345_CPU_ID:
		gpio_out_low_reg = GPIO_DATA_LO_REG_6345;
		अवरोध;
	शेष:
		gpio_out_low_reg = GPIO_DATA_LO_REG;
		अवरोध;
	पूर्ण
पूर्ण

अटल DEFINE_SPINLOCK(bcm63xx_gpio_lock);
अटल u32 gpio_out_low, gpio_out_high;

अटल व्योम bcm63xx_gpio_set(काष्ठा gpio_chip *chip,
			     अचिन्हित gpio, पूर्णांक val)
अणु
	u32 reg;
	u32 mask;
	u32 *v;
	अचिन्हित दीर्घ flags;

	BUG_ON(gpio >= chip->ngpio);

	अगर (gpio < 32) अणु
		reg = gpio_out_low_reg;
		mask = 1 << gpio;
		v = &gpio_out_low;
	पूर्ण अन्यथा अणु
		reg = GPIO_DATA_HI_REG;
		mask = 1 << (gpio - 32);
		v = &gpio_out_high;
	पूर्ण

	spin_lock_irqsave(&bcm63xx_gpio_lock, flags);
	अगर (val)
		*v |= mask;
	अन्यथा
		*v &= ~mask;
	bcm_gpio_ग_लिखोl(*v, reg);
	spin_unlock_irqrestore(&bcm63xx_gpio_lock, flags);
पूर्ण

अटल पूर्णांक bcm63xx_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	u32 reg;
	u32 mask;

	BUG_ON(gpio >= chip->ngpio);

	अगर (gpio < 32) अणु
		reg = gpio_out_low_reg;
		mask = 1 << gpio;
	पूर्ण अन्यथा अणु
		reg = GPIO_DATA_HI_REG;
		mask = 1 << (gpio - 32);
	पूर्ण

	वापस !!(bcm_gpio_पढ़ोl(reg) & mask);
पूर्ण

अटल पूर्णांक bcm63xx_gpio_set_direction(काष्ठा gpio_chip *chip,
				      अचिन्हित gpio, पूर्णांक dir)
अणु
	u32 reg;
	u32 mask;
	u32 पंचांगp;
	अचिन्हित दीर्घ flags;

	BUG_ON(gpio >= chip->ngpio);

	अगर (gpio < 32) अणु
		reg = GPIO_CTL_LO_REG;
		mask = 1 << gpio;
	पूर्ण अन्यथा अणु
		reg = GPIO_CTL_HI_REG;
		mask = 1 << (gpio - 32);
	पूर्ण

	spin_lock_irqsave(&bcm63xx_gpio_lock, flags);
	पंचांगp = bcm_gpio_पढ़ोl(reg);
	अगर (dir == BCM63XX_GPIO_सूची_IN)
		पंचांगp &= ~mask;
	अन्यथा
		पंचांगp |= mask;
	bcm_gpio_ग_लिखोl(पंचांगp, reg);
	spin_unlock_irqrestore(&bcm63xx_gpio_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	वापस bcm63xx_gpio_set_direction(chip, gpio, BCM63XX_GPIO_सूची_IN);
पूर्ण

अटल पूर्णांक bcm63xx_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित gpio, पूर्णांक value)
अणु
	bcm63xx_gpio_set(chip, gpio, value);
	वापस bcm63xx_gpio_set_direction(chip, gpio, BCM63XX_GPIO_सूची_OUT);
पूर्ण


अटल काष्ठा gpio_chip bcm63xx_gpio_chip = अणु
	.label			= "bcm63xx-gpio",
	.direction_input	= bcm63xx_gpio_direction_input,
	.direction_output	= bcm63xx_gpio_direction_output,
	.get			= bcm63xx_gpio_get,
	.set			= bcm63xx_gpio_set,
	.base			= 0,
पूर्ण;

पूर्णांक __init bcm63xx_gpio_init(व्योम)
अणु
	bcm63xx_gpio_out_low_reg_init();

	gpio_out_low = bcm_gpio_पढ़ोl(gpio_out_low_reg);
	अगर (!BCMCPU_IS_6345())
		gpio_out_high = bcm_gpio_पढ़ोl(GPIO_DATA_HI_REG);
	bcm63xx_gpio_chip.ngpio = bcm63xx_gpio_count();
	pr_info("registering %d GPIOs\n", bcm63xx_gpio_chip.ngpio);

	वापस gpiochip_add_data(&bcm63xx_gpio_chip, शून्य);
पूर्ण
