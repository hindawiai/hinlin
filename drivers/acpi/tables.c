<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi_tables.c - ACPI Boot-Time Table Parsing
 *
 *  Copyright (C) 2001 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

/* Uncomment next line to get verbose prपूर्णांकout */
/* #घोषणा DEBUG */
#घोषणा pr_fmt(fmt) "ACPI: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/irq.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/acpi.h>
#समावेश <linux/memblock.h>
#समावेश <linux/earlycpपन.स>
#समावेश <linux/initrd.h>
#समावेश <linux/security.h>
#समावेश "internal.h"

#अगर_घोषित CONFIG_ACPI_CUSTOM_DSDT
#समावेश CONFIG_ACPI_CUSTOM_DSDT_खाता
#पूर्ण_अगर

#घोषणा ACPI_MAX_TABLES		128

अटल अक्षर *mps_पूर्णांकi_flags_polarity[] = अणु "dfl", "high", "res", "low" पूर्ण;
अटल अक्षर *mps_पूर्णांकi_flags_trigger[] = अणु "dfl", "edge", "res", "level" पूर्ण;

अटल काष्ठा acpi_table_desc initial_tables[ACPI_MAX_TABLES] __initdata;

अटल पूर्णांक acpi_apic_instance __initdata;

क्रमागत acpi_subtable_type अणु
	ACPI_SUBTABLE_COMMON,
	ACPI_SUBTABLE_HMAT,
पूर्ण;

काष्ठा acpi_subtable_entry अणु
	जोड़ acpi_subtable_headers *hdr;
	क्रमागत acpi_subtable_type type;
पूर्ण;

/*
 * Disable table checksum verअगरication क्रम the early stage due to the size
 * limitation of the current x86 early mapping implementation.
 */
अटल bool acpi_verअगरy_table_checksum __initdata = false;

