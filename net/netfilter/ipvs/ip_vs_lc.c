<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Least-Connection Scheduling module
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *
 * Changes:
 *     Wensong Zhang            :     added the ip_vs_lc_update_svc
 *     Wensong Zhang            :     added any dest with weight=0 is quiesced
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <net/ip_vs.h>

/*
 *	Least Connection scheduling
 */
अटल काष्ठा ip_vs_dest *
ip_vs_lc_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		  काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest, *least = शून्य;
	अचिन्हित पूर्णांक loh = 0, करोh;

	IP_VS_DBG(6, "%s(): Scheduling...\n", __func__);

	/*
	 * Simply select the server with the least number of
	 *        (activeconns<<5) + inactconns
	 * Except whose weight is equal to zero.
	 * If the weight is equal to zero, it means that the server is
	 * quiesced, the existing connections to the server still get
	 * served, but no new connection is asचिन्हित to the server.
	 */

	list_क्रम_each_entry_rcu(dest, &svc->destinations, n_list) अणु
		अगर ((dest->flags & IP_VS_DEST_F_OVERLOAD) ||
		    atomic_पढ़ो(&dest->weight) == 0)
			जारी;
		करोh = ip_vs_dest_conn_overhead(dest);
		अगर (!least || करोh < loh) अणु
			least = dest;
			loh = करोh;
		पूर्ण
	पूर्ण

	अगर (!least)
		ip_vs_scheduler_err(svc, "no destination available");
	अन्यथा
		IP_VS_DBG_BUF(6, "LC: server %s:%u activeconns %d "
			      "inactconns %d\n",
			      IP_VS_DBG_ADDR(least->af, &least->addr),
			      ntohs(least->port),
			      atomic_पढ़ो(&least->activeconns),
			      atomic_पढ़ो(&least->inactconns));

	वापस least;
पूर्ण


अटल काष्ठा ip_vs_scheduler ip_vs_lc_scheduler = अणु
	.name =			"lc",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_lc_scheduler.n_list),
	.schedule =		ip_vs_lc_schedule,
पूर्ण;


अटल पूर्णांक __init ip_vs_lc_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_lc_scheduler) ;
पूर्ण

अटल व्योम __निकास ip_vs_lc_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_lc_scheduler);
	synchronize_rcu();
पूर्ण

module_init(ip_vs_lc_init);
module_निकास(ip_vs_lc_cleanup);
MODULE_LICENSE("GPL");
