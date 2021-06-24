<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "axg-tdm-formatter.h"

#घोषणा TDMOUT_CTRL0			0x00
#घोषणा  TDMOUT_CTRL0_BITNUM_MASK	GENMASK(4, 0)
#घोषणा  TDMOUT_CTRL0_BITNUM(x)		((x) << 0)
#घोषणा  TDMOUT_CTRL0_SLOTNUM_MASK	GENMASK(9, 5)
#घोषणा  TDMOUT_CTRL0_SLOTNUM(x)	((x) << 5)
#घोषणा  TDMOUT_CTRL0_INIT_BITNUM_MASK	GENMASK(19, 15)
#घोषणा  TDMOUT_CTRL0_INIT_BITNUM(x)	((x) << 15)
#घोषणा  TDMOUT_CTRL0_ENABLE		BIT(31)
#घोषणा  TDMOUT_CTRL0_RST_OUT		BIT(29)
#घोषणा  TDMOUT_CTRL0_RST_IN		BIT(28)
#घोषणा TDMOUT_CTRL1			0x04
#घोषणा  TDMOUT_CTRL1_TYPE_MASK		GENMASK(6, 4)
#घोषणा  TDMOUT_CTRL1_TYPE(x)		((x) << 4)
#घोषणा  SM1_TDMOUT_CTRL1_GAIN_EN	7
#घोषणा  TDMOUT_CTRL1_MSB_POS_MASK	GENMASK(12, 8)
#घोषणा  TDMOUT_CTRL1_MSB_POS(x)	((x) << 8)
#घोषणा  TDMOUT_CTRL1_SEL_SHIFT		24
#घोषणा  TDMOUT_CTRL1_GAIN_EN		26
#घोषणा  TDMOUT_CTRL1_WS_INV		BIT(28)
#घोषणा TDMOUT_SWAP			0x08
#घोषणा TDMOUT_MASK0			0x0c
#घोषणा TDMOUT_MASK1			0x10
#घोषणा TDMOUT_MASK2			0x14
#घोषणा TDMOUT_MASK3			0x18
#घोषणा TDMOUT_STAT			0x1c
#घोषणा TDMOUT_GAIN0			0x20
#घोषणा TDMOUT_GAIN1			0x24
#घोषणा TDMOUT_MUTE_VAL			0x28
#घोषणा TDMOUT_MUTE0			0x2c
#घोषणा TDMOUT_MUTE1			0x30
#घोषणा TDMOUT_MUTE2			0x34
#घोषणा TDMOUT_MUTE3			0x38
#घोषणा TDMOUT_MASK_VAL			0x3c

अटल स्थिर काष्ठा regmap_config axg_tdmout_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= TDMOUT_MASK_VAL,
पूर्ण;

