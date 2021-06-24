<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008
 * Guennadi Liakhovetski, DENX Software Engineering, <lg@denx.de>
 *
 * Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/console.h>
#समावेश <linux/clk.h>
#समावेश <linux/mutex.h>
#समावेश <linux/dma/ipu-dma.h>
#समावेश <linux/backlight.h>

#समावेश <linux/platक्रमm_data/dma-imx.h>
#समावेश <linux/platक्रमm_data/video-mx3fb.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#घोषणा MX3FB_NAME		"mx3_sdc_fb"

#घोषणा MX3FB_REG_OFFSET	0xB4

/* SDC Registers */
#घोषणा SDC_COM_CONF		(0xB4 - MX3FB_REG_OFFSET)
#घोषणा SDC_GW_CTRL		(0xB8 - MX3FB_REG_OFFSET)
#घोषणा SDC_FG_POS		(0xBC - MX3FB_REG_OFFSET)
#घोषणा SDC_BG_POS		(0xC0 - MX3FB_REG_OFFSET)
#घोषणा SDC_CUR_POS		(0xC4 - MX3FB_REG_OFFSET)
#घोषणा SDC_PWM_CTRL		(0xC8 - MX3FB_REG_OFFSET)
#घोषणा SDC_CUR_MAP		(0xCC - MX3FB_REG_OFFSET)
#घोषणा SDC_HOR_CONF		(0xD0 - MX3FB_REG_OFFSET)
#घोषणा SDC_VER_CONF		(0xD4 - MX3FB_REG_OFFSET)
#घोषणा SDC_SHARP_CONF_1	(0xD8 - MX3FB_REG_OFFSET)
#घोषणा SDC_SHARP_CONF_2	(0xDC - MX3FB_REG_OFFSET)

/* Register bits */
#घोषणा SDC_COM_TFT_COLOR	0x00000001UL
#घोषणा SDC_COM_FG_EN		0x00000010UL
#घोषणा SDC_COM_GWSEL		0x00000020UL
#घोषणा SDC_COM_GLB_A		0x00000040UL
#घोषणा SDC_COM_KEY_COLOR_G	0x00000080UL
#घोषणा SDC_COM_BG_EN		0x00000200UL
#घोषणा SDC_COM_SHARP		0x00001000UL

#घोषणा SDC_V_SYNC_WIDTH_L	0x00000001UL

/* Display Interface रेजिस्टरs */
#घोषणा DI_DISP_IF_CONF		(0x0124 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP_SIG_POL		(0x0128 - MX3FB_REG_OFFSET)
#घोषणा DI_SER_DISP1_CONF	(0x012C - MX3FB_REG_OFFSET)
#घोषणा DI_SER_DISP2_CONF	(0x0130 - MX3FB_REG_OFFSET)
#घोषणा DI_HSP_CLK_PER		(0x0134 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP0_TIME_CONF_1	(0x0138 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP0_TIME_CONF_2	(0x013C - MX3FB_REG_OFFSET)
#घोषणा DI_DISP0_TIME_CONF_3	(0x0140 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP1_TIME_CONF_1	(0x0144 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP1_TIME_CONF_2	(0x0148 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP1_TIME_CONF_3	(0x014C - MX3FB_REG_OFFSET)
#घोषणा DI_DISP2_TIME_CONF_1	(0x0150 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP2_TIME_CONF_2	(0x0154 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP2_TIME_CONF_3	(0x0158 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP3_TIME_CONF	(0x015C - MX3FB_REG_OFFSET)
#घोषणा DI_DISP0_DB0_MAP	(0x0160 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP0_DB1_MAP	(0x0164 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP0_DB2_MAP	(0x0168 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP0_CB0_MAP	(0x016C - MX3FB_REG_OFFSET)
#घोषणा DI_DISP0_CB1_MAP	(0x0170 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP0_CB2_MAP	(0x0174 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP1_DB0_MAP	(0x0178 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP1_DB1_MAP	(0x017C - MX3FB_REG_OFFSET)
#घोषणा DI_DISP1_DB2_MAP	(0x0180 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP1_CB0_MAP	(0x0184 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP1_CB1_MAP	(0x0188 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP1_CB2_MAP	(0x018C - MX3FB_REG_OFFSET)
#घोषणा DI_DISP2_DB0_MAP	(0x0190 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP2_DB1_MAP	(0x0194 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP2_DB2_MAP	(0x0198 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP2_CB0_MAP	(0x019C - MX3FB_REG_OFFSET)
#घोषणा DI_DISP2_CB1_MAP	(0x01A0 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP2_CB2_MAP	(0x01A4 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP3_B0_MAP		(0x01A8 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP3_B1_MAP		(0x01AC - MX3FB_REG_OFFSET)
#घोषणा DI_DISP3_B2_MAP		(0x01B0 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP_ACC_CC		(0x01B4 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP_LLA_CONF	(0x01B8 - MX3FB_REG_OFFSET)
#घोषणा DI_DISP_LLA_DATA	(0x01BC - MX3FB_REG_OFFSET)

/* DI_DISP_SIG_POL bits */
#घोषणा DI_D3_VSYNC_POL_SHIFT		28
#घोषणा DI_D3_HSYNC_POL_SHIFT		27
#घोषणा DI_D3_DRDY_SHARP_POL_SHIFT	26
#घोषणा DI_D3_CLK_POL_SHIFT		25
#घोषणा DI_D3_DATA_POL_SHIFT		24

/* DI_DISP_IF_CONF bits */
#घोषणा DI_D3_CLK_IDLE_SHIFT		26
#घोषणा DI_D3_CLK_SEL_SHIFT		25
#घोषणा DI_D3_DATAMSK_SHIFT		24

क्रमागत ipu_panel अणु
	IPU_PANEL_SHARP_TFT,
	IPU_PANEL_TFT,
पूर्ण;

काष्ठा ipu_di_संकेत_cfg अणु
	अचिन्हित datamask_en:1;
	अचिन्हित clksel_en:1;
	अचिन्हित clkidle_en:1;
	अचिन्हित data_pol:1;	/* true = inverted */
	अचिन्हित clk_pol:1;	/* true = rising edge */
	अचिन्हित enable_pol:1;
	अचिन्हित Hsync_pol:1;	/* true = active high */
	अचिन्हित Vsync_pol:1;
पूर्ण;

अटल स्थिर काष्ठा fb_videomode mx3fb_modedb[] = अणु
	अणु
		/* 240x320 @ 60 Hz */
		.name		= "Sharp-QVGA",
		.refresh	= 60,
		.xres		= 240,
		.yres		= 320,
		.pixघड़ी	= 185925,
		.left_margin	= 9,
		.right_margin	= 16,
		.upper_margin	= 7,
		.lower_margin	= 9,
		.hsync_len	= 1,
		.vsync_len	= 1,
		.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_SHARP_MODE |
				  FB_SYNC_CLK_INVERT | FB_SYNC_DATA_INVERT |
				  FB_SYNC_CLK_IDLE_EN,
		.vmode		= FB_VMODE_NONINTERLACED,
		.flag		= 0,
	पूर्ण, अणु
		/* 240x33 @ 60 Hz */
		.name		= "Sharp-CLI",
		.refresh	= 60,
		.xres		= 240,
		.yres		= 33,
		.pixघड़ी	= 185925,
		.left_margin	= 9,
		.right_margin	= 16,
		.upper_margin	= 7,
		.lower_margin	= 9 + 287,
		.hsync_len	= 1,
		.vsync_len	= 1,
		.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_SHARP_MODE |
				  FB_SYNC_CLK_INVERT | FB_SYNC_DATA_INVERT |
				  FB_SYNC_CLK_IDLE_EN,
		.vmode		= FB_VMODE_NONINTERLACED,
		.flag		= 0,
	पूर्ण, अणु
		/* 640x480 @ 60 Hz */
		.name		= "NEC-VGA",
		.refresh	= 60,
		.xres		= 640,
		.yres		= 480,
		.pixघड़ी	= 38255,
		.left_margin	= 144,
		.right_margin	= 0,
		.upper_margin	= 34,
		.lower_margin	= 40,
		.hsync_len	= 1,
		.vsync_len	= 1,
		.sync		= FB_SYNC_VERT_HIGH_ACT | FB_SYNC_OE_ACT_HIGH,
		.vmode		= FB_VMODE_NONINTERLACED,
		.flag		= 0,
	पूर्ण, अणु
		/* NTSC TV output */
		.name		= "TV-NTSC",
		.refresh	= 60,
		.xres		= 640,
		.yres		= 480,
		.pixघड़ी	= 37538,
		.left_margin	= 38,
		.right_margin	= 858 - 640 - 38 - 3,
		.upper_margin	= 36,
		.lower_margin	= 518 - 480 - 36 - 1,
		.hsync_len	= 3,
		.vsync_len	= 1,
		.sync		= 0,
		.vmode		= FB_VMODE_NONINTERLACED,
		.flag		= 0,
	पूर्ण, अणु
		/* PAL TV output */
		.name		= "TV-PAL",
		.refresh	= 50,
		.xres		= 640,
		.yres		= 480,
		.pixघड़ी	= 37538,
		.left_margin	= 38,
		.right_margin	= 960 - 640 - 38 - 32,
		.upper_margin	= 32,
		.lower_margin	= 555 - 480 - 32 - 3,
		.hsync_len	= 32,
		.vsync_len	= 3,
		.sync		= 0,
		.vmode		= FB_VMODE_NONINTERLACED,
		.flag		= 0,
	पूर्ण, अणु
		/* TV output VGA mode, 640x480 @ 65 Hz */
		.name		= "TV-VGA",
		.refresh	= 60,
		.xres		= 640,
		.yres		= 480,
		.pixघड़ी	= 40574,
		.left_margin	= 35,
		.right_margin	= 45,
		.upper_margin	= 9,
		.lower_margin	= 1,
		.hsync_len	= 46,
		.vsync_len	= 5,
		.sync		= 0,
		.vmode		= FB_VMODE_NONINTERLACED,
		.flag		= 0,
	पूर्ण,
