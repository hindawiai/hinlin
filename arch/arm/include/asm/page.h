<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/page.h
 *
 *  Copyright (C) 1995-2003 Russell King
 */
#अगर_अघोषित _ASMARM_PAGE_H
#घोषणा _ASMARM_PAGE_H

/* PAGE_SHIFT determines the page size */
#घोषणा PAGE_SHIFT		12
#घोषणा PAGE_SIZE		(_AC(1,UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK		(~((1 << PAGE_SHIFT) - 1))

#अगर_अघोषित __ASSEMBLY__

#अगर_अघोषित CONFIG_MMU

#समावेश <यंत्र/page-nommu.h>

#अन्यथा

#समावेश <यंत्र/glue.h>

/*
 *	User Space Model
 *	================
 *
 *	This section selects the correct set of functions क्रम dealing with
 *	page-based copying and clearing क्रम user space क्रम the particular
 *	processor(s) we're building क्रम.
 *
 *	We have the following to choose from:
 *	  v4wt		- ARMv4 with ग_लिखोthrough cache, without minicache
 *	  v4wb		- ARMv4 with ग_लिखोback cache, without minicache
 *	  v4_mc		- ARMv4 with minicache
 *	  xscale	- Xscale
 *	  xsc3		- XScalev3
 */
#अघोषित _USER
#अघोषित MULTI_USER

#अगर_घोषित CONFIG_CPU_COPY_V4WT
# अगरdef _USER
#  define MULTI_USER 1
# अन्यथा
#  define _USER v4wt
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_COPY_V4WB
# अगरdef _USER
#  define MULTI_USER 1
# अन्यथा
#  define _USER v4wb
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_COPY_FEROCEON
# अगरdef _USER
#  define MULTI_USER 1
# अन्यथा
#  define _USER feroceon
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_COPY_FA
# अगरdef _USER
#  define MULTI_USER 1
# अन्यथा
#  define _USER fa
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_SA1100
# अगरdef _USER
#  define MULTI_USER 1
# अन्यथा
#  define _USER v4_mc
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_XSCALE
# अगरdef _USER
#  define MULTI_USER 1
# अन्यथा
#  define _USER xscale_mc
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_XSC3
# अगरdef _USER
#  define MULTI_USER 1
# अन्यथा
#  define _USER xsc3_mc
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_COPY_V6
# define MULTI_USER 1
#पूर्ण_अगर

#अगर !defined(_USER) && !defined(MULTI_USER)
#त्रुटि Unknown user operations model
#पूर्ण_अगर

काष्ठा page;
काष्ठा vm_area_काष्ठा;

काष्ठा cpu_user_fns अणु
	व्योम (*cpu_clear_user_highpage)(काष्ठा page *page, अचिन्हित दीर्घ vaddr);
	व्योम (*cpu_copy_user_highpage)(काष्ठा page *to, काष्ठा page *from,
			अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma);
पूर्ण;

#अगर_घोषित MULTI_USER
बाह्य काष्ठा cpu_user_fns cpu_user;

#घोषणा __cpu_clear_user_highpage	cpu_user.cpu_clear_user_highpage
#घोषणा __cpu_copy_user_highpage	cpu_user.cpu_copy_user_highpage

#अन्यथा

#घोषणा __cpu_clear_user_highpage	__glue(_USER,_clear_user_highpage)
#घोषणा __cpu_copy_user_highpage	__glue(_USER,_copy_user_highpage)

बाह्य व्योम __cpu_clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr);
बाह्य व्योम __cpu_copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma);
#पूर्ण_अगर

#घोषणा clear_user_highpage(page,vaddr)		\
	 __cpu_clear_user_highpage(page, vaddr)

#घोषणा __HAVE_ARCH_COPY_USER_HIGHPAGE
#घोषणा copy_user_highpage(to,from,vaddr,vma)	\
	__cpu_copy_user_highpage(to, from, vaddr, vma)

#घोषणा clear_page(page)	स_रखो((व्योम *)(page), 0, PAGE_SIZE)
बाह्य व्योम copy_page(व्योम *to, स्थिर व्योम *from);

#अगर_घोषित CONFIG_KUSER_HELPERS
#घोषणा __HAVE_ARCH_GATE_AREA 1
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM_LPAE
#समावेश <यंत्र/pgtable-3level-types.h>
#अन्यथा
#समावेश <यंत्र/pgtable-2level-types.h>
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_MMU */

प्रकार काष्ठा page *pgtable_t;

#अगर_घोषित CONFIG_HAVE_ARCH_PFN_VALID
बाह्य पूर्णांक pfn_valid(अचिन्हित दीर्घ);
#पूर्ण_अगर

#समावेश <यंत्र/memory.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_TSK_EXEC

#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर
