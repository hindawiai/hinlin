<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200 and G400
 *
 * (c) 1998-2002 Petr Vandrovec <vandrove@vc.cvut.cz>
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

#समावेश "matroxfb_accel.h"
#समावेश "matroxfb_DAC1064.h"
#समावेश "matroxfb_Ti3026.h"
#समावेश "matroxfb_misc.h"

#घोषणा curr_ydstorg(x)	((x)->curr.ydstorg.pixels)

#घोषणा mga_ydstlen(y,l) mga_outl(M_YDSTLEN | M_EXEC, ((y) << 16) | (l))

अटल अंतरभूत व्योम matrox_cfb4_pal(u_पूर्णांक32_t* pal) अणु
	अचिन्हित पूर्णांक i;
	
	क्रम (i = 0; i < 16; i++) अणु
		pal[i] = i * 0x11111111U;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम matrox_cfb8_pal(u_पूर्णांक32_t* pal) अणु
	अचिन्हित पूर्णांक i;
	
	क्रम (i = 0; i < 16; i++) अणु
		pal[i] = i * 0x01010101U;
	पूर्ण
पूर्ण

अटल व्योम matroxfb_copyarea(काष्ठा fb_info* info, स्थिर काष्ठा fb_copyarea* area);
अटल व्योम matroxfb_fillrect(काष्ठा fb_info* info, स्थिर काष्ठा fb_fillrect* rect);
अटल व्योम matroxfb_imageblit(काष्ठा fb_info* info, स्थिर काष्ठा fb_image* image);
अटल व्योम matroxfb_cfb4_fillrect(काष्ठा fb_info* info, स्थिर काष्ठा fb_fillrect* rect);
अटल व्योम matroxfb_cfb4_copyarea(काष्ठा fb_info* info, स्थिर काष्ठा fb_copyarea* area);

व्योम matrox_cfbX_init(काष्ठा matrox_fb_info *minfo)
अणु
	u_पूर्णांक32_t maccess;
	u_पूर्णांक32_t mpitch;
	u_पूर्णांक32_t mopmode;
	पूर्णांक accel;

	DBG(__func__)

	mpitch = minfo->fbcon.var.xres_भव;

	minfo->fbops.fb_copyarea = cfb_copyarea;
	minfo->fbops.fb_fillrect = cfb_fillrect;
	minfo->fbops.fb_imageblit = cfb_imageblit;
	minfo->fbops.fb_cursor = शून्य;

	accel = (minfo->fbcon.var.accel_flags & FB_ACCELF_TEXT) == FB_ACCELF_TEXT;

	चयन (minfo->fbcon.var.bits_per_pixel) अणु
		हाल 4:		maccess = 0x00000000;	/* accelerate as 8bpp video */
				mpitch = (mpitch >> 1) | 0x8000; /* disable linearization */
				mopmode = M_OPMODE_4BPP;
				matrox_cfb4_pal(minfo->cmap);
				अगर (accel && !(mpitch & 1)) अणु
					minfo->fbops.fb_copyarea = matroxfb_cfb4_copyarea;
					minfo->fbops.fb_fillrect = matroxfb_cfb4_fillrect;
				पूर्ण
				अवरोध;
		हाल 8:		maccess = 0x00000000;
				mopmode = M_OPMODE_8BPP;
				matrox_cfb8_pal(minfo->cmap);
				अगर (accel) अणु
					minfo->fbops.fb_copyarea = matroxfb_copyarea;
					minfo->fbops.fb_fillrect = matroxfb_fillrect;
					minfo->fbops.fb_imageblit = matroxfb_imageblit;
				पूर्ण
				अवरोध;
		हाल 16:	अगर (minfo->fbcon.var.green.length == 5)
					maccess = 0xC0000001;
				अन्यथा
					maccess = 0x40000001;
				mopmode = M_OPMODE_16BPP;
				अगर (accel) अणु
					minfo->fbops.fb_copyarea = matroxfb_copyarea;
					minfo->fbops.fb_fillrect = matroxfb_fillrect;
					minfo->fbops.fb_imageblit = matroxfb_imageblit;
				पूर्ण
				अवरोध;
		हाल 24:	maccess = 0x00000003;
				mopmode = M_OPMODE_24BPP;
				अगर (accel) अणु
					minfo->fbops.fb_copyarea = matroxfb_copyarea;
					minfo->fbops.fb_fillrect = matroxfb_fillrect;
					minfo->fbops.fb_imageblit = matroxfb_imageblit;
				पूर्ण
				अवरोध;
		हाल 32:	maccess = 0x00000002;
				mopmode = M_OPMODE_32BPP;
				अगर (accel) अणु
					minfo->fbops.fb_copyarea = matroxfb_copyarea;
					minfo->fbops.fb_fillrect = matroxfb_fillrect;
					minfo->fbops.fb_imageblit = matroxfb_imageblit;
				पूर्ण
				अवरोध;
		शेष:	maccess = 0x00000000;
				mopmode = 0x00000000;
				अवरोध;	/* turn off acceleration!!! */
	पूर्ण
	mga_fअगरo(8);
	mga_outl(M_PITCH, mpitch);
	mga_outl(M_YDSTORG, curr_ydstorg(minfo));
	अगर (minfo->capable.plnwt)
		mga_outl(M_PLNWT, -1);
	अगर (minfo->capable.srcorg) अणु
		mga_outl(M_SRCORG, 0);
		mga_outl(M_DSTORG, 0);
	पूर्ण
	mga_outl(M_OPMODE, mopmode);
	mga_outl(M_CXBNDRY, 0xFFFF0000);
	mga_outl(M_YTOP, 0);
	mga_outl(M_YBOT, 0x01FFFFFF);
	mga_outl(M_MACCESS, maccess);
	minfo->accel.m_dwg_rect = M_DWG_TRAP | M_DWG_SOLID | M_DWG_ARZERO | M_DWG_SGNZERO | M_DWG_SHIFTZERO;
	अगर (isMilleniumII(minfo)) minfo->accel.m_dwg_rect |= M_DWG_TRANSC;
	minfo->accel.m_opmode = mopmode;
	minfo->accel.m_access = maccess;
	minfo->accel.m_pitch = mpitch;
