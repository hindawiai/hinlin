<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/topology.h>
#समावेश <linux/cpu.h>
#समावेश <linux/range.h>

#समावेश <यंत्र/amd_nb.h>
#समावेश <यंत्र/pci_x86.h>

#समावेश <यंत्र/pci-direct.h>

#समावेश "bus_numa.h"

#घोषणा AMD_NB_F0_NODE_ID			0x60
#घोषणा AMD_NB_F0_UNIT_ID			0x64
#घोषणा AMD_NB_F1_CONFIG_MAP_REG		0xe0

#घोषणा RANGE_NUM				16
#घोषणा AMD_NB_F1_CONFIG_MAP_RANGES		4

काष्ठा amd_hostbridge अणु
	u32 bus;
	u32 slot;
	u32 device;
पूर्ण;

/*
 * IMPORTANT NOTE:
 * hb_probes[] and early_root_info_init() is in मुख्यtenance mode.
 * It only supports K8, Fam10h, Fam11h, and Fam15h_00h-0fh .
 * Future processor will rely on inक्रमmation in ACPI.
 */
अटल काष्ठा amd_hostbridge hb_probes[] __initdata = अणु
	अणु 0, 0x18, 0x1100 पूर्ण, /* K8 */
	अणु 0, 0x18, 0x1200 पूर्ण, /* Family10h */
	अणु 0xff, 0, 0x1200 पूर्ण, /* Family10h */
	अणु 0, 0x18, 0x1300 पूर्ण, /* Family11h */
	अणु 0, 0x18, 0x1600 पूर्ण, /* Family15h */
पूर्ण;

अटल काष्ठा pci_root_info __init *find_pci_root_info(पूर्णांक node, पूर्णांक link)
अणु
	काष्ठा pci_root_info *info;

	/* find the position */
	list_क्रम_each_entry(info, &pci_root_infos, list)
		अगर (info->node == node && info->link == link)
			वापस info;

	वापस शून्य;
पूर्ण

/**
 * early_root_info_init()
 * called beक्रमe pcibios_scan_root and pci_scan_bus
 * fills the mp_bus_to_cpumask array based according
 * to the LDT Bus Number Registers found in the northbridge.
 */
