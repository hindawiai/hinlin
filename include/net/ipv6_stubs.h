<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IPV6_STUBS_H
#घोषणा _IPV6_STUBS_H

#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/neighbour.h>
#समावेश <net/sock.h>

/* काष्ठाs from net/ip6_fib.h */
काष्ठा fib6_info;
काष्ठा fib6_nh;
काष्ठा fib6_config;
काष्ठा fib6_result;

/* This is ugly, ideally these symbols should be built
 * पूर्णांकo the core kernel.
 */
काष्ठा ipv6_stub अणु
	पूर्णांक (*ipv6_sock_mc_join)(काष्ठा sock *sk, पूर्णांक अगरindex,
				 स्थिर काष्ठा in6_addr *addr);
	पूर्णांक (*ipv6_sock_mc_drop)(काष्ठा sock *sk, पूर्णांक अगरindex,
				 स्थिर काष्ठा in6_addr *addr);
	काष्ठा dst_entry *(*ipv6_dst_lookup_flow)(काष्ठा net *net,
						  स्थिर काष्ठा sock *sk,
						  काष्ठा flowi6 *fl6,
						  स्थिर काष्ठा in6_addr *final_dst);
	पूर्णांक (*ipv6_route_input)(काष्ठा sk_buff *skb);

	काष्ठा fib6_table *(*fib6_get_table)(काष्ठा net *net, u32 id);
	पूर्णांक (*fib6_lookup)(काष्ठा net *net, पूर्णांक oअगर, काष्ठा flowi6 *fl6,
			   काष्ठा fib6_result *res, पूर्णांक flags);
	पूर्णांक (*fib6_table_lookup)(काष्ठा net *net, काष्ठा fib6_table *table,
				 पूर्णांक oअगर, काष्ठा flowi6 *fl6,
				 काष्ठा fib6_result *res, पूर्णांक flags);
	व्योम (*fib6_select_path)(स्थिर काष्ठा net *net, काष्ठा fib6_result *res,
				 काष्ठा flowi6 *fl6, पूर्णांक oअगर, bool oअगर_match,
				 स्थिर काष्ठा sk_buff *skb, पूर्णांक strict);
	u32 (*ip6_mtu_from_fib6)(स्थिर काष्ठा fib6_result *res,
				 स्थिर काष्ठा in6_addr *daddr,
				 स्थिर काष्ठा in6_addr *saddr);

	पूर्णांक (*fib6_nh_init)(काष्ठा net *net, काष्ठा fib6_nh *fib6_nh,
			    काष्ठा fib6_config *cfg, gfp_t gfp_flags,
			    काष्ठा netlink_ext_ack *extack);
	व्योम (*fib6_nh_release)(काष्ठा fib6_nh *fib6_nh);
	व्योम (*fib6_update_sernum)(काष्ठा net *net, काष्ठा fib6_info *rt);
	पूर्णांक (*ip6_del_rt)(काष्ठा net *net, काष्ठा fib6_info *rt, bool skip_notअगरy);
	व्योम (*fib6_rt_update)(काष्ठा net *net, काष्ठा fib6_info *rt,
			       काष्ठा nl_info *info);

	व्योम (*udpv6_encap_enable)(व्योम);
	व्योम (*ndisc_send_na)(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *daddr,
			      स्थिर काष्ठा in6_addr *solicited_addr,
			      bool router, bool solicited, bool override, bool inc_opt);
#अगर IS_ENABLED(CONFIG_XFRM)
	व्योम (*xfrm6_local_rxpmtu)(काष्ठा sk_buff *skb, u32 mtu);
	पूर्णांक (*xfrm6_udp_encap_rcv)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
	पूर्णांक (*xfrm6_rcv_encap)(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
			       पूर्णांक encap_type);
#पूर्ण_अगर
	काष्ठा neigh_table *nd_tbl;

	पूर्णांक (*ipv6_fragment)(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
			     पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *));
	काष्ठा net_device *(*ipv6_dev_find)(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
					    काष्ठा net_device *dev);
पूर्ण;
बाह्य स्थिर काष्ठा ipv6_stub *ipv6_stub __पढ़ो_mostly;

/* A stub used by bpf helpers. Similarly ugly as ipv6_stub */
काष्ठा ipv6_bpf_stub अणु
	पूर्णांक (*inet6_bind)(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len,
			  u32 flags);
	काष्ठा sock *(*udp6_lib_lookup)(काष्ठा net *net,
				     स्थिर काष्ठा in6_addr *saddr, __be16 sport,
				     स्थिर काष्ठा in6_addr *daddr, __be16 dport,
				     पूर्णांक dअगर, पूर्णांक sdअगर, काष्ठा udp_table *tbl,
				     काष्ठा sk_buff *skb);
पूर्ण;
बाह्य स्थिर काष्ठा ipv6_bpf_stub *ipv6_bpf_stub __पढ़ो_mostly;

#पूर्ण_अगर
