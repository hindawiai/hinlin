<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/sstfb.c -- vooकरोo graphics frame buffer
 *
 *     Copyright (c) 2000-2002 Ghozlane Toumi <gtoumi@laposte.net>
 *
 *     Created 15 Jan 2000 by Ghozlane Toumi
 *
 * Contributions (and many thanks) :
 *
 * 03/2001 James Simmons   <jsimmons@infradead.org>
 * 04/2001 Paul Mundt      <lethal@chaoticdreams.org>
 * 05/2001 Urs Ganse       <ursg@uni.de>
 *	(initial work on vooकरोo2 port, पूर्णांकerlace)
 * 09/2002 Helge Deller    <deller@gmx.de>
 *	(enable driver on big-endian machines (hppa), ioctl fixes)
 * 12/2002 Helge Deller    <deller@gmx.de>
 *	(port driver to new frambuffer infraकाष्ठाure)
 * 01/2003 Helge Deller    <deller@gmx.de>
 *	(initial work on fb hardware acceleration क्रम vooकरोo2)
 * 08/2006 Alan Cox 	   <alan@redhat.com>
 *	Remove never finished and bogus 24/32bit support
 *	Clean up macro abuse
 *	Minor tidying क्रम क्रमmat.
 * 12/2006 Helge Deller    <deller@gmx.de>
 *	add /sys/class/graphics/fbX/vgapass sysfs-पूर्णांकerface
 *	add module option "mode_option" to set initial screen mode
 *	use fbdev शेष videomode database
 *	हटाओ debug functions from ioctl
 */

/*
 * The vooकरोo1 has the following memory mapped address space:
 * 0x000000 - 0x3fffff : रेजिस्टरs              (4MB)
 * 0x400000 - 0x7fffff : linear frame buffer    (4MB)
 * 0x800000 - 0xffffff : texture memory         (8MB)
 */

/*
 * misc notes, TODOs, toASKs, and deep thoughts

-TODO: at one समय or another test that the mode is acceptable by the monitor
-ASK: Can I choose dअगरferent ordering क्रम the color bitfields (rgba argb ...)
      which one should i use ? is there any preferred one ? It seems ARGB is
      the one ...
-TODO: in  set_var check the validity of timings (hsync vsync)...
-TODO: check and recheck the use of sst_रुको_idle : we करोn't flush the fअगरo via
       a nop command. so it's ok as long as the commands we pass don't go
       through the fअगरo. warning: issuing a nop command seems to need pci_fअगरo
-FIXME: in हाल of failure in the init sequence, be sure we वापस to a safe
        state.
- FIXME: Use accelerator क्रम 2D scroll
-FIXME: 4MB boards have banked memory (FbiInit2 bits 1 & 20)
 */

/*
 * debug info
 * SST_DEBUG : enable debugging
 * SST_DEBUG_REG : debug रेजिस्टरs
 *   0 :  no debug
 *   1 : dac calls, [un]set_bits, FbiInit
 *   2 : insane debug level (log every रेजिस्टर पढ़ो/ग_लिखो)
 * SST_DEBUG_FUNC : functions
 *   0 : no debug
 *   1 : function call / debug ioctl
 *   2 : variables
 *   3 : flood . you करोn't want to करो that. trust me.
 * SST_DEBUG_VAR : debug display/var काष्ठाs
 *   0 : no debug
 *   1 : dumps display, fb_var
 *
 * sstfb specअगरic ioctls:
 *   		toggle vga (0x46db) : toggle vga_pass_through
 */

#अघोषित SST_DEBUG


/*
 * Includes
 */

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <video/sstfb.h>


/* initialized by setup */

अटल bool vgapass;		/* enable VGA passthrough cable */
अटल पूर्णांक mem;			/* mem size in MB, 0 = स्वतःdetect */
अटल bool clipping = 1;	/* use clipping (slower, safer) */
अटल पूर्णांक gfxclk;		/* क्रमce FBI freq in Mhz . Dangerous */
अटल bool slowpci;		/* slow PCI settings */

/*
  Possible शेष video modes: 800x600@60, 640x480@75, 1024x768@76, 640x480@60
*/
#घोषणा DEFAULT_VIDEO_MODE "640x480@60"

अटल अक्षर *mode_option = DEFAULT_VIDEO_MODE;

क्रमागत अणु
	ID_VOODOO1 = 0,
	ID_VOODOO2 = 1,
पूर्ण;

#घोषणा IS_VOODOO2(par) ((par)->type == ID_VOODOO2)

अटल काष्ठा sst_spec vooकरोo_spec[] = अणु
 अणु .name = "Voodoo Graphics", .शेष_gfx_घड़ी = 50000, .max_gfxclk = 60 पूर्ण,
 अणु .name = "Voodoo2",	      .शेष_gfx_घड़ी = 75000, .max_gfxclk = 85 पूर्ण,
पूर्ण;


/*
 * debug functions
 */

#अगर (SST_DEBUG_REG > 0)
अटल व्योम sst_dbg_prपूर्णांक_पढ़ो_reg(u32 reg, u32 val) अणु
	स्थिर अक्षर *regname;
	चयन (reg) अणु
	हाल FBIINIT0:	regname = "FbiInit0"; अवरोध;
	हाल FBIINIT1:	regname = "FbiInit1"; अवरोध;
	हाल FBIINIT2:	regname = "FbiInit2"; अवरोध;
	हाल FBIINIT3:	regname = "FbiInit3"; अवरोध;
	हाल FBIINIT4:	regname = "FbiInit4"; अवरोध;
	हाल FBIINIT5:	regname = "FbiInit5"; अवरोध;
	हाल FBIINIT6:	regname = "FbiInit6"; अवरोध;
	शेष:	regname = शून्य;       अवरोध;
	पूर्ण
	अगर (regname == शून्य)
		r_ddprपूर्णांकk("sst_read(%#x): %#x\n", reg, val);
	अन्यथा
		r_dprपूर्णांकk(" sst_read(%s): %#x\n", regname, val);
पूर्ण

अटल व्योम sst_dbg_prपूर्णांक_ग_लिखो_reg(u32 reg, u32 val) अणु
	स्थिर अक्षर *regname;
	चयन (reg) अणु
	हाल FBIINIT0:	regname = "FbiInit0"; अवरोध;
	हाल FBIINIT1:	regname = "FbiInit1"; अवरोध;
	हाल FBIINIT2:	regname = "FbiInit2"; अवरोध;
	हाल FBIINIT3:	regname = "FbiInit3"; अवरोध;
	हाल FBIINIT4:	regname = "FbiInit4"; अवरोध;
	हाल FBIINIT5:	regname = "FbiInit5"; अवरोध;
	हाल FBIINIT6:	regname = "FbiInit6"; अवरोध;
	शेष:	regname = शून्य;       अवरोध;
	पूर्ण
	अगर (regname == शून्य)
		r_ddprपूर्णांकk("sst_write(%#x, %#x)\n", reg, val);
	अन्यथा
		r_dprपूर्णांकk(" sst_write(%s, %#x)\n", regname, val);
पूर्ण
#अन्यथा /*  (SST_DEBUG_REG > 0) */
#  define sst_dbg_prपूर्णांक_पढ़ो_reg(reg, val)	करो अणुपूर्ण जबतक(0)
#  define sst_dbg_prपूर्णांक_ग_लिखो_reg(reg, val)	करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर /*  (SST_DEBUG_REG > 0) */

/*
 * hardware access functions
 */

/* रेजिस्टर access */
#घोषणा sst_पढ़ो(reg)		__sst_पढ़ो(par->mmio_vbase, reg)
#घोषणा sst_ग_लिखो(reg,val)	__sst_ग_लिखो(par->mmio_vbase, reg, val)
#घोषणा sst_set_bits(reg,val)	__sst_set_bits(par->mmio_vbase, reg, val)
#घोषणा sst_unset_bits(reg,val)	__sst_unset_bits(par->mmio_vbase, reg, val)
#घोषणा sst_dac_पढ़ो(reg)	__sst_dac_पढ़ो(par->mmio_vbase, reg)
#घोषणा sst_dac_ग_लिखो(reg,val)	__sst_dac_ग_लिखो(par->mmio_vbase, reg, val)
#घोषणा dac_i_पढ़ो(reg)		__dac_i_पढ़ो(par->mmio_vbase, reg)
#घोषणा dac_i_ग_लिखो(reg,val)	__dac_i_ग_लिखो(par->mmio_vbase, reg, val)

