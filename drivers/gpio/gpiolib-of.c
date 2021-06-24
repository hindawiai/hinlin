<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * OF helpers क्रम the GPIO API
 *
 * Copyright (c) 2007-2008  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/machine.h>

#समावेश "gpiolib.h"
#समावेश "gpiolib-of.h"

/**
 * of_gpio_spi_cs_get_count() - special GPIO counting क्रम SPI
 * @dev:    Consuming device
 * @con_id: Function within the GPIO consumer
 *
 * Some elder GPIO controllers need special quirks. Currently we handle
 * the Freescale and PPC GPIO controller with bindings that करोesn't use the
 * established "cs-gpios" क्रम chip selects but instead rely on
 * "gpios" क्रम the chip select lines. If we detect this, we redirect
 * the counting of "cs-gpios" to count "gpios" transparent to the
 * driver.
 */
अटल पूर्णांक of_gpio_spi_cs_get_count(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	काष्ठा device_node *np = dev->of_node;

	अगर (!IS_ENABLED(CONFIG_SPI_MASTER))
		वापस 0;
	अगर (!con_id || म_भेद(con_id, "cs"))
		वापस 0;
	अगर (!of_device_is_compatible(np, "fsl,spi") &&
	    !of_device_is_compatible(np, "aeroflexgaisler,spictrl") &&
	    !of_device_is_compatible(np, "ibm,ppc4xx-spi"))
		वापस 0;
	वापस of_gpio_named_count(np, "gpios");
पूर्ण

/*
 * This is used by बाह्यal users of of_gpio_count() from <linux/of_gpपन.स>
 *
 * FIXME: get rid of those बाह्यal users by converting them to GPIO
 * descriptors and let them all use gpiod_count()
 */
पूर्णांक of_gpio_get_count(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	पूर्णांक ret;
	अक्षर propname[32];
	अचिन्हित पूर्णांक i;

	ret = of_gpio_spi_cs_get_count(dev, con_id);
	अगर (ret > 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) अणु
		अगर (con_id)
			snम_लिखो(propname, माप(propname), "%s-%s",
				 con_id, gpio_suffixes[i]);
		अन्यथा
			snम_लिखो(propname, माप(propname), "%s",
				 gpio_suffixes[i]);

		ret = of_gpio_named_count(dev->of_node, propname);
		अगर (ret > 0)
			अवरोध;
	पूर्ण
	वापस ret ? ret : -ENOENT;
पूर्ण

अटल पूर्णांक of_gpiochip_match_node_and_xlate(काष्ठा gpio_chip *chip, व्योम *data)
अणु
	काष्ठा of_phandle_args *gpiospec = data;

	वापस chip->gpiodev->dev.of_node == gpiospec->np &&
				chip->of_xlate &&
				chip->of_xlate(chip, gpiospec, शून्य) >= 0;
पूर्ण

अटल काष्ठा gpio_chip *of_find_gpiochip_by_xlate(
					काष्ठा of_phandle_args *gpiospec)
अणु
	वापस gpiochip_find(gpiospec, of_gpiochip_match_node_and_xlate);
पूर्ण

अटल काष्ठा gpio_desc *of_xlate_and_get_gpiod_flags(काष्ठा gpio_chip *chip,
					काष्ठा of_phandle_args *gpiospec,
					क्रमागत of_gpio_flags *flags)
अणु
	पूर्णांक ret;

	अगर (chip->of_gpio_n_cells != gpiospec->args_count)
		वापस ERR_PTR(-EINVAL);

	ret = chip->of_xlate(chip, gpiospec, flags);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस gpiochip_get_desc(chip, ret);
पूर्ण

/**
 * of_gpio_need_valid_mask() - figure out अगर the OF GPIO driver needs
 * to set the .valid_mask
 * @gc: the target gpio_chip
 *
 * Return: true अगर the valid mask needs to be set
 */
bool of_gpio_need_valid_mask(स्थिर काष्ठा gpio_chip *gc)
अणु
	पूर्णांक size;
	काष्ठा device_node *np = gc->of_node;

	size = of_property_count_u32_elems(np,  "gpio-reserved-ranges");
	अगर (size > 0 && size % 2 == 0)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम of_gpio_flags_quirks(काष्ठा device_node *np,
				 स्थिर अक्षर *propname,
				 क्रमागत of_gpio_flags *flags,
				 पूर्णांक index)
अणु
	/*
	 * Some GPIO fixed regulator quirks.
	 * Note that active low is the शेष.
	 */
	अगर (IS_ENABLED(CONFIG_REGULATOR) &&
	    (of_device_is_compatible(np, "regulator-fixed") ||
	     of_device_is_compatible(np, "reg-fixed-voltage") ||
	     (!(म_भेद(propname, "enable-gpio") &&
		म_भेद(propname, "enable-gpios")) &&
	      of_device_is_compatible(np, "regulator-gpio")))) अणु
		bool active_low = !of_property_पढ़ो_bool(np,
							 "enable-active-high");
		/*
		 * The regulator GPIO handles are specअगरied such that the
		 * presence or असलence of "enable-active-high" solely controls
		 * the polarity of the GPIO line. Any phandle flags must
		 * be actively ignored.
		 */
		अगर ((*flags & OF_GPIO_ACTIVE_LOW) && !active_low) अणु
			pr_warn("%s GPIO handle specifies active low - ignored\n",
				of_node_full_name(np));
			*flags &= ~OF_GPIO_ACTIVE_LOW;
		पूर्ण
		अगर (active_low)
			*flags |= OF_GPIO_ACTIVE_LOW;
	पूर्ण
	/*
	 * Legacy खोलो drain handling क्रम fixed voltage regulators.
	 */
	अगर (IS_ENABLED(CONFIG_REGULATOR) &&
	    of_device_is_compatible(np, "reg-fixed-voltage") &&
	    of_property_पढ़ो_bool(np, "gpio-open-drain")) अणु
		*flags |= (OF_GPIO_SINGLE_ENDED | OF_GPIO_OPEN_DRAIN);
		pr_info("%s uses legacy open drain flag - update the DTS if you can\n",
			of_node_full_name(np));
	पूर्ण

	/*
	 * Legacy handling of SPI active high chip select. If we have a
	 * property named "cs-gpios" we need to inspect the child node
	 * to determine अगर the flags should have inverted semantics.
	 */
	अगर (IS_ENABLED(CONFIG_SPI_MASTER) && !म_भेद(propname, "cs-gpios") &&
	    of_property_पढ़ो_bool(np, "cs-gpios")) अणु
		काष्ठा device_node *child;
		u32 cs;
		पूर्णांक ret;

		क्रम_each_child_of_node(np, child) अणु
			ret = of_property_पढ़ो_u32(child, "reg", &cs);
			अगर (ret)
				जारी;
			अगर (cs == index) अणु
				/*
				 * SPI children have active low chip selects
				 * by शेष. This can be specअगरied negatively
				 * by just omitting "spi-cs-high" in the
				 * device node, or actively by tagging on
				 * GPIO_ACTIVE_LOW as flag in the device
				 * tree. If the line is simultaneously
				 * tagged as active low in the device tree
				 * and has the "spi-cs-high" set, we get a
				 * conflict and the "spi-cs-high" flag will
				 * take precedence.
				 */
				अगर (of_property_पढ़ो_bool(child, "spi-cs-high")) अणु
					अगर (*flags & OF_GPIO_ACTIVE_LOW) अणु
						pr_warn("%s GPIO handle specifies active low - ignored\n",
							of_node_full_name(child));
						*flags &= ~OF_GPIO_ACTIVE_LOW;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (!(*flags & OF_GPIO_ACTIVE_LOW))
						pr_info("%s enforce active low on chipselect handle\n",
							of_node_full_name(child));
					*flags |= OF_GPIO_ACTIVE_LOW;
				पूर्ण
				of_node_put(child);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Legacy handling of sपंचांगmac's active-low PHY reset line */
	अगर (IS_ENABLED(CONFIG_STMMAC_ETH) &&
	    !म_भेद(propname, "snps,reset-gpio") &&
	    of_property_पढ़ो_bool(np, "snps,reset-active-low"))
		*flags |= OF_GPIO_ACTIVE_LOW;
पूर्ण

/**
 * of_get_named_gpiod_flags() - Get a GPIO descriptor and flags क्रम GPIO API
 * @np:		device node to get GPIO from
 * @propname:	property name containing gpio specअगरier(s)
 * @index:	index of the GPIO
 * @flags:	a flags poपूर्णांकer to fill in
 *
 * Returns GPIO descriptor to use with Linux GPIO API, or one of the त्रुटि_सं
 * value on the error condition. If @flags is not शून्य the function also fills
 * in flags क्रम the GPIO.
 */
अटल काष्ठा gpio_desc *of_get_named_gpiod_flags(काष्ठा device_node *np,
		     स्थिर अक्षर *propname, पूर्णांक index, क्रमागत of_gpio_flags *flags)
अणु
	काष्ठा of_phandle_args gpiospec;
	काष्ठा gpio_chip *chip;
	काष्ठा gpio_desc *desc;
	पूर्णांक ret;

	ret = of_parse_phandle_with_args_map(np, propname, "gpio", index,
					     &gpiospec);
	अगर (ret) अणु
		pr_debug("%s: can't parse '%s' property of node '%pOF[%d]'\n",
			__func__, propname, np, index);
		वापस ERR_PTR(ret);
	पूर्ण

	chip = of_find_gpiochip_by_xlate(&gpiospec);
	अगर (!chip) अणु
		desc = ERR_PTR(-EPROBE_DEFER);
		जाओ out;
	पूर्ण

	desc = of_xlate_and_get_gpiod_flags(chip, &gpiospec, flags);
	अगर (IS_ERR(desc))
		जाओ out;

	अगर (flags)
		of_gpio_flags_quirks(np, propname, flags, index);

	pr_debug("%s: parsed '%s' property of node '%pOF[%d]' - status (%d)\n",
		 __func__, propname, np, index,
		 PTR_ERR_OR_ZERO(desc));

out:
	of_node_put(gpiospec.np);

	वापस desc;
पूर्ण

पूर्णांक of_get_named_gpio_flags(काष्ठा device_node *np, स्थिर अक्षर *list_name,
			    पूर्णांक index, क्रमागत of_gpio_flags *flags)
अणु
	काष्ठा gpio_desc *desc;

	desc = of_get_named_gpiod_flags(np, list_name, index, flags);

	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);
	अन्यथा
		वापस desc_to_gpio(desc);
पूर्ण
EXPORT_SYMBOL_GPL(of_get_named_gpio_flags);

/**
 * gpiod_get_from_of_node() - obtain a GPIO from an OF node
 * @node:	handle of the OF node
 * @propname:	name of the DT property representing the GPIO
 * @index:	index of the GPIO to obtain क्रम the consumer
 * @dflags:	GPIO initialization flags
 * @label:	label to attach to the requested GPIO
 *
 * Returns:
 * On successful request the GPIO pin is configured in accordance with
 * provided @dflags.
 *
 * In हाल of error an ERR_PTR() is वापसed.
 */
काष्ठा gpio_desc *gpiod_get_from_of_node(काष्ठा device_node *node,
					 स्थिर अक्षर *propname, पूर्णांक index,
					 क्रमागत gpiod_flags dflags,
					 स्थिर अक्षर *label)
अणु
	अचिन्हित दीर्घ lflags = GPIO_LOOKUP_FLAGS_DEFAULT;
	काष्ठा gpio_desc *desc;
	क्रमागत of_gpio_flags flags;
	bool active_low = false;
	bool single_ended = false;
	bool खोलो_drain = false;
	bool transitory = false;
	पूर्णांक ret;

	desc = of_get_named_gpiod_flags(node, propname,
					index, &flags);

	अगर (!desc || IS_ERR(desc)) अणु
		वापस desc;
	पूर्ण

	active_low = flags & OF_GPIO_ACTIVE_LOW;
	single_ended = flags & OF_GPIO_SINGLE_ENDED;
	खोलो_drain = flags & OF_GPIO_OPEN_DRAIN;
	transitory = flags & OF_GPIO_TRANSITORY;

	ret = gpiod_request(desc, label);
	अगर (ret == -EBUSY && (dflags & GPIOD_FLAGS_BIT_NONEXCLUSIVE))
		वापस desc;
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (active_low)
		lflags |= GPIO_ACTIVE_LOW;

	अगर (single_ended) अणु
		अगर (खोलो_drain)
			lflags |= GPIO_OPEN_DRAIN;
		अन्यथा
			lflags |= GPIO_OPEN_SOURCE;
	पूर्ण

	अगर (transitory)
		lflags |= GPIO_TRANSITORY;

	अगर (flags & OF_GPIO_PULL_UP)
		lflags |= GPIO_PULL_UP;

	अगर (flags & OF_GPIO_PULL_DOWN)
		lflags |= GPIO_PULL_DOWN;

	ret = gpiod_configure_flags(desc, propname, lflags, dflags);
	अगर (ret < 0) अणु
		gpiod_put(desc);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_from_of_node);

