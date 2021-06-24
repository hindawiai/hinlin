<शैली गुरु>
/*
 * Common utility functions क्रम VGA-based graphics cards.
 *
 * Copyright (c) 2006-2007 Ondrej Zajicek <santiago@crमुक्तnet.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Some parts are based on David Boucher's viafb (http://davesकरोमुख्य.org.uk/viafb/)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <linux/svga.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/पन.स>


/* Write a CRT रेजिस्टर value spपढ़ो across multiple रेजिस्टरs */
व्योम svga_wcrt_multi(व्योम __iomem *regbase, स्थिर काष्ठा vga_regset *regset, u32 value)
अणु
	u8 regval, bitval, bitnum;

	जबतक (regset->regnum != VGA_REGSET_END_VAL) अणु
		regval = vga_rcrt(regbase, regset->regnum);
		bitnum = regset->lowbit;
		जबतक (bitnum <= regset->highbit) अणु
			bitval = 1 << bitnum;
			regval = regval & ~bitval;
			अगर (value & 1) regval = regval | bitval;
			bitnum ++;
			value = value >> 1;
		पूर्ण
		vga_wcrt(regbase, regset->regnum, regval);
		regset ++;
	पूर्ण
पूर्ण

/* Write a sequencer रेजिस्टर value spपढ़ो across multiple रेजिस्टरs */
व्योम svga_wseq_multi(व्योम __iomem *regbase, स्थिर काष्ठा vga_regset *regset, u32 value)
अणु
	u8 regval, bitval, bitnum;

	जबतक (regset->regnum != VGA_REGSET_END_VAL) अणु
		regval = vga_rseq(regbase, regset->regnum);
		bitnum = regset->lowbit;
		जबतक (bitnum <= regset->highbit) अणु
			bitval = 1 << bitnum;
			regval = regval & ~bitval;
			अगर (value & 1) regval = regval | bitval;
			bitnum ++;
			value = value >> 1;
		पूर्ण
		vga_wseq(regbase, regset->regnum, regval);
		regset ++;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक svga_regset_size(स्थिर काष्ठा vga_regset *regset)
अणु
	u8 count = 0;

	जबतक (regset->regnum != VGA_REGSET_END_VAL) अणु
		count += regset->highbit - regset->lowbit + 1;
		regset ++;
	पूर्ण
	वापस 1 << count;
पूर्ण


/* ------------------------------------------------------------------------- */


/* Set graphics controller रेजिस्टरs to sane values */
व्योम svga_set_शेष_gfx_regs(व्योम __iomem *regbase)
अणु
	/* All standard GFX रेजिस्टरs (GR00 - GR08) */
	vga_wgfx(regbase, VGA_GFX_SR_VALUE, 0x00);
	vga_wgfx(regbase, VGA_GFX_SR_ENABLE, 0x00);
	vga_wgfx(regbase, VGA_GFX_COMPARE_VALUE, 0x00);
	vga_wgfx(regbase, VGA_GFX_DATA_ROTATE, 0x00);
	vga_wgfx(regbase, VGA_GFX_PLANE_READ, 0x00);
	vga_wgfx(regbase, VGA_GFX_MODE, 0x00);
/*	vga_wgfx(regbase, VGA_GFX_MODE, 0x20); */
/*	vga_wgfx(regbase, VGA_GFX_MODE, 0x40); */
	vga_wgfx(regbase, VGA_GFX_MISC, 0x05);
/*	vga_wgfx(regbase, VGA_GFX_MISC, 0x01); */
	vga_wgfx(regbase, VGA_GFX_COMPARE_MASK, 0x0F);
	vga_wgfx(regbase, VGA_GFX_BIT_MASK, 0xFF);
पूर्ण

/* Set attribute controller रेजिस्टरs to sane values */
व्योम svga_set_शेष_atc_regs(व्योम __iomem *regbase)
अणु
	u8 count;

	vga_r(regbase, 0x3DA);
	vga_w(regbase, VGA_ATT_W, 0x00);

	/* All standard ATC रेजिस्टरs (AR00 - AR14) */
	क्रम (count = 0; count <= 0xF; count ++)
		svga_wattr(regbase, count, count);

	svga_wattr(regbase, VGA_ATC_MODE, 0x01);
