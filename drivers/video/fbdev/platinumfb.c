<शैली गुरु>
/*
 *  platinumfb.c -- frame buffer device क्रम the PowerMac 'platinum' display
 *
 *  Copyright (C) 1998 Franz Sirl
 *
 *  Frame buffer काष्ठाure from:
 *    drivers/video/controlfb.c -- frame buffer device क्रम
 *    Apple 'control' display chip.
 *    Copyright (C) 1998 Dan Jacobowitz
 *
 *  Hardware inक्रमmation from:
 *    platinum.c: Console support क्रम PowerMac "platinum" display adaptor.
 *    Copyright (C) 1996 Paul Mackerras and Mark Abene
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#अघोषित DEBUG

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/nvram.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/prom.h>

#समावेश "macmodes.h"
#समावेश "platinumfb.h"

अटल पूर्णांक शेष_vmode = VMODE_NVRAM;
अटल पूर्णांक शेष_cmode = CMODE_NVRAM;

काष्ठा fb_info_platinum अणु
	काष्ठा fb_info			*info;

	पूर्णांक				vmode, cmode;
	पूर्णांक				xres, yres;
	पूर्णांक				vxres, vyres;
	पूर्णांक				xoffset, yoffset;

	काष्ठा अणु
		__u8 red, green, blue;
	पूर्ण				palette[256];
	u32				pseuकरो_palette[16];
	
	अस्थिर काष्ठा cmap_regs	__iomem *cmap_regs;
	अचिन्हित दीर्घ			cmap_regs_phys;
	
	अस्थिर काष्ठा platinum_regs	__iomem *platinum_regs;
	अचिन्हित दीर्घ			platinum_regs_phys;
	
	__u8				__iomem *frame_buffer;
	अस्थिर __u8			__iomem *base_frame_buffer;
	अचिन्हित दीर्घ			frame_buffer_phys;
	
	अचिन्हित दीर्घ			total_vram;
	पूर्णांक				clktype;
	पूर्णांक				dactype;

	काष्ठा resource			rsrc_fb, rsrc_reg;
पूर्ण;

/*
 * Frame buffer device API
 */

अटल पूर्णांक platinumfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
	u_पूर्णांक transp, काष्ठा fb_info *info);
अटल पूर्णांक platinumfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info);
अटल पूर्णांक platinumfb_set_par (काष्ठा fb_info *info);
अटल पूर्णांक platinumfb_check_var (काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info);

/*
 * पूर्णांकernal functions
 */

अटल अंतरभूत पूर्णांक platinum_vram_reqd(पूर्णांक video_mode, पूर्णांक color_mode);
अटल पूर्णांक पढ़ो_platinum_sense(काष्ठा fb_info_platinum *pinfo);
अटल व्योम set_platinum_घड़ी(काष्ठा fb_info_platinum *pinfo);
अटल व्योम platinum_set_hardware(काष्ठा fb_info_platinum *pinfo);
अटल पूर्णांक platinum_var_to_par(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info_platinum *pinfo,
			       पूर्णांक check_only);

/*
 * Interface used by the world
 */

अटल स्थिर काष्ठा fb_ops platinumfb_ops = अणु
	.owner =	THIS_MODULE,
	.fb_check_var	= platinumfb_check_var,
	.fb_set_par	= platinumfb_set_par,
	.fb_setcolreg	= platinumfb_setcolreg,
	.fb_blank	= platinumfb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

/*
 * Checks a var काष्ठाure
 */
