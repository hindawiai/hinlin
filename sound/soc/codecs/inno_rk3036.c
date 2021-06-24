<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver of Inno codec क्रम rk3036 by Rockchip Inc.
 *
 * Author: Rockchip Inc.
 * Author: Zheng ShunQian<zhengsq@rock-chips.com>
 */

#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

#समावेश "inno_rk3036.h"

काष्ठा rk3036_codec_priv अणु
	व्योम __iomem *base;
	काष्ठा clk *pclk;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_MINMAX(rk3036_codec_hp_tlv, -39, 0);

अटल पूर्णांक rk3036_codec_antipop_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rk3036_codec_antipop_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	पूर्णांक val, regval;

	regval = snd_soc_component_पढ़ो(component, INNO_R09);
	val = ((regval >> INNO_R09_HPL_ANITPOP_SHIFT) &
	       INNO_R09_HP_ANTIPOP_MSK) == INNO_R09_HP_ANTIPOP_ON;
	ucontrol->value.पूर्णांकeger.value[0] = val;

	val = ((regval >> INNO_R09_HPR_ANITPOP_SHIFT) &
	       INNO_R09_HP_ANTIPOP_MSK) == INNO_R09_HP_ANTIPOP_ON;
	ucontrol->value.पूर्णांकeger.value[1] = val;

	वापस 0;
पूर्ण

