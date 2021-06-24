<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Gateworks Corporation
 */

/* Page 0x00 - General Control */
#घोषणा REG_VERSION		0x0000
#घोषणा REG_INPUT_SEL		0x0001
#घोषणा REG_SVC_MODE		0x0002
#घोषणा REG_HPD_MAN_CTRL	0x0003
#घोषणा REG_RT_MAN_CTRL		0x0004
#घोषणा REG_STANDBY_SOFT_RST	0x000A
#घोषणा REG_HDMI_SOFT_RST	0x000B
#घोषणा REG_HDMI_INFO_RST	0x000C
#घोषणा REG_INT_FLG_CLR_TOP	0x000E
#घोषणा REG_INT_FLG_CLR_SUS	0x000F
#घोषणा REG_INT_FLG_CLR_DDC	0x0010
#घोषणा REG_INT_FLG_CLR_RATE	0x0011
#घोषणा REG_INT_FLG_CLR_MODE	0x0012
#घोषणा REG_INT_FLG_CLR_INFO	0x0013
#घोषणा REG_INT_FLG_CLR_AUDIO	0x0014
#घोषणा REG_INT_FLG_CLR_HDCP	0x0015
#घोषणा REG_INT_FLG_CLR_AFE	0x0016
#घोषणा REG_INT_MASK_TOP	0x0017
#घोषणा REG_INT_MASK_SUS	0x0018
#घोषणा REG_INT_MASK_DDC	0x0019
#घोषणा REG_INT_MASK_RATE	0x001A
#घोषणा REG_INT_MASK_MODE	0x001B
#घोषणा REG_INT_MASK_INFO	0x001C
#घोषणा REG_INT_MASK_AUDIO	0x001D
#घोषणा REG_INT_MASK_HDCP	0x001E
#घोषणा REG_INT_MASK_AFE	0x001F
#घोषणा REG_DETECT_5V		0x0020
#घोषणा REG_SUS_STATUS		0x0021
#घोषणा REG_V_PER		0x0022
#घोषणा REG_H_PER		0x0025
#घोषणा REG_HS_WIDTH		0x0027
#घोषणा REG_FMT_H_TOT		0x0029
#घोषणा REG_FMT_H_ACT		0x002b
#घोषणा REG_FMT_H_FRONT		0x002d
#घोषणा REG_FMT_H_SYNC		0x002f
#घोषणा REG_FMT_H_BACK		0x0031
#घोषणा REG_FMT_V_TOT		0x0033
#घोषणा REG_FMT_V_ACT		0x0035
#घोषणा REG_FMT_V_FRONT_F1	0x0037
#घोषणा REG_FMT_V_FRONT_F2	0x0038
#घोषणा REG_FMT_V_SYNC		0x0039
#घोषणा REG_FMT_V_BACK_F1	0x003a
#घोषणा REG_FMT_V_BACK_F2	0x003b
#घोषणा REG_FMT_DE_ACT		0x003c
#घोषणा REG_RATE_CTRL		0x0040
#घोषणा REG_CLK_MIN_RATE	0x0043
#घोषणा REG_CLK_MAX_RATE	0x0046
#घोषणा REG_CLK_A_STATUS	0x0049
#घोषणा REG_CLK_A_RATE		0x004A
#घोषणा REG_DRIFT_CLK_A_REG	0x004D
#घोषणा REG_CLK_B_STATUS	0x004E
#घोषणा REG_CLK_B_RATE		0x004F
#घोषणा REG_DRIFT_CLK_B_REG	0x0052
#घोषणा REG_HDCP_CTRL		0x0060
#घोषणा REG_HDCP_KDS		0x0061
#घोषणा REG_HDCP_BCAPS		0x0063
#घोषणा REG_HDCP_KEY_CTRL	0x0064
#घोषणा REG_INFO_CTRL		0x0076
#घोषणा REG_INFO_EXCEED		0x0077
#घोषणा REG_PIX_REPEAT		0x007B
#घोषणा REG_AUDIO_PATH		0x007C
#घोषणा REG_AUDCFG		0x007D
#घोषणा REG_AUDIO_OUT_ENABLE	0x007E
#घोषणा REG_AUDIO_OUT_HIZ	0x007F
#घोषणा REG_VDP_CTRL		0x0080
#घोषणा REG_VDP_MATRIX		0x0081
#घोषणा REG_VHREF_CTRL		0x00A0
#घोषणा REG_PXCNT_PR		0x00A2
#घोषणा REG_PXCNT_NPIX		0x00A4
#घोषणा REG_LCNT_PR		0x00A6
#घोषणा REG_LCNT_NLIN		0x00A8
#घोषणा REG_HREF_S		0x00AA
#घोषणा REG_HREF_E		0x00AC
#घोषणा REG_HS_S		0x00AE
#घोषणा REG_HS_E		0x00B0
#घोषणा REG_VREF_F1_S		0x00B2
#घोषणा REG_VREF_F1_WIDTH	0x00B4
#घोषणा REG_VREF_F2_S		0x00B5
#घोषणा REG_VREF_F2_WIDTH	0x00B7
#घोषणा REG_VS_F1_LINE_S	0x00B8
#घोषणा REG_VS_F1_LINE_WIDTH	0x00BA
#घोषणा REG_VS_F2_LINE_S	0x00BB
#घोषणा REG_VS_F2_LINE_WIDTH	0x00BD
#घोषणा REG_VS_F1_PIX_S		0x00BE
#घोषणा REG_VS_F1_PIX_E		0x00C0
#घोषणा REG_VS_F2_PIX_S		0x00C2
#घोषणा REG_VS_F2_PIX_E		0x00C4
#घोषणा REG_FREF_F1_S		0x00C6
#घोषणा REG_FREF_F2_S		0x00C8
#घोषणा REG_FDW_S		0x00ca
#घोषणा REG_FDW_E		0x00cc
#घोषणा REG_BLK_GY		0x00da
#घोषणा REG_BLK_BU		0x00dc
#घोषणा REG_BLK_RV		0x00de
#घोषणा REG_FILTERS_CTRL	0x00e0
#घोषणा REG_DITHERING_CTRL	0x00E9
#घोषणा REG_OF			0x00EA
#घोषणा REG_PCLK		0x00EB
#घोषणा REG_HS_HREF		0x00EC
#घोषणा REG_VS_VREF		0x00ED
#घोषणा REG_DE_FREF		0x00EE
#घोषणा REG_VP35_32_CTRL	0x00EF
#घोषणा REG_VP31_28_CTRL	0x00F0
#घोषणा REG_VP27_24_CTRL	0x00F1
#घोषणा REG_VP23_20_CTRL	0x00F2
#घोषणा REG_VP19_16_CTRL	0x00F3
#घोषणा REG_VP15_12_CTRL	0x00F4
#घोषणा REG_VP11_08_CTRL	0x00F5
#घोषणा REG_VP07_04_CTRL	0x00F6
#घोषणा REG_VP03_00_CTRL	0x00F7
#घोषणा REG_CURPAGE_00H		0xFF

