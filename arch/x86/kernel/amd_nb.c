<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Shared support code क्रम AMD K8 northbridges and derivatives.
 * Copyright 2006 Andi Kleen, SUSE Lअसल.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci_ids.h>
#समावेश <यंत्र/amd_nb.h>

#घोषणा PCI_DEVICE_ID_AMD_17H_ROOT	0x1450
#घोषणा PCI_DEVICE_ID_AMD_17H_M10H_ROOT	0x15d0
#घोषणा PCI_DEVICE_ID_AMD_17H_M30H_ROOT	0x1480
#घोषणा PCI_DEVICE_ID_AMD_17H_M60H_ROOT	0x1630
#घोषणा PCI_DEVICE_ID_AMD_17H_DF_F4	0x1464
#घोषणा PCI_DEVICE_ID_AMD_17H_M10H_DF_F4 0x15ec
#घोषणा PCI_DEVICE_ID_AMD_17H_M30H_DF_F4 0x1494
#घोषणा PCI_DEVICE_ID_AMD_17H_M60H_DF_F4 0x144c
#घोषणा PCI_DEVICE_ID_AMD_17H_M70H_DF_F4 0x1444
#घोषणा PCI_DEVICE_ID_AMD_19H_DF_F4	0x1654

/* Protect the PCI config रेजिस्टर pairs used क्रम SMN and DF indirect access. */
अटल DEFINE_MUTEX(smn_mutex);

अटल u32 *flush_words;

अटल स्थिर काष्ठा pci_device_id amd_root_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_ROOT) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M10H_ROOT) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M30H_ROOT) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M60H_ROOT) पूर्ण,
	अणुपूर्ण
पूर्ण;

#घोषणा PCI_DEVICE_ID_AMD_CNB17H_F4     0x1704

अटल स्थिर काष्ठा pci_device_id amd_nb_misc_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_MISC) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_MISC) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_M10H_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_M30H_NB_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_M60H_NB_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_16H_NB_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_16H_M30H_NB_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_DF_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M10H_DF_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M30H_DF_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M60H_DF_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CNB17H_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M70H_DF_F3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_19H_DF_F3) पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id amd_nb_link_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_M30H_NB_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_M60H_NB_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_16H_NB_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_16H_M30H_NB_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_DF_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M10H_DF_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M30H_DF_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M60H_DF_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_17H_M70H_DF_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_19H_DF_F4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CNB17H_F4) पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id hygon_root_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HYGON, PCI_DEVICE_ID_AMD_17H_ROOT) पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id hygon_nb_misc_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HYGON, PCI_DEVICE_ID_AMD_17H_DF_F3) पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id hygon_nb_link_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HYGON, PCI_DEVICE_ID_AMD_17H_DF_F4) पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा amd_nb_bus_dev_range amd_nb_bus_dev_ranges[] __initस्थिर = अणु
	अणु 0x00, 0x18, 0x20 पूर्ण,
	अणु 0xff, 0x00, 0x20 पूर्ण,
	अणु 0xfe, 0x00, 0x20 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा amd_northbridge_info amd_northbridges;

u16 amd_nb_num(व्योम)
अणु
	वापस amd_northbridges.num;
पूर्ण
EXPORT_SYMBOL_GPL(amd_nb_num);

bool amd_nb_has_feature(अचिन्हित पूर्णांक feature)
अणु
	वापस ((amd_northbridges.flags & feature) == feature);
पूर्ण
EXPORT_SYMBOL_GPL(amd_nb_has_feature);

काष्ठा amd_northbridge *node_to_amd_nb(पूर्णांक node)
अणु
	वापस (node < amd_northbridges.num) ? &amd_northbridges.nb[node] : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(node_to_amd_nb);

अटल काष्ठा pci_dev *next_northbridge(काष्ठा pci_dev *dev,
					स्थिर काष्ठा pci_device_id *ids)
अणु
	करो अणु
		dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, dev);
		अगर (!dev)
			अवरोध;
	पूर्ण जबतक (!pci_match_id(ids, dev));
	वापस dev;
पूर्ण

अटल पूर्णांक __amd_smn_rw(u16 node, u32 address, u32 *value, bool ग_लिखो)
अणु
	काष्ठा pci_dev *root;
	पूर्णांक err = -ENODEV;

	अगर (node >= amd_northbridges.num)
		जाओ out;

	root = node_to_amd_nb(node)->root;
	अगर (!root)
		जाओ out;

	mutex_lock(&smn_mutex);

	err = pci_ग_लिखो_config_dword(root, 0x60, address);
	अगर (err) अणु
		pr_warn("Error programming SMN address 0x%x.\n", address);
		जाओ out_unlock;
	पूर्ण

	err = (ग_लिखो ? pci_ग_लिखो_config_dword(root, 0x64, *value)
		     : pci_पढ़ो_config_dword(root, 0x64, value));
	अगर (err)
		pr_warn("Error %s SMN address 0x%x.\n",
			(ग_लिखो ? "writing to" : "reading from"), address);

