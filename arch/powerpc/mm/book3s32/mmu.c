<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines क्रम handling the MMU on those
 * PowerPC implementations where the MMU substantially follows the
 * architecture specअगरication.  This includes the 6xx, 7xx, 7xxx,
 * and 8260 implementations but excludes the 8xx and 4xx.
 *  -- paulus
 *
 *  Derived from arch/ppc/mm/init.c:
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/sections.h>

#समावेश <mm/mmu_decl.h>

u8 __initdata early_hash[SZ_256K] __aligned(SZ_256K) = अणु0पूर्ण;

अटल काष्ठा hash_pte __initdata *Hash = (काष्ठा hash_pte *)early_hash;
अटल अचिन्हित दीर्घ __initdata Hash_size, Hash_mask;
अटल अचिन्हित पूर्णांक __initdata hash_mb, hash_mb2;
अचिन्हित दीर्घ __initdata _SDR1;

काष्ठा ppc_bat BATS[8][2];	/* 8 pairs of IBAT, DBAT */

अटल काष्ठा batrange अणु	/* stores address ranges mapped by BATs */
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ limit;
	phys_addr_t phys;
पूर्ण bat_addrs[8];

#अगर_घोषित CONFIG_SMP
अचिन्हित दीर्घ mmu_hash_lock;
#पूर्ण_अगर

/*
 * Return PA क्रम this VA अगर it is mapped by a BAT, or 0
 */
phys_addr_t v_block_mapped(अचिन्हित दीर्घ va)
अणु
	पूर्णांक b;
	क्रम (b = 0; b < ARRAY_SIZE(bat_addrs); ++b)
		अगर (va >= bat_addrs[b].start && va < bat_addrs[b].limit)
			वापस bat_addrs[b].phys + (va - bat_addrs[b].start);
	वापस 0;
पूर्ण

/*
 * Return VA क्रम a given PA or 0 अगर not mapped
 */
अचिन्हित दीर्घ p_block_mapped(phys_addr_t pa)
अणु
	पूर्णांक b;
	क्रम (b = 0; b < ARRAY_SIZE(bat_addrs); ++b)
		अगर (pa >= bat_addrs[b].phys
	    	    && pa < (bat_addrs[b].limit-bat_addrs[b].start)
		              +bat_addrs[b].phys)
			वापस bat_addrs[b].start+(pa-bat_addrs[b].phys);
	वापस 0;
पूर्ण

अटल पूर्णांक find_मुक्त_bat(व्योम)
अणु
	पूर्णांक b;
	पूर्णांक n = mmu_has_feature(MMU_FTR_USE_HIGH_BATS) ? 8 : 4;

	क्रम (b = 0; b < n; b++) अणु
		काष्ठा ppc_bat *bat = BATS[b];

		अगर (!(bat[1].batu & 3))
			वापस b;
	पूर्ण
	वापस -1;
पूर्ण

/*
 * This function calculates the size of the larger block usable to map the
 * beginning of an area based on the start address and size of that area:
 * - max block size is 256 on 6xx.
 * - base address must be aligned to the block size. So the maximum block size
 *   is identअगरied by the lowest bit set to 1 in the base address (क्रम instance
 *   अगर base is 0x16000000, max size is 0x02000000).
 * - block size has to be a घातer of two. This is calculated by finding the
 *   highest bit set to 1.
 */
अटल अचिन्हित पूर्णांक block_size(अचिन्हित दीर्घ base, अचिन्हित दीर्घ top)
अणु
	अचिन्हित पूर्णांक max_size = SZ_256M;
	अचिन्हित पूर्णांक base_shअगरt = (ffs(base) - 1) & 31;
	अचिन्हित पूर्णांक block_shअगरt = (fls(top - base) - 1) & 31;

	वापस min3(max_size, 1U << base_shअगरt, 1U << block_shअगरt);
पूर्ण

/*
 * Set up one of the IBAT (block address translation) रेजिस्टर pairs.
 * The parameters are not checked; in particular size must be a घातer
 * of 2 between 128k and 256M.
 */
अटल व्योम setibat(पूर्णांक index, अचिन्हित दीर्घ virt, phys_addr_t phys,
		    अचिन्हित पूर्णांक size, pgprot_t prot)
अणु
	अचिन्हित पूर्णांक bl = (size >> 17) - 1;
	पूर्णांक wimgxpp;
	काष्ठा ppc_bat *bat = BATS[index];
	अचिन्हित दीर्घ flags = pgprot_val(prot);

	अगर (!cpu_has_feature(CPU_FTR_NEED_COHERENT))
		flags &= ~_PAGE_COHERENT;

	wimgxpp = (flags & _PAGE_COHERENT) | (_PAGE_EXEC ? BPP_RX : BPP_XX);
	bat[0].batu = virt | (bl << 2) | 2; /* Vs=1, Vp=0 */
	bat[0].batl = BAT_PHYS_ADDR(phys) | wimgxpp;
	अगर (flags & _PAGE_USER)
		bat[0].batu |= 1;	/* Vp = 1 */
