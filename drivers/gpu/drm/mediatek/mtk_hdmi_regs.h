<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Jie Qiu <jie.qiu@mediatek.com>
 */
#अगर_अघोषित _MTK_HDMI_REGS_H
#घोषणा _MTK_HDMI_REGS_H

#घोषणा GRL_INT_MASK		0x18
#घोषणा GRL_IFM_PORT		0x188
#घोषणा GRL_CH_SWAP		0x198
#घोषणा LR_SWAP				BIT(0)
#घोषणा LFE_CC_SWAP			BIT(1)
#घोषणा LSRS_SWAP			BIT(2)
#घोषणा RLS_RRS_SWAP			BIT(3)
#घोषणा LR_STATUS_SWAP			BIT(4)
#घोषणा GRL_I2S_C_STA0		0x140
#घोषणा GRL_I2S_C_STA1		0x144
#घोषणा GRL_I2S_C_STA2		0x148
#घोषणा GRL_I2S_C_STA3		0x14C
#घोषणा GRL_I2S_C_STA4		0x150
#घोषणा GRL_I2S_UV		0x154
#घोषणा I2S_UV_V			BIT(0)
#घोषणा I2S_UV_U			BIT(1)
#घोषणा I2S_UV_CH_EN_MASK		0x3c
#घोषणा I2S_UV_CH_EN(x)			BIT((x) + 2)
#घोषणा I2S_UV_TMDS_DEBUG		BIT(6)
#घोषणा I2S_UV_NORMAL_INFO_INV		BIT(7)
#घोषणा GRL_ACP_ISRC_CTRL	0x158
#घोषणा VS_EN				BIT(0)
#घोषणा ACP_EN				BIT(1)
#घोषणा ISRC1_EN			BIT(2)
#घोषणा ISRC2_EN			BIT(3)
#घोषणा GAMUT_EN			BIT(4)
#घोषणा GRL_CTS_CTRL		0x160
#घोषणा CTS_CTRL_SOFT			BIT(0)
#घोषणा GRL_INT			0x14
#घोषणा INT_MDI				BIT(0)
#घोषणा INT_HDCP			BIT(1)
#घोषणा INT_FIFO_O			BIT(2)
#घोषणा INT_FIFO_U			BIT(3)
#घोषणा INT_IFM_ERR			BIT(4)
#घोषणा INT_INF_DONE			BIT(5)
#घोषणा INT_NCTS_DONE			BIT(6)
#घोषणा INT_CTRL_PKT_DONE		BIT(7)
#घोषणा GRL_INT_MASK		0x18
#घोषणा GRL_CTRL		0x1C
#घोषणा CTRL_GEN_EN			BIT(2)
#घोषणा CTRL_SPD_EN			BIT(3)
#घोषणा CTRL_MPEG_EN			BIT(4)
#घोषणा CTRL_AUDIO_EN			BIT(5)
#घोषणा CTRL_AVI_EN			BIT(6)
#घोषणा CTRL_AVMUTE			BIT(7)
#घोषणा	GRL_STATUS		0x20
#घोषणा STATUS_HTPLG			BIT(0)
#घोषणा STATUS_PORD			BIT(1)
#घोषणा GRL_DIVN		0x170
#घोषणा NCTS_WRI_ANYTIME		BIT(6)
#घोषणा GRL_AUDIO_CFG		0x17C
#घोषणा AUDIO_ZERO			BIT(0)
#घोषणा HIGH_BIT_RATE			BIT(1)
#घोषणा SACD_DST			BIT(2)
#घोषणा DST_NORMAL_DOUBLE		BIT(3)
#घोषणा DSD_INV				BIT(4)
#घोषणा LR_INV				BIT(5)
#घोषणा LR_MIX				BIT(6)
#घोषणा DSD_SEL				BIT(7)
#घोषणा GRL_NCTS		0x184
#घोषणा GRL_CH_SW0		0x18C
#घोषणा GRL_CH_SW1		0x190
#घोषणा GRL_CH_SW2		0x194
#घोषणा CH_SWITCH(from, to)		((from) << ((to) * 3))
#घोषणा GRL_INFOFRM_VER		0x19C
#घोषणा GRL_INFOFRM_TYPE	0x1A0
#घोषणा GRL_INFOFRM_LNG		0x1A4
#घोषणा GRL_MIX_CTRL		0x1B4
#घोषणा MIX_CTRL_SRC_EN			BIT(0)
#घोषणा BYPASS_VOLUME			BIT(1)
#घोषणा MIX_CTRL_FLAT			BIT(7)
#घोषणा GRL_AOUT_CFG		0x1C4
#घोषणा AOUT_BNUM_SEL_MASK		0x03
#घोषणा AOUT_24BIT			0x00
#घोषणा AOUT_20BIT			0x02
#घोषणा AOUT_16BIT			0x03
#घोषणा AOUT_FIFO_ADAP_CTRL		BIT(6)
#घोषणा AOUT_BURST_PREAMBLE_EN		BIT(7)
#घोषणा HIGH_BIT_RATE_PACKET_ALIGN	(AOUT_BURST_PREAMBLE_EN | \
					 AOUT_FIFO_ADAP_CTRL)
