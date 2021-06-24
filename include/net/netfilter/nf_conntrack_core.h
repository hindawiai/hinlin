<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header is used to share core functionality between the
 * standalone connection tracking module, and the compatibility layer's use
 * of connection tracking.
 *
 * 16 Dec 2003: Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- generalize L3 protocol dependent part.
 *
 * Derived from include/linux/netfiter_ipv4/ip_conntrack_core.h
 */

#अगर_अघोषित _NF_CONNTRACK_CORE_H
#घोषणा _NF_CONNTRACK_CORE_H

#समावेश <linux/netfilter.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>

/* This header is used to share core functionality between the
   standalone connection tracking module, and the compatibility layer's use
   of connection tracking. */

अचिन्हित पूर्णांक nf_conntrack_in(काष्ठा sk_buff *skb,
			     स्थिर काष्ठा nf_hook_state *state);

पूर्णांक nf_conntrack_init_net(काष्ठा net *net);
व्योम nf_conntrack_cleanup_net(काष्ठा net *net);
व्योम nf_conntrack_cleanup_net_list(काष्ठा list_head *net_निकास_list);

व्योम nf_conntrack_proto_pernet_init(काष्ठा net *net);
व्योम nf_conntrack_proto_pernet_fini(काष्ठा net *net);

पूर्णांक nf_conntrack_proto_init(व्योम);
व्योम nf_conntrack_proto_fini(व्योम);

पूर्णांक nf_conntrack_init_start(व्योम);
व्योम nf_conntrack_cleanup_start(व्योम);

व्योम nf_conntrack_init_end(व्योम);
व्योम nf_conntrack_cleanup_end(व्योम);

bool nf_ct_invert_tuple(काष्ठा nf_conntrack_tuple *inverse,
			स्थिर काष्ठा nf_conntrack_tuple *orig);

/* Find a connection corresponding to a tuple. */
काष्ठा nf_conntrack_tuple_hash *
nf_conntrack_find_get(काष्ठा net *net,
		      स्थिर काष्ठा nf_conntrack_zone *zone,
		      स्थिर काष्ठा nf_conntrack_tuple *tuple);

पूर्णांक __nf_conntrack_confirm(काष्ठा sk_buff *skb);

/* Confirm a connection: वापसs NF_DROP अगर packet must be dropped. */
अटल अंतरभूत पूर्णांक nf_conntrack_confirm(काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_conn *ct = (काष्ठा nf_conn *)skb_nfct(skb);
	पूर्णांक ret = NF_ACCEPT;

	अगर (ct) अणु
		अगर (!nf_ct_is_confirmed(ct))
			ret = __nf_conntrack_confirm(skb);
		अगर (likely(ret == NF_ACCEPT))
			nf_ct_deliver_cached_events(ct);
	पूर्ण
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक nf_confirm(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo);

व्योम prपूर्णांक_tuple(काष्ठा seq_file *s, स्थिर काष्ठा nf_conntrack_tuple *tuple,
		 स्थिर काष्ठा nf_conntrack_l4proto *proto);

#घोषणा CONNTRACK_LOCKS 1024

बाह्य spinlock_t nf_conntrack_locks[CONNTRACK_LOCKS];
व्योम nf_conntrack_lock(spinlock_t *lock);

बाह्य spinlock_t nf_conntrack_expect_lock;

#पूर्ण_अगर /* _NF_CONNTRACK_CORE_H */
