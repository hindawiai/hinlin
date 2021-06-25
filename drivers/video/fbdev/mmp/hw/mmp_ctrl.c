<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/video/mmp/hw/mmp_ctrl.c
 * Marvell MMP series Display Controller support
 *
 * Copyright (C) 2012 Marvell Technology Group Ltd.
 * Authors:  Guoqing Li <ligq@marvell.com>
 *          Lisa Du <cldu@marvell.com>
 *          Zhou Zhu <zzhu3@marvell.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पन.स>

#समावेश "mmp_ctrl.h"

अटल irqवापस_t ctrl_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmphw_ctrl *ctrl = (काष्ठा mmphw_ctrl *)dev_id;
	u32 isr, imask, पंचांगp;

	isr = पढ़ोl_relaxed(ctrl->reg_base + SPU_IRQ_ISR);
	imask = पढ़ोl_relaxed(ctrl->reg_base + SPU_IRQ_ENA);

	करो अणु
		/* clear घड़ी only */
		पंचांगp = पढ़ोl_relaxed(ctrl->reg_base + SPU_IRQ_ISR);
		अगर (पंचांगp & isr)
			ग_लिखोl_relaxed(~isr, ctrl->reg_base + SPU_IRQ_ISR);
	पूर्ण जबतक ((isr = पढ़ोl_relaxed(ctrl->reg_base + SPU_IRQ_ISR)) & imask);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 fmt_to_reg(काष्ठा mmp_overlay *overlay, पूर्णांक pix_fmt)
अणु
	u32 rbswap = 0, uvswap = 0, yuvswap = 0,
		csc_en = 0, val = 0,
		vid = overlay_is_vid(overlay);

	चयन (pix_fmt) अणु
	हाल PIXFMT_RGB565:
	हाल PIXFMT_RGB1555:
	हाल PIXFMT_RGB888PACK:
	हाल PIXFMT_RGB888UNPACK:
	हाल PIXFMT_RGBA888:
		rbswap = 1;
		अवरोध;
	हाल PIXFMT_VYUY:
	हाल PIXFMT_YVU422P:
	हाल PIXFMT_YVU420P:
		uvswap = 1;
		अवरोध;
	हाल PIXFMT_YUYV:
		yuvswap = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (pix_fmt) अणु
	हाल PIXFMT_RGB565:
	हाल PIXFMT_BGR565:
		अवरोध;
	हाल PIXFMT_RGB1555:
	हाल PIXFMT_BGR1555:
		val = 0x1;
		अवरोध;
	हाल PIXFMT_RGB888PACK:
	हाल PIXFMT_BGR888PACK:
		val = 0x2;
		अवरोध;
	हाल PIXFMT_RGB888UNPACK:
	हाल PIXFMT_BGR888UNPACK:
		val = 0x3;
		अवरोध;
	हाल PIXFMT_RGBA888:
	हाल PIXFMT_BGRA888:
		val = 0x4;
		अवरोध;
	हाल PIXFMT_UYVY:
	हाल PIXFMT_VYUY:
	हाल PIXFMT_YUYV:
		val = 0x5;
		csc_en = 1;
		अवरोध;
	हाल PIXFMT_YUV422P:
	हाल PIXFMT_YVU422P:
		val = 0x6;
		csc_en = 1;
		अवरोध;
	हाल PIXFMT_YUV420P:
	हाल PIXFMT_YVU420P:
		val = 0x7;
		csc_en = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस (dma_palette(0) | dma_fmt(vid, val) |
		dma_swaprb(vid, rbswap) | dma_swapuv(vid, uvswap) |
		dma_swapyuv(vid, yuvswap) | dma_csc(vid, csc_en));
पूर्ण

