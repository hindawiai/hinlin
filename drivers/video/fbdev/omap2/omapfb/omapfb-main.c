<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/omapfb-मुख्य.c
 *
 * Copyright (C) 2008 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/omapfb.h>

#समावेश <video/omapfb_dss.h>
#समावेश <video/omapvrfb.h>

#समावेश "omapfb.h"

#घोषणा MODULE_NAME     "omapfb"

#घोषणा OMAPFB_PLANE_XRES_MIN		8
#घोषणा OMAPFB_PLANE_YRES_MIN		8

अटल अक्षर *def_mode;
अटल अक्षर *def_vram;
अटल bool def_vrfb;
अटल पूर्णांक def_rotate;
अटल bool def_mirror;
अटल bool स्वतः_update;
अटल अचिन्हित पूर्णांक स्वतः_update_freq;
module_param(स्वतः_update, bool, 0);
module_param(स्वतः_update_freq, uपूर्णांक, 0644);

#अगर_घोषित DEBUG
bool omapfb_debug;
module_param_named(debug, omapfb_debug, bool, 0644);
अटल bool omapfb_test_pattern;
module_param_named(test, omapfb_test_pattern, bool, 0644);
#पूर्ण_अगर

अटल पूर्णांक omapfb_fb_init(काष्ठा omapfb2_device *fbdev, काष्ठा fb_info *fbi);
अटल पूर्णांक omapfb_get_recommended_bpp(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_dss_device *dssdev);

#अगर_घोषित DEBUG
अटल व्योम draw_pixel(काष्ठा fb_info *fbi, पूर्णांक x, पूर्णांक y, अचिन्हित color)
अणु
	काष्ठा fb_var_screeninfo *var = &fbi->var;
	काष्ठा fb_fix_screeninfo *fix = &fbi->fix;
	व्योम __iomem *addr = fbi->screen_base;
	स्थिर अचिन्हित bytespp = var->bits_per_pixel >> 3;
	स्थिर अचिन्हित line_len = fix->line_length / bytespp;

	पूर्णांक r = (color >> 16) & 0xff;
	पूर्णांक g = (color >> 8) & 0xff;
	पूर्णांक b = (color >> 0) & 0xff;

	अगर (var->bits_per_pixel == 16) अणु
		u16 __iomem *p = (u16 __iomem *)addr;
		p += y * line_len + x;

		r = r * 32 / 256;
		g = g * 64 / 256;
		b = b * 32 / 256;

		__raw_ग_लिखोw((r << 11) | (g << 5) | (b << 0), p);
	पूर्ण अन्यथा अगर (var->bits_per_pixel == 24) अणु
		u8 __iomem *p = (u8 __iomem *)addr;
		p += (y * line_len + x) * 3;

		__raw_ग_लिखोb(b, p + 0);
		__raw_ग_लिखोb(g, p + 1);
		__raw_ग_लिखोb(r, p + 2);
	पूर्ण अन्यथा अगर (var->bits_per_pixel == 32) अणु
		u32 __iomem *p = (u32 __iomem *)addr;
		p += y * line_len + x;
		__raw_ग_लिखोl(color, p);
	पूर्ण
पूर्ण

अटल व्योम fill_fb(काष्ठा fb_info *fbi)
अणु
	काष्ठा fb_var_screeninfo *var = &fbi->var;
	स्थिर लघु w = var->xres_भव;
	स्थिर लघु h = var->yres_भव;
	व्योम __iomem *addr = fbi->screen_base;
	पूर्णांक y, x;

	अगर (!addr)
		वापस;

	DBG("fill_fb %dx%d, line_len %d bytes\n", w, h, fbi->fix.line_length);

	क्रम (y = 0; y < h; y++) अणु
		क्रम (x = 0; x < w; x++) अणु
			अगर (x < 20 && y < 20)
				draw_pixel(fbi, x, y, 0xffffff);
			अन्यथा अगर (x < 20 && (y > 20 && y < h - 20))
				draw_pixel(fbi, x, y, 0xff);
			अन्यथा अगर (y < 20 && (x > 20 && x < w - 20))
				draw_pixel(fbi, x, y, 0xff00);
			अन्यथा अगर (x > w - 20 && (y > 20 && y < h - 20))
				draw_pixel(fbi, x, y, 0xff0000);
			अन्यथा अगर (y > h - 20 && (x > 20 && x < w - 20))
				draw_pixel(fbi, x, y, 0xffff00);
			अन्यथा अगर (x == 20 || x == w - 20 ||
					y == 20 || y == h - 20)
				draw_pixel(fbi, x, y, 0xffffff);
			अन्यथा अगर (x == y || w - x == h - y)
				draw_pixel(fbi, x, y, 0xff00ff);
			अन्यथा अगर (w - x == y || x == h - y)
				draw_pixel(fbi, x, y, 0x00ffff);
			अन्यथा अगर (x > 20 && y > 20 && x < w - 20 && y < h - 20) अणु
				पूर्णांक t = x * 3 / w;
				अचिन्हित r = 0, g = 0, b = 0;
				अचिन्हित c;
				अगर (var->bits_per_pixel == 16) अणु
					अगर (t == 0)
						b = (y % 32) * 256 / 32;
					अन्यथा अगर (t == 1)
						g = (y % 64) * 256 / 64;
					अन्यथा अगर (t == 2)
						r = (y % 32) * 256 / 32;
				पूर्ण अन्यथा अणु
					अगर (t == 0)
						b = (y % 256);
					अन्यथा अगर (t == 1)
						g = (y % 256);
					अन्यथा अगर (t == 2)
						r = (y % 256);
				पूर्ण
				c = (r << 16) | (g << 8) | (b << 0);
				draw_pixel(fbi, x, y, c);
			पूर्ण अन्यथा अणु
				draw_pixel(fbi, x, y, 0);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित omapfb_get_vrfb_offset(स्थिर काष्ठा omapfb_info *ofbi, पूर्णांक rot)
अणु
	स्थिर काष्ठा vrfb *vrfb = &ofbi->region->vrfb;
	अचिन्हित offset;

	चयन (rot) अणु
	हाल FB_ROTATE_UR:
		offset = 0;
		अवरोध;
	हाल FB_ROTATE_CW:
		offset = vrfb->yoffset;
		अवरोध;
	हाल FB_ROTATE_UD:
		offset = vrfb->yoffset * OMAP_VRFB_LINE_LEN + vrfb->xoffset;
		अवरोध;
	हाल FB_ROTATE_CCW:
		offset = vrfb->xoffset * OMAP_VRFB_LINE_LEN;
		अवरोध;
	शेष:
		BUG();
		वापस 0;
	पूर्ण

	offset *= vrfb->bytespp;

	वापस offset;
पूर्ण

अटल u32 omapfb_get_region_rot_paddr(स्थिर काष्ठा omapfb_info *ofbi, पूर्णांक rot)
अणु
	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) अणु
		वापस ofbi->region->vrfb.paddr[rot]
			+ omapfb_get_vrfb_offset(ofbi, rot);
	पूर्ण अन्यथा अणु
		वापस ofbi->region->paddr;
	पूर्ण
पूर्ण

अटल u32 omapfb_get_region_paddr(स्थिर काष्ठा omapfb_info *ofbi)
अणु
	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB)
		वापस ofbi->region->vrfb.paddr[0];
	अन्यथा
		वापस ofbi->region->paddr;
पूर्ण

अटल व्योम __iomem *omapfb_get_region_vaddr(स्थिर काष्ठा omapfb_info *ofbi)
अणु
	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB)
		वापस ofbi->region->vrfb.vaddr[0];
	अन्यथा
		वापस ofbi->region->vaddr;
पूर्ण

अटल काष्ठा omapfb_colormode omapfb_colormodes[] = अणु
	अणु
		.dssmode = OMAP_DSS_COLOR_UYVY,
		.bits_per_pixel = 16,
		.nonstd = OMAPFB_COLOR_YUV422,
	पूर्ण, अणु
		.dssmode = OMAP_DSS_COLOR_YUV2,
		.bits_per_pixel = 16,
		.nonstd = OMAPFB_COLOR_YUY422,
	पूर्ण, अणु
		.dssmode = OMAP_DSS_COLOR_ARGB16,
		.bits_per_pixel = 16,
		.red	= अणु .length = 4, .offset = 8, .msb_right = 0 पूर्ण,
		.green	= अणु .length = 4, .offset = 4, .msb_right = 0 पूर्ण,
		.blue	= अणु .length = 4, .offset = 0, .msb_right = 0 पूर्ण,
		.transp	= अणु .length = 4, .offset = 12, .msb_right = 0 पूर्ण,
	पूर्ण, अणु
		.dssmode = OMAP_DSS_COLOR_RGB16,
		.bits_per_pixel = 16,
		.red	= अणु .length = 5, .offset = 11, .msb_right = 0 पूर्ण,
		.green	= अणु .length = 6, .offset = 5, .msb_right = 0 पूर्ण,
		.blue	= अणु .length = 5, .offset = 0, .msb_right = 0 पूर्ण,
		.transp	= अणु .length = 0, .offset = 0, .msb_right = 0 पूर्ण,
	पूर्ण, अणु
		.dssmode = OMAP_DSS_COLOR_RGB24P,
		.bits_per_pixel = 24,
		.red	= अणु .length = 8, .offset = 16, .msb_right = 0 पूर्ण,
		.green	= अणु .length = 8, .offset = 8, .msb_right = 0 पूर्ण,
		.blue	= अणु .length = 8, .offset = 0, .msb_right = 0 पूर्ण,
		.transp	= अणु .length = 0, .offset = 0, .msb_right = 0 पूर्ण,
	पूर्ण, अणु
		.dssmode = OMAP_DSS_COLOR_RGB24U,
		.bits_per_pixel = 32,
		.red	= अणु .length = 8, .offset = 16, .msb_right = 0 पूर्ण,
		.green	= अणु .length = 8, .offset = 8, .msb_right = 0 पूर्ण,
		.blue	= अणु .length = 8, .offset = 0, .msb_right = 0 पूर्ण,
		.transp	= अणु .length = 0, .offset = 0, .msb_right = 0 पूर्ण,
	पूर्ण, अणु
		.dssmode = OMAP_DSS_COLOR_ARGB32,
		.bits_per_pixel = 32,
		.red	= अणु .length = 8, .offset = 16, .msb_right = 0 पूर्ण,
		.green	= अणु .length = 8, .offset = 8, .msb_right = 0 पूर्ण,
		.blue	= अणु .length = 8, .offset = 0, .msb_right = 0 पूर्ण,
		.transp	= अणु .length = 8, .offset = 24, .msb_right = 0 पूर्ण,
	पूर्ण, अणु
		.dssmode = OMAP_DSS_COLOR_RGBA32,
		.bits_per_pixel = 32,
		.red	= अणु .length = 8, .offset = 24, .msb_right = 0 पूर्ण,
		.green	= अणु .length = 8, .offset = 16, .msb_right = 0 पूर्ण,
		.blue	= अणु .length = 8, .offset = 8, .msb_right = 0 पूर्ण,
		.transp	= अणु .length = 8, .offset = 0, .msb_right = 0 पूर्ण,
	पूर्ण, अणु
		.dssmode = OMAP_DSS_COLOR_RGBX32,
		.bits_per_pixel = 32,
		.red	= अणु .length = 8, .offset = 24, .msb_right = 0 पूर्ण,
		.green	= अणु .length = 8, .offset = 16, .msb_right = 0 पूर्ण,
		.blue	= अणु .length = 8, .offset = 8, .msb_right = 0 पूर्ण,
		.transp	= अणु .length = 0, .offset = 0, .msb_right = 0 पूर्ण,
	पूर्ण,
