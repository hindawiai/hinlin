<शैली गुरु>
/*
 *  linux/drivers/video/arkfb.c -- Frame buffer device driver क्रम ARK 2000PV
 *  with ICS 5342 dac (it is easy to add support क्रम dअगरferent dacs).
 *
 *  Copyright (c) 2007 Ondrej Zajicek <santiago@crमुक्तnet.org>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 *  Code is based on s3fb
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/svga.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/console.h> /* Why should fb driver call console functions? because console_lock() */
#समावेश <video/vga.h>

काष्ठा arkfb_info अणु
	पूर्णांक mclk_freq;
	पूर्णांक wc_cookie;

	काष्ठा dac_info *dac;
	काष्ठा vgastate state;
	काष्ठा mutex खोलो_lock;
	अचिन्हित पूर्णांक ref_count;
	u32 pseuकरो_palette[16];
पूर्ण;


/* ------------------------------------------------------------------------- */


अटल स्थिर काष्ठा svga_fb_क्रमmat arkfb_क्रमmats[] = अणु
	अणु 0,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_TEXT, FB_AUX_TEXT_SVGA_STEP4,	FB_VISUAL_PSEUDOCOLOR, 8, 8पूर्ण,
	अणु 4,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_PSEUDOCOLOR, 8, 16पूर्ण,
	अणु 4,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण, 1,
		FB_TYPE_INTERLEAVED_PLANES, 1,		FB_VISUAL_PSEUDOCOLOR, 8, 16पूर्ण,
	अणु 8,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_PSEUDOCOLOR, 8, 8पूर्ण,
	अणु16,  अणु10, 5, 0पूर्ण, अणु5, 5, 0पूर्ण,  अणु0, 5, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 4, 4पूर्ण,
	अणु16,  अणु11, 5, 0पूर्ण, अणु5, 6, 0पूर्ण,  अणु0, 5, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 4, 4पूर्ण,
	अणु24,  अणु16, 8, 0पूर्ण, अणु8, 8, 0पूर्ण,  अणु0, 8, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 8, 8पूर्ण,
	अणु32,  अणु16, 8, 0पूर्ण, अणु8, 8, 0पूर्ण,  अणु0, 8, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 2, 2पूर्ण,
	SVGA_FORMAT_END
पूर्ण;


/* CRT timing रेजिस्टर sets */

अटल स्थिर काष्ठा vga_regset ark_h_total_regs[]        = अणुअणु0x00, 0, 7पूर्ण, अणु0x41, 7, 7पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_h_display_regs[]      = अणुअणु0x01, 0, 7पूर्ण, अणु0x41, 6, 6पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_h_blank_start_regs[]  = अणुअणु0x02, 0, 7पूर्ण, अणु0x41, 5, 5पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_h_blank_end_regs[]    = अणुअणु0x03, 0, 4पूर्ण, अणु0x05, 7, 7	पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_h_sync_start_regs[]   = अणुअणु0x04, 0, 7पूर्ण, अणु0x41, 4, 4पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_h_sync_end_regs[]     = अणुअणु0x05, 0, 4पूर्ण, VGA_REGSET_ENDपूर्ण;

अटल स्थिर काष्ठा vga_regset ark_v_total_regs[]        = अणुअणु0x06, 0, 7पूर्ण, अणु0x07, 0, 0पूर्ण, अणु0x07, 5, 5पूर्ण, अणु0x40, 7, 7पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_v_display_regs[]      = अणुअणु0x12, 0, 7पूर्ण, अणु0x07, 1, 1पूर्ण, अणु0x07, 6, 6पूर्ण, अणु0x40, 6, 6पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_v_blank_start_regs[]  = अणुअणु0x15, 0, 7पूर्ण, अणु0x07, 3, 3पूर्ण, अणु0x09, 5, 5पूर्ण, अणु0x40, 5, 5पूर्ण, VGA_REGSET_ENDपूर्ण;
// स्थिर काष्ठा vga_regset ark_v_blank_end_regs[]    = अणुअणु0x16, 0, 6पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_v_blank_end_regs[]    = अणुअणु0x16, 0, 7पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_v_sync_start_regs[]   = अणुअणु0x10, 0, 7पूर्ण, अणु0x07, 2, 2पूर्ण, अणु0x07, 7, 7पूर्ण, अणु0x40, 4, 4पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_v_sync_end_regs[]     = अणुअणु0x11, 0, 3पूर्ण, VGA_REGSET_ENDपूर्ण;

अटल स्थिर काष्ठा vga_regset ark_line_compare_regs[]   = अणुअणु0x18, 0, 7पूर्ण, अणु0x07, 4, 4पूर्ण, अणु0x09, 6, 6पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_start_address_regs[]  = अणुअणु0x0d, 0, 7पूर्ण, अणु0x0c, 0, 7पूर्ण, अणु0x40, 0, 2पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset ark_offset_regs[]         = अणुअणु0x13, 0, 7पूर्ण, अणु0x41, 3, 3पूर्ण, VGA_REGSET_ENDपूर्ण;

