<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2014-2015 Pengutronix, Markus Pargmann <mpa@pengutronix.de>
// Based on driver from 2011:
//   Juergen Beisert, Pengutronix <kernel@pengutronix.de>
//
// This is the driver क्रम the imx25 TCQ (Touchscreen Conversion Queue)
// connected to the imx25 ADC.

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/imx25-tsadc.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

अटल स्थिर अक्षर mx25_tcq_name[] = "mx25-tcq";

क्रमागत mx25_tcq_mode अणु
	MX25_TS_4WIRE,
पूर्ण;

काष्ठा mx25_tcq_priv अणु
	काष्ठा regmap *regs;
	काष्ठा regmap *core_regs;
	काष्ठा input_dev *idev;
	क्रमागत mx25_tcq_mode mode;
	अचिन्हित पूर्णांक pen_threshold;
	अचिन्हित पूर्णांक sample_count;
	अचिन्हित पूर्णांक expected_samples;
	अचिन्हित पूर्णांक pen_debounce;
	अचिन्हित पूर्णांक settling_समय;
	काष्ठा clk *clk;
	पूर्णांक irq;
	काष्ठा device *dev;
पूर्ण;

अटल काष्ठा regmap_config mx25_tcq_regconfig = अणु
	.fast_io = true,
	.max_रेजिस्टर = 0x5c,
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mx25_tcq_ids[] = अणु
	अणु .compatible = "fsl,imx25-tcq", पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mx25_tcq_ids);

#घोषणा TSC_4WIRE_PRE_INDEX 0
#घोषणा TSC_4WIRE_X_INDEX 1
#घोषणा TSC_4WIRE_Y_INDEX 2
#घोषणा TSC_4WIRE_POST_INDEX 3
#घोषणा TSC_4WIRE_LEAVE 4

#घोषणा MX25_TSC_DEF_THRESHOLD 80
#घोषणा TSC_MAX_SAMPLES 16

#घोषणा MX25_TSC_REPEAT_WAIT 14

क्रमागत mx25_adc_configurations अणु
	MX25_CFG_PRECHARGE = 0,
	MX25_CFG_TOUCH_DETECT,
	MX25_CFG_X_MEASUREMENT,
	MX25_CFG_Y_MEASUREMENT,
पूर्ण;

#घोषणा MX25_PRECHARGE_VALUE (\
			MX25_ADCQ_CFG_YPLL_OFF | \
			MX25_ADCQ_CFG_XNUR_OFF | \
			MX25_ADCQ_CFG_XPUL_HIGH | \
			MX25_ADCQ_CFG_REFP_INT | \
			MX25_ADCQ_CFG_IN_XP | \
			MX25_ADCQ_CFG_REFN_NGND2 | \
			MX25_ADCQ_CFG_IGS)

#घोषणा MX25_TOUCH_DETECT_VALUE (\
			MX25_ADCQ_CFG_YNLR | \
			MX25_ADCQ_CFG_YPLL_OFF | \
			MX25_ADCQ_CFG_XNUR_OFF | \
			MX25_ADCQ_CFG_XPUL_OFF | \
			MX25_ADCQ_CFG_REFP_INT | \
			MX25_ADCQ_CFG_IN_XP | \
			MX25_ADCQ_CFG_REFN_NGND2 | \
			MX25_ADCQ_CFG_PENIACK)

अटल व्योम imx25_setup_queue_cfgs(काष्ठा mx25_tcq_priv *priv,
				   अचिन्हित पूर्णांक settling_cnt)