#घोषणा MASK_VPER		0x3fffff
#घोषणा MASK_VHREF		0x3fff
#घोषणा MASK_HPER		0x0fff
#घोषणा MASK_HSWIDTH		0x03ff

/* HPD Detection */
#घोषणा DETECT_UTIL		BIT(7)	/* utility of HDMI level */
#घोषणा DETECT_HPD		BIT(6)	/* HPD of HDMI level */
#घोषणा DETECT_5V_SEL		BIT(2)	/* 5V present on selected input */
#घोषणा DETECT_5V_B		BIT(1)	/* 5V present on input B */
#घोषणा DETECT_5V_A		BIT(0)	/* 5V present on input A */

/* Input Select */
#घोषणा INPUT_SEL_RST_FMT	BIT(7)	/* 1=reset क्रमmat measurement */
#घोषणा INPUT_SEL_RST_VDP	BIT(2)	/* 1=reset video data path */
#घोषणा INPUT_SEL_OUT_MODE	BIT(1)	/* 0=loop 1=bypass */
#घोषणा INPUT_SEL_B		BIT(0)	/* 0=inputA 1=inputB */

/* Service Mode */
#घोषणा SVC_MODE_CLK2_MASK	0xc0
#घोषणा SVC_MODE_CLK2_SHIFT	6
#घोषणा SVC_MODE_CLK2_XTL	0L
#घोषणा SVC_MODE_CLK2_XTLDIV2	1L
#घोषणा SVC_MODE_CLK2_HDMIX2	3L
#घोषणा SVC_MODE_CLK1_MASK	0x30
#घोषणा SVC_MODE_CLK1_SHIFT	4
#घोषणा SVC_MODE_CLK1_XTAL	0L
#घोषणा SVC_MODE_CLK1_XTLDIV2	1L
#घोषणा SVC_MODE_CLK1_HDMI	3L
#घोषणा SVC_MODE_RAMP		BIT(3)	/* 0=colorbar 1=ramp */
#घोषणा SVC_MODE_PAL		BIT(2)	/* 0=NTSC(480i/p) 1=PAL(576i/p) */
#घोषणा SVC_MODE_INT_PROG	BIT(1)	/* 0=पूर्णांकerlaced 1=progressive */
#घोषणा SVC_MODE_SM_ON		BIT(0)	/* Enable color bars and tone gen */

/* HDP Manual Control */
#घोषणा HPD_MAN_CTRL_HPD_PULSE	BIT(7)	/* HPD Pulse low 110ms */
#घोषणा HPD_MAN_CTRL_5VEN	BIT(2)	/* Output 5V */
#घोषणा HPD_MAN_CTRL_HPD_B	BIT(1)	/* Assert HPD High क्रम Input A */
#घोषणा HPD_MAN_CTRL_HPD_A	BIT(0)	/* Assert HPD High क्रम Input A */

/* RT_MAN_CTRL */
#घोषणा RT_MAN_CTRL_RT_AUTO	BIT(7)
#घोषणा RT_MAN_CTRL_RT		BIT(6)
#घोषणा RT_MAN_CTRL_RT_B	BIT(1)	/* enable TMDS pull-up on Input B */
#घोषणा RT_MAN_CTRL_RT_A	BIT(0)	/* enable TMDS pull-up on Input A */

/* VDP_CTRL */
#घोषणा VDP_CTRL_COMPDEL_BP	BIT(5)	/* bypass compdel */
#घोषणा VDP_CTRL_FORMATTER_BP	BIT(4)	/* bypass क्रमmatter */
#घोषणा VDP_CTRL_PREFILTER_BP	BIT(1)	/* bypass prefilter */
#घोषणा VDP_CTRL_MATRIX_BP	BIT(0)	/* bypass matrix conversion */