अटल स्थिर काष्ठा svga_timing_regs ark_timing_regs     = अणु
	ark_h_total_regs, ark_h_display_regs, ark_h_blank_start_regs,
	ark_h_blank_end_regs, ark_h_sync_start_regs, ark_h_sync_end_regs,
	ark_v_total_regs, ark_v_display_regs, ark_v_blank_start_regs,
	ark_v_blank_end_regs, ark_v_sync_start_regs, ark_v_sync_end_regs,
पूर्ण;


/* ------------------------------------------------------------------------- */


/* Module parameters */

अटल अक्षर *mode_option = "640x480-8@60";

MODULE_AUTHOR("(c) 2007 Ondrej Zajicek <santiago@crfreenet.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("fbdev driver for ARK 2000PV");

module_param(mode_option, अक्षरp, 0444);
MODULE_PARM_DESC(mode_option, "Default video mode ('640x480-8@60', etc)");
module_param_named(mode, mode_option, अक्षरp, 0444);
MODULE_PARM_DESC(mode, "Default video mode ('640x480-8@60', etc) (deprecated)");

अटल पूर्णांक threshold = 4;

module_param(threshold, पूर्णांक, 0644);
MODULE_PARM_DESC(threshold, "FIFO threshold");


/* ------------------------------------------------------------------------- */


अटल व्योम arkfb_settile(काष्ठा fb_info *info, काष्ठा fb_tilemap *map)
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
			fb_ग_लिखोb(font[i], &fb[i * 4]);
			fb_ग_लिखोb(font[i], &fb[i * 4 + (128 * 8)]);
		पूर्ण
		fb += 128;

		अगर ((c % 8) == 7)
			fb += 128*8;

		font += map->height;
	पूर्ण
पूर्ण

अटल व्योम arkfb_tilecursor(काष्ठा fb_info *info, काष्ठा fb_tilecursor *cursor)
अणु
	काष्ठा arkfb_info *par = info->par;

	svga_tilecursor(par->state.vgabase, info, cursor);
पूर्ण

अटल काष्ठा fb_tile_ops arkfb_tile_ops = अणु
	.fb_settile	= arkfb_settile,
	.fb_tilecopy	= svga_tilecopy,
	.fb_tilefill    = svga_tilefill,
	.fb_tileblit    = svga_tileblit,
	.fb_tilecursor  = arkfb_tilecursor,
	.fb_get_tilemax = svga_get_tilemax,
पूर्ण;


/* ------------------------------------------------------------------------- */


/* image data is MSB-first, fb काष्ठाure is MSB-first too */
अटल अंतरभूत u32 expand_color(u32 c)
अणु
	वापस ((c & 1) | ((c & 2) << 7) | ((c & 4) << 14) | ((c & 8) << 21)) * 0xFF;
पूर्ण

/* arkfb_iplan_imageblit silently assumes that almost everything is 8-pixel aligned */
अटल व्योम arkfb_iplan_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
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

/* arkfb_iplan_fillrect silently assumes that almost everything is 8-pixel aligned */
अटल व्योम arkfb_iplan_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
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

/* arkfb_cfb4_imageblit silently assumes that almost everything is 8-pixel aligned */
अटल व्योम arkfb_cfb4_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
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

अटल व्योम arkfb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	अगर ((info->var.bits_per_pixel == 4) && (image->depth == 1)
	    && ((image->width % 8) == 0) && ((image->dx % 8) == 0)) अणु
		अगर (info->fix.type == FB_TYPE_INTERLEAVED_PLANES)
			arkfb_iplan_imageblit(info, image);
		अन्यथा
			arkfb_cfb4_imageblit(info, image);
	पूर्ण अन्यथा
		cfb_imageblit(info, image);
पूर्ण

अटल व्योम arkfb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	अगर ((info->var.bits_per_pixel == 4)
	    && ((rect->width % 8) == 0) && ((rect->dx % 8) == 0)
	    && (info->fix.type == FB_TYPE_INTERLEAVED_PLANES))
		arkfb_iplan_fillrect(info, rect);
	 अन्यथा
		cfb_fillrect(info, rect);
पूर्ण


/* ------------------------------------------------------------------------- */


क्रमागत
अणु
	DAC_PSEUDO8_8,
	DAC_RGB1555_8,
	DAC_RGB0565_8,
	DAC_RGB0888_8,
	DAC_RGB8888_8,
	DAC_PSEUDO8_16,
	DAC_RGB1555_16,
	DAC_RGB0565_16,
	DAC_RGB0888_16,
	DAC_RGB8888_16,
	DAC_MAX
पूर्ण;

काष्ठा dac_ops अणु
	पूर्णांक (*dac_get_mode)(काष्ठा dac_info *info);
	पूर्णांक (*dac_set_mode)(काष्ठा dac_info *info, पूर्णांक mode);
	पूर्णांक (*dac_get_freq)(काष्ठा dac_info *info, पूर्णांक channel);
	पूर्णांक (*dac_set_freq)(काष्ठा dac_info *info, पूर्णांक channel, u32 freq);
	व्योम (*dac_release)(काष्ठा dac_info *info);
पूर्ण;

प्रकार व्योम (*dac_पढ़ो_regs_t)(व्योम *data, u8 *code, पूर्णांक count);
प्रकार व्योम (*dac_ग_लिखो_regs_t)(व्योम *data, u8 *code, पूर्णांक count);

काष्ठा dac_info
अणु
	काष्ठा dac_ops *dacops;
	dac_पढ़ो_regs_t dac_पढ़ो_regs;
	dac_ग_लिखो_regs_t dac_ग_लिखो_regs;
	व्योम *data;
पूर्ण;


अटल अंतरभूत u8 dac_पढ़ो_reg(काष्ठा dac_info *info, u8 reg)
अणु
	u8 code[2] = अणुreg, 0पूर्ण;
	info->dac_पढ़ो_regs(info->data, code, 1);
	वापस code[1];
पूर्ण

अटल अंतरभूत व्योम dac_पढ़ो_regs(काष्ठा dac_info *info, u8 *code, पूर्णांक count)
अणु
	info->dac_पढ़ो_regs(info->data, code, count);
पूर्ण

अटल अंतरभूत व्योम dac_ग_लिखो_reg(काष्ठा dac_info *info, u8 reg, u8 val)
अणु
	u8 code[2] = अणुreg, valपूर्ण;
	info->dac_ग_लिखो_regs(info->data, code, 1);
पूर्ण

अटल अंतरभूत व्योम dac_ग_लिखो_regs(काष्ठा dac_info *info, u8 *code, पूर्णांक count)
अणु
	info->dac_ग_लिखो_regs(info->data, code, count);
पूर्ण

अटल अंतरभूत पूर्णांक dac_set_mode(काष्ठा dac_info *info, पूर्णांक mode)
अणु
	वापस info->dacops->dac_set_mode(info, mode);
पूर्ण

अटल अंतरभूत पूर्णांक dac_set_freq(काष्ठा dac_info *info, पूर्णांक channel, u32 freq)
अणु
	वापस info->dacops->dac_set_freq(info, channel, freq);
पूर्ण

अटल अंतरभूत व्योम dac_release(काष्ठा dac_info *info)
अणु
	info->dacops->dac_release(info);
पूर्ण


/* ------------------------------------------------------------------------- */


/* ICS5342 DAC */

काष्ठा ics5342_info
अणु
	काष्ठा dac_info dac;
	u8 mode;
पूर्ण;

#घोषणा DAC_PAR(info) ((काष्ठा ics5342_info *) info)

/* LSB is set to distinguish unused slots */
अटल स्थिर u8 ics5342_mode_table[DAC_MAX] = अणु
	[DAC_PSEUDO8_8]  = 0x01, [DAC_RGB1555_8]  = 0x21, [DAC_RGB0565_8]  = 0x61,
	[DAC_RGB0888_8]  = 0x41, [DAC_PSEUDO8_16] = 0x11, [DAC_RGB1555_16] = 0x31,
	[DAC_RGB0565_16] = 0x51, [DAC_RGB0888_16] = 0x91, [DAC_RGB8888_16] = 0x71
पूर्ण;

अटल पूर्णांक ics5342_set_mode(काष्ठा dac_info *info, पूर्णांक mode)
अणु
	u8 code;

	अगर (mode >= DAC_MAX)
		वापस -EINVAL;

	code = ics5342_mode_table[mode];

	अगर (! code)
		वापस -EINVAL;

	dac_ग_लिखो_reg(info, 6, code & 0xF0);
	DAC_PAR(info)->mode = mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा svga_pll ics5342_pll = अणु3, 129, 3, 33, 0, 3,
	60000, 250000, 14318पूर्ण;

/* pd4 - allow only posभागider 4 (r=2) */
अटल स्थिर काष्ठा svga_pll ics5342_pll_pd4 = अणु3, 129, 3, 33, 2, 2,
	60000, 335000, 14318पूर्ण;

/* 270 MHz should be upper bound क्रम VCO घड़ी according to specs,
   but that is too restrictive in pd4 हाल */

अटल पूर्णांक ics5342_set_freq(काष्ठा dac_info *info, पूर्णांक channel, u32 freq)
अणु
	u16 m, n, r;

	/* only postभागider 4 (r=2) is valid in mode DAC_PSEUDO8_16 */
	पूर्णांक rv = svga_compute_pll((DAC_PAR(info)->mode == DAC_PSEUDO8_16)
				  ? &ics5342_pll_pd4 : &ics5342_pll,
				  freq, &m, &n, &r, 0);

	अगर (rv < 0) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		u8 code[6] = अणु4, 3, 5, m-2, 5, (n-2) | (r << 5)पूर्ण;
		dac_ग_लिखो_regs(info, code, 3);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ics5342_release(काष्ठा dac_info *info)
अणु
	ics5342_set_mode(info, DAC_PSEUDO8_8);
	kमुक्त(info);
पूर्ण

अटल काष्ठा dac_ops ics5342_ops = अणु
	.dac_set_mode	= ics5342_set_mode,
	.dac_set_freq	= ics5342_set_freq,
	.dac_release	= ics5342_release
पूर्ण;


अटल काष्ठा dac_info * ics5342_init(dac_पढ़ो_regs_t drr, dac_ग_लिखो_regs_t dwr, व्योम *data)
अणु
	काष्ठा dac_info *info = kzalloc(माप(काष्ठा ics5342_info), GFP_KERNEL);

	अगर (! info)
		वापस शून्य;

	info->dacops = &ics5342_ops;
	info->dac_पढ़ो_regs = drr;
	info->dac_ग_लिखो_regs = dwr;
	info->data = data;
	DAC_PAR(info)->mode = DAC_PSEUDO8_8; /* estimation */
	वापस info;
पूर्ण


/* ------------------------------------------------------------------------- */


अटल अचिन्हित लघु dac_regs[4] = अणु0x3c8, 0x3c9, 0x3c6, 0x3c7पूर्ण;

अटल व्योम ark_dac_पढ़ो_regs(व्योम *data, u8 *code, पूर्णांक count)
अणु
	काष्ठा fb_info *info = data;
	काष्ठा arkfb_info *par;
	u8 regval;

	par = info->par;
	regval = vga_rseq(par->state.vgabase, 0x1C);
	जबतक (count != 0)
	अणु
		vga_wseq(par->state.vgabase, 0x1C, regval | (code[0] & 4 ? 0x80 : 0));
		code[1] = vga_r(par->state.vgabase, dac_regs[code[0] & 3]);
		count--;
		code += 2;
	पूर्ण

	vga_wseq(par->state.vgabase, 0x1C, regval);
पूर्ण

अटल व्योम ark_dac_ग_लिखो_regs(व्योम *data, u8 *code, पूर्णांक count)
अणु
	काष्ठा fb_info *info = data;
	काष्ठा arkfb_info *par;
	u8 regval;

	par = info->par;
	regval = vga_rseq(par->state.vgabase, 0x1C);
	जबतक (count != 0)
	अणु
		vga_wseq(par->state.vgabase, 0x1C, regval | (code[0] & 4 ? 0x80 : 0));
		vga_w(par->state.vgabase, dac_regs[code[0] & 3], code[1]);
		count--;
		code += 2;
	पूर्ण

	vga_wseq(par->state.vgabase, 0x1C, regval);
पूर्ण


अटल व्योम ark_set_pixघड़ी(काष्ठा fb_info *info, u32 pixघड़ी)
अणु
	काष्ठा arkfb_info *par = info->par;
	u8 regval;

	पूर्णांक rv = dac_set_freq(par->dac, 0, 1000000000 / pixघड़ी);
	अगर (rv < 0) अणु
		fb_err(info, "cannot set requested pixclock, keeping old value\n");
		वापस;
	पूर्ण

	/* Set VGA misc रेजिस्टर  */
	regval = vga_r(par->state.vgabase, VGA_MIS_R);
	vga_w(par->state.vgabase, VGA_MIS_W, regval | VGA_MIS_ENB_PLL_LOAD);
पूर्ण


/* Open framebuffer */

अटल पूर्णांक arkfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा arkfb_info *par = info->par;

	mutex_lock(&(par->खोलो_lock));
	अगर (par->ref_count == 0) अणु
		व्योम __iomem *vgabase = par->state.vgabase;

		स_रखो(&(par->state), 0, माप(काष्ठा vgastate));
		par->state.vgabase = vgabase;
		par->state.flags = VGA_SAVE_MODE | VGA_SAVE_FONTS | VGA_SAVE_CMAP;
		par->state.num_crtc = 0x60;
		par->state.num_seq = 0x30;
		save_vga(&(par->state));
	पूर्ण

	par->ref_count++;
	mutex_unlock(&(par->खोलो_lock));

	वापस 0;
पूर्ण

/* Close framebuffer */

अटल पूर्णांक arkfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा arkfb_info *par = info->par;

	mutex_lock(&(par->खोलो_lock));
	अगर (par->ref_count == 0) अणु
		mutex_unlock(&(par->खोलो_lock));
		वापस -EINVAL;
	पूर्ण

	अगर (par->ref_count == 1) अणु
		restore_vga(&(par->state));
		dac_set_mode(par->dac, DAC_PSEUDO8_8);
	पूर्ण

	par->ref_count--;
	mutex_unlock(&(par->खोलो_lock));

	वापस 0;
पूर्ण

/* Validate passed in var */

अटल पूर्णांक arkfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	पूर्णांक rv, mem, step;

	/* Find appropriate क्रमmat */
	rv = svga_match_क्रमmat (arkfb_क्रमmats, var, शून्य);
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
	step = arkfb_क्रमmats[rv].xresstep - 1;
	var->xres_भव = (var->xres_भव+step) & ~step;


	/* Check whether have enough memory */
	mem = ((var->bits_per_pixel * var->xres_भव) >> 3) * var->yres_भव;
	अगर (mem > info->screen_size)
	अणु
		fb_err(info, "not enough framebuffer memory (%d kB requested, %d kB available)\n",
		       mem >> 10, (अचिन्हित पूर्णांक) (info->screen_size >> 10));
		वापस -EINVAL;
	पूर्ण

	rv = svga_check_timings (&ark_timing_regs, var, info->node);
	अगर (rv < 0)
	अणु
		fb_err(info, "invalid timings requested\n");
		वापस rv;
	पूर्ण

	/* Interlaced mode is broken */
	अगर (var->vmode & FB_VMODE_INTERLACED)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Set video mode from par */

अटल पूर्णांक arkfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा arkfb_info *par = info->par;
	u32 value, mode, hmul, hभाग, offset_value, screen_size;
	u32 bpp = info->var.bits_per_pixel;
	u8 regval;

	अगर (bpp != 0) अणु
		info->fix.ypanstep = 1;
		info->fix.line_length = (info->var.xres_भव * bpp) / 8;

		info->flags &= ~FBINFO_MISC_TILEBLITTING;
		info->tileops = शून्य;

		/* in 4bpp supports 8p wide tiles only, any tiles otherwise */
		info->pixmap.blit_x = (bpp == 4) ? (1 << (8 - 1)) : (~(u32)0);
		info->pixmap.blit_y = ~(u32)0;

		offset_value = (info->var.xres_भव * bpp) / 64;
		screen_size = info->var.yres_भव * info->fix.line_length;
	पूर्ण अन्यथा अणु
		info->fix.ypanstep = 16;
		info->fix.line_length = 0;

		info->flags |= FBINFO_MISC_TILEBLITTING;
		info->tileops = &arkfb_tile_ops;

		/* supports 8x16 tiles only */
		info->pixmap.blit_x = 1 << (8 - 1);
		info->pixmap.blit_y = 1 << (16 - 1);

		offset_value = info->var.xres_भव / 16;
		screen_size = (info->var.xres_भव * info->var.yres_भव) / 64;
	पूर्ण

	info->var.xoffset = 0;
	info->var.yoffset = 0;
	info->var.activate = FB_ACTIVATE_NOW;

	/* Unlock रेजिस्टरs */
	svga_wcrt_mask(par->state.vgabase, 0x11, 0x00, 0x80);

	/* Blank screen and turn off sync */
	svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
	svga_wcrt_mask(par->state.vgabase, 0x17, 0x00, 0x80);

	/* Set शेष values */
	svga_set_शेष_gfx_regs(par->state.vgabase);
	svga_set_शेष_atc_regs(par->state.vgabase);
	svga_set_शेष_seq_regs(par->state.vgabase);
	svga_set_शेष_crt_regs(par->state.vgabase);
	svga_wcrt_multi(par->state.vgabase, ark_line_compare_regs, 0xFFFFFFFF);
	svga_wcrt_multi(par->state.vgabase, ark_start_address_regs, 0);

	/* ARK specअगरic initialization */
	svga_wseq_mask(par->state.vgabase, 0x10, 0x1F, 0x1F); /* enable linear framebuffer and full memory access */
	svga_wseq_mask(par->state.vgabase, 0x12, 0x03, 0x03); /* 4 MB linear framebuffer size */

	vga_wseq(par->state.vgabase, 0x13, info->fix.smem_start >> 16);
	vga_wseq(par->state.vgabase, 0x14, info->fix.smem_start >> 24);
	vga_wseq(par->state.vgabase, 0x15, 0);
	vga_wseq(par->state.vgabase, 0x16, 0);

	/* Set the FIFO threshold रेजिस्टर */
	/* It is fascinating way to store 5-bit value in 8-bit रेजिस्टर */
	regval = 0x10 | ((threshold & 0x0E) >> 1) | (threshold & 0x01) << 7 | (threshold & 0x10) << 1;
	vga_wseq(par->state.vgabase, 0x18, regval);

	/* Set the offset रेजिस्टर */
	fb_dbg(info, "offset register       : %d\n", offset_value);
	svga_wcrt_multi(par->state.vgabase, ark_offset_regs, offset_value);

	/* fix क्रम hi-res texपंचांगode */
	svga_wcrt_mask(par->state.vgabase, 0x40, 0x08, 0x08);

	अगर (info->var.vmode & FB_VMODE_DOUBLE)
		svga_wcrt_mask(par->state.vgabase, 0x09, 0x80, 0x80);
	अन्यथा
		svga_wcrt_mask(par->state.vgabase, 0x09, 0x00, 0x80);

	अगर (info->var.vmode & FB_VMODE_INTERLACED)
		svga_wcrt_mask(par->state.vgabase, 0x44, 0x04, 0x04);
	अन्यथा
		svga_wcrt_mask(par->state.vgabase, 0x44, 0x00, 0x04);

	hmul = 1;
	hभाग = 1;
	mode = svga_match_क्रमmat(arkfb_क्रमmats, &(info->var), &(info->fix));

	/* Set mode-specअगरic रेजिस्टर values */
	चयन (mode) अणु
	हाल 0:
		fb_dbg(info, "text mode\n");
		svga_set_texपंचांगode_vga_regs(par->state.vgabase);

		vga_wseq(par->state.vgabase, 0x11, 0x10); /* basic VGA mode */
		svga_wcrt_mask(par->state.vgabase, 0x46, 0x00, 0x04); /* 8bit pixel path */
		dac_set_mode(par->dac, DAC_PSEUDO8_8);

		अवरोध;
	हाल 1:
		fb_dbg(info, "4 bit pseudocolor\n");
		vga_wgfx(par->state.vgabase, VGA_GFX_MODE, 0x40);

		vga_wseq(par->state.vgabase, 0x11, 0x10); /* basic VGA mode */
		svga_wcrt_mask(par->state.vgabase, 0x46, 0x00, 0x04); /* 8bit pixel path */
		dac_set_mode(par->dac, DAC_PSEUDO8_8);
		अवरोध;
	हाल 2:
		fb_dbg(info, "4 bit pseudocolor, planar\n");

		vga_wseq(par->state.vgabase, 0x11, 0x10); /* basic VGA mode */
		svga_wcrt_mask(par->state.vgabase, 0x46, 0x00, 0x04); /* 8bit pixel path */
		dac_set_mode(par->dac, DAC_PSEUDO8_8);
		अवरोध;
	हाल 3:
		fb_dbg(info, "8 bit pseudocolor\n");

		vga_wseq(par->state.vgabase, 0x11, 0x16); /* 8bpp accel mode */

		अगर (info->var.pixघड़ी > 20000) अणु
			fb_dbg(info, "not using multiplex\n");
			svga_wcrt_mask(par->state.vgabase, 0x46, 0x00, 0x04); /* 8bit pixel path */
			dac_set_mode(par->dac, DAC_PSEUDO8_8);
		पूर्ण अन्यथा अणु
			fb_dbg(info, "using multiplex\n");
			svga_wcrt_mask(par->state.vgabase, 0x46, 0x04, 0x04); /* 16bit pixel path */
			dac_set_mode(par->dac, DAC_PSEUDO8_16);
			hभाग = 2;
		पूर्ण
		अवरोध;
	हाल 4:
		fb_dbg(info, "5/5/5 truecolor\n");

		vga_wseq(par->state.vgabase, 0x11, 0x1A); /* 16bpp accel mode */
		svga_wcrt_mask(par->state.vgabase, 0x46, 0x04, 0x04); /* 16bit pixel path */
		dac_set_mode(par->dac, DAC_RGB1555_16);
		अवरोध;
	हाल 5:
		fb_dbg(info, "5/6/5 truecolor\n");

		vga_wseq(par->state.vgabase, 0x11, 0x1A); /* 16bpp accel mode */
		svga_wcrt_mask(par->state.vgabase, 0x46, 0x04, 0x04); /* 16bit pixel path */
		dac_set_mode(par->dac, DAC_RGB0565_16);
		अवरोध;
	हाल 6:
		fb_dbg(info, "8/8/8 truecolor\n");

		vga_wseq(par->state.vgabase, 0x11, 0x16); /* 8bpp accel mode ??? */
		svga_wcrt_mask(par->state.vgabase, 0x46, 0x04, 0x04); /* 16bit pixel path */
		dac_set_mode(par->dac, DAC_RGB0888_16);
		hmul = 3;
		hभाग = 2;
		अवरोध;
	हाल 7:
		fb_dbg(info, "8/8/8/8 truecolor\n");

		vga_wseq(par->state.vgabase, 0x11, 0x1E); /* 32bpp accel mode */
		svga_wcrt_mask(par->state.vgabase, 0x46, 0x04, 0x04); /* 16bit pixel path */
		dac_set_mode(par->dac, DAC_RGB8888_16);
		hmul = 2;
		अवरोध;
	शेष:
		fb_err(info, "unsupported mode - bug\n");
		वापस -EINVAL;
	पूर्ण

	ark_set_pixघड़ी(info, (hभाग * info->var.pixघड़ी) / hmul);
	svga_set_timings(par->state.vgabase, &ark_timing_regs, &(info->var), hmul, hभाग,
			 (info->var.vmode & FB_VMODE_DOUBLE)     ? 2 : 1,
			 (info->var.vmode & FB_VMODE_INTERLACED) ? 2 : 1,
			  hmul, info->node);

	/* Set पूर्णांकerlaced mode start/end रेजिस्टर */
	value = info->var.xres + info->var.left_margin + info->var.right_margin + info->var.hsync_len;
	value = ((value * hmul / hभाग) / 8) - 5;
	vga_wcrt(par->state.vgabase, 0x42, (value + 1) / 2);

	स_रखो_io(info->screen_base, 0x00, screen_size);
	/* Device and screen back on */
	svga_wcrt_mask(par->state.vgabase, 0x17, 0x80, 0x80);
	svga_wseq_mask(par->state.vgabase, 0x01, 0x00, 0x20);

	वापस 0;
पूर्ण

/* Set a colour रेजिस्टर */

अटल पूर्णांक arkfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
				u_पूर्णांक transp, काष्ठा fb_info *fb)
