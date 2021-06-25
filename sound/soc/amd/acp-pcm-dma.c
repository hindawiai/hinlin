<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD ALSA SoC PCM Driver क्रम ACP 2.x
 *
 * Copyright 2014-2015 Advanced Micro Devices, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/sizes.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <sound/soc.h>
#समावेश <drm/amd_asic_type.h>
#समावेश "acp.h"

#घोषणा DRV_NAME "acp_audio_dma"

#घोषणा PLAYBACK_MIN_NUM_PERIODS    2
#घोषणा PLAYBACK_MAX_NUM_PERIODS    2
#घोषणा PLAYBACK_MAX_PERIOD_SIZE    16384
#घोषणा PLAYBACK_MIN_PERIOD_SIZE    1024
#घोषणा CAPTURE_MIN_NUM_PERIODS     2
#घोषणा CAPTURE_MAX_NUM_PERIODS     2
#घोषणा CAPTURE_MAX_PERIOD_SIZE     16384
#घोषणा CAPTURE_MIN_PERIOD_SIZE     1024

#घोषणा MAX_BUFFER (PLAYBACK_MAX_PERIOD_SIZE * PLAYBACK_MAX_NUM_PERIODS)
#घोषणा MIN_BUFFER MAX_BUFFER

#घोषणा ST_PLAYBACK_MAX_PERIOD_SIZE 4096
#घोषणा ST_CAPTURE_MAX_PERIOD_SIZE  ST_PLAYBACK_MAX_PERIOD_SIZE
#घोषणा ST_MAX_BUFFER (ST_PLAYBACK_MAX_PERIOD_SIZE * PLAYBACK_MAX_NUM_PERIODS)
#घोषणा ST_MIN_BUFFER ST_MAX_BUFFER

#घोषणा DRV_NAME "acp_audio_dma"
bool bt_uart_enable = true;
EXPORT_SYMBOL(bt_uart_enable);

अटल स्थिर काष्ठा snd_pcm_hardware acp_pcm_hardware_playback = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 1,
	.channels_max = 8,
	.rates = SNDRV_PCM_RATE_8000_96000,
	.rate_min = 8000,
	.rate_max = 96000,
	.buffer_bytes_max = PLAYBACK_MAX_NUM_PERIODS * PLAYBACK_MAX_PERIOD_SIZE,
	.period_bytes_min = PLAYBACK_MIN_PERIOD_SIZE,
	.period_bytes_max = PLAYBACK_MAX_PERIOD_SIZE,
	.periods_min = PLAYBACK_MIN_NUM_PERIODS,
	.periods_max = PLAYBACK_MAX_NUM_PERIODS,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware acp_pcm_hardware_capture = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_BATCH |
	    SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 1,
	.channels_max = 2,
	.rates = SNDRV_PCM_RATE_8000_48000,
	.rate_min = 8000,
	.rate_max = 48000,
	.buffer_bytes_max = CAPTURE_MAX_NUM_PERIODS * CAPTURE_MAX_PERIOD_SIZE,
	.period_bytes_min = CAPTURE_MIN_PERIOD_SIZE,
	.period_bytes_max = CAPTURE_MAX_PERIOD_SIZE,
	.periods_min = CAPTURE_MIN_NUM_PERIODS,
	.periods_max = CAPTURE_MAX_NUM_PERIODS,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware acp_st_pcm_hardware_playback = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 1,
	.channels_max = 8,
	.rates = SNDRV_PCM_RATE_8000_96000,
	.rate_min = 8000,
	.rate_max = 96000,
	.buffer_bytes_max = ST_MAX_BUFFER,
	.period_bytes_min = PLAYBACK_MIN_PERIOD_SIZE,
	.period_bytes_max = ST_PLAYBACK_MAX_PERIOD_SIZE,
	.periods_min = PLAYBACK_MIN_NUM_PERIODS,
	.periods_max = PLAYBACK_MAX_NUM_PERIODS,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware acp_st_pcm_hardware_capture = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 1,
	.channels_max = 2,
	.rates = SNDRV_PCM_RATE_8000_48000,
	.rate_min = 8000,
	.rate_max = 48000,
	.buffer_bytes_max = ST_MAX_BUFFER,
	.period_bytes_min = CAPTURE_MIN_PERIOD_SIZE,
	.period_bytes_max = ST_CAPTURE_MAX_PERIOD_SIZE,
	.periods_min = CAPTURE_MIN_NUM_PERIODS,
	.periods_max = CAPTURE_MAX_NUM_PERIODS,
पूर्ण;

अटल u32 acp_reg_पढ़ो(व्योम __iomem *acp_mmio, u32 reg)
अणु
	वापस पढ़ोl(acp_mmio + (reg * 4));
पूर्ण

अटल व्योम acp_reg_ग_लिखो(u32 val, व्योम __iomem *acp_mmio, u32 reg)
अणु
	ग_लिखोl(val, acp_mmio + (reg * 4));
पूर्ण

/*
 * Configure a given dma channel parameters - enable/disable,
 * number of descriptors, priority
 */
अटल व्योम config_acp_dma_channel(व्योम __iomem *acp_mmio, u8 ch_num,
				   u16 dscr_strt_idx, u16 num_dscrs,
				   क्रमागत acp_dma_priority_level priority_level)
अणु
	u32 dma_ctrl;

	/* disable the channel run field */
	dma_ctrl = acp_reg_पढ़ो(acp_mmio, mmACP_DMA_CNTL_0 + ch_num);
	dma_ctrl &= ~ACP_DMA_CNTL_0__DMAChRun_MASK;
	acp_reg_ग_लिखो(dma_ctrl, acp_mmio, mmACP_DMA_CNTL_0 + ch_num);

	/* program a DMA channel with first descriptor to be processed. */
	acp_reg_ग_लिखो((ACP_DMA_DSCR_STRT_IDX_0__DMAChDscrStrtIdx_MASK
			& dscr_strt_idx),
			acp_mmio, mmACP_DMA_DSCR_STRT_IDX_0 + ch_num);

	/*
	 * program a DMA channel with the number of descriptors to be
	 * processed in the transfer
	 */
	acp_reg_ग_लिखो(ACP_DMA_DSCR_CNT_0__DMAChDscrCnt_MASK & num_dscrs,
		      acp_mmio, mmACP_DMA_DSCR_CNT_0 + ch_num);

	/* set DMA channel priority */
	acp_reg_ग_लिखो(priority_level, acp_mmio, mmACP_DMA_PRIO_0 + ch_num);
पूर्ण

/* Initialize a dma descriptor in SRAM based on descritor inक्रमmation passed */
अटल व्योम config_dma_descriptor_in_sram(व्योम __iomem *acp_mmio,
					  u16 descr_idx,
					  acp_dma_dscr_transfer_t *descr_info)
अणु
	u32 sram_offset;

	sram_offset = (descr_idx * माप(acp_dma_dscr_transfer_t));

	/* program the source base address. */
	acp_reg_ग_लिखो(sram_offset, acp_mmio, mmACP_SRBM_Targ_Idx_Addr);
	acp_reg_ग_लिखो(descr_info->src,	acp_mmio, mmACP_SRBM_Targ_Idx_Data);
	/* program the destination base address. */
	acp_reg_ग_लिखो(sram_offset + 4,	acp_mmio, mmACP_SRBM_Targ_Idx_Addr);
	acp_reg_ग_लिखो(descr_info->dest, acp_mmio, mmACP_SRBM_Targ_Idx_Data);

	/* program the number of bytes to be transferred क्रम this descriptor. */
	acp_reg_ग_लिखो(sram_offset + 8,	acp_mmio, mmACP_SRBM_Targ_Idx_Addr);
	acp_reg_ग_लिखो(descr_info->xfer_val, acp_mmio, mmACP_SRBM_Targ_Idx_Data);
