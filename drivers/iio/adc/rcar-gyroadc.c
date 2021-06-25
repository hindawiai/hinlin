<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Renesas R-Car GyroADC driver
 *
 * Copyright 2016 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>

#घोषणा DRIVER_NAME				"rcar-gyroadc"

/* GyroADC रेजिस्टरs. */
#घोषणा RCAR_GYROADC_MODE_SELECT		0x00
#घोषणा RCAR_GYROADC_MODE_SELECT_1_MB88101A	0x0
#घोषणा RCAR_GYROADC_MODE_SELECT_2_ADCS7476	0x1
#घोषणा RCAR_GYROADC_MODE_SELECT_3_MAX1162	0x3

#घोषणा RCAR_GYROADC_START_STOP			0x04
#घोषणा RCAR_GYROADC_START_STOP_START		BIT(0)

#घोषणा RCAR_GYROADC_CLOCK_LENGTH		0x08
#घोषणा RCAR_GYROADC_1_25MS_LENGTH		0x0c

#घोषणा RCAR_GYROADC_REALTIME_DATA(ch)		(0x10 + ((ch) * 4))
#घोषणा RCAR_GYROADC_100MS_ADDED_DATA(ch)	(0x30 + ((ch) * 4))
#घोषणा RCAR_GYROADC_10MS_AVG_DATA(ch)		(0x50 + ((ch) * 4))

#घोषणा RCAR_GYROADC_FIFO_STATUS		0x70
#घोषणा RCAR_GYROADC_FIFO_STATUS_EMPTY(ch)	BIT(0 + (4 * (ch)))
#घोषणा RCAR_GYROADC_FIFO_STATUS_FULL(ch)	BIT(1 + (4 * (ch)))
#घोषणा RCAR_GYROADC_FIFO_STATUS_ERROR(ch)	BIT(2 + (4 * (ch)))

#घोषणा RCAR_GYROADC_INTR			0x74
#घोषणा RCAR_GYROADC_INTR_INT			BIT(0)

#घोषणा RCAR_GYROADC_INTENR			0x78
#घोषणा RCAR_GYROADC_INTENR_INTEN		BIT(0)

#घोषणा RCAR_GYROADC_SAMPLE_RATE		800	/* Hz */

#घोषणा RCAR_GYROADC_RUNTIME_PM_DELAY_MS	2000

क्रमागत rcar_gyroadc_model अणु
	RCAR_GYROADC_MODEL_DEFAULT,
	RCAR_GYROADC_MODEL_R8A7792,
पूर्ण;

काष्ठा rcar_gyroadc अणु
	काष्ठा device			*dev;
	व्योम __iomem			*regs;
	काष्ठा clk			*clk;
	काष्ठा regulator		*vref[8];
	अचिन्हित पूर्णांक			num_channels;
	क्रमागत rcar_gyroadc_model		model;
	अचिन्हित पूर्णांक			mode;
	अचिन्हित पूर्णांक			sample_width;
पूर्ण;

अटल व्योम rcar_gyroadc_hw_init(काष्ठा rcar_gyroadc *priv)
अणु
	स्थिर अचिन्हित दीर्घ clk_mhz = clk_get_rate(priv->clk) / 1000000;
	स्थिर अचिन्हित दीर्घ clk_mul =
		(priv->mode == RCAR_GYROADC_MODE_SELECT_1_MB88101A) ? 10 : 5;
	अचिन्हित दीर्घ clk_len = clk_mhz * clk_mul;

	/*
	 * According to the R-Car Gen2 datasheet Rev. 1.01, Sept 08 2014,
	 * page 77-7, घड़ी length must be even number. If it's odd number,
	 * add one.
	 */
	अगर (clk_len & 1)
		clk_len++;

	/* Stop the GyroADC. */
	ग_लिखोl(0, priv->regs + RCAR_GYROADC_START_STOP);

	/* Disable IRQ on V2H. */
	अगर (priv->model == RCAR_GYROADC_MODEL_R8A7792)
		ग_लिखोl(0, priv->regs + RCAR_GYROADC_INTENR);

	/* Set mode and timing. */
	ग_लिखोl(priv->mode, priv->regs + RCAR_GYROADC_MODE_SELECT);
	ग_लिखोl(clk_len, priv->regs + RCAR_GYROADC_CLOCK_LENGTH);
	ग_लिखोl(clk_mhz * 1250, priv->regs + RCAR_GYROADC_1_25MS_LENGTH);
पूर्ण

अटल व्योम rcar_gyroadc_hw_start(काष्ठा rcar_gyroadc *priv)
अणु
	/* Start sampling. */
	ग_लिखोl(RCAR_GYROADC_START_STOP_START,
	       priv->regs + RCAR_GYROADC_START_STOP);

	/*
	 * Wait क्रम the first conversion to complete. This is दीर्घer than
	 * the 1.25 mS in the datasheet because 1.25 mS is not enough क्रम
	 * the hardware to deliver the first sample and the hardware करोes
	 * then वापस zeroes instead of valid data.
	 */
	mdelay(3);
