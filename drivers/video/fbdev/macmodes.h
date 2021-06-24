<शैली गुरु>
/*
 *  linux/drivers/video/macmodes.h -- Standard MacOS video modes
 *
 *	Copyright (C) 1998 Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#अगर_अघोषित _VIDEO_MACMODES_H
#घोषणा _VIDEO_MACMODES_H

    /*
     *  Video mode values.
     *  These are supposed to be the same as the values that Apple uses in
     *  MacOS.
     */

#घोषणा VMODE_NVRAM		0
#घोषणा VMODE_512_384_60I	1	/* 512x384, 60Hz पूर्णांकerlaced (NTSC) */
#घोषणा VMODE_512_384_60	2	/* 512x384, 60Hz */
#घोषणा VMODE_640_480_50I	3	/* 640x480, 50Hz पूर्णांकerlaced (PAL) */
#घोषणा VMODE_640_480_60I	4	/* 640x480, 60Hz पूर्णांकerlaced (NTSC) */
#घोषणा VMODE_640_480_60	5	/* 640x480, 60Hz (VGA) */
#घोषणा VMODE_640_480_67	6	/* 640x480, 67Hz */
#घोषणा VMODE_640_870_75P	7	/* 640x870, 75Hz (portrait) */
#घोषणा VMODE_768_576_50I	8	/* 768x576, 50Hz (PAL full frame) */
#घोषणा VMODE_800_600_56	9	/* 800x600, 56Hz */
#घोषणा VMODE_800_600_60	10	/* 800x600, 60Hz */
#घोषणा VMODE_800_600_72	11	/* 800x600, 72Hz */
#घोषणा VMODE_800_600_75	12	/* 800x600, 75Hz */
#घोषणा VMODE_832_624_75	13	/* 832x624, 75Hz */
#घोषणा VMODE_1024_768_60	14	/* 1024x768, 60Hz */
#घोषणा VMODE_1024_768_70	15	/* 1024x768, 70Hz (or 72Hz?) */
#घोषणा VMODE_1024_768_75V	16	/* 1024x768, 75Hz (VESA) */
#घोषणा VMODE_1024_768_75	17	/* 1024x768, 75Hz */
#घोषणा VMODE_1152_870_75	18	/* 1152x870, 75Hz */
#घोषणा VMODE_1280_960_75	19	/* 1280x960, 75Hz */
#घोषणा VMODE_1280_1024_75	20	/* 1280x1024, 75Hz */
#घोषणा VMODE_1152_768_60	21	/* 1152x768, 60Hz     Titanium PowerBook */
#घोषणा VMODE_1600_1024_60	22	/* 1600x1024, 60Hz 22" Cinema Display */
#घोषणा VMODE_MAX		22
#घोषणा VMODE_CHOOSE		99

#घोषणा CMODE_NVRAM		-1
#घोषणा CMODE_CHOOSE		-2
#घोषणा CMODE_8			0	/* 8 bits/pixel */
#घोषणा CMODE_16		1	/* 16 (actually 15) bits/pixel */
#घोषणा CMODE_32		2	/* 32 (actually 24) bits/pixel */


बाह्य पूर्णांक mac_vmode_to_var(पूर्णांक vmode, पूर्णांक cmode,
			    काष्ठा fb_var_screeninfo *var);
बाह्य पूर्णांक mac_var_to_vmode(स्थिर काष्ठा fb_var_screeninfo *var, पूर्णांक *vmode,
			    पूर्णांक *cmode);
बाह्य पूर्णांक mac_map_monitor_sense(पूर्णांक sense);
बाह्य पूर्णांक mac_find_mode(काष्ठा fb_var_screeninfo *var,
			 काष्ठा fb_info *info,
			 स्थिर अक्षर *mode_option,
			 अचिन्हित पूर्णांक शेष_bpp);


    /*
     *  Addresses in NVRAM where video mode and pixel size are stored.
     */

#घोषणा NV_VMODE		0x140f
#घोषणा NV_CMODE		0x1410

#पूर्ण_अगर /* _VIDEO_MACMODES_H */
