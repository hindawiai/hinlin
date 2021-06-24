<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_EXTENTS_H
#घोषणा _BCACHE_EXTENTS_H

बाह्य स्थिर काष्ठा btree_keys_ops bch_btree_keys_ops;
बाह्य स्थिर काष्ठा btree_keys_ops bch_extent_keys_ops;

काष्ठा bkey;
काष्ठा cache_set;

व्योम bch_extent_to_text(अक्षर *buf, माप_प्रकार size, स्थिर काष्ठा bkey *k);
bool __bch_btree_ptr_invalid(काष्ठा cache_set *c, स्थिर काष्ठा bkey *k);
bool __bch_extent_invalid(काष्ठा cache_set *c, स्थिर काष्ठा bkey *k);

#पूर्ण_अगर /* _BCACHE_EXTENTS_H */
