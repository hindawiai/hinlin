<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * macfb.c: Generic framebuffer क्रम Macs whose colourmaps/modes we
 * करोn't know how to set.
 *
 * (c) 1999 David Huggins-Daines <dhd@debian.org>
 *
 * Primarily based on vesafb.c, by Gerd Knorr
 * (c) 1998 Gerd Knorr <kraxel@cs.tu-berlin.de>
 *
 * Also uses inक्रमmation and code from:
 *
 * The original macfb.c from Linux/mac68k 2.0, by Alan Cox, Juergen
 * Mellinger, Mikael Forselius, Michael Schmitz, and others.
 *
 * valkyriefb.c, by Martin Costabel, Kevin Schoedel, Barry Nathan, Dan
 * Jacobowitz, Paul Mackerras, Fabio Riccardi, and Geert Uytterhoeven.
 *
 * The VideoToolbox "Bugs" web page at
 * http://rajsky.psych.nyu.edu/Tips/VideoBugs.hपंचांगl
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/nubus.h>
#समावेश <linux/init.h>
#समावेश <linux/fb.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/पन.स>

/* Common DAC base address क्रम the LC, RBV, Valkyrie, and IIvx */
#घोषणा DAC_BASE 0x50f24000

/* Some addresses क्रम the DAFB */
#घोषणा DAFB_BASE 0xf9800200

/* Address क्रम the built-in Civic framebuffer in Quadra AVs */
#घोषणा CIVIC_BASE 0x50f30800

/* GSC (Gray Scale Controller) base address */
#घोषणा GSC_BASE 0x50F20000

/* CSC (Color Screen Controller) base address */
#घोषणा CSC_BASE 0x50F20000

अटल पूर्णांक (*macfb_setpalette)(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			       अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			       काष्ठा fb_info *info);

अटल काष्ठा अणु
	अचिन्हित अक्षर addr;
	अचिन्हित अक्षर lut;
पूर्ण __iomem *v8_brazil_cmap_regs;

अटल काष्ठा अणु
	अचिन्हित अक्षर addr;
	अक्षर pad1[3]; /* word aligned */
	अचिन्हित अक्षर lut;
	अक्षर pad2[3]; /* word aligned */
	अचिन्हित अक्षर cntl; /* a guess as to purpose */
पूर्ण __iomem *rbv_cmap_regs;

अटल काष्ठा अणु
	अचिन्हित दीर्घ reset;
	अचिन्हित दीर्घ pad1[3];
	अचिन्हित अक्षर pad2[3];
	अचिन्हित अक्षर lut;
पूर्ण __iomem *dafb_cmap_regs;

अटल काष्ठा अणु
	अचिन्हित अक्षर addr;	/* OFFSET: 0x00 */
	अचिन्हित अक्षर pad1[15];
	अचिन्हित अक्षर lut;	/* OFFSET: 0x10 */
	अचिन्हित अक्षर pad2[15];
	अचिन्हित अक्षर status;	/* OFFSET: 0x20 */
	अचिन्हित अक्षर pad3[7];
	अचिन्हित दीर्घ vbl_addr;	/* OFFSET: 0x28 */
	अचिन्हित पूर्णांक  status2;	/* OFFSET: 0x2C */
पूर्ण __iomem *civic_cmap_regs;

अटल काष्ठा अणु
	अक्षर pad1[0x40];
	अचिन्हित अक्षर clut_waddr;	/* 0x40 */
	अक्षर pad2;
	अचिन्हित अक्षर clut_data;	/* 0x42 */
	अक्षर pad3[0x3];
	अचिन्हित अक्षर clut_raddr;	/* 0x46 */
पूर्ण __iomem *csc_cmap_regs;

/* The रेजिस्टरs in these काष्ठाs are in NuBus slot space */
काष्ठा mdc_cmap_regs अणु
	अक्षर pad1[0x200200];
	अचिन्हित अक्षर addr;
	अक्षर pad2[6];
	अचिन्हित अक्षर lut;
