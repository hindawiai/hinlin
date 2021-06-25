<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/linkage.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/समयx.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/device.h>
#समावेश <linux/bitops.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/prom.h>

/*
 * ISA PIC or low IO-APIC triggered (INTA-cycle or APIC) पूर्णांकerrupts:
 * (these are usually mapped to vectors 0x30-0x3f)
 */

/*
 * The IO-APIC gives us many more पूर्णांकerrupt sources. Most of these
 * are unused but an SMP प्रणाली is supposed to have enough memory ...
 * someबार (mostly wrt. hw bugs) we get corrupted vectors all
 * across the spectrum, so we really want to be prepared to get all
 * of these. Plus, more घातerful प्रणालीs might have more than 64
 * IO-APIC रेजिस्टरs.
 *
 * (these are usually mapped पूर्णांकo the 0x30-0xff vector range)
 */

DEFINE_PER_CPU(vector_irq_t, vector_irq) = अणु
	[0 ... NR_VECTORS - 1] = VECTOR_UNUSED,
पूर्ण;

व्योम __init init_ISA_irqs(व्योम)
अणु
	काष्ठा irq_chip *chip = legacy_pic->chip;
	पूर्णांक i;

	/*
	 * Try to set up the through-local-APIC भव wire mode earlier.
	 *
	 * On some 32-bit UP machines, whose APIC has been disabled by BIOS
	 * and then got re-enabled by "lapic", it hangs at boot समय without this.
	 */
	init_bsp_APIC();

	legacy_pic->init(0);

	क्रम (i = 0; i < nr_legacy_irqs(); i++)
		irq_set_chip_and_handler(i, chip, handle_level_irq);
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक i;

	/*
	 * On cpu 0, Assign ISA_IRQ_VECTOR(irq) to IRQ 0..15.
	 * If these IRQ's are handled by legacy पूर्णांकerrupt-controllers like PIC,
	 * then this configuration will likely be अटल after the boot. If
	 * these IRQs are handled by more modern controllers like IO-APIC,
	 * then this vector space can be मुक्तd and re-used dynamically as the
	 * irq's migrate etc.
	 */
	क्रम (i = 0; i < nr_legacy_irqs(); i++)
		per_cpu(vector_irq, 0)[ISA_IRQ_VECTOR(i)] = irq_to_desc(i);

	BUG_ON(irq_init_percpu_irqstack(smp_processor_id()));

	x86_init.irqs.पूर्णांकr_init();
पूर्ण

व्योम __init native_init_IRQ(व्योम)
अणु
	/* Execute any quirks beक्रमe the call gates are initialised: */
	x86_init.irqs.pre_vector_init();

	idt_setup_apic_and_irq_gates();
	lapic_assign_प्रणाली_vectors();

	अगर (!acpi_ioapic && !of_ioapic && nr_legacy_irqs()) अणु
		/* IRQ2 is cascade पूर्णांकerrupt to second पूर्णांकerrupt controller */
		अगर (request_irq(2, no_action, IRQF_NO_THREAD, "cascade", शून्य))
			pr_err("%s: request_irq() failed\n", "cascade");
	पूर्ण
पूर्ण
