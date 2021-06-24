<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_MMAN_H__
#घोषणा __SPARC_MMAN_H__

#समावेश <uapi/यंत्र/mman.h>

#अगर_अघोषित __ASSEMBLY__
#घोषणा arch_mmap_check(addr,len,flags)	sparc_mmap_check(addr,len)
पूर्णांक sparc_mmap_check(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len);

#अगर_घोषित CONFIG_SPARC64
#समावेश <यंत्र/adi_64.h>

अटल अंतरभूत व्योम ipi_set_tstate_mcde(व्योम *arg)
अणु
	काष्ठा mm_काष्ठा *mm = arg;

	/* Set TSTATE_MCDE क्रम the task using address map that ADI has been
	 * enabled on अगर the task is running. If not, it will be set
	 * स्वतःmatically at the next context चयन
	 */
	अगर (current->mm == mm) अणु
		काष्ठा pt_regs *regs;

		regs = task_pt_regs(current);
		regs->tstate |= TSTATE_MCDE;
	पूर्ण
पूर्ण

#घोषणा arch_calc_vm_prot_bits(prot, pkey) sparc_calc_vm_prot_bits(prot)
अटल अंतरभूत अचिन्हित दीर्घ sparc_calc_vm_prot_bits(अचिन्हित दीर्घ prot)
अणु
	अगर (adi_capable() && (prot & PROT_ADI)) अणु
		काष्ठा pt_regs *regs;

		अगर (!current->mm->context.adi) अणु
			regs = task_pt_regs(current);
			regs->tstate |= TSTATE_MCDE;
			current->mm->context.adi = true;
			on_each_cpu_mask(mm_cpumask(current->mm),
					 ipi_set_tstate_mcde, current->mm, 0);
		पूर्ण
		वापस VM_SPARC_ADI;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा arch_vm_get_page_prot(vm_flags) sparc_vm_get_page_prot(vm_flags)
अटल अंतरभूत pgprot_t sparc_vm_get_page_prot(अचिन्हित दीर्घ vm_flags)
अणु
	वापस (vm_flags & VM_SPARC_ADI) ? __pgprot(_PAGE_MCD_4V) : __pgprot(0);
पूर्ण

#घोषणा arch_validate_prot(prot, addr) sparc_validate_prot(prot, addr)
अटल अंतरभूत पूर्णांक sparc_validate_prot(अचिन्हित दीर्घ prot, अचिन्हित दीर्घ addr)
अणु
	अगर (prot & ~(PROT_READ | PROT_WRITE | PROT_EXEC | PROT_SEM | PROT_ADI))
		वापस 0;
	वापस 1;
पूर्ण

#घोषणा arch_validate_flags(vm_flags) arch_validate_flags(vm_flags)
/* arch_validate_flags() - Ensure combination of flags is valid क्रम a
 *	VMA.
 */
अटल अंतरभूत bool arch_validate_flags(अचिन्हित दीर्घ vm_flags)
अणु
	/* If ADI is being enabled on this VMA, check क्रम ADI
	 * capability on the platक्रमm and ensure VMA is suitable
	 * क्रम ADI
	 */
	अगर (vm_flags & VM_SPARC_ADI) अणु
		अगर (!adi_capable())
			वापस false;

		/* ADI can not be enabled on PFN mapped pages */
		अगर (vm_flags & (VM_PFNMAP | VM_MIXEDMAP))
			वापस false;

		/* Mergeable pages can become unmergeable
		 * अगर ADI is enabled on them even अगर they
		 * have identical data on them. This can be
		 * because ADI enabled pages with identical
		 * data may still not have identical ADI
		 * tags on them. Disallow ADI on mergeable
		 * pages.
		 */
		अगर (vm_flags & VM_MERGEABLE)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARC64 */

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __SPARC_MMAN_H__ */
