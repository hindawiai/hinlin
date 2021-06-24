<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200 and G400
 *
 * (c) 1998-2002 Petr Vandrovec <vandrove@vc.cvut.cz>
 *
 * Portions Copyright (c) 2001 Matrox Graphics Inc.
 *
 * Version: 1.65 2002/08/14
 *
 * MTRR stuff: 1998 Tom Rini <trini@kernel.crashing.org>
 *
 * Contributors: "menion?" <menion@mindless.com>
 *                     Betatesting, fixes, ideas
 *
 *               "Kurt Garloff" <garloff@suse.de>
 *                     Betatesting, fixes, ideas, videomodes, videomodes timmings
 *
 *               "Tom Rini" <trini@kernel.crashing.org>
 *                     MTRR stuff, PPC cleanups, betatesting, fixes, ideas
 *
 *               "Bibek Sahu" <scorpio@करोdds.net>
 *                     Access device through पढ़ोb|w|l and ग_लिखो b|w|l
 *                     Extensive debugging stuff
 *
 *               "Daniel Haun" <haund@usa.net>
 *                     Testing, hardware cursor fixes
 *
 *               "Scott Wood" <sawst46+@pitt.edu>
 *                     Fixes
 *
 *               "Gerd Knorr" <kraxel@goldbach.isdn.cs.tu-berlin.de>
 *                     Betatesting
 *
 *               "Kelly French" <targon@hazmat.com>
 *               "Fernando Herrera" <fherrera@eurielec.etsit.upm.es>
 *                     Betatesting, bug reporting
 *
 *               "Pablo Bianucci" <pbian@pccp.com.ar>
 *                     Fixes, ideas, betatesting
 *
 *               "Inaky Perez Gonzalez" <inaky@peloncho.fis.ucm.es>
 *                     Fixes, enhandcements, ideas, betatesting
 *
 *               "Ryuichi Oikawa" <roikawa@rr.iiij4u.or.jp>
 *                     PPC betatesting, PPC support, backward compatibility
 *
 *               "Paul Womar" <Paul@pwomar.demon.co.uk>
 *               "Owen Waller" <O.Waller@ee.qub.ac.uk>
 *                     PPC betatesting
 *
 *               "Thomas Pornin" <pornin@bolet.ens.fr>
 *                     Alpha betatesting
 *
 *               "Pieter van Leuven" <pvl@iae.nl>
 *               "Ulf Jaenicke-Roessler" <ujr@physik.phy.tu-dresden.de>
 *                     G100 testing
 *
 *               "H. Peter Arvin" <hpa@transmeta.com>
 *                     Ideas
 *
 *               "Cort Dougan" <cort@cs.nmt.edu>
 *                     CHRP fixes and PReP cleanup
 *
 *               "Mark Vojkovich" <mvojkovi@ucsd.edu>
 *                     G400 support
 *
 *               "David C. Hansen" <haveblue@us.ibm.com>
 *                     Fixes
 *
 *               "Ian Romanick" <idr@us.ibm.com>
 *                     Find PInS data in BIOS on PowerPC प्रणालीs.
 *
 * (following author is not in any relation with this code, but his code
 *  is included in this driver)
 *
 * Based on framebuffer driver क्रम VBE 2.0 compliant graphic boards
 *     (c) 1998 Gerd Knorr <kraxel@cs.tu-berlin.de>
 *
 * (following author is not in any relation with this code, but his ideas
 *  were used when writing this driver)
 *
 *		 FreeVBE/AF (Matrox), "Shawn Hargreaves" <shawn@talula.demon.co.uk>
 *
 */


#समावेश "matroxfb_misc.h"
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/matroxfb.h>

व्योम matroxfb_DAC_out(स्थिर काष्ठा matrox_fb_info *minfo, पूर्णांक reg, पूर्णांक val)
अणु
	DBG_REG(__func__)
	mga_outb(M_RAMDAC_BASE+M_X_INDEX, reg);
	mga_outb(M_RAMDAC_BASE+M_X_DATAREG, val);
पूर्ण

पूर्णांक matroxfb_DAC_in(स्थिर काष्ठा matrox_fb_info *minfo, पूर्णांक reg)
अणु
	DBG_REG(__func__)
	mga_outb(M_RAMDAC_BASE+M_X_INDEX, reg);
	वापस mga_inb(M_RAMDAC_BASE+M_X_DATAREG);
पूर्ण

व्योम matroxfb_var2my(काष्ठा fb_var_screeninfo* var, काष्ठा my_timming* mt) अणु
	अचिन्हित पूर्णांक pixघड़ी = var->pixघड़ी;

	DBG(__func__)

	अगर (!pixघड़ी) pixघड़ी = 10000;	/* 10ns = 100MHz */
	mt->pixघड़ी = 1000000000 / pixघड़ी;
	अगर (mt->pixघड़ी < 1) mt->pixघड़ी = 1;
	mt->mnp = -1;
	mt->dblscan = var->vmode & FB_VMODE_DOUBLE;
	mt->पूर्णांकerlaced = var->vmode & FB_VMODE_INTERLACED;
	mt->HDisplay = var->xres;
	mt->HSyncStart = mt->HDisplay + var->right_margin;
	mt->HSyncEnd = mt->HSyncStart + var->hsync_len;
	mt->HTotal = mt->HSyncEnd + var->left_margin;
	mt->VDisplay = var->yres;
	mt->VSyncStart = mt->VDisplay + var->lower_margin;
	mt->VSyncEnd = mt->VSyncStart + var->vsync_len;
	mt->VTotal = mt->VSyncEnd + var->upper_margin;
	mt->sync = var->sync;
