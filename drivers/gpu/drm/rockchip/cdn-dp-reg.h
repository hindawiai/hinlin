<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Chris Zhong <zyw@rock-chips.com>
 */

#अगर_अघोषित _CDN_DP_REG_H
#घोषणा _CDN_DP_REG_H

#समावेश <linux/bitops.h>

#घोषणा ADDR_IMEM		0x10000
#घोषणा ADDR_DMEM		0x20000

/* APB CFG addr */
#घोषणा APB_CTRL			0
#घोषणा XT_INT_CTRL			0x04
#घोषणा MAILBOX_FULL_ADDR		0x08
#घोषणा MAILBOX_EMPTY_ADDR		0x0c
#घोषणा MAILBOX0_WR_DATA		0x10
#घोषणा MAILBOX0_RD_DATA		0x14
#घोषणा KEEP_ALIVE			0x18
#घोषणा VER_L				0x1c
#घोषणा VER_H				0x20
#घोषणा VER_LIB_L_ADDR			0x24
#घोषणा VER_LIB_H_ADDR			0x28
#घोषणा SW_DEBUG_L			0x2c
#घोषणा SW_DEBUG_H			0x30
#घोषणा MAILBOX_INT_MASK		0x34
#घोषणा MAILBOX_INT_STATUS		0x38
#घोषणा SW_CLK_L			0x3c
#घोषणा SW_CLK_H			0x40
#घोषणा SW_EVENTS0			0x44
#घोषणा SW_EVENTS1			0x48
#घोषणा SW_EVENTS2			0x4c
#घोषणा SW_EVENTS3			0x50
#घोषणा XT_OCD_CTRL			0x60
#घोषणा APB_INT_MASK			0x6c
#घोषणा APB_STATUS_MASK			0x70

/* audio decoder addr */
#घोषणा AUDIO_SRC_CNTL			0x30000
#घोषणा AUDIO_SRC_CNFG			0x30004
#घोषणा COM_CH_STTS_BITS		0x30008
#घोषणा STTS_BIT_CH(x)			(0x3000c + ((x) << 2))
#घोषणा SPDIF_CTRL_ADDR			0x3004c
#घोषणा SPDIF_CH1_CS_3100_ADDR		0x30050
#घोषणा SPDIF_CH1_CS_6332_ADDR		0x30054
#घोषणा SPDIF_CH1_CS_9564_ADDR		0x30058
#घोषणा SPDIF_CH1_CS_12796_ADDR		0x3005c
#घोषणा SPDIF_CH1_CS_159128_ADDR	0x30060
#घोषणा SPDIF_CH1_CS_191160_ADDR	0x30064
#घोषणा SPDIF_CH2_CS_3100_ADDR		0x30068
#घोषणा SPDIF_CH2_CS_6332_ADDR		0x3006c
#घोषणा SPDIF_CH2_CS_9564_ADDR		0x30070
#घोषणा SPDIF_CH2_CS_12796_ADDR		0x30074
#घोषणा SPDIF_CH2_CS_159128_ADDR	0x30078
#घोषणा SPDIF_CH2_CS_191160_ADDR	0x3007c
#घोषणा SMPL2PKT_CNTL			0x30080
#घोषणा SMPL2PKT_CNFG			0x30084
#घोषणा FIFO_CNTL			0x30088
#घोषणा FIFO_STTS			0x3008c

/* source pअगर addr */
#घोषणा SOURCE_PIF_WR_ADDR		0x30800
#घोषणा SOURCE_PIF_WR_REQ		0x30804
#घोषणा SOURCE_PIF_RD_ADDR		0x30808
#घोषणा SOURCE_PIF_RD_REQ		0x3080c
#घोषणा SOURCE_PIF_DATA_WR		0x30810
#घोषणा SOURCE_PIF_DATA_RD		0x30814
#घोषणा SOURCE_PIF_FIFO1_FLUSH		0x30818
#घोषणा SOURCE_PIF_FIFO2_FLUSH		0x3081c
#घोषणा SOURCE_PIF_STATUS		0x30820
#घोषणा SOURCE_PIF_INTERRUPT_SOURCE	0x30824
#घोषणा SOURCE_PIF_INTERRUPT_MASK	0x30828
#घोषणा SOURCE_PIF_PKT_ALLOC_REG	0x3082c
#घोषणा SOURCE_PIF_PKT_ALLOC_WR_EN	0x30830
#घोषणा SOURCE_PIF_SW_RESET		0x30834

