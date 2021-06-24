<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * x86_64 specअगरic EFI support functions
 * Based on Extensible Firmware Interface Specअगरication version 1.0
 *
 * Copyright (C) 2005-2008 Intel Co.
 *	Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *	Bibo Mao <bibo.mao@पूर्णांकel.com>
 *	Chandramouli Narayanan <mouli@linux.पूर्णांकel.com>
 *	Huang Ying <ying.huang@पूर्णांकel.com>
 *
 * Code to convert EFI to E820 map has been implemented in elilo bootloader
 * based on a EFI patch by Edgar Hucek. Based on the E820 map, the page table
 * is setup appropriately क्रम EFI runसमय code.
 * - mouli 06/14/2007.
 *
 */

#घोषणा pr_fmt(fmt) "efi: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/memblock.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/efi.h>
#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/ucs2_माला.स>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/sched/task.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sev.h>

/*
 * We allocate runसमय services regions top-करोwn, starting from -4G, i.e.
 * 0xffff_ffff_0000_0000 and limit EFI VA mapping space to 64G.
 */
अटल u64 efi_va = EFI_VA_START;
अटल काष्ठा mm_काष्ठा *efi_prev_mm;

/*
 * We need our own copy of the higher levels of the page tables
 * because we want to aव्योम inserting EFI region mappings (EFI_VA_END
 * to EFI_VA_START) पूर्णांकo the standard kernel page tables. Everything
 * अन्यथा can be shared, see efi_sync_low_kernel_mappings().
 *
 * We करोn't want the pgd on the pgd_list and cannot use pgd_alloc() क्रम the
 * allocation.
 */
पूर्णांक __init efi_alloc_page_tables(व्योम)
अणु
	pgd_t *pgd, *efi_pgd;
	p4d_t *p4d;
	pud_t *pud;
	gfp_t gfp_mask;

	gfp_mask = GFP_KERNEL | __GFP_ZERO;
	efi_pgd = (pgd_t *)__get_मुक्त_pages(gfp_mask, PGD_ALLOCATION_ORDER);
	अगर (!efi_pgd)
		जाओ fail;

	pgd = efi_pgd + pgd_index(EFI_VA_END);
	p4d = p4d_alloc(&init_mm, pgd, EFI_VA_END);
	अगर (!p4d)
		जाओ मुक्त_pgd;

	pud = pud_alloc(&init_mm, p4d, EFI_VA_END);
	अगर (!pud)
		जाओ मुक्त_p4d;

	efi_mm.pgd = efi_pgd;
	mm_init_cpumask(&efi_mm);
	init_new_context(शून्य, &efi_mm);

	वापस 0;

मुक्त_p4d:
	अगर (pgtable_l5_enabled())
		मुक्त_page((अचिन्हित दीर्घ)pgd_page_vaddr(*pgd));
मुक्त_pgd:
	मुक्त_pages((अचिन्हित दीर्घ)efi_pgd, PGD_ALLOCATION_ORDER);
fail:
	वापस -ENOMEM;
पूर्ण

/*
 * Add low kernel mappings क्रम passing arguments to EFI functions.
 */
