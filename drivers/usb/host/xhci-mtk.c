<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MediaTek xHCI Host Controller Driver
 *
 * Copyright (c) 2015 MediaTek Inc.
 * Author:
 *  Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "xhci.h"
#समावेश "xhci-mtk.h"

/* ip_pw_ctrl0 रेजिस्टर */
#घोषणा CTRL0_IP_SW_RST	BIT(0)

/* ip_pw_ctrl1 रेजिस्टर */
#घोषणा CTRL1_IP_HOST_PDN	BIT(0)

/* ip_pw_ctrl2 रेजिस्टर */
#घोषणा CTRL2_IP_DEV_PDN	BIT(0)

/* ip_pw_sts1 रेजिस्टर */
#घोषणा STS1_IP_SLEEP_STS	BIT(30)
#घोषणा STS1_U3_MAC_RST	BIT(16)
#घोषणा STS1_XHCI_RST		BIT(11)
#घोषणा STS1_SYS125_RST	BIT(10)
#घोषणा STS1_REF_RST		BIT(8)
#घोषणा STS1_SYSPLL_STABLE	BIT(0)

/* ip_xhci_cap रेजिस्टर */
#घोषणा CAP_U3_PORT_NUM(p)	((p) & 0xff)
#घोषणा CAP_U2_PORT_NUM(p)	(((p) >> 8) & 0xff)

/* u3_ctrl_p रेजिस्टर */
#घोषणा CTRL_U3_PORT_HOST_SEL	BIT(2)
#घोषणा CTRL_U3_PORT_PDN	BIT(1)
#घोषणा CTRL_U3_PORT_DIS	BIT(0)

/* u2_ctrl_p रेजिस्टर */
#घोषणा CTRL_U2_PORT_HOST_SEL	BIT(2)
#घोषणा CTRL_U2_PORT_PDN	BIT(1)
#घोषणा CTRL_U2_PORT_DIS	BIT(0)

/* u2_phy_pll रेजिस्टर */
#घोषणा CTRL_U2_FORCE_PLL_STB	BIT(28)

/* usb remote wakeup रेजिस्टरs in syscon */

/* mt8173 etc */
#घोषणा PERI_WK_CTRL1	0x4
#घोषणा WC1_IS_C(x)	(((x) & 0xf) << 26)  /* cycle debounce */
#घोषणा WC1_IS_EN	BIT(25)
#घोषणा WC1_IS_P	BIT(6)  /* polarity क्रम ip sleep */

/* mt8183 */
#घोषणा PERI_WK_CTRL0	0x0
#घोषणा WC0_IS_C(x)	((u32)(((x) & 0xf) << 28))  /* cycle debounce */
#घोषणा WC0_IS_P	BIT(12)	/* polarity */
#घोषणा WC0_IS_EN	BIT(6)

/* mt8192 */
#घोषणा WC0_SSUSB0_CDEN		BIT(6)
#घोषणा WC0_IS_SPM_EN		BIT(1)

/* mt2712 etc */
#घोषणा PERI_SSUSB_SPM_CTRL	0x0
#घोषणा SSC_IP_SLEEP_EN	BIT(4)
#घोषणा SSC_SPM_INT_EN		BIT(1)

क्रमागत ssusb_uwk_vers अणु
	SSUSB_UWK_V1 = 1,
	SSUSB_UWK_V2,
	SSUSB_UWK_V1_1 = 101,	/* specअगरic revision 1.01 */
	SSUSB_UWK_V1_2,		/* specअगरic revision 1.2 */
पूर्ण;

