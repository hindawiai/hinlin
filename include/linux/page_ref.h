<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PAGE_REF_H
#घोषणा _LINUX_PAGE_REF_H

#समावेश <linux/atomic.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/tracepoपूर्णांक-defs.h>

DECLARE_TRACEPOINT(page_ref_set);
DECLARE_TRACEPOINT(page_ref_mod);
DECLARE_TRACEPOINT(page_ref_mod_and_test);
DECLARE_TRACEPOINT(page_ref_mod_and_वापस);
DECLARE_TRACEPOINT(page_ref_mod_unless);
DECLARE_TRACEPOINT(page_ref_मुक्तze);
DECLARE_TRACEPOINT(page_ref_unमुक्तze);

#अगर_घोषित CONFIG_DEBUG_PAGE_REF

/*
 * Ideally we would want to use the trace_<tracepoपूर्णांक>_enabled() helper
 * functions. But due to include header file issues, that is not
 * feasible. Instead we have to खोलो code the अटल key functions.
 *
 * See trace_##name##_enabled(व्योम) in include/linux/tracepoपूर्णांक.h
 */
#घोषणा page_ref_tracepoपूर्णांक_active(t) tracepoपूर्णांक_enabled(t)

बाह्य व्योम __page_ref_set(काष्ठा page *page, पूर्णांक v);
बाह्य व्योम __page_ref_mod(काष्ठा page *page, पूर्णांक v);
बाह्य व्योम __page_ref_mod_and_test(काष्ठा page *page, पूर्णांक v, पूर्णांक ret);
बाह्य व्योम __page_ref_mod_and_वापस(काष्ठा page *page, पूर्णांक v, पूर्णांक ret);
बाह्य व्योम __page_ref_mod_unless(काष्ठा page *page, पूर्णांक v, पूर्णांक u);
बाह्य व्योम __page_ref_मुक्तze(काष्ठा page *page, पूर्णांक v, पूर्णांक ret);
बाह्य व्योम __page_ref_unमुक्तze(काष्ठा page *page, पूर्णांक v);

#अन्यथा

#घोषणा page_ref_tracepoपूर्णांक_active(t) false

अटल अंतरभूत व्योम __page_ref_set(काष्ठा page *page, पूर्णांक v)
अणु
पूर्ण
अटल अंतरभूत व्योम __page_ref_mod(काष्ठा page *page, पूर्णांक v)
अणु
पूर्ण
अटल अंतरभूत व्योम __page_ref_mod_and_test(काष्ठा page *page, पूर्णांक v, पूर्णांक ret)
अणु
पूर्ण
अटल अंतरभूत व्योम __page_ref_mod_and_वापस(काष्ठा page *page, पूर्णांक v, पूर्णांक ret)
अणु
पूर्ण
अटल अंतरभूत व्योम __page_ref_mod_unless(काष्ठा page *page, पूर्णांक v, पूर्णांक u)
अणु
पूर्ण
अटल अंतरभूत व्योम __page_ref_मुक्तze(काष्ठा page *page, पूर्णांक v, पूर्णांक ret)
अणु
पूर्ण
अटल अंतरभूत व्योम __page_ref_unमुक्तze(काष्ठा page *page, पूर्णांक v)
अणु
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत पूर्णांक page_ref_count(काष्ठा page *page)
अणु
	वापस atomic_पढ़ो(&page->_refcount);
पूर्ण

अटल अंतरभूत पूर्णांक page_count(काष्ठा page *page)
अणु
	वापस atomic_पढ़ो(&compound_head(page)->_refcount);
पूर्ण

अटल अंतरभूत व्योम set_page_count(काष्ठा page *page, पूर्णांक v)
अणु
	atomic_set(&page->_refcount, v);
	अगर (page_ref_tracepoपूर्णांक_active(page_ref_set))
		__page_ref_set(page, v);
पूर्ण

/*
 * Setup the page count beक्रमe being मुक्तd पूर्णांकo the page allocator क्रम
 * the first समय (boot or memory hotplug)
 */
अटल अंतरभूत व्योम init_page_count(काष्ठा page *page)
अणु
	set_page_count(page, 1);
पूर्ण

अटल अंतरभूत व्योम page_ref_add(काष्ठा page *page, पूर्णांक nr)
अणु
	atomic_add(nr, &page->_refcount);
	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod))
		__page_ref_mod(page, nr);
पूर्ण

अटल अंतरभूत व्योम page_ref_sub(काष्ठा page *page, पूर्णांक nr)
अणु
	atomic_sub(nr, &page->_refcount);
	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod))
		__page_ref_mod(page, -nr);
पूर्ण

अटल अंतरभूत पूर्णांक page_ref_sub_वापस(काष्ठा page *page, पूर्णांक nr)
अणु
	पूर्णांक ret = atomic_sub_वापस(nr, &page->_refcount);

	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod_and_वापस))
		__page_ref_mod_and_वापस(page, -nr, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम page_ref_inc(काष्ठा page *page)
अणु
	atomic_inc(&page->_refcount);
	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod))
		__page_ref_mod(page, 1);
पूर्ण

अटल अंतरभूत व्योम page_ref_dec(काष्ठा page *page)
अणु
	atomic_dec(&page->_refcount);
	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod))
		__page_ref_mod(page, -1);
पूर्ण

अटल अंतरभूत पूर्णांक page_ref_sub_and_test(काष्ठा page *page, पूर्णांक nr)
अणु
	पूर्णांक ret = atomic_sub_and_test(nr, &page->_refcount);

	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod_and_test))
		__page_ref_mod_and_test(page, -nr, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक page_ref_inc_वापस(काष्ठा page *page)
अणु
	पूर्णांक ret = atomic_inc_वापस(&page->_refcount);

	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod_and_वापस))
		__page_ref_mod_and_वापस(page, 1, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक page_ref_dec_and_test(काष्ठा page *page)
अणु
	पूर्णांक ret = atomic_dec_and_test(&page->_refcount);

	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod_and_test))
		__page_ref_mod_and_test(page, -1, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक page_ref_dec_वापस(काष्ठा page *page)
अणु
	पूर्णांक ret = atomic_dec_वापस(&page->_refcount);

	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod_and_वापस))
		__page_ref_mod_and_वापस(page, -1, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक page_ref_add_unless(काष्ठा page *page, पूर्णांक nr, पूर्णांक u)
अणु
	पूर्णांक ret = atomic_add_unless(&page->_refcount, nr, u);

	अगर (page_ref_tracepoपूर्णांक_active(page_ref_mod_unless))
		__page_ref_mod_unless(page, nr, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक page_ref_मुक्तze(काष्ठा page *page, पूर्णांक count)
अणु
	पूर्णांक ret = likely(atomic_cmpxchg(&page->_refcount, count, 0) == count);

	अगर (page_ref_tracepoपूर्णांक_active(page_ref_मुक्तze))
		__page_ref_मुक्तze(page, count, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम page_ref_unमुक्तze(काष्ठा page *page, पूर्णांक count)
अणु
	VM_BUG_ON_PAGE(page_count(page) != 0, page);
	VM_BUG_ON(count == 0);

	atomic_set_release(&page->_refcount, count);
	अगर (page_ref_tracepoपूर्णांक_active(page_ref_unमुक्तze))
		__page_ref_unमुक्तze(page, count);
पूर्ण

#पूर्ण_अगर
