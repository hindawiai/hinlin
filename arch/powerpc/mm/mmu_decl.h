<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Declarations of procedures and variables shared between files
 * in arch/ppc/mm/.
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
#समावेश <linux/mm.h>
#समावेश <यंत्र/mmu.h>

#अगर_घोषित CONFIG_PPC_MMU_NOHASH
#समावेश <यंत्र/trace.h>

/*
 * On 40x and 8xx, we directly अंतरभूत tlbia and tlbivax
 */
#अगर defined(CONFIG_40x) || defined(CONFIG_PPC_8xx)
अटल अंतरभूत व्योम _tlbil_all(व्योम)
अणु
	यंत्र अस्थिर ("sync; tlbia; isync" : : : "memory");
	trace_tlbia(MMU_NO_CONTEXT);
पूर्ण
अटल अंतरभूत व्योम _tlbil_pid(अचिन्हित पूर्णांक pid)
अणु
	यंत्र अस्थिर ("sync; tlbia; isync" : : : "memory");
	trace_tlbia(pid);
पूर्ण
#घोषणा _tlbil_pid_noind(pid)	_tlbil_pid(pid)

#अन्यथा /* CONFIG_40x || CONFIG_PPC_8xx */
बाह्य व्योम _tlbil_all(व्योम);
बाह्य व्योम _tlbil_pid(अचिन्हित पूर्णांक pid);
#अगर_घोषित CONFIG_PPC_BOOK3E
बाह्य व्योम _tlbil_pid_noind(अचिन्हित पूर्णांक pid);
#अन्यथा
#घोषणा _tlbil_pid_noind(pid)	_tlbil_pid(pid)
#पूर्ण_अगर
#पूर्ण_अगर /* !(CONFIG_40x || CONFIG_PPC_8xx) */

/*
 * On 8xx, we directly अंतरभूत tlbie, on others, it's बाह्य
 */
#अगर_घोषित CONFIG_PPC_8xx
अटल अंतरभूत व्योम _tlbil_va(अचिन्हित दीर्घ address, अचिन्हित पूर्णांक pid,
			     अचिन्हित पूर्णांक tsize, अचिन्हित पूर्णांक ind)
अणु
	यंत्र अस्थिर ("tlbie %0; sync" : : "r" (address) : "memory");
	trace_tlbie(0, 0, address, pid, 0, 0, 0);
पूर्ण
#या_अगर defined(CONFIG_PPC_BOOK3E)
बाह्य व्योम _tlbil_va(अचिन्हित दीर्घ address, अचिन्हित पूर्णांक pid,
		      अचिन्हित पूर्णांक tsize, अचिन्हित पूर्णांक ind);
#अन्यथा
बाह्य व्योम __tlbil_va(अचिन्हित दीर्घ address, अचिन्हित पूर्णांक pid);
अटल अंतरभूत व्योम _tlbil_va(अचिन्हित दीर्घ address, अचिन्हित पूर्णांक pid,
			     अचिन्हित पूर्णांक tsize, अचिन्हित पूर्णांक ind)
अणु
	__tlbil_va(address, pid);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_8xx */

#अगर defined(CONFIG_PPC_BOOK3E) || defined(CONFIG_PPC_47x)
बाह्य व्योम _tlbivax_bcast(अचिन्हित दीर्घ address, अचिन्हित पूर्णांक pid,
			   अचिन्हित पूर्णांक tsize, अचिन्हित पूर्णांक ind);
#अन्यथा
अटल अंतरभूत व्योम _tlbivax_bcast(अचिन्हित दीर्घ address, अचिन्हित पूर्णांक pid,
				   अचिन्हित पूर्णांक tsize, अचिन्हित पूर्णांक ind)
अणु
	BUG();
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम prपूर्णांक_प्रणाली_hash_info(व्योम) अणुपूर्ण

#अन्यथा /* CONFIG_PPC_MMU_NOHASH */

व्योम prपूर्णांक_प्रणाली_hash_info(व्योम);

#पूर्ण_अगर /* CONFIG_PPC_MMU_NOHASH */

#अगर_घोषित CONFIG_PPC32

बाह्य व्योम mapin_ram(व्योम);
बाह्य व्योम setbat(पूर्णांक index, अचिन्हित दीर्घ virt, phys_addr_t phys,
		   अचिन्हित पूर्णांक size, pgprot_t prot);

