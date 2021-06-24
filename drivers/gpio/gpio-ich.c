<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Intel ICH6-10, Series 5 and 6, Atom C2000 (Avoton/Rangeley) GPIO driver
 *
 * Copyright (C) 2010 Extreme Engineering Solutions.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mfd/lpc_ich.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_NAME "gpio_ich"

/*
 * GPIO रेजिस्टर offsets in GPIO I/O space.
 * Each chunk of 32 GPIOs is manipulated via its own USE_SELx, IO_SELx, and
 * LVLx रेजिस्टरs.  Logic in the पढ़ो/ग_लिखो functions takes a रेजिस्टर and
 * an असलolute bit number and determines the proper रेजिस्टर offset and bit
 * number in that रेजिस्टर.  For example, to पढ़ो the value of GPIO bit 50
 * the code would access offset ichx_regs[2(=GPIO_LVL)][1(=50/32)],
 * bit 18 (50%32).
 */
क्रमागत GPIO_REG अणु
	GPIO_USE_SEL = 0,
	GPIO_IO_SEL,
	GPIO_LVL,
	GPO_BLINK
पूर्ण;

अटल स्थिर u8 ichx_regs[4][3] = अणु
	अणु0x00, 0x30, 0x40पूर्ण,	/* USE_SEL[1-3] offsets */
	अणु0x04, 0x34, 0x44पूर्ण,	/* IO_SEL[1-3] offsets */
	अणु0x0c, 0x38, 0x48पूर्ण,	/* LVL[1-3] offsets */
	अणु0x18, 0x18, 0x18पूर्ण,	/* BLINK offset */
पूर्ण;

अटल स्थिर u8 ichx_reglen[3] = अणु
	0x30, 0x10, 0x10,
पूर्ण;

अटल स्थिर u8 avoton_regs[4][3] = अणु
	अणु0x00, 0x80, 0x00पूर्ण,
	अणु0x04, 0x84, 0x00पूर्ण,
	अणु0x08, 0x88, 0x00पूर्ण,
पूर्ण;

अटल स्थिर u8 avoton_reglen[3] = अणु
	0x10, 0x10, 0x00,
पूर्ण;

#घोषणा ICHX_WRITE(val, reg, base_res)	outl(val, (reg) + (base_res)->start)
#घोषणा ICHX_READ(reg, base_res)	inl((reg) + (base_res)->start)

काष्ठा ichx_desc अणु
	/* Max GPIO pins the chipset can have */
	uपूर्णांक ngpio;

	/* chipset रेजिस्टरs */
	स्थिर u8 (*regs)[3];
	स्थिर u8 *reglen;

	/* GPO_BLINK is available on this chipset */
	bool have_blink;

	/* Whether the chipset has GPIO in GPE0_STS in the PM IO region */
	bool uses_gpe0;

	/* USE_SEL is bogus on some chipsets, eg 3100 */
	u32 use_sel_ignore[3];

	/* Some chipsets have quirks, let these use their own request/get */
	पूर्णांक (*request)(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset);
	पूर्णांक (*get)(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset);

	/*
	 * Some chipsets करोn't let पढ़ोing output values on GPIO_LVL रेजिस्टर
	 * this option allows driver caching written output values
	 */
	bool use_outlvl_cache;
पूर्ण;

अटल काष्ठा अणु
	spinlock_t lock;
	काष्ठा device *dev;
	काष्ठा gpio_chip chip;
	काष्ठा resource *gpio_base;	/* GPIO IO base */
	काष्ठा resource *pm_base;	/* Power Management IO base */
	काष्ठा ichx_desc *desc;	/* Poपूर्णांकer to chipset-specअगरic description */
	u32 orig_gpio_ctrl;	/* Orig CTRL value, used to restore on निकास */
	u8 use_gpio;		/* Which GPIO groups are usable */
	पूर्णांक outlvl_cache[3];	/* cached output values */
पूर्ण ichx_priv;

अटल पूर्णांक modparam_gpiobase = -1;	/* dynamic */
module_param_named(gpiobase, modparam_gpiobase, पूर्णांक, 0444);
MODULE_PARM_DESC(gpiobase, "The GPIO number base. -1 means dynamic, which is the default.");

