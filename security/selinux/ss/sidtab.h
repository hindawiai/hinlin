<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * A security identअगरier table (sidtab) is a lookup table
 * of security context काष्ठाures indexed by SID value.
 *
 * Original author: Stephen Smalley, <sds@tycho.nsa.gov>
 * Author: Ondrej Mosnacek, <omosnacek@gmail.com>
 *
 * Copyright (C) 2018 Red Hat, Inc.
 */
#अगर_अघोषित _SS_SIDTAB_H_
#घोषणा _SS_SIDTAB_H_

#समावेश <linux/spinlock_types.h>
#समावेश <linux/log2.h>
#समावेश <linux/hashtable.h>

#समावेश "context.h"

काष्ठा sidtab_entry अणु
	u32 sid;
	u32 hash;
	काष्ठा context context;
#अगर CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE > 0
	काष्ठा sidtab_str_cache __rcu *cache;
#पूर्ण_अगर
	काष्ठा hlist_node list;
पूर्ण;

जोड़ sidtab_entry_inner अणु
	काष्ठा sidtab_node_inner *ptr_inner;
	काष्ठा sidtab_node_leaf  *ptr_leaf;
पूर्ण;

/* align node size to page boundary */
#घोषणा SIDTAB_NODE_ALLOC_SHIFT PAGE_SHIFT
#घोषणा SIDTAB_NODE_ALLOC_SIZE  PAGE_SIZE

#घोषणा माप_प्रकारo_shअगरt(size) ((size) == 1 ? 1 : (स्थिर_ilog2((size) - 1) + 1))

#घोषणा SIDTAB_INNER_SHIFT \
	(SIDTAB_NODE_ALLOC_SHIFT - माप_प्रकारo_shअगरt(माप(जोड़ sidtab_entry_inner)))
#घोषणा SIDTAB_INNER_ENTRIES ((माप_प्रकार)1 << SIDTAB_INNER_SHIFT)
#घोषणा SIDTAB_LEAF_ENTRIES \
	(SIDTAB_NODE_ALLOC_SIZE / माप(काष्ठा sidtab_entry))

#घोषणा SIDTAB_MAX_BITS 32
#घोषणा SIDTAB_MAX U32_MAX
/* ensure enough tree levels क्रम SIDTAB_MAX entries */
#घोषणा SIDTAB_MAX_LEVEL \
	DIV_ROUND_UP(SIDTAB_MAX_BITS - माप_प्रकारo_shअगरt(SIDTAB_LEAF_ENTRIES), \
		     SIDTAB_INNER_SHIFT)

काष्ठा sidtab_node_leaf अणु
	काष्ठा sidtab_entry entries[SIDTAB_LEAF_ENTRIES];
पूर्ण;

काष्ठा sidtab_node_inner अणु
	जोड़ sidtab_entry_inner entries[SIDTAB_INNER_ENTRIES];
पूर्ण;

काष्ठा sidtab_isid_entry अणु
	पूर्णांक set;
	काष्ठा sidtab_entry entry;
पूर्ण;

काष्ठा sidtab_convert_params अणु
	पूर्णांक (*func)(काष्ठा context *oldc, काष्ठा context *newc, व्योम *args);
	व्योम *args;
	काष्ठा sidtab *target;
पूर्ण;

#घोषणा SIDTAB_HASH_BITS CONFIG_SECURITY_SELINUX_SIDTAB_HASH_BITS
#घोषणा SIDTAB_HASH_BUCKETS (1 << SIDTAB_HASH_BITS)

काष्ठा sidtab अणु
	/*
	 * lock-मुक्त पढ़ो access only क्रम as many items as a prior पढ़ो of
	 * 'count'
	 */
	जोड़ sidtab_entry_inner roots[SIDTAB_MAX_LEVEL + 1];
	/*
	 * access atomically via अणुREAD|WRITEपूर्ण_ONCE(); only increment under
	 * spinlock
	 */
	u32 count;
	/* access only under spinlock */
	काष्ठा sidtab_convert_params *convert;
	bool frozen;
	spinlock_t lock;

#अगर CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE > 0
	/* SID -> context string cache */
	u32 cache_मुक्त_slots;
	काष्ठा list_head cache_lru_list;
	spinlock_t cache_lock;
#पूर्ण_अगर

	/* index == SID - 1 (no entry क्रम SECSID_शून्य) */
	काष्ठा sidtab_isid_entry isids[SECINITSID_NUM];

	/* Hash table क्रम fast reverse context-to-sid lookups. */
	DECLARE_HASHTABLE(context_to_sid, SIDTAB_HASH_BITS);
पूर्ण;

पूर्णांक sidtab_init(काष्ठा sidtab *s);
पूर्णांक sidtab_set_initial(काष्ठा sidtab *s, u32 sid, काष्ठा context *context);
काष्ठा sidtab_entry *sidtab_search_entry(काष्ठा sidtab *s, u32 sid);
काष्ठा sidtab_entry *sidtab_search_entry_क्रमce(काष्ठा sidtab *s, u32 sid);

अटल अंतरभूत काष्ठा context *sidtab_search(काष्ठा sidtab *s, u32 sid)
अणु
	काष्ठा sidtab_entry *entry = sidtab_search_entry(s, sid);

	वापस entry ? &entry->context : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा context *sidtab_search_क्रमce(काष्ठा sidtab *s, u32 sid)
अणु
	काष्ठा sidtab_entry *entry = sidtab_search_entry_क्रमce(s, sid);

	वापस entry ? &entry->context : शून्य;
पूर्ण

पूर्णांक sidtab_convert(काष्ठा sidtab *s, काष्ठा sidtab_convert_params *params);

व्योम sidtab_cancel_convert(काष्ठा sidtab *s);

व्योम sidtab_मुक्तze_begin(काष्ठा sidtab *s, अचिन्हित दीर्घ *flags) __acquires(&s->lock);
व्योम sidtab_मुक्तze_end(काष्ठा sidtab *s, अचिन्हित दीर्घ *flags) __releases(&s->lock);

पूर्णांक sidtab_context_to_sid(काष्ठा sidtab *s, काष्ठा context *context, u32 *sid);

व्योम sidtab_destroy(काष्ठा sidtab *s);

पूर्णांक sidtab_hash_stats(काष्ठा sidtab *sidtab, अक्षर *page);

#अगर CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE > 0
व्योम sidtab_sid2str_put(काष्ठा sidtab *s, काष्ठा sidtab_entry *entry,
			स्थिर अक्षर *str, u32 str_len);
पूर्णांक sidtab_sid2str_get(काष्ठा sidtab *s, काष्ठा sidtab_entry *entry,
		       अक्षर **out, u32 *out_len);
#अन्यथा
अटल अंतरभूत व्योम sidtab_sid2str_put(काष्ठा sidtab *s,
				      काष्ठा sidtab_entry *entry,
				      स्थिर अक्षर *str, u32 str_len)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक sidtab_sid2str_get(काष्ठा sidtab *s,
				     काष्ठा sidtab_entry *entry,
				     अक्षर **out, u32 *out_len)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर /* CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE > 0 */

#पूर्ण_अगर	/* _SS_SIDTAB_H_ */


