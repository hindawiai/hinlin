<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2018-2020 Intel Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "kmb_drv.h"
#समावेश "kmb_dsi.h"
#समावेश "kmb_regs.h"

अटल पूर्णांक kmb_display_clk_enable(काष्ठा kmb_drm_निजी *kmb)
अणु
	पूर्णांक ret = 0;

	ret = clk_prepare_enable(kmb->kmb_clk.clk_lcd);
	अगर (ret) अणु
		drm_err(&kmb->drm, "Failed to enable LCD clock: %d\n", ret);
		वापस ret;
	पूर्ण
	DRM_INFO("SUCCESS : enabled LCD clocks\n");
	वापस 0;
पूर्ण

अटल पूर्णांक kmb_initialize_घड़ीs(काष्ठा kmb_drm_निजी *kmb, काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा regmap *msscam;

	kmb->kmb_clk.clk_lcd = devm_clk_get(dev, "clk_lcd");
	अगर (IS_ERR(kmb->kmb_clk.clk_lcd)) अणु
		drm_err(&kmb->drm, "clk_get() failed clk_lcd\n");
		वापस PTR_ERR(kmb->kmb_clk.clk_lcd);
	पूर्ण

	kmb->kmb_clk.clk_pll0 = devm_clk_get(dev, "clk_pll0");
	अगर (IS_ERR(kmb->kmb_clk.clk_pll0)) अणु
		drm_err(&kmb->drm, "clk_get() failed clk_pll0 ");
		वापस PTR_ERR(kmb->kmb_clk.clk_pll0);
	पूर्ण
	kmb->sys_clk_mhz = clk_get_rate(kmb->kmb_clk.clk_pll0) / 1000000;
	drm_info(&kmb->drm, "system clk = %d Mhz", kmb->sys_clk_mhz);

	ret =  kmb_dsi_clk_init(kmb->kmb_dsi);

	/* Set LCD घड़ी to 200 Mhz */
	clk_set_rate(kmb->kmb_clk.clk_lcd, KMB_LCD_DEFAULT_CLK);
	अगर (clk_get_rate(kmb->kmb_clk.clk_lcd) != KMB_LCD_DEFAULT_CLK) अणु
		drm_err(&kmb->drm, "failed to set to clk_lcd to %d\n",
			KMB_LCD_DEFAULT_CLK);
		वापस -1;
	पूर्ण
	drm_dbg(&kmb->drm, "clk_lcd = %ld\n", clk_get_rate(kmb->kmb_clk.clk_lcd));

	ret = kmb_display_clk_enable(kmb);
	अगर (ret)
		वापस ret;

	msscam = syscon_regmap_lookup_by_compatible("intel,keembay-msscam");
	अगर (IS_ERR(msscam)) अणु
		drm_err(&kmb->drm, "failed to get msscam syscon");
		वापस -1;
	पूर्ण

	/* Enable MSS_CAM_CLK_CTRL क्रम MIPI TX and LCD */
	regmap_update_bits(msscam, MSS_CAM_CLK_CTRL, 0x1fff, 0x1fff);
	regmap_update_bits(msscam, MSS_CAM_RSTN_CTRL, 0xffffffff, 0xffffffff);
	वापस 0;
पूर्ण

अटल व्योम kmb_display_clk_disable(काष्ठा kmb_drm_निजी *kmb)
अणु
	clk_disable_unprepare(kmb->kmb_clk.clk_lcd);
पूर्ण

अटल व्योम __iomem *kmb_map_mmio(काष्ठा drm_device *drm,
				  काष्ठा platक्रमm_device *pdev,
				  अक्षर *name)
अणु
	काष्ठा resource *res;
	व्योम __iomem *mem;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, name);
	अगर (!res) अणु
		drm_err(drm, "failed to get resource for %s", name);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	mem = devm_ioremap_resource(drm->dev, res);
	अगर (IS_ERR(mem))
		drm_err(drm, "failed to ioremap %s registers", name);
	वापस mem;
पूर्ण

