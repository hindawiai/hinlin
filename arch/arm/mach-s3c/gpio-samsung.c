<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2009-2011 Samsung Electronics Co., Ltd.
//		http://www.samsung.com/
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//      Ben Dooks <ben@simtec.co.uk>
//      http://armlinux.simtec.co.uk/
//
// Samsung - GPIOlib support

#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/irq.h>

#समावेश <mach/irqs.h>
#समावेश "map.h"
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "cpu.h"
#समावेश "gpio-core.h"
#समावेश "gpio-cfg.h"
#समावेश "gpio-cfg-helpers.h"
#समावेश "pm.h"

पूर्णांक samsung_gpio_setpull_upकरोwn(काष्ठा samsung_gpio_chip *chip,
				अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull)
अणु
	व्योम __iomem *reg = chip->base + 0x08;
	पूर्णांक shअगरt = off * 2;
	u32 pup;

	pup = __raw_पढ़ोl(reg);
	pup &= ~(3 << shअगरt);
	pup |= pull << shअगरt;
	__raw_ग_लिखोl(pup, reg);

	वापस 0;
पूर्ण

samsung_gpio_pull_t samsung_gpio_getpull_upकरोwn(काष्ठा samsung_gpio_chip *chip,
						अचिन्हित पूर्णांक off)
अणु
	व्योम __iomem *reg = chip->base + 0x08;
	पूर्णांक shअगरt = off * 2;
	u32 pup = __raw_पढ़ोl(reg);

	pup >>= shअगरt;
	pup &= 0x3;

	वापस (__क्रमce samsung_gpio_pull_t)pup;
पूर्ण

पूर्णांक s3c2443_gpio_setpull(काष्ठा samsung_gpio_chip *chip,
			 अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull)
अणु
	चयन (pull) अणु
	हाल S3C_GPIO_PULL_NONE:
		pull = 0x01;
		अवरोध;
	हाल S3C_GPIO_PULL_UP:
		pull = 0x00;
		अवरोध;
	हाल S3C_GPIO_PULL_DOWN:
		pull = 0x02;
		अवरोध;
	पूर्ण
	वापस samsung_gpio_setpull_upकरोwn(chip, off, pull);
पूर्ण

samsung_gpio_pull_t s3c2443_gpio_getpull(काष्ठा samsung_gpio_chip *chip,
					 अचिन्हित पूर्णांक off)
अणु
	samsung_gpio_pull_t pull;

	pull = samsung_gpio_getpull_upकरोwn(chip, off);

	चयन (pull) अणु
	हाल 0x00:
		pull = S3C_GPIO_PULL_UP;
		अवरोध;
	हाल 0x01:
	हाल 0x03:
		pull = S3C_GPIO_PULL_NONE;
		अवरोध;
	हाल 0x02:
		pull = S3C_GPIO_PULL_DOWN;
		अवरोध;
	पूर्ण

	वापस pull;
पूर्ण

अटल पूर्णांक s3c24xx_gpio_setpull_1(काष्ठा samsung_gpio_chip *chip,
				  अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull,
				  samsung_gpio_pull_t upकरोwn)
अणु
	व्योम __iomem *reg = chip->base + 0x08;
	u32 pup = __raw_पढ़ोl(reg);

	अगर (pull == upकरोwn)
		pup &= ~(1 << off);
	अन्यथा अगर (pull == S3C_GPIO_PULL_NONE)
		pup |= (1 << off);
	अन्यथा
		वापस -EINVAL;

	__raw_ग_लिखोl(pup, reg);
	वापस 0;
पूर्ण

अटल samsung_gpio_pull_t s3c24xx_gpio_getpull_1(काष्ठा samsung_gpio_chip *chip,
						  अचिन्हित पूर्णांक off,
						  samsung_gpio_pull_t upकरोwn)
अणु
	व्योम __iomem *reg = chip->base + 0x08;
	u32 pup = __raw_पढ़ोl(reg);

	pup &= (1 << off);
	वापस pup ? S3C_GPIO_PULL_NONE : upकरोwn;
पूर्ण

samsung_gpio_pull_t s3c24xx_gpio_getpull_1up(काष्ठा samsung_gpio_chip *chip,
					     अचिन्हित पूर्णांक off)
अणु
	वापस s3c24xx_gpio_getpull_1(chip, off, S3C_GPIO_PULL_UP);
पूर्ण

पूर्णांक s3c24xx_gpio_setpull_1up(काष्ठा samsung_gpio_chip *chip,
			     अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull)
अणु
	वापस s3c24xx_gpio_setpull_1(chip, off, pull, S3C_GPIO_PULL_UP);
पूर्ण

samsung_gpio_pull_t s3c24xx_gpio_getpull_1करोwn(काष्ठा samsung_gpio_chip *chip,
					       अचिन्हित पूर्णांक off)
अणु
	वापस s3c24xx_gpio_getpull_1(chip, off, S3C_GPIO_PULL_DOWN);
पूर्ण

पूर्णांक s3c24xx_gpio_setpull_1करोwn(काष्ठा samsung_gpio_chip *chip,
			       अचिन्हित पूर्णांक off, samsung_gpio_pull_t pull)
अणु
	वापस s3c24xx_gpio_setpull_1(chip, off, pull, S3C_GPIO_PULL_DOWN);
पूर्ण

/*
 * samsung_gpio_setcfg_2bit - Samsung 2bit style GPIO configuration.
 * @chip: The gpio chip that is being configured.
 * @off: The offset क्रम the GPIO being configured.
 * @cfg: The configuration value to set.
 *
 * This helper deal with the GPIO हालs where the control रेजिस्टर
 * has two bits of configuration per gpio, which have the following
 * functions:
 *	00 = input
 *	01 = output
 *	1x = special function
 */

अटल पूर्णांक samsung_gpio_setcfg_2bit(काष्ठा samsung_gpio_chip *chip,
				    अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक cfg)
अणु
	व्योम __iomem *reg = chip->base;
	अचिन्हित पूर्णांक shअगरt = off * 2;
	u32 con;

	अगर (samsung_gpio_is_cfg_special(cfg)) अणु
		cfg &= 0xf;
		अगर (cfg > 3)
			वापस -EINVAL;

		cfg <<= shअगरt;
	पूर्ण

	con = __raw_पढ़ोl(reg);
	con &= ~(0x3 << shअगरt);
	con |= cfg;
	__raw_ग_लिखोl(con, reg);

	वापस 0;
पूर्ण

/*
 * samsung_gpio_अ_लोfg_2bit - Samsung 2bit style GPIO configuration पढ़ो.
 * @chip: The gpio chip that is being configured.
 * @off: The offset क्रम the GPIO being configured.
 *
 * The reverse of samsung_gpio_setcfg_2bit(). Will वापस a value which
 * could be directly passed back to samsung_gpio_setcfg_2bit(), from the
 * S3C_GPIO_SPECIAL() macro.
 */

अटल अचिन्हित पूर्णांक samsung_gpio_अ_लोfg_2bit(काष्ठा samsung_gpio_chip *chip,
					     अचिन्हित पूर्णांक off)
अणु
	u32 con;

	con = __raw_पढ़ोl(chip->base);
	con >>= off * 2;
	con &= 3;

	/* this conversion works क्रम IN and OUT as well as special mode */
	वापस S3C_GPIO_SPECIAL(con);
पूर्ण

/*
 * samsung_gpio_setcfg_4bit - Samsung 4bit single रेजिस्टर GPIO config.
 * @chip: The gpio chip that is being configured.
 * @off: The offset क्रम the GPIO being configured.
 * @cfg: The configuration value to set.
 *
 * This helper deal with the GPIO हालs where the control रेजिस्टर has 4 bits
 * of control per GPIO, generally in the क्रमm of:
 *	0000 = Input
 *	0001 = Output
 *	others = Special functions (dependent on bank)
 *
 * Note, since the code to deal with the हाल where there are two control
 * रेजिस्टरs instead of one, we करो not have a separate set of functions क्रम
 * each हाल.
 */

अटल पूर्णांक samsung_gpio_setcfg_4bit(काष्ठा samsung_gpio_chip *chip,
				    अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक cfg)
अणु
	व्योम __iomem *reg = chip->base;
	अचिन्हित पूर्णांक shअगरt = (off & 7) * 4;
	u32 con;

	अगर (off < 8 && chip->chip.ngpio > 8)
		reg -= 4;

	अगर (samsung_gpio_is_cfg_special(cfg)) अणु
		cfg &= 0xf;
		cfg <<= shअगरt;
	पूर्ण

	con = __raw_पढ़ोl(reg);
	con &= ~(0xf << shअगरt);
	con |= cfg;
	__raw_ग_लिखोl(con, reg);

	वापस 0;
पूर्ण

/*
 * samsung_gpio_अ_लोfg_4bit - Samsung 4bit single रेजिस्टर GPIO config पढ़ो.
 * @chip: The gpio chip that is being configured.
 * @off: The offset क्रम the GPIO being configured.
 *
 * The reverse of samsung_gpio_setcfg_4bit(), turning a gpio configuration
 * रेजिस्टर setting पूर्णांकo a value the software can use, such as could be passed
 * to samsung_gpio_setcfg_4bit().
 *
 * @sa samsung_gpio_अ_लोfg_2bit
 */

अटल अचिन्हित samsung_gpio_अ_लोfg_4bit(काष्ठा samsung_gpio_chip *chip,
					 अचिन्हित पूर्णांक off)
अणु
	व्योम __iomem *reg = chip->base;
	अचिन्हित पूर्णांक shअगरt = (off & 7) * 4;
	u32 con;

	अगर (off < 8 && chip->chip.ngpio > 8)
		reg -= 4;

	con = __raw_पढ़ोl(reg);
	con >>= shअगरt;
	con &= 0xf;

	/* this conversion works क्रम IN and OUT as well as special mode */
	वापस S3C_GPIO_SPECIAL(con);
पूर्ण

#अगर_घोषित CONFIG_PLAT_S3C24XX
/*
 * s3c24xx_gpio_setcfg_abank - S3C24XX style GPIO configuration (Bank A)
 * @chip: The gpio chip that is being configured.
 * @off: The offset क्रम the GPIO being configured.
 * @cfg: The configuration value to set.
 *
 * This helper deal with the GPIO हालs where the control रेजिस्टर
 * has one bit of configuration क्रम the gpio, where setting the bit
 * means the pin is in special function mode and unset means output.
 */

अटल पूर्णांक s3c24xx_gpio_setcfg_abank(काष्ठा samsung_gpio_chip *chip,
				     अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक cfg)
अणु
	व्योम __iomem *reg = chip->base;
	अचिन्हित पूर्णांक shअगरt = off;
	u32 con;

	अगर (samsung_gpio_is_cfg_special(cfg)) अणु
		cfg &= 0xf;

		/* Map output to 0, and SFN2 to 1 */
		cfg -= 1;
		अगर (cfg > 1)
			वापस -EINVAL;

		cfg <<= shअगरt;
	पूर्ण

	con = __raw_पढ़ोl(reg);
	con &= ~(0x1 << shअगरt);
	con |= cfg;
	__raw_ग_लिखोl(con, reg);

	वापस 0;
पूर्ण

/*
 * s3c24xx_gpio_अ_लोfg_abank - S3C24XX style GPIO configuration पढ़ो (Bank A)
 * @chip: The gpio chip that is being configured.
 * @off: The offset क्रम the GPIO being configured.
 *
 * The reverse of s3c24xx_gpio_setcfg_abank() turning an GPIO पूर्णांकo a usable
 * GPIO configuration value.
 *
 * @sa samsung_gpio_अ_लोfg_2bit
 * @sa samsung_gpio_अ_लोfg_4bit
 */