व्योम acpi_table_prपूर्णांक_madt_entry(काष्ठा acpi_subtable_header *header)
अणु
	अगर (!header)
		वापस;

	चयन (header->type) अणु

	हाल ACPI_MADT_TYPE_LOCAL_APIC:
		अणु
			काष्ठा acpi_madt_local_apic *p =
			    (काष्ठा acpi_madt_local_apic *)header;
			pr_debug("LAPIC (acpi_id[0x%02x] lapic_id[0x%02x] %s)\n",
				 p->processor_id, p->id,
				 (p->lapic_flags & ACPI_MADT_ENABLED) ? "enabled" : "disabled");
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_LOCAL_X2APIC:
		अणु
			काष्ठा acpi_madt_local_x2apic *p =
			    (काष्ठा acpi_madt_local_x2apic *)header;
			pr_debug("X2APIC (apic_id[0x%02x] uid[0x%02x] %s)\n",
				 p->local_apic_id, p->uid,
				 (p->lapic_flags & ACPI_MADT_ENABLED) ? "enabled" : "disabled");
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_IO_APIC:
		अणु
			काष्ठा acpi_madt_io_apic *p =
			    (काष्ठा acpi_madt_io_apic *)header;
			pr_debug("IOAPIC (id[0x%02x] address[0x%08x] gsi_base[%d])\n",
				 p->id, p->address, p->global_irq_base);
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_INTERRUPT_OVERRIDE:
		अणु
			काष्ठा acpi_madt_पूर्णांकerrupt_override *p =
			    (काष्ठा acpi_madt_पूर्णांकerrupt_override *)header;
			pr_info("INT_SRC_OVR (bus %d bus_irq %d global_irq %d %s %s)\n",
				p->bus, p->source_irq, p->global_irq,
				mps_पूर्णांकi_flags_polarity[p->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK],
				mps_पूर्णांकi_flags_trigger[(p->पूर्णांकi_flags & ACPI_MADT_TRIGGER_MASK) >> 2]);
			अगर (p->पूर्णांकi_flags  &
			    ~(ACPI_MADT_POLARITY_MASK | ACPI_MADT_TRIGGER_MASK))
				pr_info("INT_SRC_OVR unexpected reserved flags: 0x%x\n",
					p->पूर्णांकi_flags  &
					~(ACPI_MADT_POLARITY_MASK | ACPI_MADT_TRIGGER_MASK));
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_NMI_SOURCE:
		अणु
			काष्ठा acpi_madt_nmi_source *p =
			    (काष्ठा acpi_madt_nmi_source *)header;
			pr_info("NMI_SRC (%s %s global_irq %d)\n",
				mps_पूर्णांकi_flags_polarity[p->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK],
				mps_पूर्णांकi_flags_trigger[(p->पूर्णांकi_flags & ACPI_MADT_TRIGGER_MASK) >> 2],
				p->global_irq);
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_LOCAL_APIC_NMI:
		अणु
			काष्ठा acpi_madt_local_apic_nmi *p =
			    (काष्ठा acpi_madt_local_apic_nmi *)header;
			pr_info("LAPIC_NMI (acpi_id[0x%02x] %s %s lint[0x%x])\n",
				p->processor_id,
				mps_पूर्णांकi_flags_polarity[p->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK	],
				mps_पूर्णांकi_flags_trigger[(p->पूर्णांकi_flags & ACPI_MADT_TRIGGER_MASK) >> 2],
				p->lपूर्णांक);
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_LOCAL_X2APIC_NMI:
		अणु
			u16 polarity, trigger;
			काष्ठा acpi_madt_local_x2apic_nmi *p =
			    (काष्ठा acpi_madt_local_x2apic_nmi *)header;

			polarity = p->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK;
			trigger = (p->पूर्णांकi_flags & ACPI_MADT_TRIGGER_MASK) >> 2;

			pr_info("X2APIC_NMI (uid[0x%02x] %s %s lint[0x%x])\n",
				p->uid,
				mps_पूर्णांकi_flags_polarity[polarity],
				mps_पूर्णांकi_flags_trigger[trigger],
				p->lपूर्णांक);
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_LOCAL_APIC_OVERRIDE:
		अणु
			काष्ठा acpi_madt_local_apic_override *p =
			    (काष्ठा acpi_madt_local_apic_override *)header;
			pr_info("LAPIC_ADDR_OVR (address[%p])\n",
				(व्योम *)(अचिन्हित दीर्घ)p->address);
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_IO_SAPIC:
		अणु
			काष्ठा acpi_madt_io_sapic *p =
			    (काष्ठा acpi_madt_io_sapic *)header;
			pr_debug("IOSAPIC (id[0x%x] address[%p] gsi_base[%d])\n",
				 p->id, (व्योम *)(अचिन्हित दीर्घ)p->address,
				 p->global_irq_base);
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_LOCAL_SAPIC:
		अणु
			काष्ठा acpi_madt_local_sapic *p =
			    (काष्ठा acpi_madt_local_sapic *)header;
			pr_debug("LSAPIC (acpi_id[0x%02x] lsapic_id[0x%02x] lsapic_eid[0x%02x] %s)\n",
				 p->processor_id, p->id, p->eid,
				 (p->lapic_flags & ACPI_MADT_ENABLED) ? "enabled" : "disabled");
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_INTERRUPT_SOURCE:
		अणु
			काष्ठा acpi_madt_पूर्णांकerrupt_source *p =
			    (काष्ठा acpi_madt_पूर्णांकerrupt_source *)header;
			pr_info("PLAT_INT_SRC (%s %s type[0x%x] id[0x%04x] eid[0x%x] iosapic_vector[0x%x] global_irq[0x%x]\n",
				mps_पूर्णांकi_flags_polarity[p->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK],
				mps_पूर्णांकi_flags_trigger[(p->पूर्णांकi_flags & ACPI_MADT_TRIGGER_MASK) >> 2],
				p->type, p->id, p->eid, p->io_sapic_vector,
				p->global_irq);
		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_GENERIC_INTERRUPT:
		अणु
			काष्ठा acpi_madt_generic_पूर्णांकerrupt *p =
				(काष्ठा acpi_madt_generic_पूर्णांकerrupt *)header;
			pr_debug("GICC (acpi_id[0x%04x] address[%llx] MPIDR[0x%llx] %s)\n",
				 p->uid, p->base_address,
				 p->arm_mpidr,
				 (p->flags & ACPI_MADT_ENABLED) ? "enabled" : "disabled");

		पूर्ण
		अवरोध;

	हाल ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR:
		अणु
			काष्ठा acpi_madt_generic_distributor *p =
				(काष्ठा acpi_madt_generic_distributor *)header;
			pr_debug("GIC Distributor (gic_id[0x%04x] address[%llx] gsi_base[%d])\n",
				 p->gic_id, p->base_address,
				 p->global_irq_base);
		पूर्ण
		अवरोध;

	शेष:
		pr_warn("Found unsupported MADT entry (type = 0x%x)\n",
			header->type);
		अवरोध;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ __init
