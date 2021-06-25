<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */
#अगर_अघोषित __LCD_H__
#घोषणा __LCD_H__

/*Definition TMDS Device ID रेजिस्टर*/
#घोषणा     VT1631_DEVICE_ID_REG        0x02
#घोषणा     VT1631_DEVICE_ID            0x92

#घोषणा     VT3271_DEVICE_ID_REG        0x02
#घोषणा     VT3271_DEVICE_ID            0x71

/* Definition DVI Panel ID*/
/* Resolution: 640x480,   Channel: single, Dithering: Enable */
#घोषणा     LCD_PANEL_ID0_640X480       0x00
/* Resolution: 800x600,   Channel: single, Dithering: Enable */
#घोषणा     LCD_PANEL_ID1_800X600       0x01
/* Resolution: 1024x768,  Channel: single, Dithering: Enable */
#घोषणा     LCD_PANEL_ID2_1024X768      0x02
/* Resolution: 1280x768,  Channel: single, Dithering: Enable */
#घोषणा     LCD_PANEL_ID3_1280X768      0x03
/* Resolution: 1280x1024, Channel: dual,   Dithering: Enable */
#घोषणा     LCD_PANEL_ID4_1280X1024     0x04
/* Resolution: 1400x1050, Channel: dual,   Dithering: Enable */
#घोषणा     LCD_PANEL_ID5_1400X1050     0x05
/* Resolution: 1600x1200, Channel: dual,   Dithering: Enable */
#घोषणा     LCD_PANEL_ID6_1600X1200     0x06
/* Resolution: 1366x768,  Channel: single, Dithering: Disable */
#घोषणा     LCD_PANEL_ID7_1366X768      0x07
/* Resolution: 1024x600,  Channel: single, Dithering: Enable*/
#घोषणा     LCD_PANEL_ID8_1024X600      0x08
/* Resolution: 1280x800,  Channel: single, Dithering: Enable*/
#घोषणा     LCD_PANEL_ID9_1280X800      0x09
/* Resolution: 800x480,   Channel: single, Dithering: Enable*/
#घोषणा     LCD_PANEL_IDA_800X480       0x0A
/* Resolution: 1360x768,   Channel: single, Dithering: Disable*/
#घोषणा     LCD_PANEL_IDB_1360X768     0x0B
/* Resolution: 480x640,  Channel: single, Dithering: Enable */
#घोषणा     LCD_PANEL_IDC_480X640      0x0C
/* Resolution: 1200x900,  Channel: single, Dithering: Disable */
#घोषणा     LCD_PANEL_IDD_1200X900      0x0D


बाह्य पूर्णांक viafb_LCD2_ON;
बाह्य पूर्णांक viafb_LCD_ON;
बाह्य पूर्णांक viafb_DVI_ON;

व्योम viafb_disable_lvds_vt1636(काष्ठा lvds_setting_inक्रमmation
			 *plvds_setting_info,
			 काष्ठा lvds_chip_inक्रमmation *plvds_chip_info);
व्योम viafb_enable_lvds_vt1636(काष्ठा lvds_setting_inक्रमmation
			*plvds_setting_info,
			काष्ठा lvds_chip_inक्रमmation *plvds_chip_info);
व्योम viafb_lcd_disable(व्योम);
व्योम viafb_lcd_enable(व्योम);
व्योम viafb_init_lcd_size(व्योम);
व्योम viafb_init_lvds_output_पूर्णांकerface(काष्ठा lvds_chip_inक्रमmation
				*plvds_chip_info,
				काष्ठा lvds_setting_inक्रमmation
				*plvds_setting_info);
व्योम viafb_lcd_set_mode(स्थिर काष्ठा fb_var_screeninfo *var, u16 cxres,
	u16 cyres, काष्ठा lvds_setting_inक्रमmation *plvds_setting_info,
	काष्ठा lvds_chip_inक्रमmation *plvds_chip_info);
bool viafb_lvds_trयंत्रitter_identअगरy(व्योम);
व्योम viafb_init_lvds_output_पूर्णांकerface(काष्ठा lvds_chip_inक्रमmation
				*plvds_chip_info,
				काष्ठा lvds_setting_inक्रमmation
				*plvds_setting_info);
bool viafb_lcd_get_mobile_state(bool *mobile);

#पूर्ण_अगर /* __LCD_H__ */
