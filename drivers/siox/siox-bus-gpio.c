<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2017 Pengutronix, Uwe Kleine-Kथघnig <kernel@pengutronix.de>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/delay.h>

#समावेश "siox.h"

#घोषणा DRIVER_NAME "siox-gpio"

काष्ठा siox_gpio_ddata अणु
	काष्ठा gpio_desc *din;
	काष्ठा gpio_desc *करोut;
	काष्ठा gpio_desc *dclk;
	काष्ठा gpio_desc *dld;
पूर्ण;

अटल अचिन्हित पूर्णांक siox_clkhigh_ns = 1000;
अटल अचिन्हित पूर्णांक siox_loadhigh_ns;
अटल अचिन्हित पूर्णांक siox_bytegap_ns;

अटल पूर्णांक siox_gpio_pushpull(काष्ठा siox_master *smaster,
			      माप_प्रकार रखो_बफ_len, स्थिर u8 रखो_बफ[],
			      माप_प्रकार getbuf_len, u8 getbuf[])
अणु
	काष्ठा siox_gpio_ddata *ddata = siox_master_get_devdata(smaster);
	माप_प्रकार i;
	माप_प्रकार cycles = max(रखो_बफ_len, getbuf_len);

	/* reset data and घड़ी */
	gpiod_set_value_cansleep(ddata->करोut, 0);
	gpiod_set_value_cansleep(ddata->dclk, 0);

	gpiod_set_value_cansleep(ddata->dld, 1);
	ndelay(siox_loadhigh_ns);
	gpiod_set_value_cansleep(ddata->dld, 0);

	क्रम (i = 0; i < cycles; ++i) अणु
		u8 set = 0, get = 0;
		माप_प्रकार j;

		अगर (i >= cycles - रखो_बफ_len)
			set = रखो_बफ[i - (cycles - रखो_बफ_len)];

		क्रम (j = 0; j < 8; ++j) अणु
			get <<= 1;
			अगर (gpiod_get_value_cansleep(ddata->din))
				get |= 1;

			/* DOUT is logically inverted */
			gpiod_set_value_cansleep(ddata->करोut, !(set & 0x80));
			set <<= 1;

			gpiod_set_value_cansleep(ddata->dclk, 1);
			ndelay(siox_clkhigh_ns);
			gpiod_set_value_cansleep(ddata->dclk, 0);
		पूर्ण

		अगर (i < getbuf_len)
			getbuf[i] = get;

		ndelay(siox_bytegap_ns);
	पूर्ण

	gpiod_set_value_cansleep(ddata->dld, 1);
	ndelay(siox_loadhigh_ns);
	gpiod_set_value_cansleep(ddata->dld, 0);

	/*
	 * Resetting करोut isn't necessary protocol wise, but it makes the
	 * संकेतs more pretty because the करोut level is deterministic between
	 * cycles. Note that this only affects करोut between the master and the
	 * first siox device. करोut क्रम the later devices depend on the output of
	 * the previous siox device.
	 */
	gpiod_set_value_cansleep(ddata->करोut, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक siox_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा siox_gpio_ddata *ddata;
	पूर्णांक ret;
	काष्ठा siox_master *smaster;

	smaster = siox_master_alloc(&pdev->dev, माप(*ddata));
	अगर (!smaster) अणु
		dev_err(dev, "failed to allocate siox master\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, smaster);
	ddata = siox_master_get_devdata(smaster);

	ddata->din = devm_gpiod_get(dev, "din", GPIOD_IN);
	अगर (IS_ERR(ddata->din)) अणु
		ret = PTR_ERR(ddata->din);
		dev_err(dev, "Failed to get %s GPIO: %d\n", "din", ret);
		जाओ err;
	पूर्ण

	ddata->करोut = devm_gpiod_get(dev, "dout", GPIOD_OUT_LOW);
	अगर (IS_ERR(ddata->करोut)) अणु
		ret = PTR_ERR(ddata->करोut);
		dev_err(dev, "Failed to get %s GPIO: %d\n", "dout", ret);
		जाओ err;
	पूर्ण

	ddata->dclk = devm_gpiod_get(dev, "dclk", GPIOD_OUT_LOW);
	अगर (IS_ERR(ddata->dclk)) अणु
		ret = PTR_ERR(ddata->dclk);
		dev_err(dev, "Failed to get %s GPIO: %d\n", "dclk", ret);
		जाओ err;
	पूर्ण

	ddata->dld = devm_gpiod_get(dev, "dld", GPIOD_OUT_LOW);
	अगर (IS_ERR(ddata->dld)) अणु
		ret = PTR_ERR(ddata->dld);
		dev_err(dev, "Failed to get %s GPIO: %d\n", "dld", ret);
		जाओ err;
	पूर्ण

	smaster->pushpull = siox_gpio_pushpull;
	/* XXX: determine स्वतःmatically like spi करोes */
	smaster->busno = 0;

	ret = siox_master_रेजिस्टर(smaster);
	अगर (ret) अणु
		dev_err(dev, "Failed to register siox master: %d\n", ret);
err:
		siox_master_put(smaster);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक siox_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा siox_master *master = platक्रमm_get_drvdata(pdev);

	siox_master_unरेजिस्टर(master);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id siox_gpio_dt_ids[] = अणु
	अणु .compatible = "eckelmann,siox-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, siox_gpio_dt_ids);

अटल काष्ठा platक्रमm_driver siox_gpio_driver = अणु
	.probe = siox_gpio_probe,
	.हटाओ = siox_gpio_हटाओ,

	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = siox_gpio_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(siox_gpio_driver);

MODULE_AUTHOR("Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
