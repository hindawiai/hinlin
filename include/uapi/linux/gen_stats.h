<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_GEN_STATS_H
#घोषणा __LINUX_GEN_STATS_H

#समावेश <linux/types.h>

क्रमागत अणु
	TCA_STATS_UNSPEC,
	TCA_STATS_BASIC,
	TCA_STATS_RATE_EST,
	TCA_STATS_QUEUE,
	TCA_STATS_APP,
	TCA_STATS_RATE_EST64,
	TCA_STATS_PAD,
	TCA_STATS_BASIC_HW,
	TCA_STATS_PKT64,
	__TCA_STATS_MAX,
पूर्ण;
#घोषणा TCA_STATS_MAX (__TCA_STATS_MAX - 1)

/**
 * काष्ठा gnet_stats_basic - byte/packet throughput statistics
 * @bytes: number of seen bytes
 * @packets: number of seen packets
 */
काष्ठा gnet_stats_basic अणु
	__u64	bytes;
	__u32	packets;
पूर्ण;

/**
 * काष्ठा gnet_stats_rate_est - rate estimator
 * @bps: current byte rate
 * @pps: current packet rate
 */
काष्ठा gnet_stats_rate_est अणु
	__u32	bps;
	__u32	pps;
पूर्ण;

/**
 * काष्ठा gnet_stats_rate_est64 - rate estimator
 * @bps: current byte rate
 * @pps: current packet rate
 */
काष्ठा gnet_stats_rate_est64 अणु
	__u64	bps;
	__u64	pps;
पूर्ण;

/**
 * काष्ठा gnet_stats_queue - queuing statistics
 * @qlen: queue length
 * @backlog: backlog size of queue
 * @drops: number of dropped packets
 * @requeues: number of requeues
 * @overlimits: number of enqueues over the limit
 */
काष्ठा gnet_stats_queue अणु
	__u32	qlen;
	__u32	backlog;
	__u32	drops;
	__u32	requeues;
	__u32	overlimits;
पूर्ण;

/**
 * काष्ठा gnet_estimator - rate estimator configuration
 * @पूर्णांकerval: sampling period
 * @ewma_log: the log of measurement winकरोw weight
 */
काष्ठा gnet_estimator अणु
	चिन्हित अक्षर	पूर्णांकerval;
	अचिन्हित अक्षर	ewma_log;
पूर्ण;


#पूर्ण_अगर /* __LINUX_GEN_STATS_H */
