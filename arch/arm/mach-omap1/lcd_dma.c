<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/lcd_dma.c
 *
 * Extracted from arch/arm/plat-omap/dma.c
 * Copyright (C) 2003 - 2008 Nokia Corporation
 * Author: Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 * DMA channel linking क्रम 1610 by Samuel Ortiz <samuel.ortiz@nokia.com>
 * Graphics DMA and LCD DMA graphics tranक्रमmations
 * by Imre Deak <imre.deak@nokia.com>
 * OMAP2/3 support Copyright (C) 2004-2007 Texas Instruments, Inc.
 * Merged to support both OMAP1 and OMAP2 by Tony Lindgren <tony@atomide.com>
 * Some functions based on earlier dma-omap.c Copyright (C) 2001 RidgeRun, Inc.
 *
 * Copyright (C) 2009 Texas Instruments
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * Support functions क्रम the OMAP पूर्णांकernal DMA channels.
 */

#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश <linux/omap-dma.h>

#समावेश <mach/hardware.h>
#समावेश <mach/lcdc.h>

पूर्णांक omap_lcd_dma_running(व्योम)
अणु
	/*
	 * On OMAP1510, पूर्णांकernal LCD controller will start the transfer
	 * when it माला_लो enabled, so assume DMA running अगर LCD enabled.
	 */
	अगर (cpu_is_omap15xx())
		अगर (omap_पढ़ोw(OMAP_LCDC_CONTROL) & OMAP_LCDC_CTRL_LCD_EN)
			वापस 1;

	/* Check अगर LCD DMA is running */
	अगर (cpu_is_omap16xx())
		अगर (omap_पढ़ोw(OMAP1610_DMA_LCD_CCR) & OMAP_DMA_CCR_EN)
			वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा lcd_dma_info अणु
	spinlock_t lock;
	पूर्णांक reserved;
	व्योम (*callback)(u16 status, व्योम *data);
	व्योम *cb_data;

	पूर्णांक active;
	अचिन्हित दीर्घ addr;
	पूर्णांक rotate, data_type, xres, yres;
	पूर्णांक vxres;
	पूर्णांक mirror;
	पूर्णांक xscale, yscale;
	पूर्णांक ext_ctrl;
	पूर्णांक src_port;
	पूर्णांक single_transfer;
पूर्ण lcd_dma;

व्योम omap_set_lcd_dma_b1(अचिन्हित दीर्घ addr, u16 fb_xres, u16 fb_yres,
			 पूर्णांक data_type)
अणु
	lcd_dma.addr = addr;
	lcd_dma.data_type = data_type;
	lcd_dma.xres = fb_xres;
	lcd_dma.yres = fb_yres;
पूर्ण
EXPORT_SYMBOL(omap_set_lcd_dma_b1);

व्योम omap_set_lcd_dma_ext_controller(पूर्णांक बाह्यal)
अणु
	lcd_dma.ext_ctrl = बाह्यal;
पूर्ण
EXPORT_SYMBOL(omap_set_lcd_dma_ext_controller);

व्योम omap_set_lcd_dma_single_transfer(पूर्णांक single)
अणु
	lcd_dma.single_transfer = single;
पूर्ण
EXPORT_SYMBOL(omap_set_lcd_dma_single_transfer);

व्योम omap_set_lcd_dma_b1_rotation(पूर्णांक rotate)
अणु
	अगर (cpu_is_omap15xx()) अणु
		prपूर्णांकk(KERN_ERR "DMA rotation is not supported in 1510 mode\n");
		BUG();
		वापस;
	पूर्ण
	lcd_dma.rotate = rotate;
पूर्ण
EXPORT_SYMBOL(omap_set_lcd_dma_b1_rotation);

व्योम omap_set_lcd_dma_b1_mirror(पूर्णांक mirror)
अणु
	अगर (cpu_is_omap15xx()) अणु
		prपूर्णांकk(KERN_ERR "DMA mirror is not supported in 1510 mode\n");
		BUG();
	पूर्ण
	lcd_dma.mirror = mirror;
पूर्ण
EXPORT_SYMBOL(omap_set_lcd_dma_b1_mirror);

व्योम omap_set_lcd_dma_b1_vxres(अचिन्हित दीर्घ vxres)
अणु
	अगर (cpu_is_omap15xx()) अणु
		pr_err("DMA virtual resolution is not supported in 1510 mode\n");
		BUG();
	पूर्ण
	lcd_dma.vxres = vxres;
पूर्ण
EXPORT_SYMBOL(omap_set_lcd_dma_b1_vxres);

