<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C Platक्रमm - GPIO core
 */

#अगर_अघोषित __PLAT_SAMSUNG_GPIO_CORE_H
#घोषणा __PLAT_SAMSUNG_GPIO_CORE_H

/* Bring in machine-local definitions, especially S3C_GPIO_END */
#समावेश "gpio-samsung.h"
#समावेश <linux/gpio/driver.h>

#घोषणा GPIOCON_OFF	(0x00)
#घोषणा GPIODAT_OFF	(0x04)

#घोषणा con_4bit_shअगरt(__off) ((__off) * 4)

/* Define the core gpiolib support functions that the s3c platक्रमms may
 * need to extend or change depending on the hardware and the s3c chip
 * selected at build or found at run समय.
 *
 * These definitions are not पूर्णांकended क्रम driver inclusion, there is
 * nothing here that should not live outside the platक्रमm and core
 * specअगरic code.
*/

काष्ठा samsung_gpio_chip;

/**
 * काष्ठा samsung_gpio_pm - घातer management (suspend/resume) inक्रमmation
 * @save: Routine to save the state of the GPIO block
 * @resume: Routine to resume the GPIO block.
 */
काष्ठा samsung_gpio_pm अणु
	व्योम (*save)(काष्ठा samsung_gpio_chip *chip);
	व्योम (*resume)(काष्ठा samsung_gpio_chip *chip);
पूर्ण;

काष्ठा samsung_gpio_cfg;

/**
 * काष्ठा samsung_gpio_chip - wrapper क्रम specअगरic implementation of gpio
 * @chip: The chip काष्ठाure to be exported via gpiolib.
 * @base: The base poपूर्णांकer to the gpio configuration रेजिस्टरs.
 * @group: The group रेजिस्टर number क्रम gpio पूर्णांकerrupt support.
 * @irq_base: The base irq number.
 * @config: special function and pull-resistor control inक्रमmation.
 * @lock: Lock क्रम exclusive access to this gpio bank.
 * @pm_save: Save inक्रमmation क्रम suspend/resume support.
 * @biपंचांगap_gpio_पूर्णांक: Biपंचांगap क्रम representing GPIO पूर्णांकerrupt or not.
 *
 * This wrapper provides the necessary inक्रमmation क्रम the Samsung
 * specअगरic gpios being रेजिस्टरed with gpiolib.
 *
 * The lock protects each gpio bank from multiple access of the shared
 * configuration रेजिस्टरs, or from पढ़ोing of data whilst another thपढ़ो
 * is writing to the रेजिस्टर set.
 *
 * Each chip has its own lock to aव्योम any  contention between dअगरferent
 * CPU cores trying to get one lock क्रम dअगरferent GPIO banks, where each
 * bank of GPIO has its own रेजिस्टर space and configuration रेजिस्टरs.
 */
काष्ठा samsung_gpio_chip अणु
	काष्ठा gpio_chip	chip;
	काष्ठा samsung_gpio_cfg	*config;
	काष्ठा samsung_gpio_pm	*pm;
	व्योम __iomem		*base;
	पूर्णांक			irq_base;
	पूर्णांक			group;
	spinlock_t		 lock;
#अगर_घोषित CONFIG_PM
	u32			pm_save[4];
#पूर्ण_अगर
	u32			biपंचांगap_gpio_पूर्णांक;
पूर्ण;

अटल अंतरभूत काष्ठा samsung_gpio_chip *to_samsung_gpio(काष्ठा gpio_chip *gpc)
अणु
	वापस container_of(gpc, काष्ठा samsung_gpio_chip, chip);
पूर्ण

/**
 * samsung_gpiolib_to_irq - convert gpio pin to irq number
 * @chip: The gpio chip that the pin beदीर्घs to.
 * @offset: The offset of the pin in the chip.
 *
 * This helper वापसs the irq number calculated from the chip->irq_base and
 * the provided offset.
 */
बाह्य पूर्णांक samsung_gpiolib_to_irq(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset);

/* exported क्रम core SoC support to change */
बाह्य काष्ठा samsung_gpio_cfg s3c24xx_gpiocfg_शेष;

#अगर_घोषित CONFIG_S3C_GPIO_TRACK
बाह्य काष्ठा samsung_gpio_chip *s3c_gpios[S3C_GPIO_END];

अटल अंतरभूत काष्ठा samsung_gpio_chip *samsung_gpiolib_अ_लोhip(अचिन्हित पूर्णांक chip)
अणु
	वापस (chip < S3C_GPIO_END) ? s3c_gpios[chip] : शून्य;
पूर्ण
#अन्यथा
/* machine specअगरic code should provide samsung_gpiolib_अ_लोhip */

बाह्य काष्ठा samsung_gpio_chip s3c24xx_gpios[];

अटल अंतरभूत काष्ठा samsung_gpio_chip *samsung_gpiolib_अ_लोhip(अचिन्हित पूर्णांक pin)
अणु
	काष्ठा samsung_gpio_chip *chip;

	अगर (pin > S3C_GPIO_END)
		वापस शून्य;

	chip = &s3c24xx_gpios[pin/32];
	वापस ((pin - chip->chip.base) < chip->chip.ngpio) ? chip : शून्य;
पूर्ण

अटल अंतरभूत व्योम s3c_gpiolib_track(काष्ठा samsung_gpio_chip *chip) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
बाह्य काष्ठा samsung_gpio_pm samsung_gpio_pm_1bit;
बाह्य काष्ठा samsung_gpio_pm samsung_gpio_pm_2bit;
बाह्य काष्ठा samsung_gpio_pm samsung_gpio_pm_4bit;
#घोषणा __gpio_pm(x) x
#अन्यथा
#घोषणा samsung_gpio_pm_1bit शून्य
#घोषणा samsung_gpio_pm_2bit शून्य
#घोषणा samsung_gpio_pm_4bit शून्य
#घोषणा __gpio_pm(x) शून्य

#पूर्ण_अगर /* CONFIG_PM */

/* locking wrappers to deal with multiple access to the same gpio bank */
#घोषणा samsung_gpio_lock(_oc, _fl) spin_lock_irqsave(&(_oc)->lock, _fl)
#घोषणा samsung_gpio_unlock(_oc, _fl) spin_unlock_irqrestore(&(_oc)->lock, _fl)

#पूर्ण_अगर /* __PLAT_SAMSUNG_GPIO_CORE_H */