/*
 * The SPI GPIO bindings happened beक्रमe we managed to establish that GPIO
 * properties should be named "foo-gpios" so we have this special kludge क्रम
 * them.
 */
अटल काष्ठा gpio_desc *of_find_spi_gpio(काष्ठा device *dev, स्थिर अक्षर *con_id,
					  क्रमागत of_gpio_flags *of_flags)
अणु
	अक्षर prop_name[32]; /* 32 is max size of property name */
	काष्ठा device_node *np = dev->of_node;
	काष्ठा gpio_desc *desc;

	/*
	 * Hopefully the compiler stubs the rest of the function अगर this
	 * is false.
	 */
	अगर (!IS_ENABLED(CONFIG_SPI_MASTER))
		वापस ERR_PTR(-ENOENT);

	/* Allow this specअगरically क्रम "spi-gpio" devices */
	अगर (!of_device_is_compatible(np, "spi-gpio") || !con_id)
		वापस ERR_PTR(-ENOENT);

	/* Will be "gpio-sck", "gpio-mosi" or "gpio-miso" */
	snम_लिखो(prop_name, माप(prop_name), "%s-%s", "gpio", con_id);

	desc = of_get_named_gpiod_flags(np, prop_name, 0, of_flags);
	वापस desc;
पूर्ण

