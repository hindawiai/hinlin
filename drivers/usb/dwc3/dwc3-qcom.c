<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, The Linux Foundation. All rights reserved.
 *
 * Inspired by dwc3-of-simple.c
 */

#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/extcon.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/reset.h>
#समावेश <linux/iopoll.h>

#समावेश "core.h"

/* USB QSCRATCH Hardware रेजिस्टरs */
#घोषणा QSCRATCH_HS_PHY_CTRL			0x10
#घोषणा UTMI_OTG_VBUS_VALID			BIT(20)
#घोषणा SW_SESSVLD_SEL				BIT(28)

#घोषणा QSCRATCH_SS_PHY_CTRL			0x30
#घोषणा LANE0_PWR_PRESENT			BIT(24)

#घोषणा QSCRATCH_GENERAL_CFG			0x08
#घोषणा PIPE_UTMI_CLK_SEL			BIT(0)
#घोषणा PIPE3_PHYSTATUS_SW			BIT(3)
#घोषणा PIPE_UTMI_CLK_DIS			BIT(8)

#घोषणा PWR_EVNT_IRQ_STAT_REG			0x58
#घोषणा PWR_EVNT_LPM_IN_L2_MASK			BIT(4)
#घोषणा PWR_EVNT_LPM_OUT_L2_MASK		BIT(5)

#घोषणा SDM845_QSCRATCH_BASE_OFFSET		0xf8800
#घोषणा SDM845_QSCRATCH_SIZE			0x400
#घोषणा SDM845_DWC3_CORE_SIZE			0xcd00

/* Interconnect path bandwidths in MBps */
#घोषणा USB_MEMORY_AVG_HS_BW MBps_to_icc(240)
#घोषणा USB_MEMORY_PEAK_HS_BW MBps_to_icc(700)
#घोषणा USB_MEMORY_AVG_SS_BW  MBps_to_icc(1000)
#घोषणा USB_MEMORY_PEAK_SS_BW MBps_to_icc(2500)
#घोषणा APPS_USB_AVG_BW 0
#घोषणा APPS_USB_PEAK_BW MBps_to_icc(40)

काष्ठा dwc3_acpi_pdata अणु
	u32			qscratch_base_offset;
	u32			qscratch_base_size;
	u32			dwc3_core_base_size;
	पूर्णांक			hs_phy_irq_index;
	पूर्णांक			dp_hs_phy_irq_index;
	पूर्णांक			dm_hs_phy_irq_index;
	पूर्णांक			ss_phy_irq_index;
	bool			is_urs;
पूर्ण;

काष्ठा dwc3_qcom अणु
	काष्ठा device		*dev;
	व्योम __iomem		*qscratch_base;
	काष्ठा platक्रमm_device	*dwc3;
	काष्ठा platक्रमm_device	*urs_usb;
	काष्ठा clk		**clks;
	पूर्णांक			num_घड़ीs;
	काष्ठा reset_control	*resets;

	पूर्णांक			hs_phy_irq;
	पूर्णांक			dp_hs_phy_irq;
	पूर्णांक			dm_hs_phy_irq;
	पूर्णांक			ss_phy_irq;

	काष्ठा extcon_dev	*edev;
	काष्ठा extcon_dev	*host_edev;
	काष्ठा notअगरier_block	vbus_nb;
	काष्ठा notअगरier_block	host_nb;

	स्थिर काष्ठा dwc3_acpi_pdata *acpi_pdata;

	क्रमागत usb_dr_mode	mode;
	bool			is_suspended;
	bool			pm_suspended;
	काष्ठा icc_path		*icc_path_ddr;
	काष्ठा icc_path		*icc_path_apps;
पूर्ण;

अटल अंतरभूत व्योम dwc3_qcom_setbits(व्योम __iomem *base, u32 offset, u32 val)
अणु
	u32 reg;

	reg = पढ़ोl(base + offset);
	reg |= val;
	ग_लिखोl(reg, base + offset);

	/* ensure that above ग_लिखो is through */
	पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत व्योम dwc3_qcom_clrbits(व्योम __iomem *base, u32 offset, u32 val)
अणु
	u32 reg;

	reg = पढ़ोl(base + offset);
	reg &= ~val;
	ग_लिखोl(reg, base + offset);

	/* ensure that above ग_लिखो is through */
	पढ़ोl(base + offset);