अटल पूर्णांक platinumfb_check_var (काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	वापस platinum_var_to_par(var, info->par, 1);
पूर्ण

/*
 * Applies current var to display
 */
अटल पूर्णांक platinumfb_set_par (काष्ठा fb_info *info)
अणु
	काष्ठा fb_info_platinum *pinfo = info->par;
	काष्ठा platinum_regvals *init;
	पूर्णांक err, offset = 0x20;

	अगर((err = platinum_var_to_par(&info->var, pinfo, 0))) अणु
		prपूर्णांकk (KERN_ERR "platinumfb_set_par: error calling"
				 " platinum_var_to_par: %d.\n", err);
		वापस err;
	पूर्ण

	platinum_set_hardware(pinfo);

	init = platinum_reg_init[pinfo->vmode-1];
	
 	अगर ((pinfo->vmode == VMODE_832_624_75) && (pinfo->cmode > CMODE_8))
  		offset = 0x10;

	info->screen_base = pinfo->frame_buffer + init->fb_offset + offset;
	mutex_lock(&info->mm_lock);
	info->fix.smem_start = (pinfo->frame_buffer_phys) + init->fb_offset + offset;
	mutex_unlock(&info->mm_lock);
	info->fix.visual = (pinfo->cmode == CMODE_8) ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_सूचीECTCOLOR;
 	info->fix.line_length = vmode_attrs[pinfo->vmode-1].hres * (1<<pinfo->cmode)
		+ offset;
	prपूर्णांकk("line_length: %x\n", info->fix.line_length);
	वापस 0;
पूर्ण

अटल पूर्णांक platinumfb_blank(पूर्णांक blank,  काष्ठा fb_info *fb)
अणु
/*
 *  Blank the screen अगर blank_mode != 0, अन्यथा unblank. If blank == शून्य
 *  then the caller blanks by setting the CLUT (Color Look Up Table) to all
 *  black. Return 0 अगर blanking succeeded, != 0 अगर un-/blanking failed due
 *  to e.g. a video mode which करोesn't support it. Implements VESA suspend
 *  and घातerकरोwn modes on hardware that supports disabling hsync/vsync:
 *    blank_mode == 2: suspend vsync
 *    blank_mode == 3: suspend hsync
 *    blank_mode == 4: घातerकरोwn
 */
/* [danj] I think there's something fishy about those स्थिरants... */
/*
	काष्ठा fb_info_platinum *info = (काष्ठा fb_info_platinum *) fb;
	पूर्णांक	ctrl;

	ctrl = le32_to_cpup(&info->platinum_regs->ctrl.r) | 0x33;
	अगर (blank)
		--blank_mode;
	अगर (blank & VESA_VSYNC_SUSPEND)
		ctrl &= ~3;
	अगर (blank & VESA_HSYNC_SUSPEND)
		ctrl &= ~0x30;
	out_le32(&info->platinum_regs->ctrl.r, ctrl);
*/
/* TODO: Figure out how the heck to घातerकरोwn this thing! */
	वापस 0;
पूर्ण

अटल पूर्णांक platinumfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			      u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा fb_info_platinum *pinfo = info->par;
	अस्थिर काष्ठा cmap_regs __iomem *cmap_regs = pinfo->cmap_regs;

	अगर (regno > 255)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	pinfo->palette[regno].red = red;
	pinfo->palette[regno].green = green;
	pinfo->palette[regno].blue = blue;

	out_8(&cmap_regs->addr, regno);		/* tell clut what addr to fill	*/
	out_8(&cmap_regs->lut, red);		/* send one color channel at	*/
	out_8(&cmap_regs->lut, green);		/* a समय...			*/
	out_8(&cmap_regs->lut, blue);

	अगर (regno < 16) अणु
		पूर्णांक i;
		u32 *pal = info->pseuकरो_palette;
		चयन (pinfo->cmode) अणु
		हाल CMODE_16:
			pal[regno] = (regno << 10) | (regno << 5) | regno;
			अवरोध;
		हाल CMODE_32:
			i = (regno << 8) | regno;
			pal[regno] = (i << 16) | i;
			अवरोध;
		पूर्ण
	पूर्ण
	
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक platinum_vram_reqd(पूर्णांक video_mode, पूर्णांक color_mode)
अणु
	पूर्णांक baseval = vmode_attrs[video_mode-1].hres * (1<<color_mode);

	अगर ((video_mode == VMODE_832_624_75) && (color_mode > CMODE_8))
		baseval += 0x10;
	अन्यथा
		baseval += 0x20;

	वापस vmode_attrs[video_mode-1].vres * baseval + 0x1000;
पूर्ण

#घोषणा STORE_D2(a, d) अणु \
	out_8(&cmap_regs->addr, (a+32)); \
	out_8(&cmap_regs->d2, (d)); \
पूर्ण

अटल व्योम set_platinum_घड़ी(काष्ठा fb_info_platinum *pinfo)
अणु
	अस्थिर काष्ठा cmap_regs __iomem *cmap_regs = pinfo->cmap_regs;
	काष्ठा platinum_regvals	*init;

	init = platinum_reg_init[pinfo->vmode-1];

	STORE_D2(6, 0xc6);
	out_8(&cmap_regs->addr,3+32);

	अगर (in_8(&cmap_regs->d2) == 2) अणु
		STORE_D2(7, init->घड़ी_params[pinfo->clktype][0]);
		STORE_D2(8, init->घड़ी_params[pinfo->clktype][1]);
		STORE_D2(3, 3);
	पूर्ण अन्यथा अणु
		STORE_D2(4, init->घड़ी_params[pinfo->clktype][0]);
		STORE_D2(5, init->घड़ी_params[pinfo->clktype][1]);
		STORE_D2(3, 2);
	पूर्ण

	__delay(5000);
	STORE_D2(9, 0xa6);
पूर्ण


/* Now how about actually saying, Make it so! */
/* Some things in here probably करोn't need to be करोne each समय. */
अटल व्योम platinum_set_hardware(काष्ठा fb_info_platinum *pinfo)
अणु
	अस्थिर काष्ठा platinum_regs	__iomem *platinum_regs = pinfo->platinum_regs;
	अस्थिर काष्ठा cmap_regs	__iomem *cmap_regs = pinfo->cmap_regs;
	काष्ठा platinum_regvals		*init;
	पूर्णांक				i;
	पूर्णांक				vmode, cmode;
	
	vmode = pinfo->vmode;
	cmode = pinfo->cmode;

	init = platinum_reg_init[vmode - 1];

	/* Initialize display timing रेजिस्टरs */
	out_be32(&platinum_regs->reg[24].r, 7);	/* turn display off */

	क्रम (i = 0; i < 26; ++i)
		out_be32(&platinum_regs->reg[i+32].r, init->regs[i]);

	out_be32(&platinum_regs->reg[26+32].r, (pinfo->total_vram == 0x100000 ?
						init->offset[cmode] + 4 - cmode :
						init->offset[cmode]));
	out_be32(&platinum_regs->reg[16].r, (अचिन्हित) pinfo->frame_buffer_phys+init->fb_offset+0x10);
	out_be32(&platinum_regs->reg[18].r, init->pitch[cmode]);
	out_be32(&platinum_regs->reg[19].r, (pinfo->total_vram == 0x100000 ?
					     init->mode[cmode+1] :
					     init->mode[cmode]));
	out_be32(&platinum_regs->reg[20].r, (pinfo->total_vram == 0x100000 ? 0x11 : 0x1011));
	out_be32(&platinum_regs->reg[21].r, 0x100);
	out_be32(&platinum_regs->reg[22].r, 1);
	out_be32(&platinum_regs->reg[23].r, 1);
	out_be32(&platinum_regs->reg[26].r, 0xc00);
	out_be32(&platinum_regs->reg[27].r, 0x235);
	/* out_be32(&platinum_regs->reg[27].r, 0x2aa); */

	STORE_D2(0, (pinfo->total_vram == 0x100000 ?
		     init->dacula_ctrl[cmode] & 0xf :
		     init->dacula_ctrl[cmode]));
	STORE_D2(1, 4);
	STORE_D2(2, 0);

	set_platinum_घड़ी(pinfo);

	out_be32(&platinum_regs->reg[24].r, 0);	/* turn display on */
पूर्ण

/*
 * Set misc info vars क्रम this driver
 */
अटल व्योम platinum_init_info(काष्ठा fb_info *info,
			       काष्ठा fb_info_platinum *pinfo)
अणु
	/* Fill fb_info */
	info->fbops = &platinumfb_ops;
	info->pseuकरो_palette = pinfo->pseuकरो_palette;
        info->flags = FBINFO_DEFAULT;
	info->screen_base = pinfo->frame_buffer + 0x20;

	fb_alloc_cmap(&info->cmap, 256, 0);

	/* Fill fix common fields */
	म_नकल(info->fix.id, "platinum");
	info->fix.mmio_start = pinfo->platinum_regs_phys;
	info->fix.mmio_len = 0x1000;
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.smem_start = pinfo->frame_buffer_phys + 0x20; /* will be updated later */
	info->fix.smem_len = pinfo->total_vram - 0x20;
        info->fix.ywrapstep = 0;
	info->fix.xpanstep = 0;
	info->fix.ypanstep = 0;
        info->fix.type_aux = 0;
        info->fix.accel = FB_ACCEL_NONE;
पूर्ण


अटल पूर्णांक platinum_init_fb(काष्ठा fb_info *info)
अणु
	काष्ठा fb_info_platinum *pinfo = info->par;
	काष्ठा fb_var_screeninfo var;
	पूर्णांक sense, rc;

	sense = पढ़ो_platinum_sense(pinfo);
	prपूर्णांकk(KERN_INFO "platinumfb: Monitor sense value = 0x%x, ", sense);

	अगर (IS_REACHABLE(CONFIG_NVRAM) && शेष_vmode == VMODE_NVRAM)
		शेष_vmode = nvram_पढ़ो_byte(NV_VMODE);
	अगर (शेष_vmode <= 0 || शेष_vmode > VMODE_MAX ||
	    !platinum_reg_init[शेष_vmode - 1]) अणु
		शेष_vmode = mac_map_monitor_sense(sense);
		अगर (!platinum_reg_init[शेष_vmode - 1])
			शेष_vmode = VMODE_640_480_60;
	पूर्ण

	अगर (IS_REACHABLE(CONFIG_NVRAM) && शेष_cmode == CMODE_NVRAM)
		शेष_cmode = nvram_पढ़ो_byte(NV_CMODE);
	अगर (शेष_cmode < CMODE_8 || शेष_cmode > CMODE_32)
		शेष_cmode = CMODE_8;
	/*
	 * Reduce the pixel size अगर we करोn't have enough VRAM.
	 */
	जबतक(शेष_cmode > CMODE_8 &&
	      platinum_vram_reqd(शेष_vmode, शेष_cmode) > pinfo->total_vram)
		शेष_cmode--;

	prपूर्णांकk("platinumfb:  Using video mode %d and color mode %d.\n", शेष_vmode, शेष_cmode);

	/* Setup शेष var */
	अगर (mac_vmode_to_var(शेष_vmode, शेष_cmode, &var) < 0) अणु
		/* This shouldn't happen! */
		prपूर्णांकk("mac_vmode_to_var(%d, %d,) failed\n", शेष_vmode, शेष_cmode);
try_again:
		शेष_vmode = VMODE_640_480_60;
		शेष_cmode = CMODE_8;
		अगर (mac_vmode_to_var(शेष_vmode, शेष_cmode, &var) < 0) अणु
			prपूर्णांकk(KERN_ERR "platinumfb: mac_vmode_to_var() failed\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	/* Initialize info काष्ठाure */
	platinum_init_info(info, pinfo);

	/* Apply शेष var */
	info->var = var;
	var.activate = FB_ACTIVATE_NOW;
	rc = fb_set_var(info, &var);
	अगर (rc && (शेष_vmode != VMODE_640_480_60 || शेष_cmode != CMODE_8))
		जाओ try_again;

	/* Register with fbdev layer */
	rc = रेजिस्टर_framebuffer(info);
	अगर (rc < 0)
		वापस rc;

	fb_info(info, "Apple Platinum frame buffer device\n");

	वापस 0;
पूर्ण

/*
 * Get the monitor sense value.
 * Note that this can be called beक्रमe calibrate_delay,
 * so we can't use udelay.
 */
अटल पूर्णांक पढ़ो_platinum_sense(काष्ठा fb_info_platinum *info)
अणु
	अस्थिर काष्ठा platinum_regs __iomem *platinum_regs = info->platinum_regs;
	पूर्णांक sense;

	out_be32(&platinum_regs->reg[23].r, 7);	/* turn off drivers */
	__delay(2000);
	sense = (~in_be32(&platinum_regs->reg[23].r) & 7) << 8;

	/* drive each sense line low in turn and collect the other 2 */
	out_be32(&platinum_regs->reg[23].r, 3);	/* drive A low */
	__delay(2000);
	sense |= (~in_be32(&platinum_regs->reg[23].r) & 3) << 4;
	out_be32(&platinum_regs->reg[23].r, 5);	/* drive B low */
	__delay(2000);
	sense |= (~in_be32(&platinum_regs->reg[23].r) & 4) << 1;
	sense |= (~in_be32(&platinum_regs->reg[23].r) & 1) << 2;
	out_be32(&platinum_regs->reg[23].r, 6);	/* drive C low */
	__delay(2000);
	sense |= (~in_be32(&platinum_regs->reg[23].r) & 6) >> 1;

	out_be32(&platinum_regs->reg[23].r, 7);	/* turn off drivers */

	वापस sense;
पूर्ण

/*
 * This routine takes a user-supplied var, and picks the best vmode/cmode from it.
 * It also updates the var काष्ठाure to the actual mode data obtained
 */
अटल पूर्णांक platinum_var_to_par(काष्ठा fb_var_screeninfo *var, 
			       काष्ठा fb_info_platinum *pinfo,
			       पूर्णांक check_only)
अणु
	पूर्णांक vmode, cmode;

	अगर (mac_var_to_vmode(var, &vmode, &cmode) != 0) अणु
		prपूर्णांकk(KERN_ERR "platinum_var_to_par: mac_var_to_vmode unsuccessful.\n");
		prपूर्णांकk(KERN_ERR "platinum_var_to_par: var->xres = %d\n", var->xres);
		prपूर्णांकk(KERN_ERR "platinum_var_to_par: var->yres = %d\n", var->yres);
		prपूर्णांकk(KERN_ERR "platinum_var_to_par: var->xres_virtual = %d\n", var->xres_भव);
		prपूर्णांकk(KERN_ERR "platinum_var_to_par: var->yres_virtual = %d\n", var->yres_भव);
		prपूर्णांकk(KERN_ERR "platinum_var_to_par: var->bits_per_pixel = %d\n", var->bits_per_pixel);
		prपूर्णांकk(KERN_ERR "platinum_var_to_par: var->pixclock = %d\n", var->pixघड़ी);
		prपूर्णांकk(KERN_ERR "platinum_var_to_par: var->vmode = %d\n", var->vmode);
		वापस -EINVAL;
	पूर्ण

	अगर (!platinum_reg_init[vmode-1]) अणु
		prपूर्णांकk(KERN_ERR "platinum_var_to_par, vmode %d not valid.\n", vmode);
		वापस -EINVAL;
	पूर्ण

	अगर (platinum_vram_reqd(vmode, cmode) > pinfo->total_vram) अणु
		prपूर्णांकk(KERN_ERR "platinum_var_to_par, not enough ram for vmode %d, cmode %d.\n", vmode, cmode);
		वापस -EINVAL;
	पूर्ण

	अगर (mac_vmode_to_var(vmode, cmode, var))
		वापस -EINVAL;

	अगर (check_only)
		वापस 0;

	pinfo->vmode = vmode;
	pinfo->cmode = cmode;
	pinfo->xres = vmode_attrs[vmode-1].hres;
	pinfo->yres = vmode_attrs[vmode-1].vres;
	pinfo->xoffset = 0;
	pinfo->yoffset = 0;
	pinfo->vxres = pinfo->xres;
	pinfo->vyres = pinfo->yres;
	
	वापस 0;
पूर्ण


/* 
 * Parse user specअगरied options (`video=platinumfb:')
 */
अटल पूर्णांक __init platinumfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "vmode:", 6)) अणु
	    		पूर्णांक vmode = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			अगर (vmode > 0 && vmode <= VMODE_MAX)
				शेष_vmode = vmode;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "cmode:", 6)) अणु
			पूर्णांक depth = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			चयन (depth) अणु
			 हाल 0:
			 हाल 8:
			    शेष_cmode = CMODE_8;
			    अवरोध;
			 हाल 15:
			 हाल 16:
			    शेष_cmode = CMODE_16;
			    अवरोध;
			 हाल 24:
			 हाल 32:
			    शेष_cmode = CMODE_32;
			    अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित __घातerpc__
