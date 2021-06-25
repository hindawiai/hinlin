<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * handle transition of Linux booting another kernel
 * Copyright (C) 2002-2005 Eric Biederman  <ebiederm@xmission.com>
 */

#घोषणा pr_fmt(fmt)	"kexec: " fmt

#समावेश <linux/mm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/माला.स>
#समावेश <linux/gfp.h>
#समावेश <linux/reboot.h>
#समावेश <linux/numa.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/पन.स>
#समावेश <linux/suspend.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/efi.h>

#समावेश <यंत्र/init.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/kexec-bzimage64.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/set_memory.h>

#अगर_घोषित CONFIG_ACPI
/*
 * Used जबतक adding mapping क्रम ACPI tables.
 * Can be reused when other iomem regions need be mapped
 */
काष्ठा init_pgtable_data अणु
	काष्ठा x86_mapping_info *info;
	pgd_t *level4p;
पूर्ण;

अटल पूर्णांक mem_region_callback(काष्ठा resource *res, व्योम *arg)
अणु
	काष्ठा init_pgtable_data *data = arg;
	अचिन्हित दीर्घ mstart, mend;

	mstart = res->start;
	mend = mstart + resource_size(res) - 1;

	वापस kernel_ident_mapping_init(data->info, data->level4p, mstart, mend);
पूर्ण

अटल पूर्णांक
map_acpi_tables(काष्ठा x86_mapping_info *info, pgd_t *level4p)
अणु
	काष्ठा init_pgtable_data data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	data.info = info;
	data.level4p = level4p;
	flags = IORESOURCE_MEM | IORESOURCE_BUSY;

	ret = walk_iomem_res_desc(IORES_DESC_ACPI_TABLES, flags, 0, -1,
				  &data, mem_region_callback);
	अगर (ret && ret != -EINVAL)
		वापस ret;

	/* ACPI tables could be located in ACPI Non-अस्थिर Storage region */
	ret = walk_iomem_res_desc(IORES_DESC_ACPI_NV_STORAGE, flags, 0, -1,
				  &data, mem_region_callback);
	अगर (ret && ret != -EINVAL)
		वापस ret;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक map_acpi_tables(काष्ठा x86_mapping_info *info, pgd_t *level4p) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC_खाता
स्थिर काष्ठा kexec_file_ops * स्थिर kexec_file_loaders[] = अणु
		&kexec_bzImage64_ops,
		शून्य
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक
map_efi_systab(काष्ठा x86_mapping_info *info, pgd_t *level4p)
अणु
#अगर_घोषित CONFIG_EFI
	अचिन्हित दीर्घ mstart, mend;

	अगर (!efi_enabled(EFI_BOOT))
		वापस 0;

	mstart = (boot_params.efi_info.efi_systab |
			((u64)boot_params.efi_info.efi_systab_hi<<32));

	अगर (efi_enabled(EFI_64BIT))
		mend = mstart + माप(efi_प्रणाली_table_64_t);
	अन्यथा
		mend = mstart + माप(efi_प्रणाली_table_32_t);

	अगर (!mstart)
		वापस 0;

	वापस kernel_ident_mapping_init(info, level4p, mstart, mend);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम मुक्त_transition_pgtable(काष्ठा kimage *image)
अणु
	मुक्त_page((अचिन्हित दीर्घ)image->arch.p4d);
	image->arch.p4d = शून्य;
	मुक्त_page((अचिन्हित दीर्घ)image->arch.pud);
	image->arch.pud = शून्य;
	मुक्त_page((अचिन्हित दीर्घ)image->arch.pmd);
	image->arch.pmd = शून्य;
	मुक्त_page((अचिन्हित दीर्घ)image->arch.pte);
	image->arch.pte = शून्य;
पूर्ण