पूर्ण

अटल व्योम rcar_gyroadc_hw_stop(काष्ठा rcar_gyroadc *priv)
अणु
	/* Stop the GyroADC. */
	ग_लिखोl(0, priv->regs + RCAR_GYROADC_START_STOP);
पूर्ण

#घोषणा RCAR_GYROADC_CHAN(_idx) अणु				\
	.type			= IIO_VOLTAGE,			\
	.indexed		= 1,				\
	.channel		= (_idx),			\
	.info_mask_separate	= BIT(IIO_CHAN_INFO_RAW) |	\
				  BIT(IIO_CHAN_INFO_SCALE),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec rcar_gyroadc_iio_channels_1[] = अणु
	RCAR_GYROADC_CHAN(0),
	RCAR_GYROADC_CHAN(1),
	RCAR_GYROADC_CHAN(2),
	RCAR_GYROADC_CHAN(3),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec rcar_gyroadc_iio_channels_2[] = अणु
	RCAR_GYROADC_CHAN(0),
	RCAR_GYROADC_CHAN(1),
	RCAR_GYROADC_CHAN(2),
	RCAR_GYROADC_CHAN(3),
	RCAR_GYROADC_CHAN(4),
	RCAR_GYROADC_CHAN(5),
	RCAR_GYROADC_CHAN(6),
	RCAR_GYROADC_CHAN(7),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec rcar_gyroadc_iio_channels_3[] = अणु
	RCAR_GYROADC_CHAN(0),
	RCAR_GYROADC_CHAN(1),
	RCAR_GYROADC_CHAN(2),
	RCAR_GYROADC_CHAN(3),
	RCAR_GYROADC_CHAN(4),
	RCAR_GYROADC_CHAN(5),
	RCAR_GYROADC_CHAN(6),
	RCAR_GYROADC_CHAN(7),
पूर्ण;

