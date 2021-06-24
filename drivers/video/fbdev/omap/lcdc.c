<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OMAP1 पूर्णांकernal LCD controller
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/err.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/clk.h>
#समावेश <linux/gfp.h>

#समावेश <mach/lcdc.h>
#समावेश <linux/omap-dma.h>

#समावेश <यंत्र/mach-types.h>

#समावेश "omapfb.h"

#समावेश "lcdc.h"

#घोषणा MODULE_NAME			"lcdc"

#घोषणा MAX_PALETTE_SIZE		PAGE_SIZE

क्रमागत lcdc_load_mode अणु
	OMAP_LCDC_LOAD_PALETTE,
	OMAP_LCDC_LOAD_FRAME,
	OMAP_LCDC_LOAD_PALETTE_AND_FRAME
पूर्ण;

अटल काष्ठा omap_lcd_controller अणु
	क्रमागत omapfb_update_mode	update_mode;
	पूर्णांक			ext_mode;

	अचिन्हित दीर्घ		frame_offset;
	पूर्णांक			screen_width;
	पूर्णांक			xres;
	पूर्णांक			yres;

	क्रमागत omapfb_color_क्रमmat	color_mode;
	पूर्णांक			bpp;
	व्योम			*palette_virt;
	dma_addr_t		palette_phys;
	पूर्णांक			palette_code;
	पूर्णांक			palette_size;

	अचिन्हित पूर्णांक		irq_mask;
	काष्ठा completion	last_frame_complete;
	काष्ठा completion	palette_load_complete;
	काष्ठा clk		*lcd_ck;
	काष्ठा omapfb_device	*fbdev;

	व्योम			(*dma_callback)(व्योम *data);
	व्योम			*dma_callback_data;

	dma_addr_t		vram_phys;
	व्योम			*vram_virt;
	अचिन्हित दीर्घ		vram_size;
पूर्ण lcdc;

अटल अंतरभूत व्योम enable_irqs(पूर्णांक mask)
अणु
	lcdc.irq_mask |= mask;
पूर्ण

अटल अंतरभूत व्योम disable_irqs(पूर्णांक mask)
अणु
	lcdc.irq_mask &= ~mask;
पूर्ण

अटल व्योम set_load_mode(क्रमागत lcdc_load_mode mode)
अणु
	u32 l;

	l = omap_पढ़ोl(OMAP_LCDC_CONTROL);
	l &= ~(3 << 20);
	चयन (mode) अणु
	हाल OMAP_LCDC_LOAD_PALETTE:
		l |= 1 << 20;
		अवरोध;
	हाल OMAP_LCDC_LOAD_FRAME:
		l |= 2 << 20;
		अवरोध;
	हाल OMAP_LCDC_LOAD_PALETTE_AND_FRAME:
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	omap_ग_लिखोl(l, OMAP_LCDC_CONTROL);
पूर्ण

अटल व्योम enable_controller(व्योम)
अणु
	u32 l;

	l = omap_पढ़ोl(OMAP_LCDC_CONTROL);
	l |= OMAP_LCDC_CTRL_LCD_EN;
	l &= ~OMAP_LCDC_IRQ_MASK;
	l |= lcdc.irq_mask | OMAP_LCDC_IRQ_DONE;	/* enabled IRQs */
	omap_ग_लिखोl(l, OMAP_LCDC_CONTROL);
पूर्ण

अटल व्योम disable_controller_async(व्योम)
अणु
	u32 l;
	u32 mask;

	l = omap_पढ़ोl(OMAP_LCDC_CONTROL);
	mask = OMAP_LCDC_CTRL_LCD_EN | OMAP_LCDC_IRQ_MASK;
	/*
	 * Preserve the DONE mask, since we still want to get the
	 * final DONE irq. It will be disabled in the IRQ handler.
	 */
	mask &= ~OMAP_LCDC_IRQ_DONE;
	l &= ~mask;
	omap_ग_लिखोl(l, OMAP_LCDC_CONTROL);
पूर्ण