/*	svga_wattr(regbase, VGA_ATC_MODE, 0x41); */
	svga_wattr(regbase, VGA_ATC_OVERSCAN, 0x00);
	svga_wattr(regbase, VGA_ATC_PLANE_ENABLE, 0x0F);
	svga_wattr(regbase, VGA_ATC_PEL, 0x00);
	svga_wattr(regbase, VGA_ATC_COLOR_PAGE, 0x00);

	vga_r(regbase, 0x3DA);
	vga_w(regbase, VGA_ATT_W, 0x20);
पूर्ण

/* Set sequencer रेजिस्टरs to sane values */
व्योम svga_set_शेष_seq_regs(व्योम __iomem *regbase)
अणु
	/* Standard sequencer रेजिस्टरs (SR01 - SR04), SR00 is not set */
	vga_wseq(regbase, VGA_SEQ_CLOCK_MODE, VGA_SR01_CHAR_CLK_8DOTS);
	vga_wseq(regbase, VGA_SEQ_PLANE_WRITE, VGA_SR02_ALL_PLANES);
	vga_wseq(regbase, VGA_SEQ_CHARACTER_MAP, 0x00);
/*	vga_wseq(regbase, VGA_SEQ_MEMORY_MODE, VGA_SR04_EXT_MEM | VGA_SR04_SEQ_MODE | VGA_SR04_CHN_4M); */
	vga_wseq(regbase, VGA_SEQ_MEMORY_MODE, VGA_SR04_EXT_MEM | VGA_SR04_SEQ_MODE);
पूर्ण

/* Set CRTC रेजिस्टरs to sane values */
व्योम svga_set_शेष_crt_regs(व्योम __iomem *regbase)
अणु
	/* Standard CRT रेजिस्टरs CR03 CR08 CR09 CR14 CR17 */
	svga_wcrt_mask(regbase, 0x03, 0x80, 0x80);	/* Enable vertical retrace EVRA */
	vga_wcrt(regbase, VGA_CRTC_PRESET_ROW, 0);
	svga_wcrt_mask(regbase, VGA_CRTC_MAX_SCAN, 0, 0x1F);
	vga_wcrt(regbase, VGA_CRTC_UNDERLINE, 0);
	vga_wcrt(regbase, VGA_CRTC_MODE, 0xE3);
पूर्ण

व्योम svga_set_texपंचांगode_vga_regs(व्योम __iomem *regbase)
अणु
	/* svga_wseq_mask(regbase, 0x1, 0x00, 0x01); */   /* Switch 8/9 pixel per अक्षर */
	vga_wseq(regbase, VGA_SEQ_MEMORY_MODE, VGA_SR04_EXT_MEM);
	vga_wseq(regbase, VGA_SEQ_PLANE_WRITE, 0x03);

	vga_wcrt(regbase, VGA_CRTC_MAX_SCAN, 0x0f); /* 0x4f */
	vga_wcrt(regbase, VGA_CRTC_UNDERLINE, 0x1f);
	svga_wcrt_mask(regbase, VGA_CRTC_MODE, 0x23, 0x7f);

	vga_wcrt(regbase, VGA_CRTC_CURSOR_START, 0x0d);
	vga_wcrt(regbase, VGA_CRTC_CURSOR_END, 0x0e);
	vga_wcrt(regbase, VGA_CRTC_CURSOR_HI, 0x00);
	vga_wcrt(regbase, VGA_CRTC_CURSOR_LO, 0x00);

	vga_wgfx(regbase, VGA_GFX_MODE, 0x10); /* Odd/even memory mode */
	vga_wgfx(regbase, VGA_GFX_MISC, 0x0E); /* Misc graphics रेजिस्टर - text mode enable */
	vga_wgfx(regbase, VGA_GFX_COMPARE_MASK, 0x00);

	vga_r(regbase, 0x3DA);
	vga_w(regbase, VGA_ATT_W, 0x00);

	svga_wattr(regbase, 0x10, 0x0C);			/* Attribute Mode Control Register - text mode, blinking and line graphics */
	svga_wattr(regbase, 0x13, 0x08);			/* Horizontal Pixel Panning Register  */

	vga_r(regbase, 0x3DA);
	vga_w(regbase, VGA_ATT_W, 0x20);
