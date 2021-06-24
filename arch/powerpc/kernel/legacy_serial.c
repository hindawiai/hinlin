<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/console.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/serial_reg.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/serial.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/early_ioremap.h>

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) करो अणु prपूर्णांकk(fmt); पूर्ण जबतक(0)
#अन्यथा
#घोषणा DBG(fmt...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#घोषणा MAX_LEGACY_SERIAL_PORTS	8

अटल काष्ठा plat_serial8250_port
legacy_serial_ports[MAX_LEGACY_SERIAL_PORTS+1];
अटल काष्ठा legacy_serial_info अणु
	काष्ठा device_node		*np;
	अचिन्हित पूर्णांक			speed;
	अचिन्हित पूर्णांक			घड़ी;
	पूर्णांक				irq_check_parent;
	phys_addr_t			taddr;
	व्योम __iomem			*early_addr;
पूर्ण legacy_serial_infos[MAX_LEGACY_SERIAL_PORTS];

अटल स्थिर काष्ठा of_device_id legacy_serial_parents[] __initस्थिर = अणु
	अणु.type = "soc",पूर्ण,
	अणु.type = "tsi-bridge",पूर्ण,
	अणु.type = "opb", पूर्ण,
	अणु.compatible = "ibm,opb",पूर्ण,
	अणु.compatible = "simple-bus",पूर्ण,
	अणु.compatible = "wrs,epld-localbus",पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक legacy_serial_count;
अटल पूर्णांक legacy_serial_console = -1;

अटल स्थिर upf_t legacy_port_flags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
	UPF_SHARE_IRQ | UPF_FIXED_PORT;

अटल अचिन्हित पूर्णांक tsi_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	offset = offset << p->regshअगरt;
	अगर (offset == UART_IIR) अणु
		पंचांगp = पढ़ोl(p->membase + (UART_IIR & ~3));
		वापस (पंचांगp >> 16) & 0xff; /* UART_IIR % 4 == 2 */
	पूर्ण अन्यथा
		वापस पढ़ोb(p->membase + offset);
पूर्ण

अटल व्योम tsi_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	offset = offset << p->regshअगरt;
	अगर (!((offset == UART_IER) && (value & UART_IER_UUE)))
		ग_लिखोb(value, p->membase + offset);
पूर्ण

अटल पूर्णांक __init add_legacy_port(काष्ठा device_node *np, पूर्णांक want_index,
				  पूर्णांक iotype, phys_addr_t base,
				  phys_addr_t taddr, अचिन्हित दीर्घ irq,
				  upf_t flags, पूर्णांक irq_check_parent)
