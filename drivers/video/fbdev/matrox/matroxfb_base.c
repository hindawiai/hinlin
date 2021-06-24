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
 *               "Samuel Hocevar" <sam@via.ecp.fr>
 *                     Fixes
 *
 *               "Anton Altaparmakov" <AntonA@bigfoot.com>
 *                     G400 MAX/non-MAX distinction
 *
 *               "Ken Aaker" <kdaaker@rchland.vnet.ibm.com>
 *                     memtype extension (needed क्रम GXT130P RS/6000 adapter)
 *
 *               "Uns Lider" <unslider@miअक्रमa.org>
 *                     G100 PLNWT fixes
 *
 *               "Denis Zaitsev" <zzz@cd-club.ru>
 *                     Fixes
 *
 *               "Mike Pieper" <mike@pieper-family.de>
 *                     TVOut enhandcements, V4L2 control पूर्णांकerface.
 *
 *               "Diego Biurrun" <diego@biurrun.de>
 *                     DFP testing
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

#समावेश <linux/version.h>

#समावेश "matroxfb_base.h"
#समावेश "matroxfb_misc.h"
#समावेश "matroxfb_accel.h"
#समावेश "matroxfb_DAC1064.h"
#समावेश "matroxfb_Ti3026.h"
#समावेश "matroxfb_maven.h"
#समावेश "matroxfb_crtc2.h"
#समावेश "matroxfb_g450.h"
#समावेश <linux/matroxfb.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/nvram.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/machdep.h>
अटल पूर्णांक शेष_vmode = VMODE_NVRAM;
अटल पूर्णांक शेष_cmode = CMODE_NVRAM;
#पूर्ण_अगर

अटल व्योम matroxfb_unरेजिस्टर_device(काष्ठा matrox_fb_info* minfo);

/* --------------------------------------------------------------------- */

/*
 * card parameters
 */

/* --------------------------------------------------------------------- */

अटल काष्ठा fb_var_screeninfo vesafb_defined = अणु
	640,480,640,480,/* W,H, W, H (भव) load xres,xres_भव*/
	0,0,		/* भव -> visible no offset */
	8,		/* depth -> load bits_per_pixel */
	0,		/* greyscale ? */
	अणु0,0,0पूर्ण,	/* R */
	अणु0,0,0पूर्ण,	/* G */
	अणु0,0,0पूर्ण,	/* B */
	अणु0,0,0पूर्ण,	/* transparency */
	0,		/* standard pixel क्रमmat */
	FB_ACTIVATE_NOW,
	-1,-1,
	FB_ACCELF_TEXT,	/* accel flags */
	39721L,48L,16L,33L,10L,
	96L,2L,~0,	/* No sync info */
	FB_VMODE_NONINTERLACED,
पूर्ण;



/* --------------------------------------------------------------------- */
अटल व्योम update_crtc2(काष्ठा matrox_fb_info *minfo, अचिन्हित पूर्णांक pos)
अणु
	काष्ठा matroxfb_dh_fb_info *info = minfo->crtc2.info;

	/* Make sure that displays are compatible */
	अगर (info && (info->fbcon.var.bits_per_pixel == minfo->fbcon.var.bits_per_pixel)
		 && (info->fbcon.var.xres_भव == minfo->fbcon.var.xres_भव)
		 && (info->fbcon.var.green.length == minfo->fbcon.var.green.length)
		 ) अणु
		चयन (minfo->fbcon.var.bits_per_pixel) अणु
			हाल 16:
			हाल 32:
				pos = pos * 8;
				अगर (info->पूर्णांकerlaced) अणु
					mga_outl(0x3C2C, pos);
					mga_outl(0x3C28, pos + minfo->fbcon.var.xres_भव * minfo->fbcon.var.bits_per_pixel / 8);
				पूर्ण अन्यथा अणु
					mga_outl(0x3C28, pos);
				पूर्ण
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम matroxfb_crtc1_panpos(काष्ठा matrox_fb_info *minfo)
अणु
	अगर (minfo->crtc1.panpos >= 0) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक panpos;

		matroxfb_DAC_lock_irqsave(flags);
		panpos = minfo->crtc1.panpos;
		अगर (panpos >= 0) अणु
			अचिन्हित पूर्णांक extvga_reg;

			minfo->crtc1.panpos = -1; /* No update pending anymore */
			extvga_reg = mga_inb(M_EXTVGA_INDEX);
			mga_setr(M_EXTVGA_INDEX, 0x00, panpos);
			अगर (extvga_reg != 0x00) अणु
				mga_outb(M_EXTVGA_INDEX, extvga_reg);
			पूर्ण
		पूर्ण
		matroxfb_DAC_unlock_irqrestore(flags);
	पूर्ण
पूर्ण

अटल irqवापस_t matrox_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	u_पूर्णांक32_t status;
	पूर्णांक handled = 0;
	काष्ठा matrox_fb_info *minfo = dev_id;

	status = mga_inl(M_STATUS);

	अगर (status & 0x20) अणु
		mga_outl(M_ICLEAR, 0x20);
		minfo->crtc1.vsync.cnt++;
		matroxfb_crtc1_panpos(minfo);
		wake_up_पूर्णांकerruptible(&minfo->crtc1.vsync.रुको);
		handled = 1;
	पूर्ण
	अगर (status & 0x200) अणु
		mga_outl(M_ICLEAR, 0x200);
		minfo->crtc2.vsync.cnt++;
		wake_up_पूर्णांकerruptible(&minfo->crtc2.vsync.रुको);
		handled = 1;
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण

पूर्णांक matroxfb_enable_irq(काष्ठा matrox_fb_info *minfo, पूर्णांक reenable)
अणु
	u_पूर्णांक32_t bm;

	अगर (minfo->devflags.accelerator == FB_ACCEL_MATROX_MGAG400)
		bm = 0x220;
	अन्यथा
		bm = 0x020;

	अगर (!test_and_set_bit(0, &minfo->irq_flags)) अणु
		अगर (request_irq(minfo->pcidev->irq, matrox_irq,
				IRQF_SHARED, "matroxfb", minfo)) अणु
			clear_bit(0, &minfo->irq_flags);
			वापस -EINVAL;
		पूर्ण
		/* Clear any pending field पूर्णांकerrupts */
		mga_outl(M_ICLEAR, bm);
		mga_outl(M_IEN, mga_inl(M_IEN) | bm);
	पूर्ण अन्यथा अगर (reenable) अणु
		u_पूर्णांक32_t ien;

		ien = mga_inl(M_IEN);
		अगर ((ien & bm) != bm) अणु
			prपूर्णांकk(KERN_DEBUG "matroxfb: someone disabled IRQ [%08X]\n", ien);
			mga_outl(M_IEN, ien | bm);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम matroxfb_disable_irq(काष्ठा matrox_fb_info *minfo)
अणु
	अगर (test_and_clear_bit(0, &minfo->irq_flags)) अणु
		/* Flush pending pan-at-vbl request... */
		matroxfb_crtc1_panpos(minfo);
		अगर (minfo->devflags.accelerator == FB_ACCEL_MATROX_MGAG400)
			mga_outl(M_IEN, mga_inl(M_IEN) & ~0x220);
		अन्यथा
			mga_outl(M_IEN, mga_inl(M_IEN) & ~0x20);
		मुक्त_irq(minfo->pcidev->irq, minfo);
	पूर्ण
पूर्ण

पूर्णांक matroxfb_रुको_क्रम_sync(काष्ठा matrox_fb_info *minfo, u_पूर्णांक32_t crtc)
अणु
	काष्ठा matrox_vsync *vs;
	अचिन्हित पूर्णांक cnt;
	पूर्णांक ret;

	चयन (crtc) अणु
		हाल 0:
			vs = &minfo->crtc1.vsync;
			अवरोध;
		हाल 1:
			अगर (minfo->devflags.accelerator != FB_ACCEL_MATROX_MGAG400) अणु
				वापस -ENODEV;
			पूर्ण
			vs = &minfo->crtc2.vsync;
			अवरोध;
		शेष:
			वापस -ENODEV;
	पूर्ण
	ret = matroxfb_enable_irq(minfo, 0);
	अगर (ret) अणु
		वापस ret;
	पूर्ण

	cnt = vs->cnt;
	ret = रुको_event_पूर्णांकerruptible_समयout(vs->रुको, cnt != vs->cnt, HZ/10);
	अगर (ret < 0) अणु
		वापस ret;
	पूर्ण
	अगर (ret == 0) अणु
		matroxfb_enable_irq(minfo, 1);
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल व्योम matrox_pan_var(काष्ठा matrox_fb_info *minfo,
			   काष्ठा fb_var_screeninfo *var)
अणु
	अचिन्हित पूर्णांक pos;
	अचिन्हित लघु p0, p1, p2;
	अचिन्हित पूर्णांक p3;
	पूर्णांक vbl;
	अचिन्हित दीर्घ flags;

	CRITFLAGS

	DBG(__func__)

	अगर (minfo->dead)
		वापस;

	minfo->fbcon.var.xoffset = var->xoffset;
	minfo->fbcon.var.yoffset = var->yoffset;
	pos = (minfo->fbcon.var.yoffset * minfo->fbcon.var.xres_भव + minfo->fbcon.var.xoffset) * minfo->curr.final_bppShअगरt / 32;
	pos += minfo->curr.ydstorg.chunks;
	p0 = minfo->hw.CRTC[0x0D] = pos & 0xFF;
	p1 = minfo->hw.CRTC[0x0C] = (pos & 0xFF00) >> 8;
	p2 = minfo->hw.CRTCEXT[0] = (minfo->hw.CRTCEXT[0] & 0xB0) | ((pos >> 16) & 0x0F) | ((pos >> 14) & 0x40);
	p3 = minfo->hw.CRTCEXT[8] = pos >> 21;

	/* FB_ACTIVATE_VBL and we can acquire पूर्णांकerrupts? Honor FB_ACTIVATE_VBL then... */
	vbl = (var->activate & FB_ACTIVATE_VBL) && (matroxfb_enable_irq(minfo, 0) == 0);

	CRITBEGIN

	matroxfb_DAC_lock_irqsave(flags);
	mga_setr(M_CRTC_INDEX, 0x0D, p0);
	mga_setr(M_CRTC_INDEX, 0x0C, p1);
	अगर (minfo->devflags.support32MB)
		mga_setr(M_EXTVGA_INDEX, 0x08, p3);
	अगर (vbl) अणु
		minfo->crtc1.panpos = p2;
	पूर्ण अन्यथा अणु
		/* Abort any pending change */
		minfo->crtc1.panpos = -1;
		mga_setr(M_EXTVGA_INDEX, 0x00, p2);
	पूर्ण
	matroxfb_DAC_unlock_irqrestore(flags);

	update_crtc2(minfo, pos);

	CRITEND
पूर्ण

अटल व्योम matroxfb_हटाओ(काष्ठा matrox_fb_info *minfo, पूर्णांक dummy)
अणु
	/* Currently we are holding big kernel lock on all dead & usecount updates.
	 * Destroy everything after all users release it. Especially करो not unरेजिस्टर
	 * framebuffer and iounmap memory, neither fbmem nor fbcon-cfb* करोes not check
	 * क्रम device unplugged when in use.
	 * In future we should poपूर्णांक mmio.vbase & video.vbase somewhere where we can
	 * ग_लिखो data without causing too much damage...
	 */

	minfo->dead = 1;
	अगर (minfo->usecount) अणु
		/* destroy it later */
		वापस;
	पूर्ण
	matroxfb_unरेजिस्टर_device(minfo);
	unरेजिस्टर_framebuffer(&minfo->fbcon);
	matroxfb_g450_shutकरोwn(minfo);
	arch_phys_wc_del(minfo->wc_cookie);
	iounmap(minfo->mmio.vbase.vaddr);
	iounmap(minfo->video.vbase.vaddr);
	release_mem_region(minfo->video.base, minfo->video.len_maximum);
	release_mem_region(minfo->mmio.base, 16384);
	kमुक्त(minfo);
पूर्ण

	/*
	 * Open/Release the frame buffer device
	 */

अटल पूर्णांक matroxfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	DBG_LOOP(__func__)

	अगर (minfo->dead) अणु
		वापस -ENXIO;
	पूर्ण
	minfo->usecount++;
	अगर (user) अणु
		minfo->userusecount++;
	पूर्ण
	वापस(0);
पूर्ण

अटल पूर्णांक matroxfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	DBG_LOOP(__func__)

	अगर (user) अणु
		अगर (0 == --minfo->userusecount) अणु
			matroxfb_disable_irq(minfo);
		पूर्ण
	पूर्ण
	अगर (!(--minfo->usecount) && minfo->dead) अणु
		matroxfb_हटाओ(minfo, 0);
	पूर्ण
	वापस(0);
पूर्ण

अटल पूर्णांक matroxfb_pan_display(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info* info) अणु
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	DBG(__func__)

	matrox_pan_var(minfo, var);
	वापस 0;
पूर्ण

अटल पूर्णांक matroxfb_get_final_bppShअगरt(स्थिर काष्ठा matrox_fb_info *minfo,
				       पूर्णांक bpp)
अणु
	पूर्णांक bppshft2;

	DBG(__func__)

	bppshft2 = bpp;
	अगर (!bppshft2) अणु
		वापस 8;
	पूर्ण
	अगर (isInterleave(minfo))
		bppshft2 >>= 1;
	अगर (minfo->devflags.video64bits)
		bppshft2 >>= 1;
	वापस bppshft2;
पूर्ण

अटल पूर्णांक matroxfb_test_and_set_rounding(स्थिर काष्ठा matrox_fb_info *minfo,
					  पूर्णांक xres, पूर्णांक bpp)
अणु
	पूर्णांक over;
	पूर्णांक rounding;

	DBG(__func__)

	चयन (bpp) अणु
		हाल 0:		वापस xres;
		हाल 4:		rounding = 128;
				अवरोध;
		हाल 8:		rounding = 64;	/* करोc says 64; 32 is OK क्रम G400 */
				अवरोध;
		हाल 16:	rounding = 32;
				अवरोध;
		हाल 24:	rounding = 64;	/* करोc says 64; 32 is OK क्रम G400 */
				अवरोध;
		शेष:	rounding = 16;
				/* on G400, 16 really करोes not work */
				अगर (minfo->devflags.accelerator == FB_ACCEL_MATROX_MGAG400)
					rounding = 32;
				अवरोध;
	पूर्ण
	अगर (isInterleave(minfo)) अणु
		rounding *= 2;
	पूर्ण
	over = xres % rounding;
	अगर (over)
		xres += rounding-over;
	वापस xres;
