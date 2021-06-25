<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Automatic Configuration of IP -- use DHCP, BOOTP, RARP, or
 *  user-supplied inक्रमmation to configure own IP address and routes.
 *
 *  Copyright (C) 1996-1998 Martin Mares <mj@atrey.karlin.mff.cuni.cz>
 *
 *  Derived from network configuration code in fs/nfs/nfsroot.c,
 *  originally Copyright (C) 1995, 1996 Gero Kuhlmann and me.
 *
 *  BOOTP rewritten to स्थिरruct and analyse packets itself instead
 *  of misusing the IP layer. num_bugs_causing_wrong_arp_replies--;
 *					     -- MJ, December 1998
 *
 *  Fixed ip_स्वतः_config_setup calling at startup in the new "Linker Magic"
 *  initialization scheme.
 *	- Arnalकरो Carvalho de Melo <acme@conectiva.com.br>, 08/11/1999
 *
 *  DHCP support added.  To users this looks like a whole separate
 *  protocol, but we know it's just a bag on the side of BOOTP.
 *		-- Chip Salzenberg <chip@valinux.com>, May 2000
 *
 *  Ported DHCP support from 2.2.16 to 2.4.0-test4
 *              -- Eric Biederman <ebiederman@lnxi.com>, 30 Aug 2000
 *
 *  Merged changes from 2.2.19 पूर्णांकo 2.4.3
 *              -- Eric Biederman <ebiederman@lnxi.com>, 22 April Aug 2001
 *
 *  Multiple Nameservers in /proc/net/pnp
 *              --  Josef Siemes <jsiemes@web.de>, Aug 2002
 *
 *  NTP servers in /proc/net/ipconfig/ntp_servers
 *              --  Chris Novakovic <chris@chrisn.me.uk>, April 2018
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/init.h>
#समावेश <linux/utsname.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर.h>
#समावेश <linux/inet.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/socket.h>
#समावेश <linux/route.h>
#समावेश <linux/udp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/major.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/delay.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/arp.h>
#समावेश <net/ip.h>
#समावेश <net/ipconfig.h>
#समावेश <net/route.h>

#समावेश <linux/uaccess.h>
#समावेश <net/checksum.h>
#समावेश <यंत्र/processor.h>

#अगर defined(CONFIG_IP_PNP_DHCP)
#घोषणा IPCONFIG_DHCP
#पूर्ण_अगर
#अगर defined(CONFIG_IP_PNP_BOOTP) || defined(CONFIG_IP_PNP_DHCP)
#घोषणा IPCONFIG_BOOTP
#पूर्ण_अगर
#अगर defined(CONFIG_IP_PNP_RARP)
#घोषणा IPCONFIG_RARP
#पूर्ण_अगर
#अगर defined(IPCONFIG_BOOTP) || defined(IPCONFIG_RARP)
#घोषणा IPCONFIG_DYNAMIC
#पूर्ण_अगर

/* Define the मित्रly delay beक्रमe and after खोलोing net devices */
#घोषणा CONF_POST_OPEN		10	/* After खोलोing: 10 msecs */

/* Define the समयout क्रम रुकोing क्रम a DHCP/BOOTP/RARP reply */
#घोषणा CONF_OPEN_RETRIES 	2	/* (Re)खोलो devices twice */
#घोषणा CONF_SEND_RETRIES 	6	/* Send six requests per खोलो */
#घोषणा CONF_BASE_TIMEOUT	(HZ*2)	/* Initial समयout: 2 seconds */
#घोषणा CONF_TIMEOUT_RANDOM	(HZ)	/* Maximum amount of अक्रमomization */
#घोषणा CONF_TIMEOUT_MULT	*7/4	/* Rate of समयout growth */
#घोषणा CONF_TIMEOUT_MAX	(HZ*30)	/* Maximum allowed समयout */
#घोषणा CONF_NAMESERVERS_MAX   3       /* Maximum number of nameservers
					   - '3' from resolv.h */
#घोषणा CONF_NTP_SERVERS_MAX   3	/* Maximum number of NTP servers */

#घोषणा NONE cpu_to_be32(INADDR_NONE)
#घोषणा ANY cpu_to_be32(INADDR_ANY)

/* Wait क्रम carrier समयout शेष in seconds */
अटल अचिन्हित पूर्णांक carrier_समयout = 120;

/*
 * Public IP configuration
 */

/* This is used by platक्रमms which might be able to set the ipconfig
 * variables using firmware environment vars.  If this is set, it will
 * ignore such firmware variables.
 */
पूर्णांक ic_set_manually __initdata = 0;		/* IPconfig parameters set manually */

अटल पूर्णांक ic_enable __initdata;		/* IP config enabled? */

/* Protocol choice */
पूर्णांक ic_proto_enabled __initdata = 0
#अगर_घोषित IPCONFIG_BOOTP
			| IC_BOOTP
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_PNP_DHCP
			| IC_USE_DHCP
#पूर्ण_अगर
#अगर_घोषित IPCONFIG_RARP
			| IC_RARP
#पूर्ण_अगर
			;

अटल पूर्णांक ic_host_name_set __initdata;	/* Host name set by us? */

__be32 ic_myaddr = NONE;		/* My IP address */
अटल __be32 ic_neपंचांगask = NONE;	/* Neपंचांगask क्रम local subnet */
__be32 ic_gateway = NONE;	/* Gateway IP address */

#अगर_घोषित IPCONFIG_DYNAMIC
अटल __be32 ic_addrservaddr = NONE;	/* IP Address of the IP addresses'server */
#पूर्ण_अगर

__be32 ic_servaddr = NONE;	/* Boot server IP address */

__be32 root_server_addr = NONE;	/* Address of NFS server */
u8 root_server_path[256] = अणु 0, पूर्ण;	/* Path to mount as root */

/* venकरोr class identअगरier */
अटल अक्षर venकरोr_class_identअगरier[253] __initdata;

#अगर defined(CONFIG_IP_PNP_DHCP)
अटल अक्षर dhcp_client_identअगरier[253] __initdata;
#पूर्ण_अगर

/* Persistent data: */

#अगर_घोषित IPCONFIG_DYNAMIC
अटल पूर्णांक ic_proto_used;			/* Protocol used, अगर any */
#अन्यथा
#घोषणा ic_proto_used 0
#पूर्ण_अगर
अटल __be32 ic_nameservers[CONF_NAMESERVERS_MAX]; /* DNS Server IP addresses */
अटल __be32 ic_ntp_servers[CONF_NTP_SERVERS_MAX]; /* NTP server IP addresses */
अटल u8 ic_करोमुख्य[64];		/* DNS (not NIS) करोमुख्य name */

/*
 * Private state.
 */

/* Name of user-selected boot device */
अटल अक्षर user_dev_name[IFNAMSIZ] __initdata = अणु 0, पूर्ण;

/* Protocols supported by available पूर्णांकerfaces */
अटल पूर्णांक ic_proto_have_अगर __initdata;

/* MTU क्रम boot device */
अटल पूर्णांक ic_dev_mtu __initdata;

#अगर_घोषित IPCONFIG_DYNAMIC
अटल DEFINE_SPINLOCK(ic_recv_lock);
अटल अस्थिर पूर्णांक ic_got_reply __initdata;    /* Proto(s) that replied */
#पूर्ण_अगर
#अगर_घोषित IPCONFIG_DHCP
अटल पूर्णांक ic_dhcp_msgtype __initdata;	/* DHCP msg type received */
#पूर्ण_अगर


/*
 *	Network devices
 */

काष्ठा ic_device अणु
	काष्ठा ic_device *next;
	काष्ठा net_device *dev;
	अचिन्हित लघु flags;
	लघु able;
	__be32 xid;
पूर्ण;

अटल काष्ठा ic_device *ic_first_dev __initdata;	/* List of खोलो device */
अटल काष्ठा ic_device *ic_dev __initdata;		/* Selected device */

अटल bool __init ic_is_init_dev(काष्ठा net_device *dev)
अणु
	अगर (dev->flags & IFF_LOOPBACK)
		वापस false;
	वापस user_dev_name[0] ? !म_भेद(dev->name, user_dev_name) :
	    (!(dev->flags & IFF_LOOPBACK) &&
	     (dev->flags & (IFF_POINTOPOINT|IFF_BROADCAST)) &&
	     म_भेदन(dev->name, "dummy", 5));
