<शैली गुरु>
/*
 *  Driver क्रम AT91 LCD Controller
 *
 *  Copyright (C) 2007 Aपंचांगel Corporation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/backlight.h>
#समावेश <linux/gfp.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <video/of_videomode.h>
#समावेश <video/of_display_timing.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <video/videomode.h>

#समावेश <video/aपंचांगel_lcdc.h>

काष्ठा aपंचांगel_lcdfb_config अणु
	bool have_alt_pixघड़ी;
	bool have_hozval;
	bool have_पूर्णांकensity_bit;
पूर्ण;

 /* LCD Controller info data काष्ठाure, stored in device platक्रमm_data */
काष्ठा aपंचांगel_lcdfb_info अणु
	spinlock_t		lock;
	काष्ठा fb_info		*info;
	व्योम __iomem		*mmio;
	पूर्णांक			irq_base;
	काष्ठा work_काष्ठा	task;

	अचिन्हित पूर्णांक		smem_len;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा clk		*bus_clk;
	काष्ठा clk		*lcdc_clk;

	काष्ठा backlight_device	*backlight;
	u8			bl_घातer;
	u8			saved_lcdcon;

	u32			pseuकरो_palette[16];
	bool			have_पूर्णांकensity_bit;

	काष्ठा aपंचांगel_lcdfb_pdata pdata;

	काष्ठा aपंचांगel_lcdfb_config *config;
	काष्ठा regulator	*reg_lcd;
पूर्ण;

काष्ठा aपंचांगel_lcdfb_घातer_ctrl_gpio अणु
	काष्ठा gpio_desc *gpiod;

	काष्ठा list_head list;
पूर्ण;

#घोषणा lcdc_पढ़ोl(sinfo, reg)		__raw_पढ़ोl((sinfo)->mmio+(reg))
#घोषणा lcdc_ग_लिखोl(sinfo, reg, val)	__raw_ग_लिखोl((val), (sinfo)->mmio+(reg))

/* configurable parameters */
#घोषणा ATMEL_LCDC_CVAL_DEFAULT		0xc8
#घोषणा ATMEL_LCDC_DMA_BURST_LEN	8	/* words */
#घोषणा ATMEL_LCDC_FIFO_SIZE		512	/* words */

अटल काष्ठा aपंचांगel_lcdfb_config at91sam9261_config = अणु
	.have_hozval		= true,
	.have_पूर्णांकensity_bit	= true,
पूर्ण;

अटल काष्ठा aपंचांगel_lcdfb_config at91sam9263_config = अणु
	.have_पूर्णांकensity_bit	= true,
पूर्ण;

अटल काष्ठा aपंचांगel_lcdfb_config at91sam9g10_config = अणु
	.have_hozval		= true,
पूर्ण;

अटल काष्ठा aपंचांगel_lcdfb_config at91sam9g45_config = अणु
	.have_alt_pixघड़ी	= true,
पूर्ण;

अटल काष्ठा aपंचांगel_lcdfb_config at91sam9g45es_config = अणु
पूर्ण;

अटल काष्ठा aपंचांगel_lcdfb_config at91sam9rl_config = अणु
	.have_पूर्णांकensity_bit	= true,
पूर्ण;

अटल u32 contrast_ctr = ATMEL_LCDC_PS_DIV8
		| ATMEL_LCDC_POL_POSITIVE
		| ATMEL_LCDC_ENA_PWMENABLE;

#अगर_घोषित CONFIG_BACKLIGHT_ATMEL_LCDC

/* some bl->props field just changed */
अटल पूर्णांक aपंचांगel_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा aपंचांगel_lcdfb_info *sinfo = bl_get_data(bl);
	पूर्णांक			घातer = sinfo->bl_घातer;
	पूर्णांक			brightness = bl->props.brightness;

	/* REVISIT there may be a meaningful dअगरference between
	 * fb_blank and घातer ... there seem to be some हालs
	 * this करोesn't handle correctly.
	 */
	अगर (bl->props.fb_blank != sinfo->bl_घातer)
		घातer = bl->props.fb_blank;
	अन्यथा अगर (bl->props.घातer != sinfo->bl_घातer)
		घातer = bl->props.घातer;

	अगर (brightness < 0 && घातer == FB_BLANK_UNBLANK)
		brightness = lcdc_पढ़ोl(sinfo, ATMEL_LCDC_CONTRAST_VAL);
	अन्यथा अगर (घातer != FB_BLANK_UNBLANK)
		brightness = 0;

	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_CONTRAST_VAL, brightness);
	अगर (contrast_ctr & ATMEL_LCDC_POL_POSITIVE)
		lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_CONTRAST_CTR,
			brightness ? contrast_ctr : 0);
	अन्यथा
		lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_CONTRAST_CTR, contrast_ctr);

	bl->props.fb_blank = bl->props.घातer = sinfo->bl_घातer = घातer;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा aपंचांगel_lcdfb_info *sinfo = bl_get_data(bl);

	वापस lcdc_पढ़ोl(sinfo, ATMEL_LCDC_CONTRAST_VAL);
पूर्ण

अटल स्थिर काष्ठा backlight_ops aपंचांगel_lcdc_bl_ops = अणु
	.update_status = aपंचांगel_bl_update_status,
	.get_brightness = aपंचांगel_bl_get_brightness,
पूर्ण;

