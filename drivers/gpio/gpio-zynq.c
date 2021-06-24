<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Xilinx Zynq GPIO device driver
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>

#घोषणा DRIVER_NAME "zynq-gpio"

/* Maximum banks */
#घोषणा ZYNQ_GPIO_MAX_BANK	4
#घोषणा ZYNQMP_GPIO_MAX_BANK	6
#घोषणा VERSAL_GPIO_MAX_BANK	4
#घोषणा PMC_GPIO_MAX_BANK	5
#घोषणा VERSAL_UNUSED_BANKS	2

#घोषणा ZYNQ_GPIO_BANK0_NGPIO	32
#घोषणा ZYNQ_GPIO_BANK1_NGPIO	22
#घोषणा ZYNQ_GPIO_BANK2_NGPIO	32
#घोषणा ZYNQ_GPIO_BANK3_NGPIO	32

#घोषणा ZYNQMP_GPIO_BANK0_NGPIO 26
#घोषणा ZYNQMP_GPIO_BANK1_NGPIO 26
#घोषणा ZYNQMP_GPIO_BANK2_NGPIO 26
#घोषणा ZYNQMP_GPIO_BANK3_NGPIO 32
#घोषणा ZYNQMP_GPIO_BANK4_NGPIO 32
#घोषणा ZYNQMP_GPIO_BANK5_NGPIO 32

#घोषणा	ZYNQ_GPIO_NR_GPIOS	118
#घोषणा	ZYNQMP_GPIO_NR_GPIOS	174

#घोषणा ZYNQ_GPIO_BANK0_PIN_MIN(str)	0
#घोषणा ZYNQ_GPIO_BANK0_PIN_MAX(str)	(ZYNQ_GPIO_BANK0_PIN_MIN(str) + \
					ZYNQ##str##_GPIO_BANK0_NGPIO - 1)
#घोषणा ZYNQ_GPIO_BANK1_PIN_MIN(str)	(ZYNQ_GPIO_BANK0_PIN_MAX(str) + 1)
#घोषणा ZYNQ_GPIO_BANK1_PIN_MAX(str)	(ZYNQ_GPIO_BANK1_PIN_MIN(str) + \
					ZYNQ##str##_GPIO_BANK1_NGPIO - 1)
#घोषणा ZYNQ_GPIO_BANK2_PIN_MIN(str)	(ZYNQ_GPIO_BANK1_PIN_MAX(str) + 1)
#घोषणा ZYNQ_GPIO_BANK2_PIN_MAX(str)	(ZYNQ_GPIO_BANK2_PIN_MIN(str) + \
					ZYNQ##str##_GPIO_BANK2_NGPIO - 1)
#घोषणा ZYNQ_GPIO_BANK3_PIN_MIN(str)	(ZYNQ_GPIO_BANK2_PIN_MAX(str) + 1)
#घोषणा ZYNQ_GPIO_BANK3_PIN_MAX(str)	(ZYNQ_GPIO_BANK3_PIN_MIN(str) + \
					ZYNQ##str##_GPIO_BANK3_NGPIO - 1)
#घोषणा ZYNQ_GPIO_BANK4_PIN_MIN(str)	(ZYNQ_GPIO_BANK3_PIN_MAX(str) + 1)
#घोषणा ZYNQ_GPIO_BANK4_PIN_MAX(str)	(ZYNQ_GPIO_BANK4_PIN_MIN(str) + \
					ZYNQ##str##_GPIO_BANK4_NGPIO - 1)
#घोषणा ZYNQ_GPIO_BANK5_PIN_MIN(str)	(ZYNQ_GPIO_BANK4_PIN_MAX(str) + 1)
#घोषणा ZYNQ_GPIO_BANK5_PIN_MAX(str)	(ZYNQ_GPIO_BANK5_PIN_MIN(str) + \
					ZYNQ##str##_GPIO_BANK5_NGPIO - 1)

/* Register offsets क्रम the GPIO device */
/* LSW Mask & Data -WO */
#घोषणा ZYNQ_GPIO_DATA_LSW_OFFSET(BANK)	(0x000 + (8 * BANK))
/* MSW Mask & Data -WO */
#घोषणा ZYNQ_GPIO_DATA_MSW_OFFSET(BANK)	(0x004 + (8 * BANK))
/* Data Register-RW */
#घोषणा ZYNQ_GPIO_DATA_OFFSET(BANK)	(0x040 + (4 * BANK))
#घोषणा ZYNQ_GPIO_DATA_RO_OFFSET(BANK)	(0x060 + (4 * BANK))
/* Direction mode reg-RW */
#घोषणा ZYNQ_GPIO_सूचीM_OFFSET(BANK)	(0x204 + (0x40 * BANK))
/* Output enable reg-RW */
#घोषणा ZYNQ_GPIO_OUTEN_OFFSET(BANK)	(0x208 + (0x40 * BANK))
/* Interrupt mask reg-RO */
#घोषणा ZYNQ_GPIO_INTMASK_OFFSET(BANK)	(0x20C + (0x40 * BANK))
/* Interrupt enable reg-WO */
#घोषणा ZYNQ_GPIO_INTEN_OFFSET(BANK)	(0x210 + (0x40 * BANK))
/* Interrupt disable reg-WO */
#घोषणा ZYNQ_GPIO_INTDIS_OFFSET(BANK)	(0x214 + (0x40 * BANK))
/* Interrupt status reg-RO */
#घोषणा ZYNQ_GPIO_INTSTS_OFFSET(BANK)	(0x218 + (0x40 * BANK))
/* Interrupt type reg-RW */
#घोषणा ZYNQ_GPIO_INTTYPE_OFFSET(BANK)	(0x21C + (0x40 * BANK))
/* Interrupt polarity reg-RW */
#घोषणा ZYNQ_GPIO_INTPOL_OFFSET(BANK)	(0x220 + (0x40 * BANK))
/* Interrupt on any, reg-RW */
#घोषणा ZYNQ_GPIO_INTANY_OFFSET(BANK)	(0x224 + (0x40 * BANK))

