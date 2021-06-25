<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mmconfig-shared.c - Low-level direct PCI config space access via
 *                     MMCONFIG - common code between i386 and x86-64.
 *
 * This code करोes:
 * - known chipset handling
 * - ACPI decoding and validation
 *
 * Per-architecture code takes care of the mappings and accesses
 * themselves.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rculist.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/acpi.h>

#घोषणा PREFIX "PCI: "

/* Indicate अगर the mmcfg resources have been placed पूर्णांकo the resource table. */
अटल bool pci_mmcfg_running_state;
अटल bool pci_mmcfg_arch_init_failed;
अटल DEFINE_MUTEX(pci_mmcfg_lock);
#घोषणा pci_mmcfg_lock_held() lock_is_held(&(pci_mmcfg_lock).dep_map)

LIST_HEAD(pci_mmcfg_list);

अटल व्योम __init pci_mmconfig_हटाओ(काष्ठा pci_mmcfg_region *cfg)
अणु
	अगर (cfg->res.parent)
		release_resource(&cfg->res);
	list_del(&cfg->list);
	kमुक्त(cfg);
पूर्ण

अटल व्योम __init मुक्त_all_mmcfg(व्योम)
अणु
	काष्ठा pci_mmcfg_region *cfg, *पंचांगp;

	pci_mmcfg_arch_मुक्त();
	list_क्रम_each_entry_safe(cfg, पंचांगp, &pci_mmcfg_list, list)
		pci_mmconfig_हटाओ(cfg);
पूर्ण

अटल व्योम list_add_sorted(काष्ठा pci_mmcfg_region *new)
अणु
	काष्ठा pci_mmcfg_region *cfg;

	/* keep list sorted by segment and starting bus number */
	list_क्रम_each_entry_rcu(cfg, &pci_mmcfg_list, list, pci_mmcfg_lock_held()) अणु
		अगर (cfg->segment > new->segment ||
		    (cfg->segment == new->segment &&
		     cfg->start_bus >= new->start_bus)) अणु
			list_add_tail_rcu(&new->list, &cfg->list);
			वापस;
		पूर्ण
	पूर्ण
	list_add_tail_rcu(&new->list, &pci_mmcfg_list);
पूर्ण

अटल काष्ठा pci_mmcfg_region *pci_mmconfig_alloc(पूर्णांक segment, पूर्णांक start,
						   पूर्णांक end, u64 addr)
अणु
	काष्ठा pci_mmcfg_region *new;
	काष्ठा resource *res;

	अगर (addr == 0)
		वापस शून्य;

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	new->address = addr;
	new->segment = segment;
	new->start_bus = start;
	new->end_bus = end;

	res = &new->res;
	res->start = addr + PCI_MMCFG_BUS_OFFSET(start);
	res->end = addr + PCI_MMCFG_BUS_OFFSET(end + 1) - 1;
	res->flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	snम_लिखो(new->name, PCI_MMCFG_RESOURCE_NAME_LEN,
		 "PCI MMCONFIG %04x [bus %02x-%02x]", segment, start, end);
	res->name = new->name;

	वापस new;
पूर्ण

काष्ठा pci_mmcfg_region *__init pci_mmconfig_add(पूर्णांक segment, पूर्णांक start,
						 पूर्णांक end, u64 addr)
अणु
	काष्ठा pci_mmcfg_region *new;

	new = pci_mmconfig_alloc(segment, start, end, addr);
	अगर (new) अणु
		mutex_lock(&pci_mmcfg_lock);
		list_add_sorted(new);
		mutex_unlock(&pci_mmcfg_lock);

		pr_info(PREFIX
		       "MMCONFIG for domain %04x [bus %02x-%02x] at %pR "
		       "(base %#lx)\n",
		       segment, start, end, &new->res, (अचिन्हित दीर्घ)addr);
	पूर्ण

	वापस new;
पूर्ण