पूर्ण

अटल व्योम pre_config_reset(व्योम __iomem *acp_mmio, u16 ch_num)
अणु
	u32 dma_ctrl;
	पूर्णांक ret;

	/* clear the reset bit */
	dma_ctrl = acp_reg_पढ़ो(acp_mmio, mmACP_DMA_CNTL_0 + ch_num);
	dma_ctrl &= ~ACP_DMA_CNTL_0__DMAChRst_MASK;
	acp_reg_ग_लिखो(dma_ctrl, acp_mmio, mmACP_DMA_CNTL_0 + ch_num);
	/* check the reset bit beक्रमe programming configuration रेजिस्टरs */
	ret = पढ़ोl_poll_समयout(acp_mmio + ((mmACP_DMA_CNTL_0 + ch_num) * 4),
				 dma_ctrl,
				 !(dma_ctrl & ACP_DMA_CNTL_0__DMAChRst_MASK),
				 100, ACP_DMA_RESET_TIME);
	अगर (ret < 0)
		pr_err("Failed to clear reset of channel : %d\n", ch_num);
पूर्ण

/*
 * Initialize the DMA descriptor inक्रमmation क्रम transfer between
 * प्रणाली memory <-> ACP SRAM
 */
अटल व्योम set_acp_sysmem_dma_descriptors(व्योम __iomem *acp_mmio,
					   u32 size, पूर्णांक direction,
					   u32 pte_offset, u16 ch,
					   u32 sram_bank, u16 dma_dscr_idx,
					   u32 asic_type)
अणु
	u16 i;
	acp_dma_dscr_transfer_t dmadscr[NUM_DSCRS_PER_CHANNEL];

	क्रम (i = 0; i < NUM_DSCRS_PER_CHANNEL; i++) अणु
		dmadscr[i].xfer_val = 0;
		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
			dma_dscr_idx = dma_dscr_idx + i;
			dmadscr[i].dest = sram_bank + (i * (size / 2));
			dmadscr[i].src = ACP_INTERNAL_APERTURE_WINDOW_0_ADDRESS
				+ (pte_offset * SZ_4K) + (i * (size / 2));
			चयन (asic_type) अणु
			हाल CHIP_STONEY:
				dmadscr[i].xfer_val |=
				(ACP_DMA_ATTR_DAGB_GARLIC_TO_SHAREDMEM  << 16) |
				(size / 2);
				अवरोध;
			शेष:
				dmadscr[i].xfer_val |=
				(ACP_DMA_ATTR_DAGB_ONION_TO_SHAREDMEM  << 16) |
				(size / 2);
			पूर्ण
		पूर्ण अन्यथा अणु
			dma_dscr_idx = dma_dscr_idx + i;
			dmadscr[i].src = sram_bank + (i * (size / 2));
			dmadscr[i].dest =
			ACP_INTERNAL_APERTURE_WINDOW_0_ADDRESS +
			(pte_offset * SZ_4K) + (i * (size / 2));
			चयन (asic_type) अणु
			हाल CHIP_STONEY:
				dmadscr[i].xfer_val |=
				(ACP_DMA_ATTR_SHARED_MEM_TO_DAGB_GARLIC << 16) |
				(size / 2);
				अवरोध;
			शेष:
				dmadscr[i].xfer_val |=
				(ACP_DMA_ATTR_SHAREDMEM_TO_DAGB_ONION << 16) |
				(size / 2);
			पूर्ण
		पूर्ण
		config_dma_descriptor_in_sram(acp_mmio, dma_dscr_idx,
					      &dmadscr[i]);
	पूर्ण
	pre_config_reset(acp_mmio, ch);
	config_acp_dma_channel(acp_mmio, ch,
			       dma_dscr_idx - 1,
			       NUM_DSCRS_PER_CHANNEL,
			       ACP_DMA_PRIORITY_LEVEL_NORMAL);
पूर्ण

/*
 * Initialize the DMA descriptor inक्रमmation क्रम transfer between
 * ACP SRAM <-> I2S
 */
अटल व्योम set_acp_to_i2s_dma_descriptors(व्योम __iomem *acp_mmio, u32 size,
					   पूर्णांक direction, u32 sram_bank,
					   u16 destination, u16 ch,
					   u16 dma_dscr_idx, u32 asic_type)
अणु
	u16 i;
	acp_dma_dscr_transfer_t dmadscr[NUM_DSCRS_PER_CHANNEL];

	क्रम (i = 0; i < NUM_DSCRS_PER_CHANNEL; i++) अणु
		dmadscr[i].xfer_val = 0;
		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
			dma_dscr_idx = dma_dscr_idx + i;
			dmadscr[i].src = sram_bank  + (i * (size / 2));
			/* dmadscr[i].dest is unused by hardware. */
			dmadscr[i].dest = 0;
			dmadscr[i].xfer_val |= BIT(22) | (destination << 16) |
						(size / 2);
		पूर्ण अन्यथा अणु
			dma_dscr_idx = dma_dscr_idx + i;
			/* dmadscr[i].src is unused by hardware. */
			dmadscr[i].src = 0;
			dmadscr[i].dest =
				 sram_bank + (i * (size / 2));
			dmadscr[i].xfer_val |= BIT(22) |
				(destination << 16) | (size / 2);
		पूर्ण
		config_dma_descriptor_in_sram(acp_mmio, dma_dscr_idx,
					      &dmadscr[i]);
	पूर्ण
	pre_config_reset(acp_mmio, ch);
	/* Configure the DMA channel with the above descriptore */
	config_acp_dma_channel(acp_mmio, ch, dma_dscr_idx - 1,
			       NUM_DSCRS_PER_CHANNEL,
			       ACP_DMA_PRIORITY_LEVEL_NORMAL);
पूर्ण

/* Create page table entries in ACP SRAM क्रम the allocated memory */
अटल व्योम acp_pte_config(व्योम __iomem *acp_mmio, dma_addr_t addr,
			   u16 num_of_pages, u32 pte_offset)
अणु
	u16 page_idx;
	u32 low;
	u32 high;
	u32 offset;

	offset	= ACP_DAGB_GRP_SRBM_SRAM_BASE_OFFSET + (pte_offset * 8);
	क्रम (page_idx = 0; page_idx < (num_of_pages); page_idx++) अणु
		/* Load the low address of page पूर्णांक ACP SRAM through SRBM */
		acp_reg_ग_लिखो((offset + (page_idx * 8)),
			      acp_mmio, mmACP_SRBM_Targ_Idx_Addr);

		low = lower_32_bits(addr);
		high = upper_32_bits(addr);

		acp_reg_ग_लिखो(low, acp_mmio, mmACP_SRBM_Targ_Idx_Data);

		/* Load the High address of page पूर्णांक ACP SRAM through SRBM */
		acp_reg_ग_लिखो((offset + (page_idx * 8) + 4),
			      acp_mmio, mmACP_SRBM_Targ_Idx_Addr);

		/* page enable in ACP */
		high |= BIT(31);
		acp_reg_ग_लिखो(high, acp_mmio, mmACP_SRBM_Targ_Idx_Data);

		/* Move to next physically contiguos page */
		addr += PAGE_SIZE;
	पूर्ण
