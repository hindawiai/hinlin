<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * File: include/linux/omapfb.h
 *
 * Framebuffer driver क्रम TI OMAP boards
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#अगर_अघोषित _UAPI__LINUX_OMAPFB_H__
#घोषणा _UAPI__LINUX_OMAPFB_H__

#समावेश <linux/fb.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/* IOCTL commands. */

#घोषणा OMAP_IOW(num, dtype)	_IOW('O', num, dtype)
#घोषणा OMAP_IOR(num, dtype)	_IOR('O', num, dtype)
#घोषणा OMAP_IOWR(num, dtype)	_IOWR('O', num, dtype)
#घोषणा OMAP_IO(num)		_IO('O', num)

#घोषणा OMAPFB_MIRROR		OMAP_IOW(31, पूर्णांक)
#घोषणा OMAPFB_SYNC_GFX		OMAP_IO(37)
#घोषणा OMAPFB_VSYNC		OMAP_IO(38)
#घोषणा OMAPFB_SET_UPDATE_MODE	OMAP_IOW(40, पूर्णांक)
#घोषणा OMAPFB_GET_CAPS		OMAP_IOR(42, काष्ठा omapfb_caps)
#घोषणा OMAPFB_GET_UPDATE_MODE	OMAP_IOW(43, पूर्णांक)
#घोषणा OMAPFB_LCD_TEST		OMAP_IOW(45, पूर्णांक)
#घोषणा OMAPFB_CTRL_TEST	OMAP_IOW(46, पूर्णांक)
#घोषणा OMAPFB_UPDATE_WINDOW_OLD OMAP_IOW(47, काष्ठा omapfb_update_winकरोw_old)
#घोषणा OMAPFB_SET_COLOR_KEY	OMAP_IOW(50, काष्ठा omapfb_color_key)
#घोषणा OMAPFB_GET_COLOR_KEY	OMAP_IOW(51, काष्ठा omapfb_color_key)
#घोषणा OMAPFB_SETUP_PLANE	OMAP_IOW(52, काष्ठा omapfb_plane_info)
#घोषणा OMAPFB_QUERY_PLANE	OMAP_IOW(53, काष्ठा omapfb_plane_info)
#घोषणा OMAPFB_UPDATE_WINDOW	OMAP_IOW(54, काष्ठा omapfb_update_winकरोw)
#घोषणा OMAPFB_SETUP_MEM	OMAP_IOW(55, काष्ठा omapfb_mem_info)
#घोषणा OMAPFB_QUERY_MEM	OMAP_IOW(56, काष्ठा omapfb_mem_info)
#घोषणा OMAPFB_WAITFORVSYNC	OMAP_IO(57)
#घोषणा OMAPFB_MEMORY_READ	OMAP_IOR(58, काष्ठा omapfb_memory_पढ़ो)
#घोषणा OMAPFB_GET_OVERLAY_COLORMODE OMAP_IOR(59, काष्ठा omapfb_ovl_colormode)
#घोषणा OMAPFB_WAITFORGO	OMAP_IO(60)
#घोषणा OMAPFB_GET_VRAM_INFO	OMAP_IOR(61, काष्ठा omapfb_vram_info)
#घोषणा OMAPFB_SET_TEARSYNC	OMAP_IOW(62, काष्ठा omapfb_tearsync_info)
#घोषणा OMAPFB_GET_DISPLAY_INFO	OMAP_IOR(63, काष्ठा omapfb_display_info)

#घोषणा OMAPFB_CAPS_GENERIC_MASK	0x00000fff
#घोषणा OMAPFB_CAPS_LCDC_MASK		0x00fff000
#घोषणा OMAPFB_CAPS_PANEL_MASK		0xff000000

#घोषणा OMAPFB_CAPS_MANUAL_UPDATE	0x00001000
#घोषणा OMAPFB_CAPS_TEARSYNC		0x00002000
#घोषणा OMAPFB_CAPS_PLANE_RELOCATE_MEM	0x00004000
#घोषणा OMAPFB_CAPS_PLANE_SCALE		0x00008000
#घोषणा OMAPFB_CAPS_WINDOW_PIXEL_DOUBLE	0x00010000
#घोषणा OMAPFB_CAPS_WINDOW_SCALE	0x00020000
#घोषणा OMAPFB_CAPS_WINDOW_OVERLAY	0x00040000
#घोषणा OMAPFB_CAPS_WINDOW_ROTATE	0x00080000
#घोषणा OMAPFB_CAPS_SET_BACKLIGHT	0x01000000

/* Values from DSP must map to lower 16-bits */
#घोषणा OMAPFB_FORMAT_MASK		0x00ff
#घोषणा OMAPFB_FORMAT_FLAG_DOUBLE	0x0100
#घोषणा OMAPFB_FORMAT_FLAG_TEARSYNC	0x0200
#घोषणा OMAPFB_FORMAT_FLAG_FORCE_VSYNC	0x0400
#घोषणा OMAPFB_FORMAT_FLAG_ENABLE_OVERLAY	0x0800
#घोषणा OMAPFB_FORMAT_FLAG_DISABLE_OVERLAY	0x1000