पूर्ण

#अगर 0
व्योम svga_dump_var(काष्ठा fb_var_screeninfo *var, पूर्णांक node)
अणु
	pr_debug("fb%d: var.vmode         : 0x%X\n", node, var->vmode);
	pr_debug("fb%d: var.xres          : %d\n", node, var->xres);
	pr_debug("fb%d: var.yres          : %d\n", node, var->yres);
	pr_debug("fb%d: var.bits_per_pixel: %d\n", node, var->bits_per_pixel);
	pr_debug("fb%d: var.xres_virtual  : %d\n", node, var->xres_भव);
	pr_debug("fb%d: var.yres_virtual  : %d\n", node, var->yres_भव);
	pr_debug("fb%d: var.left_margin   : %d\n", node, var->left_margin);
	pr_debug("fb%d: var.right_margin  : %d\n", node, var->right_margin);
	pr_debug("fb%d: var.upper_margin  : %d\n", node, var->upper_margin);
	pr_debug("fb%d: var.lower_margin  : %d\n", node, var->lower_margin);
	pr_debug("fb%d: var.hsync_len     : %d\n", node, var->hsync_len);
	pr_debug("fb%d: var.vsync_len     : %d\n", node, var->vsync_len);
	pr_debug("fb%d: var.sync          : 0x%X\n", node, var->sync);
	pr_debug("fb%d: var.pixclock      : %d\n\n", node, var->pixघड़ी);
पूर्ण
#पूर्ण_अगर  /*  0  */


/* ------------------------------------------------------------------------- */


व्योम svga_settile(काष्ठा fb_info *info, काष्ठा fb_tilemap *map)
अणु
	स्थिर u8 *font = map->data;
	u8 __iomem *fb = (u8 __iomem *)info->screen_base;
	पूर्णांक i, c;

	अगर ((map->width != 8) || (map->height != 16) ||
	    (map->depth != 1) || (map->length != 256)) अणु
		fb_err(info, "unsupported font parameters: width %d, height %d, depth %d, length %d\n",
		       map->width, map->height, map->depth, map->length);
		वापस;
	पूर्ण

	fb += 2;
	क्रम (c = 0; c < map->length; c++) अणु
		क्रम (i = 0; i < map->height; i++) अणु
			fb_ग_लिखोb(font[i], fb + i * 4);
//			fb[i * 4] = font[i];
		पूर्ण
		fb += 128;
		font += map->height;
	पूर्ण
पूर्ण

/* Copy area in text (tileblit) mode */
व्योम svga_tilecopy(काष्ठा fb_info *info, काष्ठा fb_tilearea *area)
अणु
	पूर्णांक dx, dy;
	/*  colstride is halved in this function because u16 are used */
	पूर्णांक colstride = 1 << (info->fix.type_aux & FB_AUX_TEXT_SVGA_MASK);
	पूर्णांक rowstride = colstride * (info->var.xres_भव / 8);
	u16 __iomem *fb = (u16 __iomem *) info->screen_base;
	u16 __iomem *src, *dst;

	अगर ((area->sy > area->dy) ||
	    ((area->sy == area->dy) && (area->sx > area->dx))) अणु
		src = fb + area->sx * colstride + area->sy * rowstride;
		dst = fb + area->dx * colstride + area->dy * rowstride;
	    पूर्ण अन्यथा अणु
		src = fb + (area->sx + area->width - 1) * colstride
			 + (area->sy + area->height - 1) * rowstride;
		dst = fb + (area->dx + area->width - 1) * colstride
			 + (area->dy + area->height - 1) * rowstride;

		colstride = -colstride;
		rowstride = -rowstride;
	    पूर्ण

	क्रम (dy = 0; dy < area->height; dy++) अणु
		u16 __iomem *src2 = src;
		u16 __iomem *dst2 = dst;
		क्रम (dx = 0; dx < area->width; dx++) अणु
			fb_ग_लिखोw(fb_पढ़ोw(src2), dst2);
//			*dst2 = *src2;
			src2 += colstride;
			dst2 += colstride;
		पूर्ण
		src += rowstride;
		dst += rowstride;
	पूर्ण
पूर्ण

