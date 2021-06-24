<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale i.MX6UL touchscreen controller driver
//
// Copyright (C) 2015 Freescale Semiconductor, Inc.

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>

/* ADC configuration रेजिस्टरs field define */
#घोषणा ADC_AIEN		(0x1 << 7)
#घोषणा ADC_CONV_DISABLE	0x1F
#घोषणा ADC_AVGE		(0x1 << 5)
#घोषणा ADC_CAL			(0x1 << 7)
#घोषणा ADC_CALF		0x2
#घोषणा ADC_12BIT_MODE		(0x2 << 2)
#घोषणा ADC_CONV_MODE_MASK	(0x3 << 2)
#घोषणा ADC_IPG_CLK		0x00
#घोषणा ADC_INPUT_CLK_MASK	0x3
#घोषणा ADC_CLK_DIV_8		(0x03 << 5)
#घोषणा ADC_CLK_DIV_MASK	(0x3 << 5)
#घोषणा ADC_SHORT_SAMPLE_MODE	(0x0 << 4)
#घोषणा ADC_SAMPLE_MODE_MASK	(0x1 << 4)
#घोषणा ADC_HARDWARE_TRIGGER	(0x1 << 13)
#घोषणा ADC_AVGS_SHIFT		14
#घोषणा ADC_AVGS_MASK		(0x3 << 14)
#घोषणा SELECT_CHANNEL_4	0x04
#घोषणा SELECT_CHANNEL_1	0x01
#घोषणा DISABLE_CONVERSION_INT	(0x0 << 7)

/* ADC रेजिस्टरs */
#घोषणा REG_ADC_HC0		0x00
#घोषणा REG_ADC_HC1		0x04
#घोषणा REG_ADC_HC2		0x08
#घोषणा REG_ADC_HC3		0x0C
#घोषणा REG_ADC_HC4		0x10
#घोषणा REG_ADC_HS		0x14
#घोषणा REG_ADC_R0		0x18
#घोषणा REG_ADC_CFG		0x2C
#घोषणा REG_ADC_GC		0x30
#घोषणा REG_ADC_GS		0x34

#घोषणा ADC_TIMEOUT		msecs_to_jअगरfies(100)

/* TSC रेजिस्टरs */
#घोषणा REG_TSC_BASIC_SETING	0x00
#घोषणा REG_TSC_PRE_CHARGE_TIME	0x10
#घोषणा REG_TSC_FLOW_CONTROL	0x20
#घोषणा REG_TSC_MEASURE_VALUE	0x30
#घोषणा REG_TSC_INT_EN		0x40
#घोषणा REG_TSC_INT_SIG_EN	0x50
#घोषणा REG_TSC_INT_STATUS	0x60
#घोषणा REG_TSC_DEBUG_MODE	0x70
#घोषणा REG_TSC_DEBUG_MODE2	0x80

/* TSC configuration रेजिस्टरs field define */
#घोषणा DETECT_4_WIRE_MODE	(0x0 << 4)
#घोषणा AUTO_MEASURE		0x1
#घोषणा MEASURE_SIGNAL		0x1
#घोषणा DETECT_SIGNAL		(0x1 << 4)
#घोषणा VALID_SIGNAL		(0x1 << 8)
#घोषणा MEASURE_INT_EN		0x1
#घोषणा MEASURE_SIG_EN		0x1
#घोषणा VALID_SIG_EN		(0x1 << 8)
#घोषणा DE_GLITCH_2		(0x2 << 29)
#घोषणा START_SENSE		(0x1 << 12)
#घोषणा TSC_DISABLE		(0x1 << 16)
#घोषणा DETECT_MODE		0x2

काष्ठा imx6ul_tsc अणु
	काष्ठा device *dev;
	काष्ठा input_dev *input;
	व्योम __iomem *tsc_regs;
	व्योम __iomem *adc_regs;
	काष्ठा clk *tsc_clk;
	काष्ठा clk *adc_clk;
	काष्ठा gpio_desc *xnur_gpio;

	u32 measure_delay_समय;
	u32 pre_अक्षरge_समय;
	bool average_enable;
	u32 average_select;

	काष्ठा completion completion;
पूर्ण;

