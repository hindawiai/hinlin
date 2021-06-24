<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PACKET_INTERNAL_H__
#घोषणा __PACKET_INTERNAL_H__

#समावेश <linux/refcount.h>

काष्ठा packet_mclist अणु
	काष्ठा packet_mclist	*next;
	पूर्णांक			अगरindex;
	पूर्णांक			count;
	अचिन्हित लघु		type;
	अचिन्हित लघु		alen;
	अचिन्हित अक्षर		addr[MAX_ADDR_LEN];
पूर्ण;

/* kbdq - kernel block descriptor queue */
काष्ठा tpacket_kbdq_core अणु
	काष्ठा pgv	*pkbdq;
	अचिन्हित पूर्णांक	feature_req_word;
	अचिन्हित पूर्णांक	hdrlen;
	अचिन्हित अक्षर	reset_pending_on_curr_blk;
	अचिन्हित अक्षर   delete_blk_समयr;
	अचिन्हित लघु	kactive_blk_num;
	अचिन्हित लघु	blk_माप_priv;

	/* last_kactive_blk_num:
	 * trick to see अगर user-space has caught up
	 * in order to aव्योम refreshing समयr when every single pkt arrives.
	 */
	अचिन्हित लघु	last_kactive_blk_num;

	अक्षर		*pkblk_start;
	अक्षर		*pkblk_end;
	पूर्णांक		kblk_size;
	अचिन्हित पूर्णांक	max_frame_len;
	अचिन्हित पूर्णांक	knum_blocks;
	uपूर्णांक64_t	knxt_seq_num;
	अक्षर		*prev;
	अक्षर		*nxt_offset;
	काष्ठा sk_buff	*skb;

	rwlock_t	blk_fill_in_prog_lock;

	/* Default is set to 8ms */
#घोषणा DEFAULT_PRB_RETIRE_TOV	(8)

	अचिन्हित लघु  retire_blk_tov;
	अचिन्हित लघु  version;
	अचिन्हित दीर्घ	tov_in_jअगरfies;

	/* समयr to retire an outstanding block */
	काष्ठा समयr_list retire_blk_समयr;
पूर्ण;

काष्ठा pgv अणु
	अक्षर *buffer;
पूर्ण;

काष्ठा packet_ring_buffer अणु
	काष्ठा pgv		*pg_vec;

	अचिन्हित पूर्णांक		head;
	अचिन्हित पूर्णांक		frames_per_block;
	अचिन्हित पूर्णांक		frame_size;
	अचिन्हित पूर्णांक		frame_max;

	अचिन्हित पूर्णांक		pg_vec_order;
	अचिन्हित पूर्णांक		pg_vec_pages;
	अचिन्हित पूर्णांक		pg_vec_len;

	अचिन्हित पूर्णांक __percpu	*pending_refcnt;

	जोड़ अणु
		अचिन्हित दीर्घ			*rx_owner_map;
		काष्ठा tpacket_kbdq_core	prb_bdqc;
	पूर्ण;
पूर्ण;

बाह्य काष्ठा mutex fanout_mutex;
#घोषणा PACKET_FANOUT_MAX	(1 << 16)

काष्ठा packet_fanout अणु
	possible_net_t		net;
	अचिन्हित पूर्णांक		num_members;
	u32			max_num_members;
	u16			id;
	u8			type;
	u8			flags;
	जोड़ अणु
		atomic_t		rr_cur;
		काष्ठा bpf_prog __rcu	*bpf_prog;
	पूर्ण;
	काष्ठा list_head	list;
	spinlock_t		lock;
	refcount_t		sk_ref;
	काष्ठा packet_type	prot_hook ____cacheline_aligned_in_smp;
	काष्ठा sock	__rcu	*arr[];
पूर्ण;

काष्ठा packet_rollover अणु
	पूर्णांक			sock;
	atomic_दीर्घ_t		num;
	atomic_दीर्घ_t		num_huge;
	atomic_दीर्घ_t		num_failed;
#घोषणा ROLLOVER_HLEN	(L1_CACHE_BYTES / माप(u32))
	u32			history[ROLLOVER_HLEN] ____cacheline_aligned;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा packet_sock अणु
	/* काष्ठा sock has to be the first member of packet_sock */
	काष्ठा sock		sk;
	काष्ठा packet_fanout	*fanout;
	जोड़  tpacket_stats_u	stats;
	काष्ठा packet_ring_buffer	rx_ring;
	काष्ठा packet_ring_buffer	tx_ring;
	पूर्णांक			copy_thresh;
	spinlock_t		bind_lock;
	काष्ठा mutex		pg_vec_lock;
	अचिन्हित पूर्णांक		running;	/* bind_lock must be held */
	अचिन्हित पूर्णांक		auxdata:1,	/* ग_लिखोr must hold sock lock */
				origdev:1,
				has_vnet_hdr:1,
				tp_loss:1,
				tp_tx_has_off:1;
	पूर्णांक			pressure;
	पूर्णांक			अगरindex;	/* bound device		*/
	__be16			num;
	काष्ठा packet_rollover	*rollover;
	काष्ठा packet_mclist	*mclist;
	atomic_t		mapped;
	क्रमागत tpacket_versions	tp_version;
	अचिन्हित पूर्णांक		tp_hdrlen;
	अचिन्हित पूर्णांक		tp_reserve;
	अचिन्हित पूर्णांक		tp_tstamp;
	काष्ठा completion	skb_completion;
	काष्ठा net_device __rcu	*cached_dev;
	पूर्णांक			(*xmit)(काष्ठा sk_buff *skb);
	काष्ठा packet_type	prot_hook ____cacheline_aligned_in_smp;
	atomic_t		tp_drops ____cacheline_aligned_in_smp;
पूर्ण;

अटल अंतरभूत काष्ठा packet_sock *pkt_sk(काष्ठा sock *sk)
अणु
	वापस (काष्ठा packet_sock *)sk;
पूर्ण

#पूर्ण_अगर
