<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  boot.c - Architecture-Specअगरic Low-Level ACPI Boot Support
 *
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2001 Jun Nakajima <jun.nakajima@पूर्णांकel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/acpi_pmपंचांगr.h>
#समावेश <linux/efi.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/export.h>
#समावेश <linux/dmi.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/memblock.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/efi-bgrt.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/setup.h>

#समावेश "sleep.h" /* To include x86_acpi_suspend_lowlevel */
अटल पूर्णांक __initdata acpi_क्रमce = 0;
पूर्णांक acpi_disabled;
EXPORT_SYMBOL(acpi_disabled);

#अगर_घोषित	CONFIG_X86_64
# include <यंत्र/proto.h>
#पूर्ण_अगर				/* X86 */

#घोषणा PREFIX			"ACPI: "

पूर्णांक acpi_noirq;				/* skip ACPI IRQ initialization */
अटल पूर्णांक acpi_nobgrt;			/* skip ACPI BGRT */
पूर्णांक acpi_pci_disabled;		/* skip ACPI PCI scan and IRQ initialization */
EXPORT_SYMBOL(acpi_pci_disabled);

पूर्णांक acpi_lapic;
पूर्णांक acpi_ioapic;
पूर्णांक acpi_strict;
पूर्णांक acpi_disable_cmcff;

/* ACPI SCI override configuration */
u8 acpi_sci_flags __initdata;
u32 acpi_sci_override_gsi __initdata = INVALID_ACPI_IRQ;
पूर्णांक acpi_skip_समयr_override __initdata;
पूर्णांक acpi_use_समयr_override __initdata;
पूर्णांक acpi_fix_pin2_polarity __initdata;

#अगर_घोषित CONFIG_X86_LOCAL_APIC
अटल u64 acpi_lapic_addr __initdata = APIC_DEFAULT_PHYS_BASE;
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_IO_APIC
/*
 * Locks related to IOAPIC hotplug
 * Hotplug side:
 *	->device_hotplug_lock
 *		->acpi_ioapic_lock
 *			->ioapic_lock
 * Interrupt mapping side:
 *	->acpi_ioapic_lock
 *		->ioapic_mutex
 *			->ioapic_lock
 */
अटल DEFINE_MUTEX(acpi_ioapic_lock);
#पूर्ण_अगर

/* --------------------------------------------------------------------------
                              Boot-समय Configuration
   -------------------------------------------------------------------------- */

/*
 * The शेष पूर्णांकerrupt routing model is PIC (8259).  This माला_लो
 * overridden अगर IOAPICs are क्रमागतerated (below).
 */
क्रमागत acpi_irq_model_id acpi_irq_model = ACPI_IRQ_MODEL_PIC;


/*
 * ISA irqs by शेष are the first 16 gsis but can be
 * any gsi as specअगरied by an पूर्णांकerrupt source override.
 */
अटल u32 isa_irq_to_gsi[NR_IRQS_LEGACY] __पढ़ो_mostly = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
पूर्ण;

/*
 * This is just a simple wrapper around early_memremap(),
 * with sanity checks क्रम phys == 0 and size == 0.
 */
व्योम __init __iomem *__acpi_map_table(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size)
अणु

	अगर (!phys || !size)
		वापस शून्य;

	वापस early_memremap(phys, size);
पूर्ण

व्योम __init __acpi_unmap_table(व्योम __iomem *map, अचिन्हित दीर्घ size)
अणु
	अगर (!map || !size)
		वापस;

	early_memunmap(map, size);
पूर्ण

#अगर_घोषित CONFIG_X86_LOCAL_APIC
अटल पूर्णांक __init acpi_parse_madt(काष्ठा acpi_table_header *table)
अणु
	काष्ठा acpi_table_madt *madt = शून्य;

	अगर (!boot_cpu_has(X86_FEATURE_APIC))
		वापस -EINVAL;

	madt = (काष्ठा acpi_table_madt *)table;
	अगर (!madt) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "Unable to map MADT\n");
		वापस -ENODEV;
	पूर्ण

	अगर (madt->address) अणु
		acpi_lapic_addr = (u64) madt->address;

		prपूर्णांकk(KERN_DEBUG PREFIX "Local APIC address 0x%08x\n",
		       madt->address);
	पूर्ण

	शेष_acpi_madt_oem_check(madt->header.oem_id,
				    madt->header.oem_table_id);

	वापस 0;
पूर्ण

/**
 * acpi_रेजिस्टर_lapic - रेजिस्टर a local apic and generates a logic cpu number
 * @id: local apic id to रेजिस्टर
 * @acpiid: ACPI id to रेजिस्टर
 * @enabled: this cpu is enabled or not
 *
 * Returns the logic cpu number which maps to the local apic
 */