/* REG_VHREF_CTRL */
#घोषणा VHREF_INT_DET		BIT(7)	/* पूर्णांकerlace detect: 1=alt 0=frame */
#घोषणा VHREF_VSYNC_MASK	0x60
#घोषणा VHREF_VSYNC_SHIFT	6
#घोषणा VHREF_VSYNC_AUTO	0L
#घोषणा VHREF_VSYNC_FDW		1L
#घोषणा VHREF_VSYNC_EVEN	2L
#घोषणा VHREF_VSYNC_ODD		3L
#घोषणा VHREF_STD_DET_MASK	0x18
#घोषणा VHREF_STD_DET_SHIFT	3
#घोषणा VHREF_STD_DET_PAL	0L
#घोषणा VHREF_STD_DET_NTSC	1L
#घोषणा VHREF_STD_DET_AUTO	2L
#घोषणा VHREF_STD_DET_OFF	3L
#घोषणा VHREF_VREF_SRC_STD	BIT(2)	/* 1=from standard 0=manual */
#घोषणा VHREF_HREF_SRC_STD	BIT(1)	/* 1=from standard 0=manual */
#घोषणा VHREF_HSYNC_SEL_HS	BIT(0)	/* 1=HS 0=VS */

/* AUDIO_OUT_ENABLE */
#घोषणा AUDIO_OUT_ENABLE_ACLK	BIT(5)
#घोषणा AUDIO_OUT_ENABLE_WS	BIT(4)
#घोषणा AUDIO_OUT_ENABLE_AP3	BIT(3)
#घोषणा AUDIO_OUT_ENABLE_AP2	BIT(2)
#घोषणा AUDIO_OUT_ENABLE_AP1	BIT(1)
#घोषणा AUDIO_OUT_ENABLE_AP0	BIT(0)

/* Prefilter Control */
#घोषणा FILTERS_CTRL_BU_MASK	0x0c
#घोषणा FILTERS_CTRL_BU_SHIFT	2
#घोषणा FILTERS_CTRL_RV_MASK	0x03
#घोषणा FILTERS_CTRL_RV_SHIFT	0
#घोषणा FILTERS_CTRL_OFF	0L	/* off */
#घोषणा FILTERS_CTRL_2TAP	1L	/* 2 Taps */
#घोषणा FILTERS_CTRL_7TAP	2L	/* 7 Taps */
#घोषणा FILTERS_CTRL_2_7TAP	3L	/* 2/7 Taps */

/* PCLK Configuration */
#घोषणा PCLK_DELAY_MASK		0x70
#घोषणा PCLK_DELAY_SHIFT	4	/* Pixel delay (-8..+7) */
#घोषणा PCLK_INV_SHIFT		2
#घोषणा PCLK_SEL_MASK		0x03	/* घड़ी scaler */
#घोषणा PCLK_SEL_SHIFT		0
#घोषणा PCLK_SEL_X1		0L
#घोषणा PCLK_SEL_X2		1L
#घोषणा PCLK_SEL_DIV2		2L
#घोषणा PCLK_SEL_DIV4		3L

/* Pixel Repeater */
#घोषणा PIX_REPEAT_MASK_UP_SEL	0x30
#घोषणा PIX_REPEAT_MASK_REP	0x0f
#घोषणा PIX_REPEAT_SHIFT	4
#घोषणा PIX_REPEAT_CHROMA	1

/* Page 0x01 - HDMI info and packets */
#घोषणा REG_HDMI_FLAGS		0x0100
#घोषणा REG_DEEP_COLOR_MODE	0x0101
#घोषणा REG_AUDIO_FLAGS		0x0108
#घोषणा REG_AUDIO_FREQ		0x0109
#घोषणा REG_ACP_PACKET_TYPE	0x0141
#घोषणा REG_ISRC1_PACKET_TYPE	0x0161
#घोषणा REG_ISRC2_PACKET_TYPE	0x0181
#घोषणा REG_GBD_PACKET_TYPE	0x01a1

/* HDMI_FLAGS */
#घोषणा HDMI_FLAGS_AUDIO	BIT(7)	/* Audio packet in last videoframe */
#घोषणा HDMI_FLAGS_HDMI		BIT(6)	/* HDMI detected */
#घोषणा HDMI_FLAGS_EESS		BIT(5)	/* EESS detected */
#घोषणा HDMI_FLAGS_HDCP		BIT(4)	/* HDCP detected */
#घोषणा HDMI_FLAGS_AVMUTE	BIT(3)	/* AVMUTE */
#घोषणा HDMI_FLAGS_AUD_LAYOUT	BIT(2)	/* Layout status Audio sample packet */
#घोषणा HDMI_FLAGS_AUD_FIFO_OF	BIT(1)	/* FIFO पढ़ो/ग_लिखो poपूर्णांकers crossed */
#घोषणा HDMI_FLAGS_AUD_FIFO_LOW	BIT(0)	/* FIFO पढ़ो ptr within 2 of ग_लिखो */