पूर्ण

अटल पूर्णांक __init ic_खोलो_devs(व्योम)
अणु
	काष्ठा ic_device *d, **last;
	काष्ठा net_device *dev;
	अचिन्हित लघु oflags;
	अचिन्हित दीर्घ start, next_msg;

	last = &ic_first_dev;
	rtnl_lock();

	/* bring loopback device up first */
	क्रम_each_netdev(&init_net, dev) अणु
		अगर (!(dev->flags & IFF_LOOPBACK))
			जारी;
		अगर (dev_change_flags(dev, dev->flags | IFF_UP, शून्य) < 0)
			pr_err("IP-Config: Failed to open %s\n", dev->name);
	पूर्ण

	क्रम_each_netdev(&init_net, dev) अणु
		अगर (ic_is_init_dev(dev)) अणु
			पूर्णांक able = 0;
			अगर (dev->mtu >= 364)
				able |= IC_BOOTP;
			अन्यथा
				pr_warn("DHCP/BOOTP: Ignoring device %s, MTU %d too small\n",
					dev->name, dev->mtu);
			अगर (!(dev->flags & IFF_NOARP))
				able |= IC_RARP;
			able &= ic_proto_enabled;
			अगर (ic_proto_enabled && !able)
				जारी;
			oflags = dev->flags;
			अगर (dev_change_flags(dev, oflags | IFF_UP, शून्य) < 0) अणु
				pr_err("IP-Config: Failed to open %s\n",
				       dev->name);
				जारी;
			पूर्ण
			अगर (!(d = kदो_स्मृति(माप(काष्ठा ic_device), GFP_KERNEL))) अणु
				rtnl_unlock();
				वापस -ENOMEM;
			पूर्ण
			d->dev = dev;
			*last = d;
			last = &d->next;
			d->flags = oflags;
			d->able = able;
			अगर (able & IC_BOOTP)
				get_अक्रमom_bytes(&d->xid, माप(__be32));
			अन्यथा
				d->xid = 0;
			ic_proto_have_अगर |= able;
			pr_debug("IP-Config: %s UP (able=%d, xid=%08x)\n",
				 dev->name, able, d->xid);
		पूर्ण
	पूर्ण

	/* no poपूर्णांक in रुकोing अगर we could not bring up at least one device */
	अगर (!ic_first_dev)
		जाओ have_carrier;

	/* रुको क्रम a carrier on at least one device */
	start = jअगरfies;
	next_msg = start + msecs_to_jअगरfies(20000);
	जबतक (समय_beक्रमe(jअगरfies, start +
			   msecs_to_jअगरfies(carrier_समयout * 1000))) अणु
		पूर्णांक रुको, elapsed;

		क्रम_each_netdev(&init_net, dev)
			अगर (ic_is_init_dev(dev) && netअगर_carrier_ok(dev))
				जाओ have_carrier;

		msleep(1);

		अगर (समय_beक्रमe(jअगरfies, next_msg))
			जारी;

		elapsed = jअगरfies_to_msecs(jअगरfies - start);
		रुको = (carrier_समयout * 1000 - elapsed + 500) / 1000;
		pr_info("Waiting up to %d more seconds for network.\n", रुको);
		next_msg = jअगरfies + msecs_to_jअगरfies(20000);
	पूर्ण
have_carrier:
	rtnl_unlock();

	*last = शून्य;

	अगर (!ic_first_dev) अणु
		अगर (user_dev_name[0])
			pr_err("IP-Config: Device `%s' not found\n",
			       user_dev_name);
		अन्यथा
			pr_err("IP-Config: No network devices available\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/* Close all network पूर्णांकerfaces except the one we've स्वतःconfigured, and its
 * lowers, in हाल it's a stacked भव पूर्णांकerface.
 */
अटल व्योम __init ic_बंद_devs(व्योम)
अणु
	काष्ठा net_device *selected_dev = ic_dev ? ic_dev->dev : शून्य;
	काष्ठा ic_device *d, *next;
	काष्ठा net_device *dev;

	rtnl_lock();
	next = ic_first_dev;
	जबतक ((d = next)) अणु
		bool bring_करोwn = (d != ic_dev);
		काष्ठा net_device *lower;
		काष्ठा list_head *iter;

		next = d->next;
		dev = d->dev;

		अगर (selected_dev) अणु
			netdev_क्रम_each_lower_dev(selected_dev, lower, iter) अणु
				अगर (dev == lower) अणु
					bring_करोwn = false;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (bring_करोwn) अणु
			pr_debug("IP-Config: Downing %s\n", dev->name);
			dev_change_flags(dev, d->flags, शून्य);
		पूर्ण
		kमुक्त(d);
	पूर्ण
	rtnl_unlock();
पूर्ण

/*
 *	Interface to various network functions.
 */

अटल अंतरभूत व्योम
set_sockaddr(काष्ठा sockaddr_in *sin, __be32 addr, __be16 port)
अणु
	sin->sin_family = AF_INET;
	sin->sin_addr.s_addr = addr;
	sin->sin_port = port;
पूर्ण

/*
 *	Set up पूर्णांकerface addresses and routes.
 */

अटल पूर्णांक __init ic_setup_अगर(व्योम)
अणु
	काष्ठा अगरreq ir;
	काष्ठा sockaddr_in *sin = (व्योम *) &ir.अगरr_अगरru.अगरru_addr;
	पूर्णांक err;

	स_रखो(&ir, 0, माप(ir));
	म_नकल(ir.अगरr_अगरrn.अगरrn_name, ic_dev->dev->name);
	set_sockaddr(sin, ic_myaddr, 0);
	अगर ((err = devinet_ioctl(&init_net, SIOCSIFADDR, &ir)) < 0) अणु
		pr_err("IP-Config: Unable to set interface address (%d)\n",
		       err);
		वापस -1;
	पूर्ण
	set_sockaddr(sin, ic_neपंचांगask, 0);
	अगर ((err = devinet_ioctl(&init_net, SIOCSIFNETMASK, &ir)) < 0) अणु
		pr_err("IP-Config: Unable to set interface netmask (%d)\n",
		       err);
		वापस -1;
	पूर्ण
	set_sockaddr(sin, ic_myaddr | ~ic_neपंचांगask, 0);
	अगर ((err = devinet_ioctl(&init_net, SIOCSIFBRDADDR, &ir)) < 0) अणु
		pr_err("IP-Config: Unable to set interface broadcast address (%d)\n",
		       err);
		वापस -1;
	पूर्ण
	/* Handle the हाल where we need non-standard MTU on the boot link (a network
	 * using jumbo frames, क्रम instance).  If we can't set the mtu, don't error
	 * out, we'll try to muddle aदीर्घ.
	 */
	अगर (ic_dev_mtu != 0) अणु
		rtnl_lock();
		अगर ((err = dev_set_mtu(ic_dev->dev, ic_dev_mtu)) < 0)
			pr_err("IP-Config: Unable to set interface mtu to %d (%d)\n",
			       ic_dev_mtu, err);
		rtnl_unlock();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init ic_setup_routes(व्योम)
अणु
	/* No need to setup device routes, only the शेष route... */

	अगर (ic_gateway != NONE) अणु
		काष्ठा rtentry rm;
		पूर्णांक err;

		स_रखो(&rm, 0, माप(rm));
		अगर ((ic_gateway ^ ic_myaddr) & ic_neपंचांगask) अणु
			pr_err("IP-Config: Gateway not on directly connected network\n");
			वापस -1;
		पूर्ण
		set_sockaddr((काष्ठा sockaddr_in *) &rm.rt_dst, 0, 0);
		set_sockaddr((काष्ठा sockaddr_in *) &rm.rt_genmask, 0, 0);
		set_sockaddr((काष्ठा sockaddr_in *) &rm.rt_gateway, ic_gateway, 0);
		rm.rt_flags = RTF_UP | RTF_GATEWAY;
		अगर ((err = ip_rt_ioctl(&init_net, SIOCADDRT, &rm)) < 0) अणु
			pr_err("IP-Config: Cannot add default route (%d)\n",
			       err);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Fill in शेष values क्रम all missing parameters.
 */

अटल पूर्णांक __init ic_शेषs(व्योम)
अणु
	/*
	 *	At this poपूर्णांक we have no userspace running so need not
	 *	claim locks on प्रणाली_utsname
	 */

	अगर (!ic_host_name_set)
		प्र_लिखो(init_utsname()->nodename, "%pI4", &ic_myaddr);

	अगर (root_server_addr == NONE)
		root_server_addr = ic_servaddr;

	अगर (ic_neपंचांगask == NONE) अणु
		अगर (IN_CLASSA(ntohl(ic_myaddr)))
			ic_neपंचांगask = htonl(IN_CLASSA_NET);
		अन्यथा अगर (IN_CLASSB(ntohl(ic_myaddr)))
			ic_neपंचांगask = htonl(IN_CLASSB_NET);
		अन्यथा अगर (IN_CLASSC(ntohl(ic_myaddr)))
			ic_neपंचांगask = htonl(IN_CLASSC_NET);
		अन्यथा अगर (IN_CLASSE(ntohl(ic_myaddr)))
			ic_neपंचांगask = htonl(IN_CLASSE_NET);
		अन्यथा अणु
			pr_err("IP-Config: Unable to guess netmask for address %pI4\n",
			       &ic_myaddr);
			वापस -1;
		पूर्ण
		pr_notice("IP-Config: Guessing netmask %pI4\n",
			  &ic_neपंचांगask);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	RARP support.
 */

#अगर_घोषित IPCONFIG_RARP

अटल पूर्णांक ic_rarp_recv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *pt, काष्ठा net_device *orig_dev);