अटल अचिन्हित s3c24xx_gpio_अ_लोfg_abank(काष्ठा samsung_gpio_chip *chip,
					  अचिन्हित पूर्णांक off)
अणु
	u32 con;

	con = __raw_पढ़ोl(chip->base);
	con >>= off;
	con &= 1;
	con++;

	वापस S3C_GPIO_SFN(con);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init samsung_gpiolib_set_cfg(काष्ठा samsung_gpio_cfg *chipcfg,
					   पूर्णांक nr_chips)
अणु
	क्रम (; nr_chips > 0; nr_chips--, chipcfg++) अणु
		अगर (!chipcfg->set_config)
			chipcfg->set_config = samsung_gpio_setcfg_4bit;
		अगर (!chipcfg->get_config)
			chipcfg->get_config = samsung_gpio_अ_लोfg_4bit;
		अगर (!chipcfg->set_pull)
			chipcfg->set_pull = samsung_gpio_setpull_upकरोwn;
		अगर (!chipcfg->get_pull)
			chipcfg->get_pull = samsung_gpio_getpull_upकरोwn;
	पूर्ण
पूर्ण

काष्ठा samsung_gpio_cfg s3c24xx_gpiocfg_शेष = अणु
	.set_config	= samsung_gpio_setcfg_2bit,
	.get_config	= samsung_gpio_अ_लोfg_2bit,
पूर्ण;

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल काष्ठा samsung_gpio_cfg s3c24xx_gpiocfg_banka = अणु
	.set_config	= s3c24xx_gpio_setcfg_abank,
	.get_config	= s3c24xx_gpio_अ_लोfg_abank,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा samsung_gpio_cfg samsung_gpio_cfgs[] = अणु
	[0] = अणु
		.cfg_eपूर्णांक	= 0x0,
	पूर्ण,
	[1] = अणु
		.cfg_eपूर्णांक	= 0x3,
	पूर्ण,
	[2] = अणु
		.cfg_eपूर्णांक	= 0x7,
	पूर्ण,
	[3] = अणु
		.cfg_eपूर्णांक	= 0xF,
	पूर्ण,
	[4] = अणु
		.cfg_eपूर्णांक	= 0x0,
		.set_config	= samsung_gpio_setcfg_2bit,
		.get_config	= samsung_gpio_अ_लोfg_2bit,
	पूर्ण,
	[5] = अणु
		.cfg_eपूर्णांक	= 0x2,
		.set_config	= samsung_gpio_setcfg_2bit,
		.get_config	= samsung_gpio_अ_लोfg_2bit,
	पूर्ण,
	[6] = अणु
		.cfg_eपूर्णांक	= 0x3,
		.set_config	= samsung_gpio_setcfg_2bit,
		.get_config	= samsung_gpio_अ_लोfg_2bit,
	पूर्ण,
	[7] = अणु
		.set_config	= samsung_gpio_setcfg_2bit,
		.get_config	= samsung_gpio_अ_लोfg_2bit,
	पूर्ण,
पूर्ण;

/*
 * Default routines क्रम controlling GPIO, based on the original S3C24XX
 * GPIO functions which deal with the हाल where each gpio bank of the
 * chip is as following:
 *
 * base + 0x00: Control रेजिस्टर, 2 bits per gpio
 *	        gpio n: 2 bits starting at (2*n)
 *		00 = input, 01 = output, others mean special-function
 * base + 0x04: Data रेजिस्टर, 1 bit per gpio
 *		bit n: data bit n
*/

