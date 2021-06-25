<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2007, Olof Johansson, PA Semi
 *
 * Based on arch/घातerpc/sysdev/mpic_u3msi.c:
 *
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

#समावेश <sysdev/mpic.h>

/* Allocate 16 पूर्णांकerrupts per device, to give an alignment of 16,
 * since that's the size of the grouping w.r.t. affinity. If someone
 * needs more than 32 MSI's down the road we'll have to rethink this,
 * but it should be OK क्रम now.
 */
#घोषणा ALLOC_CHUNK 16

#घोषणा PASEMI_MSI_ADDR 0xfc080000

/* A bit ugly, can we get this from the pci_dev somehow? */
अटल काष्ठा mpic *msi_mpic;


अटल व्योम mpic_pasemi_msi_mask_irq(काष्ठा irq_data *data)
अणु
	pr_debug("mpic_pasemi_msi_mask_irq %d\n", data->irq);
	pci_msi_mask_irq(data);
	mpic_mask_irq(data);
पूर्ण

अटल व्योम mpic_pasemi_msi_unmask_irq(काष्ठा irq_data *data)
अणु
	pr_debug("mpic_pasemi_msi_unmask_irq %d\n", data->irq);
	mpic_unmask_irq(data);
	pci_msi_unmask_irq(data);
पूर्ण

अटल काष्ठा irq_chip mpic_pasemi_msi_chip = अणु
	.irq_shutकरोwn		= mpic_pasemi_msi_mask_irq,
	.irq_mask		= mpic_pasemi_msi_mask_irq,
	.irq_unmask		= mpic_pasemi_msi_unmask_irq,
	.irq_eoi		= mpic_end_irq,
	.irq_set_type		= mpic_set_irq_type,
	.irq_set_affinity	= mpic_set_affinity,
	.name			= "PASEMI-MSI",
पूर्ण;

अटल व्योम pasemi_msi_tearकरोwn_msi_irqs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा msi_desc *entry;
	irq_hw_number_t hwirq;

	pr_debug("pasemi_msi_teardown_msi_irqs, pdev %p\n", pdev);

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		अगर (!entry->irq)
			जारी;

		hwirq = virq_to_hw(entry->irq);
		irq_set_msi_desc(entry->irq, शून्य);
		irq_dispose_mapping(entry->irq);
		msi_biपंचांगap_मुक्त_hwirqs(&msi_mpic->msi_biपंचांगap, hwirq, ALLOC_CHUNK);
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक pasemi_msi_setup_msi_irqs(काष्ठा pci_dev *pdev, पूर्णांक nvec, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक virq;
	काष्ठा msi_desc *entry;
	काष्ठा msi_msg msg;
	पूर्णांक hwirq;

	अगर (type == PCI_CAP_ID_MSIX)
		pr_debug("pasemi_msi: MSI-X untested, trying anyway\n");
	pr_debug("pasemi_msi_setup_msi_irqs, pdev %p nvec %d type %d\n",
		 pdev, nvec, type);

	msg.address_hi = 0;
	msg.address_lo = PASEMI_MSI_ADDR;

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		/* Allocate 16 पूर्णांकerrupts क्रम now, since that's the grouping क्रम
		 * affinity. This can be changed later अगर it turns out 32 is too
		 * few MSIs क्रम someone, but restrictions will apply to how the
		 * sources can be changed independently.
		 */
		hwirq = msi_biपंचांगap_alloc_hwirqs(&msi_mpic->msi_biपंचांगap,
						ALLOC_CHUNK);
		अगर (hwirq < 0) अणु
			pr_debug("pasemi_msi: failed allocating hwirq\n");
			वापस hwirq;
		पूर्ण

		virq = irq_create_mapping(msi_mpic->irqhost, hwirq);
		अगर (!virq) अणु
			pr_debug("pasemi_msi: failed mapping hwirq 0x%x\n",
				  hwirq);
			msi_biपंचांगap_मुक्त_hwirqs(&msi_mpic->msi_biपंचांगap, hwirq,
					       ALLOC_CHUNK);
			वापस -ENOSPC;
		पूर्ण

		/* Vector on MSI is really an offset, the hardware adds
		 * it to the value written at the magic address. So set
		 * it to 0 to reमुख्य sane.
		 */
		mpic_set_vector(virq, 0);

		irq_set_msi_desc(virq, entry);
		irq_set_chip(virq, &mpic_pasemi_msi_chip);
		irq_set_irq_type(virq, IRQ_TYPE_EDGE_RISING);

		pr_debug("pasemi_msi: allocated virq 0x%x (hw 0x%x) " \
			 "addr 0x%x\n", virq, hwirq, msg.address_lo);

		/* Likewise, the device ग_लिखोs [0...511] पूर्णांकo the target
		 * रेजिस्टर to generate MSI [512...1023]
		 */
		msg.data = hwirq-0x200;
		pci_ग_लिखो_msi_msg(virq, &msg);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mpic_pasemi_msi_init(काष्ठा mpic *mpic)
अणु
	पूर्णांक rc;
	काष्ठा pci_controller *phb;
	काष्ठा device_node *of_node;

	of_node = irq_करोमुख्य_get_of_node(mpic->irqhost);
	अगर (!of_node ||
	    !of_device_is_compatible(of_node,
				     "pasemi,pwrficient-openpic"))
		वापस -ENODEV;

	rc = mpic_msi_init_allocator(mpic);
	अगर (rc) अणु
		pr_debug("pasemi_msi: Error allocating bitmap!\n");
		वापस rc;
	पूर्ण

	pr_debug("pasemi_msi: Registering PA Semi MPIC MSI callbacks\n");

	msi_mpic = mpic;
	list_क्रम_each_entry(phb, &hose_list, list_node) अणु
		WARN_ON(phb->controller_ops.setup_msi_irqs);
		phb->controller_ops.setup_msi_irqs = pasemi_msi_setup_msi_irqs;
		phb->controller_ops.tearकरोwn_msi_irqs = pasemi_msi_tearकरोwn_msi_irqs;
	पूर्ण

	वापस 0;
पूर्ण
