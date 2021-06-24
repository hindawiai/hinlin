<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005 Intel Corporation
 * Copyright (C) 2009 Hewlett-Packard Development Company, L.P.
 *
 *	Alex Chiang <achiang@hp.com>
 *	- Unअगरied x86/ia64 implementations
 *
 * I/O APIC hotplug support
 *	Yinghai Lu <yinghai@kernel.org>
 *	Jiang Liu <jiang.liu@पूर्णांकel.com>
 */
#समावेश <linux/export.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/processor.h>

अटल काष्ठा acpi_table_madt *get_madt_table(व्योम)
अणु
	अटल काष्ठा acpi_table_madt *madt;
	अटल पूर्णांक पढ़ो_madt;

	अगर (!पढ़ो_madt) अणु
		अगर (ACPI_FAILURE(acpi_get_table(ACPI_SIG_MADT, 0,
					(काष्ठा acpi_table_header **)&madt)))
			madt = शून्य;
		पढ़ो_madt++;
	पूर्ण

	वापस madt;
पूर्ण

अटल पूर्णांक map_lapic_id(काष्ठा acpi_subtable_header *entry,
		 u32 acpi_id, phys_cpuid_t *apic_id)
अणु
	काष्ठा acpi_madt_local_apic *lapic =
		container_of(entry, काष्ठा acpi_madt_local_apic, header);

	अगर (!(lapic->lapic_flags & ACPI_MADT_ENABLED))
		वापस -ENODEV;

	अगर (lapic->processor_id != acpi_id)
		वापस -EINVAL;

	*apic_id = lapic->id;
	वापस 0;
पूर्ण

अटल पूर्णांक map_x2apic_id(काष्ठा acpi_subtable_header *entry,
		पूर्णांक device_declaration, u32 acpi_id, phys_cpuid_t *apic_id)
अणु
	काष्ठा acpi_madt_local_x2apic *apic =
		container_of(entry, काष्ठा acpi_madt_local_x2apic, header);

	अगर (!(apic->lapic_flags & ACPI_MADT_ENABLED))
		वापस -ENODEV;

	अगर (device_declaration && (apic->uid == acpi_id)) अणु
		*apic_id = apic->local_apic_id;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक map_lsapic_id(काष्ठा acpi_subtable_header *entry,
		पूर्णांक device_declaration, u32 acpi_id, phys_cpuid_t *apic_id)
अणु
	काष्ठा acpi_madt_local_sapic *lsapic =
		container_of(entry, काष्ठा acpi_madt_local_sapic, header);

	अगर (!(lsapic->lapic_flags & ACPI_MADT_ENABLED))
		वापस -ENODEV;

	अगर (device_declaration) अणु
		अगर ((entry->length < 16) || (lsapic->uid != acpi_id))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (lsapic->processor_id != acpi_id)
		वापस -EINVAL;

	*apic_id = (lsapic->id << 8) | lsapic->eid;
	वापस 0;
पूर्ण

/*
 * Retrieve the ARM CPU physical identअगरier (MPIDR)
 */
अटल पूर्णांक map_gicc_mpidr(काष्ठा acpi_subtable_header *entry,
		पूर्णांक device_declaration, u32 acpi_id, phys_cpuid_t *mpidr)
अणु
	काष्ठा acpi_madt_generic_पूर्णांकerrupt *gicc =
	    container_of(entry, काष्ठा acpi_madt_generic_पूर्णांकerrupt, header);

	अगर (!(gicc->flags & ACPI_MADT_ENABLED))
		वापस -ENODEV;

	/* device_declaration means Device object in DSDT, in the
	 * GIC पूर्णांकerrupt model, logical processors are required to
	 * have a Processor Device object in the DSDT, so we should
	 * check device_declaration here
	 */
	अगर (device_declaration && (gicc->uid == acpi_id)) अणु
		*mpidr = gicc->arm_mpidr;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल phys_cpuid_t map_madt_entry(काष्ठा acpi_table_madt *madt,
				   पूर्णांक type, u32 acpi_id)