अटल पूर्णांक ichx_ग_लिखो_bit(पूर्णांक reg, अचिन्हित पूर्णांक nr, पूर्णांक val, पूर्णांक verअगरy)
अणु
	अचिन्हित दीर्घ flags;
	u32 data, पंचांगp;
	पूर्णांक reg_nr = nr / 32;
	पूर्णांक bit = nr & 0x1f;

	spin_lock_irqsave(&ichx_priv.lock, flags);

	अगर (reg == GPIO_LVL && ichx_priv.desc->use_outlvl_cache)
		data = ichx_priv.outlvl_cache[reg_nr];
	अन्यथा
		data = ICHX_READ(ichx_priv.desc->regs[reg][reg_nr],
				 ichx_priv.gpio_base);

	अगर (val)
		data |= BIT(bit);
	अन्यथा
		data &= ~BIT(bit);
	ICHX_WRITE(data, ichx_priv.desc->regs[reg][reg_nr],
			 ichx_priv.gpio_base);
	अगर (reg == GPIO_LVL && ichx_priv.desc->use_outlvl_cache)
		ichx_priv.outlvl_cache[reg_nr] = data;

	पंचांगp = ICHX_READ(ichx_priv.desc->regs[reg][reg_nr],
			ichx_priv.gpio_base);

	spin_unlock_irqrestore(&ichx_priv.lock, flags);

	वापस (verअगरy && data != पंचांगp) ? -EPERM : 0;
पूर्ण

अटल पूर्णांक ichx_पढ़ो_bit(पूर्णांक reg, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित दीर्घ flags;
	u32 data;
	पूर्णांक reg_nr = nr / 32;
	पूर्णांक bit = nr & 0x1f;

	spin_lock_irqsave(&ichx_priv.lock, flags);

	data = ICHX_READ(ichx_priv.desc->regs[reg][reg_nr],
			 ichx_priv.gpio_base);

	अगर (reg == GPIO_LVL && ichx_priv.desc->use_outlvl_cache)
		data = ichx_priv.outlvl_cache[reg_nr] | data;

	spin_unlock_irqrestore(&ichx_priv.lock, flags);

	वापस !!(data & BIT(bit));
पूर्ण

अटल bool ichx_gpio_check_available(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr)
अणु
	वापस !!(ichx_priv.use_gpio & BIT(nr / 32));
पूर्ण

अटल पूर्णांक ichx_gpio_get_direction(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr)
अणु
	अगर (ichx_पढ़ो_bit(GPIO_IO_SEL, nr))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक ichx_gpio_direction_input(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr)
अणु
	/*
	 * Try setting pin as an input and verअगरy it worked since many pins
	 * are output-only.
	 */
	वापस ichx_ग_लिखो_bit(GPIO_IO_SEL, nr, 1, 1);
पूर्ण

अटल पूर्णांक ichx_gpio_direction_output(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr,
					पूर्णांक val)
अणु
	/* Disable blink hardware which is available क्रम GPIOs from 0 to 31. */
	अगर (nr < 32 && ichx_priv.desc->have_blink)
		ichx_ग_लिखो_bit(GPO_BLINK, nr, 0, 0);

	/* Set GPIO output value. */
	ichx_ग_लिखो_bit(GPIO_LVL, nr, val, 0);

	/*
	 * Try setting pin as an output and verअगरy it worked since many pins
	 * are input-only.
	 */
	वापस ichx_ग_लिखो_bit(GPIO_IO_SEL, nr, 0, 1);
पूर्ण

अटल पूर्णांक ichx_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक nr)
अणु
	वापस ichx_पढ़ो_bit(GPIO_LVL, nr);
पूर्ण

अटल पूर्णांक ich6_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित दीर्घ flags;
	u32 data;

	/*
	 * GPI 0 - 15 need to be पढ़ो from the घातer management रेजिस्टरs on
	 * a ICH6/3100 bridge.
	 */
	अगर (nr < 16) अणु
		अगर (!ichx_priv.pm_base)
			वापस -ENXIO;

		spin_lock_irqsave(&ichx_priv.lock, flags);

		/* GPI 0 - 15 are latched, ग_लिखो 1 to clear*/
		ICHX_WRITE(BIT(16 + nr), 0, ichx_priv.pm_base);
		data = ICHX_READ(0, ichx_priv.pm_base);

		spin_unlock_irqrestore(&ichx_priv.lock, flags);

		वापस !!((data >> 16) & BIT(nr));
	पूर्ण अन्यथा अणु
		वापस ichx_gpio_get(chip, nr);
	पूर्ण
पूर्ण