पूर्ण

पूर्णांक matroxfb_PLL_calcघड़ी(स्थिर काष्ठा matrox_pll_features* pll, अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक fmax,
		अचिन्हित पूर्णांक* in, अचिन्हित पूर्णांक* feed, अचिन्हित पूर्णांक* post) अणु
	अचिन्हित पूर्णांक bestdअगरf = ~0;
	अचिन्हित पूर्णांक bestvco = 0;
	अचिन्हित पूर्णांक fxtal = pll->ref_freq;
	अचिन्हित पूर्णांक fwant;
	अचिन्हित पूर्णांक p;

	DBG(__func__)

	fwant = freq;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_ERR "post_shift_max: %d\n", pll->post_shअगरt_max);
	prपूर्णांकk(KERN_ERR "ref_freq: %d\n", pll->ref_freq);
	prपूर्णांकk(KERN_ERR "freq: %d\n", freq);
	prपूर्णांकk(KERN_ERR "vco_freq_min: %d\n", pll->vco_freq_min);
	prपूर्णांकk(KERN_ERR "in_div_min: %d\n", pll->in_भाग_min);
	prपूर्णांकk(KERN_ERR "in_div_max: %d\n", pll->in_भाग_max);
	prपूर्णांकk(KERN_ERR "feed_div_min: %d\n", pll->feed_भाग_min);
	prपूर्णांकk(KERN_ERR "feed_div_max: %d\n", pll->feed_भाग_max);
	prपूर्णांकk(KERN_ERR "fmax: %d\n", fmax);
#पूर्ण_अगर
	क्रम (p = 1; p <= pll->post_shअगरt_max; p++) अणु
		अगर (fwant * 2 > fmax)
			अवरोध;
		fwant *= 2;
	पूर्ण
	अगर (fwant < pll->vco_freq_min) fwant = pll->vco_freq_min;
	अगर (fwant > fmax) fwant = fmax;
	क्रम (; p-- > 0; fwant >>= 1, bestdअगरf >>= 1) अणु
		अचिन्हित पूर्णांक m;

		अगर (fwant < pll->vco_freq_min) अवरोध;
		क्रम (m = pll->in_भाग_min; m <= pll->in_भाग_max; m++) अणु
			अचिन्हित पूर्णांक dअगरf, fvco;
			अचिन्हित पूर्णांक n;

			n = (fwant * (m + 1) + (fxtal >> 1)) / fxtal - 1;
			अगर (n > pll->feed_भाग_max)
				अवरोध;
			अगर (n < pll->feed_भाग_min)
				n = pll->feed_भाग_min;
			fvco = (fxtal * (n + 1)) / (m + 1);
			अगर (fvco < fwant)
				dअगरf = fwant - fvco;
			अन्यथा
				dअगरf = fvco - fwant;
			अगर (dअगरf < bestdअगरf) अणु
				bestdअगरf = dअगरf;
				*post = p;
				*in = m;
				*feed = n;
				bestvco = fvco;
			पूर्ण
		पूर्ण
	पूर्ण
	dprपूर्णांकk(KERN_ERR "clk: %02X %02X %02X %d %d %d\n", *in, *feed, *post, fxtal, bestvco, fwant);
	वापस bestvco;
पूर्ण

