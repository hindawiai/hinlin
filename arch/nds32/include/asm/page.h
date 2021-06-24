<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2005-2017 Andes Technology Corporation
 */

#अगर_अघोषित _ASMNDS32_PAGE_H
#घोषणा _ASMNDS32_PAGE_H

#अगर_घोषित CONFIG_ANDES_PAGE_SIZE_4KB
#घोषणा PAGE_SHIFT      12
#पूर्ण_अगर
#अगर_घोषित CONFIG_ANDES_PAGE_SIZE_8KB
#घोषणा PAGE_SHIFT      13
#पूर्ण_अगर
#समावेश <linux/स्थिर.h>
#घोषणा PAGE_SIZE       (_AC(1,UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK       (~(PAGE_SIZE-1))

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__

काष्ठा page;
काष्ठा vm_area_काष्ठा;
#अगर_घोषित CONFIG_CPU_CACHE_ALIASING
बाह्य व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			       अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma);
बाह्य व्योम clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr);

व्योम copy_user_page(व्योम *vto, व्योम *vfrom, अचिन्हित दीर्घ vaddr,
		    काष्ठा page *to);
व्योम clear_user_page(व्योम *addr, अचिन्हित दीर्घ vaddr, काष्ठा page *page);
#घोषणा __HAVE_ARCH_COPY_USER_HIGHPAGE
#घोषणा clear_user_highpage	clear_user_highpage
#अन्यथा
#घोषणा clear_user_page(page, vaddr, pg)        clear_page(page)
#घोषणा copy_user_page(to, from, vaddr, pg)     copy_page(to, from)
#पूर्ण_अगर

व्योम clear_page(व्योम *page);
व्योम copy_page(व्योम *to, व्योम *from);

प्रकार अचिन्हित दीर्घ pte_t;
प्रकार अचिन्हित दीर्घ pgd_t;
प्रकार अचिन्हित दीर्घ pgprot_t;

#घोषणा pte_val(x)      (x)
#घोषणा pgd_val(x)	(x)
#घोषणा pgprot_val(x)   (x)

#घोषणा __pte(x)        (x)
#घोषणा __pgd(x)        (x)
#घोषणा __pgprot(x)     (x)

प्रकार काष्ठा page *pgtable_t;

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर
