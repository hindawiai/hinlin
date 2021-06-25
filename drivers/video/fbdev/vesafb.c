<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * framebuffer driver क्रम VBE 2.0 compliant graphic boards
 *
 * चयनing to graphics mode happens at boot समय (जबतक
 * running in real mode, see arch/i386/boot/video.S).
 *
 * (c) 1998 Gerd Knorr <kraxel@goldbach.in-berlin.de>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/पन.स>

#समावेश <video/vga.h>

#घोषणा dac_reg	(0x3c8)
#घोषणा dac_val	(0x3c9)

/* --------------------------------------------------------------------- */

काष्ठा vesafb_par अणु
	u32 pseuकरो_palette[256];
	पूर्णांक wc_cookie;
	काष्ठा resource *region;
पूर्ण;

अटल काष्ठा fb_var_screeninfo vesafb_defined = अणु
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.right_margin	= 32,
	.upper_margin	= 16,
	.lower_margin	= 4,
	.vsync_len	= 4,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल काष्ठा fb_fix_screeninfo vesafb_fix = अणु
	.id	= "VESA VGA",
	.type	= FB_TYPE_PACKED_PIXELS,
	.accel	= FB_ACCEL_NONE,
पूर्ण;

अटल पूर्णांक   inverse    __पढ़ो_mostly;
अटल पूर्णांक   mtrr       __पढ़ो_mostly;		/* disable mtrr */
अटल पूर्णांक   vram_remap;			/* Set amount of memory to be used */
अटल पूर्णांक   vram_total;			/* Set total amount of memory */
अटल पूर्णांक   pmi_setpal __पढ़ो_mostly = 1;	/* pmi क्रम palette changes ??? */
अटल पूर्णांक   ypan       __पढ़ो_mostly;		/* 0..nothing, 1..ypan, 2..ywrap */
अटल व्योम  (*pmi_start)(व्योम) __पढ़ो_mostly;
अटल व्योम  (*pmi_pal)  (व्योम) __पढ़ो_mostly;
अटल पूर्णांक   depth      __पढ़ो_mostly;
अटल पूर्णांक   vga_compat __पढ़ो_mostly;
/* --------------------------------------------------------------------- */

अटल पूर्णांक vesafb_pan_display(काष्ठा fb_var_screeninfo *var,
                              काष्ठा fb_info *info)
अणु
#अगर_घोषित __i386__
	पूर्णांक offset;

	offset = (var->yoffset * info->fix.line_length + var->xoffset) / 4;

        __यंत्र__ __अस्थिर__(
                "call *(%%edi)"
                : /* no वापस value */
                : "a" (0x4f07),         /* EAX */
                  "b" (0),              /* EBX */
                  "c" (offset),         /* ECX */
                  "d" (offset >> 16),   /* EDX */
                  "D" (&pmi_start));    /* EDI */
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक vesa_setpalette(पूर्णांक regno, अचिन्हित red, अचिन्हित green,
			    अचिन्हित blue)
अणु
	पूर्णांक shअगरt = 16 - depth;
	पूर्णांक err = -EINVAL;

/*
 * Try VGA रेजिस्टरs first...
 */
	अगर (vga_compat) अणु
		outb_p(regno,       dac_reg);
		outb_p(red   >> shअगरt, dac_val);
		outb_p(green >> shअगरt, dac_val);
		outb_p(blue  >> shअगरt, dac_val);
		err = 0;
	पूर्ण

#अगर_घोषित __i386__
/*
 * Fallback to the PMI....
 */
	अगर (err && pmi_setpal) अणु
		काष्ठा अणु u_अक्षर blue, green, red, pad; पूर्ण entry;

		entry.red   = red   >> shअगरt;
		entry.green = green >> shअगरt;
		entry.blue  = blue  >> shअगरt;
		entry.pad   = 0;
	        __यंत्र__ __अस्थिर__(
                "call *(%%esi)"
                : /* no वापस value */
                : "a" (0x4f09),         /* EAX */
                  "b" (0),              /* EBX */
                  "c" (1),              /* ECX */
                  "d" (regno),          /* EDX */
                  "D" (&entry),         /* EDI */
                  "S" (&pmi_pal));      /* ESI */
		err = 0;
	पूर्ण
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल पूर्णांक vesafb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			    अचिन्हित blue, अचिन्हित transp,
			    काष्ठा fb_info *info)
