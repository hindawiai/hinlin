<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#अगर_अघोषित __EROFS_FS_ZPVEC_H
#घोषणा __EROFS_FS_ZPVEC_H

#समावेश "tagptr.h"

/* page type in pagevec क्रम decompress subप्रणाली */
क्रमागत z_erofs_page_type अणु
	/* including Z_EROFS_VLE_PAGE_TAIL_EXCLUSIVE */
	Z_EROFS_PAGE_TYPE_EXCLUSIVE,

	Z_EROFS_VLE_PAGE_TYPE_TAIL_SHARED,

	Z_EROFS_VLE_PAGE_TYPE_HEAD,
	Z_EROFS_VLE_PAGE_TYPE_MAX
पूर्ण;

बाह्य व्योम __compileसमय_error("Z_EROFS_PAGE_TYPE_EXCLUSIVE != 0")
	__bad_page_type_exclusive(व्योम);

/* pagevec tagged poपूर्णांकer */
प्रकार tagptr2_t	erofs_vtptr_t;

/* pagevec collector */
काष्ठा z_erofs_pagevec_ctor अणु
	काष्ठा page *curr, *next;
	erofs_vtptr_t *pages;

	अचिन्हित पूर्णांक nr, index;
पूर्ण;

अटल अंतरभूत व्योम z_erofs_pagevec_ctor_निकास(काष्ठा z_erofs_pagevec_ctor *ctor,
					     bool atomic)
अणु
	अगर (!ctor->curr)
		वापस;

	अगर (atomic)
		kunmap_atomic(ctor->pages);
	अन्यथा
		kunmap(ctor->curr);
पूर्ण

अटल अंतरभूत काष्ठा page *
z_erofs_pagevec_ctor_next_page(काष्ठा z_erofs_pagevec_ctor *ctor,
			       अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक index;

	/* keep away from occupied pages */
	अगर (ctor->next)
		वापस ctor->next;

	क्रम (index = 0; index < nr; ++index) अणु
		स्थिर erofs_vtptr_t t = ctor->pages[index];
		स्थिर अचिन्हित पूर्णांक tags = tagptr_unfold_tags(t);

		अगर (tags == Z_EROFS_PAGE_TYPE_EXCLUSIVE)
			वापस tagptr_unfold_ptr(t);
	पूर्ण
	DBG_BUGON(nr >= ctor->nr);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
z_erofs_pagevec_ctor_pageकरोwn(काष्ठा z_erofs_pagevec_ctor *ctor,
			      bool atomic)
अणु
	काष्ठा page *next = z_erofs_pagevec_ctor_next_page(ctor, ctor->nr);

	z_erofs_pagevec_ctor_निकास(ctor, atomic);

	ctor->curr = next;
	ctor->next = शून्य;
	ctor->pages = atomic ?
		kmap_atomic(ctor->curr) : kmap(ctor->curr);

	ctor->nr = PAGE_SIZE / माप(काष्ठा page *);
	ctor->index = 0;
पूर्ण

अटल अंतरभूत व्योम z_erofs_pagevec_ctor_init(काष्ठा z_erofs_pagevec_ctor *ctor,
					     अचिन्हित पूर्णांक nr,
					     erofs_vtptr_t *pages,
					     अचिन्हित पूर्णांक i)
अणु
	ctor->nr = nr;
	ctor->curr = ctor->next = शून्य;
	ctor->pages = pages;

	अगर (i >= nr) अणु
		i -= nr;
		z_erofs_pagevec_ctor_pageकरोwn(ctor, false);
		जबतक (i > ctor->nr) अणु
			i -= ctor->nr;
			z_erofs_pagevec_ctor_pageकरोwn(ctor, false);
		पूर्ण
	पूर्ण
	ctor->next = z_erofs_pagevec_ctor_next_page(ctor, i);
	ctor->index = i;
पूर्ण

अटल अंतरभूत bool z_erofs_pagevec_enqueue(काष्ठा z_erofs_pagevec_ctor *ctor,
					   काष्ठा page *page,
					   क्रमागत z_erofs_page_type type,
					   bool *occupied)
अणु
	*occupied = false;
	अगर (!ctor->next && type)
		अगर (ctor->index + 1 == ctor->nr)
			वापस false;

	अगर (ctor->index >= ctor->nr)
		z_erofs_pagevec_ctor_pageकरोwn(ctor, false);

	/* exclusive page type must be 0 */
	अगर (Z_EROFS_PAGE_TYPE_EXCLUSIVE != (uपूर्णांकptr_t)शून्य)
		__bad_page_type_exclusive();

	/* should remind that collector->next never equal to 1, 2 */
	अगर (type == (uपूर्णांकptr_t)ctor->next) अणु
		ctor->next = page;
		*occupied = true;
	पूर्ण
	ctor->pages[ctor->index++] = tagptr_fold(erofs_vtptr_t, page, type);
	वापस true;
पूर्ण

अटल अंतरभूत काष्ठा page *
z_erofs_pagevec_dequeue(काष्ठा z_erofs_pagevec_ctor *ctor,
			क्रमागत z_erofs_page_type *type)
अणु
	erofs_vtptr_t t;

	अगर (ctor->index >= ctor->nr) अणु
		DBG_BUGON(!ctor->next);
		z_erofs_pagevec_ctor_pageकरोwn(ctor, true);
	पूर्ण

	t = ctor->pages[ctor->index];

	*type = tagptr_unfold_tags(t);

	/* should remind that collector->next never equal to 1, 2 */
	अगर (*type == (uपूर्णांकptr_t)ctor->next)
		ctor->next = tagptr_unfold_ptr(t);

	ctor->pages[ctor->index++] = tagptr_fold(erofs_vtptr_t, शून्य, 0);
	वापस tagptr_unfold_ptr(t);
पूर्ण
#पूर्ण_अगर