अणु
	चयन (fb->var.bits_per_pixel) अणु
	हाल 0:
	हाल 4:
		अगर (regno >= 16)
			वापस -EINVAL;

		अगर ((fb->var.bits_per_pixel == 4) &&
		    (fb->var.nonstd == 0)) अणु
			outb(0xF0, VGA_PEL_MSK);
			outb(regno*16, VGA_PEL_IW);
		पूर्ण अन्यथा अणु
			outb(0x0F, VGA_PEL_MSK);
			outb(regno, VGA_PEL_IW);
		पूर्ण
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

		((u32*)fb->pseuकरो_palette)[regno] = ((red & 0xFF00) << 8) |
			(green & 0xFF00) | ((blue & 0xFF00) >> 8);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Set the display blanking state */

अटल पूर्णांक arkfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा arkfb_info *par = info->par;

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		fb_dbg(info, "unblank\n");
		svga_wseq_mask(par->state.vgabase, 0x01, 0x00, 0x20);
		svga_wcrt_mask(par->state.vgabase, 0x17, 0x80, 0x80);
		अवरोध;
	हाल FB_BLANK_NORMAL:
		fb_dbg(info, "blank\n");
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		svga_wcrt_mask(par->state.vgabase, 0x17, 0x80, 0x80);
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_VSYNC_SUSPEND:
		fb_dbg(info, "sync down\n");
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		svga_wcrt_mask(par->state.vgabase, 0x17, 0x00, 0x80);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


