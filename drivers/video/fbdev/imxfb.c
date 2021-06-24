<शैली गुरु>
/*
 *  Freescale i.MX Frame Buffer device driver
 *
 *  Copyright (C) 2004 Sascha Hauer, Pengutronix
 *   Based on acornfb.c Copyright (C) Russell King.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Please direct your questions and comments on this driver to the following
 * email address:
 *
 *	linux-arm-kernel@lists.arm.linux.org.uk
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/lcd.h>
#समावेश <linux/math64.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/regulator/consumer.h>

#समावेश <video/of_display_timing.h>
#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <linux/platक्रमm_data/video-imxfb.h>

/*
 * Complain अगर VAR is out of range.
 */
#घोषणा DEBUG_VAR 1

#घोषणा DRIVER_NAME "imx-fb"

#घोषणा LCDC_SSA	0x00

#घोषणा LCDC_SIZE	0x04
#घोषणा SIZE_XMAX(x)	((((x) >> 4) & 0x3f) << 20)

#घोषणा YMAX_MASK_IMX1	0x1ff
#घोषणा YMAX_MASK_IMX21	0x3ff

#घोषणा LCDC_VPW	0x08
#घोषणा VPW_VPW(x)	((x) & 0x3ff)

#घोषणा LCDC_CPOS	0x0C
#घोषणा CPOS_CC1	(1<<31)
#घोषणा CPOS_CC0	(1<<30)
#घोषणा CPOS_OP		(1<<28)
#घोषणा CPOS_CXP(x)	(((x) & 3ff) << 16)

#घोषणा LCDC_LCWHB	0x10
#घोषणा LCWHB_BK_EN	(1<<31)
#घोषणा LCWHB_CW(w)	(((w) & 0x1f) << 24)
#घोषणा LCWHB_CH(h)	(((h) & 0x1f) << 16)
#घोषणा LCWHB_BD(x)	((x) & 0xff)

#घोषणा LCDC_LCHCC	0x14

#घोषणा LCDC_PCR	0x18

#घोषणा LCDC_HCR	0x1C
#घोषणा HCR_H_WIDTH(x)	(((x) & 0x3f) << 26)
#घोषणा HCR_H_WAIT_1(x)	(((x) & 0xff) << 8)
#घोषणा HCR_H_WAIT_2(x)	((x) & 0xff)

#घोषणा LCDC_VCR	0x20
#घोषणा VCR_V_WIDTH(x)	(((x) & 0x3f) << 26)
#घोषणा VCR_V_WAIT_1(x)	(((x) & 0xff) << 8)
#घोषणा VCR_V_WAIT_2(x)	((x) & 0xff)

#घोषणा LCDC_POS	0x24
#घोषणा POS_POS(x)	((x) & 1f)

#घोषणा LCDC_LSCR1	0x28
/* bit fields in imxfb.h */

#घोषणा LCDC_PWMR	0x2C
/* bit fields in imxfb.h */

#घोषणा LCDC_DMACR	0x30
/* bit fields in imxfb.h */

#घोषणा LCDC_RMCR	0x34

#घोषणा RMCR_LCDC_EN_MX1	(1<<1)

#घोषणा RMCR_SELF_REF	(1<<0)

#घोषणा LCDC_LCDICR	0x38
#घोषणा LCDICR_INT_SYN	(1<<2)
#घोषणा LCDICR_INT_CON	(1)

#घोषणा LCDC_LCDISR	0x40
#घोषणा LCDISR_UDR_ERR	(1<<3)
#घोषणा LCDISR_ERR_RES	(1<<2)
#घोषणा LCDISR_खातापूर्ण	(1<<1)
#घोषणा LCDISR_BOF	(1<<0)

#घोषणा IMXFB_LSCR1_DEFAULT 0x00120300

#घोषणा LCDC_LAUSCR	0x80
#घोषणा LAUSCR_AUS_MODE	(1<<31)

/* Used fb-mode. Can be set on kernel command line, thereक्रमe file-अटल. */
अटल स्थिर अक्षर *fb_mode;

/*
 * These are the bitfields क्रम each
 * display depth that we support.
 */
काष्ठा imxfb_rgb अणु
	काष्ठा fb_bitfield	red;
	काष्ठा fb_bitfield	green;
	काष्ठा fb_bitfield	blue;
	काष्ठा fb_bitfield	transp;
पूर्ण;

क्रमागत imxfb_type अणु
	IMX1_FB,
	IMX21_FB,
पूर्ण;

