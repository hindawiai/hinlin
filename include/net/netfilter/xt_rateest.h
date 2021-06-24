<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XT_RATEEST_H
#घोषणा _XT_RATEEST_H

#समावेश <net/gen_stats.h>

काष्ठा xt_rateest अणु
	/* keep lock and bstats on same cache line to speedup xt_rateest_tg() */
	काष्ठा gnet_stats_basic_packed	bstats;
	spinlock_t			lock;


	/* following fields not accessed in hot path */
	अचिन्हित पूर्णांक			refcnt;
	काष्ठा hlist_node		list;
	अक्षर				name[IFNAMSIZ];
	काष्ठा gnet_estimator		params;
	काष्ठा rcu_head			rcu;

	/* keep this field far away to speedup xt_rateest_mt() */
	काष्ठा net_rate_estimator __rcu *rate_est;
पूर्ण;

काष्ठा xt_rateest *xt_rateest_lookup(काष्ठा net *net, स्थिर अक्षर *name);
व्योम xt_rateest_put(काष्ठा net *net, काष्ठा xt_rateest *est);

#पूर्ण_अगर /* _XT_RATEEST_H */
