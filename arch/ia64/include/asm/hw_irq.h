<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_HW_IRQ_H
#घोषणा _ASM_IA64_HW_IRQ_H

/*
 * Copyright (C) 2001-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/profile.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp.h>

प्रकार u8 ia64_vector;

/*
 * 0 special
 *
 * 1,3-14 are reserved from firmware
 *
 * 16-255 (vectored बाह्यal पूर्णांकerrupts) are available
 *
 * 15 spurious पूर्णांकerrupt (see IVR)
 *
 * 16 lowest priority, 255 highest priority
 *
 * 15 classes of 16 पूर्णांकerrupts each.
 */
#घोषणा IA64_MIN_VECTORED_IRQ		 16
#घोषणा IA64_MAX_VECTORED_IRQ		255
#घोषणा IA64_NUM_VECTORS		256

#घोषणा AUTO_ASSIGN			-1

#घोषणा IA64_SPURIOUS_INT_VECTOR	0x0f

/*
 * Vectors 0x10-0x1f are used क्रम low priority पूर्णांकerrupts, e.g. CMCI.
 */
#घोषणा IA64_CPEP_VECTOR		0x1c	/* corrected platक्रमm error polling vector */
#घोषणा IA64_CMCP_VECTOR		0x1d	/* corrected machine-check polling vector */
#घोषणा IA64_CPE_VECTOR			0x1e	/* corrected platक्रमm error पूर्णांकerrupt vector */
#घोषणा IA64_CMC_VECTOR			0x1f	/* corrected machine-check पूर्णांकerrupt vector */
/*
 * Vectors 0x20-0x2f are reserved क्रम legacy ISA IRQs.
 * Use vectors 0x30-0xe7 as the शेष device vector range क्रम ia64.
 * Platक्रमms may choose to reduce this range in platक्रमm_irq_setup, but the
 * platक्रमm range must fall within
 *	[IA64_DEF_FIRST_DEVICE_VECTOR..IA64_DEF_LAST_DEVICE_VECTOR]
 */
बाह्य पूर्णांक ia64_first_device_vector;
बाह्य पूर्णांक ia64_last_device_vector;

#अगर_घोषित CONFIG_SMP
/* Reserve the lower priority vector than device vectors क्रम "move IRQ" IPI */
#घोषणा IA64_IRQ_MOVE_VECTOR		0x30	/* "move IRQ" IPI */
#घोषणा IA64_DEF_FIRST_DEVICE_VECTOR	0x31
#अन्यथा
#घोषणा IA64_DEF_FIRST_DEVICE_VECTOR	0x30
#पूर्ण_अगर
#घोषणा IA64_DEF_LAST_DEVICE_VECTOR	0xe7
#घोषणा IA64_FIRST_DEVICE_VECTOR	ia64_first_device_vector
#घोषणा IA64_LAST_DEVICE_VECTOR		ia64_last_device_vector
#घोषणा IA64_MAX_DEVICE_VECTORS		(IA64_DEF_LAST_DEVICE_VECTOR - IA64_DEF_FIRST_DEVICE_VECTOR + 1)
#घोषणा IA64_NUM_DEVICE_VECTORS		(IA64_LAST_DEVICE_VECTOR - IA64_FIRST_DEVICE_VECTOR + 1)

#घोषणा IA64_MCA_RENDEZ_VECTOR		0xe8	/* MCA rendez पूर्णांकerrupt */
#घोषणा IA64_TIMER_VECTOR		0xef	/* use highest-prio group 15 पूर्णांकerrupt क्रम समयr */
#घोषणा	IA64_MCA_WAKEUP_VECTOR		0xf0	/* MCA wakeup (must be >MCA_RENDEZ_VECTOR) */
#घोषणा IA64_IPI_LOCAL_TLB_FLUSH	0xfc	/* SMP flush local TLB */
#घोषणा IA64_IPI_RESCHEDULE		0xfd	/* SMP reschedule */
#घोषणा IA64_IPI_VECTOR			0xfe	/* पूर्णांकer-processor पूर्णांकerrupt vector */

/* Used क्रम encoding redirected irqs */

#घोषणा IA64_IRQ_REसूचीECTED		(1 << 31)

/* IA64 पूर्णांकer-cpu पूर्णांकerrupt related definitions */

#घोषणा IA64_IPI_DEFAULT_BASE_ADDR	0xfee00000

