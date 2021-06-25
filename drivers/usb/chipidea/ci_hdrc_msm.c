<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2010, Code Aurora Forum. All rights reserved. */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/usb/chipidea.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/पन.स>
#समावेश <linux/reset-controller.h>
#समावेश <linux/extcon.h>
#समावेश <linux/of.h>

#समावेश "ci.h"

#घोषणा HS_PHY_AHB_MODE			0x0098

#घोषणा HS_PHY_GENCONFIG		0x009c
#घोषणा HS_PHY_TXFIFO_IDLE_FORCE_DIS	BIT(4)

#घोषणा HS_PHY_GENCONFIG_2		0x00a0
#घोषणा HS_PHY_SESS_VLD_CTRL_EN		BIT(7)
#घोषणा HS_PHY_ULPI_TX_PKT_EN_CLR_FIX	BIT(19)

#घोषणा HSPHY_SESS_VLD_CTRL		BIT(25)

/* Venकरोr base starts at 0x200 beyond CI base */
#घोषणा HS_PHY_CTRL			0x0040
#घोषणा HS_PHY_SEC_CTRL			0x0078
#घोषणा HS_PHY_DIG_CLAMP_N		BIT(16)
#घोषणा HS_PHY_POR_ASSERT		BIT(0)

काष्ठा ci_hdrc_msm अणु
	काष्ठा platक्रमm_device *ci;
	काष्ठा clk *core_clk;
	काष्ठा clk *अगरace_clk;
	काष्ठा clk *fs_clk;
	काष्ठा ci_hdrc_platक्रमm_data pdata;
	काष्ठा reset_controller_dev rcdev;
	bool secondary_phy;
	bool hsic;
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक
ci_hdrc_msm_por_reset(काष्ठा reset_controller_dev *r, अचिन्हित दीर्घ id)
अणु
	काष्ठा ci_hdrc_msm *ci_msm = container_of(r, काष्ठा ci_hdrc_msm, rcdev);
	व्योम __iomem *addr = ci_msm->base;
	u32 val;

	अगर (id)
		addr += HS_PHY_SEC_CTRL;
	अन्यथा
		addr += HS_PHY_CTRL;

	val = पढ़ोl_relaxed(addr);
	val |= HS_PHY_POR_ASSERT;
	ग_लिखोl(val, addr);
	/*
	 * रुको क्रम minimum 10 microseconds as suggested by manual.
	 * Use a slightly larger value since the exact value didn't
	 * work 100% of the समय.
	 */
	udelay(12);
	val &= ~HS_PHY_POR_ASSERT;
	ग_लिखोl(val, addr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops ci_hdrc_msm_reset_ops = अणु
	.reset = ci_hdrc_msm_por_reset,
पूर्ण;

अटल पूर्णांक ci_hdrc_msm_notअगरy_event(काष्ठा ci_hdrc *ci, अचिन्हित event)
अणु
	काष्ठा device *dev = ci->dev->parent;
	काष्ठा ci_hdrc_msm *msm_ci = dev_get_drvdata(dev);
	पूर्णांक ret;

	चयन (event) अणु
	हाल CI_HDRC_CONTROLLER_RESET_EVENT:
		dev_dbg(dev, "CI_HDRC_CONTROLLER_RESET_EVENT received\n");

		hw_phymode_configure(ci);
		अगर (msm_ci->secondary_phy) अणु
			u32 val = पढ़ोl_relaxed(msm_ci->base + HS_PHY_SEC_CTRL);
			val |= HS_PHY_DIG_CLAMP_N;
			ग_लिखोl_relaxed(val, msm_ci->base + HS_PHY_SEC_CTRL);
		पूर्ण

		ret = phy_init(ci->phy);
		अगर (ret)
			वापस ret;

		ret = phy_घातer_on(ci->phy);
		अगर (ret) अणु
			phy_निकास(ci->phy);
			वापस ret;
		पूर्ण

		/* use AHB transactor, allow posted data ग_लिखोs */
		hw_ग_लिखो_id_reg(ci, HS_PHY_AHB_MODE, 0xffffffff, 0x8);

		/* workaround क्रम rx buffer collision issue */
		hw_ग_लिखो_id_reg(ci, HS_PHY_GENCONFIG,
				HS_PHY_TXFIFO_IDLE_FORCE_DIS, 0);

		अगर (!msm_ci->hsic)
			hw_ग_लिखो_id_reg(ci, HS_PHY_GENCONFIG_2,
					HS_PHY_ULPI_TX_PKT_EN_CLR_FIX, 0);

		अगर (!IS_ERR(ci->platdata->vbus_extcon.edev) || ci->role_चयन) अणु
			hw_ग_लिखो_id_reg(ci, HS_PHY_GENCONFIG_2,
					HS_PHY_SESS_VLD_CTRL_EN,
					HS_PHY_SESS_VLD_CTRL_EN);
			hw_ग_लिखो(ci, OP_USBCMD, HSPHY_SESS_VLD_CTRL,
				 HSPHY_SESS_VLD_CTRL);

		पूर्ण
		अवरोध;
	हाल CI_HDRC_CONTROLLER_STOPPED_EVENT:
		dev_dbg(dev, "CI_HDRC_CONTROLLER_STOPPED_EVENT received\n");
		phy_घातer_off(ci->phy);
		phy_निकास(ci->phy);
		अवरोध;
	शेष:
		dev_dbg(dev, "unknown ci_hdrc event\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ci_hdrc_msm_mux_phy(काष्ठा ci_hdrc_msm *ci,
			       काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा of_phandle_args args;
	u32 val;
	पूर्णांक ret;

	ret = of_parse_phandle_with_fixed_args(dev->of_node, "phy-select", 2, 0,
					       &args);
	अगर (ret)
		वापस 0;

	regmap = syscon_node_to_regmap(args.np);
	of_node_put(args.np);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ret = regmap_ग_लिखो(regmap, args.args[0], args.args[1]);
	अगर (ret)
		वापस ret;

	ci->secondary_phy = !!args.args[1];
	अगर (ci->secondary_phy) अणु
		val = पढ़ोl_relaxed(ci->base + HS_PHY_SEC_CTRL);
		val |= HS_PHY_DIG_CLAMP_N;
		ग_लिखोl_relaxed(val, ci->base + HS_PHY_SEC_CTRL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ci_hdrc_msm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ci_hdrc_msm *ci;
	काष्ठा platक्रमm_device *plat_ci;
	काष्ठा clk *clk;
	काष्ठा reset_control *reset;
	पूर्णांक ret;
	काष्ठा device_node *ulpi_node, *phy_node;

	dev_dbg(&pdev->dev, "ci_hdrc_msm_probe\n");

	ci = devm_kzalloc(&pdev->dev, माप(*ci), GFP_KERNEL);
	अगर (!ci)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, ci);

	ci->pdata.name = "ci_hdrc_msm";
	ci->pdata.capoffset = DEF_CAPOFFSET;
	ci->pdata.flags	= CI_HDRC_REGS_SHARED | CI_HDRC_DISABLE_STREAMING |
			  CI_HDRC_OVERRIDE_AHB_BURST |
			  CI_HDRC_OVERRIDE_PHY_CONTROL;
	ci->pdata.notअगरy_event = ci_hdrc_msm_notअगरy_event;

	reset = devm_reset_control_get(&pdev->dev, "core");
	अगर (IS_ERR(reset))
		वापस PTR_ERR(reset);

	ci->core_clk = clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ci->अगरace_clk = clk = devm_clk_get(&pdev->dev, "iface");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ci->fs_clk = clk = devm_clk_get_optional(&pdev->dev, "fs");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ci->base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(ci->base))
		वापस PTR_ERR(ci->base);

	ci->rcdev.owner = THIS_MODULE;
	ci->rcdev.ops = &ci_hdrc_msm_reset_ops;
	ci->rcdev.of_node = pdev->dev.of_node;
	ci->rcdev.nr_resets = 2;
	ret = devm_reset_controller_रेजिस्टर(&pdev->dev, &ci->rcdev);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(ci->fs_clk);
	अगर (ret)
		वापस ret;

	reset_control_निश्चित(reset);
	usleep_range(10000, 12000);
	reset_control_deनिश्चित(reset);

	clk_disable_unprepare(ci->fs_clk);

	ret = clk_prepare_enable(ci->core_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(ci->अगरace_clk);
	अगर (ret)
		जाओ err_अगरace;

	ret = ci_hdrc_msm_mux_phy(ci, pdev);
	अगर (ret)
		जाओ err_mux;

	ulpi_node = of_get_child_by_name(pdev->dev.of_node, "ulpi");
	अगर (ulpi_node) अणु
		phy_node = of_get_next_available_child(ulpi_node, शून्य);
		ci->hsic = of_device_is_compatible(phy_node, "qcom,usb-hsic-phy");
		of_node_put(phy_node);
	पूर्ण
	of_node_put(ulpi_node);

	plat_ci = ci_hdrc_add_device(&pdev->dev, pdev->resource,
				     pdev->num_resources, &ci->pdata);
	अगर (IS_ERR(plat_ci)) अणु
		ret = PTR_ERR(plat_ci);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "ci_hdrc_add_device failed!\n");
		जाओ err_mux;
	पूर्ण

	ci->ci = plat_ci;

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_no_callbacks(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	वापस 0;

err_mux:
	clk_disable_unprepare(ci->अगरace_clk);
err_अगरace:
	clk_disable_unprepare(ci->core_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ci_hdrc_msm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ci_hdrc_msm *ci = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	ci_hdrc_हटाओ_device(ci->ci);
	clk_disable_unprepare(ci->अगरace_clk);
	clk_disable_unprepare(ci->core_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id msm_ci_dt_match[] = अणु
	अणु .compatible = "qcom,ci-hdrc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, msm_ci_dt_match);

अटल काष्ठा platक्रमm_driver ci_hdrc_msm_driver = अणु
	.probe = ci_hdrc_msm_probe,
	.हटाओ = ci_hdrc_msm_हटाओ,
	.driver = अणु
		.name = "msm_hsusb",
		.of_match_table = msm_ci_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ci_hdrc_msm_driver);

MODULE_ALIAS("platform:msm_hsusb");
MODULE_ALIAS("platform:ci13xxx_msm");
MODULE_LICENSE("GPL v2");
