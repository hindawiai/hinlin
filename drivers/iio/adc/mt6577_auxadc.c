<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Zhiyong Tao <zhiyong.tao@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/पन.स>
#समावेश <linux/iio/iपन.स>

/* Register definitions */
#घोषणा MT6577_AUXADC_CON0                    0x00
#घोषणा MT6577_AUXADC_CON1                    0x04
#घोषणा MT6577_AUXADC_CON2                    0x10
#घोषणा MT6577_AUXADC_STA                     BIT(0)

#घोषणा MT6577_AUXADC_DAT0                    0x14
#घोषणा MT6577_AUXADC_RDY0                    BIT(12)

#घोषणा MT6577_AUXADC_MISC                    0x94
#घोषणा MT6577_AUXADC_PDN_EN                  BIT(14)

#घोषणा MT6577_AUXADC_DAT_MASK                0xfff
#घोषणा MT6577_AUXADC_SLEEP_US                1000
#घोषणा MT6577_AUXADC_TIMEOUT_US              10000
#घोषणा MT6577_AUXADC_POWER_READY_MS          1
#घोषणा MT6577_AUXADC_SAMPLE_READY_US         25

काष्ठा mtk_auxadc_compatible अणु
	bool sample_data_cali;
	bool check_global_idle;
पूर्ण;

काष्ठा mt6577_auxadc_device अणु
	व्योम __iomem *reg_base;
	काष्ठा clk *adc_clk;
	काष्ठा mutex lock;
	स्थिर काष्ठा mtk_auxadc_compatible *dev_comp;
पूर्ण;

अटल स्थिर काष्ठा mtk_auxadc_compatible mt8173_compat = अणु
	.sample_data_cali = false,
	.check_global_idle = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_auxadc_compatible mt6765_compat = अणु
	.sample_data_cali = true,
	.check_global_idle = false,
पूर्ण;

#घोषणा MT6577_AUXADC_CHANNEL(idx) अणु				    \
		.type = IIO_VOLTAGE,				    \
		.indexed = 1,					    \
		.channel = (idx),				    \
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED), \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mt6577_auxadc_iio_channels[] = अणु
	MT6577_AUXADC_CHANNEL(0),
	MT6577_AUXADC_CHANNEL(1),
	MT6577_AUXADC_CHANNEL(2),
	MT6577_AUXADC_CHANNEL(3),
	MT6577_AUXADC_CHANNEL(4),
	MT6577_AUXADC_CHANNEL(5),
	MT6577_AUXADC_CHANNEL(6),
	MT6577_AUXADC_CHANNEL(7),
	MT6577_AUXADC_CHANNEL(8),
	MT6577_AUXADC_CHANNEL(9),
	MT6577_AUXADC_CHANNEL(10),
	MT6577_AUXADC_CHANNEL(11),
	MT6577_AUXADC_CHANNEL(12),
	MT6577_AUXADC_CHANNEL(13),
	MT6577_AUXADC_CHANNEL(14),
	MT6577_AUXADC_CHANNEL(15),
पूर्ण;

अटल पूर्णांक mt_auxadc_get_cali_data(पूर्णांक rawdata, bool enable_cali)
अणु
	वापस rawdata;
पूर्ण

अटल अंतरभूत व्योम mt6577_auxadc_mod_reg(व्योम __iomem *reg,
					 u32 or_mask, u32 and_mask)
अणु
	u32 val;

	val = पढ़ोl(reg);
	val |= or_mask;
	val &= ~and_mask;
	ग_लिखोl(val, reg);
पूर्ण

