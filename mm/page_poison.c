<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/page_ext.h>
#समावेश <linux/poison.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/kasan.h>

bool _page_poisoning_enabled_early;
EXPORT_SYMBOL(_page_poisoning_enabled_early);
DEFINE_STATIC_KEY_FALSE(_page_poisoning_enabled);
EXPORT_SYMBOL(_page_poisoning_enabled);

अटल पूर्णांक __init early_page_poison_param(अक्षर *buf)
अणु
	वापस kstrtobool(buf, &_page_poisoning_enabled_early);
पूर्ण
early_param("page_poison", early_page_poison_param);

अटल व्योम poison_page(काष्ठा page *page)
अणु
	व्योम *addr = kmap_atomic(page);

	/* KASAN still think the page is in-use, so skip it. */
	kasan_disable_current();
	स_रखो(kasan_reset_tag(addr), PAGE_POISON, PAGE_SIZE);
	kasan_enable_current();
	kunmap_atomic(addr);
पूर्ण

व्योम __kernel_poison_pages(काष्ठा page *page, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		poison_page(page + i);
पूर्ण

अटल bool single_bit_flip(अचिन्हित अक्षर a, अचिन्हित अक्षर b)
अणु
	अचिन्हित अक्षर error = a ^ b;

	वापस error && !(error & (error - 1));
पूर्ण

अटल व्योम check_poison_mem(काष्ठा page *page, अचिन्हित अक्षर *mem, माप_प्रकार bytes)
अणु
	अटल DEFINE_RATELIMIT_STATE(ratelimit, 5 * HZ, 10);
	अचिन्हित अक्षर *start;
	अचिन्हित अक्षर *end;

	start = स_प्रथम_inv(mem, PAGE_POISON, bytes);
	अगर (!start)
		वापस;

	क्रम (end = mem + bytes - 1; end > start; end--) अणु
		अगर (*end != PAGE_POISON)
			अवरोध;
	पूर्ण

	अगर (!__ratelimit(&ratelimit))
		वापस;
	अन्यथा अगर (start == end && single_bit_flip(*start, PAGE_POISON))
		pr_err("pagealloc: single bit error\n");
	अन्यथा
		pr_err("pagealloc: memory corruption\n");

	prपूर्णांक_hex_dump(KERN_ERR, "", DUMP_PREFIX_ADDRESS, 16, 1, start,
			end - start + 1, 1);
	dump_stack();
	dump_page(page, "pagealloc: corrupted page details");
पूर्ण

अटल व्योम unpoison_page(काष्ठा page *page)
अणु
	व्योम *addr;

	addr = kmap_atomic(page);
	kasan_disable_current();
	/*
	 * Page poisoning when enabled poisons each and every page
	 * that is मुक्तd to buddy. Thus no extra check is करोne to
	 * see अगर a page was poisoned.
	 */
	check_poison_mem(page, kasan_reset_tag(addr), PAGE_SIZE);
	kasan_enable_current();
	kunmap_atomic(addr);
पूर्ण

व्योम __kernel_unpoison_pages(काष्ठा page *page, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		unpoison_page(page + i);
पूर्ण

#अगर_अघोषित CONFIG_ARCH_SUPPORTS_DEBUG_PAGEALLOC
व्योम __kernel_map_pages(काष्ठा page *page, पूर्णांक numpages, पूर्णांक enable)
अणु
	/* This function करोes nothing, all work is करोne via poison pages */
पूर्ण
#पूर्ण_अगर
