<शैली गुरु>
/*
 * linux/drivers/video/neofb.c -- NeoMagic Framebuffer Driver
 *
 * Copyright (c) 2001-2002  Denis Oliver Kropp <करोk@directfb.org>
 *
 *
 * Card specअगरic code is based on XFree86's neomagic driver.
 * Framebuffer framework code is based on code of cyber2000fb.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 *
 *
 * 0.4.1
 *  - Cosmetic changes (करोk)
 *
 * 0.4
 *  - Toshiba Libretto support, allow modes larger than LCD size अगर
 *    LCD is disabled, keep BIOS settings अगर पूर्णांकernal/बाह्यal display
 *    haven't been enabled explicitly
 *                          (Thomas J. Moore <dark@mama.indstate.edu>)
 *
 * 0.3.3
 *  - Porting over to new fbdev api. (jsimmons)
 *  
 * 0.3.2
 *  - got rid of all भग्नing poपूर्णांक (करोk) 
 *
 * 0.3.1
 *  - added module license (करोk)
 *
 * 0.3
 *  - hardware accelerated clear and move क्रम 2200 and above (करोk)
 *  - maximum allowed करोtघड़ी is handled now (करोk)
 *
 * 0.2.1
 *  - correct panning after X usage (करोk)
 *  - added module and kernel parameters (करोk)
 *  - no stretching अगर बाह्यal display is enabled (करोk)
 *
 * 0.2
 *  - initial version (करोk)
 *
 *
 * TODO
 * - ioctl क्रम पूर्णांकernal/बाह्यal चयनing
 * - blanking
 * - 32bit depth support, maybe impossible
 * - disable pan-on-sync, need specs
 *
 * BUGS
 * - white margin on bootup like with tdfxfb (colormap problem?)
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#अगर_घोषित CONFIG_TOSHIBA
#समावेश <linux/toshiba.h>
#पूर्ण_अगर

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <video/vga.h>
#समावेश <video/neomagic.h>

#घोषणा Nखातापूर्णB_VERSION "0.4.2"

/* --------------------------------------------------------------------- */

अटल bool पूर्णांकernal;
अटल bool बाह्यal;
अटल bool libretto;
अटल bool nostretch;
अटल bool nopciburst;
अटल अक्षर *mode_option = शून्य;

#अगर_घोषित MODULE

MODULE_AUTHOR("(c) 2001-2002  Denis Oliver Kropp <dok@convergence.de>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FBDev driver for NeoMagic PCI Chips");
module_param(पूर्णांकernal, bool, 0);
MODULE_PARM_DESC(पूर्णांकernal, "Enable output on internal LCD Display.");
module_param(बाह्यal, bool, 0);
MODULE_PARM_DESC(बाह्यal, "Enable output on external CRT.");
module_param(libretto, bool, 0);
MODULE_PARM_DESC(libretto, "Force Libretto 100/110 800x480 LCD.");
module_param(nostretch, bool, 0);
MODULE_PARM_DESC(nostretch,
		 "Disable stretching of modes smaller than LCD.");
module_param(nopciburst, bool, 0);
MODULE_PARM_DESC(nopciburst, "Disable PCI burst mode.");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Preferred video mode ('640x480-8@60', etc)");

#पूर्ण_अगर


/* --------------------------------------------------------------------- */

अटल biosMode bios8[] = अणु
	अणु320, 240, 0x40पूर्ण,
	अणु300, 400, 0x42पूर्ण,
	अणु640, 400, 0x20पूर्ण,
	अणु640, 480, 0x21पूर्ण,
	अणु800, 600, 0x23पूर्ण,
	अणु1024, 768, 0x25पूर्ण,
पूर्ण;

अटल biosMode bios16[] = अणु
	अणु320, 200, 0x2eपूर्ण,
	अणु320, 240, 0x41पूर्ण,
	अणु300, 400, 0x43पूर्ण,
	अणु640, 480, 0x31पूर्ण,
	अणु800, 600, 0x34पूर्ण,
	अणु1024, 768, 0x37पूर्ण,
पूर्ण;

अटल biosMode bios24[] = अणु
	अणु640, 480, 0x32पूर्ण,
	अणु800, 600, 0x35पूर्ण,
	अणु1024, 768, 0x38पूर्ण
पूर्ण;

#अगर_घोषित NO_32BIT_SUPPORT_YET
/* FIXME: guessed values, wrong */
अटल biosMode bios32[] = अणु
	अणु640, 480, 0x33पूर्ण,
	अणु800, 600, 0x36पूर्ण,
	अणु1024, 768, 0x39पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल अंतरभूत व्योम ग_लिखो_le32(पूर्णांक regindex, u32 val, स्थिर काष्ठा neofb_par *par)
अणु
	ग_लिखोl(val, par->neo2200 + par->cursorOff + regindex);
पूर्ण

अटल पूर्णांक neoFindMode(पूर्णांक xres, पूर्णांक yres, पूर्णांक depth)
अणु
	पूर्णांक xres_s;
	पूर्णांक i, size;
	biosMode *mode;

	चयन (depth) अणु
	हाल 8:
		size = ARRAY_SIZE(bios8);
		mode = bios8;
		अवरोध;
	हाल 16:
		size = ARRAY_SIZE(bios16);
		mode = bios16;
		अवरोध;
	हाल 24:
		size = ARRAY_SIZE(bios24);
		mode = bios24;
		अवरोध;
#अगर_घोषित NO_32BIT_SUPPORT_YET
	हाल 32:
		size = ARRAY_SIZE(bios32);
		mode = bios32;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		अगर (xres <= mode[i].x_res) अणु
			xres_s = mode[i].x_res;
			क्रम (; i < size; i++) अणु
				अगर (mode[i].x_res != xres_s)
					वापस mode[i - 1].mode;
				अगर (yres <= mode[i].y_res)
					वापस mode[i].mode;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस mode[size - 1].mode;
पूर्ण

/*
 * neoCalcVCLK --
 *
 * Determine the बंदst घड़ी frequency to the one requested.
 */
#घोषणा MAX_N 127
#घोषणा MAX_D 31
#घोषणा MAX_F 1

अटल व्योम neoCalcVCLK(स्थिर काष्ठा fb_info *info,
			काष्ठा neofb_par *par, दीर्घ freq)
अणु
	पूर्णांक n, d, f;
	पूर्णांक n_best = 0, d_best = 0, f_best = 0;
	दीर्घ f_best_dअगरf = 0x7ffff;

	क्रम (f = 0; f <= MAX_F; f++)
		क्रम (d = 0; d <= MAX_D; d++)
			क्रम (n = 0; n <= MAX_N; n++) अणु
				दीर्घ f_out;
				दीर्घ f_dअगरf;

				f_out = ((14318 * (n + 1)) / (d + 1)) >> f;
				f_dअगरf = असल(f_out - freq);
				अगर (f_dअगरf <= f_best_dअगरf) अणु
					f_best_dअगरf = f_dअगरf;
					n_best = n;
					d_best = d;
					f_best = f;
				पूर्ण
				अगर (f_out > freq)
					अवरोध;
			पूर्ण

	अगर (info->fix.accel == FB_ACCEL_NEOMAGIC_NM2200 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2230 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2360 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2380) अणु
		/* NOT_DONE:  We are trying the full range of the 2200 घड़ी.
		   We should be able to try n up to 2047 */
		par->VCLK3NumeratorLow = n_best;
		par->VCLK3NumeratorHigh = (f_best << 7);
	पूर्ण अन्यथा
		par->VCLK3NumeratorLow = n_best | (f_best << 7);

	par->VCLK3Denominator = d_best;

#अगर_घोषित Nखातापूर्णB_DEBUG
	prपूर्णांकk(KERN_DEBUG "neoVCLK: f:%ld NumLow=%d NumHi=%d Den=%d Df=%ld\n",
	       freq,
	       par->VCLK3NumeratorLow,
	       par->VCLK3NumeratorHigh,
	       par->VCLK3Denominator, f_best_dअगरf);
#पूर्ण_अगर
पूर्ण

/*
 * vgaHWInit --
 *      Handle the initialization, etc. of a screen.
 *      Return FALSE on failure.
 */

अटल पूर्णांक vgaHWInit(स्थिर काष्ठा fb_var_screeninfo *var,
		     काष्ठा neofb_par *par)
