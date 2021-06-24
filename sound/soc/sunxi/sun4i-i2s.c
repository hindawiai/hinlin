<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Andrea Venturi
 * Andrea Venturi <be17068@iperbole.bo.it>
 *
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#घोषणा SUN4I_I2S_CTRL_REG		0x00
#घोषणा SUN4I_I2S_CTRL_SDO_EN_MASK		GENMASK(11, 8)
#घोषणा SUN4I_I2S_CTRL_SDO_EN(sकरो)			BIT(8 + (sकरो))
#घोषणा SUN4I_I2S_CTRL_MODE_MASK		BIT(5)
#घोषणा SUN4I_I2S_CTRL_MODE_SLAVE			(1 << 5)
#घोषणा SUN4I_I2S_CTRL_MODE_MASTER			(0 << 5)
#घोषणा SUN4I_I2S_CTRL_TX_EN			BIT(2)
#घोषणा SUN4I_I2S_CTRL_RX_EN			BIT(1)
#घोषणा SUN4I_I2S_CTRL_GL_EN			BIT(0)

#घोषणा SUN4I_I2S_FMT0_REG		0x04
#घोषणा SUN4I_I2S_FMT0_LRCLK_POLARITY_MASK	BIT(7)
#घोषणा SUN4I_I2S_FMT0_LRCLK_POLARITY_INVERTED		(1 << 7)
#घोषणा SUN4I_I2S_FMT0_LRCLK_POLARITY_NORMAL		(0 << 7)
#घोषणा SUN4I_I2S_FMT0_BCLK_POLARITY_MASK	BIT(6)
#घोषणा SUN4I_I2S_FMT0_BCLK_POLARITY_INVERTED		(1 << 6)
#घोषणा SUN4I_I2S_FMT0_BCLK_POLARITY_NORMAL		(0 << 6)
#घोषणा SUN4I_I2S_FMT0_SR_MASK			GENMASK(5, 4)
#घोषणा SUN4I_I2S_FMT0_SR(sr)				((sr) << 4)
#घोषणा SUN4I_I2S_FMT0_WSS_MASK			GENMASK(3, 2)
#घोषणा SUN4I_I2S_FMT0_WSS(wss)				((wss) << 2)
#घोषणा SUN4I_I2S_FMT0_FMT_MASK			GENMASK(1, 0)
#घोषणा SUN4I_I2S_FMT0_FMT_RIGHT_J			(2 << 0)
#घोषणा SUN4I_I2S_FMT0_FMT_LEFT_J			(1 << 0)
#घोषणा SUN4I_I2S_FMT0_FMT_I2S				(0 << 0)

#घोषणा SUN4I_I2S_FMT1_REG		0x08
#घोषणा SUN4I_I2S_FMT1_REG_SEXT_MASK		BIT(8)
#घोषणा SUN4I_I2S_FMT1_REG_SEXT(sext)			((sext) << 8)

#घोषणा SUN4I_I2S_FIFO_TX_REG		0x0c
#घोषणा SUN4I_I2S_FIFO_RX_REG		0x10

#घोषणा SUN4I_I2S_FIFO_CTRL_REG		0x14
#घोषणा SUN4I_I2S_FIFO_CTRL_FLUSH_TX		BIT(25)
#घोषणा SUN4I_I2S_FIFO_CTRL_FLUSH_RX		BIT(24)
#घोषणा SUN4I_I2S_FIFO_CTRL_TX_MODE_MASK	BIT(2)
#घोषणा SUN4I_I2S_FIFO_CTRL_TX_MODE(mode)		((mode) << 2)
#घोषणा SUN4I_I2S_FIFO_CTRL_RX_MODE_MASK	GENMASK(1, 0)
#घोषणा SUN4I_I2S_FIFO_CTRL_RX_MODE(mode)		(mode)

#घोषणा SUN4I_I2S_FIFO_STA_REG		0x18

#घोषणा SUN4I_I2S_DMA_INT_CTRL_REG	0x1c
#घोषणा SUN4I_I2S_DMA_INT_CTRL_TX_DRQ_EN	BIT(7)
#घोषणा SUN4I_I2S_DMA_INT_CTRL_RX_DRQ_EN	BIT(3)

#घोषणा SUN4I_I2S_INT_STA_REG		0x20

#घोषणा SUN4I_I2S_CLK_DIV_REG		0x24
#घोषणा SUN4I_I2S_CLK_DIV_MCLK_EN		BIT(7)
#घोषणा SUN4I_I2S_CLK_DIV_BCLK_MASK		GENMASK(6, 4)
#घोषणा SUN4I_I2S_CLK_DIV_BCLK(bclk)			((bclk) << 4)
#घोषणा SUN4I_I2S_CLK_DIV_MCLK_MASK		GENMASK(3, 0)
#घोषणा SUN4I_I2S_CLK_DIV_MCLK(mclk)			((mclk) << 0)

#घोषणा SUN4I_I2S_TX_CNT_REG		0x28
#घोषणा SUN4I_I2S_RX_CNT_REG		0x2c

#घोषणा SUN4I_I2S_TX_CHAN_SEL_REG	0x30
#घोषणा SUN4I_I2S_CHAN_SEL_MASK			GENMASK(2, 0)
#घोषणा SUN4I_I2S_CHAN_SEL(num_chan)		(((num_chan) - 1) << 0)

#घोषणा SUN4I_I2S_TX_CHAN_MAP_REG	0x34
#घोषणा SUN4I_I2S_TX_CHAN_MAP(chan, sample)	((sample) << (chan << 2))

#घोषणा SUN4I_I2S_RX_CHAN_SEL_REG	0x38
#घोषणा SUN4I_I2S_RX_CHAN_MAP_REG	0x3c

/* Defines required क्रम sun8i-h3 support */
#घोषणा SUN8I_I2S_CTRL_BCLK_OUT			BIT(18)
#घोषणा SUN8I_I2S_CTRL_LRCK_OUT			BIT(17)

#घोषणा SUN8I_I2S_CTRL_MODE_MASK		GENMASK(5, 4)
#घोषणा SUN8I_I2S_CTRL_MODE_RIGHT		(2 << 4)
#घोषणा SUN8I_I2S_CTRL_MODE_LEFT		(1 << 4)
#घोषणा SUN8I_I2S_CTRL_MODE_PCM			(0 << 4)

#घोषणा SUN8I_I2S_FMT0_LRCLK_POLARITY_MASK	BIT(19)
#घोषणा SUN8I_I2S_FMT0_LRCLK_POLARITY_INVERTED		(1 << 19)
#घोषणा SUN8I_I2S_FMT0_LRCLK_POLARITY_NORMAL		(0 << 19)
#घोषणा SUN8I_I2S_FMT0_LRCK_PERIOD_MASK		GENMASK(17, 8)
#घोषणा SUN8I_I2S_FMT0_LRCK_PERIOD(period)	((period - 1) << 8)
#घोषणा SUN8I_I2S_FMT0_BCLK_POLARITY_MASK	BIT(7)
#घोषणा SUN8I_I2S_FMT0_BCLK_POLARITY_INVERTED		(1 << 7)
#घोषणा SUN8I_I2S_FMT0_BCLK_POLARITY_NORMAL		(0 << 7)

#घोषणा SUN8I_I2S_FMT1_REG_SEXT_MASK		GENMASK(5, 4)
#घोषणा SUN8I_I2S_FMT1_REG_SEXT(sext)			((sext) << 4)

#घोषणा SUN8I_I2S_INT_STA_REG		0x0c
#घोषणा SUN8I_I2S_FIFO_TX_REG		0x20

