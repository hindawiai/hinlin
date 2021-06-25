<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Minimalist driver क्रम a generic PCI-to-EISA bridge.
 *
 * (C) 2003 Marc Zyngier <maz@wild-wind.fr.eu.org>
 *
 * Ivan Kokshaysky <ink@jurassic.park.msu.ru> :
 * Generalisation from i82375 to PCI_CLASS_BRIDGE_EISA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/eisa.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

/* There is only *one* pci_eisa device per machine, right ? */
अटल काष्ठा eisa_root_device pci_eisa_root;

अटल पूर्णांक __init pci_eisa_init(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc, i;
	काष्ठा resource *res, *bus_res = शून्य;

	अगर ((rc = pci_enable_device (pdev))) अणु
		dev_err(&pdev->dev, "Could not enable device\n");
		वापस rc;
	पूर्ण

	/*
	 * The Intel 82375 PCI-EISA bridge is a subtractive-decode PCI
	 * device, so the resources available on EISA are the same as those
	 * available on the 82375 bus.  This works the same as a PCI-PCI
	 * bridge in subtractive-decode mode (see pci_पढ़ो_bridge_bases()).
	 * We assume other PCI-EISA bridges are similar.
	 *
	 * eisa_root_रेजिस्टर() can only deal with a single io port resource,
	*  so we use the first valid io port resource.
	 */
	pci_bus_क्रम_each_resource(pdev->bus, res, i)
		अगर (res && (res->flags & IORESOURCE_IO)) अणु
			bus_res = res;
			अवरोध;
		पूर्ण

	अगर (!bus_res) अणु
		dev_err(&pdev->dev, "No resources available\n");
		वापस -1;
	पूर्ण

	pci_eisa_root.dev		= &pdev->dev;
	pci_eisa_root.res		= bus_res;
	pci_eisa_root.bus_base_addr	= bus_res->start;
	pci_eisa_root.slots		= EISA_MAX_SLOTS;
	pci_eisa_root.dma_mask		= pdev->dma_mask;
	dev_set_drvdata(pci_eisa_root.dev, &pci_eisa_root);

	अगर (eisa_root_रेजिस्टर (&pci_eisa_root)) अणु
		dev_err(&pdev->dev, "Could not register EISA root\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We have to call pci_eisa_init_early() beक्रमe pnpacpi_init()/isapnp_init().
 *   Otherwise pnp resource will get enabled early and could prevent eisa
 *   to be initialized.
 * Also need to make sure pci_eisa_init_early() is called after
 * x86/pci_subsys_init().
 * So need to use subsys_initcall_sync with it.
 */
अटल पूर्णांक __init pci_eisa_init_early(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;
	पूर्णांक ret;

	क्रम_each_pci_dev(dev)
		अगर ((dev->class >> 8) == PCI_CLASS_BRIDGE_EISA) अणु
			ret = pci_eisa_init(dev);
			अगर (ret)
				वापस ret;
		पूर्ण

	वापस 0;
पूर्ण
subsys_initcall_sync(pci_eisa_init_early);
