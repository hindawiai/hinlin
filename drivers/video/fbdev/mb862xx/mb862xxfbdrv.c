<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/mb862xx/mb862xxfb.c
 *
 * Fujitsu Carmine/Coral-P(A)/Lime framebuffer driver
 *
 * (C) 2008 Anम_से_दij Gustschin <agust@denx.de>
 * DENX Software Engineering
 */

#अघोषित DEBUG

#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#अगर defined(CONFIG_OF)
#समावेश <linux/of_platक्रमm.h>
#पूर्ण_अगर
#समावेश "mb862xxfb.h"
#समावेश "mb862xx_reg.h"

#घोषणा NR_PALETTE		256
#घोषणा MB862XX_MEM_SIZE	0x1000000
#घोषणा CORALP_MEM_SIZE		0x2000000
#घोषणा CARMINE_MEM_SIZE	0x8000000
#घोषणा DRV_NAME		"mb862xxfb"

#अगर defined(CONFIG_SOCRATES)
अटल काष्ठा mb862xx_gc_mode socrates_gc_mode = अणु
	/* Mode क्रम Prime View PM070WL4 TFT LCD Panel */
	अणु "800x480", 45, 800, 480, 40000, 86, 42, 33, 10, 128, 2, 0, 0, 0 पूर्ण,
	/* 16 bits/pixel, 16MB, 133MHz, SDRAM memory mode value */
	16, 0x1000000, GC_CCF_COT_133, 0x4157ba63
पूर्ण;
#पूर्ण_अगर

/* Helpers */
अटल अंतरभूत पूर्णांक h_total(काष्ठा fb_var_screeninfo *var)
अणु
	वापस var->xres + var->left_margin +
		var->right_margin + var->hsync_len;
पूर्ण

अटल अंतरभूत पूर्णांक v_total(काष्ठा fb_var_screeninfo *var)
अणु
	वापस var->yres + var->upper_margin +
		var->lower_margin + var->vsync_len;
पूर्ण

अटल अंतरभूत पूर्णांक hsp(काष्ठा fb_var_screeninfo *var)
अणु
	वापस var->xres + var->right_margin - 1;
पूर्ण

अटल अंतरभूत पूर्णांक vsp(काष्ठा fb_var_screeninfo *var)
अणु
	वापस var->yres + var->lower_margin - 1;
पूर्ण