#घोषणा SUN8I_I2S_CHAN_CFG_REG		0x30
#घोषणा SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM_MASK	GENMASK(6, 4)
#घोषणा SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM(chan)	((chan - 1) << 4)
#घोषणा SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM_MASK	GENMASK(2, 0)
#घोषणा SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM(chan)	(chan - 1)

#घोषणा SUN8I_I2S_TX_CHAN_MAP_REG	0x44
#घोषणा SUN8I_I2S_TX_CHAN_SEL_REG	0x34
#घोषणा SUN8I_I2S_TX_CHAN_OFFSET_MASK		GENMASK(13, 12)
#घोषणा SUN8I_I2S_TX_CHAN_OFFSET(offset)	(offset << 12)
#घोषणा SUN8I_I2S_TX_CHAN_EN_MASK		GENMASK(11, 4)
#घोषणा SUN8I_I2S_TX_CHAN_EN(num_chan)		(((1 << num_chan) - 1) << 4)

#घोषणा SUN8I_I2S_RX_CHAN_SEL_REG	0x54
#घोषणा SUN8I_I2S_RX_CHAN_MAP_REG	0x58

/* Defines required क्रम sun50i-h6 support */
#घोषणा SUN50I_H6_I2S_TX_CHAN_SEL_OFFSET_MASK	GENMASK(21, 20)
#घोषणा SUN50I_H6_I2S_TX_CHAN_SEL_OFFSET(offset)	((offset) << 20)
#घोषणा SUN50I_H6_I2S_TX_CHAN_SEL_MASK		GENMASK(19, 16)
#घोषणा SUN50I_H6_I2S_TX_CHAN_SEL(chan)		((chan - 1) << 16)
#घोषणा SUN50I_H6_I2S_TX_CHAN_EN_MASK		GENMASK(15, 0)
#घोषणा SUN50I_H6_I2S_TX_CHAN_EN(num_chan)	(((1 << num_chan) - 1))

#घोषणा SUN50I_H6_I2S_TX_CHAN_MAP0_REG	0x44
#घोषणा SUN50I_H6_I2S_TX_CHAN_MAP1_REG	0x48

#घोषणा SUN50I_H6_I2S_RX_CHAN_SEL_REG	0x64
#घोषणा SUN50I_H6_I2S_RX_CHAN_MAP0_REG	0x68
#घोषणा SUN50I_H6_I2S_RX_CHAN_MAP1_REG	0x6C

काष्ठा sun4i_i2s;

/**
 * काष्ठा sun4i_i2s_quirks - Dअगरferences between SoC variants.
 * @has_reset: SoC needs reset deनिश्चितed.
 * @reg_offset_txdata: offset of the tx fअगरo.
 * @sun4i_i2s_regmap: regmap config to use.
 * @field_clkभाग_mclk_en: regmap field to enable mclk output.
 * @field_fmt_wss: regmap field to set word select size.
 * @field_fmt_sr: regmap field to set sample resolution.
 * @bclk_भागiders: bit घड़ी भागiders array
 * @num_bclk_भागiders: number of bit घड़ी भागiders
 * @mclk_भागiders: mclk भागiders array
 * @num_mclk_भागiders: number of mclk भागiders
 * @get_bclk_parent_rate: callback to get bclk parent rate
 * @get_sr: callback to get sample resolution
 * @get_wss: callback to get word select size
 * @set_chan_cfg: callback to set channel configuration
 * @set_fmt: callback to set क्रमmat
 */
काष्ठा sun4i_i2s_quirks अणु
	bool				has_reset;
	अचिन्हित पूर्णांक			reg_offset_txdata;	/* TX FIFO */
	स्थिर काष्ठा regmap_config	*sun4i_i2s_regmap;

	/* Register fields क्रम i2s */
	काष्ठा reg_field		field_clkभाग_mclk_en;
	काष्ठा reg_field		field_fmt_wss;
	काष्ठा reg_field		field_fmt_sr;

	स्थिर काष्ठा sun4i_i2s_clk_भाग	*bclk_भागiders;
	अचिन्हित पूर्णांक			num_bclk_भागiders;
	स्थिर काष्ठा sun4i_i2s_clk_भाग	*mclk_भागiders;
	अचिन्हित पूर्णांक			num_mclk_भागiders;

	अचिन्हित दीर्घ (*get_bclk_parent_rate)(स्थिर काष्ठा sun4i_i2s *i2s);
	पूर्णांक	(*get_sr)(अचिन्हित पूर्णांक width);
	पूर्णांक	(*get_wss)(अचिन्हित पूर्णांक width);

	/*
	 * In the set_chan_cfg() function poपूर्णांकer:
	 * @slots: channels per frame + padding slots, regardless of क्रमmat
	 * @slot_width: bits per sample + padding bits, regardless of क्रमmat
	 */
	पूर्णांक	(*set_chan_cfg)(स्थिर काष्ठा sun4i_i2s *i2s,
				अचिन्हित पूर्णांक channels,	अचिन्हित पूर्णांक slots,
				अचिन्हित पूर्णांक slot_width);
	पूर्णांक	(*set_fmt)(स्थिर काष्ठा sun4i_i2s *i2s, अचिन्हित पूर्णांक fmt);
पूर्ण;

काष्ठा sun4i_i2s अणु
	काष्ठा clk	*bus_clk;
	काष्ठा clk	*mod_clk;
	काष्ठा regmap	*regmap;
	काष्ठा reset_control *rst;

	अचिन्हित पूर्णांक	क्रमmat;
	अचिन्हित पूर्णांक	mclk_freq;
	अचिन्हित पूर्णांक	slots;
	अचिन्हित पूर्णांक	slot_width;

	काष्ठा snd_dmaengine_dai_dma_data	capture_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data	playback_dma_data;

	/* Register fields क्रम i2s */
	काष्ठा regmap_field	*field_clkभाग_mclk_en;
	काष्ठा regmap_field	*field_fmt_wss;
	काष्ठा regmap_field	*field_fmt_sr;

	स्थिर काष्ठा sun4i_i2s_quirks	*variant;
पूर्ण;

काष्ठा sun4i_i2s_clk_भाग अणु
	u8	भाग;
	u8	val;
पूर्ण;

अटल स्थिर काष्ठा sun4i_i2s_clk_भाग sun4i_i2s_bclk_भाग[] = अणु
	अणु .भाग = 2, .val = 0 पूर्ण,
	अणु .भाग = 4, .val = 1 पूर्ण,
	अणु .भाग = 6, .val = 2 पूर्ण,
	अणु .भाग = 8, .val = 3 पूर्ण,
	अणु .भाग = 12, .val = 4 पूर्ण,
	अणु .भाग = 16, .val = 5 पूर्ण,
	/* TODO - extend भागide ratio supported by newer SoCs */
पूर्ण;

अटल स्थिर काष्ठा sun4i_i2s_clk_भाग sun4i_i2s_mclk_भाग[] = अणु
	अणु .भाग = 1, .val = 0 पूर्ण,
	अणु .भाग = 2, .val = 1 पूर्ण,
	अणु .भाग = 4, .val = 2 पूर्ण,
	अणु .भाग = 6, .val = 3 पूर्ण,
	अणु .भाग = 8, .val = 4 पूर्ण,
	अणु .भाग = 12, .val = 5 पूर्ण,
	अणु .भाग = 16, .val = 6 पूर्ण,
	अणु .भाग = 24, .val = 7 पूर्ण,
	/* TODO - extend भागide ratio supported by newer SoCs */
पूर्ण;