व्योम efi_sync_low_kernel_mappings(व्योम)
अणु
	अचिन्हित num_entries;
	pgd_t *pgd_k, *pgd_efi;
	p4d_t *p4d_k, *p4d_efi;
	pud_t *pud_k, *pud_efi;
	pgd_t *efi_pgd = efi_mm.pgd;

	pgd_efi = efi_pgd + pgd_index(PAGE_OFFSET);
	pgd_k = pgd_offset_k(PAGE_OFFSET);

	num_entries = pgd_index(EFI_VA_END) - pgd_index(PAGE_OFFSET);
	स_नकल(pgd_efi, pgd_k, माप(pgd_t) * num_entries);

	pgd_efi = efi_pgd + pgd_index(EFI_VA_END);
	pgd_k = pgd_offset_k(EFI_VA_END);
	p4d_efi = p4d_offset(pgd_efi, 0);
	p4d_k = p4d_offset(pgd_k, 0);

	num_entries = p4d_index(EFI_VA_END);
	स_नकल(p4d_efi, p4d_k, माप(p4d_t) * num_entries);

	/*
	 * We share all the PUD entries apart from those that map the
	 * EFI regions. Copy around them.
	 */
	BUILD_BUG_ON((EFI_VA_START & ~PUD_MASK) != 0);
	BUILD_BUG_ON((EFI_VA_END & ~PUD_MASK) != 0);

	p4d_efi = p4d_offset(pgd_efi, EFI_VA_END);
	p4d_k = p4d_offset(pgd_k, EFI_VA_END);
	pud_efi = pud_offset(p4d_efi, 0);
	pud_k = pud_offset(p4d_k, 0);

	num_entries = pud_index(EFI_VA_END);
	स_नकल(pud_efi, pud_k, माप(pud_t) * num_entries);

	pud_efi = pud_offset(p4d_efi, EFI_VA_START);
	pud_k = pud_offset(p4d_k, EFI_VA_START);

	num_entries = PTRS_PER_PUD - pud_index(EFI_VA_START);
	स_नकल(pud_efi, pud_k, माप(pud_t) * num_entries);
पूर्ण

/*
 * Wrapper क्रम slow_virt_to_phys() that handles शून्य addresses.
 */
अटल अंतरभूत phys_addr_t
virt_to_phys_or_null_size(व्योम *va, अचिन्हित दीर्घ size)
अणु
	phys_addr_t pa;

	अगर (!va)
		वापस 0;

	अगर (virt_addr_valid(va))
		वापस virt_to_phys(va);

	pa = slow_virt_to_phys(va);

	/* check अगर the object crosses a page boundary */
	अगर (WARN_ON((pa ^ (pa + size - 1)) & PAGE_MASK))
		वापस 0;

	वापस pa;
पूर्ण

#घोषणा virt_to_phys_or_null(addr)				\
	virt_to_phys_or_null_size((addr), माप(*(addr)))