व्योम omap_set_lcd_dma_b1_scale(अचिन्हित पूर्णांक xscale, अचिन्हित पूर्णांक yscale)
अणु
	अगर (cpu_is_omap15xx()) अणु
		prपूर्णांकk(KERN_ERR "DMA scale is not supported in 1510 mode\n");
		BUG();
	पूर्ण
	lcd_dma.xscale = xscale;
	lcd_dma.yscale = yscale;
पूर्ण
EXPORT_SYMBOL(omap_set_lcd_dma_b1_scale);

अटल व्योम set_b1_regs(व्योम)
अणु
	अचिन्हित दीर्घ top, bottom;
	पूर्णांक es;
	u16 w;
	अचिन्हित दीर्घ en, fn;
	दीर्घ ei, fi;
	अचिन्हित दीर्घ vxres;
	अचिन्हित पूर्णांक xscale, yscale;

	चयन (lcd_dma.data_type) अणु
	हाल OMAP_DMA_DATA_TYPE_S8:
		es = 1;
		अवरोध;
	हाल OMAP_DMA_DATA_TYPE_S16:
		es = 2;
		अवरोध;
	हाल OMAP_DMA_DATA_TYPE_S32:
		es = 4;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	vxres = lcd_dma.vxres ? lcd_dma.vxres : lcd_dma.xres;
	xscale = lcd_dma.xscale ? lcd_dma.xscale : 1;
	yscale = lcd_dma.yscale ? lcd_dma.yscale : 1;
	BUG_ON(vxres < lcd_dma.xres);

#घोषणा PIXADDR(x, y) (lcd_dma.addr +					\
		((y) * vxres * yscale + (x) * xscale) * es)
