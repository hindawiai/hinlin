<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LPC32xx built-in touchscreen driver
 *
 * Copyright (C) 2010 NXP Semiconductors
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

/*
 * Touchscreen controller रेजिस्टर offsets
 */
#घोषणा LPC32XX_TSC_STAT			0x00
#घोषणा LPC32XX_TSC_SEL				0x04
#घोषणा LPC32XX_TSC_CON				0x08
#घोषणा LPC32XX_TSC_FIFO			0x0C
#घोषणा LPC32XX_TSC_DTR				0x10
#घोषणा LPC32XX_TSC_RTR				0x14
#घोषणा LPC32XX_TSC_UTR				0x18
#घोषणा LPC32XX_TSC_TTR				0x1C
#घोषणा LPC32XX_TSC_DXP				0x20
#घोषणा LPC32XX_TSC_MIN_X			0x24
#घोषणा LPC32XX_TSC_MAX_X			0x28
#घोषणा LPC32XX_TSC_MIN_Y			0x2C
#घोषणा LPC32XX_TSC_MAX_Y			0x30
#घोषणा LPC32XX_TSC_AUX_UTR			0x34
#घोषणा LPC32XX_TSC_AUX_MIN			0x38
#घोषणा LPC32XX_TSC_AUX_MAX			0x3C

#घोषणा LPC32XX_TSC_STAT_FIFO_OVRRN		BIT(8)
#घोषणा LPC32XX_TSC_STAT_FIFO_EMPTY		BIT(7)

#घोषणा LPC32XX_TSC_SEL_DEFVAL			0x0284

#घोषणा LPC32XX_TSC_ADCCON_IRQ_TO_FIFO_4	(0x1 << 11)
#घोषणा LPC32XX_TSC_ADCCON_X_SAMPLE_SIZE(s)	((10 - (s)) << 7)
#घोषणा LPC32XX_TSC_ADCCON_Y_SAMPLE_SIZE(s)	((10 - (s)) << 4)
#घोषणा LPC32XX_TSC_ADCCON_POWER_UP		BIT(2)
#घोषणा LPC32XX_TSC_ADCCON_AUTO_EN		BIT(0)

#घोषणा LPC32XX_TSC_FIFO_TS_P_LEVEL		BIT(31)
#घोषणा LPC32XX_TSC_FIFO_NORMALIZE_X_VAL(x)	(((x) & 0x03FF0000) >> 16)
#घोषणा LPC32XX_TSC_FIFO_NORMALIZE_Y_VAL(y)	((y) & 0x000003FF)

#घोषणा LPC32XX_TSC_ADCDAT_VALUE_MASK		0x000003FF

#घोषणा LPC32XX_TSC_MIN_XY_VAL			0x0
#घोषणा LPC32XX_TSC_MAX_XY_VAL			0x3FF

#घोषणा MOD_NAME "ts-lpc32xx"

#घोषणा tsc_पढ़ोl(dev, reg) \
	__raw_पढ़ोl((dev)->tsc_base + (reg))
#घोषणा tsc_ग_लिखोl(dev, reg, val) \
	__raw_ग_लिखोl((val), (dev)->tsc_base + (reg))

काष्ठा lpc32xx_tsc अणु
	काष्ठा input_dev *dev;
	व्योम __iomem *tsc_base;
	पूर्णांक irq;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम lpc32xx_fअगरo_clear(काष्ठा lpc32xx_tsc *tsc)
अणु
	जबतक (!(tsc_पढ़ोl(tsc, LPC32XX_TSC_STAT) &
			LPC32XX_TSC_STAT_FIFO_EMPTY))
		tsc_पढ़ोl(tsc, LPC32XX_TSC_FIFO);
पूर्ण