काष्ठा pci_mmcfg_region *pci_mmconfig_lookup(पूर्णांक segment, पूर्णांक bus)
अणु
	काष्ठा pci_mmcfg_region *cfg;

	list_क्रम_each_entry_rcu(cfg, &pci_mmcfg_list, list, pci_mmcfg_lock_held())
		अगर (cfg->segment == segment &&
		    cfg->start_bus <= bus && bus <= cfg->end_bus)
			वापस cfg;

	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *__init pci_mmcfg_e7520(व्योम)
अणु
	u32 win;
	raw_pci_ops->पढ़ो(0, 0, PCI_DEVFN(0, 0), 0xce, 2, &win);

	win = win & 0xf000;
	अगर (win == 0x0000 || win == 0xf000)
		वापस शून्य;

	अगर (pci_mmconfig_add(0, 0, 255, win << 16) == शून्य)
		वापस शून्य;

	वापस "Intel Corporation E7520 Memory Controller Hub";
पूर्ण

अटल स्थिर अक्षर *__init pci_mmcfg_पूर्णांकel_945(व्योम)
अणु
	u32 pciexbar, mask = 0, len = 0;

	raw_pci_ops->पढ़ो(0, 0, PCI_DEVFN(0, 0), 0x48, 4, &pciexbar);

	/* Enable bit */
	अगर (!(pciexbar & 1))
		वापस शून्य;

	/* Size bits */
	चयन ((pciexbar >> 1) & 3) अणु
	हाल 0:
		mask = 0xf0000000U;
		len  = 0x10000000U;
		अवरोध;
	हाल 1:
		mask = 0xf8000000U;
		len  = 0x08000000U;
		अवरोध;
	हाल 2:
		mask = 0xfc000000U;
		len  = 0x04000000U;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	/* Errata #2, things अवरोध when not aligned on a 256Mb boundary */
	/* Can only happen in 64M/128M mode */

	अगर ((pciexbar & mask) & 0x0fffffffU)
		वापस शून्य;

	/* Don't hit the APIC रेजिस्टरs and their मित्रs */
	अगर ((pciexbar & mask) >= 0xf0000000U)
		वापस शून्य;

	अगर (pci_mmconfig_add(0, 0, (len >> 20) - 1, pciexbar & mask) == शून्य)
		वापस शून्य;

	वापस "Intel Corporation 945G/GZ/P/PL Express Memory Controller Hub";
पूर्ण

अटल स्थिर अक्षर *__init pci_mmcfg_amd_fam10h(व्योम)
अणु
	u32 low, high, address;
	u64 base, msr;
	पूर्णांक i;
	अचिन्हित segnbits = 0, busnbits, end_bus;

	अगर (!(pci_probe & PCI_CHECK_ENABLE_AMD_MMCONF))
		वापस शून्य;

	address = MSR_FAM10H_MMIO_CONF_BASE;
	अगर (rdmsr_safe(address, &low, &high))
		वापस शून्य;

	msr = high;
	msr <<= 32;
	msr |= low;

	/* mmconfig is not enable */
	अगर (!(msr & FAM10H_MMIO_CONF_ENABLE))
		वापस शून्य;

	base = msr & (FAM10H_MMIO_CONF_BASE_MASK<<FAM10H_MMIO_CONF_BASE_SHIFT);

	busnbits = (msr >> FAM10H_MMIO_CONF_BUSRANGE_SHIFT) &
			 FAM10H_MMIO_CONF_BUSRANGE_MASK;

	/*
	 * only handle bus 0 ?
	 * need to skip it
	 */
	अगर (!busnbits)
		वापस शून्य;

	अगर (busnbits > 8) अणु
		segnbits = busnbits - 8;
		busnbits = 8;
	पूर्ण

	end_bus = (1 << busnbits) - 1;
	क्रम (i = 0; i < (1 << segnbits); i++)
		अगर (pci_mmconfig_add(i, 0, end_bus,
				     base + (1<<28) * i) == शून्य) अणु
			मुक्त_all_mmcfg();
			वापस शून्य;
		पूर्ण

	वापस "AMD Family 10h NB";