अटल पूर्णांक kmb_hw_init(काष्ठा drm_device *drm, अचिन्हित दीर्घ flags)
अणु
	काष्ठा kmb_drm_निजी *kmb = to_kmb(drm);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(drm->dev);
	पूर्णांक irq_lcd;
	पूर्णांक ret = 0;

	/* Map LCD MMIO रेजिस्टरs */
	kmb->lcd_mmio = kmb_map_mmio(drm, pdev, "lcd");
	अगर (IS_ERR(kmb->lcd_mmio)) अणु
		drm_err(&kmb->drm, "failed to map LCD registers\n");
		वापस -ENOMEM;
	पूर्ण

	/* Map MIPI MMIO रेजिस्टरs */
	ret = kmb_dsi_map_mmio(kmb->kmb_dsi);
	अगर (ret)
		वापस ret;

	/* Enable display घड़ीs */
	kmb_initialize_घड़ीs(kmb, &pdev->dev);

	/* Register irqs here - section 17.3 in databook
	 * lists LCD at 79 and 82 क्रम MIPI under MSS CPU -
	 * firmware has redirected 79 to A53 IRQ 33
	 */

	/* Allocate LCD पूर्णांकerrupt resources */
	irq_lcd = platक्रमm_get_irq(pdev, 0);
	अगर (irq_lcd < 0) अणु
		drm_err(&kmb->drm, "irq_lcd not found");
		जाओ setup_fail;
	पूर्ण

	/* Get the optional framebuffer memory resource */
	ret = of_reserved_mem_device_init(drm->dev);
	अगर (ret && ret != -ENODEV)
		वापस ret;

	spin_lock_init(&kmb->irq_lock);

	kmb->irq_lcd = irq_lcd;

	वापस 0;

 setup_fail:
	of_reserved_mem_device_release(drm->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs kmb_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक kmb_setup_mode_config(काष्ठा drm_device *drm)
अणु
	पूर्णांक ret;
	काष्ठा kmb_drm_निजी *kmb = to_kmb(drm);

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		वापस ret;
	drm->mode_config.min_width = KMB_MIN_WIDTH;
	drm->mode_config.min_height = KMB_MIN_HEIGHT;
	drm->mode_config.max_width = KMB_MAX_WIDTH;
	drm->mode_config.max_height = KMB_MAX_HEIGHT;
	drm->mode_config.funcs = &kmb_mode_config_funcs;

	ret = kmb_setup_crtc(drm);
	अगर (ret < 0) अणु
		drm_err(drm, "failed to create crtc\n");
		वापस ret;
	पूर्ण
	ret = kmb_dsi_encoder_init(drm, kmb->kmb_dsi);
	/* Set the CRTC's port so that the encoder component can find it */
	kmb->crtc.port = of_graph_get_port_by_id(drm->dev->of_node, 0);
	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	अगर (ret < 0) अणु
		drm_err(drm, "failed to initialize vblank\n");
		pm_runसमय_disable(drm->dev);
		वापस ret;
	पूर्ण

	drm_mode_config_reset(drm);
	वापस 0;
पूर्ण

अटल irqवापस_t handle_lcd_irq(काष्ठा drm_device *dev)
अणु
	अचिन्हित दीर्घ status, val, val1;
	पूर्णांक plane_id, dma0_state, dma1_state;
	काष्ठा kmb_drm_निजी *kmb = to_kmb(dev);

	status = kmb_पढ़ो_lcd(kmb, LCD_INT_STATUS);

	spin_lock(&kmb->irq_lock);
	अगर (status & LCD_INT_खातापूर्ण) अणु
		kmb_ग_लिखो_lcd(kmb, LCD_INT_CLEAR, LCD_INT_खातापूर्ण);

		/* When disabling/enabling LCD layers, the change takes effect
		 * immediately and करोes not रुको क्रम खातापूर्ण (end of frame).
		 * When kmb_plane_atomic_disable is called, mark the plane as
		 * disabled but actually disable the plane when खातापूर्ण irq is
		 * being handled.
		 */
		क्रम (plane_id = LAYER_0;
				plane_id < KMB_MAX_PLANES; plane_id++) अणु
			अगर (kmb->plane_status[plane_id].disable) अणु
				kmb_clr_biपंचांगask_lcd(kmb,
						    LCD_LAYERn_DMA_CFG
						    (plane_id),
						    LCD_DMA_LAYER_ENABLE);

				kmb_clr_biपंचांगask_lcd(kmb, LCD_CONTROL,
						    kmb->plane_status[plane_id].ctrl);

				kmb->plane_status[plane_id].disable = false;
			पूर्ण
		पूर्ण
		अगर (kmb->kmb_under_flow) अणु
			/* DMA Recovery after underflow */
			dma0_state = (kmb->layer_no == 0) ?
			    LCD_VIDEO0_DMA0_STATE : LCD_VIDEO1_DMA0_STATE;
			dma1_state = (kmb->layer_no == 0) ?
			    LCD_VIDEO0_DMA1_STATE : LCD_VIDEO1_DMA1_STATE;

			करो अणु
				kmb_ग_लिखो_lcd(kmb, LCD_FIFO_FLUSH, 1);
				val = kmb_पढ़ो_lcd(kmb, dma0_state)
				    & LCD_DMA_STATE_ACTIVE;
				val1 = kmb_पढ़ो_lcd(kmb, dma1_state)
				    & LCD_DMA_STATE_ACTIVE;
			पूर्ण जबतक ((val || val1));
			/* disable dma */
			kmb_clr_biपंचांगask_lcd(kmb,
					    LCD_LAYERn_DMA_CFG(kmb->layer_no),
					    LCD_DMA_LAYER_ENABLE);
			kmb_ग_लिखो_lcd(kmb, LCD_FIFO_FLUSH, 1);
			kmb->kmb_flush_करोne = 1;
			kmb->kmb_under_flow = 0;
		पूर्ण
	पूर्ण

	अगर (status & LCD_INT_LINE_CMP) अणु
		/* clear line compare पूर्णांकerrupt */
		kmb_ग_लिखो_lcd(kmb, LCD_INT_CLEAR, LCD_INT_LINE_CMP);
	पूर्ण

	अगर (status & LCD_INT_VERT_COMP) अणु
		/* Read VSTATUS */
		val = kmb_पढ़ो_lcd(kmb, LCD_VSTATUS);
		val = (val & LCD_VSTATUS_VERTICAL_STATUS_MASK);
		चयन (val) अणु
		हाल LCD_VSTATUS_COMPARE_VSYNC:
			/* Clear vertical compare पूर्णांकerrupt */
			kmb_ग_लिखो_lcd(kmb, LCD_INT_CLEAR, LCD_INT_VERT_COMP);
			अगर (kmb->kmb_flush_करोne) अणु
				kmb_set_biपंचांगask_lcd(kmb,
						    LCD_LAYERn_DMA_CFG
						    (kmb->layer_no),
						    LCD_DMA_LAYER_ENABLE);
				kmb->kmb_flush_करोne = 0;
			पूर्ण
			drm_crtc_handle_vblank(&kmb->crtc);
			अवरोध;
		हाल LCD_VSTATUS_COMPARE_BACKPORCH:
		हाल LCD_VSTATUS_COMPARE_ACTIVE:
		हाल LCD_VSTATUS_COMPARE_FRONT_PORCH:
			kmb_ग_लिखो_lcd(kmb, LCD_INT_CLEAR, LCD_INT_VERT_COMP);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (status & LCD_INT_DMA_ERR) अणु
		val =
		    (status & LCD_INT_DMA_ERR &
		     kmb_पढ़ो_lcd(kmb, LCD_INT_ENABLE));
		/* LAYER0 - VL0 */
		अगर (val & (LAYER0_DMA_FIFO_UNDERFLOW |
			   LAYER0_DMA_CB_FIFO_UNDERFLOW |
			   LAYER0_DMA_CR_FIFO_UNDERFLOW)) अणु
			kmb->kmb_under_flow++;
			drm_info(&kmb->drm,
				 "!LAYER0:VL0 DMA UNDERFLOW val = 0x%lx,under_flow=%d",
			     val, kmb->kmb_under_flow);
			/* disable underflow पूर्णांकerrupt */
			kmb_clr_biपंचांगask_lcd(kmb, LCD_INT_ENABLE,
					    LAYER0_DMA_FIFO_UNDERFLOW |
					    LAYER0_DMA_CB_FIFO_UNDERFLOW |
					    LAYER0_DMA_CR_FIFO_UNDERFLOW);
			kmb_set_biपंचांगask_lcd(kmb, LCD_INT_CLEAR,
					    LAYER0_DMA_CB_FIFO_UNDERFLOW |
					    LAYER0_DMA_FIFO_UNDERFLOW |
					    LAYER0_DMA_CR_FIFO_UNDERFLOW);
			/* disable स्वतः restart mode */
			kmb_clr_biपंचांगask_lcd(kmb, LCD_LAYERn_DMA_CFG(0),
					    LCD_DMA_LAYER_CONT_PING_PONG_UPDATE);

			kmb->layer_no = 0;
		पूर्ण

		अगर (val & LAYER0_DMA_FIFO_OVERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER0:VL0 DMA OVERFLOW val = 0x%lx", val);
		अगर (val & LAYER0_DMA_CB_FIFO_OVERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER0:VL0 DMA CB OVERFLOW val = 0x%lx", val);
		अगर (val & LAYER0_DMA_CR_FIFO_OVERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER0:VL0 DMA CR OVERFLOW val = 0x%lx", val);

		/* LAYER1 - VL1 */
		अगर (val & (LAYER1_DMA_FIFO_UNDERFLOW |
			   LAYER1_DMA_CB_FIFO_UNDERFLOW |
			   LAYER1_DMA_CR_FIFO_UNDERFLOW)) अणु
			kmb->kmb_under_flow++;
			drm_info(&kmb->drm,
				 "!LAYER1:VL1 DMA UNDERFLOW val = 0x%lx, under_flow=%d",
			     val, kmb->kmb_under_flow);
			/* disable underflow पूर्णांकerrupt */
			kmb_clr_biपंचांगask_lcd(kmb, LCD_INT_ENABLE,
					    LAYER1_DMA_FIFO_UNDERFLOW |
					    LAYER1_DMA_CB_FIFO_UNDERFLOW |
					    LAYER1_DMA_CR_FIFO_UNDERFLOW);
			kmb_set_biपंचांगask_lcd(kmb, LCD_INT_CLEAR,
					    LAYER1_DMA_CB_FIFO_UNDERFLOW |
					    LAYER1_DMA_FIFO_UNDERFLOW |
					    LAYER1_DMA_CR_FIFO_UNDERFLOW);
			/* disable स्वतः restart mode */
			kmb_clr_biपंचांगask_lcd(kmb, LCD_LAYERn_DMA_CFG(1),
					    LCD_DMA_LAYER_CONT_PING_PONG_UPDATE);
			kmb->layer_no = 1;
		पूर्ण

		/* LAYER1 - VL1 */
		अगर (val & LAYER1_DMA_FIFO_OVERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER1:VL1 DMA OVERFLOW val = 0x%lx", val);
		अगर (val & LAYER1_DMA_CB_FIFO_OVERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER1:VL1 DMA CB OVERFLOW val = 0x%lx", val);
		अगर (val & LAYER1_DMA_CR_FIFO_OVERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER1:VL1 DMA CR OVERFLOW val = 0x%lx", val);

		/* LAYER2 - GL0 */
		अगर (val & LAYER2_DMA_FIFO_UNDERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER2:GL0 DMA UNDERFLOW val = 0x%lx", val);
		अगर (val & LAYER2_DMA_FIFO_OVERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER2:GL0 DMA OVERFLOW val = 0x%lx", val);

		/* LAYER3 - GL1 */
		अगर (val & LAYER3_DMA_FIFO_UNDERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER3:GL1 DMA UNDERFLOW val = 0x%lx", val);
		अगर (val & LAYER3_DMA_FIFO_UNDERFLOW)
			drm_dbg(&kmb->drm,
				"LAYER3:GL1 DMA OVERFLOW val = 0x%lx", val);
	पूर्ण

	spin_unlock(&kmb->irq_lock);

	अगर (status & LCD_INT_LAYER) अणु
		/* Clear layer पूर्णांकerrupts */
		kmb_ग_लिखो_lcd(kmb, LCD_INT_CLEAR, LCD_INT_LAYER);
	पूर्ण

	/* Clear all पूर्णांकerrupts */
	kmb_set_biपंचांगask_lcd(kmb, LCD_INT_CLEAR, 1);
	वापस IRQ_HANDLED;
पूर्ण

/* IRQ handler */
अटल irqवापस_t kmb_isr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *)arg;

	handle_lcd_irq(dev);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम kmb_irq_reset(काष्ठा drm_device *drm)
अणु
	kmb_ग_लिखो_lcd(to_kmb(drm), LCD_INT_CLEAR, 0xFFFF);
	kmb_ग_लिखो_lcd(to_kmb(drm), LCD_INT_ENABLE, 0);
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(fops);

अटल स्थिर काष्ठा drm_driver kmb_driver = अणु
	.driver_features = DRIVER_GEM |
	    DRIVER_MODESET | DRIVER_ATOMIC,
	.irq_handler = kmb_isr,
	.irq_preinstall = kmb_irq_reset,
	.irq_uninstall = kmb_irq_reset,
	/* GEM Operations */
	.fops = &fops,
	DRM_GEM_CMA_DRIVER_OPS_VMAP,
	.name = "kmb-drm",
	.desc = "KEEMBAY DISPLAY DRIVER ",
	.date = "20201008",
	.major = 1,
	.minor = 0,
पूर्ण;

अटल पूर्णांक kmb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा kmb_drm_निजी *kmb = to_kmb(drm);

	drm_dev_unरेजिस्टर(drm);
	drm_kms_helper_poll_fini(drm);
	of_node_put(kmb->crtc.port);
	kmb->crtc.port = शून्य;
	pm_runसमय_get_sync(drm->dev);
	drm_irq_uninstall(drm);
	pm_runसमय_put_sync(drm->dev);
	pm_runसमय_disable(drm->dev);

	of_reserved_mem_device_release(drm->dev);

	/* Release clks */
	kmb_display_clk_disable(kmb);

	dev_set_drvdata(dev, शून्य);

	/* Unरेजिस्टर DSI host */
	kmb_dsi_host_unरेजिस्टर(kmb->kmb_dsi);
	drm_atomic_helper_shutकरोwn(drm);
	वापस 0;
पूर्ण

अटल पूर्णांक kmb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = get_device(&pdev->dev);
	काष्ठा kmb_drm_निजी *kmb;
	पूर्णांक ret = 0;
	काष्ठा device_node *dsi_in;
	काष्ठा device_node *dsi_node;
	काष्ठा platक्रमm_device *dsi_pdev;

	/* The bridge (ADV 7535) will वापस -EPROBE_DEFER until it
	 * has a mipi_dsi_host to रेजिस्टर its device to. So, we
	 * first रेजिस्टर the DSI host during probe समय, and then वापस
	 * -EPROBE_DEFER until the bridge is loaded. Probe will be called again
	 *  and then the rest of the driver initialization can proceed
	 *  afterwards and the bridge can be successfully attached.
	 */
	dsi_in = of_graph_get_endpoपूर्णांक_by_regs(dev->of_node, 0, 0);
	अगर (!dsi_in) अणु
		DRM_ERROR("Failed to get dsi_in node info from DT");
		वापस -EINVAL;
	पूर्ण
	dsi_node = of_graph_get_remote_port_parent(dsi_in);
	अगर (!dsi_node) अणु
		of_node_put(dsi_in);
		DRM_ERROR("Failed to get dsi node from DT\n");
		वापस -EINVAL;
	पूर्ण

	dsi_pdev = of_find_device_by_node(dsi_node);
	अगर (!dsi_pdev) अणु
		of_node_put(dsi_in);
		of_node_put(dsi_node);
		DRM_ERROR("Failed to get dsi platform device\n");
		वापस -EINVAL;
	पूर्ण

	of_node_put(dsi_in);
	of_node_put(dsi_node);
	ret = kmb_dsi_host_bridge_init(get_device(&dsi_pdev->dev));

	अगर (ret == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (ret) अणु
		DRM_ERROR("probe failed to initialize DSI host bridge\n");
		वापस ret;
	पूर्ण

	/* Create DRM device */
	kmb = devm_drm_dev_alloc(dev, &kmb_driver,
				 काष्ठा kmb_drm_निजी, drm);
	अगर (IS_ERR(kmb))
		वापस PTR_ERR(kmb);

	dev_set_drvdata(dev, &kmb->drm);

	/* Initialize MIPI DSI */
	kmb->kmb_dsi = kmb_dsi_init(dsi_pdev);
	अगर (IS_ERR(kmb->kmb_dsi)) अणु
		drm_err(&kmb->drm, "failed to initialize DSI\n");
		ret = PTR_ERR(kmb->kmb_dsi);
		जाओ err_मुक्त1;
	पूर्ण

	kmb->kmb_dsi->dev = &dsi_pdev->dev;
	kmb->kmb_dsi->pdev = dsi_pdev;
	ret = kmb_hw_init(&kmb->drm, 0);
	अगर (ret)
		जाओ err_मुक्त1;

	ret = kmb_setup_mode_config(&kmb->drm);
	अगर (ret)
		जाओ err_मुक्त;

	ret = drm_irq_install(&kmb->drm, kmb->irq_lcd);
	अगर (ret < 0) अणु
		drm_err(&kmb->drm, "failed to install IRQ handler\n");
		जाओ err_irq;
	पूर्ण

	drm_kms_helper_poll_init(&kmb->drm);

	/* Register graphics device with the kernel */
	ret = drm_dev_रेजिस्टर(&kmb->drm, 0);
	अगर (ret)
		जाओ err_रेजिस्टर;

	वापस 0;

 err_रेजिस्टर:
	drm_kms_helper_poll_fini(&kmb->drm);
 err_irq:
	pm_runसमय_disable(kmb->drm.dev);
 err_मुक्त:
	drm_crtc_cleanup(&kmb->crtc);
	drm_mode_config_cleanup(&kmb->drm);
 err_मुक्त1:
	dev_set_drvdata(dev, शून्य);
	kmb_dsi_host_unरेजिस्टर(kmb->kmb_dsi);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id kmb_of_match[] = अणु
	अणु.compatible = "intel,keembay-display"पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, kmb_of_match);

अटल पूर्णांक __maybe_unused kmb_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा kmb_drm_निजी *kmb = to_kmb(drm);

	drm_kms_helper_poll_disable(drm);

	kmb->state = drm_atomic_helper_suspend(drm);
	अगर (IS_ERR(kmb->state)) अणु
		drm_kms_helper_poll_enable(drm);
		वापस PTR_ERR(kmb->state);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused kmb_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा kmb_drm_निजी *kmb = drm ? to_kmb(drm) : शून्य;

	अगर (!kmb)
		वापस 0;

	drm_atomic_helper_resume(drm, kmb->state);
	drm_kms_helper_poll_enable(drm);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(kmb_pm_ops, kmb_pm_suspend, kmb_pm_resume);

अटल काष्ठा platक्रमm_driver kmb_platक्रमm_driver = अणु
	.probe = kmb_probe,
	.हटाओ = kmb_हटाओ,
	.driver = अणु
		.name = "kmb-drm",
		.pm = &kmb_pm_ops,
		.of_match_table = kmb_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(kmb_platक्रमm_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("Keembay Display driver");
MODULE_LICENSE("GPL v2");
