<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2017 - 2018 Covalent IO, Inc. http://covalent.io */

#अगर_अघोषित _LINUX_SKMSG_H
#घोषणा _LINUX_SKMSG_H

#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/skbuff.h>

#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <net/strparser.h>

#घोषणा MAX_MSG_FRAGS			MAX_SKB_FRAGS
#घोषणा NR_MSG_FRAG_IDS			(MAX_MSG_FRAGS + 1)

क्रमागत __sk_action अणु
	__SK_DROP = 0,
	__SK_PASS,
	__SK_REसूचीECT,
	__SK_NONE,
पूर्ण;

काष्ठा sk_msg_sg अणु
	u32				start;
	u32				curr;
	u32				end;
	u32				size;
	u32				copyअवरोध;
	अचिन्हित दीर्घ			copy;
	/* The extra two elements:
	 * 1) used क्रम chaining the front and sections when the list becomes
	 *    partitioned (e.g. end < start). The crypto APIs require the
	 *    chaining;
	 * 2) to chain tailer SG entries after the message.
	 */
	काष्ठा scatterlist		data[MAX_MSG_FRAGS + 2];
पूर्ण;
अटल_निश्चित(BITS_PER_LONG >= NR_MSG_FRAG_IDS);

/* UAPI in filter.c depends on काष्ठा sk_msg_sg being first element. */
काष्ठा sk_msg अणु
	काष्ठा sk_msg_sg		sg;
	व्योम				*data;
	व्योम				*data_end;
	u32				apply_bytes;
	u32				cork_bytes;
	u32				flags;
	काष्ठा sk_buff			*skb;
	काष्ठा sock			*sk_redir;
	काष्ठा sock			*sk;
	काष्ठा list_head		list;
पूर्ण;

काष्ठा sk_psock_progs अणु
	काष्ठा bpf_prog			*msg_parser;
	काष्ठा bpf_prog			*stream_parser;
	काष्ठा bpf_prog			*stream_verdict;
	काष्ठा bpf_prog			*skb_verdict;
पूर्ण;

क्रमागत sk_psock_state_bits अणु
	SK_PSOCK_TX_ENABLED,
पूर्ण;

काष्ठा sk_psock_link अणु
	काष्ठा list_head		list;
	काष्ठा bpf_map			*map;
	व्योम				*link_raw;
पूर्ण;

काष्ठा sk_psock_work_state अणु
	काष्ठा sk_buff			*skb;
	u32				len;
	u32				off;
पूर्ण;

काष्ठा sk_psock अणु
	काष्ठा sock			*sk;
	काष्ठा sock			*sk_redir;
	u32				apply_bytes;
	u32				cork_bytes;
	u32				eval;
	काष्ठा sk_msg			*cork;
	काष्ठा sk_psock_progs		progs;
#अगर IS_ENABLED(CONFIG_BPF_STREAM_PARSER)
	काष्ठा strparser		strp;
#पूर्ण_अगर
	काष्ठा sk_buff_head		ingress_skb;
	काष्ठा list_head		ingress_msg;
	spinlock_t			ingress_lock;
	अचिन्हित दीर्घ			state;
	काष्ठा list_head		link;
	spinlock_t			link_lock;
	refcount_t			refcnt;
	व्योम (*saved_unhash)(काष्ठा sock *sk);
	व्योम (*saved_बंद)(काष्ठा sock *sk, दीर्घ समयout);
	व्योम (*saved_ग_लिखो_space)(काष्ठा sock *sk);
	व्योम (*saved_data_पढ़ोy)(काष्ठा sock *sk);
	पूर्णांक  (*psock_update_sk_prot)(काष्ठा sock *sk, काष्ठा sk_psock *psock,
				     bool restore);
	काष्ठा proto			*sk_proto;
	काष्ठा mutex			work_mutex;
	काष्ठा sk_psock_work_state	work_state;
	काष्ठा work_काष्ठा		work;
	काष्ठा rcu_work			rwork;
पूर्ण;

पूर्णांक sk_msg_alloc(काष्ठा sock *sk, काष्ठा sk_msg *msg, पूर्णांक len,
		 पूर्णांक elem_first_coalesce);
पूर्णांक sk_msg_clone(काष्ठा sock *sk, काष्ठा sk_msg *dst, काष्ठा sk_msg *src,
		 u32 off, u32 len);
