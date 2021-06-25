<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Samsung Platक्रमm - GPIO pin configuration helper definitions
 */

/* This is meant क्रम core cpu support, machine or other driver files
 * should not be including this header.
 */

#अगर_अघोषित __PLAT_GPIO_CFG_HELPERS_H
#घोषणा __PLAT_GPIO_CFG_HELPERS_H __खाता__

/* As a note, all gpio configuration functions are entered exclusively, either
 * with the relevant lock held or the प्रणाली prevented from करोing anything अन्यथा
 * by disabling पूर्णांकerrupts.
*/

अटल अंतरभूत पूर्णांक samsung_gpio_करो_setcfg(काष्ठा samsung_gpio_chip *chip,
					 अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक config)
अणु
	वापस (chip->config->set_config)(chip, off, config);
पूर्ण

अटल अंतरभूत अचिन्हित samsung_gpio_करो_अ_लोfg(काष्ठा samsung_gpio_chip *chip,
					      अचिन्हित पूर्णांक off)
अणु
	वापस (chip->config->get_config)(chip, off);
पूर्ण

अटल अंतरभूत पूर्णांक samsung_gpio_करो_setpull(काष्ठा samsung_gpio_chip *chip,
					  अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull)
अणु
	वापस (chip->config->set_pull)(chip, off, pull);
पूर्ण

अटल अंतरभूत samsung_gpio_pull_t samsung_gpio_करो_getpull(काष्ठा samsung_gpio_chip *chip,
							  अचिन्हित पूर्णांक off)
अणु
	वापस chip->config->get_pull(chip, off);
पूर्ण

/* Pull-अणुup,करोwnपूर्ण resistor controls.
 *
 * S3C2410,S3C2440 = Pull-UP,
 * S3C2412,S3C2413 = Pull-Down
 * S3C6400,S3C6410 = Pull-Both [None,Down,Up,Undef]
 * S3C2443 = Pull-Both [not same as S3C6400]
 */

/**
 * s3c24xx_gpio_setpull_1up() - Pull configuration क्रम choice of up or none.
 * @chip: The gpio chip that is being configured.
 * @off: The offset क्रम the GPIO being configured.
 * @param: pull: The pull mode being requested.
 *
 * This is a helper function क्रम the हाल where we have GPIOs with one
 * bit configuring the presence of a pull-up resistor.
 */
बाह्य पूर्णांक s3c24xx_gpio_setpull_1up(काष्ठा samsung_gpio_chip *chip,
				    अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull);

/**
 * s3c24xx_gpio_setpull_1करोwn() - Pull configuration क्रम choice of करोwn or none
 * @chip: The gpio chip that is being configured
 * @off: The offset क्रम the GPIO being configured
 * @param: pull: The pull mode being requested
 *
 * This is a helper function क्रम the हाल where we have GPIOs with one
 * bit configuring the presence of a pull-करोwn resistor.
 */
बाह्य पूर्णांक s3c24xx_gpio_setpull_1करोwn(काष्ठा samsung_gpio_chip *chip,
				      अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull);

/**
 * samsung_gpio_setpull_uघातn() - Pull configuration क्रम choice of up,
 * करोwn or none
 *
 * @chip: The gpio chip that is being configured.
 * @off: The offset क्रम the GPIO being configured.
 * @param: pull: The pull mode being requested.
 *
 * This is a helper function क्रम the हाल where we have GPIOs with two
 * bits configuring the presence of a pull resistor, in the following
 * order:
 *	00 = No pull resistor connected
 *	01 = Pull-up resistor connected
 *	10 = Pull-करोwn resistor connected
 */
बाह्य पूर्णांक samsung_gpio_setpull_upकरोwn(काष्ठा samsung_gpio_chip *chip,
				       अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull);

/**
 * samsung_gpio_getpull_upकरोwn() - Get configuration क्रम choice of up,
 * करोwn or none
 *
 * @chip: The gpio chip that the GPIO pin beदीर्घs to
 * @off: The offset to the pin to get the configuration of.
 *
 * This helper function पढ़ोs the state of the pull-अणुup,करोwnपूर्ण resistor
 * क्रम the given GPIO in the same हाल as samsung_gpio_setpull_uघातn.
*/
बाह्य samsung_gpio_pull_t samsung_gpio_getpull_upकरोwn(काष्ठा samsung_gpio_chip *chip,
						       अचिन्हित पूर्णांक off);

/**
 * s3c24xx_gpio_getpull_1up() - Get configuration क्रम choice of up or none
 * @chip: The gpio chip that the GPIO pin beदीर्घs to
 * @off: The offset to the pin to get the configuration of.
 *
 * This helper function पढ़ोs the state of the pull-up resistor क्रम the
 * given GPIO in the same हाल as s3c24xx_gpio_setpull_1up.
*/
बाह्य samsung_gpio_pull_t s3c24xx_gpio_getpull_1up(काष्ठा samsung_gpio_chip *chip,
						    अचिन्हित पूर्णांक off);

/**
 * s3c24xx_gpio_getpull_1करोwn() - Get configuration क्रम choice of करोwn or none
 * @chip: The gpio chip that the GPIO pin beदीर्घs to
 * @off: The offset to the pin to get the configuration of.
 *
 * This helper function पढ़ोs the state of the pull-करोwn resistor क्रम the
 * given GPIO in the same हाल as s3c24xx_gpio_setpull_1करोwn.
*/
बाह्य samsung_gpio_pull_t s3c24xx_gpio_getpull_1करोwn(काष्ठा samsung_gpio_chip *chip,
						      अचिन्हित पूर्णांक off);

/**
 * s3c2443_gpio_setpull() - Pull configuration क्रम s3c2443.
 * @chip: The gpio chip that is being configured.
 * @off: The offset क्रम the GPIO being configured.
 * @param: pull: The pull mode being requested.
 *
 * This is a helper function क्रम the हाल where we have GPIOs with two
 * bits configuring the presence of a pull resistor, in the following
 * order:
 *	00 = Pull-up resistor connected
 *	10 = Pull-करोwn resistor connected
 *	x1 = No pull up resistor
 */
बाह्य पूर्णांक s3c2443_gpio_setpull(काष्ठा samsung_gpio_chip *chip,
				अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull);

/**
 * s3c2443_gpio_getpull() - Get configuration क्रम s3c2443 pull resistors
 * @chip: The gpio chip that the GPIO pin beदीर्घs to.
 * @off: The offset to the pin to get the configuration of.
 *
 * This helper function पढ़ोs the state of the pull-अणुup,करोwnपूर्ण resistor क्रम the
 * given GPIO in the same हाल as samsung_gpio_setpull_uघातn.
*/
बाह्य samsung_gpio_pull_t s3c2443_gpio_getpull(काष्ठा samsung_gpio_chip *chip,
						अचिन्हित पूर्णांक off);

#पूर्ण_अगर /* __PLAT_GPIO_CFG_HELPERS_H */
