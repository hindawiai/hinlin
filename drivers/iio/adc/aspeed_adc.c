<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aspeed AST2400/2500 ADC
 *
 * Copyright (C) 2017 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iopoll.h>

#घोषणा ASPEED_RESOLUTION_BITS		10
#घोषणा ASPEED_CLOCKS_PER_SAMPLE	12

#घोषणा ASPEED_REG_ENGINE_CONTROL	0x00
#घोषणा ASPEED_REG_INTERRUPT_CONTROL	0x04
#घोषणा ASPEED_REG_VGA_DETECT_CONTROL	0x08
#घोषणा ASPEED_REG_CLOCK_CONTROL	0x0C
#घोषणा ASPEED_REG_MAX			0xC0

#घोषणा ASPEED_OPERATION_MODE_POWER_DOWN	(0x0 << 1)
#घोषणा ASPEED_OPERATION_MODE_STANDBY		(0x1 << 1)
#घोषणा ASPEED_OPERATION_MODE_NORMAL		(0x7 << 1)

#घोषणा ASPEED_ENGINE_ENABLE		BIT(0)

#घोषणा ASPEED_ADC_CTRL_INIT_RDY	BIT(8)

#घोषणा ASPEED_ADC_INIT_POLLING_TIME	500
#घोषणा ASPEED_ADC_INIT_TIMEOUT		500000

काष्ठा aspeed_adc_model_data अणु
	स्थिर अक्षर *model_name;
	अचिन्हित पूर्णांक min_sampling_rate;	// Hz
	अचिन्हित पूर्णांक max_sampling_rate;	// Hz
	अचिन्हित पूर्णांक vref_voltage;	// mV
	bool रुको_init_sequence;
पूर्ण;

काष्ठा aspeed_adc_data अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	spinlock_t		clk_lock;
	काष्ठा clk_hw		*clk_prescaler;
	काष्ठा clk_hw		*clk_scaler;
	काष्ठा reset_control	*rst;
पूर्ण;

#घोषणा ASPEED_CHAN(_idx, _data_reg_addr) अणु			\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = (_idx),					\
	.address = (_data_reg_addr),				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec aspeed_adc_iio_channels[] = अणु
	ASPEED_CHAN(0, 0x10),
	ASPEED_CHAN(1, 0x12),
	ASPEED_CHAN(2, 0x14),
	ASPEED_CHAN(3, 0x16),
	ASPEED_CHAN(4, 0x18),
	ASPEED_CHAN(5, 0x1A),
	ASPEED_CHAN(6, 0x1C),
	ASPEED_CHAN(7, 0x1E),
	ASPEED_CHAN(8, 0x20),
	ASPEED_CHAN(9, 0x22),
	ASPEED_CHAN(10, 0x24),
	ASPEED_CHAN(11, 0x26),
	ASPEED_CHAN(12, 0x28),
	ASPEED_CHAN(13, 0x2A),
	ASPEED_CHAN(14, 0x2C),
	ASPEED_CHAN(15, 0x2E),
पूर्ण;

