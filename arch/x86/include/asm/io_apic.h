<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IO_APIC_H
#घोषणा _ASM_X86_IO_APIC_H

#समावेश <linux/types.h>
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/apicdef.h>
#समावेश <यंत्र/irq_vectors.h>
#समावेश <यंत्र/x86_init.h>
/*
 * Intel IO-APIC support क्रम SMP and UP प्रणालीs.
 *
 * Copyright (C) 1997, 1998, 1999, 2000 Ingo Molnar
 */

/*
 * The काष्ठाure of the IO-APIC:
 */
जोड़ IO_APIC_reg_00 अणु
	u32	raw;
	काष्ठा अणु
		u32	__reserved_2	: 14,
			LTS		:  1,
			delivery_type	:  1,
			__reserved_1	:  8,
			ID		:  8;
	पूर्ण __attribute__ ((packed)) bits;
पूर्ण;

जोड़ IO_APIC_reg_01 अणु
	u32	raw;
	काष्ठा अणु
		u32	version		:  8,
			__reserved_2	:  7,
			PRQ		:  1,
			entries		:  8,
			__reserved_1	:  8;
	पूर्ण __attribute__ ((packed)) bits;
पूर्ण;

जोड़ IO_APIC_reg_02 अणु
	u32	raw;
	काष्ठा अणु
		u32	__reserved_2	: 24,
			arbitration	:  4,
			__reserved_1	:  4;
	पूर्ण __attribute__ ((packed)) bits;
पूर्ण;

जोड़ IO_APIC_reg_03 अणु
	u32	raw;
	काष्ठा अणु
		u32	boot_DT		:  1,
			__reserved_1	: 31;
	पूर्ण __attribute__ ((packed)) bits;
पूर्ण;

काष्ठा IO_APIC_route_entry अणु
	जोड़ अणु
		काष्ठा अणु
			u64	vector			:  8,
				delivery_mode		:  3,
				dest_mode_logical	:  1,
				delivery_status		:  1,
				active_low		:  1,
				irr			:  1,
				is_level		:  1,
				masked			:  1,
				reserved_0		: 15,
				reserved_1		: 17,
				virt_destid_8_14	:  7,
				destid_0_7		:  8;
		पूर्ण;
		काष्ठा अणु
			u64	ir_shared_0		:  8,
				ir_zero			:  3,
				ir_index_15		:  1,
				ir_shared_1		:  5,
				ir_reserved_0		: 31,
				ir_क्रमmat		:  1,
				ir_index_0_14		: 15;
		पूर्ण;
		काष्ठा अणु
			u64	w1			: 32,
				w2			: 32;
		पूर्ण;
	पूर्ण;
पूर्ण __attribute__ ((packed));

काष्ठा irq_alloc_info;
काष्ठा ioapic_करोमुख्य_cfg;

#घोषणा	IOAPIC_MAP_ALLOC		0x1
#घोषणा	IOAPIC_MAP_CHECK		0x2

#अगर_घोषित CONFIG_X86_IO_APIC

/*
 * # of IO-APICs and # of IRQ routing रेजिस्टरs
 */
बाह्य पूर्णांक nr_ioapics;

बाह्य पूर्णांक mpc_ioapic_id(पूर्णांक ioapic);
बाह्य अचिन्हित पूर्णांक mpc_ioapic_addr(पूर्णांक ioapic);

/* # of MP IRQ source entries */
बाह्य पूर्णांक mp_irq_entries;

/* MP IRQ source entries */
बाह्य काष्ठा mpc_पूर्णांकsrc mp_irqs[MAX_IRQ_SOURCES];

/* 1 अगर "noapic" boot option passed */
बाह्य पूर्णांक skip_ioapic_setup;

/* 1 अगर "noapic" boot option passed */
बाह्य पूर्णांक noioapicquirk;

/* -1 अगर "noapic" boot option passed */
बाह्य पूर्णांक noioapicreroute;

बाह्य u32 gsi_top;

बाह्य अचिन्हित दीर्घ io_apic_irqs;

#घोषणा IO_APIC_IRQ(x) (((x) >= NR_IRQS_LEGACY) || ((1 << (x)) & io_apic_irqs))

/*
 * If we use the IO-APIC क्रम IRQ routing, disable स्वतःmatic
 * assignment of PCI IRQ's.
 */
#घोषणा io_apic_assign_pci_irqs \
	(mp_irq_entries && !skip_ioapic_setup && io_apic_irqs)

