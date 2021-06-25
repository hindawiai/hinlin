<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001-2003 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * The base lksctp header.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Xingang Guo           <xingang.guo@पूर्णांकel.com>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Daisy Chang           <daisyc@us.ibm.com>
 *    Sridhar Samudrala     <sri@us.ibm.com>
 *    Ardelle Fan           <ardelle.fan@पूर्णांकel.com>
 *    Ryan Layer            <rmlayer@us.ibm.com>
 *    Kevin Gao             <kevin.gao@पूर्णांकel.com> 
 */

#अगर_अघोषित __net_sctp_h__
#घोषणा __net_sctp_h__

/* Header Strategy.
 *    Start getting some control over the header file depencies:
 *       includes
 *       स्थिरants
 *       काष्ठाs
 *       prototypes
 *       macros, बाह्यs, and अंतरभूतs
 *
 *   Move test_frame specअगरic items out of the kernel headers
 *   and पूर्णांकo the test frame headers.   This is not perfect in any sense
 *   and will जारी to evolve.
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <linux/tty.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/idr.h>

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#पूर्ण_अगर

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <net/sock.h>
#समावेश <net/snmp.h>
#समावेश <net/sctp/काष्ठाs.h>
#समावेश <net/sctp/स्थिरants.h>

#अगर_घोषित CONFIG_IP_SCTP_MODULE
#घोषणा SCTP_PROTOSW_FLAG 0
#अन्यथा /* अटल! */
#घोषणा SCTP_PROTOSW_FLAG INET_PROTOSW_PERMANENT
#पूर्ण_अगर

/* Round an पूर्णांक up to the next multiple of 4.  */
#घोषणा SCTP_PAD4(s) (((s)+3)&~3)
/* Truncate to the previous multiple of 4.  */
#घोषणा SCTP_TRUNC4(s) ((s)&~3)

/*
 * Function declarations.
 */

/*
 * sctp/protocol.c
 */
पूर्णांक sctp_copy_local_addr_list(काष्ठा net *net, काष्ठा sctp_bind_addr *addr,
			      क्रमागत sctp_scope, gfp_t gfp, पूर्णांक flags);
काष्ठा sctp_pf *sctp_get_pf_specअगरic(sa_family_t family);
पूर्णांक sctp_रेजिस्टर_pf(काष्ठा sctp_pf *, sa_family_t);
व्योम sctp_addr_wq_mgmt(काष्ठा net *, काष्ठा sctp_sockaddr_entry *, पूर्णांक);
पूर्णांक sctp_udp_sock_start(काष्ठा net *net);
व्योम sctp_udp_sock_stop(काष्ठा net *net);

/*
 * sctp/socket.c
 */
पूर्णांक sctp_inet_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		      पूर्णांक addr_len, पूर्णांक flags);
पूर्णांक sctp_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक sctp_inet_listen(काष्ठा socket *sock, पूर्णांक backlog);
व्योम sctp_ग_लिखो_space(काष्ठा sock *sk);
व्योम sctp_data_पढ़ोy(काष्ठा sock *sk);
__poll_t sctp_poll(काष्ठा file *file, काष्ठा socket *sock,
		poll_table *रुको);
व्योम sctp_sock_rमुक्त(काष्ठा sk_buff *skb);
व्योम sctp_copy_sock(काष्ठा sock *newsk, काष्ठा sock *sk,
		    काष्ठा sctp_association *asoc);
बाह्य काष्ठा percpu_counter sctp_sockets_allocated;
पूर्णांक sctp_asconf_mgmt(काष्ठा sctp_sock *, काष्ठा sctp_sockaddr_entry *);
काष्ठा sk_buff *sctp_skb_recv_datagram(काष्ठा sock *, पूर्णांक, पूर्णांक, पूर्णांक *);

व्योम sctp_transport_walk_start(काष्ठा rhashtable_iter *iter);
व्योम sctp_transport_walk_stop(काष्ठा rhashtable_iter *iter);
काष्ठा sctp_transport *sctp_transport_get_next(काष्ठा net *net,
			काष्ठा rhashtable_iter *iter);
काष्ठा sctp_transport *sctp_transport_get_idx(काष्ठा net *net,
			काष्ठा rhashtable_iter *iter, पूर्णांक pos);