/* bellow रेजिस्टरs need access by mailbox */
/* source car addr */
#घोषणा SOURCE_HDTX_CAR			0x0900
#घोषणा SOURCE_DPTX_CAR			0x0904
#घोषणा SOURCE_PHY_CAR			0x0908
#घोषणा SOURCE_CEC_CAR			0x090c
#घोषणा SOURCE_CBUS_CAR			0x0910
#घोषणा SOURCE_PKT_CAR			0x0918
#घोषणा SOURCE_AIF_CAR			0x091c
#घोषणा SOURCE_CIPHER_CAR		0x0920
#घोषणा SOURCE_CRYPTO_CAR		0x0924

/* घड़ी meters addr */
#घोषणा CM_CTRL				0x0a00
#घोषणा CM_I2S_CTRL			0x0a04
#घोषणा CM_SPDIF_CTRL			0x0a08
#घोषणा CM_VID_CTRL			0x0a0c
#घोषणा CM_LANE_CTRL			0x0a10
#घोषणा I2S_NM_STABLE			0x0a14
#घोषणा I2S_NCTS_STABLE			0x0a18
#घोषणा SPDIF_NM_STABLE			0x0a1c
#घोषणा SPDIF_NCTS_STABLE		0x0a20
#घोषणा NMVID_MEAS_STABLE		0x0a24
#घोषणा I2S_MEAS			0x0a40
#घोषणा SPDIF_MEAS			0x0a80
#घोषणा NMVID_MEAS			0x0ac0

/* source vअगर addr */
#घोषणा BND_HSYNC2VSYNC			0x0b00
#घोषणा HSYNC2VSYNC_F1_L1		0x0b04
#घोषणा HSYNC2VSYNC_F2_L1		0x0b08
#घोषणा HSYNC2VSYNC_STATUS		0x0b0c
#घोषणा HSYNC2VSYNC_POL_CTRL		0x0b10

/* dptx phy addr */
#घोषणा DP_TX_PHY_CONFIG_REG		0x2000
#घोषणा DP_TX_PHY_SW_RESET		0x2004
#घोषणा DP_TX_PHY_SCRAMBLER_SEED	0x2008
#घोषणा DP_TX_PHY_TRAINING_01_04	0x200c
#घोषणा DP_TX_PHY_TRAINING_05_08	0x2010
#घोषणा DP_TX_PHY_TRAINING_09_10	0x2014
#घोषणा TEST_COR			0x23fc

/* dptx hpd addr */
#घोषणा HPD_IRQ_DET_MIN_TIMER		0x2100
#घोषणा HPD_IRQ_DET_MAX_TIMER		0x2104
#घोषणा HPD_UNPLGED_DET_MIN_TIMER	0x2108
#घोषणा HPD_STABLE_TIMER		0x210c
#घोषणा HPD_FILTER_TIMER		0x2110
#घोषणा HPD_EVENT_MASK			0x211c
#घोषणा HPD_EVENT_DET			0x2120

/* dpyx framer addr */
#घोषणा DP_FRAMER_GLOBAL_CONFIG		0x2200
#घोषणा DP_SW_RESET			0x2204
#घोषणा DP_FRAMER_TU			0x2208
#घोषणा DP_FRAMER_PXL_REPR		0x220c
#घोषणा DP_FRAMER_SP			0x2210
#घोषणा AUDIO_PACK_CONTROL		0x2214
#घोषणा DP_VC_TABLE(x)			(0x2218 + ((x) << 2))
#घोषणा DP_VB_ID			0x2258
#घोषणा DP_MTPH_LVP_CONTROL		0x225c
#घोषणा DP_MTPH_SYMBOL_VALUES		0x2260
#घोषणा DP_MTPH_ECF_CONTROL		0x2264
#घोषणा DP_MTPH_ACT_CONTROL		0x2268
#घोषणा DP_MTPH_STATUS			0x226c
#घोषणा DP_INTERRUPT_SOURCE		0x2270
#घोषणा DP_INTERRUPT_MASK		0x2274
#घोषणा DP_FRONT_BACK_PORCH		0x2278
#घोषणा DP_BYTE_COUNT			0x227c

