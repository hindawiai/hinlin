<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *   पूर्णांकel_hdmi_lpe_audपन.स - Intel HDMI LPE audio driver
 *
 *  Copyright (C) 2016 Intel Corp
 *  Authors:	Sailaja Bandarupalli <sailaja.bandarupalli@पूर्णांकel.com>
 *		Ramesh Babu K V <ramesh.babu@पूर्णांकel.com>
 *		Vaibhav Agarwal <vaibhav.agarwal@पूर्णांकel.com>
 *		Jerome Anand <jerome.anand@पूर्णांकel.com>
 *		Aravind Siddappaji <aravindx.siddappaji@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#अगर_अघोषित __INTEL_HDMI_LPE_AUDIO_H
#घोषणा __INTEL_HDMI_LPE_AUDIO_H

#घोषणा HAD_MIN_CHANNEL		2
#घोषणा HAD_MAX_CHANNEL		8
#घोषणा HAD_NUM_OF_RING_BUFS	4

/* max 20bit address, aligned to 64 */
#घोषणा HAD_MAX_BUFFER		((1024 * 1024 - 1) & ~0x3f)
#घोषणा HAD_DEFAULT_BUFFER	(600 * 1024) /* शेष pपुनः_स्मृति size */
#घोषणा HAD_MAX_PERIODS		256	/* arbitrary, but should suffice */
#घोषणा HAD_MIN_PERIODS		1
#घोषणा HAD_MAX_PERIOD_BYTES	((HAD_MAX_BUFFER / HAD_MIN_PERIODS) & ~0x3f)
#घोषणा HAD_MIN_PERIOD_BYTES	1024	/* might be smaller */
#घोषणा HAD_FIFO_SIZE		0 /* fअगरo not being used */
#घोषणा MAX_SPEAKERS		8

#घोषणा AUD_SAMPLE_RATE_32	32000
#घोषणा AUD_SAMPLE_RATE_44_1	44100
#घोषणा AUD_SAMPLE_RATE_48	48000
#घोषणा AUD_SAMPLE_RATE_88_2	88200
#घोषणा AUD_SAMPLE_RATE_96	96000
#घोषणा AUD_SAMPLE_RATE_176_4	176400
#घोषणा AUD_SAMPLE_RATE_192	192000

#घोषणा HAD_MIN_RATE		AUD_SAMPLE_RATE_32
#घोषणा HAD_MAX_RATE		AUD_SAMPLE_RATE_192

#घोषणा DIS_SAMPLE_RATE_25_2	25200
#घोषणा DIS_SAMPLE_RATE_27	27000
#घोषणा DIS_SAMPLE_RATE_54	54000
#घोषणा DIS_SAMPLE_RATE_74_25	74250
#घोषणा DIS_SAMPLE_RATE_148_5	148500
#घोषणा HAD_REG_WIDTH		0x08
#घोषणा HAD_MAX_DIP_WORDS		16

/* DP Link Rates */
#घोषणा DP_2_7_GHZ			270000
#घोषणा DP_1_62_GHZ			162000

/* Maud Values */
#घोषणा AUD_SAMPLE_RATE_32_DP_2_7_MAUD_VAL		1988
#घोषणा AUD_SAMPLE_RATE_44_1_DP_2_7_MAUD_VAL		2740
#घोषणा AUD_SAMPLE_RATE_48_DP_2_7_MAUD_VAL		2982
#घोषणा AUD_SAMPLE_RATE_88_2_DP_2_7_MAUD_VAL		5480
#घोषणा AUD_SAMPLE_RATE_96_DP_2_7_MAUD_VAL		5965
#घोषणा AUD_SAMPLE_RATE_176_4_DP_2_7_MAUD_VAL		10961
#घोषणा HAD_MAX_RATE_DP_2_7_MAUD_VAL			11930
#घोषणा AUD_SAMPLE_RATE_32_DP_1_62_MAUD_VAL		3314
#घोषणा AUD_SAMPLE_RATE_44_1_DP_1_62_MAUD_VAL		4567
#घोषणा AUD_SAMPLE_RATE_48_DP_1_62_MAUD_VAL		4971
#घोषणा AUD_SAMPLE_RATE_88_2_DP_1_62_MAUD_VAL		9134
#घोषणा AUD_SAMPLE_RATE_96_DP_1_62_MAUD_VAL		9942
#घोषणा AUD_SAMPLE_RATE_176_4_DP_1_62_MAUD_VAL		18268
#घोषणा HAD_MAX_RATE_DP_1_62_MAUD_VAL			19884

/* Naud Value */
#घोषणा DP_NAUD_VAL					32768

