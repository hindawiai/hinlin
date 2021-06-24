<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO-based I2C Arbitration Using a Challenge & Response Mechanism
 *
 * Copyright (C) 2012 Google, Inc
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>


/**
 * काष्ठा i2c_arbitrator_data - Driver data क्रम I2C arbitrator
 *
 * @our_gpio: GPIO descriptor we'll use to claim.
 * @their_gpio: GPIO descriptor that the other side will use to claim.
 * @slew_delay_us: microseconds to रुको क्रम a GPIO to go high.
 * @रुको_retry_us: we'll attempt another claim after this many microseconds.
 * @रुको_मुक्त_us: we'll give up after this many microseconds.
 */

काष्ठा i2c_arbitrator_data अणु
	काष्ठा gpio_desc *our_gpio;
	काष्ठा gpio_desc *their_gpio;
	अचिन्हित पूर्णांक slew_delay_us;
	अचिन्हित पूर्णांक रुको_retry_us;
	अचिन्हित पूर्णांक रुको_मुक्त_us;
पूर्ण;


/*
 * i2c_arbitrator_select - claim the I2C bus
 *
 * Use the GPIO-based संकेतling protocol; वापस -EBUSY अगर we fail.
 */
अटल पूर्णांक i2c_arbitrator_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	स्थिर काष्ठा i2c_arbitrator_data *arb = i2c_mux_priv(muxc);
	अचिन्हित दीर्घ stop_retry, stop_समय;

	/* Start a round of trying to claim the bus */
	stop_समय = jअगरfies + usecs_to_jअगरfies(arb->रुको_मुक्त_us) + 1;
	करो अणु
		/* Indicate that we want to claim the bus */
		gpiod_set_value(arb->our_gpio, 1);
		udelay(arb->slew_delay_us);

		/* Wait क्रम the other master to release it */
		stop_retry = jअगरfies + usecs_to_jअगरfies(arb->रुको_retry_us) + 1;
		जबतक (समय_beक्रमe(jअगरfies, stop_retry)) अणु
			पूर्णांक gpio_val = gpiod_get_value(arb->their_gpio);

			अगर (!gpio_val) अणु
				/* We got it, so वापस */
				वापस 0;
			पूर्ण

			usleep_range(50, 200);
		पूर्ण

		/* It didn't release, so give up, रुको, and try again */
		gpiod_set_value(arb->our_gpio, 0);

		usleep_range(arb->रुको_retry_us, arb->रुको_retry_us * 2);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop_समय));

	/* Give up, release our claim */
	gpiod_set_value(arb->our_gpio, 0);
	udelay(arb->slew_delay_us);
	dev_err(muxc->dev, "Could not claim bus, timeout\n");
	वापस -EBUSY;
पूर्ण

/*
 * i2c_arbitrator_deselect - release the I2C bus
 *
 * Release the I2C bus using the GPIO-based संकेतling protocol.
 */
अटल पूर्णांक i2c_arbitrator_deselect(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	स्थिर काष्ठा i2c_arbitrator_data *arb = i2c_mux_priv(muxc);

	/* Release the bus and रुको क्रम the other master to notice */
	gpiod_set_value(arb->our_gpio, 0);
	udelay(arb->slew_delay_us);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_arbitrator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *parent_np;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा i2c_arbitrator_data *arb;
	काष्ठा gpio_desc *dummy;
	पूर्णांक ret;

	/* We only support probing from device tree; no platक्रमm_data */
	अगर (!np) अणु
		dev_err(dev, "Cannot find device tree node\n");
		वापस -ENODEV;
	पूर्ण
	अगर (dev_get_platdata(dev)) अणु
		dev_err(dev, "Platform data is not supported\n");
		वापस -EINVAL;
	पूर्ण

	muxc = i2c_mux_alloc(शून्य, dev, 1, माप(*arb), I2C_MUX_ARBITRATOR,
			     i2c_arbitrator_select, i2c_arbitrator_deselect);
	अगर (!muxc)
		वापस -ENOMEM;
	arb = i2c_mux_priv(muxc);

	platक्रमm_set_drvdata(pdev, muxc);

	/* Request GPIOs, our GPIO as unclaimed to begin with */
	arb->our_gpio = devm_gpiod_get(dev, "our-claim", GPIOD_OUT_LOW);
	अगर (IS_ERR(arb->our_gpio)) अणु
		dev_err(dev, "could not get \"our-claim\" GPIO (%ld)\n",
			PTR_ERR(arb->our_gpio));
		वापस PTR_ERR(arb->our_gpio);
	पूर्ण

	arb->their_gpio = devm_gpiod_get(dev, "their-claim", GPIOD_IN);
	अगर (IS_ERR(arb->their_gpio)) अणु
		dev_err(dev, "could not get \"their-claim\" GPIO (%ld)\n",
			PTR_ERR(arb->their_gpio));
		वापस PTR_ERR(arb->their_gpio);
	पूर्ण

	/* At the moment we only support a single two master (us + 1 other) */
	dummy = devm_gpiod_get_index(dev, "their-claim", 1, GPIOD_IN);
	अगर (!IS_ERR(dummy)) अणु
		dev_err(dev, "Only one other master is supported\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (PTR_ERR(dummy) == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण

	/* Arbitration parameters */
	अगर (of_property_पढ़ो_u32(np, "slew-delay-us", &arb->slew_delay_us))
		arb->slew_delay_us = 10;
	अगर (of_property_पढ़ो_u32(np, "wait-retry-us", &arb->रुको_retry_us))
		arb->रुको_retry_us = 3000;
	अगर (of_property_पढ़ो_u32(np, "wait-free-us", &arb->रुको_मुक्त_us))
		arb->रुको_मुक्त_us = 50000;

	/* Find our parent */
	parent_np = of_parse_phandle(np, "i2c-parent", 0);
	अगर (!parent_np) अणु
		dev_err(dev, "Cannot parse i2c-parent\n");
		वापस -EINVAL;
	पूर्ण
	muxc->parent = of_get_i2c_adapter_by_node(parent_np);
	of_node_put(parent_np);
	अगर (!muxc->parent) अणु
		dev_err(dev, "Cannot find parent bus\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	/* Actually add the mux adapter */
	ret = i2c_mux_add_adapter(muxc, 0, 0, 0);
	अगर (ret)
		i2c_put_adapter(muxc->parent);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_arbitrator_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_mux_core *muxc = platक्रमm_get_drvdata(pdev);

	i2c_mux_del_adapters(muxc);
	i2c_put_adapter(muxc->parent);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id i2c_arbitrator_of_match[] = अणु
	अणु .compatible = "i2c-arb-gpio-challenge", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_arbitrator_of_match);

अटल काष्ठा platक्रमm_driver i2c_arbitrator_driver = अणु
	.probe	= i2c_arbitrator_probe,
	.हटाओ	= i2c_arbitrator_हटाओ,
	.driver	= अणु
		.name	= "i2c-arb-gpio-challenge",
		.of_match_table = i2c_arbitrator_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(i2c_arbitrator_driver);

MODULE_DESCRIPTION("GPIO-based I2C Arbitration");
MODULE_AUTHOR("Doug Anderson <dianders@chromium.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:i2c-arb-gpio-challenge");