#घोषणा invalidate_cache(addr) \
	यंत्र अस्थिर("eieio; dcbf 0,%1" \
	: "=m" (*(addr)) : "r" (addr) : "memory");
#अन्यथा
#घोषणा invalidate_cache(addr)
#पूर्ण_अगर

अटल पूर्णांक platinumfb_probe(काष्ठा platक्रमm_device* odev)
अणु
	काष्ठा device_node	*dp = odev->dev.of_node;
	काष्ठा fb_info		*info;
	काष्ठा fb_info_platinum	*pinfo;
	अस्थिर __u8		*fbuffer;
	पूर्णांक			bank0, bank1, bank2, bank3, rc;

	dev_info(&odev->dev, "Found Apple Platinum video hardware\n");

	info = framebuffer_alloc(माप(*pinfo), &odev->dev);
	अगर (!info)
		वापस -ENOMEM;

	pinfo = info->par;

	अगर (of_address_to_resource(dp, 0, &pinfo->rsrc_reg) ||
	    of_address_to_resource(dp, 1, &pinfo->rsrc_fb)) अणु
		dev_err(&odev->dev, "Can't get resources\n");
		framebuffer_release(info);
		वापस -ENXIO;
	पूर्ण
	dev_dbg(&odev->dev, " registers  : 0x%llx...0x%llx\n",
		(अचिन्हित दीर्घ दीर्घ)pinfo->rsrc_reg.start,
		(अचिन्हित दीर्घ दीर्घ)pinfo->rsrc_reg.end);
	dev_dbg(&odev->dev, " framebuffer: 0x%llx...0x%llx\n",
		(अचिन्हित दीर्घ दीर्घ)pinfo->rsrc_fb.start,
		(अचिन्हित दीर्घ दीर्घ)pinfo->rsrc_fb.end);

	/* Do not try to request रेजिस्टर space, they overlap with the
	 * northbridge and that can fail. Only request framebuffer
	 */
	अगर (!request_mem_region(pinfo->rsrc_fb.start,
				resource_size(&pinfo->rsrc_fb),
				"platinumfb framebuffer")) अणु
		prपूर्णांकk(KERN_ERR "platinumfb: Can't request framebuffer !\n");
		framebuffer_release(info);
		वापस -ENXIO;
	पूर्ण

	/* frame buffer - map only 4MB */
	pinfo->frame_buffer_phys = pinfo->rsrc_fb.start;
	pinfo->frame_buffer = ioremap_wt(pinfo->rsrc_fb.start, 0x400000);
	pinfo->base_frame_buffer = pinfo->frame_buffer;

	/* रेजिस्टरs */
	pinfo->platinum_regs_phys = pinfo->rsrc_reg.start;
	pinfo->platinum_regs = ioremap(pinfo->rsrc_reg.start, 0x1000);

	pinfo->cmap_regs_phys = 0xf301b000;	/* XXX not in prom? */
	request_mem_region(pinfo->cmap_regs_phys, 0x1000, "platinumfb cmap");
	pinfo->cmap_regs = ioremap(pinfo->cmap_regs_phys, 0x1000);

	/* Grok total video ram */
	out_be32(&pinfo->platinum_regs->reg[16].r, (अचिन्हित)pinfo->frame_buffer_phys);
	out_be32(&pinfo->platinum_regs->reg[20].r, 0x1011);	/* select max vram */
	out_be32(&pinfo->platinum_regs->reg[24].r, 0);	/* चयन in vram */

	fbuffer = pinfo->base_frame_buffer;
	fbuffer[0x100000] = 0x34;
	fbuffer[0x100008] = 0x0;
	invalidate_cache(&fbuffer[0x100000]);
	fbuffer[0x200000] = 0x56;
	fbuffer[0x200008] = 0x0;
	invalidate_cache(&fbuffer[0x200000]);
	fbuffer[0x300000] = 0x78;
	fbuffer[0x300008] = 0x0;
	invalidate_cache(&fbuffer[0x300000]);
	bank0 = 1; /* builtin 1MB vram, always there */
	bank1 = fbuffer[0x100000] == 0x34;
	bank2 = fbuffer[0x200000] == 0x56;
	bank3 = fbuffer[0x300000] == 0x78;
	pinfo->total_vram = (bank0 + bank1 + bank2 + bank3) * 0x100000;
	prपूर्णांकk(KERN_INFO "platinumfb: Total VRAM = %dMB (%d%d%d%d)\n",
	       (अचिन्हित पूर्णांक) (pinfo->total_vram / 1024 / 1024),
	       bank3, bank2, bank1, bank0);

	/*
	 * Try to determine whether we have an old or a new DACula.
	 */
	out_8(&pinfo->cmap_regs->addr, 0x40);
	pinfo->dactype = in_8(&pinfo->cmap_regs->d2);
	चयन (pinfo->dactype) अणु
	हाल 0x3c:
		pinfo->clktype = 1;
		prपूर्णांकk(KERN_INFO "platinumfb: DACula type 0x3c\n");
		अवरोध;
	हाल 0x84:
		pinfo->clktype = 0;
		prपूर्णांकk(KERN_INFO "platinumfb: DACula type 0x84\n");
		अवरोध;
	शेष:
		pinfo->clktype = 0;
		prपूर्णांकk(KERN_INFO "platinumfb: Unknown DACula type: %x\n", pinfo->dactype);
		अवरोध;
	पूर्ण
	dev_set_drvdata(&odev->dev, info);
	
	rc = platinum_init_fb(info);
	अगर (rc != 0) अणु
		iounmap(pinfo->frame_buffer);
		iounmap(pinfo->platinum_regs);
		iounmap(pinfo->cmap_regs);
		framebuffer_release(info);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक platinumfb_हटाओ(काष्ठा platक्रमm_device* odev)
