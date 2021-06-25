<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम the camera device found on Marvell MMP processors; known
 * to work with the Armada 610 as used in the OLPC 1.75 प्रणाली.
 *
 * Copyright 2011 Jonathan Corbet <corbet@lwn.net>
 * Copyright 2018 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <linux/platक्रमm_data/media/mmp-camera.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/pm.h>
#समावेश <linux/clk.h>

#समावेश "mcam-core.h"

MODULE_ALIAS("platform:mmp-camera");
MODULE_AUTHOR("Jonathan Corbet <corbet@lwn.net>");
MODULE_LICENSE("GPL");

अटल अक्षर *mcam_clks[] = अणु"axi", "func", "phy"पूर्ण;

काष्ठा mmp_camera अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mcam_camera mcam;
	काष्ठा list_head devlist;
	काष्ठा clk *mipi_clk;
	पूर्णांक irq;
पूर्ण;

अटल अंतरभूत काष्ठा mmp_camera *mcam_to_cam(काष्ठा mcam_camera *mcam)
अणु
	वापस container_of(mcam, काष्ठा mmp_camera, mcam);
पूर्ण

/*
 * calc the dphy रेजिस्टर values
 * There are three dphy रेजिस्टरs being used.
 * dphy[0] - CSI2_DPHY3
 * dphy[1] - CSI2_DPHY5
 * dphy[2] - CSI2_DPHY6
 * CSI2_DPHY3 and CSI2_DPHY6 can be set with a शेष value
 * or be calculated dynamically
 */
अटल व्योम mmpcam_calc_dphy(काष्ठा mcam_camera *mcam)
अणु
	काष्ठा mmp_camera *cam = mcam_to_cam(mcam);
	काष्ठा mmp_camera_platक्रमm_data *pdata = cam->pdev->dev.platक्रमm_data;
	काष्ठा device *dev = &cam->pdev->dev;
	अचिन्हित दीर्घ tx_clk_esc;

	/*
	 * If CSI2_DPHY3 is calculated dynamically,
	 * pdata->lane_clk should be alपढ़ोy set
	 * either in the board driver अटलally
	 * or in the sensor driver dynamically.
	 */
	/*
	 * dphy[0] - CSI2_DPHY3:
	 *  bit 0 ~ bit 7: HS Term Enable.
	 *   defines the समय that the DPHY
	 *   रुको beक्रमe enabling the data
	 *   lane termination after detecting
	 *   that the sensor has driven the data
	 *   lanes to the LP00 bridge state.
	 *   The value is calculated by:
	 *   (Max T(D_TERM_EN)/Period(DDR)) - 1
	 *  bit 8 ~ bit 15: HS_SETTLE
	 *   Time पूर्णांकerval during which the HS
	 *   receiver shall ignore any Data Lane
	 *   HS transitions.
	 *   The value has been calibrated on
	 *   dअगरferent boards. It seems to work well.
	 *
	 *  More detail please refer
	 *  MIPI Alliance Spectअगरication क्रम D-PHY
	 *  करोcument क्रम explanation of HS-SETTLE
	 *  and D-TERM-EN.
	 */
	चयन (pdata->dphy3_algo) अणु
	हाल DPHY3_ALGO_PXA910:
		/*
		 * Calculate CSI2_DPHY3 algo क्रम PXA910
		 */
		pdata->dphy[0] =
			(((1 + (pdata->lane_clk * 80) / 1000) & 0xff) << 8)
			| (1 + pdata->lane_clk * 35 / 1000);
		अवरोध;
	हाल DPHY3_ALGO_PXA2128:
		/*
		 * Calculate CSI2_DPHY3 algo क्रम PXA2128
		 */
		pdata->dphy[0] =
			(((2 + (pdata->lane_clk * 110) / 1000) & 0xff) << 8)
			| (1 + pdata->lane_clk * 35 / 1000);
		अवरोध;
	शेष:
		/*
		 * Use शेष CSI2_DPHY3 value क्रम PXA688/PXA988
		 */
		dev_dbg(dev, "camera: use the default CSI2_DPHY3 value\n");
	पूर्ण

	/*
	 * mipi_clk will never be changed, it is a fixed value on MMP
	 */
	अगर (IS_ERR(cam->mipi_clk))
		वापस;

	/* get the escape clk, this is hard coded */
	clk_prepare_enable(cam->mipi_clk);
	tx_clk_esc = (clk_get_rate(cam->mipi_clk) / 1000000) / 12;
	clk_disable_unprepare(cam->mipi_clk);
	/*
	 * dphy[2] - CSI2_DPHY6:
	 * bit 0 ~ bit 7: CK Term Enable
	 *  Time क्रम the Clock Lane receiver to enable the HS line
	 *  termination. The value is calculated similarly with
	 *  HS Term Enable
	 * bit 8 ~ bit 15: CK Settle
	 *  Time पूर्णांकerval during which the HS receiver shall ignore
	 *  any Clock Lane HS transitions.
	 *  The value is calibrated on the boards.
	 */
	pdata->dphy[2] =
		((((534 * tx_clk_esc) / 2000 - 1) & 0xff) << 8)
		| (((38 * tx_clk_esc) / 1000 - 1) & 0xff);

	dev_dbg(dev, "camera: DPHY sets: dphy3=0x%x, dphy5=0x%x, dphy6=0x%x\n",
		pdata->dphy[0], pdata->dphy[1], pdata->dphy[2]);