काष्ठा irq_cfg;
बाह्य व्योम ioapic_insert_resources(व्योम);
बाह्य पूर्णांक arch_early_ioapic_init(व्योम);

बाह्य पूर्णांक save_ioapic_entries(व्योम);
बाह्य व्योम mask_ioapic_entries(व्योम);
बाह्य पूर्णांक restore_ioapic_entries(व्योम);

बाह्य व्योम setup_ioapic_ids_from_mpc(व्योम);
बाह्य व्योम setup_ioapic_ids_from_mpc_nocheck(व्योम);

बाह्य पूर्णांक mp_find_ioapic(u32 gsi);
बाह्य पूर्णांक mp_find_ioapic_pin(पूर्णांक ioapic, u32 gsi);
बाह्य पूर्णांक mp_map_gsi_to_irq(u32 gsi, अचिन्हित पूर्णांक flags,
			     काष्ठा irq_alloc_info *info);
बाह्य व्योम mp_unmap_irq(पूर्णांक irq);
बाह्य पूर्णांक mp_रेजिस्टर_ioapic(पूर्णांक id, u32 address, u32 gsi_base,
			      काष्ठा ioapic_करोमुख्य_cfg *cfg);
बाह्य पूर्णांक mp_unरेजिस्टर_ioapic(u32 gsi_base);
बाह्य पूर्णांक mp_ioapic_रेजिस्टरed(u32 gsi_base);

बाह्य व्योम ioapic_set_alloc_attr(काष्ठा irq_alloc_info *info,
				  पूर्णांक node, पूर्णांक trigger, पूर्णांक polarity);

बाह्य व्योम mp_save_irq(काष्ठा mpc_पूर्णांकsrc *m);

बाह्य व्योम disable_ioapic_support(व्योम);

बाह्य व्योम __init io_apic_init_mappings(व्योम);
बाह्य अचिन्हित पूर्णांक native_io_apic_पढ़ो(अचिन्हित पूर्णांक apic, अचिन्हित पूर्णांक reg);
बाह्य व्योम native_restore_boot_irq_mode(व्योम);

अटल अंतरभूत अचिन्हित पूर्णांक io_apic_पढ़ो(अचिन्हित पूर्णांक apic, अचिन्हित पूर्णांक reg)
अणु
	वापस x86_apic_ops.io_apic_पढ़ो(apic, reg);
पूर्ण

बाह्य व्योम setup_IO_APIC(व्योम);
बाह्य व्योम enable_IO_APIC(व्योम);
बाह्य व्योम clear_IO_APIC(व्योम);
बाह्य व्योम restore_boot_irq_mode(व्योम);
बाह्य पूर्णांक IO_APIC_get_PCI_irq_vector(पूर्णांक bus, पूर्णांक devfn, पूर्णांक pin);
बाह्य व्योम prपूर्णांक_IO_APICs(व्योम);
#अन्यथा  /* !CONFIG_X86_IO_APIC */

#घोषणा IO_APIC_IRQ(x)		0
#घोषणा io_apic_assign_pci_irqs 0
#घोषणा setup_ioapic_ids_from_mpc x86_init_noop
अटल अंतरभूत व्योम ioapic_insert_resources(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक arch_early_ioapic_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम prपूर्णांक_IO_APICs(व्योम) अणुपूर्ण
#घोषणा gsi_top (NR_IRQS_LEGACY)
अटल अंतरभूत पूर्णांक mp_find_ioapic(u32 gsi) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक mp_map_gsi_to_irq(u32 gsi, अचिन्हित पूर्णांक flags,
				    काष्ठा irq_alloc_info *info)
अणु
	वापस gsi;
पूर्ण

अटल अंतरभूत व्योम mp_unmap_irq(पूर्णांक irq) अणु पूर्ण

अटल अंतरभूत पूर्णांक save_ioapic_entries(व्योम)
अणु
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम mask_ioapic_entries(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक restore_ioapic_entries(व्योम)
अणु
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम mp_save_irq(काष्ठा mpc_पूर्णांकsrc *m) अणु पूर्ण
अटल अंतरभूत व्योम disable_ioapic_support(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम io_apic_init_mappings(व्योम) अणु पूर्ण
#घोषणा native_io_apic_पढ़ो		शून्य
#घोषणा native_restore_boot_irq_mode	शून्य

अटल अंतरभूत व्योम setup_IO_APIC(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम enable_IO_APIC(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम restore_boot_irq_mode(व्योम) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_IO_APIC_H */
