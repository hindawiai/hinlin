<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* linux/net/ipv4/arp.c
 *
 * Copyright (C) 1994 by Florian  La Roche
 *
 * This module implements the Address Resolution Protocol ARP (RFC 826),
 * which is used to convert IP addresses (or in the future maybe other
 * high-level addresses) पूर्णांकo a low-level hardware address (like an Ethernet
 * address).
 *
 * Fixes:
 *		Alan Cox	:	Removed the Ethernet assumptions in
 *					Florian's code
 *		Alan Cox	:	Fixed some small errors in the ARP
 *					logic
 *		Alan Cox	:	Allow >4K in /proc
 *		Alan Cox	:	Make ARP add its own protocol entry
 *		Ross Martin     :       Rewrote arp_rcv() and arp_get_info()
 *		Stephen Henson	:	Add AX25 support to arp_get_info()
 *		Alan Cox	:	Drop data when a device is करोwned.
 *		Alan Cox	:	Use init_समयr().
 *		Alan Cox	:	Double lock fixes.
 *		Martin Seine	:	Move the arphdr काष्ठाure
 *					to अगर_arp.h क्रम compatibility.
 *					with BSD based programs.
 *		Andrew Tridgell :       Added ARP neपंचांगask code and
 *					re-arranged proxy handling.
 *		Alan Cox	:	Changed to use notअगरiers.
 *		Niibe Yutaka	:	Reply क्रम this device or proxies only.
 *		Alan Cox	:	Don't proxy across hardware types!
 *		Jonathan Naylor :	Added support क्रम NET/ROM.
 *		Mike Shaver     :       RFC1122 checks.
 *		Jonathan Naylor :	Only lookup the hardware address क्रम
 *					the correct hardware type.
 *		Germano Caronni	:	Assorted subtle races.
 *		Craig Schlenter :	Don't modअगरy permanent entry
 *					during arp_rcv.
 *		Russ Nelson	:	Tidied up a few bits.
 *		Alexey Kuznetsov:	Major changes to caching and behaviour,
 *					eg पूर्णांकelligent arp probing and
 *					generation
 *					of host करोwn events.
 *		Alan Cox	:	Missing unlock in device events.
 *		Eckes		:	ARP ioctl control errors.
 *		Alexey Kuznetsov:	Arp मुक्त fix.
 *		Manuel Rodriguez:	Gratuitous ARP.
 *              Jonathan Layes  :       Added arpd support through kerneld
 *                                      message queue (960314)
 *		Mike Shaver	:	/proc/sys/net/ipv4/arp_* support
 *		Mike McLagan    :	Routing by source
 *		Stuart Cheshire	:	Metricom and grat arp fixes
 *					*** FOR 2.1 clean this up ***
 *		Lawrence V. Stefani: (08/12/96) Added FDDI support.
 *		Alan Cox	:	Took the AP1000 nasty FDDI hack and
 *					folded पूर्णांकo the मुख्यstream FDDI code.
 *					Ack spit, Linus how did you allow that
 *					one in...
 *		Jes Sorensen	:	Make FDDI work again in 2.1.x and
 *					clean up the APFDDI & gen. FDDI bits.
 *		Alexey Kuznetsov:	new arp state machine;
 *					now it is in net/core/neighbour.c.
 *		Krzysztof Halasa:	Added Frame Relay ARP support.
 *		Arnalकरो C. Melo :	convert /proc/net/arp to seq_file
 *		Shmulik Hen:		Split arp_send to arp_create and
 *					arp_xmit so पूर्णांकermediate drivers like
 *					bonding can change the skb beक्रमe
 *					sending (e.g. insert 8021q tag).
 *		Harald Welte	:	convert to make use of jenkins hash
 *		Jesper D. Brouer:       Proxy ARP PVLAN RFC 3069 support.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/capability.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/mm.h>
#समावेश <linux/inet.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/fddidevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/net.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर

#समावेश <net/net_namespace.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/route.h>
#समावेश <net/protocol.h>
#समावेश <net/tcp.h>
#समावेश <net/sock.h>
#समावेश <net/arp.h>
#समावेश <net/ax25.h>
#समावेश <net/netrom.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/ip_tunnels.h>

#समावेश <linux/uaccess.h>

#समावेश <linux/netfilter_arp.h>

/*
 *	Interface to generic neighbour cache.
 */
अटल u32 arp_hash(स्थिर व्योम *pkey, स्थिर काष्ठा net_device *dev, __u32 *hash_rnd);
अटल bool arp_key_eq(स्थिर काष्ठा neighbour *n, स्थिर व्योम *pkey);
अटल पूर्णांक arp_स्थिरructor(काष्ठा neighbour *neigh);
अटल व्योम arp_solicit(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb);
अटल व्योम arp_error_report(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb);
अटल व्योम parp_reकरो(काष्ठा sk_buff *skb);
अटल पूर्णांक arp_is_multicast(स्थिर व्योम *pkey);

अटल स्थिर काष्ठा neigh_ops arp_generic_ops = अणु
	.family =		AF_INET,
	.solicit =		arp_solicit,
	.error_report =		arp_error_report,
	.output =		neigh_resolve_output,
	.connected_output =	neigh_connected_output,
पूर्ण;

अटल स्थिर काष्ठा neigh_ops arp_hh_ops = अणु
	.family =		AF_INET,
	.solicit =		arp_solicit,
	.error_report =		arp_error_report,
	.output =		neigh_resolve_output,
	.connected_output =	neigh_resolve_output,
पूर्ण;

अटल स्थिर काष्ठा neigh_ops arp_direct_ops = अणु
	.family =		AF_INET,
	.output =		neigh_direct_output,
	.connected_output =	neigh_direct_output,
पूर्ण;

काष्ठा neigh_table arp_tbl = अणु
	.family		= AF_INET,
	.key_len	= 4,
	.protocol	= cpu_to_be16(ETH_P_IP),
	.hash		= arp_hash,
	.key_eq		= arp_key_eq,
	.स्थिरructor	= arp_स्थिरructor,
	.proxy_reकरो	= parp_reकरो,
	.is_multicast	= arp_is_multicast,
	.id		= "arp_cache",
	.parms		= अणु
		.tbl			= &arp_tbl,
		.reachable_समय		= 30 * HZ,
		.data	= अणु
			[NEIGH_VAR_MCAST_PROBES] = 3,
			[NEIGH_VAR_UCAST_PROBES] = 3,
			[NEIGH_VAR_RETRANS_TIME] = 1 * HZ,
			[NEIGH_VAR_BASE_REACHABLE_TIME] = 30 * HZ,
			[NEIGH_VAR_DELAY_PROBE_TIME] = 5 * HZ,
			[NEIGH_VAR_GC_STALETIME] = 60 * HZ,
			[NEIGH_VAR_QUEUE_LEN_BYTES] = SK_WMEM_MAX,
			[NEIGH_VAR_PROXY_QLEN] = 64,
			[NEIGH_VAR_ANYCAST_DELAY] = 1 * HZ,
			[NEIGH_VAR_PROXY_DELAY]	= (8 * HZ) / 10,
			[NEIGH_VAR_LOCKTIME] = 1 * HZ,
		पूर्ण,
	पूर्ण,
	.gc_पूर्णांकerval	= 30 * HZ,
	.gc_thresh1	= 128,
	.gc_thresh2	= 512,
	.gc_thresh3	= 1024,
