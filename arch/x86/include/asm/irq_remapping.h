<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <joerg.roedel@amd.com>
 *
 * This header file contains the पूर्णांकerface of the पूर्णांकerrupt remapping code to
 * the x86 पूर्णांकerrupt management code.
 */

#अगर_अघोषित __X86_IRQ_REMAPPING_H
#घोषणा __X86_IRQ_REMAPPING_H

#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/io_apic.h>

काष्ठा msi_msg;
काष्ठा irq_alloc_info;

क्रमागत irq_remap_cap अणु
	IRQ_POSTING_CAP = 0,
पूर्ण;

क्रमागत अणु
	IRQ_REMAP_XAPIC_MODE,
	IRQ_REMAP_X2APIC_MODE,
पूर्ण;

काष्ठा vcpu_data अणु
	u64 pi_desc_addr;	/* Physical address of PI Descriptor */
	u32 vector;		/* Guest vector of the पूर्णांकerrupt */
पूर्ण;

#अगर_घोषित CONFIG_IRQ_REMAP

बाह्य raw_spinlock_t irq_2_ir_lock;

बाह्य bool irq_remapping_cap(क्रमागत irq_remap_cap cap);
बाह्य व्योम set_irq_remapping_broken(व्योम);
बाह्य पूर्णांक irq_remapping_prepare(व्योम);
बाह्य पूर्णांक irq_remapping_enable(व्योम);
बाह्य व्योम irq_remapping_disable(व्योम);
बाह्य पूर्णांक irq_remapping_reenable(पूर्णांक);
बाह्य पूर्णांक irq_remap_enable_fault_handling(व्योम);
बाह्य व्योम panic_अगर_irq_remap(स्थिर अक्षर *msg);

/* Create PCI MSI/MSIx irqकरोमुख्य, use @parent as the parent irqकरोमुख्य. */
बाह्य काष्ठा irq_करोमुख्य *
arch_create_remap_msi_irq_करोमुख्य(काष्ठा irq_करोमुख्य *par, स्थिर अक्षर *n, पूर्णांक id);

/* Get parent irqकरोमुख्य क्रम पूर्णांकerrupt remapping irqकरोमुख्य */
अटल अंतरभूत काष्ठा irq_करोमुख्य *arch_get_ir_parent_करोमुख्य(व्योम)
अणु
	वापस x86_vector_करोमुख्य;
पूर्ण

#अन्यथा  /* CONFIG_IRQ_REMAP */

अटल अंतरभूत bool irq_remapping_cap(क्रमागत irq_remap_cap cap) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम set_irq_remapping_broken(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक irq_remapping_prepare(व्योम) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक irq_remapping_enable(व्योम) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम irq_remapping_disable(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक irq_remapping_reenable(पूर्णांक eim) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक irq_remap_enable_fault_handling(व्योम) अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत व्योम panic_अगर_irq_remap(स्थिर अक्षर *msg)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_IRQ_REMAP */
#पूर्ण_अगर /* __X86_IRQ_REMAPPING_H */