/* HDMI Controller रेजिस्टर offsets - audio करोमुख्य common */
/* Base address क्रम below regs = 0x65000 */
क्रमागत hdmi_ctrl_reg_offset_common अणु
	AUDIO_HDMI_CONFIG_A = 0x000,
	AUDIO_HDMI_CONFIG_B = 0x800,
	AUDIO_HDMI_CONFIG_C = 0x900,
पूर्ण;
/* HDMI controller रेजिस्टर offsets */
क्रमागत hdmi_ctrl_reg_offset अणु
	AUD_CONFIG		= 0x0,
	AUD_CH_STATUS_0		= 0x08,
	AUD_CH_STATUS_1		= 0x0C,
	AUD_HDMI_CTS		= 0x10,
	AUD_N_ENABLE		= 0x14,
	AUD_SAMPLE_RATE		= 0x18,
	AUD_BUF_CONFIG		= 0x20,
	AUD_BUF_CH_SWAP		= 0x24,
	AUD_BUF_A_ADDR		= 0x40,
	AUD_BUF_A_LENGTH	= 0x44,
	AUD_BUF_B_ADDR		= 0x48,
	AUD_BUF_B_LENGTH	= 0x4c,
	AUD_BUF_C_ADDR		= 0x50,
	AUD_BUF_C_LENGTH	= 0x54,
	AUD_BUF_D_ADDR		= 0x58,
	AUD_BUF_D_LENGTH	= 0x5c,
	AUD_CNTL_ST		= 0x60,
	AUD_HDMI_STATUS		= 0x64, /* v2 */
	AUD_HDMIW_INFOFR	= 0x68, /* v2 */
पूर्ण;

/* Audio configuration */
जोड़ aud_cfg अणु
	काष्ठा अणु
		u32 aud_en:1;
		u32 layout:1;		/* LAYOUT[01], see below */
		u32 fmt:2;
		u32 num_ch:3;
		u32 set:1;
		u32 flat:1;
		u32 val_bit:1;
		u32 user_bit:1;
		u32 underrun:1;		/* 0: send null packets,
					 * 1: send silence stream
					 */
		u32 packet_mode:1;	/* 0: 32bit container, 1: 16bit */
		u32 left_align:1;	/* 0: MSB bits 0-23, 1: bits 8-31 */
		u32 bogus_sample:1;	/* bogus sample क्रम odd channels */
		u32 dp_modei:1;		/* 0: HDMI, 1: DP */
		u32 rsvd:16;
	पूर्ण regx;
	u32 regval;
पूर्ण;

#घोषणा AUD_CONFIG_VALID_BIT			(1 << 9)
#घोषणा AUD_CONFIG_DP_MODE			(1 << 15)
#घोषणा AUD_CONFIG_CH_MASK	0x70
#घोषणा LAYOUT0			0		/* पूर्णांकerleaved stereo */
#घोषणा LAYOUT1			1		/* क्रम channels > 2 */

/* Audio Channel Status 0 Attributes */
जोड़ aud_ch_status_0 अणु
	काष्ठा अणु
		u32 ch_status:1;
		u32 lpcm_id:1;
		u32 cp_info:1;
		u32 क्रमmat:3;
		u32 mode:2;
		u32 ctg_code:8;
		u32 src_num:4;
		u32 ch_num:4;
		u32 samp_freq:4;	/* CH_STATUS_MAP_XXX */
		u32 clk_acc:2;
		u32 rsvd:2;
	पूर्ण regx;
	u32 regval;
पूर्ण;

/* samp_freq values - Sampling rate as per IEC60958 Ver 3 */
#घोषणा CH_STATUS_MAP_32KHZ	0x3
#घोषणा CH_STATUS_MAP_44KHZ	0x0
#घोषणा CH_STATUS_MAP_48KHZ	0x2
#घोषणा CH_STATUS_MAP_88KHZ	0x8
#घोषणा CH_STATUS_MAP_96KHZ	0xA
#घोषणा CH_STATUS_MAP_176KHZ	0xC
#घोषणा CH_STATUS_MAP_192KHZ	0xE

/* Audio Channel Status 1 Attributes */
जोड़ aud_ch_status_1 अणु
	काष्ठा अणु
		u32 max_wrd_len:1;
		u32 wrd_len:3;
		u32 rsvd:28;
	पूर्ण regx;
	u32 regval;
पूर्ण;

#घोषणा MAX_SMPL_WIDTH_20	0x0
#घोषणा MAX_SMPL_WIDTH_24	0x1
#घोषणा SMPL_WIDTH_16BITS	0x1
#घोषणा SMPL_WIDTH_24BITS	0x5