अटल पूर्णांक acpi_रेजिस्टर_lapic(पूर्णांक id, u32 acpiid, u8 enabled)
अणु
	अचिन्हित पूर्णांक ver = 0;
	पूर्णांक cpu;

	अगर (id >= MAX_LOCAL_APIC) अणु
		prपूर्णांकk(KERN_INFO PREFIX "skipped apicid that is too big\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!enabled) अणु
		++disabled_cpus;
		वापस -EINVAL;
	पूर्ण

	अगर (boot_cpu_physical_apicid != -1U)
		ver = boot_cpu_apic_version;

	cpu = generic_processor_info(id, ver);
	अगर (cpu >= 0)
		early_per_cpu(x86_cpu_to_acpiid, cpu) = acpiid;

	वापस cpu;
पूर्ण

अटल पूर्णांक __init
acpi_parse_x2apic(जोड़ acpi_subtable_headers *header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_local_x2apic *processor = शून्य;
#अगर_घोषित CONFIG_X86_X2APIC
	u32 apic_id;
	u8 enabled;
#पूर्ण_अगर

	processor = (काष्ठा acpi_madt_local_x2apic *)header;

	अगर (BAD_MADT_ENTRY(processor, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

#अगर_घोषित CONFIG_X86_X2APIC
	apic_id = processor->local_apic_id;
	enabled = processor->lapic_flags & ACPI_MADT_ENABLED;

	/* Ignore invalid ID */
	अगर (apic_id == 0xffffffff)
		वापस 0;

	/*
	 * We need to रेजिस्टर disabled CPU as well to permit
	 * counting disabled CPUs. This allows us to size
	 * cpus_possible_map more accurately, to permit
	 * to not pपुनः_स्मृतिating memory क्रम all NR_CPUS
	 * when we use CPU hotplug.
	 */
	अगर (!apic->apic_id_valid(apic_id)) अणु
		अगर (enabled)
			pr_warn(PREFIX "x2apic entry ignored\n");
		वापस 0;
	पूर्ण

	acpi_रेजिस्टर_lapic(apic_id, processor->uid, enabled);
#अन्यथा
	prपूर्णांकk(KERN_WARNING PREFIX "x2apic entry ignored\n");
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_lapic(जोड़ acpi_subtable_headers * header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_local_apic *processor = शून्य;

	processor = (काष्ठा acpi_madt_local_apic *)header;

	अगर (BAD_MADT_ENTRY(processor, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

	/* Ignore invalid ID */
	अगर (processor->id == 0xff)
		वापस 0;

	/*
	 * We need to रेजिस्टर disabled CPU as well to permit
	 * counting disabled CPUs. This allows us to size
	 * cpus_possible_map more accurately, to permit
	 * to not pपुनः_स्मृतिating memory क्रम all NR_CPUS
	 * when we use CPU hotplug.
	 */
	acpi_रेजिस्टर_lapic(processor->id,	/* APIC ID */
			    processor->processor_id, /* ACPI ID */
			    processor->lapic_flags & ACPI_MADT_ENABLED);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_sapic(जोड़ acpi_subtable_headers *header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_local_sapic *processor = शून्य;

	processor = (काष्ठा acpi_madt_local_sapic *)header;

	अगर (BAD_MADT_ENTRY(processor, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

	acpi_रेजिस्टर_lapic((processor->id << 8) | processor->eid,/* APIC ID */
			    processor->processor_id, /* ACPI ID */
			    processor->lapic_flags & ACPI_MADT_ENABLED);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_lapic_addr_ovr(जोड़ acpi_subtable_headers * header,
			  स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_local_apic_override *lapic_addr_ovr = शून्य;

	lapic_addr_ovr = (काष्ठा acpi_madt_local_apic_override *)header;

	अगर (BAD_MADT_ENTRY(lapic_addr_ovr, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

	acpi_lapic_addr = lapic_addr_ovr->address;

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_x2apic_nmi(जोड़ acpi_subtable_headers *header,
		      स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_local_x2apic_nmi *x2apic_nmi = शून्य;

	x2apic_nmi = (काष्ठा acpi_madt_local_x2apic_nmi *)header;

	अगर (BAD_MADT_ENTRY(x2apic_nmi, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

	अगर (x2apic_nmi->lपूर्णांक != 1)
		prपूर्णांकk(KERN_WARNING PREFIX "NMI not connected to LINT 1!\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_lapic_nmi(जोड़ acpi_subtable_headers * header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_local_apic_nmi *lapic_nmi = शून्य;

	lapic_nmi = (काष्ठा acpi_madt_local_apic_nmi *)header;

	अगर (BAD_MADT_ENTRY(lapic_nmi, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

	अगर (lapic_nmi->lपूर्णांक != 1)
		prपूर्णांकk(KERN_WARNING PREFIX "NMI not connected to LINT 1!\n");

	वापस 0;
पूर्ण

#पूर्ण_अगर				/*CONFIG_X86_LOCAL_APIC */

#अगर_घोषित CONFIG_X86_IO_APIC
#घोषणा MP_ISA_BUS		0

अटल पूर्णांक __init mp_रेजिस्टर_ioapic_irq(u8 bus_irq, u8 polarity,
						u8 trigger, u32 gsi);

अटल व्योम __init mp_override_legacy_irq(u8 bus_irq, u8 polarity, u8 trigger,
					  u32 gsi)
अणु
	/*
	 * Check bus_irq boundary.
	 */
	अगर (bus_irq >= NR_IRQS_LEGACY) अणु
		pr_warn("Invalid bus_irq %u for legacy override\n", bus_irq);
		वापस;
	पूर्ण

	/*
	 * TBD: This check is क्रम faulty समयr entries, where the override
	 *      erroneously sets the trigger to level, resulting in a HUGE
	 *      increase of समयr पूर्णांकerrupts!
	 */
	अगर ((bus_irq == 0) && (trigger == 3))
		trigger = 1;

	अगर (mp_रेजिस्टर_ioapic_irq(bus_irq, polarity, trigger, gsi) < 0)
		वापस;
	/*
	 * Reset शेष identity mapping अगर gsi is also an legacy IRQ,
	 * otherwise there will be more than one entry with the same GSI
	 * and acpi_isa_irq_to_gsi() may give wrong result.
	 */
	अगर (gsi < nr_legacy_irqs() && isa_irq_to_gsi[gsi] == gsi)
		isa_irq_to_gsi[gsi] = INVALID_ACPI_IRQ;
	isa_irq_to_gsi[bus_irq] = gsi;
पूर्ण

अटल पूर्णांक mp_config_acpi_gsi(काष्ठा device *dev, u32 gsi, पूर्णांक trigger,
			पूर्णांक polarity)
अणु
#अगर_घोषित CONFIG_X86_MPPARSE
	काष्ठा mpc_पूर्णांकsrc mp_irq;
	काष्ठा pci_dev *pdev;
	अचिन्हित अक्षर number;
	अचिन्हित पूर्णांक devfn;
	पूर्णांक ioapic;
	u8 pin;

	अगर (!acpi_ioapic)
		वापस 0;
	अगर (!dev || !dev_is_pci(dev))
		वापस 0;

	pdev = to_pci_dev(dev);
	number = pdev->bus->number;
	devfn = pdev->devfn;
	pin = pdev->pin;
	/* prपूर्णांक the entry should happen on mptable identically */
	mp_irq.type = MP_INTSRC;
	mp_irq.irqtype = mp_INT;
	mp_irq.irqflag = (trigger == ACPI_EDGE_SENSITIVE ? 4 : 0x0c) |
				(polarity == ACPI_ACTIVE_HIGH ? 1 : 3);
	mp_irq.srcbus = number;
	mp_irq.srcbusirq = (((devfn >> 3) & 0x1f) << 2) | ((pin - 1) & 3);
	ioapic = mp_find_ioapic(gsi);
	mp_irq.dstapic = mpc_ioapic_id(ioapic);
	mp_irq.dstirq = mp_find_ioapic_pin(ioapic, gsi);

	mp_save_irq(&mp_irq);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __init mp_रेजिस्टर_ioapic_irq(u8 bus_irq, u8 polarity,
						u8 trigger, u32 gsi)
अणु
	काष्ठा mpc_पूर्णांकsrc mp_irq;
	पूर्णांक ioapic, pin;

	/* Convert 'gsi' to 'ioapic.pin'(INTIN#) */
	ioapic = mp_find_ioapic(gsi);
	अगर (ioapic < 0) अणु
		pr_warn("Failed to find ioapic for gsi : %u\n", gsi);
		वापस ioapic;
	पूर्ण

	pin = mp_find_ioapic_pin(ioapic, gsi);

	mp_irq.type = MP_INTSRC;
	mp_irq.irqtype = mp_INT;
	mp_irq.irqflag = (trigger << 2) | polarity;
	mp_irq.srcbus = MP_ISA_BUS;
	mp_irq.srcbusirq = bus_irq;
	mp_irq.dstapic = mpc_ioapic_id(ioapic);
	mp_irq.dstirq = pin;

	mp_save_irq(&mp_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_ioapic(जोड़ acpi_subtable_headers * header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_io_apic *ioapic = शून्य;
	काष्ठा ioapic_करोमुख्य_cfg cfg = अणु
		.type = IOAPIC_DOMAIN_DYNAMIC,
		.ops = &mp_ioapic_irqकरोमुख्य_ops,
	पूर्ण;

	ioapic = (काष्ठा acpi_madt_io_apic *)header;

	अगर (BAD_MADT_ENTRY(ioapic, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

	/* Statically assign IRQ numbers क्रम IOAPICs hosting legacy IRQs */
	अगर (ioapic->global_irq_base < nr_legacy_irqs())
		cfg.type = IOAPIC_DOMAIN_LEGACY;

	mp_रेजिस्टर_ioapic(ioapic->id, ioapic->address, ioapic->global_irq_base,
			   &cfg);

	वापस 0;
पूर्ण

/*
 * Parse Interrupt Source Override क्रम the ACPI SCI
 */
अटल व्योम __init acpi_sci_ioapic_setup(u8 bus_irq, u16 polarity, u16 trigger, u32 gsi)
अणु
	अगर (trigger == 0)	/* compatible SCI trigger is level */
		trigger = 3;

	अगर (polarity == 0)	/* compatible SCI polarity is low */
		polarity = 3;

	/* Command-line over-ride via acpi_sci= */
	अगर (acpi_sci_flags & ACPI_MADT_TRIGGER_MASK)
		trigger = (acpi_sci_flags & ACPI_MADT_TRIGGER_MASK) >> 2;

	अगर (acpi_sci_flags & ACPI_MADT_POLARITY_MASK)
		polarity = acpi_sci_flags & ACPI_MADT_POLARITY_MASK;

	अगर (bus_irq < NR_IRQS_LEGACY)
		mp_override_legacy_irq(bus_irq, polarity, trigger, gsi);
	अन्यथा
		mp_रेजिस्टर_ioapic_irq(bus_irq, polarity, trigger, gsi);

	acpi_penalize_sci_irq(bus_irq, trigger, polarity);

	/*
	 * stash over-ride to indicate we've been here
	 * and क्रम later update of acpi_gbl_FADT
	 */
	acpi_sci_override_gsi = gsi;
	वापस;
पूर्ण

अटल पूर्णांक __init
acpi_parse_पूर्णांक_src_ovr(जोड़ acpi_subtable_headers * header,
		       स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_पूर्णांकerrupt_override *पूर्णांकsrc = शून्य;

	पूर्णांकsrc = (काष्ठा acpi_madt_पूर्णांकerrupt_override *)header;

	अगर (BAD_MADT_ENTRY(पूर्णांकsrc, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

	अगर (पूर्णांकsrc->source_irq == acpi_gbl_FADT.sci_पूर्णांकerrupt) अणु
		acpi_sci_ioapic_setup(पूर्णांकsrc->source_irq,
				      पूर्णांकsrc->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK,
				      (पूर्णांकsrc->पूर्णांकi_flags & ACPI_MADT_TRIGGER_MASK) >> 2,
				      पूर्णांकsrc->global_irq);
		वापस 0;
	पूर्ण

	अगर (पूर्णांकsrc->source_irq == 0) अणु
		अगर (acpi_skip_समयr_override) अणु
			prपूर्णांकk(PREFIX "BIOS IRQ0 override ignored.\n");
			वापस 0;
		पूर्ण

		अगर ((पूर्णांकsrc->global_irq == 2) && acpi_fix_pin2_polarity
			&& (पूर्णांकsrc->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK)) अणु
			पूर्णांकsrc->पूर्णांकi_flags &= ~ACPI_MADT_POLARITY_MASK;
			prपूर्णांकk(PREFIX "BIOS IRQ0 pin2 override: forcing polarity to high active.\n");
		पूर्ण
	पूर्ण

	mp_override_legacy_irq(पूर्णांकsrc->source_irq,
				पूर्णांकsrc->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK,
				(पूर्णांकsrc->पूर्णांकi_flags & ACPI_MADT_TRIGGER_MASK) >> 2,
				पूर्णांकsrc->global_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_nmi_src(जोड़ acpi_subtable_headers * header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_nmi_source *nmi_src = शून्य;

	nmi_src = (काष्ठा acpi_madt_nmi_source *)header;

	अगर (BAD_MADT_ENTRY(nmi_src, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

	/* TBD: Support nimsrc entries? */

	वापस 0;
पूर्ण

#पूर्ण_अगर				/* CONFIG_X86_IO_APIC */

/*
 * acpi_pic_sci_set_trigger()
 *
 * use ELCR to set PIC-mode trigger type क्रम SCI
 *
 * If a PIC-mode SCI is not recognized or gives spurious IRQ7's
 * it may require Edge Trigger -- use "acpi_sci=edge"
 *
 * Port 0x4d0-4d1 are ECLR1 and ECLR2, the Edge/Level Control Registers
 * क्रम the 8259 PIC.  bit[n] = 1 means irq[n] is Level, otherwise Edge.
 * ECLR1 is IRQs 0-7 (IRQ 0, 1, 2 must be 0)
 * ECLR2 is IRQs 8-15 (IRQ 8, 13 must be 0)
 */

व्योम __init acpi_pic_sci_set_trigger(अचिन्हित पूर्णांक irq, u16 trigger)
अणु
	अचिन्हित पूर्णांक mask = 1 << irq;
	अचिन्हित पूर्णांक old, new;

	/* Real old ELCR mask */
	old = inb(0x4d0) | (inb(0x4d1) << 8);

	/*
	 * If we use ACPI to set PCI IRQs, then we should clear ELCR
	 * since we will set it correctly as we enable the PCI irq
	 * routing.
	 */
	new = acpi_noirq ? old : 0;

	/*
	 * Update SCI inक्रमmation in the ELCR, it isn't in the PCI
	 * routing tables..
	 */
	चयन (trigger) अणु
	हाल 1:		/* Edge - clear */
		new &= ~mask;
		अवरोध;
	हाल 3:		/* Level - set */
		new |= mask;
		अवरोध;
	पूर्ण

	अगर (old == new)
		वापस;

	prपूर्णांकk(PREFIX "setting ELCR to %04x (from %04x)\n", new, old);
	outb(new, 0x4d0);
	outb(new >> 8, 0x4d1);
पूर्ण

पूर्णांक acpi_gsi_to_irq(u32 gsi, अचिन्हित पूर्णांक *irqp)
अणु
	पूर्णांक rc, irq, trigger, polarity;

	अगर (acpi_irq_model == ACPI_IRQ_MODEL_PIC) अणु
		*irqp = gsi;
		वापस 0;
	पूर्ण

	rc = acpi_get_override_irq(gsi, &trigger, &polarity);
	अगर (rc)
		वापस rc;

	trigger = trigger ? ACPI_LEVEL_SENSITIVE : ACPI_EDGE_SENSITIVE;
	polarity = polarity ? ACPI_ACTIVE_LOW : ACPI_ACTIVE_HIGH;
	irq = acpi_रेजिस्टर_gsi(शून्य, gsi, trigger, polarity);
	अगर (irq < 0)
		वापस irq;

	*irqp = irq;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_gsi_to_irq);

पूर्णांक acpi_isa_irq_to_gsi(अचिन्हित isa_irq, u32 *gsi)
अणु
	अगर (isa_irq < nr_legacy_irqs() &&
	    isa_irq_to_gsi[isa_irq] != INVALID_ACPI_IRQ) अणु
		*gsi = isa_irq_to_gsi[isa_irq];
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक acpi_रेजिस्टर_gsi_pic(काष्ठा device *dev, u32 gsi,
				 पूर्णांक trigger, पूर्णांक polarity)
अणु
#अगर_घोषित CONFIG_PCI
	/*
	 * Make sure all (legacy) PCI IRQs are set as level-triggered.
	 */
	अगर (trigger == ACPI_LEVEL_SENSITIVE)
		elcr_set_level_irq(gsi);
#पूर्ण_अगर

	वापस gsi;
पूर्ण

#अगर_घोषित CONFIG_X86_LOCAL_APIC
अटल पूर्णांक acpi_रेजिस्टर_gsi_ioapic(काष्ठा device *dev, u32 gsi,
				    पूर्णांक trigger, पूर्णांक polarity)
अणु
	पूर्णांक irq = gsi;
#अगर_घोषित CONFIG_X86_IO_APIC
	पूर्णांक node;
	काष्ठा irq_alloc_info info;

	node = dev ? dev_to_node(dev) : NUMA_NO_NODE;
	trigger = trigger == ACPI_EDGE_SENSITIVE ? 0 : 1;
	polarity = polarity == ACPI_ACTIVE_HIGH ? 0 : 1;
	ioapic_set_alloc_attr(&info, node, trigger, polarity);

	mutex_lock(&acpi_ioapic_lock);
	irq = mp_map_gsi_to_irq(gsi, IOAPIC_MAP_ALLOC, &info);
	/* Don't set up the ACPI SCI because it's alपढ़ोy set up */
	अगर (irq >= 0 && enable_update_mptable && gsi != acpi_gbl_FADT.sci_पूर्णांकerrupt)
		mp_config_acpi_gsi(dev, gsi, trigger, polarity);
	mutex_unlock(&acpi_ioapic_lock);
#पूर्ण_अगर

	वापस irq;
पूर्ण

अटल व्योम acpi_unरेजिस्टर_gsi_ioapic(u32 gsi)
अणु
#अगर_घोषित CONFIG_X86_IO_APIC
	पूर्णांक irq;

	mutex_lock(&acpi_ioapic_lock);
	irq = mp_map_gsi_to_irq(gsi, 0, शून्य);
	अगर (irq > 0)
		mp_unmap_irq(irq);
	mutex_unlock(&acpi_ioapic_lock);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

पूर्णांक (*__acpi_रेजिस्टर_gsi)(काष्ठा device *dev, u32 gsi,
			   पूर्णांक trigger, पूर्णांक polarity) = acpi_रेजिस्टर_gsi_pic;
व्योम (*__acpi_unरेजिस्टर_gsi)(u32 gsi) = शून्य;

#अगर_घोषित CONFIG_ACPI_SLEEP
पूर्णांक (*acpi_suspend_lowlevel)(व्योम) = x86_acpi_suspend_lowlevel;
#अन्यथा
पूर्णांक (*acpi_suspend_lowlevel)(व्योम);
#पूर्ण_अगर

/*
 * success: वापस IRQ number (>=0)
 * failure: वापस < 0
 */
पूर्णांक acpi_रेजिस्टर_gsi(काष्ठा device *dev, u32 gsi, पूर्णांक trigger, पूर्णांक polarity)
अणु
	वापस __acpi_रेजिस्टर_gsi(dev, gsi, trigger, polarity);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_रेजिस्टर_gsi);

व्योम acpi_unरेजिस्टर_gsi(u32 gsi)
अणु
	अगर (__acpi_unरेजिस्टर_gsi)
		__acpi_unरेजिस्टर_gsi(gsi);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_unरेजिस्टर_gsi);

#अगर_घोषित CONFIG_X86_LOCAL_APIC
अटल व्योम __init acpi_set_irq_model_ioapic(व्योम)
अणु
	acpi_irq_model = ACPI_IRQ_MODEL_IOAPIC;
	__acpi_रेजिस्टर_gsi = acpi_रेजिस्टर_gsi_ioapic;
	__acpi_unरेजिस्टर_gsi = acpi_unरेजिस्टर_gsi_ioapic;
	acpi_ioapic = 1;
पूर्ण
#पूर्ण_अगर

/*
 *  ACPI based hotplug support क्रम CPU
 */
#अगर_घोषित CONFIG_ACPI_HOTPLUG_CPU
#समावेश <acpi/processor.h>

अटल पूर्णांक acpi_map_cpu2node(acpi_handle handle, पूर्णांक cpu, पूर्णांक physid)
अणु
#अगर_घोषित CONFIG_ACPI_NUMA
	पूर्णांक nid;

	nid = acpi_get_node(handle);
	अगर (nid != NUMA_NO_NODE) अणु
		set_apicid_to_node(physid, nid);
		numa_set_node(cpu, nid);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक acpi_map_cpu(acpi_handle handle, phys_cpuid_t physid, u32 acpi_id,
		 पूर्णांक *pcpu)
अणु
	पूर्णांक cpu;

	cpu = acpi_रेजिस्टर_lapic(physid, acpi_id, ACPI_MADT_ENABLED);
	अगर (cpu < 0) अणु
		pr_info(PREFIX "Unable to map lapic to logical cpu number\n");
		वापस cpu;
	पूर्ण

	acpi_processor_set_pdc(handle);
	acpi_map_cpu2node(handle, cpu, physid);

	*pcpu = cpu;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(acpi_map_cpu);

पूर्णांक acpi_unmap_cpu(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_ACPI_NUMA
	set_apicid_to_node(per_cpu(x86_cpu_to_apicid, cpu), NUMA_NO_NODE);
#पूर्ण_अगर

	per_cpu(x86_cpu_to_apicid, cpu) = -1;
	set_cpu_present(cpu, false);
	num_processors--;

	वापस (0);
पूर्ण
EXPORT_SYMBOL(acpi_unmap_cpu);
#पूर्ण_अगर				/* CONFIG_ACPI_HOTPLUG_CPU */

पूर्णांक acpi_रेजिस्टर_ioapic(acpi_handle handle, u64 phys_addr, u32 gsi_base)
अणु
	पूर्णांक ret = -ENOSYS;
#अगर_घोषित CONFIG_ACPI_HOTPLUG_IOAPIC
	पूर्णांक ioapic_id;
	u64 addr;
	काष्ठा ioapic_करोमुख्य_cfg cfg = अणु
		.type = IOAPIC_DOMAIN_DYNAMIC,
		.ops = &mp_ioapic_irqकरोमुख्य_ops,
	पूर्ण;

	ioapic_id = acpi_get_ioapic_id(handle, gsi_base, &addr);
	अगर (ioapic_id < 0) अणु
		अचिन्हित दीर्घ दीर्घ uid;
		acpi_status status;

		status = acpi_evaluate_पूर्णांकeger(handle, METHOD_NAME__UID,
					       शून्य, &uid);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_handle_warn(handle, "failed to get IOAPIC ID.\n");
			वापस -EINVAL;
		पूर्ण
		ioapic_id = (पूर्णांक)uid;
	पूर्ण

	mutex_lock(&acpi_ioapic_lock);
	ret  = mp_रेजिस्टर_ioapic(ioapic_id, phys_addr, gsi_base, &cfg);
	mutex_unlock(&acpi_ioapic_lock);
#पूर्ण_अगर

	वापस ret;
पूर्ण
EXPORT_SYMBOL(acpi_रेजिस्टर_ioapic);

पूर्णांक acpi_unरेजिस्टर_ioapic(acpi_handle handle, u32 gsi_base)
अणु
	पूर्णांक ret = -ENOSYS;

#अगर_घोषित CONFIG_ACPI_HOTPLUG_IOAPIC
	mutex_lock(&acpi_ioapic_lock);
	ret  = mp_unरेजिस्टर_ioapic(gsi_base);
	mutex_unlock(&acpi_ioapic_lock);
#पूर्ण_अगर

	वापस ret;
पूर्ण
EXPORT_SYMBOL(acpi_unरेजिस्टर_ioapic);

/**
 * acpi_ioapic_रेजिस्टरed - Check whether IOAPIC associated with @gsi_base
 *			    has been रेजिस्टरed
 * @handle:	ACPI handle of the IOAPIC device
 * @gsi_base:	GSI base associated with the IOAPIC
 *
 * Assume caller holds some type of lock to serialize acpi_ioapic_रेजिस्टरed()
 * with acpi_रेजिस्टर_ioapic()/acpi_unरेजिस्टर_ioapic().
 */
पूर्णांक acpi_ioapic_रेजिस्टरed(acpi_handle handle, u32 gsi_base)
अणु
	पूर्णांक ret = 0;

#अगर_घोषित CONFIG_ACPI_HOTPLUG_IOAPIC
	mutex_lock(&acpi_ioapic_lock);
	ret  = mp_ioapic_रेजिस्टरed(gsi_base);
	mutex_unlock(&acpi_ioapic_lock);
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक __init acpi_parse_sbf(काष्ठा acpi_table_header *table)
अणु
	काष्ठा acpi_table_boot *sb = (काष्ठा acpi_table_boot *)table;

	sbf_port = sb->cmos_index;	/* Save CMOS port */

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HPET_TIMER
#समावेश <यंत्र/hpet.h>

अटल काष्ठा resource *hpet_res __initdata;

अटल पूर्णांक __init acpi_parse_hpet(काष्ठा acpi_table_header *table)
अणु
	काष्ठा acpi_table_hpet *hpet_tbl = (काष्ठा acpi_table_hpet *)table;

	अगर (hpet_tbl->address.space_id != ACPI_SPACE_MEM) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "HPET timers must be located in "
		       "memory.\n");
		वापस -1;
	पूर्ण

	hpet_address = hpet_tbl->address.address;
	hpet_blockid = hpet_tbl->sequence;

	/*
	 * Some broken BIOSes advertise HPET at 0x0. We really करो not
	 * want to allocate a resource there.
	 */
	अगर (!hpet_address) अणु
		prपूर्णांकk(KERN_WARNING PREFIX
		       "HPET id: %#x base: %#lx is invalid\n",
		       hpet_tbl->id, hpet_address);
		वापस 0;
	पूर्ण
#अगर_घोषित CONFIG_X86_64
	/*
	 * Some even more broken BIOSes advertise HPET at
	 * 0xfed0000000000000 instead of 0xfed00000. Fix it up and add
	 * some noise:
	 */
	अगर (hpet_address == 0xfed0000000000000UL) अणु
		अगर (!hpet_क्रमce_user) अणु
			prपूर्णांकk(KERN_WARNING PREFIX "HPET id: %#x "
			       "base: 0xfed0000000000000 is bogus\n "
			       "try hpet=force on the kernel command line to "
			       "fix it up to 0xfed00000.\n", hpet_tbl->id);
			hpet_address = 0;
			वापस 0;
		पूर्ण
		prपूर्णांकk(KERN_WARNING PREFIX
		       "HPET id: %#x base: 0xfed0000000000000 fixed up "
		       "to 0xfed00000.\n", hpet_tbl->id);
		hpet_address >>= 32;
	पूर्ण
#पूर्ण_अगर
	prपूर्णांकk(KERN_INFO PREFIX "HPET id: %#x base: %#lx\n",
	       hpet_tbl->id, hpet_address);

	/*
	 * Allocate and initialize the HPET firmware resource क्रम adding पूर्णांकo
	 * the resource tree during the lateinit समयframe.
	 */
#घोषणा HPET_RESOURCE_NAME_SIZE 9
	hpet_res = memblock_alloc(माप(*hpet_res) + HPET_RESOURCE_NAME_SIZE,
				  SMP_CACHE_BYTES);
	अगर (!hpet_res)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*hpet_res) + HPET_RESOURCE_NAME_SIZE);

	hpet_res->name = (व्योम *)&hpet_res[1];
	hpet_res->flags = IORESOURCE_MEM;
	snम_लिखो((अक्षर *)hpet_res->name, HPET_RESOURCE_NAME_SIZE, "HPET %u",
		 hpet_tbl->sequence);

	hpet_res->start = hpet_address;
	hpet_res->end = hpet_address + (1 * 1024) - 1;

	वापस 0;
पूर्ण

/*
 * hpet_insert_resource inserts the HPET resources used पूर्णांकo the resource
 * tree.
 */
अटल __init पूर्णांक hpet_insert_resource(व्योम)
अणु
	अगर (!hpet_res)
		वापस 1;

	वापस insert_resource(&iomem_resource, hpet_res);
पूर्ण

late_initcall(hpet_insert_resource);

#अन्यथा
#घोषणा	acpi_parse_hpet	शून्य
#पूर्ण_अगर

अटल पूर्णांक __init acpi_parse_fadt(काष्ठा acpi_table_header *table)
अणु
	अगर (!(acpi_gbl_FADT.boot_flags & ACPI_FADT_LEGACY_DEVICES)) अणु
		pr_debug("ACPI: no legacy devices present\n");
		x86_platक्रमm.legacy.devices.pnpbios = 0;
	पूर्ण

	अगर (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
	    !(acpi_gbl_FADT.boot_flags & ACPI_FADT_8042) &&
	    x86_platक्रमm.legacy.i8042 != X86_LEGACY_I8042_PLATFORM_ABSENT) अणु
		pr_debug("ACPI: i8042 controller is absent\n");
		x86_platक्रमm.legacy.i8042 = X86_LEGACY_I8042_FIRMWARE_ABSENT;
	पूर्ण

	अगर (acpi_gbl_FADT.boot_flags & ACPI_FADT_NO_CMOS_RTC) अणु
		pr_debug("ACPI: not registering RTC platform device\n");
		x86_platक्रमm.legacy.rtc = 0;
	पूर्ण

	अगर (acpi_gbl_FADT.boot_flags & ACPI_FADT_NO_VGA) अणु
		pr_debug("ACPI: probing for VGA not safe\n");
		x86_platक्रमm.legacy.no_vga = 1;
	पूर्ण

#अगर_घोषित CONFIG_X86_PM_TIMER
	/* detect the location of the ACPI PM Timer */
	अगर (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID) अणु
		/* FADT rev. 2 */
		अगर (acpi_gbl_FADT.xpm_समयr_block.space_id !=
		    ACPI_ADR_SPACE_SYSTEM_IO)
			वापस 0;

		pmपंचांगr_ioport = acpi_gbl_FADT.xpm_समयr_block.address;
		/*
		 * "X" fields are optional extensions to the original V1.0
		 * fields, so we must selectively expand V1.0 fields अगर the
		 * corresponding X field is zero.
	 	 */
		अगर (!pmपंचांगr_ioport)
			pmपंचांगr_ioport = acpi_gbl_FADT.pm_समयr_block;
	पूर्ण अन्यथा अणु
		/* FADT rev. 1 */
		pmपंचांगr_ioport = acpi_gbl_FADT.pm_समयr_block;
	पूर्ण
	अगर (pmपंचांगr_ioport)
		prपूर्णांकk(KERN_INFO PREFIX "PM-Timer IO Port: %#x\n",
		       pmपंचांगr_ioport);
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित	CONFIG_X86_LOCAL_APIC
/*
 * Parse LAPIC entries in MADT
 * वापसs 0 on success, < 0 on error
 */

अटल पूर्णांक __init early_acpi_parse_madt_lapic_addr_ovr(व्योम)
अणु
	पूर्णांक count;

	अगर (!boot_cpu_has(X86_FEATURE_APIC))
		वापस -ENODEV;

	/*
	 * Note that the LAPIC address is obtained from the MADT (32-bit value)
	 * and (optionally) overridden by a LAPIC_ADDR_OVR entry (64-bit value).
	 */

	count = acpi_table_parse_madt(ACPI_MADT_TYPE_LOCAL_APIC_OVERRIDE,
				      acpi_parse_lapic_addr_ovr, 0);
	अगर (count < 0) अणु
		prपूर्णांकk(KERN_ERR PREFIX
		       "Error parsing LAPIC address override entry\n");
		वापस count;
	पूर्ण

	रेजिस्टर_lapic_address(acpi_lapic_addr);

	वापस count;
पूर्ण

अटल पूर्णांक __init acpi_parse_madt_lapic_entries(व्योम)
अणु
	पूर्णांक count;
	पूर्णांक x2count = 0;
	पूर्णांक ret;
	काष्ठा acpi_subtable_proc madt_proc[2];

	अगर (!boot_cpu_has(X86_FEATURE_APIC))
		वापस -ENODEV;

	count = acpi_table_parse_madt(ACPI_MADT_TYPE_LOCAL_SAPIC,
				      acpi_parse_sapic, MAX_LOCAL_APIC);

	अगर (!count) अणु
		स_रखो(madt_proc, 0, माप(madt_proc));
		madt_proc[0].id = ACPI_MADT_TYPE_LOCAL_APIC;
		madt_proc[0].handler = acpi_parse_lapic;
		madt_proc[1].id = ACPI_MADT_TYPE_LOCAL_X2APIC;
		madt_proc[1].handler = acpi_parse_x2apic;
		ret = acpi_table_parse_entries_array(ACPI_SIG_MADT,
				माप(काष्ठा acpi_table_madt),
				madt_proc, ARRAY_SIZE(madt_proc), MAX_LOCAL_APIC);
		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_ERR PREFIX
					"Error parsing LAPIC/X2APIC entries\n");
			वापस ret;
		पूर्ण

		count = madt_proc[0].count;
		x2count = madt_proc[1].count;
	पूर्ण
	अगर (!count && !x2count) अणु
		prपूर्णांकk(KERN_ERR PREFIX "No LAPIC entries present\n");
		/* TBD: Cleanup to allow fallback to MPS */
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (count < 0 || x2count < 0) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Error parsing LAPIC entry\n");
		/* TBD: Cleanup to allow fallback to MPS */
		वापस count;
	पूर्ण

	x2count = acpi_table_parse_madt(ACPI_MADT_TYPE_LOCAL_X2APIC_NMI,
					acpi_parse_x2apic_nmi, 0);
	count = acpi_table_parse_madt(ACPI_MADT_TYPE_LOCAL_APIC_NMI,
				      acpi_parse_lapic_nmi, 0);
	अगर (count < 0 || x2count < 0) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Error parsing LAPIC NMI entry\n");
		/* TBD: Cleanup to allow fallback to MPS */
		वापस count;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर				/* CONFIG_X86_LOCAL_APIC */

#अगर_घोषित	CONFIG_X86_IO_APIC
अटल व्योम __init mp_config_acpi_legacy_irqs(व्योम)
अणु
	पूर्णांक i;
	काष्ठा mpc_पूर्णांकsrc mp_irq;

#अगर_घोषित CONFIG_EISA
	/*
	 * Fabricate the legacy ISA bus (bus #31).
	 */
	mp_bus_id_to_type[MP_ISA_BUS] = MP_BUS_ISA;
#पूर्ण_अगर
	set_bit(MP_ISA_BUS, mp_bus_not_pci);
	pr_debug("Bus #%d is ISA (nIRQs: %d)\n", MP_ISA_BUS, nr_legacy_irqs());

	/*
	 * Use the शेष configuration क्रम the IRQs 0-15.  Unless
	 * overridden by (MADT) पूर्णांकerrupt source override entries.
	 */
	क्रम (i = 0; i < nr_legacy_irqs(); i++) अणु
		पूर्णांक ioapic, pin;
		अचिन्हित पूर्णांक dstapic;
		पूर्णांक idx;
		u32 gsi;

		/* Locate the gsi that irq i maps to. */
		अगर (acpi_isa_irq_to_gsi(i, &gsi))
			जारी;

		/*
		 * Locate the IOAPIC that manages the ISA IRQ.
		 */
		ioapic = mp_find_ioapic(gsi);
		अगर (ioapic < 0)
			जारी;
		pin = mp_find_ioapic_pin(ioapic, gsi);
		dstapic = mpc_ioapic_id(ioapic);

		क्रम (idx = 0; idx < mp_irq_entries; idx++) अणु
			काष्ठा mpc_पूर्णांकsrc *irq = mp_irqs + idx;

			/* Do we alपढ़ोy have a mapping क्रम this ISA IRQ? */
			अगर (irq->srcbus == MP_ISA_BUS && irq->srcbusirq == i)
				अवरोध;

			/* Do we alपढ़ोy have a mapping क्रम this IOAPIC pin */
			अगर (irq->dstapic == dstapic && irq->dstirq == pin)
				अवरोध;
		पूर्ण

		अगर (idx != mp_irq_entries) अणु
			prपूर्णांकk(KERN_DEBUG "ACPI: IRQ%d used by override.\n", i);
			जारी;	/* IRQ alपढ़ोy used */
		पूर्ण

		mp_irq.type = MP_INTSRC;
		mp_irq.irqflag = 0;	/* Conक्रमming */
		mp_irq.srcbus = MP_ISA_BUS;
		mp_irq.dstapic = dstapic;
		mp_irq.irqtype = mp_INT;
		mp_irq.srcbusirq = i; /* Identity mapped */
		mp_irq.dstirq = pin;

		mp_save_irq(&mp_irq);
	पूर्ण
पूर्ण

/*
 * Parse IOAPIC related entries in MADT
 * वापसs 0 on success, < 0 on error
 */
अटल पूर्णांक __init acpi_parse_madt_ioapic_entries(व्योम)
अणु
	पूर्णांक count;

	/*
	 * ACPI पूर्णांकerpreter is required to complete पूर्णांकerrupt setup,
	 * so अगर it is off, करोn't क्रमागतerate the io-apics with ACPI.
	 * If MPS is present, it will handle them,
	 * otherwise the प्रणाली will stay in PIC mode
	 */
	अगर (acpi_disabled || acpi_noirq)
		वापस -ENODEV;

	अगर (!boot_cpu_has(X86_FEATURE_APIC))
		वापस -ENODEV;

	/*
	 * अगर "noapic" boot option, करोn't look क्रम IO-APICs
	 */
	अगर (skip_ioapic_setup) अणु
		prपूर्णांकk(KERN_INFO PREFIX "Skipping IOAPIC probe "
		       "due to 'noapic' option.\n");
		वापस -ENODEV;
	पूर्ण

	count = acpi_table_parse_madt(ACPI_MADT_TYPE_IO_APIC, acpi_parse_ioapic,
				      MAX_IO_APICS);
	अगर (!count) अणु
		prपूर्णांकk(KERN_ERR PREFIX "No IOAPIC entries present\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (count < 0) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Error parsing IOAPIC entry\n");
		वापस count;
	पूर्ण

	count = acpi_table_parse_madt(ACPI_MADT_TYPE_INTERRUPT_OVERRIDE,
				      acpi_parse_पूर्णांक_src_ovr, nr_irqs);
	अगर (count < 0) अणु
		prपूर्णांकk(KERN_ERR PREFIX
		       "Error parsing interrupt source overrides entry\n");
		/* TBD: Cleanup to allow fallback to MPS */
		वापस count;
	पूर्ण

	/*
	 * If BIOS did not supply an INT_SRC_OVR क्रम the SCI
	 * pretend we got one so we can set the SCI flags.
	 * But ignore setting up SCI on hardware reduced platक्रमms.
	 */
	अगर (acpi_sci_override_gsi == INVALID_ACPI_IRQ && !acpi_gbl_reduced_hardware)
		acpi_sci_ioapic_setup(acpi_gbl_FADT.sci_पूर्णांकerrupt, 0, 0,
				      acpi_gbl_FADT.sci_पूर्णांकerrupt);

	/* Fill in identity legacy mappings where no override */
	mp_config_acpi_legacy_irqs();

	count = acpi_table_parse_madt(ACPI_MADT_TYPE_NMI_SOURCE,
				      acpi_parse_nmi_src, nr_irqs);
	अगर (count < 0) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Error parsing NMI SRC entry\n");
		/* TBD: Cleanup to allow fallback to MPS */
		वापस count;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_parse_madt_ioapic_entries(व्योम)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर	/* !CONFIG_X86_IO_APIC */

अटल व्योम __init early_acpi_process_madt(व्योम)
अणु
#अगर_घोषित CONFIG_X86_LOCAL_APIC
	पूर्णांक error;

	अगर (!acpi_table_parse(ACPI_SIG_MADT, acpi_parse_madt)) अणु

		/*
		 * Parse MADT LAPIC entries
		 */
		error = early_acpi_parse_madt_lapic_addr_ovr();
		अगर (!error) अणु
			acpi_lapic = 1;
			smp_found_config = 1;
		पूर्ण
		अगर (error == -EINVAL) अणु
			/*
			 * Dell Precision Workstation 410, 610 come here.
			 */
			prपूर्णांकk(KERN_ERR PREFIX
			       "Invalid BIOS MADT, disabling ACPI\n");
			disable_acpi();
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init acpi_process_madt(व्योम)
अणु
#अगर_घोषित CONFIG_X86_LOCAL_APIC
	पूर्णांक error;

	अगर (!acpi_table_parse(ACPI_SIG_MADT, acpi_parse_madt)) अणु

		/*
		 * Parse MADT LAPIC entries
		 */
		error = acpi_parse_madt_lapic_entries();
		अगर (!error) अणु
			acpi_lapic = 1;

			/*
			 * Parse MADT IO-APIC entries
			 */
			mutex_lock(&acpi_ioapic_lock);
			error = acpi_parse_madt_ioapic_entries();
			mutex_unlock(&acpi_ioapic_lock);
			अगर (!error) अणु
				acpi_set_irq_model_ioapic();

				smp_found_config = 1;
			पूर्ण
		पूर्ण
		अगर (error == -EINVAL) अणु
			/*
			 * Dell Precision Workstation 410, 610 come here.
			 */
			prपूर्णांकk(KERN_ERR PREFIX
			       "Invalid BIOS MADT, disabling ACPI\n");
			disable_acpi();
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
 		 * ACPI found no MADT, and so ACPI wants UP PIC mode.
 		 * In the event an MPS table was found, क्रमget it.
 		 * Boot with "acpi=off" to use MPS on such a प्रणाली.
 		 */
		अगर (smp_found_config) अणु
			prपूर्णांकk(KERN_WARNING PREFIX
				"No APIC-table, disabling MPS\n");
			smp_found_config = 0;
		पूर्ण
	पूर्ण

	/*
	 * ACPI supports both logical (e.g. Hyper-Thपढ़ोing) and physical
	 * processors, where MPS only supports physical.
	 */
	अगर (acpi_lapic && acpi_ioapic)
		prपूर्णांकk(KERN_INFO "Using ACPI (MADT) for SMP configuration "
		       "information\n");
	अन्यथा अगर (acpi_lapic)
		prपूर्णांकk(KERN_INFO "Using ACPI for processor (LAPIC) "
		       "configuration information\n");
#पूर्ण_अगर
	वापस;
पूर्ण

अटल पूर्णांक __init disable_acpi_irq(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (!acpi_क्रमce) अणु
		prपूर्णांकk(KERN_NOTICE "%s detected: force use of acpi=noirq\n",
		       d->ident);
		acpi_noirq_set();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init disable_acpi_pci(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (!acpi_क्रमce) अणु
		prपूर्णांकk(KERN_NOTICE "%s detected: force use of pci=noacpi\n",
		       d->ident);
		acpi_disable_pci();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init dmi_disable_acpi(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (!acpi_क्रमce) अणु
		prपूर्णांकk(KERN_NOTICE "%s detected: acpi off\n", d->ident);
		disable_acpi();
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_NOTICE
		       "Warning: DMI blacklist says broken, but acpi forced\n");
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Force ignoring BIOS IRQ0 override
 */
अटल पूर्णांक __init dmi_ignore_irq0_समयr_override(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (!acpi_skip_समयr_override) अणु
		pr_notice("%s detected: Ignoring BIOS IRQ0 override\n",
			d->ident);
		acpi_skip_समयr_override = 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ACPI offers an alternative platक्रमm पूर्णांकerface model that हटाओs
 * ACPI hardware requirements क्रम platक्रमms that करो not implement
 * the PC Architecture.
 *
 * We initialize the Hardware-reduced ACPI model here:
 */
व्योम __init acpi_generic_reduced_hw_init(व्योम)
अणु
	/*
	 * Override x86_init functions and bypass legacy PIC in
	 * hardware reduced ACPI mode.
	 */
	x86_init.समयrs.समयr_init	= x86_init_noop;
	x86_init.irqs.pre_vector_init	= x86_init_noop;
	legacy_pic			= &null_legacy_pic;
पूर्ण

अटल व्योम __init acpi_reduced_hw_init(व्योम)
अणु
	अगर (acpi_gbl_reduced_hardware)
		x86_init.acpi.reduced_hw_early_init();
पूर्ण

/*
 * If your प्रणाली is blacklisted here, but you find that acpi=क्रमce
 * works क्रम you, please contact linux-acpi@vger.kernel.org
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id acpi_dmi_table[] __initस्थिर = अणु
	/*
	 * Boxes that need ACPI disabled
	 */
	अणु
	 .callback = dmi_disable_acpi,
	 .ident = "IBM Thinkpad",
	 .matches = अणु
		     DMI_MATCH(DMI_BOARD_VENDOR, "IBM"),
		     DMI_MATCH(DMI_BOARD_NAME, "2629H1G"),
		     पूर्ण,
	 पूर्ण,

	/*
	 * Boxes that need ACPI PCI IRQ routing disabled
	 */
	अणु
	 .callback = disable_acpi_irq,
	 .ident = "ASUS A7V",
	 .matches = अणु
		     DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC"),
		     DMI_MATCH(DMI_BOARD_NAME, "<A7V>"),
		     /* newer BIOS, Revision 1011, करोes work */
		     DMI_MATCH(DMI_BIOS_VERSION,
			       "ASUS A7V ACPI BIOS Revision 1007"),
		     पूर्ण,
	 पूर्ण,
	अणु
		/*
		 * Latest BIOS क्रम IBM 600E (1.16) has bad pcinum
		 * क्रम LPC bridge, which is needed क्रम the PCI
		 * पूर्णांकerrupt links to work. DSDT fix is in bug 5966.
		 * 2645, 2646 model numbers are shared with 600/600E/600X
		 */
	 .callback = disable_acpi_irq,
	 .ident = "IBM Thinkpad 600 Series 2645",
	 .matches = अणु
		     DMI_MATCH(DMI_BOARD_VENDOR, "IBM"),
		     DMI_MATCH(DMI_BOARD_NAME, "2645"),
		     पूर्ण,
	 पूर्ण,
	अणु
	 .callback = disable_acpi_irq,
	 .ident = "IBM Thinkpad 600 Series 2646",
	 .matches = अणु
		     DMI_MATCH(DMI_BOARD_VENDOR, "IBM"),
		     DMI_MATCH(DMI_BOARD_NAME, "2646"),
		     पूर्ण,
	 पूर्ण,
	/*
	 * Boxes that need ACPI PCI IRQ routing and PCI scan disabled
	 */
	अणु			/* _BBN 0 bug */
	 .callback = disable_acpi_pci,
	 .ident = "ASUS PR-DLS",
	 .matches = अणु
		     DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
		     DMI_MATCH(DMI_BOARD_NAME, "PR-DLS"),
		     DMI_MATCH(DMI_BIOS_VERSION,
			       "ASUS PR-DLS ACPI BIOS Revision 1010"),
		     DMI_MATCH(DMI_BIOS_DATE, "03/21/2003")
		     पूर्ण,
	 पूर्ण,
	अणु
	 .callback = disable_acpi_pci,
	 .ident = "Acer TravelMate 36x Laptop",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 360"),
		     पूर्ण,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

/* second table क्रम DMI checks that should run after early-quirks */
अटल स्थिर काष्ठा dmi_प्रणाली_id acpi_dmi_table_late[] __initस्थिर = अणु
	/*
	 * HP laptops which use a DSDT reporting as HP/SB400/10000,
	 * which includes some code which overrides all temperature
	 * trip poपूर्णांकs to 16C अगर the INTIN2 input of the I/O APIC
	 * is enabled.  This input is incorrectly designated the
	 * ISA IRQ 0 via an पूर्णांकerrupt source override even though
	 * it is wired to the output of the master 8259A and INTIN0
	 * is not connected at all.  Force ignoring BIOS IRQ0
	 * override in that हालs.
	 */
	अणु
	 .callback = dmi_ignore_irq0_समयr_override,
	 .ident = "HP nx6115 laptop",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq nx6115"),
		     पूर्ण,
	 पूर्ण,
	अणु
	 .callback = dmi_ignore_irq0_समयr_override,
	 .ident = "HP NX6125 laptop",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq nx6125"),
		     पूर्ण,
	 पूर्ण,
	अणु
	 .callback = dmi_ignore_irq0_समयr_override,
	 .ident = "HP NX6325 laptop",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq nx6325"),
		     पूर्ण,
	 पूर्ण,
	अणु
	 .callback = dmi_ignore_irq0_समयr_override,
	 .ident = "HP 6715b laptop",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq 6715b"),
		     पूर्ण,
	 पूर्ण,
	अणु
	 .callback = dmi_ignore_irq0_समयr_override,
	 .ident = "FUJITSU SIEMENS",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "AMILO PRO V2030"),
		     पूर्ण,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * acpi_boot_table_init() and acpi_boot_init()
 *  called from setup_arch(), always.
 *	1. checksums all tables
 *	2. क्रमागतerates lapics
 *	3. क्रमागतerates io-apics
 *
 * acpi_table_init() is separate to allow पढ़ोing SRAT without
 * other side effects.
 *
 * side effects of acpi_boot_init:
 *	acpi_lapic = 1 अगर LAPIC found
 *	acpi_ioapic = 1 अगर IOAPIC found
 *	अगर (acpi_lapic && acpi_ioapic) smp_found_config = 1;
 *	अगर acpi_blacklisted() acpi_disabled = 1;
 *	acpi_irq_model=...
 *	...
 */

व्योम __init acpi_boot_table_init(व्योम)
अणु
	dmi_check_प्रणाली(acpi_dmi_table);

	/*
	 * If acpi_disabled, bail out
	 */
	अगर (acpi_disabled)
		वापस;

	/*
	 * Initialize the ACPI boot-समय table parser.
	 */
	अगर (acpi_locate_initial_tables())
		disable_acpi();
	अन्यथा
		acpi_reserve_initial_tables();
पूर्ण

पूर्णांक __init early_acpi_boot_init(व्योम)
अणु
	अगर (acpi_disabled)
		वापस 1;

	acpi_table_init_complete();

	acpi_table_parse(ACPI_SIG_BOOT, acpi_parse_sbf);

	/*
	 * blacklist may disable ACPI entirely
	 */
	अगर (acpi_blacklisted()) अणु
		अगर (acpi_क्रमce) अणु
			prपूर्णांकk(KERN_WARNING PREFIX "acpi=force override\n");
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING PREFIX "Disabling ACPI support\n");
			disable_acpi();
			वापस 1;
		पूर्ण
	पूर्ण

	/*
	 * Process the Multiple APIC Description Table (MADT), अगर present
	 */
	early_acpi_process_madt();

	/*
	 * Hardware-reduced ACPI mode initialization:
	 */
	acpi_reduced_hw_init();

	वापस 0;
पूर्ण

पूर्णांक __init acpi_boot_init(व्योम)
अणु
	/* those are executed after early-quirks are executed */
	dmi_check_प्रणाली(acpi_dmi_table_late);

	/*
	 * If acpi_disabled, bail out
	 */
	अगर (acpi_disabled)
		वापस 1;

	acpi_table_parse(ACPI_SIG_BOOT, acpi_parse_sbf);

	/*
	 * set sci_पूर्णांक and PM समयr address
	 */
	acpi_table_parse(ACPI_SIG_FADT, acpi_parse_fadt);

	/*
	 * Process the Multiple APIC Description Table (MADT), अगर present
	 */
	acpi_process_madt();

	acpi_table_parse(ACPI_SIG_HPET, acpi_parse_hpet);
	अगर (IS_ENABLED(CONFIG_ACPI_BGRT) && !acpi_nobgrt)
		acpi_table_parse(ACPI_SIG_BGRT, acpi_parse_bgrt);

	अगर (!acpi_noirq)
		x86_init.pci.init = pci_acpi_init;

	/* Do not enable ACPI SPCR console by शेष */
	acpi_parse_spcr(earlycon_acpi_spcr_enable, false);
	वापस 0;
पूर्ण

अटल पूर्णांक __init parse_acpi(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	/* "acpi=off" disables both ACPI table parsing and पूर्णांकerpreter */
	अगर (म_भेद(arg, "off") == 0) अणु
		disable_acpi();
	पूर्ण
	/* acpi=क्रमce to over-ride black-list */
	अन्यथा अगर (म_भेद(arg, "force") == 0) अणु
		acpi_क्रमce = 1;
		acpi_disabled = 0;
	पूर्ण
	/* acpi=strict disables out-of-spec workarounds */
	अन्यथा अगर (म_भेद(arg, "strict") == 0) अणु
		acpi_strict = 1;
	पूर्ण
	/* acpi=rsdt use RSDT instead of XSDT */
	अन्यथा अगर (म_भेद(arg, "rsdt") == 0) अणु
		acpi_gbl_करो_not_use_xsdt = TRUE;
	पूर्ण
	/* "acpi=noirq" disables ACPI पूर्णांकerrupt routing */
	अन्यथा अगर (म_भेद(arg, "noirq") == 0) अणु
		acpi_noirq_set();
	पूर्ण
	/* "acpi=copy_dsdt" copies DSDT */
	अन्यथा अगर (म_भेद(arg, "copy_dsdt") == 0) अणु
		acpi_gbl_copy_dsdt_locally = 1;
	पूर्ण
	/* "acpi=nocmcff" disables FF mode क्रम corrected errors */
	अन्यथा अगर (म_भेद(arg, "nocmcff") == 0) अणु
		acpi_disable_cmcff = 1;
	पूर्ण अन्यथा अणु
		/* Core will prपूर्णांकk when we वापस error. */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
early_param("acpi", parse_acpi);

अटल पूर्णांक __init parse_acpi_bgrt(अक्षर *arg)
अणु
	acpi_nobgrt = true;
	वापस 0;
पूर्ण
early_param("bgrt_disable", parse_acpi_bgrt);

/* FIXME: Using pci= क्रम an ACPI parameter is a travesty. */
अटल पूर्णांक __init parse_pci(अक्षर *arg)
अणु
	अगर (arg && म_भेद(arg, "noacpi") == 0)
		acpi_disable_pci();
	वापस 0;
पूर्ण
early_param("pci", parse_pci);

पूर्णांक __init acpi_mps_check(व्योम)
अणु
#अगर defined(CONFIG_X86_LOCAL_APIC) && !defined(CONFIG_X86_MPPARSE)
/* mptable code is not built-in*/
	अगर (acpi_disabled || acpi_noirq) अणु
		prपूर्णांकk(KERN_WARNING "MPS support code is not built-in.\n"
		       "Using acpi=off or acpi=noirq or pci=noacpi "
		       "may have problem\n");
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_IO_APIC
अटल पूर्णांक __init parse_acpi_skip_समयr_override(अक्षर *arg)
अणु
	acpi_skip_समयr_override = 1;
	वापस 0;
पूर्ण
early_param("acpi_skip_timer_override", parse_acpi_skip_समयr_override);

अटल पूर्णांक __init parse_acpi_use_समयr_override(अक्षर *arg)
अणु
	acpi_use_समयr_override = 1;
	वापस 0;
पूर्ण
early_param("acpi_use_timer_override", parse_acpi_use_समयr_override);
#पूर्ण_अगर /* CONFIG_X86_IO_APIC */

अटल पूर्णांक __init setup_acpi_sci(अक्षर *s)
अणु
	अगर (!s)
		वापस -EINVAL;
	अगर (!म_भेद(s, "edge"))
		acpi_sci_flags =  ACPI_MADT_TRIGGER_EDGE |
			(acpi_sci_flags & ~ACPI_MADT_TRIGGER_MASK);
	अन्यथा अगर (!म_भेद(s, "level"))
		acpi_sci_flags = ACPI_MADT_TRIGGER_LEVEL |
			(acpi_sci_flags & ~ACPI_MADT_TRIGGER_MASK);
	अन्यथा अगर (!म_भेद(s, "high"))
		acpi_sci_flags = ACPI_MADT_POLARITY_ACTIVE_HIGH |
			(acpi_sci_flags & ~ACPI_MADT_POLARITY_MASK);
	अन्यथा अगर (!म_भेद(s, "low"))
		acpi_sci_flags = ACPI_MADT_POLARITY_ACTIVE_LOW |
			(acpi_sci_flags & ~ACPI_MADT_POLARITY_MASK);
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण
early_param("acpi_sci", setup_acpi_sci);

पूर्णांक __acpi_acquire_global_lock(अचिन्हित पूर्णांक *lock)
अणु
	अचिन्हित पूर्णांक old, new, val;
	करो अणु
		old = *lock;
		new = (((old & ~0x3) + 2) + ((old >> 1) & 0x1));
		val = cmpxchg(lock, old, new);
	पूर्ण जबतक (unlikely (val != old));
	वापस ((new & 0x3) < 3) ? -1 : 0;
पूर्ण

पूर्णांक __acpi_release_global_lock(अचिन्हित पूर्णांक *lock)
अणु
	अचिन्हित पूर्णांक old, new, val;
	करो अणु
		old = *lock;
		new = old & ~0x3;
		val = cmpxchg(lock, old, new);
	पूर्ण जबतक (unlikely (val != old));
	वापस old & 0x1;
पूर्ण

व्योम __init arch_reserve_mem_area(acpi_physical_address addr, माप_प्रकार size)
अणु
	e820__range_add(addr, size, E820_TYPE_ACPI);
	e820__update_table_prपूर्णांक();
पूर्ण

व्योम x86_शेष_set_root_poपूर्णांकer(u64 addr)
अणु
	boot_params.acpi_rsdp_addr = addr;
पूर्ण

u64 x86_शेष_get_root_poपूर्णांकer(व्योम)
अणु
	वापस boot_params.acpi_rsdp_addr;
पूर्ण
