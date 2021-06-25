<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2012-2013 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __FSL_SAI_H
#घोषणा __FSL_SAI_H

#समावेश <sound/dmaengine_pcm.h>

#घोषणा FSL_SAI_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			 SNDRV_PCM_FMTBIT_S20_3LE |\
			 SNDRV_PCM_FMTBIT_S24_LE |\
			 SNDRV_PCM_FMTBIT_S32_LE)

/* SAI Register Map Register */
#घोषणा FSL_SAI_VERID	0x00 /* SAI Version ID Register */
#घोषणा FSL_SAI_PARAM	0x04 /* SAI Parameter Register */
#घोषणा FSL_SAI_TCSR(ofs)	(0x00 + ofs) /* SAI Transmit Control */
#घोषणा FSL_SAI_TCR1(ofs)	(0x04 + ofs) /* SAI Transmit Configuration 1 */
#घोषणा FSL_SAI_TCR2(ofs)	(0x08 + ofs) /* SAI Transmit Configuration 2 */
#घोषणा FSL_SAI_TCR3(ofs)	(0x0c + ofs) /* SAI Transmit Configuration 3 */
#घोषणा FSL_SAI_TCR4(ofs)	(0x10 + ofs) /* SAI Transmit Configuration 4 */
#घोषणा FSL_SAI_TCR5(ofs)	(0x14 + ofs) /* SAI Transmit Configuration 5 */
#घोषणा FSL_SAI_TDR0	0x20 /* SAI Transmit Data 0 */
#घोषणा FSL_SAI_TDR1	0x24 /* SAI Transmit Data 1 */
#घोषणा FSL_SAI_TDR2	0x28 /* SAI Transmit Data 2 */
#घोषणा FSL_SAI_TDR3	0x2C /* SAI Transmit Data 3 */
#घोषणा FSL_SAI_TDR4	0x30 /* SAI Transmit Data 4 */
#घोषणा FSL_SAI_TDR5	0x34 /* SAI Transmit Data 5 */
#घोषणा FSL_SAI_TDR6	0x38 /* SAI Transmit Data 6 */
#घोषणा FSL_SAI_TDR7	0x3C /* SAI Transmit Data 7 */
#घोषणा FSL_SAI_TFR0	0x40 /* SAI Transmit FIFO 0 */
#घोषणा FSL_SAI_TFR1	0x44 /* SAI Transmit FIFO 1 */
#घोषणा FSL_SAI_TFR2	0x48 /* SAI Transmit FIFO 2 */
#घोषणा FSL_SAI_TFR3	0x4C /* SAI Transmit FIFO 3 */
#घोषणा FSL_SAI_TFR4	0x50 /* SAI Transmit FIFO 4 */
#घोषणा FSL_SAI_TFR5	0x54 /* SAI Transmit FIFO 5 */
#घोषणा FSL_SAI_TFR6	0x58 /* SAI Transmit FIFO 6 */
#घोषणा FSL_SAI_TFR7	0x5C /* SAI Transmit FIFO 7 */
#घोषणा FSL_SAI_TMR	0x60 /* SAI Transmit Mask */
#घोषणा FSL_SAI_TTCTL	0x70 /* SAI Transmit Timestamp Control Register */
#घोषणा FSL_SAI_TTCTN	0x74 /* SAI Transmit Timestamp Counter Register */
#घोषणा FSL_SAI_TBCTN	0x78 /* SAI Transmit Bit Counter Register */
#घोषणा FSL_SAI_TTCAP	0x7C /* SAI Transmit Timestamp Capture */
#घोषणा FSL_SAI_RCSR(ofs)	(0x80 + ofs) /* SAI Receive Control */
#घोषणा FSL_SAI_RCR1(ofs)	(0x84 + ofs)/* SAI Receive Configuration 1 */
#घोषणा FSL_SAI_RCR2(ofs)	(0x88 + ofs) /* SAI Receive Configuration 2 */
#घोषणा FSL_SAI_RCR3(ofs)	(0x8c + ofs) /* SAI Receive Configuration 3 */
#घोषणा FSL_SAI_RCR4(ofs)	(0x90 + ofs) /* SAI Receive Configuration 4 */
#घोषणा FSL_SAI_RCR5(ofs)	(0x94 + ofs) /* SAI Receive Configuration 5 */
#घोषणा FSL_SAI_RDR0	0xa0 /* SAI Receive Data 0 */
#घोषणा FSL_SAI_RDR1	0xa4 /* SAI Receive Data 1 */
#घोषणा FSL_SAI_RDR2	0xa8 /* SAI Receive Data 2 */
#घोषणा FSL_SAI_RDR3	0xac /* SAI Receive Data 3 */
#घोषणा FSL_SAI_RDR4	0xb0 /* SAI Receive Data 4 */
#घोषणा FSL_SAI_RDR5	0xb4 /* SAI Receive Data 5 */
#घोषणा FSL_SAI_RDR6	0xb8 /* SAI Receive Data 6 */
#घोषणा FSL_SAI_RDR7	0xbc /* SAI Receive Data 7 */
#घोषणा FSL_SAI_RFR0	0xc0 /* SAI Receive FIFO 0 */
#घोषणा FSL_SAI_RFR1	0xc4 /* SAI Receive FIFO 1 */
#घोषणा FSL_SAI_RFR2	0xc8 /* SAI Receive FIFO 2 */
#घोषणा FSL_SAI_RFR3	0xcc /* SAI Receive FIFO 3 */
#घोषणा FSL_SAI_RFR4	0xd0 /* SAI Receive FIFO 4 */
#घोषणा FSL_SAI_RFR5	0xd4 /* SAI Receive FIFO 5 */
#घोषणा FSL_SAI_RFR6	0xd8 /* SAI Receive FIFO 6 */
#घोषणा FSL_SAI_RFR7	0xdc /* SAI Receive FIFO 7 */
#घोषणा FSL_SAI_RMR	0xe0 /* SAI Receive Mask */
#घोषणा FSL_SAI_RTCTL	0xf0 /* SAI Receive Timestamp Control Register */
#घोषणा FSL_SAI_RTCTN	0xf4 /* SAI Receive Timestamp Counter Register */
#घोषणा FSL_SAI_RBCTN	0xf8 /* SAI Receive Bit Counter Register */
#घोषणा FSL_SAI_RTCAP	0xfc /* SAI Receive Timestamp Capture */

#घोषणा FSL_SAI_MCTL	0x100 /* SAI MCLK Control Register */
#घोषणा FSL_SAI_MDIV	0x104 /* SAI MCLK Divide Register */

#घोषणा FSL_SAI_xCSR(tx, ofs)	(tx ? FSL_SAI_TCSR(ofs) : FSL_SAI_RCSR(ofs))
#घोषणा FSL_SAI_xCR1(tx, ofs)	(tx ? FSL_SAI_TCR1(ofs) : FSL_SAI_RCR1(ofs))
#घोषणा FSL_SAI_xCR2(tx, ofs)	(tx ? FSL_SAI_TCR2(ofs) : FSL_SAI_RCR2(ofs))
#घोषणा FSL_SAI_xCR3(tx, ofs)	(tx ? FSL_SAI_TCR3(ofs) : FSL_SAI_RCR3(ofs))
#घोषणा FSL_SAI_xCR4(tx, ofs)	(tx ? FSL_SAI_TCR4(ofs) : FSL_SAI_RCR4(ofs))
#घोषणा FSL_SAI_xCR5(tx, ofs)	(tx ? FSL_SAI_TCR5(ofs) : FSL_SAI_RCR5(ofs))
#घोषणा FSL_SAI_xDR(tx, ofs)	(tx ? FSL_SAI_TDR(ofs) : FSL_SAI_RDR(ofs))
#घोषणा FSL_SAI_xFR(tx, ofs)	(tx ? FSL_SAI_TFR(ofs) : FSL_SAI_RFR(ofs))
#घोषणा FSL_SAI_xMR(tx)		(tx ? FSL_SAI_TMR : FSL_SAI_RMR)

/* SAI Transmit/Receive Control Register */
#घोषणा FSL_SAI_CSR_TERE	BIT(31)
#घोषणा FSL_SAI_CSR_SE		BIT(30)
#घोषणा FSL_SAI_CSR_FR		BIT(25)
#घोषणा FSL_SAI_CSR_SR		BIT(24)
#घोषणा FSL_SAI_CSR_xF_SHIFT	16
#घोषणा FSL_SAI_CSR_xF_W_SHIFT	18
#घोषणा FSL_SAI_CSR_xF_MASK	(0x1f << FSL_SAI_CSR_xF_SHIFT)
#घोषणा FSL_SAI_CSR_xF_W_MASK	(0x7 << FSL_SAI_CSR_xF_W_SHIFT)
#घोषणा FSL_SAI_CSR_WSF		BIT(20)
#घोषणा FSL_SAI_CSR_SEF		BIT(19)
#घोषणा FSL_SAI_CSR_FEF		BIT(18)
#घोषणा FSL_SAI_CSR_FWF		BIT(17)
#घोषणा FSL_SAI_CSR_FRF		BIT(16)
#घोषणा FSL_SAI_CSR_xIE_SHIFT	8
#घोषणा FSL_SAI_CSR_xIE_MASK	(0x1f << FSL_SAI_CSR_xIE_SHIFT)
#घोषणा FSL_SAI_CSR_WSIE	BIT(12)
#घोषणा FSL_SAI_CSR_SEIE	BIT(11)
#घोषणा FSL_SAI_CSR_FEIE	BIT(10)
#घोषणा FSL_SAI_CSR_FWIE	BIT(9)
#घोषणा FSL_SAI_CSR_FRIE	BIT(8)
#घोषणा FSL_SAI_CSR_FRDE	BIT(0)

/* SAI Transmit and Receive Configuration 1 Register */
#घोषणा FSL_SAI_CR1_RFW_MASK(x)	((x) - 1)

/* SAI Transmit and Receive Configuration 2 Register */
#घोषणा FSL_SAI_CR2_SYNC	BIT(30)
#घोषणा FSL_SAI_CR2_MSEL_MASK	(0x3 << 26)
#घोषणा FSL_SAI_CR2_MSEL_BUS	0
#घोषणा FSL_SAI_CR2_MSEL_MCLK1	BIT(26)
#घोषणा FSL_SAI_CR2_MSEL_MCLK2	BIT(27)
#घोषणा FSL_SAI_CR2_MSEL_MCLK3	(BIT(26) | BIT(27))
#घोषणा FSL_SAI_CR2_MSEL(ID)	((ID) << 26)
#घोषणा FSL_SAI_CR2_BCP		BIT(25)
#घोषणा FSL_SAI_CR2_BCD_MSTR	BIT(24)
#घोषणा FSL_SAI_CR2_BYP		BIT(23) /* BCLK bypass */
#घोषणा FSL_SAI_CR2_DIV_MASK	0xff

/* SAI Transmit and Receive Configuration 3 Register */
#घोषणा FSL_SAI_CR3_TRCE(x)     ((x) << 16)
#घोषणा FSL_SAI_CR3_TRCE_MASK	GENMASK(23, 16)
#घोषणा FSL_SAI_CR3_WDFL(x)	(x)
#घोषणा FSL_SAI_CR3_WDFL_MASK	0x1f

/* SAI Transmit and Receive Configuration 4 Register */

