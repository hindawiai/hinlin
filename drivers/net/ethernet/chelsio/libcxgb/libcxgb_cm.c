<शैली गुरु>
/*
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/tcp.h>
#समावेश <linux/ipv6.h>
#समावेश <net/route.h>
#समावेश <net/ip6_route.h>

#समावेश "libcxgb_cm.h"

व्योम
cxgb_get_4tuple(काष्ठा cpl_pass_accept_req *req, क्रमागत chip_type type,
		पूर्णांक *iptype, __u8 *local_ip, __u8 *peer_ip,
		__be16 *local_port, __be16 *peer_port)
अणु
	पूर्णांक eth_len = (CHELSIO_CHIP_VERSION(type) <= CHELSIO_T5) ?
		      ETH_HDR_LEN_G(be32_to_cpu(req->hdr_len)) :
		      T6_ETH_HDR_LEN_G(be32_to_cpu(req->hdr_len));
	पूर्णांक ip_len = (CHELSIO_CHIP_VERSION(type) <= CHELSIO_T5) ?
		     IP_HDR_LEN_G(be32_to_cpu(req->hdr_len)) :
		     T6_IP_HDR_LEN_G(be32_to_cpu(req->hdr_len));
	काष्ठा iphdr *ip = (काष्ठा iphdr *)((u8 *)(req + 1) + eth_len);
	काष्ठा ipv6hdr *ip6 = (काष्ठा ipv6hdr *)((u8 *)(req + 1) + eth_len);
	काष्ठा tcphdr *tcp = (काष्ठा tcphdr *)
			     ((u8 *)(req + 1) + eth_len + ip_len);

	अगर (ip->version == 4) अणु
		pr_debug("%s saddr 0x%x daddr 0x%x sport %u dport %u\n",
			 __func__, ntohl(ip->saddr), ntohl(ip->daddr),
			 ntohs(tcp->source), ntohs(tcp->dest));
		*iptype = 4;
		स_नकल(peer_ip, &ip->saddr, 4);
		स_नकल(local_ip, &ip->daddr, 4);
	पूर्ण अन्यथा अणु
		pr_debug("%s saddr %pI6 daddr %pI6 sport %u dport %u\n",
			 __func__, ip6->saddr.s6_addr, ip6->daddr.s6_addr,
			 ntohs(tcp->source), ntohs(tcp->dest));
		*iptype = 6;
		स_नकल(peer_ip, ip6->saddr.s6_addr, 16);
		स_नकल(local_ip, ip6->daddr.s6_addr, 16);
	पूर्ण
	*peer_port = tcp->source;
	*local_port = tcp->dest;
पूर्ण
EXPORT_SYMBOL(cxgb_get_4tuple);

अटल bool
cxgb_our_पूर्णांकerface(काष्ठा cxgb4_lld_info *lldi,
		   काष्ठा net_device *(*get_real_dev)(काष्ठा net_device *),
		   काष्ठा net_device *egress_dev)
अणु
	पूर्णांक i;

	egress_dev = get_real_dev(egress_dev);
	क्रम (i = 0; i < lldi->nports; i++)
		अगर (lldi->ports[i] == egress_dev)
			वापस true;
	वापस false;
पूर्ण

काष्ठा dst_entry *
cxgb_find_route(काष्ठा cxgb4_lld_info *lldi,
		काष्ठा net_device *(*get_real_dev)(काष्ठा net_device *),
		__be32 local_ip, __be32 peer_ip, __be16 local_port,
		__be16 peer_port, u8 tos)
अणु
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;
	काष्ठा neighbour *n;

	rt = ip_route_output_ports(&init_net, &fl4, शून्य, peer_ip, local_ip,
				   peer_port, local_port, IPPROTO_TCP,
				   tos, 0);
	अगर (IS_ERR(rt))
		वापस शून्य;
	n = dst_neigh_lookup(&rt->dst, &peer_ip);
	अगर (!n)
		वापस शून्य;
	अगर (!cxgb_our_पूर्णांकerface(lldi, get_real_dev, n->dev) &&
	    !(n->dev->flags & IFF_LOOPBACK)) अणु
		neigh_release(n);
		dst_release(&rt->dst);
		वापस शून्य;
	पूर्ण
	neigh_release(n);
	वापस &rt->dst;
पूर्ण
EXPORT_SYMBOL(cxgb_find_route);

काष्ठा dst_entry *
cxgb_find_route6(काष्ठा cxgb4_lld_info *lldi,
		 काष्ठा net_device *(*get_real_dev)(काष्ठा net_device *),
		 __u8 *local_ip, __u8 *peer_ip, __be16 local_port,
		 __be16 peer_port, u8 tos, __u32 sin6_scope_id)
अणु
	काष्ठा dst_entry *dst = शून्य;

	अगर (IS_ENABLED(CONFIG_IPV6)) अणु
		काष्ठा flowi6 fl6;

		स_रखो(&fl6, 0, माप(fl6));
		स_नकल(&fl6.daddr, peer_ip, 16);
		स_नकल(&fl6.saddr, local_ip, 16);
		अगर (ipv6_addr_type(&fl6.daddr) & IPV6_ADDR_LINKLOCAL)
			fl6.flowi6_oअगर = sin6_scope_id;
		dst = ip6_route_output(&init_net, शून्य, &fl6);
		अगर (dst->error ||
		    (!cxgb_our_पूर्णांकerface(lldi, get_real_dev,
					 ip6_dst_idev(dst)->dev) &&
		     !(ip6_dst_idev(dst)->dev->flags & IFF_LOOPBACK))) अणु
			dst_release(dst);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस dst;
पूर्ण
EXPORT_SYMBOL(cxgb_find_route6);