acpi_get_entry_type(काष्ठा acpi_subtable_entry *entry)
अणु
	चयन (entry->type) अणु
	हाल ACPI_SUBTABLE_COMMON:
		वापस entry->hdr->common.type;
	हाल ACPI_SUBTABLE_HMAT:
		वापस entry->hdr->hmat.type;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ __init
acpi_get_entry_length(काष्ठा acpi_subtable_entry *entry)
अणु
	चयन (entry->type) अणु
	हाल ACPI_SUBTABLE_COMMON:
		वापस entry->hdr->common.length;
	हाल ACPI_SUBTABLE_HMAT:
		वापस entry->hdr->hmat.length;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ __init
acpi_get_subtable_header_length(काष्ठा acpi_subtable_entry *entry)
अणु
	चयन (entry->type) अणु
	हाल ACPI_SUBTABLE_COMMON:
		वापस माप(entry->hdr->common);
	हाल ACPI_SUBTABLE_HMAT:
		वापस माप(entry->hdr->hmat);
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत acpi_subtable_type __init
acpi_get_subtable_type(अक्षर *id)
अणु
	अगर (म_भेदन(id, ACPI_SIG_HMAT, 4) == 0)
		वापस ACPI_SUBTABLE_HMAT;
	वापस ACPI_SUBTABLE_COMMON;
पूर्ण

/**
 * acpi_parse_entries_array - क्रम each proc_num find a suitable subtable
 *
 * @id: table id (क्रम debugging purposes)
 * @table_size: size of the root table
 * @table_header: where करोes the table start?
 * @proc: array of acpi_subtable_proc काष्ठा containing entry id
 *        and associated handler with it
 * @proc_num: how big proc is?
 * @max_entries: how many entries can we process?
 *
 * For each proc_num find a subtable with proc->id and run proc->handler
 * on it. Assumption is that there's only single handler क्रम particular
 * entry id.
 *
 * The table_size is not the size of the complete ACPI table (the length
 * field in the header काष्ठा), but only the size of the root table; i.e.,
 * the offset from the very first byte of the complete ACPI table, to the
 * first byte of the very first subtable.
 *
 * On success वापसs sum of all matching entries क्रम all proc handlers.
 * Otherwise, -ENODEV or -EINVAL is वापसed.
 */
अटल पूर्णांक __init acpi_parse_entries_array(अक्षर *id, अचिन्हित दीर्घ table_size,
		काष्ठा acpi_table_header *table_header,
		काष्ठा acpi_subtable_proc *proc, पूर्णांक proc_num,
		अचिन्हित पूर्णांक max_entries)
अणु
	काष्ठा acpi_subtable_entry entry;
	अचिन्हित दीर्घ table_end, subtable_len, entry_len;
	पूर्णांक count = 0;
	पूर्णांक errs = 0;
	पूर्णांक i;

	table_end = (अचिन्हित दीर्घ)table_header + table_header->length;

	/* Parse all entries looking क्रम a match. */

	entry.type = acpi_get_subtable_type(id);
	entry.hdr = (जोड़ acpi_subtable_headers *)
	    ((अचिन्हित दीर्घ)table_header + table_size);
	subtable_len = acpi_get_subtable_header_length(&entry);

	जबतक (((अचिन्हित दीर्घ)entry.hdr) + subtable_len  < table_end) अणु
		अगर (max_entries && count >= max_entries)
			अवरोध;

		क्रम (i = 0; i < proc_num; i++) अणु
			अगर (acpi_get_entry_type(&entry) != proc[i].id)
				जारी;
			अगर (!proc[i].handler ||
			     (!errs && proc[i].handler(entry.hdr, table_end))) अणु
				errs++;
				जारी;
			पूर्ण

			proc[i].count++;
			अवरोध;
		पूर्ण
		अगर (i != proc_num)
			count++;

		/*
		 * If entry->length is 0, अवरोध from this loop to aव्योम
		 * infinite loop.
		 */
		entry_len = acpi_get_entry_length(&entry);
		अगर (entry_len == 0) अणु
			pr_err("[%4.4s:0x%02x] Invalid zero length\n", id, proc->id);
			वापस -EINVAL;
		पूर्ण

		entry.hdr = (जोड़ acpi_subtable_headers *)
		    ((अचिन्हित दीर्घ)entry.hdr + entry_len);
	पूर्ण

	अगर (max_entries && count > max_entries) अणु
		pr_warn("[%4.4s:0x%02x] found the maximum %i entries\n",
			id, proc->id, count);
	पूर्ण

	वापस errs ? -EINVAL : count;
