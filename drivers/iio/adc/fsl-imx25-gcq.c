<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2015 Pengutronix, Markus Pargmann <mpa@pengutronix.de>
 *
 * This is the driver क्रम the imx25 GCQ (Generic Conversion Queue)
 * connected to the imx25 ADC.
 */

#समावेश <dt-bindings/iio/adc/fsl-imx25-gcq.h>
#समावेश <linux/clk.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/imx25-tsadc.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा MX25_GCQ_TIMEOUT (msecs_to_jअगरfies(2000))

अटल स्थिर अक्षर * स्थिर driver_name = "mx25-gcq";

क्रमागत mx25_gcq_cfgs अणु
	MX25_CFG_XP = 0,
	MX25_CFG_YP,
	MX25_CFG_XN,
	MX25_CFG_YN,
	MX25_CFG_WIPER,
	MX25_CFG_INAUX0,
	MX25_CFG_INAUX1,
	MX25_CFG_INAUX2,
	MX25_NUM_CFGS,
पूर्ण;

काष्ठा mx25_gcq_priv अणु
	काष्ठा regmap *regs;
	काष्ठा completion completed;
	काष्ठा clk *clk;
	पूर्णांक irq;
	काष्ठा regulator *vref[4];
	u32 channel_vref_mv[MX25_NUM_CFGS];
	/*
	 * Lock to protect the device state during a potential concurrent
	 * पढ़ो access from userspace. Reading a raw value requires a sequence
	 * of रेजिस्टर ग_लिखोs, then a रुको क्रम a completion callback,
	 * and finally a रेजिस्टर पढ़ो, during which userspace could issue
	 * another पढ़ो request. This lock protects a पढ़ो access from
	 * ocurring beक्रमe another one has finished.
	 */
	काष्ठा mutex lock;
पूर्ण;

#घोषणा MX25_CQG_CHAN(chan, id) अणु\
	.type = IIO_VOLTAGE,\
	.indexed = 1,\
	.channel = chan,\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_SCALE),\
	.datasheet_name = id,\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mx25_gcq_channels[MX25_NUM_CFGS] = अणु
	MX25_CQG_CHAN(MX25_CFG_XP, "xp"),
	MX25_CQG_CHAN(MX25_CFG_YP, "yp"),
	MX25_CQG_CHAN(MX25_CFG_XN, "xn"),
	MX25_CQG_CHAN(MX25_CFG_YN, "yn"),
	MX25_CQG_CHAN(MX25_CFG_WIPER, "wiper"),
	MX25_CQG_CHAN(MX25_CFG_INAUX0, "inaux0"),
	MX25_CQG_CHAN(MX25_CFG_INAUX1, "inaux1"),
	MX25_CQG_CHAN(MX25_CFG_INAUX2, "inaux2"),
पूर्ण;

अटल स्थिर अक्षर * स्थिर mx25_gcq_refp_names[] = अणु
	[MX25_ADC_REFP_YP] = "yp",
	[MX25_ADC_REFP_XP] = "xp",
	[MX25_ADC_REFP_INT] = "int",
	[MX25_ADC_REFP_EXT] = "ext",
पूर्ण;

अटल irqवापस_t mx25_gcq_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mx25_gcq_priv *priv = data;
	u32 stats;

	regmap_पढ़ो(priv->regs, MX25_ADCQ_SR, &stats);

	अगर (stats & MX25_ADCQ_SR_EOQ) अणु
		regmap_update_bits(priv->regs, MX25_ADCQ_MR,
				   MX25_ADCQ_MR_EOQ_IRQ, MX25_ADCQ_MR_EOQ_IRQ);
		complete(&priv->completed);
	पूर्ण

	/* Disable conversion queue run */
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_FQS, 0);

	/* Acknowledge all possible irqs */
	regmap_ग_लिखो(priv->regs, MX25_ADCQ_SR, MX25_ADCQ_SR_FRR |
		     MX25_ADCQ_SR_FUR | MX25_ADCQ_SR_FOR |
		     MX25_ADCQ_SR_EOQ | MX25_ADCQ_SR_PD);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mx25_gcq_get_raw_value(काष्ठा device *dev,
				  काष्ठा iio_chan_spec स्थिर *chan,
				  काष्ठा mx25_gcq_priv *priv,
				  पूर्णांक *val)
