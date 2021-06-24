<शैली गुरु>
 /***************************************************************************\
|*                                                                           *|
|*       Copyright 1993-2003 NVIDIA, Corporation.  All rights reserved.      *|
|*                                                                           *|
|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|
|*     पूर्णांकernational laws.  Users and possessors of this source code are     *|
|*     hereby granted a nonexclusive,  royalty-मुक्त copyright license to     *|
|*     use this code in inभागidual and commercial software.                  *|
|*                                                                           *|
|*     Any use of this source code must include,  in the user करोcumenta-     *|
|*     tion and  पूर्णांकernal comments to the code,  notices to the end user     *|
|*     as follows:                                                           *|
|*                                                                           *|
|*       Copyright 1993-2003 NVIDIA, Corporation.  All rights reserved.      *|
|*                                                                           *|
|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|
|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  "AS IS"     *|
|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|
|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|
|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|
|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|
|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INसूचीECT,  INCI-     *|
|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|
|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|
|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|
|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|
|*                                                                           *|
|*     U.S. Government  End  Users.   This source code  is a "commercial     *|
|*     item,"  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|
|*     consisting  of "commercial  computer  software"  and  "commercial     *|
|*     computer  software  करोcumentation,"  as such  terms  are  used in     *|
|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|
|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|
|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|
|*     all U.S. Government End Users  acquire the source code  with only     *|
|*     those rights set क्रमth herein.                                        *|
|*                                                                           *|
 \***************************************************************************/

/*
 * GPL Licensing Note - According to Mark Vojkovich, author of the Xorg/
 * XFree86 'nv' driver, this source code is provided under MIT-style licensing
 * where the source code is provided "as is" without warranty of any kind.
 * The only usage restriction is क्रम the copyright notices to be retained
 * whenever code is used.
 *
 * Antonino Daplas <adaplas@pol.net> 2005-03-11
 */

#समावेश <linux/fb.h>
#समावेश <linux/nmi.h>

#समावेश "nv_type.h"
#समावेश "nv_proto.h"
#समावेश "nv_dma.h"
#समावेश "nv_local.h"

/* There is a HW race condition with videoram command buffers.
   You can't jump to the location of your put offset.  We ग_लिखो put
   at the jump offset + SKIPS dwords with noop padding in between
   to solve this problem */
#घोषणा SKIPS  8

अटल स्थिर पूर्णांक NVCopyROP[16] = अणु
	0xCC,			/* copy   */
	0x55			/* invert */
पूर्ण;

अटल स्थिर पूर्णांक NVCopyROP_PM[16] = अणु
	0xCA,			/* copy  */
	0x5A,			/* invert */
पूर्ण;

अटल अंतरभूत व्योम nvidiafb_safe_mode(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;

	touch_softlockup_watchकरोg();
	info->pixmap.scan_align = 1;
	par->lockup = 1;
पूर्ण

अटल अंतरभूत व्योम NVFlush(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	पूर्णांक count = 1000000000;

	जबतक (--count && READ_GET(par) != par->dmaPut) ;

	अगर (!count) अणु
		prपूर्णांकk("nvidiafb: DMA Flush lockup\n");
		nvidiafb_safe_mode(info);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम NVSync(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	पूर्णांक count = 1000000000;

	जबतक (--count && NV_RD32(par->PGRAPH, 0x0700)) ;

	अगर (!count) अणु
		prपूर्णांकk("nvidiafb: DMA Sync lockup\n");
		nvidiafb_safe_mode(info);
	पूर्ण
पूर्ण

अटल व्योम NVDmaKickoff(काष्ठा nvidia_par *par)
अणु
	अगर (par->dmaCurrent != par->dmaPut) अणु
		par->dmaPut = par->dmaCurrent;
		WRITE_PUT(par, par->dmaPut);
	पूर्ण
पूर्ण

अटल व्योम NVDmaWait(काष्ठा fb_info *info, पूर्णांक size)
अणु
	काष्ठा nvidia_par *par = info->par;
	पूर्णांक dmaGet;
	पूर्णांक count = 1000000000, cnt;
	size++;

	जबतक (par->dmaFree < size && --count && !par->lockup) अणु
		dmaGet = READ_GET(par);

		अगर (par->dmaPut >= dmaGet) अणु
			par->dmaFree = par->dmaMax - par->dmaCurrent;
			अगर (par->dmaFree < size) अणु
				NVDmaNext(par, 0x20000000);
				अगर (dmaGet <= SKIPS) अणु
					अगर (par->dmaPut <= SKIPS)
						WRITE_PUT(par, SKIPS + 1);
					cnt = 1000000000;
					करो अणु
						dmaGet = READ_GET(par);
					पूर्ण जबतक (--cnt && dmaGet <= SKIPS);
					अगर (!cnt) अणु
						prपूर्णांकk("DMA Get lockup\n");
						par->lockup = 1;
					पूर्ण
				पूर्ण
				WRITE_PUT(par, SKIPS);
				par->dmaCurrent = par->dmaPut = SKIPS;
				par->dmaFree = dmaGet - (SKIPS + 1);
			पूर्ण
		पूर्ण अन्यथा
			par->dmaFree = dmaGet - par->dmaCurrent - 1;
	पूर्ण

	अगर (!count) अणु
		prपूर्णांकk("nvidiafb: DMA Wait Lockup\n");
		nvidiafb_safe_mode(info);
	पूर्ण
पूर्ण

अटल व्योम NVSetPattern(काष्ठा fb_info *info, u32 clr0, u32 clr1,
			 u32 pat0, u32 pat1)
अणु
	काष्ठा nvidia_par *par = info->par;

	NVDmaStart(info, par, PATTERN_COLOR_0, 4);
	NVDmaNext(par, clr0);
	NVDmaNext(par, clr1);
	NVDmaNext(par, pat0);
	NVDmaNext(par, pat1);
पूर्ण

अटल व्योम NVSetRopSolid(काष्ठा fb_info *info, u32 rop, u32 planemask)
अणु
	काष्ठा nvidia_par *par = info->par;

	अगर (planemask != ~0) अणु
		NVSetPattern(info, 0, planemask, ~0, ~0);
		अगर (par->currentRop != (rop + 32)) अणु
			NVDmaStart(info, par, ROP_SET, 1);
			NVDmaNext(par, NVCopyROP_PM[rop]);
			par->currentRop = rop + 32;
		पूर्ण
	पूर्ण अन्यथा अगर (par->currentRop != rop) अणु
		अगर (par->currentRop >= 16)
			NVSetPattern(info, ~0, ~0, ~0, ~0);
		NVDmaStart(info, par, ROP_SET, 1);
		NVDmaNext(par, NVCopyROP[rop]);
		par->currentRop = rop;
	पूर्ण
पूर्ण

अटल व्योम NVSetClippingRectangle(काष्ठा fb_info *info, पूर्णांक x1, पूर्णांक y1,
				   पूर्णांक x2, पूर्णांक y2)
अणु
	काष्ठा nvidia_par *par = info->par;
	पूर्णांक h = y2 - y1 + 1;
	पूर्णांक w = x2 - x1 + 1;

	NVDmaStart(info, par, CLIP_POINT, 2);
	NVDmaNext(par, (y1 << 16) | x1);
	NVDmaNext(par, (h << 16) | w);
पूर्ण

व्योम NVResetGraphics(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	u32 surfaceFormat, patternFormat, rectFormat, lineFormat;
	पूर्णांक pitch, i;

	pitch = info->fix.line_length;

	par->dmaBase = (u32 __iomem *) (&par->FbStart[par->FbUsableSize]);

	क्रम (i = 0; i < SKIPS; i++)
		NV_WR32(&par->dmaBase[i], 0, 0x00000000);

	NV_WR32(&par->dmaBase[0x0 + SKIPS], 0, 0x00040000);
	NV_WR32(&par->dmaBase[0x1 + SKIPS], 0, 0x80000010);
	NV_WR32(&par->dmaBase[0x2 + SKIPS], 0, 0x00042000);
	NV_WR32(&par->dmaBase[0x3 + SKIPS], 0, 0x80000011);
	NV_WR32(&par->dmaBase[0x4 + SKIPS], 0, 0x00044000);
	NV_WR32(&par->dmaBase[0x5 + SKIPS], 0, 0x80000012);
	NV_WR32(&par->dmaBase[0x6 + SKIPS], 0, 0x00046000);
	NV_WR32(&par->dmaBase[0x7 + SKIPS], 0, 0x80000013);
	NV_WR32(&par->dmaBase[0x8 + SKIPS], 0, 0x00048000);
	NV_WR32(&par->dmaBase[0x9 + SKIPS], 0, 0x80000014);
	NV_WR32(&par->dmaBase[0xA + SKIPS], 0, 0x0004A000);
	NV_WR32(&par->dmaBase[0xB + SKIPS], 0, 0x80000015);
	NV_WR32(&par->dmaBase[0xC + SKIPS], 0, 0x0004C000);
	NV_WR32(&par->dmaBase[0xD + SKIPS], 0, 0x80000016);
	NV_WR32(&par->dmaBase[0xE + SKIPS], 0, 0x0004E000);
	NV_WR32(&par->dmaBase[0xF + SKIPS], 0, 0x80000017);

	par->dmaPut = 0;
	par->dmaCurrent = 16 + SKIPS;
	par->dmaMax = 8191;
	par->dmaFree = par->dmaMax - par->dmaCurrent;

	चयन (info->var.bits_per_pixel) अणु
	हाल 32:
	हाल 24:
		surfaceFormat = SURFACE_FORMAT_DEPTH24;
		patternFormat = PATTERN_FORMAT_DEPTH24;
		rectFormat = RECT_FORMAT_DEPTH24;
		lineFormat = LINE_FORMAT_DEPTH24;
		अवरोध;
	हाल 16:
		surfaceFormat = SURFACE_FORMAT_DEPTH16;
		patternFormat = PATTERN_FORMAT_DEPTH16;
		rectFormat = RECT_FORMAT_DEPTH16;
		lineFormat = LINE_FORMAT_DEPTH16;
		अवरोध;
	शेष:
		surfaceFormat = SURFACE_FORMAT_DEPTH8;
		patternFormat = PATTERN_FORMAT_DEPTH8;
		rectFormat = RECT_FORMAT_DEPTH8;
		lineFormat = LINE_FORMAT_DEPTH8;
		अवरोध;
	पूर्ण

	NVDmaStart(info, par, SURFACE_FORMAT, 4);
	NVDmaNext(par, surfaceFormat);
	NVDmaNext(par, pitch | (pitch << 16));
	NVDmaNext(par, 0);
	NVDmaNext(par, 0);

	NVDmaStart(info, par, PATTERN_FORMAT, 1);
	NVDmaNext(par, patternFormat);

	NVDmaStart(info, par, RECT_FORMAT, 1);
	NVDmaNext(par, rectFormat);

	NVDmaStart(info, par, LINE_FORMAT, 1);
	NVDmaNext(par, lineFormat);

	par->currentRop = ~0;	/* set to something invalid */
	NVSetRopSolid(info, ROP_COPY, ~0);

	NVSetClippingRectangle(info, 0, 0, info->var.xres_भव,
			       info->var.yres_भव);

	NVDmaKickoff(par);
पूर्ण

पूर्णांक nvidiafb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस 0;

	अगर (!par->lockup)
		NVFlush(info);

	अगर (!par->lockup)
		NVSync(info);

	वापस 0;
पूर्ण

व्योम nvidiafb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region)
अणु
	काष्ठा nvidia_par *par = info->par;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;

	अगर (par->lockup) अणु
		cfb_copyarea(info, region);
		वापस;
	पूर्ण

	NVDmaStart(info, par, BLIT_POINT_SRC, 3);
	NVDmaNext(par, (region->sy << 16) | region->sx);
	NVDmaNext(par, (region->dy << 16) | region->dx);
	NVDmaNext(par, (region->height << 16) | region->width);

	NVDmaKickoff(par);
पूर्ण

व्योम nvidiafb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा nvidia_par *par = info->par;
	u32 color;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;

	अगर (par->lockup) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	अगर (info->var.bits_per_pixel == 8)
		color = rect->color;
	अन्यथा
		color = ((u32 *) info->pseuकरो_palette)[rect->color];

	अगर (rect->rop != ROP_COPY)
		NVSetRopSolid(info, rect->rop, ~0);

	NVDmaStart(info, par, RECT_SOLID_COLOR, 1);
	NVDmaNext(par, color);

	NVDmaStart(info, par, RECT_SOLID_RECTS(0), 2);
	NVDmaNext(par, (rect->dx << 16) | rect->dy);
	NVDmaNext(par, (rect->width << 16) | rect->height);

	NVDmaKickoff(par);

	अगर (rect->rop != ROP_COPY)
		NVSetRopSolid(info, ROP_COPY, ~0);
पूर्ण

अटल व्योम nvidiafb_mono_color_expand(काष्ठा fb_info *info,
				       स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा nvidia_par *par = info->par;
	u32 fg, bg, mask = ~(~0 >> (32 - info->var.bits_per_pixel));
	u32 dsize, width, *data = (u32 *) image->data, पंचांगp;
	पूर्णांक j, k = 0;

	width = (image->width + 31) & ~31;
	dsize = (width * image->height) >> 5;

	अगर (info->var.bits_per_pixel == 8) अणु
		fg = image->fg_color | mask;
		bg = image->bg_color | mask;
	पूर्ण अन्यथा अणु
		fg = ((u32 *) info->pseuकरो_palette)[image->fg_color] | mask;
		bg = ((u32 *) info->pseuकरो_palette)[image->bg_color] | mask;
	पूर्ण

	NVDmaStart(info, par, RECT_EXPAND_TWO_COLOR_CLIP, 7);
	NVDmaNext(par, (image->dy << 16) | (image->dx & 0xffff));
	NVDmaNext(par, ((image->dy + image->height) << 16) |
		  ((image->dx + image->width) & 0xffff));
	NVDmaNext(par, bg);
	NVDmaNext(par, fg);
	NVDmaNext(par, (image->height << 16) | width);
	NVDmaNext(par, (image->height << 16) | width);
	NVDmaNext(par, (image->dy << 16) | (image->dx & 0xffff));

	जबतक (dsize >= RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS) अणु
		NVDmaStart(info, par, RECT_EXPAND_TWO_COLOR_DATA(0),
			   RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS);

		क्रम (j = RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS; j--;) अणु
			पंचांगp = data[k++];
			reverse_order(&पंचांगp);
			NVDmaNext(par, पंचांगp);
		पूर्ण

		dsize -= RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS;
	पूर्ण

	अगर (dsize) अणु
		NVDmaStart(info, par, RECT_EXPAND_TWO_COLOR_DATA(0), dsize);

		क्रम (j = dsize; j--;) अणु
			पंचांगp = data[k++];
			reverse_order(&पंचांगp);
			NVDmaNext(par, पंचांगp);
		पूर्ण
	पूर्ण

	NVDmaKickoff(par);
पूर्ण

व्योम nvidiafb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा nvidia_par *par = info->par;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;

	अगर (image->depth == 1 && !par->lockup)
		nvidiafb_mono_color_expand(info, image);
	अन्यथा
		cfb_imageblit(info, image);
पूर्ण