out_unlock:
	mutex_unlock(&smn_mutex);

out:
	वापस err;
पूर्ण

पूर्णांक amd_smn_पढ़ो(u16 node, u32 address, u32 *value)
अणु
	वापस __amd_smn_rw(node, address, value, false);
पूर्ण
EXPORT_SYMBOL_GPL(amd_smn_पढ़ो);

पूर्णांक amd_smn_ग_लिखो(u16 node, u32 address, u32 value)
अणु
	वापस __amd_smn_rw(node, address, &value, true);
पूर्ण
EXPORT_SYMBOL_GPL(amd_smn_ग_लिखो);

/*
 * Data Fabric Indirect Access uses FICAA/FICAD.
 *
 * Fabric Indirect Configuration Access Address (FICAA): Conकाष्ठाed based
 * on the device's Instance Id and the PCI function and रेजिस्टर offset of
 * the desired रेजिस्टर.
 *
 * Fabric Indirect Configuration Access Data (FICAD): There are FICAD LO
 * and FICAD HI रेजिस्टरs but so far we only need the LO रेजिस्टर.
 */
पूर्णांक amd_df_indirect_पढ़ो(u16 node, u8 func, u16 reg, u8 instance_id, u32 *lo)
अणु
	काष्ठा pci_dev *F4;
	u32 ficaa;
	पूर्णांक err = -ENODEV;

	अगर (node >= amd_northbridges.num)
		जाओ out;

	F4 = node_to_amd_nb(node)->link;
	अगर (!F4)
		जाओ out;

	ficaa  = 1;
	ficaa |= reg & 0x3FC;
	ficaa |= (func & 0x7) << 11;
	ficaa |= instance_id << 16;

	mutex_lock(&smn_mutex);

	err = pci_ग_लिखो_config_dword(F4, 0x5C, ficaa);
	अगर (err) अणु
		pr_warn("Error writing DF Indirect FICAA, FICAA=0x%x\n", ficaa);
		जाओ out_unlock;
	पूर्ण

	err = pci_पढ़ो_config_dword(F4, 0x98, lo);
	अगर (err)
		pr_warn("Error reading DF Indirect FICAD LO, FICAA=0x%x.\n", ficaa);

out_unlock:
	mutex_unlock(&smn_mutex);

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(amd_df_indirect_पढ़ो);