अणु
	पूर्णांक hsync_end = var->xres + var->right_margin + var->hsync_len;
	पूर्णांक htotal = (hsync_end + var->left_margin) >> 3;
	पूर्णांक vsync_start = var->yres + var->lower_margin;
	पूर्णांक vsync_end = vsync_start + var->vsync_len;
	पूर्णांक vtotal = vsync_end + var->upper_margin;

	par->MiscOutReg = 0x23;

	अगर (!(var->sync & FB_SYNC_HOR_HIGH_ACT))
		par->MiscOutReg |= 0x40;

	अगर (!(var->sync & FB_SYNC_VERT_HIGH_ACT))
		par->MiscOutReg |= 0x80;

	/*
	 * Time Sequencer
	 */
	par->Sequencer[0] = 0x00;
	par->Sequencer[1] = 0x01;
	par->Sequencer[2] = 0x0F;
	par->Sequencer[3] = 0x00;	/* Font select */
	par->Sequencer[4] = 0x0E;	/* Misc */

	/*
	 * CRTC Controller
	 */
	par->CRTC[0] = htotal - 5;
	par->CRTC[1] = (var->xres >> 3) - 1;
	par->CRTC[2] = (var->xres >> 3) - 1;
	par->CRTC[3] = ((htotal - 1) & 0x1F) | 0x80;
	par->CRTC[4] = ((var->xres + var->right_margin) >> 3);
	par->CRTC[5] = (((htotal - 1) & 0x20) << 2)
	    | (((hsync_end >> 3)) & 0x1F);
	par->CRTC[6] = (vtotal - 2) & 0xFF;
	par->CRTC[7] = (((vtotal - 2) & 0x100) >> 8)
	    | (((var->yres - 1) & 0x100) >> 7)
	    | ((vsync_start & 0x100) >> 6)
	    | (((var->yres - 1) & 0x100) >> 5)
	    | 0x10 | (((vtotal - 2) & 0x200) >> 4)
	    | (((var->yres - 1) & 0x200) >> 3)
	    | ((vsync_start & 0x200) >> 2);
	par->CRTC[8] = 0x00;
	par->CRTC[9] = (((var->yres - 1) & 0x200) >> 4) | 0x40;

	अगर (var->vmode & FB_VMODE_DOUBLE)
		par->CRTC[9] |= 0x80;

	par->CRTC[10] = 0x00;
	par->CRTC[11] = 0x00;
	par->CRTC[12] = 0x00;
	par->CRTC[13] = 0x00;
	par->CRTC[14] = 0x00;
	par->CRTC[15] = 0x00;
	par->CRTC[16] = vsync_start & 0xFF;
	par->CRTC[17] = (vsync_end & 0x0F) | 0x20;
	par->CRTC[18] = (var->yres - 1) & 0xFF;
	par->CRTC[19] = var->xres_भव >> 4;
	par->CRTC[20] = 0x00;
	par->CRTC[21] = (var->yres - 1) & 0xFF;
	par->CRTC[22] = (vtotal - 1) & 0xFF;
	par->CRTC[23] = 0xC3;
	par->CRTC[24] = 0xFF;

	/*
	 * are these unnecessary?
	 * vgaHWHBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN | KGA_ENABLE_ON_ZERO);
	 * vgaHWVBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN | KGA_ENABLE_ON_ZERO);
	 */

	/*
	 * Graphics Display Controller
	 */
	par->Graphics[0] = 0x00;
	par->Graphics[1] = 0x00;
	par->Graphics[2] = 0x00;
	par->Graphics[3] = 0x00;
	par->Graphics[4] = 0x00;
	par->Graphics[5] = 0x40;
	par->Graphics[6] = 0x05;	/* only map 64k VGA memory !!!! */
	par->Graphics[7] = 0x0F;
	par->Graphics[8] = 0xFF;


	par->Attribute[0] = 0x00;	/* standard colormap translation */
	par->Attribute[1] = 0x01;
	par->Attribute[2] = 0x02;
	par->Attribute[3] = 0x03;
	par->Attribute[4] = 0x04;
	par->Attribute[5] = 0x05;
	par->Attribute[6] = 0x06;
	par->Attribute[7] = 0x07;
	par->Attribute[8] = 0x08;
	par->Attribute[9] = 0x09;
	par->Attribute[10] = 0x0A;
	par->Attribute[11] = 0x0B;
	par->Attribute[12] = 0x0C;
	par->Attribute[13] = 0x0D;
	par->Attribute[14] = 0x0E;
	par->Attribute[15] = 0x0F;
	par->Attribute[16] = 0x41;
	par->Attribute[17] = 0xFF;
	par->Attribute[18] = 0x0F;
	par->Attribute[19] = 0x00;
	par->Attribute[20] = 0x00;
	वापस 0;
पूर्ण

अटल व्योम vgaHWLock(काष्ठा vgastate *state)
अणु
	/* Protect CRTC[0-7] */
	vga_wcrt(state->vgabase, 0x11, vga_rcrt(state->vgabase, 0x11) | 0x80);
पूर्ण

अटल व्योम vgaHWUnlock(व्योम)
अणु
	/* Unprotect CRTC[0-7] */
	vga_wcrt(शून्य, 0x11, vga_rcrt(शून्य, 0x11) & ~0x80);
पूर्ण

अटल व्योम neoLock(काष्ठा vgastate *state)
अणु
	vga_wgfx(state->vgabase, 0x09, 0x00);
	vgaHWLock(state);
पूर्ण

अटल व्योम neoUnlock(व्योम)
अणु
	vgaHWUnlock();
	vga_wgfx(शून्य, 0x09, 0x26);
पूर्ण

/*
 * VGA Palette management
 */
अटल पूर्णांक paletteEnabled = 0;

अटल अंतरभूत व्योम VGAenablePalette(व्योम)
अणु
	vga_r(शून्य, VGA_IS1_RC);
	vga_w(शून्य, VGA_ATT_W, 0x00);
	paletteEnabled = 1;
पूर्ण

अटल अंतरभूत व्योम VGAdisablePalette(व्योम)
अणु
	vga_r(शून्य, VGA_IS1_RC);
	vga_w(शून्य, VGA_ATT_W, 0x20);
	paletteEnabled = 0;
पूर्ण

अटल अंतरभूत व्योम VGAwATTR(u8 index, u8 value)
अणु
	अगर (paletteEnabled)
		index &= ~0x20;
	अन्यथा
		index |= 0x20;

	vga_r(शून्य, VGA_IS1_RC);
	vga_wattr(शून्य, index, value);
पूर्ण

अटल व्योम vgaHWProtect(पूर्णांक on)
अणु
	अचिन्हित अक्षर पंचांगp;

	पंचांगp = vga_rseq(शून्य, 0x01);
	अगर (on) अणु
		/*
		 * Turn off screen and disable sequencer.
		 */
		vga_wseq(शून्य, 0x00, 0x01);		/* Synchronous Reset */
		vga_wseq(शून्य, 0x01, पंचांगp | 0x20);	/* disable the display */

		VGAenablePalette();
	पूर्ण अन्यथा अणु
		/*
		 * Reenable sequencer, then turn on screen.
		 */
		vga_wseq(शून्य, 0x01, पंचांगp & ~0x20);	/* reenable display */
		vga_wseq(शून्य, 0x00, 0x03);		/* clear synchronousreset */

		VGAdisablePalette();
	पूर्ण
पूर्ण

अटल व्योम vgaHWRestore(स्थिर काष्ठा fb_info *info,
			 स्थिर काष्ठा neofb_par *par)
अणु
	पूर्णांक i;

	vga_w(शून्य, VGA_MIS_W, par->MiscOutReg);

	क्रम (i = 1; i < 5; i++)
		vga_wseq(शून्य, i, par->Sequencer[i]);

	/* Ensure CRTC रेजिस्टरs 0-7 are unlocked by clearing bit 7 or CRTC[17] */
	vga_wcrt(शून्य, 17, par->CRTC[17] & ~0x80);

	क्रम (i = 0; i < 25; i++)
		vga_wcrt(शून्य, i, par->CRTC[i]);

	क्रम (i = 0; i < 9; i++)
		vga_wgfx(शून्य, i, par->Graphics[i]);

	VGAenablePalette();

	क्रम (i = 0; i < 21; i++)
		VGAwATTR(i, par->Attribute[i]);

	VGAdisablePalette();
पूर्ण


/* -------------------- Hardware specअगरic routines ------------------------- */

/*
 * Hardware Acceleration क्रम Neo2200+
 */
अटल अंतरभूत पूर्णांक neo2200_sync(काष्ठा fb_info *info)
अणु
	काष्ठा neofb_par *par = info->par;

	जबतक (पढ़ोl(&par->neo2200->bltStat) & 1)
		cpu_relax();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम neo2200_रुको_fअगरo(काष्ठा fb_info *info,
				     पूर्णांक requested_fअगरo_space)
अणु
	//  ndev->neo.रुकोfअगरo_calls++;
	//  ndev->neo.रुकोfअगरo_sum += requested_fअगरo_space;

	/* FIXME: करोes not work
	   अगर (neo_fअगरo_space < requested_fअगरo_space)
	   अणु
	   neo_fअगरo_रुकोcycles++;

	   जबतक (1)
	   अणु
	   neo_fअगरo_space = (neo2200->bltStat >> 8);
	   अगर (neo_fअगरo_space >= requested_fअगरo_space)
	   अवरोध;
	   पूर्ण
	   पूर्ण
	   अन्यथा
	   अणु
	   neo_fअगरo_cache_hits++;
	   पूर्ण

	   neo_fअगरo_space -= requested_fअगरo_space;
	 */

	neo2200_sync(info);
पूर्ण

अटल अंतरभूत व्योम neo2200_accel_init(काष्ठा fb_info *info,
				      काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा neofb_par *par = info->par;
	Neo2200 __iomem *neo2200 = par->neo2200;
	u32 bltMod, pitch;

	neo2200_sync(info);

	चयन (var->bits_per_pixel) अणु
	हाल 8:
		bltMod = NEO_MODE1_DEPTH8;
		pitch = var->xres_भव;
		अवरोध;
	हाल 15:
	हाल 16:
		bltMod = NEO_MODE1_DEPTH16;
		pitch = var->xres_भव * 2;
		अवरोध;
	हाल 24:
		bltMod = NEO_MODE1_DEPTH24;
		pitch = var->xres_भव * 3;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR
		       "neofb: neo2200_accel_init: unexpected bits per pixel!\n");
		वापस;
	पूर्ण

	ग_लिखोl(bltMod << 16, &neo2200->bltStat);
	ग_लिखोl((pitch << 16) | pitch, &neo2200->pitch);
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक
neofb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा neofb_par *par = info->par;

	अगर (!par->ref_count) अणु
		स_रखो(&par->state, 0, माप(काष्ठा vgastate));
		par->state.flags = VGA_SAVE_MODE | VGA_SAVE_FONTS;
		save_vga(&par->state);
	पूर्ण
	par->ref_count++;

	वापस 0;
पूर्ण

अटल पूर्णांक
neofb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा neofb_par *par = info->par;

	अगर (!par->ref_count)
		वापस -EINVAL;

	अगर (par->ref_count == 1) अणु
		restore_vga(&par->state);
	पूर्ण
	par->ref_count--;

	वापस 0;
पूर्ण