/* Delivery modes क्रम पूर्णांकer-cpu पूर्णांकerrupts */
क्रमागत अणु
        IA64_IPI_DM_INT =       0x0,    /* pend an बाह्यal पूर्णांकerrupt */
        IA64_IPI_DM_PMI =       0x2,    /* pend a PMI */
        IA64_IPI_DM_NMI =       0x4,    /* pend an NMI (vector 2) */
        IA64_IPI_DM_INIT =      0x5,    /* pend an INIT पूर्णांकerrupt */
        IA64_IPI_DM_EXTINT =    0x7,    /* pend an 8259-compatible पूर्णांकerrupt. */
पूर्ण;

बाह्य __u8 isa_irq_to_vector_map[16];
#घोषणा isa_irq_to_vector(x)	isa_irq_to_vector_map[(x)]

काष्ठा irq_cfg अणु
	ia64_vector vector;
	cpumask_t करोमुख्य;
	cpumask_t old_करोमुख्य;
	अचिन्हित move_cleanup_count;
	u8 move_in_progress : 1;
पूर्ण;
बाह्य spinlock_t vector_lock;
बाह्य काष्ठा irq_cfg irq_cfg[NR_IRQS];
#घोषणा irq_to_करोमुख्य(x)	irq_cfg[(x)].करोमुख्य
DECLARE_PER_CPU(पूर्णांक[IA64_NUM_VECTORS], vector_irq);

बाह्य काष्ठा irq_chip irq_type_ia64_lsapic;	/* CPU-पूर्णांकernal पूर्णांकerrupt controller */

#घोषणा ia64_रेजिस्टर_ipi	ia64_native_रेजिस्टर_ipi
#घोषणा assign_irq_vector	ia64_native_assign_irq_vector
#घोषणा मुक्त_irq_vector		ia64_native_मुक्त_irq_vector
#घोषणा ia64_resend_irq		ia64_native_resend_irq

बाह्य व्योम ia64_native_रेजिस्टर_ipi(व्योम);
बाह्य पूर्णांक bind_irq_vector(पूर्णांक irq, पूर्णांक vector, cpumask_t करोमुख्य);
बाह्य पूर्णांक ia64_native_assign_irq_vector (पूर्णांक irq);	/* allocate a मुक्त vector */
बाह्य व्योम ia64_native_मुक्त_irq_vector (पूर्णांक vector);
बाह्य पूर्णांक reserve_irq_vector (पूर्णांक vector);
बाह्य व्योम __setup_vector_irq(पूर्णांक cpu);
बाह्य व्योम ia64_send_ipi (पूर्णांक cpu, पूर्णांक vector, पूर्णांक delivery_mode, पूर्णांक redirect);
बाह्य व्योम destroy_and_reserve_irq (अचिन्हित पूर्णांक irq);

#अगर_घोषित CONFIG_SMP
बाह्य पूर्णांक irq_prepare_move(पूर्णांक irq, पूर्णांक cpu);
बाह्य व्योम irq_complete_move(अचिन्हित पूर्णांक irq);
#अन्यथा
अटल अंतरभूत पूर्णांक irq_prepare_move(पूर्णांक irq, पूर्णांक cpu) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम irq_complete_move(अचिन्हित पूर्णांक irq) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ia64_native_resend_irq(अचिन्हित पूर्णांक vector)
अणु
	ia64_send_ipi(smp_processor_id(), vector, IA64_IPI_DM_INT, 0);
पूर्ण

/*
 * Next follows the irq descriptor पूर्णांकerface.  On IA-64, each CPU supports 256 पूर्णांकerrupt
 * vectors.  On smaller प्रणालीs, there is a one-to-one correspondence between पूर्णांकerrupt
 * vectors and the Linux irq numbers.  However, larger प्रणालीs may have multiple पूर्णांकerrupt
 * करोमुख्यs meaning that the translation from vector number to irq number depends on the
 * पूर्णांकerrupt करोमुख्य that a CPU beदीर्घs to.  This API असलtracts such platक्रमm-dependent
 * dअगरferences and provides a unअगरorm means to translate between vector and irq numbers
 * and to obtain the irq descriptor क्रम a given irq number.
 */

/* Extract the IA-64 vector that corresponds to IRQ.  */
अटल अंतरभूत ia64_vector
irq_to_vector (पूर्णांक irq)
अणु
	वापस irq_cfg[irq].vector;
पूर्ण

/*
 * Convert the local IA-64 vector to the corresponding irq number.  This translation is
 * करोne in the context of the पूर्णांकerrupt करोमुख्य that the currently executing CPU beदीर्घs
 * to.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
local_vector_to_irq (ia64_vector vec)
अणु
	वापस __this_cpu_पढ़ो(vector_irq[vec]);
पूर्ण

#पूर्ण_अगर /* _ASM_IA64_HW_IRQ_H */
