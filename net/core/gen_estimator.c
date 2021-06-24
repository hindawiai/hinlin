<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/gen_estimator.c	Simple rate estimator.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *		Eric Dumazet <edumazet@google.com>
 *
 * Changes:
 *              Jamal Hadi Salim - moved it to net/core and reshulfed
 *              names to make it usable in general net subप्रणाली.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/in.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/seqlock.h>
#समावेश <net/sock.h>
#समावेश <net/gen_stats.h>

/* This code is NOT पूर्णांकended to be used क्रम statistics collection,
 * its purpose is to provide a base क्रम statistical multiplexing
 * क्रम controlled load service.
 * If you need only statistics, run a user level daemon which
 * periodically पढ़ोs byte counters.
 */

काष्ठा net_rate_estimator अणु
	काष्ठा gnet_stats_basic_packed	*bstats;
	spinlock_t		*stats_lock;
	seqcount_t		*running;
	काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats;
	u8			ewma_log;
	u8			पूर्णांकvl_log; /* period : (250ms << पूर्णांकvl_log) */

	seqcount_t		seq;
	u64			last_packets;
	u64			last_bytes;

	u64			avpps;
	u64			avbps;

	अचिन्हित दीर्घ           next_jअगरfies;
	काष्ठा समयr_list       समयr;
	काष्ठा rcu_head		rcu;
पूर्ण;

अटल व्योम est_fetch_counters(काष्ठा net_rate_estimator *e,
			       काष्ठा gnet_stats_basic_packed *b)
अणु
	स_रखो(b, 0, माप(*b));
	अगर (e->stats_lock)
		spin_lock(e->stats_lock);

	__gnet_stats_copy_basic(e->running, b, e->cpu_bstats, e->bstats);

	अगर (e->stats_lock)
		spin_unlock(e->stats_lock);

पूर्ण

अटल व्योम est_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा net_rate_estimator *est = from_समयr(est, t, समयr);
	काष्ठा gnet_stats_basic_packed b;
	u64 rate, brate;

	est_fetch_counters(est, &b);
	brate = (b.bytes - est->last_bytes) << (10 - est->पूर्णांकvl_log);
	brate = (brate >> est->ewma_log) - (est->avbps >> est->ewma_log);

	rate = (b.packets - est->last_packets) << (10 - est->पूर्णांकvl_log);
	rate = (rate >> est->ewma_log) - (est->avpps >> est->ewma_log);

	ग_लिखो_seqcount_begin(&est->seq);
	est->avbps += brate;
	est->avpps += rate;
	ग_लिखो_seqcount_end(&est->seq);

	est->last_bytes = b.bytes;
	est->last_packets = b.packets;

	est->next_jअगरfies += ((HZ/4) << est->पूर्णांकvl_log);

	अगर (unlikely(समय_after_eq(jअगरfies, est->next_jअगरfies))) अणु
		/* Ouch... समयr was delayed. */
		est->next_jअगरfies = jअगरfies + 1;
	पूर्ण
	mod_समयr(&est->समयr, est->next_jअगरfies);
पूर्ण

/**
 * gen_new_estimator - create a new rate estimator
 * @bstats: basic statistics
 * @cpu_bstats: bstats per cpu
 * @rate_est: rate estimator statistics
 * @lock: lock क्रम statistics and control path
 * @running: qdisc running seqcount
 * @opt: rate estimator configuration TLV
 *
 * Creates a new rate estimator with &bstats as source and &rate_est
 * as destination. A new समयr with the पूर्णांकerval specअगरied in the
 * configuration TLV is created. Upon each पूर्णांकerval, the latest statistics
 * will be पढ़ो from &bstats and the estimated rate will be stored in
 * &rate_est with the statistics lock grabbed during this period.
 *
 * Returns 0 on success or a negative error code.
 *
 */
पूर्णांक gen_new_estimator(काष्ठा gnet_stats_basic_packed *bstats,
		      काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats,
		      काष्ठा net_rate_estimator __rcu **rate_est,
		      spinlock_t *lock,
		      seqcount_t *running,
		      काष्ठा nlattr *opt)