अटल पूर्णांक
neofb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा neofb_par *par = info->par;
	पूर्णांक memlen, vramlen;
	पूर्णांक mode_ok = 0;

	DBG("neofb_check_var");

	अगर (PICOS2KHZ(var->pixघड़ी) > par->maxClock)
		वापस -EINVAL;

	/* Is the mode larger than the LCD panel? */
	अगर (par->पूर्णांकernal_display &&
            ((var->xres > par->NeoPanelWidth) ||
	     (var->yres > par->NeoPanelHeight))) अणु
		prपूर्णांकk(KERN_INFO
		       "Mode (%dx%d) larger than the LCD panel (%dx%d)\n",
		       var->xres, var->yres, par->NeoPanelWidth,
		       par->NeoPanelHeight);
		वापस -EINVAL;
	पूर्ण

	/* Is the mode one of the acceptable sizes? */
	अगर (!par->पूर्णांकernal_display)
		mode_ok = 1;
	अन्यथा अणु
		चयन (var->xres) अणु
		हाल 1280:
			अगर (var->yres == 1024)
				mode_ok = 1;
			अवरोध;
		हाल 1024:
			अगर (var->yres == 768)
				mode_ok = 1;
			अवरोध;
		हाल 800:
			अगर (var->yres == (par->libretto ? 480 : 600))
				mode_ok = 1;
			अवरोध;
		हाल 640:
			अगर (var->yres == 480)
				mode_ok = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!mode_ok) अणु
		prपूर्णांकk(KERN_INFO
		       "Mode (%dx%d) won't display properly on LCD\n",
		       var->xres, var->yres);
		वापस -EINVAL;
	पूर्ण

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	var->transp.offset = 0;
	var->transp.length = 0;
	चयन (var->bits_per_pixel) अणु
	हाल 8:		/* PSEUDOCOLOUR, 256 */
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		अवरोध;

	हाल 16:		/* सूचीECTCOLOUR, 64k */
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		अवरोध;

	हाल 24:		/* TRUECOLOUR, 16m */
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		अवरोध;

