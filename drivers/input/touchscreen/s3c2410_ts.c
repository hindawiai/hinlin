<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Samsung S3C24XX touchscreen driver
 *
 * Copyright 2004 Arnaud Patard <arnaud.patard@rtp-net.org>
 * Copyright 2008 Ben Dooks <ben-linux@fluff.org>
 * Copyright 2009 Simtec Electronics <linux@simtec.co.uk>
 *
 * Additional work by Herbert Pथघtzl <herbert@13thन्यूनमान.at> and
 * Harald Welte <laक्रमge@खोलोmoko.org>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <linux/soc/samsung/s3c-adc.h>
#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>

#घोषणा	S3C2410_ADCCON			(0x00)
#घोषणा	S3C2410_ADCTSC			(0x04)
#घोषणा	S3C2410_ADCDLY			(0x08)
#घोषणा	S3C2410_ADCDAT0			(0x0C)
#घोषणा	S3C2410_ADCDAT1			(0x10)
#घोषणा	S3C64XX_ADCUPDN			(0x14)
#घोषणा	S3C2443_ADCMUX			(0x18)
#घोषणा	S3C64XX_ADCCLRINT		(0x18)
#घोषणा	S5P_ADCMUX			(0x1C)
#घोषणा	S3C64XX_ADCCLRINTPNDNUP		(0x20)

/* ADCTSC Register Bits */
#घोषणा S3C2443_ADCTSC_UD_SEN		(1 << 8)
#घोषणा S3C2410_ADCTSC_YM_SEN		(1<<7)
#घोषणा S3C2410_ADCTSC_YP_SEN		(1<<6)
#घोषणा S3C2410_ADCTSC_XM_SEN		(1<<5)
#घोषणा S3C2410_ADCTSC_XP_SEN		(1<<4)
#घोषणा S3C2410_ADCTSC_PULL_UP_DISABLE	(1<<3)
#घोषणा S3C2410_ADCTSC_AUTO_PST		(1<<2)
#घोषणा S3C2410_ADCTSC_XY_PST(x)	(((x)&0x3)<<0)

/* ADCDAT0 Bits */
#घोषणा S3C2410_ADCDAT0_UPDOWN		(1<<15)
#घोषणा S3C2410_ADCDAT0_AUTO_PST	(1<<14)
#घोषणा S3C2410_ADCDAT0_XY_PST		(0x3<<12)
#घोषणा S3C2410_ADCDAT0_XPDATA_MASK	(0x03FF)

/* ADCDAT1 Bits */
#घोषणा S3C2410_ADCDAT1_UPDOWN		(1<<15)
#घोषणा S3C2410_ADCDAT1_AUTO_PST	(1<<14)
#घोषणा S3C2410_ADCDAT1_XY_PST		(0x3<<12)
#घोषणा S3C2410_ADCDAT1_YPDATA_MASK	(0x03FF)


#घोषणा TSC_SLEEP  (S3C2410_ADCTSC_PULL_UP_DISABLE | S3C2410_ADCTSC_XY_PST(0))

#घोषणा INT_DOWN	(0)
#घोषणा INT_UP		(1 << 8)

#घोषणा WAIT4INT	(S3C2410_ADCTSC_YM_SEN | \
			 S3C2410_ADCTSC_YP_SEN | \
			 S3C2410_ADCTSC_XP_SEN | \
			 S3C2410_ADCTSC_XY_PST(3))

#घोषणा AUTOPST		(S3C2410_ADCTSC_YM_SEN | \
			 S3C2410_ADCTSC_YP_SEN | \
			 S3C2410_ADCTSC_XP_SEN | \
			 S3C2410_ADCTSC_AUTO_PST | \
			 S3C2410_ADCTSC_XY_PST(0))

#घोषणा FEAT_PEN_IRQ	(1 << 0)	/* HAS ADCCLRINTPNDNUP */

/* Per-touchscreen data. */

/**
 * काष्ठा s3c2410ts - driver touchscreen state.
 * @client: The ADC client we रेजिस्टरed with the core driver.
 * @dev: The device we are bound to.
 * @input: The input device we रेजिस्टरed with the input subप्रणाली.
 * @घड़ी: The घड़ी क्रम the adc.
 * @io: Poपूर्णांकer to the IO base.
 * @xp: The accumulated X position data.
 * @yp: The accumulated Y position data.
 * @irq_tc: The पूर्णांकerrupt number क्रम pen up/करोwn पूर्णांकerrupt
 * @count: The number of samples collected.
 * @shअगरt: The log2 of the maximum count to पढ़ो in one go.
 * @features: The features supported by the TSADC MOdule.
 */