/* Disable all पूर्णांकerrupts mask */
#घोषणा ZYNQ_GPIO_IXR_DISABLE_ALL	0xFFFFFFFF

/* Mid pin number of a bank */
#घोषणा ZYNQ_GPIO_MID_PIN_NUM 16

/* GPIO upper 16 bit mask */
#घोषणा ZYNQ_GPIO_UPPER_MASK 0xFFFF0000

/* set to dअगरferentiate zynq from zynqmp, 0=zynqmp, 1=zynq */
#घोषणा ZYNQ_GPIO_QUIRK_IS_ZYNQ	BIT(0)
#घोषणा GPIO_QUIRK_DATA_RO_BUG	BIT(1)
#घोषणा GPIO_QUIRK_VERSAL	BIT(2)

काष्ठा gpio_regs अणु
	u32 datamsw[ZYNQMP_GPIO_MAX_BANK];
	u32 datalsw[ZYNQMP_GPIO_MAX_BANK];
	u32 dirm[ZYNQMP_GPIO_MAX_BANK];
	u32 outen[ZYNQMP_GPIO_MAX_BANK];
	u32 पूर्णांक_en[ZYNQMP_GPIO_MAX_BANK];
	u32 पूर्णांक_dis[ZYNQMP_GPIO_MAX_BANK];
	u32 पूर्णांक_type[ZYNQMP_GPIO_MAX_BANK];
	u32 पूर्णांक_polarity[ZYNQMP_GPIO_MAX_BANK];
	u32 पूर्णांक_any[ZYNQMP_GPIO_MAX_BANK];
पूर्ण;

/**
 * काष्ठा zynq_gpio - gpio device निजी data काष्ठाure
 * @chip:	instance of the gpio_chip
 * @base_addr:	base address of the GPIO device
 * @clk:	घड़ी resource क्रम this controller
 * @irq:	पूर्णांकerrupt क्रम the GPIO device
 * @p_data:	poपूर्णांकer to platक्रमm data
 * @context:	context रेजिस्टरs
 * @dirlock:	lock used क्रम direction in/out synchronization
 */
काष्ठा zynq_gpio अणु
	काष्ठा gpio_chip chip;
	व्योम __iomem *base_addr;
	काष्ठा clk *clk;
	पूर्णांक irq;
	स्थिर काष्ठा zynq_platक्रमm_data *p_data;
	काष्ठा gpio_regs context;
	spinlock_t dirlock; /* lock */
पूर्ण;

/**
 * काष्ठा zynq_platक्रमm_data -  zynq gpio platक्रमm data काष्ठाure
 * @label:	string to store in gpio->label
 * @quirks:	Flags is used to identअगरy the platक्रमm
 * @ngpio:	max number of gpio pins
 * @max_bank:	maximum number of gpio banks
 * @bank_min:	this array represents bank's min pin
 * @bank_max:	this array represents bank's max pin
 */
काष्ठा zynq_platक्रमm_data अणु
	स्थिर अक्षर *label;
	u32 quirks;
	u16 ngpio;
	पूर्णांक max_bank;
	पूर्णांक bank_min[ZYNQMP_GPIO_MAX_BANK];
	पूर्णांक bank_max[ZYNQMP_GPIO_MAX_BANK];
पूर्ण;

अटल काष्ठा irq_chip zynq_gpio_level_irqchip;
अटल काष्ठा irq_chip zynq_gpio_edge_irqchip;

/**
 * zynq_gpio_is_zynq - test अगर HW is zynq or zynqmp
 * @gpio:	Poपूर्णांकer to driver data काष्ठा
 *
 * Return: 0 अगर zynqmp, 1 अगर zynq.
 */
अटल पूर्णांक zynq_gpio_is_zynq(काष्ठा zynq_gpio *gpio)
अणु
	वापस !!(gpio->p_data->quirks & ZYNQ_GPIO_QUIRK_IS_ZYNQ);
पूर्ण

/**
 * gpio_data_ro_bug - test अगर HW bug exists or not
 * @gpio:       Poपूर्णांकer to driver data काष्ठा
 *
 * Return: 0 अगर bug करोesnot exist, 1 अगर bug exists.
 */
अटल पूर्णांक gpio_data_ro_bug(काष्ठा zynq_gpio *gpio)
अणु
	वापस !!(gpio->p_data->quirks & GPIO_QUIRK_DATA_RO_BUG);
पूर्ण

/**
 * zynq_gpio_get_bank_pin - Get the bank number and pin number within that bank
 * क्रम a given pin in the GPIO device
 * @pin_num:	gpio pin number within the device
 * @bank_num:	an output parameter used to वापस the bank number of the gpio
 *		pin
 * @bank_pin_num: an output parameter used to वापस pin number within a bank
 *		  क्रम the given gpio pin
 * @gpio:	gpio device data काष्ठाure
 *
 * Returns the bank number and pin offset within the bank.
 */
अटल अंतरभूत व्योम zynq_gpio_get_bank_pin(अचिन्हित पूर्णांक pin_num,
					  अचिन्हित पूर्णांक *bank_num,
					  अचिन्हित पूर्णांक *bank_pin_num,
					  काष्ठा zynq_gpio *gpio)
अणु
	पूर्णांक bank;

	क्रम (bank = 0; bank < gpio->p_data->max_bank; bank++) अणु
		अगर ((pin_num >= gpio->p_data->bank_min[bank]) &&
		    (pin_num <= gpio->p_data->bank_max[bank])) अणु
			*bank_num = bank;
			*bank_pin_num = pin_num -
					gpio->p_data->bank_min[bank];
			वापस;
		पूर्ण
		अगर (gpio->p_data->quirks & GPIO_QUIRK_VERSAL)
			bank = bank + VERSAL_UNUSED_BANKS;
	पूर्ण

	/* शेष */
	WARN(true, "invalid GPIO pin number: %u", pin_num);
	*bank_num = 0;
	*bank_pin_num = 0;