अटल व्योम disable_controller(व्योम)
अणु
	init_completion(&lcdc.last_frame_complete);
	disable_controller_async();
	अगर (!रुको_क्रम_completion_समयout(&lcdc.last_frame_complete,
				msecs_to_jअगरfies(500)))
		dev_err(lcdc.fbdev->dev, "timeout waiting for FRAME DONE\n");
पूर्ण

अटल व्योम reset_controller(u32 status)
अणु
	अटल अचिन्हित दीर्घ reset_count;
	अटल अचिन्हित दीर्घ last_jअगरfies;

	disable_controller_async();
	reset_count++;
	अगर (reset_count == 1 || समय_after(jअगरfies, last_jअगरfies + HZ)) अणु
		dev_err(lcdc.fbdev->dev,
			  "resetting (status %#010x,reset count %lu)\n",
			  status, reset_count);
		last_jअगरfies = jअगरfies;
	पूर्ण
	अगर (reset_count < 100) अणु
		enable_controller();
	पूर्ण अन्यथा अणु
		reset_count = 0;
		dev_err(lcdc.fbdev->dev,
			"too many reset attempts, giving up.\n");
	पूर्ण
पूर्ण

/*
 * Configure the LCD DMA according to the current mode specअगरied by parameters
 * in lcdc.fbdev and fbdev->var.
 */
अटल व्योम setup_lcd_dma(व्योम)
अणु
	अटल स्थिर पूर्णांक dma_elem_type[] = अणु
		0,
		OMAP_DMA_DATA_TYPE_S8,
		OMAP_DMA_DATA_TYPE_S16,
		0,
		OMAP_DMA_DATA_TYPE_S32,
	पूर्ण;
	काष्ठा omapfb_plane_काष्ठा *plane = lcdc.fbdev->fb_info[0]->par;
	काष्ठा fb_var_screeninfo *var = &lcdc.fbdev->fb_info[0]->var;
	अचिन्हित दीर्घ	src;
	पूर्णांक		esize, xelem, yelem;

	src = lcdc.vram_phys + lcdc.frame_offset;

	चयन (var->rotate) अणु
	हाल 0:
		अगर (plane->info.mirror || (src & 3) ||
		    lcdc.color_mode == OMAPFB_COLOR_YUV420 ||
		    (lcdc.xres & 1))
			esize = 2;
		अन्यथा
			esize = 4;
		xelem = lcdc.xres * lcdc.bpp / 8 / esize;
		yelem = lcdc.yres;
		अवरोध;
	हाल 90:
	हाल 180:
	हाल 270:
		अगर (cpu_is_omap15xx()) अणु
			BUG();
		पूर्ण
		esize = 2;
		xelem = lcdc.yres * lcdc.bpp / 16;
		yelem = lcdc.xres;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण
#अगर_घोषित VERBOSE
	dev_dbg(lcdc.fbdev->dev,
		 "setup_dma: src %#010lx esize %d xelem %d yelem %d\n",
		 src, esize, xelem, yelem);
#पूर्ण_अगर
	omap_set_lcd_dma_b1(src, xelem, yelem, dma_elem_type[esize]);
	अगर (!cpu_is_omap15xx()) अणु
		पूर्णांक bpp = lcdc.bpp;

		/*
		 * YUV support is only क्रम बाह्यal mode when we have the
		 * YUV winकरोw embedded in a 16bpp frame buffer.
		 */
		अगर (lcdc.color_mode == OMAPFB_COLOR_YUV420)
			bpp = 16;
		/* Set भव xres elem size */
		omap_set_lcd_dma_b1_vxres(
			lcdc.screen_width * bpp / 8 / esize);
		/* Setup transक्रमmations */
		omap_set_lcd_dma_b1_rotation(var->rotate);
		omap_set_lcd_dma_b1_mirror(plane->info.mirror);
	पूर्ण
	omap_setup_lcd_dma();
पूर्ण