/* Page 0x12 - HDMI Extra control and debug */
#घोषणा REG_CLK_CFG		0x1200
#घोषणा REG_CLK_OUT_CFG		0x1201
#घोषणा REG_CFG1		0x1202
#घोषणा REG_CFG2		0x1203
#घोषणा REG_WDL_CFG		0x1210
#घोषणा REG_DELOCK_DELAY	0x1212
#घोषणा REG_PON_OVR_EN		0x12A0
#घोषणा REG_PON_CBIAS		0x12A1
#घोषणा REG_PON_RESCAL		0x12A2
#घोषणा REG_PON_RES		0x12A3
#घोषणा REG_PON_CLK		0x12A4
#घोषणा REG_PON_PLL		0x12A5
#घोषणा REG_PON_EQ		0x12A6
#घोषणा REG_PON_DES		0x12A7
#घोषणा REG_PON_OUT		0x12A8
#घोषणा REG_PON_MUX		0x12A9
#घोषणा REG_MODE_REC_CFG1	0x12F8
#घोषणा REG_MODE_REC_CFG2	0x12F9
#घोषणा REG_MODE_REC_STS	0x12FA
#घोषणा REG_AUDIO_LAYOUT	0x12D0

#घोषणा PON_EN			1
#घोषणा PON_DIS			0

/* CLK CFG */
#घोषणा CLK_CFG_INV_OUT_CLK	BIT(7)
#घोषणा CLK_CFG_INV_BUS_CLK	BIT(6)
#घोषणा CLK_CFG_SEL_ACLK_EN	BIT(1)
#घोषणा CLK_CFG_SEL_ACLK	BIT(0)
#घोषणा CLK_CFG_DIS		0

/* Page 0x13 - HDMI Extra control and debug */
#घोषणा REG_DEEP_COLOR_CTRL	0x1300
#घोषणा REG_CGU_DBG_SEL		0x1305
#घोषणा REG_HDCP_DDC_ADDR	0x1310
#घोषणा REG_HDCP_KIDX		0x1316
#घोषणा REG_DEEP_PLL7_BYP	0x1347
#घोषणा REG_HDCP_DE_CTRL	0x1370
#घोषणा REG_HDCP_EP_FILT_CTRL	0x1371
#घोषणा REG_HDMI_CTRL		0x1377
#घोषणा REG_HMTP_CTRL		0x137a
#घोषणा REG_TIMER_D		0x13CF
#घोषणा REG_SUS_SET_RGB0	0x13E1
#घोषणा REG_SUS_SET_RGB1	0x13E2
#घोषणा REG_SUS_SET_RGB2	0x13E3
#घोषणा REG_SUS_SET_RGB3	0x13E4
#घोषणा REG_SUS_SET_RGB4	0x13E5
#घोषणा REG_MAN_SUS_HDMI_SEL	0x13E8
#घोषणा REG_MAN_HDMI_SET	0x13E9
#घोषणा REG_SUS_CLOCK_GOOD	0x13EF

/* HDCP DE Control */
#घोषणा HDCP_DE_MODE_MASK	0xc0	/* DE Measurement mode */
#घोषणा HDCP_DE_MODE_SHIFT	6
#घोषणा HDCP_DE_REGEN_EN	BIT(5)	/* enable regen mode */
#घोषणा HDCP_DE_FILTER_MASK	0x18	/* DE filter sensitivity */
#घोषणा HDCP_DE_FILTER_SHIFT	3
#घोषणा HDCP_DE_COMP_MASK	0x07	/* DE Composition mode */
#घोषणा HDCP_DE_COMP_MIXED	6L
#घोषणा HDCP_DE_COMP_OR		5L
#घोषणा HDCP_DE_COMP_AND	4L
#घोषणा HDCP_DE_COMP_CH3	3L
#घोषणा HDCP_DE_COMP_CH2	2L
#घोषणा HDCP_DE_COMP_CH1	1L
#घोषणा HDCP_DE_COMP_CH0	0L

/* HDCP EP Filter Control */
#घोषणा HDCP_EP_FIL_CTL_MASK	0x30
#घोषणा HDCP_EP_FIL_CTL_SHIFT	4
#घोषणा HDCP_EP_FIL_VS_MASK	0x0c
#घोषणा HDCP_EP_FIL_VS_SHIFT	2
#घोषणा HDCP_EP_FIL_HS_MASK	0x03
#घोषणा HDCP_EP_FIL_HS_SHIFT	0

/* HDMI_CTRL */
#घोषणा HDMI_CTRL_MUTE_MASK	0x0c
#घोषणा HDMI_CTRL_MUTE_SHIFT	2
#घोषणा HDMI_CTRL_MUTE_AUTO	0L
#घोषणा HDMI_CTRL_MUTE_OFF	1L
#घोषणा HDMI_CTRL_MUTE_ON	2L
#घोषणा HDMI_CTRL_HDCP_MASK	0x03
#घोषणा HDMI_CTRL_HDCP_SHIFT	0
#घोषणा HDMI_CTRL_HDCP_EESS	2L
#घोषणा HDMI_CTRL_HDCP_OESS	1L
#घोषणा HDMI_CTRL_HDCP_AUTO	0L

/* CGU_DBG_SEL bits */
#घोषणा CGU_DBG_CLK_SEL_MASK	0x18
#घोषणा CGU_DBG_CLK_SEL_SHIFT	3
#घोषणा CGU_DBG_XO_FRO_SEL	BIT(2)
#घोषणा CGU_DBG_VDP_CLK_SEL	BIT(1)
#घोषणा CGU_DBG_PIX_CLK_SEL	BIT(0)