/*
 * The old Freescale bindings use simply "gpios" as name क्रम the chip select
 * lines rather than "cs-gpios" like all other SPI hardware. Account क्रम this
 * with a special quirk.
 */
अटल काष्ठा gpio_desc *of_find_spi_cs_gpio(काष्ठा device *dev,
					     स्थिर अक्षर *con_id,
					     अचिन्हित पूर्णांक idx,
					     अचिन्हित दीर्घ *flags)
अणु
	काष्ठा device_node *np = dev->of_node;

	अगर (!IS_ENABLED(CONFIG_SPI_MASTER))
		वापस ERR_PTR(-ENOENT);

	/* Allow this specअगरically क्रम Freescale and PPC devices */
	अगर (!of_device_is_compatible(np, "fsl,spi") &&
	    !of_device_is_compatible(np, "aeroflexgaisler,spictrl") &&
	    !of_device_is_compatible(np, "ibm,ppc4xx-spi"))
		वापस ERR_PTR(-ENOENT);
	/* Allow only अगर asking क्रम "cs-gpios" */
	अगर (!con_id || म_भेद(con_id, "cs"))
		वापस ERR_PTR(-ENOENT);

	/*
	 * While all other SPI controllers use "cs-gpios" the Freescale
	 * uses just "gpios" so translate to that when "cs-gpios" is
	 * requested.
	 */
	वापस of_find_gpio(dev, शून्य, idx, flags);
