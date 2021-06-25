<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Never Queue scheduling module
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *
 * Changes:
 */

/*
 * The NQ algorithm aकरोpts a two-speed model. When there is an idle server
 * available, the job will be sent to the idle server, instead of रुकोing
 * क्रम a fast one. When there is no idle server available, the job will be
 * sent to the server that minimize its expected delay (The Shortest
 * Expected Delay scheduling algorithm).
 *
 * See the following paper क्रम more inक्रमmation:
 * A. Weinrib and S. Shenker, Greed is not enough: Adaptive load sharing
 * in large heterogeneous प्रणालीs. In Proceedings IEEE INFOCOM'88,
 * pages 986-994, 1988.
 *
 * Thanks must go to Marko Buuri <marko@buuri.name> क्रम talking NQ to me.
 *
 * The dअगरference between NQ and SED is that NQ can improve overall
 * प्रणाली utilization.
 *
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <net/ip_vs.h>


अटल अंतरभूत पूर्णांक
ip_vs_nq_dest_overhead(काष्ठा ip_vs_dest *dest)
अणु
	/*
	 * We only use the active connection number in the cost
	 * calculation here.
	 */
	वापस atomic_पढ़ो(&dest->activeconns) + 1;
पूर्ण


/*
 *	Weighted Least Connection scheduling
 */
अटल काष्ठा ip_vs_dest *
ip_vs_nq_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		  काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest, *least = शून्य;
	पूर्णांक loh = 0, करोh;

	IP_VS_DBG(6, "%s(): Scheduling...\n", __func__);

	/*
	 * We calculate the load of each dest server as follows:
	 *	(server expected overhead) / dest->weight
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

		अगर (dest->flags & IP_VS_DEST_F_OVERLOAD ||
		    !atomic_पढ़ो(&dest->weight))
			जारी;

		करोh = ip_vs_nq_dest_overhead(dest);

		/* वापस the server directly अगर it is idle */
		अगर (atomic_पढ़ो(&dest->activeconns) == 0) अणु
			least = dest;
			loh = करोh;
			जाओ out;
		पूर्ण

		अगर (!least ||
		    ((__s64)loh * atomic_पढ़ो(&dest->weight) >
		     (__s64)करोh * atomic_पढ़ो(&least->weight))) अणु
			least = dest;
			loh = करोh;
		पूर्ण
	पूर्ण

	अगर (!least) अणु
		ip_vs_scheduler_err(svc, "no destination available");
		वापस शून्य;
	पूर्ण

  out:
	IP_VS_DBG_BUF(6, "NQ: server %s:%u "
		      "activeconns %d refcnt %d weight %d overhead %d\n",
		      IP_VS_DBG_ADDR(least->af, &least->addr),
		      ntohs(least->port),
		      atomic_पढ़ो(&least->activeconns),
		      refcount_पढ़ो(&least->refcnt),
		      atomic_पढ़ो(&least->weight), loh);

	वापस least;
पूर्ण


अटल काष्ठा ip_vs_scheduler ip_vs_nq_scheduler =
अणु
	.name =			"nq",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_nq_scheduler.n_list),
	.schedule =		ip_vs_nq_schedule,
पूर्ण;


अटल पूर्णांक __init ip_vs_nq_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_nq_scheduler);
पूर्ण

अटल व्योम __निकास ip_vs_nq_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_nq_scheduler);
	synchronize_rcu();
पूर्ण

module_init(ip_vs_nq_init);
module_निकास(ip_vs_nq_cleanup);
MODULE_LICENSE("GPL");