अणु
	पूर्णांक err = 0;

	/*
	 *  Set a single color रेजिस्टर. The values supplied are
	 *  alपढ़ोy rounded करोwn to the hardware's capabilities
	 *  (according to the entries in the `var' काष्ठाure). Return
	 *  != 0 क्रम invalid regno.
	 */
	
	अगर (regno >= info->cmap.len)
		वापस 1;

	अगर (info->var.bits_per_pixel == 8)
		err = vesa_setpalette(regno,red,green,blue);
	अन्यथा अगर (regno < 16) अणु
		चयन (info->var.bits_per_pixel) अणु
		हाल 16:
			अगर (info->var.red.offset == 10) अणु
				/* 1:5:5:5 */
				((u32*) (info->pseuकरो_palette))[regno] =
					((red   & 0xf800) >>  1) |
					((green & 0xf800) >>  6) |
					((blue  & 0xf800) >> 11);
			पूर्ण अन्यथा अणु
				/* 0:5:6:5 */
				((u32*) (info->pseuकरो_palette))[regno] =
					((red   & 0xf800)      ) |
					((green & 0xfc00) >>  5) |
					((blue  & 0xf800) >> 11);
			पूर्ण
			अवरोध;
		हाल 24:
		हाल 32:
			red   >>= 8;
			green >>= 8;
			blue  >>= 8;
			((u32 *)(info->pseuकरो_palette))[regno] =
				(red   << info->var.red.offset)   |
				(green << info->var.green.offset) |
				(blue  << info->var.blue.offset);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम vesafb_destroy(काष्ठा fb_info *info)
अणु
	काष्ठा vesafb_par *par = info->par;

	fb_dealloc_cmap(&info->cmap);
	arch_phys_wc_del(par->wc_cookie);
	अगर (info->screen_base)
		iounmap(info->screen_base);
	release_mem_region(info->apertures->ranges[0].base, info->apertures->ranges[0].size);
पूर्ण

