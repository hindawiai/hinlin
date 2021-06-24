<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/w100fb.c
 *
 * Frame Buffer Device क्रम ATI Imageon w100 (Wallaby)
 *
 * Copyright (C) 2002, ATI Corp.
 * Copyright (C) 2004-2006 Riअक्षरd Purdie
 * Copyright (c) 2005 Ian Molton
 * Copyright (c) 2006 Alberto Mardegan
 *
 * Rewritten क्रम 2.6 by Riअक्षरd Purdie <rpurdie@rpsys.net>
 *
 * Generic platक्रमm support by Ian Molton <spyro@f2s.com>
 * and Riअक्षरd Purdie <rpurdie@rpsys.net>
 *
 * w32xx support by Ian Molton
 *
 * Hardware acceleration support by Alberto Mardegan
 * <mardy@users.sourceक्रमge.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <video/w100fb.h>
#समावेश "w100fb.h"

/*
 * Prototypes
 */
अटल व्योम w100_suspend(u32 mode);
अटल व्योम w100_vsync(व्योम);
अटल व्योम w100_hw_init(काष्ठा w100fb_par*);
अटल व्योम w100_pwm_setup(काष्ठा w100fb_par*);
अटल व्योम w100_init_घड़ीs(काष्ठा w100fb_par*);
अटल व्योम w100_setup_memory(काष्ठा w100fb_par*);
अटल व्योम w100_init_lcd(काष्ठा w100fb_par*);
अटल व्योम w100_set_dispregs(काष्ठा w100fb_par*);
अटल व्योम w100_update_enable(व्योम);
अटल व्योम w100_update_disable(व्योम);
अटल व्योम calc_hsync(काष्ठा w100fb_par *par);
अटल व्योम w100_init_graphic_engine(काष्ठा w100fb_par *par);
काष्ठा w100_pll_info *w100_get_xtal_table(अचिन्हित पूर्णांक freq);

/* Pseuकरो palette size */
#घोषणा MAX_PALETTES      16

#घोषणा W100_SUSPEND_EXTMEM 0
#घोषणा W100_SUSPEND_ALL    1

#घोषणा BITS_PER_PIXEL    16

/* Remapped addresses क्रम base cfg, memmapped regs and the frame buffer itself */
अटल व्योम __iomem *remapped_base;
अटल व्योम __iomem *remapped_regs;
अटल व्योम __iomem *remapped_fbuf;

#घोषणा REMAPPED_FB_LEN   0x15ffff

/* This is the offset in the w100's address space we map the current
   framebuffer memory to. We use the position of बाह्यal memory as
   we can remap पूर्णांकernal memory to there अगर बाह्यal isn't present. */
#घोषणा W100_FB_BASE MEM_EXT_BASE_VALUE


/*
 * Sysfs functions
 */
अटल sमाप_प्रकार flip_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा w100fb_par *par=info->par;

	वापस प्र_लिखो(buf, "%d\n",par->flip);
पूर्ण

अटल sमाप_प्रकार flip_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक flip;
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा w100fb_par *par=info->par;

	flip = simple_म_से_अदीर्घ(buf, शून्य, 10);

	अगर (flip > 0)
		par->flip = 1;
	अन्यथा
		par->flip = 0;

	w100_update_disable();
	w100_set_dispregs(par);
	w100_update_enable();

	calc_hsync(par);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(flip);