पूर्ण

/**
 * zynq_gpio_get_value - Get the state of the specअगरied pin of GPIO device
 * @chip:	gpio_chip instance to be worked on
 * @pin:	gpio pin number within the device
 *
 * This function पढ़ोs the state of the specअगरied pin of the GPIO device.
 *
 * Return: 0 अगर the pin is low, 1 अगर pin is high.
 */
अटल पूर्णांक zynq_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	u32 data;
	अचिन्हित पूर्णांक bank_num, bank_pin_num;
	काष्ठा zynq_gpio *gpio = gpiochip_get_data(chip);

	zynq_gpio_get_bank_pin(pin, &bank_num, &bank_pin_num, gpio);

	अगर (gpio_data_ro_bug(gpio)) अणु
		अगर (zynq_gpio_is_zynq(gpio)) अणु
			अगर (bank_num <= 1) अणु
				data = पढ़ोl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_DATA_RO_OFFSET(bank_num));
			पूर्ण अन्यथा अणु
				data = पढ़ोl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_DATA_OFFSET(bank_num));
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bank_num <= 2) अणु
				data = पढ़ोl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_DATA_RO_OFFSET(bank_num));
			पूर्ण अन्यथा अणु
				data = पढ़ोl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_DATA_OFFSET(bank_num));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		data = पढ़ोl_relaxed(gpio->base_addr +
			ZYNQ_GPIO_DATA_RO_OFFSET(bank_num));
	पूर्ण
	वापस (data >> bank_pin_num) & 1;
पूर्ण

/**
 * zynq_gpio_set_value - Modअगरy the state of the pin with specअगरied value
 * @chip:	gpio_chip instance to be worked on
 * @pin:	gpio pin number within the device
 * @state:	value used to modअगरy the state of the specअगरied pin
 *
 * This function calculates the रेजिस्टर offset (i.e to lower 16 bits or
 * upper 16 bits) based on the given pin number and sets the state of a
 * gpio pin to the specअगरied value. The state is either 0 or non-zero.
 */
अटल व्योम zynq_gpio_set_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin,
				पूर्णांक state)
अणु
	अचिन्हित पूर्णांक reg_offset, bank_num, bank_pin_num;
	काष्ठा zynq_gpio *gpio = gpiochip_get_data(chip);

	zynq_gpio_get_bank_pin(pin, &bank_num, &bank_pin_num, gpio);

	अगर (bank_pin_num >= ZYNQ_GPIO_MID_PIN_NUM) अणु
		/* only 16 data bits in bit maskable reg */
		bank_pin_num -= ZYNQ_GPIO_MID_PIN_NUM;
		reg_offset = ZYNQ_GPIO_DATA_MSW_OFFSET(bank_num);
	पूर्ण अन्यथा अणु
		reg_offset = ZYNQ_GPIO_DATA_LSW_OFFSET(bank_num);
	पूर्ण

	/*
	 * get the 32 bit value to be written to the mask/data रेजिस्टर where
	 * the upper 16 bits is the mask and lower 16 bits is the data
	 */
	state = !!state;
	state = ~(1 << (bank_pin_num + ZYNQ_GPIO_MID_PIN_NUM)) &
		((state << bank_pin_num) | ZYNQ_GPIO_UPPER_MASK);

	ग_लिखोl_relaxed(state, gpio->base_addr + reg_offset);
पूर्ण

/**
 * zynq_gpio_dir_in - Set the direction of the specअगरied GPIO pin as input
 * @chip:	gpio_chip instance to be worked on
 * @pin:	gpio pin number within the device
 *
 * This function uses the पढ़ो-modअगरy-ग_लिखो sequence to set the direction of
 * the gpio pin as input.
 *
 * Return: 0 always
 */
अटल पूर्णांक zynq_gpio_dir_in(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	u32 reg;
	अचिन्हित पूर्णांक bank_num, bank_pin_num;
	अचिन्हित दीर्घ flags;
	काष्ठा zynq_gpio *gpio = gpiochip_get_data(chip);

	zynq_gpio_get_bank_pin(pin, &bank_num, &bank_pin_num, gpio);

	/*
	 * On zynq bank 0 pins 7 and 8 are special and cannot be used
	 * as inमाला_दो.
	 */
	अगर (zynq_gpio_is_zynq(gpio) && bank_num == 0 &&
	    (bank_pin_num == 7 || bank_pin_num == 8))
		वापस -EINVAL;

	/* clear the bit in direction mode reg to set the pin as input */
	spin_lock_irqsave(&gpio->dirlock, flags);
	reg = पढ़ोl_relaxed(gpio->base_addr + ZYNQ_GPIO_सूचीM_OFFSET(bank_num));
	reg &= ~BIT(bank_pin_num);
	ग_लिखोl_relaxed(reg, gpio->base_addr + ZYNQ_GPIO_सूचीM_OFFSET(bank_num));
	spin_unlock_irqrestore(&gpio->dirlock, flags);

	वापस 0;
पूर्ण

/**
 * zynq_gpio_dir_out - Set the direction of the specअगरied GPIO pin as output
 * @chip:	gpio_chip instance to be worked on
 * @pin:	gpio pin number within the device
 * @state:	value to be written to specअगरied pin
 *
 * This function sets the direction of specअगरied GPIO pin as output, configures
 * the Output Enable रेजिस्टर क्रम the pin and uses zynq_gpio_set to set
 * the state of the pin to the value specअगरied.
 *
 * Return: 0 always
 */
अटल पूर्णांक zynq_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin,
			     पूर्णांक state)
अणु
	u32 reg;
	अचिन्हित पूर्णांक bank_num, bank_pin_num;
	अचिन्हित दीर्घ flags;
	काष्ठा zynq_gpio *gpio = gpiochip_get_data(chip);

	zynq_gpio_get_bank_pin(pin, &bank_num, &bank_pin_num, gpio);

	/* set the GPIO pin as output */
	spin_lock_irqsave(&gpio->dirlock, flags);
	reg = पढ़ोl_relaxed(gpio->base_addr + ZYNQ_GPIO_सूचीM_OFFSET(bank_num));
	reg |= BIT(bank_pin_num);
	ग_लिखोl_relaxed(reg, gpio->base_addr + ZYNQ_GPIO_सूचीM_OFFSET(bank_num));

	/* configure the output enable reg क्रम the pin */
	reg = पढ़ोl_relaxed(gpio->base_addr + ZYNQ_GPIO_OUTEN_OFFSET(bank_num));
	reg |= BIT(bank_pin_num);
	ग_लिखोl_relaxed(reg, gpio->base_addr + ZYNQ_GPIO_OUTEN_OFFSET(bank_num));
	spin_unlock_irqrestore(&gpio->dirlock, flags);

	/* set the state of the pin */
	zynq_gpio_set_value(chip, pin, state);
	वापस 0;
पूर्ण

/**
 * zynq_gpio_get_direction - Read the direction of the specअगरied GPIO pin
 * @chip:	gpio_chip instance to be worked on
 * @pin:	gpio pin number within the device
 *
 * This function वापसs the direction of the specअगरied GPIO.
 *
 * Return: GPIO_LINE_सूचीECTION_OUT or GPIO_LINE_सूचीECTION_IN
 */
अटल पूर्णांक zynq_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	u32 reg;
	अचिन्हित पूर्णांक bank_num, bank_pin_num;
	काष्ठा zynq_gpio *gpio = gpiochip_get_data(chip);

	zynq_gpio_get_bank_pin(pin, &bank_num, &bank_pin_num, gpio);

	reg = पढ़ोl_relaxed(gpio->base_addr + ZYNQ_GPIO_सूचीM_OFFSET(bank_num));

	अगर (reg & BIT(bank_pin_num))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

/**
 * zynq_gpio_irq_mask - Disable the पूर्णांकerrupts क्रम a gpio pin
 * @irq_data:	per irq and chip data passed करोwn to chip functions
 *
 * This function calculates gpio pin number from irq number and sets the
 * bit in the Interrupt Disable रेजिस्टर of the corresponding bank to disable
 * पूर्णांकerrupts क्रम that pin.
 */
अटल व्योम zynq_gpio_irq_mask(काष्ठा irq_data *irq_data)
अणु
	अचिन्हित पूर्णांक device_pin_num, bank_num, bank_pin_num;
	काष्ठा zynq_gpio *gpio =
		gpiochip_get_data(irq_data_get_irq_chip_data(irq_data));

	device_pin_num = irq_data->hwirq;
	zynq_gpio_get_bank_pin(device_pin_num, &bank_num, &bank_pin_num, gpio);
	ग_लिखोl_relaxed(BIT(bank_pin_num),
		       gpio->base_addr + ZYNQ_GPIO_INTDIS_OFFSET(bank_num));
पूर्ण

/**
 * zynq_gpio_irq_unmask - Enable the पूर्णांकerrupts क्रम a gpio pin
 * @irq_data:	irq data containing irq number of gpio pin क्रम the पूर्णांकerrupt
 *		to enable
 *
 * This function calculates the gpio pin number from irq number and sets the
 * bit in the Interrupt Enable रेजिस्टर of the corresponding bank to enable
 * पूर्णांकerrupts क्रम that pin.
 */
अटल व्योम zynq_gpio_irq_unmask(काष्ठा irq_data *irq_data)
अणु
	अचिन्हित पूर्णांक device_pin_num, bank_num, bank_pin_num;
	काष्ठा zynq_gpio *gpio =
		gpiochip_get_data(irq_data_get_irq_chip_data(irq_data));

	device_pin_num = irq_data->hwirq;
	zynq_gpio_get_bank_pin(device_pin_num, &bank_num, &bank_pin_num, gpio);
	ग_लिखोl_relaxed(BIT(bank_pin_num),
		       gpio->base_addr + ZYNQ_GPIO_INTEN_OFFSET(bank_num));
पूर्ण

/**
 * zynq_gpio_irq_ack - Acknowledge the पूर्णांकerrupt of a gpio pin
 * @irq_data:	irq data containing irq number of gpio pin क्रम the पूर्णांकerrupt
 *		to ack
 *
 * This function calculates gpio pin number from irq number and sets the bit
 * in the Interrupt Status Register of the corresponding bank, to ACK the irq.
 */
अटल व्योम zynq_gpio_irq_ack(काष्ठा irq_data *irq_data)
अणु
	अचिन्हित पूर्णांक device_pin_num, bank_num, bank_pin_num;
	काष्ठा zynq_gpio *gpio =
		gpiochip_get_data(irq_data_get_irq_chip_data(irq_data));

	device_pin_num = irq_data->hwirq;
	zynq_gpio_get_bank_pin(device_pin_num, &bank_num, &bank_pin_num, gpio);
	ग_लिखोl_relaxed(BIT(bank_pin_num),
		       gpio->base_addr + ZYNQ_GPIO_INTSTS_OFFSET(bank_num));
पूर्ण

/**
 * zynq_gpio_irq_enable - Enable the पूर्णांकerrupts क्रम a gpio pin
 * @irq_data:	irq data containing irq number of gpio pin क्रम the पूर्णांकerrupt
 *		to enable
 *
 * Clears the INTSTS bit and unmasks the given पूर्णांकerrupt.
 */
