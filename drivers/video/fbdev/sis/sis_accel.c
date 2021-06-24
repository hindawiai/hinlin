<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SiS 300/540/630[S]/730[S],
 * SiS 315[E|PRO]/550/[M]650/651/[M]661[F|M]X/740/[M]741[GX]/330/[M]760[GX],
 * XGI V3XT/V5/V8, Z7
 * frame buffer driver क्रम Linux kernels >= 2.4.14 and >=2.6.3
 *
 * 2D acceleration part
 *
 * Based on the XFree86/X.org driver which is
 *     Copyright (C) 2001-2005 by Thomas Winischhofer, Vienna, Austria
 *
 * Author: Thomas Winischhofer <thomas@winischhofer.net>
 *			(see http://www.winischhofer.net/
 *			क्रम more inक्रमmation and updates)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>

#समावेश "sis.h"
#समावेश "sis_accel.h"

अटल स्थिर u8 sisALUConv[] =
अणु
    0x00,       /* dest = 0;            0,      GXclear,        0 */
    0x88,       /* dest &= src;         DSa,    GXand,          0x1 */
    0x44,       /* dest = src & ~dest;  SDna,   GXandReverse,   0x2 */
    0xCC,       /* dest = src;          S,      GXcopy,         0x3 */
    0x22,       /* dest &= ~src;        DSna,   GXandInverted,  0x4 */
    0xAA,       /* dest = dest;         D,      GXnoop,         0x5 */
    0x66,       /* dest = ^src;         DSx,    GXxor,          0x6 */
    0xEE,       /* dest |= src;         DSo,    GXor,           0x7 */
    0x11,       /* dest = ~src & ~dest; DSon,   GXnor,          0x8 */
    0x99,       /* dest ^= ~src ;       DSxn,   GXequiv,        0x9 */
    0x55,       /* dest = ~dest;        Dn,     GXInvert,       0xA */
    0xDD,       /* dest = src|~dest ;   SDno,   GXorReverse,    0xB */
    0x33,       /* dest = ~src;         Sn,     GXcopyInverted, 0xC */
    0xBB,       /* dest |= ~src;        DSno,   GXorInverted,   0xD */
    0x77,       /* dest = ~src|~dest;   DSan,   GXnand,         0xE */
    0xFF,       /* dest = 0xFF;         1,      GXset,          0xF */
पूर्ण;
/* same ROP but with Pattern as Source */
अटल स्थिर u8 sisPatALUConv[] =
अणु
    0x00,       /* dest = 0;            0,      GXclear,        0 */
    0xA0,       /* dest &= src;         DPa,    GXand,          0x1 */
    0x50,       /* dest = src & ~dest;  PDna,   GXandReverse,   0x2 */
    0xF0,       /* dest = src;          P,      GXcopy,         0x3 */
    0x0A,       /* dest &= ~src;        DPna,   GXandInverted,  0x4 */
    0xAA,       /* dest = dest;         D,      GXnoop,         0x5 */
    0x5A,       /* dest = ^src;         DPx,    GXxor,          0x6 */
    0xFA,       /* dest |= src;         DPo,    GXor,           0x7 */
    0x05,       /* dest = ~src & ~dest; DPon,   GXnor,          0x8 */
    0xA5,       /* dest ^= ~src ;       DPxn,   GXequiv,        0x9 */
    0x55,       /* dest = ~dest;        Dn,     GXInvert,       0xA */
    0xF5,       /* dest = src|~dest ;   PDno,   GXorReverse,    0xB */
    0x0F,       /* dest = ~src;         Pn,     GXcopyInverted, 0xC */
    0xAF,       /* dest |= ~src;        DPno,   GXorInverted,   0xD */
    0x5F,       /* dest = ~src|~dest;   DPan,   GXnand,         0xE */
    0xFF,       /* dest = 0xFF;         1,      GXset,          0xF */
पूर्ण;

अटल स्थिर पूर्णांक myrops[] = अणु
   	3, 10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
पूर्ण;

/* 300 series ----------------------------------------------------- */
#अगर_घोषित CONFIG_FB_SIS_300
अटल व्योम
SiS300Sync(काष्ठा sis_video_info *ivideo)
अणु
	SiS300Idle
पूर्ण

अटल व्योम
SiS300SetupForScreenToScreenCopy(काष्ठा sis_video_info *ivideo, पूर्णांक xdir, पूर्णांक ydir,
                                 पूर्णांक rop, पूर्णांक trans_color)
अणु
	SiS300SetupDSTColorDepth(ivideo->DstColor);
	SiS300SetupSRCPitch(ivideo->video_linelength)
	SiS300SetupDSTRect(ivideo->video_linelength, 0xffff)

	अगर(trans_color != -1) अणु
		SiS300SetupROP(0x0A)
		SiS300SetupSRCTrans(trans_color)
		SiS300SetupCMDFlag(TRANSPARENT_BITBLT)
	पूर्ण अन्यथा अणु
	        SiS300SetupROP(sisALUConv[rop])
	पूर्ण
	अगर(xdir > 0) अणु
		SiS300SetupCMDFlag(X_INC)
	पूर्ण
	अगर(ydir > 0) अणु
		SiS300SetupCMDFlag(Y_INC)
	पूर्ण
पूर्ण

अटल व्योम
SiS300SubsequentScreenToScreenCopy(काष्ठा sis_video_info *ivideo, पूर्णांक src_x,
				   पूर्णांक src_y, पूर्णांक dst_x, पूर्णांक dst_y, पूर्णांक width, पूर्णांक height)
अणु
	u32 srcbase = 0, dstbase = 0;

	अगर(src_y >= 2048) अणु
		srcbase = ivideo->video_linelength * src_y;
		src_y = 0;
	पूर्ण
	अगर(dst_y >= 2048) अणु
		dstbase = ivideo->video_linelength * dst_y;
		dst_y = 0;
	पूर्ण

	SiS300SetupSRCBase(srcbase);
	SiS300SetupDSTBase(dstbase);

	अगर(!(ivideo->CommandReg & X_INC))  अणु
		src_x += width-1;
		dst_x += width-1;
	पूर्ण
	अगर(!(ivideo->CommandReg & Y_INC))  अणु
		src_y += height-1;
		dst_y += height-1;
	पूर्ण
	SiS300SetupRect(width, height)
	SiS300SetupSRCXY(src_x, src_y)
	SiS300SetupDSTXY(dst_x, dst_y)
	SiS300DoCMD
पूर्ण

अटल व्योम
SiS300SetupForSolidFill(काष्ठा sis_video_info *ivideo, u32 color, पूर्णांक rop)
अणु
	SiS300SetupPATFG(color)
	SiS300SetupDSTRect(ivideo->video_linelength, 0xffff)
	SiS300SetupDSTColorDepth(ivideo->DstColor);
	SiS300SetupROP(sisPatALUConv[rop])
	SiS300SetupCMDFlag(PATFG)
पूर्ण

अटल व्योम
SiS300SubsequentSolidFillRect(काष्ठा sis_video_info *ivideo, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h)
अणु
	u32 dstbase = 0;

	अगर(y >= 2048) अणु
		dstbase = ivideo->video_linelength * y;
		y = 0;
	पूर्ण
	SiS300SetupDSTBase(dstbase)
	SiS300SetupDSTXY(x,y)
	SiS300SetupRect(w,h)
	SiS300SetupCMDFlag(X_INC | Y_INC | BITBLT)
	SiS300DoCMD
पूर्ण
#पूर्ण_अगर

/* 315/330/340 series ---------------------------------------------- */

#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम
SiS310Sync(काष्ठा sis_video_info *ivideo)
अणु
	SiS310Idle
पूर्ण