अटल स्थिर काष्ठा sun4i_i2s_clk_भाग sun8i_i2s_clk_भाग[] = अणु
	अणु .भाग = 1, .val = 1 पूर्ण,
	अणु .भाग = 2, .val = 2 पूर्ण,
	अणु .भाग = 4, .val = 3 पूर्ण,
	अणु .भाग = 6, .val = 4 पूर्ण,
	अणु .भाग = 8, .val = 5 पूर्ण,
	अणु .भाग = 12, .val = 6 पूर्ण,
	अणु .भाग = 16, .val = 7 पूर्ण,
	अणु .भाग = 24, .val = 8 पूर्ण,
	अणु .भाग = 32, .val = 9 पूर्ण,
	अणु .भाग = 48, .val = 10 पूर्ण,
	अणु .भाग = 64, .val = 11 पूर्ण,
	अणु .भाग = 96, .val = 12 पूर्ण,
	अणु .भाग = 128, .val = 13 पूर्ण,
	अणु .भाग = 176, .val = 14 पूर्ण,
	अणु .भाग = 192, .val = 15 पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ sun4i_i2s_get_bclk_parent_rate(स्थिर काष्ठा sun4i_i2s *i2s)
अणु
	वापस i2s->mclk_freq;
पूर्ण

अटल अचिन्हित दीर्घ sun8i_i2s_get_bclk_parent_rate(स्थिर काष्ठा sun4i_i2s *i2s)
अणु
	वापस clk_get_rate(i2s->mod_clk);
पूर्ण

अटल पूर्णांक sun4i_i2s_get_bclk_भाग(काष्ठा sun4i_i2s *i2s,
				  अचिन्हित दीर्घ parent_rate,
				  अचिन्हित पूर्णांक sampling_rate,
				  अचिन्हित पूर्णांक channels,
				  अचिन्हित पूर्णांक word_size)
अणु
	स्थिर काष्ठा sun4i_i2s_clk_भाग *भागiders = i2s->variant->bclk_भागiders;
	पूर्णांक भाग = parent_rate / sampling_rate / word_size / channels;
	पूर्णांक i;

	क्रम (i = 0; i < i2s->variant->num_bclk_भागiders; i++) अणु
		स्थिर काष्ठा sun4i_i2s_clk_भाग *bभाग = &भागiders[i];

		अगर (bभाग->भाग == भाग)
			वापस bभाग->val;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sun4i_i2s_get_mclk_भाग(काष्ठा sun4i_i2s *i2s,
				  अचिन्हित दीर्घ parent_rate,
				  अचिन्हित दीर्घ mclk_rate)
अणु
	स्थिर काष्ठा sun4i_i2s_clk_भाग *भागiders = i2s->variant->mclk_भागiders;
	पूर्णांक भाग = parent_rate / mclk_rate;
	पूर्णांक i;

	क्रम (i = 0; i < i2s->variant->num_mclk_भागiders; i++) अणु
		स्थिर काष्ठा sun4i_i2s_clk_भाग *mभाग = &भागiders[i];

		अगर (mभाग->भाग == भाग)
			वापस mभाग->val;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sun4i_i2s_oversample_rates[] = अणु 128, 192, 256, 384, 512, 768 पूर्ण;
अटल bool sun4i_i2s_oversample_is_valid(अचिन्हित पूर्णांक oversample)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sun4i_i2s_oversample_rates); i++)
		अगर (sun4i_i2s_oversample_rates[i] == oversample)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक sun4i_i2s_set_clk_rate(काष्ठा snd_soc_dai *dai,
				  अचिन्हित पूर्णांक rate,
				  अचिन्हित पूर्णांक slots,
				  अचिन्हित पूर्णांक slot_width)
अणु
	काष्ठा sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक oversample_rate, clk_rate, bclk_parent_rate;
	पूर्णांक bclk_भाग, mclk_भाग;
	पूर्णांक ret;

	चयन (rate) अणु
	हाल 176400:
	हाल 88200:
	हाल 44100:
	हाल 22050:
	हाल 11025:
		clk_rate = 22579200;
		अवरोध;

	हाल 192000:
	हाल 128000:
	हाल 96000:
	हाल 64000:
	हाल 48000:
	हाल 32000:
	हाल 24000:
	हाल 16000:
	हाल 12000:
	हाल 8000:
		clk_rate = 24576000;
		अवरोध;

	शेष:
		dev_err(dai->dev, "Unsupported sample rate: %u\n", rate);
		वापस -EINVAL;
	पूर्ण

	ret = clk_set_rate(i2s->mod_clk, clk_rate);
	अगर (ret)
		वापस ret;

	oversample_rate = i2s->mclk_freq / rate;
	अगर (!sun4i_i2s_oversample_is_valid(oversample_rate)) अणु
		dev_err(dai->dev, "Unsupported oversample rate: %d\n",
			oversample_rate);
		वापस -EINVAL;
	पूर्ण

	bclk_parent_rate = i2s->variant->get_bclk_parent_rate(i2s);
	bclk_भाग = sun4i_i2s_get_bclk_भाग(i2s, bclk_parent_rate,
					  rate, slots, slot_width);
	अगर (bclk_भाग < 0) अणु
		dev_err(dai->dev, "Unsupported BCLK divider: %d\n", bclk_भाग);
		वापस -EINVAL;
	पूर्ण

	mclk_भाग = sun4i_i2s_get_mclk_भाग(i2s, clk_rate, i2s->mclk_freq);
	अगर (mclk_भाग < 0) अणु
		dev_err(dai->dev, "Unsupported MCLK divider: %d\n", mclk_भाग);
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(i2s->regmap, SUN4I_I2S_CLK_DIV_REG,
		     SUN4I_I2S_CLK_DIV_BCLK(bclk_भाग) |
		     SUN4I_I2S_CLK_DIV_MCLK(mclk_भाग));

	regmap_field_ग_लिखो(i2s->field_clkभाग_mclk_en, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_i2s_get_sr(अचिन्हित पूर्णांक width)
अणु
	चयन (width) अणु
	हाल 16:
		वापस 0;
	हाल 20:
		वापस 1;
	हाल 24:
		वापस 2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sun4i_i2s_get_wss(अचिन्हित पूर्णांक width)
अणु
	चयन (width) अणु
	हाल 16:
		वापस 0;
	हाल 20:
		वापस 1;
	हाल 24:
		वापस 2;
	हाल 32:
		वापस 3;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sun8i_i2s_get_sr_wss(अचिन्हित पूर्णांक width)
अणु
	चयन (width) अणु
	हाल 8:
		वापस 1;
	हाल 12:
		वापस 2;
	हाल 16:
		वापस 3;
	हाल 20:
		वापस 4;
	हाल 24:
		वापस 5;
	हाल 28:
		वापस 6;
	हाल 32:
		वापस 7;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sun4i_i2s_set_chan_cfg(स्थिर काष्ठा sun4i_i2s *i2s,
				  अचिन्हित पूर्णांक channels, अचिन्हित पूर्णांक slots,
				  अचिन्हित पूर्णांक slot_width)
अणु
	/* Map the channels क्रम playback and capture */
	regmap_ग_लिखो(i2s->regmap, SUN4I_I2S_TX_CHAN_MAP_REG, 0x76543210);
	regmap_ग_लिखो(i2s->regmap, SUN4I_I2S_RX_CHAN_MAP_REG, 0x00003210);

	/* Configure the channels */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_TX_CHAN_SEL_REG,
			   SUN4I_I2S_CHAN_SEL_MASK,
			   SUN4I_I2S_CHAN_SEL(channels));
	regmap_update_bits(i2s->regmap, SUN4I_I2S_RX_CHAN_SEL_REG,
			   SUN4I_I2S_CHAN_SEL_MASK,
			   SUN4I_I2S_CHAN_SEL(channels));

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_i2s_set_chan_cfg(स्थिर काष्ठा sun4i_i2s *i2s,
				  अचिन्हित पूर्णांक channels, अचिन्हित पूर्णांक slots,
				  अचिन्हित पूर्णांक slot_width)
