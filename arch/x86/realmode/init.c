<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/crash.h>
#समावेश <यंत्र/sev.h>

काष्ठा real_mode_header *real_mode_header;
u32 *trampoline_cr4_features;

/* Hold the pgd entry used on booting additional CPUs */
pgd_t trampoline_pgd_entry;

व्योम __init reserve_real_mode(व्योम)
अणु
	phys_addr_t mem;
	माप_प्रकार size = real_mode_size_needed();

	अगर (!size)
		वापस;

	WARN_ON(slab_is_available());

	/* Has to be under 1M so we can execute real-mode AP code. */
	mem = memblock_find_in_range(0, 1<<20, size, PAGE_SIZE);
	अगर (!mem)
		pr_info("No sub-1M memory is available for the trampoline\n");
	अन्यथा
		set_real_mode_mem(mem);

	/*
	 * Unconditionally reserve the entire fisrt 1M, see comment in
	 * setup_arch().
	 */
	memblock_reserve(0, SZ_1M);
पूर्ण

अटल व्योम sme_sev_setup_real_mode(काष्ठा trampoline_header *th)
अणु
#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
	अगर (sme_active())
		th->flags |= TH_FLAGS_SME_ACTIVE;

	अगर (sev_es_active()) अणु
		/*
		 * Skip the call to verअगरy_cpu() in secondary_startup_64 as it
		 * will cause #VC exceptions when the AP can't handle them yet.
		 */
		th->start = (u64) secondary_startup_64_no_verअगरy;

		अगर (sev_es_setup_ap_jump_table(real_mode_header))
			panic("Failed to get/update SEV-ES AP Jump Table");
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init setup_real_mode(व्योम)
अणु
	u16 real_mode_seg;
	स्थिर u32 *rel;
	u32 count;
	अचिन्हित अक्षर *base;
	अचिन्हित दीर्घ phys_base;
	काष्ठा trampoline_header *trampoline_header;
	माप_प्रकार size = PAGE_ALIGN(real_mode_blob_end - real_mode_blob);
#अगर_घोषित CONFIG_X86_64
	u64 *trampoline_pgd;
	u64 efer;
#पूर्ण_अगर

	base = (अचिन्हित अक्षर *)real_mode_header;

	/*
	 * If SME is active, the trampoline area will need to be in
	 * decrypted memory in order to bring up other processors
	 * successfully. This is not needed क्रम SEV.
	 */
	अगर (sme_active())
		set_memory_decrypted((अचिन्हित दीर्घ)base, size >> PAGE_SHIFT);

	स_नकल(base, real_mode_blob, size);

	phys_base = __pa(base);
	real_mode_seg = phys_base >> 4;

	rel = (u32 *) real_mode_relocs;

	/* 16-bit segment relocations. */
	count = *rel++;
	जबतक (count--) अणु
		u16 *seg = (u16 *) (base + *rel++);
		*seg = real_mode_seg;
	पूर्ण

	/* 32-bit linear relocations. */
	count = *rel++;
	जबतक (count--) अणु
		u32 *ptr = (u32 *) (base + *rel++);
		*ptr += phys_base;
	पूर्ण

	/* Must be perक्रमmed *after* relocation. */
	trampoline_header = (काष्ठा trampoline_header *)
		__va(real_mode_header->trampoline_header);

#अगर_घोषित CONFIG_X86_32
	trampoline_header->start = __pa_symbol(startup_32_smp);
	trampoline_header->gdt_limit = __BOOT_DS + 7;
	trampoline_header->gdt_base = __pa_symbol(boot_gdt);
#अन्यथा
	/*
	 * Some AMD processors will #GP(0) अगर EFER.LMA is set in WRMSR
	 * so we need to mask it out.
	 */
	rdmsrl(MSR_EFER, efer);
	trampoline_header->efer = efer & ~EFER_LMA;

	trampoline_header->start = (u64) secondary_startup_64;
	trampoline_cr4_features = &trampoline_header->cr4;
	*trampoline_cr4_features = mmu_cr4_features;

	trampoline_header->flags = 0;

	trampoline_pgd = (u64 *) __va(real_mode_header->trampoline_pgd);
	trampoline_pgd[0] = trampoline_pgd_entry.pgd;
	trampoline_pgd[511] = init_top_pgt[511].pgd;
#पूर्ण_अगर

	sme_sev_setup_real_mode(trampoline_header);
पूर्ण

/*
 * reserve_real_mode() माला_लो called very early, to guarantee the
 * availability of low memory. This is beक्रमe the proper kernel page
 * tables are set up, so we cannot set page permissions in that
 * function. Also trampoline code will be executed by APs so we
 * need to mark it executable at करो_pre_smp_initcalls() at least,
 * thus run it as a early_initcall().
 */
अटल व्योम __init set_real_mode_permissions(व्योम)
अणु
	अचिन्हित अक्षर *base = (अचिन्हित अक्षर *) real_mode_header;
	माप_प्रकार size = PAGE_ALIGN(real_mode_blob_end - real_mode_blob);

	माप_प्रकार ro_size =
		PAGE_ALIGN(real_mode_header->ro_end) -
		__pa(base);

	माप_प्रकार text_size =
		PAGE_ALIGN(real_mode_header->ro_end) -
		real_mode_header->text_start;

	अचिन्हित दीर्घ text_start =
		(अचिन्हित दीर्घ) __va(real_mode_header->text_start);

	set_memory_nx((अचिन्हित दीर्घ) base, size >> PAGE_SHIFT);
	set_memory_ro((अचिन्हित दीर्घ) base, ro_size >> PAGE_SHIFT);
	set_memory_x((अचिन्हित दीर्घ) text_start, text_size >> PAGE_SHIFT);
पूर्ण

अटल पूर्णांक __init init_real_mode(व्योम)
अणु
	अगर (!real_mode_header)
		panic("Real mode trampoline was not allocated");

	setup_real_mode();
	set_real_mode_permissions();

	वापस 0;
पूर्ण
early_initcall(init_real_mode);