#घोषणा PIXSTEP(sx, sy, dx, dy) (PIXADDR(dx, dy) - PIXADDR(sx, sy) - es + 1)

	चयन (lcd_dma.rotate) अणु
	हाल 0:
		अगर (!lcd_dma.mirror) अणु
			top = PIXADDR(0, 0);
			bottom = PIXADDR(lcd_dma.xres - 1, lcd_dma.yres - 1);
			/* 1510 DMA requires the bottom address to be 2 more
			 * than the actual last memory access location. */
			अगर (cpu_is_omap15xx() &&
				lcd_dma.data_type == OMAP_DMA_DATA_TYPE_S32)
					bottom += 2;
			ei = PIXSTEP(0, 0, 1, 0);
			fi = PIXSTEP(lcd_dma.xres - 1, 0, 0, 1);
		पूर्ण अन्यथा अणु
			top = PIXADDR(lcd_dma.xres - 1, 0);
			bottom = PIXADDR(0, lcd_dma.yres - 1);
			ei = PIXSTEP(1, 0, 0, 0);
			fi = PIXSTEP(0, 0, lcd_dma.xres - 1, 1);
		पूर्ण
		en = lcd_dma.xres;
		fn = lcd_dma.yres;
		अवरोध;
	हाल 90:
		अगर (!lcd_dma.mirror) अणु
			top = PIXADDR(0, lcd_dma.yres - 1);
			bottom = PIXADDR(lcd_dma.xres - 1, 0);
			ei = PIXSTEP(0, 1, 0, 0);
			fi = PIXSTEP(0, 0, 1, lcd_dma.yres - 1);
		पूर्ण अन्यथा अणु
			top = PIXADDR(lcd_dma.xres - 1, lcd_dma.yres - 1);
			bottom = PIXADDR(0, 0);
			ei = PIXSTEP(0, 1, 0, 0);
			fi = PIXSTEP(1, 0, 0, lcd_dma.yres - 1);
		पूर्ण
		en = lcd_dma.yres;
		fn = lcd_dma.xres;
		अवरोध;
	हाल 180:
		अगर (!lcd_dma.mirror) अणु
			top = PIXADDR(lcd_dma.xres - 1, lcd_dma.yres - 1);
			bottom = PIXADDR(0, 0);
			ei = PIXSTEP(1, 0, 0, 0);
			fi = PIXSTEP(0, 1, lcd_dma.xres - 1, 0);
		पूर्ण अन्यथा अणु
			top = PIXADDR(0, lcd_dma.yres - 1);
			bottom = PIXADDR(lcd_dma.xres - 1, 0);
			ei = PIXSTEP(0, 0, 1, 0);
			fi = PIXSTEP(lcd_dma.xres - 1, 1, 0, 0);
		पूर्ण
		en = lcd_dma.xres;
		fn = lcd_dma.yres;
		अवरोध;
	हाल 270:
		अगर (!lcd_dma.mirror) अणु
			top = PIXADDR(lcd_dma.xres - 1, 0);
			bottom = PIXADDR(0, lcd_dma.yres - 1);
			ei = PIXSTEP(0, 0, 0, 1);
			fi = PIXSTEP(1, lcd_dma.yres - 1, 0, 0);
		पूर्ण अन्यथा अणु
			top = PIXADDR(0, 0);
			bottom = PIXADDR(lcd_dma.xres - 1, lcd_dma.yres - 1);
			ei = PIXSTEP(0, 0, 0, 1);
			fi = PIXSTEP(0, lcd_dma.yres - 1, 1, 0);
		पूर्ण
		en = lcd_dma.yres;
		fn = lcd_dma.xres;
		अवरोध;
	शेष:
		BUG();
		वापस;	/* Suppress warning about uninitialized vars */
	पूर्ण

	अगर (cpu_is_omap15xx()) अणु
		omap_ग_लिखोw(top >> 16, OMAP1510_DMA_LCD_TOP_F1_U);
		omap_ग_लिखोw(top, OMAP1510_DMA_LCD_TOP_F1_L);
		omap_ग_लिखोw(bottom >> 16, OMAP1510_DMA_LCD_BOT_F1_U);
		omap_ग_लिखोw(bottom, OMAP1510_DMA_LCD_BOT_F1_L);

		वापस;
	पूर्ण

	/* 1610 regs */
	omap_ग_लिखोw(top >> 16, OMAP1610_DMA_LCD_TOP_B1_U);
	omap_ग_लिखोw(top, OMAP1610_DMA_LCD_TOP_B1_L);
	omap_ग_लिखोw(bottom >> 16, OMAP1610_DMA_LCD_BOT_B1_U);
	omap_ग_लिखोw(bottom, OMAP1610_DMA_LCD_BOT_B1_L);

	omap_ग_लिखोw(en, OMAP1610_DMA_LCD_SRC_EN_B1);
	omap_ग_लिखोw(fn, OMAP1610_DMA_LCD_SRC_FN_B1);

	w = omap_पढ़ोw(OMAP1610_DMA_LCD_CSDP);
	w &= ~0x03;
	w |= lcd_dma.data_type;
	omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CSDP);

	w = omap_पढ़ोw(OMAP1610_DMA_LCD_CTRL);
	/* Always set the source port as SDRAM क्रम now*/
	w &= ~(0x03 << 6);
	अगर (lcd_dma.callback != शून्य)
		w |= 1 << 1;		/* Block पूर्णांकerrupt enable */
	अन्यथा
		w &= ~(1 << 1);
	omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CTRL);

	अगर (!(lcd_dma.rotate || lcd_dma.mirror ||
	      lcd_dma.vxres || lcd_dma.xscale || lcd_dma.yscale))
		वापस;

	w = omap_पढ़ोw(OMAP1610_DMA_LCD_CCR);
	/* Set the द्विगुन-indexed addressing mode */
	w |= (0x03 << 12);
	omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CCR);

	omap_ग_लिखोw(ei, OMAP1610_DMA_LCD_SRC_EI_B1);
	omap_ग_लिखोw(fi >> 16, OMAP1610_DMA_LCD_SRC_FI_B1_U);
	omap_ग_लिखोw(fi, OMAP1610_DMA_LCD_SRC_FI_B1_L);
पूर्ण

अटल irqवापस_t lcd_dma_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u16 w;

	w = omap_पढ़ोw(OMAP1610_DMA_LCD_CTRL);
	अगर (unlikely(!(w & (1 << 3)))) अणु
		prपूर्णांकk(KERN_WARNING "Spurious LCD DMA IRQ\n");
		वापस IRQ_NONE;
	पूर्ण
	/* Ack the IRQ */
	w |= (1 << 3);
	omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CTRL);
	lcd_dma.active = 0;
	अगर (lcd_dma.callback != शून्य)
		lcd_dma.callback(w, lcd_dma.cb_data);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक omap_request_lcd_dma(व्योम (*callback)(u16 status, व्योम *data),
			 व्योम *data)
अणु
	spin_lock_irq(&lcd_dma.lock);
	अगर (lcd_dma.reserved) अणु
		spin_unlock_irq(&lcd_dma.lock);
		prपूर्णांकk(KERN_ERR "LCD DMA channel already reserved\n");
		BUG();
		वापस -EBUSY;
	पूर्ण
	lcd_dma.reserved = 1;
	spin_unlock_irq(&lcd_dma.lock);
	lcd_dma.callback = callback;
	lcd_dma.cb_data = data;
	lcd_dma.active = 0;
	lcd_dma.single_transfer = 0;
	lcd_dma.rotate = 0;
	lcd_dma.vxres = 0;
	lcd_dma.mirror = 0;
	lcd_dma.xscale = 0;
	lcd_dma.yscale = 0;
	lcd_dma.ext_ctrl = 0;
	lcd_dma.src_port = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(omap_request_lcd_dma);

