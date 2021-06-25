<शैली गुरु>
/*
 * Board setup routines क्रम the storcenter
 *
 * Copyright 2007 (C) Oyvind Repvik (nail@nslu2-linux.org)
 * Copyright 2007 Andy Wilcox, Jon Loeliger
 *
 * Based on linkstation.c by G. Liakhovetski
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of
 * any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/initrd.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/pci-bridge.h>

#समावेश "mpc10x.h"


अटल स्थिर काष्ठा of_device_id storcenter_of_bus[] __initस्थिर = अणु
	अणु .name = "soc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init storcenter_device_probe(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, storcenter_of_bus, शून्य);
	वापस 0;
पूर्ण
machine_device_initcall(storcenter, storcenter_device_probe);


अटल पूर्णांक __init storcenter_add_bridge(काष्ठा device_node *dev)
अणु
#अगर_घोषित CONFIG_PCI
	पूर्णांक len;
	काष्ठा pci_controller *hose;
	स्थिर पूर्णांक *bus_range;

	prपूर्णांकk("Adding PCI host bridge %pOF\n", dev);

	hose = pcibios_alloc_controller(dev);
	अगर (hose == शून्य)
		वापस -ENOMEM;

	bus_range = of_get_property(dev, "bus-range", &len);
	hose->first_busno = bus_range ? bus_range[0] : 0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	setup_indirect_pci(hose, MPC10X_MAPB_CNFG_ADDR, MPC10X_MAPB_CNFG_DATA, 0);

	/* Interpret the "ranges" property */
	/* This also maps the I/O region and sets isa_io/mem_base */
	pci_process_bridge_OF_ranges(hose, dev, 1);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __init storcenter_setup_arch(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "IOMEGA StorCenter\n");
पूर्ण

अटल व्योम __init storcenter_setup_pci(व्योम)
अणु
	काष्ठा device_node *np;

	/* Lookup PCI host bridges */
	क्रम_each_compatible_node(np, "pci", "mpc10x-pci")
		storcenter_add_bridge(np);
पूर्ण

/*
 * Interrupt setup and service.  Interrupts on the turbostation come
 * from the four PCI slots plus onboard 8241 devices: I2C, DUART.
 */
अटल व्योम __init storcenter_init_IRQ(व्योम)
अणु
	काष्ठा mpic *mpic;

	mpic = mpic_alloc(शून्य, 0, 0, 16, 0, " OpenPIC  ");
	BUG_ON(mpic == शून्य);

	/*
	 * 16 Serial Interrupts followed by 16 Internal Interrupts.
	 * I2C is the second पूर्णांकernal, so it is at 17, 0x11020.
	 */
	mpic_assign_isu(mpic, 0, mpic->paddr + 0x10200);
	mpic_assign_isu(mpic, 1, mpic->paddr + 0x11000);

	mpic_init(mpic);
पूर्ण

अटल व्योम __noवापस storcenter_restart(अक्षर *cmd)
अणु
	local_irq_disable();

	/* Set exception prefix high - to the firmware */
	mपंचांगsr(mfmsr() | MSR_IP);
	isync();

	/* Wait क्रम reset to happen */
	क्रम (;;) ;
पूर्ण

अटल पूर्णांक __init storcenter_probe(व्योम)
अणु
	वापस of_machine_is_compatible("iomega,storcenter");
पूर्ण

define_machine(storcenter)अणु
	.name 			= "IOMEGA StorCenter",
	.probe 			= storcenter_probe,
	.setup_arch 		= storcenter_setup_arch,
	.discover_phbs 		= storcenter_setup_pci,
	.init_IRQ 		= storcenter_init_IRQ,
	.get_irq 		= mpic_get_irq,
	.restart 		= storcenter_restart,
	.calibrate_decr 	= generic_calibrate_decr,
पूर्ण;