पूर्ण;

अटल bool cmp_component(काष्ठा fb_bitfield *f1, काष्ठा fb_bitfield *f2)
अणु
	वापस f1->length == f2->length &&
		f1->offset == f2->offset &&
		f1->msb_right == f2->msb_right;
पूर्ण

अटल bool cmp_var_to_colormode(काष्ठा fb_var_screeninfo *var,
		काष्ठा omapfb_colormode *color)
अणु
	अगर (var->bits_per_pixel == 0 ||
			var->red.length == 0 ||
			var->blue.length == 0 ||
			var->green.length == 0)
		वापस false;

	वापस var->bits_per_pixel == color->bits_per_pixel &&
		cmp_component(&var->red, &color->red) &&
		cmp_component(&var->green, &color->green) &&
		cmp_component(&var->blue, &color->blue) &&
		cmp_component(&var->transp, &color->transp);
पूर्ण

अटल व्योम assign_colormode_to_var(काष्ठा fb_var_screeninfo *var,
		काष्ठा omapfb_colormode *color)
अणु
	var->bits_per_pixel = color->bits_per_pixel;
	var->nonstd = color->nonstd;
	var->red = color->red;
	var->green = color->green;
	var->blue = color->blue;
	var->transp = color->transp;
पूर्ण

अटल पूर्णांक fb_mode_to_dss_mode(काष्ठा fb_var_screeninfo *var,
		क्रमागत omap_color_mode *mode)