बाह्य पूर्णांक __map_without_bats;
बाह्य अचिन्हित पूर्णांक rtas_data, rtas_size;

काष्ठा hash_pte;
बाह्य u8 early_hash[];

#पूर्ण_अगर /* CONFIG_PPC32 */

बाह्य अचिन्हित दीर्घ __max_low_memory;
बाह्य phys_addr_t __initial_memory_limit_addr;
बाह्य phys_addr_t total_memory;
बाह्य phys_addr_t total_lowmem;
बाह्य phys_addr_t memstart_addr;
बाह्य phys_addr_t lowmem_end_addr;

#अगर_घोषित CONFIG_WII
बाह्य अचिन्हित दीर्घ wii_hole_start;
बाह्य अचिन्हित दीर्घ wii_hole_size;

बाह्य अचिन्हित दीर्घ wii_mmu_mapin_mem2(अचिन्हित दीर्घ top);
बाह्य व्योम wii_memory_fixups(व्योम);
#पूर्ण_अगर

/* ...and now those things that may be slightly dअगरferent between processor
 * architectures.  -- Dan
 */
#अगर_घोषित CONFIG_PPC32
बाह्य व्योम MMU_init_hw(व्योम);
व्योम MMU_init_hw_patch(व्योम);
अचिन्हित दीर्घ mmu_mapin_ram(अचिन्हित दीर्घ base, अचिन्हित दीर्घ top);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
बाह्य अचिन्हित दीर्घ map_mem_in_cams(अचिन्हित दीर्घ ram, पूर्णांक max_cam_idx,
				     bool dryrun);
बाह्य अचिन्हित दीर्घ calc_cam_sz(अचिन्हित दीर्घ ram, अचिन्हित दीर्घ virt,
				 phys_addr_t phys);
#अगर_घोषित CONFIG_PPC32
बाह्य व्योम adjust_total_lowmem(व्योम);
बाह्य पूर्णांक चयन_to_as1(व्योम);
बाह्य व्योम restore_to_as0(पूर्णांक esel, पूर्णांक offset, व्योम *dt_ptr, पूर्णांक bootcpu);
व्योम create_kaslr_tlb_entry(पूर्णांक entry, अचिन्हित दीर्घ virt, phys_addr_t phys);
व्योम reloc_kernel_entry(व्योम *fdt, पूर्णांक addr);
बाह्य पूर्णांक is_second_reloc;
#पूर्ण_अगर
बाह्य व्योम loadcam_entry(अचिन्हित पूर्णांक index);
बाह्य व्योम loadcam_multi(पूर्णांक first_idx, पूर्णांक num, पूर्णांक पंचांगp_idx);

#अगर_घोषित CONFIG_RANDOMIZE_BASE
व्योम kaslr_early_init(व्योम *dt_ptr, phys_addr_t size);
व्योम kaslr_late_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kaslr_early_init(व्योम *dt_ptr, phys_addr_t size) अणुपूर्ण
अटल अंतरभूत व्योम kaslr_late_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

काष्ठा tlbcam अणु
	u32	MAS0;
	u32	MAS1;
	अचिन्हित दीर्घ	MAS2;
	u32	MAS3;
	u32	MAS7;
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_BOOK3S_32) || defined(CONFIG_FSL_BOOKE) || defined(CONFIG_PPC_8xx)
/* 6xx have BATS */
/* FSL_BOOKE have TLBCAM */
/* 8xx have LTLB */
phys_addr_t v_block_mapped(अचिन्हित दीर्घ va);
अचिन्हित दीर्घ p_block_mapped(phys_addr_t pa);
#अन्यथा
अटल अंतरभूत phys_addr_t v_block_mapped(अचिन्हित दीर्घ va) अणु वापस 0; पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ p_block_mapped(phys_addr_t pa) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_BOOK3S_32) || defined(CONFIG_PPC_8xx)
व्योम mmu_mark_iniपंचांगem_nx(व्योम);
व्योम mmu_mark_rodata_ro(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mmu_mark_iniपंचांगem_nx(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम mmu_mark_rodata_ro(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_8xx
व्योम __init mmu_mapin_immr(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_DEBUG_WX
व्योम ptdump_check_wx(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ptdump_check_wx(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool debug_pagealloc_enabled_or_kfence(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_KFENCE) || debug_pagealloc_enabled();
पूर्ण
