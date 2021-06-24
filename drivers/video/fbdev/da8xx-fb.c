<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2008-2009 MontaVista Software Inc.
 * Copyright (C) 2008-2009 Texas Instruments Inc
 *
 * Based on the LCD driver क्रम TI Avalanche processors written by
 * Ajay Singh and Shalom Hai.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fb.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/console.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/lcm.h>
#समावेश <video/da8xx-fb.h>
#समावेश <यंत्र/भाग64.h>

#घोषणा DRIVER_NAME "da8xx_lcdc"

#घोषणा LCD_VERSION_1	1
#घोषणा LCD_VERSION_2	2

/* LCD Status Register */
#घोषणा LCD_END_OF_FRAME1		BIT(9)
#घोषणा LCD_END_OF_FRAME0		BIT(8)
#घोषणा LCD_PL_LOAD_DONE		BIT(6)
#घोषणा LCD_FIFO_UNDERFLOW		BIT(5)
#घोषणा LCD_SYNC_LOST			BIT(2)
#घोषणा LCD_FRAME_DONE			BIT(0)

/* LCD DMA Control Register */
#घोषणा LCD_DMA_BURST_SIZE(x)		((x) << 4)
#घोषणा LCD_DMA_BURST_1			0x0
#घोषणा LCD_DMA_BURST_2			0x1
#घोषणा LCD_DMA_BURST_4			0x2
#घोषणा LCD_DMA_BURST_8			0x3
#घोषणा LCD_DMA_BURST_16		0x4
#घोषणा LCD_V1_END_OF_FRAME_INT_ENA	BIT(2)
#घोषणा LCD_V2_END_OF_FRAME0_INT_ENA	BIT(8)
#घोषणा LCD_V2_END_OF_FRAME1_INT_ENA	BIT(9)
#घोषणा LCD_DUAL_FRAME_BUFFER_ENABLE	BIT(0)

/* LCD Control Register */
#घोषणा LCD_CLK_DIVISOR(x)		((x) << 8)
#घोषणा LCD_RASTER_MODE			0x01

/* LCD Raster Control Register */
#घोषणा LCD_PALETTE_LOAD_MODE(x)	((x) << 20)
#घोषणा PALETTE_AND_DATA		0x00
#घोषणा PALETTE_ONLY			0x01
#घोषणा DATA_ONLY			0x02

#घोषणा LCD_MONO_8BIT_MODE		BIT(9)
#घोषणा LCD_RASTER_ORDER		BIT(8)
#घोषणा LCD_TFT_MODE			BIT(7)
#घोषणा LCD_V1_UNDERFLOW_INT_ENA	BIT(6)
#घोषणा LCD_V2_UNDERFLOW_INT_ENA	BIT(5)
#घोषणा LCD_V1_PL_INT_ENA		BIT(4)
#घोषणा LCD_V2_PL_INT_ENA		BIT(6)
#घोषणा LCD_MONOCHROME_MODE		BIT(1)
#घोषणा LCD_RASTER_ENABLE		BIT(0)
#घोषणा LCD_TFT_ALT_ENABLE		BIT(23)
#घोषणा LCD_STN_565_ENABLE		BIT(24)
#घोषणा LCD_V2_DMA_CLK_EN		BIT(2)
#घोषणा LCD_V2_LIDD_CLK_EN		BIT(1)
#घोषणा LCD_V2_CORE_CLK_EN		BIT(0)
#घोषणा LCD_V2_LPP_B10			26
#घोषणा LCD_V2_TFT_24BPP_MODE		BIT(25)
#घोषणा LCD_V2_TFT_24BPP_UNPACK		BIT(26)

/* LCD Raster Timing 2 Register */
#घोषणा LCD_AC_BIAS_TRANSITIONS_PER_INT(x)	((x) << 16)
#घोषणा LCD_AC_BIAS_FREQUENCY(x)		((x) << 8)
#घोषणा LCD_SYNC_CTRL				BIT(25)
#घोषणा LCD_SYNC_EDGE				BIT(24)
#घोषणा LCD_INVERT_PIXEL_CLOCK			BIT(22)
#घोषणा LCD_INVERT_LINE_CLOCK			BIT(21)
#घोषणा LCD_INVERT_FRAME_CLOCK			BIT(20)

/* LCD Block */
#घोषणा  LCD_PID_REG				0x0
#घोषणा  LCD_CTRL_REG				0x4
#घोषणा  LCD_STAT_REG				0x8
#घोषणा  LCD_RASTER_CTRL_REG			0x28
#घोषणा  LCD_RASTER_TIMING_0_REG		0x2C
#घोषणा  LCD_RASTER_TIMING_1_REG		0x30
#घोषणा  LCD_RASTER_TIMING_2_REG		0x34
#घोषणा  LCD_DMA_CTRL_REG			0x40
#घोषणा  LCD_DMA_FRM_BUF_BASE_ADDR_0_REG	0x44
#घोषणा  LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG	0x48
#घोषणा  LCD_DMA_FRM_BUF_BASE_ADDR_1_REG	0x4C
#घोषणा  LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG	0x50

/* Interrupt Registers available only in Version 2 */
#घोषणा  LCD_RAW_STAT_REG			0x58
#घोषणा  LCD_MASKED_STAT_REG			0x5c
#घोषणा  LCD_INT_ENABLE_SET_REG			0x60
#घोषणा  LCD_INT_ENABLE_CLR_REG			0x64
#घोषणा  LCD_END_OF_INT_IND_REG			0x68

/* Clock रेजिस्टरs available only on Version 2 */
#घोषणा  LCD_CLK_ENABLE_REG			0x6c
#घोषणा  LCD_CLK_RESET_REG			0x70
#घोषणा  LCD_CLK_MAIN_RESET			BIT(3)

#घोषणा LCD_NUM_BUFFERS	2

#घोषणा PALETTE_SIZE	256

#घोषणा	CLK_MIN_DIV	2
#घोषणा	CLK_MAX_DIV	255

अटल व्योम __iomem *da8xx_fb_reg_base;
अटल अचिन्हित पूर्णांक lcd_revision;
अटल irq_handler_t lcdc_irq_handler;
अटल रुको_queue_head_t frame_करोne_wq;
अटल पूर्णांक frame_करोne_flag;

अटल अचिन्हित पूर्णांक lcdc_पढ़ो(अचिन्हित पूर्णांक addr)
अणु
	वापस (अचिन्हित पूर्णांक)__raw_पढ़ोl(da8xx_fb_reg_base + (addr));
पूर्ण

अटल व्योम lcdc_ग_लिखो(अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक addr)
अणु
	__raw_ग_लिखोl(val, da8xx_fb_reg_base + (addr));
पूर्ण

काष्ठा da8xx_fb_par अणु
	काष्ठा device		*dev;
	dma_addr_t		p_palette_base;
	अचिन्हित अक्षर *v_palette_base;
	dma_addr_t		vram_phys;
	अचिन्हित दीर्घ		vram_size;
	व्योम			*vram_virt;
	अचिन्हित पूर्णांक		dma_start;
	अचिन्हित पूर्णांक		dma_end;
	काष्ठा clk *lcdc_clk;
	पूर्णांक irq;
	अचिन्हित पूर्णांक palette_sz;
	पूर्णांक blank;
	रुको_queue_head_t	vsync_रुको;
	पूर्णांक			vsync_flag;
	पूर्णांक			vsync_समयout;
	spinlock_t		lock_क्रम_chan_update;

	/*
	 * LCDC has 2 ping pong DMA channels, channel 0
	 * and channel 1.
	 */
	अचिन्हित पूर्णांक		which_dma_channel_करोne;
#अगर_घोषित CONFIG_CPU_FREQ
	काष्ठा notअगरier_block	freq_transition;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		lcdc_clk_rate;
	काष्ठा regulator	*lcd_supply;
	u32 pseuकरो_palette[16];
	काष्ठा fb_videomode	mode;
	काष्ठा lcd_ctrl_config	cfg;
पूर्ण;

