<शैली गुरु>
/*
 *  valkyriefb.c -- frame buffer device क्रम the PowerMac 'valkyrie' display
 *
 *  Created 8 August 1998 by 
 *  Martin Costabel <costabel@wanaकरोo.fr> and Kevin Schoedel
 *
 *  Vmode-चयनing changes and vmode 15/17 modअगरications created 29 August
 *  1998 by Barry K. Nathan <barryn@pobox.com>.
 *
 *  Ported to m68k Macपूर्णांकosh by David Huggins-Daines <dhd@debian.org>
 *
 *  Derived directly from:
 *
 *   controlfb.c -- frame buffer device क्रम the PowerMac 'control' display
 *   Copyright (C) 1998 Dan Jacobowitz <dan@debian.org>
 *
 *   pmc-valkyrie.c -- Console support क्रम PowerMac "valkyrie" display adaptor.
 *   Copyright (C) 1997 Paul Mackerras.
 *
 *  and indirectly:
 *
 *  Frame buffer काष्ठाure from:
 *    drivers/video/chipsfb.c -- frame buffer device क्रम
 *    Chips & Technologies 65550 chip.
 *
 *    Copyright (C) 1998 Paul Mackerras
 *
 *    This file is derived from the Powermac "chips" driver:
 *    Copyright (C) 1997 Fabio Riccardi.
 *    And from the frame buffer device क्रम Open Firmware-initialized devices:
 *    Copyright (C) 1997 Geert Uytterhoeven.
 *
 *  Hardware inक्रमmation from:
 *    control.c: Console support क्रम PowerMac "control" display adaptor.
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/selection.h>
#समावेश <linux/init.h>
#समावेश <linux/nvram.h>
#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#अगर_घोषित CONFIG_MAC
#समावेश <यंत्र/macपूर्णांकosh.h>
#अन्यथा
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

#समावेश "macmodes.h"
#समावेश "valkyriefb.h"

अटल पूर्णांक शेष_vmode = VMODE_NVRAM;
अटल पूर्णांक शेष_cmode = CMODE_NVRAM;

काष्ठा fb_par_valkyrie अणु
	पूर्णांक	vmode, cmode;
	पूर्णांक	xres, yres;
	पूर्णांक	vxres, vyres;
	काष्ठा valkyrie_regvals *init;
पूर्ण;

काष्ठा fb_info_valkyrie अणु
	काष्ठा fb_info		info;
	काष्ठा fb_par_valkyrie	par;
	काष्ठा cmap_regs	__iomem *cmap_regs;
	अचिन्हित दीर्घ		cmap_regs_phys;
	
	काष्ठा valkyrie_regs	__iomem *valkyrie_regs;
	अचिन्हित दीर्घ		valkyrie_regs_phys;
	
	__u8			__iomem *frame_buffer;
	अचिन्हित दीर्घ		frame_buffer_phys;
	
	पूर्णांक			sense;
	अचिन्हित दीर्घ		total_vram;

	u32			pseuकरो_palette[16];
पूर्ण;

/*
 * Exported functions
 */
पूर्णांक valkyriefb_init(व्योम);
पूर्णांक valkyriefb_setup(अक्षर*);

अटल पूर्णांक valkyriefb_check_var(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info);
अटल पूर्णांक valkyriefb_set_par(काष्ठा fb_info *info);
अटल पूर्णांक valkyriefb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			     u_पूर्णांक transp, काष्ठा fb_info *info);
अटल पूर्णांक valkyriefb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info);

अटल पूर्णांक पढ़ो_valkyrie_sense(काष्ठा fb_info_valkyrie *p);
अटल व्योम set_valkyrie_घड़ी(अचिन्हित अक्षर *params);
अटल पूर्णांक valkyrie_var_to_par(काष्ठा fb_var_screeninfo *var,
	काष्ठा fb_par_valkyrie *par, स्थिर काष्ठा fb_info *fb_info);

अटल पूर्णांक valkyrie_init_info(काष्ठा fb_info *info, काष्ठा fb_info_valkyrie *p);
अटल व्योम valkyrie_par_to_fix(काष्ठा fb_par_valkyrie *par, काष्ठा fb_fix_screeninfo *fix);
अटल व्योम valkyrie_init_fix(काष्ठा fb_fix_screeninfo *fix, काष्ठा fb_info_valkyrie *p);

अटल स्थिर काष्ठा fb_ops valkyriefb_ops = अणु
	.owner =	THIS_MODULE,
	.fb_check_var =	valkyriefb_check_var,
	.fb_set_par =	valkyriefb_set_par,
	.fb_setcolreg =	valkyriefb_setcolreg,
	.fb_blank =	valkyriefb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

