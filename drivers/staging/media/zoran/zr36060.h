<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Zoran ZR36060 basic configuration functions - header file
 *
 * Copyright (C) 2002 Laurent Pinअक्षरt <laurent.pinअक्षरt@skynet.be>
 */

#अगर_अघोषित ZR36060_H
#घोषणा ZR36060_H

#समावेश "videocodec.h"

/* data stored क्रम each zoran jpeg codec chip */
काष्ठा zr36060 अणु
	अक्षर name[32];
	पूर्णांक num;
	/* io dataकाष्ठाure */
	काष्ठा videocodec *codec;
	// last coder status
	__u8 status;
	// actual coder setup
	पूर्णांक mode;

	__u16 width;
	__u16 height;

	__u16 bitrate_ctrl;

	__u32 total_code_vol;
	__u32 real_code_vol;
	__u16 max_block_vol;

	__u8 h_samp_ratio[8];
	__u8 v_samp_ratio[8];
	__u16 scalefact;
	__u16 dri;

	/* app/com marker data */
	काष्ठा jpeg_app_marker app;
	काष्ठा jpeg_com_marker com;
पूर्ण;

/* ZR36060 रेजिस्टर addresses */
#घोषणा ZR060_LOAD			0x000
#घोषणा ZR060_CFSR			0x001
#घोषणा ZR060_CIR			0x002
#घोषणा ZR060_CMR			0x003
#घोषणा ZR060_MBZ			0x004
#घोषणा ZR060_MBCVR			0x005
#घोषणा ZR060_MER			0x006
#घोषणा ZR060_IMR			0x007
#घोषणा ZR060_ISR			0x008
#घोषणा ZR060_TCV_NET_HI		0x009
#घोषणा ZR060_TCV_NET_MH		0x00a
#घोषणा ZR060_TCV_NET_ML		0x00b
#घोषणा ZR060_TCV_NET_LO		0x00c
#घोषणा ZR060_TCV_DATA_HI		0x00d
#घोषणा ZR060_TCV_DATA_MH		0x00e
#घोषणा ZR060_TCV_DATA_ML		0x00f
#घोषणा ZR060_TCV_DATA_LO		0x010
#घोषणा ZR060_SF_HI			0x011
#घोषणा ZR060_SF_LO			0x012
#घोषणा ZR060_AF_HI			0x013
#घोषणा ZR060_AF_M			0x014
#घोषणा ZR060_AF_LO			0x015
#घोषणा ZR060_ACV_HI			0x016
#घोषणा ZR060_ACV_MH			0x017
#घोषणा ZR060_ACV_ML			0x018
#घोषणा ZR060_ACV_LO			0x019
#घोषणा ZR060_ACT_HI			0x01a
#घोषणा ZR060_ACT_MH			0x01b
#घोषणा ZR060_ACT_ML			0x01c
#घोषणा ZR060_ACT_LO			0x01d
#घोषणा ZR060_ACV_TURN_HI		0x01e
#घोषणा ZR060_ACV_TURN_MH		0x01f
#घोषणा ZR060_ACV_TURN_ML		0x020
#घोषणा ZR060_ACV_TURN_LO		0x021
#घोषणा ZR060_IDR_DEV			0x022
#घोषणा ZR060_IDR_REV			0x023
#घोषणा ZR060_TCR_HI			0x024
#घोषणा ZR060_TCR_LO			0x025
#घोषणा ZR060_VCR			0x030
#घोषणा ZR060_VPR			0x031
#घोषणा ZR060_SR			0x032
#घोषणा ZR060_BCR_Y			0x033
#घोषणा ZR060_BCR_U			0x034
#घोषणा ZR060_BCR_V			0x035
#घोषणा ZR060_SGR_VTOTAL_HI		0x036
#घोषणा ZR060_SGR_VTOTAL_LO		0x037
#घोषणा ZR060_SGR_HTOTAL_HI		0x038
#घोषणा ZR060_SGR_HTOTAL_LO		0x039
#घोषणा ZR060_SGR_VSYNC			0x03a
#घोषणा ZR060_SGR_HSYNC			0x03b
#घोषणा ZR060_SGR_BVSTART		0x03c
#घोषणा ZR060_SGR_BHSTART		0x03d
#घोषणा ZR060_SGR_BVEND_HI		0x03e
#घोषणा ZR060_SGR_BVEND_LO		0x03f
#घोषणा ZR060_SGR_BHEND_HI		0x040
#घोषणा ZR060_SGR_BHEND_LO		0x041
#घोषणा ZR060_AAR_VSTART_HI		0x042
#घोषणा ZR060_AAR_VSTART_LO		0x043
#घोषणा ZR060_AAR_VEND_HI		0x044
#घोषणा ZR060_AAR_VEND_LO		0x045
#घोषणा ZR060_AAR_HSTART_HI		0x046
#घोषणा ZR060_AAR_HSTART_LO		0x047
#घोषणा ZR060_AAR_HEND_HI		0x048
#घोषणा ZR060_AAR_HEND_LO		0x049
#घोषणा ZR060_SWR_VSTART_HI		0x04a
#घोषणा ZR060_SWR_VSTART_LO		0x04b
#घोषणा ZR060_SWR_VEND_HI		0x04c
#घोषणा ZR060_SWR_VEND_LO		0x04d
#घोषणा ZR060_SWR_HSTART_HI		0x04e
#घोषणा ZR060_SWR_HSTART_LO		0x04f
#घोषणा ZR060_SWR_HEND_HI		0x050
#घोषणा ZR060_SWR_HEND_LO		0x051