/* Fill area in text (tileblit) mode */
व्योम svga_tilefill(काष्ठा fb_info *info, काष्ठा fb_tilerect *rect)
अणु
	पूर्णांक dx, dy;
	पूर्णांक colstride = 2 << (info->fix.type_aux & FB_AUX_TEXT_SVGA_MASK);
	पूर्णांक rowstride = colstride * (info->var.xres_भव / 8);
	पूर्णांक attr = (0x0F & rect->bg) << 4 | (0x0F & rect->fg);
	u8 __iomem *fb = (u8 __iomem *)info->screen_base;
	fb += rect->sx * colstride + rect->sy * rowstride;

	क्रम (dy = 0; dy < rect->height; dy++) अणु
		u8 __iomem *fb2 = fb;
		क्रम (dx = 0; dx < rect->width; dx++) अणु
			fb_ग_लिखोb(rect->index, fb2);
			fb_ग_लिखोb(attr, fb2 + 1);
			fb2 += colstride;
		पूर्ण
		fb += rowstride;
	पूर्ण
पूर्ण

/* Write text in text (tileblit) mode */
व्योम svga_tileblit(काष्ठा fb_info *info, काष्ठा fb_tileblit *blit)
अणु
	पूर्णांक dx, dy, i;
	पूर्णांक colstride = 2 << (info->fix.type_aux & FB_AUX_TEXT_SVGA_MASK);
	पूर्णांक rowstride = colstride * (info->var.xres_भव / 8);
	पूर्णांक attr = (0x0F & blit->bg) << 4 | (0x0F & blit->fg);
	u8 __iomem *fb = (u8 __iomem *)info->screen_base;
	fb += blit->sx * colstride + blit->sy * rowstride;

	i=0;
	क्रम (dy=0; dy < blit->height; dy ++) अणु
		u8 __iomem *fb2 = fb;
		क्रम (dx = 0; dx < blit->width; dx ++) अणु
			fb_ग_लिखोb(blit->indices[i], fb2);
			fb_ग_लिखोb(attr, fb2 + 1);
			fb2 += colstride;
			i ++;
			अगर (i == blit->length) वापस;
		पूर्ण
		fb += rowstride;
	पूर्ण

पूर्ण

/* Set cursor in text (tileblit) mode */
व्योम svga_tilecursor(व्योम __iomem *regbase, काष्ठा fb_info *info, काष्ठा fb_tilecursor *cursor)
अणु
	u8 cs = 0x0d;
	u8 ce = 0x0e;
	u16 pos =  cursor->sx + (info->var.xoffset /  8)
		+ (cursor->sy + (info->var.yoffset / 16))
		   * (info->var.xres_भव / 8);

	अगर (! cursor -> mode)
		वापस;

	svga_wcrt_mask(regbase, 0x0A, 0x20, 0x20); /* disable cursor */

	अगर (cursor -> shape == FB_TILE_CURSOR_NONE)
		वापस;

	चयन (cursor -> shape) अणु
	हाल FB_TILE_CURSOR_UNDERLINE:
		cs = 0x0d;
		अवरोध;
	हाल FB_TILE_CURSOR_LOWER_THIRD:
		cs = 0x09;
		अवरोध;
	हाल FB_TILE_CURSOR_LOWER_HALF:
		cs = 0x07;
		अवरोध;
	हाल FB_TILE_CURSOR_TWO_THIRDS:
		cs = 0x05;
		अवरोध;
	हाल FB_TILE_CURSOR_BLOCK:
		cs = 0x01;
		अवरोध;
	पूर्ण

	/* set cursor position */
	vga_wcrt(regbase, 0x0E, pos >> 8);
	vga_wcrt(regbase, 0x0F, pos & 0xFF);

	vga_wcrt(regbase, 0x0B, ce); /* set cursor end */
	vga_wcrt(regbase, 0x0A, cs); /* set cursor start and enable it */
पूर्ण

पूर्णांक svga_get_tilemax(काष्ठा fb_info *info)
अणु
	वापस 256;
पूर्ण

/* Get capabilities of accelerator based on the mode */

व्योम svga_get_caps(काष्ठा fb_info *info, काष्ठा fb_blit_caps *caps,
		   काष्ठा fb_var_screeninfo *var)
