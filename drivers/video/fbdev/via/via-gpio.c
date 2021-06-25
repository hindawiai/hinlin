<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम viafb GPIO ports.
 *
 * Copyright 2009 Jonathan Corbet <corbet@lwn.net>
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/via-core.h>
#समावेश <linux/via-gpपन.स>
#समावेश <linux/export.h>

/*
 * The ports we know about.  Note that the port-25 gpios are not
 * mentioned in the datasheet.
 */

काष्ठा viafb_gpio अणु
	अक्षर *vg_name;	/* Data sheet name */
	u16 vg_io_port;
	u8  vg_port_index;
	पूर्णांक  vg_mask_shअगरt;
पूर्ण;

अटल काष्ठा viafb_gpio viafb_all_gpios[] = अणु
	अणु
		.vg_name = "VGPIO0",  /* Guess - not in datasheet */
		.vg_io_port = VIASR,
		.vg_port_index = 0x25,
		.vg_mask_shअगरt = 1
	पूर्ण,
	अणु
		.vg_name = "VGPIO1",
		.vg_io_port = VIASR,
		.vg_port_index = 0x25,
		.vg_mask_shअगरt = 0
	पूर्ण,
	अणु
		.vg_name = "VGPIO2",  /* aka DISPCLKI0 */
		.vg_io_port = VIASR,
		.vg_port_index = 0x2c,
		.vg_mask_shअगरt = 1
	पूर्ण,
	अणु
		.vg_name = "VGPIO3",  /* aka DISPCLKO0 */
		.vg_io_port = VIASR,
		.vg_port_index = 0x2c,
		.vg_mask_shअगरt = 0
	पूर्ण,
	अणु
		.vg_name = "VGPIO4",  /* DISPCLKI1 */
		.vg_io_port = VIASR,
		.vg_port_index = 0x3d,
		.vg_mask_shअगरt = 1
	पूर्ण,
	अणु
		.vg_name = "VGPIO5",  /* DISPCLKO1 */
		.vg_io_port = VIASR,
		.vg_port_index = 0x3d,
		.vg_mask_shअगरt = 0
	पूर्ण,
पूर्ण;

#घोषणा VIAFB_NUM_GPIOS ARRAY_SIZE(viafb_all_gpios)

/*
 * This काष्ठाure controls the active GPIOs, which may be a subset
 * of those which are known.
 */

काष्ठा viafb_gpio_cfg अणु
	काष्ठा gpio_chip gpio_chip;
	काष्ठा viafb_dev *vdev;
	काष्ठा viafb_gpio *active_gpios[VIAFB_NUM_GPIOS];
	स्थिर अक्षर *gpio_names[VIAFB_NUM_GPIOS];
पूर्ण;

/*
 * GPIO access functions
 */
अटल व्योम via_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक nr,
			 पूर्णांक value)
अणु
	काष्ठा viafb_gpio_cfg *cfg = gpiochip_get_data(chip);
	u8 reg;
	काष्ठा viafb_gpio *gpio;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cfg->vdev->reg_lock, flags);
	gpio = cfg->active_gpios[nr];
	reg = via_पढ़ो_reg(VIASR, gpio->vg_port_index);
	reg |= 0x40 << gpio->vg_mask_shअगरt;  /* output enable */
	अगर (value)
		reg |= 0x10 << gpio->vg_mask_shअगरt;
	अन्यथा
		reg &= ~(0x10 << gpio->vg_mask_shअगरt);
	via_ग_लिखो_reg(VIASR, gpio->vg_port_index, reg);
	spin_unlock_irqrestore(&cfg->vdev->reg_lock, flags);
पूर्ण

अटल पूर्णांक via_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक nr,
			    पूर्णांक value)
अणु
	via_gpio_set(chip, nr, value);
	वापस 0;
पूर्ण

/*
 * Set the input direction.  I'm not sure this is right; we should
 * be able to करो input without disabling output.
 */
अटल पूर्णांक via_gpio_dir_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा viafb_gpio_cfg *cfg = gpiochip_get_data(chip);
	काष्ठा viafb_gpio *gpio;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cfg->vdev->reg_lock, flags);
	gpio = cfg->active_gpios[nr];
	via_ग_लिखो_reg_mask(VIASR, gpio->vg_port_index, 0,
			0x40 << gpio->vg_mask_shअगरt);
	spin_unlock_irqrestore(&cfg->vdev->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक via_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा viafb_gpio_cfg *cfg = gpiochip_get_data(chip);
	u8 reg;
	काष्ठा viafb_gpio *gpio;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cfg->vdev->reg_lock, flags);
	gpio = cfg->active_gpios[nr];
	reg = via_पढ़ो_reg(VIASR, gpio->vg_port_index);
	spin_unlock_irqrestore(&cfg->vdev->reg_lock, flags);
	वापस !!(reg & (0x04 << gpio->vg_mask_shअगरt));
पूर्ण


अटल काष्ठा viafb_gpio_cfg viafb_gpio_config = अणु
	.gpio_chip = अणु
		.label = "VIAFB onboard GPIO",
		.owner = THIS_MODULE,
		.direction_output = via_gpio_dir_out,
		.set = via_gpio_set,
		.direction_input = via_gpio_dir_input,
		.get = via_gpio_get,
		.base = -1,
		.ngpio = 0,
		.can_sleep = 0
	पूर्ण
पूर्ण;

/*
 * Manage the software enable bit.
 */