अटल व्योम zynq_gpio_irq_enable(काष्ठा irq_data *irq_data)
अणु
	/*
	 * The Zynq GPIO controller करोes not disable पूर्णांकerrupt detection when
	 * the पूर्णांकerrupt is masked and only disables the propagation of the
	 * पूर्णांकerrupt. This means when the controller detects an पूर्णांकerrupt
	 * condition जबतक the पूर्णांकerrupt is logically disabled it will propagate
	 * that पूर्णांकerrupt event once the पूर्णांकerrupt is enabled. This will cause
	 * the पूर्णांकerrupt consumer to see spurious पूर्णांकerrupts to prevent this
	 * first make sure that the पूर्णांकerrupt is not निश्चितed and then enable
	 * it.
	 */
	zynq_gpio_irq_ack(irq_data);
	zynq_gpio_irq_unmask(irq_data);
पूर्ण

/**
 * zynq_gpio_set_irq_type - Set the irq type क्रम a gpio pin
 * @irq_data:	irq data containing irq number of gpio pin
 * @type:	पूर्णांकerrupt type that is to be set क्रम the gpio pin
 *
 * This function माला_लो the gpio pin number and its bank from the gpio pin number
 * and configures the INT_TYPE, INT_POLARITY and INT_ANY रेजिस्टरs.
 *
 * Return: 0, negative error otherwise.
 * TYPE-EDGE_RISING,  INT_TYPE - 1, INT_POLARITY - 1,  INT_ANY - 0;
 * TYPE-EDGE_FALLING, INT_TYPE - 1, INT_POLARITY - 0,  INT_ANY - 0;
 * TYPE-EDGE_BOTH,    INT_TYPE - 1, INT_POLARITY - NA, INT_ANY - 1;
 * TYPE-LEVEL_HIGH,   INT_TYPE - 0, INT_POLARITY - 1,  INT_ANY - NA;
 * TYPE-LEVEL_LOW,    INT_TYPE - 0, INT_POLARITY - 0,  INT_ANY - NA
 */
