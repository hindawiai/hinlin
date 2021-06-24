<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/pci.h>
#समावेश <misc/cxl.h>
#समावेश "cxl.h"

अटल पूर्णांक cxl_pci_probe_mode(काष्ठा pci_bus *bus)
अणु
	वापस PCI_PROBE_NORMAL;
पूर्ण

अटल पूर्णांक cxl_setup_msi_irqs(काष्ठा pci_dev *pdev, पूर्णांक nvec, पूर्णांक type)
अणु
	वापस -ENODEV;
पूर्ण

अटल व्योम cxl_tearकरोwn_msi_irqs(काष्ठा pci_dev *pdev)
अणु
	/*
	 * MSI should never be set but need still need to provide this call
	 * back.
	 */
पूर्ण

अटल bool cxl_pci_enable_device_hook(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *phb;
	काष्ठा cxl_afu *afu;
	काष्ठा cxl_context *ctx;

	phb = pci_bus_to_host(dev->bus);
	afu = (काष्ठा cxl_afu *)phb->निजी_data;

	अगर (!cxl_ops->link_ok(afu->adapter, afu)) अणु
		dev_warn(&dev->dev, "%s: Device link is down, refusing to enable AFU\n", __func__);
		वापस false;
	पूर्ण

	dev->dev.archdata.dma_offset = PAGE_OFFSET;

	/*
	 * Allocate a context to करो cxl things too.  If we eventually करो real
	 * DMA ops, we'll need a शेष context to attach them to
	 */
	ctx = cxl_dev_context_init(dev);
	अगर (IS_ERR(ctx))
		वापस false;
	dev->dev.archdata.cxl_ctx = ctx;

	वापस (cxl_ops->afu_check_and_enable(afu) == 0);
पूर्ण

अटल व्योम cxl_pci_disable_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा cxl_context *ctx = cxl_get_context(dev);

	अगर (ctx) अणु
		अगर (ctx->status == STARTED) अणु
			dev_err(&dev->dev, "Default context started\n");
			वापस;
		पूर्ण
		dev->dev.archdata.cxl_ctx = शून्य;
		cxl_release_context(ctx);
	पूर्ण
पूर्ण

अटल resource_माप_प्रकार cxl_pci_winकरोw_alignment(काष्ठा pci_bus *bus,
						अचिन्हित दीर्घ type)
अणु
	वापस 1;
पूर्ण

अटल व्योम cxl_pci_reset_secondary_bus(काष्ठा pci_dev *dev)
अणु
	/* Should we करो an AFU reset here ? */
पूर्ण

अटल पूर्णांक cxl_pcie_cfg_record(u8 bus, u8 devfn)
अणु
	वापस (bus << 8) + devfn;
पूर्ण

अटल अंतरभूत काष्ठा cxl_afu *pci_bus_to_afu(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *phb = bus ? pci_bus_to_host(bus) : शून्य;

	वापस phb ? phb->निजी_data : शून्य;
पूर्ण

अटल व्योम cxl_afu_configured_put(काष्ठा cxl_afu *afu)
अणु
	atomic_dec_अगर_positive(&afu->configured_state);
पूर्ण

अटल bool cxl_afu_configured_get(काष्ठा cxl_afu *afu)
अणु
	वापस atomic_inc_unless_negative(&afu->configured_state);
पूर्ण

अटल अंतरभूत पूर्णांक cxl_pcie_config_info(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				       काष्ठा cxl_afu *afu, पूर्णांक *_record)
अणु
	पूर्णांक record;

	record = cxl_pcie_cfg_record(bus->number, devfn);
	अगर (record > afu->crs_num)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	*_record = record;
	वापस 0;
पूर्ण

अटल पूर्णांक cxl_pcie_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
	पूर्णांक rc, record;
	काष्ठा cxl_afu *afu;
	u8 val8;
	u16 val16;
	u32 val32;

	afu = pci_bus_to_afu(bus);
	/* Grab a पढ़ोer lock on afu. */
	अगर (afu == शून्य || !cxl_afu_configured_get(afu))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	rc = cxl_pcie_config_info(bus, devfn, afu, &record);
	अगर (rc)
		जाओ out;

	चयन (len) अणु
	हाल 1:
		rc = cxl_ops->afu_cr_पढ़ो8(afu, record, offset,	&val8);
		*val = val8;
		अवरोध;
	हाल 2:
		rc = cxl_ops->afu_cr_पढ़ो16(afu, record, offset, &val16);
		*val = val16;
		अवरोध;
	हाल 4:
		rc = cxl_ops->afu_cr_पढ़ो32(afu, record, offset, &val32);
		*val = val32;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

out:
	cxl_afu_configured_put(afu);
	वापस rc ? PCIBIOS_DEVICE_NOT_FOUND : 0;
पूर्ण

अटल पूर्णांक cxl_pcie_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				 पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	पूर्णांक rc, record;
	काष्ठा cxl_afu *afu;

	afu = pci_bus_to_afu(bus);
	/* Grab a पढ़ोer lock on afu. */
	अगर (afu == शून्य || !cxl_afu_configured_get(afu))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	rc = cxl_pcie_config_info(bus, devfn, afu, &record);
	अगर (rc)
		जाओ out;

	चयन (len) अणु
	हाल 1:
		rc = cxl_ops->afu_cr_ग_लिखो8(afu, record, offset, val & 0xff);
		अवरोध;
	हाल 2:
		rc = cxl_ops->afu_cr_ग_लिखो16(afu, record, offset, val & 0xffff);
		अवरोध;
	हाल 4:
		rc = cxl_ops->afu_cr_ग_लिखो32(afu, record, offset, val);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

out:
	cxl_afu_configured_put(afu);
	वापस rc ? PCIBIOS_SET_FAILED : 0;
पूर्ण

अटल काष्ठा pci_ops cxl_pcie_pci_ops =
अणु
	.पढ़ो = cxl_pcie_पढ़ो_config,
	.ग_लिखो = cxl_pcie_ग_लिखो_config,
पूर्ण;


अटल काष्ठा pci_controller_ops cxl_pci_controller_ops =
अणु
	.probe_mode = cxl_pci_probe_mode,
	.enable_device_hook = cxl_pci_enable_device_hook,
	.disable_device = cxl_pci_disable_device,
	.release_device = cxl_pci_disable_device,
	.winकरोw_alignment = cxl_pci_winकरोw_alignment,
	.reset_secondary_bus = cxl_pci_reset_secondary_bus,
	.setup_msi_irqs = cxl_setup_msi_irqs,
	.tearकरोwn_msi_irqs = cxl_tearकरोwn_msi_irqs,
पूर्ण;

पूर्णांक cxl_pci_vphb_add(काष्ठा cxl_afu *afu)
अणु
	काष्ठा pci_controller *phb;
	काष्ठा device_node *vphb_dn;
	काष्ठा device *parent;

	/*
	 * If there are no AFU configuration records we won't have anything to
	 * expose under the vPHB, so skip creating one, वापसing success since
	 * this is still a valid हाल. This will also opt us out of EEH
	 * handling since we won't have anything special to करो अगर there are no
	 * kernel drivers attached to the vPHB, and EEH handling is not yet
	 * supported in the peer model.
	 */
	अगर (!afu->crs_num)
		वापस 0;

	/* The parent device is the adapter. Reuse the device node of
	 * the adapter.
	 * We करोn't seem to care what device node is used क्रम the vPHB,
	 * but tools such as lsvpd walk up the device parents looking
	 * क्रम a valid location code, so we might as well show devices
	 * attached to the adapter as being located on that adapter.
	 */
	parent = afu->adapter->dev.parent;
	vphb_dn = parent->of_node;

	/* Alloc and setup PHB data काष्ठाure */
	phb = pcibios_alloc_controller(vphb_dn);
	अगर (!phb)
		वापस -ENODEV;

	/* Setup parent in sysfs */
	phb->parent = parent;

	/* Setup the PHB using arch provided callback */
	phb->ops = &cxl_pcie_pci_ops;
	phb->cfg_addr = शून्य;
	phb->cfg_data = शून्य;
	phb->निजी_data = afu;
	phb->controller_ops = cxl_pci_controller_ops;

	/* Scan the bus */
	pcibios_scan_phb(phb);
	अगर (phb->bus == शून्य)
		वापस -ENXIO;

	/* Set release hook on root bus */
	pci_set_host_bridge_release(to_pci_host_bridge(phb->bus->bridge),
				    pcibios_मुक्त_controller_deferred,
				    (व्योम *) phb);

	/* Claim resources. This might need some rework as well depending
	 * whether we are करोing probe-only or not, like assigning unasचिन्हित
	 * resources etc...
	 */
	pcibios_claim_one_bus(phb->bus);

	/* Add probed PCI devices to the device model */
	pci_bus_add_devices(phb->bus);

	afu->phb = phb;

	वापस 0;
पूर्ण

व्योम cxl_pci_vphb_हटाओ(काष्ठा cxl_afu *afu)
अणु
	काष्ठा pci_controller *phb;

	/* If there is no configuration record we won't have one of these */
	अगर (!afu || !afu->phb)
		वापस;

	phb = afu->phb;
	afu->phb = शून्य;

	pci_हटाओ_root_bus(phb->bus);
	/*
	 * We करोn't free phb here - that's handled by
	 * pcibios_मुक्त_controller_deferred()
	 */
पूर्ण

bool cxl_pci_is_vphb_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *phb;

	phb = pci_bus_to_host(dev->bus);

	वापस (phb->ops == &cxl_pcie_pci_ops);
पूर्ण

काष्ठा cxl_afu *cxl_pci_to_afu(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *phb;

	phb = pci_bus_to_host(dev->bus);

	वापस (काष्ठा cxl_afu *)phb->निजी_data;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_pci_to_afu);

अचिन्हित पूर्णांक cxl_pci_to_cfg_record(काष्ठा pci_dev *dev)
अणु
	वापस cxl_pcie_cfg_record(dev->bus->number, dev->devfn);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_pci_to_cfg_record);