पूर्ण

/*
 * Some regulator bindings happened beक्रमe we managed to establish that GPIO
 * properties should be named "foo-gpios" so we have this special kludge क्रम
 * them.
 */
अटल काष्ठा gpio_desc *of_find_regulator_gpio(काष्ठा device *dev, स्थिर अक्षर *con_id,
						क्रमागत of_gpio_flags *of_flags)
अणु
	/* These are the connection IDs we accept as legacy GPIO phandles */
	स्थिर अक्षर *whitelist[] = अणु
		"wlf,ldoena", /* Arizona */
		"wlf,ldo1ena", /* WM8994 */
		"wlf,ldo2ena", /* WM8994 */
	पूर्ण;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा gpio_desc *desc;
	पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_REGULATOR))
		वापस ERR_PTR(-ENOENT);

	अगर (!con_id)
		वापस ERR_PTR(-ENOENT);

	i = match_string(whitelist, ARRAY_SIZE(whitelist), con_id);
	अगर (i < 0)
		वापस ERR_PTR(-ENOENT);

	desc = of_get_named_gpiod_flags(np, con_id, 0, of_flags);
	वापस desc;
पूर्ण

अटल काष्ठा gpio_desc *of_find_arizona_gpio(काष्ठा device *dev,
					      स्थिर अक्षर *con_id,
					      क्रमागत of_gpio_flags *of_flags)
अणु
	अगर (!IS_ENABLED(CONFIG_MFD_ARIZONA))
		वापस ERR_PTR(-ENOENT);

	अगर (!con_id || म_भेद(con_id, "wlf,reset"))
		वापस ERR_PTR(-ENOENT);

	वापस of_get_named_gpiod_flags(dev->of_node, con_id, 0, of_flags);
पूर्ण

अटल काष्ठा gpio_desc *of_find_usb_gpio(काष्ठा device *dev,
					  स्थिर अक्षर *con_id,
					  क्रमागत of_gpio_flags *of_flags)
अणु
	/*
	 * Currently this USB quirk is only क्रम the Fairchild FUSB302 host which is using
	 * an unकरोcumented DT GPIO line named "fcs,int_n" without the compulsory "-gpios"
	 * suffix.
	 */
	अगर (!IS_ENABLED(CONFIG_TYPEC_FUSB302))
		वापस ERR_PTR(-ENOENT);

	अगर (!con_id || म_भेद(con_id, "fcs,int_n"))
		वापस ERR_PTR(-ENOENT);

	वापस of_get_named_gpiod_flags(dev->of_node, con_id, 0, of_flags);
पूर्ण

काष्ठा gpio_desc *of_find_gpio(काष्ठा device *dev, स्थिर अक्षर *con_id,
			       अचिन्हित पूर्णांक idx, अचिन्हित दीर्घ *flags)