अणु
	u32 preअक्षरge_cfg =
			MX25_PRECHARGE_VALUE |
			MX25_ADCQ_CFG_SETTLING_TIME(settling_cnt);
	u32 touch_detect_cfg =
			MX25_TOUCH_DETECT_VALUE |
			MX25_ADCQ_CFG_NOS(1) |
			MX25_ADCQ_CFG_SETTLING_TIME(settling_cnt);

	regmap_ग_लिखो(priv->core_regs, MX25_TSC_TICR, preअक्षरge_cfg);

	/* PRECHARGE */
	regmap_ग_लिखो(priv->regs, MX25_ADCQ_CFG(MX25_CFG_PRECHARGE),
		     preअक्षरge_cfg);

	/* TOUCH_DETECT */
	regmap_ग_लिखो(priv->regs, MX25_ADCQ_CFG(MX25_CFG_TOUCH_DETECT),
		     touch_detect_cfg);

	/* X Measurement */
	regmap_ग_लिखो(priv->regs, MX25_ADCQ_CFG(MX25_CFG_X_MEASUREMENT),
		     MX25_ADCQ_CFG_YPLL_OFF |
		     MX25_ADCQ_CFG_XNUR_LOW |
		     MX25_ADCQ_CFG_XPUL_HIGH |
		     MX25_ADCQ_CFG_REFP_XP |
		     MX25_ADCQ_CFG_IN_YP |
		     MX25_ADCQ_CFG_REFN_XN |
		     MX25_ADCQ_CFG_NOS(priv->sample_count) |
		     MX25_ADCQ_CFG_SETTLING_TIME(settling_cnt));

	/* Y Measurement */
	regmap_ग_लिखो(priv->regs, MX25_ADCQ_CFG(MX25_CFG_Y_MEASUREMENT),
		     MX25_ADCQ_CFG_YNLR |
		     MX25_ADCQ_CFG_YPLL_HIGH |
		     MX25_ADCQ_CFG_XNUR_OFF |
		     MX25_ADCQ_CFG_XPUL_OFF |
		     MX25_ADCQ_CFG_REFP_YP |
		     MX25_ADCQ_CFG_IN_XP |
		     MX25_ADCQ_CFG_REFN_YN |
		     MX25_ADCQ_CFG_NOS(priv->sample_count) |
		     MX25_ADCQ_CFG_SETTLING_TIME(settling_cnt));

	/* Enable the touch detection right now */
	regmap_ग_लिखो(priv->core_regs, MX25_TSC_TICR, touch_detect_cfg |
		     MX25_ADCQ_CFG_IGS);
पूर्ण

अटल पूर्णांक imx25_setup_queue_4wire(काष्ठा mx25_tcq_priv *priv,
				   अचिन्हित settling_cnt, पूर्णांक *items)
अणु
	imx25_setup_queue_cfgs(priv, settling_cnt);

	/* Setup the conversion queue */
	regmap_ग_लिखो(priv->regs, MX25_ADCQ_ITEM_7_0,
		     MX25_ADCQ_ITEM(0, MX25_CFG_PRECHARGE) |
		     MX25_ADCQ_ITEM(1, MX25_CFG_TOUCH_DETECT) |
		     MX25_ADCQ_ITEM(2, MX25_CFG_X_MEASUREMENT) |
		     MX25_ADCQ_ITEM(3, MX25_CFG_Y_MEASUREMENT) |
		     MX25_ADCQ_ITEM(4, MX25_CFG_PRECHARGE) |
		     MX25_ADCQ_ITEM(5, MX25_CFG_TOUCH_DETECT));

	/*
	 * We measure X/Y with 'sample_count' number of samples and execute a
	 * touch detection twice, with 1 sample each
	 */
	priv->expected_samples = priv->sample_count * 2 + 2;
	*items = 6;

	वापस 0;
पूर्ण

अटल व्योम mx25_tcq_disable_touch_irq(काष्ठा mx25_tcq_priv *priv)
अणु
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_PDMSK,
			   MX25_ADCQ_CR_PDMSK);
पूर्ण

अटल व्योम mx25_tcq_enable_touch_irq(काष्ठा mx25_tcq_priv *priv)
अणु
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_PDMSK, 0);
पूर्ण