अणु
	काष्ठा fb_info		*info = dev_get_drvdata(&odev->dev);
	काष्ठा fb_info_platinum	*pinfo = info->par;
	
        unरेजिस्टर_framebuffer (info);
	
	/* Unmap frame buffer and रेजिस्टरs */
	iounmap(pinfo->frame_buffer);
	iounmap(pinfo->platinum_regs);
	iounmap(pinfo->cmap_regs);

	release_mem_region(pinfo->rsrc_fb.start,
			   resource_size(&pinfo->rsrc_fb));

	release_mem_region(pinfo->cmap_regs_phys, 0x1000);

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल काष्ठा of_device_id platinumfb_match[] = 
अणु
	अणु
	.name 		= "platinum",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver platinum_driver = 
अणु
	.driver = अणु
		.name = "platinumfb",
		.of_match_table = platinumfb_match,
	पूर्ण,
	.probe		= platinumfb_probe,
	.हटाओ		= platinumfb_हटाओ,
पूर्ण;

अटल पूर्णांक __init platinumfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("platinumfb", &option))
		वापस -ENODEV;
	platinumfb_setup(option);
#पूर्ण_अगर
	platक्रमm_driver_रेजिस्टर(&platinum_driver);

	वापस 0;
पूर्ण

अटल व्योम __निकास platinumfb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&platinum_driver);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("framebuffer driver for Apple Platinum video");
module_init(platinumfb_init);

#अगर_घोषित MODULE
module_निकास(platinumfb_निकास);
#पूर्ण_अगर