पूर्ण

अटल irqवापस_t mmpcam_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mcam_camera *mcam = data;
	अचिन्हित पूर्णांक irqs, handled;

	spin_lock(&mcam->dev_lock);
	irqs = mcam_reg_पढ़ो(mcam, REG_IRQSTAT);
	handled = mccic_irq(mcam, irqs);
	spin_unlock(&mcam->dev_lock);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम mcam_init_clk(काष्ठा mcam_camera *mcam)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NR_MCAM_CLK; i++) अणु
		अगर (mcam_clks[i] != शून्य) अणु
			/* Some clks are not necessary on some boards
			 * We still try to run even it fails getting clk
			 */
			mcam->clk[i] = devm_clk_get(mcam->dev, mcam_clks[i]);
			अगर (IS_ERR(mcam->clk[i]))
				dev_warn(mcam->dev, "Could not get clk: %s\n",
						mcam_clks[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mmpcam_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmp_camera *cam;
	काष्ठा mcam_camera *mcam;
	काष्ठा resource *res;
	काष्ठा fwnode_handle *ep;
	काष्ठा mmp_camera_platक्रमm_data *pdata;
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret;

	cam = devm_kzalloc(&pdev->dev, माप(*cam), GFP_KERNEL);
	अगर (cam == शून्य)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, cam);
	cam->pdev = pdev;
	INIT_LIST_HEAD(&cam->devlist);

	mcam = &cam->mcam;
	mcam->calc_dphy = mmpcam_calc_dphy;
	mcam->dev = &pdev->dev;
	pdata = pdev->dev.platक्रमm_data;
	अगर (pdata) अणु
		mcam->mclk_src = pdata->mclk_src;
		mcam->mclk_भाग = pdata->mclk_भाग;
		mcam->bus_type = pdata->bus_type;
		mcam->dphy = pdata->dphy;
		mcam->lane = pdata->lane;
	पूर्ण अन्यथा अणु
		/*
		 * These are values that used to be hardcoded in mcam-core and
		 * work well on a OLPC XO 1.75 with a parallel bus sensor.
		 * If it turns out other setups make sense, the values should
		 * be obtained from the device tree.
		 */
		mcam->mclk_src = 3;
		mcam->mclk_भाग = 2;
	पूर्ण
	अगर (mcam->bus_type == V4L2_MBUS_CSI2_DPHY) अणु
		cam->mipi_clk = devm_clk_get(mcam->dev, "mipi");
		अगर ((IS_ERR(cam->mipi_clk) && mcam->dphy[2] == 0))
			वापस PTR_ERR(cam->mipi_clk);
	पूर्ण
	mcam->mipi_enabled = false;
	mcam->chip_id = MCAM_ARMADA610;
	mcam->buffer_mode = B_DMA_sg;
	strscpy(mcam->bus_info, "platform:mmp-camera", माप(mcam->bus_info));
	spin_lock_init(&mcam->dev_lock);
	/*
	 * Get our I/O memory.
	 */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mcam->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mcam->regs))
		वापस PTR_ERR(mcam->regs);
	mcam->regs_size = resource_size(res);

	mcam_init_clk(mcam);

	/*
	 * Create a match of the sensor against its OF node.
	 */
	ep = fwnode_graph_get_next_endpoपूर्णांक(of_fwnode_handle(pdev->dev.of_node),
					    शून्य);
	अगर (!ep)
		वापस -ENODEV;

	v4l2_async_notअगरier_init(&mcam->notअगरier);

	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(&mcam->notअगरier, ep,
							   काष्ठा v4l2_async_subdev);
	fwnode_handle_put(ep);
	अगर (IS_ERR(asd)) अणु
		ret = PTR_ERR(asd);
		जाओ out;
	पूर्ण

	/*
	 * Register the device with the core.
	 */
	ret = mccic_रेजिस्टर(mcam);
	अगर (ret)
		वापस ret;

	/*
	 * Add OF घड़ी provider.
	 */
	ret = of_clk_add_provider(pdev->dev.of_node, of_clk_src_simple_get,
								mcam->mclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't add DT clock provider\n");
		जाओ out;
	पूर्ण

	/*
	 * Finally, set up our IRQ now that the core is पढ़ोy to
	 * deal with it.
	 */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res == शून्य) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	cam->irq = res->start;
	ret = devm_request_irq(&pdev->dev, cam->irq, mmpcam_irq, IRQF_SHARED,
					"mmp-camera", mcam);
	अगर (ret)
		जाओ out;

	pm_runसमय_enable(&pdev->dev);
	वापस 0;
out:
	mccic_shutकरोwn(mcam);

	वापस ret;
पूर्ण


अटल पूर्णांक mmpcam_हटाओ(काष्ठा mmp_camera *cam)
अणु
	काष्ठा mcam_camera *mcam = &cam->mcam;

	mccic_shutकरोwn(mcam);
	pm_runसमय_क्रमce_suspend(mcam->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक mmpcam_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmp_camera *cam = platक्रमm_get_drvdata(pdev);

	अगर (cam == शून्य)
		वापस -ENODEV;
	वापस mmpcam_हटाओ(cam);
पूर्ण

/*
 * Suspend/resume support.
 */

अटल पूर्णांक __maybe_unused mmpcam_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mmp_camera *cam = dev_get_drvdata(dev);
	काष्ठा mcam_camera *mcam = &cam->mcam;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NR_MCAM_CLK; i++) अणु
		अगर (!IS_ERR(mcam->clk[i]))
			clk_prepare_enable(mcam->clk[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mmpcam_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmp_camera *cam = dev_get_drvdata(dev);
	काष्ठा mcam_camera *mcam = &cam->mcam;
	पूर्णांक i;

	क्रम (i = NR_MCAM_CLK - 1; i >= 0; i--) अणु
		अगर (!IS_ERR(mcam->clk[i]))
			clk_disable_unprepare(mcam->clk[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mmpcam_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmp_camera *cam = dev_get_drvdata(dev);

	अगर (!pm_runसमय_suspended(dev))
		mccic_suspend(&cam->mcam);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mmpcam_resume(काष्ठा device *dev)
अणु
	काष्ठा mmp_camera *cam = dev_get_drvdata(dev);

	अगर (!pm_runसमय_suspended(dev))
		वापस mccic_resume(&cam->mcam);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mmpcam_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mmpcam_runसमय_suspend, mmpcam_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(mmpcam_suspend, mmpcam_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmpcam_of_match[] = अणु
	अणु .compatible = "marvell,mmp2-ccic", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mmpcam_of_match);

अटल काष्ठा platक्रमm_driver mmpcam_driver = अणु
	.probe		= mmpcam_probe,
	.हटाओ		= mmpcam_platक्रमm_हटाओ,
	.driver = अणु
		.name	= "mmp-camera",
		.of_match_table = of_match_ptr(mmpcam_of_match),
		.pm = &mmpcam_pm_ops,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(mmpcam_driver);
