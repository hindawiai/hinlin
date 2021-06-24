<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Ola Lilja <ola.o.lilja@stericsson.com>,
 *         क्रम ST-Ericsson.
 *
 * License terms:
 */


#अगर_अघोषित UX500_MSP_I2S_H
#घोषणा UX500_MSP_I2S_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/asoc-ux500-msp.h>

#घोषणा MSP_INPUT_FREQ_APB 48000000

/*** Stereo mode. Used क्रम APB data accesses as 16 bits accesses (mono),
 *   32 bits accesses (stereo).
 ***/
क्रमागत msp_stereo_mode अणु
	MSP_MONO,
	MSP_STEREO
पूर्ण;

/* Direction (Transmit/Receive mode) */
क्रमागत msp_direction अणु
	MSP_TX = 1,
	MSP_RX = 2
पूर्ण;

/* Transmit and receive configuration रेजिस्टर */
#घोषणा MSP_BIG_ENDIAN           0x00000000
#घोषणा MSP_LITTLE_ENDIAN        0x00001000
#घोषणा MSP_UNEXPECTED_FS_ABORT  0x00000000
#घोषणा MSP_UNEXPECTED_FS_IGNORE 0x00008000
#घोषणा MSP_NON_MODE_BIT_MASK    0x00009000

/* Global configuration रेजिस्टर */
#घोषणा RX_ENABLE             0x00000001
#घोषणा RX_FIFO_ENABLE        0x00000002
#घोषणा RX_SYNC_SRG           0x00000010
#घोषणा RX_CLK_POL_RISING     0x00000020
#घोषणा RX_CLK_SEL_SRG        0x00000040
#घोषणा TX_ENABLE             0x00000100
#घोषणा TX_FIFO_ENABLE        0x00000200
#घोषणा TX_SYNC_SRG_PROG      0x00001800
#घोषणा TX_SYNC_SRG_AUTO      0x00001000
#घोषणा TX_CLK_POL_RISING     0x00002000
#घोषणा TX_CLK_SEL_SRG        0x00004000
#घोषणा TX_EXTRA_DELAY_ENABLE 0x00008000
#घोषणा SRG_ENABLE            0x00010000
#घोषणा FRAME_GEN_ENABLE      0x00100000
#घोषणा SRG_CLK_SEL_APB       0x00000000
#घोषणा RX_FIFO_SYNC_HI       0x00000000
#घोषणा TX_FIFO_SYNC_HI       0x00000000
#घोषणा SPI_CLK_MODE_NORMAL   0x00000000

#घोषणा MSP_FRAME_SIZE_AUTO -1

#घोषणा MSP_DR		0x00
#घोषणा MSP_GCR		0x04
#घोषणा MSP_TCF		0x08
#घोषणा MSP_RCF		0x0c
#घोषणा MSP_SRG		0x10
#घोषणा MSP_FLR		0x14
#घोषणा MSP_DMACR	0x18

#घोषणा MSP_IMSC	0x20
#घोषणा MSP_RIS		0x24
#घोषणा MSP_MIS		0x28
#घोषणा MSP_ICR		0x2c
#घोषणा MSP_MCR		0x30
#घोषणा MSP_RCV		0x34
#घोषणा MSP_RCM		0x38

#घोषणा MSP_TCE0	0x40
#घोषणा MSP_TCE1	0x44
#घोषणा MSP_TCE2	0x48
#घोषणा MSP_TCE3	0x4c

#घोषणा MSP_RCE0	0x60
#घोषणा MSP_RCE1	0x64
#घोषणा MSP_RCE2	0x68
#घोषणा MSP_RCE3	0x6c
#घोषणा MSP_IODLY	0x70

#घोषणा MSP_ITCR	0x80
#घोषणा MSP_ITIP	0x84
#घोषणा MSP_ITOP	0x88
#घोषणा MSP_TSTDR	0x8c

#घोषणा MSP_PID0	0xfe0
#घोषणा MSP_PID1	0xfe4
#घोषणा MSP_PID2	0xfe8
#घोषणा MSP_PID3	0xfec

#घोषणा MSP_CID0	0xff0
#घोषणा MSP_CID1	0xff4
#घोषणा MSP_CID2	0xff8
#घोषणा MSP_CID3	0xffc

/* Protocol dependant parameters list */
#घोषणा RX_ENABLE_MASK		BIT(0)
#घोषणा RX_FIFO_ENABLE_MASK	BIT(1)
#घोषणा RX_FSYNC_MASK		BIT(2)
#घोषणा सूचीECT_COMPANDING_MASK	BIT(3)
#घोषणा RX_SYNC_SEL_MASK	BIT(4)
#घोषणा RX_CLK_POL_MASK		BIT(5)
#घोषणा RX_CLK_SEL_MASK		BIT(6)
#घोषणा LOOPBACK_MASK		BIT(7)
#घोषणा TX_ENABLE_MASK		BIT(8)
#घोषणा TX_FIFO_ENABLE_MASK	BIT(9)
#घोषणा TX_FSYNC_MASK		BIT(10)
#घोषणा TX_MSP_TDR_TSR		BIT(11)
#घोषणा TX_SYNC_SEL_MASK	(BIT(12) | BIT(11))
#घोषणा TX_CLK_POL_MASK		BIT(13)
#घोषणा TX_CLK_SEL_MASK		BIT(14)
#घोषणा TX_EXTRA_DELAY_MASK	BIT(15)
#घोषणा SRG_ENABLE_MASK		BIT(16)
#घोषणा SRG_CLK_POL_MASK	BIT(17)
#घोषणा SRG_CLK_SEL_MASK	(BIT(19) | BIT(18))
#घोषणा FRAME_GEN_EN_MASK	BIT(20)
#घोषणा SPI_CLK_MODE_MASK	(BIT(22) | BIT(21))
#घोषणा SPI_BURST_MODE_MASK	BIT(23)

#घोषणा RXEN_SHIFT		0
#घोषणा RFFEN_SHIFT		1
#घोषणा RFSPOL_SHIFT		2
#घोषणा DCM_SHIFT		3
#घोषणा RFSSEL_SHIFT		4
#घोषणा RCKPOL_SHIFT		5
#घोषणा RCKSEL_SHIFT		6
#घोषणा LBM_SHIFT		7
#घोषणा TXEN_SHIFT		8
#घोषणा TFFEN_SHIFT		9
#घोषणा TFSPOL_SHIFT		10
#घोषणा TFSSEL_SHIFT		11
#घोषणा TCKPOL_SHIFT		13
#घोषणा TCKSEL_SHIFT		14
#घोषणा TXDDL_SHIFT		15
#घोषणा SGEN_SHIFT		16
#घोषणा SCKPOL_SHIFT		17
#घोषणा SCKSEL_SHIFT		18
#घोषणा FGEN_SHIFT		20
#घोषणा SPICKM_SHIFT		21
#घोषणा TBSWAP_SHIFT		28

#घोषणा RCKPOL_MASK		BIT(0)
#घोषणा TCKPOL_MASK		BIT(0)
#घोषणा SPICKM_MASK		(BIT(1) | BIT(0))
#घोषणा MSP_RX_CLKPOL_BIT(n)     ((n & RCKPOL_MASK) << RCKPOL_SHIFT)
#घोषणा MSP_TX_CLKPOL_BIT(n)     ((n & TCKPOL_MASK) << TCKPOL_SHIFT)

#घोषणा P1ELEN_SHIFT		0
#घोषणा P1FLEN_SHIFT		3
#घोषणा DTYP_SHIFT		10
#घोषणा ENDN_SHIFT		12
#घोषणा DDLY_SHIFT		13
#घोषणा FSIG_SHIFT		15
#घोषणा P2ELEN_SHIFT		16
#घोषणा P2FLEN_SHIFT		19
#घोषणा P2SM_SHIFT		26
#घोषणा P2EN_SHIFT		27
#घोषणा FSYNC_SHIFT		15