अटल काष्ठा fb_var_screeninfo da8xx_fb_var;

अटल काष्ठा fb_fix_screeninfo da8xx_fb_fix = अणु
	.id = "DA8xx FB Drv",
	.type = FB_TYPE_PACKED_PIXELS,
	.type_aux = 0,
	.visual = FB_VISUAL_PSEUDOCOLOR,
	.xpanstep = 0,
	.ypanstep = 1,
	.ywrapstep = 0,
	.accel = FB_ACCEL_NONE
पूर्ण;

अटल काष्ठा fb_videomode known_lcd_panels[] = अणु
	/* Sharp LCD035Q3DG01 */
	[0] = अणु
		.name           = "Sharp_LCD035Q3DG01",
		.xres           = 320,
		.yres           = 240,
		.pixघड़ी       = KHZ2PICOS(4607),
		.left_margin    = 6,
		.right_margin   = 8,
		.upper_margin   = 2,
		.lower_margin   = 2,
		.hsync_len      = 0,
		.vsync_len      = 0,
		.sync           = FB_SYNC_CLK_INVERT,
	पूर्ण,
	/* Sharp LK043T1DG01 */
	[1] = अणु
		.name           = "Sharp_LK043T1DG01",
		.xres           = 480,
		.yres           = 272,
		.pixघड़ी       = KHZ2PICOS(7833),
		.left_margin    = 2,
		.right_margin   = 2,
		.upper_margin   = 2,
		.lower_margin   = 2,
		.hsync_len      = 41,
		.vsync_len      = 10,
		.sync           = 0,
		.flag           = 0,
	पूर्ण,
	[2] = अणु
		/* Hitachi SP10Q010 */
		.name           = "SP10Q010",
		.xres           = 320,
		.yres           = 240,
		.pixघड़ी       = KHZ2PICOS(7833),
		.left_margin    = 10,
		.right_margin   = 10,
		.upper_margin   = 10,
		.lower_margin   = 10,
		.hsync_len      = 10,
		.vsync_len      = 10,
		.sync           = 0,
		.flag           = 0,
	पूर्ण,
	[3] = अणु
		/* Densitron 84-0023-001T */
		.name           = "Densitron_84-0023-001T",
		.xres           = 320,
		.yres           = 240,
		.pixघड़ी       = KHZ2PICOS(6400),
		.left_margin    = 0,
		.right_margin   = 0,
		.upper_margin   = 0,
		.lower_margin   = 0,
		.hsync_len      = 30,
		.vsync_len      = 3,
		.sync           = 0,
	पूर्ण,
पूर्ण;

अटल bool da8xx_fb_is_raster_enabled(व्योम)
अणु
	वापस !!(lcdc_पढ़ो(LCD_RASTER_CTRL_REG) & LCD_RASTER_ENABLE);
पूर्ण

/* Enable the Raster Engine of the LCD Controller */
अटल व्योम lcd_enable_raster(व्योम)
अणु
	u32 reg;

	/* Put LCDC in reset क्रम several cycles */
	अगर (lcd_revision == LCD_VERSION_2)
		/* Write 1 to reset LCDC */
		lcdc_ग_लिखो(LCD_CLK_MAIN_RESET, LCD_CLK_RESET_REG);
	mdelay(1);

	/* Bring LCDC out of reset */
	अगर (lcd_revision == LCD_VERSION_2)
		lcdc_ग_लिखो(0, LCD_CLK_RESET_REG);
	mdelay(1);

	/* Above reset sequence करोesnot reset रेजिस्टर context */
	reg = lcdc_पढ़ो(LCD_RASTER_CTRL_REG);
	अगर (!(reg & LCD_RASTER_ENABLE))
		lcdc_ग_लिखो(reg | LCD_RASTER_ENABLE, LCD_RASTER_CTRL_REG);
पूर्ण

/* Disable the Raster Engine of the LCD Controller */
अटल व्योम lcd_disable_raster(क्रमागत da8xx_frame_complete रुको_क्रम_frame_करोne)
अणु
	u32 reg;
	पूर्णांक ret;

	reg = lcdc_पढ़ो(LCD_RASTER_CTRL_REG);
	अगर (reg & LCD_RASTER_ENABLE)
		lcdc_ग_लिखो(reg & ~LCD_RASTER_ENABLE, LCD_RASTER_CTRL_REG);
	अन्यथा
		/* वापस अगर alपढ़ोy disabled */
		वापस;

	अगर ((रुको_क्रम_frame_करोne == DA8XX_FRAME_WAIT) &&
			(lcd_revision == LCD_VERSION_2)) अणु
		frame_करोne_flag = 0;
		ret = रुको_event_पूर्णांकerruptible_समयout(frame_करोne_wq,
				frame_करोne_flag != 0,
				msecs_to_jअगरfies(50));
		अगर (ret == 0)
			pr_err("LCD Controller timed out\n");
	पूर्ण
पूर्ण

अटल व्योम lcd_blit(पूर्णांक load_mode, काष्ठा da8xx_fb_par *par)
अणु
	u32 start;
	u32 end;
	u32 reg_ras;
	u32 reg_dma;
	u32 reg_पूर्णांक;

	/* init reg to clear PLM (loading mode) fields */
	reg_ras = lcdc_पढ़ो(LCD_RASTER_CTRL_REG);
	reg_ras &= ~(3 << 20);

	reg_dma  = lcdc_पढ़ो(LCD_DMA_CTRL_REG);

	अगर (load_mode == LOAD_DATA) अणु
		start    = par->dma_start;
		end      = par->dma_end;

		reg_ras |= LCD_PALETTE_LOAD_MODE(DATA_ONLY);
		अगर (lcd_revision == LCD_VERSION_1) अणु
			reg_dma |= LCD_V1_END_OF_FRAME_INT_ENA;
		पूर्ण अन्यथा अणु
			reg_पूर्णांक = lcdc_पढ़ो(LCD_INT_ENABLE_SET_REG) |
				LCD_V2_END_OF_FRAME0_INT_ENA |
				LCD_V2_END_OF_FRAME1_INT_ENA |
				LCD_FRAME_DONE | LCD_SYNC_LOST;
			lcdc_ग_लिखो(reg_पूर्णांक, LCD_INT_ENABLE_SET_REG);
		पूर्ण
		reg_dma |= LCD_DUAL_FRAME_BUFFER_ENABLE;

		lcdc_ग_लिखो(start, LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
		lcdc_ग_लिखो(end, LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
		lcdc_ग_लिखो(start, LCD_DMA_FRM_BUF_BASE_ADDR_1_REG);
		lcdc_ग_लिखो(end, LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG);
	पूर्ण अन्यथा अगर (load_mode == LOAD_PALETTE) अणु
		start    = par->p_palette_base;
		end      = start + par->palette_sz - 1;

		reg_ras |= LCD_PALETTE_LOAD_MODE(PALETTE_ONLY);

		अगर (lcd_revision == LCD_VERSION_1) अणु
			reg_ras |= LCD_V1_PL_INT_ENA;
		पूर्ण अन्यथा अणु
			reg_पूर्णांक = lcdc_पढ़ो(LCD_INT_ENABLE_SET_REG) |
				LCD_V2_PL_INT_ENA;
			lcdc_ग_लिखो(reg_पूर्णांक, LCD_INT_ENABLE_SET_REG);
		पूर्ण

		lcdc_ग_लिखो(start, LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
		lcdc_ग_लिखो(end, LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
	पूर्ण

	lcdc_ग_लिखो(reg_dma, LCD_DMA_CTRL_REG);
	lcdc_ग_लिखो(reg_ras, LCD_RASTER_CTRL_REG);

	/*
	 * The Raster enable bit must be set after all other control fields are
	 * set.
	 */
	lcd_enable_raster();
पूर्ण

/* Configure the Burst Size and fअगरo threhold of DMA */
अटल पूर्णांक lcd_cfg_dma(पूर्णांक burst_size, पूर्णांक fअगरo_th)
अणु
	u32 reg;

	reg = lcdc_पढ़ो(LCD_DMA_CTRL_REG) & 0x00000001;
	चयन (burst_size) अणु
	हाल 1:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_1);
		अवरोध;
	हाल 2:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_2);
		अवरोध;
	हाल 4:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_4);
		अवरोध;
	हाल 8:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_8);
		अवरोध;
	हाल 16:
	शेष:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_16);
		अवरोध;
	पूर्ण

	reg |= (fअगरo_th << 8);

	lcdc_ग_लिखो(reg, LCD_DMA_CTRL_REG);

	वापस 0;
