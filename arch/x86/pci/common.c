<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	Low-Level PCI Support क्रम PC
 *
 *	(c) 1999--2000 Martin Mares <mj@ucw.cz>
 */

#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irqकरोमुख्य.h>

अचिन्हित पूर्णांक pci_probe = PCI_PROBE_BIOS | PCI_PROBE_CONF1 | PCI_PROBE_CONF2 |
				PCI_PROBE_MMCONF;

अटल पूर्णांक pci_bf_sort;
पूर्णांक pci_routeirq;
पूर्णांक noioapicquirk;
#अगर_घोषित CONFIG_X86_REROUTE_FOR_BROKEN_BOOT_IRQS
पूर्णांक noioapicreroute = 0;
#अन्यथा
पूर्णांक noioapicreroute = 1;
#पूर्ण_अगर
पूर्णांक pcibios_last_bus = -1;
अचिन्हित दीर्घ pirq_table_addr;
स्थिर काष्ठा pci_raw_ops *__पढ़ो_mostly raw_pci_ops;
स्थिर काष्ठा pci_raw_ops *__पढ़ो_mostly raw_pci_ext_ops;

पूर्णांक raw_pci_पढ़ो(अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
						पूर्णांक reg, पूर्णांक len, u32 *val)
अणु
	अगर (करोमुख्य == 0 && reg < 256 && raw_pci_ops)
		वापस raw_pci_ops->पढ़ो(करोमुख्य, bus, devfn, reg, len, val);
	अगर (raw_pci_ext_ops)
		वापस raw_pci_ext_ops->पढ़ो(करोमुख्य, bus, devfn, reg, len, val);
	वापस -EINVAL;
पूर्ण

पूर्णांक raw_pci_ग_लिखो(अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
						पूर्णांक reg, पूर्णांक len, u32 val)
अणु
	अगर (करोमुख्य == 0 && reg < 256 && raw_pci_ops)
		वापस raw_pci_ops->ग_लिखो(करोमुख्य, bus, devfn, reg, len, val);
	अगर (raw_pci_ext_ops)
		वापस raw_pci_ext_ops->ग_लिखो(करोमुख्य, bus, devfn, reg, len, val);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	वापस raw_pci_पढ़ो(pci_करोमुख्य_nr(bus), bus->number,
				 devfn, where, size, value);
पूर्ण

अटल पूर्णांक pci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 value)
अणु
	वापस raw_pci_ग_लिखो(pci_करोमुख्य_nr(bus), bus->number,
				  devfn, where, size, value);
पूर्ण

काष्ठा pci_ops pci_root_ops = अणु
	.पढ़ो = pci_पढ़ो,
	.ग_लिखो = pci_ग_लिखो,
पूर्ण;

/*
 * This पूर्णांकerrupt-safe spinlock protects all accesses to PCI configuration
 * space, except क्रम the mmconfig (ECAM) based operations.
 */
DEFINE_RAW_SPINLOCK(pci_config_lock);

