<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C Platक्रमm - GPIO pin configuration
 */

/* This file contains the necessary definitions to get the basic gpio
 * pin configuration करोne such as setting a pin to input or output or
 * changing the pull-अणुup,करोwnपूर्ण configurations.
 */

/* Note, this पूर्णांकerface is being added to the s3c64xx arch first and will
 * be added to the s3c24xx प्रणालीs later.
 */

#अगर_अघोषित __PLAT_GPIO_CFG_H
#घोषणा __PLAT_GPIO_CFG_H __खाता__

#समावेश <linux/types.h>

प्रकार अचिन्हित पूर्णांक __bitwise samsung_gpio_pull_t;

/* क्रमward declaration अगर gpio-core.h hasn't been included */
काष्ठा samsung_gpio_chip;

/**
 * काष्ठा samsung_gpio_cfg GPIO configuration
 * @cfg_eपूर्णांक: Configuration setting when used क्रम बाह्यal पूर्णांकerrupt source
 * @get_pull: Read the current pull configuration क्रम the GPIO
 * @set_pull: Set the current pull configuration क्रम the GPIO
 * @set_config: Set the current configuration क्रम the GPIO
 * @get_config: Read the current configuration क्रम the GPIO
 *
 * Each chip can have more than one type of GPIO bank available and some
 * have dअगरferent capabilites even when they have the same control रेजिस्टर
 * layouts. Provide an poपूर्णांक to vector control routine and provide any
 * per-bank configuration inक्रमmation that other प्रणालीs such as the
 * बाह्यal पूर्णांकerrupt code will need.
 *
 * @sa samsung_gpio_cfgpin
 * @sa s3c_gpio_अ_लोfg
 * @sa s3c_gpio_setpull
 * @sa s3c_gpio_getpull
 */
काष्ठा samsung_gpio_cfg अणु
	अचिन्हित पूर्णांक	cfg_eपूर्णांक;

	samsung_gpio_pull_t	(*get_pull)(काष्ठा samsung_gpio_chip *chip, अचिन्हित offs);
	पूर्णांक		(*set_pull)(काष्ठा samsung_gpio_chip *chip, अचिन्हित offs,
				    samsung_gpio_pull_t pull);

	अचिन्हित (*get_config)(काष्ठा samsung_gpio_chip *chip, अचिन्हित offs);
	पूर्णांक	 (*set_config)(काष्ठा samsung_gpio_chip *chip, अचिन्हित offs,
			       अचिन्हित config);
पूर्ण;

#घोषणा S3C_GPIO_SPECIAL_MARK	(0xfffffff0)
#घोषणा S3C_GPIO_SPECIAL(x)	(S3C_GPIO_SPECIAL_MARK | (x))

/* Defines क्रम generic pin configurations */
#घोषणा S3C_GPIO_INPUT	(S3C_GPIO_SPECIAL(0))
#घोषणा S3C_GPIO_OUTPUT	(S3C_GPIO_SPECIAL(1))
#घोषणा S3C_GPIO_SFN(x)	(S3C_GPIO_SPECIAL(x))

#घोषणा samsung_gpio_is_cfg_special(_cfg) \
	(((_cfg) & S3C_GPIO_SPECIAL_MARK) == S3C_GPIO_SPECIAL_MARK)

/**
 * s3c_gpio_cfgpin() - Change the GPIO function of a pin.
 * @pin pin The pin number to configure.
 * @to to The configuration क्रम the pin's function.
 *
 * Configure which function is actually connected to the बाह्यal
 * pin, such as an gpio input, output or some क्रमm of special function
 * connected to an पूर्णांकernal peripheral block.
 *
 * The @to parameter can be one of the generic S3C_GPIO_INPUT, S3C_GPIO_OUTPUT
 * or S3C_GPIO_SFN() to indicate one of the possible values that the helper
 * will then generate the correct bit mask and shअगरt क्रम the configuration.
 *
 * If a bank of GPIOs all needs to be set to special-function 2, then
 * the following code will work:
 *
 *	क्रम (gpio = start; gpio < end; gpio++)
 *		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
 *
 * The @to parameter can also be a specअगरic value alपढ़ोy shअगरted to the
 * correct position in the control रेजिस्टर, although these are discouraged
 * in newer kernels and are only being kept क्रम compatibility.
 */