पूर्ण

अटल व्योम lcd_cfg_ac_bias(पूर्णांक period, पूर्णांक transitions_per_पूर्णांक)
अणु
	u32 reg;

	/* Set the AC Bias Period and Number of Transisitons per Interrupt */
	reg = lcdc_पढ़ो(LCD_RASTER_TIMING_2_REG) & 0xFFF00000;
	reg |= LCD_AC_BIAS_FREQUENCY(period) |
		LCD_AC_BIAS_TRANSITIONS_PER_INT(transitions_per_पूर्णांक);
	lcdc_ग_लिखो(reg, LCD_RASTER_TIMING_2_REG);
पूर्ण

अटल व्योम lcd_cfg_horizontal_sync(पूर्णांक back_porch, पूर्णांक pulse_width,
		पूर्णांक front_porch)
अणु
	u32 reg;

	reg = lcdc_पढ़ो(LCD_RASTER_TIMING_0_REG) & 0x3ff;
	reg |= (((back_porch-1) & 0xff) << 24)
	    | (((front_porch-1) & 0xff) << 16)
	    | (((pulse_width-1) & 0x3f) << 10);
	lcdc_ग_लिखो(reg, LCD_RASTER_TIMING_0_REG);

	/*
	 * LCDC Version 2 adds some extra bits that increase the allowable
	 * size of the horizontal timing रेजिस्टरs.
	 * remember that the रेजिस्टरs use 0 to represent 1 so all values
	 * that get set पूर्णांकo रेजिस्टर need to be decremented by 1
	 */
	अगर (lcd_revision == LCD_VERSION_2) अणु
		/* Mask off the bits we want to change */
		reg = lcdc_पढ़ो(LCD_RASTER_TIMING_2_REG) & ~0x780000ff;
		reg |= ((front_porch-1) & 0x300) >> 8;
		reg |= ((back_porch-1) & 0x300) >> 4;
		reg |= ((pulse_width-1) & 0x3c0) << 21;
		lcdc_ग_लिखो(reg, LCD_RASTER_TIMING_2_REG);
	पूर्ण
पूर्ण

अटल व्योम lcd_cfg_vertical_sync(पूर्णांक back_porch, पूर्णांक pulse_width,
		पूर्णांक front_porch)
अणु
	u32 reg;

	reg = lcdc_पढ़ो(LCD_RASTER_TIMING_1_REG) & 0x3ff;
	reg |= ((back_porch & 0xff) << 24)
	    | ((front_porch & 0xff) << 16)
	    | (((pulse_width-1) & 0x3f) << 10);
	lcdc_ग_लिखो(reg, LCD_RASTER_TIMING_1_REG);
पूर्ण

अटल पूर्णांक lcd_cfg_display(स्थिर काष्ठा lcd_ctrl_config *cfg,
		काष्ठा fb_videomode *panel)
अणु
	u32 reg;
	u32 reg_पूर्णांक;

	reg = lcdc_पढ़ो(LCD_RASTER_CTRL_REG) & ~(LCD_TFT_MODE |
						LCD_MONO_8BIT_MODE |
						LCD_MONOCHROME_MODE);

	चयन (cfg->panel_shade) अणु
	हाल MONOCHROME:
		reg |= LCD_MONOCHROME_MODE;
		अगर (cfg->mono_8bit_mode)
			reg |= LCD_MONO_8BIT_MODE;
		अवरोध;
	हाल COLOR_ACTIVE:
		reg |= LCD_TFT_MODE;
		अगर (cfg->tft_alt_mode)
			reg |= LCD_TFT_ALT_ENABLE;
		अवरोध;

	हाल COLOR_PASSIVE:
		/* AC bias applicable only क्रम Pasive panels */
		lcd_cfg_ac_bias(cfg->ac_bias, cfg->ac_bias_पूर्णांकrpt);
		अगर (cfg->bpp == 12 && cfg->stn_565_mode)
			reg |= LCD_STN_565_ENABLE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* enable additional पूर्णांकerrupts here */
	अगर (lcd_revision == LCD_VERSION_1) अणु
		reg |= LCD_V1_UNDERFLOW_INT_ENA;
	पूर्ण अन्यथा अणु
		reg_पूर्णांक = lcdc_पढ़ो(LCD_INT_ENABLE_SET_REG) |
			LCD_V2_UNDERFLOW_INT_ENA;
		lcdc_ग_लिखो(reg_पूर्णांक, LCD_INT_ENABLE_SET_REG);
	पूर्ण

	lcdc_ग_लिखो(reg, LCD_RASTER_CTRL_REG);

	reg = lcdc_पढ़ो(LCD_RASTER_TIMING_2_REG);

	reg |= LCD_SYNC_CTRL;

	अगर (cfg->sync_edge)
		reg |= LCD_SYNC_EDGE;
	अन्यथा
		reg &= ~LCD_SYNC_EDGE;

	अगर ((panel->sync & FB_SYNC_HOR_HIGH_ACT) == 0)
		reg |= LCD_INVERT_LINE_CLOCK;
	अन्यथा
		reg &= ~LCD_INVERT_LINE_CLOCK;

	अगर ((panel->sync & FB_SYNC_VERT_HIGH_ACT) == 0)
		reg |= LCD_INVERT_FRAME_CLOCK;
	अन्यथा
		reg &= ~LCD_INVERT_FRAME_CLOCK;

	lcdc_ग_लिखो(reg, LCD_RASTER_TIMING_2_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक lcd_cfg_frame_buffer(काष्ठा da8xx_fb_par *par, u32 width, u32 height,
		u32 bpp, u32 raster_order)
अणु
	u32 reg;

	अगर (bpp > 16 && lcd_revision == LCD_VERSION_1)
		वापस -EINVAL;

	/* Set the Panel Width */
	/* Pixels per line = (PPL + 1)*16 */
	अगर (lcd_revision == LCD_VERSION_1) अणु
		/*
		 * 0x3F in bits 4..9 gives max horizontal resolution = 1024
		 * pixels.
		 */
		width &= 0x3f0;
	पूर्ण अन्यथा अणु
		/*
		 * 0x7F in bits 4..10 gives max horizontal resolution = 2048
		 * pixels.
		 */
		width &= 0x7f0;
	पूर्ण

	reg = lcdc_पढ़ो(LCD_RASTER_TIMING_0_REG);
	reg &= 0xfffffc00;
	अगर (lcd_revision == LCD_VERSION_1) अणु
		reg |= ((width >> 4) - 1) << 4;
	पूर्ण अन्यथा अणु
		width = (width >> 4) - 1;
		reg |= ((width & 0x3f) << 4) | ((width & 0x40) >> 3);
	पूर्ण
	lcdc_ग_लिखो(reg, LCD_RASTER_TIMING_0_REG);

	/* Set the Panel Height */
	/* Set bits 9:0 of Lines Per Pixel */
	reg = lcdc_पढ़ो(LCD_RASTER_TIMING_1_REG);
	reg = ((height - 1) & 0x3ff) | (reg & 0xfffffc00);
	lcdc_ग_लिखो(reg, LCD_RASTER_TIMING_1_REG);

	/* Set bit 10 of Lines Per Pixel */
	अगर (lcd_revision == LCD_VERSION_2) अणु
		reg = lcdc_पढ़ो(LCD_RASTER_TIMING_2_REG);
		reg |= ((height - 1) & 0x400) << 16;
		lcdc_ग_लिखो(reg, LCD_RASTER_TIMING_2_REG);
	पूर्ण

	/* Set the Raster Order of the Frame Buffer */
	reg = lcdc_पढ़ो(LCD_RASTER_CTRL_REG) & ~(1 << 8);
	अगर (raster_order)
		reg |= LCD_RASTER_ORDER;

	par->palette_sz = 16 * 2;

	चयन (bpp) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 16:
		अवरोध;
	हाल 24:
		reg |= LCD_V2_TFT_24BPP_MODE;
		अवरोध;
	हाल 32:
		reg |= LCD_V2_TFT_24BPP_MODE;
		reg |= LCD_V2_TFT_24BPP_UNPACK;
		अवरोध;
	हाल 8:
		par->palette_sz = 256 * 2;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	lcdc_ग_लिखो(reg, LCD_RASTER_CTRL_REG);

	वापस 0;
पूर्ण

#घोषणा CNVT_TOHW(val, width) ((((val) << (width)) + 0x7FFF - (val)) >> 16)
अटल पूर्णांक fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			      अचिन्हित blue, अचिन्हित transp,
			      काष्ठा fb_info *info)