पूर्ण;
EXPORT_SYMBOL(arp_tbl);

पूर्णांक arp_mc_map(__be32 addr, u8 *haddr, काष्ठा net_device *dev, पूर्णांक dir)
अणु
	चयन (dev->type) अणु
	हाल ARPHRD_ETHER:
	हाल ARPHRD_FDDI:
	हाल ARPHRD_IEEE802:
		ip_eth_mc_map(addr, haddr);
		वापस 0;
	हाल ARPHRD_INFINIBAND:
		ip_ib_mc_map(addr, dev->broadcast, haddr);
		वापस 0;
	हाल ARPHRD_IPGRE:
		ip_ipgre_mc_map(addr, dev->broadcast, haddr);
		वापस 0;
	शेष:
		अगर (dir) अणु
			स_नकल(haddr, dev->broadcast, dev->addr_len);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण


अटल u32 arp_hash(स्थिर व्योम *pkey,
		    स्थिर काष्ठा net_device *dev,
		    __u32 *hash_rnd)
अणु
	वापस arp_hashfn(pkey, dev, hash_rnd);
पूर्ण

अटल bool arp_key_eq(स्थिर काष्ठा neighbour *neigh, स्थिर व्योम *pkey)
अणु
	वापस neigh_key_eq32(neigh, pkey);
पूर्ण