काष्ठा imxfb_info अणु
	काष्ठा platक्रमm_device  *pdev;
	व्योम __iomem		*regs;
	काष्ठा clk		*clk_ipg;
	काष्ठा clk		*clk_ahb;
	काष्ठा clk		*clk_per;
	क्रमागत imxfb_type		devtype;
	bool			enabled;

	/*
	 * These are the addresses we mapped
	 * the framebuffer memory region to.
	 */
	dma_addr_t		map_dma;
	u_पूर्णांक			map_size;

	u_पूर्णांक			palette_size;

	dma_addr_t		dbar1;
	dma_addr_t		dbar2;

	u_पूर्णांक			pcr;
	u_पूर्णांक			lauscr;
	u_पूर्णांक			pwmr;
	u_पूर्णांक			lscr1;
	u_पूर्णांक			dmacr;
	bool			cmap_inverse;
	bool			cmap_अटल;

	काष्ठा imx_fb_videomode *mode;
	पूर्णांक			num_modes;

	काष्ठा regulator	*lcd_pwr;
	पूर्णांक			lcd_pwr_enabled;
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id imxfb_devtype[] = अणु
	अणु
		.name = "imx1-fb",
		.driver_data = IMX1_FB,
	पूर्ण, अणु
		.name = "imx21-fb",
		.driver_data = IMX21_FB,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, imxfb_devtype);

अटल स्थिर काष्ठा of_device_id imxfb_of_dev_id[] = अणु
	अणु
		.compatible = "fsl,imx1-fb",
		.data = &imxfb_devtype[IMX1_FB],
	पूर्ण, अणु
		.compatible = "fsl,imx21-fb",
		.data = &imxfb_devtype[IMX21_FB],
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imxfb_of_dev_id);

अटल अंतरभूत पूर्णांक is_imx1_fb(काष्ठा imxfb_info *fbi)
अणु
	वापस fbi->devtype == IMX1_FB;
पूर्ण

#घोषणा IMX_NAME	"IMX"

/*
 * Minimum X and Y resolutions
 */
#घोषणा MIN_XRES	64
#घोषणा MIN_YRES	64

/* Actually this really is 18bit support, the lowest 2 bits of each colour
 * are unused in hardware. We claim to have 24bit support to make software
 * like X work, which करोes not support 18bit.
 */
अटल काष्ठा imxfb_rgb def_rgb_18 = अणु
	.red	= अणु.offset = 16, .length = 8,पूर्ण,
	.green	= अणु.offset = 8, .length = 8,पूर्ण,
	.blue	= अणु.offset = 0, .length = 8,पूर्ण,
	.transp = अणु.offset = 0, .length = 0,पूर्ण,
पूर्ण;

अटल काष्ठा imxfb_rgb def_rgb_16_tft = अणु
	.red	= अणु.offset = 11, .length = 5,पूर्ण,
	.green	= अणु.offset = 5, .length = 6,पूर्ण,
	.blue	= अणु.offset = 0, .length = 5,पूर्ण,
	.transp = अणु.offset = 0, .length = 0,पूर्ण,
पूर्ण;

अटल काष्ठा imxfb_rgb def_rgb_16_stn = अणु
	.red	= अणु.offset = 8, .length = 4,पूर्ण,
	.green	= अणु.offset = 4, .length = 4,पूर्ण,
	.blue	= अणु.offset = 0, .length = 4,पूर्ण,
	.transp = अणु.offset = 0, .length = 0,पूर्ण,
पूर्ण;

अटल काष्ठा imxfb_rgb def_rgb_8 = अणु
	.red	= अणु.offset = 0, .length = 8,पूर्ण,
	.green	= अणु.offset = 0, .length = 8,पूर्ण,
	.blue	= अणु.offset = 0, .length = 8,पूर्ण,
	.transp = अणु.offset = 0, .length = 0,पूर्ण,
पूर्ण;

अटल पूर्णांक imxfb_activate_var(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info);

अटल अंतरभूत u_पूर्णांक chan_to_field(u_पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक imxfb_setpalettereg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		u_पूर्णांक trans, काष्ठा fb_info *info)
अणु
	काष्ठा imxfb_info *fbi = info->par;
	u_पूर्णांक val, ret = 1;

