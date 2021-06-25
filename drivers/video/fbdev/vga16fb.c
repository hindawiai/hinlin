<शैली गुरु>
/*
 * linux/drivers/video/vga16.c -- VGA 16-color framebuffer driver
 * 
 * Copyright 1999 Ben Pfaff <pfaffben@debian.org> and Petr Vandrovec <VANDROVE@vc.cvut.cz>
 * Based on VGA info at http://www.goodnet.com/~tinara/FreeVGA/home.hपंचांग
 * Based on VESA framebuffer (c) 1998 Gerd Knorr <kraxel@goldbach.in-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.  
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

#समावेश <यंत्र/पन.स>
#समावेश <video/vga.h>

#घोषणा VGA_FB_PHYS 0xA0000
#घोषणा VGA_FB_PHYS_LEN 65536

#घोषणा MODE_SKIP4	1
#घोषणा MODE_8BPP	2
#घोषणा MODE_CFB	4
#घोषणा MODE_TEXT	8

/* --------------------------------------------------------------------- */

/*
 * card parameters
 */

काष्ठा vga16fb_par अणु
	/* काष्ठाure holding original VGA रेजिस्टर settings when the
           screen is blanked */
	काष्ठा अणु
		अचिन्हित अक्षर	SeqCtrlIndex;	  /* Sequencer Index reg.   */
		अचिन्हित अक्षर	CrtCtrlIndex;	  /* CRT-Contr. Index reg.  */
		अचिन्हित अक्षर	CrtMiscIO;	  /* Miscellaneous रेजिस्टर */
		अचिन्हित अक्षर	HorizontalTotal;  /* CRT-Controller:00h */
		अचिन्हित अक्षर	HorizDisplayEnd;  /* CRT-Controller:01h */
		अचिन्हित अक्षर	StartHorizRetrace;/* CRT-Controller:04h */
		अचिन्हित अक्षर	EndHorizRetrace;  /* CRT-Controller:05h */
		अचिन्हित अक्षर	Overflow;	  /* CRT-Controller:07h */
		अचिन्हित अक्षर	StartVertRetrace; /* CRT-Controller:10h */
		अचिन्हित अक्षर	EndVertRetrace;	  /* CRT-Controller:11h */
		अचिन्हित अक्षर	ModeControl;	  /* CRT-Controller:17h */
		अचिन्हित अक्षर	ClockingMode;	  /* Seq-Controller:01h */
	पूर्ण vga_state;
	काष्ठा vgastate state;
	अचिन्हित पूर्णांक ref_count;
	पूर्णांक palette_blanked, vesa_blanked, mode, isVGA;
	u8 misc, pel_msk, vss, clkभाग;
	u8 crtc[VGA_CRT_C];
पूर्ण;

/* --------------------------------------------------------------------- */

अटल काष्ठा fb_var_screeninfo vga16fb_defined = अणु
	.xres		= 640,
	.yres		= 480,
	.xres_भव	= 640,
	.yres_भव	= 480,
	.bits_per_pixel	= 4,	
	.activate	= FB_ACTIVATE_TEST,
	.height		= -1,
	.width		= -1,
	.pixघड़ी	= 39721,
	.left_margin	= 48,
	.right_margin	= 16,
	.upper_margin	= 33,
	.lower_margin	= 10,
	.hsync_len 	= 96,
	.vsync_len	= 2,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

/* name should not depend on EGA/VGA */
अटल स्थिर काष्ठा fb_fix_screeninfo vga16fb_fix = अणु
	.id		= "VGA16 VGA",
	.smem_start	= VGA_FB_PHYS,
	.smem_len	= VGA_FB_PHYS_LEN,
	.type		= FB_TYPE_VGA_PLANES,
	.type_aux	= FB_AUX_VGA_PLANES_VGA4,
	.visual		= FB_VISUAL_PSEUDOCOLOR,
	.xpanstep	= 8,
	.ypanstep	= 1,
	.line_length	= 640 / 8,
	.accel		= FB_ACCEL_NONE
पूर्ण;

/* The VGA's weird architecture often requires that we पढ़ो a byte and
   ग_लिखो a byte to the same location.  It करोesn't matter *what* byte
   we ग_लिखो, however.  This is because all the action goes on behind
   the scenes in the VGA's 32-bit latch रेजिस्टर, and पढ़ोing and writing
   video memory just invokes latch behavior.

   To aव्योम race conditions (is this necessary?), पढ़ोing and writing
   the memory byte should be करोne with a single inकाष्ठाion.  One
   suitable inकाष्ठाion is the x86 bitwise OR.  The following
   पढ़ो-modअगरy-ग_लिखो routine should optimize to one such bitwise
   OR. */
अटल अंतरभूत व्योम rmw(अस्थिर अक्षर __iomem *p)
अणु
	पढ़ोb(p);
	ग_लिखोb(1, p);
पूर्ण

/* Set the Graphics Mode Register, and वापस its previous value.
   Bits 0-1 are ग_लिखो mode, bit 3 is पढ़ो mode. */
अटल अंतरभूत पूर्णांक seपंचांगode(पूर्णांक mode)
अणु
	पूर्णांक oldmode;
	
	oldmode = vga_io_rgfx(VGA_GFX_MODE);
	vga_io_w(VGA_GFX_D, mode);
	वापस oldmode;
पूर्ण

/* Select the Bit Mask Register and वापस its value. */
अटल अंतरभूत पूर्णांक selecपंचांगask(व्योम)
अणु
	वापस vga_io_rgfx(VGA_GFX_BIT_MASK);
पूर्ण

/* Set the value of the Bit Mask Register.  It must alपढ़ोy have been
   selected with selecपंचांगask(). */
अटल अंतरभूत व्योम seपंचांगask(पूर्णांक mask)
अणु
	vga_io_w(VGA_GFX_D, mask);
पूर्ण

/* Set the Data Rotate Register and वापस its old value. 
   Bits 0-2 are rotate count, bits 3-4 are logical operation
   (0=NOP, 1=AND, 2=OR, 3=XOR). */
अटल अंतरभूत पूर्णांक setop(पूर्णांक op)
अणु
	पूर्णांक olकरोp;
	
	olकरोp = vga_io_rgfx(VGA_GFX_DATA_ROTATE);
	vga_io_w(VGA_GFX_D, op);
	वापस olकरोp;
पूर्ण

/* Set the Enable Set/Reset Register and वापस its old value.  
   The code here always uses value 0xf क्रम this रेजिस्टर. */
अटल अंतरभूत पूर्णांक setsr(पूर्णांक sr)
अणु
	पूर्णांक oldsr;

	oldsr = vga_io_rgfx(VGA_GFX_SR_ENABLE);
	vga_io_w(VGA_GFX_D, sr);
	वापस oldsr;
पूर्ण

