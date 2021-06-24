<शैली गुरु>
/*
 * linux/drivers/video/s3fb.c -- Frame buffer device driver क्रम S3 Trio/Virge
 *
 * Copyright (c) 2006-2007 Ondrej Zajicek <santiago@crमुक्तnet.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Code is based on David Boucher's viafb (http://davesकरोमुख्य.org.uk/viafb/)
 * which is based on the code of neofb.
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

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

काष्ठा s3fb_info अणु
	पूर्णांक chip, rev, mclk_freq;
	पूर्णांक wc_cookie;
	काष्ठा vgastate state;
	काष्ठा mutex खोलो_lock;
	अचिन्हित पूर्णांक ref_count;
	u32 pseuकरो_palette[16];
#अगर_घोषित CONFIG_FB_S3_DDC
	u8 __iomem *mmio;
	bool ddc_रेजिस्टरed;
	काष्ठा i2c_adapter ddc_adapter;
	काष्ठा i2c_algo_bit_data ddc_algo;
#पूर्ण_अगर
पूर्ण;


/* ------------------------------------------------------------------------- */

अटल स्थिर काष्ठा svga_fb_क्रमmat s3fb_क्रमmats[] = अणु
	अणु 0,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण,  अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_TEXT, FB_AUX_TEXT_SVGA_STEP4,	FB_VISUAL_PSEUDOCOLOR, 8, 16पूर्ण,
	अणु 4,  अणु0, 4, 0पूर्ण,  अणु0, 4, 0पूर्ण,  अणु0, 4, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_PSEUDOCOLOR, 8, 16पूर्ण,
	अणु 4,  अणु0, 4, 0पूर्ण,  अणु0, 4, 0पूर्ण,  अणु0, 4, 0पूर्ण, अणु0, 0, 0पूर्ण, 1,
		FB_TYPE_INTERLEAVED_PLANES, 1,		FB_VISUAL_PSEUDOCOLOR, 8, 16पूर्ण,
	अणु 8,  अणु0, 8, 0पूर्ण,  अणु0, 8, 0पूर्ण,  अणु0, 8, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_PSEUDOCOLOR, 4, 8पूर्ण,
	अणु16,  अणु10, 5, 0पूर्ण, अणु5, 5, 0पूर्ण,  अणु0, 5, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 2, 4पूर्ण,
	अणु16,  अणु11, 5, 0पूर्ण, अणु5, 6, 0पूर्ण,  अणु0, 5, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 2, 4पूर्ण,
	अणु24,  अणु16, 8, 0पूर्ण, अणु8, 8, 0पूर्ण,  अणु0, 8, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 1, 2पूर्ण,
	अणु32,  अणु16, 8, 0पूर्ण, अणु8, 8, 0पूर्ण,  अणु0, 8, 0पूर्ण, अणु0, 0, 0पूर्ण, 0,
		FB_TYPE_PACKED_PIXELS, 0,		FB_VISUAL_TRUECOLOR, 1, 2पूर्ण,
	SVGA_FORMAT_END
पूर्ण;


अटल स्थिर काष्ठा svga_pll s3_pll = अणु3, 129, 3, 33, 0, 3,
	35000, 240000, 14318पूर्ण;
अटल स्थिर काष्ठा svga_pll s3_trio3d_pll = अणु3, 129, 3, 31, 0, 4,
	230000, 460000, 14318पूर्ण;

अटल स्थिर पूर्णांक s3_memsizes[] = अणु4096, 0, 3072, 8192, 2048, 6144, 1024, 512पूर्ण;

अटल स्थिर अक्षर * स्थिर s3_names[] = अणु"S3 Unknown", "S3 Trio32", "S3 Trio64", "S3 Trio64V+",
			"S3 Trio64UV+", "S3 Trio64V2/DX", "S3 Trio64V2/GX",
			"S3 Plato/PX", "S3 Aurora64V+", "S3 Virge",
			"S3 Virge/VX", "S3 Virge/DX", "S3 Virge/GX",
			"S3 Virge/GX2", "S3 Virge/GX2+", "",
			"S3 Trio3D/1X", "S3 Trio3D/2X", "S3 Trio3D/2X",
			"S3 Trio3D", "S3 Virge/MX"पूर्ण;

#घोषणा CHIP_UNKNOWN		0x00
#घोषणा CHIP_732_TRIO32		0x01
#घोषणा CHIP_764_TRIO64		0x02
#घोषणा CHIP_765_TRIO64VP	0x03
#घोषणा CHIP_767_TRIO64UVP	0x04
#घोषणा CHIP_775_TRIO64V2_DX	0x05
#घोषणा CHIP_785_TRIO64V2_GX	0x06
#घोषणा CHIP_551_PLATO_PX	0x07
#घोषणा CHIP_M65_AURORA64VP	0x08
#घोषणा CHIP_325_VIRGE		0x09
#घोषणा CHIP_988_VIRGE_VX	0x0A
#घोषणा CHIP_375_VIRGE_DX	0x0B
#घोषणा CHIP_385_VIRGE_GX	0x0C
#घोषणा CHIP_357_VIRGE_GX2	0x0D
#घोषणा CHIP_359_VIRGE_GX2P	0x0E
#घोषणा CHIP_360_TRIO3D_1X	0x10
#घोषणा CHIP_362_TRIO3D_2X	0x11
#घोषणा CHIP_368_TRIO3D_2X	0x12
#घोषणा CHIP_365_TRIO3D		0x13
#घोषणा CHIP_260_VIRGE_MX	0x14

#घोषणा CHIP_XXX_TRIO		0x80
#घोषणा CHIP_XXX_TRIO64V2_DXGX	0x81
#घोषणा CHIP_XXX_VIRGE_DXGX	0x82
#घोषणा CHIP_36X_TRIO3D_1X_2X	0x83

#घोषणा CHIP_UNDECIDED_FLAG	0x80
#घोषणा CHIP_MASK		0xFF

#घोषणा MMIO_OFFSET		0x1000000
#घोषणा MMIO_SIZE		0x10000

/* CRT timing रेजिस्टर sets */

अटल स्थिर काष्ठा vga_regset s3_h_total_regs[]        = अणुअणु0x00, 0, 7पूर्ण, अणु0x5D, 0, 0पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_h_display_regs[]      = अणुअणु0x01, 0, 7पूर्ण, अणु0x5D, 1, 1पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_h_blank_start_regs[]  = अणुअणु0x02, 0, 7पूर्ण, अणु0x5D, 2, 2पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_h_blank_end_regs[]    = अणुअणु0x03, 0, 4पूर्ण, अणु0x05, 7, 7पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_h_sync_start_regs[]   = अणुअणु0x04, 0, 7पूर्ण, अणु0x5D, 4, 4पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_h_sync_end_regs[]     = अणुअणु0x05, 0, 4पूर्ण, VGA_REGSET_ENDपूर्ण;

अटल स्थिर काष्ठा vga_regset s3_v_total_regs[]        = अणुअणु0x06, 0, 7पूर्ण, अणु0x07, 0, 0पूर्ण, अणु0x07, 5, 5पूर्ण, अणु0x5E, 0, 0पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_v_display_regs[]      = अणुअणु0x12, 0, 7पूर्ण, अणु0x07, 1, 1पूर्ण, अणु0x07, 6, 6पूर्ण, अणु0x5E, 1, 1पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_v_blank_start_regs[]  = अणुअणु0x15, 0, 7पूर्ण, अणु0x07, 3, 3पूर्ण, अणु0x09, 5, 5पूर्ण, अणु0x5E, 2, 2पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_v_blank_end_regs[]    = अणुअणु0x16, 0, 7पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_v_sync_start_regs[]   = अणुअणु0x10, 0, 7पूर्ण, अणु0x07, 2, 2पूर्ण, अणु0x07, 7, 7पूर्ण, अणु0x5E, 4, 4पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_v_sync_end_regs[]     = अणुअणु0x11, 0, 3पूर्ण, VGA_REGSET_ENDपूर्ण;

अटल स्थिर काष्ठा vga_regset s3_line_compare_regs[]   = अणुअणु0x18, 0, 7पूर्ण, अणु0x07, 4, 4पूर्ण, अणु0x09, 6, 6पूर्ण, अणु0x5E, 6, 6पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_start_address_regs[]  = अणुअणु0x0d, 0, 7पूर्ण, अणु0x0c, 0, 7पूर्ण, अणु0x69, 0, 4पूर्ण, VGA_REGSET_ENDपूर्ण;
अटल स्थिर काष्ठा vga_regset s3_offset_regs[]         = अणुअणु0x13, 0, 7पूर्ण, अणु0x51, 4, 5पूर्ण, VGA_REGSET_ENDपूर्ण; /* set 0x43 bit 2 to 0 */

अटल स्थिर काष्ठा vga_regset s3_dtpc_regs[]		= अणुअणु0x3B, 0, 7पूर्ण, अणु0x5D, 6, 6पूर्ण, VGA_REGSET_ENDपूर्ण;

अटल स्थिर काष्ठा svga_timing_regs s3_timing_regs     = अणु
	s3_h_total_regs, s3_h_display_regs, s3_h_blank_start_regs,
	s3_h_blank_end_regs, s3_h_sync_start_regs, s3_h_sync_end_regs,
	s3_v_total_regs, s3_v_display_regs, s3_v_blank_start_regs,
	s3_v_blank_end_regs, s3_v_sync_start_regs, s3_v_sync_end_regs,
पूर्ण;


/* ------------------------------------------------------------------------- */

/* Module parameters */


अटल अक्षर *mode_option;
अटल पूर्णांक mtrr = 1;
अटल पूर्णांक fasttext = 1;


