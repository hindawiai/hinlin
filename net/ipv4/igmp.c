<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Linux NET3:	Internet Group Management Protocol  [IGMP]
 *
 *	This code implements the IGMP protocol as defined in RFC1112. There has
 *	been a further revision of this protocol since which is now supported.
 *
 *	If you have trouble with this module be careful what gcc you have used,
 *	the older version didn't come out right using gcc 2.5.8, the newer one
 *	seems to fall out with gcc 2.6.2.
 *
 *	Authors:
 *		Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	Fixes:
 *
 *		Alan Cox	:	Added lots of __अंतरभूत__ to optimise
 *					the memory usage of all the tiny little
 *					functions.
 *		Alan Cox	:	Dumped the header building experiment.
 *		Alan Cox	:	Minor tweaks पढ़ोy क्रम multicast routing
 *					and extended IGMP protocol.
 *		Alan Cox	:	Removed a load of अंतरभूत directives. Gcc 2.5.8
 *					ग_लिखोs utterly bogus code otherwise (sigh)
 *					fixed IGMP loopback to behave in the manner
 *					desired by mrouted, fixed the fact it has been
 *					broken since 1.3.6 and cleaned up a few minor
 *					poपूर्णांकs.
 *
 *		Chih-Jen Chang	:	Tried to revise IGMP to Version 2
 *		Tsu-Sheng Tsao		E-mail: chihjenc@scf.usc.edu and tsusheng@scf.usc.edu
 *					The enhancements are मुख्यly based on Steve Deering's
 * 					ipmulti-3.5 source code.
 *		Chih-Jen Chang	:	Added the igmp_get_mrouter_info and
 *		Tsu-Sheng Tsao		igmp_set_mrouter_info to keep track of
 *					the mrouted version on that device.
 *		Chih-Jen Chang	:	Added the max_resp_समय parameter to
 *		Tsu-Sheng Tsao		igmp_heard_query(). Using this parameter
 *					to identअगरy the multicast router version
 *					and करो what the IGMP version 2 specअगरied.
 *		Chih-Jen Chang	:	Added a समयr to revert to IGMP V2 router
 *		Tsu-Sheng Tsao		अगर the specअगरied समय expired.
 *		Alan Cox	:	Stop IGMP from 0.0.0.0 being accepted.
 *		Alan Cox	:	Use GFP_ATOMIC in the right places.
 *		Christian Daudt :	igmp समयr wasn't set क्रम local group
 *					memberships but was being deleted,
 *					which caused a "del_समयr() called
 *					from %p with समयr not initialized\न"
 *					message (960131).
 *		Christian Daudt :	हटाओd del_समयr from
 *					igmp_समयr_expire function (960205).
 *             Christian Daudt :       igmp_heard_report now only calls
 *                                     igmp_समयr_expire अगर पंचांग->running is
 *                                     true (960216).
 *		Malcolm Beattie :	ttl comparison wrong in igmp_rcv made
 *					igmp_heard_query never trigger. Expiry
 *					miscalculation fixed in igmp_heard_query
 *					and अक्रमom() made to वापस अचिन्हित to
 *					prevent negative expiry बार.
 *		Alexey Kuznetsov:	Wrong group leaving behaviour, backport
 *					fix from pending 2.1.x patches.
 *		Alan Cox:		Forget to enable FDDI support earlier.
 *		Alexey Kuznetsov:	Fixed leaving groups on device करोwn.
 *		Alexey Kuznetsov:	Accordance to igmp-v2-06 draft.
 *		David L Stevens:	IGMPv3 support, with help from
 *					Vinay Kulkarni
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/igmp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/बार.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/byteorder/generic.h>

#समावेश <net/net_namespace.h>
#समावेश <net/arp.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/route.h>
#समावेश <net/sock.h>
#समावेश <net/checksum.h>
#समावेश <net/inet_common.h>
#समावेश <linux/netfilter_ipv4.h>
#अगर_घोषित CONFIG_IP_MROUTE
#समावेश <linux/mroute.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_FS
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_MULTICAST
/* Parameter names and values are taken from igmp-v2-06 draft */

#घोषणा IGMP_QUERY_INTERVAL			(125*HZ)
#घोषणा IGMP_QUERY_RESPONSE_INTERVAL		(10*HZ)

#घोषणा IGMP_INITIAL_REPORT_DELAY		(1)

/* IGMP_INITIAL_REPORT_DELAY is not from IGMP specs!
 * IGMP specs require to report membership immediately after
 * joining a group, but we delay the first report by a
 * small पूर्णांकerval. It seems more natural and still करोes not
 * contradict to specs provided this delay is small enough.
 */

#घोषणा IGMP_V1_SEEN(in_dev) \
	(IPV4_DEVCONF_ALL(dev_net(in_dev->dev), FORCE_IGMP_VERSION) == 1 || \
	 IN_DEV_CONF_GET((in_dev), FORCE_IGMP_VERSION) == 1 || \
	 ((in_dev)->mr_v1_seen && \
	  समय_beक्रमe(jअगरfies, (in_dev)->mr_v1_seen)))
#घोषणा IGMP_V2_SEEN(in_dev) \
	(IPV4_DEVCONF_ALL(dev_net(in_dev->dev), FORCE_IGMP_VERSION) == 2 || \
	 IN_DEV_CONF_GET((in_dev), FORCE_IGMP_VERSION) == 2 || \
	 ((in_dev)->mr_v2_seen && \
	  समय_beक्रमe(jअगरfies, (in_dev)->mr_v2_seen)))

अटल पूर्णांक unsolicited_report_पूर्णांकerval(काष्ठा in_device *in_dev)
अणु
	पूर्णांक पूर्णांकerval_ms, पूर्णांकerval_jअगरfies;

	अगर (IGMP_V1_SEEN(in_dev) || IGMP_V2_SEEN(in_dev))
		पूर्णांकerval_ms = IN_DEV_CONF_GET(
			in_dev,
			IGMPV2_UNSOLICITED_REPORT_INTERVAL);
	अन्यथा /* v3 */
		पूर्णांकerval_ms = IN_DEV_CONF_GET(
			in_dev,
			IGMPV3_UNSOLICITED_REPORT_INTERVAL);

	पूर्णांकerval_jअगरfies = msecs_to_jअगरfies(पूर्णांकerval_ms);

	/* _समयr functions can't handle a delay of 0 jअगरfies so ensure
	 *  we always वापस a positive value.
	 */
	अगर (पूर्णांकerval_jअगरfies <= 0)
		पूर्णांकerval_jअगरfies = 1;
	वापस पूर्णांकerval_jअगरfies;
पूर्ण

अटल व्योम igmpv3_add_delrec(काष्ठा in_device *in_dev, काष्ठा ip_mc_list *im,
			      gfp_t gfp);
अटल व्योम igmpv3_del_delrec(काष्ठा in_device *in_dev, काष्ठा ip_mc_list *im);
अटल व्योम igmpv3_clear_delrec(काष्ठा in_device *in_dev);
अटल पूर्णांक sf_setstate(काष्ठा ip_mc_list *pmc);
अटल व्योम sf_markstate(काष्ठा ip_mc_list *pmc);
#पूर्ण_अगर
अटल व्योम ip_mc_clear_src(काष्ठा ip_mc_list *pmc);
अटल पूर्णांक ip_mc_add_src(काष्ठा in_device *in_dev, __be32 *pmca, पूर्णांक sभ_शेषe,
			 पूर्णांक sfcount, __be32 *psfsrc, पूर्णांक delta);

अटल व्योम ip_ma_put(काष्ठा ip_mc_list *im)
अणु
	अगर (refcount_dec_and_test(&im->refcnt)) अणु
		in_dev_put(im->पूर्णांकerface);
		kमुक्त_rcu(im, rcu);
	पूर्ण
पूर्ण

#घोषणा क्रम_each_pmc_rcu(in_dev, pmc)				\
	क्रम (pmc = rcu_dereference(in_dev->mc_list);		\
	     pmc != शून्य;					\
	     pmc = rcu_dereference(pmc->next_rcu))

#घोषणा क्रम_each_pmc_rtnl(in_dev, pmc)				\
	क्रम (pmc = rtnl_dereference(in_dev->mc_list);		\
	     pmc != शून्य;					\
	     pmc = rtnl_dereference(pmc->next_rcu))

अटल व्योम ip_sf_list_clear_all(काष्ठा ip_sf_list *psf)
अणु
	काष्ठा ip_sf_list *next;

	जबतक (psf) अणु
		next = psf->sf_next;
		kमुक्त(psf);
		psf = next;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IP_MULTICAST

/*
 *	Timer management
 */

अटल व्योम igmp_stop_समयr(काष्ठा ip_mc_list *im)
अणु
	spin_lock_bh(&im->lock);
	अगर (del_समयr(&im->समयr))
		refcount_dec(&im->refcnt);
	im->पंचांग_running = 0;
	im->reporter = 0;
	im->unsolicit_count = 0;
	spin_unlock_bh(&im->lock);
पूर्ण

/* It must be called with locked im->lock */
अटल व्योम igmp_start_समयr(काष्ठा ip_mc_list *im, पूर्णांक max_delay)
अणु
	पूर्णांक tv = pअक्रमom_u32() % max_delay;

	im->पंचांग_running = 1;
	अगर (!mod_समयr(&im->समयr, jअगरfies+tv+2))
		refcount_inc(&im->refcnt);
पूर्ण

अटल व्योम igmp_gq_start_समयr(काष्ठा in_device *in_dev)
अणु
	पूर्णांक tv = pअक्रमom_u32() % in_dev->mr_maxdelay;
	अचिन्हित दीर्घ exp = jअगरfies + tv + 2;

	अगर (in_dev->mr_gq_running &&
	    समय_after_eq(exp, (in_dev->mr_gq_समयr).expires))
		वापस;

	in_dev->mr_gq_running = 1;
	अगर (!mod_समयr(&in_dev->mr_gq_समयr, exp))
		in_dev_hold(in_dev);
पूर्ण

अटल व्योम igmp_अगरc_start_समयr(काष्ठा in_device *in_dev, पूर्णांक delay)
अणु
	पूर्णांक tv = pअक्रमom_u32() % delay;

	अगर (!mod_समयr(&in_dev->mr_अगरc_समयr, jअगरfies+tv+2))
		in_dev_hold(in_dev);
पूर्ण

अटल व्योम igmp_mod_समयr(काष्ठा ip_mc_list *im, पूर्णांक max_delay)
अणु
	spin_lock_bh(&im->lock);
	im->unsolicit_count = 0;
	अगर (del_समयr(&im->समयr)) अणु
		अगर ((दीर्घ)(im->समयr.expires-jअगरfies) < max_delay) अणु
			add_समयr(&im->समयr);
			im->पंचांग_running = 1;
			spin_unlock_bh(&im->lock);
			वापस;
		पूर्ण
		refcount_dec(&im->refcnt);
	पूर्ण
	igmp_start_समयr(im, max_delay);
	spin_unlock_bh(&im->lock);
पूर्ण


/*
 *	Send an IGMP report.
 */

#घोषणा IGMP_SIZE (माप(काष्ठा igmphdr)+माप(काष्ठा iphdr)+4)


अटल पूर्णांक is_in(काष्ठा ip_mc_list *pmc, काष्ठा ip_sf_list *psf, पूर्णांक type,
	पूर्णांक gdeleted, पूर्णांक sdeleted)
अणु
	चयन (type) अणु
	हाल IGMPV3_MODE_IS_INCLUDE:
	हाल IGMPV3_MODE_IS_EXCLUDE:
		अगर (gdeleted || sdeleted)
			वापस 0;
		अगर (!(pmc->gsquery && !psf->sf_gsresp)) अणु
			अगर (pmc->sभ_शेषe == MCAST_INCLUDE)
				वापस 1;
			/* करोn't include अगर this source is excluded
			 * in all filters
			 */
			अगर (psf->sf_count[MCAST_INCLUDE])
				वापस type == IGMPV3_MODE_IS_INCLUDE;
			वापस pmc->sfcount[MCAST_EXCLUDE] ==
				psf->sf_count[MCAST_EXCLUDE];
		पूर्ण
		वापस 0;
	हाल IGMPV3_CHANGE_TO_INCLUDE:
		अगर (gdeleted || sdeleted)
			वापस 0;
		वापस psf->sf_count[MCAST_INCLUDE] != 0;
	हाल IGMPV3_CHANGE_TO_EXCLUDE:
		अगर (gdeleted || sdeleted)
			वापस 0;
		अगर (pmc->sfcount[MCAST_EXCLUDE] == 0 ||
		    psf->sf_count[MCAST_INCLUDE])
			वापस 0;
		वापस pmc->sfcount[MCAST_EXCLUDE] ==
			psf->sf_count[MCAST_EXCLUDE];
	हाल IGMPV3_ALLOW_NEW_SOURCES:
		अगर (gdeleted || !psf->sf_crcount)
			वापस 0;
		वापस (pmc->sभ_शेषe == MCAST_INCLUDE) ^ sdeleted;
	हाल IGMPV3_BLOCK_OLD_SOURCES:
		अगर (pmc->sभ_शेषe == MCAST_INCLUDE)
			वापस gdeleted || (psf->sf_crcount && sdeleted);
		वापस psf->sf_crcount && !gdeleted && !sdeleted;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
igmp_scount(काष्ठा ip_mc_list *pmc, पूर्णांक type, पूर्णांक gdeleted, पूर्णांक sdeleted)
अणु
	काष्ठा ip_sf_list *psf;
	पूर्णांक scount = 0;

	क्रम (psf = pmc->sources; psf; psf = psf->sf_next) अणु
		अगर (!is_in(pmc, psf, type, gdeleted, sdeleted))
			जारी;
		scount++;
	पूर्ण
	वापस scount;
पूर्ण

/* source address selection per RFC 3376 section 4.2.13 */
अटल __be32 igmpv3_get_srcaddr(काष्ठा net_device *dev,
				 स्थिर काष्ठा flowi4 *fl4)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);
	स्थिर काष्ठा in_अगरaddr *अगरa;

	अगर (!in_dev)
		वापस htonl(INADDR_ANY);

	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		अगर (fl4->saddr == अगरa->अगरa_local)
			वापस fl4->saddr;
	पूर्ण

	वापस htonl(INADDR_ANY);
पूर्ण