पूर्ण;

काष्ठा toby_cmap_regs अणु
	अक्षर pad1[0x90018];
	अचिन्हित अक्षर lut; /* TFBClutWDataReg, offset 0x90018 */
	अक्षर pad2[3];
	अचिन्हित अक्षर addr; /* TFBClutAddrReg, offset 0x9001C */
पूर्ण;

काष्ठा jet_cmap_regs अणु
	अक्षर pad1[0xe0e000];
	अचिन्हित अक्षर addr;
	अचिन्हित अक्षर lut;
पूर्ण;

#घोषणा PIXEL_TO_MM(a)	(((a)*10)/28)	/* width in mm at 72 dpi */

अटल काष्ठा fb_var_screeninfo macfb_defined = अणु
	.activate	= FB_ACTIVATE_NOW,
	.right_margin	= 32,
	.upper_margin	= 16,
	.lower_margin	= 4,
	.vsync_len	= 4,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल काष्ठा fb_fix_screeninfo macfb_fix = अणु
	.type	= FB_TYPE_PACKED_PIXELS,
	.accel	= FB_ACCEL_NONE,
पूर्ण;

अटल व्योम *slot_addr;
अटल काष्ठा fb_info fb_info;
अटल u32 pseuकरो_palette[16];
अटल पूर्णांक vidtest;

/*
 * Unlike the Valkyrie, the DAFB cannot set inभागidual colormap
 * रेजिस्टरs.  Thereक्रमe, we करो what the MacOS driver करोes (no
 * kidding!) and simply set them one by one until we hit the one we
 * want.
 */