पूर्ण

पूर्णांक __init acpi_table_parse_entries_array(अक्षर *id,
			 अचिन्हित दीर्घ table_size,
			 काष्ठा acpi_subtable_proc *proc, पूर्णांक proc_num,
			 अचिन्हित पूर्णांक max_entries)
अणु
	काष्ठा acpi_table_header *table_header = शून्य;
	पूर्णांक count;
	u32 instance = 0;

	अगर (acpi_disabled)
		वापस -ENODEV;

	अगर (!id)
		वापस -EINVAL;

	अगर (!table_size)
		वापस -EINVAL;

	अगर (!म_भेदन(id, ACPI_SIG_MADT, 4))
		instance = acpi_apic_instance;

	acpi_get_table(id, instance, &table_header);
	अगर (!table_header) अणु
		pr_warn("%4.4s not present\n", id);
		वापस -ENODEV;
	पूर्ण

	count = acpi_parse_entries_array(id, table_size, table_header,
			proc, proc_num, max_entries);

	acpi_put_table(table_header);
	वापस count;
पूर्ण

पूर्णांक __init acpi_table_parse_entries(अक्षर *id,
			अचिन्हित दीर्घ table_size,
			पूर्णांक entry_id,
			acpi_tbl_entry_handler handler,
			अचिन्हित पूर्णांक max_entries)
अणु
	काष्ठा acpi_subtable_proc proc = अणु
		.id		= entry_id,
		.handler	= handler,
	पूर्ण;

	वापस acpi_table_parse_entries_array(id, table_size, &proc, 1,
						max_entries);
पूर्ण

पूर्णांक __init acpi_table_parse_madt(क्रमागत acpi_madt_type id,
		      acpi_tbl_entry_handler handler, अचिन्हित पूर्णांक max_entries)
अणु
	वापस acpi_table_parse_entries(ACPI_SIG_MADT,
					    माप(काष्ठा acpi_table_madt), id,
					    handler, max_entries);
पूर्ण

/**
 * acpi_table_parse - find table with @id, run @handler on it
 * @id: table id to find
 * @handler: handler to run
 *
 * Scan the ACPI System Descriptor Table (STD) क्रम a table matching @id,
 * run @handler on it.
 *
 * Return 0 अगर table found, -त्रुटि_सं अगर not.
 */
पूर्णांक __init acpi_table_parse(अक्षर *id, acpi_tbl_table_handler handler)
अणु
	काष्ठा acpi_table_header *table = शून्य;

	अगर (acpi_disabled)
		वापस -ENODEV;

	अगर (!id || !handler)
		वापस -EINVAL;

	अगर (म_भेदन(id, ACPI_SIG_MADT, 4) == 0)
		acpi_get_table(id, acpi_apic_instance, &table);
	अन्यथा
		acpi_get_table(id, 0, &table);

	अगर (table) अणु
		handler(table);
		acpi_put_table(table);
		वापस 0;
	पूर्ण अन्यथा
		वापस -ENODEV;
पूर्ण

/*
 * The BIOS is supposed to supply a single APIC/MADT,
 * but some report two.  Provide a knob to use either.
 * (करोn't you wish instance 0 and 1 were not the same?)
 */