/* Set the Set/Reset Register and वापस its old value. */
अटल अंतरभूत पूर्णांक setcolor(पूर्णांक color)
अणु
	पूर्णांक oldcolor;

	oldcolor = vga_io_rgfx(VGA_GFX_SR_VALUE);
	vga_io_w(VGA_GFX_D, color);
	वापस oldcolor;
पूर्ण

/* Return the value in the Graphics Address Register. */
अटल अंतरभूत पूर्णांक getindex(व्योम)
अणु
	वापस vga_io_r(VGA_GFX_I);
पूर्ण

/* Set the value in the Graphics Address Register. */
अटल अंतरभूत व्योम setindex(पूर्णांक index)
अणु
	vga_io_w(VGA_GFX_I, index);
पूर्ण

अटल व्योम vga16fb_pan_var(काष्ठा fb_info *info, 
			    काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा vga16fb_par *par = info->par;
	u32 xoffset, pos;

	xoffset = var->xoffset;
	अगर (info->var.bits_per_pixel == 8) अणु
		pos = (info->var.xres_भव * var->yoffset + xoffset) >> 2;
	पूर्ण अन्यथा अगर (par->mode & MODE_TEXT) अणु
		पूर्णांक fh = 16; // FIXME !!! font height. Fugde क्रम now.
		pos = (info->var.xres_भव * (var->yoffset / fh) + xoffset) >> 3;
	पूर्ण अन्यथा अणु
		अगर (info->var.nonstd)
			xoffset--;
		pos = (info->var.xres_भव * var->yoffset + xoffset) >> 3;
	पूर्ण
	vga_io_wcrt(VGA_CRTC_START_HI, pos >> 8);
	vga_io_wcrt(VGA_CRTC_START_LO, pos & 0xFF);
	/* अगर we support CFB4, then we must! support xoffset with pixel
	 * granularity अगर someone supports xoffset in bit resolution */
	vga_io_r(VGA_IS1_RC);		/* reset flip-flop */
	vga_io_w(VGA_ATT_IW, VGA_ATC_PEL);
	अगर (info->var.bits_per_pixel == 8)
		vga_io_w(VGA_ATT_IW, (xoffset & 3) << 1);
	अन्यथा
		vga_io_w(VGA_ATT_IW, xoffset & 7);
	vga_io_r(VGA_IS1_RC);
	vga_io_w(VGA_ATT_IW, 0x20);
पूर्ण

अटल व्योम vga16fb_update_fix(काष्ठा fb_info *info)
अणु
	अगर (info->var.bits_per_pixel == 4) अणु
		अगर (info->var.nonstd) अणु
			info->fix.type = FB_TYPE_PACKED_PIXELS;
			info->fix.line_length = info->var.xres_भव / 2;
		पूर्ण अन्यथा अणु
			info->fix.type = FB_TYPE_VGA_PLANES;
			info->fix.type_aux = FB_AUX_VGA_PLANES_VGA4;
			info->fix.line_length = info->var.xres_भव / 8;
		पूर्ण
	पूर्ण अन्यथा अगर (info->var.bits_per_pixel == 0) अणु
		info->fix.type = FB_TYPE_TEXT;
		info->fix.type_aux = FB_AUX_TEXT_CGA;
		info->fix.line_length = info->var.xres_भव / 4;
	पूर्ण अन्यथा अणु	/* 8bpp */
		अगर (info->var.nonstd) अणु
			info->fix.type = FB_TYPE_VGA_PLANES;
			info->fix.type_aux = FB_AUX_VGA_PLANES_CFB8;
			info->fix.line_length = info->var.xres_भव / 4;
		पूर्ण अन्यथा अणु
			info->fix.type = FB_TYPE_PACKED_PIXELS;
			info->fix.line_length = info->var.xres_भव;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम vga16fb_घड़ी_chip(काष्ठा vga16fb_par *par,
			       अचिन्हित पूर्णांक *pixघड़ी,
			       स्थिर काष्ठा fb_info *info,
			       पूर्णांक mul, पूर्णांक भाग)
अणु
	अटल स्थिर काष्ठा अणु
		u32 pixघड़ी;
		u8  misc;
		u8  seq_घड़ी_mode;
	पूर्ण *ptr, *best, vgaघड़ीs[] = अणु
		अणु 79442 /* 12.587 */, 0x00, 0x08पूर्ण,
		अणु 70616 /* 14.161 */, 0x04, 0x08पूर्ण,
		अणु 39721 /* 25.175 */, 0x00, 0x00पूर्ण,
		अणु 35308 /* 28.322 */, 0x04, 0x00पूर्ण,
		अणु     0 /* bad */,    0x00, 0x00पूर्णपूर्ण;
	पूर्णांक err;

	*pixघड़ी = (*pixघड़ी * mul) / भाग;
	best = vgaघड़ीs;
	err = *pixघड़ी - best->pixघड़ी;
	अगर (err < 0) err = -err;
	क्रम (ptr = vgaघड़ीs + 1; ptr->pixघड़ी; ptr++) अणु
		पूर्णांक पंचांगp;

		पंचांगp = *pixघड़ी - ptr->pixघड़ी;
		अगर (पंचांगp < 0) पंचांगp = -पंचांगp;
		अगर (पंचांगp < err) अणु
			err = पंचांगp;
			best = ptr;
		पूर्ण
	पूर्ण
	par->misc |= best->misc;
	par->clkभाग = best->seq_घड़ी_mode;
	*pixघड़ी = (best->pixघड़ी * भाग) / mul;
पूर्ण
			       
#घोषणा FAIL(X) वापस -EINVAL

अटल पूर्णांक vga16fb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा vga16fb_par *par = info->par;

	अगर (!par->ref_count) अणु
		स_रखो(&par->state, 0, माप(काष्ठा vgastate));
		par->state.flags = VGA_SAVE_FONTS | VGA_SAVE_MODE |
			VGA_SAVE_CMAP;
		save_vga(&par->state);
	पूर्ण
	par->ref_count++;

	वापस 0;
पूर्ण

अटल पूर्णांक vga16fb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा vga16fb_par *par = info->par;

	अगर (!par->ref_count)
		वापस -EINVAL;

	अगर (par->ref_count == 1)
		restore_vga(&par->state);
	par->ref_count--;

	वापस 0;
पूर्ण

अटल पूर्णांक vga16fb_check_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा vga16fb_par *par = info->par;
	u32 xres, right, hslen, left, xtotal;
	u32 yres, lower, vslen, upper, ytotal;
	u32 vxres, xoffset, vyres, yoffset;
	u32 pos;
	u8 r7, rMode;
	पूर्णांक shअगरt;
	पूर्णांक mode;
	u32 maxmem;

	par->pel_msk = 0xFF;

	अगर (var->bits_per_pixel == 4) अणु
		अगर (var->nonstd) अणु
			अगर (!par->isVGA)
				वापस -EINVAL;
			shअगरt = 3;
			mode = MODE_SKIP4 | MODE_CFB;
			maxmem = 16384;
			par->pel_msk = 0x0F;
		पूर्ण अन्यथा अणु
			shअगरt = 3;
			mode = 0;
			maxmem = 65536;
		पूर्ण
	पूर्ण अन्यथा अगर (var->bits_per_pixel == 8) अणु
		अगर (!par->isVGA)
			वापस -EINVAL;	/* no support on EGA */
		shअगरt = 2;
		अगर (var->nonstd) अणु
			mode = MODE_8BPP | MODE_CFB;
			maxmem = 65536;
		पूर्ण अन्यथा अणु
			mode = MODE_SKIP4 | MODE_8BPP | MODE_CFB;
			maxmem = 16384;
		पूर्ण
	पूर्ण अन्यथा
		वापस -EINVAL;

	xres = (var->xres + 7) & ~7;
	vxres = (var->xres_भव + 0xF) & ~0xF;
	xoffset = (var->xoffset + 7) & ~7;
	left = (var->left_margin + 7) & ~7;
	right = (var->right_margin + 7) & ~7;
	hslen = (var->hsync_len + 7) & ~7;

	अगर (vxres < xres)
		vxres = xres;
	अगर (xres + xoffset > vxres)
		xoffset = vxres - xres;

	var->xres = xres;
	var->right_margin = right;
	var->hsync_len = hslen;
	var->left_margin = left;
	var->xres_भव = vxres;
	var->xoffset = xoffset;

	xres >>= shअगरt;
	right >>= shअगरt;
	hslen >>= shअगरt;
	left >>= shअगरt;
	vxres >>= shअगरt;
	xtotal = xres + right + hslen + left;
	अगर (xtotal >= 256)
		FAIL("xtotal too big");
	अगर (hslen > 32)
		FAIL("hslen too big");
	अगर (right + hslen + left > 64)
		FAIL("hblank too big");
	par->crtc[VGA_CRTC_H_TOTAL] = xtotal - 5;
	par->crtc[VGA_CRTC_H_BLANK_START] = xres - 1;
	par->crtc[VGA_CRTC_H_DISP] = xres - 1;
	pos = xres + right;
	par->crtc[VGA_CRTC_H_SYNC_START] = pos;
	pos += hslen;
	par->crtc[VGA_CRTC_H_SYNC_END] = pos & 0x1F;
	pos += left - 2; /* blank_end + 2 <= total + 5 */
	par->crtc[VGA_CRTC_H_BLANK_END] = (pos & 0x1F) | 0x80;
	अगर (pos & 0x20)
		par->crtc[VGA_CRTC_H_SYNC_END] |= 0x80;

	yres = var->yres;
	lower = var->lower_margin;
	vslen = var->vsync_len;
	upper = var->upper_margin;
	vyres = var->yres_भव;
	yoffset = var->yoffset;

	अगर (yres > vyres)
		vyres = yres;
	अगर (vxres * vyres > maxmem) अणु
		vyres = maxmem / vxres;
		अगर (vyres < yres)
			वापस -ENOMEM;
	पूर्ण
	अगर (yoffset + yres > vyres)
		yoffset = vyres - yres;
	var->yres = yres;
	var->lower_margin = lower;
	var->vsync_len = vslen;
	var->upper_margin = upper;
	var->yres_भव = vyres;
	var->yoffset = yoffset;

	अगर (var->vmode & FB_VMODE_DOUBLE) अणु
		yres <<= 1;
		lower <<= 1;
		vslen <<= 1;
		upper <<= 1;
	पूर्ण
	ytotal = yres + lower + vslen + upper;
	अगर (ytotal > 1024) अणु
		ytotal >>= 1;
		yres >>= 1;
		lower >>= 1;
		vslen >>= 1;
		upper >>= 1;
		rMode = 0x04;
	पूर्ण अन्यथा
		rMode = 0x00;
	अगर (ytotal > 1024)
		FAIL("ytotal too big");
	अगर (vslen > 16)
		FAIL("vslen too big");
	par->crtc[VGA_CRTC_V_TOTAL] = ytotal - 2;
	r7 = 0x10;	/* disable linecompare */
	अगर (ytotal & 0x100) r7 |= 0x01;
	अगर (ytotal & 0x200) r7 |= 0x20;
	par->crtc[VGA_CRTC_PRESET_ROW] = 0;
	par->crtc[VGA_CRTC_MAX_SCAN] = 0x40;	/* 1 scanline, no linecmp */
	अगर (var->vmode & FB_VMODE_DOUBLE)
		par->crtc[VGA_CRTC_MAX_SCAN] |= 0x80;
	par->crtc[VGA_CRTC_CURSOR_START] = 0x20;
	par->crtc[VGA_CRTC_CURSOR_END]   = 0x00;
	अगर ((mode & (MODE_CFB | MODE_8BPP)) == MODE_CFB)
		xoffset--;
	pos = yoffset * vxres + (xoffset >> shअगरt);
	par->crtc[VGA_CRTC_START_HI]     = pos >> 8;
	par->crtc[VGA_CRTC_START_LO]     = pos & 0xFF;
	par->crtc[VGA_CRTC_CURSOR_HI]    = 0x00;
	par->crtc[VGA_CRTC_CURSOR_LO]    = 0x00;
	pos = yres - 1;
	par->crtc[VGA_CRTC_V_DISP_END] = pos & 0xFF;
	par->crtc[VGA_CRTC_V_BLANK_START] = pos & 0xFF;
	अगर (pos & 0x100)
		r7 |= 0x0A;	/* 0x02 -> DISP_END, 0x08 -> BLANK_START */
	अगर (pos & 0x200) अणु
		r7 |= 0x40;	/* 0x40 -> DISP_END */
		par->crtc[VGA_CRTC_MAX_SCAN] |= 0x20; /* BLANK_START */
	पूर्ण
	pos += lower;
	par->crtc[VGA_CRTC_V_SYNC_START] = pos & 0xFF;
	अगर (pos & 0x100)
		r7 |= 0x04;
	अगर (pos & 0x200)
		r7 |= 0x80;
	pos += vslen;
	par->crtc[VGA_CRTC_V_SYNC_END] = (pos & 0x0F) & ~0x10; /* disabled IRQ */
	pos += upper - 1; /* blank_end + 1 <= ytotal + 2 */
	par->crtc[VGA_CRTC_V_BLANK_END] = pos & 0xFF; /* 0x7F क्रम original VGA,
                     but some SVGA chips requires all 8 bits to set */
	अगर (vxres >= 512)
		FAIL("vxres too long");
	par->crtc[VGA_CRTC_OFFSET] = vxres >> 1;
	अगर (mode & MODE_SKIP4)
		par->crtc[VGA_CRTC_UNDERLINE] = 0x5F;	/* 256, cfb8 */
	अन्यथा
		par->crtc[VGA_CRTC_UNDERLINE] = 0x1F;	/* 16, vgap */
	par->crtc[VGA_CRTC_MODE] = rMode | ((mode & MODE_TEXT) ? 0xA3 : 0xE3);
	par->crtc[VGA_CRTC_LINE_COMPARE] = 0xFF;
	par->crtc[VGA_CRTC_OVERFLOW] = r7;

	par->vss = 0x00;	/* 3DA */

	par->misc = 0xE3;	/* enable CPU, ports 0x3Dx, positive sync */
	अगर (var->sync & FB_SYNC_HOR_HIGH_ACT)
		par->misc &= ~0x40;
	अगर (var->sync & FB_SYNC_VERT_HIGH_ACT)
		par->misc &= ~0x80;
	
	par->mode = mode;

	अगर (mode & MODE_8BPP)
		/* pixel घड़ी == vga घड़ी / 2 */
		vga16fb_घड़ी_chip(par, &var->pixघड़ी, info, 1, 2);
	अन्यथा
		/* pixel घड़ी == vga घड़ी */
		vga16fb_घड़ी_chip(par, &var->pixघड़ी, info, 1, 1);
	
	var->red.offset = var->green.offset = var->blue.offset = 
	var->transp.offset = 0;
	var->red.length = var->green.length = var->blue.length =
		(par->isVGA) ? 6 : 2;
	var->transp.length = 0;
	var->activate = FB_ACTIVATE_NOW;
	var->height = -1;
	var->width = -1;
	var->accel_flags = 0;
	वापस 0;
पूर्ण
#अघोषित FAIL

अटल पूर्णांक vga16fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा vga16fb_par *par = info->par;
	u8 gdc[VGA_GFX_C];
	u8 seq[VGA_SEQ_C];
	u8 atc[VGA_ATT_C];
	पूर्णांक fh, i;

	seq[VGA_SEQ_CLOCK_MODE] = 0x01 | par->clkभाग;
	अगर (par->mode & MODE_TEXT)
		seq[VGA_SEQ_PLANE_WRITE] = 0x03;
	अन्यथा
		seq[VGA_SEQ_PLANE_WRITE] = 0x0F;
	seq[VGA_SEQ_CHARACTER_MAP] = 0x00;
	अगर (par->mode & MODE_TEXT)
		seq[VGA_SEQ_MEMORY_MODE] = 0x03;
	अन्यथा अगर (par->mode & MODE_SKIP4)
		seq[VGA_SEQ_MEMORY_MODE] = 0x0E;
	अन्यथा
		seq[VGA_SEQ_MEMORY_MODE] = 0x06;

	gdc[VGA_GFX_SR_VALUE] = 0x00;
	gdc[VGA_GFX_SR_ENABLE] = 0x00;
	gdc[VGA_GFX_COMPARE_VALUE] = 0x00;
	gdc[VGA_GFX_DATA_ROTATE] = 0x00;
	gdc[VGA_GFX_PLANE_READ] = 0;
	अगर (par->mode & MODE_TEXT) अणु
		gdc[VGA_GFX_MODE] = 0x10;
		gdc[VGA_GFX_MISC] = 0x06;
	पूर्ण अन्यथा अणु
		अगर (par->mode & MODE_CFB)
			gdc[VGA_GFX_MODE] = 0x40;
		अन्यथा
			gdc[VGA_GFX_MODE] = 0x00;
		gdc[VGA_GFX_MISC] = 0x05;
	पूर्ण
	gdc[VGA_GFX_COMPARE_MASK] = 0x0F;
	gdc[VGA_GFX_BIT_MASK] = 0xFF;

	क्रम (i = 0x00; i < 0x10; i++)
		atc[i] = i;
	अगर (par->mode & MODE_TEXT)
		atc[VGA_ATC_MODE] = 0x04;
	अन्यथा अगर (par->mode & MODE_8BPP)
		atc[VGA_ATC_MODE] = 0x41;
	अन्यथा
		atc[VGA_ATC_MODE] = 0x81;
	atc[VGA_ATC_OVERSCAN] = 0x00;	/* 0 क्रम EGA, 0xFF क्रम VGA */
	atc[VGA_ATC_PLANE_ENABLE] = 0x0F;
	अगर (par->mode & MODE_8BPP)
		atc[VGA_ATC_PEL] = (info->var.xoffset & 3) << 1;
	अन्यथा
		atc[VGA_ATC_PEL] = info->var.xoffset & 7;
	atc[VGA_ATC_COLOR_PAGE] = 0x00;
	
	अगर (par->mode & MODE_TEXT) अणु
		fh = 16; // FIXME !!! Fudge font height. 
		par->crtc[VGA_CRTC_MAX_SCAN] = (par->crtc[VGA_CRTC_MAX_SCAN] 
					       & ~0x1F) | (fh - 1);
	पूर्ण

	vga_io_w(VGA_MIS_W, vga_io_r(VGA_MIS_R) | 0x01);

	/* Enable graphics रेजिस्टर modअगरication */
	अगर (!par->isVGA) अणु
		vga_io_w(EGA_GFX_E0, 0x00);
		vga_io_w(EGA_GFX_E1, 0x01);
	पूर्ण
	
	/* update misc output रेजिस्टर */
	vga_io_w(VGA_MIS_W, par->misc);
	
	/* synchronous reset on */
	vga_io_wseq(0x00, 0x01);

	अगर (par->isVGA)
		vga_io_w(VGA_PEL_MSK, par->pel_msk);

	/* ग_लिखो sequencer रेजिस्टरs */
	vga_io_wseq(VGA_SEQ_CLOCK_MODE, seq[VGA_SEQ_CLOCK_MODE] | 0x20);
	क्रम (i = 2; i < VGA_SEQ_C; i++) अणु
		vga_io_wseq(i, seq[i]);
	पूर्ण
	
	/* synchronous reset off */
	vga_io_wseq(0x00, 0x03);

	/* deprotect CRT रेजिस्टरs 0-7 */
	vga_io_wcrt(VGA_CRTC_V_SYNC_END, par->crtc[VGA_CRTC_V_SYNC_END]);

	/* ग_लिखो CRT रेजिस्टरs */
	क्रम (i = 0; i < VGA_CRTC_REGS; i++) अणु
		vga_io_wcrt(i, par->crtc[i]);
	पूर्ण
	
	/* ग_लिखो graphics controller रेजिस्टरs */
	क्रम (i = 0; i < VGA_GFX_C; i++) अणु
		vga_io_wgfx(i, gdc[i]);
	पूर्ण
	
	/* ग_लिखो attribute controller रेजिस्टरs */
	क्रम (i = 0; i < VGA_ATT_C; i++) अणु
		vga_io_r(VGA_IS1_RC);		/* reset flip-flop */
		vga_io_wattr(i, atc[i]);
	पूर्ण

	/* Wait क्रम screen to stabilize. */
	mdelay(50);

	vga_io_wseq(VGA_SEQ_CLOCK_MODE, seq[VGA_SEQ_CLOCK_MODE]);

	vga_io_r(VGA_IS1_RC);
	vga_io_w(VGA_ATT_IW, 0x20);

	vga16fb_update_fix(info);
	वापस 0;
पूर्ण

अटल व्योम ega16_setpalette(पूर्णांक regno, अचिन्हित red, अचिन्हित green, अचिन्हित blue)
अणु
	अटल स्थिर अचिन्हित अक्षर map[] = अणु 000, 001, 010, 011 पूर्ण;
	पूर्णांक val;
	
	अगर (regno >= 16)
		वापस;
	val = map[red>>14] | ((map[green>>14]) << 1) | ((map[blue>>14]) << 2);
	vga_io_r(VGA_IS1_RC);   /* ! 0x3BA */
	vga_io_wattr(regno, val);
	vga_io_r(VGA_IS1_RC);   /* some clones need it */
	vga_io_w(VGA_ATT_IW, 0x20); /* unblank screen */
पूर्ण

अटल व्योम vga16_setpalette(पूर्णांक regno, अचिन्हित red, अचिन्हित green, अचिन्हित blue)
अणु
	outb(regno,       VGA_PEL_IW);
	outb(red   >> 10, VGA_PEL_D);
	outb(green >> 10, VGA_PEL_D);
	outb(blue  >> 10, VGA_PEL_D);
पूर्ण

अटल पूर्णांक vga16fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			     अचिन्हित blue, अचिन्हित transp,
			     काष्ठा fb_info *info)
