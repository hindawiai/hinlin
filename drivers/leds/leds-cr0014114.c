<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Crane Merchandising Systems. All rights reserved.
// Copyright (C) 2018 Oleh Kravchenko <oleg@kaa.org.ua>

#समावेश <linux/delay.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/workqueue.h>

/*
 *  CR0014114 SPI protocol descrtiption:
 *  +----+-----------------------------------+----+
 *  | CMD|             BRIGHTNESS            |CRC |
 *  +----+-----------------------------------+----+
 *  |    | LED0| LED1| LED2| LED3| LED4| LED5|    |
 *  |    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+    |
 *  |    |R|G|B|R|G|B|R|G|B|R|G|B|R|G|B|R|G|B|    |
 *  | 1  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 1  |
 *  |    |1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|    |
 *  |    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+    |
 *  |    |               18                  |    |
 *  +----+-----------------------------------+----+
 *  |                    20                       |
 *  +---------------------------------------------+
 *
 *  PS: Boards can be connected to the chain:
 *      SPI -> board0 -> board1 -> board2 ..
 */

/* CR0014114 SPI commands */
#घोषणा CR_SET_BRIGHTNESS	0x80
#घोषणा CR_INIT_REENUMERATE	0x81
#घोषणा CR_NEXT_REENUMERATE	0x82

/* CR0014114 शेष settings */
#घोषणा CR_MAX_BRIGHTNESS	GENMASK(6, 0)
#घोषणा CR_FW_DELAY_MSEC	10
#घोषणा CR_RECOUNT_DELAY	(HZ * 3600)

#घोषणा CR_DEV_NAME		"cr0014114"

काष्ठा cr0014114_led अणु
	काष्ठा cr0014114	*priv;
	काष्ठा led_classdev	ldev;
	u8			brightness;
पूर्ण;

काष्ठा cr0014114 अणु
	bool			करो_recount;
	माप_प्रकार			count;
	काष्ठा delayed_work	work;
	काष्ठा device		*dev;
	काष्ठा mutex		lock;
	काष्ठा spi_device	*spi;
	u8			*buf;
	अचिन्हित दीर्घ		delay;
	काष्ठा cr0014114_led	leds[];
पूर्ण;

अटल व्योम cr0014114_calc_crc(u8 *buf, स्थिर माप_प्रकार len)
अणु
	माप_प्रकार	i;
	u8	crc;

	क्रम (i = 1, crc = 1; i < len - 1; i++)
		crc += buf[i];
	crc |= BIT(7);

	/* special हाल when CRC matches the SPI commands */
	अगर (crc == CR_SET_BRIGHTNESS ||
	    crc == CR_INIT_REENUMERATE ||
	    crc == CR_NEXT_REENUMERATE)
		crc = 0xfe;

	buf[len - 1] = crc;
पूर्ण

अटल पूर्णांक cr0014114_recount(काष्ठा cr0014114 *priv)
अणु
	पूर्णांक	ret;
	माप_प्रकार	i;
	u8	cmd;

	dev_dbg(priv->dev, "LEDs recount is started\n");

	cmd = CR_INIT_REENUMERATE;
	ret = spi_ग_लिखो(priv->spi, &cmd, माप(cmd));
	अगर (ret)
		जाओ err;

	cmd = CR_NEXT_REENUMERATE;
	क्रम (i = 0; i < priv->count; i++) अणु
		msleep(CR_FW_DELAY_MSEC);

		ret = spi_ग_लिखो(priv->spi, &cmd, माप(cmd));
		अगर (ret)
			जाओ err;
	पूर्ण