/* Sets the video mode according to info->var */
अटल पूर्णांक valkyriefb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा fb_info_valkyrie *p =
		container_of(info, काष्ठा fb_info_valkyrie, info);
	अस्थिर काष्ठा valkyrie_regs __iomem *valkyrie_regs = p->valkyrie_regs;
	काष्ठा fb_par_valkyrie *par = info->par;
	काष्ठा valkyrie_regvals	*init;
	पूर्णांक err;

	अगर ((err = valkyrie_var_to_par(&info->var, par, info)))
		वापस err;

	valkyrie_par_to_fix(par, &info->fix);

	/* Reset the valkyrie */
	out_8(&valkyrie_regs->status.r, 0);
	udelay(100);

	/* Initialize display timing रेजिस्टरs */
	init = par->init;
	out_8(&valkyrie_regs->mode.r, init->mode | 0x80);
	out_8(&valkyrie_regs->depth.r, par->cmode + 3);
	set_valkyrie_घड़ी(init->घड़ी_params);
	udelay(100);

	/* Turn on display */
	out_8(&valkyrie_regs->mode.r, init->mode);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक valkyrie_par_to_var(काष्ठा fb_par_valkyrie *par,
				      काष्ठा fb_var_screeninfo *var)
अणु
	वापस mac_vmode_to_var(par->vmode, par->cmode, var);
पूर्ण

अटल पूर्णांक
valkyriefb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	पूर्णांक err;
	काष्ठा fb_par_valkyrie par;

	अगर ((err = valkyrie_var_to_par(var, &par, info)))
		वापस err;
	valkyrie_par_to_var(&par, var);
	वापस 0;
पूर्ण

/*
 *  Blank the screen अगर blank_mode != 0, अन्यथा unblank. If blank_mode == शून्य
 *  then the caller blanks by setting the CLUT (Color Look Up Table) to all
 *  black. Return 0 अगर blanking succeeded, != 0 अगर un-/blanking failed due
 *  to e.g. a video mode which करोesn't support it. Implements VESA suspend
 *  and घातerकरोwn modes on hardware that supports disabling hsync/vsync:
 *    blank_mode == 2: suspend vsync
 *    blank_mode == 3: suspend hsync
 *    blank_mode == 4: घातerकरोwn
 */
अटल पूर्णांक valkyriefb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा fb_info_valkyrie *p =
		container_of(info, काष्ठा fb_info_valkyrie, info);
	काष्ठा fb_par_valkyrie *par = info->par;
	काष्ठा valkyrie_regvals	*init = par->init;

	अगर (init == शून्य)
		वापस 1;

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:			/* unblank */
		out_8(&p->valkyrie_regs->mode.r, init->mode);
		अवरोध;
	हाल FB_BLANK_NORMAL:
		वापस 1;	/* get caller to set CLUT to all black */
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
		/*
		 * [kps] Value extracted from MacOS. I करोn't know
		 * whether this bit disables hsync or vsync, or
		 * whether the hardware can करो the other as well.
		 */
		out_8(&p->valkyrie_regs->mode.r, init->mode | 0x40);
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		out_8(&p->valkyrie_regs->mode.r, 0x66);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक valkyriefb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			     u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा fb_info_valkyrie *p =
		container_of(info, काष्ठा fb_info_valkyrie, info);
	अस्थिर काष्ठा cmap_regs __iomem *cmap_regs = p->cmap_regs;
	काष्ठा fb_par_valkyrie *par = info->par;

	अगर (regno > 255)
		वापस 1;
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	/* tell clut which address to fill */
	out_8(&p->cmap_regs->addr, regno);
	udelay(1);
	/* send one color channel at a समय */
	out_8(&cmap_regs->lut, red);
	out_8(&cmap_regs->lut, green);
	out_8(&cmap_regs->lut, blue);

	अगर (regno < 16 && par->cmode == CMODE_16)
		((u32 *)info->pseuकरो_palette)[regno] =
			(regno << 10) | (regno << 5) | regno;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक valkyrie_vram_reqd(पूर्णांक video_mode, पूर्णांक color_mode)
अणु
	पूर्णांक pitch;
	काष्ठा valkyrie_regvals *init = valkyrie_reg_init[video_mode-1];
	
	अगर ((pitch = init->pitch[color_mode]) == 0)
		pitch = 2 * init->pitch[0];
	वापस init->vres * pitch;
