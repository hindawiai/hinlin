<शैली गुरु>
/*
 *  linux/drivers/video/modedb.c -- Standard video mode database management
 *
 *	Copyright (C) 1999 Geert Uytterhoeven
 *
 *	2001 - Documented with DocBook
 *	- Brad Douglas <brad@neruo.com>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/kernel.h>

#अघोषित DEBUG

#घोषणा name_matches(v, s, l) \
    ((v).name && !म_भेदन((s), (v).name, (l)) && म_माप((v).name) == (l))
#घोषणा res_matches(v, x, y) \
    ((v).xres == (x) && (v).yres == (y))

#अगर_घोषित DEBUG
#घोषणा DPRINTK(fmt, args...)	prपूर्णांकk("modedb %s: " fmt, __func__ , ## args)
#अन्यथा
#घोषणा DPRINTK(fmt, args...)
#पूर्ण_अगर

/*
 *  Standard video mode definitions (taken from XFree86)
 */

अटल स्थिर काष्ठा fb_videomode modedb[] = अणु

	/* 640x400 @ 70 Hz, 31.5 kHz hsync */
	अणु शून्य, 70, 640, 400, 39721, 40, 24, 39, 9, 96, 2, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 640x480 @ 60 Hz, 31.5 kHz hsync */
	अणु शून्य, 60, 640, 480, 39721, 40, 24, 32, 11, 96, 2,	0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 800x600 @ 56 Hz, 35.15 kHz hsync */
	अणु शून्य, 56, 800, 600, 27777, 128, 24, 22, 1, 72, 2,	0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1024x768 @ 87 Hz पूर्णांकerlaced, 35.5 kHz hsync */
	अणु शून्य, 87, 1024, 768, 22271, 56, 24, 33, 8, 160, 8, 0,
		FB_VMODE_INTERLACED पूर्ण,

	/* 640x400 @ 85 Hz, 37.86 kHz hsync */
	अणु शून्य, 85, 640, 400, 31746, 96, 32, 41, 1, 64, 3,
		FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED पूर्ण,

	/* 640x480 @ 72 Hz, 36.5 kHz hsync */
	अणु शून्य, 72, 640, 480, 31746, 144, 40, 30, 8, 40, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 640x480 @ 75 Hz, 37.50 kHz hsync */
	अणु शून्य, 75, 640, 480, 31746, 120, 16, 16, 1, 64, 3,	0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 800x600 @ 60 Hz, 37.8 kHz hsync */
	अणु शून्य, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 640x480 @ 85 Hz, 43.27 kHz hsync */
	अणु शून्य, 85, 640, 480, 27777, 80, 56, 25, 1, 56, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1152x864 @ 89 Hz पूर्णांकerlaced, 44 kHz hsync */
	अणु शून्य, 89, 1152, 864, 15384, 96, 16, 110, 1, 216, 10, 0,
		FB_VMODE_INTERLACED पूर्ण,
	/* 800x600 @ 72 Hz, 48.0 kHz hsync */
	अणु शून्य, 72, 800, 600, 20000, 64, 56, 23, 37, 120, 6,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1024x768 @ 60 Hz, 48.4 kHz hsync */
	अणु शून्य, 60, 1024, 768, 15384, 168, 8, 29, 3, 144, 6, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 640x480 @ 100 Hz, 53.01 kHz hsync */
	अणु शून्य, 100, 640, 480, 21834, 96, 32, 36, 8, 96, 6,	0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1152x864 @ 60 Hz, 53.5 kHz hsync */
	अणु शून्य, 60, 1152, 864, 11123, 208, 64, 16, 4, 256, 8, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 800x600 @ 85 Hz, 55.84 kHz hsync */
	अणु शून्य, 85, 800, 600, 16460, 160, 64, 36, 16, 64, 5, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1024x768 @ 70 Hz, 56.5 kHz hsync */
	अणु शून्य, 70, 1024, 768, 13333, 144, 24, 29, 3, 136, 6, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1280x1024 @ 87 Hz पूर्णांकerlaced, 51 kHz hsync */
	अणु शून्य, 87, 1280, 1024, 12500, 56, 16, 128, 1, 216, 12,	0,
		FB_VMODE_INTERLACED पूर्ण,

	/* 800x600 @ 100 Hz, 64.02 kHz hsync */
	अणु शून्य, 100, 800, 600, 14357, 160, 64, 30, 4, 64, 6, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1024x768 @ 76 Hz, 62.5 kHz hsync */
	अणु शून्य, 76, 1024, 768, 11764, 208, 8, 36, 16, 120, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1152x864 @ 70 Hz, 62.4 kHz hsync */
	अणु शून्य, 70, 1152, 864, 10869, 106, 56, 20, 1, 160, 10, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1280x1024 @ 61 Hz, 64.2 kHz hsync */
	अणु शून्य, 61, 1280, 1024, 9090, 200, 48, 26, 1, 184, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1400x1050 @ 60Hz, 63.9 kHz hsync */
	अणु शून्य, 60, 1400, 1050, 9259, 136, 40, 13, 1, 112, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1400x1050 @ 75,107 Hz, 82,392 kHz +hsync +vsync*/
	अणु शून्य, 75, 1400, 1050, 7190, 120, 56, 23, 10, 112, 13,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1400x1050 @ 60 Hz, ? kHz +hsync +vsync*/
	अणु शून्य, 60, 1400, 1050, 9259, 128, 40, 12, 0, 112, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1024x768 @ 85 Hz, 70.24 kHz hsync */
	अणु शून्य, 85, 1024, 768, 10111, 192, 32, 34, 14, 160, 6, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1152x864 @ 78 Hz, 70.8 kHz hsync */
	अणु शून्य, 78, 1152, 864, 9090, 228, 88, 32, 0, 84, 12, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1280x1024 @ 70 Hz, 74.59 kHz hsync */
	अणु शून्य, 70, 1280, 1024, 7905, 224, 32, 28, 8, 160, 8, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1600x1200 @ 60Hz, 75.00 kHz hsync */
	अणु शून्य, 60, 1600, 1200, 6172, 304, 64, 46, 1, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1152x864 @ 84 Hz, 76.0 kHz hsync */
	अणु शून्य, 84, 1152, 864, 7407, 184, 312, 32, 0, 128, 12, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1280x1024 @ 74 Hz, 78.85 kHz hsync */
	अणु शून्य, 74, 1280, 1024, 7407, 256, 32, 34, 3, 144, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1024x768 @ 100Hz, 80.21 kHz hsync */
	अणु शून्य, 100, 1024, 768, 8658, 192, 32, 21, 3, 192, 10, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1280x1024 @ 76 Hz, 81.13 kHz hsync */
	अणु शून्य, 76, 1280, 1024, 7407, 248, 32, 34, 3, 104, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1600x1200 @ 70 Hz, 87.50 kHz hsync */
	अणु शून्य, 70, 1600, 1200, 5291, 304, 64, 46, 1, 192, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1152x864 @ 100 Hz, 89.62 kHz hsync */
	अणु शून्य, 100, 1152, 864, 7264, 224, 32, 17, 2, 128, 19, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1280x1024 @ 85 Hz, 91.15 kHz hsync */
	अणु शून्य, 85, 1280, 1024, 6349, 224, 64, 44, 1, 160, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1600x1200 @ 75 Hz, 93.75 kHz hsync */
	अणु शून्य, 75, 1600, 1200, 4938, 304, 64, 46, 1, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1680x1050 @ 60 Hz, 65.191 kHz hsync */
	अणु शून्य, 60, 1680, 1050, 6848, 280, 104, 30, 3, 176, 6,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1600x1200 @ 85 Hz, 105.77 kHz hsync */
	अणु शून्य, 85, 1600, 1200, 4545, 272, 16, 37, 4, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1280x1024 @ 100 Hz, 107.16 kHz hsync */
	अणु शून्य, 100, 1280, 1024, 5502, 256, 32, 26, 7, 128, 15, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1800x1440 @ 64Hz, 96.15 kHz hsync  */
	अणु शून्य, 64, 1800, 1440, 4347, 304, 96, 46, 1, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1800x1440 @ 70Hz, 104.52 kHz hsync  */
	अणु शून्य, 70, 1800, 1440, 4000, 304, 96, 46, 1, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 512x384 @ 78 Hz, 31.50 kHz hsync */
	अणु शून्य, 78, 512, 384, 49603, 48, 16, 16, 1, 64, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 512x384 @ 85 Hz, 34.38 kHz hsync */
	अणु शून्य, 85, 512, 384, 45454, 48, 16, 16, 1, 64, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 320x200 @ 70 Hz, 31.5 kHz hsync, 8:5 aspect ratio */
	अणु शून्य, 70, 320, 200, 79440, 16, 16, 20, 4, 48, 1, 0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	अणु शून्य, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1, 0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 320x240 @ 72 Hz, 36.5 kHz hsync */
	अणु शून्य, 72, 320, 240, 63492, 16, 16, 16, 4, 48, 2, 0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 400x300 @ 56 Hz, 35.2 kHz hsync, 4:3 aspect ratio */
	अणु शून्य, 56, 400, 300, 55555, 64, 16, 10, 1, 32, 1, 0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 400x300 @ 60 Hz, 37.8 kHz hsync */
	अणु शून्य, 60, 400, 300, 50000, 48, 16, 11, 1, 64, 2, 0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 400x300 @ 72 Hz, 48.0 kHz hsync */
	अणु शून्य, 72, 400, 300, 40000, 32, 24, 11, 19, 64, 3,	0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 480x300 @ 56 Hz, 35.2 kHz hsync, 8:5 aspect ratio */
	अणु शून्य, 56, 480, 300, 46176, 80, 16, 10, 1, 40, 1, 0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 480x300 @ 60 Hz, 37.8 kHz hsync */
	अणु शून्य, 60, 480, 300, 41858, 56, 16, 11, 1, 80, 2, 0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 480x300 @ 63 Hz, 39.6 kHz hsync */
	अणु शून्य, 63, 480, 300, 40000, 56, 16, 11, 1, 80, 2, 0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 480x300 @ 72 Hz, 48.0 kHz hsync */
	अणु शून्य, 72, 480, 300, 33386, 40, 24, 11, 19, 80, 3, 0,
		FB_VMODE_DOUBLE पूर्ण,

	/* 1920x1200 @ 60 Hz, 74.5 Khz hsync */
	अणु शून्य, 60, 1920, 1200, 5177, 128, 336, 1, 38, 208, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1152x768, 60 Hz, PowerBook G4 Titanium I and II */
	अणु शून्य, 60, 1152, 768, 14047, 158, 26, 29, 3, 136, 6,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1366x768, 60 Hz, 47.403 kHz hsync, WXGA 16:9 aspect ratio */
	अणु शून्य, 60, 1366, 768, 13806, 120, 10, 14, 3, 32, 5, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 1280x800, 60 Hz, 47.403 kHz hsync, WXGA 16:10 aspect ratio */
	अणु शून्य, 60, 1280, 800, 12048, 200, 64, 24, 1, 136, 3, 0,
		FB_VMODE_NONINTERLACED पूर्ण,

	/* 720x576i @ 50 Hz, 15.625 kHz hsync (PAL RGB) */
	अणु शून्य, 50, 720, 576, 74074, 64, 16, 39, 5, 64, 5, 0,
		FB_VMODE_INTERLACED पूर्ण,

	/* 800x520i @ 50 Hz, 15.625 kHz hsync (PAL RGB) */
	अणु शून्य, 50, 800, 520, 58823, 144, 64, 72, 28, 80, 5, 0,
		FB_VMODE_INTERLACED पूर्ण,

	/* 864x480 @ 60 Hz, 35.15 kHz hsync */
	अणु शून्य, 60, 864, 480, 27777, 1, 1, 1, 1, 0, 0,
		0, FB_VMODE_NONINTERLACED पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_FB_MODE_HELPERS