पूर्णांक matroxfb_vgaHWinit(काष्ठा matrox_fb_info *minfo, काष्ठा my_timming *m)
अणु
	अचिन्हित पूर्णांक hd, hs, he, hbe, ht;
	अचिन्हित पूर्णांक vd, vs, ve, vt, lc;
	अचिन्हित पूर्णांक wd;
	अचिन्हित पूर्णांक भागider;
	पूर्णांक i;
	काष्ठा matrox_hw_state * स्थिर hw = &minfo->hw;

	DBG(__func__)

	hw->SEQ[0] = 0x00;
	hw->SEQ[1] = 0x01;	/* or 0x09 */
	hw->SEQ[2] = 0x0F;	/* bitplanes */
	hw->SEQ[3] = 0x00;
	hw->SEQ[4] = 0x0E;
	/* CRTC 0..7, 9, 16..19, 21, 22 are reprogrammed by Matrox Millennium code... Hope that by MGA1064 too */
	अगर (m->dblscan) अणु
		m->VTotal <<= 1;
		m->VDisplay <<= 1;
		m->VSyncStart <<= 1;
		m->VSyncEnd <<= 1;
	पूर्ण
	अगर (m->पूर्णांकerlaced) अणु
		m->VTotal >>= 1;
		m->VDisplay >>= 1;
		m->VSyncStart >>= 1;
		m->VSyncEnd >>= 1;
	पूर्ण

	/* GCTL is ignored when not using 0xA0000 aperture */
	hw->GCTL[0] = 0x00;
	hw->GCTL[1] = 0x00;
	hw->GCTL[2] = 0x00;
	hw->GCTL[3] = 0x00;
	hw->GCTL[4] = 0x00;
	hw->GCTL[5] = 0x40;
	hw->GCTL[6] = 0x05;
	hw->GCTL[7] = 0x0F;
	hw->GCTL[8] = 0xFF;

	/* Whole ATTR is ignored in PowerGraphics mode */
	क्रम (i = 0; i < 16; i++)
		hw->ATTR[i] = i;
	hw->ATTR[16] = 0x41;
	hw->ATTR[17] = 0xFF;
	hw->ATTR[18] = 0x0F;
	hw->ATTR[19] = 0x00;
	hw->ATTR[20] = 0x00;

	hd = m->HDisplay >> 3;
	hs = m->HSyncStart >> 3;
	he = m->HSyncEnd >> 3;
	ht = m->HTotal >> 3;
	/* standard timmings are in 8pixels, but क्रम पूर्णांकerleaved we cannot */
	/* करो it क्रम 4bpp (because of (4bpp >> 1(पूर्णांकerleaved))/4 == 0) */
	/* using 16 or more pixels per unit can save us */
	भागider = minfo->curr.final_bppShअगरt;
	जबतक (भागider & 3) अणु
		hd >>= 1;
		hs >>= 1;
		he >>= 1;
		ht >>= 1;
		भागider <<= 1;
	पूर्ण
	भागider = भागider / 4;
	/* भागider can be from 1 to 8 */
	जबतक (भागider > 8) अणु
		hd <<= 1;
		hs <<= 1;
		he <<= 1;
		ht <<= 1;
		भागider >>= 1;
	पूर्ण
	hd = hd - 1;
	hs = hs - 1;
	he = he - 1;
	ht = ht - 1;
	vd = m->VDisplay - 1;
	vs = m->VSyncStart - 1;
	ve = m->VSyncEnd - 1;
	vt = m->VTotal - 2;
	lc = vd;
	/* G200 cannot work with (ht & 7) == 6 */
	अगर (((ht & 0x07) == 0x06) || ((ht & 0x0F) == 0x04))
		ht++;
	hbe = ht;
	wd = minfo->fbcon.var.xres_भव * minfo->curr.final_bppShअगरt / 64;

	hw->CRTCEXT[0] = 0;
	hw->CRTCEXT[5] = 0;
	अगर (m->पूर्णांकerlaced) अणु
		hw->CRTCEXT[0] = 0x80;
		hw->CRTCEXT[5] = (hs + he - ht) >> 1;
		अगर (!m->dblscan)
			wd <<= 1;
		vt &= ~1;
	पूर्ण
	hw->CRTCEXT[0] |=  (wd & 0x300) >> 4;
	hw->CRTCEXT[1] = (((ht - 4) & 0x100) >> 8) |
			  ((hd      & 0x100) >> 7) | /* blanking */
			  ((hs      & 0x100) >> 6) | /* sync start */
			   (hbe     & 0x040);	 /* end hor. blanking */
	/* FIXME: Enable vidrst only on G400, and only अगर TV-out is used */
	अगर (minfo->outमाला_दो[1].src == MATROXFB_SRC_CRTC1)
		hw->CRTCEXT[1] |= 0x88;		/* enable horizontal and vertical vidrst */
	hw->CRTCEXT[2] =  ((vt & 0xC00) >> 10) |
			  ((vd & 0x400) >>  8) |	/* disp end */
			  ((vd & 0xC00) >>  7) |	/* vblanking start */
			  ((vs & 0xC00) >>  5) |
			  ((lc & 0x400) >>  3);
	hw->CRTCEXT[3] = (भागider - 1) | 0x80;
	hw->CRTCEXT[4] = 0;

	hw->CRTC[0] = ht-4;
	hw->CRTC[1] = hd;
	hw->CRTC[2] = hd;
	hw->CRTC[3] = (hbe & 0x1F) | 0x80;
	hw->CRTC[4] = hs;
	hw->CRTC[5] = ((hbe & 0x20) << 2) | (he & 0x1F);
	hw->CRTC[6] = vt & 0xFF;
	hw->CRTC[7] = ((vt & 0x100) >> 8) |
		      ((vd & 0x100) >> 7) |
		      ((vs & 0x100) >> 6) |
		      ((vd & 0x100) >> 5) |
		      ((lc & 0x100) >> 4) |
		      ((vt & 0x200) >> 4) |
		      ((vd & 0x200) >> 3) |
		      ((vs & 0x200) >> 2);
	hw->CRTC[8] = 0x00;
	hw->CRTC[9] = ((vd & 0x200) >> 4) |
		      ((lc & 0x200) >> 3);
	अगर (m->dblscan && !m->पूर्णांकerlaced)
		hw->CRTC[9] |= 0x80;
	क्रम (i = 10; i < 16; i++)
		hw->CRTC[i] = 0x00;
	hw->CRTC[16] = vs /* & 0xFF */;
	hw->CRTC[17] = (ve & 0x0F) | 0x20;
	hw->CRTC[18] = vd /* & 0xFF */;
	hw->CRTC[19] = wd /* & 0xFF */;
	hw->CRTC[20] = 0x00;
	hw->CRTC[21] = vd /* & 0xFF */;
	hw->CRTC[22] = (vt + 1) /* & 0xFF */;
	hw->CRTC[23] = 0xC3;
	hw->CRTC[24] = lc;
	वापस 0;
