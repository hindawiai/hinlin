<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2006, Segher Boessenkool, IBM Corporation.
 * Copyright 2006-2007, Michael Ellerman, IBM Corporation.
 */

#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/msi_biपंचांगap.h>

#समावेश "mpic.h"

/* A bit ugly, can we get this from the pci_dev somehow? */
अटल काष्ठा mpic *msi_mpic;

अटल व्योम mpic_u3msi_mask_irq(काष्ठा irq_data *data)
अणु
	pci_msi_mask_irq(data);
	mpic_mask_irq(data);
पूर्ण

अटल व्योम mpic_u3msi_unmask_irq(काष्ठा irq_data *data)
अणु
	mpic_unmask_irq(data);
	pci_msi_unmask_irq(data);
पूर्ण

अटल काष्ठा irq_chip mpic_u3msi_chip = अणु
	.irq_shutकरोwn		= mpic_u3msi_mask_irq,
	.irq_mask		= mpic_u3msi_mask_irq,
	.irq_unmask		= mpic_u3msi_unmask_irq,
	.irq_eoi		= mpic_end_irq,
	.irq_set_type		= mpic_set_irq_type,
	.irq_set_affinity	= mpic_set_affinity,
	.name			= "MPIC-U3MSI",
पूर्ण;

अटल u64 पढ़ो_ht_magic_addr(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक pos)
अणु
	u8 flags;
	u32 पंचांगp;
	u64 addr;

	pci_पढ़ो_config_byte(pdev, pos + HT_MSI_FLAGS, &flags);

	अगर (flags & HT_MSI_FLAGS_FIXED)
		वापस HT_MSI_FIXED_ADDR;

	pci_पढ़ो_config_dword(pdev, pos + HT_MSI_ADDR_LO, &पंचांगp);
	addr = पंचांगp & HT_MSI_ADDR_LO_MASK;
	pci_पढ़ो_config_dword(pdev, pos + HT_MSI_ADDR_HI, &पंचांगp);
	addr = addr | ((u64)पंचांगp << 32);

	वापस addr;
पूर्ण

अटल u64 find_ht_magic_addr(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक hwirq)
अणु
	काष्ठा pci_bus *bus;
	अचिन्हित पूर्णांक pos;

	क्रम (bus = pdev->bus; bus && bus->self; bus = bus->parent) अणु
		pos = pci_find_ht_capability(bus->self, HT_CAPTYPE_MSI_MAPPING);
		अगर (pos)
			वापस पढ़ो_ht_magic_addr(bus->self, pos);
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 find_u4_magic_addr(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक hwirq)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(pdev->bus);

	/* U4 PCIe MSIs need to ग_लिखो to the special रेजिस्टर in
	 * the bridge that generates पूर्णांकerrupts. There should be
	 * theorically a रेजिस्टर at 0xf8005000 where you just ग_लिखो
	 * the MSI number and that triggers the right पूर्णांकerrupt, but
	 * unक्रमtunately, this is busted in HW, the bridge endian swaps
	 * the value and hits the wrong nibble in the रेजिस्टर.
	 *
	 * So instead we use another रेजिस्टर set which is used normally
	 * क्रम converting HT पूर्णांकerrupts to MPIC पूर्णांकerrupts, which decodes
	 * the पूर्णांकerrupt number as part of the low address bits
	 *
	 * This will not work अगर we ever use more than one legacy MSI in
	 * a block but we never करो. For one MSI or multiple MSI-X where
	 * each पूर्णांकerrupt address can be specअगरied separately, it works
	 * just fine.
	 */
	अगर (of_device_is_compatible(hose->dn, "u4-pcie") ||
	    of_device_is_compatible(hose->dn, "U4-pcie"))
		वापस 0xf8004000 | (hwirq << 4);

	वापस 0;
पूर्ण

अटल व्योम u3msi_tearकरोwn_msi_irqs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा msi_desc *entry;
	irq_hw_number_t hwirq;

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		अगर (!entry->irq)
			जारी;

		hwirq = virq_to_hw(entry->irq);
		irq_set_msi_desc(entry->irq, शून्य);
		irq_dispose_mapping(entry->irq);
		msi_biपंचांगap_मुक्त_hwirqs(&msi_mpic->msi_biपंचांगap, hwirq, 1);
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक u3msi_setup_msi_irqs(काष्ठा pci_dev *pdev, पूर्णांक nvec, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक virq;
	काष्ठा msi_desc *entry;
	काष्ठा msi_msg msg;
	u64 addr;
	पूर्णांक hwirq;

	अगर (type == PCI_CAP_ID_MSIX)
		pr_debug("u3msi: MSI-X untested, trying anyway.\n");

	/* If we can't find a magic address then MSI ain't gonna work */
	अगर (find_ht_magic_addr(pdev, 0) == 0 &&
	    find_u4_magic_addr(pdev, 0) == 0) अणु
		pr_debug("u3msi: no magic address found for %s\n",
			 pci_name(pdev));
		वापस -ENXIO;
	पूर्ण

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		hwirq = msi_biपंचांगap_alloc_hwirqs(&msi_mpic->msi_biपंचांगap, 1);
		अगर (hwirq < 0) अणु
			pr_debug("u3msi: failed allocating hwirq\n");
			वापस hwirq;
		पूर्ण

		addr = find_ht_magic_addr(pdev, hwirq);
		अगर (addr == 0)
			addr = find_u4_magic_addr(pdev, hwirq);
		msg.address_lo = addr & 0xFFFFFFFF;
		msg.address_hi = addr >> 32;

		virq = irq_create_mapping(msi_mpic->irqhost, hwirq);
		अगर (!virq) अणु
			pr_debug("u3msi: failed mapping hwirq 0x%x\n", hwirq);
			msi_biपंचांगap_मुक्त_hwirqs(&msi_mpic->msi_biपंचांगap, hwirq, 1);
			वापस -ENOSPC;
		पूर्ण

		irq_set_msi_desc(virq, entry);
		irq_set_chip(virq, &mpic_u3msi_chip);
		irq_set_irq_type(virq, IRQ_TYPE_EDGE_RISING);

		pr_debug("u3msi: allocated virq 0x%x (hw 0x%x) addr 0x%lx\n",
			  virq, hwirq, (अचिन्हित दीर्घ)addr);

		prपूर्णांकk("u3msi: allocated virq 0x%x (hw 0x%x) addr 0x%lx\n",
			  virq, hwirq, (अचिन्हित दीर्घ)addr);
		msg.data = hwirq;
		pci_ग_लिखो_msi_msg(virq, &msg);

		hwirq++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mpic_u3msi_init(काष्ठा mpic *mpic)
अणु
	पूर्णांक rc;
	काष्ठा pci_controller *phb;

	rc = mpic_msi_init_allocator(mpic);
	अगर (rc) अणु
		pr_debug("u3msi: Error allocating bitmap!\n");
		वापस rc;
	पूर्ण

	pr_debug("u3msi: Registering MPIC U3 MSI callbacks.\n");

	BUG_ON(msi_mpic);
	msi_mpic = mpic;

	list_क्रम_each_entry(phb, &hose_list, list_node) अणु
		WARN_ON(phb->controller_ops.setup_msi_irqs);
		phb->controller_ops.setup_msi_irqs = u3msi_setup_msi_irqs;
		phb->controller_ops.tearकरोwn_msi_irqs = u3msi_tearकरोwn_msi_irqs;
	पूर्ण

	वापस 0;
पूर्ण
