<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * HDMI header definition क्रम OMAP4 HDMI core IP
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com/
 */

#अगर_अघोषित _HDMI4_CORE_H_
#घोषणा _HDMI4_CORE_H_

#समावेश "hdmi.h"

/* OMAP4 HDMI IP Core System */

#घोषणा HDMI_CORE_SYS_VND_IDL			0x0
#घोषणा HDMI_CORE_SYS_DEV_IDL			0x8
#घोषणा HDMI_CORE_SYS_DEV_IDH			0xC
#घोषणा HDMI_CORE_SYS_DEV_REV			0x10
#घोषणा HDMI_CORE_SYS_SRST			0x14
#घोषणा HDMI_CORE_SYS_SYS_CTRL1			0x20
#घोषणा HDMI_CORE_SYS_SYS_STAT			0x24
#घोषणा HDMI_CORE_SYS_SYS_CTRL3			0x28
#घोषणा HDMI_CORE_SYS_DCTL			0x34
#घोषणा HDMI_CORE_SYS_DE_DLY			0xC8
#घोषणा HDMI_CORE_SYS_DE_CTRL			0xCC
#घोषणा HDMI_CORE_SYS_DE_TOP			0xD0
#घोषणा HDMI_CORE_SYS_DE_CNTL			0xD8
#घोषणा HDMI_CORE_SYS_DE_CNTH			0xDC
#घोषणा HDMI_CORE_SYS_DE_LINL			0xE0
#घोषणा HDMI_CORE_SYS_DE_LINH_1			0xE4
#घोषणा HDMI_CORE_SYS_HRES_L			0xE8
#घोषणा HDMI_CORE_SYS_HRES_H			0xEC
#घोषणा HDMI_CORE_SYS_VRES_L			0xF0
#घोषणा HDMI_CORE_SYS_VRES_H			0xF4
#घोषणा HDMI_CORE_SYS_IADJUST			0xF8
#घोषणा HDMI_CORE_SYS_POLDETECT			0xFC
#घोषणा HDMI_CORE_SYS_HWIDTH1			0x110
#घोषणा HDMI_CORE_SYS_HWIDTH2			0x114
#घोषणा HDMI_CORE_SYS_VWIDTH			0x11C
#घोषणा HDMI_CORE_SYS_VID_CTRL			0x120
#घोषणा HDMI_CORE_SYS_VID_ACEN			0x124
#घोषणा HDMI_CORE_SYS_VID_MODE			0x128
#घोषणा HDMI_CORE_SYS_VID_BLANK1		0x12C
#घोषणा HDMI_CORE_SYS_VID_BLANK2		0x130
#घोषणा HDMI_CORE_SYS_VID_BLANK3		0x134
#घोषणा HDMI_CORE_SYS_DC_HEADER			0x138
#घोषणा HDMI_CORE_SYS_VID_DITHER		0x13C
#घोषणा HDMI_CORE_SYS_RGB2XVYCC_CT		0x140
#घोषणा HDMI_CORE_SYS_R2Y_COEFF_LOW		0x144
#घोषणा HDMI_CORE_SYS_R2Y_COEFF_UP		0x148
#घोषणा HDMI_CORE_SYS_G2Y_COEFF_LOW		0x14C
#घोषणा HDMI_CORE_SYS_G2Y_COEFF_UP		0x150
#घोषणा HDMI_CORE_SYS_B2Y_COEFF_LOW		0x154
#घोषणा HDMI_CORE_SYS_B2Y_COEFF_UP		0x158
#घोषणा HDMI_CORE_SYS_R2CB_COEFF_LOW		0x15C
#घोषणा HDMI_CORE_SYS_R2CB_COEFF_UP		0x160
#घोषणा HDMI_CORE_SYS_G2CB_COEFF_LOW		0x164
#घोषणा HDMI_CORE_SYS_G2CB_COEFF_UP		0x168
#घोषणा HDMI_CORE_SYS_B2CB_COEFF_LOW		0x16C
#घोषणा HDMI_CORE_SYS_B2CB_COEFF_UP		0x170
#घोषणा HDMI_CORE_SYS_R2CR_COEFF_LOW		0x174
#घोषणा HDMI_CORE_SYS_R2CR_COEFF_UP		0x178
#घोषणा HDMI_CORE_SYS_G2CR_COEFF_LOW		0x17C
#घोषणा HDMI_CORE_SYS_G2CR_COEFF_UP		0x180
#घोषणा HDMI_CORE_SYS_B2CR_COEFF_LOW		0x184
#घोषणा HDMI_CORE_SYS_B2CR_COEFF_UP		0x188
#घोषणा HDMI_CORE_SYS_RGB_OFFSET_LOW		0x18C
#घोषणा HDMI_CORE_SYS_RGB_OFFSET_UP		0x190
#घोषणा HDMI_CORE_SYS_Y_OFFSET_LOW		0x194
#घोषणा HDMI_CORE_SYS_Y_OFFSET_UP		0x198
#घोषणा HDMI_CORE_SYS_CBCR_OFFSET_LOW		0x19C
#घोषणा HDMI_CORE_SYS_CBCR_OFFSET_UP		0x1A0
#घोषणा HDMI_CORE_SYS_INTR_STATE		0x1C0
#घोषणा HDMI_CORE_SYS_INTR1			0x1C4
#घोषणा HDMI_CORE_SYS_INTR2			0x1C8
#घोषणा HDMI_CORE_SYS_INTR3			0x1CC
#घोषणा HDMI_CORE_SYS_INTR4			0x1D0
#घोषणा HDMI_CORE_SYS_INTR_UNMASK1		0x1D4
#घोषणा HDMI_CORE_SYS_INTR_UNMASK2		0x1D8
#घोषणा HDMI_CORE_SYS_INTR_UNMASK3		0x1DC
#घोषणा HDMI_CORE_SYS_INTR_UNMASK4		0x1E0
#घोषणा HDMI_CORE_SYS_INTR_CTRL			0x1E4
#घोषणा HDMI_CORE_SYS_TMDS_CTRL			0x208