पूर्ण;

काष्ठा mx3fb_data अणु
	काष्ठा fb_info		*fbi;
	पूर्णांक			backlight_level;
	व्योम __iomem		*reg_base;
	spinlock_t		lock;
	काष्ठा device		*dev;
	काष्ठा backlight_device	*bl;

	uपूर्णांक32_t		h_start_width;
	uपूर्णांक32_t		v_start_width;
	क्रमागत disp_data_mapping	disp_data_fmt;
पूर्ण;

काष्ठा dma_chan_request अणु
	काष्ठा mx3fb_data	*mx3fb;
	क्रमागत ipu_channel	id;
पूर्ण;

/* MX3 specअगरic framebuffer inक्रमmation. */
काष्ठा mx3fb_info अणु
	पूर्णांक				blank;
	क्रमागत ipu_channel		ipu_ch;
	uपूर्णांक32_t			cur_ipu_buf;

	u32				pseuकरो_palette[16];

	काष्ठा completion		flip_cmpl;
	काष्ठा mutex			mutex;	/* Protects fb-ops */
	काष्ठा mx3fb_data		*mx3fb;
	काष्ठा idmac_channel		*idmac_channel;
	काष्ठा dma_async_tx_descriptor	*txd;
	dma_cookie_t			cookie;
	काष्ठा scatterlist		sg[2];

	काष्ठा fb_var_screeninfo	cur_var; /* current var info */
पूर्ण;

अटल व्योम sdc_set_brightness(काष्ठा mx3fb_data *mx3fb, uपूर्णांक8_t value);
अटल u32 sdc_get_brightness(काष्ठा mx3fb_data *mx3fb);

अटल पूर्णांक mx3fb_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा mx3fb_data *fbd = bl_get_data(bl);

	वापस sdc_get_brightness(fbd);
पूर्ण

अटल पूर्णांक mx3fb_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा mx3fb_data *fbd = bl_get_data(bl);
	पूर्णांक brightness = bl->props.brightness;

	अगर (bl->props.घातer != FB_BLANK_UNBLANK)
		brightness = 0;
	अगर (bl->props.fb_blank != FB_BLANK_UNBLANK)
		brightness = 0;

	fbd->backlight_level = (fbd->backlight_level & ~0xFF) | brightness;

	sdc_set_brightness(fbd, fbd->backlight_level);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops mx3fb_lcdc_bl_ops = अणु
	.update_status = mx3fb_bl_update_status,
	.get_brightness = mx3fb_bl_get_brightness,
पूर्ण;