अटल व्योम dmafetch_set_fmt(काष्ठा mmp_overlay *overlay)
अणु
	u32 पंचांगp;
	काष्ठा mmp_path *path = overlay->path;
	पंचांगp = पढ़ोl_relaxed(ctrl_regs(path) + dma_ctrl(0, path->id));
	पंचांगp &= ~dma_mask(overlay_is_vid(overlay));
	पंचांगp |= fmt_to_reg(overlay, overlay->win.pix_fmt);
	ग_लिखोl_relaxed(पंचांगp, ctrl_regs(path) + dma_ctrl(0, path->id));
पूर्ण

अटल व्योम overlay_set_win(काष्ठा mmp_overlay *overlay, काष्ठा mmp_win *win)
अणु
	काष्ठा lcd_regs *regs = path_regs(overlay->path);

	/* निश्चित win supported */
	स_नकल(&overlay->win, win, माप(काष्ठा mmp_win));

	mutex_lock(&overlay->access_ok);

	अगर (overlay_is_vid(overlay)) अणु
		ग_लिखोl_relaxed(win->pitch[0],
				(व्योम __iomem *)&regs->v_pitch_yc);
		ग_लिखोl_relaxed(win->pitch[2] << 16 | win->pitch[1],
				(व्योम __iomem *)&regs->v_pitch_uv);

		ग_लिखोl_relaxed((win->ysrc << 16) | win->xsrc,
				(व्योम __iomem *)&regs->v_size);
		ग_लिखोl_relaxed((win->ydst << 16) | win->xdst,
				(व्योम __iomem *)&regs->v_size_z);
		ग_लिखोl_relaxed(win->ypos << 16 | win->xpos,
				(व्योम __iomem *)&regs->v_start);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(win->pitch[0], (व्योम __iomem *)&regs->g_pitch);

		ग_लिखोl_relaxed((win->ysrc << 16) | win->xsrc,
				(व्योम __iomem *)&regs->g_size);
		ग_लिखोl_relaxed((win->ydst << 16) | win->xdst,
				(व्योम __iomem *)&regs->g_size_z);
		ग_लिखोl_relaxed(win->ypos << 16 | win->xpos,
				(व्योम __iomem *)&regs->g_start);
	पूर्ण

	dmafetch_set_fmt(overlay);
	mutex_unlock(&overlay->access_ok);
पूर्ण

अटल व्योम dmafetch_onoff(काष्ठा mmp_overlay *overlay, पूर्णांक on)
अणु
	u32 mask = overlay_is_vid(overlay) ? CFG_DMA_ENA_MASK :
		   CFG_GRA_ENA_MASK;
	u32 enable = overlay_is_vid(overlay) ? CFG_DMA_ENA(1) : CFG_GRA_ENA(1);
	u32 पंचांगp;
	काष्ठा mmp_path *path = overlay->path;

	mutex_lock(&overlay->access_ok);
	पंचांगp = पढ़ोl_relaxed(ctrl_regs(path) + dma_ctrl(0, path->id));
	पंचांगp &= ~mask;
	पंचांगp |= (on ? enable : 0);
	ग_लिखोl(पंचांगp, ctrl_regs(path) + dma_ctrl(0, path->id));
	mutex_unlock(&overlay->access_ok);
पूर्ण

अटल व्योम path_enabledisable(काष्ठा mmp_path *path, पूर्णांक on)
अणु
	u32 पंचांगp;
	mutex_lock(&path->access_ok);
	पंचांगp = पढ़ोl_relaxed(ctrl_regs(path) + LCD_SCLK(path));
	अगर (on)
		पंचांगp &= ~SCLK_DISABLE;
	अन्यथा
		पंचांगp |= SCLK_DISABLE;
	ग_लिखोl_relaxed(पंचांगp, ctrl_regs(path) + LCD_SCLK(path));
	mutex_unlock(&path->access_ok);
पूर्ण

अटल व्योम path_onoff(काष्ठा mmp_path *path, पूर्णांक on)
अणु
	अगर (path->status == on) अणु
		dev_info(path->dev, "path %s is already %s\n",
				path->name, stat_name(path->status));
		वापस;
	पूर्ण

	अगर (on) अणु
		path_enabledisable(path, 1);

		अगर (path->panel && path->panel->set_onoff)
			path->panel->set_onoff(path->panel, 1);
	पूर्ण अन्यथा अणु
		अगर (path->panel && path->panel->set_onoff)
			path->panel->set_onoff(path->panel, 0);

		path_enabledisable(path, 0);
	पूर्ण
	path->status = on;