अणु
	स्थिर __be32 *clk, *spd, *rs;
	u32 घड़ी = BASE_BAUD * 16;
	u32 shअगरt = 0;
	पूर्णांक index;

	/* get घड़ी freq. अगर present */
	clk = of_get_property(np, "clock-frequency", शून्य);
	अगर (clk && *clk)
		घड़ी = be32_to_cpup(clk);

	/* get शेष speed अगर present */
	spd = of_get_property(np, "current-speed", शून्य);

	/* get रेजिस्टर shअगरt अगर present */
	rs = of_get_property(np, "reg-shift", शून्य);
	अगर (rs && *rs)
		shअगरt = be32_to_cpup(rs);

	/* If we have a location index, then try to use it */
	अगर (want_index >= 0 && want_index < MAX_LEGACY_SERIAL_PORTS)
		index = want_index;
	अन्यथा
		index = legacy_serial_count;

	/* अगर our index is still out of range, that mean that
	 * array is full, we could scan क्रम a मुक्त slot but that
	 * make little sense to bother, just skip the port
	 */
	अगर (index >= MAX_LEGACY_SERIAL_PORTS)
		वापस -1;
	अगर (index >= legacy_serial_count)
		legacy_serial_count = index + 1;

	/* Check अगर there is a port who alपढ़ोy claimed our slot */
	अगर (legacy_serial_infos[index].np != शून्य) अणु
		/* अगर we still have some room, move it, अन्यथा override */
		अगर (legacy_serial_count < MAX_LEGACY_SERIAL_PORTS) अणु
			prपूर्णांकk(KERN_DEBUG "Moved legacy port %d -> %d\n",
			       index, legacy_serial_count);
			legacy_serial_ports[legacy_serial_count] =
				legacy_serial_ports[index];
			legacy_serial_infos[legacy_serial_count] =
				legacy_serial_infos[index];
			legacy_serial_count++;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG "Replacing legacy port %d\n", index);
		पूर्ण
	पूर्ण

	/* Now fill the entry */
	स_रखो(&legacy_serial_ports[index], 0,
	       माप(काष्ठा plat_serial8250_port));
	अगर (iotype == UPIO_PORT)
		legacy_serial_ports[index].iobase = base;
	अन्यथा
		legacy_serial_ports[index].mapbase = base;

	legacy_serial_ports[index].iotype = iotype;
	legacy_serial_ports[index].uartclk = घड़ी;
	legacy_serial_ports[index].irq = irq;
	legacy_serial_ports[index].flags = flags;
	legacy_serial_ports[index].regshअगरt = shअगरt;
	legacy_serial_infos[index].taddr = taddr;
	legacy_serial_infos[index].np = of_node_get(np);
	legacy_serial_infos[index].घड़ी = घड़ी;
	legacy_serial_infos[index].speed = spd ? be32_to_cpup(spd) : 0;
	legacy_serial_infos[index].irq_check_parent = irq_check_parent;

	अगर (iotype == UPIO_TSI) अणु
		legacy_serial_ports[index].serial_in = tsi_serial_in;
		legacy_serial_ports[index].serial_out = tsi_serial_out;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "Found legacy serial port %d for %pOF\n",
	       index, np);
	prपूर्णांकk(KERN_DEBUG "  %s=%llx, taddr=%llx, irq=%lx, clk=%d, speed=%d\n",
	       (iotype == UPIO_PORT) ? "port" : "mem",
	       (अचिन्हित दीर्घ दीर्घ)base, (अचिन्हित दीर्घ दीर्घ)taddr, irq,
	       legacy_serial_ports[index].uartclk,
	       legacy_serial_infos[index].speed);

	वापस index;
पूर्ण

अटल पूर्णांक __init add_legacy_soc_port(काष्ठा device_node *np,
				      काष्ठा device_node *soc_dev)
अणु
	u64 addr;
	स्थिर __be32 *addrp;
	काष्ठा device_node *tsi = of_get_parent(np);

	/* We only support ports that have a घड़ी frequency properly
	 * encoded in the device-tree.
	 */
	अगर (of_get_property(np, "clock-frequency", शून्य) == शून्य)
		वापस -1;

	/* अगर reg-offset करोn't try to use it */
	अगर ((of_get_property(np, "reg-offset", शून्य) != शून्य))
		वापस -1;

	/* अगर rtas uses this device, करोn't try to use it as well */
	अगर (of_get_property(np, "used-by-rtas", शून्य) != शून्य)
		वापस -1;

	/* Get the address */
	addrp = of_get_address(soc_dev, 0, शून्य, शून्य);
	अगर (addrp == शून्य)
		वापस -1;

	addr = of_translate_address(soc_dev, addrp);
	अगर (addr == OF_BAD_ADDR)
		वापस -1;

	/* Add port, irq will be dealt with later. We passed a translated
	 * IO port value. It will be fixed up later aदीर्घ with the irq
	 */
	अगर (of_node_is_type(tsi, "tsi-bridge"))
		वापस add_legacy_port(np, -1, UPIO_TSI, addr, addr,
				       0, legacy_port_flags, 0);
	अन्यथा
		वापस add_legacy_port(np, -1, UPIO_MEM, addr, addr,
				       0, legacy_port_flags, 0);
पूर्ण

अटल पूर्णांक __init add_legacy_isa_port(काष्ठा device_node *np,
				      काष्ठा device_node *isa_brg)