पूर्ण;

व्योम matroxfb_vgaHWrestore(काष्ठा matrox_fb_info *minfo)
अणु
	पूर्णांक i;
	काष्ठा matrox_hw_state * स्थिर hw = &minfo->hw;
	CRITFLAGS

	DBG(__func__)

	dprपूर्णांकk(KERN_INFO "MiscOutReg: %02X\n", hw->MiscOutReg);
	dprपूर्णांकk(KERN_INFO "SEQ regs:   ");
	क्रम (i = 0; i < 5; i++)
		dprपूर्णांकk("%02X:", hw->SEQ[i]);
	dprपूर्णांकk("\n");
	dprपूर्णांकk(KERN_INFO "GDC regs:   ");
	क्रम (i = 0; i < 9; i++)
		dprपूर्णांकk("%02X:", hw->GCTL[i]);
	dprपूर्णांकk("\n");
	dprपूर्णांकk(KERN_INFO "CRTC regs: ");
	क्रम (i = 0; i < 25; i++)
		dprपूर्णांकk("%02X:", hw->CRTC[i]);
	dprपूर्णांकk("\n");
	dprपूर्णांकk(KERN_INFO "ATTR regs: ");
	क्रम (i = 0; i < 21; i++)
		dprपूर्णांकk("%02X:", hw->ATTR[i]);
	dprपूर्णांकk("\n");

	CRITBEGIN

	mga_inb(M_ATTR_RESET);
	mga_outb(M_ATTR_INDEX, 0);
	mga_outb(M_MISC_REG, hw->MiscOutReg);
	क्रम (i = 1; i < 5; i++)
		mga_setr(M_SEQ_INDEX, i, hw->SEQ[i]);
	mga_setr(M_CRTC_INDEX, 17, hw->CRTC[17] & 0x7F);
	क्रम (i = 0; i < 25; i++)
		mga_setr(M_CRTC_INDEX, i, hw->CRTC[i]);
	क्रम (i = 0; i < 9; i++)
		mga_setr(M_GRAPHICS_INDEX, i, hw->GCTL[i]);
	क्रम (i = 0; i < 21; i++) अणु
		mga_inb(M_ATTR_RESET);
		mga_outb(M_ATTR_INDEX, i);
		mga_outb(M_ATTR_INDEX, hw->ATTR[i]);
	पूर्ण
	mga_outb(M_PALETTE_MASK, 0xFF);
	mga_outb(M_DAC_REG, 0x00);
	क्रम (i = 0; i < 768; i++)
		mga_outb(M_DAC_VAL, hw->DACpal[i]);
	mga_inb(M_ATTR_RESET);
	mga_outb(M_ATTR_INDEX, 0x20);

	CRITEND
पूर्ण

अटल व्योम get_pins(अचिन्हित अक्षर __iomem* pins, काष्ठा matrox_bios* bd) अणु
	अचिन्हित पूर्णांक b0 = पढ़ोb(pins);
	
	अगर (b0 == 0x2E && पढ़ोb(pins+1) == 0x41) अणु
		अचिन्हित पूर्णांक pins_len = पढ़ोb(pins+2);
		अचिन्हित पूर्णांक i;
		अचिन्हित अक्षर cksum;
		अचिन्हित अक्षर* dst = bd->pins;

		अगर (pins_len < 3 || pins_len > 128) अणु
			वापस;
		पूर्ण
		*dst++ = 0x2E;
		*dst++ = 0x41;
		*dst++ = pins_len;
		cksum = 0x2E + 0x41 + pins_len;
		क्रम (i = 3; i < pins_len; i++) अणु
			cksum += *dst++ = पढ़ोb(pins+i);
		पूर्ण
		अगर (cksum) अणु
			वापस;
		पूर्ण
		bd->pins_len = pins_len;
	पूर्ण अन्यथा अगर (b0 == 0x40 && पढ़ोb(pins+1) == 0x00) अणु
		अचिन्हित पूर्णांक i;
		अचिन्हित अक्षर* dst = bd->pins;

		*dst++ = 0x40;
		*dst++ = 0;
		क्रम (i = 2; i < 0x40; i++) अणु
			*dst++ = पढ़ोb(pins+i);
		पूर्ण
		bd->pins_len = 0x40;
	पूर्ण
पूर्ण

अटल व्योम get_bios_version(अचिन्हित अक्षर __iomem * vbios, काष्ठा matrox_bios* bd) अणु
	अचिन्हित पूर्णांक pcir_offset;
	
	pcir_offset = पढ़ोb(vbios + 24) | (पढ़ोb(vbios + 25) << 8);
	अगर (pcir_offset >= 26 && pcir_offset < 0xFFE0 &&
	    पढ़ोb(vbios + pcir_offset    ) == 'P' &&
	    पढ़ोb(vbios + pcir_offset + 1) == 'C' &&
	    पढ़ोb(vbios + pcir_offset + 2) == 'I' &&
	    पढ़ोb(vbios + pcir_offset + 3) == 'R') अणु
		अचिन्हित अक्षर h;

		h = पढ़ोb(vbios + pcir_offset + 0x12);
		bd->version.vMaj = (h >> 4) & 0xF;
		bd->version.vMin = h & 0xF;
		bd->version.vRev = पढ़ोb(vbios + pcir_offset + 0x13);
	पूर्ण अन्यथा अणु
		अचिन्हित अक्षर h;

		h = पढ़ोb(vbios + 5);
		bd->version.vMaj = (h >> 4) & 0xF;
		bd->version.vMin = h & 0xF;
		bd->version.vRev = 0;
	पूर्ण
