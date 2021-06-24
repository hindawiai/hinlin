<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-footbridge/ebsa285-pci.c
 *
 * PCI bios-type initialisation क्रम PCI machines
 *
 * Bits taken from various places.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/mach-types.h>

अटल पूर्णांक irqmap_ebsa285[] = अणु IRQ_IN3, IRQ_IN1, IRQ_IN0, IRQ_PCI पूर्ण;

अटल पूर्णांक ebsa285_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (dev->venकरोr == PCI_VENDOR_ID_CONTAQ &&
	    dev->device == PCI_DEVICE_ID_CONTAQ_82C693)
		चयन (PCI_FUNC(dev->devfn)) अणु
		हाल 1:	वापस 14;
		हाल 2:	वापस 15;
		हाल 3:	वापस 12;
		पूर्ण

	वापस irqmap_ebsa285[(slot + pin) & 3];
पूर्ण

अटल काष्ठा hw_pci ebsa285_pci __initdata = अणु
	.map_irq		= ebsa285_map_irq,
	.nr_controllers		= 1,
	.ops			= &dc21285_ops,
	.setup			= dc21285_setup,
	.preinit		= dc21285_preinit,
	.postinit		= dc21285_postinit,
पूर्ण;

अटल पूर्णांक __init ebsa285_init_pci(व्योम)
अणु
	अगर (machine_is_ebsa285())
		pci_common_init(&ebsa285_pci);
	वापस 0;
पूर्ण

subsys_initcall(ebsa285_init_pci);
