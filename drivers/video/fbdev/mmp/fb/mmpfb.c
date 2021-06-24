<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/video/mmp/fb/mmpfb.c
 * Framebuffer driver क्रम Marvell Display controller.
 *
 * Copyright (C) 2012 Marvell Technology Group Ltd.
 * Authors: Zhou Zhu <zzhu3@marvell.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "mmpfb.h"

अटल पूर्णांक var_to_pixfmt(काष्ठा fb_var_screeninfo *var)
अणु
	/*
	 * Pseuकरोcolor mode?
	 */
	अगर (var->bits_per_pixel == 8)
		वापस PIXFMT_PSEUDOCOLOR;

	/*
	 * Check क्रम YUV422PLANAR.
	 */
	अगर (var->bits_per_pixel == 16 && var->red.length == 8 &&
			var->green.length == 4 && var->blue.length == 4) अणु
		अगर (var->green.offset >= var->blue.offset)
			वापस PIXFMT_YUV422P;
		अन्यथा
			वापस PIXFMT_YVU422P;
	पूर्ण

	/*
	 * Check क्रम YUV420PLANAR.
	 */
	अगर (var->bits_per_pixel == 12 && var->red.length == 8 &&
			var->green.length == 2 && var->blue.length == 2) अणु
		अगर (var->green.offset >= var->blue.offset)
			वापस PIXFMT_YUV420P;
		अन्यथा
			वापस PIXFMT_YVU420P;
	पूर्ण

	/*
	 * Check क्रम YUV422PACK.
	 */
	अगर (var->bits_per_pixel == 16 && var->red.length == 16 &&
			var->green.length == 16 && var->blue.length == 16) अणु
		अगर (var->red.offset == 0)
			वापस PIXFMT_YUYV;
		अन्यथा अगर (var->green.offset >= var->blue.offset)
			वापस PIXFMT_UYVY;
		अन्यथा
			वापस PIXFMT_VYUY;
	पूर्ण

	/*
	 * Check क्रम 565/1555.
	 */
	अगर (var->bits_per_pixel == 16 && var->red.length <= 5 &&
			var->green.length <= 6 && var->blue.length <= 5) अणु
		अगर (var->transp.length == 0) अणु
			अगर (var->red.offset >= var->blue.offset)
				वापस PIXFMT_RGB565;
			अन्यथा
				वापस PIXFMT_BGR565;
		पूर्ण
	पूर्ण

	/*
	 * Check क्रम 888/A888.
	 */
	अगर (var->bits_per_pixel <= 32 && var->red.length <= 8 &&
			var->green.length <= 8 && var->blue.length <= 8) अणु
		अगर (var->bits_per_pixel == 24 && var->transp.length == 0) अणु
			अगर (var->red.offset >= var->blue.offset)
				वापस PIXFMT_RGB888PACK;
			अन्यथा
				वापस PIXFMT_BGR888PACK;
		पूर्ण

		अगर (var->bits_per_pixel == 32 && var->transp.offset == 24) अणु
			अगर (var->red.offset >= var->blue.offset)
				वापस PIXFMT_RGBA888;
			अन्यथा
				वापस PIXFMT_BGRA888;
		पूर्ण अन्यथा अणु
			अगर (var->red.offset >= var->blue.offset)
				वापस PIXFMT_RGB888UNPACK;
			अन्यथा
				वापस PIXFMT_BGR888UNPACK;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम pixfmt_to_var(काष्ठा fb_var_screeninfo *var, पूर्णांक pix_fmt)