/*
 * TSC module need ADC to get the measure value. So
 * beक्रमe config TSC, we should initialize ADC module.
 */
अटल पूर्णांक imx6ul_adc_init(काष्ठा imx6ul_tsc *tsc)
अणु
	u32 adc_hc = 0;
	u32 adc_gc;
	u32 adc_gs;
	u32 adc_cfg;
	अचिन्हित दीर्घ समयout;

	reinit_completion(&tsc->completion);

	adc_cfg = पढ़ोl(tsc->adc_regs + REG_ADC_CFG);
	adc_cfg &= ~(ADC_CONV_MODE_MASK | ADC_INPUT_CLK_MASK);
	adc_cfg |= ADC_12BIT_MODE | ADC_IPG_CLK;
	adc_cfg &= ~(ADC_CLK_DIV_MASK | ADC_SAMPLE_MODE_MASK);
	adc_cfg |= ADC_CLK_DIV_8 | ADC_SHORT_SAMPLE_MODE;
	अगर (tsc->average_enable) अणु
		adc_cfg &= ~ADC_AVGS_MASK;
		adc_cfg |= (tsc->average_select) << ADC_AVGS_SHIFT;
	पूर्ण
	adc_cfg &= ~ADC_HARDWARE_TRIGGER;
	ग_लिखोl(adc_cfg, tsc->adc_regs + REG_ADC_CFG);

	/* enable calibration पूर्णांकerrupt */
	adc_hc |= ADC_AIEN;
	adc_hc |= ADC_CONV_DISABLE;
	ग_लिखोl(adc_hc, tsc->adc_regs + REG_ADC_HC0);

	/* start ADC calibration */
	adc_gc = पढ़ोl(tsc->adc_regs + REG_ADC_GC);
	adc_gc |= ADC_CAL;
	अगर (tsc->average_enable)
		adc_gc |= ADC_AVGE;
	ग_लिखोl(adc_gc, tsc->adc_regs + REG_ADC_GC);

	समयout = रुको_क्रम_completion_समयout
			(&tsc->completion, ADC_TIMEOUT);
	अगर (समयout == 0) अणु
		dev_err(tsc->dev, "Timeout for adc calibration\n");
		वापस -ETIMEDOUT;
	पूर्ण

	adc_gs = पढ़ोl(tsc->adc_regs + REG_ADC_GS);
	अगर (adc_gs & ADC_CALF) अणु
		dev_err(tsc->dev, "ADC calibration failed\n");
		वापस -EINVAL;
	पूर्ण

	/* TSC need the ADC work in hardware trigger */
	adc_cfg = पढ़ोl(tsc->adc_regs + REG_ADC_CFG);
	adc_cfg |= ADC_HARDWARE_TRIGGER;
	ग_लिखोl(adc_cfg, tsc->adc_regs + REG_ADC_CFG);

	वापस 0;
पूर्ण

/*
 * This is a TSC workaround. Currently TSC misconnect two
 * ADC channels, this function remap channel configure क्रम
 * hardware trigger.
 */
अटल व्योम imx6ul_tsc_channel_config(काष्ठा imx6ul_tsc *tsc)
अणु
	u32 adc_hc0, adc_hc1, adc_hc2, adc_hc3, adc_hc4;

	adc_hc0 = DISABLE_CONVERSION_INT;
	ग_लिखोl(adc_hc0, tsc->adc_regs + REG_ADC_HC0);

	adc_hc1 = DISABLE_CONVERSION_INT | SELECT_CHANNEL_4;
	ग_लिखोl(adc_hc1, tsc->adc_regs + REG_ADC_HC1);

	adc_hc2 = DISABLE_CONVERSION_INT;
	ग_लिखोl(adc_hc2, tsc->adc_regs + REG_ADC_HC2);

	adc_hc3 = DISABLE_CONVERSION_INT | SELECT_CHANNEL_1;
	ग_लिखोl(adc_hc3, tsc->adc_regs + REG_ADC_HC3);

	adc_hc4 = DISABLE_CONVERSION_INT;
	ग_लिखोl(adc_hc4, tsc->adc_regs + REG_ADC_HC4);
पूर्ण

/*
 * TSC setting, confige the pre-अक्षरge समय and measure delay समय.
 * dअगरferent touch screen may need dअगरferent pre-अक्षरge समय and
 * measure delay समय.
 */