अटल काष्ठा fb_ops vesafb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_destroy     = vesafb_destroy,
	.fb_setcolreg	= vesafb_setcolreg,
	.fb_pan_display	= vesafb_pan_display,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक vesafb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;
	
	अगर (!options || !*options)
		वापस 0;
	
	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt) जारी;
		
		अगर (! म_भेद(this_opt, "inverse"))
			inverse=1;
		अन्यथा अगर (! म_भेद(this_opt, "redraw"))
			ypan=0;
		अन्यथा अगर (! म_भेद(this_opt, "ypan"))
			ypan=1;
		अन्यथा अगर (! म_भेद(this_opt, "ywrap"))
			ypan=2;
		अन्यथा अगर (! म_भेद(this_opt, "vgapal"))
			pmi_setpal=0;
		अन्यथा अगर (! म_भेद(this_opt, "pmipal"))
			pmi_setpal=1;
		अन्यथा अगर (! म_भेदन(this_opt, "mtrr:", 5))
			mtrr = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (! म_भेद(this_opt, "nomtrr"))
			mtrr=0;
		अन्यथा अगर (! म_भेदन(this_opt, "vtotal:", 7))
			vram_total = simple_म_से_अदीर्घ(this_opt+7, शून्य, 0);
		अन्यथा अगर (! म_भेदन(this_opt, "vremap:", 7))
			vram_remap = simple_म_से_अदीर्घ(this_opt+7, शून्य, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vesafb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा vesafb_par *par;
	पूर्णांक i, err;
	अचिन्हित पूर्णांक size_vmode;
	अचिन्हित पूर्णांक size_remap;
	अचिन्हित पूर्णांक माप_प्रकारotal;
	अक्षर *option = शून्य;

	/* ignore error वापस of fb_get_options */
	fb_get_options("vesafb", &option);
	vesafb_setup(option);

	अगर (screen_info.orig_video_isVGA != VIDEO_TYPE_VLFB)
		वापस -ENODEV;

	vga_compat = (screen_info.capabilities & 2) ? 0 : 1;
	vesafb_fix.smem_start = screen_info.lfb_base;
	vesafb_defined.bits_per_pixel = screen_info.lfb_depth;
	अगर (15 == vesafb_defined.bits_per_pixel)
		vesafb_defined.bits_per_pixel = 16;
	vesafb_defined.xres = screen_info.lfb_width;
	vesafb_defined.yres = screen_info.lfb_height;
	vesafb_fix.line_length = screen_info.lfb_linelength;
	vesafb_fix.visual   = (vesafb_defined.bits_per_pixel == 8) ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;

	/*   size_vmode -- that is the amount of memory needed क्रम the
	 *                 used video mode, i.e. the minimum amount of
	 *                 memory we need. */
	size_vmode = vesafb_defined.yres * vesafb_fix.line_length;

	/*   माप_प्रकारotal -- all video memory we have. Used क्रम mtrr
	 *                 entries, resource allocation and bounds
	 *                 checking. */
	माप_प्रकारotal = screen_info.lfb_size * 65536;
	अगर (vram_total)
		माप_प्रकारotal = vram_total * 1024 * 1024;
	अगर (माप_प्रकारotal < size_vmode)
		माप_प्रकारotal = size_vmode;

	/*   size_remap -- the amount of video memory we are going to
	 *                 use क्रम vesafb.  With modern cards it is no
	 *                 option to simply use माप_प्रकारotal as that
	 *                 wastes plenty of kernel address space. */
	size_remap  = size_vmode * 2;
	अगर (vram_remap)
		size_remap = vram_remap * 1024 * 1024;
	अगर (size_remap < size_vmode)
		size_remap = size_vmode;
	अगर (size_remap > माप_प्रकारotal)
		size_remap = माप_प्रकारotal;
	vesafb_fix.smem_len = size_remap;

#अगर_अघोषित __i386__
	screen_info.vesapm_seg = 0;
#पूर्ण_अगर

	अगर (!request_mem_region(vesafb_fix.smem_start, माप_प्रकारotal, "vesafb")) अणु
		prपूर्णांकk(KERN_WARNING
		       "vesafb: cannot reserve video memory at 0x%lx\n",
			vesafb_fix.smem_start);
		/* We cannot make this fatal. Someबार this comes from magic
		   spaces our resource handlers simply करोn't know about */
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा vesafb_par), &dev->dev);
	अगर (!info) अणु
		release_mem_region(vesafb_fix.smem_start, माप_प्रकारotal);
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(dev, info);
	par = info->par;
	info->pseuकरो_palette = par->pseuकरो_palette;

	/* set vesafb aperture size क्रम generic probing */
	info->apertures = alloc_apertures(1);
	अगर (!info->apertures) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण
	info->apertures->ranges[0].base = screen_info.lfb_base;
	info->apertures->ranges[0].size = माप_प्रकारotal;

	prपूर्णांकk(KERN_INFO "vesafb: mode is %dx%dx%d, linelength=%d, pages=%d\n",
	       vesafb_defined.xres, vesafb_defined.yres, vesafb_defined.bits_per_pixel, vesafb_fix.line_length, screen_info.pages);

	अगर (screen_info.vesapm_seg) अणु
		prपूर्णांकk(KERN_INFO "vesafb: protected mode interface info at %04x:%04x\n",
		       screen_info.vesapm_seg,screen_info.vesapm_off);
	पूर्ण

	अगर (screen_info.vesapm_seg < 0xc000)
		ypan = pmi_setpal = 0; /* not available or some DOS TSR ... */

	अगर (ypan || pmi_setpal) अणु
		अचिन्हित लघु *pmi_base;
		pmi_base  = (अचिन्हित लघु*)phys_to_virt(((अचिन्हित दीर्घ)screen_info.vesapm_seg << 4) + screen_info.vesapm_off);
		pmi_start = (व्योम*)((अक्षर*)pmi_base + pmi_base[1]);
		pmi_pal   = (व्योम*)((अक्षर*)pmi_base + pmi_base[2]);
		prपूर्णांकk(KERN_INFO "vesafb: pmi: set display start = %p, set palette = %p\n",pmi_start,pmi_pal);
		अगर (pmi_base[3]) अणु
			prपूर्णांकk(KERN_INFO "vesafb: pmi: ports = ");
			क्रम (i = pmi_base[3]/2; pmi_base[i] != 0xffff; i++)
				prपूर्णांकk("%x ", pmi_base[i]);
			prपूर्णांकk("\n");
			अगर (pmi_base[i] != 0xffff) अणु
				/*
				 * memory areas not supported (yet?)
				 *
				 * Rules are: we have to set up a descriptor क्रम the requested
				 * memory area and pass it in the ES रेजिस्टर to the BIOS function.
				 */
				prपूर्णांकk(KERN_INFO "vesafb: can't handle memory requests, pmi disabled\n");
				ypan = pmi_setpal = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (vesafb_defined.bits_per_pixel == 8 && !pmi_setpal && !vga_compat) अणु
		prपूर्णांकk(KERN_WARNING "vesafb: hardware palette is unchangeable,\n"
		                    "        colors may be incorrect\n");
		vesafb_fix.visual = FB_VISUAL_STATIC_PSEUDOCOLOR;
	पूर्ण

	vesafb_defined.xres_भव = vesafb_defined.xres;
	vesafb_defined.yres_भव = vesafb_fix.smem_len / vesafb_fix.line_length;
	अगर (ypan && vesafb_defined.yres_भव > vesafb_defined.yres) अणु
		prपूर्णांकk(KERN_INFO "vesafb: scrolling: %s using protected mode interface, yres_virtual=%d\n",
		       (ypan > 1) ? "ywrap" : "ypan",vesafb_defined.yres_भव);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "vesafb: scrolling: redraw\n");
		vesafb_defined.yres_भव = vesafb_defined.yres;
		ypan = 0;
	पूर्ण

	/* some dummy values क्रम timing to make fbset happy */
	vesafb_defined.pixघड़ी     = 10000000 / vesafb_defined.xres * 1000 / vesafb_defined.yres;
	vesafb_defined.left_margin  = (vesafb_defined.xres / 8) & 0xf8;
	vesafb_defined.hsync_len    = (vesafb_defined.xres / 8) & 0xf8;
	
	vesafb_defined.red.offset    = screen_info.red_pos;
	vesafb_defined.red.length    = screen_info.red_size;
	vesafb_defined.green.offset  = screen_info.green_pos;
	vesafb_defined.green.length  = screen_info.green_size;
	vesafb_defined.blue.offset   = screen_info.blue_pos;
	vesafb_defined.blue.length   = screen_info.blue_size;
	vesafb_defined.transp.offset = screen_info.rsvd_pos;
	vesafb_defined.transp.length = screen_info.rsvd_size;

	अगर (vesafb_defined.bits_per_pixel <= 8) अणु
		depth = vesafb_defined.green.length;
		vesafb_defined.red.length =
		vesafb_defined.green.length =
		vesafb_defined.blue.length =
		vesafb_defined.bits_per_pixel;
	पूर्ण

	prपूर्णांकk(KERN_INFO "vesafb: %s: "
	       "size=%d:%d:%d:%d, shift=%d:%d:%d:%d\n",
	       (vesafb_defined.bits_per_pixel > 8) ?
	       "Truecolor" : (vga_compat || pmi_setpal) ?
	       "Pseudocolor" : "Static Pseudocolor",
	       screen_info.rsvd_size,
	       screen_info.red_size,
	       screen_info.green_size,
	       screen_info.blue_size,
	       screen_info.rsvd_pos,
	       screen_info.red_pos,
	       screen_info.green_pos,
	       screen_info.blue_pos);

	vesafb_fix.ypanstep  = ypan     ? 1 : 0;
	vesafb_fix.ywrapstep = (ypan>1) ? 1 : 0;

	/* request failure करोes not faze us, as vgacon probably has this
	 * region alपढ़ोy (FIXME) */
	par->region = request_region(0x3c0, 32, "vesafb");

	अगर (mtrr == 3) अणु
		अचिन्हित पूर्णांक temp_size = माप_प्रकारotal;

		/* Find the largest घातer-of-two */
		temp_size = roundup_घात_of_two(temp_size);

		/* Try and find a घातer of two to add */
		करो अणु
			par->wc_cookie =
				arch_phys_wc_add(vesafb_fix.smem_start,
						 temp_size);
			temp_size >>= 1;
		पूर्ण जबतक (temp_size >= PAGE_SIZE && par->wc_cookie < 0);

		info->screen_base = ioremap_wc(vesafb_fix.smem_start, vesafb_fix.smem_len);
	पूर्ण अन्यथा अणु
		अगर (mtrr && mtrr != 3)
			WARN_ONCE(1, "Only MTRR_TYPE_WRCOMB (3) make sense\n");
		info->screen_base = ioremap(vesafb_fix.smem_start, vesafb_fix.smem_len);
	पूर्ण

	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR
		       "vesafb: abort, cannot ioremap video memory 0x%x @ 0x%lx\n",
			vesafb_fix.smem_len, vesafb_fix.smem_start);
		err = -EIO;
		जाओ err_release_region;
	पूर्ण

	prपूर्णांकk(KERN_INFO "vesafb: framebuffer at 0x%lx, mapped to 0x%p, "
	       "using %dk, total %dk\n",
	       vesafb_fix.smem_start, info->screen_base,
	       size_remap/1024, माप_प्रकारotal/1024);

	अगर (!ypan)
		vesafb_ops.fb_pan_display = शून्य;

	info->fbops = &vesafb_ops;
	info->var = vesafb_defined;
	info->fix = vesafb_fix;
	info->flags = FBINFO_FLAG_DEFAULT | FBINFO_MISC_FIRMWARE |
		(ypan ? FBINFO_HWACCEL_YPAN : 0);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		err = -ENOMEM;
		जाओ err_release_region;
	पूर्ण
	अगर (रेजिस्टर_framebuffer(info)<0) अणु
		err = -EINVAL;
		fb_dealloc_cmap(&info->cmap);
		जाओ err_release_region;
	पूर्ण
	fb_info(info, "%s frame buffer device\n", info->fix.id);
	वापस 0;
err_release_region:
	arch_phys_wc_del(par->wc_cookie);
	अगर (info->screen_base)
		iounmap(info->screen_base);
	अगर (par->region)
		release_region(0x3c0, 32);
err:
	framebuffer_release(info);
	release_mem_region(vesafb_fix.smem_start, माप_प्रकारotal);
	वापस err;
पूर्ण

अटल पूर्णांक vesafb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_framebuffer(info);
	अगर (((काष्ठा vesafb_par *)(info->par))->region)
		release_region(0x3c0, 32);
	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vesafb_driver = अणु
	.driver = अणु
		.name = "vesa-framebuffer",
	पूर्ण,
	.probe = vesafb_probe,
	.हटाओ = vesafb_हटाओ,
पूर्ण;

module_platक्रमm_driver(vesafb_driver);
MODULE_LICENSE("GPL");