/* dptx stream addr */
#घोषणा MSA_HORIZONTAL_0		0x2280
#घोषणा MSA_HORIZONTAL_1		0x2284
#घोषणा MSA_VERTICAL_0			0x2288
#घोषणा MSA_VERTICAL_1			0x228c
#घोषणा MSA_MISC			0x2290
#घोषणा STREAM_CONFIG			0x2294
#घोषणा AUDIO_PACK_STATUS		0x2298
#घोषणा VIF_STATUS			0x229c
#घोषणा PCK_STUFF_STATUS_0		0x22a0
#घोषणा PCK_STUFF_STATUS_1		0x22a4
#घोषणा INFO_PACK_STATUS		0x22a8
#घोषणा RATE_GOVERNOR_STATUS		0x22ac
#घोषणा DP_HORIZONTAL			0x22b0
#घोषणा DP_VERTICAL_0			0x22b4
#घोषणा DP_VERTICAL_1			0x22b8
#घोषणा DP_BLOCK_SDP			0x22bc

/* dptx glbl addr */
#घोषणा DPTX_LANE_EN			0x2300
#घोषणा DPTX_ENHNCD			0x2304
#घोषणा DPTX_INT_MASK			0x2308
#घोषणा DPTX_INT_STATUS			0x230c

/* dp aux addr */
#घोषणा DP_AUX_HOST_CONTROL		0x2800
#घोषणा DP_AUX_INTERRUPT_SOURCE		0x2804
#घोषणा DP_AUX_INTERRUPT_MASK		0x2808
#घोषणा DP_AUX_SWAP_INVERSION_CONTROL	0x280c
#घोषणा DP_AUX_SEND_NACK_TRANSACTION	0x2810
#घोषणा DP_AUX_CLEAR_RX			0x2814
#घोषणा DP_AUX_CLEAR_TX			0x2818
#घोषणा DP_AUX_TIMER_STOP		0x281c
#घोषणा DP_AUX_TIMER_CLEAR		0x2820
#घोषणा DP_AUX_RESET_SW			0x2824
#घोषणा DP_AUX_DIVIDE_2M		0x2828
#घोषणा DP_AUX_TX_PREACHARGE_LENGTH	0x282c
#घोषणा DP_AUX_FREQUENCY_1M_MAX		0x2830
#घोषणा DP_AUX_FREQUENCY_1M_MIN		0x2834
#घोषणा DP_AUX_RX_PRE_MIN		0x2838
#घोषणा DP_AUX_RX_PRE_MAX		0x283c
#घोषणा DP_AUX_TIMER_PRESET		0x2840
#घोषणा DP_AUX_NACK_FORMAT		0x2844
#घोषणा DP_AUX_TX_DATA			0x2848
#घोषणा DP_AUX_RX_DATA			0x284c
#घोषणा DP_AUX_TX_STATUS		0x2850
#घोषणा DP_AUX_RX_STATUS		0x2854
#घोषणा DP_AUX_RX_CYCLE_COUNTER		0x2858
#घोषणा DP_AUX_MAIN_STATES		0x285c
#घोषणा DP_AUX_MAIN_TIMER		0x2860
#घोषणा DP_AUX_AFE_OUT			0x2864

