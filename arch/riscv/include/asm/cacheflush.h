<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_CACHEFLUSH_H
#घोषणा _ASM_RISCV_CACHEFLUSH_H

#समावेश <linux/mm.h>

अटल अंतरभूत व्योम local_flush_icache_all(व्योम)
अणु
	यंत्र अस्थिर ("fence.i" ::: "memory");
पूर्ण

#घोषणा PG_dcache_clean PG_arch_1

अटल अंतरभूत व्योम flush_dcache_page(काष्ठा page *page)
अणु
	अगर (test_bit(PG_dcache_clean, &page->flags))
		clear_bit(PG_dcache_clean, &page->flags);
पूर्ण
#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1

/*
 * RISC-V करोesn't have an inकाष्ठाion to flush parts of the inकाष्ठाion cache,
 * so instead we just flush the whole thing.
 */
#घोषणा flush_icache_range(start, end) flush_icache_all()
#घोषणा flush_icache_user_page(vma, pg, addr, len) \
	flush_icache_mm(vma->vm_mm, 0)

#अगर_अघोषित CONFIG_SMP

#घोषणा flush_icache_all() local_flush_icache_all()
#घोषणा flush_icache_mm(mm, local) flush_icache_all()

#अन्यथा /* CONFIG_SMP */

व्योम flush_icache_all(व्योम);
व्योम flush_icache_mm(काष्ठा mm_काष्ठा *mm, bool local);

#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Bits in sys_riscv_flush_icache()'s flags argument.
 */
#घोषणा SYS_RISCV_FLUSH_ICACHE_LOCAL 1UL
#घोषणा SYS_RISCV_FLUSH_ICACHE_ALL   (SYS_RISCV_FLUSH_ICACHE_LOCAL)

#समावेश <यंत्र-generic/cacheflush.h>

#पूर्ण_अगर /* _ASM_RISCV_CACHEFLUSH_H */
