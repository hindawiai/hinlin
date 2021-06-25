<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Board setup routines क्रम the Motorola/Emerson MVME5100.
 *
 * Copyright 2013 CSC Australia Pty. Ltd.
 *
 * Based on earlier code by:
 *
 *    Matt Porter, MontaVista Software Inc.
 *    Copyright 2001 MontaVista Software Inc.
 *
 * Author: Stephen Chivers <schivers@csc.com>
 */

#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/prom.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/udbg.h>

#घोषणा HAWK_MPIC_SIZE		0x00040000U
#घोषणा MVME5100_PCI_MEM_OFFSET 0x00000000

/* Board रेजिस्टर addresses. */
#घोषणा BOARD_STATUS_REG	0xfef88080
#घोषणा BOARD_MODFAIL_REG	0xfef88090
#घोषणा BOARD_MODRST_REG	0xfef880a0
#घोषणा BOARD_TBEN_REG		0xfef880c0
#घोषणा BOARD_SW_READ_REG	0xfef880e0
#घोषणा BOARD_GEO_ADDR_REG	0xfef880e8
#घोषणा BOARD_EXT_FEATURE1_REG	0xfef880f0
#घोषणा BOARD_EXT_FEATURE2_REG	0xfef88100

अटल phys_addr_t pci_membase;
अटल u_अक्षर *restart;

अटल व्योम mvme5100_8259_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq = i8259_irq();

	अगर (cascade_irq)
		generic_handle_irq(cascade_irq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल व्योम __init mvme5100_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic;
	काष्ठा device_node *np;
	काष्ठा device_node *cp = शून्य;
	अचिन्हित पूर्णांक cirq;
	अचिन्हित दीर्घ पूर्णांकack = 0;
	स्थिर u32 *prop = शून्य;

	np = of_find_node_by_type(शून्य, "open-pic");
	अगर (!np) अणु
		pr_err("Could not find open-pic node\n");
		वापस;
	पूर्ण

	mpic = mpic_alloc(np, pci_membase, 0, 16, 256, " OpenPIC  ");

	BUG_ON(mpic == शून्य);
	of_node_put(np);

	mpic_assign_isu(mpic, 0, pci_membase + 0x10000);

	mpic_init(mpic);

	cp = of_find_compatible_node(शून्य, शून्य, "chrp,iic");
	अगर (cp == शून्य) अणु
		pr_warn("mvme5100_pic_init: couldn't find i8259\n");
		वापस;
	पूर्ण

	cirq = irq_of_parse_and_map(cp, 0);
	अगर (!cirq) अणु
		pr_warn("mvme5100_pic_init: no cascade interrupt?\n");
		वापस;
	पूर्ण

	np = of_find_compatible_node(शून्य, "pci", "mpc10x-pci");
	अगर (np) अणु
		prop = of_get_property(np, "8259-interrupt-acknowledge", शून्य);

		अगर (prop)
			पूर्णांकack = prop[0];

		of_node_put(np);
	पूर्ण

	अगर (पूर्णांकack)
		pr_debug("mvme5100_pic_init: PCI 8259 intack at 0x%016lx\n",
		   पूर्णांकack);

	i8259_init(cp, पूर्णांकack);
	of_node_put(cp);
	irq_set_chained_handler(cirq, mvme5100_8259_cascade);
पूर्ण

अटल पूर्णांक __init mvme5100_add_bridge(काष्ठा device_node *dev)
अणु
	स्थिर पूर्णांक		*bus_range;
	पूर्णांक			len;
	काष्ठा pci_controller	*hose;
	अचिन्हित लघु		devid;

	pr_info("Adding PCI host bridge %pOF\n", dev);

	bus_range = of_get_property(dev, "bus-range", &len);

	hose = pcibios_alloc_controller(dev);
	अगर (hose == शून्य)
		वापस -ENOMEM;

	hose->first_busno = bus_range ? bus_range[0] : 0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	setup_indirect_pci(hose, 0xfe000cf8, 0xfe000cfc, 0);

	pci_process_bridge_OF_ranges(hose, dev, 1);

	early_पढ़ो_config_word(hose, 0, 0, PCI_DEVICE_ID, &devid);

	अगर (devid != PCI_DEVICE_ID_MOTOROLA_HAWK) अणु
		pr_err("HAWK PHB not present?\n");
		वापस 0;
	पूर्ण

	early_पढ़ो_config_dword(hose, 0, 0, PCI_BASE_ADDRESS_1, &pci_membase);

	अगर (pci_membase == 0) अणु
		pr_err("HAWK PHB mibar not correctly set?\n");
		वापस 0;
	पूर्ण

	pr_info("mvme5100_pic_init: pci_membase: %x\n", pci_membase);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mvme5100_of_bus_ids[] __initस्थिर = अणु
	अणु .compatible = "hawk-bridge", पूर्ण,
	अणुपूर्ण,
पूर्ण;

/*
 * Setup the architecture
 */
अटल व्योम __init mvme5100_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("mvme5100_setup_arch()", 0);

	restart = ioremap(BOARD_MODRST_REG, 4);
पूर्ण

अटल व्योम __init mvme5100_setup_pci(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम_each_compatible_node(np, "pci", "hawk-pci")
		mvme5100_add_bridge(np);
पूर्ण

अटल व्योम mvme5100_show_cpuinfo(काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, "Vendor\t\t: Motorola/Emerson\n");
	seq_माला_दो(m, "Machine\t\t: MVME5100\n");
पूर्ण

अटल व्योम __noवापस mvme5100_restart(अक्षर *cmd)
अणु

	local_irq_disable();
	mपंचांगsr(mfmsr() | MSR_IP);

	out_8((u_अक्षर *) restart, 0x01);

	जबतक (1)
		;
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mvme5100_probe(व्योम)
अणु
	वापस of_machine_is_compatible("MVME5100");
पूर्ण

अटल पूर्णांक __init probe_of_platक्रमm_devices(व्योम)
अणु

	of_platक्रमm_bus_probe(शून्य, mvme5100_of_bus_ids, शून्य);
	वापस 0;
पूर्ण

machine_device_initcall(mvme5100, probe_of_platक्रमm_devices);

define_machine(mvme5100) अणु
	.name			= "MVME5100",
	.probe			= mvme5100_probe,
	.setup_arch		= mvme5100_setup_arch,
	.discover_phbs		= mvme5100_setup_pci,
	.init_IRQ		= mvme5100_pic_init,
	.show_cpuinfo		= mvme5100_show_cpuinfo,
	.get_irq		= mpic_get_irq,
	.restart		= mvme5100_restart,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
