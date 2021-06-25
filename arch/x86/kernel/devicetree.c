<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Architecture specअगरic OF callbacks.
 */
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/initrd.h>

#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/prom.h>

__initdata u64 initial_dtb;
अक्षर __initdata cmd_line[COMMAND_LINE_SIZE];

पूर्णांक __initdata of_ioapic;

व्योम __init early_init_dt_scan_chosen_arch(अचिन्हित दीर्घ node)
अणु
	BUG();
पूर्ण

व्योम __init early_init_dt_add_memory_arch(u64 base, u64 size)
अणु
	BUG();
पूर्ण

व्योम __init add_dtb(u64 data)
अणु
	initial_dtb = data + दुरत्व(काष्ठा setup_data, data);
पूर्ण

/*
 * CE4100 ids. Will be moved to machine_device_initcall() once we have it.
 */
अटल काष्ठा of_device_id __initdata ce4100_ids[] = अणु
	अणु .compatible = "intel,ce4100-cp", पूर्ण,
	अणु .compatible = "isa", पूर्ण,
	अणु .compatible = "pci", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init add_bus_probe(व्योम)
अणु
	अगर (!of_have_populated_dt())
		वापस 0;

	वापस of_platक्रमm_bus_probe(शून्य, ce4100_ids, शून्य);
पूर्ण
device_initcall(add_bus_probe);

#अगर_घोषित CONFIG_PCI
काष्ठा device_node *pcibios_get_phb_of_node(काष्ठा pci_bus *bus)
अणु
	काष्ठा device_node *np;

	क्रम_each_node_by_type(np, "pci") अणु
		स्थिर व्योम *prop;
		अचिन्हित पूर्णांक bus_min;

		prop = of_get_property(np, "bus-range", शून्य);
		अगर (!prop)
			जारी;
		bus_min = be32_to_cpup(prop);
		अगर (bus->number == bus_min)
			वापस np;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक x86_of_pci_irq_enable(काष्ठा pci_dev *dev)
अणु
	u32 virq;
	पूर्णांक ret;
	u8 pin;

	ret = pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	अगर (ret)
		वापस ret;
	अगर (!pin)
		वापस 0;

	virq = of_irq_parse_and_map_pci(dev, 0, 0);
	अगर (virq == 0)
		वापस -EINVAL;
	dev->irq = virq;
	वापस 0;
पूर्ण

अटल व्योम x86_of_pci_irq_disable(काष्ठा pci_dev *dev)
अणु
पूर्ण

व्योम x86_of_pci_init(व्योम)
अणु
	pcibios_enable_irq = x86_of_pci_irq_enable;
	pcibios_disable_irq = x86_of_pci_irq_disable;
पूर्ण
#पूर्ण_अगर

अटल व्योम __init dtb_setup_hpet(व्योम)
अणु
#अगर_घोषित CONFIG_HPET_TIMER
	काष्ठा device_node *dn;
	काष्ठा resource r;
	पूर्णांक ret;

	dn = of_find_compatible_node(शून्य, शून्य, "intel,ce4100-hpet");
	अगर (!dn)
		वापस;
	ret = of_address_to_resource(dn, 0, &r);
	अगर (ret) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	hpet_address = r.start;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_X86_LOCAL_APIC

अटल व्योम __init dtb_cpu_setup(व्योम)
अणु
	काष्ठा device_node *dn;
	u32 apic_id, version;
	पूर्णांक ret;

	version = GET_APIC_VERSION(apic_पढ़ो(APIC_LVR));
	क्रम_each_of_cpu_node(dn) अणु
		ret = of_property_पढ़ो_u32(dn, "reg", &apic_id);
		अगर (ret < 0) अणु
			pr_warn("%pOF: missing local APIC ID\n", dn);
			जारी;
		पूर्ण
		generic_processor_info(apic_id, version);
	पूर्ण
पूर्ण

अटल व्योम __init dtb_lapic_setup(व्योम)
अणु
	काष्ठा device_node *dn;
	काष्ठा resource r;
	अचिन्हित दीर्घ lapic_addr = APIC_DEFAULT_PHYS_BASE;
	पूर्णांक ret;

	dn = of_find_compatible_node(शून्य, शून्य, "intel,ce4100-lapic");
	अगर (dn) अणु
		ret = of_address_to_resource(dn, 0, &r);
		अगर (WARN_ON(ret))
			वापस;
		lapic_addr = r.start;
	पूर्ण

	/* Did the boot loader setup the local APIC ? */
	अगर (!boot_cpu_has(X86_FEATURE_APIC)) अणु
		अगर (apic_क्रमce_enable(lapic_addr))
			वापस;
	पूर्ण
	smp_found_config = 1;
	pic_mode = 1;
	रेजिस्टर_lapic_address(lapic_addr);
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_LOCAL_APIC */