पूर्ण

अटल व्योम get_bios_output(अचिन्हित अक्षर __iomem* vbios, काष्ठा matrox_bios* bd) अणु
	अचिन्हित अक्षर b;
	
	b = पढ़ोb(vbios + 0x7FF1);
	अगर (b == 0xFF) अणु
		b = 0;
	पूर्ण
	bd->output.state = b;
पूर्ण

अटल व्योम get_bios_tvout(अचिन्हित अक्षर __iomem* vbios, काष्ठा matrox_bios* bd) अणु
	अचिन्हित पूर्णांक i;
	
	/* Check क्रम 'IBM .*(V....TVO' string - it means TVO BIOS */
	bd->output.tvout = 0;
	अगर (पढ़ोb(vbios + 0x1D) != 'I' ||
	    पढ़ोb(vbios + 0x1E) != 'B' ||
	    पढ़ोb(vbios + 0x1F) != 'M' ||
	    पढ़ोb(vbios + 0x20) != ' ') अणु
	    	वापस;
	पूर्ण
	क्रम (i = 0x2D; i < 0x2D + 128; i++) अणु
		अचिन्हित अक्षर b = पढ़ोb(vbios + i);
		
		अगर (b == '(' && readb(vbios + i + 1) == 'V') अणु
			अगर (पढ़ोb(vbios + i + 6) == 'T' &&
			    पढ़ोb(vbios + i + 7) == 'V' &&
			    पढ़ोb(vbios + i + 8) == 'O') अणु
				bd->output.tvout = 1;
			पूर्ण
			वापस;
		पूर्ण
		अगर (b == 0)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम parse_bios(अचिन्हित अक्षर __iomem* vbios, काष्ठा matrox_bios* bd) अणु
	अचिन्हित पूर्णांक pins_offset;
	
	अगर (पढ़ोb(vbios) != 0x55 || पढ़ोb(vbios + 1) != 0xAA) अणु
		वापस;
	पूर्ण
	bd->bios_valid = 1;
	get_bios_version(vbios, bd);
	get_bios_output(vbios, bd);
	get_bios_tvout(vbios, bd);
#अगर defined(__घातerpc__)
	/* On PowerPC cards, the PInS offset isn't stored at the end of the
	 * BIOS image.  Instead, you must search the entire BIOS image क्रम
	 * the magic PInS signature.
	 *
	 * This actually applies to all OpenFirmware base cards.  Since these
	 * cards could be put in a MIPS or SPARC प्रणाली, should the condition
	 * be something dअगरferent?
	 */
	क्रम ( pins_offset = 0 ; pins_offset <= 0xFF80 ; pins_offset++ ) अणु
		अचिन्हित अक्षर header[3];

		header[0] = पढ़ोb(vbios + pins_offset);
		header[1] = पढ़ोb(vbios + pins_offset + 1);
		header[2] = पढ़ोb(vbios + pins_offset + 2);
		अगर ( (header[0] == 0x2E) && (header[1] == 0x41)
		     && ((header[2] == 0x40) || (header[2] == 0x80)) ) अणु
			prपूर्णांकk(KERN_INFO "PInS data found at offset %u\n",
			       pins_offset);
			get_pins(vbios + pins_offset, bd);
			अवरोध;
		पूर्ण
	पूर्ण
#अन्यथा
	pins_offset = पढ़ोb(vbios + 0x7FFC) | (पढ़ोb(vbios + 0x7FFD) << 8);
	अगर (pins_offset <= 0xFF80) अणु
		get_pins(vbios + pins_offset, bd);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक parse_pins1(काष्ठा matrox_fb_info *minfo,
		       स्थिर काष्ठा matrox_bios *bd)
अणु
	अचिन्हित पूर्णांक maxdac;

	चयन (bd->pins[22]) अणु
		हाल 0:		maxdac = 175000; अवरोध;
		हाल 1:		maxdac = 220000; अवरोध;
		शेष:	maxdac = 240000; अवरोध;
	पूर्ण
	अगर (get_unaligned_le16(bd->pins + 24)) अणु
		maxdac = get_unaligned_le16(bd->pins + 24) * 10;
	पूर्ण
	minfo->limits.pixel.vcomax = maxdac;
	minfo->values.pll.प्रणाली = get_unaligned_le16(bd->pins + 28) ?
		get_unaligned_le16(bd->pins + 28) * 10 : 50000;
	/* ignore 4MB, 8MB, module घड़ीs */
	minfo->features.pll.ref_freq = 14318;
	minfo->values.reg.mctlwtst	= 0x00030101;
	वापस 0;
पूर्ण