अटल अंतरभूत u32 __sst_पढ़ो(u8 __iomem *vbase, u32 reg)
अणु
	u32 ret = पढ़ोl(vbase + reg);
	sst_dbg_prपूर्णांक_पढ़ो_reg(reg, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम __sst_ग_लिखो(u8 __iomem *vbase, u32 reg, u32 val)
अणु
	sst_dbg_prपूर्णांक_ग_लिखो_reg(reg, val);
	ग_लिखोl(val, vbase + reg);
पूर्ण

अटल अंतरभूत व्योम __sst_set_bits(u8 __iomem *vbase, u32 reg, u32 val)
अणु
	r_dprपूर्णांकk("sst_set_bits(%#x, %#x)\n", reg, val);
	__sst_ग_लिखो(vbase, reg, __sst_पढ़ो(vbase, reg) | val);
पूर्ण

अटल अंतरभूत व्योम __sst_unset_bits(u8 __iomem *vbase, u32 reg, u32 val)
अणु
	r_dprपूर्णांकk("sst_unset_bits(%#x, %#x)\n", reg, val);
	__sst_ग_लिखो(vbase, reg, __sst_पढ़ो(vbase, reg) & ~val);
पूर्ण

/*
 * रुको क्रम the fbi chip. ASK: what happens अगर the fbi is stuck ?
 *
 * the FBI is supposed to be पढ़ोy अगर we receive 5 समय
 * in a row a "idle" answer to our requests
 */

#घोषणा sst_रुको_idle() __sst_रुको_idle(par->mmio_vbase)

अटल पूर्णांक __sst_रुको_idle(u8 __iomem *vbase)
अणु
	पूर्णांक count = 0;

	/* अगर (करोFBINOP) __sst_ग_लिखो(vbase, NOPCMD, 0); */

	जबतक(1) अणु
		अगर (__sst_पढ़ो(vbase, STATUS) & STATUS_FBI_BUSY) अणु
			f_dddprपूर्णांकk("status: busy\n");
/* FIXME basically, this is a busy रुको. maybe not that good. oh well;
 * this is a small loop after all.
 * Or maybe we should use mdelay() or udelay() here instead ? */
			count = 0;
		पूर्ण अन्यथा अणु
			count++;
			f_dddprपूर्णांकk("status: idle(%d)\n", count);
		पूर्ण
		अगर (count >= 5) वापस 1;
/* XXX  करो something to aव्योम hanging the machine अगर the vooकरोo is out */
	पूर्ण
पूर्ण


/* dac access */
/* dac_पढ़ो should be remaped to FbiInit2 (via the pci reg init_enable) */
अटल u8 __sst_dac_पढ़ो(u8 __iomem *vbase, u8 reg)
अणु
	u8 ret;

	reg &= 0x07;
	__sst_ग_लिखो(vbase, DAC_DATA, ((u32)reg << 8) | DAC_READ_CMD );
	__sst_रुको_idle(vbase);
	/* udelay(10); */
	ret = __sst_पढ़ो(vbase, DAC_READ) & 0xff;
	r_dprपूर्णांकk("sst_dac_read(%#x): %#x\n", reg, ret);

	वापस ret;
पूर्ण

अटल व्योम __sst_dac_ग_लिखो(u8 __iomem *vbase, u8 reg, u8 val)
अणु
	r_dprपूर्णांकk("sst_dac_write(%#x, %#x)\n", reg, val);
	reg &= 0x07;
	__sst_ग_लिखो(vbase, DAC_DATA,(((u32)reg << 8)) | (u32)val);
	__sst_रुको_idle(vbase);
पूर्ण

/* indexed access to ti/att dacs */
अटल u32 __dac_i_पढ़ो(u8 __iomem *vbase, u8 reg)
अणु
	u32 ret;

	__sst_dac_ग_लिखो(vbase, DACREG_ADDR_I, reg);
	ret = __sst_dac_पढ़ो(vbase, DACREG_DATA_I);
	r_dprपूर्णांकk("sst_dac_read_i(%#x): %#x\n", reg, ret);
	वापस ret;
पूर्ण
अटल व्योम __dac_i_ग_लिखो(u8 __iomem *vbase, u8 reg,u8 val)
अणु
	r_dprपूर्णांकk("sst_dac_write_i(%#x, %#x)\n", reg, val);
	__sst_dac_ग_लिखो(vbase, DACREG_ADDR_I, reg);
	__sst_dac_ग_लिखो(vbase, DACREG_DATA_I, val);
पूर्ण

/* compute the m,n,p  , वापसs the real freq
 * (ics datasheet :  N <-> N1 , P <-> N2)
 *
 * Fout= Fref * (M+2)/( 2^P * (N+2))
 *  we try to get बंद to the asked freq
 *  with P as high, and M as low as possible
 * range:
 * ti/att : 0 <= M <= 255; 0 <= P <= 3; 0<= N <= 63
 * ics    : 1 <= M <= 127; 0 <= P <= 3; 1<= N <= 31
 * we'll use the lowest limitation, should be precise enouth
 */
अटल पूर्णांक sst_calc_pll(स्थिर पूर्णांक freq, पूर्णांक *freq_out, काष्ठा pll_timing *t)
अणु
	पूर्णांक m, m2, n, p, best_err, fout;
	पूर्णांक best_n = -1;
	पूर्णांक best_m = -1;

	best_err = freq;
	p = 3;
	/* f * 2^P = vco should be less than VCOmax ~ 250 MHz क्रम ics*/
	जबतक (((1 << p) * freq > VCO_MAX) && (p >= 0))
		p--;
	अगर (p == -1)
		वापस -EINVAL;
	क्रम (n = 1; n < 32; n++) अणु
		/* calc 2 * m so we can round it later*/
		m2 = (2 * freq * (1 << p) * (n + 2) ) / DAC_FREF - 4 ;

		m = (m2 % 2 ) ? m2/2+1 : m2/2 ;
		अगर (m >= 128)
			अवरोध;
		fout = (DAC_FREF * (m + 2)) / ((1 << p) * (n + 2));
		अगर ((असल(fout - freq) < best_err) && (m > 0)) अणु
			best_n = n;
			best_m = m;
			best_err = असल(fout - freq);
			/* we get the lowest m , allowing 0.5% error in freq*/
			अगर (200*best_err < freq) अवरोध;
		पूर्ण
	पूर्ण
	अगर (best_n == -1)  /* unlikely, but who knows ? */
		वापस -EINVAL;
	t->p = p;
	t->n = best_n;
	t->m = best_m;
	*freq_out = (DAC_FREF * (t->m + 2)) / ((1 << t->p) * (t->n + 2));
	f_ddprपूर्णांकk ("m: %d, n: %d, p: %d, F: %dKhz\n",
		  t->m, t->n, t->p, *freq_out);
	वापस 0;
पूर्ण

/*
 * clear lfb screen
 */
अटल व्योम sstfb_clear_screen(काष्ठा fb_info *info)
अणु
	/* clear screen */
	fb_स_रखो(info->screen_base, 0, info->fix.smem_len);
पूर्ण


/**
 *      sstfb_check_var - Optional function.  Validates a var passed in.
 *      @var: frame buffer variable screen काष्ठाure
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Limit to the abilities of a single chip as SLI is not supported
 *	by this driver.
 */

अटल पूर्णांक sstfb_check_var(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info)
अणु
	काष्ठा sstfb_par *par = info->par;
	पूर्णांक hSyncOff   = var->xres + var->right_margin + var->left_margin;
	पूर्णांक vSyncOff   = var->yres + var->lower_margin + var->upper_margin;
	पूर्णांक vBackPorch = var->left_margin, yDim = var->yres;
	पूर्णांक vSyncOn    = var->vsync_len;
	पूर्णांक tiles_in_X, real_length;
	अचिन्हित पूर्णांक freq;

	अगर (sst_calc_pll(PICOS2KHZ(var->pixघड़ी), &freq, &par->pll)) अणु
		prपूर्णांकk(KERN_ERR "sstfb: Pixclock at %ld KHZ out of range\n",
				PICOS2KHZ(var->pixघड़ी));
		वापस -EINVAL;
	पूर्ण
	var->pixघड़ी = KHZ2PICOS(freq);
	
	अगर (var->vmode & FB_VMODE_INTERLACED)
		vBackPorch += (vBackPorch % 2);
	अगर (var->vmode & FB_VMODE_DOUBLE) अणु
		vBackPorch <<= 1;
		yDim <<=1;
		vSyncOn <<=1;
		vSyncOff <<=1;
	पूर्ण

	चयन (var->bits_per_pixel) अणु
	हाल 0 ... 16 :
		var->bits_per_pixel = 16;
		अवरोध;
	शेष :
		prपूर्णांकk(KERN_ERR "sstfb: Unsupported bpp %d\n", var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण
	
	/* validity tests */
	अगर (var->xres <= 1 || yDim <= 0 || var->hsync_len <= 1  ||
	    hSyncOff <= 1  || var->left_margin <= 2  || vSyncOn <= 0 ||
	    vSyncOff <= 0 || vBackPorch <= 0) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (IS_VOODOO2(par)) अणु
		/* Vooकरोo 2 limits */
		tiles_in_X = (var->xres + 63 ) / 64 * 2;		

		अगर (var->xres  > POW2(11) || yDim >= POW2(11)) अणु
			prपूर्णांकk(KERN_ERR "sstfb: Unsupported resolution %dx%d\n",
			         var->xres, var->yres);
			वापस -EINVAL;
		पूर्ण

		अगर (var->hsync_len > POW2(9) || hSyncOff > POW2(11) ||
		    var->left_margin - 2 >= POW2(9) || vSyncOn >= POW2(13) ||
		    vSyncOff >= POW2(13) || vBackPorch >= POW2(9) ||
		    tiles_in_X >= POW2(6) || tiles_in_X <= 0) अणु
			prपूर्णांकk(KERN_ERR "sstfb: Unsupported timings\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Vooकरोo limits */
		tiles_in_X = (var->xres + 63 ) / 64;

		अगर (var->vmode) अणु
			prपूर्णांकk(KERN_ERR "sstfb: Interlace/doublescan not supported %#x\n",
				var->vmode);
			वापस -EINVAL;
		पूर्ण
		अगर (var->xres > POW2(10) || var->yres >= POW2(10)) अणु
			prपूर्णांकk(KERN_ERR "sstfb: Unsupported resolution %dx%d\n",
			         var->xres, var->yres);
			वापस -EINVAL;
		पूर्ण
		अगर (var->hsync_len > POW2(8) || hSyncOff - 1 > POW2(10) ||
		    var->left_margin - 2 >= POW2(8) || vSyncOn >= POW2(12) ||
		    vSyncOff >= POW2(12) || vBackPorch >= POW2(8) ||
		    tiles_in_X >= POW2(4) || tiles_in_X <= 0) अणु
			prपूर्णांकk(KERN_ERR "sstfb: Unsupported timings\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* it seems that the fbi uses tiles of 64x16 pixels to "map" the mem */
	/* FIXME: i करोn't like this... looks wrong */
	real_length = tiles_in_X  * (IS_VOODOO2(par) ? 32 : 64 )
	              * ((var->bits_per_pixel == 16) ? 2 : 4);

	अगर (real_length * yDim > info->fix.smem_len) अणु
		prपूर्णांकk(KERN_ERR "sstfb: Not enough video memory\n");
		वापस -ENOMEM;
	पूर्ण

	var->sync &= (FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT);
	var->vmode &= (FB_VMODE_INTERLACED | FB_VMODE_DOUBLE);
	var->xoffset = 0;
	var->yoffset = 0;
	var->height  = -1;
	var->width   = -1;

	/*
	 * correct the color bit fields
	 */
	/* var->अणुred|green|blueपूर्ण.msb_right = 0; */

	चयन (var->bits_per_pixel) अणु
	हाल 16:	/* RGB 565  LfbMode 0 */
		var->red.length    = 5;
		var->green.length  = 6;
		var->blue.length   = 5;
		var->transp.length = 0;

		var->red.offset    = 11;
		var->green.offset  = 5;
		var->blue.offset   = 0;
		var->transp.offset = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *      sstfb_set_par - Optional function.  Alters the hardware state.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक sstfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा sstfb_par *par = info->par;
	u32 lfbmode, fbiinit1, fbiinit2, fbiinit3, fbiinit5, fbiinit6=0;
	काष्ठा pci_dev *sst_dev = par->dev;
	अचिन्हित पूर्णांक freq;
	पूर्णांक ntiles;

	par->hSyncOff	= info->var.xres + info->var.right_margin + info->var.left_margin;

	par->yDim 	= info->var.yres;
	par->vSyncOn 	= info->var.vsync_len;
	par->vSyncOff	= info->var.yres + info->var.lower_margin + info->var.upper_margin;
	par->vBackPorch = info->var.upper_margin;

	/* We need par->pll */
	sst_calc_pll(PICOS2KHZ(info->var.pixघड़ी), &freq, &par->pll);

	अगर (info->var.vmode & FB_VMODE_INTERLACED)
		par->vBackPorch += (par->vBackPorch % 2);
	अगर (info->var.vmode & FB_VMODE_DOUBLE) अणु
		par->vBackPorch <<= 1;
		par->yDim <<=1;
		par->vSyncOn <<=1;
		par->vSyncOff <<=1;
	पूर्ण

	अगर (IS_VOODOO2(par)) अणु
		/* vooकरोo2 has 32 pixel wide tiles , BUT strange things
		   happen with odd number of tiles */
		par->tiles_in_X = (info->var.xres + 63 ) / 64 * 2;
	पूर्ण अन्यथा अणु
		/* vooकरोo1 has 64 pixels wide tiles. */
		par->tiles_in_X = (info->var.xres + 63 ) / 64;
	पूर्ण

	f_ddprपूर्णांकk("hsync_len hSyncOff vsync_len vSyncOff\n");
	f_ddprपूर्णांकk("%-7d %-8d %-7d %-8d\n",
	           info->var.hsync_len, par->hSyncOff,
	           par->vSyncOn, par->vSyncOff);
	f_ddprपूर्णांकk("left_margin upper_margin xres yres Freq\n");
	f_ddprपूर्णांकk("%-10d %-10d %-4d %-4d %-8ld\n",
	           info->var.left_margin, info->var.upper_margin,
	           info->var.xres, info->var.yres, PICOS2KHZ(info->var.pixघड़ी));

	sst_ग_लिखो(NOPCMD, 0);
	sst_रुको_idle();
	pci_ग_लिखो_config_dword(sst_dev, PCI_INIT_ENABLE, PCI_EN_INIT_WR);
	sst_set_bits(FBIINIT1, VIDEO_RESET);
	sst_set_bits(FBIINIT0, FBI_RESET | FIFO_RESET);
	sst_unset_bits(FBIINIT2, EN_DRAM_REFRESH);
	sst_रुको_idle();

	/*sst_unset_bits (FBIINIT0, FBI_RESET); / reenable FBI ? */

	sst_ग_लिखो(BACKPORCH, par->vBackPorch << 16 | (info->var.left_margin - 2));
	sst_ग_लिखो(VIDEODIMENSIONS, par->yDim << 16 | (info->var.xres - 1));
	sst_ग_लिखो(HSYNC, (par->hSyncOff - 1) << 16 | (info->var.hsync_len - 1));
	sst_ग_लिखो(VSYNC,       par->vSyncOff << 16 | par->vSyncOn);

	fbiinit2 = sst_पढ़ो(FBIINIT2);
	fbiinit3 = sst_पढ़ो(FBIINIT3);

	/* everything is reset. we enable fbiinit2/3 remap : dac access ok */
	pci_ग_लिखो_config_dword(sst_dev, PCI_INIT_ENABLE,
	                       PCI_EN_INIT_WR | PCI_REMAP_DAC );

	par->dac_sw.set_vidmod(info, info->var.bits_per_pixel);

	/* set video घड़ी */
	par->dac_sw.set_pll(info, &par->pll, VID_CLOCK);

	/* disable fbiinit2/3 remap */
	pci_ग_लिखो_config_dword(sst_dev, PCI_INIT_ENABLE,
	                       PCI_EN_INIT_WR);

	/* restore fbiinit2/3 */
	sst_ग_लिखो(FBIINIT2,fbiinit2);
	sst_ग_लिखो(FBIINIT3,fbiinit3);

	fbiinit1 = (sst_पढ़ो(FBIINIT1) & VIDEO_MASK)
	            | EN_DATA_OE
	            | EN_BLANK_OE
	            | EN_HVSYNC_OE
	            | EN_DCLK_OE
		 /* | (15 << TILES_IN_X_SHIFT) */
	            | SEL_INPUT_VCLK_2X
		 /* | (2 << VCLK_2X_SEL_DEL_SHIFT)
	            | (2 << VCLK_DEL_SHIFT) */;
/* try with vclk_in_delay =0 (bits 29:30) , vclk_out_delay =0 (bits(27:28)
 in (near) future set them accordingly to revision + resolution (cf glide)
 first understand what it stands क्रम :)
 FIXME: there are some artefacts... check क्रम the vclk_in_delay
 lets try with 6ns delay in both vclk_out & in...
 करोh... they're still there :\
*/

	ntiles = par->tiles_in_X;
	अगर (IS_VOODOO2(par)) अणु
		fbiinit1 |= ((ntiles & 0x20) >> 5) << TILES_IN_X_MSB_SHIFT
		            | ((ntiles & 0x1e) >> 1) << TILES_IN_X_SHIFT;
/* as the only value of importance क्रम us in fbiinit6 is tiles in X (lsb),
   and as पढ़ोing fbinit 6 will वापस crap (see FBIINIT6_DEFAULT) we just
   ग_लिखो our value. BTW due to the dac unable to पढ़ो odd number of tiles, this
   field is always null ... */
		fbiinit6 = (ntiles & 0x1) << TILES_IN_X_LSB_SHIFT;
	पूर्ण
	अन्यथा
		fbiinit1 |= ntiles << TILES_IN_X_SHIFT;

	चयन (info->var.bits_per_pixel) अणु
	हाल 16:
		fbiinit1 |=  SEL_SOURCE_VCLK_2X_SEL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	sst_ग_लिखो(FBIINIT1, fbiinit1);
	अगर (IS_VOODOO2(par)) अणु
		sst_ग_लिखो(FBIINIT6, fbiinit6);
		fbiinit5=sst_पढ़ो(FBIINIT5) & FBIINIT5_MASK ;
		अगर (info->var.vmode & FB_VMODE_INTERLACED)
			fbiinit5 |= INTERLACE;
		अगर (info->var.vmode & FB_VMODE_DOUBLE)
			fbiinit5 |= VDOUBLESCAN;
		अगर (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
			fbiinit5 |= HSYNC_HIGH;
		अगर (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
			fbiinit5 |= VSYNC_HIGH;
		sst_ग_लिखो(FBIINIT5, fbiinit5);
	पूर्ण
	sst_रुको_idle();
	sst_unset_bits(FBIINIT1, VIDEO_RESET);
	sst_unset_bits(FBIINIT0, FBI_RESET | FIFO_RESET);
	sst_set_bits(FBIINIT2, EN_DRAM_REFRESH);
	/* disables fbiinit ग_लिखोs */
	pci_ग_लिखो_config_dword(sst_dev, PCI_INIT_ENABLE, PCI_EN_FIFO_WR);

	/* set lfbmode : set mode + front buffer क्रम पढ़ोs/ग_लिखोs
	   + disable pipeline */
	चयन (info->var.bits_per_pixel) अणु
	हाल 16:
		lfbmode = LFB_565;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

#अगर defined(__BIG_ENDIAN)
	/* Enable byte-swizzle functionality in hardware.
	 * With this enabled, all our पढ़ो- and ग_लिखो-accesses to
	 * the vooकरोo framebuffer can be करोne in native क्रमmat, and
	 * the hardware will स्वतःmatically convert it to little-endian.
	 * - tested on HP-PARISC, Helge Deller <deller@gmx.de> */
	lfbmode |= ( LFB_WORD_SWIZZLE_WR | LFB_BYTE_SWIZZLE_WR |
		     LFB_WORD_SWIZZLE_RD | LFB_BYTE_SWIZZLE_RD );
#पूर्ण_अगर
	
	अगर (clipping) अणु
		sst_ग_लिखो(LFBMODE, lfbmode | EN_PXL_PIPELINE);
	/*
	 * Set "clipping" dimensions. If clipping is disabled and
	 * ग_लिखोs to offscreen areas of the framebuffer are perक्रमmed,
	 * the "behaviour is undefined" (_very_ undefined) - Urs
	 */
	/* btw, it requires enabling pixel pipeline in LFBMODE .
	   off screen पढ़ो/ग_लिखोs will just wrap and पढ़ो/prपूर्णांक pixels
	   on screen. Ugly but not that dangerous */
		f_ddprपूर्णांकk("setting clipping dimensions 0..%d, 0..%d\n",
		            info->var.xres - 1, par->yDim - 1);

		sst_ग_लिखो(CLIP_LEFT_RIGHT, info->var.xres);
		sst_ग_लिखो(CLIP_LOWY_HIGHY, par->yDim);
		sst_set_bits(FBZMODE, EN_CLIPPING | EN_RGB_WRITE);
	पूर्ण अन्यथा अणु
		/* no clipping : direct access, no pipeline */
		sst_ग_लिखो(LFBMODE, lfbmode);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *      sstfb_setcolreg - Optional function. Sets a color रेजिस्टर.
 *      @regno: hardware colormap रेजिस्टर
 *      @red: frame buffer colormap काष्ठाure
 *      @green: The green value which can be up to 16 bits wide
 *      @blue:  The blue value which can be up to 16 bits wide.
 *      @transp: If supported the alpha value which can be up to 16 bits wide.
 *      @info: frame buffer info काष्ठाure
 */
अटल पूर्णांक sstfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
                           u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा sstfb_par *par = info->par;
	u32 col;

	f_dddprपूर्णांकk("sstfb_setcolreg\n");
	f_dddprपूर्णांकk("%-2d rgbt: %#x, %#x, %#x, %#x\n",
	            regno, red, green, blue, transp);
	अगर (regno > 15)
		वापस 0;

	red    >>= (16 - info->var.red.length);
	green  >>= (16 - info->var.green.length);
	blue   >>= (16 - info->var.blue.length);
	transp >>= (16 - info->var.transp.length);
	col = (red << info->var.red.offset)
	    | (green << info->var.green.offset)
	    | (blue  << info->var.blue.offset)
	    | (transp << info->var.transp.offset);
	
	par->palette[regno] = col;

	वापस 0;
पूर्ण

अटल व्योम sstfb_setvgapass( काष्ठा fb_info *info, पूर्णांक enable )
अणु
	काष्ठा sstfb_par *par = info->par;
	काष्ठा pci_dev *sst_dev = par->dev;
	u32 fbiinit0, पंचांगp;

	enable = enable ? 1:0;
	अगर (par->vgapass == enable)
		वापस;
	par->vgapass = enable;

	pci_पढ़ो_config_dword(sst_dev, PCI_INIT_ENABLE, &पंचांगp);
	pci_ग_लिखो_config_dword(sst_dev, PCI_INIT_ENABLE,
			       पंचांगp | PCI_EN_INIT_WR );
	fbiinit0 = sst_पढ़ो (FBIINIT0);
	अगर (par->vgapass) अणु
		sst_ग_लिखो(FBIINIT0, fbiinit0 & ~DIS_VGA_PASSTHROUGH);
		fb_info(info, "Enabling VGA pass-through\n");
	पूर्ण अन्यथा अणु
		sst_ग_लिखो(FBIINIT0, fbiinit0 | DIS_VGA_PASSTHROUGH);
		fb_info(info, "Disabling VGA pass-through\n");
	पूर्ण
	pci_ग_लिखो_config_dword(sst_dev, PCI_INIT_ENABLE, पंचांगp);
पूर्ण

अटल sमाप_प्रकार store_vgapass(काष्ठा device *device, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(device);
	अक्षर ** last = शून्य;
	पूर्णांक val;

	val = simple_म_से_अदीर्घ(buf, last, 0);
	sstfb_setvgapass(info, val);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_vgapass(काष्ठा device *device, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(device);
	काष्ठा sstfb_par *par = info->par;
	वापस प्र_लिखो(buf, "%d\n", par->vgapass);
पूर्ण

अटल काष्ठा device_attribute device_attrs[] = अणु
	__ATTR(vgapass, S_IRUGO|S_IWUSR, show_vgapass, store_vgapass)
	पूर्ण;

अटल पूर्णांक sstfb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा sstfb_par *par;
	u32 val;

	चयन (cmd) अणु
	/* set/get VGA pass_through mode */
	हाल SSTFB_SET_VGAPASS:
		अगर (copy_from_user(&val, (व्योम __user *)arg, माप(val)))
			वापस -EFAULT;
		sstfb_setvgapass(info, val);
		वापस 0;
	हाल SSTFB_GET_VGAPASS:
		par = info->par;
		val = par->vgapass;
		अगर (copy_to_user((व्योम __user *)arg, &val, माप(val)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण


/*
 * Screen-to-Screen BitBlt 2D command (क्रम the bmove fb op.) - Vooकरोo2 only
 */
#अगर 0
अटल व्योम sstfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा sstfb_par *par = info->par;
	u32 stride = info->fix.line_length;
   
	अगर (!IS_VOODOO2(par))
		वापस;

	sst_ग_लिखो(BLTSRCBASEADDR, 0);
	sst_ग_लिखो(BLTDSTBASEADDR, 0);
	sst_ग_लिखो(BLTROP, BLTROP_COPY);
	sst_ग_लिखो(BLTXYSTRIDES, stride | (stride << 16));
	sst_ग_लिखो(BLTSRCXY, area->sx | (area->sy << 16));
	sst_ग_लिखो(BLTDSTXY, area->dx | (area->dy << 16));
	sst_ग_लिखो(BLTSIZE, area->width | (area->height << 16));
	sst_ग_लिखो(BLTCOMMAND, BLT_SCR2SCR_BITBLT | LAUNCH_BITBLT |
		(BLT_16BPP_FMT << 3) /* | BIT(14) */ | BIT(15) );
	sst_रुको_idle();
पूर्ण
#पूर्ण_अगर


/*
 * FillRect 2D command (solidfill or invert (via ROP_XOR)) - Vooकरोo2 only
 */
#अगर 0
अटल व्योम sstfb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect) 
अणु
	काष्ठा sstfb_par *par = info->par;
	u32 stride = info->fix.line_length;

	अगर (!IS_VOODOO2(par))
		वापस;
   	
	sst_ग_लिखो(BLTCLIPX, info->var.xres);
	sst_ग_लिखो(BLTCLIPY, info->var.yres);
	
	sst_ग_लिखो(BLTDSTBASEADDR, 0);
	sst_ग_लिखो(BLTCOLOR, rect->color);
	sst_ग_लिखो(BLTROP, rect->rop == ROP_COPY ? BLTROP_COPY : BLTROP_XOR);
	sst_ग_लिखो(BLTXYSTRIDES, stride | (stride << 16));
	sst_ग_लिखो(BLTDSTXY, rect->dx | (rect->dy << 16));
	sst_ग_लिखो(BLTSIZE, rect->width | (rect->height << 16));
	sst_ग_लिखो(BLTCOMMAND, BLT_RECFILL_BITBLT | LAUNCH_BITBLT
		 | (BLT_16BPP_FMT << 3) /* | BIT(14) */ | BIT(15) | BIT(16) );
	sst_रुको_idle();
पूर्ण
#पूर्ण_अगर



/* 
 * get lfb size 
 */
अटल पूर्णांक sst_get_memsize(काष्ठा fb_info *info, __u32 *memsize)
अणु
	u8 __iomem *fbbase_virt = info->screen_base;

	/* क्रमce memsize */
	अगर (mem >= 1  && mem <= 4) अणु
		*memsize = (mem * 0x100000);
		prपूर्णांकk(KERN_INFO "supplied memsize: %#x\n", *memsize);
		वापस 1;
	पूर्ण

	ग_लिखोl(0xdeadbeef, fbbase_virt);
	ग_लिखोl(0xdeadbeef, fbbase_virt+0x100000);
	ग_लिखोl(0xdeadbeef, fbbase_virt+0x200000);
	f_ddprपूर्णांकk("0MB: %#x, 1MB: %#x, 2MB: %#x\n",
	           पढ़ोl(fbbase_virt), पढ़ोl(fbbase_virt + 0x100000),
	           पढ़ोl(fbbase_virt + 0x200000));

	ग_लिखोl(0xabcdef01, fbbase_virt);

	f_ddprपूर्णांकk("0MB: %#x, 1MB: %#x, 2MB: %#x\n",
	           पढ़ोl(fbbase_virt), पढ़ोl(fbbase_virt + 0x100000),
	           पढ़ोl(fbbase_virt + 0x200000));

	/* checks क्रम 4mb lfb, then 2, then शेषs to 1 */
	अगर (पढ़ोl(fbbase_virt + 0x200000) == 0xdeadbeef)
		*memsize = 0x400000;
	अन्यथा अगर (पढ़ोl(fbbase_virt + 0x100000) == 0xdeadbeef)
		*memsize = 0x200000;
	अन्यथा
		*memsize = 0x100000;
	f_ddprपूर्णांकk("detected memsize: %dMB\n", *memsize >> 20);
	वापस 1;
पूर्ण


/* 
 * DAC detection routines 
 */

/* fbi should be idle, and fअगरo emty and mem disabled */
/* supposed to detect AT&T ATT20C409 and Ti TVP3409 ramdacs */

अटल पूर्णांक sst_detect_att(काष्ठा fb_info *info)
अणु
	काष्ठा sstfb_par *par = info->par;
	पूर्णांक i, mir, dir;

	क्रम (i = 0; i < 3; i++) अणु
		sst_dac_ग_लिखो(DACREG_WMA, 0); 	/* backकरोor */
		sst_dac_पढ़ो(DACREG_RMR);	/* पढ़ो 4 बार RMR */
		sst_dac_पढ़ो(DACREG_RMR);
		sst_dac_पढ़ो(DACREG_RMR);
		sst_dac_पढ़ो(DACREG_RMR);
		/* the fअगरth समय,  CR0 is पढ़ो */
		sst_dac_पढ़ो(DACREG_RMR);
		/* the 6th, manufacturer id रेजिस्टर */
		mir = sst_dac_पढ़ो(DACREG_RMR);
		/*the 7th, device ID रेजिस्टर */
		dir = sst_dac_पढ़ो(DACREG_RMR);
		f_ddprपूर्णांकk("mir: %#x, dir: %#x\n", mir, dir);
		अगर (mir == DACREG_MIR_ATT && dir == DACREG_सूची_ATT) अणु
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sst_detect_ti(काष्ठा fb_info *info)
अणु
	काष्ठा sstfb_par *par = info->par;
	पूर्णांक i, mir, dir;

	क्रम (i = 0; i<3; i++) अणु
		sst_dac_ग_लिखो(DACREG_WMA, 0); 	/* backकरोor */
		sst_dac_पढ़ो(DACREG_RMR);	/* पढ़ो 4 बार RMR */
		sst_dac_पढ़ो(DACREG_RMR);
		sst_dac_पढ़ो(DACREG_RMR);
		sst_dac_पढ़ो(DACREG_RMR);
		/* the fअगरth समय,  CR0 is पढ़ो */
		sst_dac_पढ़ो(DACREG_RMR);
		/* the 6th, manufacturer id रेजिस्टर */
		mir = sst_dac_पढ़ो(DACREG_RMR);
		/*the 7th, device ID रेजिस्टर */
		dir = sst_dac_पढ़ो(DACREG_RMR);
		f_ddprपूर्णांकk("mir: %#x, dir: %#x\n", mir, dir);
		अगर ((mir == DACREG_MIR_TI ) && (dir == DACREG_सूची_TI)) अणु
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * try to detect ICS5342  ramdac
 * we get the 1st byte (M value) of preset f1,f7 and fB
 * why those 3 ? mmmh... क्रम now, i'll करो it the glide way...
 * and ask questions later. anyway, it seems that all the freq रेजिस्टरs are
 * really at their शेष state (cf specs) so i ask again, why those 3 regs ?
 * mmmmh.. it seems that's much more ugly than i thought. we use f0 and fA क्रम
 * pll programming, so in fact, we *hope* that the f1, f7 & fB won't be
 * touched...
 * is it really safe ? how can i reset this ramdac ? geee...
 */
अटल पूर्णांक sst_detect_ics(काष्ठा fb_info *info)
अणु
	काष्ठा sstfb_par *par = info->par;
	पूर्णांक m_clk0_1, m_clk0_7, m_clk1_b;
	पूर्णांक n_clk0_1, n_clk0_7, n_clk1_b;
	पूर्णांक i;

	क्रम (i = 0; i<5; i++ ) अणु
		sst_dac_ग_लिखो(DACREG_ICS_PLLRMA, 0x1);	/* f1 */
		m_clk0_1 = sst_dac_पढ़ो(DACREG_ICS_PLLDATA);
		n_clk0_1 = sst_dac_पढ़ो(DACREG_ICS_PLLDATA);
		sst_dac_ग_लिखो(DACREG_ICS_PLLRMA, 0x7);	/* f7 */
		m_clk0_7 = sst_dac_पढ़ो(DACREG_ICS_PLLDATA);
		n_clk0_7 = sst_dac_पढ़ो(DACREG_ICS_PLLDATA);
		sst_dac_ग_लिखो(DACREG_ICS_PLLRMA, 0xb);	/* fB */
		m_clk1_b= sst_dac_पढ़ो(DACREG_ICS_PLLDATA);
		n_clk1_b= sst_dac_पढ़ो(DACREG_ICS_PLLDATA);
		f_ddprपूर्णांकk("m_clk0_1: %#x, m_clk0_7: %#x, m_clk1_b: %#x\n",
			m_clk0_1, m_clk0_7, m_clk1_b);
		f_ddprपूर्णांकk("n_clk0_1: %#x, n_clk0_7: %#x, n_clk1_b: %#x\n",
			n_clk0_1, n_clk0_7, n_clk1_b);
		अगर ((   m_clk0_1 == DACREG_ICS_PLL_CLK0_1_INI)
		    && (m_clk0_7 == DACREG_ICS_PLL_CLK0_7_INI)
		    && (m_clk1_b == DACREG_ICS_PLL_CLK1_B_INI)) अणु
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/*
 * gfx, video, pci fअगरo should be reset, dram refresh disabled
 * see detect_dac
 */

अटल पूर्णांक sst_set_pll_att_ti(काष्ठा fb_info *info, 
		स्थिर काष्ठा pll_timing *t, स्थिर पूर्णांक घड़ी)
अणु
	काष्ठा sstfb_par *par = info->par;
	u8 cr0, cc;

	/* enable indexed mode */
	sst_dac_ग_लिखो(DACREG_WMA, 0); 	/* backकरोor */
	sst_dac_पढ़ो(DACREG_RMR);	/* 1 समय:  RMR */
	sst_dac_पढ़ो(DACREG_RMR);	/* 2 RMR */
	sst_dac_पढ़ो(DACREG_RMR);	/* 3 //  */
	sst_dac_पढ़ो(DACREG_RMR);	/* 4 //  */
	cr0 = sst_dac_पढ़ो(DACREG_RMR);	/* 5 CR0 */

	sst_dac_ग_लिखो(DACREG_WMA, 0);
	sst_dac_पढ़ो(DACREG_RMR);
	sst_dac_पढ़ो(DACREG_RMR);
	sst_dac_पढ़ो(DACREG_RMR);
	sst_dac_पढ़ो(DACREG_RMR);
	sst_dac_ग_लिखो(DACREG_RMR, (cr0 & 0xf0)
	              | DACREG_CR0_EN_INDEXED
	              | DACREG_CR0_8BIT
	              | DACREG_CR0_PWDOWN );
	/* so, now we are in indexed mode . dunno अगर its common, but
	   i find this way of करोing things a little bit weird :p */

	udelay(300);
	cc = dac_i_पढ़ो(DACREG_CC_I);
	चयन (घड़ी) अणु
	हाल VID_CLOCK:
		dac_i_ग_लिखो(DACREG_AC0_I, t->m);
		dac_i_ग_लिखो(DACREG_AC1_I, t->p << 6 | t->n);
		dac_i_ग_लिखो(DACREG_CC_I,
		            (cc & 0x0f) | DACREG_CC_CLKA | DACREG_CC_CLKA_C);
		अवरोध;
	हाल GFX_CLOCK:
		dac_i_ग_लिखो(DACREG_BD0_I, t->m);
		dac_i_ग_लिखो(DACREG_BD1_I, t->p << 6 | t->n);
		dac_i_ग_लिखो(DACREG_CC_I,
		            (cc & 0xf0) | DACREG_CC_CLKB | DACREG_CC_CLKB_D);
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: wrong clock code '%d'\n",
		        __func__, घड़ी);
		वापस 0;
		पूर्ण
	udelay(300);

	/* घातer up the dac & वापस to "normal" non-indexed mode */
	dac_i_ग_लिखो(DACREG_CR0_I,
	            cr0 & ~DACREG_CR0_PWDOWN & ~DACREG_CR0_EN_INDEXED);
	वापस 1;
पूर्ण

अटल पूर्णांक sst_set_pll_ics(काष्ठा fb_info *info,
		स्थिर काष्ठा pll_timing *t, स्थिर पूर्णांक घड़ी)
अणु
	काष्ठा sstfb_par *par = info->par;
	u8 pll_ctrl;

	sst_dac_ग_लिखो(DACREG_ICS_PLLRMA, DACREG_ICS_PLL_CTRL);
	pll_ctrl = sst_dac_पढ़ो(DACREG_ICS_PLLDATA);
	चयन(घड़ी) अणु
	हाल VID_CLOCK:
		sst_dac_ग_लिखो(DACREG_ICS_PLLWMA, 0x0);	/* CLK0, f0 */
		sst_dac_ग_लिखो(DACREG_ICS_PLLDATA, t->m);
		sst_dac_ग_लिखो(DACREG_ICS_PLLDATA, t->p << 5 | t->n);
		/* selects freq f0 क्रम घड़ी 0 */
		sst_dac_ग_लिखो(DACREG_ICS_PLLWMA, DACREG_ICS_PLL_CTRL);
		sst_dac_ग_लिखो(DACREG_ICS_PLLDATA,
		              (pll_ctrl & 0xd8)
		              | DACREG_ICS_CLK0
		              | DACREG_ICS_CLK0_0);
		अवरोध;
	हाल GFX_CLOCK :
		sst_dac_ग_लिखो(DACREG_ICS_PLLWMA, 0xa);	/* CLK1, fA */
		sst_dac_ग_लिखो(DACREG_ICS_PLLDATA, t->m);
		sst_dac_ग_लिखो(DACREG_ICS_PLLDATA, t->p << 5 | t->n);
		/* selects freq fA क्रम घड़ी 1 */
		sst_dac_ग_लिखो(DACREG_ICS_PLLWMA, DACREG_ICS_PLL_CTRL);
		sst_dac_ग_लिखो(DACREG_ICS_PLLDATA,
		              (pll_ctrl & 0xef) | DACREG_ICS_CLK1_A);
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: wrong clock code '%d'\n",
		        __func__, घड़ी);
		वापस 0;
		पूर्ण
	udelay(300);
	वापस 1;
पूर्ण

अटल व्योम sst_set_vidmod_att_ti(काष्ठा fb_info *info, स्थिर पूर्णांक bpp)
अणु
	काष्ठा sstfb_par *par = info->par;
	u8 cr0;

	sst_dac_ग_लिखो(DACREG_WMA, 0); 	/* backकरोor */
	sst_dac_पढ़ो(DACREG_RMR);	/* पढ़ो 4 बार RMR */
	sst_dac_पढ़ो(DACREG_RMR);
	sst_dac_पढ़ो(DACREG_RMR);
	sst_dac_पढ़ो(DACREG_RMR);
	/* the fअगरth समय,  CR0 is पढ़ो */
	cr0 = sst_dac_पढ़ो(DACREG_RMR);

	sst_dac_ग_लिखो(DACREG_WMA, 0); 	/* backकरोor */
	sst_dac_पढ़ो(DACREG_RMR);	/* पढ़ो 4 बार RMR */
	sst_dac_पढ़ो(DACREG_RMR);
	sst_dac_पढ़ो(DACREG_RMR);
	sst_dac_पढ़ो(DACREG_RMR);
	/* cr0 */
	चयन(bpp) अणु
	हाल 16:
		sst_dac_ग_लिखो(DACREG_RMR, (cr0 & 0x0f) | DACREG_CR0_16BPP);
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: bad depth '%u'\n", __func__, bpp);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sst_set_vidmod_ics(काष्ठा fb_info *info, स्थिर पूर्णांक bpp)
अणु
	काष्ठा sstfb_par *par = info->par;

	चयन(bpp) अणु
	हाल 16:
		sst_dac_ग_लिखो(DACREG_ICS_CMD, DACREG_ICS_CMD_16BPP);
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: bad depth '%u'\n", __func__, bpp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * detect dac type
 * prerequisite : ग_लिखो to FbiInitx enabled, video and fbi and pci fअगरo reset,
 * dram refresh disabled, FbiInit remaped.
 * TODO: mmh.. maybe i should put the "prerequisite" in the func ...
 */


अटल काष्ठा dac_चयन dacs[] = अणु
	अणु	.name		= "TI TVP3409",
		.detect		= sst_detect_ti,
		.set_pll	= sst_set_pll_att_ti,
		.set_vidmod	= sst_set_vidmod_att_ti पूर्ण,

	अणु	.name		= "AT&T ATT20C409",
		.detect		= sst_detect_att,
		.set_pll	= sst_set_pll_att_ti,
		.set_vidmod	= sst_set_vidmod_att_ti पूर्ण,
	अणु	.name		= "ICS ICS5342",
		.detect		= sst_detect_ics,
		.set_pll	= sst_set_pll_ics,
		.set_vidmod	= sst_set_vidmod_ics पूर्ण,
पूर्ण;

अटल पूर्णांक sst_detect_dactype(काष्ठा fb_info *info, काष्ठा sstfb_par *par)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(dacs); i++) अणु
		ret = dacs[i].detect(info);
		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (!ret)
		वापस 0;
	f_dprपूर्णांकk("%s found %s\n", __func__, dacs[i].name);
	par->dac_sw = dacs[i];
	वापस 1;
पूर्ण

/*
 * Internal Routines
 */
अटल पूर्णांक sst_init(काष्ठा fb_info *info, काष्ठा sstfb_par *par)
अणु
	u32 fbiinit0, fbiinit1, fbiinit4;
	काष्ठा pci_dev *dev = par->dev;
	काष्ठा pll_timing gfx_timings;
	काष्ठा sst_spec *spec;
	पूर्णांक Fout;
	पूर्णांक gfx_घड़ी;

	spec = &vooकरोo_spec[par->type];
	f_ddprपूर्णांकk(" fbiinit0   fbiinit1   fbiinit2   fbiinit3   fbiinit4  "
	           " fbiinit6\n");
	f_ddprपूर्णांकk("%0#10x %0#10x %0#10x %0#10x %0#10x %0#10x\n",
	            sst_पढ़ो(FBIINIT0), sst_पढ़ो(FBIINIT1), sst_पढ़ो(FBIINIT2),
	            sst_पढ़ो(FBIINIT3), sst_पढ़ो(FBIINIT4), sst_पढ़ो(FBIINIT6));
	/* disable video घड़ी */
	pci_ग_लिखो_config_dword(dev, PCI_VCLK_DISABLE, 0);

	/* enable writing to init रेजिस्टरs, disable pci fअगरo */
	pci_ग_लिखो_config_dword(dev, PCI_INIT_ENABLE, PCI_EN_INIT_WR);
	/* reset video */
	sst_set_bits(FBIINIT1, VIDEO_RESET);
	sst_रुको_idle();
	/* reset gfx + pci fअगरo */
	sst_set_bits(FBIINIT0, FBI_RESET | FIFO_RESET);
	sst_रुको_idle();

	/* unreset fअगरo */
	/*sst_unset_bits(FBIINIT0, FIFO_RESET);
	sst_रुको_idle();*/
	/* unreset FBI */
	/*sst_unset_bits(FBIINIT0, FBI_RESET);
	sst_रुको_idle();*/

	/* disable dram refresh */
	sst_unset_bits(FBIINIT2, EN_DRAM_REFRESH);
	sst_रुको_idle();
	/* remap fbinit2/3 to dac */
	pci_ग_लिखो_config_dword(dev, PCI_INIT_ENABLE,
				PCI_EN_INIT_WR | PCI_REMAP_DAC );
	/* detect dac type */
	अगर (!sst_detect_dactype(info, par)) अणु
		prपूर्णांकk(KERN_ERR "sstfb: unknown dac type.\n");
		//FIXME watch it: we are not in a safe state, bad bad bad.
		वापस 0;
	पूर्ण

	/* set graphic घड़ी */
	gfx_घड़ी = spec->शेष_gfx_घड़ी;
	अगर ((gfxclk >10 ) && (gfxclk < spec->max_gfxclk)) अणु
		prपूर्णांकk(KERN_INFO "sstfb: Using supplied graphic freq : %dMHz\n", gfxclk);
		 gfx_घड़ी = gfxclk *1000;
	पूर्ण अन्यथा अगर (gfxclk) अणु
		prपूर्णांकk(KERN_WARNING "sstfb: %dMhz is way out of spec! Using default\n", gfxclk);
	पूर्ण

	sst_calc_pll(gfx_घड़ी, &Fout, &gfx_timings);
	par->dac_sw.set_pll(info, &gfx_timings, GFX_CLOCK);

	/* disable fbiinit remap */
	pci_ग_लिखो_config_dword(dev, PCI_INIT_ENABLE,
	                       PCI_EN_INIT_WR| PCI_EN_FIFO_WR );
	/* शेषs init रेजिस्टरs */
	/* FbiInit0: unreset gfx, unreset fअगरo */
	fbiinit0 = FBIINIT0_DEFAULT;
	fbiinit1 = FBIINIT1_DEFAULT;
	fbiinit4 = FBIINIT4_DEFAULT;
	par->vgapass = vgapass;
	अगर (par->vgapass)
		fbiinit0 &= ~DIS_VGA_PASSTHROUGH;
	अन्यथा
		fbiinit0 |= DIS_VGA_PASSTHROUGH;
	अगर (slowpci) अणु
		fbiinit1 |= SLOW_PCI_WRITES;
		fbiinit4 |= SLOW_PCI_READS;
	पूर्ण अन्यथा अणु
		fbiinit1 &= ~SLOW_PCI_WRITES;
		fbiinit4 &= ~SLOW_PCI_READS;
	पूर्ण
	sst_ग_लिखो(FBIINIT0, fbiinit0);
	sst_रुको_idle();
	sst_ग_लिखो(FBIINIT1, fbiinit1);
	sst_रुको_idle();
	sst_ग_लिखो(FBIINIT2, FBIINIT2_DEFAULT);
	sst_रुको_idle();
	sst_ग_लिखो(FBIINIT3, FBIINIT3_DEFAULT);
	sst_रुको_idle();
	sst_ग_लिखो(FBIINIT4, fbiinit4);
	sst_रुको_idle();
	अगर (IS_VOODOO2(par)) अणु
		sst_ग_लिखो(FBIINIT6, FBIINIT6_DEFAULT);
		sst_रुको_idle();
	पूर्ण

	pci_ग_लिखो_config_dword(dev, PCI_INIT_ENABLE, PCI_EN_FIFO_WR);
	pci_ग_लिखो_config_dword(dev, PCI_VCLK_ENABLE, 0);
	वापस 1;
पूर्ण

अटल व्योम sst_shutकरोwn(काष्ठा fb_info *info)
अणु
	काष्ठा sstfb_par *par = info->par;
	काष्ठा pci_dev *dev = par->dev;
	काष्ठा pll_timing gfx_timings;
	पूर्णांक Fout;

	/* reset video, gfx, fअगरo, disable dram + remap fbiinit2/3 */
	pci_ग_लिखो_config_dword(dev, PCI_INIT_ENABLE, PCI_EN_INIT_WR);
	sst_set_bits(FBIINIT1, VIDEO_RESET | EN_BLANKING);
	sst_unset_bits(FBIINIT2, EN_DRAM_REFRESH);
	sst_set_bits(FBIINIT0, FBI_RESET | FIFO_RESET);
	sst_रुको_idle();
	pci_ग_लिखो_config_dword(dev, PCI_INIT_ENABLE,
	                       PCI_EN_INIT_WR | PCI_REMAP_DAC);
	/* set 20Mhz gfx घड़ी */
	sst_calc_pll(20000, &Fout, &gfx_timings);
	par->dac_sw.set_pll(info, &gfx_timings, GFX_CLOCK);
	/* TODO maybe shutकरोwn the dac, vrefresh and so on... */
	pci_ग_लिखो_config_dword(dev, PCI_INIT_ENABLE,
	                       PCI_EN_INIT_WR);
	sst_unset_bits(FBIINIT0, FBI_RESET | FIFO_RESET | DIS_VGA_PASSTHROUGH);
	pci_ग_लिखो_config_dword(dev, PCI_VCLK_DISABLE,0);
	/* maybe keep fbiinit* and PCI_INIT_enable in the fb_info काष्ठा
	 * from start ? */
	pci_ग_लिखो_config_dword(dev, PCI_INIT_ENABLE, 0);

पूर्ण

/*
 * Interface to the world
 */
अटल पूर्णांक sstfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt) जारी;

		f_ddprपूर्णांकk("option %s\n", this_opt);

		अगर (!म_भेद(this_opt, "vganopass"))
			vgapass = 0;
		अन्यथा अगर (!म_भेद(this_opt, "vgapass"))
			vgapass = 1;
		अन्यथा अगर (!म_भेद(this_opt, "clipping"))
		        clipping = 1;
		अन्यथा अगर (!म_भेद(this_opt, "noclipping"))
		        clipping = 0;
		अन्यथा अगर (!म_भेद(this_opt, "fastpci"))
		        slowpci = 0;
		अन्यथा अगर (!म_भेद(this_opt, "slowpci"))
		        slowpci = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "mem:",4))
			mem = simple_म_से_अदीर्घ (this_opt+4, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "gfxclk:",7))
			gfxclk = simple_म_से_अदीर्घ (this_opt+7, शून्य, 0);
		अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा fb_ops sstfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= sstfb_check_var,
	.fb_set_par	= sstfb_set_par,
	.fb_setcolreg	= sstfb_setcolreg,
	.fb_fillrect	= cfb_fillrect, /* sstfb_fillrect */
	.fb_copyarea	= cfb_copyarea, /* sstfb_copyarea */
	.fb_imageblit	= cfb_imageblit,
	.fb_ioctl	= sstfb_ioctl,
पूर्ण;

अटल पूर्णांक sstfb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा fb_info *info;
	काष्ठा fb_fix_screeninfo *fix;
	काष्ठा sstfb_par *par;
	काष्ठा sst_spec *spec;
	पूर्णांक err;

	/* Enable device in PCI config. */
	अगर ((err=pci_enable_device(pdev))) अणु
		prपूर्णांकk(KERN_ERR "cannot enable device\n");
		वापस err;
	पूर्ण

	/* Allocate the fb and par काष्ठाures.  */
	info = framebuffer_alloc(माप(काष्ठा sstfb_par), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, info);
	
	par  = info->par;
	fix  = &info->fix;
	
	par->type = id->driver_data;
	spec = &vooकरोo_spec[par->type];
	f_ddprपूर्णांकk("found device : %s\n", spec->name);

	par->dev = pdev;
	par->revision = pdev->revision;

	fix->mmio_start = pci_resource_start(pdev,0);
	fix->mmio_len	= 0x400000;
	fix->smem_start = fix->mmio_start + 0x400000;

	अगर (!request_mem_region(fix->mmio_start, fix->mmio_len, "sstfb MMIO")) अणु
		prपूर्णांकk(KERN_ERR "sstfb: cannot reserve mmio memory\n");
		जाओ fail_mmio_mem;
	पूर्ण

	अगर (!request_mem_region(fix->smem_start, 0x400000,"sstfb FB")) अणु
		prपूर्णांकk(KERN_ERR "sstfb: cannot reserve fb memory\n");
		जाओ fail_fb_mem;
	पूर्ण

	par->mmio_vbase = ioremap(fix->mmio_start,
					fix->mmio_len);
	अगर (!par->mmio_vbase) अणु
		prपूर्णांकk(KERN_ERR "sstfb: cannot remap register area %#lx\n",
		        fix->mmio_start);
		जाओ fail_mmio_remap;
	पूर्ण
	info->screen_base = ioremap(fix->smem_start, 0x400000);
	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR "sstfb: cannot remap framebuffer %#lx\n",
		        fix->smem_start);
		जाओ fail_fb_remap;
	पूर्ण

	अगर (!sst_init(info, par)) अणु
		prपूर्णांकk(KERN_ERR "sstfb: Init failed\n");
		जाओ fail;
	पूर्ण
	sst_get_memsize(info, &fix->smem_len);
	strlcpy(fix->id, spec->name, माप(fix->id));

	prपूर्णांकk(KERN_INFO "%s (revision %d) with %s dac\n",
		fix->id, par->revision, par->dac_sw.name);
	prपूर्णांकk(KERN_INFO "framebuffer at %#lx, mapped to 0x%p, size %dMB\n",
	        fix->smem_start, info->screen_base,
	        fix->smem_len >> 20);

	f_ddprपूर्णांकk("regbase_virt: %p\n", par->mmio_vbase);
	f_ddprपूर्णांकk("membase_phys: %#lx\n", fix->smem_start);
	f_ddprपूर्णांकk("fbbase_virt: %p\n", info->screen_base);

	info->flags	= FBINFO_DEFAULT;
	info->fbops	= &sstfb_ops;
	info->pseuकरो_palette = par->palette;

	fix->type	= FB_TYPE_PACKED_PIXELS;
	fix->visual	= FB_VISUAL_TRUECOLOR;
	fix->accel	= FB_ACCEL_NONE;  /* FIXME */
	/*
	 * According to the specs, the linelength must be of 1024 *pixels*
	 * and the 24bpp mode is in fact a 32 bpp mode (and both are in
	 * fact dithered to 16bit).
	 */
	fix->line_length = 2048; /* शेष value, क्रम 24 or 32bit: 4096 */
	
	fb_find_mode(&info->var, info, mode_option, शून्य, 0, शून्य, 16);

	अगर (sstfb_check_var(&info->var, info)) अणु
		prपूर्णांकk(KERN_ERR "sstfb: invalid video mode.\n");
		जाओ fail;
	पूर्ण

	अगर (sstfb_set_par(info)) अणु
		prपूर्णांकk(KERN_ERR "sstfb: can't set default video mode.\n");
		जाओ fail;
	पूर्ण
	
	अगर (fb_alloc_cmap(&info->cmap, 256, 0)) अणु
		prपूर्णांकk(KERN_ERR "sstfb: can't alloc cmap memory.\n");
		जाओ fail;
	पूर्ण

	/* रेजिस्टर fb */
	info->device = &pdev->dev;
	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		prपूर्णांकk(KERN_ERR "sstfb: can't register framebuffer.\n");
		जाओ fail_रेजिस्टर;
	पूर्ण

	sstfb_clear_screen(info);

	अगर (device_create_file(info->dev, &device_attrs[0]))
		prपूर्णांकk(KERN_WARNING "sstfb: can't create sysfs entry.\n");


	fb_info(info, "%s frame buffer device at 0x%p\n",
		fix->id, info->screen_base);

	वापस 0;

fail_रेजिस्टर:
	fb_dealloc_cmap(&info->cmap);
fail:
	iounmap(info->screen_base);
fail_fb_remap:
	iounmap(par->mmio_vbase);
fail_mmio_remap:
	release_mem_region(fix->smem_start, 0x400000);
fail_fb_mem:
	release_mem_region(fix->mmio_start, info->fix.mmio_len);
fail_mmio_mem:
	framebuffer_release(info);
	वापस -ENXIO; 	/* no vooकरोo detected */
पूर्ण

अटल व्योम sstfb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sstfb_par *par;
	काष्ठा fb_info *info;

	info = pci_get_drvdata(pdev);
	par = info->par;
	
	device_हटाओ_file(info->dev, &device_attrs[0]);
	sst_shutकरोwn(info);
	iounmap(info->screen_base);
	iounmap(par->mmio_vbase);
	release_mem_region(info->fix.smem_start, 0x400000);
	release_mem_region(info->fix.mmio_start, info->fix.mmio_len);
	fb_dealloc_cmap(&info->cmap);
	unरेजिस्टर_framebuffer(info);
	framebuffer_release(info);
पूर्ण


अटल स्थिर काष्ठा pci_device_id sstfb_id_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_3DFX, PCI_DEVICE_ID_3DFX_VOODOO ),
		.driver_data = ID_VOODOO1, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_3DFX, PCI_DEVICE_ID_3DFX_VOODOO2),
		.driver_data = ID_VOODOO2, पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver sstfb_driver = अणु
	.name		= "sstfb",
	.id_table	= sstfb_id_tbl,
	.probe		= sstfb_probe,
	.हटाओ		= sstfb_हटाओ,