err:
	dev_dbg(priv->dev, "LEDs recount is finished\n");

	अगर (ret)
		dev_err(priv->dev, "with error %d", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cr0014114_sync(काष्ठा cr0014114 *priv)
अणु
	पूर्णांक		ret;
	माप_प्रकार		i;
	अचिन्हित दीर्घ	udelay, now = jअगरfies;

	/* to aव्योम SPI mistiming with firmware we should रुको some समय */
	अगर (समय_after(priv->delay, now)) अणु
		udelay = jअगरfies_to_usecs(priv->delay - now);
		usleep_range(udelay, udelay + 1);
	पूर्ण

	अगर (unlikely(priv->करो_recount)) अणु
		ret = cr0014114_recount(priv);
		अगर (ret)
			जाओ err;

		priv->करो_recount = false;
		msleep(CR_FW_DELAY_MSEC);
	पूर्ण

	priv->buf[0] = CR_SET_BRIGHTNESS;
	क्रम (i = 0; i < priv->count; i++)
		priv->buf[i + 1] = priv->leds[i].brightness;
	cr0014114_calc_crc(priv->buf, priv->count + 2);
	ret = spi_ग_लिखो(priv->spi, priv->buf, priv->count + 2);

err:
	priv->delay = jअगरfies + msecs_to_jअगरfies(CR_FW_DELAY_MSEC);

	वापस ret;
पूर्ण

अटल व्योम cr0014114_recount_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक			ret;
	काष्ठा cr0014114	*priv = container_of(work,
						     काष्ठा cr0014114,
						     work.work);

	mutex_lock(&priv->lock);
	priv->करो_recount = true;
	ret = cr0014114_sync(priv);
	mutex_unlock(&priv->lock);

	अगर (ret)
		dev_warn(priv->dev, "sync of LEDs failed %d\n", ret);

	schedule_delayed_work(&priv->work, CR_RECOUNT_DELAY);
पूर्ण

अटल पूर्णांक cr0014114_set_sync(काष्ठा led_classdev *ldev,
			      क्रमागत led_brightness brightness)
अणु
	पूर्णांक			ret;
	काष्ठा cr0014114_led    *led = container_of(ldev,
						    काष्ठा cr0014114_led,
						    ldev);

	dev_dbg(led->priv->dev, "Set brightness to %d\n", brightness);

	mutex_lock(&led->priv->lock);
	led->brightness = (u8)brightness;
	ret = cr0014114_sync(led->priv);
	mutex_unlock(&led->priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cr0014114_probe_dt(काष्ठा cr0014114 *priv)
अणु
	माप_प्रकार			i = 0;
	काष्ठा cr0014114_led	*led;
	काष्ठा fwnode_handle	*child;
	काष्ठा led_init_data	init_data = अणुपूर्ण;
	पूर्णांक			ret;

	device_क्रम_each_child_node(priv->dev, child) अणु
		led = &priv->leds[i];

		led->priv			  = priv;
		led->ldev.max_brightness	  = CR_MAX_BRIGHTNESS;
		led->ldev.brightness_set_blocking = cr0014114_set_sync;

		init_data.fwnode = child;
		init_data.devicename = CR_DEV_NAME;
		init_data.शेष_label = ":";

		ret = devm_led_classdev_रेजिस्टर_ext(priv->dev, &led->ldev,
						     &init_data);
		अगर (ret) अणु
			dev_err(priv->dev,
				"failed to register LED device, err %d", ret);
			fwnode_handle_put(child);
			वापस ret;
		पूर्ण

		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cr0014114_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा cr0014114	*priv;
	माप_प्रकार			count;
	पूर्णांक			ret;

	count = device_get_child_node_count(&spi->dev);
	अगर (!count) अणु
		dev_err(&spi->dev, "LEDs are not defined in device tree!");
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(&spi->dev, काष्ठा_size(priv, leds, count),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->buf = devm_kzalloc(&spi->dev, count + 2, GFP_KERNEL);
	अगर (!priv->buf)
		वापस -ENOMEM;

	mutex_init(&priv->lock);
	INIT_DELAYED_WORK(&priv->work, cr0014114_recount_work);
	priv->count	= count;
	priv->dev	= &spi->dev;
	priv->spi	= spi;
	priv->delay	= jअगरfies -
			  msecs_to_jअगरfies(CR_FW_DELAY_MSEC);

	priv->करो_recount = true;
	ret = cr0014114_sync(priv);
	अगर (ret) अणु
		dev_err(priv->dev, "first recount failed %d\n", ret);
		वापस ret;
	पूर्ण

	priv->करो_recount = true;
	ret = cr0014114_sync(priv);
	अगर (ret) अणु
		dev_err(priv->dev, "second recount failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cr0014114_probe_dt(priv);
	अगर (ret)
		वापस ret;

	/* setup recount work to workaround buggy firmware */
	schedule_delayed_work(&priv->work, CR_RECOUNT_DELAY);

	spi_set_drvdata(spi, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक cr0014114_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा cr0014114 *priv = spi_get_drvdata(spi);

	cancel_delayed_work_sync(&priv->work);
	mutex_destroy(&priv->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cr0014114_dt_ids[] = अणु
	अणु .compatible = "crane,cr0014114", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, cr0014114_dt_ids);

अटल काष्ठा spi_driver cr0014114_driver = अणु
	.probe		= cr0014114_probe,
	.हटाओ		= cr0014114_हटाओ,
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= cr0014114_dt_ids,
	पूर्ण,
पूर्ण;

module_spi_driver(cr0014114_driver);

MODULE_AUTHOR("Oleh Kravchenko <oleg@kaa.org.ua>");
MODULE_DESCRIPTION("cr0014114 LED driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:cr0014114");
