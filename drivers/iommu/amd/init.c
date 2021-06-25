<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2010 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <jroedel@suse.de>
 *         Leo Duran <leo.duran@amd.com>
 */

#घोषणा pr_fmt(fmt)     "AMD-Vi: " fmt
#घोषणा dev_fmt(fmt)    pr_fmt(fmt)

#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/list.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/msi.h>
#समावेश <linux/irq.h>
#समावेश <linux/amd-iommu.h>
#समावेश <linux/export.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/gart.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/iommu_table.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/set_memory.h>

#समावेश <linux/crash_dump.h>

#समावेश "amd_iommu.h"
#समावेश "../irq_remapping.h"

/*
 * definitions क्रम the ACPI scanning code
 */
#घोषणा IVRS_HEADER_LENGTH 48

#घोषणा ACPI_IVHD_TYPE_MAX_SUPPORTED	0x40
#घोषणा ACPI_IVMD_TYPE_ALL              0x20
#घोषणा ACPI_IVMD_TYPE                  0x21
#घोषणा ACPI_IVMD_TYPE_RANGE            0x22

#घोषणा IVHD_DEV_ALL                    0x01
#घोषणा IVHD_DEV_SELECT                 0x02
#घोषणा IVHD_DEV_SELECT_RANGE_START     0x03
#घोषणा IVHD_DEV_RANGE_END              0x04
#घोषणा IVHD_DEV_ALIAS                  0x42
#घोषणा IVHD_DEV_ALIAS_RANGE            0x43
#घोषणा IVHD_DEV_EXT_SELECT             0x46
#घोषणा IVHD_DEV_EXT_SELECT_RANGE       0x47
#घोषणा IVHD_DEV_SPECIAL		0x48
#घोषणा IVHD_DEV_ACPI_HID		0xf0

#घोषणा UID_NOT_PRESENT                 0
#घोषणा UID_IS_INTEGER                  1
#घोषणा UID_IS_CHARACTER                2

#घोषणा IVHD_SPECIAL_IOAPIC		1
#घोषणा IVHD_SPECIAL_HPET		2

#घोषणा IVHD_FLAG_HT_TUN_EN_MASK        0x01
#घोषणा IVHD_FLAG_PASSPW_EN_MASK        0x02
#घोषणा IVHD_FLAG_RESPASSPW_EN_MASK     0x04
#घोषणा IVHD_FLAG_ISOC_EN_MASK          0x08

#घोषणा IVMD_FLAG_EXCL_RANGE            0x08
#घोषणा IVMD_FLAG_IW                    0x04
#घोषणा IVMD_FLAG_IR                    0x02
#घोषणा IVMD_FLAG_UNITY_MAP             0x01

#घोषणा ACPI_DEVFLAG_INITPASS           0x01
#घोषणा ACPI_DEVFLAG_EXTINT             0x02
#घोषणा ACPI_DEVFLAG_NMI                0x04
#घोषणा ACPI_DEVFLAG_SYSMGT1            0x10
#घोषणा ACPI_DEVFLAG_SYSMGT2            0x20
#घोषणा ACPI_DEVFLAG_LINT0              0x40
#घोषणा ACPI_DEVFLAG_LINT1              0x80
#घोषणा ACPI_DEVFLAG_ATSDIS             0x10000000

#घोषणा LOOP_TIMEOUT	100000
/*
 * ACPI table definitions
 *
 * These data काष्ठाures are laid over the table to parse the important values
 * out of it.
 */

बाह्य स्थिर काष्ठा iommu_ops amd_iommu_ops;

/*
 * काष्ठाure describing one IOMMU in the ACPI table. Typically followed by one
 * or more ivhd_entrys.
 */
काष्ठा ivhd_header अणु
	u8 type;
	u8 flags;
	u16 length;
	u16 devid;
	u16 cap_ptr;
	u64 mmio_phys;
	u16 pci_seg;
	u16 info;
	u32 efr_attr;

	/* Following only valid on IVHD type 11h and 40h */
	u64 efr_reg; /* Exact copy of MMIO_EXT_FEATURES */
	u64 res;
पूर्ण __attribute__((packed));

/*
 * A device entry describing which devices a specअगरic IOMMU translates and
 * which requestor ids they use.
 */
काष्ठा ivhd_entry अणु
	u8 type;
	u16 devid;
	u8 flags;
	u32 ext;
	u32 hidh;
	u64 cid;
	u8 uidf;
	u8 uidl;
	u8 uid;
पूर्ण __attribute__((packed));

/*
 * An AMD IOMMU memory definition काष्ठाure. It defines things like exclusion
 * ranges क्रम devices and regions that should be unity mapped.
 */
काष्ठा ivmd_header अणु
	u8 type;
	u8 flags;
	u16 length;
	u16 devid;
	u16 aux;
	u64 resv;
	u64 range_start;
	u64 range_length;
पूर्ण __attribute__((packed));

bool amd_iommu_dump;
bool amd_iommu_irq_remap __पढ़ो_mostly;

क्रमागत io_pgtable_fmt amd_iommu_pgtable = AMD_IOMMU_V1;

पूर्णांक amd_iommu_guest_ir = AMD_IOMMU_GUEST_IR_VAPIC;
अटल पूर्णांक amd_iommu_xt_mode = IRQ_REMAP_XAPIC_MODE;

अटल bool amd_iommu_detected;
अटल bool __initdata amd_iommu_disabled;
अटल पूर्णांक amd_iommu_target_ivhd_type;

u16 amd_iommu_last_bdf;			/* largest PCI device id we have
					   to handle */
LIST_HEAD(amd_iommu_unity_map);		/* a list of required unity mappings
					   we find in ACPI */
bool amd_iommu_unmap_flush;		/* अगर true, flush on every unmap */

LIST_HEAD(amd_iommu_list);		/* list of all AMD IOMMUs in the
					   प्रणाली */

/* Array to assign indices to IOMMUs*/
काष्ठा amd_iommu *amd_iommus[MAX_IOMMUS];

/* Number of IOMMUs present in the प्रणाली */
अटल पूर्णांक amd_iommus_present;

/* IOMMUs have a non-present cache? */
bool amd_iommu_np_cache __पढ़ो_mostly;
bool amd_iommu_iotlb_sup __पढ़ो_mostly = true;

u32 amd_iommu_max_pasid __पढ़ो_mostly = ~0;

bool amd_iommu_v2_present __पढ़ो_mostly;
अटल bool amd_iommu_pc_present __पढ़ो_mostly;

bool amd_iommu_क्रमce_isolation __पढ़ो_mostly;

/*
 * Poपूर्णांकer to the device table which is shared by all AMD IOMMUs
 * it is indexed by the PCI device id or the HT unit id and contains
 * inक्रमmation about the करोमुख्य the device beदीर्घs to as well as the
 * page table root poपूर्णांकer.
 */
काष्ठा dev_table_entry *amd_iommu_dev_table;
/*
 * Poपूर्णांकer to a device table which the content of old device table
 * will be copied to. It's only be used in kdump kernel.
 */
अटल काष्ठा dev_table_entry *old_dev_tbl_cpy;

/*
 * The alias table is a driver specअगरic data काष्ठाure which contains the
 * mappings of the PCI device ids to the actual requestor ids on the IOMMU.
 * More than one device can share the same requestor id.
 */
u16 *amd_iommu_alias_table;

/*
 * The rlookup table is used to find the IOMMU which is responsible
 * क्रम a specअगरic device. It is also indexed by the PCI device id.
 */
काष्ठा amd_iommu **amd_iommu_rlookup_table;

/*
 * This table is used to find the irq remapping table क्रम a given device id
 * quickly.
 */
काष्ठा irq_remap_table **irq_lookup_table;

/*
 * AMD IOMMU allows up to 2^16 dअगरferent protection करोमुख्यs. This is a biपंचांगap
 * to know which ones are alपढ़ोy in use.
 */
अचिन्हित दीर्घ *amd_iommu_pd_alloc_biपंचांगap;

अटल u32 dev_table_size;	/* size of the device table */
अटल u32 alias_table_size;	/* size of the alias table */
अटल u32 rlookup_table_size;	/* size अगर the rlookup table */

क्रमागत iommu_init_state अणु
	IOMMU_START_STATE,
	IOMMU_IVRS_DETECTED,
	IOMMU_ACPI_FINISHED,
	IOMMU_ENABLED,
	IOMMU_PCI_INIT,
	IOMMU_INTERRUPTS_EN,
	IOMMU_DMA_OPS,
	IOMMU_INITIALIZED,
	IOMMU_NOT_FOUND,
	IOMMU_INIT_ERROR,
	IOMMU_CMDLINE_DISABLED,
पूर्ण;

/* Early ioapic and hpet maps from kernel command line */
#घोषणा EARLY_MAP_SIZE		4
अटल काष्ठा devid_map __initdata early_ioapic_map[EARLY_MAP_SIZE];
अटल काष्ठा devid_map __initdata early_hpet_map[EARLY_MAP_SIZE];
अटल काष्ठा acpihid_map_entry __initdata early_acpihid_map[EARLY_MAP_SIZE];

अटल पूर्णांक __initdata early_ioapic_map_size;
अटल पूर्णांक __initdata early_hpet_map_size;
अटल पूर्णांक __initdata early_acpihid_map_size;

अटल bool __initdata cmdline_maps;

अटल क्रमागत iommu_init_state init_state = IOMMU_START_STATE;

अटल पूर्णांक amd_iommu_enable_पूर्णांकerrupts(व्योम);
अटल पूर्णांक __init iommu_go_to_state(क्रमागत iommu_init_state state);
अटल व्योम init_device_table_dma(व्योम);

अटल bool amd_iommu_pre_enabled = true;

अटल u32 amd_iommu_ivinfo __initdata;

bool translation_pre_enabled(काष्ठा amd_iommu *iommu)
अणु
	वापस (iommu->flags & AMD_IOMMU_FLAG_TRANS_PRE_ENABLED);
पूर्ण

अटल व्योम clear_translation_pre_enabled(काष्ठा amd_iommu *iommu)
अणु
	iommu->flags &= ~AMD_IOMMU_FLAG_TRANS_PRE_ENABLED;
पूर्ण

अटल व्योम init_translation_status(काष्ठा amd_iommu *iommu)
अणु
	u64 ctrl;

	ctrl = पढ़ोq(iommu->mmio_base + MMIO_CONTROL_OFFSET);
	अगर (ctrl & (1<<CONTROL_IOMMU_EN))
		iommu->flags |= AMD_IOMMU_FLAG_TRANS_PRE_ENABLED;
पूर्ण

अटल अंतरभूत व्योम update_last_devid(u16 devid)
अणु
	अगर (devid > amd_iommu_last_bdf)
		amd_iommu_last_bdf = devid;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ tbl_size(पूर्णांक entry_size)
अणु
	अचिन्हित shअगरt = PAGE_SHIFT +
			 get_order(((पूर्णांक)amd_iommu_last_bdf + 1) * entry_size);

	वापस 1UL << shअगरt;
पूर्ण

पूर्णांक amd_iommu_get_num_iommus(व्योम)
अणु
	वापस amd_iommus_present;
पूर्ण

/*
 * For IVHD type 0x11/0x40, EFR is also available via IVHD.
 * Default to IVHD EFR since it is available sooner
 * (i.e. beक्रमe PCI init).
 */
अटल व्योम __init early_iommu_features_init(काष्ठा amd_iommu *iommu,
					     काष्ठा ivhd_header *h)
अणु
	अगर (amd_iommu_ivinfo & IOMMU_IVINFO_EFRSUP)
		iommu->features = h->efr_reg;
पूर्ण

/* Access to l1 and l2 indexed रेजिस्टर spaces */

अटल u32 iommu_पढ़ो_l1(काष्ठा amd_iommu *iommu, u16 l1, u8 address)
अणु
	u32 val;

	pci_ग_लिखो_config_dword(iommu->dev, 0xf8, (address | l1 << 16));
	pci_पढ़ो_config_dword(iommu->dev, 0xfc, &val);
	वापस val;
पूर्ण

अटल व्योम iommu_ग_लिखो_l1(काष्ठा amd_iommu *iommu, u16 l1, u8 address, u32 val)
अणु
	pci_ग_लिखो_config_dword(iommu->dev, 0xf8, (address | l1 << 16 | 1 << 31));
	pci_ग_लिखो_config_dword(iommu->dev, 0xfc, val);
	pci_ग_लिखो_config_dword(iommu->dev, 0xf8, (address | l1 << 16));
पूर्ण

अटल u32 iommu_पढ़ो_l2(काष्ठा amd_iommu *iommu, u8 address)
अणु
	u32 val;

	pci_ग_लिखो_config_dword(iommu->dev, 0xf0, address);
	pci_पढ़ो_config_dword(iommu->dev, 0xf4, &val);
	वापस val;
पूर्ण

अटल व्योम iommu_ग_लिखो_l2(काष्ठा amd_iommu *iommu, u8 address, u32 val)
अणु
	pci_ग_लिखो_config_dword(iommu->dev, 0xf0, (address | 1 << 8));
	pci_ग_लिखो_config_dword(iommu->dev, 0xf4, val);
पूर्ण

/****************************************************************************
 *
 * AMD IOMMU MMIO रेजिस्टर space handling functions
 *
 * These functions are used to program the IOMMU device रेजिस्टरs in
 * MMIO space required क्रम that driver.
 *
 ****************************************************************************/

/*
 * This function set the exclusion range in the IOMMU. DMA accesses to the
 * exclusion range are passed through untranslated
 */
अटल व्योम iommu_set_exclusion_range(काष्ठा amd_iommu *iommu)
अणु
	u64 start = iommu->exclusion_start & PAGE_MASK;
	u64 limit = (start + iommu->exclusion_length - 1) & PAGE_MASK;
	u64 entry;

	अगर (!iommu->exclusion_start)
		वापस;

	entry = start | MMIO_EXCL_ENABLE_MASK;
	स_नकल_toio(iommu->mmio_base + MMIO_EXCL_BASE_OFFSET,
			&entry, माप(entry));

	entry = limit;
	स_नकल_toio(iommu->mmio_base + MMIO_EXCL_LIMIT_OFFSET,
			&entry, माप(entry));
पूर्ण

अटल व्योम iommu_set_cwwb_range(काष्ठा amd_iommu *iommu)
अणु
	u64 start = iommu_virt_to_phys((व्योम *)iommu->cmd_sem);
	u64 entry = start & PM_ADDR_MASK;

	अगर (!iommu_feature(iommu, FEATURE_SNP))
		वापस;

	/* Note:
	 * Re-purpose Exclusion base/limit रेजिस्टरs क्रम Completion रुको
	 * ग_लिखो-back base/limit.
	 */
	स_नकल_toio(iommu->mmio_base + MMIO_EXCL_BASE_OFFSET,
		    &entry, माप(entry));

	/* Note:
	 * Default to 4 Kbytes, which can be specअगरied by setting base
	 * address equal to the limit address.
	 */
	स_नकल_toio(iommu->mmio_base + MMIO_EXCL_LIMIT_OFFSET,
		    &entry, माप(entry));
पूर्ण

/* Programs the physical address of the device table पूर्णांकo the IOMMU hardware */
अटल व्योम iommu_set_device_table(काष्ठा amd_iommu *iommu)
अणु
	u64 entry;

	BUG_ON(iommu->mmio_base == शून्य);

	entry = iommu_virt_to_phys(amd_iommu_dev_table);
	entry |= (dev_table_size >> 12) - 1;
	स_नकल_toio(iommu->mmio_base + MMIO_DEV_TABLE_OFFSET,
			&entry, माप(entry));
पूर्ण

/* Generic functions to enable/disable certain features of the IOMMU. */
अटल व्योम iommu_feature_enable(काष्ठा amd_iommu *iommu, u8 bit)
अणु
	u64 ctrl;

	ctrl = पढ़ोq(iommu->mmio_base +  MMIO_CONTROL_OFFSET);
	ctrl |= (1ULL << bit);
	ग_लिखोq(ctrl, iommu->mmio_base +  MMIO_CONTROL_OFFSET);
पूर्ण

अटल व्योम iommu_feature_disable(काष्ठा amd_iommu *iommu, u8 bit)
अणु
	u64 ctrl;

	ctrl = पढ़ोq(iommu->mmio_base + MMIO_CONTROL_OFFSET);
	ctrl &= ~(1ULL << bit);
	ग_लिखोq(ctrl, iommu->mmio_base + MMIO_CONTROL_OFFSET);
पूर्ण

अटल व्योम iommu_set_inv_tlb_समयout(काष्ठा amd_iommu *iommu, पूर्णांक समयout)
अणु
	u64 ctrl;

	ctrl = पढ़ोq(iommu->mmio_base + MMIO_CONTROL_OFFSET);
	ctrl &= ~CTRL_INV_TO_MASK;
	ctrl |= (समयout << CONTROL_INV_TIMEOUT) & CTRL_INV_TO_MASK;
	ग_लिखोq(ctrl, iommu->mmio_base + MMIO_CONTROL_OFFSET);
पूर्ण

/* Function to enable the hardware */
अटल व्योम iommu_enable(काष्ठा amd_iommu *iommu)
अणु
	iommu_feature_enable(iommu, CONTROL_IOMMU_EN);
पूर्ण

अटल व्योम iommu_disable(काष्ठा amd_iommu *iommu)
अणु
	अगर (!iommu->mmio_base)
		वापस;

	/* Disable command buffer */
	iommu_feature_disable(iommu, CONTROL_CMDBUF_EN);

	/* Disable event logging and event पूर्णांकerrupts */
	iommu_feature_disable(iommu, CONTROL_EVT_INT_EN);
	iommu_feature_disable(iommu, CONTROL_EVT_LOG_EN);

	/* Disable IOMMU GA_LOG */
	iommu_feature_disable(iommu, CONTROL_GALOG_EN);
	iommu_feature_disable(iommu, CONTROL_GAINT_EN);

	/* Disable IOMMU hardware itself */
	iommu_feature_disable(iommu, CONTROL_IOMMU_EN);
पूर्ण

/*
 * mapping and unmapping functions क्रम the IOMMU MMIO space. Each AMD IOMMU in
 * the प्रणाली has one.
 */
अटल u8 __iomem * __init iommu_map_mmio_space(u64 address, u64 end)
अणु
	अगर (!request_mem_region(address, end, "amd_iommu")) अणु
		pr_err("Can not reserve memory region %llx-%llx for mmio\n",
			address, end);
		pr_err("This is a BIOS bug. Please contact your hardware vendor\n");
		वापस शून्य;
	पूर्ण

	वापस (u8 __iomem *)ioremap(address, end);
पूर्ण

अटल व्योम __init iommu_unmap_mmio_space(काष्ठा amd_iommu *iommu)
अणु
	अगर (iommu->mmio_base)
		iounmap(iommu->mmio_base);
	release_mem_region(iommu->mmio_phys, iommu->mmio_phys_end);
पूर्ण

अटल अंतरभूत u32 get_ivhd_header_size(काष्ठा ivhd_header *h)
अणु
	u32 size = 0;

	चयन (h->type) अणु
	हाल 0x10:
		size = 24;
		अवरोध;
	हाल 0x11:
	हाल 0x40:
		size = 40;
		अवरोध;
	पूर्ण
	वापस size;
पूर्ण

/****************************************************************************
 *
 * The functions below beदीर्घ to the first pass of AMD IOMMU ACPI table
 * parsing. In this pass we try to find out the highest device id this
 * code has to handle. Upon this inक्रमmation the size of the shared data
 * काष्ठाures is determined later.
 *
 ****************************************************************************/

/*
 * This function calculates the length of a given IVHD entry
 */
अटल अंतरभूत पूर्णांक ivhd_entry_length(u8 *ivhd)
अणु
	u32 type = ((काष्ठा ivhd_entry *)ivhd)->type;

	अगर (type < 0x80) अणु
		वापस 0x04 << (*ivhd >> 6);
	पूर्ण अन्यथा अगर (type == IVHD_DEV_ACPI_HID) अणु
		/* For ACPI_HID, offset 21 is uid len */
		वापस *((u8 *)ivhd + 21) + 22;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * After पढ़ोing the highest device id from the IOMMU PCI capability header
 * this function looks अगर there is a higher device id defined in the ACPI table
 */
अटल पूर्णांक __init find_last_devid_from_ivhd(काष्ठा ivhd_header *h)
अणु
	u8 *p = (व्योम *)h, *end = (व्योम *)h;
	काष्ठा ivhd_entry *dev;

	u32 ivhd_size = get_ivhd_header_size(h);

	अगर (!ivhd_size) अणु
		pr_err("Unsupported IVHD type %#x\n", h->type);
		वापस -EINVAL;
	पूर्ण

	p += ivhd_size;
	end += h->length;

	जबतक (p < end) अणु
		dev = (काष्ठा ivhd_entry *)p;
		चयन (dev->type) अणु
		हाल IVHD_DEV_ALL:
			/* Use maximum BDF value क्रम DEV_ALL */
			update_last_devid(0xffff);
			अवरोध;
		हाल IVHD_DEV_SELECT:
		हाल IVHD_DEV_RANGE_END:
		हाल IVHD_DEV_ALIAS:
		हाल IVHD_DEV_EXT_SELECT:
			/* all the above subfield types refer to device ids */
			update_last_devid(dev->devid);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		p += ivhd_entry_length(p);
	पूर्ण

	WARN_ON(p != end);

	वापस 0;
पूर्ण

अटल पूर्णांक __init check_ivrs_checksum(काष्ठा acpi_table_header *table)
अणु
	पूर्णांक i;
	u8 checksum = 0, *p = (u8 *)table;

	क्रम (i = 0; i < table->length; ++i)
		checksum += p[i];
	अगर (checksum != 0) अणु
		/* ACPI table corrupt */
		pr_err(FW_BUG "IVRS invalid checksum\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Iterate over all IVHD entries in the ACPI table and find the highest device
 * id which we need to handle. This is the first of three functions which parse
 * the ACPI table. So we check the checksum here.
 */
अटल पूर्णांक __init find_last_devid_acpi(काष्ठा acpi_table_header *table)
अणु
	u8 *p = (u8 *)table, *end = (u8 *)table;
	काष्ठा ivhd_header *h;

	p += IVRS_HEADER_LENGTH;

	end += table->length;
	जबतक (p < end) अणु
		h = (काष्ठा ivhd_header *)p;
		अगर (h->type == amd_iommu_target_ivhd_type) अणु
			पूर्णांक ret = find_last_devid_from_ivhd(h);

			अगर (ret)
				वापस ret;
		पूर्ण
		p += h->length;
	पूर्ण
	WARN_ON(p != end);

	वापस 0;
पूर्ण

/****************************************************************************
 *
 * The following functions beदीर्घ to the code path which parses the ACPI table
 * the second समय. In this ACPI parsing iteration we allocate IOMMU specअगरic
 * data काष्ठाures, initialize the device/alias/rlookup table and also
 * basically initialize the hardware.
 *
 ****************************************************************************/

/*
 * Allocates the command buffer. This buffer is per AMD IOMMU. We can
 * ग_लिखो commands to that buffer later and the IOMMU will execute them
 * asynchronously
 */
अटल पूर्णांक __init alloc_command_buffer(काष्ठा amd_iommu *iommu)
अणु
	iommu->cmd_buf = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
						  get_order(CMD_BUFFER_SIZE));

	वापस iommu->cmd_buf ? 0 : -ENOMEM;
पूर्ण

/*
 * This function resets the command buffer अगर the IOMMU stopped fetching
 * commands from it.
 */
व्योम amd_iommu_reset_cmd_buffer(काष्ठा amd_iommu *iommu)
अणु
	iommu_feature_disable(iommu, CONTROL_CMDBUF_EN);

	ग_लिखोl(0x00, iommu->mmio_base + MMIO_CMD_HEAD_OFFSET);
	ग_लिखोl(0x00, iommu->mmio_base + MMIO_CMD_TAIL_OFFSET);
	iommu->cmd_buf_head = 0;
	iommu->cmd_buf_tail = 0;

	iommu_feature_enable(iommu, CONTROL_CMDBUF_EN);
पूर्ण

/*
 * This function ग_लिखोs the command buffer address to the hardware and
 * enables it.
 */
अटल व्योम iommu_enable_command_buffer(काष्ठा amd_iommu *iommu)
अणु
	u64 entry;

	BUG_ON(iommu->cmd_buf == शून्य);

	entry = iommu_virt_to_phys(iommu->cmd_buf);
	entry |= MMIO_CMD_SIZE_512;

	स_नकल_toio(iommu->mmio_base + MMIO_CMD_BUF_OFFSET,
		    &entry, माप(entry));

	amd_iommu_reset_cmd_buffer(iommu);
पूर्ण

/*
 * This function disables the command buffer
 */
अटल व्योम iommu_disable_command_buffer(काष्ठा amd_iommu *iommu)
अणु
	iommu_feature_disable(iommu, CONTROL_CMDBUF_EN);
पूर्ण

अटल व्योम __init मुक्त_command_buffer(काष्ठा amd_iommu *iommu)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)iommu->cmd_buf, get_order(CMD_BUFFER_SIZE));
पूर्ण

अटल व्योम *__init iommu_alloc_4k_pages(काष्ठा amd_iommu *iommu,
					 gfp_t gfp, माप_प्रकार size)
अणु
	पूर्णांक order = get_order(size);
	व्योम *buf = (व्योम *)__get_मुक्त_pages(gfp, order);

	अगर (buf &&
	    iommu_feature(iommu, FEATURE_SNP) &&
	    set_memory_4k((अचिन्हित दीर्घ)buf, (1 << order))) अणु
		मुक्त_pages((अचिन्हित दीर्घ)buf, order);
		buf = शून्य;
	पूर्ण

	वापस buf;
पूर्ण

/* allocates the memory where the IOMMU will log its events to */
अटल पूर्णांक __init alloc_event_buffer(काष्ठा amd_iommu *iommu)
अणु
	iommu->evt_buf = iommu_alloc_4k_pages(iommu, GFP_KERNEL | __GFP_ZERO,
					      EVT_BUFFER_SIZE);

	वापस iommu->evt_buf ? 0 : -ENOMEM;
पूर्ण

अटल व्योम iommu_enable_event_buffer(काष्ठा amd_iommu *iommu)
अणु
	u64 entry;

	BUG_ON(iommu->evt_buf == शून्य);

	entry = iommu_virt_to_phys(iommu->evt_buf) | EVT_LEN_MASK;

	स_नकल_toio(iommu->mmio_base + MMIO_EVT_BUF_OFFSET,
		    &entry, माप(entry));

	/* set head and tail to zero manually */
	ग_लिखोl(0x00, iommu->mmio_base + MMIO_EVT_HEAD_OFFSET);
	ग_लिखोl(0x00, iommu->mmio_base + MMIO_EVT_TAIL_OFFSET);

	iommu_feature_enable(iommu, CONTROL_EVT_LOG_EN);
पूर्ण

/*
 * This function disables the event log buffer
 */
अटल व्योम iommu_disable_event_buffer(काष्ठा amd_iommu *iommu)
अणु
	iommu_feature_disable(iommu, CONTROL_EVT_LOG_EN);
पूर्ण

अटल व्योम __init मुक्त_event_buffer(काष्ठा amd_iommu *iommu)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)iommu->evt_buf, get_order(EVT_BUFFER_SIZE));
पूर्ण

/* allocates the memory where the IOMMU will log its events to */
अटल पूर्णांक __init alloc_ppr_log(काष्ठा amd_iommu *iommu)
अणु
	iommu->ppr_log = iommu_alloc_4k_pages(iommu, GFP_KERNEL | __GFP_ZERO,
					      PPR_LOG_SIZE);

	वापस iommu->ppr_log ? 0 : -ENOMEM;
पूर्ण

अटल व्योम iommu_enable_ppr_log(काष्ठा amd_iommu *iommu)
अणु
	u64 entry;

	अगर (iommu->ppr_log == शून्य)
		वापस;

	entry = iommu_virt_to_phys(iommu->ppr_log) | PPR_LOG_SIZE_512;

	स_नकल_toio(iommu->mmio_base + MMIO_PPR_LOG_OFFSET,
		    &entry, माप(entry));

	/* set head and tail to zero manually */
	ग_लिखोl(0x00, iommu->mmio_base + MMIO_PPR_HEAD_OFFSET);
	ग_लिखोl(0x00, iommu->mmio_base + MMIO_PPR_TAIL_OFFSET);

	iommu_feature_enable(iommu, CONTROL_PPRLOG_EN);
	iommu_feature_enable(iommu, CONTROL_PPR_EN);
पूर्ण

अटल व्योम __init मुक्त_ppr_log(काष्ठा amd_iommu *iommu)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)iommu->ppr_log, get_order(PPR_LOG_SIZE));
पूर्ण

अटल व्योम मुक्त_ga_log(काष्ठा amd_iommu *iommu)
अणु
#अगर_घोषित CONFIG_IRQ_REMAP
	मुक्त_pages((अचिन्हित दीर्घ)iommu->ga_log, get_order(GA_LOG_SIZE));
	मुक्त_pages((अचिन्हित दीर्घ)iommu->ga_log_tail, get_order(8));
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक iommu_ga_log_enable(काष्ठा amd_iommu *iommu)
अणु
#अगर_घोषित CONFIG_IRQ_REMAP
	u32 status, i;

	अगर (!iommu->ga_log)
		वापस -EINVAL;

	status = पढ़ोl(iommu->mmio_base + MMIO_STATUS_OFFSET);

	/* Check अगर alपढ़ोy running */
	अगर (status & (MMIO_STATUS_GALOG_RUN_MASK))
		वापस 0;

	iommu_feature_enable(iommu, CONTROL_GAINT_EN);
	iommu_feature_enable(iommu, CONTROL_GALOG_EN);

	क्रम (i = 0; i < LOOP_TIMEOUT; ++i) अणु
		status = पढ़ोl(iommu->mmio_base + MMIO_STATUS_OFFSET);
		अगर (status & (MMIO_STATUS_GALOG_RUN_MASK))
			अवरोध;
	पूर्ण

	अगर (i >= LOOP_TIMEOUT)
		वापस -EINVAL;
