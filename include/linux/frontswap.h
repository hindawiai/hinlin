<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FRONTSWAP_H
#घोषणा _LINUX_FRONTSWAP_H

#समावेश <linux/swap.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/jump_label.h>

/*
 * Return code to denote that requested number of
 * frontswap pages are unused(moved to page cache).
 * Used in shmem_unuse and try_to_unuse.
 */
#घोषणा FRONTSWAP_PAGES_UNUSED	2

काष्ठा frontswap_ops अणु
	व्योम (*init)(अचिन्हित); /* this swap type was just swapon'ed */
	पूर्णांक (*store)(अचिन्हित, pgoff_t, काष्ठा page *); /* store a page */
	पूर्णांक (*load)(अचिन्हित, pgoff_t, काष्ठा page *); /* load a page */
	व्योम (*invalidate_page)(अचिन्हित, pgoff_t); /* page no दीर्घer needed */
	व्योम (*invalidate_area)(अचिन्हित); /* swap type just swapoff'ed */
	काष्ठा frontswap_ops *next; /* निजी poपूर्णांकer to next ops */
पूर्ण;

बाह्य व्योम frontswap_रेजिस्टर_ops(काष्ठा frontswap_ops *ops);
बाह्य व्योम frontswap_shrink(अचिन्हित दीर्घ);
बाह्य अचिन्हित दीर्घ frontswap_curr_pages(व्योम);
बाह्य व्योम frontswap_ग_लिखोthrough(bool);
#घोषणा FRONTSWAP_HAS_EXCLUSIVE_GETS
बाह्य व्योम frontswap_पंचांगem_exclusive_माला_लो(bool);

बाह्य bool __frontswap_test(काष्ठा swap_info_काष्ठा *, pgoff_t);
बाह्य व्योम __frontswap_init(अचिन्हित type, अचिन्हित दीर्घ *map);
बाह्य पूर्णांक __frontswap_store(काष्ठा page *page);
बाह्य पूर्णांक __frontswap_load(काष्ठा page *page);
बाह्य व्योम __frontswap_invalidate_page(अचिन्हित, pgoff_t);
बाह्य व्योम __frontswap_invalidate_area(अचिन्हित);

#अगर_घोषित CONFIG_FRONTSWAP
बाह्य काष्ठा अटल_key_false frontswap_enabled_key;

अटल अंतरभूत bool frontswap_enabled(व्योम)
अणु
	वापस अटल_branch_unlikely(&frontswap_enabled_key);
पूर्ण

अटल अंतरभूत bool frontswap_test(काष्ठा swap_info_काष्ठा *sis, pgoff_t offset)
अणु
	वापस __frontswap_test(sis, offset);
पूर्ण

अटल अंतरभूत व्योम frontswap_map_set(काष्ठा swap_info_काष्ठा *p,
				     अचिन्हित दीर्घ *map)
अणु
	p->frontswap_map = map;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *frontswap_map_get(काष्ठा swap_info_काष्ठा *p)
अणु
	वापस p->frontswap_map;
पूर्ण
#अन्यथा
/* all अंतरभूत routines become no-ops and all बाह्यs are ignored */

अटल अंतरभूत bool frontswap_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool frontswap_test(काष्ठा swap_info_काष्ठा *sis, pgoff_t offset)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम frontswap_map_set(काष्ठा swap_info_काष्ठा *p,
				     अचिन्हित दीर्घ *map)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *frontswap_map_get(काष्ठा swap_info_काष्ठा *p)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक frontswap_store(काष्ठा page *page)
अणु
	अगर (frontswap_enabled())
		वापस __frontswap_store(page);

	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक frontswap_load(काष्ठा page *page)
अणु
	अगर (frontswap_enabled())
		वापस __frontswap_load(page);

	वापस -1;
पूर्ण

अटल अंतरभूत व्योम frontswap_invalidate_page(अचिन्हित type, pgoff_t offset)
अणु
	अगर (frontswap_enabled())
		__frontswap_invalidate_page(type, offset);
पूर्ण

अटल अंतरभूत व्योम frontswap_invalidate_area(अचिन्हित type)
अणु
	अगर (frontswap_enabled())
		__frontswap_invalidate_area(type);
पूर्ण

अटल अंतरभूत व्योम frontswap_init(अचिन्हित type, अचिन्हित दीर्घ *map)
अणु
#अगर_घोषित CONFIG_FRONTSWAP
	__frontswap_init(type, map);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _LINUX_FRONTSWAP_H */