अणु
	अचिन्हित पूर्णांक lrck_period;

	/* Map the channels क्रम playback and capture */
	regmap_ग_लिखो(i2s->regmap, SUN8I_I2S_TX_CHAN_MAP_REG, 0x76543210);
	regmap_ग_लिखो(i2s->regmap, SUN8I_I2S_RX_CHAN_MAP_REG, 0x76543210);

	/* Configure the channels */
	regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
			   SUN4I_I2S_CHAN_SEL_MASK,
			   SUN4I_I2S_CHAN_SEL(channels));
	regmap_update_bits(i2s->regmap, SUN8I_I2S_RX_CHAN_SEL_REG,
			   SUN4I_I2S_CHAN_SEL_MASK,
			   SUN4I_I2S_CHAN_SEL(channels));

	regmap_update_bits(i2s->regmap, SUN8I_I2S_CHAN_CFG_REG,
			   SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM_MASK,
			   SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM(channels));
	regmap_update_bits(i2s->regmap, SUN8I_I2S_CHAN_CFG_REG,
			   SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM_MASK,
			   SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM(channels));

	चयन (i2s->क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		lrck_period = slot_width * slots;
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_I2S:
		lrck_period = slot_width;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN8I_I2S_FMT0_LRCK_PERIOD_MASK,
			   SUN8I_I2S_FMT0_LRCK_PERIOD(lrck_period));

	regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
			   SUN8I_I2S_TX_CHAN_EN_MASK,
			   SUN8I_I2S_TX_CHAN_EN(channels));

	वापस 0;
पूर्ण

अटल पूर्णांक sun50i_h6_i2s_set_chan_cfg(स्थिर काष्ठा sun4i_i2s *i2s,
				      अचिन्हित पूर्णांक channels, अचिन्हित पूर्णांक slots,
				      अचिन्हित पूर्णांक slot_width)
अणु
	अचिन्हित पूर्णांक lrck_period;

	/* Map the channels क्रम playback and capture */
	regmap_ग_लिखो(i2s->regmap, SUN50I_H6_I2S_TX_CHAN_MAP0_REG, 0xFEDCBA98);
	regmap_ग_लिखो(i2s->regmap, SUN50I_H6_I2S_TX_CHAN_MAP1_REG, 0x76543210);
	regmap_ग_लिखो(i2s->regmap, SUN50I_H6_I2S_RX_CHAN_MAP0_REG, 0xFEDCBA98);
	regmap_ग_लिखो(i2s->regmap, SUN50I_H6_I2S_RX_CHAN_MAP1_REG, 0x76543210);

	/* Configure the channels */
	regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
			   SUN50I_H6_I2S_TX_CHAN_SEL_MASK,
			   SUN50I_H6_I2S_TX_CHAN_SEL(channels));
	regmap_update_bits(i2s->regmap, SUN50I_H6_I2S_RX_CHAN_SEL_REG,
			   SUN50I_H6_I2S_TX_CHAN_SEL_MASK,
			   SUN50I_H6_I2S_TX_CHAN_SEL(channels));

	regmap_update_bits(i2s->regmap, SUN8I_I2S_CHAN_CFG_REG,
			   SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM_MASK,
			   SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM(channels));
	regmap_update_bits(i2s->regmap, SUN8I_I2S_CHAN_CFG_REG,
			   SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM_MASK,
			   SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM(channels));

	चयन (i2s->क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		lrck_period = slot_width * slots;
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_I2S:
		lrck_period = slot_width;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN8I_I2S_FMT0_LRCK_PERIOD_MASK,
			   SUN8I_I2S_FMT0_LRCK_PERIOD(lrck_period));

	regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
			   SUN50I_H6_I2S_TX_CHAN_EN_MASK,
			   SUN50I_H6_I2S_TX_CHAN_EN(channels));

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक word_size = params_width(params);
	अचिन्हित पूर्णांक slot_width = params_physical_width(params);
	अचिन्हित पूर्णांक channels = params_channels(params);

	अचिन्हित पूर्णांक slots = channels;

	पूर्णांक ret, sr, wss;
	u32 width;

	अगर (i2s->slots)
		slots = i2s->slots;

	अगर (i2s->slot_width)
		slot_width = i2s->slot_width;

	ret = i2s->variant->set_chan_cfg(i2s, channels, slots, slot_width);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Invalid channel configuration\n");
		वापस ret;
	पूर्ण

	/* Set signअगरicant bits in our FIFOs */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_FIFO_CTRL_REG,
			   SUN4I_I2S_FIFO_CTRL_TX_MODE_MASK |
			   SUN4I_I2S_FIFO_CTRL_RX_MODE_MASK,
			   SUN4I_I2S_FIFO_CTRL_TX_MODE(1) |
			   SUN4I_I2S_FIFO_CTRL_RX_MODE(1));

	चयन (params_physical_width(params)) अणु
	हाल 16:
		width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		अवरोध;
	हाल 32:
		width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unsupported physical sample width: %d\n",
			params_physical_width(params));
		वापस -EINVAL;
	पूर्ण
	i2s->playback_dma_data.addr_width = width;

	sr = i2s->variant->get_sr(word_size);
	अगर (sr < 0)
		वापस -EINVAL;

	wss = i2s->variant->get_wss(slot_width);
	अगर (wss < 0)
		वापस -EINVAL;

	regmap_field_ग_लिखो(i2s->field_fmt_wss, wss);
	regmap_field_ग_लिखो(i2s->field_fmt_sr, sr);

	वापस sun4i_i2s_set_clk_rate(dai, params_rate(params),
				      slots, slot_width);
पूर्ण

अटल पूर्णांक sun4i_i2s_set_soc_fmt(स्थिर काष्ठा sun4i_i2s *i2s,
				 अचिन्हित पूर्णांक fmt)
अणु
	u32 val;

	/* DAI घड़ी polarity */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_IF:
		/* Invert both घड़ीs */
		val = SUN4I_I2S_FMT0_BCLK_POLARITY_INVERTED |
		      SUN4I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		/* Invert bit घड़ी */
		val = SUN4I_I2S_FMT0_BCLK_POLARITY_INVERTED;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		/* Invert frame घड़ी */
		val = SUN4I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN4I_I2S_FMT0_LRCLK_POLARITY_MASK |
			   SUN4I_I2S_FMT0_BCLK_POLARITY_MASK,
			   val);

	/* DAI Mode */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		val = SUN4I_I2S_FMT0_FMT_I2S;
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		val = SUN4I_I2S_FMT0_FMT_LEFT_J;
		अवरोध;

	हाल SND_SOC_DAIFMT_RIGHT_J:
		val = SUN4I_I2S_FMT0_FMT_RIGHT_J;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN4I_I2S_FMT0_FMT_MASK, val);

	/* DAI घड़ी master masks */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* BCLK and LRCLK master */
		val = SUN4I_I2S_CTRL_MODE_MASTER;
		अवरोध;

	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* BCLK and LRCLK slave */
		val = SUN4I_I2S_CTRL_MODE_SLAVE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_MODE_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_i2s_set_soc_fmt(स्थिर काष्ठा sun4i_i2s *i2s,
				 अचिन्हित पूर्णांक fmt)