अटल व्योम mx3fb_init_backlight(काष्ठा mx3fb_data *fbd)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device	*bl;

	अगर (fbd->bl)
		वापस;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.max_brightness = 0xff;
	props.type = BACKLIGHT_RAW;
	sdc_set_brightness(fbd, fbd->backlight_level);

	bl = backlight_device_रेजिस्टर("mx3fb-bl", fbd->dev, fbd,
				       &mx3fb_lcdc_bl_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(fbd->dev, "error %ld on backlight register\n",
				PTR_ERR(bl));
		वापस;
	पूर्ण

	fbd->bl = bl;
	bl->props.घातer = FB_BLANK_UNBLANK;
	bl->props.fb_blank = FB_BLANK_UNBLANK;
	bl->props.brightness = mx3fb_bl_get_brightness(bl);
पूर्ण

अटल व्योम mx3fb_निकास_backlight(काष्ठा mx3fb_data *fbd)
अणु
	backlight_device_unरेजिस्टर(fbd->bl);
पूर्ण

अटल व्योम mx3fb_dma_करोne(व्योम *);

/* Used fb-mode and bpp. Can be set on kernel command line, thereक्रमe file-अटल. */
अटल स्थिर अक्षर *fb_mode;
अटल अचिन्हित दीर्घ शेष_bpp = 16;

अटल u32 mx3fb_पढ़ो_reg(काष्ठा mx3fb_data *mx3fb, अचिन्हित दीर्घ reg)
अणु
	वापस __raw_पढ़ोl(mx3fb->reg_base + reg);
पूर्ण

अटल व्योम mx3fb_ग_लिखो_reg(काष्ठा mx3fb_data *mx3fb, u32 value, अचिन्हित दीर्घ reg)
अणु
	__raw_ग_लिखोl(value, mx3fb->reg_base + reg);
पूर्ण

काष्ठा di_mapping अणु
	uपूर्णांक32_t b0, b1, b2;
पूर्ण;

अटल स्थिर काष्ठा di_mapping di_mappings[] = अणु
	[IPU_DISP_DATA_MAPPING_RGB666] = अणु 0x0005000f, 0x000b000f, 0x0011000f पूर्ण,
	[IPU_DISP_DATA_MAPPING_RGB565] = अणु 0x0004003f, 0x000a000f, 0x000f003f पूर्ण,
	[IPU_DISP_DATA_MAPPING_RGB888] = अणु 0x00070000, 0x000f0000, 0x00170000 पूर्ण,
पूर्ण;

अटल व्योम sdc_fb_init(काष्ठा mx3fb_info *fbi)
अणु
	काष्ठा mx3fb_data *mx3fb = fbi->mx3fb;
	uपूर्णांक32_t reg;

	reg = mx3fb_पढ़ो_reg(mx3fb, SDC_COM_CONF);

	mx3fb_ग_लिखो_reg(mx3fb, reg | SDC_COM_BG_EN, SDC_COM_CONF);
पूर्ण

/* Returns enabled flag beक्रमe uninit */
अटल uपूर्णांक32_t sdc_fb_uninit(काष्ठा mx3fb_info *fbi)
अणु
	काष्ठा mx3fb_data *mx3fb = fbi->mx3fb;
	uपूर्णांक32_t reg;

	reg = mx3fb_पढ़ो_reg(mx3fb, SDC_COM_CONF);

	mx3fb_ग_लिखो_reg(mx3fb, reg & ~SDC_COM_BG_EN, SDC_COM_CONF);

	वापस reg & SDC_COM_BG_EN;
पूर्ण

अटल व्योम sdc_enable_channel(काष्ठा mx3fb_info *mx3_fbi)
अणु
	काष्ठा mx3fb_data *mx3fb = mx3_fbi->mx3fb;
	काष्ठा idmac_channel *ichan = mx3_fbi->idmac_channel;
	काष्ठा dma_chan *dma_chan = &ichan->dma_chan;
	अचिन्हित दीर्घ flags;
	dma_cookie_t cookie;

	अगर (mx3_fbi->txd)
		dev_dbg(mx3fb->dev, "mx3fbi %p, desc %p, sg %p\n", mx3_fbi,
			to_tx_desc(mx3_fbi->txd), to_tx_desc(mx3_fbi->txd)->sg);
	अन्यथा
		dev_dbg(mx3fb->dev, "mx3fbi %p, txd = NULL\n", mx3_fbi);

	/* This enables the channel */
	अगर (mx3_fbi->cookie < 0) अणु
		mx3_fbi->txd = dmaengine_prep_slave_sg(dma_chan,
		      &mx3_fbi->sg[0], 1, DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT);
		अगर (!mx3_fbi->txd) अणु
			dev_err(mx3fb->dev, "Cannot allocate descriptor on %d\n",
				dma_chan->chan_id);
			वापस;
		पूर्ण

		mx3_fbi->txd->callback_param	= mx3_fbi->txd;
		mx3_fbi->txd->callback		= mx3fb_dma_करोne;

		cookie = mx3_fbi->txd->tx_submit(mx3_fbi->txd);
		dev_dbg(mx3fb->dev, "%d: Submit %p #%d [%c]\n", __LINE__,
		       mx3_fbi->txd, cookie, list_empty(&ichan->queue) ? '-' : '+');
	पूर्ण अन्यथा अणु
		अगर (!mx3_fbi->txd || !mx3_fbi->txd->tx_submit) अणु
			dev_err(mx3fb->dev, "Cannot enable channel %d\n",
				dma_chan->chan_id);
			वापस;
		पूर्ण

		/* Just re-activate the same buffer */
		dma_async_issue_pending(dma_chan);
		cookie = mx3_fbi->cookie;
		dev_dbg(mx3fb->dev, "%d: Re-submit %p #%d [%c]\n", __LINE__,
		       mx3_fbi->txd, cookie, list_empty(&ichan->queue) ? '-' : '+');
	पूर्ण

	अगर (cookie >= 0) अणु
		spin_lock_irqsave(&mx3fb->lock, flags);
		sdc_fb_init(mx3_fbi);
		mx3_fbi->cookie = cookie;
		spin_unlock_irqrestore(&mx3fb->lock, flags);
	पूर्ण

	/*
	 * Attention! Without this msleep the channel keeps generating
	 * पूर्णांकerrupts. Next sdc_set_brightness() is going to be called
	 * from mx3fb_blank().
	 */
	msleep(2);
पूर्ण

अटल व्योम sdc_disable_channel(काष्ठा mx3fb_info *mx3_fbi)
अणु
	काष्ठा mx3fb_data *mx3fb = mx3_fbi->mx3fb;
	अचिन्हित दीर्घ flags;

	अगर (mx3_fbi->txd == शून्य)
		वापस;

	spin_lock_irqsave(&mx3fb->lock, flags);

	sdc_fb_uninit(mx3_fbi);

	spin_unlock_irqrestore(&mx3fb->lock, flags);

	dmaengine_terminate_all(mx3_fbi->txd->chan);
	mx3_fbi->txd = शून्य;
	mx3_fbi->cookie = -EINVAL;
पूर्ण

/**
 * sdc_set_winकरोw_pos() - set winकरोw position of the respective plane.
 * @mx3fb:	mx3fb context.
 * @channel:	IPU DMAC channel ID.
 * @x_pos:	X coordinate relative to the top left corner to place winकरोw at.
 * @y_pos:	Y coordinate relative to the top left corner to place winकरोw at.
 * @वापस:	0 on success or negative error code on failure.
 */
अटल पूर्णांक sdc_set_winकरोw_pos(काष्ठा mx3fb_data *mx3fb, क्रमागत ipu_channel channel,
			      पूर्णांक16_t x_pos, पूर्णांक16_t y_pos)
अणु
	अगर (channel != IDMAC_SDC_0)
		वापस -EINVAL;

	x_pos += mx3fb->h_start_width;
	y_pos += mx3fb->v_start_width;

	mx3fb_ग_लिखो_reg(mx3fb, (x_pos << 16) | y_pos, SDC_BG_POS);
	वापस 0;
पूर्ण

/**
 * sdc_init_panel() - initialize a synchronous LCD panel.
 * @mx3fb:		mx3fb context.
 * @panel:		panel type.
 * @pixel_clk:		desired pixel घड़ी frequency in Hz.
 * @width:		width of panel in pixels.
 * @height:		height of panel in pixels.
 * @h_start_width:	number of pixel घड़ीs between the HSYNC संकेत pulse
 *			and the start of valid data.
 * @h_sync_width:	width of the HSYNC संकेत in units of pixel घड़ीs.
 * @h_end_width:	number of pixel घड़ीs between the end of valid data
 *			and the HSYNC संकेत क्रम next line.
 * @v_start_width:	number of lines between the VSYNC संकेत pulse and the
 *			start of valid data.
 * @v_sync_width:	width of the VSYNC संकेत in units of lines
 * @v_end_width:	number of lines between the end of valid data and the
 *			VSYNC संकेत क्रम next frame.
 * @sig:		bitfield of संकेत polarities क्रम LCD पूर्णांकerface.
 * @वापस:		0 on success or negative error code on failure.
 */
अटल पूर्णांक sdc_init_panel(काष्ठा mx3fb_data *mx3fb, क्रमागत ipu_panel panel,
			  uपूर्णांक32_t pixel_clk,
			  uपूर्णांक16_t width, uपूर्णांक16_t height,
			  uपूर्णांक16_t h_start_width, uपूर्णांक16_t h_sync_width,
			  uपूर्णांक16_t h_end_width, uपूर्णांक16_t v_start_width,
			  uपूर्णांक16_t v_sync_width, uपूर्णांक16_t v_end_width,
			  स्थिर काष्ठा ipu_di_संकेत_cfg *sig)
अणु
	अचिन्हित दीर्घ lock_flags;
	uपूर्णांक32_t reg;
	uपूर्णांक32_t old_conf;
	uपूर्णांक32_t भाग;
	काष्ठा clk *ipu_clk;
	स्थिर काष्ठा di_mapping *map;

	dev_dbg(mx3fb->dev, "panel size = %d x %d", width, height);

	अगर (v_sync_width == 0 || h_sync_width == 0)
		वापस -EINVAL;

	/* Init panel size and blanking periods */
	reg = ((uपूर्णांक32_t) (h_sync_width - 1) << 26) |
		((uपूर्णांक32_t) (width + h_start_width + h_end_width - 1) << 16);
	mx3fb_ग_लिखो_reg(mx3fb, reg, SDC_HOR_CONF);

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_CONT " hor_conf %x,", reg);
#पूर्ण_अगर

	reg = ((uपूर्णांक32_t) (v_sync_width - 1) << 26) | SDC_V_SYNC_WIDTH_L |
	    ((uपूर्णांक32_t) (height + v_start_width + v_end_width - 1) << 16);
	mx3fb_ग_लिखो_reg(mx3fb, reg, SDC_VER_CONF);

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_CONT " ver_conf %x\n", reg);
#पूर्ण_अगर

	mx3fb->h_start_width = h_start_width;
	mx3fb->v_start_width = v_start_width;

	चयन (panel) अणु
	हाल IPU_PANEL_SHARP_TFT:
		mx3fb_ग_लिखो_reg(mx3fb, 0x00FD0102L, SDC_SHARP_CONF_1);
		mx3fb_ग_लिखो_reg(mx3fb, 0x00F500F4L, SDC_SHARP_CONF_2);
		mx3fb_ग_लिखो_reg(mx3fb, SDC_COM_SHARP | SDC_COM_TFT_COLOR, SDC_COM_CONF);
		अवरोध;
	हाल IPU_PANEL_TFT:
		mx3fb_ग_लिखो_reg(mx3fb, SDC_COM_TFT_COLOR, SDC_COM_CONF);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Init घड़ीing */

	/*
	 * Calculate भागider: fractional part is 4 bits so simply multiple by
	 * 2^4 to get fractional part, as दीर्घ as we stay under ~250MHz and on
	 * i.MX31 it (HSP_CLK) is <= 178MHz. Currently 128.267MHz
	 */
	ipu_clk = clk_get(mx3fb->dev, शून्य);
	अगर (!IS_ERR(ipu_clk)) अणु
		भाग = clk_get_rate(ipu_clk) * 16 / pixel_clk;
		clk_put(ipu_clk);
	पूर्ण अन्यथा अणु
		भाग = 0;
	पूर्ण

	अगर (भाग < 0x40) अणु	/* Divider less than 4 */
		dev_dbg(mx3fb->dev,
			"InitPanel() - Pixel clock divider less than 4\n");
		भाग = 0x40;
	पूर्ण

	dev_dbg(mx3fb->dev, "pixel clk = %u, divider %u.%u\n",
		pixel_clk, भाग >> 4, (भाग & 7) * 125);

	spin_lock_irqsave(&mx3fb->lock, lock_flags);

	/*
	 * DISP3_IF_CLK_DOWN_WR is half the भागider value and 2 fraction bits
	 * fewer. Subtract 1 extra from DISP3_IF_CLK_DOWN_WR based on timing
	 * debug. DISP3_IF_CLK_UP_WR is 0
	 */
	mx3fb_ग_लिखो_reg(mx3fb, (((भाग / 8) - 1) << 22) | भाग, DI_DISP3_TIME_CONF);

	/* DI settings */
	old_conf = mx3fb_पढ़ो_reg(mx3fb, DI_DISP_IF_CONF) & 0x78FFFFFF;
	old_conf |= sig->datamask_en << DI_D3_DATAMSK_SHIFT |
		sig->clksel_en << DI_D3_CLK_SEL_SHIFT |
		sig->clkidle_en << DI_D3_CLK_IDLE_SHIFT;
	mx3fb_ग_लिखो_reg(mx3fb, old_conf, DI_DISP_IF_CONF);

	old_conf = mx3fb_पढ़ो_reg(mx3fb, DI_DISP_SIG_POL) & 0xE0FFFFFF;
	old_conf |= sig->data_pol << DI_D3_DATA_POL_SHIFT |
		sig->clk_pol << DI_D3_CLK_POL_SHIFT |
		sig->enable_pol << DI_D3_DRDY_SHARP_POL_SHIFT |
		sig->Hsync_pol << DI_D3_HSYNC_POL_SHIFT |
		sig->Vsync_pol << DI_D3_VSYNC_POL_SHIFT;
	mx3fb_ग_लिखो_reg(mx3fb, old_conf, DI_DISP_SIG_POL);

	map = &di_mappings[mx3fb->disp_data_fmt];
	mx3fb_ग_लिखो_reg(mx3fb, map->b0, DI_DISP3_B0_MAP);
	mx3fb_ग_लिखो_reg(mx3fb, map->b1, DI_DISP3_B1_MAP);
	mx3fb_ग_लिखो_reg(mx3fb, map->b2, DI_DISP3_B2_MAP);

	spin_unlock_irqrestore(&mx3fb->lock, lock_flags);

	dev_dbg(mx3fb->dev, "DI_DISP_IF_CONF = 0x%08X\n",
		mx3fb_पढ़ो_reg(mx3fb, DI_DISP_IF_CONF));
	dev_dbg(mx3fb->dev, "DI_DISP_SIG_POL = 0x%08X\n",
		mx3fb_पढ़ो_reg(mx3fb, DI_DISP_SIG_POL));
	dev_dbg(mx3fb->dev, "DI_DISP3_TIME_CONF = 0x%08X\n",
		mx3fb_पढ़ो_reg(mx3fb, DI_DISP3_TIME_CONF));

	वापस 0;