अटल व्योम शेष_pins1(काष्ठा matrox_fb_info *minfo)
अणु
	/* Millennium */
	minfo->limits.pixel.vcomax	= 220000;
	minfo->values.pll.प्रणाली	=  50000;
	minfo->features.pll.ref_freq	=  14318;
	minfo->values.reg.mctlwtst	= 0x00030101;
पूर्ण

अटल पूर्णांक parse_pins2(काष्ठा matrox_fb_info *minfo,
		       स्थिर काष्ठा matrox_bios *bd)
अणु
	minfo->limits.pixel.vcomax	=
	minfo->limits.प्रणाली.vcomax	= (bd->pins[41] == 0xFF) ? 230000 : ((bd->pins[41] + 100) * 1000);
	minfo->values.reg.mctlwtst	= ((bd->pins[51] & 0x01) ? 0x00000001 : 0) |
					  ((bd->pins[51] & 0x02) ? 0x00000100 : 0) |
					  ((bd->pins[51] & 0x04) ? 0x00010000 : 0) |
					  ((bd->pins[51] & 0x08) ? 0x00020000 : 0);
	minfo->values.pll.प्रणाली	= (bd->pins[43] == 0xFF) ? 50000 : ((bd->pins[43] + 100) * 1000);
	minfo->features.pll.ref_freq	= 14318;
	वापस 0;
पूर्ण

अटल व्योम शेष_pins2(काष्ठा matrox_fb_info *minfo)
अणु
	/* Millennium II, Mystique */
	minfo->limits.pixel.vcomax	=
	minfo->limits.प्रणाली.vcomax	= 230000;
	minfo->values.reg.mctlwtst	= 0x00030101;
	minfo->values.pll.प्रणाली	=  50000;
	minfo->features.pll.ref_freq	=  14318;
पूर्ण

अटल पूर्णांक parse_pins3(काष्ठा matrox_fb_info *minfo,
		       स्थिर काष्ठा matrox_bios *bd)
अणु
	minfo->limits.pixel.vcomax	=
	minfo->limits.प्रणाली.vcomax	= (bd->pins[36] == 0xFF) ? 230000			: ((bd->pins[36] + 100) * 1000);
	minfo->values.reg.mctlwtst	= get_unaligned_le32(bd->pins + 48) == 0xFFFFFFFF ?
		0x01250A21 : get_unaligned_le32(bd->pins + 48);
	/* memory config */
	minfo->values.reg.memrdbk	= ((bd->pins[57] << 21) & 0x1E000000) |
					  ((bd->pins[57] << 22) & 0x00C00000) |
					  ((bd->pins[56] <<  1) & 0x000001E0) |
					  ( bd->pins[56]        & 0x0000000F);
	minfo->values.reg.opt		= (bd->pins[54] & 7) << 10;
	minfo->values.reg.opt2		= bd->pins[58] << 12;
	minfo->features.pll.ref_freq	= (bd->pins[52] & 0x20) ? 14318 : 27000;
	वापस 0;
पूर्ण

अटल व्योम शेष_pins3(काष्ठा matrox_fb_info *minfo)
अणु
	/* G100, G200 */
	minfo->limits.pixel.vcomax	=
	minfo->limits.प्रणाली.vcomax	= 230000;
	minfo->values.reg.mctlwtst	= 0x01250A21;
	minfo->values.reg.memrdbk	= 0x00000000;
	minfo->values.reg.opt		= 0x00000C00;
	minfo->values.reg.opt2		= 0x00000000;
	minfo->features.pll.ref_freq	=  27000;
पूर्ण

अटल पूर्णांक parse_pins4(काष्ठा matrox_fb_info *minfo,
		       स्थिर काष्ठा matrox_bios *bd)
अणु
	minfo->limits.pixel.vcomax	= (bd->pins[ 39] == 0xFF) ? 230000			: bd->pins[ 39] * 4000;
	minfo->limits.प्रणाली.vcomax	= (bd->pins[ 38] == 0xFF) ? minfo->limits.pixel.vcomax	: bd->pins[ 38] * 4000;
	minfo->values.reg.mctlwtst	= get_unaligned_le32(bd->pins + 71);
	minfo->values.reg.memrdbk	= ((bd->pins[87] << 21) & 0x1E000000) |
					  ((bd->pins[87] << 22) & 0x00C00000) |
					  ((bd->pins[86] <<  1) & 0x000001E0) |
					  ( bd->pins[86]        & 0x0000000F);
	minfo->values.reg.opt		= ((bd->pins[53] << 15) & 0x00400000) |
					  ((bd->pins[53] << 22) & 0x10000000) |
					  ((bd->pins[53] <<  7) & 0x00001C00);
	minfo->values.reg.opt3		= get_unaligned_le32(bd->pins + 67);
	minfo->values.pll.प्रणाली	= (bd->pins[ 65] == 0xFF) ? 200000 			: bd->pins[ 65] * 4000;
	minfo->features.pll.ref_freq	= (bd->pins[ 92] & 0x01) ? 14318 : 27000;
	वापस 0;
पूर्ण

अटल व्योम शेष_pins4(काष्ठा matrox_fb_info *minfo)
अणु
	/* G400 */
	minfo->limits.pixel.vcomax	=
	minfo->limits.प्रणाली.vcomax	= 252000;
	minfo->values.reg.mctlwtst	= 0x04A450A1;
	minfo->values.reg.memrdbk	= 0x000000E7;
	minfo->values.reg.opt		= 0x10000400;
	minfo->values.reg.opt3		= 0x0190A419;
	minfo->values.pll.प्रणाली	= 200000;
	minfo->features.pll.ref_freq	= 27000;
पूर्ण

अटल पूर्णांक parse_pins5(काष्ठा matrox_fb_info *minfo,
		       स्थिर काष्ठा matrox_bios *bd)
अणु
	अचिन्हित पूर्णांक mult;
	
	mult = bd->pins[4]?8000:6000;
	
	minfo->limits.pixel.vcomax	= (bd->pins[ 38] == 0xFF) ? 600000			: bd->pins[ 38] * mult;
	minfo->limits.प्रणाली.vcomax	= (bd->pins[ 36] == 0xFF) ? minfo->limits.pixel.vcomax	: bd->pins[ 36] * mult;
	minfo->limits.video.vcomax	= (bd->pins[ 37] == 0xFF) ? minfo->limits.प्रणाली.vcomax	: bd->pins[ 37] * mult;
	minfo->limits.pixel.vcomin	= (bd->pins[123] == 0xFF) ? 256000			: bd->pins[123] * mult;
	minfo->limits.प्रणाली.vcomin	= (bd->pins[121] == 0xFF) ? minfo->limits.pixel.vcomin	: bd->pins[121] * mult;
	minfo->limits.video.vcomin	= (bd->pins[122] == 0xFF) ? minfo->limits.प्रणाली.vcomin	: bd->pins[122] * mult;
	minfo->values.pll.प्रणाली	=
	minfo->values.pll.video		= (bd->pins[ 92] == 0xFF) ? 284000			: bd->pins[ 92] * 4000;
	minfo->values.reg.opt		= get_unaligned_le32(bd->pins + 48);
	minfo->values.reg.opt2		= get_unaligned_le32(bd->pins + 52);
	minfo->values.reg.opt3		= get_unaligned_le32(bd->pins + 94);
	minfo->values.reg.mctlwtst	= get_unaligned_le32(bd->pins + 98);
	minfo->values.reg.memmisc	= get_unaligned_le32(bd->pins + 102);
	minfo->values.reg.memrdbk	= get_unaligned_le32(bd->pins + 106);
	minfo->features.pll.ref_freq	= (bd->pins[110] & 0x01) ? 14318 : 27000;
	minfo->values.memory.ddr	= (bd->pins[114] & 0x60) == 0x20;
	minfo->values.memory.dll	= (bd->pins[115] & 0x02) != 0;
	minfo->values.memory.emrswen	= (bd->pins[115] & 0x01) != 0;
	minfo->values.reg.maccess	= minfo->values.memory.emrswen ? 0x00004000 : 0x00000000;
	अगर (bd->pins[115] & 4) अणु
		minfo->values.reg.mctlwtst_core = minfo->values.reg.mctlwtst;
	पूर्ण अन्यथा अणु
		अटल स्थिर u8 wtst_xlat[] = अणु
			0, 1, 5, 6, 7, 5, 2, 3
		पूर्ण;

		minfo->values.reg.mctlwtst_core = (minfo->values.reg.mctlwtst & ~7) |
						  wtst_xlat[minfo->values.reg.mctlwtst & 7];
	पूर्ण
	minfo->max_pixel_घड़ी_panellink = bd->pins[47] * 4000;
	वापस 0;
पूर्ण

अटल व्योम शेष_pins5(काष्ठा matrox_fb_info *minfo)
अणु
	/* Mine 16MB G450 with SDRAM DDR */
	minfo->limits.pixel.vcomax	=
	minfo->limits.प्रणाली.vcomax	=
	minfo->limits.video.vcomax	= 600000;
	minfo->limits.pixel.vcomin	=
	minfo->limits.प्रणाली.vcomin	=
	minfo->limits.video.vcomin	= 256000;
	minfo->values.pll.प्रणाली	=
	minfo->values.pll.video		= 284000;
	minfo->values.reg.opt		= 0x404A1160;
	minfo->values.reg.opt2		= 0x0000AC00;
	minfo->values.reg.opt3		= 0x0090A409;
	minfo->values.reg.mctlwtst_core	=
	minfo->values.reg.mctlwtst	= 0x0C81462B;
	minfo->values.reg.memmisc	= 0x80000004;
	minfo->values.reg.memrdbk	= 0x01001103;
	minfo->features.pll.ref_freq	= 27000;
	minfo->values.memory.ddr	= 1;
	minfo->values.memory.dll	= 1;
	minfo->values.memory.emrswen	= 1;
	minfo->values.reg.maccess	= 0x00004000;
पूर्ण

अटल पूर्णांक matroxfb_set_limits(काष्ठा matrox_fb_info *minfo,
			       स्थिर काष्ठा matrox_bios *bd)