/* crypto addr */
#घोषणा CRYPTO_HDCP_REVISION		0x5800
#घोषणा HDCP_CRYPTO_CONFIG		0x5804
#घोषणा CRYPTO_INTERRUPT_SOURCE		0x5808
#घोषणा CRYPTO_INTERRUPT_MASK		0x580c
#घोषणा CRYPTO22_CONFIG			0x5818
#घोषणा CRYPTO22_STATUS			0x581c
#घोषणा SHA_256_DATA_IN			0x583c
#घोषणा SHA_256_DATA_OUT_(x)		(0x5850 + ((x) << 2))
#घोषणा AES_32_KEY_(x)			(0x5870 + ((x) << 2))
#घोषणा AES_32_DATA_IN			0x5880
#घोषणा AES_32_DATA_OUT_(x)		(0x5884 + ((x) << 2))
#घोषणा CRYPTO14_CONFIG			0x58a0
#घोषणा CRYPTO14_STATUS			0x58a4
#घोषणा CRYPTO14_PRNM_OUT		0x58a8
#घोषणा CRYPTO14_KM_0			0x58ac
#घोषणा CRYPTO14_KM_1			0x58b0
#घोषणा CRYPTO14_AN_0			0x58b4
#घोषणा CRYPTO14_AN_1			0x58b8
#घोषणा CRYPTO14_YOUR_KSV_0		0x58bc
#घोषणा CRYPTO14_YOUR_KSV_1		0x58c0
#घोषणा CRYPTO14_MI_0			0x58c4
#घोषणा CRYPTO14_MI_1			0x58c8
#घोषणा CRYPTO14_TI_0			0x58cc
#घोषणा CRYPTO14_KI_0			0x58d0
#घोषणा CRYPTO14_KI_1			0x58d4
#घोषणा CRYPTO14_BLOCKS_NUM		0x58d8
#घोषणा CRYPTO14_KEY_MEM_DATA_0		0x58dc
#घोषणा CRYPTO14_KEY_MEM_DATA_1		0x58e0
#घोषणा CRYPTO14_SHA1_MSG_DATA		0x58e4
#घोषणा CRYPTO14_SHA1_V_VALUE_(x)	(0x58e8 + ((x) << 2))
#घोषणा TRNG_CTRL			0x58fc
#घोषणा TRNG_DATA_RDY			0x5900
#घोषणा TRNG_DATA			0x5904

/* cipher addr */
#घोषणा HDCP_REVISION			0x60000
#घोषणा INTERRUPT_SOURCE		0x60004
#घोषणा INTERRUPT_MASK			0x60008
#घोषणा HDCP_CIPHER_CONFIG		0x6000c
#घोषणा AES_128_KEY_0			0x60010
#घोषणा AES_128_KEY_1			0x60014
#घोषणा AES_128_KEY_2			0x60018
#घोषणा AES_128_KEY_3			0x6001c
#घोषणा AES_128_RANDOM_0		0x60020
#घोषणा AES_128_RANDOM_1		0x60024
#घोषणा CIPHER14_KM_0			0x60028
#घोषणा CIPHER14_KM_1			0x6002c
#घोषणा CIPHER14_STATUS			0x60030
#घोषणा CIPHER14_RI_PJ_STATUS		0x60034
#घोषणा CIPHER_MODE			0x60038
#घोषणा CIPHER14_AN_0			0x6003c
#घोषणा CIPHER14_AN_1			0x60040
#घोषणा CIPHER22_AUTH			0x60044
#घोषणा CIPHER14_R0_DP_STATUS		0x60048
#घोषणा CIPHER14_BOOTSTRAP		0x6004c

#घोषणा DPTX_FRMR_DATA_CLK_RSTN_EN	BIT(11)
#घोषणा DPTX_FRMR_DATA_CLK_EN		BIT(10)
#घोषणा DPTX_PHY_DATA_RSTN_EN		BIT(9)
#घोषणा DPTX_PHY_DATA_CLK_EN		BIT(8)
#घोषणा DPTX_PHY_CHAR_RSTN_EN		BIT(7)
#घोषणा DPTX_PHY_CHAR_CLK_EN		BIT(6)
#घोषणा SOURCE_AUX_SYS_CLK_RSTN_EN	BIT(5)
#घोषणा SOURCE_AUX_SYS_CLK_EN		BIT(4)
#घोषणा DPTX_SYS_CLK_RSTN_EN		BIT(3)
#घोषणा DPTX_SYS_CLK_EN			BIT(2)
#घोषणा CFG_DPTX_VIF_CLK_RSTN_EN	BIT(1)
#घोषणा CFG_DPTX_VIF_CLK_EN		BIT(0)