#अगर_घोषित CONFIG_X86_IO_APIC
अटल अचिन्हित पूर्णांक ioapic_id;

काष्ठा of_ioapic_type अणु
	u32 out_type;
	u32 is_level;
	u32 active_low;
पूर्ण;

अटल काष्ठा of_ioapic_type of_ioapic_type[] =
अणु
	अणु
		.out_type	= IRQ_TYPE_EDGE_FALLING,
		.is_level	= 0,
		.active_low	= 1,
	पूर्ण,
	अणु
		.out_type	= IRQ_TYPE_LEVEL_HIGH,
		.is_level	= 1,
		.active_low	= 0,
	पूर्ण,
	अणु
		.out_type	= IRQ_TYPE_LEVEL_LOW,
		.is_level	= 1,
		.active_low	= 1,
	पूर्ण,
	अणु
		.out_type	= IRQ_TYPE_EDGE_RISING,
		.is_level	= 0,
		.active_low	= 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dt_irqकरोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा irq_fwspec *fwspec = (काष्ठा irq_fwspec *)arg;
	काष्ठा of_ioapic_type *it;
	काष्ठा irq_alloc_info पंचांगp;
	पूर्णांक type_index;

	अगर (WARN_ON(fwspec->param_count < 2))
		वापस -EINVAL;

	type_index = fwspec->param[1];
	अगर (type_index >= ARRAY_SIZE(of_ioapic_type))
		वापस -EINVAL;

	it = &of_ioapic_type[type_index];
	ioapic_set_alloc_attr(&पंचांगp, NUMA_NO_NODE, it->is_level, it->active_low);
	पंचांगp.devid = mpc_ioapic_id(mp_irqकरोमुख्य_ioapic_idx(करोमुख्य));
	पंचांगp.ioapic.pin = fwspec->param[0];

	वापस mp_irqकरोमुख्य_alloc(करोमुख्य, virq, nr_irqs, &पंचांगp);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ioapic_irq_करोमुख्य_ops = अणु
	.alloc		= dt_irqकरोमुख्य_alloc,
	.मुक्त		= mp_irqकरोमुख्य_मुक्त,
	.activate	= mp_irqकरोमुख्य_activate,
	.deactivate	= mp_irqकरोमुख्य_deactivate,
पूर्ण;

अटल व्योम __init dtb_add_ioapic(काष्ठा device_node *dn)
अणु
	काष्ठा resource r;
	पूर्णांक ret;
	काष्ठा ioapic_करोमुख्य_cfg cfg = अणु
		.type = IOAPIC_DOMAIN_DYNAMIC,
		.ops = &ioapic_irq_करोमुख्य_ops,
		.dev = dn,
	पूर्ण;

	ret = of_address_to_resource(dn, 0, &r);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Can't obtain address from device node %pOF.\n", dn);
		वापस;
	पूर्ण
	mp_रेजिस्टर_ioapic(++ioapic_id, r.start, gsi_top, &cfg);
पूर्ण

अटल व्योम __init dtb_ioapic_setup(व्योम)
अणु
	काष्ठा device_node *dn;

	क्रम_each_compatible_node(dn, शून्य, "intel,ce4100-ioapic")
		dtb_add_ioapic(dn);

	अगर (nr_ioapics) अणु
		of_ioapic = 1;
		वापस;
	पूर्ण
	prपूर्णांकk(KERN_ERR "Error: No information about IO-APIC in OF.\n");
पूर्ण
#अन्यथा
अटल व्योम __init dtb_ioapic_setup(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम __init dtb_apic_setup(व्योम)
अणु
#अगर_घोषित CONFIG_X86_LOCAL_APIC
	dtb_lapic_setup();
	dtb_cpu_setup();
#पूर्ण_अगर
	dtb_ioapic_setup();
पूर्ण

#अगर_घोषित CONFIG_OF_EARLY_FLATTREE
अटल व्योम __init x86_flattree_get_config(व्योम)
अणु
	u32 size, map_len;
	व्योम *dt;

	अगर (!initial_dtb)
		वापस;

	map_len = max(PAGE_SIZE - (initial_dtb & ~PAGE_MASK), (u64)128);

	dt = early_memremap(initial_dtb, map_len);
	size = fdt_totalsize(dt);
	अगर (map_len < size) अणु
		early_memunmap(dt, map_len);
		dt = early_memremap(initial_dtb, size);
		map_len = size;
	पूर्ण

	early_init_dt_verअगरy(dt);
	unflatten_and_copy_device_tree();
	early_memunmap(dt, map_len);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम x86_flattree_get_config(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम __init x86_dtb_init(व्योम)
अणु
	x86_flattree_get_config();

	अगर (!of_have_populated_dt())
		वापस;

	dtb_setup_hpet();
	dtb_apic_setup();
पूर्ण
