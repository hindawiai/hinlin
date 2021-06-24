<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 */
#अगर_अघोषित _ASM_POWERPC_MMAN_H
#घोषणा _ASM_POWERPC_MMAN_H

#समावेश <uapi/यंत्र/mman.h>

#अगर_घोषित CONFIG_PPC64

#समावेश <यंत्र/cputable.h>
#समावेश <linux/mm.h>
#समावेश <linux/pkeys.h>
#समावेश <यंत्र/cpu_has_feature.h>

अटल अंतरभूत अचिन्हित दीर्घ arch_calc_vm_prot_bits(अचिन्हित दीर्घ prot,
		अचिन्हित दीर्घ pkey)
अणु
#अगर_घोषित CONFIG_PPC_MEM_KEYS
	वापस (((prot & PROT_SAO) ? VM_SAO : 0) | pkey_to_vmflag_bits(pkey));
#अन्यथा
	वापस ((prot & PROT_SAO) ? VM_SAO : 0);
#पूर्ण_अगर
पूर्ण
#घोषणा arch_calc_vm_prot_bits(prot, pkey) arch_calc_vm_prot_bits(prot, pkey)

अटल अंतरभूत pgprot_t arch_vm_get_page_prot(अचिन्हित दीर्घ vm_flags)
अणु
#अगर_घोषित CONFIG_PPC_MEM_KEYS
	वापस (vm_flags & VM_SAO) ?
		__pgprot(_PAGE_SAO | vmflag_to_pte_pkey_bits(vm_flags)) :
		__pgprot(0 | vmflag_to_pte_pkey_bits(vm_flags));
#अन्यथा
	वापस (vm_flags & VM_SAO) ? __pgprot(_PAGE_SAO) : __pgprot(0);
#पूर्ण_अगर
पूर्ण
#घोषणा arch_vm_get_page_prot(vm_flags) arch_vm_get_page_prot(vm_flags)

अटल अंतरभूत bool arch_validate_prot(अचिन्हित दीर्घ prot, अचिन्हित दीर्घ addr)
अणु
	अगर (prot & ~(PROT_READ | PROT_WRITE | PROT_EXEC | PROT_SEM | PROT_SAO))
		वापस false;
	अगर (prot & PROT_SAO) अणु
		अगर (!cpu_has_feature(CPU_FTR_SAO))
			वापस false;
		अगर (firmware_has_feature(FW_FEATURE_LPAR) &&
		    !IS_ENABLED(CONFIG_PPC_PROT_SAO_LPAR))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण
#घोषणा arch_validate_prot arch_validate_prot

#पूर्ण_अगर /* CONFIG_PPC64 */
#पूर्ण_अगर	/* _ASM_POWERPC_MMAN_H */
