<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_ATALK_H__
#घोषणा __LINUX_ATALK_H__


#समावेश <net/sock.h>
#समावेश <uapi/linux/atalk.h>

काष्ठा atalk_route अणु
	काष्ठा net_device  *dev;
	काष्ठा atalk_addr  target;
	काष्ठा atalk_addr  gateway;
	पूर्णांक		   flags;
	काष्ठा atalk_route *next;
पूर्ण;

/**
 *	काष्ठा atalk_अगरace - AppleTalk Interface
 *	@dev - Network device associated with this पूर्णांकerface
 *	@address - Our address
 *	@status - What are we करोing?
 *	@nets - Associated direct netrange
 *	@next - next element in the list of पूर्णांकerfaces
 */
काष्ठा atalk_अगरace अणु
	काष्ठा net_device	*dev;
	काष्ठा atalk_addr	address;
	पूर्णांक			status;
#घोषणा ATIF_PROBE	1		/* Probing क्रम an address */
#घोषणा ATIF_PROBE_FAIL	2		/* Probe collided */
	काष्ठा atalk_netrange	nets;
	काष्ठा atalk_अगरace	*next;
पूर्ण;
	
काष्ठा atalk_sock अणु
	/* काष्ठा sock has to be the first member of atalk_sock */
	काष्ठा sock	sk;
	__be16		dest_net;
	__be16		src_net;
	अचिन्हित अक्षर	dest_node;
	अचिन्हित अक्षर	src_node;
	अचिन्हित अक्षर	dest_port;
	अचिन्हित अक्षर	src_port;
पूर्ण;

अटल अंतरभूत काष्ठा atalk_sock *at_sk(काष्ठा sock *sk)
अणु
	वापस (काष्ठा atalk_sock *)sk;
पूर्ण

काष्ठा ddpehdr अणु
	__be16	deh_len_hops;	/* lower 10 bits are length, next 4 - hops */
	__be16	deh_sum;
	__be16	deh_dnet;
	__be16	deh_snet;
	__u8	deh_dnode;
	__u8	deh_snode;
	__u8	deh_dport;
	__u8	deh_sport;
	/* And netatalk apps expect to stick the type in themselves */
पूर्ण;

अटल __अंतरभूत__ काष्ठा ddpehdr *ddp_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ddpehdr *)skb_transport_header(skb);
पूर्ण

/* AppleTalk AARP headers */
काष्ठा elapaarp अणु
	__be16	hw_type;
#घोषणा AARP_HW_TYPE_ETHERNET		1
#घोषणा AARP_HW_TYPE_TOKENRING		2
	__be16	pa_type;
	__u8	hw_len;
	__u8	pa_len;
#घोषणा AARP_PA_ALEN			4
	__be16	function;
#घोषणा AARP_REQUEST			1
#घोषणा AARP_REPLY			2
#घोषणा AARP_PROBE			3
	__u8	hw_src[ETH_ALEN];
	__u8	pa_src_zero;
	__be16	pa_src_net;
	__u8	pa_src_node;
	__u8	hw_dst[ETH_ALEN];
	__u8	pa_dst_zero;
	__be16	pa_dst_net;
	__u8	pa_dst_node;
पूर्ण __attribute__ ((packed));

अटल __अंतरभूत__ काष्ठा elapaarp *aarp_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा elapaarp *)skb_transport_header(skb);
पूर्ण

/* Not specअगरied - how दीर्घ till we drop a resolved entry */
#घोषणा AARP_EXPIRY_TIME	(5 * 60 * HZ)
/* Size of hash table */
#घोषणा AARP_HASH_SIZE		16
/* Fast retransmission समयr when resolving */
#घोषणा AARP_TICK_TIME		(HZ / 5)
/* Send 10 requests then give up (2 seconds) */
#घोषणा AARP_RETRANSMIT_LIMIT	10
/*
 * Some value bigger than total retransmit समय + a bit क्रम last reply to
 * appear and to stop continual requests
 */
#घोषणा AARP_RESOLVE_TIME	(10 * HZ)

बाह्य काष्ठा datalink_proto *ddp_dl, *aarp_dl;
बाह्य पूर्णांक aarp_proto_init(व्योम);

/* Inter module exports */

/* Give a device find its atअगर control काष्ठाure */
#अगर IS_ENABLED(CONFIG_IRDA) || IS_ENABLED(CONFIG_ATALK)
अटल अंतरभूत काष्ठा atalk_अगरace *atalk_find_dev(काष्ठा net_device *dev)
अणु
	वापस dev->atalk_ptr;
पूर्ण
#पूर्ण_अगर

बाह्य काष्ठा atalk_addr *atalk_find_dev_addr(काष्ठा net_device *dev);
बाह्य काष्ठा net_device *atrtr_get_dev(काष्ठा atalk_addr *sa);
बाह्य पूर्णांक		 aarp_send_ddp(काष्ठा net_device *dev,
				       काष्ठा sk_buff *skb,
				       काष्ठा atalk_addr *sa, व्योम *hwaddr);
बाह्य व्योम		 aarp_device_करोwn(काष्ठा net_device *dev);
बाह्य व्योम		 aarp_probe_network(काष्ठा atalk_अगरace *atअगर);
बाह्य पूर्णांक 		 aarp_proxy_probe_network(काष्ठा atalk_अगरace *atअगर,
				     काष्ठा atalk_addr *sa);
बाह्य व्योम		 aarp_proxy_हटाओ(काष्ठा net_device *dev,
					   काष्ठा atalk_addr *sa);

बाह्य व्योम		aarp_cleanup_module(व्योम);

बाह्य काष्ठा hlist_head atalk_sockets;
बाह्य rwlock_t atalk_sockets_lock;

बाह्य काष्ठा atalk_route *atalk_routes;
बाह्य rwlock_t atalk_routes_lock;

बाह्य काष्ठा atalk_अगरace *atalk_पूर्णांकerfaces;
बाह्य rwlock_t atalk_पूर्णांकerfaces_lock;

बाह्य काष्ठा atalk_route atrtr_शेष;

काष्ठा aarp_iter_state अणु
	पूर्णांक bucket;
	काष्ठा aarp_entry **table;
पूर्ण;

बाह्य स्थिर काष्ठा seq_operations aarp_seq_ops;

बाह्य पूर्णांक sysctl_aarp_expiry_समय;
बाह्य पूर्णांक sysctl_aarp_tick_समय;
बाह्य पूर्णांक sysctl_aarp_retransmit_limit;
बाह्य पूर्णांक sysctl_aarp_resolve_समय;

#अगर_घोषित CONFIG_SYSCTL
बाह्य पूर्णांक atalk_रेजिस्टर_sysctl(व्योम);
बाह्य व्योम atalk_unरेजिस्टर_sysctl(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक atalk_रेजिस्टर_sysctl(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम atalk_unरेजिस्टर_sysctl(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
बाह्य पूर्णांक atalk_proc_init(व्योम);
बाह्य व्योम atalk_proc_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक atalk_proc_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम atalk_proc_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

#पूर्ण_अगर /* __LINUX_ATALK_H__ */