अटल पूर्णांक arp_स्थिरructor(काष्ठा neighbour *neigh)
अणु
	__be32 addr;
	काष्ठा net_device *dev = neigh->dev;
	काष्ठा in_device *in_dev;
	काष्ठा neigh_parms *parms;
	u32 inaddr_any = INADDR_ANY;

	अगर (dev->flags & (IFF_LOOPBACK | IFF_POINTOPOINT))
		स_नकल(neigh->primary_key, &inaddr_any, arp_tbl.key_len);

	addr = *(__be32 *)neigh->primary_key;
	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(dev);
	अगर (!in_dev) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	neigh->type = inet_addr_type_dev_table(dev_net(dev), dev, addr);

	parms = in_dev->arp_parms;
	__neigh_parms_put(neigh->parms);
	neigh->parms = neigh_parms_clone(parms);
	rcu_पढ़ो_unlock();

	अगर (!dev->header_ops) अणु
		neigh->nud_state = NUD_NOARP;
		neigh->ops = &arp_direct_ops;
		neigh->output = neigh_direct_output;
	पूर्ण अन्यथा अणु
		/* Good devices (checked by पढ़ोing texts, but only Ethernet is
		   tested)

		   ARPHRD_ETHER: (ethernet, apfddi)
		   ARPHRD_FDDI: (fddi)
		   ARPHRD_IEEE802: (tr)
		   ARPHRD_METRICOM: (strip)
		   ARPHRD_ARCNET:
		   etc. etc. etc.

		   ARPHRD_IPDDP will also work, अगर author repairs it.
		   I did not it, because this driver करोes not work even
		   in old paradigm.
		 */

		अगर (neigh->type == RTN_MULTICAST) अणु
			neigh->nud_state = NUD_NOARP;
			arp_mc_map(addr, neigh->ha, dev, 1);
		पूर्ण अन्यथा अगर (dev->flags & (IFF_NOARP | IFF_LOOPBACK)) अणु
			neigh->nud_state = NUD_NOARP;
			स_नकल(neigh->ha, dev->dev_addr, dev->addr_len);
		पूर्ण अन्यथा अगर (neigh->type == RTN_BROADCAST ||
			   (dev->flags & IFF_POINTOPOINT)) अणु
			neigh->nud_state = NUD_NOARP;
			स_नकल(neigh->ha, dev->broadcast, dev->addr_len);
		पूर्ण

		अगर (dev->header_ops->cache)
			neigh->ops = &arp_hh_ops;
		अन्यथा
			neigh->ops = &arp_generic_ops;

		अगर (neigh->nud_state & NUD_VALID)
			neigh->output = neigh->ops->connected_output;
		अन्यथा
			neigh->output = neigh->ops->output;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम arp_error_report(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	dst_link_failure(skb);
	kमुक्त_skb(skb);
पूर्ण

/* Create and send an arp packet. */
अटल व्योम arp_send_dst(पूर्णांक type, पूर्णांक ptype, __be32 dest_ip,
			 काष्ठा net_device *dev, __be32 src_ip,
			 स्थिर अचिन्हित अक्षर *dest_hw,
			 स्थिर अचिन्हित अक्षर *src_hw,
			 स्थिर अचिन्हित अक्षर *target_hw,
			 काष्ठा dst_entry *dst)
अणु
	काष्ठा sk_buff *skb;

	/* arp on this पूर्णांकerface. */
	अगर (dev->flags & IFF_NOARP)
		वापस;

	skb = arp_create(type, ptype, dest_ip, dev, src_ip,
			 dest_hw, src_hw, target_hw);
	अगर (!skb)
		वापस;

	skb_dst_set(skb, dst_clone(dst));
	arp_xmit(skb);
पूर्ण

व्योम arp_send(पूर्णांक type, पूर्णांक ptype, __be32 dest_ip,
	      काष्ठा net_device *dev, __be32 src_ip,
	      स्थिर अचिन्हित अक्षर *dest_hw, स्थिर अचिन्हित अक्षर *src_hw,
	      स्थिर अचिन्हित अक्षर *target_hw)
अणु
	arp_send_dst(type, ptype, dest_ip, dev, src_ip, dest_hw, src_hw,
		     target_hw, शून्य);
पूर्ण
EXPORT_SYMBOL(arp_send);

अटल व्योम arp_solicit(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	__be32 saddr = 0;
	u8 dst_ha[MAX_ADDR_LEN], *dst_hw = शून्य;
	काष्ठा net_device *dev = neigh->dev;
	__be32 target = *(__be32 *)neigh->primary_key;
	पूर्णांक probes = atomic_पढ़ो(&neigh->probes);
	काष्ठा in_device *in_dev;
	काष्ठा dst_entry *dst = शून्य;

	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(dev);
	अगर (!in_dev) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	चयन (IN_DEV_ARP_ANNOUNCE(in_dev)) अणु
	शेष:
	हाल 0:		/* By शेष announce any local IP */
		अगर (skb && inet_addr_type_dev_table(dev_net(dev), dev,
					  ip_hdr(skb)->saddr) == RTN_LOCAL)
			saddr = ip_hdr(skb)->saddr;
		अवरोध;
	हाल 1:		/* Restrict announcements of saddr in same subnet */
		अगर (!skb)
			अवरोध;
		saddr = ip_hdr(skb)->saddr;
		अगर (inet_addr_type_dev_table(dev_net(dev), dev,
					     saddr) == RTN_LOCAL) अणु
			/* saddr should be known to target */
			अगर (inet_addr_onlink(in_dev, target, saddr))
				अवरोध;
		पूर्ण
		saddr = 0;
		अवरोध;
	हाल 2:		/* Aव्योम secondary IPs, get a primary/preferred one */
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!saddr)
		saddr = inet_select_addr(dev, target, RT_SCOPE_LINK);

	probes -= NEIGH_VAR(neigh->parms, UCAST_PROBES);
	अगर (probes < 0) अणु
		अगर (!(neigh->nud_state & NUD_VALID))
			pr_debug("trying to ucast probe in NUD_INVALID\n");
		neigh_ha_snapshot(dst_ha, neigh, dev);
		dst_hw = dst_ha;
	पूर्ण अन्यथा अणु
		probes -= NEIGH_VAR(neigh->parms, APP_PROBES);
		अगर (probes < 0) अणु
			neigh_app_ns(neigh);
			वापस;
		पूर्ण
	पूर्ण

	अगर (skb && !(dev->priv_flags & IFF_XMIT_DST_RELEASE))
		dst = skb_dst(skb);
	arp_send_dst(ARPOP_REQUEST, ETH_P_ARP, target, dev, saddr,
		     dst_hw, dev->dev_addr, शून्य, dst);
पूर्ण

अटल पूर्णांक arp_ignore(काष्ठा in_device *in_dev, __be32 sip, __be32 tip)
अणु
	काष्ठा net *net = dev_net(in_dev->dev);
	पूर्णांक scope;

	चयन (IN_DEV_ARP_IGNORE(in_dev)) अणु
	हाल 0:	/* Reply, the tip is alपढ़ोy validated */
		वापस 0;
	हाल 1:	/* Reply only अगर tip is configured on the incoming पूर्णांकerface */
		sip = 0;
		scope = RT_SCOPE_HOST;
		अवरोध;
	हाल 2:	/*
		 * Reply only अगर tip is configured on the incoming पूर्णांकerface
		 * and is in same subnet as sip
		 */
		scope = RT_SCOPE_HOST;
		अवरोध;
	हाल 3:	/* Do not reply क्रम scope host addresses */
		sip = 0;
		scope = RT_SCOPE_LINK;
		in_dev = शून्य;
		अवरोध;
	हाल 4:	/* Reserved */
	हाल 5:
	हाल 6:
	हाल 7:
		वापस 0;
	हाल 8:	/* Do not reply */
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
	वापस !inet_confirm_addr(net, in_dev, sip, tip, scope);
पूर्ण

अटल पूर्णांक arp_filter(__be32 sip, __be32 tip, काष्ठा net_device *dev)
अणु
	काष्ठा rtable *rt;
	पूर्णांक flag = 0;
	/*अचिन्हित दीर्घ now; */
	काष्ठा net *net = dev_net(dev);

	rt = ip_route_output(net, sip, tip, 0, l3mdev_master_अगरindex_rcu(dev));
	अगर (IS_ERR(rt))
		वापस 1;
	अगर (rt->dst.dev != dev) अणु
		__NET_INC_STATS(net, LINUX_MIB_ARPFILTER);
		flag = 1;
	पूर्ण
	ip_rt_put(rt);
	वापस flag;
पूर्ण

/*
 * Check अगर we can use proxy ARP क्रम this path
 */
अटल अंतरभूत पूर्णांक arp_fwd_proxy(काष्ठा in_device *in_dev,
				काष्ठा net_device *dev,	काष्ठा rtable *rt)
अणु
	काष्ठा in_device *out_dev;
	पूर्णांक imi, omi = -1;

	अगर (rt->dst.dev == dev)
		वापस 0;

	अगर (!IN_DEV_PROXY_ARP(in_dev))
		वापस 0;
	imi = IN_DEV_MEDIUM_ID(in_dev);
	अगर (imi == 0)
		वापस 1;
	अगर (imi == -1)
		वापस 0;

	/* place to check क्रम proxy_arp क्रम routes */

	out_dev = __in_dev_get_rcu(rt->dst.dev);
	अगर (out_dev)
		omi = IN_DEV_MEDIUM_ID(out_dev);

	वापस omi != imi && omi != -1;
पूर्ण

/*
 * Check क्रम RFC3069 proxy arp निजी VLAN (allow to send back to same dev)
 *
 * RFC3069 supports proxy arp replies back to the same पूर्णांकerface.  This
 * is करोne to support (ethernet) चयन features, like RFC 3069, where
 * the inभागidual ports are not allowed to communicate with each
 * other, BUT they are allowed to talk to the upstream router.  As
 * described in RFC 3069, it is possible to allow these hosts to
 * communicate through the upstream router, by proxy_arp'ing.
 *
 * RFC 3069: "VLAN Aggregation for Efficient IP Address Allocation"
 *
 *  This technology is known by dअगरferent names:
 *    In RFC 3069 it is called VLAN Aggregation.
 *    Cisco and Allied Telesyn call it Private VLAN.
 *    Hewlett-Packard call it Source-Port filtering or port-isolation.
 *    Ericsson call it MAC-Forced Forwarding (RFC Draft).
 *
 */
अटल अंतरभूत पूर्णांक arp_fwd_pvlan(काष्ठा in_device *in_dev,
				काष्ठा net_device *dev,	काष्ठा rtable *rt,
				__be32 sip, __be32 tip)
अणु
	/* Private VLAN is only concerned about the same ethernet segment */
	अगर (rt->dst.dev != dev)
		वापस 0;

	/* Don't reply on self probes (often करोne by winकरोwz boxes)*/
	अगर (sip == tip)
		वापस 0;

	अगर (IN_DEV_PROXY_ARP_PVLAN(in_dev))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/*
 *	Interface to link layer: send routine and receive handler.
 */

/*
 *	Create an arp packet. If dest_hw is not set, we create a broadcast
 *	message.
 */
काष्ठा sk_buff *arp_create(पूर्णांक type, पूर्णांक ptype, __be32 dest_ip,
			   काष्ठा net_device *dev, __be32 src_ip,
			   स्थिर अचिन्हित अक्षर *dest_hw,
			   स्थिर अचिन्हित अक्षर *src_hw,
			   स्थिर अचिन्हित अक्षर *target_hw)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा arphdr *arp;
	अचिन्हित अक्षर *arp_ptr;
	पूर्णांक hlen = LL_RESERVED_SPACE(dev);
	पूर्णांक tlen = dev->needed_tailroom;

	/*
	 *	Allocate a buffer
	 */

	skb = alloc_skb(arp_hdr_len(dev) + hlen + tlen, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, hlen);
	skb_reset_network_header(skb);
	arp = skb_put(skb, arp_hdr_len(dev));
	skb->dev = dev;
	skb->protocol = htons(ETH_P_ARP);
	अगर (!src_hw)
		src_hw = dev->dev_addr;
	अगर (!dest_hw)
		dest_hw = dev->broadcast;

	/*
	 *	Fill the device header क्रम the ARP frame
	 */
	अगर (dev_hard_header(skb, dev, ptype, dest_hw, src_hw, skb->len) < 0)
		जाओ out;

	/*
	 * Fill out the arp protocol part.
	 *
	 * The arp hardware type should match the device type, except क्रम FDDI,
	 * which (according to RFC 1390) should always equal 1 (Ethernet).
	 */
	/*
	 *	Exceptions everywhere. AX.25 uses the AX.25 PID value not the
	 *	DIX code क्रम the protocol. Make these device काष्ठाure fields.
	 */
	चयन (dev->type) अणु
	शेष:
		arp->ar_hrd = htons(dev->type);
		arp->ar_pro = htons(ETH_P_IP);
		अवरोध;

#अगर IS_ENABLED(CONFIG_AX25)
	हाल ARPHRD_AX25:
		arp->ar_hrd = htons(ARPHRD_AX25);
		arp->ar_pro = htons(AX25_P_IP);
		अवरोध;

#अगर IS_ENABLED(CONFIG_NETROM)
	हाल ARPHRD_NETROM:
		arp->ar_hrd = htons(ARPHRD_NETROM);
		arp->ar_pro = htons(AX25_P_IP);
		अवरोध;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_FDDI)
	हाल ARPHRD_FDDI:
		arp->ar_hrd = htons(ARPHRD_ETHER);
		arp->ar_pro = htons(ETH_P_IP);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	arp->ar_hln = dev->addr_len;
	arp->ar_pln = 4;
	arp->ar_op = htons(type);

	arp_ptr = (अचिन्हित अक्षर *)(arp + 1);

	स_नकल(arp_ptr, src_hw, dev->addr_len);
	arp_ptr += dev->addr_len;
	स_नकल(arp_ptr, &src_ip, 4);
	arp_ptr += 4;

	चयन (dev->type) अणु