अटल व्योम __init check_multiple_madt(व्योम)
अणु
	काष्ठा acpi_table_header *table = शून्य;

	acpi_get_table(ACPI_SIG_MADT, 2, &table);
	अगर (table) अणु
		pr_warn("BIOS bug: multiple APIC/MADT found, using %d\n",
			acpi_apic_instance);
		pr_warn("If \"acpi_apic_instance=%d\" works better, "
			"notify linux-acpi@vger.kernel.org\n",
			acpi_apic_instance ? 0 : 2);
		acpi_put_table(table);

	पूर्ण अन्यथा
		acpi_apic_instance = 0;

	वापस;
पूर्ण

अटल व्योम acpi_table_taपूर्णांक(काष्ठा acpi_table_header *table)
अणु
	pr_warn("Override [%4.4s-%8.8s], this is unsafe: tainting kernel\n",
		table->signature, table->oem_table_id);
	add_taपूर्णांक(TAINT_OVERRIDDEN_ACPI_TABLE, LOCKDEP_NOW_UNRELIABLE);
पूर्ण

#अगर_घोषित CONFIG_ACPI_TABLE_UPGRADE
अटल u64 acpi_tables_addr;
अटल पूर्णांक all_tables_size;

/* Copied from acpica/tbutils.c:acpi_tb_checksum() */
अटल u8 __init acpi_table_checksum(u8 *buffer, u32 length)
अणु
	u8 sum = 0;
	u8 *end = buffer + length;

	जबतक (buffer < end)
		sum = (u8) (sum + *(buffer++));
	वापस sum;
पूर्ण

/* All but ACPI_SIG_RSDP and ACPI_SIG_FACS: */
अटल स्थिर अक्षर table_sigs[][ACPI_NAMESEG_SIZE] __initस्थिर = अणु
	ACPI_SIG_BERT, ACPI_SIG_BGRT, ACPI_SIG_CPEP, ACPI_SIG_ECDT,
	ACPI_SIG_EINJ, ACPI_SIG_ERST, ACPI_SIG_HEST, ACPI_SIG_MADT,
	ACPI_SIG_MSCT, ACPI_SIG_SBST, ACPI_SIG_SLIT, ACPI_SIG_SRAT,
	ACPI_SIG_ASF,  ACPI_SIG_BOOT, ACPI_SIG_DBGP, ACPI_SIG_DMAR,
	ACPI_SIG_HPET, ACPI_SIG_IBFT, ACPI_SIG_IVRS, ACPI_SIG_MCFG,
	ACPI_SIG_MCHI, ACPI_SIG_SLIC, ACPI_SIG_SPCR, ACPI_SIG_SPMI,
	ACPI_SIG_TCPA, ACPI_SIG_UEFI, ACPI_SIG_WAET, ACPI_SIG_WDAT,
	ACPI_SIG_WDDT, ACPI_SIG_WDRT, ACPI_SIG_DSDT, ACPI_SIG_FADT,
	ACPI_SIG_PSDT, ACPI_SIG_RSDT, ACPI_SIG_XSDT, ACPI_SIG_SSDT,
	ACPI_SIG_IORT, ACPI_SIG_NFIT, ACPI_SIG_HMAT, ACPI_SIG_PPTT,
	ACPI_SIG_NHLT पूर्ण;

#घोषणा ACPI_HEADER_SIZE माप(काष्ठा acpi_table_header)

#घोषणा NR_ACPI_INITRD_TABLES 64
अटल काष्ठा cpio_data __initdata acpi_initrd_files[NR_ACPI_INITRD_TABLES];
अटल DECLARE_BITMAP(acpi_initrd_installed, NR_ACPI_INITRD_TABLES);

#घोषणा MAP_CHUNK_SIZE   (NR_FIX_BTMAPS << PAGE_SHIFT)