अटल पूर्णांक __init can_skip_ioresource_align(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	pci_probe |= PCI_CAN_SKIP_ISA_ALIGN;
	prपूर्णांकk(KERN_INFO "PCI: %s detected, can skip ISA alignment\n", d->ident);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id can_skip_pciprobe_dmi_table[] __initस्थिर = अणु
/*
 * Systems where PCI IO resource ISA alignment can be skipped
 * when the ISA enable bit in the bridge control is not set
 */
	अणु
		.callback = can_skip_ioresource_align,
		.ident = "IBM System x3800",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IBM"),
			DMI_MATCH(DMI_PRODUCT_NAME, "x3800"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = can_skip_ioresource_align,
		.ident = "IBM System x3850",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IBM"),
			DMI_MATCH(DMI_PRODUCT_NAME, "x3850"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = can_skip_ioresource_align,
		.ident = "IBM System x3950",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IBM"),
			DMI_MATCH(DMI_PRODUCT_NAME, "x3950"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम __init dmi_check_skip_isa_align(व्योम)
अणु
	dmi_check_प्रणाली(can_skip_pciprobe_dmi_table);
पूर्ण

अटल व्योम pcibios_fixup_device_resources(काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *rom_r = &dev->resource[PCI_ROM_RESOURCE];
	काष्ठा resource *bar_r;
	पूर्णांक bar;

	अगर (pci_probe & PCI_NOASSIGN_BARS) अणु
		/*
		* If the BIOS did not assign the BAR, zero out the
		* resource so the kernel करोesn't attempt to assign
		* it later on in pci_assign_unasचिन्हित_resources
		*/
		क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++) अणु
			bar_r = &dev->resource[bar];
			अगर (bar_r->start == 0 && bar_r->end != 0) अणु
				bar_r->flags = 0;
				bar_r->end = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pci_probe & PCI_NOASSIGN_ROMS) अणु
		अगर (rom_r->parent)
			वापस;
		अगर (rom_r->start) अणु
			/* we deal with BIOS asचिन्हित ROM later */
			वापस;
		पूर्ण
		rom_r->start = rom_r->end = rom_r->flags = 0;
	पूर्ण
पूर्ण

/*
 *  Called after each bus is probed, but beक्रमe its children
 *  are examined.
 */

व्योम pcibios_fixup_bus(काष्ठा pci_bus *b)
अणु
	काष्ठा pci_dev *dev;

	pci_पढ़ो_bridge_bases(b);
	list_क्रम_each_entry(dev, &b->devices, bus_list)
		pcibios_fixup_device_resources(dev);
पूर्ण

व्योम pcibios_add_bus(काष्ठा pci_bus *bus)
अणु
	acpi_pci_add_bus(bus);
पूर्ण

व्योम pcibios_हटाओ_bus(काष्ठा pci_bus *bus)
अणु
	acpi_pci_हटाओ_bus(bus);
पूर्ण

/*
 * Only use DMI inक्रमmation to set this अगर nothing was passed
 * on the kernel command line (which was parsed earlier).
 */

अटल पूर्णांक __init set_bf_sort(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (pci_bf_sort == pci_bf_sort_शेष) अणु
		pci_bf_sort = pci_dmi_bf;
		prपूर्णांकk(KERN_INFO "PCI: %s detected, enabling pci=bfsort.\n", d->ident);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init पढ़ो_dmi_type_b1(स्थिर काष्ठा dmi_header *dm,
				    व्योम *निजी_data)
अणु
	u8 *data = (u8 *)dm + 4;

	अगर (dm->type != 0xB1)
		वापस;
	अगर ((((*(u32 *)data) >> 9) & 0x03) == 0x01)
		set_bf_sort((स्थिर काष्ठा dmi_प्रणाली_id *)निजी_data);
पूर्ण

अटल पूर्णांक __init find_sort_method(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	dmi_walk(पढ़ो_dmi_type_b1, (व्योम *)d);
	वापस 0;
पूर्ण

/*
 * Enable rक्रमागतbering of PCI bus# ranges to reach all PCI busses (Cardbus)
 */
#अगर_घोषित __i386__
अटल पूर्णांक __init assign_all_busses(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	pci_probe |= PCI_ASSIGN_ALL_BUSSES;
	prपूर्णांकk(KERN_INFO "%s detected: enabling PCI bus# renumbering"
			" (pci=assign-busses)\n", d->ident);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init set_scan_all(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	prपूर्णांकk(KERN_INFO "PCI: %s detected, enabling pci=pcie_scan_all\n",
	       d->ident);
	pci_add_flags(PCI_SCAN_ALL_PCIE_DEVS);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id pciprobe_dmi_table[] __initस्थिर = अणु
#अगर_घोषित __i386__
/*
 * Laptops which need pci=assign-busses to see Cardbus cards
 */
	अणु
		.callback = assign_all_busses,
		.ident = "Samsung X20 Laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Samsung Electronics"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SX20S"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर		/* __i386__ */
	अणु
		.callback = set_bf_sort,
		.ident = "Dell PowerEdge 1950",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PowerEdge 1950"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "Dell PowerEdge 1955",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PowerEdge 1955"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "Dell PowerEdge 2900",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PowerEdge 2900"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "Dell PowerEdge 2950",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PowerEdge 2950"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "Dell PowerEdge R900",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PowerEdge R900"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = find_sort_method,
		.ident = "Dell System",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL20p G3",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL20p G3"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL20p G4",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL20p G4"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL30p G1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL30p G1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL25p G1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL25p G1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL35p G1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL35p G1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL45p G1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL45p G1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL45p G2",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL45p G2"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL460c G1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL460c G1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL465c G1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL465c G1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL480c G1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL480c G1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant BL685c G1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant BL685c G1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant DL360",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant DL360"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant DL380",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant DL380"),
		पूर्ण,
	पूर्ण,
#अगर_घोषित __i386__
	अणु
		.callback = assign_all_busses,
		.ident = "Compaq EVO N800c",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Compaq"),
			DMI_MATCH(DMI_PRODUCT_NAME, "EVO N800c"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant DL385 G2",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant DL385 G2"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_bf_sort,
		.ident = "HP ProLiant DL585 G2",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ProLiant DL585 G2"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_scan_all,
		.ident = "Stratus/NEC ftServer",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Stratus"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ftServer"),
		पूर्ण,
	पूर्ण,
        अणु
                .callback = set_scan_all,
                .ident = "Stratus/NEC ftServer",
                .matches = अणु
                        DMI_MATCH(DMI_SYS_VENDOR, "NEC"),
                        DMI_MATCH(DMI_PRODUCT_NAME, "Express5800/R32"),
                पूर्ण,
        पूर्ण,
        अणु
                .callback = set_scan_all,
                .ident = "Stratus/NEC ftServer",
                .matches = अणु
                        DMI_MATCH(DMI_SYS_VENDOR, "NEC"),
                        DMI_MATCH(DMI_PRODUCT_NAME, "Express5800/R31"),
                पूर्ण,
        पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम __init dmi_check_pciprobe(व्योम)
अणु
	dmi_check_प्रणाली(pciprobe_dmi_table);
पूर्ण

व्योम pcibios_scan_root(पूर्णांक busnum)
अणु
	काष्ठा pci_bus *bus;
	काष्ठा pci_sysdata *sd;
	LIST_HEAD(resources);

	sd = kzalloc(माप(*sd), GFP_KERNEL);
	अगर (!sd) अणु
		prपूर्णांकk(KERN_ERR "PCI: OOM, skipping PCI bus %02x\n", busnum);
		वापस;
	पूर्ण
	sd->node = x86_pci_root_bus_node(busnum);
	x86_pci_root_bus_resources(busnum, &resources);
	prपूर्णांकk(KERN_DEBUG "PCI: Probing PCI hardware (bus %02x)\n", busnum);
	bus = pci_scan_root_bus(शून्य, busnum, &pci_root_ops, sd, &resources);
	अगर (!bus) अणु
		pci_मुक्त_resource_list(&resources);
		kमुक्त(sd);
		वापस;
	पूर्ण
	pci_bus_add_devices(bus);
पूर्ण

व्योम __init pcibios_set_cache_line_size(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	/*
	 * Set PCI cacheline size to that of the CPU अगर the CPU has reported it.
	 * (For older CPUs that करोn't support cpuid, we se it to 32 bytes
	 * It's also good क्रम 386/486s (which actually have 16)
	 * as quite a few PCI devices करो not support smaller values.
	 */
	अगर (c->x86_clflush_size > 0) अणु
		pci_dfl_cache_line_size = c->x86_clflush_size >> 2;
		prपूर्णांकk(KERN_DEBUG "PCI: pci_cache_line_size set to %d bytes\n",
			pci_dfl_cache_line_size << 2);
	पूर्ण अन्यथा अणु
 		pci_dfl_cache_line_size = 32 >> 2;
		prपूर्णांकk(KERN_DEBUG "PCI: Unknown cacheline size. Setting to 32 bytes\n");
	पूर्ण
पूर्ण

पूर्णांक __init pcibios_init(व्योम)
अणु
	अगर (!raw_pci_ops && !raw_pci_ext_ops) अणु
		prपूर्णांकk(KERN_WARNING "PCI: System does not support PCI\n");
		वापस 0;
	पूर्ण

	pcibios_set_cache_line_size();
	pcibios_resource_survey();

	अगर (pci_bf_sort >= pci_क्रमce_bf)
		pci_sort_bपढ़ोthfirst();
	वापस 0;
पूर्ण

अक्षर *__init pcibios_setup(अक्षर *str)
अणु
	अगर (!म_भेद(str, "off")) अणु
		pci_probe = 0;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "bfsort")) अणु
		pci_bf_sort = pci_क्रमce_bf;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "nobfsort")) अणु
		pci_bf_sort = pci_क्रमce_nobf;
		वापस शून्य;
	पूर्ण
#अगर_घोषित CONFIG_PCI_BIOS
	अन्यथा अगर (!म_भेद(str, "bios")) अणु
		pci_probe = PCI_PROBE_BIOS;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "nobios")) अणु
		pci_probe &= ~PCI_PROBE_BIOS;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "biosirq")) अणु
		pci_probe |= PCI_BIOS_IRQ_SCAN;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेदन(str, "pirqaddr=", 9)) अणु
		pirq_table_addr = simple_म_से_अदीर्घ(str+9, शून्य, 0);
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_सूचीECT
	अन्यथा अगर (!म_भेद(str, "conf1")) अणु
		pci_probe = PCI_PROBE_CONF1 | PCI_NO_CHECKS;
		वापस शून्य;
	पूर्ण
	अन्यथा अगर (!म_भेद(str, "conf2")) अणु
		pci_probe = PCI_PROBE_CONF2 | PCI_NO_CHECKS;
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_MMCONFIG
	अन्यथा अगर (!म_भेद(str, "nommconf")) अणु
		pci_probe &= ~PCI_PROBE_MMCONF;
		वापस शून्य;
	पूर्ण
	अन्यथा अगर (!म_भेद(str, "check_enable_amd_mmconf")) अणु
		pci_probe |= PCI_CHECK_ENABLE_AMD_MMCONF;
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर
	अन्यथा अगर (!म_भेद(str, "noacpi")) अणु
		acpi_noirq_set();
		वापस शून्य;
	पूर्ण
	अन्यथा अगर (!म_भेद(str, "noearly")) अणु
		pci_probe |= PCI_PROBE_NOEARLY;
		वापस शून्य;
	पूर्ण
	अन्यथा अगर (!म_भेद(str, "usepirqmask")) अणु
		pci_probe |= PCI_USE_PIRQ_MASK;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेदन(str, "irqmask=", 8)) अणु
		pcibios_irq_mask = simple_म_से_दीर्घ(str+8, शून्य, 0);
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेदन(str, "lastbus=", 8)) अणु
		pcibios_last_bus = simple_म_से_दीर्घ(str+8, शून्य, 0);
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "rom")) अणु
		pci_probe |= PCI_ASSIGN_ROMS;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "norom")) अणु
		pci_probe |= PCI_NOASSIGN_ROMS;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "nobar")) अणु
		pci_probe |= PCI_NOASSIGN_BARS;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "assign-busses")) अणु
		pci_probe |= PCI_ASSIGN_ALL_BUSSES;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "use_crs")) अणु
		pci_probe |= PCI_USE__CRS;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "nocrs")) अणु
		pci_probe |= PCI_ROOT_NO_CRS;
		वापस शून्य;
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	पूर्ण अन्यथा अगर (!म_भेद(str, "big_root_window")) अणु
		pci_probe |= PCI_BIG_ROOT_WINDOW;
		वापस शून्य;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (!म_भेद(str, "routeirq")) अणु
		pci_routeirq = 1;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "skip_isa_align")) अणु
		pci_probe |= PCI_CAN_SKIP_ISA_ALIGN;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "noioapicquirk")) अणु
		noioapicquirk = 1;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "ioapicreroute")) अणु
		अगर (noioapicreroute != -1)
			noioapicreroute = 0;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "noioapicreroute")) अणु
		अगर (noioapicreroute != -1)
			noioapicreroute = 1;
		वापस शून्य;
	पूर्ण
	वापस str;
