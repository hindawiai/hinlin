<शैली गुरु>
/*
 *	ipddp.c: IP to Appletalk-IP Encapsulation driver क्रम Linux
 *		 Appletalk-IP to IP Decapsulation driver क्रम Linux
 *
 *	Authors:
 *      - DDP-IP Encap by: Bradक्रमd W. Johnson <johns393@maroon.tc.umn.edu>
 *	- DDP-IP Decap by: Jay Schulist <jschlst@samba.org>
 *
 *	Derived from:
 *	- Almost all code alपढ़ोy existed in net/appletalk/ddp.c I just
 *	  moved/reorginized it पूर्णांकo a driver file. Original IP-over-DDP code
 *	  was करोne by Bradक्रमd W. Johnson <johns393@maroon.tc.umn.edu>
 *      - skeleton.c: A network driver outline क्रम linux.
 *        Written 1993-94 by Donald Becker.
 *	- dummy.c: A dummy net driver. By Nick Holloway.
 *	- MacGate: A user space Daemon क्रम Appletalk-IP Decap क्रम
 *	  Linux by Jay Schulist <jschlst@samba.org>
 *
 *      Copyright 1993 United States Government as represented by the
 *      Director, National Security Agency.
 *
 *      This software may be used and distributed according to the terms
 *      of the GNU General Public License, incorporated herein by reference.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/atalk.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <net/route.h>
#समावेश <linux/uaccess.h>

#समावेश "ipddp.h"		/* Our stuff */

अटल स्थिर अक्षर version[] = KERN_INFO "ipddp.c:v0.01 8/28/97 Bradford W. Johnson <johns393@maroon.tc.umn.edu>\n";

अटल काष्ठा ipddp_route *ipddp_route_list;
अटल DEFINE_SPINLOCK(ipddp_route_lock);

#अगर_घोषित CONFIG_IPDDP_ENCAP
अटल पूर्णांक ipddp_mode = IPDDP_ENCAP;
#अन्यथा
अटल पूर्णांक ipddp_mode = IPDDP_DECAP;
#पूर्ण_अगर

/* Index to functions, as function prototypes. */
अटल netdev_tx_t ipddp_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev);
अटल पूर्णांक ipddp_create(काष्ठा ipddp_route *new_rt);
अटल पूर्णांक ipddp_delete(काष्ठा ipddp_route *rt);
अटल काष्ठा ipddp_route* __ipddp_find_route(काष्ठा ipddp_route *rt);
अटल पूर्णांक ipddp_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);

अटल स्थिर काष्ठा net_device_ops ipddp_netdev_ops = अणु
	.nकरो_start_xmit		= ipddp_xmit,
	.nकरो_करो_ioctl   	= ipddp_ioctl,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल काष्ठा net_device * __init ipddp_init(व्योम)
अणु
	अटल अचिन्हित version_prपूर्णांकed;
	काष्ठा net_device *dev;
	पूर्णांक err;

	dev = alloc_etherdev(0);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	netअगर_keep_dst(dev);
	म_नकल(dev->name, "ipddp%d");

	अगर (version_prपूर्णांकed++ == 0)
                prपूर्णांकk(version);

	/* Initialize the device काष्ठाure. */
	dev->netdev_ops = &ipddp_netdev_ops;

        dev->type = ARPHRD_IPDDP;       	/* IP over DDP tunnel */
        dev->mtu = 585;
        dev->flags |= IFF_NOARP;

        /*
         *      The worst हाल header we will need is currently a
         *      ethernet header (14 bytes) and a ddp header (माप ddpehdr+1)
         *      We send over SNAP so that takes another 8 bytes.
         */
        dev->hard_header_len = 14+8+माप(काष्ठा ddpehdr)+1;

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		मुक्त_netdev(dev);
		वापस ERR_PTR(err);
	पूर्ण

	/* Let the user now what mode we are in */
	अगर(ipddp_mode == IPDDP_ENCAP)
		prपूर्णांकk("%s: Appletalk-IP Encap. mode by Bradford W. Johnson <johns393@maroon.tc.umn.edu>\n", 
			dev->name);
	अगर(ipddp_mode == IPDDP_DECAP)
		prपूर्णांकk("%s: Appletalk-IP Decap. mode by Jay Schulist <jschlst@samba.org>\n", 
			dev->name);

        वापस dev;
