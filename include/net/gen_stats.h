<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_GEN_STATS_H
#घोषणा __NET_GEN_STATS_H

#समावेश <linux/gen_stats.h>
#समावेश <linux/socket.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/pkt_sched.h>

/* Note: this used to be in include/uapi/linux/gen_stats.h */
काष्ठा gnet_stats_basic_packed अणु
	__u64	bytes;
	__u64	packets;
पूर्ण;

काष्ठा gnet_stats_basic_cpu अणु
	काष्ठा gnet_stats_basic_packed bstats;
	काष्ठा u64_stats_sync syncp;
पूर्ण __aligned(2 * माप(u64));

काष्ठा net_rate_estimator;

काष्ठा gnet_dump अणु
	spinlock_t *      lock;
	काष्ठा sk_buff *  skb;
	काष्ठा nlattr *   tail;

	/* Backward compatibility */
	पूर्णांक               compat_tc_stats;
	पूर्णांक               compat_xstats;
	पूर्णांक               padattr;
	व्योम *            xstats;
	पूर्णांक               xstats_len;
	काष्ठा tc_stats   tc_stats;
पूर्ण;

पूर्णांक gnet_stats_start_copy(काष्ठा sk_buff *skb, पूर्णांक type, spinlock_t *lock,
			  काष्ठा gnet_dump *d, पूर्णांक padattr);

पूर्णांक gnet_stats_start_copy_compat(काष्ठा sk_buff *skb, पूर्णांक type,
				 पूर्णांक tc_stats_type, पूर्णांक xstats_type,
				 spinlock_t *lock, काष्ठा gnet_dump *d,
				 पूर्णांक padattr);

पूर्णांक gnet_stats_copy_basic(स्थिर seqcount_t *running,
			  काष्ठा gnet_dump *d,
			  काष्ठा gnet_stats_basic_cpu __percpu *cpu,
			  काष्ठा gnet_stats_basic_packed *b);
व्योम __gnet_stats_copy_basic(स्थिर seqcount_t *running,
			     काष्ठा gnet_stats_basic_packed *bstats,
			     काष्ठा gnet_stats_basic_cpu __percpu *cpu,
			     काष्ठा gnet_stats_basic_packed *b);
पूर्णांक gnet_stats_copy_basic_hw(स्थिर seqcount_t *running,
			     काष्ठा gnet_dump *d,
			     काष्ठा gnet_stats_basic_cpu __percpu *cpu,
			     काष्ठा gnet_stats_basic_packed *b);
पूर्णांक gnet_stats_copy_rate_est(काष्ठा gnet_dump *d,
			     काष्ठा net_rate_estimator __rcu **ptr);
पूर्णांक gnet_stats_copy_queue(काष्ठा gnet_dump *d,
			  काष्ठा gnet_stats_queue __percpu *cpu_q,
			  काष्ठा gnet_stats_queue *q, __u32 qlen);
व्योम __gnet_stats_copy_queue(काष्ठा gnet_stats_queue *qstats,
			     स्थिर काष्ठा gnet_stats_queue __percpu *cpu_q,
			     स्थिर काष्ठा gnet_stats_queue *q, __u32 qlen);
पूर्णांक gnet_stats_copy_app(काष्ठा gnet_dump *d, व्योम *st, पूर्णांक len);

पूर्णांक gnet_stats_finish_copy(काष्ठा gnet_dump *d);

पूर्णांक gen_new_estimator(काष्ठा gnet_stats_basic_packed *bstats,
		      काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats,
		      काष्ठा net_rate_estimator __rcu **rate_est,
		      spinlock_t *lock,
		      seqcount_t *running, काष्ठा nlattr *opt);
व्योम gen_समाप्त_estimator(काष्ठा net_rate_estimator __rcu **ptr);
पूर्णांक gen_replace_estimator(काष्ठा gnet_stats_basic_packed *bstats,
			  काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats,
			  काष्ठा net_rate_estimator __rcu **ptr,
			  spinlock_t *lock,
			  seqcount_t *running, काष्ठा nlattr *opt);
bool gen_estimator_active(काष्ठा net_rate_estimator __rcu **ptr);
bool gen_estimator_पढ़ो(काष्ठा net_rate_estimator __rcu **ptr,
			काष्ठा gnet_stats_rate_est64 *sample);
#पूर्ण_अगर
