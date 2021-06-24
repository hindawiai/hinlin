<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MM_PAGE_IDLE_H
#घोषणा _LINUX_MM_PAGE_IDLE_H

#समावेश <linux/bitops.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/page_ext.h>

#अगर_घोषित CONFIG_IDLE_PAGE_TRACKING

#अगर_घोषित CONFIG_64BIT
अटल अंतरभूत bool page_is_young(काष्ठा page *page)
अणु
	वापस PageYoung(page);
पूर्ण

अटल अंतरभूत व्योम set_page_young(काष्ठा page *page)
अणु
	SetPageYoung(page);
पूर्ण

अटल अंतरभूत bool test_and_clear_page_young(काष्ठा page *page)
अणु
	वापस TestClearPageYoung(page);
पूर्ण

अटल अंतरभूत bool page_is_idle(काष्ठा page *page)
अणु
	वापस PageIdle(page);
पूर्ण

अटल अंतरभूत व्योम set_page_idle(काष्ठा page *page)
अणु
	SetPageIdle(page);
पूर्ण

अटल अंतरभूत व्योम clear_page_idle(काष्ठा page *page)
अणु
	ClearPageIdle(page);
पूर्ण
#अन्यथा /* !CONFIG_64BIT */
/*
 * If there is not enough space to store Idle and Young bits in page flags, use
 * page ext flags instead.
 */
बाह्य काष्ठा page_ext_operations page_idle_ops;

अटल अंतरभूत bool page_is_young(काष्ठा page *page)
अणु
	काष्ठा page_ext *page_ext = lookup_page_ext(page);

	अगर (unlikely(!page_ext))
		वापस false;

	वापस test_bit(PAGE_EXT_YOUNG, &page_ext->flags);
पूर्ण

अटल अंतरभूत व्योम set_page_young(काष्ठा page *page)
अणु
	काष्ठा page_ext *page_ext = lookup_page_ext(page);

	अगर (unlikely(!page_ext))
		वापस;

	set_bit(PAGE_EXT_YOUNG, &page_ext->flags);
पूर्ण

अटल अंतरभूत bool test_and_clear_page_young(काष्ठा page *page)
अणु
	काष्ठा page_ext *page_ext = lookup_page_ext(page);

	अगर (unlikely(!page_ext))
		वापस false;

	वापस test_and_clear_bit(PAGE_EXT_YOUNG, &page_ext->flags);
पूर्ण

अटल अंतरभूत bool page_is_idle(काष्ठा page *page)
अणु
	काष्ठा page_ext *page_ext = lookup_page_ext(page);

	अगर (unlikely(!page_ext))
		वापस false;

	वापस test_bit(PAGE_EXT_IDLE, &page_ext->flags);
पूर्ण

अटल अंतरभूत व्योम set_page_idle(काष्ठा page *page)
अणु
	काष्ठा page_ext *page_ext = lookup_page_ext(page);

	अगर (unlikely(!page_ext))
		वापस;

	set_bit(PAGE_EXT_IDLE, &page_ext->flags);
पूर्ण

अटल अंतरभूत व्योम clear_page_idle(काष्ठा page *page)
अणु
	काष्ठा page_ext *page_ext = lookup_page_ext(page);

	अगर (unlikely(!page_ext))
		वापस;

	clear_bit(PAGE_EXT_IDLE, &page_ext->flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_64BIT */

#अन्यथा /* !CONFIG_IDLE_PAGE_TRACKING */

अटल अंतरभूत bool page_is_young(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम set_page_young(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत bool test_and_clear_page_young(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool page_is_idle(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम set_page_idle(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम clear_page_idle(काष्ठा page *page)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_IDLE_PAGE_TRACKING */

#पूर्ण_अगर /* _LINUX_MM_PAGE_IDLE_H */
