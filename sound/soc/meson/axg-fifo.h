<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/*
 * Copyright (c) 2018 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित _MESON_AXG_FIFO_H
#घोषणा _MESON_AXG_FIFO_H

काष्ठा clk;
काष्ठा platक्रमm_device;
काष्ठा reg_field;
काष्ठा regmap;
काष्ठा regmap_field;
काष्ठा reset_control;

काष्ठा snd_soc_component_driver;
काष्ठा snd_soc_dai;
काष्ठा snd_soc_dai_driver;

काष्ठा snd_soc_pcm_runसमय;

#घोषणा AXG_FIFO_CH_MAX			128
#घोषणा AXG_FIFO_RATES			(SNDRV_PCM_RATE_5512 |		\
					 SNDRV_PCM_RATE_8000_192000)
#घोषणा AXG_FIFO_FORMATS		(SNDRV_PCM_FMTBIT_S8 |		\
					 SNDRV_PCM_FMTBIT_S16_LE |	\
					 SNDRV_PCM_FMTBIT_S20_LE |	\
					 SNDRV_PCM_FMTBIT_S24_LE |	\
					 SNDRV_PCM_FMTBIT_S32_LE |	\
					 SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE)

#घोषणा AXG_FIFO_BURST			8

#घोषणा FIFO_INT_ADDR_FINISH		BIT(0)
#घोषणा FIFO_INT_ADDR_INT		BIT(1)
#घोषणा FIFO_INT_COUNT_REPEAT		BIT(2)
#घोषणा FIFO_INT_COUNT_ONCE		BIT(3)
#घोषणा FIFO_INT_FIFO_ZERO		BIT(4)
#घोषणा FIFO_INT_FIFO_DEPTH		BIT(5)
#घोषणा FIFO_INT_MASK			GENMASK(7, 0)

#घोषणा FIFO_CTRL0			0x00
#घोषणा  CTRL0_DMA_EN			BIT(31)
#घोषणा  CTRL0_INT_EN(x)		((x) << 16)
#घोषणा  CTRL0_SEL_MASK			GENMASK(2, 0)
#घोषणा  CTRL0_SEL_SHIFT		0
#घोषणा FIFO_CTRL1			0x04
#घोषणा  CTRL1_INT_CLR(x)		((x) << 0)
#घोषणा  CTRL1_STATUS2_SEL_MASK		GENMASK(11, 8)
#घोषणा  CTRL1_STATUS2_SEL(x)		((x) << 8)
#घोषणा   STATUS2_SEL_DDR_READ		0
#घोषणा  CTRL1_FRDDR_DEPTH_MASK		GENMASK(31, 24)
#घोषणा  CTRL1_FRDDR_DEPTH(x)		((x) << 24)
#घोषणा FIFO_START_ADDR			0x08
#घोषणा FIFO_FINISH_ADDR		0x0c
#घोषणा FIFO_INT_ADDR			0x10
#घोषणा FIFO_STATUS1			0x14
#घोषणा  STATUS1_INT_STS(x)		((x) << 0)
#घोषणा FIFO_STATUS2			0x18
#घोषणा FIFO_INIT_ADDR			0x24
#घोषणा FIFO_CTRL2			0x28

काष्ठा axg_fअगरo अणु
	काष्ठा regmap *map;
	काष्ठा clk *pclk;
	काष्ठा reset_control *arb;
	काष्ठा regmap_field *field_threshold;
	अचिन्हित पूर्णांक depth;
	पूर्णांक irq;
पूर्ण;

काष्ठा axg_fअगरo_match_data अणु
	स्थिर काष्ठा snd_soc_component_driver *component_drv;
	काष्ठा snd_soc_dai_driver *dai_drv;
	काष्ठा reg_field field_threshold;
पूर्ण;

पूर्णांक axg_fअगरo_pcm_खोलो(काष्ठा snd_soc_component *component,
		      काष्ठा snd_pcm_substream *ss);
पूर्णांक axg_fअगरo_pcm_बंद(काष्ठा snd_soc_component *component,
		       काष्ठा snd_pcm_substream *ss);
पूर्णांक axg_fअगरo_pcm_hw_params(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *ss,
			   काष्ठा snd_pcm_hw_params *params);
पूर्णांक g12a_fअगरo_pcm_hw_params(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *ss,
			    काष्ठा snd_pcm_hw_params *params);
पूर्णांक axg_fअगरo_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *ss);
snd_pcm_uframes_t axg_fअगरo_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
				       काष्ठा snd_pcm_substream *ss);
पूर्णांक axg_fअगरo_pcm_trigger(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *ss, पूर्णांक cmd);

पूर्णांक axg_fअगरo_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd, अचिन्हित पूर्णांक type);
पूर्णांक axg_fअगरo_probe(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* _MESON_AXG_FIFO_H */
