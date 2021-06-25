<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Weighted Fail Over module
 *
 * Authors:     Kenny Mathis <kmathis@chokepoपूर्णांक.net>
 *
 * Changes:
 *     Kenny Mathis            :     added initial functionality based on weight
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <net/ip_vs.h>

/* Weighted Fail Over Module */
अटल काष्ठा ip_vs_dest *
ip_vs_fo_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		  काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest, *hweight = शून्य;
	पूर्णांक hw = 0; /* Track highest weight */

	IP_VS_DBG(6, "ip_vs_fo_schedule(): Scheduling...\n");

	/* Basic failover functionality
	 * Find भव server with highest weight and send it traffic
	 */
	list_क्रम_each_entry_rcu(dest, &svc->destinations, n_list) अणु
		अगर (!(dest->flags & IP_VS_DEST_F_OVERLOAD) &&
		    atomic_पढ़ो(&dest->weight) > hw) अणु
			hweight = dest;
			hw = atomic_पढ़ो(&dest->weight);
		पूर्ण
	पूर्ण

	अगर (hweight) अणु
		IP_VS_DBG_BUF(6, "FO: server %s:%u activeconns %d weight %d\n",
			      IP_VS_DBG_ADDR(hweight->af, &hweight->addr),
			      ntohs(hweight->port),
			      atomic_पढ़ो(&hweight->activeconns),
			      atomic_पढ़ो(&hweight->weight));
		वापस hweight;
	पूर्ण

	ip_vs_scheduler_err(svc, "no destination available");
	वापस शून्य;
पूर्ण

अटल काष्ठा ip_vs_scheduler ip_vs_fo_scheduler = अणु
	.name =			"fo",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_fo_scheduler.n_list),
	.schedule =		ip_vs_fo_schedule,
पूर्ण;

अटल पूर्णांक __init ip_vs_fo_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_fo_scheduler);
पूर्ण

अटल व्योम __निकास ip_vs_fo_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_fo_scheduler);
	synchronize_rcu();
पूर्ण

module_init(ip_vs_fo_init);
module_निकास(ip_vs_fo_cleanup);
MODULE_LICENSE("GPL");