अणु
	अचिन्हित दीर्घ madt_end, entry;
	phys_cpuid_t phys_id = PHYS_CPUID_INVALID;	/* CPU hardware ID */

	अगर (!madt)
		वापस phys_id;

	entry = (अचिन्हित दीर्घ)madt;
	madt_end = entry + madt->header.length;

	/* Parse all entries looking क्रम a match. */

	entry += माप(काष्ठा acpi_table_madt);
	जबतक (entry + माप(काष्ठा acpi_subtable_header) < madt_end) अणु
		काष्ठा acpi_subtable_header *header =
			(काष्ठा acpi_subtable_header *)entry;
		अगर (header->type == ACPI_MADT_TYPE_LOCAL_APIC) अणु
			अगर (!map_lapic_id(header, acpi_id, &phys_id))
				अवरोध;
		पूर्ण अन्यथा अगर (header->type == ACPI_MADT_TYPE_LOCAL_X2APIC) अणु
			अगर (!map_x2apic_id(header, type, acpi_id, &phys_id))
				अवरोध;
		पूर्ण अन्यथा अगर (header->type == ACPI_MADT_TYPE_LOCAL_SAPIC) अणु
			अगर (!map_lsapic_id(header, type, acpi_id, &phys_id))
				अवरोध;
		पूर्ण अन्यथा अगर (header->type == ACPI_MADT_TYPE_GENERIC_INTERRUPT) अणु
			अगर (!map_gicc_mpidr(header, type, acpi_id, &phys_id))
				अवरोध;
		पूर्ण
		entry += header->length;
	पूर्ण
	वापस phys_id;
पूर्ण

phys_cpuid_t __init acpi_map_madt_entry(u32 acpi_id)
अणु
	काष्ठा acpi_table_madt *madt = शून्य;
	phys_cpuid_t rv;

	acpi_get_table(ACPI_SIG_MADT, 0,
		       (काष्ठा acpi_table_header **)&madt);
	अगर (!madt)
		वापस PHYS_CPUID_INVALID;

	rv = map_madt_entry(madt, 1, acpi_id);

	acpi_put_table((काष्ठा acpi_table_header *)madt);

	वापस rv;
पूर्ण

अटल phys_cpuid_t map_mat_entry(acpi_handle handle, पूर्णांक type, u32 acpi_id)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	काष्ठा acpi_subtable_header *header;
	phys_cpuid_t phys_id = PHYS_CPUID_INVALID;

	अगर (ACPI_FAILURE(acpi_evaluate_object(handle, "_MAT", शून्य, &buffer)))
		जाओ निकास;

	अगर (!buffer.length || !buffer.poपूर्णांकer)
		जाओ निकास;

	obj = buffer.poपूर्णांकer;
	अगर (obj->type != ACPI_TYPE_BUFFER ||
	    obj->buffer.length < माप(काष्ठा acpi_subtable_header)) अणु
		जाओ निकास;
	पूर्ण

	header = (काष्ठा acpi_subtable_header *)obj->buffer.poपूर्णांकer;
	अगर (header->type == ACPI_MADT_TYPE_LOCAL_APIC)
		map_lapic_id(header, acpi_id, &phys_id);
	अन्यथा अगर (header->type == ACPI_MADT_TYPE_LOCAL_SAPIC)
		map_lsapic_id(header, type, acpi_id, &phys_id);
	अन्यथा अगर (header->type == ACPI_MADT_TYPE_LOCAL_X2APIC)
		map_x2apic_id(header, type, acpi_id, &phys_id);
	अन्यथा अगर (header->type == ACPI_MADT_TYPE_GENERIC_INTERRUPT)
		map_gicc_mpidr(header, type, acpi_id, &phys_id);

निकास:
	kमुक्त(buffer.poपूर्णांकer);
	वापस phys_id;
पूर्ण

phys_cpuid_t acpi_get_phys_id(acpi_handle handle, पूर्णांक type, u32 acpi_id)
अणु
	phys_cpuid_t phys_id;

	phys_id = map_mat_entry(handle, type, acpi_id);
	अगर (invalid_phys_cpuid(phys_id))
		phys_id = map_madt_entry(get_madt_table(), type, acpi_id);

	वापस phys_id;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_get_phys_id);

पूर्णांक acpi_map_cpuid(phys_cpuid_t phys_id, u32 acpi_id)
अणु
#अगर_घोषित CONFIG_SMP
	पूर्णांक i;
#पूर्ण_अगर

	अगर (invalid_phys_cpuid(phys_id)) अणु
		/*
		 * On UP processor, there is no _MAT or MADT table.
		 * So above phys_id is always set to PHYS_CPUID_INVALID.
		 *
		 * BIOS may define multiple CPU handles even क्रम UP processor.
		 * For example,
		 *
		 * Scope (_PR)
		 * अणु
		 *     Processor (CPU0, 0x00, 0x00000410, 0x06) अणुपूर्ण
		 *     Processor (CPU1, 0x01, 0x00000410, 0x06) अणुपूर्ण
		 *     Processor (CPU2, 0x02, 0x00000410, 0x06) अणुपूर्ण
		 *     Processor (CPU3, 0x03, 0x00000410, 0x06) अणुपूर्ण
		 * पूर्ण
		 *
		 * Ignores phys_id and always वापसs 0 क्रम the processor
		 * handle with acpi id 0 अगर nr_cpu_ids is 1.
		 * This should be the हाल अगर SMP tables are not found.
		 * Return -EINVAL क्रम other CPU's handle.
		 */
		अगर (nr_cpu_ids <= 1 && acpi_id == 0)
			वापस acpi_id;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_SMP
	क्रम_each_possible_cpu(i) अणु
		अगर (cpu_physical_id(i) == phys_id)
			वापस i;
	पूर्ण
#अन्यथा
	/* In UP kernel, only processor 0 is valid */
	अगर (phys_id == 0)
		वापस phys_id;
#पूर्ण_अगर
	वापस -ENODEV;
पूर्ण

पूर्णांक acpi_get_cpuid(acpi_handle handle, पूर्णांक type, u32 acpi_id)
अणु
	phys_cpuid_t phys_id;

	phys_id = acpi_get_phys_id(handle, type, acpi_id);

	वापस acpi_map_cpuid(phys_id, acpi_id);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_get_cpuid);

#अगर_घोषित CONFIG_ACPI_HOTPLUG_IOAPIC
अटल पूर्णांक get_ioapic_id(काष्ठा acpi_subtable_header *entry, u32 gsi_base,
			 u64 *phys_addr, पूर्णांक *ioapic_id)
अणु
	काष्ठा acpi_madt_io_apic *ioapic = (काष्ठा acpi_madt_io_apic *)entry;

	अगर (ioapic->global_irq_base != gsi_base)
		वापस 0;

	*phys_addr = ioapic->address;
	*ioapic_id = ioapic->id;
	वापस 1;
पूर्ण

अटल पूर्णांक parse_madt_ioapic_entry(u32 gsi_base, u64 *phys_addr)
अणु
	काष्ठा acpi_subtable_header *hdr;
	अचिन्हित दीर्घ madt_end, entry;
	काष्ठा acpi_table_madt *madt;
	पूर्णांक apic_id = -1;

	madt = get_madt_table();
	अगर (!madt)
		वापस apic_id;

	entry = (अचिन्हित दीर्घ)madt;
	madt_end = entry + madt->header.length;

	/* Parse all entries looking क्रम a match. */
	entry += माप(काष्ठा acpi_table_madt);
	जबतक (entry + माप(काष्ठा acpi_subtable_header) < madt_end) अणु
		hdr = (काष्ठा acpi_subtable_header *)entry;
		अगर (hdr->type == ACPI_MADT_TYPE_IO_APIC &&
		    get_ioapic_id(hdr, gsi_base, phys_addr, &apic_id))
			अवरोध;
		अन्यथा
			entry += hdr->length;
	पूर्ण

	वापस apic_id;
पूर्ण

अटल पूर्णांक parse_mat_ioapic_entry(acpi_handle handle, u32 gsi_base,
				  u64 *phys_addr)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_subtable_header *header;
	जोड़ acpi_object *obj;
	पूर्णांक apic_id = -1;

	अगर (ACPI_FAILURE(acpi_evaluate_object(handle, "_MAT", शून्य, &buffer)))
		जाओ निकास;

	अगर (!buffer.length || !buffer.poपूर्णांकer)
		जाओ निकास;

	obj = buffer.poपूर्णांकer;
	अगर (obj->type != ACPI_TYPE_BUFFER ||
	    obj->buffer.length < माप(काष्ठा acpi_subtable_header))
		जाओ निकास;

	header = (काष्ठा acpi_subtable_header *)obj->buffer.poपूर्णांकer;
	अगर (header->type == ACPI_MADT_TYPE_IO_APIC)
		get_ioapic_id(header, gsi_base, phys_addr, &apic_id);

निकास:
	kमुक्त(buffer.poपूर्णांकer);
	वापस apic_id;
पूर्ण

/**
 * acpi_get_ioapic_id - Get IOAPIC ID and physical address matching @gsi_base
 * @handle:	ACPI object क्रम IOAPIC device
 * @gsi_base:	GSI base to match with
 * @phys_addr:	Poपूर्णांकer to store physical address of matching IOAPIC record
 *
 * Walk resources वापसed by ACPI_MAT method, then ACPI MADT table, to search
 * क्रम an ACPI IOAPIC record matching @gsi_base.
 * Return IOAPIC id and store physical address in @phys_addr अगर found a match,
 * otherwise वापस <0.
 */
पूर्णांक acpi_get_ioapic_id(acpi_handle handle, u32 gsi_base, u64 *phys_addr)
अणु
	पूर्णांक apic_id;

	apic_id = parse_mat_ioapic_entry(handle, gsi_base, phys_addr);
	अगर (apic_id == -1)
		apic_id = parse_madt_ioapic_entry(gsi_base, phys_addr);

	वापस apic_id;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_HOTPLUG_IOAPIC */
