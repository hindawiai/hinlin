<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_FRAG_H__
#घोषणा __NET_FRAG_H__

#समावेश <linux/rhashtable-types.h>
#समावेश <linux/completion.h>

/* Per netns frag queues directory */
काष्ठा fqdir अणु
	/* sysctls */
	दीर्घ			high_thresh;
	दीर्घ			low_thresh;
	पूर्णांक			समयout;
	पूर्णांक			max_dist;
	काष्ठा inet_frags	*f;
	काष्ठा net		*net;
	bool			dead;

	काष्ठा rhashtable       rhashtable ____cacheline_aligned_in_smp;

	/* Keep atomic mem on separate cachelines in काष्ठाs that include it */
	atomic_दीर्घ_t		mem ____cacheline_aligned_in_smp;
	काष्ठा work_काष्ठा	destroy_work;
	काष्ठा llist_node	मुक्त_list;
पूर्ण;

/**
 * fragment queue flags
 *
 * @INET_FRAG_FIRST_IN: first fragment has arrived
 * @INET_FRAG_LAST_IN: final fragment has arrived
 * @INET_FRAG_COMPLETE: frag queue has been processed and is due क्रम deकाष्ठाion
 * @INET_FRAG_HASH_DEAD: inet_frag_समाप्त() has not हटाओd fq from rhashtable
 */
क्रमागत अणु
	INET_FRAG_FIRST_IN	= BIT(0),
	INET_FRAG_LAST_IN	= BIT(1),
	INET_FRAG_COMPLETE	= BIT(2),
	INET_FRAG_HASH_DEAD	= BIT(3),
पूर्ण;

काष्ठा frag_v4_compare_key अणु
	__be32		saddr;
	__be32		daddr;
	u32		user;
	u32		vअगर;
	__be16		id;
	u16		protocol;
पूर्ण;

काष्ठा frag_v6_compare_key अणु
	काष्ठा in6_addr	saddr;
	काष्ठा in6_addr	daddr;
	u32		user;
	__be32		id;
	u32		iअगर;
पूर्ण;

/**
 * काष्ठा inet_frag_queue - fragment queue
 *
 * @node: rhash node
 * @key: keys identअगरying this frag.
 * @समयr: queue expiration समयr
 * @lock: spinlock protecting this frag
 * @refcnt: reference count of the queue
 * @rb_fragments: received fragments rb-tree root
 * @fragments_tail: received fragments tail
 * @last_run_head: the head of the last "run". see ip_fragment.c
 * @stamp: बारtamp of the last received fragment
 * @len: total length of the original datagram
 * @meat: length of received fragments so far
 * @flags: fragment queue flags
 * @max_size: maximum received fragment size
 * @fqdir: poपूर्णांकer to काष्ठा fqdir
 * @rcu: rcu head क्रम मुक्तing deferall
 */
काष्ठा inet_frag_queue अणु
	काष्ठा rhash_head	node;
	जोड़ अणु
		काष्ठा frag_v4_compare_key v4;
		काष्ठा frag_v6_compare_key v6;
	पूर्ण key;
	काष्ठा समयr_list	समयr;
	spinlock_t		lock;
	refcount_t		refcnt;
	काष्ठा rb_root		rb_fragments;
	काष्ठा sk_buff		*fragments_tail;
	काष्ठा sk_buff		*last_run_head;
	kसमय_प्रकार			stamp;
	पूर्णांक			len;
	पूर्णांक			meat;
	__u8			flags;
	u16			max_size;
	काष्ठा fqdir		*fqdir;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा inet_frags अणु
	अचिन्हित पूर्णांक		qsize;

	व्योम			(*स्थिरructor)(काष्ठा inet_frag_queue *q,
					       स्थिर व्योम *arg);
	व्योम			(*deकाष्ठाor)(काष्ठा inet_frag_queue *);
	व्योम			(*frag_expire)(काष्ठा समयr_list *t);
	काष्ठा kmem_cache	*frags_cachep;
	स्थिर अक्षर		*frags_cache_name;
	काष्ठा rhashtable_params rhash_params;
	refcount_t		refcnt;
	काष्ठा completion	completion;