अणु
	काष्ठा vga16fb_par *par = info->par;
	पूर्णांक gray;

	/*
	 *  Set a single color रेजिस्टर. The values supplied are
	 *  alपढ़ोy rounded करोwn to the hardware's capabilities
	 *  (according to the entries in the `var' काष्ठाure). Return
	 *  != 0 क्रम invalid regno.
	 */
	
	अगर (regno >= 256)
		वापस 1;

	gray = info->var.grayscale;
	
	अगर (gray) अणु
		/* gray = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण
	अगर (par->isVGA) 
		vga16_setpalette(regno,red,green,blue);
	अन्यथा
		ega16_setpalette(regno,red,green,blue);
	वापस 0;
पूर्ण

अटल पूर्णांक vga16fb_pan_display(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *info) 
अणु
	vga16fb_pan_var(info, var);
	वापस 0;
पूर्ण

/* The following VESA blanking code is taken from vgacon.c.  The VGA
   blanking code was originally by Huang shi chao, and modअगरied by
   Christoph Rimek (chrimek@toppoपूर्णांक.de) and todd j. derr
   (tjd@barefoot.org) क्रम Linux. */

अटल व्योम vga_vesa_blank(काष्ठा vga16fb_par *par, पूर्णांक mode)
अणु
	अचिन्हित अक्षर SeqCtrlIndex = vga_io_r(VGA_SEQ_I);
	अचिन्हित अक्षर CrtCtrlIndex = vga_io_r(VGA_CRT_IC);
	
	/* save original values of VGA controller रेजिस्टरs */
	अगर(!par->vesa_blanked) अणु
		par->vga_state.CrtMiscIO = vga_io_r(VGA_MIS_R);
		//sti();

		par->vga_state.HorizontalTotal = vga_io_rcrt(0x00);	/* HorizontalTotal */
		par->vga_state.HorizDisplayEnd = vga_io_rcrt(0x01);	/* HorizDisplayEnd */
		par->vga_state.StartHorizRetrace = vga_io_rcrt(0x04);	/* StartHorizRetrace */
		par->vga_state.EndHorizRetrace = vga_io_rcrt(0x05);	/* EndHorizRetrace */
		par->vga_state.Overflow = vga_io_rcrt(0x07);		/* Overflow */
		par->vga_state.StartVertRetrace = vga_io_rcrt(0x10);	/* StartVertRetrace */
		par->vga_state.EndVertRetrace = vga_io_rcrt(0x11);	/* EndVertRetrace */
		par->vga_state.ModeControl = vga_io_rcrt(0x17);	/* ModeControl */
		par->vga_state.ClockingMode = vga_io_rseq(0x01);	/* ClockingMode */
	पूर्ण

	/* assure that video is enabled */
	/* "0x20" is VIDEO_ENABLE_bit in रेजिस्टर 01 of sequencer */
	vga_io_wseq(0x01, par->vga_state.ClockingMode | 0x20);

	/* test क्रम vertical retrace in process.... */
	अगर ((par->vga_state.CrtMiscIO & 0x80) == 0x80)
		vga_io_w(VGA_MIS_W, par->vga_state.CrtMiscIO & 0xef);

	/*
	 * Set <End of vertical retrace> to minimum (0) and
	 * <Start of vertical Retrace> to maximum (incl. overflow)
	 * Result: turn off vertical sync (VSync) pulse.
	 */
	अगर (mode & FB_BLANK_VSYNC_SUSPEND) अणु
		vga_io_wcrt(VGA_CRTC_V_SYNC_START, 0xff);
		vga_io_wcrt(VGA_CRTC_V_SYNC_END, 0x40);
		/* bits 9,10 of vert. retrace */
		vga_io_wcrt(VGA_CRTC_OVERFLOW, par->vga_state.Overflow | 0x84);
	पूर्ण

	अगर (mode & FB_BLANK_HSYNC_SUSPEND) अणु
		/*
		 * Set <End of horizontal retrace> to minimum (0) and
		 *  <Start of horizontal Retrace> to maximum
		 * Result: turn off horizontal sync (HSync) pulse.
		 */
		vga_io_wcrt(VGA_CRTC_H_SYNC_START, 0xff);
		vga_io_wcrt(VGA_CRTC_H_SYNC_END, 0x00);
	पूर्ण

	/* restore both index रेजिस्टरs */
	outb_p(SeqCtrlIndex, VGA_SEQ_I);
	outb_p(CrtCtrlIndex, VGA_CRT_IC);
