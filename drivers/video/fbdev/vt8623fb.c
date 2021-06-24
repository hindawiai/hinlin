<शैली गुरु>
/*
 * linux/drivers/video/vt8623fb.c - fbdev driver क्रम
 * पूर्णांकegrated graphic core in VIA VT8623 [CLE266] chipset
 *
 * Copyright (c) 2006-2007 Ondrej Zajicek <santiago@crमुक्तnet.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Code is based on s3fb, some parts are from David Boucher's viafb
 * (http://davesकरोमुख्य.org.uk/viafb/)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/svga.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/console.h> /* Why should fb driver call console functions? because console_lock() */
#समावेश <video/vga.h>

काष्ठा vt8623fb_info अणु
	अक्षर __iomem *mmio_base;
	पूर्णांक wc_cookie;
	काष्ठा vgastate state;
	काष्ठा mutex खोलो_lock;
	अचिन्हित पूर्णांक ref_count;
	u32 pseuकरो_palette[16];
पूर्ण;



/* ------------------------------------------------------------------------- */

अटल स्थिर काष्ठा svga_fb_क्रमmat vt8623fb_क्रमmats[] = अणु
	अणु 0,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_TEXT, FB_AUX_TEXT_SVGA_STEP8,	FB_VISUAL_PSEUDOCOLOR, 16, 16पूर्ण,
	अणु 4,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_PSEUDOCOLOR, 16, 16पूर्ण,
	अणु 4,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण, 1,
		FB_TYPE_INTERLEAVED_PLANES, 1,		FB_VISUAL_PSEUDOCOLOR, 16, 16पूर्ण,
	अणु 8,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_PSEUDOCOLOR, 8, 8पूर्ण,
/*	अणु16,  अणु10, 5, 0पूर्ण, अणु5, 5, 0पूर्ण,  अणु0, 5, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 4, 4पूर्ण,	*/
	अणु16,  अणु11, 5, 0पूर्ण, अणु5, 6, 0पूर्ण,  अणु0, 5, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 4, 4पूर्ण,
	अणु32,  अणु16, 8, 0पूर्ण, अणु8, 8, 0पूर्ण,  अणु0, 8, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 2, 2पूर्ण,
	SVGA_FORMAT_END
पूर्ण;

अटल स्थिर काष्ठा svga_pll vt8623_pll = अणु2, 127, 2, 7, 0, 3,
	60000, 300000, 14318पूर्ण;

/* CRT timing रेजिस्टर sets */

अटल स्थिर काष्ठा vga_regset vt8623_h_total_regs[]       = अणुअणु0x00, 0, 7पूर्ण, अणु0x36, 3, 3पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_h_display_regs[]     = अणुअणु0x01, 0, 7पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_h_blank_start_regs[] = अणुअणु0x02, 0, 7पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_h_blank_end_regs[]   = अणुअणु0x03, 0, 4पूर्ण, अणु0x05, 7, 7पूर्ण, अणु0x33, 5, 5पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_h_sync_start_regs[]  = अणुअणु0x04, 0, 7पूर्ण, अणु0x33, 4, 4पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_h_sync_end_regs[]    = अणुअणु0x05, 0, 4पूर्ण, VGA_REGSET_ENDपूर्ण;

अटल स्थिर काष्ठा vga_regset vt8623_v_total_regs[]       = अणुअणु0x06, 0, 7पूर्ण, अणु0x07, 0, 0पूर्ण, अणु0x07, 5, 5पूर्ण, अणु0x35, 0, 0पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_v_display_regs[]     = अणुअणु0x12, 0, 7पूर्ण, अणु0x07, 1, 1पूर्ण, अणु0x07, 6, 6पूर्ण, अणु0x35, 2, 2पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_v_blank_start_regs[] = अणुअणु0x15, 0, 7पूर्ण, अणु0x07, 3, 3पूर्ण, अणु0x09, 5, 5पूर्ण, अणु0x35, 3, 3पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_v_blank_end_regs[]   = अणुअणु0x16, 0, 7पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_v_sync_start_regs[]  = अणुअणु0x10, 0, 7पूर्ण, अणु0x07, 2, 2पूर्ण, अणु0x07, 7, 7पूर्ण, अणु0x35, 1, 1पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_v_sync_end_regs[]    = अणुअणु0x11, 0, 3पूर्ण, VGA_REGSET_ENDपूर्ण;

अटल स्थिर काष्ठा vga_regset vt8623_offset_regs[]        = अणुअणु0x13, 0, 7पूर्ण, अणु0x35, 5, 7पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_line_compare_regs[]  = अणुअणु0x18, 0, 7पूर्ण, अणु0x07, 4, 4पूर्ण, अणु0x09, 6, 6पूर्ण, अणु0x33, 0, 2पूर्ण, अणु0x35, 4, 4पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_fetch_count_regs[]   = अणुअणु0x1C, 0, 7पूर्ण, अणु0x1D, 0, 1पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset vt8623_start_address_regs[] = अणुअणु0x0d, 0, 7पूर्ण, अणु0x0c, 0, 7पूर्ण, अणु0x34, 0, 7पूर्ण, अणु0x48, 0, 1पूर्ण, VGA_REGSET_ENDपूर्ण;

अटल स्थिर काष्ठा svga_timing_regs vt8623_timing_regs     = अणु
	vt8623_h_total_regs, vt8623_h_display_regs, vt8623_h_blank_start_regs,
	vt8623_h_blank_end_regs, vt8623_h_sync_start_regs, vt8623_h_sync_end_regs,
	vt8623_v_total_regs, vt8623_v_display_regs, vt8623_v_blank_start_regs,
	vt8623_v_blank_end_regs, vt8623_v_sync_start_regs, vt8623_v_sync_end_regs,
पूर्ण;


/* ------------------------------------------------------------------------- */


/* Module parameters */

अटल अक्षर *mode_option = "640x480-8@60";
अटल पूर्णांक mtrr = 1;