स्थिर काष्ठा fb_videomode vesa_modes[] = अणु
	/* 0 640x350-85 VESA */
	अणु शून्य, 85, 640, 350, 31746,  96, 32, 60, 32, 64, 3,
	  FB_SYNC_HOR_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESAपूर्ण,
	/* 1 640x400-85 VESA */
	अणु शून्य, 85, 640, 400, 31746,  96, 32, 41, 01, 64, 3,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 2 720x400-85 VESA */
	अणु शून्य, 85, 721, 400, 28169, 108, 36, 42, 01, 72, 3,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 3 640x480-60 VESA */
	अणु शून्य, 60, 640, 480, 39682,  48, 16, 33, 10, 96, 2,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 4 640x480-72 VESA */
	अणु शून्य, 72, 640, 480, 31746, 128, 24, 29, 9, 40, 2,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 5 640x480-75 VESA */
	अणु शून्य, 75, 640, 480, 31746, 120, 16, 16, 01, 64, 3,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 6 640x480-85 VESA */
	अणु शून्य, 85, 640, 480, 27777, 80, 56, 25, 01, 56, 3,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 7 800x600-56 VESA */
	अणु शून्य, 56, 800, 600, 27777, 128, 24, 22, 01, 72, 2,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 8 800x600-60 VESA */
	अणु शून्य, 60, 800, 600, 25000, 88, 40, 23, 01, 128, 4,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 9 800x600-72 VESA */
	अणु शून्य, 72, 800, 600, 20000, 64, 56, 23, 37, 120, 6,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 10 800x600-75 VESA */
	अणु शून्य, 75, 800, 600, 20202, 160, 16, 21, 01, 80, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 11 800x600-85 VESA */
	अणु शून्य, 85, 800, 600, 17761, 152, 32, 27, 01, 64, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
        /* 12 1024x768i-43 VESA */
	अणु शून्य, 43, 1024, 768, 22271, 56, 8, 41, 0, 176, 8,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_INTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 13 1024x768-60 VESA */
	अणु शून्य, 60, 1024, 768, 15384, 160, 24, 29, 3, 136, 6,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 14 1024x768-70 VESA */
	अणु शून्य, 70, 1024, 768, 13333, 144, 24, 29, 3, 136, 6,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 15 1024x768-75 VESA */
	अणु शून्य, 75, 1024, 768, 12690, 176, 16, 28, 1, 96, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 16 1024x768-85 VESA */
	अणु शून्य, 85, 1024, 768, 10582, 208, 48, 36, 1, 96, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 17 1152x864-75 VESA */
	अणु शून्य, 75, 1152, 864, 9259, 256, 64, 32, 1, 128, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 18 1280x960-60 VESA */
	अणु शून्य, 60, 1280, 960, 9259, 312, 96, 36, 1, 112, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 19 1280x960-85 VESA */
	अणु शून्य, 85, 1280, 960, 6734, 224, 64, 47, 1, 160, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 20 1280x1024-60 VESA */
	अणु शून्य, 60, 1280, 1024, 9259, 248, 48, 38, 1, 112, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 21 1280x1024-75 VESA */
	अणु शून्य, 75, 1280, 1024, 7407, 248, 16, 38, 1, 144, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 22 1280x1024-85 VESA */
	अणु शून्य, 85, 1280, 1024, 6349, 224, 64, 44, 1, 160, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 23 1600x1200-60 VESA */
	अणु शून्य, 60, 1600, 1200, 6172, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 24 1600x1200-65 VESA */
	अणु शून्य, 65, 1600, 1200, 5698, 304,  64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 25 1600x1200-70 VESA */
	अणु शून्य, 70, 1600, 1200, 5291, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 26 1600x1200-75 VESA */
	अणु शून्य, 75, 1600, 1200, 4938, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 27 1600x1200-85 VESA */
	अणु शून्य, 85, 1600, 1200, 4357, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 28 1792x1344-60 VESA */
	अणु शून्य, 60, 1792, 1344, 4882, 328, 128, 46, 1, 200, 3,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 29 1792x1344-75 VESA */
	अणु शून्य, 75, 1792, 1344, 3831, 352, 96, 69, 1, 216, 3,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 30 1856x1392-60 VESA */
	अणु शून्य, 60, 1856, 1392, 4580, 352, 96, 43, 1, 224, 3,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 31 1856x1392-75 VESA */
	अणु शून्य, 75, 1856, 1392, 3472, 352, 128, 104, 1, 224, 3,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 32 1920x1440-60 VESA */
	अणु शून्य, 60, 1920, 1440, 4273, 344, 128, 56, 1, 200, 3,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 33 1920x1440-75 VESA */
	अणु शून्य, 75, 1920, 1440, 3367, 352, 144, 56, 1, 224, 3,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 34 1920x1200-60 RB VESA */
	अणु शून्य, 60, 1920, 1200, 6493, 80, 48, 26, 3, 32, 6,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 35 1920x1200-60 VESA */
	अणु शून्य, 60, 1920, 1200, 5174, 336, 136, 36, 3, 200, 6,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 36 1920x1200-75 VESA */
	अणु शून्य, 75, 1920, 1200, 4077, 344, 136, 46, 3, 208, 6,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 37 1920x1200-85 VESA */
	अणु शून्य, 85, 1920, 1200, 3555, 352, 144, 53, 3, 208, 6,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 38 2560x1600-60 RB VESA */
	अणु शून्य, 60, 2560, 1600, 3724, 80, 48, 37, 3, 32, 6,
	  FB_SYNC_HOR_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 39 2560x1600-60 VESA */
	अणु शून्य, 60, 2560, 1600, 2869, 472, 192, 49, 3, 280, 6,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 40 2560x1600-75 VESA */
	अणु शून्य, 75, 2560, 1600, 2256, 488, 208, 63, 3, 280, 6,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 41 2560x1600-85 VESA */
	अणु शून्य, 85, 2560, 1600, 1979, 488, 208, 73, 3, 280, 6,
	  FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
	/* 42 2560x1600-120 RB VESA */
	अणु शून्य, 120, 2560, 1600, 1809, 80, 48, 85, 3, 32, 6,
	  FB_SYNC_HOR_HIGH_ACT, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA पूर्ण,