पूर्ण

अटल bool __initdata mcp55_checked;
अटल स्थिर अक्षर *__init pci_mmcfg_nvidia_mcp55(व्योम)
अणु
	पूर्णांक bus;
	पूर्णांक mcp55_mmconf_found = 0;

	अटल स्थिर u32 extcfg_regnum __initस्थिर	= 0x90;
	अटल स्थिर u32 extcfg_regsize __initस्थिर	= 4;
	अटल स्थिर u32 extcfg_enable_mask __initस्थिर	= 1 << 31;
	अटल स्थिर u32 extcfg_start_mask __initस्थिर	= 0xff << 16;
	अटल स्थिर पूर्णांक extcfg_start_shअगरt __initस्थिर	= 16;
	अटल स्थिर u32 extcfg_size_mask __initस्थिर	= 0x3 << 28;
	अटल स्थिर पूर्णांक extcfg_size_shअगरt __initस्थिर	= 28;
	अटल स्थिर पूर्णांक extcfg_sizebus[] __initस्थिर	= अणु
		0x100, 0x80, 0x40, 0x20
	पूर्ण;
	अटल स्थिर u32 extcfg_base_mask[] __initस्थिर	= अणु
		0x7ff8, 0x7ffc, 0x7ffe, 0x7fff
	पूर्ण;
	अटल स्थिर पूर्णांक extcfg_base_lshअगरt __initस्थिर	= 25;

	/*
	 * करो check अगर amd fam10h alपढ़ोy took over
	 */
	अगर (!acpi_disabled || !list_empty(&pci_mmcfg_list) || mcp55_checked)
		वापस शून्य;

	mcp55_checked = true;
	क्रम (bus = 0; bus < 256; bus++) अणु
		u64 base;
		u32 l, extcfg;
		u16 venकरोr, device;
		पूर्णांक start, size_index, end;

		raw_pci_ops->पढ़ो(0, bus, PCI_DEVFN(0, 0), 0, 4, &l);
		venकरोr = l & 0xffff;
		device = (l >> 16) & 0xffff;

		अगर (PCI_VENDOR_ID_NVIDIA != venकरोr || 0x0369 != device)
			जारी;

		raw_pci_ops->पढ़ो(0, bus, PCI_DEVFN(0, 0), extcfg_regnum,
				  extcfg_regsize, &extcfg);

		अगर (!(extcfg & extcfg_enable_mask))
			जारी;

		size_index = (extcfg & extcfg_size_mask) >> extcfg_size_shअगरt;
		base = extcfg & extcfg_base_mask[size_index];
		/* base could > 4G */
		base <<= extcfg_base_lshअगरt;
		start = (extcfg & extcfg_start_mask) >> extcfg_start_shअगरt;
		end = start + extcfg_sizebus[size_index] - 1;
		अगर (pci_mmconfig_add(0, start, end, base) == शून्य)
			जारी;
		mcp55_mmconf_found++;
	पूर्ण

	अगर (!mcp55_mmconf_found)
		वापस शून्य;

	वापस "nVidia MCP55";
पूर्ण

काष्ठा pci_mmcfg_hostbridge_probe अणु
	u32 bus;
	u32 devfn;
	u32 venकरोr;
	u32 device;
	स्थिर अक्षर *(*probe)(व्योम);
पूर्ण;