अटल पूर्णांक zynq_gpio_set_irq_type(काष्ठा irq_data *irq_data, अचिन्हित पूर्णांक type)
अणु
	u32 पूर्णांक_type, पूर्णांक_pol, पूर्णांक_any;
	अचिन्हित पूर्णांक device_pin_num, bank_num, bank_pin_num;
	काष्ठा zynq_gpio *gpio =
		gpiochip_get_data(irq_data_get_irq_chip_data(irq_data));

	device_pin_num = irq_data->hwirq;
	zynq_gpio_get_bank_pin(device_pin_num, &bank_num, &bank_pin_num, gpio);

	पूर्णांक_type = पढ़ोl_relaxed(gpio->base_addr +
				 ZYNQ_GPIO_INTTYPE_OFFSET(bank_num));
	पूर्णांक_pol = पढ़ोl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTPOL_OFFSET(bank_num));
	पूर्णांक_any = पढ़ोl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTANY_OFFSET(bank_num));

	/*
	 * based on the type requested, configure the INT_TYPE, INT_POLARITY
	 * and INT_ANY रेजिस्टरs
	 */
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		पूर्णांक_type |= BIT(bank_pin_num);
		पूर्णांक_pol |= BIT(bank_pin_num);
		पूर्णांक_any &= ~BIT(bank_pin_num);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		पूर्णांक_type |= BIT(bank_pin_num);
		पूर्णांक_pol &= ~BIT(bank_pin_num);
		पूर्णांक_any &= ~BIT(bank_pin_num);
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		पूर्णांक_type |= BIT(bank_pin_num);
		पूर्णांक_any |= BIT(bank_pin_num);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		पूर्णांक_type &= ~BIT(bank_pin_num);
		पूर्णांक_pol |= BIT(bank_pin_num);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		पूर्णांक_type &= ~BIT(bank_pin_num);
		पूर्णांक_pol &= ~BIT(bank_pin_num);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl_relaxed(पूर्णांक_type,
		       gpio->base_addr + ZYNQ_GPIO_INTTYPE_OFFSET(bank_num));
	ग_लिखोl_relaxed(पूर्णांक_pol,
		       gpio->base_addr + ZYNQ_GPIO_INTPOL_OFFSET(bank_num));
	ग_लिखोl_relaxed(पूर्णांक_any,
		       gpio->base_addr + ZYNQ_GPIO_INTANY_OFFSET(bank_num));

	अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_chip_handler_name_locked(irq_data,
						 &zynq_gpio_level_irqchip,
						 handle_fasteoi_irq, शून्य);
	अन्यथा
		irq_set_chip_handler_name_locked(irq_data,
						 &zynq_gpio_edge_irqchip,
						 handle_level_irq, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक zynq_gpio_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा zynq_gpio *gpio =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	irq_set_irq_wake(gpio->irq, on);

	वापस 0;
पूर्ण

अटल पूर्णांक zynq_gpio_irq_reqres(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(chip->parent);
	अगर (ret < 0)
		वापस ret;

	वापस gpiochip_reqres_irq(chip, d->hwirq);
पूर्ण

अटल व्योम zynq_gpio_irq_relres(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);

	gpiochip_relres_irq(chip, d->hwirq);
	pm_runसमय_put(chip->parent);
पूर्ण

/* irq chip descriptor */
अटल काष्ठा irq_chip zynq_gpio_level_irqchip = अणु
	.name		= DRIVER_NAME,
	.irq_enable	= zynq_gpio_irq_enable,
	.irq_eoi	= zynq_gpio_irq_ack,
	.irq_mask	= zynq_gpio_irq_mask,
	.irq_unmask	= zynq_gpio_irq_unmask,
	.irq_set_type	= zynq_gpio_set_irq_type,
	.irq_set_wake	= zynq_gpio_set_wake,
	.irq_request_resources = zynq_gpio_irq_reqres,
	.irq_release_resources = zynq_gpio_irq_relres,
	.flags		= IRQCHIP_EOI_THREADED | IRQCHIP_EOI_IF_HANDLED |
			  IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल काष्ठा irq_chip zynq_gpio_edge_irqchip = अणु
	.name		= DRIVER_NAME,
	.irq_enable	= zynq_gpio_irq_enable,
	.irq_ack	= zynq_gpio_irq_ack,
	.irq_mask	= zynq_gpio_irq_mask,
	.irq_unmask	= zynq_gpio_irq_unmask,
	.irq_set_type	= zynq_gpio_set_irq_type,
	.irq_set_wake	= zynq_gpio_set_wake,
	.irq_request_resources = zynq_gpio_irq_reqres,
	.irq_release_resources = zynq_gpio_irq_relres,
	.flags		= IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल व्योम zynq_gpio_handle_bank_irq(काष्ठा zynq_gpio *gpio,
				      अचिन्हित पूर्णांक bank_num,
				      अचिन्हित दीर्घ pending)
अणु
	अचिन्हित पूर्णांक bank_offset = gpio->p_data->bank_min[bank_num];
	काष्ठा irq_करोमुख्य *irqकरोमुख्य = gpio->chip.irq.करोमुख्य;
	पूर्णांक offset;

	अगर (!pending)
		वापस;

	क्रम_each_set_bit(offset, &pending, 32) अणु
		अचिन्हित पूर्णांक gpio_irq;

		gpio_irq = irq_find_mapping(irqकरोमुख्य, offset + bank_offset);
		generic_handle_irq(gpio_irq);
	पूर्ण
पूर्ण

/**
 * zynq_gpio_irqhandler - IRQ handler क्रम the gpio banks of a gpio device
 * @desc:	irq descriptor instance of the 'irq'
 *
 * This function पढ़ोs the Interrupt Status Register of each bank to get the
 * gpio pin number which has triggered an पूर्णांकerrupt. It then acks the triggered
 * पूर्णांकerrupt and calls the pin specअगरic handler set by the higher layer
 * application क्रम that pin.
 * Note: A bug is reported अगर no handler is set क्रम the gpio pin.
 */
अटल व्योम zynq_gpio_irqhandler(काष्ठा irq_desc *desc)
अणु
	u32 पूर्णांक_sts, पूर्णांक_enb;
	अचिन्हित पूर्णांक bank_num;
	काष्ठा zynq_gpio *gpio =
		gpiochip_get_data(irq_desc_get_handler_data(desc));
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);

	chained_irq_enter(irqchip, desc);

	क्रम (bank_num = 0; bank_num < gpio->p_data->max_bank; bank_num++) अणु
		पूर्णांक_sts = पढ़ोl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_INTSTS_OFFSET(bank_num));
		पूर्णांक_enb = पढ़ोl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_INTMASK_OFFSET(bank_num));
		zynq_gpio_handle_bank_irq(gpio, bank_num, पूर्णांक_sts & ~पूर्णांक_enb);
		अगर (gpio->p_data->quirks & GPIO_QUIRK_VERSAL)
			bank_num = bank_num + VERSAL_UNUSED_BANKS;
	पूर्ण

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल व्योम zynq_gpio_save_context(काष्ठा zynq_gpio *gpio)
अणु
	अचिन्हित पूर्णांक bank_num;

	क्रम (bank_num = 0; bank_num < gpio->p_data->max_bank; bank_num++) अणु
		gpio->context.datalsw[bank_num] =
				पढ़ोl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_DATA_LSW_OFFSET(bank_num));
		gpio->context.datamsw[bank_num] =
				पढ़ोl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_DATA_MSW_OFFSET(bank_num));
		gpio->context.dirm[bank_num] = पढ़ोl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_सूचीM_OFFSET(bank_num));
		gpio->context.पूर्णांक_en[bank_num] = पढ़ोl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTMASK_OFFSET(bank_num));
		gpio->context.पूर्णांक_type[bank_num] =
				पढ़ोl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTTYPE_OFFSET(bank_num));
		gpio->context.पूर्णांक_polarity[bank_num] =
				पढ़ोl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTPOL_OFFSET(bank_num));
		gpio->context.पूर्णांक_any[bank_num] =
				पढ़ोl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTANY_OFFSET(bank_num));
		अगर (gpio->p_data->quirks & GPIO_QUIRK_VERSAL)
			bank_num = bank_num + VERSAL_UNUSED_BANKS;
	पूर्ण
पूर्ण

