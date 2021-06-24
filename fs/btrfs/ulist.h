<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2011 STRATO AG
 * written by Arne Jansen <sensille@gmx.net>
 */

#अगर_अघोषित BTRFS_ULIST_H
#घोषणा BTRFS_ULIST_H

#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>

/*
 * ulist is a generic data काष्ठाure to hold a collection of unique u64
 * values. The only operations it supports is adding to the list and
 * क्रमागतerating it.
 * It is possible to store an auxiliary value aदीर्घ with the key.
 *
 */
काष्ठा ulist_iterator अणु
	काष्ठा list_head *cur_list;  /* hपूर्णांक to start search */
पूर्ण;

/*
 * element of the list
 */
काष्ठा ulist_node अणु
	u64 val;		/* value to store */
	u64 aux;		/* auxiliary value saved aदीर्घ with the val */

	काष्ठा list_head list;  /* used to link node */
	काष्ठा rb_node rb_node;	/* used to speed up search */
पूर्ण;

काष्ठा ulist अणु
	/*
	 * number of elements stored in list
	 */
	अचिन्हित दीर्घ nnodes;

	काष्ठा list_head nodes;
	काष्ठा rb_root root;
पूर्ण;

व्योम ulist_init(काष्ठा ulist *ulist);
व्योम ulist_release(काष्ठा ulist *ulist);
व्योम ulist_reinit(काष्ठा ulist *ulist);
काष्ठा ulist *ulist_alloc(gfp_t gfp_mask);
व्योम ulist_मुक्त(काष्ठा ulist *ulist);
पूर्णांक ulist_add(काष्ठा ulist *ulist, u64 val, u64 aux, gfp_t gfp_mask);
पूर्णांक ulist_add_merge(काष्ठा ulist *ulist, u64 val, u64 aux,
		    u64 *old_aux, gfp_t gfp_mask);
पूर्णांक ulist_del(काष्ठा ulist *ulist, u64 val, u64 aux);

/* just like ulist_add_merge() but take a poपूर्णांकer क्रम the aux data */
अटल अंतरभूत पूर्णांक ulist_add_merge_ptr(काष्ठा ulist *ulist, u64 val, व्योम *aux,
				      व्योम **old_aux, gfp_t gfp_mask)
अणु
#अगर BITS_PER_LONG == 32
	u64 old64 = (uपूर्णांकptr_t)*old_aux;
	पूर्णांक ret = ulist_add_merge(ulist, val, (uपूर्णांकptr_t)aux, &old64, gfp_mask);
	*old_aux = (व्योम *)((uपूर्णांकptr_t)old64);
	वापस ret;
#अन्यथा
	वापस ulist_add_merge(ulist, val, (u64)aux, (u64 *)old_aux, gfp_mask);
#पूर्ण_अगर
पूर्ण

काष्ठा ulist_node *ulist_next(काष्ठा ulist *ulist,
			      काष्ठा ulist_iterator *uiter);

#घोषणा ULIST_ITER_INIT(uiter) ((uiter)->cur_list = शून्य)

#पूर्ण_अगर