MODULE_AUTHOR("(c) 2006 Ondrej Zajicek <santiago@crfreenet.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("fbdev driver for integrated graphics core in VIA VT8623 [CLE266]");

module_param(mode_option, अक्षरp, 0644);
MODULE_PARM_DESC(mode_option, "Default video mode ('640x480-8@60', etc)");
module_param_named(mode, mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode, "Default video mode e.g. '648x480-8@60' (deprecated)");
module_param(mtrr, पूर्णांक, 0444);
MODULE_PARM_DESC(mtrr, "Enable write-combining with MTRR (1=enable, 0=disable, default=1)");


/* ------------------------------------------------------------------------- */

अटल व्योम vt8623fb_tilecursor(काष्ठा fb_info *info, काष्ठा fb_tilecursor *cursor)
अणु
	काष्ठा vt8623fb_info *par = info->par;

	svga_tilecursor(par->state.vgabase, info, cursor);
पूर्ण

अटल काष्ठा fb_tile_ops vt8623fb_tile_ops = अणु
	.fb_settile	= svga_settile,
	.fb_tilecopy	= svga_tilecopy,
	.fb_tilefill    = svga_tilefill,
	.fb_tileblit    = svga_tileblit,
	.fb_tilecursor  = vt8623fb_tilecursor,
	.fb_get_tilemax = svga_get_tilemax,
पूर्ण;


/* ------------------------------------------------------------------------- */


/* image data is MSB-first, fb काष्ठाure is MSB-first too */
अटल अंतरभूत u32 expand_color(u32 c)
अणु
	वापस ((c & 1) | ((c & 2) << 7) | ((c & 4) << 14) | ((c & 8) << 21)) * 0xFF;
पूर्ण

/* vt8623fb_iplan_imageblit silently assumes that almost everything is 8-pixel aligned */
अटल व्योम vt8623fb_iplan_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	u32 fg = expand_color(image->fg_color);
	u32 bg = expand_color(image->bg_color);
	स्थिर u8 *src1, *src;
	u8 __iomem *dst1;
	u32 __iomem *dst;
	u32 val;
	पूर्णांक x, y;

	src1 = image->data;
	dst1 = info->screen_base + (image->dy * info->fix.line_length)
		 + ((image->dx / 8) * 4);

	क्रम (y = 0; y < image->height; y++) अणु
		src = src1;
		dst = (u32 __iomem *) dst1;
		क्रम (x = 0; x < image->width; x += 8) अणु
			val = *(src++) * 0x01010101;
			val = (val & fg) | (~val & bg);
			fb_ग_लिखोl(val, dst++);
		पूर्ण
		src1 += image->width / 8;
		dst1 += info->fix.line_length;
	पूर्ण
पूर्ण

/* vt8623fb_iplan_fillrect silently assumes that almost everything is 8-pixel aligned */
अटल व्योम vt8623fb_iplan_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	u32 fg = expand_color(rect->color);
	u8 __iomem *dst1;
	u32 __iomem *dst;
	पूर्णांक x, y;

	dst1 = info->screen_base + (rect->dy * info->fix.line_length)
		 + ((rect->dx / 8) * 4);

	क्रम (y = 0; y < rect->height; y++) अणु
		dst = (u32 __iomem *) dst1;
		क्रम (x = 0; x < rect->width; x += 8) अणु
			fb_ग_लिखोl(fg, dst++);
		पूर्ण
		dst1 += info->fix.line_length;
	पूर्ण
पूर्ण


/* image data is MSB-first, fb काष्ठाure is high-nibble-in-low-byte-first */
अटल अंतरभूत u32 expand_pixel(u32 c)
अणु
	वापस (((c &  1) << 24) | ((c &  2) << 27) | ((c &  4) << 14) | ((c &   8) << 17) |
		((c & 16) <<  4) | ((c & 32) <<  7) | ((c & 64) >>  6) | ((c & 128) >>  3)) * 0xF;
पूर्ण

/* vt8623fb_cfb4_imageblit silently assumes that almost everything is 8-pixel aligned */
अटल व्योम vt8623fb_cfb4_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	u32 fg = image->fg_color * 0x11111111;
	u32 bg = image->bg_color * 0x11111111;
	स्थिर u8 *src1, *src;
	u8 __iomem *dst1;
	u32 __iomem *dst;
	u32 val;
	पूर्णांक x, y;

	src1 = image->data;
	dst1 = info->screen_base + (image->dy * info->fix.line_length)
		 + ((image->dx / 8) * 4);

	क्रम (y = 0; y < image->height; y++) अणु
		src = src1;
		dst = (u32 __iomem *) dst1;
		क्रम (x = 0; x < image->width; x += 8) अणु
			val = expand_pixel(*(src++));
			val = (val & fg) | (~val & bg);
			fb_ग_लिखोl(val, dst++);
		पूर्ण
		src1 += image->width / 8;
		dst1 += info->fix.line_length;
	पूर्ण
पूर्ण

अटल व्योम vt8623fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	अगर ((info->var.bits_per_pixel == 4) && (image->depth == 1)
	    && ((image->width % 8) == 0) && ((image->dx % 8) == 0)) अणु
		अगर (info->fix.type == FB_TYPE_INTERLEAVED_PLANES)
			vt8623fb_iplan_imageblit(info, image);
		अन्यथा
			vt8623fb_cfb4_imageblit(info, image);
	पूर्ण अन्यथा
		cfb_imageblit(info, image);
पूर्ण

अटल व्योम vt8623fb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	अगर ((info->var.bits_per_pixel == 4)
	    && ((rect->width % 8) == 0) && ((rect->dx % 8) == 0)
	    && (info->fix.type == FB_TYPE_INTERLEAVED_PLANES))
		vt8623fb_iplan_fillrect(info, rect);
	 अन्यथा
		cfb_fillrect(info, rect);
पूर्ण


/* ------------------------------------------------------------------------- */


अटल व्योम vt8623_set_pixघड़ी(काष्ठा fb_info *info, u32 pixघड़ी)
अणु
	काष्ठा vt8623fb_info *par = info->par;
	u16 m, n, r;
	u8 regval;
	पूर्णांक rv;

	rv = svga_compute_pll(&vt8623_pll, 1000000000 / pixघड़ी, &m, &n, &r, info->node);
	अगर (rv < 0) अणु
		fb_err(info, "cannot set requested pixclock, keeping old value\n");
		वापस;
	पूर्ण

	/* Set VGA misc रेजिस्टर  */
	regval = vga_r(par->state.vgabase, VGA_MIS_R);
	vga_w(par->state.vgabase, VGA_MIS_W, regval | VGA_MIS_ENB_PLL_LOAD);

	/* Set घड़ी रेजिस्टरs */
	vga_wseq(par->state.vgabase, 0x46, (n  | (r << 6)));
	vga_wseq(par->state.vgabase, 0x47, m);

	udelay(1000);

	/* PLL reset */
	svga_wseq_mask(par->state.vgabase, 0x40, 0x02, 0x02);
	svga_wseq_mask(par->state.vgabase, 0x40, 0x00, 0x02);
पूर्ण


अटल पूर्णांक vt8623fb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा vt8623fb_info *par = info->par;

	mutex_lock(&(par->खोलो_lock));
	अगर (par->ref_count == 0) अणु
		व्योम __iomem *vgabase = par->state.vgabase;

		स_रखो(&(par->state), 0, माप(काष्ठा vgastate));
		par->state.vgabase = vgabase;
		par->state.flags = VGA_SAVE_MODE | VGA_SAVE_FONTS | VGA_SAVE_CMAP;
		par->state.num_crtc = 0xA2;
		par->state.num_seq = 0x50;
		save_vga(&(par->state));
	पूर्ण

	par->ref_count++;
	mutex_unlock(&(par->खोलो_lock));

	वापस 0;
पूर्ण

अटल पूर्णांक vt8623fb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा vt8623fb_info *par = info->par;

	mutex_lock(&(par->खोलो_lock));
	अगर (par->ref_count == 0) अणु
		mutex_unlock(&(par->खोलो_lock));
		वापस -EINVAL;
	पूर्ण

	अगर (par->ref_count == 1)
		restore_vga(&(par->state));

	par->ref_count--;
	mutex_unlock(&(par->खोलो_lock));

	वापस 0;
पूर्ण

अटल पूर्णांक vt8623fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	पूर्णांक rv, mem, step;

	/* Find appropriate क्रमmat */
	rv = svga_match_क्रमmat (vt8623fb_क्रमmats, var, शून्य);
	अगर (rv < 0)
	अणु
		fb_err(info, "unsupported mode requested\n");
		वापस rv;
	पूर्ण

	/* Do not allow to have real resoulution larger than भव */
	अगर (var->xres > var->xres_भव)
		var->xres_भव = var->xres;

	अगर (var->yres > var->yres_भव)
		var->yres_भव = var->yres;

	/* Round up xres_भव to have proper alignment of lines */
	step = vt8623fb_क्रमmats[rv].xresstep - 1;
	var->xres_भव = (var->xres_भव+step) & ~step;

	/* Check whether have enough memory */
	mem = ((var->bits_per_pixel * var->xres_भव) >> 3) * var->yres_भव;
	अगर (mem > info->screen_size)
	अणु
		fb_err(info, "not enough framebuffer memory (%d kB requested, %d kB available)\n",
		       mem >> 10, (अचिन्हित पूर्णांक) (info->screen_size >> 10));
		वापस -EINVAL;
	पूर्ण

	/* Text mode is limited to 256 kB of memory */
	अगर ((var->bits_per_pixel == 0) && (mem > (256*1024)))
	अणु
		fb_err(info, "text framebuffer size too large (%d kB requested, 256 kB possible)\n",
		       mem >> 10);
		वापस -EINVAL;
	पूर्ण

	rv = svga_check_timings (&vt8623_timing_regs, var, info->node);
	अगर (rv < 0)
	अणु
		fb_err(info, "invalid timings requested\n");
		वापस rv;
	पूर्ण

	/* Interlaced mode not supported */
	अगर (var->vmode & FB_VMODE_INTERLACED)
		वापस -EINVAL;

	वापस 0;
पूर्ण


अटल पूर्णांक vt8623fb_set_par(काष्ठा fb_info *info)
अणु
	u32 mode, offset_value, fetch_value, screen_size;
	काष्ठा vt8623fb_info *par = info->par;
	u32 bpp = info->var.bits_per_pixel;

	अगर (bpp != 0) अणु
		info->fix.ypanstep = 1;
		info->fix.line_length = (info->var.xres_भव * bpp) / 8;

		info->flags &= ~FBINFO_MISC_TILEBLITTING;
		info->tileops = शून्य;

		/* in 4bpp supports 8p wide tiles only, any tiles otherwise */
		info->pixmap.blit_x = (bpp == 4) ? (1 << (8 - 1)) : (~(u32)0);
		info->pixmap.blit_y = ~(u32)0;

		offset_value = (info->var.xres_भव * bpp) / 64;
		fetch_value  = ((info->var.xres * bpp) / 128) + 4;

		अगर (bpp == 4)
			fetch_value  = (info->var.xres / 8) + 8; /* + 0 is OK */

		screen_size  = info->var.yres_भव * info->fix.line_length;
	पूर्ण अन्यथा अणु
		info->fix.ypanstep = 16;
		info->fix.line_length = 0;

		info->flags |= FBINFO_MISC_TILEBLITTING;
		info->tileops = &vt8623fb_tile_ops;

		/* supports 8x16 tiles only */
		info->pixmap.blit_x = 1 << (8 - 1);
		info->pixmap.blit_y = 1 << (16 - 1);

		offset_value = info->var.xres_भव / 16;
		fetch_value  = (info->var.xres / 8) + 8;
		screen_size  = (info->var.xres_भव * info->var.yres_भव) / 64;
	पूर्ण

	info->var.xoffset = 0;
	info->var.yoffset = 0;
	info->var.activate = FB_ACTIVATE_NOW;

	/* Unlock रेजिस्टरs */
	svga_wseq_mask(par->state.vgabase, 0x10, 0x01, 0x01);
	svga_wcrt_mask(par->state.vgabase, 0x11, 0x00, 0x80);
	svga_wcrt_mask(par->state.vgabase, 0x47, 0x00, 0x01);

	/* Device, screen and sync off */
	svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
	svga_wcrt_mask(par->state.vgabase, 0x36, 0x30, 0x30);
	svga_wcrt_mask(par->state.vgabase, 0x17, 0x00, 0x80);

	/* Set शेष values */
	svga_set_शेष_gfx_regs(par->state.vgabase);
	svga_set_शेष_atc_regs(par->state.vgabase);
	svga_set_शेष_seq_regs(par->state.vgabase);
	svga_set_शेष_crt_regs(par->state.vgabase);
	svga_wcrt_multi(par->state.vgabase, vt8623_line_compare_regs, 0xFFFFFFFF);
	svga_wcrt_multi(par->state.vgabase, vt8623_start_address_regs, 0);

	svga_wcrt_multi(par->state.vgabase, vt8623_offset_regs, offset_value);
	svga_wseq_multi(par->state.vgabase, vt8623_fetch_count_regs, fetch_value);

	/* Clear H/V Skew */
	svga_wcrt_mask(par->state.vgabase, 0x03, 0x00, 0x60);
	svga_wcrt_mask(par->state.vgabase, 0x05, 0x00, 0x60);

	अगर (info->var.vmode & FB_VMODE_DOUBLE)
		svga_wcrt_mask(par->state.vgabase, 0x09, 0x80, 0x80);
	अन्यथा
		svga_wcrt_mask(par->state.vgabase, 0x09, 0x00, 0x80);

	svga_wseq_mask(par->state.vgabase, 0x1E, 0xF0, 0xF0); // DI/DVP bus
	svga_wseq_mask(par->state.vgabase, 0x2A, 0x0F, 0x0F); // DI/DVP bus
	svga_wseq_mask(par->state.vgabase, 0x16, 0x08, 0xBF); // FIFO पढ़ो threshold
	vga_wseq(par->state.vgabase, 0x17, 0x1F);       // FIFO depth
	vga_wseq(par->state.vgabase, 0x18, 0x4E);
	svga_wseq_mask(par->state.vgabase, 0x1A, 0x08, 0x08); // enable MMIO ?

	vga_wcrt(par->state.vgabase, 0x32, 0x00);
	vga_wcrt(par->state.vgabase, 0x34, 0x00);
	vga_wcrt(par->state.vgabase, 0x6A, 0x80);
	vga_wcrt(par->state.vgabase, 0x6A, 0xC0);

	vga_wgfx(par->state.vgabase, 0x20, 0x00);
	vga_wgfx(par->state.vgabase, 0x21, 0x00);
	vga_wgfx(par->state.vgabase, 0x22, 0x00);

	/* Set SR15 according to number of bits per pixel */
	mode = svga_match_क्रमmat(vt8623fb_क्रमmats, &(info->var), &(info->fix));
	चयन (mode) अणु
	हाल 0:
		fb_dbg(info, "text mode\n");
		svga_set_texपंचांगode_vga_regs(par->state.vgabase);
		svga_wseq_mask(par->state.vgabase, 0x15, 0x00, 0xFE);
		svga_wcrt_mask(par->state.vgabase, 0x11, 0x60, 0x70);
		अवरोध;
	हाल 1:
		fb_dbg(info, "4 bit pseudocolor\n");
		vga_wgfx(par->state.vgabase, VGA_GFX_MODE, 0x40);
		svga_wseq_mask(par->state.vgabase, 0x15, 0x20, 0xFE);
		svga_wcrt_mask(par->state.vgabase, 0x11, 0x00, 0x70);
		अवरोध;
	हाल 2:
		fb_dbg(info, "4 bit pseudocolor, planar\n");
		svga_wseq_mask(par->state.vgabase, 0x15, 0x00, 0xFE);
		svga_wcrt_mask(par->state.vgabase, 0x11, 0x00, 0x70);
		अवरोध;
	हाल 3:
		fb_dbg(info, "8 bit pseudocolor\n");
		svga_wseq_mask(par->state.vgabase, 0x15, 0x22, 0xFE);
		अवरोध;
	हाल 4:
		fb_dbg(info, "5/6/5 truecolor\n");
		svga_wseq_mask(par->state.vgabase, 0x15, 0xB6, 0xFE);
		अवरोध;
	हाल 5:
		fb_dbg(info, "8/8/8 truecolor\n");
		svga_wseq_mask(par->state.vgabase, 0x15, 0xAE, 0xFE);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "vt8623fb: unsupported mode - bug\n");
		वापस (-EINVAL);
	पूर्ण

	vt8623_set_pixघड़ी(info, info->var.pixघड़ी);
	svga_set_timings(par->state.vgabase, &vt8623_timing_regs, &(info->var), 1, 1,
			 (info->var.vmode & FB_VMODE_DOUBLE) ? 2 : 1, 1,
			 1, info->node);

	स_रखो_io(info->screen_base, 0x00, screen_size);

	/* Device and screen back on */
	svga_wcrt_mask(par->state.vgabase, 0x17, 0x80, 0x80);
	svga_wcrt_mask(par->state.vgabase, 0x36, 0x00, 0x30);
	svga_wseq_mask(par->state.vgabase, 0x01, 0x00, 0x20);

	वापस 0;