#अगर_घोषित NO_32BIT_SUPPORT_YET
	हाल 32:		/* TRUECOLOUR, 16m */
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		अवरोध;
#पूर्ण_अगर
	शेष:
		prपूर्णांकk(KERN_WARNING "neofb: no support for %dbpp\n",
		       var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	vramlen = info->fix.smem_len;
	अगर (vramlen > 4 * 1024 * 1024)
		vramlen = 4 * 1024 * 1024;

	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;

	memlen = var->xres_भव * var->bits_per_pixel * var->yres_भव >> 3;

	अगर (memlen > vramlen) अणु
		var->yres_भव =  vramlen * 8 / (var->xres_भव *
				   	var->bits_per_pixel);
		memlen = var->xres_भव * var->bits_per_pixel *
				var->yres_भव / 8;
	पूर्ण

	/* we must round yres/xres करोwn, we alपढ़ोy rounded y/xres_भव up
	   अगर it was possible. We should वापस -EINVAL, but I disagree */
	अगर (var->yres_भव < var->yres)
		var->yres = var->yres_भव;
	अगर (var->xoffset + var->xres > var->xres_भव)
		var->xoffset = var->xres_भव - var->xres;
	अगर (var->yoffset + var->yres > var->yres_भव)
		var->yoffset = var->yres_भव - var->yres;

	var->nonstd = 0;
	var->height = -1;
	var->width = -1;

	अगर (var->bits_per_pixel >= 24 || !par->neo2200)
		var->accel_flags &= ~FB_ACCELF_TEXT;
	वापस 0;
पूर्ण

अटल पूर्णांक neofb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा neofb_par *par = info->par;
	अचिन्हित अक्षर temp;
	पूर्णांक i, घड़ी_hi = 0;
	पूर्णांक lcd_stretch;
	पूर्णांक hoffset, voffset;
	पूर्णांक vsync_start, vtotal;

	DBG("neofb_set_par");

	neoUnlock();

	vgaHWProtect(1);	/* Blank the screen */

	vsync_start = info->var.yres + info->var.lower_margin;
	vtotal = vsync_start + info->var.vsync_len + info->var.upper_margin;

	/*
	 * This will allocate the dataकाष्ठाure and initialize all of the
	 * generic VGA रेजिस्टरs.
	 */

	अगर (vgaHWInit(&info->var, par))
		वापस -EINVAL;

	/*
	 * The शेष value asचिन्हित by vgaHW.c is 0x41, but this करोes
	 * not work क्रम NeoMagic.
	 */
	par->Attribute[16] = 0x01;

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		par->CRTC[0x13] = info->var.xres_भव >> 3;
		par->ExtCRTOffset = info->var.xres_भव >> 11;
		par->ExtColorModeSelect = 0x11;
		अवरोध;
	हाल 16:
		par->CRTC[0x13] = info->var.xres_भव >> 2;
		par->ExtCRTOffset = info->var.xres_भव >> 10;
		par->ExtColorModeSelect = 0x13;
		अवरोध;
	हाल 24:
		par->CRTC[0x13] = (info->var.xres_भव * 3) >> 3;
		par->ExtCRTOffset = (info->var.xres_भव * 3) >> 11;
		par->ExtColorModeSelect = 0x14;
		अवरोध;
#अगर_घोषित NO_32BIT_SUPPORT_YET
	हाल 32:		/* FIXME: guessed values */
		par->CRTC[0x13] = info->var.xres_भव >> 1;
		par->ExtCRTOffset = info->var.xres_भव >> 9;
		par->ExtColorModeSelect = 0x15;
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

	par->ExtCRTDispAddr = 0x10;

	/* Vertical Extension */
	par->VerticalExt = (((vtotal - 2) & 0x400) >> 10)
	    | (((info->var.yres - 1) & 0x400) >> 9)
	    | (((vsync_start) & 0x400) >> 8)
	    | (((vsync_start) & 0x400) >> 7);

	/* Fast ग_लिखो bursts on unless disabled. */
	अगर (par->pci_burst)
		par->SysIfaceCntl1 = 0x30;
	अन्यथा
		par->SysIfaceCntl1 = 0x00;

	par->SysIfaceCntl2 = 0xc0;	/* VESA Bios sets this to 0x80! */

	/* Initialize: by शेष, we want display config रेजिस्टर to be पढ़ो */
	par->PanelDispCntlRegRead = 1;

	/* Enable any user specअगरied display devices. */
	par->PanelDispCntlReg1 = 0x00;
	अगर (par->पूर्णांकernal_display)
		par->PanelDispCntlReg1 |= 0x02;
	अगर (par->बाह्यal_display)
		par->PanelDispCntlReg1 |= 0x01;

	/* If the user did not specअगरy any display devices, then... */
	अगर (par->PanelDispCntlReg1 == 0x00) अणु
		/* Default to पूर्णांकernal (i.e., LCD) only. */
		par->PanelDispCntlReg1 = vga_rgfx(शून्य, 0x20) & 0x03;
	पूर्ण

	/* If we are using a fixed mode, then tell the chip we are. */
	चयन (info->var.xres) अणु
	हाल 1280:
		par->PanelDispCntlReg1 |= 0x60;
		अवरोध;
	हाल 1024:
		par->PanelDispCntlReg1 |= 0x40;
		अवरोध;
	हाल 800:
		par->PanelDispCntlReg1 |= 0x20;
		अवरोध;
	हाल 640:
	शेष:
		अवरोध;
	पूर्ण

	/* Setup shaकरोw रेजिस्टर locking. */
	चयन (par->PanelDispCntlReg1 & 0x03) अणु
	हाल 0x01:		/* External CRT only mode: */
		par->GeneralLockReg = 0x00;
		/* We need to program the VCLK क्रम बाह्यal display only mode. */
		par->ProgramVCLK = 1;
		अवरोध;
	हाल 0x02:		/* Internal LCD only mode: */
	हाल 0x03:		/* Simultaneous पूर्णांकernal/बाह्यal (LCD/CRT) mode: */
		par->GeneralLockReg = 0x01;
		/* Don't program the VCLK when using the LCD. */
		par->ProgramVCLK = 0;
		अवरोध;
	पूर्ण

	/*
	 * If the screen is to be stretched, turn on stretching क्रम the
	 * various modes.
	 *
	 * OPTION_LCD_STRETCH means stretching should be turned off!
	 */
	par->PanelDispCntlReg2 = 0x00;
	par->PanelDispCntlReg3 = 0x00;

	अगर (par->lcd_stretch && (par->PanelDispCntlReg1 == 0x02) &&	/* LCD only */
	    (info->var.xres != par->NeoPanelWidth)) अणु
		चयन (info->var.xres) अणु
		हाल 320:	/* Needs testing.  KEM -- 24 May 98 */
		हाल 400:	/* Needs testing.  KEM -- 24 May 98 */
		हाल 640:
		हाल 800:
		हाल 1024:
			lcd_stretch = 1;
			par->PanelDispCntlReg2 |= 0xC6;
			अवरोध;
		शेष:
			lcd_stretch = 0;
			/* No stretching in these modes. */
		पूर्ण
	पूर्ण अन्यथा
		lcd_stretch = 0;

	/*
	 * If the screen is to be centerd, turn on the centering क्रम the
	 * various modes.
	 */
	par->PanelVertCenterReg1 = 0x00;
	par->PanelVertCenterReg2 = 0x00;
	par->PanelVertCenterReg3 = 0x00;
	par->PanelVertCenterReg4 = 0x00;
	par->PanelVertCenterReg5 = 0x00;
	par->PanelHorizCenterReg1 = 0x00;
	par->PanelHorizCenterReg2 = 0x00;
	par->PanelHorizCenterReg3 = 0x00;
	par->PanelHorizCenterReg4 = 0x00;
	par->PanelHorizCenterReg5 = 0x00;


	अगर (par->PanelDispCntlReg1 & 0x02) अणु
		अगर (info->var.xres == par->NeoPanelWidth) अणु
			/*
			 * No centering required when the requested display width
			 * equals the panel width.
			 */
		पूर्ण अन्यथा अणु
			par->PanelDispCntlReg2 |= 0x01;
			par->PanelDispCntlReg3 |= 0x10;

			/* Calculate the horizontal and vertical offsets. */
			अगर (!lcd_stretch) अणु
				hoffset =
				    ((par->NeoPanelWidth -
				      info->var.xres) >> 4) - 1;
				voffset =
				    ((par->NeoPanelHeight -
				      info->var.yres) >> 1) - 2;
			पूर्ण अन्यथा अणु
				/* Stretched modes cannot be centered. */
				hoffset = 0;
				voffset = 0;
			पूर्ण

			चयन (info->var.xres) अणु
			हाल 320:	/* Needs testing.  KEM -- 24 May 98 */
				par->PanelHorizCenterReg3 = hoffset;
				par->PanelVertCenterReg2 = voffset;
				अवरोध;
			हाल 400:	/* Needs testing.  KEM -- 24 May 98 */
				par->PanelHorizCenterReg4 = hoffset;
				par->PanelVertCenterReg1 = voffset;
				अवरोध;
			हाल 640:
				par->PanelHorizCenterReg1 = hoffset;
				par->PanelVertCenterReg3 = voffset;
				अवरोध;
			हाल 800:
				par->PanelHorizCenterReg2 = hoffset;
				par->PanelVertCenterReg4 = voffset;
				अवरोध;
			हाल 1024:
				par->PanelHorizCenterReg5 = hoffset;
				par->PanelVertCenterReg5 = voffset;
				अवरोध;
			हाल 1280:
			शेष:
				/* No centering in these modes. */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	par->biosMode =
	    neoFindMode(info->var.xres, info->var.yres,
			info->var.bits_per_pixel);

	/*
	 * Calculate the VCLK that most बंदly matches the requested करोt
	 * घड़ी.
	 */
	neoCalcVCLK(info, par, PICOS2KHZ(info->var.pixघड़ी));

	/* Since we program the घड़ीs ourselves, always use VCLK3. */
	par->MiscOutReg |= 0x0C;

	/* alपढ़ो unlocked above */
	/* BOGUS  vga_wgfx(शून्य, 0x09, 0x26); */

	/* करोn't know what this is, but it's 0 from bootup anyway */
	vga_wgfx(शून्य, 0x15, 0x00);

	/* was set to 0x01 by my bios in text and vesa modes */
	vga_wgfx(शून्य, 0x0A, par->GeneralLockReg);

	/*
	 * The color mode needs to be set beक्रमe calling vgaHWRestore
	 * to ensure the DAC is initialized properly.
	 *
	 * NOTE: Make sure we करोn't change bits make sure we don't change
	 * any reserved bits.
	 */
	temp = vga_rgfx(शून्य, 0x90);
	चयन (info->fix.accel) अणु
	हाल FB_ACCEL_NEOMAGIC_NM2070:
		temp &= 0xF0;	/* Save bits 7:4 */
		temp |= (par->ExtColorModeSelect & ~0xF0);
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2090:
	हाल FB_ACCEL_NEOMAGIC_NM2093:
	हाल FB_ACCEL_NEOMAGIC_NM2097:
	हाल FB_ACCEL_NEOMAGIC_NM2160:
	हाल FB_ACCEL_NEOMAGIC_NM2200:
	हाल FB_ACCEL_NEOMAGIC_NM2230:
	हाल FB_ACCEL_NEOMAGIC_NM2360:
	हाल FB_ACCEL_NEOMAGIC_NM2380:
		temp &= 0x70;	/* Save bits 6:4 */
		temp |= (par->ExtColorModeSelect & ~0x70);
		अवरोध;
	पूर्ण

	vga_wgfx(शून्य, 0x90, temp);

	/*
	 * In some rare हालs a lockup might occur अगर we करोn't delay
	 * here. (Reported by Miles Lane)
	 */
	//mdelay(200);

	/*
	 * Disable horizontal and vertical graphics and text expansions so
	 * that vgaHWRestore works properly.
	 */
	temp = vga_rgfx(शून्य, 0x25);
	temp &= 0x39;
	vga_wgfx(शून्य, 0x25, temp);

	/*
	 * Sleep क्रम 200ms to make sure that the two operations above have
	 * had समय to take effect.
	 */
	mdelay(200);

	/*
	 * This function handles restoring the generic VGA रेजिस्टरs.  */
	vgaHWRestore(info, par);

	/* linear colormap क्रम non palettized modes */
	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		/* PseuकरोColor, 256 */
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	हाल 16:
		/* TrueColor, 64k */
		info->fix.visual = FB_VISUAL_TRUECOLOR;

		क्रम (i = 0; i < 64; i++) अणु
			outb(i, 0x3c8);

			outb(i << 1, 0x3c9);
			outb(i, 0x3c9);
			outb(i << 1, 0x3c9);
		पूर्ण
		अवरोध;
	हाल 24:
#अगर_घोषित NO_32BIT_SUPPORT_YET
	हाल 32:
#पूर्ण_अगर
		/* TrueColor, 16m */
		info->fix.visual = FB_VISUAL_TRUECOLOR;

		क्रम (i = 0; i < 256; i++) अणु
			outb(i, 0x3c8);

			outb(i, 0x3c9);
			outb(i, 0x3c9);
			outb(i, 0x3c9);
		पूर्ण
		अवरोध;
	पूर्ण

	vga_wgfx(शून्य, 0x0E, par->ExtCRTDispAddr);
	vga_wgfx(शून्य, 0x0F, par->ExtCRTOffset);
	temp = vga_rgfx(शून्य, 0x10);
	temp &= 0x0F;		/* Save bits 3:0 */
	temp |= (par->SysIfaceCntl1 & ~0x0F);	/* VESA Bios sets bit 1! */
	vga_wgfx(शून्य, 0x10, temp);

	vga_wgfx(शून्य, 0x11, par->SysIfaceCntl2);
	vga_wgfx(शून्य, 0x15, 0 /*par->SingleAddrPage */ );
	vga_wgfx(शून्य, 0x16, 0 /*par->DualAddrPage */ );

	temp = vga_rgfx(शून्य, 0x20);
	चयन (info->fix.accel) अणु
	हाल FB_ACCEL_NEOMAGIC_NM2070:
		temp &= 0xFC;	/* Save bits 7:2 */
		temp |= (par->PanelDispCntlReg1 & ~0xFC);
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2090:
	हाल FB_ACCEL_NEOMAGIC_NM2093:
	हाल FB_ACCEL_NEOMAGIC_NM2097:
	हाल FB_ACCEL_NEOMAGIC_NM2160:
		temp &= 0xDC;	/* Save bits 7:6,4:2 */
		temp |= (par->PanelDispCntlReg1 & ~0xDC);
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2200:
	हाल FB_ACCEL_NEOMAGIC_NM2230:
	हाल FB_ACCEL_NEOMAGIC_NM2360:
	हाल FB_ACCEL_NEOMAGIC_NM2380:
		temp &= 0x98;	/* Save bits 7,4:3 */
		temp |= (par->PanelDispCntlReg1 & ~0x98);
		अवरोध;
	पूर्ण
	vga_wgfx(शून्य, 0x20, temp);

	temp = vga_rgfx(शून्य, 0x25);
	temp &= 0x38;		/* Save bits 5:3 */
	temp |= (par->PanelDispCntlReg2 & ~0x38);
	vga_wgfx(शून्य, 0x25, temp);

	अगर (info->fix.accel != FB_ACCEL_NEOMAGIC_NM2070) अणु
		temp = vga_rgfx(शून्य, 0x30);
		temp &= 0xEF;	/* Save bits 7:5 and bits 3:0 */
		temp |= (par->PanelDispCntlReg3 & ~0xEF);
		vga_wgfx(शून्य, 0x30, temp);
	पूर्ण

	vga_wgfx(शून्य, 0x28, par->PanelVertCenterReg1);
	vga_wgfx(शून्य, 0x29, par->PanelVertCenterReg2);
	vga_wgfx(शून्य, 0x2a, par->PanelVertCenterReg3);

	अगर (info->fix.accel != FB_ACCEL_NEOMAGIC_NM2070) अणु
		vga_wgfx(शून्य, 0x32, par->PanelVertCenterReg4);
		vga_wgfx(शून्य, 0x33, par->PanelHorizCenterReg1);
		vga_wgfx(शून्य, 0x34, par->PanelHorizCenterReg2);
		vga_wgfx(शून्य, 0x35, par->PanelHorizCenterReg3);
	पूर्ण

	अगर (info->fix.accel == FB_ACCEL_NEOMAGIC_NM2160)
		vga_wgfx(शून्य, 0x36, par->PanelHorizCenterReg4);

	अगर (info->fix.accel == FB_ACCEL_NEOMAGIC_NM2200 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2230 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2360 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2380) अणु
		vga_wgfx(शून्य, 0x36, par->PanelHorizCenterReg4);
		vga_wgfx(शून्य, 0x37, par->PanelVertCenterReg5);
		vga_wgfx(शून्य, 0x38, par->PanelHorizCenterReg5);

		घड़ी_hi = 1;
	पूर्ण

	/* Program VCLK3 अगर needed. */
	अगर (par->ProgramVCLK && ((vga_rgfx(शून्य, 0x9B) != par->VCLK3NumeratorLow)
				 || (vga_rgfx(शून्य, 0x9F) != par->VCLK3Denominator)
				 || (घड़ी_hi && ((vga_rgfx(शून्य, 0x8F) & ~0x0f)
						  != (par->VCLK3NumeratorHigh &
						      ~0x0F))))) अणु
		vga_wgfx(शून्य, 0x9B, par->VCLK3NumeratorLow);
		अगर (घड़ी_hi) अणु
			temp = vga_rgfx(शून्य, 0x8F);
			temp &= 0x0F;	/* Save bits 3:0 */
			temp |= (par->VCLK3NumeratorHigh & ~0x0F);
			vga_wgfx(शून्य, 0x8F, temp);
		पूर्ण
		vga_wgfx(शून्य, 0x9F, par->VCLK3Denominator);
	पूर्ण

	अगर (par->biosMode)
		vga_wcrt(शून्य, 0x23, par->biosMode);

	vga_wgfx(शून्य, 0x93, 0xc0);	/* Gives 5x faster framebuffer ग_लिखोs !!! */

	/* Program vertical extension रेजिस्टर */
	अगर (info->fix.accel == FB_ACCEL_NEOMAGIC_NM2200 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2230 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2360 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2380) अणु
		vga_wcrt(शून्य, 0x70, par->VerticalExt);
	पूर्ण

	vgaHWProtect(0);	/* Turn on screen */

	/* Calling this also locks offset रेजिस्टरs required in update_start */
	neoLock(&par->state);

	info->fix.line_length =
	    info->var.xres_भव * (info->var.bits_per_pixel >> 3);

	चयन (info->fix.accel) अणु
		हाल FB_ACCEL_NEOMAGIC_NM2200:
		हाल FB_ACCEL_NEOMAGIC_NM2230: 
		हाल FB_ACCEL_NEOMAGIC_NM2360: 
		हाल FB_ACCEL_NEOMAGIC_NM2380: 
			neo2200_accel_init(info, &info->var);
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण	
	वापस 0;
पूर्ण

/*
 *    Pan or Wrap the Display
 */
अटल पूर्णांक neofb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा neofb_par *par = info->par;
	काष्ठा vgastate *state = &par->state;
	पूर्णांक oldExtCRTDispAddr;
	पूर्णांक Base;

	DBG("neofb_update_start");

	Base = (var->yoffset * info->var.xres_भव + var->xoffset) >> 2;
	Base *= (info->var.bits_per_pixel + 7) / 8;

	neoUnlock();

	/*
	 * These are the generic starting address रेजिस्टरs.
	 */
	vga_wcrt(state->vgabase, 0x0C, (Base & 0x00FF00) >> 8);
	vga_wcrt(state->vgabase, 0x0D, (Base & 0x00FF));

	/*
	 * Make sure we करोn't clobber some other bits that might alपढ़ोy
	 * have been set. NOTE: NM2200 has a writable bit 3, but it shouldn't
	 * be needed.
	 */
	oldExtCRTDispAddr = vga_rgfx(शून्य, 0x0E);
	vga_wgfx(state->vgabase, 0x0E, (((Base >> 16) & 0x0f) | (oldExtCRTDispAddr & 0xf0)));

	neoLock(state);

	वापस 0;
पूर्ण

अटल पूर्णांक neofb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			   u_पूर्णांक transp, काष्ठा fb_info *fb)
अणु
	अगर (regno >= fb->cmap.len || regno > 255)
		वापस -EINVAL;

	अगर (fb->var.bits_per_pixel <= 8) अणु
		outb(regno, 0x3c8);

		outb(red >> 10, 0x3c9);
		outb(green >> 10, 0x3c9);
		outb(blue >> 10, 0x3c9);
	पूर्ण अन्यथा अगर (regno < 16) अणु
		चयन (fb->var.bits_per_pixel) अणु
		हाल 16:
			((u32 *) fb->pseuकरो_palette)[regno] =
				((red & 0xf800)) | ((green & 0xfc00) >> 5) |
				((blue & 0xf800) >> 11);
			अवरोध;
		हाल 24:
			((u32 *) fb->pseuकरो_palette)[regno] =
				((red & 0xff00) << 8) | ((green & 0xff00)) |
				((blue & 0xff00) >> 8);
			अवरोध;