व्योम __init acpi_table_upgrade(व्योम)
अणु
	व्योम *data;
	माप_प्रकार size;
	पूर्णांक sig, no, table_nr = 0, total_offset = 0;
	दीर्घ offset = 0;
	काष्ठा acpi_table_header *table;
	अक्षर cpio_path[32] = "kernel/firmware/acpi/";
	काष्ठा cpio_data file;

	अगर (IS_ENABLED(CONFIG_ACPI_TABLE_OVERRIDE_VIA_BUILTIN_INITRD)) अणु
		data = __initramfs_start;
		size = __initramfs_size;
	पूर्ण अन्यथा अणु
		data = (व्योम *)initrd_start;
		size = initrd_end - initrd_start;
	पूर्ण

	अगर (data == शून्य || size == 0)
		वापस;

	क्रम (no = 0; no < NR_ACPI_INITRD_TABLES; no++) अणु
		file = find_cpio_data(cpio_path, data, size, &offset);
		अगर (!file.data)
			अवरोध;

		data += offset;
		size -= offset;

		अगर (file.size < माप(काष्ठा acpi_table_header)) अणु
			pr_err("ACPI OVERRIDE: Table smaller than ACPI header [%s%s]\n",
				cpio_path, file.name);
			जारी;
		पूर्ण

		table = file.data;

		क्रम (sig = 0; sig < ARRAY_SIZE(table_sigs); sig++)
			अगर (!स_भेद(table->signature, table_sigs[sig], 4))
				अवरोध;

		अगर (sig >= ARRAY_SIZE(table_sigs)) अणु
			pr_err("ACPI OVERRIDE: Unknown signature [%s%s]\n",
				cpio_path, file.name);
			जारी;
		पूर्ण
		अगर (file.size != table->length) अणु
			pr_err("ACPI OVERRIDE: File length does not match table length [%s%s]\n",
				cpio_path, file.name);
			जारी;
		पूर्ण
		अगर (acpi_table_checksum(file.data, table->length)) अणु
			pr_err("ACPI OVERRIDE: Bad table checksum [%s%s]\n",
				cpio_path, file.name);
			जारी;
		पूर्ण

		pr_info("%4.4s ACPI table found in initrd [%s%s][0x%x]\n",
			table->signature, cpio_path, file.name, table->length);

		all_tables_size += table->length;
		acpi_initrd_files[table_nr].data = file.data;
		acpi_initrd_files[table_nr].size = file.size;
		table_nr++;
	पूर्ण
	अगर (table_nr == 0)
		वापस;

	अगर (security_locked_करोwn(LOCKDOWN_ACPI_TABLES)) अणु
		pr_notice("kernel is locked down, ignoring table override\n");
		वापस;
	पूर्ण

	acpi_tables_addr =
		memblock_find_in_range(0, ACPI_TABLE_UPGRADE_MAX_PHYS,
				       all_tables_size, PAGE_SIZE);
	अगर (!acpi_tables_addr) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	/*
	 * Only calling e820_add_reserve करोes not work and the
	 * tables are invalid (memory got used) later.
	 * memblock_reserve works as expected and the tables won't get modअगरied.
	 * But it's not enough on X86 because ioremap will
	 * complain later (used by acpi_os_map_memory) that the pages
	 * that should get mapped are not marked "reserved".
	 * Both memblock_reserve and e820__range_add (via arch_reserve_mem_area)
	 * works fine.
	 */
	memblock_reserve(acpi_tables_addr, all_tables_size);
	arch_reserve_mem_area(acpi_tables_addr, all_tables_size);

	/*
	 * early_ioremap only can remap 256k one समय. If we map all
	 * tables one समय, we will hit the limit. Need to map chunks
	 * one by one during copying the same as that in relocate_initrd().
	 */
	क्रम (no = 0; no < table_nr; no++) अणु
		अचिन्हित अक्षर *src_p = acpi_initrd_files[no].data;
		phys_addr_t size = acpi_initrd_files[no].size;
		phys_addr_t dest_addr = acpi_tables_addr + total_offset;
		phys_addr_t slop, clen;
		अक्षर *dest_p;

		total_offset += size;

		जबतक (size) अणु
			slop = dest_addr & ~PAGE_MASK;
			clen = size;
			अगर (clen > MAP_CHUNK_SIZE - slop)
				clen = MAP_CHUNK_SIZE - slop;
			dest_p = early_memremap(dest_addr & PAGE_MASK,
						clen + slop);
			स_नकल(dest_p + slop, src_p, clen);
			early_memunmap(dest_p, clen + slop);
			src_p += clen;
			dest_addr += clen;
			size -= clen;
		पूर्ण
	पूर्ण
पूर्ण

अटल acpi_status
acpi_table_initrd_override(काष्ठा acpi_table_header *existing_table,
			   acpi_physical_address *address, u32 *length)