#पूर्ण_अगर /* CONFIG_IRQ_REMAP */
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IRQ_REMAP
अटल पूर्णांक iommu_init_ga_log(काष्ठा amd_iommu *iommu)
अणु
	u64 entry;

	अगर (!AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir))
		वापस 0;

	iommu->ga_log = (u8 *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					get_order(GA_LOG_SIZE));
	अगर (!iommu->ga_log)
		जाओ err_out;

	iommu->ga_log_tail = (u8 *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					get_order(8));
	अगर (!iommu->ga_log_tail)
		जाओ err_out;

	entry = iommu_virt_to_phys(iommu->ga_log) | GA_LOG_SIZE_512;
	स_नकल_toio(iommu->mmio_base + MMIO_GA_LOG_BASE_OFFSET,
		    &entry, माप(entry));
	entry = (iommu_virt_to_phys(iommu->ga_log_tail) &
		 (BIT_ULL(52)-1)) & ~7ULL;
	स_नकल_toio(iommu->mmio_base + MMIO_GA_LOG_TAIL_OFFSET,
		    &entry, माप(entry));
	ग_लिखोl(0x00, iommu->mmio_base + MMIO_GA_HEAD_OFFSET);
	ग_लिखोl(0x00, iommu->mmio_base + MMIO_GA_TAIL_OFFSET);

	वापस 0;
err_out:
	मुक्त_ga_log(iommu);
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_IRQ_REMAP */

अटल पूर्णांक iommu_init_ga(काष्ठा amd_iommu *iommu)
अणु
	पूर्णांक ret = 0;

#अगर_घोषित CONFIG_IRQ_REMAP
	/* Note: We have alपढ़ोy checked GASup from IVRS table.
	 *       Now, we need to make sure that GAMSup is set.
	 */
	अगर (AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir) &&
	    !iommu_feature(iommu, FEATURE_GAM_VAPIC))
		amd_iommu_guest_ir = AMD_IOMMU_GUEST_IR_LEGACY_GA;

	ret = iommu_init_ga_log(iommu);
#पूर्ण_अगर /* CONFIG_IRQ_REMAP */

	वापस ret;
पूर्ण

अटल पूर्णांक __init alloc_cwwb_sem(काष्ठा amd_iommu *iommu)
अणु
	iommu->cmd_sem = iommu_alloc_4k_pages(iommu, GFP_KERNEL | __GFP_ZERO, 1);

	वापस iommu->cmd_sem ? 0 : -ENOMEM;
पूर्ण

अटल व्योम __init मुक्त_cwwb_sem(काष्ठा amd_iommu *iommu)
अणु
	अगर (iommu->cmd_sem)
		मुक्त_page((अचिन्हित दीर्घ)iommu->cmd_sem);
पूर्ण

अटल व्योम iommu_enable_xt(काष्ठा amd_iommu *iommu)
अणु
#अगर_घोषित CONFIG_IRQ_REMAP
	/*
	 * XT mode (32-bit APIC destination ID) requires
	 * GA mode (128-bit IRTE support) as a prerequisite.
	 */
	अगर (AMD_IOMMU_GUEST_IR_GA(amd_iommu_guest_ir) &&
	    amd_iommu_xt_mode == IRQ_REMAP_X2APIC_MODE)
		iommu_feature_enable(iommu, CONTROL_XT_EN);
#पूर्ण_अगर /* CONFIG_IRQ_REMAP */
पूर्ण

अटल व्योम iommu_enable_gt(काष्ठा amd_iommu *iommu)
अणु
	अगर (!iommu_feature(iommu, FEATURE_GT))
		वापस;

	iommu_feature_enable(iommu, CONTROL_GT_EN);
पूर्ण

/* sets a specअगरic bit in the device table entry. */
अटल व्योम set_dev_entry_bit(u16 devid, u8 bit)
अणु
	पूर्णांक i = (bit >> 6) & 0x03;
	पूर्णांक _bit = bit & 0x3f;

	amd_iommu_dev_table[devid].data[i] |= (1UL << _bit);
पूर्ण

अटल पूर्णांक get_dev_entry_bit(u16 devid, u8 bit)
अणु
	पूर्णांक i = (bit >> 6) & 0x03;
	पूर्णांक _bit = bit & 0x3f;

	वापस (amd_iommu_dev_table[devid].data[i] & (1UL << _bit)) >> _bit;
पूर्ण


अटल bool copy_device_table(व्योम)
अणु
	u64 पूर्णांक_ctl, पूर्णांक_tab_len, entry = 0, last_entry = 0;
	काष्ठा dev_table_entry *old_devtb = शून्य;
	u32 lo, hi, devid, old_devtb_size;
	phys_addr_t old_devtb_phys;
	काष्ठा amd_iommu *iommu;
	u16 करोm_id, dte_v, irq_v;
	gfp_t gfp_flag;
	u64 पंचांगp;

	अगर (!amd_iommu_pre_enabled)
		वापस false;

	pr_warn("Translation is already enabled - trying to copy translation structures\n");
	क्रम_each_iommu(iommu) अणु
		/* All IOMMUs should use the same device table with the same size */
		lo = पढ़ोl(iommu->mmio_base + MMIO_DEV_TABLE_OFFSET);
		hi = पढ़ोl(iommu->mmio_base + MMIO_DEV_TABLE_OFFSET + 4);
		entry = (((u64) hi) << 32) + lo;
		अगर (last_entry && last_entry != entry) अणु
			pr_err("IOMMU:%d should use the same dev table as others!\n",
				iommu->index);
			वापस false;
		पूर्ण
		last_entry = entry;

		old_devtb_size = ((entry & ~PAGE_MASK) + 1) << 12;
		अगर (old_devtb_size != dev_table_size) अणु
			pr_err("The device table size of IOMMU:%d is not expected!\n",
				iommu->index);
			वापस false;
		पूर्ण
	पूर्ण

	/*
	 * When SME is enabled in the first kernel, the entry includes the
	 * memory encryption mask(sme_me_mask), we must हटाओ the memory
	 * encryption mask to obtain the true physical address in kdump kernel.
	 */
	old_devtb_phys = __sme_clr(entry) & PAGE_MASK;

	अगर (old_devtb_phys >= 0x100000000ULL) अणु
		pr_err("The address of old device table is above 4G, not trustworthy!\n");
		वापस false;
	पूर्ण
	old_devtb = (sme_active() && is_kdump_kernel())
		    ? (__क्रमce व्योम *)ioremap_encrypted(old_devtb_phys,
							dev_table_size)
		    : memremap(old_devtb_phys, dev_table_size, MEMREMAP_WB);

	अगर (!old_devtb)
		वापस false;

	gfp_flag = GFP_KERNEL | __GFP_ZERO | GFP_DMA32;
	old_dev_tbl_cpy = (व्योम *)__get_मुक्त_pages(gfp_flag,
				get_order(dev_table_size));
	अगर (old_dev_tbl_cpy == शून्य) अणु
		pr_err("Failed to allocate memory for copying old device table!\n");
		वापस false;
	पूर्ण

	क्रम (devid = 0; devid <= amd_iommu_last_bdf; ++devid) अणु
		old_dev_tbl_cpy[devid] = old_devtb[devid];
		करोm_id = old_devtb[devid].data[1] & DEV_DOMID_MASK;
		dte_v = old_devtb[devid].data[0] & DTE_FLAG_V;

		अगर (dte_v && करोm_id) अणु
			old_dev_tbl_cpy[devid].data[0] = old_devtb[devid].data[0];
			old_dev_tbl_cpy[devid].data[1] = old_devtb[devid].data[1];
			__set_bit(करोm_id, amd_iommu_pd_alloc_biपंचांगap);
			/* If gcr3 table existed, mask it out */
			अगर (old_devtb[devid].data[0] & DTE_FLAG_GV) अणु
				पंचांगp = DTE_GCR3_VAL_B(~0ULL) << DTE_GCR3_SHIFT_B;
				पंचांगp |= DTE_GCR3_VAL_C(~0ULL) << DTE_GCR3_SHIFT_C;
				old_dev_tbl_cpy[devid].data[1] &= ~पंचांगp;
				पंचांगp = DTE_GCR3_VAL_A(~0ULL) << DTE_GCR3_SHIFT_A;
				पंचांगp |= DTE_FLAG_GV;
				old_dev_tbl_cpy[devid].data[0] &= ~पंचांगp;
			पूर्ण
		पूर्ण

		irq_v = old_devtb[devid].data[2] & DTE_IRQ_REMAP_ENABLE;
		पूर्णांक_ctl = old_devtb[devid].data[2] & DTE_IRQ_REMAP_INTCTL_MASK;
		पूर्णांक_tab_len = old_devtb[devid].data[2] & DTE_INTTABLEN_MASK;
		अगर (irq_v && (पूर्णांक_ctl || पूर्णांक_tab_len)) अणु
			अगर ((पूर्णांक_ctl != DTE_IRQ_REMAP_INTCTL) ||
			    (पूर्णांक_tab_len != DTE_INTTABLEN)) अणु
				pr_err("Wrong old irq remapping flag: %#x\n", devid);
				वापस false;
			पूर्ण

		        old_dev_tbl_cpy[devid].data[2] = old_devtb[devid].data[2];
		पूर्ण
	पूर्ण
	memunmap(old_devtb);

	वापस true;
पूर्ण

व्योम amd_iommu_apply_erratum_63(u16 devid)
अणु
	पूर्णांक sysmgt;

	sysmgt = get_dev_entry_bit(devid, DEV_ENTRY_SYSMGT1) |
		 (get_dev_entry_bit(devid, DEV_ENTRY_SYSMGT2) << 1);

	अगर (sysmgt == 0x01)
		set_dev_entry_bit(devid, DEV_ENTRY_IW);
पूर्ण

/* Writes the specअगरic IOMMU क्रम a device पूर्णांकo the rlookup table */
अटल व्योम __init set_iommu_क्रम_device(काष्ठा amd_iommu *iommu, u16 devid)
अणु
	amd_iommu_rlookup_table[devid] = iommu;
पूर्ण

/*
 * This function takes the device specअगरic flags पढ़ो from the ACPI
 * table and sets up the device table entry with that inक्रमmation
 */
अटल व्योम __init set_dev_entry_from_acpi(काष्ठा amd_iommu *iommu,
					   u16 devid, u32 flags, u32 ext_flags)
अणु
	अगर (flags & ACPI_DEVFLAG_INITPASS)
		set_dev_entry_bit(devid, DEV_ENTRY_INIT_PASS);
	अगर (flags & ACPI_DEVFLAG_EXTINT)
		set_dev_entry_bit(devid, DEV_ENTRY_EINT_PASS);
	अगर (flags & ACPI_DEVFLAG_NMI)
		set_dev_entry_bit(devid, DEV_ENTRY_NMI_PASS);
	अगर (flags & ACPI_DEVFLAG_SYSMGT1)
		set_dev_entry_bit(devid, DEV_ENTRY_SYSMGT1);
	अगर (flags & ACPI_DEVFLAG_SYSMGT2)
		set_dev_entry_bit(devid, DEV_ENTRY_SYSMGT2);
	अगर (flags & ACPI_DEVFLAG_LINT0)
		set_dev_entry_bit(devid, DEV_ENTRY_LINT0_PASS);
	अगर (flags & ACPI_DEVFLAG_LINT1)
		set_dev_entry_bit(devid, DEV_ENTRY_LINT1_PASS);

	amd_iommu_apply_erratum_63(devid);

	set_iommu_क्रम_device(iommu, devid);
पूर्ण

पूर्णांक __init add_special_device(u8 type, u8 id, u16 *devid, bool cmd_line)
अणु
	काष्ठा devid_map *entry;
	काष्ठा list_head *list;

	अगर (type == IVHD_SPECIAL_IOAPIC)
		list = &ioapic_map;
	अन्यथा अगर (type == IVHD_SPECIAL_HPET)
		list = &hpet_map;
	अन्यथा
		वापस -EINVAL;

	list_क्रम_each_entry(entry, list, list) अणु
		अगर (!(entry->id == id && entry->cmd_line))
			जारी;

		pr_info("Command-line override present for %s id %d - ignoring\n",
			type == IVHD_SPECIAL_IOAPIC ? "IOAPIC" : "HPET", id);

		*devid = entry->devid;

		वापस 0;
	पूर्ण

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->id	= id;
	entry->devid	= *devid;
	entry->cmd_line	= cmd_line;

	list_add_tail(&entry->list, list);

	वापस 0;
पूर्ण

अटल पूर्णांक __init add_acpi_hid_device(u8 *hid, u8 *uid, u16 *devid,
				      bool cmd_line)
अणु
	काष्ठा acpihid_map_entry *entry;
	काष्ठा list_head *list = &acpihid_map;

	list_क्रम_each_entry(entry, list, list) अणु
		अगर (म_भेद(entry->hid, hid) ||
		    (*uid && *entry->uid && म_भेद(entry->uid, uid)) ||
		    !entry->cmd_line)
			जारी;

		pr_info("Command-line override for hid:%s uid:%s\n",
			hid, uid);
		*devid = entry->devid;
		वापस 0;
	पूर्ण

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	स_नकल(entry->uid, uid, म_माप(uid));
	स_नकल(entry->hid, hid, म_माप(hid));
	entry->devid = *devid;
	entry->cmd_line	= cmd_line;
	entry->root_devid = (entry->devid & (~0x7));

	pr_info("%s, add hid:%s, uid:%s, rdevid:%d\n",
		entry->cmd_line ? "cmd" : "ivrs",
		entry->hid, entry->uid, entry->root_devid);

	list_add_tail(&entry->list, list);
	वापस 0;
पूर्ण

अटल पूर्णांक __init add_early_maps(व्योम)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < early_ioapic_map_size; ++i) अणु
		ret = add_special_device(IVHD_SPECIAL_IOAPIC,
					 early_ioapic_map[i].id,
					 &early_ioapic_map[i].devid,
					 early_ioapic_map[i].cmd_line);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < early_hpet_map_size; ++i) अणु
		ret = add_special_device(IVHD_SPECIAL_HPET,
					 early_hpet_map[i].id,
					 &early_hpet_map[i].devid,
					 early_hpet_map[i].cmd_line);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < early_acpihid_map_size; ++i) अणु
		ret = add_acpi_hid_device(early_acpihid_map[i].hid,
					  early_acpihid_map[i].uid,
					  &early_acpihid_map[i].devid,
					  early_acpihid_map[i].cmd_line);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Takes a poपूर्णांकer to an AMD IOMMU entry in the ACPI table and
 * initializes the hardware and our data काष्ठाures with it.
 */
अटल पूर्णांक __init init_iommu_from_acpi(काष्ठा amd_iommu *iommu,
					काष्ठा ivhd_header *h)