पूर्णांक __init efi_setup_page_tables(अचिन्हित दीर्घ pa_memmap, अचिन्हित num_pages)
अणु
	अचिन्हित दीर्घ pfn, text, pf, rodata;
	काष्ठा page *page;
	अचिन्हित npages;
	pgd_t *pgd = efi_mm.pgd;

	/*
	 * It can happen that the physical address of new_memmap lands in memory
	 * which is not mapped in the EFI page table. Thereक्रमe we need to go
	 * and ident-map those pages containing the map beक्रमe calling
	 * phys_efi_set_भव_address_map().
	 */
	pfn = pa_memmap >> PAGE_SHIFT;
	pf = _PAGE_NX | _PAGE_RW | _PAGE_ENC;
	अगर (kernel_map_pages_in_pgd(pgd, pfn, pa_memmap, num_pages, pf)) अणु
		pr_err("Error ident-mapping new memmap (0x%lx)!\n", pa_memmap);
		वापस 1;
	पूर्ण

	/*
	 * Certain firmware versions are way too senसमयntal and still believe
	 * they are exclusive and unquestionable owners of the first physical page,
	 * even though they explicitly mark it as EFI_CONVENTIONAL_MEMORY
	 * (but then ग_लिखो-access it later during SetVirtualAddressMap()).
	 *
	 * Create a 1:1 mapping क्रम this page, to aव्योम triple faults during early
	 * boot with such firmware. We are मुक्त to hand this page to the BIOS,
	 * as trim_bios_range() will reserve the first page and isolate it away
	 * from memory allocators anyway.
	 */
	अगर (kernel_map_pages_in_pgd(pgd, 0x0, 0x0, 1, pf)) अणु
		pr_err("Failed to create 1:1 mapping for the first page!\n");
		वापस 1;
	पूर्ण

	/*
	 * When SEV-ES is active, the GHCB as set by the kernel will be used
	 * by firmware. Create a 1:1 unencrypted mapping क्रम each GHCB.
	 */
	अगर (sev_es_efi_map_ghcbs(pgd)) अणु
		pr_err("Failed to create 1:1 mapping for the GHCBs!\n");
		वापस 1;
	पूर्ण

	/*
	 * When making calls to the firmware everything needs to be 1:1
	 * mapped and addressable with 32-bit poपूर्णांकers. Map the kernel
	 * text and allocate a new stack because we can't rely on the
	 * stack poपूर्णांकer being < 4GB.
	 */
	अगर (!efi_is_mixed())
		वापस 0;

	page = alloc_page(GFP_KERNEL|__GFP_DMA32);
	अगर (!page) अणु
		pr_err("Unable to allocate EFI runtime stack < 4GB\n");
		वापस 1;
	पूर्ण

	efi_mixed_mode_stack_pa = page_to_phys(page + 1); /* stack grows करोwn */

	npages = (_etext - _text) >> PAGE_SHIFT;
	text = __pa(_text);
	pfn = text >> PAGE_SHIFT;

	pf = _PAGE_ENC;
	अगर (kernel_map_pages_in_pgd(pgd, pfn, text, npages, pf)) अणु
		pr_err("Failed to map kernel text 1:1\n");
		वापस 1;
	पूर्ण

	npages = (__end_rodata - __start_rodata) >> PAGE_SHIFT;
	rodata = __pa(__start_rodata);
	pfn = rodata >> PAGE_SHIFT;

	pf = _PAGE_NX | _PAGE_ENC;
	अगर (kernel_map_pages_in_pgd(pgd, pfn, rodata, npages, pf)) अणु
		pr_err("Failed to map kernel rodata 1:1\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init __map_region(efi_memory_desc_t *md, u64 va)
अणु
	अचिन्हित दीर्घ flags = _PAGE_RW;
	अचिन्हित दीर्घ pfn;
	pgd_t *pgd = efi_mm.pgd;

	/*
	 * EFI_RUNTIME_SERVICES_CODE regions typically cover PE/COFF
	 * executable images in memory that consist of both R-X and
	 * RW- sections, so we cannot apply पढ़ो-only or non-exec
	 * permissions just yet. However, modern EFI प्रणालीs provide
	 * a memory attributes table that describes those sections
	 * with the appropriate restricted permissions, which are
	 * applied in efi_runसमय_update_mappings() below. All other
	 * regions can be mapped non-executable at this poपूर्णांक, with
	 * the exception of boot services code regions, but those will
	 * be unmapped again entirely in efi_मुक्त_boot_services().
	 */
	अगर (md->type != EFI_BOOT_SERVICES_CODE &&
	    md->type != EFI_RUNTIME_SERVICES_CODE)
		flags |= _PAGE_NX;

	अगर (!(md->attribute & EFI_MEMORY_WB))
		flags |= _PAGE_PCD;

	अगर (sev_active() && md->type != EFI_MEMORY_MAPPED_IO)
		flags |= _PAGE_ENC;

	pfn = md->phys_addr >> PAGE_SHIFT;
	अगर (kernel_map_pages_in_pgd(pgd, pfn, va, md->num_pages, flags))
		pr_warn("Error mapping PA 0x%llx -> VA 0x%llx!\n",
			   md->phys_addr, va);
पूर्ण

व्योम __init efi_map_region(efi_memory_desc_t *md)
अणु
	अचिन्हित दीर्घ size = md->num_pages << PAGE_SHIFT;
	u64 pa = md->phys_addr;

	/*
	 * Make sure the 1:1 mappings are present as a catch-all क्रम b0rked
	 * firmware which करोesn't update all पूर्णांकernal poपूर्णांकers after चयनing
	 * to भव mode and would otherwise crap on us.
	 */
	__map_region(md, md->phys_addr);

	/*
	 * Enक्रमce the 1:1 mapping as the शेष भव address when
	 * booting in EFI mixed mode, because even though we may be
	 * running a 64-bit kernel, the firmware may only be 32-bit.
	 */
	अगर (efi_is_mixed()) अणु
		md->virt_addr = md->phys_addr;
		वापस;
	पूर्ण

	efi_va -= size;

	/* Is PA 2M-aligned? */
	अगर (!(pa & (PMD_SIZE - 1))) अणु
		efi_va &= PMD_MASK;
	पूर्ण अन्यथा अणु
		u64 pa_offset = pa & (PMD_SIZE - 1);
		u64 prev_va = efi_va;

		/* get us the same offset within this 2M page */
		efi_va = (efi_va & PMD_MASK) + pa_offset;

		अगर (efi_va > prev_va)
			efi_va -= PMD_SIZE;
	पूर्ण

	अगर (efi_va < EFI_VA_END) अणु
		pr_warn(FW_WARN "VA address range overflow!\n");
		वापस;
	पूर्ण

	/* Do the VA map */
	__map_region(md, efi_va);
	md->virt_addr = efi_va;
पूर्ण

/*
 * kexec kernel will use efi_map_region_fixed to map efi runसमय memory ranges.
 * md->virt_addr is the original भव address which had been mapped in kexec
 * 1st kernel.
 */
व्योम __init efi_map_region_fixed(efi_memory_desc_t *md)
अणु
	__map_region(md, md->phys_addr);
	__map_region(md, md->virt_addr);
पूर्ण

व्योम __init parse_efi_setup(u64 phys_addr, u32 data_len)
अणु
	efi_setup = phys_addr + माप(काष्ठा setup_data);
पूर्ण

अटल पूर्णांक __init efi_update_mappings(efi_memory_desc_t *md, अचिन्हित दीर्घ pf)
अणु
	अचिन्हित दीर्घ pfn;
	pgd_t *pgd = efi_mm.pgd;
	पूर्णांक err1, err2;

	/* Update the 1:1 mapping */
	pfn = md->phys_addr >> PAGE_SHIFT;
	err1 = kernel_map_pages_in_pgd(pgd, pfn, md->phys_addr, md->num_pages, pf);
	अगर (err1) अणु
		pr_err("Error while updating 1:1 mapping PA 0x%llx -> VA 0x%llx!\n",
			   md->phys_addr, md->virt_addr);
	पूर्ण

	err2 = kernel_map_pages_in_pgd(pgd, pfn, md->virt_addr, md->num_pages, pf);
	अगर (err2) अणु
		pr_err("Error while updating VA mapping PA 0x%llx -> VA 0x%llx!\n",
			   md->phys_addr, md->virt_addr);
	पूर्ण

	वापस err1 || err2;
पूर्ण

अटल पूर्णांक __init efi_update_mem_attr(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md)
अणु
	अचिन्हित दीर्घ pf = 0;

	अगर (md->attribute & EFI_MEMORY_XP)
		pf |= _PAGE_NX;

	अगर (!(md->attribute & EFI_MEMORY_RO))
		pf |= _PAGE_RW;

	अगर (sev_active())
		pf |= _PAGE_ENC;

	वापस efi_update_mappings(md, pf);
पूर्ण

व्योम __init efi_runसमय_update_mappings(व्योम)
अणु
	efi_memory_desc_t *md;

	/*
	 * Use the EFI Memory Attribute Table क्रम mapping permissions अगर it
	 * exists, since it is पूर्णांकended to supersede EFI_PROPERTIES_TABLE.
	 */
	अगर (efi_enabled(EFI_MEM_ATTR)) अणु
		efi_memattr_apply_permissions(शून्य, efi_update_mem_attr);
		वापस;
	पूर्ण

	/*
	 * EFI_MEMORY_ATTRIBUTES_TABLE is पूर्णांकended to replace
	 * EFI_PROPERTIES_TABLE. So, use EFI_PROPERTIES_TABLE to update
	 * permissions only अगर EFI_MEMORY_ATTRIBUTES_TABLE is not
	 * published by the firmware. Even अगर we find a buggy implementation of
	 * EFI_MEMORY_ATTRIBUTES_TABLE, करोn't fall back to
	 * EFI_PROPERTIES_TABLE, because of the same reason.
	 */

	अगर (!efi_enabled(EFI_NX_PE_DATA))
		वापस;

	क्रम_each_efi_memory_desc(md) अणु
		अचिन्हित दीर्घ pf = 0;

		अगर (!(md->attribute & EFI_MEMORY_RUNTIME))
			जारी;

		अगर (!(md->attribute & EFI_MEMORY_WB))
			pf |= _PAGE_PCD;

		अगर ((md->attribute & EFI_MEMORY_XP) ||
			(md->type == EFI_RUNTIME_SERVICES_DATA))
			pf |= _PAGE_NX;

		अगर (!(md->attribute & EFI_MEMORY_RO) &&
			(md->type != EFI_RUNTIME_SERVICES_CODE))
			pf |= _PAGE_RW;

		अगर (sev_active())
			pf |= _PAGE_ENC;

		efi_update_mappings(md, pf);
	पूर्ण
पूर्ण

व्योम __init efi_dump_pagetable(व्योम)
अणु
#अगर_घोषित CONFIG_EFI_PGT_DUMP
	ptdump_walk_pgd_level(शून्य, &efi_mm);
#पूर्ण_अगर
पूर्ण

/*
 * Makes the calling thपढ़ो चयन to/from efi_mm context. Can be used
 * in a kernel thपढ़ो and user context. Preemption needs to reमुख्य disabled
 * जबतक the EFI-mm is borrowed. mmgrab()/mmdrop() is not used because the mm
 * can not change under us.
 * It should be ensured that there are no concurrent calls to this function.
 */
व्योम efi_enter_mm(व्योम)
अणु
	efi_prev_mm = current->active_mm;
	current->active_mm = &efi_mm;
	चयन_mm(efi_prev_mm, &efi_mm, शून्य);
पूर्ण

व्योम efi_leave_mm(व्योम)
अणु
	current->active_mm = efi_prev_mm;
	चयन_mm(&efi_mm, efi_prev_mm, शून्य);
पूर्ण

अटल DEFINE_SPINLOCK(efi_runसमय_lock);

/*
 * DS and ES contain user values.  We need to save them.
 * The 32-bit EFI code needs a valid DS, ES, and SS.  There's no
 * need to save the old SS: __KERNEL_DS is always acceptable.
 */
#घोषणा __efi_thunk(func, ...)						\
(अणु									\
	अचिन्हित लघु __ds, __es;					\
	efi_status_t ____s;						\
									\
	savesegment(ds, __ds);						\
	savesegment(es, __es);						\
									\
	loadsegment(ss, __KERNEL_DS);					\
	loadsegment(ds, __KERNEL_DS);					\
	loadsegment(es, __KERNEL_DS);					\
									\
	____s = efi64_thunk(efi.runसमय->mixed_mode.func, __VA_ARGS__);	\
									\
	loadsegment(ds, __ds);						\
	loadsegment(es, __es);						\
									\
	____s ^= (____s & BIT(31)) | (____s & BIT_ULL(31)) << 32;	\
	____s;								\
पूर्ण)

/*
 * Switch to the EFI page tables early so that we can access the 1:1
 * runसमय services mappings which are not mapped in any other page
 * tables.
 *
 * Also, disable पूर्णांकerrupts because the IDT poपूर्णांकs to 64-bit handlers,
 * which aren't going to function correctly when we चयन to 32-bit.
 */
#घोषणा efi_thunk(func...)						\
(अणु									\
	efi_status_t __s;						\
									\
	arch_efi_call_virt_setup();					\
									\
	__s = __efi_thunk(func);					\
									\
	arch_efi_call_virt_tearकरोwn();					\
									\
	__s;								\
पूर्ण)

अटल efi_status_t __init __no_sanitize_address
efi_thunk_set_भव_address_map(अचिन्हित दीर्घ memory_map_size,
				  अचिन्हित दीर्घ descriptor_size,
				  u32 descriptor_version,
				  efi_memory_desc_t *भव_map)
अणु
	efi_status_t status;
	अचिन्हित दीर्घ flags;

	efi_sync_low_kernel_mappings();
	local_irq_save(flags);

	efi_enter_mm();

	status = __efi_thunk(set_भव_address_map, memory_map_size,
			     descriptor_size, descriptor_version, भव_map);

	efi_leave_mm();
	local_irq_restore(flags);

	वापस status;
पूर्ण

अटल efi_status_t efi_thunk_get_समय(efi_समय_प्रकार *पंचांग, efi_समय_cap_t *tc)
अणु
	वापस EFI_UNSUPPORTED;
पूर्ण

अटल efi_status_t efi_thunk_set_समय(efi_समय_प्रकार *पंचांग)
अणु
	वापस EFI_UNSUPPORTED;
पूर्ण

अटल efi_status_t
efi_thunk_get_wakeup_समय(efi_bool_t *enabled, efi_bool_t *pending,
			  efi_समय_प्रकार *पंचांग)
अणु
	वापस EFI_UNSUPPORTED;
पूर्ण

अटल efi_status_t
efi_thunk_set_wakeup_समय(efi_bool_t enabled, efi_समय_प्रकार *पंचांग)
अणु
	वापस EFI_UNSUPPORTED;
पूर्ण

अटल अचिन्हित दीर्घ efi_name_size(efi_अक्षर16_t *name)
अणु
	वापस ucs2_strsize(name, EFI_VAR_NAME_LEN) + 1;
पूर्ण

अटल efi_status_t
efi_thunk_get_variable(efi_अक्षर16_t *name, efi_guid_t *venकरोr,
		       u32 *attr, अचिन्हित दीर्घ *data_size, व्योम *data)
अणु
	u8 buf[24] __aligned(8);
	efi_guid_t *vnd = PTR_ALIGN((efi_guid_t *)buf, माप(*vnd));
	efi_status_t status;
	u32 phys_name, phys_venकरोr, phys_attr;
	u32 phys_data_size, phys_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&efi_runसमय_lock, flags);

	*vnd = *venकरोr;

	phys_data_size = virt_to_phys_or_null(data_size);
	phys_venकरोr = virt_to_phys_or_null(vnd);
	phys_name = virt_to_phys_or_null_size(name, efi_name_size(name));
	phys_attr = virt_to_phys_or_null(attr);
	phys_data = virt_to_phys_or_null_size(data, *data_size);

	अगर (!phys_name || (data && !phys_data))
		status = EFI_INVALID_PARAMETER;
	अन्यथा
		status = efi_thunk(get_variable, phys_name, phys_venकरोr,
				   phys_attr, phys_data_size, phys_data);

	spin_unlock_irqrestore(&efi_runसमय_lock, flags);

	वापस status;