#अगर IS_ENABLED(CONFIG_FIREWIRE_NET)
	हाल ARPHRD_IEEE1394:
		अवरोध;
#पूर्ण_अगर
	शेष:
		अगर (target_hw)
			स_नकल(arp_ptr, target_hw, dev->addr_len);
		अन्यथा
			स_रखो(arp_ptr, 0, dev->addr_len);
		arp_ptr += dev->addr_len;
	पूर्ण
	स_नकल(arp_ptr, &dest_ip, 4);

	वापस skb;

out:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(arp_create);

अटल पूर्णांक arp_xmit_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस dev_queue_xmit(skb);
पूर्ण

/*
 *	Send an arp packet.
 */
व्योम arp_xmit(काष्ठा sk_buff *skb)
अणु
	/* Send it off, maybe filter it using firewalling first.  */
	NF_HOOK(NFPROTO_ARP, NF_ARP_OUT,
		dev_net(skb->dev), शून्य, skb, शून्य, skb->dev,
		arp_xmit_finish);
पूर्ण
EXPORT_SYMBOL(arp_xmit);

अटल bool arp_is_garp(काष्ठा net *net, काष्ठा net_device *dev,
			पूर्णांक *addr_type, __be16 ar_op,
			__be32 sip, __be32 tip,
			अचिन्हित अक्षर *sha, अचिन्हित अक्षर *tha)
अणु
	bool is_garp = tip == sip;

	/* Gratuitous ARP _replies_ also require target hwaddr to be
	 * the same as source.
	 */
	अगर (is_garp && ar_op == htons(ARPOP_REPLY))
		is_garp =
			/* IPv4 over IEEE 1394 करोesn't provide target
			 * hardware address field in its ARP payload.
			 */
			tha &&
			!स_भेद(tha, sha, dev->addr_len);

	अगर (is_garp) अणु
		*addr_type = inet_addr_type_dev_table(net, dev, sip);
		अगर (*addr_type != RTN_UNICAST)
			is_garp = false;
	पूर्ण
	वापस is_garp;
पूर्ण

/*
 *	Process an arp request.
 */

अटल पूर्णांक arp_process(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);
	काष्ठा arphdr *arp;
	अचिन्हित अक्षर *arp_ptr;
	काष्ठा rtable *rt;
	अचिन्हित अक्षर *sha;
	अचिन्हित अक्षर *tha = शून्य;
	__be32 sip, tip;
	u16 dev_type = dev->type;
	पूर्णांक addr_type;
	काष्ठा neighbour *n;
	काष्ठा dst_entry *reply_dst = शून्य;
	bool is_garp = false;

	/* arp_rcv below verअगरies the ARP header and verअगरies the device
	 * is ARP'able.
	 */

	अगर (!in_dev)
		जाओ out_मुक्त_skb;

	arp = arp_hdr(skb);

	चयन (dev_type) अणु
	शेष:
		अगर (arp->ar_pro != htons(ETH_P_IP) ||
		    htons(dev_type) != arp->ar_hrd)
			जाओ out_मुक्त_skb;
		अवरोध;
	हाल ARPHRD_ETHER:
	हाल ARPHRD_FDDI:
	हाल ARPHRD_IEEE802:
		/*
		 * ETHERNET, and Fibre Channel (which are IEEE 802
		 * devices, according to RFC 2625) devices will accept ARP
		 * hardware types of either 1 (Ethernet) or 6 (IEEE 802.2).
		 * This is the हाल also of FDDI, where the RFC 1390 says that
		 * FDDI devices should accept ARP hardware of (1) Ethernet,
		 * however, to be more robust, we'll accept both 1 (Ethernet)
		 * or 6 (IEEE 802.2)
		 */
		अगर ((arp->ar_hrd != htons(ARPHRD_ETHER) &&
		     arp->ar_hrd != htons(ARPHRD_IEEE802)) ||
		    arp->ar_pro != htons(ETH_P_IP))
			जाओ out_मुक्त_skb;
		अवरोध;
	हाल ARPHRD_AX25:
		अगर (arp->ar_pro != htons(AX25_P_IP) ||
		    arp->ar_hrd != htons(ARPHRD_AX25))
			जाओ out_मुक्त_skb;
		अवरोध;
	हाल ARPHRD_NETROM:
		अगर (arp->ar_pro != htons(AX25_P_IP) ||
		    arp->ar_hrd != htons(ARPHRD_NETROM))
			जाओ out_मुक्त_skb;
		अवरोध;
	पूर्ण

	/* Understand only these message types */

	अगर (arp->ar_op != htons(ARPOP_REPLY) &&
	    arp->ar_op != htons(ARPOP_REQUEST))
		जाओ out_मुक्त_skb;