पूर्ण

अटल व्योम vga_vesa_unblank(काष्ठा vga16fb_par *par)
अणु
	अचिन्हित अक्षर SeqCtrlIndex = vga_io_r(VGA_SEQ_I);
	अचिन्हित अक्षर CrtCtrlIndex = vga_io_r(VGA_CRT_IC);
	
	/* restore original values of VGA controller रेजिस्टरs */
	vga_io_w(VGA_MIS_W, par->vga_state.CrtMiscIO);

	/* HorizontalTotal */
	vga_io_wcrt(0x00, par->vga_state.HorizontalTotal);
	/* HorizDisplayEnd */
	vga_io_wcrt(0x01, par->vga_state.HorizDisplayEnd);
	/* StartHorizRetrace */
	vga_io_wcrt(0x04, par->vga_state.StartHorizRetrace);
	/* EndHorizRetrace */
	vga_io_wcrt(0x05, par->vga_state.EndHorizRetrace);
	/* Overflow */
	vga_io_wcrt(0x07, par->vga_state.Overflow);
	/* StartVertRetrace */
	vga_io_wcrt(0x10, par->vga_state.StartVertRetrace);
	/* EndVertRetrace */
	vga_io_wcrt(0x11, par->vga_state.EndVertRetrace);
	/* ModeControl */
	vga_io_wcrt(0x17, par->vga_state.ModeControl);
	/* ClockingMode */
	vga_io_wseq(0x01, par->vga_state.ClockingMode);

	/* restore index/control रेजिस्टरs */
	vga_io_w(VGA_SEQ_I, SeqCtrlIndex);
	vga_io_w(VGA_CRT_IC, CrtCtrlIndex);
पूर्ण

अटल व्योम vga_pal_blank(व्योम)
अणु
	पूर्णांक i;

	क्रम (i=0; i<16; i++) अणु
		outb_p(i, VGA_PEL_IW);
		outb_p(0, VGA_PEL_D);
		outb_p(0, VGA_PEL_D);
		outb_p(0, VGA_PEL_D);
	पूर्ण
पूर्ण

/* 0 unblank, 1 blank, 2 no vsync, 3 no hsync, 4 off */
अटल पूर्णांक vga16fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा vga16fb_par *par = info->par;

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:				/* Unblank */
		अगर (par->vesa_blanked) अणु
			vga_vesa_unblank(par);
			par->vesa_blanked = 0;
		पूर्ण
		अगर (par->palette_blanked) अणु
			par->palette_blanked = 0;
		पूर्ण
		अवरोध;
	हाल FB_BLANK_NORMAL:				/* blank */
		vga_pal_blank();
		par->palette_blanked = 1;
		अवरोध;
	शेष:			/* VESA blanking */
		vga_vesa_blank(par, blank);
		par->vesa_blanked = 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vga_8planes_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	u32 dx = rect->dx, width = rect->width;
        अक्षर oldindex = getindex();
        अक्षर oldmode = seपंचांगode(0x40);
        अक्षर oldmask = selecपंचांगask();
        पूर्णांक line_ofs, height;
        अक्षर olकरोp, oldsr;
        अक्षर __iomem *where;

        dx /= 4;
        where = info->screen_base + dx + rect->dy * info->fix.line_length;

        अगर (rect->rop == ROP_COPY) अणु
                olकरोp = setop(0);
                oldsr = setsr(0);

                width /= 4;
                line_ofs = info->fix.line_length - width;
                seपंचांगask(0xff);

                height = rect->height;

                जबतक (height--) अणु
                        पूर्णांक x;

                        /* we can करो स_रखो... */
                        क्रम (x = width; x > 0; --x) अणु
                                ग_लिखोb(rect->color, where);
                                where++;
                        पूर्ण
                        where += line_ofs;
                पूर्ण
        पूर्ण अन्यथा अणु
                अक्षर oldcolor = setcolor(0xf);
                पूर्णांक y;

                olकरोp = setop(0x18);
                oldsr = setsr(0xf);
                seपंचांगask(0x0F);
                क्रम (y = 0; y < rect->height; y++) अणु
                        rmw(where);
                        rmw(where+1);
                        where += info->fix.line_length;
                पूर्ण
                setcolor(oldcolor);
        पूर्ण
        seपंचांगask(oldmask);
        setsr(oldsr);
        setop(olकरोp);
        seपंचांगode(oldmode);
        setindex(oldindex);
