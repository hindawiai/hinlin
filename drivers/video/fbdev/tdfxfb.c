<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * tdfxfb.c
 *
 * Author: Hannu Mallat <hmallat@cc.hut.fi>
 *
 * Copyright तऊ 1999 Hannu Mallat
 * All rights reserved
 *
 * Created      : Thu Sep 23 18:17:43 1999, hmallat
 * Last modअगरied: Tue Nov  2 21:19:47 1999, hmallat
 *
 * I2C part copied from the i2c-vooकरोo3.c driver by:
 * Froकरो Looijaard <froकरोl@dds.nl>,
 * Philip Edelbrock <phil@netroedge.com>,
 * Ralph Metzler <rjkm@thp.uni-koeln.de>, and
 * Mark D. Studebaker <mdsxyz123@yahoo.com>
 *
 * Lots of the inक्रमmation here comes from the Daryll Strauss' Banshee
 * patches to the XF86 server, and the rest comes from the 3dfx
 * Banshee specअगरication. I'm very much indebted to Daryll क्रम his
 * work on the X server.
 *
 * Vooकरोo3 support was contributed Harold Oga. Lots of additions
 * (proper acceleration, 24 bpp, hardware cursor) and bug fixes by Attila
 * Kesmarki. Thanks guys!
 *
 * Vooकरोo1 and Vooकरोo2 support aren't relevant to this driver as they
 * behave very dअगरferently from the Vooकरोo3/4/5. For anyone wanting to
 * use frame buffer on the Vooकरोo1/2, see the sstfb driver (which is
 * located at http://www.sourceक्रमge.net/projects/sstfb).
 *
 * While I _am_ grateful to 3Dfx क्रम releasing the specs क्रम Banshee,
 * I करो wish the next version is a bit more complete. Without the XF86
 * patches I couldn't have gotten even this far... क्रम instance, the
 * extensions to the VGA रेजिस्टर set go completely unmentioned in the
 * spec! Also, lots of references are made to the 'SST core', but no
 * spec is खुलाly available, AFAIK.
 *
 * The काष्ठाure of this driver comes pretty much from the Permedia
 * driver by Ilario Nardinocchi, which in turn is based on skeletonfb.
 *
 * TODO:
 * - multihead support (basically need to support an array of fb_infos)
 * - support other architectures (PPC, Alpha); करोes the fact that the VGA
 *   core can be accessed only thru I/O (not memory mapped) complicate
 *   things?
 *
 * Version history:
 *
 * 0.1.4 (released 2002-05-28)	ported over to new fbdev api by James Simmons
 *
 * 0.1.3 (released 1999-11-02)	added Attila's panning support, code
 *				reorg, hwcursor address page size alignment
 *				(क्रम mmapping both frame buffer and regs),
 *				and my changes to get rid of hardcoded
 *				VGA i/o रेजिस्टर locations (uses PCI
 *				configuration info now)
 * 0.1.2 (released 1999-10-19)	added Attila Kesmarki's bug fixes and
 *				improvements
 * 0.1.1 (released 1999-10-07)	added Vooकरोo3 support by Harold Oga.
 * 0.1.0 (released 1999-10-06)	initial version
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>

#समावेश <video/tdfx.h>

#घोषणा DPRINTK(a, b...) pr_debug("fb: %s: " a, __func__ , ## b)

#घोषणा BANSHEE_MAX_PIXCLOCK 270000
#घोषणा VOODOO3_MAX_PIXCLOCK 300000
#घोषणा VOODOO5_MAX_PIXCLOCK 350000

अटल स्थिर काष्ठा fb_fix_screeninfo tdfx_fix = अणु
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_PSEUDOCOLOR,
	.ypanstep =	1,
	.ywrapstep =	1,
	.accel =	FB_ACCEL_3DFX_BANSHEE
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo tdfx_var = अणु
	/* "640x480, 8 bpp @ 60 Hz */
	.xres =		640,
	.yres =		480,
	.xres_भव =	640,
	.yres_भव =	1024,
	.bits_per_pixel = 8,
	.red =		अणु0, 8, 0पूर्ण,
	.blue =		अणु0, 8, 0पूर्ण,
	.green =	अणु0, 8, 0पूर्ण,
	.activate =	FB_ACTIVATE_NOW,
	.height =	-1,
	.width =	-1,
	.accel_flags =	FB_ACCELF_TEXT,
	.pixघड़ी =	39722,
	.left_margin =	40,
	.right_margin =	24,
	.upper_margin =	32,
	.lower_margin =	11,
	.hsync_len =	96,
	.vsync_len =	2,
	.vmode =	FB_VMODE_NONINTERLACED
पूर्ण;

/*
 * PCI driver prototypes
 */
अटल पूर्णांक tdfxfb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id);
अटल व्योम tdfxfb_हटाओ(काष्ठा pci_dev *pdev);

अटल स्थिर काष्ठा pci_device_id tdfxfb_id_table[] = अणु
	अणु PCI_VENDOR_ID_3DFX, PCI_DEVICE_ID_3DFX_BANSHEE,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_BASE_CLASS_DISPLAY << 16,
	  0xff0000, 0 पूर्ण,
	अणु PCI_VENDOR_ID_3DFX, PCI_DEVICE_ID_3DFX_VOODOO3,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_BASE_CLASS_DISPLAY << 16,
	  0xff0000, 0 पूर्ण,
	अणु PCI_VENDOR_ID_3DFX, PCI_DEVICE_ID_3DFX_VOODOO5,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_BASE_CLASS_DISPLAY << 16,
	  0xff0000, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver tdfxfb_driver = अणु
	.name		= "tdfxfb",
	.id_table	= tdfxfb_id_table,
	.probe		= tdfxfb_probe,
	.हटाओ		= tdfxfb_हटाओ,
पूर्ण;

MODULE_DEVICE_TABLE(pci, tdfxfb_id_table);

/*
 * Driver data
 */
अटल पूर्णांक nopan;
अटल पूर्णांक nowrap = 1;      /* not implemented (yet) */
अटल पूर्णांक hwcursor = 1;
अटल अक्षर *mode_option;
अटल bool nomtrr;

/* -------------------------------------------------------------------------
 *			Hardware-specअगरic funcions
 * ------------------------------------------------------------------------- */

अटल अंतरभूत u8 vga_inb(काष्ठा tdfx_par *par, u32 reg)
अणु
	वापस inb(par->iobase + reg - 0x300);
पूर्ण

अटल अंतरभूत व्योम vga_outb(काष्ठा tdfx_par *par, u32 reg, u8 val)
अणु
	outb(val, par->iobase + reg - 0x300);
पूर्ण

अटल अंतरभूत व्योम gra_outb(काष्ठा tdfx_par *par, u32 idx, u8 val)
अणु
	vga_outb(par, GRA_I, idx);
	wmb();
	vga_outb(par, GRA_D, val);
	wmb();
पूर्ण

अटल अंतरभूत व्योम seq_outb(काष्ठा tdfx_par *par, u32 idx, u8 val)
अणु
	vga_outb(par, SEQ_I, idx);
	wmb();
	vga_outb(par, SEQ_D, val);
	wmb();
पूर्ण

अटल अंतरभूत u8 seq_inb(काष्ठा tdfx_par *par, u32 idx)
अणु
	vga_outb(par, SEQ_I, idx);
	mb();
	वापस vga_inb(par, SEQ_D);
पूर्ण

अटल अंतरभूत व्योम crt_outb(काष्ठा tdfx_par *par, u32 idx, u8 val)
अणु
	vga_outb(par, CRT_I, idx);
	wmb();
	vga_outb(par, CRT_D, val);
	wmb();
पूर्ण

अटल अंतरभूत u8 crt_inb(काष्ठा tdfx_par *par, u32 idx)
अणु
	vga_outb(par, CRT_I, idx);
	mb();
	वापस vga_inb(par, CRT_D);