अणु
	चयन (pix_fmt) अणु
	हाल PIXFMT_RGB565:
		var->bits_per_pixel = 16;
		var->red.offset = 11;	var->red.length = 5;
		var->green.offset = 5;   var->green.length = 6;
		var->blue.offset = 0;	var->blue.length = 5;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_BGR565:
		var->bits_per_pixel = 16;
		var->red.offset = 0;	var->red.length = 5;
		var->green.offset = 5;	 var->green.length = 6;
		var->blue.offset = 11;	var->blue.length = 5;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_RGB888UNPACK:
		var->bits_per_pixel = 32;
		var->red.offset = 16;	var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_BGR888UNPACK:
		var->bits_per_pixel = 32;
		var->red.offset = 0;	var->red.length = 8;
		var->green.offset = 8;	 var->green.length = 8;
		var->blue.offset = 16;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_RGBA888:
		var->bits_per_pixel = 32;
		var->red.offset = 16;	var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;	var->blue.length = 8;
		var->transp.offset = 24; var->transp.length = 8;
		अवरोध;
	हाल PIXFMT_BGRA888:
		var->bits_per_pixel = 32;
		var->red.offset = 0;	var->red.length = 8;
		var->green.offset = 8;	 var->green.length = 8;
		var->blue.offset = 16;	var->blue.length = 8;
		var->transp.offset = 24; var->transp.length = 8;
		अवरोध;
	हाल PIXFMT_RGB888PACK:
		var->bits_per_pixel = 24;
		var->red.offset = 16;	var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_BGR888PACK:
		var->bits_per_pixel = 24;
		var->red.offset = 0;	var->red.length = 8;
		var->green.offset = 8;	 var->green.length = 8;
		var->blue.offset = 16;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_YUV420P:
		var->bits_per_pixel = 12;
		var->red.offset = 4;	 var->red.length = 8;
		var->green.offset = 2;   var->green.length = 2;
		var->blue.offset = 0;   var->blue.length = 2;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_YVU420P:
		var->bits_per_pixel = 12;
		var->red.offset = 4;	 var->red.length = 8;
		var->green.offset = 0;	 var->green.length = 2;
		var->blue.offset = 2;	var->blue.length = 2;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_YUV422P:
		var->bits_per_pixel = 16;
		var->red.offset = 8;	 var->red.length = 8;
		var->green.offset = 4;   var->green.length = 4;
		var->blue.offset = 0;   var->blue.length = 4;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_YVU422P:
		var->bits_per_pixel = 16;
		var->red.offset = 8;	 var->red.length = 8;
		var->green.offset = 0;	 var->green.length = 4;
		var->blue.offset = 4;	var->blue.length = 4;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_UYVY:
		var->bits_per_pixel = 16;
		var->red.offset = 8;	 var->red.length = 16;
		var->green.offset = 4;   var->green.length = 16;
		var->blue.offset = 0;   var->blue.length = 16;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_VYUY:
		var->bits_per_pixel = 16;
		var->red.offset = 8;	 var->red.length = 16;
		var->green.offset = 0;	 var->green.length = 16;
		var->blue.offset = 4;	var->blue.length = 16;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_YUYV:
		var->bits_per_pixel = 16;
		var->red.offset = 0;	 var->red.length = 16;
		var->green.offset = 4;	 var->green.length = 16;
		var->blue.offset = 8;	var->blue.length = 16;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	हाल PIXFMT_PSEUDOCOLOR:
		var->bits_per_pixel = 8;
		var->red.offset = 0;	 var->red.length = 8;
		var->green.offset = 0;   var->green.length = 8;
		var->blue.offset = 0;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * fb framework has its limitation:
 * 1. input color/output color is not seprated
 * 2. fb_videomode not include output color
 * so क्रम fb usage, we keep a output क्रमmat which is not changed
 *  then it's added क्रम mmpmode
 */
अटल व्योम fbmode_to_mmpmode(काष्ठा mmp_mode *mode,
		काष्ठा fb_videomode *videomode, पूर्णांक output_fmt)
