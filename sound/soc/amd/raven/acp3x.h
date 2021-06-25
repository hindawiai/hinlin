<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * AMD ALSA SoC PCM Driver
 *
 * Copyright 2016 Advanced Micro Devices, Inc.
 */

#समावेश "chip_offset_byte.h"
#समावेश <sound/pcm.h>
#घोषणा I2S_SP_INSTANCE                 0x01
#घोषणा I2S_BT_INSTANCE                 0x02

#घोषणा TDM_ENABLE 1
#घोषणा TDM_DISABLE 0

#घोषणा ACP3x_DEVS		4
#घोषणा ACP3x_PHY_BASE_ADDRESS 0x1240000
#घोषणा	ACP3x_I2S_MODE	0
#घोषणा	ACP3x_REG_START	0x1240000
#घोषणा	ACP3x_REG_END	0x1250200
#घोषणा ACP3x_I2STDM_REG_START	0x1242400
#घोषणा ACP3x_I2STDM_REG_END	0x1242410
#घोषणा ACP3x_BT_TDM_REG_START	0x1242800
#घोषणा ACP3x_BT_TDM_REG_END	0x1242810
#घोषणा I2S_MODE	0x04
#घोषणा	I2S_RX_THRESHOLD	27
#घोषणा	I2S_TX_THRESHOLD	28
#घोषणा	BT_TX_THRESHOLD 26
#घोषणा	BT_RX_THRESHOLD 25
#घोषणा ACP_ERR_INTR_MASK	29
#घोषणा ACP3x_POWER_ON 0x00
#घोषणा ACP3x_POWER_ON_IN_PROGRESS 0x01
#घोषणा ACP3x_POWER_OFF 0x02
#घोषणा ACP3x_POWER_OFF_IN_PROGRESS 0x03
#घोषणा ACP3x_SOFT_RESET__SoftResetAudDone_MASK	0x00010001

#घोषणा ACP_SRAM_PTE_OFFSET	0x02050000
#घोषणा ACP_SRAM_SP_PB_PTE_OFFSET	0x0
#घोषणा ACP_SRAM_SP_CP_PTE_OFFSET	0x100
#घोषणा ACP_SRAM_BT_PB_PTE_OFFSET	0x200
#घोषणा ACP_SRAM_BT_CP_PTE_OFFSET	0x300
#घोषणा PAGE_SIZE_4K_ENABLE 0x2
#घोषणा I2S_SP_TX_MEM_WINDOW_START	0x4000000
#घोषणा I2S_SP_RX_MEM_WINDOW_START	0x4020000
#घोषणा I2S_BT_TX_MEM_WINDOW_START	0x4040000
#घोषणा I2S_BT_RX_MEM_WINDOW_START	0x4060000

#घोषणा SP_PB_FIFO_ADDR_OFFSET		0x500
#घोषणा SP_CAPT_FIFO_ADDR_OFFSET	0x700
#घोषणा BT_PB_FIFO_ADDR_OFFSET		0x900
#घोषणा BT_CAPT_FIFO_ADDR_OFFSET	0xB00
#घोषणा PLAYBACK_MIN_NUM_PERIODS    2
#घोषणा PLAYBACK_MAX_NUM_PERIODS    8
#घोषणा PLAYBACK_MAX_PERIOD_SIZE    8192
#घोषणा PLAYBACK_MIN_PERIOD_SIZE    1024
#घोषणा CAPTURE_MIN_NUM_PERIODS     2
#घोषणा CAPTURE_MAX_NUM_PERIODS     8
#घोषणा CAPTURE_MAX_PERIOD_SIZE     8192
#घोषणा CAPTURE_MIN_PERIOD_SIZE     1024

#घोषणा MAX_BUFFER (PLAYBACK_MAX_PERIOD_SIZE * PLAYBACK_MAX_NUM_PERIODS)
#घोषणा MIN_BUFFER MAX_BUFFER
#घोषणा FIFO_SIZE 0x100
#घोषणा DMA_SIZE 0x40
#घोषणा FRM_LEN 0x100