#घोषणा SOURCE_PHY_RSTN_EN		BIT(1)
#घोषणा SOURCE_PHY_CLK_EN		BIT(0)

#घोषणा SOURCE_PKT_SYS_RSTN_EN		BIT(3)
#घोषणा SOURCE_PKT_SYS_CLK_EN		BIT(2)
#घोषणा SOURCE_PKT_DATA_RSTN_EN		BIT(1)
#घोषणा SOURCE_PKT_DATA_CLK_EN		BIT(0)

#घोषणा SPDIF_CDR_CLK_RSTN_EN		BIT(5)
#घोषणा SPDIF_CDR_CLK_EN		BIT(4)
#घोषणा SOURCE_AIF_SYS_RSTN_EN		BIT(3)
#घोषणा SOURCE_AIF_SYS_CLK_EN		BIT(2)
#घोषणा SOURCE_AIF_CLK_RSTN_EN		BIT(1)
#घोषणा SOURCE_AIF_CLK_EN		BIT(0)

#घोषणा SOURCE_CIPHER_SYSTEM_CLK_RSTN_EN	BIT(3)
#घोषणा SOURCE_CIPHER_SYS_CLK_EN		BIT(2)
#घोषणा SOURCE_CIPHER_CHAR_CLK_RSTN_EN		BIT(1)
#घोषणा SOURCE_CIPHER_CHAR_CLK_EN		BIT(0)

#घोषणा SOURCE_CRYPTO_SYS_CLK_RSTN_EN	BIT(1)
#घोषणा SOURCE_CRYPTO_SYS_CLK_EN	BIT(0)

#घोषणा APB_IRAM_PATH			BIT(2)
#घोषणा APB_DRAM_PATH			BIT(1)
#घोषणा APB_XT_RESET			BIT(0)

#घोषणा MAILBOX_INT_MASK_BIT		BIT(1)
#घोषणा PIF_INT_MASK_BIT		BIT(0)
#घोषणा ALL_INT_MASK			3

/* mailbox */
#घोषणा MB_OPCODE_ID			0
#घोषणा MB_MODULE_ID			1
#घोषणा MB_SIZE_MSB_ID			2
#घोषणा MB_SIZE_LSB_ID			3
#घोषणा MB_DATA_ID			4

#घोषणा MB_MODULE_ID_DP_TX		0x01
#घोषणा MB_MODULE_ID_HDCP_TX		0x07
#घोषणा MB_MODULE_ID_HDCP_RX		0x08
#घोषणा MB_MODULE_ID_HDCP_GENERAL	0x09
#घोषणा MB_MODULE_ID_GENERAL		0x0a

/* general opcode */
#घोषणा GENERAL_MAIN_CONTROL            0x01
#घोषणा GENERAL_TEST_ECHO               0x02
#घोषणा GENERAL_BUS_SETTINGS            0x03
#घोषणा GENERAL_TEST_ACCESS             0x04

#घोषणा DPTX_SET_POWER_MNG			0x00
#घोषणा DPTX_SET_HOST_CAPABILITIES		0x01
#घोषणा DPTX_GET_EDID				0x02
#घोषणा DPTX_READ_DPCD				0x03
#घोषणा DPTX_WRITE_DPCD				0x04
#घोषणा DPTX_ENABLE_EVENT			0x05
#घोषणा DPTX_WRITE_REGISTER			0x06
#घोषणा DPTX_READ_REGISTER			0x07
#घोषणा DPTX_WRITE_FIELD			0x08
#घोषणा DPTX_TRAINING_CONTROL			0x09
#घोषणा DPTX_READ_EVENT				0x0a
#घोषणा DPTX_READ_LINK_STAT			0x0b
#घोषणा DPTX_SET_VIDEO				0x0c
#घोषणा DPTX_SET_AUDIO				0x0d
#घोषणा DPTX_GET_LAST_AUX_STAUS			0x0e
#घोषणा DPTX_SET_LINK_BREAK_POINT		0x0f
#घोषणा DPTX_FORCE_LANES			0x10
#घोषणा DPTX_HPD_STATE				0x11