अणु
	u64 भाग_result = 1000000000000ll;
	mode->name = videomode->name;
	mode->refresh = videomode->refresh;
	mode->xres = videomode->xres;
	mode->yres = videomode->yres;

	करो_भाग(भाग_result, videomode->pixघड़ी);
	mode->pixघड़ी_freq = (u32)भाग_result;

	mode->left_margin = videomode->left_margin;
	mode->right_margin = videomode->right_margin;
	mode->upper_margin = videomode->upper_margin;
	mode->lower_margin = videomode->lower_margin;
	mode->hsync_len = videomode->hsync_len;
	mode->vsync_len = videomode->vsync_len;
	mode->hsync_invert = !!(videomode->sync & FB_SYNC_HOR_HIGH_ACT);
	mode->vsync_invert = !!(videomode->sync & FB_SYNC_VERT_HIGH_ACT);
	/* no defined flag in fb, use vmode>>3*/
	mode->invert_pixघड़ी = !!(videomode->vmode & 8);
	mode->pix_fmt_out = output_fmt;
पूर्ण

अटल व्योम mmpmode_to_fbmode(काष्ठा fb_videomode *videomode,
		काष्ठा mmp_mode *mode)
अणु
	u64 भाग_result = 1000000000000ll;

	videomode->name = mode->name;
	videomode->refresh = mode->refresh;
	videomode->xres = mode->xres;
	videomode->yres = mode->yres;

	करो_भाग(भाग_result, mode->pixघड़ी_freq);
	videomode->pixघड़ी = (u32)भाग_result;

	videomode->left_margin = mode->left_margin;
	videomode->right_margin = mode->right_margin;
	videomode->upper_margin = mode->upper_margin;
	videomode->lower_margin = mode->lower_margin;
	videomode->hsync_len = mode->hsync_len;
	videomode->vsync_len = mode->vsync_len;
	videomode->sync = (mode->hsync_invert ? FB_SYNC_HOR_HIGH_ACT : 0)
		| (mode->vsync_invert ? FB_SYNC_VERT_HIGH_ACT : 0);
	videomode->vmode = mode->invert_pixघड़ी ? 8 : 0;
पूर्ण

अटल पूर्णांक mmpfb_check_var(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info)
अणु
	काष्ठा mmpfb_info *fbi = info->par;

	अगर (var->bits_per_pixel == 8)
		वापस -EINVAL;
	/*
	 * Basic geometry sanity checks.
	 */
	अगर (var->xoffset + var->xres > var->xres_भव)
		वापस -EINVAL;
	अगर (var->yoffset + var->yres > var->yres_भव)
		वापस -EINVAL;

	/*
	 * Check size of framebuffer.
	 */
	अगर (var->xres_भव * var->yres_भव *
			(var->bits_per_pixel >> 3) > fbi->fb_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक chan_to_field(अचिन्हित पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	वापस ((chan & 0xffff) >> (16 - bf->length)) << bf->offset;
पूर्ण

अटल u32 to_rgb(u16 red, u16 green, u16 blue)
अणु
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	वापस (red << 16) | (green << 8) | blue;
पूर्ण

अटल पूर्णांक mmpfb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
		अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
		अचिन्हित पूर्णांक trans, काष्ठा fb_info *info)
अणु
	काष्ठा mmpfb_info *fbi = info->par;
	u32 val;

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR && regno < 16) अणु
		val =  chan_to_field(red,   &info->var.red);
		val |= chan_to_field(green, &info->var.green);
		val |= chan_to_field(blue , &info->var.blue);
		fbi->pseuकरो_palette[regno] = val;
	पूर्ण

	अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR && regno < 256) अणु
		val = to_rgb(red, green, blue);
		/* TODO */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmpfb_pan_display(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info)
अणु
	काष्ठा mmpfb_info *fbi = info->par;
	काष्ठा mmp_addr addr;

	स_रखो(&addr, 0, माप(addr));
	addr.phys[0] = (var->yoffset * var->xres_भव + var->xoffset)
		* var->bits_per_pixel / 8 + fbi->fb_start_dma;
	mmp_overlay_set_addr(fbi->overlay, &addr);

	वापस 0;
पूर्ण

