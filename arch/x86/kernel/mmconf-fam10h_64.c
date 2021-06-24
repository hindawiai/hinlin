<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AMD Family 10h mmconfig enablement
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/dmi.h>
#समावेश <linux/range.h>

#समावेश <यंत्र/pci-direct.h>
#समावेश <linux/sort.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/mmconfig.h>
#समावेश <यंत्र/pci_x86.h>

काष्ठा pci_hostbridge_probe अणु
	u32 bus;
	u32 slot;
	u32 venकरोr;
	u32 device;
पूर्ण;

अटल u64 fam10h_pci_mmconf_base;

अटल काष्ठा pci_hostbridge_probe pci_probes[] = अणु
	अणु 0, 0x18, PCI_VENDOR_ID_AMD, 0x1200 पूर्ण,
	अणु 0xff, 0, PCI_VENDOR_ID_AMD, 0x1200 पूर्ण,
पूर्ण;

अटल पूर्णांक cmp_range(स्थिर व्योम *x1, स्थिर व्योम *x2)
अणु
	स्थिर काष्ठा range *r1 = x1;
	स्थिर काष्ठा range *r2 = x2;
	पूर्णांक start1, start2;

	start1 = r1->start >> 32;
	start2 = r2->start >> 32;

	वापस start1 - start2;
पूर्ण