अटल पूर्णांक aspeed_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा aspeed_adc_data *data = iio_priv(indio_dev);
	स्थिर काष्ठा aspeed_adc_model_data *model_data =
			of_device_get_match_data(data->dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = पढ़ोw(data->base + chan->address);
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = model_data->vref_voltage;
		*val2 = ASPEED_RESOLUTION_BITS;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = clk_get_rate(data->clk_scaler->clk) /
				ASPEED_CLOCKS_PER_SAMPLE;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक aspeed_adc_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा aspeed_adc_data *data = iio_priv(indio_dev);
	स्थिर काष्ठा aspeed_adc_model_data *model_data =
			of_device_get_match_data(data->dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val < model_data->min_sampling_rate ||
			val > model_data->max_sampling_rate)
			वापस -EINVAL;

		clk_set_rate(data->clk_scaler->clk,
				val * ASPEED_CLOCKS_PER_SAMPLE);
		वापस 0;

	हाल IIO_CHAN_INFO_SCALE:
	हाल IIO_CHAN_INFO_RAW:
		/*
		 * Technically, these could be written but the only reasons
		 * क्रम करोing so seem better handled in userspace.  EPERM is
		 * वापसed to संकेत this is a policy choice rather than a
		 * hardware limitation.
		 */
		वापस -EPERM;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक aspeed_adc_reg_access(काष्ठा iio_dev *indio_dev,
				 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक ग_लिखोval,
				 अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा aspeed_adc_data *data = iio_priv(indio_dev);

	अगर (!पढ़ोval || reg % 4 || reg > ASPEED_REG_MAX)
		वापस -EINVAL;

	*पढ़ोval = पढ़ोl(data->base + reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info aspeed_adc_iio_info = अणु
	.पढ़ो_raw = aspeed_adc_पढ़ो_raw,
	.ग_लिखो_raw = aspeed_adc_ग_लिखो_raw,
	.debugfs_reg_access = aspeed_adc_reg_access,
पूर्ण;

अटल पूर्णांक aspeed_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा aspeed_adc_data *data;
	स्थिर काष्ठा aspeed_adc_model_data *model_data;
	स्थिर अक्षर *clk_parent_name;
	पूर्णांक ret;
	u32 adc_engine_control_reg_val;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->dev = &pdev->dev;

	data->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	/* Register ADC घड़ी prescaler with source specअगरied by device tree. */
	spin_lock_init(&data->clk_lock);
	clk_parent_name = of_clk_get_parent_name(pdev->dev.of_node, 0);

	data->clk_prescaler = clk_hw_रेजिस्टर_भागider(
				&pdev->dev, "prescaler", clk_parent_name, 0,
				data->base + ASPEED_REG_CLOCK_CONTROL,
				17, 15, 0, &data->clk_lock);
	अगर (IS_ERR(data->clk_prescaler))
		वापस PTR_ERR(data->clk_prescaler);

	/*
	 * Register ADC घड़ी scaler करोwnstream from the prescaler. Allow rate
	 * setting to adjust the prescaler as well.
	 */
	data->clk_scaler = clk_hw_रेजिस्टर_भागider(
				&pdev->dev, "scaler", "prescaler",
				CLK_SET_RATE_PARENT,
				data->base + ASPEED_REG_CLOCK_CONTROL,
				0, 10, 0, &data->clk_lock);
	अगर (IS_ERR(data->clk_scaler)) अणु
		ret = PTR_ERR(data->clk_scaler);
		जाओ scaler_error;
	पूर्ण

	data->rst = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(data->rst)) अणु
		dev_err(&pdev->dev,
			"invalid or missing reset controller device tree entry");
		ret = PTR_ERR(data->rst);
		जाओ reset_error;
	पूर्ण
	reset_control_deनिश्चित(data->rst);

	model_data = of_device_get_match_data(&pdev->dev);

	अगर (model_data->रुको_init_sequence) अणु
		/* Enable engine in normal mode. */
		ग_लिखोl(ASPEED_OPERATION_MODE_NORMAL | ASPEED_ENGINE_ENABLE,
		       data->base + ASPEED_REG_ENGINE_CONTROL);

		/* Wait क्रम initial sequence complete. */
		ret = पढ़ोl_poll_समयout(data->base + ASPEED_REG_ENGINE_CONTROL,
					 adc_engine_control_reg_val,
					 adc_engine_control_reg_val &
					 ASPEED_ADC_CTRL_INIT_RDY,
					 ASPEED_ADC_INIT_POLLING_TIME,
					 ASPEED_ADC_INIT_TIMEOUT);
		अगर (ret)
			जाओ poll_समयout_error;
	पूर्ण

	/* Start all channels in normal mode. */
	ret = clk_prepare_enable(data->clk_scaler->clk);
	अगर (ret)
		जाओ clk_enable_error;

	adc_engine_control_reg_val = GENMASK(31, 16) |
		ASPEED_OPERATION_MODE_NORMAL | ASPEED_ENGINE_ENABLE;
	ग_लिखोl(adc_engine_control_reg_val,
		data->base + ASPEED_REG_ENGINE_CONTROL);

	model_data = of_device_get_match_data(&pdev->dev);
	indio_dev->name = model_data->model_name;
	indio_dev->info = &aspeed_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = aspeed_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(aspeed_adc_iio_channels);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ iio_रेजिस्टर_error;

	वापस 0;

iio_रेजिस्टर_error:
	ग_लिखोl(ASPEED_OPERATION_MODE_POWER_DOWN,
		data->base + ASPEED_REG_ENGINE_CONTROL);
	clk_disable_unprepare(data->clk_scaler->clk);
clk_enable_error:
poll_समयout_error:
	reset_control_निश्चित(data->rst);
reset_error:
	clk_hw_unरेजिस्टर_भागider(data->clk_scaler);
scaler_error:
	clk_hw_unरेजिस्टर_भागider(data->clk_prescaler);
	वापस ret;
पूर्ण

अटल पूर्णांक aspeed_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा aspeed_adc_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	ग_लिखोl(ASPEED_OPERATION_MODE_POWER_DOWN,
		data->base + ASPEED_REG_ENGINE_CONTROL);
	clk_disable_unprepare(data->clk_scaler->clk);
	reset_control_निश्चित(data->rst);
	clk_hw_unरेजिस्टर_भागider(data->clk_scaler);
	clk_hw_unरेजिस्टर_भागider(data->clk_prescaler);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा aspeed_adc_model_data ast2400_model_data = अणु
	.model_name = "ast2400-adc",
	.vref_voltage = 2500, // mV
	.min_sampling_rate = 10000,
	.max_sampling_rate = 500000,
पूर्ण;

अटल स्थिर काष्ठा aspeed_adc_model_data ast2500_model_data = अणु
	.model_name = "ast2500-adc",
	.vref_voltage = 1800, // mV
	.min_sampling_rate = 1,
	.max_sampling_rate = 1000000,
	.रुको_init_sequence = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aspeed_adc_matches[] = अणु
	अणु .compatible = "aspeed,ast2400-adc", .data = &ast2400_model_data पूर्ण,
	अणु .compatible = "aspeed,ast2500-adc", .data = &ast2500_model_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aspeed_adc_matches);

अटल काष्ठा platक्रमm_driver aspeed_adc_driver = अणु
	.probe = aspeed_adc_probe,
	.हटाओ = aspeed_adc_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = aspeed_adc_matches,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(aspeed_adc_driver);

MODULE_AUTHOR("Rick Altherr <raltherr@google.com>");
MODULE_DESCRIPTION("Aspeed AST2400/2500 ADC Driver");
MODULE_LICENSE("GPL");
