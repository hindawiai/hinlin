<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश <यंत्र/shmparam.h>

बाह्य व्योम flush_dcache_page(काष्ठा page *page);

अटल अंतरभूत अचिन्हित दीर्घ pages_करो_alias(अचिन्हित दीर्घ addr1,
					   अचिन्हित दीर्घ addr2)
अणु
	वापस (addr1 ^ addr2) & (SHMLBA-1);
पूर्ण

अटल अंतरभूत व्योम clear_user_page(व्योम *addr, अचिन्हित दीर्घ vaddr,
				   काष्ठा page *page)
अणु
	clear_page(addr);
	अगर (pages_करो_alias((अचिन्हित दीर्घ) addr, vaddr & PAGE_MASK))
		flush_dcache_page(page);
पूर्ण

अटल अंतरभूत व्योम copy_user_page(व्योम *to, व्योम *from, अचिन्हित दीर्घ vaddr,
				  काष्ठा page *page)
अणु
	copy_page(to, from);
	अगर (pages_करो_alias((अचिन्हित दीर्घ) to, vaddr & PAGE_MASK))
		flush_dcache_page(page);
पूर्ण