अणु
	u32 mode, val;
	u8 offset;

	/*
	 * DAI घड़ी polarity
	 *
	 * The setup क्रम LRCK contradicts the datasheet, but under a
	 * scope it's clear that the LRCK polarity is reversed
	 * compared to the expected polarity on the bus.
	 */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_IF:
		/* Invert both घड़ीs */
		val = SUN8I_I2S_FMT0_BCLK_POLARITY_INVERTED;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		/* Invert bit घड़ी */
		val = SUN8I_I2S_FMT0_BCLK_POLARITY_INVERTED |
		      SUN8I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		/* Invert frame घड़ी */
		val = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		val = SUN8I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN8I_I2S_FMT0_LRCLK_POLARITY_MASK |
			   SUN8I_I2S_FMT0_BCLK_POLARITY_MASK,
			   val);

	/* DAI Mode */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		mode = SUN8I_I2S_CTRL_MODE_PCM;
		offset = 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B:
		mode = SUN8I_I2S_CTRL_MODE_PCM;
		offset = 0;
		अवरोध;

	हाल SND_SOC_DAIFMT_I2S:
		mode = SUN8I_I2S_CTRL_MODE_LEFT;
		offset = 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		mode = SUN8I_I2S_CTRL_MODE_LEFT;
		offset = 0;
		अवरोध;

	हाल SND_SOC_DAIFMT_RIGHT_J:
		mode = SUN8I_I2S_CTRL_MODE_RIGHT;
		offset = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN8I_I2S_CTRL_MODE_MASK, mode);
	regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
			   SUN8I_I2S_TX_CHAN_OFFSET_MASK,
			   SUN8I_I2S_TX_CHAN_OFFSET(offset));
	regmap_update_bits(i2s->regmap, SUN8I_I2S_RX_CHAN_SEL_REG,
			   SUN8I_I2S_TX_CHAN_OFFSET_MASK,
			   SUN8I_I2S_TX_CHAN_OFFSET(offset));

	/* DAI घड़ी master masks */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* BCLK and LRCLK master */
		val = SUN8I_I2S_CTRL_BCLK_OUT |	SUN8I_I2S_CTRL_LRCK_OUT;
		अवरोध;

	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* BCLK and LRCLK slave */
		val = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN8I_I2S_CTRL_BCLK_OUT | SUN8I_I2S_CTRL_LRCK_OUT,
			   val);

	/* Set sign extension to pad out LSB with 0 */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT1_REG,
			   SUN8I_I2S_FMT1_REG_SEXT_MASK,
			   SUN8I_I2S_FMT1_REG_SEXT(0));

	वापस 0;
पूर्ण

अटल पूर्णांक sun50i_h6_i2s_set_soc_fmt(स्थिर काष्ठा sun4i_i2s *i2s,
				     अचिन्हित पूर्णांक fmt)
अणु
	u32 mode, val;
	u8 offset;

	/*
	 * DAI घड़ी polarity
	 *
	 * The setup क्रम LRCK contradicts the datasheet, but under a
	 * scope it's clear that the LRCK polarity is reversed
	 * compared to the expected polarity on the bus.
	 */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_IF:
		/* Invert both घड़ीs */
		val = SUN8I_I2S_FMT0_BCLK_POLARITY_INVERTED;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		/* Invert bit घड़ी */
		val = SUN8I_I2S_FMT0_BCLK_POLARITY_INVERTED |
		      SUN8I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		/* Invert frame घड़ी */
		val = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		val = SUN8I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN8I_I2S_FMT0_LRCLK_POLARITY_MASK |
			   SUN8I_I2S_FMT0_BCLK_POLARITY_MASK,
			   val);

	/* DAI Mode */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		mode = SUN8I_I2S_CTRL_MODE_PCM;
		offset = 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B:
		mode = SUN8I_I2S_CTRL_MODE_PCM;
		offset = 0;
		अवरोध;

	हाल SND_SOC_DAIFMT_I2S:
		mode = SUN8I_I2S_CTRL_MODE_LEFT;
		offset = 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		mode = SUN8I_I2S_CTRL_MODE_LEFT;
		offset = 0;
		अवरोध;

	हाल SND_SOC_DAIFMT_RIGHT_J:
		mode = SUN8I_I2S_CTRL_MODE_RIGHT;
		offset = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN8I_I2S_CTRL_MODE_MASK, mode);
	regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
			   SUN50I_H6_I2S_TX_CHAN_SEL_OFFSET_MASK,
			   SUN50I_H6_I2S_TX_CHAN_SEL_OFFSET(offset));
	regmap_update_bits(i2s->regmap, SUN50I_H6_I2S_RX_CHAN_SEL_REG,
			   SUN50I_H6_I2S_TX_CHAN_SEL_OFFSET_MASK,
			   SUN50I_H6_I2S_TX_CHAN_SEL_OFFSET(offset));

	/* DAI घड़ी master masks */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* BCLK and LRCLK master */
		val = SUN8I_I2S_CTRL_BCLK_OUT |	SUN8I_I2S_CTRL_LRCK_OUT;
		अवरोध;

	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* BCLK and LRCLK slave */
		val = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN8I_I2S_CTRL_BCLK_OUT | SUN8I_I2S_CTRL_LRCK_OUT,
			   val);

	/* Set sign extension to pad out LSB with 0 */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT1_REG,
			   SUN8I_I2S_FMT1_REG_SEXT_MASK,
			   SUN8I_I2S_FMT1_REG_SEXT(0));

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_i2s_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = i2s->variant->set_fmt(i2s, fmt);
	अगर (ret) अणु
		dev_err(dai->dev, "Unsupported format configuration\n");
		वापस ret;
	पूर्ण

	i2s->क्रमmat = fmt;

	वापस 0;
पूर्ण

अटल व्योम sun4i_i2s_start_capture(काष्ठा sun4i_i2s *i2s)
अणु
	/* Flush RX FIFO */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_FIFO_CTRL_REG,
			   SUN4I_I2S_FIFO_CTRL_FLUSH_RX,
			   SUN4I_I2S_FIFO_CTRL_FLUSH_RX);

	/* Clear RX counter */
	regmap_ग_लिखो(i2s->regmap, SUN4I_I2S_RX_CNT_REG, 0);

	/* Enable RX Block */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_RX_EN,
			   SUN4I_I2S_CTRL_RX_EN);

	/* Enable RX DRQ */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_DMA_INT_CTRL_REG,
			   SUN4I_I2S_DMA_INT_CTRL_RX_DRQ_EN,
			   SUN4I_I2S_DMA_INT_CTRL_RX_DRQ_EN);
पूर्ण

अटल व्योम sun4i_i2s_start_playback(काष्ठा sun4i_i2s *i2s)
अणु
	/* Flush TX FIFO */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_FIFO_CTRL_REG,
			   SUN4I_I2S_FIFO_CTRL_FLUSH_TX,
			   SUN4I_I2S_FIFO_CTRL_FLUSH_TX);

	/* Clear TX counter */
	regmap_ग_लिखो(i2s->regmap, SUN4I_I2S_TX_CNT_REG, 0);

	/* Enable TX Block */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_TX_EN,
			   SUN4I_I2S_CTRL_TX_EN);

	/* Enable TX DRQ */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_DMA_INT_CTRL_REG,
			   SUN4I_I2S_DMA_INT_CTRL_TX_DRQ_EN,
			   SUN4I_I2S_DMA_INT_CTRL_TX_DRQ_EN);
पूर्ण

अटल व्योम sun4i_i2s_stop_capture(काष्ठा sun4i_i2s *i2s)
अणु
	/* Disable RX Block */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_RX_EN,
			   0);

	/* Disable RX DRQ */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_DMA_INT_CTRL_REG,
			   SUN4I_I2S_DMA_INT_CTRL_RX_DRQ_EN,
			   0);
पूर्ण