अटल पूर्णांक rk3036_codec_antipop_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	पूर्णांक val, ret, regmsk;

	val = (ucontrol->value.पूर्णांकeger.value[0] ?
	       INNO_R09_HP_ANTIPOP_ON : INNO_R09_HP_ANTIPOP_OFF) <<
	      INNO_R09_HPL_ANITPOP_SHIFT;
	val |= (ucontrol->value.पूर्णांकeger.value[1] ?
		INNO_R09_HP_ANTIPOP_ON : INNO_R09_HP_ANTIPOP_OFF) <<
	       INNO_R09_HPR_ANITPOP_SHIFT;

	regmsk = INNO_R09_HP_ANTIPOP_MSK << INNO_R09_HPL_ANITPOP_SHIFT |
		 INNO_R09_HP_ANTIPOP_MSK << INNO_R09_HPR_ANITPOP_SHIFT;

	ret = snd_soc_component_update_bits(component, INNO_R09,
					    regmsk, val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

#घोषणा SOC_RK3036_CODEC_ANTIPOP_DECL(xname) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = rk3036_codec_antipop_info, .get = rk3036_codec_antipop_get, \
	.put = rk3036_codec_antipop_put, पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rk3036_codec_dapm_controls[] = अणु
	SOC_DOUBLE_R_RANGE_TLV("Headphone Volume", INNO_R07, INNO_R08,
		INNO_HP_GAIN_SHIFT, INNO_HP_GAIN_N39DB,
		INNO_HP_GAIN_0DB, 0, rk3036_codec_hp_tlv),
	SOC_DOUBLE("Zero Cross Switch", INNO_R06, INNO_R06_VOUTL_CZ_SHIFT,
		INNO_R06_VOUTR_CZ_SHIFT, 1, 0),
	SOC_DOUBLE("Headphone Switch", INNO_R09, INNO_R09_HPL_MUTE_SHIFT,
		INNO_R09_HPR_MUTE_SHIFT, 1, 0),
	SOC_RK3036_CODEC_ANTIPOP_DECL("Anti-pop Switch"),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rk3036_codec_hpl_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DAC Left Out Switch", INNO_R09,
			INNO_R09_DACL_SWITCH_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rk3036_codec_hpr_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DAC Right Out Switch", INNO_R09,
			INNO_R09_DACR_SWITCH_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rk3036_codec_hpl_चयन_controls[] = अणु
	SOC_DAPM_SINGLE("HP Left Out Switch", INNO_R05,
			INNO_R05_HPL_WORK_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rk3036_codec_hpr_चयन_controls[] = अणु
	SOC_DAPM_SINGLE("HP Right Out Switch", INNO_R05,
			INNO_R05_HPR_WORK_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rk3036_codec_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY_S("DAC PWR", 1, INNO_R06,
			      INNO_R06_DAC_EN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DACL VREF", 2, INNO_R04,
			      INNO_R04_DACL_VREF_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DACR VREF", 2, INNO_R04,
			      INNO_R04_DACR_VREF_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DACL HiLo VREF", 3, INNO_R06,
			      INNO_R06_DACL_HILO_VREF_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DACR HiLo VREF", 3, INNO_R06,
			      INNO_R06_DACR_HILO_VREF_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DACR CLK", 3, INNO_R04,
			      INNO_R04_DACR_CLK_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DACL CLK", 3, INNO_R04,
			      INNO_R04_DACL_CLK_SHIFT, 0, शून्य, 0),

	SND_SOC_DAPM_DAC("DACL", "Left Playback", INNO_R04,
			 INNO_R04_DACL_SW_SHIFT, 0),
	SND_SOC_DAPM_DAC("DACR", "Right Playback", INNO_R04,
			 INNO_R04_DACR_SW_SHIFT, 0),

	SND_SOC_DAPM_MIXER("Left Headphone Mixer", SND_SOC_NOPM, 0, 0,
		rk3036_codec_hpl_mixer_controls,
		ARRAY_SIZE(rk3036_codec_hpl_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Headphone Mixer", SND_SOC_NOPM, 0, 0,
		rk3036_codec_hpr_mixer_controls,
		ARRAY_SIZE(rk3036_codec_hpr_mixer_controls)),

	SND_SOC_DAPM_PGA("HP Left Out", INNO_R05,
			 INNO_R05_HPL_EN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HP Right Out", INNO_R05,
			 INNO_R05_HPR_EN_SHIFT, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("HP Left Switch",  SND_SOC_NOPM, 0, 0,
			   rk3036_codec_hpl_चयन_controls,
			   ARRAY_SIZE(rk3036_codec_hpl_चयन_controls)),
	SND_SOC_DAPM_MIXER("HP Right Switch",  SND_SOC_NOPM, 0, 0,
			   rk3036_codec_hpr_चयन_controls,
			   ARRAY_SIZE(rk3036_codec_hpr_चयन_controls)),

	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rk3036_codec_dapm_routes[] = अणु
	अणु"DACL VREF", शून्य, "DAC PWR"पूर्ण,
	अणु"DACR VREF", शून्य, "DAC PWR"पूर्ण,
	अणु"DACL HiLo VREF", शून्य, "DAC PWR"पूर्ण,
	अणु"DACR HiLo VREF", शून्य, "DAC PWR"पूर्ण,
	अणु"DACL CLK", शून्य, "DAC PWR"पूर्ण,
	अणु"DACR CLK", शून्य, "DAC PWR"पूर्ण,

	अणु"DACL", शून्य, "DACL VREF"पूर्ण,
	अणु"DACL", शून्य, "DACL HiLo VREF"पूर्ण,
	अणु"DACL", शून्य, "DACL CLK"पूर्ण,
	अणु"DACR", शून्य, "DACR VREF"पूर्ण,
	अणु"DACR", शून्य, "DACR HiLo VREF"पूर्ण,
	अणु"DACR", शून्य, "DACR CLK"पूर्ण,

	अणु"Left Headphone Mixer", "DAC Left Out Switch", "DACL"पूर्ण,
	अणु"Right Headphone Mixer", "DAC Right Out Switch", "DACR"पूर्ण,
	अणु"HP Left Out", शून्य, "Left Headphone Mixer"पूर्ण,
	अणु"HP Right Out", शून्य, "Right Headphone Mixer"पूर्ण,

	अणु"HP Left Switch", "HP Left Out Switch", "HP Left Out"पूर्ण,
	अणु"HP Right Switch", "HP Right Out Switch", "HP Right Out"पूर्ण,

	अणु"HPL", शून्य, "HP Left Switch"पूर्ण,
	अणु"HPR", शून्य, "HP Right Switch"पूर्ण,
पूर्ण;

अटल पूर्णांक rk3036_codec_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक reg01_val = 0,  reg02_val = 0, reg03_val = 0;

	dev_dbg(component->dev, "rk3036_codec dai set fmt : %08x\n", fmt);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg01_val |= INNO_R01_PINसूची_IN_SLAVE |
			     INNO_R01_I2SMODE_SLAVE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		reg01_val |= INNO_R01_PINसूची_OUT_MASTER |
			     INNO_R01_I2SMODE_MASTER;
		अवरोध;
	शेष:
		dev_err(component->dev, "invalid fmt\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		reg02_val |= INNO_R02_DACM_PCM;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		reg02_val |= INNO_R02_DACM_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		reg02_val |= INNO_R02_DACM_RJM;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg02_val |= INNO_R02_DACM_LJM;
		अवरोध;
	शेष:
		dev_err(component->dev, "set dai format failed\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		reg02_val |= INNO_R02_LRCP_NORMAL;
		reg03_val |= INNO_R03_BCP_NORMAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		reg02_val |= INNO_R02_LRCP_REVERSAL;
		reg03_val |= INNO_R03_BCP_REVERSAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg02_val |= INNO_R02_LRCP_REVERSAL;
		reg03_val |= INNO_R03_BCP_NORMAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		reg02_val |= INNO_R02_LRCP_NORMAL;
		reg03_val |= INNO_R03_BCP_REVERSAL;
		अवरोध;
	शेष:
		dev_err(component->dev, "set dai format failed\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, INNO_R01, INNO_R01_I2SMODE_MSK |
			    INNO_R01_PINसूची_MSK, reg01_val);
	snd_soc_component_update_bits(component, INNO_R02, INNO_R02_LRCP_MSK |
			    INNO_R02_DACM_MSK, reg02_val);
	snd_soc_component_update_bits(component, INNO_R03, INNO_R03_BCP_MSK, reg03_val);

	वापस 0;
पूर्ण

अटल पूर्णांक rk3036_codec_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *hw_params,
				      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक reg02_val = 0, reg03_val = 0;

	चयन (params_क्रमmat(hw_params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		reg02_val |= INNO_R02_VWL_16BIT;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		reg02_val |= INNO_R02_VWL_20BIT;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		reg02_val |= INNO_R02_VWL_24BIT;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		reg02_val |= INNO_R02_VWL_32BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg02_val |= INNO_R02_LRCP_NORMAL;
	reg03_val |= INNO_R03_FWL_32BIT | INNO_R03_DACR_WORK;

	snd_soc_component_update_bits(component, INNO_R02, INNO_R02_LRCP_MSK |
			    INNO_R02_VWL_MSK, reg02_val);
	snd_soc_component_update_bits(component, INNO_R03, INNO_R03_DACR_MSK |
			    INNO_R03_FWL_MSK, reg03_val);
	वापस 0;
पूर्ण

#घोषणा RK3036_CODEC_RATES (SNDRV_PCM_RATE_8000  | \
			    SNDRV_PCM_RATE_16000 | \
			    SNDRV_PCM_RATE_32000 | \
			    SNDRV_PCM_RATE_44100 | \
			    SNDRV_PCM_RATE_48000 | \
			    SNDRV_PCM_RATE_96000)

#घोषणा RK3036_CODEC_FMTS (SNDRV_PCM_FMTBIT_S16_LE  | \
			   SNDRV_PCM_FMTBIT_S20_3LE | \
			   SNDRV_PCM_FMTBIT_S24_LE  | \
			   SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops rk3036_codec_dai_ops = अणु
	.set_fmt	= rk3036_codec_dai_set_fmt,
	.hw_params	= rk3036_codec_dai_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rk3036_codec_dai_driver[] = अणु
	अणु
		.name = "rk3036-codec-dai",
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RK3036_CODEC_RATES,
			.क्रमmats = RK3036_CODEC_FMTS,
		पूर्ण,
		.ops = &rk3036_codec_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल व्योम rk3036_codec_reset(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_ग_लिखो(component, INNO_R00,
		      INNO_R00_CSR_RESET | INNO_R00_CDCR_RESET);
	snd_soc_component_ग_लिखो(component, INNO_R00,
		      INNO_R00_CSR_WORK | INNO_R00_CDCR_WORK);
पूर्ण

अटल पूर्णांक rk3036_codec_probe(काष्ठा snd_soc_component *component)
अणु
	rk3036_codec_reset(component);
	वापस 0;
पूर्ण

अटल व्योम rk3036_codec_हटाओ(काष्ठा snd_soc_component *component)
अणु
	rk3036_codec_reset(component);
पूर्ण

अटल पूर्णांक rk3036_codec_set_bias_level(काष्ठा snd_soc_component *component,
				       क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_STANDBY:
		/* set a big current क्रम capacitor अक्षरging. */
		snd_soc_component_ग_लिखो(component, INNO_R10, INNO_R10_MAX_CUR);
		/* start preअक्षरge */
		snd_soc_component_ग_लिखो(component, INNO_R06, INNO_R06_DAC_PRECHARGE);

		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* set a big current क्रम capacitor disअक्षरging. */
		snd_soc_component_ग_लिखो(component, INNO_R10, INNO_R10_MAX_CUR);
		/* start disअक्षरge. */
		snd_soc_component_ग_लिखो(component, INNO_R06, INNO_R06_DAC_DISCHARGE);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver rk3036_codec_driver = अणु
	.probe			= rk3036_codec_probe,
	.हटाओ			= rk3036_codec_हटाओ,
	.set_bias_level		= rk3036_codec_set_bias_level,
	.controls		= rk3036_codec_dapm_controls,
	.num_controls		= ARRAY_SIZE(rk3036_codec_dapm_controls),
	.dapm_routes		= rk3036_codec_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rk3036_codec_dapm_routes),
	.dapm_widमाला_लो		= rk3036_codec_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rk3036_codec_dapm_widमाला_लो),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rk3036_codec_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
पूर्ण;

#घोषणा GRF_SOC_CON0		0x00140
#घोषणा GRF_ACODEC_SEL		(BIT(10) | BIT(16 + 10))

अटल पूर्णांक rk3036_codec_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk3036_codec_priv *priv;
	काष्ठा device_node *of_node = pdev->dev.of_node;
	व्योम __iomem *base;
	काष्ठा regmap *grf;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->base = base;
	priv->regmap = devm_regmap_init_mmio(&pdev->dev, priv->base,
					     &rk3036_codec_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(&pdev->dev, "init regmap failed\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	grf = syscon_regmap_lookup_by_phandle(of_node, "rockchip,grf");
	अगर (IS_ERR(grf)) अणु
		dev_err(&pdev->dev, "needs 'rockchip,grf' property\n");
		वापस PTR_ERR(grf);
	पूर्ण
	ret = regmap_ग_लिखो(grf, GRF_SOC_CON0, GRF_ACODEC_SEL);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not write to GRF: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->pclk = devm_clk_get(&pdev->dev, "acodec_pclk");
	अगर (IS_ERR(priv->pclk))
		वापस PTR_ERR(priv->pclk);

	ret = clk_prepare_enable(priv->pclk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable clk\n");
		वापस ret;
	पूर्ण

	priv->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, priv);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &rk3036_codec_driver,
				     rk3036_codec_dai_driver,
				     ARRAY_SIZE(rk3036_codec_dai_driver));
	अगर (ret) अणु
		clk_disable_unprepare(priv->pclk);
		dev_set_drvdata(&pdev->dev, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rk3036_codec_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk3036_codec_priv *priv = dev_get_drvdata(&pdev->dev);

	clk_disable_unprepare(priv->pclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rk3036_codec_of_match[] __maybe_unused = अणु
	अणु .compatible = "rockchip,rk3036-codec", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rk3036_codec_of_match);

अटल काष्ठा platक्रमm_driver rk3036_codec_platक्रमm_driver = अणु
	.driver = अणु
		.name = "rk3036-codec-platform",
		.of_match_table = of_match_ptr(rk3036_codec_of_match),
	पूर्ण,
	.probe = rk3036_codec_platक्रमm_probe,
	.हटाओ = rk3036_codec_platक्रमm_हटाओ,
पूर्ण;

module_platक्रमm_driver(rk3036_codec_platक्रमm_driver);

MODULE_AUTHOR("Rockchip Inc.");
MODULE_DESCRIPTION("Rockchip rk3036 codec driver");
MODULE_LICENSE("GPL");
