<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AmigaOne platक्रमm setup
 *
 * Copyright 2008 Gerhard Pircher (gerhard_pircher@gmx.net)
 *
 *   Based on original amigaone_setup.c source code
 * Copyright 2003 by Hans-Joerg Frieden and Thomas Frieden
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/seq_file.h>
#समावेश <generated/utsrelease.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/dma.h>

बाह्य व्योम __flush_disable_L1(व्योम);

व्योम amigaone_show_cpuinfo(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "vendor\t\t: Eyetech Ltd.\n");
पूर्ण

अटल पूर्णांक __init amigaone_add_bridge(काष्ठा device_node *dev)
अणु
	स्थिर u32 *cfg_addr, *cfg_data;
	पूर्णांक len;
	स्थिर पूर्णांक *bus_range;
	काष्ठा pci_controller *hose;

	prपूर्णांकk(KERN_INFO "Adding PCI host bridge %pOF\n", dev);

	cfg_addr = of_get_address(dev, 0, शून्य, शून्य);
	cfg_data = of_get_address(dev, 1, शून्य, शून्य);
	अगर ((cfg_addr == शून्य) || (cfg_data == शून्य))
		वापस -ENODEV;

	bus_range = of_get_property(dev, "bus-range", &len);
	अगर ((bus_range == शून्य) || (len < 2 * माप(पूर्णांक)))
		prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF, assume"
		       " bus 0\n", dev);

	hose = pcibios_alloc_controller(dev);
	अगर (hose == शून्य)
		वापस -ENOMEM;

	hose->first_busno = bus_range ? bus_range[0] : 0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	setup_indirect_pci(hose, cfg_addr[0], cfg_data[0], 0);

	/* Interpret the "ranges" property */
	/* This also maps the I/O region and sets isa_io/mem_base */
	pci_process_bridge_OF_ranges(hose, dev, 1);

	वापस 0;
पूर्ण

व्योम __init amigaone_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("Linux/PPC "UTS_RELEASE"\n", 0);
पूर्ण

अटल व्योम __init amigaone_discover_phbs(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक phb = -ENODEV;

	/* Lookup PCI host bridges. */
	क्रम_each_compatible_node(np, "pci", "mai-logic,articia-s")
		phb = amigaone_add_bridge(np);

	BUG_ON(phb != 0);
पूर्ण

व्योम __init amigaone_init_IRQ(व्योम)
अणु
	काष्ठा device_node *pic, *np = शून्य;
	स्थिर अचिन्हित दीर्घ *prop = शून्य;
	अचिन्हित दीर्घ पूर्णांक_ack = 0;

	/* Search क्रम ISA पूर्णांकerrupt controller. */
	pic = of_find_compatible_node(शून्य, "interrupt-controller",
	                              "pnpPNP,000");
	BUG_ON(pic == शून्य);

	/* Look क्रम पूर्णांकerrupt acknowledge address in the PCI root node. */
	np = of_find_compatible_node(शून्य, "pci", "mai-logic,articia-s");
	अगर (np) अणु
		prop = of_get_property(np, "8259-interrupt-acknowledge", शून्य);
		अगर (prop)
			पूर्णांक_ack = prop[0];
		of_node_put(np);
	पूर्ण

	अगर (पूर्णांक_ack == 0)
		prपूर्णांकk(KERN_WARNING "Cannot find PCI interrupt acknowledge"
		       " address, polling\n");

	i8259_init(pic, पूर्णांक_ack);
	ppc_md.get_irq = i8259_irq;
	irq_set_शेष_host(i8259_get_host());
पूर्ण

अटल पूर्णांक __init request_isa_regions(व्योम)
अणु
	request_region(0x00, 0x20, "dma1");
	request_region(0x40, 0x20, "timer");
	request_region(0x80, 0x10, "dma page reg");
	request_region(0xc0, 0x20, "dma2");

	वापस 0;
पूर्ण
machine_device_initcall(amigaone, request_isa_regions);

व्योम __noवापस amigaone_restart(अक्षर *cmd)
अणु
	local_irq_disable();

	/* Flush and disable caches. */
	__flush_disable_L1();

        /* Set SRR0 to the reset vector and turn on MSR_IP. */
	mtspr(SPRN_SRR0, 0xfff00100);
	mtspr(SPRN_SRR1, MSR_IP);

	/* Do an rfi to jump back to firmware. */
	__यंत्र__ __अस्थिर__("rfi" : : : "memory");

	/* Not reached. */
	जबतक (1);
पूर्ण

अटल पूर्णांक __init amigaone_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("eyetech,amigaone")) अणु
		/*
		 * Coherent memory access cause complete प्रणाली lockup! Thus
		 * disable this CPU feature, even अगर the CPU needs it.
		 */
		cur_cpu_spec->cpu_features &= ~CPU_FTR_NEED_COHERENT;

		DMA_MODE_READ = 0x44;
		DMA_MODE_WRITE = 0x48;

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

define_machine(amigaone) अणु
	.name			= "AmigaOne",
	.probe			= amigaone_probe,
	.setup_arch		= amigaone_setup_arch,
	.discover_phbs		= amigaone_discover_phbs,
	.show_cpuinfo		= amigaone_show_cpuinfo,
	.init_IRQ		= amigaone_init_IRQ,
	.restart		= amigaone_restart,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