पूर्ण

अटल पूर्णांक matroxfb_pitch_adjust(स्थिर काष्ठा matrox_fb_info *minfo, पूर्णांक xres,
				 पूर्णांक bpp)
अणु
	स्थिर पूर्णांक* width;
	पूर्णांक xres_new;

	DBG(__func__)

	अगर (!bpp) वापस xres;

	width = minfo->capable.vxres;

	अगर (minfo->devflags.precise_width) अणु
		जबतक (*width) अणु
			अगर ((*width >= xres) && (matroxfb_test_and_set_rounding(minfo, *width, bpp) == *width)) अणु
				अवरोध;
			पूर्ण
			width++;
		पूर्ण
		xres_new = *width;
	पूर्ण अन्यथा अणु
		xres_new = matroxfb_test_and_set_rounding(minfo, xres, bpp);
	पूर्ण
	वापस xres_new;
पूर्ण

अटल पूर्णांक matroxfb_get_cmap_len(काष्ठा fb_var_screeninfo *var) अणु

	DBG(__func__)

	चयन (var->bits_per_pixel) अणु
		हाल 4:
			वापस 16;	/* pseuकरोcolor... 16 entries HW palette */
		हाल 8:
			वापस 256;	/* pseuकरोcolor... 256 entries HW palette */
		हाल 16:
			वापस 16;	/* directcolor... 16 entries SW palette */
					/* Mystique: truecolor, 16 entries SW palette, HW palette hardwired पूर्णांकo 1:1 mapping */
		हाल 24:
			वापस 16;	/* directcolor... 16 entries SW palette */
					/* Mystique: truecolor, 16 entries SW palette, HW palette hardwired पूर्णांकo 1:1 mapping */
		हाल 32:
			वापस 16;	/* directcolor... 16 entries SW palette */
					/* Mystique: truecolor, 16 entries SW palette, HW palette hardwired पूर्णांकo 1:1 mapping */
	पूर्ण
	वापस 16;	/* वापस something reasonable... or panic()? */
पूर्ण

अटल पूर्णांक matroxfb_decode_var(स्थिर काष्ठा matrox_fb_info *minfo,
			       काष्ठा fb_var_screeninfo *var, पूर्णांक *visual,
			       पूर्णांक *video_cmap_len, अचिन्हित पूर्णांक* ydstorg)
अणु
	काष्ठा RGBT अणु
		अचिन्हित अक्षर bpp;
		काष्ठा अणु
			अचिन्हित अक्षर offset,
				      length;
		पूर्ण red,
		  green,
		  blue,
		  transp;
		चिन्हित अक्षर visual;
	पूर्ण;
	अटल स्थिर काष्ठा RGBT table[]= अणु
		अणु 8,अणु 0,8पूर्ण,अणु0,8पूर्ण,अणु0,8पूर्ण,अणु 0,0पूर्ण,MX_VISUAL_PSEUDOCOLORपूर्ण,
		अणु15,अणु10,5पूर्ण,अणु5,5पूर्ण,अणु0,5पूर्ण,अणु15,1पूर्ण,MX_VISUAL_सूचीECTCOLORपूर्ण,
		अणु16,अणु11,5पूर्ण,अणु5,6पूर्ण,अणु0,5पूर्ण,अणु 0,0पूर्ण,MX_VISUAL_सूचीECTCOLORपूर्ण,
		अणु24,अणु16,8पूर्ण,अणु8,8पूर्ण,अणु0,8पूर्ण,अणु 0,0पूर्ण,MX_VISUAL_सूचीECTCOLORपूर्ण,
		अणु32,अणु16,8पूर्ण,अणु8,8पूर्ण,अणु0,8पूर्ण,अणु24,8पूर्ण,MX_VISUAL_सूचीECTCOLORपूर्ण
	पूर्ण;
	काष्ठा RGBT स्थिर *rgbt;
	अचिन्हित पूर्णांक bpp = var->bits_per_pixel;
	अचिन्हित पूर्णांक vramlen;
	अचिन्हित पूर्णांक memlen;

	DBG(__func__)

	चयन (bpp) अणु
		हाल 4:	 अगर (!minfo->capable.cfb4) वापस -EINVAL;
			 अवरोध;
		हाल 8:	 अवरोध;
		हाल 16: अवरोध;
		हाल 24: अवरोध;
		हाल 32: अवरोध;
		शेष: वापस -EINVAL;
	पूर्ण
	*ydstorg = 0;
	vramlen = minfo->video.len_usable;
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;
	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;

	var->xres_भव = matroxfb_pitch_adjust(minfo, var->xres_भव, bpp);
	memlen = var->xres_भव * bpp * var->yres_भव / 8;
	अगर (memlen > vramlen) अणु
		var->yres_भव = vramlen * 8 / (var->xres_भव * bpp);
		memlen = var->xres_भव * bpp * var->yres_भव / 8;
	पूर्ण
	/* There is hardware bug that no line can cross 4MB boundary */
	/* give up क्रम CFB24, it is impossible to easy workaround it */
	/* क्रम other try to करो something */
	अगर (!minfo->capable.cross4MB && (memlen > 0x400000)) अणु
		अगर (bpp == 24) अणु
			/* sorry */
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक linelen;
			अचिन्हित पूर्णांक m1 = linelen = var->xres_भव * bpp / 8;
			अचिन्हित पूर्णांक m2 = PAGE_SIZE;	/* or 128 अगर you करो not need PAGE ALIGNED address */
			अचिन्हित पूर्णांक max_yres;

			जबतक (m1) अणु
				जबतक (m2 >= m1) m2 -= m1;
				swap(m1, m2);
			पूर्ण
			m2 = linelen * PAGE_SIZE / m2;
			*ydstorg = m2 = 0x400000 % m2;
			max_yres = (vramlen - m2) / linelen;
			अगर (var->yres_भव > max_yres)
				var->yres_भव = max_yres;
		पूर्ण
	पूर्ण
	/* YDSTLEN contains only चिन्हित 16bit value */
	अगर (var->yres_भव > 32767)
		var->yres_भव = 32767;
	/* we must round yres/xres करोwn, we alपढ़ोy rounded y/xres_भव up
	   अगर it was possible. We should वापस -EINVAL, but I disagree */
	अगर (var->yres_भव < var->yres)
		var->yres = var->yres_भव;
	अगर (var->xres_भव < var->xres)
		var->xres = var->xres_भव;
	अगर (var->xoffset + var->xres > var->xres_भव)
		var->xoffset = var->xres_भव - var->xres;
	अगर (var->yoffset + var->yres > var->yres_भव)
		var->yoffset = var->yres_भव - var->yres;

	अगर (bpp == 16 && var->green.length == 5) अणु
		bpp--; /* an artअगरicial value - 15 */
	पूर्ण

	क्रम (rgbt = table; rgbt->bpp < bpp; rgbt++);
#घोषणा	SETCLR(clr)\
	var->clr.offset = rgbt->clr.offset;\
	var->clr.length = rgbt->clr.length
	SETCLR(red);
	SETCLR(green);
	SETCLR(blue);
	SETCLR(transp);
#अघोषित	SETCLR
	*visual = rgbt->visual;

	अगर (bpp > 8)
		dprपूर्णांकk("matroxfb: truecolor: "
			"size=%d:%d:%d:%d, shift=%d:%d:%d:%d\n",
			var->transp.length, var->red.length, var->green.length, var->blue.length,
			var->transp.offset, var->red.offset, var->green.offset, var->blue.offset);

	*video_cmap_len = matroxfb_get_cmap_len(var);
	dprपूर्णांकk(KERN_INFO "requested %d*%d/%dbpp (%d*%d)\n", var->xres, var->yres, var->bits_per_pixel,
				var->xres_भव, var->yres_भव);
	वापस 0;
पूर्ण

अटल पूर्णांक matroxfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			      अचिन्हित blue, अचिन्हित transp,
			      काष्ठा fb_info *fb_info)
अणु
	काष्ठा matrox_fb_info* minfo = container_of(fb_info, काष्ठा matrox_fb_info, fbcon);

	DBG(__func__)

	/*
	 *  Set a single color रेजिस्टर. The values supplied are
	 *  alपढ़ोy rounded करोwn to the hardware's capabilities
	 *  (according to the entries in the `var' काष्ठाure). Return
	 *  != 0 क्रम invalid regno.
	 */

	अगर (regno >= minfo->curr.cmap_len)
		वापस 1;

	अगर (minfo->fbcon.var.grayscale) अणु
		/* gray = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण

	red = CNVT_TOHW(red, minfo->fbcon.var.red.length);
	green = CNVT_TOHW(green, minfo->fbcon.var.green.length);
	blue = CNVT_TOHW(blue, minfo->fbcon.var.blue.length);
	transp = CNVT_TOHW(transp, minfo->fbcon.var.transp.length);

	चयन (minfo->fbcon.var.bits_per_pixel) अणु
	हाल 4:
	हाल 8:
		mga_outb(M_DAC_REG, regno);
		mga_outb(M_DAC_VAL, red);
		mga_outb(M_DAC_VAL, green);
		mga_outb(M_DAC_VAL, blue);
		अवरोध;
	हाल 16:
		अगर (regno >= 16)
			अवरोध;
		अणु
			u_पूर्णांक16_t col =
				(red << minfo->fbcon.var.red.offset)     |
				(green << minfo->fbcon.var.green.offset) |
				(blue << minfo->fbcon.var.blue.offset)   |
				(transp << minfo->fbcon.var.transp.offset); /* क्रम 1:5:5:5 */
			minfo->cmap[regno] = col | (col << 16);
		पूर्ण
		अवरोध;
	हाल 24:
	हाल 32:
		अगर (regno >= 16)
			अवरोध;
		minfo->cmap[regno] =
			(red   << minfo->fbcon.var.red.offset)   |
			(green << minfo->fbcon.var.green.offset) |
			(blue  << minfo->fbcon.var.blue.offset)  |
			(transp << minfo->fbcon.var.transp.offset);	/* 8:8:8:8 */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम matroxfb_init_fix(काष्ठा matrox_fb_info *minfo)
अणु
	काष्ठा fb_fix_screeninfo *fix = &minfo->fbcon.fix;
	DBG(__func__)

	म_नकल(fix->id,"MATROX");

	fix->xpanstep = 8;	/* 8 क्रम 8bpp, 4 क्रम 16bpp, 2 क्रम 32bpp */
	fix->ypanstep = 1;
	fix->ywrapstep = 0;
	fix->mmio_start = minfo->mmio.base;
	fix->mmio_len = minfo->mmio.len;
	fix->accel = minfo->devflags.accelerator;
पूर्ण

अटल व्योम matroxfb_update_fix(काष्ठा matrox_fb_info *minfo)
अणु
	काष्ठा fb_fix_screeninfo *fix = &minfo->fbcon.fix;
	DBG(__func__)

	mutex_lock(&minfo->fbcon.mm_lock);
	fix->smem_start = minfo->video.base + minfo->curr.ydstorg.bytes;
	fix->smem_len = minfo->video.len_usable - minfo->curr.ydstorg.bytes;
	mutex_unlock(&minfo->fbcon.mm_lock);
पूर्ण

