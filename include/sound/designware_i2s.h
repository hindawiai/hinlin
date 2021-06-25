<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (ST) 2012 Rajeev Kumar (rajeevkumar.linux@gmail.com)
 */

#अगर_अघोषित __SOUND_DESIGNWARE_I2S_H
#घोषणा __SOUND_DESIGNWARE_I2S_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/types.h>

/*
 * काष्ठा i2s_clk_config_data - represent i2s clk configuration data
 * @chan_nr: number of channel
 * @data_width: number of bits per sample (8/16/24/32 bit)
 * @sample_rate: sampling frequency (8Khz, 16Khz, 32Khz, 44Khz, 48Khz)
 */
काष्ठा i2s_clk_config_data अणु
	पूर्णांक chan_nr;
	u32 data_width;
	u32 sample_rate;
पूर्ण;

काष्ठा i2s_platक्रमm_data अणु
	#घोषणा DWC_I2S_PLAY	(1 << 0)
	#घोषणा DWC_I2S_RECORD	(1 << 1)
	#घोषणा DW_I2S_SLAVE	(1 << 2)
	#घोषणा DW_I2S_MASTER	(1 << 3)
	अचिन्हित पूर्णांक cap;
	पूर्णांक channel;
	u32 snd_fmts;
	u32 snd_rates;

	#घोषणा DW_I2S_QUIRK_COMP_REG_OFFSET	(1 << 0)
	#घोषणा DW_I2S_QUIRK_COMP_PARAM1	(1 << 1)
	#घोषणा DW_I2S_QUIRK_16BIT_IDX_OVERRIDE (1 << 2)
	अचिन्हित पूर्णांक quirks;
	अचिन्हित पूर्णांक i2s_reg_comp1;
	अचिन्हित पूर्णांक i2s_reg_comp2;

	व्योम *play_dma_data;
	व्योम *capture_dma_data;
	bool (*filter)(काष्ठा dma_chan *chan, व्योम *slave);
	पूर्णांक (*i2s_clk_cfg)(काष्ठा i2s_clk_config_data *config);
पूर्ण;

काष्ठा i2s_dma_data अणु
	व्योम *data;
	dma_addr_t addr;
	u32 max_burst;
	क्रमागत dma_slave_buswidth addr_width;
	bool (*filter)(काष्ठा dma_chan *chan, व्योम *slave);
पूर्ण;

/* I2S DMA रेजिस्टरs */
#घोषणा I2S_RXDMA		0x01C0
#घोषणा I2S_TXDMA		0x01C8

#घोषणा TWO_CHANNEL_SUPPORT	2	/* up to 2.0 */
#घोषणा FOUR_CHANNEL_SUPPORT	4	/* up to 3.1 */
#घोषणा SIX_CHANNEL_SUPPORT	6	/* up to 5.1 */
#घोषणा EIGHT_CHANNEL_SUPPORT	8	/* up to 7.1 */

#पूर्ण_अगर /*  __SOUND_DESIGNWARE_I2S_H */