#घोषणा GRL_SHIFT_L1		0x1C0
#घोषणा GRL_SHIFT_R2		0x1B0
#घोषणा AUDIO_PACKET_OFF		BIT(6)
#घोषणा GRL_CFG0		0x24
#घोषणा CFG0_I2S_MODE_MASK		0x3
#घोषणा CFG0_I2S_MODE_RTJ		0x1
#घोषणा CFG0_I2S_MODE_LTJ		0x0
#घोषणा CFG0_I2S_MODE_I2S		0x2
#घोषणा CFG0_W_LENGTH_MASK		0x30
#घोषणा CFG0_W_LENGTH_24BIT		0x00
#घोषणा CFG0_W_LENGTH_16BIT		0x10
#घोषणा GRL_CFG1		0x28
#घोषणा CFG1_EDG_SEL			BIT(0)
#घोषणा CFG1_SPDIF			BIT(1)
#घोषणा CFG1_DVI			BIT(2)
#घोषणा CFG1_HDCP_DEBUG			BIT(3)
#घोषणा GRL_CFG2		0x2c
#घोषणा CFG2_MHL_DE_SEL			BIT(3)
#घोषणा CFG2_MHL_FAKE_DE_SEL		BIT(4)
#घोषणा CFG2_MHL_DATA_REMAP		BIT(5)
#घोषणा CFG2_NOTICE_EN			BIT(6)
#घोषणा CFG2_ACLK_INV			BIT(7)
#घोषणा GRL_CFG3		0x30
#घोषणा CFG3_AES_KEY_INDEX_MASK		0x3f
#घोषणा CFG3_CONTROL_PACKET_DELAY	BIT(6)
#घोषणा CFG3_KSV_LOAD_START		BIT(7)
#घोषणा GRL_CFG4		0x34
#घोषणा CFG4_AES_KEY_LOAD		BIT(4)
#घोषणा CFG4_AV_UNMUTE_EN		BIT(5)
#घोषणा CFG4_AV_UNMUTE_SET		BIT(6)
#घोषणा CFG4_MHL_MODE			BIT(7)
#घोषणा GRL_CFG5		0x38
#घोषणा CFG5_CD_RATIO_MASK	0x8F
#घोषणा CFG5_FS128			(0x1 << 4)
#घोषणा CFG5_FS256			(0x2 << 4)
#घोषणा CFG5_FS384			(0x3 << 4)
#घोषणा CFG5_FS512			(0x4 << 4)
#घोषणा CFG5_FS768			(0x6 << 4)
#घोषणा DUMMY_304		0x304
#घोषणा CHMO_SEL			(0x3 << 2)
#घोषणा CHM1_SEL			(0x3 << 4)
#घोषणा CHM2_SEL			(0x3 << 6)
#घोषणा AUDIO_I2S_NCTS_SEL		BIT(1)
#घोषणा AUDIO_I2S_NCTS_SEL_64		(1 << 1)
#घोषणा AUDIO_I2S_NCTS_SEL_128		(0 << 1)
#घोषणा NEW_GCP_CTRL			BIT(0)
#घोषणा NEW_GCP_CTRL_MERGE		BIT(0)
#घोषणा GRL_L_STATUS_0		0x200
#घोषणा GRL_L_STATUS_1		0x204
#घोषणा GRL_L_STATUS_2		0x208
#घोषणा GRL_L_STATUS_3		0x20c
#घोषणा GRL_L_STATUS_4		0x210
#घोषणा GRL_L_STATUS_5		0x214
#घोषणा GRL_L_STATUS_6		0x218
#घोषणा GRL_L_STATUS_7		0x21c
#घोषणा GRL_L_STATUS_8		0x220
#घोषणा GRL_L_STATUS_9		0x224
#घोषणा GRL_L_STATUS_10		0x228
#घोषणा GRL_L_STATUS_11		0x22c
#घोषणा GRL_L_STATUS_12		0x230
#घोषणा GRL_L_STATUS_13		0x234
#घोषणा GRL_L_STATUS_14		0x238
#घोषणा GRL_L_STATUS_15		0x23c
#घोषणा GRL_L_STATUS_16		0x240
#घोषणा GRL_L_STATUS_17		0x244
#घोषणा GRL_L_STATUS_18		0x248
#घोषणा GRL_L_STATUS_19		0x24c
#घोषणा GRL_L_STATUS_20		0x250
#घोषणा GRL_L_STATUS_21		0x254
#घोषणा GRL_L_STATUS_22		0x258
#घोषणा GRL_L_STATUS_23		0x25c
#घोषणा GRL_R_STATUS_0		0x260
#घोषणा GRL_R_STATUS_1		0x264
#घोषणा GRL_R_STATUS_2		0x268
#घोषणा GRL_R_STATUS_3		0x26c
#घोषणा GRL_R_STATUS_4		0x270
#घोषणा GRL_R_STATUS_5		0x274
#घोषणा GRL_R_STATUS_6		0x278
#घोषणा GRL_R_STATUS_7		0x27c
#घोषणा GRL_R_STATUS_8		0x280
#घोषणा GRL_R_STATUS_9		0x284
#घोषणा GRL_R_STATUS_10		0x288
#घोषणा GRL_R_STATUS_11		0x28c
#घोषणा GRL_R_STATUS_12		0x290
#घोषणा GRL_R_STATUS_13		0x294
#घोषणा GRL_R_STATUS_14		0x298
#घोषणा GRL_R_STATUS_15		0x29c
#घोषणा GRL_R_STATUS_16		0x2a0
#घोषणा GRL_R_STATUS_17		0x2a4
#घोषणा GRL_R_STATUS_18		0x2a8
#घोषणा GRL_R_STATUS_19		0x2ac
#घोषणा GRL_R_STATUS_20		0x2b0
#घोषणा GRL_R_STATUS_21		0x2b4
#घोषणा GRL_R_STATUS_22		0x2b8
#घोषणा GRL_R_STATUS_23		0x2bc
#घोषणा GRL_ABIST_CTRL0		0x2D4
#घोषणा GRL_ABIST_CTRL1		0x2D8
#घोषणा ABIST_EN			BIT(7)
#घोषणा ABIST_DATA_FMT			(0x7 << 0)
#घोषणा VIDEO_CFG_0		0x380
#घोषणा VIDEO_CFG_1		0x384
#घोषणा VIDEO_CFG_2		0x388
#घोषणा VIDEO_CFG_3		0x38c
#घोषणा VIDEO_CFG_4		0x390
#घोषणा VIDEO_SOURCE_SEL		BIT(7)
#घोषणा NORMAL_PATH			(1 << 7)
#घोषणा GEN_RGB				(0 << 7)