#अगर_घोषित NO_32BIT_SUPPORT_YET
		हाल 32:
			((u32 *) fb->pseuकरो_palette)[regno] =
				((transp & 0xff00) << 16) | ((red & 0xff00) << 8) |
				((green & 0xff00)) | ((blue & 0xff00) >> 8);
			अवरोध;
#पूर्ण_अगर
		शेष:
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *    (Un)Blank the display.
 */
अटल पूर्णांक neofb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	/*
	 *  Blank the screen अगर blank_mode != 0, अन्यथा unblank.
	 *  Return 0 अगर blanking succeeded, != 0 अगर un-/blanking failed due to
	 *  e.g. a video mode which करोesn't support it. Implements VESA suspend
	 *  and घातerकरोwn modes क्रम monitors, and backlight control on LCDs.
	 *    blank_mode == 0: unblanked (backlight on)
	 *    blank_mode == 1: blank (backlight on)
	 *    blank_mode == 2: suspend vsync (backlight off)
	 *    blank_mode == 3: suspend hsync (backlight off)
	 *    blank_mode == 4: घातerकरोwn (backlight off)
	 *
	 *  wms...Enable VESA DPMS compatible घातerकरोwn mode
	 *  run "setterm -powersave powerdown" to take advantage
	 */
	काष्ठा neofb_par *par = info->par;
	पूर्णांक seqflags, lcdflags, dpmsflags, reg, पंचांगpdisp;

	/*
	 * Read back the रेजिस्टर bits related to display configuration. They might
	 * have been changed underneath the driver via Fn key stroke.
	 */
	neoUnlock();
	पंचांगpdisp = vga_rgfx(शून्य, 0x20) & 0x03;
	neoLock(&par->state);

	/* In हाल we blank the screen, we want to store the possibly new
	 * configuration in the driver. During un-blank, we re-apply this setting,
	 * since the LCD bit will be cleared in order to चयन off the backlight.
	 */
	अगर (par->PanelDispCntlRegRead) अणु
		par->PanelDispCntlReg1 = पंचांगpdisp;
	पूर्ण
	par->PanelDispCntlRegRead = !blank_mode;

	चयन (blank_mode) अणु
	हाल FB_BLANK_POWERDOWN:	/* घातerकरोwn - both sync lines करोwn */
		seqflags = VGA_SR01_SCREEN_OFF; /* Disable sequencer */
		lcdflags = 0;			/* LCD off */
		dpmsflags = NEO_GR01_SUPPRESS_HSYNC |
			    NEO_GR01_SUPPRESS_VSYNC;
#अगर_घोषित CONFIG_TOSHIBA
		/* Do we still need this ? */
		/* attempt to turn off backlight on toshiba; also turns off बाह्यal */
		अणु
			SMMRegisters regs;

			regs.eax = 0xff00; /* HCI_SET */
			regs.ebx = 0x0002; /* HCI_BACKLIGHT */
			regs.ecx = 0x0000; /* HCI_DISABLE */
			tosh_smm(&regs);
		पूर्ण
#पूर्ण_अगर
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:		/* hsync off */
		seqflags = VGA_SR01_SCREEN_OFF;	/* Disable sequencer */
		lcdflags = 0;			/* LCD off */
		dpmsflags = NEO_GR01_SUPPRESS_HSYNC;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:		/* vsync off */
		seqflags = VGA_SR01_SCREEN_OFF;	/* Disable sequencer */
		lcdflags = 0;			/* LCD off */
		dpmsflags = NEO_GR01_SUPPRESS_VSYNC;
		अवरोध;
	हाल FB_BLANK_NORMAL:		/* just blank screen (backlight stays on) */
		seqflags = VGA_SR01_SCREEN_OFF;	/* Disable sequencer */
		/*
		 * During a blank operation with the LID shut, we might store "LCD off"
		 * by mistake. Due to timing issues, the BIOS may चयन the lights
		 * back on, and we turn it back off once we "unblank".
		 *
		 * So here is an attempt to implement ">=" - अगर we are in the process
		 * of unblanking, and the LCD bit is unset in the driver but set in the
		 * रेजिस्टर, we must keep it.
		 */
		lcdflags = ((par->PanelDispCntlReg1 | पंचांगpdisp) & 0x02); /* LCD normal */
		dpmsflags = 0x00;	/* no hsync/vsync suppression */
		अवरोध;
	हाल FB_BLANK_UNBLANK:		/* unblank */
		seqflags = 0;			/* Enable sequencer */
		lcdflags = ((par->PanelDispCntlReg1 | पंचांगpdisp) & 0x02); /* LCD normal */
		dpmsflags = 0x00;	/* no hsync/vsync suppression */
#अगर_घोषित CONFIG_TOSHIBA
		/* Do we still need this ? */
		/* attempt to re-enable backlight/बाह्यal on toshiba */
		अणु
			SMMRegisters regs;

			regs.eax = 0xff00; /* HCI_SET */
			regs.ebx = 0x0002; /* HCI_BACKLIGHT */
			regs.ecx = 0x0001; /* HCI_ENABLE */
			tosh_smm(&regs);
		पूर्ण
#पूर्ण_अगर
		अवरोध;
	शेष:	/* Anything अन्यथा we करोn't understand; वापस 1 to tell
			 * fb_blank we didn't aactually करो anything */
		वापस 1;
	पूर्ण

	neoUnlock();
	reg = (vga_rseq(शून्य, 0x01) & ~0x20) | seqflags;
	vga_wseq(शून्य, 0x01, reg);
	reg = (vga_rgfx(शून्य, 0x20) & ~0x02) | lcdflags;
	vga_wgfx(शून्य, 0x20, reg);
	reg = (vga_rgfx(शून्य, 0x01) & ~0xF0) | 0x80 | dpmsflags;
	vga_wgfx(शून्य, 0x01, reg);
	neoLock(&par->state);
	वापस 0;
पूर्ण

