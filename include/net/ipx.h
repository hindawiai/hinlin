<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_INET_IPX_H_
#घोषणा _NET_INET_IPX_H_
/*
 *	The following inक्रमmation is in its entirety obtained from:
 *
 *	Novell 'IPX Router Specification' Version 1.10 
 *		Part No. 107-000029-001
 *
 *	Which is available from ftp.novell.com
 */

#समावेश <linux/netdevice.h>
#समावेश <net/datalink.h>
#समावेश <linux/ipx.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/refcount.h>

काष्ठा ipx_address अणु
	__be32  net;
	__u8    node[IPX_NODE_LEN]; 
	__be16  sock;
पूर्ण;

#घोषणा ipx_broadcast_node	"\377\377\377\377\377\377"
#घोषणा ipx_this_node           "\0\0\0\0\0\0"

#घोषणा IPX_MAX_PPROP_HOPS 8

काष्ठा ipxhdr अणु
	__be16			ipx_checksum __packed;
#घोषणा IPX_NO_CHECKSUM	cpu_to_be16(0xFFFF)
	__be16			ipx_pktsize __packed;
	__u8			ipx_tctrl;
	__u8			ipx_type;
#घोषणा IPX_TYPE_UNKNOWN	0x00
#घोषणा IPX_TYPE_RIP		0x01	/* may also be 0 */
#घोषणा IPX_TYPE_SAP		0x04	/* may also be 0 */
#घोषणा IPX_TYPE_SPX		0x05	/* SPX protocol */
#घोषणा IPX_TYPE_NCP		0x11	/* $lots क्रम करोcs on this (SPIT) */
#घोषणा IPX_TYPE_PPROP		0x14	/* complicated flood fill brdcast */
	काष्ठा ipx_address	ipx_dest __packed;
	काष्ठा ipx_address	ipx_source __packed;
पूर्ण;

/* From af_ipx.c */
बाह्य पूर्णांक sysctl_ipx_pprop_broadcasting;

काष्ठा ipx_पूर्णांकerface अणु
	/* IPX address */
	__be32			अगर_netnum;
	अचिन्हित अक्षर		अगर_node[IPX_NODE_LEN];
	refcount_t		refcnt;

	/* physical device info */
	काष्ठा net_device	*अगर_dev;
	काष्ठा datalink_proto	*अगर_dlink;
	__be16			अगर_dlink_type;

	/* socket support */
	अचिन्हित लघु		अगर_sknum;
	काष्ठा hlist_head	अगर_sklist;
	spinlock_t		अगर_sklist_lock;

	/* administrative overhead */
	पूर्णांक			अगर_ipx_offset;
	अचिन्हित अक्षर		अगर_पूर्णांकernal;
	अचिन्हित अक्षर		अगर_primary;
	
	काष्ठा list_head	node; /* node in ipx_पूर्णांकerfaces list */
पूर्ण;

काष्ठा ipx_route अणु
	__be32			ir_net;
	काष्ठा ipx_पूर्णांकerface	*ir_पूर्णांकrfc;
	अचिन्हित अक्षर		ir_routed;
	अचिन्हित अक्षर		ir_router_node[IPX_NODE_LEN];
	काष्ठा list_head	node; /* node in ipx_routes list */
	refcount_t		refcnt;
पूर्ण;

काष्ठा ipx_cb अणु
	u8	ipx_tctrl;
	__be32	ipx_dest_net;
	__be32	ipx_source_net;
	काष्ठा अणु
		__be32 netnum;
		पूर्णांक index;
	पूर्ण last_hop;
पूर्ण;

#समावेश <net/sock.h>

काष्ठा ipx_sock अणु
	/* काष्ठा sock has to be the first member of ipx_sock */
	काष्ठा sock		sk;
	काष्ठा ipx_address	dest_addr;
	काष्ठा ipx_पूर्णांकerface	*पूर्णांकrfc;
	__be16			port;
