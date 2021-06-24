<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * File: af_phonet.h
 *
 * Phonet sockets kernel definitions
 *
 * Copyright (C) 2008 Nokia Corporation.
 */

#अगर_अघोषित AF_PHONET_H
#घोषणा AF_PHONET_H

/*
 * The lower layers may not require more space, ever. Make sure it's
 * enough.
 */
#घोषणा MAX_PHONET_HEADER	(8 + MAX_HEADER)

/*
 * Every Phonet* socket has this काष्ठाure first in its
 * protocol-specअगरic काष्ठाure under name c.
 */
काष्ठा pn_sock अणु
	काष्ठा sock	sk;
	u16		sobject;
	u16		करोbject;
	u8		resource;
पूर्ण;

अटल अंतरभूत काष्ठा pn_sock *pn_sk(काष्ठा sock *sk)
अणु
	वापस (काष्ठा pn_sock *)sk;
पूर्ण

बाह्य स्थिर काष्ठा proto_ops phonet_dgram_ops;

व्योम pn_sock_init(व्योम);
काष्ठा sock *pn_find_sock_by_sa(काष्ठा net *net, स्थिर काष्ठा sockaddr_pn *sa);
व्योम pn_deliver_sock_broadcast(काष्ठा net *net, काष्ठा sk_buff *skb);
व्योम phonet_get_local_port_range(पूर्णांक *min, पूर्णांक *max);
पूर्णांक pn_sock_hash(काष्ठा sock *sk);
व्योम pn_sock_unhash(काष्ठा sock *sk);
पूर्णांक pn_sock_get_port(काष्ठा sock *sk, अचिन्हित लघु sport);

काष्ठा sock *pn_find_sock_by_res(काष्ठा net *net, u8 res);
पूर्णांक pn_sock_bind_res(काष्ठा sock *sock, u8 res);
पूर्णांक pn_sock_unbind_res(काष्ठा sock *sk, u8 res);
व्योम pn_sock_unbind_all_res(काष्ठा sock *sk);

पूर्णांक pn_skb_send(काष्ठा sock *sk, काष्ठा sk_buff *skb,
		स्थिर काष्ठा sockaddr_pn *target);

अटल अंतरभूत काष्ठा phonethdr *pn_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा phonethdr *)skb_network_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा phoneपंचांगsg *pn_msg(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा phoneपंचांगsg *)skb_transport_header(skb);
पूर्ण

/*
 * Get the other party's sockaddr from received skb. The skb begins
 * with a Phonet header.
 */
अटल अंतरभूत
व्योम pn_skb_get_src_sockaddr(काष्ठा sk_buff *skb, काष्ठा sockaddr_pn *sa)
अणु
	काष्ठा phonethdr *ph = pn_hdr(skb);
	u16 obj = pn_object(ph->pn_sdev, ph->pn_sobj);

	sa->spn_family = AF_PHONET;
	pn_sockaddr_set_object(sa, obj);
	pn_sockaddr_set_resource(sa, ph->pn_res);
	स_रखो(sa->spn_zero, 0, माप(sa->spn_zero));
पूर्ण

अटल अंतरभूत
व्योम pn_skb_get_dst_sockaddr(काष्ठा sk_buff *skb, काष्ठा sockaddr_pn *sa)
अणु
	काष्ठा phonethdr *ph = pn_hdr(skb);
	u16 obj = pn_object(ph->pn_rdev, ph->pn_robj);

	sa->spn_family = AF_PHONET;
	pn_sockaddr_set_object(sa, obj);
	pn_sockaddr_set_resource(sa, ph->pn_res);
	स_रखो(sa->spn_zero, 0, माप(sa->spn_zero));
पूर्ण

/* Protocols in Phonet protocol family. */
काष्ठा phonet_protocol अणु
	स्थिर काष्ठा proto_ops	*ops;
	काष्ठा proto		*prot;
	पूर्णांक			sock_type;
पूर्ण;

पूर्णांक phonet_proto_रेजिस्टर(अचिन्हित पूर्णांक protocol,
		स्थिर काष्ठा phonet_protocol *pp);
व्योम phonet_proto_unरेजिस्टर(अचिन्हित पूर्णांक protocol,
		स्थिर काष्ठा phonet_protocol *pp);

पूर्णांक phonet_sysctl_init(व्योम);
व्योम phonet_sysctl_निकास(व्योम);
पूर्णांक isi_रेजिस्टर(व्योम);
व्योम isi_unरेजिस्टर(व्योम);

#पूर्ण_अगर