#घोषणा P1ELEN_MASK		0x00000007
#घोषणा P2ELEN_MASK		0x00070000
#घोषणा P1FLEN_MASK		0x00000378
#घोषणा P2FLEN_MASK		0x03780000
#घोषणा DDLY_MASK		0x00003000
#घोषणा DTYP_MASK		0x00000600
#घोषणा P2SM_MASK		0x04000000
#घोषणा P2EN_MASK		0x08000000
#घोषणा ENDN_MASK		0x00001000
#घोषणा TFSPOL_MASK		0x00000400
#घोषणा TBSWAP_MASK		0x30000000
#घोषणा COMPANDING_MODE_MASK	0x00000c00
#घोषणा FSYNC_MASK		0x00008000

#घोषणा MSP_P1_ELEM_LEN_BITS(n)		(n & P1ELEN_MASK)
#घोषणा MSP_P2_ELEM_LEN_BITS(n)		(((n) << P2ELEN_SHIFT) & P2ELEN_MASK)
#घोषणा MSP_P1_FRAME_LEN_BITS(n)	(((n) << P1FLEN_SHIFT) & P1FLEN_MASK)
#घोषणा MSP_P2_FRAME_LEN_BITS(n)	(((n) << P2FLEN_SHIFT) & P2FLEN_MASK)
#घोषणा MSP_DATA_DELAY_BITS(n)		(((n) << DDLY_SHIFT) & DDLY_MASK)
#घोषणा MSP_DATA_TYPE_BITS(n)		(((n) << DTYP_SHIFT) & DTYP_MASK)
#घोषणा MSP_P2_START_MODE_BIT(n)	((n << P2SM_SHIFT) & P2SM_MASK)
#घोषणा MSP_P2_ENABLE_BIT(n)		((n << P2EN_SHIFT) & P2EN_MASK)
#घोषणा MSP_SET_ENDIANNES_BIT(n)	((n << ENDN_SHIFT) & ENDN_MASK)
#घोषणा MSP_FSYNC_POL(n)		((n << TFSPOL_SHIFT) & TFSPOL_MASK)
#घोषणा MSP_DATA_WORD_SWAP(n)		((n << TBSWAP_SHIFT) & TBSWAP_MASK)
#घोषणा MSP_SET_COMPANDING_MODE(n)	((n << DTYP_SHIFT) & \
						COMPANDING_MODE_MASK)
#घोषणा MSP_SET_FSYNC_IGNORE(n)		((n << FSYNC_SHIFT) & FSYNC_MASK)

/* Flag रेजिस्टर */
#घोषणा RX_BUSY			BIT(0)
#घोषणा RX_FIFO_EMPTY		BIT(1)
#घोषणा RX_FIFO_FULL		BIT(2)
#घोषणा TX_BUSY			BIT(3)
#घोषणा TX_FIFO_EMPTY		BIT(4)
#घोषणा TX_FIFO_FULL		BIT(5)

#घोषणा RBUSY_SHIFT		0
#घोषणा RFE_SHIFT		1
#घोषणा RFU_SHIFT		2
#घोषणा TBUSY_SHIFT		3
#घोषणा TFE_SHIFT		4
#घोषणा TFU_SHIFT		5

/* Multichannel control रेजिस्टर */
#घोषणा RMCEN_SHIFT		0
#घोषणा RMCSF_SHIFT		1
#घोषणा RCMPM_SHIFT		3
#घोषणा TMCEN_SHIFT		5
#घोषणा TNCSF_SHIFT		6

/* Sample rate generator रेजिस्टर */
#घोषणा SCKDIV_SHIFT		0
#घोषणा FRWID_SHIFT		10
#घोषणा FRPER_SHIFT		16