#घोषणा CNVT_TOHW(val,width) ((((val)<<(width))+0x7FFF-(val))>>16)
	अगर (regno < fbi->palette_size) अणु
		val = (CNVT_TOHW(red, 4) << 8) |
		      (CNVT_TOHW(green,4) << 4) |
		      CNVT_TOHW(blue,  4);

		ग_लिखोl(val, fbi->regs + 0x800 + (regno << 2));
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक imxfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		   u_पूर्णांक trans, काष्ठा fb_info *info)
अणु
	काष्ठा imxfb_info *fbi = info->par;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 1;

	/*
	 * If inverse mode was selected, invert all the colours
	 * rather than the रेजिस्टर number.  The रेजिस्टर number
	 * is what you poke पूर्णांकo the framebuffer to produce the
	 * colour you requested.
	 */
	अगर (fbi->cmap_inverse) अणु
		red   = 0xffff - red;
		green = 0xffff - green;
		blue  = 0xffff - blue;
	पूर्ण

	/*
	 * If greyscale is true, then we convert the RGB value
	 * to greyscale no mater what visual we are using.
	 */
	अगर (info->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
					7471 * blue) >> 16;

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		/*
		 * 12 or 16-bit True Colour.  We encode the RGB value
		 * according to the RGB bitfield inक्रमmation.
		 */
		अगर (regno < 16) अणु
			u32 *pal = info->pseuकरो_palette;

			val  = chan_to_field(red, &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue, &info->var.blue);

			pal[regno] = val;
			ret = 0;
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_STATIC_PSEUDOCOLOR:
	हाल FB_VISUAL_PSEUDOCOLOR:
		ret = imxfb_setpalettereg(regno, red, green, blue, trans, info);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा imx_fb_videomode *imxfb_find_mode(काष्ठा imxfb_info *fbi)
अणु
	काष्ठा imx_fb_videomode *m;
	पूर्णांक i;

	अगर (!fb_mode)
		वापस &fbi->mode[0];

	क्रम (i = 0, m = &fbi->mode[0]; i < fbi->num_modes; i++, m++) अणु
		अगर (!म_भेद(m->mode.name, fb_mode))
			वापस m;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 *  imxfb_check_var():
 *    Round up in the following order: bits_per_pixel, xres,
 *    yres, xres_भव, yres_भव, xoffset, yoffset, grayscale,
 *    bitfields, horizontal timing, vertical timing.
 */
अटल पूर्णांक imxfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा imxfb_info *fbi = info->par;
	काष्ठा imxfb_rgb *rgb;
	स्थिर काष्ठा imx_fb_videomode *imxfb_mode;
	अचिन्हित दीर्घ lcd_clk;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	u32 pcr = 0;

	अगर (var->xres < MIN_XRES)
		var->xres = MIN_XRES;
	अगर (var->yres < MIN_YRES)
		var->yres = MIN_YRES;

	imxfb_mode = imxfb_find_mode(fbi);
	अगर (!imxfb_mode)
		वापस -EINVAL;

	var->xres		= imxfb_mode->mode.xres;
	var->yres		= imxfb_mode->mode.yres;
	var->bits_per_pixel	= imxfb_mode->bpp;
	var->pixघड़ी		= imxfb_mode->mode.pixघड़ी;
	var->hsync_len		= imxfb_mode->mode.hsync_len;
	var->left_margin	= imxfb_mode->mode.left_margin;
	var->right_margin	= imxfb_mode->mode.right_margin;
	var->vsync_len		= imxfb_mode->mode.vsync_len;
	var->upper_margin	= imxfb_mode->mode.upper_margin;
	var->lower_margin	= imxfb_mode->mode.lower_margin;
	var->sync		= imxfb_mode->mode.sync;
	var->xres_भव	= max(var->xres_भव, var->xres);
	var->yres_भव	= max(var->yres_भव, var->yres);

	pr_debug("var->bits_per_pixel=%d\n", var->bits_per_pixel);

	lcd_clk = clk_get_rate(fbi->clk_per);

	पंचांगp = var->pixघड़ी * (अचिन्हित दीर्घ दीर्घ)lcd_clk;

	करो_भाग(पंचांगp, 1000000);

	अगर (करो_भाग(पंचांगp, 1000000) > 500000)
		पंचांगp++;

	pcr = (अचिन्हित पूर्णांक)पंचांगp;

	अगर (--pcr > 0x3F) अणु
		pcr = 0x3F;
		prपूर्णांकk(KERN_WARNING "Must limit pixel clock to %luHz\n",
				lcd_clk / pcr);
	पूर्ण

	चयन (var->bits_per_pixel) अणु
	हाल 32:
		pcr |= PCR_BPIX_18;
		rgb = &def_rgb_18;
		अवरोध;
	हाल 16:
	शेष:
		अगर (is_imx1_fb(fbi))
			pcr |= PCR_BPIX_12;
		अन्यथा
			pcr |= PCR_BPIX_16;

		अगर (imxfb_mode->pcr & PCR_TFT)
			rgb = &def_rgb_16_tft;
		अन्यथा
			rgb = &def_rgb_16_stn;
		अवरोध;
	हाल 8:
		pcr |= PCR_BPIX_8;
		rgb = &def_rgb_8;
		अवरोध;
	पूर्ण

	/* add sync polarities */
	pcr |= imxfb_mode->pcr & ~(0x3f | (7 << 25));

	fbi->pcr = pcr;
	/*
	 * The LCDC AUS Mode Control Register करोes not exist on imx1.
	 */
	अगर (!is_imx1_fb(fbi) && imxfb_mode->aus_mode)
		fbi->lauscr = LAUSCR_AUS_MODE;

	/*
	 * Copy the RGB parameters क्रम this display
	 * from the machine specअगरic parameters.
	 */
	var->red    = rgb->red;
	var->green  = rgb->green;
	var->blue   = rgb->blue;
	var->transp = rgb->transp;

	pr_debug("RGBT length = %d:%d:%d:%d\n",
		var->red.length, var->green.length, var->blue.length,
		var->transp.length);

	pr_debug("RGBT offset = %d:%d:%d:%d\n",
		var->red.offset, var->green.offset, var->blue.offset,
		var->transp.offset);

	वापस 0;