/* value definitions क्रम HDMI_CORE_SYS_SYS_CTRL1 fields */
#घोषणा HDMI_CORE_SYS_SYS_CTRL1_VEN_FOLLOWVSYNC	0x1
#घोषणा HDMI_CORE_SYS_SYS_CTRL1_HEN_FOLLOWHSYNC	0x1
#घोषणा HDMI_CORE_SYS_SYS_CTRL1_BSEL_24BITBUS	0x1
#घोषणा HDMI_CORE_SYS_SYS_CTRL1_EDGE_RISINGEDGE	0x1

/* HDMI DDC E-DID */
#घोषणा HDMI_CORE_DDC_ADDR			0x3B4
#घोषणा HDMI_CORE_DDC_SEGM			0x3B8
#घोषणा HDMI_CORE_DDC_OFFSET			0x3BC
#घोषणा HDMI_CORE_DDC_COUNT1			0x3C0
#घोषणा HDMI_CORE_DDC_COUNT2			0x3C4
#घोषणा HDMI_CORE_DDC_STATUS			0x3C8
#घोषणा HDMI_CORE_DDC_CMD			0x3CC
#घोषणा HDMI_CORE_DDC_DATA			0x3D0

/* HDMI IP Core Audio Video */

#घोषणा HDMI_CORE_AV_ACR_CTRL			0x4
#घोषणा HDMI_CORE_AV_FREQ_SVAL			0x8
#घोषणा HDMI_CORE_AV_N_SVAL1			0xC
#घोषणा HDMI_CORE_AV_N_SVAL2			0x10
#घोषणा HDMI_CORE_AV_N_SVAL3			0x14
#घोषणा HDMI_CORE_AV_CTS_SVAL1			0x18
#घोषणा HDMI_CORE_AV_CTS_SVAL2			0x1C
#घोषणा HDMI_CORE_AV_CTS_SVAL3			0x20
#घोषणा HDMI_CORE_AV_CTS_HVAL1			0x24
#घोषणा HDMI_CORE_AV_CTS_HVAL2			0x28
#घोषणा HDMI_CORE_AV_CTS_HVAL3			0x2C
#घोषणा HDMI_CORE_AV_AUD_MODE			0x50
#घोषणा HDMI_CORE_AV_SPDIF_CTRL			0x54
#घोषणा HDMI_CORE_AV_HW_SPDIF_FS		0x60
#घोषणा HDMI_CORE_AV_SWAP_I2S			0x64
#घोषणा HDMI_CORE_AV_SPDIF_ERTH			0x6C
#घोषणा HDMI_CORE_AV_I2S_IN_MAP			0x70
#घोषणा HDMI_CORE_AV_I2S_IN_CTRL		0x74
#घोषणा HDMI_CORE_AV_I2S_CHST0			0x78
#घोषणा HDMI_CORE_AV_I2S_CHST1			0x7C
#घोषणा HDMI_CORE_AV_I2S_CHST2			0x80
#घोषणा HDMI_CORE_AV_I2S_CHST4			0x84
#घोषणा HDMI_CORE_AV_I2S_CHST5			0x88
#घोषणा HDMI_CORE_AV_ASRC			0x8C
#घोषणा HDMI_CORE_AV_I2S_IN_LEN			0x90
#घोषणा HDMI_CORE_AV_HDMI_CTRL			0xBC
#घोषणा HDMI_CORE_AV_AUDO_TXSTAT		0xC0
#घोषणा HDMI_CORE_AV_AUD_PAR_BUSCLK_1		0xCC
#घोषणा HDMI_CORE_AV_AUD_PAR_BUSCLK_2		0xD0
#घोषणा HDMI_CORE_AV_AUD_PAR_BUSCLK_3		0xD4
#घोषणा HDMI_CORE_AV_TEST_TXCTRL		0xF0
#घोषणा HDMI_CORE_AV_DPD			0xF4
#घोषणा HDMI_CORE_AV_PB_CTRL1			0xF8
#घोषणा HDMI_CORE_AV_PB_CTRL2			0xFC
#घोषणा HDMI_CORE_AV_AVI_BASE			0x100
#घोषणा HDMI_CORE_AV_AVI_TYPE			0x100
#घोषणा HDMI_CORE_AV_AVI_VERS			0x104
#घोषणा HDMI_CORE_AV_AVI_LEN			0x108
#घोषणा HDMI_CORE_AV_AVI_CHSUM			0x10C
#घोषणा HDMI_CORE_AV_AVI_DBYTE(n)		(n * 4 + 0x110)
#घोषणा HDMI_CORE_AV_SPD_TYPE			0x180
#घोषणा HDMI_CORE_AV_SPD_VERS			0x184
#घोषणा HDMI_CORE_AV_SPD_LEN			0x188
#घोषणा HDMI_CORE_AV_SPD_CHSUM			0x18C
#घोषणा HDMI_CORE_AV_SPD_DBYTE(n)		(n * 4 + 0x190)
#घोषणा HDMI_CORE_AV_AUDIO_TYPE			0x200
#घोषणा HDMI_CORE_AV_AUDIO_VERS			0x204
#घोषणा HDMI_CORE_AV_AUDIO_LEN			0x208
#घोषणा HDMI_CORE_AV_AUDIO_CHSUM		0x20C
#घोषणा HDMI_CORE_AV_AUD_DBYTE(n)		(n * 4 + 0x210)
#घोषणा HDMI_CORE_AV_MPEG_TYPE			0x280
#घोषणा HDMI_CORE_AV_MPEG_VERS			0x284
#घोषणा HDMI_CORE_AV_MPEG_LEN			0x288
#घोषणा HDMI_CORE_AV_MPEG_CHSUM			0x28C
#घोषणा HDMI_CORE_AV_MPEG_DBYTE(n)		(n * 4 + 0x290)
#घोषणा HDMI_CORE_AV_GEN_DBYTE(n)		(n * 4 + 0x300)
#घोषणा HDMI_CORE_AV_CP_BYTE1			0x37C
#घोषणा HDMI_CORE_AV_GEN2_DBYTE(n)		(n * 4 + 0x380)
#घोषणा HDMI_CORE_AV_CEC_ADDR_ID		0x3FC