पूर्ण

अटल व्योम vga16fb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	पूर्णांक x, x2, y2, vxres, vyres, width, height, line_ofs;
	अक्षर __iomem *dst;

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	अगर (!rect->width || !rect->height || rect->dx > vxres || rect->dy > vyres)
		वापस;

	/* We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly. */

	x2 = rect->dx + rect->width;
	y2 = rect->dy + rect->height;
	x2 = x2 < vxres ? x2 : vxres;
	y2 = y2 < vyres ? y2 : vyres;
	width = x2 - rect->dx;

	चयन (info->fix.type) अणु
	हाल FB_TYPE_VGA_PLANES:
		अगर (info->fix.type_aux == FB_AUX_VGA_PLANES_VGA4) अणु

			height = y2 - rect->dy;
			width = rect->width/8;

			line_ofs = info->fix.line_length - width;
			dst = info->screen_base + (rect->dx/8) + rect->dy * info->fix.line_length;

			चयन (rect->rop) अणु
			हाल ROP_COPY:
				seपंचांगode(0);
				setop(0);
				setsr(0xf);
				setcolor(rect->color);
				selecपंचांगask();

				seपंचांगask(0xff);

				जबतक (height--) अणु
					क्रम (x = 0; x < width; x++) अणु
						ग_लिखोb(0, dst);
						dst++;
					पूर्ण
					dst += line_ofs;
				पूर्ण
				अवरोध;
			हाल ROP_XOR:
				seपंचांगode(0);
				setop(0x18);
				setsr(0xf);
				setcolor(0xf);
				selecपंचांगask();

				seपंचांगask(0xff);
				जबतक (height--) अणु
					क्रम (x = 0; x < width; x++) अणु
						rmw(dst);
						dst++;
					पूर्ण
					dst += line_ofs;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा 
			vga_8planes_fillrect(info, rect);
		अवरोध;
	हाल FB_TYPE_PACKED_PIXELS:
	शेष:
		cfb_fillrect(info, rect);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vga_8planes_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
        अक्षर oldindex = getindex();
        अक्षर oldmode = seपंचांगode(0x41);
        अक्षर olकरोp = setop(0);
        अक्षर oldsr = setsr(0xf);
        पूर्णांक height, line_ofs, x;
	u32 sx, dx, width;
	अक्षर __iomem *dest;
	अक्षर __iomem *src;

        height = area->height;

        sx = area->sx / 4;
        dx = area->dx / 4;
        width = area->width / 4;

        अगर (area->dy < area->sy || (area->dy == area->sy && dx < sx)) अणु
                line_ofs = info->fix.line_length - width;
                dest = info->screen_base + dx + area->dy * info->fix.line_length;
                src = info->screen_base + sx + area->sy * info->fix.line_length;
                जबतक (height--) अणु
                        क्रम (x = 0; x < width; x++) अणु
                                पढ़ोb(src);
                                ग_लिखोb(0, dest);
                                src++;
                                dest++;
                        पूर्ण
                        src += line_ofs;
                        dest += line_ofs;
                पूर्ण
        पूर्ण अन्यथा अणु
                line_ofs = info->fix.line_length - width;
                dest = info->screen_base + dx + width +
			(area->dy + height - 1) * info->fix.line_length;
                src = info->screen_base + sx + width +
			(area->sy + height - 1) * info->fix.line_length;
                जबतक (height--) अणु
                        क्रम (x = 0; x < width; x++) अणु
                                --src;
                                --dest;
                                पढ़ोb(src);
                                ग_लिखोb(0, dest);
                        पूर्ण
                        src -= line_ofs;
                        dest -= line_ofs;
                पूर्ण
        पूर्ण

        setsr(oldsr);
        setop(olकरोp);
        seपंचांगode(oldmode);
        setindex(oldindex);