काष्ठा s3c2410ts अणु
	काष्ठा s3c_adc_client *client;
	काष्ठा device *dev;
	काष्ठा input_dev *input;
	काष्ठा clk *घड़ी;
	व्योम __iomem *io;
	अचिन्हित दीर्घ xp;
	अचिन्हित दीर्घ yp;
	पूर्णांक irq_tc;
	पूर्णांक count;
	पूर्णांक shअगरt;
	पूर्णांक features;
पूर्ण;

अटल काष्ठा s3c2410ts ts;

/**
 * get_करोwn - वापस the करोwn state of the pen
 * @data0: The data पढ़ो from ADCDAT0 रेजिस्टर.
 * @data1: The data पढ़ो from ADCDAT1 रेजिस्टर.
 *
 * Return non-zero अगर both पढ़ोings show that the pen is करोwn.
 */
अटल अंतरभूत bool get_करोwn(अचिन्हित दीर्घ data0, अचिन्हित दीर्घ data1)
अणु
	/* वापसs true अगर both data values show stylus करोwn */
	वापस (!(data0 & S3C2410_ADCDAT0_UPDOWN) &&
		!(data1 & S3C2410_ADCDAT0_UPDOWN));
पूर्ण

अटल व्योम touch_समयr_fire(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ data0;
	अचिन्हित दीर्घ data1;
	bool करोwn;

	data0 = पढ़ोl(ts.io + S3C2410_ADCDAT0);
	data1 = पढ़ोl(ts.io + S3C2410_ADCDAT1);

	करोwn = get_करोwn(data0, data1);

	अगर (करोwn) अणु
		अगर (ts.count == (1 << ts.shअगरt)) अणु
			ts.xp >>= ts.shअगरt;
			ts.yp >>= ts.shअगरt;

			dev_dbg(ts.dev, "%s: X=%lu, Y=%lu, count=%d\n",
				__func__, ts.xp, ts.yp, ts.count);

			input_report_असल(ts.input, ABS_X, ts.xp);
			input_report_असल(ts.input, ABS_Y, ts.yp);

			input_report_key(ts.input, BTN_TOUCH, 1);
			input_sync(ts.input);

			ts.xp = 0;
			ts.yp = 0;
			ts.count = 0;
		पूर्ण

		s3c_adc_start(ts.client, 0, 1 << ts.shअगरt);
	पूर्ण अन्यथा अणु
		ts.xp = 0;
		ts.yp = 0;
		ts.count = 0;

		input_report_key(ts.input, BTN_TOUCH, 0);
		input_sync(ts.input);

		ग_लिखोl(WAIT4INT | INT_DOWN, ts.io + S3C2410_ADCTSC);
	पूर्ण
पूर्ण

अटल DEFINE_TIMER(touch_समयr, touch_समयr_fire);

/**
 * stylus_irq - touchscreen stylus event पूर्णांकerrupt
 * @irq: The पूर्णांकerrupt number
 * @dev_id: The device ID.
 *
 * Called when the IRQ_TC is fired क्रम a pen up or करोwn event.
 */
अटल irqवापस_t stylus_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ data0;
	अचिन्हित दीर्घ data1;
	bool करोwn;

	data0 = पढ़ोl(ts.io + S3C2410_ADCDAT0);
	data1 = पढ़ोl(ts.io + S3C2410_ADCDAT1);

	करोwn = get_करोwn(data0, data1);

	/* TODO we should never get an पूर्णांकerrupt with करोwn set जबतक
	 * the समयr is running, but maybe we ought to verअगरy that the
	 * समयr isn't running anyways. */

	अगर (करोwn)
		s3c_adc_start(ts.client, 0, 1 << ts.shअगरt);
	अन्यथा
		dev_dbg(ts.dev, "%s: count=%d\n", __func__, ts.count);

	अगर (ts.features & FEAT_PEN_IRQ) अणु
		/* Clear pen करोwn/up पूर्णांकerrupt */
		ग_लिखोl(0x0, ts.io + S3C64XX_ADCCLRINTPNDNUP);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * s3c24xx_ts_conversion - ADC conversion callback
 * @client: The client that was रेजिस्टरed with the ADC core.
 * @data0: The पढ़ोing from ADCDAT0.
 * @data1: The पढ़ोing from ADCDAT1.
 * @left: The number of samples left.
 *
 * Called when a conversion has finished.
 */
अटल व्योम s3c24xx_ts_conversion(काष्ठा s3c_adc_client *client,
				  अचिन्हित data0, अचिन्हित data1,
				  अचिन्हित *left)
अणु
	dev_dbg(ts.dev, "%s: %d,%d\n", __func__, data0, data1);

	ts.xp += data0;
	ts.yp += data1;

	ts.count++;

	/* From tests, it seems that it is unlikely to get a pen-up
	 * event during the conversion process which means we can
	 * ignore any pen-up events with less than the requisite
	 * count करोne.
	 *
	 * In several thousand conversions, no pen-ups where detected
	 * beक्रमe count completed.
	 */
पूर्ण

/**
 * s3c24xx_ts_select - ADC selection callback.
 * @client: The client that was रेजिस्टरed with the ADC core.
 * @select: The reason क्रम select.
 *
 * Called when the ADC core selects (or deslects) us as a client.
 */
अटल व्योम s3c24xx_ts_select(काष्ठा s3c_adc_client *client, अचिन्हित select)
अणु
	अगर (select) अणु
		ग_लिखोl(S3C2410_ADCTSC_PULL_UP_DISABLE | AUTOPST,
		       ts.io + S3C2410_ADCTSC);
	पूर्ण अन्यथा अणु
		mod_समयr(&touch_समयr, jअगरfies+1);
		ग_लिखोl(WAIT4INT | INT_UP, ts.io + S3C2410_ADCTSC);
	पूर्ण
पूर्ण

/**
 * s3c2410ts_probe - device core probe entry poपूर्णांक
 * @pdev: The device we are being bound to.
 *
 * Initialise, find and allocate any resources we need to run and then
 * रेजिस्टर with the ADC and input प्रणालीs.
 */
अटल पूर्णांक s3c2410ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c2410_ts_mach_info *info;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा input_dev *input_dev;
	काष्ठा resource *res;
	पूर्णांक ret = -EINVAL;

	/* Initialise input stuff */
	स_रखो(&ts, 0, माप(काष्ठा s3c2410ts));

	ts.dev = dev;

	info = dev_get_platdata(dev);
	अगर (!info) अणु
		dev_err(dev, "no platform data, cannot attach\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "initialising touchscreen\n");

	ts.घड़ी = clk_get(dev, "adc");
	अगर (IS_ERR(ts.घड़ी)) अणु
		dev_err(dev, "cannot get adc clock source\n");
		वापस -ENOENT;
	पूर्ण

	ret = clk_prepare_enable(ts.घड़ी);
	अगर (ret) अणु
		dev_err(dev, "Failed! to enabled clocks\n");
		जाओ err_clk_get;
	पूर्ण
	dev_dbg(dev, "got and enabled clocks\n");

	ts.irq_tc = ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "no resource for interrupt\n");
		जाओ err_clk;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "no resource for registers\n");
		ret = -ENOENT;
		जाओ err_clk;
	पूर्ण

	ts.io = ioremap(res->start, resource_size(res));
	अगर (ts.io == शून्य) अणु
		dev_err(dev, "cannot map registers\n");
		ret = -ENOMEM;
		जाओ err_clk;
	पूर्ण

	/* inititalise the gpio */
	अगर (info->cfg_gpio)
		info->cfg_gpio(to_platक्रमm_device(ts.dev));

	ts.client = s3c_adc_रेजिस्टर(pdev, s3c24xx_ts_select,
				     s3c24xx_ts_conversion, 1);
	अगर (IS_ERR(ts.client)) अणु
		dev_err(dev, "failed to register adc client\n");
		ret = PTR_ERR(ts.client);
		जाओ err_iomap;
	पूर्ण

	/* Initialise रेजिस्टरs */
	अगर ((info->delay & 0xffff) > 0)
		ग_लिखोl(info->delay & 0xffff, ts.io + S3C2410_ADCDLY);

	ग_लिखोl(WAIT4INT | INT_DOWN, ts.io + S3C2410_ADCTSC);

	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		dev_err(dev, "Unable to allocate the input device !!\n");
		ret = -ENOMEM;
		जाओ err_iomap;
	पूर्ण

	ts.input = input_dev;
	ts.input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	ts.input->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(ts.input, ABS_X, 0, 0x3FF, 0, 0);
	input_set_असल_params(ts.input, ABS_Y, 0, 0x3FF, 0, 0);

	ts.input->name = "S3C24XX TouchScreen";
	ts.input->id.bustype = BUS_HOST;
	ts.input->id.venकरोr = 0xDEAD;
	ts.input->id.product = 0xBEEF;
	ts.input->id.version = 0x0102;

	ts.shअगरt = info->oversampling_shअगरt;
	ts.features = platक्रमm_get_device_id(pdev)->driver_data;

	ret = request_irq(ts.irq_tc, stylus_irq, 0,
			  "s3c2410_ts_pen", ts.input);
	अगर (ret) अणु
		dev_err(dev, "cannot get TC interrupt\n");
		जाओ err_inputdev;
	पूर्ण

	dev_info(dev, "driver attached, registering input device\n");

	/* All went ok, so रेजिस्टर to the input प्रणाली */
	ret = input_रेजिस्टर_device(ts.input);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register input device\n");
		ret = -EIO;
		जाओ err_tcirq;
	पूर्ण

	वापस 0;

 err_tcirq:
	मुक्त_irq(ts.irq_tc, ts.input);
 err_inputdev:
	input_मुक्त_device(ts.input);
 err_iomap:
	iounmap(ts.io);
 err_clk:
	clk_disable_unprepare(ts.घड़ी);
	del_समयr_sync(&touch_समयr);
 err_clk_get:
	clk_put(ts.घड़ी);
	वापस ret;