अटल व्योम imx6ul_tsc_set(काष्ठा imx6ul_tsc *tsc)
अणु
	u32 basic_setting = 0;
	u32 start;

	basic_setting |= tsc->measure_delay_समय << 8;
	basic_setting |= DETECT_4_WIRE_MODE | AUTO_MEASURE;
	ग_लिखोl(basic_setting, tsc->tsc_regs + REG_TSC_BASIC_SETING);

	ग_लिखोl(DE_GLITCH_2, tsc->tsc_regs + REG_TSC_DEBUG_MODE2);

	ग_लिखोl(tsc->pre_अक्षरge_समय, tsc->tsc_regs + REG_TSC_PRE_CHARGE_TIME);
	ग_लिखोl(MEASURE_INT_EN, tsc->tsc_regs + REG_TSC_INT_EN);
	ग_लिखोl(MEASURE_SIG_EN | VALID_SIG_EN,
		tsc->tsc_regs + REG_TSC_INT_SIG_EN);

	/* start sense detection */
	start = पढ़ोl(tsc->tsc_regs + REG_TSC_FLOW_CONTROL);
	start |= START_SENSE;
	start &= ~TSC_DISABLE;
	ग_लिखोl(start, tsc->tsc_regs + REG_TSC_FLOW_CONTROL);
पूर्ण

अटल पूर्णांक imx6ul_tsc_init(काष्ठा imx6ul_tsc *tsc)
अणु
	पूर्णांक err;

	err = imx6ul_adc_init(tsc);
	अगर (err)
		वापस err;
	imx6ul_tsc_channel_config(tsc);
	imx6ul_tsc_set(tsc);

	वापस 0;
पूर्ण

अटल व्योम imx6ul_tsc_disable(काष्ठा imx6ul_tsc *tsc)
अणु
	u32 tsc_flow;
	u32 adc_cfg;

	/* TSC controller enters to idle status */
	tsc_flow = पढ़ोl(tsc->tsc_regs + REG_TSC_FLOW_CONTROL);
	tsc_flow |= TSC_DISABLE;
	ग_लिखोl(tsc_flow, tsc->tsc_regs + REG_TSC_FLOW_CONTROL);

	/* ADC controller enters to stop mode */
	adc_cfg = पढ़ोl(tsc->adc_regs + REG_ADC_HC0);
	adc_cfg |= ADC_CONV_DISABLE;
	ग_लिखोl(adc_cfg, tsc->adc_regs + REG_ADC_HC0);
पूर्ण

/* Delay some समय (max 2ms), रुको the pre-अक्षरge करोne. */
अटल bool tsc_रुको_detect_mode(काष्ठा imx6ul_tsc *tsc)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(2);
	u32 state_machine;
	u32 debug_mode2;

	करो अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस false;

		usleep_range(200, 400);
		debug_mode2 = पढ़ोl(tsc->tsc_regs + REG_TSC_DEBUG_MODE2);
		state_machine = (debug_mode2 >> 20) & 0x7;
	पूर्ण जबतक (state_machine != DETECT_MODE);

	usleep_range(200, 400);
	वापस true;
पूर्ण

