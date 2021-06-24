<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt8192-afe-gpio.c  --  Mediatek 8192 afe gpio ctrl
//
// Copyright (c) 2020 MediaTek Inc.
// Author: Shane Chien <shane.chien@mediatek.com>
//

#समावेश <linux/gpपन.स>
#समावेश <linux/pinctrl/consumer.h>

#समावेश "mt8192-afe-common.h"
#समावेश "mt8192-afe-gpio.h"

अटल काष्ठा pinctrl *aud_pinctrl;

क्रमागत mt8192_afe_gpio अणु
	MT8192_AFE_GPIO_DAT_MISO_OFF,
	MT8192_AFE_GPIO_DAT_MISO_ON,
	MT8192_AFE_GPIO_DAT_MOSI_OFF,
	MT8192_AFE_GPIO_DAT_MOSI_ON,
	MT8192_AFE_GPIO_DAT_MISO_CH34_OFF,
	MT8192_AFE_GPIO_DAT_MISO_CH34_ON,
	MT8192_AFE_GPIO_DAT_MOSI_CH34_OFF,
	MT8192_AFE_GPIO_DAT_MOSI_CH34_ON,
	MT8192_AFE_GPIO_I2S0_OFF,
	MT8192_AFE_GPIO_I2S0_ON,
	MT8192_AFE_GPIO_I2S1_OFF,
	MT8192_AFE_GPIO_I2S1_ON,
	MT8192_AFE_GPIO_I2S2_OFF,
	MT8192_AFE_GPIO_I2S2_ON,
	MT8192_AFE_GPIO_I2S3_OFF,
	MT8192_AFE_GPIO_I2S3_ON,
	MT8192_AFE_GPIO_I2S5_OFF,
	MT8192_AFE_GPIO_I2S5_ON,
	MT8192_AFE_GPIO_I2S6_OFF,
	MT8192_AFE_GPIO_I2S6_ON,
	MT8192_AFE_GPIO_I2S7_OFF,
	MT8192_AFE_GPIO_I2S7_ON,
	MT8192_AFE_GPIO_I2S8_OFF,
	MT8192_AFE_GPIO_I2S8_ON,
	MT8192_AFE_GPIO_I2S9_OFF,
	MT8192_AFE_GPIO_I2S9_ON,
	MT8192_AFE_GPIO_VOW_DAT_OFF,
	MT8192_AFE_GPIO_VOW_DAT_ON,
	MT8192_AFE_GPIO_VOW_CLK_OFF,
	MT8192_AFE_GPIO_VOW_CLK_ON,
	MT8192_AFE_GPIO_CLK_MOSI_OFF,
	MT8192_AFE_GPIO_CLK_MOSI_ON,
	MT8192_AFE_GPIO_TDM_OFF,
	MT8192_AFE_GPIO_TDM_ON,
	MT8192_AFE_GPIO_GPIO_NUM
पूर्ण;

काष्ठा audio_gpio_attr अणु
	स्थिर अक्षर *name;
	bool gpio_prepare;
	काष्ठा pinctrl_state *gpioctrl;
पूर्ण;