अटल irqवापस_t lpc32xx_ts_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 पंचांगp, rv[4], xs[4], ys[4];
	पूर्णांक idx;
	काष्ठा lpc32xx_tsc *tsc = dev_id;
	काष्ठा input_dev *input = tsc->dev;

	पंचांगp = tsc_पढ़ोl(tsc, LPC32XX_TSC_STAT);

	अगर (पंचांगp & LPC32XX_TSC_STAT_FIFO_OVRRN) अणु
		/* FIFO overflow - throw away samples */
		lpc32xx_fअगरo_clear(tsc);
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * Gather and normalize 4 samples. Pen-up events may have less
	 * than 4 samples, but its ok to pop 4 and let the last sample
	 * pen status check drop the samples.
	 */
	idx = 0;
	जबतक (idx < 4 &&
	       !(tsc_पढ़ोl(tsc, LPC32XX_TSC_STAT) &
			LPC32XX_TSC_STAT_FIFO_EMPTY)) अणु
		पंचांगp = tsc_पढ़ोl(tsc, LPC32XX_TSC_FIFO);
		xs[idx] = LPC32XX_TSC_ADCDAT_VALUE_MASK -
			LPC32XX_TSC_FIFO_NORMALIZE_X_VAL(पंचांगp);
		ys[idx] = LPC32XX_TSC_ADCDAT_VALUE_MASK -
			LPC32XX_TSC_FIFO_NORMALIZE_Y_VAL(पंचांगp);
		rv[idx] = पंचांगp;
		idx++;
	पूर्ण

	/* Data is only valid अगर pen is still करोwn in last sample */
	अगर (!(rv[3] & LPC32XX_TSC_FIFO_TS_P_LEVEL) && idx == 4) अणु
		/* Use average of 2nd and 3rd sample क्रम position */
		input_report_असल(input, ABS_X, (xs[1] + xs[2]) / 2);
		input_report_असल(input, ABS_Y, (ys[1] + ys[2]) / 2);
		input_report_key(input, BTN_TOUCH, 1);
	पूर्ण अन्यथा अणु
		input_report_key(input, BTN_TOUCH, 0);
	पूर्ण

	input_sync(input);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम lpc32xx_stop_tsc(काष्ठा lpc32xx_tsc *tsc)
अणु
	/* Disable स्वतः mode */
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_CON,
		   tsc_पढ़ोl(tsc, LPC32XX_TSC_CON) &
			     ~LPC32XX_TSC_ADCCON_AUTO_EN);

	clk_disable_unprepare(tsc->clk);
पूर्ण

अटल पूर्णांक lpc32xx_setup_tsc(काष्ठा lpc32xx_tsc *tsc)
अणु
	u32 पंचांगp;
	पूर्णांक err;

	err = clk_prepare_enable(tsc->clk);
	अगर (err)
		वापस err;

	पंचांगp = tsc_पढ़ोl(tsc, LPC32XX_TSC_CON) & ~LPC32XX_TSC_ADCCON_POWER_UP;

	/* Set the TSC FIFO depth to 4 samples @ 10-bits per sample (max) */
	पंचांगp = LPC32XX_TSC_ADCCON_IRQ_TO_FIFO_4 |
	      LPC32XX_TSC_ADCCON_X_SAMPLE_SIZE(10) |
	      LPC32XX_TSC_ADCCON_Y_SAMPLE_SIZE(10);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_CON, पंचांगp);

	/* These values are all preset */
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_SEL, LPC32XX_TSC_SEL_DEFVAL);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_MIN_X, LPC32XX_TSC_MIN_XY_VAL);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_MAX_X, LPC32XX_TSC_MAX_XY_VAL);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_MIN_Y, LPC32XX_TSC_MIN_XY_VAL);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_MAX_Y, LPC32XX_TSC_MAX_XY_VAL);

	/* Aux support is not used */
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_AUX_UTR, 0);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_AUX_MIN, 0);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_AUX_MAX, 0);

	/*
	 * Set sample rate to about 240Hz per X/Y pair. A single measurement
	 * consists of 4 pairs which gives about a 60Hz sample rate based on
	 * a stable 32768Hz घड़ी source. Values are in घड़ीs.
	 * Rate is (32768 / (RTR + XCONV + RTR + YCONV + DXP + TTR + UTR) / 4
	 */
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_RTR, 0x2);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_DTR, 0x2);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_TTR, 0x10);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_DXP, 0x4);
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_UTR, 88);

	lpc32xx_fअगरo_clear(tsc);

	/* Enable स्वतःmatic ts event capture */
	tsc_ग_लिखोl(tsc, LPC32XX_TSC_CON, पंचांगp | LPC32XX_TSC_ADCCON_AUTO_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा lpc32xx_tsc *tsc = input_get_drvdata(dev);

	वापस lpc32xx_setup_tsc(tsc);
पूर्ण

अटल व्योम lpc32xx_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा lpc32xx_tsc *tsc = input_get_drvdata(dev);

	lpc32xx_stop_tsc(tsc);
पूर्ण

अटल पूर्णांक lpc32xx_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_tsc *tsc;
	काष्ठा input_dev *input;
	काष्ठा resource *res;
	resource_माप_प्रकार size;
	पूर्णांक irq;
	पूर्णांक error;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Can't get memory resource\n");
		वापस -ENOENT;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	tsc = kzalloc(माप(*tsc), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!tsc || !input) अणु
		dev_err(&pdev->dev, "failed allocating memory\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	tsc->dev = input;
	tsc->irq = irq;

	size = resource_size(res);

	अगर (!request_mem_region(res->start, size, pdev->name)) अणु
		dev_err(&pdev->dev, "TSC registers are not free\n");
		error = -EBUSY;
		जाओ err_मुक्त_mem;
	पूर्ण

	tsc->tsc_base = ioremap(res->start, size);
	अगर (!tsc->tsc_base) अणु
		dev_err(&pdev->dev, "Can't map memory\n");
		error = -ENOMEM;
		जाओ err_release_mem;
	पूर्ण

	tsc->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(tsc->clk)) अणु
		dev_err(&pdev->dev, "failed getting clock\n");
		error = PTR_ERR(tsc->clk);
		जाओ err_unmap;
	पूर्ण

	input->name = MOD_NAME;
	input->phys = "lpc32xx/input0";
	input->id.bustype = BUS_HOST;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x0002;
	input->id.version = 0x0100;
	input->dev.parent = &pdev->dev;
	input->खोलो = lpc32xx_ts_खोलो;
	input->बंद = lpc32xx_ts_बंद;

	input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(input, ABS_X, LPC32XX_TSC_MIN_XY_VAL,
			     LPC32XX_TSC_MAX_XY_VAL, 0, 0);
	input_set_असल_params(input, ABS_Y, LPC32XX_TSC_MIN_XY_VAL,
			     LPC32XX_TSC_MAX_XY_VAL, 0, 0);

	input_set_drvdata(input, tsc);

	error = request_irq(tsc->irq, lpc32xx_ts_पूर्णांकerrupt,
			    0, pdev->name, tsc);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed requesting interrupt\n");
		जाओ err_put_घड़ी;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed registering input device\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tsc);
	device_init_wakeup(&pdev->dev, 1);

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(tsc->irq, tsc);
err_put_घड़ी:
	clk_put(tsc->clk);