अटल irqवापस_t lcdc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 status;

	status = omap_पढ़ोl(OMAP_LCDC_STATUS);

	अगर (status & (OMAP_LCDC_STAT_FUF | OMAP_LCDC_STAT_SYNC_LOST))
		reset_controller(status);
	अन्यथा अणु
		अगर (status & OMAP_LCDC_STAT_DONE) अणु
			u32 l;

			/*
			 * Disable IRQ_DONE. The status bit will be cleared
			 * only when the controller is reenabled and we करोn't
			 * want to get more पूर्णांकerrupts.
			 */
			l = omap_पढ़ोl(OMAP_LCDC_CONTROL);
			l &= ~OMAP_LCDC_IRQ_DONE;
			omap_ग_लिखोl(l, OMAP_LCDC_CONTROL);
			complete(&lcdc.last_frame_complete);
		पूर्ण
		अगर (status & OMAP_LCDC_STAT_LOADED_PALETTE) अणु
			disable_controller_async();
			complete(&lcdc.palette_load_complete);
		पूर्ण
	पूर्ण

	/*
	 * Clear these पूर्णांकerrupt status bits.
	 * Sync_lost, FUF bits were cleared by disabling the LCD controller
	 * LOADED_PALETTE can be cleared this way only in palette only
	 * load mode. In other load modes it's cleared by disabling the
	 * controller.
	 */
	status &= ~(OMAP_LCDC_STAT_VSYNC |
		    OMAP_LCDC_STAT_LOADED_PALETTE |
		    OMAP_LCDC_STAT_ABC |
		    OMAP_LCDC_STAT_LINE_INT);
	omap_ग_लिखोl(status, OMAP_LCDC_STATUS);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Change to a new video mode. We defer this to a later समय to aव्योम any
 * flicker and not to mess up the current LCD DMA context. For this we disable
 * the LCD controller, which will generate a DONE irq after the last frame has
 * been transferred. Then it'll be safe to reconfigure both the LCD controller
 * as well as the LCD DMA.
 */
अटल पूर्णांक omap_lcdc_setup_plane(पूर्णांक plane, पूर्णांक channel_out,
				 अचिन्हित दीर्घ offset, पूर्णांक screen_width,
				 पूर्णांक pos_x, पूर्णांक pos_y, पूर्णांक width, पूर्णांक height,
				 पूर्णांक color_mode)
अणु
	काष्ठा fb_var_screeninfo *var = &lcdc.fbdev->fb_info[0]->var;
	काष्ठा lcd_panel *panel = lcdc.fbdev->panel;
	पूर्णांक rot_x, rot_y;

	अगर (var->rotate == 0) अणु
		rot_x = panel->x_res;
		rot_y = panel->y_res;
	पूर्ण अन्यथा अणु
		rot_x = panel->y_res;
		rot_y = panel->x_res;
	पूर्ण
	अगर (plane != 0 || channel_out != 0 || pos_x != 0 || pos_y != 0 ||
	    width > rot_x || height > rot_y) अणु
#अगर_घोषित VERBOSE
		dev_dbg(lcdc.fbdev->dev,
			"invalid plane params plane %d pos_x %d pos_y %d "
			"w %d h %d\n", plane, pos_x, pos_y, width, height);
#पूर्ण_अगर
		वापस -EINVAL;
	पूर्ण

	lcdc.frame_offset = offset;
	lcdc.xres = width;
	lcdc.yres = height;
	lcdc.screen_width = screen_width;
	lcdc.color_mode = color_mode;

	चयन (color_mode) अणु
	हाल OMAPFB_COLOR_CLUT_8BPP:
		lcdc.bpp = 8;
		lcdc.palette_code = 0x3000;
		lcdc.palette_size = 512;
		अवरोध;
	हाल OMAPFB_COLOR_RGB565:
		lcdc.bpp = 16;
		lcdc.palette_code = 0x4000;
		lcdc.palette_size = 32;
		अवरोध;
	हाल OMAPFB_COLOR_RGB444:
		lcdc.bpp = 16;
		lcdc.palette_code = 0x4000;
		lcdc.palette_size = 32;
		अवरोध;
	हाल OMAPFB_COLOR_YUV420:
		अगर (lcdc.ext_mode) अणु
			lcdc.bpp = 12;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल OMAPFB_COLOR_YUV422:
		अगर (lcdc.ext_mode) अणु
			lcdc.bpp = 16;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		/* FIXME: other BPPs.
		 * bpp1: code  0,     size 256
		 * bpp2: code  0x1000 size 256
		 * bpp4: code  0x2000 size 256
		 * bpp12: code 0x4000 size 32
		 */
		dev_dbg(lcdc.fbdev->dev, "invalid color mode %d\n", color_mode);
		BUG();
		वापस -1;
	पूर्ण

	अगर (lcdc.ext_mode) अणु
		setup_lcd_dma();
		वापस 0;
	पूर्ण

	अगर (lcdc.update_mode == OMAPFB_AUTO_UPDATE) अणु
		disable_controller();
		omap_stop_lcd_dma();
		setup_lcd_dma();
		enable_controller();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_lcdc_enable_plane(पूर्णांक plane, पूर्णांक enable)
