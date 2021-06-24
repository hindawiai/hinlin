<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_DEBUG_H
#घोषणा _BCACHE_DEBUG_H

काष्ठा bio;
काष्ठा cached_dev;
काष्ठा cache_set;

#अगर_घोषित CONFIG_BCACHE_DEBUG

व्योम bch_btree_verअगरy(काष्ठा btree *b);
व्योम bch_data_verअगरy(काष्ठा cached_dev *dc, काष्ठा bio *bio);

#घोषणा expensive_debug_checks(c)	((c)->expensive_debug_checks)
#घोषणा key_merging_disabled(c)		((c)->key_merging_disabled)
#घोषणा bypass_torture_test(d)		((d)->bypass_torture_test)

#अन्यथा /* DEBUG */

अटल अंतरभूत व्योम bch_btree_verअगरy(काष्ठा btree *b) अणुपूर्ण
अटल अंतरभूत व्योम bch_data_verअगरy(काष्ठा cached_dev *dc, काष्ठा bio *bio) अणुपूर्ण

#घोषणा expensive_debug_checks(c)	0
#घोषणा key_merging_disabled(c)		0
#घोषणा bypass_torture_test(d)		0

#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS
व्योम bch_debug_init_cache_set(काष्ठा cache_set *c);
#अन्यथा
अटल अंतरभूत व्योम bch_debug_init_cache_set(काष्ठा cache_set *c) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
