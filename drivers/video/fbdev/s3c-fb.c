<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/video/s3c-fb.c
 *
 * Copyright 2008 Openmoko Inc.
 * Copyright 2008-2010 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * Samsung SoC Framebuffer driver
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_data/video_s3c.h>

#समावेश <video/samsung_fimd.h>

/* This driver will export a number of framebuffer पूर्णांकerfaces depending
 * on the configuration passed in via the platक्रमm data. Each fb instance
 * maps to a hardware winकरोw. Currently there is no support क्रम runसमय
 * setting of the alpha-blending functions that each winकरोw has, so only
 * winकरोw 0 is actually useful.
 *
 * Winकरोw 0 is treated specially, it is used क्रम the basis of the LCD
 * output timings and as the control क्रम the output घातer-करोwn state.
*/

/* note, the previous use of <mach/regs-fb.h> to get platक्रमm specअगरic data
 * has been replaced by using the platक्रमm device name to pick the correct
 * configuration data क्रम the प्रणाली.
*/

#अगर_घोषित CONFIG_FB_S3C_DEBUG_REGWRITE
#अघोषित ग_लिखोl
#घोषणा ग_लिखोl(v, r) करो अणु \
	pr_debug("%s: %08x => %p\n", __func__, (अचिन्हित पूर्णांक)v, r); \
	__raw_ग_लिखोl(v, r); \
पूर्ण जबतक (0)
#पूर्ण_अगर /* FB_S3C_DEBUG_REGWRITE */

/* irq_flags bits */
#घोषणा S3C_FB_VSYNC_IRQ_EN	0

#घोषणा VSYNC_TIMEOUT_MSEC 50

काष्ठा s3c_fb;

#घोषणा VALID_BPP(x) (1 << ((x) - 1))

#घोषणा OSD_BASE(win, variant) ((variant).osd + ((win) * (variant).osd_stride))
#घोषणा VIDOSD_A(win, variant) (OSD_BASE(win, variant) + 0x00)
#घोषणा VIDOSD_B(win, variant) (OSD_BASE(win, variant) + 0x04)
#घोषणा VIDOSD_C(win, variant) (OSD_BASE(win, variant) + 0x08)
#घोषणा VIDOSD_D(win, variant) (OSD_BASE(win, variant) + 0x0C)

/**
 * काष्ठा s3c_fb_variant - fb variant inक्रमmation
 * @is_2443: Set अगर S3C2443/S3C2416 style hardware.
 * @nr_winकरोws: The number of winकरोws.
 * @vidtcon: The base क्रम the VIDTCONx रेजिस्टरs
 * @wincon: The base क्रम the WINxCON रेजिस्टरs.
 * @winmap: The base क्रम the WINxMAP रेजिस्टरs.
 * @keycon: The असलe क्रम the WxKEYCON रेजिस्टरs.
 * @buf_start: Offset of buffer start रेजिस्टरs.
 * @buf_size: Offset of buffer size रेजिस्टरs.
 * @buf_end: Offset of buffer end रेजिस्टरs.
 * @osd: The base क्रम the OSD रेजिस्टरs.
 * @osd_stride: stride of osd
 * @palette: Address of palette memory, or 0 अगर none.
 * @has_prtcon: Set अगर has PRTCON रेजिस्टर.
 * @has_shaकरोwcon: Set अगर has SHADOWCON रेजिस्टर.
 * @has_blendcon: Set अगर has BLENDCON रेजिस्टर.
 * @has_clksel: Set अगर VIDCON0 रेजिस्टर has CLKSEL bit.
 * @has_fixvclk: Set अगर VIDCON1 रेजिस्टर has FIXVCLK bits.
 */
काष्ठा s3c_fb_variant अणु
	अचिन्हित पूर्णांक	is_2443:1;
	अचिन्हित लघु	nr_winकरोws;
	अचिन्हित पूर्णांक	vidtcon;
	अचिन्हित लघु	wincon;
	अचिन्हित लघु	winmap;
	अचिन्हित लघु	keycon;
	अचिन्हित लघु	buf_start;
	अचिन्हित लघु	buf_end;
	अचिन्हित लघु	buf_size;
	अचिन्हित लघु	osd;
	अचिन्हित लघु	osd_stride;
	अचिन्हित लघु	palette[S3C_FB_MAX_WIN];

	अचिन्हित पूर्णांक	has_prtcon:1;
	अचिन्हित पूर्णांक	has_shaकरोwcon:1;
	अचिन्हित पूर्णांक	has_blendcon:1;
	अचिन्हित पूर्णांक	has_clksel:1;
	अचिन्हित पूर्णांक	has_fixvclk:1;
पूर्ण;

/**
 * काष्ठा s3c_fb_win_variant
 * @has_osd_c: Set अगर has OSD C रेजिस्टर.
 * @has_osd_d: Set अगर has OSD D रेजिस्टर.
 * @has_osd_alpha: Set अगर can change alpha transparency क्रम a winकरोw.
 * @palette_sz: Size of palette in entries.
 * @palette_16bpp: Set अगर palette is 16bits wide.
 * @osd_size_off: If != 0, supports setting up OSD क्रम a winकरोw; the appropriate
 *                रेजिस्टर is located at the given offset from OSD_BASE.
 * @valid_bpp: 1 bit per BPP setting to show valid bits-per-pixel.
 *
 * valid_bpp bit x is set अगर (x+1)BPP is supported.
 */
काष्ठा s3c_fb_win_variant अणु
	अचिन्हित पूर्णांक	has_osd_c:1;
	अचिन्हित पूर्णांक	has_osd_d:1;
	अचिन्हित पूर्णांक	has_osd_alpha:1;
	अचिन्हित पूर्णांक	palette_16bpp:1;
	अचिन्हित लघु	osd_size_off;
	अचिन्हित लघु	palette_sz;
	u32		valid_bpp;
पूर्ण;

/**
 * काष्ठा s3c_fb_driverdata - per-device type driver data क्रम init समय.
 * @variant: The variant inक्रमmation क्रम this driver.
 * @win: The winकरोw inक्रमmation क्रम each winकरोw.
 */
काष्ठा s3c_fb_driverdata अणु
	काष्ठा s3c_fb_variant	variant;
	काष्ठा s3c_fb_win_variant *win[S3C_FB_MAX_WIN];
पूर्ण;

/**
 * काष्ठा s3c_fb_palette - palette inक्रमmation
 * @r: Red bitfield.
 * @g: Green bitfield.
 * @b: Blue bitfield.
 * @a: Alpha bitfield.
 */
काष्ठा s3c_fb_palette अणु
	काष्ठा fb_bitfield	r;
	काष्ठा fb_bitfield	g;
	काष्ठा fb_bitfield	b;
	काष्ठा fb_bitfield	a;
पूर्ण;

/**
 * काष्ठा s3c_fb_win - per winकरोw निजी data क्रम each framebuffer.
 * @windata: The platक्रमm data supplied क्रम the winकरोw configuration.
 * @parent: The hardware that this winकरोw is part of.
 * @fbinfo: Poपूर्णांकer pack to the framebuffer info क्रम this winकरोw.
 * @variant: The variant inक्रमmation क्रम this winकरोw.
 * @palette_buffer: Buffer/cache to hold palette entries.
 * @pseuकरो_palette: For use in TRUECOLOUR modes क्रम entries 0..15/
 * @index: The winकरोw number of this winकरोw.
 * @palette: The bitfields क्रम changing r/g/b पूर्णांकo a hardware palette entry.
 */
काष्ठा s3c_fb_win अणु
	काष्ठा s3c_fb_pd_win	*windata;
	काष्ठा s3c_fb		*parent;
	काष्ठा fb_info		*fbinfo;
	काष्ठा s3c_fb_palette	 palette;
	काष्ठा s3c_fb_win_variant variant;

	u32			*palette_buffer;
	u32			 pseuकरो_palette[16];
	अचिन्हित पूर्णांक		 index;
पूर्ण;

/**
 * काष्ठा s3c_fb_vsync - vsync inक्रमmation
 * @रुको:	a queue क्रम processes रुकोing क्रम vsync
 * @count:	vsync पूर्णांकerrupt count
 */
काष्ठा s3c_fb_vsync अणु
	रुको_queue_head_t	रुको;
	अचिन्हित पूर्णांक		count;
पूर्ण;