अटल पूर्णांक mt6577_auxadc_पढ़ो(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan)
अणु
	u32 val;
	व्योम __iomem *reg_channel;
	पूर्णांक ret;
	काष्ठा mt6577_auxadc_device *adc_dev = iio_priv(indio_dev);

	reg_channel = adc_dev->reg_base + MT6577_AUXADC_DAT0 +
		      chan->channel * 0x04;

	mutex_lock(&adc_dev->lock);

	mt6577_auxadc_mod_reg(adc_dev->reg_base + MT6577_AUXADC_CON1,
			      0, 1 << chan->channel);

	/* पढ़ो channel and make sure old पढ़ोy bit == 0 */
	ret = पढ़ोl_poll_समयout(reg_channel, val,
				 ((val & MT6577_AUXADC_RDY0) == 0),
				 MT6577_AUXADC_SLEEP_US,
				 MT6577_AUXADC_TIMEOUT_US);
	अगर (ret < 0) अणु
		dev_err(indio_dev->dev.parent,
			"wait for channel[%d] ready bit clear time out\n",
			chan->channel);
		जाओ err_समयout;
	पूर्ण

	/* set bit to trigger sample */
	mt6577_auxadc_mod_reg(adc_dev->reg_base + MT6577_AUXADC_CON1,
			      1 << chan->channel, 0);

	/* we must delay here क्रम hardware sample channel data */
	udelay(MT6577_AUXADC_SAMPLE_READY_US);

	अगर (adc_dev->dev_comp->check_global_idle) अणु
		/* check MTK_AUXADC_CON2 अगर auxadc is idle */
		ret = पढ़ोl_poll_समयout(adc_dev->reg_base + MT6577_AUXADC_CON2,
					 val, ((val & MT6577_AUXADC_STA) == 0),
					 MT6577_AUXADC_SLEEP_US,
					 MT6577_AUXADC_TIMEOUT_US);
		अगर (ret < 0) अणु
			dev_err(indio_dev->dev.parent,
				"wait for auxadc idle time out\n");
			जाओ err_समयout;
		पूर्ण
	पूर्ण

	/* पढ़ो channel and make sure पढ़ोy bit == 1 */
	ret = पढ़ोl_poll_समयout(reg_channel, val,
				 ((val & MT6577_AUXADC_RDY0) != 0),
				 MT6577_AUXADC_SLEEP_US,
				 MT6577_AUXADC_TIMEOUT_US);
	अगर (ret < 0) अणु
		dev_err(indio_dev->dev.parent,
			"wait for channel[%d] data ready time out\n",
			chan->channel);
		जाओ err_समयout;
	पूर्ण

	/* पढ़ो data */
	val = पढ़ोl(reg_channel) & MT6577_AUXADC_DAT_MASK;

	mutex_unlock(&adc_dev->lock);

	वापस val;

err_समयout:

	mutex_unlock(&adc_dev->lock);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक mt6577_auxadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				  काष्ठा iio_chan_spec स्थिर *chan,
				  पूर्णांक *val,
				  पूर्णांक *val2,
				  दीर्घ info)
