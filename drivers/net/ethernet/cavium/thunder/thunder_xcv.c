<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>

#समावेश "nic.h"
#समावेश "thunder_bgx.h"

#घोषणा DRV_NAME	"thunder_xcv"
#घोषणा DRV_VERSION	"1.0"

/* Register offsets */
#घोषणा XCV_RESET		0x00
#घोषणा   PORT_EN		BIT_ULL(63)
#घोषणा   CLK_RESET		BIT_ULL(15)
#घोषणा   DLL_RESET		BIT_ULL(11)
#घोषणा   COMP_EN		BIT_ULL(7)
#घोषणा   TX_PKT_RESET		BIT_ULL(3)
#घोषणा   TX_DATA_RESET		BIT_ULL(2)
#घोषणा   RX_PKT_RESET		BIT_ULL(1)
#घोषणा   RX_DATA_RESET		BIT_ULL(0)
#घोषणा XCV_DLL_CTL		0x10
#घोषणा   CLKRX_BYP		BIT_ULL(23)
#घोषणा   CLKTX_BYP		BIT_ULL(15)
#घोषणा XCV_COMP_CTL		0x20
#घोषणा   DRV_BYP		BIT_ULL(63)
#घोषणा XCV_CTL			0x30
#घोषणा XCV_INT			0x40
#घोषणा XCV_INT_W1S		0x48
#घोषणा XCV_INT_ENA_W1C		0x50
#घोषणा XCV_INT_ENA_W1S		0x58
#घोषणा XCV_INBND_STATUS	0x80
#घोषणा XCV_BATCH_CRD_RET	0x100

काष्ठा xcv अणु
	व्योम __iomem		*reg_base;
	काष्ठा pci_dev		*pdev;
पूर्ण;

अटल काष्ठा xcv *xcv;

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id xcv_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, 0xA056) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

MODULE_AUTHOR("Cavium Inc");
MODULE_DESCRIPTION("Cavium Thunder RGX/XCV Driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, xcv_id_table);

व्योम xcv_init_hw(व्योम)
अणु
	u64  cfg;

	/* Take DLL out of reset */
	cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
	cfg &= ~DLL_RESET;
	ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_RESET);

	/* Take घड़ी tree out of reset */
	cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
	cfg &= ~CLK_RESET;
	ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_RESET);
	/* Wait क्रम DLL to lock */
	msleep(1);

	/* Configure DLL - enable or bypass
	 * TX no bypass, RX bypass
	 */
	cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_DLL_CTL);
	cfg &= ~0xFF03;
	cfg |= CLKRX_BYP;
	ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_DLL_CTL);

	/* Enable compensation controller and क्रमce the
	 * ग_लिखो to be visible to HW by पढ़ोig back.
	 */
	cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
	cfg |= COMP_EN;
	ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_RESET);
	पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
	/* Wait क्रम compensation state machine to lock */
	msleep(10);

	/* enable the XCV block */
	cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
	cfg |= PORT_EN;
	ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_RESET);

	cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
	cfg |= CLK_RESET;
	ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_RESET);
पूर्ण
EXPORT_SYMBOL(xcv_init_hw);

व्योम xcv_setup_link(bool link_up, पूर्णांक link_speed)
अणु
	u64  cfg;
	पूर्णांक speed = 2;

	अगर (!xcv) अणु
		pr_err("XCV init not done, probe may have failed\n");
		वापस;
	पूर्ण

	अगर (link_speed == 100)
		speed = 1;
	अन्यथा अगर (link_speed == 10)
		speed = 0;

	अगर (link_up) अणु
		/* set operating speed */
		cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_CTL);
		cfg &= ~0x03;
		cfg |= speed;
		ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_CTL);

		/* Reset datapaths */
		cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
		cfg |= TX_DATA_RESET | RX_DATA_RESET;
		ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_RESET);

		/* Enable the packet flow */
		cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
		cfg |= TX_PKT_RESET | RX_PKT_RESET;
		ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_RESET);

		/* Return credits to RGX */
		ग_लिखोq_relaxed(0x01, xcv->reg_base + XCV_BATCH_CRD_RET);
	पूर्ण अन्यथा अणु
		/* Disable packet flow */
		cfg = पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
		cfg &= ~(TX_PKT_RESET | RX_PKT_RESET);
		ग_लिखोq_relaxed(cfg, xcv->reg_base + XCV_RESET);
		पढ़ोq_relaxed(xcv->reg_base + XCV_RESET);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(xcv_setup_link);

अटल पूर्णांक xcv_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	काष्ठा device *dev = &pdev->dev;

	xcv = devm_kzalloc(dev, माप(काष्ठा xcv), GFP_KERNEL);
	अगर (!xcv)
		वापस -ENOMEM;
	xcv->pdev = pdev;

	pci_set_drvdata(pdev, xcv);

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		जाओ err_kमुक्त;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		जाओ err_disable_device;
	पूर्ण

	/* MAP configuration रेजिस्टरs */
	xcv->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	अगर (!xcv->reg_base) अणु
		dev_err(dev, "XCV: Cannot map CSR memory space, aborting\n");
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	वापस 0;

err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
err_kमुक्त:
	devm_kमुक्त(dev, xcv);
	xcv = शून्य;
	वापस err;
पूर्ण

अटल व्योम xcv_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	अगर (xcv) अणु
		devm_kमुक्त(dev, xcv);
		xcv = शून्य;
	पूर्ण

	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver xcv_driver = अणु
	.name = DRV_NAME,
	.id_table = xcv_id_table,
	.probe = xcv_probe,
	.हटाओ = xcv_हटाओ,
पूर्ण;

अटल पूर्णांक __init xcv_init_module(व्योम)
अणु
	pr_info("%s, ver %s\n", DRV_NAME, DRV_VERSION);

	वापस pci_रेजिस्टर_driver(&xcv_driver);
पूर्ण

अटल व्योम __निकास xcv_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&xcv_driver);
पूर्ण

module_init(xcv_init_module);
module_निकास(xcv_cleanup_module);