पूर्ण

अटल efi_status_t
efi_thunk_set_variable(efi_अक्षर16_t *name, efi_guid_t *venकरोr,
		       u32 attr, अचिन्हित दीर्घ data_size, व्योम *data)
अणु
	u8 buf[24] __aligned(8);
	efi_guid_t *vnd = PTR_ALIGN((efi_guid_t *)buf, माप(*vnd));
	u32 phys_name, phys_venकरोr, phys_data;
	efi_status_t status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&efi_runसमय_lock, flags);

	*vnd = *venकरोr;

	phys_name = virt_to_phys_or_null_size(name, efi_name_size(name));
	phys_venकरोr = virt_to_phys_or_null(vnd);
	phys_data = virt_to_phys_or_null_size(data, data_size);

	अगर (!phys_name || (data && !phys_data))
		status = EFI_INVALID_PARAMETER;
	अन्यथा
		status = efi_thunk(set_variable, phys_name, phys_venकरोr,
				   attr, data_size, phys_data);

	spin_unlock_irqrestore(&efi_runसमय_lock, flags);

	वापस status;
पूर्ण

अटल efi_status_t
efi_thunk_set_variable_nonblocking(efi_अक्षर16_t *name, efi_guid_t *venकरोr,
				   u32 attr, अचिन्हित दीर्घ data_size,
				   व्योम *data)