अणु
	क्रमागत omap_color_mode dssmode;
	पूर्णांक i;

	/* first match with nonstd field */
	अगर (var->nonstd) अणु
		क्रम (i = 0; i < ARRAY_SIZE(omapfb_colormodes); ++i) अणु
			काष्ठा omapfb_colormode *m = &omapfb_colormodes[i];
			अगर (var->nonstd == m->nonstd) अणु
				assign_colormode_to_var(var, m);
				*mode = m->dssmode;
				वापस 0;
			पूर्ण
		पूर्ण

		वापस -EINVAL;
	पूर्ण

	/* then try exact match of bpp and colors */
	क्रम (i = 0; i < ARRAY_SIZE(omapfb_colormodes); ++i) अणु
		काष्ठा omapfb_colormode *m = &omapfb_colormodes[i];
		अगर (cmp_var_to_colormode(var, m)) अणु
			assign_colormode_to_var(var, m);
			*mode = m->dssmode;
			वापस 0;
		पूर्ण
	पूर्ण

	/* match with bpp अगर user has not filled color fields
	 * properly */
	चयन (var->bits_per_pixel) अणु
	हाल 1:
		dssmode = OMAP_DSS_COLOR_CLUT1;
		अवरोध;
	हाल 2:
		dssmode = OMAP_DSS_COLOR_CLUT2;
		अवरोध;
	हाल 4:
		dssmode = OMAP_DSS_COLOR_CLUT4;
		अवरोध;
	हाल 8:
		dssmode = OMAP_DSS_COLOR_CLUT8;
		अवरोध;
	हाल 12:
		dssmode = OMAP_DSS_COLOR_RGB12U;
		अवरोध;
	हाल 16:
		dssmode = OMAP_DSS_COLOR_RGB16;
		अवरोध;
	हाल 24:
		dssmode = OMAP_DSS_COLOR_RGB24P;
		अवरोध;
	हाल 32:
		dssmode = OMAP_DSS_COLOR_RGB24U;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(omapfb_colormodes); ++i) अणु
		काष्ठा omapfb_colormode *m = &omapfb_colormodes[i];
		अगर (dssmode == m->dssmode) अणु
			assign_colormode_to_var(var, m);
			*mode = m->dssmode;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक check_fb_res_bounds(काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक xres_min = OMAPFB_PLANE_XRES_MIN;
	पूर्णांक xres_max = 2048;
	पूर्णांक yres_min = OMAPFB_PLANE_YRES_MIN;
	पूर्णांक yres_max = 2048;

	/* XXX: some applications seem to set भव res to 0. */
	अगर (var->xres_भव == 0)
		var->xres_भव = var->xres;

	अगर (var->yres_भव == 0)
		var->yres_भव = var->yres;

	अगर (var->xres_भव < xres_min || var->yres_भव < yres_min)
		वापस -EINVAL;

	अगर (var->xres < xres_min)
		var->xres = xres_min;
	अगर (var->yres < yres_min)
		var->yres = yres_min;
	अगर (var->xres > xres_max)
		var->xres = xres_max;
	अगर (var->yres > yres_max)
		var->yres = yres_max;

	अगर (var->xres > var->xres_भव)
		var->xres = var->xres_भव;
	अगर (var->yres > var->yres_भव)
		var->yres = var->yres_भव;

	वापस 0;
पूर्ण

अटल व्योम shrink_height(अचिन्हित दीर्घ max_frame_size,
		काष्ठा fb_var_screeninfo *var)
अणु
	DBG("can't fit FB into memory, reducing y\n");
	var->yres_भव = max_frame_size /
		(var->xres_भव * var->bits_per_pixel >> 3);

	अगर (var->yres_भव < OMAPFB_PLANE_YRES_MIN)
		var->yres_भव = OMAPFB_PLANE_YRES_MIN;

	अगर (var->yres > var->yres_भव)
		var->yres = var->yres_भव;
पूर्ण

अटल व्योम shrink_width(अचिन्हित दीर्घ max_frame_size,
		काष्ठा fb_var_screeninfo *var)
अणु
	DBG("can't fit FB into memory, reducing x\n");
	var->xres_भव = max_frame_size / var->yres_भव /
		(var->bits_per_pixel >> 3);

	अगर (var->xres_भव < OMAPFB_PLANE_XRES_MIN)
		var->xres_भव = OMAPFB_PLANE_XRES_MIN;

	अगर (var->xres > var->xres_भव)
		var->xres = var->xres_भव;
पूर्ण

अटल पूर्णांक check_vrfb_fb_size(अचिन्हित दीर्घ region_size,
		स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	अचिन्हित दीर्घ min_phys_size = omap_vrfb_min_phys_size(var->xres_भव,
		var->yres_भव, var->bits_per_pixel >> 3);

	वापस min_phys_size > region_size ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक check_fb_size(स्थिर काष्ठा omapfb_info *ofbi,
		काष्ठा fb_var_screeninfo *var)
अणु
	अचिन्हित दीर्घ max_frame_size = ofbi->region->size;
	पूर्णांक bytespp = var->bits_per_pixel >> 3;
	अचिन्हित दीर्घ line_size = var->xres_भव * bytespp;

	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) अणु
		/* One needs to check क्रम both VRFB and OMAPFB limitations. */
		अगर (check_vrfb_fb_size(max_frame_size, var))
			shrink_height(omap_vrfb_max_height(
				max_frame_size, var->xres_भव, bytespp) *
				line_size, var);

		अगर (check_vrfb_fb_size(max_frame_size, var)) अणु
			DBG("cannot fit FB to memory\n");
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण

	DBG("max frame size %lu, line size %lu\n", max_frame_size, line_size);

	अगर (line_size * var->yres_भव > max_frame_size)
		shrink_height(max_frame_size, var);

	अगर (line_size * var->yres_भव > max_frame_size) अणु
		shrink_width(max_frame_size, var);
		line_size = var->xres_भव * bytespp;
	पूर्ण

	अगर (line_size * var->yres_भव > max_frame_size) अणु
		DBG("cannot fit FB to memory\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Consider अगर VRFB assisted rotation is in use and अगर the भव space क्रम
 * the zero degree view needs to be mapped. The need क्रम mapping also acts as
 * the trigger क्रम setting up the hardware on the context in question. This
 * ensures that one करोes not attempt to access the भव view beक्रमe the
 * hardware is serving the address translations.
 */
अटल पूर्णांक setup_vrfb_rotation(काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_mem_region *rg = ofbi->region;
	काष्ठा vrfb *vrfb = &rg->vrfb;
	काष्ठा fb_var_screeninfo *var = &fbi->var;
	काष्ठा fb_fix_screeninfo *fix = &fbi->fix;
	अचिन्हित bytespp;
	bool yuv_mode;
	क्रमागत omap_color_mode mode;
	पूर्णांक r;
	bool reconf;

	अगर (!rg->size || ofbi->rotation_type != OMAP_DSS_ROT_VRFB)
		वापस 0;

	DBG("setup_vrfb_rotation\n");

	r = fb_mode_to_dss_mode(var, &mode);
	अगर (r)
		वापस r;

	bytespp = var->bits_per_pixel >> 3;

	yuv_mode = mode == OMAP_DSS_COLOR_YUV2 || mode == OMAP_DSS_COLOR_UYVY;

	/* We need to reconfigure VRFB अगर the resolution changes, अगर yuv mode
	 * is enabled/disabled, or अगर bytes per pixel changes */

	/* XXX we shouldn't allow this when framebuffer is mmapped */

	reconf = false;

	अगर (yuv_mode != vrfb->yuv_mode)
		reconf = true;
	अन्यथा अगर (bytespp != vrfb->bytespp)
		reconf = true;
	अन्यथा अगर (vrfb->xres != var->xres_भव ||
			vrfb->yres != var->yres_भव)
		reconf = true;

	अगर (vrfb->vaddr[0] && reconf) अणु
		fbi->screen_base = शून्य;
		fix->smem_start = 0;
		fix->smem_len = 0;
		iounmap(vrfb->vaddr[0]);
		vrfb->vaddr[0] = शून्य;
		DBG("setup_vrfb_rotation: reset fb\n");
	पूर्ण

	अगर (vrfb->vaddr[0])
		वापस 0;

	omap_vrfb_setup(&rg->vrfb, rg->paddr,
			var->xres_भव,
			var->yres_भव,
			bytespp, yuv_mode);

	/* Now one can ioremap the 0 angle view */
	r = omap_vrfb_map_angle(vrfb, var->yres_भव, 0);
	अगर (r)
		वापस r;

	/* used by खोलो/ग_लिखो in fbmem.c */
	fbi->screen_base = ofbi->region->vrfb.vaddr[0];

	fix->smem_start = ofbi->region->vrfb.paddr[0];

	चयन (var->nonstd) अणु
	हाल OMAPFB_COLOR_YUV422:
	हाल OMAPFB_COLOR_YUY422:
		fix->line_length =
			(OMAP_VRFB_LINE_LEN * var->bits_per_pixel) >> 2;
		अवरोध;
	शेष:
		fix->line_length =
			(OMAP_VRFB_LINE_LEN * var->bits_per_pixel) >> 3;
		अवरोध;
	पूर्ण

	fix->smem_len = var->yres_भव * fix->line_length;

	वापस 0;
पूर्ण

पूर्णांक dss_mode_to_fb_mode(क्रमागत omap_color_mode dssmode,
			काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(omapfb_colormodes); ++i) अणु
		काष्ठा omapfb_colormode *mode = &omapfb_colormodes[i];
		अगर (dssmode == mode->dssmode) अणु
			assign_colormode_to_var(var, mode);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

व्योम set_fb_fix(काष्ठा fb_info *fbi)
अणु
	काष्ठा fb_fix_screeninfo *fix = &fbi->fix;
	काष्ठा fb_var_screeninfo *var = &fbi->var;
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_mem_region *rg = ofbi->region;

	DBG("set_fb_fix\n");

	/* used by खोलो/ग_लिखो in fbmem.c */
	fbi->screen_base = (अक्षर __iomem *)omapfb_get_region_vaddr(ofbi);

	/* used by mmap in fbmem.c */
	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) अणु
		चयन (var->nonstd) अणु
		हाल OMAPFB_COLOR_YUV422:
		हाल OMAPFB_COLOR_YUY422:
			fix->line_length =
				(OMAP_VRFB_LINE_LEN * var->bits_per_pixel) >> 2;
			अवरोध;
		शेष:
			fix->line_length =
				(OMAP_VRFB_LINE_LEN * var->bits_per_pixel) >> 3;
			अवरोध;
		पूर्ण

		fix->smem_len = var->yres_भव * fix->line_length;
	पूर्ण अन्यथा अणु
		fix->line_length =
			(var->xres_भव * var->bits_per_pixel) >> 3;
		fix->smem_len = rg->size;
	पूर्ण

	fix->smem_start = omapfb_get_region_paddr(ofbi);

	fix->type = FB_TYPE_PACKED_PIXELS;

	अगर (var->nonstd)
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा अणु
		चयन (var->bits_per_pixel) अणु
		हाल 32:
		हाल 24:
		हाल 16:
		हाल 12:
			fix->visual = FB_VISUAL_TRUECOLOR;
			/* 12bpp is stored in 16 bits */
			अवरोध;
		हाल 1:
		हाल 2:
		हाल 4:
		हाल 8:
			fix->visual = FB_VISUAL_PSEUDOCOLOR;
			अवरोध;
		पूर्ण
	पूर्ण

	fix->accel = FB_ACCEL_NONE;

	fix->xpanstep = 1;
	fix->ypanstep = 1;
पूर्ण

/* check new var and possibly modअगरy it to be ok */
पूर्णांक check_fb_var(काष्ठा fb_info *fbi, काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omap_dss_device *display = fb2display(fbi);
	क्रमागत omap_color_mode mode = 0;
	पूर्णांक i;
	पूर्णांक r;

	DBG("check_fb_var %d\n", ofbi->id);

	WARN_ON(!atomic_पढ़ो(&ofbi->region->lock_count));

	r = fb_mode_to_dss_mode(var, &mode);
	अगर (r) अणु
		DBG("cannot convert var to omap dss mode\n");
		वापस r;
	पूर्ण

	क्रम (i = 0; i < ofbi->num_overlays; ++i) अणु
		अगर ((ofbi->overlays[i]->supported_modes & mode) == 0) अणु
			DBG("invalid mode\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (var->rotate > 3)
		वापस -EINVAL;

	अगर (check_fb_res_bounds(var))
		वापस -EINVAL;

	/* When no memory is allocated ignore the size check */
	अगर (ofbi->region->size != 0 && check_fb_size(ofbi, var))
		वापस -EINVAL;

	अगर (var->xres + var->xoffset > var->xres_भव)
		var->xoffset = var->xres_भव - var->xres;
	अगर (var->yres + var->yoffset > var->yres_भव)
		var->yoffset = var->yres_भव - var->yres;

	DBG("xres = %d, yres = %d, vxres = %d, vyres = %d\n",
			var->xres, var->yres,
			var->xres_भव, var->yres_भव);

	अगर (display && display->driver->get_dimensions) अणु
		u32 w, h;
		display->driver->get_dimensions(display, &w, &h);
		var->width = DIV_ROUND_CLOSEST(w, 1000);
		var->height = DIV_ROUND_CLOSEST(h, 1000);
	पूर्ण अन्यथा अणु
		var->height = -1;
		var->width = -1;
	पूर्ण

	var->grayscale          = 0;

	अगर (display && display->driver->get_timings) अणु
		काष्ठा omap_video_timings timings;
		display->driver->get_timings(display, &timings);

		/* pixघड़ी in ps, the rest in pixघड़ी */
		var->pixघड़ी = timings.pixelघड़ी != 0 ?
			KHZ2PICOS(timings.pixelघड़ी / 1000) :
			0;
		var->left_margin = timings.hbp;
		var->right_margin = timings.hfp;
		var->upper_margin = timings.vbp;
		var->lower_margin = timings.vfp;
		var->hsync_len = timings.hsw;
		var->vsync_len = timings.vsw;
		var->sync |= timings.hsync_level == OMAPDSS_SIG_ACTIVE_HIGH ?
				FB_SYNC_HOR_HIGH_ACT : 0;
		var->sync |= timings.vsync_level == OMAPDSS_SIG_ACTIVE_HIGH ?
				FB_SYNC_VERT_HIGH_ACT : 0;
		var->vmode = timings.पूर्णांकerlace ?
				FB_VMODE_INTERLACED : FB_VMODE_NONINTERLACED;
	पूर्ण अन्यथा अणु
		var->pixघड़ी = 0;
		var->left_margin = 0;
		var->right_margin = 0;
		var->upper_margin = 0;
		var->lower_margin = 0;
		var->hsync_len = 0;
		var->vsync_len = 0;
		var->sync = 0;
		var->vmode = FB_VMODE_NONINTERLACED;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ---------------------------------------------------------------------------
 * fbdev framework callbacks
 * ---------------------------------------------------------------------------
 */
अटल पूर्णांक omapfb_खोलो(काष्ठा fb_info *fbi, पूर्णांक user)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_release(काष्ठा fb_info *fbi, पूर्णांक user)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित calc_rotation_offset_dma(स्थिर काष्ठा fb_var_screeninfo *var,
		स्थिर काष्ठा fb_fix_screeninfo *fix, पूर्णांक rotation)
अणु
	अचिन्हित offset;

	offset = var->yoffset * fix->line_length +
		var->xoffset * (var->bits_per_pixel >> 3);

	वापस offset;
पूर्ण

अटल अचिन्हित calc_rotation_offset_vrfb(स्थिर काष्ठा fb_var_screeninfo *var,
		स्थिर काष्ठा fb_fix_screeninfo *fix, पूर्णांक rotation)
अणु
	अचिन्हित offset;

	अगर (rotation == FB_ROTATE_UD)
		offset = (var->yres_भव - var->yres) *
			fix->line_length;
	अन्यथा अगर (rotation == FB_ROTATE_CW)
		offset = (var->yres_भव - var->yres) *
			(var->bits_per_pixel >> 3);
	अन्यथा
		offset = 0;

	अगर (rotation == FB_ROTATE_UR)
		offset += var->yoffset * fix->line_length +
			var->xoffset * (var->bits_per_pixel >> 3);
	अन्यथा अगर (rotation == FB_ROTATE_UD)
		offset -= var->yoffset * fix->line_length +
			var->xoffset * (var->bits_per_pixel >> 3);
	अन्यथा अगर (rotation == FB_ROTATE_CW)
		offset -= var->xoffset * fix->line_length +
			var->yoffset * (var->bits_per_pixel >> 3);
	अन्यथा अगर (rotation == FB_ROTATE_CCW)
		offset += var->xoffset * fix->line_length +
			var->yoffset * (var->bits_per_pixel >> 3);

	वापस offset;
पूर्ण

अटल व्योम omapfb_calc_addr(स्थिर काष्ठा omapfb_info *ofbi,
			     स्थिर काष्ठा fb_var_screeninfo *var,
			     स्थिर काष्ठा fb_fix_screeninfo *fix,
			     पूर्णांक rotation, u32 *paddr)
अणु
	u32 data_start_p;
	पूर्णांक offset;

	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB)
		data_start_p = omapfb_get_region_rot_paddr(ofbi, rotation);
	अन्यथा
		data_start_p = omapfb_get_region_paddr(ofbi);

	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB)
		offset = calc_rotation_offset_vrfb(var, fix, rotation);
	अन्यथा
		offset = calc_rotation_offset_dma(var, fix, rotation);

	data_start_p += offset;

	अगर (offset)
		DBG("offset %d, %d = %d\n",
		    var->xoffset, var->yoffset, offset);

	DBG("paddr %x\n", data_start_p);

	*paddr = data_start_p;
पूर्ण

/* setup overlay according to the fb */
पूर्णांक omapfb_setup_overlay(काष्ठा fb_info *fbi, काष्ठा omap_overlay *ovl,
		u16 posx, u16 posy, u16 outw, u16 outh)
अणु
	पूर्णांक r = 0;
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा fb_var_screeninfo *var = &fbi->var;
	काष्ठा fb_fix_screeninfo *fix = &fbi->fix;
	क्रमागत omap_color_mode mode = 0;
	u32 data_start_p = 0;
	काष्ठा omap_overlay_info info;
	पूर्णांक xres, yres;
	पूर्णांक screen_width;
	पूर्णांक mirror;
	पूर्णांक rotation = var->rotate;
	पूर्णांक i;

	WARN_ON(!atomic_पढ़ो(&ofbi->region->lock_count));

	क्रम (i = 0; i < ofbi->num_overlays; i++) अणु
		अगर (ovl != ofbi->overlays[i])
			जारी;

		rotation = (rotation + ofbi->rotation[i]) % 4;
		अवरोध;
	पूर्ण

	DBG("setup_overlay %d, posx %d, posy %d, outw %d, outh %d\n", ofbi->id,
			posx, posy, outw, outh);

	अगर (rotation == FB_ROTATE_CW || rotation == FB_ROTATE_CCW) अणु
		xres = var->yres;
		yres = var->xres;
	पूर्ण अन्यथा अणु
		xres = var->xres;
		yres = var->yres;
	पूर्ण

	अगर (ofbi->region->size)
		omapfb_calc_addr(ofbi, var, fix, rotation, &data_start_p);

	r = fb_mode_to_dss_mode(var, &mode);
	अगर (r) अणु
		DBG("fb_mode_to_dss_mode failed");
		जाओ err;
	पूर्ण

	चयन (var->nonstd) अणु
	हाल OMAPFB_COLOR_YUV422:
	हाल OMAPFB_COLOR_YUY422:
		अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) अणु
			screen_width = fix->line_length
				/ (var->bits_per_pixel >> 2);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		screen_width = fix->line_length / (var->bits_per_pixel >> 3);
		अवरोध;
	पूर्ण

	ovl->get_overlay_info(ovl, &info);

	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB)
		mirror = 0;
	अन्यथा
		mirror = ofbi->mirror;

	info.paddr = data_start_p;
	info.screen_width = screen_width;
	info.width = xres;
	info.height = yres;
	info.color_mode = mode;
	info.rotation_type = ofbi->rotation_type;
	info.rotation = rotation;
	info.mirror = mirror;

	info.pos_x = posx;
	info.pos_y = posy;
	info.out_width = outw;
	info.out_height = outh;

	r = ovl->set_overlay_info(ovl, &info);
	अगर (r) अणु
		DBG("ovl->setup_overlay_info failed\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	DBG("setup_overlay failed\n");
	वापस r;
पूर्ण

/* apply var to the overlay */
पूर्णांक omapfb_apply_changes(काष्ठा fb_info *fbi, पूर्णांक init)
अणु
	पूर्णांक r = 0;
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा fb_var_screeninfo *var = &fbi->var;
	काष्ठा omap_overlay *ovl;
	u16 posx, posy;
	u16 outw, outh;
	पूर्णांक i;

#अगर_घोषित DEBUG
	अगर (omapfb_test_pattern)
		fill_fb(fbi);
#पूर्ण_अगर

	WARN_ON(!atomic_पढ़ो(&ofbi->region->lock_count));

	क्रम (i = 0; i < ofbi->num_overlays; i++) अणु
		ovl = ofbi->overlays[i];

		DBG("apply_changes, fb %d, ovl %d\n", ofbi->id, ovl->id);

		अगर (ofbi->region->size == 0) अणु
			/* the fb is not available. disable the overlay */
			omapfb_overlay_enable(ovl, 0);
			अगर (!init && ovl->manager)
				ovl->manager->apply(ovl->manager);
			जारी;
		पूर्ण

		अगर (init || (ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0) अणु
			पूर्णांक rotation = (var->rotate + ofbi->rotation[i]) % 4;
			अगर (rotation == FB_ROTATE_CW ||
					rotation == FB_ROTATE_CCW) अणु
				outw = var->yres;
				outh = var->xres;
			पूर्ण अन्यथा अणु
				outw = var->xres;
				outh = var->yres;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा omap_overlay_info info;
			ovl->get_overlay_info(ovl, &info);
			outw = info.out_width;
			outh = info.out_height;
		पूर्ण

		अगर (init) अणु
			posx = 0;
			posy = 0;
		पूर्ण अन्यथा अणु
			काष्ठा omap_overlay_info info;
			ovl->get_overlay_info(ovl, &info);
			posx = info.pos_x;
			posy = info.pos_y;
		पूर्ण

		r = omapfb_setup_overlay(fbi, ovl, posx, posy, outw, outh);
		अगर (r)
			जाओ err;

		अगर (!init && ovl->manager)
			ovl->manager->apply(ovl->manager);
	पूर्ण
	वापस 0;
err:
	DBG("apply_changes failed\n");
	वापस r;
पूर्ण

/* checks var and eventually tweaks it to something supported,
 * DO NOT MODIFY PAR */
अटल पूर्णांक omapfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	पूर्णांक r;

	DBG("check_var(%d)\n", FB2OFB(fbi)->id);

	omapfb_get_mem_region(ofbi->region);

	r = check_fb_var(fbi, var);

	omapfb_put_mem_region(ofbi->region);

	वापस r;
पूर्ण

/* set the video mode according to info->var */
अटल पूर्णांक omapfb_set_par(काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	पूर्णांक r;

	DBG("set_par(%d)\n", FB2OFB(fbi)->id);

	omapfb_get_mem_region(ofbi->region);

	set_fb_fix(fbi);

	r = setup_vrfb_rotation(fbi);
	अगर (r)
		जाओ out;

	r = omapfb_apply_changes(fbi, 0);

 out:
	omapfb_put_mem_region(ofbi->region);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_pan_display(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा fb_var_screeninfo new_var;
	पूर्णांक r;

	DBG("pan_display(%d)\n", FB2OFB(fbi)->id);

	अगर (var->xoffset == fbi->var.xoffset &&
	    var->yoffset == fbi->var.yoffset)
		वापस 0;

	new_var = fbi->var;
	new_var.xoffset = var->xoffset;
	new_var.yoffset = var->yoffset;

	fbi->var = new_var;

	omapfb_get_mem_region(ofbi->region);

	r = omapfb_apply_changes(fbi, 0);

	omapfb_put_mem_region(ofbi->region);

	वापस r;
पूर्ण

अटल व्योम mmap_user_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा omapfb2_mem_region *rg = vma->vm_निजी_data;

	omapfb_get_mem_region(rg);
	atomic_inc(&rg->map_count);
	omapfb_put_mem_region(rg);
पूर्ण

अटल व्योम mmap_user_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा omapfb2_mem_region *rg = vma->vm_निजी_data;

	omapfb_get_mem_region(rg);
	atomic_dec(&rg->map_count);
	omapfb_put_mem_region(rg);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा mmap_user_ops = अणु
	.खोलो = mmap_user_खोलो,
	.बंद = mmap_user_बंद,
पूर्ण;

अटल पूर्णांक omapfb_mmap(काष्ठा fb_info *fbi, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा fb_fix_screeninfo *fix = &fbi->fix;
	काष्ठा omapfb2_mem_region *rg;
	अचिन्हित दीर्घ start;
	u32 len;
	पूर्णांक r;

	rg = omapfb_get_mem_region(ofbi->region);

	start = omapfb_get_region_paddr(ofbi);
	len = fix->smem_len;

	DBG("user mmap region start %lx, len %d, off %lx\n", start, len,
			vma->vm_pgoff << PAGE_SHIFT);

	vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
	vma->vm_ops = &mmap_user_ops;
	vma->vm_निजी_data = rg;

	r = vm_iomap_memory(vma, start, len);
	अगर (r)
		जाओ error;

	/* vm_ops.खोलो won't be called क्रम mmap itself. */
	atomic_inc(&rg->map_count);

	omapfb_put_mem_region(rg);

	वापस 0;

error:
	omapfb_put_mem_region(ofbi->region);

	वापस r;
पूर्ण

/* Store a single color palette entry पूर्णांकo a pseuकरो palette or the hardware
 * palette अगर one is available. For now we support only 16bpp and thus store
 * the entry only to the pseuकरो palette.
 */
अटल पूर्णांक _setcolreg(काष्ठा fb_info *fbi, u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green,
		u_पूर्णांक blue, u_पूर्णांक transp, पूर्णांक update_hw_pal)
अणु
	/*काष्ठा omapfb_info *ofbi = FB2OFB(fbi);*/
	/*काष्ठा omapfb2_device *fbdev = ofbi->fbdev;*/
	काष्ठा fb_var_screeninfo *var = &fbi->var;
	पूर्णांक r = 0;

	क्रमागत omapfb_color_क्रमmat mode = OMAPFB_COLOR_RGB24U; /* XXX */

	/*चयन (plane->color_mode) अणु*/
	चयन (mode) अणु
	हाल OMAPFB_COLOR_YUV422:
	हाल OMAPFB_COLOR_YUV420:
	हाल OMAPFB_COLOR_YUY422:
		r = -EINVAL;
		अवरोध;
	हाल OMAPFB_COLOR_CLUT_8BPP:
	हाल OMAPFB_COLOR_CLUT_4BPP:
	हाल OMAPFB_COLOR_CLUT_2BPP:
	हाल OMAPFB_COLOR_CLUT_1BPP:
		/*
		   अगर (fbdev->ctrl->setcolreg)
		   r = fbdev->ctrl->setcolreg(regno, red, green, blue,
		   transp, update_hw_pal);
		   */
		r = -EINVAL;
		अवरोध;
	हाल OMAPFB_COLOR_RGB565:
	हाल OMAPFB_COLOR_RGB444:
	हाल OMAPFB_COLOR_RGB24P:
	हाल OMAPFB_COLOR_RGB24U:
		अगर (regno < 16) अणु
			u32 pal;
			pal = ((red >> (16 - var->red.length)) <<
					var->red.offset) |
				((green >> (16 - var->green.length)) <<
				 var->green.offset) |
				(blue >> (16 - var->blue.length));
			((u32 *)(fbi->pseuकरो_palette))[regno] = pal;
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक omapfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	DBG("setcolreg\n");

	वापस _setcolreg(info, regno, red, green, blue, transp, 1);
पूर्ण

अटल पूर्णांक omapfb_setcmap(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info)
अणु
	पूर्णांक count, index, r;
	u16 *red, *green, *blue, *transp;
	u16 trans = 0xffff;

	DBG("setcmap\n");

	red     = cmap->red;
	green   = cmap->green;
	blue    = cmap->blue;
	transp  = cmap->transp;
	index   = cmap->start;

	क्रम (count = 0; count < cmap->len; count++) अणु
		अगर (transp)
			trans = *transp++;
		r = _setcolreg(info, index++, *red++, *green++, *blue++, trans,
				count == cmap->len - 1);
		अगर (r != 0)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_blank(पूर्णांक blank, काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omap_dss_device *display = fb2display(fbi);
	काष्ठा omapfb_display_data *d;
	पूर्णांक r = 0;

	अगर (!display)
		वापस -EINVAL;

	omapfb_lock(fbdev);

	d = get_display_data(fbdev, display);

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
		अगर (display->state == OMAP_DSS_DISPLAY_ACTIVE)
			जाओ निकास;

		r = display->driver->enable(display);

		अगर ((display->caps & OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE) &&
				d->update_mode == OMAPFB_AUTO_UPDATE &&
				!d->स्वतः_update_work_enabled)
			omapfb_start_स्वतः_update(fbdev, display);

		अवरोध;

	हाल FB_BLANK_NORMAL:
		/* FB_BLANK_NORMAL could be implemented.
		 * Needs DSS additions. */
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_POWERDOWN:
		अगर (display->state != OMAP_DSS_DISPLAY_ACTIVE)
			जाओ निकास;

		अगर (d->स्वतः_update_work_enabled)
			omapfb_stop_स्वतः_update(fbdev, display);

		display->driver->disable(display);

		अवरोध;

	शेष:
		r = -EINVAL;
	पूर्ण

निकास:
	omapfb_unlock(fbdev);

	वापस r;
पूर्ण

#अगर 0
/* XXX fb_पढ़ो and fb_ग_लिखो are needed क्रम VRFB */
sमाप_प्रकार omapfb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	DBG("omapfb_write %d, %lu\n", count, (अचिन्हित दीर्घ)*ppos);
	/* XXX needed क्रम VRFB */
	वापस count;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा fb_ops omapfb_ops = अणु
	.owner          = THIS_MODULE,
	.fb_खोलो        = omapfb_खोलो,
	.fb_release     = omapfb_release,
	.fb_fillrect    = cfb_fillrect,
	.fb_copyarea    = cfb_copyarea,
	.fb_imageblit   = cfb_imageblit,
	.fb_blank       = omapfb_blank,
	.fb_ioctl       = omapfb_ioctl,
	.fb_check_var   = omapfb_check_var,
	.fb_set_par     = omapfb_set_par,
	.fb_pan_display = omapfb_pan_display,
	.fb_mmap	= omapfb_mmap,
	.fb_setcolreg	= omapfb_setcolreg,
	.fb_setcmap	= omapfb_setcmap,
	/*.fb_ग_लिखो	= omapfb_ग_लिखो,*/
पूर्ण;

अटल व्योम omapfb_मुक्त_fbmem(काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omapfb2_mem_region *rg;

	rg = ofbi->region;

	अगर (rg->token == शून्य)
		वापस;

	WARN_ON(atomic_पढ़ो(&rg->map_count));

	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) अणु
		/* unmap the 0 angle rotation */
		अगर (rg->vrfb.vaddr[0]) अणु
			iounmap(rg->vrfb.vaddr[0]);
			rg->vrfb.vaddr[0] = शून्य;
		पूर्ण

		omap_vrfb_release_ctx(&rg->vrfb);
	पूर्ण

	dma_मुक्त_attrs(fbdev->dev, rg->size, rg->token, rg->dma_handle,
			rg->attrs);

	rg->token = शून्य;
	rg->vaddr = शून्य;
	rg->paddr = 0;
	rg->alloc = 0;
	rg->size = 0;
पूर्ण

अटल व्योम clear_fb_info(काष्ठा fb_info *fbi)
अणु
	स_रखो(&fbi->var, 0, माप(fbi->var));
	स_रखो(&fbi->fix, 0, माप(fbi->fix));
	strlcpy(fbi->fix.id, MODULE_NAME, माप(fbi->fix.id));
पूर्ण

अटल पूर्णांक omapfb_मुक्त_all_fbmem(काष्ठा omapfb2_device *fbdev)
अणु
	पूर्णांक i;

	DBG("free all fbmem\n");

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		काष्ठा fb_info *fbi = fbdev->fbs[i];
		omapfb_मुक्त_fbmem(fbi);
		clear_fb_info(fbi);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_alloc_fbmem(काष्ठा fb_info *fbi, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ paddr)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omapfb2_mem_region *rg;
	व्योम *token;
	अचिन्हित दीर्घ attrs;
	dma_addr_t dma_handle;
	पूर्णांक r;

	rg = ofbi->region;

	rg->paddr = 0;
	rg->vaddr = शून्य;
	स_रखो(&rg->vrfb, 0, माप rg->vrfb);
	rg->size = 0;
	rg->type = 0;
	rg->alloc = false;
	rg->map = false;

	size = PAGE_ALIGN(size);

	attrs = DMA_ATTR_WRITE_COMBINE;

	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB)
		attrs |= DMA_ATTR_NO_KERNEL_MAPPING;

	DBG("allocating %lu bytes for fb %d\n", size, ofbi->id);

	token = dma_alloc_attrs(fbdev->dev, size, &dma_handle,
			GFP_KERNEL, attrs);

	अगर (token == शून्य) अणु
		dev_err(fbdev->dev, "failed to allocate framebuffer\n");
		वापस -ENOMEM;
	पूर्ण

	DBG("allocated VRAM paddr %lx, vaddr %p\n",
			(अचिन्हित दीर्घ)dma_handle, token);

	अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) अणु
		r = omap_vrfb_request_ctx(&rg->vrfb);
		अगर (r) अणु
			dma_मुक्त_attrs(fbdev->dev, size, token, dma_handle,
					attrs);
			dev_err(fbdev->dev, "vrfb create ctx failed\n");
			वापस r;
		पूर्ण
	पूर्ण

	rg->attrs = attrs;
	rg->token = token;
	rg->dma_handle = dma_handle;

	rg->paddr = (अचिन्हित दीर्घ)dma_handle;
	rg->vaddr = (व्योम __iomem *)token;
	rg->size = size;
	rg->alloc = 1;

	वापस 0;
पूर्ण

/* allocate fbmem using display resolution as reference */
अटल पूर्णांक omapfb_alloc_fbmem_display(काष्ठा fb_info *fbi, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ paddr)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omap_dss_device *display;
	पूर्णांक bytespp;

	display =  fb2display(fbi);

	अगर (!display)
		वापस 0;

	चयन (omapfb_get_recommended_bpp(fbdev, display)) अणु
	हाल 16:
		bytespp = 2;
		अवरोध;
	हाल 24:
		bytespp = 4;
		अवरोध;
	शेष:
		bytespp = 4;
		अवरोध;
	पूर्ण

	अगर (!size) अणु
		u16 w, h;

		display->driver->get_resolution(display, &w, &h);

		अगर (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) अणु
			size = max(omap_vrfb_min_phys_size(w, h, bytespp),
					omap_vrfb_min_phys_size(h, w, bytespp));

			DBG("adjusting fb mem size for VRFB, %u -> %lu\n",
					w * h * bytespp, size);
		पूर्ण अन्यथा अणु
			size = w * h * bytespp;
		पूर्ण
	पूर्ण

	अगर (!size)
		वापस 0;

	वापस omapfb_alloc_fbmem(fbi, size, paddr);
पूर्ण

अटल पूर्णांक omapfb_parse_vram_param(स्थिर अक्षर *param, पूर्णांक max_entries,
		अचिन्हित दीर्घ *sizes, अचिन्हित दीर्घ *paddrs)
अणु
	अचिन्हित पूर्णांक fbnum;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ paddr = 0;
	अक्षर *p, *start;

	start = (अक्षर *)param;

	जबतक (1) अणु
		p = start;

		fbnum = simple_म_से_अदीर्घ(p, &p, 10);

		अगर (p == start)
			वापस -EINVAL;

		अगर (*p != ':')
			वापस -EINVAL;

		अगर (fbnum >= max_entries)
			वापस -EINVAL;

		size = memparse(p + 1, &p);

		अगर (!size)
			वापस -EINVAL;

		paddr = 0;

		अगर (*p == '@') अणु
			paddr = simple_म_से_अदीर्घ(p + 1, &p, 16);

			अगर (!paddr)
				वापस -EINVAL;

		पूर्ण

		WARN_ONCE(paddr,
			"reserving memory at predefined address not supported\n");

		paddrs[fbnum] = paddr;
		sizes[fbnum] = size;

		अगर (*p == 0)
			अवरोध;

		अगर (*p != ',')
			वापस -EINVAL;

		++p;

		start = p;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_allocate_all_fbs(काष्ठा omapfb2_device *fbdev)
अणु
	पूर्णांक i, r;
	अचिन्हित दीर्घ vram_sizes[10];
	अचिन्हित दीर्घ vram_paddrs[10];

	स_रखो(&vram_sizes, 0, माप(vram_sizes));
	स_रखो(&vram_paddrs, 0, माप(vram_paddrs));

	अगर (def_vram &&	omapfb_parse_vram_param(def_vram, 10,
				vram_sizes, vram_paddrs)) अणु
		dev_err(fbdev->dev, "failed to parse vram parameter\n");

		स_रखो(&vram_sizes, 0, माप(vram_sizes));
		स_रखो(&vram_paddrs, 0, माप(vram_paddrs));
	पूर्ण

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		/* allocate memory स्वतःmatically only क्रम fb0, or अगर
		 * excplicitly defined with vram or plat data option */
		अगर (i == 0 || vram_sizes[i] != 0) अणु
			r = omapfb_alloc_fbmem_display(fbdev->fbs[i],
					vram_sizes[i], vram_paddrs[i]);

			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		काष्ठा omapfb_info *ofbi = FB2OFB(fbdev->fbs[i]);
		काष्ठा omapfb2_mem_region *rg;
		rg = ofbi->region;

		DBG("region%d phys %08x virt %p size=%lu\n",
				i,
				rg->paddr,
				rg->vaddr,
				rg->size);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omapfb_clear_fb(काष्ठा fb_info *fbi)
अणु
	स्थिर काष्ठा fb_fillrect rect = अणु
		.dx = 0,
		.dy = 0,
		.width = fbi->var.xres_भव,
		.height = fbi->var.yres_भव,
		.color = 0,
		.rop = ROP_COPY,
	पूर्ण;

	cfb_fillrect(fbi, &rect);
पूर्ण

पूर्णांक omapfb_पुनः_स्मृति_fbmem(काष्ठा fb_info *fbi, अचिन्हित दीर्घ size, पूर्णांक type)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omapfb2_mem_region *rg = ofbi->region;
	अचिन्हित दीर्घ old_size = rg->size;
	अचिन्हित दीर्घ old_paddr = rg->paddr;
	पूर्णांक old_type = rg->type;
	पूर्णांक r;

	अगर (type != OMAPFB_MEMTYPE_SDRAM)
		वापस -EINVAL;

	size = PAGE_ALIGN(size);

	अगर (old_size == size && old_type == type)
		वापस 0;

	omapfb_मुक्त_fbmem(fbi);

	अगर (size == 0) अणु
		clear_fb_info(fbi);
		वापस 0;
	पूर्ण

	r = omapfb_alloc_fbmem(fbi, size, 0);

	अगर (r) अणु
		अगर (old_size)
			omapfb_alloc_fbmem(fbi, old_size, old_paddr);

		अगर (rg->size == 0)
			clear_fb_info(fbi);

		वापस r;
	पूर्ण

	अगर (old_size == size)
		वापस 0;

	अगर (old_size == 0) अणु
		DBG("initializing fb %d\n", ofbi->id);
		r = omapfb_fb_init(fbdev, fbi);
		अगर (r) अणु
			DBG("omapfb_fb_init failed\n");
			जाओ err;
		पूर्ण
		r = omapfb_apply_changes(fbi, 1);
		अगर (r) अणु
			DBG("omapfb_apply_changes failed\n");
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा fb_var_screeninfo new_var;
		स_नकल(&new_var, &fbi->var, माप(new_var));
		r = check_fb_var(fbi, &new_var);
		अगर (r)
			जाओ err;
		स_नकल(&fbi->var, &new_var, माप(fbi->var));
		set_fb_fix(fbi);
		r = setup_vrfb_rotation(fbi);
		अगर (r)
			जाओ err;
	पूर्ण

	omapfb_clear_fb(fbi);

	वापस 0;
err:
	omapfb_मुक्त_fbmem(fbi);
	clear_fb_info(fbi);
	वापस r;
पूर्ण

अटल व्योम omapfb_स्वतः_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा omap_dss_device *dssdev;
	काष्ठा omap_dss_driver *dssdrv;
	काष्ठा omapfb_display_data *d;
	u16 w, h;
	अचिन्हित पूर्णांक freq;
	काष्ठा omapfb2_device *fbdev;

	d = container_of(work, काष्ठा omapfb_display_data,
			स्वतः_update_work.work);

	dssdev = d->dssdev;
	dssdrv = dssdev->driver;
	fbdev = d->fbdev;

	अगर (!dssdrv || !dssdrv->update)
		वापस;

	अगर (dssdrv->sync)
		dssdrv->sync(dssdev);

	dssdrv->get_resolution(dssdev, &w, &h);
	dssdrv->update(dssdev, 0, 0, w, h);

	freq = स्वतः_update_freq;
	अगर (freq == 0)
		freq = 20;
	queue_delayed_work(fbdev->स्वतः_update_wq,
			&d->स्वतः_update_work, HZ / freq);
पूर्ण

व्योम omapfb_start_स्वतः_update(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_dss_device *display)
अणु
	काष्ठा omapfb_display_data *d;

	अगर (fbdev->स्वतः_update_wq == शून्य) अणु
		काष्ठा workqueue_काष्ठा *wq;

		wq = create_singlethपढ़ो_workqueue("omapfb_auto_update");

		अगर (wq == शून्य) अणु
			dev_err(fbdev->dev, "Failed to create workqueue for "
					"auto-update\n");
			वापस;
		पूर्ण

		fbdev->स्वतः_update_wq = wq;
	पूर्ण

	d = get_display_data(fbdev, display);

	INIT_DELAYED_WORK(&d->स्वतः_update_work, omapfb_स्वतः_update_work);

	d->स्वतः_update_work_enabled = true;

	omapfb_स्वतः_update_work(&d->स्वतः_update_work.work);
पूर्ण

व्योम omapfb_stop_स्वतः_update(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_dss_device *display)
अणु
	काष्ठा omapfb_display_data *d;

	d = get_display_data(fbdev, display);

	cancel_delayed_work_sync(&d->स्वतः_update_work);

	d->स्वतः_update_work_enabled = false;
पूर्ण

/* initialize fb_info, var, fix to something sane based on the display */
अटल पूर्णांक omapfb_fb_init(काष्ठा omapfb2_device *fbdev, काष्ठा fb_info *fbi)
अणु
	काष्ठा fb_var_screeninfo *var = &fbi->var;
	काष्ठा omap_dss_device *display = fb2display(fbi);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	पूर्णांक r = 0;

	fbi->fbops = &omapfb_ops;
	fbi->flags = FBINFO_FLAG_DEFAULT;
	fbi->pseuकरो_palette = fbdev->pseuकरो_palette;

	अगर (ofbi->region->size == 0) अणु
		clear_fb_info(fbi);
		वापस 0;
	पूर्ण

	var->nonstd = 0;
	var->bits_per_pixel = 0;

	var->rotate = def_rotate;

	अगर (display) अणु
		u16 w, h;
		पूर्णांक rotation = (var->rotate + ofbi->rotation[0]) % 4;

		display->driver->get_resolution(display, &w, &h);

		अगर (rotation == FB_ROTATE_CW ||
				rotation == FB_ROTATE_CCW) अणु
			var->xres = h;
			var->yres = w;
		पूर्ण अन्यथा अणु
			var->xres = w;
			var->yres = h;
		पूर्ण

		var->xres_भव = var->xres;
		var->yres_भव = var->yres;

		अगर (!var->bits_per_pixel) अणु
			चयन (omapfb_get_recommended_bpp(fbdev, display)) अणु
			हाल 16:
				var->bits_per_pixel = 16;
				अवरोध;
			हाल 24:
				var->bits_per_pixel = 32;
				अवरोध;
			शेष:
				dev_err(fbdev->dev, "illegal display "
						"bpp\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* अगर there's no display, let's just guess some basic values */
		var->xres = 320;
		var->yres = 240;
		var->xres_भव = var->xres;
		var->yres_भव = var->yres;
		अगर (!var->bits_per_pixel)
			var->bits_per_pixel = 16;
	पूर्ण

	r = check_fb_var(fbi, var);
	अगर (r)
		जाओ err;

	set_fb_fix(fbi);
	r = setup_vrfb_rotation(fbi);
	अगर (r)
		जाओ err;

	r = fb_alloc_cmap(&fbi->cmap, 256, 0);
	अगर (r)
		dev_err(fbdev->dev, "unable to allocate color map memory\n");

err:
	वापस r;
पूर्ण

अटल व्योम fbinfo_cleanup(काष्ठा omapfb2_device *fbdev, काष्ठा fb_info *fbi)
अणु
	fb_dealloc_cmap(&fbi->cmap);
पूर्ण


अटल व्योम omapfb_मुक्त_resources(काष्ठा omapfb2_device *fbdev)
अणु
	पूर्णांक i;

	DBG("free_resources\n");

	अगर (fbdev == शून्य)
		वापस;

	क्रम (i = 0; i < fbdev->num_overlays; i++) अणु
		काष्ठा omap_overlay *ovl = fbdev->overlays[i];

		ovl->disable(ovl);

		अगर (ovl->manager)
			ovl->unset_manager(ovl);
	पूर्ण

	क्रम (i = 0; i < fbdev->num_fbs; i++)
		unरेजिस्टर_framebuffer(fbdev->fbs[i]);

	/* मुक्त the reserved fbmem */
	omapfb_मुक्त_all_fbmem(fbdev);

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		fbinfo_cleanup(fbdev, fbdev->fbs[i]);
		framebuffer_release(fbdev->fbs[i]);
	पूर्ण

	क्रम (i = 0; i < fbdev->num_displays; i++) अणु
		काष्ठा omap_dss_device *dssdev = fbdev->displays[i].dssdev;

		अगर (fbdev->displays[i].स्वतः_update_work_enabled)
			omapfb_stop_स्वतः_update(fbdev, dssdev);

		अगर (dssdev->state != OMAP_DSS_DISPLAY_DISABLED)
			dssdev->driver->disable(dssdev);

		dssdev->driver->disconnect(dssdev);

		omap_dss_put_device(dssdev);
	पूर्ण

	अगर (fbdev->स्वतः_update_wq != शून्य) अणु
		flush_workqueue(fbdev->स्वतः_update_wq);
		destroy_workqueue(fbdev->स्वतः_update_wq);
		fbdev->स्वतः_update_wq = शून्य;
	पूर्ण

	dev_set_drvdata(fbdev->dev, शून्य);
पूर्ण

अटल पूर्णांक omapfb_create_framebuffers(काष्ठा omapfb2_device *fbdev)
अणु
	पूर्णांक r, i;

	fbdev->num_fbs = 0;

	DBG("create %d framebuffers\n",	CONFIG_FB_OMAP2_NUM_FBS);

	/* allocate fb_infos */
	क्रम (i = 0; i < CONFIG_FB_OMAP2_NUM_FBS; i++) अणु
		काष्ठा fb_info *fbi;
		काष्ठा omapfb_info *ofbi;

		fbi = framebuffer_alloc(माप(काष्ठा omapfb_info),
				fbdev->dev);
		अगर (!fbi)
			वापस -ENOMEM;

		clear_fb_info(fbi);

		fbdev->fbs[i] = fbi;

		ofbi = FB2OFB(fbi);
		ofbi->fbdev = fbdev;
		ofbi->id = i;

		ofbi->region = &fbdev->regions[i];
		ofbi->region->id = i;
		init_rwsem(&ofbi->region->lock);

		/* assign these early, so that fb alloc can use them */
		ofbi->rotation_type = def_vrfb ? OMAP_DSS_ROT_VRFB :
			OMAP_DSS_ROT_DMA;
		ofbi->mirror = def_mirror;

		fbdev->num_fbs++;
	पूर्ण

	DBG("fb_infos allocated\n");

	/* assign overlays क्रम the fbs */
	क्रम (i = 0; i < min(fbdev->num_fbs, fbdev->num_overlays); i++) अणु
		काष्ठा omapfb_info *ofbi = FB2OFB(fbdev->fbs[i]);

		ofbi->overlays[0] = fbdev->overlays[i];
		ofbi->num_overlays = 1;
	पूर्ण

	/* allocate fb memories */
	r = omapfb_allocate_all_fbs(fbdev);
	अगर (r) अणु
		dev_err(fbdev->dev, "failed to allocate fbmem\n");
		वापस r;
	पूर्ण

	DBG("fbmems allocated\n");

	/* setup fb_infos */
	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		काष्ठा fb_info *fbi = fbdev->fbs[i];
		काष्ठा omapfb_info *ofbi = FB2OFB(fbi);

		omapfb_get_mem_region(ofbi->region);
		r = omapfb_fb_init(fbdev, fbi);
		omapfb_put_mem_region(ofbi->region);

		अगर (r) अणु
			dev_err(fbdev->dev, "failed to setup fb_info\n");
			वापस r;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		काष्ठा fb_info *fbi = fbdev->fbs[i];
		काष्ठा omapfb_info *ofbi = FB2OFB(fbi);

		अगर (ofbi->region->size == 0)
			जारी;

		omapfb_clear_fb(fbi);
	पूर्ण

	DBG("fb_infos initialized\n");

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		r = रेजिस्टर_framebuffer(fbdev->fbs[i]);
		अगर (r != 0) अणु
			dev_err(fbdev->dev,
				"registering framebuffer %d failed\n", i);
			वापस r;
		पूर्ण
	पूर्ण

	DBG("framebuffers registered\n");

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		काष्ठा fb_info *fbi = fbdev->fbs[i];
		काष्ठा omapfb_info *ofbi = FB2OFB(fbi);

		omapfb_get_mem_region(ofbi->region);
		r = omapfb_apply_changes(fbi, 1);
		omapfb_put_mem_region(ofbi->region);

		अगर (r) अणु
			dev_err(fbdev->dev, "failed to change mode\n");
			वापस r;
		पूर्ण
	पूर्ण

	/* Enable fb0 */
	अगर (fbdev->num_fbs > 0) अणु
		काष्ठा omapfb_info *ofbi = FB2OFB(fbdev->fbs[0]);

		अगर (ofbi->num_overlays > 0) अणु
			काष्ठा omap_overlay *ovl = ofbi->overlays[0];

			ovl->manager->apply(ovl->manager);

			r = omapfb_overlay_enable(ovl, 1);

			अगर (r) अणु
				dev_err(fbdev->dev,
						"failed to enable overlay\n");
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण

	DBG("create_framebuffers done\n");

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_mode_to_timings(स्थिर अक्षर *mode_str,
		काष्ठा omap_dss_device *display,
		काष्ठा omap_video_timings *timings, u8 *bpp)
अणु
	काष्ठा fb_info *fbi;
	काष्ठा fb_var_screeninfo *var;
	काष्ठा fb_ops *fbops;
	पूर्णांक r;

#अगर_घोषित CONFIG_OMAP2_DSS_VENC
	अगर (म_भेद(mode_str, "pal") == 0) अणु
		*timings = omap_dss_pal_timings;
		*bpp = 24;
		वापस 0;
	पूर्ण अन्यथा अगर (म_भेद(mode_str, "ntsc") == 0) अणु
		*timings = omap_dss_ntsc_timings;
		*bpp = 24;
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	/* this is quite a hack, but I wanted to use the modedb and क्रम
	 * that we need fb_info and var, so we create dummy ones */

	*bpp = 0;
	fbi = शून्य;
	var = शून्य;
	fbops = शून्य;

	fbi = kzalloc(माप(*fbi), GFP_KERNEL);
	अगर (fbi == शून्य) अणु
		r = -ENOMEM;
		जाओ err;
	पूर्ण

	var = kzalloc(माप(*var), GFP_KERNEL);
	अगर (var == शून्य) अणु
		r = -ENOMEM;
		जाओ err;
	पूर्ण

	fbops = kzalloc(माप(*fbops), GFP_KERNEL);
	अगर (fbops == शून्य) अणु
		r = -ENOMEM;
		जाओ err;
	पूर्ण

	fbi->fbops = fbops;

	r = fb_find_mode(var, fbi, mode_str, शून्य, 0, शून्य, 24);
	अगर (r == 0) अणु
		r = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (display->driver->get_timings) अणु
		display->driver->get_timings(display, timings);
	पूर्ण अन्यथा अणु
		timings->data_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
		timings->de_level = OMAPDSS_SIG_ACTIVE_HIGH;
		timings->sync_pclk_edge = OMAPDSS_DRIVE_SIG_FALLING_EDGE;
	पूर्ण

	timings->pixelघड़ी = PICOS2KHZ(var->pixघड़ी) * 1000;
	timings->hbp = var->left_margin;
	timings->hfp = var->right_margin;
	timings->vbp = var->upper_margin;
	timings->vfp = var->lower_margin;
	timings->hsw = var->hsync_len;
	timings->vsw = var->vsync_len;
	timings->x_res = var->xres;
	timings->y_res = var->yres;
	timings->hsync_level = var->sync & FB_SYNC_HOR_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_LOW;
	timings->vsync_level = var->sync & FB_SYNC_VERT_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_LOW;
	timings->पूर्णांकerlace = var->vmode & FB_VMODE_INTERLACED;

	चयन (var->bits_per_pixel) अणु
	हाल 16:
		*bpp = 16;
		अवरोध;
	हाल 24:
	हाल 32:
	शेष:
		*bpp = 24;
		अवरोध;
	पूर्ण

	r = 0;

err:
	kमुक्त(fbi);
	kमुक्त(var);
	kमुक्त(fbops);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_set_def_mode(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_dss_device *display, अक्षर *mode_str)
अणु
	पूर्णांक r;
	u8 bpp;
	काष्ठा omap_video_timings timings, temp_timings;
	काष्ठा omapfb_display_data *d;

	r = omapfb_mode_to_timings(mode_str, display, &timings, &bpp);
	अगर (r)
		वापस r;

	d = get_display_data(fbdev, display);
	d->bpp_override = bpp;

	अगर (display->driver->check_timings) अणु
		r = display->driver->check_timings(display, &timings);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		/* If check_timings is not present compare xres and yres */
		अगर (display->driver->get_timings) अणु
			display->driver->get_timings(display, &temp_timings);

			अगर (temp_timings.x_res != timings.x_res ||
				temp_timings.y_res != timings.y_res)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (display->driver->set_timings)
			display->driver->set_timings(display, &timings);

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_get_recommended_bpp(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omapfb_display_data *d;

	BUG_ON(dssdev->driver->get_recommended_bpp == शून्य);

	d = get_display_data(fbdev, dssdev);

	अगर (d->bpp_override != 0)
		वापस d->bpp_override;

	वापस dssdev->driver->get_recommended_bpp(dssdev);
पूर्ण

अटल पूर्णांक omapfb_parse_def_modes(काष्ठा omapfb2_device *fbdev)
अणु
	अक्षर *str, *options, *this_opt;
	पूर्णांक r = 0;

	str = kstrdup(def_mode, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;
	options = str;

	जबतक (!r && (this_opt = strsep(&options, ",")) != शून्य) अणु
		अक्षर *p, *display_str, *mode_str;
		काष्ठा omap_dss_device *display;
		पूर्णांक i;

		p = म_अक्षर(this_opt, ':');
		अगर (!p) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		*p = 0;
		display_str = this_opt;
		mode_str = p + 1;

		display = शून्य;
		क्रम (i = 0; i < fbdev->num_displays; ++i) अणु
			अगर (म_भेद(fbdev->displays[i].dssdev->name,
						display_str) == 0) अणु
				display = fbdev->displays[i].dssdev;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!display) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		r = omapfb_set_def_mode(fbdev, display, mode_str);
		अगर (r)
			अवरोध;
	पूर्ण

	kमुक्त(str);

	वापस r;
पूर्ण

अटल व्योम fb_videomode_to_omap_timings(काष्ठा fb_videomode *m,
		काष्ठा omap_dss_device *display,
		काष्ठा omap_video_timings *t)
अणु
	अगर (display->driver->get_timings) अणु
		display->driver->get_timings(display, t);
	पूर्ण अन्यथा अणु
		t->data_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
		t->de_level = OMAPDSS_SIG_ACTIVE_HIGH;
		t->sync_pclk_edge = OMAPDSS_DRIVE_SIG_FALLING_EDGE;
	पूर्ण

	t->x_res = m->xres;
	t->y_res = m->yres;
	t->pixelघड़ी = PICOS2KHZ(m->pixघड़ी) * 1000;
	t->hsw = m->hsync_len;
	t->hfp = m->right_margin;
	t->hbp = m->left_margin;
	t->vsw = m->vsync_len;
	t->vfp = m->lower_margin;
	t->vbp = m->upper_margin;
	t->hsync_level = m->sync & FB_SYNC_HOR_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_LOW;
	t->vsync_level = m->sync & FB_SYNC_VERT_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_LOW;
	t->पूर्णांकerlace = m->vmode & FB_VMODE_INTERLACED;
पूर्ण

अटल पूर्णांक omapfb_find_best_mode(काष्ठा omap_dss_device *display,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा fb_monspecs *specs;
	u8 *edid;
	पूर्णांक r, i, best_idx, len;

	अगर (!display->driver->पढ़ो_edid)
		वापस -ENODEV;

	len = 0x80 * 2;
	edid = kदो_स्मृति(len, GFP_KERNEL);
	अगर (edid == शून्य)
		वापस -ENOMEM;

	r = display->driver->पढ़ो_edid(display, edid, len);
	अगर (r < 0)
		जाओ err1;

	specs = kzalloc(माप(*specs), GFP_KERNEL);
	अगर (specs == शून्य) अणु
		r = -ENOMEM;
		जाओ err1;
	पूर्ण

	fb_edid_to_monspecs(edid, specs);

	best_idx = -1;

	क्रम (i = 0; i < specs->modedb_len; ++i) अणु
		काष्ठा fb_videomode *m;
		काष्ठा omap_video_timings t;

		m = &specs->modedb[i];

		अगर (m->pixघड़ी == 0)
			जारी;

		/* skip repeated pixel modes */
		अगर (m->xres == 2880 || m->xres == 1440)
			जारी;

		अगर (m->vmode & FB_VMODE_INTERLACED ||
				m->vmode & FB_VMODE_DOUBLE)
			जारी;

		fb_videomode_to_omap_timings(m, display, &t);

		r = display->driver->check_timings(display, &t);
		अगर (r == 0) अणु
			best_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (best_idx == -1) अणु
		r = -ENOENT;
		जाओ err2;
	पूर्ण

	fb_videomode_to_omap_timings(&specs->modedb[best_idx], display,
		timings);

	r = 0;

err2:
	fb_destroy_modedb(specs->modedb);
	kमुक्त(specs);
err1:
	kमुक्त(edid);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_init_display(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_dss_driver *dssdrv = dssdev->driver;
	काष्ठा omapfb_display_data *d;
	पूर्णांक r;

	r = dssdrv->enable(dssdev);
	अगर (r) अणु
		dev_warn(fbdev->dev, "Failed to enable display '%s'\n",
				dssdev->name);
		वापस r;
	पूर्ण

	d = get_display_data(fbdev, dssdev);

	d->fbdev = fbdev;

	अगर (dssdev->caps & OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE) अणु
		u16 w, h;

		अगर (स्वतः_update) अणु
			omapfb_start_स्वतः_update(fbdev, dssdev);
			d->update_mode = OMAPFB_AUTO_UPDATE;
		पूर्ण अन्यथा अणु
			d->update_mode = OMAPFB_MANUAL_UPDATE;
		पूर्ण

		अगर (dssdrv->enable_te) अणु
			r = dssdrv->enable_te(dssdev, 1);
			अगर (r) अणु
				dev_err(fbdev->dev, "Failed to set TE\n");
				वापस r;
			पूर्ण
		पूर्ण

		dssdrv->get_resolution(dssdev, &w, &h);
		r = dssdrv->update(dssdev, 0, 0, w, h);
		अगर (r) अणु
			dev_err(fbdev->dev,
					"Failed to update display\n");
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अणु
		d->update_mode = OMAPFB_AUTO_UPDATE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_init_connections(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_dss_device *def_dssdev)
अणु
	पूर्णांक i, r;
	काष्ठा omap_overlay_manager *mgr;

	r = def_dssdev->driver->connect(def_dssdev);
	अगर (r) अणु
		dev_err(fbdev->dev, "failed to connect default display\n");
		वापस r;
	पूर्ण

	क्रम (i = 0; i < fbdev->num_displays; ++i) अणु
		काष्ठा omap_dss_device *dssdev = fbdev->displays[i].dssdev;

		अगर (dssdev == def_dssdev)
			जारी;

		/*
		 * We करोn't care अगर the connect succeeds or not. We just want to
		 * connect as many displays as possible.
		 */
		dssdev->driver->connect(dssdev);
	पूर्ण

	mgr = omapdss_find_mgr_from_display(def_dssdev);

	अगर (!mgr) अणु
		dev_err(fbdev->dev, "no ovl manager for the default display\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < fbdev->num_overlays; i++) अणु
		काष्ठा omap_overlay *ovl = fbdev->overlays[i];

		अगर (ovl->manager)
			ovl->unset_manager(ovl);

		r = ovl->set_manager(ovl, mgr);
		अगर (r)
			dev_warn(fbdev->dev,
					"failed to connect overlay %s to manager %s\n",
					ovl->name, mgr->name);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा omap_dss_device *
omapfb_find_शेष_display(काष्ठा omapfb2_device *fbdev)
अणु
	स्थिर अक्षर *def_name;
	पूर्णांक i;

	/*
	 * Search with the display name from the user or the board file,
	 * comparing to display names and aliases
	 */

	def_name = omapdss_get_शेष_display_name();

	अगर (def_name) अणु
		क्रम (i = 0; i < fbdev->num_displays; ++i) अणु
			काष्ठा omap_dss_device *dssdev;

			dssdev = fbdev->displays[i].dssdev;

			अगर (dssdev->name && म_भेद(def_name, dssdev->name) == 0)
				वापस dssdev;

			अगर (म_भेद(def_name, dssdev->alias) == 0)
				वापस dssdev;
		पूर्ण

		/* def_name given but not found */
		वापस शून्य;
	पूर्ण

	/* then look क्रम DT alias display0 */
	क्रम (i = 0; i < fbdev->num_displays; ++i) अणु
		काष्ठा omap_dss_device *dssdev;
		पूर्णांक id;

		dssdev = fbdev->displays[i].dssdev;

		अगर (dssdev->dev->of_node == शून्य)
			जारी;

		id = of_alias_get_id(dssdev->dev->of_node, "display");
		अगर (id == 0)
			वापस dssdev;
	पूर्ण

	/* वापस the first display we have in the list */
	वापस fbdev->displays[0].dssdev;
पूर्ण

अटल पूर्णांक omapfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omapfb2_device *fbdev = शून्य;
	पूर्णांक r = 0;
	पूर्णांक i;
	काष्ठा omap_dss_device *def_display;
	काष्ठा omap_dss_device *dssdev;

	DBG("omapfb_probe\n");

	अगर (omapdss_is_initialized() == false)
		वापस -EPROBE_DEFER;

	अगर (pdev->num_resources != 0) अणु
		dev_err(&pdev->dev, "probed for an unknown device\n");
		r = -ENODEV;
		जाओ err0;
	पूर्ण

	fbdev = devm_kzalloc(&pdev->dev, माप(काष्ठा omapfb2_device),
			GFP_KERNEL);
	अगर (fbdev == शून्य) अणु
		r = -ENOMEM;
		जाओ err0;
	पूर्ण

	अगर (def_vrfb && !omap_vrfb_supported()) अणु
		def_vrfb = 0;
		dev_warn(&pdev->dev, "VRFB is not supported on this hardware, "
				"ignoring the module parameter vrfb=y\n");
	पूर्ण

	r = omapdss_compat_init();
	अगर (r)
		जाओ err0;

	mutex_init(&fbdev->mtx);

	fbdev->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, fbdev);

	fbdev->num_displays = 0;
	dssdev = शून्य;
	क्रम_each_dss_dev(dssdev) अणु
		काष्ठा omapfb_display_data *d;

		omap_dss_get_device(dssdev);

		अगर (!dssdev->driver) अणु
			dev_warn(&pdev->dev, "no driver for display: %s\n",
				dssdev->name);
			omap_dss_put_device(dssdev);
			जारी;
		पूर्ण

		d = &fbdev->displays[fbdev->num_displays++];
		d->dssdev = dssdev;
		अगर (dssdev->caps & OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE)
			d->update_mode = OMAPFB_MANUAL_UPDATE;
		अन्यथा
			d->update_mode = OMAPFB_AUTO_UPDATE;
	पूर्ण

	अगर (fbdev->num_displays == 0) अणु
		dev_err(&pdev->dev, "no displays\n");
		r = -EPROBE_DEFER;
		जाओ cleanup;
	पूर्ण

	fbdev->num_overlays = omap_dss_get_num_overlays();
	क्रम (i = 0; i < fbdev->num_overlays; i++)
		fbdev->overlays[i] = omap_dss_get_overlay(i);

	fbdev->num_managers = omap_dss_get_num_overlay_managers();
	क्रम (i = 0; i < fbdev->num_managers; i++)
		fbdev->managers[i] = omap_dss_get_overlay_manager(i);

	def_display = omapfb_find_शेष_display(fbdev);
	अगर (def_display == शून्य) अणु
		dev_err(fbdev->dev, "failed to find default display\n");
		r = -EPROBE_DEFER;
		जाओ cleanup;
	पूर्ण

	r = omapfb_init_connections(fbdev, def_display);
	अगर (r) अणु
		dev_err(fbdev->dev, "failed to init overlay connections\n");
		जाओ cleanup;
	पूर्ण

	अगर (def_mode && म_माप(def_mode) > 0) अणु
		अगर (omapfb_parse_def_modes(fbdev))
			dev_warn(&pdev->dev, "cannot parse default modes\n");
	पूर्ण अन्यथा अगर (def_display && def_display->driver->set_timings &&
			def_display->driver->check_timings) अणु
		काष्ठा omap_video_timings t;

		r = omapfb_find_best_mode(def_display, &t);

		अगर (r == 0)
			def_display->driver->set_timings(def_display, &t);
	पूर्ण

	r = omapfb_create_framebuffers(fbdev);
	अगर (r)
		जाओ cleanup;

	क्रम (i = 0; i < fbdev->num_managers; i++) अणु
		काष्ठा omap_overlay_manager *mgr;
		mgr = fbdev->managers[i];
		r = mgr->apply(mgr);
		अगर (r)
			dev_warn(fbdev->dev, "failed to apply dispc config\n");
	पूर्ण

	DBG("mgr->apply'ed\n");

	अगर (def_display) अणु
		r = omapfb_init_display(fbdev, def_display);
		अगर (r) अणु
			dev_err(fbdev->dev,
					"failed to initialize default "
					"display\n");
			जाओ cleanup;
		पूर्ण
	पूर्ण

	DBG("create sysfs for fbs\n");
	r = omapfb_create_sysfs(fbdev);
	अगर (r) अणु
		dev_err(fbdev->dev, "failed to create sysfs entries\n");
		जाओ cleanup;
	पूर्ण

	अगर (def_display) अणु
		u16 w, h;

		def_display->driver->get_resolution(def_display, &w, &h);

		dev_info(fbdev->dev, "using display '%s' mode %dx%d\n",
			def_display->name, w, h);
	पूर्ण

	वापस 0;

cleanup:
	omapfb_मुक्त_resources(fbdev);
	omapdss_compat_uninit();
err0:
	dev_err(&pdev->dev, "failed to setup omapfb\n");
	वापस r;
पूर्ण

अटल पूर्णांक omapfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omapfb2_device *fbdev = platक्रमm_get_drvdata(pdev);

	/* FIXME: रुको till completion of pending events */

	omapfb_हटाओ_sysfs(fbdev);

	omapfb_मुक्त_resources(fbdev);

	omapdss_compat_uninit();

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omapfb_driver = अणु
	.probe		= omapfb_probe,
	.हटाओ         = omapfb_हटाओ,
	.driver         = अणु
		.name   = "omapfb",
	पूर्ण,
पूर्ण;

module_param_named(mode, def_mode, अक्षरp, 0);
module_param_named(vram, def_vram, अक्षरp, 0);
module_param_named(rotate, def_rotate, पूर्णांक, 0);
module_param_named(vrfb, def_vrfb, bool, 0);
module_param_named(mirror, def_mirror, bool, 0);

module_platक्रमm_driver(omapfb_driver);

MODULE_ALIAS("platform:omapfb");
MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@nokia.com>");
MODULE_DESCRIPTION("OMAP2/3 Framebuffer");
MODULE_LICENSE("GPL v2");