पूर्ण

अटल अंतरभूत व्योम att_outb(काष्ठा tdfx_par *par, u32 idx, u8 val)
अणु
	vga_inb(par, IS1_R);
	vga_outb(par, ATT_IW, idx);
	vga_outb(par, ATT_IW, val);
पूर्ण

अटल अंतरभूत व्योम vga_disable_video(काष्ठा tdfx_par *par)
अणु
	अचिन्हित अक्षर s;

	s = seq_inb(par, 0x01) | 0x20;
	seq_outb(par, 0x00, 0x01);
	seq_outb(par, 0x01, s);
	seq_outb(par, 0x00, 0x03);
पूर्ण

अटल अंतरभूत व्योम vga_enable_video(काष्ठा tdfx_par *par)
अणु
	अचिन्हित अक्षर s;

	s = seq_inb(par, 0x01) & 0xdf;
	seq_outb(par, 0x00, 0x01);
	seq_outb(par, 0x01, s);
	seq_outb(par, 0x00, 0x03);
पूर्ण

अटल अंतरभूत व्योम vga_enable_palette(काष्ठा tdfx_par *par)
अणु
	vga_inb(par, IS1_R);
	mb();
	vga_outb(par, ATT_IW, 0x20);
पूर्ण

अटल अंतरभूत u32 tdfx_inl(काष्ठा tdfx_par *par, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(par->regbase_virt + reg);
पूर्ण

अटल अंतरभूत व्योम tdfx_outl(काष्ठा tdfx_par *par, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, par->regbase_virt + reg);
पूर्ण

अटल अंतरभूत व्योम banshee_make_room(काष्ठा tdfx_par *par, पूर्णांक size)
अणु
	/* Note: The Vooकरोo3's onboard FIFO has 32 slots. This loop
	 * won't quit अगर you ask क्रम more. */
	जबतक ((tdfx_inl(par, STATUS) & 0x1f) < size - 1)
		cpu_relax();
पूर्ण

अटल पूर्णांक banshee_रुको_idle(काष्ठा fb_info *info)
अणु
	काष्ठा tdfx_par *par = info->par;
	पूर्णांक i = 0;

	banshee_make_room(par, 1);
	tdfx_outl(par, COMMAND_3D, COMMAND_3D_NOP);

	करो अणु
		अगर ((tdfx_inl(par, STATUS) & STATUS_BUSY) == 0)
			i++;
	पूर्ण जबतक (i < 3);

	वापस 0;
पूर्ण

/*
 * Set the color of a palette entry in 8bpp mode
 */
अटल अंतरभूत व्योम करो_setpalentry(काष्ठा tdfx_par *par, अचिन्हित regno, u32 c)
अणु
	banshee_make_room(par, 2);
	tdfx_outl(par, DACADDR, regno);
	/* पढ़ो after ग_लिखो makes it working */
	tdfx_inl(par, DACADDR);
	tdfx_outl(par, DACDATA, c);
पूर्ण

अटल u32 करो_calc_pll(पूर्णांक freq, पूर्णांक *freq_out)
अणु
	पूर्णांक m, n, k, best_m, best_n, best_k, best_error;
	पूर्णांक fref = 14318;

	best_error = freq;
	best_n = best_m = best_k = 0;

	क्रम (k = 3; k >= 0; k--) अणु
		क्रम (m = 63; m >= 0; m--) अणु
			/*
			 * Estimate value of n that produces target frequency
			 * with current m and k
			 */
			पूर्णांक n_estimated = ((freq * (m + 2) << k) / fref) - 2;

			/* Search neighborhood of estimated n */
			क्रम (n = max(0, n_estimated);
				n <= min(255, n_estimated + 1);
				n++) अणु
				/*
				 * Calculate PLL freqency with current m, k and
				 * estimated n
				 */
				पूर्णांक f = (fref * (n + 2) / (m + 2)) >> k;
				पूर्णांक error = असल(f - freq);

				/*
				 * If this is the बंदst we've come to the
				 * target frequency then remember n, m and k
				 */
				अगर (error < best_error) अणु
					best_error = error;
					best_n = n;
					best_m = m;
					best_k = k;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	n = best_n;
	m = best_m;
	k = best_k;
	*freq_out = (fref * (n + 2) / (m + 2)) >> k;

	वापस (n << 8) | (m << 2) | k;
पूर्ण

अटल व्योम करो_ग_लिखो_regs(काष्ठा fb_info *info, काष्ठा banshee_reg *reg)
अणु
	काष्ठा tdfx_par *par = info->par;
	पूर्णांक i;

	banshee_रुको_idle(info);

	tdfx_outl(par, MISCINIT1, tdfx_inl(par, MISCINIT1) | 0x01);

	crt_outb(par, 0x11, crt_inb(par, 0x11) & 0x7f); /* CRT unprotect */

	banshee_make_room(par, 3);
	tdfx_outl(par, VGAINIT1, reg->vgainit1 & 0x001FFFFF);
	tdfx_outl(par, VIDPROCCFG, reg->vidcfg & ~0x00000001);
#अगर 0
	tdfx_outl(par, PLLCTRL1, reg->mempll);
	tdfx_outl(par, PLLCTRL2, reg->gfxpll);
#पूर्ण_अगर
	tdfx_outl(par, PLLCTRL0, reg->vidpll);

	vga_outb(par, MISC_W, reg->misc[0x00] | 0x01);

	क्रम (i = 0; i < 5; i++)
		seq_outb(par, i, reg->seq[i]);

	क्रम (i = 0; i < 25; i++)
		crt_outb(par, i, reg->crt[i]);

	क्रम (i = 0; i < 9; i++)
		gra_outb(par, i, reg->gra[i]);

	क्रम (i = 0; i < 21; i++)
		att_outb(par, i, reg->att[i]);

	crt_outb(par, 0x1a, reg->ext[0]);
	crt_outb(par, 0x1b, reg->ext[1]);

	vga_enable_palette(par);
	vga_enable_video(par);

	banshee_make_room(par, 9);
	tdfx_outl(par, VGAINIT0, reg->vgainit0);
	tdfx_outl(par, DACMODE, reg->dacmode);
	tdfx_outl(par, VIDDESKSTRIDE, reg->stride);
	tdfx_outl(par, HWCURPATADDR, reg->curspataddr);

	tdfx_outl(par, VIDSCREENSIZE, reg->screensize);
	tdfx_outl(par, VIDDESKSTART, reg->startaddr);
	tdfx_outl(par, VIDPROCCFG, reg->vidcfg);
	tdfx_outl(par, VGAINIT1, reg->vgainit1);
	tdfx_outl(par, MISCINIT0, reg->miscinit0);

	banshee_make_room(par, 8);
	tdfx_outl(par, SRCBASE, reg->startaddr);
	tdfx_outl(par, DSTBASE, reg->startaddr);
	tdfx_outl(par, COMMANDEXTRA_2D, 0);
	tdfx_outl(par, CLIP0MIN, 0);
	tdfx_outl(par, CLIP0MAX, 0x0fff0fff);
	tdfx_outl(par, CLIP1MIN, 0);
	tdfx_outl(par, CLIP1MAX, 0x0fff0fff);
	tdfx_outl(par, SRCXY, 0);

	banshee_रुको_idle(info);
पूर्ण

अटल अचिन्हित दीर्घ करो_lfb_size(काष्ठा tdfx_par *par, अचिन्हित लघु dev_id)
अणु
	u32 draminit0 = tdfx_inl(par, DRAMINIT0);
	u32 draminit1 = tdfx_inl(par, DRAMINIT1);
	u32 miscinit1;
	पूर्णांक num_chips = (draminit0 & DRAMINIT0_SGRAM_NUM) ? 8 : 4;
	पूर्णांक chip_size; /* in MB */
	पूर्णांक has_sgram = draminit1 & DRAMINIT1_MEM_SDRAM;

	अगर (dev_id < PCI_DEVICE_ID_3DFX_VOODOO5) अणु
		/* Banshee/Vooकरोo3 */
		chip_size = 2;
		अगर (has_sgram && !(draminit0 & DRAMINIT0_SGRAM_TYPE))
			chip_size = 1;
	पूर्ण अन्यथा अणु
		/* Vooकरोo4/5 */
		has_sgram = 0;
		chip_size = draminit0 & DRAMINIT0_SGRAM_TYPE_MASK;
		chip_size = 1 << (chip_size >> DRAMINIT0_SGRAM_TYPE_SHIFT);
	पूर्ण

	/* disable block ग_लिखोs क्रम SDRAM */
	miscinit1 = tdfx_inl(par, MISCINIT1);
	miscinit1 |= has_sgram ? 0 : MISCINIT1_2DBLOCK_DIS;
	miscinit1 |= MISCINIT1_CLUT_INV;

	banshee_make_room(par, 1);
	tdfx_outl(par, MISCINIT1, miscinit1);
	वापस num_chips * chip_size * 1024l * 1024;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक tdfxfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा tdfx_par *par = info->par;
	u32 lpitch;

	अगर (var->bits_per_pixel != 8  && var->bits_per_pixel != 16 &&
	    var->bits_per_pixel != 24 && var->bits_per_pixel != 32) अणु
		DPRINTK("depth not supported: %u\n", var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	अगर (var->xres != var->xres_भव)
		var->xres_भव = var->xres;

	अगर (var->yres > var->yres_भव)
		var->yres_भव = var->yres;

	अगर (var->xoffset) अणु
		DPRINTK("xoffset not supported\n");
		वापस -EINVAL;
	पूर्ण
	var->yoffset = 0;

	/*
	 * Banshee करोesn't support पूर्णांकerlace, but Vooकरोo4/5 and probably
	 * Vooकरोo3 करो.
	 * no direct inक्रमmation about device id now?
	 *  use max_pixघड़ी क्रम this...
	 */
	अगर (((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) &&
	    (par->max_pixघड़ी < VOODOO3_MAX_PIXCLOCK)) अणु
		DPRINTK("interlace not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (info->monspecs.hfmax && info->monspecs.vfmax &&
	    info->monspecs.dclkmax && fb_validate_mode(var, info) < 0) अणु
		DPRINTK("mode outside monitor's specs\n");
		वापस -EINVAL;
	पूर्ण

	var->xres = (var->xres + 15) & ~15; /* could someबार be 8 */
	lpitch = var->xres * ((var->bits_per_pixel + 7) >> 3);

	अगर (var->xres < 320 || var->xres > 2048) अणु
		DPRINTK("width not supported: %u\n", var->xres);
		वापस -EINVAL;
	पूर्ण

	अगर (var->yres < 200 || var->yres > 2048) अणु
		DPRINTK("height not supported: %u\n", var->yres);
		वापस -EINVAL;
	पूर्ण

	अगर (lpitch * var->yres_भव > info->fix.smem_len) अणु
		var->yres_भव = info->fix.smem_len / lpitch;
		अगर (var->yres_भव < var->yres) अणु
			DPRINTK("no memory for screen (%ux%ux%u)\n",
				var->xres, var->yres_भव,
				var->bits_per_pixel);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (PICOS2KHZ(var->pixघड़ी) > par->max_pixघड़ी) अणु
		DPRINTK("pixclock too high (%ldKHz)\n",
			PICOS2KHZ(var->pixघड़ी));
		वापस -EINVAL;
	पूर्ण

	var->transp.offset = 0;
	var->transp.length = 0;
	चयन (var->bits_per_pixel) अणु
	हाल 8:
		var->red.length = 8;
		var->red.offset = 0;
		var->green = var->red;
		var->blue = var->red;
		अवरोध;
	हाल 16:
		var->red.offset   = 11;
		var->red.length   = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset  = 0;
		var->blue.length  = 5;
		अवरोध;
	हाल 32:
		var->transp.offset = 24;
		var->transp.length = 8;
		fallthrough;
	हाल 24:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = var->green.length = var->blue.length = 8;
		अवरोध;
	पूर्ण
	var->width = -1;
	var->height = -1;

	var->accel_flags = FB_ACCELF_TEXT;

	DPRINTK("Checking graphics mode at %dx%d depth %d\n",
		var->xres, var->yres, var->bits_per_pixel);
	वापस 0;
पूर्ण

अटल पूर्णांक tdfxfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा tdfx_par *par = info->par;
	u32 hdispend = info->var.xres;
	u32 hsyncsta = hdispend + info->var.right_margin;
	u32 hsyncend = hsyncsta + info->var.hsync_len;
	u32 htotal   = hsyncend + info->var.left_margin;
	u32 hd, hs, he, ht, hbs, hbe;
	u32 vd, vs, ve, vt, vbs, vbe;
	काष्ठा banshee_reg reg;
	पूर्णांक fout, freq;
	u32 wd;
	u32 cpp = (info->var.bits_per_pixel + 7) >> 3;

	स_रखो(&reg, 0, माप(reg));

	reg.vidcfg = VIDCFG_VIDPROC_ENABLE | VIDCFG_DESK_ENABLE |
		     VIDCFG_CURS_X11 |
		     ((cpp - 1) << VIDCFG_PIXFMT_SHIFT) |
		     (cpp != 1 ? VIDCFG_CLUT_BYPASS : 0);

	/* PLL settings */
	freq = PICOS2KHZ(info->var.pixघड़ी);

	reg.vidcfg &= ~VIDCFG_2X;

	अगर (freq > par->max_pixघड़ी / 2) अणु
		freq = freq > par->max_pixघड़ी ? par->max_pixघड़ी : freq;
		reg.dacmode |= DACMODE_2X;
		reg.vidcfg  |= VIDCFG_2X;
		hdispend >>= 1;
		hsyncsta >>= 1;
		hsyncend >>= 1;
		htotal   >>= 1;
	पूर्ण

	wd = (hdispend >> 3) - 1;
	hd  = wd;
	hs  = (hsyncsta >> 3) - 1;
	he  = (hsyncend >> 3) - 1;
	ht  = (htotal >> 3) - 1;
	hbs = hd;
	hbe = ht;

	अगर ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE) अणु
		vd = (info->var.yres << 1) - 1;
		vs  = vd + (info->var.lower_margin << 1);
		ve  = vs + (info->var.vsync_len << 1);
		vt = ve + (info->var.upper_margin << 1) - 1;
		reg.screensize = info->var.xres | (info->var.yres << 13);
		reg.vidcfg |= VIDCFG_HALF_MODE;
		reg.crt[0x09] = 0x80;
	पूर्ण अन्यथा अणु
		vd = info->var.yres - 1;
		vs  = vd + info->var.lower_margin;
		ve  = vs + info->var.vsync_len;
		vt = ve + info->var.upper_margin - 1;
		reg.screensize = info->var.xres | (info->var.yres << 12);
		reg.vidcfg &= ~VIDCFG_HALF_MODE;
	पूर्ण
	vbs = vd;
	vbe = vt;

	/* this is all pretty standard VGA रेजिस्टर stuffing */
	reg.misc[0x00] = 0x0f |
			(info->var.xres < 400 ? 0xa0 :
			 info->var.xres < 480 ? 0x60 :
			 info->var.xres < 768 ? 0xe0 : 0x20);

	reg.gra[0x05] = 0x40;
	reg.gra[0x06] = 0x05;
	reg.gra[0x07] = 0x0f;
	reg.gra[0x08] = 0xff;

	reg.att[0x00] = 0x00;
	reg.att[0x01] = 0x01;
	reg.att[0x02] = 0x02;
	reg.att[0x03] = 0x03;
	reg.att[0x04] = 0x04;
	reg.att[0x05] = 0x05;
	reg.att[0x06] = 0x06;
	reg.att[0x07] = 0x07;
	reg.att[0x08] = 0x08;
	reg.att[0x09] = 0x09;
	reg.att[0x0a] = 0x0a;
	reg.att[0x0b] = 0x0b;
	reg.att[0x0c] = 0x0c;
	reg.att[0x0d] = 0x0d;
	reg.att[0x0e] = 0x0e;
	reg.att[0x0f] = 0x0f;
	reg.att[0x10] = 0x41;
	reg.att[0x12] = 0x0f;

	reg.seq[0x00] = 0x03;
	reg.seq[0x01] = 0x01; /* fixme: clkभाग2? */
	reg.seq[0x02] = 0x0f;
	reg.seq[0x03] = 0x00;
	reg.seq[0x04] = 0x0e;

	reg.crt[0x00] = ht - 4;
	reg.crt[0x01] = hd;
	reg.crt[0x02] = hbs;
	reg.crt[0x03] = 0x80 | (hbe & 0x1f);
	reg.crt[0x04] = hs;
	reg.crt[0x05] = ((hbe & 0x20) << 2) | (he & 0x1f);
	reg.crt[0x06] = vt;
	reg.crt[0x07] = ((vs & 0x200) >> 2) |
			((vd & 0x200) >> 3) |
			((vt & 0x200) >> 4) | 0x10 |
			((vbs & 0x100) >> 5) |
			((vs & 0x100) >> 6) |
			((vd & 0x100) >> 7) |
			((vt & 0x100) >> 8);
	reg.crt[0x09] |= 0x40 | ((vbs & 0x200) >> 4);
	reg.crt[0x10] = vs;
	reg.crt[0x11] = (ve & 0x0f) | 0x20;
	reg.crt[0x12] = vd;
	reg.crt[0x13] = wd;
	reg.crt[0x15] = vbs;
	reg.crt[0x16] = vbe + 1;
	reg.crt[0x17] = 0xc3;
	reg.crt[0x18] = 0xff;

	/* Banshee's nonvga stuff */
	reg.ext[0x00] = (((ht & 0x100) >> 8) |
			((hd & 0x100) >> 6) |
			((hbs & 0x100) >> 4) |
			((hbe & 0x40) >> 1) |
			((hs & 0x100) >> 2) |
			((he & 0x20) << 2));
	reg.ext[0x01] = (((vt & 0x400) >> 10) |
			((vd & 0x400) >> 8) |
			((vbs & 0x400) >> 6) |
			((vbe & 0x400) >> 4));

	reg.vgainit0 =	VGAINIT0_8BIT_DAC     |
			VGAINIT0_EXT_ENABLE   |
			VGAINIT0_WAKEUP_3C3   |
			VGAINIT0_ALT_READBACK |
			VGAINIT0_EXTSHIFTOUT;
	reg.vgainit1 = tdfx_inl(par, VGAINIT1) & 0x1fffff;

	अगर (hwcursor)
		reg.curspataddr = info->fix.smem_len;

	reg.cursloc   = 0;

	reg.cursc0    = 0;
	reg.cursc1    = 0xffffff;

	reg.stride    = info->var.xres * cpp;
	reg.startaddr = info->var.yoffset * reg.stride
			+ info->var.xoffset * cpp;

	reg.vidpll = करो_calc_pll(freq, &fout);
#अगर 0
	reg.mempll = करो_calc_pll(..., &fout);
	reg.gfxpll = करो_calc_pll(..., &fout);
#पूर्ण_अगर

	अगर ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED)
		reg.vidcfg |= VIDCFG_INTERLACE;
	reg.miscinit0 = tdfx_inl(par, MISCINIT0);

#अगर defined(__BIG_ENDIAN)
	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
	हाल 24:
		reg.miscinit0 &= ~(1 << 30);
		reg.miscinit0 &= ~(1 << 31);
		अवरोध;
	हाल 16:
		reg.miscinit0 |= (1 << 30);
		reg.miscinit0 |= (1 << 31);
		अवरोध;
	हाल 32:
		reg.miscinit0 |= (1 << 30);
		reg.miscinit0 &= ~(1 << 31);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	करो_ग_लिखो_regs(info, &reg);

	/* Now change fb_fix_screeninfo according to changes in par */
	info->fix.line_length = reg.stride;
	info->fix.visual = (info->var.bits_per_pixel == 8)
				? FB_VISUAL_PSEUDOCOLOR
				: FB_VISUAL_TRUECOLOR;
	DPRINTK("Graphics mode is now set at %dx%d depth %d\n",
		info->var.xres, info->var.yres, info->var.bits_per_pixel);
	वापस 0;
पूर्ण

/* A handy macro shamelessly pinched from matroxfb */
#घोषणा CNVT_TOHW(val, width) ((((val) << (width)) + 0x7FFF - (val)) >> 16)

अटल पूर्णांक tdfxfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			    अचिन्हित blue, अचिन्हित transp,
			    काष्ठा fb_info *info)