अणु
	u8 buf[24] __aligned(8);
	efi_guid_t *vnd = PTR_ALIGN((efi_guid_t *)buf, माप(*vnd));
	u32 phys_name, phys_venकरोr, phys_data;
	efi_status_t status;
	अचिन्हित दीर्घ flags;

	अगर (!spin_trylock_irqsave(&efi_runसमय_lock, flags))
		वापस EFI_NOT_READY;

	*vnd = *venकरोr;

	phys_name = virt_to_phys_or_null_size(name, efi_name_size(name));
	phys_venकरोr = virt_to_phys_or_null(vnd);
	phys_data = virt_to_phys_or_null_size(data, data_size);

	अगर (!phys_name || (data && !phys_data))
		status = EFI_INVALID_PARAMETER;
	अन्यथा
		status = efi_thunk(set_variable, phys_name, phys_venकरोr,
				   attr, data_size, phys_data);

	spin_unlock_irqrestore(&efi_runसमय_lock, flags);

	वापस status;
पूर्ण

अटल efi_status_t
efi_thunk_get_next_variable(अचिन्हित दीर्घ *name_size,
			    efi_अक्षर16_t *name,
			    efi_guid_t *venकरोr)
अणु
	u8 buf[24] __aligned(8);
	efi_guid_t *vnd = PTR_ALIGN((efi_guid_t *)buf, माप(*vnd));
	efi_status_t status;
	u32 phys_name_size, phys_name, phys_venकरोr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&efi_runसमय_lock, flags);

	*vnd = *venकरोr;

	phys_name_size = virt_to_phys_or_null(name_size);
	phys_venकरोr = virt_to_phys_or_null(vnd);
	phys_name = virt_to_phys_or_null_size(name, *name_size);

	अगर (!phys_name)
		status = EFI_INVALID_PARAMETER;
	अन्यथा
		status = efi_thunk(get_next_variable, phys_name_size,
				   phys_name, phys_venकरोr);

	spin_unlock_irqrestore(&efi_runसमय_lock, flags);

	*venकरोr = *vnd;
	वापस status;