अटल अंतरभूत पूर्णांक d_pitch(काष्ठा fb_var_screeninfo *var)
अणु
	वापस var->xres * var->bits_per_pixel / 8;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक chan_to_field(अचिन्हित पूर्णांक chan,
					 काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक mb862xxfb_setcolreg(अचिन्हित regno,
			       अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			       अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा mb862xxfb_par *par = info->par;
	अचिन्हित पूर्णांक val;

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		अगर (regno < 16) अणु
			val  = chan_to_field(red,   &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue,  &info->var.blue);
			par->pseuकरो_palette[regno] = val;
		पूर्ण
		अवरोध;
	हाल FB_VISUAL_PSEUDOCOLOR:
		अगर (regno < 256) अणु
			val = (red >> 8) << 16;
			val |= (green >> 8) << 8;
			val |= blue >> 8;
			outreg(disp, GC_L0PAL0 + (regno * 4), val);
		पूर्ण
		अवरोध;
	शेष:
		वापस 1;   /* unsupported type */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mb862xxfb_check_var(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *fbi)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर (fbi->dev)
		dev_dbg(fbi->dev, "%s\n", __func__);

	/* check अगर these values fit पूर्णांकo the रेजिस्टरs */
	अगर (var->hsync_len > 255 || var->vsync_len > 255)
		वापस -EINVAL;

	अगर ((var->xres + var->right_margin) >= 4096)
		वापस -EINVAL;

	अगर ((var->yres + var->lower_margin) > 4096)
		वापस -EINVAL;

	अगर (h_total(var) > 4096 || v_total(var) > 4096)
		वापस -EINVAL;

	अगर (var->xres_भव > 4096 || var->yres_भव > 4096)
		वापस -EINVAL;

	अगर (var->bits_per_pixel <= 8)
		var->bits_per_pixel = 8;
	अन्यथा अगर (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	अन्यथा अगर (var->bits_per_pixel <= 32)
		var->bits_per_pixel = 32;

	/*
	 * can cope with 8,16 or 24/32bpp अगर resulting
	 * pitch is भागisible by 64 without reमुख्यder
	 */
	अगर (d_pitch(&fbi->var) % GC_L0M_L0W_UNIT) अणु
		पूर्णांक r;

		var->bits_per_pixel = 0;
		करो अणु
			var->bits_per_pixel += 8;
			r = d_pitch(&fbi->var) % GC_L0M_L0W_UNIT;
		पूर्ण जबतक (r && var->bits_per_pixel <= 32);

		अगर (d_pitch(&fbi->var) % GC_L0M_L0W_UNIT)
			वापस -EINVAL;
	पूर्ण

	/* line length is going to be 128 bit aligned */
	पंचांगp = (var->xres * var->bits_per_pixel) / 8;
	अगर ((पंचांगp & 15) != 0)
		वापस -EINVAL;

	/* set r/g/b positions and validate bpp */
	चयन (var->bits_per_pixel) अणु
	हाल 8:
		var->red.length		= var->bits_per_pixel;
		var->green.length	= var->bits_per_pixel;
		var->blue.length	= var->bits_per_pixel;
		var->red.offset		= 0;
		var->green.offset	= 0;
		var->blue.offset	= 0;
		var->transp.length	= 0;
		अवरोध;
	हाल 16:
		var->red.length		= 5;
		var->green.length	= 5;
		var->blue.length	= 5;
		var->red.offset		= 10;
		var->green.offset	= 5;
		var->blue.offset	= 0;
		var->transp.length	= 0;
		अवरोध;
	हाल 24:
	हाल 32:
		var->transp.length	= 8;
		var->red.length		= 8;
		var->green.length	= 8;
		var->blue.length	= 8;
		var->transp.offset	= 24;
		var->red.offset		= 16;
		var->green.offset	= 8;
		var->blue.offset	= 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा fb_ops mb862xxfb_ops;

/*
 * set display parameters
 */
अटल पूर्णांक mb862xxfb_set_par(काष्ठा fb_info *fbi)
अणु
	काष्ठा mb862xxfb_par *par = fbi->par;
	अचिन्हित दीर्घ reg, sc;

	dev_dbg(par->dev, "%s\n", __func__);
	अगर (par->type == BT_CORALP)
		mb862xxfb_init_accel(fbi, &mb862xxfb_ops, fbi->var.xres);

	अगर (par->pre_init)
		वापस 0;

	/* disp off */
	reg = inreg(disp, GC_DCM1);
	reg &= ~GC_DCM01_DEN;
	outreg(disp, GC_DCM1, reg);

	/* set display reference घड़ी भाग. */
	sc = par->refclk / (1000000 / fbi->var.pixघड़ी) - 1;
	reg = inreg(disp, GC_DCM1);
	reg &= ~(GC_DCM01_CKS | GC_DCM01_RESV | GC_DCM01_SC);
	reg |= sc << 8;
	outreg(disp, GC_DCM1, reg);
	dev_dbg(par->dev, "SC 0x%lx\n", sc);

	/* disp dimension, क्रमmat */
	reg =  pack(d_pitch(&fbi->var) / GC_L0M_L0W_UNIT,
		    (fbi->var.yres - 1));
	अगर (fbi->var.bits_per_pixel == 16)
		reg |= GC_L0M_L0C_16;
	outreg(disp, GC_L0M, reg);

	अगर (fbi->var.bits_per_pixel == 32) अणु
		reg = inreg(disp, GC_L0EM);
		outreg(disp, GC_L0EM, reg | GC_L0EM_L0EC_24);
	पूर्ण
	outreg(disp, GC_WY_WX, 0);
	reg = pack(fbi->var.yres - 1, fbi->var.xres);
	outreg(disp, GC_WH_WW, reg);
	outreg(disp, GC_L0OA0, 0);
	outreg(disp, GC_L0DA0, 0);
	outreg(disp, GC_L0DY_L0DX, 0);
	outreg(disp, GC_L0WY_L0WX, 0);
	outreg(disp, GC_L0WH_L0WW, reg);

	/* both HW-cursors off */
	reg = inreg(disp, GC_CPM_CUTC);
	reg &= ~(GC_CPM_CEN0 | GC_CPM_CEN1);
	outreg(disp, GC_CPM_CUTC, reg);

	/* timings */
	reg = pack(fbi->var.xres - 1, fbi->var.xres - 1);
	outreg(disp, GC_HDB_HDP, reg);
	reg = pack((fbi->var.yres - 1), vsp(&fbi->var));
	outreg(disp, GC_VDP_VSP, reg);
	reg = ((fbi->var.vsync_len - 1) << 24) |
	      pack((fbi->var.hsync_len - 1), hsp(&fbi->var));
	outreg(disp, GC_VSW_HSW_HSP, reg);
	outreg(disp, GC_HTP, pack(h_total(&fbi->var) - 1, 0));
	outreg(disp, GC_VTR, pack(v_total(&fbi->var) - 1, 0));

	/* display on */
	reg = inreg(disp, GC_DCM1);
	reg |= GC_DCM01_DEN | GC_DCM01_L0E;
	reg &= ~GC_DCM01_ESY;
	outreg(disp, GC_DCM1, reg);
	वापस 0;
पूर्ण

अटल पूर्णांक mb862xxfb_pan(काष्ठा fb_var_screeninfo *var,
			 काष्ठा fb_info *info)
अणु
	काष्ठा mb862xxfb_par *par = info->par;
	अचिन्हित दीर्घ reg;

	reg = pack(var->yoffset, var->xoffset);
	outreg(disp, GC_L0WY_L0WX, reg);

	reg = pack(info->var.yres_भव, info->var.xres_भव);
	outreg(disp, GC_L0WH_L0WW, reg);
	वापस 0;
पूर्ण

अटल पूर्णांक mb862xxfb_blank(पूर्णांक mode, काष्ठा fb_info *fbi)
अणु
	काष्ठा mb862xxfb_par  *par = fbi->par;
	अचिन्हित दीर्घ reg;

	dev_dbg(fbi->dev, "blank mode=%d\n", mode);

	चयन (mode) अणु
	हाल FB_BLANK_POWERDOWN:
		reg = inreg(disp, GC_DCM1);
		reg &= ~GC_DCM01_DEN;
		outreg(disp, GC_DCM1, reg);
		अवरोध;
	हाल FB_BLANK_UNBLANK:
		reg = inreg(disp, GC_DCM1);
		reg |= GC_DCM01_DEN;
		outreg(disp, GC_DCM1, reg);
		अवरोध;
	हाल FB_BLANK_NORMAL:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	शेष:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mb862xxfb_ioctl(काष्ठा fb_info *fbi, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	काष्ठा mb862xxfb_par *par = fbi->par;
	काष्ठा mb862xx_l1_cfg *l1_cfg = &par->l1_cfg;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक *enable;
	u32 l1em = 0;

	चयन (cmd) अणु
	हाल MB862XX_L1_GET_CFG:
		अगर (copy_to_user(argp, l1_cfg, माप(*l1_cfg)))
			वापस -EFAULT;
		अवरोध;
	हाल MB862XX_L1_SET_CFG:
		अगर (copy_from_user(l1_cfg, argp, माप(*l1_cfg)))
			वापस -EFAULT;
		अगर (l1_cfg->dh == 0 || l1_cfg->dw == 0)
			वापस -EINVAL;
		अगर ((l1_cfg->sw >= l1_cfg->dw) && (l1_cfg->sh >= l1_cfg->dh)) अणु
			/* करोwnscaling */
			outreg(cap, GC_CAP_CSC,
				pack((l1_cfg->sh << 11) / l1_cfg->dh,
				     (l1_cfg->sw << 11) / l1_cfg->dw));
			l1em = inreg(disp, GC_L1EM);
			l1em &= ~GC_L1EM_DM;
		पूर्ण अन्यथा अगर ((l1_cfg->sw <= l1_cfg->dw) &&
			   (l1_cfg->sh <= l1_cfg->dh)) अणु
			/* upscaling */
			outreg(cap, GC_CAP_CSC,
				pack((l1_cfg->sh << 11) / l1_cfg->dh,
				     (l1_cfg->sw << 11) / l1_cfg->dw));
			outreg(cap, GC_CAP_CMSS,
				pack(l1_cfg->sw >> 1, l1_cfg->sh));
			outreg(cap, GC_CAP_CMDS,
				pack(l1_cfg->dw >> 1, l1_cfg->dh));
			l1em = inreg(disp, GC_L1EM);
			l1em |= GC_L1EM_DM;
		पूर्ण

		अगर (l1_cfg->mirror) अणु
			outreg(cap, GC_CAP_CBM,
				inreg(cap, GC_CAP_CBM) | GC_CBM_HRV);
			l1em |= l1_cfg->dw * 2 - 8;
		पूर्ण अन्यथा अणु
			outreg(cap, GC_CAP_CBM,
				inreg(cap, GC_CAP_CBM) & ~GC_CBM_HRV);
			l1em &= 0xffff0000;
		पूर्ण
		outreg(disp, GC_L1EM, l1em);
		अवरोध;
	हाल MB862XX_L1_ENABLE:
		enable = (पूर्णांक *)arg;
		अगर (*enable) अणु
			outreg(disp, GC_L1DA, par->cap_buf);
			outreg(cap, GC_CAP_IMG_START,
				pack(l1_cfg->sy >> 1, l1_cfg->sx));
			outreg(cap, GC_CAP_IMG_END,
				pack(l1_cfg->sh, l1_cfg->sw));
			outreg(disp, GC_L1M, GC_L1M_16 | GC_L1M_YC | GC_L1M_CS |
					     (par->l1_stride << 16));
			outreg(disp, GC_L1WY_L1WX,
				pack(l1_cfg->dy, l1_cfg->dx));
			outreg(disp, GC_L1WH_L1WW,
				pack(l1_cfg->dh - 1, l1_cfg->dw));
			outreg(disp, GC_DLS, 1);
			outreg(cap, GC_CAP_VCM,
				GC_VCM_VIE | GC_VCM_CM | GC_VCM_VS_PAL);
			outreg(disp, GC_DCM1, inreg(disp, GC_DCM1) |
					      GC_DCM1_DEN | GC_DCM1_L1E);
		पूर्ण अन्यथा अणु
			outreg(cap, GC_CAP_VCM,
				inreg(cap, GC_CAP_VCM) & ~GC_VCM_VIE);
			outreg(disp, GC_DCM1,
				inreg(disp, GC_DCM1) & ~GC_DCM1_L1E);
		पूर्ण
		अवरोध;
	हाल MB862XX_L1_CAP_CTL:
		enable = (पूर्णांक *)arg;
		अगर (*enable) अणु
			outreg(cap, GC_CAP_VCM,
				inreg(cap, GC_CAP_VCM) | GC_VCM_VIE);
		पूर्ण अन्यथा अणु
			outreg(cap, GC_CAP_VCM,
				inreg(cap, GC_CAP_VCM) & ~GC_VCM_VIE);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* framebuffer ops */
अटल काष्ठा fb_ops mb862xxfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= mb862xxfb_check_var,
	.fb_set_par	= mb862xxfb_set_par,
	.fb_setcolreg	= mb862xxfb_setcolreg,
	.fb_blank	= mb862xxfb_blank,
	.fb_pan_display	= mb862xxfb_pan,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_ioctl	= mb862xxfb_ioctl,
पूर्ण;

/* initialize fb_info data */
अटल पूर्णांक mb862xxfb_init_fbinfo(काष्ठा fb_info *fbi)
अणु
	काष्ठा mb862xxfb_par *par = fbi->par;
	काष्ठा mb862xx_gc_mode *mode = par->gc_mode;
	अचिन्हित दीर्घ reg;
	पूर्णांक stride;

	fbi->fbops = &mb862xxfb_ops;
	fbi->pseuकरो_palette = par->pseuकरो_palette;
	fbi->screen_base = par->fb_base;
	fbi->screen_size = par->mapped_vram;

	म_नकल(fbi->fix.id, DRV_NAME);
	fbi->fix.smem_start = (अचिन्हित दीर्घ)par->fb_base_phys;
	fbi->fix.mmio_start = (अचिन्हित दीर्घ)par->mmio_base_phys;
	fbi->fix.mmio_len = par->mmio_len;
	fbi->fix.accel = FB_ACCEL_NONE;
	fbi->fix.type = FB_TYPE_PACKED_PIXELS;
	fbi->fix.type_aux = 0;
	fbi->fix.xpanstep = 1;
	fbi->fix.ypanstep = 1;
	fbi->fix.ywrapstep = 0;

	reg = inreg(disp, GC_DCM1);
	अगर (reg & GC_DCM01_DEN && reg & GC_DCM01_L0E) अणु
		/* get the disp mode from active display cfg */
		अचिन्हित दीर्घ sc = ((reg & GC_DCM01_SC) >> 8) + 1;
		अचिन्हित दीर्घ hsp, vsp, ht, vt;

		dev_dbg(par->dev, "using bootloader's disp. mode\n");
		fbi->var.pixघड़ी = (sc * 1000000) / par->refclk;
		fbi->var.xres = (inreg(disp, GC_HDB_HDP) & 0x0fff) + 1;
		reg = inreg(disp, GC_VDP_VSP);
		fbi->var.yres = ((reg >> 16) & 0x0fff) + 1;
		vsp = (reg & 0x0fff) + 1;
		fbi->var.xres_भव = fbi->var.xres;
		fbi->var.yres_भव = fbi->var.yres;
		reg = inreg(disp, GC_L0EM);
		अगर (reg & GC_L0EM_L0EC_24) अणु
			fbi->var.bits_per_pixel = 32;
		पूर्ण अन्यथा अणु
			reg = inreg(disp, GC_L0M);
			अगर (reg & GC_L0M_L0C_16)
				fbi->var.bits_per_pixel = 16;
			अन्यथा
				fbi->var.bits_per_pixel = 8;
		पूर्ण
		reg = inreg(disp, GC_VSW_HSW_HSP);
		fbi->var.hsync_len = ((reg & 0xff0000) >> 16) + 1;
		fbi->var.vsync_len = ((reg & 0x3f000000) >> 24) + 1;
		hsp = (reg & 0xffff) + 1;
		ht = ((inreg(disp, GC_HTP) & 0xfff0000) >> 16) + 1;
		fbi->var.right_margin = hsp - fbi->var.xres;
		fbi->var.left_margin = ht - hsp - fbi->var.hsync_len;
		vt = ((inreg(disp, GC_VTR) & 0xfff0000) >> 16) + 1;
		fbi->var.lower_margin = vsp - fbi->var.yres;
		fbi->var.upper_margin = vt - vsp - fbi->var.vsync_len;
	पूर्ण अन्यथा अगर (mode) अणु
		dev_dbg(par->dev, "using supplied mode\n");
		fb_videomode_to_var(&fbi->var, (काष्ठा fb_videomode *)mode);
		fbi->var.bits_per_pixel = mode->def_bpp ? mode->def_bpp : 8;
	पूर्ण अन्यथा अणु
		पूर्णांक ret;

		ret = fb_find_mode(&fbi->var, fbi, "640x480-16@60",
				   शून्य, 0, शून्य, 16);
		अगर (ret == 0 || ret == 4) अणु
			dev_err(par->dev,
				"failed to get initial mode\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	fbi->var.xoffset = 0;
	fbi->var.yoffset = 0;
	fbi->var.grayscale = 0;
	fbi->var.nonstd = 0;
	fbi->var.height = -1;
	fbi->var.width = -1;
	fbi->var.accel_flags = 0;
	fbi->var.vmode = FB_VMODE_NONINTERLACED;
	fbi->var.activate = FB_ACTIVATE_NOW;
	fbi->flags = FBINFO_DEFAULT |
#अगर_घोषित __BIG_ENDIAN
		     FBINFO_FOREIGN_ENDIAN |
#पूर्ण_अगर
		     FBINFO_HWACCEL_XPAN |
		     FBINFO_HWACCEL_YPAN;

	/* check and possibly fix bpp */
	अगर ((fbi->fbops->fb_check_var)(&fbi->var, fbi))
		dev_err(par->dev, "check_var() failed on initial setup?\n");

	fbi->fix.visual = fbi->var.bits_per_pixel == 8 ?
			 FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	fbi->fix.line_length = (fbi->var.xres_भव *
				fbi->var.bits_per_pixel) / 8;
	fbi->fix.smem_len = fbi->fix.line_length * fbi->var.yres_भव;

	/*
	 * reserve space क्रम capture buffers and two cursors
	 * at the end of vram: 720x576 * 2 * 2.2 + 64x64 * 16.
	 */
	par->cap_buf = par->mapped_vram - 0x1bd800 - 0x10000;
	par->cap_len = 0x1bd800;
	par->l1_cfg.sx = 0;
	par->l1_cfg.sy = 0;
	par->l1_cfg.sw = 720;
	par->l1_cfg.sh = 576;
	par->l1_cfg.dx = 0;
	par->l1_cfg.dy = 0;
	par->l1_cfg.dw = 720;
	par->l1_cfg.dh = 576;
	stride = par->l1_cfg.sw * (fbi->var.bits_per_pixel / 8);
	par->l1_stride = stride / 64 + ((stride % 64) ? 1 : 0);
	outreg(cap, GC_CAP_CBM, GC_CBM_OO | GC_CBM_CBST |
				(par->l1_stride << 16));
	outreg(cap, GC_CAP_CBOA, par->cap_buf);
	outreg(cap, GC_CAP_CBLA, par->cap_buf + par->cap_len);
	वापस 0;
पूर्ण

/*
 * show some display controller and cursor रेजिस्टरs
 */
अटल sमाप_प्रकार mb862xxfb_show_dispregs(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा mb862xxfb_par *par = fbi->par;
	अक्षर *ptr = buf;
	अचिन्हित पूर्णांक reg;

	क्रम (reg = GC_DCM0; reg <= GC_L0DY_L0DX; reg += 4)
		ptr += प्र_लिखो(ptr, "%08x = %08x\n",
			       reg, inreg(disp, reg));

	क्रम (reg = GC_CPM_CUTC; reg <= GC_CUY1_CUX1; reg += 4)
		ptr += प्र_लिखो(ptr, "%08x = %08x\n",
			       reg, inreg(disp, reg));

	क्रम (reg = GC_DCM1; reg <= GC_L0WH_L0WW; reg += 4)
		ptr += प्र_लिखो(ptr, "%08x = %08x\n",
			       reg, inreg(disp, reg));

	क्रम (reg = 0x400; reg <= 0x410; reg += 4)
		ptr += प्र_लिखो(ptr, "geo %08x = %08x\n",
			       reg, inreg(geo, reg));

	क्रम (reg = 0x400; reg <= 0x410; reg += 4)
		ptr += प्र_लिखो(ptr, "draw %08x = %08x\n",
			       reg, inreg(draw, reg));

	क्रम (reg = 0x440; reg <= 0x450; reg += 4)
		ptr += प्र_लिखो(ptr, "draw %08x = %08x\n",
			       reg, inreg(draw, reg));

	वापस ptr - buf;
पूर्ण

अटल DEVICE_ATTR(dispregs, 0444, mb862xxfb_show_dispregs, शून्य);

अटल irqवापस_t mb862xx_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mb862xxfb_par *par = (काष्ठा mb862xxfb_par *) dev_id;
	अचिन्हित दीर्घ reg_ist, mask;

	अगर (!par)
		वापस IRQ_NONE;

	अगर (par->type == BT_CARMINE) अणु
		/* Get Interrupt Status */
		reg_ist = inreg(ctrl, GC_CTRL_STATUS);
		mask = inreg(ctrl, GC_CTRL_INT_MASK);
		अगर (reg_ist == 0)
			वापस IRQ_HANDLED;

		reg_ist &= mask;
		अगर (reg_ist == 0)
			वापस IRQ_HANDLED;

		/* Clear पूर्णांकerrupt status */
		outreg(ctrl, 0x0, reg_ist);
	पूर्ण अन्यथा अणु
		/* Get status */
		reg_ist = inreg(host, GC_IST);
		mask = inreg(host, GC_IMASK);

		reg_ist &= mask;
		अगर (reg_ist == 0)
			वापस IRQ_HANDLED;

		/* Clear status */
		outreg(host, GC_IST, ~reg_ist);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

#अगर defined(CONFIG_FB_MB862XX_LIME)
/*
 * GDC (Lime, Coral(B/Q), Mपूर्णांक, ...) on host bus
 */
अटल पूर्णांक mb862xx_gdc_init(काष्ठा mb862xxfb_par *par)
अणु
	अचिन्हित दीर्घ ccf, mmr;
	अचिन्हित दीर्घ ver, rev;

	अगर (!par)
		वापस -ENODEV;

#अगर defined(CONFIG_FB_PRE_INIT_FB)
	par->pre_init = 1;
#पूर्ण_अगर
	par->host = par->mmio_base;
	par->i2c = par->mmio_base + MB862XX_I2C_BASE;
	par->disp = par->mmio_base + MB862XX_DISP_BASE;
	par->cap = par->mmio_base + MB862XX_CAP_BASE;
	par->draw = par->mmio_base + MB862XX_DRAW_BASE;
	par->geo = par->mmio_base + MB862XX_GEO_BASE;
	par->pio = par->mmio_base + MB862XX_PIO_BASE;

	par->refclk = GC_DISP_REFCLK_400;

	ver = inreg(host, GC_CID);
	rev = inreg(pio, GC_REVISION);
	अगर ((ver == 0x303) && (rev & 0xffffff00) == 0x20050100) अणु
		dev_info(par->dev, "Fujitsu Lime v1.%d found\n",
			 (पूर्णांक)rev & 0xff);
		par->type = BT_LIME;
		ccf = par->gc_mode ? par->gc_mode->ccf : GC_CCF_COT_100;
		mmr = par->gc_mode ? par->gc_mode->mmr : 0x414fb7f2;
	पूर्ण अन्यथा अणु
		dev_info(par->dev, "? GDC, CID/Rev.: 0x%lx/0x%lx \n", ver, rev);
		वापस -ENODEV;
	पूर्ण

	अगर (!par->pre_init) अणु
		outreg(host, GC_CCF, ccf);
		udelay(200);
		outreg(host, GC_MMR, mmr);
		udelay(10);
	पूर्ण

	/* पूर्णांकerrupt status */
	outreg(host, GC_IST, 0);
	outreg(host, GC_IMASK, GC_INT_EN);
	वापस 0;
पूर्ण

अटल पूर्णांक of_platक्रमm_mb862xx_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा mb862xxfb_par *par;
	काष्ठा fb_info *info;
	काष्ठा resource res;
	resource_माप_प्रकार res_size;
	अचिन्हित दीर्घ ret = -ENODEV;

	अगर (of_address_to_resource(np, 0, &res)) अणु
		dev_err(dev, "Invalid address\n");
		वापस -ENXIO;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा mb862xxfb_par), dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	par->info = info;
	par->dev = dev;

	par->irq = irq_of_parse_and_map(np, 0);
	अगर (par->irq == NO_IRQ) अणु
		dev_err(dev, "failed to map irq\n");
		ret = -ENODEV;
		जाओ fbrel;
	पूर्ण

	res_size = resource_size(&res);
	par->res = request_mem_region(res.start, res_size, DRV_NAME);
	अगर (par->res == शून्य) अणु
		dev_err(dev, "Cannot claim framebuffer/mmio\n");
		ret = -ENXIO;
		जाओ irqdisp;
	पूर्ण

#अगर defined(CONFIG_SOCRATES)
	par->gc_mode = &socrates_gc_mode;
#पूर्ण_अगर

	par->fb_base_phys = res.start;
	par->mmio_base_phys = res.start + MB862XX_MMIO_BASE;
	par->mmio_len = MB862XX_MMIO_SIZE;
	अगर (par->gc_mode)
		par->mapped_vram = par->gc_mode->max_vram;
	अन्यथा
		par->mapped_vram = MB862XX_MEM_SIZE;

	par->fb_base = ioremap(par->fb_base_phys, par->mapped_vram);
	अगर (par->fb_base == शून्य) अणु
		dev_err(dev, "Cannot map framebuffer\n");
		जाओ rel_reg;
	पूर्ण

	par->mmio_base = ioremap(par->mmio_base_phys, par->mmio_len);
	अगर (par->mmio_base == शून्य) अणु
		dev_err(dev, "Cannot map registers\n");
		जाओ fb_unmap;
	पूर्ण

	dev_dbg(dev, "fb phys 0x%llx 0x%lx\n",
		(u64)par->fb_base_phys, (uदीर्घ)par->mapped_vram);
	dev_dbg(dev, "mmio phys 0x%llx 0x%lx, (irq = %d)\n",
		(u64)par->mmio_base_phys, (uदीर्घ)par->mmio_len, par->irq);

	अगर (mb862xx_gdc_init(par))
		जाओ io_unmap;

	अगर (request_irq(par->irq, mb862xx_पूर्णांकr, 0,
			DRV_NAME, (व्योम *)par)) अणु
		dev_err(dev, "Cannot request irq\n");
		जाओ io_unmap;
	पूर्ण

	mb862xxfb_init_fbinfo(info);

	अगर (fb_alloc_cmap(&info->cmap, NR_PALETTE, 0) < 0) अणु
		dev_err(dev, "Could not allocate cmap for fb_info.\n");
		जाओ मुक्त_irq;
	पूर्ण

	अगर ((info->fbops->fb_set_par)(info))
		dev_err(dev, "set_var() failed on initial setup?\n");

	अगर (रेजिस्टर_framebuffer(info)) अणु
		dev_err(dev, "failed to register framebuffer\n");
		जाओ rel_cmap;
	पूर्ण

	dev_set_drvdata(dev, info);

	अगर (device_create_file(dev, &dev_attr_dispregs))
		dev_err(dev, "Can't create sysfs regdump file\n");
	वापस 0;

rel_cmap:
	fb_dealloc_cmap(&info->cmap);
मुक्त_irq:
	outreg(host, GC_IMASK, 0);
	मुक्त_irq(par->irq, (व्योम *)par);
io_unmap:
	iounmap(par->mmio_base);
fb_unmap:
	iounmap(par->fb_base);
rel_reg:
	release_mem_region(res.start, res_size);
irqdisp:
	irq_dispose_mapping(par->irq);
fbrel:
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल पूर्णांक of_platक्रमm_mb862xx_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(&ofdev->dev);
	काष्ठा mb862xxfb_par *par = fbi->par;
	resource_माप_प्रकार res_size = resource_size(par->res);
	अचिन्हित दीर्घ reg;

	dev_dbg(fbi->dev, "%s release\n", fbi->fix.id);

	/* display off */
	reg = inreg(disp, GC_DCM1);
	reg &= ~(GC_DCM01_DEN | GC_DCM01_L0E);
	outreg(disp, GC_DCM1, reg);

	/* disable पूर्णांकerrupts */
	outreg(host, GC_IMASK, 0);

	मुक्त_irq(par->irq, (व्योम *)par);
	irq_dispose_mapping(par->irq);

	device_हटाओ_file(&ofdev->dev, &dev_attr_dispregs);

	unरेजिस्टर_framebuffer(fbi);
	fb_dealloc_cmap(&fbi->cmap);

	iounmap(par->mmio_base);
	iounmap(par->fb_base);

	release_mem_region(par->res->start, res_size);
	framebuffer_release(fbi);
	वापस 0;
पूर्ण

/*
 * common types
 */
अटल काष्ठा of_device_id of_platक्रमm_mb862xx_tbl[] = अणु
	अणु .compatible = "fujitsu,MB86276", पूर्ण,
	अणु .compatible = "fujitsu,lime", पूर्ण,
	अणु .compatible = "fujitsu,MB86277", पूर्ण,
	अणु .compatible = "fujitsu,mint", पूर्ण,
	अणु .compatible = "fujitsu,MB86293", पूर्ण,
	अणु .compatible = "fujitsu,MB86294", पूर्ण,
	अणु .compatible = "fujitsu,coral", पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_platक्रमm_mb862xx_tbl);

अटल काष्ठा platक्रमm_driver of_platक्रमm_mb862xxfb_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_platक्रमm_mb862xx_tbl,
	पूर्ण,
	.probe		= of_platक्रमm_mb862xx_probe,
	.हटाओ		= of_platक्रमm_mb862xx_हटाओ,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_FB_MB862XX_PCI_GDC)
अटल पूर्णांक coralp_init(काष्ठा mb862xxfb_par *par)
अणु
	पूर्णांक cn, ver;

	par->host = par->mmio_base;
	par->i2c = par->mmio_base + MB862XX_I2C_BASE;
	par->disp = par->mmio_base + MB862XX_DISP_BASE;
	par->cap = par->mmio_base + MB862XX_CAP_BASE;
	par->draw = par->mmio_base + MB862XX_DRAW_BASE;
	par->geo = par->mmio_base + MB862XX_GEO_BASE;
	par->pio = par->mmio_base + MB862XX_PIO_BASE;

	par->refclk = GC_DISP_REFCLK_400;

	अगर (par->mapped_vram >= 0x2000000) अणु
		/* relocate gdc रेजिस्टरs space */
		ग_लिखोl(1, par->fb_base + MB862XX_MMIO_BASE + GC_RSW);
		udelay(1); /* रुको at least 20 bus cycles */
	पूर्ण

	ver = inreg(host, GC_CID);
	cn = (ver & GC_CID_CNAME_MSK) >> 8;
	ver = ver & GC_CID_VERSION_MSK;
	अगर (cn == 3) अणु
		अचिन्हित दीर्घ reg;

		dev_info(par->dev, "Fujitsu Coral-%s GDC Rev.%d found\n",\
			 (ver == 6) ? "P" : (ver == 8) ? "PA" : "?",
			 par->pdev->revision);
		reg = inreg(disp, GC_DCM1);
		अगर (reg & GC_DCM01_DEN && reg & GC_DCM01_L0E)
			par->pre_init = 1;

		अगर (!par->pre_init) अणु
			outreg(host, GC_CCF, GC_CCF_CGE_166 | GC_CCF_COT_133);
			udelay(200);
			outreg(host, GC_MMR, GC_MMR_CORALP_EVB_VAL);
			udelay(10);
		पूर्ण
		/* Clear पूर्णांकerrupt status */
		outreg(host, GC_IST, 0);
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	mb862xx_i2c_init(par);
	वापस 0;
पूर्ण

अटल पूर्णांक init_dram_ctrl(काष्ठा mb862xxfb_par *par)
अणु
	अचिन्हित दीर्घ i = 0;

	/*
	 * Set io mode first! Spec. says IC may be destroyed
	 * अगर not set to SSTL2/LVCMOS beक्रमe init.
	 */
	outreg(dram_ctrl, GC_DCTL_IOCONT1_IOCONT0, GC_EVB_DCTL_IOCONT1_IOCONT0);

	/* DRAM init */
	outreg(dram_ctrl, GC_DCTL_MODE_ADD, GC_EVB_DCTL_MODE_ADD);
	outreg(dram_ctrl, GC_DCTL_SETTIME1_EMODE, GC_EVB_DCTL_SETTIME1_EMODE);
	outreg(dram_ctrl, GC_DCTL_REFRESH_SETTIME2,
	       GC_EVB_DCTL_REFRESH_SETTIME2);
	outreg(dram_ctrl, GC_DCTL_RSV2_RSV1, GC_EVB_DCTL_RSV2_RSV1);
	outreg(dram_ctrl, GC_DCTL_DDRIF2_DDRIF1, GC_EVB_DCTL_DDRIF2_DDRIF1);
	outreg(dram_ctrl, GC_DCTL_RSV0_STATES, GC_EVB_DCTL_RSV0_STATES);

	/* DLL reset करोne? */
	जबतक ((inreg(dram_ctrl, GC_DCTL_RSV0_STATES) & GC_DCTL_STATES_MSK)) अणु
		udelay(GC_DCTL_INIT_WAIT_INTERVAL);
		अगर (i++ > GC_DCTL_INIT_WAIT_CNT) अणु
			dev_err(par->dev, "VRAM init failed.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	outreg(dram_ctrl, GC_DCTL_MODE_ADD, GC_EVB_DCTL_MODE_ADD_AFT_RST);
	outreg(dram_ctrl, GC_DCTL_RSV0_STATES, GC_EVB_DCTL_RSV0_STATES_AFT_RST);
	वापस 0;
पूर्ण

अटल पूर्णांक carmine_init(काष्ठा mb862xxfb_par *par)
अणु
	अचिन्हित दीर्घ reg;

	par->ctrl = par->mmio_base + MB86297_CTRL_BASE;
	par->i2c = par->mmio_base + MB86297_I2C_BASE;
	par->disp = par->mmio_base + MB86297_DISP0_BASE;
	par->disp1 = par->mmio_base + MB86297_DISP1_BASE;
	par->cap = par->mmio_base + MB86297_CAP0_BASE;
	par->cap1 = par->mmio_base + MB86297_CAP1_BASE;
	par->draw = par->mmio_base + MB86297_DRAW_BASE;
	par->dram_ctrl = par->mmio_base + MB86297_DRAMCTRL_BASE;
	par->wrback = par->mmio_base + MB86297_WRBACK_BASE;

	par->refclk = GC_DISP_REFCLK_533;

	/* warm up */
	reg = GC_CTRL_CLK_EN_DRAM | GC_CTRL_CLK_EN_2D3D | GC_CTRL_CLK_EN_DISP0;
	outreg(ctrl, GC_CTRL_CLK_ENABLE, reg);

	/* check क्रम engine module revision */
	अगर (inreg(draw, GC_2D3D_REV) == GC_RE_REVISION)
		dev_info(par->dev, "Fujitsu Carmine GDC Rev.%d found\n",
			 par->pdev->revision);
	अन्यथा
		जाओ err_init;

	reg &= ~GC_CTRL_CLK_EN_2D3D;
	outreg(ctrl, GC_CTRL_CLK_ENABLE, reg);

	/* set up vram */
	अगर (init_dram_ctrl(par) < 0)
		जाओ err_init;

	outreg(ctrl, GC_CTRL_INT_MASK, 0);
	वापस 0;

err_init:
	outreg(ctrl, GC_CTRL_CLK_ENABLE, 0);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक mb862xx_pci_gdc_init(काष्ठा mb862xxfb_par *par)
अणु
	चयन (par->type) अणु
	हाल BT_CORALP:
		वापस coralp_init(par);
	हाल BT_CARMINE:
		वापस carmine_init(par);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

#घोषणा CHIP_ID(id)	\
	अणु PCI_DEVICE(PCI_VENDOR_ID_FUJITSU_LIMITED, id) पूर्ण

अटल स्थिर काष्ठा pci_device_id mb862xx_pci_tbl[] = अणु
	/* MB86295/MB86296 */
	CHIP_ID(PCI_DEVICE_ID_FUJITSU_CORALP),
	CHIP_ID(PCI_DEVICE_ID_FUJITSU_CORALPA),
	/* MB86297 */
	CHIP_ID(PCI_DEVICE_ID_FUJITSU_CARMINE),
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, mb862xx_pci_tbl);

अटल पूर्णांक mb862xx_pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा mb862xxfb_par *par;
	काष्ठा fb_info *info;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot enable PCI device\n");
		जाओ out;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा mb862xxfb_par), dev);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ dis_dev;
	पूर्ण

	par = info->par;
	par->info = info;
	par->dev = dev;
	par->pdev = pdev;
	par->irq = pdev->irq;

	ret = pci_request_regions(pdev, DRV_NAME);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot reserve region(s) for PCI device\n");
		जाओ rel_fb;
	पूर्ण

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_FUJITSU_CORALP:
	हाल PCI_DEVICE_ID_FUJITSU_CORALPA:
		par->fb_base_phys = pci_resource_start(par->pdev, 0);
		par->mapped_vram = CORALP_MEM_SIZE;
		अगर (par->mapped_vram >= 0x2000000) अणु
			par->mmio_base_phys = par->fb_base_phys +
					      MB862XX_MMIO_HIGH_BASE;
		पूर्ण अन्यथा अणु
			par->mmio_base_phys = par->fb_base_phys +
					      MB862XX_MMIO_BASE;
		पूर्ण
		par->mmio_len = MB862XX_MMIO_SIZE;
		par->type = BT_CORALP;
		अवरोध;
	हाल PCI_DEVICE_ID_FUJITSU_CARMINE:
		par->fb_base_phys = pci_resource_start(par->pdev, 2);
		par->mmio_base_phys = pci_resource_start(par->pdev, 3);
		par->mmio_len = pci_resource_len(par->pdev, 3);
		par->mapped_vram = CARMINE_MEM_SIZE;
		par->type = BT_CARMINE;
		अवरोध;
	शेष:
		/* should never occur */
		ret = -EIO;
		जाओ rel_reg;
	पूर्ण

	par->fb_base = ioremap(par->fb_base_phys, par->mapped_vram);
	अगर (par->fb_base == शून्य) अणु
		dev_err(dev, "Cannot map framebuffer\n");
		ret = -EIO;
		जाओ rel_reg;
	पूर्ण

	par->mmio_base = ioremap(par->mmio_base_phys, par->mmio_len);
	अगर (par->mmio_base == शून्य) अणु
		dev_err(dev, "Cannot map registers\n");
		ret = -EIO;
		जाओ fb_unmap;
	पूर्ण

	dev_dbg(dev, "fb phys 0x%llx 0x%lx\n",
		(अचिन्हित दीर्घ दीर्घ)par->fb_base_phys, (uदीर्घ)par->mapped_vram);
	dev_dbg(dev, "mmio phys 0x%llx 0x%lx\n",
		(अचिन्हित दीर्घ दीर्घ)par->mmio_base_phys, (uदीर्घ)par->mmio_len);

	ret = mb862xx_pci_gdc_init(par);
	अगर (ret)
		जाओ io_unmap;

	ret = request_irq(par->irq, mb862xx_पूर्णांकr, IRQF_SHARED,
			  DRV_NAME, (व्योम *)par);
	अगर (ret) अणु
		dev_err(dev, "Cannot request irq\n");
		जाओ io_unmap;
	पूर्ण

	mb862xxfb_init_fbinfo(info);

	अगर (fb_alloc_cmap(&info->cmap, NR_PALETTE, 0) < 0) अणु
		dev_err(dev, "Could not allocate cmap for fb_info.\n");
		ret = -ENOMEM;
		जाओ मुक्त_irq;
	पूर्ण

	अगर ((info->fbops->fb_set_par)(info))
		dev_err(dev, "set_var() failed on initial setup?\n");

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register framebuffer\n");
		जाओ rel_cmap;
	पूर्ण

	pci_set_drvdata(pdev, info);

	अगर (device_create_file(dev, &dev_attr_dispregs))
		dev_err(dev, "Can't create sysfs regdump file\n");

	अगर (par->type == BT_CARMINE)
		outreg(ctrl, GC_CTRL_INT_MASK, GC_CARMINE_INT_EN);
	अन्यथा
		outreg(host, GC_IMASK, GC_INT_EN);

	वापस 0;

rel_cmap:
	fb_dealloc_cmap(&info->cmap);
मुक्त_irq:
	मुक्त_irq(par->irq, (व्योम *)par);
io_unmap:
	iounmap(par->mmio_base);
fb_unmap:
	iounmap(par->fb_base);
rel_reg:
	pci_release_regions(pdev);
rel_fb:
	framebuffer_release(info);
dis_dev:
	pci_disable_device(pdev);
out:
	वापस ret;
पूर्ण

अटल व्योम mb862xx_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *fbi = pci_get_drvdata(pdev);
	काष्ठा mb862xxfb_par *par = fbi->par;
	अचिन्हित दीर्घ reg;

	dev_dbg(fbi->dev, "%s release\n", fbi->fix.id);

	/* display off */
	reg = inreg(disp, GC_DCM1);
	reg &= ~(GC_DCM01_DEN | GC_DCM01_L0E);
	outreg(disp, GC_DCM1, reg);

	अगर (par->type == BT_CARMINE) अणु
		outreg(ctrl, GC_CTRL_INT_MASK, 0);
		outreg(ctrl, GC_CTRL_CLK_ENABLE, 0);
	पूर्ण अन्यथा अणु
		outreg(host, GC_IMASK, 0);
	पूर्ण

	mb862xx_i2c_निकास(par);

	device_हटाओ_file(&pdev->dev, &dev_attr_dispregs);

	unरेजिस्टर_framebuffer(fbi);
	fb_dealloc_cmap(&fbi->cmap);

	मुक्त_irq(par->irq, (व्योम *)par);
	iounmap(par->mmio_base);
	iounmap(par->fb_base);

	pci_release_regions(pdev);
	framebuffer_release(fbi);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver mb862xxfb_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= mb862xx_pci_tbl,
	.probe		= mb862xx_pci_probe,
	.हटाओ		= mb862xx_pci_हटाओ,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक mb862xxfb_init(व्योम)
अणु
	पूर्णांक ret = -ENODEV;

#अगर defined(CONFIG_FB_MB862XX_LIME)
	ret = platक्रमm_driver_रेजिस्टर(&of_platक्रमm_mb862xxfb_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_FB_MB862XX_PCI_GDC)
	ret = pci_रेजिस्टर_driver(&mb862xxfb_pci_driver);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम __निकास mb862xxfb_निकास(व्योम)
अणु
#अगर defined(CONFIG_FB_MB862XX_LIME)
	platक्रमm_driver_unरेजिस्टर(&of_platक्रमm_mb862xxfb_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_FB_MB862XX_PCI_GDC)
	pci_unरेजिस्टर_driver(&mb862xxfb_pci_driver);
#पूर्ण_अगर
पूर्ण

module_init(mb862xxfb_init);
module_निकास(mb862xxfb_निकास);

MODULE_DESCRIPTION("Fujitsu MB862xx Framebuffer driver");
MODULE_AUTHOR("Anatolij Gustschin <agust@denx.de>");
MODULE_LICENSE("GPL v2");