अटल पूर्णांक rcar_gyroadc_set_घातer(काष्ठा rcar_gyroadc *priv, bool on)
अणु
	काष्ठा device *dev = priv->dev;
	पूर्णांक ret;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0)
			pm_runसमय_put_noidle(dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(dev);
		ret = pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_gyroadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा rcar_gyroadc *priv = iio_priv(indio_dev);
	काष्ठा regulator *consumer;
	अचिन्हित पूर्णांक datareg = RCAR_GYROADC_REALTIME_DATA(chan->channel);
	अचिन्हित पूर्णांक vref;
	पूर्णांक ret;

	/*
	 * MB88101 is special in that it has only single regulator क्रम
	 * all four channels.
	 */
	अगर (priv->mode == RCAR_GYROADC_MODE_SELECT_1_MB88101A)
		consumer = priv->vref[0];
	अन्यथा
		consumer = priv->vref[chan->channel];

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type != IIO_VOLTAGE)
			वापस -EINVAL;

		/* Channel not connected. */
		अगर (!consumer)
			वापस -EINVAL;

		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = rcar_gyroadc_set_घातer(priv, true);
		अगर (ret < 0) अणु
			iio_device_release_direct_mode(indio_dev);
			वापस ret;
		पूर्ण

		*val = पढ़ोl(priv->regs + datareg);
		*val &= BIT(priv->sample_width) - 1;

		ret = rcar_gyroadc_set_घातer(priv, false);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/* Channel not connected. */
		अगर (!consumer)
			वापस -EINVAL;

		vref = regulator_get_voltage(consumer);
		*val = vref / 1000;
		*val2 = 1 << priv->sample_width;

		वापस IIO_VAL_FRACTIONAL;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = RCAR_GYROADC_SAMPLE_RATE;

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक rcar_gyroadc_reg_access(काष्ठा iio_dev *indio_dev,
				   अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक ग_लिखोval,
				   अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा rcar_gyroadc *priv = iio_priv(indio_dev);
	अचिन्हित पूर्णांक maxreg = RCAR_GYROADC_FIFO_STATUS;

	अगर (पढ़ोval == शून्य)
		वापस -EINVAL;

	अगर (reg % 4)
		वापस -EINVAL;

	/* Handle the V2H हाल with extra पूर्णांकerrupt block. */
	अगर (priv->model == RCAR_GYROADC_MODEL_R8A7792)
		maxreg = RCAR_GYROADC_INTENR;

	अगर (reg > maxreg)
		वापस -EINVAL;

	*पढ़ोval = पढ़ोl(priv->regs + reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info rcar_gyroadc_iio_info = अणु
	.पढ़ो_raw		= rcar_gyroadc_पढ़ो_raw,
	.debugfs_reg_access	= rcar_gyroadc_reg_access,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_gyroadc_match[] = अणु
	अणु
		/* R-Car compatible GyroADC */
		.compatible	= "renesas,rcar-gyroadc",
		.data		= (व्योम *)RCAR_GYROADC_MODEL_DEFAULT,
	पूर्ण, अणु
		/* R-Car V2H specialty with पूर्णांकerrupt रेजिस्टरs. */
		.compatible	= "renesas,r8a7792-gyroadc",
		.data		= (व्योम *)RCAR_GYROADC_MODEL_R8A7792,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rcar_gyroadc_match);

अटल स्थिर काष्ठा of_device_id rcar_gyroadc_child_match[] = अणु
	/* Mode 1 ADCs */
	अणु
		.compatible	= "fujitsu,mb88101a",
		.data		= (व्योम *)RCAR_GYROADC_MODE_SELECT_1_MB88101A,
	पूर्ण,
	/* Mode 2 ADCs */
	अणु
		.compatible	= "ti,adcs7476",
		.data		= (व्योम *)RCAR_GYROADC_MODE_SELECT_2_ADCS7476,
	पूर्ण, अणु
		.compatible	= "ti,adc121",
		.data		= (व्योम *)RCAR_GYROADC_MODE_SELECT_2_ADCS7476,
	पूर्ण, अणु
		.compatible	= "adi,ad7476",
		.data		= (व्योम *)RCAR_GYROADC_MODE_SELECT_2_ADCS7476,
	पूर्ण,
	/* Mode 3 ADCs */
	अणु
		.compatible	= "maxim,max1162",
		.data		= (व्योम *)RCAR_GYROADC_MODE_SELECT_3_MAX1162,
	पूर्ण, अणु
		.compatible	= "maxim,max11100",
		.data		= (व्योम *)RCAR_GYROADC_MODE_SELECT_3_MAX1162,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक rcar_gyroadc_parse_subdevs(काष्ठा iio_dev *indio_dev)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा iio_chan_spec *channels;
	काष्ठा rcar_gyroadc *priv = iio_priv(indio_dev);
	काष्ठा device *dev = priv->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child;
	काष्ठा regulator *vref;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक adcmode = -1, childmode;
	अचिन्हित पूर्णांक sample_width;
	अचिन्हित पूर्णांक num_channels;
	पूर्णांक ret, first = 1;

	क्रम_each_child_of_node(np, child) अणु
		of_id = of_match_node(rcar_gyroadc_child_match, child);
		अगर (!of_id) अणु
			dev_err(dev, "Ignoring unsupported ADC \"%pOFn\".",
				child);
			जारी;
		पूर्ण

		childmode = (uपूर्णांकptr_t)of_id->data;
		चयन (childmode) अणु
		हाल RCAR_GYROADC_MODE_SELECT_1_MB88101A:
			sample_width = 12;
			channels = rcar_gyroadc_iio_channels_1;
			num_channels = ARRAY_SIZE(rcar_gyroadc_iio_channels_1);
			अवरोध;
		हाल RCAR_GYROADC_MODE_SELECT_2_ADCS7476:
			sample_width = 15;
			channels = rcar_gyroadc_iio_channels_2;
			num_channels = ARRAY_SIZE(rcar_gyroadc_iio_channels_2);
			अवरोध;
		हाल RCAR_GYROADC_MODE_SELECT_3_MAX1162:
			sample_width = 16;
			channels = rcar_gyroadc_iio_channels_3;
			num_channels = ARRAY_SIZE(rcar_gyroadc_iio_channels_3);
			अवरोध;
		शेष:
			जाओ err_e_inval;
		पूर्ण

		/*
		 * MB88101 is special in that it's only a single chip taking
		 * up all the CHS lines. Thus, the DT binding is also special
		 * and has no reg property. If we run पूर्णांकo such ADC, handle
		 * it here.
		 */
		अगर (childmode == RCAR_GYROADC_MODE_SELECT_1_MB88101A) अणु
			reg = 0;
		पूर्ण अन्यथा अणु
			ret = of_property_पढ़ो_u32(child, "reg", &reg);
			अगर (ret) अणु
				dev_err(dev,
					"Failed to get child reg property of ADC \"%pOFn\".\n",
					child);
				जाओ err_of_node_put;
			पूर्ण

			/* Channel number is too high. */
			अगर (reg >= num_channels) अणु
				dev_err(dev,
					"Only %i channels supported with %pOFn, but reg = <%i>.\n",
					num_channels, child, reg);
				जाओ err_e_inval;
			पूर्ण
		पूर्ण

		/* Child node selected dअगरferent mode than the rest. */
		अगर (!first && (adcmode != childmode)) अणु
			dev_err(dev,
				"Channel %i uses different ADC mode than the rest.\n",
				reg);
			जाओ err_e_inval;
		पूर्ण

		/* Channel is valid, grab the regulator. */
		dev->of_node = child;
		vref = devm_regulator_get(dev, "vref");
		dev->of_node = np;
		अगर (IS_ERR(vref)) अणु
			dev_dbg(dev, "Channel %i 'vref' supply not connected.\n",
				reg);
			ret = PTR_ERR(vref);
			जाओ err_of_node_put;
		पूर्ण

		priv->vref[reg] = vref;

		अगर (!first)
			जारी;

		/* First child node which passed sanity tests. */
		adcmode = childmode;
		first = 0;

		priv->num_channels = num_channels;
		priv->mode = childmode;
		priv->sample_width = sample_width;

		indio_dev->channels = channels;
		indio_dev->num_channels = num_channels;

		/*
		 * MB88101 is special and we only have one such device
		 * attached to the GyroADC at a समय, so अगर we found it,
		 * we can stop parsing here.
		 */
		अगर (childmode == RCAR_GYROADC_MODE_SELECT_1_MB88101A) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (first) अणु
		dev_err(dev, "No valid ADC channels found, aborting.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;

err_e_inval:
	ret = -EINVAL;
err_of_node_put:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल व्योम rcar_gyroadc_deinit_supplies(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा rcar_gyroadc *priv = iio_priv(indio_dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		अगर (!priv->vref[i])
			जारी;

		regulator_disable(priv->vref[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक rcar_gyroadc_init_supplies(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा rcar_gyroadc *priv = iio_priv(indio_dev);
	काष्ठा device *dev = priv->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		अगर (!priv->vref[i])
			जारी;

		ret = regulator_enable(priv->vref[i]);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable regulator %i (ret=%i)\n",
				i, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	rcar_gyroadc_deinit_supplies(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक rcar_gyroadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rcar_gyroadc *priv;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*priv));
	अगर (!indio_dev)
		वापस -ENOMEM;

	priv = iio_priv(indio_dev);
	priv->dev = dev;

	priv->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->regs))
		वापस PTR_ERR(priv->regs);

	priv->clk = devm_clk_get(dev, "fck");
	अगर (IS_ERR(priv->clk))
		वापस dev_err_probe(dev, PTR_ERR(priv->clk),
				     "Failed to get IF clock\n");

	ret = rcar_gyroadc_parse_subdevs(indio_dev);
	अगर (ret)
		वापस ret;

	ret = rcar_gyroadc_init_supplies(indio_dev);
	अगर (ret)
		वापस ret;

	priv->model = (क्रमागत rcar_gyroadc_model)
		of_device_get_match_data(&pdev->dev);

	platक्रमm_set_drvdata(pdev, indio_dev);

	indio_dev->name = DRIVER_NAME;
	indio_dev->info = &rcar_gyroadc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(dev, "Could not prepare or enable the IF clock.\n");
		जाओ err_clk_अगर_enable;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(dev, RCAR_GYROADC_RUNTIME_PM_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_enable(dev);

	pm_runसमय_get_sync(dev);
	rcar_gyroadc_hw_init(priv);
	rcar_gyroadc_hw_start(priv);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "Couldn't register IIO device.\n");
		जाओ err_iio_device_रेजिस्टर;
	पूर्ण

	pm_runसमय_put_sync(dev);

	वापस 0;

err_iio_device_रेजिस्टर:
	rcar_gyroadc_hw_stop(priv);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	clk_disable_unprepare(priv->clk);
err_clk_अगर_enable:
	rcar_gyroadc_deinit_supplies(indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_gyroadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा rcar_gyroadc *priv = iio_priv(indio_dev);
	काष्ठा device *dev = priv->dev;

	iio_device_unरेजिस्टर(indio_dev);
	pm_runसमय_get_sync(dev);
	rcar_gyroadc_hw_stop(priv);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	clk_disable_unprepare(priv->clk);
	rcar_gyroadc_deinit_supplies(indio_dev);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_PM)
अटल पूर्णांक rcar_gyroadc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा rcar_gyroadc *priv = iio_priv(indio_dev);

	rcar_gyroadc_hw_stop(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_gyroadc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा rcar_gyroadc *priv = iio_priv(indio_dev);

	rcar_gyroadc_hw_start(priv);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rcar_gyroadc_pm_ops = अणु
	SET_RUNTIME_PM_OPS(rcar_gyroadc_suspend, rcar_gyroadc_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver rcar_gyroadc_driver = अणु
	.probe          = rcar_gyroadc_probe,
	.हटाओ         = rcar_gyroadc_हटाओ,
	.driver         = अणु
		.name		= DRIVER_NAME,
		.of_match_table	= rcar_gyroadc_match,
		.pm		= &rcar_gyroadc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rcar_gyroadc_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("Renesas R-Car GyroADC driver");
MODULE_LICENSE("GPL");