अटल व्योम sun4i_i2s_stop_playback(काष्ठा sun4i_i2s *i2s)
अणु
	/* Disable TX Block */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_TX_EN,
			   0);

	/* Disable TX DRQ */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_DMA_INT_CTRL_REG,
			   SUN4I_I2S_DMA_INT_CTRL_TX_DRQ_EN,
			   0);
पूर्ण

अटल पूर्णांक sun4i_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			sun4i_i2s_start_playback(i2s);
		अन्यथा
			sun4i_i2s_start_capture(i2s);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			sun4i_i2s_stop_playback(i2s);
		अन्यथा
			sun4i_i2s_stop_capture(i2s);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_i2s_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	अगर (clk_id != 0)
		वापस -EINVAL;

	i2s->mclk_freq = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_i2s_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				  अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				  पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	अगर (slots > 8)
		वापस -EINVAL;

	i2s->slots = slots;
	i2s->slot_width = slot_width;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sun4i_i2s_dai_ops = अणु
	.hw_params	= sun4i_i2s_hw_params,
	.set_fmt	= sun4i_i2s_set_fmt,
	.set_sysclk	= sun4i_i2s_set_sysclk,
	.set_tdm_slot	= sun4i_i2s_set_tdm_slot,
	.trigger	= sun4i_i2s_trigger,
पूर्ण;

अटल पूर्णांक sun4i_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai,
				  &i2s->playback_dma_data,
				  &i2s->capture_dma_data);

	वापस 0;
पूर्ण

#घोषणा SUN4I_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
			 SNDRV_PCM_FMTBIT_S20_LE | \
			 SNDRV_PCM_FMTBIT_S24_LE)

अटल काष्ठा snd_soc_dai_driver sun4i_i2s_dai = अणु
	.probe = sun4i_i2s_dai_probe,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SUN4I_FORMATS,
	पूर्ण,
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SUN4I_FORMATS,
	पूर्ण,
	.ops = &sun4i_i2s_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sun4i_i2s_component = अणु
	.name	= "sun4i-dai",
पूर्ण;