अणु
	काष्ठा tdfx_par *par = info->par;
	u32 rgbcol;

	अगर (regno >= info->cmap.len || regno > 255)
		वापस 1;

	/* grayscale works only partially under directcolor */
	अगर (info->var.grayscale) अणु
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		blue = (red * 77 + green * 151 + blue * 28) >> 8;
		green = blue;
		red = blue;
	पूर्ण

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_PSEUDOCOLOR:
		rgbcol = (((u32)red   & 0xff00) << 8) |
			 (((u32)green & 0xff00) << 0) |
			 (((u32)blue  & 0xff00) >> 8);
		करो_setpalentry(par, regno, rgbcol);
		अवरोध;
	/* Truecolor has no hardware color palettes. */
	हाल FB_VISUAL_TRUECOLOR:
		अगर (regno < 16) अणु
			rgbcol = (CNVT_TOHW(red, info->var.red.length) <<
				  info->var.red.offset) |
				(CNVT_TOHW(green, info->var.green.length) <<
				 info->var.green.offset) |
				(CNVT_TOHW(blue, info->var.blue.length) <<
				 info->var.blue.offset) |
				(CNVT_TOHW(transp, info->var.transp.length) <<
				 info->var.transp.offset);
			par->palette[regno] = rgbcol;
		पूर्ण

		अवरोध;
	शेष:
		DPRINTK("bad depth %u\n", info->var.bits_per_pixel);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* 0 unblank, 1 blank, 2 no vsync, 3 no hsync, 4 off */
अटल पूर्णांक tdfxfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा tdfx_par *par = info->par;
	पूर्णांक vgablank = 1;
	u32 dacmode = tdfx_inl(par, DACMODE);

	dacmode &= ~(BIT(1) | BIT(3));

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK: /* Screen: On; HSync: On, VSync: On */
		vgablank = 0;
		अवरोध;
	हाल FB_BLANK_NORMAL: /* Screen: Off; HSync: On, VSync: On */
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND: /* Screen: Off; HSync: On, VSync: Off */
		dacmode |= BIT(3);
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND: /* Screen: Off; HSync: Off, VSync: On */
		dacmode |= BIT(1);
		अवरोध;
	हाल FB_BLANK_POWERDOWN: /* Screen: Off; HSync: Off, VSync: Off */
		dacmode |= BIT(1) | BIT(3);
		अवरोध;
	पूर्ण

	banshee_make_room(par, 1);
	tdfx_outl(par, DACMODE, dacmode);
	अगर (vgablank)
		vga_disable_video(par);
	अन्यथा
		vga_enable_video(par);
	वापस 0;
पूर्ण

/*
 * Set the starting position of the visible screen to var->yoffset
 */
अटल पूर्णांक tdfxfb_pan_display(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा tdfx_par *par = info->par;
	u32 addr = var->yoffset * info->fix.line_length;

	अगर (nopan || var->xoffset)
		वापस -EINVAL;

	banshee_make_room(par, 1);
	tdfx_outl(par, VIDDESKSTART, addr);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_FB_3DFX_ACCEL
/*
 * FillRect 2D command (solidfill or invert (via ROP_XOR))
 */
अटल व्योम tdfxfb_fillrect(काष्ठा fb_info *info,
			    स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा tdfx_par *par = info->par;
	u32 bpp = info->var.bits_per_pixel;
	u32 stride = info->fix.line_length;
	u32 fmt = stride | ((bpp + ((bpp == 8) ? 0 : 8)) << 13);
	पूर्णांक tdfx_rop;
	u32 dx = rect->dx;
	u32 dy = rect->dy;
	u32 dstbase = 0;

	अगर (rect->rop == ROP_COPY)
		tdfx_rop = TDFX_ROP_COPY;
	अन्यथा
		tdfx_rop = TDFX_ROP_XOR;

	/* assume always rect->height < 4096 */
	अगर (dy + rect->height > 4095) अणु
		dstbase = stride * dy;
		dy = 0;
	पूर्ण
	/* assume always rect->width < 4096 */
	अगर (dx + rect->width > 4095) अणु
		dstbase += dx * bpp >> 3;
		dx = 0;
	पूर्ण
	banshee_make_room(par, 6);
	tdfx_outl(par, DSTFORMAT, fmt);
	अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR) अणु
		tdfx_outl(par, COLORFORE, rect->color);
	पूर्ण अन्यथा अणु /* FB_VISUAL_TRUECOLOR */
		tdfx_outl(par, COLORFORE, par->palette[rect->color]);
	पूर्ण
	tdfx_outl(par, COMMAND_2D, COMMAND_2D_FILLRECT | (tdfx_rop << 24));
	tdfx_outl(par, DSTBASE, dstbase);
	tdfx_outl(par, DSTSIZE, rect->width | (rect->height << 16));
	tdfx_outl(par, LAUNCH_2D, dx | (dy << 16));
पूर्ण

/*
 * Screen-to-Screen BitBlt 2D command (क्रम the bmove fb op.)
 */
अटल व्योम tdfxfb_copyarea(काष्ठा fb_info *info,
			    स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा tdfx_par *par = info->par;
	u32 sx = area->sx, sy = area->sy, dx = area->dx, dy = area->dy;
	u32 bpp = info->var.bits_per_pixel;
	u32 stride = info->fix.line_length;
	u32 blitcmd = COMMAND_2D_S2S_BITBLT | (TDFX_ROP_COPY << 24);
	u32 fmt = stride | ((bpp + ((bpp == 8) ? 0 : 8)) << 13);
	u32 dstbase = 0;
	u32 srcbase = 0;

	/* assume always area->height < 4096 */
	अगर (sy + area->height > 4095) अणु
		srcbase = stride * sy;
		sy = 0;
	पूर्ण
	/* assume always area->width < 4096 */
	अगर (sx + area->width > 4095) अणु
		srcbase += sx * bpp >> 3;
		sx = 0;
	पूर्ण
	/* assume always area->height < 4096 */
	अगर (dy + area->height > 4095) अणु
		dstbase = stride * dy;
		dy = 0;
	पूर्ण
	/* assume always area->width < 4096 */
	अगर (dx + area->width > 4095) अणु
		dstbase += dx * bpp >> 3;
		dx = 0;
	पूर्ण

	अगर (area->sx <= area->dx) अणु
		/* -X */
		blitcmd |= BIT(14);
		sx += area->width - 1;
		dx += area->width - 1;
	पूर्ण
	अगर (area->sy <= area->dy) अणु
		/* -Y */
		blitcmd |= BIT(15);
		sy += area->height - 1;
		dy += area->height - 1;
	पूर्ण

	banshee_make_room(par, 8);

	tdfx_outl(par, SRCFORMAT, fmt);
	tdfx_outl(par, DSTFORMAT, fmt);
	tdfx_outl(par, COMMAND_2D, blitcmd);
	tdfx_outl(par, DSTSIZE, area->width | (area->height << 16));
	tdfx_outl(par, DSTXY, dx | (dy << 16));
	tdfx_outl(par, SRCBASE, srcbase);
	tdfx_outl(par, DSTBASE, dstbase);
	tdfx_outl(par, LAUNCH_2D, sx | (sy << 16));
पूर्ण

अटल व्योम tdfxfb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा tdfx_par *par = info->par;
	पूर्णांक size = image->height * ((image->width * image->depth + 7) >> 3);
	पूर्णांक fअगरo_मुक्त;
	पूर्णांक i, stride = info->fix.line_length;
	u32 bpp = info->var.bits_per_pixel;
	u32 dstfmt = stride | ((bpp + ((bpp == 8) ? 0 : 8)) << 13);
	u8 *अक्षरdata = (u8 *) image->data;
	u32 srcfmt;
	u32 dx = image->dx;
	u32 dy = image->dy;
	u32 dstbase = 0;

	अगर (image->depth != 1) अणु
#अगर_घोषित BROKEN_CODE
		banshee_make_room(par, 6 + ((size + 3) >> 2));
		srcfmt = stride | ((bpp + ((bpp == 8) ? 0 : 8)) << 13) |
			0x400000;
#अन्यथा
		cfb_imageblit(info, image);
#पूर्ण_अगर
		वापस;
	पूर्ण
	banshee_make_room(par, 9);
	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_PSEUDOCOLOR:
		tdfx_outl(par, COLORFORE, image->fg_color);
		tdfx_outl(par, COLORBACK, image->bg_color);
		अवरोध;
	हाल FB_VISUAL_TRUECOLOR:
	शेष:
		tdfx_outl(par, COLORFORE,
			  par->palette[image->fg_color]);
		tdfx_outl(par, COLORBACK,
			  par->palette[image->bg_color]);
	पूर्ण
#अगर_घोषित __BIG_ENDIAN
	srcfmt = 0x400000 | BIT(20);
#अन्यथा
	srcfmt = 0x400000;
#पूर्ण_अगर
	/* assume always image->height < 4096 */
	अगर (dy + image->height > 4095) अणु
		dstbase = stride * dy;
		dy = 0;
	पूर्ण
	/* assume always image->width < 4096 */
	अगर (dx + image->width > 4095) अणु
		dstbase += dx * bpp >> 3;
		dx = 0;
	पूर्ण

	tdfx_outl(par, DSTBASE, dstbase);
	tdfx_outl(par, SRCXY, 0);
	tdfx_outl(par, DSTXY, dx | (dy << 16));
	tdfx_outl(par, COMMAND_2D,
		  COMMAND_2D_H2S_BITBLT | (TDFX_ROP_COPY << 24));
	tdfx_outl(par, SRCFORMAT, srcfmt);
	tdfx_outl(par, DSTFORMAT, dstfmt);
	tdfx_outl(par, DSTSIZE, image->width | (image->height << 16));

	/* A count of how many मुक्त FIFO entries we've requested.
	 * When this goes negative, we need to request more. */
	fअगरo_मुक्त = 0;

	/* Send four bytes at a समय of data */
	क्रम (i = (size >> 2); i > 0; i--) अणु
		अगर (--fअगरo_मुक्त < 0) अणु
			fअगरo_मुक्त = 31;
			banshee_make_room(par, fअगरo_मुक्त);
		पूर्ण
		tdfx_outl(par, LAUNCH_2D, *(u32 *)अक्षरdata);
		अक्षरdata += 4;
	पूर्ण

	/* Send the leftovers now */
	banshee_make_room(par, 3);
	चयन (size % 4) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		tdfx_outl(par, LAUNCH_2D, *अक्षरdata);
		अवरोध;
	हाल 2:
		tdfx_outl(par, LAUNCH_2D, *(u16 *)अक्षरdata);
		अवरोध;
	हाल 3:
		tdfx_outl(par, LAUNCH_2D,
			*(u16 *)अक्षरdata | (अक्षरdata[3] << 24));
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_3DFX_ACCEL */

अटल पूर्णांक tdfxfb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा tdfx_par *par = info->par;
	u32 vidcfg;

	अगर (!hwcursor)
		वापस -EINVAL;	/* just to क्रमce soft_cursor() call */

	/* Too large of a cursor or wrong bpp :-( */
	अगर (cursor->image.width > 64 ||
	    cursor->image.height > 64 ||
	    cursor->image.depth > 1)
		वापस -EINVAL;

	vidcfg = tdfx_inl(par, VIDPROCCFG);
	अगर (cursor->enable)
		tdfx_outl(par, VIDPROCCFG, vidcfg | VIDCFG_HWCURSOR_ENABLE);
	अन्यथा
		tdfx_outl(par, VIDPROCCFG, vidcfg & ~VIDCFG_HWCURSOR_ENABLE);

	/*
	 * If the cursor is not be changed this means either we want the
	 * current cursor state (अगर enable is set) or we want to query what
	 * we can करो with the cursor (अगर enable is not set)
	 */
	अगर (!cursor->set)
		वापस 0;

	/* fix cursor color - XFree86 क्रममाला_लो to restore it properly */
	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		काष्ठा fb_cmap cmap = info->cmap;
		u32 bg_idx = cursor->image.bg_color;
		u32 fg_idx = cursor->image.fg_color;
		अचिन्हित दीर्घ bg_color, fg_color;

		fg_color = (((u32)cmap.red[fg_idx]   & 0xff00) << 8) |
			   (((u32)cmap.green[fg_idx] & 0xff00) << 0) |
			   (((u32)cmap.blue[fg_idx]  & 0xff00) >> 8);
		bg_color = (((u32)cmap.red[bg_idx]   & 0xff00) << 8) |
			   (((u32)cmap.green[bg_idx] & 0xff00) << 0) |
			   (((u32)cmap.blue[bg_idx]  & 0xff00) >> 8);
		banshee_make_room(par, 2);
		tdfx_outl(par, HWCURC0, bg_color);
		tdfx_outl(par, HWCURC1, fg_color);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETPOS) अणु
		पूर्णांक x = cursor->image.dx;
		पूर्णांक y = cursor->image.dy - info->var.yoffset;

		x += 63;
		y += 63;
		banshee_make_room(par, 1);
		tdfx_outl(par, HWCURLOC, (y << 16) + x);
	पूर्ण
	अगर (cursor->set & (FB_CUR_SETIMAGE | FB_CUR_SETSHAPE)) अणु
		/*
		 * Vooकरोo 3 and above cards use 2 monochrome cursor patterns.
		 *    The reason is so the card can fetch 8 words at a समय
		 * and are stored on chip क्रम use क्रम the next 8 scanlines.
		 * This reduces the number of बार क्रम access to draw the
		 * cursor क्रम each screen refresh.
		 *    Each pattern is a biपंचांगap of 64 bit wide and 64 bit high
		 * (total of 8192 bits or 1024 bytes). The two patterns are
		 * stored in such a way that pattern 0 always resides in the
		 * lower half (least signअगरicant 64 bits) of a 128 bit word
		 * and pattern 1 the upper half. If you examine the data of
		 * the cursor image the graphics card uses then from the
		 * beginning you see line one of pattern 0, line one of
		 * pattern 1, line two of pattern 0, line two of pattern 1,
		 * etc etc. The linear stride क्रम the cursor is always 16 bytes
		 * (128 bits) which is the maximum cursor width बार two क्रम
		 * the two monochrome patterns.
		 */
		u8 __iomem *cursorbase = info->screen_base + info->fix.smem_len;
		u8 *biपंचांगap = (u8 *)cursor->image.data;
		u8 *mask = (u8 *)cursor->mask;
		पूर्णांक i;

		fb_स_रखो(cursorbase, 0, 1024);

		क्रम (i = 0; i < cursor->image.height; i++) अणु
			पूर्णांक h = 0;
			पूर्णांक j = (cursor->image.width + 7) >> 3;

			क्रम (; j > 0; j--) अणु
				u8 data = *mask ^ *biपंचांगap;
				अगर (cursor->rop == ROP_COPY)
					data = *mask & *biपंचांगap;
				/* Pattern 0. Copy the cursor mask to it */
				fb_ग_लिखोb(*mask, cursorbase + h);
				mask++;
				/* Pattern 1. Copy the cursor biपंचांगap to it */
				fb_ग_लिखोb(data, cursorbase + h + 8);
				biपंचांगap++;
				h++;
			पूर्ण
			cursorbase += 16;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops tdfxfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= tdfxfb_check_var,
	.fb_set_par	= tdfxfb_set_par,
	.fb_setcolreg	= tdfxfb_setcolreg,
	.fb_blank	= tdfxfb_blank,
	.fb_pan_display	= tdfxfb_pan_display,
	.fb_sync	= banshee_रुको_idle,
	.fb_cursor	= tdfxfb_cursor,
#अगर_घोषित CONFIG_FB_3DFX_ACCEL
	.fb_fillrect	= tdfxfb_fillrect,
	.fb_copyarea	= tdfxfb_copyarea,
	.fb_imageblit	= tdfxfb_imageblit,
#अन्यथा
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_FB_3DFX_I2C
/* The voo GPIO रेजिस्टरs करोn't have inभागidual masks क्रम each bit
   so we always have to पढ़ो beक्रमe writing. */

अटल व्योम tdfxfb_i2c_setscl(व्योम *data, पूर्णांक val)
अणु
	काष्ठा tdfxfb_i2c_chan 	*chan = data;
	काष्ठा tdfx_par 	*par = chan->par;
	अचिन्हित पूर्णांक r;

	r = tdfx_inl(par, VIDSERPARPORT);
	अगर (val)
		r |= I2C_SCL_OUT;
	अन्यथा
		r &= ~I2C_SCL_OUT;
	tdfx_outl(par, VIDSERPARPORT, r);
	tdfx_inl(par, VIDSERPARPORT);	/* flush posted ग_लिखो */
पूर्ण

अटल व्योम tdfxfb_i2c_setsda(व्योम *data, पूर्णांक val)
अणु
	काष्ठा tdfxfb_i2c_chan 	*chan = data;
	काष्ठा tdfx_par 	*par = chan->par;
	अचिन्हित पूर्णांक r;

	r = tdfx_inl(par, VIDSERPARPORT);
	अगर (val)
		r |= I2C_SDA_OUT;
	अन्यथा
		r &= ~I2C_SDA_OUT;
	tdfx_outl(par, VIDSERPARPORT, r);
	tdfx_inl(par, VIDSERPARPORT);	/* flush posted ग_लिखो */
पूर्ण

/* The GPIO pins are खोलो drain, so the pins always reमुख्य outमाला_दो.
   We rely on the i2c-algo-bit routines to set the pins high beक्रमe
   पढ़ोing the input from other chips. */

अटल पूर्णांक tdfxfb_i2c_माला_लोcl(व्योम *data)
अणु
	काष्ठा tdfxfb_i2c_chan 	*chan = data;
	काष्ठा tdfx_par 	*par = chan->par;

	वापस (0 != (tdfx_inl(par, VIDSERPARPORT) & I2C_SCL_IN));
पूर्ण

अटल पूर्णांक tdfxfb_i2c_माला_लोda(व्योम *data)
अणु
	काष्ठा tdfxfb_i2c_chan 	*chan = data;
	काष्ठा tdfx_par 	*par = chan->par;

	वापस (0 != (tdfx_inl(par, VIDSERPARPORT) & I2C_SDA_IN));
पूर्ण

अटल व्योम tdfxfb_ddc_setscl(व्योम *data, पूर्णांक val)
अणु
	काष्ठा tdfxfb_i2c_chan 	*chan = data;
	काष्ठा tdfx_par 	*par = chan->par;
	अचिन्हित पूर्णांक r;

	r = tdfx_inl(par, VIDSERPARPORT);
	अगर (val)
		r |= DDC_SCL_OUT;
	अन्यथा
		r &= ~DDC_SCL_OUT;
	tdfx_outl(par, VIDSERPARPORT, r);
	tdfx_inl(par, VIDSERPARPORT);	/* flush posted ग_लिखो */
पूर्ण

अटल व्योम tdfxfb_ddc_setsda(व्योम *data, पूर्णांक val)
अणु
	काष्ठा tdfxfb_i2c_chan 	*chan = data;
	काष्ठा tdfx_par 	*par = chan->par;
	अचिन्हित पूर्णांक r;

	r = tdfx_inl(par, VIDSERPARPORT);
	अगर (val)
		r |= DDC_SDA_OUT;
	अन्यथा
		r &= ~DDC_SDA_OUT;
	tdfx_outl(par, VIDSERPARPORT, r);
	tdfx_inl(par, VIDSERPARPORT);	/* flush posted ग_लिखो */
पूर्ण

अटल पूर्णांक tdfxfb_ddc_माला_लोcl(व्योम *data)
अणु
	काष्ठा tdfxfb_i2c_chan 	*chan = data;
	काष्ठा tdfx_par 	*par = chan->par;

	वापस (0 != (tdfx_inl(par, VIDSERPARPORT) & DDC_SCL_IN));
पूर्ण

अटल पूर्णांक tdfxfb_ddc_माला_लोda(व्योम *data)
अणु
	काष्ठा tdfxfb_i2c_chan 	*chan = data;
	काष्ठा tdfx_par 	*par = chan->par;

	वापस (0 != (tdfx_inl(par, VIDSERPARPORT) & DDC_SDA_IN));
पूर्ण

अटल पूर्णांक tdfxfb_setup_ddc_bus(काष्ठा tdfxfb_i2c_chan *chan, स्थिर अक्षर *name,
				काष्ठा device *dev)
अणु
	पूर्णांक rc;

	strlcpy(chan->adapter.name, name, माप(chan->adapter.name));
	chan->adapter.owner		= THIS_MODULE;
	chan->adapter.class		= I2C_CLASS_DDC;
	chan->adapter.algo_data		= &chan->algo;
	chan->adapter.dev.parent	= dev;
	chan->algo.setsda		= tdfxfb_ddc_setsda;
	chan->algo.setscl		= tdfxfb_ddc_setscl;
	chan->algo.माला_लोda		= tdfxfb_ddc_माला_लोda;
	chan->algo.माला_लोcl		= tdfxfb_ddc_माला_लोcl;
	chan->algo.udelay		= 10;
	chan->algo.समयout		= msecs_to_jअगरfies(500);
	chan->algo.data 		= chan;

	i2c_set_adapdata(&chan->adapter, chan);

	rc = i2c_bit_add_bus(&chan->adapter);
	अगर (rc == 0)
		DPRINTK("I2C bus %s registered.\n", name);
	अन्यथा
		chan->par = शून्य;

	वापस rc;
पूर्ण

अटल पूर्णांक tdfxfb_setup_i2c_bus(काष्ठा tdfxfb_i2c_chan *chan, स्थिर अक्षर *name,
				काष्ठा device *dev)
अणु
	पूर्णांक rc;

	strlcpy(chan->adapter.name, name, माप(chan->adapter.name));
	chan->adapter.owner		= THIS_MODULE;
	chan->adapter.algo_data		= &chan->algo;
	chan->adapter.dev.parent	= dev;
	chan->algo.setsda		= tdfxfb_i2c_setsda;
	chan->algo.setscl		= tdfxfb_i2c_setscl;
	chan->algo.माला_लोda		= tdfxfb_i2c_माला_लोda;
	chan->algo.माला_लोcl		= tdfxfb_i2c_माला_लोcl;
	chan->algo.udelay		= 10;
	chan->algo.समयout		= msecs_to_jअगरfies(500);
	chan->algo.data 		= chan;

	i2c_set_adapdata(&chan->adapter, chan);

	rc = i2c_bit_add_bus(&chan->adapter);
	अगर (rc == 0)
		DPRINTK("I2C bus %s registered.\n", name);
	अन्यथा
		chan->par = शून्य;

	वापस rc;
पूर्ण

अटल व्योम tdfxfb_create_i2c_busses(काष्ठा fb_info *info)
अणु
	काष्ठा tdfx_par *par = info->par;

	tdfx_outl(par, VIDINFORMAT, 0x8160);
	tdfx_outl(par, VIDSERPARPORT, 0xcffc0020);

	par->chan[0].par = par;
	par->chan[1].par = par;

	tdfxfb_setup_ddc_bus(&par->chan[0], "Voodoo3-DDC", info->dev);
	tdfxfb_setup_i2c_bus(&par->chan[1], "Voodoo3-I2C", info->dev);
पूर्ण

अटल व्योम tdfxfb_delete_i2c_busses(काष्ठा tdfx_par *par)
अणु
	अगर (par->chan[0].par)
		i2c_del_adapter(&par->chan[0].adapter);
	par->chan[0].par = शून्य;

	अगर (par->chan[1].par)
		i2c_del_adapter(&par->chan[1].adapter);
	par->chan[1].par = शून्य;
पूर्ण

अटल पूर्णांक tdfxfb_probe_i2c_connector(काष्ठा tdfx_par *par,
				      काष्ठा fb_monspecs *specs)
अणु
	u8 *edid = शून्य;

	DPRINTK("Probe DDC Bus\n");
	अगर (par->chan[0].par)
		edid = fb_ddc_पढ़ो(&par->chan[0].adapter);

	अगर (edid) अणु
		fb_edid_to_monspecs(edid, specs);
		kमुक्त(edid);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_3DFX_I2C */

/**
 *      tdfxfb_probe - Device Initializiation
 *
 *      @pdev:  PCI Device to initialize
 *      @id:    PCI Device ID
 *
 *      Initializes and allocates resources क्रम PCI device @pdev.
 *
 */
अटल पूर्णांक tdfxfb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा tdfx_par *शेष_par;
	काष्ठा fb_info *info;
	पूर्णांक err, lpitch;
	काष्ठा fb_monspecs *specs;
	bool found;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "tdfxfb: Can't enable pdev: %d\n", err);
		वापस err;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा tdfx_par), &pdev->dev);

	अगर (!info)
		वापस -ENOMEM;

	शेष_par = info->par;
	info->fix = tdfx_fix;

	/* Configure the शेष fb_fix_screeninfo first */
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_3DFX_BANSHEE:
		म_नकल(info->fix.id, "3Dfx Banshee");
		शेष_par->max_pixघड़ी = BANSHEE_MAX_PIXCLOCK;
		अवरोध;
	हाल PCI_DEVICE_ID_3DFX_VOODOO3:
		म_नकल(info->fix.id, "3Dfx Voodoo3");
		शेष_par->max_pixघड़ी = VOODOO3_MAX_PIXCLOCK;
		अवरोध;
	हाल PCI_DEVICE_ID_3DFX_VOODOO5:
		म_नकल(info->fix.id, "3Dfx Voodoo5");
		शेष_par->max_pixघड़ी = VOODOO5_MAX_PIXCLOCK;
		अवरोध;
	पूर्ण

	info->fix.mmio_start = pci_resource_start(pdev, 0);
	info->fix.mmio_len = pci_resource_len(pdev, 0);
	अगर (!request_mem_region(info->fix.mmio_start, info->fix.mmio_len,
				"tdfx regbase")) अणु
		prपूर्णांकk(KERN_ERR "tdfxfb: Can't reserve regbase\n");
		जाओ out_err;
	पूर्ण

	शेष_par->regbase_virt =
		ioremap(info->fix.mmio_start, info->fix.mmio_len);
	अगर (!शेष_par->regbase_virt) अणु
		prपूर्णांकk(KERN_ERR "fb: Can't remap %s register area.\n",
				info->fix.id);
		जाओ out_err_regbase;
	पूर्ण

	info->fix.smem_start = pci_resource_start(pdev, 1);
	info->fix.smem_len = करो_lfb_size(शेष_par, pdev->device);
	अगर (!info->fix.smem_len) अणु
		prपूर्णांकk(KERN_ERR "fb: Can't count %s memory.\n", info->fix.id);
		जाओ out_err_regbase;
	पूर्ण

	अगर (!request_mem_region(info->fix.smem_start,
				pci_resource_len(pdev, 1), "tdfx smem")) अणु
		prपूर्णांकk(KERN_ERR "tdfxfb: Can't reserve smem\n");
		जाओ out_err_regbase;
	पूर्ण

	info->screen_base = ioremap_wc(info->fix.smem_start,
				       info->fix.smem_len);
	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR "fb: Can't remap %s framebuffer.\n",
				info->fix.id);
		जाओ out_err_screenbase;
	पूर्ण

	शेष_par->iobase = pci_resource_start(pdev, 2);

	अगर (!request_region(pci_resource_start(pdev, 2),
			    pci_resource_len(pdev, 2), "tdfx iobase")) अणु
		prपूर्णांकk(KERN_ERR "tdfxfb: Can't reserve iobase\n");
		जाओ out_err_screenbase;
	पूर्ण

	prपूर्णांकk(KERN_INFO "fb: %s memory = %dK\n", info->fix.id,
			info->fix.smem_len >> 10);

	अगर (!nomtrr)
		शेष_par->wc_cookie= arch_phys_wc_add(info->fix.smem_start,
							 info->fix.smem_len);

	info->fix.ypanstep	= nopan ? 0 : 1;
	info->fix.ywrapstep	= nowrap ? 0 : 1;

	info->fbops		= &tdfxfb_ops;
	info->pseuकरो_palette	= शेष_par->palette;
	info->flags		= FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