अटल काष्ठा packet_type rarp_packet_type __initdata = अणु
	.type =	cpu_to_be16(ETH_P_RARP),
	.func =	ic_rarp_recv,
पूर्ण;

अटल अंतरभूत व्योम __init ic_rarp_init(व्योम)
अणु
	dev_add_pack(&rarp_packet_type);
पूर्ण

अटल अंतरभूत व्योम __init ic_rarp_cleanup(व्योम)
अणु
	dev_हटाओ_pack(&rarp_packet_type);
पूर्ण

/*
 *  Process received RARP packet.
 */
अटल पूर्णांक __init
ic_rarp_recv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा arphdr *rarp;
	अचिन्हित अक्षर *rarp_ptr;
	__be32 sip, tip;
	अचिन्हित अक्षर *tha;		/* t क्रम "target" */
	काष्ठा ic_device *d;

	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ drop;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस NET_RX_DROP;

	अगर (!pskb_may_pull(skb, माप(काष्ठा arphdr)))
		जाओ drop;

	/* Basic sanity checks can be करोne without the lock.  */
	rarp = (काष्ठा arphdr *)skb_transport_header(skb);

	/* If this test करोesn't pass, it's not IP, or we should
	 * ignore it anyway.
	 */
	अगर (rarp->ar_hln != dev->addr_len || dev->type != ntohs(rarp->ar_hrd))
		जाओ drop;

	/* If it's not a RARP reply, delete it. */
	अगर (rarp->ar_op != htons(ARPOP_RREPLY))
		जाओ drop;

	/* If it's not Ethernet, delete it. */
	अगर (rarp->ar_pro != htons(ETH_P_IP))
		जाओ drop;

	अगर (!pskb_may_pull(skb, arp_hdr_len(dev)))
		जाओ drop;

	/* OK, it is all there and looks valid, process... */
	rarp = (काष्ठा arphdr *)skb_transport_header(skb);
	rarp_ptr = (अचिन्हित अक्षर *) (rarp + 1);

	/* One reply at a समय, please. */
	spin_lock(&ic_recv_lock);

	/* If we alपढ़ोy have a reply, just drop the packet */
	अगर (ic_got_reply)
		जाओ drop_unlock;

	/* Find the ic_device that the packet arrived on */
	d = ic_first_dev;
	जबतक (d && d->dev != dev)
		d = d->next;
	अगर (!d)
		जाओ drop_unlock;	/* should never happen */

	/* Extract variable-width fields */
	rarp_ptr += dev->addr_len;
	स_नकल(&sip, rarp_ptr, 4);
	rarp_ptr += 4;
	tha = rarp_ptr;
	rarp_ptr += dev->addr_len;
	स_नकल(&tip, rarp_ptr, 4);

	/* Discard packets which are not meant क्रम us. */
	अगर (स_भेद(tha, dev->dev_addr, dev->addr_len))
		जाओ drop_unlock;

	/* Discard packets which are not from specअगरied server. */
	अगर (ic_servaddr != NONE && ic_servaddr != sip)
		जाओ drop_unlock;

	/* We have a winner! */
	ic_dev = d;
	अगर (ic_myaddr == NONE)
		ic_myaddr = tip;
	ic_servaddr = sip;
	ic_addrservaddr = sip;
	ic_got_reply = IC_RARP;

drop_unlock:
	/* Show's over.  Nothing to see here.  */
	spin_unlock(&ic_recv_lock);

drop:
	/* Throw the packet out. */
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण


/*
 *  Send RARP request packet over a single पूर्णांकerface.
 */
अटल व्योम __init ic_rarp_send_अगर(काष्ठा ic_device *d)
अणु
	काष्ठा net_device *dev = d->dev;
	arp_send(ARPOP_RREQUEST, ETH_P_RARP, 0, dev, 0, शून्य,
		 dev->dev_addr, dev->dev_addr);
पूर्ण
#पूर्ण_अगर

/*
 *  Predefine Nameservers
 */
अटल अंतरभूत व्योम __init ic_nameservers_predef(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CONF_NAMESERVERS_MAX; i++)
		ic_nameservers[i] = NONE;
पूर्ण

/* Predefine NTP servers */
अटल अंतरभूत व्योम __init ic_ntp_servers_predef(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CONF_NTP_SERVERS_MAX; i++)
		ic_ntp_servers[i] = NONE;
पूर्ण

/*
 *	DHCP/BOOTP support.
 */

#अगर_घोषित IPCONFIG_BOOTP

काष्ठा bootp_pkt अणु		/* BOOTP packet क्रमmat */
	काष्ठा iphdr iph;	/* IP header */
	काष्ठा udphdr udph;	/* UDP header */
	u8 op;			/* 1=request, 2=reply */
	u8 htype;		/* HW address type */
	u8 hlen;		/* HW address length */
	u8 hops;		/* Used only by gateways */
	__be32 xid;		/* Transaction ID */
	__be16 secs;		/* Seconds since we started */
	__be16 flags;		/* Just what it says */
	__be32 client_ip;		/* Client's IP address अगर known */
	__be32 your_ip;		/* Asचिन्हित IP address */
	__be32 server_ip;		/* (Next, e.g. NFS) Server's IP address */
	__be32 relay_ip;		/* IP address of BOOTP relay */
	u8 hw_addr[16];		/* Client's HW address */
	u8 serv_name[64];	/* Server host name */
	u8 boot_file[128];	/* Name of boot file */
	u8 exten[312];		/* DHCP options / BOOTP venकरोr extensions */
पूर्ण;

/* packet ops */
#घोषणा BOOTP_REQUEST	1
#घोषणा BOOTP_REPLY	2

/* DHCP message types */
#घोषणा DHCPDISCOVER	1
#घोषणा DHCPOFFER	2
#घोषणा DHCPREQUEST	3
#घोषणा DHCPDECLINE	4
#घोषणा DHCPACK		5
#घोषणा DHCPNAK		6
#घोषणा DHCPRELEASE	7
#घोषणा DHCPINFORM	8

अटल पूर्णांक ic_bootp_recv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *pt, काष्ठा net_device *orig_dev);

अटल काष्ठा packet_type bootp_packet_type __initdata = अणु
	.type =	cpu_to_be16(ETH_P_IP),
	.func =	ic_bootp_recv,
पूर्ण;

/*
 *  Initialize DHCP/BOOTP extension fields in the request.
 */

अटल स्थिर u8 ic_bootp_cookie[4] = अणु 99, 130, 83, 99 पूर्ण;

#अगर_घोषित IPCONFIG_DHCP