/* REG_MAN_SUS_HDMI_SEL / REG_MAN_HDMI_SET bits */
#घोषणा MAN_DIS_OUT_BUF		BIT(7)
#घोषणा MAN_DIS_ANA_PATH	BIT(6)
#घोषणा MAN_DIS_HDCP		BIT(5)
#घोषणा MAN_DIS_TMDS_ENC	BIT(4)
#घोषणा MAN_DIS_TMDS_FLOW	BIT(3)
#घोषणा MAN_RST_HDCP		BIT(2)
#घोषणा MAN_RST_TMDS_ENC	BIT(1)
#घोषणा MAN_RST_TMDS_FLOW	BIT(0)

/* Page 0x14 - Audio Extra control and debug */
#घोषणा REG_FIFO_LATENCY_VAL	0x1403
#घोषणा REG_AUDIO_CLOCK		0x1411
#घोषणा REG_TEST_NCTS_CTRL	0x1415
#घोषणा REG_TEST_AUDIO_FREQ	0x1426
#घोषणा REG_TEST_MODE		0x1437

/* Audio Clock Configuration */
#घोषणा AUDIO_CLOCK_PLL_PD	BIT(7)	/* घातerकरोwn PLL */
#घोषणा AUDIO_CLOCK_SEL_MASK	0x7f
#घोषणा AUDIO_CLOCK_SEL_16FS	0L	/* 16*fs */
#घोषणा AUDIO_CLOCK_SEL_32FS	1L	/* 32*fs */
#घोषणा AUDIO_CLOCK_SEL_64FS	2L	/* 64*fs */
#घोषणा AUDIO_CLOCK_SEL_128FS	3L	/* 128*fs */
#घोषणा AUDIO_CLOCK_SEL_256FS	4L	/* 256*fs */
#घोषणा AUDIO_CLOCK_SEL_512FS	5L	/* 512*fs */

/* Page 0x20: EDID and Hotplug Detect */
#घोषणा REG_EDID_IN_BYTE0	0x2000 /* EDID base */
#घोषणा REG_EDID_IN_VERSION	0x2080
#घोषणा REG_EDID_ENABLE		0x2081
#घोषणा REG_HPD_POWER		0x2084
#घोषणा REG_HPD_AUTO_CTRL	0x2085
#घोषणा REG_HPD_DURATION	0x2086
#घोषणा REG_RX_HPD_HEAC		0x2087

/* EDID_ENABLE */
#घोषणा EDID_ENABLE_NACK_OFF	BIT(7)
#घोषणा EDID_ENABLE_EDID_ONLY	BIT(6)
#घोषणा EDID_ENABLE_B_EN	BIT(1)
#घोषणा EDID_ENABLE_A_EN	BIT(0)

/* HPD Power */
#घोषणा HPD_POWER_BP_MASK	0x0c
#घोषणा HPD_POWER_BP_SHIFT	2
#घोषणा HPD_POWER_BP_LOW	0L
#घोषणा HPD_POWER_BP_HIGH	1L
#घोषणा HPD_POWER_EDID_ONLY	BIT(1)

/* HPD Auto control */
#घोषणा HPD_AUTO_READ_EDID	BIT(7)
#घोषणा HPD_AUTO_HPD_F3TECH	BIT(5)
#घोषणा HPD_AUTO_HP_OTHER	BIT(4)
#घोषणा HPD_AUTO_HPD_UNSEL	BIT(3)
#घोषणा HPD_AUTO_HPD_ALL_CH	BIT(2)
#घोषणा HPD_AUTO_HPD_PRV_CH	BIT(1)
#घोषणा HPD_AUTO_HPD_NEW_CH	BIT(0)

/* Page 0x21 - EDID content */
#घोषणा REG_EDID_IN_BYTE128	0x2100 /* CEA Extension block */
#घोषणा REG_EDID_IN_SPA_SUB	0x2180
#घोषणा REG_EDID_IN_SPA_AB_A	0x2181
#घोषणा REG_EDID_IN_SPA_CD_A	0x2182
#घोषणा REG_EDID_IN_CKSUM_A	0x2183
#घोषणा REG_EDID_IN_SPA_AB_B	0x2184
#घोषणा REG_EDID_IN_SPA_CD_B	0x2185
#घोषणा REG_EDID_IN_CKSUM_B	0x2186

/* Page 0x30 - NV Configuration */
#घोषणा REG_RT_AUTO_CTRL	0x3000
#घोषणा REG_EQ_MAN_CTRL0	0x3001
#घोषणा REG_EQ_MAN_CTRL1	0x3002
#घोषणा REG_OUTPUT_CFG		0x3003
#घोषणा REG_MUTE_CTRL		0x3004
#घोषणा REG_SLAVE_ADDR		0x3005
#घोषणा REG_CMTP_REG6		0x3006
#घोषणा REG_CMTP_REG7		0x3007
#घोषणा REG_CMTP_REG8		0x3008
#घोषणा REG_CMTP_REG9		0x3009
#घोषणा REG_CMTP_REGA		0x300A
#घोषणा REG_CMTP_REGB		0x300B
#घोषणा REG_CMTP_REGC		0x300C
#घोषणा REG_CMTP_REGD		0x300D
#घोषणा REG_CMTP_REGE		0x300E
#घोषणा REG_CMTP_REGF		0x300F
#घोषणा REG_CMTP_REG10		0x3010
#घोषणा REG_CMTP_REG11		0x3011

