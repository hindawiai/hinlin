<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Statistics क्रम NFS server.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */
#अगर_अघोषित _NFSD_STATS_H
#घोषणा _NFSD_STATS_H

#समावेश <uapi/linux/nfsd/stats.h>
#समावेश <linux/percpu_counter.h>


क्रमागत अणु
	NFSD_STATS_RC_HITS,		/* repcache hits */
	NFSD_STATS_RC_MISSES,		/* repcache misses */
	NFSD_STATS_RC_NOCACHE,		/* uncached reqs */
	NFSD_STATS_FH_STALE,		/* FH stale error */
	NFSD_STATS_IO_READ,		/* bytes वापसed to पढ़ो requests */
	NFSD_STATS_IO_WRITE,		/* bytes passed in ग_लिखो requests */
#अगर_घोषित CONFIG_NFSD_V4
	NFSD_STATS_FIRST_NFS4_OP,	/* count of inभागidual nfsv4 operations */
	NFSD_STATS_LAST_NFS4_OP = NFSD_STATS_FIRST_NFS4_OP + LAST_NFS4_OP,
#घोषणा NFSD_STATS_NFS4_OP(op)	(NFSD_STATS_FIRST_NFS4_OP + (op))
#पूर्ण_अगर
	NFSD_STATS_COUNTERS_NUM
पूर्ण;

काष्ठा nfsd_stats अणु
	काष्ठा percpu_counter	counter[NFSD_STATS_COUNTERS_NUM];

	/* Protected by nfsd_mutex */
	अचिन्हित पूर्णांक	th_cnt;		/* number of available thपढ़ोs */
पूर्ण;


बाह्य काष्ठा nfsd_stats	nfsdstats;

बाह्य काष्ठा svc_stat		nfsd_svcstats;

पूर्णांक nfsd_percpu_counters_init(काष्ठा percpu_counter counters[], पूर्णांक num);
व्योम nfsd_percpu_counters_reset(काष्ठा percpu_counter counters[], पूर्णांक num);
व्योम nfsd_percpu_counters_destroy(काष्ठा percpu_counter counters[], पूर्णांक num);
पूर्णांक nfsd_stat_init(व्योम);
व्योम nfsd_stat_shutकरोwn(व्योम);

अटल अंतरभूत व्योम nfsd_stats_rc_hits_inc(व्योम)
अणु
	percpu_counter_inc(&nfsdstats.counter[NFSD_STATS_RC_HITS]);
पूर्ण

अटल अंतरभूत व्योम nfsd_stats_rc_misses_inc(व्योम)
अणु
	percpu_counter_inc(&nfsdstats.counter[NFSD_STATS_RC_MISSES]);
पूर्ण

अटल अंतरभूत व्योम nfsd_stats_rc_nocache_inc(व्योम)
अणु
	percpu_counter_inc(&nfsdstats.counter[NFSD_STATS_RC_NOCACHE]);
पूर्ण

अटल अंतरभूत व्योम nfsd_stats_fh_stale_inc(काष्ठा svc_export *exp)
अणु
	percpu_counter_inc(&nfsdstats.counter[NFSD_STATS_FH_STALE]);
	अगर (exp)
		percpu_counter_inc(&exp->ex_stats.counter[EXP_STATS_FH_STALE]);
पूर्ण

अटल अंतरभूत व्योम nfsd_stats_io_पढ़ो_add(काष्ठा svc_export *exp, s64 amount)
अणु
	percpu_counter_add(&nfsdstats.counter[NFSD_STATS_IO_READ], amount);
	अगर (exp)
		percpu_counter_add(&exp->ex_stats.counter[EXP_STATS_IO_READ], amount);
पूर्ण

अटल अंतरभूत व्योम nfsd_stats_io_ग_लिखो_add(काष्ठा svc_export *exp, s64 amount)
अणु
	percpu_counter_add(&nfsdstats.counter[NFSD_STATS_IO_WRITE], amount);
	अगर (exp)
		percpu_counter_add(&exp->ex_stats.counter[EXP_STATS_IO_WRITE], amount);
पूर्ण

अटल अंतरभूत व्योम nfsd_stats_payload_misses_inc(काष्ठा nfsd_net *nn)
अणु
	percpu_counter_inc(&nn->counter[NFSD_NET_PAYLOAD_MISSES]);
पूर्ण

अटल अंतरभूत व्योम nfsd_stats_drc_mem_usage_add(काष्ठा nfsd_net *nn, s64 amount)
अणु
	percpu_counter_add(&nn->counter[NFSD_NET_DRC_MEM_USAGE], amount);
पूर्ण

अटल अंतरभूत व्योम nfsd_stats_drc_mem_usage_sub(काष्ठा nfsd_net *nn, s64 amount)
अणु
	percpu_counter_sub(&nn->counter[NFSD_NET_DRC_MEM_USAGE], amount);
पूर्ण

#पूर्ण_अगर /* _NFSD_STATS_H */
