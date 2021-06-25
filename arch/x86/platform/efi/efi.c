<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common EFI (Extensible Firmware Interface) support functions
 * Based on Extensible Firmware Interface Specअगरication version 1.0
 *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999-2002 Hewlett-Packard Co.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 2005-2008 Intel Co.
 *	Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *	Bibo Mao <bibo.mao@पूर्णांकel.com>
 *	Chandramouli Narayanan <mouli@linux.पूर्णांकel.com>
 *	Huang Ying <ying.huang@पूर्णांकel.com>
 * Copyright (C) 2013 SuSE Lअसल
 *	Borislav Petkov <bp@suse.de> - runसमय services VA mapping
 *
 * Copied from efi_32.c to eliminate the duplicated code between EFI
 * 32/64 support code. --ying 2007-10-26
 *
 * All EFI Runसमय Services are not implemented yet as EFI only
 * supports physical mode addressing on SoftSDV. This is to be fixed
 * in a future version.  --drummond 1999-07-20
 *
 * Implemented EFI runसमय services and भव mode calls.  --davidm
 *
 * Goutham Rao: <goutham.rao@पूर्णांकel.com>
 *	Skip non-WB memory and ignore empty memory ranges.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/efi.h>
#समावेश <linux/efi-bgrt.h>
#समावेश <linux/export.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/समय.स>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>
#समावेश <linux/bcd.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/uv/uv.h>

अटल अचिन्हित दीर्घ efi_systab_phys __initdata;
अटल अचिन्हित दीर्घ prop_phys = EFI_INVALID_TABLE_ADDR;
अटल अचिन्हित दीर्घ uga_phys = EFI_INVALID_TABLE_ADDR;
अटल अचिन्हित दीर्घ efi_runसमय, efi_nr_tables;

अचिन्हित दीर्घ efi_fw_venकरोr, efi_config_table;

अटल स्थिर efi_config_table_type_t arch_tables[] __initस्थिर = अणु
	अणुEFI_PROPERTIES_TABLE_GUID,	&prop_phys,		"PROP"		पूर्ण,
	अणुUGA_IO_PROTOCOL_GUID,		&uga_phys,		"UGA"		पूर्ण,
#अगर_घोषित CONFIG_X86_UV
	अणुUV_SYSTEM_TABLE_GUID,		&uv_systab_phys,	"UVsystab"	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ * स्थिर efi_tables[] = अणु
	&efi.acpi,
	&efi.acpi20,
	&efi.smbios,
	&efi.smbios3,
	&uga_phys,
#अगर_घोषित CONFIG_X86_UV
	&uv_systab_phys,
#पूर्ण_अगर
	&efi_fw_venकरोr,
	&efi_runसमय,
	&efi_config_table,
	&efi.esrt,
	&prop_phys,
	&efi_mem_attr_table,
#अगर_घोषित CONFIG_EFI_RCI2_TABLE
	&rci2_table_phys,
#पूर्ण_अगर
	&efi.tpm_log,
	&efi.tpm_final_log,
	&efi_rng_seed,
#अगर_घोषित CONFIG_LOAD_UEFI_KEYS
	&efi.mokvar_table,
#पूर्ण_अगर
पूर्ण;

u64 efi_setup;		/* efi setup_data physical address */

अटल पूर्णांक add_efi_memmap __initdata;
अटल पूर्णांक __init setup_add_efi_memmap(अक्षर *arg)
अणु
	add_efi_memmap = 1;
	वापस 0;
पूर्ण
early_param("add_efi_memmap", setup_add_efi_memmap);

व्योम __init efi_find_mirror(व्योम)
अणु
	efi_memory_desc_t *md;
	u64 mirror_size = 0, total_size = 0;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस;

	क्रम_each_efi_memory_desc(md) अणु
		अचिन्हित दीर्घ दीर्घ start = md->phys_addr;
		अचिन्हित दीर्घ दीर्घ size = md->num_pages << EFI_PAGE_SHIFT;

		total_size += size;
		अगर (md->attribute & EFI_MEMORY_MORE_RELIABLE) अणु
			memblock_mark_mirror(start, size);
			mirror_size += size;
		पूर्ण
	पूर्ण
	अगर (mirror_size)
		pr_info("Memory: %lldM/%lldM mirrored memory\n",
			mirror_size>>20, total_size>>20);
पूर्ण

/*
 * Tell the kernel about the EFI memory map.  This might include
 * more than the max 128 entries that can fit in the passed in e820
 * legacy (zeropage) memory map, but the kernel's e820 table can hold
 * E820_MAX_ENTRIES.
 */

अटल व्योम __init करो_add_efi_memmap(व्योम)
अणु
	efi_memory_desc_t *md;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस;

	क्रम_each_efi_memory_desc(md) अणु
		अचिन्हित दीर्घ दीर्घ start = md->phys_addr;
		अचिन्हित दीर्घ दीर्घ size = md->num_pages << EFI_PAGE_SHIFT;
		पूर्णांक e820_type;

		चयन (md->type) अणु
		हाल EFI_LOADER_CODE:
		हाल EFI_LOADER_DATA:
		हाल EFI_BOOT_SERVICES_CODE:
		हाल EFI_BOOT_SERVICES_DATA:
		हाल EFI_CONVENTIONAL_MEMORY:
			अगर (efi_soft_reserve_enabled()
			    && (md->attribute & EFI_MEMORY_SP))
				e820_type = E820_TYPE_SOFT_RESERVED;
			अन्यथा अगर (md->attribute & EFI_MEMORY_WB)
				e820_type = E820_TYPE_RAM;
			अन्यथा
				e820_type = E820_TYPE_RESERVED;
			अवरोध;
		हाल EFI_ACPI_RECLAIM_MEMORY:
			e820_type = E820_TYPE_ACPI;
			अवरोध;
		हाल EFI_ACPI_MEMORY_NVS:
			e820_type = E820_TYPE_NVS;
			अवरोध;
		हाल EFI_UNUSABLE_MEMORY:
			e820_type = E820_TYPE_UNUSABLE;
			अवरोध;
		हाल EFI_PERSISTENT_MEMORY:
			e820_type = E820_TYPE_PMEM;
			अवरोध;
		शेष:
			/*
			 * EFI_RESERVED_TYPE EFI_RUNTIME_SERVICES_CODE
			 * EFI_RUNTIME_SERVICES_DATA EFI_MEMORY_MAPPED_IO
			 * EFI_MEMORY_MAPPED_IO_PORT_SPACE EFI_PAL_CODE
			 */
			e820_type = E820_TYPE_RESERVED;
			अवरोध;
		पूर्ण

		e820__range_add(start, size, e820_type);
	पूर्ण
	e820__update_table(e820_table);
पूर्ण

/*
 * Given add_efi_memmap शेषs to 0 and there there is no alternative
 * e820 mechanism क्रम soft-reserved memory, import the full EFI memory
 * map अगर soft reservations are present and enabled. Otherwise, the
 * mechanism to disable the kernel's consideration of EFI_MEMORY_SP is
 * the efi=nosoftreserve option.
 */
अटल bool करो_efi_soft_reserve(व्योम)
अणु
	efi_memory_desc_t *md;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस false;

	अगर (!efi_soft_reserve_enabled())
		वापस false;

	क्रम_each_efi_memory_desc(md)
		अगर (md->type == EFI_CONVENTIONAL_MEMORY &&
		    (md->attribute & EFI_MEMORY_SP))
			वापस true;
	वापस false;
पूर्ण