पूर्ण


/*
 * Transmit LLAP/ELAP frame using aarp_send_ddp.
 */
अटल netdev_tx_t ipddp_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
        काष्ठा rtable *rtable = skb_rtable(skb);
        __be32 paddr = 0;
        काष्ठा ddpehdr *ddp;
        काष्ठा ipddp_route *rt;
        काष्ठा atalk_addr *our_addr;

	अगर (rtable->rt_gw_family == AF_INET)
		paddr = rtable->rt_gw4;

	spin_lock(&ipddp_route_lock);

	/*
         * Find appropriate route to use, based only on IP number.
         */
        क्रम(rt = ipddp_route_list; rt != शून्य; rt = rt->next)
        अणु
                अगर(rt->ip == paddr)
                        अवरोध;
        पूर्ण
        अगर(rt == शून्य) अणु
		spin_unlock(&ipddp_route_lock);
                वापस NETDEV_TX_OK;
	पूर्ण

        our_addr = atalk_find_dev_addr(rt->dev);

	अगर(ipddp_mode == IPDDP_DECAP)
		/* 
		 * Pull off the excess room that should not be there.
		 * This is due to a hard-header problem. This is the
		 * quick fix क्रम now though, till it अवरोधs.
		 */
		skb_pull(skb, 35-(माप(काष्ठा ddpehdr)+1));

	/* Create the Extended DDP header */
	ddp = (काष्ठा ddpehdr *)skb->data;
        ddp->deh_len_hops = htons(skb->len + (1<<10));
        ddp->deh_sum = 0;

	/*
         * For Localtalk we need aarp_send_ddp to strip the
         * दीर्घ DDP header and place a shot DDP header on it.
         */
        अगर(rt->dev->type == ARPHRD_LOCALTLK)
        अणु
                ddp->deh_dnet  = 0;   /* FIXME more hops?? */
                ddp->deh_snet  = 0;
        पूर्ण
        अन्यथा
        अणु
                ddp->deh_dnet  = rt->at.s_net;   /* FIXME more hops?? */
                ddp->deh_snet  = our_addr->s_net;
        पूर्ण
        ddp->deh_dnode = rt->at.s_node;
        ddp->deh_snode = our_addr->s_node;
        ddp->deh_dport = 72;
        ddp->deh_sport = 72;

        *((__u8 *)(ddp+1)) = 22;        	/* ddp type = IP */

        skb->protocol = htons(ETH_P_ATALK);     /* Protocol has changed */

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	aarp_send_ddp(rt->dev, skb, &rt->at, शून्य);

	spin_unlock(&ipddp_route_lock);

        वापस NETDEV_TX_OK;
पूर्ण

/*
 * Create a routing entry. We first verअगरy that the
 * record करोes not alपढ़ोy exist. If it करोes we वापस -EEXIST
 */
अटल पूर्णांक ipddp_create(काष्ठा ipddp_route *new_rt)
अणु
        काष्ठा ipddp_route *rt = kzalloc(माप(*rt), GFP_KERNEL);

        अगर (rt == शून्य)
                वापस -ENOMEM;

        rt->ip = new_rt->ip;
        rt->at = new_rt->at;
        rt->next = शून्य;
        अगर ((rt->dev = atrtr_get_dev(&rt->at)) == शून्य) अणु
		kमुक्त(rt);
                वापस -ENETUNREACH;
        पूर्ण

	spin_lock_bh(&ipddp_route_lock);
	अगर (__ipddp_find_route(rt)) अणु
		spin_unlock_bh(&ipddp_route_lock);
		kमुक्त(rt);
		वापस -EEXIST;
	पूर्ण

        rt->next = ipddp_route_list;
        ipddp_route_list = rt;

	spin_unlock_bh(&ipddp_route_lock);

        वापस 0;
