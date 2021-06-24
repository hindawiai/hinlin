<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Linux NET3:	IP/IP protocol decoder.
 *
 *	Authors:
 *		Sam Lantinga (slouken@cs.ucdavis.edu)  02/01/95
 *
 *	Fixes:
 *		Alan Cox	:	Merged and made usable non modular (its so tiny its silly as
 *					a module taking up 2 pages).
 *		Alan Cox	: 	Fixed bug with 1.3.18 and IPIP not working (now needs to set skb->h.iph)
 *					to keep ip_क्रमward happy.
 *		Alan Cox	:	More fixes क्रम 1.3.21, and firewall fix. Maybe this will work soon 8).
 *		Kai Schulte	:	Fixed #घोषणाs क्रम IP_FIREWALL->FIREWALL
 *              David Woodhouse :       Perक्रमm some basic ICMP handling.
 *                                      IPIP Routing without decapsulation.
 *              Carlos Picoto   :       GRE over IP support
 *		Alexey Kuznetsov:	Reworked. Really, now it is truncated version of ipv4/ip_gre.c.
 *					I करो not want to merge them together.
 */

/* tunnel.c: an IP tunnel driver

	The purpose of this driver is to provide an IP tunnel through
	which you can tunnel network traffic transparently across subnets.

	This was written by looking at Nick Holloway's dummy driver
	Thanks क्रम the great code!

		-Sam Lantinga	(slouken@cs.ucdavis.edu)  02/01/95

	Minor tweaks:
		Cleaned up the code a little and added some pre-1.3.0 tweaks.
		dev->hard_header/hard_header_len changed to use no headers.
		Comments/bracketing tweaked.
		Made the tunnels use dev->name not tunnel: when error reporting.
		Added tx_dropped stat

		-Alan Cox	(alan@lxorguk.ukuu.org.uk) 21 March 95

	Reworked:
		Changed to tunnel to destination gateway in addition to the
			tunnel's poपूर्णांकopoपूर्णांक address
		Almost completely rewritten
		Note:  There is currently no firewall or ICMP handling करोne.

		-Sam Lantinga	(slouken@cs.ucdavis.edu) 02/13/96

*/

/* Things I wish I had known when writing the tunnel driver:

	When the tunnel_xmit() function is called, the skb contains the
	packet to be sent (plus a great deal of extra info), and dev
	contains the tunnel device that _we_ are.

	When we are passed a packet, we are expected to fill in the
	source address with our source IP address.

	What is the proper way to allocate, copy and मुक्त a buffer?
	After you allocate it, it is a "0 length" chunk of memory
	starting at zero.  If you want to add headers to the buffer
	later, you'll have to call "skb_reserve(skb, amount)" with
	the amount of memory you want reserved.  Then, you call
	"skb_put(skb, amount)" with the amount of space you want in
	the buffer.  skb_put() वापसs a poपूर्णांकer to the top (#0) of
	that buffer.  skb->len is set to the amount of space you have
	"allocated" with skb_put().  You can then ग_लिखो up to skb->len
	bytes to that buffer.  If you need more, you can call skb_put()
	again with the additional amount of space you need.  You can
	find out how much more space you can allocate by calling
	"skb_tailroom(skb)".
	Now, to add header space, call "skb_push(skb, header_len)".
	This creates space at the beginning of the buffer and वापसs
	a poपूर्णांकer to this new space.  If later you need to strip a
	header from a buffer, call "skb_pull(skb, header_len)".
	skb_headroom() will वापस how much space is left at the top
	of the buffer (beक्रमe the मुख्य data).  Remember, this headroom
	space must be reserved beक्रमe the skb_put() function is called.
	*/

/*
   This version of net/ipv4/ipip.c is cloned of net/ipv4/ip_gre.c

   For comments look at net/ipv4/ip_gre.c --ANK
 */


#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/अगर_ether.h>

#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/dst_metadata.h>

अटल bool log_ecn_error = true;
module_param(log_ecn_error, bool, 0644);
MODULE_PARM_DESC(log_ecn_error, "Log packets received with corrupted ECN");

अटल अचिन्हित पूर्णांक ipip_net_id __पढ़ो_mostly;

अटल पूर्णांक ipip_tunnel_init(काष्ठा net_device *dev);
अटल काष्ठा rtnl_link_ops ipip_link_ops __पढ़ो_mostly;

