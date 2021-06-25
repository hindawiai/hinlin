<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hibernation support क्रम x86
 *
 * Copyright (c) 2007 Rafael J. Wysocki <rjw@sisk.pl>
 * Copyright (c) 2002 Pavel Machek <pavel@ucw.cz>
 * Copyright (c) 2001 Patrick Mochel <mochel@osdl.org>
 */
#समावेश <linux/gfp.h>
#समावेश <linux/smp.h>
#समावेश <linux/suspend.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/types.h>
#समावेश <linux/crc32.h>

#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/init.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/tlbflush.h>

/*
 * Address to jump to in the last phase of restore in order to get to the image
 * kernel's text (this value is passed in the image header).
 */
अचिन्हित दीर्घ restore_jump_address __visible;
अचिन्हित दीर्घ jump_address_phys;

/*
 * Value of the cr3 रेजिस्टर from beक्रमe the hibernation (this value is passed
 * in the image header).
 */
अचिन्हित दीर्घ restore_cr3 __visible;
अचिन्हित दीर्घ temp_pgt __visible;
अचिन्हित दीर्घ relocated_restore_code __visible;

/**
 *	pfn_is_nosave - check अगर given pfn is in the 'nosave' section
 */
पूर्णांक pfn_is_nosave(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ nosave_begin_pfn;
	अचिन्हित दीर्घ nosave_end_pfn;

	nosave_begin_pfn = __pa_symbol(&__nosave_begin) >> PAGE_SHIFT;
	nosave_end_pfn = PAGE_ALIGN(__pa_symbol(&__nosave_end)) >> PAGE_SHIFT;

	वापस pfn >= nosave_begin_pfn && pfn < nosave_end_pfn;
पूर्ण

काष्ठा restore_data_record अणु
	अचिन्हित दीर्घ jump_address;
	अचिन्हित दीर्घ jump_address_phys;
	अचिन्हित दीर्घ cr3;
	अचिन्हित दीर्घ magic;
	अचिन्हित दीर्घ e820_checksum;
पूर्ण;

/**
 * compute_e820_crc32 - calculate crc32 of a given e820 table
 *
 * @table: the e820 table to be calculated
 *
 * Return: the resulting checksum
 */
अटल अंतरभूत u32 compute_e820_crc32(काष्ठा e820_table *table)
अणु
	पूर्णांक size = दुरत्व(काष्ठा e820_table, entries) +
		माप(काष्ठा e820_entry) * table->nr_entries;

	वापस ~crc32_le(~0, (अचिन्हित अक्षर स्थिर *)table, size);
पूर्ण

#अगर_घोषित CONFIG_X86_64
#घोषणा RESTORE_MAGIC	0x23456789ABCDEF02UL
#अन्यथा
#घोषणा RESTORE_MAGIC	0x12345679UL
#पूर्ण_अगर

/**
 *	arch_hibernation_header_save - populate the architecture specअगरic part
 *		of a hibernation image header
 *	@addr: address to save the data at
 */
पूर्णांक arch_hibernation_header_save(व्योम *addr, अचिन्हित पूर्णांक max_size)
अणु
	काष्ठा restore_data_record *rdr = addr;

	अगर (max_size < माप(काष्ठा restore_data_record))
		वापस -EOVERFLOW;
	rdr->magic = RESTORE_MAGIC;
	rdr->jump_address = (अचिन्हित दीर्घ)restore_रेजिस्टरs;
	rdr->jump_address_phys = __pa_symbol(restore_रेजिस्टरs);

	/*
	 * The restore code fixes up CR3 and CR4 in the following sequence:
	 *
	 * [in hibernation यंत्र]
	 * 1. CR3 <= temporary page tables
	 * 2. CR4 <= mmu_cr4_features (from the kernel that restores us)
	 * 3. CR3 <= rdr->cr3
	 * 4. CR4 <= mmu_cr4_features (from us, i.e. the image kernel)
	 * [in restore_processor_state()]
	 * 5. CR4 <= saved CR4
	 * 6. CR3 <= saved CR3
	 *
	 * Our mmu_cr4_features has CR4.PCIDE=0, and toggling
	 * CR4.PCIDE जबतक CR3's PCID bits are nonzero is illegal, so
	 * rdr->cr3 needs to poपूर्णांक to valid page tables but must not
	 * have any of the PCID bits set.
	 */
	rdr->cr3 = restore_cr3 & ~CR3_PCID_MASK;

	rdr->e820_checksum = compute_e820_crc32(e820_table_firmware);
	वापस 0;
पूर्ण

/**
 *	arch_hibernation_header_restore - पढ़ो the architecture specअगरic data
 *		from the hibernation image header
 *	@addr: address to पढ़ो the data from
 */
पूर्णांक arch_hibernation_header_restore(व्योम *addr)
अणु
	काष्ठा restore_data_record *rdr = addr;

	अगर (rdr->magic != RESTORE_MAGIC) अणु
		pr_crit("Unrecognized hibernate image header format!\n");
		वापस -EINVAL;
	पूर्ण

	restore_jump_address = rdr->jump_address;
	jump_address_phys = rdr->jump_address_phys;
	restore_cr3 = rdr->cr3;

	अगर (rdr->e820_checksum != compute_e820_crc32(e820_table_firmware)) अणु
		pr_crit("Hibernate inconsistent memory map detected!\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक relocate_restore_code(व्योम)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	relocated_restore_code = get_safe_page(GFP_ATOMIC);
	अगर (!relocated_restore_code)
		वापस -ENOMEM;

	स_नकल((व्योम *)relocated_restore_code, core_restore_code, PAGE_SIZE);

	/* Make the page containing the relocated code executable */
	pgd = (pgd_t *)__va(पढ़ो_cr3_pa()) +
		pgd_index(relocated_restore_code);
	p4d = p4d_offset(pgd, relocated_restore_code);
	अगर (p4d_large(*p4d)) अणु
		set_p4d(p4d, __p4d(p4d_val(*p4d) & ~_PAGE_NX));
		जाओ out;
	पूर्ण
	pud = pud_offset(p4d, relocated_restore_code);
	अगर (pud_large(*pud)) अणु
		set_pud(pud, __pud(pud_val(*pud) & ~_PAGE_NX));
		जाओ out;
	पूर्ण
	pmd = pmd_offset(pud, relocated_restore_code);
	अगर (pmd_large(*pmd)) अणु
		set_pmd(pmd, __pmd(pmd_val(*pmd) & ~_PAGE_NX));
		जाओ out;
	पूर्ण
	pte = pte_offset_kernel(pmd, relocated_restore_code);
	set_pte(pte, __pte(pte_val(*pte) & ~_PAGE_NX));
out:
	__flush_tlb_all();
	वापस 0;
पूर्ण

पूर्णांक arch_resume_nosmt(व्योम)
अणु
	पूर्णांक ret = 0;
	/*
	 * We reached this जबतक coming out of hibernation. This means
	 * that SMT siblings are sleeping in hlt, as mरुको is not safe
	 * against control transition during resume (see comment in
	 * hibernate_resume_nonboot_cpu_disable()).
	 *
	 * If the resumed kernel has SMT disabled, we have to take all the
	 * SMT siblings out of hlt, and offline them again so that they
	 * end up in mरुको proper.
	 *
	 * Called with hotplug disabled.
	 */
	cpu_hotplug_enable();
	अगर (cpu_smt_control == CPU_SMT_DISABLED ||
			cpu_smt_control == CPU_SMT_FORCE_DISABLED) अणु
		क्रमागत cpuhp_smt_control old = cpu_smt_control;

		ret = cpuhp_smt_enable();
		अगर (ret)
			जाओ out;
		ret = cpuhp_smt_disable(old);
		अगर (ret)
			जाओ out;
	पूर्ण
out:
	cpu_hotplug_disable();
	वापस ret;
पूर्ण