पूर्ण


अटल पूर्णांक vt8623fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
				u_पूर्णांक transp, काष्ठा fb_info *fb)
अणु
	चयन (fb->var.bits_per_pixel) अणु
	हाल 0:
	हाल 4:
		अगर (regno >= 16)
			वापस -EINVAL;

		outb(0x0F, VGA_PEL_MSK);
		outb(regno, VGA_PEL_IW);
		outb(red >> 10, VGA_PEL_D);
		outb(green >> 10, VGA_PEL_D);
		outb(blue >> 10, VGA_PEL_D);
		अवरोध;
	हाल 8:
		अगर (regno >= 256)
			वापस -EINVAL;

		outb(0xFF, VGA_PEL_MSK);
		outb(regno, VGA_PEL_IW);
		outb(red >> 10, VGA_PEL_D);
		outb(green >> 10, VGA_PEL_D);
		outb(blue >> 10, VGA_PEL_D);
		अवरोध;
	हाल 16:
		अगर (regno >= 16)
			वापस 0;

		अगर (fb->var.green.length == 5)
			((u32*)fb->pseuकरो_palette)[regno] = ((red & 0xF800) >> 1) |
				((green & 0xF800) >> 6) | ((blue & 0xF800) >> 11);
		अन्यथा अगर (fb->var.green.length == 6)
			((u32*)fb->pseuकरो_palette)[regno] = (red & 0xF800) |
				((green & 0xFC00) >> 5) | ((blue & 0xF800) >> 11);
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल 24:
	हाल 32:
		अगर (regno >= 16)
			वापस 0;

		/* ((transp & 0xFF00) << 16) */
		((u32*)fb->pseuकरो_palette)[regno] = ((red & 0xFF00) << 8) |
			(green & 0xFF00) | ((blue & 0xFF00) >> 8);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक vt8623fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा vt8623fb_info *par = info->par;

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		fb_dbg(info, "unblank\n");
		svga_wcrt_mask(par->state.vgabase, 0x36, 0x00, 0x30);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x00, 0x20);
		अवरोध;
	हाल FB_BLANK_NORMAL:
		fb_dbg(info, "blank\n");
		svga_wcrt_mask(par->state.vgabase, 0x36, 0x00, 0x30);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		fb_dbg(info, "DPMS standby (hsync off)\n");
		svga_wcrt_mask(par->state.vgabase, 0x36, 0x10, 0x30);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		fb_dbg(info, "DPMS suspend (vsync off)\n");
		svga_wcrt_mask(par->state.vgabase, 0x36, 0x20, 0x30);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		fb_dbg(info, "DPMS off (no sync)\n");
		svga_wcrt_mask(par->state.vgabase, 0x36, 0x30, 0x30);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक vt8623fb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा vt8623fb_info *par = info->par;
	अचिन्हित पूर्णांक offset;

	/* Calculate the offset */
	अगर (info->var.bits_per_pixel == 0) अणु
		offset = (var->yoffset / 16) * info->var.xres_भव
		       + var->xoffset;
		offset = offset >> 3;
	पूर्ण अन्यथा अणु
		offset = (var->yoffset * info->fix.line_length) +
			 (var->xoffset * info->var.bits_per_pixel / 8);
		offset = offset >> ((info->var.bits_per_pixel == 4) ? 2 : 1);
	पूर्ण

	/* Set the offset */
	svga_wcrt_multi(par->state.vgabase, vt8623_start_address_regs, offset);

	वापस 0;