अटल व्योम mx25_tcq_disable_fअगरo_irq(काष्ठा mx25_tcq_priv *priv)
अणु
	regmap_update_bits(priv->regs, MX25_ADCQ_MR, MX25_ADCQ_MR_FDRY_IRQ,
			   MX25_ADCQ_MR_FDRY_IRQ);
पूर्ण

अटल व्योम mx25_tcq_enable_fअगरo_irq(काष्ठा mx25_tcq_priv *priv)
अणु
	regmap_update_bits(priv->regs, MX25_ADCQ_MR, MX25_ADCQ_MR_FDRY_IRQ, 0);
पूर्ण

अटल व्योम mx25_tcq_क्रमce_queue_start(काष्ठा mx25_tcq_priv *priv)
अणु
	regmap_update_bits(priv->regs, MX25_ADCQ_CR,
			   MX25_ADCQ_CR_FQS,
			   MX25_ADCQ_CR_FQS);
पूर्ण

अटल व्योम mx25_tcq_क्रमce_queue_stop(काष्ठा mx25_tcq_priv *priv)
अणु
	regmap_update_bits(priv->regs, MX25_ADCQ_CR,
			   MX25_ADCQ_CR_FQS, 0);
पूर्ण

अटल व्योम mx25_tcq_fअगरo_reset(काष्ठा mx25_tcq_priv *priv)
अणु
	u32 tcqcr;

	regmap_पढ़ो(priv->regs, MX25_ADCQ_CR, &tcqcr);
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_FRST,
			   MX25_ADCQ_CR_FRST);
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_FRST, 0);
	regmap_ग_लिखो(priv->regs, MX25_ADCQ_CR, tcqcr);
पूर्ण

अटल व्योम mx25_tcq_re_enable_touch_detection(काष्ठा mx25_tcq_priv *priv)
अणु
	/* stop the queue from looping */
	mx25_tcq_क्रमce_queue_stop(priv);

	/* क्रम a clean touch detection, preload the X plane */
	regmap_ग_लिखो(priv->core_regs, MX25_TSC_TICR, MX25_PRECHARGE_VALUE);

	/* waste some समय now to pre-load the X plate to high voltage */
	mx25_tcq_fअगरo_reset(priv);

	/* re-enable the detection right now */
	regmap_ग_लिखो(priv->core_regs, MX25_TSC_TICR,
		     MX25_TOUCH_DETECT_VALUE | MX25_ADCQ_CFG_IGS);

	regmap_update_bits(priv->regs, MX25_ADCQ_SR, MX25_ADCQ_SR_PD,
			   MX25_ADCQ_SR_PD);

	/* enable the pen करोwn event to be a source क्रम the पूर्णांकerrupt */
	regmap_update_bits(priv->regs, MX25_ADCQ_MR, MX25_ADCQ_MR_PD_IRQ, 0);

	/* lets fire the next IRQ अगर someone touches the touchscreen */
	mx25_tcq_enable_touch_irq(priv);
पूर्ण

अटल व्योम mx25_tcq_create_event_क्रम_4wire(काष्ठा mx25_tcq_priv *priv,
					    u32 *sample_buf,
					    अचिन्हित पूर्णांक samples)
