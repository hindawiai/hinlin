<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IRQ_VECTORS_H
#घोषणा _ASM_X86_IRQ_VECTORS_H

#समावेश <linux/thपढ़ोs.h>
/*
 * Linux IRQ vector layout.
 *
 * There are 256 IDT entries (per CPU - each entry is 8 bytes) which can
 * be defined by Linux. They are used as a jump table by the CPU when a
 * given vector is triggered - by a CPU-बाह्यal, CPU-पूर्णांकernal or
 * software-triggered event.
 *
 * Linux sets the kernel code address each entry jumps to early during
 * bootup, and never changes them. This is the general layout of the
 * IDT entries:
 *
 *  Vectors   0 ...  31 : प्रणाली traps and exceptions - hardcoded events
 *  Vectors  32 ... 127 : device पूर्णांकerrupts
 *  Vector  128         : legacy पूर्णांक80 syscall पूर्णांकerface
 *  Vectors 129 ... LOCAL_TIMER_VECTOR-1
 *  Vectors LOCAL_TIMER_VECTOR ... 255 : special पूर्णांकerrupts
 *
 * 64-bit x86 has per CPU IDT tables, 32-bit has one shared IDT table.
 *
 * This file क्रमागतerates the exact layout of them:
 */

#घोषणा NMI_VECTOR			0x02
#घोषणा MCE_VECTOR			0x12

/*
 * IDT vectors usable क्रम बाह्यal पूर्णांकerrupt sources start at 0x20.
 * (0x80 is the syscall vector, 0x30-0x3f are क्रम ISA)
 */
#घोषणा FIRST_EXTERNAL_VECTOR		0x20

/*
 * Reserve the lowest usable vector (and hence lowest priority)  0x20 क्रम
 * triggering cleanup after irq migration. 0x21-0x2f will still be used
 * क्रम device पूर्णांकerrupts.
 */
#घोषणा IRQ_MOVE_CLEANUP_VECTOR		FIRST_EXTERNAL_VECTOR

#घोषणा IA32_SYSCALL_VECTOR		0x80

/*
 * Vectors 0x30-0x3f are used क्रम ISA पूर्णांकerrupts.
 *   round up to the next 16-vector boundary
 */
#घोषणा ISA_IRQ_VECTOR(irq)		(((FIRST_EXTERNAL_VECTOR + 16) & ~15) + irq)

/*
 * Special IRQ vectors used by the SMP architecture, 0xf0-0xff
 *
 *  some of the following vectors are 'rare', they are merged
 *  पूर्णांकo a single vector (CALL_FUNCTION_VECTOR) to save vector space.
 *  TLB, reschedule and local APIC vectors are perक्रमmance-critical.
 */

#घोषणा SPURIOUS_APIC_VECTOR		0xff
/*
 * Sanity check
 */
#अगर ((SPURIOUS_APIC_VECTOR & 0x0F) != 0x0F)
# error SPURIOUS_APIC_VECTOR definition error
#पूर्ण_अगर

#घोषणा ERROR_APIC_VECTOR		0xfe
#घोषणा RESCHEDULE_VECTOR		0xfd
#घोषणा CALL_FUNCTION_VECTOR		0xfc
#घोषणा CALL_FUNCTION_SINGLE_VECTOR	0xfb
#घोषणा THERMAL_APIC_VECTOR		0xfa
#घोषणा THRESHOLD_APIC_VECTOR		0xf9
#घोषणा REBOOT_VECTOR			0xf8

/*
 * Generic प्रणाली vector क्रम platक्रमm specअगरic use
 */
#घोषणा X86_PLATFORM_IPI_VECTOR		0xf7

/*
 * IRQ work vector:
 */
#घोषणा IRQ_WORK_VECTOR			0xf6

#घोषणा UV_BAU_MESSAGE			0xf5
#घोषणा DEFERRED_ERROR_VECTOR		0xf4

/* Vector on which hypervisor callbacks will be delivered */
#घोषणा HYPERVISOR_CALLBACK_VECTOR	0xf3

/* Vector क्रम KVM to deliver posted पूर्णांकerrupt IPI */
#अगर_घोषित CONFIG_HAVE_KVM
#घोषणा POSTED_INTR_VECTOR		0xf2
#घोषणा POSTED_INTR_WAKEUP_VECTOR	0xf1
#घोषणा POSTED_INTR_NESTED_VECTOR	0xf0
#पूर्ण_अगर

#घोषणा MANAGED_IRQ_SHUTDOWN_VECTOR	0xef

#अगर IS_ENABLED(CONFIG_HYPERV)
#घोषणा HYPERV_REENLIGHTENMENT_VECTOR	0xee
#घोषणा HYPERV_STIMER0_VECTOR		0xed
#पूर्ण_अगर

#घोषणा LOCAL_TIMER_VECTOR		0xec

#घोषणा NR_VECTORS			 256

#अगर_घोषित CONFIG_X86_LOCAL_APIC
#घोषणा FIRST_SYSTEM_VECTOR		LOCAL_TIMER_VECTOR
#अन्यथा
#घोषणा FIRST_SYSTEM_VECTOR		NR_VECTORS
#पूर्ण_अगर

/*
 * Size the maximum number of पूर्णांकerrupts.
 *
 * If the irq_desc[] array has a sparse layout, we can size things
 * generously - it scales up linearly with the maximum number of CPUs,
 * and the maximum number of IO-APICs, whichever is higher.
 *
 * In other हालs we size more conservatively, to not create too large
 * अटल arrays.
 */

#घोषणा NR_IRQS_LEGACY			16

#घोषणा CPU_VECTOR_LIMIT		(64 * NR_CPUS)
#घोषणा IO_APIC_VECTOR_LIMIT		(32 * MAX_IO_APICS)

#अगर defined(CONFIG_X86_IO_APIC) && defined(CONFIG_PCI_MSI)
#घोषणा NR_IRQS						\
	(CPU_VECTOR_LIMIT > IO_APIC_VECTOR_LIMIT ?	\
		(NR_VECTORS + CPU_VECTOR_LIMIT)  :	\
		(NR_VECTORS + IO_APIC_VECTOR_LIMIT))
#या_अगर defined(CONFIG_X86_IO_APIC)
#घोषणा	NR_IRQS				(NR_VECTORS + IO_APIC_VECTOR_LIMIT)
#या_अगर defined(CONFIG_PCI_MSI)
#घोषणा NR_IRQS				(NR_VECTORS + CPU_VECTOR_LIMIT)
#अन्यथा
#घोषणा NR_IRQS				NR_IRQS_LEGACY
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_IRQ_VECTORS_H */