अणु
	दीर्घ समयout;
	u32 data;

	/* Setup the configuration we want to use */
	regmap_ग_लिखो(priv->regs, MX25_ADCQ_ITEM_7_0,
		     MX25_ADCQ_ITEM(0, chan->channel));

	regmap_update_bits(priv->regs, MX25_ADCQ_MR, MX25_ADCQ_MR_EOQ_IRQ, 0);

	/* Trigger queue क्रम one run */
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_FQS,
			   MX25_ADCQ_CR_FQS);

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&priv->completed, MX25_GCQ_TIMEOUT);
	अगर (समयout < 0) अणु
		dev_err(dev, "ADC wait for measurement failed\n");
		वापस समयout;
	पूर्ण अन्यथा अगर (समयout == 0) अणु
		dev_err(dev, "ADC timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	regmap_पढ़ो(priv->regs, MX25_ADCQ_FIFO, &data);

	*val = MX25_ADCQ_FIFO_DATA(data);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक mx25_gcq_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mx25_gcq_priv *priv = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&priv->lock);
		ret = mx25_gcq_get_raw_value(&indio_dev->dev, chan, priv, val);
		mutex_unlock(&priv->lock);
		वापस ret;

	हाल IIO_CHAN_INFO_SCALE:
		*val = priv->channel_vref_mv[chan->channel];
		*val2 = 12;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info mx25_gcq_iio_info = अणु
	.पढ़ो_raw = mx25_gcq_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mx25_gcq_regconfig = अणु
	.max_रेजिस्टर = 0x5c,
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल पूर्णांक mx25_gcq_setup_cfgs(काष्ठा platक्रमm_device *pdev,
			       काष्ठा mx25_gcq_priv *priv)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *child;
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित पूर्णांक refp_used[4] = अणुपूर्ण;
	पूर्णांक ret, i;

	/*
	 * Setup all configurations रेजिस्टरs with a शेष conversion
	 * configuration क्रम each input
	 */
	क्रम (i = 0; i < MX25_NUM_CFGS; ++i)
		regmap_ग_लिखो(priv->regs, MX25_ADCQ_CFG(i),
			     MX25_ADCQ_CFG_YPLL_OFF |
			     MX25_ADCQ_CFG_XNUR_OFF |
			     MX25_ADCQ_CFG_XPUL_OFF |
			     MX25_ADCQ_CFG_REFP_INT |
			     MX25_ADCQ_CFG_IN(i) |
			     MX25_ADCQ_CFG_REFN_NGND2);

	/*
	 * First get all regulators to store them in channel_vref_mv अगर
	 * necessary. Later we use that inक्रमmation क्रम proper IIO scale
	 * inक्रमmation.
	 */
	priv->vref[MX25_ADC_REFP_INT] = शून्य;
	priv->vref[MX25_ADC_REFP_EXT] =
		devm_regulator_get_optional(&pdev->dev, "vref-ext");
	priv->vref[MX25_ADC_REFP_XP] =
		devm_regulator_get_optional(&pdev->dev, "vref-xp");
	priv->vref[MX25_ADC_REFP_YP] =
		devm_regulator_get_optional(&pdev->dev, "vref-yp");

	क्रम_each_child_of_node(np, child) अणु
		u32 reg;
		u32 refp = MX25_ADCQ_CFG_REFP_INT;
		u32 refn = MX25_ADCQ_CFG_REFN_NGND2;

		ret = of_property_पढ़ो_u32(child, "reg", &reg);
		अगर (ret) अणु
			dev_err(dev, "Failed to get reg property\n");
			of_node_put(child);
			वापस ret;
		पूर्ण

		अगर (reg >= MX25_NUM_CFGS) अणु
			dev_err(dev,
				"reg value is greater than the number of available configuration registers\n");
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण

		of_property_पढ़ो_u32(child, "fsl,adc-refp", &refp);
		of_property_पढ़ो_u32(child, "fsl,adc-refn", &refn);

		चयन (refp) अणु
		हाल MX25_ADC_REFP_EXT:
		हाल MX25_ADC_REFP_XP:
		हाल MX25_ADC_REFP_YP:
			अगर (IS_ERR(priv->vref[refp])) अणु
				dev_err(dev, "Error, trying to use external voltage reference without a vref-%s regulator.",
					mx25_gcq_refp_names[refp]);
				of_node_put(child);
				वापस PTR_ERR(priv->vref[refp]);
			पूर्ण
			priv->channel_vref_mv[reg] =
				regulator_get_voltage(priv->vref[refp]);
			/* Conversion from uV to mV */
			priv->channel_vref_mv[reg] /= 1000;
			अवरोध;
		हाल MX25_ADC_REFP_INT:
			priv->channel_vref_mv[reg] = 2500;
			अवरोध;
		शेष:
			dev_err(dev, "Invalid positive reference %d\n", refp);
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण

		++refp_used[refp];

		/*
		 * Shअगरt the पढ़ो values to the correct positions within the
		 * रेजिस्टर.
		 */
		refp = MX25_ADCQ_CFG_REFP(refp);
		refn = MX25_ADCQ_CFG_REFN(refn);

		अगर ((refp & MX25_ADCQ_CFG_REFP_MASK) != refp) अणु
			dev_err(dev, "Invalid fsl,adc-refp property value\n");
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण
		अगर ((refn & MX25_ADCQ_CFG_REFN_MASK) != refn) अणु
			dev_err(dev, "Invalid fsl,adc-refn property value\n");
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण

		regmap_update_bits(priv->regs, MX25_ADCQ_CFG(reg),
				   MX25_ADCQ_CFG_REFP_MASK |
				   MX25_ADCQ_CFG_REFN_MASK,
				   refp | refn);
	पूर्ण
	regmap_update_bits(priv->regs, MX25_ADCQ_CR,
			   MX25_ADCQ_CR_FRST | MX25_ADCQ_CR_QRST,
			   MX25_ADCQ_CR_FRST | MX25_ADCQ_CR_QRST);

	regmap_ग_लिखो(priv->regs, MX25_ADCQ_CR,
		     MX25_ADCQ_CR_PDMSK | MX25_ADCQ_CR_QSM_FQS);

	/* Remove unused regulators */
	क्रम (i = 0; i != 4; ++i) अणु
		अगर (!refp_used[i]) अणु
			अगर (!IS_ERR_OR_शून्य(priv->vref[i]))
				devm_regulator_put(priv->vref[i]);
			priv->vref[i] = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mx25_gcq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा mx25_gcq_priv *priv;
	काष्ठा mx25_tsadc *tsadc = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *mem;
	पूर्णांक ret;
	पूर्णांक i;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*priv));
	अगर (!indio_dev)
		वापस -ENOMEM;

	priv = iio_priv(indio_dev);

	mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	priv->regs = devm_regmap_init_mmio(dev, mem, &mx25_gcq_regconfig);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "Failed to initialize regmap\n");
		वापस PTR_ERR(priv->regs);
	पूर्ण

	mutex_init(&priv->lock);

	init_completion(&priv->completed);

	ret = mx25_gcq_setup_cfgs(pdev, priv);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i != 4; ++i) अणु
		अगर (!priv->vref[i])
			जारी;

		ret = regulator_enable(priv->vref[i]);
		अगर (ret)
			जाओ err_regulator_disable;
	पूर्ण

	priv->clk = tsadc->clk;
	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clock\n");
		जाओ err_vref_disable;
	पूर्ण

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq <= 0) अणु
		ret = priv->irq;
		अगर (!ret)
			ret = -ENXIO;
		जाओ err_clk_unprepare;
	पूर्ण

	ret = request_irq(priv->irq, mx25_gcq_irq, 0, pdev->name, priv);
	अगर (ret) अणु
		dev_err(dev, "Failed requesting IRQ\n");
		जाओ err_clk_unprepare;
	पूर्ण

	indio_dev->channels = mx25_gcq_channels;
	indio_dev->num_channels = ARRAY_SIZE(mx25_gcq_channels);
	indio_dev->info = &mx25_gcq_iio_info;
	indio_dev->name = driver_name;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register iio device\n");
		जाओ err_irq_मुक्त;
	पूर्ण

	platक्रमm_set_drvdata(pdev, indio_dev);

	वापस 0;

