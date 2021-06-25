<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/page.h
 *
 * Copyright (C) 1995-2003 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_PAGE_H
#घोषणा __ASM_PAGE_H

#समावेश <यंत्र/page-def.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/personality.h> /* क्रम READ_IMPLIES_EXEC */
#समावेश <यंत्र/pgtable-types.h>

काष्ठा page;
काष्ठा vm_area_काष्ठा;

बाह्य व्योम copy_page(व्योम *to, स्थिर व्योम *from);
बाह्य व्योम clear_page(व्योम *to);

व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma);
#घोषणा __HAVE_ARCH_COPY_USER_HIGHPAGE

व्योम copy_highpage(काष्ठा page *to, काष्ठा page *from);
#घोषणा __HAVE_ARCH_COPY_HIGHPAGE

#घोषणा __alloc_zeroed_user_highpage(movableflags, vma, vaddr) \
	alloc_page_vma(GFP_HIGHUSER | __GFP_ZERO | movableflags, vma, vaddr)
#घोषणा __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE

#घोषणा clear_user_page(page, vaddr, pg)	clear_page(page)
#घोषणा copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

प्रकार काष्ठा page *pgtable_t;

बाह्य पूर्णांक pfn_valid(अचिन्हित दीर्घ);

#समावेश <यंत्र/memory.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा VM_DATA_DEFAULT_FLAGS	(VM_DATA_FLAGS_TSK_EXEC | VM_MTE_ALLOWED)

#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर
