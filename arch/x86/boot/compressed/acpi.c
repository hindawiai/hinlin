<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा BOOT_CTYPE_H
#समावेश "misc.h"
#समावेश "error.h"
#समावेश "../string.h"

#समावेश <linux/numa.h>
#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>

/*
 * Longest parameter of 'acpi=' is 'copy_dsdt', plus an extra '\0'
 * क्रम termination.
 */
#घोषणा MAX_ACPI_ARG_LENGTH 10

/*
 * Immovable memory regions representation. Max amount of memory regions is
 * MAX_NUMNODES*2.
 */
काष्ठा mem_vector immovable_mem[MAX_NUMNODES*2];

/*
 * Search EFI प्रणाली tables क्रम RSDP.  If both ACPI_20_TABLE_GUID and
 * ACPI_TABLE_GUID are found, take the क्रमmer, which has more features.
 */
अटल acpi_physical_address
__efi_get_rsdp_addr(अचिन्हित दीर्घ config_tables, अचिन्हित पूर्णांक nr_tables,
		    bool efi_64)
अणु
	acpi_physical_address rsdp_addr = 0;

#अगर_घोषित CONFIG_EFI
	पूर्णांक i;

	/* Get EFI tables from systab. */
	क्रम (i = 0; i < nr_tables; i++) अणु
		acpi_physical_address table;
		efi_guid_t guid;

		अगर (efi_64) अणु
			efi_config_table_64_t *tbl = (efi_config_table_64_t *)config_tables + i;

			guid  = tbl->guid;
			table = tbl->table;

			अगर (!IS_ENABLED(CONFIG_X86_64) && table >> 32) अणु
				debug_माला_दोtr("Error getting RSDP address: EFI config table located above 4GB.\n");
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			efi_config_table_32_t *tbl = (efi_config_table_32_t *)config_tables + i;

			guid  = tbl->guid;
			table = tbl->table;
		पूर्ण

		अगर (!(efi_guidcmp(guid, ACPI_TABLE_GUID)))
			rsdp_addr = table;
		अन्यथा अगर (!(efi_guidcmp(guid, ACPI_20_TABLE_GUID)))
			वापस table;
	पूर्ण
#पूर्ण_अगर
	वापस rsdp_addr;
पूर्ण

/* EFI/kexec support is 64-bit only. */
#अगर_घोषित CONFIG_X86_64
अटल काष्ठा efi_setup_data *get_kexec_setup_data_addr(व्योम)
अणु
	काष्ठा setup_data *data;
	u64 pa_data;

	pa_data = boot_params->hdr.setup_data;
	जबतक (pa_data) अणु
		data = (काष्ठा setup_data *)pa_data;
		अगर (data->type == SETUP_EFI)
			वापस (काष्ठा efi_setup_data *)(pa_data + माप(काष्ठा setup_data));

		pa_data = data->next;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल acpi_physical_address kexec_get_rsdp_addr(व्योम)
अणु
	efi_प्रणाली_table_64_t *systab;
	काष्ठा efi_setup_data *esd;
	काष्ठा efi_info *ei;
	अक्षर *sig;

	esd = (काष्ठा efi_setup_data *)get_kexec_setup_data_addr();
	अगर (!esd)
		वापस 0;

	अगर (!esd->tables) अणु
		debug_माला_दोtr("Wrong kexec SETUP_EFI data.\n");
		वापस 0;
	पूर्ण

	ei = &boot_params->efi_info;
	sig = (अक्षर *)&ei->efi_loader_signature;
	अगर (म_भेदन(sig, EFI64_LOADER_SIGNATURE, 4)) अणु
		debug_माला_दोtr("Wrong kexec EFI loader signature.\n");
		वापस 0;
	पूर्ण

	/* Get systab from boot params. */
	systab = (efi_प्रणाली_table_64_t *) (ei->efi_systab | ((__u64)ei->efi_systab_hi << 32));
	अगर (!systab)
		error("EFI system table not found in kexec boot_params.");

	वापस __efi_get_rsdp_addr((अचिन्हित दीर्घ)esd->tables, systab->nr_tables, true);