पूर्ण

अटल व्योम vga16fb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	u32 dx = area->dx, dy = area->dy, sx = area->sx, sy = area->sy; 
	पूर्णांक x, x2, y2, old_dx, old_dy, vxres, vyres;
	पूर्णांक height, width, line_ofs;
	अक्षर __iomem *dst = शून्य;
	अक्षर __iomem *src = शून्य;

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	अगर (area->dx > vxres || area->sx > vxres || area->dy > vyres ||
	    area->sy > vyres)
		वापस;

	/* clip the destination */
	old_dx = area->dx;
	old_dy = area->dy;

	/*
	 * We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly.
	 */
	x2 = area->dx + area->width;
	y2 = area->dy + area->height;
	dx = area->dx > 0 ? area->dx : 0;
	dy = area->dy > 0 ? area->dy : 0;
	x2 = x2 < vxres ? x2 : vxres;
	y2 = y2 < vyres ? y2 : vyres;
	width = x2 - dx;
	height = y2 - dy;

	अगर (sx + dx < old_dx || sy + dy < old_dy)
		वापस;

	/* update sx1,sy1 */
	sx += (dx - old_dx);
	sy += (dy - old_dy);

	/* the source must be completely inside the भव screen */
	अगर (sx + width > vxres || sy + height > vyres)
		वापस;

	चयन (info->fix.type) अणु
	हाल FB_TYPE_VGA_PLANES:
		अगर (info->fix.type_aux == FB_AUX_VGA_PLANES_VGA4) अणु
			width = width/8;
			line_ofs = info->fix.line_length - width;

			seपंचांगode(1);
			setop(0);
			setsr(0xf);

			अगर (dy < sy || (dy == sy && dx < sx)) अणु
				dst = info->screen_base + (dx/8) + dy * info->fix.line_length;
				src = info->screen_base + (sx/8) + sy * info->fix.line_length;
				जबतक (height--) अणु
					क्रम (x = 0; x < width; x++) अणु
						पढ़ोb(src);
						ग_लिखोb(0, dst);
						dst++;
						src++;
					पूर्ण
					src += line_ofs;
					dst += line_ofs;
				पूर्ण
			पूर्ण अन्यथा अणु
				dst = info->screen_base + (dx/8) + width + 
					(dy + height - 1) * info->fix.line_length;
				src = info->screen_base + (sx/8) + width + 
					(sy + height  - 1) * info->fix.line_length;
				जबतक (height--) अणु
					क्रम (x = 0; x < width; x++) अणु
						dst--;
						src--;
						पढ़ोb(src);
						ग_लिखोb(0, dst);
					पूर्ण
					src -= line_ofs;
					dst -= line_ofs;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा 
			vga_8planes_copyarea(info, area);
		अवरोध;
	हाल FB_TYPE_PACKED_PIXELS:
	शेष:
		cfb_copyarea(info, area);
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा TRANS_MASK_LOW  अणु0x0,0x8,0x4,0xC,0x2,0xA,0x6,0xE,0x1,0x9,0x5,0xD,0x3,0xB,0x7,0xFपूर्ण
#घोषणा TRANS_MASK_HIGH अणु0x000, 0x800, 0x400, 0xC00, 0x200, 0xA00, 0x600, 0xE00, \
			 0x100, 0x900, 0x500, 0xD00, 0x300, 0xB00, 0x700, 0xF00पूर्ण

#अगर defined(__LITTLE_ENDIAN)
अटल स्थिर u16 transl_l[] = TRANS_MASK_LOW;
अटल स्थिर u16 transl_h[] = TRANS_MASK_HIGH;
#या_अगर defined(__BIG_ENDIAN)
अटल स्थिर u16 transl_l[] = TRANS_MASK_HIGH;
अटल स्थिर u16 transl_h[] = TRANS_MASK_LOW;
#अन्यथा
#त्रुटि "Only __BIG_ENDIAN and __LITTLE_ENDIAN are supported in vga-planes"
#पूर्ण_अगर

अटल व्योम vga_8planes_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
        अक्षर oldindex = getindex();
        अक्षर oldmode = seपंचांगode(0x40);
        अक्षर olकरोp = setop(0);
        अक्षर oldsr = setsr(0);
        अक्षर oldmask = selecपंचांगask();
	स्थिर अचिन्हित अक्षर *cdat = image->data;
	u32 dx = image->dx;
        अक्षर __iomem *where;
        पूर्णांक y;

        dx /= 4;
        where = info->screen_base + dx + image->dy * info->fix.line_length;

        seपंचांगask(0xff);
        ग_लिखोb(image->bg_color, where);
        पढ़ोb(where);
        selecपंचांगask();
        seपंचांगask(image->fg_color ^ image->bg_color);
        seपंचांगode(0x42);
        setop(0x18);
        क्रम (y = 0; y < image->height; y++, where += info->fix.line_length)
                ग_लिखोw(transl_h[cdat[y]&0xF] | transl_l[cdat[y] >> 4], where);
        seपंचांगask(oldmask);
        setsr(oldsr);
        setop(olकरोp);
        seपंचांगode(oldmode);
        setindex(oldindex);
पूर्ण