/* Page 0x80 - CEC */
#घोषणा REG_PWR_CONTROL		0x80F4
#घोषणा REG_OSC_DIVIDER		0x80F5
#घोषणा REG_EN_OSC_PERIOD_LSB	0x80F8
#घोषणा REG_CONTROL		0x80FF

/* global पूर्णांकerrupt flags (INT_FLG_CRL_TOP) */
#घोषणा INTERRUPT_AFE		BIT(7) /* AFE module */
#घोषणा INTERRUPT_HDCP		BIT(6) /* HDCP module */
#घोषणा INTERRUPT_AUDIO		BIT(5) /* Audio module */
#घोषणा INTERRUPT_INFO		BIT(4) /* Infoframe module */
#घोषणा INTERRUPT_MODE		BIT(3) /* HDMI mode module */
#घोषणा INTERRUPT_RATE		BIT(2) /* rate module */
#घोषणा INTERRUPT_DDC		BIT(1) /* DDC module */
#घोषणा INTERRUPT_SUS		BIT(0) /* SUS module */

/* INT_FLG_CLR_HDCP bits */
#घोषणा MASK_HDCP_MTP		BIT(7) /* HDCP MTP busy */
#घोषणा MASK_HDCP_DLMTP		BIT(4) /* HDCP end करोwnload MTP to SRAM */
#घोषणा MASK_HDCP_DLRAM		BIT(3) /* HDCP end करोwnload keys from SRAM */
#घोषणा MASK_HDCP_ENC		BIT(2) /* HDCP ENC */
#घोषणा MASK_STATE_C5		BIT(1) /* HDCP State C5 reached */
#घोषणा MASK_AKSV		BIT(0) /* AKSV received (start of auth) */

/* INT_FLG_CLR_RATE bits */
#घोषणा MASK_RATE_B_DRIFT	BIT(7) /* Rate measurement drअगरted */
#घोषणा MASK_RATE_B_ST		BIT(6) /* Rate measurement stability change */
#घोषणा MASK_RATE_B_ACT		BIT(5) /* Rate measurement activity change */
#घोषणा MASK_RATE_B_PST		BIT(4) /* Rate measreument presence change */
#घोषणा MASK_RATE_A_DRIFT	BIT(3) /* Rate measurement drअगरted */
#घोषणा MASK_RATE_A_ST		BIT(2) /* Rate measurement stability change */
#घोषणा MASK_RATE_A_ACT		BIT(1) /* Rate measurement presence change */
#घोषणा MASK_RATE_A_PST		BIT(0) /* Rate measreument presence change */

/* INT_FLG_CLR_SUS (Start Up Sequencer) bits */
#घोषणा MASK_MPT		BIT(7) /* Config MTP end of process */
#घोषणा MASK_FMT		BIT(5) /* Video क्रमmat changed */
#घोषणा MASK_RT_PULSE		BIT(4) /* End of termination resistance pulse */
#घोषणा MASK_SUS_END		BIT(3) /* SUS last state reached */
#घोषणा MASK_SUS_ACT		BIT(2) /* Activity of selected input changed */
#घोषणा MASK_SUS_CH		BIT(1) /* Selected input changed */
#घोषणा MASK_SUS_ST		BIT(0) /* SUS state changed */

/* INT_FLG_CLR_DDC bits */
#घोषणा MASK_EDID_MTP		BIT(7) /* EDID MTP end of process */
#घोषणा MASK_DDC_ERR		BIT(6) /* master DDC error */
#घोषणा MASK_DDC_CMD_DONE	BIT(5) /* master DDC cmd send correct */
#घोषणा MASK_READ_DONE		BIT(4) /* End of करोwn EDID पढ़ो */
#घोषणा MASK_RX_DDC_SW		BIT(3) /* Output DDC चयनing finished */
#घोषणा MASK_HDCP_DDC_SW	BIT(2) /* HDCP DDC चयनing finished */
#घोषणा MASK_HDP_PULSE_END	BIT(1) /* End of Hot Plug Detect pulse */
#घोषणा MASK_DET_5V		BIT(0) /* Detection of +5V */

/* INT_FLG_CLR_MODE bits */
#घोषणा MASK_HDMI_FLG		BIT(7) /* HDMI mode/avmute/encrypt/FIFO fail */
#घोषणा MASK_GAMUT		BIT(6) /* Gamut packet */
#घोषणा MASK_ISRC2		BIT(5) /* ISRC2 packet */
#घोषणा MASK_ISRC1		BIT(4) /* ISRC1 packet */
#घोषणा MASK_ACP		BIT(3) /* Audio Content Protection packet */
#घोषणा MASK_DC_NO_GCP		BIT(2) /* GCP not received in 5 frames */
#घोषणा MASK_DC_PHASE		BIT(1) /* deepcolor pixel phase needs update */
#घोषणा MASK_DC_MODE		BIT(0) /* deepcolor color depth changed */

/* INT_FLG_CLR_INFO bits (Infoframe Change Status) */
#घोषणा MASK_MPS_IF		BIT(6) /* MPEG Source Product */
#घोषणा MASK_AUD_IF		BIT(5) /* Audio */
#घोषणा MASK_SPD_IF		BIT(4) /* Source Product Descriptor */
#घोषणा MASK_AVI_IF		BIT(3) /* Auxiliary Video IF */
#घोषणा MASK_VS_IF_OTHER_BK2	BIT(2) /* Venकरोr Specअगरic (bank2) */
#घोषणा MASK_VS_IF_OTHER_BK1	BIT(1) /* Venकरोr Specअगरic (bank1) */
#घोषणा MASK_VS_IF_HDMI		BIT(0) /* Venकरोr Specअगरic (w/ HDMI LLC code) */