पूर्ण
#अन्यथा
अटल acpi_physical_address kexec_get_rsdp_addr(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_X86_64 */

अटल acpi_physical_address efi_get_rsdp_addr(व्योम)
अणु
#अगर_घोषित CONFIG_EFI
	अचिन्हित दीर्घ systab, config_tables;
	अचिन्हित पूर्णांक nr_tables;
	काष्ठा efi_info *ei;
	bool efi_64;
	अक्षर *sig;

	ei = &boot_params->efi_info;
	sig = (अक्षर *)&ei->efi_loader_signature;

	अगर (!म_भेदन(sig, EFI64_LOADER_SIGNATURE, 4)) अणु
		efi_64 = true;
	पूर्ण अन्यथा अगर (!म_भेदन(sig, EFI32_LOADER_SIGNATURE, 4)) अणु
		efi_64 = false;
	पूर्ण अन्यथा अणु
		debug_माला_दोtr("Wrong EFI loader signature.\n");
		वापस 0;
	पूर्ण

	/* Get systab from boot params. */
#अगर_घोषित CONFIG_X86_64
	systab = ei->efi_systab | ((__u64)ei->efi_systab_hi << 32);
#अन्यथा
	अगर (ei->efi_systab_hi || ei->efi_memmap_hi) अणु
		debug_माला_दोtr("Error getting RSDP address: EFI system table located above 4GB.\n");
		वापस 0;
	पूर्ण
	systab = ei->efi_systab;
#पूर्ण_अगर
	अगर (!systab)
		error("EFI system table not found.");

	/* Handle EFI bitness properly */
	अगर (efi_64) अणु
		efi_प्रणाली_table_64_t *stbl = (efi_प्रणाली_table_64_t *)systab;

		config_tables	= stbl->tables;
		nr_tables	= stbl->nr_tables;
	पूर्ण अन्यथा अणु
		efi_प्रणाली_table_32_t *stbl = (efi_प्रणाली_table_32_t *)systab;

		config_tables	= stbl->tables;
		nr_tables	= stbl->nr_tables;
	पूर्ण

	अगर (!config_tables)
		error("EFI config tables not found.");

	वापस __efi_get_rsdp_addr(config_tables, nr_tables, efi_64);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल u8 compute_checksum(u8 *buffer, u32 length)
अणु
	u8 *end = buffer + length;
	u8 sum = 0;

	जबतक (buffer < end)
		sum += *(buffer++);

	वापस sum;
पूर्ण

/* Search a block of memory क्रम the RSDP signature. */
अटल u8 *scan_mem_क्रम_rsdp(u8 *start, u32 length)
अणु
	काष्ठा acpi_table_rsdp *rsdp;
	u8 *address, *end;

	end = start + length;

	/* Search from given start address क्रम the requested length */
	क्रम (address = start; address < end; address += ACPI_RSDP_SCAN_STEP) अणु
		/*
		 * Both RSDP signature and checksum must be correct.
		 * Note: Someबार there exists more than one RSDP in memory;
		 * the valid RSDP has a valid checksum, all others have an
		 * invalid checksum.
		 */
		rsdp = (काष्ठा acpi_table_rsdp *)address;

		/* BAD Signature */
		अगर (!ACPI_VALIDATE_RSDP_SIG(rsdp->signature))
			जारी;

		/* Check the standard checksum */
		अगर (compute_checksum((u8 *)rsdp, ACPI_RSDP_CHECKSUM_LENGTH))
			जारी;

		/* Check extended checksum अगर table version >= 2 */
		अगर ((rsdp->revision >= 2) &&
		    (compute_checksum((u8 *)rsdp, ACPI_RSDP_XCHECKSUM_LENGTH)))
			जारी;

		/* Signature and checksum valid, we have found a real RSDP */
		वापस address;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Search RSDP address in EBDA. */
अटल acpi_physical_address bios_get_rsdp_addr(व्योम)
अणु
	अचिन्हित दीर्घ address;
	u8 *rsdp;

	/* Get the location of the Extended BIOS Data Area (EBDA) */
	address = *(u16 *)ACPI_EBDA_PTR_LOCATION;
	address <<= 4;

	/*
	 * Search EBDA paragraphs (EBDA is required to be a minimum of
	 * 1K length)
	 */
	अगर (address > 0x400) अणु
		rsdp = scan_mem_क्रम_rsdp((u8 *)address, ACPI_EBDA_WINDOW_SIZE);
		अगर (rsdp)
			वापस (acpi_physical_address)(अचिन्हित दीर्घ)rsdp;
	पूर्ण

	/* Search upper memory: 16-byte boundaries in E0000h-FFFFFh */
	rsdp = scan_mem_क्रम_rsdp((u8 *) ACPI_HI_RSDP_WINDOW_BASE,
					ACPI_HI_RSDP_WINDOW_SIZE);
	अगर (rsdp)
		वापस (acpi_physical_address)(अचिन्हित दीर्घ)rsdp;

	वापस 0;
पूर्ण

/* Return RSDP address on success, otherwise 0. */
acpi_physical_address get_rsdp_addr(व्योम)
अणु
	acpi_physical_address pa;

	pa = boot_params->acpi_rsdp_addr;

	/*
	 * Try to get EFI data from setup_data. This can happen when we're a
	 * kexec'ed kernel and kexec(1) has passed all the required EFI info to
	 * us.
	 */
	अगर (!pa)
		pa = kexec_get_rsdp_addr();

	अगर (!pa)
		pa = efi_get_rsdp_addr();

	अगर (!pa)
		pa = bios_get_rsdp_addr();

	वापस pa;
पूर्ण

#अगर defined(CONFIG_RANDOMIZE_BASE) && defined(CONFIG_MEMORY_HOTREMOVE)
/*
 * Max length of 64-bit hex address string is 19, prefix "0x" + 16 hex
 * digits, and '\0' क्रम termination.
 */
#घोषणा MAX_ADDR_LEN 19

अटल अचिन्हित दीर्घ get_cmdline_acpi_rsdp(व्योम)
अणु
	अचिन्हित दीर्घ addr = 0;

#अगर_घोषित CONFIG_KEXEC
	अक्षर val[MAX_ADDR_LEN] = अणु पूर्ण;
	पूर्णांक ret;

	ret = cmdline_find_option("acpi_rsdp", val, MAX_ADDR_LEN);
	अगर (ret < 0)
		वापस 0;

	अगर (boot_kम_से_अदीर्घ(val, 16, &addr))
		वापस 0;
#पूर्ण_अगर
	वापस addr;
पूर्ण

/* Compute SRAT address from RSDP. */
अटल अचिन्हित दीर्घ get_acpi_srat_table(व्योम)
अणु
	अचिन्हित दीर्घ root_table, acpi_table;
	काष्ठा acpi_table_header *header;
	काष्ठा acpi_table_rsdp *rsdp;
	u32 num_entries, size, len;
	अक्षर arg[10];
	u8 *entry;

	/*
	 * Check whether we were given an RSDP on the command line. We करोn't
	 * stash this in boot params because the kernel itself may have
	 * dअगरferent ideas about whether to trust a command-line parameter.
	 */
	rsdp = (काष्ठा acpi_table_rsdp *)get_cmdline_acpi_rsdp();
	अगर (!rsdp)
		rsdp = (काष्ठा acpi_table_rsdp *)(दीर्घ)
			boot_params->acpi_rsdp_addr;

	अगर (!rsdp)
		वापस 0;

	/* Get ACPI root table from RSDP.*/
	अगर (!(cmdline_find_option("acpi", arg, माप(arg)) == 4 &&
	    !म_भेदन(arg, "rsdt", 4)) &&
	    rsdp->xsdt_physical_address &&
	    rsdp->revision > 1) अणु
		root_table = rsdp->xsdt_physical_address;
		size = ACPI_XSDT_ENTRY_SIZE;
	पूर्ण अन्यथा अणु
		root_table = rsdp->rsdt_physical_address;
		size = ACPI_RSDT_ENTRY_SIZE;
	पूर्ण

	अगर (!root_table)
		वापस 0;

	header = (काष्ठा acpi_table_header *)root_table;
	len = header->length;
	अगर (len < माप(काष्ठा acpi_table_header) + size)
		वापस 0;

	num_entries = (len - माप(काष्ठा acpi_table_header)) / size;
	entry = (u8 *)(root_table + माप(काष्ठा acpi_table_header));

	जबतक (num_entries--) अणु
		अगर (size == ACPI_RSDT_ENTRY_SIZE)
			acpi_table = *(u32 *)entry;
		अन्यथा
			acpi_table = *(u64 *)entry;

		अगर (acpi_table) अणु
			header = (काष्ठा acpi_table_header *)acpi_table;

			अगर (ACPI_COMPARE_NAMESEG(header->signature, ACPI_SIG_SRAT))
				वापस acpi_table;
		पूर्ण
		entry += size;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * count_immovable_mem_regions - Parse SRAT and cache the immovable
 * memory regions पूर्णांकo the immovable_mem array.
 *
 * Return the number of immovable memory regions on success, 0 on failure:
 *
 * - Too many immovable memory regions
 * - ACPI off or no SRAT found
 * - No immovable memory region found.
 */
पूर्णांक count_immovable_mem_regions(व्योम)
अणु
	अचिन्हित दीर्घ table_addr, table_end, table;
	काष्ठा acpi_subtable_header *sub_table;
	काष्ठा acpi_table_header *table_header;
	अक्षर arg[MAX_ACPI_ARG_LENGTH];
	पूर्णांक num = 0;

	अगर (cmdline_find_option("acpi", arg, माप(arg)) == 3 &&
	    !म_भेदन(arg, "off", 3))
		वापस 0;

	table_addr = get_acpi_srat_table();
	अगर (!table_addr)
		वापस 0;

	table_header = (काष्ठा acpi_table_header *)table_addr;
	table_end = table_addr + table_header->length;
	table = table_addr + माप(काष्ठा acpi_table_srat);

	जबतक (table + माप(काष्ठा acpi_subtable_header) < table_end) अणु

		sub_table = (काष्ठा acpi_subtable_header *)table;
		अगर (!sub_table->length) अणु
			debug_माला_दोtr("Invalid zero length SRAT subtable.\n");
			वापस 0;
		पूर्ण

		अगर (sub_table->type == ACPI_SRAT_TYPE_MEMORY_AFFINITY) अणु
			काष्ठा acpi_srat_mem_affinity *ma;

			ma = (काष्ठा acpi_srat_mem_affinity *)sub_table;
			अगर (!(ma->flags & ACPI_SRAT_MEM_HOT_PLUGGABLE) && ma->length) अणु
				immovable_mem[num].start = ma->base_address;
				immovable_mem[num].size = ma->length;
				num++;
			पूर्ण

			अगर (num >= MAX_NUMNODES*2) अणु
				debug_माला_दोtr("Too many immovable memory regions, aborting.\n");
				वापस 0;
			पूर्ण
		पूर्ण
		table += sub_table->length;
	पूर्ण
	वापस num;
पूर्ण
#पूर्ण_अगर /* CONFIG_RANDOMIZE_BASE && CONFIG_MEMORY_HOTREMOVE */