पूर्णांक sctp_transport_lookup_process(पूर्णांक (*cb)(काष्ठा sctp_transport *, व्योम *),
				  काष्ठा net *net,
				  स्थिर जोड़ sctp_addr *laddr,
				  स्थिर जोड़ sctp_addr *paddr, व्योम *p);
पूर्णांक sctp_क्रम_each_transport(पूर्णांक (*cb)(काष्ठा sctp_transport *, व्योम *),
			    पूर्णांक (*cb_करोne)(काष्ठा sctp_transport *, व्योम *),
			    काष्ठा net *net, पूर्णांक *pos, व्योम *p);
पूर्णांक sctp_क्रम_each_endpoपूर्णांक(पूर्णांक (*cb)(काष्ठा sctp_endpoपूर्णांक *, व्योम *), व्योम *p);
पूर्णांक sctp_get_sctp_info(काष्ठा sock *sk, काष्ठा sctp_association *asoc,
		       काष्ठा sctp_info *info);

/*
 * sctp/primitive.c
 */
पूर्णांक sctp_primitive_ASSOCIATE(काष्ठा net *, काष्ठा sctp_association *, व्योम *arg);
पूर्णांक sctp_primitive_SHUTDOWN(काष्ठा net *, काष्ठा sctp_association *, व्योम *arg);
पूर्णांक sctp_primitive_ABORT(काष्ठा net *, काष्ठा sctp_association *, व्योम *arg);
पूर्णांक sctp_primitive_SEND(काष्ठा net *, काष्ठा sctp_association *, व्योम *arg);
पूर्णांक sctp_primitive_REQUESTHEARTBEAT(काष्ठा net *, काष्ठा sctp_association *, व्योम *arg);
पूर्णांक sctp_primitive_ASCONF(काष्ठा net *, काष्ठा sctp_association *, व्योम *arg);
पूर्णांक sctp_primitive_RECONF(काष्ठा net *net, काष्ठा sctp_association *asoc,
			  व्योम *arg);

/*
 * sctp/input.c
 */
पूर्णांक sctp_rcv(काष्ठा sk_buff *skb);
पूर्णांक sctp_v4_err(काष्ठा sk_buff *skb, u32 info);
पूर्णांक sctp_hash_endpoपूर्णांक(काष्ठा sctp_endpoपूर्णांक *ep);
व्योम sctp_unhash_endpoपूर्णांक(काष्ठा sctp_endpoपूर्णांक *);
काष्ठा sock *sctp_err_lookup(काष्ठा net *net, पूर्णांक family, काष्ठा sk_buff *,
			     काष्ठा sctphdr *, काष्ठा sctp_association **,
			     काष्ठा sctp_transport **);
व्योम sctp_err_finish(काष्ठा sock *, काष्ठा sctp_transport *);
व्योम sctp_icmp_frag_needed(काष्ठा sock *, काष्ठा sctp_association *,
			   काष्ठा sctp_transport *t, __u32 pmtu);
व्योम sctp_icmp_redirect(काष्ठा sock *, काष्ठा sctp_transport *,
			काष्ठा sk_buff *);
व्योम sctp_icmp_proto_unreachable(काष्ठा sock *sk,
				 काष्ठा sctp_association *asoc,
				 काष्ठा sctp_transport *t);
व्योम sctp_backlog_migrate(काष्ठा sctp_association *assoc,
			  काष्ठा sock *oldsk, काष्ठा sock *newsk);
पूर्णांक sctp_transport_hashtable_init(व्योम);
व्योम sctp_transport_hashtable_destroy(व्योम);
पूर्णांक sctp_hash_transport(काष्ठा sctp_transport *t);
व्योम sctp_unhash_transport(काष्ठा sctp_transport *t);
काष्ठा sctp_transport *sctp_addrs_lookup_transport(
				काष्ठा net *net,
				स्थिर जोड़ sctp_addr *laddr,
				स्थिर जोड़ sctp_addr *paddr);
काष्ठा sctp_transport *sctp_epaddr_lookup_transport(
				स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				स्थिर जोड़ sctp_addr *paddr);

/*
 * sctp/proc.c
 */
पूर्णांक __net_init sctp_proc_init(काष्ठा net *net);

/*
 * sctp/offload.c
 */
पूर्णांक sctp_offload_init(व्योम);