अटल पूर्णांक dafb_setpalette(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			   अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			   काष्ठा fb_info *info)
अणु
	अटल पूर्णांक lastreg = -2;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/*
	 * fbdev will set an entire colourmap, but X won't.  Hopefully
	 * this should accommodate both of them
	 */
	अगर (regno != lastreg + 1) अणु
		पूर्णांक i;

		/* Stab in the dark trying to reset the CLUT poपूर्णांकer */
		nubus_ग_लिखोl(0, &dafb_cmap_regs->reset);
		nop();

		/* Loop until we get to the रेजिस्टर we want */
		क्रम (i = 0; i < regno; i++) अणु
			nubus_ग_लिखोb(info->cmap.red[i] >> 8,
				     &dafb_cmap_regs->lut);
			nop();
			nubus_ग_लिखोb(info->cmap.green[i] >> 8,
				     &dafb_cmap_regs->lut);
			nop();
			nubus_ग_लिखोb(info->cmap.blue[i] >> 8,
				     &dafb_cmap_regs->lut);
			nop();
		पूर्ण
	पूर्ण

	nubus_ग_लिखोb(red, &dafb_cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(green, &dafb_cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(blue, &dafb_cmap_regs->lut);

	local_irq_restore(flags);
	lastreg = regno;
	वापस 0;
पूर्ण

/* V8 and Brazil seem to use the same DAC.  Sonora करोes as well. */
अटल पूर्णांक v8_brazil_setpalette(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
				अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
				काष्ठा fb_info *info)
अणु
	अचिन्हित पूर्णांक bpp = info->var.bits_per_pixel;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* On these chips, the CLUT रेजिस्टर numbers are spपढ़ो out
	 * across the रेजिस्टर space.  Thus:
	 * In 8bpp, all regnos are valid.
	 * In 4bpp, the regnos are 0x0f, 0x1f, 0x2f, etc, etc
	 * In 2bpp, the regnos are 0x3f, 0x7f, 0xbf, 0xff
	 */
	regno = (regno << (8 - bpp)) | (0xFF >> bpp);
	nubus_ग_लिखोb(regno, &v8_brazil_cmap_regs->addr);
	nop();

	/* send one color channel at a समय */
	nubus_ग_लिखोb(red, &v8_brazil_cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(green, &v8_brazil_cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(blue, &v8_brazil_cmap_regs->lut);

	local_irq_restore(flags);
	वापस 0;
पूर्ण

/* RAM-Based Video */
अटल पूर्णांक rbv_setpalette(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			  अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			  काष्ठा fb_info *info)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* From the VideoToolbox driver.  Seems to be saying that
	 * regno #254 and #255 are the important ones क्रम 1-bit color,
	 * regno #252-255 are the important ones क्रम 2-bit color, etc.
	 */
	regno += 256 - (1 << info->var.bits_per_pixel);

	/* reset clut? (VideoToolbox sez "not necessary") */
	nubus_ग_लिखोb(0xFF, &rbv_cmap_regs->cntl);
	nop();

	/* tell clut which address to use. */
	nubus_ग_लिखोb(regno, &rbv_cmap_regs->addr);
	nop();

	/* send one color channel at a समय. */
	nubus_ग_लिखोb(red, &rbv_cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(green, &rbv_cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(blue, &rbv_cmap_regs->lut);

	local_irq_restore(flags);
	वापस 0;
पूर्ण

/* Macपूर्णांकosh Display Card (8*24) */
अटल पूर्णांक mdc_setpalette(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			  अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			  काष्ठा fb_info *info)
अणु
	काष्ठा mdc_cmap_regs *cmap_regs = slot_addr;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* the nop's are there to order ग_लिखोs. */
	nubus_ग_लिखोb(regno, &cmap_regs->addr);
	nop();
	nubus_ग_लिखोb(red, &cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(green, &cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(blue, &cmap_regs->lut);

	local_irq_restore(flags);
	वापस 0;
पूर्ण

/* Toby frame buffer */
अटल पूर्णांक toby_setpalette(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			   अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			   काष्ठा fb_info *info)
अणु
	काष्ठा toby_cmap_regs *cmap_regs = slot_addr;
	अचिन्हित पूर्णांक bpp = info->var.bits_per_pixel;
	अचिन्हित दीर्घ flags;

	red = ~red;
	green = ~green;
	blue = ~blue;
	regno = (regno << (8 - bpp)) | (0xFF >> bpp);

	local_irq_save(flags);

	nubus_ग_लिखोb(regno, &cmap_regs->addr);
	nop();
	nubus_ग_लिखोb(red, &cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(green, &cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(blue, &cmap_regs->lut);

	local_irq_restore(flags);
	वापस 0;
पूर्ण

/* Jet frame buffer */
अटल पूर्णांक jet_setpalette(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			  अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			  काष्ठा fb_info *info)
अणु
	काष्ठा jet_cmap_regs *cmap_regs = slot_addr;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	nubus_ग_लिखोb(regno, &cmap_regs->addr);
	nop();
	nubus_ग_लिखोb(red, &cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(green, &cmap_regs->lut);
	nop();
	nubus_ग_लिखोb(blue, &cmap_regs->lut);

	local_irq_restore(flags);
	वापस 0;
पूर्ण

/*
 * Civic framebuffer -- Quadra AV built-in video.  A chip
 * called Sebastian holds the actual color palettes, and
 * apparently, there are two dअगरferent banks of 512K RAM
 * which can act as separate framebuffers क्रम करोing video
 * input and viewing the screen at the same समय!  The 840AV
 * Can add another 1MB RAM to give the two framebuffers
 * 1MB RAM apiece.
 */
अटल पूर्णांक civic_setpalette(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			    अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			    काष्ठा fb_info *info)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक clut_status;
	
	local_irq_save(flags);

	/* Set the रेजिस्टर address */
	nubus_ग_लिखोb(regno, &civic_cmap_regs->addr);
	nop();

	/*
	 * Grab a status word and करो some checking;
	 * Then finally ग_लिखो the clut!
	 */
	clut_status =  nubus_पढ़ोb(&civic_cmap_regs->status2);

	अगर ((clut_status & 0x0008) == 0)
	अणु
#अगर 0
		अगर ((clut_status & 0x000D) != 0)
		अणु
			nubus_ग_लिखोb(0x00, &civic_cmap_regs->lut);
			nop();
			nubus_ग_लिखोb(0x00, &civic_cmap_regs->lut);
			nop();
		पूर्ण
#पूर्ण_अगर

		nubus_ग_लिखोb(red, &civic_cmap_regs->lut);
		nop();
		nubus_ग_लिखोb(green, &civic_cmap_regs->lut);
		nop();
		nubus_ग_लिखोb(blue, &civic_cmap_regs->lut);
		nop();
		nubus_ग_लिखोb(0x00, &civic_cmap_regs->lut);
	पूर्ण
	अन्यथा
	अणु
		अचिन्हित अक्षर junk;

		junk = nubus_पढ़ोb(&civic_cmap_regs->lut);
		nop();
		junk = nubus_पढ़ोb(&civic_cmap_regs->lut);
		nop();
		junk = nubus_पढ़ोb(&civic_cmap_regs->lut);
		nop();
		junk = nubus_पढ़ोb(&civic_cmap_regs->lut);
		nop();

		अगर ((clut_status & 0x000D) != 0)
		अणु
			nubus_ग_लिखोb(0x00, &civic_cmap_regs->lut);
			nop();
			nubus_ग_लिखोb(0x00, &civic_cmap_regs->lut);
			nop();
		पूर्ण

		nubus_ग_लिखोb(red, &civic_cmap_regs->lut);
		nop();
		nubus_ग_लिखोb(green, &civic_cmap_regs->lut);
		nop();
		nubus_ग_लिखोb(blue, &civic_cmap_regs->lut);
		nop();
		nubus_ग_लिखोb(junk, &civic_cmap_regs->lut);
	पूर्ण

	local_irq_restore(flags);
	वापस 0;
पूर्ण

/*
 * The CSC is the framebuffer on the PowerBook 190 series
 * (and the 5300 too, but that's a PowerMac). This function
 * brought to you in part by the ECSC driver क्रम MkLinux.
 */
अटल पूर्णांक csc_setpalette(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			  अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			  काष्ठा fb_info *info)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	udelay(1); /* mklinux on PB 5300 रुकोs क्रम 260 ns */
	nubus_ग_लिखोb(regno, &csc_cmap_regs->clut_waddr);
	nubus_ग_लिखोb(red, &csc_cmap_regs->clut_data);
	nubus_ग_लिखोb(green, &csc_cmap_regs->clut_data);
	nubus_ग_लिखोb(blue, &csc_cmap_regs->clut_data);

	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल पूर्णांक macfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *fb_info)
अणु
	/*
	 * Set a single color रेजिस्टर. The values supplied are
	 * alपढ़ोy rounded करोwn to the hardware's capabilities
	 * (according to the entries in the `var' काष्ठाure).
	 * Return non-zero क्रम invalid regno.
	 */
	
	अगर (regno >= fb_info->cmap.len)
		वापस 1;

	अगर (fb_info->var.bits_per_pixel <= 8) अणु
		चयन (fb_info->var.bits_per_pixel) अणु
		हाल 1:
			/* We shouldn't get here */
			अवरोध;
		हाल 2:
		हाल 4:
		हाल 8:
			अगर (macfb_setpalette)
				macfb_setpalette(regno, red >> 8, green >> 8,
						 blue >> 8, fb_info);
			अन्यथा
				वापस 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (regno < 16) अणु
		चयन (fb_info->var.bits_per_pixel) अणु
		हाल 16:
			अगर (fb_info->var.red.offset == 10) अणु
				/* 1:5:5:5 */
				((u32*) (fb_info->pseuकरो_palette))[regno] =
					((red   & 0xf800) >>  1) |
					((green & 0xf800) >>  6) |
					((blue  & 0xf800) >> 11) |
					((transp != 0) << 15);
			पूर्ण अन्यथा अणु
				/* 0:5:6:5 */
				((u32*) (fb_info->pseuकरो_palette))[regno] =
					((red   & 0xf800) >>  0) |
					((green & 0xfc00) >>  5) |
					((blue  & 0xf800) >> 11);
			पूर्ण
			अवरोध;
		/*
		 * 24-bit colour almost करोesn't exist on 68k Macs --
		 * https://support.apple.com/kb/TA28634 (Old Article: 10992)
		 */
		हाल 24:
		हाल 32:
			red   >>= 8;
			green >>= 8;
			blue  >>= 8;
			((u32 *)(fb_info->pseuकरो_palette))[regno] =
				(red   << fb_info->var.red.offset) |
				(green << fb_info->var.green.offset) |
				(blue  << fb_info->var.blue.offset);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops macfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= macfb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल व्योम __init macfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;

		अगर (!म_भेद(this_opt, "inverse"))
			fb_invert_cmaps();
		अन्यथा
			अगर (!म_भेद(this_opt, "vidtest"))
				vidtest = 1; /* enable experimental CLUT code */
	पूर्ण
पूर्ण

अटल व्योम __init iounmap_macfb(व्योम)
अणु
	अगर (dafb_cmap_regs)
		iounmap(dafb_cmap_regs);
	अगर (v8_brazil_cmap_regs)
		iounmap(v8_brazil_cmap_regs);
	अगर (rbv_cmap_regs)
		iounmap(rbv_cmap_regs);
	अगर (civic_cmap_regs)
		iounmap(civic_cmap_regs);
	अगर (csc_cmap_regs)
		iounmap(csc_cmap_regs);
पूर्ण

अटल पूर्णांक __init macfb_init(व्योम)
अणु
	पूर्णांक video_cmap_len, video_is_nubus = 0;
	काष्ठा nubus_rsrc *ndev = शून्य;
	अक्षर *option = शून्य;
	पूर्णांक err;

	अगर (fb_get_options("macfb", &option))
		वापस -ENODEV;
	macfb_setup(option);

	अगर (!MACH_IS_MAC) 
		वापस -ENODEV;

	अगर (mac_bi_data.id == MAC_MODEL_Q630 ||
	    mac_bi_data.id == MAC_MODEL_P588)
		वापस -ENODEV; /* See valkyriefb.c */

	macfb_defined.xres = mac_bi_data.dimensions & 0xFFFF;
	macfb_defined.yres = mac_bi_data.dimensions >> 16;
	macfb_defined.bits_per_pixel = mac_bi_data.videodepth;

	macfb_fix.line_length = mac_bi_data.videorow;
	macfb_fix.smem_len    = macfb_fix.line_length * macfb_defined.yres;
	/* Note: physical address (since 2.1.127) */
	macfb_fix.smem_start  = mac_bi_data.videoaddr;

	/*
	 * This is actually redundant with the initial mappings.
	 * However, there are some non-obvious aspects to the way
	 * those mappings are set up, so this is in fact the safest
	 * way to ensure that this driver will work on every possible Mac
	 */
	fb_info.screen_base = ioremap(mac_bi_data.videoaddr,
				      macfb_fix.smem_len);
	अगर (!fb_info.screen_base)
		वापस -ENODEV;

	pr_info("macfb: framebuffer at 0x%08lx, mapped to 0x%p, size %dk\n",
	        macfb_fix.smem_start, fb_info.screen_base,
	        macfb_fix.smem_len / 1024);
	pr_info("macfb: mode is %dx%dx%d, linelength=%d\n",
	        macfb_defined.xres, macfb_defined.yres,
	        macfb_defined.bits_per_pixel, macfb_fix.line_length);

	/* Fill in the available video resolution */
	macfb_defined.xres_भव = macfb_defined.xres;
	macfb_defined.yres_भव = macfb_defined.yres;
	macfb_defined.height       = PIXEL_TO_MM(macfb_defined.yres);
	macfb_defined.width        = PIXEL_TO_MM(macfb_defined.xres);

	/* Some dummy values क्रम timing to make fbset happy */
	macfb_defined.pixघड़ी     = 10000000 / macfb_defined.xres *
				     1000 / macfb_defined.yres;
	macfb_defined.left_margin  = (macfb_defined.xres / 8) & 0xf8;
	macfb_defined.hsync_len    = (macfb_defined.xres / 8) & 0xf8;

	चयन (macfb_defined.bits_per_pixel) अणु
	हाल 1:
		macfb_defined.red.length = macfb_defined.bits_per_pixel;
		macfb_defined.green.length = macfb_defined.bits_per_pixel;
		macfb_defined.blue.length = macfb_defined.bits_per_pixel;
		video_cmap_len = 2;
		macfb_fix.visual = FB_VISUAL_MONO01;
		अवरोध;
	हाल 2:
	हाल 4:
	हाल 8:
		macfb_defined.red.length = macfb_defined.bits_per_pixel;
		macfb_defined.green.length = macfb_defined.bits_per_pixel;
		macfb_defined.blue.length = macfb_defined.bits_per_pixel;
		video_cmap_len = 1 << macfb_defined.bits_per_pixel;
		macfb_fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	हाल 16:
		macfb_defined.transp.offset = 15;
		macfb_defined.transp.length = 1;
		macfb_defined.red.offset = 10;
		macfb_defined.red.length = 5;
		macfb_defined.green.offset = 5;
		macfb_defined.green.length = 5;
		macfb_defined.blue.offset = 0;
		macfb_defined.blue.length = 5;
		video_cmap_len = 16;
		/*
		 * Should actually be FB_VISUAL_सूचीECTCOLOR, but this
		 * works too
		 */
		macfb_fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	हाल 24:
	हाल 32:
		macfb_defined.red.offset = 16;
		macfb_defined.red.length = 8;
		macfb_defined.green.offset = 8;
		macfb_defined.green.length = 8;
		macfb_defined.blue.offset = 0;
		macfb_defined.blue.length = 8;
		video_cmap_len = 16;
		macfb_fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	शेष:
		pr_err("macfb: unknown or unsupported bit depth: %d\n",
		       macfb_defined.bits_per_pixel);
		err = -EINVAL;
		जाओ fail_unmap;
	पूर्ण
	
	/*
	 * We take a wild guess that अगर the video physical address is
	 * in nubus slot space, that the nubus card is driving video.
	 * Penguin really ought to tell us whether we are using पूर्णांकernal
	 * video or not.
	 * Hopefully we only find one of them.  Otherwise our NuBus
	 * code is really broken :-)
	 */

	क्रम_each_func_rsrc(ndev) अणु
		अचिन्हित दीर्घ base = ndev->board->slot_addr;

		अगर (mac_bi_data.videoaddr < base ||
		    mac_bi_data.videoaddr - base > 0xFFFFFF)
			जारी;

		अगर (ndev->category != NUBUS_CAT_DISPLAY ||
		    ndev->type != NUBUS_TYPE_VIDEO)
			जारी;

		video_is_nubus = 1;
		slot_addr = (अचिन्हित अक्षर *)base;

		चयन(ndev->dr_hw) अणु
		हाल NUBUS_DRHW_APPLE_MDC:
			म_नकल(macfb_fix.id, "Mac Disp. Card");
			macfb_setpalette = mdc_setpalette;
			अवरोध;
		हाल NUBUS_DRHW_APPLE_TFB:
			म_नकल(macfb_fix.id, "Toby");
			macfb_setpalette = toby_setpalette;
			अवरोध;
		हाल NUBUS_DRHW_APPLE_JET:
			म_नकल(macfb_fix.id, "Jet");
			macfb_setpalette = jet_setpalette;
			अवरोध;
		शेष:
			म_नकल(macfb_fix.id, "Generic NuBus");
			अवरोध;
		पूर्ण
	पूर्ण

	/* If it's not a NuBus card, it must be पूर्णांकernal video */
	अगर (!video_is_nubus)
		चयन (mac_bi_data.id) अणु
		/*
		 * DAFB Quadras
		 * Note: these first four have the v7 DAFB, which is
		 * known to be rather unlike the ones used in the
		 * other models
		 */
		हाल MAC_MODEL_P475:
		हाल MAC_MODEL_P475F:
		हाल MAC_MODEL_P575:
		हाल MAC_MODEL_Q605:

		हाल MAC_MODEL_Q800:
		हाल MAC_MODEL_Q650:
		हाल MAC_MODEL_Q610:
		हाल MAC_MODEL_C650:
		हाल MAC_MODEL_C610:
		हाल MAC_MODEL_Q700:
		हाल MAC_MODEL_Q900:
		हाल MAC_MODEL_Q950:
			म_नकल(macfb_fix.id, "DAFB");
			macfb_setpalette = dafb_setpalette;
			dafb_cmap_regs = ioremap(DAFB_BASE, 0x1000);
			अवरोध;

		/*
		 * LC II uses the V8 framebuffer
		 */
		हाल MAC_MODEL_LCII:
			म_नकल(macfb_fix.id, "V8");
			macfb_setpalette = v8_brazil_setpalette;
			v8_brazil_cmap_regs = ioremap(DAC_BASE, 0x1000);
			अवरोध;

		/*
		 * IIvi, IIvx use the "Brazil" framebuffer (which is
		 * very much like the V8, it seems, and probably uses
		 * the same DAC)
		 */
		हाल MAC_MODEL_IIVI:
		हाल MAC_MODEL_IIVX:
		हाल MAC_MODEL_P600:
			म_नकल(macfb_fix.id, "Brazil");
			macfb_setpalette = v8_brazil_setpalette;
			v8_brazil_cmap_regs = ioremap(DAC_BASE, 0x1000);
			अवरोध;

		/*
		 * LC III (and मित्रs) use the Sonora framebuffer
		 * Incidentally this is also used in the non-AV models
		 * of the x100 PowerMacs
		 * These करो in fact seem to use the same DAC पूर्णांकerface
		 * as the LC II.
		 */
		हाल MAC_MODEL_LCIII:
		हाल MAC_MODEL_P520:
		हाल MAC_MODEL_P550:
		हाल MAC_MODEL_P460:
			म_नकल(macfb_fix.id, "Sonora");
			macfb_setpalette = v8_brazil_setpalette;
			v8_brazil_cmap_regs = ioremap(DAC_BASE, 0x1000);
			अवरोध;

		/*
		 * IIci and IIsi use the infamous RBV chip
		 * (the IIsi is just a rebadged and crippled
		 * IIci in a dअगरferent हाल, BTW)
		 */
		हाल MAC_MODEL_IICI:
		हाल MAC_MODEL_IISI:
			म_नकल(macfb_fix.id, "RBV");
			macfb_setpalette = rbv_setpalette;
			rbv_cmap_regs = ioremap(DAC_BASE, 0x1000);
			अवरोध;

		/*
		 * AVs use the Civic framebuffer
		 */
		हाल MAC_MODEL_Q840:
		हाल MAC_MODEL_C660:
			म_नकल(macfb_fix.id, "Civic");
			macfb_setpalette = civic_setpalette;
			civic_cmap_regs = ioremap(CIVIC_BASE, 0x1000);
			अवरोध;

		
		/*
		 * Assorted weirकरोs
		 * We think this may be like the LC II
		 */
		हाल MAC_MODEL_LC:
			म_नकल(macfb_fix.id, "LC");
			अगर (vidtest) अणु
				macfb_setpalette = v8_brazil_setpalette;
				v8_brazil_cmap_regs =
					ioremap(DAC_BASE, 0x1000);
			पूर्ण
			अवरोध;

		/*
		 * We think this may be like the LC II
		 */
		हाल MAC_MODEL_CCL:
			म_नकल(macfb_fix.id, "Color Classic");
			अगर (vidtest) अणु
				macfb_setpalette = v8_brazil_setpalette;
				v8_brazil_cmap_regs =
					ioremap(DAC_BASE, 0x1000);
			पूर्ण
			अवरोध;

		/*
		 * And we *करो* mean "weirdos"
		 */
		हाल MAC_MODEL_TV:
			म_नकल(macfb_fix.id, "Mac TV");
			अवरोध;

		/*
		 * These करोn't have colour, so no need to worry
		 */
		हाल MAC_MODEL_SE30:
		हाल MAC_MODEL_CLII:
			म_नकल(macfb_fix.id, "Monochrome");
			अवरोध;

		/*
		 * Powerbooks are particularly dअगरficult.  Many of
		 * them have separate framebuffers क्रम बाह्यal and
		 * पूर्णांकernal video, which is admittedly pretty cool,
		 * but will be a bit of a headache to support here.
		 * Also, many of them are grayscale, and we करोn't
		 * really support that.
		 */

		/*
		 * Slot 0 ROM says TIM. No बाह्यal video. B&W.
		 */
		हाल MAC_MODEL_PB140:
		हाल MAC_MODEL_PB145:
		हाल MAC_MODEL_PB170:
			म_नकल(macfb_fix.id, "DDC");
			अवरोध;

		/*
		 * Internal is GSC, External (अगर present) is ViSC
		 */
		हाल MAC_MODEL_PB150:	/* no बाह्यal video */
		हाल MAC_MODEL_PB160:
		हाल MAC_MODEL_PB165:
		हाल MAC_MODEL_PB180:
		हाल MAC_MODEL_PB210:
		हाल MAC_MODEL_PB230:
			म_नकल(macfb_fix.id, "GSC");
			अवरोध;

		/*
		 * Internal is TIM, External is ViSC
		 */
		हाल MAC_MODEL_PB165C:
		हाल MAC_MODEL_PB180C:
			म_नकल(macfb_fix.id, "TIM");
			अवरोध;

		/*
		 * Internal is CSC, External is Keystone+Ariel.
		 */
		हाल MAC_MODEL_PB190:	/* बाह्यal video is optional */
		हाल MAC_MODEL_PB520:
		हाल MAC_MODEL_PB250:
		हाल MAC_MODEL_PB270C:
		हाल MAC_MODEL_PB280:
		हाल MAC_MODEL_PB280C:
			म_नकल(macfb_fix.id, "CSC");
			macfb_setpalette = csc_setpalette;
			csc_cmap_regs = ioremap(CSC_BASE, 0x1000);
			अवरोध;

		शेष:
			म_नकल(macfb_fix.id, "Unknown");
			अवरोध;
		पूर्ण

	fb_info.fbops		= &macfb_ops;
	fb_info.var		= macfb_defined;
	fb_info.fix		= macfb_fix;
	fb_info.pseuकरो_palette	= pseuकरो_palette;
	fb_info.flags		= FBINFO_DEFAULT;

	err = fb_alloc_cmap(&fb_info.cmap, video_cmap_len, 0);
	अगर (err)
		जाओ fail_unmap;

	err = रेजिस्टर_framebuffer(&fb_info);
	अगर (err)
		जाओ fail_dealloc;

	fb_info(&fb_info, "%s frame buffer device\n", fb_info.fix.id);

	वापस 0;

fail_dealloc:
	fb_dealloc_cmap(&fb_info.cmap);
fail_unmap:
	iounmap(fb_info.screen_base);
	iounmap_macfb();
	वापस err;
पूर्ण

module_init(macfb_init);
MODULE_LICENSE("GPL");