अटल पूर्णांक ipip_err(काष्ठा sk_buff *skb, u32 info)
अणु
	/* All the routers (except क्रम Linux) वापस only
	 * 8 bytes of packet payload. It means, that precise relaying of
	 * ICMP in the real Internet is असलolutely infeasible.
	 */
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा ip_tunnel_net *itn = net_generic(net, ipip_net_id);
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	स्थिर पूर्णांक type = icmp_hdr(skb)->type;
	स्थिर पूर्णांक code = icmp_hdr(skb)->code;
	काष्ठा ip_tunnel *t;
	पूर्णांक err = 0;

	t = ip_tunnel_lookup(itn, skb->dev->अगरindex, TUNNEL_NO_KEY,
			     iph->daddr, iph->saddr, 0);
	अगर (!t) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	चयन (type) अणु
	हाल ICMP_DEST_UNREACH:
		चयन (code) अणु
		हाल ICMP_SR_FAILED:
			/* Impossible event. */
			जाओ out;
		शेष:
			/* All others are translated to HOST_UNREACH.
			 * rfc2003 contains "deep thoughts" about NET_UNREACH,
			 * I believe they are just ether pollution. --ANK
			 */
			अवरोध;
		पूर्ण
		अवरोध;

	हाल ICMP_TIME_EXCEEDED:
		अगर (code != ICMP_EXC_TTL)
			जाओ out;
		अवरोध;

	हाल ICMP_REसूचीECT:
		अवरोध;

	शेष:
		जाओ out;
	पूर्ण

	अगर (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED) अणु
		ipv4_update_pmtu(skb, net, info, t->parms.link, iph->protocol);
		जाओ out;
	पूर्ण

	अगर (type == ICMP_REसूचीECT) अणु
		ipv4_redirect(skb, net, t->parms.link, iph->protocol);
		जाओ out;
	पूर्ण

	अगर (t->parms.iph.daddr == 0) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (t->parms.iph.ttl == 0 && type == ICMP_TIME_EXCEEDED)
		जाओ out;

	अगर (समय_beक्रमe(jअगरfies, t->err_समय + IPTUNNEL_ERR_TIMEO))
		t->err_count++;
	अन्यथा
		t->err_count = 1;
	t->err_समय = jअगरfies;

out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा tnl_ptk_info ipip_tpi = अणु
	/* no tunnel info required क्रम ipip. */
	.proto = htons(ETH_P_IP),
पूर्ण;

#अगर IS_ENABLED(CONFIG_MPLS)
अटल स्थिर काष्ठा tnl_ptk_info mplsip_tpi = अणु
	/* no tunnel info required क्रम mplsip. */
	.proto = htons(ETH_P_MPLS_UC),
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक ipip_tunnel_rcv(काष्ठा sk_buff *skb, u8 ipproto)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा ip_tunnel_net *itn = net_generic(net, ipip_net_id);
	काष्ठा metadata_dst *tun_dst = शून्य;
	काष्ठा ip_tunnel *tunnel;
	स्थिर काष्ठा iphdr *iph;

	iph = ip_hdr(skb);
	tunnel = ip_tunnel_lookup(itn, skb->dev->अगरindex, TUNNEL_NO_KEY,
			iph->saddr, iph->daddr, 0);
	अगर (tunnel) अणु
		स्थिर काष्ठा tnl_ptk_info *tpi;

		अगर (tunnel->parms.iph.protocol != ipproto &&
		    tunnel->parms.iph.protocol != 0)
			जाओ drop;

		अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb))
			जाओ drop;
#अगर IS_ENABLED(CONFIG_MPLS)
		अगर (ipproto == IPPROTO_MPLS)
			tpi = &mplsip_tpi;
		अन्यथा
#पूर्ण_अगर
			tpi = &ipip_tpi;
		अगर (iptunnel_pull_header(skb, 0, tpi->proto, false))
			जाओ drop;
		अगर (tunnel->collect_md) अणु
			tun_dst = ip_tun_rx_dst(skb, 0, 0, 0);
			अगर (!tun_dst)
				वापस 0;
		पूर्ण
		वापस ip_tunnel_rcv(tunnel, skb, tpi, tun_dst, log_ecn_error);
	पूर्ण

	वापस -1;

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक ipip_rcv(काष्ठा sk_buff *skb)
अणु
	वापस ipip_tunnel_rcv(skb, IPPROTO_IPIP);