पूर्ण

/*
 * imxfb_set_par():
 *	Set the user defined part of the display क्रम the specअगरied console
 */
अटल पूर्णांक imxfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा imxfb_info *fbi = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;

	अगर (var->bits_per_pixel == 16 || var->bits_per_pixel == 32)
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा अगर (!fbi->cmap_अटल)
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा अणु
		/*
		 * Some people have weird ideas about wanting अटल
		 * pseuकरोcolor maps.  I suspect their user space
		 * applications are broken.
		 */
		info->fix.visual = FB_VISUAL_STATIC_PSEUDOCOLOR;
	पूर्ण

	info->fix.line_length = var->xres_भव * var->bits_per_pixel / 8;
	fbi->palette_size = var->bits_per_pixel == 8 ? 256 : 16;

	imxfb_activate_var(var, info);

	वापस 0;
पूर्ण

अटल पूर्णांक imxfb_enable_controller(काष्ठा imxfb_info *fbi)
अणु
	पूर्णांक ret;

	अगर (fbi->enabled)
		वापस 0;

	pr_debug("Enabling LCD controller\n");

	ग_लिखोl(fbi->map_dma, fbi->regs + LCDC_SSA);

	/* panning offset 0 (0 pixel offset)        */
	ग_लिखोl(0x00000000, fbi->regs + LCDC_POS);

	/* disable hardware cursor */
	ग_लिखोl(पढ़ोl(fbi->regs + LCDC_CPOS) & ~(CPOS_CC0 | CPOS_CC1),
		fbi->regs + LCDC_CPOS);

	/*
	 * RMCR_LCDC_EN_MX1 is present on i.MX1 only, but करोesn't hurt
	 * on other SoCs
	 */
	ग_लिखोl(RMCR_LCDC_EN_MX1, fbi->regs + LCDC_RMCR);

	ret = clk_prepare_enable(fbi->clk_ipg);
	अगर (ret)
		जाओ err_enable_ipg;

	ret = clk_prepare_enable(fbi->clk_ahb);
	अगर (ret)
		जाओ err_enable_ahb;

	ret = clk_prepare_enable(fbi->clk_per);
	अगर (ret)
		जाओ err_enable_per;

	fbi->enabled = true;
	वापस 0;

err_enable_per:
	clk_disable_unprepare(fbi->clk_ahb);
err_enable_ahb:
	clk_disable_unprepare(fbi->clk_ipg);
err_enable_ipg:
	ग_लिखोl(0, fbi->regs + LCDC_RMCR);

	वापस ret;
पूर्ण

अटल व्योम imxfb_disable_controller(काष्ठा imxfb_info *fbi)
अणु
	अगर (!fbi->enabled)
		वापस;

	pr_debug("Disabling LCD controller\n");

	clk_disable_unprepare(fbi->clk_per);
	clk_disable_unprepare(fbi->clk_ahb);
	clk_disable_unprepare(fbi->clk_ipg);
	fbi->enabled = false;

	ग_लिखोl(0, fbi->regs + LCDC_RMCR);
पूर्ण

अटल पूर्णांक imxfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा imxfb_info *fbi = info->par;

	pr_debug("imxfb_blank: blank=%d\n", blank);

	चयन (blank) अणु
	हाल FB_BLANK_POWERDOWN:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_NORMAL:
		imxfb_disable_controller(fbi);
		अवरोध;

	हाल FB_BLANK_UNBLANK:
		वापस imxfb_enable_controller(fbi);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops imxfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= imxfb_check_var,
	.fb_set_par	= imxfb_set_par,
	.fb_setcolreg	= imxfb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_blank	= imxfb_blank,
पूर्ण;

/*
 * imxfb_activate_var():
 *	Configures LCD Controller based on entries in var parameter.  Settings are
 *	only written to the controller अगर changes were made.
 */