/* INT_FLG_CLR_AUDIO bits */
#घोषणा MASK_AUDIO_FREQ_FLG	BIT(5) /* Audio freq change */
#घोषणा MASK_AUDIO_FLG		BIT(4) /* DST, OBA, HBR, ASP change */
#घोषणा MASK_MUTE_FLG		BIT(3) /* Audio Mute */
#घोषणा MASK_CH_STATE		BIT(2) /* Channel status */
#घोषणा MASK_UNMUTE_FIFO	BIT(1) /* Audio Unmute */
#घोषणा MASK_ERROR_FIFO_PT	BIT(0) /* Audio FIFO poपूर्णांकer error */

/* INT_FLG_CLR_AFE bits */
#घोषणा MASK_AFE_WDL_UNLOCKED	BIT(7) /* Wordlocker was unlocked */
#घोषणा MASK_AFE_GAIN_DONE	BIT(6) /* Gain calibration करोne */
#घोषणा MASK_AFE_OFFSET_DONE	BIT(5) /* Offset calibration करोne */
#घोषणा MASK_AFE_ACTIVITY_DET	BIT(4) /* Activity detected on data */
#घोषणा MASK_AFE_PLL_LOCK	BIT(3) /* TMDS PLL is locked */
#घोषणा MASK_AFE_TRMCAL_DONE	BIT(2) /* Termination calibration करोne */
#घोषणा MASK_AFE_ASU_STATE	BIT(1) /* ASU state is reached */
#घोषणा MASK_AFE_ASU_READY	BIT(0) /* AFE calibration करोne: TMDS पढ़ोy */

/* Audio Output */
#घोषणा AUDCFG_CLK_INVERT	BIT(7)	/* invert A_CLK polarity */
#घोषणा AUDCFG_TEST_TONE	BIT(6)	/* enable test tone generator */
#घोषणा AUDCFG_BUS_SHIFT	5
#घोषणा AUDCFG_BUS_I2S		0L
#घोषणा AUDCFG_BUS_SPDIF	1L
#घोषणा AUDCFG_I2SW_SHIFT	4
#घोषणा AUDCFG_I2SW_16		0L
#घोषणा AUDCFG_I2SW_32		1L
#घोषणा AUDCFG_AUTO_MUTE_EN	BIT(3)	/* Enable Automatic audio mute */
#घोषणा AUDCFG_HBR_SHIFT	2
#घोषणा AUDCFG_HBR_STRAIGHT	0L	/* straight via AP0 */
#घोषणा AUDCFG_HBR_DEMUX	1L	/* demuxed via AP0:AP3 */
#घोषणा AUDCFG_TYPE_MASK	0x03
#घोषणा AUDCFG_TYPE_SHIFT	0
#घोषणा AUDCFG_TYPE_DST		3L	/* Direct Stream Transfer (DST) */
#घोषणा AUDCFG_TYPE_OBA		2L	/* One Bit Audio (OBA) */
#घोषणा AUDCFG_TYPE_HBR		1L	/* High Bit Rate (HBR) */
#घोषणा AUDCFG_TYPE_PCM		0L	/* Audio samples */

/* Video Formatter */
#घोषणा OF_VP_ENABLE		BIT(7)	/* VP[35:0]/HS/VS/DE/CLK */
#घोषणा OF_BLK			BIT(4)	/* blanking codes */
#घोषणा OF_TRC			BIT(3)	/* timing codes (SAV/EAV) */
#घोषणा OF_FMT_MASK		0x3
#घोषणा OF_FMT_444		0L	/* RGB444/YUV444 */
#घोषणा OF_FMT_422_SMPT		1L	/* YUV422 semi-planar */
#घोषणा OF_FMT_422_CCIR		2L	/* YUV422 CCIR656 */

/* HS/HREF output control */
#घोषणा HS_HREF_DELAY_MASK	0xf0
#घोषणा HS_HREF_DELAY_SHIFT	4	/* Pixel delay (-8..+7) */
#घोषणा HS_HREF_PXQ_SHIFT	3	/* Timing codes from HREF */
#घोषणा HS_HREF_INV_SHIFT	2	/* polarity (1=invert) */
#घोषणा HS_HREF_SEL_MASK	0x03
#घोषणा HS_HREF_SEL_SHIFT	0
#घोषणा HS_HREF_SEL_HS_VHREF	0L	/* HS from VHREF */
#घोषणा HS_HREF_SEL_HREF_VHREF	1L	/* HREF from VHREF */
#घोषणा HS_HREF_SEL_HREF_HDMI	2L	/* HREF from HDMI */
#घोषणा HS_HREF_SEL_NONE	3L	/* not generated */

/* VS output control */
#घोषणा VS_VREF_DELAY_MASK	0xf0
#घोषणा VS_VREF_DELAY_SHIFT	4	/* Pixel delay (-8..+7) */
#घोषणा VS_VREF_INV_SHIFT	2	/* polarity (1=invert) */
#घोषणा VS_VREF_SEL_MASK	0x03
#घोषणा VS_VREF_SEL_SHIFT	0
#घोषणा VS_VREF_SEL_VS_VHREF	0L	/* VS from VHREF */
#घोषणा VS_VREF_SEL_VREF_VHREF	1L	/* VREF from VHREF */
#घोषणा VS_VREF_SEL_VREF_HDMI	2L	/* VREF from HDMI */
#घोषणा VS_VREF_SEL_NONE	3L	/* not generated */