अटल व्योम __init
ic_dhcp_init_options(u8 *options, काष्ठा ic_device *d)
अणु
	u8 mt = ((ic_servaddr == NONE)
		 ? DHCPDISCOVER : DHCPREQUEST);
	u8 *e = options;
	पूर्णांक len;

	pr_debug("DHCP: Sending message type %d (%s)\n", mt, d->dev->name);

	स_नकल(e, ic_bootp_cookie, 4);	/* RFC1048 Magic Cookie */
	e += 4;

	*e++ = 53;		/* DHCP message type */
	*e++ = 1;
	*e++ = mt;

	अगर (mt == DHCPREQUEST) अणु
		*e++ = 54;	/* Server ID (IP address) */
		*e++ = 4;
		स_नकल(e, &ic_servaddr, 4);
		e += 4;

		*e++ = 50;	/* Requested IP address */
		*e++ = 4;
		स_नकल(e, &ic_myaddr, 4);
		e += 4;
	पूर्ण

	/* always? */
	अणु
		अटल स्थिर u8 ic_req_params[] = अणु
			1,	/* Subnet mask */
			3,	/* Default gateway */
			6,	/* DNS server */
			12,	/* Host name */
			15,	/* Doमुख्य name */
			17,	/* Boot path */
			26,	/* MTU */
			40,	/* NIS करोमुख्य name */
			42,	/* NTP servers */
		पूर्ण;

		*e++ = 55;	/* Parameter request list */
		*e++ = माप(ic_req_params);
		स_नकल(e, ic_req_params, माप(ic_req_params));
		e += माप(ic_req_params);

		अगर (ic_host_name_set) अणु
			*e++ = 12;	/* host-name */
			len = म_माप(utsname()->nodename);
			*e++ = len;
			स_नकल(e, utsname()->nodename, len);
			e += len;
		पूर्ण
		अगर (*venकरोr_class_identअगरier) अणु
			pr_info("DHCP: sending class identifier \"%s\"\n",
				venकरोr_class_identअगरier);
			*e++ = 60;	/* Class-identअगरier */
			len = म_माप(venकरोr_class_identअगरier);
			*e++ = len;
			स_नकल(e, venकरोr_class_identअगरier, len);
			e += len;
		पूर्ण
		len = म_माप(dhcp_client_identअगरier + 1);
		/* the minimum length of identअगरier is 2, include 1 byte type,
		 * and can not be larger than the length of options
		 */
		अगर (len >= 1 && len < 312 - (e - options) - 1) अणु
			*e++ = 61;
			*e++ = len + 1;
			स_नकल(e, dhcp_client_identअगरier, len + 1);
			e += len + 1;
		पूर्ण
	पूर्ण

	*e++ = 255;	/* End of the list */
पूर्ण

#पूर्ण_अगर /* IPCONFIG_DHCP */

अटल व्योम __init ic_bootp_init_ext(u8 *e)
अणु
	स_नकल(e, ic_bootp_cookie, 4);	/* RFC1048 Magic Cookie */
	e += 4;
	*e++ = 1;		/* Subnet mask request */
	*e++ = 4;
	e += 4;
	*e++ = 3;		/* Default gateway request */
	*e++ = 4;
	e += 4;
#अगर CONF_NAMESERVERS_MAX > 0
	*e++ = 6;		/* (DNS) name server request */
	*e++ = 4 * CONF_NAMESERVERS_MAX;
	e += 4 * CONF_NAMESERVERS_MAX;
#पूर्ण_अगर
	*e++ = 12;		/* Host name request */
	*e++ = 32;
	e += 32;
	*e++ = 40;		/* NIS Doमुख्य name request */
	*e++ = 32;
	e += 32;
	*e++ = 17;		/* Boot path */
	*e++ = 40;
	e += 40;

	*e++ = 57;		/* set extension buffer size क्रम reply */
	*e++ = 2;
	*e++ = 1;		/* 128+236+8+20+14, see dhcpd sources */
	*e++ = 150;

	*e++ = 255;		/* End of the list */
पूर्ण


/*
 *  Initialize the DHCP/BOOTP mechanism.
 */
अटल अंतरभूत व्योम __init ic_bootp_init(व्योम)
अणु
	/* Re-initialise all name servers and NTP servers to NONE, in हाल any
	 * were set via the "ip=" or "nfsaddrs=" kernel command line parameters:
	 * any IP addresses specअगरied there will alपढ़ोy have been decoded but
	 * are no दीर्घer needed
	 */
	ic_nameservers_predef();
	ic_ntp_servers_predef();

	dev_add_pack(&bootp_packet_type);
पूर्ण


/*
 *  DHCP/BOOTP cleanup.
 */
अटल अंतरभूत व्योम __init ic_bootp_cleanup(व्योम)
अणु
	dev_हटाओ_pack(&bootp_packet_type);
पूर्ण


/*
 *  Send DHCP/BOOTP request to single पूर्णांकerface.
 */
अटल व्योम __init ic_bootp_send_अगर(काष्ठा ic_device *d, अचिन्हित दीर्घ jअगरfies_dअगरf)
अणु
	काष्ठा net_device *dev = d->dev;
	काष्ठा sk_buff *skb;
	काष्ठा bootp_pkt *b;
	काष्ठा iphdr *h;
	पूर्णांक hlen = LL_RESERVED_SPACE(dev);
	पूर्णांक tlen = dev->needed_tailroom;

	/* Allocate packet */
	skb = alloc_skb(माप(काष्ठा bootp_pkt) + hlen + tlen + 15,
			GFP_KERNEL);
	अगर (!skb)
		वापस;
	skb_reserve(skb, hlen);
	b = skb_put_zero(skb, माप(काष्ठा bootp_pkt));

	/* Conकाष्ठा IP header */
	skb_reset_network_header(skb);
	h = ip_hdr(skb);
	h->version = 4;
	h->ihl = 5;
	h->tot_len = htons(माप(काष्ठा bootp_pkt));
	h->frag_off = htons(IP_DF);
	h->ttl = 64;
	h->protocol = IPPROTO_UDP;
	h->daddr = htonl(INADDR_BROADCAST);
	h->check = ip_fast_csum((अचिन्हित अक्षर *) h, h->ihl);

	/* Conकाष्ठा UDP header */
	b->udph.source = htons(68);
	b->udph.dest = htons(67);
	b->udph.len = htons(माप(काष्ठा bootp_pkt) - माप(काष्ठा iphdr));
	/* UDP checksum not calculated -- explicitly allowed in BOOTP RFC */

	/* Conकाष्ठा DHCP/BOOTP header */
	b->op = BOOTP_REQUEST;
	अगर (dev->type < 256) /* check क्रम false types */
		b->htype = dev->type;
	अन्यथा अगर (dev->type == ARPHRD_FDDI)
		b->htype = ARPHRD_ETHER;
	अन्यथा अणु
		pr_warn("Unknown ARP type 0x%04x for device %s\n", dev->type,
			dev->name);
		b->htype = dev->type; /* can cause undefined behavior */
	पूर्ण

	/* server_ip and your_ip address are both alपढ़ोy zero per RFC2131 */
	b->hlen = dev->addr_len;
	स_नकल(b->hw_addr, dev->dev_addr, dev->addr_len);
	b->secs = htons(jअगरfies_dअगरf / HZ);
	b->xid = d->xid;

	/* add DHCP options or BOOTP extensions */
#अगर_घोषित IPCONFIG_DHCP
	अगर (ic_proto_enabled & IC_USE_DHCP)
		ic_dhcp_init_options(b->exten, d);
	अन्यथा
#पूर्ण_अगर
		ic_bootp_init_ext(b->exten);

	/* Chain packet करोwn the line... */
	skb->dev = dev;
	skb->protocol = htons(ETH_P_IP);
	अगर (dev_hard_header(skb, dev, ntohs(skb->protocol),
			    dev->broadcast, dev->dev_addr, skb->len) < 0) अणु
		kमुक्त_skb(skb);
		prपूर्णांकk("E");
		वापस;
	पूर्ण

	अगर (dev_queue_xmit(skb) < 0)
		prपूर्णांकk("E");
पूर्ण