अटल काष्ठा snd_soc_dai *
axg_tdmout_get_be(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_path *p;
	काष्ठा snd_soc_dai *be;

	snd_soc_dapm_widget_क्रम_each_sink_path(w, p) अणु
		अगर (!p->connect)
			जारी;

		अगर (p->sink->id == snd_soc_dapm_dai_in)
			वापस (काष्ठा snd_soc_dai *)p->sink->priv;

		be = axg_tdmout_get_be(p->sink);
		अगर (be)
			वापस be;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा axg_tdm_stream *
axg_tdmout_get_tdm_stream(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dai *be = axg_tdmout_get_be(w);

	अगर (!be)
		वापस शून्य;

	वापस be->playback_dma_data;
पूर्ण

अटल व्योम axg_tdmout_enable(काष्ठा regmap *map)
अणु
	/* Apply both reset */
	regmap_update_bits(map, TDMOUT_CTRL0,
			   TDMOUT_CTRL0_RST_OUT | TDMOUT_CTRL0_RST_IN, 0);

	/* Clear out reset beक्रमe in reset */
	regmap_update_bits(map, TDMOUT_CTRL0,
			   TDMOUT_CTRL0_RST_OUT, TDMOUT_CTRL0_RST_OUT);
	regmap_update_bits(map, TDMOUT_CTRL0,
			   TDMOUT_CTRL0_RST_IN,  TDMOUT_CTRL0_RST_IN);

	/* Actually enable tdmout */
	regmap_update_bits(map, TDMOUT_CTRL0,
			   TDMOUT_CTRL0_ENABLE, TDMOUT_CTRL0_ENABLE);
पूर्ण

अटल व्योम axg_tdmout_disable(काष्ठा regmap *map)
अणु
	regmap_update_bits(map, TDMOUT_CTRL0, TDMOUT_CTRL0_ENABLE, 0);
पूर्ण

अटल पूर्णांक axg_tdmout_prepare(काष्ठा regmap *map,
			      स्थिर काष्ठा axg_tdm_क्रमmatter_hw *quirks,
			      काष्ठा axg_tdm_stream *ts)
अणु
	अचिन्हित पूर्णांक val, skew = quirks->skew_offset;

	/* Set the stream skew */
	चयन (ts->अगरace->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_DSP_A:
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_DSP_B:
		skew += 1;
		अवरोध;

	शेष:
		pr_err("Unsupported format: %u\n",
		       ts->अगरace->fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	val = TDMOUT_CTRL0_INIT_BITNUM(skew);

	/* Set the slot width */
	val |= TDMOUT_CTRL0_BITNUM(ts->अगरace->slot_width - 1);

	/* Set the slot number */
	val |= TDMOUT_CTRL0_SLOTNUM(ts->अगरace->slots - 1);

	regmap_update_bits(map, TDMOUT_CTRL0,
			   TDMOUT_CTRL0_INIT_BITNUM_MASK |
			   TDMOUT_CTRL0_BITNUM_MASK |
			   TDMOUT_CTRL0_SLOTNUM_MASK, val);

	/* Set the sample width */
	val = TDMOUT_CTRL1_MSB_POS(ts->width - 1);

	/* FIFO data are arranged in chunks of 64bits */
	चयन (ts->physical_width) अणु
	हाल 8:
		/* 8 samples of 8 bits */
		val |= TDMOUT_CTRL1_TYPE(0);
		अवरोध;
	हाल 16:
		/* 4 samples of 16 bits - right justअगरied */
		val |= TDMOUT_CTRL1_TYPE(2);
		अवरोध;
	हाल 32:
		/* 2 samples of 32 bits - right justअगरied */
		val |= TDMOUT_CTRL1_TYPE(4);
		अवरोध;
	शेष:
		pr_err("Unsupported physical width: %u\n",
		       ts->physical_width);
		वापस -EINVAL;
	पूर्ण

	/* If the sample घड़ी is inverted, invert it back क्रम the क्रमmatter */
	अगर (axg_tdm_lrclk_invert(ts->अगरace->fmt))
		val |= TDMOUT_CTRL1_WS_INV;

	regmap_update_bits(map, TDMOUT_CTRL1,
			   (TDMOUT_CTRL1_TYPE_MASK | TDMOUT_CTRL1_MSB_POS_MASK |
			    TDMOUT_CTRL1_WS_INV), val);

	/* Set अटल swap mask configuration */
	regmap_ग_लिखो(map, TDMOUT_SWAP, 0x76543210);

	वापस axg_tdm_क्रमmatter_set_channel_masks(map, ts, TDMOUT_MASK0);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new axg_tdmout_controls[] = अणु
	SOC_DOUBLE("Lane 0 Volume", TDMOUT_GAIN0,  0,  8, 255, 0),
	SOC_DOUBLE("Lane 1 Volume", TDMOUT_GAIN0, 16, 24, 255, 0),
	SOC_DOUBLE("Lane 2 Volume", TDMOUT_GAIN1,  0,  8, 255, 0),
	SOC_DOUBLE("Lane 3 Volume", TDMOUT_GAIN1, 16, 24, 255, 0),
	SOC_SINGLE("Gain Enable Switch", TDMOUT_CTRL1,
		   TDMOUT_CTRL1_GAIN_EN, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर axg_tdmout_sel_texts[] = अणु
	"IN 0", "IN 1", "IN 2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(axg_tdmout_sel_क्रमागत, TDMOUT_CTRL1,
			    TDMOUT_CTRL1_SEL_SHIFT, axg_tdmout_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new axg_tdmout_in_mux =
	SOC_DAPM_ENUM("Input Source", axg_tdmout_sel_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget axg_tdmout_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("IN 0", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("SRC SEL", SND_SOC_NOPM, 0, 0, &axg_tdmout_in_mux),
	SND_SOC_DAPM_PGA_E("ENC", SND_SOC_NOPM, 0, 0, शून्य, 0,
			   axg_tdm_क्रमmatter_event,
			   (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD)),
	SND_SOC_DAPM_AIF_OUT("OUT", शून्य, 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route axg_tdmout_dapm_routes[] = अणु
	अणु "SRC SEL", "IN 0", "IN 0" पूर्ण,
	अणु "SRC SEL", "IN 1", "IN 1" पूर्ण,
	अणु "SRC SEL", "IN 2", "IN 2" पूर्ण,
	अणु "ENC", शून्य, "SRC SEL" पूर्ण,
	अणु "OUT", शून्य, "ENC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver axg_tdmout_component_drv = अणु
	.controls		= axg_tdmout_controls,
	.num_controls		= ARRAY_SIZE(axg_tdmout_controls),
	.dapm_widमाला_लो		= axg_tdmout_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(axg_tdmout_dapm_widमाला_लो),
	.dapm_routes		= axg_tdmout_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(axg_tdmout_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा axg_tdm_क्रमmatter_ops axg_tdmout_ops = अणु
	.get_stream	= axg_tdmout_get_tdm_stream,
	.prepare	= axg_tdmout_prepare,
	.enable		= axg_tdmout_enable,
	.disable	= axg_tdmout_disable,
पूर्ण;

अटल स्थिर काष्ठा axg_tdm_क्रमmatter_driver axg_tdmout_drv = अणु
	.component_drv	= &axg_tdmout_component_drv,
	.regmap_cfg	= &axg_tdmout_regmap_cfg,
	.ops		= &axg_tdmout_ops,
	.quirks		= &(स्थिर काष्ठा axg_tdm_क्रमmatter_hw) अणु
		.skew_offset = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा axg_tdm_क्रमmatter_driver g12a_tdmout_drv = अणु
	.component_drv	= &axg_tdmout_component_drv,
	.regmap_cfg	= &axg_tdmout_regmap_cfg,
	.ops		= &axg_tdmout_ops,
	.quirks		= &(स्थिर काष्ठा axg_tdm_क्रमmatter_hw) अणु
		.skew_offset = 2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sm1_tdmout_controls[] = अणु
	SOC_DOUBLE("Lane 0 Volume", TDMOUT_GAIN0,  0,  8, 255, 0),
	SOC_DOUBLE("Lane 1 Volume", TDMOUT_GAIN0, 16, 24, 255, 0),
	SOC_DOUBLE("Lane 2 Volume", TDMOUT_GAIN1,  0,  8, 255, 0),
	SOC_DOUBLE("Lane 3 Volume", TDMOUT_GAIN1, 16, 24, 255, 0),
	SOC_SINGLE("Gain Enable Switch", TDMOUT_CTRL1,
		   SM1_TDMOUT_CTRL1_GAIN_EN, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर sm1_tdmout_sel_texts[] = अणु
	"IN 0", "IN 1", "IN 2", "IN 3", "IN 4",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sm1_tdmout_sel_क्रमागत, TDMOUT_CTRL1,
			    TDMOUT_CTRL1_SEL_SHIFT, sm1_tdmout_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new sm1_tdmout_in_mux =
	SOC_DAPM_ENUM("Input Source", sm1_tdmout_sel_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget sm1_tdmout_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("IN 0", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 4", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("SRC SEL", SND_SOC_NOPM, 0, 0, &sm1_tdmout_in_mux),
	SND_SOC_DAPM_PGA_E("ENC", SND_SOC_NOPM, 0, 0, शून्य, 0,
			   axg_tdm_क्रमmatter_event,
			   (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD)),
	SND_SOC_DAPM_AIF_OUT("OUT", शून्य, 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sm1_tdmout_dapm_routes[] = अणु
	अणु "SRC SEL", "IN 0", "IN 0" पूर्ण,
	अणु "SRC SEL", "IN 1", "IN 1" पूर्ण,
	अणु "SRC SEL", "IN 2", "IN 2" पूर्ण,
	अणु "SRC SEL", "IN 3", "IN 3" पूर्ण,
	अणु "SRC SEL", "IN 4", "IN 4" पूर्ण,
	अणु "ENC", शून्य, "SRC SEL" पूर्ण,
	अणु "OUT", शून्य, "ENC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sm1_tdmout_component_drv = अणु
	.controls		= sm1_tdmout_controls,
	.num_controls		= ARRAY_SIZE(sm1_tdmout_controls),
	.dapm_widमाला_लो		= sm1_tdmout_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sm1_tdmout_dapm_widमाला_लो),
	.dapm_routes		= sm1_tdmout_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(sm1_tdmout_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा axg_tdm_क्रमmatter_driver sm1_tdmout_drv = अणु
	.component_drv	= &sm1_tdmout_component_drv,
	.regmap_cfg	= &axg_tdmout_regmap_cfg,
	.ops		= &axg_tdmout_ops,
	.quirks		= &(स्थिर काष्ठा axg_tdm_क्रमmatter_hw) अणु
		.skew_offset = 2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_tdmout_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-tdmout",
		.data = &axg_tdmout_drv,
	पूर्ण, अणु
		.compatible = "amlogic,g12a-tdmout",
		.data = &g12a_tdmout_drv,
	पूर्ण, अणु
		.compatible = "amlogic,sm1-tdmout",
		.data = &sm1_tdmout_drv,
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_tdmout_of_match);

अटल काष्ठा platक्रमm_driver axg_tdmout_pdrv = अणु
	.probe = axg_tdm_क्रमmatter_probe,
	.driver = अणु
		.name = "axg-tdmout",
		.of_match_table = axg_tdmout_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_tdmout_pdrv);

MODULE_DESCRIPTION("Amlogic AXG TDM output formatter driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