पूर्ण;
EXPORT_SYMBOL(vesa_modes);

स्थिर काष्ठा dmt_videomode dmt_modes[DMT_SIZE] = अणु
	अणु 0x01, 0x0000, 0x000000, &vesa_modes[0] पूर्ण,
	अणु 0x02, 0x3119, 0x000000, &vesa_modes[1] पूर्ण,
	अणु 0x03, 0x0000, 0x000000, &vesa_modes[2] पूर्ण,
	अणु 0x04, 0x3140, 0x000000, &vesa_modes[3] पूर्ण,
	अणु 0x05, 0x314c, 0x000000, &vesa_modes[4] पूर्ण,
	अणु 0x06, 0x314f, 0x000000, &vesa_modes[5] पूर्ण,
	अणु 0x07, 0x3159, 0x000000, &vesa_modes[6] पूर्ण,
	अणु 0x08, 0x0000, 0x000000, &vesa_modes[7] पूर्ण,
	अणु 0x09, 0x4540, 0x000000, &vesa_modes[8] पूर्ण,
	अणु 0x0a, 0x454c, 0x000000, &vesa_modes[9] पूर्ण,
	अणु 0x0b, 0x454f, 0x000000, &vesa_modes[10] पूर्ण,
	अणु 0x0c, 0x4559, 0x000000, &vesa_modes[11] पूर्ण,
	अणु 0x0d, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x0e, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x0f, 0x0000, 0x000000, &vesa_modes[12] पूर्ण,
	अणु 0x10, 0x6140, 0x000000, &vesa_modes[13] पूर्ण,
	अणु 0x11, 0x614a, 0x000000, &vesa_modes[14] पूर्ण,
	अणु 0x12, 0x614f, 0x000000, &vesa_modes[15] पूर्ण,
	अणु 0x13, 0x6159, 0x000000, &vesa_modes[16] पूर्ण,
	अणु 0x14, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x15, 0x714f, 0x000000, &vesa_modes[17] पूर्ण,
	अणु 0x16, 0x0000, 0x7f1c21, शून्य पूर्ण,
	अणु 0x17, 0x0000, 0x7f1c28, शून्य पूर्ण,
	अणु 0x18, 0x0000, 0x7f1c44, शून्य पूर्ण,
	अणु 0x19, 0x0000, 0x7f1c62, शून्य पूर्ण,
	अणु 0x1a, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x1b, 0x0000, 0x8f1821, शून्य पूर्ण,
	अणु 0x1c, 0x8100, 0x8f1828, शून्य पूर्ण,
	अणु 0x1d, 0x810f, 0x8f1844, शून्य पूर्ण,
	अणु 0x1e, 0x8119, 0x8f1862, शून्य पूर्ण,
	अणु 0x1f, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x20, 0x8140, 0x000000, &vesa_modes[18] पूर्ण,
	अणु 0x21, 0x8159, 0x000000, &vesa_modes[19] पूर्ण,
	अणु 0x22, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x23, 0x8180, 0x000000, &vesa_modes[20] पूर्ण,
	अणु 0x24, 0x818f, 0x000000, &vesa_modes[21] पूर्ण,
	अणु 0x25, 0x8199, 0x000000, &vesa_modes[22] पूर्ण,
	अणु 0x26, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x27, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x28, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x29, 0x0000, 0x0c2021, शून्य पूर्ण,
	अणु 0x2a, 0x9040, 0x0c2028, शून्य पूर्ण,
	अणु 0x2b, 0x904f, 0x0c2044, शून्य पूर्ण,
	अणु 0x2c, 0x9059, 0x0c2062, शून्य पूर्ण,
	अणु 0x2d, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x2e, 0x9500, 0xc11821, शून्य पूर्ण,
	अणु 0x2f, 0x9500, 0xc11828, शून्य पूर्ण,
	अणु 0x30, 0x950f, 0xc11844, शून्य पूर्ण,
	अणु 0x31, 0x9519, 0xc11868, शून्य पूर्ण,
	अणु 0x32, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x33, 0xa940, 0x000000, &vesa_modes[23] पूर्ण,
	अणु 0x34, 0xa945, 0x000000, &vesa_modes[24] पूर्ण,
	अणु 0x35, 0xa94a, 0x000000, &vesa_modes[25] पूर्ण,
	अणु 0x36, 0xa94f, 0x000000, &vesa_modes[26] पूर्ण,
	अणु 0x37, 0xa959, 0x000000, &vesa_modes[27] पूर्ण,
	अणु 0x38, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x39, 0x0000, 0x0c2821, शून्य पूर्ण,
	अणु 0x3a, 0xb300, 0x0c2828, शून्य पूर्ण,
	अणु 0x3b, 0xb30f, 0x0c2844, शून्य पूर्ण,
	अणु 0x3c, 0xb319, 0x0c2868, शून्य पूर्ण,
	अणु 0x3d, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x3e, 0xc140, 0x000000, &vesa_modes[28] पूर्ण,
	अणु 0x3f, 0xc14f, 0x000000, &vesa_modes[29] पूर्ण,
	अणु 0x40, 0x0000, 0x000000, शून्यपूर्ण,
	अणु 0x41, 0xc940, 0x000000, &vesa_modes[30] पूर्ण,
	अणु 0x42, 0xc94f, 0x000000, &vesa_modes[31] पूर्ण,
	अणु 0x43, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x44, 0x0000, 0x572821, &vesa_modes[34] पूर्ण,
	अणु 0x45, 0xd100, 0x572828, &vesa_modes[35] पूर्ण,
	अणु 0x46, 0xd10f, 0x572844, &vesa_modes[36] पूर्ण,
	अणु 0x47, 0xd119, 0x572862, &vesa_modes[37] पूर्ण,
	अणु 0x48, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x49, 0xd140, 0x000000, &vesa_modes[32] पूर्ण,
	अणु 0x4a, 0xd14f, 0x000000, &vesa_modes[33] पूर्ण,
	अणु 0x4b, 0x0000, 0x000000, शून्य पूर्ण,
	अणु 0x4c, 0x0000, 0x1f3821, &vesa_modes[38] पूर्ण,
	अणु 0x4d, 0x0000, 0x1f3828, &vesa_modes[39] पूर्ण,
	अणु 0x4e, 0x0000, 0x1f3844, &vesa_modes[40] पूर्ण,
	अणु 0x4f, 0x0000, 0x1f3862, &vesa_modes[41] पूर्ण,
	अणु 0x50, 0x0000, 0x000000, &vesa_modes[42] पूर्ण,