/**
 * काष्ठा s3c_fb - overall hardware state of the hardware
 * @slock: The spinlock protection क्रम this data काष्ठाure.
 * @dev: The device that we bound to, क्रम prपूर्णांकing, etc.
 * @bus_clk: The clk (hclk) feeding our पूर्णांकerface and possibly pixclk.
 * @lcd_clk: The clk (sclk) feeding pixclk.
 * @regs: The mapped hardware रेजिस्टरs.
 * @variant: Variant inक्रमmation क्रम this hardware.
 * @enabled: A biपंचांगask of enabled hardware winकरोws.
 * @output_on: Flag अगर the physical output is enabled.
 * @pdata: The platक्रमm configuration data passed with the device.
 * @winकरोws: The hardware winकरोws that have been claimed.
 * @irq_no: IRQ line number
 * @irq_flags: irq flags
 * @vsync_info: VSYNC-related inक्रमmation (count, queues...)
 */
काष्ठा s3c_fb अणु
	spinlock_t		slock;
	काष्ठा device		*dev;
	काष्ठा clk		*bus_clk;
	काष्ठा clk		*lcd_clk;
	व्योम __iomem		*regs;
	काष्ठा s3c_fb_variant	 variant;

	अचिन्हित अक्षर		 enabled;
	bool			 output_on;

	काष्ठा s3c_fb_platdata	*pdata;
	काष्ठा s3c_fb_win	*winकरोws[S3C_FB_MAX_WIN];

	पूर्णांक			 irq_no;
	अचिन्हित दीर्घ		 irq_flags;
	काष्ठा s3c_fb_vsync	 vsync_info;
पूर्ण;

/**
 * s3c_fb_validate_win_bpp - validate the bits-per-pixel क्रम this mode.
 * @win: The device winकरोw.
 * @bpp: The bit depth.
 */
अटल bool s3c_fb_validate_win_bpp(काष्ठा s3c_fb_win *win, अचिन्हित पूर्णांक bpp)
अणु
	वापस win->variant.valid_bpp & VALID_BPP(bpp);
पूर्ण

/**
 * s3c_fb_check_var() - framebuffer layer request to verअगरy a given mode.
 * @var: The screen inक्रमmation to verअगरy.
 * @info: The framebuffer device.
 *
 * Framebuffer layer call to verअगरy the given inक्रमmation and allow us to
 * update various inक्रमmation depending on the hardware capabilities.
 */
अटल पूर्णांक s3c_fb_check_var(काष्ठा fb_var_screeninfo *var,
			    काष्ठा fb_info *info)
