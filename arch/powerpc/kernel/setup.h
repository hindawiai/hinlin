<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Prototypes क्रम functions that are shared between setup_(32|64|common).c
 *
 * Copyright 2016 Michael Ellerman, IBM Corporation.
 */

#अगर_अघोषित __ARCH_POWERPC_KERNEL_SETUP_H
#घोषणा __ARCH_POWERPC_KERNEL_SETUP_H

व्योम initialize_cache_info(व्योम);
व्योम irqstack_early_init(व्योम);

#अगर_घोषित CONFIG_PPC32
व्योम setup_घातer_save(व्योम);
#अन्यथा
अटल अंतरभूत व्योम setup_घातer_save(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PPC64) && defined(CONFIG_SMP)
व्योम check_smt_enabled(व्योम);
#अन्यथा
अटल अंतरभूत व्योम check_smt_enabled(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_BOOK3E) && defined(CONFIG_SMP)
व्योम setup_tlb_core_data(व्योम);
#अन्यथा
अटल अंतरभूत व्योम setup_tlb_core_data(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_BOOK3E) || defined(CONFIG_BOOKE) || defined(CONFIG_40x)
व्योम exc_lvl_early_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम exc_lvl_early_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PPC64) || defined(CONFIG_VMAP_STACK)
व्योम emergency_stack_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम emergency_stack_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
u64 ppc64_bolted_size(व्योम);

/* Default SPR values from firmware/kexec */
बाह्य अचिन्हित दीर्घ spr_शेष_dscr;
#पूर्ण_अगर

/*
 * Having this in kvm_ppc.h makes include dependencies too
 * tricky to solve क्रम setup-common.c so have it here.
 */
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
व्योम kvm_cma_reserve(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kvm_cma_reserve(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TAU
u32 cpu_temp(अचिन्हित दीर्घ cpu);
u32 cpu_temp_both(अचिन्हित दीर्घ cpu);
u32 tau_पूर्णांकerrupts(अचिन्हित दीर्घ cpu);
#पूर्ण_अगर /* CONFIG_TAU */

#पूर्ण_अगर /* __ARCH_POWERPC_KERNEL_SETUP_H */