अटल व्योम
neo2200_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा neofb_par *par = info->par;
	u_दीर्घ dst, rop;

	dst = rect->dx + rect->dy * info->var.xres_भव;
	rop = rect->rop ? 0x060000 : 0x0c0000;

	neo2200_रुको_fअगरo(info, 4);

	/* set blt control */
	ग_लिखोl(NEO_BC3_FIFO_EN |
	       NEO_BC0_SRC_IS_FG | NEO_BC3_SKIP_MAPPING |
	       //               NEO_BC3_DST_XY_ADDR  |
	       //               NEO_BC3_SRC_XY_ADDR  |
	       rop, &par->neo2200->bltCntl);

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		ग_लिखोl(rect->color, &par->neo2200->fgColor);
		अवरोध;
	हाल 16:
	हाल 24:
		ग_लिखोl(((u32 *) (info->pseuकरो_palette))[rect->color],
		       &par->neo2200->fgColor);
		अवरोध;
	पूर्ण

	ग_लिखोl(dst * ((info->var.bits_per_pixel + 7) >> 3),
	       &par->neo2200->dstStart);
	ग_लिखोl((rect->height << 16) | (rect->width & 0xffff),
	       &par->neo2200->xyExt);
पूर्ण

अटल व्योम
neo2200_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	u32 sx = area->sx, sy = area->sy, dx = area->dx, dy = area->dy;
	काष्ठा neofb_par *par = info->par;
	u_दीर्घ src, dst, bltCntl;

	bltCntl = NEO_BC3_FIFO_EN | NEO_BC3_SKIP_MAPPING | 0x0C0000;

	अगर ((dy > sy) || ((dy == sy) && (dx > sx))) अणु
		/* Start with the lower right corner */
		sy += (area->height - 1);
		dy += (area->height - 1);
		sx += (area->width - 1);
		dx += (area->width - 1);

		bltCntl |= NEO_BC0_X_DEC | NEO_BC0_DST_Y_DEC | NEO_BC0_SRC_Y_DEC;
	पूर्ण

	src = sx * (info->var.bits_per_pixel >> 3) + sy*info->fix.line_length;
	dst = dx * (info->var.bits_per_pixel >> 3) + dy*info->fix.line_length;

	neo2200_रुको_fअगरo(info, 4);

	/* set blt control */
	ग_लिखोl(bltCntl, &par->neo2200->bltCntl);

	ग_लिखोl(src, &par->neo2200->srcStart);
	ग_लिखोl(dst, &par->neo2200->dstStart);
	ग_लिखोl((area->height << 16) | (area->width & 0xffff),
	       &par->neo2200->xyExt);
पूर्ण

अटल व्योम
neo2200_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा neofb_par *par = info->par;
	पूर्णांक s_pitch = (image->width * image->depth + 7) >> 3;
	पूर्णांक scan_align = info->pixmap.scan_align - 1;
	पूर्णांक buf_align = info->pixmap.buf_align - 1;
	पूर्णांक bltCntl_flags, d_pitch, data_len;

	// The data is padded क्रम the hardware
	d_pitch = (s_pitch + scan_align) & ~scan_align;
	data_len = ((d_pitch * image->height) + buf_align) & ~buf_align;

	neo2200_sync(info);

	अगर (image->depth == 1) अणु
		अगर (info->var.bits_per_pixel == 24 && image->width < 16) अणु
			/* FIXME. There is a bug with accelerated color-expanded
			 * transfers in 24 bit mode अगर the image being transferred
			 * is less than 16 bits wide. This is due to insufficient
			 * padding when writing the image. We need to adjust
			 * काष्ठा fb_pixmap. Not yet करोne. */
			cfb_imageblit(info, image);
			वापस;
		पूर्ण
		bltCntl_flags = NEO_BC0_SRC_MONO;
	पूर्ण अन्यथा अगर (image->depth == info->var.bits_per_pixel) अणु
		bltCntl_flags = 0;
	पूर्ण अन्यथा अणु
		/* We करोn't currently support hardware acceleration अगर image
		 * depth is dअगरferent from display */
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		ग_लिखोl(image->fg_color, &par->neo2200->fgColor);
		ग_लिखोl(image->bg_color, &par->neo2200->bgColor);
		अवरोध;
	हाल 16:
	हाल 24:
		ग_लिखोl(((u32 *) (info->pseuकरो_palette))[image->fg_color],
		       &par->neo2200->fgColor);
		ग_लिखोl(((u32 *) (info->pseuकरो_palette))[image->bg_color],
		       &par->neo2200->bgColor);
		अवरोध;
	पूर्ण

	ग_लिखोl(NEO_BC0_SYS_TO_VID |
		NEO_BC3_SKIP_MAPPING | bltCntl_flags |
		// NEO_BC3_DST_XY_ADDR |
		0x0c0000, &par->neo2200->bltCntl);

	ग_लिखोl(0, &par->neo2200->srcStart);
//      par->neo2200->dstStart = (image->dy << 16) | (image->dx & 0xffff);
	ग_लिखोl(((image->dx & 0xffff) * (info->var.bits_per_pixel >> 3) +
		image->dy * info->fix.line_length), &par->neo2200->dstStart);
	ग_लिखोl((image->height << 16) | (image->width & 0xffff),
	       &par->neo2200->xyExt);

	स_नकल_toio(par->mmio_vbase + 0x100000, image->data, data_len);
पूर्ण

अटल व्योम
neofb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	चयन (info->fix.accel) अणु
		हाल FB_ACCEL_NEOMAGIC_NM2200:
		हाल FB_ACCEL_NEOMAGIC_NM2230: 
		हाल FB_ACCEL_NEOMAGIC_NM2360: 
		हाल FB_ACCEL_NEOMAGIC_NM2380:
			neo2200_fillrect(info, rect);
			अवरोध;
		शेष:
			cfb_fillrect(info, rect);
			अवरोध;
	पूर्ण	
पूर्ण

अटल व्योम
neofb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	चयन (info->fix.accel) अणु
		हाल FB_ACCEL_NEOMAGIC_NM2200:
		हाल FB_ACCEL_NEOMAGIC_NM2230: 
		हाल FB_ACCEL_NEOMAGIC_NM2360: 
		हाल FB_ACCEL_NEOMAGIC_NM2380: 
			neo2200_copyarea(info, area);
			अवरोध;
		शेष:
			cfb_copyarea(info, area);
			अवरोध;
	पूर्ण	
पूर्ण

अटल व्योम
neofb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	चयन (info->fix.accel) अणु
		हाल FB_ACCEL_NEOMAGIC_NM2200:
		हाल FB_ACCEL_NEOMAGIC_NM2230:
		हाल FB_ACCEL_NEOMAGIC_NM2360:
		हाल FB_ACCEL_NEOMAGIC_NM2380:
			neo2200_imageblit(info, image);
			अवरोध;
		शेष:
			cfb_imageblit(info, image);
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक 
neofb_sync(काष्ठा fb_info *info)
अणु
	चयन (info->fix.accel) अणु
		हाल FB_ACCEL_NEOMAGIC_NM2200:
		हाल FB_ACCEL_NEOMAGIC_NM2230: 
		हाल FB_ACCEL_NEOMAGIC_NM2360: 
		हाल FB_ACCEL_NEOMAGIC_NM2380: 
			neo2200_sync(info);
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण
	वापस 0;		
पूर्ण

/*
अटल व्योम
neofb_draw_cursor(काष्ठा fb_info *info, u8 *dst, u8 *src, अचिन्हित पूर्णांक width)
अणु
	//स_रखो_io(info->sprite.addr, 0xff, 1);
पूर्ण

अटल पूर्णांक
neofb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा neofb_par *par = (काष्ठा neofb_par *) info->par;

	* Disable cursor *
	ग_लिखो_le32(NEOREG_CURSCNTL, ~NEO_CURS_ENABLE, par);

	अगर (cursor->set & FB_CUR_SETPOS) अणु
		u32 x = cursor->image.dx;
		u32 y = cursor->image.dy;

		info->cursor.image.dx = x;
		info->cursor.image.dy = y;
		ग_लिखो_le32(NEOREG_CURSX, x, par);
		ग_लिखो_le32(NEOREG_CURSY, y, par);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETSIZE) अणु
		info->cursor.image.height = cursor->image.height;
		info->cursor.image.width = cursor->image.width;
	पूर्ण

	अगर (cursor->set & FB_CUR_SETHOT)
		info->cursor.hot = cursor->hot;

	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		अगर (cursor->image.depth == 1) अणु
			u32 fg = cursor->image.fg_color;
			u32 bg = cursor->image.bg_color;

			info->cursor.image.fg_color = fg;
			info->cursor.image.bg_color = bg;

			fg = ((fg & 0xff0000) >> 16) | ((fg & 0xff) << 16) | (fg & 0xff00);
			bg = ((bg & 0xff0000) >> 16) | ((bg & 0xff) << 16) | (bg & 0xff00);
			ग_लिखो_le32(NEOREG_CURSFGCOLOR, fg, par);
			ग_लिखो_le32(NEOREG_CURSBGCOLOR, bg, par);
		पूर्ण
	पूर्ण

	अगर (cursor->set & FB_CUR_SETSHAPE)
		fb_load_cursor_image(info);

	अगर (info->cursor.enable)
		ग_लिखो_le32(NEOREG_CURSCNTL, NEO_CURS_ENABLE, par);
	वापस 0;
पूर्ण
*/

अटल स्थिर काष्ठा fb_ops neofb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= neofb_खोलो,
	.fb_release	= neofb_release,
	.fb_check_var	= neofb_check_var,
	.fb_set_par	= neofb_set_par,
	.fb_setcolreg	= neofb_setcolreg,
	.fb_pan_display	= neofb_pan_display,
	.fb_blank	= neofb_blank,
	.fb_sync	= neofb_sync,
	.fb_fillrect	= neofb_fillrect,
	.fb_copyarea	= neofb_copyarea,
	.fb_imageblit	= neofb_imageblit,
पूर्ण;

/* --------------------------------------------------------------------- */