/*
 *	Extract fields
 */
	arp_ptr = (अचिन्हित अक्षर *)(arp + 1);
	sha	= arp_ptr;
	arp_ptr += dev->addr_len;
	स_नकल(&sip, arp_ptr, 4);
	arp_ptr += 4;
	चयन (dev_type) अणु
#अगर IS_ENABLED(CONFIG_FIREWIRE_NET)
	हाल ARPHRD_IEEE1394:
		अवरोध;
#पूर्ण_अगर
	शेष:
		tha = arp_ptr;
		arp_ptr += dev->addr_len;
	पूर्ण
	स_नकल(&tip, arp_ptr, 4);
/*
 *	Check क्रम bad requests क्रम 127.x.x.x and requests क्रम multicast
 *	addresses.  If this is one such, delete it.
 */
	अगर (ipv4_is_multicast(tip) ||
	    (!IN_DEV_ROUTE_LOCALNET(in_dev) && ipv4_is_loopback(tip)))
		जाओ out_मुक्त_skb;

 /*
  *	For some 802.11 wireless deployments (and possibly other networks),
  *	there will be an ARP proxy and gratuitous ARP frames are attacks
  *	and thus should not be accepted.
  */
	अगर (sip == tip && IN_DEV_ORCONF(in_dev, DROP_GRATUITOUS_ARP))
		जाओ out_मुक्त_skb;

/*
 *     Special हाल: We must set Frame Relay source Q.922 address
 */
	अगर (dev_type == ARPHRD_DLCI)
		sha = dev->broadcast;

/*
 *  Process entry.  The idea here is we want to send a reply अगर it is a
 *  request क्रम us or अगर it is a request क्रम someone अन्यथा that we hold
 *  a proxy क्रम.  We want to add an entry to our cache अगर it is a reply
 *  to us or अगर it is a request क्रम our address.
 *  (The assumption क्रम this last is that अगर someone is requesting our
 *  address, they are probably पूर्णांकending to talk to us, so it saves समय
 *  अगर we cache their address.  Their address is also probably not in
 *  our cache, since ours is not in their cache.)
 *
 *  Putting this another way, we only care about replies अगर they are to
 *  us, in which हाल we add them to the cache.  For requests, we care
 *  about those क्रम us and those क्रम our proxies.  We reply to both,
 *  and in the हाल of requests क्रम us we add the requester to the arp
 *  cache.
 */

	अगर (arp->ar_op == htons(ARPOP_REQUEST) && skb_metadata_dst(skb))
		reply_dst = (काष्ठा dst_entry *)
			    iptunnel_metadata_reply(skb_metadata_dst(skb),
						    GFP_ATOMIC);

	/* Special हाल: IPv4 duplicate address detection packet (RFC2131) */
	अगर (sip == 0) अणु
		अगर (arp->ar_op == htons(ARPOP_REQUEST) &&
		    inet_addr_type_dev_table(net, dev, tip) == RTN_LOCAL &&
		    !arp_ignore(in_dev, sip, tip))
			arp_send_dst(ARPOP_REPLY, ETH_P_ARP, sip, dev, tip,
				     sha, dev->dev_addr, sha, reply_dst);
		जाओ out_consume_skb;
	पूर्ण

	अगर (arp->ar_op == htons(ARPOP_REQUEST) &&
	    ip_route_input_noref(skb, tip, sip, 0, dev) == 0) अणु

		rt = skb_rtable(skb);
		addr_type = rt->rt_type;

		अगर (addr_type == RTN_LOCAL) अणु
			पूर्णांक करोnt_send;

			करोnt_send = arp_ignore(in_dev, sip, tip);
			अगर (!करोnt_send && IN_DEV_ARPFILTER(in_dev))
				करोnt_send = arp_filter(sip, tip, dev);
			अगर (!करोnt_send) अणु
				n = neigh_event_ns(&arp_tbl, sha, &sip, dev);
				अगर (n) अणु
					arp_send_dst(ARPOP_REPLY, ETH_P_ARP,
						     sip, dev, tip, sha,
						     dev->dev_addr, sha,
						     reply_dst);
					neigh_release(n);
				पूर्ण
			पूर्ण
			जाओ out_consume_skb;
		पूर्ण अन्यथा अगर (IN_DEV_FORWARD(in_dev)) अणु
			अगर (addr_type == RTN_UNICAST  &&
			    (arp_fwd_proxy(in_dev, dev, rt) ||
			     arp_fwd_pvlan(in_dev, dev, rt, sip, tip) ||
			     (rt->dst.dev != dev &&
			      pneigh_lookup(&arp_tbl, net, &tip, dev, 0)))) अणु
				n = neigh_event_ns(&arp_tbl, sha, &sip, dev);
				अगर (n)
					neigh_release(n);

				अगर (NEIGH_CB(skb)->flags & LOCALLY_ENQUEUED ||
				    skb->pkt_type == PACKET_HOST ||
				    NEIGH_VAR(in_dev->arp_parms, PROXY_DELAY) == 0) अणु
					arp_send_dst(ARPOP_REPLY, ETH_P_ARP,
						     sip, dev, tip, sha,
						     dev->dev_addr, sha,
						     reply_dst);
				पूर्ण अन्यथा अणु
					pneigh_enqueue(&arp_tbl,
						       in_dev->arp_parms, skb);
					जाओ out_मुक्त_dst;
				पूर्ण
				जाओ out_consume_skb;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Update our ARP tables */

	n = __neigh_lookup(&arp_tbl, &sip, dev, 0);

	addr_type = -1;
	अगर (n || IN_DEV_ARP_ACCEPT(in_dev)) अणु
		is_garp = arp_is_garp(net, dev, &addr_type, arp->ar_op,
				      sip, tip, sha, tha);
	पूर्ण

	अगर (IN_DEV_ARP_ACCEPT(in_dev)) अणु
		/* Unsolicited ARP is not accepted by शेष.
		   It is possible, that this option should be enabled क्रम some
		   devices (strip is candidate)
		 */
		अगर (!n &&
		    (is_garp ||
		     (arp->ar_op == htons(ARPOP_REPLY) &&
		      (addr_type == RTN_UNICAST ||
		       (addr_type < 0 &&
			/* postpone calculation to as late as possible */
			inet_addr_type_dev_table(net, dev, sip) ==
				RTN_UNICAST)))))
			n = __neigh_lookup(&arp_tbl, &sip, dev, 1);
	पूर्ण

	अगर (n) अणु
		पूर्णांक state = NUD_REACHABLE;
		पूर्णांक override;

		/* If several dअगरferent ARP replies follows back-to-back,
		   use the FIRST one. It is possible, अगर several proxy
		   agents are active. Taking the first reply prevents
		   arp trashing and chooses the fastest router.
		 */
		override = समय_after(jअगरfies,
				      n->updated +
				      NEIGH_VAR(n->parms, LOCKTIME)) ||
			   is_garp;

		/* Broadcast replies and request packets
		   करो not निश्चित neighbour reachability.
		 */
		अगर (arp->ar_op != htons(ARPOP_REPLY) ||
		    skb->pkt_type != PACKET_HOST)
			state = NUD_STALE;
		neigh_update(n, sha, state,
			     override ? NEIGH_UPDATE_F_OVERRIDE : 0, 0);
		neigh_release(n);
	पूर्ण

