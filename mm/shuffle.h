<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright(c) 2018 Intel Corporation. All rights reserved.
#अगर_अघोषित _MM_SHUFFLE_H
#घोषणा _MM_SHUFFLE_H
#समावेश <linux/jump_label.h>

#घोषणा SHUFFLE_ORDER (MAX_ORDER-1)

#अगर_घोषित CONFIG_SHUFFLE_PAGE_ALLOCATOR
DECLARE_STATIC_KEY_FALSE(page_alloc_shuffle_key);
बाह्य व्योम __shuffle_मुक्त_memory(pg_data_t *pgdat);
बाह्य bool shuffle_pick_tail(व्योम);
अटल अंतरभूत व्योम __meminit shuffle_मुक्त_memory(pg_data_t *pgdat)
अणु
	अगर (!अटल_branch_unlikely(&page_alloc_shuffle_key))
		वापस;
	__shuffle_मुक्त_memory(pgdat);
पूर्ण

बाह्य व्योम __shuffle_zone(काष्ठा zone *z);
अटल अंतरभूत व्योम __meminit shuffle_zone(काष्ठा zone *z)
अणु
	अगर (!अटल_branch_unlikely(&page_alloc_shuffle_key))
		वापस;
	__shuffle_zone(z);
पूर्ण

अटल अंतरभूत bool is_shuffle_order(पूर्णांक order)
अणु
	अगर (!अटल_branch_unlikely(&page_alloc_shuffle_key))
		वापस false;
	वापस order >= SHUFFLE_ORDER;
पूर्ण
#अन्यथा
अटल अंतरभूत bool shuffle_pick_tail(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम shuffle_मुक्त_memory(pg_data_t *pgdat)
अणु
पूर्ण

अटल अंतरभूत व्योम shuffle_zone(काष्ठा zone *z)
अणु
पूर्ण

अटल अंतरभूत bool is_shuffle_order(पूर्णांक order)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _MM_SHUFFLE_H */