/* Pan the display */

अटल पूर्णांक arkfb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा arkfb_info *par = info->par;
	अचिन्हित पूर्णांक offset;

	/* Calculate the offset */
	अगर (info->var.bits_per_pixel == 0) अणु
		offset = (var->yoffset / 16) * (info->var.xres_भव / 2)
		       + (var->xoffset / 2);
		offset = offset >> 2;
	पूर्ण अन्यथा अणु
		offset = (var->yoffset * info->fix.line_length) +
			 (var->xoffset * info->var.bits_per_pixel / 8);
		offset = offset >> ((info->var.bits_per_pixel == 4) ? 2 : 3);
	पूर्ण

	/* Set the offset */
	svga_wcrt_multi(par->state.vgabase, ark_start_address_regs, offset);

	वापस 0;
पूर्ण


/* ------------------------------------------------------------------------- */


/* Frame buffer operations */

अटल स्थिर काष्ठा fb_ops arkfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= arkfb_खोलो,
	.fb_release	= arkfb_release,
	.fb_check_var	= arkfb_check_var,
	.fb_set_par	= arkfb_set_par,
	.fb_setcolreg	= arkfb_setcolreg,
	.fb_blank	= arkfb_blank,
	.fb_pan_display	= arkfb_pan_display,
	.fb_fillrect	= arkfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= arkfb_imageblit,
	.fb_get_caps    = svga_get_caps,