अणु
	काष्ठा da8xx_fb_par *par = info->par;
	अचिन्हित लघु *palette = (अचिन्हित लघु *) par->v_palette_base;
	u_लघु pal;
	पूर्णांक update_hw = 0;

	अगर (regno > 255)
		वापस 1;

	अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR)
		वापस 1;

	अगर (info->var.bits_per_pixel > 16 && lcd_revision == LCD_VERSION_1)
		वापस -EINVAL;

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		red = CNVT_TOHW(red, info->var.red.length);
		green = CNVT_TOHW(green, info->var.green.length);
		blue = CNVT_TOHW(blue, info->var.blue.length);
		अवरोध;
	हाल FB_VISUAL_PSEUDOCOLOR:
		चयन (info->var.bits_per_pixel) अणु
		हाल 4:
			अगर (regno > 15)
				वापस -EINVAL;

			अगर (info->var.grayscale) अणु
				pal = regno;
			पूर्ण अन्यथा अणु
				red >>= 4;
				green >>= 8;
				blue >>= 12;

				pal = red & 0x0f00;
				pal |= green & 0x00f0;
				pal |= blue & 0x000f;
			पूर्ण
			अगर (regno == 0)
				pal |= 0x2000;
			palette[regno] = pal;
			अवरोध;

		हाल 8:
			red >>= 4;
			green >>= 8;
			blue >>= 12;

			pal = (red & 0x0f00);
			pal |= (green & 0x00f0);
			pal |= (blue & 0x000f);

			अगर (palette[regno] != pal) अणु
				update_hw = 1;
				palette[regno] = pal;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Truecolor has hardware independent palette */
	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR) अणु
		u32 v;

		अगर (regno > 15)
			वापस -EINVAL;

		v = (red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset);

		((u32 *) (info->pseuकरो_palette))[regno] = v;
		अगर (palette[0] != 0x4000) अणु
			update_hw = 1;
			palette[0] = 0x4000;
		पूर्ण
	पूर्ण

	/* Update the palette in the h/w as needed. */
	अगर (update_hw)
		lcd_blit(LOAD_PALETTE, par);

	वापस 0;
पूर्ण
#अघोषित CNVT_TOHW

अटल व्योम da8xx_fb_lcd_reset(व्योम)
अणु
	/* DMA has to be disabled */
	lcdc_ग_लिखो(0, LCD_DMA_CTRL_REG);
	lcdc_ग_लिखो(0, LCD_RASTER_CTRL_REG);

	अगर (lcd_revision == LCD_VERSION_2) अणु
		lcdc_ग_लिखो(0, LCD_INT_ENABLE_SET_REG);
		/* Write 1 to reset */
		lcdc_ग_लिखो(LCD_CLK_MAIN_RESET, LCD_CLK_RESET_REG);
		lcdc_ग_लिखो(0, LCD_CLK_RESET_REG);
	पूर्ण
पूर्ण

अटल पूर्णांक da8xx_fb_config_clk_भागider(काष्ठा da8xx_fb_par *par,
					      अचिन्हित lcdc_clk_भाग,
					      अचिन्हित lcdc_clk_rate)
अणु
	पूर्णांक ret;

	अगर (par->lcdc_clk_rate != lcdc_clk_rate) अणु
		ret = clk_set_rate(par->lcdc_clk, lcdc_clk_rate);
		अगर (ret) अणु
			dev_err(par->dev,
				"unable to set clock rate at %u\n",
				lcdc_clk_rate);
			वापस ret;
		पूर्ण
		par->lcdc_clk_rate = clk_get_rate(par->lcdc_clk);
	पूर्ण

	/* Configure the LCD घड़ी भागisor. */
	lcdc_ग_लिखो(LCD_CLK_DIVISOR(lcdc_clk_भाग) |
			(LCD_RASTER_MODE & 0x1), LCD_CTRL_REG);

	अगर (lcd_revision == LCD_VERSION_2)
		lcdc_ग_लिखो(LCD_V2_DMA_CLK_EN | LCD_V2_LIDD_CLK_EN |
				LCD_V2_CORE_CLK_EN, LCD_CLK_ENABLE_REG);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक da8xx_fb_calc_clk_भागider(काष्ठा da8xx_fb_par *par,
					      अचिन्हित pixघड़ी,
					      अचिन्हित *lcdc_clk_rate)
अणु
	अचिन्हित lcdc_clk_भाग;

	pixघड़ी = PICOS2KHZ(pixघड़ी) * 1000;

	*lcdc_clk_rate = par->lcdc_clk_rate;

	अगर (pixघड़ी < (*lcdc_clk_rate / CLK_MAX_DIV)) अणु
		*lcdc_clk_rate = clk_round_rate(par->lcdc_clk,
						pixघड़ी * CLK_MAX_DIV);
		lcdc_clk_भाग = CLK_MAX_DIV;
	पूर्ण अन्यथा अगर (pixघड़ी > (*lcdc_clk_rate / CLK_MIN_DIV)) अणु
		*lcdc_clk_rate = clk_round_rate(par->lcdc_clk,
						pixघड़ी * CLK_MIN_DIV);
		lcdc_clk_भाग = CLK_MIN_DIV;
	पूर्ण अन्यथा अणु
		lcdc_clk_भाग = *lcdc_clk_rate / pixघड़ी;
	पूर्ण

	वापस lcdc_clk_भाग;
पूर्ण

अटल पूर्णांक da8xx_fb_calc_config_clk_भागider(काष्ठा da8xx_fb_par *par,
					    काष्ठा fb_videomode *mode)
अणु
	अचिन्हित lcdc_clk_rate;
	अचिन्हित lcdc_clk_भाग = da8xx_fb_calc_clk_भागider(par, mode->pixघड़ी,
							  &lcdc_clk_rate);

	वापस da8xx_fb_config_clk_भागider(par, lcdc_clk_भाग, lcdc_clk_rate);
पूर्ण

अटल अचिन्हित da8xx_fb_round_clk(काष्ठा da8xx_fb_par *par,
					  अचिन्हित pixघड़ी)
अणु
	अचिन्हित lcdc_clk_भाग, lcdc_clk_rate;

	lcdc_clk_भाग = da8xx_fb_calc_clk_भागider(par, pixघड़ी, &lcdc_clk_rate);
	वापस KHZ2PICOS(lcdc_clk_rate / (1000 * lcdc_clk_भाग));
पूर्ण

अटल पूर्णांक lcd_init(काष्ठा da8xx_fb_par *par, स्थिर काष्ठा lcd_ctrl_config *cfg,
		काष्ठा fb_videomode *panel)
अणु
	u32 bpp;
	पूर्णांक ret = 0;

	ret = da8xx_fb_calc_config_clk_भागider(par, panel);
	अगर (ret) अणु
		dev_err(par->dev, "unable to configure clock\n");
		वापस ret;
	पूर्ण

	अगर (panel->sync & FB_SYNC_CLK_INVERT)
		lcdc_ग_लिखो((lcdc_पढ़ो(LCD_RASTER_TIMING_2_REG) |
			LCD_INVERT_PIXEL_CLOCK), LCD_RASTER_TIMING_2_REG);
	अन्यथा
		lcdc_ग_लिखो((lcdc_पढ़ो(LCD_RASTER_TIMING_2_REG) &
			~LCD_INVERT_PIXEL_CLOCK), LCD_RASTER_TIMING_2_REG);

	/* Configure the DMA burst size and fअगरo threshold. */
	ret = lcd_cfg_dma(cfg->dma_burst_sz, cfg->fअगरo_th);
	अगर (ret < 0)
		वापस ret;

	/* Configure the vertical and horizontal sync properties. */
	lcd_cfg_vertical_sync(panel->upper_margin, panel->vsync_len,
			panel->lower_margin);
	lcd_cfg_horizontal_sync(panel->left_margin, panel->hsync_len,
			panel->right_margin);

	/* Configure क्रम disply */
	ret = lcd_cfg_display(cfg, panel);
	अगर (ret < 0)
		वापस ret;

	bpp = cfg->bpp;

	अगर (bpp == 12)
		bpp = 16;
	ret = lcd_cfg_frame_buffer(par, (अचिन्हित पूर्णांक)panel->xres,
				(अचिन्हित पूर्णांक)panel->yres, bpp,
				cfg->raster_order);
	अगर (ret < 0)
		वापस ret;

	/* Configure FDD */
	lcdc_ग_लिखो((lcdc_पढ़ो(LCD_RASTER_CTRL_REG) & 0xfff00fff) |
		       (cfg->fdd << 12), LCD_RASTER_CTRL_REG);

	वापस 0;
पूर्ण