अटल व्योम
SiS310SetupForScreenToScreenCopy(काष्ठा sis_video_info *ivideo, पूर्णांक rop, पूर्णांक trans_color)
अणु
	SiS310SetupDSTColorDepth(ivideo->DstColor);
	SiS310SetupSRCPitch(ivideo->video_linelength)
	SiS310SetupDSTRect(ivideo->video_linelength, 0x0fff)
	अगर(trans_color != -1) अणु
		SiS310SetupROP(0x0A)
		SiS310SetupSRCTrans(trans_color)
		SiS310SetupCMDFlag(TRANSPARENT_BITBLT)
	पूर्ण अन्यथा अणु
	        SiS310SetupROP(sisALUConv[rop])
		/* Set command - not needed, both 0 */
		/* SiSSetupCMDFlag(BITBLT | SRCVIDEO) */
	पूर्ण
	SiS310SetupCMDFlag(ivideo->SiS310_AccelDepth)
	/* The chip is smart enough to know the direction */
पूर्ण

अटल व्योम
SiS310SubsequentScreenToScreenCopy(काष्ठा sis_video_info *ivideo, पूर्णांक src_x, पूर्णांक src_y,
			 पूर्णांक dst_x, पूर्णांक dst_y, पूर्णांक width, पूर्णांक height)
अणु
	u32 srcbase = 0, dstbase = 0;
	पूर्णांक mymin = min(src_y, dst_y);
	पूर्णांक mymax = max(src_y, dst_y);

	/* Although the chip knows the direction to use
	 * अगर the source and destination areas overlap,
	 * that logic fails अगर we fiddle with the biपंचांगap
	 * addresses. Thereक्रमe, we check अगर the source
	 * and destination blitting areas overlap and
	 * adapt the biपंचांगap addresses synchronously
	 * अगर the coordinates exceed the valid range.
	 * The the areas करो not overlap, we करो our
	 * normal check.
	 */
	अगर((mymax - mymin) < height) अणु
		अगर((src_y >= 2048) || (dst_y >= 2048)) अणु
			srcbase = ivideo->video_linelength * mymin;
			dstbase = ivideo->video_linelength * mymin;
			src_y -= mymin;
			dst_y -= mymin;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर(src_y >= 2048) अणु
			srcbase = ivideo->video_linelength * src_y;
			src_y = 0;
		पूर्ण
		अगर(dst_y >= 2048) अणु
			dstbase = ivideo->video_linelength * dst_y;
			dst_y = 0;
		पूर्ण
	पूर्ण

	srcbase += ivideo->video_offset;
	dstbase += ivideo->video_offset;

	SiS310SetupSRCBase(srcbase);
	SiS310SetupDSTBase(dstbase);
	SiS310SetupRect(width, height)
	SiS310SetupSRCXY(src_x, src_y)
	SiS310SetupDSTXY(dst_x, dst_y)
	SiS310DoCMD
पूर्ण

अटल व्योम
SiS310SetupForSolidFill(काष्ठा sis_video_info *ivideo, u32 color, पूर्णांक rop)
अणु
	SiS310SetupPATFG(color)
	SiS310SetupDSTRect(ivideo->video_linelength, 0x0fff)
	SiS310SetupDSTColorDepth(ivideo->DstColor);
	SiS310SetupROP(sisPatALUConv[rop])
	SiS310SetupCMDFlag(PATFG | ivideo->SiS310_AccelDepth)
पूर्ण

अटल व्योम
SiS310SubsequentSolidFillRect(काष्ठा sis_video_info *ivideo, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h)
अणु
	u32 dstbase = 0;

	अगर(y >= 2048) अणु
		dstbase = ivideo->video_linelength * y;
		y = 0;
	पूर्ण
	dstbase += ivideo->video_offset;
	SiS310SetupDSTBase(dstbase)
	SiS310SetupDSTXY(x,y)
	SiS310SetupRect(w,h)
	SiS310SetupCMDFlag(BITBLT)
	SiS310DoCMD
पूर्ण
#पूर्ण_अगर

/* --------------------------------------------------------------------- */

/* The exported routines */

पूर्णांक sisfb_initaccel(काष्ठा sis_video_info *ivideo)
अणु
#अगर_घोषित SISFB_USE_SPINLOCKS
	spin_lock_init(&ivideo->lockaccel);
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम sisfb_syncaccel(काष्ठा sis_video_info *ivideo)
अणु
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
#अगर_घोषित CONFIG_FB_SIS_300
		SiS300Sync(ivideo);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
		SiS310Sync(ivideo);
