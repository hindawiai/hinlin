<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Framebuffer driver क्रम TI OMAP boards
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 *
 * Acknowledgements:
 *   Alex McMains <aam@ridgerun.com>       - Original driver
 *   Juha Yrjola <juha.yrjola@nokia.com>   - Original driver and improvements
 *   Dirk Behme <dirk.behme@de.bosch.com>  - changes क्रम 2.6 kernel API
 *   Texas Instruments                     - H3 support
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>

#समावेश <linux/omap-dma.h>

#समावेश <mach/hardware.h>

#समावेश "omapfb.h"
#समावेश "lcdc.h"

#घोषणा MODULE_NAME	"omapfb"

अटल अचिन्हित पूर्णांक	def_accel;
अटल अचिन्हित दीर्घ	def_vram[OMAPFB_PLANE_NUM];
अटल अचिन्हित पूर्णांक	def_vram_cnt;
अटल अचिन्हित दीर्घ	def_vxres;
अटल अचिन्हित दीर्घ	def_vyres;
अटल अचिन्हित पूर्णांक	def_rotate;
अटल अचिन्हित पूर्णांक	def_mirror;

अटल bool	manual_update = IS_BUILTIN(CONFIG_FB_OMAP_MANUAL_UPDATE);

अटल काष्ठा platक्रमm_device	*fbdev_pdev;
अटल काष्ठा lcd_panel		*fbdev_panel;
अटल काष्ठा omapfb_device	*omapfb_dev;

काष्ठा caps_table_काष्ठा अणु
	अचिन्हित दीर्घ flag;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा caps_table_काष्ठा ctrl_caps[] = अणु
	अणु OMAPFB_CAPS_MANUAL_UPDATE,  "manual update" पूर्ण,
	अणु OMAPFB_CAPS_TEARSYNC,       "tearing synchronization" पूर्ण,
	अणु OMAPFB_CAPS_PLANE_RELOCATE_MEM, "relocate plane memory" पूर्ण,
	अणु OMAPFB_CAPS_PLANE_SCALE,    "scale plane" पूर्ण,
	अणु OMAPFB_CAPS_WINDOW_PIXEL_DOUBLE, "pixel double window" पूर्ण,
	अणु OMAPFB_CAPS_WINDOW_SCALE,   "scale window" पूर्ण,
	अणु OMAPFB_CAPS_WINDOW_OVERLAY, "overlay window" पूर्ण,
	अणु OMAPFB_CAPS_WINDOW_ROTATE,  "rotate window" पूर्ण,
	अणु OMAPFB_CAPS_SET_BACKLIGHT,  "backlight setting" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा caps_table_काष्ठा color_caps[] = अणु
	अणु 1 << OMAPFB_COLOR_RGB565,	"RGB565", पूर्ण,
	अणु 1 << OMAPFB_COLOR_YUV422,	"YUV422", पूर्ण,
	अणु 1 << OMAPFB_COLOR_YUV420,	"YUV420", पूर्ण,
	अणु 1 << OMAPFB_COLOR_CLUT_8BPP,	"CLUT8", पूर्ण,
	अणु 1 << OMAPFB_COLOR_CLUT_4BPP,	"CLUT4", पूर्ण,
	अणु 1 << OMAPFB_COLOR_CLUT_2BPP,	"CLUT2", पूर्ण,
	अणु 1 << OMAPFB_COLOR_CLUT_1BPP,	"CLUT1", पूर्ण,
	अणु 1 << OMAPFB_COLOR_RGB444,	"RGB444", पूर्ण,
	अणु 1 << OMAPFB_COLOR_YUY422,	"YUY422", पूर्ण,
पूर्ण;

अटल व्योम omapdss_release(काष्ठा device *dev)
अणु
पूर्ण

/* dummy device क्रम घड़ीs */
अटल काष्ठा platक्रमm_device omapdss_device = अणु
	.name		= "omapdss_dss",
	.id		= -1,
	.dev            = अणु
		.release = omapdss_release,
	पूर्ण,
पूर्ण;

/*
 * ---------------------------------------------------------------------------
 * LCD panel
 * ---------------------------------------------------------------------------
 */
बाह्य काष्ठा lcd_ctrl hwa742_ctrl;

अटल स्थिर काष्ठा lcd_ctrl *ctrls[] = अणु
	&omap1_पूर्णांक_ctrl,

#अगर_घोषित CONFIG_FB_OMAP_LCDC_HWA742
	&hwa742_ctrl,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_FB_OMAP_LCDC_EXTERNAL
बाह्य काष्ठा lcd_ctrl_extअगर omap1_ext_अगर;
#पूर्ण_अगर

अटल व्योम omapfb_rqueue_lock(काष्ठा omapfb_device *fbdev)
अणु
	mutex_lock(&fbdev->rqueue_mutex);
पूर्ण

अटल व्योम omapfb_rqueue_unlock(काष्ठा omapfb_device *fbdev)
अणु
	mutex_unlock(&fbdev->rqueue_mutex);
पूर्ण

/*
 * ---------------------------------------------------------------------------
 * LCD controller and LCD DMA
 * ---------------------------------------------------------------------------
 */
/*
 * Allocate resources needed क्रम LCD controller and LCD DMA operations. Video
 * memory is allocated from प्रणाली memory according to the भव display
 * size, except अगर a bigger memory size is specअगरied explicitly as a kernel
 * parameter.
 */
अटल पूर्णांक ctrl_init(काष्ठा omapfb_device *fbdev)
अणु
	पूर्णांक r;
	पूर्णांक i;

	/* kernel/module vram parameters override boot tags/board config */
	अगर (def_vram_cnt) अणु
		क्रम (i = 0; i < def_vram_cnt; i++)
			fbdev->mem_desc.region[i].size =
				PAGE_ALIGN(def_vram[i]);
		fbdev->mem_desc.region_cnt = i;
	पूर्ण

	अगर (!fbdev->mem_desc.region_cnt) अणु
		काष्ठा lcd_panel *panel = fbdev->panel;
		पूर्णांक def_size;
		पूर्णांक bpp = panel->bpp;

		/* 12 bpp is packed in 16 bits */
		अगर (bpp == 12)
			bpp = 16;
		def_size = def_vxres * def_vyres * bpp / 8;
		fbdev->mem_desc.region_cnt = 1;
		fbdev->mem_desc.region[0].size = PAGE_ALIGN(def_size);
	पूर्ण
	r = fbdev->ctrl->init(fbdev, 0, &fbdev->mem_desc);
	अगर (r < 0) अणु
		dev_err(fbdev->dev, "controller initialization failed (%d)\n",
			r);
		वापस r;
	पूर्ण

#अगर_घोषित DEBUG
	क्रम (i = 0; i < fbdev->mem_desc.region_cnt; i++) अणु
		dev_dbg(fbdev->dev, "region%d phys %08x virt %p size=%lu\n",
			 i,
			 fbdev->mem_desc.region[i].paddr,
			 fbdev->mem_desc.region[i].vaddr,
			 fbdev->mem_desc.region[i].size);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम ctrl_cleanup(काष्ठा omapfb_device *fbdev)
अणु
	fbdev->ctrl->cleanup();
पूर्ण

/* Must be called with fbdev->rqueue_mutex held. */
अटल पूर्णांक ctrl_change_mode(काष्ठा fb_info *fbi)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ offset;
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	काष्ठा fb_var_screeninfo *var = &fbi->var;

	offset = var->yoffset * fbi->fix.line_length +
		 var->xoffset * var->bits_per_pixel / 8;

	अगर (fbdev->ctrl->sync)
		fbdev->ctrl->sync();
	r = fbdev->ctrl->setup_plane(plane->idx, plane->info.channel_out,
				 offset, var->xres_भव,
				 plane->info.pos_x, plane->info.pos_y,
				 var->xres, var->yres, plane->color_mode);
	अगर (r < 0)
		वापस r;

	अगर (fbdev->ctrl->set_rotate != शून्य) अणु
		r = fbdev->ctrl->set_rotate(var->rotate);
		अगर (r < 0)
			वापस r;
	पूर्ण

	अगर (fbdev->ctrl->set_scale != शून्य)
		r = fbdev->ctrl->set_scale(plane->idx,
				   var->xres, var->yres,
				   plane->info.out_width,
				   plane->info.out_height);

	वापस r;