#घोषणा SCK_DIV_MASK		0x0000003FF
#घोषणा FRAME_WIDTH_BITS(n)	(((n) << FRWID_SHIFT)  & 0x0000FC00)
#घोषणा FRAME_PERIOD_BITS(n)	(((n) << FRPER_SHIFT) & 0x1FFF0000)

/* DMA controller रेजिस्टर */
#घोषणा RX_DMA_ENABLE		BIT(0)
#घोषणा TX_DMA_ENABLE		BIT(1)

#घोषणा RDMAE_SHIFT		0
#घोषणा TDMAE_SHIFT		1

/* Interrupt Register */
#घोषणा RX_SERVICE_INT		BIT(0)
#घोषणा RX_OVERRUN_ERROR_INT	BIT(1)
#घोषणा RX_FSYNC_ERR_INT	BIT(2)
#घोषणा RX_FSYNC_INT		BIT(3)
#घोषणा TX_SERVICE_INT		BIT(4)
#घोषणा TX_UNDERRUN_ERR_INT	BIT(5)
#घोषणा TX_FSYNC_ERR_INT	BIT(6)
#घोषणा TX_FSYNC_INT		BIT(7)
#घोषणा ALL_INT			0x000000ff

/* MSP test control रेजिस्टर */
#घोषणा MSP_ITCR_ITEN		BIT(0)
#घोषणा MSP_ITCR_TESTFIFO	BIT(1)

#घोषणा RMCEN_BIT   0
#घोषणा RMCSF_BIT   1
#घोषणा RCMPM_BIT   3
#घोषणा TMCEN_BIT   5
#घोषणा TNCSF_BIT   6

/* Single or dual phase mode */
क्रमागत msp_phase_mode अणु
	MSP_SINGLE_PHASE,
	MSP_DUAL_PHASE
पूर्ण;

/* Frame length */
क्रमागत msp_frame_length अणु
	MSP_FRAME_LEN_1 = 0,
	MSP_FRAME_LEN_2 = 1,
	MSP_FRAME_LEN_4 = 3,
	MSP_FRAME_LEN_8 = 7,
	MSP_FRAME_LEN_12 = 11,
	MSP_FRAME_LEN_16 = 15,
	MSP_FRAME_LEN_20 = 19,
	MSP_FRAME_LEN_32 = 31,
	MSP_FRAME_LEN_48 = 47,
	MSP_FRAME_LEN_64 = 63
पूर्ण;

/* Element length */
क्रमागत msp_elem_length अणु
	MSP_ELEM_LEN_8 = 0,
	MSP_ELEM_LEN_10 = 1,
	MSP_ELEM_LEN_12 = 2,
	MSP_ELEM_LEN_14 = 3,
	MSP_ELEM_LEN_16 = 4,
	MSP_ELEM_LEN_20 = 5,
	MSP_ELEM_LEN_24 = 6,
	MSP_ELEM_LEN_32 = 7
पूर्ण;

क्रमागत msp_data_xfer_width अणु
	MSP_DATA_TRANSFER_WIDTH_BYTE,
	MSP_DATA_TRANSFER_WIDTH_HALFWORD,
	MSP_DATA_TRANSFER_WIDTH_WORD
पूर्ण;

क्रमागत msp_frame_sync अणु
	MSP_FSYNC_UNIGNORE = 0,
	MSP_FSYNC_IGNORE = 1,
पूर्ण;

क्रमागत msp_phase2_start_mode अणु
	MSP_PHASE2_START_MODE_IMEDIATE,
	MSP_PHASE2_START_MODE_FSYNC
पूर्ण;

क्रमागत msp_btf अणु
	MSP_BTF_MS_BIT_FIRST = 0,
	MSP_BTF_LS_BIT_FIRST = 1
पूर्ण;

क्रमागत msp_fsync_pol अणु
	MSP_FSYNC_POL_ACT_HI = 0,
	MSP_FSYNC_POL_ACT_LO = 1
पूर्ण;

