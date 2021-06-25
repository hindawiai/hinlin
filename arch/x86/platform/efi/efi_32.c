<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Extensible Firmware Interface
 *
 * Based on Extensible Firmware Interface Specअगरication version 1.0
 *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999-2002 Hewlett-Packard Co.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
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

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/efi.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/efi.h>

व्योम __init efi_map_region(efi_memory_desc_t *md)
अणु
	u64 start_pfn, end_pfn, end;
	अचिन्हित दीर्घ size;
	व्योम *va;

	start_pfn	= PFN_DOWN(md->phys_addr);
	size		= md->num_pages << PAGE_SHIFT;
	end		= md->phys_addr + size;
	end_pfn 	= PFN_UP(end);

	अगर (pfn_range_is_mapped(start_pfn, end_pfn)) अणु
		va = __va(md->phys_addr);

		अगर (!(md->attribute & EFI_MEMORY_WB))
			set_memory_uc((अचिन्हित दीर्घ)va, md->num_pages);
	पूर्ण अन्यथा अणु
		va = ioremap_cache(md->phys_addr, size);
	पूर्ण

	md->virt_addr = (अचिन्हित दीर्घ)va;
	अगर (!va)
		pr_err("ioremap of 0x%llX failed!\n", md->phys_addr);
पूर्ण

/*
 * To make EFI call EFI runसमय service in physical addressing mode we need
 * prolog/epilog beक्रमe/after the invocation to claim the EFI runसमय service
 * handler exclusively and to duplicate a memory mapping in low memory space,
 * say 0 - 3G.
 */

पूर्णांक __init efi_alloc_page_tables(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम efi_sync_low_kernel_mappings(व्योम) अणुपूर्ण

व्योम __init efi_dump_pagetable(व्योम)
अणु
#अगर_घोषित CONFIG_EFI_PGT_DUMP
	ptdump_walk_pgd_level(शून्य, &init_mm);
#पूर्ण_अगर
पूर्ण

पूर्णांक __init efi_setup_page_tables(अचिन्हित दीर्घ pa_memmap, अचिन्हित num_pages)
अणु
	वापस 0;
पूर्ण

व्योम __init efi_map_region_fixed(efi_memory_desc_t *md) अणुपूर्ण
व्योम __init parse_efi_setup(u64 phys_addr, u32 data_len) अणुपूर्ण

efi_status_t efi_call_svam(efi_runसमय_services_t * स्थिर *,
			   u32, u32, u32, व्योम *, u32);

efi_status_t __init efi_set_भव_address_map(अचिन्हित दीर्घ memory_map_size,
						अचिन्हित दीर्घ descriptor_size,
						u32 descriptor_version,
						efi_memory_desc_t *भव_map,
						अचिन्हित दीर्घ systab_phys)
अणु
	स्थिर efi_प्रणाली_table_t *systab = (efi_प्रणाली_table_t *)systab_phys;
	काष्ठा desc_ptr gdt_descr;
	efi_status_t status;
	अचिन्हित दीर्घ flags;
	pgd_t *save_pgd;

	/* Current pgd is swapper_pg_dir, we'll restore it later: */
	save_pgd = swapper_pg_dir;
	load_cr3(initial_page_table);
	__flush_tlb_all();

	gdt_descr.address = get_cpu_gdt_paddr(0);
	gdt_descr.size = GDT_SIZE - 1;
	load_gdt(&gdt_descr);

	/* Disable पूर्णांकerrupts around EFI calls: */
	local_irq_save(flags);
	status = efi_call_svam(&systab->runसमय,
			       memory_map_size, descriptor_size,
			       descriptor_version, भव_map,
			       __pa(&efi.runसमय));
	local_irq_restore(flags);

	load_fixmap_gdt(0);
	load_cr3(save_pgd);
	__flush_tlb_all();

	वापस status;
पूर्ण

व्योम __init efi_runसमय_update_mappings(व्योम)
अणु
	अगर (__supported_pte_mask & _PAGE_NX) अणु
		efi_memory_desc_t *md;

		/* Make EFI runसमय service code area executable */
		क्रम_each_efi_memory_desc(md) अणु
			अगर (md->type != EFI_RUNTIME_SERVICES_CODE)
				जारी;

			set_memory_x(md->virt_addr, md->num_pages);
		पूर्ण
	पूर्ण
पूर्ण