अणु
	dev_dbg(lcdc.fbdev->dev,
		"plane %d enable %d update_mode %d ext_mode %d\n",
		plane, enable, lcdc.update_mode, lcdc.ext_mode);
	अगर (plane != OMAPFB_PLANE_GFX)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Configure the LCD DMA क्रम a palette load operation and करो the palette
 * करोwnloading synchronously. We करोn't use the frame+palette load mode of
 * the controller, since the palette can always be करोwnloaded separately.
 */
अटल व्योम load_palette(व्योम)
अणु
	u16	*palette;

	palette = (u16 *)lcdc.palette_virt;

	*(u16 *)palette &= 0x0fff;
	*(u16 *)palette |= lcdc.palette_code;

	omap_set_lcd_dma_b1(lcdc.palette_phys,
		lcdc.palette_size / 4 + 1, 1, OMAP_DMA_DATA_TYPE_S32);

	omap_set_lcd_dma_single_transfer(1);
	omap_setup_lcd_dma();

	init_completion(&lcdc.palette_load_complete);
	enable_irqs(OMAP_LCDC_IRQ_LOADED_PALETTE);
	set_load_mode(OMAP_LCDC_LOAD_PALETTE);
	enable_controller();
	अगर (!रुको_क्रम_completion_समयout(&lcdc.palette_load_complete,
				msecs_to_jअगरfies(500)))
		dev_err(lcdc.fbdev->dev, "timeout waiting for FRAME DONE\n");
	/* The controller माला_लो disabled in the irq handler */
	disable_irqs(OMAP_LCDC_IRQ_LOADED_PALETTE);
	omap_stop_lcd_dma();

	omap_set_lcd_dma_single_transfer(lcdc.ext_mode);
पूर्ण

/* Used only in पूर्णांकernal controller mode */
अटल पूर्णांक omap_lcdc_setcolreg(u_पूर्णांक regno, u16 red, u16 green, u16 blue,
			       u16 transp, पूर्णांक update_hw_pal)
अणु
	u16 *palette;

	अगर (lcdc.color_mode != OMAPFB_COLOR_CLUT_8BPP || regno > 255)
		वापस -EINVAL;

	palette = (u16 *)lcdc.palette_virt;

	palette[regno] &= ~0x0fff;
	palette[regno] |= ((red >> 12) << 8) | ((green >> 12) << 4 ) |
			   (blue >> 12);

	अगर (update_hw_pal) अणु
		disable_controller();
		omap_stop_lcd_dma();
		load_palette();
		setup_lcd_dma();
		set_load_mode(OMAP_LCDC_LOAD_FRAME);
		enable_controller();
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम calc_ck_भाग(पूर्णांक is_tft, पूर्णांक pck, पूर्णांक *pck_भाग)
अणु
	अचिन्हित दीर्घ lck;

	pck = max(1, pck);
	lck = clk_get_rate(lcdc.lcd_ck);
	*pck_भाग = (lck + pck - 1) / pck;
	अगर (is_tft)
		*pck_भाग = max(2, *pck_भाग);
	अन्यथा
		*pck_भाग = max(3, *pck_भाग);
	अगर (*pck_भाग > 255) अणु
		/* FIXME: try to adjust logic घड़ी भागider as well */
		*pck_भाग = 255;
		dev_warn(lcdc.fbdev->dev, "pixclock %d kHz too low.\n",
			 pck / 1000);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम setup_regs(व्योम)