पूर्ण

#अगर IS_ENABLED(CONFIG_MPLS)
अटल पूर्णांक mplsip_rcv(काष्ठा sk_buff *skb)
अणु
	वापस ipip_tunnel_rcv(skb, IPPROTO_MPLS);
पूर्ण
#पूर्ण_अगर

/*
 *	This function assumes it is being called from dev_queue_xmit()
 *	and that skb is filled properly by that function.
 */
अटल netdev_tx_t ipip_tunnel_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	स्थिर काष्ठा iphdr  *tiph = &tunnel->parms.iph;
	u8 ipproto;

	अगर (!pskb_inet_may_pull(skb))
		जाओ tx_error;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		ipproto = IPPROTO_IPIP;
		अवरोध;
#अगर IS_ENABLED(CONFIG_MPLS)
	हाल htons(ETH_P_MPLS_UC):
		ipproto = IPPROTO_MPLS;
		अवरोध;
#पूर्ण_अगर
	शेष:
		जाओ tx_error;
	पूर्ण

	अगर (tiph->protocol != ipproto && tiph->protocol != 0)
		जाओ tx_error;

	अगर (iptunnel_handle_offloads(skb, SKB_GSO_IPXIP4))
		जाओ tx_error;

	skb_set_inner_ipproto(skb, ipproto);

	अगर (tunnel->collect_md)
		ip_md_tunnel_xmit(skb, dev, ipproto, 0);
	अन्यथा
		ip_tunnel_xmit(skb, dev, tiph, ipproto);
	वापस NETDEV_TX_OK;

tx_error:
	kमुक्त_skb(skb);

	dev->stats.tx_errors++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल bool ipip_tunnel_ioctl_verअगरy_protocol(u8 ipproto)
अणु
	चयन (ipproto) अणु
	हाल 0:
	हाल IPPROTO_IPIP:
#अगर IS_ENABLED(CONFIG_MPLS)
	हाल IPPROTO_MPLS:
#पूर्ण_अगर
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
ipip_tunnel_ctl(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p, पूर्णांक cmd)
अणु
	अगर (cmd == SIOCADDTUNNEL || cmd == SIOCCHGTUNNEL) अणु
		अगर (p->iph.version != 4 ||
		    !ipip_tunnel_ioctl_verअगरy_protocol(p->iph.protocol) ||
		    p->iph.ihl != 5 || (p->iph.frag_off & htons(~IP_DF)))
			वापस -EINVAL;
	पूर्ण

	p->i_key = p->o_key = 0;
	p->i_flags = p->o_flags = 0;
	वापस ip_tunnel_ctl(dev, p, cmd);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ipip_netdev_ops = अणु
	.nकरो_init       = ipip_tunnel_init,
	.nकरो_uninit     = ip_tunnel_uninit,
	.nकरो_start_xmit	= ipip_tunnel_xmit,
	.nकरो_करो_ioctl	= ip_tunnel_ioctl,
	.nकरो_change_mtu = ip_tunnel_change_mtu,
	.nकरो_get_stats64 = dev_get_tstats64,
	.nकरो_get_अगरlink = ip_tunnel_get_अगरlink,
	.nकरो_tunnel_ctl	= ipip_tunnel_ctl,
पूर्ण;

#घोषणा IPIP_FEATURES (NETIF_F_SG |		\
		       NETIF_F_FRAGLIST |	\
		       NETIF_F_HIGHDMA |	\
		       NETIF_F_GSO_SOFTWARE |	\
		       NETIF_F_HW_CSUM)

अटल व्योम ipip_tunnel_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops		= &ipip_netdev_ops;
	dev->header_ops		= &ip_tunnel_header_ops;

	dev->type		= ARPHRD_TUNNEL;
	dev->flags		= IFF_NOARP;
	dev->addr_len		= 4;
	dev->features		|= NETIF_F_LLTX;
	netअगर_keep_dst(dev);

	dev->features		|= IPIP_FEATURES;
	dev->hw_features	|= IPIP_FEATURES;
	ip_tunnel_setup(dev, ipip_net_id);
पूर्ण