अटल bool sun4i_i2s_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SUN4I_I2S_FIFO_TX_REG:
		वापस false;

	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool sun4i_i2s_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SUN4I_I2S_FIFO_RX_REG:
	हाल SUN4I_I2S_FIFO_STA_REG:
		वापस false;

	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool sun4i_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SUN4I_I2S_FIFO_RX_REG:
	हाल SUN4I_I2S_INT_STA_REG:
	हाल SUN4I_I2S_RX_CNT_REG:
	हाल SUN4I_I2S_TX_CNT_REG:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sun8i_i2s_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SUN8I_I2S_FIFO_TX_REG:
		वापस false;

	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool sun8i_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SUN4I_I2S_FIFO_CTRL_REG:
	हाल SUN4I_I2S_FIFO_RX_REG:
	हाल SUN4I_I2S_FIFO_STA_REG:
	हाल SUN4I_I2S_RX_CNT_REG:
	हाल SUN4I_I2S_TX_CNT_REG:
	हाल SUN8I_I2S_FIFO_TX_REG:
	हाल SUN8I_I2S_INT_STA_REG:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष sun4i_i2s_reg_शेषs[] = अणु
	अणु SUN4I_I2S_CTRL_REG, 0x00000000 पूर्ण,
	अणु SUN4I_I2S_FMT0_REG, 0x0000000c पूर्ण,
	अणु SUN4I_I2S_FMT1_REG, 0x00004020 पूर्ण,
	अणु SUN4I_I2S_FIFO_CTRL_REG, 0x000400f0 पूर्ण,
	अणु SUN4I_I2S_DMA_INT_CTRL_REG, 0x00000000 पूर्ण,
	अणु SUN4I_I2S_CLK_DIV_REG, 0x00000000 पूर्ण,
	अणु SUN4I_I2S_TX_CHAN_SEL_REG, 0x00000001 पूर्ण,
	अणु SUN4I_I2S_TX_CHAN_MAP_REG, 0x76543210 पूर्ण,
	अणु SUN4I_I2S_RX_CHAN_SEL_REG, 0x00000001 पूर्ण,
	अणु SUN4I_I2S_RX_CHAN_MAP_REG, 0x00003210 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष sun8i_i2s_reg_शेषs[] = अणु
	अणु SUN4I_I2S_CTRL_REG, 0x00060000 पूर्ण,
	अणु SUN4I_I2S_FMT0_REG, 0x00000033 पूर्ण,
	अणु SUN4I_I2S_FMT1_REG, 0x00000030 पूर्ण,
	अणु SUN4I_I2S_FIFO_CTRL_REG, 0x000400f0 पूर्ण,
	अणु SUN4I_I2S_DMA_INT_CTRL_REG, 0x00000000 पूर्ण,
	अणु SUN4I_I2S_CLK_DIV_REG, 0x00000000 पूर्ण,
	अणु SUN8I_I2S_CHAN_CFG_REG, 0x00000000 पूर्ण,
	अणु SUN8I_I2S_TX_CHAN_SEL_REG, 0x00000000 पूर्ण,
	अणु SUN8I_I2S_TX_CHAN_MAP_REG, 0x00000000 पूर्ण,
	अणु SUN8I_I2S_RX_CHAN_SEL_REG, 0x00000000 पूर्ण,
	अणु SUN8I_I2S_RX_CHAN_MAP_REG, 0x00000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष sun50i_h6_i2s_reg_शेषs[] = अणु
	अणु SUN4I_I2S_CTRL_REG, 0x00060000 पूर्ण,
	अणु SUN4I_I2S_FMT0_REG, 0x00000033 पूर्ण,
	अणु SUN4I_I2S_FMT1_REG, 0x00000030 पूर्ण,
	अणु SUN4I_I2S_FIFO_CTRL_REG, 0x000400f0 पूर्ण,
	अणु SUN4I_I2S_DMA_INT_CTRL_REG, 0x00000000 पूर्ण,
	अणु SUN4I_I2S_CLK_DIV_REG, 0x00000000 पूर्ण,
	अणु SUN8I_I2S_CHAN_CFG_REG, 0x00000000 पूर्ण,
	अणु SUN8I_I2S_TX_CHAN_SEL_REG, 0x00000000 पूर्ण,
	अणु SUN50I_H6_I2S_TX_CHAN_MAP0_REG, 0x00000000 पूर्ण,
	अणु SUN50I_H6_I2S_TX_CHAN_MAP1_REG, 0x00000000 पूर्ण,
	अणु SUN50I_H6_I2S_RX_CHAN_SEL_REG, 0x00000000 पूर्ण,
	अणु SUN50I_H6_I2S_RX_CHAN_MAP0_REG, 0x00000000 पूर्ण,
	अणु SUN50I_H6_I2S_RX_CHAN_MAP1_REG, 0x00000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun4i_i2s_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN4I_I2S_RX_CHAN_MAP_REG,

	.cache_type	= REGCACHE_FLAT,
	.reg_शेषs	= sun4i_i2s_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(sun4i_i2s_reg_शेषs),
	.ग_लिखोable_reg	= sun4i_i2s_wr_reg,
	.पढ़ोable_reg	= sun4i_i2s_rd_reg,
	.अस्थिर_reg	= sun4i_i2s_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun8i_i2s_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN8I_I2S_RX_CHAN_MAP_REG,
	.cache_type	= REGCACHE_FLAT,
	.reg_शेषs	= sun8i_i2s_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(sun8i_i2s_reg_शेषs),
	.ग_लिखोable_reg	= sun4i_i2s_wr_reg,
	.पढ़ोable_reg	= sun8i_i2s_rd_reg,
	.अस्थिर_reg	= sun8i_i2s_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun50i_h6_i2s_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN50I_H6_I2S_RX_CHAN_MAP1_REG,
	.cache_type	= REGCACHE_FLAT,
	.reg_शेषs	= sun50i_h6_i2s_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(sun50i_h6_i2s_reg_शेषs),
	.ग_लिखोable_reg	= sun4i_i2s_wr_reg,
	.पढ़ोable_reg	= sun8i_i2s_rd_reg,
	.अस्थिर_reg	= sun8i_i2s_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक sun4i_i2s_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sun4i_i2s *i2s = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(i2s->bus_clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable bus clock\n");
		वापस ret;
	पूर्ण

	regcache_cache_only(i2s->regmap, false);
	regcache_mark_dirty(i2s->regmap);

	ret = regcache_sync(i2s->regmap);
	अगर (ret) अणु
		dev_err(dev, "Failed to sync regmap cache\n");
		जाओ err_disable_clk;
	पूर्ण

	/* Enable the whole hardware block */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_GL_EN, SUN4I_I2S_CTRL_GL_EN);

	/* Enable the first output line */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_SDO_EN_MASK,
			   SUN4I_I2S_CTRL_SDO_EN(0));

	ret = clk_prepare_enable(i2s->mod_clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable module clock\n");
		जाओ err_disable_clk;
	पूर्ण

	वापस 0;

err_disable_clk:
	clk_disable_unprepare(i2s->bus_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_i2s_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun4i_i2s *i2s = dev_get_drvdata(dev);

	clk_disable_unprepare(i2s->mod_clk);

	/* Disable our output lines */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_SDO_EN_MASK, 0);

	/* Disable the whole hardware block */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_GL_EN, 0);

	regcache_cache_only(i2s->regmap, true);

	clk_disable_unprepare(i2s->bus_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun4i_i2s_quirks sun4i_a10_i2s_quirks = अणु
	.has_reset		= false,
	.reg_offset_txdata	= SUN4I_I2S_FIFO_TX_REG,
	.sun4i_i2s_regmap	= &sun4i_i2s_regmap_config,
	.field_clkभाग_mclk_en	= REG_FIELD(SUN4I_I2S_CLK_DIV_REG, 7, 7),
	.field_fmt_wss		= REG_FIELD(SUN4I_I2S_FMT0_REG, 2, 3),
	.field_fmt_sr		= REG_FIELD(SUN4I_I2S_FMT0_REG, 4, 5),
	.bclk_भागiders		= sun4i_i2s_bclk_भाग,
	.num_bclk_भागiders	= ARRAY_SIZE(sun4i_i2s_bclk_भाग),
	.mclk_भागiders		= sun4i_i2s_mclk_भाग,
	.num_mclk_भागiders	= ARRAY_SIZE(sun4i_i2s_mclk_भाग),
	.get_bclk_parent_rate	= sun4i_i2s_get_bclk_parent_rate,
	.get_sr			= sun4i_i2s_get_sr,
	.get_wss		= sun4i_i2s_get_wss,
	.set_chan_cfg		= sun4i_i2s_set_chan_cfg,
	.set_fmt		= sun4i_i2s_set_soc_fmt,
पूर्ण;

अटल स्थिर काष्ठा sun4i_i2s_quirks sun6i_a31_i2s_quirks = अणु
	.has_reset		= true,
	.reg_offset_txdata	= SUN4I_I2S_FIFO_TX_REG,
	.sun4i_i2s_regmap	= &sun4i_i2s_regmap_config,
	.field_clkभाग_mclk_en	= REG_FIELD(SUN4I_I2S_CLK_DIV_REG, 7, 7),
	.field_fmt_wss		= REG_FIELD(SUN4I_I2S_FMT0_REG, 2, 3),
	.field_fmt_sr		= REG_FIELD(SUN4I_I2S_FMT0_REG, 4, 5),
	.bclk_भागiders		= sun4i_i2s_bclk_भाग,
	.num_bclk_भागiders	= ARRAY_SIZE(sun4i_i2s_bclk_भाग),
	.mclk_भागiders		= sun4i_i2s_mclk_भाग,
	.num_mclk_भागiders	= ARRAY_SIZE(sun4i_i2s_mclk_भाग),
	.get_bclk_parent_rate	= sun4i_i2s_get_bclk_parent_rate,
	.get_sr			= sun4i_i2s_get_sr,
	.get_wss		= sun4i_i2s_get_wss,
	.set_chan_cfg		= sun4i_i2s_set_chan_cfg,
	.set_fmt		= sun4i_i2s_set_soc_fmt,
पूर्ण;

/*
 * This करोesn't describe the TDM controller करोcumented in the A83t
 * datasheet, but the three unकरोcumented I2S controller that use the
 * older design.
 */
अटल स्थिर काष्ठा sun4i_i2s_quirks sun8i_a83t_i2s_quirks = अणु
	.has_reset		= true,
	.reg_offset_txdata	= SUN8I_I2S_FIFO_TX_REG,
	.sun4i_i2s_regmap	= &sun4i_i2s_regmap_config,
	.field_clkभाग_mclk_en	= REG_FIELD(SUN4I_I2S_CLK_DIV_REG, 7, 7),
	.field_fmt_wss		= REG_FIELD(SUN4I_I2S_FMT0_REG, 2, 3),
	.field_fmt_sr		= REG_FIELD(SUN4I_I2S_FMT0_REG, 4, 5),
	.bclk_भागiders		= sun4i_i2s_bclk_भाग,
	.num_bclk_भागiders	= ARRAY_SIZE(sun4i_i2s_bclk_भाग),
	.mclk_भागiders		= sun4i_i2s_mclk_भाग,
	.num_mclk_भागiders	= ARRAY_SIZE(sun4i_i2s_mclk_भाग),
	.get_bclk_parent_rate	= sun4i_i2s_get_bclk_parent_rate,
	.get_sr			= sun4i_i2s_get_sr,
	.get_wss		= sun4i_i2s_get_wss,
	.set_chan_cfg		= sun4i_i2s_set_chan_cfg,
	.set_fmt		= sun4i_i2s_set_soc_fmt,
पूर्ण;

अटल स्थिर काष्ठा sun4i_i2s_quirks sun8i_h3_i2s_quirks = अणु
	.has_reset		= true,
	.reg_offset_txdata	= SUN8I_I2S_FIFO_TX_REG,
	.sun4i_i2s_regmap	= &sun8i_i2s_regmap_config,
	.field_clkभाग_mclk_en	= REG_FIELD(SUN4I_I2S_CLK_DIV_REG, 8, 8),
	.field_fmt_wss		= REG_FIELD(SUN4I_I2S_FMT0_REG, 0, 2),
	.field_fmt_sr		= REG_FIELD(SUN4I_I2S_FMT0_REG, 4, 6),
	.bclk_भागiders		= sun8i_i2s_clk_भाग,
	.num_bclk_भागiders	= ARRAY_SIZE(sun8i_i2s_clk_भाग),
	.mclk_भागiders		= sun8i_i2s_clk_भाग,
	.num_mclk_भागiders	= ARRAY_SIZE(sun8i_i2s_clk_भाग),
	.get_bclk_parent_rate	= sun8i_i2s_get_bclk_parent_rate,
	.get_sr			= sun8i_i2s_get_sr_wss,
	.get_wss		= sun8i_i2s_get_sr_wss,
	.set_chan_cfg		= sun8i_i2s_set_chan_cfg,
	.set_fmt		= sun8i_i2s_set_soc_fmt,
पूर्ण;

अटल स्थिर काष्ठा sun4i_i2s_quirks sun50i_a64_codec_i2s_quirks = अणु
	.has_reset		= true,
	.reg_offset_txdata	= SUN8I_I2S_FIFO_TX_REG,
	.sun4i_i2s_regmap	= &sun4i_i2s_regmap_config,
	.field_clkभाग_mclk_en	= REG_FIELD(SUN4I_I2S_CLK_DIV_REG, 7, 7),
	.field_fmt_wss		= REG_FIELD(SUN4I_I2S_FMT0_REG, 2, 3),
	.field_fmt_sr		= REG_FIELD(SUN4I_I2S_FMT0_REG, 4, 5),
	.bclk_भागiders		= sun4i_i2s_bclk_भाग,
	.num_bclk_भागiders	= ARRAY_SIZE(sun4i_i2s_bclk_भाग),
	.mclk_भागiders		= sun4i_i2s_mclk_भाग,
	.num_mclk_भागiders	= ARRAY_SIZE(sun4i_i2s_mclk_भाग),
	.get_bclk_parent_rate	= sun4i_i2s_get_bclk_parent_rate,
	.get_sr			= sun4i_i2s_get_sr,
	.get_wss		= sun4i_i2s_get_wss,
	.set_chan_cfg		= sun4i_i2s_set_chan_cfg,
	.set_fmt		= sun4i_i2s_set_soc_fmt,
पूर्ण;

अटल स्थिर काष्ठा sun4i_i2s_quirks sun50i_h6_i2s_quirks = अणु
	.has_reset		= true,
	.reg_offset_txdata	= SUN8I_I2S_FIFO_TX_REG,
	.sun4i_i2s_regmap	= &sun50i_h6_i2s_regmap_config,
	.field_clkभाग_mclk_en	= REG_FIELD(SUN4I_I2S_CLK_DIV_REG, 8, 8),
	.field_fmt_wss		= REG_FIELD(SUN4I_I2S_FMT0_REG, 0, 2),
	.field_fmt_sr		= REG_FIELD(SUN4I_I2S_FMT0_REG, 4, 6),
	.bclk_भागiders		= sun8i_i2s_clk_भाग,
	.num_bclk_भागiders	= ARRAY_SIZE(sun8i_i2s_clk_भाग),
	.mclk_भागiders		= sun8i_i2s_clk_भाग,
	.num_mclk_भागiders	= ARRAY_SIZE(sun8i_i2s_clk_भाग),
	.get_bclk_parent_rate	= sun8i_i2s_get_bclk_parent_rate,
	.get_sr			= sun8i_i2s_get_sr_wss,
	.get_wss		= sun8i_i2s_get_sr_wss,
	.set_chan_cfg		= sun50i_h6_i2s_set_chan_cfg,
	.set_fmt		= sun50i_h6_i2s_set_soc_fmt,
पूर्ण;

अटल पूर्णांक sun4i_i2s_init_regmap_fields(काष्ठा device *dev,
					काष्ठा sun4i_i2s *i2s)
अणु
	i2s->field_clkभाग_mclk_en =
		devm_regmap_field_alloc(dev, i2s->regmap,
					i2s->variant->field_clkभाग_mclk_en);
	अगर (IS_ERR(i2s->field_clkभाग_mclk_en))
		वापस PTR_ERR(i2s->field_clkभाग_mclk_en);

	i2s->field_fmt_wss =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_fmt_wss);
	अगर (IS_ERR(i2s->field_fmt_wss))
		वापस PTR_ERR(i2s->field_fmt_wss);

	i2s->field_fmt_sr =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_fmt_sr);
	अगर (IS_ERR(i2s->field_fmt_sr))
		वापस PTR_ERR(i2s->field_fmt_sr);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_i2s *i2s;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक irq, ret;

	i2s = devm_kzalloc(&pdev->dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, i2s);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	i2s->variant = of_device_get_match_data(&pdev->dev);
	अगर (!i2s->variant) अणु
		dev_err(&pdev->dev, "Failed to determine the quirks to use\n");
		वापस -ENODEV;
	पूर्ण

	i2s->bus_clk = devm_clk_get(&pdev->dev, "apb");
	अगर (IS_ERR(i2s->bus_clk)) अणु
		dev_err(&pdev->dev, "Can't get our bus clock\n");
		वापस PTR_ERR(i2s->bus_clk);
	पूर्ण

	i2s->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					    i2s->variant->sun4i_i2s_regmap);
	अगर (IS_ERR(i2s->regmap)) अणु
		dev_err(&pdev->dev, "Regmap initialisation failed\n");
		वापस PTR_ERR(i2s->regmap);
	पूर्ण

	i2s->mod_clk = devm_clk_get(&pdev->dev, "mod");
	अगर (IS_ERR(i2s->mod_clk)) अणु
		dev_err(&pdev->dev, "Can't get our mod clock\n");
		वापस PTR_ERR(i2s->mod_clk);
	पूर्ण

	अगर (i2s->variant->has_reset) अणु
		i2s->rst = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
		अगर (IS_ERR(i2s->rst)) अणु
			dev_err(&pdev->dev, "Failed to get reset control\n");
			वापस PTR_ERR(i2s->rst);
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(i2s->rst)) अणु
		ret = reset_control_deनिश्चित(i2s->rst);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Failed to deassert the reset control\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	i2s->playback_dma_data.addr = res->start +
					i2s->variant->reg_offset_txdata;
	i2s->playback_dma_data.maxburst = 8;

	i2s->capture_dma_data.addr = res->start + SUN4I_I2S_FIFO_RX_REG;
	i2s->capture_dma_data.maxburst = 8;

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = sun4i_i2s_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	ret = sun4i_i2s_init_regmap_fields(&pdev->dev, i2s);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not initialise regmap fields\n");
		जाओ err_suspend;
	पूर्ण

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register PCM\n");
		जाओ err_suspend;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &sun4i_i2s_component,
					      &sun4i_i2s_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register DAI\n");
		जाओ err_suspend;
	पूर्ण

	वापस 0;