अटल पूर्णांक matroxfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	पूर्णांक err;
	पूर्णांक visual;
	पूर्णांक cmap_len;
	अचिन्हित पूर्णांक ydstorg;
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	अगर (minfo->dead) अणु
		वापस -ENXIO;
	पूर्ण
	अगर ((err = matroxfb_decode_var(minfo, var, &visual, &cmap_len, &ydstorg)) != 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक matroxfb_set_par(काष्ठा fb_info *info)
अणु
	पूर्णांक err;
	पूर्णांक visual;
	पूर्णांक cmap_len;
	अचिन्हित पूर्णांक ydstorg;
	काष्ठा fb_var_screeninfo *var;
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	DBG(__func__)

	अगर (minfo->dead) अणु
		वापस -ENXIO;
	पूर्ण

	var = &info->var;
	अगर ((err = matroxfb_decode_var(minfo, var, &visual, &cmap_len, &ydstorg)) != 0)
		वापस err;
	minfo->fbcon.screen_base = vaddr_va(minfo->video.vbase) + ydstorg;
	matroxfb_update_fix(minfo);
	minfo->fbcon.fix.visual = visual;
	minfo->fbcon.fix.type = FB_TYPE_PACKED_PIXELS;
	minfo->fbcon.fix.type_aux = 0;
	minfo->fbcon.fix.line_length = (var->xres_भव * var->bits_per_pixel) >> 3;
	अणु
		अचिन्हित पूर्णांक pos;

		minfo->curr.cmap_len = cmap_len;
		ydstorg += minfo->devflags.ydstorg;
		minfo->curr.ydstorg.bytes = ydstorg;
		minfo->curr.ydstorg.chunks = ydstorg >> (isInterleave(minfo) ? 3 : 2);
		अगर (var->bits_per_pixel == 4)
			minfo->curr.ydstorg.pixels = ydstorg;
		अन्यथा
			minfo->curr.ydstorg.pixels = (ydstorg * 8) / var->bits_per_pixel;
		minfo->curr.final_bppShअगरt = matroxfb_get_final_bppShअगरt(minfo, var->bits_per_pixel);
		अणु	काष्ठा my_timming mt;
			काष्ठा matrox_hw_state* hw;
			पूर्णांक out;

			matroxfb_var2my(var, &mt);
			mt.crtc = MATROXFB_SRC_CRTC1;
			/* CRTC1 delays */
			चयन (var->bits_per_pixel) अणु
				हाल  0:	mt.delay = 31 + 0; अवरोध;
				हाल 16:	mt.delay = 21 + 8; अवरोध;
				हाल 24:	mt.delay = 17 + 8; अवरोध;
				हाल 32:	mt.delay = 16 + 8; अवरोध;
				शेष:	mt.delay = 31 + 8; अवरोध;
			पूर्ण

			hw = &minfo->hw;

			करोwn_पढ़ो(&minfo->altout.lock);
			क्रम (out = 0; out < MATROXFB_MAX_OUTPUTS; out++) अणु
				अगर (minfo->outमाला_दो[out].src == MATROXFB_SRC_CRTC1 &&
				    minfo->outमाला_दो[out].output->compute) अणु
					minfo->outमाला_दो[out].output->compute(minfo->outमाला_दो[out].data, &mt);
				पूर्ण
			पूर्ण
			up_पढ़ो(&minfo->altout.lock);
			minfo->crtc1.pixघड़ी = mt.pixघड़ी;
			minfo->crtc1.mnp = mt.mnp;
			minfo->hw_चयन->init(minfo, &mt);
			pos = (var->yoffset * var->xres_भव + var->xoffset) * minfo->curr.final_bppShअगरt / 32;
			pos += minfo->curr.ydstorg.chunks;

			hw->CRTC[0x0D] = pos & 0xFF;
			hw->CRTC[0x0C] = (pos & 0xFF00) >> 8;
			hw->CRTCEXT[0] = (hw->CRTCEXT[0] & 0xF0) | ((pos >> 16) & 0x0F) | ((pos >> 14) & 0x40);
			hw->CRTCEXT[8] = pos >> 21;
			minfo->hw_चयन->restore(minfo);
			update_crtc2(minfo, pos);
			करोwn_पढ़ो(&minfo->altout.lock);
			क्रम (out = 0; out < MATROXFB_MAX_OUTPUTS; out++) अणु
				अगर (minfo->outमाला_दो[out].src == MATROXFB_SRC_CRTC1 &&
				    minfo->outमाला_दो[out].output->program) अणु
					minfo->outमाला_दो[out].output->program(minfo->outमाला_दो[out].data);
				पूर्ण
			पूर्ण
			क्रम (out = 0; out < MATROXFB_MAX_OUTPUTS; out++) अणु
				अगर (minfo->outमाला_दो[out].src == MATROXFB_SRC_CRTC1 &&
				    minfo->outमाला_दो[out].output->start) अणु
					minfo->outमाला_दो[out].output->start(minfo->outमाला_दो[out].data);
				पूर्ण
			पूर्ण
			up_पढ़ो(&minfo->altout.lock);
			matrox_cfbX_init(minfo);
		पूर्ण
	पूर्ण
	minfo->initialized = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक matroxfb_get_vblank(काष्ठा matrox_fb_info *minfo,
			       काष्ठा fb_vblank *vblank)
अणु
	अचिन्हित पूर्णांक sts1;

	matroxfb_enable_irq(minfo, 0);
	स_रखो(vblank, 0, माप(*vblank));
	vblank->flags = FB_VBLANK_HAVE_VCOUNT | FB_VBLANK_HAVE_VSYNC |
			FB_VBLANK_HAVE_VBLANK | FB_VBLANK_HAVE_HBLANK;
	sts1 = mga_inb(M_INSTS1);
	vblank->vcount = mga_inl(M_VCOUNT);
	/* BTW, on my PIII/450 with G400, पढ़ोing M_INSTS1
	   byte makes this call about 12% slower (1.70 vs. 2.05 us
	   per ioctl()) */
	अगर (sts1 & 1)
		vblank->flags |= FB_VBLANK_HBLANKING;
	अगर (sts1 & 8)
		vblank->flags |= FB_VBLANK_VSYNCING;
	अगर (vblank->vcount >= minfo->fbcon.var.yres)
		vblank->flags |= FB_VBLANK_VBLANKING;
	अगर (test_bit(0, &minfo->irq_flags)) अणु
		vblank->flags |= FB_VBLANK_HAVE_COUNT;
		/* Only one ग_लिखोr, aligned पूर्णांक value...
		   it should work without lock and without atomic_t */
		vblank->count = minfo->crtc1.vsync.cnt;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा matrox_altout panellink_output = अणु
	.name	 = "Panellink output",
पूर्ण;

अटल पूर्णांक matroxfb_ioctl(काष्ठा fb_info *info,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	DBG(__func__)

	अगर (minfo->dead) अणु
		वापस -ENXIO;
	पूर्ण

	चयन (cmd) अणु
		हाल FBIOGET_VBLANK:
			अणु
				काष्ठा fb_vblank vblank;
				पूर्णांक err;

				err = matroxfb_get_vblank(minfo, &vblank);
				अगर (err)
					वापस err;
				अगर (copy_to_user(argp, &vblank, माप(vblank)))
					वापस -EFAULT;
				वापस 0;
			पूर्ण
		हाल FBIO_WAITFORVSYNC:
			अणु
				u_पूर्णांक32_t crt;

				अगर (get_user(crt, (u_पूर्णांक32_t __user *)arg))
					वापस -EFAULT;

				वापस matroxfb_रुको_क्रम_sync(minfo, crt);
			पूर्ण
		हाल MATROXFB_SET_OUTPUT_MODE:
			अणु
				काष्ठा matroxioc_output_mode mom;
				काष्ठा matrox_altout *oproc;
				पूर्णांक val;

				अगर (copy_from_user(&mom, argp, माप(mom)))
					वापस -EFAULT;
				अगर (mom.output >= MATROXFB_MAX_OUTPUTS)
					वापस -ENXIO;
				करोwn_पढ़ो(&minfo->altout.lock);
				oproc = minfo->outमाला_दो[mom.output].output;
				अगर (!oproc) अणु
					val = -ENXIO;
				पूर्ण अन्यथा अगर (!oproc->verअगरymode) अणु
					अगर (mom.mode == MATROXFB_OUTPUT_MODE_MONITOR) अणु
						val = 0;
					पूर्ण अन्यथा अणु
						val = -EINVAL;
					पूर्ण
				पूर्ण अन्यथा अणु
					val = oproc->verअगरymode(minfo->outमाला_दो[mom.output].data, mom.mode);
				पूर्ण
				अगर (!val) अणु
					अगर (minfo->outमाला_दो[mom.output].mode != mom.mode) अणु
						minfo->outमाला_दो[mom.output].mode = mom.mode;
						val = 1;
					पूर्ण
				पूर्ण
				up_पढ़ो(&minfo->altout.lock);
				अगर (val != 1)
					वापस val;
				चयन (minfo->outमाला_दो[mom.output].src) अणु
					हाल MATROXFB_SRC_CRTC1:
						matroxfb_set_par(info);
						अवरोध;
					हाल MATROXFB_SRC_CRTC2:
						अणु
							काष्ठा matroxfb_dh_fb_info* crtc2;

							करोwn_पढ़ो(&minfo->crtc2.lock);
							crtc2 = minfo->crtc2.info;
							अगर (crtc2)
								crtc2->fbcon.fbops->fb_set_par(&crtc2->fbcon);
							up_पढ़ो(&minfo->crtc2.lock);
						पूर्ण
						अवरोध;
				पूर्ण
				वापस 0;
			पूर्ण
		हाल MATROXFB_GET_OUTPUT_MODE:
			अणु
				काष्ठा matroxioc_output_mode mom;
				काष्ठा matrox_altout *oproc;
				पूर्णांक val;

				अगर (copy_from_user(&mom, argp, माप(mom)))
					वापस -EFAULT;
				अगर (mom.output >= MATROXFB_MAX_OUTPUTS)
					वापस -ENXIO;
				करोwn_पढ़ो(&minfo->altout.lock);
				oproc = minfo->outमाला_दो[mom.output].output;
				अगर (!oproc) अणु
					val = -ENXIO;
				पूर्ण अन्यथा अणु
					mom.mode = minfo->outमाला_दो[mom.output].mode;
					val = 0;
				पूर्ण
				up_पढ़ो(&minfo->altout.lock);
				अगर (val)
					वापस val;
				अगर (copy_to_user(argp, &mom, माप(mom)))
					वापस -EFAULT;
				वापस 0;
			पूर्ण
		हाल MATROXFB_SET_OUTPUT_CONNECTION:
			अणु
				u_पूर्णांक32_t पंचांगp;
				पूर्णांक i;
				पूर्णांक changes;

				अगर (copy_from_user(&पंचांगp, argp, माप(पंचांगp)))
					वापस -EFAULT;
				क्रम (i = 0; i < 32; i++) अणु
					अगर (पंचांगp & (1 << i)) अणु
						अगर (i >= MATROXFB_MAX_OUTPUTS)
							वापस -ENXIO;
						अगर (!minfo->outमाला_दो[i].output)
							वापस -ENXIO;
						चयन (minfo->outमाला_दो[i].src) अणु
							हाल MATROXFB_SRC_NONE:
							हाल MATROXFB_SRC_CRTC1:
								अवरोध;
							शेष:
								वापस -EBUSY;
						पूर्ण
					पूर्ण
				पूर्ण
				अगर (minfo->devflags.panellink) अणु
					अगर (पंचांगp & MATROXFB_OUTPUT_CONN_DFP) अणु
						अगर (पंचांगp & MATROXFB_OUTPUT_CONN_SECONDARY)
							वापस -EINVAL;
						क्रम (i = 0; i < MATROXFB_MAX_OUTPUTS; i++) अणु
							अगर (minfo->outमाला_दो[i].src == MATROXFB_SRC_CRTC2) अणु
								वापस -EBUSY;
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण
				changes = 0;
				क्रम (i = 0; i < MATROXFB_MAX_OUTPUTS; i++) अणु
					अगर (पंचांगp & (1 << i)) अणु
						अगर (minfo->outमाला_दो[i].src != MATROXFB_SRC_CRTC1) अणु
							changes = 1;
							minfo->outमाला_दो[i].src = MATROXFB_SRC_CRTC1;
						पूर्ण
					पूर्ण अन्यथा अगर (minfo->outमाला_दो[i].src == MATROXFB_SRC_CRTC1) अणु
						changes = 1;
						minfo->outमाला_दो[i].src = MATROXFB_SRC_NONE;
					पूर्ण
				पूर्ण
				अगर (!changes)
					वापस 0;
				matroxfb_set_par(info);
				वापस 0;
			पूर्ण
		हाल MATROXFB_GET_OUTPUT_CONNECTION:
			अणु
				u_पूर्णांक32_t conn = 0;
				पूर्णांक i;

				क्रम (i = 0; i < MATROXFB_MAX_OUTPUTS; i++) अणु
					अगर (minfo->outमाला_दो[i].src == MATROXFB_SRC_CRTC1) अणु
						conn |= 1 << i;
					पूर्ण
				पूर्ण
				अगर (put_user(conn, (u_पूर्णांक32_t __user *)arg))
					वापस -EFAULT;
				वापस 0;
			पूर्ण
		हाल MATROXFB_GET_AVAILABLE_OUTPUTS:
			अणु
				u_पूर्णांक32_t conn = 0;
				पूर्णांक i;

				क्रम (i = 0; i < MATROXFB_MAX_OUTPUTS; i++) अणु
					अगर (minfo->outमाला_दो[i].output) अणु
						चयन (minfo->outमाला_दो[i].src) अणु
							हाल MATROXFB_SRC_NONE:
							हाल MATROXFB_SRC_CRTC1:
								conn |= 1 << i;
								अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
				अगर (minfo->devflags.panellink) अणु
					अगर (conn & MATROXFB_OUTPUT_CONN_DFP)
						conn &= ~MATROXFB_OUTPUT_CONN_SECONDARY;
					अगर (conn & MATROXFB_OUTPUT_CONN_SECONDARY)
						conn &= ~MATROXFB_OUTPUT_CONN_DFP;
				पूर्ण
				अगर (put_user(conn, (u_पूर्णांक32_t __user *)arg))
					वापस -EFAULT;
				वापस 0;
			पूर्ण
		हाल MATROXFB_GET_ALL_OUTPUTS:
			अणु
				u_पूर्णांक32_t conn = 0;
				पूर्णांक i;

				क्रम (i = 0; i < MATROXFB_MAX_OUTPUTS; i++) अणु
					अगर (minfo->outमाला_दो[i].output) अणु
						conn |= 1 << i;
					पूर्ण
				पूर्ण
				अगर (put_user(conn, (u_पूर्णांक32_t __user *)arg))
					वापस -EFAULT;
				वापस 0;
			पूर्ण
		हाल VIDIOC_QUERYCAP:
			अणु
				काष्ठा v4l2_capability r;

				स_रखो(&r, 0, माप(r));
				म_नकल(r.driver, "matroxfb");
				म_नकल(r.card, "Matrox");
				प्र_लिखो(r.bus_info, "PCI:%s", pci_name(minfo->pcidev));
				r.version = KERNEL_VERSION(1,0,0);
				r.capabilities = V4L2_CAP_VIDEO_OUTPUT;
				अगर (copy_to_user(argp, &r, माप(r)))
					वापस -EFAULT;
				वापस 0;

			पूर्ण
		हाल VIDIOC_QUERYCTRL:
			अणु
				काष्ठा v4l2_queryctrl qctrl;
				पूर्णांक err;

				अगर (copy_from_user(&qctrl, argp, माप(qctrl)))
					वापस -EFAULT;

				करोwn_पढ़ो(&minfo->altout.lock);
				अगर (!minfo->outमाला_दो[1].output) अणु
					err = -ENXIO;
				पूर्ण अन्यथा अगर (minfo->outमाला_दो[1].output->getqueryctrl) अणु
					err = minfo->outमाला_दो[1].output->getqueryctrl(minfo->outमाला_दो[1].data, &qctrl);
				पूर्ण अन्यथा अणु
					err = -EINVAL;
				पूर्ण
				up_पढ़ो(&minfo->altout.lock);
				अगर (err >= 0 &&
				    copy_to_user(argp, &qctrl, माप(qctrl)))
					वापस -EFAULT;
				वापस err;
			पूर्ण
		हाल VIDIOC_G_CTRL:
			अणु
				काष्ठा v4l2_control ctrl;
				पूर्णांक err;

				अगर (copy_from_user(&ctrl, argp, माप(ctrl)))
					वापस -EFAULT;

				करोwn_पढ़ो(&minfo->altout.lock);
				अगर (!minfo->outमाला_दो[1].output) अणु
					err = -ENXIO;
				पूर्ण अन्यथा अगर (minfo->outमाला_दो[1].output->अ_लोtrl) अणु
					err = minfo->outमाला_दो[1].output->अ_लोtrl(minfo->outमाला_दो[1].data, &ctrl);
				पूर्ण अन्यथा अणु
					err = -EINVAL;
				पूर्ण
				up_पढ़ो(&minfo->altout.lock);
				अगर (err >= 0 &&
				    copy_to_user(argp, &ctrl, माप(ctrl)))
					वापस -EFAULT;
				वापस err;
			पूर्ण
		हाल VIDIOC_S_CTRL:
			अणु
				काष्ठा v4l2_control ctrl;
				पूर्णांक err;

				अगर (copy_from_user(&ctrl, argp, माप(ctrl)))
					वापस -EFAULT;

				करोwn_पढ़ो(&minfo->altout.lock);
				अगर (!minfo->outमाला_दो[1].output) अणु
					err = -ENXIO;
				पूर्ण अन्यथा अगर (minfo->outमाला_दो[1].output->setctrl) अणु
					err = minfo->outमाला_दो[1].output->setctrl(minfo->outमाला_दो[1].data, &ctrl);
				पूर्ण अन्यथा अणु
					err = -EINVAL;
				पूर्ण
				up_पढ़ो(&minfo->altout.lock);
				वापस err;
			पूर्ण
	पूर्ण
	वापस -ENOTTY;
पूर्ण

/* 0 unblank, 1 blank, 2 no vsync, 3 no hsync, 4 off */

अटल पूर्णांक matroxfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	पूर्णांक seq;
	पूर्णांक crtc;
	CRITFLAGS
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	DBG(__func__)

	अगर (minfo->dead)
		वापस 1;

	चयन (blank) अणु
	हाल FB_BLANK_NORMAL:  seq = 0x20; crtc = 0x00; अवरोध; /* works ??? */
	हाल FB_BLANK_VSYNC_SUSPEND:  seq = 0x20; crtc = 0x10; अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:  seq = 0x20; crtc = 0x20; अवरोध;
	हाल FB_BLANK_POWERDOWN:  seq = 0x20; crtc = 0x30; अवरोध;
	शेष: seq = 0x00; crtc = 0x00; अवरोध;
	पूर्ण

	CRITBEGIN

	mga_outb(M_SEQ_INDEX, 1);
	mga_outb(M_SEQ_DATA, (mga_inb(M_SEQ_DATA) & ~0x20) | seq);
	mga_outb(M_EXTVGA_INDEX, 1);
	mga_outb(M_EXTVGA_DATA, (mga_inb(M_EXTVGA_DATA) & ~0x30) | crtc);

	CRITEND
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops matroxfb_ops = अणु
	.owner =	THIS_MODULE,
	.fb_खोलो =	matroxfb_खोलो,
	.fb_release =	matroxfb_release,
	.fb_check_var =	matroxfb_check_var,
	.fb_set_par =	matroxfb_set_par,
	.fb_setcolreg =	matroxfb_setcolreg,
	.fb_pan_display =matroxfb_pan_display,
	.fb_blank =	matroxfb_blank,
	.fb_ioctl =	matroxfb_ioctl,
/*	.fb_fillrect =	<set by matrox_cfbX_init>, */
/*	.fb_copyarea =	<set by matrox_cfbX_init>, */
/*	.fb_imageblit =	<set by matrox_cfbX_init>, */
/*	.fb_cursor =	<set by matrox_cfbX_init>, */
पूर्ण;

#घोषणा RSDepth(X)	(((X) >> 8) & 0x0F)
#घोषणा RS8bpp		0x1
#घोषणा RS15bpp		0x2
#घोषणा RS16bpp		0x3
#घोषणा RS32bpp		0x4
#घोषणा RS4bpp		0x5
#घोषणा RS24bpp		0x6
#घोषणा RSText		0x7
#घोषणा RSText8		0x8
/* 9-F */
अटल काष्ठा अणु काष्ठा fb_bitfield red, green, blue, transp; पूर्णांक bits_per_pixel; पूर्ण colors[] = अणु
	अणु अणु  0, 8, 0पूर्ण, अणु 0, 8, 0पूर्ण, अणु 0, 8, 0पूर्ण, अणु  0, 0, 0पूर्ण,  8 पूर्ण,
	अणु अणु 10, 5, 0पूर्ण, अणु 5, 5, 0पूर्ण, अणु 0, 5, 0पूर्ण, अणु 15, 1, 0पूर्ण, 16 पूर्ण,
	अणु अणु 11, 5, 0पूर्ण, अणु 5, 6, 0पूर्ण, अणु 0, 5, 0पूर्ण, अणु  0, 0, 0पूर्ण, 16 पूर्ण,
	अणु अणु 16, 8, 0पूर्ण, अणु 8, 8, 0पूर्ण, अणु 0, 8, 0पूर्ण, अणु 24, 8, 0पूर्ण, 32 पूर्ण,
	अणु अणु  0, 8, 0पूर्ण, अणु 0, 8, 0पूर्ण, अणु 0, 8, 0पूर्ण, अणु  0, 0, 0पूर्ण,  4 पूर्ण,
	अणु अणु 16, 8, 0पूर्ण, अणु 8, 8, 0पूर्ण, अणु 0, 8, 0पूर्ण, अणु  0, 0, 0पूर्ण, 24 पूर्ण,
	अणु अणु  0, 6, 0पूर्ण, अणु 0, 6, 0पूर्ण, अणु 0, 6, 0पूर्ण, अणु  0, 0, 0पूर्ण,  0 पूर्ण,	/* texपंचांगode with (शेष) VGA8x16 */
	अणु अणु  0, 6, 0पूर्ण, अणु 0, 6, 0पूर्ण, अणु 0, 6, 0पूर्ण, अणु  0, 0, 0पूर्ण,  0 पूर्ण,	/* texपंचांगode hardwired to VGA8x8 */
पूर्ण;

/* initialized by setup, see explanation at end of file (search क्रम MODULE_PARM_DESC) */
अटल अचिन्हित पूर्णांक mem;		/* "matroxfb:mem:xxxxxM" */
अटल पूर्णांक option_precise_width = 1;	/* cannot be changed, option_precise_width==0 must imply noaccel */
अटल पूर्णांक inv24;			/* "matroxfb:inv24" */
अटल पूर्णांक cross4MB = -1;		/* "matroxfb:cross4MB" */
अटल पूर्णांक disabled;			/* "matroxfb:disabled" */
अटल पूर्णांक noaccel;			/* "matroxfb:noaccel" */
अटल पूर्णांक nopan;			/* "matroxfb:nopan" */
अटल पूर्णांक no_pci_retry;		/* "matroxfb:nopciretry" */
अटल पूर्णांक novga;			/* "matroxfb:novga" */
अटल पूर्णांक nobios;			/* "matroxfb:nobios" */
अटल पूर्णांक noinit = 1;			/* "matroxfb:init" */
अटल पूर्णांक inverse;			/* "matroxfb:inverse" */
अटल पूर्णांक sgram;			/* "matroxfb:sgram" */
अटल पूर्णांक mtrr = 1;			/* "matroxfb:nomtrr" */
अटल पूर्णांक grayscale;			/* "matroxfb:grayscale" */
अटल पूर्णांक dev = -1;			/* "matroxfb:dev:xxxxx" */
अटल अचिन्हित पूर्णांक vesa = ~0;		/* "matroxfb:vesa:xxxxx" */
अटल पूर्णांक depth = -1;			/* "matroxfb:depth:xxxxx" */
अटल अचिन्हित पूर्णांक xres;		/* "matroxfb:xres:xxxxx" */
अटल अचिन्हित पूर्णांक yres;		/* "matroxfb:yres:xxxxx" */
अटल अचिन्हित पूर्णांक upper = ~0;		/* "matroxfb:upper:xxxxx" */
अटल अचिन्हित पूर्णांक lower = ~0;		/* "matroxfb:lower:xxxxx" */
अटल अचिन्हित पूर्णांक vslen;		/* "matroxfb:vslen:xxxxx" */
अटल अचिन्हित पूर्णांक left = ~0;		/* "matroxfb:left:xxxxx" */
अटल अचिन्हित पूर्णांक right = ~0;		/* "matroxfb:right:xxxxx" */
अटल अचिन्हित पूर्णांक hslen;		/* "matroxfb:hslen:xxxxx" */
अटल अचिन्हित पूर्णांक pixघड़ी;		/* "matroxfb:pixclock:xxxxx" */
अटल पूर्णांक sync = -1;			/* "matroxfb:sync:xxxxx" */
अटल अचिन्हित पूर्णांक fv;			/* "matroxfb:fv:xxxxx" */
अटल अचिन्हित पूर्णांक fh;			/* "matroxfb:fh:xxxxxk" */
अटल अचिन्हित पूर्णांक maxclk;		/* "matroxfb:maxclk:xxxxM" */
अटल पूर्णांक dfp;				/* "matroxfb:dfp */
अटल पूर्णांक dfp_type = -1;		/* "matroxfb:dfp:xxx */
अटल पूर्णांक memtype = -1;		/* "matroxfb:memtype:xxx" */
अटल अक्षर outमाला_दो[8];			/* "matroxfb:outputs:xxx" */

#अगर_अघोषित MODULE
अटल अक्षर videomode[64];		/* "matroxfb:mode:xxxxx" or "matroxfb:xxxxx" */
#पूर्ण_अगर

अटल पूर्णांक matroxfb_geपंचांगemory(काष्ठा matrox_fb_info *minfo,
			      अचिन्हित पूर्णांक maxSize, अचिन्हित पूर्णांक *realSize)
अणु
	vaddr_t vm;
	अचिन्हित पूर्णांक offs;
	अचिन्हित पूर्णांक offs2;
	अचिन्हित अक्षर orig;
	अचिन्हित अक्षर bytes[32];
	अचिन्हित अक्षर* पंचांगp;

	DBG(__func__)

	vm = minfo->video.vbase;
	maxSize &= ~0x1FFFFF;	/* must be X*2MB (really it must be 2 or X*4MB) */
	/* at least 2MB */
	अगर (maxSize < 0x0200000) वापस 0;
	अगर (maxSize > 0x2000000) maxSize = 0x2000000;

	mga_outb(M_EXTVGA_INDEX, 0x03);
	orig = mga_inb(M_EXTVGA_DATA);
	mga_outb(M_EXTVGA_DATA, orig | 0x80);

	पंचांगp = bytes;
	क्रम (offs = 0x100000; offs < maxSize; offs += 0x200000)
		*पंचांगp++ = mga_पढ़ोb(vm, offs);
	क्रम (offs = 0x100000; offs < maxSize; offs += 0x200000)
		mga_ग_लिखोb(vm, offs, 0x02);
	mga_outb(M_CACHEFLUSH, 0x00);
	क्रम (offs = 0x100000; offs < maxSize; offs += 0x200000) अणु
		अगर (mga_पढ़ोb(vm, offs) != 0x02)
			अवरोध;
		mga_ग_लिखोb(vm, offs, mga_पढ़ोb(vm, offs) - 0x02);
		अगर (mga_पढ़ोb(vm, offs))
			अवरोध;
	पूर्ण
	पंचांगp = bytes;
	क्रम (offs2 = 0x100000; offs2 < maxSize; offs2 += 0x200000)
		mga_ग_लिखोb(vm, offs2, *पंचांगp++);

	mga_outb(M_EXTVGA_INDEX, 0x03);
	mga_outb(M_EXTVGA_DATA, orig);

	*realSize = offs - 0x100000;
#अगर_घोषित CONFIG_FB_MATROX_MILLENIUM
	minfo->पूर्णांकerleave = !(!isMillenium(minfo) || ((offs - 0x100000) & 0x3FFFFF));
#पूर्ण_अगर
	वापस 1;
पूर्ण

काष्ठा video_board अणु
	पूर्णांक maxvram;
	पूर्णांक maxdisplayable;
	पूर्णांक accelID;
	काष्ठा matrox_चयन* lowlevel;
		 पूर्ण;
#अगर_घोषित CONFIG_FB_MATROX_MILLENIUM
अटल काष्ठा video_board vbMillennium = अणु
	.maxvram = 0x0800000,
	.maxdisplayable = 0x0800000,
	.accelID = FB_ACCEL_MATROX_MGA2064W,
	.lowlevel = &matrox_millennium
पूर्ण;

अटल काष्ठा video_board vbMillennium2 = अणु
	.maxvram = 0x1000000,
	.maxdisplayable = 0x0800000,
	.accelID = FB_ACCEL_MATROX_MGA2164W,
	.lowlevel = &matrox_millennium
पूर्ण;

अटल काष्ठा video_board vbMillennium2A = अणु
	.maxvram = 0x1000000,
	.maxdisplayable = 0x0800000,
	.accelID = FB_ACCEL_MATROX_MGA2164W_AGP,
	.lowlevel = &matrox_millennium
पूर्ण;
#पूर्ण_अगर	/* CONFIG_FB_MATROX_MILLENIUM */
#अगर_घोषित CONFIG_FB_MATROX_MYSTIQUE
अटल काष्ठा video_board vbMystique = अणु
	.maxvram = 0x0800000,
	.maxdisplayable = 0x0800000,
	.accelID = FB_ACCEL_MATROX_MGA1064SG,
	.lowlevel = &matrox_mystique
पूर्ण;
#पूर्ण_अगर	/* CONFIG_FB_MATROX_MYSTIQUE */
#अगर_घोषित CONFIG_FB_MATROX_G
अटल काष्ठा video_board vbG100 = अणु
	.maxvram = 0x0800000,
	.maxdisplayable = 0x0800000,
	.accelID = FB_ACCEL_MATROX_MGAG100,
	.lowlevel = &matrox_G100
पूर्ण;

अटल काष्ठा video_board vbG200 = अणु
	.maxvram = 0x1000000,
	.maxdisplayable = 0x1000000,
	.accelID = FB_ACCEL_MATROX_MGAG200,
	.lowlevel = &matrox_G100
पूर्ण;
अटल काष्ठा video_board vbG200eW = अणु
	.maxvram = 0x800000,
	.maxdisplayable = 0x800000,
	.accelID = FB_ACCEL_MATROX_MGAG200,
	.lowlevel = &matrox_G100
पूर्ण;
/* from करोc it looks like that accelerator can draw only to low 16MB :-( Direct accesses & displaying are OK क्रम
   whole 32MB */
अटल काष्ठा video_board vbG400 = अणु
	.maxvram = 0x2000000,
	.maxdisplayable = 0x1000000,
	.accelID = FB_ACCEL_MATROX_MGAG400,
	.lowlevel = &matrox_G100
पूर्ण;
#पूर्ण_अगर

#घोषणा DEVF_VIDEO64BIT		0x0001
#घोषणा	DEVF_SWAPS		0x0002
#घोषणा DEVF_SRCORG		0x0004
#घोषणा DEVF_DUALHEAD		0x0008
#घोषणा DEVF_CROSS4MB		0x0010
#घोषणा DEVF_TEXT4B		0x0020
/* #घोषणा DEVF_recycled	0x0040	*/
/* #घोषणा DEVF_recycled	0x0080	*/
#घोषणा DEVF_SUPPORT32MB	0x0100
#घोषणा DEVF_ANY_VXRES		0x0200
#घोषणा DEVF_TEXT16B		0x0400
#घोषणा DEVF_CRTC2		0x0800
#घोषणा DEVF_MAVEN_CAPABLE	0x1000
#घोषणा DEVF_PANELLINK_CAPABLE	0x2000
#घोषणा DEVF_G450DAC		0x4000

#घोषणा DEVF_GCORE	(DEVF_VIDEO64BIT | DEVF_SWAPS | DEVF_CROSS4MB)
#घोषणा DEVF_G2CORE	(DEVF_GCORE | DEVF_ANY_VXRES | DEVF_MAVEN_CAPABLE | DEVF_PANELLINK_CAPABLE | DEVF_SRCORG | DEVF_DUALHEAD)
#घोषणा DEVF_G100	(DEVF_GCORE) /* no करोc, no vxres... */
#घोषणा DEVF_G200	(DEVF_G2CORE)
#घोषणा DEVF_G400	(DEVF_G2CORE | DEVF_SUPPORT32MB | DEVF_TEXT16B | DEVF_CRTC2)
/* अगर you'll find how to drive DFP... */
#घोषणा DEVF_G450	(DEVF_GCORE | DEVF_ANY_VXRES | DEVF_SUPPORT32MB | DEVF_TEXT16B | DEVF_CRTC2 | DEVF_G450DAC | DEVF_SRCORG | DEVF_DUALHEAD)
#घोषणा DEVF_G550	(DEVF_G450)

अटल काष्ठा board अणु
	अचिन्हित लघु venकरोr, device, rev, svid, sid;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक maxclk;
	क्रमागत mga_chip chip;
	काष्ठा video_board* base;
	स्थिर अक्षर* name;
		पूर्ण dev_list[] = अणु
#अगर_घोषित CONFIG_FB_MATROX_MILLENIUM
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MIL,	0xFF,
		0,			0,
		DEVF_TEXT4B,
		230000,
		MGA_2064,
		&vbMillennium,
		"Millennium (PCI)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MIL_2,	0xFF,
		0,			0,
		DEVF_SWAPS,
		220000,
		MGA_2164,
		&vbMillennium2,
		"Millennium II (PCI)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MIL_2_AGP,	0xFF,
		0,			0,
		DEVF_SWAPS,
		250000,
		MGA_2164,
		&vbMillennium2A,
		"Millennium II (AGP)"पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_MATROX_MYSTIQUE
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MYS,	0x02,
		0,			0,
		DEVF_VIDEO64BIT | DEVF_CROSS4MB,
		180000,
		MGA_1064,
		&vbMystique,
		"Mystique (PCI)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MYS,	0xFF,
		0,			0,
		DEVF_VIDEO64BIT | DEVF_SWAPS | DEVF_CROSS4MB,
		220000,
		MGA_1164,
		&vbMystique,
		"Mystique 220 (PCI)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MYS_AGP,	0x02,
		0,			0,
		DEVF_VIDEO64BIT | DEVF_CROSS4MB,
		180000,
		MGA_1064,
		&vbMystique,
		"Mystique (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MYS_AGP,	0xFF,
		0,			0,
		DEVF_VIDEO64BIT | DEVF_SWAPS | DEVF_CROSS4MB,
		220000,
		MGA_1164,
		&vbMystique,
		"Mystique 220 (AGP)"पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_MATROX_G
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G100_MM,	0xFF,
		0,			0,
		DEVF_G100,
		230000,
		MGA_G100,
		&vbG100,
		"MGA-G100 (PCI)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G100_AGP,	0xFF,
		0,			0,
		DEVF_G100,
		230000,
		MGA_G100,
		&vbG100,
		"MGA-G100 (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G200_PCI,	0xFF,
		0,			0,
		DEVF_G200,
		250000,
		MGA_G200,
		&vbG200,
		"MGA-G200 (PCI)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	0x0532,	0xFF,
		0,			0,
		DEVF_G200,
		250000,
		MGA_G200,
		&vbG200eW,
		"MGA-G200eW (PCI)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G200_AGP,	0xFF,
		PCI_SS_VENDOR_ID_MATROX,	PCI_SS_ID_MATROX_GENERIC,
		DEVF_G200,
		220000,
		MGA_G200,
		&vbG200,
		"MGA-G200 (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G200_AGP,	0xFF,
		PCI_SS_VENDOR_ID_MATROX,	PCI_SS_ID_MATROX_MYSTIQUE_G200_AGP,
		DEVF_G200,
		230000,
		MGA_G200,
		&vbG200,
		"Mystique G200 (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G200_AGP,	0xFF,
		PCI_SS_VENDOR_ID_MATROX,	PCI_SS_ID_MATROX_MILLENIUM_G200_AGP,
		DEVF_G200,
		250000,
		MGA_G200,
		&vbG200,
		"Millennium G200 (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G200_AGP,	0xFF,
		PCI_SS_VENDOR_ID_MATROX,	PCI_SS_ID_MATROX_MARVEL_G200_AGP,
		DEVF_G200,
		230000,
		MGA_G200,
		&vbG200,
		"Marvel G200 (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G200_AGP,	0xFF,
		PCI_SS_VENDOR_ID_SIEMENS_NIXDORF,	PCI_SS_ID_SIEMENS_MGA_G200_AGP,
		DEVF_G200,
		230000,
		MGA_G200,
		&vbG200,
		"MGA-G200 (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G200_AGP,	0xFF,
		0,			0,
		DEVF_G200,
		230000,
		MGA_G200,
		&vbG200,
		"G200 (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G400,	0x80,
		PCI_SS_VENDOR_ID_MATROX,	PCI_SS_ID_MATROX_MILLENNIUM_G400_MAX_AGP,
		DEVF_G400,
		360000,
		MGA_G400,
		&vbG400,
		"Millennium G400 MAX (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G400,	0x80,
		0,			0,
		DEVF_G400,
		300000,
		MGA_G400,
		&vbG400,
		"G400 (AGP)"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G400,	0xFF,
		0,			0,
		DEVF_G450,
		360000,
		MGA_G450,
		&vbG400,
		"G450"पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G550,	0xFF,
		0,			0,
		DEVF_G550,
		360000,
		MGA_G550,
		&vbG400,
		"G550"पूर्ण,
#पूर्ण_अगर
	अणु0,			0,				0xFF,
		0,			0,
		0,
		0,
		0,
		शून्य,
		शून्यपूर्णपूर्ण;

#अगर_अघोषित MODULE
अटल स्थिर काष्ठा fb_videomode शेषmode = अणु
	/* 640x480 @ 60Hz, 31.5 kHz */
	शून्य, 60, 640, 480, 39721, 40, 24, 32, 11, 96, 2,
	0, FB_VMODE_NONINTERLACED
पूर्ण;

अटल पूर्णांक hotplug = 0;
#पूर्ण_अगर /* !MODULE */

अटल व्योम setDefaultOutमाला_दो(काष्ठा matrox_fb_info *minfo)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर अक्षर* ptr;

	minfo->outमाला_दो[0].शेष_src = MATROXFB_SRC_CRTC1;
	अगर (minfo->devflags.g450dac) अणु
		minfo->outमाला_दो[1].शेष_src = MATROXFB_SRC_CRTC1;
		minfo->outमाला_दो[2].शेष_src = MATROXFB_SRC_CRTC1;
	पूर्ण अन्यथा अगर (dfp) अणु
		minfo->outमाला_दो[2].शेष_src = MATROXFB_SRC_CRTC1;
	पूर्ण
	ptr = outमाला_दो;
	क्रम (i = 0; i < MATROXFB_MAX_OUTPUTS; i++) अणु
		अक्षर c = *ptr++;

		अगर (c == 0) अणु
			अवरोध;
		पूर्ण
		अगर (c == '0') अणु
			minfo->outमाला_दो[i].शेष_src = MATROXFB_SRC_NONE;
		पूर्ण अन्यथा अगर (c == '1') अणु
			minfo->outमाला_दो[i].शेष_src = MATROXFB_SRC_CRTC1;
		पूर्ण अन्यथा अगर (c == '2' && minfo->devflags.crtc2) अणु
			minfo->outमाला_दो[i].शेष_src = MATROXFB_SRC_CRTC2;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "matroxfb: Unknown outputs setting\n");
			अवरोध;
		पूर्ण
	पूर्ण
	/* Nullअगरy this option क्रम subsequent adapters */
	outमाला_दो[0] = 0;
पूर्ण

अटल पूर्णांक initMatrox2(काष्ठा matrox_fb_info *minfo, काष्ठा board *b)
अणु
	अचिन्हित दीर्घ ctrlptr_phys = 0;
	अचिन्हित दीर्घ video_base_phys = 0;
	अचिन्हित पूर्णांक memsize;
	पूर्णांक err;

	अटल स्थिर काष्ठा pci_device_id पूर्णांकel_82437[] = अणु
		अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82437) पूर्ण,
		अणु पूर्ण,
	पूर्ण;

	DBG(__func__)

	/* set शेष values... */
	vesafb_defined.accel_flags = FB_ACCELF_TEXT;

	minfo->hw_चयन = b->base->lowlevel;
	minfo->devflags.accelerator = b->base->accelID;
	minfo->max_pixel_घड़ी = b->maxclk;

	prपूर्णांकk(KERN_INFO "matroxfb: Matrox %s detected\n", b->name);
	minfo->capable.plnwt = 1;
	minfo->chip = b->chip;
	minfo->capable.srcorg = b->flags & DEVF_SRCORG;
	minfo->devflags.video64bits = b->flags & DEVF_VIDEO64BIT;
	अगर (b->flags & DEVF_TEXT4B) अणु
		minfo->devflags.vgastep = 4;
		minfo->devflags.texपंचांगode = 4;
		minfo->devflags.text_type_aux = FB_AUX_TEXT_MGA_STEP16;
	पूर्ण अन्यथा अगर (b->flags & DEVF_TEXT16B) अणु
		minfo->devflags.vgastep = 16;
		minfo->devflags.texपंचांगode = 1;
		minfo->devflags.text_type_aux = FB_AUX_TEXT_MGA_STEP16;
	पूर्ण अन्यथा अणु
		minfo->devflags.vgastep = 8;
		minfo->devflags.texपंचांगode = 1;
		minfo->devflags.text_type_aux = FB_AUX_TEXT_MGA_STEP8;
	पूर्ण
	minfo->devflags.support32MB = (b->flags & DEVF_SUPPORT32MB) != 0;
	minfo->devflags.precise_width = !(b->flags & DEVF_ANY_VXRES);
	minfo->devflags.crtc2 = (b->flags & DEVF_CRTC2) != 0;
	minfo->devflags.maven_capable = (b->flags & DEVF_MAVEN_CAPABLE) != 0;
	minfo->devflags.dualhead = (b->flags & DEVF_DUALHEAD) != 0;
	minfo->devflags.dfp_type = dfp_type;
	minfo->devflags.g450dac = (b->flags & DEVF_G450DAC) != 0;
	minfo->devflags.textstep = minfo->devflags.vgastep * minfo->devflags.texपंचांगode;
	minfo->devflags.textvram = 65536 / minfo->devflags.texपंचांगode;
	setDefaultOutमाला_दो(minfo);
	अगर (b->flags & DEVF_PANELLINK_CAPABLE) अणु
		minfo->outमाला_दो[2].data = minfo;
		minfo->outमाला_दो[2].output = &panellink_output;
		minfo->outमाला_दो[2].src = minfo->outमाला_दो[2].शेष_src;
		minfo->outमाला_दो[2].mode = MATROXFB_OUTPUT_MODE_MONITOR;
		minfo->devflags.panellink = 1;
	पूर्ण

	अगर (minfo->capable.cross4MB < 0)
		minfo->capable.cross4MB = b->flags & DEVF_CROSS4MB;
	अगर (b->flags & DEVF_SWAPS) अणु
		ctrlptr_phys = pci_resource_start(minfo->pcidev, 1);
		video_base_phys = pci_resource_start(minfo->pcidev, 0);
		minfo->devflags.fbResource = PCI_BASE_ADDRESS_0;
	पूर्ण अन्यथा अणु
		ctrlptr_phys = pci_resource_start(minfo->pcidev, 0);
		video_base_phys = pci_resource_start(minfo->pcidev, 1);
		minfo->devflags.fbResource = PCI_BASE_ADDRESS_1;
	पूर्ण
	err = -EINVAL;
	अगर (!ctrlptr_phys) अणु
		prपूर्णांकk(KERN_ERR "matroxfb: control registers are not available, matroxfb disabled\n");
		जाओ fail;
	पूर्ण
	अगर (!video_base_phys) अणु
		prपूर्णांकk(KERN_ERR "matroxfb: video RAM is not available in PCI address space, matroxfb disabled\n");
		जाओ fail;
	पूर्ण
	memsize = b->base->maxvram;
	अगर (!request_mem_region(ctrlptr_phys, 16384, "matroxfb MMIO")) अणु
		जाओ fail;
	पूर्ण
	अगर (!request_mem_region(video_base_phys, memsize, "matroxfb FB")) अणु
		जाओ failCtrlMR;
	पूर्ण
	minfo->video.len_maximum = memsize;
	/* convert mem (स्वतःdetect k, M) */
	अगर (mem < 1024) mem *= 1024;
	अगर (mem < 0x00100000) mem *= 1024;

	अगर (mem && (mem < memsize))
		memsize = mem;
	err = -ENOMEM;

	minfo->mmio.vbase.vaddr = ioremap(ctrlptr_phys, 16384);
	अगर (!minfo->mmio.vbase.vaddr) अणु
		prपूर्णांकk(KERN_ERR "matroxfb: cannot ioremap(%lX, 16384), matroxfb disabled\n", ctrlptr_phys);
		जाओ failVideoMR;
	पूर्ण
	minfo->mmio.base = ctrlptr_phys;
	minfo->mmio.len = 16384;
	minfo->video.base = video_base_phys;
	minfo->video.vbase.vaddr = ioremap_wc(video_base_phys, memsize);
	अगर (!minfo->video.vbase.vaddr) अणु
		prपूर्णांकk(KERN_ERR "matroxfb: cannot ioremap(%lX, %d), matroxfb disabled\n",
			video_base_phys, memsize);
		जाओ failCtrlIO;
	पूर्ण
	अणु
		u_पूर्णांक32_t cmd;
		u_पूर्णांक32_t mga_option;

		pci_पढ़ो_config_dword(minfo->pcidev, PCI_OPTION_REG, &mga_option);
		pci_पढ़ो_config_dword(minfo->pcidev, PCI_COMMAND, &cmd);
		mga_option &= 0x7FFFFFFF; /* clear BIG_ENDIAN */
		mga_option |= MX_OPTION_BSWAP;
		/* disable palette snooping */
		cmd &= ~PCI_COMMAND_VGA_PALETTE;
		अगर (pci_dev_present(पूर्णांकel_82437)) अणु
			अगर (!(mga_option & 0x20000000) && !minfo->devflags.nopciretry) अणु
				prपूर्णांकk(KERN_WARNING "matroxfb: Disabling PCI retries due to i82437 present\n");
			पूर्ण
			mga_option |= 0x20000000;
			minfo->devflags.nopciretry = 1;
		पूर्ण
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_COMMAND, cmd);
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, mga_option);
		minfo->hw.MXoptionReg = mga_option;

		/* select non-DMA memory क्रम PCI_MGA_DATA, otherwise dump of PCI cfg space can lock PCI bus */
		/* maybe preinit() candidate, but it is same... क्रम all devices... at this समय... */
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_MGA_INDEX, 0x00003C00);
	पूर्ण

	err = -ENXIO;
	matroxfb_पढ़ो_pins(minfo);
	अगर (minfo->hw_चयन->preinit(minfo)) अणु
		जाओ failVideoIO;
	पूर्ण

	err = -ENOMEM;
	अगर (!matroxfb_geपंचांगemory(minfo, memsize, &minfo->video.len) || !minfo->video.len) अणु
		prपूर्णांकk(KERN_ERR "matroxfb: cannot determine memory size\n");
		जाओ failVideoIO;
	पूर्ण
	minfo->devflags.ydstorg = 0;

	minfo->video.base = video_base_phys;
	minfo->video.len_usable = minfo->video.len;
	अगर (minfo->video.len_usable > b->base->maxdisplayable)
		minfo->video.len_usable = b->base->maxdisplayable;
	अगर (mtrr)
		minfo->wc_cookie = arch_phys_wc_add(video_base_phys,
						    minfo->video.len);

	अगर (!minfo->devflags.novga)
		request_region(0x3C0, 32, "matrox");
	matroxfb_g450_connect(minfo);
	minfo->hw_चयन->reset(minfo);

	minfo->fbcon.monspecs.hfmin = 0;
	minfo->fbcon.monspecs.hfmax = fh;
	minfo->fbcon.monspecs.vfmin = 0;
	minfo->fbcon.monspecs.vfmax = fv;
	minfo->fbcon.monspecs.dpms = 0;	/* TBD */

	/* अटल settings */
	vesafb_defined.red = colors[depth-1].red;
	vesafb_defined.green = colors[depth-1].green;
	vesafb_defined.blue = colors[depth-1].blue;
	vesafb_defined.bits_per_pixel = colors[depth-1].bits_per_pixel;
	vesafb_defined.grayscale = grayscale;
	vesafb_defined.vmode = 0;
	अगर (noaccel)
		vesafb_defined.accel_flags &= ~FB_ACCELF_TEXT;

	minfo->fbops = matroxfb_ops;
	minfo->fbcon.fbops = &minfo->fbops;
	minfo->fbcon.pseuकरो_palette = minfo->cmap;
	minfo->fbcon.flags = FBINFO_PARTIAL_PAN_OK | 	 /* Prefer panning क्रम scroll under MC viewer/edit */
				      FBINFO_HWACCEL_COPYAREA |  /* We have hw-assisted bmove */
				      FBINFO_HWACCEL_FILLRECT |  /* And fillrect */
				      FBINFO_HWACCEL_IMAGEBLIT | /* And imageblit */
				      FBINFO_HWACCEL_XPAN |      /* And we support both horizontal */
				      FBINFO_HWACCEL_YPAN |      /* And vertical panning */
				      FBINFO_READS_FAST;
	minfo->video.len_usable &= PAGE_MASK;
	fb_alloc_cmap(&minfo->fbcon.cmap, 256, 1);

