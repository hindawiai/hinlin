<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM64 ACPI Parking Protocol implementation
 *
 * Authors: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 *	    Mark Salter <msalter@redhat.com>
 */
#समावेश <linux/acpi.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cpu_ops.h>

काष्ठा parking_protocol_mailbox अणु
	__le32 cpu_id;
	__le32 reserved;
	__le64 entry_poपूर्णांक;
पूर्ण;

काष्ठा cpu_mailbox_entry अणु
	काष्ठा parking_protocol_mailbox __iomem *mailbox;
	phys_addr_t mailbox_addr;
	u8 version;
	u8 gic_cpu_id;
पूर्ण;

अटल काष्ठा cpu_mailbox_entry cpu_mailbox_entries[NR_CPUS];

व्योम __init acpi_set_mailbox_entry(पूर्णांक cpu,
				   काष्ठा acpi_madt_generic_पूर्णांकerrupt *p)
अणु
	काष्ठा cpu_mailbox_entry *cpu_entry = &cpu_mailbox_entries[cpu];

	cpu_entry->mailbox_addr = p->parked_address;
	cpu_entry->version = p->parking_version;
	cpu_entry->gic_cpu_id = p->cpu_पूर्णांकerface_number;
पूर्ण

bool acpi_parking_protocol_valid(पूर्णांक cpu)
अणु
	काष्ठा cpu_mailbox_entry *cpu_entry = &cpu_mailbox_entries[cpu];

	वापस cpu_entry->mailbox_addr && cpu_entry->version;
पूर्ण

अटल पूर्णांक acpi_parking_protocol_cpu_init(अचिन्हित पूर्णांक cpu)
अणु
	pr_debug("%s: ACPI parked addr=%llx\n", __func__,
		  cpu_mailbox_entries[cpu].mailbox_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_parking_protocol_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_parking_protocol_cpu_boot(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_mailbox_entry *cpu_entry = &cpu_mailbox_entries[cpu];
	काष्ठा parking_protocol_mailbox __iomem *mailbox;
	u32 cpu_id;

	/*
	 * Map mailbox memory with attribute device nGnRE (ie ioremap -
	 * this deviates from the parking protocol specअगरications since
	 * the mailboxes are required to be mapped nGnRnE; the attribute
	 * discrepancy is harmless insofar as the protocol specअगरication
	 * is concerned).
	 * If the mailbox is mistakenly allocated in the linear mapping
	 * by FW ioremap will fail since the mapping will be prevented
	 * by the kernel (it clashes with the linear mapping attributes
	 * specअगरications).
	 */
	mailbox = ioremap(cpu_entry->mailbox_addr, माप(*mailbox));
	अगर (!mailbox)
		वापस -EIO;

	cpu_id = पढ़ोl_relaxed(&mailbox->cpu_id);
	/*
	 * Check अगर firmware has set-up the mailbox entry properly
	 * beक्रमe kickstarting the respective cpu.
	 */
	अगर (cpu_id != ~0U) अणु
		iounmap(mailbox);
		वापस -ENXIO;
	पूर्ण

	/*
	 * stash the mailbox address mapping to use it क्रम further FW
	 * checks in the postboot method
	 */
	cpu_entry->mailbox = mailbox;

	/*
	 * We ग_लिखो the entry poपूर्णांक and cpu id as LE regardless of the
	 * native endianness of the kernel. Thereक्रमe, any boot-loaders
	 * that पढ़ो this address need to convert this address to the
	 * Boot-Loader's endianness beक्रमe jumping.
	 */
	ग_लिखोq_relaxed(__pa_symbol(function_nocfi(secondary_entry)),
		       &mailbox->entry_poपूर्णांक);
	ग_लिखोl_relaxed(cpu_entry->gic_cpu_id, &mailbox->cpu_id);

	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	वापस 0;
पूर्ण

अटल व्योम acpi_parking_protocol_cpu_postboot(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा cpu_mailbox_entry *cpu_entry = &cpu_mailbox_entries[cpu];
	काष्ठा parking_protocol_mailbox __iomem *mailbox = cpu_entry->mailbox;
	u64 entry_poपूर्णांक;

	entry_poपूर्णांक = पढ़ोq_relaxed(&mailbox->entry_poपूर्णांक);
	/*
	 * Check अगर firmware has cleared the entry_poपूर्णांक as expected
	 * by the protocol specअगरication.
	 */
	WARN_ON(entry_poपूर्णांक);
पूर्ण

स्थिर काष्ठा cpu_operations acpi_parking_protocol_ops = अणु
	.name		= "parking-protocol",
	.cpu_init	= acpi_parking_protocol_cpu_init,
	.cpu_prepare	= acpi_parking_protocol_cpu_prepare,
	.cpu_boot	= acpi_parking_protocol_cpu_boot,
	.cpu_postboot	= acpi_parking_protocol_cpu_postboot
पूर्ण;
