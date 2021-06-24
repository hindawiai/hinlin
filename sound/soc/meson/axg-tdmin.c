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

#घोषणा TDMIN_CTRL			0x00
#घोषणा  TDMIN_CTRL_ENABLE		BIT(31)
#घोषणा  TDMIN_CTRL_I2S_MODE		BIT(30)
#घोषणा  TDMIN_CTRL_RST_OUT		BIT(29)
#घोषणा  TDMIN_CTRL_RST_IN		BIT(28)
#घोषणा  TDMIN_CTRL_WS_INV		BIT(25)
#घोषणा  TDMIN_CTRL_SEL_SHIFT		20
#घोषणा  TDMIN_CTRL_IN_BIT_SKEW_MASK	GENMASK(18, 16)
#घोषणा  TDMIN_CTRL_IN_BIT_SKEW(x)	((x) << 16)
#घोषणा  TDMIN_CTRL_LSB_FIRST		BIT(5)
#घोषणा  TDMIN_CTRL_BITNUM_MASK	GENMASK(4, 0)
#घोषणा  TDMIN_CTRL_BITNUM(x)		((x) << 0)
#घोषणा TDMIN_SWAP			0x04
#घोषणा TDMIN_MASK0			0x08
#घोषणा TDMIN_MASK1			0x0c
#घोषणा TDMIN_MASK2			0x10
#घोषणा TDMIN_MASK3			0x14
#घोषणा TDMIN_STAT			0x18
#घोषणा TDMIN_MUTE_VAL			0x1c
#घोषणा TDMIN_MUTE0			0x20
#घोषणा TDMIN_MUTE1			0x24
#घोषणा TDMIN_MUTE2			0x28
#घोषणा TDMIN_MUTE3			0x2c

अटल स्थिर काष्ठा regmap_config axg_tdmin_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= TDMIN_MUTE3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर axg_tdmin_sel_texts[] = अणु
	"IN 0", "IN 1", "IN 2",  "IN 3",  "IN 4",  "IN 5",  "IN 6",  "IN 7",
	"IN 8", "IN 9", "IN 10", "IN 11", "IN 12", "IN 13", "IN 14", "IN 15",
पूर्ण;