पूर्ण

अटल efi_status_t
efi_thunk_get_next_high_mono_count(u32 *count)
अणु
	वापस EFI_UNSUPPORTED;
पूर्ण

अटल व्योम
efi_thunk_reset_प्रणाली(पूर्णांक reset_type, efi_status_t status,
		       अचिन्हित दीर्घ data_size, efi_अक्षर16_t *data)
अणु
	u32 phys_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&efi_runसमय_lock, flags);

	phys_data = virt_to_phys_or_null_size(data, data_size);

	efi_thunk(reset_प्रणाली, reset_type, status, data_size, phys_data);

	spin_unlock_irqrestore(&efi_runसमय_lock, flags);
पूर्ण

अटल efi_status_t
efi_thunk_update_capsule(efi_capsule_header_t **capsules,
			 अचिन्हित दीर्घ count, अचिन्हित दीर्घ sg_list)
अणु
	/*
	 * To properly support this function we would need to repackage
	 * 'capsules' because the firmware doesn't understand 64-bit
	 * poपूर्णांकers.
	 */
	वापस EFI_UNSUPPORTED;
पूर्ण

अटल efi_status_t
efi_thunk_query_variable_info(u32 attr, u64 *storage_space,
			      u64 *reमुख्यing_space,
			      u64 *max_variable_size)