अणु
	अचिन्हित पूर्णांक x_pos = 0;
	अचिन्हित पूर्णांक y_pos = 0;
	अचिन्हित पूर्णांक touch_pre = 0;
	अचिन्हित पूर्णांक touch_post = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < samples; i++) अणु
		अचिन्हित पूर्णांक index = MX25_ADCQ_FIFO_ID(sample_buf[i]);
		अचिन्हित पूर्णांक val = MX25_ADCQ_FIFO_DATA(sample_buf[i]);

		चयन (index) अणु
		हाल 1:
			touch_pre = val;
			अवरोध;
		हाल 2:
			x_pos = val;
			अवरोध;
		हाल 3:
			y_pos = val;
			अवरोध;
		हाल 5:
			touch_post = val;
			अवरोध;
		शेष:
			dev_dbg(priv->dev, "Dropped samples because of invalid index %d\n",
				index);
			वापस;
		पूर्ण
	पूर्ण

	अगर (samples != 0) अणु
		/*
		 * only अगर both touch measures are below a threshold,
		 * the position is valid
		 */
		अगर (touch_pre < priv->pen_threshold &&
		    touch_post < priv->pen_threshold) अणु
			/* valid samples, generate a report */
			x_pos /= priv->sample_count;
			y_pos /= priv->sample_count;
			input_report_असल(priv->idev, ABS_X, x_pos);
			input_report_असल(priv->idev, ABS_Y, y_pos);
			input_report_key(priv->idev, BTN_TOUCH, 1);
			input_sync(priv->idev);

			/* get next sample */
			mx25_tcq_enable_fअगरo_irq(priv);
		पूर्ण अन्यथा अगर (touch_pre >= priv->pen_threshold &&
			   touch_post >= priv->pen_threshold) अणु
			/*
			 * अगर both samples are invalid,
			 * generate a release report
			 */
			input_report_key(priv->idev, BTN_TOUCH, 0);
			input_sync(priv->idev);
			mx25_tcq_re_enable_touch_detection(priv);
		पूर्ण अन्यथा अणु
			/*
			 * अगर only one of both touch measurements are
			 * below the threshold, still some bouncing
			 * happens. Take additional samples in this
			 * हाल to be sure
			 */
			mx25_tcq_enable_fअगरo_irq(priv);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t mx25_tcq_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mx25_tcq_priv *priv = dev_id;
	u32 sample_buf[TSC_MAX_SAMPLES];
	अचिन्हित पूर्णांक samples;
	u32 stats;
	अचिन्हित पूर्णांक i;

	/*
	 * Check how many samples are available. We always have to पढ़ो exactly
	 * sample_count samples from the fअगरo, or a multiple of sample_count.
	 * Otherwise we mixup samples पूर्णांकo dअगरferent touch events.
	 */
	regmap_पढ़ो(priv->regs, MX25_ADCQ_SR, &stats);
	samples = MX25_ADCQ_SR_FDN(stats);
	samples -= samples % priv->sample_count;

	अगर (!samples)
		वापस IRQ_HANDLED;

	क्रम (i = 0; i != samples; ++i)
		regmap_पढ़ो(priv->regs, MX25_ADCQ_FIFO, &sample_buf[i]);

	mx25_tcq_create_event_क्रम_4wire(priv, sample_buf, samples);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mx25_tcq_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mx25_tcq_priv *priv = dev_id;
	u32 stat;
	पूर्णांक ret = IRQ_HANDLED;

	regmap_पढ़ो(priv->regs, MX25_ADCQ_SR, &stat);

	अगर (stat & (MX25_ADCQ_SR_FRR | MX25_ADCQ_SR_FUR | MX25_ADCQ_SR_FOR))
		mx25_tcq_re_enable_touch_detection(priv);

	अगर (stat & MX25_ADCQ_SR_PD) अणु
		mx25_tcq_disable_touch_irq(priv);
		mx25_tcq_क्रमce_queue_start(priv);
		mx25_tcq_enable_fअगरo_irq(priv);
	पूर्ण

	अगर (stat & MX25_ADCQ_SR_FDRY) अणु
		mx25_tcq_disable_fअगरo_irq(priv);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	regmap_update_bits(priv->regs, MX25_ADCQ_SR, MX25_ADCQ_SR_FRR |
			   MX25_ADCQ_SR_FUR | MX25_ADCQ_SR_FOR |
			   MX25_ADCQ_SR_PD,
			   MX25_ADCQ_SR_FRR | MX25_ADCQ_SR_FUR |
			   MX25_ADCQ_SR_FOR | MX25_ADCQ_SR_PD);

	वापस ret;
पूर्ण

