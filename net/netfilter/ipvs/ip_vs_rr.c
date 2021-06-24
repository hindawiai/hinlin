<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Round-Robin Scheduling module
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Peter Kese <peter.kese@ijs.si>
 *
 * Fixes/Changes:
 *     Wensong Zhang            :     changed the ip_vs_rr_schedule to वापस dest
 *     Julian Anastasov         :     fixed the शून्य poपूर्णांकer access bug in debugging
 *     Wensong Zhang            :     changed some comestics things क्रम debugging
 *     Wensong Zhang            :     changed क्रम the d-linked destination list
 *     Wensong Zhang            :     added the ip_vs_rr_update_svc
 *     Wensong Zhang            :     added any dest with weight=0 is quiesced
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <net/ip_vs.h>


अटल पूर्णांक ip_vs_rr_init_svc(काष्ठा ip_vs_service *svc)
अणु
	svc->sched_data = &svc->destinations;
	वापस 0;
पूर्ण


अटल पूर्णांक ip_vs_rr_del_dest(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा list_head *p;

	spin_lock_bh(&svc->sched_lock);
	p = (काष्ठा list_head *) svc->sched_data;
	/* dest is alपढ़ोy unlinked, so p->prev is not valid but
	 * p->next is valid, use it to reach previous entry.
	 */
	अगर (p == &dest->n_list)
		svc->sched_data = p->next->prev;
	spin_unlock_bh(&svc->sched_lock);
	वापस 0;
पूर्ण


/*
 * Round-Robin Scheduling
 */
अटल काष्ठा ip_vs_dest *
ip_vs_rr_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		  काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा list_head *p;
	काष्ठा ip_vs_dest *dest, *last;
	पूर्णांक pass = 0;

	IP_VS_DBG(6, "%s(): Scheduling...\n", __func__);

	spin_lock_bh(&svc->sched_lock);
	p = (काष्ठा list_head *) svc->sched_data;
	last = dest = list_entry(p, काष्ठा ip_vs_dest, n_list);

	करो अणु
		list_क्रम_each_entry_जारी_rcu(dest,
						 &svc->destinations,
						 n_list) अणु
			अगर (!(dest->flags & IP_VS_DEST_F_OVERLOAD) &&
			    atomic_पढ़ो(&dest->weight) > 0)
				/* HIT */
				जाओ out;
			अगर (dest == last)
				जाओ stop;
		पूर्ण
		pass++;
		/* Previous dest could be unlinked, करो not loop क्रमever.
		 * If we stay at head there is no need क्रम 2nd pass.
		 */
	पूर्ण जबतक (pass < 2 && p != &svc->destinations);

stop:
	spin_unlock_bh(&svc->sched_lock);
	ip_vs_scheduler_err(svc, "no destination available");
	वापस शून्य;

  out:
	svc->sched_data = &dest->n_list;
	spin_unlock_bh(&svc->sched_lock);
	IP_VS_DBG_BUF(6, "RR: server %s:%u "
		      "activeconns %d refcnt %d weight %d\n",
		      IP_VS_DBG_ADDR(dest->af, &dest->addr), ntohs(dest->port),
		      atomic_पढ़ो(&dest->activeconns),
		      refcount_पढ़ो(&dest->refcnt), atomic_पढ़ो(&dest->weight));

	वापस dest;
पूर्ण


अटल काष्ठा ip_vs_scheduler ip_vs_rr_scheduler = अणु
	.name =			"rr",			/* name */
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_rr_scheduler.n_list),
	.init_service =		ip_vs_rr_init_svc,
	.add_dest =		शून्य,
	.del_dest =		ip_vs_rr_del_dest,
	.schedule =		ip_vs_rr_schedule,
पूर्ण;

अटल पूर्णांक __init ip_vs_rr_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_rr_scheduler);
पूर्ण

अटल व्योम __निकास ip_vs_rr_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_rr_scheduler);
	synchronize_rcu();
पूर्ण

module_init(ip_vs_rr_init);
module_निकास(ip_vs_rr_cleanup);
MODULE_LICENSE("GPL");