पूर्ण

अटल व्योम overlay_set_onoff(काष्ठा mmp_overlay *overlay, पूर्णांक on)
अणु
	अगर (overlay->status == on) अणु
		dev_info(overlay_to_ctrl(overlay)->dev, "overlay %s is already %s\n",
			overlay->path->name, stat_name(overlay->status));
		वापस;
	पूर्ण
	overlay->status = on;
	dmafetch_onoff(overlay, on);
	अगर (overlay->path->ops.check_status(overlay->path)
			!= overlay->path->status)
		path_onoff(overlay->path, on);
पूर्ण

अटल व्योम overlay_set_fetch(काष्ठा mmp_overlay *overlay, पूर्णांक fetch_id)
अणु
	overlay->dmafetch_id = fetch_id;
पूर्ण

अटल पूर्णांक overlay_set_addr(काष्ठा mmp_overlay *overlay, काष्ठा mmp_addr *addr)
अणु
	काष्ठा lcd_regs *regs = path_regs(overlay->path);

	/* FIXME: निश्चित addr supported */
	स_नकल(&overlay->addr, addr, माप(काष्ठा mmp_addr));

	अगर (overlay_is_vid(overlay)) अणु
		ग_लिखोl_relaxed(addr->phys[0], (व्योम __iomem *)&regs->v_y0);
		ग_लिखोl_relaxed(addr->phys[1], (व्योम __iomem *)&regs->v_u0);
		ग_लिखोl_relaxed(addr->phys[2], (व्योम __iomem *)&regs->v_v0);
	पूर्ण अन्यथा
		ग_लिखोl_relaxed(addr->phys[0], (व्योम __iomem *)&regs->g_0);

	वापस overlay->addr.phys[0];
पूर्ण

अटल व्योम path_set_mode(काष्ठा mmp_path *path, काष्ठा mmp_mode *mode)
अणु
	काष्ठा lcd_regs *regs = path_regs(path);
	u32 total_x, total_y, vsync_ctrl, पंचांगp, sclk_src, sclk_भाग,
		link_config = path_to_path_plat(path)->link_config,
		dsi_rbswap = path_to_path_plat(path)->link_config;

	/* FIXME: निश्चित videomode supported */
	स_नकल(&path->mode, mode, माप(काष्ठा mmp_mode));

	mutex_lock(&path->access_ok);

	/* polarity of timing संकेतs */
	पंचांगp = पढ़ोl_relaxed(ctrl_regs(path) + पूर्णांकf_ctrl(path->id)) & 0x1;
	पंचांगp |= mode->vsync_invert ? 0 : 0x8;
	पंचांगp |= mode->hsync_invert ? 0 : 0x4;
	पंचांगp |= link_config & CFG_DUMBMODE_MASK;
	पंचांगp |= CFG_DUMB_ENA(1);
	ग_लिखोl_relaxed(पंचांगp, ctrl_regs(path) + पूर्णांकf_ctrl(path->id));

	/* पूर्णांकerface rb_swap setting */
	पंचांगp = पढ़ोl_relaxed(ctrl_regs(path) + पूर्णांकf_rbswap_ctrl(path->id)) &
		(~(CFG_INTFRBSWAP_MASK));
	पंचांगp |= dsi_rbswap & CFG_INTFRBSWAP_MASK;
	ग_लिखोl_relaxed(पंचांगp, ctrl_regs(path) + पूर्णांकf_rbswap_ctrl(path->id));

	ग_लिखोl_relaxed((mode->yres << 16) | mode->xres,
		(व्योम __iomem *)&regs->screen_active);
	ग_लिखोl_relaxed((mode->left_margin << 16) | mode->right_margin,
		(व्योम __iomem *)&regs->screen_h_porch);
	ग_लिखोl_relaxed((mode->upper_margin << 16) | mode->lower_margin,
		(व्योम __iomem *)&regs->screen_v_porch);
	total_x = mode->xres + mode->left_margin + mode->right_margin +
		mode->hsync_len;
	total_y = mode->yres + mode->upper_margin + mode->lower_margin +
		mode->vsync_len;
	ग_लिखोl_relaxed((total_y << 16) | total_x,
		(व्योम __iomem *)&regs->screen_size);

	/* vsync ctrl */
	अगर (path->output_type == PATH_OUT_DSI)
		vsync_ctrl = 0x01330133;
	अन्यथा
		vsync_ctrl = ((mode->xres + mode->right_margin) << 16)
					| (mode->xres + mode->right_margin);
	ग_लिखोl_relaxed(vsync_ctrl, (व्योम __iomem *)&regs->vsync_ctrl);

	/* set pixघड़ी भाग */
	sclk_src = clk_get_rate(path_to_ctrl(path)->clk);
	sclk_भाग = sclk_src / mode->pixघड़ी_freq;
	अगर (sclk_भाग * mode->pixघड़ी_freq < sclk_src)
		sclk_भाग++;

	dev_info(path->dev, "%s sclk_src %d sclk_div 0x%x pclk %d\n",
			__func__, sclk_src, sclk_भाग, mode->pixघड़ी_freq);

	पंचांगp = पढ़ोl_relaxed(ctrl_regs(path) + LCD_SCLK(path));
	पंचांगp &= ~CLK_INT_DIV_MASK;
	पंचांगp |= sclk_भाग;
	ग_लिखोl_relaxed(पंचांगp, ctrl_regs(path) + LCD_SCLK(path));

	mutex_unlock(&path->access_ok);