अटल व्योम init_backlight(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device	*bl;

	sinfo->bl_घातer = FB_BLANK_UNBLANK;

	अगर (sinfo->backlight)
		वापस;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 0xff;
	bl = backlight_device_रेजिस्टर("backlight", &sinfo->pdev->dev, sinfo,
				       &aपंचांगel_lcdc_bl_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&sinfo->pdev->dev, "error %ld on backlight register\n",
				PTR_ERR(bl));
		वापस;
	पूर्ण
	sinfo->backlight = bl;

	bl->props.घातer = FB_BLANK_UNBLANK;
	bl->props.fb_blank = FB_BLANK_UNBLANK;
	bl->props.brightness = aपंचांगel_bl_get_brightness(bl);
पूर्ण

अटल व्योम निकास_backlight(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	अगर (!sinfo->backlight)
		वापस;

	अगर (sinfo->backlight->ops) अणु
		sinfo->backlight->props.घातer = FB_BLANK_POWERDOWN;
		sinfo->backlight->ops->update_status(sinfo->backlight);
	पूर्ण
	backlight_device_unरेजिस्टर(sinfo->backlight);
पूर्ण

#अन्यथा

अटल व्योम init_backlight(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	dev_warn(&sinfo->pdev->dev, "backlight control is not available\n");
पूर्ण

अटल व्योम निकास_backlight(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
पूर्ण

#पूर्ण_अगर

अटल व्योम init_contrast(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	काष्ठा aपंचांगel_lcdfb_pdata *pdata = &sinfo->pdata;

	/* contrast pwm can be 'inverted' */
	अगर (pdata->lcdcon_pol_negative)
		contrast_ctr &= ~(ATMEL_LCDC_POL_POSITIVE);

	/* have some शेष contrast/backlight settings */
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_CONTRAST_CTR, contrast_ctr);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_CONTRAST_VAL, ATMEL_LCDC_CVAL_DEFAULT);

	अगर (pdata->lcdcon_is_backlight)
		init_backlight(sinfo);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_lcdfb_घातer_control(काष्ठा aपंचांगel_lcdfb_info *sinfo, पूर्णांक on)
अणु
	पूर्णांक ret;
	काष्ठा aपंचांगel_lcdfb_pdata *pdata = &sinfo->pdata;

	अगर (pdata->aपंचांगel_lcdfb_घातer_control)
		pdata->aपंचांगel_lcdfb_घातer_control(pdata, on);
	अन्यथा अगर (sinfo->reg_lcd) अणु
		अगर (on) अणु
			ret = regulator_enable(sinfo->reg_lcd);
			अगर (ret)
				dev_err(&sinfo->pdev->dev,
					"lcd regulator enable failed:	%d\n", ret);
		पूर्ण अन्यथा अणु
			ret = regulator_disable(sinfo->reg_lcd);
			अगर (ret)
				dev_err(&sinfo->pdev->dev,
					"lcd regulator disable failed: %d\n", ret);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा fb_fix_screeninfo aपंचांगel_lcdfb_fix __initस्थिर = अणु
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_TRUECOLOR,
	.xpanstep	= 0,
	.ypanstep	= 1,
	.ywrapstep	= 0,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल अचिन्हित दीर्घ compute_hozval(काष्ठा aपंचांगel_lcdfb_info *sinfo,
							अचिन्हित दीर्घ xres)
अणु
	अचिन्हित दीर्घ lcdcon2;
	अचिन्हित दीर्घ value;

	अगर (!sinfo->config->have_hozval)
		वापस xres;

	lcdcon2 = lcdc_पढ़ोl(sinfo, ATMEL_LCDC_LCDCON2);
	value = xres;
	अगर ((lcdcon2 & ATMEL_LCDC_DISTYPE) != ATMEL_LCDC_DISTYPE_TFT) अणु
		/* STN display */
		अगर ((lcdcon2 & ATMEL_LCDC_DISTYPE) == ATMEL_LCDC_DISTYPE_STNCOLOR) अणु
			value *= 3;
		पूर्ण
		अगर ( (lcdcon2 & ATMEL_LCDC_IFWIDTH) == ATMEL_LCDC_IFWIDTH_4
		   || ( (lcdcon2 & ATMEL_LCDC_IFWIDTH) == ATMEL_LCDC_IFWIDTH_8
		      && (lcdcon2 & ATMEL_LCDC_SCANMOD) == ATMEL_LCDC_SCANMOD_DUAL ))
			value = DIV_ROUND_UP(value, 4);
		अन्यथा
			value = DIV_ROUND_UP(value, 8);
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम aपंचांगel_lcdfb_stop_noरुको(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	काष्ठा aपंचांगel_lcdfb_pdata *pdata = &sinfo->pdata;

	/* Turn off the LCD controller and the DMA controller */
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_PWRCON,
			pdata->guard_समय << ATMEL_LCDC_GUARDT_OFFSET);

	/* Wait क्रम the LCDC core to become idle */
	जबतक (lcdc_पढ़ोl(sinfo, ATMEL_LCDC_PWRCON) & ATMEL_LCDC_BUSY)
		msleep(10);

	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_DMACON, 0);
पूर्ण

अटल व्योम aपंचांगel_lcdfb_stop(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	aपंचांगel_lcdfb_stop_noरुको(sinfo);

	/* Wait क्रम DMA engine to become idle... */
	जबतक (lcdc_पढ़ोl(sinfo, ATMEL_LCDC_DMACON) & ATMEL_LCDC_DMABUSY)
		msleep(10);
पूर्ण

अटल व्योम aपंचांगel_lcdfb_start(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	काष्ठा aपंचांगel_lcdfb_pdata *pdata = &sinfo->pdata;

	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_DMACON, pdata->शेष_dmacon);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_PWRCON,
		(pdata->guard_समय << ATMEL_LCDC_GUARDT_OFFSET)
		| ATMEL_LCDC_PWR);
पूर्ण

अटल व्योम aपंचांगel_lcdfb_update_dma(काष्ठा fb_info *info,
			       काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा aपंचांगel_lcdfb_info *sinfo = info->par;
	काष्ठा fb_fix_screeninfo *fix = &info->fix;
	अचिन्हित दीर्घ dma_addr;

	dma_addr = (fix->smem_start + var->yoffset * fix->line_length
		    + var->xoffset * info->var.bits_per_pixel / 8);

	dma_addr &= ~3UL;

	/* Set framebuffer DMA base address and pixel offset */
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_DMABADDR1, dma_addr);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_lcdfb_मुक्त_video_memory(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	काष्ठा fb_info *info = sinfo->info;

	dma_मुक्त_wc(info->device, info->fix.smem_len, info->screen_base,
		    info->fix.smem_start);
पूर्ण

/**
 *	aपंचांगel_lcdfb_alloc_video_memory - Allocate framebuffer memory
 *	@sinfo: the frame buffer to allocate memory क्रम
 * 	
 * 	This function is called only from the aपंचांगel_lcdfb_probe()
 * 	so no locking by fb_info->mm_lock around smem_len setting is needed.
 */
अटल पूर्णांक aपंचांगel_lcdfb_alloc_video_memory(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	काष्ठा fb_info *info = sinfo->info;
	काष्ठा fb_var_screeninfo *var = &info->var;
	अचिन्हित पूर्णांक smem_len;

	smem_len = (var->xres_भव * var->yres_भव
		    * ((var->bits_per_pixel + 7) / 8));
	info->fix.smem_len = max(smem_len, sinfo->smem_len);

	info->screen_base = dma_alloc_wc(info->device, info->fix.smem_len,
					 (dma_addr_t *)&info->fix.smem_start,
					 GFP_KERNEL);

	अगर (!info->screen_base) अणु
		वापस -ENOMEM;
	पूर्ण

	स_रखो(info->screen_base, 0, info->fix.smem_len);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_videomode *aपंचांगel_lcdfb_choose_mode(काष्ठा fb_var_screeninfo *var,
						     काष्ठा fb_info *info)
अणु
	काष्ठा fb_videomode varfbmode;
	स्थिर काष्ठा fb_videomode *fbmode = शून्य;

	fb_var_to_videomode(&varfbmode, var);
	fbmode = fb_find_nearest_mode(&varfbmode, &info->modelist);
	अगर (fbmode)
		fb_videomode_to_var(var, fbmode);
	वापस fbmode;
पूर्ण


/**
 *      aपंचांगel_lcdfb_check_var - Validates a var passed in.
 *      @var: frame buffer variable screen काष्ठाure
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Checks to see अगर the hardware supports the state requested by
 *	var passed in. This function करोes not alter the hardware
 *	state!!!  This means the data stored in काष्ठा fb_info and
 *	काष्ठा aपंचांगel_lcdfb_info करो not change. This includes the var
 *	inside of काष्ठा fb_info.  Do NOT change these. This function
 *	can be called on its own अगर we पूर्णांकent to only test a mode and
 *	not actually set it. The stuff in modedb.c is a example of
 *	this. If the var passed in is slightly off by what the
 *	hardware can support then we alter the var PASSED in to what
 *	we can करो. If the hardware करोesn't support mode change a
 *	-EINVAL will be वापसed by the upper layers. You करोn't need
 *	to implement this function then. If you hardware करोesn't
 *	support changing the resolution then this function is not
 *	needed. In this हाल the driver would just provide a var that
 *	represents the अटल state the screen is in.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक aपंचांगel_lcdfb_check_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा device *dev = info->device;
	काष्ठा aपंचांगel_lcdfb_info *sinfo = info->par;
	काष्ठा aपंचांगel_lcdfb_pdata *pdata = &sinfo->pdata;
	अचिन्हित दीर्घ clk_value_khz;

	clk_value_khz = clk_get_rate(sinfo->lcdc_clk) / 1000;

	dev_dbg(dev, "%s:\n", __func__);

	अगर (!(var->pixघड़ी && var->bits_per_pixel)) अणु
		/* choose a suitable mode अगर possible */
		अगर (!aपंचांगel_lcdfb_choose_mode(var, info)) अणु
			dev_err(dev, "needed value not specified\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "  resolution: %ux%u\n", var->xres, var->yres);
	dev_dbg(dev, "  pixclk:     %lu KHz\n", PICOS2KHZ(var->pixघड़ी));
	dev_dbg(dev, "  bpp:        %u\n", var->bits_per_pixel);
	dev_dbg(dev, "  clk:        %lu KHz\n", clk_value_khz);

	अगर (PICOS2KHZ(var->pixघड़ी) > clk_value_khz) अणु
		dev_err(dev, "%lu KHz pixel clock is too fast\n", PICOS2KHZ(var->pixघड़ी));
		वापस -EINVAL;
	पूर्ण

	/* Do not allow to have real resoulution larger than भव */
	अगर (var->xres > var->xres_भव)
		var->xres_भव = var->xres;

	अगर (var->yres > var->yres_भव)
		var->yres_भव = var->yres;

	/* Force same alignment क्रम each line */
	var->xres = (var->xres + 3) & ~3UL;
	var->xres_भव = (var->xres_भव + 3) & ~3UL;

	var->red.msb_right = var->green.msb_right = var->blue.msb_right = 0;
	var->transp.msb_right = 0;
	var->transp.offset = var->transp.length = 0;
	var->xoffset = var->yoffset = 0;

	अगर (info->fix.smem_len) अणु
		अचिन्हित पूर्णांक smem_len = (var->xres_भव * var->yres_भव
					 * ((var->bits_per_pixel + 7) / 8));
		अगर (smem_len > info->fix.smem_len) अणु
			dev_err(dev, "Frame buffer is too small (%u) for screen size (need at least %u)\n",
				info->fix.smem_len, smem_len);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Saturate vertical and horizontal timings at maximum values */
	var->vsync_len = min_t(u32, var->vsync_len,
			(ATMEL_LCDC_VPW >> ATMEL_LCDC_VPW_OFFSET) + 1);
	var->upper_margin = min_t(u32, var->upper_margin,
			ATMEL_LCDC_VBP >> ATMEL_LCDC_VBP_OFFSET);
	var->lower_margin = min_t(u32, var->lower_margin,
			ATMEL_LCDC_VFP);
	var->right_margin = min_t(u32, var->right_margin,
			(ATMEL_LCDC_HFP >> ATMEL_LCDC_HFP_OFFSET) + 1);
	var->hsync_len = min_t(u32, var->hsync_len,
			(ATMEL_LCDC_HPW >> ATMEL_LCDC_HPW_OFFSET) + 1);
	var->left_margin = min_t(u32, var->left_margin,
			ATMEL_LCDC_HBP + 1);

	/* Some parameters can't be zero */
	var->vsync_len = max_t(u32, var->vsync_len, 1);
	var->right_margin = max_t(u32, var->right_margin, 1);
	var->hsync_len = max_t(u32, var->hsync_len, 1);
	var->left_margin = max_t(u32, var->left_margin, 1);

	चयन (var->bits_per_pixel) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		var->red.offset = var->green.offset = var->blue.offset = 0;
		var->red.length = var->green.length = var->blue.length
			= var->bits_per_pixel;
		अवरोध;
	हाल 16:
		/* Older SOCs use IBGR:555 rather than BGR:565. */
		अगर (sinfo->config->have_पूर्णांकensity_bit)
			var->green.length = 5;
		अन्यथा
			var->green.length = 6;

		अगर (pdata->lcd_wiring_mode == ATMEL_LCDC_WIRING_RGB) अणु
			/* RGB:5X5 mode */
			var->red.offset = var->green.length + 5;
			var->blue.offset = 0;
		पूर्ण अन्यथा अणु
			/* BGR:5X5 mode */
			var->red.offset = 0;
			var->blue.offset = var->green.length + 5;
		पूर्ण
		var->green.offset = 5;
		var->red.length = var->blue.length = 5;
		अवरोध;
	हाल 32:
		var->transp.offset = 24;
		var->transp.length = 8;
		fallthrough;
	हाल 24:
		अगर (pdata->lcd_wiring_mode == ATMEL_LCDC_WIRING_RGB) अणु
			/* RGB:888 mode */
			var->red.offset = 16;
			var->blue.offset = 0;
		पूर्ण अन्यथा अणु
			/* BGR:888 mode */
			var->red.offset = 0;
			var->blue.offset = 16;
		पूर्ण
		var->green.offset = 8;
		var->red.length = var->green.length = var->blue.length = 8;
		अवरोध;
	शेष:
		dev_err(dev, "color depth %d not supported\n",
					var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * LCD reset sequence
 */
अटल व्योम aपंचांगel_lcdfb_reset(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	might_sleep();

	aपंचांगel_lcdfb_stop(sinfo);
	aपंचांगel_lcdfb_start(sinfo);
पूर्ण

/**
 *      aपंचांगel_lcdfb_set_par - Alters the hardware state.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Using the fb_var_screeninfo in fb_info we set the resolution
 *	of the this particular framebuffer. This function alters the
 *	par AND the fb_fix_screeninfo stored in fb_info. It करोesn't
 *	not alter var in fb_info since we are using that data. This
 *	means we depend on the data in var inside fb_info to be
 *	supported by the hardware.  aपंचांगel_lcdfb_check_var is always called
 *	beक्रमe aपंचांगel_lcdfb_set_par to ensure this.  Again अगर you can't
 *	change the resolution you करोn't need this function.
 *
 */
अटल पूर्णांक aपंचांगel_lcdfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा aपंचांगel_lcdfb_info *sinfo = info->par;
	काष्ठा aपंचांगel_lcdfb_pdata *pdata = &sinfo->pdata;
	अचिन्हित दीर्घ hozval_linesz;
	अचिन्हित दीर्घ value;
	अचिन्हित दीर्घ clk_value_khz;
	अचिन्हित दीर्घ bits_per_line;
	अचिन्हित दीर्घ pix_factor = 2;

	might_sleep();

	dev_dbg(info->device, "%s:\n", __func__);
	dev_dbg(info->device, "  * resolution: %ux%u (%ux%u virtual)\n",
		 info->var.xres, info->var.yres,
		 info->var.xres_भव, info->var.yres_भव);

	aपंचांगel_lcdfb_stop_noरुको(sinfo);

	अगर (info->var.bits_per_pixel == 1)
		info->fix.visual = FB_VISUAL_MONO01;
	अन्यथा अगर (info->var.bits_per_pixel <= 8)
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा
		info->fix.visual = FB_VISUAL_TRUECOLOR;

	bits_per_line = info->var.xres_भव * info->var.bits_per_pixel;
	info->fix.line_length = DIV_ROUND_UP(bits_per_line, 8);

	/* Re-initialize the DMA engine... */
	dev_dbg(info->device, "  * update DMA engine\n");
	aपंचांगel_lcdfb_update_dma(info, &info->var);

	/* ...set frame size and burst length = 8 words (?) */
	value = (info->var.yres * info->var.xres * info->var.bits_per_pixel) / 32;
	value |= ((ATMEL_LCDC_DMA_BURST_LEN - 1) << ATMEL_LCDC_BLENGTH_OFFSET);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_DMAFRMCFG, value);

	/* Now, the LCDC core... */

	/* Set pixel घड़ी */
	अगर (sinfo->config->have_alt_pixघड़ी)
		pix_factor = 1;

	clk_value_khz = clk_get_rate(sinfo->lcdc_clk) / 1000;

	value = DIV_ROUND_UP(clk_value_khz, PICOS2KHZ(info->var.pixघड़ी));

	अगर (value < pix_factor) अणु
		dev_notice(info->device, "Bypassing pixel clock divider\n");
		lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_LCDCON1, ATMEL_LCDC_BYPASS);
	पूर्ण अन्यथा अणु
		value = (value / pix_factor) - 1;
		dev_dbg(info->device, "  * programming CLKVAL = 0x%08lx\n",
				value);
		lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_LCDCON1,
				value << ATMEL_LCDC_CLKVAL_OFFSET);
		info->var.pixघड़ी =
			KHZ2PICOS(clk_value_khz / (pix_factor * (value + 1)));
		dev_dbg(info->device, "  updated pixclk:     %lu KHz\n",
					PICOS2KHZ(info->var.pixघड़ी));
	पूर्ण


	/* Initialize control रेजिस्टर 2 */
	value = pdata->शेष_lcdcon2;

	अगर (!(info->var.sync & FB_SYNC_HOR_HIGH_ACT))
		value |= ATMEL_LCDC_INVLINE_INVERTED;
	अगर (!(info->var.sync & FB_SYNC_VERT_HIGH_ACT))
		value |= ATMEL_LCDC_INVFRAME_INVERTED;

	चयन (info->var.bits_per_pixel) अणु
		हाल 1:	value |= ATMEL_LCDC_PIXELSIZE_1; अवरोध;
		हाल 2: value |= ATMEL_LCDC_PIXELSIZE_2; अवरोध;
		हाल 4: value |= ATMEL_LCDC_PIXELSIZE_4; अवरोध;
		हाल 8: value |= ATMEL_LCDC_PIXELSIZE_8; अवरोध;
		हाल 15: fallthrough;
		हाल 16: value |= ATMEL_LCDC_PIXELSIZE_16; अवरोध;
		हाल 24: value |= ATMEL_LCDC_PIXELSIZE_24; अवरोध;
		हाल 32: value |= ATMEL_LCDC_PIXELSIZE_32; अवरोध;
		शेष: BUG(); अवरोध;
	पूर्ण
	dev_dbg(info->device, "  * LCDCON2 = %08lx\n", value);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_LCDCON2, value);

	/* Vertical timing */
	value = (info->var.vsync_len - 1) << ATMEL_LCDC_VPW_OFFSET;
	value |= info->var.upper_margin << ATMEL_LCDC_VBP_OFFSET;
	value |= info->var.lower_margin;
	dev_dbg(info->device, "  * LCDTIM1 = %08lx\n", value);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_TIM1, value);

	/* Horizontal timing */
	value = (info->var.right_margin - 1) << ATMEL_LCDC_HFP_OFFSET;
	value |= (info->var.hsync_len - 1) << ATMEL_LCDC_HPW_OFFSET;
	value |= (info->var.left_margin - 1);
	dev_dbg(info->device, "  * LCDTIM2 = %08lx\n", value);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_TIM2, value);

	/* Horizontal value (aka line size) */
	hozval_linesz = compute_hozval(sinfo, info->var.xres);

	/* Display size */
	value = (hozval_linesz - 1) << ATMEL_LCDC_HOZVAL_OFFSET;
	value |= info->var.yres - 1;
	dev_dbg(info->device, "  * LCDFRMCFG = %08lx\n", value);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_LCDFRMCFG, value);

	/* FIFO Threshold: Use क्रमmula from data sheet */
	value = ATMEL_LCDC_FIFO_SIZE - (2 * ATMEL_LCDC_DMA_BURST_LEN + 3);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_FIFO, value);

	/* Toggle LCD_MODE every frame */
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_MVAL, 0);

	/* Disable all पूर्णांकerrupts */
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_IDR, ~0U);
	/* Enable FIFO & DMA errors */
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_IER, ATMEL_LCDC_UFLWI | ATMEL_LCDC_OWRI | ATMEL_LCDC_MERI);

	/* ...रुको क्रम DMA engine to become idle... */
	जबतक (lcdc_पढ़ोl(sinfo, ATMEL_LCDC_DMACON) & ATMEL_LCDC_DMABUSY)
		msleep(10);

	aपंचांगel_lcdfb_start(sinfo);

	dev_dbg(info->device, "  * DONE\n");

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक chan_to_field(अचिन्हित पूर्णांक chan, स्थिर काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

/**
 *  	aपंचांगel_lcdfb_setcolreg - Optional function. Sets a color रेजिस्टर.
 *      @regno: Which रेजिस्टर in the CLUT we are programming
 *      @red: The red value which can be up to 16 bits wide
 *	@green: The green value which can be up to 16 bits wide
 *	@blue:  The blue value which can be up to 16 bits wide.
 *	@transp: If supported the alpha value which can be up to 16 bits wide.
 *      @info: frame buffer info काष्ठाure
 *
 *  	Set a single color रेजिस्टर. The values supplied have a 16 bit
 *  	magnitude which needs to be scaled in this function क्रम the hardware.
 *	Things to take पूर्णांकo consideration are how many color रेजिस्टरs, अगर
 *	any, are supported with the current color visual. With truecolor mode
 *	no color palettes are supported. Here a pseuकरो palette is created
 *	which we store the value in pseuकरो_palette in काष्ठा fb_info. For
 *	pseuकरोcolor mode we have a limited color palette. To deal with this
 *	we can program what color is displayed क्रम a particular pixel value.
 *	DirectColor is similar in that we can program each color field. If
 *	we have a अटल colormap we करोn't need to implement this function.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success. In an
 *	ideal world, this would have been the हाल, but as it turns
 *	out, the other drivers वापस 1 on failure, so that's what
 *	we're going to करो.
 */
अटल पूर्णांक aपंचांगel_lcdfb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			     अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			     अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा aपंचांगel_lcdfb_info *sinfo = info->par;
	काष्ठा aपंचांगel_lcdfb_pdata *pdata = &sinfo->pdata;
	अचिन्हित पूर्णांक val;
	u32 *pal;
	पूर्णांक ret = 1;

	अगर (info->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green
				      + 7471 * blue) >> 16;

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		अगर (regno < 16) अणु
			pal = info->pseuकरो_palette;

			val  = chan_to_field(red, &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue, &info->var.blue);

			pal[regno] = val;
			ret = 0;
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_PSEUDOCOLOR:
		अगर (regno < 256) अणु
			अगर (sinfo->config->have_पूर्णांकensity_bit) अणु
				/* old style I+BGR:555 */
				val  = ((red   >> 11) & 0x001f);
				val |= ((green >>  6) & 0x03e0);
				val |= ((blue  >>  1) & 0x7c00);

				/*
				 * TODO: पूर्णांकensity bit. Maybe something like
				 *   ~(red[10] ^ green[10] ^ blue[10]) & 1
				 */
			पूर्ण अन्यथा अणु
				/* new style BGR:565 / RGB:565 */
				अगर (pdata->lcd_wiring_mode == ATMEL_LCDC_WIRING_RGB) अणु
					val  = ((blue >> 11) & 0x001f);
					val |= ((red  >>  0) & 0xf800);
				पूर्ण अन्यथा अणु
					val  = ((red  >> 11) & 0x001f);
					val |= ((blue >>  0) & 0xf800);
				पूर्ण

				val |= ((green >>  5) & 0x07e0);
			पूर्ण

			lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_LUT(regno), val);
			ret = 0;
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_MONO01:
		अगर (regno < 2) अणु
			val = (regno == 0) ? 0x00 : 0x1F;
			lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_LUT(regno), val);
			ret = 0;
		पूर्ण
		अवरोध;

	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_lcdfb_pan_display(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *info)
अणु
	dev_dbg(info->device, "%s\n", __func__);

	aपंचांगel_lcdfb_update_dma(info, var);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_lcdfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा aपंचांगel_lcdfb_info *sinfo = info->par;

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
	हाल FB_BLANK_NORMAL:
		aपंचांगel_lcdfb_start(sinfo);
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		aपंचांगel_lcdfb_stop(sinfo);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* let fbcon करो a soft blank क्रम us */
	वापस ((blank_mode == FB_BLANK_NORMAL) ? 1 : 0);
पूर्ण

अटल स्थिर काष्ठा fb_ops aपंचांगel_lcdfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= aपंचांगel_lcdfb_check_var,
	.fb_set_par	= aपंचांगel_lcdfb_set_par,
	.fb_setcolreg	= aपंचांगel_lcdfb_setcolreg,
	.fb_blank	= aपंचांगel_lcdfb_blank,
	.fb_pan_display	= aपंचांगel_lcdfb_pan_display,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल irqवापस_t aपंचांगel_lcdfb_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fb_info *info = dev_id;
	काष्ठा aपंचांगel_lcdfb_info *sinfo = info->par;
	u32 status;

	status = lcdc_पढ़ोl(sinfo, ATMEL_LCDC_ISR);
	अगर (status & ATMEL_LCDC_UFLWI) अणु
		dev_warn(info->device, "FIFO underflow %#x\n", status);
		/* reset DMA and FIFO to aव्योम screen shअगरting */
		schedule_work(&sinfo->task);
	पूर्ण
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_ICR, status);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * LCD controller task (to reset the LCD)
 */
