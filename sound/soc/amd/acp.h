<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ACP_HW_H
#घोषणा __ACP_HW_H

#समावेश "include/acp_2_2_d.h"
#समावेश "include/acp_2_2_sh_mask.h"

#घोषणा ACP_PAGE_SIZE_4K_ENABLE			0x02

#घोषणा ACP_PLAYBACK_PTE_OFFSET			10
#घोषणा ACP_CAPTURE_PTE_OFFSET			0

/* Playback and Capture Offset क्रम Stoney */
#घोषणा ACP_ST_PLAYBACK_PTE_OFFSET	0x04
#घोषणा ACP_ST_CAPTURE_PTE_OFFSET	0x00
#घोषणा ACP_ST_BT_PLAYBACK_PTE_OFFSET	0x08
#घोषणा ACP_ST_BT_CAPTURE_PTE_OFFSET	0x0c

#घोषणा ACP_GARLIC_CNTL_DEFAULT			0x00000FB4
#घोषणा ACP_ONION_CNTL_DEFAULT			0x00000FB4

#घोषणा ACP_PHYSICAL_BASE			0x14000

/*
 * In हाल of I2S SP controller instance, Stoney uses SRAM bank 1 क्रम
 * playback and SRAM Bank 2 क्रम capture where as in हाल of BT I2S
 * Instance, Stoney uses SRAM Bank 3 क्रम playback & SRAM Bank 4 will
 * be used क्रम capture. Carrizo uses I2S SP controller instance. SRAM Banks
 * 1, 2, 3, 4 will be used क्रम playback & SRAM Banks 5, 6, 7, 8 will be used
 * क्रम capture scenario.
 */
#घोषणा ACP_SRAM_BANK_1_ADDRESS		0x4002000
#घोषणा ACP_SRAM_BANK_2_ADDRESS		0x4004000
#घोषणा ACP_SRAM_BANK_3_ADDRESS		0x4006000
#घोषणा ACP_SRAM_BANK_4_ADDRESS		0x4008000
#घोषणा ACP_SRAM_BANK_5_ADDRESS		0x400A000

#घोषणा ACP_DMA_RESET_TIME			10000
#घोषणा ACP_CLOCK_EN_TIME_OUT_VALUE		0x000000FF
#घोषणा ACP_SOFT_RESET_DONE_TIME_OUT_VALUE	0x000000FF
#घोषणा ACP_DMA_COMPLETE_TIME_OUT_VALUE		0x000000FF

#घोषणा ACP_SRAM_BASE_ADDRESS			0x4000000
#घोषणा ACP_DAGB_GRP_SRAM_BASE_ADDRESS		0x4001000
#घोषणा ACP_DAGB_GRP_SRBM_SRAM_BASE_OFFSET	0x1000
#घोषणा ACP_INTERNAL_APERTURE_WINDOW_0_ADDRESS	0x00000000
#घोषणा ACP_INTERNAL_APERTURE_WINDOW_4_ADDRESS	0x01800000

#घोषणा TO_ACP_I2S_1   0x2
#घोषणा TO_ACP_I2S_2   0x4
#घोषणा TO_BLUETOOTH   0x3
#घोषणा FROM_ACP_I2S_1 0xa
#घोषणा FROM_ACP_I2S_2 0xb
#घोषणा FROM_BLUETOOTH 0xb

#घोषणा I2S_SP_INSTANCE                 0x01
#घोषणा I2S_BT_INSTANCE                 0x02
#घोषणा CAP_CHANNEL0			0x00
#घोषणा CAP_CHANNEL1			0x01

#घोषणा ACP_TILE_ON_MASK                0x03
#घोषणा ACP_TILE_OFF_MASK               0x02
#घोषणा ACP_TILE_ON_RETAIN_REG_MASK     0x1f
#घोषणा ACP_TILE_OFF_RETAIN_REG_MASK    0x20

#घोषणा ACP_TILE_P1_MASK                0x3e
#घोषणा ACP_TILE_P2_MASK                0x3d
#घोषणा ACP_TILE_DSP0_MASK              0x3b
#घोषणा ACP_TILE_DSP1_MASK              0x37

#घोषणा ACP_TILE_DSP2_MASK              0x2f
/* Playback DMA channels */
#घोषणा SYSRAM_TO_ACP_CH_NUM 12
#घोषणा ACP_TO_I2S_DMA_CH_NUM 13

/* Capture DMA channels */
#घोषणा I2S_TO_ACP_DMA_CH_NUM 14
#घोषणा ACP_TO_SYSRAM_CH_NUM 15

/* Playback DMA Channels क्रम I2S BT instance */
#घोषणा SYSRAM_TO_ACP_BT_INSTANCE_CH_NUM  8
#घोषणा ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM 9

/* Capture DMA Channels क्रम I2S BT Instance */
#घोषणा I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM 10
#घोषणा ACP_TO_SYSRAM_BT_INSTANCE_CH_NUM 11

#घोषणा NUM_DSCRS_PER_CHANNEL 2