#घोषणा FW_STANDBY				0
#घोषणा FW_ACTIVE				1

#घोषणा DPTX_EVENT_ENABLE_HPD			BIT(0)
#घोषणा DPTX_EVENT_ENABLE_TRAINING		BIT(1)

#घोषणा LINK_TRAINING_NOT_ACTIVE		0
#घोषणा LINK_TRAINING_RUN			1
#घोषणा LINK_TRAINING_RESTART			2

#घोषणा CONTROL_VIDEO_IDLE			0
#घोषणा CONTROL_VIDEO_VALID			1

#घोषणा TU_CNT_RST_EN				BIT(15)
#घोषणा VIF_BYPASS_INTERLACE			BIT(13)
#घोषणा INTERLACE_FMT_DET			BIT(12)
#घोषणा INTERLACE_DTCT_WIN			0x20

#घोषणा DP_FRAMER_SP_INTERLACE_EN		BIT(2)
#घोषणा DP_FRAMER_SP_HSP			BIT(1)
#घोषणा DP_FRAMER_SP_VSP			BIT(0)

/* capability */
#घोषणा AUX_HOST_INVERT				3
#घोषणा	FAST_LT_SUPPORT				1
#घोषणा FAST_LT_NOT_SUPPORT			0
#घोषणा LANE_MAPPING_NORMAL			0x1b
#घोषणा LANE_MAPPING_FLIPPED			0xe4
#घोषणा ENHANCED				1
#घोषणा SCRAMBLER_EN				BIT(4)

#घोषणा	FULL_LT_STARTED				BIT(0)
#घोषणा FASE_LT_STARTED				BIT(1)
#घोषणा CLK_RECOVERY_FINISHED			BIT(2)
#घोषणा EQ_PHASE_FINISHED			BIT(3)
#घोषणा FASE_LT_START_FINISHED			BIT(4)
#घोषणा CLK_RECOVERY_FAILED			BIT(5)
#घोषणा EQ_PHASE_FAILED				BIT(6)
#घोषणा FASE_LT_FAILED				BIT(7)

#घोषणा DPTX_HPD_EVENT				BIT(0)
#घोषणा DPTX_TRAINING_EVENT			BIT(1)
#घोषणा HDCP_TX_STATUS_EVENT			BIT(4)
#घोषणा HDCP2_TX_IS_KM_STORED_EVENT		BIT(5)
#घोषणा HDCP2_TX_STORE_KM_EVENT			BIT(6)
#घोषणा HDCP_TX_IS_RECEIVER_ID_VALID_EVENT	BIT(7)

#घोषणा TU_SIZE					30
#घोषणा CDN_DP_MAX_LINK_RATE			DP_LINK_BW_5_4

/* audio */
#घोषणा AUDIO_PACK_EN				BIT(8)
#घोषणा SAMPLING_FREQ(x)			(((x) & 0xf) << 16)
#घोषणा ORIGINAL_SAMP_FREQ(x)			(((x) & 0xf) << 24)
#घोषणा SYNC_WR_TO_CH_ZERO			BIT(1)
#घोषणा I2S_DEC_START				BIT(1)
#घोषणा AUDIO_SW_RST				BIT(0)
#घोषणा SMPL2PKT_EN				BIT(1)
#घोषणा MAX_NUM_CH(x)				(((x) & 0x1f) - 1)
#घोषणा NUM_OF_I2S_PORTS(x)			((((x) / 2 - 1) & 0x3) << 5)
#घोषणा AUDIO_TYPE_LPCM				(2 << 7)
#घोषणा CFG_SUB_PCKT_NUM(x)			((((x) - 1) & 0x7) << 11)
#घोषणा AUDIO_CH_NUM(x)				((((x) - 1) & 0x1f) << 2)
#घोषणा TRANS_SMPL_WIDTH_16			0
#घोषणा TRANS_SMPL_WIDTH_24			BIT(11)
#घोषणा TRANS_SMPL_WIDTH_32			(2 << 11)
#घोषणा I2S_DEC_PORT_EN(x)			(((x) & 0xf) << 17)
#घोषणा SPDIF_ENABLE				BIT(21)
#घोषणा SPDIF_AVG_SEL				BIT(20)
#घोषणा SPDIF_JITTER_BYPASS			BIT(19)
#घोषणा SPDIF_FIFO_MID_RANGE(x)			(((x) & 0xff) << 11)
#घोषणा SPDIF_JITTER_THRSH(x)			(((x) & 0xff) << 3)
#घोषणा SPDIF_JITTER_AVG_WIN(x)			((x) & 0x7)