अटल काष्ठा sk_buff *igmpv3_newpack(काष्ठा net_device *dev, अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtable *rt;
	काष्ठा iphdr *pip;
	काष्ठा igmpv3_report *pig;
	काष्ठा net *net = dev_net(dev);
	काष्ठा flowi4 fl4;
	पूर्णांक hlen = LL_RESERVED_SPACE(dev);
	पूर्णांक tlen = dev->needed_tailroom;
	अचिन्हित पूर्णांक size = mtu;

	जबतक (1) अणु
		skb = alloc_skb(size + hlen + tlen,
				GFP_ATOMIC | __GFP_NOWARN);
		अगर (skb)
			अवरोध;
		size >>= 1;
		अगर (size < 256)
			वापस शून्य;
	पूर्ण
	skb->priority = TC_PRIO_CONTROL;

	rt = ip_route_output_ports(net, &fl4, शून्य, IGMPV3_ALL_MCR, 0,
				   0, 0,
				   IPPROTO_IGMP, 0, dev->अगरindex);
	अगर (IS_ERR(rt)) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	skb_dst_set(skb, &rt->dst);
	skb->dev = dev;

	skb_reserve(skb, hlen);
	skb_tailroom_reserve(skb, mtu, tlen);

	skb_reset_network_header(skb);
	pip = ip_hdr(skb);
	skb_put(skb, माप(काष्ठा iphdr) + 4);

	pip->version  = 4;
	pip->ihl      = (माप(काष्ठा iphdr)+4)>>2;
	pip->tos      = 0xc0;
	pip->frag_off = htons(IP_DF);
	pip->ttl      = 1;
	pip->daddr    = fl4.daddr;

	rcu_पढ़ो_lock();
	pip->saddr    = igmpv3_get_srcaddr(dev, &fl4);
	rcu_पढ़ो_unlock();

	pip->protocol = IPPROTO_IGMP;
	pip->tot_len  = 0;	/* filled in later */
	ip_select_ident(net, skb, शून्य);
	((u8 *)&pip[1])[0] = IPOPT_RA;
	((u8 *)&pip[1])[1] = 4;
	((u8 *)&pip[1])[2] = 0;
	((u8 *)&pip[1])[3] = 0;

	skb->transport_header = skb->network_header + माप(काष्ठा iphdr) + 4;
	skb_put(skb, माप(*pig));
	pig = igmpv3_report_hdr(skb);
	pig->type = IGMPV3_HOST_MEMBERSHIP_REPORT;
	pig->resv1 = 0;
	pig->csum = 0;
	pig->resv2 = 0;
	pig->ngrec = 0;
	वापस skb;
पूर्ण

अटल पूर्णांक igmpv3_sendpack(काष्ठा sk_buff *skb)
अणु
	काष्ठा igmphdr *pig = igmp_hdr(skb);
	स्थिर पूर्णांक igmplen = skb_tail_poपूर्णांकer(skb) - skb_transport_header(skb);

	pig->csum = ip_compute_csum(igmp_hdr(skb), igmplen);

	वापस ip_local_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
पूर्ण

अटल पूर्णांक grec_size(काष्ठा ip_mc_list *pmc, पूर्णांक type, पूर्णांक gdel, पूर्णांक sdel)
अणु
	वापस माप(काष्ठा igmpv3_grec) + 4*igmp_scount(pmc, type, gdel, sdel);
पूर्ण

अटल काष्ठा sk_buff *add_grhead(काष्ठा sk_buff *skb, काष्ठा ip_mc_list *pmc,
	पूर्णांक type, काष्ठा igmpv3_grec **ppgr, अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा net_device *dev = pmc->पूर्णांकerface->dev;
	काष्ठा igmpv3_report *pih;
	काष्ठा igmpv3_grec *pgr;

	अगर (!skb) अणु
		skb = igmpv3_newpack(dev, mtu);
		अगर (!skb)
			वापस शून्य;
	पूर्ण
	pgr = skb_put(skb, माप(काष्ठा igmpv3_grec));
	pgr->grec_type = type;
	pgr->grec_auxwords = 0;
	pgr->grec_nsrcs = 0;
	pgr->grec_mca = pmc->multiaddr;
	pih = igmpv3_report_hdr(skb);
	pih->ngrec = htons(ntohs(pih->ngrec)+1);
	*ppgr = pgr;
	वापस skb;
पूर्ण

#घोषणा AVAILABLE(skb)	((skb) ? skb_availroom(skb) : 0)

अटल काष्ठा sk_buff *add_grec(काष्ठा sk_buff *skb, काष्ठा ip_mc_list *pmc,
	पूर्णांक type, पूर्णांक gdeleted, पूर्णांक sdeleted)
अणु
	काष्ठा net_device *dev = pmc->पूर्णांकerface->dev;
	काष्ठा net *net = dev_net(dev);
	काष्ठा igmpv3_report *pih;
	काष्ठा igmpv3_grec *pgr = शून्य;
	काष्ठा ip_sf_list *psf, *psf_next, *psf_prev, **psf_list;
	पूर्णांक scount, stotal, first, isquery, truncate;
	अचिन्हित पूर्णांक mtu;

	अगर (pmc->multiaddr == IGMP_ALL_HOSTS)
		वापस skb;
	अगर (ipv4_is_local_multicast(pmc->multiaddr) && !net->ipv4.sysctl_igmp_llm_reports)
		वापस skb;

	mtu = READ_ONCE(dev->mtu);
	अगर (mtu < IPV4_MIN_MTU)
		वापस skb;

	isquery = type == IGMPV3_MODE_IS_INCLUDE ||
		  type == IGMPV3_MODE_IS_EXCLUDE;
	truncate = type == IGMPV3_MODE_IS_EXCLUDE ||
		    type == IGMPV3_CHANGE_TO_EXCLUDE;

	stotal = scount = 0;

	psf_list = sdeleted ? &pmc->tomb : &pmc->sources;

	अगर (!*psf_list)
		जाओ empty_source;

	pih = skb ? igmpv3_report_hdr(skb) : शून्य;

	/* EX and TO_EX get a fresh packet, अगर needed */
	अगर (truncate) अणु
		अगर (pih && pih->ngrec &&
		    AVAILABLE(skb) < grec_size(pmc, type, gdeleted, sdeleted)) अणु
			अगर (skb)
				igmpv3_sendpack(skb);
			skb = igmpv3_newpack(dev, mtu);
		पूर्ण
	पूर्ण
	first = 1;
	psf_prev = शून्य;
	क्रम (psf = *psf_list; psf; psf = psf_next) अणु
		__be32 *psrc;

		psf_next = psf->sf_next;

		अगर (!is_in(pmc, psf, type, gdeleted, sdeleted)) अणु
			psf_prev = psf;
			जारी;
		पूर्ण

		/* Based on RFC3376 5.1. Should not send source-list change
		 * records when there is a filter mode change.
		 */
		अगर (((gdeleted && pmc->sभ_शेषe == MCAST_EXCLUDE) ||
		     (!gdeleted && pmc->crcount)) &&
		    (type == IGMPV3_ALLOW_NEW_SOURCES ||
		     type == IGMPV3_BLOCK_OLD_SOURCES) && psf->sf_crcount)
			जाओ decrease_sf_crcount;

		/* clear marks on query responses */
		अगर (isquery)
			psf->sf_gsresp = 0;

		अगर (AVAILABLE(skb) < माप(__be32) +
		    first*माप(काष्ठा igmpv3_grec)) अणु
			अगर (truncate && !first)
				अवरोध;	 /* truncate these */
			अगर (pgr)
				pgr->grec_nsrcs = htons(scount);
			अगर (skb)
				igmpv3_sendpack(skb);
			skb = igmpv3_newpack(dev, mtu);
			first = 1;
			scount = 0;
		पूर्ण
		अगर (first) अणु
			skb = add_grhead(skb, pmc, type, &pgr, mtu);
			first = 0;
		पूर्ण
		अगर (!skb)
			वापस शून्य;
		psrc = skb_put(skb, माप(__be32));
		*psrc = psf->sf_inaddr;
		scount++; stotal++;
		अगर ((type == IGMPV3_ALLOW_NEW_SOURCES ||
		     type == IGMPV3_BLOCK_OLD_SOURCES) && psf->sf_crcount) अणु
decrease_sf_crcount:
			psf->sf_crcount--;
			अगर ((sdeleted || gdeleted) && psf->sf_crcount == 0) अणु
				अगर (psf_prev)
					psf_prev->sf_next = psf->sf_next;
				अन्यथा
					*psf_list = psf->sf_next;
				kमुक्त(psf);
				जारी;
			पूर्ण
		पूर्ण
		psf_prev = psf;
	पूर्ण

empty_source:
	अगर (!stotal) अणु
		अगर (type == IGMPV3_ALLOW_NEW_SOURCES ||
		    type == IGMPV3_BLOCK_OLD_SOURCES)
			वापस skb;
		अगर (pmc->crcount || isquery) अणु
			/* make sure we have room क्रम group header */
			अगर (skb && AVAILABLE(skb) < माप(काष्ठा igmpv3_grec)) अणु
				igmpv3_sendpack(skb);
				skb = शून्य; /* add_grhead will get a new one */
			पूर्ण
			skb = add_grhead(skb, pmc, type, &pgr, mtu);
		पूर्ण
	पूर्ण
	अगर (pgr)
		pgr->grec_nsrcs = htons(scount);

	अगर (isquery)
		pmc->gsquery = 0;	/* clear query state on report */
	वापस skb;
पूर्ण

अटल पूर्णांक igmpv3_send_report(काष्ठा in_device *in_dev, काष्ठा ip_mc_list *pmc)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा net *net = dev_net(in_dev->dev);
	पूर्णांक type;

	अगर (!pmc) अणु
		rcu_पढ़ो_lock();
		क्रम_each_pmc_rcu(in_dev, pmc) अणु
			अगर (pmc->multiaddr == IGMP_ALL_HOSTS)
				जारी;
			अगर (ipv4_is_local_multicast(pmc->multiaddr) &&
			     !net->ipv4.sysctl_igmp_llm_reports)
				जारी;
			spin_lock_bh(&pmc->lock);
			अगर (pmc->sfcount[MCAST_EXCLUDE])
				type = IGMPV3_MODE_IS_EXCLUDE;
			अन्यथा
				type = IGMPV3_MODE_IS_INCLUDE;
			skb = add_grec(skb, pmc, type, 0, 0);
			spin_unlock_bh(&pmc->lock);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		spin_lock_bh(&pmc->lock);
		अगर (pmc->sfcount[MCAST_EXCLUDE])
			type = IGMPV3_MODE_IS_EXCLUDE;
		अन्यथा
			type = IGMPV3_MODE_IS_INCLUDE;
		skb = add_grec(skb, pmc, type, 0, 0);
		spin_unlock_bh(&pmc->lock);
	पूर्ण
	अगर (!skb)
		वापस 0;
	वापस igmpv3_sendpack(skb);
पूर्ण

/*
 * हटाओ zero-count source records from a source filter list
 */
अटल व्योम igmpv3_clear_zeros(काष्ठा ip_sf_list **ppsf)
अणु
	काष्ठा ip_sf_list *psf_prev, *psf_next, *psf;

	psf_prev = शून्य;
	क्रम (psf = *ppsf; psf; psf = psf_next) अणु
		psf_next = psf->sf_next;
		अगर (psf->sf_crcount == 0) अणु
			अगर (psf_prev)
				psf_prev->sf_next = psf->sf_next;
			अन्यथा
				*ppsf = psf->sf_next;
			kमुक्त(psf);
		पूर्ण अन्यथा
			psf_prev = psf;
	पूर्ण
पूर्ण

अटल व्योम kमुक्त_pmc(काष्ठा ip_mc_list *pmc)
अणु
	ip_sf_list_clear_all(pmc->sources);
	ip_sf_list_clear_all(pmc->tomb);
	kमुक्त(pmc);
पूर्ण

अटल व्योम igmpv3_send_cr(काष्ठा in_device *in_dev)
अणु
	काष्ठा ip_mc_list *pmc, *pmc_prev, *pmc_next;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक type, dtype;

	rcu_पढ़ो_lock();
	spin_lock_bh(&in_dev->mc_tomb_lock);

	/* deleted MCA's */
	pmc_prev = शून्य;
	क्रम (pmc = in_dev->mc_tomb; pmc; pmc = pmc_next) अणु
		pmc_next = pmc->next;
		अगर (pmc->sभ_शेषe == MCAST_INCLUDE) अणु
			type = IGMPV3_BLOCK_OLD_SOURCES;
			dtype = IGMPV3_BLOCK_OLD_SOURCES;
			skb = add_grec(skb, pmc, type, 1, 0);
			skb = add_grec(skb, pmc, dtype, 1, 1);
		पूर्ण
		अगर (pmc->crcount) अणु
			अगर (pmc->sभ_शेषe == MCAST_EXCLUDE) अणु
				type = IGMPV3_CHANGE_TO_INCLUDE;
				skb = add_grec(skb, pmc, type, 1, 0);
			पूर्ण
			pmc->crcount--;
			अगर (pmc->crcount == 0) अणु
				igmpv3_clear_zeros(&pmc->tomb);
				igmpv3_clear_zeros(&pmc->sources);
			पूर्ण
		पूर्ण
		अगर (pmc->crcount == 0 && !pmc->tomb && !pmc->sources) अणु
			अगर (pmc_prev)
				pmc_prev->next = pmc_next;
			अन्यथा
				in_dev->mc_tomb = pmc_next;
			in_dev_put(pmc->पूर्णांकerface);
			kमुक्त_pmc(pmc);
		पूर्ण अन्यथा
			pmc_prev = pmc;
	पूर्ण
	spin_unlock_bh(&in_dev->mc_tomb_lock);

	/* change recs */
	क्रम_each_pmc_rcu(in_dev, pmc) अणु
		spin_lock_bh(&pmc->lock);
		अगर (pmc->sfcount[MCAST_EXCLUDE]) अणु
			type = IGMPV3_BLOCK_OLD_SOURCES;
			dtype = IGMPV3_ALLOW_NEW_SOURCES;
		पूर्ण अन्यथा अणु
			type = IGMPV3_ALLOW_NEW_SOURCES;
			dtype = IGMPV3_BLOCK_OLD_SOURCES;
		पूर्ण
		skb = add_grec(skb, pmc, type, 0, 0);
		skb = add_grec(skb, pmc, dtype, 0, 1);	/* deleted sources */

		/* filter mode changes */
		अगर (pmc->crcount) अणु
			अगर (pmc->sभ_शेषe == MCAST_EXCLUDE)
				type = IGMPV3_CHANGE_TO_EXCLUDE;
			अन्यथा
				type = IGMPV3_CHANGE_TO_INCLUDE;
			skb = add_grec(skb, pmc, type, 0, 0);
			pmc->crcount--;
		पूर्ण
		spin_unlock_bh(&pmc->lock);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!skb)
		वापस;
	(व्योम) igmpv3_sendpack(skb);
पूर्ण

अटल पूर्णांक igmp_send_report(काष्ठा in_device *in_dev, काष्ठा ip_mc_list *pmc,
	पूर्णांक type)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा iphdr *iph;
	काष्ठा igmphdr *ih;
	काष्ठा rtable *rt;
	काष्ठा net_device *dev = in_dev->dev;
	काष्ठा net *net = dev_net(dev);
	__be32	group = pmc ? pmc->multiaddr : 0;
	काष्ठा flowi4 fl4;
	__be32	dst;
	पूर्णांक hlen, tlen;

	अगर (type == IGMPV3_HOST_MEMBERSHIP_REPORT)
		वापस igmpv3_send_report(in_dev, pmc);

	अगर (ipv4_is_local_multicast(group) && !net->ipv4.sysctl_igmp_llm_reports)
		वापस 0;

	अगर (type == IGMP_HOST_LEAVE_MESSAGE)
		dst = IGMP_ALL_ROUTER;
	अन्यथा
		dst = group;

	rt = ip_route_output_ports(net, &fl4, शून्य, dst, 0,
				   0, 0,
				   IPPROTO_IGMP, 0, dev->अगरindex);
	अगर (IS_ERR(rt))
		वापस -1;

	hlen = LL_RESERVED_SPACE(dev);
	tlen = dev->needed_tailroom;
	skb = alloc_skb(IGMP_SIZE + hlen + tlen, GFP_ATOMIC);
	अगर (!skb) अणु
		ip_rt_put(rt);
		वापस -1;
	पूर्ण
	skb->priority = TC_PRIO_CONTROL;

	skb_dst_set(skb, &rt->dst);

	skb_reserve(skb, hlen);

	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	skb_put(skb, माप(काष्ठा iphdr) + 4);

	iph->version  = 4;
	iph->ihl      = (माप(काष्ठा iphdr)+4)>>2;
	iph->tos      = 0xc0;
	iph->frag_off = htons(IP_DF);
	iph->ttl      = 1;
	iph->daddr    = dst;
	iph->saddr    = fl4.saddr;
	iph->protocol = IPPROTO_IGMP;
	ip_select_ident(net, skb, शून्य);
	((u8 *)&iph[1])[0] = IPOPT_RA;
	((u8 *)&iph[1])[1] = 4;
	((u8 *)&iph[1])[2] = 0;
	((u8 *)&iph[1])[3] = 0;

	ih = skb_put(skb, माप(काष्ठा igmphdr));
	ih->type = type;
	ih->code = 0;
	ih->csum = 0;
	ih->group = group;
	ih->csum = ip_compute_csum((व्योम *)ih, माप(काष्ठा igmphdr));

	वापस ip_local_out(net, skb->sk, skb);
पूर्ण

अटल व्योम igmp_gq_समयr_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा in_device *in_dev = from_समयr(in_dev, t, mr_gq_समयr);

	in_dev->mr_gq_running = 0;
	igmpv3_send_report(in_dev, शून्य);
	in_dev_put(in_dev);
पूर्ण

अटल व्योम igmp_अगरc_समयr_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा in_device *in_dev = from_समयr(in_dev, t, mr_अगरc_समयr);

	igmpv3_send_cr(in_dev);
	अगर (in_dev->mr_अगरc_count) अणु
		in_dev->mr_अगरc_count--;
		igmp_अगरc_start_समयr(in_dev,
				     unsolicited_report_पूर्णांकerval(in_dev));
	पूर्ण
	in_dev_put(in_dev);
पूर्ण

अटल व्योम igmp_अगरc_event(काष्ठा in_device *in_dev)
अणु
	काष्ठा net *net = dev_net(in_dev->dev);
	अगर (IGMP_V1_SEEN(in_dev) || IGMP_V2_SEEN(in_dev))
		वापस;
	in_dev->mr_अगरc_count = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;
	igmp_अगरc_start_समयr(in_dev, 1);
पूर्ण


अटल व्योम igmp_समयr_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा ip_mc_list *im = from_समयr(im, t, समयr);
	काष्ठा in_device *in_dev = im->पूर्णांकerface;

	spin_lock(&im->lock);
	im->पंचांग_running = 0;

	अगर (im->unsolicit_count && --im->unsolicit_count)
		igmp_start_समयr(im, unsolicited_report_पूर्णांकerval(in_dev));

	im->reporter = 1;
	spin_unlock(&im->lock);

	अगर (IGMP_V1_SEEN(in_dev))
		igmp_send_report(in_dev, im, IGMP_HOST_MEMBERSHIP_REPORT);
	अन्यथा अगर (IGMP_V2_SEEN(in_dev))
		igmp_send_report(in_dev, im, IGMPV2_HOST_MEMBERSHIP_REPORT);
	अन्यथा
		igmp_send_report(in_dev, im, IGMPV3_HOST_MEMBERSHIP_REPORT);

	ip_ma_put(im);
पूर्ण

/* mark EXCLUDE-mode sources */
अटल पूर्णांक igmp_xmarksources(काष्ठा ip_mc_list *pmc, पूर्णांक nsrcs, __be32 *srcs)
अणु
	काष्ठा ip_sf_list *psf;
	पूर्णांक i, scount;

	scount = 0;
	क्रम (psf = pmc->sources; psf; psf = psf->sf_next) अणु
		अगर (scount == nsrcs)
			अवरोध;
		क्रम (i = 0; i < nsrcs; i++) अणु
			/* skip inactive filters */
			अगर (psf->sf_count[MCAST_INCLUDE] ||
			    pmc->sfcount[MCAST_EXCLUDE] !=
			    psf->sf_count[MCAST_EXCLUDE])
				अवरोध;
			अगर (srcs[i] == psf->sf_inaddr) अणु
				scount++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	pmc->gsquery = 0;
	अगर (scount == nsrcs)	/* all sources excluded */
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक igmp_marksources(काष्ठा ip_mc_list *pmc, पूर्णांक nsrcs, __be32 *srcs)
अणु
	काष्ठा ip_sf_list *psf;
	पूर्णांक i, scount;

	अगर (pmc->sभ_शेषe == MCAST_EXCLUDE)
		वापस igmp_xmarksources(pmc, nsrcs, srcs);

	/* mark INCLUDE-mode sources */
	scount = 0;
	क्रम (psf = pmc->sources; psf; psf = psf->sf_next) अणु
		अगर (scount == nsrcs)
			अवरोध;
		क्रम (i = 0; i < nsrcs; i++)
			अगर (srcs[i] == psf->sf_inaddr) अणु
				psf->sf_gsresp = 1;
				scount++;
				अवरोध;
			पूर्ण
	पूर्ण
	अगर (!scount) अणु
		pmc->gsquery = 0;
		वापस 0;
	पूर्ण
	pmc->gsquery = 1;
	वापस 1;
पूर्ण

/* वापस true अगर packet was dropped */
अटल bool igmp_heard_report(काष्ठा in_device *in_dev, __be32 group)
अणु
	काष्ठा ip_mc_list *im;
	काष्ठा net *net = dev_net(in_dev->dev);

	/* Timers are only set क्रम non-local groups */

	अगर (group == IGMP_ALL_HOSTS)
		वापस false;
	अगर (ipv4_is_local_multicast(group) && !net->ipv4.sysctl_igmp_llm_reports)
		वापस false;

	rcu_पढ़ो_lock();
	क्रम_each_pmc_rcu(in_dev, im) अणु
		अगर (im->multiaddr == group) अणु
			igmp_stop_समयr(im);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस false;
पूर्ण

/* वापस true अगर packet was dropped */
अटल bool igmp_heard_query(काष्ठा in_device *in_dev, काष्ठा sk_buff *skb,
	पूर्णांक len)
अणु
	काष्ठा igmphdr 		*ih = igmp_hdr(skb);
	काष्ठा igmpv3_query *ih3 = igmpv3_query_hdr(skb);
	काष्ठा ip_mc_list	*im;
	__be32			group = ih->group;
	पूर्णांक			max_delay;
	पूर्णांक			mark = 0;
	काष्ठा net		*net = dev_net(in_dev->dev);


	अगर (len == 8) अणु
		अगर (ih->code == 0) अणु
			/* Alas, old v1 router presents here. */

			max_delay = IGMP_QUERY_RESPONSE_INTERVAL;
			in_dev->mr_v1_seen = jअगरfies +
				(in_dev->mr_qrv * in_dev->mr_qi) +
				in_dev->mr_qri;
			group = 0;
		पूर्ण अन्यथा अणु
			/* v2 router present */
			max_delay = ih->code*(HZ/IGMP_TIMER_SCALE);
			in_dev->mr_v2_seen = jअगरfies +
				(in_dev->mr_qrv * in_dev->mr_qi) +
				in_dev->mr_qri;
		पूर्ण
		/* cancel the पूर्णांकerface change समयr */
		in_dev->mr_अगरc_count = 0;
		अगर (del_समयr(&in_dev->mr_अगरc_समयr))
			__in_dev_put(in_dev);
		/* clear deleted report items */
		igmpv3_clear_delrec(in_dev);
	पूर्ण अन्यथा अगर (len < 12) अणु
		वापस true;	/* ignore bogus packet; मुक्तd by caller */
	पूर्ण अन्यथा अगर (IGMP_V1_SEEN(in_dev)) अणु
		/* This is a v3 query with v1 queriers present */
		max_delay = IGMP_QUERY_RESPONSE_INTERVAL;
		group = 0;
	पूर्ण अन्यथा अगर (IGMP_V2_SEEN(in_dev)) अणु
		/* this is a v3 query with v2 queriers present;
		 * Interpretation of the max_delay code is problematic here.
		 * A real v2 host would use ih_code directly, जबतक v3 has a
		 * dअगरferent encoding. We use the v3 encoding as more likely
		 * to be पूर्णांकended in a v3 query.
		 */
		max_delay = IGMPV3_MRC(ih3->code)*(HZ/IGMP_TIMER_SCALE);
		अगर (!max_delay)
			max_delay = 1;	/* can't mod w/ 0 */
	पूर्ण अन्यथा अणु /* v3 */
		अगर (!pskb_may_pull(skb, माप(काष्ठा igmpv3_query)))
			वापस true;

		ih3 = igmpv3_query_hdr(skb);
		अगर (ih3->nsrcs) अणु
			अगर (!pskb_may_pull(skb, माप(काष्ठा igmpv3_query)
					   + ntohs(ih3->nsrcs)*माप(__be32)))
				वापस true;
			ih3 = igmpv3_query_hdr(skb);
		पूर्ण

		max_delay = IGMPV3_MRC(ih3->code)*(HZ/IGMP_TIMER_SCALE);
		अगर (!max_delay)
			max_delay = 1;	/* can't mod w/ 0 */
		in_dev->mr_maxdelay = max_delay;

		/* RFC3376, 4.1.6. QRV and 4.1.7. QQIC, when the most recently
		 * received value was zero, use the शेष or अटलally
		 * configured value.
		 */
		in_dev->mr_qrv = ih3->qrv ?: net->ipv4.sysctl_igmp_qrv;
		in_dev->mr_qi = IGMPV3_QQIC(ih3->qqic)*HZ ?: IGMP_QUERY_INTERVAL;

		/* RFC3376, 8.3. Query Response Interval:
		 * The number of seconds represented by the [Query Response
		 * Interval] must be less than the [Query Interval].
		 */
		अगर (in_dev->mr_qri >= in_dev->mr_qi)
			in_dev->mr_qri = (in_dev->mr_qi/HZ - 1)*HZ;

		अगर (!group) अणु /* general query */
			अगर (ih3->nsrcs)
				वापस true;	/* no sources allowed */
			igmp_gq_start_समयr(in_dev);
			वापस false;
		पूर्ण
		/* mark sources to include, अगर group & source-specअगरic */
		mark = ih3->nsrcs != 0;
	पूर्ण

	/*
	 * - Start the समयrs in all of our membership records
	 *   that the query applies to क्रम the पूर्णांकerface on
	 *   which the query arrived excl. those that beदीर्घ
	 *   to a "local" group (224.0.0.X)
	 * - For समयrs alपढ़ोy running check अगर they need to
	 *   be reset.
	 * - Use the igmp->igmp_code field as the maximum
	 *   delay possible
	 */
	rcu_पढ़ो_lock();
	क्रम_each_pmc_rcu(in_dev, im) अणु
		पूर्णांक changed;

		अगर (group && group != im->multiaddr)
			जारी;
		अगर (im->multiaddr == IGMP_ALL_HOSTS)
			जारी;
		अगर (ipv4_is_local_multicast(im->multiaddr) &&
		    !net->ipv4.sysctl_igmp_llm_reports)
			जारी;
		spin_lock_bh(&im->lock);
		अगर (im->पंचांग_running)
			im->gsquery = im->gsquery && mark;
		अन्यथा
			im->gsquery = mark;
		changed = !im->gsquery ||
			igmp_marksources(im, ntohs(ih3->nsrcs), ih3->srcs);
		spin_unlock_bh(&im->lock);
		अगर (changed)
			igmp_mod_समयr(im, max_delay);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस false;
पूर्ण

/* called in rcu_पढ़ो_lock() section */
पूर्णांक igmp_rcv(काष्ठा sk_buff *skb)
अणु
	/* This basically follows the spec line by line -- see RFC1112 */
	काष्ठा igmphdr *ih;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा in_device *in_dev;
	पूर्णांक len = skb->len;
	bool dropped = true;

	अगर (netअगर_is_l3_master(dev)) अणु
		dev = dev_get_by_index_rcu(dev_net(dev), IPCB(skb)->iअगर);
		अगर (!dev)
			जाओ drop;
	पूर्ण

	in_dev = __in_dev_get_rcu(dev);
	अगर (!in_dev)
		जाओ drop;

	अगर (!pskb_may_pull(skb, माप(काष्ठा igmphdr)))
		जाओ drop;

	अगर (skb_checksum_simple_validate(skb))
		जाओ drop;

	ih = igmp_hdr(skb);
	चयन (ih->type) अणु
	हाल IGMP_HOST_MEMBERSHIP_QUERY:
		dropped = igmp_heard_query(in_dev, skb, len);
		अवरोध;
	हाल IGMP_HOST_MEMBERSHIP_REPORT:
	हाल IGMPV2_HOST_MEMBERSHIP_REPORT:
		/* Is it our report looped back? */
		अगर (rt_is_output_route(skb_rtable(skb)))
			अवरोध;
		/* करोn't rely on MC router hearing unicast reports */
		अगर (skb->pkt_type == PACKET_MULTICAST ||
		    skb->pkt_type == PACKET_BROADCAST)
			dropped = igmp_heard_report(in_dev, ih->group);
		अवरोध;
	हाल IGMP_PIM:
#अगर_घोषित CONFIG_IP_PIMSM_V1
		वापस pim_rcv_v1(skb);
#पूर्ण_अगर
	हाल IGMPV3_HOST_MEMBERSHIP_REPORT:
	हाल IGMP_DVMRP:
	हाल IGMP_TRACE:
	हाल IGMP_HOST_LEAVE_MESSAGE:
	हाल IGMP_MTRACE:
	हाल IGMP_MTRACE_RESP:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

drop:
	अगर (dropped)
		kमुक्त_skb(skb);
	अन्यथा
		consume_skb(skb);
	वापस 0;
पूर्ण

#पूर्ण_अगर


/*
 *	Add a filter to a device
 */

अटल व्योम ip_mc_filter_add(काष्ठा in_device *in_dev, __be32 addr)
अणु
	अक्षर buf[MAX_ADDR_LEN];
	काष्ठा net_device *dev = in_dev->dev;

	/* Checking क्रम IFF_MULTICAST here is WRONG-WRONG-WRONG.
	   We will get multicast token leakage, when IFF_MULTICAST
	   is changed. This check should be करोne in nकरो_set_rx_mode
	   routine. Something sort of:
	   अगर (dev->mc_list && dev->flags&IFF_MULTICAST) अणु करो it; पूर्ण
	   --ANK
	   */
	अगर (arp_mc_map(addr, buf, dev, 0) == 0)
		dev_mc_add(dev, buf);
पूर्ण

/*
 *	Remove a filter from a device
 */

अटल व्योम ip_mc_filter_del(काष्ठा in_device *in_dev, __be32 addr)
अणु
	अक्षर buf[MAX_ADDR_LEN];
	काष्ठा net_device *dev = in_dev->dev;

	अगर (arp_mc_map(addr, buf, dev, 0) == 0)
		dev_mc_del(dev, buf);
पूर्ण

#अगर_घोषित CONFIG_IP_MULTICAST
/*
 * deleted ip_mc_list manipulation
 */
अटल व्योम igmpv3_add_delrec(काष्ठा in_device *in_dev, काष्ठा ip_mc_list *im,
			      gfp_t gfp)
अणु
	काष्ठा ip_mc_list *pmc;
	काष्ठा net *net = dev_net(in_dev->dev);

	/* this is an "ip_mc_list" क्रम convenience; only the fields below
	 * are actually used. In particular, the refcnt and users are not
	 * used क्रम management of the delete list. Using the same काष्ठाure
	 * क्रम deleted items allows change reports to use common code with
	 * non-deleted or query-response MCA's.
	 */
	pmc = kzalloc(माप(*pmc), gfp);
	अगर (!pmc)
		वापस;
	spin_lock_init(&pmc->lock);
	spin_lock_bh(&im->lock);
	pmc->पूर्णांकerface = im->पूर्णांकerface;
	in_dev_hold(in_dev);
	pmc->multiaddr = im->multiaddr;
	pmc->crcount = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;
	pmc->sभ_शेषe = im->sभ_शेषe;
	अगर (pmc->sभ_शेषe == MCAST_INCLUDE) अणु
		काष्ठा ip_sf_list *psf;

		pmc->tomb = im->tomb;
		pmc->sources = im->sources;
		im->tomb = im->sources = शून्य;
		क्रम (psf = pmc->sources; psf; psf = psf->sf_next)
			psf->sf_crcount = pmc->crcount;
	पूर्ण
	spin_unlock_bh(&im->lock);

	spin_lock_bh(&in_dev->mc_tomb_lock);
	pmc->next = in_dev->mc_tomb;
	in_dev->mc_tomb = pmc;
	spin_unlock_bh(&in_dev->mc_tomb_lock);
पूर्ण

/*
 * restore ip_mc_list deleted records
 */
अटल व्योम igmpv3_del_delrec(काष्ठा in_device *in_dev, काष्ठा ip_mc_list *im)
अणु
	काष्ठा ip_mc_list *pmc, *pmc_prev;
	काष्ठा ip_sf_list *psf;
	काष्ठा net *net = dev_net(in_dev->dev);
	__be32 multiaddr = im->multiaddr;

	spin_lock_bh(&in_dev->mc_tomb_lock);
	pmc_prev = शून्य;
	क्रम (pmc = in_dev->mc_tomb; pmc; pmc = pmc->next) अणु
		अगर (pmc->multiaddr == multiaddr)
			अवरोध;
		pmc_prev = pmc;
	पूर्ण
	अगर (pmc) अणु
		अगर (pmc_prev)
			pmc_prev->next = pmc->next;
		अन्यथा
			in_dev->mc_tomb = pmc->next;
	पूर्ण
	spin_unlock_bh(&in_dev->mc_tomb_lock);

	spin_lock_bh(&im->lock);
	अगर (pmc) अणु
		im->पूर्णांकerface = pmc->पूर्णांकerface;
		अगर (im->sभ_शेषe == MCAST_INCLUDE) अणु
			swap(im->tomb, pmc->tomb);
			swap(im->sources, pmc->sources);
			क्रम (psf = im->sources; psf; psf = psf->sf_next)
				psf->sf_crcount = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;
		पूर्ण अन्यथा अणु
			im->crcount = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;
		पूर्ण
		in_dev_put(pmc->पूर्णांकerface);
		kमुक्त_pmc(pmc);
	पूर्ण
	spin_unlock_bh(&im->lock);
पूर्ण

/*
 * flush ip_mc_list deleted records
 */
अटल व्योम igmpv3_clear_delrec(काष्ठा in_device *in_dev)
अणु
	काष्ठा ip_mc_list *pmc, *nextpmc;

	spin_lock_bh(&in_dev->mc_tomb_lock);
	pmc = in_dev->mc_tomb;
	in_dev->mc_tomb = शून्य;
	spin_unlock_bh(&in_dev->mc_tomb_lock);

	क्रम (; pmc; pmc = nextpmc) अणु
		nextpmc = pmc->next;
		ip_mc_clear_src(pmc);
		in_dev_put(pmc->पूर्णांकerface);
		kमुक्त_pmc(pmc);
	पूर्ण
	/* clear dead sources, too */
	rcu_पढ़ो_lock();
	क्रम_each_pmc_rcu(in_dev, pmc) अणु
		काष्ठा ip_sf_list *psf;

		spin_lock_bh(&pmc->lock);
		psf = pmc->tomb;
		pmc->tomb = शून्य;
		spin_unlock_bh(&pmc->lock);
		ip_sf_list_clear_all(psf);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर

अटल व्योम __igmp_group_dropped(काष्ठा ip_mc_list *im, gfp_t gfp)
अणु
	काष्ठा in_device *in_dev = im->पूर्णांकerface;
#अगर_घोषित CONFIG_IP_MULTICAST
	काष्ठा net *net = dev_net(in_dev->dev);
	पूर्णांक reporter;
#पूर्ण_अगर

	अगर (im->loaded) अणु
		im->loaded = 0;
		ip_mc_filter_del(in_dev, im->multiaddr);
	पूर्ण

#अगर_घोषित CONFIG_IP_MULTICAST
	अगर (im->multiaddr == IGMP_ALL_HOSTS)
		वापस;
	अगर (ipv4_is_local_multicast(im->multiaddr) && !net->ipv4.sysctl_igmp_llm_reports)
		वापस;

	reporter = im->reporter;
	igmp_stop_समयr(im);

	अगर (!in_dev->dead) अणु
		अगर (IGMP_V1_SEEN(in_dev))
			वापस;
		अगर (IGMP_V2_SEEN(in_dev)) अणु
			अगर (reporter)
				igmp_send_report(in_dev, im, IGMP_HOST_LEAVE_MESSAGE);
			वापस;
		पूर्ण
		/* IGMPv3 */
		igmpv3_add_delrec(in_dev, im, gfp);

		igmp_अगरc_event(in_dev);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम igmp_group_dropped(काष्ठा ip_mc_list *im)
अणु
	__igmp_group_dropped(im, GFP_KERNEL);
पूर्ण

अटल व्योम igmp_group_added(काष्ठा ip_mc_list *im)
अणु
	काष्ठा in_device *in_dev = im->पूर्णांकerface;
#अगर_घोषित CONFIG_IP_MULTICAST
	काष्ठा net *net = dev_net(in_dev->dev);
#पूर्ण_अगर

	अगर (im->loaded == 0) अणु
		im->loaded = 1;
		ip_mc_filter_add(in_dev, im->multiaddr);
	पूर्ण

#अगर_घोषित CONFIG_IP_MULTICAST
	अगर (im->multiaddr == IGMP_ALL_HOSTS)
		वापस;
	अगर (ipv4_is_local_multicast(im->multiaddr) && !net->ipv4.sysctl_igmp_llm_reports)
		वापस;

	अगर (in_dev->dead)
		वापस;

	im->unsolicit_count = net->ipv4.sysctl_igmp_qrv;
	अगर (IGMP_V1_SEEN(in_dev) || IGMP_V2_SEEN(in_dev)) अणु
		spin_lock_bh(&im->lock);
		igmp_start_समयr(im, IGMP_INITIAL_REPORT_DELAY);
		spin_unlock_bh(&im->lock);
		वापस;
	पूर्ण
	/* अन्यथा, v3 */

	/* Based on RFC3376 5.1, क्रम newly added INCLUDE SSM, we should
	 * not send filter-mode change record as the mode should be from
	 * IN() to IN(A).
	 */
	अगर (im->sभ_शेषe == MCAST_EXCLUDE)
		im->crcount = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;

	igmp_अगरc_event(in_dev);
#पूर्ण_अगर
पूर्ण


/*
 *	Multicast list managers
 */

अटल u32 ip_mc_hash(स्थिर काष्ठा ip_mc_list *im)
अणु
	वापस hash_32((__क्रमce u32)im->multiaddr, MC_HASH_SZ_LOG);
पूर्ण

अटल व्योम ip_mc_hash_add(काष्ठा in_device *in_dev,
			   काष्ठा ip_mc_list *im)
अणु
	काष्ठा ip_mc_list __rcu **mc_hash;
	u32 hash;

	mc_hash = rtnl_dereference(in_dev->mc_hash);
	अगर (mc_hash) अणु
		hash = ip_mc_hash(im);
		im->next_hash = mc_hash[hash];
		rcu_assign_poपूर्णांकer(mc_hash[hash], im);
		वापस;
	पूर्ण

	/* करो not use a hash table क्रम small number of items */
	अगर (in_dev->mc_count < 4)
		वापस;

	mc_hash = kzalloc(माप(काष्ठा ip_mc_list *) << MC_HASH_SZ_LOG,
			  GFP_KERNEL);
	अगर (!mc_hash)
		वापस;

	क्रम_each_pmc_rtnl(in_dev, im) अणु
		hash = ip_mc_hash(im);
		im->next_hash = mc_hash[hash];
		RCU_INIT_POINTER(mc_hash[hash], im);
	पूर्ण

	rcu_assign_poपूर्णांकer(in_dev->mc_hash, mc_hash);
पूर्ण

अटल व्योम ip_mc_hash_हटाओ(काष्ठा in_device *in_dev,
			      काष्ठा ip_mc_list *im)
अणु
	काष्ठा ip_mc_list __rcu **mc_hash = rtnl_dereference(in_dev->mc_hash);
	काष्ठा ip_mc_list *aux;

	अगर (!mc_hash)
		वापस;
	mc_hash += ip_mc_hash(im);
	जबतक ((aux = rtnl_dereference(*mc_hash)) != im)
		mc_hash = &aux->next_hash;
	*mc_hash = im->next_hash;
पूर्ण


/*
 *	A socket has joined a multicast group on device dev.
 */
अटल व्योम ____ip_mc_inc_group(काष्ठा in_device *in_dev, __be32 addr,
				अचिन्हित पूर्णांक mode, gfp_t gfp)
अणु
	काष्ठा ip_mc_list *im;

	ASSERT_RTNL();

	क्रम_each_pmc_rtnl(in_dev, im) अणु
		अगर (im->multiaddr == addr) अणु
			im->users++;
			ip_mc_add_src(in_dev, &addr, mode, 0, शून्य, 0);
			जाओ out;
		पूर्ण
	पूर्ण

	im = kzalloc(माप(*im), gfp);
	अगर (!im)
		जाओ out;

	im->users = 1;
	im->पूर्णांकerface = in_dev;
	in_dev_hold(in_dev);
	im->multiaddr = addr;
	/* initial mode is (EX, empty) */
	im->sभ_शेषe = mode;
	im->sfcount[mode] = 1;
	refcount_set(&im->refcnt, 1);
	spin_lock_init(&im->lock);
#अगर_घोषित CONFIG_IP_MULTICAST
	समयr_setup(&im->समयr, igmp_समयr_expire, 0);
#पूर्ण_अगर

	im->next_rcu = in_dev->mc_list;
	in_dev->mc_count++;
	rcu_assign_poपूर्णांकer(in_dev->mc_list, im);

	ip_mc_hash_add(in_dev, im);

#अगर_घोषित CONFIG_IP_MULTICAST
	igmpv3_del_delrec(in_dev, im);
#पूर्ण_अगर
	igmp_group_added(im);
	अगर (!in_dev->dead)
		ip_rt_multicast_event(in_dev);
out:
	वापस;
पूर्ण

व्योम __ip_mc_inc_group(काष्ठा in_device *in_dev, __be32 addr, gfp_t gfp)
अणु
	____ip_mc_inc_group(in_dev, addr, MCAST_EXCLUDE, gfp);
पूर्ण
EXPORT_SYMBOL(__ip_mc_inc_group);

व्योम ip_mc_inc_group(काष्ठा in_device *in_dev, __be32 addr)
अणु
	__ip_mc_inc_group(in_dev, addr, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(ip_mc_inc_group);

अटल पूर्णांक ip_mc_check_iphdr(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक offset = skb_network_offset(skb) + माप(*iph);

	अगर (!pskb_may_pull(skb, offset))
		वापस -EINVAL;

	iph = ip_hdr(skb);

	अगर (iph->version != 4 || ip_hdrlen(skb) < माप(*iph))
		वापस -EINVAL;

	offset += ip_hdrlen(skb) - माप(*iph);

	अगर (!pskb_may_pull(skb, offset))
		वापस -EINVAL;

	iph = ip_hdr(skb);

	अगर (unlikely(ip_fast_csum((u8 *)iph, iph->ihl)))
		वापस -EINVAL;

	len = skb_network_offset(skb) + ntohs(iph->tot_len);
	अगर (skb->len < len || len < offset)
		वापस -EINVAL;

	skb_set_transport_header(skb, offset);

	वापस 0;
पूर्ण

अटल पूर्णांक ip_mc_check_igmp_reportv3(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = skb_transport_offset(skb);

	len += माप(काष्ठा igmpv3_report);

	वापस ip_mc_may_pull(skb, len) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक ip_mc_check_igmp_query(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक transport_len = ip_transport_len(skb);
	अचिन्हित पूर्णांक len;

	/* IGMPvअणु1,2पूर्ण? */
	अगर (transport_len != माप(काष्ठा igmphdr)) अणु
		/* or IGMPv3? */
		अगर (transport_len < माप(काष्ठा igmpv3_query))
			वापस -EINVAL;

		len = skb_transport_offset(skb) + माप(काष्ठा igmpv3_query);
		अगर (!ip_mc_may_pull(skb, len))
			वापस -EINVAL;
	पूर्ण

	/* RFC2236+RFC3376 (IGMPv2+IGMPv3) require the multicast link layer
	 * all-प्रणालीs destination addresses (224.0.0.1) क्रम general queries
	 */
	अगर (!igmp_hdr(skb)->group &&
	    ip_hdr(skb)->daddr != htonl(INADDR_ALLHOSTS_GROUP))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ip_mc_check_igmp_msg(काष्ठा sk_buff *skb)
अणु
	चयन (igmp_hdr(skb)->type) अणु
	हाल IGMP_HOST_LEAVE_MESSAGE:
	हाल IGMP_HOST_MEMBERSHIP_REPORT:
	हाल IGMPV2_HOST_MEMBERSHIP_REPORT:
		वापस 0;
	हाल IGMPV3_HOST_MEMBERSHIP_REPORT:
		वापस ip_mc_check_igmp_reportv3(skb);
	हाल IGMP_HOST_MEMBERSHIP_QUERY:
		वापस ip_mc_check_igmp_query(skb);
	शेष:
		वापस -ENOMSG;
	पूर्ण
पूर्ण

अटल __sum16 ip_mc_validate_checksum(काष्ठा sk_buff *skb)
अणु
	वापस skb_checksum_simple_validate(skb);
पूर्ण

अटल पूर्णांक ip_mc_check_igmp_csum(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = skb_transport_offset(skb) + माप(काष्ठा igmphdr);
	अचिन्हित पूर्णांक transport_len = ip_transport_len(skb);
	काष्ठा sk_buff *skb_chk;

	अगर (!ip_mc_may_pull(skb, len))
		वापस -EINVAL;

	skb_chk = skb_checksum_trimmed(skb, transport_len,
				       ip_mc_validate_checksum);
	अगर (!skb_chk)
		वापस -EINVAL;

	अगर (skb_chk != skb)
		kमुक्त_skb(skb_chk);

	वापस 0;
पूर्ण

/**
 * ip_mc_check_igmp - checks whether this is a sane IGMP packet
 * @skb: the skb to validate
 *
 * Checks whether an IPv4 packet is a valid IGMP packet. If so sets
 * skb transport header accordingly and वापसs zero.
 *
 * -EINVAL: A broken packet was detected, i.e. it violates some पूर्णांकernet
 *  standard
 * -ENOMSG: IP header validation succeeded but it is not an IGMP packet.
 * -ENOMEM: A memory allocation failure happened.
 *
 * Caller needs to set the skb network header and मुक्त any वापसed skb अगर it
 * dअगरfers from the provided skb.
 */
पूर्णांक ip_mc_check_igmp(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = ip_mc_check_iphdr(skb);

	अगर (ret < 0)
		वापस ret;

	अगर (ip_hdr(skb)->protocol != IPPROTO_IGMP)
		वापस -ENOMSG;

	ret = ip_mc_check_igmp_csum(skb);
	अगर (ret < 0)
		वापस ret;

	वापस ip_mc_check_igmp_msg(skb);
पूर्ण
EXPORT_SYMBOL(ip_mc_check_igmp);

/*
 *	Resend IGMP JOIN report; used by netdev notअगरier.
 */
अटल व्योम ip_mc_rejoin_groups(काष्ठा in_device *in_dev)
अणु
#अगर_घोषित CONFIG_IP_MULTICAST
	काष्ठा ip_mc_list *im;
	पूर्णांक type;
	काष्ठा net *net = dev_net(in_dev->dev);

	ASSERT_RTNL();

	क्रम_each_pmc_rtnl(in_dev, im) अणु
		अगर (im->multiaddr == IGMP_ALL_HOSTS)
			जारी;
		अगर (ipv4_is_local_multicast(im->multiaddr) &&
		    !net->ipv4.sysctl_igmp_llm_reports)
			जारी;

		/* a failover is happening and चयनes
		 * must be notअगरied immediately
		 */
		अगर (IGMP_V1_SEEN(in_dev))
			type = IGMP_HOST_MEMBERSHIP_REPORT;
		अन्यथा अगर (IGMP_V2_SEEN(in_dev))
			type = IGMPV2_HOST_MEMBERSHIP_REPORT;
		अन्यथा
			type = IGMPV3_HOST_MEMBERSHIP_REPORT;
		igmp_send_report(in_dev, im, type);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 *	A socket has left a multicast group on device dev
 */

व्योम __ip_mc_dec_group(काष्ठा in_device *in_dev, __be32 addr, gfp_t gfp)
अणु
	काष्ठा ip_mc_list *i;
	काष्ठा ip_mc_list __rcu **ip;

	ASSERT_RTNL();

	क्रम (ip = &in_dev->mc_list;
	     (i = rtnl_dereference(*ip)) != शून्य;
	     ip = &i->next_rcu) अणु
		अगर (i->multiaddr == addr) अणु
			अगर (--i->users == 0) अणु
				ip_mc_hash_हटाओ(in_dev, i);
				*ip = i->next_rcu;
				in_dev->mc_count--;
				__igmp_group_dropped(i, gfp);
				ip_mc_clear_src(i);

				अगर (!in_dev->dead)
					ip_rt_multicast_event(in_dev);

				ip_ma_put(i);
				वापस;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__ip_mc_dec_group);

/* Device changing type */

व्योम ip_mc_unmap(काष्ठा in_device *in_dev)
अणु
	काष्ठा ip_mc_list *pmc;

	ASSERT_RTNL();

	क्रम_each_pmc_rtnl(in_dev, pmc)
		igmp_group_dropped(pmc);
पूर्ण

व्योम ip_mc_remap(काष्ठा in_device *in_dev)
अणु
	काष्ठा ip_mc_list *pmc;

	ASSERT_RTNL();

	क्रम_each_pmc_rtnl(in_dev, pmc) अणु
#अगर_घोषित CONFIG_IP_MULTICAST
		igmpv3_del_delrec(in_dev, pmc);
#पूर्ण_अगर
		igmp_group_added(pmc);
	पूर्ण
पूर्ण

/* Device going करोwn */

व्योम ip_mc_करोwn(काष्ठा in_device *in_dev)
अणु
	काष्ठा ip_mc_list *pmc;

	ASSERT_RTNL();

	क्रम_each_pmc_rtnl(in_dev, pmc)
		igmp_group_dropped(pmc);

#अगर_घोषित CONFIG_IP_MULTICAST
	in_dev->mr_अगरc_count = 0;
	अगर (del_समयr(&in_dev->mr_अगरc_समयr))
		__in_dev_put(in_dev);
	in_dev->mr_gq_running = 0;
	अगर (del_समयr(&in_dev->mr_gq_समयr))
		__in_dev_put(in_dev);
#पूर्ण_अगर

	ip_mc_dec_group(in_dev, IGMP_ALL_HOSTS);
पूर्ण

#अगर_घोषित CONFIG_IP_MULTICAST
अटल व्योम ip_mc_reset(काष्ठा in_device *in_dev)
अणु
	काष्ठा net *net = dev_net(in_dev->dev);

	in_dev->mr_qi = IGMP_QUERY_INTERVAL;
	in_dev->mr_qri = IGMP_QUERY_RESPONSE_INTERVAL;
	in_dev->mr_qrv = net->ipv4.sysctl_igmp_qrv;
पूर्ण
#अन्यथा
अटल व्योम ip_mc_reset(काष्ठा in_device *in_dev)
अणु
पूर्ण
#पूर्ण_अगर

व्योम ip_mc_init_dev(काष्ठा in_device *in_dev)
अणु
	ASSERT_RTNL();

#अगर_घोषित CONFIG_IP_MULTICAST
	समयr_setup(&in_dev->mr_gq_समयr, igmp_gq_समयr_expire, 0);
	समयr_setup(&in_dev->mr_अगरc_समयr, igmp_अगरc_समयr_expire, 0);
#पूर्ण_अगर
	ip_mc_reset(in_dev);

	spin_lock_init(&in_dev->mc_tomb_lock);
पूर्ण

/* Device going up */

व्योम ip_mc_up(काष्ठा in_device *in_dev)
अणु
	काष्ठा ip_mc_list *pmc;

	ASSERT_RTNL();

	ip_mc_reset(in_dev);
	ip_mc_inc_group(in_dev, IGMP_ALL_HOSTS);

	क्रम_each_pmc_rtnl(in_dev, pmc) अणु
#अगर_घोषित CONFIG_IP_MULTICAST
		igmpv3_del_delrec(in_dev, pmc);
#पूर्ण_अगर
		igmp_group_added(pmc);
	पूर्ण
पूर्ण

/*
 *	Device is about to be destroyed: clean up.
 */

व्योम ip_mc_destroy_dev(काष्ठा in_device *in_dev)
अणु
	काष्ठा ip_mc_list *i;

	ASSERT_RTNL();

	/* Deactivate समयrs */
	ip_mc_करोwn(in_dev);
#अगर_घोषित CONFIG_IP_MULTICAST
	igmpv3_clear_delrec(in_dev);
#पूर्ण_अगर

	जबतक ((i = rtnl_dereference(in_dev->mc_list)) != शून्य) अणु
		in_dev->mc_list = i->next_rcu;
		in_dev->mc_count--;
		ip_mc_clear_src(i);
		ip_ma_put(i);
	पूर्ण
पूर्ण

/* RTNL is locked */
अटल काष्ठा in_device *ip_mc_find_dev(काष्ठा net *net, काष्ठा ip_mreqn *imr)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा in_device *idev = शून्य;

	अगर (imr->imr_अगरindex) अणु
		idev = inetdev_by_index(net, imr->imr_अगरindex);
		वापस idev;
	पूर्ण
	अगर (imr->imr_address.s_addr) अणु
		dev = __ip_dev_find(net, imr->imr_address.s_addr, false);
		अगर (!dev)
			वापस शून्य;
	पूर्ण

	अगर (!dev) अणु
		काष्ठा rtable *rt = ip_route_output(net,
						    imr->imr_multiaddr.s_addr,
						    0, 0, 0);
		अगर (!IS_ERR(rt)) अणु
			dev = rt->dst.dev;
			ip_rt_put(rt);
		पूर्ण
	पूर्ण
	अगर (dev) अणु
		imr->imr_अगरindex = dev->अगरindex;
		idev = __in_dev_get_rtnl(dev);
	पूर्ण
	वापस idev;
पूर्ण

/*
 *	Join a socket to a group
 */

अटल पूर्णांक ip_mc_del1_src(काष्ठा ip_mc_list *pmc, पूर्णांक sभ_शेषe,
	__be32 *psfsrc)
अणु
	काष्ठा ip_sf_list *psf, *psf_prev;
	पूर्णांक rv = 0;

	psf_prev = शून्य;
	क्रम (psf = pmc->sources; psf; psf = psf->sf_next) अणु
		अगर (psf->sf_inaddr == *psfsrc)
			अवरोध;
		psf_prev = psf;
	पूर्ण
	अगर (!psf || psf->sf_count[sभ_शेषe] == 0) अणु
		/* source filter not found, or count wrong =>  bug */
		वापस -ESRCH;
	पूर्ण
	psf->sf_count[sभ_शेषe]--;
	अगर (psf->sf_count[sभ_शेषe] == 0) अणु
		ip_rt_multicast_event(pmc->पूर्णांकerface);
	पूर्ण
	अगर (!psf->sf_count[MCAST_INCLUDE] && !psf->sf_count[MCAST_EXCLUDE]) अणु
#अगर_घोषित CONFIG_IP_MULTICAST
		काष्ठा in_device *in_dev = pmc->पूर्णांकerface;
		काष्ठा net *net = dev_net(in_dev->dev);
#पूर्ण_अगर

		/* no more filters क्रम this source */
		अगर (psf_prev)
			psf_prev->sf_next = psf->sf_next;
		अन्यथा
			pmc->sources = psf->sf_next;
#अगर_घोषित CONFIG_IP_MULTICAST
		अगर (psf->sf_oldin &&
		    !IGMP_V1_SEEN(in_dev) && !IGMP_V2_SEEN(in_dev)) अणु
			psf->sf_crcount = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;
			psf->sf_next = pmc->tomb;
			pmc->tomb = psf;
			rv = 1;
		पूर्ण अन्यथा
#पूर्ण_अगर
			kमुक्त(psf);
	पूर्ण
	वापस rv;
पूर्ण

#अगर_अघोषित CONFIG_IP_MULTICAST
#घोषणा igmp_अगरc_event(x)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक ip_mc_del_src(काष्ठा in_device *in_dev, __be32 *pmca, पूर्णांक sभ_शेषe,
			 पूर्णांक sfcount, __be32 *psfsrc, पूर्णांक delta)
अणु
	काष्ठा ip_mc_list *pmc;
	पूर्णांक	changerec = 0;
	पूर्णांक	i, err;

	अगर (!in_dev)
		वापस -ENODEV;
	rcu_पढ़ो_lock();
	क्रम_each_pmc_rcu(in_dev, pmc) अणु
		अगर (*pmca == pmc->multiaddr)
			अवरोध;
	पूर्ण
	अगर (!pmc) अणु
		/* MCA not found?? bug */
		rcu_पढ़ो_unlock();
		वापस -ESRCH;
	पूर्ण
	spin_lock_bh(&pmc->lock);
	rcu_पढ़ो_unlock();
#अगर_घोषित CONFIG_IP_MULTICAST
	sf_markstate(pmc);
#पूर्ण_अगर
	अगर (!delta) अणु
		err = -EINVAL;
		अगर (!pmc->sfcount[sभ_शेषe])
			जाओ out_unlock;
		pmc->sfcount[sभ_शेषe]--;
	पूर्ण
	err = 0;
	क्रम (i = 0; i < sfcount; i++) अणु
		पूर्णांक rv = ip_mc_del1_src(pmc, sभ_शेषe, &psfsrc[i]);

		changerec |= rv > 0;
		अगर (!err && rv < 0)
			err = rv;
	पूर्ण
	अगर (pmc->sभ_शेषe == MCAST_EXCLUDE &&
	    pmc->sfcount[MCAST_EXCLUDE] == 0 &&
	    pmc->sfcount[MCAST_INCLUDE]) अणु
#अगर_घोषित CONFIG_IP_MULTICAST
		काष्ठा ip_sf_list *psf;
		काष्ठा net *net = dev_net(in_dev->dev);
#पूर्ण_अगर

		/* filter mode change */
		pmc->sभ_शेषe = MCAST_INCLUDE;
#अगर_घोषित CONFIG_IP_MULTICAST
		pmc->crcount = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;
		in_dev->mr_अगरc_count = pmc->crcount;
		क्रम (psf = pmc->sources; psf; psf = psf->sf_next)
			psf->sf_crcount = 0;
		igmp_अगरc_event(pmc->पूर्णांकerface);
	पूर्ण अन्यथा अगर (sf_setstate(pmc) || changerec) अणु
		igmp_अगरc_event(pmc->पूर्णांकerface);
#पूर्ण_अगर
	पूर्ण
out_unlock:
	spin_unlock_bh(&pmc->lock);
	वापस err;
पूर्ण

/*
 * Add multicast single-source filter to the पूर्णांकerface list
 */
अटल पूर्णांक ip_mc_add1_src(काष्ठा ip_mc_list *pmc, पूर्णांक sभ_शेषe,
	__be32 *psfsrc)
अणु
	काष्ठा ip_sf_list *psf, *psf_prev;

	psf_prev = शून्य;
	क्रम (psf = pmc->sources; psf; psf = psf->sf_next) अणु
		अगर (psf->sf_inaddr == *psfsrc)
			अवरोध;
		psf_prev = psf;
	पूर्ण
	अगर (!psf) अणु
		psf = kzalloc(माप(*psf), GFP_ATOMIC);
		अगर (!psf)
			वापस -ENOBUFS;
		psf->sf_inaddr = *psfsrc;
		अगर (psf_prev) अणु
			psf_prev->sf_next = psf;
		पूर्ण अन्यथा
			pmc->sources = psf;
	पूर्ण
	psf->sf_count[sभ_शेषe]++;
	अगर (psf->sf_count[sभ_शेषe] == 1) अणु
		ip_rt_multicast_event(pmc->पूर्णांकerface);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IP_MULTICAST
अटल व्योम sf_markstate(काष्ठा ip_mc_list *pmc)
अणु
	काष्ठा ip_sf_list *psf;
	पूर्णांक mca_xcount = pmc->sfcount[MCAST_EXCLUDE];

	क्रम (psf = pmc->sources; psf; psf = psf->sf_next)
		अगर (pmc->sfcount[MCAST_EXCLUDE]) अणु
			psf->sf_oldin = mca_xcount ==
				psf->sf_count[MCAST_EXCLUDE] &&
				!psf->sf_count[MCAST_INCLUDE];
		पूर्ण अन्यथा
			psf->sf_oldin = psf->sf_count[MCAST_INCLUDE] != 0;
पूर्ण

अटल पूर्णांक sf_setstate(काष्ठा ip_mc_list *pmc)
अणु
	काष्ठा ip_sf_list *psf, *dpsf;
	पूर्णांक mca_xcount = pmc->sfcount[MCAST_EXCLUDE];
	पूर्णांक qrv = pmc->पूर्णांकerface->mr_qrv;
	पूर्णांक new_in, rv;

	rv = 0;
	क्रम (psf = pmc->sources; psf; psf = psf->sf_next) अणु
		अगर (pmc->sfcount[MCAST_EXCLUDE]) अणु
			new_in = mca_xcount == psf->sf_count[MCAST_EXCLUDE] &&
				!psf->sf_count[MCAST_INCLUDE];
		पूर्ण अन्यथा
			new_in = psf->sf_count[MCAST_INCLUDE] != 0;
		अगर (new_in) अणु
			अगर (!psf->sf_oldin) अणु
				काष्ठा ip_sf_list *prev = शून्य;

				क्रम (dpsf = pmc->tomb; dpsf; dpsf = dpsf->sf_next) अणु
					अगर (dpsf->sf_inaddr == psf->sf_inaddr)
						अवरोध;
					prev = dpsf;
				पूर्ण
				अगर (dpsf) अणु
					अगर (prev)
						prev->sf_next = dpsf->sf_next;
					अन्यथा
						pmc->tomb = dpsf->sf_next;
					kमुक्त(dpsf);
				पूर्ण
				psf->sf_crcount = qrv;
				rv++;
			पूर्ण
		पूर्ण अन्यथा अगर (psf->sf_oldin) अणु

			psf->sf_crcount = 0;
			/*
			 * add or update "delete" records अगर an active filter
			 * is now inactive
			 */
			क्रम (dpsf = pmc->tomb; dpsf; dpsf = dpsf->sf_next)
				अगर (dpsf->sf_inaddr == psf->sf_inaddr)
					अवरोध;
			अगर (!dpsf) अणु
				dpsf = kदो_स्मृति(माप(*dpsf), GFP_ATOMIC);
				अगर (!dpsf)
					जारी;
				*dpsf = *psf;
				/* pmc->lock held by callers */
				dpsf->sf_next = pmc->tomb;
				pmc->tomb = dpsf;
			पूर्ण
			dpsf->sf_crcount = qrv;
			rv++;
		पूर्ण
	पूर्ण
	वापस rv;
पूर्ण
#पूर्ण_अगर

/*
 * Add multicast source filter list to the पूर्णांकerface list
 */
अटल पूर्णांक ip_mc_add_src(काष्ठा in_device *in_dev, __be32 *pmca, पूर्णांक sभ_शेषe,
			 पूर्णांक sfcount, __be32 *psfsrc, पूर्णांक delta)
अणु
	काष्ठा ip_mc_list *pmc;
	पूर्णांक	isexclude;
	पूर्णांक	i, err;

	अगर (!in_dev)
		वापस -ENODEV;
	rcu_पढ़ो_lock();
	क्रम_each_pmc_rcu(in_dev, pmc) अणु
		अगर (*pmca == pmc->multiaddr)
			अवरोध;
	पूर्ण
	अगर (!pmc) अणु
		/* MCA not found?? bug */
		rcu_पढ़ो_unlock();
		वापस -ESRCH;
	पूर्ण
	spin_lock_bh(&pmc->lock);
	rcu_पढ़ो_unlock();

#अगर_घोषित CONFIG_IP_MULTICAST
	sf_markstate(pmc);
#पूर्ण_अगर
	isexclude = pmc->sभ_शेषe == MCAST_EXCLUDE;
	अगर (!delta)
		pmc->sfcount[sभ_शेषe]++;
	err = 0;
	क्रम (i = 0; i < sfcount; i++) अणु
		err = ip_mc_add1_src(pmc, sभ_शेषe, &psfsrc[i]);
		अगर (err)
			अवरोध;
	पूर्ण
	अगर (err) अणु
		पूर्णांक j;

		अगर (!delta)
			pmc->sfcount[sभ_शेषe]--;
		क्रम (j = 0; j < i; j++)
			(व्योम) ip_mc_del1_src(pmc, sभ_शेषe, &psfsrc[j]);
	पूर्ण अन्यथा अगर (isexclude != (pmc->sfcount[MCAST_EXCLUDE] != 0)) अणु
#अगर_घोषित CONFIG_IP_MULTICAST
		काष्ठा ip_sf_list *psf;
		काष्ठा net *net = dev_net(pmc->पूर्णांकerface->dev);
		in_dev = pmc->पूर्णांकerface;
#पूर्ण_अगर

		/* filter mode change */
		अगर (pmc->sfcount[MCAST_EXCLUDE])
			pmc->sभ_शेषe = MCAST_EXCLUDE;
		अन्यथा अगर (pmc->sfcount[MCAST_INCLUDE])
			pmc->sभ_शेषe = MCAST_INCLUDE;
#अगर_घोषित CONFIG_IP_MULTICAST
		/* अन्यथा no filters; keep old mode क्रम reports */

		pmc->crcount = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;
		in_dev->mr_अगरc_count = pmc->crcount;
		क्रम (psf = pmc->sources; psf; psf = psf->sf_next)
			psf->sf_crcount = 0;
		igmp_अगरc_event(in_dev);
	पूर्ण अन्यथा अगर (sf_setstate(pmc)) अणु
		igmp_अगरc_event(in_dev);
#पूर्ण_अगर
	पूर्ण
	spin_unlock_bh(&pmc->lock);
	वापस err;
पूर्ण

अटल व्योम ip_mc_clear_src(काष्ठा ip_mc_list *pmc)
अणु
	काष्ठा ip_sf_list *tomb, *sources;

	spin_lock_bh(&pmc->lock);
	tomb = pmc->tomb;
	pmc->tomb = शून्य;
	sources = pmc->sources;
	pmc->sources = शून्य;
	pmc->sभ_शेषe = MCAST_EXCLUDE;
	pmc->sfcount[MCAST_INCLUDE] = 0;
	pmc->sfcount[MCAST_EXCLUDE] = 1;
	spin_unlock_bh(&pmc->lock);

	ip_sf_list_clear_all(tomb);
	ip_sf_list_clear_all(sources);
पूर्ण

/* Join a multicast group
 */
अटल पूर्णांक __ip_mc_join_group(काष्ठा sock *sk, काष्ठा ip_mreqn *imr,
			      अचिन्हित पूर्णांक mode)
अणु
	__be32 addr = imr->imr_multiaddr.s_addr;
	काष्ठा ip_mc_socklist *iml, *i;
	काष्ठा in_device *in_dev;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक अगरindex;
	पूर्णांक count = 0;
	पूर्णांक err;

	ASSERT_RTNL();

	अगर (!ipv4_is_multicast(addr))
		वापस -EINVAL;

	in_dev = ip_mc_find_dev(net, imr);

	अगर (!in_dev) अणु
		err = -ENODEV;
		जाओ करोne;
	पूर्ण

	err = -EADDRINUSE;
	अगरindex = imr->imr_अगरindex;
	क्रम_each_pmc_rtnl(inet, i) अणु
		अगर (i->multi.imr_multiaddr.s_addr == addr &&
		    i->multi.imr_अगरindex == अगरindex)
			जाओ करोne;
		count++;
	पूर्ण
	err = -ENOBUFS;
	अगर (count >= net->ipv4.sysctl_igmp_max_memberships)
		जाओ करोne;
	iml = sock_kदो_स्मृति(sk, माप(*iml), GFP_KERNEL);
	अगर (!iml)
		जाओ करोne;

	स_नकल(&iml->multi, imr, माप(*imr));
	iml->next_rcu = inet->mc_list;
	iml->sflist = शून्य;
	iml->sभ_शेषe = mode;
	rcu_assign_poपूर्णांकer(inet->mc_list, iml);
	____ip_mc_inc_group(in_dev, addr, mode, GFP_KERNEL);
	err = 0;
करोne:
	वापस err;
पूर्ण

/* Join ASM (Any-Source Multicast) group
 */
पूर्णांक ip_mc_join_group(काष्ठा sock *sk, काष्ठा ip_mreqn *imr)
अणु
	वापस __ip_mc_join_group(sk, imr, MCAST_EXCLUDE);
पूर्ण
EXPORT_SYMBOL(ip_mc_join_group);

/* Join SSM (Source-Specअगरic Multicast) group
 */
पूर्णांक ip_mc_join_group_ssm(काष्ठा sock *sk, काष्ठा ip_mreqn *imr,
			 अचिन्हित पूर्णांक mode)
अणु
	वापस __ip_mc_join_group(sk, imr, mode);
पूर्ण

अटल पूर्णांक ip_mc_leave_src(काष्ठा sock *sk, काष्ठा ip_mc_socklist *iml,
			   काष्ठा in_device *in_dev)
अणु
	काष्ठा ip_sf_socklist *psf = rtnl_dereference(iml->sflist);
	पूर्णांक err;

	अगर (!psf) अणु
		/* any-source empty exclude हाल */
		वापस ip_mc_del_src(in_dev, &iml->multi.imr_multiaddr.s_addr,
			iml->sभ_शेषe, 0, शून्य, 0);
	पूर्ण
	err = ip_mc_del_src(in_dev, &iml->multi.imr_multiaddr.s_addr,
			iml->sभ_शेषe, psf->sl_count, psf->sl_addr, 0);
	RCU_INIT_POINTER(iml->sflist, शून्य);
	/* decrease mem now to aव्योम the memleak warning */
	atomic_sub(IP_SFLSIZE(psf->sl_max), &sk->sk_omem_alloc);
	kमुक्त_rcu(psf, rcu);
	वापस err;
पूर्ण

पूर्णांक ip_mc_leave_group(काष्ठा sock *sk, काष्ठा ip_mreqn *imr)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ip_mc_socklist *iml;
	काष्ठा ip_mc_socklist __rcu **imlp;
	काष्ठा in_device *in_dev;
	काष्ठा net *net = sock_net(sk);
	__be32 group = imr->imr_multiaddr.s_addr;
	u32 अगरindex;
	पूर्णांक ret = -EADDRNOTAVAIL;

	ASSERT_RTNL();

	in_dev = ip_mc_find_dev(net, imr);
	अगर (!imr->imr_अगरindex && !imr->imr_address.s_addr && !in_dev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	अगरindex = imr->imr_अगरindex;
	क्रम (imlp = &inet->mc_list;
	     (iml = rtnl_dereference(*imlp)) != शून्य;
	     imlp = &iml->next_rcu) अणु
		अगर (iml->multi.imr_multiaddr.s_addr != group)
			जारी;
		अगर (अगरindex) अणु
			अगर (iml->multi.imr_अगरindex != अगरindex)
				जारी;
		पूर्ण अन्यथा अगर (imr->imr_address.s_addr && imr->imr_address.s_addr !=
				iml->multi.imr_address.s_addr)
			जारी;

		(व्योम) ip_mc_leave_src(sk, iml, in_dev);

		*imlp = iml->next_rcu;

		अगर (in_dev)
			ip_mc_dec_group(in_dev, group);

		/* decrease mem now to aव्योम the memleak warning */
		atomic_sub(माप(*iml), &sk->sk_omem_alloc);
		kमुक्त_rcu(iml, rcu);
		वापस 0;
	पूर्ण
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ip_mc_leave_group);

पूर्णांक ip_mc_source(पूर्णांक add, पूर्णांक omode, काष्ठा sock *sk, काष्ठा
	ip_mreq_source *mreqs, पूर्णांक अगरindex)
अणु
	पूर्णांक err;
	काष्ठा ip_mreqn imr;
	__be32 addr = mreqs->imr_multiaddr;
	काष्ठा ip_mc_socklist *pmc;
	काष्ठा in_device *in_dev = शून्य;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ip_sf_socklist *psl;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक leavegroup = 0;
	पूर्णांक i, j, rv;

	अगर (!ipv4_is_multicast(addr))
		वापस -EINVAL;

	ASSERT_RTNL();

	imr.imr_multiaddr.s_addr = mreqs->imr_multiaddr;
	imr.imr_address.s_addr = mreqs->imr_पूर्णांकerface;
	imr.imr_अगरindex = अगरindex;
	in_dev = ip_mc_find_dev(net, &imr);

	अगर (!in_dev) अणु
		err = -ENODEV;
		जाओ करोne;
	पूर्ण
	err = -EADDRNOTAVAIL;

	क्रम_each_pmc_rtnl(inet, pmc) अणु
		अगर ((pmc->multi.imr_multiaddr.s_addr ==
		     imr.imr_multiaddr.s_addr) &&
		    (pmc->multi.imr_अगरindex == imr.imr_अगरindex))
			अवरोध;
	पूर्ण
	अगर (!pmc) अणु		/* must have a prior join */
		err = -EINVAL;
		जाओ करोne;
	पूर्ण
	/* अगर a source filter was set, must be the same mode as beक्रमe */
	अगर (pmc->sflist) अणु
		अगर (pmc->sभ_शेषe != omode) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अगर (pmc->sभ_शेषe != omode) अणु
		/* allow mode चयनes क्रम empty-set filters */
		ip_mc_add_src(in_dev, &mreqs->imr_multiaddr, omode, 0, शून्य, 0);
		ip_mc_del_src(in_dev, &mreqs->imr_multiaddr, pmc->sभ_शेषe, 0,
			शून्य, 0);
		pmc->sभ_शेषe = omode;
	पूर्ण

	psl = rtnl_dereference(pmc->sflist);
	अगर (!add) अणु
		अगर (!psl)
			जाओ करोne;	/* err = -EADDRNOTAVAIL */
		rv = !0;
		क्रम (i = 0; i < psl->sl_count; i++) अणु
			rv = स_भेद(&psl->sl_addr[i], &mreqs->imr_sourceaddr,
				माप(__be32));
			अगर (rv == 0)
				अवरोध;
		पूर्ण
		अगर (rv)		/* source not found */
			जाओ करोne;	/* err = -EADDRNOTAVAIL */

		/* special हाल - (INCLUDE, empty) == LEAVE_GROUP */
		अगर (psl->sl_count == 1 && omode == MCAST_INCLUDE) अणु
			leavegroup = 1;
			जाओ करोne;
		पूर्ण

		/* update the पूर्णांकerface filter */
		ip_mc_del_src(in_dev, &mreqs->imr_multiaddr, omode, 1,
			&mreqs->imr_sourceaddr, 1);

		क्रम (j = i+1; j < psl->sl_count; j++)
			psl->sl_addr[j-1] = psl->sl_addr[j];
		psl->sl_count--;
		err = 0;
		जाओ करोne;
	पूर्ण
	/* अन्यथा, add a new source to the filter */

	अगर (psl && psl->sl_count >= net->ipv4.sysctl_igmp_max_msf) अणु
		err = -ENOBUFS;
		जाओ करोne;
	पूर्ण
	अगर (!psl || psl->sl_count == psl->sl_max) अणु
		काष्ठा ip_sf_socklist *newpsl;
		पूर्णांक count = IP_SFBLOCK;

		अगर (psl)
			count += psl->sl_max;
		newpsl = sock_kदो_स्मृति(sk, IP_SFLSIZE(count), GFP_KERNEL);
		अगर (!newpsl) अणु
			err = -ENOBUFS;
			जाओ करोne;
		पूर्ण
		newpsl->sl_max = count;
		newpsl->sl_count = count - IP_SFBLOCK;
		अगर (psl) अणु
			क्रम (i = 0; i < psl->sl_count; i++)
				newpsl->sl_addr[i] = psl->sl_addr[i];
			/* decrease mem now to aव्योम the memleak warning */
			atomic_sub(IP_SFLSIZE(psl->sl_max), &sk->sk_omem_alloc);
			kमुक्त_rcu(psl, rcu);
		पूर्ण
		rcu_assign_poपूर्णांकer(pmc->sflist, newpsl);
		psl = newpsl;
	पूर्ण
	rv = 1;	/* > 0 क्रम insert logic below अगर sl_count is 0 */
	क्रम (i = 0; i < psl->sl_count; i++) अणु
		rv = स_भेद(&psl->sl_addr[i], &mreqs->imr_sourceaddr,
			माप(__be32));
		अगर (rv == 0)
			अवरोध;
	पूर्ण
	अगर (rv == 0)		/* address alपढ़ोy there is an error */
		जाओ करोne;
	क्रम (j = psl->sl_count-1; j >= i; j--)
		psl->sl_addr[j+1] = psl->sl_addr[j];
	psl->sl_addr[i] = mreqs->imr_sourceaddr;
	psl->sl_count++;
	err = 0;
	/* update the पूर्णांकerface list */
	ip_mc_add_src(in_dev, &mreqs->imr_multiaddr, omode, 1,
		&mreqs->imr_sourceaddr, 1);
करोne:
	अगर (leavegroup)
		err = ip_mc_leave_group(sk, &imr);
	वापस err;
पूर्ण

पूर्णांक ip_mc_msfilter(काष्ठा sock *sk, काष्ठा ip_msfilter *msf, पूर्णांक अगरindex)
अणु
	पूर्णांक err = 0;
	काष्ठा ip_mreqn	imr;
	__be32 addr = msf->imsf_multiaddr;
	काष्ठा ip_mc_socklist *pmc;
	काष्ठा in_device *in_dev;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ip_sf_socklist *newpsl, *psl;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक leavegroup = 0;

	अगर (!ipv4_is_multicast(addr))
		वापस -EINVAL;
	अगर (msf->imsf_भ_शेषe != MCAST_INCLUDE &&
	    msf->imsf_भ_शेषe != MCAST_EXCLUDE)
		वापस -EINVAL;

	ASSERT_RTNL();

	imr.imr_multiaddr.s_addr = msf->imsf_multiaddr;
	imr.imr_address.s_addr = msf->imsf_पूर्णांकerface;
	imr.imr_अगरindex = अगरindex;
	in_dev = ip_mc_find_dev(net, &imr);

	अगर (!in_dev) अणु
		err = -ENODEV;
		जाओ करोne;
	पूर्ण

	/* special हाल - (INCLUDE, empty) == LEAVE_GROUP */
	अगर (msf->imsf_भ_शेषe == MCAST_INCLUDE && msf->imsf_numsrc == 0) अणु
		leavegroup = 1;
		जाओ करोne;
	पूर्ण

	क्रम_each_pmc_rtnl(inet, pmc) अणु
		अगर (pmc->multi.imr_multiaddr.s_addr == msf->imsf_multiaddr &&
		    pmc->multi.imr_अगरindex == imr.imr_अगरindex)
			अवरोध;
	पूर्ण
	अगर (!pmc) अणु		/* must have a prior join */
		err = -EINVAL;
		जाओ करोne;
	पूर्ण
	अगर (msf->imsf_numsrc) अणु
		newpsl = sock_kदो_स्मृति(sk, IP_SFLSIZE(msf->imsf_numsrc),
							   GFP_KERNEL);
		अगर (!newpsl) अणु
			err = -ENOBUFS;
			जाओ करोne;
		पूर्ण
		newpsl->sl_max = newpsl->sl_count = msf->imsf_numsrc;
		स_नकल(newpsl->sl_addr, msf->imsf_slist,
			msf->imsf_numsrc * माप(msf->imsf_slist[0]));
		err = ip_mc_add_src(in_dev, &msf->imsf_multiaddr,
			msf->imsf_भ_शेषe, newpsl->sl_count, newpsl->sl_addr, 0);
		अगर (err) अणु
			sock_kमुक्त_s(sk, newpsl, IP_SFLSIZE(newpsl->sl_max));
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		newpsl = शून्य;
		(व्योम) ip_mc_add_src(in_dev, &msf->imsf_multiaddr,
				     msf->imsf_भ_शेषe, 0, शून्य, 0);
	पूर्ण
	psl = rtnl_dereference(pmc->sflist);
	अगर (psl) अणु
		(व्योम) ip_mc_del_src(in_dev, &msf->imsf_multiaddr, pmc->sभ_शेषe,
			psl->sl_count, psl->sl_addr, 0);
		/* decrease mem now to aव्योम the memleak warning */
		atomic_sub(IP_SFLSIZE(psl->sl_max), &sk->sk_omem_alloc);
		kमुक्त_rcu(psl, rcu);
	पूर्ण अन्यथा
		(व्योम) ip_mc_del_src(in_dev, &msf->imsf_multiaddr, pmc->sभ_शेषe,
			0, शून्य, 0);
	rcu_assign_poपूर्णांकer(pmc->sflist, newpsl);
	pmc->sभ_शेषe = msf->imsf_भ_शेषe;
	err = 0;
करोne:
	अगर (leavegroup)
		err = ip_mc_leave_group(sk, &imr);
	वापस err;
पूर्ण

पूर्णांक ip_mc_msfget(काष्ठा sock *sk, काष्ठा ip_msfilter *msf,
	काष्ठा ip_msfilter __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक err, len, count, copycount;
	काष्ठा ip_mreqn	imr;
	__be32 addr = msf->imsf_multiaddr;
	काष्ठा ip_mc_socklist *pmc;
	काष्ठा in_device *in_dev;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ip_sf_socklist *psl;
	काष्ठा net *net = sock_net(sk);

	ASSERT_RTNL();

	अगर (!ipv4_is_multicast(addr))
		वापस -EINVAL;

	imr.imr_multiaddr.s_addr = msf->imsf_multiaddr;
	imr.imr_address.s_addr = msf->imsf_पूर्णांकerface;
	imr.imr_अगरindex = 0;
	in_dev = ip_mc_find_dev(net, &imr);

	अगर (!in_dev) अणु
		err = -ENODEV;
		जाओ करोne;
	पूर्ण
	err = -EADDRNOTAVAIL;

	क्रम_each_pmc_rtnl(inet, pmc) अणु
		अगर (pmc->multi.imr_multiaddr.s_addr == msf->imsf_multiaddr &&
		    pmc->multi.imr_अगरindex == imr.imr_अगरindex)
			अवरोध;
	पूर्ण
	अगर (!pmc)		/* must have a prior join */
		जाओ करोne;
	msf->imsf_भ_शेषe = pmc->sभ_शेषe;
	psl = rtnl_dereference(pmc->sflist);
	अगर (!psl) अणु
		len = 0;
		count = 0;
	पूर्ण अन्यथा अणु
		count = psl->sl_count;
	पूर्ण
	copycount = count < msf->imsf_numsrc ? count : msf->imsf_numsrc;
	len = copycount * माप(psl->sl_addr[0]);
	msf->imsf_numsrc = count;
	अगर (put_user(IP_MSFILTER_SIZE(copycount), optlen) ||
	    copy_to_user(optval, msf, IP_MSFILTER_SIZE(0))) अणु
		वापस -EFAULT;
	पूर्ण
	अगर (len &&
	    copy_to_user(&optval->imsf_slist[0], psl->sl_addr, len))
		वापस -EFAULT;
	वापस 0;
करोne:
	वापस err;
पूर्ण

पूर्णांक ip_mc_gsfget(काष्ठा sock *sk, काष्ठा group_filter *gsf,
	काष्ठा sockaddr_storage __user *p)
अणु
	पूर्णांक i, count, copycount;
	काष्ठा sockaddr_in *psin;
	__be32 addr;
	काष्ठा ip_mc_socklist *pmc;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ip_sf_socklist *psl;

	ASSERT_RTNL();

	psin = (काष्ठा sockaddr_in *)&gsf->gf_group;
	अगर (psin->sin_family != AF_INET)
		वापस -EINVAL;
	addr = psin->sin_addr.s_addr;
	अगर (!ipv4_is_multicast(addr))
		वापस -EINVAL;

	क्रम_each_pmc_rtnl(inet, pmc) अणु
		अगर (pmc->multi.imr_multiaddr.s_addr == addr &&
		    pmc->multi.imr_अगरindex == gsf->gf_पूर्णांकerface)
			अवरोध;
	पूर्ण
	अगर (!pmc)		/* must have a prior join */
		वापस -EADDRNOTAVAIL;
	gsf->gf_भ_शेषe = pmc->sभ_शेषe;
	psl = rtnl_dereference(pmc->sflist);
	count = psl ? psl->sl_count : 0;
	copycount = count < gsf->gf_numsrc ? count : gsf->gf_numsrc;
	gsf->gf_numsrc = count;
	क्रम (i = 0; i < copycount; i++, p++) अणु
		काष्ठा sockaddr_storage ss;

		psin = (काष्ठा sockaddr_in *)&ss;
		स_रखो(&ss, 0, माप(ss));
		psin->sin_family = AF_INET;
		psin->sin_addr.s_addr = psl->sl_addr[i];
		अगर (copy_to_user(p, &ss, माप(ss)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * check अगर a multicast source filter allows delivery क्रम a given <src,dst,पूर्णांकf>
 */
पूर्णांक ip_mc_sf_allow(काष्ठा sock *sk, __be32 loc_addr, __be32 rmt_addr,
		   पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ip_mc_socklist *pmc;
	काष्ठा ip_sf_socklist *psl;
	पूर्णांक i;
	पूर्णांक ret;

	ret = 1;
	अगर (!ipv4_is_multicast(loc_addr))
		जाओ out;

	rcu_पढ़ो_lock();
	क्रम_each_pmc_rcu(inet, pmc) अणु
		अगर (pmc->multi.imr_multiaddr.s_addr == loc_addr &&
		    (pmc->multi.imr_अगरindex == dअगर ||
		     (sdअगर && pmc->multi.imr_अगरindex == sdअगर)))
			अवरोध;
	पूर्ण
	ret = inet->mc_all;
	अगर (!pmc)
		जाओ unlock;
	psl = rcu_dereference(pmc->sflist);
	ret = (pmc->sभ_शेषe == MCAST_EXCLUDE);
	अगर (!psl)
		जाओ unlock;

	क्रम (i = 0; i < psl->sl_count; i++) अणु
		अगर (psl->sl_addr[i] == rmt_addr)
			अवरोध;
	पूर्ण
	ret = 0;
	अगर (pmc->sभ_शेषe == MCAST_INCLUDE && i >= psl->sl_count)
		जाओ unlock;
	अगर (pmc->sभ_शेषe == MCAST_EXCLUDE && i < psl->sl_count)
		जाओ unlock;
	ret = 1;
unlock:
	rcu_पढ़ो_unlock();
out:
	वापस ret;
पूर्ण

/*
 *	A socket is closing.
 */

व्योम ip_mc_drop_socket(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ip_mc_socklist *iml;
	काष्ठा net *net = sock_net(sk);

	अगर (!inet->mc_list)
		वापस;

	rtnl_lock();
	जबतक ((iml = rtnl_dereference(inet->mc_list)) != शून्य) अणु
		काष्ठा in_device *in_dev;

		inet->mc_list = iml->next_rcu;
		in_dev = inetdev_by_index(net, iml->multi.imr_अगरindex);
		(व्योम) ip_mc_leave_src(sk, iml, in_dev);
		अगर (in_dev)
			ip_mc_dec_group(in_dev, iml->multi.imr_multiaddr.s_addr);
		/* decrease mem now to aव्योम the memleak warning */
		atomic_sub(माप(*iml), &sk->sk_omem_alloc);
		kमुक्त_rcu(iml, rcu);
	पूर्ण
	rtnl_unlock();
पूर्ण

/* called with rcu_पढ़ो_lock() */
पूर्णांक ip_check_mc_rcu(काष्ठा in_device *in_dev, __be32 mc_addr, __be32 src_addr, u8 proto)
अणु
	काष्ठा ip_mc_list *im;
	काष्ठा ip_mc_list __rcu **mc_hash;
	काष्ठा ip_sf_list *psf;
	पूर्णांक rv = 0;

	mc_hash = rcu_dereference(in_dev->mc_hash);
	अगर (mc_hash) अणु
		u32 hash = hash_32((__क्रमce u32)mc_addr, MC_HASH_SZ_LOG);

		क्रम (im = rcu_dereference(mc_hash[hash]);
		     im != शून्य;
		     im = rcu_dereference(im->next_hash)) अणु
			अगर (im->multiaddr == mc_addr)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_pmc_rcu(in_dev, im) अणु
			अगर (im->multiaddr == mc_addr)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (im && proto == IPPROTO_IGMP) अणु
		rv = 1;
	पूर्ण अन्यथा अगर (im) अणु
		अगर (src_addr) अणु
			क्रम (psf = im->sources; psf; psf = psf->sf_next) अणु
				अगर (psf->sf_inaddr == src_addr)
					अवरोध;
			पूर्ण
			अगर (psf)
				rv = psf->sf_count[MCAST_INCLUDE] ||
					psf->sf_count[MCAST_EXCLUDE] !=
					im->sfcount[MCAST_EXCLUDE];
			अन्यथा
				rv = im->sfcount[MCAST_EXCLUDE] != 0;
		पूर्ण अन्यथा
			rv = 1; /* unspecअगरied source; tentatively allow */
	पूर्ण
	वापस rv;
पूर्ण

#अगर defined(CONFIG_PROC_FS)
काष्ठा igmp_mc_iter_state अणु
	काष्ठा seq_net_निजी p;
	काष्ठा net_device *dev;
	काष्ठा in_device *in_dev;
पूर्ण;

#घोषणा	igmp_mc_seq_निजी(seq)	((काष्ठा igmp_mc_iter_state *)(seq)->निजी)

अटल अंतरभूत काष्ठा ip_mc_list *igmp_mc_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा ip_mc_list *im = शून्य;
	काष्ठा igmp_mc_iter_state *state = igmp_mc_seq_निजी(seq);

	state->in_dev = शून्य;
	क्रम_each_netdev_rcu(net, state->dev) अणु
		काष्ठा in_device *in_dev;

		in_dev = __in_dev_get_rcu(state->dev);
		अगर (!in_dev)
			जारी;
		im = rcu_dereference(in_dev->mc_list);
		अगर (im) अणु
			state->in_dev = in_dev;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस im;
पूर्ण

अटल काष्ठा ip_mc_list *igmp_mc_get_next(काष्ठा seq_file *seq, काष्ठा ip_mc_list *im)
अणु
	काष्ठा igmp_mc_iter_state *state = igmp_mc_seq_निजी(seq);

	im = rcu_dereference(im->next_rcu);
	जबतक (!im) अणु
		state->dev = next_net_device_rcu(state->dev);
		अगर (!state->dev) अणु
			state->in_dev = शून्य;
			अवरोध;
		पूर्ण
		state->in_dev = __in_dev_get_rcu(state->dev);
		अगर (!state->in_dev)
			जारी;
		im = rcu_dereference(state->in_dev->mc_list);
	पूर्ण
	वापस im;
पूर्ण

अटल काष्ठा ip_mc_list *igmp_mc_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा ip_mc_list *im = igmp_mc_get_first(seq);
	अगर (im)
		जबतक (pos && (im = igmp_mc_get_next(seq, im)) != शून्य)
			--pos;
	वापस pos ? शून्य : im;
पूर्ण

अटल व्योम *igmp_mc_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rcu)
अणु
	rcu_पढ़ो_lock();
	वापस *pos ? igmp_mc_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *igmp_mc_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा ip_mc_list *im;
	अगर (v == SEQ_START_TOKEN)
		im = igmp_mc_get_first(seq);
	अन्यथा
		im = igmp_mc_get_next(seq, v);
	++*pos;
	वापस im;
पूर्ण

अटल व्योम igmp_mc_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rcu)
अणु
	काष्ठा igmp_mc_iter_state *state = igmp_mc_seq_निजी(seq);

	state->in_dev = शून्य;
	state->dev = शून्य;
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक igmp_mc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq,
			 "Idx\tDevice    : Count Querier\tGroup    Users Timer\tReporter\n");
	अन्यथा अणु
		काष्ठा ip_mc_list *im = (काष्ठा ip_mc_list *)v;
		काष्ठा igmp_mc_iter_state *state = igmp_mc_seq_निजी(seq);
		अक्षर   *querier;
		दीर्घ delta;

#अगर_घोषित CONFIG_IP_MULTICAST
		querier = IGMP_V1_SEEN(state->in_dev) ? "V1" :
			  IGMP_V2_SEEN(state->in_dev) ? "V2" :
			  "V3";
#अन्यथा
		querier = "NONE";
#पूर्ण_अगर

		अगर (rcu_access_poपूर्णांकer(state->in_dev->mc_list) == im) अणु
			seq_म_लिखो(seq, "%d\t%-10s: %5d %7s\n",
				   state->dev->अगरindex, state->dev->name, state->in_dev->mc_count, querier);
		पूर्ण

		delta = im->समयr.expires - jअगरfies;
		seq_म_लिखो(seq,
			   "\t\t\t\t%08X %5d %d:%08lX\t\t%d\n",
			   im->multiaddr, im->users,
			   im->पंचांग_running,
			   im->पंचांग_running ? jअगरfies_delta_to_घड़ी_प्रकार(delta) : 0,
			   im->reporter);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations igmp_mc_seq_ops = अणु
	.start	=	igmp_mc_seq_start,
	.next	=	igmp_mc_seq_next,
	.stop	=	igmp_mc_seq_stop,
	.show	=	igmp_mc_seq_show,
पूर्ण;

काष्ठा igmp_mcf_iter_state अणु
	काष्ठा seq_net_निजी p;
	काष्ठा net_device *dev;
	काष्ठा in_device *idev;
	काष्ठा ip_mc_list *im;
पूर्ण;

#घोषणा igmp_mcf_seq_निजी(seq)	((काष्ठा igmp_mcf_iter_state *)(seq)->निजी)

अटल अंतरभूत काष्ठा ip_sf_list *igmp_mcf_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा ip_sf_list *psf = शून्य;
	काष्ठा ip_mc_list *im = शून्य;
	काष्ठा igmp_mcf_iter_state *state = igmp_mcf_seq_निजी(seq);

	state->idev = शून्य;
	state->im = शून्य;
	क्रम_each_netdev_rcu(net, state->dev) अणु
		काष्ठा in_device *idev;
		idev = __in_dev_get_rcu(state->dev);
		अगर (unlikely(!idev))
			जारी;
		im = rcu_dereference(idev->mc_list);
		अगर (likely(im)) अणु
			spin_lock_bh(&im->lock);
			psf = im->sources;
			अगर (likely(psf)) अणु
				state->im = im;
				state->idev = idev;
				अवरोध;
			पूर्ण
			spin_unlock_bh(&im->lock);
		पूर्ण
	पूर्ण
	वापस psf;
पूर्ण

अटल काष्ठा ip_sf_list *igmp_mcf_get_next(काष्ठा seq_file *seq, काष्ठा ip_sf_list *psf)
अणु
	काष्ठा igmp_mcf_iter_state *state = igmp_mcf_seq_निजी(seq);

	psf = psf->sf_next;
	जबतक (!psf) अणु
		spin_unlock_bh(&state->im->lock);
		state->im = state->im->next;
		जबतक (!state->im) अणु
			state->dev = next_net_device_rcu(state->dev);
			अगर (!state->dev) अणु
				state->idev = शून्य;
				जाओ out;
			पूर्ण
			state->idev = __in_dev_get_rcu(state->dev);
			अगर (!state->idev)
				जारी;
			state->im = rcu_dereference(state->idev->mc_list);
		पूर्ण
		अगर (!state->im)
			अवरोध;
		spin_lock_bh(&state->im->lock);
		psf = state->im->sources;
	पूर्ण
out:
	वापस psf;
पूर्ण

अटल काष्ठा ip_sf_list *igmp_mcf_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा ip_sf_list *psf = igmp_mcf_get_first(seq);
	अगर (psf)
		जबतक (pos && (psf = igmp_mcf_get_next(seq, psf)) != शून्य)
			--pos;
	वापस pos ? शून्य : psf;
पूर्ण

अटल व्योम *igmp_mcf_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rcu)
अणु
	rcu_पढ़ो_lock();
	वापस *pos ? igmp_mcf_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *igmp_mcf_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा ip_sf_list *psf;
	अगर (v == SEQ_START_TOKEN)
		psf = igmp_mcf_get_first(seq);
	अन्यथा
		psf = igmp_mcf_get_next(seq, v);
	++*pos;
	वापस psf;
पूर्ण

अटल व्योम igmp_mcf_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rcu)
अणु
	काष्ठा igmp_mcf_iter_state *state = igmp_mcf_seq_निजी(seq);
	अगर (likely(state->im)) अणु
		spin_unlock_bh(&state->im->lock);
		state->im = शून्य;
	पूर्ण
	state->idev = शून्य;
	state->dev = शून्य;
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक igmp_mcf_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ip_sf_list *psf = (काष्ठा ip_sf_list *)v;
	काष्ठा igmp_mcf_iter_state *state = igmp_mcf_seq_निजी(seq);

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Idx Device        MCA        SRC    INC    EXC\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(seq,
			   "%3d %6.6s 0x%08x "
			   "0x%08x %6lu %6lu\n",
			   state->dev->अगरindex, state->dev->name,
			   ntohl(state->im->multiaddr),
			   ntohl(psf->sf_inaddr),
			   psf->sf_count[MCAST_INCLUDE],
			   psf->sf_count[MCAST_EXCLUDE]);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations igmp_mcf_seq_ops = अणु
	.start	=	igmp_mcf_seq_start,
	.next	=	igmp_mcf_seq_next,
	.stop	=	igmp_mcf_seq_stop,
	.show	=	igmp_mcf_seq_show,
पूर्ण;

अटल पूर्णांक __net_init igmp_net_init(काष्ठा net *net)
अणु
	काष्ठा proc_dir_entry *pde;
	पूर्णांक err;

	pde = proc_create_net("igmp", 0444, net->proc_net, &igmp_mc_seq_ops,
			माप(काष्ठा igmp_mc_iter_state));
	अगर (!pde)
		जाओ out_igmp;
	pde = proc_create_net("mcfilter", 0444, net->proc_net,
			&igmp_mcf_seq_ops, माप(काष्ठा igmp_mcf_iter_state));
	अगर (!pde)
		जाओ out_mcfilter;
	err = inet_ctl_sock_create(&net->ipv4.mc_स्वतःjoin_sk, AF_INET,
				   SOCK_DGRAM, 0, net);
	अगर (err < 0) अणु
		pr_err("Failed to initialize the IGMP autojoin socket (err %d)\n",
		       err);
		जाओ out_sock;
	पूर्ण

	वापस 0;

out_sock:
	हटाओ_proc_entry("mcfilter", net->proc_net);
out_mcfilter:
	हटाओ_proc_entry("igmp", net->proc_net);
out_igmp:
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास igmp_net_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("mcfilter", net->proc_net);
	हटाओ_proc_entry("igmp", net->proc_net);
	inet_ctl_sock_destroy(net->ipv4.mc_स्वतःjoin_sk);
पूर्ण

अटल काष्ठा pernet_operations igmp_net_ops = अणु
	.init = igmp_net_init,
	.निकास = igmp_net_निकास,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक igmp_netdev_event(काष्ठा notअगरier_block *this,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा in_device *in_dev;

	चयन (event) अणु
	हाल NETDEV_RESEND_IGMP:
		in_dev = __in_dev_get_rtnl(dev);
		अगर (in_dev)
			ip_mc_rejoin_groups(in_dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block igmp_notअगरier = अणु
	.notअगरier_call = igmp_netdev_event,
पूर्ण;

पूर्णांक __init igmp_mc_init(व्योम)
अणु
#अगर defined(CONFIG_PROC_FS)
	पूर्णांक err;

	err = रेजिस्टर_pernet_subsys(&igmp_net_ops);
	अगर (err)
		वापस err;
	err = रेजिस्टर_netdevice_notअगरier(&igmp_notअगरier);
	अगर (err)
		जाओ reg_notअगर_fail;
	वापस 0;

reg_notअगर_fail:
	unरेजिस्टर_pernet_subsys(&igmp_net_ops);
	वापस err;
#अन्यथा
	वापस रेजिस्टर_netdevice_notअगरier(&igmp_notअगरier);
#पूर्ण_अगर
पूर्ण