पूर्ण

अचिन्हित पूर्णांक pcibios_assign_all_busses(व्योम)
अणु
	वापस (pci_probe & PCI_ASSIGN_ALL_BUSSES) ? 1 : 0;
पूर्ण

अटल व्योम set_dev_करोमुख्य_options(काष्ठा pci_dev *pdev)
अणु
	अगर (is_vmd(pdev->bus))
		pdev->hotplug_user_indicators = 1;
पूर्ण

पूर्णांक pcibios_add_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_setup_rom *rom;
	काष्ठा irq_करोमुख्य *msiकरोm;
	काष्ठा setup_data *data;
	u64 pa_data;

	pa_data = boot_params.hdr.setup_data;
	जबतक (pa_data) अणु
		data = memremap(pa_data, माप(*rom), MEMREMAP_WB);
		अगर (!data)
			वापस -ENOMEM;

		अगर (data->type == SETUP_PCI) अणु
			rom = (काष्ठा pci_setup_rom *)data;

			अगर ((pci_करोमुख्य_nr(dev->bus) == rom->segment) &&
			    (dev->bus->number == rom->bus) &&
			    (PCI_SLOT(dev->devfn) == rom->device) &&
			    (PCI_FUNC(dev->devfn) == rom->function) &&
			    (dev->venकरोr == rom->venकरोr) &&
			    (dev->device == rom->devid)) अणु
				dev->rom = pa_data +
				      दुरत्व(काष्ठा pci_setup_rom, romdata);
				dev->romlen = rom->pcilen;
			पूर्ण
		पूर्ण
		pa_data = data->next;
		memunmap(data);
	पूर्ण
	set_dev_करोमुख्य_options(dev);

	/*
	 * Setup the initial MSI करोमुख्य of the device. If the underlying
	 * bus has a PCI/MSI irqकरोमुख्य associated use the bus करोमुख्य,
	 * otherwise set the शेष करोमुख्य. This ensures that special irq
	 * करोमुख्यs e.g. VMD are preserved. The शेष ensures initial
	 * operation अगर irq remapping is not active. If irq remapping is
	 * active it will overग_लिखो the करोमुख्य poपूर्णांकer when the device is
	 * associated to a remapping करोमुख्य.
	 */
	msiकरोm = dev_get_msi_करोमुख्य(&dev->bus->dev);
	अगर (!msiकरोm)
		msiकरोm = x86_pci_msi_शेष_करोमुख्य;
	dev_set_msi_करोमुख्य(&dev->dev, msiकरोm);
	वापस 0;