#घोषणा PLAYBACK_START_DMA_DESCR_CH12 0
#घोषणा PLAYBACK_END_DMA_DESCR_CH12 1
#घोषणा PLAYBACK_START_DMA_DESCR_CH13 2
#घोषणा PLAYBACK_END_DMA_DESCR_CH13 3

#घोषणा CAPTURE_START_DMA_DESCR_CH14 4
#घोषणा CAPTURE_END_DMA_DESCR_CH14 5
#घोषणा CAPTURE_START_DMA_DESCR_CH15 6
#घोषणा CAPTURE_END_DMA_DESCR_CH15 7

/* I2S BT Instance DMA Descriptors */
#घोषणा PLAYBACK_START_DMA_DESCR_CH8 8
#घोषणा PLAYBACK_END_DMA_DESCR_CH8 9
#घोषणा PLAYBACK_START_DMA_DESCR_CH9 10
#घोषणा PLAYBACK_END_DMA_DESCR_CH9 11

#घोषणा CAPTURE_START_DMA_DESCR_CH10 12
#घोषणा CAPTURE_END_DMA_DESCR_CH10 13
#घोषणा CAPTURE_START_DMA_DESCR_CH11 14
#घोषणा CAPTURE_END_DMA_DESCR_CH11 15

#घोषणा mmACP_I2S_16BIT_RESOLUTION_EN       0x5209
#घोषणा ACP_I2S_MIC_16BIT_RESOLUTION_EN 0x01
#घोषणा ACP_I2S_SP_16BIT_RESOLUTION_EN	0x02
#घोषणा ACP_I2S_BT_16BIT_RESOLUTION_EN	0x04
#घोषणा ACP_BT_UART_PAD_SELECT_MASK	0x1

क्रमागत acp_dma_priority_level अणु
	/* 0x0 Specअगरies the DMA channel is given normal priority */
	ACP_DMA_PRIORITY_LEVEL_NORMAL = 0x0,
	/* 0x1 Specअगरies the DMA channel is given high priority */
	ACP_DMA_PRIORITY_LEVEL_HIGH = 0x1,
	ACP_DMA_PRIORITY_LEVEL_FORCESIZE = 0xFF
पूर्ण;

काष्ठा audio_substream_data अणु
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक order;
	u16 num_of_pages;
	u16 i2s_instance;
	u16 capture_channel;
	u16 direction;
	u16 ch1;
	u16 ch2;
	u16 destination;
	u16 dma_dscr_idx_1;
	u16 dma_dscr_idx_2;
	u32 pte_offset;
	u32 sram_bank;
	u32 byte_cnt_high_reg_offset;
	u32 byte_cnt_low_reg_offset;
	u32 dma_curr_dscr;
	uपूर्णांक64_t size;
	u64 bytescount;
	व्योम __iomem *acp_mmio;
पूर्ण;

काष्ठा audio_drv_data अणु
	काष्ठा snd_pcm_substream *play_i2ssp_stream;
	काष्ठा snd_pcm_substream *capture_i2ssp_stream;
	काष्ठा snd_pcm_substream *play_i2sbt_stream;
	काष्ठा snd_pcm_substream *capture_i2sbt_stream;
	व्योम __iomem *acp_mmio;
	u32 asic_type;
पूर्ण;

/*
 * this काष्ठाure used क्रम platक्रमm data transfer between machine driver
 * and dma driver
 */
काष्ठा acp_platक्रमm_info अणु
	u16 play_i2s_instance;
	u16 cap_i2s_instance;
	u16 capture_channel;
पूर्ण;

जोड़ acp_dma_count अणु
	काष्ठा अणु
	u32 low;
	u32 high;
	पूर्ण bcount;
	u64 bytescount;
पूर्ण;

क्रमागत अणु
	ACP_TILE_P1 = 0,
	ACP_TILE_P2,
	ACP_TILE_DSP0,
	ACP_TILE_DSP1,
	ACP_TILE_DSP2,
पूर्ण;

क्रमागत अणु
	ACP_DMA_ATTR_SHAREDMEM_TO_DAGB_ONION = 0x0,
	ACP_DMA_ATTR_SHARED_MEM_TO_DAGB_GARLIC = 0x1,
	ACP_DMA_ATTR_DAGB_ONION_TO_SHAREDMEM = 0x8,
	ACP_DMA_ATTR_DAGB_GARLIC_TO_SHAREDMEM = 0x9,
	ACP_DMA_ATTR_FORCE_SIZE = 0xF
पूर्ण;

प्रकार काष्ठा acp_dma_dscr_transfer अणु
	/* Specअगरies the source memory location क्रम the DMA data transfer. */
	u32 src;
	/*
	 * Specअगरies the destination memory location to where the data will
	 * be transferred.
	 */
	u32 dest;
	/*
	 * Specअगरies the number of bytes need to be transferred
	 * from source to destination memory.Transfer direction & IOC enable
	 */
	u32 xfer_val;
	/* Reserved क्रम future use */
	u32 reserved;
पूर्ण acp_dma_dscr_transfer_t;

#पूर्ण_अगर /*__ACP_HW_H */