अटल पूर्णांक ipip_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);

	स_नकल(dev->dev_addr, &tunnel->parms.iph.saddr, 4);
	स_नकल(dev->broadcast, &tunnel->parms.iph.daddr, 4);

	tunnel->tun_hlen = 0;
	tunnel->hlen = tunnel->tun_hlen + tunnel->encap_hlen;
	वापस ip_tunnel_init(dev);
पूर्ण

अटल पूर्णांक ipip_tunnel_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				काष्ठा netlink_ext_ack *extack)
अणु
	u8 proto;

	अगर (!data || !data[IFLA_IPTUN_PROTO])
		वापस 0;

	proto = nla_get_u8(data[IFLA_IPTUN_PROTO]);
	अगर (proto != IPPROTO_IPIP && proto != IPPROTO_MPLS && proto != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम ipip_netlink_parms(काष्ठा nlattr *data[],
			       काष्ठा ip_tunnel_parm *parms, bool *collect_md,
			       __u32 *fwmark)
अणु
	स_रखो(parms, 0, माप(*parms));

	parms->iph.version = 4;
	parms->iph.protocol = IPPROTO_IPIP;
	parms->iph.ihl = 5;
	*collect_md = false;

	अगर (!data)
		वापस;

	अगर (data[IFLA_IPTUN_LINK])
		parms->link = nla_get_u32(data[IFLA_IPTUN_LINK]);

	अगर (data[IFLA_IPTUN_LOCAL])
		parms->iph.saddr = nla_get_in_addr(data[IFLA_IPTUN_LOCAL]);

	अगर (data[IFLA_IPTUN_REMOTE])
		parms->iph.daddr = nla_get_in_addr(data[IFLA_IPTUN_REMOTE]);

	अगर (data[IFLA_IPTUN_TTL]) अणु
		parms->iph.ttl = nla_get_u8(data[IFLA_IPTUN_TTL]);
		अगर (parms->iph.ttl)
			parms->iph.frag_off = htons(IP_DF);
	पूर्ण

	अगर (data[IFLA_IPTUN_TOS])
		parms->iph.tos = nla_get_u8(data[IFLA_IPTUN_TOS]);

	अगर (data[IFLA_IPTUN_PROTO])
		parms->iph.protocol = nla_get_u8(data[IFLA_IPTUN_PROTO]);

	अगर (!data[IFLA_IPTUN_PMTUDISC] || nla_get_u8(data[IFLA_IPTUN_PMTUDISC]))
		parms->iph.frag_off = htons(IP_DF);

	अगर (data[IFLA_IPTUN_COLLECT_METADATA])
		*collect_md = true;

	अगर (data[IFLA_IPTUN_FWMARK])
		*fwmark = nla_get_u32(data[IFLA_IPTUN_FWMARK]);
पूर्ण

/* This function वापसs true when ENCAP attributes are present in the nl msg */
अटल bool ipip_netlink_encap_parms(काष्ठा nlattr *data[],
				     काष्ठा ip_tunnel_encap *ipencap)
अणु
	bool ret = false;

	स_रखो(ipencap, 0, माप(*ipencap));

	अगर (!data)
		वापस ret;

	अगर (data[IFLA_IPTUN_ENCAP_TYPE]) अणु
		ret = true;
		ipencap->type = nla_get_u16(data[IFLA_IPTUN_ENCAP_TYPE]);
	पूर्ण

	अगर (data[IFLA_IPTUN_ENCAP_FLAGS]) अणु
		ret = true;
		ipencap->flags = nla_get_u16(data[IFLA_IPTUN_ENCAP_FLAGS]);
	पूर्ण

	अगर (data[IFLA_IPTUN_ENCAP_SPORT]) अणु
		ret = true;
		ipencap->sport = nla_get_be16(data[IFLA_IPTUN_ENCAP_SPORT]);
	पूर्ण

	अगर (data[IFLA_IPTUN_ENCAP_DPORT]) अणु
		ret = true;
		ipencap->dport = nla_get_be16(data[IFLA_IPTUN_ENCAP_DPORT]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ipip_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा ip_tunnel_parm p;
	काष्ठा ip_tunnel_encap ipencap;
	__u32 fwmark = 0;

	अगर (ipip_netlink_encap_parms(data, &ipencap)) अणु
		पूर्णांक err = ip_tunnel_encap_setup(t, &ipencap);

		अगर (err < 0)
			वापस err;
	पूर्ण

	ipip_netlink_parms(data, &p, &t->collect_md, &fwmark);
	वापस ip_tunnel_newlink(dev, tb, &p, fwmark);
पूर्ण

अटल पूर्णांक ipip_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			   काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा ip_tunnel_parm p;
	काष्ठा ip_tunnel_encap ipencap;
	bool collect_md;
	__u32 fwmark = t->fwmark;

	अगर (ipip_netlink_encap_parms(data, &ipencap)) अणु
		पूर्णांक err = ip_tunnel_encap_setup(t, &ipencap);

		अगर (err < 0)
			वापस err;
	पूर्ण

	ipip_netlink_parms(data, &p, &collect_md, &fwmark);
	अगर (collect_md)
		वापस -EINVAL;

	अगर (((dev->flags & IFF_POINTOPOINT) && !p.iph.daddr) ||
	    (!(dev->flags & IFF_POINTOPOINT) && p.iph.daddr))
		वापस -EINVAL;

	वापस ip_tunnel_changelink(dev, tb, &p, fwmark);
पूर्ण

अटल माप_प्रकार ipip_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_IPTUN_LINK */
		nla_total_size(4) +
		/* IFLA_IPTUN_LOCAL */
		nla_total_size(4) +
		/* IFLA_IPTUN_REMOTE */
		nla_total_size(4) +
		/* IFLA_IPTUN_TTL */
		nla_total_size(1) +
		/* IFLA_IPTUN_TOS */
		nla_total_size(1) +
		/* IFLA_IPTUN_PROTO */
		nla_total_size(1) +
		/* IFLA_IPTUN_PMTUDISC */
		nla_total_size(1) +
		/* IFLA_IPTUN_ENCAP_TYPE */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_FLAGS */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_SPORT */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_DPORT */
		nla_total_size(2) +
		/* IFLA_IPTUN_COLLECT_METADATA */
		nla_total_size(0) +
		/* IFLA_IPTUN_FWMARK */
		nla_total_size(4) +
		0;
पूर्ण

अटल पूर्णांक ipip_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा ip_tunnel_parm *parm = &tunnel->parms;

	अगर (nla_put_u32(skb, IFLA_IPTUN_LINK, parm->link) ||
	    nla_put_in_addr(skb, IFLA_IPTUN_LOCAL, parm->iph.saddr) ||
	    nla_put_in_addr(skb, IFLA_IPTUN_REMOTE, parm->iph.daddr) ||
	    nla_put_u8(skb, IFLA_IPTUN_TTL, parm->iph.ttl) ||
	    nla_put_u8(skb, IFLA_IPTUN_TOS, parm->iph.tos) ||
	    nla_put_u8(skb, IFLA_IPTUN_PROTO, parm->iph.protocol) ||
	    nla_put_u8(skb, IFLA_IPTUN_PMTUDISC,
		       !!(parm->iph.frag_off & htons(IP_DF))) ||
	    nla_put_u32(skb, IFLA_IPTUN_FWMARK, tunnel->fwmark))
		जाओ nla_put_failure;

	अगर (nla_put_u16(skb, IFLA_IPTUN_ENCAP_TYPE,
			tunnel->encap.type) ||
	    nla_put_be16(skb, IFLA_IPTUN_ENCAP_SPORT,
			 tunnel->encap.sport) ||
	    nla_put_be16(skb, IFLA_IPTUN_ENCAP_DPORT,
			 tunnel->encap.dport) ||
	    nla_put_u16(skb, IFLA_IPTUN_ENCAP_FLAGS,
			tunnel->encap.flags))
		जाओ nla_put_failure;

	अगर (tunnel->collect_md)
		अगर (nla_put_flag(skb, IFLA_IPTUN_COLLECT_METADATA))
			जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy ipip_policy[IFLA_IPTUN_MAX + 1] = अणु
	[IFLA_IPTUN_LINK]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_LOCAL]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_REMOTE]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_TTL]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_TOS]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_PROTO]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_PMTUDISC]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_ENCAP_TYPE]		= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_ENCAP_FLAGS]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_ENCAP_SPORT]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_ENCAP_DPORT]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_COLLECT_METADATA]	= अणु .type = NLA_FLAG पूर्ण,
	[IFLA_IPTUN_FWMARK]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा rtnl_link_ops ipip_link_ops __पढ़ो_mostly = अणु
	.kind		= "ipip",
	.maxtype	= IFLA_IPTUN_MAX,
	.policy		= ipip_policy,
	.priv_size	= माप(काष्ठा ip_tunnel),
	.setup		= ipip_tunnel_setup,
	.validate	= ipip_tunnel_validate,
	.newlink	= ipip_newlink,
	.changelink	= ipip_changelink,
	.dellink	= ip_tunnel_dellink,
	.get_size	= ipip_get_size,
	.fill_info	= ipip_fill_info,
	.get_link_net	= ip_tunnel_get_link_net,