/* Data delay (in bit घड़ी cycles) */
क्रमागत msp_delay अणु
	MSP_DELAY_0 = 0,
	MSP_DELAY_1 = 1,
	MSP_DELAY_2 = 2,
	MSP_DELAY_3 = 3
पूर्ण;

/* Configurations of घड़ीs (transmit, receive or sample rate generator) */
क्रमागत msp_edge अणु
	MSP_FALLING_EDGE = 0,
	MSP_RISING_EDGE = 1,
पूर्ण;

क्रमागत msp_hws अणु
	MSP_SWAP_NONE = 0,
	MSP_SWAP_BYTE_PER_WORD = 1,
	MSP_SWAP_BYTE_PER_HALF_WORD = 2,
	MSP_SWAP_HALF_WORD_PER_WORD = 3
पूर्ण;

क्रमागत msp_compress_mode अणु
	MSP_COMPRESS_MODE_LINEAR = 0,
	MSP_COMPRESS_MODE_MU_LAW = 2,
	MSP_COMPRESS_MODE_A_LAW = 3
पूर्ण;

क्रमागत msp_expand_mode अणु
	MSP_EXPAND_MODE_LINEAR = 0,
	MSP_EXPAND_MODE_LINEAR_SIGNED = 1,
	MSP_EXPAND_MODE_MU_LAW = 2,
	MSP_EXPAND_MODE_A_LAW = 3
पूर्ण;

#घोषणा MSP_FRAME_PERIOD_IN_MONO_MODE 256
#घोषणा MSP_FRAME_PERIOD_IN_STEREO_MODE 32
#घोषणा MSP_FRAME_WIDTH_IN_STEREO_MODE 16

क्रमागत msp_protocol अणु
	MSP_I2S_PROTOCOL,
	MSP_PCM_PROTOCOL,
	MSP_PCM_COMPAND_PROTOCOL,
	MSP_INVALID_PROTOCOL
पूर्ण;

/*
 * No of रेजिस्टरs to backup during
 * suspend resume
 */
#घोषणा MAX_MSP_BACKUP_REGS 36

क्रमागत i2s_direction_t अणु
	MSP_सूची_TX = 0x01,
	MSP_सूची_RX = 0x02,
पूर्ण;

क्रमागत msp_data_size अणु
	MSP_DATA_BITS_DEFAULT = -1,
	MSP_DATA_BITS_8 = 0x00,
	MSP_DATA_BITS_10,
	MSP_DATA_BITS_12,
	MSP_DATA_BITS_14,
	MSP_DATA_BITS_16,
	MSP_DATA_BITS_20,
	MSP_DATA_BITS_24,
	MSP_DATA_BITS_32,
पूर्ण;

क्रमागत msp_state अणु
	MSP_STATE_IDLE = 0,
	MSP_STATE_CONFIGURED = 1,
	MSP_STATE_RUNNING = 2,
पूर्ण;

क्रमागत msp_rx_comparison_enable_mode अणु
	MSP_COMPARISON_DISABLED = 0,
	MSP_COMPARISON_NONEQUAL_ENABLED = 2,
	MSP_COMPARISON_EQUAL_ENABLED = 3
पूर्ण;

काष्ठा msp_multichannel_config अणु
	bool rx_multichannel_enable;
	bool tx_multichannel_enable;
	क्रमागत msp_rx_comparison_enable_mode rx_comparison_enable_mode;
	u8 padding;
	u32 comparison_value;
	u32 comparison_mask;
	u32 rx_channel_0_enable;
	u32 rx_channel_1_enable;
	u32 rx_channel_2_enable;
	u32 rx_channel_3_enable;
	u32 tx_channel_0_enable;
	u32 tx_channel_1_enable;
	u32 tx_channel_2_enable;
	u32 tx_channel_3_enable;
पूर्ण;

काष्ठा msp_protdesc अणु
	u32 rx_phase_mode;
	u32 tx_phase_mode;
	u32 rx_phase2_start_mode;
	u32 tx_phase2_start_mode;
	u32 rx_byte_order;
	u32 tx_byte_order;
	u32 rx_frame_len_1;
	u32 rx_frame_len_2;
	u32 tx_frame_len_1;
	u32 tx_frame_len_2;
	u32 rx_elem_len_1;
	u32 rx_elem_len_2;
	u32 tx_elem_len_1;
	u32 tx_elem_len_2;
	u32 rx_data_delay;
	u32 tx_data_delay;
	u32 rx_clk_pol;
	u32 tx_clk_pol;
	u32 rx_fsync_pol;
	u32 tx_fsync_pol;
	u32 rx_half_word_swap;
	u32 tx_half_word_swap;
	u32 compression_mode;
	u32 expansion_mode;
	u32 frame_sync_ignore;
	u32 frame_period;
	u32 frame_width;
	u32 घड़ीs_per_frame;
पूर्ण;

काष्ठा ux500_msp_config अणु
	अचिन्हित पूर्णांक f_inअ_दोlk;
	अचिन्हित पूर्णांक rx_clk_sel;
	अचिन्हित पूर्णांक tx_clk_sel;
	अचिन्हित पूर्णांक srg_clk_sel;
	अचिन्हित पूर्णांक rx_fsync_pol;
	अचिन्हित पूर्णांक tx_fsync_pol;
	अचिन्हित पूर्णांक rx_fsync_sel;
	अचिन्हित पूर्णांक tx_fsync_sel;
	अचिन्हित पूर्णांक rx_fअगरo_config;
	अचिन्हित पूर्णांक tx_fअगरo_config;
	अचिन्हित पूर्णांक loopback_enable;
	अचिन्हित पूर्णांक tx_data_enable;
	अचिन्हित पूर्णांक शेष_protdesc;
	काष्ठा msp_protdesc protdesc;
	पूर्णांक multichannel_configured;
	काष्ठा msp_multichannel_config multichannel_config;
	अचिन्हित पूर्णांक direction;
	अचिन्हित पूर्णांक protocol;
	अचिन्हित पूर्णांक frame_freq;
	क्रमागत msp_data_size data_size;
	अचिन्हित पूर्णांक def_elem_len;
	अचिन्हित पूर्णांक iodelay;
पूर्ण;

काष्ठा ux500_msp_dma_params अणु
	अचिन्हित पूर्णांक data_size;
	dma_addr_t tx_rx_addr;
	काष्ठा stedma40_chan_cfg *dma_cfg;
पूर्ण;

काष्ठा ux500_msp अणु
	पूर्णांक id;
	व्योम __iomem *रेजिस्टरs;
	काष्ठा device *dev;
	काष्ठा ux500_msp_dma_params playback_dma_data;
	काष्ठा ux500_msp_dma_params capture_dma_data;
	क्रमागत msp_state msp_state;
	पूर्णांक def_elem_len;
	अचिन्हित पूर्णांक dir_busy;
	पूर्णांक loopback_enable;
	अचिन्हित पूर्णांक f_bitclk;
पूर्ण;

काष्ठा msp_i2s_platक्रमm_data;
पूर्णांक ux500_msp_i2s_init_msp(काष्ठा platक्रमm_device *pdev,
			काष्ठा ux500_msp **msp_p,
			काष्ठा msp_i2s_platक्रमm_data *platक्रमm_data);
व्योम ux500_msp_i2s_cleanup_msp(काष्ठा platक्रमm_device *pdev,
			काष्ठा ux500_msp *msp);
पूर्णांक ux500_msp_i2s_खोलो(काष्ठा ux500_msp *msp, काष्ठा ux500_msp_config *config);
पूर्णांक ux500_msp_i2s_बंद(काष्ठा ux500_msp *msp,
			अचिन्हित पूर्णांक dir);
पूर्णांक ux500_msp_i2s_trigger(काष्ठा ux500_msp *msp, पूर्णांक cmd,
			पूर्णांक direction);

#पूर्ण_अगर