बाह्य पूर्णांक s3c_gpio_cfgpin(अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक to);

/**
 * s3c_gpio_अ_लोfg - Read the current function क्रम a GPIO pin
 * @pin: The pin to पढ़ो the configuration value क्रम.
 *
 * Read the configuration state of the given @pin, वापसing a value that
 * could be passed back to s3c_gpio_cfgpin().
 *
 * @sa s3c_gpio_cfgpin
 */
बाह्य अचिन्हित s3c_gpio_अ_लोfg(अचिन्हित पूर्णांक pin);

/**
 * s3c_gpio_cfgpin_range() - Change the GPIO function क्रम configuring pin range
 * @start: The pin number to start at
 * @nr: The number of pins to configure from @start.
 * @cfg: The configuration क्रम the pin's function
 *
 * Call s3c_gpio_cfgpin() क्रम the @nr pins starting at @start.
 *
 * @sa s3c_gpio_cfgpin.
 */
बाह्य पूर्णांक s3c_gpio_cfgpin_range(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक nr,
				 अचिन्हित पूर्णांक cfg);

/* Define values क्रम the pull-अणुup,करोwnपूर्ण available क्रम each gpio pin.
 *
 * These values control the state of the weak pull-अणुup,करोwnपूर्ण resistors
 * available on most pins on the S3C series. Not all chips support both
 * up or करोwn settings, and it may be dependent on the chip that is being
 * used to whether the particular mode is available.
 */
#घोषणा S3C_GPIO_PULL_NONE	((__क्रमce samsung_gpio_pull_t)0x00)
#घोषणा S3C_GPIO_PULL_DOWN	((__क्रमce samsung_gpio_pull_t)0x01)
#घोषणा S3C_GPIO_PULL_UP	((__क्रमce samsung_gpio_pull_t)0x02)

/**
 * s3c_gpio_setpull() - set the state of a gpio pin pull resistor
 * @pin: The pin number to configure the pull resistor.
 * @pull: The configuration क्रम the pull resistor.
 *
 * This function sets the state of the pull-अणुup,करोwnपूर्ण resistor क्रम the
 * specअगरied pin. It will वापस 0 अगर successful, or a negative error
 * code अगर the pin cannot support the requested pull setting.
 *
 * @pull is one of S3C_GPIO_PULL_NONE, S3C_GPIO_PULL_DOWN or S3C_GPIO_PULL_UP.
*/
बाह्य पूर्णांक s3c_gpio_setpull(अचिन्हित पूर्णांक pin, samsung_gpio_pull_t pull);

/**
 * s3c_gpio_getpull() - get the pull resistor state of a gpio pin
 * @pin: The pin number to get the settings क्रम
 *
 * Read the pull resistor value क्रम the specअगरied pin.
*/
बाह्य samsung_gpio_pull_t s3c_gpio_getpull(अचिन्हित पूर्णांक pin);

/* configure `all` aspects of an gpio */

/**
 * s3c_gpio_cfgall_range() - configure range of gpio functtion and pull.
 * @start: The gpio number to start at.
 * @nr: The number of gpio to configure from @start.
 * @cfg: The configuration to use
 * @pull: The pull setting to use.
 *
 * Run s3c_gpio_cfgpin() and s3c_gpio_setpull() over the gpio range starting
 * @gpio and running क्रम @size.
 *
 * @sa s3c_gpio_cfgpin
 * @sa s3c_gpio_setpull
 * @sa s3c_gpio_cfgpin_range
 */
बाह्य पूर्णांक s3c_gpio_cfgall_range(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक nr,
				 अचिन्हित पूर्णांक cfg, samsung_gpio_pull_t pull);

अटल अंतरभूत पूर्णांक s3c_gpio_cfgrange_nopull(अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक size,
					   अचिन्हित पूर्णांक cfg)
अणु
	वापस s3c_gpio_cfgall_range(pin, size, cfg, S3C_GPIO_PULL_NONE);
पूर्ण

#पूर्ण_अगर /* __PLAT_GPIO_CFG_H */
