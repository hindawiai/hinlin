<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा __BTREE_TP(pfx, type, sfx)	pfx ## type ## sfx
#घोषणा _BTREE_TP(pfx, type, sfx)	__BTREE_TP(pfx, type, sfx)
#घोषणा BTREE_TP(pfx)			_BTREE_TP(pfx, BTREE_TYPE_SUFFIX,)
#घोषणा BTREE_FN(name)			BTREE_TP(btree_ ## name)
#घोषणा BTREE_TYPE_HEAD			BTREE_TP(काष्ठा btree_head)
#घोषणा VISITOR_FN			BTREE_TP(visitor)
#घोषणा VISITOR_FN_T			_BTREE_TP(visitor, BTREE_TYPE_SUFFIX, _t)

BTREE_TYPE_HEAD अणु
	काष्ठा btree_head h;
पूर्ण;

अटल अंतरभूत व्योम BTREE_FN(init_mempool)(BTREE_TYPE_HEAD *head,
					  mempool_t *mempool)
अणु
	btree_init_mempool(&head->h, mempool);
पूर्ण

अटल अंतरभूत पूर्णांक BTREE_FN(init)(BTREE_TYPE_HEAD *head)
अणु
	वापस btree_init(&head->h);
पूर्ण

अटल अंतरभूत व्योम BTREE_FN(destroy)(BTREE_TYPE_HEAD *head)
अणु
	btree_destroy(&head->h);
पूर्ण

अटल अंतरभूत पूर्णांक BTREE_FN(merge)(BTREE_TYPE_HEAD *target,
				  BTREE_TYPE_HEAD *victim,
				  gfp_t gfp)
अणु
	वापस btree_merge(&target->h, &victim->h, BTREE_TYPE_GEO, gfp);
पूर्ण

#अगर (BITS_PER_LONG > BTREE_TYPE_BITS)
अटल अंतरभूत व्योम *BTREE_FN(lookup)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE key)
अणु
	अचिन्हित दीर्घ _key = key;
	वापस btree_lookup(&head->h, BTREE_TYPE_GEO, &_key);
पूर्ण

अटल अंतरभूत पूर्णांक BTREE_FN(insert)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE key,
				   व्योम *val, gfp_t gfp)
अणु
	अचिन्हित दीर्घ _key = key;
	वापस btree_insert(&head->h, BTREE_TYPE_GEO, &_key, val, gfp);
पूर्ण

अटल अंतरभूत पूर्णांक BTREE_FN(update)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE key,
		व्योम *val)
अणु
	अचिन्हित दीर्घ _key = key;
	वापस btree_update(&head->h, BTREE_TYPE_GEO, &_key, val);
पूर्ण

अटल अंतरभूत व्योम *BTREE_FN(हटाओ)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE key)
अणु
	अचिन्हित दीर्घ _key = key;
	वापस btree_हटाओ(&head->h, BTREE_TYPE_GEO, &_key);
पूर्ण

अटल अंतरभूत व्योम *BTREE_FN(last)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE *key)
अणु
	अचिन्हित दीर्घ _key;
	व्योम *val = btree_last(&head->h, BTREE_TYPE_GEO, &_key);
	अगर (val)
		*key = _key;
	वापस val;
पूर्ण

अटल अंतरभूत व्योम *BTREE_FN(get_prev)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE *key)
अणु
	अचिन्हित दीर्घ _key = *key;
	व्योम *val = btree_get_prev(&head->h, BTREE_TYPE_GEO, &_key);
	अगर (val)
		*key = _key;
	वापस val;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम *BTREE_FN(lookup)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE key)
अणु
	वापस btree_lookup(&head->h, BTREE_TYPE_GEO, (अचिन्हित दीर्घ *)&key);
पूर्ण

अटल अंतरभूत पूर्णांक BTREE_FN(insert)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE key,
			   व्योम *val, gfp_t gfp)
अणु
	वापस btree_insert(&head->h, BTREE_TYPE_GEO, (अचिन्हित दीर्घ *)&key,
			    val, gfp);
पूर्ण

अटल अंतरभूत पूर्णांक BTREE_FN(update)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE key,
		व्योम *val)
अणु
	वापस btree_update(&head->h, BTREE_TYPE_GEO, (अचिन्हित दीर्घ *)&key, val);
पूर्ण

अटल अंतरभूत व्योम *BTREE_FN(हटाओ)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE key)
अणु
	वापस btree_हटाओ(&head->h, BTREE_TYPE_GEO, (अचिन्हित दीर्घ *)&key);
पूर्ण

अटल अंतरभूत व्योम *BTREE_FN(last)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE *key)
अणु
	वापस btree_last(&head->h, BTREE_TYPE_GEO, (अचिन्हित दीर्घ *)key);
पूर्ण

अटल अंतरभूत व्योम *BTREE_FN(get_prev)(BTREE_TYPE_HEAD *head, BTREE_KEYTYPE *key)
अणु
	वापस btree_get_prev(&head->h, BTREE_TYPE_GEO, (अचिन्हित दीर्घ *)key);
पूर्ण
#पूर्ण_अगर

व्योम VISITOR_FN(व्योम *elem, अचिन्हित दीर्घ opaque, अचिन्हित दीर्घ *key,
		माप_प्रकार index, व्योम *__func);

प्रकार व्योम (*VISITOR_FN_T)(व्योम *elem, अचिन्हित दीर्घ opaque,
			     BTREE_KEYTYPE key, माप_प्रकार index);

अटल अंतरभूत माप_प्रकार BTREE_FN(visitor)(BTREE_TYPE_HEAD *head,
				       अचिन्हित दीर्घ opaque,
				       VISITOR_FN_T func2)
अणु
	वापस btree_visitor(&head->h, BTREE_TYPE_GEO, opaque,
			     visitorl, func2);
पूर्ण

अटल अंतरभूत माप_प्रकार BTREE_FN(grim_visitor)(BTREE_TYPE_HEAD *head,
					    अचिन्हित दीर्घ opaque,
					    VISITOR_FN_T func2)
अणु
	वापस btree_grim_visitor(&head->h, BTREE_TYPE_GEO, opaque,
				  visitorl, func2);
पूर्ण

#अघोषित VISITOR_FN
#अघोषित VISITOR_FN_T
#अघोषित __BTREE_TP
#अघोषित _BTREE_TP
#अघोषित BTREE_TP
#अघोषित BTREE_FN
#अघोषित BTREE_TYPE_HEAD
#अघोषित BTREE_TYPE_SUFFIX
#अघोषित BTREE_TYPE_GEO
#अघोषित BTREE_KEYTYPE
#अघोषित BTREE_TYPE_BITS