अणु
	स्थिर __be32 *reg;
	स्थिर अक्षर *typep;
	पूर्णांक index = -1;
	u64 taddr;

	DBG(" -> add_legacy_isa_port(%pOF)\n", np);

	/* Get the ISA port number */
	reg = of_get_property(np, "reg", शून्य);
	अगर (reg == शून्य)
		वापस -1;

	/* Verअगरy it's an IO port, we don't support anything अन्यथा */
	अगर (!(be32_to_cpu(reg[0]) & 0x00000001))
		वापस -1;

	/* Now look क्रम an "ibm,aix-loc" property that gives us ordering
	 * अगर any...
	 */
	typep = of_get_property(np, "ibm,aix-loc", शून्य);

	/* If we have a location index, then use it */
	अगर (typep && *typep == 'S')
		index = simple_म_से_दीर्घ(typep+1, शून्य, 0) - 1;

	/* Translate ISA address. If it fails, we still रेजिस्टर the port
	 * with no translated address so that it can be picked up as an IO
	 * port later by the serial driver
	 *
	 * Note: Don't even try on P8 lpc, we know it's not directly mapped
	 */
	अगर (!of_device_is_compatible(isa_brg, "ibm,power8-lpc") ||
	    of_get_property(isa_brg, "ranges", शून्य)) अणु
		taddr = of_translate_address(np, reg);
		अगर (taddr == OF_BAD_ADDR)
			taddr = 0;
	पूर्ण अन्यथा
		taddr = 0;

	/* Add port, irq will be dealt with later */
	वापस add_legacy_port(np, index, UPIO_PORT, be32_to_cpu(reg[1]),
			       taddr, 0, legacy_port_flags, 0);

पूर्ण

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक __init add_legacy_pci_port(काष्ठा device_node *np,
				      काष्ठा device_node *pci_dev)
अणु
	u64 addr, base;
	स्थिर __be32 *addrp;
	अचिन्हित पूर्णांक flags;
	पूर्णांक iotype, index = -1, lindex = 0;

	DBG(" -> add_legacy_pci_port(%pOF)\n", np);

	/* We only support ports that have a घड़ी frequency properly
	 * encoded in the device-tree (that is have an fcode). Anything
	 * अन्यथा can't be used that early and will be normally probed by
	 * the generic 8250_pci driver later on. The reason is that 8250
	 * compatible UARTs on PCI need all sort of quirks (port offsets
	 * etc...) that this code करोesn't know about
	 */
	अगर (of_get_property(np, "clock-frequency", शून्य) == शून्य)
		वापस -1;

	/* Get the PCI address. Assume BAR 0 */
	addrp = of_get_pci_address(pci_dev, 0, शून्य, &flags);
	अगर (addrp == शून्य)
		वापस -1;

	/* We only support BAR 0 क्रम now */
	iotype = (flags & IORESOURCE_MEM) ? UPIO_MEM : UPIO_PORT;
	addr = of_translate_address(pci_dev, addrp);
	अगर (addr == OF_BAD_ADDR)
		वापस -1;

	/* Set the IO base to the same as the translated address क्रम MMIO,
	 * or to the करोमुख्य local IO base क्रम PIO (it will be fixed up later)
	 */
	अगर (iotype == UPIO_MEM)
		base = addr;
	अन्यथा
		base = of_पढ़ो_number(&addrp[2], 1);

	/* Try to guess an index... If we have subdevices of the pci dev,
	 * we get to their "reg" property
	 */
	अगर (np != pci_dev) अणु
		स्थिर __be32 *reg = of_get_property(np, "reg", शून्य);
		अगर (reg && (be32_to_cpup(reg) < 4))
			index = lindex = be32_to_cpup(reg);
	पूर्ण

	/* Local index means it's the Nth port in the PCI chip. Unक्रमtunately
	 * the offset to add here is device specअगरic. We know about those
	 * EXAR ports and we शेष to the most common हाल. If your UART
	 * करोesn't work for these settings, you'll have to add your own special
	 * हालs here
	 */
	अगर (of_device_is_compatible(pci_dev, "pci13a8,152") ||
	    of_device_is_compatible(pci_dev, "pci13a8,154") ||
	    of_device_is_compatible(pci_dev, "pci13a8,158")) अणु
		addr += 0x200 * lindex;
		base += 0x200 * lindex;
	पूर्ण अन्यथा अणु
		addr += 8 * lindex;
		base += 8 * lindex;
	पूर्ण

	/* Add port, irq will be dealt with later. We passed a translated
	 * IO port value. It will be fixed up later aदीर्घ with the irq
	 */
	वापस add_legacy_port(np, index, iotype, base, addr, 0,
			       legacy_port_flags, np != pci_dev);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init setup_legacy_serial_console(पूर्णांक console)
