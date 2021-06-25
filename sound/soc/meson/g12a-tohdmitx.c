<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2019 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश <dt-bindings/sound/meson-g12a-tohdmitx.h>
#समावेश "meson-codec-glue.h"

#घोषणा G12A_TOHDMITX_DRV_NAME "g12a-tohdmitx"

#घोषणा TOHDMITX_CTRL0			0x0
#घोषणा  CTRL0_ENABLE_SHIFT		31
#घोषणा  CTRL0_I2S_DAT_SEL_SHIFT	12
#घोषणा  CTRL0_I2S_DAT_SEL		(0x3 << CTRL0_I2S_DAT_SEL_SHIFT)
#घोषणा  CTRL0_I2S_LRCLK_SEL		GENMASK(9, 8)
#घोषणा  CTRL0_I2S_BLK_CAP_INV		BIT(7)
#घोषणा  CTRL0_I2S_BCLK_O_INV		BIT(6)
#घोषणा  CTRL0_I2S_BCLK_SEL		GENMASK(5, 4)
#घोषणा  CTRL0_SPDIF_CLK_CAP_INV	BIT(3)
#घोषणा  CTRL0_SPDIF_CLK_O_INV		BIT(2)
#घोषणा  CTRL0_SPDIF_SEL_SHIFT		1
#घोषणा  CTRL0_SPDIF_SEL		(0x1 << CTRL0_SPDIF_SEL_SHIFT)
#घोषणा  CTRL0_SPDIF_CLK_SEL		BIT(0)

अटल स्थिर अक्षर * स्थिर g12a_tohdmitx_i2s_mux_texts[] = अणु
	"I2S A", "I2S B", "I2S C",
पूर्ण;

अटल पूर्णांक g12a_tohdmitx_i2s_mux_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक mux, changed;

	mux = snd_soc_क्रमागत_item_to_val(e, ucontrol->value.क्रमागतerated.item[0]);
	changed = snd_soc_component_test_bits(component, e->reg,
					      CTRL0_I2S_DAT_SEL,
					      FIELD_PREP(CTRL0_I2S_DAT_SEL,
							 mux));

	अगर (!changed)
		वापस 0;

	/* Force disconnect of the mux जबतक updating */
	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, 0, शून्य, शून्य);

	snd_soc_component_update_bits(component, e->reg,
				      CTRL0_I2S_DAT_SEL |
				      CTRL0_I2S_LRCLK_SEL |
				      CTRL0_I2S_BCLK_SEL,
				      FIELD_PREP(CTRL0_I2S_DAT_SEL, mux) |
				      FIELD_PREP(CTRL0_I2S_LRCLK_SEL, mux) |
				      FIELD_PREP(CTRL0_I2S_BCLK_SEL, mux));

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, mux, e, शून्य);

	वापस 0;
पूर्ण

अटल SOC_ENUM_SINGLE_DECL(g12a_tohdmitx_i2s_mux_क्रमागत, TOHDMITX_CTRL0,
			    CTRL0_I2S_DAT_SEL_SHIFT,
			    g12a_tohdmitx_i2s_mux_texts);

अटल स्थिर काष्ठा snd_kcontrol_new g12a_tohdmitx_i2s_mux =
	SOC_DAPM_ENUM_EXT("I2S Source", g12a_tohdmitx_i2s_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  g12a_tohdmitx_i2s_mux_put_क्रमागत);

अटल स्थिर अक्षर * स्थिर g12a_tohdmitx_spdअगर_mux_texts[] = अणु
	"SPDIF A", "SPDIF B",
पूर्ण;

