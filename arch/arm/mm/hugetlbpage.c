<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mm/hugetlbpage.c
 *
 * Copyright (C) 2012 ARM Ltd.
 *
 * Based on arch/x86/include/यंत्र/hugetlb.h and Bill Carson's patches
 */

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/err.h>
#समावेश <linux/sysctl.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>

/*
 * On ARM, huge pages are backed by pmd's rather than pte's, so we करो a lot
 * of type casting from pmd_t * to pte_t *.
 */

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस 0;
पूर्ण

पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस pmd_val(pmd) && !(pmd_val(pmd) & PMD_TABLE_BIT);
पूर्ण
