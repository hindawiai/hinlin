<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश <dt-bindings/sound/meson-g12a-toacodec.h>
#समावेश "axg-tdm.h"
#समावेश "meson-codec-glue.h"

#घोषणा G12A_TOACODEC_DRV_NAME "g12a-toacodec"

#घोषणा TOACODEC_CTRL0			0x0
#घोषणा  CTRL0_ENABLE_SHIFT		31
#घोषणा  CTRL0_DAT_SEL_SHIFT		14
#घोषणा  CTRL0_DAT_SEL			(0x3 << CTRL0_DAT_SEL_SHIFT)
#घोषणा  CTRL0_LANE_SEL			12
#घोषणा  CTRL0_LRCLK_SEL		GENMASK(9, 8)
#घोषणा  CTRL0_BLK_CAP_INV		BIT(7)
#घोषणा  CTRL0_BCLK_O_INV		BIT(6)
#घोषणा  CTRL0_BCLK_SEL			GENMASK(5, 4)
#घोषणा  CTRL0_MCLK_SEL			GENMASK(2, 0)

#घोषणा TOACODEC_OUT_CHMAX		2

अटल स्थिर अक्षर * स्थिर g12a_toacodec_mux_texts[] = अणु
	"I2S A", "I2S B", "I2S C",
पूर्ण;

अटल पूर्णांक g12a_toacodec_mux_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
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
					      CTRL0_DAT_SEL,
					      FIELD_PREP(CTRL0_DAT_SEL, mux));

	अगर (!changed)
		वापस 0;

	/* Force disconnect of the mux जबतक updating */
	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, 0, शून्य, शून्य);

	snd_soc_component_update_bits(component, e->reg,
				      CTRL0_DAT_SEL |
				      CTRL0_LRCLK_SEL |
				      CTRL0_BCLK_SEL,
				      FIELD_PREP(CTRL0_DAT_SEL, mux) |
				      FIELD_PREP(CTRL0_LRCLK_SEL, mux) |
				      FIELD_PREP(CTRL0_BCLK_SEL, mux));

	/*
	 * FIXME:
	 * On this soc, the glue माला_लो the MCLK directly from the घड़ी
	 * controller instead of going the through the TDM पूर्णांकerface.
	 *
	 * Here we assume पूर्णांकerface A uses घड़ी A, etc ... While it is
	 * true क्रम now, it could be dअगरferent. Instead the glue should
	 * find out the घड़ी used by the पूर्णांकerface and select the same
	 * source. For that, we will need regmap backed घड़ी mux which
	 * is a work in progress
	 */
	snd_soc_component_update_bits(component, e->reg,
				      CTRL0_MCLK_SEL,
				      FIELD_PREP(CTRL0_MCLK_SEL, mux));

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, mux, e, शून्य);

	वापस 0;
पूर्ण

अटल SOC_ENUM_SINGLE_DECL(g12a_toacodec_mux_क्रमागत, TOACODEC_CTRL0,
			    CTRL0_DAT_SEL_SHIFT,
			    g12a_toacodec_mux_texts);

अटल स्थिर काष्ठा snd_kcontrol_new g12a_toacodec_mux =
	SOC_DAPM_ENUM_EXT("Source", g12a_toacodec_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  g12a_toacodec_mux_put_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new g12a_toacodec_out_enable =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", TOACODEC_CTRL0,
				    CTRL0_ENABLE_SHIFT, 1, 0);

अटल स्थिर काष्ठा snd_soc_dapm_widget g12a_toacodec_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("SRC", SND_SOC_NOPM, 0, 0,
			 &g12a_toacodec_mux),
	SND_SOC_DAPM_SWITCH("OUT EN", SND_SOC_NOPM, 0, 0,
			    &g12a_toacodec_out_enable),
पूर्ण;

अटल पूर्णांक g12a_toacodec_input_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *params,
					 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा meson_codec_glue_input *data;
	पूर्णांक ret;

	ret = meson_codec_glue_input_hw_params(substream, params, dai);
	अगर (ret)
		वापस ret;

	/* The glue will provide 1 lane out of the 4 to the output */
	data = meson_codec_glue_input_get_data(dai);
	data->params.channels_min = min_t(अचिन्हित पूर्णांक, TOACODEC_OUT_CHMAX,
					data->params.channels_min);
	data->params.channels_max = min_t(अचिन्हित पूर्णांक, TOACODEC_OUT_CHMAX,
					data->params.channels_max);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops g12a_toacodec_input_ops = अणु
	.hw_params	= g12a_toacodec_input_hw_params,
	.set_fmt	= meson_codec_glue_input_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops g12a_toacodec_output_ops = अणु
	.startup	= meson_codec_glue_output_startup,