अणु
	u8 *p = (u8 *)h;
	u8 *end = p, flags = 0;
	u16 devid = 0, devid_start = 0, devid_to = 0;
	u32 dev_i, ext_flags = 0;
	bool alias = false;
	काष्ठा ivhd_entry *e;
	u32 ivhd_size;
	पूर्णांक ret;


	ret = add_early_maps();
	अगर (ret)
		वापस ret;

	amd_iommu_apply_ivrs_quirks();

	/*
	 * First save the recommended feature enable bits from ACPI
	 */
	iommu->acpi_flags = h->flags;

	/*
	 * Done. Now parse the device entries
	 */
	ivhd_size = get_ivhd_header_size(h);
	अगर (!ivhd_size) अणु
		pr_err("Unsupported IVHD type %#x\n", h->type);
		वापस -EINVAL;
	पूर्ण

	p += ivhd_size;

	end += h->length;


	जबतक (p < end) अणु
		e = (काष्ठा ivhd_entry *)p;
		चयन (e->type) अणु
		हाल IVHD_DEV_ALL:

			DUMP_prपूर्णांकk("  DEV_ALL\t\t\tflags: %02x\n", e->flags);

			क्रम (dev_i = 0; dev_i <= amd_iommu_last_bdf; ++dev_i)
				set_dev_entry_from_acpi(iommu, dev_i, e->flags, 0);
			अवरोध;
		हाल IVHD_DEV_SELECT:

			DUMP_prपूर्णांकk("  DEV_SELECT\t\t\t devid: %02x:%02x.%x "
				    "flags: %02x\n",
				    PCI_BUS_NUM(e->devid),
				    PCI_SLOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->flags);

			devid = e->devid;
			set_dev_entry_from_acpi(iommu, devid, e->flags, 0);
			अवरोध;
		हाल IVHD_DEV_SELECT_RANGE_START:

			DUMP_prपूर्णांकk("  DEV_SELECT_RANGE_START\t "
				    "devid: %02x:%02x.%x flags: %02x\n",
				    PCI_BUS_NUM(e->devid),
				    PCI_SLOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->flags);

			devid_start = e->devid;
			flags = e->flags;
			ext_flags = 0;
			alias = false;
			अवरोध;
		हाल IVHD_DEV_ALIAS:

			DUMP_prपूर्णांकk("  DEV_ALIAS\t\t\t devid: %02x:%02x.%x "
				    "flags: %02x devid_to: %02x:%02x.%x\n",
				    PCI_BUS_NUM(e->devid),
				    PCI_SLOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->flags,
				    PCI_BUS_NUM(e->ext >> 8),
				    PCI_SLOT(e->ext >> 8),
				    PCI_FUNC(e->ext >> 8));

			devid = e->devid;
			devid_to = e->ext >> 8;
			set_dev_entry_from_acpi(iommu, devid   , e->flags, 0);
			set_dev_entry_from_acpi(iommu, devid_to, e->flags, 0);
			amd_iommu_alias_table[devid] = devid_to;
			अवरोध;
		हाल IVHD_DEV_ALIAS_RANGE:

			DUMP_prपूर्णांकk("  DEV_ALIAS_RANGE\t\t "
				    "devid: %02x:%02x.%x flags: %02x "
				    "devid_to: %02x:%02x.%x\n",
				    PCI_BUS_NUM(e->devid),
				    PCI_SLOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->flags,
				    PCI_BUS_NUM(e->ext >> 8),
				    PCI_SLOT(e->ext >> 8),
				    PCI_FUNC(e->ext >> 8));

			devid_start = e->devid;
			flags = e->flags;
			devid_to = e->ext >> 8;
			ext_flags = 0;
			alias = true;
			अवरोध;
		हाल IVHD_DEV_EXT_SELECT:

			DUMP_prपूर्णांकk("  DEV_EXT_SELECT\t\t devid: %02x:%02x.%x "
				    "flags: %02x ext: %08x\n",
				    PCI_BUS_NUM(e->devid),
				    PCI_SLOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->flags, e->ext);

			devid = e->devid;
			set_dev_entry_from_acpi(iommu, devid, e->flags,
						e->ext);
			अवरोध;
		हाल IVHD_DEV_EXT_SELECT_RANGE:

			DUMP_prपूर्णांकk("  DEV_EXT_SELECT_RANGE\t devid: "
				    "%02x:%02x.%x flags: %02x ext: %08x\n",
				    PCI_BUS_NUM(e->devid),
				    PCI_SLOT(e->devid),
				    PCI_FUNC(e->devid),
				    e->flags, e->ext);

			devid_start = e->devid;
			flags = e->flags;
			ext_flags = e->ext;
			alias = false;
			अवरोध;
		हाल IVHD_DEV_RANGE_END:

			DUMP_prपूर्णांकk("  DEV_RANGE_END\t\t devid: %02x:%02x.%x\n",
				    PCI_BUS_NUM(e->devid),
				    PCI_SLOT(e->devid),
				    PCI_FUNC(e->devid));

			devid = e->devid;
			क्रम (dev_i = devid_start; dev_i <= devid; ++dev_i) अणु
				अगर (alias) अणु
					amd_iommu_alias_table[dev_i] = devid_to;
					set_dev_entry_from_acpi(iommu,
						devid_to, flags, ext_flags);
				पूर्ण
				set_dev_entry_from_acpi(iommu, dev_i,
							flags, ext_flags);
			पूर्ण
			अवरोध;
		हाल IVHD_DEV_SPECIAL: अणु
			u8 handle, type;
			स्थिर अक्षर *var;
			u16 devid;
			पूर्णांक ret;

			handle = e->ext & 0xff;
			devid  = (e->ext >>  8) & 0xffff;
			type   = (e->ext >> 24) & 0xff;

			अगर (type == IVHD_SPECIAL_IOAPIC)
				var = "IOAPIC";
			अन्यथा अगर (type == IVHD_SPECIAL_HPET)
				var = "HPET";
			अन्यथा
				var = "UNKNOWN";

			DUMP_prपूर्णांकk("  DEV_SPECIAL(%s[%d])\t\tdevid: %02x:%02x.%x\n",
				    var, (पूर्णांक)handle,
				    PCI_BUS_NUM(devid),
				    PCI_SLOT(devid),
				    PCI_FUNC(devid));

			ret = add_special_device(type, handle, &devid, false);
			अगर (ret)
				वापस ret;

			/*
			 * add_special_device might update the devid in हाल a
			 * command-line override is present. So call
			 * set_dev_entry_from_acpi after add_special_device.
			 */
			set_dev_entry_from_acpi(iommu, devid, e->flags, 0);

			अवरोध;
		पूर्ण
		हाल IVHD_DEV_ACPI_HID: अणु
			u16 devid;
			u8 hid[ACPIHID_HID_LEN];
			u8 uid[ACPIHID_UID_LEN];
			पूर्णांक ret;

			अगर (h->type != 0x40) अणु
				pr_err(FW_BUG "Invalid IVHD device type %#x\n",
				       e->type);
				अवरोध;
			पूर्ण

			स_नकल(hid, (u8 *)(&e->ext), ACPIHID_HID_LEN - 1);
			hid[ACPIHID_HID_LEN - 1] = '\0';

			अगर (!(*hid)) अणु
				pr_err(FW_BUG "Invalid HID.\n");
				अवरोध;
			पूर्ण

			uid[0] = '\0';
			चयन (e->uidf) अणु
			हाल UID_NOT_PRESENT:

				अगर (e->uidl != 0)
					pr_warn(FW_BUG "Invalid UID length.\n");

				अवरोध;
			हाल UID_IS_INTEGER:

				प्र_लिखो(uid, "%d", e->uid);

				अवरोध;
			हाल UID_IS_CHARACTER:

				स_नकल(uid, &e->uid, e->uidl);
				uid[e->uidl] = '\0';

				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			devid = e->devid;
			DUMP_prपूर्णांकk("  DEV_ACPI_HID(%s[%s])\t\tdevid: %02x:%02x.%x\n",
				    hid, uid,
				    PCI_BUS_NUM(devid),
				    PCI_SLOT(devid),
				    PCI_FUNC(devid));

			flags = e->flags;

			ret = add_acpi_hid_device(hid, uid, &devid, false);
			अगर (ret)
				वापस ret;

			/*
			 * add_special_device might update the devid in हाल a
			 * command-line override is present. So call
			 * set_dev_entry_from_acpi after add_special_device.
			 */
			set_dev_entry_from_acpi(iommu, devid, e->flags, 0);

			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण

		p += ivhd_entry_length(p);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init मुक्त_iommu_one(काष्ठा amd_iommu *iommu)
अणु
	मुक्त_cwwb_sem(iommu);
	मुक्त_command_buffer(iommu);
	मुक्त_event_buffer(iommu);
	मुक्त_ppr_log(iommu);
	मुक्त_ga_log(iommu);
	iommu_unmap_mmio_space(iommu);
पूर्ण

अटल व्योम __init मुक्त_iommu_all(व्योम)
अणु
	काष्ठा amd_iommu *iommu, *next;

	क्रम_each_iommu_safe(iommu, next) अणु
		list_del(&iommu->list);
		मुक्त_iommu_one(iommu);
		kमुक्त(iommu);
	पूर्ण
पूर्ण

/*
 * Family15h Model 10h-1fh erratum 746 (IOMMU Logging May Stall Translations)
 * Workaround:
 *     BIOS should disable L2B micellaneous घड़ी gating by setting
 *     L2_L2B_CK_GATE_CONTROL[CKGateL2BMiscDisable](D0F2xF4_x90[2]) = 1b
 */
अटल व्योम amd_iommu_erratum_746_workaround(काष्ठा amd_iommu *iommu)
अणु
	u32 value;

	अगर ((boot_cpu_data.x86 != 0x15) ||
	    (boot_cpu_data.x86_model < 0x10) ||
	    (boot_cpu_data.x86_model > 0x1f))
		वापस;

	pci_ग_लिखो_config_dword(iommu->dev, 0xf0, 0x90);
	pci_पढ़ो_config_dword(iommu->dev, 0xf4, &value);

	अगर (value & BIT(2))
		वापस;

	/* Select NB indirect रेजिस्टर 0x90 and enable writing */
	pci_ग_लिखो_config_dword(iommu->dev, 0xf0, 0x90 | (1 << 8));

	pci_ग_लिखो_config_dword(iommu->dev, 0xf4, value | 0x4);
	pci_info(iommu->dev, "Applying erratum 746 workaround\n");

	/* Clear the enable writing bit */
	pci_ग_लिखो_config_dword(iommu->dev, 0xf0, 0x90);
पूर्ण

/*
 * Family15h Model 30h-3fh (IOMMU Mishandles ATS Write Permission)
 * Workaround:
 *     BIOS should enable ATS ग_लिखो permission check by setting
 *     L2_DEBUG_3[AtsIgnoreIWDis](D0F2xF4_x47[0]) = 1b
 */
अटल व्योम amd_iommu_ats_ग_लिखो_check_workaround(काष्ठा amd_iommu *iommu)
अणु
	u32 value;

	अगर ((boot_cpu_data.x86 != 0x15) ||
	    (boot_cpu_data.x86_model < 0x30) ||
	    (boot_cpu_data.x86_model > 0x3f))
		वापस;

	/* Test L2_DEBUG_3[AtsIgnoreIWDis] == 1 */
	value = iommu_पढ़ो_l2(iommu, 0x47);

	अगर (value & BIT(0))
		वापस;

	/* Set L2_DEBUG_3[AtsIgnoreIWDis] = 1 */
	iommu_ग_लिखो_l2(iommu, 0x47, value | BIT(0));

	pci_info(iommu->dev, "Applying ATS write check workaround\n");
पूर्ण

/*
 * This function clues the initialization function क्रम one IOMMU
 * together and also allocates the command buffer and programs the
 * hardware. It करोes NOT enable the IOMMU. This is करोne afterwards.
 */
अटल पूर्णांक __init init_iommu_one(काष्ठा amd_iommu *iommu, काष्ठा ivhd_header *h)
अणु
	पूर्णांक ret;

	raw_spin_lock_init(&iommu->lock);
	iommu->cmd_sem_val = 0;

	/* Add IOMMU to पूर्णांकernal data काष्ठाures */
	list_add_tail(&iommu->list, &amd_iommu_list);
	iommu->index = amd_iommus_present++;

	अगर (unlikely(iommu->index >= MAX_IOMMUS)) अणु
		WARN(1, "System has more IOMMUs than supported by this driver\n");
		वापस -ENOSYS;
	पूर्ण

	/* Index is fine - add IOMMU to the array */
	amd_iommus[iommu->index] = iommu;

	/*
	 * Copy data from ACPI table entry to the iommu काष्ठा
	 */
	iommu->devid   = h->devid;
	iommu->cap_ptr = h->cap_ptr;
	iommu->pci_seg = h->pci_seg;
	iommu->mmio_phys = h->mmio_phys;

	चयन (h->type) अणु
	हाल 0x10:
		/* Check अगर IVHD EFR contains proper max banks/counters */
		अगर ((h->efr_attr != 0) &&
		    ((h->efr_attr & (0xF << 13)) != 0) &&
		    ((h->efr_attr & (0x3F << 17)) != 0))
			iommu->mmio_phys_end = MMIO_REG_END_OFFSET;
		अन्यथा
			iommu->mmio_phys_end = MMIO_CNTR_CONF_OFFSET;

		/*
		 * Note: GA (128-bit IRTE) mode requires cmpxchg16b supports.
		 * GAM also requires GA mode. Thereक्रमe, we need to
		 * check cmpxchg16b support beक्रमe enabling it.
		 */
		अगर (!boot_cpu_has(X86_FEATURE_CX16) ||
		    ((h->efr_attr & (0x1 << IOMMU_FEAT_GASUP_SHIFT)) == 0))
			amd_iommu_guest_ir = AMD_IOMMU_GUEST_IR_LEGACY;
		अवरोध;
	हाल 0x11:
	हाल 0x40:
		अगर (h->efr_reg & (1 << 9))
			iommu->mmio_phys_end = MMIO_REG_END_OFFSET;
		अन्यथा
			iommu->mmio_phys_end = MMIO_CNTR_CONF_OFFSET;

		/*
		 * Note: GA (128-bit IRTE) mode requires cmpxchg16b supports.
		 * XT, GAM also requires GA mode. Thereक्रमe, we need to
		 * check cmpxchg16b support beक्रमe enabling them.
		 */
		अगर (!boot_cpu_has(X86_FEATURE_CX16) ||
		    ((h->efr_reg & (0x1 << IOMMU_EFR_GASUP_SHIFT)) == 0)) अणु
			amd_iommu_guest_ir = AMD_IOMMU_GUEST_IR_LEGACY;
			अवरोध;
		पूर्ण

		अगर (h->efr_reg & BIT(IOMMU_EFR_XTSUP_SHIFT))
			amd_iommu_xt_mode = IRQ_REMAP_X2APIC_MODE;

		early_iommu_features_init(iommu, h);

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	iommu->mmio_base = iommu_map_mmio_space(iommu->mmio_phys,
						iommu->mmio_phys_end);
	अगर (!iommu->mmio_base)
		वापस -ENOMEM;

	अगर (alloc_cwwb_sem(iommu))
		वापस -ENOMEM;

	अगर (alloc_command_buffer(iommu))
		वापस -ENOMEM;

	अगर (alloc_event_buffer(iommu))
		वापस -ENOMEM;

	iommu->पूर्णांक_enabled = false;

	init_translation_status(iommu);
	अगर (translation_pre_enabled(iommu) && !is_kdump_kernel()) अणु
		iommu_disable(iommu);
		clear_translation_pre_enabled(iommu);
		pr_warn("Translation was enabled for IOMMU:%d but we are not in kdump mode\n",
			iommu->index);
	पूर्ण
	अगर (amd_iommu_pre_enabled)
		amd_iommu_pre_enabled = translation_pre_enabled(iommu);

	ret = init_iommu_from_acpi(iommu, h);
	अगर (ret)
		वापस ret;

	अगर (amd_iommu_irq_remap) अणु
		ret = amd_iommu_create_irq_करोमुख्य(iommu);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Make sure IOMMU is not considered to translate itself. The IVRS
	 * table tells us so, but this is a lie!
	 */
	amd_iommu_rlookup_table[iommu->devid] = शून्य;

	वापस 0;
