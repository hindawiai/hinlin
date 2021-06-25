<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Weighted Least-Connection Scheduling module
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Peter Kese <peter.kese@ijs.si>
 *
 * Changes:
 *     Wensong Zhang            :     changed the ip_vs_wlc_schedule to वापस dest
 *     Wensong Zhang            :     changed to use the inactconns in scheduling
 *     Wensong Zhang            :     changed some comestics things क्रम debugging
 *     Wensong Zhang            :     changed क्रम the d-linked destination list
 *     Wensong Zhang            :     added the ip_vs_wlc_update_svc
 *     Wensong Zhang            :     added any dest with weight=0 is quiesced
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <net/ip_vs.h>

/*
 *	Weighted Least Connection scheduling
 */
अटल काष्ठा ip_vs_dest *
ip_vs_wlc_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		   काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest, *least;
	पूर्णांक loh, करोh;

	IP_VS_DBG(6, "ip_vs_wlc_schedule(): Scheduling...\n");

	/*
	 * We calculate the load of each dest server as follows:
	 *		  (dest overhead) / dest->weight
	 *
	 * Remember -- no भग्नs in kernel mode!!!
	 * The comparison of h1*w2 > h2*w1 is equivalent to that of
	 *		  h1/w1 > h2/w2
	 * अगर every weight is larger than zero.
	 *
	 * The server with weight=0 is quiesced and will not receive any
	 * new connections.
	 */

	list_क्रम_each_entry_rcu(dest, &svc->destinations, n_list) अणु
		अगर (!(dest->flags & IP_VS_DEST_F_OVERLOAD) &&
		    atomic_पढ़ो(&dest->weight) > 0) अणु
			least = dest;
			loh = ip_vs_dest_conn_overhead(least);
			जाओ nextstage;
		पूर्ण
	पूर्ण
	ip_vs_scheduler_err(svc, "no destination available");
	वापस शून्य;

	/*
	 *    Find the destination with the least load.
	 */
  nextstage:
	list_क्रम_each_entry_जारी_rcu(dest, &svc->destinations, n_list) अणु
		अगर (dest->flags & IP_VS_DEST_F_OVERLOAD)
			जारी;
		करोh = ip_vs_dest_conn_overhead(dest);
		अगर ((__s64)loh * atomic_पढ़ो(&dest->weight) >
		    (__s64)करोh * atomic_पढ़ो(&least->weight)) अणु
			least = dest;
			loh = करोh;
		पूर्ण
	पूर्ण

	IP_VS_DBG_BUF(6, "WLC: server %s:%u "
		      "activeconns %d refcnt %d weight %d overhead %d\n",
		      IP_VS_DBG_ADDR(least->af, &least->addr),
		      ntohs(least->port),
		      atomic_पढ़ो(&least->activeconns),
		      refcount_पढ़ो(&least->refcnt),
		      atomic_पढ़ो(&least->weight), loh);

	वापस least;
पूर्ण


अटल काष्ठा ip_vs_scheduler ip_vs_wlc_scheduler =
अणु
	.name =			"wlc",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_wlc_scheduler.n_list),
	.schedule =		ip_vs_wlc_schedule,
पूर्ण;


अटल पूर्णांक __init ip_vs_wlc_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_wlc_scheduler);
पूर्ण

अटल व्योम __निकास ip_vs_wlc_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_wlc_scheduler);
	synchronize_rcu();
पूर्ण

module_init(ip_vs_wlc_init);
module_निकास(ip_vs_wlc_cleanup);
MODULE_LICENSE("GPL");