अणु
	काष्ठा legacy_serial_info *info = &legacy_serial_infos[console];
	काष्ठा plat_serial8250_port *port = &legacy_serial_ports[console];
	अचिन्हित पूर्णांक stride;

	stride = 1 << port->regshअगरt;

	/* Check अगर a translated MMIO address has been found */
	अगर (info->taddr) अणु
		info->early_addr = early_ioremap(info->taddr, 0x1000);
		अगर (info->early_addr == शून्य)
			वापस;
		udbg_uart_init_mmio(info->early_addr, stride);
	पूर्ण अन्यथा अणु
		/* Check अगर it's PIO and we support untranslated PIO */
		अगर (port->iotype == UPIO_PORT && isa_io_special)
			udbg_uart_init_pio(port->iobase, stride);
		अन्यथा
			वापस;
	पूर्ण

	/* Try to query the current speed */
	अगर (info->speed == 0)
		info->speed = udbg_probe_uart_speed(info->घड़ी);

	/* Set it up */
	DBG("default console speed = %d\n", info->speed);
	udbg_uart_setup(info->speed, info->घड़ी);
पूर्ण

अटल पूर्णांक __init ioremap_legacy_serial_console(व्योम)
अणु
	काष्ठा plat_serial8250_port *port;
	काष्ठा legacy_serial_info *info;
	व्योम __iomem *vaddr;

	अगर (legacy_serial_console < 0)
		वापस 0;

	info = &legacy_serial_infos[legacy_serial_console];
	port = &legacy_serial_ports[legacy_serial_console];

	अगर (!info->early_addr)
		वापस 0;

	vaddr = ioremap(info->taddr, 0x1000);
	अगर (WARN_ON(!vaddr))
		वापस -ENOMEM;

	udbg_uart_init_mmio(vaddr, 1 << port->regshअगरt);
	early_iounmap(info->early_addr, 0x1000);
	info->early_addr = शून्य;

	वापस 0;
पूर्ण
early_initcall(ioremap_legacy_serial_console);

/*
 * This is called very early, as part of setup_प्रणाली() or eventually
 * setup_arch(), basically beक्रमe anything अन्यथा in this file. This function
 * will try to build a list of all the available 8250-compatible serial ports
 * in the machine using the Open Firmware device-tree. It currently only deals
 * with ISA and PCI busses but could be extended. It allows a very early boot
 * console to be initialized, that list is also used later to provide 8250 with
 * the machine non-PCI ports and to properly pick the शेष console port
 */
व्योम __init find_legacy_serial_ports(व्योम)
अणु
	काष्ठा device_node *np, *मानक_निकास = शून्य;
	स्थिर अक्षर *path;
	पूर्णांक index;

	DBG(" -> find_legacy_serial_port()\n");

	/* Now find out अगर one of these is out firmware console */
	path = of_get_property(of_chosen, "linux,stdout-path", शून्य);
	अगर (path == शून्य)
		path = of_get_property(of_chosen, "stdout-path", शून्य);
	अगर (path != शून्य) अणु
		मानक_निकास = of_find_node_by_path(path);
		अगर (मानक_निकास)
			DBG("stdout is %pOF\n", मानक_निकास);
	पूर्ण अन्यथा अणु
		DBG(" no linux,stdout-path !\n");
	पूर्ण

	/* Iterate over all the 16550 ports, looking क्रम known parents */
	क्रम_each_compatible_node(np, "serial", "ns16550") अणु
		काष्ठा device_node *parent = of_get_parent(np);
		अगर (!parent)
			जारी;
		अगर (of_match_node(legacy_serial_parents, parent) != शून्य) अणु
			अगर (of_device_is_available(np)) अणु
				index = add_legacy_soc_port(np, np);
				अगर (index >= 0 && np == मानक_निकास)
					legacy_serial_console = index;
			पूर्ण
		पूर्ण
		of_node_put(parent);
	पूर्ण

	/* Next, fill our array with ISA ports */
	क्रम_each_node_by_type(np, "serial") अणु
		काष्ठा device_node *isa = of_get_parent(np);
		अगर (of_node_name_eq(isa, "isa") || of_node_name_eq(isa, "lpc")) अणु
			अगर (of_device_is_available(np)) अणु
				index = add_legacy_isa_port(np, isa);
				अगर (index >= 0 && np == मानक_निकास)
					legacy_serial_console = index;
			पूर्ण
		पूर्ण
		of_node_put(isa);
	पूर्ण