अटल पूर्णांक xhci_mtk_host_enable(काष्ठा xhci_hcd_mtk *mtk)
अणु
	काष्ठा mu3c_ippc_regs __iomem *ippc = mtk->ippc_regs;
	u32 value, check_val;
	पूर्णांक u3_ports_disabled = 0;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!mtk->has_ippc)
		वापस 0;

	/* घातer on host ip */
	value = पढ़ोl(&ippc->ip_pw_ctr1);
	value &= ~CTRL1_IP_HOST_PDN;
	ग_लिखोl(value, &ippc->ip_pw_ctr1);

	/* घातer on and enable u3 ports except skipped ones */
	क्रम (i = 0; i < mtk->num_u3_ports; i++) अणु
		अगर ((0x1 << i) & mtk->u3p_dis_msk) अणु
			u3_ports_disabled++;
			जारी;
		पूर्ण

		value = पढ़ोl(&ippc->u3_ctrl_p[i]);
		value &= ~(CTRL_U3_PORT_PDN | CTRL_U3_PORT_DIS);
		value |= CTRL_U3_PORT_HOST_SEL;
		ग_लिखोl(value, &ippc->u3_ctrl_p[i]);
	पूर्ण

	/* घातer on and enable all u2 ports */
	क्रम (i = 0; i < mtk->num_u2_ports; i++) अणु
		value = पढ़ोl(&ippc->u2_ctrl_p[i]);
		value &= ~(CTRL_U2_PORT_PDN | CTRL_U2_PORT_DIS);
		value |= CTRL_U2_PORT_HOST_SEL;
		ग_लिखोl(value, &ippc->u2_ctrl_p[i]);
	पूर्ण

	/*
	 * रुको क्रम घड़ीs to be stable, and घड़ी करोमुख्यs reset to
	 * be inactive after घातer on and enable ports
	 */
	check_val = STS1_SYSPLL_STABLE | STS1_REF_RST |
			STS1_SYS125_RST | STS1_XHCI_RST;

	अगर (mtk->num_u3_ports > u3_ports_disabled)
		check_val |= STS1_U3_MAC_RST;

	ret = पढ़ोl_poll_समयout(&ippc->ip_pw_sts1, value,
			  (check_val == (value & check_val)), 100, 20000);
	अगर (ret) अणु
		dev_err(mtk->dev, "clocks are not stable (0x%x)\n", value);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_mtk_host_disable(काष्ठा xhci_hcd_mtk *mtk)
अणु
	काष्ठा mu3c_ippc_regs __iomem *ippc = mtk->ippc_regs;
	u32 value;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!mtk->has_ippc)
		वापस 0;

	/* घातer करोwn u3 ports except skipped ones */
	क्रम (i = 0; i < mtk->num_u3_ports; i++) अणु
		अगर ((0x1 << i) & mtk->u3p_dis_msk)
			जारी;

		value = पढ़ोl(&ippc->u3_ctrl_p[i]);
		value |= CTRL_U3_PORT_PDN;
		ग_लिखोl(value, &ippc->u3_ctrl_p[i]);
	पूर्ण

	/* घातer करोwn all u2 ports */
	क्रम (i = 0; i < mtk->num_u2_ports; i++) अणु
		value = पढ़ोl(&ippc->u2_ctrl_p[i]);
		value |= CTRL_U2_PORT_PDN;
		ग_लिखोl(value, &ippc->u2_ctrl_p[i]);
	पूर्ण

	/* घातer करोwn host ip */
	value = पढ़ोl(&ippc->ip_pw_ctr1);
	value |= CTRL1_IP_HOST_PDN;
	ग_लिखोl(value, &ippc->ip_pw_ctr1);

	/* रुको क्रम host ip to sleep */
	ret = पढ़ोl_poll_समयout(&ippc->ip_pw_sts1, value,
			  (value & STS1_IP_SLEEP_STS), 100, 100000);
	अगर (ret) अणु
		dev_err(mtk->dev, "ip sleep failed!!!\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xhci_mtk_ssusb_config(काष्ठा xhci_hcd_mtk *mtk)
अणु
	काष्ठा mu3c_ippc_regs __iomem *ippc = mtk->ippc_regs;
	u32 value;

	अगर (!mtk->has_ippc)
		वापस 0;

	/* reset whole ip */
	value = पढ़ोl(&ippc->ip_pw_ctr0);
	value |= CTRL0_IP_SW_RST;
	ग_लिखोl(value, &ippc->ip_pw_ctr0);
	udelay(1);
	value = पढ़ोl(&ippc->ip_pw_ctr0);
	value &= ~CTRL0_IP_SW_RST;
	ग_लिखोl(value, &ippc->ip_pw_ctr0);

	/*
	 * device ip is शेष घातer-on in fact
	 * घातer करोwn device ip, otherwise ip-sleep will fail
	 */
	value = पढ़ोl(&ippc->ip_pw_ctr2);
	value |= CTRL2_IP_DEV_PDN;
	ग_लिखोl(value, &ippc->ip_pw_ctr2);

	value = पढ़ोl(&ippc->ip_xhci_cap);
	mtk->num_u3_ports = CAP_U3_PORT_NUM(value);
	mtk->num_u2_ports = CAP_U2_PORT_NUM(value);
	dev_dbg(mtk->dev, "%s u2p:%d, u3p:%d\n", __func__,
			mtk->num_u2_ports, mtk->num_u3_ports);

	वापस xhci_mtk_host_enable(mtk);
पूर्ण

/* only घड़ीs can be turn off क्रम ip-sleep wakeup mode */
अटल व्योम usb_wakeup_ip_sleep_set(काष्ठा xhci_hcd_mtk *mtk, bool enable)
अणु
	u32 reg, msk, val;

	चयन (mtk->uwk_vers) अणु
	हाल SSUSB_UWK_V1:
		reg = mtk->uwk_reg_base + PERI_WK_CTRL1;
		msk = WC1_IS_EN | WC1_IS_C(0xf) | WC1_IS_P;
		val = enable ? (WC1_IS_EN | WC1_IS_C(0x8)) : 0;
		अवरोध;
	हाल SSUSB_UWK_V1_1:
		reg = mtk->uwk_reg_base + PERI_WK_CTRL0;
		msk = WC0_IS_EN | WC0_IS_C(0xf) | WC0_IS_P;
		val = enable ? (WC0_IS_EN | WC0_IS_C(0x8)) : 0;
		अवरोध;
	हाल SSUSB_UWK_V1_2:
		reg = mtk->uwk_reg_base + PERI_WK_CTRL0;
		msk = WC0_SSUSB0_CDEN | WC0_IS_SPM_EN;
		val = enable ? msk : 0;
		अवरोध;
	हाल SSUSB_UWK_V2:
		reg = mtk->uwk_reg_base + PERI_SSUSB_SPM_CTRL;
		msk = SSC_IP_SLEEP_EN | SSC_SPM_INT_EN;
		val = enable ? msk : 0;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	regmap_update_bits(mtk->uwk, reg, msk, val);
पूर्ण

अटल पूर्णांक usb_wakeup_of_property_parse(काष्ठा xhci_hcd_mtk *mtk,
				काष्ठा device_node *dn)
अणु
	काष्ठा of_phandle_args args;
	पूर्णांक ret;

	/* Wakeup function is optional */
	mtk->uwk_en = of_property_पढ़ो_bool(dn, "wakeup-source");
	अगर (!mtk->uwk_en)
		वापस 0;

	ret = of_parse_phandle_with_fixed_args(dn,
				"mediatek,syscon-wakeup", 2, 0, &args);
	अगर (ret)
		वापस ret;

	mtk->uwk_reg_base = args.args[0];
	mtk->uwk_vers = args.args[1];
	mtk->uwk = syscon_node_to_regmap(args.np);
	of_node_put(args.np);
	dev_info(mtk->dev, "uwk - reg:0x%x, version:%d\n",
			mtk->uwk_reg_base, mtk->uwk_vers);

	वापस PTR_ERR_OR_ZERO(mtk->uwk);
पूर्ण

अटल व्योम usb_wakeup_set(काष्ठा xhci_hcd_mtk *mtk, bool enable)
अणु
	अगर (mtk->uwk_en)
		usb_wakeup_ip_sleep_set(mtk, enable);
पूर्ण

अटल पूर्णांक xhci_mtk_clks_get(काष्ठा xhci_hcd_mtk *mtk)
अणु
	काष्ठा clk_bulk_data *clks = mtk->clks;

	clks[0].id = "sys_ck";
	clks[1].id = "xhci_ck";
	clks[2].id = "ref_ck";
	clks[3].id = "mcu_ck";
	clks[4].id = "dma_ck";

	वापस devm_clk_bulk_get_optional(mtk->dev, BULK_CLKS_NUM, clks);
पूर्ण

अटल पूर्णांक xhci_mtk_lकरोs_enable(काष्ठा xhci_hcd_mtk *mtk)
अणु
	पूर्णांक ret;

	ret = regulator_enable(mtk->vbus);
	अगर (ret) अणु
		dev_err(mtk->dev, "failed to enable vbus\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(mtk->vusb33);
	अगर (ret) अणु
		dev_err(mtk->dev, "failed to enable vusb33\n");
		regulator_disable(mtk->vbus);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम xhci_mtk_lकरोs_disable(काष्ठा xhci_hcd_mtk *mtk)
अणु
	regulator_disable(mtk->vbus);
	regulator_disable(mtk->vusb33);
पूर्ण

अटल व्योम xhci_mtk_quirks(काष्ठा device *dev, काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा usb_hcd *hcd = xhci_to_hcd(xhci);
	काष्ठा xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);

	/*
	 * As of now platक्रमm drivers करोn't provide MSI support so we ensure
	 * here that the generic code करोes not try to make a pci_dev from our
	 * dev काष्ठा in order to setup MSI
	 */
	xhci->quirks |= XHCI_PLAT;
	xhci->quirks |= XHCI_MTK_HOST;
	/*
	 * MTK host controller gives a spurious successful event after a
	 * लघु transfer. Ignore it.
	 */
	xhci->quirks |= XHCI_SPURIOUS_SUCCESS;
	अगर (mtk->lpm_support)
		xhci->quirks |= XHCI_LPM_SUPPORT;
	अगर (mtk->u2_lpm_disable)
		xhci->quirks |= XHCI_HW_LPM_DISABLE;

	/*
	 * MTK xHCI 0.96: PSA is 1 by शेष even अगर करोesn't support stream,
	 * and it's 3 when support it.
	 */
	अगर (xhci->hci_version < 0x100 && HCC_MAX_PSA(xhci->hcc_params) == 4)
		xhci->quirks |= XHCI_BROKEN_STREAMS;
पूर्ण

/* called during probe() after chip reset completes */
अटल पूर्णांक xhci_mtk_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);
	पूर्णांक ret;

	अगर (usb_hcd_is_primary_hcd(hcd)) अणु
		ret = xhci_mtk_ssusb_config(mtk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = xhci_gen_setup(hcd, xhci_mtk_quirks);
	अगर (ret)
		वापस ret;

	अगर (usb_hcd_is_primary_hcd(hcd)) अणु
		ret = xhci_mtk_sch_init(mtk);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा xhci_driver_overrides xhci_mtk_overrides __initस्थिर = अणु
	.reset = xhci_mtk_setup,
	.add_endpoपूर्णांक = xhci_mtk_add_ep,
	.drop_endpoपूर्णांक = xhci_mtk_drop_ep,
	.check_bandwidth = xhci_mtk_check_bandwidth,
	.reset_bandwidth = xhci_mtk_reset_bandwidth,
पूर्ण;

अटल काष्ठा hc_driver __पढ़ो_mostly xhci_mtk_hc_driver;

अटल पूर्णांक xhci_mtk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा xhci_hcd_mtk *mtk;
	स्थिर काष्ठा hc_driver *driver;
	काष्ठा xhci_hcd *xhci;
	काष्ठा resource *res;
	काष्ठा usb_hcd *hcd;
	पूर्णांक ret = -ENODEV;
	पूर्णांक wakeup_irq;
	पूर्णांक irq;

	अगर (usb_disabled())
		वापस -ENODEV;

	driver = &xhci_mtk_hc_driver;
	mtk = devm_kzalloc(dev, माप(*mtk), GFP_KERNEL);
	अगर (!mtk)
		वापस -ENOMEM;

	mtk->dev = dev;
	mtk->vbus = devm_regulator_get(dev, "vbus");
	अगर (IS_ERR(mtk->vbus)) अणु
		dev_err(dev, "fail to get vbus\n");
		वापस PTR_ERR(mtk->vbus);
	पूर्ण

	mtk->vusb33 = devm_regulator_get(dev, "vusb33");
	अगर (IS_ERR(mtk->vusb33)) अणु
		dev_err(dev, "fail to get vusb33\n");
		वापस PTR_ERR(mtk->vusb33);
	पूर्ण

	ret = xhci_mtk_clks_get(mtk);
	अगर (ret)
		वापस ret;

	irq = platक्रमm_get_irq_byname_optional(pdev, "host");
	अगर (irq < 0) अणु
		अगर (irq == -EPROBE_DEFER)
			वापस irq;

		/* क्रम backward compatibility */
		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq < 0)
			वापस irq;
	पूर्ण

	wakeup_irq = platक्रमm_get_irq_byname_optional(pdev, "wakeup");
	अगर (wakeup_irq == -EPROBE_DEFER)
		वापस wakeup_irq;

	mtk->lpm_support = of_property_पढ़ो_bool(node, "usb3-lpm-capable");
	mtk->u2_lpm_disable = of_property_पढ़ो_bool(node, "usb2-lpm-disable");
	/* optional property, ignore the error अगर it करोes not exist */
	of_property_पढ़ो_u32(node, "mediatek,u3p-dis-msk",
			     &mtk->u3p_dis_msk);

	ret = usb_wakeup_of_property_parse(mtk, node);
	अगर (ret) अणु
		dev_err(dev, "failed to parse uwk property\n");
		वापस ret;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 4000);
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	ret = xhci_mtk_lकरोs_enable(mtk);
	अगर (ret)
		जाओ disable_pm;

	ret = clk_bulk_prepare_enable(BULK_CLKS_NUM, mtk->clks);
	अगर (ret)
		जाओ disable_lकरोs;

	hcd = usb_create_hcd(driver, dev, dev_name(dev));
	अगर (!hcd) अणु
		ret = -ENOMEM;
		जाओ disable_clk;
	पूर्ण

	/*
	 * USB 2.0 roothub is stored in the platक्रमm_device.
	 * Swap it with mtk HCD.
	 */
	mtk->hcd = platक्रमm_get_drvdata(pdev);
	platक्रमm_set_drvdata(pdev, mtk);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mac");
	hcd->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		ret = PTR_ERR(hcd->regs);
		जाओ put_usb2_hcd;
	पूर्ण
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ippc");
	अगर (res) अणु	/* ippc रेजिस्टर is optional */
		mtk->ippc_regs = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(mtk->ippc_regs)) अणु
			ret = PTR_ERR(mtk->ippc_regs);
			जाओ put_usb2_hcd;
		पूर्ण
		mtk->has_ippc = true;
	पूर्ण अन्यथा अणु
		mtk->has_ippc = false;
	पूर्ण

	device_init_wakeup(dev, true);

	xhci = hcd_to_xhci(hcd);
	xhci->मुख्य_hcd = hcd;

	/*
	 * imod_पूर्णांकerval is the पूर्णांकerrupt moderation value in nanoseconds.
	 * The increment पूर्णांकerval is 8 बार as much as that defined in
	 * the xHCI spec on MTK's controller.
	 */
	xhci->imod_पूर्णांकerval = 5000;
	device_property_पढ़ो_u32(dev, "imod-interval-ns", &xhci->imod_पूर्णांकerval);

	xhci->shared_hcd = usb_create_shared_hcd(driver, dev,
			dev_name(dev), hcd);
	अगर (!xhci->shared_hcd) अणु
		ret = -ENOMEM;
		जाओ disable_device_wakeup;
	पूर्ण

	ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (ret)
		जाओ put_usb3_hcd;

	अगर (HCC_MAX_PSA(xhci->hcc_params) >= 4 &&
	    !(xhci->quirks & XHCI_BROKEN_STREAMS))
		xhci->shared_hcd->can_करो_streams = 1;

	ret = usb_add_hcd(xhci->shared_hcd, irq, IRQF_SHARED);
	अगर (ret)
		जाओ dealloc_usb2_hcd;

	अगर (wakeup_irq > 0) अणु
		ret = dev_pm_set_dedicated_wake_irq(dev, wakeup_irq);
		अगर (ret) अणु
			dev_err(dev, "set wakeup irq %d failed\n", wakeup_irq);
			जाओ dealloc_usb3_hcd;
		पूर्ण
		dev_info(dev, "wakeup irq %d\n", wakeup_irq);
	पूर्ण

	device_enable_async_suspend(dev);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
	pm_runसमय_क्रमbid(dev);

	वापस 0;