अणु
	u32 l;
	काष्ठा lcd_panel *panel = lcdc.fbdev->panel;
	पूर्णांक is_tft = panel->config & OMAP_LCDC_PANEL_TFT;
	अचिन्हित दीर्घ lck;
	पूर्णांक pcd;

	l = omap_पढ़ोl(OMAP_LCDC_CONTROL);
	l &= ~OMAP_LCDC_CTRL_LCD_TFT;
	l |= is_tft ? OMAP_LCDC_CTRL_LCD_TFT : 0;
#अगर_घोषित CONFIG_MACH_OMAP_PALMTE
/* FIXME:अगर (machine_is_omap_palmte()) अणु */
		/* PalmTE uses alternate TFT setting in 8BPP mode */
		l |= (is_tft && panel->bpp == 8) ? 0x810000 : 0;
/*	पूर्ण */
#पूर्ण_अगर
	omap_ग_लिखोl(l, OMAP_LCDC_CONTROL);

	l = omap_पढ़ोl(OMAP_LCDC_TIMING2);
	l &= ~(((1 << 6) - 1) << 20);
	l |= (panel->config & OMAP_LCDC_SIGNAL_MASK) << 20;
	omap_ग_लिखोl(l, OMAP_LCDC_TIMING2);

	l = panel->x_res - 1;
	l |= (panel->hsw - 1) << 10;
	l |= (panel->hfp - 1) << 16;
	l |= (panel->hbp - 1) << 24;
	omap_ग_लिखोl(l, OMAP_LCDC_TIMING0);

	l = panel->y_res - 1;
	l |= (panel->vsw - 1) << 10;
	l |= panel->vfp << 16;
	l |= panel->vbp << 24;
	omap_ग_लिखोl(l, OMAP_LCDC_TIMING1);

	l = omap_पढ़ोl(OMAP_LCDC_TIMING2);
	l &= ~0xff;

	lck = clk_get_rate(lcdc.lcd_ck);

	अगर (!panel->pcd)
		calc_ck_भाग(is_tft, panel->pixel_घड़ी * 1000, &pcd);
	अन्यथा अणु
		dev_warn(lcdc.fbdev->dev,
		    "Pixel clock divider value is obsolete.\n"
		    "Try to set pixel_clock to %lu and pcd to 0 "
		    "in drivers/video/omap/lcd_%s.c and submit a patch.\n",
			lck / panel->pcd / 1000, panel->name);

		pcd = panel->pcd;
	पूर्ण
	l |= pcd & 0xff;
	l |= panel->acb << 8;
	omap_ग_लिखोl(l, OMAP_LCDC_TIMING2);

	/* update panel info with the exact घड़ी */
	panel->pixel_घड़ी = lck / pcd / 1000;
पूर्ण

/*
 * Configure the LCD controller, करोwnload the color palette and start a looped
 * DMA transfer of the frame image data. Called only in पूर्णांकernal
 * controller mode.
 */
अटल पूर्णांक omap_lcdc_set_update_mode(क्रमागत omapfb_update_mode mode)
अणु
	पूर्णांक r = 0;

	अगर (mode != lcdc.update_mode) अणु
		चयन (mode) अणु
		हाल OMAPFB_AUTO_UPDATE:
			setup_regs();
			load_palette();

			/* Setup and start LCD DMA */
			setup_lcd_dma();

			set_load_mode(OMAP_LCDC_LOAD_FRAME);
			enable_irqs(OMAP_LCDC_IRQ_DONE);
			/* This will start the actual DMA transfer */
			enable_controller();
			lcdc.update_mode = mode;
			अवरोध;
		हाल OMAPFB_UPDATE_DISABLED:
			disable_controller();
			omap_stop_lcd_dma();
			lcdc.update_mode = mode;
			अवरोध;
		शेष:
			r = -EINVAL;
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

अटल क्रमागत omapfb_update_mode omap_lcdc_get_update_mode(व्योम)
अणु
	वापस lcdc.update_mode;
पूर्ण

/* PM code called only in पूर्णांकernal controller mode */
अटल व्योम omap_lcdc_suspend(व्योम)
अणु
	omap_lcdc_set_update_mode(OMAPFB_UPDATE_DISABLED);