पूर्ण

/**
 * get_highest_supported_ivhd_type - Look up the appropriate IVHD type
 * @ivrs: Poपूर्णांकer to the IVRS header
 *
 * This function search through all IVDB of the maximum supported IVHD
 */
अटल u8 get_highest_supported_ivhd_type(काष्ठा acpi_table_header *ivrs)
अणु
	u8 *base = (u8 *)ivrs;
	काष्ठा ivhd_header *ivhd = (काष्ठा ivhd_header *)
					(base + IVRS_HEADER_LENGTH);
	u8 last_type = ivhd->type;
	u16 devid = ivhd->devid;

	जबतक (((u8 *)ivhd - base < ivrs->length) &&
	       (ivhd->type <= ACPI_IVHD_TYPE_MAX_SUPPORTED)) अणु
		u8 *p = (u8 *) ivhd;

		अगर (ivhd->devid == devid)
			last_type = ivhd->type;
		ivhd = (काष्ठा ivhd_header *)(p + ivhd->length);
	पूर्ण

	वापस last_type;
पूर्ण

/*
 * Iterates over all IOMMU entries in the ACPI table, allocates the
 * IOMMU काष्ठाure and initializes it with init_iommu_one()
 */
अटल पूर्णांक __init init_iommu_all(काष्ठा acpi_table_header *table)
अणु
	u8 *p = (u8 *)table, *end = (u8 *)table;
	काष्ठा ivhd_header *h;
	काष्ठा amd_iommu *iommu;
	पूर्णांक ret;

	end += table->length;
	p += IVRS_HEADER_LENGTH;

	जबतक (p < end) अणु
		h = (काष्ठा ivhd_header *)p;
		अगर (*p == amd_iommu_target_ivhd_type) अणु

			DUMP_prपूर्णांकk("device: %02x:%02x.%01x cap: %04x "
				    "seg: %d flags: %01x info %04x\n",
				    PCI_BUS_NUM(h->devid), PCI_SLOT(h->devid),
				    PCI_FUNC(h->devid), h->cap_ptr,
				    h->pci_seg, h->flags, h->info);
			DUMP_prपूर्णांकk("       mmio-addr: %016llx\n",
				    h->mmio_phys);

			iommu = kzalloc(माप(काष्ठा amd_iommu), GFP_KERNEL);
			अगर (iommu == शून्य)
				वापस -ENOMEM;

			ret = init_iommu_one(iommu, h);
			अगर (ret)
				वापस ret;
		पूर्ण
		p += h->length;

	पूर्ण
	WARN_ON(p != end);

	वापस 0;
पूर्ण

अटल व्योम init_iommu_perf_ctr(काष्ठा amd_iommu *iommu)
अणु
	u64 val;
	काष्ठा pci_dev *pdev = iommu->dev;

	अगर (!iommu_feature(iommu, FEATURE_PC))
		वापस;

	amd_iommu_pc_present = true;

	pci_info(pdev, "IOMMU performance counters supported\n");

	val = पढ़ोl(iommu->mmio_base + MMIO_CNTR_CONF_OFFSET);
	iommu->max_banks = (u8) ((val >> 12) & 0x3f);
	iommu->max_counters = (u8) ((val >> 7) & 0xf);

	वापस;
पूर्ण

अटल sमाप_प्रकार amd_iommu_show_cap(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा amd_iommu *iommu = dev_to_amd_iommu(dev);
	वापस प्र_लिखो(buf, "%x\n", iommu->cap);
पूर्ण
अटल DEVICE_ATTR(cap, S_IRUGO, amd_iommu_show_cap, शून्य);

अटल sमाप_प्रकार amd_iommu_show_features(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा amd_iommu *iommu = dev_to_amd_iommu(dev);
	वापस प्र_लिखो(buf, "%llx\n", iommu->features);
पूर्ण
अटल DEVICE_ATTR(features, S_IRUGO, amd_iommu_show_features, शून्य);

अटल काष्ठा attribute *amd_iommu_attrs[] = अणु
	&dev_attr_cap.attr,
	&dev_attr_features.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group amd_iommu_group = अणु
	.name = "amd-iommu",
	.attrs = amd_iommu_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *amd_iommu_groups[] = अणु
	&amd_iommu_group,
	शून्य,
पूर्ण;

/*
 * Note: IVHD 0x11 and 0x40 also contains exact copy
 * of the IOMMU Extended Feature Register [MMIO Offset 0030h].
 * Default to EFR in IVHD since it is available sooner (i.e. beक्रमe PCI init).
 */
अटल व्योम __init late_iommu_features_init(काष्ठा amd_iommu *iommu)
अणु
	u64 features;

	अगर (!(iommu->cap & (1 << IOMMU_CAP_EFR)))
		वापस;

	/* पढ़ो extended feature bits */
	features = पढ़ोq(iommu->mmio_base + MMIO_EXT_FEATURES);

	अगर (!iommu->features) अणु
		iommu->features = features;
		वापस;
	पूर्ण

	/*
	 * Sanity check and warn अगर EFR values from
	 * IVHD and MMIO conflict.
	 */
	अगर (features != iommu->features)
		pr_warn(FW_WARN "EFR mismatch. Use IVHD EFR (%#llx : %#llx).\n",
			features, iommu->features);
पूर्ण

अटल पूर्णांक __init iommu_init_pci(काष्ठा amd_iommu *iommu)
अणु
	पूर्णांक cap_ptr = iommu->cap_ptr;
	पूर्णांक ret;

	iommu->dev = pci_get_करोमुख्य_bus_and_slot(0, PCI_BUS_NUM(iommu->devid),
						 iommu->devid & 0xff);
	अगर (!iommu->dev)
		वापस -ENODEV;

	/* Prevent binding other PCI device drivers to IOMMU devices */
	iommu->dev->match_driver = false;

	pci_पढ़ो_config_dword(iommu->dev, cap_ptr + MMIO_CAP_HDR_OFFSET,
			      &iommu->cap);

	अगर (!(iommu->cap & (1 << IOMMU_CAP_IOTLB)))
		amd_iommu_iotlb_sup = false;

	late_iommu_features_init(iommu);

	अगर (iommu_feature(iommu, FEATURE_GT)) अणु
		पूर्णांक glxval;
		u32 max_pasid;
		u64 pयंत्रax;

		pयंत्रax = iommu->features & FEATURE_PASID_MASK;
		pयंत्रax >>= FEATURE_PASID_SHIFT;
		max_pasid  = (1 << (pयंत्रax + 1)) - 1;

		amd_iommu_max_pasid = min(amd_iommu_max_pasid, max_pasid);

		BUG_ON(amd_iommu_max_pasid & ~PASID_MASK);

		glxval   = iommu->features & FEATURE_GLXVAL_MASK;
		glxval >>= FEATURE_GLXVAL_SHIFT;

		अगर (amd_iommu_max_glx_val == -1)
			amd_iommu_max_glx_val = glxval;
		अन्यथा
			amd_iommu_max_glx_val = min(amd_iommu_max_glx_val, glxval);
	पूर्ण

	अगर (iommu_feature(iommu, FEATURE_GT) &&
	    iommu_feature(iommu, FEATURE_PPR)) अणु
		iommu->is_iommu_v2   = true;
		amd_iommu_v2_present = true;
	पूर्ण

	अगर (iommu_feature(iommu, FEATURE_PPR) && alloc_ppr_log(iommu))
		वापस -ENOMEM;

	ret = iommu_init_ga(iommu);
	अगर (ret)
		वापस ret;

	अगर (iommu->cap & (1UL << IOMMU_CAP_NPCACHE))
		amd_iommu_np_cache = true;

	init_iommu_perf_ctr(iommu);

	अगर (is_rd890_iommu(iommu->dev)) अणु
		पूर्णांक i, j;

		iommu->root_pdev =
			pci_get_करोमुख्य_bus_and_slot(0, iommu->dev->bus->number,
						    PCI_DEVFN(0, 0));

		/*
		 * Some rd890 प्रणालीs may not be fully reconfigured by the
		 * BIOS, so it's necessary क्रम us to store this inक्रमmation so
		 * it can be reprogrammed on resume
		 */
		pci_पढ़ो_config_dword(iommu->dev, iommu->cap_ptr + 4,
				&iommu->stored_addr_lo);
		pci_पढ़ो_config_dword(iommu->dev, iommu->cap_ptr + 8,
				&iommu->stored_addr_hi);

		/* Low bit locks ग_लिखोs to configuration space */
		iommu->stored_addr_lo &= ~1;

		क्रम (i = 0; i < 6; i++)
			क्रम (j = 0; j < 0x12; j++)
				iommu->stored_l1[i][j] = iommu_पढ़ो_l1(iommu, i, j);

		क्रम (i = 0; i < 0x83; i++)
			iommu->stored_l2[i] = iommu_पढ़ो_l2(iommu, i);
	पूर्ण

	amd_iommu_erratum_746_workaround(iommu);
	amd_iommu_ats_ग_लिखो_check_workaround(iommu);

	iommu_device_sysfs_add(&iommu->iommu, &iommu->dev->dev,
			       amd_iommu_groups, "ivhd%d", iommu->index);
	iommu_device_रेजिस्टर(&iommu->iommu, &amd_iommu_ops, शून्य);

	वापस pci_enable_device(iommu->dev);
पूर्ण

अटल व्योम prपूर्णांक_iommu_info(व्योम)
अणु
	अटल स्थिर अक्षर * स्थिर feat_str[] = अणु
		"PreF", "PPR", "X2APIC", "NX", "GT", "[5]",
		"IA", "GA", "HE", "PC"
	पूर्ण;
	काष्ठा amd_iommu *iommu;

	क्रम_each_iommu(iommu) अणु
		काष्ठा pci_dev *pdev = iommu->dev;
		पूर्णांक i;

		pci_info(pdev, "Found IOMMU cap 0x%x\n", iommu->cap_ptr);

		अगर (iommu->cap & (1 << IOMMU_CAP_EFR)) अणु
			pci_info(pdev, "Extended features (%#llx):",
				 iommu->features);
			क्रम (i = 0; i < ARRAY_SIZE(feat_str); ++i) अणु
				अगर (iommu_feature(iommu, (1ULL << i)))
					pr_cont(" %s", feat_str[i]);
			पूर्ण

			अगर (iommu->features & FEATURE_GAM_VAPIC)
				pr_cont(" GA_vAPIC");

			pr_cont("\n");
		पूर्ण
	पूर्ण
	अगर (irq_remapping_enabled) अणु
		pr_info("Interrupt remapping enabled\n");
		अगर (AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir))
			pr_info("Virtual APIC enabled\n");
		अगर (amd_iommu_xt_mode == IRQ_REMAP_X2APIC_MODE)
			pr_info("X2APIC enabled\n");
	पूर्ण
पूर्ण

अटल पूर्णांक __init amd_iommu_init_pci(व्योम)
अणु
	काष्ठा amd_iommu *iommu;
	पूर्णांक ret;

	क्रम_each_iommu(iommu) अणु
		ret = iommu_init_pci(iommu);
		अगर (ret)
			अवरोध;

		/* Need to setup range after PCI init */
		iommu_set_cwwb_range(iommu);
	पूर्ण

	/*
	 * Order is important here to make sure any unity map requirements are
	 * fulfilled. The unity mappings are created and written to the device
	 * table during the amd_iommu_init_api() call.
	 *
	 * After that we call init_device_table_dma() to make sure any
	 * uninitialized DTE will block DMA, and in the end we flush the caches
	 * of all IOMMUs to make sure the changes to the device table are
	 * active.
	 */
	ret = amd_iommu_init_api();

	init_device_table_dma();

	क्रम_each_iommu(iommu)
		iommu_flush_all_caches(iommu);

	अगर (!ret)
		prपूर्णांक_iommu_info();

	वापस ret;
पूर्ण

/****************************************************************************
 *
 * The following functions initialize the MSI पूर्णांकerrupts क्रम all IOMMUs
 * in the प्रणाली. It's a bit challenging because there could be multiple
 * IOMMUs per PCI BDF but we can call pci_enable_msi(x) only once per
 * pci_dev.
 *
 ****************************************************************************/

अटल पूर्णांक iommu_setup_msi(काष्ठा amd_iommu *iommu)
अणु
	पूर्णांक r;

	r = pci_enable_msi(iommu->dev);
	अगर (r)
		वापस r;

	r = request_thपढ़ोed_irq(iommu->dev->irq,
				 amd_iommu_पूर्णांक_handler,
				 amd_iommu_पूर्णांक_thपढ़ो,
				 0, "AMD-Vi",
				 iommu);

	अगर (r) अणु
		pci_disable_msi(iommu->dev);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

जोड़ पूर्णांकcapxt अणु
	u64	capxt;
	काष्ठा अणु
		u64	reserved_0		:  2,
			dest_mode_logical	:  1,
			reserved_1		:  5,
			destid_0_23		: 24,
			vector			:  8,
			reserved_2		: 16,
			destid_24_31		:  8;
	पूर्ण;
पूर्ण __attribute__ ((packed));

/*
 * There isn't really any need to mask/unmask at the irqchip level because
 * the 64-bit INTCAPXT रेजिस्टरs can be updated atomically without tearing
 * when the affinity is being updated.
 */
अटल व्योम पूर्णांकcapxt_unmask_irq(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम पूर्णांकcapxt_mask_irq(काष्ठा irq_data *data)
अणु
पूर्ण

अटल काष्ठा irq_chip पूर्णांकcapxt_controller;

अटल पूर्णांक पूर्णांकcapxt_irqकरोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				       काष्ठा irq_data *irqd, bool reserve)
अणु
	काष्ठा amd_iommu *iommu = irqd->chip_data;
	काष्ठा irq_cfg *cfg = irqd_cfg(irqd);
	जोड़ पूर्णांकcapxt xt;

	xt.capxt = 0ULL;
	xt.dest_mode_logical = apic->dest_mode_logical;
	xt.vector = cfg->vector;
	xt.destid_0_23 = cfg->dest_apicid & GENMASK(23, 0);
	xt.destid_24_31 = cfg->dest_apicid >> 24;

	/**
	 * Current IOMMU implemtation uses the same IRQ क्रम all
	 * 3 IOMMU पूर्णांकerrupts.
	 */
	ग_लिखोq(xt.capxt, iommu->mmio_base + MMIO_INTCAPXT_EVT_OFFSET);
	ग_लिखोq(xt.capxt, iommu->mmio_base + MMIO_INTCAPXT_PPR_OFFSET);
	ग_लिखोq(xt.capxt, iommu->mmio_base + MMIO_INTCAPXT_GALOG_OFFSET);
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकcapxt_irqकरोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
					  काष्ठा irq_data *irqd)
