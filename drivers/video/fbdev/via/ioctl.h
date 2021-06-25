<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#अगर_अघोषित __IOCTL_H__
#घोषणा __IOCTL_H__

#अगर_अघोषित __user
#घोषणा __user
#पूर्ण_अगर

/* VIAFB IOCTL definition */
#घोषणा VIAFB_GET_INFO_SIZE		0x56494101	/* 'VIA\01' */
#घोषणा VIAFB_GET_INFO			0x56494102	/* 'VIA\02' */
#घोषणा VIAFB_HOTPLUG			0x56494103	/* 'VIA\03' */
#घोषणा VIAFB_SET_HOTPLUG_FLAG		0x56494104	/* 'VIA\04' */
#घोषणा VIAFB_GET_RESOLUTION		0x56494105	/* 'VIA\05' */
#घोषणा VIAFB_GET_SAMM_INFO		0x56494107	/* 'VIA\07' */
#घोषणा VIAFB_TURN_ON_OUTPUT_DEVICE     0x56494108	/* 'VIA\08' */
#घोषणा VIAFB_TURN_OFF_OUTPUT_DEVICE    0x56494109	/* 'VIA\09' */
#घोषणा VIAFB_GET_DEVICE		0x5649410B
#घोषणा VIAFB_GET_DRIVER_VERSION	0x56494112	/* 'VIA\12' */
#घोषणा VIAFB_GET_CHIP_INFO		0x56494113	/* 'VIA\13' */
#घोषणा VIAFB_GET_DEVICE_INFO           0x56494115

#घोषणा VIAFB_GET_DEVICE_SUPPORT	0x56494118
#घोषणा VIAFB_GET_DEVICE_CONNECT	0x56494119
#घोषणा VIAFB_GET_PANEL_SUPPORT_EXPAND	0x5649411A
#घोषणा VIAFB_GET_DRIVER_NAME		0x56494122
#घोषणा VIAFB_GET_DEVICE_SUPPORT_STATE	0x56494123
#घोषणा VIAFB_GET_GAMMA_LUT		0x56494124
#घोषणा VIAFB_SET_GAMMA_LUT		0x56494125
#घोषणा VIAFB_GET_GAMMA_SUPPORT_STATE	0x56494126
#घोषणा VIAFB_SYNC_SURFACE		0x56494130
#घोषणा VIAFB_GET_DRIVER_CAPS		0x56494131
#घोषणा VIAFB_GET_IGA_SCALING_INFO	0x56494132
#घोषणा VIAFB_GET_PANEL_MAX_SIZE	0x56494133
#घोषणा VIAFB_GET_PANEL_MAX_POSITION	0x56494134
#घोषणा VIAFB_SET_PANEL_SIZE		0x56494135
#घोषणा VIAFB_SET_PANEL_POSITION        0x56494136
#घोषणा VIAFB_GET_PANEL_POSITION        0x56494137
#घोषणा VIAFB_GET_PANEL_SIZE		0x56494138

#घोषणा None_Device 0x00
#घोषणा CRT_Device  0x01
#घोषणा LCD_Device  0x02
#घोषणा DVI_Device  0x08
#घोषणा CRT2_Device 0x10
#घोषणा LCD2_Device 0x40

#घोषणा OP_LCD_CENTERING   0x01
#घोषणा OP_LCD_PANEL_ID    0x02
#घोषणा OP_LCD_MODE        0x03

/*SAMM operation flag*/
#घोषणा OP_SAMM            0x80

#घोषणा LCD_PANEL_ID_MAXIMUM	23

#घोषणा STATE_ON            0x1
#घोषणा STATE_OFF           0x0
#घोषणा STATE_DEFAULT       0xFFFF

#घोषणा MAX_ACTIVE_DEV_NUM  2

काष्ठा device_t अणु
	अचिन्हित लघु crt:1;
	अचिन्हित लघु dvi:1;
	अचिन्हित लघु lcd:1;
	अचिन्हित लघु samm:1;
	अचिन्हित लघु lcd_dsp_cent:1;
	अचिन्हित अक्षर lcd_mode:1;
	अचिन्हित लघु epia_dvi:1;
	अचिन्हित लघु lcd_dual_edge:1;
	अचिन्हित लघु lcd2:1;

	अचिन्हित लघु primary_dev;
	अचिन्हित अक्षर lcd_panel_id;
	अचिन्हित लघु xres, yres;
	अचिन्हित लघु xres1, yres1;
	अचिन्हित लघु refresh;
	अचिन्हित लघु bpp;
	अचिन्हित लघु refresh1;
	अचिन्हित लघु bpp1;
	अचिन्हित लघु sequence;
	अचिन्हित लघु bus_width;
