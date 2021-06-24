<शैली गुरु>
/*
 * Board setup routines क्रम the Buffalo Linkstation / Kurobox Platक्रमm.
 *
 * Copyright (C) 2006 G. Liakhovetski (g.liakhovetski@gmx.de)
 *
 * Based on sandpoपूर्णांक.c by Mark A. Greer
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of
 * any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/initrd.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/pci-bridge.h>

#समावेश "mpc10x.h"

अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .type = "soc", पूर्ण,
	अणु .compatible = "simple-bus", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init declare_of_platक्रमm_devices(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य);
	वापस 0;
पूर्ण
machine_device_initcall(linkstation, declare_of_platक्रमm_devices);

अटल पूर्णांक __init linkstation_add_bridge(काष्ठा device_node *dev)
अणु
#अगर_घोषित CONFIG_PCI
	पूर्णांक len;
	काष्ठा pci_controller *hose;
	स्थिर पूर्णांक *bus_range;

	prपूर्णांकk("Adding PCI host bridge %pOF\n", dev);

	bus_range = of_get_property(dev, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक))
		prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF, assume"
				" bus 0\n", dev);

	hose = pcibios_alloc_controller(dev);
	अगर (hose == शून्य)
		वापस -ENOMEM;
	hose->first_busno = bus_range ? bus_range[0] : 0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;
	setup_indirect_pci(hose, 0xfec00000, 0xfee00000, 0);

	/* Interpret the "ranges" property */
	/* This also maps the I/O region and sets isa_io/mem_base */
	pci_process_bridge_OF_ranges(hose, dev, 1);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __init linkstation_setup_arch(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "BUFFALO Network Attached Storage Series\n");
	prपूर्णांकk(KERN_INFO "(C) 2002-2005 BUFFALO INC.\n");
पूर्ण

अटल व्योम __init linkstation_setup_pci(व्योम)
अणु
	काष्ठा device_node *np;

	/* Lookup PCI host bridges */
	क्रम_each_compatible_node(np, "pci", "mpc10x-pci")
		linkstation_add_bridge(np);
पूर्ण

/*
 * Interrupt setup and service.  Interrupts on the linkstation come
 * from the four PCI slots plus onboard 8241 devices: I2C, DUART.
 */
अटल व्योम __init linkstation_init_IRQ(व्योम)
अणु
	काष्ठा mpic *mpic;

	mpic = mpic_alloc(शून्य, 0, 0, 4, 0, " EPIC     ");
	BUG_ON(mpic == शून्य);

	/* PCI IRQs */
	mpic_assign_isu(mpic, 0, mpic->paddr + 0x10200);

	/* I2C */
	mpic_assign_isu(mpic, 1, mpic->paddr + 0x11000);

	/* ttyS0, ttyS1 */
	mpic_assign_isu(mpic, 2, mpic->paddr + 0x11100);

	mpic_init(mpic);
पूर्ण

बाह्य व्योम avr_uart_configure(व्योम);
बाह्य व्योम avr_uart_send(स्थिर अक्षर);

अटल व्योम __noवापस linkstation_restart(अक्षर *cmd)
अणु
	local_irq_disable();

	/* Reset प्रणाली via AVR */
	avr_uart_configure();
	/* Send reboot command */
	avr_uart_send('C');

	क्रम(;;)  /* Spin until reset happens */
		avr_uart_send('G');	/* "kick" */
पूर्ण

अटल व्योम __noवापस linkstation_घातer_off(व्योम)
अणु
	local_irq_disable();

	/* Power करोwn प्रणाली via AVR */
	avr_uart_configure();
	/* send shutकरोwn command */
	avr_uart_send('E');

	क्रम(;;)  /* Spin until घातer-off happens */
		avr_uart_send('G');	/* "kick" */
	/* NOTREACHED */
पूर्ण

अटल व्योम __noवापस linkstation_halt(व्योम)
अणु
	linkstation_घातer_off();
	/* NOTREACHED */
पूर्ण

अटल व्योम linkstation_show_cpuinfo(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "vendor\t\t: Buffalo Technology\n");
	seq_म_लिखो(m, "machine\t\t: Linkstation I/Kurobox(HG)\n");
पूर्ण

अटल पूर्णांक __init linkstation_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("linkstation"))
		वापस 0;

	pm_घातer_off = linkstation_घातer_off;

	वापस 1;
पूर्ण

define_machine(linkstation)अणु
	.name 			= "Buffalo Linkstation",
	.probe 			= linkstation_probe,
	.setup_arch 		= linkstation_setup_arch,
	.discover_phbs		= linkstation_setup_pci,
	.init_IRQ 		= linkstation_init_IRQ,
	.show_cpuinfo 		= linkstation_show_cpuinfo,
	.get_irq 		= mpic_get_irq,
	.restart 		= linkstation_restart,
	.halt	 		= linkstation_halt,
	.calibrate_decr 	= generic_calibrate_decr,
पूर्ण;
