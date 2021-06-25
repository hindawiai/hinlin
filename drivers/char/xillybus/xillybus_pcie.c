<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/misc/xillybus_pcie.c
 *
 * Copyright 2011 Xillybus Ltd, http://xillybus.com
 *
 * Driver क्रम the Xillybus FPGA/host framework using PCI Express.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश "xillybus.h"

MODULE_DESCRIPTION("Xillybus driver for PCIe");
MODULE_AUTHOR("Eli Billauer, Xillybus Ltd.");
MODULE_VERSION("1.06");
MODULE_ALIAS("xillybus_pcie");
MODULE_LICENSE("GPL v2");

#घोषणा PCI_DEVICE_ID_XILLYBUS		0xebeb

#घोषणा PCI_VENDOR_ID_ACTEL		0x11aa
#घोषणा PCI_VENDOR_ID_LATTICE		0x1204

अटल स्थिर अक्षर xillyname[] = "xillybus_pcie";

अटल स्थिर काष्ठा pci_device_id xillyids[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_XILINX, PCI_DEVICE_ID_XILLYBUS)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ALTERA, PCI_DEVICE_ID_XILLYBUS)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ACTEL, PCI_DEVICE_ID_XILLYBUS)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LATTICE, PCI_DEVICE_ID_XILLYBUS)पूर्ण,
	अणु /* End: all zeroes */ पूर्ण
पूर्ण;

अटल पूर्णांक xilly_pci_direction(पूर्णांक direction)
अणु
	चयन (direction) अणु
	हाल DMA_TO_DEVICE:
		वापस PCI_DMA_TODEVICE;
	हाल DMA_FROM_DEVICE:
		वापस PCI_DMA_FROMDEVICE;
	शेष:
		वापस PCI_DMA_BIसूचीECTIONAL;
	पूर्ण
पूर्ण

अटल व्योम xilly_dma_sync_single_क्रम_cpu_pci(काष्ठा xilly_endpoपूर्णांक *ep,
					      dma_addr_t dma_handle,
					      माप_प्रकार size,
					      पूर्णांक direction)
अणु
	pci_dma_sync_single_क्रम_cpu(ep->pdev,
				    dma_handle,
				    size,
				    xilly_pci_direction(direction));
पूर्ण

अटल व्योम xilly_dma_sync_single_क्रम_device_pci(काष्ठा xilly_endpoपूर्णांक *ep,
						 dma_addr_t dma_handle,
						 माप_प्रकार size,
						 पूर्णांक direction)
अणु
	pci_dma_sync_single_क्रम_device(ep->pdev,
				       dma_handle,
				       size,
				       xilly_pci_direction(direction));
पूर्ण

अटल व्योम xilly_pci_unmap(व्योम *ptr)
अणु
	काष्ठा xilly_mapping *data = ptr;

	pci_unmap_single(data->device, data->dma_addr,
			 data->size, data->direction);

	kमुक्त(ptr);
पूर्ण

/*
 * Map either through the PCI DMA mapper or the non_PCI one. Behind the
 * scenes exactly the same functions are called with the same parameters,
 * but that can change.
 */

अटल पूर्णांक xilly_map_single_pci(काष्ठा xilly_endpoपूर्णांक *ep,
				व्योम *ptr,
				माप_प्रकार size,
				पूर्णांक direction,
				dma_addr_t *ret_dma_handle
	)
अणु
	पूर्णांक pci_direction;
	dma_addr_t addr;
	काष्ठा xilly_mapping *this;

	this = kzalloc(माप(*this), GFP_KERNEL);
	अगर (!this)
		वापस -ENOMEM;

	pci_direction = xilly_pci_direction(direction);

	addr = pci_map_single(ep->pdev, ptr, size, pci_direction);

	अगर (pci_dma_mapping_error(ep->pdev, addr)) अणु
		kमुक्त(this);
		वापस -ENODEV;
	पूर्ण

	this->device = ep->pdev;
	this->dma_addr = addr;
	this->size = size;
	this->direction = pci_direction;

	*ret_dma_handle = addr;

	वापस devm_add_action_or_reset(ep->dev, xilly_pci_unmap, this);
