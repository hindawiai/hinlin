<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mtu3.h"
#समावेश "mtu3_dr.h"
#समावेश "mtu3_debug.h"

/* u2-port0 should be घातered on and enabled; */
पूर्णांक ssusb_check_घड़ीs(काष्ठा ssusb_mtk *ssusb, u32 ex_clks)
अणु
	व्योम __iomem *ibase = ssusb->ippc_base;
	u32 value, check_val;
	पूर्णांक ret;

	check_val = ex_clks | SSUSB_SYS125_RST_B_STS | SSUSB_SYSPLL_STABLE |
			SSUSB_REF_RST_B_STS;

	ret = पढ़ोl_poll_समयout(ibase + U3D_SSUSB_IP_PW_STS1, value,
			(check_val == (value & check_val)), 100, 20000);
	अगर (ret) अणु
		dev_err(ssusb->dev, "clks of sts1 are not stable!\n");
		वापस ret;
	पूर्ण

	ret = पढ़ोl_poll_समयout(ibase + U3D_SSUSB_IP_PW_STS2, value,
			(value & SSUSB_U2_MAC_SYS_RST_B_STS), 100, 10000);
	अगर (ret) अणु
		dev_err(ssusb->dev, "mac2 clock is not stable\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssusb_phy_init(काष्ठा ssusb_mtk *ssusb)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ssusb->num_phys; i++) अणु
		ret = phy_init(ssusb->phys[i]);
		अगर (ret)
			जाओ निकास_phy;
	पूर्ण
	वापस 0;

निकास_phy:
	क्रम (; i > 0; i--)
		phy_निकास(ssusb->phys[i - 1]);

	वापस ret;
पूर्ण

अटल पूर्णांक ssusb_phy_निकास(काष्ठा ssusb_mtk *ssusb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ssusb->num_phys; i++)
		phy_निकास(ssusb->phys[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक ssusb_phy_घातer_on(काष्ठा ssusb_mtk *ssusb)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ssusb->num_phys; i++) अणु
		ret = phy_घातer_on(ssusb->phys[i]);
		अगर (ret)
			जाओ घातer_off_phy;
	पूर्ण
	वापस 0;

घातer_off_phy:
	क्रम (; i > 0; i--)
		phy_घातer_off(ssusb->phys[i - 1]);

	वापस ret;
पूर्ण

अटल व्योम ssusb_phy_घातer_off(काष्ठा ssusb_mtk *ssusb)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ssusb->num_phys; i++)
		phy_घातer_off(ssusb->phys[i]);
पूर्ण

अटल पूर्णांक ssusb_clks_enable(काष्ठा ssusb_mtk *ssusb)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(ssusb->sys_clk);
	अगर (ret) अणु
		dev_err(ssusb->dev, "failed to enable sys_clk\n");
		जाओ sys_clk_err;
	पूर्ण

	ret = clk_prepare_enable(ssusb->ref_clk);
	अगर (ret) अणु
		dev_err(ssusb->dev, "failed to enable ref_clk\n");
		जाओ ref_clk_err;
	पूर्ण

	ret = clk_prepare_enable(ssusb->mcu_clk);
	अगर (ret) अणु
		dev_err(ssusb->dev, "failed to enable mcu_clk\n");
		जाओ mcu_clk_err;
	पूर्ण

	ret = clk_prepare_enable(ssusb->dma_clk);
	अगर (ret) अणु
		dev_err(ssusb->dev, "failed to enable dma_clk\n");
		जाओ dma_clk_err;
	पूर्ण

	वापस 0;

dma_clk_err:
	clk_disable_unprepare(ssusb->mcu_clk);
mcu_clk_err:
	clk_disable_unprepare(ssusb->ref_clk);
ref_clk_err:
	clk_disable_unprepare(ssusb->sys_clk);
sys_clk_err:
	वापस ret;
पूर्ण

अटल व्योम ssusb_clks_disable(काष्ठा ssusb_mtk *ssusb)
अणु
	clk_disable_unprepare(ssusb->dma_clk);
	clk_disable_unprepare(ssusb->mcu_clk);
	clk_disable_unprepare(ssusb->ref_clk);
	clk_disable_unprepare(ssusb->sys_clk);
पूर्ण

अटल पूर्णांक ssusb_rscs_init(काष्ठा ssusb_mtk *ssusb)
अणु
	पूर्णांक ret = 0;

	ret = regulator_enable(ssusb->vusb33);
	अगर (ret) अणु
		dev_err(ssusb->dev, "failed to enable vusb33\n");
		जाओ vusb33_err;
	पूर्ण

	ret = ssusb_clks_enable(ssusb);
	अगर (ret)
		जाओ clks_err;

	ret = ssusb_phy_init(ssusb);
	अगर (ret) अणु
		dev_err(ssusb->dev, "failed to init phy\n");
		जाओ phy_init_err;
	पूर्ण

	ret = ssusb_phy_घातer_on(ssusb);
	अगर (ret) अणु
		dev_err(ssusb->dev, "failed to power on phy\n");
		जाओ phy_err;
	पूर्ण

	वापस 0;

phy_err:
	ssusb_phy_निकास(ssusb);
phy_init_err:
	ssusb_clks_disable(ssusb);
clks_err:
	regulator_disable(ssusb->vusb33);
vusb33_err:
	वापस ret;
पूर्ण

अटल व्योम ssusb_rscs_निकास(काष्ठा ssusb_mtk *ssusb)
अणु
	ssusb_clks_disable(ssusb);
	regulator_disable(ssusb->vusb33);
	ssusb_phy_घातer_off(ssusb);
	ssusb_phy_निकास(ssusb);
पूर्ण

अटल व्योम ssusb_ip_sw_reset(काष्ठा ssusb_mtk *ssusb)
अणु
	/* reset whole ip (xhci & u3d) */
	mtu3_setbits(ssusb->ippc_base, U3D_SSUSB_IP_PW_CTRL0, SSUSB_IP_SW_RST);
	udelay(1);
	mtu3_clrbits(ssusb->ippc_base, U3D_SSUSB_IP_PW_CTRL0, SSUSB_IP_SW_RST);

	/*
	 * device ip may be घातered on in firmware/BROM stage beक्रमe entering
	 * kernel stage;
	 * घातer करोwn device ip, otherwise ip-sleep will fail when working as
	 * host only mode
	 */
	mtu3_setbits(ssusb->ippc_base, U3D_SSUSB_IP_PW_CTRL2, SSUSB_IP_DEV_PDN);
पूर्ण

अटल पूर्णांक get_ssusb_rscs(काष्ठा platक्रमm_device *pdev, काष्ठा ssusb_mtk *ssusb)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा otg_चयन_mtk *otg_sx = &ssusb->otg_चयन;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i;
	पूर्णांक ret;

	ssusb->vusb33 = devm_regulator_get(dev, "vusb33");
	अगर (IS_ERR(ssusb->vusb33)) अणु
		dev_err(dev, "failed to get vusb33\n");
		वापस PTR_ERR(ssusb->vusb33);
	पूर्ण

	ssusb->sys_clk = devm_clk_get(dev, "sys_ck");
	अगर (IS_ERR(ssusb->sys_clk)) अणु
		dev_err(dev, "failed to get sys clock\n");
		वापस PTR_ERR(ssusb->sys_clk);
	पूर्ण

	ssusb->ref_clk = devm_clk_get_optional(dev, "ref_ck");
	अगर (IS_ERR(ssusb->ref_clk))
		वापस PTR_ERR(ssusb->ref_clk);

	ssusb->mcu_clk = devm_clk_get_optional(dev, "mcu_ck");
	अगर (IS_ERR(ssusb->mcu_clk))
		वापस PTR_ERR(ssusb->mcu_clk);

	ssusb->dma_clk = devm_clk_get_optional(dev, "dma_ck");
	अगर (IS_ERR(ssusb->dma_clk))
		वापस PTR_ERR(ssusb->dma_clk);

	ssusb->num_phys = of_count_phandle_with_args(node,
			"phys", "#phy-cells");
	अगर (ssusb->num_phys > 0) अणु
		ssusb->phys = devm_kसुस्मृति(dev, ssusb->num_phys,
					माप(*ssusb->phys), GFP_KERNEL);
		अगर (!ssusb->phys)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		ssusb->num_phys = 0;
	पूर्ण

	क्रम (i = 0; i < ssusb->num_phys; i++) अणु
		ssusb->phys[i] = devm_of_phy_get_by_index(dev, node, i);
		अगर (IS_ERR(ssusb->phys[i])) अणु
			dev_err(dev, "failed to get phy-%d\n", i);
			वापस PTR_ERR(ssusb->phys[i]);
		पूर्ण
	पूर्ण

	ssusb->ippc_base = devm_platक्रमm_ioremap_resource_byname(pdev, "ippc");
	अगर (IS_ERR(ssusb->ippc_base))
		वापस PTR_ERR(ssusb->ippc_base);

	ssusb->dr_mode = usb_get_dr_mode(dev);
	अगर (ssusb->dr_mode == USB_DR_MODE_UNKNOWN)
		ssusb->dr_mode = USB_DR_MODE_OTG;

	अगर (ssusb->dr_mode == USB_DR_MODE_PERIPHERAL)
		जाओ out;

	/* अगर host role is supported */
	ret = ssusb_wakeup_of_property_parse(ssusb, node);
	अगर (ret) अणु
		dev_err(dev, "failed to parse uwk property\n");
		वापस ret;
	पूर्ण

	/* optional property, ignore the error अगर it करोes not exist */
	of_property_पढ़ो_u32(node, "mediatek,u3p-dis-msk",
			     &ssusb->u3p_dis_msk);

	otg_sx->vbus = devm_regulator_get(dev, "vbus");
	अगर (IS_ERR(otg_sx->vbus)) अणु
		dev_err(dev, "failed to get vbus\n");
		वापस PTR_ERR(otg_sx->vbus);
	पूर्ण

	अगर (ssusb->dr_mode == USB_DR_MODE_HOST)
		जाओ out;

	/* अगर dual-role mode is supported */
	otg_sx->is_u3_drd = of_property_पढ़ो_bool(node, "mediatek,usb3-drd");
	otg_sx->manual_drd_enabled =
		of_property_पढ़ो_bool(node, "enable-manual-drd");
	otg_sx->role_sw_used = of_property_पढ़ो_bool(node, "usb-role-switch");

	अगर (!otg_sx->role_sw_used && of_property_पढ़ो_bool(node, "extcon")) अणु
		otg_sx->edev = extcon_get_edev_by_phandle(ssusb->dev, 0);
		अगर (IS_ERR(otg_sx->edev)) अणु
			dev_err(ssusb->dev, "couldn't get extcon device\n");
			वापस PTR_ERR(otg_sx->edev);
		पूर्ण
	पूर्ण

out:
	dev_info(dev, "dr_mode: %d, is_u3_dr: %d, u3p_dis_msk: %x, drd: %s\n",
		ssusb->dr_mode, otg_sx->is_u3_drd, ssusb->u3p_dis_msk,
		otg_sx->manual_drd_enabled ? "manual" : "auto");

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ssusb_mtk *ssusb;
	पूर्णांक ret = -ENOMEM;

	/* all elements are set to ZERO as शेष value */
	ssusb = devm_kzalloc(dev, माप(*ssusb), GFP_KERNEL);
	अगर (!ssusb)
		वापस -ENOMEM;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(dev, "No suitable DMA config available\n");
		वापस -ENOTSUPP;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ssusb);
	ssusb->dev = dev;

	ret = get_ssusb_rscs(pdev, ssusb);
	अगर (ret)
		वापस ret;

	ssusb_debugfs_create_root(ssusb);

	/* enable घातer करोमुख्य */
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);
	device_enable_async_suspend(dev);

	ret = ssusb_rscs_init(ssusb);
	अगर (ret)
		जाओ comm_init_err;

	ssusb_ip_sw_reset(ssusb);

	अगर (IS_ENABLED(CONFIG_USB_MTU3_HOST))
		ssusb->dr_mode = USB_DR_MODE_HOST;
	अन्यथा अगर (IS_ENABLED(CONFIG_USB_MTU3_GADGET))
		ssusb->dr_mode = USB_DR_MODE_PERIPHERAL;

	/* शेष as host */
	ssusb->is_host = !(ssusb->dr_mode == USB_DR_MODE_PERIPHERAL);

	चयन (ssusb->dr_mode) अणु
	हाल USB_DR_MODE_PERIPHERAL:
		ret = ssusb_gadget_init(ssusb);
		अगर (ret) अणु
			dev_err(dev, "failed to initialize gadget\n");
			जाओ comm_निकास;
		पूर्ण
		अवरोध;
	हाल USB_DR_MODE_HOST:
		ret = ssusb_host_init(ssusb, node);
		अगर (ret) अणु
			dev_err(dev, "failed to initialize host\n");
			जाओ comm_निकास;
		पूर्ण
		अवरोध;
	हाल USB_DR_MODE_OTG:
		ret = ssusb_gadget_init(ssusb);
		अगर (ret) अणु
			dev_err(dev, "failed to initialize gadget\n");
			जाओ comm_निकास;
		पूर्ण

		ret = ssusb_host_init(ssusb, node);
		अगर (ret) अणु
			dev_err(dev, "failed to initialize host\n");
			जाओ gadget_निकास;
		पूर्ण

		ret = ssusb_otg_चयन_init(ssusb);
		अगर (ret) अणु
			dev_err(dev, "failed to initialize switch\n");
			जाओ host_निकास;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(dev, "unsupported mode: %d\n", ssusb->dr_mode);
		ret = -EINVAL;
		जाओ comm_निकास;
	पूर्ण

	वापस 0;

host_निकास:
	ssusb_host_निकास(ssusb);
gadget_निकास:
	ssusb_gadget_निकास(ssusb);
comm_निकास:
	ssusb_rscs_निकास(ssusb);
comm_init_err:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	ssusb_debugfs_हटाओ_root(ssusb);

	वापस ret;
पूर्ण

अटल पूर्णांक mtu3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ssusb_mtk *ssusb = platक्रमm_get_drvdata(pdev);

	चयन (ssusb->dr_mode) अणु
	हाल USB_DR_MODE_PERIPHERAL:
		ssusb_gadget_निकास(ssusb);
		अवरोध;
	हाल USB_DR_MODE_HOST:
		ssusb_host_निकास(ssusb);
		अवरोध;
	हाल USB_DR_MODE_OTG:
		ssusb_otg_चयन_निकास(ssusb);
		ssusb_gadget_निकास(ssusb);
		ssusb_host_निकास(ssusb);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ssusb_rscs_निकास(ssusb);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	ssusb_debugfs_हटाओ_root(ssusb);

	वापस 0;
पूर्ण

/*
 * when support dual-role mode, we reject suspend when
 * it works as device mode;
 */
अटल पूर्णांक __maybe_unused mtu3_suspend(काष्ठा device *dev)
अणु
	काष्ठा ssusb_mtk *ssusb = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	/* REVISIT: disconnect it क्रम only device mode? */
	अगर (!ssusb->is_host)
		वापस 0;

	ssusb_host_disable(ssusb, true);
	ssusb_phy_घातer_off(ssusb);
	ssusb_clks_disable(ssusb);
	ssusb_wakeup_set(ssusb, true);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtu3_resume(काष्ठा device *dev)
अणु
	काष्ठा ssusb_mtk *ssusb = dev_get_drvdata(dev);
	पूर्णांक ret;

	dev_dbg(dev, "%s\n", __func__);

	अगर (!ssusb->is_host)
		वापस 0;

	ssusb_wakeup_set(ssusb, false);
	ret = ssusb_clks_enable(ssusb);
	अगर (ret)
		जाओ clks_err;

	ret = ssusb_phy_घातer_on(ssusb);
	अगर (ret)
		जाओ phy_err;

	ssusb_host_enable(ssusb);

	वापस 0;

phy_err:
	ssusb_clks_disable(ssusb);
clks_err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtu3_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mtu3_suspend, mtu3_resume)
पूर्ण;

#घोषणा DEV_PM_OPS (IS_ENABLED(CONFIG_PM) ? &mtu3_pm_ops : शून्य)

अटल स्थिर काष्ठा of_device_id mtu3_of_match[] = अणु
	अणु.compatible = "mediatek,mt8173-mtu3",पूर्ण,
	अणु.compatible = "mediatek,mtu3",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtu3_of_match);

अटल काष्ठा platक्रमm_driver mtu3_driver = अणु
	.probe = mtu3_probe,
	.हटाओ = mtu3_हटाओ,
	.driver = अणु
		.name = MTU3_DRIVER_NAME,
		.pm = DEV_PM_OPS,
		.of_match_table = mtu3_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mtu3_driver);

MODULE_AUTHOR("Chunfeng Yun <chunfeng.yun@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek USB3 DRD Controller Driver");
