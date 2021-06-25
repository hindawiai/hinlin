<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the RAW-IP module.
 *
 * Version:	@(#)raw.h	1.0.2	05/07/93
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#अगर_अघोषित _RAW_H
#घोषणा _RAW_H

#समावेश <net/inet_sock.h>
#समावेश <net/protocol.h>
#समावेश <linux/icmp.h>

बाह्य काष्ठा proto raw_prot;

बाह्य काष्ठा raw_hashinfo raw_v4_hashinfo;
काष्ठा sock *__raw_v4_lookup(काष्ठा net *net, काष्ठा sock *sk,
			     अचिन्हित लघु num, __be32 raddr,
			     __be32 laddr, पूर्णांक dअगर, पूर्णांक sdअगर);

पूर्णांक raw_पात(काष्ठा sock *sk, पूर्णांक err);
व्योम raw_icmp_error(काष्ठा sk_buff *, पूर्णांक, u32);
पूर्णांक raw_local_deliver(काष्ठा sk_buff *, पूर्णांक);

पूर्णांक raw_rcv(काष्ठा sock *, काष्ठा sk_buff *);

#घोषणा RAW_HTABLE_SIZE	MAX_INET_PROTOS

काष्ठा raw_hashinfo अणु
	rwlock_t lock;
	काष्ठा hlist_head ht[RAW_HTABLE_SIZE];
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक raw_proc_init(व्योम);
व्योम raw_proc_निकास(व्योम);

काष्ठा raw_iter_state अणु
	काष्ठा seq_net_निजी p;
	पूर्णांक bucket;
पूर्ण;

अटल अंतरभूत काष्ठा raw_iter_state *raw_seq_निजी(काष्ठा seq_file *seq)
अणु
	वापस seq->निजी;
पूर्ण
व्योम *raw_seq_start(काष्ठा seq_file *seq, loff_t *pos);
व्योम *raw_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos);
व्योम raw_seq_stop(काष्ठा seq_file *seq, व्योम *v);
#पूर्ण_अगर

पूर्णांक raw_hash_sk(काष्ठा sock *sk);
व्योम raw_unhash_sk(काष्ठा sock *sk);
व्योम raw_init(व्योम);

काष्ठा raw_sock अणु
	/* inet_sock has to be the first member */
	काष्ठा inet_sock   inet;
	काष्ठा icmp_filter filter;
	u32		   ipmr_table;
पूर्ण;

अटल अंतरभूत काष्ठा raw_sock *raw_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा raw_sock *)sk;
पूर्ण

अटल अंतरभूत bool raw_sk_bound_dev_eq(काष्ठा net *net, पूर्णांक bound_dev_अगर,
				       पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
#अगर IS_ENABLED(CONFIG_NET_L3_MASTER_DEV)
	वापस inet_bound_dev_eq(!!net->ipv4.sysctl_raw_l3mdev_accept,
				 bound_dev_अगर, dअगर, sdअगर);
#अन्यथा
	वापस inet_bound_dev_eq(true, bound_dev_अगर, dअगर, sdअगर);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर	/* _RAW_H */