पूर्ण;

#घोषणा TOACODEC_STREAM(xname, xsuffix, xchmax)			\
अणु								\
	.stream_name	= xname " " xsuffix,			\
	.channels_min	= 1,					\
	.channels_max	= (xchmax),				\
	.rate_min       = 5512,					\
	.rate_max	= 192000,				\
	.क्रमmats	= AXG_TDM_FORMATS,			\
पूर्ण

#घोषणा TOACODEC_INPUT(xname, xid) अणु					\
	.name = xname,							\
	.id = (xid),							\
	.playback = TOACODEC_STREAM(xname, "Playback", 8),		\
	.ops = &g12a_toacodec_input_ops,				\
	.probe = meson_codec_glue_input_dai_probe,			\
	.हटाओ = meson_codec_glue_input_dai_हटाओ,			\
पूर्ण

#घोषणा TOACODEC_OUTPUT(xname, xid) अणु					\
	.name = xname,							\
	.id = (xid),							\
	.capture = TOACODEC_STREAM(xname, "Capture", TOACODEC_OUT_CHMAX), \
	.ops = &g12a_toacodec_output_ops,				\
पूर्ण

अटल काष्ठा snd_soc_dai_driver g12a_toacodec_dai_drv[] = अणु
	TOACODEC_INPUT("IN A", TOACODEC_IN_A),
	TOACODEC_INPUT("IN B", TOACODEC_IN_B),
	TOACODEC_INPUT("IN C", TOACODEC_IN_C),
	TOACODEC_OUTPUT("OUT", TOACODEC_OUT),
पूर्ण;

अटल पूर्णांक g12a_toacodec_component_probe(काष्ठा snd_soc_component *c)
अणु
	/* Initialize the अटल घड़ी parameters */
	वापस snd_soc_component_ग_लिखो(c, TOACODEC_CTRL0,
				       CTRL0_BLK_CAP_INV);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route g12a_toacodec_routes[] = अणु
	अणु "SRC", "I2S A", "IN A Playback" पूर्ण,
	अणु "SRC", "I2S B", "IN B Playback" पूर्ण,
	अणु "SRC", "I2S C", "IN C Playback" पूर्ण,
	अणु "OUT EN", "Switch", "SRC" पूर्ण,
	अणु "OUT Capture", शून्य, "OUT EN" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new g12a_toacodec_controls[] = अणु
	SOC_SINGLE("Lane Select", TOACODEC_CTRL0, CTRL0_LANE_SEL, 3, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver g12a_toacodec_component_drv = अणु
	.probe			= g12a_toacodec_component_probe,
	.controls		= g12a_toacodec_controls,
	.num_controls		= ARRAY_SIZE(g12a_toacodec_controls),
	.dapm_widमाला_लो		= g12a_toacodec_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(g12a_toacodec_widमाला_लो),
	.dapm_routes		= g12a_toacodec_routes,
	.num_dapm_routes	= ARRAY_SIZE(g12a_toacodec_routes),
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config g12a_toacodec_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id g12a_toacodec_of_match[] = अणु
	अणु .compatible = "amlogic,g12a-toacodec", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, g12a_toacodec_of_match);

अटल पूर्णांक g12a_toacodec_probe(काष्ठा platक्रमm_device *pdev)
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

	map = devm_regmap_init_mmio(dev, regs, &g12a_toacodec_regmap_cfg);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "failed to init regmap: %ld\n",
			PTR_ERR(map));
		वापस PTR_ERR(map);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev,
			&g12a_toacodec_component_drv, g12a_toacodec_dai_drv,
			ARRAY_SIZE(g12a_toacodec_dai_drv));
पूर्ण

अटल काष्ठा platक्रमm_driver g12a_toacodec_pdrv = अणु
	.driver = अणु
		.name = G12A_TOACODEC_DRV_NAME,
		.of_match_table = g12a_toacodec_of_match,
	पूर्ण,
	.probe = g12a_toacodec_probe,
पूर्ण;
module_platक्रमm_driver(g12a_toacodec_pdrv);

MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_DESCRIPTION("Amlogic G12a To Internal DAC Codec Driver");
MODULE_LICENSE("GPL v2");
