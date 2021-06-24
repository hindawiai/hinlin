<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/*
 * Copyright (c) 2018 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित _MESON_AIU_H
#घोषणा _MESON_AIU_H

काष्ठा clk;
काष्ठा clk_bulk_data;
काष्ठा device;
काष्ठा of_phandle_args;
काष्ठा snd_soc_dai;
काष्ठा snd_soc_dai_ops;

क्रमागत aiu_clk_ids अणु
	PCLK = 0,
	AOCLK,
	MCLK,
	MIXER
पूर्ण;

काष्ठा aiu_पूर्णांकerface अणु
	काष्ठा clk_bulk_data *clks;
	अचिन्हित पूर्णांक clk_num;
	पूर्णांक irq;
पूर्ण;

काष्ठा aiu_platक्रमm_data अणु
	bool has_acodec;
	bool has_clk_ctrl_more_i2s_भाग;
पूर्ण;

काष्ठा aiu अणु
	काष्ठा clk *pclk;
	काष्ठा clk *spdअगर_mclk;
	काष्ठा aiu_पूर्णांकerface i2s;
	काष्ठा aiu_पूर्णांकerface spdअगर;
	स्थिर काष्ठा aiu_platक्रमm_data *platक्रमm;
पूर्ण;

#घोषणा AIU_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |	\
		     SNDRV_PCM_FMTBIT_S20_LE |	\
		     SNDRV_PCM_FMTBIT_S24_LE)

पूर्णांक aiu_of_xlate_dai_name(काष्ठा snd_soc_component *component,
			  स्थिर काष्ठा of_phandle_args *args,
			  स्थिर अक्षर **dai_name,
			  अचिन्हित पूर्णांक component_id);

पूर्णांक aiu_hdmi_ctrl_रेजिस्टर_component(काष्ठा device *dev);
पूर्णांक aiu_acodec_ctrl_रेजिस्टर_component(काष्ठा device *dev);

पूर्णांक aiu_fअगरo_i2s_dai_probe(काष्ठा snd_soc_dai *dai);
पूर्णांक aiu_fअगरo_spdअगर_dai_probe(काष्ठा snd_soc_dai *dai);

बाह्य स्थिर काष्ठा snd_soc_dai_ops aiu_fअगरo_i2s_dai_ops;
बाह्य स्थिर काष्ठा snd_soc_dai_ops aiu_fअगरo_spdअगर_dai_ops;
बाह्य स्थिर काष्ठा snd_soc_dai_ops aiu_encoder_i2s_dai_ops;
बाह्य स्थिर काष्ठा snd_soc_dai_ops aiu_encoder_spdअगर_dai_ops;

#घोषणा AIU_IEC958_BPF			0x000
#घोषणा AIU_958_MISC			0x010
#घोषणा AIU_IEC958_DCU_FF_CTRL		0x01c
#घोषणा AIU_958_CHSTAT_L0		0x020
#घोषणा AIU_958_CHSTAT_L1		0x024
#घोषणा AIU_958_CTRL			0x028
#घोषणा AIU_I2S_SOURCE_DESC		0x034
#घोषणा AIU_I2S_DAC_CFG			0x040
#घोषणा AIU_I2S_SYNC			0x044
#घोषणा AIU_I2S_MISC			0x048
#घोषणा AIU_RST_SOFT			0x054
#घोषणा AIU_CLK_CTRL			0x058
#घोषणा AIU_CLK_CTRL_MORE		0x064
#घोषणा AIU_CODEC_DAC_LRCLK_CTRL	0x0a0
#घोषणा AIU_HDMI_CLK_DATA_CTRL		0x0a8
#घोषणा AIU_ACODEC_CTRL			0x0b0
#घोषणा AIU_958_CHSTAT_R0		0x0c0
#घोषणा AIU_958_CHSTAT_R1		0x0c4
#घोषणा AIU_MEM_I2S_START		0x180
#घोषणा AIU_MEM_I2S_MASKS		0x18c
#घोषणा AIU_MEM_I2S_CONTROL		0x190
#घोषणा AIU_MEM_IEC958_START		0x194
#घोषणा AIU_MEM_IEC958_CONTROL		0x1a4
#घोषणा AIU_MEM_I2S_BUF_CNTL		0x1d8
#घोषणा AIU_MEM_IEC958_BUF_CNTL		0x1fc

#पूर्ण_अगर /* _MESON_AIU_H */