अटल पूर्णांक var_update(काष्ठा fb_info *info)
अणु
	काष्ठा mmpfb_info *fbi = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा fb_videomode *m;
	पूर्णांक pix_fmt;

	/* set pix_fmt */
	pix_fmt = var_to_pixfmt(var);
	अगर (pix_fmt < 0)
		वापस -EINVAL;
	pixfmt_to_var(var, pix_fmt);
	fbi->pix_fmt = pix_fmt;

	/* set var according to best video mode*/
	m = (काष्ठा fb_videomode *)fb_match_mode(var, &info->modelist);
	अगर (!m) अणु
		dev_err(fbi->dev, "set par: no match mode, use best mode\n");
		m = (काष्ठा fb_videomode *)fb_find_best_mode(var,
				&info->modelist);
		fb_videomode_to_var(var, m);
	पूर्ण
	स_नकल(&fbi->mode, m, माप(काष्ठा fb_videomode));

	/* fix to 2* yres */
	var->yres_भव = var->yres * 2;
	info->fix.visual = (pix_fmt == PIXFMT_PSEUDOCOLOR) ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = var->xres_भव * var->bits_per_pixel / 8;
	info->fix.ypanstep = var->yres;
	वापस 0;
पूर्ण

अटल व्योम mmpfb_set_win(काष्ठा fb_info *info)
अणु
	काष्ठा mmpfb_info *fbi = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा mmp_win win;
	u32 stride;

	स_रखो(&win, 0, माप(win));
	win.xsrc = win.xdst = fbi->mode.xres;
	win.ysrc = win.ydst = fbi->mode.yres;
	win.pix_fmt = fbi->pix_fmt;
	stride = pixfmt_to_stride(win.pix_fmt);
	win.pitch[0] = var->xres_भव * stride;
	win.pitch[1] = win.pitch[2] =
		(stride == 1) ? (var->xres_भव >> 1) : 0;
	mmp_overlay_set_win(fbi->overlay, &win);
पूर्ण

अटल पूर्णांक mmpfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा mmpfb_info *fbi = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा mmp_addr addr;
	काष्ठा mmp_mode mode;
	पूर्णांक ret;

	ret = var_update(info);
	अगर (ret != 0)
		वापस ret;

	/* set winकरोw/path according to new videomode */
	fbmode_to_mmpmode(&mode, &fbi->mode, fbi->output_fmt);
	mmp_path_set_mode(fbi->path, &mode);

	/* set winकरोw related info */
	mmpfb_set_win(info);

	/* set address always */
	स_रखो(&addr, 0, माप(addr));
	addr.phys[0] = (var->yoffset * var->xres_भव + var->xoffset)
		* var->bits_per_pixel / 8 + fbi->fb_start_dma;
	mmp_overlay_set_addr(fbi->overlay, &addr);

	वापस 0;
पूर्ण

अटल व्योम mmpfb_घातer(काष्ठा mmpfb_info *fbi, पूर्णांक घातer)
अणु
	काष्ठा mmp_addr addr;
	काष्ठा fb_var_screeninfo *var = &fbi->fb_info->var;

	/* क्रम घातer on, always set address/winकरोw again */
	अगर (घातer) अणु
		/* set winकरोw related info */
		mmpfb_set_win(fbi->fb_info);

		/* set address always */
		स_रखो(&addr, 0, माप(addr));
		addr.phys[0] = fbi->fb_start_dma +
			(var->yoffset * var->xres_भव + var->xoffset)
			* var->bits_per_pixel / 8;
		mmp_overlay_set_addr(fbi->overlay, &addr);
	पूर्ण
	mmp_overlay_set_onoff(fbi->overlay, घातer);
पूर्ण