पूर्ण

अटल व्योम dwc3_qcom_vbus_overrride_enable(काष्ठा dwc3_qcom *qcom, bool enable)
अणु
	अगर (enable) अणु
		dwc3_qcom_setbits(qcom->qscratch_base, QSCRATCH_SS_PHY_CTRL,
				  LANE0_PWR_PRESENT);
		dwc3_qcom_setbits(qcom->qscratch_base, QSCRATCH_HS_PHY_CTRL,
				  UTMI_OTG_VBUS_VALID | SW_SESSVLD_SEL);
	पूर्ण अन्यथा अणु
		dwc3_qcom_clrbits(qcom->qscratch_base, QSCRATCH_SS_PHY_CTRL,
				  LANE0_PWR_PRESENT);
		dwc3_qcom_clrbits(qcom->qscratch_base, QSCRATCH_HS_PHY_CTRL,
				  UTMI_OTG_VBUS_VALID | SW_SESSVLD_SEL);
	पूर्ण
पूर्ण

अटल पूर्णांक dwc3_qcom_vbus_notअगरier(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा dwc3_qcom *qcom = container_of(nb, काष्ठा dwc3_qcom, vbus_nb);

	/* enable vbus override क्रम device mode */
	dwc3_qcom_vbus_overrride_enable(qcom, event);
	qcom->mode = event ? USB_DR_MODE_PERIPHERAL : USB_DR_MODE_HOST;

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक dwc3_qcom_host_notअगरier(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा dwc3_qcom *qcom = container_of(nb, काष्ठा dwc3_qcom, host_nb);

	/* disable vbus override in host mode */
	dwc3_qcom_vbus_overrride_enable(qcom, !event);
	qcom->mode = event ? USB_DR_MODE_HOST : USB_DR_MODE_PERIPHERAL;

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक dwc3_qcom_रेजिस्टर_extcon(काष्ठा dwc3_qcom *qcom)
अणु
	काष्ठा device		*dev = qcom->dev;
	काष्ठा extcon_dev	*host_edev;
	पूर्णांक			ret;

	अगर (!of_property_पढ़ो_bool(dev->of_node, "extcon"))
		वापस 0;

	qcom->edev = extcon_get_edev_by_phandle(dev, 0);
	अगर (IS_ERR(qcom->edev))
		वापस PTR_ERR(qcom->edev);

	qcom->vbus_nb.notअगरier_call = dwc3_qcom_vbus_notअगरier;

	qcom->host_edev = extcon_get_edev_by_phandle(dev, 1);
	अगर (IS_ERR(qcom->host_edev))
		qcom->host_edev = शून्य;

	ret = devm_extcon_रेजिस्टर_notअगरier(dev, qcom->edev, EXTCON_USB,
					    &qcom->vbus_nb);
	अगर (ret < 0) अणु
		dev_err(dev, "VBUS notifier register failed\n");
		वापस ret;
	पूर्ण

	अगर (qcom->host_edev)
		host_edev = qcom->host_edev;
	अन्यथा
		host_edev = qcom->edev;

	qcom->host_nb.notअगरier_call = dwc3_qcom_host_notअगरier;
	ret = devm_extcon_रेजिस्टर_notअगरier(dev, host_edev, EXTCON_USB_HOST,
					    &qcom->host_nb);
	अगर (ret < 0) अणु
		dev_err(dev, "Host notifier register failed\n");
		वापस ret;
	पूर्ण

	/* Update initial VBUS override based on extcon state */
	अगर (extcon_get_state(qcom->edev, EXTCON_USB) ||
	    !extcon_get_state(host_edev, EXTCON_USB_HOST))
		dwc3_qcom_vbus_notअगरier(&qcom->vbus_nb, true, qcom->edev);
	अन्यथा
		dwc3_qcom_vbus_notअगरier(&qcom->vbus_nb, false, qcom->edev);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_qcom_पूर्णांकerconnect_enable(काष्ठा dwc3_qcom *qcom)
अणु
	पूर्णांक ret;

	ret = icc_enable(qcom->icc_path_ddr);
	अगर (ret)
		वापस ret;

	ret = icc_enable(qcom->icc_path_apps);
	अगर (ret)
		icc_disable(qcom->icc_path_ddr);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_qcom_पूर्णांकerconnect_disable(काष्ठा dwc3_qcom *qcom)
अणु
	पूर्णांक ret;

	ret = icc_disable(qcom->icc_path_ddr);
	अगर (ret)
		वापस ret;

	ret = icc_disable(qcom->icc_path_apps);
	अगर (ret)
		icc_enable(qcom->icc_path_ddr);

	वापस ret;
पूर्ण

/**
 * dwc3_qcom_पूर्णांकerconnect_init() - Get पूर्णांकerconnect path handles
 * and set bandwidth.
 * @qcom:			Poपूर्णांकer to the concerned usb core.
 *
 */
अटल पूर्णांक dwc3_qcom_पूर्णांकerconnect_init(काष्ठा dwc3_qcom *qcom)
अणु
	काष्ठा device *dev = qcom->dev;
	पूर्णांक ret;

	अगर (has_acpi_companion(dev))
		वापस 0;

	qcom->icc_path_ddr = of_icc_get(dev, "usb-ddr");
	अगर (IS_ERR(qcom->icc_path_ddr)) अणु
		dev_err(dev, "failed to get usb-ddr path: %ld\n",
			PTR_ERR(qcom->icc_path_ddr));
		वापस PTR_ERR(qcom->icc_path_ddr);
	पूर्ण

	qcom->icc_path_apps = of_icc_get(dev, "apps-usb");
	अगर (IS_ERR(qcom->icc_path_apps)) अणु
		dev_err(dev, "failed to get apps-usb path: %ld\n",
				PTR_ERR(qcom->icc_path_apps));
		वापस PTR_ERR(qcom->icc_path_apps);
	पूर्ण

	अगर (usb_get_maximum_speed(&qcom->dwc3->dev) >= USB_SPEED_SUPER ||
			usb_get_maximum_speed(&qcom->dwc3->dev) == USB_SPEED_UNKNOWN)
		ret = icc_set_bw(qcom->icc_path_ddr,
			USB_MEMORY_AVG_SS_BW, USB_MEMORY_PEAK_SS_BW);
	अन्यथा
		ret = icc_set_bw(qcom->icc_path_ddr,
			USB_MEMORY_AVG_HS_BW, USB_MEMORY_PEAK_HS_BW);

	अगर (ret) अणु
		dev_err(dev, "failed to set bandwidth for usb-ddr path: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = icc_set_bw(qcom->icc_path_apps,
		APPS_USB_AVG_BW, APPS_USB_PEAK_BW);
	अगर (ret) अणु
		dev_err(dev, "failed to set bandwidth for apps-usb path: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dwc3_qcom_पूर्णांकerconnect_निकास() - Release पूर्णांकerconnect path handles
 * @qcom:			Poपूर्णांकer to the concerned usb core.
 *
 * This function is used to release पूर्णांकerconnect path handle.
 */
अटल व्योम dwc3_qcom_पूर्णांकerconnect_निकास(काष्ठा dwc3_qcom *qcom)
अणु
	icc_put(qcom->icc_path_ddr);
	icc_put(qcom->icc_path_apps);
पूर्ण

अटल व्योम dwc3_qcom_disable_पूर्णांकerrupts(काष्ठा dwc3_qcom *qcom)
अणु
	अगर (qcom->hs_phy_irq) अणु
		disable_irq_wake(qcom->hs_phy_irq);
		disable_irq_nosync(qcom->hs_phy_irq);
	पूर्ण

	अगर (qcom->dp_hs_phy_irq) अणु
		disable_irq_wake(qcom->dp_hs_phy_irq);
		disable_irq_nosync(qcom->dp_hs_phy_irq);
	पूर्ण

	अगर (qcom->dm_hs_phy_irq) अणु
		disable_irq_wake(qcom->dm_hs_phy_irq);
		disable_irq_nosync(qcom->dm_hs_phy_irq);
	पूर्ण

	अगर (qcom->ss_phy_irq) अणु
		disable_irq_wake(qcom->ss_phy_irq);
		disable_irq_nosync(qcom->ss_phy_irq);
	पूर्ण
पूर्ण

अटल व्योम dwc3_qcom_enable_पूर्णांकerrupts(काष्ठा dwc3_qcom *qcom)
अणु
	अगर (qcom->hs_phy_irq) अणु
		enable_irq(qcom->hs_phy_irq);
		enable_irq_wake(qcom->hs_phy_irq);
	पूर्ण

	अगर (qcom->dp_hs_phy_irq) अणु
		enable_irq(qcom->dp_hs_phy_irq);
		enable_irq_wake(qcom->dp_hs_phy_irq);
	पूर्ण

	अगर (qcom->dm_hs_phy_irq) अणु
		enable_irq(qcom->dm_hs_phy_irq);
		enable_irq_wake(qcom->dm_hs_phy_irq);
	पूर्ण

	अगर (qcom->ss_phy_irq) अणु
		enable_irq(qcom->ss_phy_irq);
		enable_irq_wake(qcom->ss_phy_irq);
	पूर्ण
पूर्ण

अटल पूर्णांक dwc3_qcom_suspend(काष्ठा dwc3_qcom *qcom)
अणु
	u32 val;
	पूर्णांक i, ret;

	अगर (qcom->is_suspended)
		वापस 0;

	val = पढ़ोl(qcom->qscratch_base + PWR_EVNT_IRQ_STAT_REG);
	अगर (!(val & PWR_EVNT_LPM_IN_L2_MASK))
		dev_err(qcom->dev, "HS-PHY not in L2\n");

	क्रम (i = qcom->num_घड़ीs - 1; i >= 0; i--)
		clk_disable_unprepare(qcom->clks[i]);

	ret = dwc3_qcom_पूर्णांकerconnect_disable(qcom);
	अगर (ret)
		dev_warn(qcom->dev, "failed to disable interconnect: %d\n", ret);

	अगर (device_may_wakeup(qcom->dev))
		dwc3_qcom_enable_पूर्णांकerrupts(qcom);

	qcom->is_suspended = true;

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_qcom_resume(काष्ठा dwc3_qcom *qcom)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!qcom->is_suspended)
		वापस 0;

	अगर (device_may_wakeup(qcom->dev))
		dwc3_qcom_disable_पूर्णांकerrupts(qcom);

	क्रम (i = 0; i < qcom->num_घड़ीs; i++) अणु
		ret = clk_prepare_enable(qcom->clks[i]);
		अगर (ret < 0) अणु
			जबतक (--i >= 0)
				clk_disable_unprepare(qcom->clks[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = dwc3_qcom_पूर्णांकerconnect_enable(qcom);
	अगर (ret)
		dev_warn(qcom->dev, "failed to enable interconnect: %d\n", ret);

	/* Clear existing events from PHY related to L2 in/out */
	dwc3_qcom_setbits(qcom->qscratch_base, PWR_EVNT_IRQ_STAT_REG,
			  PWR_EVNT_LPM_IN_L2_MASK | PWR_EVNT_LPM_OUT_L2_MASK);

	qcom->is_suspended = false;

	वापस 0;
पूर्ण

अटल irqवापस_t qcom_dwc3_resume_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा dwc3_qcom *qcom = data;
	काष्ठा dwc3	*dwc = platक्रमm_get_drvdata(qcom->dwc3);

	/* If pm_suspended then let pm_resume take care of resuming h/w */
	अगर (qcom->pm_suspended)
		वापस IRQ_HANDLED;

	अगर (dwc->xhci)
		pm_runसमय_resume(&dwc->xhci->dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dwc3_qcom_select_uपंचांगi_clk(काष्ठा dwc3_qcom *qcom)
अणु
	/* Configure dwc3 to use UTMI घड़ी as PIPE घड़ी not present */
	dwc3_qcom_setbits(qcom->qscratch_base, QSCRATCH_GENERAL_CFG,
			  PIPE_UTMI_CLK_DIS);

	usleep_range(100, 1000);

	dwc3_qcom_setbits(qcom->qscratch_base, QSCRATCH_GENERAL_CFG,
			  PIPE_UTMI_CLK_SEL | PIPE3_PHYSTATUS_SW);

	usleep_range(100, 1000);

	dwc3_qcom_clrbits(qcom->qscratch_base, QSCRATCH_GENERAL_CFG,
			  PIPE_UTMI_CLK_DIS);
पूर्ण

अटल पूर्णांक dwc3_qcom_get_irq(काष्ठा platक्रमm_device *pdev,
			     स्थिर अक्षर *name, पूर्णांक num)
अणु
	काष्ठा dwc3_qcom *qcom = platक्रमm_get_drvdata(pdev);
	काष्ठा platक्रमm_device *pdev_irq = qcom->urs_usb ? qcom->urs_usb : pdev;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	अगर (np)
		ret = platक्रमm_get_irq_byname(pdev_irq, name);
	अन्यथा
		ret = platक्रमm_get_irq(pdev_irq, num);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_qcom_setup_irq(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_qcom *qcom = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा dwc3_acpi_pdata *pdata = qcom->acpi_pdata;
	पूर्णांक irq;
	पूर्णांक ret;

	irq = dwc3_qcom_get_irq(pdev, "hs_phy_irq",
				pdata ? pdata->hs_phy_irq_index : -1);
	अगर (irq > 0) अणु
		/* Keep wakeup पूर्णांकerrupts disabled until suspend */
		irq_set_status_flags(irq, IRQ_NOAUTOEN);
		ret = devm_request_thपढ़ोed_irq(qcom->dev, irq, शून्य,
					qcom_dwc3_resume_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"qcom_dwc3 HS", qcom);
		अगर (ret) अणु
			dev_err(qcom->dev, "hs_phy_irq failed: %d\n", ret);
			वापस ret;
		पूर्ण
		qcom->hs_phy_irq = irq;
	पूर्ण

	irq = dwc3_qcom_get_irq(pdev, "dp_hs_phy_irq",
				pdata ? pdata->dp_hs_phy_irq_index : -1);
	अगर (irq > 0) अणु
		irq_set_status_flags(irq, IRQ_NOAUTOEN);
		ret = devm_request_thपढ़ोed_irq(qcom->dev, irq, शून्य,
					qcom_dwc3_resume_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"qcom_dwc3 DP_HS", qcom);
		अगर (ret) अणु
			dev_err(qcom->dev, "dp_hs_phy_irq failed: %d\n", ret);
			वापस ret;
		पूर्ण
		qcom->dp_hs_phy_irq = irq;
	पूर्ण

	irq = dwc3_qcom_get_irq(pdev, "dm_hs_phy_irq",
				pdata ? pdata->dm_hs_phy_irq_index : -1);
	अगर (irq > 0) अणु
		irq_set_status_flags(irq, IRQ_NOAUTOEN);
		ret = devm_request_thपढ़ोed_irq(qcom->dev, irq, शून्य,
					qcom_dwc3_resume_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"qcom_dwc3 DM_HS", qcom);
		अगर (ret) अणु
			dev_err(qcom->dev, "dm_hs_phy_irq failed: %d\n", ret);
			वापस ret;
		पूर्ण
		qcom->dm_hs_phy_irq = irq;
	पूर्ण

	irq = dwc3_qcom_get_irq(pdev, "ss_phy_irq",
				pdata ? pdata->ss_phy_irq_index : -1);
	अगर (irq > 0) अणु
		irq_set_status_flags(irq, IRQ_NOAUTOEN);
		ret = devm_request_thपढ़ोed_irq(qcom->dev, irq, शून्य,
					qcom_dwc3_resume_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"qcom_dwc3 SS", qcom);
		अगर (ret) अणु
			dev_err(qcom->dev, "ss_phy_irq failed: %d\n", ret);
			वापस ret;
		पूर्ण
		qcom->ss_phy_irq = irq;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_qcom_clk_init(काष्ठा dwc3_qcom *qcom, पूर्णांक count)
अणु
	काष्ठा device		*dev = qcom->dev;
	काष्ठा device_node	*np = dev->of_node;
	पूर्णांक			i;

	अगर (!np || !count)
		वापस 0;

	अगर (count < 0)
		वापस count;

	qcom->num_घड़ीs = count;

	qcom->clks = devm_kसुस्मृति(dev, qcom->num_घड़ीs,
				  माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!qcom->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < qcom->num_घड़ीs; i++) अणु
		काष्ठा clk	*clk;
		पूर्णांक		ret;

		clk = of_clk_get(np, i);
		अगर (IS_ERR(clk)) अणु
			जबतक (--i >= 0)
				clk_put(qcom->clks[i]);
			वापस PTR_ERR(clk);
		पूर्ण

		ret = clk_prepare_enable(clk);
		अगर (ret < 0) अणु
			जबतक (--i >= 0) अणु
				clk_disable_unprepare(qcom->clks[i]);
				clk_put(qcom->clks[i]);
			पूर्ण
			clk_put(clk);

			वापस ret;
		पूर्ण

		qcom->clks[i] = clk;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा property_entry dwc3_qcom_acpi_properties[] = अणु
	PROPERTY_ENTRY_STRING("dr_mode", "host"),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node dwc3_qcom_swnode = अणु
	.properties = dwc3_qcom_acpi_properties,
पूर्ण;

अटल पूर्णांक dwc3_qcom_acpi_रेजिस्टर_core(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_qcom	*qcom = platक्रमm_get_drvdata(pdev);
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा resource		*res, *child_res = शून्य;
	काष्ठा platक्रमm_device	*pdev_irq = qcom->urs_usb ? qcom->urs_usb :
							    pdev;
	पूर्णांक			irq;
	पूर्णांक			ret;

	qcom->dwc3 = platक्रमm_device_alloc("dwc3", PLATFORM_DEVID_AUTO);
	अगर (!qcom->dwc3)
		वापस -ENOMEM;

	qcom->dwc3->dev.parent = dev;
	qcom->dwc3->dev.type = dev->type;
	qcom->dwc3->dev.dma_mask = dev->dma_mask;
	qcom->dwc3->dev.dma_parms = dev->dma_parms;
	qcom->dwc3->dev.coherent_dma_mask = dev->coherent_dma_mask;

	child_res = kसुस्मृति(2, माप(*child_res), GFP_KERNEL);
	अगर (!child_res)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "failed to get memory resource\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	child_res[0].flags = res->flags;
	child_res[0].start = res->start;
	child_res[0].end = child_res[0].start +
		qcom->acpi_pdata->dwc3_core_base_size;

	irq = platक्रमm_get_irq(pdev_irq, 0);
	child_res[1].flags = IORESOURCE_IRQ;
	child_res[1].start = child_res[1].end = irq;

	ret = platक्रमm_device_add_resources(qcom->dwc3, child_res, 2);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add resources\n");
		जाओ out;
	पूर्ण

	ret = device_add_software_node(&qcom->dwc3->dev, &dwc3_qcom_swnode);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to add properties\n");
		जाओ out;
	पूर्ण

	ret = platक्रमm_device_add(qcom->dwc3);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add device\n");
		device_हटाओ_software_node(&qcom->dwc3->dev);
	पूर्ण

out:
	kमुक्त(child_res);
	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_qcom_of_रेजिस्टर_core(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_qcom	*qcom = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node	*np = pdev->dev.of_node, *dwc3_np;
	काष्ठा device		*dev = &pdev->dev;
	पूर्णांक			ret;

	dwc3_np = of_get_compatible_child(np, "snps,dwc3");
	अगर (!dwc3_np) अणु
		dev_err(dev, "failed to find dwc3 core child\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_platक्रमm_populate(np, शून्य, शून्य, dev);
	अगर (ret) अणु
		dev_err(dev, "failed to register dwc3 core - %d\n", ret);
		जाओ node_put;
	पूर्ण

	qcom->dwc3 = of_find_device_by_node(dwc3_np);
	अगर (!qcom->dwc3) अणु
		ret = -ENODEV;
		dev_err(dev, "failed to get dwc3 platform device\n");
	पूर्ण

node_put:
	of_node_put(dwc3_np);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_device *
dwc3_qcom_create_urs_usb_platdev(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *fwh;
	काष्ठा acpi_device *adev;
	अक्षर name[8];
	पूर्णांक ret;
	पूर्णांक id;

	/* Figure out device id */
	ret = माला_पूछो(fwnode_get_name(dev->fwnode), "URS%d", &id);
	अगर (!ret)
		वापस शून्य;

	/* Find the child using name */
	snम_लिखो(name, माप(name), "USB%d", id);
	fwh = fwnode_get_named_child_node(dev->fwnode, name);
	अगर (!fwh)
		वापस शून्य;

	adev = to_acpi_device_node(fwh);
	अगर (!adev)
		वापस शून्य;

	वापस acpi_create_platक्रमm_device(adev, शून्य);
पूर्ण

अटल पूर्णांक dwc3_qcom_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node	*np = pdev->dev.of_node;
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा dwc3_qcom	*qcom;
	काष्ठा resource		*res, *parent_res = शून्य;
	पूर्णांक			ret, i;
	bool			ignore_pipe_clk;

	qcom = devm_kzalloc(&pdev->dev, माप(*qcom), GFP_KERNEL);
	अगर (!qcom)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, qcom);
	qcom->dev = &pdev->dev;

	अगर (has_acpi_companion(dev)) अणु
		qcom->acpi_pdata = acpi_device_get_match_data(dev);
		अगर (!qcom->acpi_pdata) अणु
			dev_err(&pdev->dev, "no supporting ACPI device data\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	qcom->resets = devm_reset_control_array_get_optional_exclusive(dev);
	अगर (IS_ERR(qcom->resets)) अणु
		ret = PTR_ERR(qcom->resets);
		dev_err(&pdev->dev, "failed to get resets, err=%d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_निश्चित(qcom->resets);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to assert resets, err=%d\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(10, 1000);

	ret = reset_control_deनिश्चित(qcom->resets);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to deassert resets, err=%d\n", ret);
		जाओ reset_निश्चित;
	पूर्ण

	ret = dwc3_qcom_clk_init(qcom, of_clk_get_parent_count(np));
	अगर (ret) अणु
		dev_err(dev, "failed to get clocks\n");
		जाओ reset_निश्चित;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	अगर (np) अणु
		parent_res = res;
	पूर्ण अन्यथा अणु
		parent_res = kmemdup(res, माप(काष्ठा resource), GFP_KERNEL);
		अगर (!parent_res)
			वापस -ENOMEM;

		parent_res->start = res->start +
			qcom->acpi_pdata->qscratch_base_offset;
		parent_res->end = parent_res->start +
			qcom->acpi_pdata->qscratch_base_size;

		अगर (qcom->acpi_pdata->is_urs) अणु
			qcom->urs_usb = dwc3_qcom_create_urs_usb_platdev(dev);
			अगर (!qcom->urs_usb) अणु
				dev_err(dev, "failed to create URS USB platdev\n");
				वापस -ENODEV;
			पूर्ण
		पूर्ण
	पूर्ण

	qcom->qscratch_base = devm_ioremap_resource(dev, parent_res);
	अगर (IS_ERR(qcom->qscratch_base)) अणु
		ret = PTR_ERR(qcom->qscratch_base);
		जाओ clk_disable;
	पूर्ण

	ret = dwc3_qcom_setup_irq(pdev);
	अगर (ret) अणु
		dev_err(dev, "failed to setup IRQs, err=%d\n", ret);
		जाओ clk_disable;
	पूर्ण

	/*
	 * Disable pipe_clk requirement अगर specअगरied. Used when dwc3
	 * operates without SSPHY and only HS/FS/LS modes are supported.
	 */
	ignore_pipe_clk = device_property_पढ़ो_bool(dev,
				"qcom,select-utmi-as-pipe-clk");
	अगर (ignore_pipe_clk)
		dwc3_qcom_select_uपंचांगi_clk(qcom);

	अगर (np)
		ret = dwc3_qcom_of_रेजिस्टर_core(pdev);
	अन्यथा
		ret = dwc3_qcom_acpi_रेजिस्टर_core(pdev);

	अगर (ret) अणु
		dev_err(dev, "failed to register DWC3 Core, err=%d\n", ret);
		जाओ depopulate;
	पूर्ण

	ret = dwc3_qcom_पूर्णांकerconnect_init(qcom);
	अगर (ret)
		जाओ depopulate;

	qcom->mode = usb_get_dr_mode(&qcom->dwc3->dev);

	/* enable vbus override क्रम device mode */
	अगर (qcom->mode == USB_DR_MODE_PERIPHERAL)
		dwc3_qcom_vbus_overrride_enable(qcom, true);

	/* रेजिस्टर extcon to override sw_vbus on Vbus change later */
	ret = dwc3_qcom_रेजिस्टर_extcon(qcom);
	अगर (ret)
		जाओ पूर्णांकerconnect_निकास;

	device_init_wakeup(&pdev->dev, 1);
	qcom->is_suspended = false;
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_क्रमbid(dev);

	वापस 0;

पूर्णांकerconnect_निकास:
	dwc3_qcom_पूर्णांकerconnect_निकास(qcom);
depopulate:
	अगर (np)
		of_platक्रमm_depopulate(&pdev->dev);
	अन्यथा
		platक्रमm_device_put(pdev);
clk_disable:
	क्रम (i = qcom->num_घड़ीs - 1; i >= 0; i--) अणु
		clk_disable_unprepare(qcom->clks[i]);
		clk_put(qcom->clks[i]);
	पूर्ण
reset_निश्चित:
	reset_control_निश्चित(qcom->resets);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_qcom_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_qcom *qcom = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i;

	device_हटाओ_software_node(&qcom->dwc3->dev);
	of_platक्रमm_depopulate(dev);

	क्रम (i = qcom->num_घड़ीs - 1; i >= 0; i--) अणु
		clk_disable_unprepare(qcom->clks[i]);
		clk_put(qcom->clks[i]);
	पूर्ण
	qcom->num_घड़ीs = 0;

	dwc3_qcom_पूर्णांकerconnect_निकास(qcom);
	reset_control_निश्चित(qcom->resets);

	pm_runसमय_allow(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_qcom_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_qcom *qcom = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	ret = dwc3_qcom_suspend(qcom);
	अगर (!ret)
		qcom->pm_suspended = true;

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_qcom_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_qcom *qcom = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = dwc3_qcom_resume(qcom);
	अगर (!ret)
		qcom->pm_suspended = false;

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_qcom_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_qcom *qcom = dev_get_drvdata(dev);

	वापस dwc3_qcom_suspend(qcom);
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_qcom_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_qcom *qcom = dev_get_drvdata(dev);

	वापस dwc3_qcom_resume(qcom);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dwc3_qcom_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dwc3_qcom_pm_suspend, dwc3_qcom_pm_resume)
	SET_RUNTIME_PM_OPS(dwc3_qcom_runसमय_suspend, dwc3_qcom_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id dwc3_qcom_of_match[] = अणु
	अणु .compatible = "qcom,dwc3" पूर्ण,
	अणु .compatible = "qcom,msm8996-dwc3" पूर्ण,
	अणु .compatible = "qcom,msm8998-dwc3" पूर्ण,
	अणु .compatible = "qcom,sdm845-dwc3" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dwc3_qcom_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा dwc3_acpi_pdata sdm845_acpi_pdata = अणु
	.qscratch_base_offset = SDM845_QSCRATCH_BASE_OFFSET,
	.qscratch_base_size = SDM845_QSCRATCH_SIZE,
	.dwc3_core_base_size = SDM845_DWC3_CORE_SIZE,
	.hs_phy_irq_index = 1,
	.dp_hs_phy_irq_index = 4,
	.dm_hs_phy_irq_index = 3,
	.ss_phy_irq_index = 2
पूर्ण;

अटल स्थिर काष्ठा dwc3_acpi_pdata sdm845_acpi_urs_pdata = अणु
	.qscratch_base_offset = SDM845_QSCRATCH_BASE_OFFSET,
	.qscratch_base_size = SDM845_QSCRATCH_SIZE,
	.dwc3_core_base_size = SDM845_DWC3_CORE_SIZE,
	.hs_phy_irq_index = 1,
	.dp_hs_phy_irq_index = 4,
	.dm_hs_phy_irq_index = 3,
	.ss_phy_irq_index = 2,
	.is_urs = true,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id dwc3_qcom_acpi_match[] = अणु
	अणु "QCOM2430", (अचिन्हित दीर्घ)&sdm845_acpi_pdata पूर्ण,
	अणु "QCOM0304", (अचिन्हित दीर्घ)&sdm845_acpi_urs_pdata पूर्ण,
	अणु "QCOM0497", (अचिन्हित दीर्घ)&sdm845_acpi_urs_pdata पूर्ण,
	अणु "QCOM04A6", (अचिन्हित दीर्घ)&sdm845_acpi_pdata पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dwc3_qcom_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver dwc3_qcom_driver = अणु
	.probe		= dwc3_qcom_probe,
	.हटाओ		= dwc3_qcom_हटाओ,
	.driver		= अणु
		.name	= "dwc3-qcom",
		.pm	= &dwc3_qcom_dev_pm_ops,
		.of_match_table	= dwc3_qcom_of_match,
		.acpi_match_table = ACPI_PTR(dwc3_qcom_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dwc3_qcom_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DesignWare DWC3 QCOM Glue Driver");