out_consume_skb:
	consume_skb(skb);

out_मुक्त_dst:
	dst_release(reply_dst);
	वापस NET_RX_SUCCESS;

out_मुक्त_skb:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल व्योम parp_reकरो(काष्ठा sk_buff *skb)
अणु
	arp_process(dev_net(skb->dev), शून्य, skb);
पूर्ण

अटल पूर्णांक arp_is_multicast(स्थिर व्योम *pkey)
अणु
	वापस ipv4_is_multicast(*((__be32 *)pkey));
पूर्ण

/*
 *	Receive an arp request from the device layer.
 */

अटल पूर्णांक arp_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		   काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	स्थिर काष्ठा arphdr *arp;

	/* करो not tweak dropwatch on an ARP we will ignore */
	अगर (dev->flags & IFF_NOARP ||
	    skb->pkt_type == PACKET_OTHERHOST ||
	    skb->pkt_type == PACKET_LOOPBACK)
		जाओ consumeskb;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ out_of_mem;

	/* ARP header, plus 2 device addresses, plus 2 IP addresses.  */
	अगर (!pskb_may_pull(skb, arp_hdr_len(dev)))
		जाओ मुक्तskb;

	arp = arp_hdr(skb);
	अगर (arp->ar_hln != dev->addr_len || arp->ar_pln != 4)
		जाओ मुक्तskb;

	स_रखो(NEIGH_CB(skb), 0, माप(काष्ठा neighbour_cb));

	वापस NF_HOOK(NFPROTO_ARP, NF_ARP_IN,
		       dev_net(dev), शून्य, skb, dev, शून्य,
		       arp_process);

consumeskb:
	consume_skb(skb);
	वापस NET_RX_SUCCESS;
मुक्तskb:
	kमुक्त_skb(skb);
out_of_mem:
	वापस NET_RX_DROP;
पूर्ण

/*
 *	User level पूर्णांकerface (ioctl)
 */

/*
 *	Set (create) an ARP cache entry.
 */

अटल पूर्णांक arp_req_set_proxy(काष्ठा net *net, काष्ठा net_device *dev, पूर्णांक on)
अणु
	अगर (!dev) अणु
		IPV4_DEVCONF_ALL(net, PROXY_ARP) = on;
		वापस 0;
	पूर्ण
	अगर (__in_dev_get_rtnl(dev)) अणु
		IN_DEV_CONF_SET(__in_dev_get_rtnl(dev), PROXY_ARP, on);
		वापस 0;
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक arp_req_set_खुला(काष्ठा net *net, काष्ठा arpreq *r,
		काष्ठा net_device *dev)
अणु
	__be32 ip = ((काष्ठा sockaddr_in *)&r->arp_pa)->sin_addr.s_addr;
	__be32 mask = ((काष्ठा sockaddr_in *)&r->arp_neपंचांगask)->sin_addr.s_addr;

	अगर (mask && mask != htonl(0xFFFFFFFF))
		वापस -EINVAL;
	अगर (!dev && (r->arp_flags & ATF_COM)) अणु
		dev = dev_getbyhwaddr_rcu(net, r->arp_ha.sa_family,
				      r->arp_ha.sa_data);
		अगर (!dev)
			वापस -ENODEV;
	पूर्ण
	अगर (mask) अणु
		अगर (!pneigh_lookup(&arp_tbl, net, &ip, dev, 1))
			वापस -ENOBUFS;
		वापस 0;
	पूर्ण

	वापस arp_req_set_proxy(net, dev, 1);
पूर्ण

अटल पूर्णांक arp_req_set(काष्ठा net *net, काष्ठा arpreq *r,
		       काष्ठा net_device *dev)
अणु
	__be32 ip;
	काष्ठा neighbour *neigh;
	पूर्णांक err;

	अगर (r->arp_flags & ATF_PUBL)
		वापस arp_req_set_खुला(net, r, dev);

	ip = ((काष्ठा sockaddr_in *)&r->arp_pa)->sin_addr.s_addr;
	अगर (r->arp_flags & ATF_PERM)
		r->arp_flags |= ATF_COM;
	अगर (!dev) अणु
		काष्ठा rtable *rt = ip_route_output(net, ip, 0, RTO_ONLINK, 0);

		अगर (IS_ERR(rt))
			वापस PTR_ERR(rt);
		dev = rt->dst.dev;
		ip_rt_put(rt);
		अगर (!dev)
			वापस -EINVAL;
	पूर्ण
	चयन (dev->type) अणु
#अगर IS_ENABLED(CONFIG_FDDI)
	हाल ARPHRD_FDDI:
		/*
		 * According to RFC 1390, FDDI devices should accept ARP
		 * hardware types of 1 (Ethernet).  However, to be more
		 * robust, we'll accept hardware types of either 1 (Ethernet)
		 * or 6 (IEEE 802.2).
		 */
		अगर (r->arp_ha.sa_family != ARPHRD_FDDI &&
		    r->arp_ha.sa_family != ARPHRD_ETHER &&
		    r->arp_ha.sa_family != ARPHRD_IEEE802)
			वापस -EINVAL;
		अवरोध;
