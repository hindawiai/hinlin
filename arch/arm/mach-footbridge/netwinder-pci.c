<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-footbridge/netwinder-pci.c
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

/*
 * We now use the slot ID instead of the device identअगरiers to select
 * which पूर्णांकerrupt is routed where.
 */
अटल पूर्णांक netwinder_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	चयन (slot) अणु
	हाल 0:  /* host bridge */
		वापस 0;

	हाल 9:  /* CyberPro */
		वापस IRQ_NETWINDER_VGA;

	हाल 10: /* DC21143 */
		वापस IRQ_NETWINDER_ETHER100;

	हाल 12: /* Winbond 553 */
		वापस IRQ_ISA_HARDDISK1;

	हाल 13: /* Winbond 89C940F */
		वापस IRQ_NETWINDER_ETHER10;

	शेष:
		prपूर्णांकk(KERN_ERR "PCI: unknown device in slot %s\n",
			pci_name(dev));
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा hw_pci netwinder_pci __initdata = अणु
	.map_irq		= netwinder_map_irq,
	.nr_controllers		= 1,
	.ops			= &dc21285_ops,
	.setup			= dc21285_setup,
	.preinit		= dc21285_preinit,
	.postinit		= dc21285_postinit,
पूर्ण;

अटल पूर्णांक __init netwinder_pci_init(व्योम)
अणु
	अगर (machine_is_netwinder())
		pci_common_init(&netwinder_pci);
	वापस 0;
पूर्ण

subsys_initcall(netwinder_pci_init);