पूर्ण

अटल व्योम set_valkyrie_घड़ी(अचिन्हित अक्षर *params)
अणु
#अगर_घोषित CONFIG_ADB_CUDA
	काष्ठा adb_request req;
	पूर्णांक i;

	क्रम (i = 0; i < 3; ++i) अणु
		cuda_request(&req, शून्य, 5, CUDA_PACKET, CUDA_GET_SET_IIC,
			     0x50, i + 1, params[i]);
		जबतक (!req.complete)
			cuda_poll();
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init valkyrie_choose_mode(काष्ठा fb_info_valkyrie *p)
अणु
	p->sense = पढ़ो_valkyrie_sense(p);
	prपूर्णांकk(KERN_INFO "Monitor sense value = 0x%x\n", p->sense);

	/* Try to pick a video mode out of NVRAM अगर we have one. */
#अगर_घोषित CONFIG_PPC_PMAC
	अगर (IS_REACHABLE(CONFIG_NVRAM) && शेष_vmode == VMODE_NVRAM)
		शेष_vmode = nvram_पढ़ो_byte(NV_VMODE);
#पूर्ण_अगर
	अगर (शेष_vmode <= 0 || शेष_vmode > VMODE_MAX ||
	    !valkyrie_reg_init[शेष_vmode - 1]) अणु
		शेष_vmode = mac_map_monitor_sense(p->sense);
		अगर (!valkyrie_reg_init[शेष_vmode - 1])
			शेष_vmode = VMODE_640_480_67;
	पूर्ण

#अगर_घोषित CONFIG_PPC_PMAC
	अगर (IS_REACHABLE(CONFIG_NVRAM) && शेष_cmode == CMODE_NVRAM)
		शेष_cmode = nvram_पढ़ो_byte(NV_CMODE);
#पूर्ण_अगर
	/*
	 * Reduce the pixel size अगर we करोn't have enough VRAM or bandwidth.
	 */
	अगर (शेष_cmode < CMODE_8 || शेष_cmode > CMODE_16
	    || valkyrie_reg_init[शेष_vmode-1]->pitch[शेष_cmode] == 0
	    || valkyrie_vram_reqd(शेष_vmode, शेष_cmode) > p->total_vram)
		शेष_cmode = CMODE_8;

	prपूर्णांकk(KERN_INFO "using video mode %d and color mode %d.\n",
	       शेष_vmode, शेष_cmode);
पूर्ण

पूर्णांक __init valkyriefb_init(व्योम)
अणु
	काष्ठा fb_info_valkyrie	*p;
	अचिन्हित दीर्घ frame_buffer_phys, cmap_regs_phys;
	पूर्णांक err;
	अक्षर *option = शून्य;

	अगर (fb_get_options("valkyriefb", &option))
		वापस -ENODEV;
	valkyriefb_setup(option);

#अगर_घोषित CONFIG_MAC
	अगर (!MACH_IS_MAC)
		वापस -ENODEV;
	अगर (!(mac_bi_data.id == MAC_MODEL_Q630
	      /* I'm not sure about this one */
	    || mac_bi_data.id == MAC_MODEL_P588))
		वापस -ENODEV;

	/* Hardcoded addresses... welcome to 68k Macपूर्णांकosh country :-) */
	frame_buffer_phys = 0xf9000000;
	cmap_regs_phys = 0x50f24000;
#अन्यथा /* ppc (!CONFIG_MAC) */
	अणु
		काष्ठा device_node *dp;
		काष्ठा resource r;

		dp = of_find_node_by_name(शून्य, "valkyrie");
		अगर (!dp)
			वापस 0;

		अगर (of_address_to_resource(dp, 0, &r)) अणु
			prपूर्णांकk(KERN_ERR "can't find address for valkyrie\n");
			वापस 0;
		पूर्ण

		frame_buffer_phys = r.start;
		cmap_regs_phys = r.start + 0x304000;
	पूर्ण
#पूर्ण_अगर /* ppc (!CONFIG_MAC) */

	p = kzalloc(माप(*p), GFP_ATOMIC);
	अगर (!p)
		वापस -ENOMEM;

	/* Map in frame buffer and रेजिस्टरs */
	अगर (!request_mem_region(frame_buffer_phys, 0x100000, "valkyriefb")) अणु
		kमुक्त(p);
		वापस 0;
	पूर्ण
	p->total_vram = 0x100000;
	p->frame_buffer_phys = frame_buffer_phys;
#अगर_घोषित CONFIG_MAC
	p->frame_buffer = ioremap(frame_buffer_phys, p->total_vram);