err_irq_मुक्त:
	मुक्त_irq(priv->irq, priv);
err_clk_unprepare:
	clk_disable_unprepare(priv->clk);
err_vref_disable:
	i = 4;
err_regulator_disable:
	क्रम (; i-- > 0;) अणु
		अगर (priv->vref[i])
			regulator_disable(priv->vref[i]);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mx25_gcq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा mx25_gcq_priv *priv = iio_priv(indio_dev);
	पूर्णांक i;

	iio_device_unरेजिस्टर(indio_dev);
	मुक्त_irq(priv->irq, priv);
	clk_disable_unprepare(priv->clk);
	क्रम (i = 4; i-- > 0;) अणु
		अगर (priv->vref[i])
			regulator_disable(priv->vref[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mx25_gcq_ids[] = अणु
	अणु .compatible = "fsl,imx25-gcq", पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mx25_gcq_ids);

अटल काष्ठा platक्रमm_driver mx25_gcq_driver = अणु
	.driver		= अणु
		.name	= "mx25-gcq",
		.of_match_table = mx25_gcq_ids,
	पूर्ण,
	.probe		= mx25_gcq_probe,
	.हटाओ		= mx25_gcq_हटाओ,
पूर्ण;
module_platक्रमm_driver(mx25_gcq_driver);

MODULE_DESCRIPTION("ADC driver for Freescale mx25");
MODULE_AUTHOR("Markus Pargmann <mpa@pengutronix.de>");
MODULE_LICENSE("GPL v2");