अटल व्योम zynq_gpio_restore_context(काष्ठा zynq_gpio *gpio)
अणु
	अचिन्हित पूर्णांक bank_num;

	क्रम (bank_num = 0; bank_num < gpio->p_data->max_bank; bank_num++) अणु
		ग_लिखोl_relaxed(ZYNQ_GPIO_IXR_DISABLE_ALL, gpio->base_addr +
				ZYNQ_GPIO_INTDIS_OFFSET(bank_num));
		ग_लिखोl_relaxed(gpio->context.datalsw[bank_num],
			       gpio->base_addr +
			       ZYNQ_GPIO_DATA_LSW_OFFSET(bank_num));
		ग_लिखोl_relaxed(gpio->context.datamsw[bank_num],
			       gpio->base_addr +
			       ZYNQ_GPIO_DATA_MSW_OFFSET(bank_num));
		ग_लिखोl_relaxed(gpio->context.dirm[bank_num],
			       gpio->base_addr +
			       ZYNQ_GPIO_सूचीM_OFFSET(bank_num));
		ग_लिखोl_relaxed(gpio->context.पूर्णांक_type[bank_num],
			       gpio->base_addr +
			       ZYNQ_GPIO_INTTYPE_OFFSET(bank_num));
		ग_लिखोl_relaxed(gpio->context.पूर्णांक_polarity[bank_num],
			       gpio->base_addr +
			       ZYNQ_GPIO_INTPOL_OFFSET(bank_num));
		ग_लिखोl_relaxed(gpio->context.पूर्णांक_any[bank_num],
			       gpio->base_addr +
			       ZYNQ_GPIO_INTANY_OFFSET(bank_num));
		ग_लिखोl_relaxed(~(gpio->context.पूर्णांक_en[bank_num]),
			       gpio->base_addr +
			       ZYNQ_GPIO_INTEN_OFFSET(bank_num));
		अगर (gpio->p_data->quirks & GPIO_QUIRK_VERSAL)
			bank_num = bank_num + VERSAL_UNUSED_BANKS;
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused zynq_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा zynq_gpio *gpio = dev_get_drvdata(dev);
	काष्ठा irq_data *data = irq_get_irq_data(gpio->irq);

	अगर (!device_may_wakeup(dev))
		disable_irq(gpio->irq);

	अगर (!irqd_is_wakeup_set(data)) अणु
		zynq_gpio_save_context(gpio);
		वापस pm_runसमय_क्रमce_suspend(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused zynq_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा zynq_gpio *gpio = dev_get_drvdata(dev);
	काष्ठा irq_data *data = irq_get_irq_data(gpio->irq);
	पूर्णांक ret;

	अगर (!device_may_wakeup(dev))
		enable_irq(gpio->irq);

	अगर (!irqd_is_wakeup_set(data)) अणु
		ret = pm_runसमय_क्रमce_resume(dev);
		zynq_gpio_restore_context(gpio);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused zynq_gpio_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा zynq_gpio *gpio = dev_get_drvdata(dev);

	clk_disable_unprepare(gpio->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused zynq_gpio_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा zynq_gpio *gpio = dev_get_drvdata(dev);

	वापस clk_prepare_enable(gpio->clk);
पूर्ण

अटल पूर्णांक zynq_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(chip->parent);

	/*
	 * If the device is alपढ़ोy active pm_runसमय_get() will वापस 1 on
	 * success, but gpio_request still needs to वापस 0.
	 */
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम zynq_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	pm_runसमय_put(chip->parent);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops zynq_gpio_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(zynq_gpio_suspend, zynq_gpio_resume)
	SET_RUNTIME_PM_OPS(zynq_gpio_runसमय_suspend,
			   zynq_gpio_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा zynq_platक्रमm_data versal_gpio_def = अणु
	.label = "versal_gpio",
	.quirks = GPIO_QUIRK_VERSAL,
	.ngpio = 58,
	.max_bank = VERSAL_GPIO_MAX_BANK,
	.bank_min[0] = 0,
	.bank_max[0] = 25, /* 0 to 25 are connected to MIOs (26 pins) */
	.bank_min[3] = 26,
	.bank_max[3] = 57, /* Bank 3 is connected to FMIOs (32 pins) */
पूर्ण;

अटल स्थिर काष्ठा zynq_platक्रमm_data pmc_gpio_def = अणु
	.label = "pmc_gpio",
	.ngpio = 116,
	.max_bank = PMC_GPIO_MAX_BANK,
	.bank_min[0] = 0,
	.bank_max[0] = 25, /* 0 to 25 are connected to MIOs (26 pins) */
	.bank_min[1] = 26,
	.bank_max[1] = 51, /* Bank 1 are connected to MIOs (26 pins) */
	.bank_min[3] = 52,
	.bank_max[3] = 83, /* Bank 3 is connected to EMIOs (32 pins) */
	.bank_min[4] = 84,
	.bank_max[4] = 115, /* Bank 4 is connected to EMIOs (32 pins) */
पूर्ण;

अटल स्थिर काष्ठा zynq_platक्रमm_data zynqmp_gpio_def = अणु
	.label = "zynqmp_gpio",
	.quirks = GPIO_QUIRK_DATA_RO_BUG,
	.ngpio = ZYNQMP_GPIO_NR_GPIOS,
	.max_bank = ZYNQMP_GPIO_MAX_BANK,
	.bank_min[0] = ZYNQ_GPIO_BANK0_PIN_MIN(MP),
	.bank_max[0] = ZYNQ_GPIO_BANK0_PIN_MAX(MP),
	.bank_min[1] = ZYNQ_GPIO_BANK1_PIN_MIN(MP),
	.bank_max[1] = ZYNQ_GPIO_BANK1_PIN_MAX(MP),
	.bank_min[2] = ZYNQ_GPIO_BANK2_PIN_MIN(MP),
	.bank_max[2] = ZYNQ_GPIO_BANK2_PIN_MAX(MP),
	.bank_min[3] = ZYNQ_GPIO_BANK3_PIN_MIN(MP),
	.bank_max[3] = ZYNQ_GPIO_BANK3_PIN_MAX(MP),
	.bank_min[4] = ZYNQ_GPIO_BANK4_PIN_MIN(MP),
	.bank_max[4] = ZYNQ_GPIO_BANK4_PIN_MAX(MP),
	.bank_min[5] = ZYNQ_GPIO_BANK5_PIN_MIN(MP),
	.bank_max[5] = ZYNQ_GPIO_BANK5_PIN_MAX(MP),
पूर्ण;

अटल स्थिर काष्ठा zynq_platक्रमm_data zynq_gpio_def = अणु
	.label = "zynq_gpio",
	.quirks = ZYNQ_GPIO_QUIRK_IS_ZYNQ | GPIO_QUIRK_DATA_RO_BUG,
	.ngpio = ZYNQ_GPIO_NR_GPIOS,
	.max_bank = ZYNQ_GPIO_MAX_BANK,
	.bank_min[0] = ZYNQ_GPIO_BANK0_PIN_MIN(),
	.bank_max[0] = ZYNQ_GPIO_BANK0_PIN_MAX(),
	.bank_min[1] = ZYNQ_GPIO_BANK1_PIN_MIN(),
	.bank_max[1] = ZYNQ_GPIO_BANK1_PIN_MAX(),
	.bank_min[2] = ZYNQ_GPIO_BANK2_PIN_MIN(),
	.bank_max[2] = ZYNQ_GPIO_BANK2_PIN_MAX(),
	.bank_min[3] = ZYNQ_GPIO_BANK3_PIN_MIN(),
	.bank_max[3] = ZYNQ_GPIO_BANK3_PIN_MAX(),
पूर्ण;

अटल स्थिर काष्ठा of_device_id zynq_gpio_of_match[] = अणु
	अणु .compatible = "xlnx,zynq-gpio-1.0", .data = &zynq_gpio_def पूर्ण,
	अणु .compatible = "xlnx,zynqmp-gpio-1.0", .data = &zynqmp_gpio_def पूर्ण,
	अणु .compatible = "xlnx,versal-gpio-1.0", .data = &versal_gpio_def पूर्ण,
	अणु .compatible = "xlnx,pmc-gpio-1.0", .data = &pmc_gpio_def पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, zynq_gpio_of_match);

/**
 * zynq_gpio_probe - Initialization method क्रम a zynq_gpio device
 * @pdev:	platक्रमm device instance
 *
 * This function allocates memory resources क्रम the gpio device and रेजिस्टरs
 * all the banks of the device. It will also set up पूर्णांकerrupts क्रम the gpio
 * pins.
 * Note: Interrupts are disabled क्रम all the banks during initialization.
 *
 * Return: 0 on success, negative error otherwise.
 */
अटल पूर्णांक zynq_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, bank_num;
	काष्ठा zynq_gpio *gpio;
	काष्ठा gpio_chip *chip;
	काष्ठा gpio_irq_chip *girq;
	स्थिर काष्ठा of_device_id *match;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	match = of_match_node(zynq_gpio_of_match, pdev->dev.of_node);
	अगर (!match) अणु
		dev_err(&pdev->dev, "of_match_node() failed\n");
		वापस -EINVAL;
	पूर्ण
	gpio->p_data = match->data;
	platक्रमm_set_drvdata(pdev, gpio);

	gpio->base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio->base_addr))
		वापस PTR_ERR(gpio->base_addr);

	gpio->irq = platक्रमm_get_irq(pdev, 0);
	अगर (gpio->irq < 0)
		वापस gpio->irq;

	/* configure the gpio chip */
	chip = &gpio->chip;
	chip->label = gpio->p_data->label;
	chip->owner = THIS_MODULE;
	chip->parent = &pdev->dev;
	chip->get = zynq_gpio_get_value;
	chip->set = zynq_gpio_set_value;
	chip->request = zynq_gpio_request;
	chip->मुक्त = zynq_gpio_मुक्त;
	chip->direction_input = zynq_gpio_dir_in;
	chip->direction_output = zynq_gpio_dir_out;
	chip->get_direction = zynq_gpio_get_direction;
	chip->base = of_alias_get_id(pdev->dev.of_node, "gpio");
	chip->ngpio = gpio->p_data->ngpio;

	/* Retrieve GPIO घड़ी */
	gpio->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(gpio->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(gpio->clk), "input clock not found.\n");

	ret = clk_prepare_enable(gpio->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		वापस ret;
	पूर्ण

	spin_lock_init(&gpio->dirlock);

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_resume_and_get(&pdev->dev);
	अगर (ret < 0)
		जाओ err_pm_dis;

	/* disable पूर्णांकerrupts क्रम all banks */
	क्रम (bank_num = 0; bank_num < gpio->p_data->max_bank; bank_num++) अणु
		ग_लिखोl_relaxed(ZYNQ_GPIO_IXR_DISABLE_ALL, gpio->base_addr +
			       ZYNQ_GPIO_INTDIS_OFFSET(bank_num));
		अगर (gpio->p_data->quirks & GPIO_QUIRK_VERSAL)
			bank_num = bank_num + VERSAL_UNUSED_BANKS;
	पूर्ण

	/* Set up the GPIO irqchip */
	girq = &chip->irq;
	girq->chip = &zynq_gpio_edge_irqchip;
	girq->parent_handler = zynq_gpio_irqhandler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
				     माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents) अणु
		ret = -ENOMEM;
		जाओ err_pm_put;
	पूर्ण
	girq->parents[0] = gpio->irq;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	/* report a bug अगर gpio chip registration fails */
	ret = gpiochip_add_data(chip, gpio);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add gpio chip\n");
		जाओ err_pm_put;
	पूर्ण

	irq_set_status_flags(gpio->irq, IRQ_DISABLE_UNLAZY);
	device_init_wakeup(&pdev->dev, 1);
	pm_runसमय_put(&pdev->dev);

	वापस 0;