अणु
	काष्ठा s3c_fb_win *win = info->par;
	काष्ठा s3c_fb *sfb = win->parent;

	dev_dbg(sfb->dev, "checking parameters\n");

	var->xres_भव = max(var->xres_भव, var->xres);
	var->yres_भव = max(var->yres_भव, var->yres);

	अगर (!s3c_fb_validate_win_bpp(win, var->bits_per_pixel)) अणु
		dev_dbg(sfb->dev, "win %d: unsupported bpp %d\n",
			win->index, var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	/* always ensure these are zero, क्रम drop through हालs below */
	var->transp.offset = 0;
	var->transp.length = 0;

	चयन (var->bits_per_pixel) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		अगर (sfb->variant.palette[win->index] != 0) अणु
			/* non palletised, A:1,R:2,G:3,B:2 mode */
			var->red.offset		= 5;
			var->green.offset	= 2;
			var->blue.offset	= 0;
			var->red.length		= 2;
			var->green.length	= 3;
			var->blue.length	= 2;
			var->transp.offset	= 7;
			var->transp.length	= 1;
		पूर्ण अन्यथा अणु
			var->red.offset	= 0;
			var->red.length	= var->bits_per_pixel;
			var->green	= var->red;
			var->blue	= var->red;
		पूर्ण
		अवरोध;

	हाल 19:
		/* 666 with one bit alpha/transparency */
		var->transp.offset	= 18;
		var->transp.length	= 1;
		fallthrough;
	हाल 18:
		var->bits_per_pixel	= 32;

		/* 666 क्रमmat */
		var->red.offset		= 12;
		var->green.offset	= 6;
		var->blue.offset	= 0;
		var->red.length		= 6;
		var->green.length	= 6;
		var->blue.length	= 6;
		अवरोध;

	हाल 16:
		/* 16 bpp, 565 क्रमmat */
		var->red.offset		= 11;
		var->green.offset	= 5;
		var->blue.offset	= 0;
		var->red.length		= 5;
		var->green.length	= 6;
		var->blue.length	= 5;
		अवरोध;

	हाल 32:
	हाल 28:
	हाल 25:
		var->transp.length	= var->bits_per_pixel - 24;
		var->transp.offset	= 24;
		fallthrough;
	हाल 24:
		/* our 24bpp is unpacked, so 32bpp */
		var->bits_per_pixel	= 32;
		var->red.offset		= 16;
		var->red.length		= 8;
		var->green.offset	= 8;
		var->green.length	= 8;
		var->blue.offset	= 0;
		var->blue.length	= 8;
		अवरोध;

	शेष:
		dev_err(sfb->dev, "invalid bpp\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(sfb->dev, "%s: verified parameters\n", __func__);
	वापस 0;
पूर्ण

/**
 * s3c_fb_calc_pixclk() - calculate the भागider to create the pixel घड़ी.
 * @sfb: The hardware state.
 * @pixclk: The pixel घड़ी wanted, in picoseconds.
 *
 * Given the specअगरied pixel घड़ी, work out the necessary भागider to get
 * बंद to the output frequency.
 */
अटल पूर्णांक s3c_fb_calc_pixclk(काष्ठा s3c_fb *sfb, अचिन्हित पूर्णांक pixclk)
अणु
	अचिन्हित दीर्घ clk;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	अचिन्हित पूर्णांक result;

	अगर (sfb->variant.has_clksel)
		clk = clk_get_rate(sfb->bus_clk);
	अन्यथा
		clk = clk_get_rate(sfb->lcd_clk);

	पंचांगp = (अचिन्हित दीर्घ दीर्घ)clk;
	पंचांगp *= pixclk;

	करो_भाग(पंचांगp, 1000000000UL);
	result = (अचिन्हित पूर्णांक)पंचांगp / 1000;

	dev_dbg(sfb->dev, "pixclk=%u, clk=%lu, div=%d (%lu)\n",
		pixclk, clk, result, result ? clk / result : clk);

	वापस result;
पूर्ण

/**
 * s3c_fb_align_word() - align pixel count to word boundary
 * @bpp: The number of bits per pixel
 * @pix: The value to be aligned.
 *
 * Align the given pixel count so that it will start on an 32bit word
 * boundary.
 */
अटल पूर्णांक s3c_fb_align_word(अचिन्हित पूर्णांक bpp, अचिन्हित पूर्णांक pix)
अणु
	पूर्णांक pix_per_word;

	अगर (bpp > 16)
		वापस pix;

	pix_per_word = (8 * 32) / bpp;
	वापस ALIGN(pix, pix_per_word);
पूर्ण

/**
 * viकरोsd_set_size() - set OSD size क्रम a winकरोw
 *
 * @win: the winकरोw to set OSD size क्रम
 * @size: OSD size रेजिस्टर value
 */
अटल व्योम viकरोsd_set_size(काष्ठा s3c_fb_win *win, u32 size)
अणु
	काष्ठा s3c_fb *sfb = win->parent;

	/* OSD can be set up अगर osd_size_off != 0 क्रम this winकरोw */
	अगर (win->variant.osd_size_off)
		ग_लिखोl(size, sfb->regs + OSD_BASE(win->index, sfb->variant)
				+ win->variant.osd_size_off);
पूर्ण

/**
 * viकरोsd_set_alpha() - set alpha transparency क्रम a winकरोw
 *
 * @win: the winकरोw to set OSD size क्रम
 * @alpha: alpha रेजिस्टर value
 */
अटल व्योम viकरोsd_set_alpha(काष्ठा s3c_fb_win *win, u32 alpha)
अणु
	काष्ठा s3c_fb *sfb = win->parent;

	अगर (win->variant.has_osd_alpha)
		ग_लिखोl(alpha, sfb->regs + VIDOSD_C(win->index, sfb->variant));
पूर्ण

/**
 * shaकरोw_protect_win() - disable updating values from shaकरोw रेजिस्टरs at vsync
 *
 * @win: winकरोw to protect रेजिस्टरs क्रम
 * @protect: 1 to protect (disable updates)
 */
अटल व्योम shaकरोw_protect_win(काष्ठा s3c_fb_win *win, bool protect)
अणु
	काष्ठा s3c_fb *sfb = win->parent;
	u32 reg;

	अगर (protect) अणु
		अगर (sfb->variant.has_prtcon) अणु
			ग_लिखोl(PRTCON_PROTECT, sfb->regs + PRTCON);
		पूर्ण अन्यथा अगर (sfb->variant.has_shaकरोwcon) अणु
			reg = पढ़ोl(sfb->regs + SHADOWCON);
			ग_लिखोl(reg | SHADOWCON_WINx_PROTECT(win->index),
				sfb->regs + SHADOWCON);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sfb->variant.has_prtcon) अणु
			ग_लिखोl(0, sfb->regs + PRTCON);
		पूर्ण अन्यथा अगर (sfb->variant.has_shaकरोwcon) अणु
			reg = पढ़ोl(sfb->regs + SHADOWCON);
			ग_लिखोl(reg & ~SHADOWCON_WINx_PROTECT(win->index),
				sfb->regs + SHADOWCON);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * s3c_fb_enable() - Set the state of the मुख्य LCD output
 * @sfb: The मुख्य framebuffer state.
 * @enable: The state to set.
 */
अटल व्योम s3c_fb_enable(काष्ठा s3c_fb *sfb, पूर्णांक enable)
अणु
	u32 vidcon0 = पढ़ोl(sfb->regs + VIDCON0);

	अगर (enable && !sfb->output_on)
		pm_runसमय_get_sync(sfb->dev);

	अगर (enable) अणु
		vidcon0 |= VIDCON0_ENVID | VIDCON0_ENVID_F;
	पूर्ण अन्यथा अणु
		/* see the note in the framebuffer datasheet about
		 * why you cannot take both of these bits करोwn at the
		 * same समय. */

		अगर (vidcon0 & VIDCON0_ENVID) अणु
			vidcon0 |= VIDCON0_ENVID;
			vidcon0 &= ~VIDCON0_ENVID_F;
		पूर्ण
	पूर्ण

	ग_लिखोl(vidcon0, sfb->regs + VIDCON0);

	अगर (!enable && sfb->output_on)
		pm_runसमय_put_sync(sfb->dev);

	sfb->output_on = enable;
पूर्ण

/**
 * s3c_fb_set_par() - framebuffer request to set new framebuffer state.
 * @info: The framebuffer to change.
 *
 * Framebuffer layer request to set a new mode क्रम the specअगरied framebuffer
 */
अटल पूर्णांक s3c_fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा s3c_fb_win *win = info->par;
	काष्ठा s3c_fb *sfb = win->parent;
	व्योम __iomem *regs = sfb->regs;
	व्योम __iomem *buf = regs;
	पूर्णांक win_no = win->index;
	u32 alpha = 0;
	u32 data;
	u32 pagewidth;

	dev_dbg(sfb->dev, "setting framebuffer parameters\n");

	pm_runसमय_get_sync(sfb->dev);

	shaकरोw_protect_win(win, 1);

	चयन (var->bits_per_pixel) अणु
	हाल 32:
	हाल 24:
	हाल 16:
	हाल 12:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	हाल 8:
		अगर (win->variant.palette_sz >= 256)
			info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अन्यथा
			info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	हाल 1:
		info->fix.visual = FB_VISUAL_MONO01;
		अवरोध;
	शेष:
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	पूर्ण

	info->fix.line_length = (var->xres_भव * var->bits_per_pixel) / 8;

	info->fix.xpanstep = info->var.xres_भव > info->var.xres ? 1 : 0;
	info->fix.ypanstep = info->var.yres_भव > info->var.yres ? 1 : 0;

	/* disable the winकरोw whilst we update it */
	ग_लिखोl(0, regs + WINCON(win_no));

	अगर (!sfb->output_on)
		s3c_fb_enable(sfb, 1);

	/* ग_लिखो the buffer address */

	/* start and end रेजिस्टरs stride is 8 */
	buf = regs + win_no * 8;

	ग_लिखोl(info->fix.smem_start, buf + sfb->variant.buf_start);

	data = info->fix.smem_start + info->fix.line_length * var->yres;
	ग_लिखोl(data, buf + sfb->variant.buf_end);

	pagewidth = (var->xres * var->bits_per_pixel) >> 3;
	data = VIDW_BUF_SIZE_OFFSET(info->fix.line_length - pagewidth) |
	       VIDW_BUF_SIZE_PAGEWIDTH(pagewidth) |
	       VIDW_BUF_SIZE_OFFSET_E(info->fix.line_length - pagewidth) |
	       VIDW_BUF_SIZE_PAGEWIDTH_E(pagewidth);
	ग_लिखोl(data, regs + sfb->variant.buf_size + (win_no * 4));

	/* ग_लिखो 'OSD' रेजिस्टरs to control position of framebuffer */

	data = VIDOSDxA_TOPLEFT_X(0) | VIDOSDxA_TOPLEFT_Y(0) |
	       VIDOSDxA_TOPLEFT_X_E(0) | VIDOSDxA_TOPLEFT_Y_E(0);
	ग_लिखोl(data, regs + VIDOSD_A(win_no, sfb->variant));

	data = VIDOSDxB_BOTRIGHT_X(s3c_fb_align_word(var->bits_per_pixel,
						     var->xres - 1)) |
	       VIDOSDxB_BOTRIGHT_Y(var->yres - 1) |
	       VIDOSDxB_BOTRIGHT_X_E(s3c_fb_align_word(var->bits_per_pixel,
						     var->xres - 1)) |
	       VIDOSDxB_BOTRIGHT_Y_E(var->yres - 1);

	ग_लिखोl(data, regs + VIDOSD_B(win_no, sfb->variant));

	data = var->xres * var->yres;

	alpha = VIDISD14C_ALPHA1_R(0xf) |
		VIDISD14C_ALPHA1_G(0xf) |
		VIDISD14C_ALPHA1_B(0xf);

	viकरोsd_set_alpha(win, alpha);
	viकरोsd_set_size(win, data);

	/* Enable DMA channel क्रम this winकरोw */
	अगर (sfb->variant.has_shaकरोwcon) अणु
		data = पढ़ोl(sfb->regs + SHADOWCON);
		data |= SHADOWCON_CHx_ENABLE(win_no);
		ग_लिखोl(data, sfb->regs + SHADOWCON);
	पूर्ण

	data = WINCONx_ENWIN;
	sfb->enabled |= (1 << win->index);

	/* note, since we have to round up the bits-per-pixel, we end up
	 * relying on the bitfield inक्रमmation क्रम r/g/b/a to work out
	 * exactly which mode of operation is पूर्णांकended. */

	चयन (var->bits_per_pixel) अणु
	हाल 1:
		data |= WINCON0_BPPMODE_1BPP;
		data |= WINCONx_BITSWP;
		data |= WINCONx_BURSTLEN_4WORD;
		अवरोध;
	हाल 2:
		data |= WINCON0_BPPMODE_2BPP;
		data |= WINCONx_BITSWP;
		data |= WINCONx_BURSTLEN_8WORD;
		अवरोध;
	हाल 4:
		data |= WINCON0_BPPMODE_4BPP;
		data |= WINCONx_BITSWP;
		data |= WINCONx_BURSTLEN_8WORD;
		अवरोध;
	हाल 8:
		अगर (var->transp.length != 0)
			data |= WINCON1_BPPMODE_8BPP_1232;
		अन्यथा
			data |= WINCON0_BPPMODE_8BPP_PALETTE;
		data |= WINCONx_BURSTLEN_8WORD;
		data |= WINCONx_BYTSWP;
		अवरोध;
	हाल 16:
		अगर (var->transp.length != 0)
			data |= WINCON1_BPPMODE_16BPP_A1555;
		अन्यथा
			data |= WINCON0_BPPMODE_16BPP_565;
		data |= WINCONx_HAWSWP;
		data |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल 24:
	हाल 32:
		अगर (var->red.length == 6) अणु
			अगर (var->transp.length != 0)
				data |= WINCON1_BPPMODE_19BPP_A1666;
			अन्यथा
				data |= WINCON1_BPPMODE_18BPP_666;
		पूर्ण अन्यथा अगर (var->transp.length == 1)
			data |= WINCON1_BPPMODE_25BPP_A1888
				| WINCON1_BLD_PIX;
		अन्यथा अगर ((var->transp.length == 4) ||
			(var->transp.length == 8))
			data |= WINCON1_BPPMODE_28BPP_A4888
				| WINCON1_BLD_PIX | WINCON1_ALPHA_SEL;
		अन्यथा
			data |= WINCON0_BPPMODE_24BPP_888;

		data |= WINCONx_WSWP;
		data |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	पूर्ण

	/* Enable the colour keying क्रम the winकरोw below this one */
	अगर (win_no > 0) अणु
		u32 keycon0_data = 0, keycon1_data = 0;
		व्योम __iomem *keycon = regs + sfb->variant.keycon;

		keycon0_data = ~(WxKEYCON0_KEYBL_EN |
				WxKEYCON0_KEYEN_F |
				WxKEYCON0_सूचीCON) | WxKEYCON0_COMPKEY(0);

		keycon1_data = WxKEYCON1_COLVAL(0xffffff);

		keycon += (win_no - 1) * 8;

		ग_लिखोl(keycon0_data, keycon + WKEYCON0);
		ग_लिखोl(keycon1_data, keycon + WKEYCON1);
	पूर्ण

	ग_लिखोl(data, regs + sfb->variant.wincon + (win_no * 4));
	ग_लिखोl(0x0, regs + sfb->variant.winmap + (win_no * 4));

	/* Set alpha value width */
	अगर (sfb->variant.has_blendcon) अणु
		data = पढ़ोl(sfb->regs + BLENDCON);
		data &= ~BLENDCON_NEW_MASK;
		अगर (var->transp.length > 4)
			data |= BLENDCON_NEW_8BIT_ALPHA_VALUE;
		अन्यथा
			data |= BLENDCON_NEW_4BIT_ALPHA_VALUE;
		ग_लिखोl(data, sfb->regs + BLENDCON);
	पूर्ण

	shaकरोw_protect_win(win, 0);

	pm_runसमय_put_sync(sfb->dev);

	वापस 0;
पूर्ण

/**
 * s3c_fb_update_palette() - set or schedule a palette update.
 * @sfb: The hardware inक्रमmation.
 * @win: The winकरोw being updated.
 * @reg: The palette index being changed.
 * @value: The computed palette value.
 *
 * Change the value of a palette रेजिस्टर, either by directly writing to
 * the palette (this requires the palette RAM to be disconnected from the
 * hardware whilst this is in progress) or schedule the update क्रम later.
 *
 * At the moment, since we have no VSYNC पूर्णांकerrupt support, we simply set
 * the palette entry directly.
 */
अटल व्योम s3c_fb_update_palette(काष्ठा s3c_fb *sfb,
				  काष्ठा s3c_fb_win *win,
				  अचिन्हित पूर्णांक reg,
				  u32 value)
अणु
	व्योम __iomem *palreg;
	u32 palcon;

	palreg = sfb->regs + sfb->variant.palette[win->index];

	dev_dbg(sfb->dev, "%s: win %d, reg %d (%p): %08x\n",
		__func__, win->index, reg, palreg, value);

	win->palette_buffer[reg] = value;

	palcon = पढ़ोl(sfb->regs + WPALCON);
	ग_लिखोl(palcon | WPALCON_PAL_UPDATE, sfb->regs + WPALCON);

	अगर (win->variant.palette_16bpp)
		ग_लिखोw(value, palreg + (reg * 2));
	अन्यथा
		ग_लिखोl(value, palreg + (reg * 4));

	ग_लिखोl(palcon, sfb->regs + WPALCON);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक chan_to_field(अचिन्हित पूर्णांक chan,
					 काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

/**
 * s3c_fb_setcolreg() - framebuffer layer request to change palette.
 * @regno: The palette index to change.
 * @red: The red field क्रम the palette data.
 * @green: The green field क्रम the palette data.
 * @blue: The blue field क्रम the palette data.
 * @transp: The transparency (alpha) field क्रम the palette data.
 * @info: The framebuffer being changed.
 */
अटल पूर्णांक s3c_fb_setcolreg(अचिन्हित regno,
			    अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			    अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा s3c_fb_win *win = info->par;
	काष्ठा s3c_fb *sfb = win->parent;
	अचिन्हित पूर्णांक val;

	dev_dbg(sfb->dev, "%s: win %d: %d => rgb=%d/%d/%d\n",
		__func__, win->index, regno, red, green, blue);

	pm_runसमय_get_sync(sfb->dev);

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		/* true-colour, use pseuकरो-palette */

		अगर (regno < 16) अणु
			u32 *pal = info->pseuकरो_palette;

			val  = chan_to_field(red,   &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue,  &info->var.blue);

			pal[regno] = val;
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_PSEUDOCOLOR:
		अगर (regno < win->variant.palette_sz) अणु
			val  = chan_to_field(red, &win->palette.r);
			val |= chan_to_field(green, &win->palette.g);
			val |= chan_to_field(blue, &win->palette.b);

			s3c_fb_update_palette(sfb, win, regno, val);
		पूर्ण

		अवरोध;

	शेष:
		pm_runसमय_put_sync(sfb->dev);
		वापस 1;	/* unknown type */
	पूर्ण

	pm_runसमय_put_sync(sfb->dev);
	वापस 0;
पूर्ण

/**
 * s3c_fb_blank() - blank or unblank the given winकरोw
 * @blank_mode: The blank state from FB_BLANK_*
 * @info: The framebuffer to blank.
 *
 * Framebuffer layer request to change the घातer state.
 */
अटल पूर्णांक s3c_fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा s3c_fb_win *win = info->par;
	काष्ठा s3c_fb *sfb = win->parent;
	अचिन्हित पूर्णांक index = win->index;
	u32 wincon;
	u32 output_on = sfb->output_on;

	dev_dbg(sfb->dev, "blank mode %d\n", blank_mode);

	pm_runसमय_get_sync(sfb->dev);

	wincon = पढ़ोl(sfb->regs + sfb->variant.wincon + (index * 4));

	चयन (blank_mode) अणु
	हाल FB_BLANK_POWERDOWN:
		wincon &= ~WINCONx_ENWIN;
		sfb->enabled &= ~(1 << index);
		fallthrough;	/* to FB_BLANK_NORMAL */

	हाल FB_BLANK_NORMAL:
		/* disable the DMA and display 0x0 (black) */
		shaकरोw_protect_win(win, 1);
		ग_लिखोl(WINxMAP_MAP | WINxMAP_MAP_COLOUR(0x0),
		       sfb->regs + sfb->variant.winmap + (index * 4));
		shaकरोw_protect_win(win, 0);
		अवरोध;

	हाल FB_BLANK_UNBLANK:
		shaकरोw_protect_win(win, 1);
		ग_लिखोl(0x0, sfb->regs + sfb->variant.winmap + (index * 4));
		shaकरोw_protect_win(win, 0);
		wincon |= WINCONx_ENWIN;
		sfb->enabled |= (1 << index);
		अवरोध;

	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	शेष:
		pm_runसमय_put_sync(sfb->dev);
		वापस 1;
	पूर्ण

	shaकरोw_protect_win(win, 1);
	ग_लिखोl(wincon, sfb->regs + sfb->variant.wincon + (index * 4));

	/* Check the enabled state to see अगर we need to be running the
	 * मुख्य LCD पूर्णांकerface, as अगर there are no active winकरोws then
	 * it is highly likely that we also करो not need to output
	 * anything.
	 */
	s3c_fb_enable(sfb, sfb->enabled ? 1 : 0);
	shaकरोw_protect_win(win, 0);

	pm_runसमय_put_sync(sfb->dev);

	वापस output_on == sfb->output_on;
पूर्ण

/**
 * s3c_fb_pan_display() - Pan the display.
 *
 * Note that the offsets can be written to the device at any समय, as their
 * values are latched at each vsync स्वतःmatically. This also means that only
 * the last call to this function will have any effect on next vsync, but
 * there is no need to sleep रुकोing क्रम it to prevent tearing.
 *
 * @var: The screen inक्रमmation to verअगरy.
 * @info: The framebuffer device.
 */
अटल पूर्णांक s3c_fb_pan_display(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा s3c_fb_win *win	= info->par;
	काष्ठा s3c_fb *sfb	= win->parent;
	व्योम __iomem *buf	= sfb->regs + win->index * 8;
	अचिन्हित पूर्णांक start_boff, end_boff;

	pm_runसमय_get_sync(sfb->dev);

	/* Offset in bytes to the start of the displayed area */
	start_boff = var->yoffset * info->fix.line_length;
	/* X offset depends on the current bpp */
	अगर (info->var.bits_per_pixel >= 8) अणु
		start_boff += var->xoffset * (info->var.bits_per_pixel >> 3);
	पूर्ण अन्यथा अणु
		चयन (info->var.bits_per_pixel) अणु
		हाल 4:
			start_boff += var->xoffset >> 1;
			अवरोध;
		हाल 2:
			start_boff += var->xoffset >> 2;
			अवरोध;
		हाल 1:
			start_boff += var->xoffset >> 3;
			अवरोध;
		शेष:
			dev_err(sfb->dev, "invalid bpp\n");
			pm_runसमय_put_sync(sfb->dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* Offset in bytes to the end of the displayed area */
	end_boff = start_boff + info->var.yres * info->fix.line_length;

	/* Temporarily turn off per-vsync update from shaकरोw रेजिस्टरs until
	 * both start and end addresses are updated to prevent corruption */
	shaकरोw_protect_win(win, 1);

	ग_लिखोl(info->fix.smem_start + start_boff, buf + sfb->variant.buf_start);
	ग_लिखोl(info->fix.smem_start + end_boff, buf + sfb->variant.buf_end);

	shaकरोw_protect_win(win, 0);

	pm_runसमय_put_sync(sfb->dev);
	वापस 0;
पूर्ण

/**
 * s3c_fb_enable_irq() - enable framebuffer पूर्णांकerrupts
 * @sfb: मुख्य hardware state
 */
अटल व्योम s3c_fb_enable_irq(काष्ठा s3c_fb *sfb)
अणु
	व्योम __iomem *regs = sfb->regs;
	u32 irq_ctrl_reg;

	अगर (!test_and_set_bit(S3C_FB_VSYNC_IRQ_EN, &sfb->irq_flags)) अणु
		/* IRQ disabled, enable it */
		irq_ctrl_reg = पढ़ोl(regs + VIDINTCON0);

		irq_ctrl_reg |= VIDINTCON0_INT_ENABLE;
		irq_ctrl_reg |= VIDINTCON0_INT_FRAME;

		irq_ctrl_reg &= ~VIDINTCON0_FRAMESEL0_MASK;
		irq_ctrl_reg |= VIDINTCON0_FRAMESEL0_VSYNC;
		irq_ctrl_reg &= ~VIDINTCON0_FRAMESEL1_MASK;
		irq_ctrl_reg |= VIDINTCON0_FRAMESEL1_NONE;

		ग_लिखोl(irq_ctrl_reg, regs + VIDINTCON0);
	पूर्ण
पूर्ण

/**
 * s3c_fb_disable_irq() - disable framebuffer पूर्णांकerrupts
 * @sfb: मुख्य hardware state
 */
अटल व्योम s3c_fb_disable_irq(काष्ठा s3c_fb *sfb)
अणु
	व्योम __iomem *regs = sfb->regs;
	u32 irq_ctrl_reg;

	अगर (test_and_clear_bit(S3C_FB_VSYNC_IRQ_EN, &sfb->irq_flags)) अणु
		/* IRQ enabled, disable it */
		irq_ctrl_reg = पढ़ोl(regs + VIDINTCON0);

		irq_ctrl_reg &= ~VIDINTCON0_INT_FRAME;
		irq_ctrl_reg &= ~VIDINTCON0_INT_ENABLE;

		ग_लिखोl(irq_ctrl_reg, regs + VIDINTCON0);
	पूर्ण
पूर्ण

अटल irqवापस_t s3c_fb_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा s3c_fb *sfb = dev_id;
	व्योम __iomem  *regs = sfb->regs;
	u32 irq_sts_reg;

	spin_lock(&sfb->slock);

	irq_sts_reg = पढ़ोl(regs + VIDINTCON1);

	अगर (irq_sts_reg & VIDINTCON1_INT_FRAME) अणु

		/* VSYNC पूर्णांकerrupt, accept it */
		ग_लिखोl(VIDINTCON1_INT_FRAME, regs + VIDINTCON1);

		sfb->vsync_info.count++;
		wake_up_पूर्णांकerruptible(&sfb->vsync_info.रुको);
	पूर्ण

	/* We only support रुकोing क्रम VSYNC क्रम now, so it's safe
	 * to always disable irqs here.
	 */
	s3c_fb_disable_irq(sfb);

	spin_unlock(&sfb->slock);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * s3c_fb_रुको_क्रम_vsync() - sleep until next VSYNC पूर्णांकerrupt or समयout
 * @sfb: मुख्य hardware state
 * @crtc: head index.
 */
अटल पूर्णांक s3c_fb_रुको_क्रम_vsync(काष्ठा s3c_fb *sfb, u32 crtc)
अणु
	अचिन्हित दीर्घ count;
	पूर्णांक ret;

	अगर (crtc != 0)
		वापस -ENODEV;

	pm_runसमय_get_sync(sfb->dev);

	count = sfb->vsync_info.count;
	s3c_fb_enable_irq(sfb);
	ret = रुको_event_पूर्णांकerruptible_समयout(sfb->vsync_info.रुको,
				       count != sfb->vsync_info.count,
				       msecs_to_jअगरfies(VSYNC_TIMEOUT_MSEC));

	pm_runसमय_put_sync(sfb->dev);

	अगर (ret == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_fb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा s3c_fb_win *win = info->par;
	काष्ठा s3c_fb *sfb = win->parent;
	पूर्णांक ret;
	u32 crtc;

	चयन (cmd) अणु
	हाल FBIO_WAITFORVSYNC:
		अगर (get_user(crtc, (u32 __user *)arg)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret = s3c_fb_रुको_क्रम_vsync(sfb, crtc);
		अवरोध;
	शेष:
		ret = -ENOTTY;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fb_ops s3c_fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= s3c_fb_check_var,
	.fb_set_par	= s3c_fb_set_par,
	.fb_blank	= s3c_fb_blank,
	.fb_setcolreg	= s3c_fb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_pan_display	= s3c_fb_pan_display,
	.fb_ioctl	= s3c_fb_ioctl,
पूर्ण;

/**
 * s3c_fb_missing_pixघड़ी() - calculates pixel घड़ी
 * @mode: The video mode to change.
 *
 * Calculate the pixel घड़ी when none has been given through platक्रमm data.
 */
अटल व्योम s3c_fb_missing_pixघड़ी(काष्ठा fb_videomode *mode)
अणु
	u64 pixclk = 1000000000000ULL;
	u32 भाग;

	भाग  = mode->left_margin + mode->hsync_len + mode->right_margin +
	       mode->xres;
	भाग *= mode->upper_margin + mode->vsync_len + mode->lower_margin +
	       mode->yres;
	भाग *= mode->refresh ? : 60;

	करो_भाग(pixclk, भाग);

	mode->pixघड़ी = pixclk;
पूर्ण

/**
 * s3c_fb_alloc_memory() - allocate display memory क्रम framebuffer winकरोw
 * @sfb: The base resources क्रम the hardware.
 * @win: The winकरोw to initialise memory क्रम.
 *
 * Allocate memory क्रम the given framebuffer.
 */
अटल पूर्णांक s3c_fb_alloc_memory(काष्ठा s3c_fb *sfb, काष्ठा s3c_fb_win *win)
अणु
	काष्ठा s3c_fb_pd_win *windata = win->windata;
	अचिन्हित पूर्णांक real_size, virt_size, size;
	काष्ठा fb_info *fbi = win->fbinfo;
	dma_addr_t map_dma;

	dev_dbg(sfb->dev, "allocating memory for display\n");

	real_size = windata->xres * windata->yres;
	virt_size = windata->भव_x * windata->भव_y;

	dev_dbg(sfb->dev, "real_size=%u (%u.%u), virt_size=%u (%u.%u)\n",
		real_size, windata->xres, windata->yres,
		virt_size, windata->भव_x, windata->भव_y);

	size = (real_size > virt_size) ? real_size : virt_size;
	size *= (windata->max_bpp > 16) ? 32 : windata->max_bpp;
	size /= 8;

	fbi->fix.smem_len = size;
	size = PAGE_ALIGN(size);

	dev_dbg(sfb->dev, "want %u bytes for window\n", size);

	fbi->screen_buffer = dma_alloc_wc(sfb->dev, size, &map_dma, GFP_KERNEL);
	अगर (!fbi->screen_buffer)
		वापस -ENOMEM;

	dev_dbg(sfb->dev, "mapped %x to %p\n",
		(अचिन्हित पूर्णांक)map_dma, fbi->screen_buffer);

	स_रखो(fbi->screen_buffer, 0x0, size);
	fbi->fix.smem_start = map_dma;

	वापस 0;
पूर्ण

/**
 * s3c_fb_मुक्त_memory() - मुक्त the display memory क्रम the given winकरोw
 * @sfb: The base resources क्रम the hardware.
 * @win: The winकरोw to मुक्त the display memory क्रम.
 *
 * Free the display memory allocated by s3c_fb_alloc_memory().
 */
अटल व्योम s3c_fb_मुक्त_memory(काष्ठा s3c_fb *sfb, काष्ठा s3c_fb_win *win)
अणु
	काष्ठा fb_info *fbi = win->fbinfo;

	अगर (fbi->screen_buffer)
		dma_मुक्त_wc(sfb->dev, PAGE_ALIGN(fbi->fix.smem_len),
			    fbi->screen_buffer, fbi->fix.smem_start);
पूर्ण

/**
 * s3c_fb_release_win() - release resources क्रम a framebuffer winकरोw.
 * @sfb: The base resources क्रम the hardware.
 * @win: The winकरोw to cleanup the resources क्रम.
 *
 * Release the resources that where claimed क्रम the hardware winकरोw,
 * such as the framebuffer instance and any memory claimed क्रम it.
 */
अटल व्योम s3c_fb_release_win(काष्ठा s3c_fb *sfb, काष्ठा s3c_fb_win *win)
अणु
	u32 data;

	अगर (win->fbinfo) अणु
		अगर (sfb->variant.has_shaकरोwcon) अणु
			data = पढ़ोl(sfb->regs + SHADOWCON);
			data &= ~SHADOWCON_CHx_ENABLE(win->index);
			data &= ~SHADOWCON_CHx_LOCAL_ENABLE(win->index);
			ग_लिखोl(data, sfb->regs + SHADOWCON);
		पूर्ण
		unरेजिस्टर_framebuffer(win->fbinfo);
		अगर (win->fbinfo->cmap.len)
			fb_dealloc_cmap(&win->fbinfo->cmap);
		s3c_fb_मुक्त_memory(sfb, win);
		framebuffer_release(win->fbinfo);
	पूर्ण
पूर्ण

/**
 * s3c_fb_probe_win() - रेजिस्टर an hardware winकरोw
 * @sfb: The base resources क्रम the hardware
 * @win_no: The winकरोw number
 * @variant: The variant inक्रमmation क्रम this winकरोw.
 * @res: Poपूर्णांकer to where to place the resultant winकरोw.
 *
 * Allocate and करो the basic initialisation क्रम one of the hardware's graphics
 * winकरोws.
 */
अटल पूर्णांक s3c_fb_probe_win(काष्ठा s3c_fb *sfb, अचिन्हित पूर्णांक win_no,
			    काष्ठा s3c_fb_win_variant *variant,
			    काष्ठा s3c_fb_win **res)
अणु
	काष्ठा fb_videomode iniपंचांगode;
	काष्ठा s3c_fb_pd_win *windata;
	काष्ठा s3c_fb_win *win;
	काष्ठा fb_info *fbinfo;
	पूर्णांक palette_size;
	पूर्णांक ret;

	dev_dbg(sfb->dev, "probing window %d, variant %p\n", win_no, variant);

	init_रुकोqueue_head(&sfb->vsync_info.रुको);

	palette_size = variant->palette_sz * 4;

	fbinfo = framebuffer_alloc(माप(काष्ठा s3c_fb_win) +
				   palette_size * माप(u32), sfb->dev);
	अगर (!fbinfo)
		वापस -ENOMEM;

	windata = sfb->pdata->win[win_no];
	iniपंचांगode = *sfb->pdata->vtiming;

	WARN_ON(windata->max_bpp == 0);
	WARN_ON(windata->xres == 0);
	WARN_ON(windata->yres == 0);

	win = fbinfo->par;
	*res = win;
	win->variant = *variant;
	win->fbinfo = fbinfo;
	win->parent = sfb;
	win->windata = windata;
	win->index = win_no;
	win->palette_buffer = (u32 *)(win + 1);

	ret = s3c_fb_alloc_memory(sfb, win);
	अगर (ret) अणु
		dev_err(sfb->dev, "failed to allocate display memory\n");
		वापस ret;
	पूर्ण

	/* setup the r/b/g positions क्रम the winकरोw's palette */
	अगर (win->variant.palette_16bpp) अणु
		/* Set RGB 5:6:5 as शेष */
		win->palette.r.offset = 11;
		win->palette.r.length = 5;
		win->palette.g.offset = 5;
		win->palette.g.length = 6;
		win->palette.b.offset = 0;
		win->palette.b.length = 5;

	पूर्ण अन्यथा अणु
		/* Set 8bpp or 8bpp and 1bit alpha */
		win->palette.r.offset = 16;
		win->palette.r.length = 8;
		win->palette.g.offset = 8;
		win->palette.g.length = 8;
		win->palette.b.offset = 0;
		win->palette.b.length = 8;
	पूर्ण

	/* setup the initial video mode from the winकरोw */
	iniपंचांगode.xres = windata->xres;
	iniपंचांगode.yres = windata->yres;
	fb_videomode_to_var(&fbinfo->var, &iniपंचांगode);

	fbinfo->fix.type	= FB_TYPE_PACKED_PIXELS;
	fbinfo->fix.accel	= FB_ACCEL_NONE;
	fbinfo->var.activate	= FB_ACTIVATE_NOW;
	fbinfo->var.vmode	= FB_VMODE_NONINTERLACED;
	fbinfo->var.bits_per_pixel = windata->शेष_bpp;
	fbinfo->fbops		= &s3c_fb_ops;
	fbinfo->flags		= FBINFO_FLAG_DEFAULT;
	fbinfo->pseuकरो_palette  = &win->pseuकरो_palette;

	/* prepare to actually start the framebuffer */

	ret = s3c_fb_check_var(&fbinfo->var, fbinfo);
	अगर (ret < 0) अणु
		dev_err(sfb->dev, "check_var failed on initial video params\n");
		वापस ret;
	पूर्ण

	/* create initial colour map */

	ret = fb_alloc_cmap(&fbinfo->cmap, win->variant.palette_sz, 1);
	अगर (ret == 0)
		fb_set_cmap(&fbinfo->cmap, fbinfo);
	अन्यथा
		dev_err(sfb->dev, "failed to allocate fb cmap\n");

	s3c_fb_set_par(fbinfo);

	dev_dbg(sfb->dev, "about to register framebuffer\n");

	/* run the check_var and set_par on our configuration. */

	ret = रेजिस्टर_framebuffer(fbinfo);
	अगर (ret < 0) अणु
		dev_err(sfb->dev, "failed to register framebuffer\n");
		वापस ret;
	पूर्ण

	dev_info(sfb->dev, "window %d: fb %s\n", win_no, fbinfo->fix.id);

	वापस 0;
पूर्ण

/**
 * s3c_fb_set_rgb_timing() - set video timing क्रम rgb पूर्णांकerface.
 * @sfb: The base resources क्रम the hardware.
 *
 * Set horizontal and vertical lcd rgb पूर्णांकerface timing.
 */
अटल व्योम s3c_fb_set_rgb_timing(काष्ठा s3c_fb *sfb)
अणु
	काष्ठा fb_videomode *vmode = sfb->pdata->vtiming;
	व्योम __iomem *regs = sfb->regs;
	पूर्णांक clkभाग;
	u32 data;

	अगर (!vmode->pixघड़ी)
		s3c_fb_missing_pixघड़ी(vmode);

	clkभाग = s3c_fb_calc_pixclk(sfb, vmode->pixघड़ी);

	data = sfb->pdata->vidcon0;
	data &= ~(VIDCON0_CLKVAL_F_MASK | VIDCON0_CLKसूची);

	अगर (clkभाग > 1)
		data |= VIDCON0_CLKVAL_F(clkभाग-1) | VIDCON0_CLKसूची;
	अन्यथा
		data &= ~VIDCON0_CLKसूची;	/* 1:1 घड़ी */

	अगर (sfb->variant.is_2443)
		data |= (1 << 5);
	ग_लिखोl(data, regs + VIDCON0);

	data = VIDTCON0_VBPD(vmode->upper_margin - 1) |
	       VIDTCON0_VFPD(vmode->lower_margin - 1) |
	       VIDTCON0_VSPW(vmode->vsync_len - 1);
	ग_लिखोl(data, regs + sfb->variant.vidtcon);

	data = VIDTCON1_HBPD(vmode->left_margin - 1) |
	       VIDTCON1_HFPD(vmode->right_margin - 1) |
	       VIDTCON1_HSPW(vmode->hsync_len - 1);
	ग_लिखोl(data, regs + sfb->variant.vidtcon + 4);

	data = VIDTCON2_LINEVAL(vmode->yres - 1) |
	       VIDTCON2_HOZVAL(vmode->xres - 1) |
	       VIDTCON2_LINEVAL_E(vmode->yres - 1) |
	       VIDTCON2_HOZVAL_E(vmode->xres - 1);
	ग_लिखोl(data, regs + sfb->variant.vidtcon + 8);
पूर्ण

/**
 * s3c_fb_clear_win() - clear hardware winकरोw रेजिस्टरs.
 * @sfb: The base resources क्रम the hardware.
 * @win: The winकरोw to process.
 *
 * Reset the specअगरic winकरोw रेजिस्टरs to a known state.
 */
अटल व्योम s3c_fb_clear_win(काष्ठा s3c_fb *sfb, पूर्णांक win)
अणु
	व्योम __iomem *regs = sfb->regs;
	u32 reg;

	ग_लिखोl(0, regs + sfb->variant.wincon + (win * 4));
	ग_लिखोl(0, regs + VIDOSD_A(win, sfb->variant));
	ग_लिखोl(0, regs + VIDOSD_B(win, sfb->variant));
	ग_लिखोl(0, regs + VIDOSD_C(win, sfb->variant));

	अगर (sfb->variant.has_shaकरोwcon) अणु
		reg = पढ़ोl(sfb->regs + SHADOWCON);
		reg &= ~(SHADOWCON_WINx_PROTECT(win) |
			SHADOWCON_CHx_ENABLE(win) |
			SHADOWCON_CHx_LOCAL_ENABLE(win));
		ग_लिखोl(reg, sfb->regs + SHADOWCON);
	पूर्ण
पूर्ण

अटल पूर्णांक s3c_fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *platid;
	काष्ठा s3c_fb_driverdata *fbdrv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा s3c_fb_platdata *pd;
	काष्ठा s3c_fb *sfb;
	काष्ठा resource *res;
	पूर्णांक win;
	पूर्णांक ret = 0;
	u32 reg;

	platid = platक्रमm_get_device_id(pdev);
	fbdrv = (काष्ठा s3c_fb_driverdata *)platid->driver_data;

	अगर (fbdrv->variant.nr_winकरोws > S3C_FB_MAX_WIN) अणु
		dev_err(dev, "too many windows, cannot attach\n");
		वापस -EINVAL;
	पूर्ण

	pd = dev_get_platdata(&pdev->dev);
	अगर (!pd) अणु
		dev_err(dev, "no platform data specified\n");
		वापस -EINVAL;
	पूर्ण

	sfb = devm_kzalloc(dev, माप(*sfb), GFP_KERNEL);
	अगर (!sfb)
		वापस -ENOMEM;

	dev_dbg(dev, "allocate new framebuffer %p\n", sfb);

	sfb->dev = dev;
	sfb->pdata = pd;
	sfb->variant = fbdrv->variant;

	spin_lock_init(&sfb->slock);

	sfb->bus_clk = devm_clk_get(dev, "lcd");
	अगर (IS_ERR(sfb->bus_clk)) अणु
		dev_err(dev, "failed to get bus clock\n");
		वापस PTR_ERR(sfb->bus_clk);
	पूर्ण

	clk_prepare_enable(sfb->bus_clk);

	अगर (!sfb->variant.has_clksel) अणु
		sfb->lcd_clk = devm_clk_get(dev, "sclk_fimd");
		अगर (IS_ERR(sfb->lcd_clk)) अणु
			dev_err(dev, "failed to get lcd clock\n");
			ret = PTR_ERR(sfb->lcd_clk);
			जाओ err_bus_clk;
		पूर्ण

		clk_prepare_enable(sfb->lcd_clk);
	पूर्ण

	pm_runसमय_enable(sfb->dev);

	sfb->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sfb->regs)) अणु
		ret = PTR_ERR(sfb->regs);
		जाओ err_lcd_clk;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(dev, "failed to acquire irq resource\n");
		ret = -ENOENT;
		जाओ err_lcd_clk;
	पूर्ण
	sfb->irq_no = res->start;
	ret = devm_request_irq(dev, sfb->irq_no, s3c_fb_irq,
			  0, "s3c_fb", sfb);
	अगर (ret) अणु
		dev_err(dev, "irq request failed\n");
		जाओ err_lcd_clk;
	पूर्ण

	dev_dbg(dev, "got resources (regs %p), probing windows\n", sfb->regs);

	platक्रमm_set_drvdata(pdev, sfb);
	pm_runसमय_get_sync(sfb->dev);

	/* setup gpio and output polarity controls */

	pd->setup_gpio();

	ग_लिखोl(pd->vidcon1, sfb->regs + VIDCON1);

	/* set video घड़ी running at under-run */
	अगर (sfb->variant.has_fixvclk) अणु
		reg = पढ़ोl(sfb->regs + VIDCON1);
		reg &= ~VIDCON1_VCLK_MASK;
		reg |= VIDCON1_VCLK_RUN;
		ग_लिखोl(reg, sfb->regs + VIDCON1);
	पूर्ण

	/* zero all winकरोws beक्रमe we करो anything */

	क्रम (win = 0; win < fbdrv->variant.nr_winकरोws; win++)
		s3c_fb_clear_win(sfb, win);

	/* initialise colour key controls */
	क्रम (win = 0; win < (fbdrv->variant.nr_winकरोws - 1); win++) अणु
		व्योम __iomem *regs = sfb->regs + sfb->variant.keycon;

		regs += (win * 8);
		ग_लिखोl(0xffffff, regs + WKEYCON0);
		ग_लिखोl(0xffffff, regs + WKEYCON1);
	पूर्ण

	s3c_fb_set_rgb_timing(sfb);

	/* we have the रेजिस्टर setup, start allocating framebuffers */

	क्रम (win = 0; win < fbdrv->variant.nr_winकरोws; win++) अणु
		अगर (!pd->win[win])
			जारी;

		ret = s3c_fb_probe_win(sfb, win, fbdrv->win[win],
				       &sfb->winकरोws[win]);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to create window %d\n", win);
			क्रम (; win >= 0; win--)
				s3c_fb_release_win(sfb, sfb->winकरोws[win]);
			जाओ err_pm_runसमय;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, sfb);
	pm_runसमय_put_sync(sfb->dev);

	वापस 0;

err_pm_runसमय:
	pm_runसमय_put_sync(sfb->dev);

err_lcd_clk:
	pm_runसमय_disable(sfb->dev);

	अगर (!sfb->variant.has_clksel)
		clk_disable_unprepare(sfb->lcd_clk);

err_bus_clk:
	clk_disable_unprepare(sfb->bus_clk);

	वापस ret;
पूर्ण

/**
 * s3c_fb_हटाओ() - Cleanup on module finalisation
 * @pdev: The platक्रमm device we are bound to.
 *
 * Shutकरोwn and then release all the resources that the driver allocated
 * on initialisation.
 */
अटल पूर्णांक s3c_fb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_fb *sfb = platक्रमm_get_drvdata(pdev);
	पूर्णांक win;

	pm_runसमय_get_sync(sfb->dev);

	क्रम (win = 0; win < S3C_FB_MAX_WIN; win++)
		अगर (sfb->winकरोws[win])
			s3c_fb_release_win(sfb, sfb->winकरोws[win]);

	अगर (!sfb->variant.has_clksel)
		clk_disable_unprepare(sfb->lcd_clk);

	clk_disable_unprepare(sfb->bus_clk);

	pm_runसमय_put_sync(sfb->dev);
	pm_runसमय_disable(sfb->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक s3c_fb_suspend(काष्ठा device *dev)
अणु
	काष्ठा s3c_fb *sfb = dev_get_drvdata(dev);
	काष्ठा s3c_fb_win *win;
	पूर्णांक win_no;

	pm_runसमय_get_sync(sfb->dev);

	क्रम (win_no = S3C_FB_MAX_WIN - 1; win_no >= 0; win_no--) अणु
		win = sfb->winकरोws[win_no];
		अगर (!win)
			जारी;

		/* use the blank function to push पूर्णांकo घातer-करोwn */
		s3c_fb_blank(FB_BLANK_POWERDOWN, win->fbinfo);
	पूर्ण

	अगर (!sfb->variant.has_clksel)
		clk_disable_unprepare(sfb->lcd_clk);

	clk_disable_unprepare(sfb->bus_clk);

	pm_runसमय_put_sync(sfb->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_fb_resume(काष्ठा device *dev)
अणु
	काष्ठा s3c_fb *sfb = dev_get_drvdata(dev);
	काष्ठा s3c_fb_platdata *pd = sfb->pdata;
	काष्ठा s3c_fb_win *win;
	पूर्णांक win_no;
	u32 reg;

	pm_runसमय_get_sync(sfb->dev);

	clk_prepare_enable(sfb->bus_clk);

	अगर (!sfb->variant.has_clksel)
		clk_prepare_enable(sfb->lcd_clk);

	/* setup gpio and output polarity controls */
	pd->setup_gpio();
	ग_लिखोl(pd->vidcon1, sfb->regs + VIDCON1);

	/* set video घड़ी running at under-run */
	अगर (sfb->variant.has_fixvclk) अणु
		reg = पढ़ोl(sfb->regs + VIDCON1);
		reg &= ~VIDCON1_VCLK_MASK;
		reg |= VIDCON1_VCLK_RUN;
		ग_लिखोl(reg, sfb->regs + VIDCON1);
	पूर्ण

	/* zero all winकरोws beक्रमe we करो anything */
	क्रम (win_no = 0; win_no < sfb->variant.nr_winकरोws; win_no++)
		s3c_fb_clear_win(sfb, win_no);

	क्रम (win_no = 0; win_no < sfb->variant.nr_winकरोws - 1; win_no++) अणु
		व्योम __iomem *regs = sfb->regs + sfb->variant.keycon;
		win = sfb->winकरोws[win_no];
		अगर (!win)
			जारी;

		shaकरोw_protect_win(win, 1);
		regs += (win_no * 8);
		ग_लिखोl(0xffffff, regs + WKEYCON0);
		ग_लिखोl(0xffffff, regs + WKEYCON1);
		shaकरोw_protect_win(win, 0);
	पूर्ण

	s3c_fb_set_rgb_timing(sfb);

	/* restore framebuffers */
	क्रम (win_no = 0; win_no < S3C_FB_MAX_WIN; win_no++) अणु
		win = sfb->winकरोws[win_no];
		अगर (!win)
			जारी;

		dev_dbg(dev, "resuming window %d\n", win_no);
		s3c_fb_set_par(win->fbinfo);
	पूर्ण

	pm_runसमय_put_sync(sfb->dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s3c_fb_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा s3c_fb *sfb = dev_get_drvdata(dev);

	अगर (!sfb->variant.has_clksel)
		clk_disable_unprepare(sfb->lcd_clk);

	clk_disable_unprepare(sfb->bus_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_fb_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा s3c_fb *sfb = dev_get_drvdata(dev);
	काष्ठा s3c_fb_platdata *pd = sfb->pdata;

	clk_prepare_enable(sfb->bus_clk);

	अगर (!sfb->variant.has_clksel)
		clk_prepare_enable(sfb->lcd_clk);

	/* setup gpio and output polarity controls */
	pd->setup_gpio();
	ग_लिखोl(pd->vidcon1, sfb->regs + VIDCON1);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा VALID_BPP124 (VALID_BPP(1) | VALID_BPP(2) | VALID_BPP(4))
#घोषणा VALID_BPP1248 (VALID_BPP124 | VALID_BPP(8))

अटल काष्ठा s3c_fb_win_variant s3c_fb_data_64xx_wins[] = अणु
	[0] = अणु
		.has_osd_c	= 1,
		.osd_size_off	= 0x8,
		.palette_sz	= 256,
		.valid_bpp	= (VALID_BPP1248 | VALID_BPP(16) |
				   VALID_BPP(18) | VALID_BPP(24)),
	पूर्ण,
	[1] = अणु
		.has_osd_c	= 1,
		.has_osd_d	= 1,
		.osd_size_off	= 0xc,
		.has_osd_alpha	= 1,
		.palette_sz	= 256,
		.valid_bpp	= (VALID_BPP1248 | VALID_BPP(16) |
				   VALID_BPP(18) | VALID_BPP(19) |
				   VALID_BPP(24) | VALID_BPP(25) |
				   VALID_BPP(28)),
	पूर्ण,
	[2] = अणु
		.has_osd_c	= 1,
		.has_osd_d	= 1,
		.osd_size_off	= 0xc,
		.has_osd_alpha	= 1,
		.palette_sz	= 16,
		.palette_16bpp	= 1,
		.valid_bpp	= (VALID_BPP1248 | VALID_BPP(16) |
				   VALID_BPP(18) | VALID_BPP(19) |
				   VALID_BPP(24) | VALID_BPP(25) |
				   VALID_BPP(28)),
	पूर्ण,
	[3] = अणु
		.has_osd_c	= 1,
		.has_osd_alpha	= 1,
		.palette_sz	= 16,
		.palette_16bpp	= 1,
		.valid_bpp	= (VALID_BPP124  | VALID_BPP(16) |
				   VALID_BPP(18) | VALID_BPP(19) |
				   VALID_BPP(24) | VALID_BPP(25) |
				   VALID_BPP(28)),
	पूर्ण,
	[4] = अणु
		.has_osd_c	= 1,
		.has_osd_alpha	= 1,
		.palette_sz	= 4,
		.palette_16bpp	= 1,
		.valid_bpp	= (VALID_BPP(1) | VALID_BPP(2) |
				   VALID_BPP(16) | VALID_BPP(18) |
				   VALID_BPP(19) | VALID_BPP(24) |
				   VALID_BPP(25) | VALID_BPP(28)),
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c_fb_driverdata s3c_fb_data_64xx = अणु
	.variant = अणु
		.nr_winकरोws	= 5,
		.vidtcon	= VIDTCON0,
		.wincon		= WINCON(0),
		.winmap		= WINxMAP(0),
		.keycon		= WKEYCON,
		.osd		= VIDOSD_BASE,
		.osd_stride	= 16,
		.buf_start	= VIDW_BUF_START(0),
		.buf_size	= VIDW_BUF_SIZE(0),
		.buf_end	= VIDW_BUF_END(0),

		.palette = अणु
			[0] = 0x400,
			[1] = 0x800,
			[2] = 0x300,
			[3] = 0x320,
			[4] = 0x340,
		पूर्ण,

		.has_prtcon	= 1,
		.has_clksel	= 1,
	पूर्ण,
	.win[0]	= &s3c_fb_data_64xx_wins[0],
	.win[1]	= &s3c_fb_data_64xx_wins[1],
	.win[2]	= &s3c_fb_data_64xx_wins[2],
	.win[3]	= &s3c_fb_data_64xx_wins[3],
	.win[4]	= &s3c_fb_data_64xx_wins[4],
पूर्ण;

/* S3C2443/S3C2416 style hardware */
अटल काष्ठा s3c_fb_driverdata s3c_fb_data_s3c2443 = अणु
	.variant = अणु
		.nr_winकरोws	= 2,
		.is_2443	= 1,

		.vidtcon	= 0x08,
		.wincon		= 0x14,
		.winmap		= 0xd0,
		.keycon		= 0xb0,
		.osd		= 0x28,
		.osd_stride	= 12,
		.buf_start	= 0x64,
		.buf_size	= 0x94,
		.buf_end	= 0x7c,

		.palette = अणु
			[0] = 0x400,
			[1] = 0x800,
		पूर्ण,
		.has_clksel	= 1,
	पूर्ण,
	.win[0] = &(काष्ठा s3c_fb_win_variant) अणु
		.palette_sz	= 256,
		.valid_bpp	= VALID_BPP1248 | VALID_BPP(16) | VALID_BPP(24),
	पूर्ण,
	.win[1] = &(काष्ठा s3c_fb_win_variant) अणु
		.has_osd_c	= 1,
		.has_osd_alpha	= 1,
		.palette_sz	= 256,
		.valid_bpp	= (VALID_BPP1248 | VALID_BPP(16) |
				   VALID_BPP(18) | VALID_BPP(19) |
				   VALID_BPP(24) | VALID_BPP(25) |
				   VALID_BPP(28)),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id s3c_fb_driver_ids[] = अणु
	अणु
		.name		= "s3c-fb",
		.driver_data	= (अचिन्हित दीर्घ)&s3c_fb_data_64xx,
	पूर्ण, अणु
		.name		= "s3c2443-fb",
		.driver_data	= (अचिन्हित दीर्घ)&s3c_fb_data_s3c2443,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s3c_fb_driver_ids);

अटल स्थिर काष्ठा dev_pm_ops s3cfb_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(s3c_fb_suspend, s3c_fb_resume)
	SET_RUNTIME_PM_OPS(s3c_fb_runसमय_suspend, s3c_fb_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver s3c_fb_driver = अणु
	.probe		= s3c_fb_probe,
	.हटाओ		= s3c_fb_हटाओ,
	.id_table	= s3c_fb_driver_ids,
	.driver		= अणु
		.name	= "s3c-fb",
		.pm	= &s3cfb_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s3c_fb_driver);

MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("Samsung S3C SoC Framebuffer driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s3c-fb");