पूर्ण

EXPORT_SYMBOL(matrox_cfbX_init);

अटल व्योम matrox_accel_restore_maccess(काष्ठा matrox_fb_info *minfo)
अणु
	mga_outl(M_MACCESS, minfo->accel.m_access);
	mga_outl(M_PITCH, minfo->accel.m_pitch);
पूर्ण

अटल व्योम matrox_accel_bmove(काष्ठा matrox_fb_info *minfo, पूर्णांक vxres, पूर्णांक sy,
			       पूर्णांक sx, पूर्णांक dy, पूर्णांक dx, पूर्णांक height, पूर्णांक width)
अणु
	पूर्णांक start, end;
	CRITFLAGS

	DBG(__func__)

	CRITBEGIN

	अगर ((dy < sy) || ((dy == sy) && (dx <= sx))) अणु
		mga_fअगरo(4);
		matrox_accel_restore_maccess(minfo);
		mga_outl(M_DWGCTL, M_DWG_BITBLT | M_DWG_SHIFTZERO | M_DWG_SGNZERO |
			 M_DWG_BFCOL | M_DWG_REPLACE);
		mga_outl(M_AR5, vxres);
		width--;
		start = sy*vxres+sx+curr_ydstorg(minfo);
		end = start+width;
	पूर्ण अन्यथा अणु
		mga_fअगरo(5);
		matrox_accel_restore_maccess(minfo);
		mga_outl(M_DWGCTL, M_DWG_BITBLT | M_DWG_SHIFTZERO | M_DWG_BFCOL | M_DWG_REPLACE);
		mga_outl(M_SGN, 5);
		mga_outl(M_AR5, -vxres);
		width--;
		end = (sy+height-1)*vxres+sx+curr_ydstorg(minfo);
		start = end+width;
		dy += height-1;
	पूर्ण
	mga_fअगरo(6);
	matrox_accel_restore_maccess(minfo);
	mga_outl(M_AR0, end);
	mga_outl(M_AR3, start);
	mga_outl(M_FXBNDRY, ((dx+width)<<16) | dx);
	mga_ydstlen(dy, height);
	WaitTillIdle();

	CRITEND