#घोषणा SLOT_WIDTH_8 0x08
#घोषणा SLOT_WIDTH_16 0x10
#घोषणा SLOT_WIDTH_24 0x18
#घोषणा SLOT_WIDTH_32 0x20
#घोषणा ACP_PGFSM_CNTL_POWER_ON_MASK	0x01
#घोषणा ACP_PGFSM_CNTL_POWER_OFF_MASK	0x00
#घोषणा ACP_PGFSM_STATUS_MASK		0x03
#घोषणा ACP_POWERED_ON			0x00
#घोषणा ACP_POWER_ON_IN_PROGRESS	0x01
#घोषणा ACP_POWERED_OFF			0x02
#घोषणा ACP_POWER_OFF_IN_PROGRESS	0x03

#घोषणा ACP3x_ITER_IRER_SAMP_LEN_MASK	0x38
#घोषणा ACP_EXT_INTR_STAT_CLEAR_MASK 0xFFFFFFFF

काष्ठा acp3x_platक्रमm_info अणु
	u16 play_i2s_instance;
	u16 cap_i2s_instance;
	u16 capture_channel;
पूर्ण;

काष्ठा i2s_dev_data अणु
	bool tdm_mode;
	अचिन्हित पूर्णांक i2s_irq;
	u16 i2s_instance;
	u32 tdm_fmt;
	u32 substream_type;
	व्योम __iomem *acp3x_base;
	काष्ठा snd_pcm_substream *play_stream;
	काष्ठा snd_pcm_substream *capture_stream;
	काष्ठा snd_pcm_substream *i2ssp_play_stream;
	काष्ठा snd_pcm_substream *i2ssp_capture_stream;
पूर्ण;

काष्ठा i2s_stream_instance अणु
	u16 num_pages;
	u16 i2s_instance;
	u16 capture_channel;
	u16 direction;
	u16 channels;
	u32 xfer_resolution;
	u32 val;
	dma_addr_t dma_addr;
	u64 bytescount;
	व्योम __iomem *acp3x_base;
पूर्ण;

अटल अंतरभूत u32 rv_पढ़ोl(व्योम __iomem *base_addr)
अणु
	वापस पढ़ोl(base_addr - ACP3x_PHY_BASE_ADDRESS);
पूर्ण

अटल अंतरभूत व्योम rv_ग_लिखोl(u32 val, व्योम __iomem *base_addr)
अणु
	ग_लिखोl(val, base_addr - ACP3x_PHY_BASE_ADDRESS);
पूर्ण

अटल अंतरभूत u64 acp_get_byte_count(काष्ठा i2s_stream_instance *rtd,
							पूर्णांक direction)
अणु
	u64 byte_count;

	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			byte_count = rv_पढ़ोl(rtd->acp3x_base +
					mmACP_BT_TX_LINEARPOSITIONCNTR_HIGH);
			byte_count |= rv_पढ़ोl(rtd->acp3x_base +
					mmACP_BT_TX_LINEARPOSITIONCNTR_LOW);
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			byte_count = rv_पढ़ोl(rtd->acp3x_base +
					mmACP_I2S_TX_LINEARPOSITIONCNTR_HIGH);
			byte_count |= rv_पढ़ोl(rtd->acp3x_base +
					mmACP_I2S_TX_LINEARPOSITIONCNTR_LOW);
		पूर्ण

	पूर्ण अन्यथा अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			byte_count = rv_पढ़ोl(rtd->acp3x_base +
					mmACP_BT_RX_LINEARPOSITIONCNTR_HIGH);
			byte_count |= rv_पढ़ोl(rtd->acp3x_base +
					mmACP_BT_RX_LINEARPOSITIONCNTR_LOW);
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			byte_count = rv_पढ़ोl(rtd->acp3x_base +
					mmACP_I2S_RX_LINEARPOSITIONCNTR_HIGH);
			byte_count |= rv_पढ़ोl(rtd->acp3x_base +
					mmACP_I2S_RX_LINEARPOSITIONCNTR_LOW);
		पूर्ण
	पूर्ण
	वापस byte_count;
पूर्ण
