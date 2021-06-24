<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Weighted Round-Robin Scheduling module
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *
 * Changes:
 *     Wensong Zhang            :     changed the ip_vs_wrr_schedule to वापस dest
 *     Wensong Zhang            :     changed some comestics things क्रम debugging
 *     Wensong Zhang            :     changed क्रम the d-linked destination list
 *     Wensong Zhang            :     added the ip_vs_wrr_update_svc
 *     Julian Anastasov         :     fixed the bug of वापसing destination
 *                                    with weight 0 when all weights are zero
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/net.h>
#समावेश <linux/gcd.h>

#समावेश <net/ip_vs.h>

/* The WRR algorithm depends on some caclulations:
 * - mw: maximum weight
 * - di: weight step, greatest common भागisor from all weights
 * - cw: current required weight
 * As result, all weights are in the [di..mw] range with a step=di.
 *
 * First, we start with cw = mw and select dests with weight >= cw.
 * Then cw is reduced with di and all dests are checked again.
 * Last pass should be with cw = di. We have mw/di passes in total:
 *
 * pass 1: cw = max weight
 * pass 2: cw = max weight - di
 * pass 3: cw = max weight - 2 * di
 * ...
 * last pass: cw = di
 *
 * Weights are supposed to be >= di but we run in parallel with
 * weight changes, it is possible some dest weight to be reduced
 * below di, bad अगर it is the only available dest.
 *
 * So, we modअगरy how mw is calculated, now it is reduced with (di - 1),
 * so that last cw is 1 to catch such dests with weight below di:
 * pass 1: cw = max weight - (di - 1)
 * pass 2: cw = max weight - di - (di - 1)
 * pass 3: cw = max weight - 2 * di - (di - 1)
 * ...
 * last pass: cw = 1
 *
 */

/*
 * current destination poपूर्णांकer क्रम weighted round-robin scheduling
 */
काष्ठा ip_vs_wrr_mark अणु
	काष्ठा ip_vs_dest *cl;	/* current dest or head */
	पूर्णांक cw;			/* current weight */
	पूर्णांक mw;			/* maximum weight */
	पूर्णांक di;			/* decreasing पूर्णांकerval */
	काष्ठा rcu_head		rcu_head;
पूर्ण;


