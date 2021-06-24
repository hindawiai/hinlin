<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * AMD ALSA SoC PDM Driver
 *
 * Copyright 2020 Advanced Micro Devices, Inc.
 */

#समावेश "rn_chip_offset_byte.h"

#घोषणा ACP_DEVS		3
#घोषणा ACP_PHY_BASE_ADDRESS 0x1240000
#घोषणा	ACP_REG_START	0x1240000
#घोषणा	ACP_REG_END	0x1250200

#घोषणा ACP_DEVICE_ID 0x15E2
#घोषणा ACP_POWER_ON 0x00
#घोषणा ACP_POWER_ON_IN_PROGRESS 0x01
#घोषणा ACP_POWER_OFF 0x02
#घोषणा ACP_POWER_OFF_IN_PROGRESS 0x03
#घोषणा ACP_SOFT_RESET_SOFTRESET_AUDDONE_MASK	0x00010001

#घोषणा ACP_PGFSM_CNTL_POWER_ON_MASK    0x01
#घोषणा ACP_PGFSM_CNTL_POWER_OFF_MASK   0x00
#घोषणा ACP_PGFSM_STATUS_MASK           0x03
#घोषणा ACP_POWERED_ON                  0x00
#घोषणा ACP_POWER_ON_IN_PROGRESS        0x01
#घोषणा ACP_POWERED_OFF                 0x02
#घोषणा ACP_POWER_OFF_IN_PROGRESS       0x03

#घोषणा ACP_ERROR_MASK 0x20000000
#घोषणा ACP_EXT_INTR_STAT_CLEAR_MASK 0xFFFFFFFF
#घोषणा PDM_DMA_STAT 0x10
#घोषणा PDM_DMA_INTR_MASK  0x10000
#घोषणा ACP_ERROR_STAT 29
#घोषणा PDM_DECIMATION_FACTOR 0x2
#घोषणा ACP_PDM_CLK_FREQ_MASK 0x07
#घोषणा ACP_WOV_MISC_CTRL_MASK 0x10
#घोषणा ACP_PDM_ENABLE 0x01
#घोषणा ACP_PDM_DISABLE 0x00
#घोषणा ACP_PDM_DMA_EN_STATUS 0x02
#घोषणा TWO_CH 0x02
#घोषणा DELAY_US 5
#घोषणा ACP_COUNTER 20000
/* समय in ms क्रम runसमय suspend delay */
#घोषणा ACP_SUSPEND_DELAY_MS	2000

#घोषणा ACP_SRAM_PTE_OFFSET	0x02050000
#घोषणा PAGE_SIZE_4K_ENABLE     0x2
#घोषणा MEM_WINDOW_START	0x4000000

#घोषणा CAPTURE_MIN_NUM_PERIODS     4
#घोषणा CAPTURE_MAX_NUM_PERIODS     4
#घोषणा CAPTURE_MAX_PERIOD_SIZE     8192
#घोषणा CAPTURE_MIN_PERIOD_SIZE     4096

#घोषणा MAX_BUFFER (CAPTURE_MAX_PERIOD_SIZE * CAPTURE_MAX_NUM_PERIODS)
#घोषणा MIN_BUFFER MAX_BUFFER
#घोषणा	ACP_DMIC_AUTO   -1

काष्ठा pdm_dev_data अणु
	u32 pdm_irq;
	व्योम __iomem *acp_base;
	काष्ठा snd_pcm_substream *capture_stream;
पूर्ण;

काष्ठा pdm_stream_instance अणु
	u16 num_pages;
	u16 channels;
	dma_addr_t dma_addr;
	u64 bytescount;
	व्योम __iomem *acp_base;
पूर्ण;

जोड़ acp_pdm_dma_count अणु
	काष्ठा अणु
	u32 low;
	u32 high;
	पूर्ण bcount;
	u64 bytescount;
पूर्ण;

अटल अंतरभूत u32 rn_पढ़ोl(व्योम __iomem *base_addr)
अणु
	वापस पढ़ोl(base_addr - ACP_PHY_BASE_ADDRESS);
पूर्ण

अटल अंतरभूत व्योम rn_ग_लिखोl(u32 val, व्योम __iomem *base_addr)
अणु
	ग_लिखोl(val, base_addr - ACP_PHY_BASE_ADDRESS);
पूर्ण
