<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2016 Facebook
 */
#अगर_अघोषित __BPF_LRU_LIST_H_
#घोषणा __BPF_LRU_LIST_H_

#समावेश <linux/list.h>
#समावेश <linux/spinlock_types.h>

#घोषणा NR_BPF_LRU_LIST_T	(3)
#घोषणा NR_BPF_LRU_LIST_COUNT	(2)
#घोषणा NR_BPF_LRU_LOCAL_LIST_T (2)
#घोषणा BPF_LOCAL_LIST_T_OFFSET NR_BPF_LRU_LIST_T

क्रमागत bpf_lru_list_type अणु
	BPF_LRU_LIST_T_ACTIVE,
	BPF_LRU_LIST_T_INACTIVE,
	BPF_LRU_LIST_T_FREE,
	BPF_LRU_LOCAL_LIST_T_FREE,
	BPF_LRU_LOCAL_LIST_T_PENDING,
पूर्ण;

काष्ठा bpf_lru_node अणु
	काष्ठा list_head list;
	u16 cpu;
	u8 type;
	u8 ref;
पूर्ण;

काष्ठा bpf_lru_list अणु
	काष्ठा list_head lists[NR_BPF_LRU_LIST_T];
	अचिन्हित पूर्णांक counts[NR_BPF_LRU_LIST_COUNT];
	/* The next inactive list rotation starts from here */
	काष्ठा list_head *next_inactive_rotation;

	raw_spinlock_t lock ____cacheline_aligned_in_smp;
पूर्ण;

काष्ठा bpf_lru_locallist अणु
	काष्ठा list_head lists[NR_BPF_LRU_LOCAL_LIST_T];
	u16 next_steal;
	raw_spinlock_t lock;
पूर्ण;

काष्ठा bpf_common_lru अणु
	काष्ठा bpf_lru_list lru_list;
	काष्ठा bpf_lru_locallist __percpu *local_list;
पूर्ण;

प्रकार bool (*del_from_htab_func)(व्योम *arg, काष्ठा bpf_lru_node *node);

काष्ठा bpf_lru अणु
	जोड़ अणु
		काष्ठा bpf_common_lru common_lru;
		काष्ठा bpf_lru_list __percpu *percpu_lru;
	पूर्ण;
	del_from_htab_func del_from_htab;
	व्योम *del_arg;
	अचिन्हित पूर्णांक hash_offset;
	अचिन्हित पूर्णांक nr_scans;
	bool percpu;
पूर्ण;

अटल अंतरभूत व्योम bpf_lru_node_set_ref(काष्ठा bpf_lru_node *node)
अणु
	/* ref is an approximation on access frequency.  It करोes not
	 * have to be very accurate.  Hence, no protection is used.
	 */
	अगर (!node->ref)
		node->ref = 1;
पूर्ण

पूर्णांक bpf_lru_init(काष्ठा bpf_lru *lru, bool percpu, u32 hash_offset,
		 del_from_htab_func del_from_htab, व्योम *delete_arg);
व्योम bpf_lru_populate(काष्ठा bpf_lru *lru, व्योम *buf, u32 node_offset,
		      u32 elem_size, u32 nr_elems);
व्योम bpf_lru_destroy(काष्ठा bpf_lru *lru);
काष्ठा bpf_lru_node *bpf_lru_pop_मुक्त(काष्ठा bpf_lru *lru, u32 hash);
व्योम bpf_lru_push_मुक्त(काष्ठा bpf_lru *lru, काष्ठा bpf_lru_node *node);
व्योम bpf_lru_promote(काष्ठा bpf_lru *lru, काष्ठा bpf_lru_node *node);

#पूर्ण_अगर