पूर्ण

पूर्णांक pcibios_enable_device(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	पूर्णांक err;

	अगर ((err = pci_enable_resources(dev, mask)) < 0)
		वापस err;

	अगर (!pci_dev_msi_enabled(dev))
		वापस pcibios_enable_irq(dev);
	वापस 0;
पूर्ण

व्योम pcibios_disable_device (काष्ठा pci_dev *dev)
अणु
	अगर (!pci_dev_msi_enabled(dev) && pcibios_disable_irq)
		pcibios_disable_irq(dev);
पूर्ण

#अगर_घोषित CONFIG_ACPI_HOTPLUG_IOAPIC
व्योम pcibios_release_device(काष्ठा pci_dev *dev)
अणु
	अगर (atomic_dec_वापस(&dev->enable_cnt) >= 0)
		pcibios_disable_device(dev);

पूर्ण
#पूर्ण_अगर

पूर्णांक pci_ext_cfg_avail(व्योम)
अणु
	अगर (raw_pci_ext_ops)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_VMD)
काष्ठा pci_dev *pci_real_dma_dev(काष्ठा pci_dev *dev)
अणु
	अगर (is_vmd(dev->bus))
		वापस to_pci_sysdata(dev->bus)->vmd_dev;

	वापस dev;
पूर्ण
#पूर्ण_अगर