पूर्ण

अटल व्योम clearibat(पूर्णांक index)
अणु
	काष्ठा ppc_bat *bat = BATS[index];

	bat[0].batu = 0;
	bat[0].batl = 0;
पूर्ण

अटल अचिन्हित दीर्घ __init __mmu_mapin_ram(अचिन्हित दीर्घ base, अचिन्हित दीर्घ top)
अणु
	पूर्णांक idx;

	जबतक ((idx = find_मुक्त_bat()) != -1 && base != top) अणु
		अचिन्हित पूर्णांक size = block_size(base, top);

		अगर (size < 128 << 10)
			अवरोध;
		setbat(idx, PAGE_OFFSET + base, base, size, PAGE_KERNEL_X);
		base += size;
	पूर्ण

	वापस base;
पूर्ण

अचिन्हित दीर्घ __init mmu_mapin_ram(अचिन्हित दीर्घ base, अचिन्हित दीर्घ top)
अणु
	अचिन्हित दीर्घ करोne;
	अचिन्हित दीर्घ border = (अचिन्हित दीर्घ)__init_begin - PAGE_OFFSET;


	अगर (debug_pagealloc_enabled_or_kfence() || __map_without_bats) अणु
		pr_debug_once("Read-Write memory mapped without BATs\n");
		अगर (base >= border)
			वापस base;
		अगर (top >= border)
			top = border;
	पूर्ण

	अगर (!strict_kernel_rwx_enabled() || base >= border || top <= border)
		वापस __mmu_mapin_ram(base, top);

	करोne = __mmu_mapin_ram(base, border);
	अगर (करोne != border)
		वापस करोne;

	वापस __mmu_mapin_ram(border, top);
पूर्ण

अटल bool is_module_segment(अचिन्हित दीर्घ addr)
अणु
	अगर (!IS_ENABLED(CONFIG_MODULES))
		वापस false;
	अगर (addr < ALIGN_DOWN(MODULES_VADDR, SZ_256M))
		वापस false;
	अगर (addr > ALIGN(MODULES_END, SZ_256M) - 1)
		वापस false;
	वापस true;
पूर्ण

व्योम mmu_mark_iniपंचांगem_nx(व्योम)
अणु
	पूर्णांक nb = mmu_has_feature(MMU_FTR_USE_HIGH_BATS) ? 8 : 4;
	पूर्णांक i;
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ)_stext - PAGE_OFFSET;
	अचिन्हित दीर्घ top = (अचिन्हित दीर्घ)_etext - PAGE_OFFSET;
	अचिन्हित दीर्घ border = (अचिन्हित दीर्घ)__init_begin - PAGE_OFFSET;
	अचिन्हित दीर्घ size;

	क्रम (i = 0; i < nb - 1 && base < top && top - base > (128 << 10);) अणु
		size = block_size(base, top);
		setibat(i++, PAGE_OFFSET + base, base, size, PAGE_KERNEL_TEXT);
		base += size;
	पूर्ण
	अगर (base < top) अणु
		size = block_size(base, top);
		size = max(size, 128UL << 10);
		अगर ((top - base) > size) अणु
			size <<= 1;
			अगर (strict_kernel_rwx_enabled() && base + size > border)
				pr_warn("Some RW data is getting mapped X. "
					"Adjust CONFIG_DATA_SHIFT to avoid that.\n");
		पूर्ण
		setibat(i++, PAGE_OFFSET + base, base, size, PAGE_KERNEL_TEXT);
		base += size;
	पूर्ण
	क्रम (; i < nb; i++)
		clearibat(i);

	update_bats();

	क्रम (i = TASK_SIZE >> 28; i < 16; i++) अणु
		/* Do not set NX on VM space क्रम modules */
		अगर (is_module_segment(i << 28))
			जारी;

		mtsr(mfsr(i << 28) | 0x10000000, i << 28);
	पूर्ण
पूर्ण

व्योम mmu_mark_rodata_ro(व्योम)
अणु
	पूर्णांक nb = mmu_has_feature(MMU_FTR_USE_HIGH_BATS) ? 8 : 4;
	पूर्णांक i;

	क्रम (i = 0; i < nb; i++) अणु
		काष्ठा ppc_bat *bat = BATS[i];

		अगर (bat_addrs[i].start < (अचिन्हित दीर्घ)__init_begin)
			bat[1].batl = (bat[1].batl & ~BPP_RW) | BPP_RX;
	पूर्ण

	update_bats();
पूर्ण

