<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */


#अगर_अघोषित _ASM_RISCV_MMU_H
#घोषणा _ASM_RISCV_MMU_H

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
#अगर_अघोषित CONFIG_MMU
	अचिन्हित दीर्घ	end_brk;
#अन्यथा
	atomic_दीर्घ_t id;
#पूर्ण_अगर
	व्योम *vdso;
#अगर_घोषित CONFIG_SMP
	/* A local icache flush is needed beक्रमe user execution can resume. */
	cpumask_t icache_stale_mask;
#पूर्ण_अगर
पूर्ण mm_context_t;

व्योम __init create_pgd_mapping(pgd_t *pgdp, uपूर्णांकptr_t va, phys_addr_t pa,
			       phys_addr_t sz, pgprot_t prot);
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_RISCV_MMU_H */