पूर्ण;


अटल पूर्णांक sstfb_init(व्योम)
अणु
	अक्षर *option = शून्य;

	अगर (fb_get_options("sstfb", &option))
		वापस -ENODEV;
	sstfb_setup(option);

	वापस pci_रेजिस्टर_driver(&sstfb_driver);
पूर्ण

अटल व्योम sstfb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sstfb_driver);
पूर्ण


module_init(sstfb_init);
module_निकास(sstfb_निकास);

MODULE_AUTHOR("(c) 2000,2002 Ghozlane Toumi <gtoumi@laposte.net>");
MODULE_DESCRIPTION("FBDev driver for 3dfx Voodoo Graphics and Voodoo2 based video boards");
MODULE_LICENSE("GPL");

module_param(mem, पूर्णांक, 0);
MODULE_PARM_DESC(mem, "Size of frame buffer memory in MB (1, 2, 4 MB, default=autodetect)");
module_param(vgapass, bool, 0);
MODULE_PARM_DESC(vgapass, "Enable VGA PassThrough mode (0 or 1) (default=0)");
module_param(clipping, bool, 0);
MODULE_PARM_DESC(clipping, "Enable clipping (slower, safer) (0 or 1) (default=1)");
module_param(gfxclk, पूर्णांक, 0);
MODULE_PARM_DESC(gfxclk, "Force graphic chip frequency in MHz. DANGEROUS. (default=auto)");
module_param(slowpci, bool, 0);
MODULE_PARM_DESC(slowpci, "Uses slow PCI settings (0 or 1) (default=0)");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Initial video mode (default=" DEFAULT_VIDEO_MODE ")");