अटल काष्ठा fb_videomode mode800x480 = अणु
	.xres           = 800,
	.yres           = 480,
	.pixघड़ी       = 25000,
	.left_margin    = 88,
	.right_margin   = 40,
	.upper_margin   = 23,
	.lower_margin   = 1,
	.hsync_len      = 128,
	.vsync_len      = 4,
	.sync           = FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.vmode          = FB_VMODE_NONINTERLACED
पूर्ण;

अटल पूर्णांक neo_map_mmio(काष्ठा fb_info *info, काष्ठा pci_dev *dev)
अणु
	काष्ठा neofb_par *par = info->par;

	DBG("neo_map_mmio");

	चयन (info->fix.accel) अणु
		हाल FB_ACCEL_NEOMAGIC_NM2070:
			info->fix.mmio_start = pci_resource_start(dev, 0)+
				0x100000;
			अवरोध;
		हाल FB_ACCEL_NEOMAGIC_NM2090:
		हाल FB_ACCEL_NEOMAGIC_NM2093:
			info->fix.mmio_start = pci_resource_start(dev, 0)+
				0x200000;
			अवरोध;
		हाल FB_ACCEL_NEOMAGIC_NM2160:
		हाल FB_ACCEL_NEOMAGIC_NM2097:
		हाल FB_ACCEL_NEOMAGIC_NM2200:
		हाल FB_ACCEL_NEOMAGIC_NM2230:
		हाल FB_ACCEL_NEOMAGIC_NM2360:
		हाल FB_ACCEL_NEOMAGIC_NM2380:
			info->fix.mmio_start = pci_resource_start(dev, 1);
			अवरोध;
		शेष:
			info->fix.mmio_start = pci_resource_start(dev, 0);
	पूर्ण
	info->fix.mmio_len = MMIO_SIZE;

	अगर (!request_mem_region
	    (info->fix.mmio_start, MMIO_SIZE, "memory mapped I/O")) अणु
		prपूर्णांकk("neofb: memory mapped IO in use\n");
		वापस -EBUSY;
	पूर्ण

	par->mmio_vbase = ioremap(info->fix.mmio_start, MMIO_SIZE);
	अगर (!par->mmio_vbase) अणु
		prपूर्णांकk("neofb: unable to map memory mapped IO\n");
		release_mem_region(info->fix.mmio_start,
				   info->fix.mmio_len);
		वापस -ENOMEM;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO "neofb: mapped io at %p\n",
		       par->mmio_vbase);
	वापस 0;
पूर्ण

अटल व्योम neo_unmap_mmio(काष्ठा fb_info *info)
अणु
	काष्ठा neofb_par *par = info->par;

	DBG("neo_unmap_mmio");

	iounmap(par->mmio_vbase);
	par->mmio_vbase = शून्य;

	release_mem_region(info->fix.mmio_start,
			   info->fix.mmio_len);
पूर्ण

अटल पूर्णांक neo_map_video(काष्ठा fb_info *info, काष्ठा pci_dev *dev,
			 पूर्णांक video_len)
अणु
	//अचिन्हित दीर्घ addr;
	काष्ठा neofb_par *par = info->par;

	DBG("neo_map_video");

	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = video_len;

	अगर (!request_mem_region(info->fix.smem_start, info->fix.smem_len,
				"frame buffer")) अणु
		prपूर्णांकk("neofb: frame buffer in use\n");
		वापस -EBUSY;
	पूर्ण

	info->screen_base =
	    ioremap_wc(info->fix.smem_start, info->fix.smem_len);
	अगर (!info->screen_base) अणु
		prपूर्णांकk("neofb: unable to map screen memory\n");
		release_mem_region(info->fix.smem_start,
				   info->fix.smem_len);
		वापस -ENOMEM;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO "neofb: mapped framebuffer at %p\n",
		       info->screen_base);

	par->wc_cookie = arch_phys_wc_add(info->fix.smem_start,
					  pci_resource_len(dev, 0));

	/* Clear framebuffer, it's all white in memory after boot */
	स_रखो_io(info->screen_base, 0, info->fix.smem_len);

	/* Allocate Cursor drawing pad.
	info->fix.smem_len -= PAGE_SIZE;
	addr = info->fix.smem_start + info->fix.smem_len;
	ग_लिखो_le32(NEOREG_CURSMEMPOS, ((0x000f & (addr >> 10)) << 8) |
					((0x0ff0 & (addr >> 10)) >> 4), par);
	addr = (अचिन्हित दीर्घ) info->screen_base + info->fix.smem_len;
	info->sprite.addr = (u8 *) addr; */
	वापस 0;
पूर्ण

अटल व्योम neo_unmap_video(काष्ठा fb_info *info)
अणु
	काष्ठा neofb_par *par = info->par;

	DBG("neo_unmap_video");

	arch_phys_wc_del(par->wc_cookie);
	iounmap(info->screen_base);
	info->screen_base = शून्य;

	release_mem_region(info->fix.smem_start,
			   info->fix.smem_len);
पूर्ण

अटल पूर्णांक neo_scan_monitor(काष्ठा fb_info *info)
अणु
	काष्ठा neofb_par *par = info->par;
	अचिन्हित अक्षर type, display;
	पूर्णांक w;

	// Eventually we will have i2c support.
	info->monspecs.modedb = kदो_स्मृति(माप(काष्ठा fb_videomode), GFP_KERNEL);
	अगर (!info->monspecs.modedb)
		वापस -ENOMEM;
	info->monspecs.modedb_len = 1;

	/* Determine the panel type */
	vga_wgfx(शून्य, 0x09, 0x26);
	type = vga_rgfx(शून्य, 0x21);
	display = vga_rgfx(शून्य, 0x20);
	अगर (!par->पूर्णांकernal_display && !par->बाह्यal_display) अणु
		par->पूर्णांकernal_display = display & 2 || !(display & 3) ? 1 : 0;
		par->बाह्यal_display = display & 1;
		prपूर्णांकk (KERN_INFO "Autodetected %s display\n",
			par->पूर्णांकernal_display && par->बाह्यal_display ? "simultaneous" :
			par->पूर्णांकernal_display ? "internal" : "external");
	पूर्ण

	/* Determine panel width -- used in NeoValidMode. */
	w = vga_rgfx(शून्य, 0x20);
	vga_wgfx(शून्य, 0x09, 0x00);
	चयन ((w & 0x18) >> 3) अणु
	हाल 0x00:
		// 640x480@60
		par->NeoPanelWidth = 640;
		par->NeoPanelHeight = 480;
		स_नकल(info->monspecs.modedb, &vesa_modes[3], माप(काष्ठा fb_videomode));
		अवरोध;
	हाल 0x01:
		par->NeoPanelWidth = 800;
		अगर (par->libretto) अणु
			par->NeoPanelHeight = 480;
			स_नकल(info->monspecs.modedb, &mode800x480, माप(काष्ठा fb_videomode));
		पूर्ण अन्यथा अणु
			// 800x600@60
			par->NeoPanelHeight = 600;
			स_नकल(info->monspecs.modedb, &vesa_modes[8], माप(काष्ठा fb_videomode));
		पूर्ण
		अवरोध;
	हाल 0x02:
		// 1024x768@60
		par->NeoPanelWidth = 1024;
		par->NeoPanelHeight = 768;
		स_नकल(info->monspecs.modedb, &vesa_modes[13], माप(काष्ठा fb_videomode));
		अवरोध;
	हाल 0x03:
		/* 1280x1024@60 panel support needs to be added */
#अगर_घोषित NOT_DONE
		par->NeoPanelWidth = 1280;
		par->NeoPanelHeight = 1024;
		स_नकल(info->monspecs.modedb, &vesa_modes[20], माप(काष्ठा fb_videomode));
		अवरोध;
#अन्यथा
		prपूर्णांकk(KERN_ERR
		       "neofb: Only 640x480, 800x600/480 and 1024x768 panels are currently supported\n");
		kमुक्त(info->monspecs.modedb);
		वापस -1;
#पूर्ण_अगर
	शेष:
		// 640x480@60
		par->NeoPanelWidth = 640;
		par->NeoPanelHeight = 480;
		स_नकल(info->monspecs.modedb, &vesa_modes[3], माप(काष्ठा fb_videomode));
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Panel is a %dx%d %s %s display\n",
	       par->NeoPanelWidth,
	       par->NeoPanelHeight,
	       (type & 0x02) ? "color" : "monochrome",
	       (type & 0x10) ? "TFT" : "dual scan");
	वापस 0;
पूर्ण

अटल पूर्णांक neo_init_hw(काष्ठा fb_info *info)
अणु
	काष्ठा neofb_par *par = info->par;
	पूर्णांक videoRam = 896;
	पूर्णांक maxClock = 65000;
	पूर्णांक CursorOff = 0x100;

	DBG("neo_init_hw");

	neoUnlock();

#अगर 0
	prपूर्णांकk(KERN_DEBUG "--- Neo extended register dump ---\n");
	क्रम (पूर्णांक w = 0; w < 0x85; w++)
		prपूर्णांकk(KERN_DEBUG "CR %p: %p\n", (व्योम *) w,
		       (व्योम *) vga_rcrt(शून्य, w));
	क्रम (पूर्णांक w = 0; w < 0xC7; w++)
		prपूर्णांकk(KERN_DEBUG "GR %p: %p\n", (व्योम *) w,
		       (व्योम *) vga_rgfx(शून्य, w));