अटल पूर्णांक mmpfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा mmpfb_info *fbi = info->par;

	mmpfb_घातer(fbi, (blank == FB_BLANK_UNBLANK));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops mmpfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_blank	= mmpfb_blank,
	.fb_check_var	= mmpfb_check_var,
	.fb_set_par	= mmpfb_set_par,
	.fb_setcolreg	= mmpfb_setcolreg,
	.fb_pan_display	= mmpfb_pan_display,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक modes_setup(काष्ठा mmpfb_info *fbi)
अणु
	काष्ठा fb_videomode *videomodes;
	काष्ठा mmp_mode *mmp_modes;
	काष्ठा fb_info *info = fbi->fb_info;
	पूर्णांक videomode_num, i;

	/* get videomodes from path */
	videomode_num = mmp_path_get_modelist(fbi->path, &mmp_modes);
	अगर (!videomode_num) अणु
		dev_warn(fbi->dev, "can't get videomode num\n");
		वापस 0;
	पूर्ण
	/* put videomode list to info काष्ठाure */
	videomodes = kसुस्मृति(videomode_num, माप(काष्ठा fb_videomode),
			     GFP_KERNEL);
	अगर (!videomodes)
		वापस -ENOMEM;

	क्रम (i = 0; i < videomode_num; i++)
		mmpmode_to_fbmode(&videomodes[i], &mmp_modes[i]);
	fb_videomode_to_modelist(videomodes, videomode_num, &info->modelist);

	/* set videomode[0] as शेष mode */
	स_नकल(&fbi->mode, &videomodes[0], माप(काष्ठा fb_videomode));
	fbi->output_fmt = mmp_modes[0].pix_fmt_out;
	fb_videomode_to_var(&info->var, &fbi->mode);
	mmp_path_set_mode(fbi->path, &mmp_modes[0]);

	kमुक्त(videomodes);
	वापस videomode_num;
पूर्ण

अटल पूर्णांक fb_info_setup(काष्ठा fb_info *info,
			काष्ठा mmpfb_info *fbi)
अणु
	पूर्णांक ret = 0;
	/* Initialise अटल fb parameters.*/
	info->flags = FBINFO_DEFAULT | FBINFO_PARTIAL_PAN_OK |
		FBINFO_HWACCEL_XPAN | FBINFO_HWACCEL_YPAN;
	info->node = -1;
	म_नकल(info->fix.id, fbi->name);
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 0;
	info->fix.ypanstep = info->var.yres;
	info->fix.ywrapstep = 0;
	info->fix.accel = FB_ACCEL_NONE;
	info->fix.smem_start = fbi->fb_start_dma;
	info->fix.smem_len = fbi->fb_size;
	info->fix.visual = (fbi->pix_fmt == PIXFMT_PSEUDOCOLOR) ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = info->var.xres_भव *
		info->var.bits_per_pixel / 8;
	info->fbops = &mmpfb_ops;
	info->pseuकरो_palette = fbi->pseuकरो_palette;
	info->screen_buffer = fbi->fb_start;
	info->screen_size = fbi->fb_size;

	/* For FB framework: Allocate color map and Register framebuffer*/
	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0)
		ret = -ENOMEM;

	वापस ret;
पूर्ण

अटल व्योम fb_info_clear(काष्ठा fb_info *info)
अणु
	fb_dealloc_cmap(&info->cmap);
पूर्ण