dealloc_usb3_hcd:
	usb_हटाओ_hcd(xhci->shared_hcd);
	xhci->shared_hcd = शून्य;

dealloc_usb2_hcd:
	usb_हटाओ_hcd(hcd);

put_usb3_hcd:
	xhci_mtk_sch_निकास(mtk);
	usb_put_hcd(xhci->shared_hcd);

disable_device_wakeup:
	device_init_wakeup(dev, false);

put_usb2_hcd:
	usb_put_hcd(hcd);

disable_clk:
	clk_bulk_disable_unprepare(BULK_CLKS_NUM, mtk->clks);

disable_lकरोs:
	xhci_mtk_lकरोs_disable(mtk);

disable_pm:
	pm_runसमय_put_sync_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक xhci_mtk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xhci_hcd_mtk *mtk = platक्रमm_get_drvdata(pdev);
	काष्ठा usb_hcd	*hcd = mtk->hcd;
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	काष्ठा usb_hcd  *shared_hcd = xhci->shared_hcd;
	काष्ठा device *dev = &pdev->dev;

	pm_runसमय_get_sync(dev);
	xhci->xhc_state |= XHCI_STATE_REMOVING;
	dev_pm_clear_wake_irq(dev);
	device_init_wakeup(dev, false);

	usb_हटाओ_hcd(shared_hcd);
	xhci->shared_hcd = शून्य;
	usb_हटाओ_hcd(hcd);
	usb_put_hcd(shared_hcd);
	usb_put_hcd(hcd);
	xhci_mtk_sch_निकास(mtk);
	clk_bulk_disable_unprepare(BULK_CLKS_NUM, mtk->clks);
	xhci_mtk_lकरोs_disable(mtk);

	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_set_suspended(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xhci_mtk_suspend(काष्ठा device *dev)
अणु
	काष्ठा xhci_hcd_mtk *mtk = dev_get_drvdata(dev);
	काष्ठा usb_hcd *hcd = mtk->hcd;
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	पूर्णांक ret;

	xhci_dbg(xhci, "%s: stop port polling\n", __func__);
	clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	del_समयr_sync(&hcd->rh_समयr);
	clear_bit(HCD_FLAG_POLL_RH, &xhci->shared_hcd->flags);
	del_समयr_sync(&xhci->shared_hcd->rh_समयr);

	ret = xhci_mtk_host_disable(mtk);
	अगर (ret)
		जाओ restart_poll_rh;

	clk_bulk_disable_unprepare(BULK_CLKS_NUM, mtk->clks);
	usb_wakeup_set(mtk, true);
	वापस 0;

restart_poll_rh:
	xhci_dbg(xhci, "%s: restart port polling\n", __func__);
	set_bit(HCD_FLAG_POLL_RH, &xhci->shared_hcd->flags);
	usb_hcd_poll_rh_status(xhci->shared_hcd);
	set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	usb_hcd_poll_rh_status(hcd);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused xhci_mtk_resume(काष्ठा device *dev)
अणु
	काष्ठा xhci_hcd_mtk *mtk = dev_get_drvdata(dev);
	काष्ठा usb_hcd *hcd = mtk->hcd;
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	पूर्णांक ret;

	usb_wakeup_set(mtk, false);
	ret = clk_bulk_prepare_enable(BULK_CLKS_NUM, mtk->clks);
	अगर (ret)
		जाओ enable_wakeup;

	ret = xhci_mtk_host_enable(mtk);
	अगर (ret)
		जाओ disable_clks;

	xhci_dbg(xhci, "%s: restart port polling\n", __func__);
	set_bit(HCD_FLAG_POLL_RH, &xhci->shared_hcd->flags);
	usb_hcd_poll_rh_status(xhci->shared_hcd);
	set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	usb_hcd_poll_rh_status(hcd);
	वापस 0;

disable_clks:
	clk_bulk_disable_unprepare(BULK_CLKS_NUM, mtk->clks);
enable_wakeup:
	usb_wakeup_set(mtk, true);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused xhci_mtk_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा xhci_hcd_mtk  *mtk = dev_get_drvdata(dev);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(mtk->hcd);
	पूर्णांक ret = 0;

	अगर (xhci->xhc_state)
		वापस -ESHUTDOWN;

	अगर (device_may_wakeup(dev))
		ret = xhci_mtk_suspend(dev);

	/* -EBUSY: let PM स्वतःmatically reschedule another स्वतःsuspend */
	वापस ret ? -EBUSY : 0;
पूर्ण

अटल पूर्णांक __maybe_unused xhci_mtk_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा xhci_hcd_mtk  *mtk = dev_get_drvdata(dev);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(mtk->hcd);
	पूर्णांक ret = 0;

	अगर (xhci->xhc_state)
		वापस -ESHUTDOWN;

	अगर (device_may_wakeup(dev))
		ret = xhci_mtk_resume(dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops xhci_mtk_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(xhci_mtk_suspend, xhci_mtk_resume)
	SET_RUNTIME_PM_OPS(xhci_mtk_runसमय_suspend,
			   xhci_mtk_runसमय_resume, शून्य)
पूर्ण;

#घोषणा DEV_PM_OPS (IS_ENABLED(CONFIG_PM) ? &xhci_mtk_pm_ops : शून्य)

अटल स्थिर काष्ठा of_device_id mtk_xhci_of_match[] = अणु
	अणु .compatible = "mediatek,mt8173-xhci"पूर्ण,
	अणु .compatible = "mediatek,mtk-xhci"पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_xhci_of_match);

अटल काष्ठा platक्रमm_driver mtk_xhci_driver = अणु
	.probe	= xhci_mtk_probe,
	.हटाओ	= xhci_mtk_हटाओ,
	.driver	= अणु
		.name = "xhci-mtk",
		.pm = DEV_PM_OPS,
		.of_match_table = mtk_xhci_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init xhci_mtk_init(व्योम)
अणु
	xhci_init_driver(&xhci_mtk_hc_driver, &xhci_mtk_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&mtk_xhci_driver);
पूर्ण
module_init(xhci_mtk_init);

अटल व्योम __निकास xhci_mtk_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mtk_xhci_driver);
पूर्ण
module_निकास(xhci_mtk_निकास);

MODULE_AUTHOR("Chunfeng Yun <chunfeng.yun@mediatek.com>");
MODULE_DESCRIPTION("MediaTek xHCI Host Controller Driver");
MODULE_LICENSE("GPL v2");