पूर्ण;
EXPORT_SYMBOL(dmt_modes);
#पूर्ण_अगर /* CONFIG_FB_MODE_HELPERS */

/**
 *	fb_try_mode - test a video mode
 *	@var: frame buffer user defined part of display
 *	@info: frame buffer info काष्ठाure
 *	@mode: frame buffer video mode काष्ठाure
 *	@bpp: color depth in bits per pixel
 *
 *	Tries a video mode to test it's validity क्रम device @info.
 *
 *	Returns 1 on success.
 *
 */

अटल पूर्णांक fb_try_mode(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info,
		       स्थिर काष्ठा fb_videomode *mode, अचिन्हित पूर्णांक bpp)
अणु
	पूर्णांक err = 0;

	DPRINTK("Trying mode %s %dx%d-%d@%d\n",
		mode->name ? mode->name : "noname",
		mode->xres, mode->yres, bpp, mode->refresh);
	var->xres = mode->xres;
	var->yres = mode->yres;
	var->xres_भव = mode->xres;
	var->yres_भव = mode->yres;
	var->xoffset = 0;
	var->yoffset = 0;
	var->bits_per_pixel = bpp;
	var->activate |= FB_ACTIVATE_TEST;
	var->pixघड़ी = mode->pixघड़ी;
	var->left_margin = mode->left_margin;
	var->right_margin = mode->right_margin;
	var->upper_margin = mode->upper_margin;
	var->lower_margin = mode->lower_margin;
	var->hsync_len = mode->hsync_len;
	var->vsync_len = mode->vsync_len;
	var->sync = mode->sync;
	var->vmode = mode->vmode;
	अगर (info->fbops->fb_check_var)
		err = info->fbops->fb_check_var(var, info);
	var->activate &= ~FB_ACTIVATE_TEST;
	वापस err;