/*
 *  Copy BOOTP-supplied string
 */
अटल पूर्णांक __init ic_bootp_string(अक्षर *dest, अक्षर *src, पूर्णांक len, पूर्णांक max)
अणु
	अगर (!len)
		वापस 0;
	अगर (len > max-1)
		len = max-1;
	स_नकल(dest, src, len);
	dest[len] = '\0';
	वापस 1;
पूर्ण


/*
 *  Process BOOTP extensions.
 */
अटल व्योम __init ic_करो_bootp_ext(u8 *ext)
अणु
	u8 servers;
	पूर्णांक i;
	__be16 mtu;

	u8 *c;

	pr_debug("DHCP/BOOTP: Got extension %d:", *ext);
	क्रम (c=ext+2; c<ext+2+ext[1]; c++)
		pr_debug(" %02x", *c);
	pr_debug("\n");

	चयन (*ext++) अणु
	हाल 1:		/* Subnet mask */
		अगर (ic_neपंचांगask == NONE)
			स_नकल(&ic_neपंचांगask, ext+1, 4);
		अवरोध;
	हाल 3:		/* Default gateway */
		अगर (ic_gateway == NONE)
			स_नकल(&ic_gateway, ext+1, 4);
		अवरोध;
	हाल 6:		/* DNS server */
		servers= *ext/4;
		अगर (servers > CONF_NAMESERVERS_MAX)
			servers = CONF_NAMESERVERS_MAX;
		क्रम (i = 0; i < servers; i++) अणु
			अगर (ic_nameservers[i] == NONE)
				स_नकल(&ic_nameservers[i], ext+1+4*i, 4);
		पूर्ण
		अवरोध;
	हाल 12:	/* Host name */
		अगर (!ic_host_name_set) अणु
			ic_bootp_string(utsname()->nodename, ext+1, *ext,
					__NEW_UTS_LEN);
			ic_host_name_set = 1;
		पूर्ण
		अवरोध;
	हाल 15:	/* Doमुख्य name (DNS) */
		अगर (!ic_करोमुख्य[0])
			ic_bootp_string(ic_करोमुख्य, ext+1, *ext, माप(ic_करोमुख्य));
		अवरोध;
	हाल 17:	/* Root path */
		अगर (!root_server_path[0])
			ic_bootp_string(root_server_path, ext+1, *ext,
					माप(root_server_path));
		अवरोध;
	हाल 26:	/* Interface MTU */
		स_नकल(&mtu, ext+1, माप(mtu));
		ic_dev_mtu = ntohs(mtu);
		अवरोध;
	हाल 40:	/* NIS Doमुख्य name (_not_ DNS) */
		ic_bootp_string(utsname()->करोमुख्यname, ext+1, *ext,
				__NEW_UTS_LEN);
		अवरोध;
	हाल 42:	/* NTP servers */
		servers = *ext / 4;
		अगर (servers > CONF_NTP_SERVERS_MAX)
			servers = CONF_NTP_SERVERS_MAX;
		क्रम (i = 0; i < servers; i++) अणु
			अगर (ic_ntp_servers[i] == NONE)
				स_नकल(&ic_ntp_servers[i], ext+1+4*i, 4);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण


/*
 *  Receive BOOTP reply.
 */
अटल पूर्णांक __init ic_bootp_recv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा bootp_pkt *b;
	काष्ठा iphdr *h;
	काष्ठा ic_device *d;
	पूर्णांक len, ext_len;

	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ drop;

	/* Perक्रमm verअगरications beक्रमe taking the lock.  */
	अगर (skb->pkt_type == PACKET_OTHERHOST)
		जाओ drop;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस NET_RX_DROP;

	अगर (!pskb_may_pull(skb,
			   माप(काष्ठा iphdr) +
			   माप(काष्ठा udphdr)))
		जाओ drop;

	b = (काष्ठा bootp_pkt *)skb_network_header(skb);
	h = &b->iph;

	अगर (h->ihl != 5 || h->version != 4 || h->protocol != IPPROTO_UDP)
		जाओ drop;

	/* Fragments are not supported */
	अगर (ip_is_fragment(h)) अणु
		net_err_ratelimited("DHCP/BOOTP: Ignoring fragmented reply\n");
		जाओ drop;
	पूर्ण

	अगर (skb->len < ntohs(h->tot_len))
		जाओ drop;

	अगर (ip_fast_csum((अक्षर *) h, h->ihl))
		जाओ drop;

	अगर (b->udph.source != htons(67) || b->udph.dest != htons(68))
		जाओ drop;

	अगर (ntohs(h->tot_len) < ntohs(b->udph.len) + माप(काष्ठा iphdr))
		जाओ drop;

	len = ntohs(b->udph.len) - माप(काष्ठा udphdr);
	ext_len = len - (माप(*b) -
			 माप(काष्ठा iphdr) -
			 माप(काष्ठा udphdr) -
			 माप(b->exten));
	अगर (ext_len < 0)
		जाओ drop;

	/* Ok the front looks good, make sure we can get at the rest.  */
	अगर (!pskb_may_pull(skb, skb->len))
		जाओ drop;

	b = (काष्ठा bootp_pkt *)skb_network_header(skb);
	h = &b->iph;

	/* One reply at a समय, please. */
	spin_lock(&ic_recv_lock);

	/* If we alपढ़ोy have a reply, just drop the packet */
	अगर (ic_got_reply)
		जाओ drop_unlock;

	/* Find the ic_device that the packet arrived on */
	d = ic_first_dev;
	जबतक (d && d->dev != dev)
		d = d->next;
	अगर (!d)
		जाओ drop_unlock;  /* should never happen */

	/* Is it a reply to our BOOTP request? */
	अगर (b->op != BOOTP_REPLY ||
	    b->xid != d->xid) अणु
		net_err_ratelimited("DHCP/BOOTP: Reply not for us on %s, op[%x] xid[%x]\n",
				    d->dev->name, b->op, b->xid);
		जाओ drop_unlock;
	पूर्ण

	/* Parse extensions */
	अगर (ext_len >= 4 &&
	    !स_भेद(b->exten, ic_bootp_cookie, 4)) अणु /* Check magic cookie */
		u8 *end = (u8 *) b + ntohs(b->iph.tot_len);
		u8 *ext;

#अगर_घोषित IPCONFIG_DHCP
		अगर (ic_proto_enabled & IC_USE_DHCP) अणु
			__be32 server_id = NONE;
			पूर्णांक mt = 0;

			ext = &b->exten[4];
			जबतक (ext < end && *ext != 0xff) अणु
				u8 *opt = ext++;
				अगर (*opt == 0)	/* Padding */
					जारी;
				ext += *ext + 1;
				अगर (ext >= end)
					अवरोध;
				चयन (*opt) अणु
				हाल 53:	/* Message type */
					अगर (opt[1])
						mt = opt[2];
					अवरोध;
				हाल 54:	/* Server ID (IP address) */
					अगर (opt[1] >= 4)
						स_नकल(&server_id, opt + 2, 4);
					अवरोध;
				पूर्ण
			पूर्ण

			pr_debug("DHCP: Got message type %d (%s)\n", mt, d->dev->name);

			चयन (mt) अणु
			हाल DHCPOFFER:
				/* While in the process of accepting one offer,
				 * ignore all others.
				 */
				अगर (ic_myaddr != NONE)
					जाओ drop_unlock;

				/* Let's accept that offer. */
				ic_myaddr = b->your_ip;
				ic_servaddr = server_id;
				pr_debug("DHCP: Offered address %pI4 by server %pI4\n",
					 &ic_myaddr, &b->iph.saddr);
				/* The DHCP indicated server address takes
				 * precedence over the bootp header one अगर
				 * they are dअगरferent.
				 */
				अगर ((server_id != NONE) &&
				    (b->server_ip != server_id))
					b->server_ip = ic_servaddr;
				अवरोध;

			हाल DHCPACK:
				अगर (स_भेद(dev->dev_addr, b->hw_addr, dev->addr_len) != 0)
					जाओ drop_unlock;

				/* Yeah! */
				अवरोध;

			शेष:
				/* Urque.  Forget it*/
				ic_myaddr = NONE;
				ic_servaddr = NONE;
				जाओ drop_unlock;
			पूर्ण

			ic_dhcp_msgtype = mt;

		पूर्ण
