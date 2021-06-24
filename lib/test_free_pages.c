<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * test_मुक्त_pages.c: Check that मुक्त_pages() करोesn't leak memory
 * Copyright (c) 2020 Oracle
 * Author: Matthew Wilcox <willy@infradead.org>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>

अटल व्योम test_मुक्त_pages(gfp_t gfp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 1000 * 1000; i++) अणु
		अचिन्हित दीर्घ addr = __get_मुक्त_pages(gfp, 3);
		काष्ठा page *page = virt_to_page(addr);

		/* Simulate page cache getting a speculative reference */
		get_page(page);
		मुक्त_pages(addr, 3);
		put_page(page);
	पूर्ण
पूर्ण

अटल पूर्णांक m_in(व्योम)
अणु
	pr_info("Testing with GFP_KERNEL\n");
	test_मुक्त_pages(GFP_KERNEL);
	pr_info("Testing with GFP_KERNEL | __GFP_COMP\n");
	test_मुक्त_pages(GFP_KERNEL | __GFP_COMP);
	pr_info("Test completed\n");

	वापस 0;
पूर्ण

अटल व्योम m_ex(व्योम)
अणु
पूर्ण

module_init(m_in);
module_निकास(m_ex);
MODULE_AUTHOR("Matthew Wilcox <willy@infradead.org>");
MODULE_LICENSE("GPL");