अटल पूर्णांक init_transition_pgtable(काष्ठा kimage *image, pgd_t *pgd)
अणु
	pgprot_t prot = PAGE_KERNEL_EXEC_NOENC;
	अचिन्हित दीर्घ vaddr, paddr;
	पूर्णांक result = -ENOMEM;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	vaddr = (अचिन्हित दीर्घ)relocate_kernel;
	paddr = __pa(page_address(image->control_code_page)+PAGE_SIZE);
	pgd += pgd_index(vaddr);
	अगर (!pgd_present(*pgd)) अणु
		p4d = (p4d_t *)get_zeroed_page(GFP_KERNEL);
		अगर (!p4d)
			जाओ err;
		image->arch.p4d = p4d;
		set_pgd(pgd, __pgd(__pa(p4d) | _KERNPG_TABLE));
	पूर्ण
	p4d = p4d_offset(pgd, vaddr);
	अगर (!p4d_present(*p4d)) अणु
		pud = (pud_t *)get_zeroed_page(GFP_KERNEL);
		अगर (!pud)
			जाओ err;
		image->arch.pud = pud;
		set_p4d(p4d, __p4d(__pa(pud) | _KERNPG_TABLE));
	पूर्ण
	pud = pud_offset(p4d, vaddr);
	अगर (!pud_present(*pud)) अणु
		pmd = (pmd_t *)get_zeroed_page(GFP_KERNEL);
		अगर (!pmd)
			जाओ err;
		image->arch.pmd = pmd;
		set_pud(pud, __pud(__pa(pmd) | _KERNPG_TABLE));
	पूर्ण
	pmd = pmd_offset(pud, vaddr);
	अगर (!pmd_present(*pmd)) अणु
		pte = (pte_t *)get_zeroed_page(GFP_KERNEL);
		अगर (!pte)
			जाओ err;
		image->arch.pte = pte;
		set_pmd(pmd, __pmd(__pa(pte) | _KERNPG_TABLE));
	पूर्ण
	pte = pte_offset_kernel(pmd, vaddr);

	अगर (sev_active())
		prot = PAGE_KERNEL_EXEC;

	set_pte(pte, pfn_pte(paddr >> PAGE_SHIFT, prot));
	वापस 0;
err:
	वापस result;
पूर्ण

अटल व्योम *alloc_pgt_page(व्योम *data)
अणु
	काष्ठा kimage *image = (काष्ठा kimage *)data;
	काष्ठा page *page;
	व्योम *p = शून्य;

	page = kimage_alloc_control_pages(image, 0);
	अगर (page) अणु
		p = page_address(page);
		clear_page(p);
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक init_pgtable(काष्ठा kimage *image, अचिन्हित दीर्घ start_pgtable)
अणु
	काष्ठा x86_mapping_info info = अणु
		.alloc_pgt_page	= alloc_pgt_page,
		.context	= image,
		.page_flag	= __PAGE_KERNEL_LARGE_EXEC,
		.kernpg_flag	= _KERNPG_TABLE_NOENC,
	पूर्ण;
	अचिन्हित दीर्घ mstart, mend;
	pgd_t *level4p;
	पूर्णांक result;
	पूर्णांक i;

	level4p = (pgd_t *)__va(start_pgtable);
	clear_page(level4p);

	अगर (sev_active()) अणु
		info.page_flag   |= _PAGE_ENC;
		info.kernpg_flag |= _PAGE_ENC;
	पूर्ण

	अगर (direct_gbpages)
		info.direct_gbpages = true;

	क्रम (i = 0; i < nr_pfn_mapped; i++) अणु
		mstart = pfn_mapped[i].start << PAGE_SHIFT;
		mend   = pfn_mapped[i].end << PAGE_SHIFT;

		result = kernel_ident_mapping_init(&info,
						 level4p, mstart, mend);
		अगर (result)
			वापस result;
	पूर्ण

	/*
	 * segments's mem ranges could be outside 0 ~ max_pfn,
	 * क्रम example when jump back to original kernel from kexeced kernel.
	 * or first kernel is booted with user mem map, and second kernel
	 * could be loaded out of that range.
	 */
	क्रम (i = 0; i < image->nr_segments; i++) अणु
		mstart = image->segment[i].mem;
		mend   = mstart + image->segment[i].memsz;

		result = kernel_ident_mapping_init(&info,
						 level4p, mstart, mend);

		अगर (result)
			वापस result;
	पूर्ण

	/*
	 * Prepare EFI systab and ACPI tables क्रम kexec kernel since they are
	 * not covered by pfn_mapped.
	 */
	result = map_efi_systab(&info, level4p);
	अगर (result)
		वापस result;

	result = map_acpi_tables(&info, level4p);
	अगर (result)
		वापस result;

	वापस init_transition_pgtable(image, level4p);
पूर्ण