अणु
	अगर (var->bits_per_pixel == 0) अणु
		/* can only support 256 8x16 biपंचांगap */
		caps->x = 1 << (8 - 1);
		caps->y = 1 << (16 - 1);
		caps->len = 256;
	पूर्ण अन्यथा अणु
		caps->x = (var->bits_per_pixel == 4) ? 1 << (8 - 1) : ~(u32)0;
		caps->y = ~(u32)0;
		caps->len = ~(u32)0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(svga_get_caps);

/* ------------------------------------------------------------------------- */


/*
 *  Compute PLL settings (M, N, R)
 *  F_VCO = (F_BASE * M) / N
 *  F_OUT = F_VCO / (2^R)
 */

अटल अंतरभूत u32 असल_dअगरf(u32 a, u32 b)
अणु
	वापस (a > b) ? (a - b) : (b - a);
पूर्ण

पूर्णांक svga_compute_pll(स्थिर काष्ठा svga_pll *pll, u32 f_wanted, u16 *m, u16 *n, u16 *r, पूर्णांक node)
अणु
	u16 am, an, ar;
	u32 f_vco, f_current, delta_current, delta_best;

	pr_debug("fb%d: ideal frequency: %d kHz\n", node, (अचिन्हित पूर्णांक) f_wanted);

	ar = pll->r_max;
	f_vco = f_wanted << ar;

	/* overflow check */
	अगर ((f_vco >> ar) != f_wanted)
		वापस -EINVAL;

	/* It is usually better to have greater VCO घड़ी
	   because of better frequency stability.
	   So first try r_max, then r smaller. */
	जबतक ((ar > pll->r_min) && (f_vco > pll->f_vco_max)) अणु
		ar--;
		f_vco = f_vco >> 1;
	पूर्ण

	/* VCO bounds check */
	अगर ((f_vco < pll->f_vco_min) || (f_vco > pll->f_vco_max))
		वापस -EINVAL;

	delta_best = 0xFFFFFFFF;
	*m = 0;
	*n = 0;
	*r = ar;

	am = pll->m_min;
	an = pll->n_min;

	जबतक ((am <= pll->m_max) && (an <= pll->n_max)) अणु
		f_current = (pll->f_base * am) / an;
		delta_current = असल_dअगरf (f_current, f_vco);

		अगर (delta_current < delta_best) अणु
			delta_best = delta_current;
			*m = am;
			*n = an;
		पूर्ण

		अगर (f_current <= f_vco) अणु
			am ++;
		पूर्ण अन्यथा अणु
			an ++;
		पूर्ण
	पूर्ण

	f_current = (pll->f_base * *m) / *n;
	pr_debug("fb%d: found frequency: %d kHz (VCO %d kHz)\n", node, (पूर्णांक) (f_current >> ar), (पूर्णांक) f_current);
	pr_debug("fb%d: m = %d n = %d r = %d\n", node, (अचिन्हित पूर्णांक) *m, (अचिन्हित पूर्णांक) *n, (अचिन्हित पूर्णांक) *r);
	वापस 0;
पूर्ण


/* ------------------------------------------------------------------------- */