अटल पूर्णांक ichx_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक nr)
अणु
	अगर (!ichx_gpio_check_available(chip, nr))
		वापस -ENXIO;

	/*
	 * Note we assume the BIOS properly set a bridge's USE value.  Some
	 * chips (eg Intel 3100) have bogus USE values though, so first see अगर
	 * the chipset's USE value can be trusted क्रम this specअगरic bit.
	 * If it can't be trusted, assume that the pin can be used as a GPIO.
	 */
	अगर (ichx_priv.desc->use_sel_ignore[nr / 32] & BIT(nr & 0x1f))
		वापस 0;

	वापस ichx_पढ़ो_bit(GPIO_USE_SEL, nr) ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक ich6_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक nr)
अणु
	/*
	 * Fixups क्रम bits 16 and 17 are necessary on the Intel ICH6/3100
	 * bridge as they are controlled by USE रेजिस्टर bits 0 and 1.  See
	 * "Table 704 GPIO_USE_SEL1 register" in the i3100 datasheet क्रम
	 * additional info.
	 */
	अगर (nr == 16 || nr == 17)
		nr -= 16;

	वापस ichx_gpio_request(chip, nr);
पूर्ण

अटल व्योम ichx_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक nr, पूर्णांक val)
अणु
	ichx_ग_लिखो_bit(GPIO_LVL, nr, val, 0);
पूर्ण

अटल व्योम ichx_gpiolib_setup(काष्ठा gpio_chip *chip)
अणु
	chip->owner = THIS_MODULE;
	chip->label = DRV_NAME;
	chip->parent = ichx_priv.dev;

	/* Allow chip-specअगरic overrides of request()/get() */
	chip->request = ichx_priv.desc->request ?
		ichx_priv.desc->request : ichx_gpio_request;
	chip->get = ichx_priv.desc->get ?
		ichx_priv.desc->get : ichx_gpio_get;

	chip->set = ichx_gpio_set;
	chip->get_direction = ichx_gpio_get_direction;
	chip->direction_input = ichx_gpio_direction_input;
	chip->direction_output = ichx_gpio_direction_output;
	chip->base = modparam_gpiobase;
	chip->ngpio = ichx_priv.desc->ngpio;
	chip->can_sleep = false;
	chip->dbg_show = शून्य;
पूर्ण

/* ICH6-based, 631xesb-based */
अटल काष्ठा ichx_desc ich6_desc = अणु
	/* Bridges using the ICH6 controller need fixups क्रम GPIO 0 - 17 */
	.request = ich6_gpio_request,
	.get = ich6_gpio_get,

	/* GPIO 0-15 are पढ़ो in the GPE0_STS PM रेजिस्टर */
	.uses_gpe0 = true,

	.ngpio = 50,
	.have_blink = true,
	.regs = ichx_regs,
	.reglen = ichx_reglen,
पूर्ण;

/* Intel 3100 */
अटल काष्ठा ichx_desc i3100_desc = अणु
	/*
	 * Bits 16,17, 20 of USE_SEL and bit 16 of USE_SEL2 always पढ़ो 0 on
	 * the Intel 3100.  See "Table 712. GPIO Summary Table" of 3100
	 * Datasheet क्रम more info.
	 */
	.use_sel_ignore = अणु0x00130000, 0x00010000, 0x0पूर्ण,

	/* The 3100 needs fixups क्रम GPIO 0 - 17 */
	.request = ich6_gpio_request,
	.get = ich6_gpio_get,

	/* GPIO 0-15 are पढ़ो in the GPE0_STS PM रेजिस्टर */
	.uses_gpe0 = true,

	.ngpio = 50,
	.regs = ichx_regs,
	.reglen = ichx_reglen,
पूर्ण;

/* ICH7 and ICH8-based */
अटल काष्ठा ichx_desc ich7_desc = अणु
	.ngpio = 50,
	.have_blink = true,
	.regs = ichx_regs,
	.reglen = ichx_reglen,
पूर्ण;

/* ICH9-based */
अटल काष्ठा ichx_desc ich9_desc = अणु
	.ngpio = 61,
	.have_blink = true,
	.regs = ichx_regs,
	.reglen = ichx_reglen,
पूर्ण;

/* ICH10-based - Consumer/corporate versions have dअगरferent amount of GPIO */
अटल काष्ठा ichx_desc ich10_cons_desc = अणु
	.ngpio = 61,
	.have_blink = true,
	.regs = ichx_regs,
	.reglen = ichx_reglen,
पूर्ण;
अटल काष्ठा ichx_desc ich10_corp_desc = अणु
	.ngpio = 72,
	.have_blink = true,
	.regs = ichx_regs,
	.reglen = ichx_reglen,
पूर्ण;

/* Intel 5 series, 6 series, 3400 series, and C200 series */
अटल काष्ठा ichx_desc पूर्णांकel5_desc = अणु
	.ngpio = 76,
	.regs = ichx_regs,
	.reglen = ichx_reglen,