पूर्ण

अटल काष्ठा mmp_overlay_ops mmphw_overlay_ops = अणु
	.set_fetch = overlay_set_fetch,
	.set_onoff = overlay_set_onoff,
	.set_win = overlay_set_win,
	.set_addr = overlay_set_addr,
पूर्ण;

अटल व्योम ctrl_set_शेष(काष्ठा mmphw_ctrl *ctrl)
अणु
	u32 पंचांगp, irq_mask;

	/*
	 * LCD Global control(LCD_TOP_CTRL) should be configed beक्रमe
	 * any other LCD रेजिस्टरs पढ़ो/ग_लिखो, or there maybe issues.
	 */
	पंचांगp = पढ़ोl_relaxed(ctrl->reg_base + LCD_TOP_CTRL);
	पंचांगp |= 0xfff0;
	ग_लिखोl_relaxed(पंचांगp, ctrl->reg_base + LCD_TOP_CTRL);


	/* disable all पूर्णांकerrupts */
	irq_mask = path_imasks(0) | err_imask(0) |
		   path_imasks(1) | err_imask(1);
	पंचांगp = पढ़ोl_relaxed(ctrl->reg_base + SPU_IRQ_ENA);
	पंचांगp &= ~irq_mask;
	पंचांगp |= irq_mask;
	ग_लिखोl_relaxed(पंचांगp, ctrl->reg_base + SPU_IRQ_ENA);
पूर्ण