अणु
	पूर्णांकcapxt_mask_irq(irqd);
पूर्ण


अटल पूर्णांक पूर्णांकcapxt_irqकरोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				    अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा irq_alloc_info *info = arg;
	पूर्णांक i, ret;

	अगर (!info || info->type != X86_IRQ_ALLOC_TYPE_AMDVI)
		वापस -EINVAL;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, arg);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = virq; i < virq + nr_irqs; i++) अणु
		काष्ठा irq_data *irqd = irq_करोमुख्य_get_irq_data(करोमुख्य, i);

		irqd->chip = &पूर्णांकcapxt_controller;
		irqd->chip_data = info->data;
		__irq_set_handler(i, handle_edge_irq, 0, "edge");
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकcapxt_irqकरोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				    अचिन्हित पूर्णांक nr_irqs)
अणु
	irq_करोमुख्य_मुक्त_irqs_top(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल पूर्णांक पूर्णांकcapxt_set_affinity(काष्ठा irq_data *irqd,
				 स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा irq_data *parent = irqd->parent_data;
	पूर्णांक ret;

	ret = parent->chip->irq_set_affinity(parent, mask, क्रमce);
	अगर (ret < 0 || ret == IRQ_SET_MASK_OK_DONE)
		वापस ret;

	वापस पूर्णांकcapxt_irqकरोमुख्य_activate(irqd->करोमुख्य, irqd, false);
पूर्ण

अटल काष्ठा irq_chip पूर्णांकcapxt_controller = अणु
	.name			= "IOMMU-MSI",
	.irq_unmask		= पूर्णांकcapxt_unmask_irq,
	.irq_mask		= पूर्णांकcapxt_mask_irq,
	.irq_ack		= irq_chip_ack_parent,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_affinity       = पूर्णांकcapxt_set_affinity,
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकcapxt_करोमुख्य_ops = अणु
	.alloc			= पूर्णांकcapxt_irqकरोमुख्य_alloc,
	.मुक्त			= पूर्णांकcapxt_irqकरोमुख्य_मुक्त,
	.activate		= पूर्णांकcapxt_irqकरोमुख्य_activate,
	.deactivate		= पूर्णांकcapxt_irqकरोमुख्य_deactivate,
पूर्ण;


अटल काष्ठा irq_करोमुख्य *iommu_irqकरोमुख्य;

अटल काष्ठा irq_करोमुख्य *iommu_get_irqकरोमुख्य(व्योम)
अणु
	काष्ठा fwnode_handle *fn;

	/* No need क्रम locking here (yet) as the init is single-thपढ़ोed */
	अगर (iommu_irqकरोमुख्य)
		वापस iommu_irqकरोमुख्य;

	fn = irq_करोमुख्य_alloc_named_fwnode("AMD-Vi-MSI");
	अगर (!fn)
		वापस शून्य;

	iommu_irqकरोमुख्य = irq_करोमुख्य_create_hierarchy(x86_vector_करोमुख्य, 0, 0,
						      fn, &पूर्णांकcapxt_करोमुख्य_ops,
						      शून्य);
	अगर (!iommu_irqकरोमुख्य)
		irq_करोमुख्य_मुक्त_fwnode(fn);

	वापस iommu_irqकरोमुख्य;
पूर्ण

अटल पूर्णांक iommu_setup_पूर्णांकcapxt(काष्ठा amd_iommu *iommu)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_alloc_info info;
	पूर्णांक irq, ret;

	करोमुख्य = iommu_get_irqकरोमुख्य();
	अगर (!करोमुख्य)
		वापस -ENXIO;

	init_irq_alloc_info(&info, शून्य);
	info.type = X86_IRQ_ALLOC_TYPE_AMDVI;
	info.data = iommu;

	irq = irq_करोमुख्य_alloc_irqs(करोमुख्य, 1, NUMA_NO_NODE, &info);
	अगर (irq < 0) अणु
		irq_करोमुख्य_हटाओ(करोमुख्य);
		वापस irq;
	पूर्ण

	ret = request_thपढ़ोed_irq(irq, amd_iommu_पूर्णांक_handler,
				   amd_iommu_पूर्णांक_thपढ़ो, 0, "AMD-Vi", iommu);
	अगर (ret) अणु
		irq_करोमुख्य_मुक्त_irqs(irq, 1);
		irq_करोमुख्य_हटाओ(करोमुख्य);
		वापस ret;
	पूर्ण

	iommu_feature_enable(iommu, CONTROL_INTCAPXT_EN);
	वापस 0;
पूर्ण

अटल पूर्णांक iommu_init_irq(काष्ठा amd_iommu *iommu)
अणु
	पूर्णांक ret;

	अगर (iommu->पूर्णांक_enabled)
		जाओ enable_faults;

	अगर (amd_iommu_xt_mode == IRQ_REMAP_X2APIC_MODE)
		ret = iommu_setup_पूर्णांकcapxt(iommu);
	अन्यथा अगर (iommu->dev->msi_cap)
		ret = iommu_setup_msi(iommu);
	अन्यथा
		ret = -ENODEV;

	अगर (ret)
		वापस ret;

	iommu->पूर्णांक_enabled = true;
enable_faults:
	iommu_feature_enable(iommu, CONTROL_EVT_INT_EN);

	अगर (iommu->ppr_log != शून्य)
		iommu_feature_enable(iommu, CONTROL_PPRINT_EN);

	iommu_ga_log_enable(iommu);

	वापस 0;
पूर्ण

/****************************************************************************
 *
 * The next functions beदीर्घ to the third pass of parsing the ACPI
 * table. In this last pass the memory mapping requirements are
 * gathered (like exclusion and unity mapping ranges).
 *
 ****************************************************************************/

अटल व्योम __init मुक्त_unity_maps(व्योम)
अणु
	काष्ठा unity_map_entry *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &amd_iommu_unity_map, list) अणु
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
पूर्ण

/* called क्रम unity map ACPI definition */
अटल पूर्णांक __init init_unity_map_range(काष्ठा ivmd_header *m)
अणु
	काष्ठा unity_map_entry *e = शून्य;
	अक्षर *s;

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (e == शून्य)
		वापस -ENOMEM;

	चयन (m->type) अणु
	शेष:
		kमुक्त(e);
		वापस 0;
	हाल ACPI_IVMD_TYPE:
		s = "IVMD_TYPEi\t\t\t";
		e->devid_start = e->devid_end = m->devid;
		अवरोध;
	हाल ACPI_IVMD_TYPE_ALL:
		s = "IVMD_TYPE_ALL\t\t";
		e->devid_start = 0;
		e->devid_end = amd_iommu_last_bdf;
		अवरोध;
	हाल ACPI_IVMD_TYPE_RANGE:
		s = "IVMD_TYPE_RANGE\t\t";
		e->devid_start = m->devid;
		e->devid_end = m->aux;
		अवरोध;
	पूर्ण
	e->address_start = PAGE_ALIGN(m->range_start);
	e->address_end = e->address_start + PAGE_ALIGN(m->range_length);
	e->prot = m->flags >> 1;

	/*
	 * Treat per-device exclusion ranges as r/w unity-mapped regions
	 * since some buggy BIOSes might lead to the overwritten exclusion
	 * range (exclusion_start and exclusion_length members). This
	 * happens when there are multiple exclusion ranges (IVMD entries)
	 * defined in ACPI table.
	 */
	अगर (m->flags & IVMD_FLAG_EXCL_RANGE)
		e->prot = (IVMD_FLAG_IW | IVMD_FLAG_IR) >> 1;

	DUMP_prपूर्णांकk("%s devid_start: %02x:%02x.%x devid_end: %02x:%02x.%x"
		    " range_start: %016llx range_end: %016llx flags: %x\n", s,
		    PCI_BUS_NUM(e->devid_start), PCI_SLOT(e->devid_start),
		    PCI_FUNC(e->devid_start), PCI_BUS_NUM(e->devid_end),
		    PCI_SLOT(e->devid_end), PCI_FUNC(e->devid_end),
		    e->address_start, e->address_end, m->flags);

	list_add_tail(&e->list, &amd_iommu_unity_map);

	वापस 0;
पूर्ण

/* iterates over all memory definitions we find in the ACPI table */
अटल पूर्णांक __init init_memory_definitions(काष्ठा acpi_table_header *table)
अणु
	u8 *p = (u8 *)table, *end = (u8 *)table;
	काष्ठा ivmd_header *m;

	end += table->length;
	p += IVRS_HEADER_LENGTH;

	जबतक (p < end) अणु
		m = (काष्ठा ivmd_header *)p;
		अगर (m->flags & (IVMD_FLAG_UNITY_MAP | IVMD_FLAG_EXCL_RANGE))
			init_unity_map_range(m);

		p += m->length;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Init the device table to not allow DMA access क्रम devices
 */
अटल व्योम init_device_table_dma(व्योम)
अणु
	u32 devid;

	क्रम (devid = 0; devid <= amd_iommu_last_bdf; ++devid) अणु
		set_dev_entry_bit(devid, DEV_ENTRY_VALID);
		set_dev_entry_bit(devid, DEV_ENTRY_TRANSLATION);
	पूर्ण
पूर्ण

अटल व्योम __init uninit_device_table_dma(व्योम)
अणु
	u32 devid;

	क्रम (devid = 0; devid <= amd_iommu_last_bdf; ++devid) अणु
		amd_iommu_dev_table[devid].data[0] = 0ULL;
		amd_iommu_dev_table[devid].data[1] = 0ULL;
	पूर्ण
पूर्ण

अटल व्योम init_device_table(व्योम)
अणु
	u32 devid;

	अगर (!amd_iommu_irq_remap)
		वापस;

	क्रम (devid = 0; devid <= amd_iommu_last_bdf; ++devid)
		set_dev_entry_bit(devid, DEV_ENTRY_IRQ_TBL_EN);
पूर्ण

अटल व्योम iommu_init_flags(काष्ठा amd_iommu *iommu)
अणु
	iommu->acpi_flags & IVHD_FLAG_HT_TUN_EN_MASK ?
		iommu_feature_enable(iommu, CONTROL_HT_TUN_EN) :
		iommu_feature_disable(iommu, CONTROL_HT_TUN_EN);

	iommu->acpi_flags & IVHD_FLAG_PASSPW_EN_MASK ?
		iommu_feature_enable(iommu, CONTROL_PASSPW_EN) :
		iommu_feature_disable(iommu, CONTROL_PASSPW_EN);

	iommu->acpi_flags & IVHD_FLAG_RESPASSPW_EN_MASK ?
		iommu_feature_enable(iommu, CONTROL_RESPASSPW_EN) :
		iommu_feature_disable(iommu, CONTROL_RESPASSPW_EN);

	iommu->acpi_flags & IVHD_FLAG_ISOC_EN_MASK ?
		iommu_feature_enable(iommu, CONTROL_ISOC_EN) :
		iommu_feature_disable(iommu, CONTROL_ISOC_EN);

	/*
	 * make IOMMU memory accesses cache coherent
	 */
	iommu_feature_enable(iommu, CONTROL_COHERENT_EN);

	/* Set IOTLB invalidation समयout to 1s */
	iommu_set_inv_tlb_समयout(iommu, CTRL_INV_TO_1S);
पूर्ण

अटल व्योम iommu_apply_resume_quirks(काष्ठा amd_iommu *iommu)
अणु
	पूर्णांक i, j;
	u32 ioc_feature_control;
	काष्ठा pci_dev *pdev = iommu->root_pdev;

	/* RD890 BIOSes may not have completely reconfigured the iommu */
	अगर (!is_rd890_iommu(iommu->dev) || !pdev)
		वापस;

	/*
	 * First, we need to ensure that the iommu is enabled. This is
	 * controlled by a रेजिस्टर in the northbridge
	 */

	/* Select Northbridge indirect रेजिस्टर 0x75 and enable writing */
	pci_ग_लिखो_config_dword(pdev, 0x60, 0x75 | (1 << 7));
	pci_पढ़ो_config_dword(pdev, 0x64, &ioc_feature_control);

	/* Enable the iommu */
	अगर (!(ioc_feature_control & 0x1))
		pci_ग_लिखो_config_dword(pdev, 0x64, ioc_feature_control | 1);

	/* Restore the iommu BAR */
	pci_ग_लिखो_config_dword(iommu->dev, iommu->cap_ptr + 4,
			       iommu->stored_addr_lo);
	pci_ग_लिखो_config_dword(iommu->dev, iommu->cap_ptr + 8,
			       iommu->stored_addr_hi);

	/* Restore the l1 indirect regs क्रम each of the 6 l1s */
	क्रम (i = 0; i < 6; i++)
		क्रम (j = 0; j < 0x12; j++)
			iommu_ग_लिखो_l1(iommu, i, j, iommu->stored_l1[i][j]);

	/* Restore the l2 indirect regs */
	क्रम (i = 0; i < 0x83; i++)
		iommu_ग_लिखो_l2(iommu, i, iommu->stored_l2[i]);

	/* Lock PCI setup रेजिस्टरs */
	pci_ग_लिखो_config_dword(iommu->dev, iommu->cap_ptr + 4,
			       iommu->stored_addr_lo | 1);
पूर्ण

अटल व्योम iommu_enable_ga(काष्ठा amd_iommu *iommu)
अणु
#अगर_घोषित CONFIG_IRQ_REMAP
	चयन (amd_iommu_guest_ir) अणु
	हाल AMD_IOMMU_GUEST_IR_VAPIC:
		iommu_feature_enable(iommu, CONTROL_GAM_EN);
		fallthrough;
	हाल AMD_IOMMU_GUEST_IR_LEGACY_GA:
		iommu_feature_enable(iommu, CONTROL_GA_EN);
		iommu->irte_ops = &irte_128_ops;
		अवरोध;
	शेष:
		iommu->irte_ops = &irte_32_ops;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम early_enable_iommu(काष्ठा amd_iommu *iommu)
अणु
	iommu_disable(iommu);
	iommu_init_flags(iommu);
	iommu_set_device_table(iommu);
	iommu_enable_command_buffer(iommu);
	iommu_enable_event_buffer(iommu);
	iommu_set_exclusion_range(iommu);
	iommu_enable_ga(iommu);
	iommu_enable_xt(iommu);
	iommu_enable(iommu);
	iommu_flush_all_caches(iommu);
पूर्ण

/*
 * This function finally enables all IOMMUs found in the प्रणाली after
 * they have been initialized.
 *
 * Or अगर in kdump kernel and IOMMUs are all pre-enabled, try to copy
 * the old content of device table entries. Not this हाल or copy failed,
 * just जारी as normal kernel करोes.
 */
अटल व्योम early_enable_iommus(व्योम)
अणु
	काष्ठा amd_iommu *iommu;


	अगर (!copy_device_table()) अणु
		/*
		 * If come here because of failure in copying device table from old
		 * kernel with all IOMMUs enabled, prपूर्णांक error message and try to
		 * मुक्त allocated old_dev_tbl_cpy.
		 */
		अगर (amd_iommu_pre_enabled)
			pr_err("Failed to copy DEV table from previous kernel.\n");
		अगर (old_dev_tbl_cpy != शून्य)
			मुक्त_pages((अचिन्हित दीर्घ)old_dev_tbl_cpy,
					get_order(dev_table_size));

		क्रम_each_iommu(iommu) अणु
			clear_translation_pre_enabled(iommu);
			early_enable_iommu(iommu);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("Copied DEV table from previous kernel.\n");
		मुक्त_pages((अचिन्हित दीर्घ)amd_iommu_dev_table,
				get_order(dev_table_size));
		amd_iommu_dev_table = old_dev_tbl_cpy;
		क्रम_each_iommu(iommu) अणु
			iommu_disable_command_buffer(iommu);
			iommu_disable_event_buffer(iommu);
			iommu_enable_command_buffer(iommu);
			iommu_enable_event_buffer(iommu);
			iommu_enable_ga(iommu);
			iommu_enable_xt(iommu);
			iommu_set_device_table(iommu);
			iommu_flush_all_caches(iommu);
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_IRQ_REMAP
	अगर (AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir))
		amd_iommu_irq_ops.capability |= (1 << IRQ_POSTING_CAP);
#पूर्ण_अगर
पूर्ण

अटल व्योम enable_iommus_v2(व्योम)
अणु
	काष्ठा amd_iommu *iommu;

	क्रम_each_iommu(iommu) अणु
		iommu_enable_ppr_log(iommu);
		iommu_enable_gt(iommu);
	पूर्ण
पूर्ण

अटल व्योम enable_iommus(व्योम)
अणु
	early_enable_iommus();

	enable_iommus_v2();
पूर्ण

अटल व्योम disable_iommus(व्योम)
अणु
	काष्ठा amd_iommu *iommu;

	क्रम_each_iommu(iommu)
		iommu_disable(iommu);

#अगर_घोषित CONFIG_IRQ_REMAP
	अगर (AMD_IOMMU_GUEST_IR_VAPIC(amd_iommu_guest_ir))
		amd_iommu_irq_ops.capability &= ~(1 << IRQ_POSTING_CAP);
#पूर्ण_अगर
पूर्ण

/*
 * Suspend/Resume support
 * disable suspend until real resume implemented
 */

अटल व्योम amd_iommu_resume(व्योम)
अणु
	काष्ठा amd_iommu *iommu;

	क्रम_each_iommu(iommu)
		iommu_apply_resume_quirks(iommu);

	/* re-load the hardware */
	enable_iommus();

	amd_iommu_enable_पूर्णांकerrupts();
पूर्ण

अटल पूर्णांक amd_iommu_suspend(व्योम)
अणु
	/* disable IOMMUs to go out of the way क्रम BIOS */
	disable_iommus();

	वापस 0;
पूर्ण

अटल काष्ठा syscore_ops amd_iommu_syscore_ops = अणु
	.suspend = amd_iommu_suspend,
	.resume = amd_iommu_resume,
पूर्ण;

अटल व्योम __init मुक्त_iommu_resources(व्योम)
अणु
	kmemleak_मुक्त(irq_lookup_table);
	मुक्त_pages((अचिन्हित दीर्घ)irq_lookup_table,
		   get_order(rlookup_table_size));
	irq_lookup_table = शून्य;

	kmem_cache_destroy(amd_iommu_irq_cache);
	amd_iommu_irq_cache = शून्य;

	मुक्त_pages((अचिन्हित दीर्घ)amd_iommu_rlookup_table,
		   get_order(rlookup_table_size));
	amd_iommu_rlookup_table = शून्य;

	मुक्त_pages((अचिन्हित दीर्घ)amd_iommu_alias_table,
		   get_order(alias_table_size));
	amd_iommu_alias_table = शून्य;

	मुक्त_pages((अचिन्हित दीर्घ)amd_iommu_dev_table,
		   get_order(dev_table_size));
	amd_iommu_dev_table = शून्य;

	मुक्त_iommu_all();
पूर्ण

/* SB IOAPIC is always on this device in AMD प्रणालीs */
#घोषणा IOAPIC_SB_DEVID		((0x00 << 8) | PCI_DEVFN(0x14, 0))

अटल bool __init check_ioapic_inक्रमmation(व्योम)
अणु
	स्थिर अक्षर *fw_bug = FW_BUG;
	bool ret, has_sb_ioapic;
	पूर्णांक idx;

	has_sb_ioapic = false;
	ret           = false;

	/*
	 * If we have map overrides on the kernel command line the
	 * messages in this function might not describe firmware bugs
	 * anymore - so be careful
	 */
	अगर (cmdline_maps)
		fw_bug = "";

	क्रम (idx = 0; idx < nr_ioapics; idx++) अणु
		पूर्णांक devid, id = mpc_ioapic_id(idx);

		devid = get_ioapic_devid(id);
		अगर (devid < 0) अणु
			pr_err("%s: IOAPIC[%d] not in IVRS table\n",
				fw_bug, id);
			ret = false;
		पूर्ण अन्यथा अगर (devid == IOAPIC_SB_DEVID) अणु
			has_sb_ioapic = true;
			ret           = true;
		पूर्ण
	पूर्ण

	अगर (!has_sb_ioapic) अणु
		/*
		 * We expect the SB IOAPIC to be listed in the IVRS
		 * table. The प्रणाली समयr is connected to the SB IOAPIC
		 * and अगर we करोn't have it in the list the प्रणाली will
		 * panic at boot समय.  This situation usually happens
		 * when the BIOS is buggy and provides us the wrong
		 * device id क्रम the IOAPIC in the प्रणाली.
		 */
		pr_err("%s: No southbridge IOAPIC found\n", fw_bug);
	पूर्ण

	अगर (!ret)
		pr_err("Disabling interrupt remapping\n");

	वापस ret;
पूर्ण

अटल व्योम __init मुक्त_dma_resources(व्योम)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)amd_iommu_pd_alloc_biपंचांगap,
		   get_order(MAX_DOMAIN_ID/8));
	amd_iommu_pd_alloc_biपंचांगap = शून्य;

	मुक्त_unity_maps();
पूर्ण

अटल व्योम __init ivinfo_init(व्योम *ivrs)
अणु
	amd_iommu_ivinfo = *((u32 *)(ivrs + IOMMU_IVINFO_OFFSET));
पूर्ण

/*
 * This is the hardware init function क्रम AMD IOMMU in the प्रणाली.
 * This function is called either from amd_iommu_init or from the पूर्णांकerrupt
 * remapping setup code.
 *
 * This function basically parses the ACPI table क्रम AMD IOMMU (IVRS)
 * four बार:
 *
 *	1 pass) Discover the most comprehensive IVHD type to use.
 *
 *	2 pass) Find the highest PCI device id the driver has to handle.
 *		Upon this inक्रमmation the size of the data काष्ठाures is
 *		determined that needs to be allocated.
 *
 *	3 pass) Initialize the data काष्ठाures just allocated with the
 *		inक्रमmation in the ACPI table about available AMD IOMMUs
 *		in the प्रणाली. It also maps the PCI devices in the
 *		प्रणाली to specअगरic IOMMUs
 *
 *	4 pass) After the basic data काष्ठाures are allocated and
 *		initialized we update them with inक्रमmation about memory
 *		remapping requirements parsed out of the ACPI table in
 *		this last pass.
 *
 * After everything is set up the IOMMUs are enabled and the necessary
 * hotplug and suspend notअगरiers are रेजिस्टरed.
 */
अटल पूर्णांक __init early_amd_iommu_init(व्योम)
अणु
	काष्ठा acpi_table_header *ivrs_base;
	पूर्णांक i, remap_cache_sz, ret;
	acpi_status status;

	अगर (!amd_iommu_detected)
		वापस -ENODEV;

	status = acpi_get_table("IVRS", 0, &ivrs_base);
	अगर (status == AE_NOT_FOUND)
		वापस -ENODEV;
	अन्यथा अगर (ACPI_FAILURE(status)) अणु
		स्थिर अक्षर *err = acpi_क्रमmat_exception(status);
		pr_err("IVRS table error: %s\n", err);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Validate checksum here so we करोn't need to करो it when
	 * we actually parse the table
	 */
	ret = check_ivrs_checksum(ivrs_base);
	अगर (ret)
		जाओ out;

	ivinfo_init(ivrs_base);

	amd_iommu_target_ivhd_type = get_highest_supported_ivhd_type(ivrs_base);
	DUMP_prपूर्णांकk("Using IVHD type %#x\n", amd_iommu_target_ivhd_type);

	/*
	 * First parse ACPI tables to find the largest Bus/Dev/Func
	 * we need to handle. Upon this inक्रमmation the shared data
	 * काष्ठाures क्रम the IOMMUs in the प्रणाली will be allocated
	 */
	ret = find_last_devid_acpi(ivrs_base);
	अगर (ret)
		जाओ out;

	dev_table_size     = tbl_size(DEV_TABLE_ENTRY_SIZE);
	alias_table_size   = tbl_size(ALIAS_TABLE_ENTRY_SIZE);
	rlookup_table_size = tbl_size(RLOOKUP_TABLE_ENTRY_SIZE);

	/* Device table - directly used by all IOMMUs */
	ret = -ENOMEM;
	amd_iommu_dev_table = (व्योम *)__get_मुक्त_pages(
				      GFP_KERNEL | __GFP_ZERO | GFP_DMA32,
				      get_order(dev_table_size));
	अगर (amd_iommu_dev_table == शून्य)
		जाओ out;

	/*
	 * Alias table - map PCI Bus/Dev/Func to Bus/Dev/Func the
	 * IOMMU see क्रम that device
	 */
	amd_iommu_alias_table = (व्योम *)__get_मुक्त_pages(GFP_KERNEL,
			get_order(alias_table_size));
	अगर (amd_iommu_alias_table == शून्य)
		जाओ out;

	/* IOMMU rlookup table - find the IOMMU क्रम a specअगरic device */
	amd_iommu_rlookup_table = (व्योम *)__get_मुक्त_pages(
			GFP_KERNEL | __GFP_ZERO,
			get_order(rlookup_table_size));
	अगर (amd_iommu_rlookup_table == शून्य)
		जाओ out;

	amd_iommu_pd_alloc_biपंचांगap = (व्योम *)__get_मुक्त_pages(
					    GFP_KERNEL | __GFP_ZERO,
					    get_order(MAX_DOMAIN_ID/8));
	अगर (amd_iommu_pd_alloc_biपंचांगap == शून्य)
		जाओ out;

	/*
	 * let all alias entries poपूर्णांक to itself
	 */
	क्रम (i = 0; i <= amd_iommu_last_bdf; ++i)
		amd_iommu_alias_table[i] = i;

	/*
	 * never allocate करोमुख्य 0 because its used as the non-allocated and
	 * error value placeholder
	 */
	__set_bit(0, amd_iommu_pd_alloc_biपंचांगap);

	/*
	 * now the data काष्ठाures are allocated and basically initialized
	 * start the real acpi table scan
	 */
	ret = init_iommu_all(ivrs_base);
	अगर (ret)
		जाओ out;

	/* Disable any previously enabled IOMMUs */
	अगर (!is_kdump_kernel() || amd_iommu_disabled)
		disable_iommus();

	अगर (amd_iommu_irq_remap)
		amd_iommu_irq_remap = check_ioapic_inक्रमmation();

	अगर (amd_iommu_irq_remap) अणु
		/*
		 * Interrupt remapping enabled, create kmem_cache क्रम the
		 * remapping tables.
		 */
		ret = -ENOMEM;
		अगर (!AMD_IOMMU_GUEST_IR_GA(amd_iommu_guest_ir))
			remap_cache_sz = MAX_IRQS_PER_TABLE * माप(u32);
		अन्यथा
			remap_cache_sz = MAX_IRQS_PER_TABLE * (माप(u64) * 2);
		amd_iommu_irq_cache = kmem_cache_create("irq_remap_cache",
							remap_cache_sz,
							DTE_INTTAB_ALIGNMENT,
							0, शून्य);
		अगर (!amd_iommu_irq_cache)
			जाओ out;

		irq_lookup_table = (व्योम *)__get_मुक्त_pages(
				GFP_KERNEL | __GFP_ZERO,
				get_order(rlookup_table_size));
		kmemleak_alloc(irq_lookup_table, rlookup_table_size,
			       1, GFP_KERNEL);
		अगर (!irq_lookup_table)
			जाओ out;
	पूर्ण

	ret = init_memory_definitions(ivrs_base);
	अगर (ret)
		जाओ out;

	/* init the device table */
	init_device_table();

out:
	/* Don't leak any ACPI memory */
	acpi_put_table(ivrs_base);

	वापस ret;
पूर्ण

अटल पूर्णांक amd_iommu_enable_पूर्णांकerrupts(व्योम)
अणु
	काष्ठा amd_iommu *iommu;
	पूर्णांक ret = 0;

	क्रम_each_iommu(iommu) अणु
		ret = iommu_init_irq(iommu);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल bool detect_ivrs(व्योम)
अणु
	काष्ठा acpi_table_header *ivrs_base;
	acpi_status status;
	पूर्णांक i;

	status = acpi_get_table("IVRS", 0, &ivrs_base);
	अगर (status == AE_NOT_FOUND)
		वापस false;
	अन्यथा अगर (ACPI_FAILURE(status)) अणु
		स्थिर अक्षर *err = acpi_क्रमmat_exception(status);
		pr_err("IVRS table error: %s\n", err);
		वापस false;
	पूर्ण

	acpi_put_table(ivrs_base);

	/* Don't use IOMMU अगर there is Stoney Ridge graphics */
	क्रम (i = 0; i < 32; i++) अणु
		u32 pci_id;

		pci_id = पढ़ो_pci_config(0, i, 0, 0);
		अगर ((pci_id & 0xffff) == 0x1002 && (pci_id >> 16) == 0x98e4) अणु
			pr_info("Disable IOMMU on Stoney Ridge\n");
			वापस false;
		पूर्ण
	पूर्ण

	/* Make sure ACS will be enabled during PCI probe */
	pci_request_acs();

	वापस true;
पूर्ण

/****************************************************************************
 *
 * AMD IOMMU Initialization State Machine
 *
 ****************************************************************************/

अटल पूर्णांक __init state_next(व्योम)
अणु
	पूर्णांक ret = 0;

	चयन (init_state) अणु
	हाल IOMMU_START_STATE:
		अगर (!detect_ivrs()) अणु
			init_state	= IOMMU_NOT_FOUND;
			ret		= -ENODEV;
		पूर्ण अन्यथा अणु
			init_state	= IOMMU_IVRS_DETECTED;
		पूर्ण
		अवरोध;
	हाल IOMMU_IVRS_DETECTED:
		अगर (amd_iommu_disabled) अणु
			init_state = IOMMU_CMDLINE_DISABLED;
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			ret = early_amd_iommu_init();
			init_state = ret ? IOMMU_INIT_ERROR : IOMMU_ACPI_FINISHED;
		पूर्ण
		अवरोध;
	हाल IOMMU_ACPI_FINISHED:
		early_enable_iommus();
		x86_platक्रमm.iommu_shutकरोwn = disable_iommus;
		init_state = IOMMU_ENABLED;
		अवरोध;
	हाल IOMMU_ENABLED:
		रेजिस्टर_syscore_ops(&amd_iommu_syscore_ops);
		ret = amd_iommu_init_pci();
		init_state = ret ? IOMMU_INIT_ERROR : IOMMU_PCI_INIT;
		enable_iommus_v2();
		अवरोध;
	हाल IOMMU_PCI_INIT:
		ret = amd_iommu_enable_पूर्णांकerrupts();
		init_state = ret ? IOMMU_INIT_ERROR : IOMMU_INTERRUPTS_EN;
		अवरोध;
	हाल IOMMU_INTERRUPTS_EN:
		ret = amd_iommu_init_dma_ops();
		init_state = ret ? IOMMU_INIT_ERROR : IOMMU_DMA_OPS;
		अवरोध;
	हाल IOMMU_DMA_OPS:
		init_state = IOMMU_INITIALIZED;
		अवरोध;
	हाल IOMMU_INITIALIZED:
		/* Nothing to करो */
		अवरोध;
	हाल IOMMU_NOT_FOUND:
	हाल IOMMU_INIT_ERROR:
	हाल IOMMU_CMDLINE_DISABLED:
		/* Error states => करो nothing */
		ret = -EINVAL;
		अवरोध;
	शेष:
		/* Unknown state */
		BUG();
	पूर्ण

	अगर (ret) अणु
		मुक्त_dma_resources();
		अगर (!irq_remapping_enabled) अणु
			disable_iommus();
			मुक्त_iommu_resources();
		पूर्ण अन्यथा अणु
			काष्ठा amd_iommu *iommu;

			uninit_device_table_dma();
			क्रम_each_iommu(iommu)
				iommu_flush_all_caches(iommu);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __init iommu_go_to_state(क्रमागत iommu_init_state state)
अणु
	पूर्णांक ret = -EINVAL;

	जबतक (init_state != state) अणु
		अगर (init_state == IOMMU_NOT_FOUND         ||
		    init_state == IOMMU_INIT_ERROR        ||
		    init_state == IOMMU_CMDLINE_DISABLED)
			अवरोध;
		ret = state_next();
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IRQ_REMAP
पूर्णांक __init amd_iommu_prepare(व्योम)
अणु
	पूर्णांक ret;

	amd_iommu_irq_remap = true;

	ret = iommu_go_to_state(IOMMU_ACPI_FINISHED);
	अगर (ret) अणु
		amd_iommu_irq_remap = false;
		वापस ret;
	पूर्ण

	वापस amd_iommu_irq_remap ? 0 : -ENODEV;
पूर्ण

पूर्णांक __init amd_iommu_enable(व्योम)
अणु
	पूर्णांक ret;

	ret = iommu_go_to_state(IOMMU_ENABLED);
	अगर (ret)
		वापस ret;

	irq_remapping_enabled = 1;
	वापस amd_iommu_xt_mode;
पूर्ण

व्योम amd_iommu_disable(व्योम)
अणु
	amd_iommu_suspend();
पूर्ण

पूर्णांक amd_iommu_reenable(पूर्णांक mode)
अणु
	amd_iommu_resume();

	वापस 0;
पूर्ण

पूर्णांक __init amd_iommu_enable_faulting(व्योम)
अणु
	/* We enable MSI later when PCI is initialized */
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * This is the core init function क्रम AMD IOMMU hardware in the प्रणाली.
 * This function is called from the generic x86 DMA layer initialization
 * code.
 */
अटल पूर्णांक __init amd_iommu_init(व्योम)
अणु
	काष्ठा amd_iommu *iommu;
	पूर्णांक ret;

	ret = iommu_go_to_state(IOMMU_INITIALIZED);
#अगर_घोषित CONFIG_GART_IOMMU
	अगर (ret && list_empty(&amd_iommu_list)) अणु
		/*
		 * We failed to initialize the AMD IOMMU - try fallback
		 * to GART अगर possible.
		 */
		gart_iommu_init();
	पूर्ण
#पूर्ण_अगर

	क्रम_each_iommu(iommu)
		amd_iommu_debugfs_setup(iommu);

	वापस ret;
पूर्ण

अटल bool amd_iommu_sme_check(व्योम)
अणु
	अगर (!sme_active() || (boot_cpu_data.x86 != 0x17))
		वापस true;

	/* For Fam17h, a specअगरic level of support is required */
	अगर (boot_cpu_data.microcode >= 0x08001205)
		वापस true;

	अगर ((boot_cpu_data.microcode >= 0x08001126) &&
	    (boot_cpu_data.microcode <= 0x080011ff))
		वापस true;

	pr_notice("IOMMU not currently supported when SME is active\n");

	वापस false;
पूर्ण

/****************************************************************************
 *
 * Early detect code. This code runs at IOMMU detection समय in the DMA
 * layer. It just looks अगर there is an IVRS ACPI table to detect AMD
 * IOMMUs
 *
 ****************************************************************************/
पूर्णांक __init amd_iommu_detect(व्योम)
अणु
	पूर्णांक ret;

	अगर (no_iommu || (iommu_detected && !gart_iommu_aperture))
		वापस -ENODEV;

	अगर (!amd_iommu_sme_check())
		वापस -ENODEV;

	ret = iommu_go_to_state(IOMMU_IVRS_DETECTED);
	अगर (ret)
		वापस ret;

	amd_iommu_detected = true;
	iommu_detected = 1;
	x86_init.iommu.iommu_init = amd_iommu_init;

	वापस 1;
पूर्ण

/****************************************************************************
 *
 * Parsing functions क्रम the AMD IOMMU specअगरic kernel command line
 * options.
 *
 ****************************************************************************/

अटल पूर्णांक __init parse_amd_iommu_dump(अक्षर *str)
अणु
	amd_iommu_dump = true;

	वापस 1;
पूर्ण

अटल पूर्णांक __init parse_amd_iommu_पूर्णांकr(अक्षर *str)
अणु
	क्रम (; *str; ++str) अणु
		अगर (म_भेदन(str, "legacy", 6) == 0) अणु
			amd_iommu_guest_ir = AMD_IOMMU_GUEST_IR_LEGACY_GA;
			अवरोध;
		पूर्ण
		अगर (म_भेदन(str, "vapic", 5) == 0) अणु
			amd_iommu_guest_ir = AMD_IOMMU_GUEST_IR_VAPIC;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक __init parse_amd_iommu_options(अक्षर *str)
अणु
	क्रम (; *str; ++str) अणु
		अगर (म_भेदन(str, "fullflush", 9) == 0)
			amd_iommu_unmap_flush = true;
		अगर (म_भेदन(str, "off", 3) == 0)
			amd_iommu_disabled = true;
		अगर (म_भेदन(str, "force_isolation", 15) == 0)
			amd_iommu_क्रमce_isolation = true;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक __init parse_ivrs_ioapic(अक्षर *str)
अणु
	अचिन्हित पूर्णांक bus, dev, fn;
	पूर्णांक ret, id, i;
	u16 devid;

	ret = माला_पूछो(str, "[%d]=%x:%x.%x", &id, &bus, &dev, &fn);

	अगर (ret != 4) अणु
		pr_err("Invalid command line: ivrs_ioapic%s\n", str);
		वापस 1;
	पूर्ण

	अगर (early_ioapic_map_size == EARLY_MAP_SIZE) अणु
		pr_err("Early IOAPIC map overflow - ignoring ivrs_ioapic%s\n",
			str);
		वापस 1;
	पूर्ण

	devid = ((bus & 0xff) << 8) | ((dev & 0x1f) << 3) | (fn & 0x7);

	cmdline_maps			= true;
	i				= early_ioapic_map_size++;
	early_ioapic_map[i].id		= id;
	early_ioapic_map[i].devid	= devid;
	early_ioapic_map[i].cmd_line	= true;

	वापस 1;
पूर्ण

अटल पूर्णांक __init parse_ivrs_hpet(अक्षर *str)
अणु
	अचिन्हित पूर्णांक bus, dev, fn;
	पूर्णांक ret, id, i;
	u16 devid;

	ret = माला_पूछो(str, "[%d]=%x:%x.%x", &id, &bus, &dev, &fn);

	अगर (ret != 4) अणु
		pr_err("Invalid command line: ivrs_hpet%s\n", str);
		वापस 1;
	पूर्ण

	अगर (early_hpet_map_size == EARLY_MAP_SIZE) अणु
		pr_err("Early HPET map overflow - ignoring ivrs_hpet%s\n",
			str);
		वापस 1;
	पूर्ण

	devid = ((bus & 0xff) << 8) | ((dev & 0x1f) << 3) | (fn & 0x7);

	cmdline_maps			= true;
	i				= early_hpet_map_size++;
	early_hpet_map[i].id		= id;
	early_hpet_map[i].devid		= devid;
	early_hpet_map[i].cmd_line	= true;

	वापस 1;
पूर्ण

अटल पूर्णांक __init parse_ivrs_acpihid(अक्षर *str)
अणु
	u32 bus, dev, fn;
	अक्षर *hid, *uid, *p;
	अक्षर acpiid[ACPIHID_UID_LEN + ACPIHID_HID_LEN] = अणु0पूर्ण;
	पूर्णांक ret, i;

	ret = माला_पूछो(str, "[%x:%x.%x]=%s", &bus, &dev, &fn, acpiid);
	अगर (ret != 4) अणु
		pr_err("Invalid command line: ivrs_acpihid(%s)\n", str);
		वापस 1;
	पूर्ण

	p = acpiid;
	hid = strsep(&p, ":");
	uid = p;

	अगर (!hid || !(*hid) || !uid) अणु
		pr_err("Invalid command line: hid or uid\n");
		वापस 1;
	पूर्ण

	i = early_acpihid_map_size++;
	स_नकल(early_acpihid_map[i].hid, hid, म_माप(hid));
	स_नकल(early_acpihid_map[i].uid, uid, म_माप(uid));
	early_acpihid_map[i].devid =
		((bus & 0xff) << 8) | ((dev & 0x1f) << 3) | (fn & 0x7);
	early_acpihid_map[i].cmd_line	= true;

	वापस 1;
पूर्ण

__setup("amd_iommu_dump",	parse_amd_iommu_dump);
__setup("amd_iommu=",		parse_amd_iommu_options);
__setup("amd_iommu_intr=",	parse_amd_iommu_पूर्णांकr);
__setup("ivrs_ioapic",		parse_ivrs_ioapic);
__setup("ivrs_hpet",		parse_ivrs_hpet);
__setup("ivrs_acpihid",		parse_ivrs_acpihid);

IOMMU_INIT_FINISH(amd_iommu_detect,
		  gart_iommu_hole_init,
		  शून्य,
		  शून्य);

bool amd_iommu_v2_supported(व्योम)
अणु
	वापस amd_iommu_v2_present;
पूर्ण
EXPORT_SYMBOL(amd_iommu_v2_supported);

काष्ठा amd_iommu *get_amd_iommu(अचिन्हित पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक i = 0;
	काष्ठा amd_iommu *iommu;

	क्रम_each_iommu(iommu)
		अगर (i++ == idx)
			वापस iommu;
	वापस शून्य;
पूर्ण

/****************************************************************************
 *
 * IOMMU EFR Perक्रमmance Counter support functionality. This code allows
 * access to the IOMMU PC functionality.
 *
 ****************************************************************************/

u8 amd_iommu_pc_get_max_banks(अचिन्हित पूर्णांक idx)
अणु
	काष्ठा amd_iommu *iommu = get_amd_iommu(idx);

	अगर (iommu)
		वापस iommu->max_banks;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(amd_iommu_pc_get_max_banks);

bool amd_iommu_pc_supported(व्योम)
अणु
	वापस amd_iommu_pc_present;
पूर्ण
EXPORT_SYMBOL(amd_iommu_pc_supported);

u8 amd_iommu_pc_get_max_counters(अचिन्हित पूर्णांक idx)
अणु
	काष्ठा amd_iommu *iommu = get_amd_iommu(idx);

	अगर (iommu)
		वापस iommu->max_counters;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(amd_iommu_pc_get_max_counters);

अटल पूर्णांक iommu_pc_get_set_reg(काष्ठा amd_iommu *iommu, u8 bank, u8 cntr,
				u8 fxn, u64 *value, bool is_ग_लिखो)
अणु
	u32 offset;
	u32 max_offset_lim;

	/* Make sure the IOMMU PC resource is available */
	अगर (!amd_iommu_pc_present)
		वापस -ENODEV;

	/* Check क्रम valid iommu and pc रेजिस्टर indexing */
	अगर (WARN_ON(!iommu || (fxn > 0x28) || (fxn & 7)))
		वापस -ENODEV;

	offset = (u32)(((0x40 | bank) << 12) | (cntr << 8) | fxn);

	/* Limit the offset to the hw defined mmio region aperture */
	max_offset_lim = (u32)(((0x40 | iommu->max_banks) << 12) |
				(iommu->max_counters << 8) | 0x28);
	अगर ((offset < MMIO_CNTR_REG_OFFSET) ||
	    (offset > max_offset_lim))
		वापस -EINVAL;

	अगर (is_ग_लिखो) अणु
		u64 val = *value & GENMASK_ULL(47, 0);

		ग_लिखोl((u32)val, iommu->mmio_base + offset);
		ग_लिखोl((val >> 32), iommu->mmio_base + offset + 4);
	पूर्ण अन्यथा अणु
		*value = पढ़ोl(iommu->mmio_base + offset + 4);
		*value <<= 32;
		*value |= पढ़ोl(iommu->mmio_base + offset);
		*value &= GENMASK_ULL(47, 0);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amd_iommu_pc_get_reg(काष्ठा amd_iommu *iommu, u8 bank, u8 cntr, u8 fxn, u64 *value)
अणु
	अगर (!iommu)
		वापस -EINVAL;

	वापस iommu_pc_get_set_reg(iommu, bank, cntr, fxn, value, false);
पूर्ण

पूर्णांक amd_iommu_pc_set_reg(काष्ठा amd_iommu *iommu, u8 bank, u8 cntr, u8 fxn, u64 *value)
अणु
	अगर (!iommu)
		वापस -EINVAL;

	वापस iommu_pc_get_set_reg(iommu, bank, cntr, fxn, value, true);
पूर्ण
