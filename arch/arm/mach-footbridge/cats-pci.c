<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-footbridge/cats-pci.c
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

/* cats host-specअगरic stuff */
अटल पूर्णांक irqmap_cats[] = अणु IRQ_PCI, IRQ_IN0, IRQ_IN1, IRQ_IN3 पूर्ण;

अटल u8 cats_no_swizzle(काष्ठा pci_dev *dev, u8 *pin)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cats_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (dev->irq >= 255)
		वापस -1;	/* not a valid पूर्णांकerrupt. */

	अगर (dev->irq >= 128)
		वापस dev->irq & 0x1f;

	अगर (dev->irq >= 1 && dev->irq <= 4)
		वापस irqmap_cats[dev->irq - 1];

	अगर (dev->irq != 0)
		prपूर्णांकk("PCI: device %02x:%02x has unknown irq line %x\n",
		       dev->bus->number, dev->devfn, dev->irq);

	वापस -1;
पूर्ण

/*
 * why not the standard PCI swizzle?  करोes this prevent 4-port tulip
 * cards being used (ie, pci-pci bridge based cards)?
 */
अटल काष्ठा hw_pci cats_pci __initdata = अणु
	.swizzle		= cats_no_swizzle,
	.map_irq		= cats_map_irq,
	.nr_controllers		= 1,
	.ops			= &dc21285_ops,
	.setup			= dc21285_setup,
	.preinit		= dc21285_preinit,
	.postinit		= dc21285_postinit,
पूर्ण;

अटल पूर्णांक __init cats_pci_init(व्योम)
अणु
	अगर (machine_is_cats())
		pci_common_init(&cats_pci);
	वापस 0;
पूर्ण

subsys_initcall(cats_pci_init);
