<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/usb/host/ehci-orion.c
 *
 * Tzachi Perelstein <tzachi@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mbus.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_data/usb-ehci-orion.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>

#समावेश "ehci.h"

#घोषणा rdl(off)	पढ़ोl_relaxed(hcd->regs + (off))
#घोषणा wrl(off, val)	ग_लिखोl_relaxed((val), hcd->regs + (off))

#घोषणा USB_CMD			0x140
#घोषणा   USB_CMD_RUN		BIT(0)
#घोषणा   USB_CMD_RESET		BIT(1)
#घोषणा USB_MODE		0x1a8
#घोषणा   USB_MODE_MASK		GENMASK(1, 0)
#घोषणा   USB_MODE_DEVICE	0x2
#घोषणा   USB_MODE_HOST		0x3
#घोषणा   USB_MODE_SDIS		BIT(4)
#घोषणा USB_CAUSE		0x310
#घोषणा USB_MASK		0x314
#घोषणा USB_WINDOW_CTRL(i)	(0x320 + ((i) << 4))
#घोषणा USB_WINDOW_BASE(i)	(0x324 + ((i) << 4))
#घोषणा USB_IPG			0x360
#घोषणा USB_PHY_PWR_CTRL	0x400
#घोषणा USB_PHY_TX_CTRL		0x420
#घोषणा USB_PHY_RX_CTRL		0x430
#घोषणा USB_PHY_IVREF_CTRL	0x440
#घोषणा USB_PHY_TST_GRP_CTRL	0x450

#घोषणा USB_SBUSCFG		0x90

/* BAWR = BARD = 3 : Align पढ़ो/ग_लिखो bursts packets larger than 128 bytes */
#घोषणा USB_SBUSCFG_BAWR_ALIGN_128B	(0x3 << 6)
#घोषणा USB_SBUSCFG_BARD_ALIGN_128B	(0x3 << 3)
/* AHBBRST = 3	   : Align AHB Burst to INCR16 (64 bytes) */
#घोषणा USB_SBUSCFG_AHBBRST_INCR16	(0x3 << 0)

#घोषणा USB_SBUSCFG_DEF_VAL (USB_SBUSCFG_BAWR_ALIGN_128B	\
			     | USB_SBUSCFG_BARD_ALIGN_128B	\
			     | USB_SBUSCFG_AHBBRST_INCR16)

#घोषणा DRIVER_DESC "EHCI orion driver"

#घोषणा hcd_to_orion_priv(h) ((काष्ठा orion_ehci_hcd *)hcd_to_ehci(h)->priv)

काष्ठा orion_ehci_hcd अणु
	काष्ठा clk *clk;
	काष्ठा phy *phy;
पूर्ण;

अटल स्थिर अक्षर hcd_name[] = "ehci-orion";

अटल काष्ठा hc_driver __पढ़ो_mostly ehci_orion_hc_driver;

/*
 * Implement Orion USB controller specअगरication guidelines
 */