पूर्ण

अटल व्योम omap_lcdc_resume(व्योम)
अणु
	omap_lcdc_set_update_mode(OMAPFB_AUTO_UPDATE);
पूर्ण

अटल व्योम omap_lcdc_get_caps(पूर्णांक plane, काष्ठा omapfb_caps *caps)
अणु
	वापस;
पूर्ण

पूर्णांक omap_lcdc_set_dma_callback(व्योम (*callback)(व्योम *data), व्योम *data)
अणु
	BUG_ON(callback == शून्य);

	अगर (lcdc.dma_callback)
		वापस -EBUSY;
	अन्यथा अणु
		lcdc.dma_callback = callback;
		lcdc.dma_callback_data = data;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(omap_lcdc_set_dma_callback);

व्योम omap_lcdc_मुक्त_dma_callback(व्योम)
अणु
	lcdc.dma_callback = शून्य;
पूर्ण
EXPORT_SYMBOL(omap_lcdc_मुक्त_dma_callback);

अटल व्योम lcdc_dma_handler(u16 status, व्योम *data)
अणु
	अगर (lcdc.dma_callback)
		lcdc.dma_callback(lcdc.dma_callback_data);
पूर्ण

अटल पूर्णांक alloc_palette_ram(व्योम)
अणु
	lcdc.palette_virt = dma_alloc_wc(lcdc.fbdev->dev, MAX_PALETTE_SIZE,
					 &lcdc.palette_phys, GFP_KERNEL);
	अगर (lcdc.palette_virt == शून्य) अणु
		dev_err(lcdc.fbdev->dev, "failed to alloc palette memory\n");
		वापस -ENOMEM;
	पूर्ण
	स_रखो(lcdc.palette_virt, 0, MAX_PALETTE_SIZE);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_palette_ram(व्योम)
अणु
	dma_मुक्त_wc(lcdc.fbdev->dev, MAX_PALETTE_SIZE, lcdc.palette_virt,
		    lcdc.palette_phys);
पूर्ण

अटल पूर्णांक alloc_fbmem(काष्ठा omapfb_mem_region *region)
अणु
	पूर्णांक bpp;
	पूर्णांक frame_size;
	काष्ठा lcd_panel *panel = lcdc.fbdev->panel;

	bpp = panel->bpp;
	अगर (bpp == 12)
		bpp = 16;
	frame_size = PAGE_ALIGN(panel->x_res * bpp / 8 * panel->y_res);
	अगर (region->size > frame_size)
		frame_size = region->size;
	lcdc.vram_size = frame_size;
	lcdc.vram_virt = dma_alloc_wc(lcdc.fbdev->dev, lcdc.vram_size,
				      &lcdc.vram_phys, GFP_KERNEL);
	अगर (lcdc.vram_virt == शून्य) अणु
		dev_err(lcdc.fbdev->dev, "unable to allocate FB DMA memory\n");
		वापस -ENOMEM;
	पूर्ण
	region->size = frame_size;
	region->paddr = lcdc.vram_phys;
	region->vaddr = lcdc.vram_virt;
	region->alloc = 1;

	स_रखो(lcdc.vram_virt, 0, lcdc.vram_size);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_fbmem(व्योम)
अणु
	dma_मुक्त_wc(lcdc.fbdev->dev, lcdc.vram_size, lcdc.vram_virt,
		    lcdc.vram_phys);
पूर्ण