अटल sमाप_प्रकार w100fb_reg_पढ़ो(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ regs, param;
	regs = simple_म_से_अदीर्घ(buf, शून्य, 16);
	param = पढ़ोl(remapped_regs + regs);
	prपूर्णांकk("Read Register 0x%08lX: 0x%08lX\n", regs, param);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(reg_पढ़ो, 0200, शून्य, w100fb_reg_पढ़ो);

अटल sमाप_प्रकार w100fb_reg_ग_लिखो(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ regs, param;
	माला_पूछो(buf, "%lx %lx", &regs, &param);

	अगर (regs <= 0x2000) अणु
		prपूर्णांकk("Write Register 0x%08lX: 0x%08lX\n", regs, param);
		ग_लिखोl(param, remapped_regs + regs);
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(reg_ग_लिखो, 0200, शून्य, w100fb_reg_ग_लिखो);


अटल sमाप_प्रकार fastpllclk_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा w100fb_par *par=info->par;

	वापस प्र_लिखो(buf, "%d\n",par->fastpll_mode);
पूर्ण

अटल sमाप_प्रकार fastpllclk_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा w100fb_par *par=info->par;

	अगर (simple_म_से_अदीर्घ(buf, शून्य, 10) > 0) अणु
		par->fastpll_mode=1;
		prपूर्णांकk("w100fb: Using fast system clock (if possible)\n");
	पूर्ण अन्यथा अणु
		par->fastpll_mode=0;
		prपूर्णांकk("w100fb: Using normal system clock\n");
	पूर्ण

	w100_init_घड़ीs(par);
	calc_hsync(par);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(fastpllclk);

अटल काष्ठा attribute *w100fb_attrs[] = अणु
	&dev_attr_fastpllclk.attr,
	&dev_attr_reg_पढ़ो.attr,
	&dev_attr_reg_ग_लिखो.attr,
	&dev_attr_flip.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(w100fb);

/*
 * Some touchscreens need hsync inक्रमmation from the video driver to
 * function correctly. We export it here.
 */
अचिन्हित दीर्घ w100fb_get_hsynclen(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा w100fb_par *par=info->par;

	/* If display is blanked/suspended, hsync isn't active */
	अगर (par->blanked)
		वापस 0;
	अन्यथा
		वापस par->hsync_len;
पूर्ण
EXPORT_SYMBOL(w100fb_get_hsynclen);

अटल व्योम w100fb_clear_screen(काष्ठा w100fb_par *par)
अणु
	स_रखो_io(remapped_fbuf + (W100_FB_BASE-MEM_WINDOW_BASE), 0, (par->xres * par->yres * BITS_PER_PIXEL/8));
पूर्ण


/*
 * Set a palette value from rgb components
 */
अटल पूर्णांक w100fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			     u_पूर्णांक trans, काष्ठा fb_info *info)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 1;

	/*
	 * If greyscale is true, then we convert the RGB value
	 * to greyscale no matter what visual we are using.
	 */
	अगर (info->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green + 7471 * blue) >> 16;

	/*
	 * 16-bit True Colour.  We encode the RGB value
	 * according to the RGB bitfield inक्रमmation.
	 */
	अगर (regno < MAX_PALETTES) अणु
		u32 *pal = info->pseuकरो_palette;

		val = (red & 0xf800) | ((green & 0xfc00) >> 5) | ((blue & 0xf800) >> 11);
		pal[regno] = val;
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण


/*
 * Blank the display based on value in blank_mode
 */
अटल पूर्णांक w100fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा w100fb_par *par = info->par;
	काष्ठा w100_tg_info *tg = par->mach->tg;

	चयन(blank_mode) अणु

 	हाल FB_BLANK_NORMAL:         /* Normal blanking */
	हाल FB_BLANK_VSYNC_SUSPEND:  /* VESA blank (vsync off) */
	हाल FB_BLANK_HSYNC_SUSPEND:  /* VESA blank (hsync off) */
 	हाल FB_BLANK_POWERDOWN:      /* Poweroff */
  		अगर (par->blanked == 0) अणु
			अगर(tg && tg->suspend)
				tg->suspend(par);
			par->blanked = 1;
  		पूर्ण
  		अवरोध;

 	हाल FB_BLANK_UNBLANK: /* Unblanking */
  		अगर (par->blanked != 0) अणु
			अगर(tg && tg->resume)
				tg->resume(par);
			par->blanked = 0;
  		पूर्ण
  		अवरोध;
 	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम w100_fअगरo_रुको(पूर्णांक entries)
अणु
	जोड़ rbbm_status_u status;
	पूर्णांक i;

	क्रम (i = 0; i < 2000000; i++) अणु
		status.val = पढ़ोl(remapped_regs + mmRBBM_STATUS);
		अगर (status.f.cmdfअगरo_avail >= entries)
			वापस;
		udelay(1);
	पूर्ण
	prपूर्णांकk(KERN_ERR "w100fb: FIFO Timeout!\n");
पूर्ण


अटल पूर्णांक w100fb_sync(काष्ठा fb_info *info)
अणु
	जोड़ rbbm_status_u status;
	पूर्णांक i;

	क्रम (i = 0; i < 2000000; i++) अणु
		status.val = पढ़ोl(remapped_regs + mmRBBM_STATUS);
		अगर (!status.f.gui_active)
			वापस 0;
		udelay(1);
	पूर्ण
	prपूर्णांकk(KERN_ERR "w100fb: Graphic engine timeout!\n");
	वापस -EBUSY;
पूर्ण


अटल व्योम w100_init_graphic_engine(काष्ठा w100fb_par *par)
अणु
	जोड़ dp_gui_master_cntl_u gmc;
	जोड़ dp_mix_u dp_mix;
	जोड़ dp_datatype_u dp_datatype;
	जोड़ dp_cntl_u dp_cntl;

	w100_fअगरo_रुको(4);
	ग_लिखोl(W100_FB_BASE, remapped_regs + mmDST_OFFSET);
	ग_लिखोl(par->xres, remapped_regs + mmDST_PITCH);
	ग_लिखोl(W100_FB_BASE, remapped_regs + mmSRC_OFFSET);
	ग_लिखोl(par->xres, remapped_regs + mmSRC_PITCH);

	w100_fअगरo_रुको(3);
	ग_लिखोl(0, remapped_regs + mmSC_TOP_LEFT);
	ग_लिखोl((par->yres << 16) | par->xres, remapped_regs + mmSC_BOTTOM_RIGHT);
	ग_लिखोl(0x1fff1fff, remapped_regs + mmSRC_SC_BOTTOM_RIGHT);

	w100_fअगरo_रुको(4);
	dp_cntl.val = 0;
	dp_cntl.f.dst_x_dir = 1;
	dp_cntl.f.dst_y_dir = 1;
	dp_cntl.f.src_x_dir = 1;
	dp_cntl.f.src_y_dir = 1;
	dp_cntl.f.dst_major_x = 1;
	dp_cntl.f.src_major_x = 1;
	ग_लिखोl(dp_cntl.val, remapped_regs + mmDP_CNTL);

	gmc.val = 0;
	gmc.f.gmc_src_pitch_offset_cntl = 1;
	gmc.f.gmc_dst_pitch_offset_cntl = 1;
	gmc.f.gmc_src_clipping = 1;
	gmc.f.gmc_dst_clipping = 1;
	gmc.f.gmc_brush_datatype = GMC_BRUSH_NONE;
	gmc.f.gmc_dst_datatype = 3; /* from DstType_16Bpp_444 */
	gmc.f.gmc_src_datatype = SRC_DATATYPE_EQU_DST;
	gmc.f.gmc_byte_pix_order = 1;
	gmc.f.gmc_शेष_sel = 0;
	gmc.f.gmc_rop3 = ROP3_SRCCOPY;
	gmc.f.gmc_dp_src_source = DP_SRC_MEM_RECTANGULAR;
	gmc.f.gmc_clr_cmp_fcn_dis = 1;
	gmc.f.gmc_wr_msk_dis = 1;
	gmc.f.gmc_dp_op = DP_OP_ROP;
	ग_लिखोl(gmc.val, remapped_regs + mmDP_GUI_MASTER_CNTL);

	dp_datatype.val = dp_mix.val = 0;
	dp_datatype.f.dp_dst_datatype = gmc.f.gmc_dst_datatype;
	dp_datatype.f.dp_brush_datatype = gmc.f.gmc_brush_datatype;
	dp_datatype.f.dp_src2_type = 0;
	dp_datatype.f.dp_src2_datatype = gmc.f.gmc_src_datatype;
	dp_datatype.f.dp_src_datatype = gmc.f.gmc_src_datatype;
	dp_datatype.f.dp_byte_pix_order = gmc.f.gmc_byte_pix_order;
	ग_लिखोl(dp_datatype.val, remapped_regs + mmDP_DATATYPE);

	dp_mix.f.dp_src_source = gmc.f.gmc_dp_src_source;
	dp_mix.f.dp_src2_source = 1;
	dp_mix.f.dp_rop3 = gmc.f.gmc_rop3;
	dp_mix.f.dp_op = gmc.f.gmc_dp_op;
	ग_लिखोl(dp_mix.val, remapped_regs + mmDP_MIX);
पूर्ण


अटल व्योम w100fb_fillrect(काष्ठा fb_info *info,
                            स्थिर काष्ठा fb_fillrect *rect)
अणु
	जोड़ dp_gui_master_cntl_u gmc;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	gmc.val = पढ़ोl(remapped_regs + mmDP_GUI_MASTER_CNTL);
	gmc.f.gmc_rop3 = ROP3_PATCOPY;
	gmc.f.gmc_brush_datatype = GMC_BRUSH_SOLID_COLOR;
	w100_fअगरo_रुको(2);
	ग_लिखोl(gmc.val, remapped_regs + mmDP_GUI_MASTER_CNTL);
	ग_लिखोl(rect->color, remapped_regs + mmDP_BRUSH_FRGD_CLR);

	w100_fअगरo_रुको(2);
	ग_लिखोl((rect->dy << 16) | (rect->dx & 0xffff), remapped_regs + mmDST_Y_X);
	ग_लिखोl((rect->width << 16) | (rect->height & 0xffff),
	       remapped_regs + mmDST_WIDTH_HEIGHT);
पूर्ण


अटल व्योम w100fb_copyarea(काष्ठा fb_info *info,
                            स्थिर काष्ठा fb_copyarea *area)
अणु
	u32 dx = area->dx, dy = area->dy, sx = area->sx, sy = area->sy;
	u32 h = area->height, w = area->width;
	जोड़ dp_gui_master_cntl_u gmc;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	gmc.val = पढ़ोl(remapped_regs + mmDP_GUI_MASTER_CNTL);
	gmc.f.gmc_rop3 = ROP3_SRCCOPY;
	gmc.f.gmc_brush_datatype = GMC_BRUSH_NONE;
	w100_fअगरo_रुको(1);
	ग_लिखोl(gmc.val, remapped_regs + mmDP_GUI_MASTER_CNTL);

	w100_fअगरo_रुको(3);
	ग_लिखोl((sy << 16) | (sx & 0xffff), remapped_regs + mmSRC_Y_X);
	ग_लिखोl((dy << 16) | (dx & 0xffff), remapped_regs + mmDST_Y_X);
	ग_लिखोl((w << 16) | (h & 0xffff), remapped_regs + mmDST_WIDTH_HEIGHT);
पूर्ण


/*
 *  Change the resolution by calling the appropriate hardware functions
 */
अटल व्योम w100fb_activate_var(काष्ठा w100fb_par *par)
अणु
	काष्ठा w100_tg_info *tg = par->mach->tg;

	w100_pwm_setup(par);
	w100_setup_memory(par);
	w100_init_घड़ीs(par);
	w100fb_clear_screen(par);
	w100_vsync();

	w100_update_disable();
	w100_init_lcd(par);
	w100_set_dispregs(par);
	w100_update_enable();
	w100_init_graphic_engine(par);

	calc_hsync(par);

	अगर (!par->blanked && tg && tg->change)
		tg->change(par);
पूर्ण


/* Select the smallest mode that allows the desired resolution to be
 * displayed. If desired, the x and y parameters can be rounded up to
 * match the selected mode.
 */
अटल काष्ठा w100_mode *w100fb_get_mode(काष्ठा w100fb_par *par, अचिन्हित पूर्णांक *x, अचिन्हित पूर्णांक *y, पूर्णांक saveval)
अणु
	काष्ठा w100_mode *mode = शून्य;
	काष्ठा w100_mode *modelist = par->mach->modelist;
	अचिन्हित पूर्णांक best_x = 0xffffffff, best_y = 0xffffffff;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0 ; i < par->mach->num_modes ; i++) अणु
		अगर (modelist[i].xres >= *x && modelist[i].yres >= *y &&
				modelist[i].xres < best_x && modelist[i].yres < best_y) अणु
			best_x = modelist[i].xres;
			best_y = modelist[i].yres;
			mode = &modelist[i];
		पूर्ण अन्यथा अगर(modelist[i].xres >= *y && modelist[i].yres >= *x &&
		        modelist[i].xres < best_y && modelist[i].yres < best_x) अणु
			best_x = modelist[i].yres;
			best_y = modelist[i].xres;
			mode = &modelist[i];
		पूर्ण
	पूर्ण

	अगर (mode && saveval) अणु
		*x = best_x;
		*y = best_y;
	पूर्ण

	वापस mode;
पूर्ण


/*
 *  w100fb_check_var():
 *  Get the video params out of 'var'. If a value doesn't fit, round it up,
 *  अगर it's too big, वापस -EINVAL.
 */
अटल पूर्णांक w100fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा w100fb_par *par=info->par;

	अगर(!w100fb_get_mode(par, &var->xres, &var->yres, 1))
		वापस -EINVAL;

	अगर (par->mach->mem && ((var->xres*var->yres*BITS_PER_PIXEL/8) > (par->mach->mem->size+1)))
		वापस -EINVAL;

	अगर (!par->mach->mem && ((var->xres*var->yres*BITS_PER_PIXEL/8) > (MEM_INT_SIZE+1)))
		वापस -EINVAL;

	var->xres_भव = max(var->xres_भव, var->xres);
	var->yres_भव = max(var->yres_भव, var->yres);

	अगर (var->bits_per_pixel > BITS_PER_PIXEL)
		वापस -EINVAL;
	अन्यथा
		var->bits_per_pixel = BITS_PER_PIXEL;

	var->red.offset = 11;
	var->red.length = 5;
	var->green.offset = 5;
	var->green.length = 6;
	var->blue.offset = 0;
	var->blue.length = 5;
	var->transp.offset = var->transp.length = 0;

	var->nonstd = 0;
	var->height = -1;
	var->width = -1;
	var->vmode = FB_VMODE_NONINTERLACED;
	var->sync = 0;
	var->pixघड़ी = 0x04;  /* 171521; */

	वापस 0;
पूर्ण


/*
 * w100fb_set_par():
 *	Set the user defined part of the display क्रम the specअगरied console
 *  by looking at the values in info.var
 */
अटल पूर्णांक w100fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा w100fb_par *par=info->par;

	अगर (par->xres != info->var.xres || par->yres != info->var.yres)	अणु
		par->xres = info->var.xres;
		par->yres = info->var.yres;
		par->mode = w100fb_get_mode(par, &par->xres, &par->yres, 0);

		info->fix.visual = FB_VISUAL_TRUECOLOR;
		info->fix.ypanstep = 0;
		info->fix.ywrapstep = 0;
		info->fix.line_length = par->xres * BITS_PER_PIXEL / 8;

		mutex_lock(&info->mm_lock);
		अगर ((par->xres*par->yres*BITS_PER_PIXEL/8) > (MEM_INT_SIZE+1)) अणु
			par->exपंचांगem_active = 1;
			info->fix.smem_len = par->mach->mem->size+1;
		पूर्ण अन्यथा अणु
			par->exपंचांगem_active = 0;
			info->fix.smem_len = MEM_INT_SIZE+1;
		पूर्ण
		mutex_unlock(&info->mm_lock);

		w100fb_activate_var(par);
	पूर्ण
	वापस 0;
पूर्ण


/*
 *  Frame buffer operations
 */
अटल स्थिर काष्ठा fb_ops w100fb_ops = अणु
	.owner        = THIS_MODULE,
	.fb_check_var = w100fb_check_var,
	.fb_set_par   = w100fb_set_par,
	.fb_setcolreg = w100fb_setcolreg,
	.fb_blank     = w100fb_blank,
	.fb_fillrect  = w100fb_fillrect,
	.fb_copyarea  = w100fb_copyarea,
	.fb_imageblit = cfb_imageblit,
	.fb_sync      = w100fb_sync,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल व्योम w100fb_save_vidmem(काष्ठा w100fb_par *par)
अणु
	पूर्णांक memsize;

	अगर (par->exपंचांगem_active) अणु
		memsize=par->mach->mem->size;
		par->saved_exपंचांगem = vदो_स्मृति(memsize);
		अगर (par->saved_exपंचांगem)
			स_नकल_fromio(par->saved_exपंचांगem, remapped_fbuf + (W100_FB_BASE-MEM_WINDOW_BASE), memsize);
	पूर्ण
	memsize=MEM_INT_SIZE;
	par->saved_पूर्णांकmem = vदो_स्मृति(memsize);
	अगर (par->saved_पूर्णांकmem && par->exपंचांगem_active)
		स_नकल_fromio(par->saved_पूर्णांकmem, remapped_fbuf + (W100_FB_BASE-MEM_INT_BASE_VALUE), memsize);
	अन्यथा अगर (par->saved_पूर्णांकmem)
		स_नकल_fromio(par->saved_पूर्णांकmem, remapped_fbuf + (W100_FB_BASE-MEM_WINDOW_BASE), memsize);
पूर्ण

अटल व्योम w100fb_restore_vidmem(काष्ठा w100fb_par *par)
अणु
	पूर्णांक memsize;

	अगर (par->exपंचांगem_active && par->saved_exपंचांगem) अणु
		memsize=par->mach->mem->size;
		स_नकल_toio(remapped_fbuf + (W100_FB_BASE-MEM_WINDOW_BASE), par->saved_exपंचांगem, memsize);
		vमुक्त(par->saved_exपंचांगem);
		par->saved_exपंचांगem = शून्य;
	पूर्ण
	अगर (par->saved_पूर्णांकmem) अणु
		memsize=MEM_INT_SIZE;
		अगर (par->exपंचांगem_active)
			स_नकल_toio(remapped_fbuf + (W100_FB_BASE-MEM_INT_BASE_VALUE), par->saved_पूर्णांकmem, memsize);
		अन्यथा
			स_नकल_toio(remapped_fbuf + (W100_FB_BASE-MEM_WINDOW_BASE), par->saved_पूर्णांकmem, memsize);
		vमुक्त(par->saved_पूर्णांकmem);
		par->saved_पूर्णांकmem = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक w100fb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा w100fb_par *par=info->par;
	काष्ठा w100_tg_info *tg = par->mach->tg;

	w100fb_save_vidmem(par);
	अगर(tg && tg->suspend)
		tg->suspend(par);
	w100_suspend(W100_SUSPEND_ALL);
	par->blanked = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक w100fb_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा w100fb_par *par=info->par;
	काष्ठा w100_tg_info *tg = par->mach->tg;

	w100_hw_init(par);
	w100fb_activate_var(par);
	w100fb_restore_vidmem(par);
	अगर(tg && tg->resume)
		tg->resume(par);
	par->blanked = 0;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा w100fb_suspend  शून्य
#घोषणा w100fb_resume   शून्य
#पूर्ण_अगर


अटल पूर्णांक w100fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err = -EIO;
	काष्ठा w100fb_mach_info *inf;
	काष्ठा fb_info *info = शून्य;
	काष्ठा w100fb_par *par;
	काष्ठा resource *mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अचिन्हित पूर्णांक chip_id;

	अगर (!mem)
		वापस -EINVAL;

	/* Remap the chip base address */
	remapped_base = ioremap(mem->start+W100_CFG_BASE, W100_CFG_LEN);
	अगर (remapped_base == शून्य)
		जाओ out;

	/* Map the रेजिस्टर space */
	remapped_regs = ioremap(mem->start+W100_REG_BASE, W100_REG_LEN);
	अगर (remapped_regs == शून्य)
		जाओ out;

	/* Identअगरy the chip */
	prपूर्णांकk("Found ");
	chip_id = पढ़ोl(remapped_regs + mmCHIP_ID);
	चयन(chip_id) अणु
		हाल CHIP_ID_W100:  prपूर्णांकk("w100");  अवरोध;
		हाल CHIP_ID_W3200: prपूर्णांकk("w3200"); अवरोध;
		हाल CHIP_ID_W3220: prपूर्णांकk("w3220"); अवरोध;
		शेष:
			prपूर्णांकk("Unknown imageon chip ID\n");
			err = -ENODEV;
			जाओ out;
	पूर्ण
	prपूर्णांकk(" at 0x%08lx.\n", (अचिन्हित दीर्घ) mem->start+W100_CFG_BASE);

	/* Remap the framebuffer */
	remapped_fbuf = ioremap(mem->start+MEM_WINDOW_BASE, MEM_WINDOW_SIZE);
	अगर (remapped_fbuf == शून्य)
		जाओ out;

	info=framebuffer_alloc(माप(काष्ठा w100fb_par), &pdev->dev);
	अगर (!info) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	par = info->par;
	platक्रमm_set_drvdata(pdev, info);

	inf = dev_get_platdata(&pdev->dev);
	par->chip_id = chip_id;
	par->mach = inf;
	par->fastpll_mode = 0;
	par->blanked = 0;

	par->pll_table=w100_get_xtal_table(inf->xtal_freq);
	अगर (!par->pll_table) अणु
		prपूर्णांकk(KERN_ERR "No matching Xtal definition found\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	info->pseuकरो_palette = kदो_स्मृति_array(MAX_PALETTES, माप(u32),
					     GFP_KERNEL);
	अगर (!info->pseuकरो_palette) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	info->fbops = &w100fb_ops;
	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_COPYAREA |
		FBINFO_HWACCEL_FILLRECT;
	info->node = -1;
	info->screen_base = remapped_fbuf + (W100_FB_BASE-MEM_WINDOW_BASE);
	info->screen_size = REMAPPED_FB_LEN;

	म_नकल(info->fix.id, "w100fb");
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux = 0;
	info->fix.accel = FB_ACCEL_NONE;
	info->fix.smem_start = mem->start+W100_FB_BASE;
	info->fix.mmio_start = mem->start+W100_REG_BASE;
	info->fix.mmio_len = W100_REG_LEN;

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	par->mode = &inf->modelist[0];
	अगर(inf->init_mode & INIT_MODE_ROTATED) अणु
		info->var.xres = par->mode->yres;
		info->var.yres = par->mode->xres;
	पूर्ण
	अन्यथा अणु
		info->var.xres = par->mode->xres;
		info->var.yres = par->mode->yres;
	पूर्ण

	अगर(inf->init_mode &= INIT_MODE_FLIPPED)
		par->flip = 1;
	अन्यथा
		par->flip = 0;

	info->var.xres_भव = info->var.xres;
	info->var.yres_भव = info->var.yres;
	info->var.pixघड़ी = 0x04;  /* 171521; */
	info->var.sync = 0;
	info->var.grayscale = 0;
	info->var.xoffset = info->var.yoffset = 0;
	info->var.accel_flags = 0;
	info->var.activate = FB_ACTIVATE_NOW;

	w100_hw_init(par);

	अगर (w100fb_check_var(&info->var, info) < 0) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	fb_info(info, "%s frame buffer device\n", info->fix.id);
	वापस 0;
out:
	अगर (info) अणु
		fb_dealloc_cmap(&info->cmap);
		kमुक्त(info->pseuकरो_palette);
	पूर्ण
	अगर (remapped_fbuf != शून्य)
		iounmap(remapped_fbuf);
	अगर (remapped_regs != शून्य)
		iounmap(remapped_regs);
	अगर (remapped_base != शून्य)
		iounmap(remapped_base);
	अगर (info)
		framebuffer_release(info);
	वापस err;
पूर्ण


अटल पूर्णांक w100fb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा w100fb_par *par=info->par;

	unरेजिस्टर_framebuffer(info);

	vमुक्त(par->saved_पूर्णांकmem);
	vमुक्त(par->saved_exपंचांगem);
	kमुक्त(info->pseuकरो_palette);
	fb_dealloc_cmap(&info->cmap);

	iounmap(remapped_base);
	iounmap(remapped_regs);
	iounmap(remapped_fbuf);

	framebuffer_release(info);

	वापस 0;
पूर्ण


/* ------------------- chipset specअगरic functions -------------------------- */


अटल व्योम w100_soft_reset(व्योम)
अणु
	u16 val = पढ़ोw((u16 __iomem *)remapped_base + cfgSTATUS);

	ग_लिखोw(val | 0x08, (u16 __iomem *)remapped_base + cfgSTATUS);
	udelay(100);
	ग_लिखोw(0x00, (u16 __iomem *)remapped_base + cfgSTATUS);
	udelay(100);
पूर्ण

अटल व्योम w100_update_disable(व्योम)
अणु
	जोड़ disp_db_buf_cntl_wr_u disp_db_buf_wr_cntl;

	/* Prevent display updates */
	disp_db_buf_wr_cntl.f.db_buf_cntl = 0x1e;
	disp_db_buf_wr_cntl.f.update_db_buf = 0;
	disp_db_buf_wr_cntl.f.en_db_buf = 0;
	ग_लिखोl((u32) (disp_db_buf_wr_cntl.val), remapped_regs + mmDISP_DB_BUF_CNTL);
पूर्ण

अटल व्योम w100_update_enable(व्योम)
अणु
	जोड़ disp_db_buf_cntl_wr_u disp_db_buf_wr_cntl;

	/* Enable display updates */
	disp_db_buf_wr_cntl.f.db_buf_cntl = 0x1e;
	disp_db_buf_wr_cntl.f.update_db_buf = 1;
	disp_db_buf_wr_cntl.f.en_db_buf = 1;
	ग_लिखोl((u32) (disp_db_buf_wr_cntl.val), remapped_regs + mmDISP_DB_BUF_CNTL);
पूर्ण

अचिन्हित दीर्घ w100fb_gpio_पढ़ो(पूर्णांक port)
अणु
	अचिन्हित दीर्घ value;

	अगर (port==W100_GPIO_PORT_A)
		value = पढ़ोl(remapped_regs + mmGPIO_DATA);
	अन्यथा
		value = पढ़ोl(remapped_regs + mmGPIO_DATA2);

	वापस value;
पूर्ण

व्योम w100fb_gpio_ग_लिखो(पूर्णांक port, अचिन्हित दीर्घ value)
अणु
	अगर (port==W100_GPIO_PORT_A)
		ग_लिखोl(value, remapped_regs + mmGPIO_DATA);
	अन्यथा
		ग_लिखोl(value, remapped_regs + mmGPIO_DATA2);
पूर्ण
EXPORT_SYMBOL(w100fb_gpio_पढ़ो);
EXPORT_SYMBOL(w100fb_gpio_ग_लिखो);

/*
 * Initialization of critical w100 hardware
 */
अटल व्योम w100_hw_init(काष्ठा w100fb_par *par)
अणु
	u32 temp32;
	जोड़ cअगर_cntl_u cअगर_cntl;
	जोड़ पूर्णांकf_cntl_u पूर्णांकf_cntl;
	जोड़ cfgreg_base_u cfgreg_base;
	जोड़ wrap_top_dir_u wrap_top_dir;
	जोड़ cअगर_पढ़ो_dbg_u cअगर_पढ़ो_dbg;
	जोड़ cpu_शेषs_u cpu_शेष;
	जोड़ cअगर_ग_लिखो_dbg_u cअगर_ग_लिखो_dbg;
	जोड़ wrap_start_dir_u wrap_start_dir;
	जोड़ cअगर_io_u cअगर_io;
	काष्ठा w100_gpio_regs *gpio = par->mach->gpio;

	w100_soft_reset();

	/* This is what the fpga_init code करोes on reset. May be wrong
	   but there is little info available */
	ग_लिखोl(0x31, remapped_regs + mmSCRATCH_UMSK);
	क्रम (temp32 = 0; temp32 < 10000; temp32++)
		पढ़ोl(remapped_regs + mmSCRATCH_UMSK);
	ग_लिखोl(0x30, remapped_regs + mmSCRATCH_UMSK);

	/* Set up CIF */
	cअगर_io.val = defCIF_IO;
	ग_लिखोl((u32)(cअगर_io.val), remapped_regs + mmCIF_IO);

	cअगर_ग_लिखो_dbg.val = पढ़ोl(remapped_regs + mmCIF_WRITE_DBG);
	cअगर_ग_लिखो_dbg.f.dis_packer_ful_during_rbbm_समयout = 0;
	cअगर_ग_लिखो_dbg.f.en_dword_split_to_rbbm = 1;
	cअगर_ग_लिखो_dbg.f.dis_समयout_during_rbbm = 1;
	ग_लिखोl((u32) (cअगर_ग_लिखो_dbg.val), remapped_regs + mmCIF_WRITE_DBG);

	cअगर_पढ़ो_dbg.val = पढ़ोl(remapped_regs + mmCIF_READ_DBG);
	cअगर_पढ़ो_dbg.f.dis_rd_same_byte_to_trig_fetch = 1;
	ग_लिखोl((u32) (cअगर_पढ़ो_dbg.val), remapped_regs + mmCIF_READ_DBG);

	cअगर_cntl.val = पढ़ोl(remapped_regs + mmCIF_CNTL);
	cअगर_cntl.f.dis_प्रणाली_bits = 1;
	cअगर_cntl.f.dis_mr = 1;
	cअगर_cntl.f.en_रुको_to_compensate_dq_prop_dly = 0;
	cअगर_cntl.f.पूर्णांकb_oe = 1;
	cअगर_cntl.f.पूर्णांकerrupt_active_high = 1;
	ग_लिखोl((u32) (cअगर_cntl.val), remapped_regs + mmCIF_CNTL);

	/* Setup cfgINTF_CNTL and cfgCPU शेषs */
	पूर्णांकf_cntl.val = defINTF_CNTL;
	पूर्णांकf_cntl.f.ad_inc_a = 1;
	पूर्णांकf_cntl.f.ad_inc_b = 1;
	पूर्णांकf_cntl.f.rd_data_rdy_a = 0;
	पूर्णांकf_cntl.f.rd_data_rdy_b = 0;
	ग_लिखोb((u8) (पूर्णांकf_cntl.val), remapped_base + cfgINTF_CNTL);

	cpu_शेष.val = defCPU_DEFAULTS;
	cpu_शेष.f.access_ind_addr_a = 1;
	cpu_शेष.f.access_ind_addr_b = 1;
	cpu_शेष.f.access_scratch_reg = 1;
	cpu_शेष.f.transition_size = 0;
	ग_लिखोb((u8) (cpu_शेष.val), remapped_base + cfgCPU_DEFAULTS);

	/* set up the apertures */
	ग_लिखोb((u8) (W100_REG_BASE >> 16), remapped_base + cfgREG_BASE);

	cfgreg_base.val = defCFGREG_BASE;
	cfgreg_base.f.cfgreg_base = W100_CFG_BASE;
	ग_लिखोl((u32) (cfgreg_base.val), remapped_regs + mmCFGREG_BASE);

	wrap_start_dir.val = defWRAP_START_सूची;
	wrap_start_dir.f.start_addr = WRAP_BUF_BASE_VALUE >> 1;
	ग_लिखोl((u32) (wrap_start_dir.val), remapped_regs + mmWRAP_START_सूची);

	wrap_top_dir.val = defWRAP_TOP_सूची;
	wrap_top_dir.f.top_addr = WRAP_BUF_TOP_VALUE >> 1;
	ग_लिखोl((u32) (wrap_top_dir.val), remapped_regs + mmWRAP_TOP_सूची);

	ग_लिखोl((u32) 0x2440, remapped_regs + mmRBBM_CNTL);

	/* Set the hardware to 565 colour */
	temp32 = पढ़ोl(remapped_regs + mmDISP_DEBUG2);
	temp32 &= 0xff7fffff;
	temp32 |= 0x00800000;
	ग_लिखोl(temp32, remapped_regs + mmDISP_DEBUG2);

	/* Initialise the GPIO lines */
	अगर (gpio) अणु
		ग_लिखोl(gpio->init_data1, remapped_regs + mmGPIO_DATA);
		ग_लिखोl(gpio->init_data2, remapped_regs + mmGPIO_DATA2);
		ग_लिखोl(gpio->gpio_dir1,  remapped_regs + mmGPIO_CNTL1);
		ग_लिखोl(gpio->gpio_oe1,   remapped_regs + mmGPIO_CNTL2);
		ग_लिखोl(gpio->gpio_dir2,  remapped_regs + mmGPIO_CNTL3);
		ग_लिखोl(gpio->gpio_oe2,   remapped_regs + mmGPIO_CNTL4);
	पूर्ण
पूर्ण


काष्ठा घातer_state अणु
	जोड़ clk_pin_cntl_u clk_pin_cntl;
	जोड़ pll_ref_fb_भाग_u pll_ref_fb_भाग;
	जोड़ pll_cntl_u pll_cntl;
	जोड़ sclk_cntl_u sclk_cntl;
	जोड़ pclk_cntl_u pclk_cntl;
	जोड़ pwrmgt_cntl_u pwrmgt_cntl;
	पूर्णांक स्वतः_mode;  /* प्रणाली घड़ी स्वतः changing? */
पूर्ण;


अटल काष्ठा घातer_state w100_pwr_state;

/* The PLL Fout is determined by (XtalFreq/(M+1)) * ((N_पूर्णांक+1) + (N_fac/8)) */

/* 12.5MHz Crystal PLL Table */
अटल काष्ठा w100_pll_info xtal_12500000[] = अणु
	/*freq     M   N_पूर्णांक    N_fac  tfgoal  lock_समय */
	अणु 50,      0,   1,       0,     0xe0,        56पूर्ण,  /*  50.00 MHz */
	अणु 75,      0,   5,       0,     0xde,        37पूर्ण,  /*  75.00 MHz */
	अणु100,      0,   7,       0,     0xe0,        28पूर्ण,  /* 100.00 MHz */
	अणु125,      0,   9,       0,     0xe0,        22पूर्ण,  /* 125.00 MHz */
	अणु150,      0,   11,      0,     0xe0,        17पूर्ण,  /* 150.00 MHz */
	अणु  0,      0,   0,       0,        0,         0पूर्ण,  /* Terminator */
पूर्ण;

/* 14.318MHz Crystal PLL Table */
अटल काष्ठा w100_pll_info xtal_14318000[] = अणु
	/*freq     M   N_पूर्णांक    N_fac  tfgoal  lock_समय */
	अणु 40,      4,   13,      0,     0xe0,        80पूर्ण, /* tfgoal guessed */
	अणु 50,      1,   6,       0,     0xe0,	     64पूर्ण, /*  50.05 MHz */
	अणु 57,      2,   11,      0,     0xe0,        53पूर्ण, /* tfgoal guessed */
	अणु 75,      0,   4,       3,     0xe0,	     43पूर्ण, /*  75.08 MHz */
	अणु100,      0,   6,       0,     0xe0,        32पूर्ण, /* 100.10 MHz */
	अणु  0,      0,   0,       0,        0,         0पूर्ण,
पूर्ण;

/* 16MHz Crystal PLL Table */
अटल काष्ठा w100_pll_info xtal_16000000[] = अणु
	/*freq     M   N_पूर्णांक    N_fac  tfgoal  lock_समय */
	अणु 72,      1,   8,       0,     0xe0,        48पूर्ण, /* tfgoal guessed */
	अणु 80,      1,   9,       0,     0xe0,        13पूर्ण, /* tfgoal guessed */
	अणु 95,      1,   10,      7,     0xe0,        38पूर्ण, /* tfgoal guessed */
	अणु 96,      1,   11,      0,     0xe0,        36पूर्ण, /* tfgoal guessed */
	अणु  0,      0,   0,       0,        0,         0पूर्ण,
पूर्ण;

अटल काष्ठा pll_entries अणु
	पूर्णांक xtal_freq;
	काष्ठा w100_pll_info *pll_table;
पूर्ण w100_pll_tables[] = अणु
	अणु 12500000, &xtal_12500000[0] पूर्ण,
	अणु 14318000, &xtal_14318000[0] पूर्ण,
	अणु 16000000, &xtal_16000000[0] पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

काष्ठा w100_pll_info *w100_get_xtal_table(अचिन्हित पूर्णांक freq)
अणु
	काष्ठा pll_entries *pll_entry = w100_pll_tables;

	करो अणु
		अगर (freq == pll_entry->xtal_freq)
			वापस pll_entry->pll_table;
		pll_entry++;
	पूर्ण जबतक (pll_entry->xtal_freq);

	वापस शून्य;
पूर्ण


अटल अचिन्हित पूर्णांक w100_get_testcount(अचिन्हित पूर्णांक testclk_sel)
अणु
	जोड़ clk_test_cntl_u clk_test_cntl;

	udelay(5);

	/* Select the test घड़ी source and reset */
	clk_test_cntl.f.start_check_freq = 0x0;
	clk_test_cntl.f.testclk_sel = testclk_sel;
	clk_test_cntl.f.tstcount_rst = 0x1; /* set reset */
	ग_लिखोl((u32) (clk_test_cntl.val), remapped_regs + mmCLK_TEST_CNTL);

	clk_test_cntl.f.tstcount_rst = 0x0; /* clear reset */
	ग_लिखोl((u32) (clk_test_cntl.val), remapped_regs + mmCLK_TEST_CNTL);

	/* Run घड़ी test */
	clk_test_cntl.f.start_check_freq = 0x1;
	ग_लिखोl((u32) (clk_test_cntl.val), remapped_regs + mmCLK_TEST_CNTL);

	/* Give the test समय to complete */
	udelay(20);

	/* Return the result */
	clk_test_cntl.val = पढ़ोl(remapped_regs + mmCLK_TEST_CNTL);
	clk_test_cntl.f.start_check_freq = 0x0;
	ग_लिखोl((u32) (clk_test_cntl.val), remapped_regs + mmCLK_TEST_CNTL);

	वापस clk_test_cntl.f.test_count;
पूर्ण


अटल पूर्णांक w100_pll_adjust(काष्ठा w100_pll_info *pll)
अणु
	अचिन्हित पूर्णांक tf80;
	अचिन्हित पूर्णांक tf20;

	/* Initial Settings */
	w100_pwr_state.pll_cntl.f.pll_pwdn = 0x0;     /* घातer करोwn */
	w100_pwr_state.pll_cntl.f.pll_reset = 0x0;    /* not reset */
	w100_pwr_state.pll_cntl.f.pll_tcpoff = 0x1;   /* Hi-Z */
	w100_pwr_state.pll_cntl.f.pll_pvg = 0x0;      /* VCO gain = 0 */
	w100_pwr_state.pll_cntl.f.pll_vcofr = 0x0;    /* VCO frequency range control = off */
	w100_pwr_state.pll_cntl.f.pll_ioffset = 0x0;  /* current offset inside VCO = 0 */
	w100_pwr_state.pll_cntl.f.pll_ring_off = 0x0;

	/* Wai Ming 80 percent of VDD 1.3V gives 1.04V, minimum operating voltage is 1.08V
	 * thereक्रमe, commented out the following lines
	 * tf80 meant tf100
	 */
	करो अणु
		/* set VCO input = 0.8 * VDD */
		w100_pwr_state.pll_cntl.f.pll_dactal = 0xd;
		ग_लिखोl((u32) (w100_pwr_state.pll_cntl.val), remapped_regs + mmPLL_CNTL);

		tf80 = w100_get_testcount(TESTCLK_SRC_PLL);
		अगर (tf80 >= (pll->tfgoal)) अणु
			/* set VCO input = 0.2 * VDD */
			w100_pwr_state.pll_cntl.f.pll_dactal = 0x7;
			ग_लिखोl((u32) (w100_pwr_state.pll_cntl.val), remapped_regs + mmPLL_CNTL);

			tf20 = w100_get_testcount(TESTCLK_SRC_PLL);
			अगर (tf20 <= (pll->tfgoal))
				वापस 1;  /* Success */

			अगर ((w100_pwr_state.pll_cntl.f.pll_vcofr == 0x0) &&
				((w100_pwr_state.pll_cntl.f.pll_pvg == 0x7) ||
				(w100_pwr_state.pll_cntl.f.pll_ioffset == 0x0))) अणु
				/* slow VCO config */
				w100_pwr_state.pll_cntl.f.pll_vcofr = 0x1;
				w100_pwr_state.pll_cntl.f.pll_pvg = 0x0;
				w100_pwr_state.pll_cntl.f.pll_ioffset = 0x0;
				जारी;
			पूर्ण
		पूर्ण
		अगर ((w100_pwr_state.pll_cntl.f.pll_ioffset) < 0x3) अणु
			w100_pwr_state.pll_cntl.f.pll_ioffset += 0x1;
		पूर्ण अन्यथा अगर ((w100_pwr_state.pll_cntl.f.pll_pvg) < 0x7) अणु
			w100_pwr_state.pll_cntl.f.pll_ioffset = 0x0;
			w100_pwr_state.pll_cntl.f.pll_pvg += 0x1;
		पूर्ण अन्यथा अणु
			वापस 0;  /* Error */
		पूर्ण
	पूर्ण जबतक(1);
पूर्ण


/*
 * w100_pll_calibration
 */
अटल पूर्णांक w100_pll_calibration(काष्ठा w100_pll_info *pll)
अणु
	पूर्णांक status;

	status = w100_pll_adjust(pll);

	/* PLL Reset And Lock */
	/* set VCO input = 0.5 * VDD */
	w100_pwr_state.pll_cntl.f.pll_dactal = 0xa;
	ग_लिखोl((u32) (w100_pwr_state.pll_cntl.val), remapped_regs + mmPLL_CNTL);

	udelay(1);  /* reset समय */

	/* enable अक्षरge pump */
	w100_pwr_state.pll_cntl.f.pll_tcpoff = 0x0;  /* normal */
	ग_लिखोl((u32) (w100_pwr_state.pll_cntl.val), remapped_regs + mmPLL_CNTL);

	/* set VCO input = Hi-Z, disable DAC */
	w100_pwr_state.pll_cntl.f.pll_dactal = 0x0;
	ग_लिखोl((u32) (w100_pwr_state.pll_cntl.val), remapped_regs + mmPLL_CNTL);

	udelay(400);  /* lock समय */

	/* PLL locked */

	वापस status;
पूर्ण


अटल पूर्णांक w100_pll_set_clk(काष्ठा w100_pll_info *pll)
अणु
	पूर्णांक status;

	अगर (w100_pwr_state.स्वतः_mode == 1)  /* स्वतः mode */
	अणु
		w100_pwr_state.pwrmgt_cntl.f.pwm_fast_noml_hw_en = 0x0;  /* disable fast to normal */
		w100_pwr_state.pwrmgt_cntl.f.pwm_noml_fast_hw_en = 0x0;  /* disable normal to fast */
		ग_लिखोl((u32) (w100_pwr_state.pwrmgt_cntl.val), remapped_regs + mmPWRMGT_CNTL);
	पूर्ण

	/* Set प्रणाली घड़ी source to XTAL whilst adjusting the PLL! */
	w100_pwr_state.sclk_cntl.f.sclk_src_sel = CLK_SRC_XTAL;
	ग_लिखोl((u32) (w100_pwr_state.sclk_cntl.val), remapped_regs + mmSCLK_CNTL);

	w100_pwr_state.pll_ref_fb_भाग.f.pll_ref_भाग = pll->M;
	w100_pwr_state.pll_ref_fb_भाग.f.pll_fb_भाग_पूर्णांक = pll->N_पूर्णांक;
	w100_pwr_state.pll_ref_fb_भाग.f.pll_fb_भाग_frac = pll->N_fac;
	w100_pwr_state.pll_ref_fb_भाग.f.pll_lock_समय = pll->lock_समय;
	ग_लिखोl((u32) (w100_pwr_state.pll_ref_fb_भाग.val), remapped_regs + mmPLL_REF_FB_DIV);

	w100_pwr_state.pwrmgt_cntl.f.pwm_mode_req = 0;
	ग_लिखोl((u32) (w100_pwr_state.pwrmgt_cntl.val), remapped_regs + mmPWRMGT_CNTL);

	status = w100_pll_calibration(pll);

	अगर (w100_pwr_state.स्वतः_mode == 1)  /* स्वतः mode */
	अणु
		w100_pwr_state.pwrmgt_cntl.f.pwm_fast_noml_hw_en = 0x1;  /* reenable fast to normal */
		w100_pwr_state.pwrmgt_cntl.f.pwm_noml_fast_hw_en = 0x1;  /* reenable normal to fast  */
		ग_लिखोl((u32) (w100_pwr_state.pwrmgt_cntl.val), remapped_regs + mmPWRMGT_CNTL);
	पूर्ण
	वापस status;
पूर्ण

/* freq = target frequency of the PLL */
अटल पूर्णांक w100_set_pll_freq(काष्ठा w100fb_par *par, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा w100_pll_info *pll = par->pll_table;

	करो अणु
		अगर (freq == pll->freq) अणु
			वापस w100_pll_set_clk(pll);
		पूर्ण
		pll++;
	पूर्ण जबतक(pll->freq);
	वापस 0;
पूर्ण

/* Set up an initial state.  Some values/fields set
   here will be overwritten. */
अटल व्योम w100_pwm_setup(काष्ठा w100fb_par *par)
अणु
	w100_pwr_state.clk_pin_cntl.f.osc_en = 0x1;
	w100_pwr_state.clk_pin_cntl.f.osc_gain = 0x1f;
	w100_pwr_state.clk_pin_cntl.f.करोnt_use_xtalin = 0x0;
	w100_pwr_state.clk_pin_cntl.f.xtalin_pm_en = 0x0;
	w100_pwr_state.clk_pin_cntl.f.xtalin_dbl_en = par->mach->xtal_dbl ? 1 : 0;
	w100_pwr_state.clk_pin_cntl.f.cg_debug = 0x0;
	ग_लिखोl((u32) (w100_pwr_state.clk_pin_cntl.val), remapped_regs + mmCLK_PIN_CNTL);

	w100_pwr_state.sclk_cntl.f.sclk_src_sel = CLK_SRC_XTAL;
	w100_pwr_state.sclk_cntl.f.sclk_post_भाग_fast = 0x0;  /* Pfast = 1 */
	w100_pwr_state.sclk_cntl.f.sclk_clkon_hys = 0x3;
	w100_pwr_state.sclk_cntl.f.sclk_post_भाग_slow = 0x0;  /* Pslow = 1 */
	w100_pwr_state.sclk_cntl.f.disp_cg_ok2चयन_en = 0x0;
	w100_pwr_state.sclk_cntl.f.sclk_क्रमce_reg = 0x0;    /* Dynamic */
	w100_pwr_state.sclk_cntl.f.sclk_क्रमce_disp = 0x0;   /* Dynamic */
	w100_pwr_state.sclk_cntl.f.sclk_क्रमce_mc = 0x0;     /* Dynamic */
	w100_pwr_state.sclk_cntl.f.sclk_क्रमce_exपंचांगc = 0x0;  /* Dynamic */
	w100_pwr_state.sclk_cntl.f.sclk_क्रमce_cp = 0x0;     /* Dynamic */
	w100_pwr_state.sclk_cntl.f.sclk_क्रमce_e2 = 0x0;     /* Dynamic */
	w100_pwr_state.sclk_cntl.f.sclk_क्रमce_e3 = 0x0;     /* Dynamic */
	w100_pwr_state.sclk_cntl.f.sclk_क्रमce_idct = 0x0;   /* Dynamic */
	w100_pwr_state.sclk_cntl.f.sclk_क्रमce_bist = 0x0;   /* Dynamic */
	w100_pwr_state.sclk_cntl.f.busy_extend_cp = 0x0;
	w100_pwr_state.sclk_cntl.f.busy_extend_e2 = 0x0;
	w100_pwr_state.sclk_cntl.f.busy_extend_e3 = 0x0;
	w100_pwr_state.sclk_cntl.f.busy_extend_idct = 0x0;
	ग_लिखोl((u32) (w100_pwr_state.sclk_cntl.val), remapped_regs + mmSCLK_CNTL);

	w100_pwr_state.pclk_cntl.f.pclk_src_sel = CLK_SRC_XTAL;
	w100_pwr_state.pclk_cntl.f.pclk_post_भाग = 0x1;    /* P = 2 */
	w100_pwr_state.pclk_cntl.f.pclk_क्रमce_disp = 0x0;  /* Dynamic */
	ग_लिखोl((u32) (w100_pwr_state.pclk_cntl.val), remapped_regs + mmPCLK_CNTL);

	w100_pwr_state.pll_ref_fb_भाग.f.pll_ref_भाग = 0x0;     /* M = 1 */
	w100_pwr_state.pll_ref_fb_भाग.f.pll_fb_भाग_पूर्णांक = 0x0;  /* N = 1.0 */
	w100_pwr_state.pll_ref_fb_भाग.f.pll_fb_भाग_frac = 0x0;
	w100_pwr_state.pll_ref_fb_भाग.f.pll_reset_समय = 0x5;
	w100_pwr_state.pll_ref_fb_भाग.f.pll_lock_समय = 0xff;
	ग_लिखोl((u32) (w100_pwr_state.pll_ref_fb_भाग.val), remapped_regs + mmPLL_REF_FB_DIV);

	w100_pwr_state.pll_cntl.f.pll_pwdn = 0x1;
	w100_pwr_state.pll_cntl.f.pll_reset = 0x1;
	w100_pwr_state.pll_cntl.f.pll_pm_en = 0x0;
	w100_pwr_state.pll_cntl.f.pll_mode = 0x0;  /* uses VCO घड़ी */
	w100_pwr_state.pll_cntl.f.pll_refclk_sel = 0x0;
	w100_pwr_state.pll_cntl.f.pll_fbclk_sel = 0x0;
	w100_pwr_state.pll_cntl.f.pll_tcpoff = 0x0;
	w100_pwr_state.pll_cntl.f.pll_pcp = 0x4;
	w100_pwr_state.pll_cntl.f.pll_pvg = 0x0;
	w100_pwr_state.pll_cntl.f.pll_vcofr = 0x0;
	w100_pwr_state.pll_cntl.f.pll_ioffset = 0x0;
	w100_pwr_state.pll_cntl.f.pll_pecc_mode = 0x0;
	w100_pwr_state.pll_cntl.f.pll_pecc_scon = 0x0;
	w100_pwr_state.pll_cntl.f.pll_dactal = 0x0;  /* Hi-Z */
	w100_pwr_state.pll_cntl.f.pll_cp_clip = 0x3;
	w100_pwr_state.pll_cntl.f.pll_conf = 0x2;
	w100_pwr_state.pll_cntl.f.pll_mbctrl = 0x2;
	w100_pwr_state.pll_cntl.f.pll_ring_off = 0x0;
	ग_लिखोl((u32) (w100_pwr_state.pll_cntl.val), remapped_regs + mmPLL_CNTL);

	w100_pwr_state.pwrmgt_cntl.f.pwm_enable = 0x0;
	w100_pwr_state.pwrmgt_cntl.f.pwm_mode_req = 0x1;  /* normal mode (0, 1, 3) */
	w100_pwr_state.pwrmgt_cntl.f.pwm_wakeup_cond = 0x0;
	w100_pwr_state.pwrmgt_cntl.f.pwm_fast_noml_hw_en = 0x0;
	w100_pwr_state.pwrmgt_cntl.f.pwm_noml_fast_hw_en = 0x0;
	w100_pwr_state.pwrmgt_cntl.f.pwm_fast_noml_cond = 0x1;  /* PM4,ENG */
	w100_pwr_state.pwrmgt_cntl.f.pwm_noml_fast_cond = 0x1;  /* PM4,ENG */
	w100_pwr_state.pwrmgt_cntl.f.pwm_idle_समयr = 0xFF;
	w100_pwr_state.pwrmgt_cntl.f.pwm_busy_समयr = 0xFF;
	ग_लिखोl((u32) (w100_pwr_state.pwrmgt_cntl.val), remapped_regs + mmPWRMGT_CNTL);

	w100_pwr_state.स्वतः_mode = 0;  /* manual mode */
पूर्ण


/*
 * Setup the w100 घड़ीs क्रम the specअगरied mode
 */
अटल व्योम w100_init_घड़ीs(काष्ठा w100fb_par *par)
अणु
	काष्ठा w100_mode *mode = par->mode;

	अगर (mode->pixclk_src == CLK_SRC_PLL || mode->sysclk_src == CLK_SRC_PLL)
		w100_set_pll_freq(par, (par->fastpll_mode && mode->fast_pll_freq) ? mode->fast_pll_freq : mode->pll_freq);

	w100_pwr_state.sclk_cntl.f.sclk_src_sel = mode->sysclk_src;
	w100_pwr_state.sclk_cntl.f.sclk_post_भाग_fast = mode->sysclk_भागider;
	w100_pwr_state.sclk_cntl.f.sclk_post_भाग_slow = mode->sysclk_भागider;
	ग_लिखोl((u32) (w100_pwr_state.sclk_cntl.val), remapped_regs + mmSCLK_CNTL);
पूर्ण

अटल व्योम w100_init_lcd(काष्ठा w100fb_par *par)
अणु
	u32 temp32;
	काष्ठा w100_mode *mode = par->mode;
	काष्ठा w100_gen_regs *regs = par->mach->regs;
	जोड़ active_h_disp_u active_h_disp;
	जोड़ active_v_disp_u active_v_disp;
	जोड़ graphic_h_disp_u graphic_h_disp;
	जोड़ graphic_v_disp_u graphic_v_disp;
	जोड़ crtc_total_u crtc_total;

	/* w3200 करोesn't like undefined bits being set so zero रेजिस्टर values first */

	active_h_disp.val = 0;
	active_h_disp.f.active_h_start=mode->left_margin;
	active_h_disp.f.active_h_end=mode->left_margin + mode->xres;
	ग_लिखोl(active_h_disp.val, remapped_regs + mmACTIVE_H_DISP);

	active_v_disp.val = 0;
	active_v_disp.f.active_v_start=mode->upper_margin;
	active_v_disp.f.active_v_end=mode->upper_margin + mode->yres;
	ग_लिखोl(active_v_disp.val, remapped_regs + mmACTIVE_V_DISP);

	graphic_h_disp.val = 0;
	graphic_h_disp.f.graphic_h_start=mode->left_margin;
	graphic_h_disp.f.graphic_h_end=mode->left_margin + mode->xres;
	ग_लिखोl(graphic_h_disp.val, remapped_regs + mmGRAPHIC_H_DISP);

	graphic_v_disp.val = 0;
	graphic_v_disp.f.graphic_v_start=mode->upper_margin;
	graphic_v_disp.f.graphic_v_end=mode->upper_margin + mode->yres;
	ग_लिखोl(graphic_v_disp.val, remapped_regs + mmGRAPHIC_V_DISP);

	crtc_total.val = 0;
	crtc_total.f.crtc_h_total=mode->left_margin  + mode->xres + mode->right_margin;
	crtc_total.f.crtc_v_total=mode->upper_margin + mode->yres + mode->lower_margin;
	ग_लिखोl(crtc_total.val, remapped_regs + mmCRTC_TOTAL);

	ग_लिखोl(mode->crtc_ss, remapped_regs + mmCRTC_SS);
	ग_लिखोl(mode->crtc_ls, remapped_regs + mmCRTC_LS);
	ग_लिखोl(mode->crtc_gs, remapped_regs + mmCRTC_GS);
	ग_लिखोl(mode->crtc_vpos_gs, remapped_regs + mmCRTC_VPOS_GS);
	ग_लिखोl(mode->crtc_rev, remapped_regs + mmCRTC_REV);
	ग_लिखोl(mode->crtc_dclk, remapped_regs + mmCRTC_DCLK);
	ग_लिखोl(mode->crtc_gclk, remapped_regs + mmCRTC_GCLK);
	ग_लिखोl(mode->crtc_goe, remapped_regs + mmCRTC_GOE);
	ग_लिखोl(mode->crtc_ps1_active, remapped_regs + mmCRTC_PS1_ACTIVE);

	ग_लिखोl(regs->lcd_क्रमmat, remapped_regs + mmLCD_FORMAT);
	ग_लिखोl(regs->lcdd_cntl1, remapped_regs + mmLCDD_CNTL1);
	ग_लिखोl(regs->lcdd_cntl2, remapped_regs + mmLCDD_CNTL2);
	ग_लिखोl(regs->genlcd_cntl1, remapped_regs + mmGENLCD_CNTL1);
	ग_लिखोl(regs->genlcd_cntl2, remapped_regs + mmGENLCD_CNTL2);
	ग_लिखोl(regs->genlcd_cntl3, remapped_regs + mmGENLCD_CNTL3);

	ग_लिखोl(0x00000000, remapped_regs + mmCRTC_FRAME);
	ग_लिखोl(0x00000000, remapped_regs + mmCRTC_FRAME_VPOS);
	ग_लिखोl(0x00000000, remapped_regs + mmCRTC_DEFAULT_COUNT);
	ग_लिखोl(0x0000FF00, remapped_regs + mmLCD_BACKGROUND_COLOR);

	/* Hack क्रम overlay in ext memory */
	temp32 = पढ़ोl(remapped_regs + mmDISP_DEBUG2);
	temp32 |= 0xc0000000;
	ग_लिखोl(temp32, remapped_regs + mmDISP_DEBUG2);
पूर्ण


अटल व्योम w100_setup_memory(काष्ठा w100fb_par *par)
अणु
	जोड़ mc_ext_mem_location_u exपंचांगem_location;
	जोड़ mc_fb_location_u पूर्णांकmem_location;
	काष्ठा w100_mem_info *mem = par->mach->mem;
	काष्ठा w100_bm_mem_info *bm_mem = par->mach->bm_mem;

	अगर (!par->exपंचांगem_active) अणु
		w100_suspend(W100_SUSPEND_EXTMEM);

		/* Map Internal Memory at FB Base */
		पूर्णांकmem_location.f.mc_fb_start = W100_FB_BASE >> 8;
		पूर्णांकmem_location.f.mc_fb_top = (W100_FB_BASE+MEM_INT_SIZE) >> 8;
		ग_लिखोl((u32) (पूर्णांकmem_location.val), remapped_regs + mmMC_FB_LOCATION);

		/* Unmap External Memory - value is *probably* irrelevant but may have meaning
		   to acceleration libraries */
		exपंचांगem_location.f.mc_ext_mem_start = MEM_EXT_BASE_VALUE >> 8;
		exपंचांगem_location.f.mc_ext_mem_top = (MEM_EXT_BASE_VALUE-1) >> 8;
		ग_लिखोl((u32) (exपंचांगem_location.val), remapped_regs + mmMC_EXT_MEM_LOCATION);
	पूर्ण अन्यथा अणु
		/* Map Internal Memory to its शेष location */
		पूर्णांकmem_location.f.mc_fb_start = MEM_INT_BASE_VALUE >> 8;
		पूर्णांकmem_location.f.mc_fb_top = (MEM_INT_BASE_VALUE+MEM_INT_SIZE) >> 8;
		ग_लिखोl((u32) (पूर्णांकmem_location.val), remapped_regs + mmMC_FB_LOCATION);

		/* Map External Memory at FB Base */
		exपंचांगem_location.f.mc_ext_mem_start = W100_FB_BASE >> 8;
		exपंचांगem_location.f.mc_ext_mem_top = (W100_FB_BASE+par->mach->mem->size) >> 8;
		ग_लिखोl((u32) (exपंचांगem_location.val), remapped_regs + mmMC_EXT_MEM_LOCATION);

		ग_लिखोl(0x00007800, remapped_regs + mmMC_BIST_CTRL);
		ग_लिखोl(mem->ext_cntl, remapped_regs + mmMEM_EXT_CNTL);
		ग_लिखोl(0x00200021, remapped_regs + mmMEM_SDRAM_MODE_REG);
		udelay(100);
		ग_लिखोl(0x80200021, remapped_regs + mmMEM_SDRAM_MODE_REG);
		udelay(100);
		ग_लिखोl(mem->sdram_mode_reg, remapped_regs + mmMEM_SDRAM_MODE_REG);
		udelay(100);
		ग_लिखोl(mem->ext_timing_cntl, remapped_regs + mmMEM_EXT_TIMING_CNTL);
		ग_लिखोl(mem->io_cntl, remapped_regs + mmMEM_IO_CNTL);
		अगर (bm_mem) अणु
			ग_लिखोl(bm_mem->ext_mem_bw, remapped_regs + mmBM_EXT_MEM_BANDWIDTH);
			ग_लिखोl(bm_mem->offset, remapped_regs + mmBM_OFFSET);
			ग_लिखोl(bm_mem->ext_timing_ctl, remapped_regs + mmBM_MEM_EXT_TIMING_CNTL);
			ग_लिखोl(bm_mem->ext_cntl, remapped_regs + mmBM_MEM_EXT_CNTL);
			ग_लिखोl(bm_mem->mode_reg, remapped_regs + mmBM_MEM_MODE_REG);
			ग_लिखोl(bm_mem->io_cntl, remapped_regs + mmBM_MEM_IO_CNTL);
			ग_लिखोl(bm_mem->config, remapped_regs + mmBM_CONFIG);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम w100_set_dispregs(काष्ठा w100fb_par *par)
अणु
	अचिन्हित दीर्घ rot=0, भागider, offset=0;
	जोड़ graphic_ctrl_u graphic_ctrl;

	/* See अगर the mode has been rotated */
	अगर (par->xres == par->mode->xres) अणु
		अगर (par->flip) अणु
			rot=3; /* 180 degree */
			offset=(par->xres * par->yres) - 1;
		पूर्ण /* अन्यथा 0 degree */
		भागider = par->mode->pixclk_भागider;
	पूर्ण अन्यथा अणु
		अगर (par->flip) अणु
			rot=2; /* 270 degree */
			offset=par->xres - 1;
		पूर्ण अन्यथा अणु
			rot=1; /* 90 degree */
			offset=par->xres * (par->yres - 1);
		पूर्ण
		भागider = par->mode->pixclk_भागider_rotated;
	पूर्ण

	graphic_ctrl.val = 0; /* w32xx करोesn't like undefined bits */
	चयन (par->chip_id) अणु
		हाल CHIP_ID_W100:
			graphic_ctrl.f_w100.color_depth=6;
			graphic_ctrl.f_w100.en_crtc=1;
			graphic_ctrl.f_w100.en_graphic_req=1;
			graphic_ctrl.f_w100.en_graphic_crtc=1;
			graphic_ctrl.f_w100.lcd_pclk_on=1;
			graphic_ctrl.f_w100.lcd_sclk_on=1;
			graphic_ctrl.f_w100.low_घातer_on=0;
			graphic_ctrl.f_w100.req_freq=0;
			graphic_ctrl.f_w100.portrait_mode=rot;

			/* Zaurus needs this */
			चयन(par->xres) अणु
				हाल 240:
				हाल 320:
				शेष:
					graphic_ctrl.f_w100.total_req_graphic=0xa0;
					अवरोध;
				हाल 480:
				हाल 640:
					चयन(rot) अणु
						हाल 0:  /* 0 */
						हाल 3:  /* 180 */
							graphic_ctrl.f_w100.low_घातer_on=1;
							graphic_ctrl.f_w100.req_freq=5;
						अवरोध;
						हाल 1:  /* 90 */
						हाल 2:  /* 270 */
							graphic_ctrl.f_w100.req_freq=4;
							अवरोध;
						शेष:
							अवरोध;
					पूर्ण
					graphic_ctrl.f_w100.total_req_graphic=0xf0;
					अवरोध;
			पूर्ण
			अवरोध;
		हाल CHIP_ID_W3200:
		हाल CHIP_ID_W3220:
			graphic_ctrl.f_w32xx.color_depth=6;
			graphic_ctrl.f_w32xx.en_crtc=1;
			graphic_ctrl.f_w32xx.en_graphic_req=1;
			graphic_ctrl.f_w32xx.en_graphic_crtc=1;
			graphic_ctrl.f_w32xx.lcd_pclk_on=1;
			graphic_ctrl.f_w32xx.lcd_sclk_on=1;
			graphic_ctrl.f_w32xx.low_घातer_on=0;
			graphic_ctrl.f_w32xx.req_freq=0;
			graphic_ctrl.f_w32xx.total_req_graphic=par->mode->xres >> 1; /* panel xres, not mode */
			graphic_ctrl.f_w32xx.portrait_mode=rot;
			अवरोध;
	पूर्ण

	/* Set the pixel घड़ी source and भागider */
	w100_pwr_state.pclk_cntl.f.pclk_src_sel = par->mode->pixclk_src;
	w100_pwr_state.pclk_cntl.f.pclk_post_भाग = भागider;
	ग_लिखोl((u32) (w100_pwr_state.pclk_cntl.val), remapped_regs + mmPCLK_CNTL);

	ग_लिखोl(graphic_ctrl.val, remapped_regs + mmGRAPHIC_CTRL);
	ग_लिखोl(W100_FB_BASE + ((offset * BITS_PER_PIXEL/8)&~0x03UL), remapped_regs + mmGRAPHIC_OFFSET);
	ग_लिखोl((par->xres*BITS_PER_PIXEL/8), remapped_regs + mmGRAPHIC_PITCH);
पूर्ण


/*
 * Work out how दीर्घ the sync pulse lasts
 * Value is 1/(समय in seconds)
 */
अटल व्योम calc_hsync(काष्ठा w100fb_par *par)
अणु
	अचिन्हित दीर्घ hsync;
	काष्ठा w100_mode *mode = par->mode;
	जोड़ crtc_ss_u crtc_ss;

	अगर (mode->pixclk_src == CLK_SRC_XTAL)
		hsync=par->mach->xtal_freq;
	अन्यथा
		hsync=((par->fastpll_mode && mode->fast_pll_freq) ? mode->fast_pll_freq : mode->pll_freq)*100000;

	hsync /= (w100_pwr_state.pclk_cntl.f.pclk_post_भाग + 1);

	crtc_ss.val = पढ़ोl(remapped_regs + mmCRTC_SS);
	अगर (crtc_ss.val)
		par->hsync_len = hsync / (crtc_ss.f.ss_end-crtc_ss.f.ss_start);
	अन्यथा
		par->hsync_len = 0;
पूर्ण

अटल व्योम w100_suspend(u32 mode)
अणु
	u32 val;

	ग_लिखोl(0x7FFF8000, remapped_regs + mmMC_EXT_MEM_LOCATION);
	ग_लिखोl(0x00FF0000, remapped_regs + mmMC_PERF_MON_CNTL);

	val = पढ़ोl(remapped_regs + mmMEM_EXT_TIMING_CNTL);
	val &= ~(0x00100000);  /* bit20=0 */
	val |= 0xFF000000;     /* bit31:24=0xff */
	ग_लिखोl(val, remapped_regs + mmMEM_EXT_TIMING_CNTL);

	val = पढ़ोl(remapped_regs + mmMEM_EXT_CNTL);
	val &= ~(0x00040000);  /* bit18=0 */
	val |= 0x00080000;     /* bit19=1 */
	ग_लिखोl(val, remapped_regs + mmMEM_EXT_CNTL);

	udelay(1);  /* रुको 1us */

	अगर (mode == W100_SUSPEND_EXTMEM) अणु
		/* CKE: Tri-State */
		val = पढ़ोl(remapped_regs + mmMEM_EXT_CNTL);
		val |= 0x40000000;  /* bit30=1 */
		ग_लिखोl(val, remapped_regs + mmMEM_EXT_CNTL);

		/* CLK: Stop */
		val = पढ़ोl(remapped_regs + mmMEM_EXT_CNTL);
		val &= ~(0x00000001);  /* bit0=0 */
		ग_लिखोl(val, remapped_regs + mmMEM_EXT_CNTL);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0x00000000, remapped_regs + mmSCLK_CNTL);
		ग_लिखोl(0x000000BF, remapped_regs + mmCLK_PIN_CNTL);
		ग_लिखोl(0x00000015, remapped_regs + mmPWRMGT_CNTL);

		udelay(5);

		val = पढ़ोl(remapped_regs + mmPLL_CNTL);
		val |= 0x00000004;  /* bit2=1 */
		ग_लिखोl(val, remapped_regs + mmPLL_CNTL);

		ग_लिखोl(0x00000000, remapped_regs + mmLCDD_CNTL1);
		ग_लिखोl(0x00000000, remapped_regs + mmLCDD_CNTL2);
		ग_लिखोl(0x00000000, remapped_regs + mmGENLCD_CNTL1);
		ग_लिखोl(0x00000000, remapped_regs + mmGENLCD_CNTL2);
		ग_लिखोl(0x00000000, remapped_regs + mmGENLCD_CNTL3);

		val = पढ़ोl(remapped_regs + mmMEM_EXT_CNTL);
		val |= 0xF0000000;
		val &= ~(0x00000001);
		ग_लिखोl(val, remapped_regs + mmMEM_EXT_CNTL);

		ग_लिखोl(0x0000001d, remapped_regs + mmPWRMGT_CNTL);
	पूर्ण
पूर्ण

अटल व्योम w100_vsync(व्योम)
अणु
	u32 पंचांगp;
	पूर्णांक समयout = 30000;  /* VSync समयout = 30[ms] > 16.8[ms] */

	पंचांगp = पढ़ोl(remapped_regs + mmACTIVE_V_DISP);

	/* set vline pos  */
	ग_लिखोl((पंचांगp >> 16) & 0x3ff, remapped_regs + mmDISP_INT_CNTL);

	/* disable vline irq */
	पंचांगp = पढ़ोl(remapped_regs + mmGEN_INT_CNTL);

	पंचांगp &= ~0x00000002;
	ग_लिखोl(पंचांगp, remapped_regs + mmGEN_INT_CNTL);

	/* clear vline irq status */
	ग_लिखोl(0x00000002, remapped_regs + mmGEN_INT_STATUS);

	/* enable vline irq */
	ग_लिखोl((पंचांगp | 0x00000002), remapped_regs + mmGEN_INT_CNTL);

	/* clear vline irq status */
	ग_लिखोl(0x00000002, remapped_regs + mmGEN_INT_STATUS);

	जबतक(समयout > 0) अणु
		अगर (पढ़ोl(remapped_regs + mmGEN_INT_STATUS) & 0x00000002)
			अवरोध;
		udelay(1);
		समयout--;
	पूर्ण

	/* disable vline irq */
	ग_लिखोl(पंचांगp, remapped_regs + mmGEN_INT_CNTL);

	/* clear vline irq status */
	ग_लिखोl(0x00000002, remapped_regs + mmGEN_INT_STATUS);
पूर्ण

अटल काष्ठा platक्रमm_driver w100fb_driver = अणु
	.probe		= w100fb_probe,
	.हटाओ		= w100fb_हटाओ,
	.suspend	= w100fb_suspend,
	.resume		= w100fb_resume,
	.driver		= अणु
		.name	= "w100fb",
		.dev_groups	= w100fb_groups,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(w100fb_driver);

MODULE_DESCRIPTION("ATI Imageon w100 framebuffer driver");
MODULE_LICENSE("GPL");
