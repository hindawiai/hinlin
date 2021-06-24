<शैली गुरु>
/*
 * Copyright (c) 2005 Voltaire Inc.  All rights reserved.
 * Copyright (c) 2002-2005, Network Appliance, Inc. All rights reserved.
 * Copyright (c) 1999-2005, Mellanox Technologies, Inc. All rights reserved.
 * Copyright (c) 2005 Intel Corporation.  All rights reserved.
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
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
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

#समावेश <linux/mutex.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/module.h>
#समावेश <net/arp.h>
#समावेश <net/neighbour.h>
#समावेश <net/route.h>
#समावेश <net/netevent.h>
#समावेश <net/ipv6_stubs.h>
#समावेश <net/ip6_route.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_sa.h>
#समावेश <rdma/ib.h>
#समावेश <rdma/rdma_netlink.h>
#समावेश <net/netlink.h>

#समावेश "core_priv.h"

काष्ठा addr_req अणु
	काष्ठा list_head list;
	काष्ठा sockaddr_storage src_addr;
	काष्ठा sockaddr_storage dst_addr;
	काष्ठा rdma_dev_addr *addr;
	व्योम *context;
	व्योम (*callback)(पूर्णांक status, काष्ठा sockaddr *src_addr,
			 काष्ठा rdma_dev_addr *addr, व्योम *context);
	अचिन्हित दीर्घ समयout;
	काष्ठा delayed_work work;
	bool resolve_by_gid_attr;	/* Consider gid attr in resolve phase */
	पूर्णांक status;
	u32 seq;
पूर्ण;

अटल atomic_t ib_nl_addr_request_seq = ATOMIC_INIT(0);

अटल DEFINE_SPINLOCK(lock);
अटल LIST_HEAD(req_list);
अटल काष्ठा workqueue_काष्ठा *addr_wq;

अटल स्थिर काष्ठा nla_policy ib_nl_addr_policy[LS_NLA_TYPE_MAX] = अणु
	[LS_NLA_TYPE_DGID] = अणु.type = NLA_BINARY,
		.len = माप(काष्ठा rdma_nla_ls_gid),
		.validation_type = NLA_VALIDATE_MIN,
		.min = माप(काष्ठा rdma_nla_ls_gid)पूर्ण,
पूर्ण;

अटल अंतरभूत bool ib_nl_is_good_ip_resp(स्थिर काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा nlattr *tb[LS_NLA_TYPE_MAX] = अणुपूर्ण;
	पूर्णांक ret;

	अगर (nlh->nlmsg_flags & RDMA_NL_LS_F_ERR)
		वापस false;

	ret = nla_parse_deprecated(tb, LS_NLA_TYPE_MAX - 1, nlmsg_data(nlh),
				   nlmsg_len(nlh), ib_nl_addr_policy, शून्य);
	अगर (ret)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम ib_nl_process_good_ip_rsep(स्थिर काष्ठा nlmsghdr *nlh)
अणु
	स्थिर काष्ठा nlattr *head, *curr;
	जोड़ ib_gid gid;
	काष्ठा addr_req *req;
	पूर्णांक len, rem;
	पूर्णांक found = 0;

	head = (स्थिर काष्ठा nlattr *)nlmsg_data(nlh);
	len = nlmsg_len(nlh);

	nla_क्रम_each_attr(curr, head, len, rem) अणु
		अगर (curr->nla_type == LS_NLA_TYPE_DGID)
			स_नकल(&gid, nla_data(curr), nla_len(curr));
	पूर्ण

	spin_lock_bh(&lock);
	list_क्रम_each_entry(req, &req_list, list) अणु
		अगर (nlh->nlmsg_seq != req->seq)
			जारी;
		/* We set the DGID part, the rest was set earlier */
		rdma_addr_set_dgid(req->addr, &gid);
		req->status = 0;
		found = 1;
		अवरोध;
	पूर्ण
	spin_unlock_bh(&lock);

	अगर (!found)
		pr_info("Couldn't find request waiting for DGID: %pI6\n",
			&gid);
पूर्ण

पूर्णांक ib_nl_handle_ip_res_resp(काष्ठा sk_buff *skb,
			     काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	अगर ((nlh->nlmsg_flags & NLM_F_REQUEST) ||
	    !(NETLINK_CB(skb).sk))
		वापस -EPERM;

	अगर (ib_nl_is_good_ip_resp(nlh))
		ib_nl_process_good_ip_rsep(nlh);

	वापस 0;
पूर्ण

अटल पूर्णांक ib_nl_ip_send_msg(काष्ठा rdma_dev_addr *dev_addr,
			     स्थिर व्योम *daddr,
			     u32 seq, u16 family)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	काष्ठा rdma_ls_ip_resolve_header *header;
	व्योम *data;
	माप_प्रकार size;
	पूर्णांक attrtype;
	पूर्णांक len;

	अगर (family == AF_INET) अणु
		size = माप(काष्ठा in_addr);
		attrtype = RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_IPV4;
	पूर्ण अन्यथा अणु
		size = माप(काष्ठा in6_addr);
		attrtype = RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_IPV6;
	पूर्ण

	len = nla_total_size(माप(size));
	len += NLMSG_ALIGN(माप(*header));

	skb = nlmsg_new(len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	data = ibnl_put_msg(skb, &nlh, seq, 0, RDMA_NL_LS,
			    RDMA_NL_LS_OP_IP_RESOLVE, NLM_F_REQUEST);
	अगर (!data) अणु
		nlmsg_मुक्त(skb);
		वापस -ENODATA;
	पूर्ण

	/* Conकाष्ठा the family header first */
	header = skb_put(skb, NLMSG_ALIGN(माप(*header)));
	header->अगरindex = dev_addr->bound_dev_अगर;
	nla_put(skb, attrtype, size, daddr);

	/* Repair the nlmsg header length */
	nlmsg_end(skb, nlh);
	rdma_nl_multicast(&init_net, skb, RDMA_NL_GROUP_LS, GFP_KERNEL);

	/* Make the request retry, so when we get the response from userspace
	 * we will have something.
	 */
	वापस -ENODATA;
पूर्ण

पूर्णांक rdma_addr_size(स्थिर काष्ठा sockaddr *addr)
अणु
	चयन (addr->sa_family) अणु
	हाल AF_INET:
		वापस माप(काष्ठा sockaddr_in);
	हाल AF_INET6:
		वापस माप(काष्ठा sockaddr_in6);
	हाल AF_IB:
		वापस माप(काष्ठा sockaddr_ib);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rdma_addr_size);

पूर्णांक rdma_addr_size_in6(काष्ठा sockaddr_in6 *addr)
अणु
	पूर्णांक ret = rdma_addr_size((काष्ठा sockaddr *) addr);

	वापस ret <= माप(*addr) ? ret : 0;
पूर्ण
EXPORT_SYMBOL(rdma_addr_size_in6);

पूर्णांक rdma_addr_size_kss(काष्ठा __kernel_sockaddr_storage *addr)
अणु
	पूर्णांक ret = rdma_addr_size((काष्ठा sockaddr *) addr);

	वापस ret <= माप(*addr) ? ret : 0;
पूर्ण
EXPORT_SYMBOL(rdma_addr_size_kss);

/**
 * rdma_copy_src_l2_addr - Copy netdevice source addresses
 * @dev_addr:	Destination address poपूर्णांकer where to copy the addresses
 * @dev:	Netdevice whose source addresses to copy
 *
 * rdma_copy_src_l2_addr() copies source addresses from the specअगरied netdevice.
 * This includes unicast address, broadcast address, device type and
 * पूर्णांकerface index.
 */
व्योम rdma_copy_src_l2_addr(काष्ठा rdma_dev_addr *dev_addr,
			   स्थिर काष्ठा net_device *dev)
अणु
	dev_addr->dev_type = dev->type;
	स_नकल(dev_addr->src_dev_addr, dev->dev_addr, MAX_ADDR_LEN);
	स_नकल(dev_addr->broadcast, dev->broadcast, MAX_ADDR_LEN);
	dev_addr->bound_dev_अगर = dev->अगरindex;
पूर्ण
EXPORT_SYMBOL(rdma_copy_src_l2_addr);

अटल काष्ठा net_device *
rdma_find_ndev_क्रम_src_ip_rcu(काष्ठा net *net, स्थिर काष्ठा sockaddr *src_in)
अणु
	काष्ठा net_device *dev = शून्य;
	पूर्णांक ret = -EADDRNOTAVAIL;

	चयन (src_in->sa_family) अणु
	हाल AF_INET:
		dev = __ip_dev_find(net,
				    ((स्थिर काष्ठा sockaddr_in *)src_in)->sin_addr.s_addr,
				    false);
		अगर (dev)
			ret = 0;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		क्रम_each_netdev_rcu(net, dev) अणु
			अगर (ipv6_chk_addr(net,
					  &((स्थिर काष्ठा sockaddr_in6 *)src_in)->sin6_addr,
					  dev, 1)) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	वापस ret ? ERR_PTR(ret) : dev;
पूर्ण

पूर्णांक rdma_translate_ip(स्थिर काष्ठा sockaddr *addr,
		      काष्ठा rdma_dev_addr *dev_addr)
अणु
	काष्ठा net_device *dev;

	अगर (dev_addr->bound_dev_अगर) अणु
		dev = dev_get_by_index(dev_addr->net, dev_addr->bound_dev_अगर);
		अगर (!dev)
			वापस -ENODEV;
		rdma_copy_src_l2_addr(dev_addr, dev);
		dev_put(dev);
		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock();
	dev = rdma_find_ndev_क्रम_src_ip_rcu(dev_addr->net, addr);
	अगर (!IS_ERR(dev))
		rdma_copy_src_l2_addr(dev_addr, dev);
	rcu_पढ़ो_unlock();
	वापस PTR_ERR_OR_ZERO(dev);
पूर्ण
EXPORT_SYMBOL(rdma_translate_ip);

अटल व्योम set_समयout(काष्ठा addr_req *req, अचिन्हित दीर्घ समय)
अणु
	अचिन्हित दीर्घ delay;

	delay = समय - jअगरfies;
	अगर ((दीर्घ)delay < 0)
		delay = 0;

	mod_delayed_work(addr_wq, &req->work, delay);
पूर्ण

अटल व्योम queue_req(काष्ठा addr_req *req)
अणु
	spin_lock_bh(&lock);
	list_add_tail(&req->list, &req_list);
	set_समयout(req, req->समयout);
	spin_unlock_bh(&lock);
पूर्ण

अटल पूर्णांक ib_nl_fetch_ha(काष्ठा rdma_dev_addr *dev_addr,
			  स्थिर व्योम *daddr, u32 seq, u16 family)
अणु
	अगर (!rdma_nl_chk_listeners(RDMA_NL_GROUP_LS))
		वापस -EADDRNOTAVAIL;

	वापस ib_nl_ip_send_msg(dev_addr, daddr, seq, family);
पूर्ण

अटल पूर्णांक dst_fetch_ha(स्थिर काष्ठा dst_entry *dst,
			काष्ठा rdma_dev_addr *dev_addr,
			स्थिर व्योम *daddr)
अणु
	काष्ठा neighbour *n;
	पूर्णांक ret = 0;

	n = dst_neigh_lookup(dst, daddr);
	अगर (!n)
		वापस -ENODATA;

	अगर (!(n->nud_state & NUD_VALID)) अणु
		neigh_event_send(n, शून्य);
		ret = -ENODATA;
	पूर्ण अन्यथा अणु
		neigh_ha_snapshot(dev_addr->dst_dev_addr, n, dst->dev);
	पूर्ण

	neigh_release(n);

	वापस ret;
पूर्ण

अटल bool has_gateway(स्थिर काष्ठा dst_entry *dst, sa_family_t family)
अणु
	काष्ठा rtable *rt;
	काष्ठा rt6_info *rt6;

	अगर (family == AF_INET) अणु
		rt = container_of(dst, काष्ठा rtable, dst);
		वापस rt->rt_uses_gateway;
	पूर्ण

	rt6 = container_of(dst, काष्ठा rt6_info, dst);
	वापस rt6->rt6i_flags & RTF_GATEWAY;
पूर्ण

अटल पूर्णांक fetch_ha(स्थिर काष्ठा dst_entry *dst, काष्ठा rdma_dev_addr *dev_addr,
		    स्थिर काष्ठा sockaddr *dst_in, u32 seq)
अणु
	स्थिर काष्ठा sockaddr_in *dst_in4 =
		(स्थिर काष्ठा sockaddr_in *)dst_in;
	स्थिर काष्ठा sockaddr_in6 *dst_in6 =
		(स्थिर काष्ठा sockaddr_in6 *)dst_in;
	स्थिर व्योम *daddr = (dst_in->sa_family == AF_INET) ?
		(स्थिर व्योम *)&dst_in4->sin_addr.s_addr :
		(स्थिर व्योम *)&dst_in6->sin6_addr;
	sa_family_t family = dst_in->sa_family;

	might_sleep();

	/* If we have a gateway in IB mode then it must be an IB network */
	अगर (has_gateway(dst, family) && dev_addr->network == RDMA_NETWORK_IB)
		वापस ib_nl_fetch_ha(dev_addr, daddr, seq, family);
	अन्यथा
		वापस dst_fetch_ha(dst, dev_addr, daddr);
पूर्ण

अटल पूर्णांक addr4_resolve(काष्ठा sockaddr *src_sock,
			 स्थिर काष्ठा sockaddr *dst_sock,
			 काष्ठा rdma_dev_addr *addr,
			 काष्ठा rtable **prt)
अणु
	काष्ठा sockaddr_in *src_in = (काष्ठा sockaddr_in *)src_sock;
	स्थिर काष्ठा sockaddr_in *dst_in =
			(स्थिर काष्ठा sockaddr_in *)dst_sock;

	__be32 src_ip = src_in->sin_addr.s_addr;
	__be32 dst_ip = dst_in->sin_addr.s_addr;
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;
	पूर्णांक ret;

	स_रखो(&fl4, 0, माप(fl4));
	fl4.daddr = dst_ip;
	fl4.saddr = src_ip;
	fl4.flowi4_oअगर = addr->bound_dev_अगर;
	rt = ip_route_output_key(addr->net, &fl4);
	ret = PTR_ERR_OR_ZERO(rt);
	अगर (ret)
		वापस ret;

	src_in->sin_addr.s_addr = fl4.saddr;

	addr->hoplimit = ip4_dst_hoplimit(&rt->dst);

	*prt = rt;
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक addr6_resolve(काष्ठा sockaddr *src_sock,
			 स्थिर काष्ठा sockaddr *dst_sock,
			 काष्ठा rdma_dev_addr *addr,
			 काष्ठा dst_entry **pdst)
अणु
	काष्ठा sockaddr_in6 *src_in = (काष्ठा sockaddr_in6 *)src_sock;
	स्थिर काष्ठा sockaddr_in6 *dst_in =
				(स्थिर काष्ठा sockaddr_in6 *)dst_sock;
	काष्ठा flowi6 fl6;
	काष्ठा dst_entry *dst;

	स_रखो(&fl6, 0, माप fl6);
	fl6.daddr = dst_in->sin6_addr;
	fl6.saddr = src_in->sin6_addr;
	fl6.flowi6_oअगर = addr->bound_dev_अगर;

	dst = ipv6_stub->ipv6_dst_lookup_flow(addr->net, शून्य, &fl6, शून्य);
	अगर (IS_ERR(dst))
		वापस PTR_ERR(dst);

	अगर (ipv6_addr_any(&src_in->sin6_addr))
		src_in->sin6_addr = fl6.saddr;

	addr->hoplimit = ip6_dst_hoplimit(dst);

	*pdst = dst;
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक addr6_resolve(काष्ठा sockaddr *src_sock,
			 स्थिर काष्ठा sockaddr *dst_sock,
			 काष्ठा rdma_dev_addr *addr,
			 काष्ठा dst_entry **pdst)
अणु
	वापस -EADDRNOTAVAIL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक addr_resolve_neigh(स्थिर काष्ठा dst_entry *dst,
			      स्थिर काष्ठा sockaddr *dst_in,
			      काष्ठा rdma_dev_addr *addr,
			      अचिन्हित पूर्णांक ndev_flags,
			      u32 seq)
अणु
	पूर्णांक ret = 0;

	अगर (ndev_flags & IFF_LOOPBACK) अणु
		स_नकल(addr->dst_dev_addr, addr->src_dev_addr, MAX_ADDR_LEN);
	पूर्ण अन्यथा अणु
		अगर (!(ndev_flags & IFF_NOARP)) अणु
			/* If the device करोesn't करो ARP पूर्णांकernally */
			ret = fetch_ha(dst, addr, dst_in, seq);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक copy_src_l2_addr(काष्ठा rdma_dev_addr *dev_addr,
			    स्थिर काष्ठा sockaddr *dst_in,
			    स्थिर काष्ठा dst_entry *dst,
			    स्थिर काष्ठा net_device *ndev)
अणु
	पूर्णांक ret = 0;

	अगर (dst->dev->flags & IFF_LOOPBACK)
		ret = rdma_translate_ip(dst_in, dev_addr);
	अन्यथा
		rdma_copy_src_l2_addr(dev_addr, dst->dev);

	/*
	 * If there's a gateway and type of device not ARPHRD_INFINIBAND,
	 * we're definitely in RoCE v2 (as RoCE v1 isn't routable) set the
	 * network type accordingly.
	 */
	अगर (has_gateway(dst, dst_in->sa_family) &&
	    ndev->type != ARPHRD_INFINIBAND)
		dev_addr->network = dst_in->sa_family == AF_INET ?
						RDMA_NETWORK_IPV4 :
						RDMA_NETWORK_IPV6;
	अन्यथा
		dev_addr->network = RDMA_NETWORK_IB;

	वापस ret;
पूर्ण

अटल पूर्णांक rdma_set_src_addr_rcu(काष्ठा rdma_dev_addr *dev_addr,
				 अचिन्हित पूर्णांक *ndev_flags,
				 स्थिर काष्ठा sockaddr *dst_in,
				 स्थिर काष्ठा dst_entry *dst)
अणु
	काष्ठा net_device *ndev = READ_ONCE(dst->dev);

	*ndev_flags = ndev->flags;
	/* A physical device must be the RDMA device to use */
	अगर (ndev->flags & IFF_LOOPBACK) अणु
		/*
		 * RDMA (IB/RoCE, iWarp) करोesn't run on lo पूर्णांकerface or
		 * loopback IP address. So अगर route is resolved to loopback
		 * पूर्णांकerface, translate that to a real ndev based on non
		 * loopback IP address.
		 */
		ndev = rdma_find_ndev_क्रम_src_ip_rcu(dev_net(ndev), dst_in);
		अगर (IS_ERR(ndev))
			वापस -ENODEV;
	पूर्ण

	वापस copy_src_l2_addr(dev_addr, dst_in, dst, ndev);
पूर्ण

अटल पूर्णांक set_addr_netns_by_gid_rcu(काष्ठा rdma_dev_addr *addr)
अणु
	काष्ठा net_device *ndev;

	ndev = rdma_पढ़ो_gid_attr_ndev_rcu(addr->sgid_attr);
	अगर (IS_ERR(ndev))
		वापस PTR_ERR(ndev);

	/*
	 * Since we are holding the rcu, पढ़ोing net and अगरindex
	 * are safe without any additional reference; because
	 * change_net_namespace() in net/core/dev.c करोes rcu sync
	 * after it changes the state to IFF_DOWN and beक्रमe
	 * updating netdev fields अणुnet, अगरindexपूर्ण.
	 */
	addr->net = dev_net(ndev);
	addr->bound_dev_अगर = ndev->अगरindex;
	वापस 0;
पूर्ण

अटल व्योम rdma_addr_set_net_शेषs(काष्ठा rdma_dev_addr *addr)
अणु
	addr->net = &init_net;
	addr->bound_dev_अगर = 0;
पूर्ण

अटल पूर्णांक addr_resolve(काष्ठा sockaddr *src_in,
			स्थिर काष्ठा sockaddr *dst_in,
			काष्ठा rdma_dev_addr *addr,
			bool resolve_neigh,
			bool resolve_by_gid_attr,
			u32 seq)
अणु
	काष्ठा dst_entry *dst = शून्य;
	अचिन्हित पूर्णांक ndev_flags = 0;
	काष्ठा rtable *rt = शून्य;
	पूर्णांक ret;

	अगर (!addr->net) अणु
		pr_warn_ratelimited("%s: missing namespace\n", __func__);
		वापस -EINVAL;
	पूर्ण

	rcu_पढ़ो_lock();
	अगर (resolve_by_gid_attr) अणु
		अगर (!addr->sgid_attr) अणु
			rcu_पढ़ो_unlock();
			pr_warn_ratelimited("%s: missing gid_attr\n", __func__);
			वापस -EINVAL;
		पूर्ण
		/*
		 * If the request is क्रम a specअगरic gid attribute of the
		 * rdma_dev_addr, derive net from the netdevice of the
		 * GID attribute.
		 */
		ret = set_addr_netns_by_gid_rcu(addr);
		अगर (ret) अणु
			rcu_पढ़ो_unlock();
			वापस ret;
		पूर्ण
	पूर्ण
	अगर (src_in->sa_family == AF_INET) अणु
		ret = addr4_resolve(src_in, dst_in, addr, &rt);
		dst = &rt->dst;
	पूर्ण अन्यथा अणु
		ret = addr6_resolve(src_in, dst_in, addr, &dst);
	पूर्ण
	अगर (ret) अणु
		rcu_पढ़ो_unlock();
		जाओ करोne;
	पूर्ण
	ret = rdma_set_src_addr_rcu(addr, &ndev_flags, dst_in, dst);
	rcu_पढ़ो_unlock();

	/*
	 * Resolve neighbor destination address अगर requested and
	 * only अगर src addr translation didn't fail.
	 */
	अगर (!ret && resolve_neigh)
		ret = addr_resolve_neigh(dst, dst_in, addr, ndev_flags, seq);

	अगर (src_in->sa_family == AF_INET)
		ip_rt_put(rt);
	अन्यथा
		dst_release(dst);
करोne:
	/*
	 * Clear the addr net to go back to its original state, only अगर it was
	 * derived from GID attribute in this context.
	 */
	अगर (resolve_by_gid_attr)
		rdma_addr_set_net_शेषs(addr);
	वापस ret;
पूर्ण

अटल व्योम process_one_req(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा addr_req *req;
	काष्ठा sockaddr *src_in, *dst_in;

	req = container_of(_work, काष्ठा addr_req, work.work);

	अगर (req->status == -ENODATA) अणु
		src_in = (काष्ठा sockaddr *)&req->src_addr;
		dst_in = (काष्ठा sockaddr *)&req->dst_addr;
		req->status = addr_resolve(src_in, dst_in, req->addr,
					   true, req->resolve_by_gid_attr,
					   req->seq);
		अगर (req->status && समय_after_eq(jअगरfies, req->समयout)) अणु
			req->status = -ETIMEDOUT;
		पूर्ण अन्यथा अगर (req->status == -ENODATA) अणु
			/* requeue the work क्रम retrying again */
			spin_lock_bh(&lock);
			अगर (!list_empty(&req->list))
				set_समयout(req, req->समयout);
			spin_unlock_bh(&lock);
			वापस;
		पूर्ण
	पूर्ण

	req->callback(req->status, (काष्ठा sockaddr *)&req->src_addr,
		req->addr, req->context);
	req->callback = शून्य;

	spin_lock_bh(&lock);
	/*
	 * Although the work will normally have been canceled by the workqueue,
	 * it can still be requeued as दीर्घ as it is on the req_list.
	 */
	cancel_delayed_work(&req->work);
	अगर (!list_empty(&req->list)) अणु
		list_del_init(&req->list);
		kमुक्त(req);
	पूर्ण
	spin_unlock_bh(&lock);
पूर्ण

पूर्णांक rdma_resolve_ip(काष्ठा sockaddr *src_addr, स्थिर काष्ठा sockaddr *dst_addr,
		    काष्ठा rdma_dev_addr *addr, अचिन्हित दीर्घ समयout_ms,
		    व्योम (*callback)(पूर्णांक status, काष्ठा sockaddr *src_addr,
				     काष्ठा rdma_dev_addr *addr, व्योम *context),
		    bool resolve_by_gid_attr, व्योम *context)
अणु
	काष्ठा sockaddr *src_in, *dst_in;
	काष्ठा addr_req *req;
	पूर्णांक ret = 0;

	req = kzalloc(माप *req, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	src_in = (काष्ठा sockaddr *) &req->src_addr;
	dst_in = (काष्ठा sockaddr *) &req->dst_addr;

	अगर (src_addr) अणु
		अगर (src_addr->sa_family != dst_addr->sa_family) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		स_नकल(src_in, src_addr, rdma_addr_size(src_addr));
	पूर्ण अन्यथा अणु
		src_in->sa_family = dst_addr->sa_family;
	पूर्ण

	स_नकल(dst_in, dst_addr, rdma_addr_size(dst_addr));
	req->addr = addr;
	req->callback = callback;
	req->context = context;
	req->resolve_by_gid_attr = resolve_by_gid_attr;
	INIT_DELAYED_WORK(&req->work, process_one_req);
	req->seq = (u32)atomic_inc_वापस(&ib_nl_addr_request_seq);

	req->status = addr_resolve(src_in, dst_in, addr, true,
				   req->resolve_by_gid_attr, req->seq);
	चयन (req->status) अणु
	हाल 0:
		req->समयout = jअगरfies;
		queue_req(req);
		अवरोध;
	हाल -ENODATA:
		req->समयout = msecs_to_jअगरfies(समयout_ms) + jअगरfies;
		queue_req(req);
		अवरोध;
	शेष:
		ret = req->status;
		जाओ err;
	पूर्ण
	वापस ret;
err:
	kमुक्त(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_resolve_ip);

पूर्णांक roce_resolve_route_from_path(काष्ठा sa_path_rec *rec,
				 स्थिर काष्ठा ib_gid_attr *attr)
अणु
	जोड़ अणु
		काष्ठा sockaddr     _sockaddr;
		काष्ठा sockaddr_in  _sockaddr_in;
		काष्ठा sockaddr_in6 _sockaddr_in6;
	पूर्ण sgid, dgid;
	काष्ठा rdma_dev_addr dev_addr = अणुपूर्ण;
	पूर्णांक ret;

	might_sleep();

	अगर (rec->roce.route_resolved)
		वापस 0;

	rdma_gid2ip((काष्ठा sockaddr *)&sgid, &rec->sgid);
	rdma_gid2ip((काष्ठा sockaddr *)&dgid, &rec->dgid);

	अगर (sgid._sockaddr.sa_family != dgid._sockaddr.sa_family)
		वापस -EINVAL;

	अगर (!attr || !attr->ndev)
		वापस -EINVAL;

	dev_addr.net = &init_net;
	dev_addr.sgid_attr = attr;

	ret = addr_resolve((काष्ठा sockaddr *)&sgid, (काष्ठा sockaddr *)&dgid,
			   &dev_addr, false, true, 0);
	अगर (ret)
		वापस ret;

	अगर ((dev_addr.network == RDMA_NETWORK_IPV4 ||
	     dev_addr.network == RDMA_NETWORK_IPV6) &&
	    rec->rec_type != SA_PATH_REC_TYPE_ROCE_V2)
		वापस -EINVAL;

	rec->roce.route_resolved = true;
	वापस 0;
पूर्ण

/**
 * rdma_addr_cancel - Cancel resolve ip request
 * @addr:	Poपूर्णांकer to address काष्ठाure given previously
 *		during rdma_resolve_ip().
 * rdma_addr_cancel() is synchronous function which cancels any pending
 * request अगर there is any.
 */
व्योम rdma_addr_cancel(काष्ठा rdma_dev_addr *addr)
अणु
	काष्ठा addr_req *req, *temp_req;
	काष्ठा addr_req *found = शून्य;

	spin_lock_bh(&lock);
	list_क्रम_each_entry_safe(req, temp_req, &req_list, list) अणु
		अगर (req->addr == addr) अणु
			/*
			 * Removing from the list means we take ownership of
			 * the req
			 */
			list_del_init(&req->list);
			found = req;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&lock);

	अगर (!found)
		वापस;

	/*
	 * sync canceling the work after removing it from the req_list
	 * guarentees no work is running and none will be started.
	 */
	cancel_delayed_work_sync(&found->work);
	kमुक्त(found);
पूर्ण
EXPORT_SYMBOL(rdma_addr_cancel);

काष्ठा resolve_cb_context अणु
	काष्ठा completion comp;
	पूर्णांक status;
पूर्ण;

अटल व्योम resolve_cb(पूर्णांक status, काष्ठा sockaddr *src_addr,
	     काष्ठा rdma_dev_addr *addr, व्योम *context)
अणु
	((काष्ठा resolve_cb_context *)context)->status = status;
	complete(&((काष्ठा resolve_cb_context *)context)->comp);
पूर्ण

पूर्णांक rdma_addr_find_l2_eth_by_grh(स्थिर जोड़ ib_gid *sgid,
				 स्थिर जोड़ ib_gid *dgid,
				 u8 *dmac, स्थिर काष्ठा ib_gid_attr *sgid_attr,
				 पूर्णांक *hoplimit)
अणु
	काष्ठा rdma_dev_addr dev_addr;
	काष्ठा resolve_cb_context ctx;
	जोड़ अणु
		काष्ठा sockaddr_in  _sockaddr_in;
		काष्ठा sockaddr_in6 _sockaddr_in6;
	पूर्ण sgid_addr, dgid_addr;
	पूर्णांक ret;

	rdma_gid2ip((काष्ठा sockaddr *)&sgid_addr, sgid);
	rdma_gid2ip((काष्ठा sockaddr *)&dgid_addr, dgid);

	स_रखो(&dev_addr, 0, माप(dev_addr));
	dev_addr.net = &init_net;
	dev_addr.sgid_attr = sgid_attr;

	init_completion(&ctx.comp);
	ret = rdma_resolve_ip((काष्ठा sockaddr *)&sgid_addr,
			      (काष्ठा sockaddr *)&dgid_addr, &dev_addr, 1000,
			      resolve_cb, true, &ctx);
	अगर (ret)
		वापस ret;

	रुको_क्रम_completion(&ctx.comp);

	ret = ctx.status;
	अगर (ret)
		वापस ret;

	स_नकल(dmac, dev_addr.dst_dev_addr, ETH_ALEN);
	*hoplimit = dev_addr.hoplimit;
	वापस 0;
पूर्ण

अटल पूर्णांक netevent_callback(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ event,
	व्योम *ctx)
अणु
	काष्ठा addr_req *req;

	अगर (event == NETEVENT_NEIGH_UPDATE) अणु
		काष्ठा neighbour *neigh = ctx;

		अगर (neigh->nud_state & NUD_VALID) अणु
			spin_lock_bh(&lock);
			list_क्रम_each_entry(req, &req_list, list)
				set_समयout(req, jअगरfies);
			spin_unlock_bh(&lock);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block nb = अणु
	.notअगरier_call = netevent_callback
पूर्ण;

पूर्णांक addr_init(व्योम)
अणु
	addr_wq = alloc_ordered_workqueue("ib_addr", 0);
	अगर (!addr_wq)
		वापस -ENOMEM;

	रेजिस्टर_netevent_notअगरier(&nb);

	वापस 0;
पूर्ण

व्योम addr_cleanup(व्योम)
अणु
	unरेजिस्टर_netevent_notअगरier(&nb);
	destroy_workqueue(addr_wq);
	WARN_ON(!list_empty(&req_list));
पूर्ण