अणु
	काष्ठा gnet_estimator *parm = nla_data(opt);
	काष्ठा net_rate_estimator *old, *est;
	काष्ठा gnet_stats_basic_packed b;
	पूर्णांक पूर्णांकvl_log;

	अगर (nla_len(opt) < माप(*parm))
		वापस -EINVAL;

	/* allowed समयr periods are :
	 * -2 : 250ms,   -1 : 500ms,    0 : 1 sec
	 *  1 : 2 sec,    2 : 4 sec,    3 : 8 sec
	 */
	अगर (parm->पूर्णांकerval < -2 || parm->पूर्णांकerval > 3)
		वापस -EINVAL;

	अगर (parm->ewma_log == 0 || parm->ewma_log >= 31)
		वापस -EINVAL;

	est = kzalloc(माप(*est), GFP_KERNEL);
	अगर (!est)
		वापस -ENOBUFS;

	seqcount_init(&est->seq);
	पूर्णांकvl_log = parm->पूर्णांकerval + 2;
	est->bstats = bstats;
	est->stats_lock = lock;
	est->running  = running;
	est->ewma_log = parm->ewma_log;
	est->पूर्णांकvl_log = पूर्णांकvl_log;
	est->cpu_bstats = cpu_bstats;

	अगर (lock)
		local_bh_disable();
	est_fetch_counters(est, &b);
	अगर (lock)
		local_bh_enable();
	est->last_bytes = b.bytes;
	est->last_packets = b.packets;

	अगर (lock)
		spin_lock_bh(lock);
	old = rcu_dereference_रक्षित(*rate_est, 1);
	अगर (old) अणु
		del_समयr_sync(&old->समयr);
		est->avbps = old->avbps;
		est->avpps = old->avpps;
	पूर्ण

	est->next_jअगरfies = jअगरfies + ((HZ/4) << पूर्णांकvl_log);
	समयr_setup(&est->समयr, est_समयr, 0);
	mod_समयr(&est->समयr, est->next_jअगरfies);

	rcu_assign_poपूर्णांकer(*rate_est, est);
	अगर (lock)
		spin_unlock_bh(lock);
	अगर (old)
		kमुक्त_rcu(old, rcu);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(gen_new_estimator);

/**
 * gen_समाप्त_estimator - हटाओ a rate estimator
 * @rate_est: rate estimator
 *
 * Removes the rate estimator.
 *
 */
व्योम gen_समाप्त_estimator(काष्ठा net_rate_estimator __rcu **rate_est)
अणु
	काष्ठा net_rate_estimator *est;

	est = xchg((__क्रमce काष्ठा net_rate_estimator **)rate_est, शून्य);
	अगर (est) अणु
		del_समयr_sync(&est->समयr);
		kमुक्त_rcu(est, rcu);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(gen_समाप्त_estimator);

/**
 * gen_replace_estimator - replace rate estimator configuration
 * @bstats: basic statistics
 * @cpu_bstats: bstats per cpu
 * @rate_est: rate estimator statistics
 * @lock: lock क्रम statistics and control path
 * @running: qdisc running seqcount (might be शून्य)
 * @opt: rate estimator configuration TLV
 *
 * Replaces the configuration of a rate estimator by calling
 * gen_समाप्त_estimator() and gen_new_estimator().
 *
 * Returns 0 on success or a negative error code.
 */
पूर्णांक gen_replace_estimator(काष्ठा gnet_stats_basic_packed *bstats,
			  काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats,
			  काष्ठा net_rate_estimator __rcu **rate_est,
			  spinlock_t *lock,
			  seqcount_t *running, काष्ठा nlattr *opt)
अणु
	वापस gen_new_estimator(bstats, cpu_bstats, rate_est,
				 lock, running, opt);
पूर्ण
EXPORT_SYMBOL(gen_replace_estimator);

/**
 * gen_estimator_active - test अगर estimator is currently in use
 * @rate_est: rate estimator
 *
 * Returns true अगर estimator is active, and false अगर not.
 */
bool gen_estimator_active(काष्ठा net_rate_estimator __rcu **rate_est)
अणु
	वापस !!rcu_access_poपूर्णांकer(*rate_est);
पूर्ण
EXPORT_SYMBOL(gen_estimator_active);

bool gen_estimator_पढ़ो(काष्ठा net_rate_estimator __rcu **rate_est,
			काष्ठा gnet_stats_rate_est64 *sample)
अणु
	काष्ठा net_rate_estimator *est;
	अचिन्हित seq;

	rcu_पढ़ो_lock();
	est = rcu_dereference(*rate_est);
	अगर (!est) अणु
		rcu_पढ़ो_unlock();
		वापस false;
	पूर्ण

	करो अणु
		seq = पढ़ो_seqcount_begin(&est->seq);
		sample->bps = est->avbps >> 8;
		sample->pps = est->avpps >> 8;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&est->seq, seq));

	rcu_पढ़ो_unlock();
	वापस true;
पूर्ण
EXPORT_SYMBOL(gen_estimator_पढ़ो);