अटल काष्ठा audio_gpio_attr aud_gpios[MT8192_AFE_GPIO_GPIO_NUM] = अणु
	[MT8192_AFE_GPIO_DAT_MISO_OFF] = अणु"aud_dat_miso_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_DAT_MISO_ON] = अणु"aud_dat_miso_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_DAT_MOSI_OFF] = अणु"aud_dat_mosi_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_DAT_MOSI_ON] = अणु"aud_dat_mosi_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S0_OFF] = अणु"aud_gpio_i2s0_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S0_ON] = अणु"aud_gpio_i2s0_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S1_OFF] = अणु"aud_gpio_i2s1_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S1_ON] = अणु"aud_gpio_i2s1_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S2_OFF] = अणु"aud_gpio_i2s2_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S2_ON] = अणु"aud_gpio_i2s2_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S3_OFF] = अणु"aud_gpio_i2s3_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S3_ON] = अणु"aud_gpio_i2s3_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S5_OFF] = अणु"aud_gpio_i2s5_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S5_ON] = अणु"aud_gpio_i2s5_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S6_OFF] = अणु"aud_gpio_i2s6_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S6_ON] = अणु"aud_gpio_i2s6_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S7_OFF] = अणु"aud_gpio_i2s7_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S7_ON] = अणु"aud_gpio_i2s7_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S8_OFF] = अणु"aud_gpio_i2s8_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S8_ON] = अणु"aud_gpio_i2s8_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S9_OFF] = अणु"aud_gpio_i2s9_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_I2S9_ON] = अणु"aud_gpio_i2s9_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_TDM_OFF] = अणु"aud_gpio_tdm_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_TDM_ON] = अणु"aud_gpio_tdm_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_VOW_DAT_OFF] = अणु"vow_dat_miso_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_VOW_DAT_ON] = अणु"vow_dat_miso_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_VOW_CLK_OFF] = अणु"vow_clk_miso_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_VOW_CLK_ON] = अणु"vow_clk_miso_on", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_DAT_MISO_CH34_OFF] = अणु"aud_dat_miso_ch34_off",
					       false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_DAT_MISO_CH34_ON] = अणु"aud_dat_miso_ch34_on",
					      false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_DAT_MOSI_CH34_OFF] = अणु"aud_dat_mosi_ch34_off",
					       false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_DAT_MOSI_CH34_ON] = अणु"aud_dat_mosi_ch34_on",
					      false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_CLK_MOSI_OFF] = अणु"aud_clk_mosi_off", false, शून्यपूर्ण,
	[MT8192_AFE_GPIO_CLK_MOSI_ON] = अणु"aud_clk_mosi_on", false, शून्यपूर्ण,
पूर्ण;

अटल DEFINE_MUTEX(gpio_request_mutex);

अटल पूर्णांक mt8192_afe_gpio_select(काष्ठा device *dev,
				  क्रमागत mt8192_afe_gpio type)
अणु
	पूर्णांक ret;

	अगर (type < 0 || type >= MT8192_AFE_GPIO_GPIO_NUM) अणु
		dev_err(dev, "%s(), error, invalid gpio type %d\n",
			__func__, type);
		वापस -EINVAL;
	पूर्ण

	अगर (!aud_gpios[type].gpio_prepare) अणु
		dev_warn(dev, "%s(), error, gpio type %d not prepared\n",
			 __func__, type);
		वापस -EIO;
	पूर्ण

	ret = pinctrl_select_state(aud_pinctrl,
				   aud_gpios[type].gpioctrl);
	अगर (ret) अणु
		dev_dbg(dev, "%s(), error, can not set gpio type %d\n",
			__func__, type);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक mt8192_afe_gpio_init(काष्ठा device *dev)
अणु
	पूर्णांक i, ret;

	aud_pinctrl = devm_pinctrl_get(dev);
	अगर (IS_ERR(aud_pinctrl)) अणु
		ret = PTR_ERR(aud_pinctrl);
		dev_err(dev, "%s(), ret %d, cannot get aud_pinctrl!\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(aud_gpios); i++) अणु
		aud_gpios[i].gpioctrl = pinctrl_lookup_state(aud_pinctrl,
							     aud_gpios[i].name);
		अगर (IS_ERR(aud_gpios[i].gpioctrl)) अणु
			ret = PTR_ERR(aud_gpios[i].gpioctrl);
			dev_dbg(dev, "%s(), pinctrl_lookup_state %s fail, ret %d\n",
				__func__, aud_gpios[i].name, ret);
		पूर्ण अन्यथा अणु
			aud_gpios[i].gpio_prepare = true;
		पूर्ण
	पूर्ण

	mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_CLK_MOSI_ON);

	/* gpio status init */
	mt8192_afe_gpio_request(dev, false, MT8192_DAI_ADDA, 0);
	mt8192_afe_gpio_request(dev, false, MT8192_DAI_ADDA, 1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mt8192_afe_gpio_init);

अटल पूर्णांक mt8192_afe_gpio_adda_dl(काष्ठा device *dev, bool enable)
अणु
	अगर (enable) अणु
		वापस mt8192_afe_gpio_select(dev,
					      MT8192_AFE_GPIO_DAT_MOSI_ON);
	पूर्ण अन्यथा अणु
		वापस mt8192_afe_gpio_select(dev,
					      MT8192_AFE_GPIO_DAT_MOSI_OFF);
	पूर्ण
पूर्ण