#घोषणा FSL_SAI_CR4_FCONT	BIT(28)
#घोषणा FSL_SAI_CR4_FCOMB_SHIFT BIT(26)
#घोषणा FSL_SAI_CR4_FCOMB_SOFT  BIT(27)
#घोषणा FSL_SAI_CR4_FCOMB_MASK  (0x3 << 26)
#घोषणा FSL_SAI_CR4_FPACK_8     (0x2 << 24)
#घोषणा FSL_SAI_CR4_FPACK_16    (0x3 << 24)
#घोषणा FSL_SAI_CR4_FRSZ(x)	(((x) - 1) << 16)
#घोषणा FSL_SAI_CR4_FRSZ_MASK	(0x1f << 16)
#घोषणा FSL_SAI_CR4_SYWD(x)	(((x) - 1) << 8)
#घोषणा FSL_SAI_CR4_SYWD_MASK	(0x1f << 8)
#घोषणा FSL_SAI_CR4_CHMOD       BIT(5)
#घोषणा FSL_SAI_CR4_CHMOD_MASK  BIT(5)
#घोषणा FSL_SAI_CR4_MF		BIT(4)
#घोषणा FSL_SAI_CR4_FSE		BIT(3)
#घोषणा FSL_SAI_CR4_FSP		BIT(1)
#घोषणा FSL_SAI_CR4_FSD_MSTR	BIT(0)

/* SAI Transmit and Receive Configuration 5 Register */
#घोषणा FSL_SAI_CR5_WNW(x)	(((x) - 1) << 24)
#घोषणा FSL_SAI_CR5_WNW_MASK	(0x1f << 24)
#घोषणा FSL_SAI_CR5_W0W(x)	(((x) - 1) << 16)
#घोषणा FSL_SAI_CR5_W0W_MASK	(0x1f << 16)
#घोषणा FSL_SAI_CR5_FBT(x)	((x) << 8)
#घोषणा FSL_SAI_CR5_FBT_MASK	(0x1f << 8)

/* SAI MCLK Control Register */
#घोषणा FSL_SAI_MCTL_MCLK_EN	BIT(30)	/* MCLK Enable */
#घोषणा FSL_SAI_MCTL_MSEL_MASK	(0x3 << 24)
#घोषणा FSL_SAI_MCTL_MSEL(ID)   ((ID) << 24)
#घोषणा FSL_SAI_MCTL_MSEL_BUS	0
#घोषणा FSL_SAI_MCTL_MSEL_MCLK1	BIT(24)
#घोषणा FSL_SAI_MCTL_MSEL_MCLK2	BIT(25)
#घोषणा FSL_SAI_MCTL_MSEL_MCLK3	(BIT(24) | BIT(25))
#घोषणा FSL_SAI_MCTL_DIV_EN	BIT(23)
#घोषणा FSL_SAI_MCTL_DIV_MASK	0xFF

/* SAI VERID Register */
#घोषणा FSL_SAI_VERID_MAJOR_SHIFT   24
#घोषणा FSL_SAI_VERID_MAJOR_MASK    GENMASK(31, 24)
#घोषणा FSL_SAI_VERID_MINOR_SHIFT   16
#घोषणा FSL_SAI_VERID_MINOR_MASK    GENMASK(23, 16)
#घोषणा FSL_SAI_VERID_FEATURE_SHIFT 0
#घोषणा FSL_SAI_VERID_FEATURE_MASK  GENMASK(15, 0)
#घोषणा FSL_SAI_VERID_EFIFO_EN	    BIT(0)
#घोषणा FSL_SAI_VERID_TSTMP_EN	    BIT(1)

/* SAI PARAM Register */
#घोषणा FSL_SAI_PARAM_SPF_SHIFT	    16
#घोषणा FSL_SAI_PARAM_SPF_MASK	    GENMASK(19, 16)
#घोषणा FSL_SAI_PARAM_WPF_SHIFT	    8
#घोषणा FSL_SAI_PARAM_WPF_MASK	    GENMASK(11, 8)
#घोषणा FSL_SAI_PARAM_DLN_MASK	    GENMASK(3, 0)

/* SAI MCLK Divide Register */
#घोषणा FSL_SAI_MDIV_MASK	    0xFFFFF

/* SAI बारtamp and bitcounter */
#घोषणा FSL_SAI_xTCTL_TSEN         BIT(0)
#घोषणा FSL_SAI_xTCTL_TSINC        BIT(1)
#घोषणा FSL_SAI_xTCTL_RTSC         BIT(8)
#घोषणा FSL_SAI_xTCTL_RBC          BIT(9)

/* SAI type */
#घोषणा FSL_SAI_DMA		BIT(0)
#घोषणा FSL_SAI_USE_AC97	BIT(1)
#घोषणा FSL_SAI_NET		BIT(2)
#घोषणा FSL_SAI_TRA_SYN		BIT(3)
#घोषणा FSL_SAI_REC_SYN		BIT(4)
#घोषणा FSL_SAI_USE_I2S_SLAVE	BIT(5)

#घोषणा FSL_FMT_TRANSMITTER	0
#घोषणा FSL_FMT_RECEIVER	1

/* SAI घड़ी sources */
#घोषणा FSL_SAI_CLK_BUS		0
#घोषणा FSL_SAI_CLK_MAST1	1
#घोषणा FSL_SAI_CLK_MAST2	2
#घोषणा FSL_SAI_CLK_MAST3	3

#घोषणा FSL_SAI_MCLK_MAX	4

/* SAI data transfer numbers per DMA request */
#घोषणा FSL_SAI_MAXBURST_TX 6
#घोषणा FSL_SAI_MAXBURST_RX 6

#घोषणा PMQOS_CPU_LATENCY   BIT(0)

काष्ठा fsl_sai_soc_data अणु
	bool use_imx_pcm;
	bool use_edma;
	bool mclk0_is_mclk1;
	अचिन्हित पूर्णांक fअगरo_depth;
	अचिन्हित पूर्णांक reg_offset;
	अचिन्हित पूर्णांक flags;
पूर्ण;

/**
 * काष्ठा fsl_sai_verid - version id data
 * @major: major version number
 * @minor: minor version number
 * @feature: feature specअगरication number
 *           0000000000000000b - Standard feature set
 *           0000000000000000b - Standard feature set
 */
काष्ठा fsl_sai_verid अणु
	u32 major;
	u32 minor;
	u32 feature;
पूर्ण;

/**
 * काष्ठा fsl_sai_param - parameter data
 * @slot_num: The maximum number of slots per frame
 * @fअगरo_depth: The number of words in each FIFO (depth)
 * @dataline: The number of datalines implemented
 */
काष्ठा fsl_sai_param अणु
	u32 slot_num;
	u32 fअगरo_depth;
	u32 dataline;
पूर्ण;

काष्ठा fsl_sai अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	काष्ठा clk *bus_clk;
	काष्ठा clk *mclk_clk[FSL_SAI_MCLK_MAX];

	bool is_slave_mode;
	bool is_lsb_first;
	bool is_dsp_mode;
	bool synchronous[2];

	अचिन्हित पूर्णांक mclk_id[2];
	अचिन्हित पूर्णांक mclk_streams;
	अचिन्हित पूर्णांक slots;
	अचिन्हित पूर्णांक slot_width;
	अचिन्हित पूर्णांक bclk_ratio;

	स्थिर काष्ठा fsl_sai_soc_data *soc_data;
	काष्ठा snd_soc_dai_driver cpu_dai_drv;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
	काष्ठा fsl_sai_verid verid;
	काष्ठा fsl_sai_param param;
	काष्ठा pm_qos_request pm_qos_req;
पूर्ण;

#घोषणा TX 1
#घोषणा RX 0

#पूर्ण_अगर /* __FSL_SAI_H */