अणु
	अक्षर prop_name[32]; /* 32 is max size of property name */
	क्रमागत of_gpio_flags of_flags;
	काष्ठा gpio_desc *desc;
	अचिन्हित पूर्णांक i;

	/* Try GPIO property "foo-gpios" and "foo-gpio" */
	क्रम (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) अणु
		अगर (con_id)
			snम_लिखो(prop_name, माप(prop_name), "%s-%s", con_id,
				 gpio_suffixes[i]);
		अन्यथा
			snम_लिखो(prop_name, माप(prop_name), "%s",
				 gpio_suffixes[i]);

		desc = of_get_named_gpiod_flags(dev->of_node, prop_name, idx,
						&of_flags);

		अगर (!gpiod_not_found(desc))
			अवरोध;
	पूर्ण

	अगर (gpiod_not_found(desc)) अणु
		/* Special handling क्रम SPI GPIOs अगर used */
		desc = of_find_spi_gpio(dev, con_id, &of_flags);
	पूर्ण

	अगर (gpiod_not_found(desc)) अणु
		/* This quirk looks up flags and all */
		desc = of_find_spi_cs_gpio(dev, con_id, idx, flags);
		अगर (!IS_ERR(desc))
			वापस desc;
	पूर्ण

	अगर (gpiod_not_found(desc)) अणु
		/* Special handling क्रम regulator GPIOs अगर used */
		desc = of_find_regulator_gpio(dev, con_id, &of_flags);
	पूर्ण

	अगर (gpiod_not_found(desc))
		desc = of_find_arizona_gpio(dev, con_id, &of_flags);

	अगर (gpiod_not_found(desc))
		desc = of_find_usb_gpio(dev, con_id, &of_flags);

	अगर (IS_ERR(desc))
		वापस desc;

	अगर (of_flags & OF_GPIO_ACTIVE_LOW)
		*flags |= GPIO_ACTIVE_LOW;

	अगर (of_flags & OF_GPIO_SINGLE_ENDED) अणु
		अगर (of_flags & OF_GPIO_OPEN_DRAIN)
			*flags |= GPIO_OPEN_DRAIN;
		अन्यथा
			*flags |= GPIO_OPEN_SOURCE;
	पूर्ण

	अगर (of_flags & OF_GPIO_TRANSITORY)
		*flags |= GPIO_TRANSITORY;

	अगर (of_flags & OF_GPIO_PULL_UP)
		*flags |= GPIO_PULL_UP;
	अगर (of_flags & OF_GPIO_PULL_DOWN)
		*flags |= GPIO_PULL_DOWN;

	वापस desc;
पूर्ण

/**
 * of_parse_own_gpio() - Get a GPIO hog descriptor, names and flags क्रम GPIO API
 * @np:		device node to get GPIO from
 * @chip:	GPIO chip whose hog is parsed
 * @idx:	Index of the GPIO to parse
 * @name:	GPIO line name
 * @lflags:	biपंचांगask of gpio_lookup_flags GPIO_* values - वापसed from
 *		of_find_gpio() or of_parse_own_gpio()
 * @dflags:	gpiod_flags - optional GPIO initialization flags
 *
 * Returns GPIO descriptor to use with Linux GPIO API, or one of the त्रुटि_सं
 * value on the error condition.
 */
अटल काष्ठा gpio_desc *of_parse_own_gpio(काष्ठा device_node *np,
					   काष्ठा gpio_chip *chip,
					   अचिन्हित पूर्णांक idx, स्थिर अक्षर **name,
					   अचिन्हित दीर्घ *lflags,
					   क्रमागत gpiod_flags *dflags)
अणु
	काष्ठा device_node *chip_np;
	क्रमागत of_gpio_flags xlate_flags;
	काष्ठा of_phandle_args gpiospec;
	काष्ठा gpio_desc *desc;
	अचिन्हित पूर्णांक i;
	u32 पंचांगp;
	पूर्णांक ret;

	chip_np = chip->of_node;
	अगर (!chip_np)
		वापस ERR_PTR(-EINVAL);

	xlate_flags = 0;
	*lflags = GPIO_LOOKUP_FLAGS_DEFAULT;
	*dflags = GPIOD_ASIS;

	ret = of_property_पढ़ो_u32(chip_np, "#gpio-cells", &पंचांगp);
	अगर (ret)
		वापस ERR_PTR(ret);

	gpiospec.np = chip_np;
	gpiospec.args_count = पंचांगp;

	क्रम (i = 0; i < पंचांगp; i++) अणु
		ret = of_property_पढ़ो_u32_index(np, "gpios", idx * पंचांगp + i,
						 &gpiospec.args[i]);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	desc = of_xlate_and_get_gpiod_flags(chip, &gpiospec, &xlate_flags);
	अगर (IS_ERR(desc))
		वापस desc;

	अगर (xlate_flags & OF_GPIO_ACTIVE_LOW)
		*lflags |= GPIO_ACTIVE_LOW;
	अगर (xlate_flags & OF_GPIO_TRANSITORY)
		*lflags |= GPIO_TRANSITORY;
	अगर (xlate_flags & OF_GPIO_PULL_UP)
		*lflags |= GPIO_PULL_UP;
	अगर (xlate_flags & OF_GPIO_PULL_DOWN)
		*lflags |= GPIO_PULL_DOWN;

	अगर (of_property_पढ़ो_bool(np, "input"))
		*dflags |= GPIOD_IN;
	अन्यथा अगर (of_property_पढ़ो_bool(np, "output-low"))
		*dflags |= GPIOD_OUT_LOW;
	अन्यथा अगर (of_property_पढ़ो_bool(np, "output-high"))
		*dflags |= GPIOD_OUT_HIGH;
	अन्यथा अणु
		pr_warn("GPIO line %d (%pOFn): no hogging state specified, bailing out\n",
			desc_to_gpio(desc), np);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (name && of_property_पढ़ो_string(np, "line-name", name))
		*name = np->name;

	वापस desc;
