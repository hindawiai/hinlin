<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI IRQ handling code
 *
 * Copyright (c) 2008 James Bottomley <James.Bottomley@HansenPartnership.com>
 * Copyright (C) 2017 Christoph Hellwig.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>

/**
 * pci_request_irq - allocate an पूर्णांकerrupt line क्रम a PCI device
 * @dev:	PCI device to operate on
 * @nr:		device-relative पूर्णांकerrupt vector index (0-based).
 * @handler:	Function to be called when the IRQ occurs.
 *		Primary handler क्रम thपढ़ोed पूर्णांकerrupts.
 *		If शून्य and thपढ़ो_fn != शून्य the शेष primary handler is
 *		installed.
 * @thपढ़ो_fn:	Function called from the IRQ handler thपढ़ो
 *		If शून्य, no IRQ thपढ़ो is created
 * @dev_id:	Cookie passed back to the handler function
 * @fmt:	Prपूर्णांकf-like क्रमmat string naming the handler
 *
 * This call allocates पूर्णांकerrupt resources and enables the पूर्णांकerrupt line and
 * IRQ handling. From the poपूर्णांक this call is made @handler and @thपढ़ो_fn may
 * be invoked.  All पूर्णांकerrupts requested using this function might be shared.
 *
 * @dev_id must not be शून्य and must be globally unique.
 */
पूर्णांक pci_request_irq(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक nr, irq_handler_t handler,
		irq_handler_t thपढ़ो_fn, व्योम *dev_id, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;
	अक्षर *devname;
	अचिन्हित दीर्घ irqflags = IRQF_SHARED;

	अगर (!handler)
		irqflags |= IRQF_ONESHOT;

	बहु_शुरू(ap, fmt);
	devname = kvaप्र_लिखो(GFP_KERNEL, fmt, ap);
	बहु_पूर्ण(ap);

	ret = request_thपढ़ोed_irq(pci_irq_vector(dev, nr), handler, thपढ़ो_fn,
				   irqflags, devname, dev_id);
	अगर (ret)
		kमुक्त(devname);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pci_request_irq);

/**
 * pci_मुक्त_irq - मुक्त an पूर्णांकerrupt allocated with pci_request_irq
 * @dev:	PCI device to operate on
 * @nr:		device-relative पूर्णांकerrupt vector index (0-based).
 * @dev_id:	Device identity to मुक्त
 *
 * Remove an पूर्णांकerrupt handler. The handler is हटाओd and अगर the पूर्णांकerrupt
 * line is no दीर्घer in use by any driver it is disabled.  The caller must
 * ensure the पूर्णांकerrupt is disabled on the device beक्रमe calling this function.
 * The function करोes not वापस until any executing पूर्णांकerrupts क्रम this IRQ
 * have completed.
 *
 * This function must not be called from पूर्णांकerrupt context.
 */
व्योम pci_मुक्त_irq(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक nr, व्योम *dev_id)
अणु
	kमुक्त(मुक्त_irq(pci_irq_vector(dev, nr), dev_id));
पूर्ण
EXPORT_SYMBOL(pci_मुक्त_irq);
