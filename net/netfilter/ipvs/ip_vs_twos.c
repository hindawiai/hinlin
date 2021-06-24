<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* IPVS:        Power of Twos Choice Scheduling module
 *
 * Authors:     Darby Payne <darby.payne@applovin.com>
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>

#समावेश <net/ip_vs.h>

/*    Power of Twos Choice scheduling, algorithm originally described by
 *    Michael Mitzenmacher.
 *
 *    Ranकरोmly picks two destinations and picks the one with the least
 *    amount of connections
 *
 *    The algorithm calculates a few variables
 *    - total_weight = sum of all weights
 *    - rweight1 = अक्रमom number between [0,total_weight]
 *    - rweight2 = अक्रमom number between [0,total_weight]
 *
 *    For each destination
 *      decrement rweight1 and rweight2 by the destination weight
 *      pick choice1 when rweight1 is <= 0
 *      pick choice2 when rweight2 is <= 0
 *
 *    Return choice2 अगर choice2 has less connections than choice 1 normalized
 *    by weight
 *
 * References
 * ----------
 *
 * [Mitzenmacher 2016]
 *    The Power of Two Ranकरोm Choices: A Survey of Techniques and Results
 *    Michael Mitzenmacher, Andrea W. Richa y, Ramesh Sitaraman
 *    http://www.eecs.harvard.edu/~michaelm/NEWWORK/postscripts/twosurvey.pdf
 *
 */
अटल काष्ठा ip_vs_dest *ip_vs_twos_schedule(काष्ठा ip_vs_service *svc,
					      स्थिर काष्ठा sk_buff *skb,
					      काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest, *choice1 = शून्य, *choice2 = शून्य;
	पूर्णांक rweight1, rweight2, weight1 = -1, weight2 = -1, overhead1 = 0;
	पूर्णांक overhead2, total_weight = 0, weight;

	IP_VS_DBG(6, "%s(): Scheduling...\n", __func__);

	/* Generate a अक्रमom weight between [0,sum of all weights) */
	list_क्रम_each_entry_rcu(dest, &svc->destinations, n_list) अणु
		अगर (!(dest->flags & IP_VS_DEST_F_OVERLOAD)) अणु
			weight = atomic_पढ़ो(&dest->weight);
			अगर (weight > 0) अणु
				total_weight += weight;
				choice1 = dest;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!choice1) अणु
		ip_vs_scheduler_err(svc, "no destination available");
		वापस शून्य;
	पूर्ण

	/* Add 1 to total_weight so that the अक्रमom weights are inclusive
	 * from 0 to total_weight
	 */
	total_weight += 1;
	rweight1 = pअक्रमom_u32() % total_weight;
	rweight2 = pअक्रमom_u32() % total_weight;

	/* Pick two weighted servers */
	list_क्रम_each_entry_rcu(dest, &svc->destinations, n_list) अणु
		अगर (dest->flags & IP_VS_DEST_F_OVERLOAD)
			जारी;

		weight = atomic_पढ़ो(&dest->weight);
		अगर (weight <= 0)
			जारी;

		rweight1 -= weight;
		rweight2 -= weight;

		अगर (rweight1 <= 0 && weight1 == -1) अणु
			choice1 = dest;
			weight1 = weight;
			overhead1 = ip_vs_dest_conn_overhead(dest);
		पूर्ण

		अगर (rweight2 <= 0 && weight2 == -1) अणु
			choice2 = dest;
			weight2 = weight;
			overhead2 = ip_vs_dest_conn_overhead(dest);
		पूर्ण

		अगर (weight1 != -1 && weight2 != -1)
			जाओ nextstage;
	पूर्ण

nextstage:
	अगर (choice2 && (weight2 * overhead1) > (weight1 * overhead2))
		choice1 = choice2;

	IP_VS_DBG_BUF(6, "twos: server %s:%u conns %d refcnt %d weight %d\n",
		      IP_VS_DBG_ADDR(choice1->af, &choice1->addr),
		      ntohs(choice1->port), atomic_पढ़ो(&choice1->activeconns),
		      refcount_पढ़ो(&choice1->refcnt),
		      atomic_पढ़ो(&choice1->weight));

	वापस choice1;
पूर्ण

अटल काष्ठा ip_vs_scheduler ip_vs_twos_scheduler = अणु
	.name = "twos",
	.refcnt = ATOMIC_INIT(0),
	.module = THIS_MODULE,
	.n_list = LIST_HEAD_INIT(ip_vs_twos_scheduler.n_list),
	.schedule = ip_vs_twos_schedule,
पूर्ण;

अटल पूर्णांक __init ip_vs_twos_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_twos_scheduler);
पूर्ण

अटल व्योम __निकास ip_vs_twos_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_twos_scheduler);
	synchronize_rcu();
पूर्ण

module_init(ip_vs_twos_init);
module_निकास(ip_vs_twos_cleanup);
MODULE_LICENSE("GPL");