#पूर्ण_अगर
	शेष:
		अगर (r->arp_ha.sa_family != dev->type)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	neigh = __neigh_lookup_त्रुटि_सं(&arp_tbl, &ip, dev);
	err = PTR_ERR(neigh);
	अगर (!IS_ERR(neigh)) अणु
		अचिन्हित पूर्णांक state = NUD_STALE;
		अगर (r->arp_flags & ATF_PERM)
			state = NUD_PERMANENT;
		err = neigh_update(neigh, (r->arp_flags & ATF_COM) ?
				   r->arp_ha.sa_data : शून्य, state,
				   NEIGH_UPDATE_F_OVERRIDE |
				   NEIGH_UPDATE_F_ADMIN, 0);
		neigh_release(neigh);
	पूर्ण
	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक arp_state_to_flags(काष्ठा neighbour *neigh)
अणु
	अगर (neigh->nud_state&NUD_PERMANENT)
		वापस ATF_PERM | ATF_COM;
	अन्यथा अगर (neigh->nud_state&NUD_VALID)
		वापस ATF_COM;
	अन्यथा
		वापस 0;
पूर्ण

/*
 *	Get an ARP cache entry.
 */

अटल पूर्णांक arp_req_get(काष्ठा arpreq *r, काष्ठा net_device *dev)
अणु
	__be32 ip = ((काष्ठा sockaddr_in *) &r->arp_pa)->sin_addr.s_addr;
	काष्ठा neighbour *neigh;
	पूर्णांक err = -ENXIO;

	neigh = neigh_lookup(&arp_tbl, &ip, dev);
	अगर (neigh) अणु
		अगर (!(neigh->nud_state & NUD_NOARP)) अणु
			पढ़ो_lock_bh(&neigh->lock);
			स_नकल(r->arp_ha.sa_data, neigh->ha, dev->addr_len);
			r->arp_flags = arp_state_to_flags(neigh);
			पढ़ो_unlock_bh(&neigh->lock);
			r->arp_ha.sa_family = dev->type;
			strlcpy(r->arp_dev, dev->name, माप(r->arp_dev));
			err = 0;
		पूर्ण
		neigh_release(neigh);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक arp_invalidate(काष्ठा net_device *dev, __be32 ip)
अणु
	काष्ठा neighbour *neigh = neigh_lookup(&arp_tbl, &ip, dev);
	पूर्णांक err = -ENXIO;
	काष्ठा neigh_table *tbl = &arp_tbl;

	अगर (neigh) अणु
		अगर (neigh->nud_state & ~NUD_NOARP)
			err = neigh_update(neigh, शून्य, NUD_FAILED,
					   NEIGH_UPDATE_F_OVERRIDE|
					   NEIGH_UPDATE_F_ADMIN, 0);
		ग_लिखो_lock_bh(&tbl->lock);
		neigh_release(neigh);
		neigh_हटाओ_one(neigh, tbl);
		ग_लिखो_unlock_bh(&tbl->lock);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक arp_req_delete_खुला(काष्ठा net *net, काष्ठा arpreq *r,
		काष्ठा net_device *dev)
अणु
	__be32 ip = ((काष्ठा sockaddr_in *) &r->arp_pa)->sin_addr.s_addr;
	__be32 mask = ((काष्ठा sockaddr_in *)&r->arp_neपंचांगask)->sin_addr.s_addr;

	अगर (mask == htonl(0xFFFFFFFF))
		वापस pneigh_delete(&arp_tbl, net, &ip, dev);

	अगर (mask)
		वापस -EINVAL;

	वापस arp_req_set_proxy(net, dev, 0);
पूर्ण

अटल पूर्णांक arp_req_delete(काष्ठा net *net, काष्ठा arpreq *r,
			  काष्ठा net_device *dev)
अणु
	__be32 ip;

	अगर (r->arp_flags & ATF_PUBL)
		वापस arp_req_delete_खुला(net, r, dev);

	ip = ((काष्ठा sockaddr_in *)&r->arp_pa)->sin_addr.s_addr;
	अगर (!dev) अणु
		काष्ठा rtable *rt = ip_route_output(net, ip, 0, RTO_ONLINK, 0);
		अगर (IS_ERR(rt))
			वापस PTR_ERR(rt);
		dev = rt->dst.dev;
		ip_rt_put(rt);
		अगर (!dev)
			वापस -EINVAL;
	पूर्ण
	वापस arp_invalidate(dev, ip);
पूर्ण

/*
 *	Handle an ARP layer I/O control request.
 */

पूर्णांक arp_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	पूर्णांक err;
	काष्ठा arpreq r;
	काष्ठा net_device *dev = शून्य;

	चयन (cmd) अणु
	हाल SIOCDARP:
	हाल SIOCSARP:
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;
		fallthrough;
	हाल SIOCGARP:
		err = copy_from_user(&r, arg, माप(काष्ठा arpreq));
		अगर (err)
			वापस -EFAULT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (r.arp_pa.sa_family != AF_INET)
		वापस -EPFNOSUPPORT;

	अगर (!(r.arp_flags & ATF_PUBL) &&
	    (r.arp_flags & (ATF_NETMASK | ATF_DONTPUB)))
		वापस -EINVAL;
	अगर (!(r.arp_flags & ATF_NETMASK))
		((काष्ठा sockaddr_in *)&r.arp_neपंचांगask)->sin_addr.s_addr =
							   htonl(0xFFFFFFFFUL);
	rtnl_lock();
	अगर (r.arp_dev[0]) अणु
		err = -ENODEV;
		dev = __dev_get_by_name(net, r.arp_dev);
		अगर (!dev)
			जाओ out;

		/* Mmmm... It is wrong... ARPHRD_NETROM==0 */
		अगर (!r.arp_ha.sa_family)
			r.arp_ha.sa_family = dev->type;
		err = -EINVAL;
		अगर ((r.arp_flags & ATF_COM) && r.arp_ha.sa_family != dev->type)
			जाओ out;
	पूर्ण अन्यथा अगर (cmd == SIOCGARP) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (cmd) अणु
	हाल SIOCDARP:
		err = arp_req_delete(net, &r, dev);
		अवरोध;
	हाल SIOCSARP:
		err = arp_req_set(net, &r, dev);
		अवरोध;
	हाल SIOCGARP:
		err = arp_req_get(&r, dev);
		अवरोध;
	पूर्ण