अटल व्योम set_idt(व्योम *newidt, u16 limit)
अणु
	काष्ठा desc_ptr curidt;

	/* x86-64 supports unaligned loads & stores */
	curidt.size    = limit;
	curidt.address = (अचिन्हित दीर्घ)newidt;

	__यंत्र__ __अस्थिर__ (
		"lidtq %0\n"
		: : "m" (curidt)
		);
पूर्ण;


अटल व्योम set_gdt(व्योम *newgdt, u16 limit)
अणु
	काष्ठा desc_ptr curgdt;

	/* x86-64 supports unaligned loads & stores */
	curgdt.size    = limit;
	curgdt.address = (अचिन्हित दीर्घ)newgdt;

	__यंत्र__ __अस्थिर__ (
		"lgdtq %0\n"
		: : "m" (curgdt)
		);
पूर्ण;

अटल व्योम load_segments(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"\tmovl %0,%%ds\n"
		"\tmovl %0,%%es\n"
		"\tmovl %0,%%ss\n"
		"\tmovl %0,%%fs\n"
		"\tmovl %0,%%gs\n"
		: : "a" (__KERNEL_DS) : "memory"
		);
पूर्ण

पूर्णांक machine_kexec_prepare(काष्ठा kimage *image)
अणु
	अचिन्हित दीर्घ start_pgtable;
	पूर्णांक result;

	/* Calculate the offsets */
	start_pgtable = page_to_pfn(image->control_code_page) << PAGE_SHIFT;

	/* Setup the identity mapped 64bit page table */
	result = init_pgtable(image, start_pgtable);
	अगर (result)
		वापस result;

	वापस 0;
पूर्ण

व्योम machine_kexec_cleanup(काष्ठा kimage *image)
अणु
	मुक्त_transition_pgtable(image);
पूर्ण

/*
 * Do not allocate memory (or fail in any way) in machine_kexec().
 * We are past the poपूर्णांक of no वापस, committed to rebooting now.
 */
व्योम machine_kexec(काष्ठा kimage *image)
अणु
	अचिन्हित दीर्घ page_list[PAGES_NR];
	व्योम *control_page;
	पूर्णांक save_ftrace_enabled;

#अगर_घोषित CONFIG_KEXEC_JUMP
	अगर (image->preserve_context)
		save_processor_state();
#पूर्ण_अगर

	save_ftrace_enabled = __ftrace_enabled_save();

	/* Interrupts aren't acceptable जबतक we reboot */
	local_irq_disable();
	hw_अवरोधpoपूर्णांक_disable();

	अगर (image->preserve_context) अणु
#अगर_घोषित CONFIG_X86_IO_APIC
		/*
		 * We need to put APICs in legacy mode so that we can
		 * get समयr पूर्णांकerrupts in second kernel. kexec/kdump
		 * paths alपढ़ोy have calls to restore_boot_irq_mode()
		 * in one क्रमm or other. kexec jump path also need one.
		 */
		clear_IO_APIC();
		restore_boot_irq_mode();
#पूर्ण_अगर
	पूर्ण

	control_page = page_address(image->control_code_page) + PAGE_SIZE;
	स_नकल(control_page, relocate_kernel, KEXEC_CONTROL_CODE_MAX_SIZE);

	page_list[PA_CONTROL_PAGE] = virt_to_phys(control_page);
	page_list[VA_CONTROL_PAGE] = (अचिन्हित दीर्घ)control_page;
	page_list[PA_TABLE_PAGE] =
	  (अचिन्हित दीर्घ)__pa(page_address(image->control_code_page));

	अगर (image->type == KEXEC_TYPE_DEFAULT)
		page_list[PA_SWAP_PAGE] = (page_to_pfn(image->swap_page)
						<< PAGE_SHIFT);

	/*
	 * The segment रेजिस्टरs are funny things, they have both a
	 * visible and an invisible part.  Whenever the visible part is
	 * set to a specअगरic selector, the invisible part is loaded
	 * with from a table in memory.  At no other समय is the
	 * descriptor table in memory accessed.
	 *
	 * I take advantage of this here by क्रमce loading the
	 * segments, beक्रमe I zap the gdt with an invalid value.
	 */
	load_segments();
	/*
	 * The gdt & idt are now invalid.
	 * If you want to load them you must set up your own idt & gdt.
	 */
	set_gdt(phys_to_virt(0), 0);
	set_idt(phys_to_virt(0), 0);

	/* now call it */
	image->start = relocate_kernel((अचिन्हित दीर्घ)image->head,
				       (अचिन्हित दीर्घ)page_list,
				       image->start,
				       image->preserve_context,
				       sme_active());

#अगर_घोषित CONFIG_KEXEC_JUMP
	अगर (image->preserve_context)
		restore_processor_state();
#पूर्ण_अगर

	__ftrace_enabled_restore(save_ftrace_enabled);
पूर्ण

/* arch-dependent functionality related to kexec file-based syscall */

#अगर_घोषित CONFIG_KEXEC_खाता
व्योम *arch_kexec_kernel_image_load(काष्ठा kimage *image)
अणु
	vमुक्त(image->elf_headers);
	image->elf_headers = शून्य;

	अगर (!image->fops || !image->fops->load)
		वापस ERR_PTR(-ENOEXEC);

	वापस image->fops->load(image, image->kernel_buf,
				 image->kernel_buf_len, image->initrd_buf,
				 image->initrd_buf_len, image->cmdline_buf,
				 image->cmdline_buf_len);
पूर्ण

/*
 * Apply purgatory relocations.
 *
 * @pi:		Purgatory to be relocated.
 * @section:	Section relocations applying to.
 * @rअन्यथाc:	Section containing RELAs.
 * @symtअसलec:	Corresponding symtab.
 *
 * TODO: Some of the code beदीर्घs to generic code. Move that in kexec.c.
 */
पूर्णांक arch_kexec_apply_relocations_add(काष्ठा purgatory_info *pi,
				     Elf_Shdr *section, स्थिर Elf_Shdr *rअन्यथाc,
				     स्थिर Elf_Shdr *symtअसलec)
अणु
	अचिन्हित पूर्णांक i;
	Elf64_Rela *rel;
	Elf64_Sym *sym;
	व्योम *location;
	अचिन्हित दीर्घ address, sec_base, value;
	स्थिर अक्षर *strtab, *name, *shstrtab;
	स्थिर Elf_Shdr *sechdrs;

	/* String & section header string table */
	sechdrs = (व्योम *)pi->ehdr + pi->ehdr->e_shoff;
	strtab = (अक्षर *)pi->ehdr + sechdrs[symtअसलec->sh_link].sh_offset;
	shstrtab = (अक्षर *)pi->ehdr + sechdrs[pi->ehdr->e_shstrndx].sh_offset;

	rel = (व्योम *)pi->ehdr + rअन्यथाc->sh_offset;

	pr_debug("Applying relocate section %s to %u\n",
		 shstrtab + rअन्यथाc->sh_name, rअन्यथाc->sh_info);

	क्रम (i = 0; i < rअन्यथाc->sh_size / माप(*rel); i++) अणु

		/*
		 * rel[i].r_offset contains byte offset from beginning
		 * of section to the storage unit affected.
		 *
		 * This is location to update. This is temporary buffer
		 * where section is currently loaded. This will finally be
		 * loaded to a dअगरferent address later, poपूर्णांकed to by
		 * ->sh_addr. kexec takes care of moving it
		 *  (kexec_load_segment()).
		 */
		location = pi->purgatory_buf;
		location += section->sh_offset;
		location += rel[i].r_offset;

		/* Final address of the location */
		address = section->sh_addr + rel[i].r_offset;

		/*
		 * rel[i].r_info contains inक्रमmation about symbol table index
		 * w.r.t which relocation must be made and type of relocation
		 * to apply. ELF64_R_SYM() and ELF64_R_TYPE() macros get
		 * these respectively.
		 */
		sym = (व्योम *)pi->ehdr + symtअसलec->sh_offset;
		sym += ELF64_R_SYM(rel[i].r_info);

		अगर (sym->st_name)
			name = strtab + sym->st_name;
		अन्यथा
			name = shstrtab + sechdrs[sym->st_shndx].sh_name;

		pr_debug("Symbol: %s info: %02x shndx: %02x value=%llx size: %llx\n",
			 name, sym->st_info, sym->st_shndx, sym->st_value,
			 sym->st_size);

		अगर (sym->st_shndx == SHN_UNDEF) अणु
			pr_err("Undefined symbol: %s\n", name);
			वापस -ENOEXEC;
		पूर्ण

		अगर (sym->st_shndx == SHN_COMMON) अणु
			pr_err("symbol '%s' in common section\n", name);
			वापस -ENOEXEC;
		पूर्ण

		अगर (sym->st_shndx == SHN_ABS)
			sec_base = 0;
		अन्यथा अगर (sym->st_shndx >= pi->ehdr->e_shnum) अणु
			pr_err("Invalid section %d for symbol %s\n",
			       sym->st_shndx, name);
			वापस -ENOEXEC;
		पूर्ण अन्यथा
			sec_base = pi->sechdrs[sym->st_shndx].sh_addr;

		value = sym->st_value;
		value += sec_base;
		value += rel[i].r_addend;

		चयन (ELF64_R_TYPE(rel[i].r_info)) अणु
		हाल R_X86_64_NONE:
			अवरोध;
		हाल R_X86_64_64:
			*(u64 *)location = value;
			अवरोध;
		हाल R_X86_64_32:
			*(u32 *)location = value;
			अगर (value != *(u32 *)location)
				जाओ overflow;
			अवरोध;
		हाल R_X86_64_32S:
			*(s32 *)location = value;
			अगर ((s64)value != *(s32 *)location)
				जाओ overflow;
			अवरोध;
		हाल R_X86_64_PC32:
		हाल R_X86_64_PLT32:
			value -= (u64)address;
			*(u32 *)location = value;
			अवरोध;
		शेष:
			pr_err("Unknown rela relocation: %llu\n",
			       ELF64_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;

overflow:
	pr_err("Overflow in relocation type %d value 0x%lx\n",
	       (पूर्णांक)ELF64_R_TYPE(rel[i].r_info), value);
	वापस -ENOEXEC;
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_खाता */

अटल पूर्णांक
kexec_mark_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, bool protect)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक nr_pages;

	/*
	 * For physical range: [start, end]. We must skip the unasचिन्हित
	 * crashk resource with zero-valued "end" member.
	 */
	अगर (!end || start > end)
		वापस 0;

	page = pfn_to_page(start >> PAGE_SHIFT);
	nr_pages = (end >> PAGE_SHIFT) - (start >> PAGE_SHIFT) + 1;
	अगर (protect)
		वापस set_pages_ro(page, nr_pages);
	अन्यथा
		वापस set_pages_rw(page, nr_pages);
