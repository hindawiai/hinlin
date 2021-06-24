<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Zoran ZR36050 basic configuration functions - header file
 *
 * Copyright (C) 2001 Wolfgang Scherr <scherr@net4you.at>
 */

#अगर_अघोषित ZR36050_H
#घोषणा ZR36050_H

#समावेश "videocodec.h"

/* data stored क्रम each zoran jpeg codec chip */
काष्ठा zr36050 अणु
	अक्षर name[32];
	पूर्णांक num;
	/* io dataकाष्ठाure */
	काष्ठा videocodec *codec;
	// last coder status
	__u8 status1;
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

	/* com/app marker */
	काष्ठा jpeg_com_marker com;
	काष्ठा jpeg_app_marker app;
पूर्ण;

/* zr36050 रेजिस्टर addresses */
#घोषणा ZR050_GO                  0x000
#घोषणा ZR050_HARDWARE            0x002
#घोषणा ZR050_MODE                0x003
#घोषणा ZR050_OPTIONS             0x004
#घोषणा ZR050_MBCV                0x005
#घोषणा ZR050_MARKERS_EN          0x006
#घोषणा ZR050_INT_REQ_0           0x007
#घोषणा ZR050_INT_REQ_1           0x008
#घोषणा ZR050_TCV_NET_HI          0x009
#घोषणा ZR050_TCV_NET_MH          0x00a
#घोषणा ZR050_TCV_NET_ML          0x00b
#घोषणा ZR050_TCV_NET_LO          0x00c
#घोषणा ZR050_TCV_DATA_HI         0x00d
#घोषणा ZR050_TCV_DATA_MH         0x00e
#घोषणा ZR050_TCV_DATA_ML         0x00f
#घोषणा ZR050_TCV_DATA_LO         0x010
#घोषणा ZR050_SF_HI               0x011
#घोषणा ZR050_SF_LO               0x012
#घोषणा ZR050_AF_HI               0x013
#घोषणा ZR050_AF_M                0x014
#घोषणा ZR050_AF_LO               0x015
#घोषणा ZR050_ACV_HI              0x016
#घोषणा ZR050_ACV_MH              0x017
#घोषणा ZR050_ACV_ML              0x018
#घोषणा ZR050_ACV_LO              0x019
#घोषणा ZR050_ACT_HI              0x01a
#घोषणा ZR050_ACT_MH              0x01b
#घोषणा ZR050_ACT_ML              0x01c
#घोषणा ZR050_ACT_LO              0x01d
#घोषणा ZR050_ACV_TURN_HI         0x01e
#घोषणा ZR050_ACV_TURN_MH         0x01f
#घोषणा ZR050_ACV_TURN_ML         0x020
#घोषणा ZR050_ACV_TURN_LO         0x021
#घोषणा ZR050_STATUS_0            0x02e
#घोषणा ZR050_STATUS_1            0x02f

#घोषणा ZR050_SOF_IDX             0x040
#घोषणा ZR050_SOS1_IDX            0x07a
#घोषणा ZR050_SOS2_IDX            0x08a
#घोषणा ZR050_SOS3_IDX            0x09a
#घोषणा ZR050_SOS4_IDX            0x0aa
#घोषणा ZR050_DRI_IDX             0x0c0
#घोषणा ZR050_DNL_IDX             0x0c6
#घोषणा ZR050_DQT_IDX             0x0cc
#घोषणा ZR050_DHT_IDX             0x1d4
#घोषणा ZR050_APP_IDX             0x380
#घोषणा ZR050_COM_IDX             0x3c0

/* zr36050 hardware रेजिस्टर bits */

#घोषणा ZR050_HW_BSWD                0x80
#घोषणा ZR050_HW_MSTR                0x40
#घोषणा ZR050_HW_DMA                 0x20
#घोषणा ZR050_HW_CFIS_1_CLK          0x00
#घोषणा ZR050_HW_CFIS_2_CLK          0x04
#घोषणा ZR050_HW_CFIS_3_CLK          0x08
#घोषणा ZR050_HW_CFIS_4_CLK          0x0C
#घोषणा ZR050_HW_CFIS_5_CLK          0x10
#घोषणा ZR050_HW_CFIS_6_CLK          0x14
#घोषणा ZR050_HW_CFIS_7_CLK          0x18
#घोषणा ZR050_HW_CFIS_8_CLK          0x1C
#घोषणा ZR050_HW_BELE                0x01

/* zr36050 mode रेजिस्टर bits */

#घोषणा ZR050_MO_COMP                0x80
#घोषणा ZR050_MO_ATP                 0x40
#घोषणा ZR050_MO_PASS2               0x20
#घोषणा ZR050_MO_TLM                 0x10
#घोषणा ZR050_MO_DCONLY              0x08
#घोषणा ZR050_MO_BRC                 0x04

#घोषणा ZR050_MO_ATP                 0x40
#घोषणा ZR050_MO_PASS2               0x20
#घोषणा ZR050_MO_TLM                 0x10
#घोषणा ZR050_MO_DCONLY              0x08

/* zr36050 option रेजिस्टर bits */

#घोषणा ZR050_OP_NSCN_1              0x00
#घोषणा ZR050_OP_NSCN_2              0x20
#घोषणा ZR050_OP_NSCN_3              0x40
#घोषणा ZR050_OP_NSCN_4              0x60
#घोषणा ZR050_OP_NSCN_5              0x80
#घोषणा ZR050_OP_NSCN_6              0xA0
#घोषणा ZR050_OP_NSCN_7              0xC0
#घोषणा ZR050_OP_NSCN_8              0xE0
#घोषणा ZR050_OP_OVF                 0x10

/* zr36050 markers-enable रेजिस्टर bits */

#घोषणा ZR050_ME_APP                 0x80
#घोषणा ZR050_ME_COM                 0x40
#घोषणा ZR050_ME_DRI                 0x20
#घोषणा ZR050_ME_DQT                 0x10
#घोषणा ZR050_ME_DHT                 0x08
#घोषणा ZR050_ME_DNL                 0x04
#घोषणा ZR050_ME_DQTI                0x02
#घोषणा ZR050_ME_DHTI                0x01

/* zr36050 status0/1 रेजिस्टर bit masks */

#घोषणा ZR050_ST_RST_MASK            0x20
#घोषणा ZR050_ST_SOF_MASK            0x02
#घोषणा ZR050_ST_SOS_MASK            0x02
#घोषणा ZR050_ST_DATRDY_MASK         0x80
#घोषणा ZR050_ST_MRKDET_MASK         0x40
#घोषणा ZR050_ST_RFM_MASK            0x10
#घोषणा ZR050_ST_RFD_MASK            0x08
#घोषणा ZR050_ST_END_MASK            0x04
#घोषणा ZR050_ST_TCVOVF_MASK         0x02
#घोषणा ZR050_ST_DATOVF_MASK         0x01

/* pixel component idx */

#घोषणा ZR050_Y_COMPONENT         0
#घोषणा ZR050_U_COMPONENT         1
#घोषणा ZR050_V_COMPONENT         2

#पूर्ण_अगर				/*fndef ZR36050_H */