#पूर्ण_अगर
	पूर्ण
पूर्ण

पूर्णांक fbcon_sis_sync(काष्ठा fb_info *info)
अणु
	काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)info->par;
	CRITFLAGS

	अगर((!ivideo->accel) || (!ivideo->engineok))
		वापस 0;

	CRITBEGIN
	sisfb_syncaccel(ivideo);
	CRITEND

	वापस 0;
पूर्ण

व्योम fbcon_sis_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)info->par;
	u32 col = 0;
	u32 vxres = info->var.xres_भव;
	u32 vyres = info->var.yres_भव;
	पूर्णांक width, height;
	CRITFLAGS

	अगर(info->state != FBINFO_STATE_RUNNING)
		वापस;

	अगर((!ivideo->accel) || (!ivideo->engineok)) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	अगर(!rect->width || !rect->height || rect->dx >= vxres || rect->dy >= vyres)
		वापस;

	/* Clipping */
	width = ((rect->dx + rect->width) > vxres) ? (vxres - rect->dx) : rect->width;
	height = ((rect->dy + rect->height) > vyres) ? (vyres - rect->dy) : rect->height;

	चयन(info->var.bits_per_pixel) अणु
	हाल 8:  col = rect->color;
		 अवरोध;
	हाल 16:
	हाल 32: col = ((u32 *)(info->pseuकरो_palette))[rect->color];
		 अवरोध;
	पूर्ण

	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
#अगर_घोषित CONFIG_FB_SIS_300
		CRITBEGIN
		SiS300SetupForSolidFill(ivideo, col, myrops[rect->rop]);
		SiS300SubsequentSolidFillRect(ivideo, rect->dx, rect->dy, width, height);
		CRITEND
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
		CRITBEGIN
		SiS310SetupForSolidFill(ivideo, col, myrops[rect->rop]);
		SiS310SubsequentSolidFillRect(ivideo, rect->dx, rect->dy, width, height);
		CRITEND
#पूर्ण_अगर
	पूर्ण

	sisfb_syncaccel(ivideo);
पूर्ण

व्योम fbcon_sis_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)info->par;
	u32 vxres = info->var.xres_भव;
	u32 vyres = info->var.yres_भव;
	पूर्णांक width = area->width;
	पूर्णांक height = area->height;
	CRITFLAGS

	अगर(info->state != FBINFO_STATE_RUNNING)
		वापस;

	अगर((!ivideo->accel) || (!ivideo->engineok)) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	अगर(!width || !height ||
	   area->sx >= vxres || area->sy >= vyres ||
	   area->dx >= vxres || area->dy >= vyres)
		वापस;

	/* Clipping */
	अगर((area->sx + width) > vxres) width = vxres - area->sx;
	अगर((area->dx + width) > vxres) width = vxres - area->dx;
	अगर((area->sy + height) > vyres) height = vyres - area->sy;
	अगर((area->dy + height) > vyres) height = vyres - area->dy;

	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
#अगर_घोषित CONFIG_FB_SIS_300
		पूर्णांक xdir, ydir;

		अगर(area->sx < area->dx) xdir = 0;
		अन्यथा                    xdir = 1;
		अगर(area->sy < area->dy) ydir = 0;
		अन्यथा                    ydir = 1;

		CRITBEGIN
		SiS300SetupForScreenToScreenCopy(ivideo, xdir, ydir, 3, -1);
		SiS300SubsequentScreenToScreenCopy(ivideo, area->sx, area->sy,
					area->dx, area->dy, width, height);
		CRITEND
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
		CRITBEGIN
		SiS310SetupForScreenToScreenCopy(ivideo, 3, -1);
		SiS310SubsequentScreenToScreenCopy(ivideo, area->sx, area->sy,
					area->dx, area->dy, width, height);
		CRITEND
#पूर्ण_अगर
	पूर्ण

	sisfb_syncaccel(ivideo);
पूर्ण