व्योम sk_msg_trim(काष्ठा sock *sk, काष्ठा sk_msg *msg, पूर्णांक len);
पूर्णांक sk_msg_मुक्त(काष्ठा sock *sk, काष्ठा sk_msg *msg);
पूर्णांक sk_msg_मुक्त_noअक्षरge(काष्ठा sock *sk, काष्ठा sk_msg *msg);
व्योम sk_msg_मुक्त_partial(काष्ठा sock *sk, काष्ठा sk_msg *msg, u32 bytes);
व्योम sk_msg_मुक्त_partial_noअक्षरge(काष्ठा sock *sk, काष्ठा sk_msg *msg,
				  u32 bytes);

व्योम sk_msg_वापस(काष्ठा sock *sk, काष्ठा sk_msg *msg, पूर्णांक bytes);
व्योम sk_msg_वापस_zero(काष्ठा sock *sk, काष्ठा sk_msg *msg, पूर्णांक bytes);

पूर्णांक sk_msg_zerocopy_from_iter(काष्ठा sock *sk, काष्ठा iov_iter *from,
			      काष्ठा sk_msg *msg, u32 bytes);
पूर्णांक sk_msg_memcopy_from_iter(काष्ठा sock *sk, काष्ठा iov_iter *from,
			     काष्ठा sk_msg *msg, u32 bytes);
पूर्णांक sk_msg_रुको_data(काष्ठा sock *sk, काष्ठा sk_psock *psock, पूर्णांक flags,
		     दीर्घ समयo, पूर्णांक *err);
पूर्णांक sk_msg_recvmsg(काष्ठा sock *sk, काष्ठा sk_psock *psock, काष्ठा msghdr *msg,
		   पूर्णांक len, पूर्णांक flags);

अटल अंतरभूत व्योम sk_msg_check_to_मुक्त(काष्ठा sk_msg *msg, u32 i, u32 bytes)
अणु
	WARN_ON(i == msg->sg.end && bytes);
पूर्ण

अटल अंतरभूत व्योम sk_msg_apply_bytes(काष्ठा sk_psock *psock, u32 bytes)
अणु
	अगर (psock->apply_bytes) अणु
		अगर (psock->apply_bytes < bytes)
			psock->apply_bytes = 0;
		अन्यथा
			psock->apply_bytes -= bytes;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 sk_msg_iter_dist(u32 start, u32 end)
अणु
	वापस end >= start ? end - start : end + (NR_MSG_FRAG_IDS - start);
पूर्ण

#घोषणा sk_msg_iter_var_prev(var)			\
	करो अणु						\
		अगर (var == 0)				\
			var = NR_MSG_FRAG_IDS - 1;	\
		अन्यथा					\
			var--;				\
	पूर्ण जबतक (0)

#घोषणा sk_msg_iter_var_next(var)			\
	करो अणु						\
		var++;					\
		अगर (var == NR_MSG_FRAG_IDS)		\
			var = 0;			\
	पूर्ण जबतक (0)

#घोषणा sk_msg_iter_prev(msg, which)			\
	sk_msg_iter_var_prev(msg->sg.which)

#घोषणा sk_msg_iter_next(msg, which)			\
	sk_msg_iter_var_next(msg->sg.which)

अटल अंतरभूत व्योम sk_msg_clear_meta(काष्ठा sk_msg *msg)
अणु
	स_रखो(&msg->sg, 0, दुरत्वend(काष्ठा sk_msg_sg, copy));
पूर्ण

अटल अंतरभूत व्योम sk_msg_init(काष्ठा sk_msg *msg)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(msg->sg.data) - 1 != NR_MSG_FRAG_IDS);
	स_रखो(msg, 0, माप(*msg));
	sg_init_marker(msg->sg.data, NR_MSG_FRAG_IDS);
पूर्ण

अटल अंतरभूत व्योम sk_msg_xfer(काष्ठा sk_msg *dst, काष्ठा sk_msg *src,
			       पूर्णांक which, u32 size)
अणु
	dst->sg.data[which] = src->sg.data[which];
	dst->sg.data[which].length  = size;
	dst->sg.size		   += size;
	src->sg.size		   -= size;
	src->sg.data[which].length -= size;
	src->sg.data[which].offset += size;