अटल पूर्णांक __init early_root_info_init(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित bus;
	अचिन्हित slot;
	पूर्णांक node;
	पूर्णांक link;
	पूर्णांक def_node;
	पूर्णांक def_link;
	काष्ठा pci_root_info *info;
	u32 reg;
	u64 start;
	u64 end;
	काष्ठा range range[RANGE_NUM];
	u64 val;
	u32 address;
	bool found;
	काष्ठा resource fam10h_mmconf_res, *fam10h_mmconf;
	u64 fam10h_mmconf_start;
	u64 fam10h_mmconf_end;

	अगर (!early_pci_allowed())
		वापस -1;

	found = false;
	क्रम (i = 0; i < ARRAY_SIZE(hb_probes); i++) अणु
		u32 id;
		u16 device;
		u16 venकरोr;

		bus = hb_probes[i].bus;
		slot = hb_probes[i].slot;
		id = पढ़ो_pci_config(bus, slot, 0, PCI_VENDOR_ID);
		venकरोr = id & 0xffff;
		device = (id>>16) & 0xffff;

		अगर (venकरोr != PCI_VENDOR_ID_AMD &&
		    venकरोr != PCI_VENDOR_ID_HYGON)
			जारी;

		अगर (hb_probes[i].device == device) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस 0;

	/*
	 * We should learn topology and routing inक्रमmation from _PXM and
	 * _CRS methods in the ACPI namespace.  We extract node numbers
	 * here to work around BIOSes that करोn't supply _PXM.
	 */
	क्रम (i = 0; i < AMD_NB_F1_CONFIG_MAP_RANGES; i++) अणु
		पूर्णांक min_bus;
		पूर्णांक max_bus;
		reg = पढ़ो_pci_config(bus, slot, 1,
				AMD_NB_F1_CONFIG_MAP_REG + (i << 2));

		/* Check अगर that रेजिस्टर is enabled क्रम bus range */
		अगर ((reg & 7) != 3)
			जारी;

		min_bus = (reg >> 16) & 0xff;
		max_bus = (reg >> 24) & 0xff;
		node = (reg >> 4) & 0x07;
		link = (reg >> 8) & 0x03;

		alloc_pci_root_info(min_bus, max_bus, node, link);
	पूर्ण

	/*
	 * The following code extracts routing inक्रमmation क्रम use on old
	 * प्रणालीs where Linux करोesn't स्वतःmatically use host bridge _CRS
	 * methods (or when the user specअगरies "pci=nocrs").
	 *
	 * We only करो this through Fam11h, because _CRS should be enough on
	 * newer प्रणालीs.
	 */
	अगर (boot_cpu_data.x86 > 0x11)
		वापस 0;

	/* get the शेष node and link क्रम left over res */
	reg = पढ़ो_pci_config(bus, slot, 0, AMD_NB_F0_NODE_ID);
	def_node = (reg >> 8) & 0x07;
	reg = पढ़ो_pci_config(bus, slot, 0, AMD_NB_F0_UNIT_ID);
	def_link = (reg >> 8) & 0x03;

	स_रखो(range, 0, माप(range));
	add_range(range, RANGE_NUM, 0, 0, 0xffff + 1);
	/* io port resource */
	क्रम (i = 0; i < 4; i++) अणु
		reg = पढ़ो_pci_config(bus, slot, 1, 0xc0 + (i << 3));
		अगर (!(reg & 3))
			जारी;

		start = reg & 0xfff000;
		reg = पढ़ो_pci_config(bus, slot, 1, 0xc4 + (i << 3));
		node = reg & 0x07;
		link = (reg >> 4) & 0x03;
		end = (reg & 0xfff000) | 0xfff;

		info = find_pci_root_info(node, link);
		अगर (!info)
			जारी; /* not found */

		prपूर्णांकk(KERN_DEBUG "node %d link %d: io port [%llx, %llx]\n",
		       node, link, start, end);

		/* kernel only handle 16 bit only */
		अगर (end > 0xffff)
			end = 0xffff;
		update_res(info, start, end, IORESOURCE_IO, 1);
		subtract_range(range, RANGE_NUM, start, end + 1);
	पूर्ण
	/* add left over io port range to def node/link, [0, 0xffff] */
	/* find the position */
	info = find_pci_root_info(def_node, def_link);
	अगर (info) अणु
		क्रम (i = 0; i < RANGE_NUM; i++) अणु
			अगर (!range[i].end)
				जारी;

			update_res(info, range[i].start, range[i].end - 1,
				   IORESOURCE_IO, 1);
		पूर्ण
	पूर्ण

	स_रखो(range, 0, माप(range));
	/* 0xfd00000000-0xffffffffff क्रम HT */
	end = cap_resource((0xfdULL<<32) - 1);
	end++;
	add_range(range, RANGE_NUM, 0, 0, end);

	/* need to take out [0, TOM) क्रम RAM*/
	address = MSR_K8_TOP_MEM1;
	rdmsrl(address, val);
	end = (val & 0xffffff800000ULL);
	prपूर्णांकk(KERN_INFO "TOM: %016llx aka %lldM\n", end, end>>20);
	अगर (end < (1ULL<<32))
		subtract_range(range, RANGE_NUM, 0, end);

	/* get mmconfig */
	fam10h_mmconf = amd_get_mmconfig_range(&fam10h_mmconf_res);
	/* need to take out mmconf range */
	अगर (fam10h_mmconf) अणु
		prपूर्णांकk(KERN_DEBUG "Fam 10h mmconf %pR\n", fam10h_mmconf);
		fam10h_mmconf_start = fam10h_mmconf->start;
		fam10h_mmconf_end = fam10h_mmconf->end;
		subtract_range(range, RANGE_NUM, fam10h_mmconf_start,
				 fam10h_mmconf_end + 1);
	पूर्ण अन्यथा अणु
		fam10h_mmconf_start = 0;
		fam10h_mmconf_end = 0;
	पूर्ण

	/* mmio resource */
	क्रम (i = 0; i < 8; i++) अणु
		reg = पढ़ो_pci_config(bus, slot, 1, 0x80 + (i << 3));
		अगर (!(reg & 3))
			जारी;

		start = reg & 0xffffff00; /* 39:16 on 31:8*/
		start <<= 8;
		reg = पढ़ो_pci_config(bus, slot, 1, 0x84 + (i << 3));
		node = reg & 0x07;
		link = (reg >> 4) & 0x03;
		end = (reg & 0xffffff00);
		end <<= 8;
		end |= 0xffff;

		info = find_pci_root_info(node, link);

		अगर (!info)
			जारी;

		prपूर्णांकk(KERN_DEBUG "node %d link %d: mmio [%llx, %llx]",
		       node, link, start, end);
		/*
		 * some sick allocation would have range overlap with fam10h
		 * mmconf range, so need to update start and end.
		 */
		अगर (fam10h_mmconf_end) अणु
			पूर्णांक changed = 0;
			u64 endx = 0;
			अगर (start >= fam10h_mmconf_start &&
			    start <= fam10h_mmconf_end) अणु
				start = fam10h_mmconf_end + 1;
				changed = 1;
			पूर्ण

			अगर (end >= fam10h_mmconf_start &&
			    end <= fam10h_mmconf_end) अणु
				end = fam10h_mmconf_start - 1;
				changed = 1;
			पूर्ण

			अगर (start < fam10h_mmconf_start &&
			    end > fam10h_mmconf_end) अणु
				/* we got a hole */
				endx = fam10h_mmconf_start - 1;
				update_res(info, start, endx, IORESOURCE_MEM, 0);
				subtract_range(range, RANGE_NUM, start,
						 endx + 1);
				prपूर्णांकk(KERN_CONT " ==> [%llx, %llx]", start, endx);
				start = fam10h_mmconf_end + 1;
				changed = 1;
			पूर्ण
			अगर (changed) अणु
				अगर (start <= end) अणु
					prपूर्णांकk(KERN_CONT " %s [%llx, %llx]", endx ? "and" : "==>", start, end);
				पूर्ण अन्यथा अणु
					prपूर्णांकk(KERN_CONT "%s\n", endx?"":" ==> none");
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण

		update_res(info, cap_resource(start), cap_resource(end),
				 IORESOURCE_MEM, 1);
		subtract_range(range, RANGE_NUM, start, end + 1);
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण

	/* need to take out [4G, TOM2) क्रम RAM*/
	/* SYS_CFG */
	address = MSR_AMD64_SYSCFG;
	rdmsrl(address, val);
	/* TOP_MEM2 is enabled? */
	अगर (val & (1<<21)) अणु
		/* TOP_MEM2 */
		address = MSR_K8_TOP_MEM2;
		rdmsrl(address, val);
		end = (val & 0xffffff800000ULL);
		prपूर्णांकk(KERN_INFO "TOM2: %016llx aka %lldM\n", end, end>>20);
		subtract_range(range, RANGE_NUM, 1ULL<<32, end);
	पूर्ण

	/*
	 * add left over mmio range to def node/link ?
	 * that is tricky, just record range in from start_min to 4G
	 */
	info = find_pci_root_info(def_node, def_link);
	अगर (info) अणु
		क्रम (i = 0; i < RANGE_NUM; i++) अणु
			अगर (!range[i].end)
				जारी;

			update_res(info, cap_resource(range[i].start),
				   cap_resource(range[i].end - 1),
				   IORESOURCE_MEM, 1);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(info, &pci_root_infos, list) अणु
		पूर्णांक busnum;
		काष्ठा pci_root_res *root_res;

		busnum = info->busn.start;
		prपूर्णांकk(KERN_DEBUG "bus: %pR on node %x link %x\n",
		       &info->busn, info->node, info->link);
		list_क्रम_each_entry(root_res, &info->resources, list)
			prपूर्णांकk(KERN_DEBUG "bus: %02x %pR\n",
				       busnum, &root_res->res);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ENABLE_CF8_EXT_CFG      (1ULL << 46)

अटल पूर्णांक amd_bus_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	u64 reg;

	rdmsrl(MSR_AMD64_NB_CFG, reg);
	अगर (!(reg & ENABLE_CF8_EXT_CFG)) अणु
		reg |= ENABLE_CF8_EXT_CFG;
		wrmsrl(MSR_AMD64_NB_CFG, reg);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init pci_enable_pci_io_ecs(व्योम)
अणु
#अगर_घोषित CONFIG_AMD_NB
	अचिन्हित पूर्णांक i, n;

	क्रम (n = i = 0; !n && amd_nb_bus_dev_ranges[i].dev_limit; ++i) अणु
		u8 bus = amd_nb_bus_dev_ranges[i].bus;
		u8 slot = amd_nb_bus_dev_ranges[i].dev_base;
		u8 limit = amd_nb_bus_dev_ranges[i].dev_limit;

		क्रम (; slot < limit; ++slot) अणु
			u32 val = पढ़ो_pci_config(bus, slot, 3, 0);

			अगर (!early_is_amd_nb(val))
				जारी;

			val = पढ़ो_pci_config(bus, slot, 3, 0x8c);
			अगर (!(val & (ENABLE_CF8_EXT_CFG >> 32))) अणु
				val |= ENABLE_CF8_EXT_CFG >> 32;
				ग_लिखो_pci_config(bus, slot, 3, 0x8c, val);
			पूर्ण
			++n;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init pci_io_ecs_init(व्योम)
अणु
	पूर्णांक ret;

	/* assume all cpus from fam10h have IO ECS */
	अगर (boot_cpu_data.x86 < 0x10)
		वापस 0;

	/* Try the PCI method first. */
	अगर (early_pci_allowed())
		pci_enable_pci_io_ecs();

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "pci/amd_bus:online",
				amd_bus_cpu_online, शून्य);
	WARN_ON(ret < 0);

	pci_probe |= PCI_HAS_IO_ECS;

	वापस 0;
पूर्ण

अटल पूर्णांक __init amd_postcore_init(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_HYGON)
		वापस 0;

	early_root_info_init();
	pci_io_ecs_init();

	वापस 0;
पूर्ण

postcore_initcall(amd_postcore_init);