अटल पूर्णांक mmpfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmp_buffer_driver_mach_info *mi;
	काष्ठा fb_info *info;
	काष्ठा mmpfb_info *fbi;
	पूर्णांक ret, modes_num;

	mi = pdev->dev.platक्रमm_data;
	अगर (mi == शून्य) अणु
		dev_err(&pdev->dev, "no platform data defined\n");
		वापस -EINVAL;
	पूर्ण

	/* initialize fb */
	info = framebuffer_alloc(माप(काष्ठा mmpfb_info), &pdev->dev);
	अगर (info == शून्य)
		वापस -ENOMEM;
	fbi = info->par;

	/* init fb */
	fbi->fb_info = info;
	platक्रमm_set_drvdata(pdev, fbi);
	fbi->dev = &pdev->dev;
	fbi->name = mi->name;
	fbi->pix_fmt = mi->शेष_pixfmt;
	pixfmt_to_var(&info->var, fbi->pix_fmt);
	mutex_init(&fbi->access_ok);

	/* get display path by name */
	fbi->path = mmp_get_path(mi->path_name);
	अगर (!fbi->path) अणु
		dev_err(&pdev->dev, "can't get the path %s\n", mi->path_name);
		ret = -EINVAL;
		जाओ failed_destroy_mutex;
	पूर्ण

	dev_info(fbi->dev, "path %s get\n", fbi->path->name);

	/* get overlay */
	fbi->overlay = mmp_path_get_overlay(fbi->path, mi->overlay_id);
	अगर (!fbi->overlay) अणु
		ret = -EINVAL;
		जाओ failed_destroy_mutex;
	पूर्ण
	/* set fetch used */
	mmp_overlay_set_fetch(fbi->overlay, mi->dmafetch_id);

	modes_num = modes_setup(fbi);
	अगर (modes_num < 0) अणु
		ret = modes_num;
		जाओ failed_destroy_mutex;
	पूर्ण

	/*
	 * अगर get modes success, means not hotplug panels, use caculated buffer
	 * or use शेष size
	 */
	अगर (modes_num > 0) अणु
		/* fix to 2* yres */
		info->var.yres_भव = info->var.yres * 2;

		/* Allocate framebuffer memory: size = modes xy *4 */
		fbi->fb_size = info->var.xres_भव * info->var.yres_भव
				* info->var.bits_per_pixel / 8;
	पूर्ण अन्यथा अणु
		fbi->fb_size = MMPFB_DEFAULT_SIZE;
	पूर्ण

	fbi->fb_start = dma_alloc_coherent(&pdev->dev, PAGE_ALIGN(fbi->fb_size),
				&fbi->fb_start_dma, GFP_KERNEL);
	अगर (fbi->fb_start == शून्य) अणु
		dev_err(&pdev->dev, "can't alloc framebuffer\n");
		ret = -ENOMEM;
		जाओ failed_destroy_mutex;
	पूर्ण
	dev_info(fbi->dev, "fb %dk allocated\n", fbi->fb_size/1024);

	/* fb घातer on */
	अगर (modes_num > 0)
		mmpfb_घातer(fbi, 1);

	ret = fb_info_setup(info, fbi);
	अगर (ret < 0)
		जाओ failed_मुक्त_buff;

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register fb: %d\n", ret);
		ret = -ENXIO;
		जाओ failed_clear_info;
	पूर्ण

	dev_info(fbi->dev, "loaded to /dev/fb%d <%s>.\n",
		info->node, info->fix.id);

#अगर_घोषित CONFIG_LOGO
	अगर (fbi->fb_start) अणु
		fb_prepare_logo(info, 0);
		fb_show_logo(info, 0);
	पूर्ण
#पूर्ण_अगर

	वापस 0;

failed_clear_info:
	fb_info_clear(info);
failed_मुक्त_buff:
	dma_मुक्त_coherent(&pdev->dev, PAGE_ALIGN(fbi->fb_size), fbi->fb_start,
		fbi->fb_start_dma);
failed_destroy_mutex:
	mutex_destroy(&fbi->access_ok);
	dev_err(fbi->dev, "mmp-fb: frame buffer device init failed\n");

	framebuffer_release(info);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver mmpfb_driver = अणु
	.driver		= अणु
		.name	= "mmp-fb",
	पूर्ण,
	.probe		= mmpfb_probe,
पूर्ण;

अटल पूर्णांक mmpfb_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mmpfb_driver);
पूर्ण
module_init(mmpfb_init);

MODULE_AUTHOR("Zhou Zhu <zhou.zhu@marvell.com>");
MODULE_DESCRIPTION("Framebuffer driver for Marvell displays");
MODULE_LICENSE("GPL");