अटल पूर्णांक imxfb_activate_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा imxfb_info *fbi = info->par;
	u32 ymax_mask = is_imx1_fb(fbi) ? YMAX_MASK_IMX1 : YMAX_MASK_IMX21;

	pr_debug("var: xres=%d hslen=%d lm=%d rm=%d\n",
		var->xres, var->hsync_len,
		var->left_margin, var->right_margin);
	pr_debug("var: yres=%d vslen=%d um=%d bm=%d\n",
		var->yres, var->vsync_len,
		var->upper_margin, var->lower_margin);

#अगर DEBUG_VAR
	अगर (var->xres < 16        || var->xres > 1024)
		prपूर्णांकk(KERN_ERR "%s: invalid xres %d\n",
			info->fix.id, var->xres);
	अगर (var->hsync_len < 1    || var->hsync_len > 64)
		prपूर्णांकk(KERN_ERR "%s: invalid hsync_len %d\n",
			info->fix.id, var->hsync_len);
	अगर (var->left_margin > 255)
		prपूर्णांकk(KERN_ERR "%s: invalid left_margin %d\n",
			info->fix.id, var->left_margin);
	अगर (var->right_margin > 255)
		prपूर्णांकk(KERN_ERR "%s: invalid right_margin %d\n",
			info->fix.id, var->right_margin);
	अगर (var->yres < 1 || var->yres > ymax_mask)
		prपूर्णांकk(KERN_ERR "%s: invalid yres %d\n",
			info->fix.id, var->yres);
	अगर (var->vsync_len > 100)
		prपूर्णांकk(KERN_ERR "%s: invalid vsync_len %d\n",
			info->fix.id, var->vsync_len);
	अगर (var->upper_margin > 63)
		prपूर्णांकk(KERN_ERR "%s: invalid upper_margin %d\n",
			info->fix.id, var->upper_margin);
	अगर (var->lower_margin > 255)
		prपूर्णांकk(KERN_ERR "%s: invalid lower_margin %d\n",
			info->fix.id, var->lower_margin);
#पूर्ण_अगर

	/* physical screen start address	    */
	ग_लिखोl(VPW_VPW(var->xres * var->bits_per_pixel / 8 / 4),
		fbi->regs + LCDC_VPW);

	ग_लिखोl(HCR_H_WIDTH(var->hsync_len - 1) |
		HCR_H_WAIT_1(var->right_margin - 1) |
		HCR_H_WAIT_2(var->left_margin - 3),
		fbi->regs + LCDC_HCR);

	ग_लिखोl(VCR_V_WIDTH(var->vsync_len) |
		VCR_V_WAIT_1(var->lower_margin) |
		VCR_V_WAIT_2(var->upper_margin),
		fbi->regs + LCDC_VCR);

	ग_लिखोl(SIZE_XMAX(var->xres) | (var->yres & ymax_mask),
			fbi->regs + LCDC_SIZE);

	ग_लिखोl(fbi->pcr, fbi->regs + LCDC_PCR);
	अगर (fbi->pwmr)
		ग_लिखोl(fbi->pwmr, fbi->regs + LCDC_PWMR);
	ग_लिखोl(fbi->lscr1, fbi->regs + LCDC_LSCR1);

	/* dmacr = 0 is no valid value, as we need DMA control marks. */
	अगर (fbi->dmacr)
		ग_लिखोl(fbi->dmacr, fbi->regs + LCDC_DMACR);

	अगर (fbi->lauscr)
		ग_लिखोl(fbi->lauscr, fbi->regs + LCDC_LAUSCR);

	वापस 0;
पूर्ण