#अगर_अघोषित MODULE
	/* mode database is marked __init!!! */
	अगर (!hotplug) अणु
		fb_find_mode(&vesafb_defined, &minfo->fbcon, videomode[0] ? videomode : शून्य,
			शून्य, 0, &शेषmode, vesafb_defined.bits_per_pixel);
	पूर्ण
#पूर्ण_अगर /* !MODULE */

	/* mode modअगरiers */
	अगर (hslen)
		vesafb_defined.hsync_len = hslen;
	अगर (vslen)
		vesafb_defined.vsync_len = vslen;
	अगर (left != ~0)
		vesafb_defined.left_margin = left;
	अगर (right != ~0)
		vesafb_defined.right_margin = right;
	अगर (upper != ~0)
		vesafb_defined.upper_margin = upper;
	अगर (lower != ~0)
		vesafb_defined.lower_margin = lower;
	अगर (xres)
		vesafb_defined.xres = xres;
	अगर (yres)
		vesafb_defined.yres = yres;
	अगर (sync != -1)
		vesafb_defined.sync = sync;
	अन्यथा अगर (vesafb_defined.sync == ~0) अणु
		vesafb_defined.sync = 0;
		अगर (yres < 400)
			vesafb_defined.sync |= FB_SYNC_HOR_HIGH_ACT;
		अन्यथा अगर (yres < 480)
			vesafb_defined.sync |= FB_SYNC_VERT_HIGH_ACT;
	पूर्ण

	/* fv, fh, maxclk limits was specअगरied */
	अणु
		अचिन्हित पूर्णांक पंचांगp;

		अगर (fv) अणु
			पंचांगp = fv * (vesafb_defined.upper_margin + vesafb_defined.yres
				  + vesafb_defined.lower_margin + vesafb_defined.vsync_len);
			अगर ((पंचांगp < fh) || (fh == 0)) fh = पंचांगp;
		पूर्ण
		अगर (fh) अणु
			पंचांगp = fh * (vesafb_defined.left_margin + vesafb_defined.xres
				  + vesafb_defined.right_margin + vesafb_defined.hsync_len);
			अगर ((पंचांगp < maxclk) || (maxclk == 0)) maxclk = पंचांगp;
		पूर्ण
		पंचांगp = (maxclk + 499) / 500;
		अगर (पंचांगp) अणु
			पंचांगp = (2000000000 + पंचांगp) / पंचांगp;
			अगर (पंचांगp > pixघड़ी) pixघड़ी = पंचांगp;
		पूर्ण
	पूर्ण
	अगर (pixघड़ी) अणु
		अगर (pixघड़ी < 2000)		/* > 500MHz */
			pixघड़ी = 4000;	/* 250MHz */
		अगर (pixघड़ी > 1000000)
			pixघड़ी = 1000000;	/* 1MHz */
		vesafb_defined.pixघड़ी = pixघड़ी;
	पूर्ण

	/* FIXME: Where to move this?! */