अटल व्योम path_set_शेष(काष्ठा mmp_path *path)
अणु
	काष्ठा lcd_regs *regs = path_regs(path);
	u32 dma_ctrl1, mask, पंचांगp, path_config;

	path_config = path_to_path_plat(path)->path_config;

	/* Configure IOPAD: should be parallel only */
	अगर (PATH_OUT_PARALLEL == path->output_type) अणु
		mask = CFG_IOPADMODE_MASK | CFG_BURST_MASK | CFG_BOUNDARY_MASK;
		पंचांगp = पढ़ोl_relaxed(ctrl_regs(path) + SPU_IOPAD_CONTROL);
		पंचांगp &= ~mask;
		पंचांगp |= path_config;
		ग_लिखोl_relaxed(पंचांगp, ctrl_regs(path) + SPU_IOPAD_CONTROL);
	पूर्ण

	/* Select path घड़ी source */
	पंचांगp = पढ़ोl_relaxed(ctrl_regs(path) + LCD_SCLK(path));
	पंचांगp &= ~SCLK_SRC_SEL_MASK;
	पंचांगp |= path_config;
	ग_लिखोl_relaxed(पंचांगp, ctrl_regs(path) + LCD_SCLK(path));

	/*
	 * Configure शेष bits: vsync triggers DMA,
	 * घातer save enable, configure alpha रेजिस्टरs to
	 * display 100% graphics, and set pixel command.
	 */
	dma_ctrl1 = 0x2032ff81;

	dma_ctrl1 |= CFG_VSYNC_INV_MASK;
	ग_लिखोl_relaxed(dma_ctrl1, ctrl_regs(path) + dma_ctrl(1, path->id));

	/* Configure शेष रेजिस्टर values */
	ग_लिखोl_relaxed(0x00000000, (व्योम __iomem *)&regs->blank_color);
	ग_लिखोl_relaxed(0x00000000, (व्योम __iomem *)&regs->g_1);
	ग_लिखोl_relaxed(0x00000000, (व्योम __iomem *)&regs->g_start);

	/*
	 * 1.enable multiple burst request in DMA AXI
	 * bus arbiter क्रम faster पढ़ो अगर not tv path;
	 * 2.enable horizontal smooth filter;
	 */
	mask = CFG_GRA_HSMOOTH_MASK | CFG_DMA_HSMOOTH_MASK | CFG_ARBFAST_ENA(1);
	पंचांगp = पढ़ोl_relaxed(ctrl_regs(path) + dma_ctrl(0, path->id));
	पंचांगp |= mask;
	अगर (PATH_TV == path->id)
		पंचांगp &= ~CFG_ARBFAST_ENA(1);
	ग_लिखोl_relaxed(पंचांगp, ctrl_regs(path) + dma_ctrl(0, path->id));
पूर्ण

अटल पूर्णांक path_init(काष्ठा mmphw_path_plat *path_plat,
		काष्ठा mmp_mach_path_config *config)
अणु
	काष्ठा mmphw_ctrl *ctrl = path_plat->ctrl;
	काष्ठा mmp_path_info *path_info;
	काष्ठा mmp_path *path = शून्य;

	dev_info(ctrl->dev, "%s: %s\n", __func__, config->name);

	/* init driver data */
	path_info = kzalloc(माप(*path_info), GFP_KERNEL);
	अगर (!path_info)
		वापस 0;

	path_info->name = config->name;
	path_info->id = path_plat->id;
	path_info->dev = ctrl->dev;
	path_info->overlay_num = config->overlay_num;
	path_info->overlay_ops = &mmphw_overlay_ops;
	path_info->set_mode = path_set_mode;
	path_info->plat_data = path_plat;

	/* create/रेजिस्टर platक्रमm device */
	path = mmp_रेजिस्टर_path(path_info);
	अगर (!path) अणु
		kमुक्त(path_info);
		वापस 0;
	पूर्ण
	path_plat->path = path;
	path_plat->path_config = config->path_config;
	path_plat->link_config = config->link_config;
	path_plat->dsi_rbswap = config->dsi_rbswap;
	path_set_शेष(path);

	kमुक्त(path_info);
	वापस 1;
पूर्ण

अटल व्योम path_deinit(काष्ठा mmphw_path_plat *path_plat)
अणु
	अगर (!path_plat)
		वापस;

	mmp_unरेजिस्टर_path(path_plat->path);
पूर्ण

