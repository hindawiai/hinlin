<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This contain platक्रमm specअगरic code क्रम APM PPC460EX based Canyonlands
 * board.
 *
 * Copyright (c) 2010, Applied Micro Circuits Corporation
 * Author: Rupjyoti Sarmah <rsarmah@apm.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc4xx.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/uic.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/delay.h>
#समावेश "44x.h"

#घोषणा BCSR_USB_EN	0x11

अटल स्थिर काष्ठा of_device_id ppc460ex_of_bus[] __initस्थिर = अणु
	अणु .compatible = "ibm,plb4", पूर्ण,
	अणु .compatible = "ibm,opb", पूर्ण,
	अणु .compatible = "ibm,ebc", पूर्ण,
	अणु .compatible = "simple-bus", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init ppc460ex_device_probe(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, ppc460ex_of_bus, शून्य);

	वापस 0;
पूर्ण
machine_device_initcall(canyonlands, ppc460ex_device_probe);

/* Using this code only क्रम the Canyonlands board.  */

अटल पूर्णांक __init ppc460ex_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("amcc,canyonlands")) अणु
		pci_set_flags(PCI_REASSIGN_ALL_RSRC);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* USB PHY fixup code on Canyonlands kit. */

अटल पूर्णांक __init ppc460ex_canyonlands_fixup(व्योम)
अणु
	u8 __iomem *bcsr ;
	व्योम __iomem *vaddr;
	काष्ठा device_node *np;
	पूर्णांक ret = 0;

	np = of_find_compatible_node(शून्य, शून्य, "amcc,ppc460ex-bcsr");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "failed did not find amcc, ppc460ex bcsr node\n");
		वापस -ENODEV;
	पूर्ण

	bcsr = of_iomap(np, 0);
	of_node_put(np);

	अगर (!bcsr) अणु
		prपूर्णांकk(KERN_CRIT "Could not remap bcsr\n");
		ret = -ENODEV;
		जाओ err_bcsr;
	पूर्ण

	np = of_find_compatible_node(शून्य, शून्य, "ibm,ppc4xx-gpio");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "failed did not find ibm,ppc4xx-gpio node\n");
		वापस -ENODEV;
	पूर्ण

	vaddr = of_iomap(np, 0);
	of_node_put(np);

	अगर (!vaddr) अणु
		prपूर्णांकk(KERN_CRIT "Could not get gpio node address\n");
		ret = -ENODEV;
		जाओ err_gpio;
	पूर्ण
	/* Disable USB, through the BCSR7 bits */
	setbits8(&bcsr[7], BCSR_USB_EN);

	/* Wait क्रम a जबतक after reset */
	msleep(100);

	/* Enable USB here */
	clrbits8(&bcsr[7], BCSR_USB_EN);

	/*
	 * Configure multiplexed gpio16 and gpio19 as alternate1 output
	 * source after USB reset. In this configuration gpio16 will be
	 * USB2HStop and gpio19 will be USB2DStop. For more details refer to
	 * table 34-7 of PPC460EX user manual.
	 */
	setbits32((vaddr + GPIO0_OSRH), 0x42000000);
	setbits32((vaddr + GPIO0_TSRH), 0x42000000);
err_gpio:
	iounmap(vaddr);
err_bcsr:
	iounmap(bcsr);
	वापस ret;
पूर्ण
machine_device_initcall(canyonlands, ppc460ex_canyonlands_fixup);
define_machine(canyonlands) अणु
	.name = "Canyonlands",
	.probe = ppc460ex_probe,
	.progress = udbg_progress,
	.init_IRQ = uic_init_tree,
	.get_irq = uic_get_irq,
	.restart = ppc4xx_reset_प्रणाली,
	.calibrate_decr = generic_calibrate_decr,
पूर्ण;