#घोषणा HDMI_CORE_AV_SPD_DBYTE_ELSIZE		0x4
#घोषणा HDMI_CORE_AV_GEN2_DBYTE_ELSIZE		0x4
#घोषणा HDMI_CORE_AV_MPEG_DBYTE_ELSIZE		0x4
#घोषणा HDMI_CORE_AV_GEN_DBYTE_ELSIZE		0x4

#घोषणा HDMI_CORE_AV_AVI_DBYTE_NELEMS		15
#घोषणा HDMI_CORE_AV_SPD_DBYTE_NELEMS		27
#घोषणा HDMI_CORE_AV_AUD_DBYTE_NELEMS		10
#घोषणा HDMI_CORE_AV_MPEG_DBYTE_NELEMS		27
#घोषणा HDMI_CORE_AV_GEN_DBYTE_NELEMS		31
#घोषणा HDMI_CORE_AV_GEN2_DBYTE_NELEMS		31

क्रमागत hdmi_core_inputbus_width अणु
	HDMI_INPUT_8BIT = 0,
	HDMI_INPUT_10BIT = 1,
	HDMI_INPUT_12BIT = 2
पूर्ण;

क्रमागत hdmi_core_dither_trunc अणु
	HDMI_OUTPUTTRUNCATION_8BIT = 0,
	HDMI_OUTPUTTRUNCATION_10BIT = 1,
	HDMI_OUTPUTTRUNCATION_12BIT = 2,
	HDMI_OUTPUTDITHER_8BIT = 3,
	HDMI_OUTPUTDITHER_10BIT = 4,
	HDMI_OUTPUTDITHER_12BIT = 5
पूर्ण;

