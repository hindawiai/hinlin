<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_HW_IRQ_H
#घोषणा _ASM_X86_HW_IRQ_H

/*
 * (C) 1992, 1993 Linus Torvalds, (C) 1997 Ingo Molnar
 *
 * moved some of the old arch/i386/kernel/irq.h to here. VY
 *
 * IRQ/IPI changes taken from work by Thomas Radke
 * <tomsoft@inक्रमmatik.tu-chemnitz.de>
 *
 * hacked by Andi Kleen क्रम x86-64.
 * unअगरied by tglx
 */

#समावेश <यंत्र/irq_vectors.h>

#घोषणा IRQ_MATRIX_BITS		NR_VECTORS

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/percpu.h>
#समावेश <linux/profile.h>
#समावेश <linux/smp.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sections.h>

#अगर_घोषित	CONFIG_X86_LOCAL_APIC
काष्ठा irq_data;
काष्ठा pci_dev;
काष्ठा msi_desc;

क्रमागत irq_alloc_type अणु
	X86_IRQ_ALLOC_TYPE_IOAPIC = 1,
	X86_IRQ_ALLOC_TYPE_HPET,
	X86_IRQ_ALLOC_TYPE_PCI_MSI,
	X86_IRQ_ALLOC_TYPE_PCI_MSIX,
	X86_IRQ_ALLOC_TYPE_DMAR,
	X86_IRQ_ALLOC_TYPE_AMDVI,
	X86_IRQ_ALLOC_TYPE_UV,
पूर्ण;

काष्ठा ioapic_alloc_info अणु
	पूर्णांक		pin;
	पूर्णांक		node;
	u32		is_level	: 1;
	u32		active_low	: 1;
	u32		valid		: 1;
पूर्ण;

काष्ठा uv_alloc_info अणु
	पूर्णांक		limit;
	पूर्णांक		blade;
	अचिन्हित दीर्घ	offset;
	अक्षर		*name;

पूर्ण;

/**
 * irq_alloc_info - X86 specअगरic पूर्णांकerrupt allocation info
 * @type:	X86 specअगरic allocation type
 * @flags:	Flags क्रम allocation tweaks
 * @devid:	Device ID क्रम allocations
 * @hwirq:	Associated hw पूर्णांकerrupt number in the करोमुख्य
 * @mask:	CPU mask क्रम vector allocation
 * @desc:	Poपूर्णांकer to msi descriptor
 * @data:	Allocation specअगरic data
 *
 * @ioapic:	IOAPIC specअगरic allocation data
 * @uv:		UV specअगरic allocation data
*/
काष्ठा irq_alloc_info अणु
	क्रमागत irq_alloc_type	type;
	u32			flags;
	u32			devid;
	irq_hw_number_t		hwirq;
	स्थिर काष्ठा cpumask	*mask;
	काष्ठा msi_desc		*desc;
	व्योम			*data;

	जोड़ अणु
		काष्ठा ioapic_alloc_info	ioapic;
		काष्ठा uv_alloc_info		uv;
	पूर्ण;
पूर्ण;

काष्ठा irq_cfg अणु
	अचिन्हित पूर्णांक		dest_apicid;
	अचिन्हित पूर्णांक		vector;
पूर्ण;

बाह्य काष्ठा irq_cfg *irq_cfg(अचिन्हित पूर्णांक irq);
बाह्य काष्ठा irq_cfg *irqd_cfg(काष्ठा irq_data *irq_data);
बाह्य व्योम lock_vector_lock(व्योम);
बाह्य व्योम unlock_vector_lock(व्योम);
#अगर_घोषित CONFIG_SMP
बाह्य व्योम send_cleanup_vector(काष्ठा irq_cfg *);
बाह्य व्योम irq_complete_move(काष्ठा irq_cfg *cfg);
#अन्यथा
अटल अंतरभूत व्योम send_cleanup_vector(काष्ठा irq_cfg *c) अणु पूर्ण
अटल अंतरभूत व्योम irq_complete_move(काष्ठा irq_cfg *c) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम apic_ack_edge(काष्ठा irq_data *data);
#अन्यथा	/*  CONFIG_X86_LOCAL_APIC */
अटल अंतरभूत व्योम lock_vector_lock(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम unlock_vector_lock(व्योम) अणुपूर्ण
#पूर्ण_अगर	/* CONFIG_X86_LOCAL_APIC */

/* Statistics */
बाह्य atomic_t irq_err_count;
बाह्य atomic_t irq_mis_count;

बाह्य व्योम elcr_set_level_irq(अचिन्हित पूर्णांक irq);

बाह्य अक्षर irq_entries_start[];
#अगर_घोषित CONFIG_TRACING
#घोषणा trace_irq_entries_start irq_entries_start
#पूर्ण_अगर

बाह्य अक्षर spurious_entries_start[];

#घोषणा VECTOR_UNUSED		शून्य
#घोषणा VECTOR_SHUTDOWN		((व्योम *)-1L)
#घोषणा VECTOR_RETRIGGERED	((व्योम *)-2L)

प्रकार काष्ठा irq_desc* vector_irq_t[NR_VECTORS];
DECLARE_PER_CPU(vector_irq_t, vector_irq);

#पूर्ण_अगर /* !ASSEMBLY_ */

#पूर्ण_अगर /* _ASM_X86_HW_IRQ_H */