#अगर_घोषित CONFIG_PCI
	/* Next, try to locate PCI ports */
	क्रम (np = शून्य; (np = of_find_all_nodes(np));) अणु
		काष्ठा device_node *pci, *parent = of_get_parent(np);
		अगर (of_node_name_eq(parent, "isa")) अणु
			of_node_put(parent);
			जारी;
		पूर्ण
		अगर (!of_node_name_eq(np, "serial") &&
		    !of_node_is_type(np, "serial")) अणु
			of_node_put(parent);
			जारी;
		पूर्ण
		/* Check क्रम known pciclass, and also check whether we have
		 * a device with child nodes क्रम ports or not
		 */
		अगर (of_device_is_compatible(np, "pciclass,0700") ||
		    of_device_is_compatible(np, "pciclass,070002"))
			pci = np;
		अन्यथा अगर (of_device_is_compatible(parent, "pciclass,0700") ||
			 of_device_is_compatible(parent, "pciclass,070002"))
			pci = parent;
		अन्यथा अणु
			of_node_put(parent);
			जारी;
		पूर्ण
		index = add_legacy_pci_port(np, pci);
		अगर (index >= 0 && np == मानक_निकास)
			legacy_serial_console = index;
		of_node_put(parent);
	पूर्ण
#पूर्ण_अगर

	DBG("legacy_serial_console = %d\n", legacy_serial_console);
	अगर (legacy_serial_console >= 0)
		setup_legacy_serial_console(legacy_serial_console);
	DBG(" <- find_legacy_serial_port()\n");
पूर्ण

अटल काष्ठा platक्रमm_device serial_device = अणु
	.name	= "serial8250",
	.id	= PLAT8250_DEV_PLATFORM,
	.dev	= अणु
		.platक्रमm_data = legacy_serial_ports,
	पूर्ण,
पूर्ण;

अटल व्योम __init fixup_port_irq(पूर्णांक index,
				  काष्ठा device_node *np,
				  काष्ठा plat_serial8250_port *port)
अणु
	अचिन्हित पूर्णांक virq;

	DBG("fixup_port_irq(%d)\n", index);

	virq = irq_of_parse_and_map(np, 0);
	अगर (!virq && legacy_serial_infos[index].irq_check_parent) अणु
		np = of_get_parent(np);
		अगर (np == शून्य)
			वापस;
		virq = irq_of_parse_and_map(np, 0);
		of_node_put(np);
	पूर्ण
	अगर (!virq)
		वापस;

	port->irq = virq;

#अगर_घोषित CONFIG_SERIAL_8250_FSL
	अगर (of_device_is_compatible(np, "fsl,ns16550")) अणु
		port->handle_irq = fsl8250_handle_irq;
		port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_8250_CONSOLE);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init fixup_port_pio(पूर्णांक index,
				  काष्ठा device_node *np,
				  काष्ठा plat_serial8250_port *port)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा pci_controller *hose;

	DBG("fixup_port_pio(%d)\n", index);

	hose = pci_find_hose_क्रम_OF_device(np);
	अगर (hose) अणु
		अचिन्हित दीर्घ offset = (अचिन्हित दीर्घ)hose->io_base_virt -
#अगर_घोषित CONFIG_PPC64
			pci_io_base;
#अन्यथा
			isa_io_base;
#पूर्ण_अगर
		DBG("port %d, IO %lx -> %lx\n",
		    index, port->iobase, port->iobase + offset);
		port->iobase += offset;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init fixup_port_mmio(पूर्णांक index,
				   काष्ठा device_node *np,
				   काष्ठा plat_serial8250_port *port)
अणु
	DBG("fixup_port_mmio(%d)\n", index);

	port->membase = ioremap(port->mapbase, 0x100);
पूर्ण

/*
 * This is called as an arch initcall, hopefully beक्रमe the PCI bus is
 * probed and/or the 8250 driver loaded since we need to रेजिस्टर our
 * platक्रमm devices beक्रमe 8250 PCI ones are detected as some of them
 * must properly "override" the platक्रमm ones.
 *
 * This function fixes up the पूर्णांकerrupt value क्रम platक्रमm ports as it
 * couldn't be करोne earlier beक्रमe पूर्णांकerrupt maps have been parsed. It
 * also "corrects" the IO address क्रम PIO ports क्रम the same reason,
 * since earlier, the PHBs भव IO space wasn't asचिन्हित yet. It then
 * रेजिस्टरs all those platक्रमm ports क्रम use by the 8250 driver when it
 * finally loads.
 */