अटल स्थिर काष्ठा pci_mmcfg_hostbridge_probe pci_mmcfg_probes[] __initस्थिर = अणु
	अणु 0, PCI_DEVFN(0, 0), PCI_VENDOR_ID_INTEL,
	  PCI_DEVICE_ID_INTEL_E7520_MCH, pci_mmcfg_e7520 पूर्ण,
	अणु 0, PCI_DEVFN(0, 0), PCI_VENDOR_ID_INTEL,
	  PCI_DEVICE_ID_INTEL_82945G_HB, pci_mmcfg_पूर्णांकel_945 पूर्ण,
	अणु 0, PCI_DEVFN(0x18, 0), PCI_VENDOR_ID_AMD,
	  0x1200, pci_mmcfg_amd_fam10h पूर्ण,
	अणु 0xff, PCI_DEVFN(0, 0), PCI_VENDOR_ID_AMD,
	  0x1200, pci_mmcfg_amd_fam10h पूर्ण,
	अणु 0, PCI_DEVFN(0, 0), PCI_VENDOR_ID_NVIDIA,
	  0x0369, pci_mmcfg_nvidia_mcp55 पूर्ण,
पूर्ण;

अटल व्योम __init pci_mmcfg_check_end_bus_number(व्योम)
अणु
	काष्ठा pci_mmcfg_region *cfg, *cfgx;

	/* Fixup overlaps */
	list_क्रम_each_entry(cfg, &pci_mmcfg_list, list) अणु
		अगर (cfg->end_bus < cfg->start_bus)
			cfg->end_bus = 255;

		/* Don't access the list head ! */
		अगर (cfg->list.next == &pci_mmcfg_list)
			अवरोध;

		cfgx = list_entry(cfg->list.next, typeof(*cfg), list);
		अगर (cfg->end_bus >= cfgx->start_bus)
			cfg->end_bus = cfgx->start_bus - 1;
	पूर्ण
पूर्ण

अटल पूर्णांक __init pci_mmcfg_check_hostbridge(व्योम)
अणु
	u32 l;
	u32 bus, devfn;
	u16 venकरोr, device;
	पूर्णांक i;
	स्थिर अक्षर *name;

	अगर (!raw_pci_ops)
		वापस 0;

	मुक्त_all_mmcfg();

	क्रम (i = 0; i < ARRAY_SIZE(pci_mmcfg_probes); i++) अणु
		bus =  pci_mmcfg_probes[i].bus;
		devfn = pci_mmcfg_probes[i].devfn;
		raw_pci_ops->पढ़ो(0, bus, devfn, 0, 4, &l);
		venकरोr = l & 0xffff;
		device = (l >> 16) & 0xffff;

		name = शून्य;
		अगर (pci_mmcfg_probes[i].venकरोr == venकरोr &&
		    pci_mmcfg_probes[i].device == device)
			name = pci_mmcfg_probes[i].probe();

		अगर (name)
			pr_info(PREFIX "%s with MMCONFIG support\n", name);
	पूर्ण

	/* some end_bus_number is crazy, fix it */
	pci_mmcfg_check_end_bus_number();

	वापस !list_empty(&pci_mmcfg_list);
पूर्ण

अटल acpi_status check_mcfg_resource(काष्ठा acpi_resource *res, व्योम *data)
अणु
	काष्ठा resource *mcfg_res = data;
	काष्ठा acpi_resource_address64 address;
	acpi_status status;

	अगर (res->type == ACPI_RESOURCE_TYPE_FIXED_MEMORY32) अणु
		काष्ठा acpi_resource_fixed_memory32 *fixmem32 =
			&res->data.fixed_memory32;
		अगर (!fixmem32)
			वापस AE_OK;
		अगर ((mcfg_res->start >= fixmem32->address) &&
		    (mcfg_res->end < (fixmem32->address +
				      fixmem32->address_length))) अणु
			mcfg_res->flags = 1;
			वापस AE_CTRL_TERMINATE;
		पूर्ण
	पूर्ण
	अगर ((res->type != ACPI_RESOURCE_TYPE_ADDRESS32) &&
	    (res->type != ACPI_RESOURCE_TYPE_ADDRESS64))
		वापस AE_OK;

	status = acpi_resource_to_address64(res, &address);
	अगर (ACPI_FAILURE(status) ||
	   (address.address.address_length <= 0) ||
	   (address.resource_type != ACPI_MEMORY_RANGE))
		वापस AE_OK;

	अगर ((mcfg_res->start >= address.address.minimum) &&
	    (mcfg_res->end < (address.address.minimum + address.address.address_length))) अणु
		mcfg_res->flags = 1;
		वापस AE_CTRL_TERMINATE;
	पूर्ण
	वापस AE_OK;