अटल पूर्णांक samsung_gpiolib_2bit_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा samsung_gpio_chip *ourchip = to_samsung_gpio(chip);
	व्योम __iomem *base = ourchip->base;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ con;

	samsung_gpio_lock(ourchip, flags);

	con = __raw_पढ़ोl(base + 0x00);
	con &= ~(3 << (offset * 2));

	__raw_ग_लिखोl(con, base + 0x00);

	samsung_gpio_unlock(ourchip, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक samsung_gpiolib_2bit_output(काष्ठा gpio_chip *chip,
				       अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा samsung_gpio_chip *ourchip = to_samsung_gpio(chip);
	व्योम __iomem *base = ourchip->base;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ dat;
	अचिन्हित दीर्घ con;

	samsung_gpio_lock(ourchip, flags);

	dat = __raw_पढ़ोl(base + 0x04);
	dat &= ~(1 << offset);
	अगर (value)
		dat |= 1 << offset;
	__raw_ग_लिखोl(dat, base + 0x04);

	con = __raw_पढ़ोl(base + 0x00);
	con &= ~(3 << (offset * 2));
	con |= 1 << (offset * 2);

	__raw_ग_लिखोl(con, base + 0x00);
	__raw_ग_लिखोl(dat, base + 0x04);

	samsung_gpio_unlock(ourchip, flags);
	वापस 0;
पूर्ण

/*
 * The samsung_gpiolib_4bit routines are to control the gpio banks where
 * the gpio configuration रेजिस्टर (GPxCON) has 4 bits per GPIO, as the
 * following example:
 *
 * base + 0x00: Control रेजिस्टर, 4 bits per gpio
 *		gpio n: 4 bits starting at (4*n)
 *		0000 = input, 0001 = output, others mean special-function
 * base + 0x04: Data रेजिस्टर, 1 bit per gpio
 *		bit n: data bit n
 *
 * Note, since the data रेजिस्टर is one bit per gpio and is at base + 0x4
 * we can use samsung_gpiolib_get and samsung_gpiolib_set to change the
 * state of the output.
 */

अटल पूर्णांक samsung_gpiolib_4bit_input(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा samsung_gpio_chip *ourchip = to_samsung_gpio(chip);
	व्योम __iomem *base = ourchip->base;
	अचिन्हित दीर्घ con;

	con = __raw_पढ़ोl(base + GPIOCON_OFF);
	अगर (ourchip->biपंचांगap_gpio_पूर्णांक & BIT(offset))
		con |= 0xf << con_4bit_shअगरt(offset);
	अन्यथा
		con &= ~(0xf << con_4bit_shअगरt(offset));
	__raw_ग_लिखोl(con, base + GPIOCON_OFF);

	pr_debug("%s: %p: CON now %08lx\n", __func__, base, con);

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_gpiolib_4bit_output(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा samsung_gpio_chip *ourchip = to_samsung_gpio(chip);
	व्योम __iomem *base = ourchip->base;
	अचिन्हित दीर्घ con;
	अचिन्हित दीर्घ dat;

	con = __raw_पढ़ोl(base + GPIOCON_OFF);
	con &= ~(0xf << con_4bit_shअगरt(offset));
	con |= 0x1 << con_4bit_shअगरt(offset);

	dat = __raw_पढ़ोl(base + GPIODAT_OFF);

	अगर (value)
		dat |= 1 << offset;
	अन्यथा
		dat &= ~(1 << offset);

	__raw_ग_लिखोl(dat, base + GPIODAT_OFF);
	__raw_ग_लिखोl(con, base + GPIOCON_OFF);
	__raw_ग_लिखोl(dat, base + GPIODAT_OFF);

	pr_debug("%s: %p: CON %08lx, DAT %08lx\n", __func__, base, con, dat);

	वापस 0;
पूर्ण

/*
 * The next set of routines are क्रम the हाल where the GPIO configuration
 * रेजिस्टरs are 4 bits per GPIO but there is more than one रेजिस्टर (the
 * bank has more than 8 GPIOs.
 *
 * This हाल is the similar to the 4 bit हाल, but the रेजिस्टरs are as
 * follows:
 *
 * base + 0x00: Control रेजिस्टर, 4 bits per gpio (lower 8 GPIOs)
 *		gpio n: 4 bits starting at (4*n)
 *		0000 = input, 0001 = output, others mean special-function
 * base + 0x04: Control रेजिस्टर, 4 bits per gpio (up to 8 additions GPIOs)
 *		gpio n: 4 bits starting at (4*n)
 *		0000 = input, 0001 = output, others mean special-function
 * base + 0x08: Data रेजिस्टर, 1 bit per gpio
 *		bit n: data bit n
 *
 * To allow us to use the samsung_gpiolib_get and samsung_gpiolib_set
 * routines we store the 'base + 0x4' address so that these routines see
 * the data रेजिस्टर at ourchip->base + 0x04.
 */

अटल पूर्णांक samsung_gpiolib_4bit2_input(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा samsung_gpio_chip *ourchip = to_samsung_gpio(chip);
	व्योम __iomem *base = ourchip->base;
	व्योम __iomem *regcon = base;
	अचिन्हित दीर्घ con;

	अगर (offset > 7)
		offset -= 8;
	अन्यथा
		regcon -= 4;

	con = __raw_पढ़ोl(regcon);
	con &= ~(0xf << con_4bit_shअगरt(offset));
	__raw_ग_लिखोl(con, regcon);

	pr_debug("%s: %p: CON %08lx\n", __func__, base, con);

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_gpiolib_4bit2_output(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा samsung_gpio_chip *ourchip = to_samsung_gpio(chip);
	व्योम __iomem *base = ourchip->base;
	व्योम __iomem *regcon = base;
	अचिन्हित दीर्घ con;
	अचिन्हित दीर्घ dat;
	अचिन्हित con_offset = offset;

	अगर (con_offset > 7)
		con_offset -= 8;
	अन्यथा
		regcon -= 4;

	con = __raw_पढ़ोl(regcon);
	con &= ~(0xf << con_4bit_shअगरt(con_offset));
	con |= 0x1 << con_4bit_shअगरt(con_offset);

	dat = __raw_पढ़ोl(base + GPIODAT_OFF);

	अगर (value)
		dat |= 1 << offset;
	अन्यथा
		dat &= ~(1 << offset);

	__raw_ग_लिखोl(dat, base + GPIODAT_OFF);
	__raw_ग_लिखोl(con, regcon);
	__raw_ग_लिखोl(dat, base + GPIODAT_OFF);

	pr_debug("%s: %p: CON %08lx, DAT %08lx\n", __func__, base, con, dat);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PLAT_S3C24XX
/* The next set of routines are क्रम the हाल of s3c24xx bank a */

अटल पूर्णांक s3c24xx_gpiolib_banka_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक s3c24xx_gpiolib_banka_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा samsung_gpio_chip *ourchip = to_samsung_gpio(chip);
	व्योम __iomem *base = ourchip->base;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ dat;
	अचिन्हित दीर्घ con;

	local_irq_save(flags);

	con = __raw_पढ़ोl(base + 0x00);
	dat = __raw_पढ़ोl(base + 0x04);

	dat &= ~(1 << offset);
	अगर (value)
		dat |= 1 << offset;

	__raw_ग_लिखोl(dat, base + 0x04);

	con &= ~(1 << offset);

	__raw_ग_लिखोl(con, base + 0x00);
	__raw_ग_लिखोl(dat, base + 0x04);

	local_irq_restore(flags);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम samsung_gpiolib_set(काष्ठा gpio_chip *chip,
				अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा samsung_gpio_chip *ourchip = to_samsung_gpio(chip);
	व्योम __iomem *base = ourchip->base;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ dat;

	samsung_gpio_lock(ourchip, flags);

	dat = __raw_पढ़ोl(base + 0x04);
	dat &= ~(1 << offset);
	अगर (value)
		dat |= 1 << offset;
	__raw_ग_लिखोl(dat, base + 0x04);

	samsung_gpio_unlock(ourchip, flags);
पूर्ण

अटल पूर्णांक samsung_gpiolib_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा samsung_gpio_chip *ourchip = to_samsung_gpio(chip);
	अचिन्हित दीर्घ val;

	val = __raw_पढ़ोl(ourchip->base + 0x04);
	val >>= offset;
	val &= 1;

	वापस val;
पूर्ण

/*
 * CONFIG_S3C_GPIO_TRACK enables the tracking of the s3c specअगरic gpios
 * क्रम use with the configuration calls, and other parts of the s3c gpiolib
 * support code.
 *
 * Not all s3c support code will need this, as some configurations of cpu
 * may only support one or two dअगरferent configuration options and have an
 * easy gpio to samsung_gpio_chip mapping function. If this is the हाल, then
 * the machine support file should provide its own samsung_gpiolib_अ_लोhip()
 * and any other necessary functions.
 */

#अगर_घोषित CONFIG_S3C_GPIO_TRACK
काष्ठा samsung_gpio_chip *s3c_gpios[S3C_GPIO_END];

अटल __init व्योम s3c_gpiolib_track(काष्ठा samsung_gpio_chip *chip)
अणु
	अचिन्हित पूर्णांक gpn;
	पूर्णांक i;

	gpn = chip->chip.base;
	क्रम (i = 0; i < chip->chip.ngpio; i++, gpn++) अणु
		BUG_ON(gpn >= ARRAY_SIZE(s3c_gpios));
		s3c_gpios[gpn] = chip;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_GPIO_TRACK */

/*
 * samsung_gpiolib_add() - add the Samsung gpio_chip.
 * @chip: The chip to रेजिस्टर
 *
 * This is a wrapper to gpiochip_add() that takes our specअगरic gpio chip
 * inक्रमmation and makes the necessary alterations क्रम the platक्रमm and
 * notes the inक्रमmation क्रम use with the configuration प्रणालीs and any
 * other parts of the प्रणाली.
 */

अटल व्योम __init samsung_gpiolib_add(काष्ठा samsung_gpio_chip *chip)
अणु
	काष्ठा gpio_chip *gc = &chip->chip;
	पूर्णांक ret;

	BUG_ON(!chip->base);
	BUG_ON(!gc->label);
	BUG_ON(!gc->ngpio);

	spin_lock_init(&chip->lock);

	अगर (!gc->direction_input)
		gc->direction_input = samsung_gpiolib_2bit_input;
	अगर (!gc->direction_output)
		gc->direction_output = samsung_gpiolib_2bit_output;
	अगर (!gc->set)
		gc->set = samsung_gpiolib_set;
	अगर (!gc->get)
		gc->get = samsung_gpiolib_get;

#अगर_घोषित CONFIG_PM
	अगर (chip->pm != शून्य) अणु
		अगर (!chip->pm->save || !chip->pm->resume)
			pr_err("gpio: %s has missing PM functions\n",
			       gc->label);
	पूर्ण अन्यथा
		pr_err("gpio: %s has no PM function\n", gc->label);
#पूर्ण_अगर

	/* gpiochip_add() prपूर्णांकs own failure message on error. */
	ret = gpiochip_add_data(gc, chip);
	अगर (ret >= 0)
		s3c_gpiolib_track(chip);
पूर्ण

अटल व्योम __init s3c24xx_gpiolib_add_chips(काष्ठा samsung_gpio_chip *chip,
					     पूर्णांक nr_chips, व्योम __iomem *base)
अणु
	पूर्णांक i;
	काष्ठा gpio_chip *gc = &chip->chip;

	क्रम (i = 0 ; i < nr_chips; i++, chip++) अणु
		/* skip banks not present on SoC */
		अगर (chip->chip.base >= S3C_GPIO_END)
			जारी;

		अगर (!chip->config)
			chip->config = &s3c24xx_gpiocfg_शेष;
		अगर (!chip->pm)
			chip->pm = __gpio_pm(&samsung_gpio_pm_2bit);
		अगर ((base != शून्य) && (chip->base == शून्य))
			chip->base = base + ((i) * 0x10);

		अगर (!gc->direction_input)
			gc->direction_input = samsung_gpiolib_2bit_input;
		अगर (!gc->direction_output)
			gc->direction_output = samsung_gpiolib_2bit_output;

		samsung_gpiolib_add(chip);
	पूर्ण
पूर्ण

अटल व्योम __init samsung_gpiolib_add_2bit_chips(काष्ठा samsung_gpio_chip *chip,
						  पूर्णांक nr_chips, व्योम __iomem *base,
						  अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < nr_chips; i++, chip++) अणु
		chip->chip.direction_input = samsung_gpiolib_2bit_input;
		chip->chip.direction_output = samsung_gpiolib_2bit_output;

		अगर (!chip->config)
			chip->config = &samsung_gpio_cfgs[7];
		अगर (!chip->pm)
			chip->pm = __gpio_pm(&samsung_gpio_pm_2bit);
		अगर ((base != शून्य) && (chip->base == शून्य))
			chip->base = base + ((i) * offset);

		samsung_gpiolib_add(chip);
	पूर्ण
पूर्ण

/*
 * samsung_gpiolib_add_4bit_chips - 4bit single रेजिस्टर GPIO config.
 * @chip: The gpio chip that is being configured.
 * @nr_chips: The no of chips (gpio ports) क्रम the GPIO being configured.
 *
 * This helper deal with the GPIO हालs where the control रेजिस्टर has 4 bits
 * of control per GPIO, generally in the क्रमm of:
 * 0000 = Input
 * 0001 = Output
 * others = Special functions (dependent on bank)
 *
 * Note, since the code to deal with the हाल where there are two control
 * रेजिस्टरs instead of one, we करो not have a separate set of function
 * (samsung_gpiolib_add_4bit2_chips)क्रम each हाल.
 */

अटल व्योम __init samsung_gpiolib_add_4bit_chips(काष्ठा samsung_gpio_chip *chip,
						  पूर्णांक nr_chips, व्योम __iomem *base)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < nr_chips; i++, chip++) अणु
		chip->chip.direction_input = samsung_gpiolib_4bit_input;
		chip->chip.direction_output = samsung_gpiolib_4bit_output;

		अगर (!chip->config)
			chip->config = &samsung_gpio_cfgs[2];
		अगर (!chip->pm)
			chip->pm = __gpio_pm(&samsung_gpio_pm_4bit);
		अगर ((base != शून्य) && (chip->base == शून्य))
			chip->base = base + ((i) * 0x20);

		chip->biपंचांगap_gpio_पूर्णांक = 0;

		samsung_gpiolib_add(chip);
	पूर्ण
पूर्ण

अटल व्योम __init samsung_gpiolib_add_4bit2_chips(काष्ठा samsung_gpio_chip *chip,
						   पूर्णांक nr_chips)
अणु
	क्रम (; nr_chips > 0; nr_chips--, chip++) अणु
		chip->chip.direction_input = samsung_gpiolib_4bit2_input;
		chip->chip.direction_output = samsung_gpiolib_4bit2_output;

		अगर (!chip->config)
			chip->config = &samsung_gpio_cfgs[2];
		अगर (!chip->pm)
			chip->pm = __gpio_pm(&samsung_gpio_pm_4bit);

		samsung_gpiolib_add(chip);
	पूर्ण
पूर्ण

पूर्णांक samsung_gpiolib_to_irq(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा samsung_gpio_chip *samsung_chip = gpiochip_get_data(chip);

	वापस samsung_chip->irq_base + offset;
पूर्ण

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल पूर्णांक s3c24xx_gpiolib_fbank_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अगर (offset < 4) अणु
		अगर (soc_is_s3c2412())
			वापस IRQ_EINT0_2412 + offset;
		अन्यथा
			वापस IRQ_EINT0 + offset;
	पूर्ण

	अगर (offset < 8)
		वापस IRQ_EINT4 + offset - 4;

	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_S3C64XX
अटल पूर्णांक s3c64xx_gpiolib_mbank_to_irq(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	वापस pin < 5 ? IRQ_EINT(23) + pin : -ENXIO;
पूर्ण

अटल पूर्णांक s3c64xx_gpiolib_lbank_to_irq(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	वापस pin >= 8 ? IRQ_EINT(16) + pin - 8 : -ENXIO;
पूर्ण
#पूर्ण_अगर

काष्ठा samsung_gpio_chip s3c24xx_gpios[] = अणु
#अगर_घोषित CONFIG_PLAT_S3C24XX
	अणु
		.config	= &s3c24xx_gpiocfg_banka,
		.chip	= अणु
			.base			= S3C2410_GPA(0),
			.owner			= THIS_MODULE,
			.label			= "GPIOA",
			.ngpio			= 27,
			.direction_input	= s3c24xx_gpiolib_banka_input,
			.direction_output	= s3c24xx_gpiolib_banka_output,
		पूर्ण,
	पूर्ण, अणु
		.chip	= अणु
			.base	= S3C2410_GPB(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOB",
			.ngpio	= 11,
		पूर्ण,
	पूर्ण, अणु
		.chip	= अणु
			.base	= S3C2410_GPC(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOC",
			.ngpio	= 16,
		पूर्ण,
	पूर्ण, अणु
		.chip	= अणु
			.base	= S3C2410_GPD(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOD",
			.ngpio	= 16,
		पूर्ण,
	पूर्ण, अणु
		.chip	= अणु
			.base	= S3C2410_GPE(0),
			.label	= "GPIOE",
			.owner	= THIS_MODULE,
			.ngpio	= 16,
		पूर्ण,
	पूर्ण, अणु
		.chip	= अणु
			.base	= S3C2410_GPF(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOF",
			.ngpio	= 8,
			.to_irq	= s3c24xx_gpiolib_fbank_to_irq,
		पूर्ण,
	पूर्ण, अणु
		.irq_base = IRQ_EINT8,
		.chip	= अणु
			.base	= S3C2410_GPG(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOG",
			.ngpio	= 16,
			.to_irq	= samsung_gpiolib_to_irq,
		पूर्ण,
	पूर्ण, अणु
		.chip	= अणु
			.base	= S3C2410_GPH(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOH",
			.ngpio	= 15,
		पूर्ण,
	पूर्ण,
		/* GPIOS क्रम the S3C2443 and later devices. */
	अणु
		.base	= S3C2440_GPJCON,
		.chip	= अणु
			.base	= S3C2410_GPJ(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOJ",
			.ngpio	= 16,
		पूर्ण,
	पूर्ण, अणु
		.base	= S3C2443_GPKCON,
		.chip	= अणु
			.base	= S3C2410_GPK(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOK",
			.ngpio	= 16,
		पूर्ण,
	पूर्ण, अणु
		.base	= S3C2443_GPLCON,
		.chip	= अणु
			.base	= S3C2410_GPL(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOL",
			.ngpio	= 15,
		पूर्ण,
	पूर्ण, अणु
		.base	= S3C2443_GPMCON,
		.chip	= अणु
			.base	= S3C2410_GPM(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOM",
			.ngpio	= 2,
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

/*
 * GPIO bank summary:
 *
 * Bank	GPIOs	Style	SlpCon	ExtInt Group
 * A	8	4Bit	Yes	1
 * B	7	4Bit	Yes	1
 * C	8	4Bit	Yes	2
 * D	5	4Bit	Yes	3
 * E	5	4Bit	Yes	None
 * F	16	2Bit	Yes	4 [1]
 * G	7	4Bit	Yes	5
 * H	10	4Bit[2]	Yes	6
 * I	16	2Bit	Yes	None
 * J	12	2Bit	Yes	None
 * K	16	4Bit[2]	No	None
 * L	15	4Bit[2] No	None
 * M	6	4Bit	No	IRQ_EINT
 * N	16	2Bit	No	IRQ_EINT
 * O	16	2Bit	Yes	7
 * P	15	2Bit	Yes	8
 * Q	9	2Bit	Yes	9
 *
 * [1] BANKF pins 14,15 करो not क्रमm part of the बाह्यal पूर्णांकerrupt sources
 * [2] BANK has two control रेजिस्टरs, GPxCON0 and GPxCON1
 */

अटल काष्ठा samsung_gpio_chip s3c64xx_gpios_4bit[] = अणु
#अगर_घोषित CONFIG_ARCH_S3C64XX
	अणु
		.chip	= अणु
			.base	= S3C64XX_GPA(0),
			.ngpio	= S3C64XX_GPIO_A_NR,
			.label	= "GPA",
		पूर्ण,
	पूर्ण, अणु
		.chip	= अणु
			.base	= S3C64XX_GPB(0),
			.ngpio	= S3C64XX_GPIO_B_NR,
			.label	= "GPB",
		पूर्ण,
	पूर्ण, अणु
		.chip	= अणु
			.base	= S3C64XX_GPC(0),
			.ngpio	= S3C64XX_GPIO_C_NR,
			.label	= "GPC",
		पूर्ण,
	पूर्ण, अणु
		.chip	= अणु
			.base	= S3C64XX_GPD(0),
			.ngpio	= S3C64XX_GPIO_D_NR,
			.label	= "GPD",
		पूर्ण,
	पूर्ण, अणु
		.config	= &samsung_gpio_cfgs[0],
		.chip	= अणु
			.base	= S3C64XX_GPE(0),
			.ngpio	= S3C64XX_GPIO_E_NR,
			.label	= "GPE",
		पूर्ण,
	पूर्ण, अणु
		.base	= S3C64XX_GPG_BASE,
		.chip	= अणु
			.base	= S3C64XX_GPG(0),
			.ngpio	= S3C64XX_GPIO_G_NR,
			.label	= "GPG",
		पूर्ण,
	पूर्ण, अणु
		.base	= S3C64XX_GPM_BASE,
		.config	= &samsung_gpio_cfgs[1],
		.chip	= अणु
			.base	= S3C64XX_GPM(0),
			.ngpio	= S3C64XX_GPIO_M_NR,
			.label	= "GPM",
			.to_irq = s3c64xx_gpiolib_mbank_to_irq,
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा samsung_gpio_chip s3c64xx_gpios_4bit2[] = अणु
#अगर_घोषित CONFIG_ARCH_S3C64XX
	अणु
		.base	= S3C64XX_GPH_BASE + 0x4,
		.chip	= अणु
			.base	= S3C64XX_GPH(0),
			.ngpio	= S3C64XX_GPIO_H_NR,
			.label	= "GPH",
		पूर्ण,
	पूर्ण, अणु
		.base	= S3C64XX_GPK_BASE + 0x4,
		.config	= &samsung_gpio_cfgs[0],
		.chip	= अणु
			.base	= S3C64XX_GPK(0),
			.ngpio	= S3C64XX_GPIO_K_NR,
			.label	= "GPK",
		पूर्ण,
	पूर्ण, अणु
		.base	= S3C64XX_GPL_BASE + 0x4,
		.config	= &samsung_gpio_cfgs[1],
		.chip	= अणु
			.base	= S3C64XX_GPL(0),
			.ngpio	= S3C64XX_GPIO_L_NR,
			.label	= "GPL",
			.to_irq = s3c64xx_gpiolib_lbank_to_irq,
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा samsung_gpio_chip s3c64xx_gpios_2bit[] = अणु
#अगर_घोषित CONFIG_ARCH_S3C64XX
	अणु
		.base	= S3C64XX_GPF_BASE,
		.config	= &samsung_gpio_cfgs[6],
		.chip	= अणु
			.base	= S3C64XX_GPF(0),
			.ngpio	= S3C64XX_GPIO_F_NR,
			.label	= "GPF",
		पूर्ण,
	पूर्ण, अणु
		.config	= &samsung_gpio_cfgs[7],
		.chip	= अणु
			.base	= S3C64XX_GPI(0),
			.ngpio	= S3C64XX_GPIO_I_NR,
			.label	= "GPI",
		पूर्ण,
	पूर्ण, अणु
		.config	= &samsung_gpio_cfgs[7],
		.chip	= अणु
			.base	= S3C64XX_GPJ(0),
			.ngpio	= S3C64XX_GPIO_J_NR,
			.label	= "GPJ",
		पूर्ण,
	पूर्ण, अणु
		.config	= &samsung_gpio_cfgs[6],
		.chip	= अणु
			.base	= S3C64XX_GPO(0),
			.ngpio	= S3C64XX_GPIO_O_NR,
			.label	= "GPO",
		पूर्ण,
	पूर्ण, अणु
		.config	= &samsung_gpio_cfgs[6],
		.chip	= अणु
			.base	= S3C64XX_GPP(0),
			.ngpio	= S3C64XX_GPIO_P_NR,
			.label	= "GPP",
		पूर्ण,
	पूर्ण, अणु
		.config	= &samsung_gpio_cfgs[6],
		.chip	= अणु
			.base	= S3C64XX_GPQ(0),
			.ngpio	= S3C64XX_GPIO_Q_NR,
			.label	= "GPQ",
		पूर्ण,
	पूर्ण, अणु
		.base	= S3C64XX_GPN_BASE,
		.irq_base = IRQ_EINT(0),
		.config	= &samsung_gpio_cfgs[5],
		.chip	= अणु
			.base	= S3C64XX_GPN(0),
			.ngpio	= S3C64XX_GPIO_N_NR,
			.label	= "GPN",
			.to_irq = samsung_gpiolib_to_irq,
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

/* TODO: cleanup soc_is_* */
अटल __init पूर्णांक samsung_gpiolib_init(व्योम)
अणु
	/*
	 * Currently there are two drivers that can provide GPIO support क्रम
	 * Samsung SoCs. For device tree enabled platक्रमms, the new
	 * pinctrl-samsung driver is used, providing both GPIO and pin control
	 * पूर्णांकerfaces. For legacy (non-DT) platक्रमms this driver is used.
	 */
	अगर (of_have_populated_dt())
		वापस 0;

	अगर (soc_is_s3c24xx()) अणु
		samsung_gpiolib_set_cfg(samsung_gpio_cfgs,
				ARRAY_SIZE(samsung_gpio_cfgs));
		s3c24xx_gpiolib_add_chips(s3c24xx_gpios,
				ARRAY_SIZE(s3c24xx_gpios), S3C24XX_VA_GPIO);
	पूर्ण अन्यथा अगर (soc_is_s3c64xx()) अणु
		samsung_gpiolib_set_cfg(samsung_gpio_cfgs,
				ARRAY_SIZE(samsung_gpio_cfgs));
		samsung_gpiolib_add_2bit_chips(s3c64xx_gpios_2bit,
				ARRAY_SIZE(s3c64xx_gpios_2bit),
				S3C64XX_VA_GPIO + 0xE0, 0x20);
		samsung_gpiolib_add_4bit_chips(s3c64xx_gpios_4bit,
				ARRAY_SIZE(s3c64xx_gpios_4bit),
				S3C64XX_VA_GPIO);
		samsung_gpiolib_add_4bit2_chips(s3c64xx_gpios_4bit2,
				ARRAY_SIZE(s3c64xx_gpios_4bit2));
	पूर्ण

	वापस 0;
पूर्ण
core_initcall(samsung_gpiolib_init);

पूर्णांक s3c_gpio_cfgpin(अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक config)
अणु
	काष्ठा samsung_gpio_chip *chip = samsung_gpiolib_अ_लोhip(pin);
	अचिन्हित दीर्घ flags;
	पूर्णांक offset;
	पूर्णांक ret;

	अगर (!chip)
		वापस -EINVAL;

	offset = pin - chip->chip.base;

	samsung_gpio_lock(chip, flags);
	ret = samsung_gpio_करो_setcfg(chip, offset, config);
	samsung_gpio_unlock(chip, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(s3c_gpio_cfgpin);

पूर्णांक s3c_gpio_cfgpin_range(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक nr,
			  अचिन्हित पूर्णांक cfg)
अणु
	पूर्णांक ret;

	क्रम (; nr > 0; nr--, start++) अणु
		ret = s3c_gpio_cfgpin(start, cfg);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s3c_gpio_cfgpin_range);

पूर्णांक s3c_gpio_cfgall_range(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक nr,
			  अचिन्हित पूर्णांक cfg, samsung_gpio_pull_t pull)
अणु
	पूर्णांक ret;

	क्रम (; nr > 0; nr--, start++) अणु
		s3c_gpio_setpull(start, pull);
		ret = s3c_gpio_cfgpin(start, cfg);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s3c_gpio_cfgall_range);

अचिन्हित s3c_gpio_अ_लोfg(अचिन्हित पूर्णांक pin)
अणु
	काष्ठा samsung_gpio_chip *chip = samsung_gpiolib_अ_लोhip(pin);
	अचिन्हित दीर्घ flags;
	अचिन्हित ret = 0;
	पूर्णांक offset;

	अगर (chip) अणु
		offset = pin - chip->chip.base;

		samsung_gpio_lock(chip, flags);
		ret = samsung_gpio_करो_अ_लोfg(chip, offset);
		samsung_gpio_unlock(chip, flags);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(s3c_gpio_अ_लोfg);

पूर्णांक s3c_gpio_setpull(अचिन्हित पूर्णांक pin, samsung_gpio_pull_t pull)
अणु
	काष्ठा samsung_gpio_chip *chip = samsung_gpiolib_अ_लोhip(pin);
	अचिन्हित दीर्घ flags;
	पूर्णांक offset, ret;

	अगर (!chip)
		वापस -EINVAL;

	offset = pin - chip->chip.base;

	samsung_gpio_lock(chip, flags);
	ret = samsung_gpio_करो_setpull(chip, offset, pull);
	samsung_gpio_unlock(chip, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(s3c_gpio_setpull);

samsung_gpio_pull_t s3c_gpio_getpull(अचिन्हित पूर्णांक pin)
अणु
	काष्ठा samsung_gpio_chip *chip = samsung_gpiolib_अ_लोhip(pin);
	अचिन्हित दीर्घ flags;
	पूर्णांक offset;
	u32 pup = 0;

	अगर (chip) अणु
		offset = pin - chip->chip.base;

		samsung_gpio_lock(chip, flags);
		pup = samsung_gpio_करो_getpull(chip, offset);
		samsung_gpio_unlock(chip, flags);
	पूर्ण

	वापस (__क्रमce samsung_gpio_pull_t)pup;
पूर्ण
EXPORT_SYMBOL(s3c_gpio_getpull);

#अगर_घोषित CONFIG_PLAT_S3C24XX
अचिन्हित पूर्णांक s3c2410_modअगरy_misccr(अचिन्हित पूर्णांक clear, अचिन्हित पूर्णांक change)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ misccr;

	local_irq_save(flags);
	misccr = __raw_पढ़ोl(S3C24XX_MISCCR);
	misccr &= ~clear;
	misccr ^= change;
	__raw_ग_लिखोl(misccr, S3C24XX_MISCCR);
	local_irq_restore(flags);

	वापस misccr;
पूर्ण
EXPORT_SYMBOL(s3c2410_modअगरy_misccr);
#पूर्ण_अगर
