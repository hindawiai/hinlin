<शैली गुरु>
/*
 * TLB miss handler क्रम SH with an MMU.
 *
 *  Copyright (C) 1999  Niibe Yutaka
 *  Copyright (C) 2003 - 2012  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/thपढ़ो_info.h>

/*
 * Called with पूर्णांकerrupts disabled.
 */
यंत्रlinkage पूर्णांक __kprobes
handle_tlbmiss(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
	       अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	pte_t entry;

	/*
	 * We करोn't take page faults क्रम P1, P2, and parts of P4, these
	 * are always mapped, whether it be due to legacy behaviour in
	 * 29-bit mode, or due to PMB configuration in 32-bit mode.
	 */
	अगर (address >= P3SEG && address < P3_ADDR_MAX) अणु
		pgd = pgd_offset_k(address);
	पूर्ण अन्यथा अणु
		अगर (unlikely(address >= TASK_SIZE || !current->mm))
			वापस 1;

		pgd = pgd_offset(current->mm, address);
	पूर्ण

	p4d = p4d_offset(pgd, address);
	अगर (p4d_none_or_clear_bad(p4d))
		वापस 1;
	pud = pud_offset(p4d, address);
	अगर (pud_none_or_clear_bad(pud))
		वापस 1;
	pmd = pmd_offset(pud, address);
	अगर (pmd_none_or_clear_bad(pmd))
		वापस 1;
	pte = pte_offset_kernel(pmd, address);
	entry = *pte;
	अगर (unlikely(pte_none(entry) || pte_not_present(entry)))
		वापस 1;
	अगर (unlikely(error_code && !pte_ग_लिखो(entry)))
		वापस 1;

	अगर (error_code)
		entry = pte_सूची_गढ़ोty(entry);
	entry = pte_mkyoung(entry);

	set_pte(pte, entry);

#अगर defined(CONFIG_CPU_SH4) && !defined(CONFIG_SMP)
	/*
	 * SH-4 करोes not set MMUCR.RC to the corresponding TLB entry in
	 * the हाल of an initial page ग_लिखो exception, so we need to
	 * flush it in order to aव्योम potential TLB entry duplication.
	 */
	अगर (error_code == FAULT_CODE_INITIAL)
		local_flush_tlb_one(get_asid(), address & PAGE_MASK);
#पूर्ण_अगर

	set_thपढ़ो_fault_code(error_code);
	update_mmu_cache(शून्य, address, pte);

	वापस 0;
पूर्ण
