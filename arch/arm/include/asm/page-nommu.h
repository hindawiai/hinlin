<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/page-nommu.h
 *
 *  Copyright (C) 2004 Hyok S. Choi
 */

#अगर_अघोषित _ASMARM_PAGE_NOMMU_H
#घोषणा _ASMARM_PAGE_NOMMU_H

#घोषणा clear_page(page)	स_रखो((page), 0, PAGE_SIZE)
#घोषणा copy_page(to,from)	स_नकल((to), (from), PAGE_SIZE)

#घोषणा clear_user_page(page, vaddr, pg)	clear_page(page)
#घोषणा copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

/*
 * These are used to make use of C type-checking..
 */
प्रकार अचिन्हित दीर्घ pte_t;
प्रकार अचिन्हित दीर्घ pmd_t;
प्रकार अचिन्हित दीर्घ pgd_t[2];
प्रकार अचिन्हित दीर्घ pgprot_t;

#घोषणा pte_val(x)      (x)
#घोषणा pmd_val(x)      (x)
#घोषणा pgd_val(x)	((x)[0])
#घोषणा pgprot_val(x)   (x)

#घोषणा __pte(x)        (x)
#घोषणा __pmd(x)        (x)
#घोषणा __pgprot(x)     (x)

#पूर्ण_अगर