पूर्ण;

अटल काष्ठा xfrm_tunnel ipip_handler __पढ़ो_mostly = अणु
	.handler	=	ipip_rcv,
	.err_handler	=	ipip_err,
	.priority	=	1,
पूर्ण;

#अगर IS_ENABLED(CONFIG_MPLS)
अटल काष्ठा xfrm_tunnel mplsip_handler __पढ़ो_mostly = अणु
	.handler	=	mplsip_rcv,
	.err_handler	=	ipip_err,
	.priority	=	1,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __net_init ipip_init_net(काष्ठा net *net)
अणु
	वापस ip_tunnel_init_net(net, ipip_net_id, &ipip_link_ops, "tunl0");
पूर्ण

अटल व्योम __net_निकास ipip_निकास_batch_net(काष्ठा list_head *list_net)
अणु
	ip_tunnel_delete_nets(list_net, ipip_net_id, &ipip_link_ops);
पूर्ण

अटल काष्ठा pernet_operations ipip_net_ops = अणु
	.init = ipip_init_net,
	.निकास_batch = ipip_निकास_batch_net,
	.id   = &ipip_net_id,
	.size = माप(काष्ठा ip_tunnel_net),
पूर्ण;

अटल पूर्णांक __init ipip_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("ipip: IPv4 and MPLS over IPv4 tunneling driver\n");

	err = रेजिस्टर_pernet_device(&ipip_net_ops);
	अगर (err < 0)
		वापस err;
	err = xfrm4_tunnel_रेजिस्टर(&ipip_handler, AF_INET);
	अगर (err < 0) अणु
		pr_info("%s: can't register tunnel\n", __func__);
		जाओ xfrm_tunnel_ipip_failed;
	पूर्ण