/* configure the state machine क्रम a 4-wire touchscreen */
अटल पूर्णांक mx25_tcq_init(काष्ठा mx25_tcq_priv *priv)
अणु
	u32 tgcr;
	अचिन्हित पूर्णांक ipg_भाग;
	अचिन्हित पूर्णांक adc_period;
	अचिन्हित पूर्णांक debounce_cnt;
	अचिन्हित पूर्णांक settling_cnt;
	पूर्णांक itemct;
	पूर्णांक error;

	regmap_पढ़ो(priv->core_regs, MX25_TSC_TGCR, &tgcr);
	ipg_भाग = max_t(अचिन्हित पूर्णांक, 4, MX25_TGCR_GET_ADCCLK(tgcr));
	adc_period = USEC_PER_SEC * ipg_भाग * 2 + 2;
	adc_period /= clk_get_rate(priv->clk) / 1000 + 1;
	debounce_cnt = DIV_ROUND_UP(priv->pen_debounce, adc_period * 8) - 1;
	settling_cnt = DIV_ROUND_UP(priv->settling_समय, adc_period * 8) - 1;

	/* Reset */
	regmap_ग_लिखो(priv->regs, MX25_ADCQ_CR,
		     MX25_ADCQ_CR_QRST | MX25_ADCQ_CR_FRST);
	regmap_update_bits(priv->regs, MX25_ADCQ_CR,
			   MX25_ADCQ_CR_QRST | MX25_ADCQ_CR_FRST, 0);

	/* up to 128 * 8 ADC घड़ीs are possible */
	अगर (debounce_cnt > 127)
		debounce_cnt = 127;

	/* up to 255 * 8 ADC घड़ीs are possible */
	अगर (settling_cnt > 255)
		settling_cnt = 255;

	error = imx25_setup_queue_4wire(priv, settling_cnt, &itemct);
	अगर (error)
		वापस error;

	regmap_update_bits(priv->regs, MX25_ADCQ_CR,
			   MX25_ADCQ_CR_LITEMID_MASK | MX25_ADCQ_CR_WMRK_MASK,
			   MX25_ADCQ_CR_LITEMID(itemct - 1) |
			   MX25_ADCQ_CR_WMRK(priv->expected_samples - 1));

	/* setup debounce count */
	regmap_update_bits(priv->core_regs, MX25_TSC_TGCR,
			   MX25_TGCR_PDBTIME_MASK,
			   MX25_TGCR_PDBTIME(debounce_cnt));

	/* enable debounce */
	regmap_update_bits(priv->core_regs, MX25_TSC_TGCR, MX25_TGCR_PDBEN,
			   MX25_TGCR_PDBEN);
	regmap_update_bits(priv->core_regs, MX25_TSC_TGCR, MX25_TGCR_PDEN,
			   MX25_TGCR_PDEN);

	/* enable the engine on demand */
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_QSM_MASK,
			   MX25_ADCQ_CR_QSM_FQS);

	/* Enable repeat and repeat रुको */
	regmap_update_bits(priv->regs, MX25_ADCQ_CR,
			   MX25_ADCQ_CR_RPT | MX25_ADCQ_CR_RWAIT_MASK,
			   MX25_ADCQ_CR_RPT |
			   MX25_ADCQ_CR_RWAIT(MX25_TSC_REPEAT_WAIT));

	वापस 0;
पूर्ण

अटल पूर्णांक mx25_tcq_parse_dt(काष्ठा platक्रमm_device *pdev,
			     काष्ठा mx25_tcq_priv *priv)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 wires;
	पूर्णांक error;

	/* Setup शेषs */
	priv->pen_threshold = 500;
	priv->sample_count = 3;
	priv->pen_debounce = 1000000;
	priv->settling_समय = 250000;

	error = of_property_पढ़ो_u32(np, "fsl,wires", &wires);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to find fsl,wires properties\n");
		वापस error;
	पूर्ण

	अगर (wires == 4) अणु
		priv->mode = MX25_TS_4WIRE;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "%u-wire mode not supported\n", wires);
		वापस -EINVAL;
	पूर्ण

	/* These are optional, we करोn't care about the वापस values */
	of_property_पढ़ो_u32(np, "fsl,pen-threshold", &priv->pen_threshold);
	of_property_पढ़ो_u32(np, "fsl,settling-time-ns", &priv->settling_समय);
	of_property_पढ़ो_u32(np, "fsl,pen-debounce-ns", &priv->pen_debounce);

	वापस 0;