पूर्ण

/**
 * of_gpiochip_add_hog - Add all hogs in a hog device node
 * @chip:	gpio chip to act on
 * @hog:	device node describing the hogs
 *
 * Returns error अगर it fails otherwise 0 on success.
 */
अटल पूर्णांक of_gpiochip_add_hog(काष्ठा gpio_chip *chip, काष्ठा device_node *hog)
अणु
	क्रमागत gpiod_flags dflags;
	काष्ठा gpio_desc *desc;
	अचिन्हित दीर्घ lflags;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0;; i++) अणु
		desc = of_parse_own_gpio(hog, chip, i, &name, &lflags, &dflags);
		अगर (IS_ERR(desc))
			अवरोध;

		ret = gpiod_hog(desc, name, lflags, dflags);
		अगर (ret < 0)
			वापस ret;

#अगर_घोषित CONFIG_OF_DYNAMIC
		desc->hog = hog;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

/**
 * of_gpiochip_scan_gpios - Scan gpio-controller क्रम gpio definitions
 * @chip:	gpio chip to act on
 *
 * This is only used by of_gpiochip_add to request/set GPIO initial
 * configuration.
 * It वापसs error अगर it fails otherwise 0 on success.
 */
अटल पूर्णांक of_gpiochip_scan_gpios(काष्ठा gpio_chip *chip)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret;

	क्रम_each_available_child_of_node(chip->of_node, np) अणु
		अगर (!of_property_पढ़ो_bool(np, "gpio-hog"))
			जारी;

		ret = of_gpiochip_add_hog(chip, np);
		अगर (ret < 0) अणु
			of_node_put(np);
			वापस ret;
		पूर्ण

		of_node_set_flag(np, OF_POPULATED);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF_DYNAMIC
/**
 * of_gpiochip_हटाओ_hog - Remove all hogs in a hog device node
 * @chip:	gpio chip to act on
 * @hog:	device node describing the hogs
 */
अटल व्योम of_gpiochip_हटाओ_hog(काष्ठा gpio_chip *chip,
				   काष्ठा device_node *hog)
