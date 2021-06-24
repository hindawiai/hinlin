<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_AMD_NB_H
#घोषणा _ASM_X86_AMD_NB_H

#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/refcount.h>

काष्ठा amd_nb_bus_dev_range अणु
	u8 bus;
	u8 dev_base;
	u8 dev_limit;
पूर्ण;

बाह्य स्थिर काष्ठा amd_nb_bus_dev_range amd_nb_bus_dev_ranges[];

बाह्य bool early_is_amd_nb(u32 value);
बाह्य काष्ठा resource *amd_get_mmconfig_range(काष्ठा resource *res);
बाह्य पूर्णांक amd_cache_northbridges(व्योम);
बाह्य व्योम amd_flush_garts(व्योम);
बाह्य पूर्णांक amd_numa_init(व्योम);
बाह्य पूर्णांक amd_get_subcaches(पूर्णांक);
बाह्य पूर्णांक amd_set_subcaches(पूर्णांक, अचिन्हित दीर्घ);

बाह्य पूर्णांक amd_smn_पढ़ो(u16 node, u32 address, u32 *value);
बाह्य पूर्णांक amd_smn_ग_लिखो(u16 node, u32 address, u32 value);
बाह्य पूर्णांक amd_df_indirect_पढ़ो(u16 node, u8 func, u16 reg, u8 instance_id, u32 *lo);

काष्ठा amd_l3_cache अणु
	अचिन्हित indices;
	u8	 subcaches[4];
पूर्ण;

काष्ठा threshold_block अणु
	अचिन्हित पूर्णांक	 block;			/* Number within bank */
	अचिन्हित पूर्णांक	 bank;			/* MCA bank the block beदीर्घs to */
	अचिन्हित पूर्णांक	 cpu;			/* CPU which controls MCA bank */
	u32		 address;		/* MSR address क्रम the block */
	u16		 पूर्णांकerrupt_enable;	/* Enable/Disable APIC पूर्णांकerrupt */
	bool		 पूर्णांकerrupt_capable;	/* Bank can generate an पूर्णांकerrupt. */

	u16		 threshold_limit;	/*
						 * Value upon which threshold
						 * पूर्णांकerrupt is generated.
						 */

	काष्ठा kobject	 kobj;			/* sysfs object */
	काष्ठा list_head miscj;			/*
						 * List of threshold blocks
						 * within a bank.
						 */
पूर्ण;

काष्ठा threshold_bank अणु
	काष्ठा kobject		*kobj;
	काष्ठा threshold_block	*blocks;

	/* initialized to the number of CPUs on the node sharing this bank */
	refcount_t		cpus;
	अचिन्हित पूर्णांक		shared;
पूर्ण;

काष्ठा amd_northbridge अणु
	काष्ठा pci_dev *root;
	काष्ठा pci_dev *misc;
	काष्ठा pci_dev *link;
	काष्ठा amd_l3_cache l3_cache;
	काष्ठा threshold_bank *bank4;
पूर्ण;

काष्ठा amd_northbridge_info अणु
	u16 num;
	u64 flags;
	काष्ठा amd_northbridge *nb;
पूर्ण;

#घोषणा AMD_NB_GART			BIT(0)
#घोषणा AMD_NB_L3_INDEX_DISABLE		BIT(1)
#घोषणा AMD_NB_L3_PARTITIONING		BIT(2)

#अगर_घोषित CONFIG_AMD_NB

u16 amd_nb_num(व्योम);
bool amd_nb_has_feature(अचिन्हित पूर्णांक feature);
काष्ठा amd_northbridge *node_to_amd_nb(पूर्णांक node);

अटल अंतरभूत u16 amd_pci_dev_to_node_id(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *misc;
	पूर्णांक i;

	क्रम (i = 0; i != amd_nb_num(); i++) अणु
		misc = node_to_amd_nb(i)->misc;

		अगर (pci_करोमुख्य_nr(misc->bus) == pci_करोमुख्य_nr(pdev->bus) &&
		    PCI_SLOT(misc->devfn) == PCI_SLOT(pdev->devfn))
			वापस i;
	पूर्ण

	WARN(1, "Unable to find AMD Northbridge id for %s\n", pci_name(pdev));
	वापस 0;
पूर्ण

अटल अंतरभूत bool amd_gart_present(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD)
		वापस false;

	/* GART present only on Fam15h, upto model 0fh */
	अगर (boot_cpu_data.x86 == 0xf || boot_cpu_data.x86 == 0x10 ||
	    (boot_cpu_data.x86 == 0x15 && boot_cpu_data.x86_model < 0x10))
		वापस true;

	वापस false;
पूर्ण

#अन्यथा

#घोषणा amd_nb_num(x)		0
#घोषणा amd_nb_has_feature(x)	false
#घोषणा node_to_amd_nb(x)	शून्य
#घोषणा amd_gart_present(x)	false

#पूर्ण_अगर


#पूर्ण_अगर /* _ASM_X86_AMD_NB_H */