#अन्यथा
	p->frame_buffer = ioremap_wt(frame_buffer_phys, p->total_vram);
#पूर्ण_अगर
	p->cmap_regs_phys = cmap_regs_phys;
	p->cmap_regs = ioremap(p->cmap_regs_phys, 0x1000);
	p->valkyrie_regs_phys = cmap_regs_phys+0x6000;
	p->valkyrie_regs = ioremap(p->valkyrie_regs_phys, 0x1000);
	err = -ENOMEM;
	अगर (p->frame_buffer == शून्य || p->cmap_regs == शून्य
	    || p->valkyrie_regs == शून्य) अणु
		prपूर्णांकk(KERN_ERR "valkyriefb: couldn't map resources\n");
		जाओ out_मुक्त;
	पूर्ण

	valkyrie_choose_mode(p);
	mac_vmode_to_var(शेष_vmode, शेष_cmode, &p->info.var);
	err = valkyrie_init_info(&p->info, p);
	अगर (err < 0)
		जाओ out_मुक्त;
	valkyrie_init_fix(&p->info.fix, p);
	अगर (valkyriefb_set_par(&p->info))
		/* "can't happen" */
		prपूर्णांकk(KERN_ERR "valkyriefb: can't set default video mode\n");

	अगर ((err = रेजिस्टर_framebuffer(&p->info)) != 0)
		जाओ out_cmap_मुक्त;

	fb_info(&p->info, "valkyrie frame buffer device\n");
	वापस 0;

 out_cmap_मुक्त:
	fb_dealloc_cmap(&p->info.cmap);
 out_मुक्त:
	अगर (p->frame_buffer)
		iounmap(p->frame_buffer);
	अगर (p->cmap_regs)
		iounmap(p->cmap_regs);
	अगर (p->valkyrie_regs)
		iounmap(p->valkyrie_regs);
	kमुक्त(p);
	वापस err;
पूर्ण

/*
 * Get the monitor sense value.
 */
अटल पूर्णांक पढ़ो_valkyrie_sense(काष्ठा fb_info_valkyrie *p)
अणु
	पूर्णांक sense, in;

	out_8(&p->valkyrie_regs->msense.r, 0);   /* release all lines */
	__delay(20000);
	sense = ((in = in_8(&p->valkyrie_regs->msense.r)) & 0x70) << 4;
	/* drive each sense line low in turn and collect the other 2 */
	out_8(&p->valkyrie_regs->msense.r, 4);   /* drive A low */
	__delay(20000);
	sense |= ((in = in_8(&p->valkyrie_regs->msense.r)) & 0x30);
	out_8(&p->valkyrie_regs->msense.r, 2);   /* drive B low */
	__delay(20000);
	sense |= ((in = in_8(&p->valkyrie_regs->msense.r)) & 0x40) >> 3;
	sense |= (in & 0x10) >> 2;
	out_8(&p->valkyrie_regs->msense.r, 1);   /* drive C low */
	__delay(20000);
	sense |= ((in = in_8(&p->valkyrie_regs->msense.r)) & 0x60) >> 5;

	out_8(&p->valkyrie_regs->msense.r, 7);

	वापस sense;
पूर्ण

/*
 * This routine takes a user-supplied var,
 * and picks the best vmode/cmode from it.
 */

/* [bkn] I did a major overhaul of this function.
 *
 * Much of the old code was "swiped by jonh from atyfb.c". Because
 * macmodes has mac_var_to_vmode, I felt that it would be better to
 * rework this function to use that, instead of reinventing the wheel to
 * add support क्रम vmode 17. This was reinक्रमced by the fact that
 * the previously swiped atyfb.c code is no दीर्घer there.
 *
 * So, I swiped and adapted platinum_var_to_par (from platinumfb.c), replacing
 * most, but not all, of the old code in the process. One side benefit of
 * swiping the platinumfb code is that we now have more comprehensible error
 * messages when a vmode/cmode चयन fails. (Most of the error messages are
 * platinumfb.c, but I added two of my own, and I also changed some commas
 * पूर्णांकo colons to make the messages more consistent with other Linux error
 * messages.) In addition, I think the new code *might* fix some vmode-
 * चयनing oddities, but I'm not sure.
 *
 * There may be some more opportunities क्रम cleanup in here, but this is a
 * good start...
 */

अटल पूर्णांक valkyrie_var_to_par(काष्ठा fb_var_screeninfo *var,
	काष्ठा fb_par_valkyrie *par, स्थिर काष्ठा fb_info *fb_info)