पूर्ण

/**
 * fb_find_mode - finds a valid video mode
 * @var: frame buffer user defined part of display
 * @info: frame buffer info काष्ठाure
 * @mode_option: string video mode to find
 * @db: video mode database
 * @dbsize: size of @db
 * @शेष_mode: शेष video mode to fall back to
 * @शेष_bpp: शेष color depth in bits per pixel
 *
 * Finds a suitable video mode, starting with the specअगरied mode
 * in @mode_option with fallback to @शेष_mode.  If
 * @शेष_mode fails, all modes in the video mode database will
 * be tried.
 *
 * Valid mode specअगरiers क्रम @mode_option::
 *
 *     <xres>x<yres>[M][R][-<bpp>][@<refresh>][i][p][m]
 *
 * or ::
 *
 *     <name>[-<bpp>][@<refresh>]
 *
 * with <xres>, <yres>, <bpp> and <refresh> decimal numbers and
 * <name> a string.
 *
 * If 'M' is present after yres (and beक्रमe refresh/bpp अगर present),
 * the function will compute the timings using VESA(पंचांग) Coordinated
 * Video Timings (CVT).  If 'R' is present after 'M', will compute with
 * reduced blanking (क्रम flatpanels).  If 'i' or 'p' are present, compute
 * पूर्णांकerlaced or progressive mode.  If 'm' is present, add margins equal
 * to 1.8% of xres rounded करोwn to 8 pixels, and 1.8% of yres. The अक्षर
 * 'i', 'p' and 'm' must be after 'M' and 'R'. Example::
 *
 *     1024x768MR-8@60m - Reduced blank with margins at 60Hz.
 *
 * NOTE: The passed काष्ठा @var is _not_ cleared!  This allows you
 * to supply values क्रम e.g. the grayscale and accel_flags fields.
 *
 * Returns zero क्रम failure, 1 अगर using specअगरied @mode_option,
 * 2 अगर using specअगरied @mode_option with an ignored refresh rate,
 * 3 अगर शेष mode is used, 4 अगर fall back to any valid mode.
 */

पूर्णांक fb_find_mode(काष्ठा fb_var_screeninfo *var,
		 काष्ठा fb_info *info, स्थिर अक्षर *mode_option,
		 स्थिर काष्ठा fb_videomode *db, अचिन्हित पूर्णांक dbsize,
		 स्थिर काष्ठा fb_videomode *शेष_mode,
		 अचिन्हित पूर्णांक शेष_bpp)
अणु
	पूर्णांक i;

	/* Set up शेषs */
	अगर (!db) अणु
		db = modedb;
		dbsize = ARRAY_SIZE(modedb);
	पूर्ण

	अगर (!शेष_mode)
		शेष_mode = &db[0];

	अगर (!शेष_bpp)
		शेष_bpp = 8;

	/* Did the user specअगरy a video mode? */
	अगर (!mode_option)
		mode_option = fb_mode_option;
	अगर (mode_option) अणु
		स्थिर अक्षर *name = mode_option;
		अचिन्हित पूर्णांक namelen = म_माप(name);
		पूर्णांक res_specअगरied = 0, bpp_specअगरied = 0, refresh_specअगरied = 0;
		अचिन्हित पूर्णांक xres = 0, yres = 0, bpp = शेष_bpp, refresh = 0;
		पूर्णांक yres_specअगरied = 0, cvt = 0, rb = 0;
		पूर्णांक पूर्णांकerlace_specअगरied = 0, पूर्णांकerlace = 0;
		पूर्णांक margins = 0;
		u32 best, dअगरf, tdअगरf;

		क्रम (i = namelen-1; i >= 0; i--) अणु
			चयन (name[i]) अणु
			हाल '@':
				namelen = i;
				अगर (!refresh_specअगरied && !bpp_specअगरied &&
				    !yres_specअगरied) अणु
					refresh = simple_म_से_दीर्घ(&name[i+1], शून्य,
								10);
					refresh_specअगरied = 1;
					अगर (cvt || rb)
						cvt = 0;
				पूर्ण अन्यथा
					जाओ करोne;
				अवरोध;
			हाल '-':
				namelen = i;
				अगर (!bpp_specअगरied && !yres_specअगरied) अणु
					bpp = simple_म_से_दीर्घ(&name[i+1], शून्य,
							    10);
					bpp_specअगरied = 1;
					अगर (cvt || rb)
						cvt = 0;
				पूर्ण अन्यथा
					जाओ करोne;
				अवरोध;
			हाल 'x':
				अगर (!yres_specअगरied) अणु
					yres = simple_म_से_दीर्घ(&name[i+1], शून्य,
							     10);
					yres_specअगरied = 1;
				पूर्ण अन्यथा
					जाओ करोne;
				अवरोध;
			हाल '0' ... '9':
				अवरोध;
			हाल 'M':
				अगर (!yres_specअगरied)
					cvt = 1;
				अवरोध;
			हाल 'R':
				अगर (!cvt)
					rb = 1;
				अवरोध;
			हाल 'm':
				अगर (!cvt)
					margins = 1;
				अवरोध;
			हाल 'p':
				अगर (!cvt) अणु
					पूर्णांकerlace = 0;
					पूर्णांकerlace_specअगरied = 1;
				पूर्ण
				अवरोध;
			हाल 'i':
				अगर (!cvt) अणु
					पूर्णांकerlace = 1;
					पूर्णांकerlace_specअगरied = 1;
				पूर्ण
				अवरोध;
			शेष:
				जाओ करोne;
			पूर्ण
		पूर्ण
		अगर (i < 0 && yres_specअगरied) अणु
			xres = simple_म_से_दीर्घ(name, शून्य, 10);
			res_specअगरied = 1;
		पूर्ण