अटल पूर्णांक __init serial_dev_init(व्योम)
अणु
	पूर्णांक i;

	अगर (legacy_serial_count == 0)
		वापस -ENODEV;

	/*
	 * Beक्रमe we रेजिस्टर the platक्रमm serial devices, we need
	 * to fixup their पूर्णांकerrupts and their IO ports.
	 */
	DBG("Fixing serial ports interrupts and IO ports ...\n");

	क्रम (i = 0; i < legacy_serial_count; i++) अणु
		काष्ठा plat_serial8250_port *port = &legacy_serial_ports[i];
		काष्ठा device_node *np = legacy_serial_infos[i].np;

		अगर (!port->irq)
			fixup_port_irq(i, np, port);
		अगर (port->iotype == UPIO_PORT)
			fixup_port_pio(i, np, port);
		अगर ((port->iotype == UPIO_MEM) || (port->iotype == UPIO_TSI))
			fixup_port_mmio(i, np, port);
	पूर्ण

	DBG("Registering platform serial ports\n");

	वापस platक्रमm_device_रेजिस्टर(&serial_device);
पूर्ण
device_initcall(serial_dev_init);


#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
/*
 * This is called very early, as part of console_init() (typically just after
 * समय_init()). This function is respondible क्रम trying to find a good
 * शेष console on serial ports. It tries to match the खोलो firmware
 * शेष output with one of the available serial console drivers that have
 * been probed earlier by find_legacy_serial_ports()
 */
अटल पूर्णांक __init check_legacy_serial_console(व्योम)
अणु
	काष्ठा device_node *prom_मानक_निकास = शून्य;
	पूर्णांक i, speed = 0, offset = 0;
	स्थिर अक्षर *name;
	स्थिर __be32 *spd;

	DBG(" -> check_legacy_serial_console()\n");

	/* The user has requested a console so this is alपढ़ोy set up. */
	अगर (म_माला(boot_command_line, "console=")) अणु
		DBG(" console was specified !\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!of_chosen) अणु
		DBG(" of_chosen is NULL !\n");
		वापस -ENODEV;
	पूर्ण

	अगर (legacy_serial_console < 0) अणु
		DBG(" legacy_serial_console not found !\n");
		वापस -ENODEV;
	पूर्ण
	/* We are getting a weird phandle from OF ... */
	/* ... So use the full path instead */
	name = of_get_property(of_chosen, "linux,stdout-path", शून्य);
	अगर (name == शून्य)
		name = of_get_property(of_chosen, "stdout-path", शून्य);
	अगर (name == शून्य) अणु
		DBG(" no stdout-path !\n");
		वापस -ENODEV;
	पूर्ण
	prom_मानक_निकास = of_find_node_by_path(name);
	अगर (!prom_मानक_निकास) अणु
		DBG(" can't find stdout package %s !\n", name);
		वापस -ENODEV;
	पूर्ण
	DBG("stdout is %pOF\n", prom_मानक_निकास);

	name = of_get_property(prom_मानक_निकास, "name", शून्य);
	अगर (!name) अणु
		DBG(" stdout package has no name !\n");
		जाओ not_found;
	पूर्ण
	spd = of_get_property(prom_मानक_निकास, "current-speed", शून्य);
	अगर (spd)
		speed = be32_to_cpup(spd);

	अगर (म_भेद(name, "serial") != 0)
		जाओ not_found;

	/* Look क्रम it in probed array */
	क्रम (i = 0; i < legacy_serial_count; i++) अणु
		अगर (prom_मानक_निकास != legacy_serial_infos[i].np)
			जारी;
		offset = i;
		speed = legacy_serial_infos[i].speed;
		अवरोध;
	पूर्ण
	अगर (i >= legacy_serial_count)
		जाओ not_found;

	of_node_put(prom_मानक_निकास);

	DBG("Found serial console at ttyS%d\n", offset);

	अगर (speed) अणु
		अटल अक्षर __initdata opt[16];
		प्र_लिखो(opt, "%d", speed);
		वापस add_preferred_console("ttyS", offset, opt);
	पूर्ण अन्यथा
		वापस add_preferred_console("ttyS", offset, शून्य);

 not_found:
	DBG("No preferred console found !\n");
	of_node_put(prom_मानक_निकास);
	वापस -ENODEV;
पूर्ण
console_initcall(check_legacy_serial_console);

#पूर्ण_अगर /* CONFIG_SERIAL_8250_CONSOLE */