पूर्ण;

/* Avoton */
अटल काष्ठा ichx_desc avoton_desc = अणु
	/* Avoton has only 59 GPIOs, but we assume the first set of रेजिस्टर
	 * (Core) has 32 instead of 31 to keep gpio-ich compliance
	 */
	.ngpio = 60,
	.regs = avoton_regs,
	.reglen = avoton_reglen,
	.use_outlvl_cache = true,
पूर्ण;

अटल पूर्णांक ichx_gpio_request_regions(काष्ठा device *dev,
	काष्ठा resource *res_base, स्थिर अक्षर *name, u8 use_gpio)
अणु
	पूर्णांक i;

	अगर (!res_base || !res_base->start || !res_base->end)
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(ichx_priv.desc->regs[0]); i++) अणु
		अगर (!(use_gpio & BIT(i)))
			जारी;
		अगर (!devm_request_region(dev,
				res_base->start + ichx_priv.desc->regs[0][i],
				ichx_priv.desc->reglen[i], name))
			वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ichx_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा lpc_ich_info *ich_info = dev_get_platdata(dev);
	काष्ठा resource *res_base, *res_pm;
	पूर्णांक err;

	अगर (!ich_info)
		वापस -ENODEV;

	चयन (ich_info->gpio_version) अणु
	हाल ICH_I3100_GPIO:
		ichx_priv.desc = &i3100_desc;
		अवरोध;
	हाल ICH_V5_GPIO:
		ichx_priv.desc = &पूर्णांकel5_desc;
		अवरोध;
	हाल ICH_V6_GPIO:
		ichx_priv.desc = &ich6_desc;
		अवरोध;
	हाल ICH_V7_GPIO:
		ichx_priv.desc = &ich7_desc;
		अवरोध;
	हाल ICH_V9_GPIO:
		ichx_priv.desc = &ich9_desc;
		अवरोध;
	हाल ICH_V10CORP_GPIO:
		ichx_priv.desc = &ich10_corp_desc;
		अवरोध;
	हाल ICH_V10CONS_GPIO:
		ichx_priv.desc = &ich10_cons_desc;
		अवरोध;
	हाल AVOTON_GPIO:
		ichx_priv.desc = &avoton_desc;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ichx_priv.dev = dev;
	spin_lock_init(&ichx_priv.lock);

	res_base = platक्रमm_get_resource(pdev, IORESOURCE_IO, ICH_RES_GPIO);
	err = ichx_gpio_request_regions(dev, res_base, pdev->name,
					ich_info->use_gpio);
	अगर (err)
		वापस err;

	ichx_priv.gpio_base = res_base;
	ichx_priv.use_gpio = ich_info->use_gpio;

	/*
	 * If necessary, determine the I/O address of ACPI/घातer management
	 * रेजिस्टरs which are needed to पढ़ो the GPE0 रेजिस्टर क्रम GPI pins
	 * 0 - 15 on some chipsets.
	 */
	अगर (!ichx_priv.desc->uses_gpe0)
		जाओ init;

	res_pm = platक्रमm_get_resource(pdev, IORESOURCE_IO, ICH_RES_GPE0);
	अगर (!res_pm) अणु
		dev_warn(dev, "ACPI BAR is unavailable, GPI 0 - 15 unavailable\n");
		जाओ init;
	पूर्ण

	अगर (!devm_request_region(dev, res_pm->start, resource_size(res_pm),
				 pdev->name)) अणु
		dev_warn(dev, "ACPI BAR is busy, GPI 0 - 15 unavailable\n");
		जाओ init;
	पूर्ण

	ichx_priv.pm_base = res_pm;

init:
	ichx_gpiolib_setup(&ichx_priv.chip);
	err = gpiochip_add_data(&ichx_priv.chip, शून्य);
	अगर (err) अणु
		dev_err(dev, "Failed to register GPIOs\n");
		वापस err;
	पूर्ण

	dev_info(dev, "GPIO from %d to %d\n", ichx_priv.chip.base,
		 ichx_priv.chip.base + ichx_priv.chip.ngpio - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक ichx_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	gpiochip_हटाओ(&ichx_priv.chip);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ichx_gpio_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
	.probe		= ichx_gpio_probe,
	.हटाओ		= ichx_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(ichx_gpio_driver);

MODULE_AUTHOR("Peter Tyser <ptyser@xes-inc.com>");
MODULE_DESCRIPTION("GPIO interface for Intel ICH series");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:"DRV_NAME);
