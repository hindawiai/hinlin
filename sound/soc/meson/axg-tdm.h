<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
 *
 * Copyright (c) 2018 Baylibre SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित _MESON_AXG_TDM_H
#घोषणा _MESON_AXG_TDM_H

#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#घोषणा AXG_TDM_NUM_LANES	4
#घोषणा AXG_TDM_CHANNEL_MAX	128
#घोषणा AXG_TDM_RATES		(SNDRV_PCM_RATE_5512 |		\
				 SNDRV_PCM_RATE_8000_192000)
#घोषणा AXG_TDM_FORMATS		(SNDRV_PCM_FMTBIT_S8 |		\
				 SNDRV_PCM_FMTBIT_S16_LE |	\
				 SNDRV_PCM_FMTBIT_S20_LE |	\
				 SNDRV_PCM_FMTBIT_S24_LE |	\
				 SNDRV_PCM_FMTBIT_S32_LE)

काष्ठा axg_tdm_अगरace अणु
	काष्ठा clk *sclk;
	काष्ठा clk *lrclk;
	काष्ठा clk *mclk;
	अचिन्हित दीर्घ mclk_rate;

	/* क्रमmat is common to all the DAIs of the अगरace */
	अचिन्हित पूर्णांक fmt;
	अचिन्हित पूर्णांक slots;
	अचिन्हित पूर्णांक slot_width;

	/* For component wide symmetry */
	पूर्णांक rate;
पूर्ण;

अटल अंतरभूत bool axg_tdm_lrclk_invert(अचिन्हित पूर्णांक fmt)
अणु
	वापस ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) == SND_SOC_DAIFMT_I2S) ^
		!!(fmt & (SND_SOC_DAIFMT_IB_IF | SND_SOC_DAIFMT_NB_IF));
पूर्ण

अटल अंतरभूत bool axg_tdm_sclk_invert(अचिन्हित पूर्णांक fmt)
अणु
	वापस fmt & (SND_SOC_DAIFMT_IB_IF | SND_SOC_DAIFMT_IB_NF);
पूर्ण

काष्ठा axg_tdm_stream अणु
	काष्ठा axg_tdm_अगरace *अगरace;
	काष्ठा list_head क्रमmatter_list;
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक channels;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक physical_width;
	u32 *mask;
	bool पढ़ोy;
पूर्ण;

काष्ठा axg_tdm_stream *axg_tdm_stream_alloc(काष्ठा axg_tdm_अगरace *अगरace);
व्योम axg_tdm_stream_मुक्त(काष्ठा axg_tdm_stream *ts);
पूर्णांक axg_tdm_stream_start(काष्ठा axg_tdm_stream *ts);
व्योम axg_tdm_stream_stop(काष्ठा axg_tdm_stream *ts);

अटल अंतरभूत पूर्णांक axg_tdm_stream_reset(काष्ठा axg_tdm_stream *ts)
अणु
	axg_tdm_stream_stop(ts);
	वापस axg_tdm_stream_start(ts);
पूर्ण

पूर्णांक axg_tdm_set_tdm_slots(काष्ठा snd_soc_dai *dai, u32 *tx_mask,
			  u32 *rx_mask, अचिन्हित पूर्णांक slots,
			  अचिन्हित पूर्णांक slot_width);

#पूर्ण_अगर /* _MESON_AXG_TDM_H */
