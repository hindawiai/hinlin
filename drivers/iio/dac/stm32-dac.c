<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is part of STM32 DAC driver
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Authors: Amelie Delaunay <amelie.delaunay@st.com>
 *	    Fabrice Gasnier <fabrice.gasnier@st.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "stm32-dac-core.h"

#घोषणा STM32_DAC_CHANNEL_1		1
#घोषणा STM32_DAC_CHANNEL_2		2
#घोषणा STM32_DAC_IS_CHAN_1(ch)		((ch) & STM32_DAC_CHANNEL_1)

#घोषणा STM32_DAC_AUTO_SUSPEND_DELAY_MS	2000

/**
 * काष्ठा sपंचांग32_dac - निजी data of DAC driver
 * @common:		reference to DAC common data
 * @lock:		lock to protect against potential races when पढ़ोing
 *			and update CR, to keep it in sync with pm_runसमय
 */
काष्ठा sपंचांग32_dac अणु
	काष्ठा sपंचांग32_dac_common *common;
	काष्ठा mutex		lock;
पूर्ण;

अटल पूर्णांक sपंचांग32_dac_is_enabled(काष्ठा iio_dev *indio_dev, पूर्णांक channel)
अणु
	काष्ठा sपंचांग32_dac *dac = iio_priv(indio_dev);
	u32 en, val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(dac->common->regmap, STM32_DAC_CR, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (STM32_DAC_IS_CHAN_1(channel))
		en = FIELD_GET(STM32_DAC_CR_EN1, val);
	अन्यथा
		en = FIELD_GET(STM32_DAC_CR_EN2, val);

	वापस !!en;
पूर्ण

अटल पूर्णांक sपंचांग32_dac_set_enable_state(काष्ठा iio_dev *indio_dev, पूर्णांक ch,
				      bool enable)
अणु
	काष्ठा sपंचांग32_dac *dac = iio_priv(indio_dev);
	काष्ठा device *dev = indio_dev->dev.parent;
	u32 msk = STM32_DAC_IS_CHAN_1(ch) ? STM32_DAC_CR_EN1 : STM32_DAC_CR_EN2;
	u32 en = enable ? msk : 0;
	पूर्णांक ret;

	/* alपढ़ोy enabled / disabled ? */
	mutex_lock(&dac->lock);
	ret = sपंचांग32_dac_is_enabled(indio_dev, ch);
	अगर (ret < 0 || enable == !!ret) अणु
		mutex_unlock(&dac->lock);
		वापस ret < 0 ? ret : 0;
	पूर्ण

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(dev);
			mutex_unlock(&dac->lock);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = regmap_update_bits(dac->common->regmap, STM32_DAC_CR, msk, en);
	mutex_unlock(&dac->lock);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev, "%s failed\n", en ?
			"Enable" : "Disable");
		जाओ err_put_pm;
	पूर्ण

	/*
	 * When HFSEL is set, it is not allowed to ग_लिखो the DHRx रेजिस्टर
	 * during 8 घड़ी cycles after the ENx bit is set. It is not allowed
	 * to make software/hardware trigger during this period either.
	 */
	अगर (en && dac->common->hfsel)
		udelay(1);

	अगर (!enable) अणु
		pm_runसमय_mark_last_busy(dev);
		pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	वापस 0;

err_put_pm:
	अगर (enable) अणु
		pm_runसमय_mark_last_busy(dev);
		pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dac_get_value(काष्ठा sपंचांग32_dac *dac, पूर्णांक channel, पूर्णांक *val)
अणु
	पूर्णांक ret;

	अगर (STM32_DAC_IS_CHAN_1(channel))
		ret = regmap_पढ़ो(dac->common->regmap, STM32_DAC_DOR1, val);
	अन्यथा
		ret = regmap_पढ़ो(dac->common->regmap, STM32_DAC_DOR2, val);

	वापस ret ? ret : IIO_VAL_INT;
पूर्ण

अटल पूर्णांक sपंचांग32_dac_set_value(काष्ठा sपंचांग32_dac *dac, पूर्णांक channel, पूर्णांक val)
अणु
	पूर्णांक ret;

	अगर (STM32_DAC_IS_CHAN_1(channel))
		ret = regmap_ग_लिखो(dac->common->regmap, STM32_DAC_DHR12R1, val);
	अन्यथा
		ret = regmap_ग_लिखो(dac->common->regmap, STM32_DAC_DHR12R2, val);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dac_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा sपंचांग32_dac *dac = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस sपंचांग32_dac_get_value(dac, chan->channel, val);
	हाल IIO_CHAN_INFO_SCALE:
		*val = dac->common->vref_mv;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_dac_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा sपंचांग32_dac *dac = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस sपंचांग32_dac_set_value(dac, chan->channel, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_dac_debugfs_reg_access(काष्ठा iio_dev *indio_dev,
					अचिन्हित reg, अचिन्हित ग_लिखोval,
					अचिन्हित *पढ़ोval)
अणु
	काष्ठा sपंचांग32_dac *dac = iio_priv(indio_dev);

	अगर (!पढ़ोval)
		वापस regmap_ग_लिखो(dac->common->regmap, reg, ग_लिखोval);
	अन्यथा
		वापस regmap_पढ़ो(dac->common->regmap, reg, पढ़ोval);
पूर्ण

अटल स्थिर काष्ठा iio_info sपंचांग32_dac_iio_info = अणु
	.पढ़ो_raw = sपंचांग32_dac_पढ़ो_raw,
	.ग_लिखो_raw = sपंचांग32_dac_ग_लिखो_raw,
	.debugfs_reg_access = sपंचांग32_dac_debugfs_reg_access,
पूर्ण;

अटल स्थिर अक्षर * स्थिर sपंचांग32_dac_घातerकरोwn_modes[] = अणु
	"three_state",
पूर्ण;

अटल पूर्णांक sपंचांग32_dac_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dac_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					अचिन्हित पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार sपंचांग32_dac_पढ़ो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					uपूर्णांकptr_t निजी,
					स्थिर काष्ठा iio_chan_spec *chan,
					अक्षर *buf)
