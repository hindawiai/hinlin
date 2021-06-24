<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित PAGE_ACTOR_H
#घोषणा PAGE_ACTOR_H
/*
 * Copyright (c) 2013
 * Phillip Lougher <phillip@squashfs.org.uk>
 */

#अगर_अघोषित CONFIG_SQUASHFS_खाता_सूचीECT
काष्ठा squashfs_page_actor अणु
	व्योम	**page;
	पूर्णांक	pages;
	पूर्णांक	length;
	पूर्णांक	next_page;
पूर्ण;

अटल अंतरभूत काष्ठा squashfs_page_actor *squashfs_page_actor_init(व्योम **page,
	पूर्णांक pages, पूर्णांक length)
अणु
	काष्ठा squashfs_page_actor *actor = kदो_स्मृति(माप(*actor), GFP_KERNEL);

	अगर (actor == शून्य)
		वापस शून्य;

	actor->length = length ? : pages * PAGE_SIZE;
	actor->page = page;
	actor->pages = pages;
	actor->next_page = 0;
	वापस actor;
पूर्ण

अटल अंतरभूत व्योम *squashfs_first_page(काष्ठा squashfs_page_actor *actor)
अणु
	actor->next_page = 1;
	वापस actor->page[0];
पूर्ण

अटल अंतरभूत व्योम *squashfs_next_page(काष्ठा squashfs_page_actor *actor)
अणु
	वापस actor->next_page == actor->pages ? शून्य :
		actor->page[actor->next_page++];
पूर्ण

अटल अंतरभूत व्योम squashfs_finish_page(काष्ठा squashfs_page_actor *actor)
अणु
	/* empty */
पूर्ण
#अन्यथा
काष्ठा squashfs_page_actor अणु
	जोड़ अणु
		व्योम		**buffer;
		काष्ठा page	**page;
	पूर्ण;
	व्योम	*pageaddr;
	व्योम    *(*squashfs_first_page)(काष्ठा squashfs_page_actor *);
	व्योम    *(*squashfs_next_page)(काष्ठा squashfs_page_actor *);
	व्योम    (*squashfs_finish_page)(काष्ठा squashfs_page_actor *);
	पूर्णांक	pages;
	पूर्णांक	length;
	पूर्णांक	next_page;
पूर्ण;

बाह्य काष्ठा squashfs_page_actor *squashfs_page_actor_init(व्योम **, पूर्णांक, पूर्णांक);
बाह्य काष्ठा squashfs_page_actor *squashfs_page_actor_init_special(काष्ठा page
							 **, पूर्णांक, पूर्णांक);
अटल अंतरभूत व्योम *squashfs_first_page(काष्ठा squashfs_page_actor *actor)
अणु
	वापस actor->squashfs_first_page(actor);
पूर्ण
अटल अंतरभूत व्योम *squashfs_next_page(काष्ठा squashfs_page_actor *actor)
अणु
	वापस actor->squashfs_next_page(actor);
पूर्ण
अटल अंतरभूत व्योम squashfs_finish_page(काष्ठा squashfs_page_actor *actor)
अणु
	actor->squashfs_finish_page(actor);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