पूर्ण

/**
 * sdc_set_color_key() - set the transparent color key क्रम SDC graphic plane.
 * @mx3fb:	mx3fb context.
 * @channel:	IPU DMAC channel ID.
 * @enable:	boolean to enable or disable color keyl.
 * @color_key:	24-bit RGB color to use as transparent color key.
 * @वापस:	0 on success or negative error code on failure.
 */
अटल पूर्णांक sdc_set_color_key(काष्ठा mx3fb_data *mx3fb, क्रमागत ipu_channel channel,
			     bool enable, uपूर्णांक32_t color_key)
अणु
	uपूर्णांक32_t reg, sdc_conf;
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(&mx3fb->lock, lock_flags);

	sdc_conf = mx3fb_पढ़ो_reg(mx3fb, SDC_COM_CONF);
	अगर (channel == IDMAC_SDC_0)
		sdc_conf &= ~SDC_COM_GWSEL;
	अन्यथा
		sdc_conf |= SDC_COM_GWSEL;

	अगर (enable) अणु
		reg = mx3fb_पढ़ो_reg(mx3fb, SDC_GW_CTRL) & 0xFF000000L;
		mx3fb_ग_लिखो_reg(mx3fb, reg | (color_key & 0x00FFFFFFL),
			     SDC_GW_CTRL);

		sdc_conf |= SDC_COM_KEY_COLOR_G;
	पूर्ण अन्यथा अणु
		sdc_conf &= ~SDC_COM_KEY_COLOR_G;
	पूर्ण
	mx3fb_ग_लिखो_reg(mx3fb, sdc_conf, SDC_COM_CONF);

	spin_unlock_irqrestore(&mx3fb->lock, lock_flags);

	वापस 0;
पूर्ण

/**
 * sdc_set_global_alpha() - set global alpha blending modes.
 * @mx3fb:	mx3fb context.
 * @enable:	boolean to enable or disable global alpha blending. If disabled,
 *		per pixel blending is used.
 * @alpha:	global alpha value.
 * @वापस:	0 on success or negative error code on failure.
 */
अटल पूर्णांक sdc_set_global_alpha(काष्ठा mx3fb_data *mx3fb, bool enable, uपूर्णांक8_t alpha)
अणु
	uपूर्णांक32_t reg;
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(&mx3fb->lock, lock_flags);

	अगर (enable) अणु
		reg = mx3fb_पढ़ो_reg(mx3fb, SDC_GW_CTRL) & 0x00FFFFFFL;
		mx3fb_ग_लिखो_reg(mx3fb, reg | ((uपूर्णांक32_t) alpha << 24), SDC_GW_CTRL);

		reg = mx3fb_पढ़ो_reg(mx3fb, SDC_COM_CONF);
		mx3fb_ग_लिखो_reg(mx3fb, reg | SDC_COM_GLB_A, SDC_COM_CONF);
	पूर्ण अन्यथा अणु
		reg = mx3fb_पढ़ो_reg(mx3fb, SDC_COM_CONF);
		mx3fb_ग_लिखो_reg(mx3fb, reg & ~SDC_COM_GLB_A, SDC_COM_CONF);
	पूर्ण

	spin_unlock_irqrestore(&mx3fb->lock, lock_flags);

	वापस 0;
पूर्ण

अटल u32 sdc_get_brightness(काष्ठा mx3fb_data *mx3fb)
अणु
	u32 brightness;

	brightness = mx3fb_पढ़ो_reg(mx3fb, SDC_PWM_CTRL);
	brightness = (brightness >> 16) & 0xFF;

	वापस brightness;
पूर्ण

अटल व्योम sdc_set_brightness(काष्ठा mx3fb_data *mx3fb, uपूर्णांक8_t value)
अणु
	dev_dbg(mx3fb->dev, "%s: value = %d\n", __func__, value);
	/* This might be board-specअगरic */
	mx3fb_ग_लिखो_reg(mx3fb, 0x03000000UL | value << 16, SDC_PWM_CTRL);
	वापस;
पूर्ण

अटल uपूर्णांक32_t bpp_to_pixfmt(पूर्णांक bpp)
अणु
	uपूर्णांक32_t pixfmt = 0;
	चयन (bpp) अणु
	हाल 24:
		pixfmt = IPU_PIX_FMT_BGR24;
		अवरोध;
	हाल 32:
		pixfmt = IPU_PIX_FMT_BGR32;
		अवरोध;
	हाल 16:
		pixfmt = IPU_PIX_FMT_RGB565;
		अवरोध;
	पूर्ण
	वापस pixfmt;
पूर्ण

अटल पूर्णांक mx3fb_blank(पूर्णांक blank, काष्ठा fb_info *fbi);
अटल पूर्णांक mx3fb_map_video_memory(काष्ठा fb_info *fbi, अचिन्हित पूर्णांक mem_len,
				  bool lock);
अटल पूर्णांक mx3fb_unmap_video_memory(काष्ठा fb_info *fbi);

/**
 * mx3fb_set_fix() - set fixed framebuffer parameters from variable settings.
 * @fbi:	framebuffer inक्रमmation poपूर्णांकer
 * @वापस:	0 on success or negative error code on failure.
 */
अटल पूर्णांक mx3fb_set_fix(काष्ठा fb_info *fbi)
अणु
	काष्ठा fb_fix_screeninfo *fix = &fbi->fix;
	काष्ठा fb_var_screeninfo *var = &fbi->var;

	स_नकल(fix->id, "DISP3 BG", 8);

	fix->line_length = var->xres_भव * var->bits_per_pixel / 8;

	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->accel = FB_ACCEL_NONE;
	fix->visual = FB_VISUAL_TRUECOLOR;
	fix->xpanstep = 1;
	fix->ypanstep = 1;

	वापस 0;