अणु
	अचिन्हित पूर्णांक pins_version;
	अटल स्थिर अचिन्हित पूर्णांक pinslen[] = अणु 64, 64, 64, 128, 128 पूर्ण;

	चयन (minfo->chip) अणु
		हाल MGA_2064:	शेष_pins1(minfo); अवरोध;
		हाल MGA_2164:
		हाल MGA_1064:
		हाल MGA_1164:	शेष_pins2(minfo); अवरोध;
		हाल MGA_G100:
		हाल MGA_G200:	शेष_pins3(minfo); अवरोध;
		हाल MGA_G400:	शेष_pins4(minfo); अवरोध;
		हाल MGA_G450:
		हाल MGA_G550:	शेष_pins5(minfo); अवरोध;
	पूर्ण
	अगर (!bd->bios_valid) अणु
		prपूर्णांकk(KERN_INFO "matroxfb: Your Matrox device does not have BIOS\n");
		वापस -1;
	पूर्ण
	अगर (bd->pins_len < 64) अणु
		prपूर्णांकk(KERN_INFO "matroxfb: BIOS on your Matrox device does not contain powerup info\n");
		वापस -1;
	पूर्ण
	अगर (bd->pins[0] == 0x2E && bd->pins[1] == 0x41) अणु
		pins_version = bd->pins[5];
		अगर (pins_version < 2 || pins_version > 5) अणु
			prपूर्णांकk(KERN_INFO "matroxfb: Unknown version (%u) of powerup info\n", pins_version);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		pins_version = 1;
	पूर्ण
	अगर (bd->pins_len != pinslen[pins_version - 1]) अणु
		prपूर्णांकk(KERN_INFO "matroxfb: Invalid powerup info\n");
		वापस -1;
	पूर्ण
	चयन (pins_version) अणु
		हाल 1:
			वापस parse_pins1(minfo, bd);
		हाल 2:
			वापस parse_pins2(minfo, bd);
		हाल 3:
			वापस parse_pins3(minfo, bd);
		हाल 4:
			वापस parse_pins4(minfo, bd);
		हाल 5:
			वापस parse_pins5(minfo, bd);
		शेष:
			prपूर्णांकk(KERN_DEBUG "matroxfb: Powerup info version %u is not yet supported\n", pins_version);
			वापस -1;
	पूर्ण
पूर्ण

व्योम matroxfb_पढ़ो_pins(काष्ठा matrox_fb_info *minfo)
अणु
	u32 opt;
	u32 biosbase;
	u32 fbbase;
	काष्ठा pci_dev *pdev = minfo->pcidev;
	
	स_रखो(&minfo->bios, 0, माप(minfo->bios));
	pci_पढ़ो_config_dword(pdev, PCI_OPTION_REG, &opt);
	pci_ग_लिखो_config_dword(pdev, PCI_OPTION_REG, opt | PCI_OPTION_ENABLE_ROM);
	pci_पढ़ो_config_dword(pdev, PCI_ROM_ADDRESS, &biosbase);
	pci_पढ़ो_config_dword(pdev, minfo->devflags.fbResource, &fbbase);
	pci_ग_लिखो_config_dword(pdev, PCI_ROM_ADDRESS, (fbbase & PCI_ROM_ADDRESS_MASK) | PCI_ROM_ADDRESS_ENABLE);
	parse_bios(vaddr_va(minfo->video.vbase), &minfo->bios);
	pci_ग_लिखो_config_dword(pdev, PCI_ROM_ADDRESS, biosbase);
	pci_ग_लिखो_config_dword(pdev, PCI_OPTION_REG, opt);
#अगर_घोषित CONFIG_X86
	अगर (!minfo->bios.bios_valid) अणु
		अचिन्हित अक्षर __iomem* b;

		b = ioremap(0x000C0000, 65536);
		अगर (!b) अणु
			prपूर्णांकk(KERN_INFO "matroxfb: Unable to map legacy BIOS\n");
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक ven = पढ़ोb(b+0x64+0) | (पढ़ोb(b+0x64+1) << 8);
			अचिन्हित पूर्णांक dev = पढ़ोb(b+0x64+2) | (पढ़ोb(b+0x64+3) << 8);
			
			अगर (ven != pdev->venकरोr || dev != pdev->device) अणु
				prपूर्णांकk(KERN_INFO "matroxfb: Legacy BIOS is for %04X:%04X, while this device is %04X:%04X\n",
					ven, dev, pdev->venकरोr, pdev->device);
			पूर्ण अन्यथा अणु
				parse_bios(b, &minfo->bios);
			पूर्ण
			iounmap(b);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	matroxfb_set_limits(minfo, &minfo->bios);
	prपूर्णांकk(KERN_INFO "PInS memtype = %u\n",
	       (minfo->values.reg.opt & 0x1C00) >> 10);
पूर्ण

EXPORT_SYMBOL(matroxfb_DAC_in);
EXPORT_SYMBOL(matroxfb_DAC_out);
EXPORT_SYMBOL(matroxfb_var2my);
EXPORT_SYMBOL(matroxfb_PLL_calcघड़ी);
EXPORT_SYMBOL(matroxfb_vgaHWinit);		/* DAC1064, Ti3026 */
EXPORT_SYMBOL(matroxfb_vgaHWrestore);		/* DAC1064, Ti3026 */
EXPORT_SYMBOL(matroxfb_पढ़ो_pins);

MODULE_AUTHOR("(c) 1999-2002 Petr Vandrovec <vandrove@vc.cvut.cz>");
MODULE_DESCRIPTION("Miscellaneous support for Matrox video cards");
MODULE_LICENSE("GPL");