पूर्ण;

काष्ठा viafb_ioctl_info अणु
	u32 viafb_id;		/* क्रम identअगरying viafb */
#घोषणा VIAID       0x56494146	/* Identअगरy myself with 'VIAF' */
	u16 venकरोr_id;
	u16 device_id;
	u8 version;
	u8 revision;
	u8 reserved[246];	/* क्रम future use */
पूर्ण;

काष्ठा viafb_ioctl_mode अणु
	u32 xres;
	u32 yres;
	u32 refresh;
	u32 bpp;
	u32 xres_sec;
	u32 yres_sec;
	u32 भव_xres_sec;
	u32 भव_yres_sec;
	u32 refresh_sec;
	u32 bpp_sec;
पूर्ण;
काष्ठा viafb_ioctl_samm अणु
	u32 samm_status;
	u32 size_prim;
	u32 size_sec;
	u32 mem_base;
	u32 offset_sec;
पूर्ण;

काष्ठा viafb_driver_version अणु
	पूर्णांक iMajorNum;
	पूर्णांक iKernelNum;
	पूर्णांक iOSNum;
	पूर्णांक iMinorNum;
पूर्ण;

काष्ठा viafb_ioctl_lcd_attribute अणु
	अचिन्हित पूर्णांक panel_id;
	अचिन्हित पूर्णांक display_center;
	अचिन्हित पूर्णांक lcd_mode;
पूर्ण;

काष्ठा viafb_ioctl_setting अणु
	/* Enable or disable active devices */
	अचिन्हित लघु device_flag;
	/* Indicate which device should be turn on or turn off. */
	अचिन्हित लघु device_status;
	अचिन्हित पूर्णांक reserved;
	/* Indicate which LCD's attribute can be changed. */
	अचिन्हित लघु lcd_operation_flag;
	/* 1: SAMM ON  0: SAMM OFF */
	अचिन्हित लघु samm_status;
	/* horizontal resolution of first device */
	अचिन्हित लघु first_dev_hor_res;
	/* vertical resolution of first device */
	अचिन्हित लघु first_dev_ver_res;
	/* horizontal resolution of second device */
	अचिन्हित लघु second_dev_hor_res;
	/* vertical resolution of second device */
	अचिन्हित लघु second_dev_ver_res;
	/* refresh rate of first device */
	अचिन्हित लघु first_dev_refresh;
	/* bpp of first device */
	अचिन्हित लघु first_dev_bpp;
	/* refresh rate of second device */
	अचिन्हित लघु second_dev_refresh;
	/* bpp of second device */
	अचिन्हित लघु second_dev_bpp;
	/* Indicate which device are primary display device. */
	अचिन्हित पूर्णांक primary_device;
	अचिन्हित पूर्णांक काष्ठा_reserved[35];
	काष्ठा viafb_ioctl_lcd_attribute lcd_attributes;
पूर्ण;

काष्ठा _UTFunctionCaps अणु
	अचिन्हित पूर्णांक dw3DScalingState;
	अचिन्हित पूर्णांक reserved[31];
पूर्ण;

काष्ठा _POSITIONVALUE अणु
	अचिन्हित पूर्णांक dwX;
	अचिन्हित पूर्णांक dwY;
पूर्ण;

काष्ठा _panel_size_pos_info अणु
	अचिन्हित पूर्णांक device_type;
	पूर्णांक x;
	पूर्णांक y;
पूर्ण;

बाह्य पूर्णांक viafb_LCD_ON;
बाह्य पूर्णांक viafb_DVI_ON;

पूर्णांक viafb_ioctl_get_viafb_info(u_दीर्घ arg);
पूर्णांक viafb_ioctl_hotplug(पूर्णांक hres, पूर्णांक vres, पूर्णांक bpp);

#पूर्ण_अगर /* __IOCTL_H__ */
