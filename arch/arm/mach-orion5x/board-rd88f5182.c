<शैली गुरु>
/*
 * arch/arm/mach-orion5x/rd88f5182-setup.c
 *
 * Marvell Orion-NAS Reference Design Setup
 *
 * Maपूर्णांकainer: Ronen Shitrit <rshitrit@marvell.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "common.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * RD-88F5182 Info
 ****************************************************************************/

/*
 * PCI
 */

#घोषणा RD88F5182_PCI_SLOT0_OFFS	7
#घोषणा RD88F5182_PCI_SLOT0_IRQ_A_PIN	7
#घोषणा RD88F5182_PCI_SLOT0_IRQ_B_PIN	6

/*****************************************************************************
 * PCI
 ****************************************************************************/

अटल व्योम __init rd88f5182_pci_preinit(व्योम)
अणु
	पूर्णांक pin;

	/*
	 * Configure PCI GPIO IRQ pins
	 */
	pin = RD88F5182_PCI_SLOT0_IRQ_A_PIN;
	अगर (gpio_request(pin, "PCI IntA") == 0) अणु
		अगर (gpio_direction_input(pin) == 0) अणु
			irq_set_irq_type(gpio_to_irq(pin), IRQ_TYPE_LEVEL_LOW);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "rd88f5182_pci_preinit failed to "
					"set_irq_type pin %d\n", pin);
			gpio_मुक्त(pin);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "rd88f5182_pci_preinit failed to request gpio %d\n", pin);
	पूर्ण

	pin = RD88F5182_PCI_SLOT0_IRQ_B_PIN;
	अगर (gpio_request(pin, "PCI IntB") == 0) अणु
		अगर (gpio_direction_input(pin) == 0) अणु
			irq_set_irq_type(gpio_to_irq(pin), IRQ_TYPE_LEVEL_LOW);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "rd88f5182_pci_preinit failed to "
					"set_irq_type pin %d\n", pin);
			gpio_मुक्त(pin);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "rd88f5182_pci_preinit failed to gpio_request %d\n", pin);
	पूर्ण
पूर्ण

अटल पूर्णांक __init rd88f5182_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
	u8 pin)
अणु
	पूर्णांक irq;

	/*
	 * Check क्रम devices with hard-wired IRQs.
	 */
	irq = orion5x_pci_map_irq(dev, slot, pin);
	अगर (irq != -1)
		वापस irq;

	/*
	 * PCI IRQs are connected via GPIOs
	 */
	चयन (slot - RD88F5182_PCI_SLOT0_OFFS) अणु
	हाल 0:
		अगर (pin == 1)
			वापस gpio_to_irq(RD88F5182_PCI_SLOT0_IRQ_A_PIN);
		अन्यथा
			वापस gpio_to_irq(RD88F5182_PCI_SLOT0_IRQ_B_PIN);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल काष्ठा hw_pci rd88f5182_pci __initdata = अणु
	.nr_controllers	= 2,
	.preinit	= rd88f5182_pci_preinit,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= rd88f5182_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init rd88f5182_pci_init(व्योम)
अणु
	अगर (of_machine_is_compatible("marvell,rd-88f5182-nas"))
		pci_common_init(&rd88f5182_pci);

	वापस 0;
पूर्ण

subsys_initcall(rd88f5182_pci_init);
