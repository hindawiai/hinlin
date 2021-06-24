<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ___ASM_SPARC_PAGE_H
#घोषणा ___ASM_SPARC_PAGE_H

#घोषणा page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)

#अगर defined(__sparc__) && defined(__arch64__)
#समावेश <यंत्र/page_64.h>
#अन्यथा
#समावेश <यंत्र/page_32.h>
#पूर्ण_अगर
#पूर्ण_अगर