अटल व्योम orion_usb_phy_v1_setup(काष्ठा usb_hcd *hcd)
अणु
	/* The below GLs are according to the Orion Errata करोcument */
	/*
	 * Clear पूर्णांकerrupt cause and mask
	 */
	wrl(USB_CAUSE, 0);
	wrl(USB_MASK, 0);

	/*
	 * Reset controller
	 */
	wrl(USB_CMD, rdl(USB_CMD) | USB_CMD_RESET);
	जबतक (rdl(USB_CMD) & USB_CMD_RESET);

	/*
	 * GL# USB-10: Set IPG क्रम non start of frame packets
	 * Bits[14:8]=0xc
	 */
	wrl(USB_IPG, (rdl(USB_IPG) & ~0x7f00) | 0xc00);

	/*
	 * GL# USB-9: USB 2.0 Power Control
	 * BG_VSEL[7:6]=0x1
	 */
	wrl(USB_PHY_PWR_CTRL, (rdl(USB_PHY_PWR_CTRL) & ~0xc0)| 0x40);

	/*
	 * GL# USB-1: USB PHY Tx Control - क्रमce calibration to '8'
	 * TXDATA_BLOCK_EN[21]=0x1, EXT_RCAL_EN[13]=0x1, IMP_CAL[6:3]=0x8
	 */
	wrl(USB_PHY_TX_CTRL, (rdl(USB_PHY_TX_CTRL) & ~0x78) | 0x202040);

	/*
	 * GL# USB-3 GL# USB-9: USB PHY Rx Control
	 * RXDATA_BLOCK_LENGHT[31:30]=0x3, EDGE_DET_SEL[27:26]=0,
	 * CDR_FASTLOCK_EN[21]=0, DISCON_THRESHOLD[9:8]=0, SQ_THRESH[7:4]=0x1
	 */
	wrl(USB_PHY_RX_CTRL, (rdl(USB_PHY_RX_CTRL) & ~0xc2003f0) | 0xc0000010);

	/*
	 * GL# USB-3 GL# USB-9: USB PHY IVREF Control
	 * PLLVDD12[1:0]=0x2, RXVDD[5:4]=0x3, Reserved[19]=0
	 */
	wrl(USB_PHY_IVREF_CTRL, (rdl(USB_PHY_IVREF_CTRL) & ~0x80003 ) | 0x32);

	/*
	 * GL# USB-3 GL# USB-9: USB PHY Test Group Control
	 * REG_FIFO_SQ_RST[15]=0
	 */
	wrl(USB_PHY_TST_GRP_CTRL, rdl(USB_PHY_TST_GRP_CTRL) & ~0x8000);

	/*
	 * Stop and reset controller
	 */
	wrl(USB_CMD, rdl(USB_CMD) & ~USB_CMD_RUN);
	wrl(USB_CMD, rdl(USB_CMD) | USB_CMD_RESET);
	जबतक (rdl(USB_CMD) & USB_CMD_RESET);

	/*
	 * GL# USB-5 Streaming disable REG_USB_MODE[4]=1
	 * TBD: This need to be करोne after each reset!
	 * GL# USB-4 Setup USB Host mode
	 */
	wrl(USB_MODE, USB_MODE_SDIS | USB_MODE_HOST);
पूर्ण

अटल व्योम
ehci_orion_conf_mbus_winकरोws(काष्ठा usb_hcd *hcd,
			     स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		wrl(USB_WINDOW_CTRL(i), 0);
		wrl(USB_WINDOW_BASE(i), 0);
	पूर्ण

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		wrl(USB_WINDOW_CTRL(i), ((cs->size - 1) & 0xffff0000) |
					(cs->mbus_attr << 8) |
					(dram->mbus_dram_target_id << 4) | 1);
		wrl(USB_WINDOW_BASE(i), cs->base);
	पूर्ण
पूर्ण

अटल पूर्णांक ehci_orion_drv_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा device *dev = hcd->self.controller;
	पूर्णांक ret;

	ret = ehci_setup(hcd);
	अगर (ret)
		वापस ret;

	/*
	 * For SoC without hlock, need to program sbuscfg value to guarantee
	 * AHB master's burst would not overrun or underrun FIFO.
	 *
	 * sbuscfg reg has to be set after usb controller reset, otherwise
	 * the value would be override to 0.
	 */
	अगर (of_device_is_compatible(dev->of_node, "marvell,armada-3700-ehci"))
		wrl(USB_SBUSCFG, USB_SBUSCFG_DEF_VAL);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ehci_orion_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);

	वापस ehci_suspend(hcd, device_may_wakeup(dev));
पूर्ण

अटल पूर्णांक __maybe_unused ehci_orion_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);

	वापस ehci_resume(hcd, false);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ehci_orion_pm_ops, ehci_orion_drv_suspend,
			 ehci_orion_drv_resume);

अटल स्थिर काष्ठा ehci_driver_overrides orion_overrides __initस्थिर = अणु
	.extra_priv_size =	माप(काष्ठा orion_ehci_hcd),
	.reset = ehci_orion_drv_reset,
पूर्ण;

