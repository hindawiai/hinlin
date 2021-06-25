<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */
#अगर_अघोषित __CHIP_H__
#घोषणा __CHIP_H__

#समावेश "global.h"

/***************************************/
/* Definition Graphic Chip Inक्रमmation */
/***************************************/

#घोषणा     PCI_VIA_VENDOR_ID       0x1106

/* Define VIA Graphic Chip Name */
#घोषणा     UNICHROME_CLE266        1
#घोषणा     UNICHROME_CLE266_DID    0x3122
#घोषणा     CLE266_REVISION_AX      0x0A
#घोषणा     CLE266_REVISION_CX      0x0C

#घोषणा     UNICHROME_K400          2
#घोषणा     UNICHROME_K400_DID      0x7205

#घोषणा     UNICHROME_K800          3
#घोषणा     UNICHROME_K800_DID      0x3108

#घोषणा     UNICHROME_PM800         4
#घोषणा     UNICHROME_PM800_DID     0x3118

#घोषणा     UNICHROME_CN700         5
#घोषणा     UNICHROME_CN700_DID     0x3344

#घोषणा     UNICHROME_CX700         6
#घोषणा     UNICHROME_CX700_DID     0x3157
#घोषणा     CX700_REVISION_700      0x0
#घोषणा     CX700_REVISION_700M     0x1
#घोषणा     CX700_REVISION_700M2    0x2

#घोषणा     UNICHROME_CN750         7
#घोषणा     UNICHROME_CN750_DID     0x3225

#घोषणा     UNICHROME_K8M890        8
#घोषणा     UNICHROME_K8M890_DID    0x3230

#घोषणा     UNICHROME_P4M890        9
#घोषणा     UNICHROME_P4M890_DID    0x3343

#घोषणा     UNICHROME_P4M900        10
#घोषणा     UNICHROME_P4M900_DID    0x3371

#घोषणा     UNICHROME_VX800         11
#घोषणा     UNICHROME_VX800_DID     0x1122

#घोषणा     UNICHROME_VX855         12
#घोषणा     UNICHROME_VX855_DID     0x5122

#घोषणा     UNICHROME_VX900         13
#घोषणा     UNICHROME_VX900_DID     0x7122

/**************************************************/
/* Definition TMDS Trयंत्रitter Inक्रमmation         */
/**************************************************/

/* Definition TMDS Trयंत्रitter Index */
#घोषणा     NON_TMDS_TRANSMITTER    0x00
#घोषणा     VT1632_TMDS             0x01
#घोषणा     INTEGRATED_TMDS         0x42

/* Definition TMDS Trयंत्रitter I2C Slave Address */
#घोषणा     VT1632_TMDS_I2C_ADDR    0x10

/**************************************************/
/* Definition LVDS Trयंत्रitter Inक्रमmation         */
/**************************************************/

/* Definition LVDS Trयंत्रitter Index */
#घोषणा     NON_LVDS_TRANSMITTER    0x00
#घोषणा     VT1631_LVDS             0x01
#घोषणा     VT1636_LVDS             0x0E
#घोषणा     INTEGRATED_LVDS         0x41

/* Definition Digital Transmitter Mode */
#घोषणा     TX_DATA_12_BITS         0x01
#घोषणा     TX_DATA_24_BITS         0x02
#घोषणा     TX_DATA_DDR_MODE        0x04
#घोषणा     TX_DATA_SDR_MODE        0x08

/* Definition LVDS Trयंत्रitter I2C Slave Address */
#घोषणा     VT1631_LVDS_I2C_ADDR    0x70
#घोषणा     VT3271_LVDS_I2C_ADDR    0x80
#घोषणा     VT1636_LVDS_I2C_ADDR    0x80

काष्ठा पंचांगds_chip_inक्रमmation अणु
	पूर्णांक पंचांगds_chip_name;
	पूर्णांक पंचांगds_chip_slave_addr;
	पूर्णांक output_पूर्णांकerface;
	पूर्णांक i2c_port;
पूर्ण;

काष्ठा lvds_chip_inक्रमmation अणु
	पूर्णांक lvds_chip_name;
	पूर्णांक lvds_chip_slave_addr;
	पूर्णांक output_पूर्णांकerface;
	पूर्णांक i2c_port;
पूर्ण;

/* The type of 2D engine */
क्रमागत via_2d_engine अणु
	VIA_2D_ENG_H2,
	VIA_2D_ENG_H5,
	VIA_2D_ENG_M1,
पूर्ण;

काष्ठा chip_inक्रमmation अणु
	पूर्णांक gfx_chip_name;
	पूर्णांक gfx_chip_revision;
	क्रमागत via_2d_engine twod_engine;
	काष्ठा पंचांगds_chip_inक्रमmation पंचांगds_chip_info;
	काष्ठा lvds_chip_inक्रमmation lvds_chip_info;
	काष्ठा lvds_chip_inक्रमmation lvds_chip_info2;
पूर्ण;

काष्ठा पंचांगds_setting_inक्रमmation अणु
	पूर्णांक iga_path;
	पूर्णांक h_active;
	पूर्णांक v_active;
	पूर्णांक max_pixel_घड़ी;
पूर्ण;

काष्ठा lvds_setting_inक्रमmation अणु
	पूर्णांक iga_path;
	पूर्णांक lcd_panel_hres;
	पूर्णांक lcd_panel_vres;
	पूर्णांक display_method;
	पूर्णांक device_lcd_dualedge;
	पूर्णांक LCDDithering;
	पूर्णांक lcd_mode;
	u32 vclk;		/*panel mode घड़ी value */
पूर्ण;

काष्ठा GFX_DPA_SETTING अणु
	पूर्णांक ClkRangeIndex;
	u8 DVP0;		/* CR96[3:0] */
	u8 DVP0DataDri_S1;	/* SR2A[5]   */
	u8 DVP0DataDri_S;	/* SR1B[1]   */
	u8 DVP0ClockDri_S1;	/* SR2A[4]   */
	u8 DVP0ClockDri_S;	/* SR1E[2]   */
	u8 DVP1;		/* CR9B[3:0] */
	u8 DVP1Driving;		/* SR65[3:0], Data and Clock driving */
	u8 DFPHigh;		/* CR97[3:0] */
	u8 DFPLow;		/* CR99[3:0] */

पूर्ण;

काष्ठा VT1636_DPA_SETTING अणु
	u8 CLK_SEL_ST1;
	u8 CLK_SEL_ST2;
पूर्ण;
#पूर्ण_अगर /* __CHIP_H__ */