अणु
	पूर्णांक table_offset = 0;
	पूर्णांक table_index = 0;
	काष्ठा acpi_table_header *table;
	u32 table_length;

	*length = 0;
	*address = 0;
	अगर (!acpi_tables_addr)
		वापस AE_OK;

	जबतक (table_offset + ACPI_HEADER_SIZE <= all_tables_size) अणु
		table = acpi_os_map_memory(acpi_tables_addr + table_offset,
					   ACPI_HEADER_SIZE);
		अगर (table_offset + table->length > all_tables_size) अणु
			acpi_os_unmap_memory(table, ACPI_HEADER_SIZE);
			WARN_ON(1);
			वापस AE_OK;
		पूर्ण

		table_length = table->length;

		/* Only override tables matched */
		अगर (स_भेद(existing_table->signature, table->signature, 4) ||
		    स_भेद(table->oem_id, existing_table->oem_id,
			   ACPI_OEM_ID_SIZE) ||
		    स_भेद(table->oem_table_id, existing_table->oem_table_id,
			   ACPI_OEM_TABLE_ID_SIZE)) अणु
			acpi_os_unmap_memory(table, ACPI_HEADER_SIZE);
			जाओ next_table;
		पूर्ण
		/*
		 * Mark the table to aव्योम being used in
		 * acpi_table_initrd_scan() and check the revision.
		 */
		अगर (test_and_set_bit(table_index, acpi_initrd_installed) ||
		    existing_table->oem_revision >= table->oem_revision) अणु
			acpi_os_unmap_memory(table, ACPI_HEADER_SIZE);
			जाओ next_table;
		पूर्ण

		*length = table_length;
		*address = acpi_tables_addr + table_offset;
		pr_info("Table Upgrade: override [%4.4s-%6.6s-%8.8s]\n",
			table->signature, table->oem_id,
			table->oem_table_id);
		acpi_os_unmap_memory(table, ACPI_HEADER_SIZE);
		अवरोध;

next_table:
		table_offset += table_length;
		table_index++;
	पूर्ण
	वापस AE_OK;
पूर्ण

अटल व्योम __init acpi_table_initrd_scan(व्योम)
अणु
	पूर्णांक table_offset = 0;
	पूर्णांक table_index = 0;
	u32 table_length;
	काष्ठा acpi_table_header *table;

	अगर (!acpi_tables_addr)
		वापस;

	जबतक (table_offset + ACPI_HEADER_SIZE <= all_tables_size) अणु
		table = acpi_os_map_memory(acpi_tables_addr + table_offset,
					   ACPI_HEADER_SIZE);
		अगर (table_offset + table->length > all_tables_size) अणु
			acpi_os_unmap_memory(table, ACPI_HEADER_SIZE);
			WARN_ON(1);
			वापस;
		पूर्ण

		table_length = table->length;

		/* Skip RSDT/XSDT which should only be used क्रम override */
		अगर (ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_RSDT) ||
		    ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_XSDT)) अणु
			acpi_os_unmap_memory(table, ACPI_HEADER_SIZE);
			जाओ next_table;
		पूर्ण
		/*
		 * Mark the table to aव्योम being used in
		 * acpi_table_initrd_override(). Though this is not possible
		 * because override is disabled in acpi_install_table().
		 */
		अगर (test_and_set_bit(table_index, acpi_initrd_installed)) अणु
			acpi_os_unmap_memory(table, ACPI_HEADER_SIZE);
			जाओ next_table;
		पूर्ण

		pr_info("Table Upgrade: install [%4.4s-%6.6s-%8.8s]\n",
			table->signature, table->oem_id,
			table->oem_table_id);
		acpi_os_unmap_memory(table, ACPI_HEADER_SIZE);
		acpi_install_table(acpi_tables_addr + table_offset, TRUE);
next_table:
		table_offset += table_length;
		table_index++;
	पूर्ण
पूर्ण
#अन्यथा
अटल acpi_status
acpi_table_initrd_override(काष्ठा acpi_table_header *existing_table,
			   acpi_physical_address *address,
			   u32 *table_length)
अणु
	*table_length = 0;
	*address = 0;
	वापस AE_OK;
पूर्ण