अटल व्योम aपंचांगel_lcdfb_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aपंचांगel_lcdfb_info *sinfo =
		container_of(work, काष्ठा aपंचांगel_lcdfb_info, task);

	aपंचांगel_lcdfb_reset(sinfo);
पूर्ण

अटल पूर्णांक __init aपंचांगel_lcdfb_init_fbinfo(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	काष्ठा fb_info *info = sinfo->info;
	पूर्णांक ret = 0;

	info->var.activate |= FB_ACTIVATE_FORCE | FB_ACTIVATE_NOW;

	dev_info(info->device,
	       "%luKiB frame buffer at %08lx (mapped at %p)\n",
	       (अचिन्हित दीर्घ)info->fix.smem_len / 1024,
	       (अचिन्हित दीर्घ)info->fix.smem_start,
	       info->screen_base);

	/* Allocate colormap */
	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (ret < 0)
		dev_err(info->device, "Alloc color map failed\n");

	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_lcdfb_start_घड़ी(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	clk_prepare_enable(sinfo->bus_clk);
	clk_prepare_enable(sinfo->lcdc_clk);
पूर्ण

अटल व्योम aपंचांगel_lcdfb_stop_घड़ी(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	clk_disable_unprepare(sinfo->bus_clk);
	clk_disable_unprepare(sinfo->lcdc_clk);
पूर्ण

अटल स्थिर काष्ठा of_device_id aपंचांगel_lcdfb_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9261-lcdc" , .data = &at91sam9261_config, पूर्ण,
	अणु .compatible = "atmel,at91sam9263-lcdc" , .data = &at91sam9263_config, पूर्ण,
	अणु .compatible = "atmel,at91sam9g10-lcdc" , .data = &at91sam9g10_config, पूर्ण,
	अणु .compatible = "atmel,at91sam9g45-lcdc" , .data = &at91sam9g45_config, पूर्ण,
	अणु .compatible = "atmel,at91sam9g45es-lcdc" , .data = &at91sam9g45es_config, पूर्ण,
	अणु .compatible = "atmel,at91sam9rl-lcdc" , .data = &at91sam9rl_config, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aपंचांगel_lcdfb_dt_ids);

अटल स्थिर अक्षर *aपंचांगel_lcdfb_wiring_modes[] = अणु
	[ATMEL_LCDC_WIRING_BGR]	= "BRG",
	[ATMEL_LCDC_WIRING_RGB]	= "RGB",
पूर्ण;

अटल पूर्णांक aपंचांगel_lcdfb_get_of_wiring_modes(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *mode;
	पूर्णांक err, i;

	err = of_property_पढ़ो_string(np, "atmel,lcd-wiring-mode", &mode);
	अगर (err < 0)
		वापस ATMEL_LCDC_WIRING_BGR;

	क्रम (i = 0; i < ARRAY_SIZE(aपंचांगel_lcdfb_wiring_modes); i++)
		अगर (!strहालcmp(mode, aपंचांगel_lcdfb_wiring_modes[i]))
			वापस i;

	वापस -ENODEV;
पूर्ण

अटल व्योम aपंचांगel_lcdfb_घातer_control_gpio(काष्ठा aपंचांगel_lcdfb_pdata *pdata, पूर्णांक on)
अणु
	काष्ठा aपंचांगel_lcdfb_घातer_ctrl_gpio *og;

	list_क्रम_each_entry(og, &pdata->pwr_gpios, list)
		gpiod_set_value(og->gpiod, on);
पूर्ण

अटल पूर्णांक aपंचांगel_lcdfb_of_init(काष्ठा aपंचांगel_lcdfb_info *sinfo)
अणु
	काष्ठा fb_info *info = sinfo->info;
	काष्ठा aपंचांगel_lcdfb_pdata *pdata = &sinfo->pdata;
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा device *dev = &sinfo->pdev->dev;
	काष्ठा device_node *np =dev->of_node;
	काष्ठा device_node *display_np;
	काष्ठा aपंचांगel_lcdfb_घातer_ctrl_gpio *og;
	bool is_gpio_घातer = false;
	काष्ठा fb_videomode fb_vm;
	काष्ठा gpio_desc *gpiod;
	काष्ठा videomode vm;
	पूर्णांक ret;
	पूर्णांक i;

	sinfo->config = (काष्ठा aपंचांगel_lcdfb_config*)
		of_match_device(aपंचांगel_lcdfb_dt_ids, dev)->data;

	display_np = of_parse_phandle(np, "display", 0);
	अगर (!display_np) अणु
		dev_err(dev, "failed to find display phandle\n");
		वापस -ENOENT;
	पूर्ण

	ret = of_property_पढ़ो_u32(display_np, "bits-per-pixel", &var->bits_per_pixel);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get property bits-per-pixel\n");
		जाओ put_display_node;
	पूर्ण

	ret = of_property_पढ़ो_u32(display_np, "atmel,guard-time", &pdata->guard_समय);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get property atmel,guard-time\n");
		जाओ put_display_node;
	पूर्ण

	ret = of_property_पढ़ो_u32(display_np, "atmel,lcdcon2", &pdata->शेष_lcdcon2);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get property atmel,lcdcon2\n");
		जाओ put_display_node;
	पूर्ण

	ret = of_property_पढ़ो_u32(display_np, "atmel,dmacon", &pdata->शेष_dmacon);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get property bits-per-pixel\n");
		जाओ put_display_node;
	पूर्ण

	INIT_LIST_HEAD(&pdata->pwr_gpios);
	क्रम (i = 0; i < gpiod_count(dev, "atmel,power-control"); i++) अणु
		ret = -ENOMEM;
		gpiod = devm_gpiod_get_index(dev, "atmel,power-control",
					     i, GPIOD_ASIS);
		अगर (IS_ERR(gpiod))
			जारी;

		og = devm_kzalloc(dev, माप(*og), GFP_KERNEL);
		अगर (!og)
			जाओ put_display_node;

		og->gpiod = gpiod;
		is_gpio_घातer = true;

		ret = gpiod_direction_output(gpiod, gpiod_is_active_low(gpiod));
		अगर (ret) अणु
			dev_err(dev, "set direction output gpio atmel,power-control[%d] failed\n", i);
			जाओ put_display_node;
		पूर्ण
		list_add(&og->list, &pdata->pwr_gpios);
	पूर्ण

	अगर (is_gpio_घातer)
		pdata->aपंचांगel_lcdfb_घातer_control = aपंचांगel_lcdfb_घातer_control_gpio;

	ret = aपंचांगel_lcdfb_get_of_wiring_modes(display_np);
	अगर (ret < 0) अणु
		dev_err(dev, "invalid atmel,lcd-wiring-mode\n");
		जाओ put_display_node;
	पूर्ण
	pdata->lcd_wiring_mode = ret;

	pdata->lcdcon_is_backlight = of_property_पढ़ो_bool(display_np, "atmel,lcdcon-backlight");
	pdata->lcdcon_pol_negative = of_property_पढ़ो_bool(display_np, "atmel,lcdcon-backlight-inverted");

	ret = of_get_videomode(display_np, &vm, OF_USE_NATIVE_MODE);
	अगर (ret) अणु
		dev_err(dev, "failed to get videomode from DT\n");
		जाओ put_display_node;
	पूर्ण

	ret = fb_videomode_from_videomode(&vm, &fb_vm);
	अगर (ret < 0)
		जाओ put_display_node;

	fb_add_videomode(&fb_vm, &info->modelist);

put_display_node:
	of_node_put(display_np);
	वापस ret;
पूर्ण

अटल पूर्णांक __init aपंचांगel_lcdfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fb_info *info;
	काष्ठा aपंचांगel_lcdfb_info *sinfo;
	काष्ठा resource *regs = शून्य;
	काष्ठा resource *map = शून्य;
	काष्ठा fb_modelist *modelist;
	पूर्णांक ret;

	dev_dbg(dev, "%s BEGIN\n", __func__);

	ret = -ENOMEM;
	info = framebuffer_alloc(माप(काष्ठा aपंचांगel_lcdfb_info), dev);
	अगर (!info)
		जाओ out;

	sinfo = info->par;
	sinfo->pdev = pdev;
	sinfo->info = info;

	INIT_LIST_HEAD(&info->modelist);

	अगर (pdev->dev.of_node) अणु
		ret = aपंचांगel_lcdfb_of_init(sinfo);
		अगर (ret)
			जाओ मुक्त_info;
	पूर्ण अन्यथा अणु
		dev_err(dev, "cannot get default configuration\n");
		जाओ मुक्त_info;
	पूर्ण

	अगर (!sinfo->config)
		जाओ मुक्त_info;

	sinfo->reg_lcd = devm_regulator_get(&pdev->dev, "lcd");
	अगर (IS_ERR(sinfo->reg_lcd))
		sinfo->reg_lcd = शून्य;

	info->flags = FBINFO_DEFAULT | FBINFO_PARTIAL_PAN_OK |
		      FBINFO_HWACCEL_YPAN;
	info->pseuकरो_palette = sinfo->pseuकरो_palette;
	info->fbops = &aपंचांगel_lcdfb_ops;

	info->fix = aपंचांगel_lcdfb_fix;
	म_नकल(info->fix.id, sinfo->pdev->name);

	/* Enable LCDC Clocks */
	sinfo->bus_clk = clk_get(dev, "hclk");
	अगर (IS_ERR(sinfo->bus_clk)) अणु
		ret = PTR_ERR(sinfo->bus_clk);
		जाओ मुक्त_info;
	पूर्ण
	sinfo->lcdc_clk = clk_get(dev, "lcdc_clk");
	अगर (IS_ERR(sinfo->lcdc_clk)) अणु
		ret = PTR_ERR(sinfo->lcdc_clk);
		जाओ put_bus_clk;
	पूर्ण
	aपंचांगel_lcdfb_start_घड़ी(sinfo);

	modelist = list_first_entry(&info->modelist,
			काष्ठा fb_modelist, list);
	fb_videomode_to_var(&info->var, &modelist->mode);

	aपंचांगel_lcdfb_check_var(&info->var, info);

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(dev, "resources unusable\n");
		ret = -ENXIO;
		जाओ stop_clk;
	पूर्ण

	sinfo->irq_base = platक्रमm_get_irq(pdev, 0);
	अगर (sinfo->irq_base < 0) अणु
		ret = sinfo->irq_base;
		जाओ stop_clk;
	पूर्ण

	/* Initialize video memory */
	map = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (map) अणु
		/* use a pre-allocated memory buffer */
		info->fix.smem_start = map->start;
		info->fix.smem_len = resource_size(map);
		अगर (!request_mem_region(info->fix.smem_start,
					info->fix.smem_len, pdev->name)) अणु
			ret = -EBUSY;
			जाओ stop_clk;
		पूर्ण

		info->screen_base = ioremap_wc(info->fix.smem_start,
					       info->fix.smem_len);
		अगर (!info->screen_base) अणु
			ret = -ENOMEM;
			जाओ release_पूर्णांकmem;
		पूर्ण

		/*
		 * Don't clear the framebuffer -- someone may have set
		 * up a splash image.
		 */
	पूर्ण अन्यथा अणु
		/* allocate memory buffer */
		ret = aपंचांगel_lcdfb_alloc_video_memory(sinfo);
		अगर (ret < 0) अणु
			dev_err(dev, "cannot allocate framebuffer: %d\n", ret);
			जाओ stop_clk;
		पूर्ण
	पूर्ण

	/* LCDC रेजिस्टरs */
	info->fix.mmio_start = regs->start;
	info->fix.mmio_len = resource_size(regs);

	अगर (!request_mem_region(info->fix.mmio_start,
				info->fix.mmio_len, pdev->name)) अणु
		ret = -EBUSY;
		जाओ मुक्त_fb;
	पूर्ण

	sinfo->mmio = ioremap(info->fix.mmio_start, info->fix.mmio_len);
	अगर (!sinfo->mmio) अणु
		dev_err(dev, "cannot map LCDC registers\n");
		ret = -ENOMEM;
		जाओ release_mem;
	पूर्ण

	/* Initialize PWM क्रम contrast or backlight ("off") */
	init_contrast(sinfo);

	/* पूर्णांकerrupt */
	ret = request_irq(sinfo->irq_base, aपंचांगel_lcdfb_पूर्णांकerrupt, 0, pdev->name, info);
	अगर (ret) अणु
		dev_err(dev, "request_irq failed: %d\n", ret);
		जाओ unmap_mmio;
	पूर्ण

	/* Some operations on the LCDC might sleep and
	 * require a preemptible task context */
	INIT_WORK(&sinfo->task, aपंचांगel_lcdfb_task);

	ret = aपंचांगel_lcdfb_init_fbinfo(sinfo);
	अगर (ret < 0) अणु
		dev_err(dev, "init fbinfo failed: %d\n", ret);
		जाओ unरेजिस्टर_irqs;
	पूर्ण

	ret = aपंचांगel_lcdfb_set_par(info);
	अगर (ret < 0) अणु
		dev_err(dev, "set par failed: %d\n", ret);
		जाओ unरेजिस्टर_irqs;
	पूर्ण

	dev_set_drvdata(dev, info);

	/*
	 * Tell the world that we're पढ़ोy to go
	 */
	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register framebuffer device: %d\n", ret);
		जाओ reset_drvdata;
	पूर्ण

	/* Power up the LCDC screen */
	aपंचांगel_lcdfb_घातer_control(sinfo, 1);

	dev_info(dev, "fb%d: Atmel LCDC at 0x%08lx (mapped at %p), irq %d\n",
		       info->node, info->fix.mmio_start, sinfo->mmio, sinfo->irq_base);

	वापस 0;

reset_drvdata:
	dev_set_drvdata(dev, शून्य);
	fb_dealloc_cmap(&info->cmap);
unरेजिस्टर_irqs:
	cancel_work_sync(&sinfo->task);
	मुक्त_irq(sinfo->irq_base, info);
unmap_mmio:
	निकास_backlight(sinfo);
	iounmap(sinfo->mmio);
release_mem:
 	release_mem_region(info->fix.mmio_start, info->fix.mmio_len);
मुक्त_fb:
	अगर (map)
		iounmap(info->screen_base);
	अन्यथा
		aपंचांगel_lcdfb_मुक्त_video_memory(sinfo);

release_पूर्णांकmem:
	अगर (map)
		release_mem_region(info->fix.smem_start, info->fix.smem_len);
stop_clk:
	aपंचांगel_lcdfb_stop_घड़ी(sinfo);
	clk_put(sinfo->lcdc_clk);
put_bus_clk:
	clk_put(sinfo->bus_clk);
मुक्त_info:
	framebuffer_release(info);
out:
	dev_dbg(dev, "%s FAILED\n", __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक __निकास aपंचांगel_lcdfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_lcdfb_info *sinfo;

	अगर (!info || !info->par)
		वापस 0;
	sinfo = info->par;

	cancel_work_sync(&sinfo->task);
	निकास_backlight(sinfo);
	aपंचांगel_lcdfb_घातer_control(sinfo, 0);
	unरेजिस्टर_framebuffer(info);
	aपंचांगel_lcdfb_stop_घड़ी(sinfo);
	clk_put(sinfo->lcdc_clk);
	clk_put(sinfo->bus_clk);
	fb_dealloc_cmap(&info->cmap);
	मुक्त_irq(sinfo->irq_base, info);
	iounmap(sinfo->mmio);
 	release_mem_region(info->fix.mmio_start, info->fix.mmio_len);
	अगर (platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1)) अणु
		iounmap(info->screen_base);
		release_mem_region(info->fix.smem_start, info->fix.smem_len);
	पूर्ण अन्यथा अणु
		aपंचांगel_lcdfb_मुक्त_video_memory(sinfo);
	पूर्ण

	framebuffer_release(info);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक aपंचांगel_lcdfb_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t mesg)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_lcdfb_info *sinfo = info->par;

	/*
	 * We करोn't want to handle पूर्णांकerrupts जबतक the घड़ी is
	 * stopped. It may take क्रमever.
	 */
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_IDR, ~0U);

	sinfo->saved_lcdcon = lcdc_पढ़ोl(sinfo, ATMEL_LCDC_CONTRAST_CTR);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_CONTRAST_CTR, 0);
	aपंचांगel_lcdfb_घातer_control(sinfo, 0);
	aपंचांगel_lcdfb_stop(sinfo);
	aपंचांगel_lcdfb_stop_घड़ी(sinfo);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_lcdfb_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_lcdfb_info *sinfo = info->par;

	aपंचांगel_lcdfb_start_घड़ी(sinfo);
	aपंचांगel_lcdfb_start(sinfo);
	aपंचांगel_lcdfb_घातer_control(sinfo, 1);
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_CONTRAST_CTR, sinfo->saved_lcdcon);

	/* Enable FIFO & DMA errors */
	lcdc_ग_लिखोl(sinfo, ATMEL_LCDC_IER, ATMEL_LCDC_UFLWI
			| ATMEL_LCDC_OWRI | ATMEL_LCDC_MERI);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा aपंचांगel_lcdfb_suspend	शून्य
#घोषणा aपंचांगel_lcdfb_resume	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver aपंचांगel_lcdfb_driver = अणु
	.हटाओ		= __निकास_p(aपंचांगel_lcdfb_हटाओ),
	.suspend	= aपंचांगel_lcdfb_suspend,
	.resume		= aपंचांगel_lcdfb_resume,
	.driver		= अणु
		.name	= "atmel_lcdfb",
		.of_match_table	= of_match_ptr(aपंचांगel_lcdfb_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(aपंचांगel_lcdfb_driver, aपंचांगel_lcdfb_probe);

MODULE_DESCRIPTION("AT91 LCD Controller framebuffer driver");
MODULE_AUTHOR("Nicolas Ferre <nicolas.ferre@atmel.com>");
MODULE_LICENSE("GPL");