पूर्ण

/*
 * ---------------------------------------------------------------------------
 * fbdev framework callbacks and the ioctl पूर्णांकerface
 * ---------------------------------------------------------------------------
 */
/* Called each समय the omapfb device is खोलोed */
अटल पूर्णांक omapfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	वापस 0;
पूर्ण

अटल व्योम omapfb_sync(काष्ठा fb_info *info);

/* Called when the omapfb device is बंदd. We make sure that any pending
 * gfx DMA operations are ended, beक्रमe we वापस. */
अटल पूर्णांक omapfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	omapfb_sync(info);
	वापस 0;
पूर्ण

/* Store a single color palette entry पूर्णांकo a pseuकरो palette or the hardware
 * palette अगर one is available. For now we support only 16bpp and thus store
 * the entry only to the pseuकरो palette.
 */
अटल पूर्णांक _setcolreg(काष्ठा fb_info *info, u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green,
			u_पूर्णांक blue, u_पूर्णांक transp, पूर्णांक update_hw_pal)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = info->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	काष्ठा fb_var_screeninfo *var = &info->var;
	पूर्णांक r = 0;

	चयन (plane->color_mode) अणु
	हाल OMAPFB_COLOR_YUV422:
	हाल OMAPFB_COLOR_YUV420:
	हाल OMAPFB_COLOR_YUY422:
		r = -EINVAL;
		अवरोध;
	हाल OMAPFB_COLOR_CLUT_8BPP:
	हाल OMAPFB_COLOR_CLUT_4BPP:
	हाल OMAPFB_COLOR_CLUT_2BPP:
	हाल OMAPFB_COLOR_CLUT_1BPP:
		अगर (fbdev->ctrl->setcolreg)
			r = fbdev->ctrl->setcolreg(regno, red, green, blue,
							transp, update_hw_pal);
		fallthrough;
	हाल OMAPFB_COLOR_RGB565:
	हाल OMAPFB_COLOR_RGB444:
		अगर (r != 0)
			अवरोध;

		अगर (regno < 16) अणु
			u16 pal;
			pal = ((red >> (16 - var->red.length)) <<
					var->red.offset) |
			      ((green >> (16 - var->green.length)) <<
					var->green.offset) |
			      (blue >> (16 - var->blue.length));
			((u32 *)(info->pseuकरो_palette))[regno] = pal;
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
	वापस _setcolreg(info, regno, red, green, blue, transp, 1);
पूर्ण

अटल पूर्णांक omapfb_setcmap(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info)
अणु
	पूर्णांक count, index, r;
	u16 *red, *green, *blue, *transp;
	u16 trans = 0xffff;

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

अटल पूर्णांक omapfb_update_full_screen(काष्ठा fb_info *fbi);