पूर्णांक __init efi_memblock_x86_reserve_range(व्योम)
अणु
	काष्ठा efi_info *e = &boot_params.efi_info;
	काष्ठा efi_memory_map_data data;
	phys_addr_t pmap;
	पूर्णांक rv;

	अगर (efi_enabled(EFI_PARAVIRT))
		वापस 0;

	/* Can't handle firmware tables above 4GB on i386 */
	अगर (IS_ENABLED(CONFIG_X86_32) && e->efi_memmap_hi > 0) अणु
		pr_err("Memory map is above 4GB, disabling EFI.\n");
		वापस -EINVAL;
	पूर्ण
	pmap = (phys_addr_t)(e->efi_memmap | ((u64)e->efi_memmap_hi << 32));

	data.phys_map		= pmap;
	data.size 		= e->efi_memmap_size;
	data.desc_size		= e->efi_memdesc_size;
	data.desc_version	= e->efi_memdesc_version;

	rv = efi_memmap_init_early(&data);
	अगर (rv)
		वापस rv;

	अगर (add_efi_memmap || करो_efi_soft_reserve())
		करो_add_efi_memmap();

	efi_fake_memmap_early();

	WARN(efi.memmap.desc_version != 1,
	     "Unexpected EFI_MEMORY_DESCRIPTOR version %ld",
	     efi.memmap.desc_version);

	memblock_reserve(pmap, efi.memmap.nr_map * efi.memmap.desc_size);
	set_bit(EFI_PRESERVE_BS_REGIONS, &efi.flags);

	वापस 0;
पूर्ण

#घोषणा OVERFLOW_ADDR_SHIFT	(64 - EFI_PAGE_SHIFT)
#घोषणा OVERFLOW_ADDR_MASK	(U64_MAX << OVERFLOW_ADDR_SHIFT)
#घोषणा U64_HIGH_BIT		(~(U64_MAX >> 1))

अटल bool __init efi_memmap_entry_valid(स्थिर efi_memory_desc_t *md, पूर्णांक i)
अणु
	u64 end = (md->num_pages << EFI_PAGE_SHIFT) + md->phys_addr - 1;
	u64 end_hi = 0;
	अक्षर buf[64];

	अगर (md->num_pages == 0) अणु
		end = 0;
	पूर्ण अन्यथा अगर (md->num_pages > EFI_PAGES_MAX ||
		   EFI_PAGES_MAX - md->num_pages <
		   (md->phys_addr >> EFI_PAGE_SHIFT)) अणु
		end_hi = (md->num_pages & OVERFLOW_ADDR_MASK)
			>> OVERFLOW_ADDR_SHIFT;

		अगर ((md->phys_addr & U64_HIGH_BIT) && !(end & U64_HIGH_BIT))
			end_hi += 1;
	पूर्ण अन्यथा अणु
		वापस true;
	पूर्ण

	pr_warn_once(FW_BUG "Invalid EFI memory map entries:\n");

	अगर (end_hi) अणु
		pr_warn("mem%02u: %s range=[0x%016llx-0x%llx%016llx] (invalid)\n",
			i, efi_md_typeattr_क्रमmat(buf, माप(buf), md),
			md->phys_addr, end_hi, end);
	पूर्ण अन्यथा अणु
		pr_warn("mem%02u: %s range=[0x%016llx-0x%016llx] (invalid)\n",
			i, efi_md_typeattr_क्रमmat(buf, माप(buf), md),
			md->phys_addr, end);
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम __init efi_clean_memmap(व्योम)
अणु
	efi_memory_desc_t *out = efi.memmap.map;
	स्थिर efi_memory_desc_t *in = out;
	स्थिर efi_memory_desc_t *end = efi.memmap.map_end;
	पूर्णांक i, n_removal;

	क्रम (i = n_removal = 0; in < end; i++) अणु
		अगर (efi_memmap_entry_valid(in, i)) अणु
			अगर (out != in)
				स_नकल(out, in, efi.memmap.desc_size);
			out = (व्योम *)out + efi.memmap.desc_size;
		पूर्ण अन्यथा अणु
			n_removal++;
		पूर्ण
		in = (व्योम *)in + efi.memmap.desc_size;
	पूर्ण

	अगर (n_removal > 0) अणु
		काष्ठा efi_memory_map_data data = अणु
			.phys_map	= efi.memmap.phys_map,
			.desc_version	= efi.memmap.desc_version,
			.desc_size	= efi.memmap.desc_size,
			.size		= efi.memmap.desc_size * (efi.memmap.nr_map - n_removal),
			.flags		= 0,
		पूर्ण;

		pr_warn("Removing %d invalid memory map entries.\n", n_removal);
		efi_memmap_install(&data);
	पूर्ण
पूर्ण

व्योम __init efi_prपूर्णांक_memmap(व्योम)
अणु
	efi_memory_desc_t *md;
	पूर्णांक i = 0;

	क्रम_each_efi_memory_desc(md) अणु
		अक्षर buf[64];

		pr_info("mem%02u: %s range=[0x%016llx-0x%016llx] (%lluMB)\n",
			i++, efi_md_typeattr_क्रमmat(buf, माप(buf), md),
			md->phys_addr,
			md->phys_addr + (md->num_pages << EFI_PAGE_SHIFT) - 1,
			(md->num_pages >> (20 - EFI_PAGE_SHIFT)));
	पूर्ण
पूर्ण

अटल पूर्णांक __init efi_systab_init(अचिन्हित दीर्घ phys)
अणु
	पूर्णांक size = efi_enabled(EFI_64BIT) ? माप(efi_प्रणाली_table_64_t)
					  : माप(efi_प्रणाली_table_32_t);
	स्थिर efi_table_hdr_t *hdr;
	bool over4g = false;
	व्योम *p;
	पूर्णांक ret;

	hdr = p = early_memremap_ro(phys, size);
	अगर (p == शून्य) अणु
		pr_err("Couldn't map the system table!\n");
		वापस -ENOMEM;
	पूर्ण

	ret = efi_systab_check_header(hdr, 1);
	अगर (ret) अणु
		early_memunmap(p, size);
		वापस ret;
	पूर्ण

	अगर (efi_enabled(EFI_64BIT)) अणु
		स्थिर efi_प्रणाली_table_64_t *systab64 = p;

		efi_runसमय	= systab64->runसमय;
		over4g		= systab64->runसमय > U32_MAX;

		अगर (efi_setup) अणु
			काष्ठा efi_setup_data *data;

			data = early_memremap_ro(efi_setup, माप(*data));
			अगर (!data) अणु
				early_memunmap(p, size);
				वापस -ENOMEM;
			पूर्ण

			efi_fw_venकरोr		= (अचिन्हित दीर्घ)data->fw_venकरोr;
			efi_config_table	= (अचिन्हित दीर्घ)data->tables;

			over4g |= data->fw_venकरोr	> U32_MAX ||
				  data->tables		> U32_MAX;

			early_memunmap(data, माप(*data));
		पूर्ण अन्यथा अणु
			efi_fw_venकरोr		= systab64->fw_venकरोr;
			efi_config_table	= systab64->tables;

			over4g |= systab64->fw_venकरोr	> U32_MAX ||
				  systab64->tables	> U32_MAX;
		पूर्ण
		efi_nr_tables = systab64->nr_tables;
	पूर्ण अन्यथा अणु
		स्थिर efi_प्रणाली_table_32_t *systab32 = p;

		efi_fw_venकरोr		= systab32->fw_venकरोr;
		efi_runसमय		= systab32->runसमय;
		efi_config_table	= systab32->tables;
		efi_nr_tables		= systab32->nr_tables;
	पूर्ण

	efi.runसमय_version = hdr->revision;

	efi_systab_report_header(hdr, efi_fw_venकरोr);
	early_memunmap(p, size);

	अगर (IS_ENABLED(CONFIG_X86_32) && over4g) अणु
		pr_err("EFI data located above 4GB, disabling EFI.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init efi_config_init(स्थिर efi_config_table_type_t *arch_tables)
अणु
	व्योम *config_tables;
	पूर्णांक sz, ret;

	अगर (efi_nr_tables == 0)
		वापस 0;

	अगर (efi_enabled(EFI_64BIT))
		sz = माप(efi_config_table_64_t);
	अन्यथा
		sz = माप(efi_config_table_32_t);

	/*
	 * Let's see what config tables the firmware passed to us.
	 */
	config_tables = early_memremap(efi_config_table, efi_nr_tables * sz);
	अगर (config_tables == शून्य) अणु
		pr_err("Could not map Configuration table!\n");
		वापस -ENOMEM;
	पूर्ण

	ret = efi_config_parse_tables(config_tables, efi_nr_tables,
				      arch_tables);

	early_memunmap(config_tables, efi_nr_tables * sz);
	वापस ret;
पूर्ण

व्योम __init efi_init(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_X86_32) &&
	    (boot_params.efi_info.efi_systab_hi ||
	     boot_params.efi_info.efi_memmap_hi)) अणु
		pr_info("Table located above 4GB, disabling EFI.\n");
		वापस;
	पूर्ण

	efi_systab_phys = boot_params.efi_info.efi_systab |
			  ((__u64)boot_params.efi_info.efi_systab_hi << 32);

	अगर (efi_systab_init(efi_systab_phys))
		वापस;

	अगर (efi_reuse_config(efi_config_table, efi_nr_tables))
		वापस;

	अगर (efi_config_init(arch_tables))
		वापस;

	/*
	 * Note: We currently करोn't support runसमय services on an EFI
	 * that करोesn't match the kernel 32/64-bit mode.
	 */

	अगर (!efi_runसमय_supported())
		pr_info("No EFI runtime due to 32/64-bit mismatch with kernel\n");

	अगर (!efi_runसमय_supported() || efi_runसमय_disabled()) अणु
		efi_memmap_unmap();
		वापस;
	पूर्ण

	/* Parse the EFI Properties table अगर it exists */
	अगर (prop_phys != EFI_INVALID_TABLE_ADDR) अणु
		efi_properties_table_t *tbl;

		tbl = early_memremap_ro(prop_phys, माप(*tbl));
		अगर (tbl == शून्य) अणु
			pr_err("Could not map Properties table!\n");
		पूर्ण अन्यथा अणु
			अगर (tbl->memory_protection_attribute &
			    EFI_PROPERTIES_RUNTIME_MEMORY_PROTECTION_NON_EXECUTABLE_PE_DATA)
				set_bit(EFI_NX_PE_DATA, &efi.flags);

			early_memunmap(tbl, माप(*tbl));
		पूर्ण
	पूर्ण

	set_bit(EFI_RUNTIME_SERVICES, &efi.flags);
	efi_clean_memmap();

	अगर (efi_enabled(EFI_DBG))
		efi_prपूर्णांक_memmap();
पूर्ण

/* Merge contiguous regions of the same type and attribute */
अटल व्योम __init efi_merge_regions(व्योम)
अणु
	efi_memory_desc_t *md, *prev_md = शून्य;

	क्रम_each_efi_memory_desc(md) अणु
		u64 prev_size;

		अगर (!prev_md) अणु
			prev_md = md;
			जारी;
		पूर्ण

		अगर (prev_md->type != md->type ||
		    prev_md->attribute != md->attribute) अणु
			prev_md = md;
			जारी;
		पूर्ण

		prev_size = prev_md->num_pages << EFI_PAGE_SHIFT;

		अगर (md->phys_addr == (prev_md->phys_addr + prev_size)) अणु
			prev_md->num_pages += md->num_pages;
			md->type = EFI_RESERVED_TYPE;
			md->attribute = 0;
			जारी;
		पूर्ण
		prev_md = md;
	पूर्ण
पूर्ण

अटल व्योम *पुनः_स्मृति_pages(व्योम *old_memmap, पूर्णांक old_shअगरt)
अणु
	व्योम *ret;

	ret = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, old_shअगरt + 1);
	अगर (!ret)
		जाओ out;

	/*
	 * A first-समय allocation करोesn't have anything to copy.
	 */
	अगर (!old_memmap)
		वापस ret;

	स_नकल(ret, old_memmap, PAGE_SIZE << old_shअगरt);

out:
	मुक्त_pages((अचिन्हित दीर्घ)old_memmap, old_shअगरt);
	वापस ret;
पूर्ण

/*
 * Iterate the EFI memory map in reverse order because the regions
 * will be mapped top-करोwn. The end result is the same as अगर we had
 * mapped things क्रमward, but करोesn't require us to change the
 * existing implementation of efi_map_region().
 */
अटल अंतरभूत व्योम *efi_map_next_entry_reverse(व्योम *entry)
अणु
	/* Initial call */
	अगर (!entry)
		वापस efi.memmap.map_end - efi.memmap.desc_size;

	entry -= efi.memmap.desc_size;
	अगर (entry < efi.memmap.map)
		वापस शून्य;

	वापस entry;
पूर्ण

/*
 * efi_map_next_entry - Return the next EFI memory map descriptor
 * @entry: Previous EFI memory map descriptor
 *
 * This is a helper function to iterate over the EFI memory map, which
 * we करो in dअगरferent orders depending on the current configuration.
 *
 * To begin traversing the memory map @entry must be %शून्य.
 *
 * Returns %शून्य when we reach the end of the memory map.
 */
अटल व्योम *efi_map_next_entry(व्योम *entry)
अणु
	अगर (efi_enabled(EFI_64BIT)) अणु
		/*
		 * Starting in UEFI v2.5 the EFI_PROPERTIES_TABLE
		 * config table feature requires us to map all entries
		 * in the same order as they appear in the EFI memory
		 * map. That is to say, entry N must have a lower
		 * भव address than entry N+1. This is because the
		 * firmware toolchain leaves relative references in
		 * the code/data sections, which are split and become
		 * separate EFI memory regions. Mapping things
		 * out-of-order leads to the firmware accessing
		 * unmapped addresses.
		 *
		 * Since we need to map things this way whether or not
		 * the kernel actually makes use of
		 * EFI_PROPERTIES_TABLE, let's just चयन to this
		 * scheme by शेष क्रम 64-bit.
		 */
		वापस efi_map_next_entry_reverse(entry);
	पूर्ण

	/* Initial call */
	अगर (!entry)
		वापस efi.memmap.map;

	entry += efi.memmap.desc_size;
	अगर (entry >= efi.memmap.map_end)
		वापस शून्य;

	वापस entry;
पूर्ण

अटल bool should_map_region(efi_memory_desc_t *md)
अणु
	/*
	 * Runसमय regions always require runसमय mappings (obviously).
	 */
	अगर (md->attribute & EFI_MEMORY_RUNTIME)
		वापस true;

	/*
	 * 32-bit EFI करोesn't suffer from the bug that requires us to
	 * reserve boot services regions, and mixed mode support
	 * करोesn't exist क्रम 32-bit kernels.
	 */
	अगर (IS_ENABLED(CONFIG_X86_32))
		वापस false;

	/*
	 * EFI specअगरic purpose memory may be reserved by शेष
	 * depending on kernel config and boot options.
	 */
	अगर (md->type == EFI_CONVENTIONAL_MEMORY &&
	    efi_soft_reserve_enabled() &&
	    (md->attribute & EFI_MEMORY_SP))
		वापस false;

	/*
	 * Map all of RAM so that we can access arguments in the 1:1
	 * mapping when making EFI runसमय calls.
	 */
	अगर (efi_is_mixed()) अणु
		अगर (md->type == EFI_CONVENTIONAL_MEMORY ||
		    md->type == EFI_LOADER_DATA ||
		    md->type == EFI_LOADER_CODE)
			वापस true;
	पूर्ण

	/*
	 * Map boot services regions as a workaround क्रम buggy
	 * firmware that accesses them even when they shouldn't.
	 *
	 * See efi_अणुreserve,मुक्तपूर्ण_boot_services().
	 */
	अगर (md->type == EFI_BOOT_SERVICES_CODE ||
	    md->type == EFI_BOOT_SERVICES_DATA)
		वापस true;

	वापस false;
पूर्ण

/*
 * Map the efi memory ranges of the runसमय services and update new_mmap with
 * भव addresses.
 */
अटल व्योम * __init efi_map_regions(पूर्णांक *count, पूर्णांक *pg_shअगरt)
अणु
	व्योम *p, *new_memmap = शून्य;
	अचिन्हित दीर्घ left = 0;
	अचिन्हित दीर्घ desc_size;
	efi_memory_desc_t *md;

	desc_size = efi.memmap.desc_size;

	p = शून्य;
	जबतक ((p = efi_map_next_entry(p))) अणु
		md = p;

		अगर (!should_map_region(md))
			जारी;

		efi_map_region(md);

		अगर (left < desc_size) अणु
			new_memmap = पुनः_स्मृति_pages(new_memmap, *pg_shअगरt);
			अगर (!new_memmap)
				वापस शून्य;

			left += PAGE_SIZE << *pg_shअगरt;
			(*pg_shअगरt)++;
		पूर्ण

		स_नकल(new_memmap + (*count * desc_size), md, desc_size);

		left -= desc_size;
		(*count)++;
	पूर्ण

	वापस new_memmap;