अटल व्योम __init acpi_table_initrd_scan(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_TABLE_UPGRADE */

acpi_status
acpi_os_physical_table_override(काष्ठा acpi_table_header *existing_table,
				acpi_physical_address *address,
				u32 *table_length)
अणु
	वापस acpi_table_initrd_override(existing_table, address,
					  table_length);
पूर्ण

#अगर_घोषित CONFIG_ACPI_CUSTOM_DSDT
अटल व्योम *amlcode __attribute__ ((weakref("AmlCode")));
अटल व्योम *dsdt_amlcode __attribute__ ((weakref("dsdt_aml_code")));
#पूर्ण_अगर

acpi_status acpi_os_table_override(काष्ठा acpi_table_header *existing_table,
		       काष्ठा acpi_table_header **new_table)
अणु
	अगर (!existing_table || !new_table)
		वापस AE_BAD_PARAMETER;

	*new_table = शून्य;

#अगर_घोषित CONFIG_ACPI_CUSTOM_DSDT
	अगर (!म_भेदन(existing_table->signature, "DSDT", 4)) अणु
		*new_table = (काष्ठा acpi_table_header *)&amlcode;
		अगर (!(*new_table))
			*new_table = (काष्ठा acpi_table_header *)&dsdt_amlcode;
	पूर्ण
#पूर्ण_अगर
	अगर (*new_table != शून्य)
		acpi_table_taपूर्णांक(existing_table);
	वापस AE_OK;
पूर्ण

/*
 * acpi_locate_initial_tables()
 *
 * find RSDP, find and checksum SDT/XSDT.
 * checksum all tables, prपूर्णांक SDT/XSDT
 *
 * result: sdt_entry[] is initialized
 */

पूर्णांक __init acpi_locate_initial_tables(व्योम)
अणु
	acpi_status status;

	अगर (acpi_verअगरy_table_checksum) अणु
		pr_info("Early table checksum verification enabled\n");
		acpi_gbl_enable_table_validation = TRUE;
	पूर्ण अन्यथा अणु
		pr_info("Early table checksum verification disabled\n");
		acpi_gbl_enable_table_validation = FALSE;
	पूर्ण

	status = acpi_initialize_tables(initial_tables, ACPI_MAX_TABLES, 0);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम __init acpi_reserve_initial_tables(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ACPI_MAX_TABLES; i++) अणु
		काष्ठा acpi_table_desc *table_desc = &initial_tables[i];
		u64 start = table_desc->address;
		u64 size = table_desc->length;

		अगर (!start || !size)
			अवरोध;

		pr_info("Reserving %4s table memory at [mem 0x%llx-0x%llx]\n",
			table_desc->signature.ascii, start, start + size - 1);

		memblock_reserve(start, size);
	पूर्ण
पूर्ण

व्योम __init acpi_table_init_complete(व्योम)
अणु
	acpi_table_initrd_scan();
	check_multiple_madt();
पूर्ण

पूर्णांक __init acpi_table_init(व्योम)
अणु
	पूर्णांक ret;

	ret = acpi_locate_initial_tables();
	अगर (ret)
		वापस ret;

	acpi_table_init_complete();

	वापस 0;
पूर्ण

अटल पूर्णांक __init acpi_parse_apic_instance(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;

	अगर (kstrtoपूर्णांक(str, 0, &acpi_apic_instance))
		वापस -EINVAL;

	pr_notice("Shall use APIC/MADT table %d\n", acpi_apic_instance);

	वापस 0;
पूर्ण
early_param("acpi_apic_instance", acpi_parse_apic_instance);

अटल पूर्णांक __init acpi_क्रमce_table_verअगरication_setup(अक्षर *s)
अणु
	acpi_verअगरy_table_checksum = true;

	वापस 0;
पूर्ण
early_param("acpi_force_table_verification", acpi_क्रमce_table_verअगरication_setup);

अटल पूर्णांक __init acpi_क्रमce_32bit_fadt_addr(अक्षर *s)
अणु
	pr_info("Forcing 32 Bit FADT addresses\n");
	acpi_gbl_use32_bit_fadt_addresses = TRUE;

	वापस 0;
पूर्ण
early_param("acpi_force_32bit_fadt_addr", acpi_क्रमce_32bit_fadt_addr);
