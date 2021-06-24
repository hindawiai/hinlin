<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Socionext UniPhier EVEA ADC/DAC codec driver.
//
// Copyright (c) 2016-2017 Socionext Inc.

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#घोषणा DRV_NAME        "evea"
#घोषणा EVEA_RATES      SNDRV_PCM_RATE_48000
#घोषणा EVEA_FORMATS    SNDRV_PCM_FMTBIT_S32_LE

#घोषणा AADCPOW(n)                           (0x0078 + 0x04 * (n))
#घोषणा   AADCPOW_AADC_POWD                   BIT(0)
#घोषणा ALINSW1                              0x0088
#घोषणा   ALINSW1_SEL1_SHIFT                  3
#घोषणा AHPOUTPOW                            0x0098
#घोषणा   AHPOUTPOW_HP_ON                     BIT(4)
#घोषणा ALINEPOW                             0x009c
#घोषणा   ALINEPOW_LIN2_POWD                  BIT(3)
#घोषणा   ALINEPOW_LIN1_POWD                  BIT(4)
#घोषणा ALO1OUTPOW                           0x00a8
#घोषणा   ALO1OUTPOW_LO1_ON                   BIT(4)
#घोषणा ALO2OUTPOW                           0x00ac
#घोषणा   ALO2OUTPOW_ADAC2_MUTE               BIT(0)
#घोषणा   ALO2OUTPOW_LO2_ON                   BIT(4)
#घोषणा AANAPOW                              0x00b8
#घोषणा   AANAPOW_A_POWD                      BIT(4)
#घोषणा ADACSEQ1(n)                          (0x0144 + 0x40 * (n))
#घोषणा   ADACSEQ1_MMUTE                      BIT(1)
#घोषणा ADACSEQ2(n)                          (0x0160 + 0x40 * (n))
#घोषणा   ADACSEQ2_ADACIN_FIX                 BIT(0)
#घोषणा ADAC1ODC                             0x0200
#घोषणा   ADAC1ODC_HP_DIS_RES_MASK            GENMASK(2, 1)
#घोषणा   ADAC1ODC_HP_DIS_RES_OFF             (0x0 << 1)
#घोषणा   ADAC1ODC_HP_DIS_RES_ON              (0x3 << 1)
#घोषणा   ADAC1ODC_ADAC_RAMPCLT_MASK          GENMASK(8, 7)
#घोषणा   ADAC1ODC_ADAC_RAMPCLT_NORMAL        (0x0 << 7)
#घोषणा   ADAC1ODC_ADAC_RAMPCLT_REDUCE        (0x1 << 7)

काष्ठा evea_priv अणु
	काष्ठा clk *clk, *clk_exiv;
	काष्ठा reset_control *rst, *rst_exiv, *rst_adamv;
	काष्ठा regmap *regmap;

	पूर्णांक चयन_lin;
	पूर्णांक चयन_lo;
	पूर्णांक चयन_hp;
पूर्ण;

अटल स्थिर अक्षर * स्थिर linsw1_sel1_text[] = अणु
	"LIN1", "LIN2", "LIN3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(linsw1_sel1_क्रमागत,
	ALINSW1, ALINSW1_SEL1_SHIFT,
	linsw1_sel1_text);