MODULE_AUTHOR("(c) 2006-2007 Ondrej Zajicek <santiago@crfreenet.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("fbdev driver for S3 Trio/Virge");

module_param(mode_option, अक्षरp, 0444);
MODULE_PARM_DESC(mode_option, "Default video mode ('640x480-8@60', etc)");
module_param_named(mode, mode_option, अक्षरp, 0444);
MODULE_PARM_DESC(mode, "Default video mode ('640x480-8@60', etc) (deprecated)");
module_param(mtrr, पूर्णांक, 0444);
MODULE_PARM_DESC(mtrr, "Enable write-combining with MTRR (1=enable, 0=disable, default=1)");

module_param(fasttext, पूर्णांक, 0644);
MODULE_PARM_DESC(fasttext, "Enable S3 fast text mode (1=enable, 0=disable, default=1)");


/* ------------------------------------------------------------------------- */

#अगर_घोषित CONFIG_FB_S3_DDC

#घोषणा DDC_REG		0xaa		/* Trio 3D/1X/2X */
#घोषणा DDC_MMIO_REG	0xff20		/* all other chips */
#घोषणा DDC_SCL_OUT	(1 << 0)
#घोषणा DDC_SDA_OUT	(1 << 1)
#घोषणा DDC_SCL_IN	(1 << 2)
#घोषणा DDC_SDA_IN	(1 << 3)
#घोषणा DDC_DRIVE_EN	(1 << 4)

अटल bool s3fb_ddc_needs_mmio(पूर्णांक chip)
अणु
	वापस !(chip == CHIP_360_TRIO3D_1X  ||
		 chip == CHIP_362_TRIO3D_2X  ||
		 chip == CHIP_368_TRIO3D_2X);
पूर्ण

अटल u8 s3fb_ddc_पढ़ो(काष्ठा s3fb_info *par)
अणु
	अगर (s3fb_ddc_needs_mmio(par->chip))
		वापस पढ़ोb(par->mmio + DDC_MMIO_REG);
	अन्यथा
		वापस vga_rcrt(par->state.vgabase, DDC_REG);
पूर्ण

अटल व्योम s3fb_ddc_ग_लिखो(काष्ठा s3fb_info *par, u8 val)
अणु
	अगर (s3fb_ddc_needs_mmio(par->chip))
		ग_लिखोb(val, par->mmio + DDC_MMIO_REG);
	अन्यथा
		vga_wcrt(par->state.vgabase, DDC_REG, val);
पूर्ण

अटल व्योम s3fb_ddc_setscl(व्योम *data, पूर्णांक val)
अणु
	काष्ठा s3fb_info *par = data;
	अचिन्हित अक्षर reg;

	reg = s3fb_ddc_पढ़ो(par) | DDC_DRIVE_EN;
	अगर (val)
		reg |= DDC_SCL_OUT;
	अन्यथा
		reg &= ~DDC_SCL_OUT;
	s3fb_ddc_ग_लिखो(par, reg);
पूर्ण

अटल व्योम s3fb_ddc_setsda(व्योम *data, पूर्णांक val)
अणु
	काष्ठा s3fb_info *par = data;
	अचिन्हित अक्षर reg;

	reg = s3fb_ddc_पढ़ो(par) | DDC_DRIVE_EN;
	अगर (val)
		reg |= DDC_SDA_OUT;
	अन्यथा
		reg &= ~DDC_SDA_OUT;
	s3fb_ddc_ग_लिखो(par, reg);
पूर्ण

अटल पूर्णांक s3fb_ddc_माला_लोcl(व्योम *data)
अणु
	काष्ठा s3fb_info *par = data;

	वापस !!(s3fb_ddc_पढ़ो(par) & DDC_SCL_IN);
पूर्ण

अटल पूर्णांक s3fb_ddc_माला_लोda(व्योम *data)
अणु
	काष्ठा s3fb_info *par = data;

	वापस !!(s3fb_ddc_पढ़ो(par) & DDC_SDA_IN);
पूर्ण

अटल पूर्णांक s3fb_setup_ddc_bus(काष्ठा fb_info *info)
अणु
	काष्ठा s3fb_info *par = info->par;

	strlcpy(par->ddc_adapter.name, info->fix.id,
		माप(par->ddc_adapter.name));
	par->ddc_adapter.owner		= THIS_MODULE;
	par->ddc_adapter.class		= I2C_CLASS_DDC;
	par->ddc_adapter.algo_data	= &par->ddc_algo;
	par->ddc_adapter.dev.parent	= info->device;
	par->ddc_algo.setsda		= s3fb_ddc_setsda;
	par->ddc_algo.setscl		= s3fb_ddc_setscl;
	par->ddc_algo.माला_लोda		= s3fb_ddc_माला_लोda;
	par->ddc_algo.माला_लोcl		= s3fb_ddc_माला_लोcl;
	par->ddc_algo.udelay		= 10;
	par->ddc_algo.समयout		= 20;
	par->ddc_algo.data		= par;

	i2c_set_adapdata(&par->ddc_adapter, par);

	/*
	 * some Virge cards have बाह्यal MUX to चयन chip I2C bus between
	 * DDC and extension pins - चयन it करो DDC
	 */
/*	vga_wseq(par->state.vgabase, 0x08, 0x06); - not needed, alपढ़ोy unlocked */
	अगर (par->chip == CHIP_357_VIRGE_GX2 ||
	    par->chip == CHIP_359_VIRGE_GX2P ||
	    par->chip == CHIP_260_VIRGE_MX)
		svga_wseq_mask(par->state.vgabase, 0x0d, 0x01, 0x03);
	अन्यथा
		svga_wseq_mask(par->state.vgabase, 0x0d, 0x00, 0x03);
	/* some Virge need this or the DDC is ignored */
	svga_wcrt_mask(par->state.vgabase, 0x5c, 0x03, 0x03);

	वापस i2c_bit_add_bus(&par->ddc_adapter);
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_S3_DDC */


/* ------------------------------------------------------------------------- */

/* Set font in S3 fast text mode */

अटल व्योम s3fb_settile_fast(काष्ठा fb_info *info, काष्ठा fb_tilemap *map)
अणु
	स्थिर u8 *font = map->data;
	u8 __iomem *fb = (u8 __iomem *) info->screen_base;
	पूर्णांक i, c;

	अगर ((map->width != 8) || (map->height != 16) ||
	    (map->depth != 1) || (map->length != 256)) अणु
		fb_err(info, "unsupported font parameters: width %d, height %d, depth %d, length %d\n",
		       map->width, map->height, map->depth, map->length);
		वापस;
	पूर्ण

	fb += 2;
	क्रम (i = 0; i < map->height; i++) अणु
		क्रम (c = 0; c < map->length; c++) अणु
			fb_ग_लिखोb(font[c * map->height + i], fb + c * 4);
		पूर्ण
		fb += 1024;
	पूर्ण
पूर्ण

अटल व्योम s3fb_tilecursor(काष्ठा fb_info *info, काष्ठा fb_tilecursor *cursor)
अणु
	काष्ठा s3fb_info *par = info->par;

	svga_tilecursor(par->state.vgabase, info, cursor);
पूर्ण

अटल काष्ठा fb_tile_ops s3fb_tile_ops = अणु
	.fb_settile	= svga_settile,
	.fb_tilecopy	= svga_tilecopy,
	.fb_tilefill    = svga_tilefill,
	.fb_tileblit    = svga_tileblit,
	.fb_tilecursor  = s3fb_tilecursor,
	.fb_get_tilemax = svga_get_tilemax,
पूर्ण;

अटल काष्ठा fb_tile_ops s3fb_fast_tile_ops = अणु
	.fb_settile	= s3fb_settile_fast,
	.fb_tilecopy	= svga_tilecopy,
	.fb_tilefill    = svga_tilefill,
	.fb_tileblit    = svga_tileblit,
	.fb_tilecursor  = s3fb_tilecursor,
	.fb_get_tilemax = svga_get_tilemax,
पूर्ण;


/* ------------------------------------------------------------------------- */

/* image data is MSB-first, fb काष्ठाure is MSB-first too */
अटल अंतरभूत u32 expand_color(u32 c)
अणु
	वापस ((c & 1) | ((c & 2) << 7) | ((c & 4) << 14) | ((c & 8) << 21)) * 0xFF;
पूर्ण

/* s3fb_iplan_imageblit silently assumes that almost everything is 8-pixel aligned */
अटल व्योम s3fb_iplan_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
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

/* s3fb_iplan_fillrect silently assumes that almost everything is 8-pixel aligned */
अटल व्योम s3fb_iplan_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
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

/* s3fb_cfb4_imageblit silently assumes that almost everything is 8-pixel aligned */
अटल व्योम s3fb_cfb4_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
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

अटल व्योम s3fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	अगर ((info->var.bits_per_pixel == 4) && (image->depth == 1)
	    && ((image->width % 8) == 0) && ((image->dx % 8) == 0)) अणु
		अगर (info->fix.type == FB_TYPE_INTERLEAVED_PLANES)
			s3fb_iplan_imageblit(info, image);
		अन्यथा
			s3fb_cfb4_imageblit(info, image);
	पूर्ण अन्यथा
		cfb_imageblit(info, image);
पूर्ण

अटल व्योम s3fb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	अगर ((info->var.bits_per_pixel == 4)
	    && ((rect->width % 8) == 0) && ((rect->dx % 8) == 0)
	    && (info->fix.type == FB_TYPE_INTERLEAVED_PLANES))
		s3fb_iplan_fillrect(info, rect);
	 अन्यथा
		cfb_fillrect(info, rect);
पूर्ण



/* ------------------------------------------------------------------------- */


अटल व्योम s3_set_pixघड़ी(काष्ठा fb_info *info, u32 pixघड़ी)
अणु
	काष्ठा s3fb_info *par = info->par;
	u16 m, n, r;
	u8 regval;
	पूर्णांक rv;

	rv = svga_compute_pll((par->chip == CHIP_365_TRIO3D) ? &s3_trio3d_pll : &s3_pll,
			      1000000000 / pixघड़ी, &m, &n, &r, info->node);
	अगर (rv < 0) अणु
		fb_err(info, "cannot set requested pixclock, keeping old value\n");
		वापस;
	पूर्ण

	/* Set VGA misc रेजिस्टर  */
	regval = vga_r(par->state.vgabase, VGA_MIS_R);
	vga_w(par->state.vgabase, VGA_MIS_W, regval | VGA_MIS_ENB_PLL_LOAD);

	/* Set S3 घड़ी रेजिस्टरs */
	अगर (par->chip == CHIP_357_VIRGE_GX2 ||
	    par->chip == CHIP_359_VIRGE_GX2P ||
	    par->chip == CHIP_360_TRIO3D_1X ||
	    par->chip == CHIP_362_TRIO3D_2X ||
	    par->chip == CHIP_368_TRIO3D_2X ||
	    par->chip == CHIP_260_VIRGE_MX) अणु
		vga_wseq(par->state.vgabase, 0x12, (n - 2) | ((r & 3) << 6));	/* n and two bits of r */
		vga_wseq(par->state.vgabase, 0x29, r >> 2); /* reमुख्यing highest bit of r */
	पूर्ण अन्यथा
		vga_wseq(par->state.vgabase, 0x12, (n - 2) | (r << 5));
	vga_wseq(par->state.vgabase, 0x13, m - 2);

	udelay(1000);

	/* Activate घड़ी - ग_लिखो 0, 1, 0 to seq/15 bit 5 */
	regval = vga_rseq (par->state.vgabase, 0x15); /* | 0x80; */
	vga_wseq(par->state.vgabase, 0x15, regval & ~(1<<5));
	vga_wseq(par->state.vgabase, 0x15, regval |  (1<<5));
	vga_wseq(par->state.vgabase, 0x15, regval & ~(1<<5));
पूर्ण


/* Open framebuffer */

अटल पूर्णांक s3fb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा s3fb_info *par = info->par;

	mutex_lock(&(par->खोलो_lock));
	अगर (par->ref_count == 0) अणु
		व्योम __iomem *vgabase = par->state.vgabase;

		स_रखो(&(par->state), 0, माप(काष्ठा vgastate));
		par->state.vgabase = vgabase;
		par->state.flags = VGA_SAVE_MODE | VGA_SAVE_FONTS | VGA_SAVE_CMAP;
		par->state.num_crtc = 0x70;
		par->state.num_seq = 0x20;
		save_vga(&(par->state));
	पूर्ण

	par->ref_count++;
	mutex_unlock(&(par->खोलो_lock));

	वापस 0;
पूर्ण

/* Close framebuffer */

अटल पूर्णांक s3fb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा s3fb_info *par = info->par;

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

/* Validate passed in var */

अटल पूर्णांक s3fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा s3fb_info *par = info->par;
	पूर्णांक rv, mem, step;
	u16 m, n, r;

	/* Find appropriate क्रमmat */
	rv = svga_match_क्रमmat (s3fb_क्रमmats, var, शून्य);

	/* 32bpp mode is not supported on VIRGE VX,
	   24bpp is not supported on others */
	अगर ((par->chip == CHIP_988_VIRGE_VX) ? (rv == 7) : (rv == 6))
		rv = -EINVAL;

	अगर (rv < 0) अणु
		fb_err(info, "unsupported mode requested\n");
		वापस rv;
	पूर्ण

	/* Do not allow to have real resoulution larger than भव */
	अगर (var->xres > var->xres_भव)
		var->xres_भव = var->xres;

	अगर (var->yres > var->yres_भव)
		var->yres_भव = var->yres;

	/* Round up xres_भव to have proper alignment of lines */
	step = s3fb_क्रमmats[rv].xresstep - 1;
	var->xres_भव = (var->xres_भव+step) & ~step;

	/* Check whether have enough memory */
	mem = ((var->bits_per_pixel * var->xres_भव) >> 3) * var->yres_भव;
	अगर (mem > info->screen_size) अणु
		fb_err(info, "not enough framebuffer memory (%d kB requested , %u kB available)\n",
		       mem >> 10, (अचिन्हित पूर्णांक) (info->screen_size >> 10));
		वापस -EINVAL;
	पूर्ण

	rv = svga_check_timings (&s3_timing_regs, var, info->node);
	अगर (rv < 0) अणु
		fb_err(info, "invalid timings requested\n");
		वापस rv;
	पूर्ण

	rv = svga_compute_pll(&s3_pll, PICOS2KHZ(var->pixघड़ी), &m, &n, &r,
				info->node);
	अगर (rv < 0) अणु
		fb_err(info, "invalid pixclock value requested\n");
		वापस rv;
	पूर्ण

	वापस 0;
पूर्ण

/* Set video mode from par */

अटल पूर्णांक s3fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा s3fb_info *par = info->par;
	u32 value, mode, hmul, offset_value, screen_size, multiplex, dbytes;
	u32 bpp = info->var.bits_per_pixel;
	u32 htotal, hsstart;

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
		info->tileops = fasttext ? &s3fb_fast_tile_ops : &s3fb_tile_ops;

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
	vga_wcrt(par->state.vgabase, 0x38, 0x48);
	vga_wcrt(par->state.vgabase, 0x39, 0xA5);
	vga_wseq(par->state.vgabase, 0x08, 0x06);
	svga_wcrt_mask(par->state.vgabase, 0x11, 0x00, 0x80);

	/* Blank screen and turn off sync */
	svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
	svga_wcrt_mask(par->state.vgabase, 0x17, 0x00, 0x80);

	/* Set शेष values */
	svga_set_शेष_gfx_regs(par->state.vgabase);
	svga_set_शेष_atc_regs(par->state.vgabase);
	svga_set_शेष_seq_regs(par->state.vgabase);
	svga_set_शेष_crt_regs(par->state.vgabase);
	svga_wcrt_multi(par->state.vgabase, s3_line_compare_regs, 0xFFFFFFFF);
	svga_wcrt_multi(par->state.vgabase, s3_start_address_regs, 0);

	/* S3 specअगरic initialization */
	svga_wcrt_mask(par->state.vgabase, 0x58, 0x10, 0x10); /* enable linear framebuffer */
	svga_wcrt_mask(par->state.vgabase, 0x31, 0x08, 0x08); /* enable sequencer access to framebuffer above 256 kB */

/*	svga_wcrt_mask(par->state.vgabase, 0x33, 0x08, 0x08); */ /* DDR ?	*/
/*	svga_wcrt_mask(par->state.vgabase, 0x43, 0x01, 0x01); */ /* DDR ?	*/
	svga_wcrt_mask(par->state.vgabase, 0x33, 0x00, 0x08); /* no DDR ?	*/
	svga_wcrt_mask(par->state.vgabase, 0x43, 0x00, 0x01); /* no DDR ?	*/

	svga_wcrt_mask(par->state.vgabase, 0x5D, 0x00, 0x28); /* Clear strange HSlen bits */

/*	svga_wcrt_mask(par->state.vgabase, 0x58, 0x03, 0x03); */

/*	svga_wcrt_mask(par->state.vgabase, 0x53, 0x12, 0x13); */ /* enable MMIO */
/*	svga_wcrt_mask(par->state.vgabase, 0x40, 0x08, 0x08); */ /* enable ग_लिखो buffer */


	/* Set the offset रेजिस्टर */
	fb_dbg(info, "offset register       : %d\n", offset_value);
	svga_wcrt_multi(par->state.vgabase, s3_offset_regs, offset_value);

	अगर (par->chip != CHIP_357_VIRGE_GX2 &&
	    par->chip != CHIP_359_VIRGE_GX2P &&
	    par->chip != CHIP_360_TRIO3D_1X &&
	    par->chip != CHIP_362_TRIO3D_2X &&
	    par->chip != CHIP_368_TRIO3D_2X &&
	    par->chip != CHIP_260_VIRGE_MX) अणु
		vga_wcrt(par->state.vgabase, 0x54, 0x18); /* M parameter */
		vga_wcrt(par->state.vgabase, 0x60, 0xff); /* N parameter */
		vga_wcrt(par->state.vgabase, 0x61, 0xff); /* L parameter */
		vga_wcrt(par->state.vgabase, 0x62, 0xff); /* L parameter */
	पूर्ण

	vga_wcrt(par->state.vgabase, 0x3A, 0x35);
	svga_wattr(par->state.vgabase, 0x33, 0x00);

	अगर (info->var.vmode & FB_VMODE_DOUBLE)
		svga_wcrt_mask(par->state.vgabase, 0x09, 0x80, 0x80);
	अन्यथा
		svga_wcrt_mask(par->state.vgabase, 0x09, 0x00, 0x80);

	अगर (info->var.vmode & FB_VMODE_INTERLACED)
		svga_wcrt_mask(par->state.vgabase, 0x42, 0x20, 0x20);
	अन्यथा
		svga_wcrt_mask(par->state.vgabase, 0x42, 0x00, 0x20);

	/* Disable hardware graphics cursor */
	svga_wcrt_mask(par->state.vgabase, 0x45, 0x00, 0x01);
	/* Disable Streams engine */
	svga_wcrt_mask(par->state.vgabase, 0x67, 0x00, 0x0C);

	mode = svga_match_क्रमmat(s3fb_क्रमmats, &(info->var), &(info->fix));

	/* S3 virge DX hack */
	अगर (par->chip == CHIP_375_VIRGE_DX) अणु
		vga_wcrt(par->state.vgabase, 0x86, 0x80);
		vga_wcrt(par->state.vgabase, 0x90, 0x00);
	पूर्ण

	/* S3 virge VX hack */
	अगर (par->chip == CHIP_988_VIRGE_VX) अणु
		vga_wcrt(par->state.vgabase, 0x50, 0x00);
		vga_wcrt(par->state.vgabase, 0x67, 0x50);
		msleep(10); /* screen reमुख्यs blank someबार without this */
		vga_wcrt(par->state.vgabase, 0x63, (mode <= 2) ? 0x90 : 0x09);
		vga_wcrt(par->state.vgabase, 0x66, 0x90);
	पूर्ण

	अगर (par->chip == CHIP_357_VIRGE_GX2 ||
	    par->chip == CHIP_359_VIRGE_GX2P ||
	    par->chip == CHIP_360_TRIO3D_1X ||
	    par->chip == CHIP_362_TRIO3D_2X ||
	    par->chip == CHIP_368_TRIO3D_2X ||
	    par->chip == CHIP_365_TRIO3D    ||
	    par->chip == CHIP_375_VIRGE_DX  ||
	    par->chip == CHIP_385_VIRGE_GX  ||
	    par->chip == CHIP_260_VIRGE_MX) अणु
		dbytes = info->var.xres * ((bpp+7)/8);
		vga_wcrt(par->state.vgabase, 0x91, (dbytes + 7) / 8);
		vga_wcrt(par->state.vgabase, 0x90, (((dbytes + 7) / 8) >> 8) | 0x80);

		vga_wcrt(par->state.vgabase, 0x66, 0x81);
	पूर्ण

	अगर (par->chip == CHIP_357_VIRGE_GX2  ||
	    par->chip == CHIP_359_VIRGE_GX2P ||
	    par->chip == CHIP_360_TRIO3D_1X ||
	    par->chip == CHIP_362_TRIO3D_2X ||
	    par->chip == CHIP_368_TRIO3D_2X ||
	    par->chip == CHIP_260_VIRGE_MX)
		vga_wcrt(par->state.vgabase, 0x34, 0x00);
	अन्यथा	/* enable Data Transfer Position Control (DTPC) */
		vga_wcrt(par->state.vgabase, 0x34, 0x10);

	svga_wcrt_mask(par->state.vgabase, 0x31, 0x00, 0x40);
	multiplex = 0;
	hmul = 1;

	/* Set mode-specअगरic रेजिस्टर values */
	चयन (mode) अणु
	हाल 0:
		fb_dbg(info, "text mode\n");
		svga_set_texपंचांगode_vga_regs(par->state.vgabase);

		/* Set additional रेजिस्टरs like in 8-bit mode */
		svga_wcrt_mask(par->state.vgabase, 0x50, 0x00, 0x30);
		svga_wcrt_mask(par->state.vgabase, 0x67, 0x00, 0xF0);

		/* Disable enhanced mode */
		svga_wcrt_mask(par->state.vgabase, 0x3A, 0x00, 0x30);

		अगर (fasttext) अणु
			fb_dbg(info, "high speed text mode set\n");
			svga_wcrt_mask(par->state.vgabase, 0x31, 0x40, 0x40);
		पूर्ण
		अवरोध;
	हाल 1:
		fb_dbg(info, "4 bit pseudocolor\n");
		vga_wgfx(par->state.vgabase, VGA_GFX_MODE, 0x40);

		/* Set additional रेजिस्टरs like in 8-bit mode */
		svga_wcrt_mask(par->state.vgabase, 0x50, 0x00, 0x30);
		svga_wcrt_mask(par->state.vgabase, 0x67, 0x00, 0xF0);

		/* disable enhanced mode */
		svga_wcrt_mask(par->state.vgabase, 0x3A, 0x00, 0x30);
		अवरोध;
	हाल 2:
		fb_dbg(info, "4 bit pseudocolor, planar\n");

		/* Set additional रेजिस्टरs like in 8-bit mode */
		svga_wcrt_mask(par->state.vgabase, 0x50, 0x00, 0x30);
		svga_wcrt_mask(par->state.vgabase, 0x67, 0x00, 0xF0);

		/* disable enhanced mode */
		svga_wcrt_mask(par->state.vgabase, 0x3A, 0x00, 0x30);
		अवरोध;
	हाल 3:
		fb_dbg(info, "8 bit pseudocolor\n");
		svga_wcrt_mask(par->state.vgabase, 0x50, 0x00, 0x30);
		अगर (info->var.pixघड़ी > 20000 ||
		    par->chip == CHIP_357_VIRGE_GX2 ||
		    par->chip == CHIP_359_VIRGE_GX2P ||
		    par->chip == CHIP_360_TRIO3D_1X ||
		    par->chip == CHIP_362_TRIO3D_2X ||
		    par->chip == CHIP_368_TRIO3D_2X ||
		    par->chip == CHIP_260_VIRGE_MX)
			svga_wcrt_mask(par->state.vgabase, 0x67, 0x00, 0xF0);
		अन्यथा अणु
			svga_wcrt_mask(par->state.vgabase, 0x67, 0x10, 0xF0);
			multiplex = 1;
		पूर्ण
		अवरोध;
	हाल 4:
		fb_dbg(info, "5/5/5 truecolor\n");
		अगर (par->chip == CHIP_988_VIRGE_VX) अणु
			अगर (info->var.pixघड़ी > 20000)
				svga_wcrt_mask(par->state.vgabase, 0x67, 0x20, 0xF0);
			अन्यथा
				svga_wcrt_mask(par->state.vgabase, 0x67, 0x30, 0xF0);
		पूर्ण अन्यथा अगर (par->chip == CHIP_365_TRIO3D) अणु
			svga_wcrt_mask(par->state.vgabase, 0x50, 0x10, 0x30);
			अगर (info->var.pixघड़ी > 8695) अणु
				svga_wcrt_mask(par->state.vgabase, 0x67, 0x30, 0xF0);
				hmul = 2;
			पूर्ण अन्यथा अणु
				svga_wcrt_mask(par->state.vgabase, 0x67, 0x20, 0xF0);
				multiplex = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			svga_wcrt_mask(par->state.vgabase, 0x50, 0x10, 0x30);
			svga_wcrt_mask(par->state.vgabase, 0x67, 0x30, 0xF0);
			अगर (par->chip != CHIP_357_VIRGE_GX2 &&
			    par->chip != CHIP_359_VIRGE_GX2P &&
			    par->chip != CHIP_360_TRIO3D_1X &&
			    par->chip != CHIP_362_TRIO3D_2X &&
			    par->chip != CHIP_368_TRIO3D_2X &&
			    par->chip != CHIP_260_VIRGE_MX)
				hmul = 2;
		पूर्ण
		अवरोध;
	हाल 5:
		fb_dbg(info, "5/6/5 truecolor\n");
		अगर (par->chip == CHIP_988_VIRGE_VX) अणु
			अगर (info->var.pixघड़ी > 20000)
				svga_wcrt_mask(par->state.vgabase, 0x67, 0x40, 0xF0);
			अन्यथा
				svga_wcrt_mask(par->state.vgabase, 0x67, 0x50, 0xF0);
		पूर्ण अन्यथा अगर (par->chip == CHIP_365_TRIO3D) अणु
			svga_wcrt_mask(par->state.vgabase, 0x50, 0x10, 0x30);
			अगर (info->var.pixघड़ी > 8695) अणु
				svga_wcrt_mask(par->state.vgabase, 0x67, 0x50, 0xF0);
				hmul = 2;
			पूर्ण अन्यथा अणु
				svga_wcrt_mask(par->state.vgabase, 0x67, 0x40, 0xF0);
				multiplex = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			svga_wcrt_mask(par->state.vgabase, 0x50, 0x10, 0x30);
			svga_wcrt_mask(par->state.vgabase, 0x67, 0x50, 0xF0);
			अगर (par->chip != CHIP_357_VIRGE_GX2 &&
			    par->chip != CHIP_359_VIRGE_GX2P &&
			    par->chip != CHIP_360_TRIO3D_1X &&
			    par->chip != CHIP_362_TRIO3D_2X &&
			    par->chip != CHIP_368_TRIO3D_2X &&
			    par->chip != CHIP_260_VIRGE_MX)
				hmul = 2;
		पूर्ण
		अवरोध;
	हाल 6:
		/* VIRGE VX हाल */
		fb_dbg(info, "8/8/8 truecolor\n");
		svga_wcrt_mask(par->state.vgabase, 0x67, 0xD0, 0xF0);
		अवरोध;
	हाल 7:
		fb_dbg(info, "8/8/8/8 truecolor\n");
		svga_wcrt_mask(par->state.vgabase, 0x50, 0x30, 0x30);
		svga_wcrt_mask(par->state.vgabase, 0x67, 0xD0, 0xF0);
		अवरोध;
	शेष:
		fb_err(info, "unsupported mode - bug\n");
		वापस -EINVAL;
	पूर्ण

	अगर (par->chip != CHIP_988_VIRGE_VX) अणु
		svga_wseq_mask(par->state.vgabase, 0x15, multiplex ? 0x10 : 0x00, 0x10);
		svga_wseq_mask(par->state.vgabase, 0x18, multiplex ? 0x80 : 0x00, 0x80);
	पूर्ण

	s3_set_pixघड़ी(info, info->var.pixघड़ी);
	svga_set_timings(par->state.vgabase, &s3_timing_regs, &(info->var), hmul, 1,
			 (info->var.vmode & FB_VMODE_DOUBLE)     ? 2 : 1,
			 (info->var.vmode & FB_VMODE_INTERLACED) ? 2 : 1,
			 hmul, info->node);

	/* Set पूर्णांकerlaced mode start/end रेजिस्टर */
	htotal = info->var.xres + info->var.left_margin + info->var.right_margin + info->var.hsync_len;
	htotal = ((htotal * hmul) / 8) - 5;
	vga_wcrt(par->state.vgabase, 0x3C, (htotal + 1) / 2);

	/* Set Data Transfer Position */
	hsstart = ((info->var.xres + info->var.right_margin) * hmul) / 8;
	/* + 2 is needed क्रम Virge/VX, करोes no harm on other cards */
	value = clamp((htotal + hsstart + 1) / 2 + 2, hsstart + 4, htotal + 1);
	svga_wcrt_multi(par->state.vgabase, s3_dtpc_regs, value);

	स_रखो_io(info->screen_base, 0x00, screen_size);
	/* Device and screen back on */
	svga_wcrt_mask(par->state.vgabase, 0x17, 0x80, 0x80);
	svga_wseq_mask(par->state.vgabase, 0x01, 0x00, 0x20);

	वापस 0;
पूर्ण

/* Set a colour रेजिस्टर */

अटल पूर्णांक s3fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
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
		अन्यथा वापस -EINVAL;
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

अटल पूर्णांक s3fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा s3fb_info *par = info->par;

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		fb_dbg(info, "unblank\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x00, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x00, 0x20);
		अवरोध;
	हाल FB_BLANK_NORMAL:
		fb_dbg(info, "blank\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x00, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		fb_dbg(info, "hsync\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x02, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		fb_dbg(info, "vsync\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x04, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		fb_dbg(info, "sync down\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x06, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


/* Pan the display */

अटल पूर्णांक s3fb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा s3fb_info *par = info->par;
	अचिन्हित पूर्णांक offset;

	/* Calculate the offset */
	अगर (info->var.bits_per_pixel == 0) अणु
		offset = (var->yoffset / 16) * (info->var.xres_भव / 2)
		       + (var->xoffset / 2);
		offset = offset >> 2;
	पूर्ण अन्यथा अणु
		offset = (var->yoffset * info->fix.line_length) +
			 (var->xoffset * info->var.bits_per_pixel / 8);
		offset = offset >> 2;
	पूर्ण

	/* Set the offset */
	svga_wcrt_multi(par->state.vgabase, s3_start_address_regs, offset);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------- */

/* Frame buffer operations */

अटल स्थिर काष्ठा fb_ops s3fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= s3fb_खोलो,
	.fb_release	= s3fb_release,
	.fb_check_var	= s3fb_check_var,
	.fb_set_par	= s3fb_set_par,
	.fb_setcolreg	= s3fb_setcolreg,
	.fb_blank	= s3fb_blank,
	.fb_pan_display	= s3fb_pan_display,
	.fb_fillrect	= s3fb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= s3fb_imageblit,
	.fb_get_caps    = svga_get_caps,
पूर्ण;

/* ------------------------------------------------------------------------- */

अटल पूर्णांक s3_identअगरication(काष्ठा s3fb_info *par)
अणु
	पूर्णांक chip = par->chip;

	अगर (chip == CHIP_XXX_TRIO) अणु
		u8 cr30 = vga_rcrt(par->state.vgabase, 0x30);
		u8 cr2e = vga_rcrt(par->state.vgabase, 0x2e);
		u8 cr2f = vga_rcrt(par->state.vgabase, 0x2f);

		अगर ((cr30 == 0xE0) || (cr30 == 0xE1)) अणु
			अगर (cr2e == 0x10)
				वापस CHIP_732_TRIO32;
			अगर (cr2e == 0x11) अणु
				अगर (! (cr2f & 0x40))
					वापस CHIP_764_TRIO64;
				अन्यथा
					वापस CHIP_765_TRIO64VP;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (chip == CHIP_XXX_TRIO64V2_DXGX) अणु
		u8 cr6f = vga_rcrt(par->state.vgabase, 0x6f);

		अगर (! (cr6f & 0x01))
			वापस CHIP_775_TRIO64V2_DX;
		अन्यथा
			वापस CHIP_785_TRIO64V2_GX;
	पूर्ण

	अगर (chip == CHIP_XXX_VIRGE_DXGX) अणु
		u8 cr6f = vga_rcrt(par->state.vgabase, 0x6f);

		अगर (! (cr6f & 0x01))
			वापस CHIP_375_VIRGE_DX;
		अन्यथा
			वापस CHIP_385_VIRGE_GX;
	पूर्ण

	अगर (chip == CHIP_36X_TRIO3D_1X_2X) अणु
		चयन (vga_rcrt(par->state.vgabase, 0x2f)) अणु
		हाल 0x00:
			वापस CHIP_360_TRIO3D_1X;
		हाल 0x01:
			वापस CHIP_362_TRIO3D_2X;
		हाल 0x02:
			वापस CHIP_368_TRIO3D_2X;
		पूर्ण
	पूर्ण

	वापस CHIP_UNKNOWN;
पूर्ण


/* PCI probe */

अटल पूर्णांक s3_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pci_bus_region bus_reg;
	काष्ठा resource vga_res;
	काष्ठा fb_info *info;
	काष्ठा s3fb_info *par;
	पूर्णांक rc;
	u8 regval, cr38, cr39;
	bool found = false;

	/* Ignore secondary VGA device because there is no VGA arbitration */
	अगर (! svga_primary_device(dev)) अणु
		dev_info(&(dev->dev), "ignoring secondary device\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate and fill driver data काष्ठाure */
	info = framebuffer_alloc(माप(काष्ठा s3fb_info), &(dev->dev));
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	mutex_init(&par->खोलो_lock);

	info->flags = FBINFO_PARTIAL_PAN_OK | FBINFO_HWACCEL_YPAN;
	info->fbops = &s3fb_ops;

	/* Prepare PCI device */
	rc = pci_enable_device(dev);
	अगर (rc < 0) अणु
		dev_err(info->device, "cannot enable PCI device\n");
		जाओ err_enable_device;
	पूर्ण

	rc = pci_request_regions(dev, "s3fb");
	अगर (rc < 0) अणु
		dev_err(info->device, "cannot reserve framebuffer region\n");
		जाओ err_request_regions;
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

	/* Unlock regs */
	cr38 = vga_rcrt(par->state.vgabase, 0x38);
	cr39 = vga_rcrt(par->state.vgabase, 0x39);
	vga_wseq(par->state.vgabase, 0x08, 0x06);
	vga_wcrt(par->state.vgabase, 0x38, 0x48);
	vga_wcrt(par->state.vgabase, 0x39, 0xA5);

	/* Identअगरy chip type */
	par->chip = id->driver_data & CHIP_MASK;
	par->rev = vga_rcrt(par->state.vgabase, 0x2f);
	अगर (par->chip & CHIP_UNDECIDED_FLAG)
		par->chip = s3_identअगरication(par);

	/* Find how many physical memory there is on card */
	/* 0x36 रेजिस्टर is accessible even अगर other रेजिस्टरs are locked */
	regval = vga_rcrt(par->state.vgabase, 0x36);
	अगर (par->chip == CHIP_360_TRIO3D_1X ||
	    par->chip == CHIP_362_TRIO3D_2X ||
	    par->chip == CHIP_368_TRIO3D_2X ||
	    par->chip == CHIP_365_TRIO3D) अणु
		चयन ((regval & 0xE0) >> 5) अणु
		हाल 0: /* 8MB -- only 4MB usable क्रम display */
		हाल 1: /* 4MB with 32-bit bus */
		हाल 2:	/* 4MB */
			info->screen_size = 4 << 20;
			अवरोध;
		हाल 4: /* 2MB on 365 Trio3D */
		हाल 6: /* 2MB */
			info->screen_size = 2 << 20;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (par->chip == CHIP_357_VIRGE_GX2 ||
		   par->chip == CHIP_359_VIRGE_GX2P ||
		   par->chip == CHIP_260_VIRGE_MX) अणु
		चयन ((regval & 0xC0) >> 6) अणु
		हाल 1: /* 4MB */
			info->screen_size = 4 << 20;
			अवरोध;
		हाल 3: /* 2MB */
			info->screen_size = 2 << 20;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (par->chip == CHIP_988_VIRGE_VX) अणु
		चयन ((regval & 0x60) >> 5) अणु
		हाल 0: /* 2MB */
			info->screen_size = 2 << 20;
			अवरोध;
		हाल 1: /* 4MB */
			info->screen_size = 4 << 20;
			अवरोध;
		हाल 2: /* 6MB */
			info->screen_size = 6 << 20;
			अवरोध;
		हाल 3: /* 8MB */
			info->screen_size = 8 << 20;
			अवरोध;
		पूर्ण
		/* off-screen memory */
		regval = vga_rcrt(par->state.vgabase, 0x37);
		चयन ((regval & 0x60) >> 5) अणु
		हाल 1: /* 4MB */
			info->screen_size -= 4 << 20;
			अवरोध;
		हाल 2: /* 2MB */
			info->screen_size -= 2 << 20;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		info->screen_size = s3_memsizes[regval >> 5] << 10;
	info->fix.smem_len = info->screen_size;

	/* Find MCLK frequency */
	regval = vga_rseq(par->state.vgabase, 0x10);
	par->mclk_freq = ((vga_rseq(par->state.vgabase, 0x11) + 2) * 14318) / ((regval & 0x1F)  + 2);
	par->mclk_freq = par->mclk_freq >> (regval >> 5);

	/* Restore locks */
	vga_wcrt(par->state.vgabase, 0x38, cr38);
	vga_wcrt(par->state.vgabase, 0x39, cr39);

	म_नकल(info->fix.id, s3_names [par->chip]);
	info->fix.mmio_start = 0;
	info->fix.mmio_len = 0;
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
	info->fix.ypanstep = 0;
	info->fix.accel = FB_ACCEL_NONE;
	info->pseuकरो_palette = (व्योम*) (par->pseuकरो_palette);
	info->var.bits_per_pixel = 8;

#अगर_घोषित CONFIG_FB_S3_DDC
	/* Enable MMIO अगर needed */
	अगर (s3fb_ddc_needs_mmio(par->chip)) अणु
		par->mmio = ioremap(info->fix.smem_start + MMIO_OFFSET, MMIO_SIZE);
		अगर (par->mmio)
			svga_wcrt_mask(par->state.vgabase, 0x53, 0x08, 0x08);	/* enable MMIO */
		अन्यथा
			dev_err(info->device, "unable to map MMIO at 0x%lx, disabling DDC",
				info->fix.smem_start + MMIO_OFFSET);
	पूर्ण
	अगर (!s3fb_ddc_needs_mmio(par->chip) || par->mmio)
		अगर (s3fb_setup_ddc_bus(info) == 0) अणु
			u8 *edid = fb_ddc_पढ़ो(&par->ddc_adapter);
			par->ddc_रेजिस्टरed = true;
			अगर (edid) अणु
				fb_edid_to_monspecs(edid, &info->monspecs);
				kमुक्त(edid);
				अगर (!info->monspecs.modedb)
					dev_err(info->device, "error getting mode database\n");
				अन्यथा अणु
					स्थिर काष्ठा fb_videomode *m;

					fb_videomode_to_modelist(info->monspecs.modedb,
								 info->monspecs.modedb_len,
								 &info->modelist);
					m = fb_find_best_display(&info->monspecs, &info->modelist);
					अगर (m) अणु
						fb_videomode_to_var(&info->var, m);
						/* fill all other info->var's fields */
						अगर (s3fb_check_var(&info->var, info) == 0)
							found = true;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	अगर (!mode_option && !found)
		mode_option = "640x480-8@60";

	/* Prepare startup mode */
	अगर (mode_option) अणु
		rc = fb_find_mode(&info->var, info, mode_option,
				   info->monspecs.modedb, info->monspecs.modedb_len,
				   शून्य, info->var.bits_per_pixel);
		अगर (!rc || rc == 4) अणु
			rc = -EINVAL;
			dev_err(info->device, "mode %s not found\n", mode_option);
			fb_destroy_modedb(info->monspecs.modedb);
			info->monspecs.modedb = शून्य;
			जाओ err_find_mode;
		पूर्ण
	पूर्ण

	fb_destroy_modedb(info->monspecs.modedb);
	info->monspecs.modedb = शून्य;

	/* maximize भव vertical size क्रम fast scrolling */
	info->var.yres_भव = info->fix.smem_len * 8 /
			(info->var.bits_per_pixel * info->var.xres_भव);
	अगर (info->var.yres_भव < info->var.yres) अणु
		dev_err(info->device, "virtual vertical size smaller than real\n");
		rc = -EINVAL;
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

	fb_info(info, "%s on %s, %d MB RAM, %d MHz MCLK\n",
		info->fix.id, pci_name(dev),
		info->fix.smem_len >> 20, (par->mclk_freq + 500) / 1000);

	अगर (par->chip == CHIP_UNKNOWN)
		fb_info(info, "unknown chip, CR2D=%x, CR2E=%x, CRT2F=%x, CRT30=%x\n",
			vga_rcrt(par->state.vgabase, 0x2d),
			vga_rcrt(par->state.vgabase, 0x2e),
			vga_rcrt(par->state.vgabase, 0x2f),
			vga_rcrt(par->state.vgabase, 0x30));

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
#अगर_घोषित CONFIG_FB_S3_DDC
	अगर (par->ddc_रेजिस्टरed)
		i2c_del_adapter(&par->ddc_adapter);
	अगर (par->mmio)
		iounmap(par->mmio);
#पूर्ण_अगर
	pci_iounmap(dev, info->screen_base);
err_iomap:
	pci_release_regions(dev);
err_request_regions:
/*	pci_disable_device(dev); */
err_enable_device:
	framebuffer_release(info);
	वापस rc;
पूर्ण


/* PCI हटाओ */

अटल व्योम s3_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);
	काष्ठा s3fb_info __maybe_unused *par;

	अगर (info) अणु
		par = info->par;
		arch_phys_wc_del(par->wc_cookie);
		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);

#अगर_घोषित CONFIG_FB_S3_DDC
		अगर (par->ddc_रेजिस्टरed)
			i2c_del_adapter(&par->ddc_adapter);
		अगर (par->mmio)
			iounmap(par->mmio);
#पूर्ण_अगर

		pci_iounmap(dev, info->screen_base);
		pci_release_regions(dev);
/*		pci_disable_device(dev); */

		framebuffer_release(info);
	पूर्ण
पूर्ण

/* PCI suspend */

अटल पूर्णांक __maybe_unused s3_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा s3fb_info *par = info->par;

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

अटल पूर्णांक __maybe_unused s3_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा s3fb_info *par = info->par;

	dev_info(info->device, "resume\n");

	console_lock();
	mutex_lock(&(par->खोलो_lock));

	अगर (par->ref_count == 0) अणु
		mutex_unlock(&(par->खोलो_lock));
		console_unlock();
		वापस 0;
	पूर्ण

	s3fb_set_par(info);
	fb_set_suspend(info, 0);

	mutex_unlock(&(par->खोलो_lock));
	console_unlock();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops s3_pci_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= s3_pci_suspend,
	.resume		= s3_pci_resume,
	.मुक्तze		= शून्य,
	.thaw		= s3_pci_resume,
	.घातeroff	= s3_pci_suspend,
	.restore	= s3_pci_resume,
#पूर्ण_अगर
पूर्ण;

/* List of boards that we are trying to support */

अटल स्थिर काष्ठा pci_device_id s3_devices[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8810), .driver_data = CHIP_XXX_TRIOपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8811), .driver_data = CHIP_XXX_TRIOपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8812), .driver_data = CHIP_M65_AURORA64VPपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8814), .driver_data = CHIP_767_TRIO64UVPपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8901), .driver_data = CHIP_XXX_TRIO64V2_DXGXपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8902), .driver_data = CHIP_551_PLATO_PXपूर्ण,

	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x5631), .driver_data = CHIP_325_VIRGEपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x883D), .driver_data = CHIP_988_VIRGE_VXपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8A01), .driver_data = CHIP_XXX_VIRGE_DXGXपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8A10), .driver_data = CHIP_357_VIRGE_GX2पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8A11), .driver_data = CHIP_359_VIRGE_GX2Pपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8A12), .driver_data = CHIP_359_VIRGE_GX2Pपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8A13), .driver_data = CHIP_36X_TRIO3D_1X_2Xपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8904), .driver_data = CHIP_365_TRIO3Dपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_S3, 0x8C01), .driver_data = CHIP_260_VIRGE_MXपूर्ण,

	अणु0, 0, 0, 0, 0, 0, 0पूर्ण