पूर्ण

अटल व्योम matrox_accel_bmove_lin(काष्ठा matrox_fb_info *minfo, पूर्णांक vxres,
				   पूर्णांक sy, पूर्णांक sx, पूर्णांक dy, पूर्णांक dx, पूर्णांक height,
				   पूर्णांक width)
अणु
	पूर्णांक start, end;
	CRITFLAGS

	DBG(__func__)

	CRITBEGIN

	अगर ((dy < sy) || ((dy == sy) && (dx <= sx))) अणु
		mga_fअगरo(4);
		matrox_accel_restore_maccess(minfo);
		mga_outl(M_DWGCTL, M_DWG_BITBLT | M_DWG_SHIFTZERO | M_DWG_SGNZERO |
			M_DWG_BFCOL | M_DWG_REPLACE);
		mga_outl(M_AR5, vxres);
		width--;
		start = sy*vxres+sx+curr_ydstorg(minfo);
		end = start+width;
	पूर्ण अन्यथा अणु
		mga_fअगरo(5);
		matrox_accel_restore_maccess(minfo);
		mga_outl(M_DWGCTL, M_DWG_BITBLT | M_DWG_SHIFTZERO | M_DWG_BFCOL | M_DWG_REPLACE);
		mga_outl(M_SGN, 5);
		mga_outl(M_AR5, -vxres);
		width--;
		end = (sy+height-1)*vxres+sx+curr_ydstorg(minfo);
		start = end+width;
		dy += height-1;
	पूर्ण
	mga_fअगरo(7);
	matrox_accel_restore_maccess(minfo);
	mga_outl(M_AR0, end);
	mga_outl(M_AR3, start);
	mga_outl(M_FXBNDRY, ((dx+width)<<16) | dx);
	mga_outl(M_YDST, dy*vxres >> 5);
	mga_outl(M_LEN | M_EXEC, height);
	WaitTillIdle();

	CRITEND
पूर्ण

अटल व्योम matroxfb_cfb4_copyarea(काष्ठा fb_info* info, स्थिर काष्ठा fb_copyarea* area) अणु
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	अगर ((area->sx | area->dx | area->width) & 1)
		cfb_copyarea(info, area);
	अन्यथा
		matrox_accel_bmove_lin(minfo, minfo->fbcon.var.xres_भव >> 1, area->sy, area->sx >> 1, area->dy, area->dx >> 1, area->height, area->width >> 1);
पूर्ण

अटल व्योम matroxfb_copyarea(काष्ठा fb_info* info, स्थिर काष्ठा fb_copyarea* area) अणु
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	matrox_accel_bmove(minfo, minfo->fbcon.var.xres_भव, area->sy, area->sx, area->dy, area->dx, area->height, area->width);
पूर्ण

अटल व्योम matroxfb_accel_clear(काष्ठा matrox_fb_info *minfo, u_पूर्णांक32_t color,
				 पूर्णांक sy, पूर्णांक sx, पूर्णांक height, पूर्णांक width)
अणु
	CRITFLAGS

	DBG(__func__)

	CRITBEGIN

	mga_fअगरo(7);
	matrox_accel_restore_maccess(minfo);
	mga_outl(M_DWGCTL, minfo->accel.m_dwg_rect | M_DWG_REPLACE);
	mga_outl(M_FCOL, color);
	mga_outl(M_FXBNDRY, ((sx + width) << 16) | sx);
	mga_ydstlen(sy, height);
	WaitTillIdle();

	CRITEND
पूर्ण

अटल व्योम matroxfb_fillrect(काष्ठा fb_info* info, स्थिर काष्ठा fb_fillrect* rect) अणु
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	चयन (rect->rop) अणु
		हाल ROP_COPY:
			matroxfb_accel_clear(minfo, ((u_पूर्णांक32_t *)info->pseuकरो_palette)[rect->color], rect->dy, rect->dx, rect->height, rect->width);
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम matroxfb_cfb4_clear(काष्ठा matrox_fb_info *minfo, u_पूर्णांक32_t bgx,
				पूर्णांक sy, पूर्णांक sx, पूर्णांक height, पूर्णांक width)