पूर्ण

अटल व्योम __init kexec_enter_भव_mode(व्योम)
अणु
#अगर_घोषित CONFIG_KEXEC_CORE
	efi_memory_desc_t *md;
	अचिन्हित पूर्णांक num_pages;

	/*
	 * We करोn't do virtual mode, since we don't करो runसमय services, on
	 * non-native EFI.
	 */
	अगर (efi_is_mixed()) अणु
		efi_memmap_unmap();
		clear_bit(EFI_RUNTIME_SERVICES, &efi.flags);
		वापस;
	पूर्ण

	अगर (efi_alloc_page_tables()) अणु
		pr_err("Failed to allocate EFI page tables\n");
		clear_bit(EFI_RUNTIME_SERVICES, &efi.flags);
		वापस;
	पूर्ण

	/*
	* Map efi regions which were passed via setup_data. The virt_addr is a
	* fixed addr which was used in first kernel of a kexec boot.
	*/
	क्रम_each_efi_memory_desc(md)
		efi_map_region_fixed(md); /* FIXME: add error handling */

	/*
	 * Unरेजिस्टर the early EFI memmap from efi_init() and install
	 * the new EFI memory map.
	 */
	efi_memmap_unmap();

	अगर (efi_memmap_init_late(efi.memmap.phys_map,
				 efi.memmap.desc_size * efi.memmap.nr_map)) अणु
		pr_err("Failed to remap late EFI memory map\n");
		clear_bit(EFI_RUNTIME_SERVICES, &efi.flags);
		वापस;
	पूर्ण

	num_pages = ALIGN(efi.memmap.nr_map * efi.memmap.desc_size, PAGE_SIZE);
	num_pages >>= PAGE_SHIFT;

	अगर (efi_setup_page_tables(efi.memmap.phys_map, num_pages)) अणु
		clear_bit(EFI_RUNTIME_SERVICES, &efi.flags);
		वापस;
	पूर्ण

	efi_sync_low_kernel_mappings();
	efi_native_runसमय_setup();
#पूर्ण_अगर
पूर्ण

/*
 * This function will चयन the EFI runसमय services to भव mode.
 * Essentially, we look through the EFI memmap and map every region that
 * has the runसमय attribute bit set in its memory descriptor पूर्णांकo the
 * efi_pgd page table.
 *
 * The new method करोes a pagetable चयन in a preemption-safe manner
 * so that we're in a dअगरferent address space when calling a runसमय
 * function. For function arguments passing we करो copy the PUDs of the
 * kernel page table पूर्णांकo efi_pgd prior to each call.
 *
 * Specially क्रम kexec boot, efi runसमय maps in previous kernel should
 * be passed in via setup_data. In that हाल runसमय ranges will be mapped
 * to the same भव addresses as the first kernel, see
 * kexec_enter_भव_mode().
 */
