<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Overflow-Connection Scheduling module
 *
 * Authors:     Raducu Deaconu <rhaकरोo_io@yahoo.com>
 *
 * Scheduler implements "overflow" loadbalancing according to number of active
 * connections , will keep all connections to the node with the highest weight
 * and overflow to the next node अगर the number of connections exceeds the node's
 * weight.
 * Note that this scheduler might not be suitable क्रम UDP because it only uses
 * active connections
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <net/ip_vs.h>

/* OVF Connection scheduling  */
अटल काष्ठा ip_vs_dest *
ip_vs_ovf_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		   काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest, *h = शून्य;
	पूर्णांक hw = 0, w;

	IP_VS_DBG(6, "ip_vs_ovf_schedule(): Scheduling...\n");
	/* select the node with highest weight, go to next in line अगर active
	* connections exceed weight
	*/
	list_क्रम_each_entry_rcu(dest, &svc->destinations, n_list) अणु
		w = atomic_पढ़ो(&dest->weight);
		अगर ((dest->flags & IP_VS_DEST_F_OVERLOAD) ||
		    atomic_पढ़ो(&dest->activeconns) > w ||
		    w == 0)
			जारी;
		अगर (!h || w > hw) अणु
			h = dest;
			hw = w;
		पूर्ण
	पूर्ण

	अगर (h) अणु
		IP_VS_DBG_BUF(6, "OVF: server %s:%u active %d w %d\n",
			      IP_VS_DBG_ADDR(h->af, &h->addr),
			      ntohs(h->port),
			      atomic_पढ़ो(&h->activeconns),
			      atomic_पढ़ो(&h->weight));
		वापस h;
	पूर्ण

	ip_vs_scheduler_err(svc, "no destination available");
	वापस शून्य;
पूर्ण

अटल काष्ठा ip_vs_scheduler ip_vs_ovf_scheduler = अणु
	.name =			"ovf",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_ovf_scheduler.n_list),
	.schedule =		ip_vs_ovf_schedule,
पूर्ण;

अटल पूर्णांक __init ip_vs_ovf_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_ovf_scheduler);
पूर्ण

अटल व्योम __निकास ip_vs_ovf_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_ovf_scheduler);
	synchronize_rcu();
पूर्ण

module_init(ip_vs_ovf_init);
module_निकास(ip_vs_ovf_cleanup);
MODULE_LICENSE("GPL");