पूर्ण;


/* ------------------------------------------------------------------------- */


/* PCI probe */
अटल पूर्णांक ark_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pci_bus_region bus_reg;
	काष्ठा resource vga_res;
	काष्ठा fb_info *info;
	काष्ठा arkfb_info *par;
	पूर्णांक rc;
	u8 regval;

	/* Ignore secondary VGA device because there is no VGA arbitration */
	अगर (! svga_primary_device(dev)) अणु
		dev_info(&(dev->dev), "ignoring secondary device\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate and fill driver data काष्ठाure */
	info = framebuffer_alloc(माप(काष्ठा arkfb_info), &(dev->dev));
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	mutex_init(&par->खोलो_lock);

	info->flags = FBINFO_PARTIAL_PAN_OK | FBINFO_HWACCEL_YPAN;
	info->fbops = &arkfb_ops;

	/* Prepare PCI device */
	rc = pci_enable_device(dev);
	अगर (rc < 0) अणु
		dev_err(info->device, "cannot enable PCI device\n");
		जाओ err_enable_device;
	पूर्ण

	rc = pci_request_regions(dev, "arkfb");
	अगर (rc < 0) अणु
		dev_err(info->device, "cannot reserve framebuffer region\n");
		जाओ err_request_regions;
	पूर्ण

	par->dac = ics5342_init(ark_dac_पढ़ो_regs, ark_dac_ग_लिखो_regs, info);
	अगर (! par->dac) अणु
		rc = -ENOMEM;
		dev_err(info->device, "RAMDAC initialization failed\n");
		जाओ err_dac;
	पूर्ण

	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = pci_resource_len(dev, 0);

	/* Map physical IO memory address पूर्णांकo kernel space */
	info->screen_base = pci_iomap_wc(dev, 0, 0);
	अगर (! info->screen_base) अणु
		rc = -ENOMEM;
		dev_err(info->device, "iomap for framebuffer failed\n");
		जाओ err_iomap;
	पूर्ण

	bus_reg.start = 0;
	bus_reg.end = 64 * 1024;

	vga_res.flags = IORESOURCE_IO;

	pcibios_bus_to_resource(dev->bus, &vga_res, &bus_reg);

	par->state.vgabase = (व्योम __iomem *) (अचिन्हित दीर्घ) vga_res.start;

	/* FIXME get memsize */
	regval = vga_rseq(par->state.vgabase, 0x10);
	info->screen_size = (1 << (regval >> 6)) << 20;
	info->fix.smem_len = info->screen_size;

	म_नकल(info->fix.id, "ARK 2000PV");
	info->fix.mmio_start = 0;
	info->fix.mmio_len = 0;
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
	info->fix.ypanstep = 0;
	info->fix.accel = FB_ACCEL_NONE;
	info->pseuकरो_palette = (व्योम*) (par->pseuकरो_palette);

	/* Prepare startup mode */
	rc = fb_find_mode(&(info->var), info, mode_option, शून्य, 0, शून्य, 8);
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
	par->wc_cookie = arch_phys_wc_add(info->fix.smem_start,
					  info->fix.smem_len);
	वापस 0;

	/* Error handling */
err_reg_fb:
	fb_dealloc_cmap(&info->cmap);
err_alloc_cmap:
err_find_mode:
	pci_iounmap(dev, info->screen_base);
err_iomap:
	dac_release(par->dac);
err_dac:
	pci_release_regions(dev);
err_request_regions:
/*	pci_disable_device(dev); */
err_enable_device:
	framebuffer_release(info);
	वापस rc;
पूर्ण

/* PCI हटाओ */

अटल व्योम ark_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);

	अगर (info) अणु
		काष्ठा arkfb_info *par = info->par;
		arch_phys_wc_del(par->wc_cookie);
		dac_release(par->dac);
		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);

		pci_iounmap(dev, info->screen_base);
		pci_release_regions(dev);
/*		pci_disable_device(dev); */

		framebuffer_release(info);
	पूर्ण
पूर्ण


/* PCI suspend */

अटल पूर्णांक __maybe_unused ark_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा arkfb_info *par = info->par;

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

अटल पूर्णांक __maybe_unused ark_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा arkfb_info *par = info->par;

	dev_info(info->device, "resume\n");

	console_lock();
	mutex_lock(&(par->खोलो_lock));

	अगर (par->ref_count == 0)
		जाओ fail;

	arkfb_set_par(info);
	fb_set_suspend(info, 0);

fail:
	mutex_unlock(&(par->खोलो_lock));
	console_unlock();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ark_pci_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ark_pci_suspend,
	.resume		= ark_pci_resume,
	.मुक्तze		= शून्य,
	.thaw		= ark_pci_resume,
	.घातeroff	= ark_pci_suspend,
	.restore	= ark_pci_resume,
#पूर्ण_अगर
पूर्ण;

/* List of boards that we are trying to support */

अटल स्थिर काष्ठा pci_device_id ark_devices[] = अणु
	अणुPCI_DEVICE(0xEDD8, 0xA099)पूर्ण,
	अणु0, 0, 0, 0, 0, 0, 0पूर्ण
पूर्ण;


MODULE_DEVICE_TABLE(pci, ark_devices);

अटल काष्ठा pci_driver arkfb_pci_driver = अणु
	.name		= "arkfb",
	.id_table	= ark_devices,
	.probe		= ark_pci_probe,
	.हटाओ		= ark_pci_हटाओ,
	.driver.pm	= &ark_pci_pm_ops,
पूर्ण;

/* Cleanup */

अटल व्योम __निकास arkfb_cleanup(व्योम)
अणु
	pr_debug("arkfb: cleaning up\n");
	pci_unरेजिस्टर_driver(&arkfb_pci_driver);
पूर्ण

/* Driver Initialisation */

अटल पूर्णांक __init arkfb_init(व्योम)
अणु

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("arkfb", &option))
		वापस -ENODEV;

	अगर (option && *option)
		mode_option = option;
#पूर्ण_अगर

	pr_debug("arkfb: initializing\n");
	वापस pci_रेजिस्टर_driver(&arkfb_pci_driver);
पूर्ण

module_init(arkfb_init);
module_निकास(arkfb_cleanup);