/*
 * sctp/stream_sched.c
 */
व्योम sctp_sched_ops_init(व्योम);

/*
 * sctp/stream.c
 */
पूर्णांक sctp_send_reset_streams(काष्ठा sctp_association *asoc,
			    काष्ठा sctp_reset_streams *params);
पूर्णांक sctp_send_reset_assoc(काष्ठा sctp_association *asoc);
पूर्णांक sctp_send_add_streams(काष्ठा sctp_association *asoc,
			  काष्ठा sctp_add_streams *params);

/*
 * Module global variables
 */

 /*
  * sctp/protocol.c
  */
बाह्य काष्ठा kmem_cache *sctp_chunk_cachep __पढ़ो_mostly;
बाह्य काष्ठा kmem_cache *sctp_bucket_cachep __पढ़ो_mostly;
बाह्य दीर्घ sysctl_sctp_mem[3];
बाह्य पूर्णांक sysctl_sctp_rmem[3];
बाह्य पूर्णांक sysctl_sctp_wmem[3];

/*
 *  Section:  Macros, बाह्यs, and अंतरभूतs
 */

/* SCTP SNMP MIB stats handlers */
#घोषणा SCTP_INC_STATS(net, field)	SNMP_INC_STATS((net)->sctp.sctp_statistics, field)
#घोषणा __SCTP_INC_STATS(net, field)	__SNMP_INC_STATS((net)->sctp.sctp_statistics, field)
#घोषणा SCTP_DEC_STATS(net, field)	SNMP_DEC_STATS((net)->sctp.sctp_statistics, field)

/* sctp mib definitions */
क्रमागत अणु
	SCTP_MIB_NUM = 0,
	SCTP_MIB_CURRESTAB,			/* CurrEstab */
	SCTP_MIB_ACTIVEESTABS,			/* ActiveEstअसल */
	SCTP_MIB_PASSIVEESTABS,			/* PassiveEstअसल */
	SCTP_MIB_ABORTEDS,			/* Aborteds */
	SCTP_MIB_SHUTDOWNS,			/* Shutकरोwns */
	SCTP_MIB_OUTOFBLUES,			/* OutOfBlues */
	SCTP_MIB_CHECKSUMERRORS,		/* ChecksumErrors */
	SCTP_MIB_OUTCTRLCHUNKS,			/* OutCtrlChunks */
	SCTP_MIB_OUTORDERCHUNKS,		/* OutOrderChunks */
	SCTP_MIB_OUTUNORDERCHUNKS,		/* OutUnorderChunks */
	SCTP_MIB_INCTRLCHUNKS,			/* InCtrlChunks */
	SCTP_MIB_INORDERCHUNKS,			/* InOrderChunks */
	SCTP_MIB_INUNORDERCHUNKS,		/* InUnorderChunks */
	SCTP_MIB_FRAGUSRMSGS,			/* FragUsrMsgs */
	SCTP_MIB_REASMUSRMSGS,			/* Reयंत्रUsrMsgs */
	SCTP_MIB_OUTSCTPPACKS,			/* OutSCTPPacks */
	SCTP_MIB_INSCTPPACKS,			/* InSCTPPacks */
	SCTP_MIB_T1_INIT_EXPIREDS,
	SCTP_MIB_T1_COOKIE_EXPIREDS,
	SCTP_MIB_T2_SHUTDOWN_EXPIREDS,
	SCTP_MIB_T3_RTX_EXPIREDS,
	SCTP_MIB_T4_RTO_EXPIREDS,
	SCTP_MIB_T5_SHUTDOWN_GUARD_EXPIREDS,
	SCTP_MIB_DELAY_SACK_EXPIREDS,
	SCTP_MIB_AUTOCLOSE_EXPIREDS,
	SCTP_MIB_T1_RETRANSMITS,
	SCTP_MIB_T3_RETRANSMITS,
	SCTP_MIB_PMTUD_RETRANSMITS,
	SCTP_MIB_FAST_RETRANSMITS,
	SCTP_MIB_IN_PKT_SOFTIRQ,
	SCTP_MIB_IN_PKT_BACKLOG,
	SCTP_MIB_IN_PKT_DISCARDS,
	SCTP_MIB_IN_DATA_CHUNK_DISCARDS,
	__SCTP_MIB_MAX