err_suspend:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		sun4i_i2s_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	अगर (!IS_ERR(i2s->rst))
		reset_control_निश्चित(i2s->rst);

	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_i2s *i2s = dev_get_drvdata(&pdev->dev);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		sun4i_i2s_runसमय_suspend(&pdev->dev);

	अगर (!IS_ERR(i2s->rst))
		reset_control_निश्चित(i2s->rst);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_i2s_match[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-i2s",
		.data = &sun4i_a10_i2s_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun6i-a31-i2s",
		.data = &sun6i_a31_i2s_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a83t-i2s",
		.data = &sun8i_a83t_i2s_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-h3-i2s",
		.data = &sun8i_h3_i2s_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-a64-codec-i2s",
		.data = &sun50i_a64_codec_i2s_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h6-i2s",
		.data = &sun50i_h6_i2s_quirks,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_i2s_match);

अटल स्थिर काष्ठा dev_pm_ops sun4i_i2s_pm_ops = अणु
	.runसमय_resume		= sun4i_i2s_runसमय_resume,
	.runसमय_suspend	= sun4i_i2s_runसमय_suspend,
पूर्ण;

अटल काष्ठा platक्रमm_driver sun4i_i2s_driver = अणु
	.probe	= sun4i_i2s_probe,
	.हटाओ	= sun4i_i2s_हटाओ,
	.driver	= अणु
		.name		= "sun4i-i2s",
		.of_match_table	= sun4i_i2s_match,
		.pm		= &sun4i_i2s_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_i2s_driver);

MODULE_AUTHOR("Andrea Venturi <be17068@iperbole.bo.it>");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A10 I2S driver");
MODULE_LICENSE("GPL");