out:
	rtnl_unlock();
	अगर (cmd == SIOCGARP && !err && copy_to_user(arg, &r, माप(r)))
		err = -EFAULT;
	वापस err;
पूर्ण

अटल पूर्णांक arp_netdev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			    व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_change_info *change_info;

	चयन (event) अणु
	हाल NETDEV_CHANGEADDR:
		neigh_changeaddr(&arp_tbl, dev);
		rt_cache_flush(dev_net(dev));
		अवरोध;
	हाल NETDEV_CHANGE:
		change_info = ptr;
		अगर (change_info->flags_changed & IFF_NOARP)
			neigh_changeaddr(&arp_tbl, dev);
		अगर (!netअगर_carrier_ok(dev))
			neigh_carrier_करोwn(&arp_tbl, dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block arp_netdev_notअगरier = अणु
	.notअगरier_call = arp_netdev_event,
पूर्ण;

/* Note, that it is not on notअगरier chain.
   It is necessary, that this routine was called after route cache will be
   flushed.
 */
व्योम arp_अगरकरोwn(काष्ठा net_device *dev)
अणु
	neigh_अगरकरोwn(&arp_tbl, dev);
पूर्ण


/*
 *	Called once on startup.
 */

अटल काष्ठा packet_type arp_packet_type __पढ़ो_mostly = अणु
	.type =	cpu_to_be16(ETH_P_ARP),
	.func =	arp_rcv,
पूर्ण;

अटल पूर्णांक arp_proc_init(व्योम);

व्योम __init arp_init(व्योम)
अणु
	neigh_table_init(NEIGH_ARP_TABLE, &arp_tbl);

	dev_add_pack(&arp_packet_type);
	arp_proc_init();
#अगर_घोषित CONFIG_SYSCTL
	neigh_sysctl_रेजिस्टर(शून्य, &arp_tbl.parms, शून्य);
#पूर्ण_अगर
	रेजिस्टर_netdevice_notअगरier(&arp_netdev_notअगरier);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
#अगर IS_ENABLED(CONFIG_AX25)

/* ------------------------------------------------------------------------ */
/*
 *	ax25 -> ASCII conversion
 */
अटल व्योम ax2asc2(ax25_address *a, अक्षर *buf)
अणु
	अक्षर c, *s;
	पूर्णांक n;

	क्रम (n = 0, s = buf; n < 6; n++) अणु
		c = (a->ax25_call[n] >> 1) & 0x7F;

		अगर (c != ' ')
			*s++ = c;
	पूर्ण

	*s++ = '-';
	n = (a->ax25_call[6] >> 1) & 0x0F;
	अगर (n > 9) अणु
		*s++ = '1';
		n -= 10;
	पूर्ण

	*s++ = n + '0';
	*s++ = '\0';

	अगर (*buf == '\0' || *buf == '-') अणु
		buf[0] = '*';
		buf[1] = '\0';
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_AX25 */

#घोषणा HBUFFERLEN 30

अटल व्योम arp_क्रमmat_neigh_entry(काष्ठा seq_file *seq,
				   काष्ठा neighbour *n)
अणु
	अक्षर hbuffer[HBUFFERLEN];
	पूर्णांक k, j;
	अक्षर tbuf[16];
	काष्ठा net_device *dev = n->dev;
	पूर्णांक hatype = dev->type;

	पढ़ो_lock(&n->lock);
	/* Convert hardware address to XX:XX:XX:XX ... क्रमm. */
#अगर IS_ENABLED(CONFIG_AX25)
	अगर (hatype == ARPHRD_AX25 || hatype == ARPHRD_NETROM)
		ax2asc2((ax25_address *)n->ha, hbuffer);
	अन्यथा अणु
#पूर्ण_अगर
	क्रम (k = 0, j = 0; k < HBUFFERLEN - 3 && j < dev->addr_len; j++) अणु
		hbuffer[k++] = hex_asc_hi(n->ha[j]);
		hbuffer[k++] = hex_asc_lo(n->ha[j]);
		hbuffer[k++] = ':';
	पूर्ण
	अगर (k != 0)
		--k;
	hbuffer[k] = 0;
#अगर IS_ENABLED(CONFIG_AX25)
	पूर्ण
#पूर्ण_अगर
	प्र_लिखो(tbuf, "%pI4", n->primary_key);
	seq_म_लिखो(seq, "%-16s 0x%-10x0x%-10x%-17s     *        %s\n",
		   tbuf, hatype, arp_state_to_flags(n), hbuffer, dev->name);
	पढ़ो_unlock(&n->lock);
पूर्ण

अटल व्योम arp_क्रमmat_pneigh_entry(काष्ठा seq_file *seq,
				    काष्ठा pneigh_entry *n)
अणु
	काष्ठा net_device *dev = n->dev;
	पूर्णांक hatype = dev ? dev->type : 0;
	अक्षर tbuf[16];

	प्र_लिखो(tbuf, "%pI4", n->key);
	seq_म_लिखो(seq, "%-16s 0x%-10x0x%-10x%s     *        %s\n",
		   tbuf, hatype, ATF_PUBL | ATF_PERM, "00:00:00:00:00:00",
		   dev ? dev->name : "*");
पूर्ण

अटल पूर्णांक arp_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "IP address       HW type     Flags       "
			      "HW address            Mask     Device\n");
	पूर्ण अन्यथा अणु
		काष्ठा neigh_seq_state *state = seq->निजी;

		अगर (state->flags & NEIGH_SEQ_IS_PNEIGH)
			arp_क्रमmat_pneigh_entry(seq, v);
		अन्यथा
			arp_क्रमmat_neigh_entry(seq, v);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *arp_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	/* Don't want to confuse "arp -a" w/ magic entries,
	 * so we tell the generic iterator to skip NUD_NOARP.
	 */
	वापस neigh_seq_start(seq, pos, &arp_tbl, NEIGH_SEQ_SKIP_NOARP);
पूर्ण

/* ------------------------------------------------------------------------ */

अटल स्थिर काष्ठा seq_operations arp_seq_ops = अणु
	.start	= arp_seq_start,
	.next	= neigh_seq_next,
	.stop	= neigh_seq_stop,
	.show	= arp_seq_show,
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल पूर्णांक __net_init arp_net_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net("arp", 0444, net->proc_net, &arp_seq_ops,
			माप(काष्ठा neigh_seq_state)))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास arp_net_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("arp", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations arp_net_ops = अणु
	.init = arp_net_init,
	.निकास = arp_net_निकास,
पूर्ण;

अटल पूर्णांक __init arp_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&arp_net_ops);
पूर्ण

#अन्यथा /* CONFIG_PROC_FS */

अटल पूर्णांक __init arp_proc_init(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */
