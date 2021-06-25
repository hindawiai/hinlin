<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Low-Level PCI Access क्रम i386 machines.
 *
 *	(c) 1999 Martin Mares <mj@ucw.cz>
 */

#समावेश <linux/ioport.h>

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt, ...) prपूर्णांकk(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा DBG(fmt, ...)				\
करो अणु						\
	अगर (0)					\
		prपूर्णांकk(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा PCI_PROBE_BIOS		0x0001
#घोषणा PCI_PROBE_CONF1		0x0002
#घोषणा PCI_PROBE_CONF2		0x0004
#घोषणा PCI_PROBE_MMCONF	0x0008
#घोषणा PCI_PROBE_MASK		0x000f
#घोषणा PCI_PROBE_NOEARLY	0x0010

#घोषणा PCI_NO_CHECKS		0x0400
#घोषणा PCI_USE_PIRQ_MASK	0x0800
#घोषणा PCI_ASSIGN_ROMS		0x1000
#घोषणा PCI_BIOS_IRQ_SCAN	0x2000
#घोषणा PCI_ASSIGN_ALL_BUSSES	0x4000
#घोषणा PCI_CAN_SKIP_ISA_ALIGN	0x8000
#घोषणा PCI_USE__CRS		0x10000
#घोषणा PCI_CHECK_ENABLE_AMD_MMCONF	0x20000
#घोषणा PCI_HAS_IO_ECS		0x40000
#घोषणा PCI_NOASSIGN_ROMS	0x80000
#घोषणा PCI_ROOT_NO_CRS		0x100000
#घोषणा PCI_NOASSIGN_BARS	0x200000
#घोषणा PCI_BIG_ROOT_WINDOW	0x400000

बाह्य अचिन्हित पूर्णांक pci_probe;
बाह्य अचिन्हित दीर्घ pirq_table_addr;

क्रमागत pci_bf_sort_state अणु
	pci_bf_sort_शेष,
	pci_क्रमce_nobf,
	pci_क्रमce_bf,
	pci_dmi_bf,
पूर्ण;

/* pci-i386.c */

व्योम pcibios_resource_survey(व्योम);
व्योम pcibios_set_cache_line_size(व्योम);

/* pci-pc.c */

बाह्य पूर्णांक pcibios_last_bus;
बाह्य काष्ठा pci_ops pci_root_ops;

व्योम pcibios_scan_specअगरic_bus(पूर्णांक busn);

/* pci-irq.c */

काष्ठा irq_info अणु
	u8 bus, devfn;			/* Bus, device and function */
	काष्ठा अणु
		u8 link;		/* IRQ line ID, chipset dependent,
					   0 = not routed */
		u16 biपंचांगap;		/* Available IRQs */
	पूर्ण __attribute__((packed)) irq[4];
	u8 slot;			/* Slot number, 0=onboard */
	u8 rfu;
पूर्ण __attribute__((packed));

काष्ठा irq_routing_table अणु
	u32 signature;			/* PIRQ_SIGNATURE should be here */
	u16 version;			/* PIRQ_VERSION */
	u16 size;			/* Table size in bytes */
	u8 rtr_bus, rtr_devfn;		/* Where the पूर्णांकerrupt router lies */
	u16 exclusive_irqs;		/* IRQs devoted exclusively to
					   PCI usage */
	u16 rtr_venकरोr, rtr_device;	/* Venकरोr and device ID of
					   पूर्णांकerrupt router */
	u32 miniport_data;		/* Crap */
	u8 rfu[11];
	u8 checksum;			/* Modulo 256 checksum must give 0 */
	काष्ठा irq_info slots[0];
पूर्ण __attribute__((packed));

बाह्य अचिन्हित पूर्णांक pcibios_irq_mask;

बाह्य raw_spinlock_t pci_config_lock;

बाह्य पूर्णांक (*pcibios_enable_irq)(काष्ठा pci_dev *dev);
बाह्य व्योम (*pcibios_disable_irq)(काष्ठा pci_dev *dev);

बाह्य bool mp_should_keep_irq(काष्ठा device *dev);

काष्ठा pci_raw_ops अणु
	पूर्णांक (*पढ़ो)(अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
						पूर्णांक reg, पूर्णांक len, u32 *val);
	पूर्णांक (*ग_लिखो)(अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
						पूर्णांक reg, पूर्णांक len, u32 val);
पूर्ण;

बाह्य स्थिर काष्ठा pci_raw_ops *raw_pci_ops;
बाह्य स्थिर काष्ठा pci_raw_ops *raw_pci_ext_ops;

बाह्य स्थिर काष्ठा pci_raw_ops pci_mmcfg;
बाह्य स्थिर काष्ठा pci_raw_ops pci_direct_conf1;
बाह्य bool port_cf9_safe;

/* arch_initcall level */
#अगर_घोषित CONFIG_PCI_सूचीECT
बाह्य पूर्णांक pci_direct_probe(व्योम);
बाह्य व्योम pci_direct_init(पूर्णांक type);
#अन्यथा
अटल अंतरभूत पूर्णांक pci_direct_probe(व्योम) अणु वापस -1; पूर्ण
अटल अंतरभूत  व्योम pci_direct_init(पूर्णांक type) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_BIOS
बाह्य व्योम pci_pcbios_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pci_pcbios_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम __init dmi_check_pciprobe(व्योम);
बाह्य व्योम __init dmi_check_skip_isa_align(व्योम);

/* some common used subsys_initcalls */
#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक __init pci_acpi_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक  __init pci_acpi_init(व्योम)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर
बाह्य व्योम __init pcibios_irq_init(व्योम);
बाह्य पूर्णांक __init pcibios_init(व्योम);
बाह्य पूर्णांक pci_legacy_init(व्योम);
बाह्य व्योम pcibios_fixup_irqs(व्योम);

/* pci-mmconfig.c */

/* "PCI MMCONFIG %04x [bus %02x-%02x]" */
#घोषणा PCI_MMCFG_RESOURCE_NAME_LEN (22 + 4 + 2 + 2)

काष्ठा pci_mmcfg_region अणु
	काष्ठा list_head list;
	काष्ठा resource res;
	u64 address;
	अक्षर __iomem *virt;
	u16 segment;
	u8 start_bus;
	u8 end_bus;
	अक्षर name[PCI_MMCFG_RESOURCE_NAME_LEN];
पूर्ण;

बाह्य पूर्णांक __init pci_mmcfg_arch_init(व्योम);
बाह्य व्योम __init pci_mmcfg_arch_मुक्त(व्योम);
बाह्य पूर्णांक pci_mmcfg_arch_map(काष्ठा pci_mmcfg_region *cfg);
बाह्य व्योम pci_mmcfg_arch_unmap(काष्ठा pci_mmcfg_region *cfg);
बाह्य पूर्णांक pci_mmconfig_insert(काष्ठा device *dev, u16 seg, u8 start, u8 end,
			       phys_addr_t addr);
बाह्य पूर्णांक pci_mmconfig_delete(u16 seg, u8 start, u8 end);
बाह्य काष्ठा pci_mmcfg_region *pci_mmconfig_lookup(पूर्णांक segment, पूर्णांक bus);
बाह्य काष्ठा pci_mmcfg_region *__init pci_mmconfig_add(पूर्णांक segment, पूर्णांक start,
							पूर्णांक end, u64 addr);

बाह्य काष्ठा list_head pci_mmcfg_list;

#घोषणा PCI_MMCFG_BUS_OFFSET(bus)      ((bus) << 20)

/*
 * On AMD Fam10h CPUs, all PCI MMIO configuration space accesses must use
 * %eax.  No other source or target रेजिस्टरs may be used.  The following
 * mmio_config_* accessors enक्रमce this.  See "BIOS and Kernel Developer's
 * Guide (BKDG) For AMD Family 10h Processors", rev. 3.48, sec 2.11.1,
 * "MMIO Configuration Coding Requirements".
 */
अटल अंतरभूत अचिन्हित अक्षर mmio_config_पढ़ोb(व्योम __iomem *pos)
अणु
	u8 val;
	यंत्र अस्थिर("movb (%1),%%al" : "=a" (val) : "r" (pos));
	वापस val;
पूर्ण

अटल अंतरभूत अचिन्हित लघु mmio_config_पढ़ोw(व्योम __iomem *pos)
अणु
	u16 val;
	यंत्र अस्थिर("movw (%1),%%ax" : "=a" (val) : "r" (pos));
	वापस val;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mmio_config_पढ़ोl(व्योम __iomem *pos)
अणु
	u32 val;
	यंत्र अस्थिर("movl (%1),%%eax" : "=a" (val) : "r" (pos));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम mmio_config_ग_लिखोb(व्योम __iomem *pos, u8 val)
अणु
	यंत्र अस्थिर("movb %%al,(%1)" : : "a" (val), "r" (pos) : "memory");
पूर्ण

अटल अंतरभूत व्योम mmio_config_ग_लिखोw(व्योम __iomem *pos, u16 val)
अणु
	यंत्र अस्थिर("movw %%ax,(%1)" : : "a" (val), "r" (pos) : "memory");
पूर्ण

अटल अंतरभूत व्योम mmio_config_ग_लिखोl(व्योम __iomem *pos, u32 val)
अणु
	यंत्र अस्थिर("movl %%eax,(%1)" : : "a" (val), "r" (pos) : "memory");
पूर्ण

#अगर_घोषित CONFIG_PCI
# अगरdef CONFIG_ACPI
#  define x86_शेष_pci_init		pci_acpi_init
# अन्यथा
#  define x86_शेष_pci_init		pci_legacy_init
# endअगर
# define x86_शेष_pci_init_irq	pcibios_irq_init
# define x86_शेष_pci_fixup_irqs	pcibios_fixup_irqs
#अन्यथा
# define x86_शेष_pci_init		शून्य
# define x86_शेष_pci_init_irq	शून्य
# define x86_शेष_pci_fixup_irqs	शून्य
#पूर्ण_अगर
