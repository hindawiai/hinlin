<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#अगर_अघोषित __DVI_H__
#घोषणा __DVI_H__

/*Definition TMDS Device ID रेजिस्टर*/
#घोषणा     VT1632_DEVICE_ID_REG        0x02
#घोषणा     VT1632_DEVICE_ID            0x92

#घोषणा     GET_DVI_SIZE_BY_SYSTEM_BIOS     0x01
#घोषणा     GET_DVI_SIZE_BY_VGA_BIOS        0x02
#घोषणा     GET_DVI_SZIE_BY_HW_STRAPPING    0x03

/* Definition DVI Panel ID*/
/* Resolution: 640x480,   Channel: single, Dithering: Enable */
#घोषणा     DVI_PANEL_ID0_640X480       0x00
/* Resolution: 800x600,   Channel: single, Dithering: Enable */
#घोषणा     DVI_PANEL_ID1_800x600       0x01
/* Resolution: 1024x768,  Channel: single, Dithering: Enable */
#घोषणा     DVI_PANEL_ID1_1024x768      0x02
/* Resolution: 1280x768,  Channel: single, Dithering: Enable */
#घोषणा     DVI_PANEL_ID1_1280x768      0x03
/* Resolution: 1280x1024, Channel: dual,   Dithering: Enable */
#घोषणा     DVI_PANEL_ID1_1280x1024     0x04
/* Resolution: 1400x1050, Channel: dual,   Dithering: Enable */
#घोषणा     DVI_PANEL_ID1_1400x1050     0x05
/* Resolution: 1600x1200, Channel: dual,   Dithering: Enable */
#घोषणा     DVI_PANEL_ID1_1600x1200     0x06

/* Define the version of EDID*/
#घोषणा     EDID_VERSION_1      1
#घोषणा     EDID_VERSION_2      2

#घोषणा     DEV_CONNECT_DVI     0x01
#घोषणा     DEV_CONNECT_HDMI    0x02

पूर्णांक viafb_dvi_sense(व्योम);
व्योम viafb_dvi_disable(व्योम);
व्योम viafb_dvi_enable(व्योम);
bool viafb_पंचांगds_trयंत्रitter_identअगरy(व्योम);
व्योम viafb_init_dvi_size(काष्ठा पंचांगds_chip_inक्रमmation *पंचांगds_chip,
	काष्ठा पंचांगds_setting_inक्रमmation *पंचांगds_setting);
व्योम viafb_dvi_set_mode(स्थिर काष्ठा fb_var_screeninfo *var,
	u16 cxres, u16 cyres, पूर्णांक iga);

#पूर्ण_अगर /* __DVI_H__ */