पूर्ण

अटल अंतरभूत व्योम sk_msg_xfer_full(काष्ठा sk_msg *dst, काष्ठा sk_msg *src)
अणु
	स_नकल(dst, src, माप(*src));
	sk_msg_init(src);
पूर्ण

अटल अंतरभूत bool sk_msg_full(स्थिर काष्ठा sk_msg *msg)
अणु
	वापस sk_msg_iter_dist(msg->sg.start, msg->sg.end) == MAX_MSG_FRAGS;
पूर्ण

अटल अंतरभूत u32 sk_msg_elem_used(स्थिर काष्ठा sk_msg *msg)
अणु
	वापस sk_msg_iter_dist(msg->sg.start, msg->sg.end);
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *sk_msg_elem(काष्ठा sk_msg *msg, पूर्णांक which)
अणु
	वापस &msg->sg.data[which];
पूर्ण

अटल अंतरभूत काष्ठा scatterlist sk_msg_elem_cpy(काष्ठा sk_msg *msg, पूर्णांक which)
अणु
	वापस msg->sg.data[which];
पूर्ण

अटल अंतरभूत काष्ठा page *sk_msg_page(काष्ठा sk_msg *msg, पूर्णांक which)
अणु
	वापस sg_page(sk_msg_elem(msg, which));
पूर्ण

अटल अंतरभूत bool sk_msg_to_ingress(स्थिर काष्ठा sk_msg *msg)
अणु
	वापस msg->flags & BPF_F_INGRESS;
पूर्ण

अटल अंतरभूत व्योम sk_msg_compute_data_poपूर्णांकers(काष्ठा sk_msg *msg)
अणु
	काष्ठा scatterlist *sge = sk_msg_elem(msg, msg->sg.start);

	अगर (test_bit(msg->sg.start, &msg->sg.copy)) अणु
		msg->data = शून्य;
		msg->data_end = शून्य;
	पूर्ण अन्यथा अणु
		msg->data = sg_virt(sge);
		msg->data_end = msg->data + sge->length;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sk_msg_page_add(काष्ठा sk_msg *msg, काष्ठा page *page,
				   u32 len, u32 offset)
अणु
	काष्ठा scatterlist *sge;

	get_page(page);
	sge = sk_msg_elem(msg, msg->sg.end);
	sg_set_page(sge, page, len, offset);
	sg_unmark_end(sge);

	__set_bit(msg->sg.end, &msg->sg.copy);
	msg->sg.size += len;
	sk_msg_iter_next(msg, end);
पूर्ण

अटल अंतरभूत व्योम sk_msg_sg_copy(काष्ठा sk_msg *msg, u32 i, bool copy_state)
अणु
	करो अणु
		अगर (copy_state)
			__set_bit(i, &msg->sg.copy);
		अन्यथा
			__clear_bit(i, &msg->sg.copy);
		sk_msg_iter_var_next(i);
		अगर (i == msg->sg.end)
			अवरोध;
	पूर्ण जबतक (1);
पूर्ण

अटल अंतरभूत व्योम sk_msg_sg_copy_set(काष्ठा sk_msg *msg, u32 start)
अणु
	sk_msg_sg_copy(msg, start, true);
पूर्ण

अटल अंतरभूत व्योम sk_msg_sg_copy_clear(काष्ठा sk_msg *msg, u32 start)
अणु
	sk_msg_sg_copy(msg, start, false);
पूर्ण

अटल अंतरभूत काष्ठा sk_psock *sk_psock(स्थिर काष्ठा sock *sk)
अणु
	वापस rcu_dereference_sk_user_data(sk);
पूर्ण

अटल अंतरभूत व्योम sk_psock_queue_msg(काष्ठा sk_psock *psock,
				      काष्ठा sk_msg *msg)
अणु
	spin_lock_bh(&psock->ingress_lock);
	list_add_tail(&msg->list, &psock->ingress_msg);
	spin_unlock_bh(&psock->ingress_lock);
पूर्ण

अटल अंतरभूत काष्ठा sk_msg *sk_psock_dequeue_msg(काष्ठा sk_psock *psock)
अणु
	काष्ठा sk_msg *msg;

	spin_lock_bh(&psock->ingress_lock);
	msg = list_first_entry_or_null(&psock->ingress_msg, काष्ठा sk_msg, list);
	अगर (msg)
		list_del(&msg->list);
	spin_unlock_bh(&psock->ingress_lock);
	वापस msg;