पूर्ण;


MODULE_DEVICE_TABLE(pci, s3_devices);

अटल काष्ठा pci_driver s3fb_pci_driver = अणु
	.name		= "s3fb",
	.id_table	= s3_devices,
	.probe		= s3_pci_probe,
	.हटाओ		= s3_pci_हटाओ,
	.driver.pm	= &s3_pci_pm_ops,
पूर्ण;

/* Parse user specअगरied options */

#अगर_अघोषित MODULE
अटल पूर्णांक  __init s3fb_setup(अक्षर *options)
अणु
	अक्षर *opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु

		अगर (!*opt)
			जारी;
		अन्यथा अगर (!म_भेदन(opt, "mtrr:", 5))
			mtrr = simple_म_से_अदीर्घ(opt + 5, शून्य, 0);
		अन्यथा अगर (!म_भेदन(opt, "fasttext:", 9))
			fasttext = simple_म_से_अदीर्घ(opt + 9, शून्य, 0);
		अन्यथा
			mode_option = opt;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Cleanup */

अटल व्योम __निकास s3fb_cleanup(व्योम)
अणु
	pr_debug("s3fb: cleaning up\n");
	pci_unरेजिस्टर_driver(&s3fb_pci_driver);
पूर्ण

/* Driver Initialisation */

अटल पूर्णांक __init s3fb_init(व्योम)
अणु

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("s3fb", &option))
		वापस -ENODEV;
	s3fb_setup(option);
#पूर्ण_अगर

	pr_debug("s3fb: initializing\n");
	वापस pci_रेजिस्टर_driver(&s3fb_pci_driver);
पूर्ण

/* ------------------------------------------------------------------------- */

/* Modularization */

module_init(s3fb_init);
module_निकास(s3fb_cleanup);