अटल पूर्णांक omapfb_blank(पूर्णांक blank, काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	पूर्णांक करो_update = 0;
	पूर्णांक r = 0;

	omapfb_rqueue_lock(fbdev);
	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
		अगर (fbdev->state == OMAPFB_SUSPENDED) अणु
			अगर (fbdev->ctrl->resume)
				fbdev->ctrl->resume();
			अगर (fbdev->panel->enable)
				fbdev->panel->enable(fbdev->panel);
			fbdev->state = OMAPFB_ACTIVE;
			अगर (fbdev->ctrl->get_update_mode() ==
					OMAPFB_MANUAL_UPDATE)
				करो_update = 1;
		पूर्ण
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		अगर (fbdev->state == OMAPFB_ACTIVE) अणु
			अगर (fbdev->panel->disable)
				fbdev->panel->disable(fbdev->panel);
			अगर (fbdev->ctrl->suspend)
				fbdev->ctrl->suspend();
			fbdev->state = OMAPFB_SUSPENDED;
		पूर्ण
		अवरोध;
	शेष:
		r = -EINVAL;
	पूर्ण
	omapfb_rqueue_unlock(fbdev);

	अगर (r == 0 && करो_update)
		r = omapfb_update_full_screen(fbi);

	वापस r;
पूर्ण

अटल व्योम omapfb_sync(काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;

	omapfb_rqueue_lock(fbdev);
	अगर (fbdev->ctrl->sync)
		fbdev->ctrl->sync();
	omapfb_rqueue_unlock(fbdev);
पूर्ण

/*
 * Set fb_info.fix fields and also updates fbdev.
 * When calling this fb_info.var must be set up alपढ़ोy.
 */
अटल व्योम set_fb_fix(काष्ठा fb_info *fbi, पूर्णांक from_init)
अणु
	काष्ठा fb_fix_screeninfo *fix = &fbi->fix;
	काष्ठा fb_var_screeninfo *var = &fbi->var;
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_mem_region *rg;
	पूर्णांक bpp;

	rg = &plane->fbdev->mem_desc.region[plane->idx];
	fbi->screen_base	= rg->vaddr;

	अगर (!from_init) अणु
		mutex_lock(&fbi->mm_lock);
		fix->smem_start		= rg->paddr;
		fix->smem_len		= rg->size;
		mutex_unlock(&fbi->mm_lock);
	पूर्ण अन्यथा अणु
		fix->smem_start		= rg->paddr;
		fix->smem_len		= rg->size;
	पूर्ण

	fix->type = FB_TYPE_PACKED_PIXELS;
	bpp = var->bits_per_pixel;
	अगर (var->nonstd)
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा चयन (var->bits_per_pixel) अणु
	हाल 16:
	हाल 12:
		fix->visual = FB_VISUAL_TRUECOLOR;
		/* 12bpp is stored in 16 bits */
		bpp = 16;
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	पूर्ण
	fix->accel		= FB_ACCEL_OMAP1610;
	fix->line_length	= var->xres_भव * bpp / 8;
पूर्ण

अटल पूर्णांक set_color_mode(काष्ठा omapfb_plane_काष्ठा *plane,
			  काष्ठा fb_var_screeninfo *var)
अणु
	चयन (var->nonstd) अणु
	हाल 0:
		अवरोध;
	हाल OMAPFB_COLOR_YUV422:
		var->bits_per_pixel = 16;
		plane->color_mode = var->nonstd;
		वापस 0;
	हाल OMAPFB_COLOR_YUV420:
		var->bits_per_pixel = 12;
		plane->color_mode = var->nonstd;
		वापस 0;
	हाल OMAPFB_COLOR_YUY422:
		var->bits_per_pixel = 16;
		plane->color_mode = var->nonstd;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (var->bits_per_pixel) अणु
	हाल 1:
		plane->color_mode = OMAPFB_COLOR_CLUT_1BPP;
		वापस 0;
	हाल 2:
		plane->color_mode = OMAPFB_COLOR_CLUT_2BPP;
		वापस 0;
	हाल 4:
		plane->color_mode = OMAPFB_COLOR_CLUT_4BPP;
		वापस 0;
	हाल 8:
		plane->color_mode = OMAPFB_COLOR_CLUT_8BPP;
		वापस 0;
	हाल 12:
		var->bits_per_pixel = 16;
		fallthrough;
	हाल 16:
		अगर (plane->fbdev->panel->bpp == 12)
			plane->color_mode = OMAPFB_COLOR_RGB444;
		अन्यथा
			plane->color_mode = OMAPFB_COLOR_RGB565;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Check the values in var against our capabilities and in हाल of out of
 * bound values try to adjust them.
 */
अटल पूर्णांक set_fb_var(काष्ठा fb_info *fbi,
		      काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक		bpp;
	अचिन्हित दीर्घ	max_frame_size;
	अचिन्हित दीर्घ	line_size;
	पूर्णांक		xres_min, xres_max;
	पूर्णांक		yres_min, yres_max;
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	काष्ठा lcd_panel *panel = fbdev->panel;

	अगर (set_color_mode(plane, var) < 0)
		वापस -EINVAL;

	bpp = var->bits_per_pixel;
	अगर (plane->color_mode == OMAPFB_COLOR_RGB444)
		bpp = 16;

	चयन (var->rotate) अणु
	हाल 0:
	हाल 180:
		xres_min = OMAPFB_PLANE_XRES_MIN;
		xres_max = panel->x_res;
		yres_min = OMAPFB_PLANE_YRES_MIN;
		yres_max = panel->y_res;
		अगर (cpu_is_omap15xx()) अणु
			var->xres = panel->x_res;
			var->yres = panel->y_res;
		पूर्ण
		अवरोध;
	हाल 90:
	हाल 270:
		xres_min = OMAPFB_PLANE_YRES_MIN;
		xres_max = panel->y_res;
		yres_min = OMAPFB_PLANE_XRES_MIN;
		yres_max = panel->x_res;
		अगर (cpu_is_omap15xx()) अणु
			var->xres = panel->y_res;
			var->yres = panel->x_res;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (var->xres < xres_min)
		var->xres = xres_min;
	अगर (var->yres < yres_min)
		var->yres = yres_min;
	अगर (var->xres > xres_max)
		var->xres = xres_max;
	अगर (var->yres > yres_max)
		var->yres = yres_max;

	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;
	max_frame_size = fbdev->mem_desc.region[plane->idx].size;
	line_size = var->xres_भव * bpp / 8;
	अगर (line_size * var->yres_भव > max_frame_size) अणु
		/* Try to keep yres_भव first */
		line_size = max_frame_size / var->yres_भव;
		var->xres_भव = line_size * 8 / bpp;
		अगर (var->xres_भव < var->xres) अणु
			/* Still करोesn't fit. Shrink yres_भव too */
			var->xres_भव = var->xres;
			line_size = var->xres * bpp / 8;
			var->yres_भव = max_frame_size / line_size;
		पूर्ण
		/* Recheck this, as the भव size changed. */
		अगर (var->xres_भव < var->xres)
			var->xres = var->xres_भव;
		अगर (var->yres_भव < var->yres)
			var->yres = var->yres_भव;
		अगर (var->xres < xres_min || var->yres < yres_min)
			वापस -EINVAL;
	पूर्ण
	अगर (var->xres + var->xoffset > var->xres_भव)
		var->xoffset = var->xres_भव - var->xres;
	अगर (var->yres + var->yoffset > var->yres_भव)
		var->yoffset = var->yres_भव - var->yres;

	अगर (plane->color_mode == OMAPFB_COLOR_RGB444) अणु
		var->red.offset	  = 8; var->red.length	 = 4;
						var->red.msb_right   = 0;
		var->green.offset = 4; var->green.length = 4;
						var->green.msb_right = 0;
		var->blue.offset  = 0; var->blue.length  = 4;
						var->blue.msb_right  = 0;
	पूर्ण अन्यथा अणु
		var->red.offset	 = 11; var->red.length	 = 5;
						var->red.msb_right   = 0;
		var->green.offset = 5;  var->green.length = 6;
						var->green.msb_right = 0;
		var->blue.offset = 0;  var->blue.length  = 5;
						var->blue.msb_right  = 0;
	पूर्ण

	var->height		= -1;
	var->width		= -1;
	var->grayscale		= 0;

	/* pixघड़ी in ps, the rest in pixघड़ी */
	var->pixघड़ी		= 10000000 / (panel->pixel_घड़ी / 100);
	var->left_margin	= panel->hfp;
	var->right_margin	= panel->hbp;
	var->upper_margin	= panel->vfp;
	var->lower_margin	= panel->vbp;
	var->hsync_len		= panel->hsw;
	var->vsync_len		= panel->vsw;

	/* TODO: get these from panel->config */
	var->vmode		= FB_VMODE_NONINTERLACED;
	var->sync		= 0;

	वापस 0;
पूर्ण


/*
 * Set new x,y offsets in the भव display क्रम the visible area and चयन
 * to the new mode.
 */
अटल पूर्णांक omapfb_pan_display(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	पूर्णांक r = 0;

	omapfb_rqueue_lock(fbdev);
	अगर (var->xoffset != fbi->var.xoffset ||
	    var->yoffset != fbi->var.yoffset) अणु
		काष्ठा fb_var_screeninfo *new_var = &fbdev->new_var;

		स_नकल(new_var, &fbi->var, माप(*new_var));
		new_var->xoffset = var->xoffset;
		new_var->yoffset = var->yoffset;
		अगर (set_fb_var(fbi, new_var))
			r = -EINVAL;
		अन्यथा अणु
			स_नकल(&fbi->var, new_var, माप(*new_var));
			ctrl_change_mode(fbi);
		पूर्ण
	पूर्ण
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

/* Set mirror to vertical axis and चयन to the new mode. */
अटल पूर्णांक omapfb_mirror(काष्ठा fb_info *fbi, पूर्णांक mirror)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	पूर्णांक r = 0;

	omapfb_rqueue_lock(fbdev);
	mirror = mirror ? 1 : 0;
	अगर (cpu_is_omap15xx())
		r = -EINVAL;
	अन्यथा अगर (mirror != plane->info.mirror) अणु
		plane->info.mirror = mirror;
		r = ctrl_change_mode(fbi);
	पूर्ण
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

/*
 * Check values in var, try to adjust them in हाल of out of bound values अगर
 * possible, or वापस error.
 */
अटल पूर्णांक omapfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	पूर्णांक r;

	omapfb_rqueue_lock(fbdev);
	अगर (fbdev->ctrl->sync != शून्य)
		fbdev->ctrl->sync();
	r = set_fb_var(fbi, var);
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

/*
 * Switch to a new mode. The parameters क्रम it has been check alपढ़ोy by
 * omapfb_check_var.
 */
अटल पूर्णांक omapfb_set_par(काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	पूर्णांक r = 0;

	omapfb_rqueue_lock(fbdev);
	set_fb_fix(fbi, 0);
	r = ctrl_change_mode(fbi);
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

पूर्णांक omapfb_update_winकरोw_async(काष्ठा fb_info *fbi,
				काष्ठा omapfb_update_winकरोw *win,
				व्योम (*callback)(व्योम *),
				व्योम *callback_data)
अणु
	पूर्णांक xres, yres;
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	काष्ठा fb_var_screeninfo *var = &fbi->var;

	चयन (var->rotate) अणु
	हाल 0:
	हाल 180:
		xres = fbdev->panel->x_res;
		yres = fbdev->panel->y_res;
		अवरोध;
	हाल 90:
	हाल 270:
		xres = fbdev->panel->y_res;
		yres = fbdev->panel->x_res;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (win->x >= xres || win->y >= yres ||
	    win->out_x > xres || win->out_y > yres)
		वापस -EINVAL;

	अगर (!fbdev->ctrl->update_winकरोw ||
	    fbdev->ctrl->get_update_mode() != OMAPFB_MANUAL_UPDATE)
		वापस -ENODEV;

	अगर (win->x + win->width > xres)
		win->width = xres - win->x;
	अगर (win->y + win->height > yres)
		win->height = yres - win->y;
	अगर (win->out_x + win->out_width > xres)
		win->out_width = xres - win->out_x;
	अगर (win->out_y + win->out_height > yres)
		win->out_height = yres - win->out_y;
	अगर (!win->width || !win->height || !win->out_width || !win->out_height)
		वापस 0;

	वापस fbdev->ctrl->update_winकरोw(fbi, win, callback, callback_data);
पूर्ण
EXPORT_SYMBOL(omapfb_update_winकरोw_async);

अटल पूर्णांक omapfb_update_win(काष्ठा fb_info *fbi,
				काष्ठा omapfb_update_winकरोw *win)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	पूर्णांक ret;

	omapfb_rqueue_lock(plane->fbdev);
	ret = omapfb_update_winकरोw_async(fbi, win, शून्य, शून्य);
	omapfb_rqueue_unlock(plane->fbdev);

	वापस ret;
पूर्ण

अटल पूर्णांक omapfb_update_full_screen(काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	काष्ठा omapfb_update_winकरोw win;
	पूर्णांक r;

	अगर (!fbdev->ctrl->update_winकरोw ||
	    fbdev->ctrl->get_update_mode() != OMAPFB_MANUAL_UPDATE)
		वापस -ENODEV;

	win.x = 0;
	win.y = 0;
	win.width = fbi->var.xres;
	win.height = fbi->var.yres;
	win.out_x = 0;
	win.out_y = 0;
	win.out_width = fbi->var.xres;
	win.out_height = fbi->var.yres;
	win.क्रमmat = 0;

	omapfb_rqueue_lock(fbdev);
	r = fbdev->ctrl->update_winकरोw(fbi, &win, शून्य, शून्य);
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_setup_plane(काष्ठा fb_info *fbi, काष्ठा omapfb_plane_info *pi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	काष्ठा lcd_panel *panel = fbdev->panel;
	काष्ठा omapfb_plane_info old_info;
	पूर्णांक r = 0;

	अगर (pi->pos_x + pi->out_width > panel->x_res ||
	    pi->pos_y + pi->out_height > panel->y_res)
		वापस -EINVAL;

	omapfb_rqueue_lock(fbdev);
	अगर (pi->enabled && !fbdev->mem_desc.region[plane->idx].size) अणु
		/*
		 * This plane's memory was freed, can't enable it
		 * until it's पुनः_स्मृतिated.
		 */
		r = -EINVAL;
		जाओ out;
	पूर्ण
	old_info = plane->info;
	plane->info = *pi;
	अगर (pi->enabled) अणु
		r = ctrl_change_mode(fbi);
		अगर (r < 0) अणु
			plane->info = old_info;
			जाओ out;
		पूर्ण
	पूर्ण
	r = fbdev->ctrl->enable_plane(plane->idx, pi->enabled);
	अगर (r < 0) अणु
		plane->info = old_info;
		जाओ out;
	पूर्ण
out:
	omapfb_rqueue_unlock(fbdev);
	वापस r;
पूर्ण

अटल पूर्णांक omapfb_query_plane(काष्ठा fb_info *fbi, काष्ठा omapfb_plane_info *pi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;

	*pi = plane->info;
	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_setup_mem(काष्ठा fb_info *fbi, काष्ठा omapfb_mem_info *mi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	काष्ठा omapfb_mem_region *rg = &fbdev->mem_desc.region[plane->idx];
	माप_प्रकार size;
	पूर्णांक r = 0;

	अगर (fbdev->ctrl->setup_mem == शून्य)
		वापस -ENODEV;
	अगर (mi->type != OMAPFB_MEMTYPE_SDRAM)
		वापस -EINVAL;

	size = PAGE_ALIGN(mi->size);
	omapfb_rqueue_lock(fbdev);
	अगर (plane->info.enabled) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (rg->size != size || rg->type != mi->type) अणु
		काष्ठा fb_var_screeninfo *new_var = &fbdev->new_var;
		अचिन्हित दीर्घ old_size = rg->size;
		u8	      old_type = rg->type;
		अचिन्हित दीर्घ paddr;

		rg->size = size;
		rg->type = mi->type;
		/*
		 * size == 0 is a special हाल, क्रम which we
		 * करोn't check / adjust the screen parameters.
		 * This isn't a problem since the plane can't
		 * be reenabled unless its size is > 0.
		 */
		अगर (old_size != size && size) अणु
			अगर (size) अणु
				स_नकल(new_var, &fbi->var, माप(*new_var));
				r = set_fb_var(fbi, new_var);
				अगर (r < 0)
					जाओ out;
			पूर्ण
		पूर्ण

		अगर (fbdev->ctrl->sync)
			fbdev->ctrl->sync();
		r = fbdev->ctrl->setup_mem(plane->idx, size, mi->type, &paddr);
		अगर (r < 0) अणु
			/* Revert changes. */
			rg->size = old_size;
			rg->type = old_type;
			जाओ out;
		पूर्ण
		rg->paddr = paddr;

		अगर (old_size != size) अणु
			अगर (size) अणु
				स_नकल(&fbi->var, new_var, माप(fbi->var));
				set_fb_fix(fbi, 0);
			पूर्ण अन्यथा अणु
				/*
				 * Set these explicitly to indicate that the
				 * plane memory is dealloce'd, the other
				 * screen parameters in var / fix are invalid.
				 */
				mutex_lock(&fbi->mm_lock);
				fbi->fix.smem_start = 0;
				fbi->fix.smem_len = 0;
				mutex_unlock(&fbi->mm_lock);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_query_mem(काष्ठा fb_info *fbi, काष्ठा omapfb_mem_info *mi)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	काष्ठा omapfb_mem_region *rg;

	rg = &fbdev->mem_desc.region[plane->idx];
	स_रखो(mi, 0, माप(*mi));
	mi->size = rg->size;
	mi->type = rg->type;

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_set_color_key(काष्ठा omapfb_device *fbdev,
				काष्ठा omapfb_color_key *ck)
अणु
	पूर्णांक r;

	अगर (!fbdev->ctrl->set_color_key)
		वापस -ENODEV;

	omapfb_rqueue_lock(fbdev);
	r = fbdev->ctrl->set_color_key(ck);
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_get_color_key(काष्ठा omapfb_device *fbdev,
				काष्ठा omapfb_color_key *ck)
अणु
	पूर्णांक r;

	अगर (!fbdev->ctrl->get_color_key)
		वापस -ENODEV;

	omapfb_rqueue_lock(fbdev);
	r = fbdev->ctrl->get_color_key(ck);
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

अटल काष्ठा blocking_notअगरier_head omapfb_client_list[OMAPFB_PLANE_NUM];
अटल पूर्णांक notअगरier_inited;

अटल व्योम omapfb_init_notअगरier(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OMAPFB_PLANE_NUM; i++)
		BLOCKING_INIT_NOTIFIER_HEAD(&omapfb_client_list[i]);
पूर्ण

पूर्णांक omapfb_रेजिस्टर_client(काष्ठा omapfb_notअगरier_block *omapfb_nb,
				omapfb_notअगरier_callback_t callback,
				व्योम *callback_data)
अणु
	पूर्णांक r;

	अगर ((अचिन्हित)omapfb_nb->plane_idx >= OMAPFB_PLANE_NUM)
		वापस -EINVAL;

	अगर (!notअगरier_inited) अणु
		omapfb_init_notअगरier();
		notअगरier_inited = 1;
	पूर्ण

	omapfb_nb->nb.notअगरier_call = (पूर्णांक (*)(काष्ठा notअगरier_block *,
					अचिन्हित दीर्घ, व्योम *))callback;
	omapfb_nb->data = callback_data;
	r = blocking_notअगरier_chain_रेजिस्टर(
				&omapfb_client_list[omapfb_nb->plane_idx],
				&omapfb_nb->nb);
	अगर (r)
		वापस r;
	अगर (omapfb_dev != शून्य &&
	    omapfb_dev->ctrl && omapfb_dev->ctrl->bind_client) अणु
		omapfb_dev->ctrl->bind_client(omapfb_nb);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(omapfb_रेजिस्टर_client);

पूर्णांक omapfb_unरेजिस्टर_client(काष्ठा omapfb_notअगरier_block *omapfb_nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(
		&omapfb_client_list[omapfb_nb->plane_idx], &omapfb_nb->nb);
पूर्ण
EXPORT_SYMBOL(omapfb_unरेजिस्टर_client);

व्योम omapfb_notअगरy_clients(काष्ठा omapfb_device *fbdev, अचिन्हित दीर्घ event)
अणु
	पूर्णांक i;

	अगर (!notअगरier_inited)
		/* no client रेजिस्टरed yet */
		वापस;

	क्रम (i = 0; i < OMAPFB_PLANE_NUM; i++)
		blocking_notअगरier_call_chain(&omapfb_client_list[i], event,
				    fbdev->fb_info[i]);
पूर्ण
EXPORT_SYMBOL(omapfb_notअगरy_clients);

अटल पूर्णांक omapfb_set_update_mode(काष्ठा omapfb_device *fbdev,
				   क्रमागत omapfb_update_mode mode)
अणु
	पूर्णांक r;

	omapfb_rqueue_lock(fbdev);
	r = fbdev->ctrl->set_update_mode(mode);
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

अटल क्रमागत omapfb_update_mode omapfb_get_update_mode(काष्ठा omapfb_device *fbdev)
अणु
	पूर्णांक r;

	omapfb_rqueue_lock(fbdev);
	r = fbdev->ctrl->get_update_mode();
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

अटल व्योम omapfb_get_caps(काष्ठा omapfb_device *fbdev, पूर्णांक plane,
				     काष्ठा omapfb_caps *caps)
अणु
	स_रखो(caps, 0, माप(*caps));
	fbdev->ctrl->get_caps(plane, caps);
	अगर (fbdev->panel->get_caps)
		caps->ctrl |= fbdev->panel->get_caps(fbdev->panel);
पूर्ण

/* For lcd testing */
व्योम omapfb_ग_लिखो_first_pixel(काष्ठा omapfb_device *fbdev, u16 pixval)
अणु
	omapfb_rqueue_lock(fbdev);
	*(u16 *)fbdev->mem_desc.region[0].vaddr = pixval;
	अगर (fbdev->ctrl->get_update_mode() == OMAPFB_MANUAL_UPDATE) अणु
		काष्ठा omapfb_update_winकरोw win;

		स_रखो(&win, 0, माप(win));
		win.width = 2;
		win.height = 2;
		win.out_width = 2;
		win.out_height = 2;
		fbdev->ctrl->update_winकरोw(fbdev->fb_info[0], &win, शून्य, शून्य);
	पूर्ण
	omapfb_rqueue_unlock(fbdev);
पूर्ण
EXPORT_SYMBOL(omapfb_ग_लिखो_first_pixel);

/*
 * Ioctl पूर्णांकerface. Part of the kernel mode frame buffer API is duplicated
 * here to be accessible by user mode code.
 */
अटल पूर्णांक omapfb_ioctl(काष्ठा fb_info *fbi, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = fbi->par;
	काष्ठा omapfb_device	*fbdev = plane->fbdev;
	स्थिर काष्ठा fb_ops *ops = fbi->fbops;
	जोड़ अणु
		काष्ठा omapfb_update_winकरोw	update_winकरोw;
		काष्ठा omapfb_plane_info	plane_info;
		काष्ठा omapfb_mem_info		mem_info;
		काष्ठा omapfb_color_key		color_key;
		क्रमागत omapfb_update_mode		update_mode;
		काष्ठा omapfb_caps		caps;
		अचिन्हित पूर्णांक		mirror;
		पूर्णांक			plane_out;
		पूर्णांक			enable_plane;
	पूर्ण p;
	पूर्णांक r = 0;

	BUG_ON(!ops);
	चयन (cmd) अणु
	हाल OMAPFB_MIRROR:
		अगर (get_user(p.mirror, (पूर्णांक __user *)arg))
			r = -EFAULT;
		अन्यथा
			omapfb_mirror(fbi, p.mirror);
		अवरोध;
	हाल OMAPFB_SYNC_GFX:
		omapfb_sync(fbi);
		अवरोध;
	हाल OMAPFB_VSYNC:
		अवरोध;
	हाल OMAPFB_SET_UPDATE_MODE:
		अगर (get_user(p.update_mode, (पूर्णांक __user *)arg))
			r = -EFAULT;
		अन्यथा
			r = omapfb_set_update_mode(fbdev, p.update_mode);
		अवरोध;
	हाल OMAPFB_GET_UPDATE_MODE:
		p.update_mode = omapfb_get_update_mode(fbdev);
		अगर (put_user(p.update_mode,
					(क्रमागत omapfb_update_mode __user *)arg))
			r = -EFAULT;
		अवरोध;
	हाल OMAPFB_UPDATE_WINDOW_OLD:
		अगर (copy_from_user(&p.update_winकरोw, (व्योम __user *)arg,
				   माप(काष्ठा omapfb_update_winकरोw_old)))
			r = -EFAULT;
		अन्यथा अणु
			काष्ठा omapfb_update_winकरोw *u = &p.update_winकरोw;
			u->out_x = u->x;
			u->out_y = u->y;
			u->out_width = u->width;
			u->out_height = u->height;
			स_रखो(u->reserved, 0, माप(u->reserved));
			r = omapfb_update_win(fbi, u);
		पूर्ण
		अवरोध;
	हाल OMAPFB_UPDATE_WINDOW:
		अगर (copy_from_user(&p.update_winकरोw, (व्योम __user *)arg,
				   माप(p.update_winकरोw)))
			r = -EFAULT;
		अन्यथा
			r = omapfb_update_win(fbi, &p.update_winकरोw);
		अवरोध;
	हाल OMAPFB_SETUP_PLANE:
		अगर (copy_from_user(&p.plane_info, (व्योम __user *)arg,
				   माप(p.plane_info)))
			r = -EFAULT;
		अन्यथा
			r = omapfb_setup_plane(fbi, &p.plane_info);
		अवरोध;
	हाल OMAPFB_QUERY_PLANE:
		अगर ((r = omapfb_query_plane(fbi, &p.plane_info)) < 0)
			अवरोध;
		अगर (copy_to_user((व्योम __user *)arg, &p.plane_info,
				   माप(p.plane_info)))
			r = -EFAULT;
		अवरोध;
	हाल OMAPFB_SETUP_MEM:
		अगर (copy_from_user(&p.mem_info, (व्योम __user *)arg,
				   माप(p.mem_info)))
			r = -EFAULT;
		अन्यथा
			r = omapfb_setup_mem(fbi, &p.mem_info);
		अवरोध;
	हाल OMAPFB_QUERY_MEM:
		अगर ((r = omapfb_query_mem(fbi, &p.mem_info)) < 0)
			अवरोध;
		अगर (copy_to_user((व्योम __user *)arg, &p.mem_info,
				   माप(p.mem_info)))
			r = -EFAULT;
		अवरोध;
	हाल OMAPFB_SET_COLOR_KEY:
		अगर (copy_from_user(&p.color_key, (व्योम __user *)arg,
				   माप(p.color_key)))
			r = -EFAULT;
		अन्यथा
			r = omapfb_set_color_key(fbdev, &p.color_key);
		अवरोध;
	हाल OMAPFB_GET_COLOR_KEY:
		अगर ((r = omapfb_get_color_key(fbdev, &p.color_key)) < 0)
			अवरोध;
		अगर (copy_to_user((व्योम __user *)arg, &p.color_key,
				 माप(p.color_key)))
			r = -EFAULT;
		अवरोध;
	हाल OMAPFB_GET_CAPS:
		omapfb_get_caps(fbdev, plane->idx, &p.caps);
		अगर (copy_to_user((व्योम __user *)arg, &p.caps, माप(p.caps)))
			r = -EFAULT;
		अवरोध;
	हाल OMAPFB_LCD_TEST:
		अणु
			पूर्णांक test_num;

			अगर (get_user(test_num, (पूर्णांक __user *)arg)) अणु
				r = -EFAULT;
				अवरोध;
			पूर्ण
			अगर (!fbdev->panel->run_test) अणु
				r = -EINVAL;
				अवरोध;
			पूर्ण
			r = fbdev->panel->run_test(fbdev->panel, test_num);
			अवरोध;
		पूर्ण
	हाल OMAPFB_CTRL_TEST:
		अणु
			पूर्णांक test_num;

			अगर (get_user(test_num, (पूर्णांक __user *)arg)) अणु
				r = -EFAULT;
				अवरोध;
			पूर्ण
			अगर (!fbdev->ctrl->run_test) अणु
				r = -EINVAL;
				अवरोध;
			पूर्ण
			r = fbdev->ctrl->run_test(test_num);
			अवरोध;
		पूर्ण
	शेष:
		r = -EINVAL;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा omapfb_plane_काष्ठा *plane = info->par;
	काष्ठा omapfb_device *fbdev = plane->fbdev;
	पूर्णांक r;

	omapfb_rqueue_lock(fbdev);
	r = fbdev->ctrl->mmap(info, vma);
	omapfb_rqueue_unlock(fbdev);

	वापस r;
पूर्ण

/*
 * Callback table क्रम the frame buffer framework. Some of these poपूर्णांकers
 * will be changed according to the current setting of fb_info->accel_flags.
 */
अटल काष्ठा fb_ops omapfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो        = omapfb_खोलो,
	.fb_release     = omapfb_release,
	.fb_setcolreg	= omapfb_setcolreg,
	.fb_setcmap	= omapfb_setcmap,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_blank       = omapfb_blank,
	.fb_ioctl	= omapfb_ioctl,
	.fb_check_var	= omapfb_check_var,
	.fb_set_par	= omapfb_set_par,
	.fb_pan_display = omapfb_pan_display,
पूर्ण;

/*
 * ---------------------------------------------------------------------------
 * Sysfs पूर्णांकerface
 * ---------------------------------------------------------------------------
 */
/* omapfbX sysfs entries */
अटल sमाप_प्रकार omapfb_show_caps_num(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा omapfb_device *fbdev = dev_get_drvdata(dev);
	पूर्णांक plane;
	माप_प्रकार size;
	काष्ठा omapfb_caps caps;

	plane = 0;
	size = 0;
	जबतक (size < PAGE_SIZE && plane < OMAPFB_PLANE_NUM) अणु
		omapfb_get_caps(fbdev, plane, &caps);
		size += scnम_लिखो(&buf[size], PAGE_SIZE - size,
			"plane#%d %#010x %#010x %#010x\n",
			plane, caps.ctrl, caps.plane_color, caps.wnd_color);
		plane++;
	पूर्ण
	वापस size;
पूर्ण

अटल sमाप_प्रकार omapfb_show_caps_text(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा omapfb_device *fbdev = dev_get_drvdata(dev);
	पूर्णांक i;
	काष्ठा omapfb_caps caps;
	पूर्णांक plane;
	माप_प्रकार size;

	plane = 0;
	size = 0;
	जबतक (size < PAGE_SIZE && plane < OMAPFB_PLANE_NUM) अणु
		omapfb_get_caps(fbdev, plane, &caps);
		size += scnम_लिखो(&buf[size], PAGE_SIZE - size,
				 "plane#%d:\n", plane);
		क्रम (i = 0; i < ARRAY_SIZE(ctrl_caps) &&
		     size < PAGE_SIZE; i++) अणु
			अगर (ctrl_caps[i].flag & caps.ctrl)
				size += scnम_लिखो(&buf[size], PAGE_SIZE - size,
					" %s\n", ctrl_caps[i].name);
		पूर्ण
		size += scnम_लिखो(&buf[size], PAGE_SIZE - size,
				 " plane colors:\n");
		क्रम (i = 0; i < ARRAY_SIZE(color_caps) &&
		     size < PAGE_SIZE; i++) अणु
			अगर (color_caps[i].flag & caps.plane_color)
				size += scnम_लिखो(&buf[size], PAGE_SIZE - size,
					"  %s\n", color_caps[i].name);
		पूर्ण
		size += scnम_लिखो(&buf[size], PAGE_SIZE - size,
				 " window colors:\n");
		क्रम (i = 0; i < ARRAY_SIZE(color_caps) &&
		     size < PAGE_SIZE; i++) अणु
			अगर (color_caps[i].flag & caps.wnd_color)
				size += scnम_लिखो(&buf[size], PAGE_SIZE - size,
					"  %s\n", color_caps[i].name);
		पूर्ण

		plane++;
	पूर्ण
	वापस size;
पूर्ण

अटल DEVICE_ATTR(caps_num, 0444, omapfb_show_caps_num, शून्य);
अटल DEVICE_ATTR(caps_text, 0444, omapfb_show_caps_text, शून्य);

/* panel sysfs entries */
अटल sमाप_प्रकार omapfb_show_panel_name(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा omapfb_device *fbdev = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", fbdev->panel->name);
पूर्ण

अटल sमाप_प्रकार omapfb_show_bklight_level(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा omapfb_device *fbdev = dev_get_drvdata(dev);
	पूर्णांक r;

	अगर (fbdev->panel->get_bklight_level) अणु
		r = snम_लिखो(buf, PAGE_SIZE, "%d\n",
			     fbdev->panel->get_bklight_level(fbdev->panel));
	पूर्ण अन्यथा
		r = -ENODEV;
	वापस r;
पूर्ण

अटल sमाप_प्रकार omapfb_store_bklight_level(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omapfb_device *fbdev = dev_get_drvdata(dev);
	पूर्णांक r;

	अगर (fbdev->panel->set_bklight_level) अणु
		अचिन्हित पूर्णांक level;

		अगर (माला_पूछो(buf, "%10d", &level) == 1) अणु
			r = fbdev->panel->set_bklight_level(fbdev->panel,
							    level);
		पूर्ण अन्यथा
			r = -EINVAL;
	पूर्ण अन्यथा
		r = -ENODEV;
	वापस r ? r : size;
पूर्ण

अटल sमाप_प्रकार omapfb_show_bklight_max(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा omapfb_device *fbdev = dev_get_drvdata(dev);
	पूर्णांक r;

	अगर (fbdev->panel->get_bklight_level) अणु
		r = snम_लिखो(buf, PAGE_SIZE, "%d\n",
			     fbdev->panel->get_bklight_max(fbdev->panel));
	पूर्ण अन्यथा
		r = -ENODEV;
	वापस r;
पूर्ण

अटल काष्ठा device_attribute dev_attr_panel_name =
	__ATTR(name, 0444, omapfb_show_panel_name, शून्य);
अटल DEVICE_ATTR(backlight_level, 0664,
		   omapfb_show_bklight_level, omapfb_store_bklight_level);
अटल DEVICE_ATTR(backlight_max, 0444, omapfb_show_bklight_max, शून्य);

अटल काष्ठा attribute *panel_attrs[] = अणु
	&dev_attr_panel_name.attr,
	&dev_attr_backlight_level.attr,
	&dev_attr_backlight_max.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group panel_attr_grp = अणु
	.name  = "panel",
	.attrs = panel_attrs,
पूर्ण;

/* ctrl sysfs entries */
अटल sमाप_प्रकार omapfb_show_ctrl_name(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा omapfb_device *fbdev = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", fbdev->ctrl->name);
पूर्ण

अटल काष्ठा device_attribute dev_attr_ctrl_name =
	__ATTR(name, 0444, omapfb_show_ctrl_name, शून्य);

अटल काष्ठा attribute *ctrl_attrs[] = अणु
	&dev_attr_ctrl_name.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ctrl_attr_grp = अणु
	.name  = "ctrl",
	.attrs = ctrl_attrs,
पूर्ण;

अटल पूर्णांक omapfb_रेजिस्टर_sysfs(काष्ठा omapfb_device *fbdev)
अणु
	पूर्णांक r;

	अगर ((r = device_create_file(fbdev->dev, &dev_attr_caps_num)))
		जाओ fail0;

	अगर ((r = device_create_file(fbdev->dev, &dev_attr_caps_text)))
		जाओ fail1;

	अगर ((r = sysfs_create_group(&fbdev->dev->kobj, &panel_attr_grp)))
		जाओ fail2;

	अगर ((r = sysfs_create_group(&fbdev->dev->kobj, &ctrl_attr_grp)))
		जाओ fail3;

	वापस 0;
fail3:
	sysfs_हटाओ_group(&fbdev->dev->kobj, &panel_attr_grp);
fail2:
	device_हटाओ_file(fbdev->dev, &dev_attr_caps_text);
fail1:
	device_हटाओ_file(fbdev->dev, &dev_attr_caps_num);
fail0:
	dev_err(fbdev->dev, "unable to register sysfs interface\n");
	वापस r;
पूर्ण

अटल व्योम omapfb_unरेजिस्टर_sysfs(काष्ठा omapfb_device *fbdev)
अणु
	sysfs_हटाओ_group(&fbdev->dev->kobj, &ctrl_attr_grp);
	sysfs_हटाओ_group(&fbdev->dev->kobj, &panel_attr_grp);
	device_हटाओ_file(fbdev->dev, &dev_attr_caps_num);
	device_हटाओ_file(fbdev->dev, &dev_attr_caps_text);
पूर्ण

/*
 * ---------------------------------------------------------------------------
 * LDM callbacks
 * ---------------------------------------------------------------------------
 */
/* Initialize प्रणाली fb_info object and set the शेष video mode.
 * The frame buffer memory alपढ़ोy allocated by lcddma_init
 */
अटल पूर्णांक fbinfo_init(काष्ठा omapfb_device *fbdev, काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo	*var = &info->var;
	काष्ठा fb_fix_screeninfo	*fix = &info->fix;
	पूर्णांक				r = 0;

	info->fbops = &omapfb_ops;
	info->flags = FBINFO_FLAG_DEFAULT;

	म_नकलन(fix->id, MODULE_NAME, माप(fix->id));

	info->pseuकरो_palette = fbdev->pseuकरो_palette;

	var->accel_flags  = def_accel ? FB_ACCELF_TEXT : 0;
	var->xres = def_vxres;
	var->yres = def_vyres;
	var->xres_भव = def_vxres;
	var->yres_भव = def_vyres;
	var->rotate	  = def_rotate;
	var->bits_per_pixel = fbdev->panel->bpp;

	set_fb_var(info, var);
	set_fb_fix(info, 1);

	r = fb_alloc_cmap(&info->cmap, 16, 0);
	अगर (r != 0)
		dev_err(fbdev->dev, "unable to allocate color map memory\n");

	वापस r;
पूर्ण

/* Release the fb_info object */
अटल व्योम fbinfo_cleanup(काष्ठा omapfb_device *fbdev, काष्ठा fb_info *fbi)
अणु
	fb_dealloc_cmap(&fbi->cmap);
पूर्ण

अटल व्योम planes_cleanup(काष्ठा omapfb_device *fbdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fbdev->mem_desc.region_cnt; i++) अणु
		अगर (fbdev->fb_info[i] == शून्य)
			अवरोध;
		fbinfo_cleanup(fbdev, fbdev->fb_info[i]);
		framebuffer_release(fbdev->fb_info[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक planes_init(काष्ठा omapfb_device *fbdev)
अणु
	काष्ठा fb_info *fbi;
	पूर्णांक i;
	पूर्णांक r;

	क्रम (i = 0; i < fbdev->mem_desc.region_cnt; i++) अणु
		काष्ठा omapfb_plane_काष्ठा *plane;
		fbi = framebuffer_alloc(माप(काष्ठा omapfb_plane_काष्ठा),
					fbdev->dev);
		अगर (fbi == शून्य) अणु
			planes_cleanup(fbdev);
			वापस -ENOMEM;
		पूर्ण
		plane = fbi->par;
		plane->idx = i;
		plane->fbdev = fbdev;
		plane->info.mirror = def_mirror;
		fbdev->fb_info[i] = fbi;

		अगर ((r = fbinfo_init(fbdev, fbi)) < 0) अणु
			framebuffer_release(fbi);
			planes_cleanup(fbdev);
			वापस r;
		पूर्ण
		plane->info.out_width = fbi->var.xres;
		plane->info.out_height = fbi->var.yres;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Free driver resources. Can be called to rollback an पातed initialization
 * sequence.
 */
अटल व्योम omapfb_मुक्त_resources(काष्ठा omapfb_device *fbdev, पूर्णांक state)
अणु
	पूर्णांक i;

	चयन (state) अणु
	हाल OMAPFB_ACTIVE:
		क्रम (i = 0; i < fbdev->mem_desc.region_cnt; i++)
			unरेजिस्टर_framebuffer(fbdev->fb_info[i]);
		fallthrough;
	हाल 7:
		omapfb_unरेजिस्टर_sysfs(fbdev);
		fallthrough;
	हाल 6:
		अगर (fbdev->panel->disable)
			fbdev->panel->disable(fbdev->panel);
		fallthrough;
	हाल 5:
		omapfb_set_update_mode(fbdev, OMAPFB_UPDATE_DISABLED);
		fallthrough;
	हाल 4:
		planes_cleanup(fbdev);
		fallthrough;
	हाल 3:
		ctrl_cleanup(fbdev);
		fallthrough;
	हाल 2:
		अगर (fbdev->panel->cleanup)
			fbdev->panel->cleanup(fbdev->panel);
		fallthrough;
	हाल 1:
		dev_set_drvdata(fbdev->dev, शून्य);
		kमुक्त(fbdev);
	हाल 0:
		/* nothing to मुक्त */
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक omapfb_find_ctrl(काष्ठा omapfb_device *fbdev)
अणु
	काष्ठा omapfb_platक्रमm_data *conf;
	अक्षर name[17];
	पूर्णांक i;

	conf = dev_get_platdata(fbdev->dev);

	fbdev->ctrl = शून्य;

	म_नकलन(name, conf->lcd.ctrl_name, माप(name) - 1);
	name[माप(name) - 1] = '\0';

	अगर (म_भेद(name, "internal") == 0) अणु
		fbdev->ctrl = fbdev->पूर्णांक_ctrl;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ctrls); i++) अणु
		dev_dbg(fbdev->dev, "ctrl %s\n", ctrls[i]->name);
		अगर (म_भेद(ctrls[i]->name, name) == 0) अणु
			fbdev->ctrl = ctrls[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fbdev->ctrl == शून्य) अणु
		dev_dbg(fbdev->dev, "ctrl %s not supported\n", name);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Called by LDM binding to probe and attach a new device.
 * Initialization sequence:
 *   1. allocate प्रणाली omapfb_device काष्ठाure
 *   2. select controller type according to platक्रमm configuration
 *      init LCD panel
 *   3. init LCD controller and LCD DMA
 *   4. init प्रणाली fb_info काष्ठाure क्रम all planes
 *   5. setup video mode क्रम first plane and enable it
 *   6. enable LCD panel
 *   7. रेजिस्टर sysfs attributes
 *   OMAPFB_ACTIVE: रेजिस्टर प्रणाली fb_info काष्ठाure क्रम all planes
 */
अटल पूर्णांक omapfb_करो_probe(काष्ठा platक्रमm_device *pdev,
				काष्ठा lcd_panel *panel)
अणु
	काष्ठा omapfb_device	*fbdev = शून्य;
	पूर्णांक			init_state;
	अचिन्हित दीर्घ		phz, hhz, vhz;
	अचिन्हित दीर्घ		vram;
	पूर्णांक			i;
	पूर्णांक			r = 0;

	init_state = 0;

	अगर (pdev->num_resources != 0) अणु
		dev_err(&pdev->dev, "probed for an unknown device\n");
		r = -ENODEV;
		जाओ cleanup;
	पूर्ण

	अगर (dev_get_platdata(&pdev->dev) == शून्य) अणु
		dev_err(&pdev->dev, "missing platform data\n");
		r = -ENOENT;
		जाओ cleanup;
	पूर्ण

	fbdev = kzalloc(माप(*fbdev), GFP_KERNEL);
	अगर (fbdev == शून्य) अणु
		dev_err(&pdev->dev,
			"unable to allocate memory for device info\n");
		r = -ENOMEM;
		जाओ cleanup;
	पूर्ण
	init_state++;

	fbdev->dev = &pdev->dev;
	fbdev->panel = panel;
	fbdev->dssdev = &omapdss_device;
	platक्रमm_set_drvdata(pdev, fbdev);

	mutex_init(&fbdev->rqueue_mutex);

	fbdev->पूर्णांक_ctrl = &omap1_पूर्णांक_ctrl;
#अगर_घोषित CONFIG_FB_OMAP_LCDC_EXTERNAL
	fbdev->ext_अगर = &omap1_ext_अगर;
#पूर्ण_अगर
	अगर (omapfb_find_ctrl(fbdev) < 0) अणु
		dev_err(fbdev->dev,
			"LCD controller not found, board not supported\n");
		r = -ENODEV;
		जाओ cleanup;
	पूर्ण

	अगर (fbdev->panel->init) अणु
		r = fbdev->panel->init(fbdev->panel, fbdev);
		अगर (r)
			जाओ cleanup;
	पूर्ण

	pr_info("omapfb: configured for panel %s\n", fbdev->panel->name);

	def_vxres = def_vxres ? def_vxres : fbdev->panel->x_res;
	def_vyres = def_vyres ? def_vyres : fbdev->panel->y_res;

	init_state++;

	r = ctrl_init(fbdev);
	अगर (r)
		जाओ cleanup;
	अगर (fbdev->ctrl->mmap != शून्य)
		omapfb_ops.fb_mmap = omapfb_mmap;
	init_state++;

	r = planes_init(fbdev);
	अगर (r)
		जाओ cleanup;
	init_state++;

#अगर_घोषित CONFIG_FB_OMAP_DMA_TUNE
	/* Set DMA priority क्रम EMIFF access to highest */
	omap_set_dma_priority(0, OMAP_DMA_PORT_EMIFF, 15);
#पूर्ण_अगर

	r = ctrl_change_mode(fbdev->fb_info[0]);
	अगर (r) अणु
		dev_err(fbdev->dev, "mode setting failed\n");
		जाओ cleanup;
	पूर्ण

	/* GFX plane is enabled by शेष */
	r = fbdev->ctrl->enable_plane(OMAPFB_PLANE_GFX, 1);
	अगर (r)
		जाओ cleanup;

	omapfb_set_update_mode(fbdev, manual_update ?
				   OMAPFB_MANUAL_UPDATE : OMAPFB_AUTO_UPDATE);
	init_state++;

	अगर (fbdev->panel->enable) अणु
		r = fbdev->panel->enable(fbdev->panel);
		अगर (r)
			जाओ cleanup;
	पूर्ण
	init_state++;

	r = omapfb_रेजिस्टर_sysfs(fbdev);
	अगर (r)
		जाओ cleanup;
	init_state++;

	vram = 0;
	क्रम (i = 0; i < fbdev->mem_desc.region_cnt; i++) अणु
		r = रेजिस्टर_framebuffer(fbdev->fb_info[i]);
		अगर (r != 0) अणु
			dev_err(fbdev->dev,
				"registering framebuffer %d failed\n", i);
			जाओ cleanup;
		पूर्ण
		vram += fbdev->mem_desc.region[i].size;
	पूर्ण

	fbdev->state = OMAPFB_ACTIVE;

	panel = fbdev->panel;
	phz = panel->pixel_घड़ी * 1000;
	hhz = phz * 10 / (panel->hfp + panel->x_res + panel->hbp + panel->hsw);
	vhz = hhz / (panel->vfp + panel->y_res + panel->vbp + panel->vsw);

	omapfb_dev = fbdev;

	pr_info("omapfb: Framebuffer initialized. Total vram %lu planes %d\n",
			vram, fbdev->mem_desc.region_cnt);
	pr_info("omapfb: Pixclock %lu kHz hfreq %lu.%lu kHz "
			"vfreq %lu.%lu Hz\n",
			phz / 1000, hhz / 10000, hhz % 10, vhz / 10, vhz % 10);

	वापस 0;

cleanup:
	omapfb_मुक्त_resources(fbdev, init_state);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक r;

	BUG_ON(fbdev_pdev != शून्य);

	r = platक्रमm_device_रेजिस्टर(&omapdss_device);
	अगर (r) अणु
		dev_err(&pdev->dev, "can't register omapdss device\n");
		वापस r;
	पूर्ण

	/* Delay actual initialization until the LCD is रेजिस्टरed */
	fbdev_pdev = pdev;
	अगर (fbdev_panel != शून्य)
		omapfb_करो_probe(fbdev_pdev, fbdev_panel);
	वापस 0;
पूर्ण

व्योम omapfb_रेजिस्टर_panel(काष्ठा lcd_panel *panel)
अणु
	BUG_ON(fbdev_panel != शून्य);

	fbdev_panel = panel;
	अगर (fbdev_pdev != शून्य)
		omapfb_करो_probe(fbdev_pdev, fbdev_panel);
पूर्ण
EXPORT_SYMBOL_GPL(omapfb_रेजिस्टर_panel);

/* Called when the device is being detached from the driver */
अटल पूर्णांक omapfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omapfb_device *fbdev = platक्रमm_get_drvdata(pdev);
	क्रमागत omapfb_state saved_state = fbdev->state;

	/* FIXME: रुको till completion of pending events */

	fbdev->state = OMAPFB_DISABLED;
	omapfb_मुक्त_resources(fbdev, saved_state);

	platक्रमm_device_unरेजिस्टर(&omapdss_device);
	fbdev->dssdev = शून्य;

	वापस 0;
पूर्ण

/* PM suspend */
अटल पूर्णांक omapfb_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t mesg)
अणु
	काष्ठा omapfb_device *fbdev = platक्रमm_get_drvdata(pdev);

	अगर (fbdev != शून्य)
		omapfb_blank(FB_BLANK_POWERDOWN, fbdev->fb_info[0]);
	वापस 0;
पूर्ण

/* PM resume */
अटल पूर्णांक omapfb_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omapfb_device *fbdev = platक्रमm_get_drvdata(pdev);

	अगर (fbdev != शून्य)
		omapfb_blank(FB_BLANK_UNBLANK, fbdev->fb_info[0]);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omapfb_driver = अणु
	.probe		= omapfb_probe,
	.हटाओ		= omapfb_हटाओ,
	.suspend	= omapfb_suspend,
	.resume		= omapfb_resume,
	.driver		= अणु
		.name	= MODULE_NAME,
	पूर्ण,
पूर्ण;

#अगर_अघोषित MODULE

/* Process kernel command line parameters */
अटल पूर्णांक __init omapfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt = शून्य;
	पूर्णांक r = 0;

	pr_debug("omapfb: options %s\n", options);

	अगर (!options || !*options)
		वापस 0;

	जबतक (!r && (this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "accel", 5))
			def_accel = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "vram:", 5)) अणु
			अक्षर *suffix;
			अचिन्हित दीर्घ vram;
			vram = (simple_म_से_अदीर्घ(this_opt + 5, &suffix, 0));
			चयन (suffix[0]) अणु
			हाल '\0':
				अवरोध;
			हाल 'm':
			हाल 'M':
				vram *= 1024;
				fallthrough;
			हाल 'k':
			हाल 'K':
				vram *= 1024;
				अवरोध;
			शेष:
				pr_debug("omapfb: invalid vram suffix %c\n",
					 suffix[0]);
				r = -1;
			पूर्ण
			def_vram[def_vram_cnt++] = vram;
		पूर्ण
		अन्यथा अगर (!म_भेदन(this_opt, "vxres:", 6))
			def_vxres = simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "vyres:", 6))
			def_vyres = simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "rotate:", 7))
			def_rotate = (simple_म_से_अदीर्घ(this_opt + 7, शून्य, 0));
		अन्यथा अगर (!म_भेदन(this_opt, "mirror:", 7))
			def_mirror = (simple_म_से_अदीर्घ(this_opt + 7, शून्य, 0));
		अन्यथा अगर (!म_भेदन(this_opt, "manual_update", 13))
			manual_update = 1;
		अन्यथा अणु
			pr_debug("omapfb: invalid option\n");
			r = -1;
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

#पूर्ण_अगर

/* Register both the driver and the device */
अटल पूर्णांक __init omapfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option;

	अगर (fb_get_options("omapfb", &option))
		वापस -ENODEV;
	omapfb_setup(option);
#पूर्ण_अगर
	/* Register the driver with LDM */
	अगर (platक्रमm_driver_रेजिस्टर(&omapfb_driver)) अणु
		pr_debug("failed to register omapfb driver\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास omapfb_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omapfb_driver);
पूर्ण

module_param_named(accel, def_accel, uपूर्णांक, 0664);
module_param_array_named(vram, def_vram, uदीर्घ, &def_vram_cnt, 0664);
module_param_named(vxres, def_vxres, दीर्घ, 0664);
module_param_named(vyres, def_vyres, दीर्घ, 0664);
module_param_named(rotate, def_rotate, uपूर्णांक, 0664);
module_param_named(mirror, def_mirror, uपूर्णांक, 0664);
module_param_named(manual_update, manual_update, bool, 0664);

module_init(omapfb_init);
module_निकास(omapfb_cleanup);

MODULE_DESCRIPTION("TI OMAP framebuffer driver");
MODULE_AUTHOR("Imre Deak <imre.deak@nokia.com>");
MODULE_LICENSE("GPL");