अटल व्योम viafb_gpio_enable(काष्ठा viafb_gpio *gpio)
अणु
	via_ग_लिखो_reg_mask(VIASR, gpio->vg_port_index, 0x02, 0x02);
पूर्ण

अटल व्योम viafb_gpio_disable(काष्ठा viafb_gpio *gpio)
अणु
	via_ग_लिखो_reg_mask(VIASR, gpio->vg_port_index, 0, 0x02);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक viafb_gpio_suspend(व्योम *निजी)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक viafb_gpio_resume(व्योम *निजी)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < viafb_gpio_config.gpio_chip.ngpio; i += 2)
		viafb_gpio_enable(viafb_gpio_config.active_gpios[i]);
	वापस 0;
पूर्ण

अटल काष्ठा viafb_pm_hooks viafb_gpio_pm_hooks = अणु
	.suspend = viafb_gpio_suspend,
	.resume = viafb_gpio_resume
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM */

/*
 * Look up a specअगरic gpio and वापस the number it was asचिन्हित.
 */
पूर्णांक viafb_gpio_lookup(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < viafb_gpio_config.gpio_chip.ngpio; i++)
		अगर (!म_भेद(name, viafb_gpio_config.active_gpios[i]->vg_name))
			वापस viafb_gpio_config.gpio_chip.base + i;
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(viafb_gpio_lookup);

/*
 * Platक्रमm device stuff.
 */
अटल पूर्णांक viafb_gpio_probe(काष्ठा platक्रमm_device *platdev)
अणु
	काष्ठा viafb_dev *vdev = platdev->dev.platक्रमm_data;
	काष्ठा via_port_cfg *port_cfg = vdev->port_cfg;
	पूर्णांक i, ngpio = 0, ret;
	काष्ठा viafb_gpio *gpio;
	अचिन्हित दीर्घ flags;

	/*
	 * Set up entries क्रम all GPIOs which have been configured to
	 * operate as such (as opposed to as i2c ports).
	 */
	क्रम (i = 0; i < VIAFB_NUM_PORTS; i++) अणु
		अगर (port_cfg[i].mode != VIA_MODE_GPIO)
			जारी;
		क्रम (gpio = viafb_all_gpios;
		     gpio < viafb_all_gpios + VIAFB_NUM_GPIOS; gpio++)
			अगर (gpio->vg_port_index == port_cfg[i].ioport_index) अणु
				viafb_gpio_config.active_gpios[ngpio] = gpio;
				viafb_gpio_config.gpio_names[ngpio] =
					gpio->vg_name;
				ngpio++;
			पूर्ण
	पूर्ण
	viafb_gpio_config.gpio_chip.ngpio = ngpio;
	viafb_gpio_config.gpio_chip.names = viafb_gpio_config.gpio_names;
	viafb_gpio_config.vdev = vdev;
	अगर (ngpio == 0) अणु
		prपूर्णांकk(KERN_INFO "viafb: no GPIOs configured\n");
		वापस 0;
	पूर्ण
	/*
	 * Enable the ports.  They come in pairs, with a single
	 * enable bit क्रम both.
	 */
	spin_lock_irqsave(&viafb_gpio_config.vdev->reg_lock, flags);
	क्रम (i = 0; i < ngpio; i += 2)
		viafb_gpio_enable(viafb_gpio_config.active_gpios[i]);
	spin_unlock_irqrestore(&viafb_gpio_config.vdev->reg_lock, flags);
	/*
	 * Get रेजिस्टरed.
	 */
	viafb_gpio_config.gpio_chip.base = -1;  /* Dynamic */
	ret = gpiochip_add_data(&viafb_gpio_config.gpio_chip,
				&viafb_gpio_config);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "viafb: failed to add gpios (%d)\n", ret);
		viafb_gpio_config.gpio_chip.ngpio = 0;
	पूर्ण
#अगर_घोषित CONFIG_PM
	viafb_pm_रेजिस्टर(&viafb_gpio_pm_hooks);
#पूर्ण_अगर
	वापस ret;
पूर्ण


अटल पूर्णांक viafb_gpio_हटाओ(काष्ठा platक्रमm_device *platdev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

#अगर_घोषित CONFIG_PM
	viafb_pm_unरेजिस्टर(&viafb_gpio_pm_hooks);
#पूर्ण_अगर

	/*
	 * Get unरेजिस्टरed.
	 */
	अगर (viafb_gpio_config.gpio_chip.ngpio > 0) अणु
		gpiochip_हटाओ(&viafb_gpio_config.gpio_chip);
	पूर्ण
	/*
	 * Disable the ports.
	 */
	spin_lock_irqsave(&viafb_gpio_config.vdev->reg_lock, flags);
	क्रम (i = 0; i < viafb_gpio_config.gpio_chip.ngpio; i += 2)
		viafb_gpio_disable(viafb_gpio_config.active_gpios[i]);
	viafb_gpio_config.gpio_chip.ngpio = 0;
	spin_unlock_irqrestore(&viafb_gpio_config.vdev->reg_lock, flags);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver via_gpio_driver = अणु
	.driver = अणु
		.name = "viafb-gpio",
	पूर्ण,
	.probe = viafb_gpio_probe,
	.हटाओ = viafb_gpio_हटाओ,
पूर्ण;

पूर्णांक viafb_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&via_gpio_driver);
पूर्ण

व्योम viafb_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&via_gpio_driver);
पूर्ण