व्योम omap_मुक्त_lcd_dma(व्योम)
अणु
	spin_lock(&lcd_dma.lock);
	अगर (!lcd_dma.reserved) अणु
		spin_unlock(&lcd_dma.lock);
		prपूर्णांकk(KERN_ERR "LCD DMA is not reserved\n");
		BUG();
		वापस;
	पूर्ण
	अगर (!cpu_is_omap15xx())
		omap_ग_लिखोw(omap_पढ़ोw(OMAP1610_DMA_LCD_CCR) & ~1,
			    OMAP1610_DMA_LCD_CCR);
	lcd_dma.reserved = 0;
	spin_unlock(&lcd_dma.lock);
पूर्ण
EXPORT_SYMBOL(omap_मुक्त_lcd_dma);

व्योम omap_enable_lcd_dma(व्योम)
अणु
	u16 w;

	/*
	 * Set the Enable bit only अगर an बाह्यal controller is
	 * connected. Otherwise the OMAP पूर्णांकernal controller will
	 * start the transfer when it माला_लो enabled.
	 */
	अगर (cpu_is_omap15xx() || !lcd_dma.ext_ctrl)
		वापस;

	w = omap_पढ़ोw(OMAP1610_DMA_LCD_CTRL);
	w |= 1 << 8;
	omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CTRL);

	lcd_dma.active = 1;

	w = omap_पढ़ोw(OMAP1610_DMA_LCD_CCR);
	w |= 1 << 7;
	omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CCR);
पूर्ण
EXPORT_SYMBOL(omap_enable_lcd_dma);

व्योम omap_setup_lcd_dma(व्योम)
अणु
	BUG_ON(lcd_dma.active);
	अगर (!cpu_is_omap15xx()) अणु
		/* Set some reasonable शेषs */
		omap_ग_लिखोw(0x5440, OMAP1610_DMA_LCD_CCR);
		omap_ग_लिखोw(0x9102, OMAP1610_DMA_LCD_CSDP);
		omap_ग_लिखोw(0x0004, OMAP1610_DMA_LCD_LCH_CTRL);
	पूर्ण
	set_b1_regs();
	अगर (!cpu_is_omap15xx()) अणु
		u16 w;

		w = omap_पढ़ोw(OMAP1610_DMA_LCD_CCR);
		/*
		 * If DMA was alपढ़ोy active set the end_prog bit to have
		 * the programmed रेजिस्टर set loaded पूर्णांकo the active
		 * रेजिस्टर set.
		 */
		w |= 1 << 11;		/* End_prog */
		अगर (!lcd_dma.single_transfer)
			w |= (3 << 8);	/* Auto_init, repeat */
		omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CCR);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(omap_setup_lcd_dma);

व्योम omap_stop_lcd_dma(व्योम)
अणु
	u16 w;

	lcd_dma.active = 0;
	अगर (cpu_is_omap15xx() || !lcd_dma.ext_ctrl)
		वापस;

	w = omap_पढ़ोw(OMAP1610_DMA_LCD_CCR);
	w &= ~(1 << 7);
	omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CCR);

	w = omap_पढ़ोw(OMAP1610_DMA_LCD_CTRL);
	w &= ~(1 << 8);
	omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CTRL);
पूर्ण
EXPORT_SYMBOL(omap_stop_lcd_dma);

अटल पूर्णांक __init omap_init_lcd_dma(व्योम)
अणु
	पूर्णांक r;

	अगर (!cpu_class_is_omap1())
		वापस -ENODEV;

	अगर (cpu_is_omap16xx()) अणु
		u16 w;

		/* this would prevent OMAP sleep */
		w = omap_पढ़ोw(OMAP1610_DMA_LCD_CTRL);
		w &= ~(1 << 8);
		omap_ग_लिखोw(w, OMAP1610_DMA_LCD_CTRL);
	पूर्ण

	spin_lock_init(&lcd_dma.lock);

	r = request_irq(INT_DMA_LCD, lcd_dma_irq_handler, 0,
			"LCD DMA", शून्य);
	अगर (r != 0)
		pr_err("unable to request IRQ for LCD DMA (error %d)\n", r);

	वापस r;
पूर्ण

arch_initcall(omap_init_lcd_dma);