पूर्ण


/* ------------------------------------------------------------------------- */


/* Frame buffer operations */

अटल स्थिर काष्ठा fb_ops vt8623fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= vt8623fb_खोलो,
	.fb_release	= vt8623fb_release,
	.fb_check_var	= vt8623fb_check_var,
	.fb_set_par	= vt8623fb_set_par,
	.fb_setcolreg	= vt8623fb_setcolreg,
	.fb_blank	= vt8623fb_blank,
	.fb_pan_display	= vt8623fb_pan_display,
	.fb_fillrect	= vt8623fb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= vt8623fb_imageblit,
	.fb_get_caps    = svga_get_caps,
पूर्ण;


/* PCI probe */

अटल पूर्णांक vt8623_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pci_bus_region bus_reg;
	काष्ठा resource vga_res;
	काष्ठा fb_info *info;
	काष्ठा vt8623fb_info *par;
	अचिन्हित पूर्णांक memsize1, memsize2;
	पूर्णांक rc;

	/* Ignore secondary VGA device because there is no VGA arbitration */
	अगर (! svga_primary_device(dev)) अणु
		dev_info(&(dev->dev), "ignoring secondary device\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate and fill driver data काष्ठाure */
	info = framebuffer_alloc(माप(काष्ठा vt8623fb_info), &(dev->dev));
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	mutex_init(&par->खोलो_lock);

	info->flags = FBINFO_PARTIAL_PAN_OK | FBINFO_HWACCEL_YPAN;
	info->fbops = &vt8623fb_ops;

	/* Prepare PCI device */

	rc = pci_enable_device(dev);
	अगर (rc < 0) अणु
		dev_err(info->device, "cannot enable PCI device\n");
		जाओ err_enable_device;
	पूर्ण

	rc = pci_request_regions(dev, "vt8623fb");
	अगर (rc < 0) अणु
		dev_err(info->device, "cannot reserve framebuffer region\n");
		जाओ err_request_regions;
	पूर्ण

	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = pci_resource_len(dev, 0);
	info->fix.mmio_start = pci_resource_start(dev, 1);
	info->fix.mmio_len = pci_resource_len(dev, 1);

	/* Map physical IO memory address पूर्णांकo kernel space */
	info->screen_base = pci_iomap_wc(dev, 0, 0);
	अगर (! info->screen_base) अणु
		rc = -ENOMEM;
		dev_err(info->device, "iomap for framebuffer failed\n");
		जाओ err_iomap_1;
	पूर्ण

	par->mmio_base = pci_iomap(dev, 1, 0);
	अगर (! par->mmio_base) अणु
		rc = -ENOMEM;
		dev_err(info->device, "iomap for MMIO failed\n");
		जाओ err_iomap_2;
	पूर्ण

	bus_reg.start = 0;
	bus_reg.end = 64 * 1024;

	vga_res.flags = IORESOURCE_IO;

	pcibios_bus_to_resource(dev->bus, &vga_res, &bus_reg);

	par->state.vgabase = (व्योम __iomem *) (अचिन्हित दीर्घ) vga_res.start;

	/* Find how many physical memory there is on card */
	memsize1 = (vga_rseq(par->state.vgabase, 0x34) + 1) >> 1;
	memsize2 = vga_rseq(par->state.vgabase, 0x39) << 2;

	अगर ((16 <= memsize1) && (memsize1 <= 64) && (memsize1 == memsize2))
		info->screen_size = memsize1 << 20;
	अन्यथा अणु
		dev_err(info->device, "memory size detection failed (%x %x), suppose 16 MB\n", memsize1, memsize2);
		info->screen_size = 16 << 20;
	पूर्ण

	info->fix.smem_len = info->screen_size;
	म_नकल(info->fix.id, "VIA VT8623");
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
	info->fix.ypanstep = 0;
	info->fix.accel = FB_ACCEL_NONE;
	info->pseuकरो_palette = (व्योम*)par->pseuकरो_palette;

	/* Prepare startup mode */

	kernel_param_lock(THIS_MODULE);
	rc = fb_find_mode(&(info->var), info, mode_option, शून्य, 0, शून्य, 8);
	kernel_param_unlock(THIS_MODULE);
	अगर (! ((rc == 1) || (rc == 2))) अणु
		rc = -EINVAL;
		dev_err(info->device, "mode %s not found\n", mode_option);
		जाओ err_find_mode;
	पूर्ण

	rc = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (rc < 0) अणु
		dev_err(info->device, "cannot allocate colormap\n");
		जाओ err_alloc_cmap;
	पूर्ण

	rc = रेजिस्टर_framebuffer(info);
	अगर (rc < 0) अणु
		dev_err(info->device, "cannot register framebuffer\n");
		जाओ err_reg_fb;
	पूर्ण

	fb_info(info, "%s on %s, %d MB RAM\n",
		info->fix.id, pci_name(dev), info->fix.smem_len >> 20);

	/* Record a reference to the driver data */
	pci_set_drvdata(dev, info);

	अगर (mtrr)
		par->wc_cookie = arch_phys_wc_add(info->fix.smem_start,
						  info->fix.smem_len);

	वापस 0;

	/* Error handling */
err_reg_fb:
	fb_dealloc_cmap(&info->cmap);
err_alloc_cmap:
err_find_mode:
	pci_iounmap(dev, par->mmio_base);
err_iomap_2:
	pci_iounmap(dev, info->screen_base);
err_iomap_1:
	pci_release_regions(dev);
err_request_regions:
/*	pci_disable_device(dev); */
err_enable_device:
	framebuffer_release(info);
	वापस rc;
पूर्ण

/* PCI हटाओ */

अटल व्योम vt8623_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);

	अगर (info) अणु
		काष्ठा vt8623fb_info *par = info->par;

		arch_phys_wc_del(par->wc_cookie);
		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);

		pci_iounmap(dev, info->screen_base);
		pci_iounmap(dev, par->mmio_base);
		pci_release_regions(dev);
