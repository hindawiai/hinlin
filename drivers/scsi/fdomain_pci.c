<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश "fdomain.h"

अटल पूर्णांक fकरोमुख्य_pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *d)
अणु
	पूर्णांक err;
	काष्ठा Scsi_Host *sh;

	err = pci_enable_device(pdev);
	अगर (err)
		जाओ fail;

	err = pci_request_regions(pdev, "fdomain_pci");
	अगर (err)
		जाओ disable_device;

	err = -ENODEV;
	अगर (pci_resource_len(pdev, 0) == 0)
		जाओ release_region;

	sh = fकरोमुख्य_create(pci_resource_start(pdev, 0), pdev->irq, 7,
			    &pdev->dev);
	अगर (!sh)
		जाओ release_region;

	pci_set_drvdata(pdev, sh);
	वापस 0;

release_region:
	pci_release_regions(pdev);
disable_device:
	pci_disable_device(pdev);
fail:
	वापस err;
पूर्ण

अटल व्योम fकरोमुख्य_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *sh = pci_get_drvdata(pdev);

	fकरोमुख्य_destroy(sh);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_device_id fकरोमुख्य_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_FD, PCI_DEVICE_ID_FD_36C70) पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, fकरोमुख्य_pci_table);

अटल काष्ठा pci_driver fकरोमुख्य_pci_driver = अणु
	.name		= "fdomain_pci",
	.id_table	= fकरोमुख्य_pci_table,
	.probe		= fकरोमुख्य_pci_probe,
	.हटाओ		= fकरोमुख्य_pci_हटाओ,
	.driver.pm	= FDOMAIN_PM_OPS,
पूर्ण;

module_pci_driver(fकरोमुख्य_pci_driver);

MODULE_AUTHOR("Ondrej Zary, Rickard E. Faith");
MODULE_DESCRIPTION("Future Domain TMC-3260 PCI SCSI driver");
MODULE_LICENSE("GPL");