पूर्ण

अटल अंतरभूत काष्ठा sk_msg *sk_psock_peek_msg(काष्ठा sk_psock *psock)
अणु
	काष्ठा sk_msg *msg;

	spin_lock_bh(&psock->ingress_lock);
	msg = list_first_entry_or_null(&psock->ingress_msg, काष्ठा sk_msg, list);
	spin_unlock_bh(&psock->ingress_lock);
	वापस msg;
पूर्ण

अटल अंतरभूत काष्ठा sk_msg *sk_psock_next_msg(काष्ठा sk_psock *psock,
					       काष्ठा sk_msg *msg)
अणु
	काष्ठा sk_msg *ret;

	spin_lock_bh(&psock->ingress_lock);
	अगर (list_is_last(&msg->list, &psock->ingress_msg))
		ret = शून्य;
	अन्यथा
		ret = list_next_entry(msg, list);
	spin_unlock_bh(&psock->ingress_lock);
	वापस ret;
पूर्ण

अटल अंतरभूत bool sk_psock_queue_empty(स्थिर काष्ठा sk_psock *psock)
अणु
	वापस psock ? list_empty(&psock->ingress_msg) : true;
पूर्ण

अटल अंतरभूत व्योम kमुक्त_sk_msg(काष्ठा sk_msg *msg)
अणु
	अगर (msg->skb)
		consume_skb(msg->skb);
	kमुक्त(msg);
पूर्ण

अटल अंतरभूत व्योम sk_psock_report_error(काष्ठा sk_psock *psock, पूर्णांक err)
अणु
	काष्ठा sock *sk = psock->sk;

	sk->sk_err = err;
	sk->sk_error_report(sk);
पूर्ण

काष्ठा sk_psock *sk_psock_init(काष्ठा sock *sk, पूर्णांक node);
व्योम sk_psock_stop(काष्ठा sk_psock *psock, bool रुको);