#अगर IS_ENABLED(CONFIG_MPLS)
	err = xfrm4_tunnel_रेजिस्टर(&mplsip_handler, AF_MPLS);
	अगर (err < 0) अणु
		pr_info("%s: can't register tunnel\n", __func__);
		जाओ xfrm_tunnel_mplsip_failed;
	पूर्ण
#पूर्ण_अगर
	err = rtnl_link_रेजिस्टर(&ipip_link_ops);
	अगर (err < 0)
		जाओ rtnl_link_failed;

out:
	वापस err;

rtnl_link_failed:
#अगर IS_ENABLED(CONFIG_MPLS)
	xfrm4_tunnel_deरेजिस्टर(&mplsip_handler, AF_MPLS);
xfrm_tunnel_mplsip_failed:

#पूर्ण_अगर
	xfrm4_tunnel_deरेजिस्टर(&ipip_handler, AF_INET);
xfrm_tunnel_ipip_failed:
	unरेजिस्टर_pernet_device(&ipip_net_ops);
	जाओ out;
पूर्ण

अटल व्योम __निकास ipip_fini(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&ipip_link_ops);
	अगर (xfrm4_tunnel_deरेजिस्टर(&ipip_handler, AF_INET))
		pr_info("%s: can't deregister tunnel\n", __func__);
#अगर IS_ENABLED(CONFIG_MPLS)
	अगर (xfrm4_tunnel_deरेजिस्टर(&mplsip_handler, AF_MPLS))
		pr_info("%s: can't deregister tunnel\n", __func__);
#पूर्ण_अगर
	unरेजिस्टर_pernet_device(&ipip_net_ops);
पूर्ण

module_init(ipip_init);
module_निकास(ipip_fini);
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK("ipip");
MODULE_ALIAS_NETDEV("tunl0");