पूर्ण

अटल acpi_status find_mboard_resource(acpi_handle handle, u32 lvl,
					व्योम *context, व्योम **rv)
अणु
	काष्ठा resource *mcfg_res = context;

	acpi_walk_resources(handle, METHOD_NAME__CRS,
			    check_mcfg_resource, context);

	अगर (mcfg_res->flags)
		वापस AE_CTRL_TERMINATE;

	वापस AE_OK;
पूर्ण

अटल bool is_acpi_reserved(u64 start, u64 end, क्रमागत e820_type not_used)
अणु
	काष्ठा resource mcfg_res;

	mcfg_res.start = start;
	mcfg_res.end = end - 1;
	mcfg_res.flags = 0;

	acpi_get_devices("PNP0C01", find_mboard_resource, &mcfg_res, शून्य);

	अगर (!mcfg_res.flags)
		acpi_get_devices("PNP0C02", find_mboard_resource, &mcfg_res,
				 शून्य);

	वापस mcfg_res.flags;
पूर्ण

प्रकार bool (*check_reserved_t)(u64 start, u64 end, क्रमागत e820_type type);

अटल bool __ref is_mmconf_reserved(check_reserved_t is_reserved,
				     काष्ठा pci_mmcfg_region *cfg,
				     काष्ठा device *dev, पूर्णांक with_e820)
अणु
	u64 addr = cfg->res.start;
	u64 size = resource_size(&cfg->res);
	u64 old_size = size;
	पूर्णांक num_buses;
	अक्षर *method = with_e820 ? "E820" : "ACPI motherboard resources";

	जबतक (!is_reserved(addr, addr + size, E820_TYPE_RESERVED)) अणु
		size >>= 1;
		अगर (size < (16UL<<20))
			अवरोध;
	पूर्ण

	अगर (size < (16UL<<20) && size != old_size)
		वापस 0;

	अगर (dev)
		dev_info(dev, "MMCONFIG at %pR reserved in %s\n",
			 &cfg->res, method);
	अन्यथा
		pr_info(PREFIX "MMCONFIG at %pR reserved in %s\n",
		       &cfg->res, method);

	अगर (old_size != size) अणु
		/* update end_bus */
		cfg->end_bus = cfg->start_bus + ((size>>20) - 1);
		num_buses = cfg->end_bus - cfg->start_bus + 1;
		cfg->res.end = cfg->res.start +
		    PCI_MMCFG_BUS_OFFSET(num_buses) - 1;
		snम_लिखो(cfg->name, PCI_MMCFG_RESOURCE_NAME_LEN,
			 "PCI MMCONFIG %04x [bus %02x-%02x]",
			 cfg->segment, cfg->start_bus, cfg->end_bus);

		अगर (dev)
			dev_info(dev,
				"MMCONFIG "
				"at %pR (base %#lx) (size reduced!)\n",
				&cfg->res, (अचिन्हित दीर्घ) cfg->address);
		अन्यथा
			pr_info(PREFIX
				"MMCONFIG for %04x [bus%02x-%02x] "
				"at %pR (base %#lx) (size reduced!)\n",
				cfg->segment, cfg->start_bus, cfg->end_bus,
				&cfg->res, (अचिन्हित दीर्घ) cfg->address);
	पूर्ण

	वापस 1;
पूर्ण

