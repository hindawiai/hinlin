<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MFD core driver क्रम X-Powers' AC100 Audio Codec IC
 *
 * The AC100 is a highly पूर्णांकegrated audio codec and RTC subप्रणाली deचिन्हित
 * क्रम mobile applications. It has 3 I2S/PCM पूर्णांकerfaces, a 2 channel DAC,
 * a 2 channel ADC with 5 inमाला_दो and a builtin mixer. The RTC subप्रणाली has
 * 3 घड़ी outमाला_दो.
 *
 * The audio codec and RTC parts are completely separate, sharing only the
 * host पूर्णांकerface क्रम access to its रेजिस्टरs.
 *
 * Copyright (2016) Chen-Yu Tsai
 *
 * Author: Chen-Yu Tsai <wens@csie.org>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/ac100.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sunxi-rsb.h>

अटल स्थिर काष्ठा regmap_range ac100_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(AC100_CHIP_AUDIO_RST, AC100_I2S_SR_CTRL),
	regmap_reg_range(AC100_I2S1_CLK_CTRL, AC100_I2S1_MXR_GAIN),
	regmap_reg_range(AC100_I2S2_CLK_CTRL, AC100_I2S2_MXR_GAIN),
	regmap_reg_range(AC100_I2S3_CLK_CTRL, AC100_I2S3_SIG_PATH_CTRL),
	regmap_reg_range(AC100_ADC_DIG_CTRL, AC100_ADC_VOL_CTRL),
	regmap_reg_range(AC100_HMIC_CTRL1, AC100_HMIC_STATUS),
	regmap_reg_range(AC100_DAC_DIG_CTRL, AC100_DAC_MXR_GAIN),
	regmap_reg_range(AC100_ADC_APC_CTRL, AC100_LINEOUT_CTRL),
	regmap_reg_range(AC100_ADC_DAP_L_CTRL, AC100_ADC_DAP_OPT),
	regmap_reg_range(AC100_DAC_DAP_CTRL, AC100_DAC_DAP_OPT),
	regmap_reg_range(AC100_ADC_DAP_ENA, AC100_DAC_DAP_ENA),
	regmap_reg_range(AC100_SRC1_CTRL1, AC100_SRC1_CTRL2),
	regmap_reg_range(AC100_SRC2_CTRL1, AC100_SRC2_CTRL2),
	regmap_reg_range(AC100_CLK32K_ANALOG_CTRL, AC100_CLKOUT_CTRL3),
	regmap_reg_range(AC100_RTC_RST, AC100_RTC_UPD),
	regmap_reg_range(AC100_ALM_INT_ENA, AC100_ALM_INT_STA),
	regmap_reg_range(AC100_ALM_SEC, AC100_RTC_GP(15)),
पूर्ण;

अटल स्थिर काष्ठा regmap_range ac100_अस्थिर_ranges[] = अणु
	regmap_reg_range(AC100_CHIP_AUDIO_RST, AC100_PLL_CTRL2),
	regmap_reg_range(AC100_HMIC_STATUS, AC100_HMIC_STATUS),
	regmap_reg_range(AC100_ADC_DAP_L_STA, AC100_ADC_DAP_L_STA),
	regmap_reg_range(AC100_SRC1_CTRL1, AC100_SRC1_CTRL1),
	regmap_reg_range(AC100_SRC1_CTRL3, AC100_SRC2_CTRL1),
	regmap_reg_range(AC100_SRC2_CTRL3, AC100_SRC2_CTRL4),
	regmap_reg_range(AC100_RTC_RST, AC100_RTC_RST),
	regmap_reg_range(AC100_RTC_SEC, AC100_ALM_INT_STA),
	regmap_reg_range(AC100_ALM_SEC, AC100_ALM_UPD),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table ac100_ग_लिखोable_table = अणु
	.yes_ranges	= ac100_ग_लिखोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(ac100_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table ac100_अस्थिर_table = अणु
	.yes_ranges	= ac100_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(ac100_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config ac100_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 16,
	.wr_table	= &ac100_ग_लिखोable_table,
	.अस्थिर_table	= &ac100_अस्थिर_table,
	.max_रेजिस्टर	= AC100_RTC_GP(15),
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल काष्ठा mfd_cell ac100_cells[] = अणु
	अणु
		.name		= "ac100-codec",
		.of_compatible	= "x-powers,ac100-codec",
	पूर्ण, अणु
		.name		= "ac100-rtc",
		.of_compatible	= "x-powers,ac100-rtc",
	पूर्ण,
पूर्ण;

अटल पूर्णांक ac100_rsb_probe(काष्ठा sunxi_rsb_device *rdev)
अणु
	काष्ठा ac100_dev *ac100;
	पूर्णांक ret;

	ac100 = devm_kzalloc(&rdev->dev, माप(*ac100), GFP_KERNEL);
	अगर (!ac100)
		वापस -ENOMEM;

	ac100->dev = &rdev->dev;
	sunxi_rsb_device_set_drvdata(rdev, ac100);

	ac100->regmap = devm_regmap_init_sunxi_rsb(rdev, &ac100_regmap_config);
	अगर (IS_ERR(ac100->regmap)) अणु
		ret = PTR_ERR(ac100->regmap);
		dev_err(ac100->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(ac100->dev, PLATFORM_DEVID_NONE, ac100_cells,
				   ARRAY_SIZE(ac100_cells), शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(ac100->dev, "failed to add MFD devices: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ac100_of_match[] = अणु
	अणु .compatible = "x-powers,ac100" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ac100_of_match);

अटल काष्ठा sunxi_rsb_driver ac100_rsb_driver = अणु
	.driver = अणु
		.name	= "ac100",
		.of_match_table	= of_match_ptr(ac100_of_match),
	पूर्ण,
	.probe	= ac100_rsb_probe,
पूर्ण;
module_sunxi_rsb_driver(ac100_rsb_driver);

MODULE_DESCRIPTION("Audio codec MFD core driver for AC100");
MODULE_AUTHOR("Chen-Yu Tsai <wens@csie.org>");
MODULE_LICENSE("GPL v2");