पूर्ण

अटल व्योम mx3fb_dma_करोne(व्योम *arg)
अणु
	काष्ठा idmac_tx_desc *tx_desc = to_tx_desc(arg);
	काष्ठा dma_chan *chan = tx_desc->txd.chan;
	काष्ठा idmac_channel *ichannel = to_idmac_chan(chan);
	काष्ठा mx3fb_data *mx3fb = ichannel->client;
	काष्ठा mx3fb_info *mx3_fbi = mx3fb->fbi->par;

	dev_dbg(mx3fb->dev, "irq %d callback\n", ichannel->eof_irq);

	/* We only need one पूर्णांकerrupt, it will be re-enabled as needed */
	disable_irq_nosync(ichannel->eof_irq);

	complete(&mx3_fbi->flip_cmpl);
पूर्ण

अटल bool mx3fb_must_set_par(काष्ठा fb_info *fbi)
अणु
	काष्ठा mx3fb_info *mx3_fbi = fbi->par;
	काष्ठा fb_var_screeninfo old_var = mx3_fbi->cur_var;
	काष्ठा fb_var_screeninfo new_var = fbi->var;

	अगर ((fbi->var.activate & FB_ACTIVATE_FORCE) &&
	    (fbi->var.activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW)
		वापस true;

	/*
	 * Ignore xoffset and yoffset update,
	 * because pan display handles this हाल.
	 */
	old_var.xoffset = new_var.xoffset;
	old_var.yoffset = new_var.yoffset;

	वापस !!स_भेद(&old_var, &new_var, माप(काष्ठा fb_var_screeninfo));
पूर्ण

अटल पूर्णांक __set_par(काष्ठा fb_info *fbi, bool lock)
अणु
	u32 mem_len, cur_xoffset, cur_yoffset;
	काष्ठा ipu_di_संकेत_cfg sig_cfg;
	क्रमागत ipu_panel mode = IPU_PANEL_TFT;
	काष्ठा mx3fb_info *mx3_fbi = fbi->par;
	काष्ठा mx3fb_data *mx3fb = mx3_fbi->mx3fb;
	काष्ठा idmac_channel *ichan = mx3_fbi->idmac_channel;
	काष्ठा idmac_video_param *video = &ichan->params.video;
	काष्ठा scatterlist *sg = mx3_fbi->sg;

	/* Total cleanup */
	अगर (mx3_fbi->txd)
		sdc_disable_channel(mx3_fbi);

	mx3fb_set_fix(fbi);

	mem_len = fbi->var.yres_भव * fbi->fix.line_length;
	अगर (mem_len > fbi->fix.smem_len) अणु
		अगर (fbi->fix.smem_start)
			mx3fb_unmap_video_memory(fbi);

		अगर (mx3fb_map_video_memory(fbi, mem_len, lock) < 0)
			वापस -ENOMEM;
	पूर्ण

	sg_init_table(&sg[0], 1);
	sg_init_table(&sg[1], 1);

	sg_dma_address(&sg[0]) = fbi->fix.smem_start;
	sg_set_page(&sg[0], virt_to_page(fbi->screen_base),
		    fbi->fix.smem_len,
		    offset_in_page(fbi->screen_base));

	अगर (mx3_fbi->ipu_ch == IDMAC_SDC_0) अणु
		स_रखो(&sig_cfg, 0, माप(sig_cfg));
		अगर (fbi->var.sync & FB_SYNC_HOR_HIGH_ACT)
			sig_cfg.Hsync_pol = true;
		अगर (fbi->var.sync & FB_SYNC_VERT_HIGH_ACT)
			sig_cfg.Vsync_pol = true;
		अगर (fbi->var.sync & FB_SYNC_CLK_INVERT)
			sig_cfg.clk_pol = true;
		अगर (fbi->var.sync & FB_SYNC_DATA_INVERT)
			sig_cfg.data_pol = true;
		अगर (fbi->var.sync & FB_SYNC_OE_ACT_HIGH)
			sig_cfg.enable_pol = true;
		अगर (fbi->var.sync & FB_SYNC_CLK_IDLE_EN)
			sig_cfg.clkidle_en = true;
		अगर (fbi->var.sync & FB_SYNC_CLK_SEL_EN)
			sig_cfg.clksel_en = true;
		अगर (fbi->var.sync & FB_SYNC_SHARP_MODE)
			mode = IPU_PANEL_SHARP_TFT;

		dev_dbg(fbi->device, "pixclock = %u Hz\n",
			(u32) (PICOS2KHZ(fbi->var.pixघड़ी) * 1000UL));

		अगर (sdc_init_panel(mx3fb, mode,
				   (PICOS2KHZ(fbi->var.pixघड़ी)) * 1000UL,
				   fbi->var.xres, fbi->var.yres,
				   fbi->var.left_margin,
				   fbi->var.hsync_len,
				   fbi->var.right_margin +
				   fbi->var.hsync_len,
				   fbi->var.upper_margin,
				   fbi->var.vsync_len,
				   fbi->var.lower_margin +
				   fbi->var.vsync_len, &sig_cfg) != 0) अणु
			dev_err(fbi->device,
				"mx3fb: Error initializing panel.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	sdc_set_winकरोw_pos(mx3fb, mx3_fbi->ipu_ch, 0, 0);

	mx3_fbi->cur_ipu_buf	= 0;

	video->out_pixel_fmt	= bpp_to_pixfmt(fbi->var.bits_per_pixel);
	video->out_width	= fbi->var.xres;
	video->out_height	= fbi->var.yres;
	video->out_stride	= fbi->var.xres_भव;

	अगर (mx3_fbi->blank == FB_BLANK_UNBLANK) अणु
		sdc_enable_channel(mx3_fbi);
		/*
		 * sg[0] poपूर्णांकs to fb smem_start address
		 * and is actually active in controller.
		 */
		mx3_fbi->cur_var.xoffset = 0;
		mx3_fbi->cur_var.yoffset = 0;
	पूर्ण

	/*
	 * Preserve xoffset and yoffest in हाल they are
	 * inactive in controller as fb is blanked.
	 */
	cur_xoffset = mx3_fbi->cur_var.xoffset;
	cur_yoffset = mx3_fbi->cur_var.yoffset;
	mx3_fbi->cur_var = fbi->var;
	mx3_fbi->cur_var.xoffset = cur_xoffset;
	mx3_fbi->cur_var.yoffset = cur_yoffset;

	वापस 0;
पूर्ण

/**
 * mx3fb_set_par() - set framebuffer parameters and change the operating mode.
 * @fbi:	framebuffer inक्रमmation poपूर्णांकer.
 * @वापस:	0 on success or negative error code on failure.
 */
अटल पूर्णांक mx3fb_set_par(काष्ठा fb_info *fbi)
अणु
	काष्ठा mx3fb_info *mx3_fbi = fbi->par;
	काष्ठा mx3fb_data *mx3fb = mx3_fbi->mx3fb;
	काष्ठा idmac_channel *ichan = mx3_fbi->idmac_channel;
	पूर्णांक ret;

	dev_dbg(mx3fb->dev, "%s [%c]\n", __func__, list_empty(&ichan->queue) ? '-' : '+');

	mutex_lock(&mx3_fbi->mutex);

	ret = mx3fb_must_set_par(fbi) ? __set_par(fbi, true) : 0;

	mutex_unlock(&mx3_fbi->mutex);

	वापस ret;
पूर्ण

/**
 * mx3fb_check_var() - check and adjust framebuffer variable parameters.
 * @var:	framebuffer variable parameters
 * @fbi:	framebuffer inक्रमmation poपूर्णांकer
 */
अटल पूर्णांक mx3fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *fbi)
अणु
	काष्ठा mx3fb_info *mx3_fbi = fbi->par;
	u32 vtotal;
	u32 htotal;

	dev_dbg(fbi->device, "%s\n", __func__);

	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;

	अगर ((var->bits_per_pixel != 32) && (var->bits_per_pixel != 24) &&
	    (var->bits_per_pixel != 16))
		var->bits_per_pixel = शेष_bpp;

	चयन (var->bits_per_pixel) अणु
	हाल 16:
		var->red.length = 5;
		var->red.offset = 11;
		var->red.msb_right = 0;

		var->green.length = 6;
		var->green.offset = 5;
		var->green.msb_right = 0;

		var->blue.length = 5;
		var->blue.offset = 0;
		var->blue.msb_right = 0;

		var->transp.length = 0;
		var->transp.offset = 0;
		var->transp.msb_right = 0;
		अवरोध;
	हाल 24:
		var->red.length = 8;
		var->red.offset = 16;
		var->red.msb_right = 0;

		var->green.length = 8;
		var->green.offset = 8;
		var->green.msb_right = 0;

		var->blue.length = 8;
		var->blue.offset = 0;
		var->blue.msb_right = 0;

		var->transp.length = 0;
		var->transp.offset = 0;
		var->transp.msb_right = 0;
		अवरोध;
	हाल 32:
		var->red.length = 8;
		var->red.offset = 16;
		var->red.msb_right = 0;

		var->green.length = 8;
		var->green.offset = 8;
		var->green.msb_right = 0;

		var->blue.length = 8;
		var->blue.offset = 0;
		var->blue.msb_right = 0;

		var->transp.length = 8;
		var->transp.offset = 24;
		var->transp.msb_right = 0;
		अवरोध;
	पूर्ण

	अगर (var->pixघड़ी < 1000) अणु
		htotal = var->xres + var->right_margin + var->hsync_len +
		    var->left_margin;
		vtotal = var->yres + var->lower_margin + var->vsync_len +
		    var->upper_margin;
		var->pixघड़ी = (vtotal * htotal * 6UL) / 100UL;
		var->pixघड़ी = KHZ2PICOS(var->pixघड़ी);
		dev_dbg(fbi->device, "pixclock set for 60Hz refresh = %u ps\n",
			var->pixघड़ी);
	पूर्ण

	var->height = -1;
	var->width = -1;
	var->grayscale = 0;

	/* Preserve sync flags */
	var->sync |= mx3_fbi->cur_var.sync;
	mx3_fbi->cur_var.sync |= var->sync;

	वापस 0;
पूर्ण

अटल u32 chan_to_field(अचिन्हित पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक mx3fb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			   अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			   अचिन्हित पूर्णांक trans, काष्ठा fb_info *fbi)
अणु
	काष्ठा mx3fb_info *mx3_fbi = fbi->par;
	u32 val;
	पूर्णांक ret = 1;

	dev_dbg(fbi->device, "%s, regno = %u\n", __func__, regno);

	mutex_lock(&mx3_fbi->mutex);
	/*
	 * If greyscale is true, then we convert the RGB value
	 * to greyscale no matter what visual we are using.
	 */
	अगर (fbi->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
				      7471 * blue) >> 16;
	चयन (fbi->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		/*
		 * 16-bit True Colour.  We encode the RGB value
		 * according to the RGB bitfield inक्रमmation.
		 */
		अगर (regno < 16) अणु
			u32 *pal = fbi->pseuकरो_palette;

			val = chan_to_field(red, &fbi->var.red);
			val |= chan_to_field(green, &fbi->var.green);
			val |= chan_to_field(blue, &fbi->var.blue);

			pal[regno] = val;

			ret = 0;
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_STATIC_PSEUDOCOLOR:
	हाल FB_VISUAL_PSEUDOCOLOR:
		अवरोध;
	पूर्ण
	mutex_unlock(&mx3_fbi->mutex);

	वापस ret;
पूर्ण

अटल व्योम __blank(पूर्णांक blank, काष्ठा fb_info *fbi)
अणु
	काष्ठा mx3fb_info *mx3_fbi = fbi->par;
	काष्ठा mx3fb_data *mx3fb = mx3_fbi->mx3fb;
	पूर्णांक was_blank = mx3_fbi->blank;

	mx3_fbi->blank = blank;

	/* Attention!
	 * Do not call sdc_disable_channel() क्रम a channel that is disabled
	 * alपढ़ोy! This will result in a kernel शून्य poपूर्णांकer dereference
	 * (mx3_fbi->txd is शून्य). Hide the fact, that all blank modes are
	 * handled equally by this driver.
	 */
	अगर (blank > FB_BLANK_UNBLANK && was_blank > FB_BLANK_UNBLANK)
		वापस;

	चयन (blank) अणु
	हाल FB_BLANK_POWERDOWN:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_NORMAL:
		sdc_set_brightness(mx3fb, 0);
		स_रखो((अक्षर *)fbi->screen_base, 0, fbi->fix.smem_len);
		/* Give LCD समय to update - enough क्रम 50 and 60 Hz */
		msleep(25);
		sdc_disable_channel(mx3_fbi);
		अवरोध;
	हाल FB_BLANK_UNBLANK:
		sdc_enable_channel(mx3_fbi);
		sdc_set_brightness(mx3fb, mx3fb->backlight_level);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * mx3fb_blank() - blank the display.
 * @blank:	blank value क्रम the panel
 * @fbi:	framebuffer inक्रमmation poपूर्णांकer
 */
अटल पूर्णांक mx3fb_blank(पूर्णांक blank, काष्ठा fb_info *fbi)
अणु
	काष्ठा mx3fb_info *mx3_fbi = fbi->par;

	dev_dbg(fbi->device, "%s, blank = %d, base %p, len %u\n", __func__,
		blank, fbi->screen_base, fbi->fix.smem_len);

	अगर (mx3_fbi->blank == blank)
		वापस 0;

	mutex_lock(&mx3_fbi->mutex);
	__blank(blank, fbi);
	mutex_unlock(&mx3_fbi->mutex);

	वापस 0;
पूर्ण

/**
 * mx3fb_pan_display() - pan or wrap the display
 * @var:	variable screen buffer inक्रमmation.
 * @fbi:	framebuffer inक्रमmation poपूर्णांकer.
 *
 * We look only at xoffset, yoffset and the FB_VMODE_YWRAP flag
 */
अटल पूर्णांक mx3fb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *fbi)
अणु
	काष्ठा mx3fb_info *mx3_fbi = fbi->par;
	u32 y_bottom;
	अचिन्हित दीर्घ base;
	off_t offset;
	dma_cookie_t cookie;
	काष्ठा scatterlist *sg = mx3_fbi->sg;
	काष्ठा dma_chan *dma_chan = &mx3_fbi->idmac_channel->dma_chan;
	काष्ठा dma_async_tx_descriptor *txd;
	पूर्णांक ret;

	dev_dbg(fbi->device, "%s [%c]\n", __func__,
		list_empty(&mx3_fbi->idmac_channel->queue) ? '-' : '+');

	अगर (var->xoffset > 0) अणु
		dev_dbg(fbi->device, "x panning not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mx3_fbi->cur_var.xoffset == var->xoffset &&
	    mx3_fbi->cur_var.yoffset == var->yoffset)
		वापस 0;	/* No change, करो nothing */

	y_bottom = var->yoffset;

	अगर (!(var->vmode & FB_VMODE_YWRAP))
		y_bottom += fbi->var.yres;

	अगर (y_bottom > fbi->var.yres_भव)
		वापस -EINVAL;

	mutex_lock(&mx3_fbi->mutex);

	offset = var->yoffset * fbi->fix.line_length
	       + var->xoffset * (fbi->var.bits_per_pixel / 8);
	base = fbi->fix.smem_start + offset;

	dev_dbg(fbi->device, "Updating SDC BG buf %d address=0x%08lX\n",
		mx3_fbi->cur_ipu_buf, base);

	/*
	 * We enable the End of Frame पूर्णांकerrupt, which will मुक्त a tx-descriptor,
	 * which we will need क्रम the next dmaengine_prep_slave_sg(). The
	 * IRQ-handler will disable the IRQ again.
	 */
	init_completion(&mx3_fbi->flip_cmpl);
	enable_irq(mx3_fbi->idmac_channel->eof_irq);

	ret = रुको_क्रम_completion_समयout(&mx3_fbi->flip_cmpl, HZ / 10);
	अगर (ret <= 0) अणु
		mutex_unlock(&mx3_fbi->mutex);
		dev_info(fbi->device, "Panning failed due to %s\n", ret < 0 ?
			 "user interrupt" : "timeout");
		disable_irq(mx3_fbi->idmac_channel->eof_irq);
		वापस ret ? : -ETIMEDOUT;
	पूर्ण

	mx3_fbi->cur_ipu_buf = !mx3_fbi->cur_ipu_buf;

	sg_dma_address(&sg[mx3_fbi->cur_ipu_buf]) = base;
	sg_set_page(&sg[mx3_fbi->cur_ipu_buf],
		    virt_to_page(fbi->screen_base + offset), fbi->fix.smem_len,
		    offset_in_page(fbi->screen_base + offset));

	अगर (mx3_fbi->txd)
		async_tx_ack(mx3_fbi->txd);

	txd = dmaengine_prep_slave_sg(dma_chan, sg +
		mx3_fbi->cur_ipu_buf, 1, DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT);
	अगर (!txd) अणु
		dev_err(fbi->device,
			"Error preparing a DMA transaction descriptor.\n");
		mutex_unlock(&mx3_fbi->mutex);
		वापस -EIO;
	पूर्ण

	txd->callback_param	= txd;
	txd->callback		= mx3fb_dma_करोne;

	/*
	 * Emulate original mx3fb behaviour: each new call to idmac_tx_submit()
	 * should चयन to another buffer
	 */
	cookie = txd->tx_submit(txd);
	dev_dbg(fbi->device, "%d: Submit %p #%d\n", __LINE__, txd, cookie);
	अगर (cookie < 0) अणु
		dev_err(fbi->device,
			"Error updating SDC buf %d to address=0x%08lX\n",
			mx3_fbi->cur_ipu_buf, base);
		mutex_unlock(&mx3_fbi->mutex);
		वापस -EIO;
	पूर्ण

	mx3_fbi->txd = txd;

	fbi->var.xoffset = var->xoffset;
	fbi->var.yoffset = var->yoffset;

	अगर (var->vmode & FB_VMODE_YWRAP)
		fbi->var.vmode |= FB_VMODE_YWRAP;
	अन्यथा
		fbi->var.vmode &= ~FB_VMODE_YWRAP;

	mx3_fbi->cur_var = fbi->var;

	mutex_unlock(&mx3_fbi->mutex);

	dev_dbg(fbi->device, "Update complete\n");

	वापस 0;
पूर्ण

/*
 * This काष्ठाure contains the poपूर्णांकers to the control functions that are
 * invoked by the core framebuffer driver to perक्रमm operations like
 * blitting, rectangle filling, copy regions and cursor definition.
 */
अटल स्थिर काष्ठा fb_ops mx3fb_ops = अणु
	.owner = THIS_MODULE,
	.fb_set_par = mx3fb_set_par,
	.fb_check_var = mx3fb_check_var,
	.fb_setcolreg = mx3fb_setcolreg,
	.fb_pan_display = mx3fb_pan_display,
	.fb_fillrect = cfb_fillrect,
	.fb_copyarea = cfb_copyarea,
	.fb_imageblit = cfb_imageblit,
	.fb_blank = mx3fb_blank,
पूर्ण;

#अगर_घोषित CONFIG_PM
/*
 * Power management hooks.      Note that we won't be called from IRQ context,
 * unlike the blank functions above, so we may sleep.
 */

/*
 * Suspends the framebuffer and blanks the screen. Power management support
 */
अटल पूर्णांक mx3fb_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा mx3fb_data *mx3fb = platक्रमm_get_drvdata(pdev);
	काष्ठा mx3fb_info *mx3_fbi = mx3fb->fbi->par;

	console_lock();
	fb_set_suspend(mx3fb->fbi, 1);
	console_unlock();

	अगर (mx3_fbi->blank == FB_BLANK_UNBLANK) अणु
		sdc_disable_channel(mx3_fbi);
		sdc_set_brightness(mx3fb, 0);

	पूर्ण
	वापस 0;
पूर्ण

/*
 * Resumes the framebuffer and unblanks the screen. Power management support
 */
अटल पूर्णांक mx3fb_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mx3fb_data *mx3fb = platक्रमm_get_drvdata(pdev);
	काष्ठा mx3fb_info *mx3_fbi = mx3fb->fbi->par;

	अगर (mx3_fbi->blank == FB_BLANK_UNBLANK) अणु
		sdc_enable_channel(mx3_fbi);
		sdc_set_brightness(mx3fb, mx3fb->backlight_level);
	पूर्ण

	console_lock();
	fb_set_suspend(mx3fb->fbi, 0);
	console_unlock();

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा mx3fb_suspend   शून्य
#घोषणा mx3fb_resume    शून्य
#पूर्ण_अगर

/*
 * Main framebuffer functions
 */

/**
 * mx3fb_map_video_memory() - allocates the DRAM memory क्रम the frame buffer.
 * @fbi:	framebuffer inक्रमmation poपूर्णांकer
 * @mem_len:	length of mapped memory
 * @lock:	करो not lock during initialisation
 * @वापस:	Error code indicating success or failure
 *
 * This buffer is remapped पूर्णांकo a non-cached, non-buffered, memory region to
 * allow palette and pixel ग_लिखोs to occur without flushing the cache. Once this
 * area is remapped, all भव memory access to the video memory should occur
 * at the new region.
 */
अटल पूर्णांक mx3fb_map_video_memory(काष्ठा fb_info *fbi, अचिन्हित पूर्णांक mem_len,
				  bool lock)
अणु
	पूर्णांक retval = 0;
	dma_addr_t addr;

	fbi->screen_base = dma_alloc_wc(fbi->device, mem_len, &addr,
					GFP_DMA | GFP_KERNEL);

	अगर (!fbi->screen_base) अणु
		dev_err(fbi->device, "Cannot allocate %u bytes framebuffer memory\n",
			mem_len);
		retval = -EBUSY;
		जाओ err0;
	पूर्ण

	अगर (lock)
		mutex_lock(&fbi->mm_lock);
	fbi->fix.smem_start = addr;
	fbi->fix.smem_len = mem_len;
	अगर (lock)
		mutex_unlock(&fbi->mm_lock);

	dev_dbg(fbi->device, "allocated fb @ p=0x%08x, v=0x%p, size=%d.\n",
		(uपूर्णांक32_t) fbi->fix.smem_start, fbi->screen_base, fbi->fix.smem_len);

	fbi->screen_size = fbi->fix.smem_len;

	/* Clear the screen */
	स_रखो((अक्षर *)fbi->screen_base, 0, fbi->fix.smem_len);

	वापस 0;

err0:
	fbi->fix.smem_len = 0;
	fbi->fix.smem_start = 0;
	fbi->screen_base = शून्य;
	वापस retval;
पूर्ण

/**
 * mx3fb_unmap_video_memory() - de-allocate frame buffer memory.
 * @fbi:	framebuffer inक्रमmation poपूर्णांकer
 * @वापस:	error code indicating success or failure
 */
अटल पूर्णांक mx3fb_unmap_video_memory(काष्ठा fb_info *fbi)
अणु
	dma_मुक्त_wc(fbi->device, fbi->fix.smem_len, fbi->screen_base,
		    fbi->fix.smem_start);

	fbi->screen_base = शून्य;
	mutex_lock(&fbi->mm_lock);
	fbi->fix.smem_start = 0;
	fbi->fix.smem_len = 0;
	mutex_unlock(&fbi->mm_lock);
	वापस 0;
पूर्ण

/**
 * mx3fb_init_fbinfo() - initialize framebuffer inक्रमmation object.
 * @dev: the device
 * @ops:	framebuffer device operations
 * @वापस:	initialized framebuffer काष्ठाure.
 */
अटल काष्ठा fb_info *mx3fb_init_fbinfo(काष्ठा device *dev,
					 स्थिर काष्ठा fb_ops *ops)
अणु
	काष्ठा fb_info *fbi;
	काष्ठा mx3fb_info *mx3fbi;
	पूर्णांक ret;

	/* Allocate sufficient memory क्रम the fb काष्ठाure */
	fbi = framebuffer_alloc(माप(काष्ठा mx3fb_info), dev);
	अगर (!fbi)
		वापस शून्य;

	mx3fbi			= fbi->par;
	mx3fbi->cookie		= -EINVAL;
	mx3fbi->cur_ipu_buf	= 0;

	fbi->var.activate	= FB_ACTIVATE_NOW;

	fbi->fbops		= ops;
	fbi->flags		= FBINFO_FLAG_DEFAULT;
	fbi->pseuकरो_palette	= mx3fbi->pseuकरो_palette;

	mutex_init(&mx3fbi->mutex);

	/* Allocate colormap */
	ret = fb_alloc_cmap(&fbi->cmap, 16, 0);
	अगर (ret < 0) अणु
		framebuffer_release(fbi);
		वापस शून्य;
	पूर्ण

	वापस fbi;
पूर्ण

अटल पूर्णांक init_fb_chan(काष्ठा mx3fb_data *mx3fb, काष्ठा idmac_channel *ichan)
अणु
	काष्ठा device *dev = mx3fb->dev;
	काष्ठा mx3fb_platक्रमm_data *mx3fb_pdata = dev_get_platdata(dev);
	स्थिर अक्षर *name = mx3fb_pdata->name;
	काष्ठा fb_info *fbi;
	काष्ठा mx3fb_info *mx3fbi;
	स्थिर काष्ठा fb_videomode *mode;
	पूर्णांक ret, num_modes;

	अगर (mx3fb_pdata->disp_data_fmt >= ARRAY_SIZE(di_mappings)) अणु
		dev_err(dev, "Illegal display data format %d\n",
				mx3fb_pdata->disp_data_fmt);
		वापस -EINVAL;
	पूर्ण

	ichan->client = mx3fb;

	अगर (ichan->dma_chan.chan_id != IDMAC_SDC_0)
		वापस -EINVAL;

	fbi = mx3fb_init_fbinfo(dev, &mx3fb_ops);
	अगर (!fbi)
		वापस -ENOMEM;

	अगर (!fb_mode)
		fb_mode = name;

	अगर (!fb_mode) अणु
		ret = -EINVAL;
		जाओ emode;
	पूर्ण

	अगर (mx3fb_pdata->mode && mx3fb_pdata->num_modes) अणु
		mode = mx3fb_pdata->mode;
		num_modes = mx3fb_pdata->num_modes;
	पूर्ण अन्यथा अणु
		mode = mx3fb_modedb;
		num_modes = ARRAY_SIZE(mx3fb_modedb);
	पूर्ण

	अगर (!fb_find_mode(&fbi->var, fbi, fb_mode, mode,
			  num_modes, शून्य, शेष_bpp)) अणु
		ret = -EBUSY;
		जाओ emode;
	पूर्ण

	fb_videomode_to_modelist(mode, num_modes, &fbi->modelist);

	/* Default Y भव size is 2x panel size */
	fbi->var.yres_भव = fbi->var.yres * 2;

	mx3fb->fbi = fbi;

	/* set Display Interface घड़ी period */
	mx3fb_ग_लिखो_reg(mx3fb, 0x00100010L, DI_HSP_CLK_PER);
	/* Might need to trigger HSP घड़ी change - see 44.3.3.8.5 */

	sdc_set_brightness(mx3fb, 255);
	sdc_set_global_alpha(mx3fb, true, 0xFF);
	sdc_set_color_key(mx3fb, IDMAC_SDC_0, false, 0);

	mx3fbi			= fbi->par;
	mx3fbi->idmac_channel	= ichan;
	mx3fbi->ipu_ch		= ichan->dma_chan.chan_id;
	mx3fbi->mx3fb		= mx3fb;
	mx3fbi->blank		= FB_BLANK_NORMAL;

	mx3fb->disp_data_fmt	= mx3fb_pdata->disp_data_fmt;

	init_completion(&mx3fbi->flip_cmpl);
	disable_irq(ichan->eof_irq);
	dev_dbg(mx3fb->dev, "disabling irq %d\n", ichan->eof_irq);
	ret = __set_par(fbi, false);
	अगर (ret < 0)
		जाओ esetpar;

	__blank(FB_BLANK_UNBLANK, fbi);

	dev_info(dev, "registered, using mode %s\n", fb_mode);

	ret = रेजिस्टर_framebuffer(fbi);
	अगर (ret < 0)
		जाओ erfb;

	वापस 0;

erfb:
esetpar:
emode:
	fb_dealloc_cmap(&fbi->cmap);
	framebuffer_release(fbi);

	वापस ret;
पूर्ण

अटल bool chan_filter(काष्ठा dma_chan *chan, व्योम *arg)
अणु
	काष्ठा dma_chan_request *rq = arg;
	काष्ठा device *dev;
	काष्ठा mx3fb_platक्रमm_data *mx3fb_pdata;

	अगर (!imx_dma_is_ipu(chan))
		वापस false;

	अगर (!rq)
		वापस false;

	dev = rq->mx3fb->dev;
	mx3fb_pdata = dev_get_platdata(dev);

	वापस rq->id == chan->chan_id &&
		mx3fb_pdata->dma_dev == chan->device->dev;
पूर्ण

अटल व्योम release_fbi(काष्ठा fb_info *fbi)
अणु
	mx3fb_unmap_video_memory(fbi);

	fb_dealloc_cmap(&fbi->cmap);

	unरेजिस्टर_framebuffer(fbi);
	framebuffer_release(fbi);
पूर्ण

अटल पूर्णांक mx3fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;
	काष्ठा resource *sdc_reg;
	काष्ठा mx3fb_data *mx3fb;
	dma_cap_mask_t mask;
	काष्ठा dma_chan *chan;
	काष्ठा dma_chan_request rq;

	/*
	 * Display Interface (DI) and Synchronous Display Controller (SDC)
	 * रेजिस्टरs
	 */
	sdc_reg = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!sdc_reg)
		वापस -EINVAL;

	mx3fb = devm_kzalloc(&pdev->dev, माप(*mx3fb), GFP_KERNEL);
	अगर (!mx3fb)
		वापस -ENOMEM;

	spin_lock_init(&mx3fb->lock);

	mx3fb->reg_base = ioremap(sdc_reg->start, resource_size(sdc_reg));
	अगर (!mx3fb->reg_base) अणु
		ret = -ENOMEM;
		जाओ eremap;
	पूर्ण

	pr_debug("Remapped %pR at %p\n", sdc_reg, mx3fb->reg_base);

	/* IDMAC पूर्णांकerface */
	dmaengine_get();

	mx3fb->dev = dev;
	platक्रमm_set_drvdata(pdev, mx3fb);

	rq.mx3fb = mx3fb;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	dma_cap_set(DMA_PRIVATE, mask);
	rq.id = IDMAC_SDC_0;
	chan = dma_request_channel(mask, chan_filter, &rq);
	अगर (!chan) अणु
		ret = -EBUSY;
		जाओ ersdc0;
	पूर्ण

	mx3fb->backlight_level = 255;

	ret = init_fb_chan(mx3fb, to_idmac_chan(chan));
	अगर (ret < 0)
		जाओ eisdc0;

	mx3fb_init_backlight(mx3fb);

	वापस 0;