/* DE/FREF output control */
#घोषणा DE_FREF_DELAY_MASK	0xf0
#घोषणा DE_FREF_DELAY_SHIFT	4	/* Pixel delay (-8..+7) */
#घोषणा DE_FREF_DE_PXQ_SHIFT	3	/* Timing codes from DE */
#घोषणा DE_FREF_INV_SHIFT	2	/* polarity (1=invert) */
#घोषणा DE_FREF_SEL_MASK	0x03
#घोषणा DE_FREF_SEL_SHIFT	0
#घोषणा DE_FREF_SEL_DE_VHREF	0L	/* DE from VHREF (HREF and not(VREF) */
#घोषणा DE_FREF_SEL_FREF_VHREF	1L	/* FREF from VHREF */
#घोषणा DE_FREF_SEL_FREF_HDMI	2L	/* FREF from HDMI */
#घोषणा DE_FREF_SEL_NONE	3L	/* not generated */

/* HDMI_SOFT_RST bits */
#घोषणा RESET_DC		BIT(7)	/* Reset deep color module */
#घोषणा RESET_HDCP		BIT(6)	/* Reset HDCP module */
#घोषणा RESET_KSV		BIT(5)	/* Reset KSV-FIFO */
#घोषणा RESET_SCFG		BIT(4)	/* Reset HDCP and repeater function */
#घोषणा RESET_HCFG		BIT(3)	/* Reset HDCP DDC part */
#घोषणा RESET_PA		BIT(2)	/* Reset polarity adjust */
#घोषणा RESET_EP		BIT(1)	/* Reset Error protection */
#घोषणा RESET_TMDS		BIT(0)	/* Reset TMDS (calib, encoding, flow) */

/* HDMI_INFO_RST bits */
#घोषणा NACK_HDCP		BIT(7)	/* No ACK on HDCP request */
#घोषणा RESET_FIFO		BIT(4)	/* Reset Audio FIFO control */
#घोषणा RESET_GAMUT		BIT(3)	/* Clear Gamut packet */
#घोषणा RESET_AI		BIT(2)	/* Clear ACP and ISRC packets */
#घोषणा RESET_IF		BIT(1)	/* Clear all Audio infoframe packets */
#घोषणा RESET_AUDIO		BIT(0)	/* Reset Audio FIFO control */

/* HDCP_BCAPS bits */
#घोषणा HDCP_HDMI		BIT(7)	/* HDCP supports HDMI (vs DVI only) */
#घोषणा HDCP_REPEATER		BIT(6)	/* HDCP supports repeater function */
#घोषणा HDCP_READY		BIT(5)	/* set by repeater function */
#घोषणा HDCP_FAST		BIT(4)	/* Up to 400kHz */
#घोषणा HDCP_11			BIT(1)	/* HDCP 1.1 supported */
#घोषणा HDCP_FAST_REAUTH	BIT(0)	/* fast reauthentication supported */

/* Audio output क्रमmatter */
#घोषणा AUDIO_LAYOUT_SP_FLAG	BIT(2)	/* sp flag used by FIFO */
#घोषणा AUDIO_LAYOUT_MANUAL	BIT(1)	/* manual layout (vs per pkt) */
#घोषणा AUDIO_LAYOUT_LAYOUT1	BIT(0)  /* Layout1: AP0-3 vs Layout0:AP0 */

/* masks क्रम पूर्णांकerrupt status रेजिस्टरs */
#घोषणा MASK_SUS_STATUS		0x1F
#घोषणा LAST_STATE_REACHED	0x1B
#घोषणा MASK_CLK_STABLE		0x04
#घोषणा MASK_CLK_ACTIVE		0x02
#घोषणा MASK_SUS_STATE		0x10
#घोषणा MASK_SR_FIFO_FIFO_CTRL	0x30
#घोषणा MASK_AUDIO_FLAG		0x10

/* Rate measurement */
#घोषणा RATE_REFTIM_ENABLE	0x01
#घोषणा CLK_MIN_RATE		0x0057e4
#घोषणा CLK_MAX_RATE		0x0395f8
#घोषणा WDL_CFG_VAL		0x82
#घोषणा DC_FILTER_VAL		0x31

/* Infoframe */
#घोषणा VS_HDMI_IF_UPDATE	0x0200
#घोषणा VS_HDMI_IF		0x0201
#घोषणा VS_BK1_IF_UPDATE	0x0220
#घोषणा VS_BK1_IF		0x0221
#घोषणा VS_BK2_IF_UPDATE	0x0240
#घोषणा VS_BK2_IF		0x0241
#घोषणा AVI_IF_UPDATE		0x0260
#घोषणा AVI_IF			0x0261
#घोषणा SPD_IF_UPDATE		0x0280
#घोषणा SPD_IF			0x0281
#घोषणा AUD_IF_UPDATE		0x02a0
#घोषणा AUD_IF			0x02a1
#घोषणा MPS_IF_UPDATE		0x02c0
#घोषणा MPS_IF			0x02c1