पूर्ण

अटल काष्ठा xilly_endpoपूर्णांक_hardware pci_hw = अणु
	.owner = THIS_MODULE,
	.hw_sync_sgl_क्रम_cpu = xilly_dma_sync_single_क्रम_cpu_pci,
	.hw_sync_sgl_क्रम_device = xilly_dma_sync_single_क्रम_device_pci,
	.map_single = xilly_map_single_pci,
पूर्ण;

अटल पूर्णांक xilly_probe(काष्ठा pci_dev *pdev,
		       स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक;
	पूर्णांक rc;

	endpoपूर्णांक = xillybus_init_endpoपूर्णांक(pdev, &pdev->dev, &pci_hw);

	अगर (!endpoपूर्णांक)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, endpoपूर्णांक);

	rc = pcim_enable_device(pdev);
	अगर (rc) अणु
		dev_err(endpoपूर्णांक->dev,
			"pcim_enable_device() failed. Aborting.\n");
		वापस rc;
	पूर्ण

	/* L0s has caused packet drops. No घातer saving, thank you. */

	pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S);

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(endpoपूर्णांक->dev,
			"Incorrect BAR configuration. Aborting.\n");
		वापस -ENODEV;
	पूर्ण

	rc = pcim_iomap_regions(pdev, 0x01, xillyname);
	अगर (rc) अणु
		dev_err(endpoपूर्णांक->dev,
			"pcim_iomap_regions() failed. Aborting.\n");
		वापस rc;
	पूर्ण

	endpoपूर्णांक->रेजिस्टरs = pcim_iomap_table(pdev)[0];

	pci_set_master(pdev);

	/* Set up a single MSI पूर्णांकerrupt */
	अगर (pci_enable_msi(pdev)) अणु
		dev_err(endpoपूर्णांक->dev,
			"Failed to enable MSI interrupts. Aborting.\n");
		वापस -ENODEV;
	पूर्ण
	rc = devm_request_irq(&pdev->dev, pdev->irq, xillybus_isr, 0,
			      xillyname, endpoपूर्णांक);
	अगर (rc) अणु
		dev_err(endpoपूर्णांक->dev,
			"Failed to register MSI handler. Aborting.\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Some (old and buggy?) hardware drops 64-bit addressed PCIe packets,
	 * even when the PCIe driver claims that a 64-bit mask is OK. On the
	 * other hand, on some architectures, 64-bit addressing is mandatory.
	 * So go क्रम the 64-bit mask only when failing is the other option.
	 */

	अगर (!pci_set_dma_mask(pdev, DMA_BIT_MASK(32))) अणु
		endpoपूर्णांक->dma_using_dac = 0;
	पूर्ण अन्यथा अगर (!pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) अणु
		endpoपूर्णांक->dma_using_dac = 1;
	पूर्ण अन्यथा अणु
		dev_err(endpoपूर्णांक->dev, "Failed to set DMA mask. Aborting.\n");
		वापस -ENODEV;
	पूर्ण

	वापस xillybus_endpoपूर्णांक_discovery(endpoपूर्णांक);
पूर्ण

अटल व्योम xilly_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक = pci_get_drvdata(pdev);

	xillybus_endpoपूर्णांक_हटाओ(endpoपूर्णांक);
पूर्ण

MODULE_DEVICE_TABLE(pci, xillyids);

अटल काष्ठा pci_driver xillybus_driver = अणु
	.name = xillyname,
	.id_table = xillyids,
	.probe = xilly_probe,
	.हटाओ = xilly_हटाओ,
पूर्ण;

module_pci_driver(xillybus_driver);