क्रमागत hdmi_core_deepcolor_ed अणु
	HDMI_DEEPCOLORPACKECTDISABLE = 0,
	HDMI_DEEPCOLORPACKECTENABLE = 1
पूर्ण;

क्रमागत hdmi_core_packet_mode अणु
	HDMI_PACKETMODERESERVEDVALUE = 0,
	HDMI_PACKETMODE24BITPERPIXEL = 4,
	HDMI_PACKETMODE30BITPERPIXEL = 5,
	HDMI_PACKETMODE36BITPERPIXEL = 6,
	HDMI_PACKETMODE48BITPERPIXEL = 7
पूर्ण;

क्रमागत hdmi_core_tclkselclkmult अणु
	HDMI_FPLL05IDCK = 0,
	HDMI_FPLL10IDCK = 1,
	HDMI_FPLL20IDCK = 2,
	HDMI_FPLL40IDCK = 3
पूर्ण;

क्रमागत hdmi_core_packet_ctrl अणु
	HDMI_PACKETENABLE = 1,
	HDMI_PACKETDISABLE = 0,
	HDMI_PACKETREPEATON = 1,
	HDMI_PACKETREPEATOFF = 0
पूर्ण;

क्रमागत hdmi_audio_i2s_config अणु
	HDMI_AUDIO_I2S_MSB_SHIFTED_FIRST = 0,
	HDMI_AUDIO_I2S_LSB_SHIFTED_FIRST = 1,
	HDMI_AUDIO_I2S_SCK_EDGE_FALLING = 0,
	HDMI_AUDIO_I2S_SCK_EDGE_RISING = 1,
	HDMI_AUDIO_I2S_VBIT_FOR_PCM = 0,
	HDMI_AUDIO_I2S_VBIT_FOR_COMPRESSED = 1,
	HDMI_AUDIO_I2S_FIRST_BIT_SHIFT = 0,
	HDMI_AUDIO_I2S_FIRST_BIT_NO_SHIFT = 1,
	HDMI_AUDIO_I2S_SD0_EN = 1,
	HDMI_AUDIO_I2S_SD1_EN = 1 << 1,
	HDMI_AUDIO_I2S_SD2_EN = 1 << 2,
	HDMI_AUDIO_I2S_SD3_EN = 1 << 3,
पूर्ण;

काष्ठा hdmi_core_video_config अणु
	क्रमागत hdmi_core_inputbus_width	ip_bus_width;
	क्रमागत hdmi_core_dither_trunc	op_dither_truc;
	क्रमागत hdmi_core_deepcolor_ed	deep_color_pkt;
	क्रमागत hdmi_core_packet_mode	pkt_mode;
	क्रमागत hdmi_core_hdmi_dvi		hdmi_dvi;
	क्रमागत hdmi_core_tclkselclkmult	tclk_sel_clkmult;
पूर्ण;

काष्ठा hdmi_core_packet_enable_repeat अणु
	u32	audio_pkt;
	u32	audio_pkt_repeat;
	u32	avi_infoframe;
	u32	avi_infoframe_repeat;
	u32	gen_cntrl_pkt;
	u32	gen_cntrl_pkt_repeat;
	u32	generic_pkt;
	u32	generic_pkt_repeat;
पूर्ण;

पूर्णांक hdmi4_core_ddc_init(काष्ठा hdmi_core_data *core);
पूर्णांक hdmi4_core_ddc_पढ़ो(व्योम *data, u8 *buf, अचिन्हित पूर्णांक block, माप_प्रकार len);

व्योम hdmi4_configure(काष्ठा hdmi_core_data *core, काष्ठा hdmi_wp_data *wp,
		काष्ठा hdmi_config *cfg);
व्योम hdmi4_core_dump(काष्ठा hdmi_core_data *core, काष्ठा seq_file *s);
पूर्णांक hdmi4_core_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_core_data *core);

पूर्णांक hdmi4_core_enable(काष्ठा hdmi_core_data *core);
व्योम hdmi4_core_disable(काष्ठा hdmi_core_data *core);
व्योम hdmi4_core_घातerकरोwn_disable(काष्ठा hdmi_core_data *core);

पूर्णांक hdmi4_audio_start(काष्ठा hdmi_core_data *core, काष्ठा hdmi_wp_data *wp);
व्योम hdmi4_audio_stop(काष्ठा hdmi_core_data *core, काष्ठा hdmi_wp_data *wp);
पूर्णांक hdmi4_audio_config(काष्ठा hdmi_core_data *core, काष्ठा hdmi_wp_data *wp,
		काष्ठा omap_dss_audio *audio, u32 pclk);
#पूर्ण_अगर
