<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IRQDOMAIN_H
#घोषणा _ASM_IRQDOMAIN_H

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <यंत्र/hw_irq.h>

#अगर_घोषित CONFIG_X86_LOCAL_APIC
क्रमागत अणु
	/* Allocate contiguous CPU vectors */
	X86_IRQ_ALLOC_CONTIGUOUS_VECTORS		= 0x1,
	X86_IRQ_ALLOC_LEGACY				= 0x2,
पूर्ण;

बाह्य पूर्णांक x86_fwspec_is_ioapic(काष्ठा irq_fwspec *fwspec);
बाह्य पूर्णांक x86_fwspec_is_hpet(काष्ठा irq_fwspec *fwspec);

बाह्य काष्ठा irq_करोमुख्य *x86_vector_करोमुख्य;

बाह्य व्योम init_irq_alloc_info(काष्ठा irq_alloc_info *info,
				स्थिर काष्ठा cpumask *mask);
बाह्य व्योम copy_irq_alloc_info(काष्ठा irq_alloc_info *dst,
				काष्ठा irq_alloc_info *src);
#पूर्ण_अगर /* CONFIG_X86_LOCAL_APIC */

#अगर_घोषित CONFIG_X86_IO_APIC
काष्ठा device_node;
काष्ठा irq_data;

क्रमागत ioapic_करोमुख्य_type अणु
	IOAPIC_DOMAIN_INVALID,
	IOAPIC_DOMAIN_LEGACY,
	IOAPIC_DOMAIN_STRICT,
	IOAPIC_DOMAIN_DYNAMIC,
पूर्ण;

काष्ठा ioapic_करोमुख्य_cfg अणु
	क्रमागत ioapic_करोमुख्य_type		type;
	स्थिर काष्ठा irq_करोमुख्य_ops	*ops;
	काष्ठा device_node		*dev;
पूर्ण;

बाह्य स्थिर काष्ठा irq_करोमुख्य_ops mp_ioapic_irqकरोमुख्य_ops;

बाह्य पूर्णांक mp_irqकरोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs, व्योम *arg);
बाह्य व्योम mp_irqकरोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs);
बाह्य पूर्णांक mp_irqकरोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				 काष्ठा irq_data *irq_data, bool reserve);
बाह्य व्योम mp_irqकरोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
				    काष्ठा irq_data *irq_data);
बाह्य पूर्णांक mp_irqकरोमुख्य_ioapic_idx(काष्ठा irq_करोमुख्य *करोमुख्य);
#पूर्ण_अगर /* CONFIG_X86_IO_APIC */

#अगर_घोषित CONFIG_PCI_MSI
व्योम x86_create_pci_msi_करोमुख्य(व्योम);
काष्ठा irq_करोमुख्य *native_create_pci_msi_करोमुख्य(व्योम);
बाह्य काष्ठा irq_करोमुख्य *x86_pci_msi_शेष_करोमुख्य;
#अन्यथा
अटल अंतरभूत व्योम x86_create_pci_msi_करोमुख्य(व्योम) अणु पूर्ण
#घोषणा native_create_pci_msi_करोमुख्य	शून्य
#घोषणा x86_pci_msi_शेष_करोमुख्य	शून्य
#पूर्ण_अगर

#पूर्ण_अगर