/* IRQ handler क्रम version 2 of LCDC */
अटल irqवापस_t lcdc_irq_handler_rev02(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा da8xx_fb_par *par = arg;
	u32 stat = lcdc_पढ़ो(LCD_MASKED_STAT_REG);

	अगर ((stat & LCD_SYNC_LOST) && (stat & LCD_FIFO_UNDERFLOW)) अणु
		lcd_disable_raster(DA8XX_FRAME_NOWAIT);
		lcdc_ग_लिखो(stat, LCD_MASKED_STAT_REG);
		lcd_enable_raster();
	पूर्ण अन्यथा अगर (stat & LCD_PL_LOAD_DONE) अणु
		/*
		 * Must disable raster beक्रमe changing state of any control bit.
		 * And also must be disabled beक्रमe clearing the PL loading
		 * पूर्णांकerrupt via the following ग_लिखो to the status रेजिस्टर. If
		 * this is करोne after then one माला_लो multiple PL करोne पूर्णांकerrupts.
		 */
		lcd_disable_raster(DA8XX_FRAME_NOWAIT);

		lcdc_ग_लिखो(stat, LCD_MASKED_STAT_REG);

		/* Disable PL completion पूर्णांकerrupt */
		lcdc_ग_लिखो(LCD_V2_PL_INT_ENA, LCD_INT_ENABLE_CLR_REG);

		/* Setup and start data loading mode */
		lcd_blit(LOAD_DATA, par);
	पूर्ण अन्यथा अणु
		lcdc_ग_लिखो(stat, LCD_MASKED_STAT_REG);

		अगर (stat & LCD_END_OF_FRAME0) अणु
			par->which_dma_channel_करोne = 0;
			lcdc_ग_लिखो(par->dma_start,
				   LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
			lcdc_ग_लिखो(par->dma_end,
				   LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
			par->vsync_flag = 1;
			wake_up_पूर्णांकerruptible(&par->vsync_रुको);
		पूर्ण

		अगर (stat & LCD_END_OF_FRAME1) अणु
			par->which_dma_channel_करोne = 1;
			lcdc_ग_लिखो(par->dma_start,
				   LCD_DMA_FRM_BUF_BASE_ADDR_1_REG);
			lcdc_ग_लिखो(par->dma_end,
				   LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG);
			par->vsync_flag = 1;
			wake_up_पूर्णांकerruptible(&par->vsync_रुको);
		पूर्ण

		/* Set only when controller is disabled and at the end of
		 * active frame
		 */
		अगर (stat & BIT(0)) अणु
			frame_करोne_flag = 1;
			wake_up_पूर्णांकerruptible(&frame_करोne_wq);
		पूर्ण
	पूर्ण

	lcdc_ग_लिखो(0, LCD_END_OF_INT_IND_REG);
	वापस IRQ_HANDLED;
पूर्ण

/* IRQ handler क्रम version 1 LCDC */
अटल irqवापस_t lcdc_irq_handler_rev01(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा da8xx_fb_par *par = arg;
	u32 stat = lcdc_पढ़ो(LCD_STAT_REG);
	u32 reg_ras;

	अगर ((stat & LCD_SYNC_LOST) && (stat & LCD_FIFO_UNDERFLOW)) अणु
		lcd_disable_raster(DA8XX_FRAME_NOWAIT);
		lcdc_ग_लिखो(stat, LCD_STAT_REG);
		lcd_enable_raster();
	पूर्ण अन्यथा अगर (stat & LCD_PL_LOAD_DONE) अणु
		/*
		 * Must disable raster beक्रमe changing state of any control bit.
		 * And also must be disabled beक्रमe clearing the PL loading
		 * पूर्णांकerrupt via the following ग_लिखो to the status रेजिस्टर. If
		 * this is करोne after then one माला_लो multiple PL करोne पूर्णांकerrupts.
		 */
		lcd_disable_raster(DA8XX_FRAME_NOWAIT);

		lcdc_ग_लिखो(stat, LCD_STAT_REG);

		/* Disable PL completion inerrupt */
		reg_ras  = lcdc_पढ़ो(LCD_RASTER_CTRL_REG);
		reg_ras &= ~LCD_V1_PL_INT_ENA;
		lcdc_ग_लिखो(reg_ras, LCD_RASTER_CTRL_REG);

		/* Setup and start data loading mode */
		lcd_blit(LOAD_DATA, par);
	पूर्ण अन्यथा अणु
		lcdc_ग_लिखो(stat, LCD_STAT_REG);

		अगर (stat & LCD_END_OF_FRAME0) अणु
			par->which_dma_channel_करोne = 0;
			lcdc_ग_लिखो(par->dma_start,
				   LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
			lcdc_ग_लिखो(par->dma_end,
				   LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
			par->vsync_flag = 1;
			wake_up_पूर्णांकerruptible(&par->vsync_रुको);
		पूर्ण

		अगर (stat & LCD_END_OF_FRAME1) अणु
			par->which_dma_channel_करोne = 1;
			lcdc_ग_लिखो(par->dma_start,
				   LCD_DMA_FRM_BUF_BASE_ADDR_1_REG);
			lcdc_ग_लिखो(par->dma_end,
				   LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG);
			par->vsync_flag = 1;
			wake_up_पूर्णांकerruptible(&par->vsync_रुको);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fb_check_var(काष्ठा fb_var_screeninfo *var,
			काष्ठा fb_info *info)
अणु
	पूर्णांक err = 0;
	काष्ठा da8xx_fb_par *par = info->par;
	पूर्णांक bpp = var->bits_per_pixel >> 3;
	अचिन्हित दीर्घ line_size = var->xres_भव * bpp;

	अगर (var->bits_per_pixel > 16 && lcd_revision == LCD_VERSION_1)
		वापस -EINVAL;

	चयन (var->bits_per_pixel) अणु
	हाल 1:
	हाल 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		var->nonstd = 0;
		अवरोध;
	हाल 4:
		var->red.offset = 0;
		var->red.length = 4;
		var->green.offset = 0;
		var->green.length = 4;
		var->blue.offset = 0;
		var->blue.length = 4;
		var->transp.offset = 0;
		var->transp.length = 0;
		var->nonstd = FB_NONSTD_REV_PIX_IN_B;
		अवरोध;
	हाल 16:		/* RGB 565 */
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		var->nonstd = 0;
		अवरोध;
	हाल 24:
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->nonstd = 0;
		अवरोध;
	हाल 32:
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->nonstd = 0;
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	अगर (line_size * var->yres_भव > par->vram_size)
		var->yres_भव = par->vram_size / line_size;

	अगर (var->yres > var->yres_भव)
		var->yres = var->yres_भव;

	अगर (var->xres > var->xres_भव)
		var->xres = var->xres_भव;

	अगर (var->xres + var->xoffset > var->xres_भव)
		var->xoffset = var->xres_भव - var->xres;
	अगर (var->yres + var->yoffset > var->yres_भव)
		var->yoffset = var->yres_भव - var->yres;

	var->pixघड़ी = da8xx_fb_round_clk(par, var->pixघड़ी);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
अटल पूर्णांक lcd_da8xx_cpufreq_transition(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा da8xx_fb_par *par;

	par = container_of(nb, काष्ठा da8xx_fb_par, freq_transition);
	अगर (val == CPUFREQ_POSTCHANGE) अणु
		अगर (par->lcdc_clk_rate != clk_get_rate(par->lcdc_clk)) अणु
			par->lcdc_clk_rate = clk_get_rate(par->lcdc_clk);
			lcd_disable_raster(DA8XX_FRAME_WAIT);
			da8xx_fb_calc_config_clk_भागider(par, &par->mode);
			अगर (par->blank == FB_BLANK_UNBLANK)
				lcd_enable_raster();
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lcd_da8xx_cpufreq_रेजिस्टर(काष्ठा da8xx_fb_par *par)
अणु
	par->freq_transition.notअगरier_call = lcd_da8xx_cpufreq_transition;

	वापस cpufreq_रेजिस्टर_notअगरier(&par->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

अटल व्योम lcd_da8xx_cpufreq_deरेजिस्टर(काष्ठा da8xx_fb_par *par)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&par->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक fb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा da8xx_fb_par *par = info->par;
	पूर्णांक ret;

#अगर_घोषित CONFIG_CPU_FREQ
	lcd_da8xx_cpufreq_deरेजिस्टर(par);
#पूर्ण_अगर
	अगर (par->lcd_supply) अणु
		ret = regulator_disable(par->lcd_supply);
		अगर (ret)
			वापस ret;
	पूर्ण

	lcd_disable_raster(DA8XX_FRAME_WAIT);
	lcdc_ग_लिखो(0, LCD_RASTER_CTRL_REG);

	/* disable DMA  */
	lcdc_ग_लिखो(0, LCD_DMA_CTRL_REG);

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	pm_runसमय_put_sync(&dev->dev);
	pm_runसमय_disable(&dev->dev);
	framebuffer_release(info);

	वापस 0;
पूर्ण

/*
 * Function to रुको क्रम vertical sync which क्रम this LCD peripheral
 * translates पूर्णांकo रुकोing क्रम the current raster frame to complete.
 */
अटल पूर्णांक fb_रुको_क्रम_vsync(काष्ठा fb_info *info)
अणु
	काष्ठा da8xx_fb_par *par = info->par;
	पूर्णांक ret;

	/*
	 * Set flag to 0 and रुको क्रम isr to set to 1. It would seem there is a
	 * race condition here where the ISR could have occurred just beक्रमe or
	 * just after this set. But since we are just coarsely रुकोing क्रम
	 * a frame to complete then that's OK. i.e. अगर the frame completed
	 * just beक्रमe this code executed then we have to रुको another full
	 * frame समय but there is no way to aव्योम such a situation. On the
	 * other hand अगर the frame completed just after then we करोn't need
	 * to रुको दीर्घ at all. Either way we are guaranteed to वापस to the
	 * user immediately after a frame completion which is all that is
	 * required.
	 */
	par->vsync_flag = 0;
	ret = रुको_event_पूर्णांकerruptible_समयout(par->vsync_रुको,
					       par->vsync_flag != 0,
					       par->vsync_समयout);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक fb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा lcd_sync_arg sync_arg;

	चयन (cmd) अणु
	हाल FBIOGET_CONTRAST:
	हाल FBIOPUT_CONTRAST:
	हाल FBIGET_BRIGHTNESS:
	हाल FBIPUT_BRIGHTNESS:
	हाल FBIGET_COLOR:
	हाल FBIPUT_COLOR:
		वापस -ENOTTY;
	हाल FBIPUT_HSYNC:
		अगर (copy_from_user(&sync_arg, (अक्षर *)arg,
				माप(काष्ठा lcd_sync_arg)))
			वापस -EFAULT;
		lcd_cfg_horizontal_sync(sync_arg.back_porch,
					sync_arg.pulse_width,
					sync_arg.front_porch);
		अवरोध;
	हाल FBIPUT_VSYNC:
		अगर (copy_from_user(&sync_arg, (अक्षर *)arg,
				माप(काष्ठा lcd_sync_arg)))
			वापस -EFAULT;
		lcd_cfg_vertical_sync(sync_arg.back_porch,
					sync_arg.pulse_width,
					sync_arg.front_porch);
		अवरोध;
	हाल FBIO_WAITFORVSYNC:
		वापस fb_रुको_क्रम_vsync(info);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा da8xx_fb_par *par = info->par;
	पूर्णांक ret = 0;

	अगर (par->blank == blank)
		वापस 0;

	par->blank = blank;
	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
		lcd_enable_raster();

		अगर (par->lcd_supply) अणु
			ret = regulator_enable(par->lcd_supply);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	हाल FB_BLANK_NORMAL:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_POWERDOWN:
		अगर (par->lcd_supply) अणु
			ret = regulator_disable(par->lcd_supply);
			अगर (ret)
				वापस ret;
		पूर्ण

		lcd_disable_raster(DA8XX_FRAME_WAIT);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Set new x,y offsets in the भव display क्रम the visible area and चयन
 * to the new mode.
 */
अटल पूर्णांक da8xx_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *fbi)
अणु
	पूर्णांक ret = 0;
	काष्ठा fb_var_screeninfo new_var;
	काष्ठा da8xx_fb_par         *par = fbi->par;
	काष्ठा fb_fix_screeninfo    *fix = &fbi->fix;
	अचिन्हित पूर्णांक end;
	अचिन्हित पूर्णांक start;
	अचिन्हित दीर्घ irq_flags;

	अगर (var->xoffset != fbi->var.xoffset ||
			var->yoffset != fbi->var.yoffset) अणु
		स_नकल(&new_var, &fbi->var, माप(new_var));
		new_var.xoffset = var->xoffset;
		new_var.yoffset = var->yoffset;
		अगर (fb_check_var(&new_var, fbi))
			ret = -EINVAL;
		अन्यथा अणु
			स_नकल(&fbi->var, &new_var, माप(new_var));

			start	= fix->smem_start +
				new_var.yoffset * fix->line_length +
				new_var.xoffset * fbi->var.bits_per_pixel / 8;
			end	= start + fbi->var.yres * fix->line_length - 1;
			par->dma_start	= start;
			par->dma_end	= end;
			spin_lock_irqsave(&par->lock_क्रम_chan_update,
					irq_flags);
			अगर (par->which_dma_channel_करोne == 0) अणु
				lcdc_ग_लिखो(par->dma_start,
					   LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
				lcdc_ग_लिखो(par->dma_end,
					   LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
			पूर्ण अन्यथा अगर (par->which_dma_channel_करोne == 1) अणु
				lcdc_ग_लिखो(par->dma_start,
					   LCD_DMA_FRM_BUF_BASE_ADDR_1_REG);
				lcdc_ग_लिखो(par->dma_end,
					   LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG);
			पूर्ण
			spin_unlock_irqrestore(&par->lock_क्रम_chan_update,
					irq_flags);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da8xxfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा da8xx_fb_par *par = info->par;
	पूर्णांक ret;
	bool raster = da8xx_fb_is_raster_enabled();

	अगर (raster)
		lcd_disable_raster(DA8XX_FRAME_WAIT);

	fb_var_to_videomode(&par->mode, &info->var);

	par->cfg.bpp = info->var.bits_per_pixel;

	info->fix.visual = (par->cfg.bpp <= 8) ?
				FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = (par->mode.xres * par->cfg.bpp) / 8;

	ret = lcd_init(par, &par->cfg, &par->mode);
	अगर (ret < 0) अणु
		dev_err(par->dev, "lcd init failed\n");
		वापस ret;
	पूर्ण

	par->dma_start = info->fix.smem_start +
			 info->var.yoffset * info->fix.line_length +
			 info->var.xoffset * info->var.bits_per_pixel / 8;
	par->dma_end   = par->dma_start +
			 info->var.yres * info->fix.line_length - 1;

	lcdc_ग_लिखो(par->dma_start, LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
	lcdc_ग_लिखो(par->dma_end, LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
	lcdc_ग_लिखो(par->dma_start, LCD_DMA_FRM_BUF_BASE_ADDR_1_REG);
	lcdc_ग_लिखो(par->dma_end, LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG);

	अगर (raster)
		lcd_enable_raster();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops da8xx_fb_ops = अणु
	.owner = THIS_MODULE,
	.fb_check_var = fb_check_var,
	.fb_set_par = da8xxfb_set_par,
	.fb_setcolreg = fb_setcolreg,
	.fb_pan_display = da8xx_pan_display,
	.fb_ioctl = fb_ioctl,
	.fb_fillrect = cfb_fillrect,
	.fb_copyarea = cfb_copyarea,
	.fb_imageblit = cfb_imageblit,
	.fb_blank = cfb_blank,
पूर्ण;

अटल काष्ठा fb_videomode *da8xx_fb_get_videomode(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा da8xx_lcdc_platक्रमm_data *fb_pdata = dev_get_platdata(&dev->dev);
	काष्ठा fb_videomode *lcdc_info;
	पूर्णांक i;

	क्रम (i = 0, lcdc_info = known_lcd_panels;
		i < ARRAY_SIZE(known_lcd_panels); i++, lcdc_info++) अणु
		अगर (म_भेद(fb_pdata->type, lcdc_info->name) == 0)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(known_lcd_panels)) अणु
		dev_err(&dev->dev, "no panel found\n");
		वापस शून्य;
	पूर्ण
	dev_info(&dev->dev, "found %s panel\n", lcdc_info->name);

	वापस lcdc_info;
पूर्ण

अटल पूर्णांक fb_probe(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा da8xx_lcdc_platक्रमm_data *fb_pdata =
						dev_get_platdata(&device->dev);
	काष्ठा lcd_ctrl_config *lcd_cfg;
	काष्ठा fb_videomode *lcdc_info;
	काष्ठा fb_info *da8xx_fb_info;
	काष्ठा da8xx_fb_par *par;
	काष्ठा clk *पंचांगp_lcdc_clk;
	पूर्णांक ret;
	अचिन्हित दीर्घ ulcm;

	अगर (fb_pdata == शून्य) अणु
		dev_err(&device->dev, "Can not get platform data\n");
		वापस -ENOENT;
	पूर्ण

	lcdc_info = da8xx_fb_get_videomode(device);
	अगर (lcdc_info == शून्य)
		वापस -ENODEV;

	da8xx_fb_reg_base = devm_platक्रमm_ioremap_resource(device, 0);
	अगर (IS_ERR(da8xx_fb_reg_base))
		वापस PTR_ERR(da8xx_fb_reg_base);

	पंचांगp_lcdc_clk = devm_clk_get(&device->dev, "fck");
	अगर (IS_ERR(पंचांगp_lcdc_clk)) अणु
		dev_err(&device->dev, "Can not get device clock\n");
		वापस PTR_ERR(पंचांगp_lcdc_clk);
	पूर्ण

	pm_runसमय_enable(&device->dev);
	pm_runसमय_get_sync(&device->dev);

	/* Determine LCD IP Version */
	चयन (lcdc_पढ़ो(LCD_PID_REG)) अणु
	हाल 0x4C100102:
		lcd_revision = LCD_VERSION_1;
		अवरोध;
	हाल 0x4F200800:
	हाल 0x4F201000:
		lcd_revision = LCD_VERSION_2;
		अवरोध;
	शेष:
		dev_warn(&device->dev, "Unknown PID Reg value 0x%x, "
				"defaulting to LCD revision 1\n",
				lcdc_पढ़ो(LCD_PID_REG));
		lcd_revision = LCD_VERSION_1;
		अवरोध;
	पूर्ण

	lcd_cfg = (काष्ठा lcd_ctrl_config *)fb_pdata->controller_data;

	अगर (!lcd_cfg) अणु
		ret = -EINVAL;
		जाओ err_pm_runसमय_disable;
	पूर्ण

	da8xx_fb_info = framebuffer_alloc(माप(काष्ठा da8xx_fb_par),
					&device->dev);
	अगर (!da8xx_fb_info) अणु
		ret = -ENOMEM;
		जाओ err_pm_runसमय_disable;
	पूर्ण

	par = da8xx_fb_info->par;
	par->dev = &device->dev;
	par->lcdc_clk = पंचांगp_lcdc_clk;
	par->lcdc_clk_rate = clk_get_rate(par->lcdc_clk);

	par->lcd_supply = devm_regulator_get_optional(&device->dev, "lcd");
	अगर (IS_ERR(par->lcd_supply)) अणु
		अगर (PTR_ERR(par->lcd_supply) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_release_fb;
		पूर्ण

		par->lcd_supply = शून्य;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(par->lcd_supply);
		अगर (ret)
			जाओ err_release_fb;
	पूर्ण

	fb_videomode_to_var(&da8xx_fb_var, lcdc_info);
	par->cfg = *lcd_cfg;

	da8xx_fb_lcd_reset();

	/* allocate frame buffer */
	par->vram_size = lcdc_info->xres * lcdc_info->yres * lcd_cfg->bpp;
	ulcm = lcm((lcdc_info->xres * lcd_cfg->bpp)/8, PAGE_SIZE);
	par->vram_size = roundup(par->vram_size/8, ulcm);
	par->vram_size = par->vram_size * LCD_NUM_BUFFERS;

	par->vram_virt = dmam_alloc_coherent(par->dev,
					     par->vram_size,
					     &par->vram_phys,
					     GFP_KERNEL | GFP_DMA);
	अगर (!par->vram_virt) अणु
		dev_err(&device->dev,
			"GLCD: kmalloc for frame buffer failed\n");
		ret = -EINVAL;
		जाओ err_release_fb;
	पूर्ण

	da8xx_fb_info->screen_base = (अक्षर __iomem *) par->vram_virt;
	da8xx_fb_fix.smem_start    = par->vram_phys;
	da8xx_fb_fix.smem_len      = par->vram_size;
	da8xx_fb_fix.line_length   = (lcdc_info->xres * lcd_cfg->bpp) / 8;

	par->dma_start = par->vram_phys;
	par->dma_end   = par->dma_start + lcdc_info->yres *
		da8xx_fb_fix.line_length - 1;

	/* allocate palette buffer */
	par->v_palette_base = dmam_alloc_coherent(par->dev, PALETTE_SIZE,
						  &par->p_palette_base,
						  GFP_KERNEL | GFP_DMA);
	अगर (!par->v_palette_base) अणु
		dev_err(&device->dev,
			"GLCD: kmalloc for palette buffer failed\n");
		ret = -EINVAL;
		जाओ err_release_fb;
	पूर्ण

	par->irq = platक्रमm_get_irq(device, 0);
	अगर (par->irq < 0) अणु
		ret = -ENOENT;
		जाओ err_release_fb;
	पूर्ण

	da8xx_fb_var.grayscale =
	    lcd_cfg->panel_shade == MONOCHROME ? 1 : 0;
	da8xx_fb_var.bits_per_pixel = lcd_cfg->bpp;

	/* Initialize fbinfo */
	da8xx_fb_info->flags = FBINFO_FLAG_DEFAULT;
	da8xx_fb_info->fix = da8xx_fb_fix;
	da8xx_fb_info->var = da8xx_fb_var;
	da8xx_fb_info->fbops = &da8xx_fb_ops;
	da8xx_fb_info->pseuकरो_palette = par->pseuकरो_palette;
	da8xx_fb_info->fix.visual = (da8xx_fb_info->var.bits_per_pixel <= 8) ?
				FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;

	ret = fb_alloc_cmap(&da8xx_fb_info->cmap, PALETTE_SIZE, 0);
	अगर (ret)
		जाओ err_release_fb;
	da8xx_fb_info->cmap.len = par->palette_sz;

	/* initialize var_screeninfo */
	da8xx_fb_var.activate = FB_ACTIVATE_FORCE;
	fb_set_var(da8xx_fb_info, &da8xx_fb_var);

	platक्रमm_set_drvdata(device, da8xx_fb_info);

	/* initialize the vsync रुको queue */
	init_रुकोqueue_head(&par->vsync_रुको);
	par->vsync_समयout = HZ / 5;
	par->which_dma_channel_करोne = -1;
	spin_lock_init(&par->lock_क्रम_chan_update);

	/* Register the Frame Buffer  */
	अगर (रेजिस्टर_framebuffer(da8xx_fb_info) < 0) अणु
		dev_err(&device->dev,
			"GLCD: Frame Buffer Registration Failed!\n");
		ret = -EINVAL;
		जाओ err_dealloc_cmap;
	पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
	ret = lcd_da8xx_cpufreq_रेजिस्टर(par);
	अगर (ret) अणु
		dev_err(&device->dev, "failed to register cpufreq\n");
		जाओ err_cpu_freq;
	पूर्ण
#पूर्ण_अगर

	अगर (lcd_revision == LCD_VERSION_1)
		lcdc_irq_handler = lcdc_irq_handler_rev01;
	अन्यथा अणु
		init_रुकोqueue_head(&frame_करोne_wq);
		lcdc_irq_handler = lcdc_irq_handler_rev02;
	पूर्ण

	ret = devm_request_irq(&device->dev, par->irq, lcdc_irq_handler, 0,
			       DRIVER_NAME, par);
	अगर (ret)
		जाओ irq_freq;
	वापस 0;

irq_freq:
#अगर_घोषित CONFIG_CPU_FREQ
	lcd_da8xx_cpufreq_deरेजिस्टर(par);
err_cpu_freq:
#पूर्ण_अगर
	unरेजिस्टर_framebuffer(da8xx_fb_info);

err_dealloc_cmap:
	fb_dealloc_cmap(&da8xx_fb_info->cmap);

err_release_fb:
	framebuffer_release(da8xx_fb_info);

err_pm_runसमय_disable:
	pm_runसमय_put_sync(&device->dev);
	pm_runसमय_disable(&device->dev);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल काष्ठा lcdc_context अणु
	u32 clk_enable;
	u32 ctrl;
	u32 dma_ctrl;
	u32 raster_timing_0;
	u32 raster_timing_1;
	u32 raster_timing_2;
	u32 पूर्णांक_enable_set;
	u32 dma_frm_buf_base_addr_0;
	u32 dma_frm_buf_उच्चमानing_addr_0;
	u32 dma_frm_buf_base_addr_1;
	u32 dma_frm_buf_उच्चमानing_addr_1;
	u32 raster_ctrl;
पूर्ण reg_context;

अटल व्योम lcd_context_save(व्योम)
अणु
	अगर (lcd_revision == LCD_VERSION_2) अणु
		reg_context.clk_enable = lcdc_पढ़ो(LCD_CLK_ENABLE_REG);
		reg_context.पूर्णांक_enable_set = lcdc_पढ़ो(LCD_INT_ENABLE_SET_REG);
	पूर्ण

	reg_context.ctrl = lcdc_पढ़ो(LCD_CTRL_REG);
	reg_context.dma_ctrl = lcdc_पढ़ो(LCD_DMA_CTRL_REG);
	reg_context.raster_timing_0 = lcdc_पढ़ो(LCD_RASTER_TIMING_0_REG);
	reg_context.raster_timing_1 = lcdc_पढ़ो(LCD_RASTER_TIMING_1_REG);
	reg_context.raster_timing_2 = lcdc_पढ़ो(LCD_RASTER_TIMING_2_REG);
	reg_context.dma_frm_buf_base_addr_0 =
		lcdc_पढ़ो(LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
	reg_context.dma_frm_buf_उच्चमानing_addr_0 =
		lcdc_पढ़ो(LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
	reg_context.dma_frm_buf_base_addr_1 =
		lcdc_पढ़ो(LCD_DMA_FRM_BUF_BASE_ADDR_1_REG);
	reg_context.dma_frm_buf_उच्चमानing_addr_1 =
		lcdc_पढ़ो(LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG);
	reg_context.raster_ctrl = lcdc_पढ़ो(LCD_RASTER_CTRL_REG);
	वापस;
पूर्ण

अटल व्योम lcd_context_restore(व्योम)
अणु
	अगर (lcd_revision == LCD_VERSION_2) अणु
		lcdc_ग_लिखो(reg_context.clk_enable, LCD_CLK_ENABLE_REG);
		lcdc_ग_लिखो(reg_context.पूर्णांक_enable_set, LCD_INT_ENABLE_SET_REG);
	पूर्ण

	lcdc_ग_लिखो(reg_context.ctrl, LCD_CTRL_REG);
	lcdc_ग_लिखो(reg_context.dma_ctrl, LCD_DMA_CTRL_REG);
	lcdc_ग_लिखो(reg_context.raster_timing_0, LCD_RASTER_TIMING_0_REG);
	lcdc_ग_लिखो(reg_context.raster_timing_1, LCD_RASTER_TIMING_1_REG);
	lcdc_ग_लिखो(reg_context.raster_timing_2, LCD_RASTER_TIMING_2_REG);
	lcdc_ग_लिखो(reg_context.dma_frm_buf_base_addr_0,
			LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
	lcdc_ग_लिखो(reg_context.dma_frm_buf_उच्चमानing_addr_0,
			LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
	lcdc_ग_लिखो(reg_context.dma_frm_buf_base_addr_1,
			LCD_DMA_FRM_BUF_BASE_ADDR_1_REG);
	lcdc_ग_लिखो(reg_context.dma_frm_buf_उच्चमानing_addr_1,
			LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG);
	lcdc_ग_लिखो(reg_context.raster_ctrl, LCD_RASTER_CTRL_REG);
	वापस;
पूर्ण

अटल पूर्णांक fb_suspend(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा da8xx_fb_par *par = info->par;
	पूर्णांक ret;

	console_lock();
	अगर (par->lcd_supply) अणु
		ret = regulator_disable(par->lcd_supply);
		अगर (ret)
			वापस ret;
	पूर्ण

	fb_set_suspend(info, 1);
	lcd_disable_raster(DA8XX_FRAME_WAIT);
	lcd_context_save();
	pm_runसमय_put_sync(dev);
	console_unlock();

	वापस 0;
पूर्ण
अटल पूर्णांक fb_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा da8xx_fb_par *par = info->par;
	पूर्णांक ret;

	console_lock();
	pm_runसमय_get_sync(dev);
	lcd_context_restore();
	अगर (par->blank == FB_BLANK_UNBLANK) अणु
		lcd_enable_raster();

		अगर (par->lcd_supply) अणु
			ret = regulator_enable(par->lcd_supply);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	fb_set_suspend(info, 0);
	console_unlock();

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(fb_pm_ops, fb_suspend, fb_resume);

अटल काष्ठा platक्रमm_driver da8xx_fb_driver = अणु
	.probe = fb_probe,
	.हटाओ = fb_हटाओ,
	.driver = अणु
		   .name = DRIVER_NAME,
		   .pm	= &fb_pm_ops,
		   पूर्ण,
पूर्ण;
module_platक्रमm_driver(da8xx_fb_driver);

MODULE_DESCRIPTION("Framebuffer driver for TI da8xx/omap-l1xx");
MODULE_AUTHOR("Texas Instruments");
MODULE_LICENSE("GPL");