/* Check CRT timing values */
पूर्णांक svga_check_timings(स्थिर काष्ठा svga_timing_regs *पंचांग, काष्ठा fb_var_screeninfo *var, पूर्णांक node)
अणु
	u32 value;

	var->xres         = (var->xres+7)&~7;
	var->left_margin  = (var->left_margin+7)&~7;
	var->right_margin = (var->right_margin+7)&~7;
	var->hsync_len    = (var->hsync_len+7)&~7;

	/* Check horizontal total */
	value = var->xres + var->left_margin + var->right_margin + var->hsync_len;
	अगर (((value / 8) - 5) >= svga_regset_size (पंचांग->h_total_regs))
		वापस -EINVAL;

	/* Check horizontal display and blank start */
	value = var->xres;
	अगर (((value / 8) - 1) >= svga_regset_size (पंचांग->h_display_regs))
		वापस -EINVAL;
	अगर (((value / 8) - 1) >= svga_regset_size (पंचांग->h_blank_start_regs))
		वापस -EINVAL;

	/* Check horizontal sync start */
	value = var->xres + var->right_margin;
	अगर (((value / 8) - 1) >= svga_regset_size (पंचांग->h_sync_start_regs))
		वापस -EINVAL;

	/* Check horizontal blank end (or length) */
	value = var->left_margin + var->right_margin + var->hsync_len;
	अगर ((value == 0) || ((value / 8) >= svga_regset_size (पंचांग->h_blank_end_regs)))
		वापस -EINVAL;

	/* Check horizontal sync end (or length) */
	value = var->hsync_len;
	अगर ((value == 0) || ((value / 8) >= svga_regset_size (पंचांग->h_sync_end_regs)))
		वापस -EINVAL;

	/* Check vertical total */
	value = var->yres + var->upper_margin + var->lower_margin + var->vsync_len;
	अगर ((value - 1) >= svga_regset_size(पंचांग->v_total_regs))
		वापस -EINVAL;

	/* Check vertical display and blank start */
	value = var->yres;
	अगर ((value - 1) >= svga_regset_size(पंचांग->v_display_regs))
		वापस -EINVAL;
	अगर ((value - 1) >= svga_regset_size(पंचांग->v_blank_start_regs))
		वापस -EINVAL;

	/* Check vertical sync start */
	value = var->yres + var->lower_margin;
	अगर ((value - 1) >= svga_regset_size(पंचांग->v_sync_start_regs))
		वापस -EINVAL;

	/* Check vertical blank end (or length) */
	value = var->upper_margin + var->lower_margin + var->vsync_len;
	अगर ((value == 0) || (value >= svga_regset_size (पंचांग->v_blank_end_regs)))
		वापस -EINVAL;

	/* Check vertical sync end  (or length) */
	value = var->vsync_len;
	अगर ((value == 0) || (value >= svga_regset_size (पंचांग->v_sync_end_regs)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Set CRT timing रेजिस्टरs */
व्योम svga_set_timings(व्योम __iomem *regbase, स्थिर काष्ठा svga_timing_regs *पंचांग,
		      काष्ठा fb_var_screeninfo *var,
		      u32 hmul, u32 hभाग, u32 vmul, u32 vभाग, u32 hborder, पूर्णांक node)
अणु
	u8 regval;
	u32 value;

	value = var->xres + var->left_margin + var->right_margin + var->hsync_len;
	value = (value * hmul) / hभाग;
	pr_debug("fb%d: horizontal total      : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->h_total_regs, (value / 8) - 5);

	value = var->xres;
	value = (value * hmul) / hभाग;
	pr_debug("fb%d: horizontal display    : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->h_display_regs, (value / 8) - 1);

	value = var->xres;
	value = (value * hmul) / hभाग;
	pr_debug("fb%d: horizontal blank start: %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->h_blank_start_regs, (value / 8) - 1 + hborder);

	value = var->xres + var->left_margin + var->right_margin + var->hsync_len;
	value = (value * hmul) / hभाग;
	pr_debug("fb%d: horizontal blank end  : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->h_blank_end_regs, (value / 8) - 1 - hborder);

	value = var->xres + var->right_margin;
	value = (value * hmul) / hभाग;
	pr_debug("fb%d: horizontal sync start : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->h_sync_start_regs, (value / 8));

	value = var->xres + var->right_margin + var->hsync_len;
	value = (value * hmul) / hभाग;
	pr_debug("fb%d: horizontal sync end   : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->h_sync_end_regs, (value / 8));

	value = var->yres + var->upper_margin + var->lower_margin + var->vsync_len;
	value = (value * vmul) / vभाग;
	pr_debug("fb%d: vertical total        : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->v_total_regs, value - 2);

	value = var->yres;
	value = (value * vmul) / vभाग;
	pr_debug("fb%d: vertical display      : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->v_display_regs, value - 1);

	value = var->yres;
	value = (value * vmul) / vभाग;
	pr_debug("fb%d: vertical blank start  : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->v_blank_start_regs, value);

	value = var->yres + var->upper_margin + var->lower_margin + var->vsync_len;
	value = (value * vmul) / vभाग;
	pr_debug("fb%d: vertical blank end    : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->v_blank_end_regs, value - 2);

	value = var->yres + var->lower_margin;
	value = (value * vmul) / vभाग;
	pr_debug("fb%d: vertical sync start   : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->v_sync_start_regs, value);

	value = var->yres + var->lower_margin + var->vsync_len;
	value = (value * vmul) / vभाग;
	pr_debug("fb%d: vertical sync end     : %d\n", node, value);
	svga_wcrt_multi(regbase, पंचांग->v_sync_end_regs, value);

	/* Set horizontal and vertical sync pulse polarity in misc रेजिस्टर */

	regval = vga_r(regbase, VGA_MIS_R);
	अगर (var->sync & FB_SYNC_HOR_HIGH_ACT) अणु
		pr_debug("fb%d: positive horizontal sync\n", node);
		regval = regval & ~0x80;
	पूर्ण अन्यथा अणु
		pr_debug("fb%d: negative horizontal sync\n", node);
		regval = regval | 0x80;
	पूर्ण
	अगर (var->sync & FB_SYNC_VERT_HIGH_ACT) अणु
		pr_debug("fb%d: positive vertical sync\n", node);
		regval = regval & ~0x40;
	पूर्ण अन्यथा अणु
		pr_debug("fb%d: negative vertical sync\n\n", node);
		regval = regval | 0x40;
	पूर्ण
	vga_w(regbase, VGA_MIS_W, regval);
पूर्ण


/* ------------------------------------------------------------------------- */


अटल अंतरभूत पूर्णांक match_क्रमmat(स्थिर काष्ठा svga_fb_क्रमmat *frm,
			       काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक i = 0;
	पूर्णांक stored = -EINVAL;

	जबतक (frm->bits_per_pixel != SVGA_FORMAT_END_VAL)
	अणु
		अगर ((var->bits_per_pixel == frm->bits_per_pixel) &&
		    (var->red.length     <= frm->red.length)     &&
		    (var->green.length   <= frm->green.length)   &&
		    (var->blue.length    <= frm->blue.length)    &&
		    (var->transp.length  <= frm->transp.length)  &&
		    (var->nonstd	 == frm->nonstd))
			वापस i;
		अगर (var->bits_per_pixel == frm->bits_per_pixel)
			stored = i;
		i++;
		frm++;
	पूर्ण
	वापस stored;
पूर्ण

पूर्णांक svga_match_क्रमmat(स्थिर काष्ठा svga_fb_क्रमmat *frm,
		      काष्ठा fb_var_screeninfo *var,
		      काष्ठा fb_fix_screeninfo *fix)
अणु
	पूर्णांक i = match_क्रमmat(frm, var);

	अगर (i >= 0) अणु
		var->bits_per_pixel = frm[i].bits_per_pixel;
		var->red            = frm[i].red;
		var->green          = frm[i].green;
		var->blue           = frm[i].blue;
		var->transp         = frm[i].transp;
		var->nonstd         = frm[i].nonstd;
		अगर (fix != शून्य) अणु
			fix->type      = frm[i].type;
			fix->type_aux  = frm[i].type_aux;
			fix->visual    = frm[i].visual;
			fix->xpanstep  = frm[i].xpanstep;
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण


EXPORT_SYMBOL(svga_wcrt_multi);
EXPORT_SYMBOL(svga_wseq_multi);

EXPORT_SYMBOL(svga_set_शेष_gfx_regs);
EXPORT_SYMBOL(svga_set_शेष_atc_regs);
EXPORT_SYMBOL(svga_set_शेष_seq_regs);
EXPORT_SYMBOL(svga_set_शेष_crt_regs);
EXPORT_SYMBOL(svga_set_texपंचांगode_vga_regs);

EXPORT_SYMBOL(svga_settile);
EXPORT_SYMBOL(svga_tilecopy);
EXPORT_SYMBOL(svga_tilefill);
EXPORT_SYMBOL(svga_tileblit);
EXPORT_SYMBOL(svga_tilecursor);
EXPORT_SYMBOL(svga_get_tilemax);

EXPORT_SYMBOL(svga_compute_pll);
EXPORT_SYMBOL(svga_check_timings);
EXPORT_SYMBOL(svga_set_timings);
EXPORT_SYMBOL(svga_match_क्रमmat);

MODULE_AUTHOR("Ondrej Zajicek <santiago@crfreenet.org>");
MODULE_DESCRIPTION("Common utility functions for VGA-based graphics cards");
MODULE_LICENSE("GPL");