#घोषणा OMAPFB_MEMTYPE_SDRAM		0
#घोषणा OMAPFB_MEMTYPE_SRAM		1
#घोषणा OMAPFB_MEMTYPE_MAX		1

#घोषणा OMAPFB_MEM_IDX_ENABLED	0x80
#घोषणा OMAPFB_MEM_IDX_MASK	0x7f

क्रमागत omapfb_color_क्रमmat अणु
	OMAPFB_COLOR_RGB565 = 0,
	OMAPFB_COLOR_YUV422,
	OMAPFB_COLOR_YUV420,
	OMAPFB_COLOR_CLUT_8BPP,
	OMAPFB_COLOR_CLUT_4BPP,
	OMAPFB_COLOR_CLUT_2BPP,
	OMAPFB_COLOR_CLUT_1BPP,
	OMAPFB_COLOR_RGB444,
	OMAPFB_COLOR_YUY422,

	OMAPFB_COLOR_ARGB16,
	OMAPFB_COLOR_RGB24U,	/* RGB24, 32-bit container */
	OMAPFB_COLOR_RGB24P,	/* RGB24, 24-bit container */
	OMAPFB_COLOR_ARGB32,
	OMAPFB_COLOR_RGBA32,
	OMAPFB_COLOR_RGBX32,
पूर्ण;

काष्ठा omapfb_update_winकरोw अणु
	__u32 x, y;
	__u32 width, height;
	__u32 क्रमmat;
	__u32 out_x, out_y;
	__u32 out_width, out_height;
	__u32 reserved[8];
पूर्ण;

काष्ठा omapfb_update_winकरोw_old अणु
	__u32 x, y;
	__u32 width, height;
	__u32 क्रमmat;
पूर्ण;

क्रमागत omapfb_plane अणु
	OMAPFB_PLANE_GFX = 0,
	OMAPFB_PLANE_VID1,
	OMAPFB_PLANE_VID2,
पूर्ण;

क्रमागत omapfb_channel_out अणु
	OMAPFB_CHANNEL_OUT_LCD = 0,
	OMAPFB_CHANNEL_OUT_DIGIT,
पूर्ण;

काष्ठा omapfb_plane_info अणु
	__u32 pos_x;
	__u32 pos_y;
	__u8  enabled;
	__u8  channel_out;
	__u8  mirror;
	__u8  mem_idx;
	__u32 out_width;
	__u32 out_height;
	__u32 reserved2[12];
पूर्ण;

काष्ठा omapfb_mem_info अणु
	__u32 size;
	__u8  type;
	__u8  reserved[3];
पूर्ण;

काष्ठा omapfb_caps अणु
	__u32 ctrl;
	__u32 plane_color;
	__u32 wnd_color;
पूर्ण;

क्रमागत omapfb_color_key_type अणु
	OMAPFB_COLOR_KEY_DISABLED = 0,
	OMAPFB_COLOR_KEY_GFX_DST,
	OMAPFB_COLOR_KEY_VID_SRC,
पूर्ण;

काष्ठा omapfb_color_key अणु
	__u8  channel_out;
	__u32 background;
	__u32 trans_key;
	__u8  key_type;
पूर्ण;

क्रमागत omapfb_update_mode अणु
	OMAPFB_UPDATE_DISABLED = 0,
	OMAPFB_AUTO_UPDATE,
	OMAPFB_MANUAL_UPDATE
पूर्ण;

काष्ठा omapfb_memory_पढ़ो अणु
	__u16 x;
	__u16 y;
	__u16 w;
	__u16 h;
	माप_प्रकार buffer_size;
	व्योम __user *buffer;
पूर्ण;

काष्ठा omapfb_ovl_colormode अणु
	__u8 overlay_idx;
	__u8 mode_idx;
	__u32 bits_per_pixel;
	__u32 nonstd;
	काष्ठा fb_bitfield red;
	काष्ठा fb_bitfield green;
	काष्ठा fb_bitfield blue;
	काष्ठा fb_bitfield transp;
पूर्ण;

काष्ठा omapfb_vram_info अणु
	__u32 total;
	__u32 मुक्त;
	__u32 largest_मुक्त_block;
	__u32 reserved[5];
पूर्ण;

काष्ठा omapfb_tearsync_info अणु
	__u8 enabled;
	__u8 reserved1[3];
	__u16 line;
	__u16 reserved2;
पूर्ण;

काष्ठा omapfb_display_info अणु
	__u16 xres;
	__u16 yres;
	__u32 width;	/* phys width of the display in micrometers */
	__u32 height;	/* phys height of the display in micrometers */
	__u32 reserved[5];
पूर्ण;


#पूर्ण_अगर /* _UAPI__LINUX_OMAPFB_H__ */