अणु
	पूर्णांक whattoकरो;
	CRITFLAGS

	DBG(__func__)

	CRITBEGIN

	whattoकरो = 0;
	अगर (sx & 1) अणु
		sx ++;
		अगर (!width) वापस;
		width --;
		whattoकरो = 1;
	पूर्ण
	अगर (width & 1) अणु
		whattoकरो |= 2;
	पूर्ण
	width >>= 1;
	sx >>= 1;
	अगर (width) अणु
		mga_fअगरo(7);
		matrox_accel_restore_maccess(minfo);
		mga_outl(M_DWGCTL, minfo->accel.m_dwg_rect | M_DWG_REPLACE2);
		mga_outl(M_FCOL, bgx);
		mga_outl(M_FXBNDRY, ((sx + width) << 16) | sx);
		mga_outl(M_YDST, sy * minfo->fbcon.var.xres_भव >> 6);
		mga_outl(M_LEN | M_EXEC, height);
		WaitTillIdle();
	पूर्ण
	अगर (whattoकरो) अणु
		u_पूर्णांक32_t step = minfo->fbcon.var.xres_भव >> 1;
		vaddr_t vbase = minfo->video.vbase;
		अगर (whattoकरो & 1) अणु
			अचिन्हित पूर्णांक uaddr = sy * step + sx - 1;
			u_पूर्णांक32_t loop;
			u_पूर्णांक8_t bgx2 = bgx & 0xF0;
			क्रम (loop = height; loop > 0; loop --) अणु
				mga_ग_लिखोb(vbase, uaddr, (mga_पढ़ोb(vbase, uaddr) & 0x0F) | bgx2);
				uaddr += step;
			पूर्ण
		पूर्ण
		अगर (whattoकरो & 2) अणु
			अचिन्हित पूर्णांक uaddr = sy * step + sx + width;
			u_पूर्णांक32_t loop;
			u_पूर्णांक8_t bgx2 = bgx & 0x0F;
			क्रम (loop = height; loop > 0; loop --) अणु
				mga_ग_लिखोb(vbase, uaddr, (mga_पढ़ोb(vbase, uaddr) & 0xF0) | bgx2);
				uaddr += step;
			पूर्ण
		पूर्ण
	पूर्ण

	CRITEND
पूर्ण

अटल व्योम matroxfb_cfb4_fillrect(काष्ठा fb_info* info, स्थिर काष्ठा fb_fillrect* rect) अणु
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	चयन (rect->rop) अणु
		हाल ROP_COPY:
			matroxfb_cfb4_clear(minfo, ((u_पूर्णांक32_t *)info->pseuकरो_palette)[rect->color], rect->dy, rect->dx, rect->height, rect->width);
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम matroxfb_1bpp_imageblit(काष्ठा matrox_fb_info *minfo, u_पूर्णांक32_t fgx,
				    u_पूर्णांक32_t bgx, स्थिर u_पूर्णांक8_t *अक्षरdata,
				    पूर्णांक width, पूर्णांक height, पूर्णांक yy, पूर्णांक xx)