अणु
	पूर्णांक vmode, cmode;
	काष्ठा valkyrie_regvals *init;
	काष्ठा fb_info_valkyrie *p =
		container_of(fb_info, काष्ठा fb_info_valkyrie, info);

	अगर (mac_var_to_vmode(var, &vmode, &cmode) != 0) अणु
		prपूर्णांकk(KERN_ERR "valkyriefb: can't do %dx%dx%d.\n",
		       var->xres, var->yres, var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	/* Check अगर we know about the wanted video mode */
	अगर (vmode < 1 || vmode > VMODE_MAX || !valkyrie_reg_init[vmode-1]) अणु
		prपूर्णांकk(KERN_ERR "valkyriefb: vmode %d not valid.\n", vmode);
		वापस -EINVAL;
	पूर्ण
	
	अगर (cmode != CMODE_8 && cmode != CMODE_16) अणु
		prपूर्णांकk(KERN_ERR "valkyriefb: cmode %d not valid.\n", cmode);
		वापस -EINVAL;
	पूर्ण

	अगर (var->xres_भव > var->xres || var->yres_भव > var->yres
	    || var->xoffset != 0 || var->yoffset != 0) अणु
		वापस -EINVAL;
	पूर्ण

	init = valkyrie_reg_init[vmode-1];
	अगर (init->pitch[cmode] == 0) अणु
		prपूर्णांकk(KERN_ERR "valkyriefb: vmode %d does not support "
		       "cmode %d.\n", vmode, cmode);
		वापस -EINVAL;
	पूर्ण

	अगर (valkyrie_vram_reqd(vmode, cmode) > p->total_vram) अणु
		prपूर्णांकk(KERN_ERR "valkyriefb: not enough ram for vmode %d, "
		       "cmode %d.\n", vmode, cmode);
		वापस -EINVAL;
	पूर्ण

	par->vmode = vmode;
	par->cmode = cmode;
	par->init = init;
	par->xres = var->xres;
	par->yres = var->yres;
	par->vxres = par->xres;
	par->vyres = par->yres;

	वापस 0;
पूर्ण

अटल व्योम valkyrie_init_fix(काष्ठा fb_fix_screeninfo *fix, काष्ठा fb_info_valkyrie *p)
अणु
	स_रखो(fix, 0, माप(*fix));
	म_नकल(fix->id, "valkyrie");
	fix->mmio_start = p->valkyrie_regs_phys;
	fix->mmio_len = माप(काष्ठा valkyrie_regs);
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->smem_start = p->frame_buffer_phys + 0x1000;
	fix->smem_len = p->total_vram;

	fix->type_aux = 0;
	fix->ywrapstep = 0;
	fix->ypanstep = 0;
	fix->xpanstep = 0;
	
पूर्ण

/* Fix must alपढ़ोy be inited above */
अटल व्योम valkyrie_par_to_fix(काष्ठा fb_par_valkyrie *par,
	काष्ठा fb_fix_screeninfo *fix)
अणु
	fix->smem_len = valkyrie_vram_reqd(par->vmode, par->cmode);
	fix->visual = (par->cmode == CMODE_8) ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_सूचीECTCOLOR;
	fix->line_length = par->vxres << par->cmode;
		/* ywrapstep, xpanstep, ypanstep */
पूर्ण

अटल पूर्णांक __init valkyrie_init_info(काष्ठा fb_info *info,
		काष्ठा fb_info_valkyrie *p)
अणु
	info->fbops = &valkyriefb_ops;
	info->screen_base = p->frame_buffer + 0x1000;
	info->flags = FBINFO_DEFAULT;
	info->pseuकरो_palette = p->pseuकरो_palette;
	info->par = &p->par;
	वापस fb_alloc_cmap(&info->cmap, 256, 0);
पूर्ण


/*
 * Parse user specअगरied options (`video=valkyriefb:')
 */
पूर्णांक __init valkyriefb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "vmode:", 6)) अणु
	    		पूर्णांक vmode = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			अगर (vmode > 0 && vmode <= VMODE_MAX)
				शेष_vmode = vmode;
		पूर्ण
		अन्यथा अगर (!म_भेदन(this_opt, "cmode:", 6)) अणु
			पूर्णांक depth = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			चयन (depth) अणु
			हाल 8:
				शेष_cmode = CMODE_8;
				अवरोध;
			हाल 15:
			हाल 16:
				शेष_cmode = CMODE_16;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

module_init(valkyriefb_init);
MODULE_LICENSE("GPL");
