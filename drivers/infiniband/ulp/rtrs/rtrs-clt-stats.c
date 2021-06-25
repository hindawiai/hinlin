<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDMA Transport Layer
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME " L" __stringअगरy(__LINE__) ": " fmt

#समावेश "rtrs-clt.h"

व्योम rtrs_clt_update_wc_stats(काष्ठा rtrs_clt_con *con)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	काष्ठा rtrs_clt_stats *stats = sess->stats;
	काष्ठा rtrs_clt_stats_pcpu *s;
	पूर्णांक cpu;

	cpu = raw_smp_processor_id();
	s = this_cpu_ptr(stats->pcpu_stats);
	अगर (unlikely(con->cpu != cpu)) अणु
		s->cpu_migr.to++;

		/* Careful here, override s poपूर्णांकer */
		s = per_cpu_ptr(stats->pcpu_stats, con->cpu);
		atomic_inc(&s->cpu_migr.from);
	पूर्ण
पूर्ण

व्योम rtrs_clt_inc_failover_cnt(काष्ठा rtrs_clt_stats *stats)
अणु
	काष्ठा rtrs_clt_stats_pcpu *s;

	s = this_cpu_ptr(stats->pcpu_stats);
	s->rdma.failover_cnt++;
पूर्ण

पूर्णांक rtrs_clt_stats_migration_cnt_to_str(काष्ठा rtrs_clt_stats *stats,
					 अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा rtrs_clt_stats_pcpu *s;

	माप_प्रकार used;
	पूर्णांक cpu;

	used = scnम_लिखो(buf, len, "    ");
	क्रम_each_possible_cpu(cpu)
		used += scnम_लिखो(buf + used, len - used, " CPU%u", cpu);

	used += scnम_लिखो(buf + used, len - used, "\nfrom:");
	क्रम_each_possible_cpu(cpu) अणु
		s = per_cpu_ptr(stats->pcpu_stats, cpu);
		used += scnम_लिखो(buf + used, len - used, " %d",
				  atomic_पढ़ो(&s->cpu_migr.from));
	पूर्ण

	used += scnम_लिखो(buf + used, len - used, "\nto  :");
	क्रम_each_possible_cpu(cpu) अणु
		s = per_cpu_ptr(stats->pcpu_stats, cpu);
		used += scnम_लिखो(buf + used, len - used, " %d",
				  s->cpu_migr.to);
	पूर्ण
	used += scnम_लिखो(buf + used, len - used, "\n");

	वापस used;
पूर्ण

पूर्णांक rtrs_clt_stats_reconnects_to_str(काष्ठा rtrs_clt_stats *stats, अक्षर *buf,
				      माप_प्रकार len)
अणु
	वापस scnम_लिखो(buf, len, "%d %d\n",
			 stats->reconnects.successful_cnt,
			 stats->reconnects.fail_cnt);
पूर्ण

sमाप_प्रकार rtrs_clt_stats_rdma_to_str(काष्ठा rtrs_clt_stats *stats,
				    अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा rtrs_clt_stats_rdma sum;
	काष्ठा rtrs_clt_stats_rdma *r;
	पूर्णांक cpu;

	स_रखो(&sum, 0, माप(sum));

	क्रम_each_possible_cpu(cpu) अणु
		r = &per_cpu_ptr(stats->pcpu_stats, cpu)->rdma;

		sum.dir[READ].cnt	  += r->dir[READ].cnt;
		sum.dir[READ].माप_प्रकारotal  += r->dir[READ].माप_प्रकारotal;
		sum.dir[WRITE].cnt	  += r->dir[WRITE].cnt;
		sum.dir[WRITE].माप_प्रकारotal += r->dir[WRITE].माप_प्रकारotal;
		sum.failover_cnt	  += r->failover_cnt;
	पूर्ण

	वापस scnम_लिखो(page, len, "%llu %llu %llu %llu %u %llu\n",
			 sum.dir[READ].cnt, sum.dir[READ].माप_प्रकारotal,
			 sum.dir[WRITE].cnt, sum.dir[WRITE].माप_प्रकारotal,
			 atomic_पढ़ो(&stats->inflight), sum.failover_cnt);
पूर्ण

sमाप_प्रकार rtrs_clt_reset_all_help(काष्ठा rtrs_clt_stats *s,
				 अक्षर *page, माप_प्रकार len)
अणु
	वापस scnम_लिखो(page, len, "echo 1 to reset all statistics\n");
पूर्ण

पूर्णांक rtrs_clt_reset_rdma_stats(काष्ठा rtrs_clt_stats *stats, bool enable)
अणु
	काष्ठा rtrs_clt_stats_pcpu *s;
	पूर्णांक cpu;

	अगर (!enable)
		वापस -EINVAL;

	क्रम_each_possible_cpu(cpu) अणु
		s = per_cpu_ptr(stats->pcpu_stats, cpu);
		स_रखो(&s->rdma, 0, माप(s->rdma));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rtrs_clt_reset_cpu_migr_stats(काष्ठा rtrs_clt_stats *stats, bool enable)
अणु
	काष्ठा rtrs_clt_stats_pcpu *s;
	पूर्णांक cpu;

	अगर (!enable)
		वापस -EINVAL;

	क्रम_each_possible_cpu(cpu) अणु
		s = per_cpu_ptr(stats->pcpu_stats, cpu);
		स_रखो(&s->cpu_migr, 0, माप(s->cpu_migr));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rtrs_clt_reset_reconnects_stat(काष्ठा rtrs_clt_stats *stats, bool enable)
अणु
	अगर (!enable)
		वापस -EINVAL;

	स_रखो(&stats->reconnects, 0, माप(stats->reconnects));

	वापस 0;
पूर्ण

पूर्णांक rtrs_clt_reset_all_stats(काष्ठा rtrs_clt_stats *s, bool enable)
अणु
	अगर (enable) अणु
		rtrs_clt_reset_rdma_stats(s, enable);
		rtrs_clt_reset_cpu_migr_stats(s, enable);
		rtrs_clt_reset_reconnects_stat(s, enable);
		atomic_set(&s->inflight, 0);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम rtrs_clt_update_rdma_stats(काष्ठा rtrs_clt_stats *stats,
					       माप_प्रकार size, पूर्णांक d)
अणु
	काष्ठा rtrs_clt_stats_pcpu *s;

	s = this_cpu_ptr(stats->pcpu_stats);
	s->rdma.dir[d].cnt++;
	s->rdma.dir[d].माप_प्रकारotal += size;
पूर्ण

व्योम rtrs_clt_update_all_stats(काष्ठा rtrs_clt_io_req *req, पूर्णांक dir)
अणु
	काष्ठा rtrs_clt_con *con = req->con;
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	काष्ठा rtrs_clt_stats *stats = sess->stats;
	अचिन्हित पूर्णांक len;

	len = req->usr_len + req->data_len;
	rtrs_clt_update_rdma_stats(stats, len, dir);
	अगर (sess->clt->mp_policy == MP_POLICY_MIN_INFLIGHT)
		atomic_inc(&stats->inflight);
पूर्ण

पूर्णांक rtrs_clt_init_stats(काष्ठा rtrs_clt_stats *stats)
अणु
	stats->pcpu_stats = alloc_percpu(typeof(*stats->pcpu_stats));
	अगर (!stats->pcpu_stats)
		वापस -ENOMEM;

	/*
	 * successful_cnt will be set to 0 after session
	 * is established क्रम the first समय
	 */
	stats->reconnects.successful_cnt = -1;

	वापस 0;
पूर्ण