अटल पूर्णांक g12a_tohdmitx_spdअगर_mux_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक mux, changed;

	mux = snd_soc_क्रमागत_item_to_val(e, ucontrol->value.क्रमागतerated.item[0]);
	changed = snd_soc_component_test_bits(component, TOHDMITX_CTRL0,
					      CTRL0_SPDIF_SEL,
					      FIELD_PREP(CTRL0_SPDIF_SEL, mux));

	अगर (!changed)
		वापस 0;

	/* Force disconnect of the mux जबतक updating */
	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, 0, शून्य, शून्य);

	snd_soc_component_update_bits(component, TOHDMITX_CTRL0,
				      CTRL0_SPDIF_SEL |
				      CTRL0_SPDIF_CLK_SEL,
				      FIELD_PREP(CTRL0_SPDIF_SEL, mux) |
				      FIELD_PREP(CTRL0_SPDIF_CLK_SEL, mux));

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, mux, e, शून्य);

	वापस 0;
पूर्ण

अटल SOC_ENUM_SINGLE_DECL(g12a_tohdmitx_spdअगर_mux_क्रमागत, TOHDMITX_CTRL0,
			    CTRL0_SPDIF_SEL_SHIFT,
			    g12a_tohdmitx_spdअगर_mux_texts);

अटल स्थिर काष्ठा snd_kcontrol_new g12a_tohdmitx_spdअगर_mux =
	SOC_DAPM_ENUM_EXT("SPDIF Source", g12a_tohdmitx_spdअगर_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  g12a_tohdmitx_spdअगर_mux_put_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new g12a_tohdmitx_out_enable =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", TOHDMITX_CTRL0,
				    CTRL0_ENABLE_SHIFT, 1, 0);

अटल स्थिर काष्ठा snd_soc_dapm_widget g12a_tohdmitx_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("I2S SRC", SND_SOC_NOPM, 0, 0,
			 &g12a_tohdmitx_i2s_mux),
	SND_SOC_DAPM_SWITCH("I2S OUT EN", SND_SOC_NOPM, 0, 0,
			    &g12a_tohdmitx_out_enable),
	SND_SOC_DAPM_MUX("SPDIF SRC", SND_SOC_NOPM, 0, 0,
			 &g12a_tohdmitx_spdअगर_mux),
	SND_SOC_DAPM_SWITCH("SPDIF OUT EN", SND_SOC_NOPM, 0, 0,
			    &g12a_tohdmitx_out_enable),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops g12a_tohdmitx_input_ops = अणु
	.hw_params	= meson_codec_glue_input_hw_params,
	.set_fmt	= meson_codec_glue_input_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops g12a_tohdmitx_output_ops = अणु
	.startup	= meson_codec_glue_output_startup,
पूर्ण;

#घोषणा TOHDMITX_SPDIF_FORMATS					\
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |	\
	 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_LE)

#घोषणा TOHDMITX_I2S_FORMATS					\
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |	\
	 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_LE |	\
	 SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा TOHDMITX_STREAM(xname, xsuffix, xfmt, xchmax)		\
अणु								\
	.stream_name	= xname " " xsuffix,			\
	.channels_min	= 1,					\
	.channels_max	= (xchmax),				\
	.rate_min       = 8000,					\
	.rate_max	= 192000,				\
	.क्रमmats	= (xfmt),				\
पूर्ण

#घोषणा TOHDMITX_IN(xname, xid, xfmt, xchmax) अणु				\
	.name = xname,							\
	.id = (xid),							\
	.playback = TOHDMITX_STREAM(xname, "Playback", xfmt, xchmax),	\
	.ops = &g12a_tohdmitx_input_ops,				\
	.probe = meson_codec_glue_input_dai_probe,			\
	.हटाओ = meson_codec_glue_input_dai_हटाओ,			\
पूर्ण

#घोषणा TOHDMITX_OUT(xname, xid, xfmt, xchmax) अणु			\
	.name = xname,							\
	.id = (xid),							\
	.capture = TOHDMITX_STREAM(xname, "Capture", xfmt, xchmax),	\
	.ops = &g12a_tohdmitx_output_ops,				\
पूर्ण