/*		pci_disable_device(dev); */

		framebuffer_release(info);
	पूर्ण
पूर्ण


/* PCI suspend */

अटल पूर्णांक __maybe_unused vt8623_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा vt8623fb_info *par = info->par;

	dev_info(info->device, "suspend\n");

	console_lock();
	mutex_lock(&(par->खोलो_lock));

	अगर (par->ref_count == 0) अणु
		mutex_unlock(&(par->खोलो_lock));
		console_unlock();
		वापस 0;
	पूर्ण

	fb_set_suspend(info, 1);

	mutex_unlock(&(par->खोलो_lock));
	console_unlock();

	वापस 0;
पूर्ण


/* PCI resume */

अटल पूर्णांक __maybe_unused vt8623_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा vt8623fb_info *par = info->par;

	dev_info(info->device, "resume\n");

	console_lock();
	mutex_lock(&(par->खोलो_lock));

	अगर (par->ref_count == 0)
		जाओ fail;

	vt8623fb_set_par(info);
	fb_set_suspend(info, 0);

fail:
	mutex_unlock(&(par->खोलो_lock));
	console_unlock();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vt8623_pci_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= vt8623_pci_suspend,
	.resume		= vt8623_pci_resume,
	.मुक्तze		= शून्य,
	.thaw		= vt8623_pci_resume,
	.घातeroff	= vt8623_pci_suspend,
	.restore	= vt8623_pci_resume,
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
पूर्ण;

/* List of boards that we are trying to support */

अटल स्थिर काष्ठा pci_device_id vt8623_devices[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_VIA, 0x3122)पूर्ण,
	अणु0, 0, 0, 0, 0, 0, 0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, vt8623_devices);

अटल काष्ठा pci_driver vt8623fb_pci_driver = अणु
	.name		= "vt8623fb",
	.id_table	= vt8623_devices,
	.probe		= vt8623_pci_probe,
	.हटाओ		= vt8623_pci_हटाओ,
	.driver.pm	= &vt8623_pci_pm_ops,
पूर्ण;

/* Cleanup */

अटल व्योम __निकास vt8623fb_cleanup(व्योम)
अणु
	pr_debug("vt8623fb: cleaning up\n");
	pci_unरेजिस्टर_driver(&vt8623fb_pci_driver);
पूर्ण

/* Driver Initialisation */

अटल पूर्णांक __init vt8623fb_init(व्योम)
अणु

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("vt8623fb", &option))
		वापस -ENODEV;

	अगर (option && *option)
		mode_option = option;
#पूर्ण_अगर

	pr_debug("vt8623fb: initializing\n");
	वापस pci_रेजिस्टर_driver(&vt8623fb_pci_driver);
पूर्ण

/* ------------------------------------------------------------------------- */

/* Modularization */

module_init(vt8623fb_init);
module_निकास(vt8623fb_cleanup);