#अगर defined(CONFIG_PPC_PMAC)
#अगर_अघोषित MODULE
	अगर (machine_is(घातermac)) अणु
		काष्ठा fb_var_screeninfo var;

		अगर (शेष_vmode <= 0 || शेष_vmode > VMODE_MAX)
			शेष_vmode = VMODE_640_480_60;
#अगर defined(CONFIG_PPC32)
		अगर (IS_REACHABLE(CONFIG_NVRAM) && शेष_cmode == CMODE_NVRAM)
			शेष_cmode = nvram_पढ़ो_byte(NV_CMODE);
#पूर्ण_अगर
		अगर (शेष_cmode < CMODE_8 || शेष_cmode > CMODE_32)
			शेष_cmode = CMODE_8;
		अगर (!mac_vmode_to_var(शेष_vmode, शेष_cmode, &var)) अणु
			var.accel_flags = vesafb_defined.accel_flags;
			var.xoffset = var.yoffset = 0;
			/* Note: mac_vmode_to_var() करोes not set all parameters */
			vesafb_defined = var;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* !MODULE */
#पूर्ण_अगर /* CONFIG_PPC_PMAC */
	vesafb_defined.xres_भव = vesafb_defined.xres;
	अगर (nopan) अणु
		vesafb_defined.yres_भव = vesafb_defined.yres;
	पूर्ण अन्यथा अणु
		vesafb_defined.yres_भव = 65536; /* large enough to be INF, but small enough
							to yres_भव * xres_भव < 2^32 */
	पूर्ण
	matroxfb_init_fix(minfo);
	minfo->fbcon.screen_base = vaddr_va(minfo->video.vbase);
	/* Normalize values (namely yres_भव) */
	matroxfb_check_var(&vesafb_defined, &minfo->fbcon);
	/* And put it पूर्णांकo "current" var. Do NOT program hardware yet, or we'll not take over
	 * vgacon correctly. fbcon_startup will call fb_set_par क्रम us, WITHOUT check_var,
	 * and unक्रमtunately it will करो it BEFORE vgacon contents is saved, so it won't work
	 * anyway. But we at least tried... */
	minfo->fbcon.var = vesafb_defined;
	err = -EINVAL;

	prपूर्णांकk(KERN_INFO "matroxfb: %dx%dx%dbpp (virtual: %dx%d)\n",
		vesafb_defined.xres, vesafb_defined.yres, vesafb_defined.bits_per_pixel,
		vesafb_defined.xres_भव, vesafb_defined.yres_भव);
	prपूर्णांकk(KERN_INFO "matroxfb: framebuffer at 0x%lX, mapped to 0x%p, size %d\n",
		minfo->video.base, vaddr_va(minfo->video.vbase), minfo->video.len);