पूर्ण

/*
 * Delete a route, we only delete a FULL match.
 * If route करोes not exist we वापस -ENOENT.
 */
अटल पूर्णांक ipddp_delete(काष्ठा ipddp_route *rt)
अणु
        काष्ठा ipddp_route **r = &ipddp_route_list;
        काष्ठा ipddp_route *पंचांगp;

	spin_lock_bh(&ipddp_route_lock);
        जबतक((पंचांगp = *r) != शून्य)
        अणु
                अगर(पंचांगp->ip == rt->ip &&
		   पंचांगp->at.s_net == rt->at.s_net &&
		   पंचांगp->at.s_node == rt->at.s_node)
                अणु
                        *r = पंचांगp->next;
			spin_unlock_bh(&ipddp_route_lock);
                        kमुक्त(पंचांगp);
                        वापस 0;
                पूर्ण
                r = &पंचांगp->next;
        पूर्ण

	spin_unlock_bh(&ipddp_route_lock);
        वापस -ENOENT;
पूर्ण

/*
 * Find a routing entry, we only वापस a FULL match
 */
अटल काष्ठा ipddp_route* __ipddp_find_route(काष्ठा ipddp_route *rt)
अणु
        काष्ठा ipddp_route *f;

        क्रम(f = ipddp_route_list; f != शून्य; f = f->next)
        अणु
                अगर(f->ip == rt->ip &&
		   f->at.s_net == rt->at.s_net &&
		   f->at.s_node == rt->at.s_node)
                        वापस f;
        पूर्ण

        वापस शून्य;
पूर्ण

अटल पूर्णांक ipddp_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
        काष्ठा ipddp_route __user *rt = अगरr->अगरr_data;
        काष्ठा ipddp_route rcp, rcp2, *rp;

        अगर(!capable(CAP_NET_ADMIN))
                वापस -EPERM;

	अगर(copy_from_user(&rcp, rt, माप(rcp)))
		वापस -EFAULT;

        चयन(cmd)
        अणु
		हाल SIOCADDIPDDPRT:
                        वापस ipddp_create(&rcp);

                हाल SIOCFINDIPDDPRT:
			spin_lock_bh(&ipddp_route_lock);
			rp = __ipddp_find_route(&rcp);
			अगर (rp) अणु
				स_रखो(&rcp2, 0, माप(rcp2));
				rcp2.ip    = rp->ip;
				rcp2.at    = rp->at;
				rcp2.flags = rp->flags;
			पूर्ण
			spin_unlock_bh(&ipddp_route_lock);

			अगर (rp) अणु
				अगर (copy_to_user(rt, &rcp2,
						 माप(काष्ठा ipddp_route)))
					वापस -EFAULT;
				वापस 0;
			पूर्ण अन्यथा
				वापस -ENOENT;

                हाल SIOCDELIPDDPRT:
                        वापस ipddp_delete(&rcp);

                शेष:
                        वापस -EINVAL;
        पूर्ण
पूर्ण

अटल काष्ठा net_device *dev_ipddp;

MODULE_LICENSE("GPL");
module_param(ipddp_mode, पूर्णांक, 0);

अटल पूर्णांक __init ipddp_init_module(व्योम)
अणु
	dev_ipddp = ipddp_init();
	वापस PTR_ERR_OR_ZERO(dev_ipddp);
पूर्ण

अटल व्योम __निकास ipddp_cleanup_module(व्योम)
अणु
        काष्ठा ipddp_route *p;

	unरेजिस्टर_netdev(dev_ipddp);
        मुक्त_netdev(dev_ipddp);

        जबतक (ipddp_route_list) अणु
                p = ipddp_route_list->next;
                kमुक्त(ipddp_route_list);
                ipddp_route_list = p;
        पूर्ण
पूर्ण

module_init(ipddp_init_module);
module_निकास(ipddp_cleanup_module);