अटल bool __ref
pci_mmcfg_check_reserved(काष्ठा device *dev, काष्ठा pci_mmcfg_region *cfg, पूर्णांक early)
अणु
	अगर (!early && !acpi_disabled) अणु
		अगर (is_mmconf_reserved(is_acpi_reserved, cfg, dev, 0))
			वापस 1;

		अगर (dev)
			dev_info(dev, FW_INFO
				 "MMCONFIG at %pR not reserved in "
				 "ACPI motherboard resources\n",
				 &cfg->res);
		अन्यथा
			pr_info(FW_INFO PREFIX
			       "MMCONFIG at %pR not reserved in "
			       "ACPI motherboard resources\n",
			       &cfg->res);
	पूर्ण

	/*
	 * e820__mapped_all() is marked as __init.
	 * All entries from ACPI MCFG table have been checked at boot समय.
	 * For MCFG inक्रमmation स्थिरructed from hotpluggable host bridge's
	 * _CBA method, just assume it's reserved.
	 */
	अगर (pci_mmcfg_running_state)
		वापस 1;

	/* Don't try to करो this check unless configuration
	   type 1 is available. how about type 2 ?*/
	अगर (raw_pci_ops)
		वापस is_mmconf_reserved(e820__mapped_all, cfg, dev, 1);

	वापस 0;
पूर्ण

अटल व्योम __init pci_mmcfg_reject_broken(पूर्णांक early)
अणु
	काष्ठा pci_mmcfg_region *cfg;

	list_क्रम_each_entry(cfg, &pci_mmcfg_list, list) अणु
		अगर (pci_mmcfg_check_reserved(शून्य, cfg, early) == 0) अणु
			pr_info(PREFIX "not using MMCONFIG\n");
			मुक्त_all_mmcfg();
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init acpi_mcfg_check_entry(काष्ठा acpi_table_mcfg *mcfg,
					काष्ठा acpi_mcfg_allocation *cfg)
अणु
	अगर (cfg->address < 0xFFFFFFFF)
		वापस 0;

	अगर (!म_भेदन(mcfg->header.oem_id, "SGI", 3))
		वापस 0;

	अगर ((mcfg->header.revision >= 1) && (dmi_get_bios_year() >= 2010))
		वापस 0;

	pr_err(PREFIX "MCFG region for %04x [bus %02x-%02x] at %#llx "
	       "is above 4GB, ignored\n", cfg->pci_segment,
	       cfg->start_bus_number, cfg->end_bus_number, cfg->address);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __init pci_parse_mcfg(काष्ठा acpi_table_header *header)
अणु
	काष्ठा acpi_table_mcfg *mcfg;
	काष्ठा acpi_mcfg_allocation *cfg_table, *cfg;
	अचिन्हित दीर्घ i;
	पूर्णांक entries;

	अगर (!header)
		वापस -EINVAL;

	mcfg = (काष्ठा acpi_table_mcfg *)header;

	/* how many config काष्ठाures करो we have */
	मुक्त_all_mmcfg();
	entries = 0;
	i = header->length - माप(काष्ठा acpi_table_mcfg);
	जबतक (i >= माप(काष्ठा acpi_mcfg_allocation)) अणु
		entries++;
		i -= माप(काष्ठा acpi_mcfg_allocation);
	पूर्ण
	अगर (entries == 0) अणु
		pr_err(PREFIX "MMCONFIG has no entries\n");
		वापस -ENODEV;
	पूर्ण

	cfg_table = (काष्ठा acpi_mcfg_allocation *) &mcfg[1];
	क्रम (i = 0; i < entries; i++) अणु
		cfg = &cfg_table[i];
		अगर (acpi_mcfg_check_entry(mcfg, cfg)) अणु
			मुक्त_all_mmcfg();
			वापस -ENODEV;
		पूर्ण

		अगर (pci_mmconfig_add(cfg->pci_segment, cfg->start_bus_number,
				   cfg->end_bus_number, cfg->address) == शून्य) अणु
			pr_warn(PREFIX "no memory for MCFG entries\n");
			मुक्त_all_mmcfg();
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI_APEI
बाह्य पूर्णांक (*arch_apei_filter_addr)(पूर्णांक (*func)(__u64 start, __u64 size,
				     व्योम *data), व्योम *data);

अटल पूर्णांक pci_mmcfg_क्रम_each_region(पूर्णांक (*func)(__u64 start, __u64 size,
				     व्योम *data), व्योम *data)
अणु
	काष्ठा pci_mmcfg_region *cfg;
	पूर्णांक rc;

	अगर (list_empty(&pci_mmcfg_list))
		वापस 0;

	list_क्रम_each_entry(cfg, &pci_mmcfg_list, list) अणु
		rc = func(cfg->res.start, resource_size(&cfg->res), data);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
#घोषणा set_apei_filter() (arch_apei_filter_addr = pci_mmcfg_क्रम_each_region)
#अन्यथा
#घोषणा set_apei_filter()
#पूर्ण_अगर

अटल व्योम __init __pci_mmcfg_init(पूर्णांक early)
अणु
	pci_mmcfg_reject_broken(early);
	अगर (list_empty(&pci_mmcfg_list))
		वापस;

	अगर (pcibios_last_bus < 0) अणु
		स्थिर काष्ठा pci_mmcfg_region *cfg;

		list_क्रम_each_entry(cfg, &pci_mmcfg_list, list) अणु
			अगर (cfg->segment)
				अवरोध;
			pcibios_last_bus = cfg->end_bus;
		पूर्ण
	पूर्ण

	अगर (pci_mmcfg_arch_init())
		pci_probe = (pci_probe & ~PCI_PROBE_MASK) | PCI_PROBE_MMCONF;
	अन्यथा अणु
		मुक्त_all_mmcfg();
		pci_mmcfg_arch_init_failed = true;
	पूर्ण
पूर्ण

अटल पूर्णांक __initdata known_bridge;

व्योम __init pci_mmcfg_early_init(व्योम)
अणु
	अगर (pci_probe & PCI_PROBE_MMCONF) अणु
		अगर (pci_mmcfg_check_hostbridge())
			known_bridge = 1;
		अन्यथा
			acpi_table_parse(ACPI_SIG_MCFG, pci_parse_mcfg);
		__pci_mmcfg_init(1);

		set_apei_filter();
	पूर्ण
पूर्ण

व्योम __init pci_mmcfg_late_init(व्योम)
अणु
	/* MMCONFIG disabled */
	अगर ((pci_probe & PCI_PROBE_MMCONF) == 0)
		वापस;

	अगर (known_bridge)
		वापस;

	/* MMCONFIG hasn't been enabled yet, try again */
	अगर (pci_probe & PCI_PROBE_MASK & ~PCI_PROBE_MMCONF) अणु
		acpi_table_parse(ACPI_SIG_MCFG, pci_parse_mcfg);
		__pci_mmcfg_init(0);
	पूर्ण
पूर्ण

अटल पूर्णांक __init pci_mmcfg_late_insert_resources(व्योम)
अणु
	काष्ठा pci_mmcfg_region *cfg;

	pci_mmcfg_running_state = true;

	/* If we are not using MMCONFIG, करोn't insert the resources. */
	अगर ((pci_probe & PCI_PROBE_MMCONF) == 0)
		वापस 1;

	/*
	 * Attempt to insert the mmcfg resources but not with the busy flag
	 * marked so it won't cause request errors when __request_region is
	 * called.
	 */
	list_क्रम_each_entry(cfg, &pci_mmcfg_list, list)
		अगर (!cfg->res.parent)
			insert_resource(&iomem_resource, &cfg->res);

	वापस 0;
पूर्ण

/*
 * Perक्रमm MMCONFIG resource insertion after PCI initialization to allow क्रम
 * misprogrammed MCFG tables that state larger sizes but actually conflict
 * with other प्रणाली resources.
 */
late_initcall(pci_mmcfg_late_insert_resources);