#घोषणा ZR060_SOF_IDX			0x060
#घोषणा ZR060_SOS_IDX			0x07a
#घोषणा ZR060_DRI_IDX			0x0c0
#घोषणा ZR060_DQT_IDX			0x0cc
#घोषणा ZR060_DHT_IDX			0x1d4
#घोषणा ZR060_APP_IDX			0x380
#घोषणा ZR060_COM_IDX			0x3c0

/* ZR36060 LOAD रेजिस्टर bits */

#घोषणा ZR060_LOAD_LOAD			 BIT(7)
#घोषणा ZR060_LOAD_SYNC_RST		 BIT(0)

/* ZR36060 Code FIFO Status रेजिस्टर bits */

#घोषणा ZR060_CFSR_BUSY			 BIT(7)
#घोषणा ZR060_CFSR_C_BUSY		 BIT(2)
#घोषणा ZR060_CFSR_CFIFO		(3 << 0)

/* ZR36060 Code Interface रेजिस्टर */

#घोषणा ZR060_CIR_CODE16		 BIT(7)
#घोषणा ZR060_CIR_ENDIAN		 BIT(6)
#घोषणा ZR060_CIR_CFIS			 BIT(2)
#घोषणा ZR060_CIR_CODE_MSTR		 BIT(0)

/* ZR36060 Codec Mode रेजिस्टर */

#घोषणा ZR060_CMR_COMP			 BIT(7)
#घोषणा ZR060_CMR_ATP			 BIT(6)
#घोषणा ZR060_CMR_PASS2			 BIT(5)
#घोषणा ZR060_CMR_TLM			 BIT(4)
#घोषणा ZR060_CMR_BRB			 BIT(2)
#घोषणा ZR060_CMR_FSF			 BIT(1)

/* ZR36060 Markers Enable रेजिस्टर */

#घोषणा ZR060_MER_APP			 BIT(7)
#घोषणा ZR060_MER_COM			 BIT(6)
#घोषणा ZR060_MER_DRI			 BIT(5)
#घोषणा ZR060_MER_DQT			 BIT(4)
#घोषणा ZR060_MER_DHT			 BIT(3)

/* ZR36060 Interrupt Mask रेजिस्टर */

#घोषणा ZR060_IMR_EOAV			 BIT(3)
#घोषणा ZR060_IMR_EOI			 BIT(2)
#घोषणा ZR060_IMR_END			 BIT(1)
#घोषणा ZR060_IMR_DATA_ERR		 BIT(0)

/* ZR36060 Interrupt Status रेजिस्टर */

#घोषणा ZR060_ISR_PRO_CNT		(3 << 6)
#घोषणा ZR060_ISR_EOAV			 BIT(3)
#घोषणा ZR060_ISR_EOI			 BIT(2)
#घोषणा ZR060_ISR_END			 BIT(1)
#घोषणा ZR060_ISR_DATA_ERR		 BIT(0)

/* ZR36060 Video Control रेजिस्टर */

#घोषणा ZR060_VCR_VIDEO8		 BIT(7)
#घोषणा ZR060_VCR_RANGE			 BIT(6)
#घोषणा ZR060_VCR_FI_DET			 BIT(3)
#घोषणा ZR060_VCR_FI_VEDGE		 BIT(2)
#घोषणा ZR060_VCR_FI_EXT			 BIT(1)
#घोषणा ZR060_VCR_SYNC_MSTR		 BIT(0)

/* ZR36060 Video Polarity रेजिस्टर */

#घोषणा ZR060_VPR_VCLK_POL		 BIT(7)
#घोषणा ZR060_VPR_P_VAL_POL		 BIT(6)
#घोषणा ZR060_VPR_POE_POL		 BIT(5)
#घोषणा ZR060_VPR_S_IMG_POL		 BIT(4)
#घोषणा ZR060_VPR_BL_POL			 BIT(3)
#घोषणा ZR060_VPR_FI_POL			 BIT(2)
#घोषणा ZR060_VPR_HS_POL			 BIT(1)
#घोषणा ZR060_VPR_VS_POL			 BIT(0)

/* ZR36060 Scaling रेजिस्टर */

#घोषणा ZR060_SR_V_SCALE			 BIT(2)
#घोषणा ZR060_SR_H_SCALE2		 BIT(0)
#घोषणा ZR060_SR_H_SCALE4		(2 << 0)

#पूर्ण_अगर				/*fndef ZR36060_H */
