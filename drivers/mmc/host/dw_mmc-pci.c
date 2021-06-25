<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Synopsys DesignWare Mulसमयdia Card PCI Interface driver
 *
 * Copyright (C) 2012 Vayavya Lअसल Pvt. Ltd.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश "dw_mmc.h"

#घोषणा PCI_BAR_NO 2
#घोषणा SYNOPSYS_DW_MCI_VENDOR_ID 0x700
#घोषणा SYNOPSYS_DW_MCI_DEVICE_ID 0x1107
/* Defining the Capabilities */
#घोषणा DW_MCI_CAPABILITIES (MMC_CAP_4_BIT_DATA | MMC_CAP_MMC_HIGHSPEED |\
				MMC_CAP_SD_HIGHSPEED | MMC_CAP_8_BIT_DATA |\
				MMC_CAP_SDIO_IRQ)

अटल काष्ठा dw_mci_board pci_board_data = अणु
	.caps				= DW_MCI_CAPABILITIES,
	.bus_hz				= 33 * 1000 * 1000,
	.detect_delay_ms		= 200,
	.fअगरo_depth			= 32,
पूर्ण;

अटल पूर्णांक dw_mci_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *entries)
अणु
	काष्ठा dw_mci *host;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	host = devm_kzalloc(&pdev->dev, माप(काष्ठा dw_mci), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	host->irq = pdev->irq;
	host->irq_flags = IRQF_SHARED;
	host->dev = &pdev->dev;
	host->pdata = &pci_board_data;

	ret = pcim_iomap_regions(pdev, 1 << PCI_BAR_NO, pci_name(pdev));
	अगर (ret)
		वापस ret;

	host->regs = pcim_iomap_table(pdev)[PCI_BAR_NO];

	pci_set_master(pdev);

	ret = dw_mci_probe(host);
	अगर (ret)
		वापस ret;

	pci_set_drvdata(pdev, host);

	वापस 0;
पूर्ण

अटल व्योम dw_mci_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा dw_mci *host = pci_get_drvdata(pdev);

	dw_mci_हटाओ(host);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dw_mci_pci_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(dw_mci_runसमय_suspend,
			   dw_mci_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा pci_device_id dw_mci_pci_id[] = अणु
	अणु PCI_DEVICE(SYNOPSYS_DW_MCI_VENDOR_ID, SYNOPSYS_DW_MCI_DEVICE_ID) पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dw_mci_pci_id);

अटल काष्ठा pci_driver dw_mci_pci_driver = अणु
	.name		= "dw_mmc_pci",
	.id_table	= dw_mci_pci_id,
	.probe		= dw_mci_pci_probe,
	.हटाओ		= dw_mci_pci_हटाओ,
	.driver		=	अणु
		.pm =   &dw_mci_pci_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(dw_mci_pci_driver);

MODULE_DESCRIPTION("DW Multimedia Card PCI Interface driver");
MODULE_AUTHOR("Shashidhar Hiremath <shashidharh@vayavyalabs.com>");
MODULE_LICENSE("GPL v2");