पूर्ण;

पूर्णांक inet_frags_init(काष्ठा inet_frags *);
व्योम inet_frags_fini(काष्ठा inet_frags *);

पूर्णांक fqdir_init(काष्ठा fqdir **fqdirp, काष्ठा inet_frags *f, काष्ठा net *net);

अटल अंतरभूत व्योम fqdir_pre_निकास(काष्ठा fqdir *fqdir)
अणु
	fqdir->high_thresh = 0; /* prevent creation of new frags */
	fqdir->dead = true;
पूर्ण
व्योम fqdir_निकास(काष्ठा fqdir *fqdir);

व्योम inet_frag_समाप्त(काष्ठा inet_frag_queue *q);
व्योम inet_frag_destroy(काष्ठा inet_frag_queue *q);
काष्ठा inet_frag_queue *inet_frag_find(काष्ठा fqdir *fqdir, व्योम *key);

/* Free all skbs in the queue; वापस the sum of their truesizes. */
अचिन्हित पूर्णांक inet_frag_rbtree_purge(काष्ठा rb_root *root);

अटल अंतरभूत व्योम inet_frag_put(काष्ठा inet_frag_queue *q)
अणु
	अगर (refcount_dec_and_test(&q->refcnt))
		inet_frag_destroy(q);
पूर्ण

/* Memory Tracking Functions. */

अटल अंतरभूत दीर्घ frag_mem_limit(स्थिर काष्ठा fqdir *fqdir)
अणु
	वापस atomic_दीर्घ_पढ़ो(&fqdir->mem);
पूर्ण

अटल अंतरभूत व्योम sub_frag_mem_limit(काष्ठा fqdir *fqdir, दीर्घ val)
अणु
	atomic_दीर्घ_sub(val, &fqdir->mem);
पूर्ण

अटल अंतरभूत व्योम add_frag_mem_limit(काष्ठा fqdir *fqdir, दीर्घ val)
अणु
	atomic_दीर्घ_add(val, &fqdir->mem);
पूर्ण

/* RFC 3168 support :
 * We want to check ECN values of all fragments, करो detect invalid combinations.
 * In ipq->ecn, we store the OR value of each ip4_frag_ecn() fragment value.
 */
#घोषणा	IPFRAG_ECN_NOT_ECT	0x01 /* one frag had ECN_NOT_ECT */
#घोषणा	IPFRAG_ECN_ECT_1	0x02 /* one frag had ECN_ECT_1 */
#घोषणा	IPFRAG_ECN_ECT_0	0x04 /* one frag had ECN_ECT_0 */
#घोषणा	IPFRAG_ECN_CE		0x08 /* one frag had ECN_CE */

बाह्य स्थिर u8 ip_frag_ecn_table[16];

/* Return values of inet_frag_queue_insert() */
#घोषणा IPFRAG_OK	0
#घोषणा IPFRAG_DUP	1
#घोषणा IPFRAG_OVERLAP	2
पूर्णांक inet_frag_queue_insert(काष्ठा inet_frag_queue *q, काष्ठा sk_buff *skb,
			   पूर्णांक offset, पूर्णांक end);
व्योम *inet_frag_reयंत्र_prepare(काष्ठा inet_frag_queue *q, काष्ठा sk_buff *skb,
			      काष्ठा sk_buff *parent);
व्योम inet_frag_reयंत्र_finish(काष्ठा inet_frag_queue *q, काष्ठा sk_buff *head,
			    व्योम *reयंत्र_data, bool try_coalesce);
काष्ठा sk_buff *inet_frag_pull_head(काष्ठा inet_frag_queue *q);

#पूर्ण_अगर