#अगर_घोषित CONFIG_IPX_INTERN
	अचिन्हित अक्षर		node[IPX_NODE_LEN];
#पूर्ण_अगर
	अचिन्हित लघु		type;
	/*
	 * To handle special ncp connection-handling sockets क्रम mars_nwe,
 	 * the connection number must be stored in the socket.
	 */
	अचिन्हित लघु		ipx_ncp_conn;
पूर्ण;

अटल अंतरभूत काष्ठा ipx_sock *ipx_sk(काष्ठा sock *sk)
अणु
	वापस (काष्ठा ipx_sock *)sk;
पूर्ण

#घोषणा IPX_SKB_CB(__skb) ((काष्ठा ipx_cb *)&((__skb)->cb[0]))

#घोषणा IPX_MIN_EPHEMERAL_SOCKET	0x4000
#घोषणा IPX_MAX_EPHEMERAL_SOCKET	0x7fff

बाह्य काष्ठा list_head ipx_routes;
बाह्य rwlock_t ipx_routes_lock;

बाह्य काष्ठा list_head ipx_पूर्णांकerfaces;
काष्ठा ipx_पूर्णांकerface *ipx_पूर्णांकerfaces_head(व्योम);
बाह्य spinlock_t ipx_पूर्णांकerfaces_lock;

बाह्य काष्ठा ipx_पूर्णांकerface *ipx_primary_net;

पूर्णांक ipx_proc_init(व्योम);
व्योम ipx_proc_निकास(व्योम);

स्थिर अक्षर *ipx_frame_name(__be16);
स्थिर अक्षर *ipx_device_name(काष्ठा ipx_पूर्णांकerface *पूर्णांकrfc);

अटल __अंतरभूत__ व्योम ipxitf_hold(काष्ठा ipx_पूर्णांकerface *पूर्णांकrfc)
अणु
	refcount_inc(&पूर्णांकrfc->refcnt);
पूर्ण

व्योम ipxitf_करोwn(काष्ठा ipx_पूर्णांकerface *पूर्णांकrfc);
काष्ठा ipx_पूर्णांकerface *ipxitf_find_using_net(__be32 net);
पूर्णांक ipxitf_send(काष्ठा ipx_पूर्णांकerface *पूर्णांकrfc, काष्ठा sk_buff *skb, अक्षर *node);
__be16 ipx_cksum(काष्ठा ipxhdr *packet, पूर्णांक length);
पूर्णांक ipxrtr_add_route(__be32 network, काष्ठा ipx_पूर्णांकerface *पूर्णांकrfc,
		     अचिन्हित अक्षर *node);
व्योम ipxrtr_del_routes(काष्ठा ipx_पूर्णांकerface *पूर्णांकrfc);
पूर्णांक ipxrtr_route_packet(काष्ठा sock *sk, काष्ठा sockaddr_ipx *usipx,
			काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक noblock);
पूर्णांक ipxrtr_route_skb(काष्ठा sk_buff *skb);
काष्ठा ipx_route *ipxrtr_lookup(__be32 net);
पूर्णांक ipxrtr_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *arg);

अटल __अंतरभूत__ व्योम ipxitf_put(काष्ठा ipx_पूर्णांकerface *पूर्णांकrfc)
अणु
	अगर (refcount_dec_and_test(&पूर्णांकrfc->refcnt))
		ipxitf_करोwn(पूर्णांकrfc);
पूर्ण

अटल __अंतरभूत__ व्योम ipxrtr_hold(काष्ठा ipx_route *rt)
अणु
	        refcount_inc(&rt->refcnt);
पूर्ण

अटल __अंतरभूत__ व्योम ipxrtr_put(काष्ठा ipx_route *rt)
अणु
	        अगर (refcount_dec_and_test(&rt->refcnt))
			                kमुक्त(rt);
पूर्ण
#पूर्ण_अगर /* _NET_INET_IPX_H_ */
