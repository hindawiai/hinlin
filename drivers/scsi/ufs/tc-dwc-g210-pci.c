<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Synopsys G210 Test Chip driver
 *
 * Copyright (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authors: Joao Pपूर्णांकo <jpपूर्णांकo@synopsys.com>
 */

#समावेश "ufshcd.h"
#समावेश "ufshcd-dwc.h"
#समावेश "tc-dwc-g210.h"

#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>

/* Test Chip type expected values */
#घोषणा TC_G210_20BIT 20
#घोषणा TC_G210_40BIT 40
#घोषणा TC_G210_INV 0

अटल पूर्णांक tc_type = TC_G210_INV;
module_param(tc_type, पूर्णांक, 0);
MODULE_PARM_DESC(tc_type, "Test Chip Type (20 = 20-bit, 40 = 40-bit)");

अटल पूर्णांक tc_dwc_g210_pci_suspend(काष्ठा device *dev)
अणु
	वापस ufshcd_प्रणाली_suspend(dev_get_drvdata(dev));
पूर्ण

अटल पूर्णांक tc_dwc_g210_pci_resume(काष्ठा device *dev)
अणु
	वापस ufshcd_प्रणाली_resume(dev_get_drvdata(dev));
पूर्ण

अटल पूर्णांक tc_dwc_g210_pci_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस ufshcd_runसमय_suspend(dev_get_drvdata(dev));
पूर्ण

अटल पूर्णांक tc_dwc_g210_pci_runसमय_resume(काष्ठा device *dev)
अणु
	वापस ufshcd_runसमय_resume(dev_get_drvdata(dev));
पूर्ण

अटल पूर्णांक tc_dwc_g210_pci_runसमय_idle(काष्ठा device *dev)
अणु
	वापस ufshcd_runसमय_idle(dev_get_drvdata(dev));
पूर्ण

/*
 * काष्ठा ufs_hba_dwc_vops - UFS DWC specअगरic variant operations
 */
अटल काष्ठा ufs_hba_variant_ops tc_dwc_g210_pci_hba_vops = अणु
	.name                   = "tc-dwc-g210-pci",
	.link_startup_notअगरy	= ufshcd_dwc_link_startup_notअगरy,
पूर्ण;

/**
 * tc_dwc_g210_pci_shutकरोwn - मुख्य function to put the controller in reset state
 * @pdev: poपूर्णांकer to PCI device handle
 */
अटल व्योम tc_dwc_g210_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	ufshcd_shutकरोwn((काष्ठा ufs_hba *)pci_get_drvdata(pdev));
पूर्ण

/**
 * tc_dwc_g210_pci_हटाओ - de-allocate PCI/SCSI host and host memory space
 *		data काष्ठाure memory
 * @pdev: poपूर्णांकer to PCI handle
 */
अटल व्योम tc_dwc_g210_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ufs_hba *hba = pci_get_drvdata(pdev);

	pm_runसमय_क्रमbid(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);
	ufshcd_हटाओ(hba);
पूर्ण

/**
 * tc_dwc_g210_pci_probe - probe routine of the driver
 * @pdev: poपूर्णांकer to PCI device handle
 * @id: PCI device id
 *
 * Returns 0 on success, non-zero value on failure
 */
अटल पूर्णांक
tc_dwc_g210_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ufs_hba *hba;
	व्योम __iomem *mmio_base;
	पूर्णांक err;

	/* Check Test Chip type and set the specअगरic setup routine */
	अगर (tc_type == TC_G210_20BIT) अणु
		tc_dwc_g210_pci_hba_vops.phy_initialization =
						tc_dwc_g210_config_20_bit;
	पूर्ण अन्यथा अगर (tc_type == TC_G210_40BIT) अणु
		tc_dwc_g210_pci_hba_vops.phy_initialization =
						tc_dwc_g210_config_40_bit;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "test chip version not specified\n");
		वापस -EPERM;
	पूर्ण

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "pcim_enable_device failed\n");
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	err = pcim_iomap_regions(pdev, 1 << 0, UFSHCD);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "request and iomap failed\n");
		वापस err;
	पूर्ण

	mmio_base = pcim_iomap_table(pdev)[0];

	err = ufshcd_alloc_host(&pdev->dev, &hba);
	अगर (err) अणु
		dev_err(&pdev->dev, "Allocation failed\n");
		वापस err;
	पूर्ण

	hba->vops = &tc_dwc_g210_pci_hba_vops;

	err = ufshcd_init(hba, mmio_base, pdev->irq);
	अगर (err) अणु
		dev_err(&pdev->dev, "Initialization failed\n");
		वापस err;
	पूर्ण

	pci_set_drvdata(pdev, hba);
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tc_dwc_g210_pci_pm_ops = अणु
	.suspend	= tc_dwc_g210_pci_suspend,
	.resume		= tc_dwc_g210_pci_resume,
	.runसमय_suspend = tc_dwc_g210_pci_runसमय_suspend,
	.runसमय_resume  = tc_dwc_g210_pci_runसमय_resume,
	.runसमय_idle    = tc_dwc_g210_pci_runसमय_idle,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id tc_dwc_g210_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_SYNOPSYS, 0xB101, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_SYNOPSYS, 0xB102, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;

MODULE_DEVICE_TABLE(pci, tc_dwc_g210_pci_tbl);

अटल काष्ठा pci_driver tc_dwc_g210_pci_driver = अणु
	.name = "tc-dwc-g210-pci",
	.id_table = tc_dwc_g210_pci_tbl,
	.probe = tc_dwc_g210_pci_probe,
	.हटाओ = tc_dwc_g210_pci_हटाओ,
	.shutकरोwn = tc_dwc_g210_pci_shutकरोwn,
	.driver = अणु
		.pm = &tc_dwc_g210_pci_pm_ops
	पूर्ण,
पूर्ण;

module_pci_driver(tc_dwc_g210_pci_driver);

MODULE_AUTHOR("Joao Pinto <Joao.Pinto@synopsys.com>");
MODULE_DESCRIPTION("Synopsys Test Chip G210 PCI glue driver");
MODULE_LICENSE("Dual BSD/GPL");
