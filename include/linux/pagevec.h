<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/pagevec.h
 *
 * In many places it is efficient to batch an operation up against multiple
 * pages.  A pagevec is a multipage container which is used क्रम that.
 */

#अगर_अघोषित _LINUX_PAGEVEC_H
#घोषणा _LINUX_PAGEVEC_H

#समावेश <linux/xarray.h>

/* 15 poपूर्णांकers + header align the pagevec काष्ठाure to a घातer of two */
#घोषणा PAGEVEC_SIZE	15

काष्ठा page;
काष्ठा address_space;

काष्ठा pagevec अणु
	अचिन्हित अक्षर nr;
	bool percpu_pvec_drained;
	काष्ठा page *pages[PAGEVEC_SIZE];
पूर्ण;

व्योम __pagevec_release(काष्ठा pagevec *pvec);
व्योम __pagevec_lru_add(काष्ठा pagevec *pvec);
व्योम pagevec_हटाओ_exceptionals(काष्ठा pagevec *pvec);
अचिन्हित pagevec_lookup_range(काष्ठा pagevec *pvec,
			      काष्ठा address_space *mapping,
			      pgoff_t *start, pgoff_t end);
अटल अंतरभूत अचिन्हित pagevec_lookup(काष्ठा pagevec *pvec,
				      काष्ठा address_space *mapping,
				      pgoff_t *start)
अणु
	वापस pagevec_lookup_range(pvec, mapping, start, (pgoff_t)-1);
पूर्ण

अचिन्हित pagevec_lookup_range_tag(काष्ठा pagevec *pvec,
		काष्ठा address_space *mapping, pgoff_t *index, pgoff_t end,
		xa_mark_t tag);
अटल अंतरभूत अचिन्हित pagevec_lookup_tag(काष्ठा pagevec *pvec,
		काष्ठा address_space *mapping, pgoff_t *index, xa_mark_t tag)
अणु
	वापस pagevec_lookup_range_tag(pvec, mapping, index, (pgoff_t)-1, tag);
पूर्ण

अटल अंतरभूत व्योम pagevec_init(काष्ठा pagevec *pvec)
अणु
	pvec->nr = 0;
	pvec->percpu_pvec_drained = false;
पूर्ण

अटल अंतरभूत व्योम pagevec_reinit(काष्ठा pagevec *pvec)
अणु
	pvec->nr = 0;
पूर्ण

अटल अंतरभूत अचिन्हित pagevec_count(काष्ठा pagevec *pvec)
अणु
	वापस pvec->nr;
पूर्ण

अटल अंतरभूत अचिन्हित pagevec_space(काष्ठा pagevec *pvec)
अणु
	वापस PAGEVEC_SIZE - pvec->nr;
पूर्ण

/*
 * Add a page to a pagevec.  Returns the number of slots still available.
 */
अटल अंतरभूत अचिन्हित pagevec_add(काष्ठा pagevec *pvec, काष्ठा page *page)
अणु
	pvec->pages[pvec->nr++] = page;
	वापस pagevec_space(pvec);
पूर्ण

अटल अंतरभूत व्योम pagevec_release(काष्ठा pagevec *pvec)
अणु
	अगर (pagevec_count(pvec))
		__pagevec_release(pvec);
पूर्ण

#पूर्ण_अगर /* _LINUX_PAGEVEC_H */
