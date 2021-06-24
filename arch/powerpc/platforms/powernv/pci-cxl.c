<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014-2016 IBM Corp.
 */

#समावेश <linux/module.h>
#समावेश <यंत्र/pnv-pci.h>
#समावेश <यंत्र/opal.h>

#समावेश "pci.h"

पूर्णांक pnv_phb_to_cxl_mode(काष्ठा pci_dev *dev, uपूर्णांक64_t mode)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	काष्ठा pnv_ioda_pe *pe;
	पूर्णांक rc;

	pe = pnv_ioda_get_pe(dev);
	अगर (!pe)
		वापस -ENODEV;

	pe_info(pe, "Switching PHB to CXL\n");

	rc = opal_pci_set_phb_cxl_mode(phb->opal_id, mode, pe->pe_number);
	अगर (rc == OPAL_UNSUPPORTED)
		dev_err(&dev->dev, "Required cxl mode not supported by firmware - update skiboot\n");
	अन्यथा अगर (rc)
		dev_err(&dev->dev, "opal_pci_set_phb_cxl_mode failed: %i\n", rc);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(pnv_phb_to_cxl_mode);

/* Find PHB क्रम cxl dev and allocate MSI hwirqs?
 * Returns the असलolute hardware IRQ number
 */
पूर्णांक pnv_cxl_alloc_hwirqs(काष्ठा pci_dev *dev, पूर्णांक num)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	पूर्णांक hwirq = msi_biपंचांगap_alloc_hwirqs(&phb->msi_bmp, num);

	अगर (hwirq < 0) अणु
		dev_warn(&dev->dev, "Failed to find a free MSI\n");
		वापस -ENOSPC;
	पूर्ण

	वापस phb->msi_base + hwirq;
पूर्ण
EXPORT_SYMBOL(pnv_cxl_alloc_hwirqs);

व्योम pnv_cxl_release_hwirqs(काष्ठा pci_dev *dev, पूर्णांक hwirq, पूर्णांक num)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;

	msi_biपंचांगap_मुक्त_hwirqs(&phb->msi_bmp, hwirq - phb->msi_base, num);
पूर्ण
EXPORT_SYMBOL(pnv_cxl_release_hwirqs);

व्योम pnv_cxl_release_hwirq_ranges(काष्ठा cxl_irq_ranges *irqs,
				  काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	पूर्णांक i, hwirq;

	क्रम (i = 1; i < CXL_IRQ_RANGES; i++) अणु
		अगर (!irqs->range[i])
			जारी;
		pr_devel("cxl release irq range 0x%x: offset: 0x%lx  limit: %ld\n",
			 i, irqs->offset[i],
			 irqs->range[i]);
		hwirq = irqs->offset[i] - phb->msi_base;
		msi_biपंचांगap_मुक्त_hwirqs(&phb->msi_bmp, hwirq,
				       irqs->range[i]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pnv_cxl_release_hwirq_ranges);

पूर्णांक pnv_cxl_alloc_hwirq_ranges(काष्ठा cxl_irq_ranges *irqs,
			       काष्ठा pci_dev *dev, पूर्णांक num)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	पूर्णांक i, hwirq, try;

	स_रखो(irqs, 0, माप(काष्ठा cxl_irq_ranges));

	/* 0 is reserved क्रम the multiplexed PSL DSI पूर्णांकerrupt */
	क्रम (i = 1; i < CXL_IRQ_RANGES && num; i++) अणु
		try = num;
		जबतक (try) अणु
			hwirq = msi_biपंचांगap_alloc_hwirqs(&phb->msi_bmp, try);
			अगर (hwirq >= 0)
				अवरोध;
			try /= 2;
		पूर्ण
		अगर (!try)
			जाओ fail;

		irqs->offset[i] = phb->msi_base + hwirq;
		irqs->range[i] = try;
		pr_devel("cxl alloc irq range 0x%x: offset: 0x%lx  limit: %li\n",
			 i, irqs->offset[i], irqs->range[i]);
		num -= try;
	पूर्ण
	अगर (num)
		जाओ fail;

	वापस 0;
fail:
	pnv_cxl_release_hwirq_ranges(irqs, dev);
	वापस -ENOSPC;
पूर्ण
EXPORT_SYMBOL(pnv_cxl_alloc_hwirq_ranges);

पूर्णांक pnv_cxl_get_irq_count(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;

	वापस phb->msi_bmp.irq_count;
पूर्ण
EXPORT_SYMBOL(pnv_cxl_get_irq_count);

पूर्णांक pnv_cxl_ioda_msi_setup(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक hwirq,
			   अचिन्हित पूर्णांक virq)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	अचिन्हित पूर्णांक xive_num = hwirq - phb->msi_base;
	काष्ठा pnv_ioda_pe *pe;
	पूर्णांक rc;

	अगर (!(pe = pnv_ioda_get_pe(dev)))
		वापस -ENODEV;

	/* Assign XIVE to PE */
	rc = opal_pci_set_xive_pe(phb->opal_id, pe->pe_number, xive_num);
	अगर (rc) अणु
		pe_warn(pe, "%s: OPAL error %d setting msi_base 0x%x "
			"hwirq 0x%x XIVE 0x%x PE\n",
			pci_name(dev), rc, phb->msi_base, hwirq, xive_num);
		वापस -EIO;
	पूर्ण
	pnv_set_msi_irq_chip(phb, virq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pnv_cxl_ioda_msi_setup);