करोne:
		अगर (cvt) अणु
			काष्ठा fb_videomode cvt_mode;
			पूर्णांक ret;

			DPRINTK("CVT mode %dx%d@%dHz%s%s%s\n", xres, yres,
				(refresh) ? refresh : 60,
				(rb) ? " reduced blanking" : "",
				(margins) ? " with margins" : "",
				(पूर्णांकerlace) ? " interlaced" : "");

			स_रखो(&cvt_mode, 0, माप(cvt_mode));
			cvt_mode.xres = xres;
			cvt_mode.yres = yres;
			cvt_mode.refresh = (refresh) ? refresh : 60;

			अगर (पूर्णांकerlace)
				cvt_mode.vmode |= FB_VMODE_INTERLACED;
			अन्यथा
				cvt_mode.vmode &= ~FB_VMODE_INTERLACED;

			ret = fb_find_mode_cvt(&cvt_mode, margins, rb);

			अगर (!ret && !fb_try_mode(var, info, &cvt_mode, bpp)) अणु
				DPRINTK("modedb CVT: CVT mode ok\n");
				वापस 1;
			पूर्ण

			DPRINTK("CVT mode invalid, getting mode from database\n");
		पूर्ण

		DPRINTK("Trying specified video mode%s %ix%i\n",
			refresh_specअगरied ? "" : " (ignoring refresh rate)",
			xres, yres);

		अगर (!refresh_specअगरied) अणु
			/*
			 * If the caller has provided a custom mode database and
			 * a valid monspecs काष्ठाure, we look क्रम the mode with
			 * the highest refresh rate.  Otherwise we play it safe
			 * it and try to find a mode with a refresh rate बंदst
			 * to the standard 60 Hz.
			 */
			अगर (db != modedb &&
			    info->monspecs.vfmin && info->monspecs.vfmax &&
			    info->monspecs.hfmin && info->monspecs.hfmax &&
			    info->monspecs.dclkmax) अणु
				refresh = 1000;
			पूर्ण अन्यथा अणु
				refresh = 60;
			पूर्ण
		पूर्ण

		dअगरf = -1;
		best = -1;
		क्रम (i = 0; i < dbsize; i++) अणु
			अगर ((name_matches(db[i], name, namelen) ||
			     (res_specअगरied && res_matches(db[i], xres, yres))) &&
			    !fb_try_mode(var, info, &db[i], bpp)) अणु
				स्थिर पूर्णांक db_पूर्णांकerlace = (db[i].vmode &
					FB_VMODE_INTERLACED ? 1 : 0);
				पूर्णांक score = असल(db[i].refresh - refresh);

				अगर (पूर्णांकerlace_specअगरied)
					score += असल(db_पूर्णांकerlace - पूर्णांकerlace);

				अगर (!पूर्णांकerlace_specअगरied ||
				    db_पूर्णांकerlace == पूर्णांकerlace)
					अगर (refresh_specअगरied &&
					    db[i].refresh == refresh)
						वापस 1;

				अगर (score < dअगरf) अणु
					dअगरf = score;
					best = i;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (best != -1) अणु
			fb_try_mode(var, info, &db[best], bpp);
			वापस (refresh_specअगरied) ? 2 : 1;
		पूर्ण

		dअगरf = 2 * (xres + yres);
		best = -1;
		DPRINTK("Trying best-fit modes\n");
		क्रम (i = 0; i < dbsize; i++) अणु
			DPRINTK("Trying %ix%i\n", db[i].xres, db[i].yres);
			अगर (!fb_try_mode(var, info, &db[i], bpp)) अणु
				tdअगरf = असल(db[i].xres - xres) +
					असल(db[i].yres - yres);

				/*
				 * Penalize modes with resolutions smaller
				 * than requested.
				 */
				अगर (xres > db[i].xres || yres > db[i].yres)
					tdअगरf += xres + yres;

				अगर (dअगरf > tdअगरf) अणु
					dअगरf = tdअगरf;
					best = i;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (best != -1) अणु
			fb_try_mode(var, info, &db[best], bpp);
			वापस 5;
		पूर्ण
	पूर्ण

	DPRINTK("Trying default video mode\n");
	अगर (!fb_try_mode(var, info, शेष_mode, शेष_bpp))
		वापस 3;

	DPRINTK("Trying all modes\n");
	क्रम (i = 0; i < dbsize; i++)
		अगर (!fb_try_mode(var, info, &db[i], शेष_bpp))
			वापस 4;

	DPRINTK("No valid mode found\n");
	वापस 0;
पूर्ण

/**
 * fb_var_to_videomode - convert fb_var_screeninfo to fb_videomode
 * @mode: poपूर्णांकer to काष्ठा fb_videomode
 * @var: poपूर्णांकer to काष्ठा fb_var_screeninfo
 */