पूर्ण;

#घोषणा SCTP_MIB_MAX    __SCTP_MIB_MAX
काष्ठा sctp_mib अणु
        अचिन्हित दीर्घ   mibs[SCTP_MIB_MAX];
पूर्ण;

/* helper function to track stats about max rto and related transport */
अटल अंतरभूत व्योम sctp_max_rto(काष्ठा sctp_association *asoc,
				काष्ठा sctp_transport *trans)
अणु
	अगर (asoc->stats.max_obs_rto < (__u64)trans->rto) अणु
		asoc->stats.max_obs_rto = trans->rto;
		स_रखो(&asoc->stats.obs_rto_ipaddr, 0,
			माप(काष्ठा sockaddr_storage));
		स_नकल(&asoc->stats.obs_rto_ipaddr, &trans->ipaddr,
			trans->af_specअगरic->sockaddr_len);
	पूर्ण
पूर्ण

/*
 * Macros क्रम keeping a global reference of object allocations.
 */
#अगर_घोषित CONFIG_SCTP_DBG_OBJCNT

बाह्य atomic_t sctp_dbg_objcnt_sock;
बाह्य atomic_t sctp_dbg_objcnt_ep;
बाह्य atomic_t sctp_dbg_objcnt_assoc;
बाह्य atomic_t sctp_dbg_objcnt_transport;
बाह्य atomic_t sctp_dbg_objcnt_chunk;
बाह्य atomic_t sctp_dbg_objcnt_bind_addr;
बाह्य atomic_t sctp_dbg_objcnt_bind_bucket;
बाह्य atomic_t sctp_dbg_objcnt_addr;
बाह्य atomic_t sctp_dbg_objcnt_datamsg;
बाह्य atomic_t sctp_dbg_objcnt_keys;