अटल पूर्णांक imxfb_init_fbinfo(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_fb_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा imxfb_info *fbi = info->par;
	काष्ठा device_node *np;

	pr_debug("%s\n",__func__);

	info->pseuकरो_palette = kदो_स्मृति_array(16, माप(u32), GFP_KERNEL);
	अगर (!info->pseuकरो_palette)
		वापस -ENOMEM;

	स_रखो(fbi, 0, माप(काष्ठा imxfb_info));

	fbi->devtype = pdev->id_entry->driver_data;

	strlcpy(info->fix.id, IMX_NAME, माप(info->fix.id));

	info->fix.type			= FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux		= 0;
	info->fix.xpanstep		= 0;
	info->fix.ypanstep		= 0;
	info->fix.ywrapstep		= 0;
	info->fix.accel			= FB_ACCEL_NONE;

	info->var.nonstd		= 0;
	info->var.activate		= FB_ACTIVATE_NOW;
	info->var.height		= -1;
	info->var.width	= -1;
	info->var.accel_flags		= 0;
	info->var.vmode			= FB_VMODE_NONINTERLACED;

	info->fbops			= &imxfb_ops;
	info->flags			= FBINFO_FLAG_DEFAULT |
					  FBINFO_READS_FAST;
	अगर (pdata) अणु
		fbi->lscr1			= pdata->lscr1;
		fbi->dmacr			= pdata->dmacr;
		fbi->pwmr			= pdata->pwmr;
	पूर्ण अन्यथा अणु
		np = pdev->dev.of_node;
		info->var.grayscale = of_property_पढ़ो_bool(np,
						"cmap-greyscale");
		fbi->cmap_inverse = of_property_पढ़ो_bool(np, "cmap-inverse");
		fbi->cmap_अटल = of_property_पढ़ो_bool(np, "cmap-static");

		fbi->lscr1 = IMXFB_LSCR1_DEFAULT;

		of_property_पढ़ो_u32(np, "fsl,lpccr", &fbi->pwmr);

		of_property_पढ़ो_u32(np, "fsl,lscr1", &fbi->lscr1);

		of_property_पढ़ो_u32(np, "fsl,dmacr", &fbi->dmacr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imxfb_of_पढ़ो_mode(काष्ठा device *dev, काष्ठा device_node *np,
		काष्ठा imx_fb_videomode *imxfb_mode)
अणु
	पूर्णांक ret;
	काष्ठा fb_videomode *of_mode = &imxfb_mode->mode;
	u32 bpp;
	u32 pcr;

	ret = of_property_पढ़ो_string(np, "model", &of_mode->name);
	अगर (ret)
		of_mode->name = शून्य;

	ret = of_get_fb_videomode(np, of_mode, OF_USE_NATIVE_MODE);
	अगर (ret) अणु
		dev_err(dev, "Failed to get videomode from DT\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "bits-per-pixel", &bpp);
	ret |= of_property_पढ़ो_u32(np, "fsl,pcr", &pcr);

	अगर (ret) अणु
		dev_err(dev, "Failed to read bpp and pcr from DT\n");
		वापस -EINVAL;
	पूर्ण

	अगर (bpp < 1 || bpp > 255) अणु
		dev_err(dev, "Bits per pixel have to be between 1 and 255\n");
		वापस -EINVAL;
	पूर्ण

	imxfb_mode->bpp = bpp;
	imxfb_mode->pcr = pcr;

	/*
	 * fsl,aus-mode is optional
	 */
	imxfb_mode->aus_mode = of_property_पढ़ो_bool(np, "fsl,aus-mode");

	वापस 0;
पूर्ण

अटल पूर्णांक imxfb_lcd_check_fb(काष्ठा lcd_device *lcddev, काष्ठा fb_info *fi)
अणु
	काष्ठा imxfb_info *fbi = dev_get_drvdata(&lcddev->dev);

	अगर (!fi || fi->par == fbi)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक imxfb_lcd_get_contrast(काष्ठा lcd_device *lcddev)
अणु
	काष्ठा imxfb_info *fbi = dev_get_drvdata(&lcddev->dev);

	वापस fbi->pwmr & 0xff;
पूर्ण

अटल पूर्णांक imxfb_lcd_set_contrast(काष्ठा lcd_device *lcddev, पूर्णांक contrast)
अणु
	काष्ठा imxfb_info *fbi = dev_get_drvdata(&lcddev->dev);

	अगर (fbi->pwmr && fbi->enabled) अणु
		अगर (contrast > 255)
			contrast = 255;
		अन्यथा अगर (contrast < 0)
			contrast = 0;

		fbi->pwmr &= ~0xff;
		fbi->pwmr |= contrast;

		ग_लिखोl(fbi->pwmr, fbi->regs + LCDC_PWMR);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imxfb_lcd_get_घातer(काष्ठा lcd_device *lcddev)
अणु
	काष्ठा imxfb_info *fbi = dev_get_drvdata(&lcddev->dev);

	अगर (!IS_ERR(fbi->lcd_pwr) &&
	    !regulator_is_enabled(fbi->lcd_pwr))
		वापस FB_BLANK_POWERDOWN;

	वापस FB_BLANK_UNBLANK;
पूर्ण

अटल पूर्णांक imxfb_regulator_set(काष्ठा imxfb_info *fbi, पूर्णांक enable)
अणु
	पूर्णांक ret;

	अगर (enable == fbi->lcd_pwr_enabled)
		वापस 0;

	अगर (enable)
		ret = regulator_enable(fbi->lcd_pwr);
	अन्यथा
		ret = regulator_disable(fbi->lcd_pwr);

	अगर (ret == 0)
		fbi->lcd_pwr_enabled = enable;

	वापस ret;
पूर्ण

अटल पूर्णांक imxfb_lcd_set_घातer(काष्ठा lcd_device *lcddev, पूर्णांक घातer)
अणु
	काष्ठा imxfb_info *fbi = dev_get_drvdata(&lcddev->dev);

	अगर (!IS_ERR(fbi->lcd_pwr))
		वापस imxfb_regulator_set(fbi, घातer == FB_BLANK_UNBLANK);

	वापस 0;
पूर्ण

अटल काष्ठा lcd_ops imxfb_lcd_ops = अणु
	.check_fb	= imxfb_lcd_check_fb,
	.get_contrast	= imxfb_lcd_get_contrast,
	.set_contrast	= imxfb_lcd_set_contrast,
	.get_घातer	= imxfb_lcd_get_घातer,
	.set_घातer	= imxfb_lcd_set_घातer,
पूर्ण;

अटल पूर्णांक imxfb_setup(व्योम)
अणु
	अक्षर *opt, *options = शून्य;

	अगर (fb_get_options("imxfb", &options))
		वापस -ENODEV;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*opt)
			जारी;
		अन्यथा
			fb_mode = opt;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imxfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imxfb_info *fbi;
	काष्ठा lcd_device *lcd;
	काष्ठा fb_info *info;
	काष्ठा imx_fb_platक्रमm_data *pdata;
	काष्ठा resource *res;
	काष्ठा imx_fb_videomode *m;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक ret, i;
	पूर्णांक bytes_per_pixel;

	dev_info(&pdev->dev, "i.MX Framebuffer driver\n");

	ret = imxfb_setup();
	अगर (ret < 0)
		वापस ret;

	of_id = of_match_device(imxfb_of_dev_id, &pdev->dev);
	अगर (of_id)
		pdev->id_entry = of_id->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	pdata = dev_get_platdata(&pdev->dev);

	info = framebuffer_alloc(माप(काष्ठा imxfb_info), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;

	fbi = info->par;

	platक्रमm_set_drvdata(pdev, info);

	ret = imxfb_init_fbinfo(pdev);
	अगर (ret < 0)
		जाओ failed_init;

	अगर (pdata) अणु
		अगर (!fb_mode)
			fb_mode = pdata->mode[0].mode.name;

		fbi->mode = pdata->mode;
		fbi->num_modes = pdata->num_modes;
	पूर्ण अन्यथा अणु
		काष्ठा device_node *display_np;
		fb_mode = शून्य;

		display_np = of_parse_phandle(pdev->dev.of_node, "display", 0);
		अगर (!display_np) अणु
			dev_err(&pdev->dev, "No display defined in devicetree\n");
			ret = -EINVAL;
			जाओ failed_of_parse;
		पूर्ण

		/*
		 * imxfb करोes not support more modes, we choose only the native
		 * mode.
		 */
		fbi->num_modes = 1;

		fbi->mode = devm_kzalloc(&pdev->dev,
				माप(काष्ठा imx_fb_videomode), GFP_KERNEL);
		अगर (!fbi->mode) अणु
			ret = -ENOMEM;
			जाओ failed_of_parse;
		पूर्ण

		ret = imxfb_of_पढ़ो_mode(&pdev->dev, display_np, fbi->mode);
		अगर (ret)
			जाओ failed_of_parse;
	पूर्ण

	/* Calculate maximum bytes used per pixel. In most हालs this should
	 * be the same as m->bpp/8 */
	m = &fbi->mode[0];
	bytes_per_pixel = (m->bpp + 7) / 8;
	क्रम (i = 0; i < fbi->num_modes; i++, m++)
		info->fix.smem_len = max_t(माप_प्रकार, info->fix.smem_len,
				m->mode.xres * m->mode.yres * bytes_per_pixel);

	res = request_mem_region(res->start, resource_size(res),
				DRIVER_NAME);
	अगर (!res) अणु
		ret = -EBUSY;
		जाओ failed_req;
	पूर्ण

	fbi->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(fbi->clk_ipg)) अणु
		ret = PTR_ERR(fbi->clk_ipg);
		जाओ failed_अ_लोlock;
	पूर्ण

	/*
	 * The LCDC controller करोes not have an enable bit. The
	 * controller starts directly when the घड़ीs are enabled.
	 * If the घड़ीs are enabled when the controller is not yet
	 * programmed with proper रेजिस्टर values (enabled at the
	 * bootloader, क्रम example) then it just goes पूर्णांकo some undefined
	 * state.
	 * To aव्योम this issue, let's enable and disable LCDC IPG घड़ी
	 * so that we क्रमce some kind of 'reset' to the LCDC block.
	 */
	ret = clk_prepare_enable(fbi->clk_ipg);
	अगर (ret)
		जाओ failed_अ_लोlock;
	clk_disable_unprepare(fbi->clk_ipg);

	fbi->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(fbi->clk_ahb)) अणु
		ret = PTR_ERR(fbi->clk_ahb);
		जाओ failed_अ_लोlock;
	पूर्ण

	fbi->clk_per = devm_clk_get(&pdev->dev, "per");
	अगर (IS_ERR(fbi->clk_per)) अणु
		ret = PTR_ERR(fbi->clk_per);
		जाओ failed_अ_लोlock;
	पूर्ण

	fbi->regs = ioremap(res->start, resource_size(res));
	अगर (fbi->regs == शून्य) अणु
		dev_err(&pdev->dev, "Cannot map frame buffer registers\n");
		ret = -ENOMEM;
		जाओ failed_ioremap;
	पूर्ण

	fbi->map_size = PAGE_ALIGN(info->fix.smem_len);
	info->screen_buffer = dma_alloc_wc(&pdev->dev, fbi->map_size,
					   &fbi->map_dma, GFP_KERNEL);
	अगर (!info->screen_buffer) अणु
		dev_err(&pdev->dev, "Failed to allocate video RAM: %d\n", ret);
		ret = -ENOMEM;
		जाओ failed_map;
	पूर्ण

	info->fix.smem_start = fbi->map_dma;

	अगर (pdata && pdata->init) अणु
		ret = pdata->init(fbi->pdev);
		अगर (ret)
			जाओ failed_platक्रमm_init;
	पूर्ण


	INIT_LIST_HEAD(&info->modelist);
	क्रम (i = 0; i < fbi->num_modes; i++)
		fb_add_videomode(&fbi->mode[i].mode, &info->modelist);

	/*
	 * This makes sure that our colour bitfield
	 * descriptors are correctly initialised.
	 */
	imxfb_check_var(&info->var, info);

	/*
	 * For modes > 8bpp, the color map is bypassed.
	 * Thereक्रमe, 256 entries are enough.
	 */
	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (ret < 0)
		जाओ failed_cmap;

	imxfb_set_par(info);
	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register framebuffer\n");
		जाओ failed_रेजिस्टर;
	पूर्ण

	fbi->lcd_pwr = devm_regulator_get(&pdev->dev, "lcd");
	अगर (PTR_ERR(fbi->lcd_pwr) == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		जाओ failed_lcd;
	पूर्ण

	lcd = devm_lcd_device_रेजिस्टर(&pdev->dev, "imxfb-lcd", &pdev->dev, fbi,
				       &imxfb_lcd_ops);
	अगर (IS_ERR(lcd)) अणु
		ret = PTR_ERR(lcd);
		जाओ failed_lcd;
	पूर्ण

	lcd->props.max_contrast = 0xff;

	imxfb_enable_controller(fbi);
	fbi->pdev = pdev;

	वापस 0;

failed_lcd:
	unरेजिस्टर_framebuffer(info);

failed_रेजिस्टर:
	fb_dealloc_cmap(&info->cmap);
failed_cmap:
	अगर (pdata && pdata->निकास)
		pdata->निकास(fbi->pdev);
failed_platक्रमm_init:
	dma_मुक्त_wc(&pdev->dev, fbi->map_size, info->screen_buffer,
		    fbi->map_dma);
failed_map:
	iounmap(fbi->regs);
failed_ioremap:
failed_अ_लोlock:
	release_mem_region(res->start, resource_size(res));
failed_req:
failed_of_parse:
	kमुक्त(info->pseuकरो_palette);
failed_init:
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल पूर्णांक imxfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_fb_platक्रमm_data *pdata;
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा imxfb_info *fbi = info->par;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	imxfb_disable_controller(fbi);

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	pdata = dev_get_platdata(&pdev->dev);
	अगर (pdata && pdata->निकास)
		pdata->निकास(fbi->pdev);
	dma_मुक्त_wc(&pdev->dev, fbi->map_size, info->screen_buffer,
		    fbi->map_dma);
	iounmap(fbi->regs);
	release_mem_region(res->start, resource_size(res));
	kमुक्त(info->pseuकरो_palette);
	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imxfb_suspend(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा imxfb_info *fbi = info->par;

	imxfb_disable_controller(fbi);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imxfb_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा imxfb_info *fbi = info->par;

	imxfb_enable_controller(fbi);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(imxfb_pm_ops, imxfb_suspend, imxfb_resume);

अटल काष्ठा platक्रमm_driver imxfb_driver = अणु
	.driver		= अणु
		.name	= DRIVER_NAME,
		.of_match_table = imxfb_of_dev_id,
		.pm	= &imxfb_pm_ops,
	पूर्ण,
	.probe		= imxfb_probe,
	.हटाओ		= imxfb_हटाओ,
	.id_table	= imxfb_devtype,
पूर्ण;
module_platक्रमm_driver(imxfb_driver);

MODULE_DESCRIPTION("Freescale i.MX framebuffer driver");
MODULE_AUTHOR("Sascha Hauer, Pengutronix");
MODULE_LICENSE("GPL");