/*
 * Set up one of the I/D BAT (block address translation) रेजिस्टर pairs.
 * The parameters are not checked; in particular size must be a घातer
 * of 2 between 128k and 256M.
 * On 603+, only set IBAT when _PAGE_EXEC is set
 */
व्योम __init setbat(पूर्णांक index, अचिन्हित दीर्घ virt, phys_addr_t phys,
		   अचिन्हित पूर्णांक size, pgprot_t prot)
अणु
	अचिन्हित पूर्णांक bl;
	पूर्णांक wimgxpp;
	काष्ठा ppc_bat *bat;
	अचिन्हित दीर्घ flags = pgprot_val(prot);

	अगर (index == -1)
		index = find_मुक्त_bat();
	अगर (index == -1) अणु
		pr_err("%s: no BAT available for mapping 0x%llx\n", __func__,
		       (अचिन्हित दीर्घ दीर्घ)phys);
		वापस;
	पूर्ण
	bat = BATS[index];

	अगर ((flags & _PAGE_NO_CACHE) ||
	    (cpu_has_feature(CPU_FTR_NEED_COHERENT) == 0))
		flags &= ~_PAGE_COHERENT;

	bl = (size >> 17) - 1;
	/* Do DBAT first */
	wimgxpp = flags & (_PAGE_WRITETHRU | _PAGE_NO_CACHE
			   | _PAGE_COHERENT | _PAGE_GUARDED);
	wimgxpp |= (flags & _PAGE_RW)? BPP_RW: BPP_RX;
	bat[1].batu = virt | (bl << 2) | 2; /* Vs=1, Vp=0 */
	bat[1].batl = BAT_PHYS_ADDR(phys) | wimgxpp;
	अगर (flags & _PAGE_USER)
		bat[1].batu |= 1; 	/* Vp = 1 */
	अगर (flags & _PAGE_GUARDED) अणु
		/* G bit must be zero in IBATs */
		flags &= ~_PAGE_EXEC;
	पूर्ण
	अगर (flags & _PAGE_EXEC)
		bat[0] = bat[1];
	अन्यथा
		bat[0].batu = bat[0].batl = 0;

	bat_addrs[index].start = virt;
	bat_addrs[index].limit = virt + ((bl + 1) << 17) - 1;
	bat_addrs[index].phys = phys;
पूर्ण

/*
 * Preload a translation in the hash table
 */
अटल व्योम hash_preload(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea)
अणु
	pmd_t *pmd;

	अगर (!mmu_has_feature(MMU_FTR_HPTE_TABLE))
		वापस;
	pmd = pmd_off(mm, ea);
	अगर (!pmd_none(*pmd))
		add_hash_page(mm->context.id, ea, pmd_val(*pmd));
पूर्ण

/*
 * This is called at the end of handling a user page fault, when the
 * fault has been handled by updating a PTE in the linux page tables.
 * We use it to preload an HPTE पूर्णांकo the hash table corresponding to
 * the updated linux PTE.
 *
 * This must always be called with the pte lock held.
 */
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		      pte_t *ptep)
अणु
	अगर (!mmu_has_feature(MMU_FTR_HPTE_TABLE))
		वापस;
	/*
	 * We करोn't need to worry about _PAGE_PRESENT here because we are
	 * called with either mm->page_table_lock held or ptl lock held
	 */

	/* We only want HPTEs क्रम linux PTEs that have _PAGE_ACCESSED set */
	अगर (!pte_young(*ptep) || address >= TASK_SIZE)
		वापस;

	/* We have to test क्रम regs शून्य since init will get here first thing at boot */
	अगर (!current->thपढ़ो.regs)
		वापस;

	/* We also aव्योम filling the hash अगर not coming from a fault */
	अगर (TRAP(current->thपढ़ो.regs) != 0x300 && TRAP(current->thपढ़ो.regs) != 0x400)
		वापस;

	hash_preload(vma->vm_mm, address);
पूर्ण

/*
 * Initialize the hash table and patch the inकाष्ठाions in hashtable.S.
 */
व्योम __init MMU_init_hw(व्योम)
अणु
	अचिन्हित पूर्णांक n_hpteg, lg_n_hpteg;

	अगर (!mmu_has_feature(MMU_FTR_HPTE_TABLE))
		वापस;

	अगर ( ppc_md.progress ) ppc_md.progress("hash:enter", 0x105);

#घोषणा LG_HPTEG_SIZE	6		/* 64 bytes per HPTEG */
#घोषणा SDR1_LOW_BITS	((n_hpteg - 1) >> 10)
#घोषणा MIN_N_HPTEG	1024		/* min 64kB hash table */

	/*
	 * Allow 1 HPTE (1/8 HPTEG) क्रम each page of memory.
	 * This is less than the recommended amount, but then
	 * Linux ain't AIX.
	 */
	n_hpteg = total_memory / (PAGE_SIZE * 8);
	अगर (n_hpteg < MIN_N_HPTEG)
		n_hpteg = MIN_N_HPTEG;
	lg_n_hpteg = __ilog2(n_hpteg);
	अगर (n_hpteg & (n_hpteg - 1)) अणु
		++lg_n_hpteg;		/* round up अगर not घातer of 2 */
		n_hpteg = 1 << lg_n_hpteg;
	पूर्ण
	Hash_size = n_hpteg << LG_HPTEG_SIZE;

	/*
	 * Find some memory क्रम the hash table.
	 */
	अगर ( ppc_md.progress ) ppc_md.progress("hash:find piece", 0x322);
	Hash = memblock_alloc(Hash_size, Hash_size);
	अगर (!Hash)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, Hash_size, Hash_size);
	_SDR1 = __pa(Hash) | SDR1_LOW_BITS;

	pr_info("Total memory = %lldMB; using %ldkB for hash table\n",
		(अचिन्हित दीर्घ दीर्घ)(total_memory >> 20), Hash_size >> 10);


	Hash_mask = n_hpteg - 1;
	hash_mb2 = hash_mb = 32 - LG_HPTEG_SIZE - lg_n_hpteg;
	अगर (lg_n_hpteg > 16)
		hash_mb2 = 16 - LG_HPTEG_SIZE;
पूर्ण

व्योम __init MMU_init_hw_patch(व्योम)
अणु
	अचिन्हित पूर्णांक hmask = Hash_mask >> (16 - LG_HPTEG_SIZE);
	अचिन्हित पूर्णांक hash = (अचिन्हित पूर्णांक)Hash - PAGE_OFFSET;

	अगर (!mmu_has_feature(MMU_FTR_HPTE_TABLE))
		वापस;

	अगर (ppc_md.progress)
		ppc_md.progress("hash:patch", 0x345);
	अगर (ppc_md.progress)
		ppc_md.progress("hash:done", 0x205);

	/* WARNING: Make sure nothing can trigger a KASAN check past this poपूर्णांक */

	/*
	 * Patch up the inकाष्ठाions in hashtable.S:create_hpte
	 */
	modअगरy_inकाष्ठाion_site(&patch__hash_page_A0, 0xffff, hash >> 16);
	modअगरy_inकाष्ठाion_site(&patch__hash_page_A1, 0x7c0, hash_mb << 6);
	modअगरy_inकाष्ठाion_site(&patch__hash_page_A2, 0x7c0, hash_mb2 << 6);
	modअगरy_inकाष्ठाion_site(&patch__hash_page_B, 0xffff, hmask);
	modअगरy_inकाष्ठाion_site(&patch__hash_page_C, 0xffff, hmask);

	/*
	 * Patch up the inकाष्ठाions in hashtable.S:flush_hash_page
	 */
	modअगरy_inकाष्ठाion_site(&patch__flush_hash_A0, 0xffff, hash >> 16);
	modअगरy_inकाष्ठाion_site(&patch__flush_hash_A1, 0x7c0, hash_mb << 6);
	modअगरy_inकाष्ठाion_site(&patch__flush_hash_A2, 0x7c0, hash_mb2 << 6);
	modअगरy_inकाष्ठाion_site(&patch__flush_hash_B, 0xffff, hmask);
पूर्ण

व्योम setup_initial_memory_limit(phys_addr_t first_memblock_base,
				phys_addr_t first_memblock_size)
अणु
	/* We करोn't currently support the first MEMBLOCK not mapping 0
	 * physical on those processors
	 */
	BUG_ON(first_memblock_base != 0);

	memblock_set_current_limit(min_t(u64, first_memblock_size, SZ_256M));
पूर्ण

व्योम __init prपूर्णांक_प्रणाली_hash_info(व्योम)
अणु
	pr_info("Hash_size         = 0x%lx\n", Hash_size);
	अगर (Hash_mask)
		pr_info("Hash_mask         = 0x%lx\n", Hash_mask);
पूर्ण

#अगर_घोषित CONFIG_PPC_KUEP
व्योम __init setup_kuep(bool disabled)
अणु
	pr_info("Activating Kernel Userspace Execution Prevention\n");

	अगर (disabled)
		pr_warn("KUEP cannot be disabled yet on 6xx when compiled in\n");
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_KUAP
व्योम __init setup_kuap(bool disabled)
अणु
	pr_info("Activating Kernel Userspace Access Protection\n");

	अगर (disabled)
		pr_warn("KUAP cannot be disabled yet on 6xx when compiled in\n");
पूर्ण
#पूर्ण_अगर

व्योम __init early_init_mmu(व्योम)
अणु
पूर्ण
