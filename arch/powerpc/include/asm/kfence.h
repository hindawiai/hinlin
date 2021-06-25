<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * घातerpc KFENCE support.
 *
 * Copyright (C) 2020 CS GROUP France
 */

#अगर_अघोषित __ASM_POWERPC_KFENCE_H
#घोषणा __ASM_POWERPC_KFENCE_H

#समावेश <linux/mm.h>
#समावेश <यंत्र/pgtable.h>

अटल अंतरभूत bool arch_kfence_init_pool(व्योम)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool kfence_protect_page(अचिन्हित दीर्घ addr, bool protect)
अणु
	pte_t *kpte = virt_to_kpte(addr);

	अगर (protect) अणु
		pte_update(&init_mm, addr, kpte, _PAGE_PRESENT, 0, 0);
		flush_tlb_kernel_range(addr, addr + PAGE_SIZE);
	पूर्ण अन्यथा अणु
		pte_update(&init_mm, addr, kpte, 0, _PAGE_PRESENT, 0);
	पूर्ण

	वापस true;
पूर्ण

#पूर्ण_अगर /* __ASM_POWERPC_KFENCE_H */