अटल पूर्णांक ehci_orion_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा orion_ehci_data *pd = dev_get_platdata(&pdev->dev);
	स्थिर काष्ठा mbus_dram_target_info *dram;
	काष्ठा resource *res;
	काष्ठा usb_hcd *hcd;
	काष्ठा ehci_hcd *ehci;
	व्योम __iomem *regs;
	पूर्णांक irq, err;
	क्रमागत orion_ehci_phy_ver phy_version;
	काष्ठा orion_ehci_hcd *priv;

	अगर (usb_disabled())
		वापस -ENODEV;

	pr_debug("Initializing Orion-SoC USB Host Controller\n");

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		err = -ENODEV;
		जाओ err;
	पूर्ण

	/*
	 * Right now device-tree probed devices करोn't get dma_mask
	 * set. Since shared usb code relies on it, set it here क्रम
	 * now. Once we have dma capability bindings this can go away.
	 */
	err = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err)
		जाओ err;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs)) अणु
		err = PTR_ERR(regs);
		जाओ err;
	पूर्ण

	hcd = usb_create_hcd(&ehci_orion_hc_driver,
			&pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);
	hcd->regs = regs;

	ehci = hcd_to_ehci(hcd);
	ehci->caps = hcd->regs + 0x100;
	hcd->has_tt = 1;

	priv = hcd_to_orion_priv(hcd);
	/*
	 * Not all platक्रमms can gate the घड़ी, so it is not an error अगर
	 * the घड़ी करोes not exists.
	 */
	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (!IS_ERR(priv->clk))
		clk_prepare_enable(priv->clk);

	priv->phy = devm_phy_optional_get(&pdev->dev, "usb");
	अगर (IS_ERR(priv->phy)) अणु
		err = PTR_ERR(priv->phy);
		अगर (err != -ENOSYS)
			जाओ err_dis_clk;
	पूर्ण

	/*
	 * (Re-)program MBUS remapping winकरोws अगर we are asked to.
	 */
	dram = mv_mbus_dram_info();
	अगर (dram)
		ehci_orion_conf_mbus_winकरोws(hcd, dram);

	/*
	 * setup Orion USB controller.
	 */
	अगर (pdev->dev.of_node)
		phy_version = EHCI_PHY_NA;
	अन्यथा
		phy_version = pd->phy_version;

	चयन (phy_version) अणु
	हाल EHCI_PHY_NA:	/* करोnt change USB phy settings */
		अवरोध;
	हाल EHCI_PHY_ORION:
		orion_usb_phy_v1_setup(hcd);
		अवरोध;
	हाल EHCI_PHY_DD:
	हाल EHCI_PHY_KW:
	शेष:
		dev_warn(&pdev->dev, "USB phy version isn't supported.\n");
	पूर्ण

	err = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (err)
		जाओ err_dis_clk;

	device_wakeup_enable(hcd->self.controller);
	वापस 0;

err_dis_clk:
	अगर (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);
	usb_put_hcd(hcd);
err:
	dev_err(&pdev->dev, "init %s fail, %d\n",
		dev_name(&pdev->dev), err);

	वापस err;
पूर्ण

अटल पूर्णांक ehci_orion_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा orion_ehci_hcd *priv = hcd_to_orion_priv(hcd);

	usb_हटाओ_hcd(hcd);

	अगर (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ehci_orion_dt_ids[] = अणु
	अणु .compatible = "marvell,orion-ehci", पूर्ण,
	अणु .compatible = "marvell,armada-3700-ehci", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ehci_orion_dt_ids);

अटल काष्ठा platक्रमm_driver ehci_orion_driver = अणु
	.probe		= ehci_orion_drv_probe,
	.हटाओ		= ehci_orion_drv_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver = अणु
		.name	= "orion-ehci",
		.of_match_table = ehci_orion_dt_ids,
		.pm = &ehci_orion_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ehci_orion_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ehci_init_driver(&ehci_orion_hc_driver, &orion_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&ehci_orion_driver);
पूर्ण
module_init(ehci_orion_init);

अटल व्योम __निकास ehci_orion_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ehci_orion_driver);
पूर्ण
module_निकास(ehci_orion_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_ALIAS("platform:orion-ehci");
MODULE_AUTHOR("Tzachi Perelstein");
MODULE_LICENSE("GPL v2");