/* Macros to atomically increment/decrement objcnt counters.  */
#घोषणा SCTP_DBG_OBJCNT_INC(name) \
atomic_inc(&sctp_dbg_objcnt_## name)
#घोषणा SCTP_DBG_OBJCNT_DEC(name) \
atomic_dec(&sctp_dbg_objcnt_## name)
#घोषणा SCTP_DBG_OBJCNT(name) \
atomic_t sctp_dbg_objcnt_## name = ATOMIC_INIT(0)

/* Macro to help create new entries in the global array of
 * objcnt counters.
 */
#घोषणा SCTP_DBG_OBJCNT_ENTRY(name) \
अणु.label= #name, .counter= &sctp_dbg_objcnt_## nameपूर्ण

व्योम sctp_dbg_objcnt_init(काष्ठा net *);

#अन्यथा

#घोषणा SCTP_DBG_OBJCNT_INC(name)
#घोषणा SCTP_DBG_OBJCNT_DEC(name)

अटल अंतरभूत व्योम sctp_dbg_objcnt_init(काष्ठा net *net) अणु वापस; पूर्ण

#पूर्ण_अगर /* CONFIG_SCTP_DBG_OBJCOUNT */

#अगर defined CONFIG_SYSCTL
व्योम sctp_sysctl_रेजिस्टर(व्योम);
व्योम sctp_sysctl_unरेजिस्टर(व्योम);
पूर्णांक sctp_sysctl_net_रेजिस्टर(काष्ठा net *net);
व्योम sctp_sysctl_net_unरेजिस्टर(काष्ठा net *net);
#अन्यथा
अटल अंतरभूत व्योम sctp_sysctl_रेजिस्टर(व्योम) अणु वापस; पूर्ण
अटल अंतरभूत व्योम sctp_sysctl_unरेजिस्टर(व्योम) अणु वापस; पूर्ण
अटल अंतरभूत पूर्णांक sctp_sysctl_net_रेजिस्टर(काष्ठा net *net) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम sctp_sysctl_net_unरेजिस्टर(काष्ठा net *net) अणु वापस; पूर्ण
#पूर्ण_अगर

/* Size of Supported Address Parameter क्रम 'x' address types. */
#घोषणा SCTP_SAT_LEN(x) (माप(काष्ठा sctp_paramhdr) + (x) * माप(__u16))

#अगर IS_ENABLED(CONFIG_IPV6)

व्योम sctp_v6_pf_init(व्योम);
व्योम sctp_v6_pf_निकास(व्योम);
पूर्णांक sctp_v6_protosw_init(व्योम);
व्योम sctp_v6_protosw_निकास(व्योम);
पूर्णांक sctp_v6_add_protocol(व्योम);
व्योम sctp_v6_del_protocol(व्योम);

#अन्यथा /* #अगर_घोषित defined(CONFIG_IPV6) */

अटल अंतरभूत व्योम sctp_v6_pf_init(व्योम) अणु वापस; पूर्ण
अटल अंतरभूत व्योम sctp_v6_pf_निकास(व्योम) अणु वापस; पूर्ण
अटल अंतरभूत पूर्णांक sctp_v6_protosw_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम sctp_v6_protosw_निकास(व्योम) अणु वापस; पूर्ण
अटल अंतरभूत पूर्णांक sctp_v6_add_protocol(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम sctp_v6_del_protocol(व्योम) अणु वापस; पूर्ण

#पूर्ण_अगर /* #अगर defined(CONFIG_IPV6) */


/* Map an association to an assoc_id. */
अटल अंतरभूत sctp_assoc_t sctp_assoc2id(स्थिर काष्ठा sctp_association *asoc)
अणु
	वापस asoc ? asoc->assoc_id : 0;
पूर्ण

अटल अंतरभूत क्रमागत sctp_sstat_state
sctp_assoc_to_state(स्थिर काष्ठा sctp_association *asoc)
अणु
	/* SCTP's uapi always had SCTP_EMPTY(=0) as a dummy state, but we
	 * got rid of it in kernel space. Thereक्रमe SCTP_CLOSED et al
	 * start at =1 in user space, but actually as =0 in kernel space.
	 * Now that we can not अवरोध user space and SCTP_EMPTY is exposed
	 * there, we need to fix it up with an ugly offset not to अवरोध
	 * applications. :(
	 */
	वापस asoc->state + 1;
पूर्ण

/* Look up the association by its id.  */
काष्ठा sctp_association *sctp_id2assoc(काष्ठा sock *sk, sctp_assoc_t id);

पूर्णांक sctp_करो_peeloff(काष्ठा sock *sk, sctp_assoc_t id, काष्ठा socket **sockp);

/* A macro to walk a list of skbs.  */
#घोषणा sctp_skb_क्रम_each(pos, head, पंचांगp) \
	skb_queue_walk_safe(head, pos, पंचांगp)

/**
 *	sctp_list_dequeue - हटाओ from the head of the queue
 *	@list: list to dequeue from
 *
 *	Remove the head of the list. The head item is
 *	वापसed or %शून्य अगर the list is empty.
 */

अटल अंतरभूत काष्ठा list_head *sctp_list_dequeue(काष्ठा list_head *list)
अणु
	काष्ठा list_head *result = शून्य;

	अगर (!list_empty(list)) अणु
		result = list->next;
		list_del_init(result);
	पूर्ण
	वापस result;
पूर्ण

/* SCTP version of skb_set_owner_r.  We need this one because
 * of the way we have to करो receive buffer accounting on bundled
 * chunks.
 */
अटल अंतरभूत व्योम sctp_skb_set_owner_r(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	काष्ठा sctp_ulpevent *event = sctp_skb2event(skb);

	skb_orphan(skb);
	skb->sk = sk;
	skb->deकाष्ठाor = sctp_sock_rमुक्त;
	atomic_add(event->rmem_len, &sk->sk_rmem_alloc);
	/*
	 * This mimics the behavior of skb_set_owner_r
	 */
	sk_mem_अक्षरge(sk, event->rmem_len);
पूर्ण

/* Tests अगर the list has one and only one entry. */
अटल अंतरभूत पूर्णांक sctp_list_single_entry(काष्ठा list_head *head)
अणु
	वापस list_is_singular(head);
पूर्ण

अटल अंतरभूत bool sctp_chunk_pending(स्थिर काष्ठा sctp_chunk *chunk)
अणु
	वापस !list_empty(&chunk->list);
पूर्ण

/* Walk through a list of TLV parameters.  Don't trust the
 * inभागidual parameter lengths and instead depend on
 * the chunk length to indicate when to stop.  Make sure
 * there is room क्रम a param header too.
 */
#घोषणा sctp_walk_params(pos, chunk, member)\
_sctp_walk_params((pos), (chunk), ntohs((chunk)->chunk_hdr.length), member)

#घोषणा _sctp_walk_params(pos, chunk, end, member)\
क्रम (pos.v = chunk->member;\
     (pos.v + दुरत्व(काष्ठा sctp_paramhdr, length) + माप(pos.p->length) <=\
      (व्योम *)chunk + end) &&\
     pos.v <= (व्योम *)chunk + end - ntohs(pos.p->length) &&\
     ntohs(pos.p->length) >= माप(काष्ठा sctp_paramhdr);\
     pos.v += SCTP_PAD4(ntohs(pos.p->length)))

#घोषणा sctp_walk_errors(err, chunk_hdr)\
_sctp_walk_errors((err), (chunk_hdr), ntohs((chunk_hdr)->length))

#घोषणा _sctp_walk_errors(err, chunk_hdr, end)\
क्रम (err = (काष्ठा sctp_errhdr *)((व्योम *)chunk_hdr + \
	    माप(काष्ठा sctp_chunkhdr));\
     ((व्योम *)err + दुरत्व(काष्ठा sctp_errhdr, length) + माप(err->length) <=\
      (व्योम *)chunk_hdr + end) &&\
     (व्योम *)err <= (व्योम *)chunk_hdr + end - ntohs(err->length) &&\
     ntohs(err->length) >= माप(काष्ठा sctp_errhdr); \
     err = (काष्ठा sctp_errhdr *)((व्योम *)err + SCTP_PAD4(ntohs(err->length))))

#घोषणा sctp_walk_fwdtsn(pos, chunk)\
_sctp_walk_fwdtsn((pos), (chunk), ntohs((chunk)->chunk_hdr->length) - माप(काष्ठा sctp_fwdtsn_chunk))

#घोषणा _sctp_walk_fwdtsn(pos, chunk, end)\
क्रम (pos = chunk->subh.fwdtsn_hdr->skip;\
     (व्योम *)pos <= (व्योम *)chunk->subh.fwdtsn_hdr->skip + end - माप(काष्ठा sctp_fwdtsn_skip);\
     pos++)

/* External references. */

बाह्य काष्ठा proto sctp_prot;
बाह्य काष्ठा proto sctpv6_prot;
व्योम sctp_put_port(काष्ठा sock *sk);

बाह्य काष्ठा idr sctp_assocs_id;
बाह्य spinlock_t sctp_assocs_id_lock;

/* Static अंतरभूत functions. */

/* Convert from an IP version number to an Address Family symbol.  */
अटल अंतरभूत पूर्णांक ipver2af(__u8 ipver)
अणु
	चयन (ipver) अणु
	हाल 4:
	        वापस  AF_INET;
	हाल 6:
		वापस AF_INET6;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Convert from an address parameter type to an address family.  */
अटल अंतरभूत पूर्णांक param_type2af(__be16 type)
अणु
	चयन (type) अणु
	हाल SCTP_PARAM_IPV4_ADDRESS:
	        वापस  AF_INET;
	हाल SCTP_PARAM_IPV6_ADDRESS:
		वापस AF_INET6;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Warning: The following hash functions assume a घातer of two 'size'. */
/* This is the hash function क्रम the SCTP port hash table. */
अटल अंतरभूत पूर्णांक sctp_phashfn(काष्ठा net *net, __u16 lport)
अणु
	वापस (net_hash_mix(net) + lport) & (sctp_port_hashsize - 1);
पूर्ण

/* This is the hash function क्रम the endpoपूर्णांक hash table. */
अटल अंतरभूत पूर्णांक sctp_ep_hashfn(काष्ठा net *net, __u16 lport)
अणु
	वापस (net_hash_mix(net) + lport) & (sctp_ep_hashsize - 1);
पूर्ण

#घोषणा sctp_क्रम_each_hentry(epb, head) \
	hlist_क्रम_each_entry(epb, head, node)

/* Is a socket of this style? */
#घोषणा sctp_style(sk, style) __sctp_style((sk), (SCTP_SOCKET_##style))
अटल अंतरभूत पूर्णांक __sctp_style(स्थिर काष्ठा sock *sk,
			       क्रमागत sctp_socket_type style)
अणु
	वापस sctp_sk(sk)->type == style;
पूर्ण

/* Is the association in this state? */
#घोषणा sctp_state(asoc, state) __sctp_state((asoc), (SCTP_STATE_##state))
अटल अंतरभूत पूर्णांक __sctp_state(स्थिर काष्ठा sctp_association *asoc,
			       क्रमागत sctp_state state)
अणु
	वापस asoc->state == state;
पूर्ण

/* Is the socket in this state? */
#घोषणा sctp_sstate(sk, state) __sctp_sstate((sk), (SCTP_SS_##state))
अटल अंतरभूत पूर्णांक __sctp_sstate(स्थिर काष्ठा sock *sk,
				क्रमागत sctp_sock_state state)
अणु
	वापस sk->sk_state == state;
पूर्ण

/* Map v4-mapped v6 address back to v4 address */
अटल अंतरभूत व्योम sctp_v6_map_v4(जोड़ sctp_addr *addr)
अणु
	addr->v4.sin_family = AF_INET;
	addr->v4.sin_port = addr->v6.sin6_port;
	addr->v4.sin_addr.s_addr = addr->v6.sin6_addr.s6_addr32[3];
पूर्ण

/* Map v4 address to v4-mapped v6 address */
अटल अंतरभूत व्योम sctp_v4_map_v6(जोड़ sctp_addr *addr)
अणु
	__be16 port;

	port = addr->v4.sin_port;
	addr->v6.sin6_addr.s6_addr32[3] = addr->v4.sin_addr.s_addr;
	addr->v6.sin6_port = port;
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_flowinfo = 0;
	addr->v6.sin6_scope_id = 0;
	addr->v6.sin6_addr.s6_addr32[0] = 0;
	addr->v6.sin6_addr.s6_addr32[1] = 0;
	addr->v6.sin6_addr.s6_addr32[2] = htonl(0x0000ffff);
पूर्ण

/* The cookie is always 0 since this is how it's used in the
 * pmtu code.
 */
अटल अंतरभूत काष्ठा dst_entry *sctp_transport_dst_check(काष्ठा sctp_transport *t)
अणु
	अगर (t->dst && !dst_check(t->dst, t->dst_cookie))
		sctp_transport_dst_release(t);

	वापस t->dst;
पूर्ण

/* Calculate max payload size given a MTU, or the total overhead अगर
 * given MTU is zero
 */
अटल अंतरभूत __u32 sctp_mtu_payload(स्थिर काष्ठा sctp_sock *sp,
				     __u32 mtu, __u32 extra)
अणु
	__u32 overhead = माप(काष्ठा sctphdr) + extra;

	अगर (sp) अणु
		overhead += sp->pf->af->net_header_len;
		अगर (sp->udp_port)
			overhead += माप(काष्ठा udphdr);
	पूर्ण अन्यथा अणु
		overhead += माप(काष्ठा ipv6hdr);
	पूर्ण

	अगर (WARN_ON_ONCE(mtu && mtu <= overhead))
		mtu = overhead;

	वापस mtu ? mtu - overhead : overhead;
पूर्ण

अटल अंतरभूत __u32 sctp_dst_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस SCTP_TRUNC4(max_t(__u32, dst_mtu(dst),
				 SCTP_DEFAULT_MINSEGMENT));
पूर्ण

अटल अंतरभूत bool sctp_transport_pmtu_check(काष्ठा sctp_transport *t)
अणु
	__u32 pmtu = sctp_dst_mtu(t->dst);

	अगर (t->pathmtu == pmtu)
		वापस true;

	t->pathmtu = pmtu;

	वापस false;
पूर्ण

अटल अंतरभूत __u32 sctp_min_frag_poपूर्णांक(काष्ठा sctp_sock *sp, __u16 datasize)
अणु
	वापस sctp_mtu_payload(sp, SCTP_DEFAULT_MINSEGMENT, datasize);
पूर्ण

अटल अंतरभूत bool sctp_newsk_पढ़ोy(स्थिर काष्ठा sock *sk)
अणु
	वापस sock_flag(sk, SOCK_DEAD) || sk->sk_socket;
पूर्ण

अटल अंतरभूत व्योम sctp_sock_set_nodelay(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	sctp_sk(sk)->nodelay = true;
	release_sock(sk);
पूर्ण

#पूर्ण_अगर /* __net_sctp_h__ */
