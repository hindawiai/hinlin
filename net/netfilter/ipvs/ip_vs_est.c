<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ip_vs_est.c: simple rate estimator क्रम IPVS
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *
 * Changes:     Hans Schillstrom <hans.schillstrom@ericsson.com>
 *              Network name space (netns) aware.
 *              Global data moved to netns i.e काष्ठा netns_ipvs
 *              Affected data: est_list and est_lock.
 *              estimation_समयr() runs with समयr per netns.
 *              get_stats()) करो the per cpu summing.
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/list.h>

#समावेश <net/ip_vs.h>

/*
  This code is to estimate rate in a लघुer पूर्णांकerval (such as 8
  seconds) क्रम भव services and real servers. For measure rate in a
  दीर्घ पूर्णांकerval, it is easy to implement a user level daemon which
  periodically पढ़ोs those statistical counters and measure rate.

  Currently, the measurement is activated by slow समयr handler. Hope
  this measurement will not पूर्णांकroduce too much load.

  We measure rate during the last 8 seconds every 2 seconds:

    avgrate = avgrate*(1-W) + rate*W

    where W = 2^(-2)

  NOTES.

  * Average bps is scaled by 2^5, जबतक average pps and cps are scaled by 2^10.

  * Netlink users can see 64-bit values but sockopt users are restricted
    to 32-bit values क्रम conns, packets, bps, cps and pps.

  * A lot of code is taken from net/core/gen_estimator.c
 */


/*
 * Make a summary from each cpu
 */
अटल व्योम ip_vs_पढ़ो_cpu_stats(काष्ठा ip_vs_kstats *sum,
				 काष्ठा ip_vs_cpu_stats __percpu *stats)
अणु
	पूर्णांक i;
	bool add = false;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा ip_vs_cpu_stats *s = per_cpu_ptr(stats, i);
		अचिन्हित पूर्णांक start;
		u64 conns, inpkts, outpkts, inbytes, outbytes;

		अगर (add) अणु
			करो अणु
				start = u64_stats_fetch_begin(&s->syncp);
				conns = s->cnt.conns;
				inpkts = s->cnt.inpkts;
				outpkts = s->cnt.outpkts;
				inbytes = s->cnt.inbytes;
				outbytes = s->cnt.outbytes;
			पूर्ण जबतक (u64_stats_fetch_retry(&s->syncp, start));
			sum->conns += conns;
			sum->inpkts += inpkts;
			sum->outpkts += outpkts;
			sum->inbytes += inbytes;
			sum->outbytes += outbytes;
		पूर्ण अन्यथा अणु
			add = true;
			करो अणु
				start = u64_stats_fetch_begin(&s->syncp);
				sum->conns = s->cnt.conns;
				sum->inpkts = s->cnt.inpkts;
				sum->outpkts = s->cnt.outpkts;
				sum->inbytes = s->cnt.inbytes;
				sum->outbytes = s->cnt.outbytes;
			पूर्ण जबतक (u64_stats_fetch_retry(&s->syncp, start));
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम estimation_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ip_vs_estimator *e;
	काष्ठा ip_vs_stats *s;
	u64 rate;
	काष्ठा netns_ipvs *ipvs = from_समयr(ipvs, t, est_समयr);

	spin_lock(&ipvs->est_lock);
	list_क्रम_each_entry(e, &ipvs->est_list, list) अणु
		s = container_of(e, काष्ठा ip_vs_stats, est);

		spin_lock(&s->lock);
		ip_vs_पढ़ो_cpu_stats(&s->kstats, s->cpustats);

		/* scaled by 2^10, but भागided 2 seconds */
		rate = (s->kstats.conns - e->last_conns) << 9;
		e->last_conns = s->kstats.conns;
		e->cps += ((s64)rate - (s64)e->cps) >> 2;

		rate = (s->kstats.inpkts - e->last_inpkts) << 9;
		e->last_inpkts = s->kstats.inpkts;
		e->inpps += ((s64)rate - (s64)e->inpps) >> 2;

		rate = (s->kstats.outpkts - e->last_outpkts) << 9;
		e->last_outpkts = s->kstats.outpkts;
		e->outpps += ((s64)rate - (s64)e->outpps) >> 2;

		/* scaled by 2^5, but भागided 2 seconds */
		rate = (s->kstats.inbytes - e->last_inbytes) << 4;
		e->last_inbytes = s->kstats.inbytes;
		e->inbps += ((s64)rate - (s64)e->inbps) >> 2;

		rate = (s->kstats.outbytes - e->last_outbytes) << 4;
		e->last_outbytes = s->kstats.outbytes;
		e->outbps += ((s64)rate - (s64)e->outbps) >> 2;
		spin_unlock(&s->lock);
	पूर्ण
	spin_unlock(&ipvs->est_lock);
	mod_समयr(&ipvs->est_समयr, jअगरfies + 2*HZ);
पूर्ण

व्योम ip_vs_start_estimator(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_stats *stats)
अणु
	काष्ठा ip_vs_estimator *est = &stats->est;

	INIT_LIST_HEAD(&est->list);

	spin_lock_bh(&ipvs->est_lock);
	list_add(&est->list, &ipvs->est_list);
	spin_unlock_bh(&ipvs->est_lock);
पूर्ण

व्योम ip_vs_stop_estimator(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_stats *stats)
अणु
	काष्ठा ip_vs_estimator *est = &stats->est;

	spin_lock_bh(&ipvs->est_lock);
	list_del(&est->list);
	spin_unlock_bh(&ipvs->est_lock);
पूर्ण

व्योम ip_vs_zero_estimator(काष्ठा ip_vs_stats *stats)
अणु
	काष्ठा ip_vs_estimator *est = &stats->est;
	काष्ठा ip_vs_kstats *k = &stats->kstats;

	/* reset counters, caller must hold the stats->lock lock */
	est->last_inbytes = k->inbytes;
	est->last_outbytes = k->outbytes;
	est->last_conns = k->conns;
	est->last_inpkts = k->inpkts;
	est->last_outpkts = k->outpkts;
	est->cps = 0;
	est->inpps = 0;
	est->outpps = 0;
	est->inbps = 0;
	est->outbps = 0;
पूर्ण

/* Get decoded rates */
व्योम ip_vs_पढ़ो_estimator(काष्ठा ip_vs_kstats *dst, काष्ठा ip_vs_stats *stats)
अणु
	काष्ठा ip_vs_estimator *e = &stats->est;

	dst->cps = (e->cps + 0x1FF) >> 10;
	dst->inpps = (e->inpps + 0x1FF) >> 10;
	dst->outpps = (e->outpps + 0x1FF) >> 10;
	dst->inbps = (e->inbps + 0xF) >> 5;
	dst->outbps = (e->outbps + 0xF) >> 5;
पूर्ण

पूर्णांक __net_init ip_vs_estimator_net_init(काष्ठा netns_ipvs *ipvs)
अणु
	INIT_LIST_HEAD(&ipvs->est_list);
	spin_lock_init(&ipvs->est_lock);
	समयr_setup(&ipvs->est_समयr, estimation_समयr, 0);
	mod_समयr(&ipvs->est_समयr, jअगरfies + 2 * HZ);
	वापस 0;
पूर्ण

व्योम __net_निकास ip_vs_estimator_net_cleanup(काष्ठा netns_ipvs *ipvs)
अणु
	del_समयr_sync(&ipvs->est_समयr);
पूर्ण