#अगर IS_ENABLED(CONFIG_BPF_STREAM_PARSER)
पूर्णांक sk_psock_init_strp(काष्ठा sock *sk, काष्ठा sk_psock *psock);
व्योम sk_psock_start_strp(काष्ठा sock *sk, काष्ठा sk_psock *psock);
व्योम sk_psock_stop_strp(काष्ठा sock *sk, काष्ठा sk_psock *psock);
#अन्यथा
अटल अंतरभूत पूर्णांक sk_psock_init_strp(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम sk_psock_start_strp(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
पूर्ण

अटल अंतरभूत व्योम sk_psock_stop_strp(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
पूर्ण
#पूर्ण_अगर

व्योम sk_psock_start_verdict(काष्ठा sock *sk, काष्ठा sk_psock *psock);
व्योम sk_psock_stop_verdict(काष्ठा sock *sk, काष्ठा sk_psock *psock);

पूर्णांक sk_psock_msg_verdict(काष्ठा sock *sk, काष्ठा sk_psock *psock,
			 काष्ठा sk_msg *msg);

अटल अंतरभूत काष्ठा sk_psock_link *sk_psock_init_link(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा sk_psock_link),
		       GFP_ATOMIC | __GFP_NOWARN);
पूर्ण

अटल अंतरभूत व्योम sk_psock_मुक्त_link(काष्ठा sk_psock_link *link)
अणु
	kमुक्त(link);
पूर्ण

काष्ठा sk_psock_link *sk_psock_link_pop(काष्ठा sk_psock *psock);

अटल अंतरभूत व्योम sk_psock_cork_मुक्त(काष्ठा sk_psock *psock)
अणु
	अगर (psock->cork) अणु
		sk_msg_मुक्त(psock->sk, psock->cork);
		kमुक्त(psock->cork);
		psock->cork = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sk_psock_restore_proto(काष्ठा sock *sk,
					  काष्ठा sk_psock *psock)
अणु
	अगर (psock->psock_update_sk_prot)
		psock->psock_update_sk_prot(sk, psock, true);
पूर्ण

अटल अंतरभूत व्योम sk_psock_set_state(काष्ठा sk_psock *psock,
				      क्रमागत sk_psock_state_bits bit)
अणु
	set_bit(bit, &psock->state);
पूर्ण

अटल अंतरभूत व्योम sk_psock_clear_state(काष्ठा sk_psock *psock,
					क्रमागत sk_psock_state_bits bit)
अणु
	clear_bit(bit, &psock->state);
पूर्ण

अटल अंतरभूत bool sk_psock_test_state(स्थिर काष्ठा sk_psock *psock,
				       क्रमागत sk_psock_state_bits bit)
अणु
	वापस test_bit(bit, &psock->state);
पूर्ण

अटल अंतरभूत काष्ठा sk_psock *sk_psock_get(काष्ठा sock *sk)
अणु
	काष्ठा sk_psock *psock;

	rcu_पढ़ो_lock();
	psock = sk_psock(sk);
	अगर (psock && !refcount_inc_not_zero(&psock->refcnt))
		psock = शून्य;
	rcu_पढ़ो_unlock();
	वापस psock;
पूर्ण

व्योम sk_psock_drop(काष्ठा sock *sk, काष्ठा sk_psock *psock);

अटल अंतरभूत व्योम sk_psock_put(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	अगर (refcount_dec_and_test(&psock->refcnt))
		sk_psock_drop(sk, psock);
पूर्ण

अटल अंतरभूत व्योम sk_psock_data_पढ़ोy(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	अगर (psock->saved_data_पढ़ोy)
		psock->saved_data_पढ़ोy(sk);
	अन्यथा
		sk->sk_data_पढ़ोy(sk);
पूर्ण

अटल अंतरभूत व्योम psock_set_prog(काष्ठा bpf_prog **pprog,
				  काष्ठा bpf_prog *prog)
अणु
	prog = xchg(pprog, prog);
	अगर (prog)
		bpf_prog_put(prog);
पूर्ण

अटल अंतरभूत पूर्णांक psock_replace_prog(काष्ठा bpf_prog **pprog,
				     काष्ठा bpf_prog *prog,
				     काष्ठा bpf_prog *old)
अणु
	अगर (cmpxchg(pprog, old, prog) != old)
		वापस -ENOENT;

	अगर (old)
		bpf_prog_put(old);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम psock_progs_drop(काष्ठा sk_psock_progs *progs)
अणु
	psock_set_prog(&progs->msg_parser, शून्य);
	psock_set_prog(&progs->stream_parser, शून्य);
	psock_set_prog(&progs->stream_verdict, शून्य);
	psock_set_prog(&progs->skb_verdict, शून्य);
पूर्ण

पूर्णांक sk_psock_tls_strp_पढ़ो(काष्ठा sk_psock *psock, काष्ठा sk_buff *skb);

अटल अंतरभूत bool sk_psock_strp_enabled(काष्ठा sk_psock *psock)
अणु
	अगर (!psock)
		वापस false;
	वापस !!psock->saved_data_पढ़ोy;
पूर्ण

#अगर IS_ENABLED(CONFIG_NET_SOCK_MSG)

/* We only have one bit so far. */
#घोषणा BPF_F_PTR_MASK ~(BPF_F_INGRESS)

अटल अंतरभूत bool skb_bpf_ingress(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ sk_redir = skb->_sk_redir;

	वापस sk_redir & BPF_F_INGRESS;
पूर्ण

अटल अंतरभूत व्योम skb_bpf_set_ingress(काष्ठा sk_buff *skb)
अणु
	skb->_sk_redir |= BPF_F_INGRESS;
पूर्ण

अटल अंतरभूत व्योम skb_bpf_set_redir(काष्ठा sk_buff *skb, काष्ठा sock *sk_redir,
				     bool ingress)
अणु
	skb->_sk_redir = (अचिन्हित दीर्घ)sk_redir;
	अगर (ingress)
		skb->_sk_redir |= BPF_F_INGRESS;
पूर्ण

अटल अंतरभूत काष्ठा sock *skb_bpf_redirect_fetch(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ sk_redir = skb->_sk_redir;

	वापस (काष्ठा sock *)(sk_redir & BPF_F_PTR_MASK);
पूर्ण

अटल अंतरभूत व्योम skb_bpf_redirect_clear(काष्ठा sk_buff *skb)
अणु
	skb->_sk_redir = 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_SOCK_MSG */
#पूर्ण_अगर /* _LINUX_SKMSG_H */