/* We करो not have to set currcon to 0... रेजिस्टर_framebuffer करो it क्रम us on first console
 * and we करो not want currcon == 0 क्रम subsequent framebuffers */

	minfo->fbcon.device = &minfo->pcidev->dev;
	अगर (रेजिस्टर_framebuffer(&minfo->fbcon) < 0) अणु
		जाओ failVideoIO;
	पूर्ण
	fb_info(&minfo->fbcon, "%s frame buffer device\n", minfo->fbcon.fix.id);

	/* there is no console on this fb... but we have to initialize hardware
	 * until someone tells me what is proper thing to करो */
	अगर (!minfo->initialized) अणु
		fb_info(&minfo->fbcon, "initializing hardware\n");
		/* We have to use FB_ACTIVATE_FORCE, as we had to put vesafb_defined to the fbcon.var
		 * alपढ़ोy beक्रमe, so रेजिस्टर_framebuffer works correctly. */
		vesafb_defined.activate |= FB_ACTIVATE_FORCE;
		fb_set_var(&minfo->fbcon, &vesafb_defined);
	पूर्ण

	वापस 0;
failVideoIO:;
	matroxfb_g450_shutकरोwn(minfo);
	iounmap(minfo->video.vbase.vaddr);
failCtrlIO:;
	iounmap(minfo->mmio.vbase.vaddr);
failVideoMR:;
	release_mem_region(video_base_phys, minfo->video.len_maximum);
failCtrlMR:;
	release_mem_region(ctrlptr_phys, 16384);
fail:;
	वापस err;
पूर्ण

अटल LIST_HEAD(matroxfb_list);
अटल LIST_HEAD(matroxfb_driver_list);

#घोषणा matroxfb_l(x) list_entry(x, काष्ठा matrox_fb_info, next_fb)
#घोषणा matroxfb_driver_l(x) list_entry(x, काष्ठा matroxfb_driver, node)
पूर्णांक matroxfb_रेजिस्टर_driver(काष्ठा matroxfb_driver* drv) अणु
	काष्ठा matrox_fb_info* minfo;

	list_add(&drv->node, &matroxfb_driver_list);
	list_क्रम_each_entry(minfo, &matroxfb_list, next_fb) अणु
		व्योम* p;

		अगर (minfo->drivers_count == MATROXFB_MAX_FB_DRIVERS)
			जारी;
		p = drv->probe(minfo);
		अगर (p) अणु
			minfo->drivers_data[minfo->drivers_count] = p;
			minfo->drivers[minfo->drivers_count++] = drv;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम matroxfb_unरेजिस्टर_driver(काष्ठा matroxfb_driver* drv) अणु
	काष्ठा matrox_fb_info* minfo;

	list_del(&drv->node);
	list_क्रम_each_entry(minfo, &matroxfb_list, next_fb) अणु
		पूर्णांक i;

		क्रम (i = 0; i < minfo->drivers_count; ) अणु
			अगर (minfo->drivers[i] == drv) अणु
				अगर (drv && drv->हटाओ)
					drv->हटाओ(minfo, minfo->drivers_data[i]);
				minfo->drivers[i] = minfo->drivers[--minfo->drivers_count];
				minfo->drivers_data[i] = minfo->drivers_data[minfo->drivers_count];
			पूर्ण अन्यथा
				i++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम matroxfb_रेजिस्टर_device(काष्ठा matrox_fb_info* minfo) अणु
	काष्ठा matroxfb_driver* drv;
	पूर्णांक i = 0;
	list_add(&minfo->next_fb, &matroxfb_list);
	क्रम (drv = matroxfb_driver_l(matroxfb_driver_list.next);
	     drv != matroxfb_driver_l(&matroxfb_driver_list);
	     drv = matroxfb_driver_l(drv->node.next)) अणु
		अगर (drv->probe) अणु
			व्योम *p = drv->probe(minfo);
			अगर (p) अणु
				minfo->drivers_data[i] = p;
				minfo->drivers[i++] = drv;
				अगर (i == MATROXFB_MAX_FB_DRIVERS)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	minfo->drivers_count = i;