err_pm_put:
	pm_runसमय_put(&pdev->dev);
err_pm_dis:
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(gpio->clk);

	वापस ret;
पूर्ण

/**
 * zynq_gpio_हटाओ - Driver removal function
 * @pdev:	platक्रमm device instance
 *
 * Return: 0 always
 */
अटल पूर्णांक zynq_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynq_gpio *gpio = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&pdev->dev);
	gpiochip_हटाओ(&gpio->chip);
	clk_disable_unprepare(gpio->clk);
	device_set_wakeup_capable(&pdev->dev, 0);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver zynq_gpio_driver = अणु
	.driver	= अणु
		.name = DRIVER_NAME,
		.pm = &zynq_gpio_dev_pm_ops,
		.of_match_table = zynq_gpio_of_match,
	पूर्ण,
	.probe = zynq_gpio_probe,
	.हटाओ = zynq_gpio_हटाओ,
पूर्ण;

/**
 * zynq_gpio_init - Initial driver registration call
 *
 * Return: value from platक्रमm_driver_रेजिस्टर
 */
अटल पूर्णांक __init zynq_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&zynq_gpio_driver);
पूर्ण
postcore_initcall(zynq_gpio_init);

अटल व्योम __निकास zynq_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&zynq_gpio_driver);
पूर्ण
module_निकास(zynq_gpio_निकास);

MODULE_AUTHOR("Xilinx Inc.");
MODULE_DESCRIPTION("Zynq GPIO driver");
MODULE_LICENSE("GPL");