अटल काष्ठा snd_soc_dai_driver g12a_tohdmitx_dai_drv[] = अणु
	TOHDMITX_IN("I2S IN A", TOHDMITX_I2S_IN_A,
		    TOHDMITX_I2S_FORMATS, 8),
	TOHDMITX_IN("I2S IN B", TOHDMITX_I2S_IN_B,
		    TOHDMITX_I2S_FORMATS, 8),
	TOHDMITX_IN("I2S IN C", TOHDMITX_I2S_IN_C,
		    TOHDMITX_I2S_FORMATS, 8),
	TOHDMITX_OUT("I2S OUT", TOHDMITX_I2S_OUT,
		     TOHDMITX_I2S_FORMATS, 8),
	TOHDMITX_IN("SPDIF IN A", TOHDMITX_SPDIF_IN_A,
		    TOHDMITX_SPDIF_FORMATS, 2),
	TOHDMITX_IN("SPDIF IN B", TOHDMITX_SPDIF_IN_B,
		    TOHDMITX_SPDIF_FORMATS, 2),
	TOHDMITX_OUT("SPDIF OUT", TOHDMITX_SPDIF_OUT,
		     TOHDMITX_SPDIF_FORMATS, 2),
पूर्ण;

अटल पूर्णांक g12a_tohdmi_component_probe(काष्ठा snd_soc_component *c)
अणु
	/* Initialize the अटल घड़ी parameters */
	वापस snd_soc_component_ग_लिखो(c, TOHDMITX_CTRL0,
		     CTRL0_I2S_BLK_CAP_INV | CTRL0_SPDIF_CLK_CAP_INV);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route g12a_tohdmitx_routes[] = अणु
	अणु "I2S SRC", "I2S A", "I2S IN A Playback" पूर्ण,
	अणु "I2S SRC", "I2S B", "I2S IN B Playback" पूर्ण,
	अणु "I2S SRC", "I2S C", "I2S IN C Playback" पूर्ण,
	अणु "I2S OUT EN", "Switch", "I2S SRC" पूर्ण,
	अणु "I2S OUT Capture", शून्य, "I2S OUT EN" पूर्ण,
	अणु "SPDIF SRC", "SPDIF A", "SPDIF IN A Playback" पूर्ण,
	अणु "SPDIF SRC", "SPDIF B", "SPDIF IN B Playback" पूर्ण,
	अणु "SPDIF OUT EN", "Switch", "SPDIF SRC" पूर्ण,
	अणु "SPDIF OUT Capture", शून्य, "SPDIF OUT EN" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver g12a_tohdmitx_component_drv = अणु
	.probe			= g12a_tohdmi_component_probe,
	.dapm_widमाला_लो		= g12a_tohdmitx_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(g12a_tohdmitx_widमाला_लो),
	.dapm_routes		= g12a_tohdmitx_routes,
	.num_dapm_routes	= ARRAY_SIZE(g12a_tohdmitx_routes),
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config g12a_tohdmitx_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id g12a_tohdmitx_of_match[] = अणु
	अणु .compatible = "amlogic,g12a-tohdmitx", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, g12a_tohdmitx_of_match);

अटल पूर्णांक g12a_tohdmitx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *regs;
	काष्ठा regmap *map;
	पूर्णांक ret;

	ret = device_reset(dev);
	अगर (ret)
		वापस ret;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	map = devm_regmap_init_mmio(dev, regs, &g12a_tohdmitx_regmap_cfg);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "failed to init regmap: %ld\n",
			PTR_ERR(map));
		वापस PTR_ERR(map);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev,
			&g12a_tohdmitx_component_drv, g12a_tohdmitx_dai_drv,
			ARRAY_SIZE(g12a_tohdmitx_dai_drv));
पूर्ण

अटल काष्ठा platक्रमm_driver g12a_tohdmitx_pdrv = अणु
	.driver = अणु
		.name = G12A_TOHDMITX_DRV_NAME,
		.of_match_table = g12a_tohdmitx_of_match,
	पूर्ण,
	.probe = g12a_tohdmitx_probe,
पूर्ण;
module_platक्रमm_driver(g12a_tohdmitx_pdrv);

MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_DESCRIPTION("Amlogic G12a To HDMI Tx Control Codec Driver");
MODULE_LICENSE("GPL v2");