व्योम fb_var_to_videomode(काष्ठा fb_videomode *mode,
			 स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	u32 pixघड़ी, hfreq, htotal, vtotal;

	mode->name = शून्य;
	mode->xres = var->xres;
	mode->yres = var->yres;
	mode->pixघड़ी = var->pixघड़ी;
	mode->hsync_len = var->hsync_len;
	mode->vsync_len = var->vsync_len;
	mode->left_margin = var->left_margin;
	mode->right_margin = var->right_margin;
	mode->upper_margin = var->upper_margin;
	mode->lower_margin = var->lower_margin;
	mode->sync = var->sync;
	mode->vmode = var->vmode & FB_VMODE_MASK;
	mode->flag = FB_MODE_IS_FROM_VAR;
	mode->refresh = 0;

	अगर (!var->pixघड़ी)
		वापस;

	pixघड़ी = PICOS2KHZ(var->pixघड़ी) * 1000;

	htotal = var->xres + var->right_margin + var->hsync_len +
		var->left_margin;
	vtotal = var->yres + var->lower_margin + var->vsync_len +
		var->upper_margin;

	अगर (var->vmode & FB_VMODE_INTERLACED)
		vtotal /= 2;
	अगर (var->vmode & FB_VMODE_DOUBLE)
		vtotal *= 2;

	अगर (!htotal || !vtotal)
		वापस;

	hfreq = pixघड़ी/htotal;
	mode->refresh = hfreq/vtotal;
पूर्ण

/**
 * fb_videomode_to_var - convert fb_videomode to fb_var_screeninfo
 * @var: poपूर्णांकer to काष्ठा fb_var_screeninfo
 * @mode: poपूर्णांकer to काष्ठा fb_videomode
 */
व्योम fb_videomode_to_var(काष्ठा fb_var_screeninfo *var,
			 स्थिर काष्ठा fb_videomode *mode)
अणु
	var->xres = mode->xres;
	var->yres = mode->yres;
	var->xres_भव = mode->xres;
	var->yres_भव = mode->yres;
	var->xoffset = 0;
	var->yoffset = 0;
	var->pixघड़ी = mode->pixघड़ी;
	var->left_margin = mode->left_margin;
	var->right_margin = mode->right_margin;
	var->upper_margin = mode->upper_margin;
	var->lower_margin = mode->lower_margin;
	var->hsync_len = mode->hsync_len;
	var->vsync_len = mode->vsync_len;
	var->sync = mode->sync;
	var->vmode = mode->vmode & FB_VMODE_MASK;
पूर्ण

/**
 * fb_mode_is_equal - compare 2 videomodes
 * @mode1: first videomode
 * @mode2: second videomode
 *
 * RETURNS:
 * 1 अगर equal, 0 अगर not
 */
पूर्णांक fb_mode_is_equal(स्थिर काष्ठा fb_videomode *mode1,
		     स्थिर काष्ठा fb_videomode *mode2)
अणु
	वापस (mode1->xres         == mode2->xres &&
		mode1->yres         == mode2->yres &&
		mode1->pixघड़ी     == mode2->pixघड़ी &&
		mode1->hsync_len    == mode2->hsync_len &&
		mode1->vsync_len    == mode2->vsync_len &&
		mode1->left_margin  == mode2->left_margin &&
		mode1->right_margin == mode2->right_margin &&
		mode1->upper_margin == mode2->upper_margin &&
		mode1->lower_margin == mode2->lower_margin &&
		mode1->sync         == mode2->sync &&
		mode1->vmode        == mode2->vmode);
पूर्ण

/**
 * fb_find_best_mode - find best matching videomode
 * @var: poपूर्णांकer to काष्ठा fb_var_screeninfo
 * @head: poपूर्णांकer to काष्ठा list_head of modelist
 *
 * RETURNS:
 * काष्ठा fb_videomode, शून्य अगर none found
 *
 * IMPORTANT:
 * This function assumes that all modelist entries in
 * info->modelist are valid.
 *
 * NOTES:
 * Finds best matching videomode which has an equal or greater dimension than
 * var->xres and var->yres.  If more than 1 videomode is found, will वापस
 * the videomode with the highest refresh rate
 */
स्थिर काष्ठा fb_videomode *fb_find_best_mode(स्थिर काष्ठा fb_var_screeninfo *var,
					     काष्ठा list_head *head)
अणु
	काष्ठा list_head *pos;
	काष्ठा fb_modelist *modelist;
	काष्ठा fb_videomode *mode, *best = शून्य;
	u32 dअगरf = -1;

	list_क्रम_each(pos, head) अणु
		u32 d;

		modelist = list_entry(pos, काष्ठा fb_modelist, list);
		mode = &modelist->mode;

		अगर (mode->xres >= var->xres && mode->yres >= var->yres) अणु
			d = (mode->xres - var->xres) +
				(mode->yres - var->yres);
			अगर (dअगरf > d) अणु
				dअगरf = d;
				best = mode;
			पूर्ण अन्यथा अगर (dअगरf == d && best &&
				   mode->refresh > best->refresh)
				best = mode;
		पूर्ण
	पूर्ण
	वापस best;
पूर्ण

/**
 * fb_find_nearest_mode - find बंदst videomode
 *
 * @mode: poपूर्णांकer to काष्ठा fb_videomode
 * @head: poपूर्णांकer to modelist
 *
 * Finds best matching videomode, smaller or greater in dimension.
 * If more than 1 videomode is found, will वापस the videomode with
 * the बंदst refresh rate.
 */
स्थिर काष्ठा fb_videomode *fb_find_nearest_mode(स्थिर काष्ठा fb_videomode *mode,
					        काष्ठा list_head *head)
अणु
	काष्ठा list_head *pos;
	काष्ठा fb_modelist *modelist;
	काष्ठा fb_videomode *cmode, *best = शून्य;
	u32 dअगरf = -1, dअगरf_refresh = -1;

	list_क्रम_each(pos, head) अणु
		u32 d;

		modelist = list_entry(pos, काष्ठा fb_modelist, list);
		cmode = &modelist->mode;

		d = असल(cmode->xres - mode->xres) +
			असल(cmode->yres - mode->yres);
		अगर (dअगरf > d) अणु
			dअगरf = d;
			dअगरf_refresh = असल(cmode->refresh - mode->refresh);
			best = cmode;
		पूर्ण अन्यथा अगर (dअगरf == d) अणु
			d = असल(cmode->refresh - mode->refresh);
			अगर (dअगरf_refresh > d) अणु
				dअगरf_refresh = d;
				best = cmode;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस best;
पूर्ण

/**
 * fb_match_mode - find a videomode which exactly matches the timings in var
 * @var: poपूर्णांकer to काष्ठा fb_var_screeninfo
 * @head: poपूर्णांकer to काष्ठा list_head of modelist
 *
 * RETURNS:
 * काष्ठा fb_videomode, शून्य अगर none found
 */
स्थिर काष्ठा fb_videomode *fb_match_mode(स्थिर काष्ठा fb_var_screeninfo *var,
					 काष्ठा list_head *head)
अणु
	काष्ठा list_head *pos;
	काष्ठा fb_modelist *modelist;
	काष्ठा fb_videomode *m, mode;

	fb_var_to_videomode(&mode, var);
	list_क्रम_each(pos, head) अणु
		modelist = list_entry(pos, काष्ठा fb_modelist, list);
		m = &modelist->mode;
		अगर (fb_mode_is_equal(m, &mode))
			वापस m;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * fb_add_videomode - adds videomode entry to modelist
 * @mode: videomode to add
 * @head: काष्ठा list_head of modelist
 *
 * NOTES:
 * Will only add unmatched mode entries
 */
पूर्णांक fb_add_videomode(स्थिर काष्ठा fb_videomode *mode, काष्ठा list_head *head)
अणु
	काष्ठा list_head *pos;
	काष्ठा fb_modelist *modelist;
	काष्ठा fb_videomode *m;
	पूर्णांक found = 0;

	list_क्रम_each(pos, head) अणु
		modelist = list_entry(pos, काष्ठा fb_modelist, list);
		m = &modelist->mode;
		अगर (fb_mode_is_equal(m, mode)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		modelist = kदो_स्मृति(माप(काष्ठा fb_modelist),
						  GFP_KERNEL);

		अगर (!modelist)
			वापस -ENOMEM;
		modelist->mode = *mode;
		list_add(&modelist->list, head);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * fb_delete_videomode - हटाओd videomode entry from modelist
 * @mode: videomode to हटाओ
 * @head: काष्ठा list_head of modelist
 *
 * NOTES:
 * Will हटाओ all matching mode entries
 */
व्योम fb_delete_videomode(स्थिर काष्ठा fb_videomode *mode,
			 काष्ठा list_head *head)
अणु
	काष्ठा list_head *pos, *n;
	काष्ठा fb_modelist *modelist;
	काष्ठा fb_videomode *m;

	list_क्रम_each_safe(pos, n, head) अणु
		modelist = list_entry(pos, काष्ठा fb_modelist, list);
		m = &modelist->mode;
		अगर (fb_mode_is_equal(m, mode)) अणु
			list_del(pos);
			kमुक्त(pos);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * fb_destroy_modelist - destroy modelist
 * @head: काष्ठा list_head of modelist
 */
व्योम fb_destroy_modelist(काष्ठा list_head *head)
अणु
	काष्ठा list_head *pos, *n;

	list_क्रम_each_safe(pos, n, head) अणु
		list_del(pos);
		kमुक्त(pos);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fb_destroy_modelist);

/**
 * fb_videomode_to_modelist - convert mode array to mode list
 * @modedb: array of काष्ठा fb_videomode
 * @num: number of entries in array
 * @head: काष्ठा list_head of modelist
 */
व्योम fb_videomode_to_modelist(स्थिर काष्ठा fb_videomode *modedb, पूर्णांक num,
			      काष्ठा list_head *head)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(head);

	क्रम (i = 0; i < num; i++) अणु
		अगर (fb_add_videomode(&modedb[i], head))
			वापस;
	पूर्ण
पूर्ण

स्थिर काष्ठा fb_videomode *fb_find_best_display(स्थिर काष्ठा fb_monspecs *specs,
					        काष्ठा list_head *head)
अणु
	काष्ठा list_head *pos;
	काष्ठा fb_modelist *modelist;
	स्थिर काष्ठा fb_videomode *m, *m1 = शून्य, *md = शून्य, *best = शून्य;
	पूर्णांक first = 0;

	अगर (!head->prev || !head->next || list_empty(head))
		जाओ finished;

	/* get the first detailed mode and the very first mode */
	list_क्रम_each(pos, head) अणु
		modelist = list_entry(pos, काष्ठा fb_modelist, list);
		m = &modelist->mode;

		अगर (!first) अणु
			m1 = m;
			first = 1;
		पूर्ण

		अगर (m->flag & FB_MODE_IS_FIRST) अणु
 			md = m;
			अवरोध;
		पूर्ण
	पूर्ण

	/* first detailed timing is preferred */
	अगर (specs->misc & FB_MISC_1ST_DETAIL) अणु
		best = md;
		जाओ finished;
	पूर्ण

	/* find best mode based on display width and height */
	अगर (specs->max_x && specs->max_y) अणु
		काष्ठा fb_var_screeninfo var;

		स_रखो(&var, 0, माप(काष्ठा fb_var_screeninfo));
		var.xres = (specs->max_x * 7200)/254;
		var.yres = (specs->max_y * 7200)/254;
		m = fb_find_best_mode(&var, head);
		अगर (m) अणु
			best = m;
			जाओ finished;
		पूर्ण
	पूर्ण

	/* use first detailed mode */
	अगर (md) अणु
		best = md;
		जाओ finished;
	पूर्ण

	/* last resort, use the very first mode */
	best = m1;
finished:
	वापस best;
पूर्ण
EXPORT_SYMBOL(fb_find_best_display);

EXPORT_SYMBOL(fb_videomode_to_var);
EXPORT_SYMBOL(fb_var_to_videomode);
EXPORT_SYMBOL(fb_mode_is_equal);
EXPORT_SYMBOL(fb_add_videomode);
EXPORT_SYMBOL(fb_match_mode);
EXPORT_SYMBOL(fb_find_best_mode);
EXPORT_SYMBOL(fb_find_nearest_mode);
EXPORT_SYMBOL(fb_videomode_to_modelist);
EXPORT_SYMBOL(fb_find_mode);
EXPORT_SYMBOL(fb_find_mode_cvt);