अटल स्थिर काष्ठा snd_kcontrol_new linesw1_mux[] = अणु
	SOC_DAPM_ENUM("Line In 1 Source", linsw1_sel1_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget evea_widमाला_लो[] = अणु
	SND_SOC_DAPM_ADC("ADC", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("Line In 1 Mux", SND_SOC_NOPM, 0, 0, linesw1_mux),
	SND_SOC_DAPM_INPUT("LIN1_LP"),
	SND_SOC_DAPM_INPUT("LIN1_RP"),
	SND_SOC_DAPM_INPUT("LIN2_LP"),
	SND_SOC_DAPM_INPUT("LIN2_RP"),
	SND_SOC_DAPM_INPUT("LIN3_LP"),
	SND_SOC_DAPM_INPUT("LIN3_RP"),

	SND_SOC_DAPM_DAC("DAC HP", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC LO1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC LO2", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("HP1_L"),
	SND_SOC_DAPM_OUTPUT("HP1_R"),
	SND_SOC_DAPM_OUTPUT("LO2_L"),
	SND_SOC_DAPM_OUTPUT("LO2_R"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route evea_routes[] = अणु
	अणु "Line In 1", शून्य, "ADC" पूर्ण,
	अणु "ADC", शून्य, "Line In 1 Mux" पूर्ण,
	अणु "Line In 1 Mux", "LIN1", "LIN1_LP" पूर्ण,
	अणु "Line In 1 Mux", "LIN1", "LIN1_RP" पूर्ण,
	अणु "Line In 1 Mux", "LIN2", "LIN2_LP" पूर्ण,
	अणु "Line In 1 Mux", "LIN2", "LIN2_RP" पूर्ण,
	अणु "Line In 1 Mux", "LIN3", "LIN3_LP" पूर्ण,
	अणु "Line In 1 Mux", "LIN3", "LIN3_RP" पूर्ण,

	अणु "DAC HP", शून्य, "Headphone 1" पूर्ण,
	अणु "DAC LO1", शून्य, "Line Out 1" पूर्ण,
	अणु "DAC LO2", शून्य, "Line Out 2" पूर्ण,
	अणु "HP1_L", शून्य, "DAC HP" पूर्ण,
	अणु "HP1_R", शून्य, "DAC HP" पूर्ण,
	अणु "LO2_L", शून्य, "DAC LO2" पूर्ण,
	अणु "LO2_R", शून्य, "DAC LO2" पूर्ण,
पूर्ण;

अटल व्योम evea_set_घातer_state_on(काष्ठा evea_priv *evea)
अणु
	काष्ठा regmap *map = evea->regmap;

	regmap_update_bits(map, AANAPOW, AANAPOW_A_POWD,
			   AANAPOW_A_POWD);

	regmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_RES_MASK,
			   ADAC1ODC_HP_DIS_RES_ON);

	regmap_update_bits(map, ADAC1ODC, ADAC1ODC_ADAC_RAMPCLT_MASK,
			   ADAC1ODC_ADAC_RAMPCLT_REDUCE);

	regmap_update_bits(map, ADACSEQ2(0), ADACSEQ2_ADACIN_FIX, 0);
	regmap_update_bits(map, ADACSEQ2(1), ADACSEQ2_ADACIN_FIX, 0);
	regmap_update_bits(map, ADACSEQ2(2), ADACSEQ2_ADACIN_FIX, 0);
पूर्ण

अटल व्योम evea_set_घातer_state_off(काष्ठा evea_priv *evea)
अणु
	काष्ठा regmap *map = evea->regmap;

	regmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_RES_MASK,
			   ADAC1ODC_HP_DIS_RES_ON);

	regmap_update_bits(map, ADACSEQ1(0), ADACSEQ1_MMUTE,
			   ADACSEQ1_MMUTE);
	regmap_update_bits(map, ADACSEQ1(1), ADACSEQ1_MMUTE,
			   ADACSEQ1_MMUTE);
	regmap_update_bits(map, ADACSEQ1(2), ADACSEQ1_MMUTE,
			   ADACSEQ1_MMUTE);

	regmap_update_bits(map, ALO1OUTPOW, ALO1OUTPOW_LO1_ON, 0);
	regmap_update_bits(map, ALO2OUTPOW, ALO2OUTPOW_LO2_ON, 0);
	regmap_update_bits(map, AHPOUTPOW, AHPOUTPOW_HP_ON, 0);
पूर्ण

अटल पूर्णांक evea_update_चयन_lin(काष्ठा evea_priv *evea)
अणु
	काष्ठा regmap *map = evea->regmap;

	अगर (evea->चयन_lin) अणु
		regmap_update_bits(map, ALINEPOW,
				   ALINEPOW_LIN2_POWD | ALINEPOW_LIN1_POWD,
				   ALINEPOW_LIN2_POWD | ALINEPOW_LIN1_POWD);

		regmap_update_bits(map, AADCPOW(0), AADCPOW_AADC_POWD,
				   AADCPOW_AADC_POWD);
		regmap_update_bits(map, AADCPOW(1), AADCPOW_AADC_POWD,
				   AADCPOW_AADC_POWD);
	पूर्ण अन्यथा अणु
		regmap_update_bits(map, AADCPOW(0), AADCPOW_AADC_POWD, 0);
		regmap_update_bits(map, AADCPOW(1), AADCPOW_AADC_POWD, 0);

		regmap_update_bits(map, ALINEPOW,
				   ALINEPOW_LIN2_POWD | ALINEPOW_LIN1_POWD, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evea_update_चयन_lo(काष्ठा evea_priv *evea)
अणु
	काष्ठा regmap *map = evea->regmap;

	अगर (evea->चयन_lo) अणु
		regmap_update_bits(map, ADACSEQ1(0), ADACSEQ1_MMUTE, 0);
		regmap_update_bits(map, ADACSEQ1(2), ADACSEQ1_MMUTE, 0);

		regmap_update_bits(map, ALO1OUTPOW, ALO1OUTPOW_LO1_ON,
				   ALO1OUTPOW_LO1_ON);
		regmap_update_bits(map, ALO2OUTPOW,
				   ALO2OUTPOW_ADAC2_MUTE | ALO2OUTPOW_LO2_ON,
				   ALO2OUTPOW_ADAC2_MUTE | ALO2OUTPOW_LO2_ON);
	पूर्ण अन्यथा अणु
		regmap_update_bits(map, ADACSEQ1(0), ADACSEQ1_MMUTE,
				   ADACSEQ1_MMUTE);
		regmap_update_bits(map, ADACSEQ1(2), ADACSEQ1_MMUTE,
				   ADACSEQ1_MMUTE);

		regmap_update_bits(map, ALO1OUTPOW, ALO1OUTPOW_LO1_ON, 0);
		regmap_update_bits(map, ALO2OUTPOW,
				   ALO2OUTPOW_ADAC2_MUTE | ALO2OUTPOW_LO2_ON,
				   0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evea_update_चयन_hp(काष्ठा evea_priv *evea)
अणु
	काष्ठा regmap *map = evea->regmap;

	अगर (evea->चयन_hp) अणु
		regmap_update_bits(map, ADACSEQ1(1), ADACSEQ1_MMUTE, 0);

		regmap_update_bits(map, AHPOUTPOW, AHPOUTPOW_HP_ON,
				   AHPOUTPOW_HP_ON);

		regmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_RES_MASK,
				   ADAC1ODC_HP_DIS_RES_OFF);
	पूर्ण अन्यथा अणु
		regmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_RES_MASK,
				   ADAC1ODC_HP_DIS_RES_ON);

		regmap_update_bits(map, ADACSEQ1(1), ADACSEQ1_MMUTE,
				   ADACSEQ1_MMUTE);

		regmap_update_bits(map, AHPOUTPOW, AHPOUTPOW_HP_ON, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम evea_update_चयन_all(काष्ठा evea_priv *evea)
अणु
	evea_update_चयन_lin(evea);
	evea_update_चयन_lo(evea);
	evea_update_चयन_hp(evea);
पूर्ण

अटल पूर्णांक evea_get_चयन_lin(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा evea_priv *evea = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = evea->चयन_lin;

	वापस 0;
पूर्ण

अटल पूर्णांक evea_set_चयन_lin(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा evea_priv *evea = snd_soc_component_get_drvdata(component);

	अगर (evea->चयन_lin == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	evea->चयन_lin = ucontrol->value.पूर्णांकeger.value[0];

	वापस evea_update_चयन_lin(evea);
पूर्ण

अटल पूर्णांक evea_get_चयन_lo(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा evea_priv *evea = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = evea->चयन_lo;

	वापस 0;
पूर्ण

अटल पूर्णांक evea_set_चयन_lo(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा evea_priv *evea = snd_soc_component_get_drvdata(component);

	अगर (evea->चयन_lo == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	evea->चयन_lo = ucontrol->value.पूर्णांकeger.value[0];

	वापस evea_update_चयन_lo(evea);
पूर्ण

अटल पूर्णांक evea_get_चयन_hp(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा evea_priv *evea = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = evea->चयन_hp;

	वापस 0;
पूर्ण

अटल पूर्णांक evea_set_चयन_hp(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा evea_priv *evea = snd_soc_component_get_drvdata(component);

	अगर (evea->चयन_hp == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	evea->चयन_hp = ucontrol->value.पूर्णांकeger.value[0];

	वापस evea_update_चयन_hp(evea);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new evea_controls[] = अणु
	SOC_SINGLE_BOOL_EXT("Line Capture Switch", 0,
			    evea_get_चयन_lin, evea_set_चयन_lin),
	SOC_SINGLE_BOOL_EXT("Line Playback Switch", 0,
			    evea_get_चयन_lo, evea_set_चयन_lo),
	SOC_SINGLE_BOOL_EXT("Headphone Playback Switch", 0,
			    evea_get_चयन_hp, evea_set_चयन_hp),
पूर्ण;

अटल पूर्णांक evea_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा evea_priv *evea = snd_soc_component_get_drvdata(component);

	evea->चयन_lin = 1;
	evea->चयन_lo = 1;
	evea->चयन_hp = 1;

	evea_set_घातer_state_on(evea);
	evea_update_चयन_all(evea);

	वापस 0;
पूर्ण

अटल पूर्णांक evea_codec_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा evea_priv *evea = snd_soc_component_get_drvdata(component);

	evea_set_घातer_state_off(evea);

	reset_control_निश्चित(evea->rst_adamv);
	reset_control_निश्चित(evea->rst_exiv);
	reset_control_निश्चित(evea->rst);

	clk_disable_unprepare(evea->clk_exiv);
	clk_disable_unprepare(evea->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक evea_codec_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा evea_priv *evea = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = clk_prepare_enable(evea->clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(evea->clk_exiv);
	अगर (ret)
		जाओ err_out_घड़ी;

	ret = reset_control_deनिश्चित(evea->rst);
	अगर (ret)
		जाओ err_out_घड़ी_exiv;

	ret = reset_control_deनिश्चित(evea->rst_exiv);
	अगर (ret)
		जाओ err_out_reset;

	ret = reset_control_deनिश्चित(evea->rst_adamv);
	अगर (ret)
		जाओ err_out_reset_exiv;

	evea_set_घातer_state_on(evea);
	evea_update_चयन_all(evea);

	वापस 0;

err_out_reset_exiv:
	reset_control_निश्चित(evea->rst_exiv);

err_out_reset:
	reset_control_निश्चित(evea->rst);

err_out_घड़ी_exiv:
	clk_disable_unprepare(evea->clk_exiv);

err_out_घड़ी:
	clk_disable_unprepare(evea->clk);

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_component_driver soc_codec_evea = अणु
	.probe			= evea_codec_probe,
	.suspend		= evea_codec_suspend,
	.resume			= evea_codec_resume,
	.dapm_widमाला_लो		= evea_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(evea_widमाला_लो),
	.dapm_routes		= evea_routes,
	.num_dapm_routes	= ARRAY_SIZE(evea_routes),
	.controls		= evea_controls,
	.num_controls		= ARRAY_SIZE(evea_controls),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver soc_dai_evea[] = अणु
	अणु
		.name     = DRV_NAME "-line1",
		.playback = अणु
			.stream_name  = "Line Out 1",
			.क्रमmats      = EVEA_FORMATS,
			.rates        = EVEA_RATES,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
		.capture = अणु
			.stream_name  = "Line In 1",
			.क्रमmats      = EVEA_FORMATS,
			.rates        = EVEA_RATES,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
	पूर्ण,
	अणु
		.name     = DRV_NAME "-hp1",
		.playback = अणु
			.stream_name  = "Headphone 1",
			.क्रमmats      = EVEA_FORMATS,
			.rates        = EVEA_RATES,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
	पूर्ण,
	अणु
		.name     = DRV_NAME "-lo2",
		.playback = अणु
			.stream_name  = "Line Out 2",
			.क्रमmats      = EVEA_FORMATS,
			.rates        = EVEA_RATES,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config evea_regmap_config = अणु
	.reg_bits      = 32,
	.reg_stride    = 4,
	.val_bits      = 32,
	.max_रेजिस्टर  = 0xffc,
	.cache_type    = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक evea_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा evea_priv *evea;
	व्योम __iomem *preg;
	पूर्णांक ret;

	evea = devm_kzalloc(&pdev->dev, माप(काष्ठा evea_priv), GFP_KERNEL);
	अगर (!evea)
		वापस -ENOMEM;

	evea->clk = devm_clk_get(&pdev->dev, "evea");
	अगर (IS_ERR(evea->clk))
		वापस PTR_ERR(evea->clk);

	evea->clk_exiv = devm_clk_get(&pdev->dev, "exiv");
	अगर (IS_ERR(evea->clk_exiv))
		वापस PTR_ERR(evea->clk_exiv);

	evea->rst = devm_reset_control_get_shared(&pdev->dev, "evea");
	अगर (IS_ERR(evea->rst))
		वापस PTR_ERR(evea->rst);

	evea->rst_exiv = devm_reset_control_get_shared(&pdev->dev, "exiv");
	अगर (IS_ERR(evea->rst_exiv))
		वापस PTR_ERR(evea->rst_exiv);

	preg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(preg))
		वापस PTR_ERR(preg);

	evea->regmap = devm_regmap_init_mmio(&pdev->dev, preg,
					     &evea_regmap_config);
	अगर (IS_ERR(evea->regmap))
		वापस PTR_ERR(evea->regmap);

	ret = clk_prepare_enable(evea->clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(evea->clk_exiv);
	अगर (ret)
		जाओ err_out_घड़ी;

	ret = reset_control_deनिश्चित(evea->rst);
	अगर (ret)
		जाओ err_out_घड़ी_exiv;

	ret = reset_control_deनिश्चित(evea->rst_exiv);
	अगर (ret)
		जाओ err_out_reset;

	/* ADAMV will hangup अगर EXIV reset is निश्चितed */
	evea->rst_adamv = devm_reset_control_get_shared(&pdev->dev, "adamv");
	अगर (IS_ERR(evea->rst_adamv)) अणु
		ret = PTR_ERR(evea->rst_adamv);
		जाओ err_out_reset_exiv;
	पूर्ण

	ret = reset_control_deनिश्चित(evea->rst_adamv);
	अगर (ret)
		जाओ err_out_reset_exiv;

	platक्रमm_set_drvdata(pdev, evea);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &soc_codec_evea,
				     soc_dai_evea, ARRAY_SIZE(soc_dai_evea));
	अगर (ret)
		जाओ err_out_reset_adamv;

	वापस 0;

err_out_reset_adamv:
	reset_control_निश्चित(evea->rst_adamv);

err_out_reset_exiv:
	reset_control_निश्चित(evea->rst_exiv);

err_out_reset:
	reset_control_निश्चित(evea->rst);

err_out_घड़ी_exiv:
	clk_disable_unprepare(evea->clk_exiv);

err_out_घड़ी:
	clk_disable_unprepare(evea->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक evea_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा evea_priv *evea = platक्रमm_get_drvdata(pdev);

	reset_control_निश्चित(evea->rst_adamv);
	reset_control_निश्चित(evea->rst_exiv);
	reset_control_निश्चित(evea->rst);

	clk_disable_unprepare(evea->clk_exiv);
	clk_disable_unprepare(evea->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id evea_of_match[] __maybe_unused = अणु
	अणु .compatible = "socionext,uniphier-evea", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, evea_of_match);

अटल काष्ठा platक्रमm_driver evea_codec_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(evea_of_match),
	पूर्ण,
	.probe  = evea_probe,
	.हटाओ = evea_हटाओ,
पूर्ण;
module_platक्रमm_driver(evea_codec_driver);

MODULE_AUTHOR("Katsuhiro Suzuki <suzuki.katsuhiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier EVEA codec driver");
MODULE_LICENSE("GPL v2");