पूर्ण

अटल व्योम matroxfb_unरेजिस्टर_device(काष्ठा matrox_fb_info* minfo) अणु
	पूर्णांक i;

	list_del(&minfo->next_fb);
	क्रम (i = 0; i < minfo->drivers_count; i++) अणु
		काष्ठा matroxfb_driver* drv = minfo->drivers[i];

		अगर (drv && drv->हटाओ)
			drv->हटाओ(minfo, minfo->drivers_data[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक matroxfb_probe(काष्ठा pci_dev* pdev, स्थिर काष्ठा pci_device_id* dummy) अणु
	काष्ठा board* b;
	u_पूर्णांक16_t svid;
	u_पूर्णांक16_t sid;
	काष्ठा matrox_fb_info* minfo;
	पूर्णांक err;
	u_पूर्णांक32_t cmd;
	DBG(__func__)

	svid = pdev->subप्रणाली_venकरोr;
	sid = pdev->subप्रणाली_device;
	क्रम (b = dev_list; b->venकरोr; b++) अणु
		अगर ((b->venकरोr != pdev->venकरोr) || (b->device != pdev->device) || (b->rev < pdev->revision)) जारी;
		अगर (b->svid)
			अगर ((b->svid != svid) || (b->sid != sid)) जारी;
		अवरोध;
	पूर्ण
	/* not match... */
	अगर (!b->venकरोr)
		वापस -ENODEV;
	अगर (dev > 0) अणु
		/* not requested one... */
		dev--;
		वापस -ENODEV;
	पूर्ण
	pci_पढ़ो_config_dword(pdev, PCI_COMMAND, &cmd);
	अगर (pci_enable_device(pdev)) अणु
		वापस -1;
	पूर्ण

	minfo = kzalloc(माप(*minfo), GFP_KERNEL);
	अगर (!minfo)
		वापस -ENOMEM;

	minfo->pcidev = pdev;
	minfo->dead = 0;
	minfo->usecount = 0;
	minfo->userusecount = 0;

	pci_set_drvdata(pdev, minfo);
	/* DEVFLAGS */
	minfo->devflags.memtype = memtype;
	अगर (memtype != -1)
		noinit = 0;
	अगर (cmd & PCI_COMMAND_MEMORY) अणु
		minfo->devflags.novga = novga;
		minfo->devflags.nobios = nobios;
		minfo->devflags.noinit = noinit;
		/* subsequent heads always needs initialization and must not enable BIOS */
		novga = 1;
		nobios = 1;
		noinit = 0;
	पूर्ण अन्यथा अणु
		minfo->devflags.novga = 1;
		minfo->devflags.nobios = 1;
		minfo->devflags.noinit = 0;
	पूर्ण

	minfo->devflags.nopciretry = no_pci_retry;
	minfo->devflags.mga_24bpp_fix = inv24;
	minfo->devflags.precise_width = option_precise_width;
	minfo->devflags.sgram = sgram;
	minfo->capable.cross4MB = cross4MB;

	spin_lock_init(&minfo->lock.DAC);
	spin_lock_init(&minfo->lock.accel);
	init_rwsem(&minfo->crtc2.lock);
	init_rwsem(&minfo->altout.lock);
	mutex_init(&minfo->fbcon.mm_lock);
	minfo->irq_flags = 0;
	init_रुकोqueue_head(&minfo->crtc1.vsync.रुको);
	init_रुकोqueue_head(&minfo->crtc2.vsync.रुको);
	minfo->crtc1.panpos = -1;

	err = initMatrox2(minfo, b);
	अगर (!err) अणु
		matroxfb_रेजिस्टर_device(minfo);
		वापस 0;
	पूर्ण
	kमुक्त(minfo);
	वापस -1;
पूर्ण

अटल व्योम pci_हटाओ_matrox(काष्ठा pci_dev* pdev) अणु
	काष्ठा matrox_fb_info* minfo;

	minfo = pci_get_drvdata(pdev);
	matroxfb_हटाओ(minfo, 1);
पूर्ण

अटल स्थिर काष्ठा pci_device_id matroxfb_devices[] = अणु
#अगर_घोषित CONFIG_FB_MATROX_MILLENIUM
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MIL,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MIL_2,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MIL_2_AGP,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_MATROX_MYSTIQUE
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_MYS,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_MATROX_G
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G100_MM,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G100_AGP,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G200_PCI,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	0x0532,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G200_AGP,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G400,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_MATROX,	PCI_DEVICE_ID_MATROX_G550,
		PCI_ANY_ID,	PCI_ANY_ID,	0, 0, 0पूर्ण,
#पूर्ण_अगर
	अणु0,			0,
		0,		0,		0, 0, 0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, matroxfb_devices);


अटल काष्ठा pci_driver matroxfb_driver = अणु
	.name =		"matroxfb",
	.id_table =	matroxfb_devices,
	.probe =	matroxfb_probe,
	.हटाओ =	pci_हटाओ_matrox,
पूर्ण;

/* **************************** init-समय only **************************** */

#घोषणा RSResolution(X)	((X) & 0x0F)
#घोषणा RS640x400	1
#घोषणा RS640x480	2
#घोषणा RS800x600	3
#घोषणा RS1024x768	4
#घोषणा RS1280x1024	5
#घोषणा RS1600x1200	6
#घोषणा RS768x576	7
#घोषणा RS960x720	8
#घोषणा RS1152x864	9
#घोषणा RS1408x1056	10
#घोषणा RS640x350	11
#घोषणा RS1056x344	12	/* 132 x 43 text */
#घोषणा RS1056x400	13	/* 132 x 50 text */
#घोषणा RS1056x480	14	/* 132 x 60 text */
#घोषणा RSNoxNo		15
/* 10-FF */
अटल काष्ठा अणु पूर्णांक xres, yres, left, right, upper, lower, hslen, vslen, vfreq; पूर्ण timmings[] __initdata = अणु
	अणु  640,  400,  48, 16, 39,  8,  96, 2, 70 पूर्ण,
	अणु  640,  480,  48, 16, 33, 10,  96, 2, 60 पूर्ण,
	अणु  800,  600, 144, 24, 28,  8, 112, 6, 60 पूर्ण,
	अणु 1024,  768, 160, 32, 30,  4, 128, 4, 60 पूर्ण,
	अणु 1280, 1024, 224, 32, 32,  4, 136, 4, 60 पूर्ण,
	अणु 1600, 1200, 272, 48, 32,  5, 152, 5, 60 पूर्ण,
	अणु  768,  576, 144, 16, 28,  6, 112, 4, 60 पूर्ण,
	अणु  960,  720, 144, 24, 28,  8, 112, 4, 60 पूर्ण,
	अणु 1152,  864, 192, 32, 30,  4, 128, 4, 60 पूर्ण,
	अणु 1408, 1056, 256, 40, 32,  5, 144, 5, 60 पूर्ण,
	अणु  640,  350,  48, 16, 39,  8,  96, 2, 70 पूर्ण,
	अणु 1056,  344,  96, 24, 59, 44, 160, 2, 70 पूर्ण,
	अणु 1056,  400,  96, 24, 39,  8, 160, 2, 70 पूर्ण,
	अणु 1056,  480,  96, 24, 36, 12, 160, 3, 60 पूर्ण,
	अणु    0,    0,  ~0, ~0, ~0, ~0,   0, 0,  0 पूर्ण
पूर्ण;

#घोषणा RSCreate(X,Y)	((X) | ((Y) << 8))
अटल काष्ठा अणु अचिन्हित पूर्णांक vesa; अचिन्हित पूर्णांक info; पूर्ण *RSptr, vesamap[] __initdata = अणु
/* शेष must be first */
	अणु    ~0, RSCreate(RSNoxNo,     RS8bpp ) पूर्ण,
	अणु 0x101, RSCreate(RS640x480,   RS8bpp ) पूर्ण,
	अणु 0x100, RSCreate(RS640x400,   RS8bpp ) पूर्ण,
	अणु 0x180, RSCreate(RS768x576,   RS8bpp ) पूर्ण,
	अणु 0x103, RSCreate(RS800x600,   RS8bpp ) पूर्ण,
	अणु 0x188, RSCreate(RS960x720,   RS8bpp ) पूर्ण,
	अणु 0x105, RSCreate(RS1024x768,  RS8bpp ) पूर्ण,
	अणु 0x190, RSCreate(RS1152x864,  RS8bpp ) पूर्ण,
	अणु 0x107, RSCreate(RS1280x1024, RS8bpp ) पूर्ण,
	अणु 0x198, RSCreate(RS1408x1056, RS8bpp ) पूर्ण,
	अणु 0x11C, RSCreate(RS1600x1200, RS8bpp ) पूर्ण,
	अणु 0x110, RSCreate(RS640x480,   RS15bpp) पूर्ण,
	अणु 0x181, RSCreate(RS768x576,   RS15bpp) पूर्ण,
	अणु 0x113, RSCreate(RS800x600,   RS15bpp) पूर्ण,
	अणु 0x189, RSCreate(RS960x720,   RS15bpp) पूर्ण,
	अणु 0x116, RSCreate(RS1024x768,  RS15bpp) पूर्ण,
	अणु 0x191, RSCreate(RS1152x864,  RS15bpp) पूर्ण,
	अणु 0x119, RSCreate(RS1280x1024, RS15bpp) पूर्ण,
	अणु 0x199, RSCreate(RS1408x1056, RS15bpp) पूर्ण,
	अणु 0x11D, RSCreate(RS1600x1200, RS15bpp) पूर्ण,
	अणु 0x111, RSCreate(RS640x480,   RS16bpp) पूर्ण,
	अणु 0x182, RSCreate(RS768x576,   RS16bpp) पूर्ण,
	अणु 0x114, RSCreate(RS800x600,   RS16bpp) पूर्ण,
	अणु 0x18A, RSCreate(RS960x720,   RS16bpp) पूर्ण,
	अणु 0x117, RSCreate(RS1024x768,  RS16bpp) पूर्ण,
	अणु 0x192, RSCreate(RS1152x864,  RS16bpp) पूर्ण,
	अणु 0x11A, RSCreate(RS1280x1024, RS16bpp) पूर्ण,
	अणु 0x19A, RSCreate(RS1408x1056, RS16bpp) पूर्ण,
	अणु 0x11E, RSCreate(RS1600x1200, RS16bpp) पूर्ण,
	अणु 0x1B2, RSCreate(RS640x480,   RS24bpp) पूर्ण,
	अणु 0x184, RSCreate(RS768x576,   RS24bpp) पूर्ण,
	अणु 0x1B5, RSCreate(RS800x600,   RS24bpp) पूर्ण,
	अणु 0x18C, RSCreate(RS960x720,   RS24bpp) पूर्ण,
	अणु 0x1B8, RSCreate(RS1024x768,  RS24bpp) पूर्ण,
	अणु 0x194, RSCreate(RS1152x864,  RS24bpp) पूर्ण,
	अणु 0x1BB, RSCreate(RS1280x1024, RS24bpp) पूर्ण,
	अणु 0x19C, RSCreate(RS1408x1056, RS24bpp) पूर्ण,
	अणु 0x1BF, RSCreate(RS1600x1200, RS24bpp) पूर्ण,
	अणु 0x112, RSCreate(RS640x480,   RS32bpp) पूर्ण,
	अणु 0x183, RSCreate(RS768x576,   RS32bpp) पूर्ण,
	अणु 0x115, RSCreate(RS800x600,   RS32bpp) पूर्ण,
	अणु 0x18B, RSCreate(RS960x720,   RS32bpp) पूर्ण,
	अणु 0x118, RSCreate(RS1024x768,  RS32bpp) पूर्ण,
	अणु 0x193, RSCreate(RS1152x864,  RS32bpp) पूर्ण,
	अणु 0x11B, RSCreate(RS1280x1024, RS32bpp) पूर्ण,
	अणु 0x19B, RSCreate(RS1408x1056, RS32bpp) पूर्ण,
	अणु 0x11F, RSCreate(RS1600x1200, RS32bpp) पूर्ण,
	अणु 0x010, RSCreate(RS640x350,   RS4bpp ) पूर्ण,
	अणु 0x012, RSCreate(RS640x480,   RS4bpp ) पूर्ण,
	अणु 0x102, RSCreate(RS800x600,   RS4bpp ) पूर्ण,
	अणु 0x104, RSCreate(RS1024x768,  RS4bpp ) पूर्ण,
	अणु 0x106, RSCreate(RS1280x1024, RS4bpp ) पूर्ण,
	अणु     0, 0				पूर्णपूर्ण;

अटल व्योम __init matroxfb_init_params(व्योम) अणु
	/* fh from kHz to Hz */
	अगर (fh < 1000)
		fh *= 1000;	/* 1kHz minimum */
	/* maxclk */
	अगर (maxclk < 1000) maxclk *= 1000;	/* kHz -> Hz, MHz -> kHz */
	अगर (maxclk < 1000000) maxclk *= 1000;	/* kHz -> Hz, 1MHz minimum */
	/* fix VESA number */
	अगर (vesa != ~0)
		vesa &= 0x1DFF;		/* mask out clearscreen, acceleration and so on */

	/* अटल settings */
	क्रम (RSptr = vesamap; RSptr->vesa; RSptr++) अणु
		अगर (RSptr->vesa == vesa) अवरोध;
	पूर्ण
	अगर (!RSptr->vesa) अणु
		prपूर्णांकk(KERN_ERR "Invalid vesa mode 0x%04X\n", vesa);
		RSptr = vesamap;
	पूर्ण
	अणु
		पूर्णांक res = RSResolution(RSptr->info)-1;
		अगर (left == ~0)
			left = timmings[res].left;
		अगर (!xres)
			xres = timmings[res].xres;
		अगर (right == ~0)
			right = timmings[res].right;
		अगर (!hslen)
			hslen = timmings[res].hslen;
		अगर (upper == ~0)
			upper = timmings[res].upper;
		अगर (!yres)
			yres = timmings[res].yres;
		अगर (lower == ~0)
			lower = timmings[res].lower;
		अगर (!vslen)
			vslen = timmings[res].vslen;
		अगर (!(fv||fh||maxclk||pixघड़ी))
			fv = timmings[res].vfreq;
		अगर (depth == -1)
			depth = RSDepth(RSptr->info);
	पूर्ण
पूर्ण

अटल पूर्णांक __init matrox_init(व्योम) अणु
	पूर्णांक err;

	matroxfb_init_params();
	err = pci_रेजिस्टर_driver(&matroxfb_driver);
	dev = -1;	/* accept all new devices... */
	वापस err;
पूर्ण

/* **************************** निकास-समय only **************************** */

अटल व्योम __निकास matrox_करोne(व्योम) अणु
	pci_unरेजिस्टर_driver(&matroxfb_driver);
पूर्ण

#अगर_अघोषित MODULE

/* ************************* init in-kernel code ************************** */

अटल पूर्णांक __init matroxfb_setup(अक्षर *options) अणु
	अक्षर *this_opt;

	DBG(__func__)

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt) जारी;

		dprपूर्णांकk("matroxfb_setup: option %s\n", this_opt);

		अगर (!म_भेदन(this_opt, "dev:", 4))
			dev = simple_म_से_अदीर्घ(this_opt+4, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "depth:", 6)) अणु
			चयन (simple_म_से_अदीर्घ(this_opt+6, शून्य, 0)) अणु
				हाल 0: depth = RSText; अवरोध;
				हाल 4: depth = RS4bpp; अवरोध;
				हाल 8: depth = RS8bpp; अवरोध;
				हाल 15:depth = RS15bpp; अवरोध;
				हाल 16:depth = RS16bpp; अवरोध;
				हाल 24:depth = RS24bpp; अवरोध;
				हाल 32:depth = RS32bpp; अवरोध;
				शेष:
					prपूर्णांकk(KERN_ERR "matroxfb: unsupported color depth\n");
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "xres:", 5))
			xres = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "yres:", 5))
			yres = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "vslen:", 6))
			vslen = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "hslen:", 6))
			hslen = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "left:", 5))
			left = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "right:", 6))
			right = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "upper:", 6))
			upper = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "lower:", 6))
			lower = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "pixclock:", 9))
			pixघड़ी = simple_म_से_अदीर्घ(this_opt+9, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "sync:", 5))
			sync = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "vesa:", 5))
			vesa = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "maxclk:", 7))
			maxclk = simple_म_से_अदीर्घ(this_opt+7, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "fh:", 3))
			fh = simple_म_से_अदीर्घ(this_opt+3, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "fv:", 3))
			fv = simple_म_से_अदीर्घ(this_opt+3, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "mem:", 4))
			mem = simple_म_से_अदीर्घ(this_opt+4, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "mode:", 5))
			strlcpy(videomode, this_opt+5, माप(videomode));
		अन्यथा अगर (!म_भेदन(this_opt, "outputs:", 8))
			strlcpy(outमाला_दो, this_opt+8, माप(outमाला_दो));
		अन्यथा अगर (!म_भेदन(this_opt, "dfp:", 4)) अणु
			dfp_type = simple_म_से_अदीर्घ(this_opt+4, शून्य, 0);
			dfp = 1;
		पूर्ण
#अगर_घोषित CONFIG_PPC_PMAC
		अन्यथा अगर (!म_भेदन(this_opt, "vmode:", 6)) अणु
			अचिन्हित पूर्णांक vmode = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			अगर (vmode > 0 && vmode <= VMODE_MAX)
				शेष_vmode = vmode;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "cmode:", 6)) अणु
			अचिन्हित पूर्णांक cmode = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			चयन (cmode) अणु
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
#पूर्ण_अगर
		अन्यथा अगर (!म_भेद(this_opt, "disabled"))	/* nodisabled करोes not exist */
			disabled = 1;
		अन्यथा अगर (!म_भेद(this_opt, "enabled"))	/* noenabled करोes not exist */
			disabled = 0;
		अन्यथा अगर (!म_भेद(this_opt, "sgram"))	/* nosgram == sdram */
			sgram = 1;
		अन्यथा अगर (!म_भेद(this_opt, "sdram"))
			sgram = 0;
		अन्यथा अगर (!म_भेदन(this_opt, "memtype:", 8))
			memtype = simple_म_से_अदीर्घ(this_opt+8, शून्य, 0);
		अन्यथा अणु
			पूर्णांक value = 1;

			अगर (!म_भेदन(this_opt, "no", 2)) अणु
				value = 0;
				this_opt += 2;
			पूर्ण
			अगर (! म_भेद(this_opt, "inverse"))
				inverse = value;
			अन्यथा अगर (!म_भेद(this_opt, "accel"))
				noaccel = !value;
			अन्यथा अगर (!म_भेद(this_opt, "pan"))
				nopan = !value;
			अन्यथा अगर (!म_भेद(this_opt, "pciretry"))
				no_pci_retry = !value;
			अन्यथा अगर (!म_भेद(this_opt, "vga"))
				novga = !value;
			अन्यथा अगर (!म_भेद(this_opt, "bios"))
				nobios = !value;
			अन्यथा अगर (!म_भेद(this_opt, "init"))
				noinit = !value;
			अन्यथा अगर (!म_भेद(this_opt, "mtrr"))
				mtrr = value;
			अन्यथा अगर (!म_भेद(this_opt, "inv24"))
				inv24 = value;
			अन्यथा अगर (!म_भेद(this_opt, "cross4MB"))
				cross4MB = value;
			अन्यथा अगर (!म_भेद(this_opt, "grayscale"))
				grayscale = value;
			अन्यथा अगर (!म_भेद(this_opt, "dfp"))
				dfp = value;
			अन्यथा अणु
				strlcpy(videomode, this_opt, माप(videomode));
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __initdata initialized = 0;

अटल पूर्णांक __init matroxfb_init(व्योम)
अणु
	अक्षर *option = शून्य;
	पूर्णांक err = 0;

	DBG(__func__)

	अगर (fb_get_options("matroxfb", &option))
		वापस -ENODEV;
	matroxfb_setup(option);

	अगर (disabled)
		वापस -ENXIO;
	अगर (!initialized) अणु
		initialized = 1;
		err = matrox_init();
	पूर्ण
	hotplug = 1;
	/* never वापस failure, user can hotplug matrox later... */
	वापस err;
पूर्ण

module_init(matroxfb_init);

#अन्यथा

/* *************************** init module code **************************** */

MODULE_AUTHOR("(c) 1998-2002 Petr Vandrovec <vandrove@vc.cvut.cz>");
MODULE_DESCRIPTION("Accelerated FBDev driver for Matrox Millennium/Mystique/G100/G200/G400/G450/G550");
MODULE_LICENSE("GPL");

module_param(mem, पूर्णांक, 0);
MODULE_PARM_DESC(mem, "Size of available memory in MB, KB or B (2,4,8,12,16MB, default=autodetect)");
module_param(disabled, पूर्णांक, 0);
MODULE_PARM_DESC(disabled, "Disabled (0 or 1=disabled) (default=0)");
module_param(noaccel, पूर्णांक, 0);
MODULE_PARM_DESC(noaccel, "Do not use accelerating engine (0 or 1=disabled) (default=0)");
module_param(nopan, पूर्णांक, 0);
MODULE_PARM_DESC(nopan, "Disable pan on startup (0 or 1=disabled) (default=0)");
module_param(no_pci_retry, पूर्णांक, 0);
MODULE_PARM_DESC(no_pci_retry, "PCI retries enabled (0 or 1=disabled) (default=0)");
module_param(novga, पूर्णांक, 0);
MODULE_PARM_DESC(novga, "VGA I/O (0x3C0-0x3DF) disabled (0 or 1=disabled) (default=0)");
module_param(nobios, पूर्णांक, 0);
MODULE_PARM_DESC(nobios, "Disables ROM BIOS (0 or 1=disabled) (default=do not change BIOS state)");
module_param(noinit, पूर्णांक, 0);
MODULE_PARM_DESC(noinit, "Disables W/SG/SD-RAM and bus interface initialization (0 or 1=do not initialize) (default=0)");
module_param(memtype, पूर्णांक, 0);
MODULE_PARM_DESC(memtype, "Memory type for G200/G400 (see Documentation/fb/matroxfb.rst for explanation) (default=3 for G200, 0 for G400)");
module_param(mtrr, पूर्णांक, 0);
MODULE_PARM_DESC(mtrr, "This speeds up video memory accesses (0=disabled or 1) (default=1)");
module_param(sgram, पूर्णांक, 0);
MODULE_PARM_DESC(sgram, "Indicates that G100/G200/G400 has SGRAM memory (0=SDRAM, 1=SGRAM) (default=0)");
module_param(inv24, पूर्णांक, 0);
MODULE_PARM_DESC(inv24, "Inverts clock polarity for 24bpp and loop frequency > 100MHz (default=do not invert polarity)");
module_param(inverse, पूर्णांक, 0);
MODULE_PARM_DESC(inverse, "Inverse (0 or 1) (default=0)");
module_param(dev, पूर्णांक, 0);
MODULE_PARM_DESC(dev, "Multihead support, attach to device ID (0..N) (default=all working)");
module_param(vesa, पूर्णांक, 0);
MODULE_PARM_DESC(vesa, "Startup videomode (0x000-0x1FF) (default=0x101)");
module_param(xres, पूर्णांक, 0);
MODULE_PARM_DESC(xres, "Horizontal resolution (px), overrides xres from vesa (default=vesa)");
module_param(yres, पूर्णांक, 0);
MODULE_PARM_DESC(yres, "Vertical resolution (scans), overrides yres from vesa (default=vesa)");
module_param(upper, पूर्णांक, 0);
MODULE_PARM_DESC(upper, "Upper blank space (scans), overrides upper from vesa (default=vesa)");
module_param(lower, पूर्णांक, 0);
MODULE_PARM_DESC(lower, "Lower blank space (scans), overrides lower from vesa (default=vesa)");
module_param(vslen, पूर्णांक, 0);
MODULE_PARM_DESC(vslen, "Vertical sync length (scans), overrides lower from vesa (default=vesa)");
module_param(left, पूर्णांक, 0);
MODULE_PARM_DESC(left, "Left blank space (px), overrides left from vesa (default=vesa)");
module_param(right, पूर्णांक, 0);
MODULE_PARM_DESC(right, "Right blank space (px), overrides right from vesa (default=vesa)");
module_param(hslen, पूर्णांक, 0);
MODULE_PARM_DESC(hslen, "Horizontal sync length (px), overrides hslen from vesa (default=vesa)");
module_param(pixघड़ी, पूर्णांक, 0);
MODULE_PARM_DESC(pixघड़ी, "Pixelclock (ns), overrides pixclock from vesa (default=vesa)");
module_param(sync, पूर्णांक, 0);
MODULE_PARM_DESC(sync, "Sync polarity, overrides sync from vesa (default=vesa)");
module_param(depth, पूर्णांक, 0);
MODULE_PARM_DESC(depth, "Color depth (0=text,8,15,16,24,32) (default=vesa)");
module_param(maxclk, पूर्णांक, 0);
MODULE_PARM_DESC(maxclk, "Startup maximal clock, 0-999MHz, 1000-999999kHz, 1000000-INF Hz");
module_param(fh, पूर्णांक, 0);
MODULE_PARM_DESC(fh, "Startup horizontal frequency, 0-999kHz, 1000-INF Hz");
module_param(fv, पूर्णांक, 0);
MODULE_PARM_DESC(fv, "Startup vertical frequency, 0-INF Hz\n"
"You should specify \"fv:max_monitor_vsync,fh:max_monitor_hsync,maxclk:max_monitor_dotclock\"");
module_param(grayscale, पूर्णांक, 0);
MODULE_PARM_DESC(grayscale, "Sets display into grayscale. Works perfectly with paletized videomode (4, 8bpp), some limitations apply to 16, 24 and 32bpp videomodes (default=nograyscale)");
module_param(cross4MB, पूर्णांक, 0);
MODULE_PARM_DESC(cross4MB, "Specifies that 4MB boundary can be in middle of line. (default=autodetected)");
module_param(dfp, पूर्णांक, 0);
MODULE_PARM_DESC(dfp, "Specifies whether to use digital flat panel interface of G200/G400 (0 or 1) (default=0)");
module_param(dfp_type, पूर्णांक, 0);
MODULE_PARM_DESC(dfp_type, "Specifies DFP interface type (0 to 255) (default=read from hardware)");
module_param_string(outमाला_दो, outमाला_दो, माप(outमाला_दो), 0);
MODULE_PARM_DESC(outमाला_दो, "Specifies which CRTC is mapped to which output (string of up to three letters, consisting of 0 (disabled), 1 (CRTC1), 2 (CRTC2)) (default=111 for Gx50, 101 for G200/G400 with DFP, and 100 for all other devices)");
#अगर_घोषित CONFIG_PPC_PMAC
module_param_named(vmode, शेष_vmode, पूर्णांक, 0);
MODULE_PARM_DESC(vmode, "Specify the vmode mode number that should be used (640x480 default)");
module_param_named(cmode, शेष_cmode, पूर्णांक, 0);
MODULE_PARM_DESC(cmode, "Specify the video depth that should be used (8bit default)");
#पूर्ण_अगर

पूर्णांक __init init_module(व्योम)अणु

	DBG(__func__)

	अगर (disabled)
		वापस -ENXIO;

	अगर (depth == 0)
		depth = RSText;
	अन्यथा अगर (depth == 4)
		depth = RS4bpp;
	अन्यथा अगर (depth == 8)
		depth = RS8bpp;
	अन्यथा अगर (depth == 15)
		depth = RS15bpp;
	अन्यथा अगर (depth == 16)
		depth = RS16bpp;
	अन्यथा अगर (depth == 24)
		depth = RS24bpp;
	अन्यथा अगर (depth == 32)
		depth = RS32bpp;
	अन्यथा अगर (depth != -1) अणु
		prपूर्णांकk(KERN_ERR "matroxfb: depth %d is not supported, using default\n", depth);
		depth = -1;
	पूर्ण
	matrox_init();
	/* never वापस failure; user can hotplug matrox later... */
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* MODULE */

module_निकास(matrox_करोne);
EXPORT_SYMBOL(matroxfb_रेजिस्टर_driver);
EXPORT_SYMBOL(matroxfb_unरेजिस्टर_driver);
EXPORT_SYMBOL(matroxfb_रुको_क्रम_sync);
EXPORT_SYMBOL(matroxfb_enable_irq);