#घोषणा MMCONF_UNIT (1ULL << FAM10H_MMIO_CONF_BASE_SHIFT)
#घोषणा MMCONF_MASK (~(MMCONF_UNIT - 1))
#घोषणा MMCONF_SIZE (MMCONF_UNIT << 8)
/* need to aव्योम (0xfd<<32), (0xfe<<32), and (0xff<<32), ht used space */
#घोषणा FAM10H_PCI_MMCONF_BASE (0xfcULL<<32)
#घोषणा BASE_VALID(b) ((b) + MMCONF_SIZE <= (0xfdULL<<32) || (b) >= (1ULL<<40))
अटल व्योम get_fam10h_pci_mmconf_base(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित bus;
	अचिन्हित slot;
	पूर्णांक found;

	u64 val;
	u32 address;
	u64 tom2;
	u64 base = FAM10H_PCI_MMCONF_BASE;

	पूर्णांक hi_mmio_num;
	काष्ठा range range[8];

	/* only try to get setting from BSP */
	अगर (fam10h_pci_mmconf_base)
		वापस;

	अगर (!early_pci_allowed())
		वापस;

	found = 0;
	क्रम (i = 0; i < ARRAY_SIZE(pci_probes); i++) अणु
		u32 id;
		u16 device;
		u16 venकरोr;

		bus = pci_probes[i].bus;
		slot = pci_probes[i].slot;
		id = पढ़ो_pci_config(bus, slot, 0, PCI_VENDOR_ID);

		venकरोr = id & 0xffff;
		device = (id>>16) & 0xffff;
		अगर (pci_probes[i].venकरोr == venकरोr &&
		    pci_probes[i].device == device) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस;

	/* SYS_CFG */
	address = MSR_AMD64_SYSCFG;
	rdmsrl(address, val);

	/* TOP_MEM2 is not enabled? */
	अगर (!(val & (1<<21))) अणु
		tom2 = 1ULL << 32;
	पूर्ण अन्यथा अणु
		/* TOP_MEM2 */
		address = MSR_K8_TOP_MEM2;
		rdmsrl(address, val);
		tom2 = max(val & 0xffffff800000ULL, 1ULL << 32);
	पूर्ण

	अगर (base <= tom2)
		base = (tom2 + 2 * MMCONF_UNIT - 1) & MMCONF_MASK;

	/*
	 * need to check अगर the range is in the high mmio range that is
	 * above 4G
	 */
	hi_mmio_num = 0;
	क्रम (i = 0; i < 8; i++) अणु
		u32 reg;
		u64 start;
		u64 end;
		reg = पढ़ो_pci_config(bus, slot, 1, 0x80 + (i << 3));
		अगर (!(reg & 3))
			जारी;

		start = (u64)(reg & 0xffffff00) << 8; /* 39:16 on 31:8*/
		reg = पढ़ो_pci_config(bus, slot, 1, 0x84 + (i << 3));
		end = ((u64)(reg & 0xffffff00) << 8) | 0xffff; /* 39:16 on 31:8*/

		अगर (end < tom2)
			जारी;

		range[hi_mmio_num].start = start;
		range[hi_mmio_num].end = end;
		hi_mmio_num++;
	पूर्ण

	अगर (!hi_mmio_num)
		जाओ out;

	/* sort the range */
	sort(range, hi_mmio_num, माप(काष्ठा range), cmp_range, शून्य);

	अगर (range[hi_mmio_num - 1].end < base)
		जाओ out;
	अगर (range[0].start > base + MMCONF_SIZE)
		जाओ out;

	/* need to find one winकरोw */
	base = (range[0].start & MMCONF_MASK) - MMCONF_UNIT;
	अगर ((base > tom2) && BASE_VALID(base))
		जाओ out;
	base = (range[hi_mmio_num - 1].end + MMCONF_UNIT) & MMCONF_MASK;
	अगर (BASE_VALID(base))
		जाओ out;
	/* need to find winकरोw between ranges */
	क्रम (i = 1; i < hi_mmio_num; i++) अणु
		base = (range[i - 1].end + MMCONF_UNIT) & MMCONF_MASK;
		val = range[i].start & MMCONF_MASK;
		अगर (val >= base + MMCONF_SIZE && BASE_VALID(base))
			जाओ out;
	पूर्ण
	वापस;

out:
	fam10h_pci_mmconf_base = base;
पूर्ण

व्योम fam10h_check_enable_mmcfg(व्योम)
अणु
	u64 val;
	u32 address;

	अगर (!(pci_probe & PCI_CHECK_ENABLE_AMD_MMCONF))
		वापस;

	address = MSR_FAM10H_MMIO_CONF_BASE;
	rdmsrl(address, val);

	/* try to make sure that AP's setting is identical to BSP setting */
	अगर (val & FAM10H_MMIO_CONF_ENABLE) अणु
		अचिन्हित busnbits;
		busnbits = (val >> FAM10H_MMIO_CONF_BUSRANGE_SHIFT) &
			FAM10H_MMIO_CONF_BUSRANGE_MASK;

		/* only trust the one handle 256 buses, अगर acpi=off */
		अगर (!acpi_pci_disabled || busnbits >= 8) अणु
			u64 base = val & MMCONF_MASK;

			अगर (!fam10h_pci_mmconf_base) अणु
				fam10h_pci_mmconf_base = base;
				वापस;
			पूर्ण अन्यथा अगर (fam10h_pci_mmconf_base ==  base)
				वापस;
		पूर्ण
	पूर्ण

	/*
	 * अगर it is not enabled, try to enable it and assume only one segment
	 * with 256 buses
	 */
	get_fam10h_pci_mmconf_base();
	अगर (!fam10h_pci_mmconf_base) अणु
		pci_probe &= ~PCI_CHECK_ENABLE_AMD_MMCONF;
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Enable MMCONFIG on AMD Family 10h\n");
	val &= ~((FAM10H_MMIO_CONF_BASE_MASK<<FAM10H_MMIO_CONF_BASE_SHIFT) |
	     (FAM10H_MMIO_CONF_BUSRANGE_MASK<<FAM10H_MMIO_CONF_BUSRANGE_SHIFT));
	val |= fam10h_pci_mmconf_base | (8 << FAM10H_MMIO_CONF_BUSRANGE_SHIFT) |
	       FAM10H_MMIO_CONF_ENABLE;
	wrmsrl(address, val);
पूर्ण

अटल पूर्णांक __init set_check_enable_amd_mmconf(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
        pci_probe |= PCI_CHECK_ENABLE_AMD_MMCONF;
        वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर mmconf_dmi_table[] = अणु
        अणु
                .callback = set_check_enable_amd_mmconf,
                .ident = "Sun Microsystems Machine",
                .matches = अणु
                        DMI_MATCH(DMI_SYS_VENDOR, "Sun Microsystems"),
                पूर्ण,
        पूर्ण,
	अणुपूर्ण
पूर्ण;

/* Called from a non __init function, but only on the BSP. */
व्योम __ref check_enable_amd_mmconf_dmi(व्योम)
अणु
	dmi_check_प्रणाली(mmconf_dmi_table);
पूर्ण