अणु
	काष्ठा mt6577_auxadc_device *adc_dev = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		*val = mt6577_auxadc_पढ़ो(indio_dev, chan);
		अगर (*val < 0) अणु
			dev_err(indio_dev->dev.parent,
				"failed to sample data on channel[%d]\n",
				chan->channel);
			वापस *val;
		पूर्ण
		अगर (adc_dev->dev_comp->sample_data_cali)
			*val = mt_auxadc_get_cali_data(*val, true);
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info mt6577_auxadc_info = अणु
	.पढ़ो_raw = &mt6577_auxadc_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक __maybe_unused mt6577_auxadc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा mt6577_auxadc_device *adc_dev = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(adc_dev->adc_clk);
	अगर (ret) अणु
		pr_err("failed to enable auxadc clock\n");
		वापस ret;
	पूर्ण

	mt6577_auxadc_mod_reg(adc_dev->reg_base + MT6577_AUXADC_MISC,
			      MT6577_AUXADC_PDN_EN, 0);
	mdelay(MT6577_AUXADC_POWER_READY_MS);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mt6577_auxadc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा mt6577_auxadc_device *adc_dev = iio_priv(indio_dev);

	mt6577_auxadc_mod_reg(adc_dev->reg_base + MT6577_AUXADC_MISC,
			      0, MT6577_AUXADC_PDN_EN);
	clk_disable_unprepare(adc_dev->adc_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mt6577_auxadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6577_auxadc_device *adc_dev;
	अचिन्हित दीर्घ adc_clk_rate;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*adc_dev));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc_dev = iio_priv(indio_dev);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &mt6577_auxadc_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mt6577_auxadc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(mt6577_auxadc_iio_channels);

	adc_dev->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(adc_dev->reg_base)) अणु
		dev_err(&pdev->dev, "failed to get auxadc base address\n");
		वापस PTR_ERR(adc_dev->reg_base);
	पूर्ण

	adc_dev->adc_clk = devm_clk_get(&pdev->dev, "main");
	अगर (IS_ERR(adc_dev->adc_clk)) अणु
		dev_err(&pdev->dev, "failed to get auxadc clock\n");
		वापस PTR_ERR(adc_dev->adc_clk);
	पूर्ण

	ret = clk_prepare_enable(adc_dev->adc_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable auxadc clock\n");
		वापस ret;
	पूर्ण

	adc_clk_rate = clk_get_rate(adc_dev->adc_clk);
	अगर (!adc_clk_rate) अणु
		ret = -EINVAL;
		dev_err(&pdev->dev, "null clock rate\n");
		जाओ err_disable_clk;
	पूर्ण

	adc_dev->dev_comp = device_get_match_data(&pdev->dev);

	mutex_init(&adc_dev->lock);

	mt6577_auxadc_mod_reg(adc_dev->reg_base + MT6577_AUXADC_MISC,
			      MT6577_AUXADC_PDN_EN, 0);
	mdelay(MT6577_AUXADC_POWER_READY_MS);

	platक्रमm_set_drvdata(pdev, indio_dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register iio device\n");
		जाओ err_घातer_off;
	पूर्ण

	वापस 0;

err_घातer_off:
	mt6577_auxadc_mod_reg(adc_dev->reg_base + MT6577_AUXADC_MISC,
			      0, MT6577_AUXADC_PDN_EN);
err_disable_clk:
	clk_disable_unprepare(adc_dev->adc_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक mt6577_auxadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा mt6577_auxadc_device *adc_dev = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	mt6577_auxadc_mod_reg(adc_dev->reg_base + MT6577_AUXADC_MISC,
			      0, MT6577_AUXADC_PDN_EN);

	clk_disable_unprepare(adc_dev->adc_clk);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mt6577_auxadc_pm_ops,
			 mt6577_auxadc_suspend,
			 mt6577_auxadc_resume);

अटल स्थिर काष्ठा of_device_id mt6577_auxadc_of_match[] = अणु
	अणु .compatible = "mediatek,mt2701-auxadc", .data = &mt8173_compatपूर्ण,
	अणु .compatible = "mediatek,mt2712-auxadc", .data = &mt8173_compatपूर्ण,
	अणु .compatible = "mediatek,mt7622-auxadc", .data = &mt8173_compatपूर्ण,
	अणु .compatible = "mediatek,mt8173-auxadc", .data = &mt8173_compatपूर्ण,
	अणु .compatible = "mediatek,mt6765-auxadc", .data = &mt6765_compatपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6577_auxadc_of_match);

अटल काष्ठा platक्रमm_driver mt6577_auxadc_driver = अणु
	.driver = अणु
		.name   = "mt6577-auxadc",
		.of_match_table = mt6577_auxadc_of_match,
		.pm = &mt6577_auxadc_pm_ops,
	पूर्ण,
	.probe	= mt6577_auxadc_probe,
	.हटाओ	= mt6577_auxadc_हटाओ,
पूर्ण;
module_platक्रमm_driver(mt6577_auxadc_driver);

MODULE_AUTHOR("Zhiyong Tao <zhiyong.tao@mediatek.com>");
MODULE_DESCRIPTION("MTK AUXADC Device Driver");
MODULE_LICENSE("GPL v2");
