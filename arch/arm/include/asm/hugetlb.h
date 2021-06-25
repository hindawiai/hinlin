<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/hugetlb.h
 *
 * Copyright (C) 2012 ARM Ltd.
 *
 * Based on arch/x86/include/यंत्र/hugetlb.h
 */

#अगर_अघोषित _ASM_ARM_HUGETLB_H
#घोषणा _ASM_ARM_HUGETLB_H

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/hugetlb-3level.h>
#समावेश <यंत्र-generic/hugetlb.h>

अटल अंतरभूत व्योम arch_clear_hugepage_flags(काष्ठा page *page)
अणु
	clear_bit(PG_dcache_clean, &page->flags);
पूर्ण
#घोषणा arch_clear_hugepage_flags arch_clear_hugepage_flags

#पूर्ण_अगर /* _ASM_ARM_HUGETLB_H */