#पूर्ण_अगर
	चयन (info->fix.accel) अणु
	हाल FB_ACCEL_NEOMAGIC_NM2070:
		videoRam = 896;
		maxClock = 65000;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2090:
	हाल FB_ACCEL_NEOMAGIC_NM2093:
	हाल FB_ACCEL_NEOMAGIC_NM2097:
		videoRam = 1152;
		maxClock = 80000;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2160:
		videoRam = 2048;
		maxClock = 90000;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2200:
		videoRam = 2560;
		maxClock = 110000;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2230:
		videoRam = 3008;
		maxClock = 110000;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2360:
		videoRam = 4096;
		maxClock = 110000;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2380:
		videoRam = 6144;
		maxClock = 110000;
		अवरोध;
	पूर्ण
	चयन (info->fix.accel) अणु
	हाल FB_ACCEL_NEOMAGIC_NM2070:
	हाल FB_ACCEL_NEOMAGIC_NM2090:
	हाल FB_ACCEL_NEOMAGIC_NM2093:
		CursorOff = 0x100;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2097:
	हाल FB_ACCEL_NEOMAGIC_NM2160:
		CursorOff = 0x100;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2200:
	हाल FB_ACCEL_NEOMAGIC_NM2230:
	हाल FB_ACCEL_NEOMAGIC_NM2360:
	हाल FB_ACCEL_NEOMAGIC_NM2380:
		CursorOff = 0x1000;

		par->neo2200 = (Neo2200 __iomem *) par->mmio_vbase;
		अवरोध;
	पूर्ण
/*
	info->sprite.size = CursorMem;
	info->sprite.scan_align = 1;
	info->sprite.buf_align = 1;
	info->sprite.flags = FB_PIXMAP_IO;
	info->sprite.outbuf = neofb_draw_cursor;
*/
	par->maxClock = maxClock;
	par->cursorOff = CursorOff;
	वापस videoRam * 1024;
पूर्ण


अटल काष्ठा fb_info *neo_alloc_fb_info(काष्ठा pci_dev *dev,
					 स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा fb_info *info;
	काष्ठा neofb_par *par;

	info = framebuffer_alloc(माप(काष्ठा neofb_par), &dev->dev);

	अगर (!info)
		वापस शून्य;

	par = info->par;

	info->fix.accel = id->driver_data;

	par->pci_burst = !nopciburst;
	par->lcd_stretch = !nostretch;
	par->libretto = libretto;

	par->पूर्णांकernal_display = पूर्णांकernal;
	par->बाह्यal_display = बाह्यal;
	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;

	चयन (info->fix.accel) अणु
	हाल FB_ACCEL_NEOMAGIC_NM2070:
		snम_लिखो(info->fix.id, माप(info->fix.id),
				"MagicGraph 128");
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2090:
		snम_लिखो(info->fix.id, माप(info->fix.id),
				"MagicGraph 128V");
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2093:
		snम_लिखो(info->fix.id, माप(info->fix.id),
				"MagicGraph 128ZV");
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2097:
		snम_लिखो(info->fix.id, माप(info->fix.id),
				"MagicGraph 128ZV+");
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2160:
		snम_लिखो(info->fix.id, माप(info->fix.id),
				"MagicGraph 128XD");
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2200:
		snम_लिखो(info->fix.id, माप(info->fix.id),
				"MagicGraph 256AV");
		info->flags |= FBINFO_HWACCEL_IMAGEBLIT |
		               FBINFO_HWACCEL_COPYAREA |
                	       FBINFO_HWACCEL_FILLRECT;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2230:
		snम_लिखो(info->fix.id, माप(info->fix.id),
				"MagicGraph 256AV+");
		info->flags |= FBINFO_HWACCEL_IMAGEBLIT |
		               FBINFO_HWACCEL_COPYAREA |
                	       FBINFO_HWACCEL_FILLRECT;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2360:
		snम_लिखो(info->fix.id, माप(info->fix.id),
				"MagicGraph 256ZX");
		info->flags |= FBINFO_HWACCEL_IMAGEBLIT |
		               FBINFO_HWACCEL_COPYAREA |
                	       FBINFO_HWACCEL_FILLRECT;
		अवरोध;
	हाल FB_ACCEL_NEOMAGIC_NM2380:
		snम_लिखो(info->fix.id, माप(info->fix.id),
				"MagicGraph 256XL+");
		info->flags |= FBINFO_HWACCEL_IMAGEBLIT |
		               FBINFO_HWACCEL_COPYAREA |
                	       FBINFO_HWACCEL_FILLRECT;
		अवरोध;
	पूर्ण

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 0;
	info->fix.ypanstep = 4;
	info->fix.ywrapstep = 0;
	info->fix.accel = id->driver_data;

	info->fbops = &neofb_ops;
	info->pseuकरो_palette = par->palette;
	वापस info;
पूर्ण

अटल व्योम neo_मुक्त_fb_info(काष्ठा fb_info *info)
अणु
	अगर (info) अणु
		/*
		 * Free the colourmap
		 */
		fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
	पूर्ण
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक neofb_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा fb_info *info;
	u_पूर्णांक h_sync, v_sync;
	पूर्णांक video_len, err;

	DBG("neofb_probe");

	err = pci_enable_device(dev);
	अगर (err)
		वापस err;

	err = -ENOMEM;
	info = neo_alloc_fb_info(dev, id);
	अगर (!info)
		वापस err;

	err = neo_map_mmio(info, dev);
	अगर (err)
		जाओ err_map_mmio;

	err = neo_scan_monitor(info);
	अगर (err)
		जाओ err_scan_monitor;

	video_len = neo_init_hw(info);
	अगर (video_len < 0) अणु
		err = video_len;
		जाओ err_init_hw;
	पूर्ण

	err = neo_map_video(info, dev, video_len);
	अगर (err)
		जाओ err_init_hw;

	अगर (!fb_find_mode(&info->var, info, mode_option, शून्य, 0,
			info->monspecs.modedb, 16)) अणु
		prपूर्णांकk(KERN_ERR "neofb: Unable to find usable video mode.\n");
		err = -EINVAL;
		जाओ err_map_video;
	पूर्ण

	/*
	 * Calculate the hsync and vsync frequencies.  Note that
	 * we split the 1e12 स्थिरant up so that we can preserve
	 * the precision and fit the results पूर्णांकo 32-bit रेजिस्टरs.
	 *  (1953125000 * 512 = 1e12)
	 */
	h_sync = 1953125000 / info->var.pixघड़ी;
	h_sync =
	    h_sync * 512 / (info->var.xres + info->var.left_margin +
			    info->var.right_margin + info->var.hsync_len);
	v_sync =
	    h_sync / (info->var.yres + info->var.upper_margin +
		      info->var.lower_margin + info->var.vsync_len);

	prपूर्णांकk(KERN_INFO "neofb v" Nखातापूर्णB_VERSION
	       ": %dkB VRAM, using %dx%d, %d.%03dkHz, %dHz\n",
	       info->fix.smem_len >> 10, info->var.xres,
	       info->var.yres, h_sync / 1000, h_sync % 1000, v_sync);

	err = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (err < 0)
		जाओ err_map_video;

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ err_reg_fb;

	fb_info(info, "%s frame buffer device\n", info->fix.id);

	/*
	 * Our driver data
	 */
	pci_set_drvdata(dev, info);
	वापस 0;

err_reg_fb:
	fb_dealloc_cmap(&info->cmap);
err_map_video:
	neo_unmap_video(info);
err_init_hw:
	fb_destroy_modedb(info->monspecs.modedb);
err_scan_monitor:
	neo_unmap_mmio(info);
err_map_mmio:
	neo_मुक्त_fb_info(info);
	वापस err;
पूर्ण

अटल व्योम neofb_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);

	DBG("neofb_remove");

	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);

		neo_unmap_video(info);
		fb_destroy_modedb(info->monspecs.modedb);
		neo_unmap_mmio(info);
		neo_मुक्त_fb_info(info);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id neofb_devices[] = अणु
	अणुPCI_VENDOR_ID_NEOMAGIC, PCI_CHIP_NM2070,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_NEOMAGIC_NM2070पूर्ण,

	अणुPCI_VENDOR_ID_NEOMAGIC, PCI_CHIP_NM2090,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_NEOMAGIC_NM2090पूर्ण,

	अणुPCI_VENDOR_ID_NEOMAGIC, PCI_CHIP_NM2093,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_NEOMAGIC_NM2093पूर्ण,

	अणुPCI_VENDOR_ID_NEOMAGIC, PCI_CHIP_NM2097,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_NEOMAGIC_NM2097पूर्ण,

	अणुPCI_VENDOR_ID_NEOMAGIC, PCI_CHIP_NM2160,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_NEOMAGIC_NM2160पूर्ण,

	अणुPCI_VENDOR_ID_NEOMAGIC, PCI_CHIP_NM2200,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_NEOMAGIC_NM2200पूर्ण,

	अणुPCI_VENDOR_ID_NEOMAGIC, PCI_CHIP_NM2230,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_NEOMAGIC_NM2230पूर्ण,

	अणुPCI_VENDOR_ID_NEOMAGIC, PCI_CHIP_NM2360,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_NEOMAGIC_NM2360पूर्ण,

	अणुPCI_VENDOR_ID_NEOMAGIC, PCI_CHIP_NM2380,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_NEOMAGIC_NM2380पूर्ण,

	अणु0, 0, 0, 0, 0, 0, 0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, neofb_devices);

अटल काष्ठा pci_driver neofb_driver = अणु
	.name =		"neofb",
	.id_table =	neofb_devices,
	.probe =	neofb_probe,
	.हटाओ =	neofb_हटाओ,
पूर्ण;

/* ************************* init in-kernel code ************************** */

#अगर_अघोषित MODULE
अटल पूर्णांक __init neofb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	DBG("neofb_setup");

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;

		अगर (!म_भेदन(this_opt, "internal", 8))
			पूर्णांकernal = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "external", 8))
			बाह्यal = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "nostretch", 9))
			nostretch = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "nopciburst", 10))
			nopciburst = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "libretto", 8))
			libretto = 1;
		अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर  /*  MODULE  */

अटल पूर्णांक __init neofb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("neofb", &option))
		वापस -ENODEV;
	neofb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&neofb_driver);
पूर्ण

module_init(neofb_init);

#अगर_घोषित MODULE
अटल व्योम __निकास neofb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&neofb_driver);
पूर्ण

module_निकास(neofb_निकास);
#पूर्ण_अगर				/* MODULE */