अटल व्योम vga_imageblit_expand(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	अक्षर __iomem *where = info->screen_base + (image->dx/8) +
		image->dy * info->fix.line_length;
	काष्ठा vga16fb_par *par = info->par;
	अक्षर *cdat = (अक्षर *) image->data;
	अक्षर __iomem *dst;
	पूर्णांक x, y;

	चयन (info->fix.type) अणु
	हाल FB_TYPE_VGA_PLANES:
		अगर (info->fix.type_aux == FB_AUX_VGA_PLANES_VGA4) अणु
			अगर (par->isVGA) अणु
				seपंचांगode(2);
				setop(0);
				setsr(0xf);
				setcolor(image->fg_color);
				selecपंचांगask();
				
				seपंचांगask(0xff);
				ग_लिखोb(image->bg_color, where);
				rmb();
				पढ़ोb(where); /* fill latches */
				seपंचांगode(3);
				wmb();
				क्रम (y = 0; y < image->height; y++) अणु
					dst = where;
					क्रम (x = image->width/8; x--;) 
						ग_लिखोb(*cdat++, dst++);
					where += info->fix.line_length;
				पूर्ण
				wmb();
			पूर्ण अन्यथा अणु
				seपंचांगode(0);
				setop(0);
				setsr(0xf);
				setcolor(image->bg_color);
				selecपंचांगask();
				
				seपंचांगask(0xff);
				क्रम (y = 0; y < image->height; y++) अणु
					dst = where;
					क्रम (x=image->width/8; x--;)अणु
						rmw(dst);
						setcolor(image->fg_color);
						selecपंचांगask();
						अगर (*cdat) अणु
							seपंचांगask(*cdat++);
							rmw(dst++);
						पूर्ण
					पूर्ण
					where += info->fix.line_length;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा 
			vga_8planes_imageblit(info, image);
		अवरोध;
	हाल FB_TYPE_PACKED_PIXELS:
	शेष:
		cfb_imageblit(info, image);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vga_imageblit_color(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	/*
	 * Draw logo 
	 */
	काष्ठा vga16fb_par *par = info->par;
	अक्षर __iomem *where =
		info->screen_base + image->dy * info->fix.line_length +
		image->dx/8;
	स्थिर अक्षर *cdat = image->data;
	अक्षर __iomem *dst;
	पूर्णांक x, y;

	चयन (info->fix.type) अणु
	हाल FB_TYPE_VGA_PLANES:
		अगर (info->fix.type_aux == FB_AUX_VGA_PLANES_VGA4 &&
		    par->isVGA) अणु
			setsr(0xf);
			setop(0);
			seपंचांगode(0);
			
			क्रम (y = 0; y < image->height; y++) अणु
				क्रम (x = 0; x < image->width; x++) अणु
					dst = where + x/8;

					setcolor(*cdat);
					selecपंचांगask();
					seपंचांगask(1 << (7 - (x % 8)));
					fb_पढ़ोb(dst);
					fb_ग_लिखोb(0, dst);

					cdat++;
				पूर्ण
				where += info->fix.line_length;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल FB_TYPE_PACKED_PIXELS:
		cfb_imageblit(info, image);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
				
अटल व्योम vga16fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	अगर (image->depth == 1)
		vga_imageblit_expand(info, image);
	अन्यथा
		vga_imageblit_color(info, image);
पूर्ण

अटल व्योम vga16fb_destroy(काष्ठा fb_info *info)
अणु
	iounmap(info->screen_base);
	fb_dealloc_cmap(&info->cmap);
	/* XXX unshare VGA regions */
	framebuffer_release(info);
पूर्ण

अटल स्थिर काष्ठा fb_ops vga16fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो        = vga16fb_खोलो,
	.fb_release     = vga16fb_release,
	.fb_destroy	= vga16fb_destroy,
	.fb_check_var	= vga16fb_check_var,
	.fb_set_par	= vga16fb_set_par,
	.fb_setcolreg 	= vga16fb_setcolreg,
	.fb_pan_display = vga16fb_pan_display,
	.fb_blank 	= vga16fb_blank,
	.fb_fillrect	= vga16fb_fillrect,
	.fb_copyarea	= vga16fb_copyarea,
	.fb_imageblit	= vga16fb_imageblit,
पूर्ण;

#अगर_अघोषित MODULE
अटल पूर्णांक __init vga16fb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;
	
	अगर (!options || !*options)
		वापस 0;
	
	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt) जारी;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vga16fb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा vga16fb_par *par;
	पूर्णांक i;
	पूर्णांक ret = 0;

	prपूर्णांकk(KERN_DEBUG "vga16fb: initializing\n");
	info = framebuffer_alloc(माप(काष्ठा vga16fb_par), &dev->dev);

	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ err_fb_alloc;
	पूर्ण
	info->apertures = alloc_apertures(1);
	अगर (!info->apertures) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	/* XXX share VGA_FB_PHYS and I/O region with vgacon and others */
	info->screen_base = (व्योम __iomem *)VGA_MAP_MEM(VGA_FB_PHYS, 0);

	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR "vga16fb: unable to map device\n");
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	prपूर्णांकk(KERN_INFO "vga16fb: mapped to 0x%p\n", info->screen_base);
	par = info->par;

	par->isVGA = screen_info.orig_video_isVGA;
	par->palette_blanked = 0;
	par->vesa_blanked = 0;

	i = par->isVGA? 6 : 2;
	
	vga16fb_defined.red.length   = i;
	vga16fb_defined.green.length = i;
	vga16fb_defined.blue.length  = i;	

	/* name should not depend on EGA/VGA */
	info->fbops = &vga16fb_ops;
	info->var = vga16fb_defined;
	info->fix = vga16fb_fix;
	/* supports rectangles with widths of multiples of 8 */
	info->pixmap.blit_x = 1 << 7 | 1 << 15 | 1 << 23 | 1 << 31;
	info->flags = FBINFO_FLAG_DEFAULT | FBINFO_MISC_FIRMWARE |
		FBINFO_HWACCEL_YPAN;

	i = (info->var.bits_per_pixel == 8) ? 256 : 16;
	ret = fb_alloc_cmap(&info->cmap, i, 0);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "vga16fb: unable to allocate colormap\n");
		ret = -ENOMEM;
		जाओ err_alloc_cmap;
	पूर्ण

	अगर (vga16fb_check_var(&info->var, info)) अणु
		prपूर्णांकk(KERN_ERR "vga16fb: unable to validate variable\n");
		ret = -EINVAL;
		जाओ err_check_var;
	पूर्ण

	vga16fb_update_fix(info);

	info->apertures->ranges[0].base = VGA_FB_PHYS;
	info->apertures->ranges[0].size = VGA_FB_PHYS_LEN;

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		prपूर्णांकk(KERN_ERR "vga16fb: unable to register framebuffer\n");
		ret = -EINVAL;
		जाओ err_check_var;
	पूर्ण

	fb_info(info, "%s frame buffer device\n", info->fix.id);
	platक्रमm_set_drvdata(dev, info);

	वापस 0;

 err_check_var:
	fb_dealloc_cmap(&info->cmap);
 err_alloc_cmap:
	iounmap(info->screen_base);
 err_ioremap:
	framebuffer_release(info);
 err_fb_alloc:
	वापस ret;
पूर्ण

अटल पूर्णांक vga16fb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);

	अगर (info)
		unरेजिस्टर_framebuffer(info);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vga16fb_driver = अणु
	.probe = vga16fb_probe,
	.हटाओ = vga16fb_हटाओ,
	.driver = अणु
		.name = "vga16fb",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *vga16fb_device;

अटल पूर्णांक __init vga16fb_init(व्योम)
अणु
	पूर्णांक ret;
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("vga16fb", &option))
		वापस -ENODEV;

	vga16fb_setup(option);
#पूर्ण_अगर
	ret = platक्रमm_driver_रेजिस्टर(&vga16fb_driver);

	अगर (!ret) अणु
		vga16fb_device = platक्रमm_device_alloc("vga16fb", 0);

		अगर (vga16fb_device)
			ret = platक्रमm_device_add(vga16fb_device);
		अन्यथा
			ret = -ENOMEM;

		अगर (ret) अणु
			platक्रमm_device_put(vga16fb_device);
			platक्रमm_driver_unरेजिस्टर(&vga16fb_driver);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास vga16fb_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(vga16fb_device);
	platक्रमm_driver_unरेजिस्टर(&vga16fb_driver);
पूर्ण

MODULE_DESCRIPTION("Legacy VGA framebuffer device driver");
MODULE_LICENSE("GPL");
module_init(vga16fb_init);
module_निकास(vga16fb_निकास);