/* CTS रेजिस्टर */
जोड़ aud_hdmi_cts अणु
	काष्ठा अणु
		u32 cts_val:24;
		u32 en_cts_prog:1;
		u32 rsvd:7;
	पूर्ण regx;
	u32 regval;
पूर्ण;

/* N रेजिस्टर */
जोड़ aud_hdmi_n_enable अणु
	काष्ठा अणु
		u32 n_val:24;
		u32 en_n_prog:1;
		u32 rsvd:7;
	पूर्ण regx;
	u32 regval;
पूर्ण;

/* Audio Buffer configurations */
जोड़ aud_buf_config अणु
	काष्ठा अणु
		u32 audio_fअगरo_watermark:8;
		u32 dma_fअगरo_watermark:3;
		u32 rsvd0:5;
		u32 aud_delay:8;
		u32 rsvd1:8;
	पूर्ण regx;
	u32 regval;
पूर्ण;

#घोषणा FIFO_THRESHOLD		0xFE
#घोषणा DMA_FIFO_THRESHOLD	0x7

/* Audio Sample Swapping offset */
जोड़ aud_buf_ch_swap अणु
	काष्ठा अणु
		u32 first_0:3;
		u32 second_0:3;
		u32 first_1:3;
		u32 second_1:3;
		u32 first_2:3;
		u32 second_2:3;
		u32 first_3:3;
		u32 second_3:3;
		u32 rsvd:8;
	पूर्ण regx;
	u32 regval;
पूर्ण;

#घोषणा SWAP_LFE_CENTER		0x00fac4c8	/* octal 76543210 */

/* Address क्रम Audio Buffer */
जोड़ aud_buf_addr अणु
	काष्ठा अणु
		u32 valid:1;
		u32 पूर्णांकr_en:1;
		u32 rsvd:4;
		u32 addr:26;
	पूर्ण regx;
	u32 regval;
पूर्ण;

#घोषणा AUD_BUF_VALID		(1U << 0)
#घोषणा AUD_BUF_INTR_EN		(1U << 1)

/* Length of Audio Buffer */
जोड़ aud_buf_len अणु
	काष्ठा अणु
		u32 buf_len:20;
		u32 rsvd:12;
	पूर्ण regx;
	u32 regval;
पूर्ण;

/* Audio Control State Register offset */
जोड़ aud_ctrl_st अणु
	काष्ठा अणु
		u32 ram_addr:4;
		u32 eld_ack:1;
		u32 eld_addr:4;
		u32 eld_buf_size:5;
		u32 eld_valid:1;
		u32 cp_पढ़ोy:1;
		u32 dip_freq:2;
		u32 dip_idx:3;
		u32 dip_en_sta:4;
		u32 rsvd:7;
	पूर्ण regx;
	u32 regval;
पूर्ण;

/* Audio HDMI Widget Data Island Packet offset */
जोड़ aud_info_frame1 अणु
	काष्ठा अणु
		u32 pkt_type:8;
		u32 ver_num:8;
		u32 len:5;
		u32 rsvd:11;
	पूर्ण regx;
	u32 regval;
पूर्ण;

#घोषणा HDMI_INFO_FRAME_WORD1	0x000a0184
#घोषणा DP_INFO_FRAME_WORD1	0x00441b84

/* DIP frame 2 */
जोड़ aud_info_frame2 अणु
	काष्ठा अणु
		u32 chksum:8;
		u32 chnl_cnt:3;
		u32 rsvd0:1;
		u32 coding_type:4;
		u32 smpl_size:2;
		u32 smpl_freq:3;
		u32 rsvd1:3;
		u32 क्रमmat:8;
	पूर्ण regx;
	u32 regval;
पूर्ण;

/* DIP frame 3 */
जोड़ aud_info_frame3 अणु
	काष्ठा अणु
		u32 chnl_alloc:8;
		u32 rsvd0:3;
		u32 lsv:4;
		u32 dm_inh:1;
		u32 rsvd1:16;
	पूर्ण regx;
	u32 regval;
पूर्ण;

#घोषणा VALID_DIP_WORDS		3

/* AUD_HDMI_STATUS bits */
#घोषणा HDMI_AUDIO_UNDERRUN		(1U << 31)
#घोषणा HDMI_AUDIO_BUFFER_DONE		(1U << 29)

/* AUD_HDMI_STATUS रेजिस्टर mask */
#घोषणा AUD_HDMI_STATUS_MASK_UNDERRUN	0xC0000000
#घोषणा AUD_HDMI_STATUS_MASK_SRDBG	0x00000002
#घोषणा AUD_HDMI_STATUSG_MASK_FUNCRST	0x00000001

#पूर्ण_अगर
