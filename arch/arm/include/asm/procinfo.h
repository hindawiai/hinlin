<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/procinfo.h
 *
 *  Copyright (C) 1996-1999 Russell King
 */
#अगर_अघोषित __ASM_PROCINFO_H
#घोषणा __ASM_PROCINFO_H

#अगर_घोषित __KERNEL__

काष्ठा cpu_tlb_fns;
काष्ठा cpu_user_fns;
काष्ठा cpu_cache_fns;
काष्ठा processor;

/*
 * Note!  काष्ठा processor is always defined अगर we're
 * using MULTI_CPU, otherwise this entry is unused,
 * but still exists.
 *
 * NOTE! The following काष्ठाure is defined by assembly
 * language, NOT C code.  For more inक्रमmation, check:
 *  arch/arm/mm/proc-*.S and arch/arm/kernel/head.S
 */
काष्ठा proc_info_list अणु
	अचिन्हित पूर्णांक		cpu_val;
	अचिन्हित पूर्णांक		cpu_mask;
	अचिन्हित दीर्घ		__cpu_mm_mmu_flags;	/* used by head.S */
	अचिन्हित दीर्घ		__cpu_io_mmu_flags;	/* used by head.S */
	अचिन्हित दीर्घ		__cpu_flush;		/* used by head.S */
	स्थिर अक्षर		*arch_name;
	स्थिर अक्षर		*elf_name;
	अचिन्हित पूर्णांक		elf_hwcap;
	स्थिर अक्षर		*cpu_name;
	काष्ठा processor	*proc;
	काष्ठा cpu_tlb_fns	*tlb;
	काष्ठा cpu_user_fns	*user;
	काष्ठा cpu_cache_fns	*cache;
पूर्ण;

#अन्यथा	/* __KERNEL__ */
#समावेश <यंत्र/elf.h>
#warning "Please include asm/elf.h instead"
#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर
