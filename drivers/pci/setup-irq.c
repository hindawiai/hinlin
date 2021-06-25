<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support routines क्रम initializing a PCI subप्रणाली
 *
 * Extruded from code written by
 *      Dave Rusling (david.rusling@reo.mts.dec.com)
 *      David Mosberger (davidm@cs.arizona.edu)
 *	David Miller (davem@redhat.com)
 */


#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/cache.h>
#समावेश "pci.h"

व्योम pci_assign_irq(काष्ठा pci_dev *dev)
अणु
	u8 pin;
	u8 slot = -1;
	पूर्णांक irq = 0;
	काष्ठा pci_host_bridge *hbrg = pci_find_host_bridge(dev->bus);

	अगर (!(hbrg->map_irq)) अणु
		pci_dbg(dev, "runtime IRQ mapping not provided by arch\n");
		वापस;
	पूर्ण

	/* If this device is not on the primary bus, we need to figure out
	   which पूर्णांकerrupt pin it will come in on.   We know which slot it
	   will come in on 'cos that slot is where the bridge is.   Each
	   समय the पूर्णांकerrupt line passes through a PCI-PCI bridge we must
	   apply the swizzle function.  */

	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	/* Cope with illegal. */
	अगर (pin > 4)
		pin = 1;

	अगर (pin) अणु
		/* Follow the chain of bridges, swizzling as we go.  */
		अगर (hbrg->swizzle_irq)
			slot = (*(hbrg->swizzle_irq))(dev, &pin);

		/*
		 * If a swizzling function is not used map_irq must
		 * ignore slot
		 */
		irq = (*(hbrg->map_irq))(dev, slot, pin);
		अगर (irq == -1)
			irq = 0;
	पूर्ण
	dev->irq = irq;

	pci_dbg(dev, "assign IRQ: got %d\n", dev->irq);

	/* Always tell the device, so the driver knows what is
	   the real IRQ to use; the device करोes not use it. */
	pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, irq);
पूर्ण