#अगर_घोषित CONFIG_FB_3DFX_ACCEL
	info->flags		|= FBINFO_HWACCEL_FILLRECT |
				   FBINFO_HWACCEL_COPYAREA |
				   FBINFO_HWACCEL_IMAGEBLIT |
				   FBINFO_READS_FAST;
#पूर्ण_अगर
	/* reserve 8192 bits क्रम cursor */
	/* the 2.4 driver says PAGE_MASK boundary is not enough क्रम Vooकरोo4 */
	अगर (hwcursor)
		info->fix.smem_len = (info->fix.smem_len - 1024) &
					(PAGE_MASK << 1);
	specs = &info->monspecs;
	found = false;
	info->var.bits_per_pixel = 8;
#अगर_घोषित CONFIG_FB_3DFX_I2C
	tdfxfb_create_i2c_busses(info);
	err = tdfxfb_probe_i2c_connector(शेष_par, specs);

	अगर (!err) अणु
		अगर (specs->modedb == शून्य)
			DPRINTK("Unable to get Mode Database\n");
		अन्यथा अणु
			स्थिर काष्ठा fb_videomode *m;

			fb_videomode_to_modelist(specs->modedb,
						 specs->modedb_len,
						 &info->modelist);
			m = fb_find_best_display(specs, &info->modelist);
			अगर (m) अणु
				fb_videomode_to_var(&info->var, m);
				/* fill all other info->var's fields */
				अगर (tdfxfb_check_var(&info->var, info) < 0)
					info->var = tdfx_var;
				अन्यथा
					found = true;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (!mode_option && !found)
		mode_option = "640x480@60";

	अगर (mode_option) अणु
		err = fb_find_mode(&info->var, info, mode_option,
				   specs->modedb, specs->modedb_len,
				   शून्य, info->var.bits_per_pixel);
		अगर (!err || err == 4)
			info->var = tdfx_var;
	पूर्ण

	अगर (found) अणु
		fb_destroy_modedb(specs->modedb);
		specs->modedb = शून्य;
	पूर्ण

	/* maximize भव vertical length */
	lpitch = info->var.xres_भव * ((info->var.bits_per_pixel + 7) >> 3);
	info->var.yres_भव = info->fix.smem_len / lpitch;
	अगर (info->var.yres_भव < info->var.yres)
		जाओ out_err_iobase;

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		prपूर्णांकk(KERN_ERR "tdfxfb: Can't allocate color map\n");
		जाओ out_err_iobase;
	पूर्ण

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		prपूर्णांकk(KERN_ERR "tdfxfb: can't register framebuffer\n");
		fb_dealloc_cmap(&info->cmap);
		जाओ out_err_iobase;
	पूर्ण
	/*
	 * Our driver data
	 */
	pci_set_drvdata(pdev, info);
	वापस 0;

out_err_iobase:
#अगर_घोषित CONFIG_FB_3DFX_I2C
	tdfxfb_delete_i2c_busses(शेष_par);
#पूर्ण_अगर
	arch_phys_wc_del(शेष_par->wc_cookie);
	release_region(pci_resource_start(pdev, 2),
		       pci_resource_len(pdev, 2));
out_err_screenbase:
	अगर (info->screen_base)
		iounmap(info->screen_base);
	release_mem_region(info->fix.smem_start, pci_resource_len(pdev, 1));
out_err_regbase:
	/*
	 * Cleanup after anything that was remapped/allocated.
	 */
	अगर (शेष_par->regbase_virt)
		iounmap(शेष_par->regbase_virt);
	release_mem_region(info->fix.mmio_start, info->fix.mmio_len);
out_err:
	framebuffer_release(info);
	वापस -ENXIO;
पूर्ण

#अगर_अघोषित MODULE
अटल व्योम __init tdfxfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;
		अगर (!म_भेद(this_opt, "nopan")) अणु
			nopan = 1;
		पूर्ण अन्यथा अगर (!म_भेद(this_opt, "nowrap")) अणु
			nowrap = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "hwcursor=", 9)) अणु
			hwcursor = simple_म_से_अदीर्घ(this_opt + 9, शून्य, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "nomtrr", 6)) अणु
			nomtrr = 1;
		पूर्ण अन्यथा अणु
			mode_option = this_opt;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 *      tdfxfb_हटाओ - Device removal
 *
 *      @pdev:  PCI Device to cleanup
 *
 *      Releases all resources allocated during the course of the driver's
 *      lअगरeसमय क्रम the PCI device @pdev.
 *
 */
अटल व्योम tdfxfb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा tdfx_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
#अगर_घोषित CONFIG_FB_3DFX_I2C
	tdfxfb_delete_i2c_busses(par);
#पूर्ण_अगर
	arch_phys_wc_del(par->wc_cookie);
	iounmap(par->regbase_virt);
	iounmap(info->screen_base);

	/* Clean up after reserved regions */
	release_region(pci_resource_start(pdev, 2),
		       pci_resource_len(pdev, 2));
	release_mem_region(pci_resource_start(pdev, 1),
			   pci_resource_len(pdev, 1));
	release_mem_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0));
	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
पूर्ण

अटल पूर्णांक __init tdfxfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("tdfxfb", &option))
		वापस -ENODEV;

	tdfxfb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&tdfxfb_driver);
पूर्ण

अटल व्योम __निकास tdfxfb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&tdfxfb_driver);
पूर्ण

MODULE_AUTHOR("Hannu Mallat <hmallat@cc.hut.fi>");
MODULE_DESCRIPTION("3Dfx framebuffer device driver");
MODULE_LICENSE("GPL");

module_param(hwcursor, पूर्णांक, 0644);
MODULE_PARM_DESC(hwcursor, "Enable hardware cursor "
			"(1=enable, 0=disable, default=1)");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Initial video mode e.g. '648x480-8@60'");
module_param(nomtrr, bool, 0);
MODULE_PARM_DESC(nomtrr, "Disable MTRR support (default: enabled)");

module_init(tdfxfb_init);
module_निकास(tdfxfb_निकास);
