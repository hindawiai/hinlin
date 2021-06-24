<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Maxtor Shared Storage II Board Setup
 *
 * Maपूर्णांकainer: Sylver Bruneau <sylver.bruneau@googlemail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "orion5x.h"
#समावेश "bridge-regs.h"
#समावेश "common.h"

/*****************************************************************************
 * Maxtor Shared Storage II Info
 ****************************************************************************/

/****************************************************************************
 * PCI setup
 ****************************************************************************/
अटल पूर्णांक __init mss2_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq;

	/*
	 * Check क्रम devices with hard-wired IRQs.
	 */
	irq = orion5x_pci_map_irq(dev, slot, pin);
	अगर (irq != -1)
		वापस irq;

	वापस -1;
पूर्ण

अटल काष्ठा hw_pci mss2_pci __initdata = अणु
	.nr_controllers = 2,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= mss2_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init mss2_pci_init(व्योम)
अणु
	अगर (machine_is_mss2())
		pci_common_init(&mss2_pci);

	वापस 0;
पूर्ण
subsys_initcall(mss2_pci_init);

/*****************************************************************************
 * MSS2 घातer off method
 ****************************************************************************/
/*
 * On the Maxtor Shared Storage II, the shutकरोwn process is the following :
 * - Userland modअगरies U-boot env to tell U-boot to go idle at next boot
 * - The board reboots
 * - U-boot starts and go पूर्णांकo an idle mode until the user press "power"
 */
अटल व्योम mss2_घातer_off(व्योम)
अणु
	u32 reg;

	/*
	 * Enable and issue soft reset
	 */
	reg = पढ़ोl(RSTOUTn_MASK);
	reg |= 1 << 2;
	ग_लिखोl(reg, RSTOUTn_MASK);

	reg = पढ़ोl(CPU_SOFT_RESET);
	reg |= 1;
	ग_लिखोl(reg, CPU_SOFT_RESET);
पूर्ण

व्योम __init mss2_init(व्योम)
अणु
	/* रेजिस्टर mss2 specअगरic घातer-off method */
	pm_घातer_off = mss2_घातer_off;
पूर्ण