पूर्ण

अटल व्योम config_acp_dma(व्योम __iomem *acp_mmio,
			   काष्ठा audio_substream_data *rtd,
			   u32 asic_type)
अणु
	u16 ch_acp_sysmem, ch_acp_i2s;

	acp_pte_config(acp_mmio, rtd->dma_addr, rtd->num_of_pages,
		       rtd->pte_offset);

	अगर (rtd->direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ch_acp_sysmem = rtd->ch1;
		ch_acp_i2s = rtd->ch2;
	पूर्ण अन्यथा अणु
		ch_acp_i2s = rtd->ch1;
		ch_acp_sysmem = rtd->ch2;
	पूर्ण
	/* Configure System memory <-> ACP SRAM DMA descriptors */
	set_acp_sysmem_dma_descriptors(acp_mmio, rtd->size,
				       rtd->direction, rtd->pte_offset,
				       ch_acp_sysmem, rtd->sram_bank,
				       rtd->dma_dscr_idx_1, asic_type);
	/* Configure ACP SRAM <-> I2S DMA descriptors */
	set_acp_to_i2s_dma_descriptors(acp_mmio, rtd->size,
				       rtd->direction, rtd->sram_bank,
				       rtd->destination, ch_acp_i2s,
				       rtd->dma_dscr_idx_2, asic_type);
पूर्ण

अटल व्योम acp_dma_cap_channel_enable(व्योम __iomem *acp_mmio,
				       u16 cap_channel)
अणु
	u32 val, ch_reg, imr_reg, res_reg;

	चयन (cap_channel) अणु
	हाल CAP_CHANNEL1:
		ch_reg = mmACP_I2SMICSP_RER1;
		res_reg = mmACP_I2SMICSP_RCR1;
		imr_reg = mmACP_I2SMICSP_IMR1;
		अवरोध;
	हाल CAP_CHANNEL0:
	शेष:
		ch_reg = mmACP_I2SMICSP_RER0;
		res_reg = mmACP_I2SMICSP_RCR0;
		imr_reg = mmACP_I2SMICSP_IMR0;
		अवरोध;
	पूर्ण
	val = acp_reg_पढ़ो(acp_mmio,
			   mmACP_I2S_16BIT_RESOLUTION_EN);
	अगर (val & ACP_I2S_MIC_16BIT_RESOLUTION_EN) अणु
		acp_reg_ग_लिखो(0x0, acp_mmio, ch_reg);
		/* Set 16bit resolution on capture */
		acp_reg_ग_लिखो(0x2, acp_mmio, res_reg);
	पूर्ण
	val = acp_reg_पढ़ो(acp_mmio, imr_reg);
	val &= ~ACP_I2SMICSP_IMR1__I2SMICSP_RXDAM_MASK;
	val &= ~ACP_I2SMICSP_IMR1__I2SMICSP_RXFOM_MASK;
	acp_reg_ग_लिखो(val, acp_mmio, imr_reg);
	acp_reg_ग_लिखो(0x1, acp_mmio, ch_reg);
पूर्ण

अटल व्योम acp_dma_cap_channel_disable(व्योम __iomem *acp_mmio,
					u16 cap_channel)
अणु
	u32 val, ch_reg, imr_reg;

	चयन (cap_channel) अणु
	हाल CAP_CHANNEL1:
		imr_reg = mmACP_I2SMICSP_IMR1;
		ch_reg = mmACP_I2SMICSP_RER1;
		अवरोध;
	हाल CAP_CHANNEL0:
	शेष:
		imr_reg = mmACP_I2SMICSP_IMR0;
		ch_reg = mmACP_I2SMICSP_RER0;
		अवरोध;
	पूर्ण
	val = acp_reg_पढ़ो(acp_mmio, imr_reg);
	val |= ACP_I2SMICSP_IMR1__I2SMICSP_RXDAM_MASK;
	val |= ACP_I2SMICSP_IMR1__I2SMICSP_RXFOM_MASK;
	acp_reg_ग_लिखो(val, acp_mmio, imr_reg);
	acp_reg_ग_लिखो(0x0, acp_mmio, ch_reg);
पूर्ण

/* Start a given DMA channel transfer */
अटल व्योम acp_dma_start(व्योम __iomem *acp_mmio, u16 ch_num, bool is_circular)
अणु
	u32 dma_ctrl;

	/* पढ़ो the dma control रेजिस्टर and disable the channel run field */
	dma_ctrl = acp_reg_पढ़ो(acp_mmio, mmACP_DMA_CNTL_0 + ch_num);

	/* Invalidating the DAGB cache */
	acp_reg_ग_लिखो(1, acp_mmio, mmACP_DAGB_ATU_CTRL);

	/*
	 * configure the DMA channel and start the DMA transfer
	 * set dmachrun bit to start the transfer and enable the
	 * पूर्णांकerrupt on completion of the dma transfer
	 */
	dma_ctrl |= ACP_DMA_CNTL_0__DMAChRun_MASK;

	चयन (ch_num) अणु
	हाल ACP_TO_I2S_DMA_CH_NUM:
	हाल I2S_TO_ACP_DMA_CH_NUM:
	हाल ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM:
	हाल I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM:
		dma_ctrl |= ACP_DMA_CNTL_0__DMAChIOCEn_MASK;
		अवरोध;
	शेष:
		dma_ctrl &= ~ACP_DMA_CNTL_0__DMAChIOCEn_MASK;
		अवरोध;
	पूर्ण

	/* enable क्रम ACP to SRAM DMA channel */
	अगर (is_circular == true)
		dma_ctrl |= ACP_DMA_CNTL_0__Circular_DMA_En_MASK;
	अन्यथा
		dma_ctrl &= ~ACP_DMA_CNTL_0__Circular_DMA_En_MASK;

	acp_reg_ग_लिखो(dma_ctrl, acp_mmio, mmACP_DMA_CNTL_0 + ch_num);
पूर्ण

/* Stop a given DMA channel transfer */
अटल पूर्णांक acp_dma_stop(व्योम __iomem *acp_mmio, u8 ch_num)
अणु
	u32 dma_ctrl;
	u32 dma_ch_sts;
	u32 count = ACP_DMA_RESET_TIME;

	dma_ctrl = acp_reg_पढ़ो(acp_mmio, mmACP_DMA_CNTL_0 + ch_num);

	/*
	 * clear the dma control रेजिस्टर fields beक्रमe writing zero
	 * in reset bit
	 */
	dma_ctrl &= ~ACP_DMA_CNTL_0__DMAChRun_MASK;
	dma_ctrl &= ~ACP_DMA_CNTL_0__DMAChIOCEn_MASK;

	acp_reg_ग_लिखो(dma_ctrl, acp_mmio, mmACP_DMA_CNTL_0 + ch_num);
	dma_ch_sts = acp_reg_पढ़ो(acp_mmio, mmACP_DMA_CH_STS);

	अगर (dma_ch_sts & BIT(ch_num)) अणु
		/*
		 * set the reset bit क्रम this channel to stop the dma
		 *  transfer
		 */
		dma_ctrl |= ACP_DMA_CNTL_0__DMAChRst_MASK;
		acp_reg_ग_लिखो(dma_ctrl, acp_mmio, mmACP_DMA_CNTL_0 + ch_num);
	पूर्ण

	/* check the channel status bit क्रम some समय and वापस the status */
	जबतक (true) अणु
		dma_ch_sts = acp_reg_पढ़ो(acp_mmio, mmACP_DMA_CH_STS);
		अगर (!(dma_ch_sts & BIT(ch_num))) अणु
			/*
			 * clear the reset flag after successfully stopping
			 * the dma transfer and अवरोध from the loop
			 */
			dma_ctrl &= ~ACP_DMA_CNTL_0__DMAChRst_MASK;

			acp_reg_ग_लिखो(dma_ctrl, acp_mmio, mmACP_DMA_CNTL_0
				      + ch_num);
			अवरोध;
		पूर्ण
		अगर (--count == 0) अणु
			pr_err("Failed to stop ACP DMA channel : %d\n", ch_num);
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(100);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम acp_set_sram_bank_state(व्योम __iomem *acp_mmio, u16 bank,
				    bool घातer_on)
अणु
	u32 val, req_reg, sts_reg, sts_reg_mask;
	u32 loops = 1000;

	अगर (bank < 32) अणु
		req_reg = mmACP_MEM_SHUT_DOWN_REQ_LO;
		sts_reg = mmACP_MEM_SHUT_DOWN_STS_LO;
		sts_reg_mask = 0xFFFFFFFF;

	पूर्ण अन्यथा अणु
		bank -= 32;
		req_reg = mmACP_MEM_SHUT_DOWN_REQ_HI;
		sts_reg = mmACP_MEM_SHUT_DOWN_STS_HI;
		sts_reg_mask = 0x0000FFFF;
	पूर्ण

	val = acp_reg_पढ़ो(acp_mmio, req_reg);
	अगर (val & (1 << bank)) अणु
		/* bank is in off state */
		अगर (घातer_on == true)
			/* request to on */
			val &= ~(1 << bank);
		अन्यथा
			/* request to off */
			वापस;
	पूर्ण अन्यथा अणु
		/* bank is in on state */
		अगर (घातer_on == false)
			/* request to off */
			val |= 1 << bank;
		अन्यथा
			/* request to on */
			वापस;
	पूर्ण
	acp_reg_ग_लिखो(val, acp_mmio, req_reg);

	जबतक (acp_reg_पढ़ो(acp_mmio, sts_reg) != sts_reg_mask) अणु
		अगर (!loops--) अणु
			pr_err("ACP SRAM bank %d state change failed\n", bank);
			अवरोध;
		पूर्ण
		cpu_relax();
	पूर्ण
पूर्ण

/* Initialize and bring ACP hardware to शेष state. */
अटल पूर्णांक acp_init(व्योम __iomem *acp_mmio, u32 asic_type)
अणु
	u16 bank;
	u32 val, count, sram_pte_offset;

	/* Assert Soft reset of ACP */
	val = acp_reg_पढ़ो(acp_mmio, mmACP_SOFT_RESET);

	val |= ACP_SOFT_RESET__SoftResetAud_MASK;
	acp_reg_ग_लिखो(val, acp_mmio, mmACP_SOFT_RESET);

	count = ACP_SOFT_RESET_DONE_TIME_OUT_VALUE;
	जबतक (true) अणु
		val = acp_reg_पढ़ो(acp_mmio, mmACP_SOFT_RESET);
		अगर (ACP_SOFT_RESET__SoftResetAudDone_MASK ==
		    (val & ACP_SOFT_RESET__SoftResetAudDone_MASK))
			अवरोध;
		अगर (--count == 0) अणु
			pr_err("Failed to reset ACP\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(100);
	पूर्ण

	/* Enable घड़ी to ACP and रुको until the घड़ी is enabled */
	val = acp_reg_पढ़ो(acp_mmio, mmACP_CONTROL);
	val = val | ACP_CONTROL__ClkEn_MASK;
	acp_reg_ग_लिखो(val, acp_mmio, mmACP_CONTROL);

	count = ACP_CLOCK_EN_TIME_OUT_VALUE;

	जबतक (true) अणु
		val = acp_reg_पढ़ो(acp_mmio, mmACP_STATUS);
		अगर (val & (u32)0x1)
			अवरोध;
		अगर (--count == 0) अणु
			pr_err("Failed to reset ACP\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(100);
	पूर्ण

	/* Deनिश्चित the SOFT RESET flags */
	val = acp_reg_पढ़ो(acp_mmio, mmACP_SOFT_RESET);
	val &= ~ACP_SOFT_RESET__SoftResetAud_MASK;
	acp_reg_ग_लिखो(val, acp_mmio, mmACP_SOFT_RESET);

	/* For BT instance change pins from UART to BT */
	अगर (!bt_uart_enable) अणु
		val = acp_reg_पढ़ो(acp_mmio, mmACP_BT_UART_PAD_SEL);
		val |= ACP_BT_UART_PAD_SELECT_MASK;
		acp_reg_ग_लिखो(val, acp_mmio, mmACP_BT_UART_PAD_SEL);
	पूर्ण

	/* initiailize Onion control DAGB रेजिस्टर */
	acp_reg_ग_लिखो(ACP_ONION_CNTL_DEFAULT, acp_mmio,
		      mmACP_AXI2DAGB_ONION_CNTL);

	/* initiailize Garlic control DAGB रेजिस्टरs */
	acp_reg_ग_लिखो(ACP_GARLIC_CNTL_DEFAULT, acp_mmio,
		      mmACP_AXI2DAGB_GARLIC_CNTL);

	sram_pte_offset = ACP_DAGB_GRP_SRAM_BASE_ADDRESS |
			ACP_DAGB_BASE_ADDR_GRP_1__AXI2DAGBSnoopSel_MASK |
			ACP_DAGB_BASE_ADDR_GRP_1__AXI2DAGBTargetMemSel_MASK |
			ACP_DAGB_BASE_ADDR_GRP_1__AXI2DAGBGrpEnable_MASK;
	acp_reg_ग_लिखो(sram_pte_offset,  acp_mmio, mmACP_DAGB_BASE_ADDR_GRP_1);
	acp_reg_ग_लिखो(ACP_PAGE_SIZE_4K_ENABLE, acp_mmio,
		      mmACP_DAGB_PAGE_SIZE_GRP_1);

	acp_reg_ग_लिखो(ACP_SRAM_BASE_ADDRESS, acp_mmio,
		      mmACP_DMA_DESC_BASE_ADDR);

	/* Num of descriptiors in SRAM 0x4, means 256 descriptors;(64 * 4) */
	acp_reg_ग_लिखो(0x4, acp_mmio, mmACP_DMA_DESC_MAX_NUM_DSCR);
	acp_reg_ग_लिखो(ACP_EXTERNAL_INTR_CNTL__DMAIOCMask_MASK,
		      acp_mmio, mmACP_EXTERNAL_INTR_CNTL);

       /*
	* When ACP_TILE_P1 is turned on, all SRAM banks get turned on.
	* Now, turn off all of them. This can't be done in 'poweron' of
	* ACP pm करोमुख्य, as this requires ACP to be initialized.
	* For Stoney, Memory gating is disabled,i.e SRAM Banks
	* won't be turned off. The शेष state क्रम SRAM banks is ON.
	* Setting SRAM bank state code skipped क्रम STONEY platक्रमm.
	*/
	अगर (asic_type != CHIP_STONEY) अणु
		क्रम (bank = 1; bank < 48; bank++)
			acp_set_sram_bank_state(acp_mmio, bank, false);
	पूर्ण
	वापस 0;
पूर्ण

/* Deinitialize ACP */
अटल पूर्णांक acp_deinit(व्योम __iomem *acp_mmio)
अणु
	u32 val;
	u32 count;

	/* Assert Soft reset of ACP */
	val = acp_reg_पढ़ो(acp_mmio, mmACP_SOFT_RESET);

	val |= ACP_SOFT_RESET__SoftResetAud_MASK;
	acp_reg_ग_लिखो(val, acp_mmio, mmACP_SOFT_RESET);

	count = ACP_SOFT_RESET_DONE_TIME_OUT_VALUE;
	जबतक (true) अणु
		val = acp_reg_पढ़ो(acp_mmio, mmACP_SOFT_RESET);
		अगर (ACP_SOFT_RESET__SoftResetAudDone_MASK ==
		    (val & ACP_SOFT_RESET__SoftResetAudDone_MASK))
			अवरोध;
		अगर (--count == 0) अणु
			pr_err("Failed to reset ACP\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(100);
	पूर्ण
	/* Disable ACP घड़ी */
	val = acp_reg_पढ़ो(acp_mmio, mmACP_CONTROL);
	val &= ~ACP_CONTROL__ClkEn_MASK;
	acp_reg_ग_लिखो(val, acp_mmio, mmACP_CONTROL);

	count = ACP_CLOCK_EN_TIME_OUT_VALUE;

	जबतक (true) अणु
		val = acp_reg_पढ़ो(acp_mmio, mmACP_STATUS);
		अगर (!(val & (u32)0x1))
			अवरोध;
		अगर (--count == 0) अणु
			pr_err("Failed to reset ACP\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(100);
	पूर्ण
	वापस 0;
पूर्ण

/* ACP DMA irq handler routine क्रम playback, capture useहालs */
अटल irqवापस_t dma_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	u16 dscr_idx;
	u32 पूर्णांकr_flag, ext_पूर्णांकr_status;
	काष्ठा audio_drv_data *irq_data;
	व्योम __iomem *acp_mmio;
	काष्ठा device *dev = arg;
	bool valid_irq = false;

	irq_data = dev_get_drvdata(dev);
	acp_mmio = irq_data->acp_mmio;

	ext_पूर्णांकr_status = acp_reg_पढ़ो(acp_mmio, mmACP_EXTERNAL_INTR_STAT);
	पूर्णांकr_flag = (((ext_पूर्णांकr_status &
		      ACP_EXTERNAL_INTR_STAT__DMAIOCStat_MASK) >>
		     ACP_EXTERNAL_INTR_STAT__DMAIOCStat__SHIFT));

	अगर ((पूर्णांकr_flag & BIT(ACP_TO_I2S_DMA_CH_NUM)) != 0) अणु
		valid_irq = true;
		snd_pcm_period_elapsed(irq_data->play_i2ssp_stream);
		acp_reg_ग_लिखो((पूर्णांकr_flag & BIT(ACP_TO_I2S_DMA_CH_NUM)) << 16,
			      acp_mmio, mmACP_EXTERNAL_INTR_STAT);
	पूर्ण

	अगर ((पूर्णांकr_flag & BIT(ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM)) != 0) अणु
		valid_irq = true;
		snd_pcm_period_elapsed(irq_data->play_i2sbt_stream);
		acp_reg_ग_लिखो((पूर्णांकr_flag &
			      BIT(ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM)) << 16,
			      acp_mmio, mmACP_EXTERNAL_INTR_STAT);
	पूर्ण

	अगर ((पूर्णांकr_flag & BIT(I2S_TO_ACP_DMA_CH_NUM)) != 0) अणु
		valid_irq = true;
		अगर (acp_reg_पढ़ो(acp_mmio, mmACP_DMA_CUR_DSCR_14) ==
				CAPTURE_START_DMA_DESCR_CH15)
			dscr_idx = CAPTURE_END_DMA_DESCR_CH14;
		अन्यथा
			dscr_idx = CAPTURE_START_DMA_DESCR_CH14;
		config_acp_dma_channel(acp_mmio, ACP_TO_SYSRAM_CH_NUM, dscr_idx,
				       1, 0);
		acp_dma_start(acp_mmio, ACP_TO_SYSRAM_CH_NUM, false);

		snd_pcm_period_elapsed(irq_data->capture_i2ssp_stream);
		acp_reg_ग_लिखो((पूर्णांकr_flag & BIT(I2S_TO_ACP_DMA_CH_NUM)) << 16,
			      acp_mmio, mmACP_EXTERNAL_INTR_STAT);
	पूर्ण

	अगर ((पूर्णांकr_flag & BIT(I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM)) != 0) अणु
		valid_irq = true;
		अगर (acp_reg_पढ़ो(acp_mmio, mmACP_DMA_CUR_DSCR_10) ==
			CAPTURE_START_DMA_DESCR_CH11)
			dscr_idx = CAPTURE_END_DMA_DESCR_CH10;
		अन्यथा
			dscr_idx = CAPTURE_START_DMA_DESCR_CH10;
		config_acp_dma_channel(acp_mmio,
				       ACP_TO_SYSRAM_BT_INSTANCE_CH_NUM,
				       dscr_idx, 1, 0);
		acp_dma_start(acp_mmio, ACP_TO_SYSRAM_BT_INSTANCE_CH_NUM,
			      false);

		snd_pcm_period_elapsed(irq_data->capture_i2sbt_stream);
		acp_reg_ग_लिखो((पूर्णांकr_flag &
			      BIT(I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM)) << 16,
			      acp_mmio, mmACP_EXTERNAL_INTR_STAT);
	पूर्ण

	अगर (valid_irq)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक acp_dma_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	u16 bank;
	पूर्णांक ret = 0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा audio_drv_data *पूर्णांकr_data = dev_get_drvdata(component->dev);
	काष्ठा audio_substream_data *adata =
		kzalloc(माप(काष्ठा audio_substream_data), GFP_KERNEL);
	अगर (!adata)
		वापस -ENOMEM;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (पूर्णांकr_data->asic_type) अणु
		हाल CHIP_STONEY:
			runसमय->hw = acp_st_pcm_hardware_playback;
			अवरोध;
		शेष:
			runसमय->hw = acp_pcm_hardware_playback;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (पूर्णांकr_data->asic_type) अणु
		हाल CHIP_STONEY:
			runसमय->hw = acp_st_pcm_hardware_capture;
			अवरोध;
		शेष:
			runसमय->hw = acp_pcm_hardware_capture;
		पूर्ण
	पूर्ण

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0) अणु
		dev_err(component->dev, "set integer constraint failed\n");
		kमुक्त(adata);
		वापस ret;
	पूर्ण

	adata->acp_mmio = पूर्णांकr_data->acp_mmio;
	runसमय->निजी_data = adata;

	/*
	 * Enable ACP irq, when neither playback or capture streams are
	 * active by the समय when a new stream is being खोलोed.
	 * This enablement is not required क्रम another stream, अगर current
	 * stream is not बंदd
	 */
	अगर (!पूर्णांकr_data->play_i2ssp_stream && !पूर्णांकr_data->capture_i2ssp_stream &&
	    !पूर्णांकr_data->play_i2sbt_stream && !पूर्णांकr_data->capture_i2sbt_stream)
		acp_reg_ग_लिखो(1, adata->acp_mmio, mmACP_EXTERNAL_INTR_ENB);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		/*
		 * For Stoney, Memory gating is disabled,i.e SRAM Banks
		 * won't be turned off. The शेष state क्रम SRAM banks is ON.
		 * Setting SRAM bank state code skipped क्रम STONEY platक्रमm.
		 */
		अगर (पूर्णांकr_data->asic_type != CHIP_STONEY) अणु
			क्रम (bank = 1; bank <= 4; bank++)
				acp_set_sram_bank_state(पूर्णांकr_data->acp_mmio,
							bank, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (पूर्णांकr_data->asic_type != CHIP_STONEY) अणु
			क्रम (bank = 5; bank <= 8; bank++)
				acp_set_sram_bank_state(पूर्णांकr_data->acp_mmio,
							bank, true);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acp_dma_hw_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	uपूर्णांक64_t size;
	u32 val = 0;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा audio_substream_data *rtd;
	काष्ठा snd_soc_pcm_runसमय *prtd = asoc_substream_to_rtd(substream);
	काष्ठा audio_drv_data *adata = dev_get_drvdata(component->dev);
	काष्ठा snd_soc_card *card = prtd->card;
	काष्ठा acp_platक्रमm_info *pinfo = snd_soc_card_get_drvdata(card);

	runसमय = substream->runसमय;
	rtd = runसमय->निजी_data;

	अगर (WARN_ON(!rtd))
		वापस -EINVAL;

	अगर (pinfo) अणु
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			rtd->i2s_instance = pinfo->play_i2s_instance;
		पूर्ण अन्यथा अणु
			rtd->i2s_instance = pinfo->cap_i2s_instance;
			rtd->capture_channel = pinfo->capture_channel;
		पूर्ण
	पूर्ण
	अगर (adata->asic_type == CHIP_STONEY) अणु
		val = acp_reg_पढ़ो(adata->acp_mmio,
				   mmACP_I2S_16BIT_RESOLUTION_EN);
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			चयन (rtd->i2s_instance) अणु
			हाल I2S_BT_INSTANCE:
				val |= ACP_I2S_BT_16BIT_RESOLUTION_EN;
				अवरोध;
			हाल I2S_SP_INSTANCE:
			शेष:
				val |= ACP_I2S_SP_16BIT_RESOLUTION_EN;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (rtd->i2s_instance) अणु
			हाल I2S_BT_INSTANCE:
				val |= ACP_I2S_BT_16BIT_RESOLUTION_EN;
				अवरोध;
			हाल I2S_SP_INSTANCE:
			शेष:
				val |= ACP_I2S_MIC_16BIT_RESOLUTION_EN;
			पूर्ण
		पूर्ण
		acp_reg_ग_लिखो(val, adata->acp_mmio,
			      mmACP_I2S_16BIT_RESOLUTION_EN);
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			rtd->pte_offset = ACP_ST_BT_PLAYBACK_PTE_OFFSET;
			rtd->ch1 = SYSRAM_TO_ACP_BT_INSTANCE_CH_NUM;
			rtd->ch2 = ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM;
			rtd->sram_bank = ACP_SRAM_BANK_3_ADDRESS;
			rtd->destination = TO_BLUETOOTH;
			rtd->dma_dscr_idx_1 = PLAYBACK_START_DMA_DESCR_CH8;
			rtd->dma_dscr_idx_2 = PLAYBACK_START_DMA_DESCR_CH9;
			rtd->byte_cnt_high_reg_offset =
					mmACP_I2S_BT_TRANSMIT_BYTE_CNT_HIGH;
			rtd->byte_cnt_low_reg_offset =
					mmACP_I2S_BT_TRANSMIT_BYTE_CNT_LOW;
			adata->play_i2sbt_stream = substream;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			चयन (adata->asic_type) अणु
			हाल CHIP_STONEY:
				rtd->pte_offset = ACP_ST_PLAYBACK_PTE_OFFSET;
				अवरोध;
			शेष:
				rtd->pte_offset = ACP_PLAYBACK_PTE_OFFSET;
			पूर्ण
			rtd->ch1 = SYSRAM_TO_ACP_CH_NUM;
			rtd->ch2 = ACP_TO_I2S_DMA_CH_NUM;
			rtd->sram_bank = ACP_SRAM_BANK_1_ADDRESS;
			rtd->destination = TO_ACP_I2S_1;
			rtd->dma_dscr_idx_1 = PLAYBACK_START_DMA_DESCR_CH12;
			rtd->dma_dscr_idx_2 = PLAYBACK_START_DMA_DESCR_CH13;
			rtd->byte_cnt_high_reg_offset =
					mmACP_I2S_TRANSMIT_BYTE_CNT_HIGH;
			rtd->byte_cnt_low_reg_offset =
					mmACP_I2S_TRANSMIT_BYTE_CNT_LOW;
			adata->play_i2ssp_stream = substream;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			rtd->pte_offset = ACP_ST_BT_CAPTURE_PTE_OFFSET;
			rtd->ch1 = I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM;
			rtd->ch2 = ACP_TO_SYSRAM_BT_INSTANCE_CH_NUM;
			rtd->sram_bank = ACP_SRAM_BANK_4_ADDRESS;
			rtd->destination = FROM_BLUETOOTH;
			rtd->dma_dscr_idx_1 = CAPTURE_START_DMA_DESCR_CH10;
			rtd->dma_dscr_idx_2 = CAPTURE_START_DMA_DESCR_CH11;
			rtd->byte_cnt_high_reg_offset =
					mmACP_I2S_BT_RECEIVE_BYTE_CNT_HIGH;
			rtd->byte_cnt_low_reg_offset =
					mmACP_I2S_BT_RECEIVE_BYTE_CNT_LOW;
			rtd->dma_curr_dscr = mmACP_DMA_CUR_DSCR_11;
			adata->capture_i2sbt_stream = substream;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			rtd->pte_offset = ACP_CAPTURE_PTE_OFFSET;
			rtd->ch1 = I2S_TO_ACP_DMA_CH_NUM;
			rtd->ch2 = ACP_TO_SYSRAM_CH_NUM;
			चयन (adata->asic_type) अणु
			हाल CHIP_STONEY:
				rtd->pte_offset = ACP_ST_CAPTURE_PTE_OFFSET;
				rtd->sram_bank = ACP_SRAM_BANK_2_ADDRESS;
				अवरोध;
			शेष:
				rtd->pte_offset = ACP_CAPTURE_PTE_OFFSET;
				rtd->sram_bank = ACP_SRAM_BANK_5_ADDRESS;
			पूर्ण
			rtd->destination = FROM_ACP_I2S_1;
			rtd->dma_dscr_idx_1 = CAPTURE_START_DMA_DESCR_CH14;
			rtd->dma_dscr_idx_2 = CAPTURE_START_DMA_DESCR_CH15;
			rtd->byte_cnt_high_reg_offset =
					mmACP_I2S_RECEIVED_BYTE_CNT_HIGH;
			rtd->byte_cnt_low_reg_offset =
					mmACP_I2S_RECEIVED_BYTE_CNT_LOW;
			rtd->dma_curr_dscr = mmACP_DMA_CUR_DSCR_15;
			adata->capture_i2ssp_stream = substream;
		पूर्ण
	पूर्ण

	size = params_buffer_bytes(params);

	acp_set_sram_bank_state(rtd->acp_mmio, 0, true);
	/* Save क्रम runसमय निजी data */
	rtd->dma_addr = substream->dma_buffer.addr;
	rtd->order = get_order(size);

	/* Fill the page table entries in ACP SRAM */
	rtd->size = size;
	rtd->num_of_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	rtd->direction = substream->stream;

	config_acp_dma(rtd->acp_mmio, rtd, adata->asic_type);
	वापस 0;
पूर्ण

अटल u64 acp_get_byte_count(काष्ठा audio_substream_data *rtd)
अणु
	जोड़ acp_dma_count byte_count;

	byte_count.bcount.high = acp_reg_पढ़ो(rtd->acp_mmio,
					      rtd->byte_cnt_high_reg_offset);
	byte_count.bcount.low  = acp_reg_पढ़ो(rtd->acp_mmio,
					      rtd->byte_cnt_low_reg_offset);
	वापस byte_count.bytescount;
पूर्ण

अटल snd_pcm_uframes_t acp_dma_poपूर्णांकer(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	u32 buffersize;
	u32 pos = 0;
	u64 bytescount = 0;
	u16 dscr;
	u32 period_bytes, delay;

	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा audio_substream_data *rtd = runसमय->निजी_data;

	अगर (!rtd)
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		period_bytes = frames_to_bytes(runसमय, runसमय->period_size);
		bytescount = acp_get_byte_count(rtd);
		अगर (bytescount >= rtd->bytescount)
			bytescount -= rtd->bytescount;
		अगर (bytescount < period_bytes) अणु
			pos = 0;
		पूर्ण अन्यथा अणु
			dscr = acp_reg_पढ़ो(rtd->acp_mmio, rtd->dma_curr_dscr);
			अगर (dscr == rtd->dma_dscr_idx_1)
				pos = period_bytes;
			अन्यथा
				pos = 0;
		पूर्ण
		अगर (bytescount > 0) अणु
			delay = करो_भाग(bytescount, period_bytes);
			runसमय->delay = bytes_to_frames(runसमय, delay);
		पूर्ण
	पूर्ण अन्यथा अणु
		buffersize = frames_to_bytes(runसमय, runसमय->buffer_size);
		bytescount = acp_get_byte_count(rtd);
		अगर (bytescount > rtd->bytescount)
			bytescount -= rtd->bytescount;
		pos = करो_भाग(bytescount, buffersize);
	पूर्ण
	वापस bytes_to_frames(runसमय, pos);
पूर्ण

अटल पूर्णांक acp_dma_mmap(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस snd_pcm_lib_शेष_mmap(substream, vma);
पूर्ण

अटल पूर्णांक acp_dma_prepare(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा audio_substream_data *rtd = runसमय->निजी_data;
	u16 ch_acp_sysmem, ch_acp_i2s;

	अगर (!rtd)
		वापस -EINVAL;

	अगर (rtd->direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ch_acp_sysmem = rtd->ch1;
		ch_acp_i2s = rtd->ch2;
	पूर्ण अन्यथा अणु
		ch_acp_i2s = rtd->ch1;
		ch_acp_sysmem = rtd->ch2;
	पूर्ण
	config_acp_dma_channel(rtd->acp_mmio,
			       ch_acp_sysmem,
			       rtd->dma_dscr_idx_1,
			       NUM_DSCRS_PER_CHANNEL, 0);
	config_acp_dma_channel(rtd->acp_mmio,
			       ch_acp_i2s,
			       rtd->dma_dscr_idx_2,
			       NUM_DSCRS_PER_CHANNEL, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक acp_dma_trigger(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक ret;

	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा audio_substream_data *rtd = runसमय->निजी_data;

	अगर (!rtd)
		वापस -EINVAL;
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		rtd->bytescount = acp_get_byte_count(rtd);
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
			अगर (rtd->capture_channel == CAP_CHANNEL0) अणु
				acp_dma_cap_channel_disable(rtd->acp_mmio,
							    CAP_CHANNEL1);
				acp_dma_cap_channel_enable(rtd->acp_mmio,
							   CAP_CHANNEL0);
			पूर्ण
			अगर (rtd->capture_channel == CAP_CHANNEL1) अणु
				acp_dma_cap_channel_disable(rtd->acp_mmio,
							    CAP_CHANNEL0);
				acp_dma_cap_channel_enable(rtd->acp_mmio,
							   CAP_CHANNEL1);
			पूर्ण
			acp_dma_start(rtd->acp_mmio, rtd->ch1, true);
		पूर्ण अन्यथा अणु
			acp_dma_start(rtd->acp_mmio, rtd->ch1, true);
			acp_dma_start(rtd->acp_mmio, rtd->ch2, true);
		पूर्ण
		ret = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		acp_dma_stop(rtd->acp_mmio, rtd->ch2);
		ret = acp_dma_stop(rtd->acp_mmio, rtd->ch1);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक acp_dma_new(काष्ठा snd_soc_component *component,
		       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा audio_drv_data *adata = dev_get_drvdata(component->dev);
	काष्ठा device *parent = component->dev->parent;

	चयन (adata->asic_type) अणु
	हाल CHIP_STONEY:
		snd_pcm_set_managed_buffer_all(rtd->pcm,
					       SNDRV_DMA_TYPE_DEV,
					       parent,
					       ST_MIN_BUFFER,
					       ST_MAX_BUFFER);
		अवरोध;
	शेष:
		snd_pcm_set_managed_buffer_all(rtd->pcm,
					       SNDRV_DMA_TYPE_DEV,
					       parent,
					       MIN_BUFFER,
					       MAX_BUFFER);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acp_dma_बंद(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	u16 bank;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा audio_substream_data *rtd = runसमय->निजी_data;
	काष्ठा audio_drv_data *adata = dev_get_drvdata(component->dev);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			adata->play_i2sbt_stream = शून्य;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			adata->play_i2ssp_stream = शून्य;
			/*
			 * For Stoney, Memory gating is disabled,i.e SRAM Banks
			 * won't be turned off. The शेष state क्रम SRAM banks
			 * is ON.Setting SRAM bank state code skipped क्रम STONEY
			 * platक्रमm. Added condition checks क्रम Carrizo platक्रमm
			 * only.
			 */
			अगर (adata->asic_type != CHIP_STONEY) अणु
				क्रम (bank = 1; bank <= 4; bank++)
					acp_set_sram_bank_state(adata->acp_mmio,
								bank, false);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा  अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			adata->capture_i2sbt_stream = शून्य;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			adata->capture_i2ssp_stream = शून्य;
			अगर (adata->asic_type != CHIP_STONEY) अणु
				क्रम (bank = 5; bank <= 8; bank++)
					acp_set_sram_bank_state(adata->acp_mmio,
								bank, false);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Disable ACP irq, when the current stream is being बंदd and
	 * another stream is also not active.
	 */
	अगर (!adata->play_i2ssp_stream && !adata->capture_i2ssp_stream &&
	    !adata->play_i2sbt_stream && !adata->capture_i2sbt_stream)
		acp_reg_ग_लिखो(0, adata->acp_mmio, mmACP_EXTERNAL_INTR_ENB);
	kमुक्त(rtd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver acp_asoc_platक्रमm = अणु
	.name		= DRV_NAME,
	.खोलो		= acp_dma_खोलो,
	.बंद		= acp_dma_बंद,
	.hw_params	= acp_dma_hw_params,
	.trigger	= acp_dma_trigger,
	.poपूर्णांकer	= acp_dma_poपूर्णांकer,
	.mmap		= acp_dma_mmap,
	.prepare	= acp_dma_prepare,
	.pcm_स्थिरruct	= acp_dma_new,
पूर्ण;

अटल पूर्णांक acp_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक status;
	काष्ठा audio_drv_data *audio_drv_data;
	काष्ठा resource *res;
	स्थिर u32 *pdata = pdev->dev.platक्रमm_data;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "Missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	audio_drv_data = devm_kzalloc(&pdev->dev, माप(काष्ठा audio_drv_data),
				      GFP_KERNEL);
	अगर (!audio_drv_data)
		वापस -ENOMEM;

	audio_drv_data->acp_mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(audio_drv_data->acp_mmio))
		वापस PTR_ERR(audio_drv_data->acp_mmio);

	/*
	 * The following members माला_लो populated in device 'open'
	 * function. Till then पूर्णांकerrupts are disabled in 'acp_init'
	 * and device करोesn't generate any पूर्णांकerrupts.
	 */

	audio_drv_data->play_i2ssp_stream = शून्य;
	audio_drv_data->capture_i2ssp_stream = शून्य;
	audio_drv_data->play_i2sbt_stream = शून्य;
	audio_drv_data->capture_i2sbt_stream = शून्य;

	audio_drv_data->asic_type =  *pdata;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "IORESOURCE_IRQ FAILED\n");
		वापस -ENODEV;
	पूर्ण

	status = devm_request_irq(&pdev->dev, res->start, dma_irq_handler,
				  0, "ACP_IRQ", &pdev->dev);
	अगर (status) अणु
		dev_err(&pdev->dev, "ACP IRQ request failed\n");
		वापस status;
	पूर्ण

	dev_set_drvdata(&pdev->dev, audio_drv_data);

	/* Initialize the ACP */
	status = acp_init(audio_drv_data->acp_mmio, audio_drv_data->asic_type);
	अगर (status) अणु
		dev_err(&pdev->dev, "ACP Init failed status:%d\n", status);
		वापस status;
	पूर्ण

	status = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
						 &acp_asoc_platक्रमm, शून्य, 0);
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "Fail to register ALSA platform device\n");
		वापस status;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 10000);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	वापस status;
पूर्ण

अटल पूर्णांक acp_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक status;
	काष्ठा audio_drv_data *adata = dev_get_drvdata(&pdev->dev);

	status = acp_deinit(adata->acp_mmio);
	अगर (status)
		dev_err(&pdev->dev, "ACP Deinit failed status:%d\n", status);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक acp_pcm_resume(काष्ठा device *dev)
अणु
	u16 bank;
	पूर्णांक status;
	काष्ठा audio_substream_data *rtd;
	काष्ठा audio_drv_data *adata = dev_get_drvdata(dev);

	status = acp_init(adata->acp_mmio, adata->asic_type);
	अगर (status) अणु
		dev_err(dev, "ACP Init failed status:%d\n", status);
		वापस status;
	पूर्ण

	अगर (adata->play_i2ssp_stream && adata->play_i2ssp_stream->runसमय) अणु
		/*
		 * For Stoney, Memory gating is disabled,i.e SRAM Banks
		 * won't be turned off. The शेष state क्रम SRAM banks is ON.
		 * Setting SRAM bank state code skipped क्रम STONEY platक्रमm.
		 */
		अगर (adata->asic_type != CHIP_STONEY) अणु
			क्रम (bank = 1; bank <= 4; bank++)
				acp_set_sram_bank_state(adata->acp_mmio, bank,
							true);
		पूर्ण
		rtd = adata->play_i2ssp_stream->runसमय->निजी_data;
		config_acp_dma(adata->acp_mmio, rtd, adata->asic_type);
	पूर्ण
	अगर (adata->capture_i2ssp_stream &&
	    adata->capture_i2ssp_stream->runसमय) अणु
		अगर (adata->asic_type != CHIP_STONEY) अणु
			क्रम (bank = 5; bank <= 8; bank++)
				acp_set_sram_bank_state(adata->acp_mmio, bank,
							true);
		पूर्ण
		rtd =  adata->capture_i2ssp_stream->runसमय->निजी_data;
		config_acp_dma(adata->acp_mmio, rtd, adata->asic_type);
	पूर्ण
	अगर (adata->asic_type != CHIP_CARRIZO) अणु
		अगर (adata->play_i2sbt_stream &&
		    adata->play_i2sbt_stream->runसमय) अणु
			rtd = adata->play_i2sbt_stream->runसमय->निजी_data;
			config_acp_dma(adata->acp_mmio, rtd, adata->asic_type);
		पूर्ण
		अगर (adata->capture_i2sbt_stream &&
		    adata->capture_i2sbt_stream->runसमय) अणु
			rtd = adata->capture_i2sbt_stream->runसमय->निजी_data;
			config_acp_dma(adata->acp_mmio, rtd, adata->asic_type);
		पूर्ण
	पूर्ण
	acp_reg_ग_लिखो(1, adata->acp_mmio, mmACP_EXTERNAL_INTR_ENB);
	वापस 0;
पूर्ण

अटल पूर्णांक acp_pcm_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक status;
	काष्ठा audio_drv_data *adata = dev_get_drvdata(dev);

	status = acp_deinit(adata->acp_mmio);
	अगर (status)
		dev_err(dev, "ACP Deinit failed status:%d\n", status);
	acp_reg_ग_लिखो(0, adata->acp_mmio, mmACP_EXTERNAL_INTR_ENB);
	वापस 0;
पूर्ण

अटल पूर्णांक acp_pcm_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक status;
	काष्ठा audio_drv_data *adata = dev_get_drvdata(dev);

	status = acp_init(adata->acp_mmio, adata->asic_type);
	अगर (status) अणु
		dev_err(dev, "ACP Init failed status:%d\n", status);
		वापस status;
	पूर्ण
	acp_reg_ग_लिखो(1, adata->acp_mmio, mmACP_EXTERNAL_INTR_ENB);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops acp_pm_ops = अणु
	.resume = acp_pcm_resume,
	.runसमय_suspend = acp_pcm_runसमय_suspend,
	.runसमय_resume = acp_pcm_runसमय_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver acp_dma_driver = अणु
	.probe = acp_audio_probe,
	.हटाओ = acp_audio_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.pm = &acp_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(acp_dma_driver);

MODULE_AUTHOR("Vijendar.Mukunda@amd.com");
MODULE_AUTHOR("Maruthi.Bayyavarapu@amd.com");
MODULE_DESCRIPTION("AMD ACP PCM Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:"DRV_NAME);