/* Change to special mux control to reset dapm */
अटल SOC_ENUM_SINGLE_DECL(axg_tdmin_sel_क्रमागत, TDMIN_CTRL,
			    TDMIN_CTRL_SEL_SHIFT, axg_tdmin_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new axg_tdmin_in_mux =
	SOC_DAPM_ENUM("Input Source", axg_tdmin_sel_क्रमागत);

अटल काष्ठा snd_soc_dai *
axg_tdmin_get_be(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_path *p;
	काष्ठा snd_soc_dai *be;

	snd_soc_dapm_widget_क्रम_each_source_path(w, p) अणु
		अगर (!p->connect)
			जारी;

		अगर (p->source->id == snd_soc_dapm_dai_out)
			वापस (काष्ठा snd_soc_dai *)p->source->priv;

		be = axg_tdmin_get_be(p->source);
		अगर (be)
			वापस be;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा axg_tdm_stream *
axg_tdmin_get_tdm_stream(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dai *be = axg_tdmin_get_be(w);

	अगर (!be)
		वापस शून्य;

	वापस be->capture_dma_data;
पूर्ण

अटल व्योम axg_tdmin_enable(काष्ठा regmap *map)
अणु
	/* Apply both reset */
	regmap_update_bits(map, TDMIN_CTRL,
			   TDMIN_CTRL_RST_OUT | TDMIN_CTRL_RST_IN, 0);

	/* Clear out reset beक्रमe in reset */
	regmap_update_bits(map, TDMIN_CTRL,
			   TDMIN_CTRL_RST_OUT, TDMIN_CTRL_RST_OUT);
	regmap_update_bits(map, TDMIN_CTRL,
			   TDMIN_CTRL_RST_IN,  TDMIN_CTRL_RST_IN);

	/* Actually enable tdmin */
	regmap_update_bits(map, TDMIN_CTRL,
			   TDMIN_CTRL_ENABLE, TDMIN_CTRL_ENABLE);
पूर्ण

अटल व्योम axg_tdmin_disable(काष्ठा regmap *map)
अणु
	regmap_update_bits(map, TDMIN_CTRL, TDMIN_CTRL_ENABLE, 0);
पूर्ण

अटल पूर्णांक axg_tdmin_prepare(काष्ठा regmap *map,
			     स्थिर काष्ठा axg_tdm_क्रमmatter_hw *quirks,
			     काष्ठा axg_tdm_stream *ts)
अणु
	अचिन्हित पूर्णांक val, skew = quirks->skew_offset;

	/* Set stream skew */
	चयन (ts->अगरace->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_DSP_A:
		skew += 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_DSP_B:
		अवरोध;

	शेष:
		pr_err("Unsupported format: %u\n",
		       ts->अगरace->fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	val = TDMIN_CTRL_IN_BIT_SKEW(skew);

	/* Set stream क्रमmat mode */
	चयन (ts->अगरace->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val |= TDMIN_CTRL_I2S_MODE;
		अवरोध;
	पूर्ण

	/* If the sample घड़ी is inverted, invert it back क्रम the क्रमmatter */
	अगर (axg_tdm_lrclk_invert(ts->अगरace->fmt))
		val |= TDMIN_CTRL_WS_INV;

	/* Set the slot width */
	val |= TDMIN_CTRL_BITNUM(ts->अगरace->slot_width - 1);

	/*
	 * The following also reset LSB_FIRST which result in the क्रमmatter
	 * placing the first bit received at bit 31
	 */
	regmap_update_bits(map, TDMIN_CTRL,
			   (TDMIN_CTRL_IN_BIT_SKEW_MASK | TDMIN_CTRL_WS_INV |
			    TDMIN_CTRL_I2S_MODE | TDMIN_CTRL_LSB_FIRST |
			    TDMIN_CTRL_BITNUM_MASK), val);

	/* Set अटल swap mask configuration */
	regmap_ग_लिखो(map, TDMIN_SWAP, 0x76543210);

	वापस axg_tdm_क्रमmatter_set_channel_masks(map, ts, TDMIN_MASK0);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget axg_tdmin_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("IN 0",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 3",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 4",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 5",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 6",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 7",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 8",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 9",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 10", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 11", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 12", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 13", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 14", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 15", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("SRC SEL", SND_SOC_NOPM, 0, 0, &axg_tdmin_in_mux),
	SND_SOC_DAPM_PGA_E("DEC", SND_SOC_NOPM, 0, 0, शून्य, 0,
			   axg_tdm_क्रमmatter_event,
			   (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD)),
	SND_SOC_DAPM_AIF_OUT("OUT", शून्य, 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route axg_tdmin_dapm_routes[] = अणु
	अणु "SRC SEL", "IN 0",  "IN 0" पूर्ण,
	अणु "SRC SEL", "IN 1",  "IN 1" पूर्ण,
	अणु "SRC SEL", "IN 2",  "IN 2" पूर्ण,
	अणु "SRC SEL", "IN 3",  "IN 3" पूर्ण,
	अणु "SRC SEL", "IN 4",  "IN 4" पूर्ण,
	अणु "SRC SEL", "IN 5",  "IN 5" पूर्ण,
	अणु "SRC SEL", "IN 6",  "IN 6" पूर्ण,
	अणु "SRC SEL", "IN 7",  "IN 7" पूर्ण,
	अणु "SRC SEL", "IN 8",  "IN 8" पूर्ण,
	अणु "SRC SEL", "IN 9",  "IN 9" पूर्ण,
	अणु "SRC SEL", "IN 10", "IN 10" पूर्ण,
	अणु "SRC SEL", "IN 11", "IN 11" पूर्ण,
	अणु "SRC SEL", "IN 12", "IN 12" पूर्ण,
	अणु "SRC SEL", "IN 13", "IN 13" पूर्ण,
	अणु "SRC SEL", "IN 14", "IN 14" पूर्ण,
	अणु "SRC SEL", "IN 15", "IN 15" पूर्ण,
	अणु "DEC", शून्य, "SRC SEL" पूर्ण,
	अणु "OUT", शून्य, "DEC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver axg_tdmin_component_drv = अणु
	.dapm_widमाला_लो		= axg_tdmin_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(axg_tdmin_dapm_widमाला_लो),
	.dapm_routes		= axg_tdmin_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(axg_tdmin_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा axg_tdm_क्रमmatter_ops axg_tdmin_ops = अणु
	.get_stream	= axg_tdmin_get_tdm_stream,
	.prepare	= axg_tdmin_prepare,
	.enable		= axg_tdmin_enable,
	.disable	= axg_tdmin_disable,
पूर्ण;

अटल स्थिर काष्ठा axg_tdm_क्रमmatter_driver axg_tdmin_drv = अणु
	.component_drv	= &axg_tdmin_component_drv,
	.regmap_cfg	= &axg_tdmin_regmap_cfg,
	.ops		= &axg_tdmin_ops,
	.quirks		= &(स्थिर काष्ठा axg_tdm_क्रमmatter_hw) अणु
		.skew_offset	= 3,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_tdmin_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-tdmin",
		.data = &axg_tdmin_drv,
	पूर्ण, अणु
		.compatible = "amlogic,g12a-tdmin",
		.data = &axg_tdmin_drv,
	पूर्ण, अणु
		.compatible = "amlogic,sm1-tdmin",
		.data = &axg_tdmin_drv,
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_tdmin_of_match);

अटल काष्ठा platक्रमm_driver axg_tdmin_pdrv = अणु
	.probe = axg_tdm_क्रमmatter_probe,
	.driver = अणु
		.name = "axg-tdmin",
		.of_match_table = axg_tdmin_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_tdmin_pdrv);

MODULE_DESCRIPTION("Amlogic AXG TDM input formatter driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