अटल पूर्णांक setup_fbmem(काष्ठा omapfb_mem_desc *req_md)
अणु
	अगर (!req_md->region_cnt) अणु
		dev_err(lcdc.fbdev->dev, "no memory regions defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (req_md->region_cnt > 1) अणु
		dev_err(lcdc.fbdev->dev, "only one plane is supported\n");
		req_md->region_cnt = 1;
	पूर्ण

	वापस alloc_fbmem(&req_md->region[0]);
पूर्ण

अटल पूर्णांक omap_lcdc_init(काष्ठा omapfb_device *fbdev, पूर्णांक ext_mode,
			  काष्ठा omapfb_mem_desc *req_vram)
अणु
	पूर्णांक r;
	u32 l;
	पूर्णांक rate;
	काष्ठा clk *tc_ck;

	lcdc.irq_mask = 0;

	lcdc.fbdev = fbdev;
	lcdc.ext_mode = ext_mode;

	l = 0;
	omap_ग_लिखोl(l, OMAP_LCDC_CONTROL);

	/* FIXME:
	 * According to errata some platक्रमms have a घड़ी rate limitiation
	 */
	lcdc.lcd_ck = clk_get(fbdev->dev, "lcd_ck");
	अगर (IS_ERR(lcdc.lcd_ck)) अणु
		dev_err(fbdev->dev, "unable to access LCD clock\n");
		r = PTR_ERR(lcdc.lcd_ck);
		जाओ fail0;
	पूर्ण

	tc_ck = clk_get(fbdev->dev, "tc_ck");
	अगर (IS_ERR(tc_ck)) अणु
		dev_err(fbdev->dev, "unable to access TC clock\n");
		r = PTR_ERR(tc_ck);
		जाओ fail1;
	पूर्ण

	rate = clk_get_rate(tc_ck);
	clk_put(tc_ck);

	अगर (machine_is_ams_delta())
		rate /= 4;
	अगर (machine_is_omap_h3())
		rate /= 3;
	r = clk_set_rate(lcdc.lcd_ck, rate);
	अगर (r) अणु
		dev_err(fbdev->dev, "failed to adjust LCD rate\n");
		जाओ fail1;
	पूर्ण
	clk_enable(lcdc.lcd_ck);

	r = request_irq(OMAP_LCDC_IRQ, lcdc_irq_handler, 0, MODULE_NAME, fbdev);
	अगर (r) अणु
		dev_err(fbdev->dev, "unable to get IRQ\n");
		जाओ fail2;
	पूर्ण

	r = omap_request_lcd_dma(lcdc_dma_handler, शून्य);
	अगर (r) अणु
		dev_err(fbdev->dev, "unable to get LCD DMA\n");
		जाओ fail3;
	पूर्ण

	omap_set_lcd_dma_single_transfer(ext_mode);
	omap_set_lcd_dma_ext_controller(ext_mode);

	अगर (!ext_mode)
		अगर ((r = alloc_palette_ram()) < 0)
			जाओ fail4;

	अगर ((r = setup_fbmem(req_vram)) < 0)
		जाओ fail5;

	pr_info("omapfb: LCDC initialized\n");

	वापस 0;
fail5:
	अगर (!ext_mode)
		मुक्त_palette_ram();
fail4:
	omap_मुक्त_lcd_dma();
fail3:
	मुक्त_irq(OMAP_LCDC_IRQ, lcdc.fbdev);
fail2:
	clk_disable(lcdc.lcd_ck);
fail1:
	clk_put(lcdc.lcd_ck);
fail0:
	वापस r;
पूर्ण

अटल व्योम omap_lcdc_cleanup(व्योम)
अणु
	अगर (!lcdc.ext_mode)
		मुक्त_palette_ram();
	मुक्त_fbmem();
	omap_मुक्त_lcd_dma();
	मुक्त_irq(OMAP_LCDC_IRQ, lcdc.fbdev);
	clk_disable(lcdc.lcd_ck);
	clk_put(lcdc.lcd_ck);
पूर्ण

स्थिर काष्ठा lcd_ctrl omap1_पूर्णांक_ctrl = अणु
	.name			= "internal",
	.init			= omap_lcdc_init,
	.cleanup		= omap_lcdc_cleanup,
	.get_caps		= omap_lcdc_get_caps,
	.set_update_mode	= omap_lcdc_set_update_mode,
	.get_update_mode	= omap_lcdc_get_update_mode,
	.update_winकरोw		= शून्य,
	.suspend		= omap_lcdc_suspend,
	.resume			= omap_lcdc_resume,
	.setup_plane		= omap_lcdc_setup_plane,
	.enable_plane		= omap_lcdc_enable_plane,
	.setcolreg		= omap_lcdc_setcolreg,
पूर्ण;