err_unmap:
	iounmap(tsc->tsc_base);
err_release_mem:
	release_mem_region(res->start, size);
err_मुक्त_mem:
	input_मुक्त_device(input);
	kमुक्त(tsc);

	वापस error;
पूर्ण

अटल पूर्णांक lpc32xx_ts_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_tsc *tsc = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *res;

	मुक्त_irq(tsc->irq, tsc);

	input_unरेजिस्टर_device(tsc->dev);

	clk_put(tsc->clk);

	iounmap(tsc->tsc_base);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	kमुक्त(tsc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक lpc32xx_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा lpc32xx_tsc *tsc = dev_get_drvdata(dev);
	काष्ठा input_dev *input = tsc->dev;

	/*
	 * Suspend and resume can be called when the device hasn't been
	 * enabled. If there are no users that have the device खोलो, then
	 * aव्योम calling the TSC stop and start functions as the TSC
	 * isn't yet घड़ीed.
	 */
	mutex_lock(&input->mutex);

	अगर (input_device_enabled(input)) अणु
		अगर (device_may_wakeup(dev))
			enable_irq_wake(tsc->irq);
		अन्यथा
			lpc32xx_stop_tsc(tsc);
	पूर्ण

	mutex_unlock(&input->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा lpc32xx_tsc *tsc = dev_get_drvdata(dev);
	काष्ठा input_dev *input = tsc->dev;

	mutex_lock(&input->mutex);

	अगर (input_device_enabled(input)) अणु
		अगर (device_may_wakeup(dev))
			disable_irq_wake(tsc->irq);
		अन्यथा
			lpc32xx_setup_tsc(tsc);
	पूर्ण

	mutex_unlock(&input->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops lpc32xx_ts_pm_ops = अणु
	.suspend	= lpc32xx_ts_suspend,
	.resume		= lpc32xx_ts_resume,
पूर्ण;
#घोषणा LPC32XX_TS_PM_OPS (&lpc32xx_ts_pm_ops)
#अन्यथा
#घोषणा LPC32XX_TS_PM_OPS शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lpc32xx_tsc_of_match[] = अणु
	अणु .compatible = "nxp,lpc3220-tsc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc32xx_tsc_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver lpc32xx_ts_driver = अणु
	.probe		= lpc32xx_ts_probe,
	.हटाओ		= lpc32xx_ts_हटाओ,
	.driver		= अणु
		.name	= MOD_NAME,
		.pm	= LPC32XX_TS_PM_OPS,
		.of_match_table = of_match_ptr(lpc32xx_tsc_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpc32xx_ts_driver);

MODULE_AUTHOR("Kevin Wells <kevin.wells@nxp.com");
MODULE_DESCRIPTION("LPC32XX TSC Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lpc32xx_ts");