अणु
	काष्ठा gpio_desc *descs = chip->gpiodev->descs;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < chip->ngpio; i++) अणु
		अगर (test_bit(FLAG_IS_HOGGED, &descs[i].flags) &&
		    descs[i].hog == hog)
			gpiochip_मुक्त_own_desc(&descs[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक of_gpiochip_match_node(काष्ठा gpio_chip *chip, व्योम *data)
अणु
	वापस chip->gpiodev->dev.of_node == data;
पूर्ण

अटल काष्ठा gpio_chip *of_find_gpiochip_by_node(काष्ठा device_node *np)
अणु
	वापस gpiochip_find(np, of_gpiochip_match_node);
पूर्ण

अटल पूर्णांक of_gpio_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			  व्योम *arg)
अणु
	काष्ठा of_reconfig_data *rd = arg;
	काष्ठा gpio_chip *chip;
	पूर्णांक ret;

	/*
	 * This only supports adding and removing complete gpio-hog nodes.
	 * Modअगरying an existing gpio-hog node is not supported (except क्रम
	 * changing its "status" property, which is treated the same as
	 * addition/removal).
	 */
	चयन (of_reconfig_get_state_change(action, arg)) अणु
	हाल OF_RECONFIG_CHANGE_ADD:
		अगर (!of_property_पढ़ो_bool(rd->dn, "gpio-hog"))
			वापस NOTIFY_OK;	/* not क्रम us */

		अगर (of_node_test_and_set_flag(rd->dn, OF_POPULATED))
			वापस NOTIFY_OK;

		chip = of_find_gpiochip_by_node(rd->dn->parent);
		अगर (chip == शून्य)
			वापस NOTIFY_OK;	/* not क्रम us */

		ret = of_gpiochip_add_hog(chip, rd->dn);
		अगर (ret < 0) अणु
			pr_err("%s: failed to add hogs for %pOF\n", __func__,
			       rd->dn);
			of_node_clear_flag(rd->dn, OF_POPULATED);
			वापस notअगरier_from_त्रुटि_सं(ret);
		पूर्ण
		अवरोध;

	हाल OF_RECONFIG_CHANGE_REMOVE:
		अगर (!of_node_check_flag(rd->dn, OF_POPULATED))
			वापस NOTIFY_OK;	/* alपढ़ोy depopulated */

		chip = of_find_gpiochip_by_node(rd->dn->parent);
		अगर (chip == शून्य)
			वापस NOTIFY_OK;	/* not क्रम us */

		of_gpiochip_हटाओ_hog(chip, rd->dn);
		of_node_clear_flag(rd->dn, OF_POPULATED);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

काष्ठा notअगरier_block gpio_of_notअगरier = अणु
	.notअगरier_call = of_gpio_notअगरy,
पूर्ण;
#पूर्ण_अगर /* CONFIG_OF_DYNAMIC */

/**
 * of_gpio_simple_xlate - translate gpiospec to the GPIO number and flags
 * @gc:		poपूर्णांकer to the gpio_chip काष्ठाure
 * @gpiospec:	GPIO specअगरier as found in the device tree
 * @flags:	a flags poपूर्णांकer to fill in
 *
 * This is simple translation function, suitable क्रम the most 1:1 mapped
 * GPIO chips. This function perक्रमms only one sanity check: whether GPIO
 * is less than ngpios (that is specअगरied in the gpio_chip).
 */
अटल पूर्णांक of_gpio_simple_xlate(काष्ठा gpio_chip *gc,
				स्थिर काष्ठा of_phandle_args *gpiospec,
				u32 *flags)
अणु
	/*
	 * We're discouraging gpio_cells < 2, since that way you'll have to
	 * ग_लिखो your own xlate function (that will have to retrieve the GPIO
	 * number and the flags from a single gpio cell -- this is possible,
	 * but not recommended).
	 */
	अगर (gc->of_gpio_n_cells < 2) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (WARN_ON(gpiospec->args_count < gc->of_gpio_n_cells))
		वापस -EINVAL;

	अगर (gpiospec->args[0] >= gc->ngpio)
		वापस -EINVAL;

	अगर (flags)
		*flags = gpiospec->args[1];

	वापस gpiospec->args[0];
पूर्ण

/**
 * of_mm_gpiochip_add_data - Add memory mapped GPIO chip (bank)
 * @np:		device node of the GPIO chip
 * @mm_gc:	poपूर्णांकer to the of_mm_gpio_chip allocated काष्ठाure
 * @data:	driver data to store in the काष्ठा gpio_chip
 *
 * To use this function you should allocate and fill mm_gc with:
 *
 * 1) In the gpio_chip काष्ठाure:
 *    - all the callbacks
 *    - of_gpio_n_cells
 *    - of_xlate callback (optional)
 *
 * 3) In the of_mm_gpio_chip काष्ठाure:
 *    - save_regs callback (optional)
 *
 * If succeeded, this function will map bank's memory and will
 * करो all necessary work क्रम you. Then you'll able to use .regs
 * to manage GPIOs from the callbacks.
 */
पूर्णांक of_mm_gpiochip_add_data(काष्ठा device_node *np,
			    काष्ठा of_mm_gpio_chip *mm_gc,
			    व्योम *data)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा gpio_chip *gc = &mm_gc->gc;

	gc->label = kaप्र_लिखो(GFP_KERNEL, "%pOF", np);
	अगर (!gc->label)
		जाओ err0;

	mm_gc->regs = of_iomap(np, 0);
	अगर (!mm_gc->regs)
		जाओ err1;

	gc->base = -1;

	अगर (mm_gc->save_regs)
		mm_gc->save_regs(mm_gc);

	mm_gc->gc.of_node = np;

	ret = gpiochip_add_data(gc, data);
	अगर (ret)
		जाओ err2;

	वापस 0;
err2:
	iounmap(mm_gc->regs);
err1:
	kमुक्त(gc->label);
err0:
	pr_err("%pOF: GPIO chip registration failed with status %d\n", np, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_mm_gpiochip_add_data);

/**
 * of_mm_gpiochip_हटाओ - Remove memory mapped GPIO chip (bank)
 * @mm_gc:	poपूर्णांकer to the of_mm_gpio_chip allocated काष्ठाure
 */
व्योम of_mm_gpiochip_हटाओ(काष्ठा of_mm_gpio_chip *mm_gc)
अणु
	काष्ठा gpio_chip *gc = &mm_gc->gc;

	अगर (!mm_gc)
		वापस;

	gpiochip_हटाओ(gc);
	iounmap(mm_gc->regs);
	kमुक्त(gc->label);
पूर्ण
EXPORT_SYMBOL_GPL(of_mm_gpiochip_हटाओ);

अटल व्योम of_gpiochip_init_valid_mask(काष्ठा gpio_chip *chip)
अणु
	पूर्णांक len, i;
	u32 start, count;
	काष्ठा device_node *np = chip->of_node;

	len = of_property_count_u32_elems(np,  "gpio-reserved-ranges");
	अगर (len < 0 || len % 2 != 0)
		वापस;

	क्रम (i = 0; i < len; i += 2) अणु
		of_property_पढ़ो_u32_index(np, "gpio-reserved-ranges",
					   i, &start);
		of_property_पढ़ो_u32_index(np, "gpio-reserved-ranges",
					   i + 1, &count);
		अगर (start >= chip->ngpio || start + count >= chip->ngpio)
			जारी;

		biपंचांगap_clear(chip->valid_mask, start, count);
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PINCTRL
अटल पूर्णांक of_gpiochip_add_pin_range(काष्ठा gpio_chip *chip)
अणु
	काष्ठा device_node *np = chip->of_node;
	काष्ठा of_phandle_args pinspec;
	काष्ठा pinctrl_dev *pctldev;
	पूर्णांक index = 0, ret;
	स्थिर अक्षर *name;
	अटल स्थिर अक्षर group_names_propname[] = "gpio-ranges-group-names";
	काष्ठा property *group_names;

	अगर (!np)
		वापस 0;

	group_names = of_find_property(np, group_names_propname, शून्य);

	क्रम (;; index++) अणु
		ret = of_parse_phandle_with_fixed_args(np, "gpio-ranges", 3,
				index, &pinspec);
		अगर (ret)
			अवरोध;

		pctldev = of_pinctrl_get(pinspec.np);
		of_node_put(pinspec.np);
		अगर (!pctldev)
			वापस -EPROBE_DEFER;

		अगर (pinspec.args[2]) अणु
			अगर (group_names) अणु
				of_property_पढ़ो_string_index(np,
						group_names_propname,
						index, &name);
				अगर (म_माप(name)) अणु
					pr_err("%pOF: Group name of numeric GPIO ranges must be the empty string.\n",
						np);
					अवरोध;
				पूर्ण
			पूर्ण
			/* npins != 0: linear range */
			ret = gpiochip_add_pin_range(chip,
					pinctrl_dev_get_devname(pctldev),
					pinspec.args[0],
					pinspec.args[1],
					pinspec.args[2]);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			/* npins == 0: special range */
			अगर (pinspec.args[1]) अणु
				pr_err("%pOF: Illegal gpio-range format.\n",
					np);
				अवरोध;
			पूर्ण

			अगर (!group_names) अणु
				pr_err("%pOF: GPIO group range requested but no %s property.\n",
					np, group_names_propname);
				अवरोध;
			पूर्ण

			ret = of_property_पढ़ो_string_index(np,
						group_names_propname,
						index, &name);
			अगर (ret)
				अवरोध;

			अगर (!म_माप(name)) अणु
				pr_err("%pOF: Group name of GPIO group range cannot be the empty string.\n",
				np);
				अवरोध;
			पूर्ण

			ret = gpiochip_add_pingroup_range(chip, pctldev,
						pinspec.args[0], name);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक of_gpiochip_add_pin_range(काष्ठा gpio_chip *chip) अणु वापस 0; पूर्ण
#पूर्ण_अगर

पूर्णांक of_gpiochip_add(काष्ठा gpio_chip *chip)
अणु
	पूर्णांक ret;

	अगर (!chip->of_node)
		वापस 0;

	अगर (!chip->of_xlate) अणु
		chip->of_gpio_n_cells = 2;
		chip->of_xlate = of_gpio_simple_xlate;
	पूर्ण

	अगर (chip->of_gpio_n_cells > MAX_PHANDLE_ARGS)
		वापस -EINVAL;

	of_gpiochip_init_valid_mask(chip);

	ret = of_gpiochip_add_pin_range(chip);
	अगर (ret)
		वापस ret;

	of_node_get(chip->of_node);

	ret = of_gpiochip_scan_gpios(chip);
	अगर (ret)
		of_node_put(chip->of_node);

	वापस ret;
पूर्ण

व्योम of_gpiochip_हटाओ(काष्ठा gpio_chip *chip)
अणु
	of_node_put(chip->of_node);
पूर्ण

व्योम of_gpio_dev_init(काष्ठा gpio_chip *gc, काष्ठा gpio_device *gdev)
अणु
	/* Set शेष OF node to parent's one अगर present */
	अगर (gc->parent)
		gdev->dev.of_node = gc->parent->of_node;

	/* If the gpiochip has an asचिन्हित OF node this takes precedence */
	अगर (gc->of_node)
		gdev->dev.of_node = gc->of_node;
	अन्यथा
		gc->of_node = gdev->dev.of_node;
पूर्ण