पूर्ण

अटल व्योम kexec_mark_crashkres(bool protect)
अणु
	अचिन्हित दीर्घ control;

	kexec_mark_range(crashk_low_res.start, crashk_low_res.end, protect);

	/* Don't touch the control code page used in crash_kexec().*/
	control = PFN_PHYS(page_to_pfn(kexec_crash_image->control_code_page));
	/* Control code page is located in the 2nd page. */
	kexec_mark_range(crashk_res.start, control + PAGE_SIZE - 1, protect);
	control += KEXEC_CONTROL_PAGE_SIZE;
	kexec_mark_range(control, crashk_res.end, protect);
पूर्ण

व्योम arch_kexec_protect_crashkres(व्योम)
अणु
	kexec_mark_crashkres(true);
पूर्ण

व्योम arch_kexec_unprotect_crashkres(व्योम)
अणु
	kexec_mark_crashkres(false);
पूर्ण

/*
 * During a traditional boot under SME, SME will encrypt the kernel,
 * so the SME kexec kernel also needs to be un-encrypted in order to
 * replicate a normal SME boot.
 *
 * During a traditional boot under SEV, the kernel has alपढ़ोy been
 * loaded encrypted, so the SEV kexec kernel needs to be encrypted in
 * order to replicate a normal SEV boot.
 */
पूर्णांक arch_kexec_post_alloc_pages(व्योम *vaddr, अचिन्हित पूर्णांक pages, gfp_t gfp)
अणु
	अगर (sev_active())
		वापस 0;

	/*
	 * If SME is active we need to be sure that kexec pages are
	 * not encrypted because when we boot to the new kernel the
	 * pages won't be accessed encrypted (initially).
	 */
	वापस set_memory_decrypted((अचिन्हित दीर्घ)vaddr, pages);
पूर्ण

व्योम arch_kexec_pre_मुक्त_pages(व्योम *vaddr, अचिन्हित पूर्णांक pages)
अणु
	अगर (sev_active())
		वापस;

	/*
	 * If SME is active we need to reset the pages back to being
	 * an encrypted mapping beक्रमe मुक्तing them.
	 */
	set_memory_encrypted((अचिन्हित दीर्घ)vaddr, pages);
पूर्ण