पूर्णांक amd_cache_northbridges(व्योम)
अणु
	स्थिर काष्ठा pci_device_id *misc_ids = amd_nb_misc_ids;
	स्थिर काष्ठा pci_device_id *link_ids = amd_nb_link_ids;
	स्थिर काष्ठा pci_device_id *root_ids = amd_root_ids;
	काष्ठा pci_dev *root, *misc, *link;
	काष्ठा amd_northbridge *nb;
	u16 roots_per_misc = 0;
	u16 misc_count = 0;
	u16 root_count = 0;
	u16 i, j;

	अगर (amd_northbridges.num)
		वापस 0;

	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON) अणु
		root_ids = hygon_root_ids;
		misc_ids = hygon_nb_misc_ids;
		link_ids = hygon_nb_link_ids;
	पूर्ण

	misc = शून्य;
	जबतक ((misc = next_northbridge(misc, misc_ids)) != शून्य)
		misc_count++;

	अगर (!misc_count)
		वापस -ENODEV;

	root = शून्य;
	जबतक ((root = next_northbridge(root, root_ids)) != शून्य)
		root_count++;

	अगर (root_count) अणु
		roots_per_misc = root_count / misc_count;

		/*
		 * There should be _exactly_ N roots क्रम each DF/SMN
		 * पूर्णांकerface.
		 */
		अगर (!roots_per_misc || (root_count % roots_per_misc)) अणु
			pr_info("Unsupported AMD DF/PCI configuration found\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	nb = kसुस्मृति(misc_count, माप(काष्ठा amd_northbridge), GFP_KERNEL);
	अगर (!nb)
		वापस -ENOMEM;

	amd_northbridges.nb = nb;
	amd_northbridges.num = misc_count;

	link = misc = root = शून्य;
	क्रम (i = 0; i < amd_northbridges.num; i++) अणु
		node_to_amd_nb(i)->root = root =
			next_northbridge(root, root_ids);
		node_to_amd_nb(i)->misc = misc =
			next_northbridge(misc, misc_ids);
		node_to_amd_nb(i)->link = link =
			next_northbridge(link, link_ids);

		/*
		 * If there are more PCI root devices than data fabric/
		 * प्रणाली management network पूर्णांकerfaces, then the (N)
		 * PCI roots per DF/SMN पूर्णांकerface are functionally the
		 * same (क्रम DF/SMN access) and N-1 are redundant.  N-1
		 * PCI roots should be skipped per DF/SMN पूर्णांकerface so
		 * the following DF/SMN पूर्णांकerfaces get mapped to
		 * correct PCI roots.
		 */
		क्रम (j = 1; j < roots_per_misc; j++)
			root = next_northbridge(root, root_ids);
	पूर्ण

	अगर (amd_gart_present())
		amd_northbridges.flags |= AMD_NB_GART;

	/*
	 * Check क्रम L3 cache presence.
	 */
	अगर (!cpuid_edx(0x80000006))
		वापस 0;

	/*
	 * Some CPU families support L3 Cache Index Disable. There are some
	 * limitations because of E382 and E388 on family 0x10.
	 */
	अगर (boot_cpu_data.x86 == 0x10 &&
	    boot_cpu_data.x86_model >= 0x8 &&
	    (boot_cpu_data.x86_model > 0x9 ||
	     boot_cpu_data.x86_stepping >= 0x1))
		amd_northbridges.flags |= AMD_NB_L3_INDEX_DISABLE;

	अगर (boot_cpu_data.x86 == 0x15)
		amd_northbridges.flags |= AMD_NB_L3_INDEX_DISABLE;

	/* L3 cache partitioning is supported on family 0x15 */
	अगर (boot_cpu_data.x86 == 0x15)
		amd_northbridges.flags |= AMD_NB_L3_PARTITIONING;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(amd_cache_northbridges);

/*
 * Ignores subdevice/subvenकरोr but as far as I can figure out
 * they're useless anyways
 */
bool __init early_is_amd_nb(u32 device)
अणु
	स्थिर काष्ठा pci_device_id *misc_ids = amd_nb_misc_ids;
	स्थिर काष्ठा pci_device_id *id;
	u32 venकरोr = device & 0xffff;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_HYGON)
		वापस false;

	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON)
		misc_ids = hygon_nb_misc_ids;

	device >>= 16;
	क्रम (id = misc_ids; id->venकरोr; id++)
		अगर (venकरोr == id->venकरोr && device == id->device)
			वापस true;
	वापस false;
पूर्ण

काष्ठा resource *amd_get_mmconfig_range(काष्ठा resource *res)
अणु
	u32 address;
	u64 base, msr;
	अचिन्हित पूर्णांक segn_busn_bits;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_HYGON)
		वापस शून्य;

	/* assume all cpus from fam10h have mmconfig */
	अगर (boot_cpu_data.x86 < 0x10)
		वापस शून्य;

	address = MSR_FAM10H_MMIO_CONF_BASE;
	rdmsrl(address, msr);

	/* mmconfig is not enabled */
	अगर (!(msr & FAM10H_MMIO_CONF_ENABLE))
		वापस शून्य;

	base = msr & (FAM10H_MMIO_CONF_BASE_MASK<<FAM10H_MMIO_CONF_BASE_SHIFT);

	segn_busn_bits = (msr >> FAM10H_MMIO_CONF_BUSRANGE_SHIFT) &
			 FAM10H_MMIO_CONF_BUSRANGE_MASK;

	res->flags = IORESOURCE_MEM;
	res->start = base;
	res->end = base + (1ULL<<(segn_busn_bits + 20)) - 1;
	वापस res;
पूर्ण

पूर्णांक amd_get_subcaches(पूर्णांक cpu)
अणु
	काष्ठा pci_dev *link = node_to_amd_nb(topology_die_id(cpu))->link;
	अचिन्हित पूर्णांक mask;

	अगर (!amd_nb_has_feature(AMD_NB_L3_PARTITIONING))
		वापस 0;

	pci_पढ़ो_config_dword(link, 0x1d4, &mask);

	वापस (mask >> (4 * cpu_data(cpu).cpu_core_id)) & 0xf;
पूर्ण

