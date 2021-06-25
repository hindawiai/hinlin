<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
बाह्य काष्ठा btree_geo btree_geo128;

काष्ठा btree_head128 अणु काष्ठा btree_head h; पूर्ण;

अटल अंतरभूत व्योम btree_init_mempool128(काष्ठा btree_head128 *head,
					 mempool_t *mempool)
अणु
	btree_init_mempool(&head->h, mempool);
पूर्ण

अटल अंतरभूत पूर्णांक btree_init128(काष्ठा btree_head128 *head)
अणु
	वापस btree_init(&head->h);
पूर्ण

अटल अंतरभूत व्योम btree_destroy128(काष्ठा btree_head128 *head)
अणु
	btree_destroy(&head->h);
पूर्ण

अटल अंतरभूत व्योम *btree_lookup128(काष्ठा btree_head128 *head, u64 k1, u64 k2)
अणु
	u64 key[2] = अणुk1, k2पूर्ण;
	वापस btree_lookup(&head->h, &btree_geo128, (अचिन्हित दीर्घ *)&key);
पूर्ण

अटल अंतरभूत व्योम *btree_get_prev128(काष्ठा btree_head128 *head,
				      u64 *k1, u64 *k2)
अणु
	u64 key[2] = अणु*k1, *k2पूर्ण;
	व्योम *val;

	val = btree_get_prev(&head->h, &btree_geo128,
			     (अचिन्हित दीर्घ *)&key);
	*k1 = key[0];
	*k2 = key[1];
	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक btree_insert128(काष्ठा btree_head128 *head, u64 k1, u64 k2,
				  व्योम *val, gfp_t gfp)
अणु
	u64 key[2] = अणुk1, k2पूर्ण;
	वापस btree_insert(&head->h, &btree_geo128,
			    (अचिन्हित दीर्घ *)&key, val, gfp);
पूर्ण

अटल अंतरभूत पूर्णांक btree_update128(काष्ठा btree_head128 *head, u64 k1, u64 k2,
				  व्योम *val)
अणु
	u64 key[2] = अणुk1, k2पूर्ण;
	वापस btree_update(&head->h, &btree_geo128,
			    (अचिन्हित दीर्घ *)&key, val);
पूर्ण

अटल अंतरभूत व्योम *btree_हटाओ128(काष्ठा btree_head128 *head, u64 k1, u64 k2)
अणु
	u64 key[2] = अणुk1, k2पूर्ण;
	वापस btree_हटाओ(&head->h, &btree_geo128, (अचिन्हित दीर्घ *)&key);
पूर्ण

अटल अंतरभूत व्योम *btree_last128(काष्ठा btree_head128 *head, u64 *k1, u64 *k2)
अणु
	u64 key[2];
	व्योम *val;

	val = btree_last(&head->h, &btree_geo128, (अचिन्हित दीर्घ *)&key[0]);
	अगर (val) अणु
		*k1 = key[0];
		*k2 = key[1];
	पूर्ण

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक btree_merge128(काष्ठा btree_head128 *target,
				 काष्ठा btree_head128 *victim,
				 gfp_t gfp)
अणु
	वापस btree_merge(&target->h, &victim->h, &btree_geo128, gfp);
पूर्ण

व्योम visitor128(व्योम *elem, अचिन्हित दीर्घ opaque, अचिन्हित दीर्घ *__key,
		माप_प्रकार index, व्योम *__func);

प्रकार व्योम (*visitor128_t)(व्योम *elem, अचिन्हित दीर्घ opaque,
			     u64 key1, u64 key2, माप_प्रकार index);

अटल अंतरभूत माप_प्रकार btree_visitor128(काष्ठा btree_head128 *head,
				      अचिन्हित दीर्घ opaque,
				      visitor128_t func2)
अणु
	वापस btree_visitor(&head->h, &btree_geo128, opaque,
			     visitor128, func2);
पूर्ण

अटल अंतरभूत माप_प्रकार btree_grim_visitor128(काष्ठा btree_head128 *head,
					   अचिन्हित दीर्घ opaque,
					   visitor128_t func2)
अणु
	वापस btree_grim_visitor(&head->h, &btree_geo128, opaque,
				  visitor128, func2);
पूर्ण

#घोषणा btree_क्रम_each_safe128(head, k1, k2, val)	\
	क्रम (val = btree_last128(head, &k1, &k2);	\
	     val;					\
	     val = btree_get_prev128(head, &k1, &k2))