अटल पूर्णांक mmphw_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmp_mach_plat_info *mi;
	काष्ठा resource *res;
	पूर्णांक ret, i, irq;
	काष्ठा mmphw_path_plat *path_plat;
	काष्ठा mmphw_ctrl *ctrl = शून्य;

	/* get resources from platक्रमm data */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "%s: no IO memory defined\n", __func__);
		ret = -ENOENT;
		जाओ failed;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = -ENOENT;
		जाओ failed;
	पूर्ण

	/* get configs from platक्रमm data */
	mi = pdev->dev.platक्रमm_data;
	अगर (mi == शून्य || !mi->path_num || !mi->paths) अणु
		dev_err(&pdev->dev, "%s: no platform data defined\n", __func__);
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	/* allocate */
	ctrl = devm_kzalloc(&pdev->dev,
			    काष्ठा_size(ctrl, path_plats, mi->path_num),
			    GFP_KERNEL);
	अगर (!ctrl) अणु
		ret = -ENOMEM;
		जाओ failed;
	पूर्ण

	ctrl->name = mi->name;
	ctrl->path_num = mi->path_num;
	ctrl->dev = &pdev->dev;
	ctrl->irq = irq;
	platक्रमm_set_drvdata(pdev, ctrl);
	mutex_init(&ctrl->access_ok);

	/* map रेजिस्टरs.*/
	अगर (!devm_request_mem_region(ctrl->dev, res->start,
			resource_size(res), ctrl->name)) अणु
		dev_err(ctrl->dev,
			"can't request region for resource %pR\n", res);
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	ctrl->reg_base = devm_ioremap(ctrl->dev,
			res->start, resource_size(res));
	अगर (ctrl->reg_base == शून्य) अणु
		dev_err(ctrl->dev, "%s: res %pR map failed\n", __func__, res);
		ret = -ENOMEM;
		जाओ failed;
	पूर्ण

	/* request irq */
	ret = devm_request_irq(ctrl->dev, ctrl->irq, ctrl_handle_irq,
		IRQF_SHARED, "lcd_controller", ctrl);
	अगर (ret < 0) अणु
		dev_err(ctrl->dev, "%s unable to request IRQ %d\n",
				__func__, ctrl->irq);
		ret = -ENXIO;
		जाओ failed;
	पूर्ण

	/* get घड़ी */
	ctrl->clk = devm_clk_get(ctrl->dev, mi->clk_name);
	अगर (IS_ERR(ctrl->clk)) अणु
		dev_err(ctrl->dev, "unable to get clk %s\n", mi->clk_name);
		ret = -ENOENT;
		जाओ failed;
	पूर्ण
	clk_prepare_enable(ctrl->clk);

	/* init global regs */
	ctrl_set_शेष(ctrl);

	/* init pathes from machine info and रेजिस्टर them */
	क्रम (i = 0; i < ctrl->path_num; i++) अणु
		/* get from config and machine info */
		path_plat = &ctrl->path_plats[i];
		path_plat->id = i;
		path_plat->ctrl = ctrl;

		/* path init */
		अगर (!path_init(path_plat, &mi->paths[i])) अणु
			ret = -EINVAL;
			जाओ failed_path_init;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_MMP_DISP_SPI
	ret = lcd_spi_रेजिस्टर(ctrl);
	अगर (ret < 0)
		जाओ failed_path_init;
#पूर्ण_अगर

	dev_info(ctrl->dev, "device init done\n");

	वापस 0;

failed_path_init:
	क्रम (i = 0; i < ctrl->path_num; i++) अणु
		path_plat = &ctrl->path_plats[i];
		path_deinit(path_plat);
	पूर्ण

	clk_disable_unprepare(ctrl->clk);
failed:
	dev_err(&pdev->dev, "device init failed\n");

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver mmphw_driver = अणु
	.driver		= अणु
		.name	= "mmp-disp",
	पूर्ण,
	.probe		= mmphw_probe,
पूर्ण;

अटल पूर्णांक mmphw_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mmphw_driver);
पूर्ण
module_init(mmphw_init);

MODULE_AUTHOR("Li Guoqing<ligq@marvell.com>");
MODULE_DESCRIPTION("Framebuffer driver for mmp");
MODULE_LICENSE("GPL");
