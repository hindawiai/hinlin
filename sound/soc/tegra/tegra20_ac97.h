<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra20_ac97.h - Definitions क्रम the Tegra20 AC97 controller driver
 *
 * Copyright (c) 2012 Lucas Stach <dev@lynxeye.de>
 *
 * Partly based on code copyright/by:
 *
 * Copyright (c) 2011,2012 Toradex Inc.
 */

#अगर_अघोषित __TEGRA20_AC97_H__
#घोषणा __TEGRA20_AC97_H__

#समावेश "tegra_pcm.h"

#घोषणा TEGRA20_AC97_CTRL				0x00
#घोषणा TEGRA20_AC97_CMD				0x04
#घोषणा TEGRA20_AC97_STATUS1				0x08
/* ... */
#घोषणा TEGRA20_AC97_FIFO1_SCR				0x1c
/* ... */
#घोषणा TEGRA20_AC97_FIFO_TX1				0x40
#घोषणा TEGRA20_AC97_FIFO_RX1				0x80

/* TEGRA20_AC97_CTRL */
#घोषणा TEGRA20_AC97_CTRL_STM2_EN			(1 << 16)
#घोषणा TEGRA20_AC97_CTRL_DOUBLE_SAMPLING_EN		(1 << 11)
#घोषणा TEGRA20_AC97_CTRL_IO_CNTRL_EN			(1 << 10)
#घोषणा TEGRA20_AC97_CTRL_HSET_DAC_EN			(1 << 9)
#घोषणा TEGRA20_AC97_CTRL_LINE2_DAC_EN			(1 << 8)
#घोषणा TEGRA20_AC97_CTRL_PCM_LFE_EN			(1 << 7)
#घोषणा TEGRA20_AC97_CTRL_PCM_SUR_EN			(1 << 6)
#घोषणा TEGRA20_AC97_CTRL_PCM_CEN_DAC_EN		(1 << 5)
#घोषणा TEGRA20_AC97_CTRL_LINE1_DAC_EN			(1 << 4)
#घोषणा TEGRA20_AC97_CTRL_PCM_DAC_EN			(1 << 3)
#घोषणा TEGRA20_AC97_CTRL_COLD_RESET			(1 << 2)
#घोषणा TEGRA20_AC97_CTRL_WARM_RESET			(1 << 1)
#घोषणा TEGRA20_AC97_CTRL_STM_EN			(1 << 0)

/* TEGRA20_AC97_CMD */
#घोषणा TEGRA20_AC97_CMD_CMD_ADDR_SHIFT			24
#घोषणा TEGRA20_AC97_CMD_CMD_ADDR_MASK			(0xff << TEGRA20_AC97_CMD_CMD_ADDR_SHIFT)
#घोषणा TEGRA20_AC97_CMD_CMD_DATA_SHIFT			8
#घोषणा TEGRA20_AC97_CMD_CMD_DATA_MASK			(0xffff << TEGRA20_AC97_CMD_CMD_DATA_SHIFT)
#घोषणा TEGRA20_AC97_CMD_CMD_ID_SHIFT			2
#घोषणा TEGRA20_AC97_CMD_CMD_ID_MASK			(0x3 << TEGRA20_AC97_CMD_CMD_ID_SHIFT)
#घोषणा TEGRA20_AC97_CMD_BUSY				(1 << 0)

/* TEGRA20_AC97_STATUS1 */
#घोषणा TEGRA20_AC97_STATUS1_STA_ADDR1_SHIFT		24
#घोषणा TEGRA20_AC97_STATUS1_STA_ADDR1_MASK		(0xff << TEGRA20_AC97_STATUS1_STA_ADDR1_SHIFT)
#घोषणा TEGRA20_AC97_STATUS1_STA_DATA1_SHIFT		8
#घोषणा TEGRA20_AC97_STATUS1_STA_DATA1_MASK		(0xffff << TEGRA20_AC97_STATUS1_STA_DATA1_SHIFT)
#घोषणा TEGRA20_AC97_STATUS1_STA_VALID1			(1 << 2)
#घोषणा TEGRA20_AC97_STATUS1_STANDBY1			(1 << 1)
#घोषणा TEGRA20_AC97_STATUS1_CODEC1_RDY			(1 << 0)

/* TEGRA20_AC97_FIFO1_SCR */
#घोषणा TEGRA20_AC97_FIFO_SCR_REC_MT_CNT_SHIFT		27
#घोषणा TEGRA20_AC97_FIFO_SCR_REC_MT_CNT_MASK		(0x1f << TEGRA20_AC97_FIFO_SCR_REC_MT_CNT_SHIFT)
#घोषणा TEGRA20_AC97_FIFO_SCR_PB_MT_CNT_SHIFT		22
#घोषणा TEGRA20_AC97_FIFO_SCR_PB_MT_CNT_MASK		(0x1f << TEGRA20_AC97_FIFO_SCR_PB_MT_CNT_SHIFT)
#घोषणा TEGRA20_AC97_FIFO_SCR_REC_OVERRUN_INT_STA	(1 << 19)
#घोषणा TEGRA20_AC97_FIFO_SCR_PB_UNDERRUN_INT_STA	(1 << 18)
#घोषणा TEGRA20_AC97_FIFO_SCR_REC_FORCE_MT		(1 << 17)
#घोषणा TEGRA20_AC97_FIFO_SCR_PB_FORCE_MT		(1 << 16)
#घोषणा TEGRA20_AC97_FIFO_SCR_REC_FULL_EN		(1 << 15)
#घोषणा TEGRA20_AC97_FIFO_SCR_REC_3QRT_FULL_EN		(1 << 14)
#घोषणा TEGRA20_AC97_FIFO_SCR_REC_QRT_FULL_EN		(1 << 13)
#घोषणा TEGRA20_AC97_FIFO_SCR_REC_EMPTY_EN		(1 << 12)
#घोषणा TEGRA20_AC97_FIFO_SCR_PB_NOT_FULL_EN		(1 << 11)
#घोषणा TEGRA20_AC97_FIFO_SCR_PB_QRT_MT_EN		(1 << 10)
#घोषणा TEGRA20_AC97_FIFO_SCR_PB_3QRT_MT_EN		(1 << 9)
#घोषणा TEGRA20_AC97_FIFO_SCR_PB_EMPTY_MT_EN		(1 << 8)

काष्ठा tegra20_ac97 अणु
	काष्ठा clk *clk_ac97;
	काष्ठा snd_dmaengine_dai_dma_data capture_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data playback_dma_data;
	काष्ठा reset_control *reset;
	काष्ठा regmap *regmap;
	पूर्णांक reset_gpio;
	पूर्णांक sync_gpio;
पूर्ण;
#पूर्ण_अगर /* __TEGRA20_AC97_H__ */