पूर्ण

/**
 * s3c2410ts_हटाओ - device core removal entry poपूर्णांक
 * @pdev: The device we are being हटाओd from.
 *
 * Free up our state पढ़ोy to be हटाओd.
 */
अटल पूर्णांक s3c2410ts_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	मुक्त_irq(ts.irq_tc, ts.input);
	del_समयr_sync(&touch_समयr);

	clk_disable_unprepare(ts.घड़ी);
	clk_put(ts.घड़ी);

	input_unरेजिस्टर_device(ts.input);
	iounmap(ts.io);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s3c2410ts_suspend(काष्ठा device *dev)
अणु
	ग_लिखोl(TSC_SLEEP, ts.io + S3C2410_ADCTSC);
	disable_irq(ts.irq_tc);
	clk_disable(ts.घड़ी);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410ts_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा s3c2410_ts_mach_info *info = dev_get_platdata(&pdev->dev);

	clk_enable(ts.घड़ी);
	enable_irq(ts.irq_tc);

	/* Initialise रेजिस्टरs */
	अगर ((info->delay & 0xffff) > 0)
		ग_लिखोl(info->delay & 0xffff, ts.io + S3C2410_ADCDLY);

	ग_लिखोl(WAIT4INT | INT_DOWN, ts.io + S3C2410_ADCTSC);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops s3c_ts_pmops = अणु
	.suspend	= s3c2410ts_suspend,
	.resume		= s3c2410ts_resume,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id s3cts_driver_ids[] = अणु
	अणु "s3c2410-ts", 0 पूर्ण,
	अणु "s3c2440-ts", 0 पूर्ण,
	अणु "s3c64xx-ts", FEAT_PEN_IRQ पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s3cts_driver_ids);

अटल काष्ठा platक्रमm_driver s3c_ts_driver = अणु
	.driver         = अणु
		.name   = "samsung-ts",
#अगर_घोषित CONFIG_PM
		.pm	= &s3c_ts_pmops,
#पूर्ण_अगर
	पूर्ण,
	.id_table	= s3cts_driver_ids,
	.probe		= s3c2410ts_probe,
	.हटाओ		= s3c2410ts_हटाओ,
पूर्ण;
module_platक्रमm_driver(s3c_ts_driver);

MODULE_AUTHOR("Arnaud Patard <arnaud.patard@rtp-net.org>, "
	      "Ben Dooks <ben@simtec.co.uk>, "
	      "Simtec Electronics <linux@simtec.co.uk>");
MODULE_DESCRIPTION("S3C24XX Touchscreen driver");
MODULE_LICENSE("GPL v2");