अटल पूर्णांक ip_vs_wrr_gcd_weight(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_dest *dest;
	पूर्णांक weight;
	पूर्णांक g = 0;

	list_क्रम_each_entry(dest, &svc->destinations, n_list) अणु
		weight = atomic_पढ़ो(&dest->weight);
		अगर (weight > 0) अणु
			अगर (g > 0)
				g = gcd(weight, g);
			अन्यथा
				g = weight;
		पूर्ण
	पूर्ण
	वापस g ? g : 1;
पूर्ण


/*
 *    Get the maximum weight of the service destinations.
 */
अटल पूर्णांक ip_vs_wrr_max_weight(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_dest *dest;
	पूर्णांक new_weight, weight = 0;

	list_क्रम_each_entry(dest, &svc->destinations, n_list) अणु
		new_weight = atomic_पढ़ो(&dest->weight);
		अगर (new_weight > weight)
			weight = new_weight;
	पूर्ण

	वापस weight;
पूर्ण


अटल पूर्णांक ip_vs_wrr_init_svc(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_wrr_mark *mark;

	/*
	 *    Allocate the mark variable क्रम WRR scheduling
	 */
	mark = kदो_स्मृति(माप(काष्ठा ip_vs_wrr_mark), GFP_KERNEL);
	अगर (mark == शून्य)
		वापस -ENOMEM;

	mark->cl = list_entry(&svc->destinations, काष्ठा ip_vs_dest, n_list);
	mark->di = ip_vs_wrr_gcd_weight(svc);
	mark->mw = ip_vs_wrr_max_weight(svc) - (mark->di - 1);
	mark->cw = mark->mw;
	svc->sched_data = mark;

	वापस 0;
पूर्ण


अटल व्योम ip_vs_wrr_करोne_svc(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_wrr_mark *mark = svc->sched_data;

	/*
	 *    Release the mark variable
	 */
	kमुक्त_rcu(mark, rcu_head);
पूर्ण


अटल पूर्णांक ip_vs_wrr_dest_changed(काष्ठा ip_vs_service *svc,
				  काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_wrr_mark *mark = svc->sched_data;

	spin_lock_bh(&svc->sched_lock);
	mark->cl = list_entry(&svc->destinations, काष्ठा ip_vs_dest, n_list);
	mark->di = ip_vs_wrr_gcd_weight(svc);
	mark->mw = ip_vs_wrr_max_weight(svc) - (mark->di - 1);
	अगर (mark->cw > mark->mw || !mark->cw)
		mark->cw = mark->mw;
	अन्यथा अगर (mark->di > 1)
		mark->cw = (mark->cw / mark->di) * mark->di + 1;
	spin_unlock_bh(&svc->sched_lock);
	वापस 0;
पूर्ण


/*
 *    Weighted Round-Robin Scheduling
 */
अटल काष्ठा ip_vs_dest *
ip_vs_wrr_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		   काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest, *last, *stop = शून्य;
	काष्ठा ip_vs_wrr_mark *mark = svc->sched_data;
	bool last_pass = false, restarted = false;

	IP_VS_DBG(6, "%s(): Scheduling...\n", __func__);

	spin_lock_bh(&svc->sched_lock);
	dest = mark->cl;
	/* No available dests? */
	अगर (mark->mw == 0)
		जाओ err_noavail;
	last = dest;
	/* Stop only after all dests were checked क्रम weight >= 1 (last pass) */
	जबतक (1) अणु
		list_क्रम_each_entry_जारी_rcu(dest,
						 &svc->destinations,
						 n_list) अणु
			अगर (!(dest->flags & IP_VS_DEST_F_OVERLOAD) &&
			    atomic_पढ़ो(&dest->weight) >= mark->cw)
				जाओ found;
			अगर (dest == stop)
				जाओ err_over;
		पूर्ण
		mark->cw -= mark->di;
		अगर (mark->cw <= 0) अणु
			mark->cw = mark->mw;
			/* Stop अगर we tried last pass from first dest:
			 * 1. last_pass: we started checks when cw > di but
			 *	then all dests were checked क्रम w >= 1
			 * 2. last was head: the first and only traversal
			 *	was क्रम weight >= 1, क्रम all dests.
			 */
			अगर (last_pass ||
			    &last->n_list == &svc->destinations)
				जाओ err_over;
			restarted = true;
		पूर्ण
		last_pass = mark->cw <= mark->di;
		अगर (last_pass && restarted &&
		    &last->n_list != &svc->destinations) अणु
			/* First traversal was क्रम w >= 1 but only
			 * क्रम dests after 'last', now करो the same
			 * क्रम all dests up to 'last'.
			 */
			stop = last;
		पूर्ण
	पूर्ण

found:
	IP_VS_DBG_BUF(6, "WRR: server %s:%u "
		      "activeconns %d refcnt %d weight %d\n",
		      IP_VS_DBG_ADDR(dest->af, &dest->addr), ntohs(dest->port),
		      atomic_पढ़ो(&dest->activeconns),
		      refcount_पढ़ो(&dest->refcnt),
		      atomic_पढ़ो(&dest->weight));
	mark->cl = dest;

  out:
	spin_unlock_bh(&svc->sched_lock);
	वापस dest;

err_noavail:
	mark->cl = dest;
	dest = शून्य;
	ip_vs_scheduler_err(svc, "no destination available");
	जाओ out;

err_over:
	mark->cl = dest;
	dest = शून्य;
	ip_vs_scheduler_err(svc, "no destination available: "
			    "all destinations are overloaded");
	जाओ out;
पूर्ण


अटल काष्ठा ip_vs_scheduler ip_vs_wrr_scheduler = अणु
	.name =			"wrr",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_wrr_scheduler.n_list),
	.init_service =		ip_vs_wrr_init_svc,
	.करोne_service =		ip_vs_wrr_करोne_svc,
	.add_dest =		ip_vs_wrr_dest_changed,
	.del_dest =		ip_vs_wrr_dest_changed,
	.upd_dest =		ip_vs_wrr_dest_changed,
	.schedule =		ip_vs_wrr_schedule,
पूर्ण;

अटल पूर्णांक __init ip_vs_wrr_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_wrr_scheduler) ;
पूर्ण

अटल व्योम __निकास ip_vs_wrr_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_wrr_scheduler);
	synchronize_rcu();
पूर्ण

module_init(ip_vs_wrr_init);
module_निकास(ip_vs_wrr_cleanup);
MODULE_LICENSE("GPL");