eisdc0:
	dma_release_channel(chan);
ersdc0:
	dmaengine_put();
	iounmap(mx3fb->reg_base);
eremap:
	dev_err(dev, "mx3fb: failed to register fb\n");
	वापस ret;
पूर्ण

अटल पूर्णांक mx3fb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mx3fb_data *mx3fb = platक्रमm_get_drvdata(dev);
	काष्ठा fb_info *fbi = mx3fb->fbi;
	काष्ठा mx3fb_info *mx3_fbi = fbi->par;
	काष्ठा dma_chan *chan;

	chan = &mx3_fbi->idmac_channel->dma_chan;
	release_fbi(fbi);

	mx3fb_निकास_backlight(mx3fb);

	dma_release_channel(chan);
	dmaengine_put();

	iounmap(mx3fb->reg_base);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mx3fb_driver = अणु
	.driver = अणु
		.name = MX3FB_NAME,
	पूर्ण,
	.probe = mx3fb_probe,
	.हटाओ = mx3fb_हटाओ,
	.suspend = mx3fb_suspend,
	.resume = mx3fb_resume,
पूर्ण;

/*
 * Parse user specअगरied options (`video=mx3fb:')
 * example:
 * 	video=mx3fb:bpp=16
 */
अटल पूर्णांक __init mx3fb_setup(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *opt, *options = शून्य;

	अगर (fb_get_options("mx3fb", &options))
		वापस -ENODEV;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*opt)
			जारी;
		अगर (!म_भेदन(opt, "bpp=", 4))
			शेष_bpp = simple_म_से_अदीर्घ(opt + 4, शून्य, 0);
		अन्यथा
			fb_mode = opt;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक __init mx3fb_init(व्योम)
अणु
	पूर्णांक ret = mx3fb_setup();

	अगर (ret < 0)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&mx3fb_driver);
	वापस ret;
पूर्ण

अटल व्योम __निकास mx3fb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mx3fb_driver);
पूर्ण

module_init(mx3fb_init);
module_निकास(mx3fb_निकास);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("MX3 framebuffer driver");
MODULE_ALIAS("platform:" MX3FB_NAME);
MODULE_LICENSE("GPL v2");