अटल irqवापस_t tsc_irq_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx6ul_tsc *tsc = dev_id;
	u32 status;
	u32 value;
	u32 x, y;
	u32 start;

	status = पढ़ोl(tsc->tsc_regs + REG_TSC_INT_STATUS);

	/* ग_लिखो 1 to clear the bit measure-संकेत */
	ग_लिखोl(MEASURE_SIGNAL | DETECT_SIGNAL,
		tsc->tsc_regs + REG_TSC_INT_STATUS);

	/* It's a HW self-clean bit. Set this bit and start sense detection */
	start = पढ़ोl(tsc->tsc_regs + REG_TSC_FLOW_CONTROL);
	start |= START_SENSE;
	ग_लिखोl(start, tsc->tsc_regs + REG_TSC_FLOW_CONTROL);

	अगर (status & MEASURE_SIGNAL) अणु
		value = पढ़ोl(tsc->tsc_regs + REG_TSC_MEASURE_VALUE);
		x = (value >> 16) & 0x0fff;
		y = value & 0x0fff;

		/*
		 * In detect mode, we can get the xnur gpio value,
		 * otherwise assume contact is stiull active.
		 */
		अगर (!tsc_रुको_detect_mode(tsc) ||
		    gpiod_get_value_cansleep(tsc->xnur_gpio)) अणु
			input_report_key(tsc->input, BTN_TOUCH, 1);
			input_report_असल(tsc->input, ABS_X, x);
			input_report_असल(tsc->input, ABS_Y, y);
		पूर्ण अन्यथा अणु
			input_report_key(tsc->input, BTN_TOUCH, 0);
		पूर्ण

		input_sync(tsc->input);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t adc_irq_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx6ul_tsc *tsc = dev_id;
	u32 coco;

	coco = पढ़ोl(tsc->adc_regs + REG_ADC_HS);
	अगर (coco & 0x01) अणु
		पढ़ोl(tsc->adc_regs + REG_ADC_R0);
		complete(&tsc->completion);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक imx6ul_tsc_start(काष्ठा imx6ul_tsc *tsc)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(tsc->adc_clk);
	अगर (err) अणु
		dev_err(tsc->dev,
			"Could not prepare or enable the adc clock: %d\n",
			err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(tsc->tsc_clk);
	अगर (err) अणु
		dev_err(tsc->dev,
			"Could not prepare or enable the tsc clock: %d\n",
			err);
		जाओ disable_adc_clk;
	पूर्ण

	err = imx6ul_tsc_init(tsc);
	अगर (err)
		जाओ disable_tsc_clk;

	वापस 0;

disable_tsc_clk:
	clk_disable_unprepare(tsc->tsc_clk);
disable_adc_clk:
	clk_disable_unprepare(tsc->adc_clk);
	वापस err;
पूर्ण

अटल व्योम imx6ul_tsc_stop(काष्ठा imx6ul_tsc *tsc)
अणु
	imx6ul_tsc_disable(tsc);

	clk_disable_unprepare(tsc->tsc_clk);
	clk_disable_unprepare(tsc->adc_clk);
पूर्ण


अटल पूर्णांक imx6ul_tsc_खोलो(काष्ठा input_dev *input_dev)
अणु
	काष्ठा imx6ul_tsc *tsc = input_get_drvdata(input_dev);

	वापस imx6ul_tsc_start(tsc);
पूर्ण

अटल व्योम imx6ul_tsc_बंद(काष्ठा input_dev *input_dev)
अणु
	काष्ठा imx6ul_tsc *tsc = input_get_drvdata(input_dev);

	imx6ul_tsc_stop(tsc);
पूर्ण

अटल पूर्णांक imx6ul_tsc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा imx6ul_tsc *tsc;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;
	पूर्णांक tsc_irq;
	पूर्णांक adc_irq;
	u32 average_samples;

	tsc = devm_kzalloc(&pdev->dev, माप(*tsc), GFP_KERNEL);
	अगर (!tsc)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = "iMX6UL Touchscreen Controller";
	input_dev->id.bustype = BUS_HOST;

	input_dev->खोलो = imx6ul_tsc_खोलो;
	input_dev->बंद = imx6ul_tsc_बंद;

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X, 0, 0xFFF, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, 0xFFF, 0, 0);

	input_set_drvdata(input_dev, tsc);

	tsc->dev = &pdev->dev;
	tsc->input = input_dev;
	init_completion(&tsc->completion);

	tsc->xnur_gpio = devm_gpiod_get(&pdev->dev, "xnur", GPIOD_IN);
	अगर (IS_ERR(tsc->xnur_gpio)) अणु
		err = PTR_ERR(tsc->xnur_gpio);
		dev_err(&pdev->dev,
			"failed to request GPIO tsc_X- (xnur): %d\n", err);
		वापस err;
	पूर्ण

	tsc->tsc_regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(tsc->tsc_regs)) अणु
		err = PTR_ERR(tsc->tsc_regs);
		dev_err(&pdev->dev, "failed to remap tsc memory: %d\n", err);
		वापस err;
	पूर्ण

	tsc->adc_regs = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(tsc->adc_regs)) अणु
		err = PTR_ERR(tsc->adc_regs);
		dev_err(&pdev->dev, "failed to remap adc memory: %d\n", err);
		वापस err;
	पूर्ण

	tsc->tsc_clk = devm_clk_get(&pdev->dev, "tsc");
	अगर (IS_ERR(tsc->tsc_clk)) अणु
		err = PTR_ERR(tsc->tsc_clk);
		dev_err(&pdev->dev, "failed getting tsc clock: %d\n", err);
		वापस err;
	पूर्ण

	tsc->adc_clk = devm_clk_get(&pdev->dev, "adc");
	अगर (IS_ERR(tsc->adc_clk)) अणु
		err = PTR_ERR(tsc->adc_clk);
		dev_err(&pdev->dev, "failed getting adc clock: %d\n", err);
		वापस err;
	पूर्ण

	tsc_irq = platक्रमm_get_irq(pdev, 0);
	अगर (tsc_irq < 0)
		वापस tsc_irq;

	adc_irq = platक्रमm_get_irq(pdev, 1);
	अगर (adc_irq < 0)
		वापस adc_irq;

	err = devm_request_thपढ़ोed_irq(tsc->dev, tsc_irq,
					शून्य, tsc_irq_fn, IRQF_ONESHOT,
					dev_name(&pdev->dev), tsc);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"failed requesting tsc irq %d: %d\n",
			tsc_irq, err);
		वापस err;
	पूर्ण

	err = devm_request_irq(tsc->dev, adc_irq, adc_irq_fn, 0,
				dev_name(&pdev->dev), tsc);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"failed requesting adc irq %d: %d\n",
			adc_irq, err);
		वापस err;
	पूर्ण

	err = of_property_पढ़ो_u32(np, "measure-delay-time",
				   &tsc->measure_delay_समय);
	अगर (err)
		tsc->measure_delay_समय = 0xffff;

	err = of_property_पढ़ो_u32(np, "pre-charge-time",
				   &tsc->pre_अक्षरge_समय);
	अगर (err)
		tsc->pre_अक्षरge_समय = 0xfff;

	err = of_property_पढ़ो_u32(np, "touchscreen-average-samples",
				   &average_samples);
	अगर (err)
		average_samples = 1;

	चयन (average_samples) अणु
	हाल 1:
		tsc->average_enable = false;
		tsc->average_select = 0; /* value unused; initialize anyway */
		अवरोध;
	हाल 4:
	हाल 8:
	हाल 16:
	हाल 32:
		tsc->average_enable = true;
		tsc->average_select = ilog2(average_samples) - 2;
		अवरोध;
	शेष:
		dev_err(&pdev->dev,
			"touchscreen-average-samples (%u) must be 1, 4, 8, 16 or 32\n",
			average_samples);
		वापस -EINVAL;
	पूर्ण

	err = input_रेजिस्टर_device(tsc->input);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"failed to register input device: %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tsc);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx6ul_tsc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा imx6ul_tsc *tsc = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = tsc->input;

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		imx6ul_tsc_stop(tsc);

	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx6ul_tsc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा imx6ul_tsc *tsc = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = tsc->input;
	पूर्णांक retval = 0;

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		retval = imx6ul_tsc_start(tsc);

	mutex_unlock(&input_dev->mutex);

	वापस retval;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(imx6ul_tsc_pm_ops,
			 imx6ul_tsc_suspend, imx6ul_tsc_resume);

अटल स्थिर काष्ठा of_device_id imx6ul_tsc_match[] = अणु
	अणु .compatible = "fsl,imx6ul-tsc", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx6ul_tsc_match);

अटल काष्ठा platक्रमm_driver imx6ul_tsc_driver = अणु
	.driver		= अणु
		.name	= "imx6ul-tsc",
		.of_match_table	= imx6ul_tsc_match,
		.pm	= &imx6ul_tsc_pm_ops,
	पूर्ण,
	.probe		= imx6ul_tsc_probe,
पूर्ण;
module_platक्रमm_driver(imx6ul_tsc_driver);

MODULE_AUTHOR("Haibo Chen <haibo.chen@freescale.com>");
MODULE_DESCRIPTION("Freescale i.MX6UL Touchscreen controller driver");
MODULE_LICENSE("GPL v2");