पूर्णांक amd_set_subcaches(पूर्णांक cpu, अचिन्हित दीर्घ mask)
अणु
	अटल अचिन्हित पूर्णांक reset, ban;
	काष्ठा amd_northbridge *nb = node_to_amd_nb(topology_die_id(cpu));
	अचिन्हित पूर्णांक reg;
	पूर्णांक cuid;

	अगर (!amd_nb_has_feature(AMD_NB_L3_PARTITIONING) || mask > 0xf)
		वापस -EINVAL;

	/* अगर necessary, collect reset state of L3 partitioning and BAN mode */
	अगर (reset == 0) अणु
		pci_पढ़ो_config_dword(nb->link, 0x1d4, &reset);
		pci_पढ़ो_config_dword(nb->misc, 0x1b8, &ban);
		ban &= 0x180000;
	पूर्ण

	/* deactivate BAN mode अगर any subcaches are to be disabled */
	अगर (mask != 0xf) अणु
		pci_पढ़ो_config_dword(nb->misc, 0x1b8, &reg);
		pci_ग_लिखो_config_dword(nb->misc, 0x1b8, reg & ~0x180000);
	पूर्ण

	cuid = cpu_data(cpu).cpu_core_id;
	mask <<= 4 * cuid;
	mask |= (0xf ^ (1 << cuid)) << 26;

	pci_ग_लिखो_config_dword(nb->link, 0x1d4, mask);

	/* reset BAN mode अगर L3 partitioning वापसed to reset state */
	pci_पढ़ो_config_dword(nb->link, 0x1d4, &reg);
	अगर (reg == reset) अणु
		pci_पढ़ो_config_dword(nb->misc, 0x1b8, &reg);
		reg &= ~0x180000;
		pci_ग_लिखो_config_dword(nb->misc, 0x1b8, reg | ban);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम amd_cache_gart(व्योम)
अणु
	u16 i;

	अगर (!amd_nb_has_feature(AMD_NB_GART))
		वापस;

	flush_words = kदो_स्मृति_array(amd_northbridges.num, माप(u32), GFP_KERNEL);
	अगर (!flush_words) अणु
		amd_northbridges.flags &= ~AMD_NB_GART;
		pr_notice("Cannot initialize GART flush words, GART support disabled\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i != amd_northbridges.num; i++)
		pci_पढ़ो_config_dword(node_to_amd_nb(i)->misc, 0x9c, &flush_words[i]);
पूर्ण

व्योम amd_flush_garts(व्योम)
अणु
	पूर्णांक flushed, i;
	अचिन्हित दीर्घ flags;
	अटल DEFINE_SPINLOCK(gart_lock);

	अगर (!amd_nb_has_feature(AMD_NB_GART))
		वापस;

	/*
	 * Aव्योम races between AGP and IOMMU. In theory it's not needed
	 * but I'm not sure if the hardware won't lose flush requests
	 * when another is pending. This whole thing is so expensive anyways
	 * that it करोesn't matter to serialize more. -AK
	 */
	spin_lock_irqsave(&gart_lock, flags);
	flushed = 0;
	क्रम (i = 0; i < amd_northbridges.num; i++) अणु
		pci_ग_लिखो_config_dword(node_to_amd_nb(i)->misc, 0x9c,
				       flush_words[i] | 1);
		flushed++;
	पूर्ण
	क्रम (i = 0; i < amd_northbridges.num; i++) अणु
		u32 w;
		/* Make sure the hardware actually executed the flush*/
		क्रम (;;) अणु
			pci_पढ़ो_config_dword(node_to_amd_nb(i)->misc,
					      0x9c, &w);
			अगर (!(w & 1))
				अवरोध;
			cpu_relax();
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&gart_lock, flags);
	अगर (!flushed)
		pr_notice("nothing to flush?\n");
पूर्ण
EXPORT_SYMBOL_GPL(amd_flush_garts);

अटल व्योम __fix_erratum_688(व्योम *info)
अणु
#घोषणा MSR_AMD64_IC_CFG 0xC0011021

	msr_set_bit(MSR_AMD64_IC_CFG, 3);
	msr_set_bit(MSR_AMD64_IC_CFG, 14);
पूर्ण

/* Apply erratum 688 fix so machines without a BIOS fix work. */
अटल __init व्योम fix_erratum_688(व्योम)
अणु
	काष्ठा pci_dev *F4;
	u32 val;

	अगर (boot_cpu_data.x86 != 0x14)
		वापस;

	अगर (!amd_northbridges.num)
		वापस;

	F4 = node_to_amd_nb(0)->link;
	अगर (!F4)
		वापस;

	अगर (pci_पढ़ो_config_dword(F4, 0x164, &val))
		वापस;

	अगर (val & BIT(2))
		वापस;

	on_each_cpu(__fix_erratum_688, शून्य, 0);

	pr_info("x86/cpu/AMD: CPU erratum 688 worked around\n");
पूर्ण

अटल __init पूर्णांक init_amd_nbs(व्योम)
अणु
	amd_cache_northbridges();
	amd_cache_gart();

	fix_erratum_688();

	वापस 0;
पूर्ण

/* This has to go after the PCI subप्रणाली */
fs_initcall(init_amd_nbs);