अणु
	पूर्णांक ret = sपंचांग32_dac_is_enabled(indio_dev, chan->channel);

	अगर (ret < 0)
		वापस ret;

	वापस sysfs_emit(buf, "%d\n", ret ? 0 : 1);
पूर्ण

अटल sमाप_प्रकार sपंचांग32_dac_ग_लिखो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					 uपूर्णांकptr_t निजी,
					 स्थिर काष्ठा iio_chan_spec *chan,
					 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	bool घातerकरोwn;
	पूर्णांक ret;

	ret = strtobool(buf, &घातerकरोwn);
	अगर (ret)
		वापस ret;

	ret = sपंचांग32_dac_set_enable_state(indio_dev, chan->channel, !घातerकरोwn);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत sपंचांग32_dac_घातerकरोwn_mode_en = अणु
	.items = sपंचांग32_dac_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(sपंचांग32_dac_घातerकरोwn_modes),
	.get = sपंचांग32_dac_get_घातerकरोwn_mode,
	.set = sपंचांग32_dac_set_घातerकरोwn_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info sपंचांग32_dac_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = sपंचांग32_dac_पढ़ो_घातerकरोwn,
		.ग_लिखो = sपंचांग32_dac_ग_लिखो_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SEPARATE, &sपंचांग32_dac_घातerकरोwn_mode_en),
	IIO_ENUM_AVAILABLE("powerdown_mode", &sपंचांग32_dac_घातerकरोwn_mode_en),
	अणुपूर्ण,
पूर्ण;

#घोषणा STM32_DAC_CHANNEL(chan, name) अणु			\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.output = 1,					\
	.channel = chan,				\
	.info_mask_separate =				\
		BIT(IIO_CHAN_INFO_RAW) |		\
		BIT(IIO_CHAN_INFO_SCALE),		\
	/* scan_index is always 0 as num_channels is 1 */ \
	.scan_type = अणु					\
		.sign = 'u',				\
		.realbits = 12,				\
		.storagebits = 16,			\
	पूर्ण,						\
	.datasheet_name = name,				\
	.ext_info = sपंचांग32_dac_ext_info			\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec sपंचांग32_dac_channels[] = अणु
	STM32_DAC_CHANNEL(STM32_DAC_CHANNEL_1, "out1"),
	STM32_DAC_CHANNEL(STM32_DAC_CHANNEL_2, "out2"),
पूर्ण;

अटल पूर्णांक sपंचांग32_dac_chan_of_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा device_node *np = indio_dev->dev.of_node;
	अचिन्हित पूर्णांक i;
	u32 channel;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "reg", &channel);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "Failed to read reg property\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sपंचांग32_dac_channels); i++) अणु
		अगर (sपंचांग32_dac_channels[i].channel == channel)
			अवरोध;
	पूर्ण
	अगर (i >= ARRAY_SIZE(sपंचांग32_dac_channels)) अणु
		dev_err(&indio_dev->dev, "Invalid reg property\n");
		वापस -EINVAL;
	पूर्ण

	indio_dev->channels = &sपंचांग32_dac_channels[i];
	/*
	 * Expose only one channel here, as they can be used independently,
	 * with separate trigger. Then separate IIO devices are instantiated
	 * to manage this.
	 */
	indio_dev->num_channels = 1;

	वापस 0;
पूर्ण;

अटल पूर्णांक sपंचांग32_dac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा sपंचांग32_dac *dac;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*dac));
	अगर (!indio_dev)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, indio_dev);

	dac = iio_priv(indio_dev);
	dac->common = dev_get_drvdata(pdev->dev.parent);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &sपंचांग32_dac_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	mutex_init(&dac->lock);

	ret = sपंचांग32_dac_chan_of_init(indio_dev);
	अगर (ret < 0)
		वापस ret;

	/* Get sपंचांग32-dac-core PM online */
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, STM32_DAC_AUTO_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_enable(dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_pm_put;

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;

err_pm_put:
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&pdev->dev);
	iio_device_unरेजिस्टर(indio_dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dac_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	पूर्णांक channel = indio_dev->channels[0].channel;
	पूर्णांक ret;

	/* Ensure DAC is disabled beक्रमe suspend */
	ret = sपंचांग32_dac_is_enabled(indio_dev, channel);
	अगर (ret)
		वापस ret < 0 ? ret : -EBUSY;

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_dac_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_dac_suspend, pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_dac_of_match[] = अणु
	अणु .compatible = "st,stm32-dac", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_dac_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_dac_driver = अणु
	.probe = sपंचांग32_dac_probe,
	.हटाओ = sपंचांग32_dac_हटाओ,
	.driver = अणु
		.name = "stm32-dac",
		.of_match_table = sपंचांग32_dac_of_match,
		.pm = &sपंचांग32_dac_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_dac_driver);

MODULE_ALIAS("platform:stm32-dac");
MODULE_AUTHOR("Amelie Delaunay <amelie.delaunay@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 DAC driver");
MODULE_LICENSE("GPL v2");