पूर्ण

अटल पूर्णांक mx25_tcq_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा device *dev = &idev->dev;
	काष्ठा mx25_tcq_priv *priv = dev_get_drvdata(dev);
	पूर्णांक error;

	error = clk_prepare_enable(priv->clk);
	अगर (error) अणु
		dev_err(dev, "Failed to enable ipg clock\n");
		वापस error;
	पूर्ण

	error = mx25_tcq_init(priv);
	अगर (error) अणु
		dev_err(dev, "Failed to init tcq\n");
		clk_disable_unprepare(priv->clk);
		वापस error;
	पूर्ण

	mx25_tcq_re_enable_touch_detection(priv);

	वापस 0;
पूर्ण

अटल व्योम mx25_tcq_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा mx25_tcq_priv *priv = input_get_drvdata(idev);

	mx25_tcq_क्रमce_queue_stop(priv);
	mx25_tcq_disable_touch_irq(priv);
	mx25_tcq_disable_fअगरo_irq(priv);
	clk_disable_unprepare(priv->clk);
पूर्ण

अटल पूर्णांक mx25_tcq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा input_dev *idev;
	काष्ठा mx25_tcq_priv *priv;
	काष्ठा mx25_tsadc *tsadc = dev_get_drvdata(dev->parent);
	व्योम __iomem *mem;
	पूर्णांक error;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->dev = dev;

	mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	error = mx25_tcq_parse_dt(pdev, priv);
	अगर (error)
		वापस error;

	priv->regs = devm_regmap_init_mmio(dev, mem, &mx25_tcq_regconfig);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "Failed to initialize regmap\n");
		वापस PTR_ERR(priv->regs);
	पूर्ण

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq <= 0)
		वापस priv->irq;

	idev = devm_input_allocate_device(dev);
	अगर (!idev) अणु
		dev_err(dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	idev->name = mx25_tcq_name;
	input_set_capability(idev, EV_KEY, BTN_TOUCH);
	input_set_असल_params(idev, ABS_X, 0, 0xfff, 0, 0);
	input_set_असल_params(idev, ABS_Y, 0, 0xfff, 0, 0);

	idev->id.bustype = BUS_HOST;
	idev->खोलो = mx25_tcq_खोलो;
	idev->बंद = mx25_tcq_बंद;

	priv->idev = idev;
	input_set_drvdata(idev, priv);

	priv->core_regs = tsadc->regs;
	अगर (!priv->core_regs)
		वापस -EINVAL;

	priv->clk = tsadc->clk;
	अगर (!priv->clk)
		वापस -EINVAL;

	platक्रमm_set_drvdata(pdev, priv);

	error = devm_request_thपढ़ोed_irq(dev, priv->irq, mx25_tcq_irq,
					  mx25_tcq_irq_thपढ़ो, 0, pdev->name,
					  priv);
	अगर (error) अणु
		dev_err(dev, "Failed requesting IRQ\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(idev);
	अगर (error) अणु
		dev_err(dev, "Failed to register input device\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mx25_tcq_driver = अणु
	.driver		= अणु
		.name	= "mx25-tcq",
		.of_match_table = mx25_tcq_ids,
	पूर्ण,
	.probe		= mx25_tcq_probe,
पूर्ण;
module_platक्रमm_driver(mx25_tcq_driver);

MODULE_DESCRIPTION("TS input driver for Freescale mx25");
MODULE_AUTHOR("Markus Pargmann <mpa@pengutronix.de>");
MODULE_LICENSE("GPL v2");