अणु
	u_पूर्णांक32_t step;
	u_पूर्णांक32_t ydstlen;
	u_पूर्णांक32_t xlen;
	u_पूर्णांक32_t ar0;
	u_पूर्णांक32_t अक्षरcell;
	u_पूर्णांक32_t fxbndry;
	vaddr_t mmio;
	पूर्णांक easy;
	CRITFLAGS

	DBG_HEAVY(__func__);

	step = (width + 7) >> 3;
	अक्षरcell = height * step;
	xlen = (अक्षरcell + 3) & ~3;
	ydstlen = (yy << 16) | height;
	अगर (width == step << 3) अणु
		ar0 = height * width - 1;
		easy = 1;
	पूर्ण अन्यथा अणु
		ar0 = width - 1;
		easy = 0;
	पूर्ण

	CRITBEGIN

	mga_fअगरo(5);
	matrox_accel_restore_maccess(minfo);
	अगर (easy)
		mga_outl(M_DWGCTL, M_DWG_ILOAD | M_DWG_SGNZERO | M_DWG_SHIFTZERO | M_DWG_BMONOWF | M_DWG_LINEAR | M_DWG_REPLACE);
	अन्यथा
		mga_outl(M_DWGCTL, M_DWG_ILOAD | M_DWG_SGNZERO | M_DWG_SHIFTZERO | M_DWG_BMONOWF | M_DWG_REPLACE);
	mga_outl(M_FCOL, fgx);
	mga_outl(M_BCOL, bgx);
	fxbndry = ((xx + width - 1) << 16) | xx;
	mmio = minfo->mmio.vbase;

	mga_fअगरo(8);
	matrox_accel_restore_maccess(minfo);
	mga_ग_लिखोl(mmio, M_FXBNDRY, fxbndry);
	mga_ग_लिखोl(mmio, M_AR0, ar0);
	mga_ग_लिखोl(mmio, M_AR3, 0);
	अगर (easy) अणु
		mga_ग_लिखोl(mmio, M_YDSTLEN | M_EXEC, ydstlen);
		mga_स_नकल_toio(mmio, अक्षरdata, xlen);
	पूर्ण अन्यथा अणु
		mga_ग_लिखोl(mmio, M_AR5, 0);
		mga_ग_लिखोl(mmio, M_YDSTLEN | M_EXEC, ydstlen);
		अगर ((step & 3) == 0) अणु
			/* Great. Source has 32bit aligned lines, so we can feed them
			   directly to the accelerator. */
			mga_स_नकल_toio(mmio, अक्षरdata, अक्षरcell);
		पूर्ण अन्यथा अगर (step == 1) अणु
			/* Special हाल क्रम 1..8bit widths */
			जबतक (height--) अणु
#अगर defined(__BIG_ENDIAN)
				fb_ग_लिखोl((*अक्षरdata) << 24, mmio.vaddr);
#अन्यथा
				fb_ग_लिखोl(*अक्षरdata, mmio.vaddr);
#पूर्ण_अगर
				अक्षरdata++;
			पूर्ण
		पूर्ण अन्यथा अगर (step == 2) अणु
			/* Special हाल क्रम 9..15bit widths */
			जबतक (height--) अणु
#अगर defined(__BIG_ENDIAN)
				fb_ग_लिखोl((*(u_पूर्णांक16_t*)अक्षरdata) << 16, mmio.vaddr);
#अन्यथा
				fb_ग_लिखोl(*(u_पूर्णांक16_t*)अक्षरdata, mmio.vaddr);
#पूर्ण_अगर
				अक्षरdata += 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Tell... well, why bother... */
			जबतक (height--) अणु
				माप_प्रकार i;
				
				क्रम (i = 0; i < step; i += 4) अणु
					/* Hope that there are at least three पढ़ोable bytes beyond the end of biपंचांगap */
					fb_ग_लिखोl(get_unaligned((u_पूर्णांक32_t*)(अक्षरdata + i)),mmio.vaddr);
				पूर्ण
				अक्षरdata += step;
			पूर्ण
		पूर्ण
	पूर्ण
	WaitTillIdle();
	CRITEND
पूर्ण


अटल व्योम matroxfb_imageblit(काष्ठा fb_info* info, स्थिर काष्ठा fb_image* image) अणु
	काष्ठा matrox_fb_info *minfo = info2minfo(info);

	DBG_HEAVY(__func__);

	अगर (image->depth == 1) अणु
		u_पूर्णांक32_t fgx, bgx;

		fgx = ((u_पूर्णांक32_t*)info->pseuकरो_palette)[image->fg_color];
		bgx = ((u_पूर्णांक32_t*)info->pseuकरो_palette)[image->bg_color];
		matroxfb_1bpp_imageblit(minfo, fgx, bgx, image->data, image->width, image->height, image->dy, image->dx);
	पूर्ण अन्यथा अणु
		/* Danger! image->depth is useless: logo paपूर्णांकing code always
		   passes framebuffer color depth here, although logo data are
		   always 8bpp and info->pseuकरो_palette is changed to contain
		   logo palette to be used (but only क्रम true/direct-color... sic...).
		   So करो it completely in software... */
		cfb_imageblit(info, image);
	पूर्ण
पूर्ण

MODULE_LICENSE("GPL");