#घोषणा HDMI_SYS_CFG1C		0x000
#घोषणा HDMI_ON				BIT(0)
#घोषणा HDMI_RST			BIT(1)
#घोषणा ANLG_ON				BIT(2)
#घोषणा CFG10_DVI			BIT(3)
#घोषणा HDMI_TST			BIT(3)
#घोषणा SYS_KEYMASK1			(0xff << 8)
#घोषणा SYS_KEYMASK2			(0xff << 16)
#घोषणा AUD_OUTSYNC_EN			BIT(24)
#घोषणा AUD_OUTSYNC_PRE_EN		BIT(25)
#घोषणा I2CM_ON				BIT(26)
#घोषणा E2PROM_TYPE_8BIT		BIT(27)
#घोषणा MCM_E2PROM_ON			BIT(28)
#घोषणा EXT_E2PROM_ON			BIT(29)
#घोषणा HTPLG_PIN_SEL_OFF		BIT(30)
#घोषणा AES_EFUSE_ENABLE		BIT(31)
#घोषणा HDMI_SYS_CFG20		0x004
#घोषणा DEEP_COLOR_MODE_MASK		(3 << 1)
#घोषणा COLOR_8BIT_MODE			(0 << 1)
#घोषणा COLOR_10BIT_MODE		(1 << 1)
#घोषणा COLOR_12BIT_MODE		(2 << 1)
#घोषणा COLOR_16BIT_MODE		(3 << 1)
#घोषणा DEEP_COLOR_EN			BIT(0)
#घोषणा HDMI_AUDIO_TEST_SEL		BIT(8)
#घोषणा HDMI2P0_EN			BIT(11)
#घोषणा HDMI_OUT_FIFO_EN		BIT(16)
#घोषणा HDMI_OUT_FIFO_CLK_INV		BIT(17)
#घोषणा MHL_MODE_ON			BIT(28)
#घोषणा MHL_PP_MODE			BIT(29)
#घोषणा MHL_SYNC_AUTO_EN		BIT(30)
#घोषणा HDMI_PCLK_FREE_RUN		BIT(31)

#घोषणा MTK_SIP_SET_AUTHORIZED_SECURE_REG 0x82000001
#पूर्ण_अगर