अणु
	efi_status_t status;
	u32 phys_storage, phys_reमुख्यing, phys_max;
	अचिन्हित दीर्घ flags;

	अगर (efi.runसमय_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		वापस EFI_UNSUPPORTED;

	spin_lock_irqsave(&efi_runसमय_lock, flags);

	phys_storage = virt_to_phys_or_null(storage_space);
	phys_reमुख्यing = virt_to_phys_or_null(reमुख्यing_space);
	phys_max = virt_to_phys_or_null(max_variable_size);

	status = efi_thunk(query_variable_info, attr, phys_storage,
			   phys_reमुख्यing, phys_max);

	spin_unlock_irqrestore(&efi_runसमय_lock, flags);

	वापस status;
पूर्ण

अटल efi_status_t
efi_thunk_query_variable_info_nonblocking(u32 attr, u64 *storage_space,
					  u64 *reमुख्यing_space,
					  u64 *max_variable_size)
अणु
	efi_status_t status;
	u32 phys_storage, phys_reमुख्यing, phys_max;
	अचिन्हित दीर्घ flags;

	अगर (efi.runसमय_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		वापस EFI_UNSUPPORTED;

	अगर (!spin_trylock_irqsave(&efi_runसमय_lock, flags))
		वापस EFI_NOT_READY;

	phys_storage = virt_to_phys_or_null(storage_space);
	phys_reमुख्यing = virt_to_phys_or_null(reमुख्यing_space);
	phys_max = virt_to_phys_or_null(max_variable_size);

	status = efi_thunk(query_variable_info, attr, phys_storage,
			   phys_reमुख्यing, phys_max);

	spin_unlock_irqrestore(&efi_runसमय_lock, flags);

	वापस status;
पूर्ण

अटल efi_status_t
efi_thunk_query_capsule_caps(efi_capsule_header_t **capsules,
			     अचिन्हित दीर्घ count, u64 *max_size,
			     पूर्णांक *reset_type)
अणु
	/*
	 * To properly support this function we would need to repackage
	 * 'capsules' because the firmware doesn't understand 64-bit
	 * poपूर्णांकers.
	 */
	वापस EFI_UNSUPPORTED;
पूर्ण

व्योम __init efi_thunk_runसमय_setup(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_EFI_MIXED))
		वापस;

	efi.get_समय = efi_thunk_get_समय;
	efi.set_समय = efi_thunk_set_समय;
	efi.get_wakeup_समय = efi_thunk_get_wakeup_समय;
	efi.set_wakeup_समय = efi_thunk_set_wakeup_समय;
	efi.get_variable = efi_thunk_get_variable;
	efi.get_next_variable = efi_thunk_get_next_variable;
	efi.set_variable = efi_thunk_set_variable;
	efi.set_variable_nonblocking = efi_thunk_set_variable_nonblocking;
	efi.get_next_high_mono_count = efi_thunk_get_next_high_mono_count;
	efi.reset_प्रणाली = efi_thunk_reset_प्रणाली;
	efi.query_variable_info = efi_thunk_query_variable_info;
	efi.query_variable_info_nonblocking = efi_thunk_query_variable_info_nonblocking;
	efi.update_capsule = efi_thunk_update_capsule;
	efi.query_capsule_caps = efi_thunk_query_capsule_caps;
पूर्ण

efi_status_t __init __no_sanitize_address
efi_set_भव_address_map(अचिन्हित दीर्घ memory_map_size,
			    अचिन्हित दीर्घ descriptor_size,
			    u32 descriptor_version,
			    efi_memory_desc_t *भव_map,
			    अचिन्हित दीर्घ systab_phys)
अणु
	स्थिर efi_प्रणाली_table_t *systab = (efi_प्रणाली_table_t *)systab_phys;
	efi_status_t status;
	अचिन्हित दीर्घ flags;

	अगर (efi_is_mixed())
		वापस efi_thunk_set_भव_address_map(memory_map_size,
							 descriptor_size,
							 descriptor_version,
							 भव_map);
	efi_enter_mm();

	efi_fpu_begin();

	/* Disable पूर्णांकerrupts around EFI calls: */
	local_irq_save(flags);
	status = efi_call(efi.runसमय->set_भव_address_map,
			  memory_map_size, descriptor_size,
			  descriptor_version, भव_map);
	local_irq_restore(flags);

	efi_fpu_end();

	/* grab the भवly remapped EFI runसमय services table poपूर्णांकer */
	efi.runसमय = READ_ONCE(systab->runसमय);

	efi_leave_mm();

	वापस status;
पूर्ण