/* Add MMCFG inक्रमmation क्रम host bridges */
पूर्णांक pci_mmconfig_insert(काष्ठा device *dev, u16 seg, u8 start, u8 end,
			phys_addr_t addr)
अणु
	पूर्णांक rc;
	काष्ठा resource *पंचांगp = शून्य;
	काष्ठा pci_mmcfg_region *cfg;

	अगर (!(pci_probe & PCI_PROBE_MMCONF) || pci_mmcfg_arch_init_failed)
		वापस -ENODEV;

	अगर (start > end)
		वापस -EINVAL;

	mutex_lock(&pci_mmcfg_lock);
	cfg = pci_mmconfig_lookup(seg, start);
	अगर (cfg) अणु
		अगर (cfg->end_bus < end)
			dev_info(dev, FW_INFO
				 "MMCONFIG for "
				 "domain %04x [bus %02x-%02x] "
				 "only partially covers this bridge\n",
				  cfg->segment, cfg->start_bus, cfg->end_bus);
		mutex_unlock(&pci_mmcfg_lock);
		वापस -EEXIST;
	पूर्ण

	अगर (!addr) अणु
		mutex_unlock(&pci_mmcfg_lock);
		वापस -EINVAL;
	पूर्ण

	rc = -EBUSY;
	cfg = pci_mmconfig_alloc(seg, start, end, addr);
	अगर (cfg == शून्य) अणु
		dev_warn(dev, "fail to add MMCONFIG (out of memory)\n");
		rc = -ENOMEM;
	पूर्ण अन्यथा अगर (!pci_mmcfg_check_reserved(dev, cfg, 0)) अणु
		dev_warn(dev, FW_BUG "MMCONFIG %pR isn't reserved\n",
			 &cfg->res);
	पूर्ण अन्यथा अणु
		/* Insert resource अगर it's not in boot stage */
		अगर (pci_mmcfg_running_state)
			पंचांगp = insert_resource_conflict(&iomem_resource,
						       &cfg->res);

		अगर (पंचांगp) अणु
			dev_warn(dev,
				 "MMCONFIG %pR conflicts with "
				 "%s %pR\n",
				 &cfg->res, पंचांगp->name, पंचांगp);
		पूर्ण अन्यथा अगर (pci_mmcfg_arch_map(cfg)) अणु
			dev_warn(dev, "fail to map MMCONFIG %pR.\n",
				 &cfg->res);
		पूर्ण अन्यथा अणु
			list_add_sorted(cfg);
			dev_info(dev, "MMCONFIG at %pR (base %#lx)\n",
				 &cfg->res, (अचिन्हित दीर्घ)addr);
			cfg = शून्य;
			rc = 0;
		पूर्ण
	पूर्ण

	अगर (cfg) अणु
		अगर (cfg->res.parent)
			release_resource(&cfg->res);
		kमुक्त(cfg);
	पूर्ण

	mutex_unlock(&pci_mmcfg_lock);

	वापस rc;
पूर्ण

/* Delete MMCFG inक्रमmation क्रम host bridges */
पूर्णांक pci_mmconfig_delete(u16 seg, u8 start, u8 end)
अणु
	काष्ठा pci_mmcfg_region *cfg;

	mutex_lock(&pci_mmcfg_lock);
	list_क्रम_each_entry_rcu(cfg, &pci_mmcfg_list, list)
		अगर (cfg->segment == seg && cfg->start_bus == start &&
		    cfg->end_bus == end) अणु
			list_del_rcu(&cfg->list);
			synchronize_rcu();
			pci_mmcfg_arch_unmap(cfg);
			अगर (cfg->res.parent)
				release_resource(&cfg->res);
			mutex_unlock(&pci_mmcfg_lock);
			kमुक्त(cfg);
			वापस 0;
		पूर्ण
	mutex_unlock(&pci_mmcfg_lock);

	वापस -ENOENT;
पूर्ण