अटल व्योम __init __efi_enter_भव_mode(व्योम)
अणु
	पूर्णांक count = 0, pg_shअगरt = 0;
	व्योम *new_memmap = शून्य;
	efi_status_t status;
	अचिन्हित दीर्घ pa;

	अगर (efi_alloc_page_tables()) अणु
		pr_err("Failed to allocate EFI page tables\n");
		जाओ err;
	पूर्ण

	efi_merge_regions();
	new_memmap = efi_map_regions(&count, &pg_shअगरt);
	अगर (!new_memmap) अणु
		pr_err("Error reallocating memory, EFI runtime non-functional!\n");
		जाओ err;
	पूर्ण

	pa = __pa(new_memmap);

	/*
	 * Unरेजिस्टर the early EFI memmap from efi_init() and install
	 * the new EFI memory map that we are about to pass to the
	 * firmware via SetVirtualAddressMap().
	 */
	efi_memmap_unmap();

	अगर (efi_memmap_init_late(pa, efi.memmap.desc_size * count)) अणु
		pr_err("Failed to remap late EFI memory map\n");
		जाओ err;
	पूर्ण

	अगर (efi_enabled(EFI_DBG)) अणु
		pr_info("EFI runtime memory map:\n");
		efi_prपूर्णांक_memmap();
	पूर्ण

	अगर (efi_setup_page_tables(pa, 1 << pg_shअगरt))
		जाओ err;

	efi_sync_low_kernel_mappings();

	status = efi_set_भव_address_map(efi.memmap.desc_size * count,
					     efi.memmap.desc_size,
					     efi.memmap.desc_version,
					     (efi_memory_desc_t *)pa,
					     efi_systab_phys);
	अगर (status != EFI_SUCCESS) अणु
		pr_err("Unable to switch EFI into virtual mode (status=%lx)!\n",
		       status);
		जाओ err;
	पूर्ण

	efi_check_क्रम_embedded_firmwares();
	efi_मुक्त_boot_services();

	अगर (!efi_is_mixed())
		efi_native_runसमय_setup();
	अन्यथा
		efi_thunk_runसमय_setup();

	/*
	 * Apply more restrictive page table mapping attributes now that
	 * SVAM() has been called and the firmware has perक्रमmed all
	 * necessary relocation fixups क्रम the new भव addresses.
	 */
	efi_runसमय_update_mappings();

	/* clean DUMMY object */
	efi_delete_dummy_variable();
	वापस;

err:
	clear_bit(EFI_RUNTIME_SERVICES, &efi.flags);
पूर्ण

व्योम __init efi_enter_भव_mode(व्योम)
अणु
	अगर (efi_enabled(EFI_PARAVIRT))
		वापस;

	efi.runसमय = (efi_runसमय_services_t *)efi_runसमय;

	अगर (efi_setup)
		kexec_enter_भव_mode();
	अन्यथा
		__efi_enter_भव_mode();

	efi_dump_pagetable();
पूर्ण

bool efi_is_table_address(अचिन्हित दीर्घ phys_addr)
अणु
	अचिन्हित पूर्णांक i;

	अगर (phys_addr == EFI_INVALID_TABLE_ADDR)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(efi_tables); i++)
		अगर (*(efi_tables[i]) == phys_addr)
			वापस true;

	वापस false;
पूर्ण

अक्षर *efi_systab_show_arch(अक्षर *str)
अणु
	अगर (uga_phys != EFI_INVALID_TABLE_ADDR)
		str += प्र_लिखो(str, "UGA=0x%lx\n", uga_phys);
	वापस str;
पूर्ण

#घोषणा EFI_FIELD(var) efi_ ## var

#घोषणा EFI_ATTR_SHOW(name) \
अटल sमाप_प्रकार name##_show(काष्ठा kobject *kobj, \
				काष्ठा kobj_attribute *attr, अक्षर *buf) \
अणु \
	वापस प्र_लिखो(buf, "0x%lx\n", EFI_FIELD(name)); \
पूर्ण

EFI_ATTR_SHOW(fw_venकरोr);
EFI_ATTR_SHOW(runसमय);
EFI_ATTR_SHOW(config_table);

काष्ठा kobj_attribute efi_attr_fw_venकरोr = __ATTR_RO(fw_venकरोr);
काष्ठा kobj_attribute efi_attr_runसमय = __ATTR_RO(runसमय);
काष्ठा kobj_attribute efi_attr_config_table = __ATTR_RO(config_table);

umode_t efi_attr_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक n)
अणु
	अगर (attr == &efi_attr_fw_venकरोr.attr) अणु
		अगर (efi_enabled(EFI_PARAVIRT) ||
				efi_fw_venकरोr == EFI_INVALID_TABLE_ADDR)
			वापस 0;
	पूर्ण अन्यथा अगर (attr == &efi_attr_runसमय.attr) अणु
		अगर (efi_runसमय == EFI_INVALID_TABLE_ADDR)
			वापस 0;
	पूर्ण अन्यथा अगर (attr == &efi_attr_config_table.attr) अणु
		अगर (efi_config_table == EFI_INVALID_TABLE_ADDR)
			वापस 0;
	पूर्ण
	वापस attr->mode;
पूर्ण