अटल पूर्णांक mt8192_afe_gpio_adda_ul(काष्ठा device *dev, bool enable)
अणु
	अगर (enable) अणु
		वापस mt8192_afe_gpio_select(dev,
					      MT8192_AFE_GPIO_DAT_MISO_ON);
	पूर्ण अन्यथा अणु
		वापस mt8192_afe_gpio_select(dev,
					      MT8192_AFE_GPIO_DAT_MISO_OFF);
	पूर्ण
पूर्ण

अटल पूर्णांक mt8192_afe_gpio_adda_ch34_dl(काष्ठा device *dev, bool enable)
अणु
	अगर (enable) अणु
		वापस mt8192_afe_gpio_select(dev,
			MT8192_AFE_GPIO_DAT_MOSI_CH34_ON);
	पूर्ण अन्यथा अणु
		वापस mt8192_afe_gpio_select(dev,
			MT8192_AFE_GPIO_DAT_MOSI_CH34_OFF);
	पूर्ण
पूर्ण

अटल पूर्णांक mt8192_afe_gpio_adda_ch34_ul(काष्ठा device *dev, bool enable)
अणु
	अगर (enable) अणु
		वापस mt8192_afe_gpio_select(dev,
			MT8192_AFE_GPIO_DAT_MISO_CH34_ON);
	पूर्ण अन्यथा अणु
		वापस mt8192_afe_gpio_select(dev,
			MT8192_AFE_GPIO_DAT_MISO_CH34_OFF);
	पूर्ण
पूर्ण

पूर्णांक mt8192_afe_gpio_request(काष्ठा device *dev, bool enable,
			    पूर्णांक dai, पूर्णांक uplink)
अणु
	mutex_lock(&gpio_request_mutex);
	चयन (dai) अणु
	हाल MT8192_DAI_ADDA:
		अगर (uplink)
			mt8192_afe_gpio_adda_ul(dev, enable);
		अन्यथा
			mt8192_afe_gpio_adda_dl(dev, enable);
		अवरोध;
	हाल MT8192_DAI_ADDA_CH34:
		अगर (uplink)
			mt8192_afe_gpio_adda_ch34_ul(dev, enable);
		अन्यथा
			mt8192_afe_gpio_adda_ch34_dl(dev, enable);
		अवरोध;
	हाल MT8192_DAI_I2S_0:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S0_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S0_OFF);
		अवरोध;
	हाल MT8192_DAI_I2S_1:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S1_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S1_OFF);
		अवरोध;
	हाल MT8192_DAI_I2S_2:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S2_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S2_OFF);
		अवरोध;
	हाल MT8192_DAI_I2S_3:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S3_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S3_OFF);
		अवरोध;
	हाल MT8192_DAI_I2S_5:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S5_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S5_OFF);
		अवरोध;
	हाल MT8192_DAI_I2S_6:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S6_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S6_OFF);
		अवरोध;
	हाल MT8192_DAI_I2S_7:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S7_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S7_OFF);
		अवरोध;
	हाल MT8192_DAI_I2S_8:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S8_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S8_OFF);
		अवरोध;
	हाल MT8192_DAI_I2S_9:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S9_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_I2S9_OFF);
		अवरोध;
	हाल MT8192_DAI_TDM:
		अगर (enable)
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_TDM_ON);
		अन्यथा
			mt8192_afe_gpio_select(dev, MT8192_AFE_GPIO_TDM_OFF);
		अवरोध;
	हाल MT8192_DAI_VOW:
		अगर (enable) अणु
			mt8192_afe_gpio_select(dev,
					       MT8192_AFE_GPIO_VOW_CLK_ON);
			mt8192_afe_gpio_select(dev,
					       MT8192_AFE_GPIO_VOW_DAT_ON);
		पूर्ण अन्यथा अणु
			mt8192_afe_gpio_select(dev,
					       MT8192_AFE_GPIO_VOW_CLK_OFF);
			mt8192_afe_gpio_select(dev,
					       MT8192_AFE_GPIO_VOW_DAT_OFF);
		पूर्ण
		अवरोध;
	शेष:
		mutex_unlock(&gpio_request_mutex);
		dev_warn(dev, "%s(), invalid dai %d\n", __func__, dai);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(&gpio_request_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mt8192_afe_gpio_request);