/* Reference cycles when using lane घड़ी as reference */
#घोषणा LANE_REF_CYC				0x8000

क्रमागत voltage_swing_level अणु
	VOLTAGE_LEVEL_0,
	VOLTAGE_LEVEL_1,
	VOLTAGE_LEVEL_2,
	VOLTAGE_LEVEL_3,
पूर्ण;

क्रमागत pre_emphasis_level अणु
	PRE_EMPHASIS_LEVEL_0,
	PRE_EMPHASIS_LEVEL_1,
	PRE_EMPHASIS_LEVEL_2,
	PRE_EMPHASIS_LEVEL_3,
पूर्ण;

क्रमागत pattern_set अणु
	PTS1		= BIT(0),
	PTS2		= BIT(1),
	PTS3		= BIT(2),
	PTS4		= BIT(3),
	DP_NONE		= BIT(4)
पूर्ण;

क्रमागत vic_color_depth अणु
	BCS_6 = 0x1,
	BCS_8 = 0x2,
	BCS_10 = 0x4,
	BCS_12 = 0x8,
	BCS_16 = 0x10,
पूर्ण;

क्रमागत vic_bt_type अणु
	BT_601 = 0x0,
	BT_709 = 0x1,
पूर्ण;

व्योम cdn_dp_घड़ी_reset(काष्ठा cdn_dp_device *dp);

व्योम cdn_dp_set_fw_clk(काष्ठा cdn_dp_device *dp, अचिन्हित दीर्घ clk);
पूर्णांक cdn_dp_load_firmware(काष्ठा cdn_dp_device *dp, स्थिर u32 *i_mem,
			 u32 i_size, स्थिर u32 *d_mem, u32 d_size);
पूर्णांक cdn_dp_set_firmware_active(काष्ठा cdn_dp_device *dp, bool enable);
पूर्णांक cdn_dp_set_host_cap(काष्ठा cdn_dp_device *dp, u8 lanes, bool flip);
पूर्णांक cdn_dp_event_config(काष्ठा cdn_dp_device *dp);
u32 cdn_dp_get_event(काष्ठा cdn_dp_device *dp);
पूर्णांक cdn_dp_get_hpd_status(काष्ठा cdn_dp_device *dp);
पूर्णांक cdn_dp_dpcd_ग_लिखो(काष्ठा cdn_dp_device *dp, u32 addr, u8 value);
पूर्णांक cdn_dp_dpcd_पढ़ो(काष्ठा cdn_dp_device *dp, u32 addr, u8 *data, u16 len);
पूर्णांक cdn_dp_get_edid_block(व्योम *dp, u8 *edid,
			  अचिन्हित पूर्णांक block, माप_प्रकार length);
पूर्णांक cdn_dp_train_link(काष्ठा cdn_dp_device *dp);
पूर्णांक cdn_dp_set_video_status(काष्ठा cdn_dp_device *dp, पूर्णांक active);
पूर्णांक cdn_dp_config_video(काष्ठा cdn_dp_device *dp);
पूर्णांक cdn_dp_audio_stop(काष्ठा cdn_dp_device *dp, काष्ठा audio_info *audio);
पूर्णांक cdn_dp_audio_mute(काष्ठा cdn_dp_device *dp, bool enable);
पूर्णांक cdn_dp_audio_config(काष्ठा cdn_dp_device *dp, काष्ठा audio_info *audio);
#पूर्ण_अगर /* _CDN_DP_REG_H */
