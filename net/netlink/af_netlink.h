<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _AF_NETLINK_H
#घोषणा _AF_NETLINK_H

#समावेश <linux/rhashtable.h>
#समावेश <linux/atomic.h>
#समावेश <linux/workqueue.h>
#समावेश <net/sock.h>

/* flags */
#घोषणा NETLINK_F_KERNEL_SOCKET		0x1
#घोषणा NETLINK_F_RECV_PKTINFO		0x2
#घोषणा NETLINK_F_BROADCAST_SEND_ERROR	0x4
#घोषणा NETLINK_F_RECV_NO_ENOBUFS	0x8
#घोषणा NETLINK_F_LISTEN_ALL_NSID	0x10
#घोषणा NETLINK_F_CAP_ACK		0x20
#घोषणा NETLINK_F_EXT_ACK		0x40
#घोषणा NETLINK_F_STRICT_CHK		0x80

#घोषणा NLGRPSZ(x)	(ALIGN(x, माप(अचिन्हित दीर्घ) * 8) / 8)
#घोषणा NLGRPLONGS(x)	(NLGRPSZ(x)/माप(अचिन्हित दीर्घ))

काष्ठा netlink_sock अणु
	/* काष्ठा sock has to be the first member of netlink_sock */
	काष्ठा sock		sk;
	u32			portid;
	u32			dst_portid;
	u32			dst_group;
	u32			flags;
	u32			subscriptions;
	u32			ngroups;
	अचिन्हित दीर्घ		*groups;
	अचिन्हित दीर्घ		state;
	माप_प्रकार			max_recvmsg_len;
	रुको_queue_head_t	रुको;
	bool			bound;
	bool			cb_running;
	पूर्णांक			dump_करोne_त्रुटि_सं;
	काष्ठा netlink_callback	cb;
	काष्ठा mutex		*cb_mutex;
	काष्ठा mutex		cb_def_mutex;
	व्योम			(*netlink_rcv)(काष्ठा sk_buff *skb);
	पूर्णांक			(*netlink_bind)(काष्ठा net *net, पूर्णांक group);
	व्योम			(*netlink_unbind)(काष्ठा net *net, पूर्णांक group);
	काष्ठा module		*module;

	काष्ठा rhash_head	node;
	काष्ठा rcu_head		rcu;
	काष्ठा work_काष्ठा	work;
पूर्ण;

अटल अंतरभूत काष्ठा netlink_sock *nlk_sk(काष्ठा sock *sk)
अणु
	वापस container_of(sk, काष्ठा netlink_sock, sk);
पूर्ण

काष्ठा netlink_table अणु
	काष्ठा rhashtable	hash;
	काष्ठा hlist_head	mc_list;
	काष्ठा listeners __rcu	*listeners;
	अचिन्हित पूर्णांक		flags;
	अचिन्हित पूर्णांक		groups;
	काष्ठा mutex		*cb_mutex;
	काष्ठा module		*module;
	पूर्णांक			(*bind)(काष्ठा net *net, पूर्णांक group);
	व्योम			(*unbind)(काष्ठा net *net, पूर्णांक group);
	bool			(*compare)(काष्ठा net *net, काष्ठा sock *sock);
	पूर्णांक			रेजिस्टरed;
पूर्ण;

बाह्य काष्ठा netlink_table *nl_table;
बाह्य rwlock_t nl_table_lock;

#पूर्ण_अगर
