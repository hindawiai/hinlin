<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale Vybrid vf610 DAC driver
 *
 * Copyright 2016 Toradex AG
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा VF610_DACx_STATCTRL		0x20

#घोषणा VF610_DAC_DACEN			BIT(15)
#घोषणा VF610_DAC_DACRFS		BIT(14)
#घोषणा VF610_DAC_LPEN			BIT(11)

#घोषणा VF610_DAC_DAT0(x)		((x) & 0xFFF)

क्रमागत vf610_conversion_mode_sel अणु
	VF610_DAC_CONV_HIGH_POWER,
	VF610_DAC_CONV_LOW_POWER,
पूर्ण;

काष्ठा vf610_dac अणु
	काष्ठा clk *clk;
	काष्ठा device *dev;
	क्रमागत vf610_conversion_mode_sel conv_mode;
	व्योम __iomem *regs;
	काष्ठा mutex lock;
पूर्ण;

अटल व्योम vf610_dac_init(काष्ठा vf610_dac *info)
अणु
	पूर्णांक val;

	info->conv_mode = VF610_DAC_CONV_LOW_POWER;
	val = VF610_DAC_DACEN | VF610_DAC_DACRFS |
		VF610_DAC_LPEN;
	ग_लिखोl(val, info->regs + VF610_DACx_STATCTRL);
पूर्ण

अटल व्योम vf610_dac_निकास(काष्ठा vf610_dac *info)
अणु
	पूर्णांक val;

	val = पढ़ोl(info->regs + VF610_DACx_STATCTRL);
	val &= ~VF610_DAC_DACEN;
	ग_लिखोl(val, info->regs + VF610_DACx_STATCTRL);
पूर्ण

अटल पूर्णांक vf610_set_conversion_mode(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan,
				अचिन्हित पूर्णांक mode)
अणु
	काष्ठा vf610_dac *info = iio_priv(indio_dev);
	पूर्णांक val;

	mutex_lock(&info->lock);
	info->conv_mode = mode;
	val = पढ़ोl(info->regs + VF610_DACx_STATCTRL);
	अगर (mode)
		val |= VF610_DAC_LPEN;
	अन्यथा
		val &= ~VF610_DAC_LPEN;
	ग_लिखोl(val, info->regs + VF610_DACx_STATCTRL);
	mutex_unlock(&info->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vf610_get_conversion_mode(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा vf610_dac *info = iio_priv(indio_dev);

	वापस info->conv_mode;
पूर्ण

अटल स्थिर अक्षर * स्थिर vf610_conv_modes[] = अणु "high-power", "low-power" पूर्ण;

अटल स्थिर काष्ठा iio_क्रमागत vf610_conversion_mode = अणु
	.items = vf610_conv_modes,
	.num_items = ARRAY_SIZE(vf610_conv_modes),
	.get = vf610_get_conversion_mode,
	.set = vf610_set_conversion_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info vf610_ext_info[] = अणु
	IIO_ENUM("conversion_mode", IIO_SHARED_BY_सूची,
		&vf610_conversion_mode),
	अणुपूर्ण,
पूर्ण;

#घोषणा VF610_DAC_CHAN(_chan_type) अणु \
	.type = (_chan_type), \
	.output = 1, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.ext_info = vf610_ext_info, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec vf610_dac_iio_channels[] = अणु
	VF610_DAC_CHAN(IIO_VOLTAGE),
पूर्ण;

अटल पूर्णांक vf610_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2,
			दीर्घ mask)
अणु
	काष्ठा vf610_dac *info = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = VF610_DAC_DAT0(पढ़ोl(info->regs));
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/*
		 * DACRFS is always 1 क्रम valid reference and typical
		 * reference voltage as per Vybrid datasheet is 3.3V
		 * from section 9.1.2.1 of Vybrid datasheet
		 */
		*val = 3300 /* mV */;
		*val2 = 12;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vf610_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक val, पूर्णांक val2,
			दीर्घ mask)
अणु
	काष्ठा vf610_dac *info = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&info->lock);
		ग_लिखोl(VF610_DAC_DAT0(val), info->regs);
		mutex_unlock(&info->lock);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info vf610_dac_iio_info = अणु
	.पढ़ो_raw = &vf610_पढ़ो_raw,
	.ग_लिखो_raw = &vf610_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vf610_dac_match[] = अणु
	अणु .compatible = "fsl,vf610-dac", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vf610_dac_match);

अटल पूर्णांक vf610_dac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा vf610_dac *info;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
					माप(काष्ठा vf610_dac));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "Failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	info = iio_priv(indio_dev);
	info->dev = &pdev->dev;

	info->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->regs))
		वापस PTR_ERR(info->regs);

	info->clk = devm_clk_get(&pdev->dev, "dac");
	अगर (IS_ERR(info->clk)) अणु
		dev_err(&pdev->dev, "Failed getting clock, err = %ld\n",
			PTR_ERR(info->clk));
		वापस PTR_ERR(info->clk);
	पूर्ण

	platक्रमm_set_drvdata(pdev, indio_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &vf610_dac_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = vf610_dac_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(vf610_dac_iio_channels);

	mutex_init(&info->lock);

	ret = clk_prepare_enable(info->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Could not prepare or enable the clock\n");
		वापस ret;
	पूर्ण

	vf610_dac_init(info);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't register the device\n");
		जाओ error_iio_device_रेजिस्टर;
	पूर्ण

	वापस 0;

error_iio_device_रेजिस्टर:
	vf610_dac_निकास(info);
	clk_disable_unprepare(info->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक vf610_dac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा vf610_dac *info = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	vf610_dac_निकास(info);
	clk_disable_unprepare(info->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक vf610_dac_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा vf610_dac *info = iio_priv(indio_dev);

	vf610_dac_निकास(info);
	clk_disable_unprepare(info->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक vf610_dac_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा vf610_dac *info = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(info->clk);
	अगर (ret)
		वापस ret;

	vf610_dac_init(info);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(vf610_dac_pm_ops, vf610_dac_suspend, vf610_dac_resume);

अटल काष्ठा platक्रमm_driver vf610_dac_driver = अणु
	.probe          = vf610_dac_probe,
	.हटाओ         = vf610_dac_हटाओ,
	.driver         = अणु
		.name   = "vf610-dac",
		.of_match_table = vf610_dac_match,
		.pm     = &vf610_dac_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(vf610_dac_driver);

MODULE_AUTHOR("Sanchayan Maity <sanchayan.maity@toradex.com>");
MODULE_DESCRIPTION("Freescale VF610 DAC driver");
MODULE_LICENSE("GPL v2");