#पूर्ण_अगर /* IPCONFIG_DHCP */

		ext = &b->exten[4];
		जबतक (ext < end && *ext != 0xff) अणु
			u8 *opt = ext++;
			अगर (*opt == 0)	/* Padding */
				जारी;
			ext += *ext + 1;
			अगर (ext < end)
				ic_करो_bootp_ext(opt);
		पूर्ण
	पूर्ण

	/* We have a winner! */
	ic_dev = d;
	ic_myaddr = b->your_ip;
	ic_servaddr = b->server_ip;
	ic_addrservaddr = b->iph.saddr;
	अगर (ic_gateway == NONE && b->relay_ip)
		ic_gateway = b->relay_ip;
	अगर (ic_nameservers[0] == NONE)
		ic_nameservers[0] = ic_servaddr;
	ic_got_reply = IC_BOOTP;

drop_unlock:
	/* Show's over.  Nothing to see here.  */
	spin_unlock(&ic_recv_lock);

drop:
	/* Throw the packet out. */
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण


#पूर्ण_अगर


/*
 *	Dynamic IP configuration -- DHCP, BOOTP, RARP.
 */

#अगर_घोषित IPCONFIG_DYNAMIC

अटल पूर्णांक __init ic_dynamic(व्योम)
अणु
	पूर्णांक retries;
	काष्ठा ic_device *d;
	अचिन्हित दीर्घ start_jअगरfies, समयout, jअगरf;
	पूर्णांक करो_bootp = ic_proto_have_अगर & IC_BOOTP;
	पूर्णांक करो_rarp = ic_proto_have_अगर & IC_RARP;

	/*
	 * If none of DHCP/BOOTP/RARP was selected, वापस with an error.
	 * This routine माला_लो only called when some pieces of inक्रमmation
	 * are missing, and without DHCP/BOOTP/RARP we are unable to get it.
	 */
	अगर (!ic_proto_enabled) अणु
		pr_err("IP-Config: Incomplete network configuration information\n");
		वापस -1;
	पूर्ण

#अगर_घोषित IPCONFIG_BOOTP
	अगर ((ic_proto_enabled ^ ic_proto_have_अगर) & IC_BOOTP)
		pr_err("DHCP/BOOTP: No suitable device found\n");
#पूर्ण_अगर
#अगर_घोषित IPCONFIG_RARP
	अगर ((ic_proto_enabled ^ ic_proto_have_अगर) & IC_RARP)
		pr_err("RARP: No suitable device found\n");
#पूर्ण_अगर

	अगर (!ic_proto_have_अगर)
		/* Error message alपढ़ोy prपूर्णांकed */
		वापस -1;

	/*
	 * Setup protocols
	 */
#अगर_घोषित IPCONFIG_BOOTP
	अगर (करो_bootp)
		ic_bootp_init();
#पूर्ण_अगर
#अगर_घोषित IPCONFIG_RARP
	अगर (करो_rarp)
		ic_rarp_init();
#पूर्ण_अगर

	/*
	 * Send requests and रुको, until we get an answer. This loop
	 * seems to be a terrible waste of CPU समय, but actually there is
	 * only one process running at all, so we करोn't need to use any
	 * scheduler functions.
	 * [Actually we could now, but the nothing अन्यथा running note still
	 *  applies.. - AC]
	 */
	pr_notice("Sending %s%s%s requests .",
		  करो_bootp
		  ? ((ic_proto_enabled & IC_USE_DHCP) ? "DHCP" : "BOOTP") : "",
		  (करो_bootp && करो_rarp) ? " and " : "",
		  करो_rarp ? "RARP" : "");

	start_jअगरfies = jअगरfies;
	d = ic_first_dev;
	retries = CONF_SEND_RETRIES;
	get_अक्रमom_bytes(&समयout, माप(समयout));
	समयout = CONF_BASE_TIMEOUT + (समयout % (अचिन्हित पूर्णांक) CONF_TIMEOUT_RANDOM);
	क्रम (;;) अणु
#अगर_घोषित IPCONFIG_BOOTP
		अगर (करो_bootp && (d->able & IC_BOOTP))
			ic_bootp_send_अगर(d, jअगरfies - start_jअगरfies);
#पूर्ण_अगर
#अगर_घोषित IPCONFIG_RARP
		अगर (करो_rarp && (d->able & IC_RARP))
			ic_rarp_send_अगर(d);
#पूर्ण_अगर

		अगर (!d->next) अणु
			jअगरf = jअगरfies + समयout;
			जबतक (समय_beक्रमe(jअगरfies, jअगरf) && !ic_got_reply)
				schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण
#अगर_घोषित IPCONFIG_DHCP
		/* DHCP isn't करोne until we get a DHCPACK. */
		अगर ((ic_got_reply & IC_BOOTP) &&
		    (ic_proto_enabled & IC_USE_DHCP) &&
		    ic_dhcp_msgtype != DHCPACK) अणु
			ic_got_reply = 0;
			/* जारी on device that got the reply */
			d = ic_dev;
			pr_cont(",");
			जारी;
		पूर्ण
#पूर्ण_अगर /* IPCONFIG_DHCP */

		अगर (ic_got_reply) अणु
			pr_cont(" OK\n");
			अवरोध;
		पूर्ण

		अगर ((d = d->next))
			जारी;

		अगर (! --retries) अणु
			pr_cont(" timed out!\n");
			अवरोध;
		पूर्ण

		d = ic_first_dev;

		समयout = समयout CONF_TIMEOUT_MULT;
		अगर (समयout > CONF_TIMEOUT_MAX)
			समयout = CONF_TIMEOUT_MAX;

		pr_cont(".");
	पूर्ण

#अगर_घोषित IPCONFIG_BOOTP
	अगर (करो_bootp)
		ic_bootp_cleanup();
#पूर्ण_अगर
#अगर_घोषित IPCONFIG_RARP
	अगर (करो_rarp)
		ic_rarp_cleanup();
#पूर्ण_अगर

	अगर (!ic_got_reply) अणु
		ic_myaddr = NONE;
		वापस -1;
	पूर्ण

	pr_info("IP-Config: Got %s answer from %pI4, my address is %pI4\n",
		((ic_got_reply & IC_RARP) ? "RARP"
		: (ic_proto_enabled & IC_USE_DHCP) ? "DHCP" : "BOOTP"),
		&ic_addrservaddr, &ic_myaddr);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* IPCONFIG_DYNAMIC */

#अगर_घोषित CONFIG_PROC_FS
/* proc_dir_entry क्रम /proc/net/ipconfig */
अटल काष्ठा proc_dir_entry *ipconfig_dir;

/* Name servers: */
अटल पूर्णांक pnp_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i;

	अगर (ic_proto_used & IC_PROTO)
		seq_म_लिखो(seq, "#PROTO: %s\n",
			   (ic_proto_used & IC_RARP) ? "RARP"
			   : (ic_proto_used & IC_USE_DHCP) ? "DHCP" : "BOOTP");
	अन्यथा
		seq_माला_दो(seq, "#MANUAL\n");

	अगर (ic_करोमुख्य[0])
		seq_म_लिखो(seq,
			   "domain %s\n", ic_करोमुख्य);
	क्रम (i = 0; i < CONF_NAMESERVERS_MAX; i++) अणु
		अगर (ic_nameservers[i] != NONE)
			seq_म_लिखो(seq, "nameserver %pI4\n",
				   &ic_nameservers[i]);
	पूर्ण
	अगर (ic_servaddr != NONE)
		seq_म_लिखो(seq, "bootserver %pI4\n",
			   &ic_servaddr);
	वापस 0;
पूर्ण

/* Create the /proc/net/ipconfig directory */
अटल पूर्णांक __init ipconfig_proc_net_init(व्योम)
अणु
	ipconfig_dir = proc_net_सूची_गढ़ो(&init_net, "ipconfig", init_net.proc_net);
	अगर (!ipconfig_dir)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Create a new file under /proc/net/ipconfig */
अटल पूर्णांक ipconfig_proc_net_create(स्थिर अक्षर *name,
				    स्थिर काष्ठा proc_ops *proc_ops)
अणु
	अक्षर *pname;
	काष्ठा proc_dir_entry *p;

	अगर (!ipconfig_dir)
		वापस -ENOMEM;

	pname = kaप्र_लिखो(GFP_KERNEL, "%s%s", "ipconfig/", name);
	अगर (!pname)
		वापस -ENOMEM;

	p = proc_create(pname, 0444, init_net.proc_net, proc_ops);
	kमुक्त(pname);
	अगर (!p)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Write NTP server IP addresses to /proc/net/ipconfig/ntp_servers */
अटल पूर्णांक ntp_servers_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CONF_NTP_SERVERS_MAX; i++) अणु
		अगर (ic_ntp_servers[i] != NONE)
			seq_म_लिखो(seq, "%pI4\n", &ic_ntp_servers[i]);
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_PROC_SHOW_ATTRIBUTE(ntp_servers);
#पूर्ण_अगर /* CONFIG_PROC_FS */

/*
 *  Extract IP address from the parameter string अगर needed. Note that we
 *  need to have root_server_addr set _beक्रमe_ IPConfig माला_लो called as it
 *  can override it.
 */
__be32 __init root_nfs_parse_addr(अक्षर *name)
अणु
	__be32 addr;
	पूर्णांक octets = 0;
	अक्षर *cp, *cq;

	cp = cq = name;
	जबतक (octets < 4) अणु
		जबतक (*cp >= '0' && *cp <= '9')
			cp++;
		अगर (cp == cq || cp - cq > 3)
			अवरोध;
		अगर (*cp == '.' || octets == 3)
			octets++;
		अगर (octets < 4)
			cp++;
		cq = cp;
	पूर्ण
	अगर (octets == 4 && (*cp == ':' || *cp == '\0')) अणु
		अगर (*cp == ':')
			*cp++ = '\0';
		addr = in_aton(name);
		स_हटाओ(name, cp, म_माप(cp) + 1);
	पूर्ण अन्यथा
		addr = NONE;

	वापस addr;
पूर्ण

#घोषणा DEVICE_WAIT_MAX		12 /* 12 seconds */

अटल पूर्णांक __init रुको_क्रम_devices(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DEVICE_WAIT_MAX; i++) अणु
		काष्ठा net_device *dev;
		पूर्णांक found = 0;

		/* make sure deferred device probes are finished */
		रुको_क्रम_device_probe();

		rtnl_lock();
		क्रम_each_netdev(&init_net, dev) अणु
			अगर (ic_is_init_dev(dev)) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		rtnl_unlock();
		अगर (found)
			वापस 0;
		ssleep(1);
	पूर्ण
	वापस -ENODEV;
पूर्ण

/*
 *	IP Autoconfig dispatcher.
 */

अटल पूर्णांक __init ip_स्वतः_config(व्योम)
अणु
	__be32 addr;
#अगर_घोषित IPCONFIG_DYNAMIC
	पूर्णांक retries = CONF_OPEN_RETRIES;
#पूर्ण_अगर
	पूर्णांक err;
	अचिन्हित पूर्णांक i, count;

	/* Initialise all name servers and NTP servers to NONE (but only अगर the
	 * "ip=" or "nfsaddrs=" kernel command line parameters weren't decoded,
	 * otherwise we'll overग_लिखो the IP addresses specअगरied there)
	 */
	अगर (ic_set_manually == 0) अणु
		ic_nameservers_predef();
		ic_ntp_servers_predef();
	पूर्ण

#अगर_घोषित CONFIG_PROC_FS
	proc_create_single("pnp", 0444, init_net.proc_net, pnp_seq_show);

	अगर (ipconfig_proc_net_init() == 0)
		ipconfig_proc_net_create("ntp_servers", &ntp_servers_proc_ops);
#पूर्ण_अगर /* CONFIG_PROC_FS */

	अगर (!ic_enable)
		वापस 0;

	pr_debug("IP-Config: Entered.\n");
#अगर_घोषित IPCONFIG_DYNAMIC
 try_try_again:
#पूर्ण_अगर
	/* Wait क्रम devices to appear */
	err = रुको_क्रम_devices();
	अगर (err)
		वापस err;

	/* Setup all network devices */
	err = ic_खोलो_devs();
	अगर (err)
		वापस err;

	/* Give drivers a chance to settle */
	msleep(CONF_POST_OPEN);

	/*
	 * If the config inक्रमmation is insufficient (e.g., our IP address or
	 * IP address of the boot server is missing or we have multiple network
	 * पूर्णांकerfaces and no शेष was set), use BOOTP or RARP to get the
	 * missing values.
	 */
	अगर (ic_myaddr == NONE ||
#अगर defined(CONFIG_ROOT_NFS) || defined(CONFIG_CIFS_ROOT)
	    (root_server_addr == NONE &&
	     ic_servaddr == NONE &&
	     (ROOT_DEV == Root_NFS || ROOT_DEV == Root_CIFS)) ||
#पूर्ण_अगर
	    ic_first_dev->next) अणु
#अगर_घोषित IPCONFIG_DYNAMIC
		अगर (ic_dynamic() < 0) अणु
			ic_बंद_devs();

			/*
			 * I करोn't know why, but someबार the
			 * eepro100 driver (at least) माला_लो upset and
			 * करोesn't work the first time it's खोलोed.
			 * But then अगर you बंद it and reखोलो it, it
			 * works just fine.  So we need to try that at
			 * least once beक्रमe giving up.
			 *
			 * Also, अगर the root will be NFS-mounted, we
			 * have nowhere to go अगर DHCP fails.  So we
			 * just have to keep trying क्रमever.
			 *
			 * 				-- Chip
			 */
#अगर_घोषित CONFIG_ROOT_NFS
			अगर (ROOT_DEV ==  Root_NFS) अणु
				pr_err("IP-Config: Retrying forever (NFS root)...\n");
				जाओ try_try_again;
			पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_ROOT
			अगर (ROOT_DEV == Root_CIFS) अणु
				pr_err("IP-Config: Retrying forever (CIFS root)...\n");
				जाओ try_try_again;
			पूर्ण
#पूर्ण_अगर

			अगर (--retries) अणु
				pr_err("IP-Config: Reopening network devices...\n");
				जाओ try_try_again;
			पूर्ण

			/* Oh, well.  At least we tried. */
			pr_err("IP-Config: Auto-configuration of network failed\n");
			वापस -1;
		पूर्ण
#अन्यथा /* !DYNAMIC */
		pr_err("IP-Config: Incomplete network configuration information\n");
		ic_बंद_devs();
		वापस -1;
#पूर्ण_अगर /* IPCONFIG_DYNAMIC */
	पूर्ण अन्यथा अणु
		/* Device selected manually or only one device -> use it */
		ic_dev = ic_first_dev;
	पूर्ण

	addr = root_nfs_parse_addr(root_server_path);
	अगर (root_server_addr == NONE)
		root_server_addr = addr;

	/*
	 * Use शेषs wherever applicable.
	 */
	अगर (ic_शेषs() < 0)
		वापस -1;

	/*
	 * Record which protocol was actually used.
	 */
#अगर_घोषित IPCONFIG_DYNAMIC
	ic_proto_used = ic_got_reply | (ic_proto_enabled & IC_USE_DHCP);
#पूर्ण_अगर

#अगर_अघोषित IPCONFIG_SILENT
	/*
	 * Clue in the चालक.
	 */
	pr_info("IP-Config: Complete:\n");

	pr_info("     device=%s, hwaddr=%*phC, ipaddr=%pI4, mask=%pI4, gw=%pI4\n",
		ic_dev->dev->name, ic_dev->dev->addr_len, ic_dev->dev->dev_addr,
		&ic_myaddr, &ic_neपंचांगask, &ic_gateway);
	pr_info("     host=%s, domain=%s, nis-domain=%s\n",
		utsname()->nodename, ic_करोमुख्य, utsname()->करोमुख्यname);
	pr_info("     bootserver=%pI4, rootserver=%pI4, rootpath=%s",
		&ic_servaddr, &root_server_addr, root_server_path);
	अगर (ic_dev_mtu)
		pr_cont(", mtu=%d", ic_dev_mtu);
	/* Name servers (अगर any): */
	क्रम (i = 0, count = 0; i < CONF_NAMESERVERS_MAX; i++) अणु
		अगर (ic_nameservers[i] != NONE) अणु
			अगर (i == 0)
				pr_info("     nameserver%u=%pI4",
					i, &ic_nameservers[i]);
			अन्यथा
				pr_cont(", nameserver%u=%pI4",
					i, &ic_nameservers[i]);

			count++;
		पूर्ण
		अगर ((i + 1 == CONF_NAMESERVERS_MAX) && count > 0)
			pr_cont("\n");
	पूर्ण
	/* NTP servers (अगर any): */
	क्रम (i = 0, count = 0; i < CONF_NTP_SERVERS_MAX; i++) अणु
		अगर (ic_ntp_servers[i] != NONE) अणु
			अगर (i == 0)
				pr_info("     ntpserver%u=%pI4",
					i, &ic_ntp_servers[i]);
			अन्यथा
				pr_cont(", ntpserver%u=%pI4",
					i, &ic_ntp_servers[i]);

			count++;
		पूर्ण
		अगर ((i + 1 == CONF_NTP_SERVERS_MAX) && count > 0)
			pr_cont("\n");
	पूर्ण
#पूर्ण_अगर /* !SILENT */

	/*
	 * Close all network devices except the device we've
	 * स्वतःconfigured and set up routes.
	 */
	अगर (ic_setup_अगर() < 0 || ic_setup_routes() < 0)
		err = -1;
	अन्यथा
		err = 0;

	ic_बंद_devs();

	वापस err;
पूर्ण

late_initcall(ip_स्वतः_config);


/*
 *  Decode any IP configuration options in the "ip=" or "nfsaddrs=" kernel
 *  command line parameter.  See Documentation/admin-guide/nfs/nfsroot.rst.
 */
अटल पूर्णांक __init ic_proto_name(अक्षर *name)
अणु
	अगर (!म_भेद(name, "on") || !म_भेद(name, "any")) अणु
		वापस 1;
	पूर्ण
	अगर (!म_भेद(name, "off") || !म_भेद(name, "none")) अणु
		वापस 0;
	पूर्ण
#अगर_घोषित CONFIG_IP_PNP_DHCP
	अन्यथा अगर (!म_भेदन(name, "dhcp", 4)) अणु
		अक्षर *client_id;

		ic_proto_enabled &= ~IC_RARP;
		client_id = म_माला(name, "dhcp,");
		अगर (client_id) अणु
			अक्षर *v;

			client_id = client_id + 5;
			v = म_अक्षर(client_id, ',');
			अगर (!v)
				वापस 1;
			*v = 0;
			अगर (kstrtou8(client_id, 0, dhcp_client_identअगरier))
				pr_debug("DHCP: Invalid client identifier type\n");
			म_नकलन(dhcp_client_identअगरier + 1, v + 1, 251);
			*v = ',';
		पूर्ण
		वापस 1;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_PNP_BOOTP
	अन्यथा अगर (!म_भेद(name, "bootp")) अणु
		ic_proto_enabled &= ~(IC_RARP | IC_USE_DHCP);
		वापस 1;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_PNP_RARP
	अन्यथा अगर (!म_भेद(name, "rarp")) अणु
		ic_proto_enabled &= ~(IC_BOOTP | IC_USE_DHCP);
		वापस 1;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित IPCONFIG_DYNAMIC
	अन्यथा अगर (!म_भेद(name, "both")) अणु
		ic_proto_enabled &= ~IC_USE_DHCP; /* backward compat :-( */
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __init ip_स्वतः_config_setup(अक्षर *addrs)
अणु
	अक्षर *cp, *ip, *dp;
	पूर्णांक num = 0;

	ic_set_manually = 1;
	ic_enable = 1;

	/*
	 * If any dhcp, bootp etc options are set, leave स्वतःconfig on
	 * and skip the below अटल IP processing.
	 */
	अगर (ic_proto_name(addrs))
		वापस 1;

	/* If no अटल IP is given, turn off स्वतःconfig and bail.  */
	अगर (*addrs == 0 ||
	    म_भेद(addrs, "off") == 0 ||
	    म_भेद(addrs, "none") == 0) अणु
		ic_enable = 0;
		वापस 1;
	पूर्ण

	/* Initialise all name servers and NTP servers to NONE */
	ic_nameservers_predef();
	ic_ntp_servers_predef();

	/* Parse string क्रम अटल IP assignment.  */
	ip = addrs;
	जबतक (ip && *ip) अणु
		अगर ((cp = म_अक्षर(ip, ':')))
			*cp++ = '\0';
		अगर (म_माप(ip) > 0) अणु
			pr_debug("IP-Config: Parameter #%d: `%s'\n", num, ip);
			चयन (num) अणु
			हाल 0:
				अगर ((ic_myaddr = in_aton(ip)) == ANY)
					ic_myaddr = NONE;
				अवरोध;
			हाल 1:
				अगर ((ic_servaddr = in_aton(ip)) == ANY)
					ic_servaddr = NONE;
				अवरोध;
			हाल 2:
				अगर ((ic_gateway = in_aton(ip)) == ANY)
					ic_gateway = NONE;
				अवरोध;
			हाल 3:
				अगर ((ic_neपंचांगask = in_aton(ip)) == ANY)
					ic_neपंचांगask = NONE;
				अवरोध;
			हाल 4:
				अगर ((dp = म_अक्षर(ip, '.'))) अणु
					*dp++ = '\0';
					strlcpy(utsname()->करोमुख्यname, dp,
						माप(utsname()->करोमुख्यname));
				पूर्ण
				strlcpy(utsname()->nodename, ip,
					माप(utsname()->nodename));
				ic_host_name_set = 1;
				अवरोध;
			हाल 5:
				strlcpy(user_dev_name, ip, माप(user_dev_name));
				अवरोध;
			हाल 6:
				अगर (ic_proto_name(ip) == 0 &&
				    ic_myaddr == NONE) अणु
					ic_enable = 0;
				पूर्ण
				अवरोध;
			हाल 7:
				अगर (CONF_NAMESERVERS_MAX >= 1) अणु
					ic_nameservers[0] = in_aton(ip);
					अगर (ic_nameservers[0] == ANY)
						ic_nameservers[0] = NONE;
				पूर्ण
				अवरोध;
			हाल 8:
				अगर (CONF_NAMESERVERS_MAX >= 2) अणु
					ic_nameservers[1] = in_aton(ip);
					अगर (ic_nameservers[1] == ANY)
						ic_nameservers[1] = NONE;
				पूर्ण
				अवरोध;
			हाल 9:
				अगर (CONF_NTP_SERVERS_MAX >= 1) अणु
					ic_ntp_servers[0] = in_aton(ip);
					अगर (ic_ntp_servers[0] == ANY)
						ic_ntp_servers[0] = NONE;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		ip = cp;
		num++;
	पूर्ण

	वापस 1;
पूर्ण
__setup("ip=", ip_स्वतः_config_setup);

अटल पूर्णांक __init nfsaddrs_config_setup(अक्षर *addrs)
अणु
	वापस ip_स्वतः_config_setup(addrs);
पूर्ण
__setup("nfsaddrs=", nfsaddrs_config_setup);

अटल पूर्णांक __init venकरोr_class_identअगरier_setup(अक्षर *addrs)
अणु
	अगर (strlcpy(venकरोr_class_identअगरier, addrs,
		    माप(venकरोr_class_identअगरier))
	    >= माप(venकरोr_class_identअगरier))
		pr_warn("DHCP: vendorclass too long, truncated to \"%s\"\n",
			venकरोr_class_identअगरier);
	वापस 1;
पूर्ण
__setup("dhcpclass=", venकरोr_class_identअगरier_setup);

अटल पूर्णांक __init set_carrier_समयout(अक्षर *str)
अणु
	sमाप_प्रकार ret;

	अगर (!str)
		वापस 0;

	ret = kstrtouपूर्णांक(str, 0, &carrier_समयout);
	अगर (ret)
		वापस 0;

	वापस 1;
पूर्ण
__setup("carrier_timeout=", set_carrier_समयout);
