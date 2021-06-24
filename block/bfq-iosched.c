<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Budget Fair Queueing (BFQ) I/O scheduler.
 *
 * Based on ideas and code from CFQ:
 * Copyright (C) 2003 Jens Axboe <axboe@kernel.dk>
 *
 * Copyright (C) 2008 Fabio Checconi <fabio@gandalf.sssup.it>
 *		      Paolo Valente <paolo.valente@unimore.it>
 *
 * Copyright (C) 2010 Paolo Valente <paolo.valente@unimore.it>
 *                    Arianna Avanzini <avanzini@google.com>
 *
 * Copyright (C) 2017 Paolo Valente <paolo.valente@linaro.org>
 *
 * BFQ is a proportional-share I/O scheduler, with some extra
 * low-latency capabilities. BFQ also supports full hierarchical
 * scheduling through cgroups. Next paragraphs provide an पूर्णांकroduction
 * on BFQ inner workings. Details on BFQ benefits, usage and
 * limitations can be found in Documentation/block/bfq-iosched.rst.
 *
 * BFQ is a proportional-share storage-I/O scheduling algorithm based
 * on the slice-by-slice service scheme of CFQ. But BFQ assigns
 * budमाला_लो, measured in number of sectors, to processes instead of
 * समय slices. The device is not granted to the in-service process
 * क्रम a given समय slice, but until it has exhausted its asचिन्हित
 * budget. This change from the समय to the service करोमुख्य enables BFQ
 * to distribute the device throughput among processes as desired,
 * without any distortion due to throughput fluctuations, or to device
 * पूर्णांकernal queueing. BFQ uses an ad hoc पूर्णांकernal scheduler, called
 * B-WF2Q+, to schedule processes according to their budमाला_लो. More
 * precisely, BFQ schedules queues associated with processes. Each
 * process/queue is asचिन्हित a user-configurable weight, and B-WF2Q+
 * guarantees that each queue receives a fraction of the throughput
 * proportional to its weight. Thanks to the accurate policy of
 * B-WF2Q+, BFQ can afक्रमd to assign high budमाला_लो to I/O-bound
 * processes issuing sequential requests (to boost the throughput),
 * and yet guarantee a low latency to पूर्णांकeractive and soft real-समय
 * applications.
 *
 * In particular, to provide these low-latency guarantees, BFQ
 * explicitly privileges the I/O of two classes of समय-sensitive
 * applications: पूर्णांकeractive and soft real-समय. In more detail, BFQ
 * behaves this way अगर the low_latency parameter is set (शेष
 * configuration). This feature enables BFQ to provide applications in
 * these classes with a very low latency.
 *
 * To implement this feature, BFQ स्थिरantly tries to detect whether
 * the I/O requests in a bfq_queue come from an पूर्णांकeractive or a soft
 * real-समय application. For brevity, in these हालs, the queue is
 * said to be पूर्णांकeractive or soft real-समय. In both हालs, BFQ
 * privileges the service of the queue, over that of non-पूर्णांकeractive
 * and non-soft-real-समय queues. This privileging is perक्रमmed,
 * मुख्यly, by raising the weight of the queue. So, क्रम brevity, we
 * call just weight-raising periods the समय periods during which a
 * queue is privileged, because deemed पूर्णांकeractive or soft real-समय.
 *
 * The detection of soft real-समय queues/applications is described in
 * detail in the comments on the function
 * bfq_bfqq_softrt_next_start. On the other hand, the detection of an
 * पूर्णांकeractive queue works as follows: a queue is deemed पूर्णांकeractive
 * अगर it is स्थिरantly non empty only क्रम a limited समय पूर्णांकerval,
 * after which it करोes become empty. The queue may be deemed
 * पूर्णांकeractive again (क्रम a limited समय), अगर it restarts being
 * स्थिरantly non empty, provided that this happens only after the
 * queue has reमुख्यed empty क्रम a given minimum idle समय.
 *
 * By शेष, BFQ computes स्वतःmatically the above maximum समय
 * पूर्णांकerval, i.e., the समय पूर्णांकerval after which a स्थिरantly
 * non-empty queue stops being deemed पूर्णांकeractive. Since a queue is
 * weight-उठाओd जबतक it is deemed पूर्णांकeractive, this maximum समय
 * पूर्णांकerval happens to coincide with the (maximum) duration of the
 * weight-raising क्रम पूर्णांकeractive queues.
 *
 * Finally, BFQ also features additional heuristics क्रम
 * preserving both a low latency and a high throughput on NCQ-capable,
 * rotational or flash-based devices, and to get the job करोne quickly
 * क्रम applications consisting in many I/O-bound processes.
 *
 * NOTE: अगर the मुख्य or only goal, with a given device, is to achieve
 * the maximum-possible throughput at all बार, then करो चयन off
 * all low-latency heuristics क्रम that device, by setting low_latency
 * to 0.
 *
 * BFQ is described in [1], where also a reference to the initial,
 * more theoretical paper on BFQ can be found. The पूर्णांकerested पढ़ोer
 * can find in the latter paper full details on the मुख्य algorithm, as
 * well as क्रमmulas of the guarantees and क्रमmal proofs of all the
 * properties.  With respect to the version of BFQ presented in these
 * papers, this implementation adds a few more heuristics, such as the
 * ones that guarantee a low latency to पूर्णांकeractive and soft real-समय
 * applications, and a hierarchical extension based on H-WF2Q+.
 *
 * B-WF2Q+ is based on WF2Q+, which is described in [2], together with
 * H-WF2Q+, जबतक the augmented tree used here to implement B-WF2Q+
 * with O(log N) complनिकासy derives from the one पूर्णांकroduced with EEVDF
 * in [3].
 *
 * [1] P. Valente, A. Avanzini, "Evolution of the BFQ Storage I/O
 *     Scheduler", Proceedings of the First Workshop on Mobile System
 *     Technologies (MST-2015), May 2015.
 *     http://algogroup.unimore.it/people/paolo/disk_sched/mst-2015.pdf
 *
 * [2] Jon C.R. Bennett and H. Zhang, "Hierarchical Packet Fair Queueing
 *     Algorithms", IEEE/ACM Transactions on Networking, 5(5):675-689,
 *     Oct 1997.
 *
 * http://www.cs.cmu.edu/~hzhang/papers/TON-97-Oct.ps.gz
 *
 * [3] I. Stoica and H. Abdel-Wahab, "Earliest Eligible Virtual Deadline
 *     First: A Flexible and Accurate Mechanism क्रम Proportional Share
 *     Resource Allocation", technical report.
 *
 * http://www.cs.berkeley.edu/~istoica/papers/eevdf-tr-95.pdf
 */
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/elevator.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/rbtree.h>
#समावेश <linux/ioprपन.स>
#समावेश <linux/sbiपंचांगap.h>
#समावेश <linux/delay.h>
#समावेश <linux/backing-dev.h>

#समावेश <trace/events/block.h>

#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-tag.h"
#समावेश "blk-mq-sched.h"
#समावेश "bfq-iosched.h"
#समावेश "blk-wbt.h"

#घोषणा BFQ_BFQQ_FNS(name)						\
व्योम bfq_mark_bfqq_##name(काष्ठा bfq_queue *bfqq)			\
अणु									\
	__set_bit(BFQQF_##name, &(bfqq)->flags);			\
पूर्ण									\
व्योम bfq_clear_bfqq_##name(काष्ठा bfq_queue *bfqq)			\
अणु									\
	__clear_bit(BFQQF_##name, &(bfqq)->flags);		\
पूर्ण									\
पूर्णांक bfq_bfqq_##name(स्थिर काष्ठा bfq_queue *bfqq)			\
अणु									\
	वापस test_bit(BFQQF_##name, &(bfqq)->flags);		\
पूर्ण

BFQ_BFQQ_FNS(just_created);
BFQ_BFQQ_FNS(busy);
BFQ_BFQQ_FNS(रुको_request);
BFQ_BFQQ_FNS(non_blocking_रुको_rq);
BFQ_BFQQ_FNS(fअगरo_expire);
BFQ_BFQQ_FNS(has_लघु_tसमय);
BFQ_BFQQ_FNS(sync);
BFQ_BFQQ_FNS(IO_bound);
BFQ_BFQQ_FNS(in_large_burst);
BFQ_BFQQ_FNS(coop);
BFQ_BFQQ_FNS(split_coop);
BFQ_BFQQ_FNS(softrt_update);
#अघोषित BFQ_BFQQ_FNS						\

/* Expiration समय of async (0) and sync (1) requests, in ns. */
अटल स्थिर u64 bfq_fअगरo_expire[2] = अणु NSEC_PER_SEC / 4, NSEC_PER_SEC / 8 पूर्ण;

/* Maximum backwards seek (magic number lअगरted from CFQ), in KiB. */
अटल स्थिर पूर्णांक bfq_back_max = 16 * 1024;

/* Penalty of a backwards seek, in number of sectors. */
अटल स्थिर पूर्णांक bfq_back_penalty = 2;

/* Idling period duration, in ns. */
अटल u64 bfq_slice_idle = NSEC_PER_SEC / 125;

/* Minimum number of asचिन्हित budमाला_लो क्रम which stats are safe to compute. */
अटल स्थिर पूर्णांक bfq_stats_min_budमाला_लो = 194;

/* Default maximum budget values, in sectors and number of requests. */
अटल स्थिर पूर्णांक bfq_शेष_max_budget = 16 * 1024;

/*
 * When a sync request is dispatched, the queue that contains that
 * request, and all the ancestor entities of that queue, are अक्षरged
 * with the number of sectors of the request. In contrast, अगर the
 * request is async, then the queue and its ancestor entities are
 * अक्षरged with the number of sectors of the request, multiplied by
 * the factor below. This throttles the bandwidth क्रम async I/O,
 * w.r.t. to sync I/O, and it is करोne to counter the tendency of async
 * ग_लिखोs to steal I/O throughput to पढ़ोs.
 *
 * The current value of this parameter is the result of a tuning with
 * several hardware and software configurations. We tried to find the
 * lowest value क्रम which ग_लिखोs करो not cause noticeable problems to
 * पढ़ोs. In fact, the lower this parameter, the stabler I/O control,
 * in the following respect.  The lower this parameter is, the less
 * the bandwidth enjoyed by a group decreases
 * - when the group करोes ग_लिखोs, w.r.t. to when it करोes पढ़ोs;
 * - when other groups करो पढ़ोs, w.r.t. to when they करो ग_लिखोs.
 */
अटल स्थिर पूर्णांक bfq_async_अक्षरge_factor = 3;

/* Default समयout values, in jअगरfies, approximating CFQ शेषs. */
स्थिर पूर्णांक bfq_समयout = HZ / 8;

/*
 * Time limit क्रम merging (see comments in bfq_setup_coचालक). Set
 * to the slowest value that, in our tests, proved to be effective in
 * removing false positives, जबतक not causing true positives to miss
 * queue merging.
 *
 * As can be deduced from the low समय limit below, queue merging, अगर
 * successful, happens at the very beginning of the I/O of the involved
 * cooperating processes, as a consequence of the arrival of the very
 * first requests from each coचालक.  After that, there is very
 * little chance to find coचालकs.
 */
अटल स्थिर अचिन्हित दीर्घ bfq_merge_समय_limit = HZ/10;

अटल काष्ठा kmem_cache *bfq_pool;

/* Below this threshold (in ns), we consider thinkसमय immediate. */
#घोषणा BFQ_MIN_TT		(2 * NSEC_PER_MSEC)

/* hw_tag detection: parallel requests threshold and min samples needed. */
#घोषणा BFQ_HW_QUEUE_THRESHOLD	3
#घोषणा BFQ_HW_QUEUE_SAMPLES	32

#घोषणा BFQQ_SEEK_THR		(sector_t)(8 * 100)
#घोषणा BFQQ_SECT_THR_NONROT	(sector_t)(2 * 32)
#घोषणा BFQ_RQ_SEEKY(bfqd, last_pos, rq) \
	(get_sdist(last_pos, rq) >			\
	 BFQQ_SEEK_THR &&				\
	 (!blk_queue_nonrot(bfqd->queue) ||		\
	  blk_rq_sectors(rq) < BFQQ_SECT_THR_NONROT))
#घोषणा BFQQ_CLOSE_THR		(sector_t)(8 * 1024)
#घोषणा BFQQ_SEEKY(bfqq)	(hweight32(bfqq->seek_history) > 19)
/*
 * Sync अक्रमom I/O is likely to be confused with soft real-समय I/O,
 * because it is अक्षरacterized by limited throughput and apparently
 * isochronous arrival pattern. To aव्योम false positives, queues
 * containing only अक्रमom (seeky) I/O are prevented from being tagged
 * as soft real-समय.
 */
#घोषणा BFQQ_TOTALLY_SEEKY(bfqq)	(bfqq->seek_history == -1)

/* Min number of samples required to perक्रमm peak-rate update */
#घोषणा BFQ_RATE_MIN_SAMPLES	32
/* Min observation समय पूर्णांकerval required to perक्रमm a peak-rate update (ns) */
#घोषणा BFQ_RATE_MIN_INTERVAL	(300*NSEC_PER_MSEC)
/* Target observation समय पूर्णांकerval क्रम a peak-rate update (ns) */
#घोषणा BFQ_RATE_REF_INTERVAL	NSEC_PER_SEC

/*
 * Shअगरt used क्रम peak-rate fixed precision calculations.
 * With
 * - the current shअगरt: 16 positions
 * - the current type used to store rate: u32
 * - the current unit of measure क्रम rate: [sectors/usec], or, more precisely,
 *   [(sectors/usec) / 2^BFQ_RATE_SHIFT] to take पूर्णांकo account the shअगरt,
 * the range of rates that can be stored is
 * [1 / 2^BFQ_RATE_SHIFT, 2^(32 - BFQ_RATE_SHIFT)] sectors/usec =
 * [1 / 2^16, 2^16] sectors/usec = [15e-6, 65536] sectors/usec =
 * [15, 65G] sectors/sec
 * Which, assuming a sector size of 512B, corresponds to a range of
 * [7.5K, 33T] B/sec
 */
#घोषणा BFQ_RATE_SHIFT		16

/*
 * When configured क्रम computing the duration of the weight-raising
 * क्रम पूर्णांकeractive queues स्वतःmatically (see the comments at the
 * beginning of this file), BFQ करोes it using the following क्रमmula:
 * duration = (ref_rate / r) * ref_wr_duration,
 * where r is the peak rate of the device, and ref_rate and
 * ref_wr_duration are two reference parameters.  In particular,
 * ref_rate is the peak rate of the reference storage device (see
 * below), and ref_wr_duration is about the maximum समय needed, with
 * BFQ and जबतक पढ़ोing two files in parallel, to load typical large
 * applications on the reference device (see the comments on
 * max_service_from_wr below, क्रम more details on how ref_wr_duration
 * is obtained).  In practice, the slower/faster the device at hand
 * is, the more/less it takes to load applications with respect to the
 * reference device.  Accordingly, the दीर्घer/लघुer BFQ grants
 * weight raising to पूर्णांकeractive applications.
 *
 * BFQ uses two dअगरferent reference pairs (ref_rate, ref_wr_duration),
 * depending on whether the device is rotational or non-rotational.
 *
 * In the following definitions, ref_rate[0] and ref_wr_duration[0]
 * are the reference values क्रम a rotational device, whereas
 * ref_rate[1] and ref_wr_duration[1] are the reference values क्रम a
 * non-rotational device. The reference rates are not the actual peak
 * rates of the devices used as a reference, but slightly lower
 * values. The reason क्रम using slightly lower values is that the
 * peak-rate estimator tends to yield slightly lower values than the
 * actual peak rate (it can yield the actual peak rate only अगर there
 * is only one process करोing I/O, and the process करोes sequential
 * I/O).
 *
 * The reference peak rates are measured in sectors/usec, left-shअगरted
 * by BFQ_RATE_SHIFT.
 */
अटल पूर्णांक ref_rate[2] = अणु14000, 33000पूर्ण;
/*
 * To improve पढ़ोability, a conversion function is used to initialize
 * the following array, which entails that the array can be
 * initialized only in a function.
 */
अटल पूर्णांक ref_wr_duration[2];

/*
 * BFQ uses the above-detailed, समय-based weight-raising mechanism to
 * privilege पूर्णांकeractive tasks. This mechanism is vulnerable to the
 * following false positives: I/O-bound applications that will go on
 * करोing I/O क्रम much दीर्घer than the duration of weight
 * raising. These applications have basically no benefit from being
 * weight-उठाओd at the beginning of their I/O. On the opposite end,
 * जबतक being weight-उठाओd, these applications
 * a) unjustly steal throughput to applications that may actually need
 * low latency;
 * b) make BFQ uselessly perक्रमm device idling; device idling results
 * in loss of device throughput with most flash-based storage, and may
 * increase latencies when used purposelessly.
 *
 * BFQ tries to reduce these problems, by aकरोpting the following
 * countermeasure. To पूर्णांकroduce this countermeasure, we need first to
 * finish explaining how the duration of weight-raising क्रम
 * पूर्णांकeractive tasks is computed.
 *
 * For a bfq_queue deemed as पूर्णांकeractive, the duration of weight
 * raising is dynamically adjusted, as a function of the estimated
 * peak rate of the device, so as to be equal to the समय needed to
 * execute the 'largest' पूर्णांकeractive task we benchmarked so far. By
 * largest task, we mean the task क्रम which each involved process has
 * to करो more I/O than क्रम any of the other tasks we benchmarked. This
 * reference पूर्णांकeractive task is the start-up of LibreOffice Writer,
 * and in this task each process/bfq_queue needs to have at most ~110K
 * sectors transferred.
 *
 * This last piece of inक्रमmation enables BFQ to reduce the actual
 * duration of weight-raising क्रम at least one class of I/O-bound
 * applications: those करोing sequential or quasi-sequential I/O. An
 * example is file copy. In fact, once started, the मुख्य I/O-bound
 * processes of these applications usually consume the above 110K
 * sectors in much less समय than the processes of an application that
 * is starting, because these I/O-bound processes will greedily devote
 * almost all their CPU cycles only to their target,
 * throughput-मित्रly I/O operations. This is even more true अगर BFQ
 * happens to be underestimating the device peak rate, and thus
 * overestimating the duration of weight raising. But, according to
 * our measurements, once transferred 110K sectors, these processes
 * have no right to be weight-उठाओd any दीर्घer.
 *
 * Basing on the last consideration, BFQ ends weight-raising क्रम a
 * bfq_queue अगर the latter happens to have received an amount of
 * service at least equal to the following स्थिरant. The स्थिरant is
 * set to slightly more than 110K, to have a minimum safety margin.
 *
 * This early ending of weight-raising reduces the amount of समय
 * during which पूर्णांकeractive false positives cause the two problems
 * described at the beginning of these comments.
 */
अटल स्थिर अचिन्हित दीर्घ max_service_from_wr = 120000;

#घोषणा RQ_BIC(rq)		icq_to_bic((rq)->elv.priv[0])
#घोषणा RQ_BFQQ(rq)		((rq)->elv.priv[1])

काष्ठा bfq_queue *bic_to_bfqq(काष्ठा bfq_io_cq *bic, bool is_sync)
अणु
	वापस bic->bfqq[is_sync];
पूर्ण

अटल व्योम bfq_put_stable_ref(काष्ठा bfq_queue *bfqq);

व्योम bic_set_bfqq(काष्ठा bfq_io_cq *bic, काष्ठा bfq_queue *bfqq, bool is_sync)
अणु
	/*
	 * If bfqq != शून्य, then a non-stable queue merge between
	 * bic->bfqq and bfqq is happening here. This causes troubles
	 * in the following हाल: bic->bfqq has also been scheduled
	 * क्रम a possible stable merge with bic->stable_merge_bfqq,
	 * and bic->stable_merge_bfqq == bfqq happens to
	 * hold. Troubles occur because bfqq may then undergo a split,
	 * thereby becoming eligible क्रम a stable merge. Yet, अगर
	 * bic->stable_merge_bfqq poपूर्णांकs exactly to bfqq, then bfqq
	 * would be stably merged with itself. To aव्योम this anomaly,
	 * we cancel the stable merge अगर
	 * bic->stable_merge_bfqq == bfqq.
	 */
	bic->bfqq[is_sync] = bfqq;

	अगर (bfqq && bic->stable_merge_bfqq == bfqq) अणु
		/*
		 * Actually, these same inकाष्ठाions are executed also
		 * in bfq_setup_coचालक, in हाल of पात or actual
		 * execution of a stable merge. We could aव्योम
		 * repeating these inकाष्ठाions there too, but अगर we
		 * did so, we would nest even more complनिकासy in this
		 * function.
		 */
		bfq_put_stable_ref(bic->stable_merge_bfqq);

		bic->stable_merge_bfqq = शून्य;
	पूर्ण
पूर्ण

काष्ठा bfq_data *bic_to_bfqd(काष्ठा bfq_io_cq *bic)
अणु
	वापस bic->icq.q->elevator->elevator_data;
पूर्ण

/**
 * icq_to_bic - convert iocontext queue काष्ठाure to bfq_io_cq.
 * @icq: the iocontext queue.
 */
अटल काष्ठा bfq_io_cq *icq_to_bic(काष्ठा io_cq *icq)
अणु
	/* bic->icq is the first member, %शून्य will convert to %शून्य */
	वापस container_of(icq, काष्ठा bfq_io_cq, icq);
पूर्ण

/**
 * bfq_bic_lookup - search पूर्णांकo @ioc a bic associated to @bfqd.
 * @bfqd: the lookup key.
 * @ioc: the io_context of the process करोing I/O.
 * @q: the request queue.
 */
अटल काष्ठा bfq_io_cq *bfq_bic_lookup(काष्ठा bfq_data *bfqd,
					काष्ठा io_context *ioc,
					काष्ठा request_queue *q)
अणु
	अगर (ioc) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा bfq_io_cq *icq;

		spin_lock_irqsave(&q->queue_lock, flags);
		icq = icq_to_bic(ioc_lookup_icq(ioc, q));
		spin_unlock_irqrestore(&q->queue_lock, flags);

		वापस icq;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Scheduler run of queue, अगर there are requests pending and no one in the
 * driver that will restart queueing.
 */
व्योम bfq_schedule_dispatch(काष्ठा bfq_data *bfqd)
अणु
	अगर (bfqd->queued != 0) अणु
		bfq_log(bfqd, "schedule dispatch");
		blk_mq_run_hw_queues(bfqd->queue, true);
	पूर्ण
पूर्ण

#घोषणा bfq_class_idle(bfqq)	((bfqq)->ioprio_class == IOPRIO_CLASS_IDLE)

#घोषणा bfq_sample_valid(samples)	((samples) > 80)

/*
 * Lअगरted from AS - choose which of rq1 and rq2 that is best served now.
 * We choose the request that is बंदr to the head right now.  Distance
 * behind the head is penalized and only allowed to a certain extent.
 */
अटल काष्ठा request *bfq_choose_req(काष्ठा bfq_data *bfqd,
				      काष्ठा request *rq1,
				      काष्ठा request *rq2,
				      sector_t last)
अणु
	sector_t s1, s2, d1 = 0, d2 = 0;
	अचिन्हित दीर्घ back_max;
#घोषणा BFQ_RQ1_WRAP	0x01 /* request 1 wraps */
#घोषणा BFQ_RQ2_WRAP	0x02 /* request 2 wraps */
	अचिन्हित पूर्णांक wrap = 0; /* bit mask: requests behind the disk head? */

	अगर (!rq1 || rq1 == rq2)
		वापस rq2;
	अगर (!rq2)
		वापस rq1;

	अगर (rq_is_sync(rq1) && !rq_is_sync(rq2))
		वापस rq1;
	अन्यथा अगर (rq_is_sync(rq2) && !rq_is_sync(rq1))
		वापस rq2;
	अगर ((rq1->cmd_flags & REQ_META) && !(rq2->cmd_flags & REQ_META))
		वापस rq1;
	अन्यथा अगर ((rq2->cmd_flags & REQ_META) && !(rq1->cmd_flags & REQ_META))
		वापस rq2;

	s1 = blk_rq_pos(rq1);
	s2 = blk_rq_pos(rq2);

	/*
	 * By definition, 1KiB is 2 sectors.
	 */
	back_max = bfqd->bfq_back_max * 2;

	/*
	 * Strict one way elevator _except_ in the हाल where we allow
	 * लघु backward seeks which are biased as twice the cost of a
	 * similar क्रमward seek.
	 */
	अगर (s1 >= last)
		d1 = s1 - last;
	अन्यथा अगर (s1 + back_max >= last)
		d1 = (last - s1) * bfqd->bfq_back_penalty;
	अन्यथा
		wrap |= BFQ_RQ1_WRAP;

	अगर (s2 >= last)
		d2 = s2 - last;
	अन्यथा अगर (s2 + back_max >= last)
		d2 = (last - s2) * bfqd->bfq_back_penalty;
	अन्यथा
		wrap |= BFQ_RQ2_WRAP;

	/* Found required data */

	/*
	 * By करोing चयन() on the bit mask "wrap" we aव्योम having to
	 * check two variables क्रम all permutations: --> faster!
	 */
	चयन (wrap) अणु
	हाल 0: /* common हाल क्रम CFQ: rq1 and rq2 not wrapped */
		अगर (d1 < d2)
			वापस rq1;
		अन्यथा अगर (d2 < d1)
			वापस rq2;

		अगर (s1 >= s2)
			वापस rq1;
		अन्यथा
			वापस rq2;

	हाल BFQ_RQ2_WRAP:
		वापस rq1;
	हाल BFQ_RQ1_WRAP:
		वापस rq2;
	हाल BFQ_RQ1_WRAP|BFQ_RQ2_WRAP: /* both rqs wrapped */
	शेष:
		/*
		 * Since both rqs are wrapped,
		 * start with the one that's further behind head
		 * (--> only *one* back seek required),
		 * since back seek takes more समय than क्रमward.
		 */
		अगर (s1 <= s2)
			वापस rq1;
		अन्यथा
			वापस rq2;
	पूर्ण
पूर्ण

/*
 * Async I/O can easily starve sync I/O (both sync पढ़ोs and sync
 * ग_लिखोs), by consuming all tags. Similarly, storms of sync ग_लिखोs,
 * such as those that sync(2) may trigger, can starve sync पढ़ोs.
 * Limit depths of async I/O and sync ग_लिखोs so as to counter both
 * problems.
 */
अटल व्योम bfq_limit_depth(अचिन्हित पूर्णांक op, काष्ठा blk_mq_alloc_data *data)
अणु
	काष्ठा bfq_data *bfqd = data->q->elevator->elevator_data;

	अगर (op_is_sync(op) && !op_is_ग_लिखो(op))
		वापस;

	data->shallow_depth =
		bfqd->word_depths[!!bfqd->wr_busy_queues][op_is_sync(op)];

	bfq_log(bfqd, "[%s] wr_busy %d sync %d depth %u",
			__func__, bfqd->wr_busy_queues, op_is_sync(op),
			data->shallow_depth);
पूर्ण

अटल काष्ठा bfq_queue *
bfq_rq_pos_tree_lookup(काष्ठा bfq_data *bfqd, काष्ठा rb_root *root,
		     sector_t sector, काष्ठा rb_node **ret_parent,
		     काष्ठा rb_node ***rb_link)
अणु
	काष्ठा rb_node **p, *parent;
	काष्ठा bfq_queue *bfqq = शून्य;

	parent = शून्य;
	p = &root->rb_node;
	जबतक (*p) अणु
		काष्ठा rb_node **n;

		parent = *p;
		bfqq = rb_entry(parent, काष्ठा bfq_queue, pos_node);

		/*
		 * Sort strictly based on sector. Smallest to the left,
		 * largest to the right.
		 */
		अगर (sector > blk_rq_pos(bfqq->next_rq))
			n = &(*p)->rb_right;
		अन्यथा अगर (sector < blk_rq_pos(bfqq->next_rq))
			n = &(*p)->rb_left;
		अन्यथा
			अवरोध;
		p = n;
		bfqq = शून्य;
	पूर्ण

	*ret_parent = parent;
	अगर (rb_link)
		*rb_link = p;

	bfq_log(bfqd, "rq_pos_tree_lookup %llu: returning %d",
		(अचिन्हित दीर्घ दीर्घ)sector,
		bfqq ? bfqq->pid : 0);

	वापस bfqq;
पूर्ण

अटल bool bfq_too_late_क्रम_merging(काष्ठा bfq_queue *bfqq)
अणु
	वापस bfqq->service_from_backlogged > 0 &&
		समय_is_beक्रमe_jअगरfies(bfqq->first_IO_समय +
				       bfq_merge_समय_limit);
पूर्ण

/*
 * The following function is not marked as __cold because it is
 * actually cold, but क्रम the same perक्रमmance goal described in the
 * comments on the likely() at the beginning of
 * bfq_setup_coचालक(). Unexpectedly, to reach an even lower
 * execution समय क्रम the हाल where this function is not invoked, we
 * had to add an unlikely() in each involved अगर().
 */
व्योम __cold
bfq_pos_tree_add_move(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा rb_node **p, *parent;
	काष्ठा bfq_queue *__bfqq;

	अगर (bfqq->pos_root) अणु
		rb_erase(&bfqq->pos_node, bfqq->pos_root);
		bfqq->pos_root = शून्य;
	पूर्ण

	/* oom_bfqq करोes not participate in queue merging */
	अगर (bfqq == &bfqd->oom_bfqq)
		वापस;

	/*
	 * bfqq cannot be merged any दीर्घer (see comments in
	 * bfq_setup_coचालक): no poपूर्णांक in adding bfqq पूर्णांकo the
	 * position tree.
	 */
	अगर (bfq_too_late_क्रम_merging(bfqq))
		वापस;

	अगर (bfq_class_idle(bfqq))
		वापस;
	अगर (!bfqq->next_rq)
		वापस;

	bfqq->pos_root = &bfq_bfqq_to_bfqg(bfqq)->rq_pos_tree;
	__bfqq = bfq_rq_pos_tree_lookup(bfqd, bfqq->pos_root,
			blk_rq_pos(bfqq->next_rq), &parent, &p);
	अगर (!__bfqq) अणु
		rb_link_node(&bfqq->pos_node, parent, p);
		rb_insert_color(&bfqq->pos_node, bfqq->pos_root);
	पूर्ण अन्यथा
		bfqq->pos_root = शून्य;
पूर्ण

/*
 * The following function वापसs false either अगर every active queue
 * must receive the same share of the throughput (symmetric scenario),
 * or, as a special हाल, अगर bfqq must receive a share of the
 * throughput lower than or equal to the share that every other active
 * queue must receive.  If bfqq करोes sync I/O, then these are the only
 * two हालs where bfqq happens to be guaranteed its share of the
 * throughput even अगर I/O dispatching is not plugged when bfqq reमुख्यs
 * temporarily empty (क्रम more details, see the comments in the
 * function bfq_better_to_idle()). For this reason, the वापस value
 * of this function is used to check whether I/O-dispatch plugging can
 * be aव्योमed.
 *
 * The above first हाल (symmetric scenario) occurs when:
 * 1) all active queues have the same weight,
 * 2) all active queues beदीर्घ to the same I/O-priority class,
 * 3) all active groups at the same level in the groups tree have the same
 *    weight,
 * 4) all active groups at the same level in the groups tree have the same
 *    number of children.
 *
 * Unक्रमtunately, keeping the necessary state क्रम evaluating exactly
 * the last two symmetry sub-conditions above would be quite complex
 * and समय consuming. Thereक्रमe this function evaluates, instead,
 * only the following stronger three sub-conditions, क्रम which it is
 * much easier to मुख्यtain the needed state:
 * 1) all active queues have the same weight,
 * 2) all active queues beदीर्घ to the same I/O-priority class,
 * 3) there are no active groups.
 * In particular, the last condition is always true अगर hierarchical
 * support or the cgroups पूर्णांकerface are not enabled, thus no state
 * needs to be मुख्यtained in this हाल.
 */
अटल bool bfq_asymmetric_scenario(काष्ठा bfq_data *bfqd,
				   काष्ठा bfq_queue *bfqq)
अणु
	bool smallest_weight = bfqq &&
		bfqq->weight_counter &&
		bfqq->weight_counter ==
		container_of(
			rb_first_cached(&bfqd->queue_weights_tree),
			काष्ठा bfq_weight_counter,
			weights_node);

	/*
	 * For queue weights to dअगरfer, queue_weights_tree must contain
	 * at least two nodes.
	 */
	bool varied_queue_weights = !smallest_weight &&
		!RB_EMPTY_ROOT(&bfqd->queue_weights_tree.rb_root) &&
		(bfqd->queue_weights_tree.rb_root.rb_node->rb_left ||
		 bfqd->queue_weights_tree.rb_root.rb_node->rb_right);

	bool multiple_classes_busy =
		(bfqd->busy_queues[0] && bfqd->busy_queues[1]) ||
		(bfqd->busy_queues[0] && bfqd->busy_queues[2]) ||
		(bfqd->busy_queues[1] && bfqd->busy_queues[2]);

	वापस varied_queue_weights || multiple_classes_busy
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	       || bfqd->num_groups_with_pending_reqs > 0
#पूर्ण_अगर
		;
पूर्ण

/*
 * If the weight-counter tree passed as input contains no counter क्रम
 * the weight of the input queue, then add that counter; otherwise just
 * increment the existing counter.
 *
 * Note that weight-counter trees contain few nodes in mostly symmetric
 * scenarios. For example, अगर all queues have the same weight, then the
 * weight-counter tree क्रम the queues may contain at most one node.
 * This holds even अगर low_latency is on, because weight-उठाओd queues
 * are not inserted in the tree.
 * In most scenarios, the rate at which nodes are created/destroyed
 * should be low too.
 */
व्योम bfq_weights_tree_add(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			  काष्ठा rb_root_cached *root)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;
	काष्ठा rb_node **new = &(root->rb_root.rb_node), *parent = शून्य;
	bool lefपंचांगost = true;

	/*
	 * Do not insert अगर the queue is alपढ़ोy associated with a
	 * counter, which happens अगर:
	 *   1) a request arrival has caused the queue to become both
	 *      non-weight-उठाओd, and hence change its weight, and
	 *      backlogged; in this respect, each of the two events
	 *      causes an invocation of this function,
	 *   2) this is the invocation of this function caused by the
	 *      second event. This second invocation is actually useless,
	 *      and we handle this fact by निकासing immediately. More
	 *      efficient or clearer solutions might possibly be aकरोpted.
	 */
	अगर (bfqq->weight_counter)
		वापस;

	जबतक (*new) अणु
		काष्ठा bfq_weight_counter *__counter = container_of(*new,
						काष्ठा bfq_weight_counter,
						weights_node);
		parent = *new;

		अगर (entity->weight == __counter->weight) अणु
			bfqq->weight_counter = __counter;
			जाओ inc_counter;
		पूर्ण
		अगर (entity->weight < __counter->weight)
			new = &((*new)->rb_left);
		अन्यथा अणु
			new = &((*new)->rb_right);
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	bfqq->weight_counter = kzalloc(माप(काष्ठा bfq_weight_counter),
				       GFP_ATOMIC);

	/*
	 * In the unlucky event of an allocation failure, we just
	 * निकास. This will cause the weight of queue to not be
	 * considered in bfq_asymmetric_scenario, which, in its turn,
	 * causes the scenario to be deemed wrongly symmetric in हाल
	 * bfqq's weight would have been the only weight making the
	 * scenario asymmetric.  On the bright side, no unbalance will
	 * however occur when bfqq becomes inactive again (the
	 * invocation of this function is triggered by an activation
	 * of queue).  In fact, bfq_weights_tree_हटाओ करोes nothing
	 * अगर !bfqq->weight_counter.
	 */
	अगर (unlikely(!bfqq->weight_counter))
		वापस;

	bfqq->weight_counter->weight = entity->weight;
	rb_link_node(&bfqq->weight_counter->weights_node, parent, new);
	rb_insert_color_cached(&bfqq->weight_counter->weights_node, root,
				lefपंचांगost);

inc_counter:
	bfqq->weight_counter->num_active++;
	bfqq->ref++;
पूर्ण

/*
 * Decrement the weight counter associated with the queue, and, अगर the
 * counter reaches 0, हटाओ the counter from the tree.
 * See the comments to the function bfq_weights_tree_add() क्रम considerations
 * about overhead.
 */
व्योम __bfq_weights_tree_हटाओ(काष्ठा bfq_data *bfqd,
			       काष्ठा bfq_queue *bfqq,
			       काष्ठा rb_root_cached *root)
अणु
	अगर (!bfqq->weight_counter)
		वापस;

	bfqq->weight_counter->num_active--;
	अगर (bfqq->weight_counter->num_active > 0)
		जाओ reset_entity_poपूर्णांकer;

	rb_erase_cached(&bfqq->weight_counter->weights_node, root);
	kमुक्त(bfqq->weight_counter);

reset_entity_poपूर्णांकer:
	bfqq->weight_counter = शून्य;
	bfq_put_queue(bfqq);
पूर्ण

/*
 * Invoke __bfq_weights_tree_हटाओ on bfqq and decrement the number
 * of active groups क्रम each queue's inactive parent entity.
 */
व्योम bfq_weights_tree_हटाओ(काष्ठा bfq_data *bfqd,
			     काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_entity *entity = bfqq->entity.parent;

	क्रम_each_entity(entity) अणु
		काष्ठा bfq_sched_data *sd = entity->my_sched_data;

		अगर (sd->next_in_service || sd->in_service_entity) अणु
			/*
			 * entity is still active, because either
			 * next_in_service or in_service_entity is not
			 * शून्य (see the comments on the definition of
			 * next_in_service क्रम details on why
			 * in_service_entity must be checked too).
			 *
			 * As a consequence, its parent entities are
			 * active as well, and thus this loop must
			 * stop here.
			 */
			अवरोध;
		पूर्ण

		/*
		 * The decrement of num_groups_with_pending_reqs is
		 * not perक्रमmed immediately upon the deactivation of
		 * entity, but it is delayed to when it also happens
		 * that the first leaf descendant bfqq of entity माला_लो
		 * all its pending requests completed. The following
		 * inकाष्ठाions perक्रमm this delayed decrement, अगर
		 * needed. See the comments on
		 * num_groups_with_pending_reqs क्रम details.
		 */
		अगर (entity->in_groups_with_pending_reqs) अणु
			entity->in_groups_with_pending_reqs = false;
			bfqd->num_groups_with_pending_reqs--;
		पूर्ण
	पूर्ण

	/*
	 * Next function is invoked last, because it causes bfqq to be
	 * मुक्तd अगर the following holds: bfqq is not in service and
	 * has no dispatched request. DO NOT use bfqq after the next
	 * function invocation.
	 */
	__bfq_weights_tree_हटाओ(bfqd, bfqq,
				  &bfqd->queue_weights_tree);
पूर्ण

/*
 * Return expired entry, or शून्य to just start from scratch in rbtree.
 */
अटल काष्ठा request *bfq_check_fअगरo(काष्ठा bfq_queue *bfqq,
				      काष्ठा request *last)
अणु
	काष्ठा request *rq;

	अगर (bfq_bfqq_fअगरo_expire(bfqq))
		वापस शून्य;

	bfq_mark_bfqq_fअगरo_expire(bfqq);

	rq = rq_entry_fअगरo(bfqq->fअगरo.next);

	अगर (rq == last || kसमय_get_ns() < rq->fअगरo_समय)
		वापस शून्य;

	bfq_log_bfqq(bfqq->bfqd, bfqq, "check_fifo: returned %p", rq);
	वापस rq;
पूर्ण

अटल काष्ठा request *bfq_find_next_rq(काष्ठा bfq_data *bfqd,
					काष्ठा bfq_queue *bfqq,
					काष्ठा request *last)
अणु
	काष्ठा rb_node *rbnext = rb_next(&last->rb_node);
	काष्ठा rb_node *rbprev = rb_prev(&last->rb_node);
	काष्ठा request *next, *prev = शून्य;

	/* Follow expired path, अन्यथा get first next available. */
	next = bfq_check_fअगरo(bfqq, last);
	अगर (next)
		वापस next;

	अगर (rbprev)
		prev = rb_entry_rq(rbprev);

	अगर (rbnext)
		next = rb_entry_rq(rbnext);
	अन्यथा अणु
		rbnext = rb_first(&bfqq->sort_list);
		अगर (rbnext && rbnext != &last->rb_node)
			next = rb_entry_rq(rbnext);
	पूर्ण

	वापस bfq_choose_req(bfqd, next, prev, blk_rq_pos(last));
पूर्ण

/* see the definition of bfq_async_अक्षरge_factor क्रम details */
अटल अचिन्हित दीर्घ bfq_serv_to_अक्षरge(काष्ठा request *rq,
					काष्ठा bfq_queue *bfqq)
अणु
	अगर (bfq_bfqq_sync(bfqq) || bfqq->wr_coeff > 1 ||
	    bfq_asymmetric_scenario(bfqq->bfqd, bfqq))
		वापस blk_rq_sectors(rq);

	वापस blk_rq_sectors(rq) * bfq_async_अक्षरge_factor;
पूर्ण

/**
 * bfq_updated_next_req - update the queue after a new next_rq selection.
 * @bfqd: the device data the queue beदीर्घs to.
 * @bfqq: the queue to update.
 *
 * If the first request of a queue changes we make sure that the queue
 * has enough budget to serve at least its first request (अगर the
 * request has grown).  We करो this because अगर the queue has not enough
 * budget क्रम its first request, it has to go through two dispatch
 * rounds to actually get it dispatched.
 */
अटल व्योम bfq_updated_next_req(काष्ठा bfq_data *bfqd,
				 काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;
	काष्ठा request *next_rq = bfqq->next_rq;
	अचिन्हित दीर्घ new_budget;

	अगर (!next_rq)
		वापस;

	अगर (bfqq == bfqd->in_service_queue)
		/*
		 * In order not to अवरोध guarantees, budमाला_लो cannot be
		 * changed after an entity has been selected.
		 */
		वापस;

	new_budget = max_t(अचिन्हित दीर्घ,
			   max_t(अचिन्हित दीर्घ, bfqq->max_budget,
				 bfq_serv_to_अक्षरge(next_rq, bfqq)),
			   entity->service);
	अगर (entity->budget != new_budget) अणु
		entity->budget = new_budget;
		bfq_log_bfqq(bfqd, bfqq, "updated next rq: new budget %lu",
					 new_budget);
		bfq_requeue_bfqq(bfqd, bfqq, false);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक bfq_wr_duration(काष्ठा bfq_data *bfqd)
अणु
	u64 dur;

	अगर (bfqd->bfq_wr_max_समय > 0)
		वापस bfqd->bfq_wr_max_समय;

	dur = bfqd->rate_dur_prod;
	करो_भाग(dur, bfqd->peak_rate);

	/*
	 * Limit duration between 3 and 25 seconds. The upper limit
	 * has been conservatively set after the following worst हाल:
	 * on a QEMU/KVM भव machine
	 * - running in a slow PC
	 * - with a भव disk stacked on a slow low-end 5400rpm HDD
	 * - serving a heavy I/O workload, such as the sequential पढ़ोing
	 *   of several files
	 * mplayer took 23 seconds to start, अगर स्थिरantly weight-उठाओd.
	 *
	 * As क्रम higher values than that accommodating the above bad
	 * scenario, tests show that higher values would often yield
	 * the opposite of the desired result, i.e., would worsen
	 * responsiveness by allowing non-पूर्णांकeractive applications to
	 * preserve weight raising क्रम too दीर्घ.
	 *
	 * On the other end, lower values than 3 seconds make it
	 * dअगरficult क्रम most पूर्णांकeractive tasks to complete their jobs
	 * beक्रमe weight-raising finishes.
	 */
	वापस clamp_val(dur, msecs_to_jअगरfies(3000), msecs_to_jअगरfies(25000));
पूर्ण

/* चयन back from soft real-समय to पूर्णांकeractive weight raising */
अटल व्योम चयन_back_to_पूर्णांकeractive_wr(काष्ठा bfq_queue *bfqq,
					  काष्ठा bfq_data *bfqd)
अणु
	bfqq->wr_coeff = bfqd->bfq_wr_coeff;
	bfqq->wr_cur_max_समय = bfq_wr_duration(bfqd);
	bfqq->last_wr_start_finish = bfqq->wr_start_at_चयन_to_srt;
पूर्ण

अटल व्योम
bfq_bfqq_resume_state(काष्ठा bfq_queue *bfqq, काष्ठा bfq_data *bfqd,
		      काष्ठा bfq_io_cq *bic, bool bfq_alपढ़ोy_existing)
अणु
	अचिन्हित पूर्णांक old_wr_coeff = 1;
	bool busy = bfq_alपढ़ोy_existing && bfq_bfqq_busy(bfqq);

	अगर (bic->saved_has_लघु_tसमय)
		bfq_mark_bfqq_has_लघु_tसमय(bfqq);
	अन्यथा
		bfq_clear_bfqq_has_लघु_tसमय(bfqq);

	अगर (bic->saved_IO_bound)
		bfq_mark_bfqq_IO_bound(bfqq);
	अन्यथा
		bfq_clear_bfqq_IO_bound(bfqq);

	bfqq->last_serv_समय_ns = bic->saved_last_serv_समय_ns;
	bfqq->inject_limit = bic->saved_inject_limit;
	bfqq->decrease_समय_jअगर = bic->saved_decrease_समय_jअगर;

	bfqq->entity.new_weight = bic->saved_weight;
	bfqq->tसमय = bic->saved_tसमय;
	bfqq->io_start_समय = bic->saved_io_start_समय;
	bfqq->tot_idle_समय = bic->saved_tot_idle_समय;
	/*
	 * Restore weight coefficient only अगर low_latency is on
	 */
	अगर (bfqd->low_latency) अणु
		old_wr_coeff = bfqq->wr_coeff;
		bfqq->wr_coeff = bic->saved_wr_coeff;
	पूर्ण
	bfqq->service_from_wr = bic->saved_service_from_wr;
	bfqq->wr_start_at_चयन_to_srt = bic->saved_wr_start_at_चयन_to_srt;
	bfqq->last_wr_start_finish = bic->saved_last_wr_start_finish;
	bfqq->wr_cur_max_समय = bic->saved_wr_cur_max_समय;

	अगर (bfqq->wr_coeff > 1 && (bfq_bfqq_in_large_burst(bfqq) ||
	    समय_is_beक्रमe_jअगरfies(bfqq->last_wr_start_finish +
				   bfqq->wr_cur_max_समय))) अणु
		अगर (bfqq->wr_cur_max_समय == bfqd->bfq_wr_rt_max_समय &&
		    !bfq_bfqq_in_large_burst(bfqq) &&
		    समय_is_after_eq_jअगरfies(bfqq->wr_start_at_चयन_to_srt +
					     bfq_wr_duration(bfqd))) अणु
			चयन_back_to_पूर्णांकeractive_wr(bfqq, bfqd);
		पूर्ण अन्यथा अणु
			bfqq->wr_coeff = 1;
			bfq_log_bfqq(bfqq->bfqd, bfqq,
				     "resume state: switching off wr");
		पूर्ण
	पूर्ण

	/* make sure weight will be updated, however we got here */
	bfqq->entity.prio_changed = 1;

	अगर (likely(!busy))
		वापस;

	अगर (old_wr_coeff == 1 && bfqq->wr_coeff > 1)
		bfqd->wr_busy_queues++;
	अन्यथा अगर (old_wr_coeff > 1 && bfqq->wr_coeff == 1)
		bfqd->wr_busy_queues--;
पूर्ण

अटल पूर्णांक bfqq_process_refs(काष्ठा bfq_queue *bfqq)
अणु
	वापस bfqq->ref - bfqq->allocated - bfqq->entity.on_st_or_in_serv -
		(bfqq->weight_counter != शून्य) - bfqq->stable_ref;
पूर्ण

/* Empty burst list and add just bfqq (see comments on bfq_handle_burst) */
अटल व्योम bfq_reset_burst_list(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_queue *item;
	काष्ठा hlist_node *n;

	hlist_क्रम_each_entry_safe(item, n, &bfqd->burst_list, burst_list_node)
		hlist_del_init(&item->burst_list_node);

	/*
	 * Start the creation of a new burst list only अगर there is no
	 * active queue. See comments on the conditional invocation of
	 * bfq_handle_burst().
	 */
	अगर (bfq_tot_busy_queues(bfqd) == 0) अणु
		hlist_add_head(&bfqq->burst_list_node, &bfqd->burst_list);
		bfqd->burst_size = 1;
	पूर्ण अन्यथा
		bfqd->burst_size = 0;

	bfqd->burst_parent_entity = bfqq->entity.parent;
पूर्ण

/* Add bfqq to the list of queues in current burst (see bfq_handle_burst) */
अटल व्योम bfq_add_to_burst(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	/* Increment burst size to take पूर्णांकo account also bfqq */
	bfqd->burst_size++;

	अगर (bfqd->burst_size == bfqd->bfq_large_burst_thresh) अणु
		काष्ठा bfq_queue *pos, *bfqq_item;
		काष्ठा hlist_node *n;

		/*
		 * Enough queues have been activated लघुly after each
		 * other to consider this burst as large.
		 */
		bfqd->large_burst = true;

		/*
		 * We can now mark all queues in the burst list as
		 * beदीर्घing to a large burst.
		 */
		hlist_क्रम_each_entry(bfqq_item, &bfqd->burst_list,
				     burst_list_node)
			bfq_mark_bfqq_in_large_burst(bfqq_item);
		bfq_mark_bfqq_in_large_burst(bfqq);

		/*
		 * From now on, and until the current burst finishes, any
		 * new queue being activated लघुly after the last queue
		 * was inserted in the burst can be immediately marked as
		 * beदीर्घing to a large burst. So the burst list is not
		 * needed any more. Remove it.
		 */
		hlist_क्रम_each_entry_safe(pos, n, &bfqd->burst_list,
					  burst_list_node)
			hlist_del_init(&pos->burst_list_node);
	पूर्ण अन्यथा /*
		* Burst not yet large: add bfqq to the burst list. Do
		* not increment the ref counter क्रम bfqq, because bfqq
		* is हटाओd from the burst list beक्रमe मुक्तing bfqq
		* in put_queue.
		*/
		hlist_add_head(&bfqq->burst_list_node, &bfqd->burst_list);
पूर्ण

/*
 * If many queues beदीर्घing to the same group happen to be created
 * लघुly after each other, then the processes associated with these
 * queues have typically a common goal. In particular, bursts of queue
 * creations are usually caused by services or applications that spawn
 * many parallel thपढ़ोs/processes. Examples are प्रणालीd during boot,
 * or git grep. To help these processes get their job करोne as soon as
 * possible, it is usually better to not grant either weight-raising
 * or device idling to their queues, unless these queues must be
 * रक्षित from the I/O flowing through other active queues.
 *
 * In this comment we describe, firstly, the reasons why this fact
 * holds, and, secondly, the next function, which implements the मुख्य
 * steps needed to properly mark these queues so that they can then be
 * treated in a dअगरferent way.
 *
 * The above services or applications benefit mostly from a high
 * throughput: the quicker the requests of the activated queues are
 * cumulatively served, the sooner the target job of these queues माला_लो
 * completed. As a consequence, weight-raising any of these queues,
 * which also implies idling the device क्रम it, is almost always
 * counterproductive, unless there are other active queues to isolate
 * these new queues from. If there no other active queues, then
 * weight-raising these new queues just lowers throughput in most
 * हालs.
 *
 * On the other hand, a burst of queue creations may be caused also by
 * the start of an application that करोes not consist of a lot of
 * parallel I/O-bound thपढ़ोs. In fact, with a complex application,
 * several लघु processes may need to be executed to start-up the
 * application. In this respect, to start an application as quickly as
 * possible, the best thing to करो is in any हाल to privilege the I/O
 * related to the application with respect to all other
 * I/O. Thereक्रमe, the best strategy to start as quickly as possible
 * an application that causes a burst of queue creations is to
 * weight-उठाओ all the queues created during the burst. This is the
 * exact opposite of the best strategy क्रम the other type of bursts.
 *
 * In the end, to take the best action क्रम each of the two हालs, the
 * two types of bursts need to be distinguished. Fortunately, this
 * seems relatively easy, by looking at the sizes of the bursts. In
 * particular, we found a threshold such that only bursts with a
 * larger size than that threshold are apparently caused by
 * services or commands such as प्रणालीd or git grep. For brevity,
 * hereafter we call just 'large' these bursts. BFQ *करोes not*
 * weight-उठाओ queues whose creation occurs in a large burst. In
 * addition, क्रम each of these queues BFQ perक्रमms or करोes not perक्रमm
 * idling depending on which choice boosts the throughput more. The
 * exact choice depends on the device and request pattern at
 * hand.
 *
 * Unक्रमtunately, false positives may occur जबतक an पूर्णांकeractive task
 * is starting (e.g., an application is being started). The
 * consequence is that the queues associated with the task करो not
 * enjoy weight raising as expected. Fortunately these false positives
 * are very rare. They typically occur अगर some service happens to
 * start करोing I/O exactly when the पूर्णांकeractive task starts.
 *
 * Turning back to the next function, it is invoked only अगर there are
 * no active queues (apart from active queues that would beदीर्घ to the
 * same, possible burst bfqq would beदीर्घ to), and it implements all
 * the steps needed to detect the occurrence of a large burst and to
 * properly mark all the queues beदीर्घing to it (so that they can then
 * be treated in a dअगरferent way). This goal is achieved by
 * मुख्यtaining a "burst list" that holds, temporarily, the queues that
 * beदीर्घ to the burst in progress. The list is then used to mark
 * these queues as beदीर्घing to a large burst अगर the burst करोes become
 * large. The मुख्य steps are the following.
 *
 * . when the very first queue is created, the queue is inserted पूर्णांकo the
 *   list (as it could be the first queue in a possible burst)
 *
 * . अगर the current burst has not yet become large, and a queue Q that करोes
 *   not yet beदीर्घ to the burst is activated लघुly after the last समय
 *   at which a new queue entered the burst list, then the function appends
 *   Q to the burst list
 *
 * . अगर, as a consequence of the previous step, the burst size reaches
 *   the large-burst threshold, then
 *
 *     . all the queues in the burst list are marked as beदीर्घing to a
 *       large burst
 *
 *     . the burst list is deleted; in fact, the burst list alपढ़ोy served
 *       its purpose (keeping temporarily track of the queues in a burst,
 *       so as to be able to mark them as beदीर्घing to a large burst in the
 *       previous sub-step), and now is not needed any more
 *
 *     . the device enters a large-burst mode
 *
 * . अगर a queue Q that करोes not beदीर्घ to the burst is created जबतक
 *   the device is in large-burst mode and लघुly after the last समय
 *   at which a queue either entered the burst list or was marked as
 *   beदीर्घing to the current large burst, then Q is immediately marked
 *   as beदीर्घing to a large burst.
 *
 * . अगर a queue Q that करोes not beदीर्घ to the burst is created a जबतक
 *   later, i.e., not लघुly after, than the last समय at which a queue
 *   either entered the burst list or was marked as beदीर्घing to the
 *   current large burst, then the current burst is deemed as finished and:
 *
 *        . the large-burst mode is reset अगर set
 *
 *        . the burst list is emptied
 *
 *        . Q is inserted in the burst list, as Q may be the first queue
 *          in a possible new burst (then the burst list contains just Q
 *          after this step).
 */
अटल व्योम bfq_handle_burst(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	/*
	 * If bfqq is alपढ़ोy in the burst list or is part of a large
	 * burst, or finally has just been split, then there is
	 * nothing अन्यथा to करो.
	 */
	अगर (!hlist_unhashed(&bfqq->burst_list_node) ||
	    bfq_bfqq_in_large_burst(bfqq) ||
	    समय_is_after_eq_jअगरfies(bfqq->split_समय +
				     msecs_to_jअगरfies(10)))
		वापस;

	/*
	 * If bfqq's creation happens late enough, or bfqq beदीर्घs to
	 * a dअगरferent group than the burst group, then the current
	 * burst is finished, and related data काष्ठाures must be
	 * reset.
	 *
	 * In this respect, consider the special हाल where bfqq is
	 * the very first queue created after BFQ is selected क्रम this
	 * device. In this हाल, last_ins_in_burst and
	 * burst_parent_entity are not yet signअगरicant when we get
	 * here. But it is easy to verअगरy that, whether or not the
	 * following condition is true, bfqq will end up being
	 * inserted पूर्णांकo the burst list. In particular the list will
	 * happen to contain only bfqq. And this is exactly what has
	 * to happen, as bfqq may be the first queue of the first
	 * burst.
	 */
	अगर (समय_is_beक्रमe_jअगरfies(bfqd->last_ins_in_burst +
	    bfqd->bfq_burst_पूर्णांकerval) ||
	    bfqq->entity.parent != bfqd->burst_parent_entity) अणु
		bfqd->large_burst = false;
		bfq_reset_burst_list(bfqd, bfqq);
		जाओ end;
	पूर्ण

	/*
	 * If we get here, then bfqq is being activated लघुly after the
	 * last queue. So, अगर the current burst is also large, we can mark
	 * bfqq as beदीर्घing to this large burst immediately.
	 */
	अगर (bfqd->large_burst) अणु
		bfq_mark_bfqq_in_large_burst(bfqq);
		जाओ end;
	पूर्ण

	/*
	 * If we get here, then a large-burst state has not yet been
	 * reached, but bfqq is being activated लघुly after the last
	 * queue. Then we add bfqq to the burst.
	 */
	bfq_add_to_burst(bfqd, bfqq);
end:
	/*
	 * At this poपूर्णांक, bfqq either has been added to the current
	 * burst or has caused the current burst to terminate and a
	 * possible new burst to start. In particular, in the second
	 * हाल, bfqq has become the first queue in the possible new
	 * burst.  In both हालs last_ins_in_burst needs to be moved
	 * क्रमward.
	 */
	bfqd->last_ins_in_burst = jअगरfies;
पूर्ण

अटल पूर्णांक bfq_bfqq_budget_left(काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;

	वापस entity->budget - entity->service;
पूर्ण

/*
 * If enough samples have been computed, वापस the current max budget
 * stored in bfqd, which is dynamically updated according to the
 * estimated disk peak rate; otherwise वापस the शेष max budget
 */
अटल पूर्णांक bfq_max_budget(काष्ठा bfq_data *bfqd)
अणु
	अगर (bfqd->budमाला_लो_asचिन्हित < bfq_stats_min_budमाला_लो)
		वापस bfq_शेष_max_budget;
	अन्यथा
		वापस bfqd->bfq_max_budget;
पूर्ण

/*
 * Return min budget, which is a fraction of the current or शेष
 * max budget (trying with 1/32)
 */
अटल पूर्णांक bfq_min_budget(काष्ठा bfq_data *bfqd)
अणु
	अगर (bfqd->budमाला_लो_asचिन्हित < bfq_stats_min_budमाला_लो)
		वापस bfq_शेष_max_budget / 32;
	अन्यथा
		वापस bfqd->bfq_max_budget / 32;
पूर्ण

/*
 * The next function, invoked after the input queue bfqq चयनes from
 * idle to busy, updates the budget of bfqq. The function also tells
 * whether the in-service queue should be expired, by वापसing
 * true. The purpose of expiring the in-service queue is to give bfqq
 * the chance to possibly preempt the in-service queue, and the reason
 * क्रम preempting the in-service queue is to achieve one of the two
 * goals below.
 *
 * 1. Guarantee to bfqq its reserved bandwidth even अगर bfqq has
 * expired because it has reमुख्यed idle. In particular, bfqq may have
 * expired क्रम one of the following two reasons:
 *
 * - BFQQE_NO_MORE_REQUESTS bfqq did not enjoy any device idling
 *   and did not make it to issue a new request beक्रमe its last
 *   request was served;
 *
 * - BFQQE_TOO_IDLE bfqq did enjoy device idling, but did not issue
 *   a new request beक्रमe the expiration of the idling-समय.
 *
 * Even अगर bfqq has expired क्रम one of the above reasons, the process
 * associated with the queue may be however issuing requests greedily,
 * and thus be sensitive to the bandwidth it receives (bfqq may have
 * reमुख्यed idle क्रम other reasons: CPU high load, bfqq not enjoying
 * idling, I/O throttling somewhere in the path from the process to
 * the I/O scheduler, ...). But अगर, after every expiration क्रम one of
 * the above two reasons, bfqq has to रुको क्रम the service of at least
 * one full budget of another queue beक्रमe being served again, then
 * bfqq is likely to get a much lower bandwidth or resource समय than
 * its reserved ones. To address this issue, two countermeasures need
 * to be taken.
 *
 * First, the budget and the बारtamps of bfqq need to be updated in
 * a special way on bfqq reactivation: they need to be updated as अगर
 * bfqq did not reमुख्य idle and did not expire. In fact, अगर they are
 * computed as अगर bfqq expired and reमुख्यed idle until reactivation,
 * then the process associated with bfqq is treated as अगर, instead of
 * being greedy, it stopped issuing requests when bfqq reमुख्यed idle,
 * and restarts issuing requests only on this reactivation. In other
 * words, the scheduler करोes not help the process recover the "service
 * hole" between bfqq expiration and reactivation. As a consequence,
 * the process receives a lower bandwidth than its reserved one. In
 * contrast, to recover this hole, the budget must be updated as अगर
 * bfqq was not expired at all beक्रमe this reactivation, i.e., it must
 * be set to the value of the reमुख्यing budget when bfqq was
 * expired. Aदीर्घ the same line, बारtamps need to be asचिन्हित the
 * value they had the last समय bfqq was selected क्रम service, i.e.,
 * beक्रमe last expiration. Thus बारtamps need to be back-shअगरted
 * with respect to their normal computation (see [1] क्रम more details
 * on this tricky aspect).
 *
 * Secondly, to allow the process to recover the hole, the in-service
 * queue must be expired too, to give bfqq the chance to preempt it
 * immediately. In fact, अगर bfqq has to रुको क्रम a full budget of the
 * in-service queue to be completed, then it may become impossible to
 * let the process recover the hole, even अगर the back-shअगरted
 * बारtamps of bfqq are lower than those of the in-service queue. If
 * this happens क्रम most or all of the holes, then the process may not
 * receive its reserved bandwidth. In this respect, it is worth noting
 * that, being the service of outstanding requests unpreemptible, a
 * little fraction of the holes may however be unrecoverable, thereby
 * causing a little loss of bandwidth.
 *
 * The last important poपूर्णांक is detecting whether bfqq करोes need this
 * bandwidth recovery. In this respect, the next function deems the
 * process associated with bfqq greedy, and thus allows it to recover
 * the hole, अगर: 1) the process is रुकोing क्रम the arrival of a new
 * request (which implies that bfqq expired क्रम one of the above two
 * reasons), and 2) such a request has arrived soon. The first
 * condition is controlled through the flag non_blocking_रुको_rq,
 * जबतक the second through the flag arrived_in_समय. If both
 * conditions hold, then the function computes the budget in the
 * above-described special way, and संकेतs that the in-service queue
 * should be expired. Timestamp back-shअगरting is करोne later in
 * __bfq_activate_entity.
 *
 * 2. Reduce latency. Even अगर बारtamps are not backshअगरted to let
 * the process associated with bfqq recover a service hole, bfqq may
 * however happen to have, after being (re)activated, a lower finish
 * बारtamp than the in-service queue.	 That is, the next budget of
 * bfqq may have to be completed beक्रमe the one of the in-service
 * queue. If this is the हाल, then preempting the in-service queue
 * allows this goal to be achieved, apart from the unpreemptible,
 * outstanding requests mentioned above.
 *
 * Unक्रमtunately, regardless of which of the above two goals one wants
 * to achieve, service trees need first to be updated to know whether
 * the in-service queue must be preempted. To have service trees
 * correctly updated, the in-service queue must be expired and
 * rescheduled, and bfqq must be scheduled too. This is one of the
 * most costly operations (in future versions, the scheduling
 * mechanism may be re-deचिन्हित in such a way to make it possible to
 * know whether preemption is needed without needing to update service
 * trees). In addition, queue preemptions almost always cause अक्रमom
 * I/O, which may in turn cause loss of throughput. Finally, there may
 * even be no in-service queue when the next function is invoked (so,
 * no queue to compare बारtamps with). Because of these facts, the
 * next function aकरोpts the following simple scheme to aव्योम costly
 * operations, too frequent preemptions and too many dependencies on
 * the state of the scheduler: it requests the expiration of the
 * in-service queue (unconditionally) only क्रम queues that need to
 * recover a hole. Then it delegates to other parts of the code the
 * responsibility of handling the above हाल 2.
 */
अटल bool bfq_bfqq_update_budg_क्रम_activation(काष्ठा bfq_data *bfqd,
						काष्ठा bfq_queue *bfqq,
						bool arrived_in_समय)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;

	/*
	 * In the next compound condition, we check also whether there
	 * is some budget left, because otherwise there is no poपूर्णांक in
	 * trying to go on serving bfqq with this same budget: bfqq
	 * would be expired immediately after being selected क्रम
	 * service. This would only cause useless overhead.
	 */
	अगर (bfq_bfqq_non_blocking_रुको_rq(bfqq) && arrived_in_समय &&
	    bfq_bfqq_budget_left(bfqq) > 0) अणु
		/*
		 * We करो not clear the flag non_blocking_रुको_rq here, as
		 * the latter is used in bfq_activate_bfqq to संकेत
		 * that बारtamps need to be back-shअगरted (and is
		 * cleared right after).
		 */

		/*
		 * In next assignment we rely on that either
		 * entity->service or entity->budget are not updated
		 * on expiration अगर bfqq is empty (see
		 * __bfq_bfqq_recalc_budget). Thus both quantities
		 * reमुख्य unchanged after such an expiration, and the
		 * following statement thereक्रमe assigns to
		 * entity->budget the reमुख्यing budget on such an
		 * expiration.
		 */
		entity->budget = min_t(अचिन्हित दीर्घ,
				       bfq_bfqq_budget_left(bfqq),
				       bfqq->max_budget);

		/*
		 * At this poपूर्णांक, we have used entity->service to get
		 * the budget left (needed क्रम updating
		 * entity->budget). Thus we finally can, and have to,
		 * reset entity->service. The latter must be reset
		 * because bfqq would otherwise be अक्षरged again क्रम
		 * the service it has received during its previous
		 * service slot(s).
		 */
		entity->service = 0;

		वापस true;
	पूर्ण

	/*
	 * We can finally complete expiration, by setting service to 0.
	 */
	entity->service = 0;
	entity->budget = max_t(अचिन्हित दीर्घ, bfqq->max_budget,
			       bfq_serv_to_अक्षरge(bfqq->next_rq, bfqq));
	bfq_clear_bfqq_non_blocking_रुको_rq(bfqq);
	वापस false;
पूर्ण

/*
 * Return the farthest past समय instant according to jअगरfies
 * macros.
 */
अटल अचिन्हित दीर्घ bfq_smallest_from_now(व्योम)
अणु
	वापस jअगरfies - MAX_JIFFY_OFFSET;
पूर्ण

अटल व्योम bfq_update_bfqq_wr_on_rq_arrival(काष्ठा bfq_data *bfqd,
					     काष्ठा bfq_queue *bfqq,
					     अचिन्हित पूर्णांक old_wr_coeff,
					     bool wr_or_deserves_wr,
					     bool पूर्णांकeractive,
					     bool in_burst,
					     bool soft_rt)
अणु
	अगर (old_wr_coeff == 1 && wr_or_deserves_wr) अणु
		/* start a weight-raising period */
		अगर (पूर्णांकeractive) अणु
			bfqq->service_from_wr = 0;
			bfqq->wr_coeff = bfqd->bfq_wr_coeff;
			bfqq->wr_cur_max_समय = bfq_wr_duration(bfqd);
		पूर्ण अन्यथा अणु
			/*
			 * No पूर्णांकeractive weight raising in progress
			 * here: assign minus infinity to
			 * wr_start_at_चयन_to_srt, to make sure
			 * that, at the end of the soft-real-समय
			 * weight raising periods that is starting
			 * now, no पूर्णांकeractive weight-raising period
			 * may be wrongly considered as still in
			 * progress (and thus actually started by
			 * mistake).
			 */
			bfqq->wr_start_at_चयन_to_srt =
				bfq_smallest_from_now();
			bfqq->wr_coeff = bfqd->bfq_wr_coeff *
				BFQ_SOFTRT_WEIGHT_FACTOR;
			bfqq->wr_cur_max_समय =
				bfqd->bfq_wr_rt_max_समय;
		पूर्ण

		/*
		 * If needed, further reduce budget to make sure it is
		 * बंद to bfqq's backlog, so as to reduce the
		 * scheduling-error component due to a too large
		 * budget. Do not care about throughput consequences,
		 * but only about latency. Finally, करो not assign a
		 * too small budget either, to aव्योम increasing
		 * latency by causing too frequent expirations.
		 */
		bfqq->entity.budget = min_t(अचिन्हित दीर्घ,
					    bfqq->entity.budget,
					    2 * bfq_min_budget(bfqd));
	पूर्ण अन्यथा अगर (old_wr_coeff > 1) अणु
		अगर (पूर्णांकeractive) अणु /* update wr coeff and duration */
			bfqq->wr_coeff = bfqd->bfq_wr_coeff;
			bfqq->wr_cur_max_समय = bfq_wr_duration(bfqd);
		पूर्ण अन्यथा अगर (in_burst)
			bfqq->wr_coeff = 1;
		अन्यथा अगर (soft_rt) अणु
			/*
			 * The application is now or still meeting the
			 * requirements क्रम being deemed soft rt.  We
			 * can then correctly and safely (re)अक्षरge
			 * the weight-raising duration क्रम the
			 * application with the weight-raising
			 * duration क्रम soft rt applications.
			 *
			 * In particular, करोing this reअक्षरge now, i.e.,
			 * beक्रमe the weight-raising period क्रम the
			 * application finishes, reduces the probability
			 * of the following negative scenario:
			 * 1) the weight of a soft rt application is
			 *    उठाओd at startup (as क्रम any newly
			 *    created application),
			 * 2) since the application is not पूर्णांकeractive,
			 *    at a certain समय weight-raising is
			 *    stopped क्रम the application,
			 * 3) at that समय the application happens to
			 *    still have pending requests, and hence
			 *    is destined to not have a chance to be
			 *    deemed soft rt beक्रमe these requests are
			 *    completed (see the comments to the
			 *    function bfq_bfqq_softrt_next_start()
			 *    क्रम details on soft rt detection),
			 * 4) these pending requests experience a high
			 *    latency because the application is not
			 *    weight-उठाओd जबतक they are pending.
			 */
			अगर (bfqq->wr_cur_max_समय !=
				bfqd->bfq_wr_rt_max_समय) अणु
				bfqq->wr_start_at_चयन_to_srt =
					bfqq->last_wr_start_finish;

				bfqq->wr_cur_max_समय =
					bfqd->bfq_wr_rt_max_समय;
				bfqq->wr_coeff = bfqd->bfq_wr_coeff *
					BFQ_SOFTRT_WEIGHT_FACTOR;
			पूर्ण
			bfqq->last_wr_start_finish = jअगरfies;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool bfq_bfqq_idle_क्रम_दीर्घ_समय(काष्ठा bfq_data *bfqd,
					काष्ठा bfq_queue *bfqq)
अणु
	वापस bfqq->dispatched == 0 &&
		समय_is_beक्रमe_jअगरfies(
			bfqq->budget_समयout +
			bfqd->bfq_wr_min_idle_समय);
पूर्ण


/*
 * Return true अगर bfqq is in a higher priority class, or has a higher
 * weight than the in-service queue.
 */
अटल bool bfq_bfqq_higher_class_or_weight(काष्ठा bfq_queue *bfqq,
					    काष्ठा bfq_queue *in_serv_bfqq)
अणु
	पूर्णांक bfqq_weight, in_serv_weight;

	अगर (bfqq->ioprio_class < in_serv_bfqq->ioprio_class)
		वापस true;

	अगर (in_serv_bfqq->entity.parent == bfqq->entity.parent) अणु
		bfqq_weight = bfqq->entity.weight;
		in_serv_weight = in_serv_bfqq->entity.weight;
	पूर्ण अन्यथा अणु
		अगर (bfqq->entity.parent)
			bfqq_weight = bfqq->entity.parent->weight;
		अन्यथा
			bfqq_weight = bfqq->entity.weight;
		अगर (in_serv_bfqq->entity.parent)
			in_serv_weight = in_serv_bfqq->entity.parent->weight;
		अन्यथा
			in_serv_weight = in_serv_bfqq->entity.weight;
	पूर्ण

	वापस bfqq_weight > in_serv_weight;
पूर्ण

अटल bool bfq_better_to_idle(काष्ठा bfq_queue *bfqq);

अटल व्योम bfq_bfqq_handle_idle_busy_चयन(काष्ठा bfq_data *bfqd,
					     काष्ठा bfq_queue *bfqq,
					     पूर्णांक old_wr_coeff,
					     काष्ठा request *rq,
					     bool *पूर्णांकeractive)
अणु
	bool soft_rt, in_burst,	wr_or_deserves_wr,
		bfqq_wants_to_preempt,
		idle_क्रम_दीर्घ_समय = bfq_bfqq_idle_क्रम_दीर्घ_समय(bfqd, bfqq),
		/*
		 * See the comments on
		 * bfq_bfqq_update_budg_क्रम_activation क्रम
		 * details on the usage of the next variable.
		 */
		arrived_in_समय =  kसमय_get_ns() <=
			bfqq->tसमय.last_end_request +
			bfqd->bfq_slice_idle * 3;


	/*
	 * bfqq deserves to be weight-उठाओd अगर:
	 * - it is sync,
	 * - it करोes not beदीर्घ to a large burst,
	 * - it has been idle क्रम enough समय or is soft real-समय,
	 * - is linked to a bfq_io_cq (it is not shared in any sense),
	 * - has a शेष weight (otherwise we assume the user wanted
	 *   to control its weight explicitly)
	 */
	in_burst = bfq_bfqq_in_large_burst(bfqq);
	soft_rt = bfqd->bfq_wr_max_softrt_rate > 0 &&
		!BFQQ_TOTALLY_SEEKY(bfqq) &&
		!in_burst &&
		समय_is_beक्रमe_jअगरfies(bfqq->soft_rt_next_start) &&
		bfqq->dispatched == 0 &&
		bfqq->entity.new_weight == 40;
	*पूर्णांकeractive = !in_burst && idle_क्रम_दीर्घ_समय &&
		bfqq->entity.new_weight == 40;
	wr_or_deserves_wr = bfqd->low_latency &&
		(bfqq->wr_coeff > 1 ||
		 (bfq_bfqq_sync(bfqq) &&
		  bfqq->bic && (*पूर्णांकeractive || soft_rt)));

	/*
	 * Using the last flag, update budget and check whether bfqq
	 * may want to preempt the in-service queue.
	 */
	bfqq_wants_to_preempt =
		bfq_bfqq_update_budg_क्रम_activation(bfqd, bfqq,
						    arrived_in_समय);

	/*
	 * If bfqq happened to be activated in a burst, but has been
	 * idle क्रम much more than an पूर्णांकeractive queue, then we
	 * assume that, in the overall I/O initiated in the burst, the
	 * I/O associated with bfqq is finished. So bfqq करोes not need
	 * to be treated as a queue beदीर्घing to a burst
	 * anymore. Accordingly, we reset bfqq's in_large_burst flag
	 * अगर set, and हटाओ bfqq from the burst list अगर it's
	 * there. We करो not decrement burst_size, because the fact
	 * that bfqq करोes not need to beदीर्घ to the burst list any
	 * more करोes not invalidate the fact that bfqq was created in
	 * a burst.
	 */
	अगर (likely(!bfq_bfqq_just_created(bfqq)) &&
	    idle_क्रम_दीर्घ_समय &&
	    समय_is_beक्रमe_jअगरfies(
		    bfqq->budget_समयout +
		    msecs_to_jअगरfies(10000))) अणु
		hlist_del_init(&bfqq->burst_list_node);
		bfq_clear_bfqq_in_large_burst(bfqq);
	पूर्ण

	bfq_clear_bfqq_just_created(bfqq);

	अगर (bfqd->low_latency) अणु
		अगर (unlikely(समय_is_after_jअगरfies(bfqq->split_समय)))
			/* wraparound */
			bfqq->split_समय =
				jअगरfies - bfqd->bfq_wr_min_idle_समय - 1;

		अगर (समय_is_beक्रमe_jअगरfies(bfqq->split_समय +
					   bfqd->bfq_wr_min_idle_समय)) अणु
			bfq_update_bfqq_wr_on_rq_arrival(bfqd, bfqq,
							 old_wr_coeff,
							 wr_or_deserves_wr,
							 *पूर्णांकeractive,
							 in_burst,
							 soft_rt);

			अगर (old_wr_coeff != bfqq->wr_coeff)
				bfqq->entity.prio_changed = 1;
		पूर्ण
	पूर्ण

	bfqq->last_idle_bklogged = jअगरfies;
	bfqq->service_from_backlogged = 0;
	bfq_clear_bfqq_softrt_update(bfqq);

	bfq_add_bfqq_busy(bfqd, bfqq);

	/*
	 * Expire in-service queue अगर preemption may be needed क्रम
	 * guarantees or throughput. As क्रम guarantees, we care
	 * explicitly about two हालs. The first is that bfqq has to
	 * recover a service hole, as explained in the comments on
	 * bfq_bfqq_update_budg_क्रम_activation(), i.e., that
	 * bfqq_wants_to_preempt is true. However, अगर bfqq करोes not
	 * carry समय-critical I/O, then bfqq's bandwidth is less
	 * important than that of queues that carry समय-critical I/O.
	 * So, as a further स्थिरraपूर्णांक, we consider this हाल only अगर
	 * bfqq is at least as weight-उठाओd, i.e., at least as समय
	 * critical, as the in-service queue.
	 *
	 * The second हाल is that bfqq is in a higher priority class,
	 * or has a higher weight than the in-service queue. If this
	 * condition करोes not hold, we करोn't care because, even अगर
	 * bfqq करोes not start to be served immediately, the resulting
	 * delay क्रम bfqq's I/O is however lower or much lower than
	 * the ideal completion समय to be guaranteed to bfqq's I/O.
	 *
	 * In both हालs, preemption is needed only अगर, according to
	 * the बारtamps of both bfqq and of the in-service queue,
	 * bfqq actually is the next queue to serve. So, to reduce
	 * useless preemptions, the वापस value of
	 * next_queue_may_preempt() is considered in the next compound
	 * condition too. Yet next_queue_may_preempt() just checks a
	 * simple, necessary condition क्रम bfqq to be the next queue
	 * to serve. In fact, to evaluate a sufficient condition, the
	 * बारtamps of the in-service queue would need to be
	 * updated, and this operation is quite costly (see the
	 * comments on bfq_bfqq_update_budg_क्रम_activation()).
	 *
	 * As क्रम throughput, we ask bfq_better_to_idle() whether we
	 * still need to plug I/O dispatching. If bfq_better_to_idle()
	 * says no, then plugging is not needed any दीर्घer, either to
	 * boost throughput or to perserve service guarantees. Then
	 * the best option is to stop plugging I/O, as not करोing so
	 * would certainly lower throughput. We may end up in this
	 * हाल अगर: (1) upon a dispatch attempt, we detected that it
	 * was better to plug I/O dispatch, and to रुको क्रम a new
	 * request to arrive क्रम the currently in-service queue, but
	 * (2) this चयन of bfqq to busy changes the scenario.
	 */
	अगर (bfqd->in_service_queue &&
	    ((bfqq_wants_to_preempt &&
	      bfqq->wr_coeff >= bfqd->in_service_queue->wr_coeff) ||
	     bfq_bfqq_higher_class_or_weight(bfqq, bfqd->in_service_queue) ||
	     !bfq_better_to_idle(bfqd->in_service_queue)) &&
	    next_queue_may_preempt(bfqd))
		bfq_bfqq_expire(bfqd, bfqd->in_service_queue,
				false, BFQQE_PREEMPTED);
पूर्ण

अटल व्योम bfq_reset_inject_limit(काष्ठा bfq_data *bfqd,
				   काष्ठा bfq_queue *bfqq)
अणु
	/* invalidate baseline total service समय */
	bfqq->last_serv_समय_ns = 0;

	/*
	 * Reset poपूर्णांकer in हाल we are रुकोing क्रम
	 * some request completion.
	 */
	bfqd->रुकोed_rq = शून्य;

	/*
	 * If bfqq has a लघु think समय, then start by setting the
	 * inject limit to 0 prudentially, because the service समय of
	 * an injected I/O request may be higher than the think समय
	 * of bfqq, and thereक्रमe, अगर one request was injected when
	 * bfqq reमुख्यs empty, this injected request might delay the
	 * service of the next I/O request क्रम bfqq signअगरicantly. In
	 * हाल bfqq can actually tolerate some injection, then the
	 * adaptive update will however उठाओ the limit soon. This
	 * lucky circumstance holds exactly because bfqq has a लघु
	 * think समय, and thus, after reमुख्यing empty, is likely to
	 * get new I/O enqueued---and then completed---beक्रमe being
	 * expired. This is the very pattern that gives the
	 * limit-update algorithm the chance to measure the effect of
	 * injection on request service बार, and then to update the
	 * limit accordingly.
	 *
	 * However, in the following special हाल, the inject limit is
	 * left to 1 even अगर the think समय is लघु: bfqq's I/O is
	 * synchronized with that of some other queue, i.e., bfqq may
	 * receive new I/O only after the I/O of the other queue is
	 * completed. Keeping the inject limit to 1 allows the
	 * blocking I/O to be served जबतक bfqq is in service. And
	 * this is very convenient both क्रम bfqq and क्रम overall
	 * throughput, as explained in detail in the comments in
	 * bfq_update_has_लघु_tसमय().
	 *
	 * On the opposite end, अगर bfqq has a दीर्घ think समय, then
	 * start directly by 1, because:
	 * a) on the bright side, keeping at most one request in
	 * service in the drive is unlikely to cause any harm to the
	 * latency of bfqq's requests, as the service समय of a single
	 * request is likely to be lower than the think समय of bfqq;
	 * b) on the करोwnside, after becoming empty, bfqq is likely to
	 * expire beक्रमe getting its next request. With this request
	 * arrival pattern, it is very hard to sample total service
	 * बार and update the inject limit accordingly (see comments
	 * on bfq_update_inject_limit()). So the limit is likely to be
	 * never, or at least selकरोm, updated.  As a consequence, by
	 * setting the limit to 1, we aव्योम that no injection ever
	 * occurs with bfqq. On the करोwnside, this proactive step
	 * further reduces chances to actually compute the baseline
	 * total service समय. Thus it reduces chances to execute the
	 * limit-update algorithm and possibly उठाओ the limit to more
	 * than 1.
	 */
	अगर (bfq_bfqq_has_लघु_tसमय(bfqq))
		bfqq->inject_limit = 0;
	अन्यथा
		bfqq->inject_limit = 1;

	bfqq->decrease_समय_jअगर = jअगरfies;
पूर्ण

अटल व्योम bfq_update_io_पूर्णांकensity(काष्ठा bfq_queue *bfqq, u64 now_ns)
अणु
	u64 tot_io_समय = now_ns - bfqq->io_start_समय;

	अगर (RB_EMPTY_ROOT(&bfqq->sort_list) && bfqq->dispatched == 0)
		bfqq->tot_idle_समय +=
			now_ns - bfqq->tसमय.last_end_request;

	अगर (unlikely(bfq_bfqq_just_created(bfqq)))
		वापस;

	/*
	 * Must be busy क्रम at least about 80% of the समय to be
	 * considered I/O bound.
	 */
	अगर (bfqq->tot_idle_समय * 5 > tot_io_समय)
		bfq_clear_bfqq_IO_bound(bfqq);
	अन्यथा
		bfq_mark_bfqq_IO_bound(bfqq);

	/*
	 * Keep an observation winकरोw of at most 200 ms in the past
	 * from now.
	 */
	अगर (tot_io_समय > 200 * NSEC_PER_MSEC) अणु
		bfqq->io_start_समय = now_ns - (tot_io_समय>>1);
		bfqq->tot_idle_समय >>= 1;
	पूर्ण
पूर्ण

/*
 * Detect whether bfqq's I/O seems synchronized with that of some
 * other queue, i.e., whether bfqq, after reमुख्यing empty, happens to
 * receive new I/O only right after some I/O request of the other
 * queue has been completed. We call waker queue the other queue, and
 * we assume, क्रम simplicity, that bfqq may have at most one waker
 * queue.
 *
 * A remarkable throughput boost can be reached by unconditionally
 * injecting the I/O of the waker queue, every समय a new
 * bfq_dispatch_request happens to be invoked जबतक I/O is being
 * plugged क्रम bfqq.  In addition to boosting throughput, this
 * unblocks bfqq's I/O, thereby improving bandwidth and latency क्रम
 * bfqq. Note that these same results may be achieved with the general
 * injection mechanism, but less effectively. For details on this
 * aspect, see the comments on the choice of the queue क्रम injection
 * in bfq_select_queue().
 *
 * Turning back to the detection of a waker queue, a queue Q is deemed
 * as a waker queue क्रम bfqq अगर, क्रम three consecutive बार, bfqq
 * happens to become non empty right after a request of Q has been
 * completed. In particular, on the first समय, Q is tentatively set
 * as a candidate waker queue, जबतक on the third consecutive समय
 * that Q is detected, the field waker_bfqq is set to Q, to confirm
 * that Q is a waker queue क्रम bfqq. These detection steps are
 * perक्रमmed only अगर bfqq has a दीर्घ think समय, so as to make it more
 * likely that bfqq's I/O is actually being blocked by a
 * synchronization. This last filter, plus the above three-बार
 * requirement, make false positives less likely.
 *
 * NOTE
 *
 * The sooner a waker queue is detected, the sooner throughput can be
 * boosted by injecting I/O from the waker queue. Fortunately,
 * detection is likely to be actually fast, क्रम the following
 * reasons. While blocked by synchronization, bfqq has a दीर्घ think
 * समय. This implies that bfqq's inject limit is at least equal to 1
 * (see the comments in bfq_update_inject_limit()). So, thanks to
 * injection, the waker queue is likely to be served during the very
 * first I/O-plugging समय पूर्णांकerval क्रम bfqq. This triggers the first
 * step of the detection mechanism. Thanks again to injection, the
 * candidate waker queue is then likely to be confirmed no later than
 * during the next I/O-plugging पूर्णांकerval क्रम bfqq.
 *
 * ISSUE
 *
 * On queue merging all waker inक्रमmation is lost.
 */
अटल व्योम bfq_check_waker(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			    u64 now_ns)
अणु
	अगर (!bfqd->last_completed_rq_bfqq ||
	    bfqd->last_completed_rq_bfqq == bfqq ||
	    bfq_bfqq_has_लघु_tसमय(bfqq) ||
	    now_ns - bfqd->last_completion >= 4 * NSEC_PER_MSEC ||
	    bfqd->last_completed_rq_bfqq == bfqq->waker_bfqq)
		वापस;

	अगर (bfqd->last_completed_rq_bfqq !=
	    bfqq->tentative_waker_bfqq) अणु
		/*
		 * First synchronization detected with a
		 * candidate waker queue, or with a dअगरferent
		 * candidate waker queue from the current one.
		 */
		bfqq->tentative_waker_bfqq =
			bfqd->last_completed_rq_bfqq;
		bfqq->num_waker_detections = 1;
	पूर्ण अन्यथा /* Same tentative waker queue detected again */
		bfqq->num_waker_detections++;

	अगर (bfqq->num_waker_detections == 3) अणु
		bfqq->waker_bfqq = bfqd->last_completed_rq_bfqq;
		bfqq->tentative_waker_bfqq = शून्य;

		/*
		 * If the waker queue disappears, then
		 * bfqq->waker_bfqq must be reset. To
		 * this goal, we मुख्यtain in each
		 * waker queue a list, woken_list, of
		 * all the queues that reference the
		 * waker queue through their
		 * waker_bfqq poपूर्णांकer. When the waker
		 * queue निकासs, the waker_bfqq poपूर्णांकer
		 * of all the queues in the woken_list
		 * is reset.
		 *
		 * In addition, अगर bfqq is alपढ़ोy in
		 * the woken_list of a waker queue,
		 * then, beक्रमe being inserted पूर्णांकo
		 * the woken_list of a new waker
		 * queue, bfqq must be हटाओd from
		 * the woken_list of the old waker
		 * queue.
		 */
		अगर (!hlist_unhashed(&bfqq->woken_list_node))
			hlist_del_init(&bfqq->woken_list_node);
		hlist_add_head(&bfqq->woken_list_node,
			       &bfqd->last_completed_rq_bfqq->woken_list);
	पूर्ण
पूर्ण

अटल व्योम bfq_add_request(काष्ठा request *rq)
अणु
	काष्ठा bfq_queue *bfqq = RQ_BFQQ(rq);
	काष्ठा bfq_data *bfqd = bfqq->bfqd;
	काष्ठा request *next_rq, *prev;
	अचिन्हित पूर्णांक old_wr_coeff = bfqq->wr_coeff;
	bool पूर्णांकeractive = false;
	u64 now_ns = kसमय_get_ns();

	bfq_log_bfqq(bfqd, bfqq, "add_request %d", rq_is_sync(rq));
	bfqq->queued[rq_is_sync(rq)]++;
	bfqd->queued++;

	अगर (RB_EMPTY_ROOT(&bfqq->sort_list) && bfq_bfqq_sync(bfqq)) अणु
		bfq_check_waker(bfqd, bfqq, now_ns);

		/*
		 * Periodically reset inject limit, to make sure that
		 * the latter eventually drops in हाल workload
		 * changes, see step (3) in the comments on
		 * bfq_update_inject_limit().
		 */
		अगर (समय_is_beक्रमe_eq_jअगरfies(bfqq->decrease_समय_jअगर +
					     msecs_to_jअगरfies(1000)))
			bfq_reset_inject_limit(bfqd, bfqq);

		/*
		 * The following conditions must hold to setup a new
		 * sampling of total service समय, and then a new
		 * update of the inject limit:
		 * - bfqq is in service, because the total service
		 *   समय is evaluated only क्रम the I/O requests of
		 *   the queues in service;
		 * - this is the right occasion to compute or to
		 *   lower the baseline total service समय, because
		 *   there are actually no requests in the drive,
		 *   or
		 *   the baseline total service समय is available, and
		 *   this is the right occasion to compute the other
		 *   quantity needed to update the inject limit, i.e.,
		 *   the total service समय caused by the amount of
		 *   injection allowed by the current value of the
		 *   limit. It is the right occasion because injection
		 *   has actually been perक्रमmed during the service
		 *   hole, and there are still in-flight requests,
		 *   which are very likely to be exactly the injected
		 *   requests, or part of them;
		 * - the minimum पूर्णांकerval क्रम sampling the total
		 *   service समय and updating the inject limit has
		 *   elapsed.
		 */
		अगर (bfqq == bfqd->in_service_queue &&
		    (bfqd->rq_in_driver == 0 ||
		     (bfqq->last_serv_समय_ns > 0 &&
		      bfqd->rqs_injected && bfqd->rq_in_driver > 0)) &&
		    समय_is_beक्रमe_eq_jअगरfies(bfqq->decrease_समय_jअगर +
					      msecs_to_jअगरfies(10))) अणु
			bfqd->last_empty_occupied_ns = kसमय_get_ns();
			/*
			 * Start the state machine क्रम measuring the
			 * total service समय of rq: setting
			 * रुको_dispatch will cause bfqd->रुकोed_rq to
			 * be set when rq will be dispatched.
			 */
			bfqd->रुको_dispatch = true;
			/*
			 * If there is no I/O in service in the drive,
			 * then possible injection occurred beक्रमe the
			 * arrival of rq will not affect the total
			 * service समय of rq. So the injection limit
			 * must not be updated as a function of such
			 * total service समय, unless new injection
			 * occurs beक्रमe rq is completed. To have the
			 * injection limit updated only in the latter
			 * हाल, reset rqs_injected here (rqs_injected
			 * will be set in हाल injection is perक्रमmed
			 * on bfqq beक्रमe rq is completed).
			 */
			अगर (bfqd->rq_in_driver == 0)
				bfqd->rqs_injected = false;
		पूर्ण
	पूर्ण

	अगर (bfq_bfqq_sync(bfqq))
		bfq_update_io_पूर्णांकensity(bfqq, now_ns);

	elv_rb_add(&bfqq->sort_list, rq);

	/*
	 * Check अगर this request is a better next-serve candidate.
	 */
	prev = bfqq->next_rq;
	next_rq = bfq_choose_req(bfqd, bfqq->next_rq, rq, bfqd->last_position);
	bfqq->next_rq = next_rq;

	/*
	 * Adjust priority tree position, अगर next_rq changes.
	 * See comments on bfq_pos_tree_add_move() क्रम the unlikely().
	 */
	अगर (unlikely(!bfqd->nonrot_with_queueing && prev != bfqq->next_rq))
		bfq_pos_tree_add_move(bfqd, bfqq);

	अगर (!bfq_bfqq_busy(bfqq)) /* चयनing to busy ... */
		bfq_bfqq_handle_idle_busy_चयन(bfqd, bfqq, old_wr_coeff,
						 rq, &पूर्णांकeractive);
	अन्यथा अणु
		अगर (bfqd->low_latency && old_wr_coeff == 1 && !rq_is_sync(rq) &&
		    समय_is_beक्रमe_jअगरfies(
				bfqq->last_wr_start_finish +
				bfqd->bfq_wr_min_पूर्णांकer_arr_async)) अणु
			bfqq->wr_coeff = bfqd->bfq_wr_coeff;
			bfqq->wr_cur_max_समय = bfq_wr_duration(bfqd);

			bfqd->wr_busy_queues++;
			bfqq->entity.prio_changed = 1;
		पूर्ण
		अगर (prev != bfqq->next_rq)
			bfq_updated_next_req(bfqd, bfqq);
	पूर्ण

	/*
	 * Assign jअगरfies to last_wr_start_finish in the following
	 * हालs:
	 *
	 * . अगर bfqq is not going to be weight-उठाओd, because, क्रम
	 *   non weight-उठाओd queues, last_wr_start_finish stores the
	 *   arrival समय of the last request; as of now, this piece
	 *   of inक्रमmation is used only क्रम deciding whether to
	 *   weight-उठाओ async queues
	 *
	 * . अगर bfqq is not weight-उठाओd, because, अगर bfqq is now
	 *   चयनing to weight-उठाओd, then last_wr_start_finish
	 *   stores the समय when weight-raising starts
	 *
	 * . अगर bfqq is पूर्णांकeractive, because, regardless of whether
	 *   bfqq is currently weight-उठाओd, the weight-raising
	 *   period must start or restart (this हाल is considered
	 *   separately because it is not detected by the above
	 *   conditions, अगर bfqq is alपढ़ोy weight-उठाओd)
	 *
	 * last_wr_start_finish has to be updated also अगर bfqq is soft
	 * real-समय, because the weight-raising period is स्थिरantly
	 * restarted on idle-to-busy transitions क्रम these queues, but
	 * this is alपढ़ोy करोne in bfq_bfqq_handle_idle_busy_चयन अगर
	 * needed.
	 */
	अगर (bfqd->low_latency &&
		(old_wr_coeff == 1 || bfqq->wr_coeff == 1 || पूर्णांकeractive))
		bfqq->last_wr_start_finish = jअगरfies;
पूर्ण

अटल काष्ठा request *bfq_find_rq_fmerge(काष्ठा bfq_data *bfqd,
					  काष्ठा bio *bio,
					  काष्ठा request_queue *q)
अणु
	काष्ठा bfq_queue *bfqq = bfqd->bio_bfqq;


	अगर (bfqq)
		वापस elv_rb_find(&bfqq->sort_list, bio_end_sector(bio));

	वापस शून्य;
पूर्ण

अटल sector_t get_sdist(sector_t last_pos, काष्ठा request *rq)
अणु
	अगर (last_pos)
		वापस असल(blk_rq_pos(rq) - last_pos);

	वापस 0;
पूर्ण

#अगर 0 /* Still not clear अगर we can करो without next two functions */
अटल व्योम bfq_activate_request(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	काष्ठा bfq_data *bfqd = q->elevator->elevator_data;

	bfqd->rq_in_driver++;
पूर्ण

अटल व्योम bfq_deactivate_request(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	काष्ठा bfq_data *bfqd = q->elevator->elevator_data;

	bfqd->rq_in_driver--;
पूर्ण
#पूर्ण_अगर

अटल व्योम bfq_हटाओ_request(काष्ठा request_queue *q,
			       काष्ठा request *rq)
अणु
	काष्ठा bfq_queue *bfqq = RQ_BFQQ(rq);
	काष्ठा bfq_data *bfqd = bfqq->bfqd;
	स्थिर पूर्णांक sync = rq_is_sync(rq);

	अगर (bfqq->next_rq == rq) अणु
		bfqq->next_rq = bfq_find_next_rq(bfqd, bfqq, rq);
		bfq_updated_next_req(bfqd, bfqq);
	पूर्ण

	अगर (rq->queuelist.prev != &rq->queuelist)
		list_del_init(&rq->queuelist);
	bfqq->queued[sync]--;
	bfqd->queued--;
	elv_rb_del(&bfqq->sort_list, rq);

	elv_rqhash_del(q, rq);
	अगर (q->last_merge == rq)
		q->last_merge = शून्य;

	अगर (RB_EMPTY_ROOT(&bfqq->sort_list)) अणु
		bfqq->next_rq = शून्य;

		अगर (bfq_bfqq_busy(bfqq) && bfqq != bfqd->in_service_queue) अणु
			bfq_del_bfqq_busy(bfqd, bfqq, false);
			/*
			 * bfqq emptied. In normal operation, when
			 * bfqq is empty, bfqq->entity.service and
			 * bfqq->entity.budget must contain,
			 * respectively, the service received and the
			 * budget used last समय bfqq emptied. These
			 * facts करो not hold in this हाल, as at least
			 * this last removal occurred जबतक bfqq is
			 * not in service. To aव्योम inconsistencies,
			 * reset both bfqq->entity.service and
			 * bfqq->entity.budget, अगर bfqq has still a
			 * process that may issue I/O requests to it.
			 */
			bfqq->entity.budget = bfqq->entity.service = 0;
		पूर्ण

		/*
		 * Remove queue from request-position tree as it is empty.
		 */
		अगर (bfqq->pos_root) अणु
			rb_erase(&bfqq->pos_node, bfqq->pos_root);
			bfqq->pos_root = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* see comments on bfq_pos_tree_add_move() क्रम the unlikely() */
		अगर (unlikely(!bfqd->nonrot_with_queueing))
			bfq_pos_tree_add_move(bfqd, bfqq);
	पूर्ण

	अगर (rq->cmd_flags & REQ_META)
		bfqq->meta_pending--;

पूर्ण

अटल bool bfq_bio_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs)
अणु
	काष्ठा bfq_data *bfqd = q->elevator->elevator_data;
	काष्ठा request *मुक्त = शून्य;
	/*
	 * bfq_bic_lookup grअसल the queue_lock: invoke it now and
	 * store its वापस value क्रम later use, to aव्योम nesting
	 * queue_lock inside the bfqd->lock. We assume that the bic
	 * वापसed by bfq_bic_lookup करोes not go away beक्रमe
	 * bfqd->lock is taken.
	 */
	काष्ठा bfq_io_cq *bic = bfq_bic_lookup(bfqd, current->io_context, q);
	bool ret;

	spin_lock_irq(&bfqd->lock);

	अगर (bic)
		bfqd->bio_bfqq = bic_to_bfqq(bic, op_is_sync(bio->bi_opf));
	अन्यथा
		bfqd->bio_bfqq = शून्य;
	bfqd->bio_bic = bic;

	ret = blk_mq_sched_try_merge(q, bio, nr_segs, &मुक्त);

	अगर (मुक्त)
		blk_mq_मुक्त_request(मुक्त);
	spin_unlock_irq(&bfqd->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक bfq_request_merge(काष्ठा request_queue *q, काष्ठा request **req,
			     काष्ठा bio *bio)
अणु
	काष्ठा bfq_data *bfqd = q->elevator->elevator_data;
	काष्ठा request *__rq;

	__rq = bfq_find_rq_fmerge(bfqd, bio, q);
	अगर (__rq && elv_bio_merge_ok(__rq, bio)) अणु
		*req = __rq;
		वापस ELEVATOR_FRONT_MERGE;
	पूर्ण

	वापस ELEVATOR_NO_MERGE;
पूर्ण

अटल काष्ठा bfq_queue *bfq_init_rq(काष्ठा request *rq);

अटल व्योम bfq_request_merged(काष्ठा request_queue *q, काष्ठा request *req,
			       क्रमागत elv_merge type)
अणु
	अगर (type == ELEVATOR_FRONT_MERGE &&
	    rb_prev(&req->rb_node) &&
	    blk_rq_pos(req) <
	    blk_rq_pos(container_of(rb_prev(&req->rb_node),
				    काष्ठा request, rb_node))) अणु
		काष्ठा bfq_queue *bfqq = bfq_init_rq(req);
		काष्ठा bfq_data *bfqd;
		काष्ठा request *prev, *next_rq;

		अगर (!bfqq)
			वापस;

		bfqd = bfqq->bfqd;

		/* Reposition request in its sort_list */
		elv_rb_del(&bfqq->sort_list, req);
		elv_rb_add(&bfqq->sort_list, req);

		/* Choose next request to be served क्रम bfqq */
		prev = bfqq->next_rq;
		next_rq = bfq_choose_req(bfqd, bfqq->next_rq, req,
					 bfqd->last_position);
		bfqq->next_rq = next_rq;
		/*
		 * If next_rq changes, update both the queue's budget to
		 * fit the new request and the queue's position in its
		 * rq_pos_tree.
		 */
		अगर (prev != bfqq->next_rq) अणु
			bfq_updated_next_req(bfqd, bfqq);
			/*
			 * See comments on bfq_pos_tree_add_move() क्रम
			 * the unlikely().
			 */
			अगर (unlikely(!bfqd->nonrot_with_queueing))
				bfq_pos_tree_add_move(bfqd, bfqq);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function is called to notअगरy the scheduler that the requests
 * rq and 'next' have been merged, with 'next' going away.  BFQ
 * exploits this hook to address the following issue: अगर 'next' has a
 * fअगरo_समय lower that rq, then the fअगरo_समय of rq must be set to
 * the value of 'next', to not forget the greater age of 'next'.
 *
 * NOTE: in this function we assume that rq is in a bfq_queue, basing
 * on that rq is picked from the hash table q->elevator->hash, which,
 * in its turn, is filled only with I/O requests present in
 * bfq_queues, जबतक BFQ is in use क्रम the request queue q. In fact,
 * the function that fills this hash table (elv_rqhash_add) is called
 * only by bfq_insert_request.
 */
अटल व्योम bfq_requests_merged(काष्ठा request_queue *q, काष्ठा request *rq,
				काष्ठा request *next)
अणु
	काष्ठा bfq_queue *bfqq = bfq_init_rq(rq),
		*next_bfqq = bfq_init_rq(next);

	अगर (!bfqq)
		वापस;

	/*
	 * If next and rq beदीर्घ to the same bfq_queue and next is older
	 * than rq, then reposition rq in the fअगरo (by substituting next
	 * with rq). Otherwise, अगर next and rq beदीर्घ to dअगरferent
	 * bfq_queues, never reposition rq: in fact, we would have to
	 * reposition it with respect to next's position in its own fअगरo,
	 * which would most certainly be too expensive with respect to
	 * the benefits.
	 */
	अगर (bfqq == next_bfqq &&
	    !list_empty(&rq->queuelist) && !list_empty(&next->queuelist) &&
	    next->fअगरo_समय < rq->fअगरo_समय) अणु
		list_del_init(&rq->queuelist);
		list_replace_init(&next->queuelist, &rq->queuelist);
		rq->fअगरo_समय = next->fअगरo_समय;
	पूर्ण

	अगर (bfqq->next_rq == next)
		bfqq->next_rq = rq;

	bfqg_stats_update_io_merged(bfqq_group(bfqq), next->cmd_flags);
पूर्ण

/* Must be called with bfqq != शून्य */
अटल व्योम bfq_bfqq_end_wr(काष्ठा bfq_queue *bfqq)
अणु
	/*
	 * If bfqq has been enjoying पूर्णांकeractive weight-raising, then
	 * reset soft_rt_next_start. We करो it क्रम the following
	 * reason. bfqq may have been conveying the I/O needed to load
	 * a soft real-समय application. Such an application actually
	 * exhibits a soft real-समय I/O pattern after it finishes
	 * loading, and finally starts करोing its job. But, अगर bfqq has
	 * been receiving a lot of bandwidth so far (likely to happen
	 * on a fast device), then soft_rt_next_start now contains a
	 * high value that. So, without this reset, bfqq would be
	 * prevented from being possibly considered as soft_rt क्रम a
	 * very दीर्घ समय.
	 */

	अगर (bfqq->wr_cur_max_समय !=
	    bfqq->bfqd->bfq_wr_rt_max_समय)
		bfqq->soft_rt_next_start = jअगरfies;

	अगर (bfq_bfqq_busy(bfqq))
		bfqq->bfqd->wr_busy_queues--;
	bfqq->wr_coeff = 1;
	bfqq->wr_cur_max_समय = 0;
	bfqq->last_wr_start_finish = jअगरfies;
	/*
	 * Trigger a weight change on the next invocation of
	 * __bfq_entity_update_weight_prio.
	 */
	bfqq->entity.prio_changed = 1;
पूर्ण

व्योम bfq_end_wr_async_queues(काष्ठा bfq_data *bfqd,
			     काष्ठा bfq_group *bfqg)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < 2; i++)
		क्रम (j = 0; j < IOPRIO_BE_NR; j++)
			अगर (bfqg->async_bfqq[i][j])
				bfq_bfqq_end_wr(bfqg->async_bfqq[i][j]);
	अगर (bfqg->async_idle_bfqq)
		bfq_bfqq_end_wr(bfqg->async_idle_bfqq);
पूर्ण

अटल व्योम bfq_end_wr(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा bfq_queue *bfqq;

	spin_lock_irq(&bfqd->lock);

	list_क्रम_each_entry(bfqq, &bfqd->active_list, bfqq_list)
		bfq_bfqq_end_wr(bfqq);
	list_क्रम_each_entry(bfqq, &bfqd->idle_list, bfqq_list)
		bfq_bfqq_end_wr(bfqq);
	bfq_end_wr_async(bfqd);

	spin_unlock_irq(&bfqd->lock);
पूर्ण

अटल sector_t bfq_io_काष्ठा_pos(व्योम *io_काष्ठा, bool request)
अणु
	अगर (request)
		वापस blk_rq_pos(io_काष्ठा);
	अन्यथा
		वापस ((काष्ठा bio *)io_काष्ठा)->bi_iter.bi_sector;
पूर्ण

अटल पूर्णांक bfq_rq_बंद_to_sector(व्योम *io_काष्ठा, bool request,
				  sector_t sector)
अणु
	वापस असल(bfq_io_काष्ठा_pos(io_काष्ठा, request) - sector) <=
	       BFQQ_CLOSE_THR;
पूर्ण

अटल काष्ठा bfq_queue *bfqq_find_बंद(काष्ठा bfq_data *bfqd,
					 काष्ठा bfq_queue *bfqq,
					 sector_t sector)
अणु
	काष्ठा rb_root *root = &bfq_bfqq_to_bfqg(bfqq)->rq_pos_tree;
	काष्ठा rb_node *parent, *node;
	काष्ठा bfq_queue *__bfqq;

	अगर (RB_EMPTY_ROOT(root))
		वापस शून्य;

	/*
	 * First, अगर we find a request starting at the end of the last
	 * request, choose it.
	 */
	__bfqq = bfq_rq_pos_tree_lookup(bfqd, root, sector, &parent, शून्य);
	अगर (__bfqq)
		वापस __bfqq;

	/*
	 * If the exact sector wasn't found, the parent of the शून्य leaf
	 * will contain the बंदst sector (rq_pos_tree sorted by
	 * next_request position).
	 */
	__bfqq = rb_entry(parent, काष्ठा bfq_queue, pos_node);
	अगर (bfq_rq_बंद_to_sector(__bfqq->next_rq, true, sector))
		वापस __bfqq;

	अगर (blk_rq_pos(__bfqq->next_rq) < sector)
		node = rb_next(&__bfqq->pos_node);
	अन्यथा
		node = rb_prev(&__bfqq->pos_node);
	अगर (!node)
		वापस शून्य;

	__bfqq = rb_entry(node, काष्ठा bfq_queue, pos_node);
	अगर (bfq_rq_बंद_to_sector(__bfqq->next_rq, true, sector))
		वापस __bfqq;

	वापस शून्य;
पूर्ण

अटल काष्ठा bfq_queue *bfq_find_बंद_coचालक(काष्ठा bfq_data *bfqd,
						   काष्ठा bfq_queue *cur_bfqq,
						   sector_t sector)
अणु
	काष्ठा bfq_queue *bfqq;

	/*
	 * We shall notice अगर some of the queues are cooperating,
	 * e.g., working बंदly on the same area of the device. In
	 * that हाल, we can group them together and: 1) करोn't waste
	 * समय idling, and 2) serve the जोड़ of their requests in
	 * the best possible order क्रम throughput.
	 */
	bfqq = bfqq_find_बंद(bfqd, cur_bfqq, sector);
	अगर (!bfqq || bfqq == cur_bfqq)
		वापस शून्य;

	वापस bfqq;
पूर्ण

अटल काष्ठा bfq_queue *
bfq_setup_merge(काष्ठा bfq_queue *bfqq, काष्ठा bfq_queue *new_bfqq)
अणु
	पूर्णांक process_refs, new_process_refs;
	काष्ठा bfq_queue *__bfqq;

	/*
	 * If there are no process references on the new_bfqq, then it is
	 * unsafe to follow the ->new_bfqq chain as other bfqq's in the chain
	 * may have dropped their last reference (not just their last process
	 * reference).
	 */
	अगर (!bfqq_process_refs(new_bfqq))
		वापस शून्य;

	/* Aव्योम a circular list and skip पूर्णांकerim queue merges. */
	जबतक ((__bfqq = new_bfqq->new_bfqq)) अणु
		अगर (__bfqq == bfqq)
			वापस शून्य;
		new_bfqq = __bfqq;
	पूर्ण

	process_refs = bfqq_process_refs(bfqq);
	new_process_refs = bfqq_process_refs(new_bfqq);
	/*
	 * If the process क्रम the bfqq has gone away, there is no
	 * sense in merging the queues.
	 */
	अगर (process_refs == 0 || new_process_refs == 0)
		वापस शून्य;

	bfq_log_bfqq(bfqq->bfqd, bfqq, "scheduling merge with queue %d",
		new_bfqq->pid);

	/*
	 * Merging is just a redirection: the requests of the process
	 * owning one of the two queues are redirected to the other queue.
	 * The latter queue, in its turn, is set as shared अगर this is the
	 * first समय that the requests of some process are redirected to
	 * it.
	 *
	 * We redirect bfqq to new_bfqq and not the opposite, because
	 * we are in the context of the process owning bfqq, thus we
	 * have the io_cq of this process. So we can immediately
	 * configure this io_cq to redirect the requests of the
	 * process to new_bfqq. In contrast, the io_cq of new_bfqq is
	 * not available any more (new_bfqq->bic == शून्य).
	 *
	 * Anyway, even in हाल new_bfqq coincides with the in-service
	 * queue, redirecting requests the in-service queue is the
	 * best option, as we feed the in-service queue with new
	 * requests बंद to the last request served and, by करोing so,
	 * are likely to increase the throughput.
	 */
	bfqq->new_bfqq = new_bfqq;
	new_bfqq->ref += process_refs;
	वापस new_bfqq;
पूर्ण

अटल bool bfq_may_be_बंद_coचालक(काष्ठा bfq_queue *bfqq,
					काष्ठा bfq_queue *new_bfqq)
अणु
	अगर (bfq_too_late_क्रम_merging(new_bfqq))
		वापस false;

	अगर (bfq_class_idle(bfqq) || bfq_class_idle(new_bfqq) ||
	    (bfqq->ioprio_class != new_bfqq->ioprio_class))
		वापस false;

	/*
	 * If either of the queues has alपढ़ोy been detected as seeky,
	 * then merging it with the other queue is unlikely to lead to
	 * sequential I/O.
	 */
	अगर (BFQQ_SEEKY(bfqq) || BFQQ_SEEKY(new_bfqq))
		वापस false;

	/*
	 * Interleaved I/O is known to be करोne by (some) applications
	 * only क्रम पढ़ोs, so it करोes not make sense to merge async
	 * queues.
	 */
	अगर (!bfq_bfqq_sync(bfqq) || !bfq_bfqq_sync(new_bfqq))
		वापस false;

	वापस true;
पूर्ण

अटल bool idling_boosts_thr_without_issues(काष्ठा bfq_data *bfqd,
					     काष्ठा bfq_queue *bfqq);

/*
 * Attempt to schedule a merge of bfqq with the currently in-service
 * queue or with a बंद queue among the scheduled queues.  Return
 * शून्य अगर no merge was scheduled, a poपूर्णांकer to the shared bfq_queue
 * काष्ठाure otherwise.
 *
 * The OOM queue is not allowed to participate to cooperation: in fact, since
 * the requests temporarily redirected to the OOM queue could be redirected
 * again to dedicated queues at any समय, the state needed to correctly
 * handle merging with the OOM queue would be quite complex and expensive
 * to मुख्यtain. Besides, in such a critical condition as an out of memory,
 * the benefits of queue merging may be little relevant, or even negligible.
 *
 * WARNING: queue merging may impair fairness among non-weight उठाओd
 * queues, क्रम at least two reasons: 1) the original weight of a
 * merged queue may change during the merged state, 2) even being the
 * weight the same, a merged queue may be bloated with many more
 * requests than the ones produced by its originally-associated
 * process.
 */
अटल काष्ठा bfq_queue *
bfq_setup_coचालक(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		     व्योम *io_काष्ठा, bool request, काष्ठा bfq_io_cq *bic)
अणु
	काष्ठा bfq_queue *in_service_bfqq, *new_bfqq;

	/*
	 * Check delayed stable merge क्रम rotational or non-queueing
	 * devs. For this branch to be executed, bfqq must not be
	 * currently merged with some other queue (i.e., bfqq->bic
	 * must be non null). If we considered also merged queues,
	 * then we should also check whether bfqq has alपढ़ोy been
	 * merged with bic->stable_merge_bfqq. But this would be
	 * costly and complicated.
	 */
	अगर (unlikely(!bfqd->nonrot_with_queueing)) अणु
		अगर (bic->stable_merge_bfqq &&
		    !bfq_bfqq_just_created(bfqq) &&
		    समय_is_after_jअगरfies(bfqq->split_समय +
					  msecs_to_jअगरfies(200))) अणु
			काष्ठा bfq_queue *stable_merge_bfqq =
				bic->stable_merge_bfqq;
			पूर्णांक proc_ref = min(bfqq_process_refs(bfqq),
					   bfqq_process_refs(stable_merge_bfqq));

			/* deschedule stable merge, because करोne or पातed here */
			bfq_put_stable_ref(stable_merge_bfqq);

			bic->stable_merge_bfqq = शून्य;

			अगर (!idling_boosts_thr_without_issues(bfqd, bfqq) &&
			    proc_ref > 0) अणु
				/* next function will take at least one ref */
				काष्ठा bfq_queue *new_bfqq =
					bfq_setup_merge(bfqq, stable_merge_bfqq);

				bic->stably_merged = true;
				अगर (new_bfqq && new_bfqq->bic)
					new_bfqq->bic->stably_merged = true;
				वापस new_bfqq;
			पूर्ण अन्यथा
				वापस शून्य;
		पूर्ण
	पूर्ण

	/*
	 * Do not perक्रमm queue merging अगर the device is non
	 * rotational and perक्रमms पूर्णांकernal queueing. In fact, such a
	 * device reaches a high speed through पूर्णांकernal parallelism
	 * and pipelining. This means that, to reach a high
	 * throughput, it must have many requests enqueued at the same
	 * समय. But, in this configuration, the पूर्णांकernal scheduling
	 * algorithm of the device करोes exactly the job of queue
	 * merging: it reorders requests so as to obtain as much as
	 * possible a sequential I/O pattern. As a consequence, with
	 * the workload generated by processes करोing पूर्णांकerleaved I/O,
	 * the throughput reached by the device is likely to be the
	 * same, with and without queue merging.
	 *
	 * Disabling merging also provides a remarkable benefit in
	 * terms of throughput. Merging tends to make many workloads
	 * artअगरicially more uneven, because of shared queues
	 * reमुख्यing non empty क्रम incomparably more समय than
	 * non-merged queues. This may accentuate workload
	 * asymmetries. For example, अगर one of the queues in a set of
	 * merged queues has a higher weight than a normal queue, then
	 * the shared queue may inherit such a high weight and, by
	 * staying almost always active, may क्रमce BFQ to perक्रमm I/O
	 * plugging most of the समय. This evidently makes it harder
	 * क्रम BFQ to let the device reach a high throughput.
	 *
	 * Finally, the likely() macro below is not used because one
	 * of the two branches is more likely than the other, but to
	 * have the code path after the following अगर() executed as
	 * fast as possible क्रम the हाल of a non rotational device
	 * with queueing. We want it because this is the fastest kind
	 * of device. On the opposite end, the likely() may lengthen
	 * the execution समय of BFQ क्रम the हाल of slower devices
	 * (rotational or at least without queueing). But in this हाल
	 * the execution समय of BFQ matters very little, अगर not at
	 * all.
	 */
	अगर (likely(bfqd->nonrot_with_queueing))
		वापस शून्य;

	/*
	 * Prevent bfqq from being merged अगर it has been created too
	 * दीर्घ ago. The idea is that true cooperating processes, and
	 * thus their associated bfq_queues, are supposed to be
	 * created लघुly after each other. This is the हाल, e.g.,
	 * क्रम KVM/QEMU and dump I/O thपढ़ोs. Basing on this
	 * assumption, the following filtering greatly reduces the
	 * probability that two non-cooperating processes, which just
	 * happen to करो बंद I/O क्रम some लघु समय पूर्णांकerval, have
	 * their queues merged by mistake.
	 */
	अगर (bfq_too_late_क्रम_merging(bfqq))
		वापस शून्य;

	अगर (bfqq->new_bfqq)
		वापस bfqq->new_bfqq;

	अगर (!io_काष्ठा || unlikely(bfqq == &bfqd->oom_bfqq))
		वापस शून्य;

	/* If there is only one backlogged queue, करोn't search. */
	अगर (bfq_tot_busy_queues(bfqd) == 1)
		वापस शून्य;

	in_service_bfqq = bfqd->in_service_queue;

	अगर (in_service_bfqq && in_service_bfqq != bfqq &&
	    likely(in_service_bfqq != &bfqd->oom_bfqq) &&
	    bfq_rq_बंद_to_sector(io_काष्ठा, request,
				   bfqd->in_serv_last_pos) &&
	    bfqq->entity.parent == in_service_bfqq->entity.parent &&
	    bfq_may_be_बंद_coचालक(bfqq, in_service_bfqq)) अणु
		new_bfqq = bfq_setup_merge(bfqq, in_service_bfqq);
		अगर (new_bfqq)
			वापस new_bfqq;
	पूर्ण
	/*
	 * Check whether there is a coचालक among currently scheduled
	 * queues. The only thing we need is that the bio/request is not
	 * शून्य, as we need it to establish whether a coचालक exists.
	 */
	new_bfqq = bfq_find_बंद_coचालक(bfqd, bfqq,
			bfq_io_काष्ठा_pos(io_काष्ठा, request));

	अगर (new_bfqq && likely(new_bfqq != &bfqd->oom_bfqq) &&
	    bfq_may_be_बंद_coचालक(bfqq, new_bfqq))
		वापस bfq_setup_merge(bfqq, new_bfqq);

	वापस शून्य;
पूर्ण

अटल व्योम bfq_bfqq_save_state(काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_io_cq *bic = bfqq->bic;

	/*
	 * If !bfqq->bic, the queue is alपढ़ोy shared or its requests
	 * have alपढ़ोy been redirected to a shared queue; both idle winकरोw
	 * and weight raising state have alपढ़ोy been saved. Do nothing.
	 */
	अगर (!bic)
		वापस;

	bic->saved_last_serv_समय_ns = bfqq->last_serv_समय_ns;
	bic->saved_inject_limit = bfqq->inject_limit;
	bic->saved_decrease_समय_jअगर = bfqq->decrease_समय_jअगर;

	bic->saved_weight = bfqq->entity.orig_weight;
	bic->saved_tसमय = bfqq->tसमय;
	bic->saved_has_लघु_tसमय = bfq_bfqq_has_लघु_tसमय(bfqq);
	bic->saved_IO_bound = bfq_bfqq_IO_bound(bfqq);
	bic->saved_io_start_समय = bfqq->io_start_समय;
	bic->saved_tot_idle_समय = bfqq->tot_idle_समय;
	bic->saved_in_large_burst = bfq_bfqq_in_large_burst(bfqq);
	bic->was_in_burst_list = !hlist_unhashed(&bfqq->burst_list_node);
	अगर (unlikely(bfq_bfqq_just_created(bfqq) &&
		     !bfq_bfqq_in_large_burst(bfqq) &&
		     bfqq->bfqd->low_latency)) अणु
		/*
		 * bfqq being merged right after being created: bfqq
		 * would have deserved पूर्णांकeractive weight raising, but
		 * did not make it to be set in a weight-उठाओd state,
		 * because of this early merge.	Store directly the
		 * weight-raising state that would have been asचिन्हित
		 * to bfqq, so that to aव्योम that bfqq unjustly fails
		 * to enjoy weight raising अगर split soon.
		 */
		bic->saved_wr_coeff = bfqq->bfqd->bfq_wr_coeff;
		bic->saved_wr_start_at_चयन_to_srt = bfq_smallest_from_now();
		bic->saved_wr_cur_max_समय = bfq_wr_duration(bfqq->bfqd);
		bic->saved_last_wr_start_finish = jअगरfies;
	पूर्ण अन्यथा अणु
		bic->saved_wr_coeff = bfqq->wr_coeff;
		bic->saved_wr_start_at_चयन_to_srt =
			bfqq->wr_start_at_चयन_to_srt;
		bic->saved_service_from_wr = bfqq->service_from_wr;
		bic->saved_last_wr_start_finish = bfqq->last_wr_start_finish;
		bic->saved_wr_cur_max_समय = bfqq->wr_cur_max_समय;
	पूर्ण
पूर्ण


अटल व्योम
bfq_reassign_last_bfqq(काष्ठा bfq_queue *cur_bfqq, काष्ठा bfq_queue *new_bfqq)
अणु
	अगर (cur_bfqq->entity.parent &&
	    cur_bfqq->entity.parent->last_bfqq_created == cur_bfqq)
		cur_bfqq->entity.parent->last_bfqq_created = new_bfqq;
	अन्यथा अगर (cur_bfqq->bfqd && cur_bfqq->bfqd->last_bfqq_created == cur_bfqq)
		cur_bfqq->bfqd->last_bfqq_created = new_bfqq;
पूर्ण

व्योम bfq_release_process_ref(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	/*
	 * To prevent bfqq's service guarantees from being violated,
	 * bfqq may be left busy, i.e., queued क्रम service, even अगर
	 * empty (see comments in __bfq_bfqq_expire() क्रम
	 * details). But, अगर no process will send requests to bfqq any
	 * दीर्घer, then there is no poपूर्णांक in keeping bfqq queued क्रम
	 * service. In addition, keeping bfqq queued क्रम service, but
	 * with no process ref any दीर्घer, may have caused bfqq to be
	 * मुक्तd when dequeued from service. But this is assumed to
	 * never happen.
	 */
	अगर (bfq_bfqq_busy(bfqq) && RB_EMPTY_ROOT(&bfqq->sort_list) &&
	    bfqq != bfqd->in_service_queue)
		bfq_del_bfqq_busy(bfqd, bfqq, false);

	bfq_reassign_last_bfqq(bfqq, शून्य);

	bfq_put_queue(bfqq);
पूर्ण

अटल व्योम
bfq_merge_bfqqs(काष्ठा bfq_data *bfqd, काष्ठा bfq_io_cq *bic,
		काष्ठा bfq_queue *bfqq, काष्ठा bfq_queue *new_bfqq)
अणु
	bfq_log_bfqq(bfqd, bfqq, "merging with queue %lu",
		(अचिन्हित दीर्घ)new_bfqq->pid);
	/* Save weight raising and idle winकरोw of the merged queues */
	bfq_bfqq_save_state(bfqq);
	bfq_bfqq_save_state(new_bfqq);
	अगर (bfq_bfqq_IO_bound(bfqq))
		bfq_mark_bfqq_IO_bound(new_bfqq);
	bfq_clear_bfqq_IO_bound(bfqq);

	/*
	 * The processes associated with bfqq are coचालकs of the
	 * processes associated with new_bfqq. So, अगर bfqq has a
	 * waker, then assume that all these processes will be happy
	 * to let bfqq's waker मुक्तly inject I/O when they have no
	 * I/O.
	 */
	अगर (bfqq->waker_bfqq && !new_bfqq->waker_bfqq &&
	    bfqq->waker_bfqq != new_bfqq) अणु
		new_bfqq->waker_bfqq = bfqq->waker_bfqq;
		new_bfqq->tentative_waker_bfqq = शून्य;

		/*
		 * If the waker queue disappears, then
		 * new_bfqq->waker_bfqq must be reset. So insert
		 * new_bfqq पूर्णांकo the woken_list of the waker. See
		 * bfq_check_waker क्रम details.
		 */
		hlist_add_head(&new_bfqq->woken_list_node,
			       &new_bfqq->waker_bfqq->woken_list);

	पूर्ण

	/*
	 * If bfqq is weight-उठाओd, then let new_bfqq inherit
	 * weight-raising. To reduce false positives, neglect the हाल
	 * where bfqq has just been created, but has not yet made it
	 * to be weight-उठाओd (which may happen because EQM may merge
	 * bfqq even beक्रमe bfq_add_request is executed क्रम the first
	 * समय क्रम bfqq). Handling this हाल would however be very
	 * easy, thanks to the flag just_created.
	 */
	अगर (new_bfqq->wr_coeff == 1 && bfqq->wr_coeff > 1) अणु
		new_bfqq->wr_coeff = bfqq->wr_coeff;
		new_bfqq->wr_cur_max_समय = bfqq->wr_cur_max_समय;
		new_bfqq->last_wr_start_finish = bfqq->last_wr_start_finish;
		new_bfqq->wr_start_at_चयन_to_srt =
			bfqq->wr_start_at_चयन_to_srt;
		अगर (bfq_bfqq_busy(new_bfqq))
			bfqd->wr_busy_queues++;
		new_bfqq->entity.prio_changed = 1;
	पूर्ण

	अगर (bfqq->wr_coeff > 1) अणु /* bfqq has given its wr to new_bfqq */
		bfqq->wr_coeff = 1;
		bfqq->entity.prio_changed = 1;
		अगर (bfq_bfqq_busy(bfqq))
			bfqd->wr_busy_queues--;
	पूर्ण

	bfq_log_bfqq(bfqd, new_bfqq, "merge_bfqqs: wr_busy %d",
		     bfqd->wr_busy_queues);

	/*
	 * Merge queues (that is, let bic redirect its requests to new_bfqq)
	 */
	bic_set_bfqq(bic, new_bfqq, 1);
	bfq_mark_bfqq_coop(new_bfqq);
	/*
	 * new_bfqq now beदीर्घs to at least two bics (it is a shared queue):
	 * set new_bfqq->bic to शून्य. bfqq either:
	 * - करोes not beदीर्घ to any bic any more, and hence bfqq->bic must
	 *   be set to शून्य, or
	 * - is a queue whose owning bics have alपढ़ोy been redirected to a
	 *   dअगरferent queue, hence the queue is destined to not beदीर्घ to
	 *   any bic soon and bfqq->bic is alपढ़ोy शून्य (thereक्रमe the next
	 *   assignment causes no harm).
	 */
	new_bfqq->bic = शून्य;
	/*
	 * If the queue is shared, the pid is the pid of one of the associated
	 * processes. Which pid depends on the exact sequence of merge events
	 * the queue underwent. So prपूर्णांकing such a pid is useless and confusing
	 * because it reports a अक्रमom pid between those of the associated
	 * processes.
	 * We mark such a queue with a pid -1, and then prपूर्णांक SHARED instead of
	 * a pid in logging messages.
	 */
	new_bfqq->pid = -1;
	bfqq->bic = शून्य;

	bfq_reassign_last_bfqq(bfqq, new_bfqq);

	bfq_release_process_ref(bfqd, bfqq);
पूर्ण

अटल bool bfq_allow_bio_merge(काष्ठा request_queue *q, काष्ठा request *rq,
				काष्ठा bio *bio)
अणु
	काष्ठा bfq_data *bfqd = q->elevator->elevator_data;
	bool is_sync = op_is_sync(bio->bi_opf);
	काष्ठा bfq_queue *bfqq = bfqd->bio_bfqq, *new_bfqq;

	/*
	 * Disallow merge of a sync bio पूर्णांकo an async request.
	 */
	अगर (is_sync && !rq_is_sync(rq))
		वापस false;

	/*
	 * Lookup the bfqq that this bio will be queued with. Allow
	 * merge only अगर rq is queued there.
	 */
	अगर (!bfqq)
		वापस false;

	/*
	 * We take advantage of this function to perक्रमm an early merge
	 * of the queues of possible cooperating processes.
	 */
	new_bfqq = bfq_setup_coचालक(bfqd, bfqq, bio, false, bfqd->bio_bic);
	अगर (new_bfqq) अणु
		/*
		 * bic still poपूर्णांकs to bfqq, then it has not yet been
		 * redirected to some other bfq_queue, and a queue
		 * merge between bfqq and new_bfqq can be safely
		 * fulfilled, i.e., bic can be redirected to new_bfqq
		 * and bfqq can be put.
		 */
		bfq_merge_bfqqs(bfqd, bfqd->bio_bic, bfqq,
				new_bfqq);
		/*
		 * If we get here, bio will be queued पूर्णांकo new_queue,
		 * so use new_bfqq to decide whether bio and rq can be
		 * merged.
		 */
		bfqq = new_bfqq;

		/*
		 * Change also bqfd->bio_bfqq, as
		 * bfqd->bio_bic now poपूर्णांकs to new_bfqq, and
		 * this function may be invoked again (and then may
		 * use again bqfd->bio_bfqq).
		 */
		bfqd->bio_bfqq = bfqq;
	पूर्ण

	वापस bfqq == RQ_BFQQ(rq);
पूर्ण

/*
 * Set the maximum समय क्रम the in-service queue to consume its
 * budget. This prevents seeky processes from lowering the throughput.
 * In practice, a समय-slice service scheme is used with seeky
 * processes.
 */
अटल व्योम bfq_set_budget_समयout(काष्ठा bfq_data *bfqd,
				   काष्ठा bfq_queue *bfqq)
अणु
	अचिन्हित पूर्णांक समयout_coeff;

	अगर (bfqq->wr_cur_max_समय == bfqd->bfq_wr_rt_max_समय)
		समयout_coeff = 1;
	अन्यथा
		समयout_coeff = bfqq->entity.weight / bfqq->entity.orig_weight;

	bfqd->last_budget_start = kसमय_get();

	bfqq->budget_समयout = jअगरfies +
		bfqd->bfq_समयout * समयout_coeff;
पूर्ण

अटल व्योम __bfq_set_in_service_queue(काष्ठा bfq_data *bfqd,
				       काष्ठा bfq_queue *bfqq)
अणु
	अगर (bfqq) अणु
		bfq_clear_bfqq_fअगरo_expire(bfqq);

		bfqd->budमाला_लो_asचिन्हित = (bfqd->budमाला_लो_asचिन्हित * 7 + 256) / 8;

		अगर (समय_is_beक्रमe_jअगरfies(bfqq->last_wr_start_finish) &&
		    bfqq->wr_coeff > 1 &&
		    bfqq->wr_cur_max_समय == bfqd->bfq_wr_rt_max_समय &&
		    समय_is_beक्रमe_jअगरfies(bfqq->budget_समयout)) अणु
			/*
			 * For soft real-समय queues, move the start
			 * of the weight-raising period क्रमward by the
			 * समय the queue has not received any
			 * service. Otherwise, a relatively दीर्घ
			 * service delay is likely to cause the
			 * weight-raising period of the queue to end,
			 * because of the लघु duration of the
			 * weight-raising period of a soft real-समय
			 * queue.  It is worth noting that this move
			 * is not so dangerous क्रम the other queues,
			 * because soft real-समय queues are not
			 * greedy.
			 *
			 * To not add a further variable, we use the
			 * overloaded field budget_समयout to
			 * determine क्रम how दीर्घ the queue has not
			 * received service, i.e., how much समय has
			 * elapsed since the queue expired. However,
			 * this is a little imprecise, because
			 * budget_समयout is set to jअगरfies अगर bfqq
			 * not only expires, but also reमुख्यs with no
			 * request.
			 */
			अगर (समय_after(bfqq->budget_समयout,
				       bfqq->last_wr_start_finish))
				bfqq->last_wr_start_finish +=
					jअगरfies - bfqq->budget_समयout;
			अन्यथा
				bfqq->last_wr_start_finish = jअगरfies;
		पूर्ण

		bfq_set_budget_समयout(bfqd, bfqq);
		bfq_log_bfqq(bfqd, bfqq,
			     "set_in_service_queue, cur-budget = %d",
			     bfqq->entity.budget);
	पूर्ण

	bfqd->in_service_queue = bfqq;
	bfqd->in_serv_last_pos = 0;
पूर्ण

/*
 * Get and set a new queue क्रम service.
 */
अटल काष्ठा bfq_queue *bfq_set_in_service_queue(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा bfq_queue *bfqq = bfq_get_next_queue(bfqd);

	__bfq_set_in_service_queue(bfqd, bfqq);
	वापस bfqq;
पूर्ण

अटल व्योम bfq_arm_slice_समयr(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा bfq_queue *bfqq = bfqd->in_service_queue;
	u32 sl;

	bfq_mark_bfqq_रुको_request(bfqq);

	/*
	 * We करोn't want to idle क्रम seeks, but we करो want to allow
	 * fair distribution of slice समय क्रम a process करोing back-to-back
	 * seeks. So allow a little bit of समय क्रम him to submit a new rq.
	 */
	sl = bfqd->bfq_slice_idle;
	/*
	 * Unless the queue is being weight-उठाओd or the scenario is
	 * asymmetric, grant only minimum idle समय अगर the queue
	 * is seeky. A दीर्घ idling is preserved क्रम a weight-उठाओd
	 * queue, or, more in general, in an asymmetric scenario,
	 * because a दीर्घ idling is needed क्रम guaranteeing to a queue
	 * its reserved share of the throughput (in particular, it is
	 * needed अगर the queue has a higher weight than some other
	 * queue).
	 */
	अगर (BFQQ_SEEKY(bfqq) && bfqq->wr_coeff == 1 &&
	    !bfq_asymmetric_scenario(bfqd, bfqq))
		sl = min_t(u64, sl, BFQ_MIN_TT);
	अन्यथा अगर (bfqq->wr_coeff > 1)
		sl = max_t(u32, sl, 20ULL * NSEC_PER_MSEC);

	bfqd->last_idling_start = kसमय_get();
	bfqd->last_idling_start_jअगरfies = jअगरfies;

	hrसमयr_start(&bfqd->idle_slice_समयr, ns_to_kसमय(sl),
		      HRTIMER_MODE_REL);
	bfqg_stats_set_start_idle_समय(bfqq_group(bfqq));
पूर्ण

/*
 * In स्वतःtuning mode, max_budget is dynamically recomputed as the
 * amount of sectors transferred in समयout at the estimated peak
 * rate. This enables BFQ to utilize a full बारlice with a full
 * budget, even अगर the in-service queue is served at peak rate. And
 * this maximises throughput with sequential workloads.
 */
अटल अचिन्हित दीर्घ bfq_calc_max_budget(काष्ठा bfq_data *bfqd)
अणु
	वापस (u64)bfqd->peak_rate * USEC_PER_MSEC *
		jअगरfies_to_msecs(bfqd->bfq_समयout)>>BFQ_RATE_SHIFT;
पूर्ण

/*
 * Update parameters related to throughput and responsiveness, as a
 * function of the estimated peak rate. See comments on
 * bfq_calc_max_budget(), and on the ref_wr_duration array.
 */
अटल व्योम update_thr_responsiveness_params(काष्ठा bfq_data *bfqd)
अणु
	अगर (bfqd->bfq_user_max_budget == 0) अणु
		bfqd->bfq_max_budget =
			bfq_calc_max_budget(bfqd);
		bfq_log(bfqd, "new max_budget = %d", bfqd->bfq_max_budget);
	पूर्ण
पूर्ण

अटल व्योम bfq_reset_rate_computation(काष्ठा bfq_data *bfqd,
				       काष्ठा request *rq)
अणु
	अगर (rq != शून्य) अणु /* new rq dispatch now, reset accordingly */
		bfqd->last_dispatch = bfqd->first_dispatch = kसमय_get_ns();
		bfqd->peak_rate_samples = 1;
		bfqd->sequential_samples = 0;
		bfqd->tot_sectors_dispatched = bfqd->last_rq_max_size =
			blk_rq_sectors(rq);
	पूर्ण अन्यथा /* no new rq dispatched, just reset the number of samples */
		bfqd->peak_rate_samples = 0; /* full re-init on next disp. */

	bfq_log(bfqd,
		"reset_rate_computation at end, sample %u/%u tot_sects %llu",
		bfqd->peak_rate_samples, bfqd->sequential_samples,
		bfqd->tot_sectors_dispatched);
पूर्ण

अटल व्योम bfq_update_rate_reset(काष्ठा bfq_data *bfqd, काष्ठा request *rq)
अणु
	u32 rate, weight, भागisor;

	/*
	 * For the convergence property to hold (see comments on
	 * bfq_update_peak_rate()) and क्रम the assessment to be
	 * reliable, a minimum number of samples must be present, and
	 * a minimum amount of समय must have elapsed. If not so, करो
	 * not compute new rate. Just reset parameters, to get पढ़ोy
	 * क्रम a new evaluation attempt.
	 */
	अगर (bfqd->peak_rate_samples < BFQ_RATE_MIN_SAMPLES ||
	    bfqd->delta_from_first < BFQ_RATE_MIN_INTERVAL)
		जाओ reset_computation;

	/*
	 * If a new request completion has occurred after last
	 * dispatch, then, to approximate the rate at which requests
	 * have been served by the device, it is more precise to
	 * extend the observation पूर्णांकerval to the last completion.
	 */
	bfqd->delta_from_first =
		max_t(u64, bfqd->delta_from_first,
		      bfqd->last_completion - bfqd->first_dispatch);

	/*
	 * Rate computed in sects/usec, and not sects/nsec, क्रम
	 * precision issues.
	 */
	rate = भाग64_ul(bfqd->tot_sectors_dispatched<<BFQ_RATE_SHIFT,
			भाग_u64(bfqd->delta_from_first, NSEC_PER_USEC));

	/*
	 * Peak rate not updated अगर:
	 * - the percentage of sequential dispatches is below 3/4 of the
	 *   total, and rate is below the current estimated peak rate
	 * - rate is unreasonably high (> 20M sectors/sec)
	 */
	अगर ((bfqd->sequential_samples < (3 * bfqd->peak_rate_samples)>>2 &&
	     rate <= bfqd->peak_rate) ||
		rate > 20<<BFQ_RATE_SHIFT)
		जाओ reset_computation;

	/*
	 * We have to update the peak rate, at last! To this purpose,
	 * we use a low-pass filter. We compute the smoothing स्थिरant
	 * of the filter as a function of the 'weight' of the new
	 * measured rate.
	 *
	 * As can be seen in next क्रमmulas, we define this weight as a
	 * quantity proportional to how sequential the workload is,
	 * and to how दीर्घ the observation समय पूर्णांकerval is.
	 *
	 * The weight runs from 0 to 8. The maximum value of the
	 * weight, 8, yields the minimum value क्रम the smoothing
	 * स्थिरant. At this minimum value क्रम the smoothing स्थिरant,
	 * the measured rate contributes क्रम half of the next value of
	 * the estimated peak rate.
	 *
	 * So, the first step is to compute the weight as a function
	 * of how sequential the workload is. Note that the weight
	 * cannot reach 9, because bfqd->sequential_samples cannot
	 * become equal to bfqd->peak_rate_samples, which, in its
	 * turn, holds true because bfqd->sequential_samples is not
	 * incremented क्रम the first sample.
	 */
	weight = (9 * bfqd->sequential_samples) / bfqd->peak_rate_samples;

	/*
	 * Second step: further refine the weight as a function of the
	 * duration of the observation पूर्णांकerval.
	 */
	weight = min_t(u32, 8,
		       भाग_u64(weight * bfqd->delta_from_first,
			       BFQ_RATE_REF_INTERVAL));

	/*
	 * Divisor ranging from 10, क्रम minimum weight, to 2, क्रम
	 * maximum weight.
	 */
	भागisor = 10 - weight;

	/*
	 * Finally, update peak rate:
	 *
	 * peak_rate = peak_rate * (भागisor-1) / भागisor  +  rate / भागisor
	 */
	bfqd->peak_rate *= भागisor-1;
	bfqd->peak_rate /= भागisor;
	rate /= भागisor; /* smoothing स्थिरant alpha = 1/भागisor */

	bfqd->peak_rate += rate;

	/*
	 * For a very slow device, bfqd->peak_rate can reach 0 (see
	 * the minimum representable values reported in the comments
	 * on BFQ_RATE_SHIFT). Push to 1 अगर this happens, to aव्योम
	 * भागisions by zero where bfqd->peak_rate is used as a
	 * भागisor.
	 */
	bfqd->peak_rate = max_t(u32, 1, bfqd->peak_rate);

	update_thr_responsiveness_params(bfqd);

reset_computation:
	bfq_reset_rate_computation(bfqd, rq);
पूर्ण

/*
 * Update the पढ़ो/ग_लिखो peak rate (the मुख्य quantity used क्रम
 * स्वतः-tuning, see update_thr_responsiveness_params()).
 *
 * It is not trivial to estimate the peak rate (correctly): because of
 * the presence of sw and hw queues between the scheduler and the
 * device components that finally serve I/O requests, it is hard to
 * say exactly when a given dispatched request is served inside the
 * device, and क्रम how दीर्घ. As a consequence, it is hard to know
 * precisely at what rate a given set of requests is actually served
 * by the device.
 *
 * On the opposite end, the dispatch समय of any request is trivially
 * available, and, from this piece of inक्रमmation, the "dispatch rate"
 * of requests can be immediately computed. So, the idea in the next
 * function is to use what is known, namely request dispatch बार
 * (plus, when useful, request completion बार), to estimate what is
 * unknown, namely in-device request service rate.
 *
 * The मुख्य issue is that, because of the above facts, the rate at
 * which a certain set of requests is dispatched over a certain समय
 * पूर्णांकerval can vary greatly with respect to the rate at which the
 * same requests are then served. But, since the size of any
 * पूर्णांकermediate queue is limited, and the service scheme is lossless
 * (no request is silently dropped), the following obvious convergence
 * property holds: the number of requests dispatched MUST become
 * बंदr and बंदr to the number of requests completed as the
 * observation पूर्णांकerval grows. This is the key property used in
 * the next function to estimate the peak service rate as a function
 * of the observed dispatch rate. The function assumes to be invoked
 * on every request dispatch.
 */
अटल व्योम bfq_update_peak_rate(काष्ठा bfq_data *bfqd, काष्ठा request *rq)
अणु
	u64 now_ns = kसमय_get_ns();

	अगर (bfqd->peak_rate_samples == 0) अणु /* first dispatch */
		bfq_log(bfqd, "update_peak_rate: goto reset, samples %d",
			bfqd->peak_rate_samples);
		bfq_reset_rate_computation(bfqd, rq);
		जाओ update_last_values; /* will add one sample */
	पूर्ण

	/*
	 * Device idle क्रम very दीर्घ: the observation पूर्णांकerval lasting
	 * up to this dispatch cannot be a valid observation पूर्णांकerval
	 * क्रम computing a new peak rate (similarly to the late-
	 * completion event in bfq_completed_request()). Go to
	 * update_rate_and_reset to have the following three steps
	 * taken:
	 * - बंद the observation पूर्णांकerval at the last (previous)
	 *   request dispatch or completion
	 * - compute rate, अगर possible, क्रम that observation पूर्णांकerval
	 * - start a new observation पूर्णांकerval with this dispatch
	 */
	अगर (now_ns - bfqd->last_dispatch > 100*NSEC_PER_MSEC &&
	    bfqd->rq_in_driver == 0)
		जाओ update_rate_and_reset;

	/* Update sampling inक्रमmation */
	bfqd->peak_rate_samples++;

	अगर ((bfqd->rq_in_driver > 0 ||
		now_ns - bfqd->last_completion < BFQ_MIN_TT)
	    && !BFQ_RQ_SEEKY(bfqd, bfqd->last_position, rq))
		bfqd->sequential_samples++;

	bfqd->tot_sectors_dispatched += blk_rq_sectors(rq);

	/* Reset max observed rq size every 32 dispatches */
	अगर (likely(bfqd->peak_rate_samples % 32))
		bfqd->last_rq_max_size =
			max_t(u32, blk_rq_sectors(rq), bfqd->last_rq_max_size);
	अन्यथा
		bfqd->last_rq_max_size = blk_rq_sectors(rq);

	bfqd->delta_from_first = now_ns - bfqd->first_dispatch;

	/* Target observation पूर्णांकerval not yet reached, go on sampling */
	अगर (bfqd->delta_from_first < BFQ_RATE_REF_INTERVAL)
		जाओ update_last_values;

update_rate_and_reset:
	bfq_update_rate_reset(bfqd, rq);
update_last_values:
	bfqd->last_position = blk_rq_pos(rq) + blk_rq_sectors(rq);
	अगर (RQ_BFQQ(rq) == bfqd->in_service_queue)
		bfqd->in_serv_last_pos = bfqd->last_position;
	bfqd->last_dispatch = now_ns;
पूर्ण

/*
 * Remove request from पूर्णांकernal lists.
 */
अटल व्योम bfq_dispatch_हटाओ(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	काष्ठा bfq_queue *bfqq = RQ_BFQQ(rq);

	/*
	 * For consistency, the next inकाष्ठाion should have been
	 * executed after removing the request from the queue and
	 * dispatching it.  We execute instead this inकाष्ठाion beक्रमe
	 * bfq_हटाओ_request() (and hence पूर्णांकroduce a temporary
	 * inconsistency), क्रम efficiency.  In fact, should this
	 * dispatch occur क्रम a non in-service bfqq, this anticipated
	 * increment prevents two counters related to bfqq->dispatched
	 * from risking to be, first, uselessly decremented, and then
	 * incremented again when the (new) value of bfqq->dispatched
	 * happens to be taken पूर्णांकo account.
	 */
	bfqq->dispatched++;
	bfq_update_peak_rate(q->elevator->elevator_data, rq);

	bfq_हटाओ_request(q, rq);
पूर्ण

/*
 * There is a हाल where idling करोes not have to be perक्रमmed क्रम
 * throughput concerns, but to preserve the throughput share of
 * the process associated with bfqq.
 *
 * To पूर्णांकroduce this हाल, we can note that allowing the drive
 * to enqueue more than one request at a समय, and hence
 * delegating de facto final scheduling decisions to the
 * drive's पूर्णांकernal scheduler, entails loss of control on the
 * actual request service order. In particular, the critical
 * situation is when requests from dअगरferent processes happen
 * to be present, at the same समय, in the पूर्णांकernal queue(s)
 * of the drive. In such a situation, the drive, by deciding
 * the service order of the पूर्णांकernally-queued requests, करोes
 * determine also the actual throughput distribution among
 * these processes. But the drive typically has no notion or
 * concern about per-process throughput distribution, and
 * makes its decisions only on a per-request basis. Thereक्रमe,
 * the service distribution enक्रमced by the drive's पूर्णांकernal
 * scheduler is likely to coincide with the desired throughput
 * distribution only in a completely symmetric, or favorably
 * skewed scenario where:
 * (i-a) each of these processes must get the same throughput as
 *	 the others,
 * (i-b) in हाल (i-a) करोes not hold, it holds that the process
 *       associated with bfqq must receive a lower or equal
 *	 throughput than any of the other processes;
 * (ii)  the I/O of each process has the same properties, in
 *       terms of locality (sequential or अक्रमom), direction
 *       (पढ़ोs or ग_लिखोs), request sizes, greediness
 *       (from I/O-bound to sporadic), and so on;

 * In fact, in such a scenario, the drive tends to treat the requests
 * of each process in about the same way as the requests of the
 * others, and thus to provide each of these processes with about the
 * same throughput.  This is exactly the desired throughput
 * distribution अगर (i-a) holds, or, अगर (i-b) holds instead, this is an
 * even more convenient distribution क्रम (the process associated with)
 * bfqq.
 *
 * In contrast, in any asymmetric or unfavorable scenario, device
 * idling (I/O-dispatch plugging) is certainly needed to guarantee
 * that bfqq receives its asचिन्हित fraction of the device throughput
 * (see [1] क्रम details).
 *
 * The problem is that idling may signअगरicantly reduce throughput with
 * certain combinations of types of I/O and devices. An important
 * example is sync अक्रमom I/O on flash storage with command
 * queueing. So, unless bfqq falls in हालs where idling also boosts
 * throughput, it is important to check conditions (i-a), i(-b) and
 * (ii) accurately, so as to aव्योम idling when not strictly needed क्रम
 * service guarantees.
 *
 * Unक्रमtunately, it is extremely dअगरficult to thoroughly check
 * condition (ii). And, in हाल there are active groups, it becomes
 * very dअगरficult to check conditions (i-a) and (i-b) too.  In fact,
 * अगर there are active groups, then, क्रम conditions (i-a) or (i-b) to
 * become false 'indirectly', it is enough that an active group
 * contains more active processes or sub-groups than some other active
 * group. More precisely, क्रम conditions (i-a) or (i-b) to become
 * false because of such a group, it is not even necessary that the
 * group is (still) active: it is sufficient that, even अगर the group
 * has become inactive, some of its descendant processes still have
 * some request alपढ़ोy dispatched but still रुकोing क्रम
 * completion. In fact, requests have still to be guaranteed their
 * share of the throughput even after being dispatched. In this
 * respect, it is easy to show that, अगर a group frequently becomes
 * inactive जबतक still having in-flight requests, and अगर, when this
 * happens, the group is not considered in the calculation of whether
 * the scenario is asymmetric, then the group may fail to be
 * guaranteed its fair share of the throughput (basically because
 * idling may not be perक्रमmed क्रम the descendant processes of the
 * group, but it had to be).  We address this issue with the following
 * bi-modal behavior, implemented in the function
 * bfq_asymmetric_scenario().
 *
 * If there are groups with requests रुकोing क्रम completion
 * (as commented above, some of these groups may even be
 * alपढ़ोy inactive), then the scenario is tagged as
 * asymmetric, conservatively, without checking any of the
 * conditions (i-a), (i-b) or (ii). So the device is idled क्रम bfqq.
 * This behavior matches also the fact that groups are created
 * exactly अगर controlling I/O is a primary concern (to
 * preserve bandwidth and latency guarantees).
 *
 * On the opposite end, अगर there are no groups with requests रुकोing
 * क्रम completion, then only conditions (i-a) and (i-b) are actually
 * controlled, i.e., provided that conditions (i-a) or (i-b) holds,
 * idling is not perक्रमmed, regardless of whether condition (ii)
 * holds.  In other words, only अगर conditions (i-a) and (i-b) करो not
 * hold, then idling is allowed, and the device tends to be prevented
 * from queueing many requests, possibly of several processes. Since
 * there are no groups with requests रुकोing क्रम completion, then, to
 * control conditions (i-a) and (i-b) it is enough to check just
 * whether all the queues with requests रुकोing क्रम completion also
 * have the same weight.
 *
 * Not checking condition (ii) evidently exposes bfqq to the
 * risk of getting less throughput than its fair share.
 * However, क्रम queues with the same weight, a further
 * mechanism, preemption, mitigates or even eliminates this
 * problem. And it करोes so without consequences on overall
 * throughput. This mechanism and its benefits are explained
 * in the next three paragraphs.
 *
 * Even अगर a queue, say Q, is expired when it reमुख्यs idle, Q
 * can still preempt the new in-service queue अगर the next
 * request of Q arrives soon (see the comments on
 * bfq_bfqq_update_budg_क्रम_activation). If all queues and
 * groups have the same weight, this क्रमm of preemption,
 * combined with the hole-recovery heuristic described in the
 * comments on function bfq_bfqq_update_budg_क्रम_activation,
 * are enough to preserve a correct bandwidth distribution in
 * the mid term, even without idling. In fact, even अगर not
 * idling allows the पूर्णांकernal queues of the device to contain
 * many requests, and thus to reorder requests, we can rather
 * safely assume that the पूर्णांकernal scheduler still preserves a
 * minimum of mid-term fairness.
 *
 * More precisely, this preemption-based, idleless approach
 * provides fairness in terms of IOPS, and not sectors per
 * second. This can be seen with a simple example. Suppose
 * that there are two queues with the same weight, but that
 * the first queue receives requests of 8 sectors, जबतक the
 * second queue receives requests of 1024 sectors. In
 * addition, suppose that each of the two queues contains at
 * most one request at a समय, which implies that each queue
 * always reमुख्यs idle after it is served. Finally, after
 * reमुख्यing idle, each queue receives very quickly a new
 * request. It follows that the two queues are served
 * alternatively, preempting each other अगर needed. This
 * implies that, although both queues have the same weight,
 * the queue with large requests receives a service that is
 * 1024/8 बार as high as the service received by the other
 * queue.
 *
 * The motivation क्रम using preemption instead of idling (क्रम
 * queues with the same weight) is that, by not idling,
 * service guarantees are preserved (completely or at least in
 * part) without minimally sacrअगरicing throughput. And, अगर
 * there is no active group, then the primary expectation क्रम
 * this device is probably a high throughput.
 *
 * We are now left only with explaining the two sub-conditions in the
 * additional compound condition that is checked below क्रम deciding
 * whether the scenario is asymmetric. To explain the first
 * sub-condition, we need to add that the function
 * bfq_asymmetric_scenario checks the weights of only
 * non-weight-उठाओd queues, क्रम efficiency reasons (see comments on
 * bfq_weights_tree_add()). Then the fact that bfqq is weight-उठाओd
 * is checked explicitly here. More precisely, the compound condition
 * below takes पूर्णांकo account also the fact that, even अगर bfqq is being
 * weight-उठाओd, the scenario is still symmetric अगर all queues with
 * requests रुकोing क्रम completion happen to be
 * weight-उठाओd. Actually, we should be even more precise here, and
 * dअगरferentiate between पूर्णांकeractive weight raising and soft real-समय
 * weight raising.
 *
 * The second sub-condition checked in the compound condition is
 * whether there is a fair amount of alपढ़ोy in-flight I/O not
 * beदीर्घing to bfqq. If so, I/O dispatching is to be plugged, क्रम the
 * following reason. The drive may decide to serve in-flight
 * non-bfqq's I/O requests before bfqq's ones, thereby delaying the
 * arrival of new I/O requests क्रम bfqq (recall that bfqq is sync). If
 * I/O-dispatching is not plugged, then, जबतक bfqq reमुख्यs empty, a
 * basically uncontrolled amount of I/O from other queues may be
 * dispatched too, possibly causing the service of bfqq's I/O to be
 * delayed even दीर्घer in the drive. This problem माला_लो more and more
 * serious as the speed and the queue depth of the drive grow,
 * because, as these two quantities grow, the probability to find no
 * queue busy but many requests in flight grows too. By contrast,
 * plugging I/O dispatching minimizes the delay induced by alपढ़ोy
 * in-flight I/O, and enables bfqq to recover the bandwidth it may
 * lose because of this delay.
 *
 * As a side note, it is worth considering that the above
 * device-idling countermeasures may however fail in the following
 * unlucky scenario: अगर I/O-dispatch plugging is (correctly) disabled
 * in a समय period during which all symmetry sub-conditions hold, and
 * thereक्रमe the device is allowed to enqueue many requests, but at
 * some later poपूर्णांक in समय some sub-condition stops to hold, then it
 * may become impossible to make requests be served in the desired
 * order until all the requests alपढ़ोy queued in the device have been
 * served. The last sub-condition commented above somewhat mitigates
 * this problem क्रम weight-उठाओd queues.
 *
 * However, as an additional mitigation क्रम this problem, we preserve
 * plugging क्रम a special symmetric हाल that may suddenly turn पूर्णांकo
 * asymmetric: the हाल where only bfqq is busy. In this हाल, not
 * expiring bfqq करोes not cause any harm to any other queues in terms
 * of service guarantees. In contrast, it aव्योमs the following unlucky
 * sequence of events: (1) bfqq is expired, (2) a new queue with a
 * lower weight than bfqq becomes busy (or more queues), (3) the new
 * queue is served until a new request arrives क्रम bfqq, (4) when bfqq
 * is finally served, there are so many requests of the new queue in
 * the drive that the pending requests क्रम bfqq take a lot of समय to
 * be served. In particular, event (2) may हाल even alपढ़ोy
 * dispatched requests of bfqq to be delayed, inside the drive. So, to
 * aव्योम this series of events, the scenario is preventively declared
 * as asymmetric also अगर bfqq is the only busy queues
 */
अटल bool idling_needed_क्रम_service_guarantees(काष्ठा bfq_data *bfqd,
						 काष्ठा bfq_queue *bfqq)
अणु
	पूर्णांक tot_busy_queues = bfq_tot_busy_queues(bfqd);

	/* No poपूर्णांक in idling क्रम bfqq अगर it won't get requests any दीर्घer */
	अगर (unlikely(!bfqq_process_refs(bfqq)))
		वापस false;

	वापस (bfqq->wr_coeff > 1 &&
		(bfqd->wr_busy_queues <
		 tot_busy_queues ||
		 bfqd->rq_in_driver >=
		 bfqq->dispatched + 4)) ||
		bfq_asymmetric_scenario(bfqd, bfqq) ||
		tot_busy_queues == 1;
पूर्ण

अटल bool __bfq_bfqq_expire(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			      क्रमागत bfqq_expiration reason)
अणु
	/*
	 * If this bfqq is shared between multiple processes, check
	 * to make sure that those processes are still issuing I/Os
	 * within the mean seek distance. If not, it may be समय to
	 * अवरोध the queues apart again.
	 */
	अगर (bfq_bfqq_coop(bfqq) && BFQQ_SEEKY(bfqq))
		bfq_mark_bfqq_split_coop(bfqq);

	/*
	 * Consider queues with a higher finish भव समय than
	 * bfqq. If idling_needed_क्रम_service_guarantees(bfqq) वापसs
	 * true, then bfqq's bandwidth would be violated अगर an
	 * uncontrolled amount of I/O from these queues were
	 * dispatched जबतक bfqq is रुकोing क्रम its new I/O to
	 * arrive. This is exactly what may happen अगर this is a क्रमced
	 * expiration caused by a preemption attempt, and अगर bfqq is
	 * not re-scheduled. To prevent this from happening, re-queue
	 * bfqq अगर it needs I/O-dispatch plugging, even अगर it is
	 * empty. By करोing so, bfqq is granted to be served beक्रमe the
	 * above queues (provided that bfqq is of course eligible).
	 */
	अगर (RB_EMPTY_ROOT(&bfqq->sort_list) &&
	    !(reason == BFQQE_PREEMPTED &&
	      idling_needed_क्रम_service_guarantees(bfqd, bfqq))) अणु
		अगर (bfqq->dispatched == 0)
			/*
			 * Overloading budget_समयout field to store
			 * the समय at which the queue reमुख्यs with no
			 * backlog and no outstanding request; used by
			 * the weight-raising mechanism.
			 */
			bfqq->budget_समयout = jअगरfies;

		bfq_del_bfqq_busy(bfqd, bfqq, true);
	पूर्ण अन्यथा अणु
		bfq_requeue_bfqq(bfqd, bfqq, true);
		/*
		 * Resort priority tree of potential बंद coचालकs.
		 * See comments on bfq_pos_tree_add_move() क्रम the unlikely().
		 */
		अगर (unlikely(!bfqd->nonrot_with_queueing &&
			     !RB_EMPTY_ROOT(&bfqq->sort_list)))
			bfq_pos_tree_add_move(bfqd, bfqq);
	पूर्ण

	/*
	 * All in-service entities must have been properly deactivated
	 * or requeued beक्रमe executing the next function, which
	 * resets all in-service entities as no more in service. This
	 * may cause bfqq to be मुक्तd. If this happens, the next
	 * function वापसs true.
	 */
	वापस __bfq_bfqd_reset_in_service(bfqd);
पूर्ण

/**
 * __bfq_bfqq_recalc_budget - try to adapt the budget to the @bfqq behavior.
 * @bfqd: device data.
 * @bfqq: queue to update.
 * @reason: reason क्रम expiration.
 *
 * Handle the feedback on @bfqq budget at queue expiration.
 * See the body क्रम detailed comments.
 */
अटल व्योम __bfq_bfqq_recalc_budget(काष्ठा bfq_data *bfqd,
				     काष्ठा bfq_queue *bfqq,
				     क्रमागत bfqq_expiration reason)
अणु
	काष्ठा request *next_rq;
	पूर्णांक budget, min_budget;

	min_budget = bfq_min_budget(bfqd);

	अगर (bfqq->wr_coeff == 1)
		budget = bfqq->max_budget;
	अन्यथा /*
	      * Use a स्थिरant, low budget क्रम weight-उठाओd queues,
	      * to help achieve a low latency. Keep it slightly higher
	      * than the minimum possible budget, to cause a little
	      * bit fewer expirations.
	      */
		budget = 2 * min_budget;

	bfq_log_bfqq(bfqd, bfqq, "recalc_budg: last budg %d, budg left %d",
		bfqq->entity.budget, bfq_bfqq_budget_left(bfqq));
	bfq_log_bfqq(bfqd, bfqq, "recalc_budg: last max_budg %d, min budg %d",
		budget, bfq_min_budget(bfqd));
	bfq_log_bfqq(bfqd, bfqq, "recalc_budg: sync %d, seeky %d",
		bfq_bfqq_sync(bfqq), BFQQ_SEEKY(bfqd->in_service_queue));

	अगर (bfq_bfqq_sync(bfqq) && bfqq->wr_coeff == 1) अणु
		चयन (reason) अणु
		/*
		 * Caveat: in all the following हालs we trade latency
		 * क्रम throughput.
		 */
		हाल BFQQE_TOO_IDLE:
			/*
			 * This is the only हाल where we may reduce
			 * the budget: अगर there is no request of the
			 * process still रुकोing क्रम completion, then
			 * we assume (tentatively) that the समयr has
			 * expired because the batch of requests of
			 * the process could have been served with a
			 * smaller budget.  Hence, betting that
			 * process will behave in the same way when it
			 * becomes backlogged again, we reduce its
			 * next budget.  As दीर्घ as we guess right,
			 * this budget cut reduces the latency
			 * experienced by the process.
			 *
			 * However, अगर there are still outstanding
			 * requests, then the process may have not yet
			 * issued its next request just because it is
			 * still रुकोing क्रम the completion of some of
			 * the still outstanding ones.  So in this
			 * subहाल we करो not reduce its budget, on the
			 * contrary we increase it to possibly boost
			 * the throughput, as discussed in the
			 * comments to the BUDGET_TIMEOUT हाल.
			 */
			अगर (bfqq->dispatched > 0) /* still outstanding reqs */
				budget = min(budget * 2, bfqd->bfq_max_budget);
			अन्यथा अणु
				अगर (budget > 5 * min_budget)
					budget -= 4 * min_budget;
				अन्यथा
					budget = min_budget;
			पूर्ण
			अवरोध;
		हाल BFQQE_BUDGET_TIMEOUT:
			/*
			 * We द्विगुन the budget here because it gives
			 * the chance to boost the throughput अगर this
			 * is not a seeky process (and has bumped पूर्णांकo
			 * this समयout because of, e.g., ZBR).
			 */
			budget = min(budget * 2, bfqd->bfq_max_budget);
			अवरोध;
		हाल BFQQE_BUDGET_EXHAUSTED:
			/*
			 * The process still has backlog, and did not
			 * let either the budget समयout or the disk
			 * idling समयout expire. Hence it is not
			 * seeky, has a लघु thinkसमय and may be
			 * happy with a higher budget too. So
			 * definitely increase the budget of this good
			 * candidate to boost the disk throughput.
			 */
			budget = min(budget * 4, bfqd->bfq_max_budget);
			अवरोध;
		हाल BFQQE_NO_MORE_REQUESTS:
			/*
			 * For queues that expire क्रम this reason, it
			 * is particularly important to keep the
			 * budget बंद to the actual service they
			 * need. Doing so reduces the बारtamp
			 * misalignment problem described in the
			 * comments in the body of
			 * __bfq_activate_entity. In fact, suppose
			 * that a queue प्रणालीatically expires क्रम
			 * BFQQE_NO_MORE_REQUESTS and presents a
			 * new request in समय to enjoy बारtamp
			 * back-shअगरting. The larger the budget of the
			 * queue is with respect to the service the
			 * queue actually requests in each service
			 * slot, the more बार the queue can be
			 * reactivated with the same भव finish
			 * समय. It follows that, even अगर this finish
			 * समय is pushed to the प्रणाली भव समय
			 * to reduce the consequent बारtamp
			 * misalignment, the queue unjustly enjoys क्रम
			 * many re-activations a lower finish समय
			 * than all newly activated queues.
			 *
			 * The service needed by bfqq is measured
			 * quite precisely by bfqq->entity.service.
			 * Since bfqq करोes not enjoy device idling,
			 * bfqq->entity.service is equal to the number
			 * of sectors that the process associated with
			 * bfqq requested to पढ़ो/ग_लिखो beक्रमe रुकोing
			 * क्रम request completions, or blocking क्रम
			 * other reasons.
			 */
			budget = max_t(पूर्णांक, bfqq->entity.service, min_budget);
			अवरोध;
		शेष:
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (!bfq_bfqq_sync(bfqq)) अणु
		/*
		 * Async queues get always the maximum possible
		 * budget, as क्रम them we करो not care about latency
		 * (in addition, their ability to dispatch is limited
		 * by the अक्षरging factor).
		 */
		budget = bfqd->bfq_max_budget;
	पूर्ण

	bfqq->max_budget = budget;

	अगर (bfqd->budमाला_लो_asचिन्हित >= bfq_stats_min_budमाला_लो &&
	    !bfqd->bfq_user_max_budget)
		bfqq->max_budget = min(bfqq->max_budget, bfqd->bfq_max_budget);

	/*
	 * If there is still backlog, then assign a new budget, making
	 * sure that it is large enough क्रम the next request.  Since
	 * the finish समय of bfqq must be kept in sync with the
	 * budget, be sure to call __bfq_bfqq_expire() *after* this
	 * update.
	 *
	 * If there is no backlog, then no need to update the budget;
	 * it will be updated on the arrival of a new request.
	 */
	next_rq = bfqq->next_rq;
	अगर (next_rq)
		bfqq->entity.budget = max_t(अचिन्हित दीर्घ, bfqq->max_budget,
					    bfq_serv_to_अक्षरge(next_rq, bfqq));

	bfq_log_bfqq(bfqd, bfqq, "head sect: %u, new budget %d",
			next_rq ? blk_rq_sectors(next_rq) : 0,
			bfqq->entity.budget);
पूर्ण

/*
 * Return true अगर the process associated with bfqq is "slow". The slow
 * flag is used, in addition to the budget समयout, to reduce the
 * amount of service provided to seeky processes, and thus reduce
 * their chances to lower the throughput. More details in the comments
 * on the function bfq_bfqq_expire().
 *
 * An important observation is in order: as discussed in the comments
 * on the function bfq_update_peak_rate(), with devices with पूर्णांकernal
 * queues, it is hard अगर ever possible to know when and क्रम how दीर्घ
 * an I/O request is processed by the device (apart from the trivial
 * I/O pattern where a new request is dispatched only after the
 * previous one has been completed). This makes it hard to evaluate
 * the real rate at which the I/O requests of each bfq_queue are
 * served.  In fact, क्रम an I/O scheduler like BFQ, serving a
 * bfq_queue means just dispatching its requests during its service
 * slot (i.e., until the budget of the queue is exhausted, or the
 * queue reमुख्यs idle, or, finally, a समयout fires). But, during the
 * service slot of a bfq_queue, around 100 ms at most, the device may
 * be even still processing requests of bfq_queues served in previous
 * service slots. On the opposite end, the requests of the in-service
 * bfq_queue may be completed after the service slot of the queue
 * finishes.
 *
 * Anyway, unless more sophisticated solutions are used
 * (where possible), the sum of the sizes of the requests dispatched
 * during the service slot of a bfq_queue is probably the only
 * approximation available क्रम the service received by the bfq_queue
 * during its service slot. And this sum is the quantity used in this
 * function to evaluate the I/O speed of a process.
 */
अटल bool bfq_bfqq_is_slow(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
				 bool compensate, क्रमागत bfqq_expiration reason,
				 अचिन्हित दीर्घ *delta_ms)
अणु
	kसमय_प्रकार delta_kसमय;
	u32 delta_usecs;
	bool slow = BFQQ_SEEKY(bfqq); /* अगर delta too लघु, use seekyness */

	अगर (!bfq_bfqq_sync(bfqq))
		वापस false;

	अगर (compensate)
		delta_kसमय = bfqd->last_idling_start;
	अन्यथा
		delta_kसमय = kसमय_get();
	delta_kसमय = kसमय_sub(delta_kसमय, bfqd->last_budget_start);
	delta_usecs = kसमय_प्रकारo_us(delta_kसमय);

	/* करोn't use too लघु समय पूर्णांकervals */
	अगर (delta_usecs < 1000) अणु
		अगर (blk_queue_nonrot(bfqd->queue))
			 /*
			  * give same worst-हाल guarantees as idling
			  * क्रम seeky
			  */
			*delta_ms = BFQ_MIN_TT / NSEC_PER_MSEC;
		अन्यथा /* अक्षरge at least one seek */
			*delta_ms = bfq_slice_idle / NSEC_PER_MSEC;

		वापस slow;
	पूर्ण

	*delta_ms = delta_usecs / USEC_PER_MSEC;

	/*
	 * Use only दीर्घ (> 20ms) पूर्णांकervals to filter out excessive
	 * spikes in service rate estimation.
	 */
	अगर (delta_usecs > 20000) अणु
		/*
		 * Caveat क्रम rotational devices: processes करोing I/O
		 * in the slower disk zones tend to be slow(er) even
		 * अगर not seeky. In this respect, the estimated peak
		 * rate is likely to be an average over the disk
		 * surface. Accordingly, to not be too harsh with
		 * unlucky processes, a process is deemed slow only अगर
		 * its rate has been lower than half of the estimated
		 * peak rate.
		 */
		slow = bfqq->entity.service < bfqd->bfq_max_budget / 2;
	पूर्ण

	bfq_log_bfqq(bfqd, bfqq, "bfq_bfqq_is_slow: slow %d", slow);

	वापस slow;
पूर्ण

/*
 * To be deemed as soft real-समय, an application must meet two
 * requirements. First, the application must not require an average
 * bandwidth higher than the approximate bandwidth required to playback or
 * record a compressed high-definition video.
 * The next function is invoked on the completion of the last request of a
 * batch, to compute the next-start समय instant, soft_rt_next_start, such
 * that, अगर the next request of the application करोes not arrive beक्रमe
 * soft_rt_next_start, then the above requirement on the bandwidth is met.
 *
 * The second requirement is that the request pattern of the application is
 * isochronous, i.e., that, after issuing a request or a batch of requests,
 * the application stops issuing new requests until all its pending requests
 * have been completed. After that, the application may issue a new batch,
 * and so on.
 * For this reason the next function is invoked to compute
 * soft_rt_next_start only क्रम applications that meet this requirement,
 * whereas soft_rt_next_start is set to infinity क्रम applications that करो
 * not.
 *
 * Unक्रमtunately, even a greedy (i.e., I/O-bound) application may
 * happen to meet, occasionally or प्रणालीatically, both the above
 * bandwidth and isochrony requirements. This may happen at least in
 * the following circumstances. First, अगर the CPU load is high. The
 * application may stop issuing requests जबतक the CPUs are busy
 * serving other processes, then restart, then stop again क्रम a जबतक,
 * and so on. The other circumstances are related to the storage
 * device: the storage device is highly loaded or reaches a low-enough
 * throughput with the I/O of the application (e.g., because the I/O
 * is अक्रमom and/or the device is slow). In all these हालs, the
 * I/O of the application may be simply slowed करोwn enough to meet
 * the bandwidth and isochrony requirements. To reduce the probability
 * that greedy applications are deemed as soft real-समय in these
 * corner हालs, a further rule is used in the computation of
 * soft_rt_next_start: the वापस value of this function is क्रमced to
 * be higher than the maximum between the following two quantities.
 *
 * (a) Current समय plus: (1) the maximum समय क्रम which the arrival
 *     of a request is रुकोed क्रम when a sync queue becomes idle,
 *     namely bfqd->bfq_slice_idle, and (2) a few extra jअगरfies. We
 *     postpone क्रम a moment the reason क्रम adding a few extra
 *     jअगरfies; we get back to it after next item (b).  Lower-bounding
 *     the वापस value of this function with the current समय plus
 *     bfqd->bfq_slice_idle tends to filter out greedy applications,
 *     because the latter issue their next request as soon as possible
 *     after the last one has been completed. In contrast, a soft
 *     real-समय application spends some समय processing data, after a
 *     batch of its requests has been completed.
 *
 * (b) Current value of bfqq->soft_rt_next_start. As poपूर्णांकed out
 *     above, greedy applications may happen to meet both the
 *     bandwidth and isochrony requirements under heavy CPU or
 *     storage-device load. In more detail, in these scenarios, these
 *     applications happen, only क्रम limited समय periods, to करो I/O
 *     slowly enough to meet all the requirements described so far,
 *     including the filtering in above item (a). These slow-speed
 *     समय पूर्णांकervals are usually पूर्णांकerspersed between other समय
 *     पूर्णांकervals during which these applications करो I/O at a very high
 *     speed. Fortunately, exactly because of the high speed of the
 *     I/O in the high-speed पूर्णांकervals, the values वापसed by this
 *     function happen to be so high, near the end of any such
 *     high-speed पूर्णांकerval, to be likely to fall *after* the end of
 *     the low-speed समय पूर्णांकerval that follows. These high values are
 *     stored in bfqq->soft_rt_next_start after each invocation of
 *     this function. As a consequence, अगर the last value of
 *     bfqq->soft_rt_next_start is स्थिरantly used to lower-bound the
 *     next value that this function may वापस, then, from the very
 *     beginning of a low-speed पूर्णांकerval, bfqq->soft_rt_next_start is
 *     likely to be स्थिरantly kept so high that any I/O request
 *     issued during the low-speed पूर्णांकerval is considered as arriving
 *     to soon क्रम the application to be deemed as soft
 *     real-समय. Then, in the high-speed पूर्णांकerval that follows, the
 *     application will not be deemed as soft real-समय, just because
 *     it will करो I/O at a high speed. And so on.
 *
 * Getting back to the filtering in item (a), in the following two
 * हालs this filtering might be easily passed by a greedy
 * application, अगर the reference quantity was just
 * bfqd->bfq_slice_idle:
 * 1) HZ is so low that the duration of a jअगरfy is comparable to or
 *    higher than bfqd->bfq_slice_idle. This happens, e.g., on slow
 *    devices with HZ=100. The समय granularity may be so coarse
 *    that the approximation, in jअगरfies, of bfqd->bfq_slice_idle
 *    is rather lower than the exact value.
 * 2) jअगरfies, instead of increasing at a स्थिरant rate, may stop increasing
 *    क्रम a जबतक, then suddenly 'jump' by several units to recover the lost
 *    increments. This seems to happen, e.g., inside भव machines.
 * To address this issue, in the filtering in (a) we करो not use as a
 * reference समय पूर्णांकerval just bfqd->bfq_slice_idle, but
 * bfqd->bfq_slice_idle plus a few jअगरfies. In particular, we add the
 * minimum number of jअगरfies क्रम which the filter seems to be quite
 * precise also in embedded प्रणालीs and KVM/QEMU भव machines.
 */
अटल अचिन्हित दीर्घ bfq_bfqq_softrt_next_start(काष्ठा bfq_data *bfqd,
						काष्ठा bfq_queue *bfqq)
अणु
	वापस max3(bfqq->soft_rt_next_start,
		    bfqq->last_idle_bklogged +
		    HZ * bfqq->service_from_backlogged /
		    bfqd->bfq_wr_max_softrt_rate,
		    jअगरfies + nsecs_to_jअगरfies(bfqq->bfqd->bfq_slice_idle) + 4);
पूर्ण

/**
 * bfq_bfqq_expire - expire a queue.
 * @bfqd: device owning the queue.
 * @bfqq: the queue to expire.
 * @compensate: अगर true, compensate क्रम the समय spent idling.
 * @reason: the reason causing the expiration.
 *
 * If the process associated with bfqq करोes slow I/O (e.g., because it
 * issues अक्रमom requests), we अक्षरge bfqq with the समय it has been
 * in service instead of the service it has received (see
 * bfq_bfqq_अक्षरge_समय क्रम details on how this goal is achieved). As
 * a consequence, bfqq will typically get higher बारtamps upon
 * reactivation, and hence it will be rescheduled as अगर it had
 * received more service than what it has actually received. In the
 * end, bfqq receives less service in proportion to how slowly its
 * associated process consumes its budमाला_लो (and hence how seriously it
 * tends to lower the throughput). In addition, this समय-अक्षरging
 * strategy guarantees समय fairness among slow processes. In
 * contrast, अगर the process associated with bfqq is not slow, we
 * अक्षरge bfqq exactly with the service it has received.
 *
 * Charging समय to the first type of queues and the exact service to
 * the other has the effect of using the WF2Q+ policy to schedule the
 * क्रमmer on a बारlice basis, without violating service करोमुख्य
 * guarantees among the latter.
 */
व्योम bfq_bfqq_expire(काष्ठा bfq_data *bfqd,
		     काष्ठा bfq_queue *bfqq,
		     bool compensate,
		     क्रमागत bfqq_expiration reason)
अणु
	bool slow;
	अचिन्हित दीर्घ delta = 0;
	काष्ठा bfq_entity *entity = &bfqq->entity;

	/*
	 * Check whether the process is slow (see bfq_bfqq_is_slow).
	 */
	slow = bfq_bfqq_is_slow(bfqd, bfqq, compensate, reason, &delta);

	/*
	 * As above explained, अक्षरge slow (typically seeky) and
	 * समयd-out queues with the समय and not the service
	 * received, to favor sequential workloads.
	 *
	 * Processes करोing I/O in the slower disk zones will tend to
	 * be slow(er) even अगर not seeky. Thereक्रमe, since the
	 * estimated peak rate is actually an average over the disk
	 * surface, these processes may समयout just क्रम bad luck. To
	 * aव्योम punishing them, करो not अक्षरge समय to processes that
	 * succeeded in consuming at least 2/3 of their budget. This
	 * allows BFQ to preserve enough elasticity to still perक्रमm
	 * bandwidth, and not समय, distribution with little unlucky
	 * or quasi-sequential processes.
	 */
	अगर (bfqq->wr_coeff == 1 &&
	    (slow ||
	     (reason == BFQQE_BUDGET_TIMEOUT &&
	      bfq_bfqq_budget_left(bfqq) >=  entity->budget / 3)))
		bfq_bfqq_अक्षरge_समय(bfqd, bfqq, delta);

	अगर (bfqd->low_latency && bfqq->wr_coeff == 1)
		bfqq->last_wr_start_finish = jअगरfies;

	अगर (bfqd->low_latency && bfqd->bfq_wr_max_softrt_rate > 0 &&
	    RB_EMPTY_ROOT(&bfqq->sort_list)) अणु
		/*
		 * If we get here, and there are no outstanding
		 * requests, then the request pattern is isochronous
		 * (see the comments on the function
		 * bfq_bfqq_softrt_next_start()). Thereक्रमe we can
		 * compute soft_rt_next_start.
		 *
		 * If, instead, the queue still has outstanding
		 * requests, then we have to रुको क्रम the completion
		 * of all the outstanding requests to discover whether
		 * the request pattern is actually isochronous.
		 */
		अगर (bfqq->dispatched == 0)
			bfqq->soft_rt_next_start =
				bfq_bfqq_softrt_next_start(bfqd, bfqq);
		अन्यथा अगर (bfqq->dispatched > 0) अणु
			/*
			 * Schedule an update of soft_rt_next_start to when
			 * the task may be discovered to be isochronous.
			 */
			bfq_mark_bfqq_softrt_update(bfqq);
		पूर्ण
	पूर्ण

	bfq_log_bfqq(bfqd, bfqq,
		"expire (%d, slow %d, num_disp %d, short_ttime %d)", reason,
		slow, bfqq->dispatched, bfq_bfqq_has_लघु_tसमय(bfqq));

	/*
	 * bfqq expired, so no total service समय needs to be computed
	 * any दीर्घer: reset state machine क्रम measuring total service
	 * बार.
	 */
	bfqd->rqs_injected = bfqd->रुको_dispatch = false;
	bfqd->रुकोed_rq = शून्य;

	/*
	 * Increase, decrease or leave budget unchanged according to
	 * reason.
	 */
	__bfq_bfqq_recalc_budget(bfqd, bfqq, reason);
	अगर (__bfq_bfqq_expire(bfqd, bfqq, reason))
		/* bfqq is gone, no more actions on it */
		वापस;

	/* mark bfqq as रुकोing a request only अगर a bic still poपूर्णांकs to it */
	अगर (!bfq_bfqq_busy(bfqq) &&
	    reason != BFQQE_BUDGET_TIMEOUT &&
	    reason != BFQQE_BUDGET_EXHAUSTED) अणु
		bfq_mark_bfqq_non_blocking_रुको_rq(bfqq);
		/*
		 * Not setting service to 0, because, अगर the next rq
		 * arrives in समय, the queue will go on receiving
		 * service with this same budget (as अगर it never expired)
		 */
	पूर्ण अन्यथा
		entity->service = 0;

	/*
	 * Reset the received-service counter क्रम every parent entity.
	 * Dअगरferently from what happens with bfqq->entity.service,
	 * the resetting of this counter never needs to be postponed
	 * क्रम parent entities. In fact, in हाल bfqq may have a
	 * chance to go on being served using the last, partially
	 * consumed budget, bfqq->entity.service needs to be kept,
	 * because अगर bfqq then actually goes on being served using
	 * the same budget, the last value of bfqq->entity.service is
	 * needed to properly decrement bfqq->entity.budget by the
	 * portion alपढ़ोy consumed. In contrast, it is not necessary
	 * to keep entity->service क्रम parent entities too, because
	 * the bubble up of the new value of bfqq->entity.budget will
	 * make sure that the budमाला_लो of parent entities are correct,
	 * even in हाल bfqq and thus parent entities go on receiving
	 * service with the same budget.
	 */
	entity = entity->parent;
	क्रम_each_entity(entity)
		entity->service = 0;
पूर्ण

/*
 * Budget समयout is not implemented through a dedicated समयr, but
 * just checked on request arrivals and completions, as well as on
 * idle समयr expirations.
 */
अटल bool bfq_bfqq_budget_समयout(काष्ठा bfq_queue *bfqq)
अणु
	वापस समय_is_beक्रमe_eq_jअगरfies(bfqq->budget_समयout);
पूर्ण

/*
 * If we expire a queue that is actively रुकोing (i.e., with the
 * device idled) क्रम the arrival of a new request, then we may incur
 * the बारtamp misalignment problem described in the body of the
 * function __bfq_activate_entity. Hence we वापस true only अगर this
 * condition करोes not hold, or अगर the queue is slow enough to deserve
 * only to be kicked off क्रम preserving a high throughput.
 */
अटल bool bfq_may_expire_क्रम_budg_समयout(काष्ठा bfq_queue *bfqq)
अणु
	bfq_log_bfqq(bfqq->bfqd, bfqq,
		"may_budget_timeout: wait_request %d left %d timeout %d",
		bfq_bfqq_रुको_request(bfqq),
			bfq_bfqq_budget_left(bfqq) >=  bfqq->entity.budget / 3,
		bfq_bfqq_budget_समयout(bfqq));

	वापस (!bfq_bfqq_रुको_request(bfqq) ||
		bfq_bfqq_budget_left(bfqq) >=  bfqq->entity.budget / 3)
		&&
		bfq_bfqq_budget_समयout(bfqq);
पूर्ण

अटल bool idling_boosts_thr_without_issues(काष्ठा bfq_data *bfqd,
					     काष्ठा bfq_queue *bfqq)
अणु
	bool rot_without_queueing =
		!blk_queue_nonrot(bfqd->queue) && !bfqd->hw_tag,
		bfqq_sequential_and_IO_bound,
		idling_boosts_thr;

	/* No poपूर्णांक in idling क्रम bfqq अगर it won't get requests any दीर्घer */
	अगर (unlikely(!bfqq_process_refs(bfqq)))
		वापस false;

	bfqq_sequential_and_IO_bound = !BFQQ_SEEKY(bfqq) &&
		bfq_bfqq_IO_bound(bfqq) && bfq_bfqq_has_लघु_tसमय(bfqq);

	/*
	 * The next variable takes पूर्णांकo account the हालs where idling
	 * boosts the throughput.
	 *
	 * The value of the variable is computed considering, first, that
	 * idling is भवly always beneficial क्रम the throughput अगर:
	 * (a) the device is not NCQ-capable and rotational, or
	 * (b) regardless of the presence of NCQ, the device is rotational and
	 *     the request pattern क्रम bfqq is I/O-bound and sequential, or
	 * (c) regardless of whether it is rotational, the device is
	 *     not NCQ-capable and the request pattern क्रम bfqq is
	 *     I/O-bound and sequential.
	 *
	 * Secondly, and in contrast to the above item (b), idling an
	 * NCQ-capable flash-based device would not boost the
	 * throughput even with sequential I/O; rather it would lower
	 * the throughput in proportion to how fast the device
	 * is. Accordingly, the next variable is true अगर any of the
	 * above conditions (a), (b) or (c) is true, and, in
	 * particular, happens to be false अगर bfqd is an NCQ-capable
	 * flash-based device.
	 */
	idling_boosts_thr = rot_without_queueing ||
		((!blk_queue_nonrot(bfqd->queue) || !bfqd->hw_tag) &&
		 bfqq_sequential_and_IO_bound);

	/*
	 * The वापस value of this function is equal to that of
	 * idling_boosts_thr, unless a special हाल holds. In this
	 * special हाल, described below, idling may cause problems to
	 * weight-उठाओd queues.
	 *
	 * When the request pool is saturated (e.g., in the presence
	 * of ग_लिखो hogs), अगर the processes associated with
	 * non-weight-उठाओd queues ask क्रम requests at a lower rate,
	 * then processes associated with weight-उठाओd queues have a
	 * higher probability to get a request from the pool
	 * immediately (or at least soon) when they need one. Thus
	 * they have a higher probability to actually get a fraction
	 * of the device throughput proportional to their high
	 * weight. This is especially true with NCQ-capable drives,
	 * which enqueue several requests in advance, and further
	 * reorder पूर्णांकernally-queued requests.
	 *
	 * For this reason, we क्रमce to false the वापस value अगर
	 * there are weight-उठाओd busy queues. In this हाल, and अगर
	 * bfqq is not weight-उठाओd, this guarantees that the device
	 * is not idled क्रम bfqq (अगर, instead, bfqq is weight-उठाओd,
	 * then idling will be guaranteed by another variable, see
	 * below). Combined with the बारtamping rules of BFQ (see
	 * [1] क्रम details), this behavior causes bfqq, and hence any
	 * sync non-weight-उठाओd queue, to get a lower number of
	 * requests served, and thus to ask क्रम a lower number of
	 * requests from the request pool, beक्रमe the busy
	 * weight-उठाओd queues get served again. This often mitigates
	 * starvation problems in the presence of heavy ग_लिखो
	 * workloads and NCQ, thereby guaranteeing a higher
	 * application and प्रणाली responsiveness in these hostile
	 * scenarios.
	 */
	वापस idling_boosts_thr &&
		bfqd->wr_busy_queues == 0;
पूर्ण

/*
 * For a queue that becomes empty, device idling is allowed only अगर
 * this function वापसs true क्रम that queue. As a consequence, since
 * device idling plays a critical role क्रम both throughput boosting
 * and service guarantees, the वापस value of this function plays a
 * critical role as well.
 *
 * In a nutshell, this function वापसs true only अगर idling is
 * beneficial क्रम throughput or, even अगर detrimental क्रम throughput,
 * idling is however necessary to preserve service guarantees (low
 * latency, desired throughput distribution, ...). In particular, on
 * NCQ-capable devices, this function tries to वापस false, so as to
 * help keep the drives' पूर्णांकernal queues full, whenever this helps the
 * device boost the throughput without causing any service-guarantee
 * issue.
 *
 * Most of the issues taken पूर्णांकo account to get the वापस value of
 * this function are not trivial. We discuss these issues in the two
 * functions providing the मुख्य pieces of inक्रमmation needed by this
 * function.
 */
अटल bool bfq_better_to_idle(काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_data *bfqd = bfqq->bfqd;
	bool idling_boosts_thr_with_no_issue, idling_needed_क्रम_service_guar;

	/* No poपूर्णांक in idling क्रम bfqq अगर it won't get requests any दीर्घer */
	अगर (unlikely(!bfqq_process_refs(bfqq)))
		वापस false;

	अगर (unlikely(bfqd->strict_guarantees))
		वापस true;

	/*
	 * Idling is perक्रमmed only अगर slice_idle > 0. In addition, we
	 * करो not idle अगर
	 * (a) bfqq is async
	 * (b) bfqq is in the idle io prio class: in this हाल we करो
	 * not idle because we want to minimize the bandwidth that
	 * queues in this class can steal to higher-priority queues
	 */
	अगर (bfqd->bfq_slice_idle == 0 || !bfq_bfqq_sync(bfqq) ||
	   bfq_class_idle(bfqq))
		वापस false;

	idling_boosts_thr_with_no_issue =
		idling_boosts_thr_without_issues(bfqd, bfqq);

	idling_needed_क्रम_service_guar =
		idling_needed_क्रम_service_guarantees(bfqd, bfqq);

	/*
	 * We have now the two components we need to compute the
	 * वापस value of the function, which is true only अगर idling
	 * either boosts the throughput (without issues), or is
	 * necessary to preserve service guarantees.
	 */
	वापस idling_boosts_thr_with_no_issue ||
		idling_needed_क्रम_service_guar;
पूर्ण

/*
 * If the in-service queue is empty but the function bfq_better_to_idle
 * वापसs true, then:
 * 1) the queue must reमुख्य in service and cannot be expired, and
 * 2) the device must be idled to रुको क्रम the possible arrival of a new
 *    request क्रम the queue.
 * See the comments on the function bfq_better_to_idle क्रम the reasons
 * why perक्रमming device idling is the best choice to boost the throughput
 * and preserve service guarantees when bfq_better_to_idle itself
 * वापसs true.
 */
अटल bool bfq_bfqq_must_idle(काष्ठा bfq_queue *bfqq)
अणु
	वापस RB_EMPTY_ROOT(&bfqq->sort_list) && bfq_better_to_idle(bfqq);
पूर्ण

/*
 * This function chooses the queue from which to pick the next extra
 * I/O request to inject, अगर it finds a compatible queue. See the
 * comments on bfq_update_inject_limit() क्रम details on the injection
 * mechanism, and क्रम the definitions of the quantities mentioned
 * below.
 */
अटल काष्ठा bfq_queue *
bfq_choose_bfqq_क्रम_injection(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा bfq_queue *bfqq, *in_serv_bfqq = bfqd->in_service_queue;
	अचिन्हित पूर्णांक limit = in_serv_bfqq->inject_limit;
	/*
	 * If
	 * - bfqq is not weight-उठाओd and thereक्रमe करोes not carry
	 *   समय-critical I/O,
	 * or
	 * - regardless of whether bfqq is weight-उठाओd, bfqq has
	 *   however a दीर्घ think समय, during which it can असलorb the
	 *   effect of an appropriate number of extra I/O requests
	 *   from other queues (see bfq_update_inject_limit क्रम
	 *   details on the computation of this number);
	 * then injection can be perक्रमmed without restrictions.
	 */
	bool in_serv_always_inject = in_serv_bfqq->wr_coeff == 1 ||
		!bfq_bfqq_has_लघु_tसमय(in_serv_bfqq);

	/*
	 * If
	 * - the baseline total service समय could not be sampled yet,
	 *   so the inject limit happens to be still 0, and
	 * - a lot of समय has elapsed since the plugging of I/O
	 *   dispatching started, so drive speed is being wasted
	 *   signअगरicantly;
	 * then temporarily उठाओ inject limit to one request.
	 */
	अगर (limit == 0 && in_serv_bfqq->last_serv_समय_ns == 0 &&
	    bfq_bfqq_रुको_request(in_serv_bfqq) &&
	    समय_is_beक्रमe_eq_jअगरfies(bfqd->last_idling_start_jअगरfies +
				      bfqd->bfq_slice_idle)
		)
		limit = 1;

	अगर (bfqd->rq_in_driver >= limit)
		वापस शून्य;

	/*
	 * Linear search of the source queue क्रम injection; but, with
	 * a high probability, very few steps are needed to find a
	 * candidate queue, i.e., a queue with enough budget left क्रम
	 * its next request. In fact:
	 * - BFQ dynamically updates the budget of every queue so as
	 *   to accommodate the expected backlog of the queue;
	 * - अगर a queue माला_लो all its requests dispatched as injected
	 *   service, then the queue is हटाओd from the active list
	 *   (and re-added only अगर it माला_लो new requests, but then it
	 *   is asचिन्हित again enough budget क्रम its new backlog).
	 */
	list_क्रम_each_entry(bfqq, &bfqd->active_list, bfqq_list)
		अगर (!RB_EMPTY_ROOT(&bfqq->sort_list) &&
		    (in_serv_always_inject || bfqq->wr_coeff > 1) &&
		    bfq_serv_to_अक्षरge(bfqq->next_rq, bfqq) <=
		    bfq_bfqq_budget_left(bfqq)) अणु
			/*
			 * Allow क्रम only one large in-flight request
			 * on non-rotational devices, क्रम the
			 * following reason. On non-rotationl drives,
			 * large requests take much दीर्घer than
			 * smaller requests to be served. In addition,
			 * the drive prefers to serve large requests
			 * w.r.t. to small ones, अगर it can choose. So,
			 * having more than one large requests queued
			 * in the drive may easily make the next first
			 * request of the in-service queue रुको क्रम so
			 * दीर्घ to अवरोध bfqq's service guarantees. On
			 * the bright side, large requests let the
			 * drive reach a very high throughput, even अगर
			 * there is only one in-flight large request
			 * at a समय.
			 */
			अगर (blk_queue_nonrot(bfqd->queue) &&
			    blk_rq_sectors(bfqq->next_rq) >=
			    BFQQ_SECT_THR_NONROT)
				limit = min_t(अचिन्हित पूर्णांक, 1, limit);
			अन्यथा
				limit = in_serv_bfqq->inject_limit;

			अगर (bfqd->rq_in_driver < limit) अणु
				bfqd->rqs_injected = true;
				वापस bfqq;
			पूर्ण
		पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Select a queue क्रम service.  If we have a current queue in service,
 * check whether to जारी servicing it, or retrieve and set a new one.
 */
अटल काष्ठा bfq_queue *bfq_select_queue(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा bfq_queue *bfqq;
	काष्ठा request *next_rq;
	क्रमागत bfqq_expiration reason = BFQQE_BUDGET_TIMEOUT;

	bfqq = bfqd->in_service_queue;
	अगर (!bfqq)
		जाओ new_queue;

	bfq_log_bfqq(bfqd, bfqq, "select_queue: already in-service queue");

	/*
	 * Do not expire bfqq क्रम budget समयout अगर bfqq may be about
	 * to enjoy device idling. The reason why, in this हाल, we
	 * prevent bfqq from expiring is the same as in the comments
	 * on the हाल where bfq_bfqq_must_idle() वापसs true, in
	 * bfq_completed_request().
	 */
	अगर (bfq_may_expire_क्रम_budg_समयout(bfqq) &&
	    !bfq_bfqq_must_idle(bfqq))
		जाओ expire;

check_queue:
	/*
	 * This loop is rarely executed more than once. Even when it
	 * happens, it is much more convenient to re-execute this loop
	 * than to वापस शून्य and trigger a new dispatch to get a
	 * request served.
	 */
	next_rq = bfqq->next_rq;
	/*
	 * If bfqq has requests queued and it has enough budget left to
	 * serve them, keep the queue, otherwise expire it.
	 */
	अगर (next_rq) अणु
		अगर (bfq_serv_to_अक्षरge(next_rq, bfqq) >
			bfq_bfqq_budget_left(bfqq)) अणु
			/*
			 * Expire the queue क्रम budget exhaustion,
			 * which makes sure that the next budget is
			 * enough to serve the next request, even अगर
			 * it comes from the fअगरo expired path.
			 */
			reason = BFQQE_BUDGET_EXHAUSTED;
			जाओ expire;
		पूर्ण अन्यथा अणु
			/*
			 * The idle समयr may be pending because we may
			 * not disable disk idling even when a new request
			 * arrives.
			 */
			अगर (bfq_bfqq_रुको_request(bfqq)) अणु
				/*
				 * If we get here: 1) at least a new request
				 * has arrived but we have not disabled the
				 * समयr because the request was too small,
				 * 2) then the block layer has unplugged
				 * the device, causing the dispatch to be
				 * invoked.
				 *
				 * Since the device is unplugged, now the
				 * requests are probably large enough to
				 * provide a reasonable throughput.
				 * So we disable idling.
				 */
				bfq_clear_bfqq_रुको_request(bfqq);
				hrसमयr_try_to_cancel(&bfqd->idle_slice_समयr);
			पूर्ण
			जाओ keep_queue;
		पूर्ण
	पूर्ण

	/*
	 * No requests pending. However, अगर the in-service queue is idling
	 * क्रम a new request, or has requests रुकोing क्रम a completion and
	 * may idle after their completion, then keep it anyway.
	 *
	 * Yet, inject service from other queues अगर it boosts
	 * throughput and is possible.
	 */
	अगर (bfq_bfqq_रुको_request(bfqq) ||
	    (bfqq->dispatched != 0 && bfq_better_to_idle(bfqq))) अणु
		काष्ठा bfq_queue *async_bfqq =
			bfqq->bic && bfqq->bic->bfqq[0] &&
			bfq_bfqq_busy(bfqq->bic->bfqq[0]) &&
			bfqq->bic->bfqq[0]->next_rq ?
			bfqq->bic->bfqq[0] : शून्य;
		काष्ठा bfq_queue *blocked_bfqq =
			!hlist_empty(&bfqq->woken_list) ?
			container_of(bfqq->woken_list.first,
				     काष्ठा bfq_queue,
				     woken_list_node)
			: शून्य;

		/*
		 * The next four mutually-exclusive अगरs decide
		 * whether to try injection, and choose the queue to
		 * pick an I/O request from.
		 *
		 * The first अगर checks whether the process associated
		 * with bfqq has also async I/O pending. If so, it
		 * injects such I/O unconditionally. Injecting async
		 * I/O from the same process can cause no harm to the
		 * process. On the contrary, it can only increase
		 * bandwidth and reduce latency क्रम the process.
		 *
		 * The second अगर checks whether there happens to be a
		 * non-empty waker queue क्रम bfqq, i.e., a queue whose
		 * I/O needs to be completed क्रम bfqq to receive new
		 * I/O. This happens, e.g., अगर bfqq is associated with
		 * a process that करोes some sync. A sync generates
		 * extra blocking I/O, which must be completed beक्रमe
		 * the process associated with bfqq can go on with its
		 * I/O. If the I/O of the waker queue is not served,
		 * then bfqq reमुख्यs empty, and no I/O is dispatched,
		 * until the idle समयout fires क्रम bfqq. This is
		 * likely to result in lower bandwidth and higher
		 * latencies क्रम bfqq, and in a severe loss of total
		 * throughput. The best action to take is thereक्रमe to
		 * serve the waker queue as soon as possible. So करो it
		 * (without relying on the third alternative below क्रम
		 * eventually serving waker_bfqq's I/O; see the last
		 * paragraph क्रम further details). This प्रणालीatic
		 * injection of I/O from the waker queue करोes not
		 * cause any delay to bfqq's I/O. On the contrary,
		 * next bfqq's I/O is brought क्रमward dramatically,
		 * क्रम it is not blocked क्रम milliseconds.
		 *
		 * The third अगर checks whether there is a queue woken
		 * by bfqq, and currently with pending I/O. Such a
		 * woken queue करोes not steal bandwidth from bfqq,
		 * because it reमुख्यs soon without I/O अगर bfqq is not
		 * served. So there is भवly no risk of loss of
		 * bandwidth क्रम bfqq अगर this woken queue has I/O
		 * dispatched जबतक bfqq is रुकोing क्रम new I/O.
		 *
		 * The fourth अगर checks whether bfqq is a queue क्रम
		 * which it is better to aव्योम injection. It is so अगर
		 * bfqq delivers more throughput when served without
		 * any further I/O from other queues in the middle, or
		 * अगर the service बार of bfqq's I/O requests both
		 * count more than overall throughput, and may be
		 * easily increased by injection (this happens अगर bfqq
		 * has a लघु think समय). If none of these
		 * conditions holds, then a candidate queue क्रम
		 * injection is looked क्रम through
		 * bfq_choose_bfqq_क्रम_injection(). Note that the
		 * latter may वापस शून्य (क्रम example अगर the inject
		 * limit क्रम bfqq is currently 0).
		 *
		 * NOTE: motivation क्रम the second alternative
		 *
		 * Thanks to the way the inject limit is updated in
		 * bfq_update_has_लघु_tसमय(), it is rather likely
		 * that, अगर I/O is being plugged क्रम bfqq and the
		 * waker queue has pending I/O requests that are
		 * blocking bfqq's I/O, then the fourth alternative
		 * above lets the waker queue get served beक्रमe the
		 * I/O-plugging समयout fires. So one may deem the
		 * second alternative superfluous. It is not, because
		 * the fourth alternative may be way less effective in
		 * हाल of a synchronization. For two मुख्य
		 * reasons. First, throughput may be low because the
		 * inject limit may be too low to guarantee the same
		 * amount of injected I/O, from the waker queue or
		 * other queues, that the second alternative
		 * guarantees (the second alternative unconditionally
		 * injects a pending I/O request of the waker queue
		 * क्रम each bfq_dispatch_request()). Second, with the
		 * fourth alternative, the duration of the plugging,
		 * i.e., the समय beक्रमe bfqq finally receives new I/O,
		 * may not be minimized, because the waker queue may
		 * happen to be served only after other queues.
		 */
		अगर (async_bfqq &&
		    icq_to_bic(async_bfqq->next_rq->elv.icq) == bfqq->bic &&
		    bfq_serv_to_अक्षरge(async_bfqq->next_rq, async_bfqq) <=
		    bfq_bfqq_budget_left(async_bfqq))
			bfqq = bfqq->bic->bfqq[0];
		अन्यथा अगर (bfqq->waker_bfqq &&
			   bfq_bfqq_busy(bfqq->waker_bfqq) &&
			   bfqq->waker_bfqq->next_rq &&
			   bfq_serv_to_अक्षरge(bfqq->waker_bfqq->next_rq,
					      bfqq->waker_bfqq) <=
			   bfq_bfqq_budget_left(bfqq->waker_bfqq)
			)
			bfqq = bfqq->waker_bfqq;
		अन्यथा अगर (blocked_bfqq &&
			   bfq_bfqq_busy(blocked_bfqq) &&
			   blocked_bfqq->next_rq &&
			   bfq_serv_to_अक्षरge(blocked_bfqq->next_rq,
					      blocked_bfqq) <=
			   bfq_bfqq_budget_left(blocked_bfqq)
			)
			bfqq = blocked_bfqq;
		अन्यथा अगर (!idling_boosts_thr_without_issues(bfqd, bfqq) &&
			 (bfqq->wr_coeff == 1 || bfqd->wr_busy_queues > 1 ||
			  !bfq_bfqq_has_लघु_tसमय(bfqq)))
			bfqq = bfq_choose_bfqq_क्रम_injection(bfqd);
		अन्यथा
			bfqq = शून्य;

		जाओ keep_queue;
	पूर्ण

	reason = BFQQE_NO_MORE_REQUESTS;
expire:
	bfq_bfqq_expire(bfqd, bfqq, false, reason);
new_queue:
	bfqq = bfq_set_in_service_queue(bfqd);
	अगर (bfqq) अणु
		bfq_log_bfqq(bfqd, bfqq, "select_queue: checking new queue");
		जाओ check_queue;
	पूर्ण
keep_queue:
	अगर (bfqq)
		bfq_log_bfqq(bfqd, bfqq, "select_queue: returned this queue");
	अन्यथा
		bfq_log(bfqd, "select_queue: no queue returned");

	वापस bfqq;
पूर्ण

अटल व्योम bfq_update_wr_data(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;

	अगर (bfqq->wr_coeff > 1) अणु /* queue is being weight-उठाओd */
		bfq_log_bfqq(bfqd, bfqq,
			"raising period dur %u/%u msec, old coeff %u, w %d(%d)",
			jअगरfies_to_msecs(jअगरfies - bfqq->last_wr_start_finish),
			jअगरfies_to_msecs(bfqq->wr_cur_max_समय),
			bfqq->wr_coeff,
			bfqq->entity.weight, bfqq->entity.orig_weight);

		अगर (entity->prio_changed)
			bfq_log_bfqq(bfqd, bfqq, "WARN: pending prio change");

		/*
		 * If the queue was activated in a burst, or too much
		 * समय has elapsed from the beginning of this
		 * weight-raising period, then end weight raising.
		 */
		अगर (bfq_bfqq_in_large_burst(bfqq))
			bfq_bfqq_end_wr(bfqq);
		अन्यथा अगर (समय_is_beक्रमe_jअगरfies(bfqq->last_wr_start_finish +
						bfqq->wr_cur_max_समय)) अणु
			अगर (bfqq->wr_cur_max_समय != bfqd->bfq_wr_rt_max_समय ||
			समय_is_beक्रमe_jअगरfies(bfqq->wr_start_at_चयन_to_srt +
					       bfq_wr_duration(bfqd))) अणु
				/*
				 * Either in पूर्णांकeractive weight
				 * raising, or in soft_rt weight
				 * raising with the
				 * पूर्णांकeractive-weight-raising period
				 * elapsed (so no चयन back to
				 * पूर्णांकeractive weight raising).
				 */
				bfq_bfqq_end_wr(bfqq);
			पूर्ण अन्यथा अणु /*
				  * soft_rt finishing जबतक still in
				  * पूर्णांकeractive period, चयन back to
				  * पूर्णांकeractive weight raising
				  */
				चयन_back_to_पूर्णांकeractive_wr(bfqq, bfqd);
				bfqq->entity.prio_changed = 1;
			पूर्ण
		पूर्ण
		अगर (bfqq->wr_coeff > 1 &&
		    bfqq->wr_cur_max_समय != bfqd->bfq_wr_rt_max_समय &&
		    bfqq->service_from_wr > max_service_from_wr) अणु
			/* see comments on max_service_from_wr */
			bfq_bfqq_end_wr(bfqq);
		पूर्ण
	पूर्ण
	/*
	 * To improve latency (क्रम this or other queues), immediately
	 * update weight both अगर it must be उठाओd and अगर it must be
	 * lowered. Since, entity may be on some active tree here, and
	 * might have a pending change of its ioprio class, invoke
	 * next function with the last parameter unset (see the
	 * comments on the function).
	 */
	अगर ((entity->weight > entity->orig_weight) != (bfqq->wr_coeff > 1))
		__bfq_entity_update_weight_prio(bfq_entity_service_tree(entity),
						entity, false);
पूर्ण

/*
 * Dispatch next request from bfqq.
 */
अटल काष्ठा request *bfq_dispatch_rq_from_bfqq(काष्ठा bfq_data *bfqd,
						 काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा request *rq = bfqq->next_rq;
	अचिन्हित दीर्घ service_to_अक्षरge;

	service_to_अक्षरge = bfq_serv_to_अक्षरge(rq, bfqq);

	bfq_bfqq_served(bfqq, service_to_अक्षरge);

	अगर (bfqq == bfqd->in_service_queue && bfqd->रुको_dispatch) अणु
		bfqd->रुको_dispatch = false;
		bfqd->रुकोed_rq = rq;
	पूर्ण

	bfq_dispatch_हटाओ(bfqd->queue, rq);

	अगर (bfqq != bfqd->in_service_queue)
		जाओ वापस_rq;

	/*
	 * If weight raising has to terminate क्रम bfqq, then next
	 * function causes an immediate update of bfqq's weight,
	 * without रुकोing क्रम next activation. As a consequence, on
	 * expiration, bfqq will be बारtamped as अगर has never been
	 * weight-उठाओd during this service slot, even अगर it has
	 * received part or even most of the service as a
	 * weight-उठाओd queue. This inflates bfqq's बारtamps, which
	 * is beneficial, as bfqq is then more willing to leave the
	 * device immediately to possible other weight-उठाओd queues.
	 */
	bfq_update_wr_data(bfqd, bfqq);

	/*
	 * Expire bfqq, pretending that its budget expired, अगर bfqq
	 * beदीर्घs to CLASS_IDLE and other queues are रुकोing क्रम
	 * service.
	 */
	अगर (!(bfq_tot_busy_queues(bfqd) > 1 && bfq_class_idle(bfqq)))
		जाओ वापस_rq;

	bfq_bfqq_expire(bfqd, bfqq, false, BFQQE_BUDGET_EXHAUSTED);

वापस_rq:
	वापस rq;
पूर्ण

अटल bool bfq_has_work(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा bfq_data *bfqd = hctx->queue->elevator->elevator_data;

	/*
	 * Aव्योमing lock: a race on bfqd->busy_queues should cause at
	 * most a call to dispatch क्रम nothing
	 */
	वापस !list_empty_careful(&bfqd->dispatch) ||
		bfq_tot_busy_queues(bfqd) > 0;
पूर्ण

अटल काष्ठा request *__bfq_dispatch_request(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा bfq_data *bfqd = hctx->queue->elevator->elevator_data;
	काष्ठा request *rq = शून्य;
	काष्ठा bfq_queue *bfqq = शून्य;

	अगर (!list_empty(&bfqd->dispatch)) अणु
		rq = list_first_entry(&bfqd->dispatch, काष्ठा request,
				      queuelist);
		list_del_init(&rq->queuelist);

		bfqq = RQ_BFQQ(rq);

		अगर (bfqq) अणु
			/*
			 * Increment counters here, because this
			 * dispatch करोes not follow the standard
			 * dispatch flow (where counters are
			 * incremented)
			 */
			bfqq->dispatched++;

			जाओ inc_in_driver_start_rq;
		पूर्ण

		/*
		 * We exploit the bfq_finish_requeue_request hook to
		 * decrement rq_in_driver, but
		 * bfq_finish_requeue_request will not be invoked on
		 * this request. So, to aव्योम unbalance, just start
		 * this request, without incrementing rq_in_driver. As
		 * a negative consequence, rq_in_driver is deceptively
		 * lower than it should be जबतक this request is in
		 * service. This may cause bfq_schedule_dispatch to be
		 * invoked uselessly.
		 *
		 * As क्रम implementing an exact solution, the
		 * bfq_finish_requeue_request hook, अगर defined, is
		 * probably invoked also on this request. So, by
		 * exploiting this hook, we could 1) increment
		 * rq_in_driver here, and 2) decrement it in
		 * bfq_finish_requeue_request. Such a solution would
		 * let the value of the counter be always accurate,
		 * but it would entail using an extra पूर्णांकerface
		 * function. This cost seems higher than the benefit,
		 * being the frequency of non-elevator-निजी
		 * requests very low.
		 */
		जाओ start_rq;
	पूर्ण

	bfq_log(bfqd, "dispatch requests: %d busy queues",
		bfq_tot_busy_queues(bfqd));

	अगर (bfq_tot_busy_queues(bfqd) == 0)
		जाओ निकास;

	/*
	 * Force device to serve one request at a समय अगर
	 * strict_guarantees is true. Forcing this service scheme is
	 * currently the ONLY way to guarantee that the request
	 * service order enक्रमced by the scheduler is respected by a
	 * queueing device. Otherwise the device is मुक्त even to make
	 * some unlucky request रुको क्रम as दीर्घ as the device
	 * wishes.
	 *
	 * Of course, serving one request at a समय may cause loss of
	 * throughput.
	 */
	अगर (bfqd->strict_guarantees && bfqd->rq_in_driver > 0)
		जाओ निकास;

	bfqq = bfq_select_queue(bfqd);
	अगर (!bfqq)
		जाओ निकास;

	rq = bfq_dispatch_rq_from_bfqq(bfqd, bfqq);

	अगर (rq) अणु
inc_in_driver_start_rq:
		bfqd->rq_in_driver++;
start_rq:
		rq->rq_flags |= RQF_STARTED;
	पूर्ण
निकास:
	वापस rq;
पूर्ण

#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
अटल व्योम bfq_update_dispatch_stats(काष्ठा request_queue *q,
				      काष्ठा request *rq,
				      काष्ठा bfq_queue *in_serv_queue,
				      bool idle_समयr_disabled)
अणु
	काष्ठा bfq_queue *bfqq = rq ? RQ_BFQQ(rq) : शून्य;

	अगर (!idle_समयr_disabled && !bfqq)
		वापस;

	/*
	 * rq and bfqq are guaranteed to exist until this function
	 * ends, क्रम the following reasons. First, rq can be
	 * dispatched to the device, and then can be completed and
	 * मुक्तd, only after this function ends. Second, rq cannot be
	 * merged (and thus मुक्तd because of a merge) any दीर्घer,
	 * because it has alपढ़ोy started. Thus rq cannot be मुक्तd
	 * beक्रमe this function ends, and, since rq has a reference to
	 * bfqq, the same guarantee holds क्रम bfqq too.
	 *
	 * In addition, the following queue lock guarantees that
	 * bfqq_group(bfqq) exists as well.
	 */
	spin_lock_irq(&q->queue_lock);
	अगर (idle_समयr_disabled)
		/*
		 * Since the idle समयr has been disabled,
		 * in_serv_queue contained some request when
		 * __bfq_dispatch_request was invoked above, which
		 * implies that rq was picked exactly from
		 * in_serv_queue. Thus in_serv_queue == bfqq, and is
		 * thereक्रमe guaranteed to exist because of the above
		 * arguments.
		 */
		bfqg_stats_update_idle_समय(bfqq_group(in_serv_queue));
	अगर (bfqq) अणु
		काष्ठा bfq_group *bfqg = bfqq_group(bfqq);

		bfqg_stats_update_avg_queue_size(bfqg);
		bfqg_stats_set_start_empty_समय(bfqg);
		bfqg_stats_update_io_हटाओ(bfqg, rq->cmd_flags);
	पूर्ण
	spin_unlock_irq(&q->queue_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम bfq_update_dispatch_stats(काष्ठा request_queue *q,
					     काष्ठा request *rq,
					     काष्ठा bfq_queue *in_serv_queue,
					     bool idle_समयr_disabled) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_BFQ_CGROUP_DEBUG */

अटल काष्ठा request *bfq_dispatch_request(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा bfq_data *bfqd = hctx->queue->elevator->elevator_data;
	काष्ठा request *rq;
	काष्ठा bfq_queue *in_serv_queue;
	bool रुकोing_rq, idle_समयr_disabled;

	spin_lock_irq(&bfqd->lock);

	in_serv_queue = bfqd->in_service_queue;
	रुकोing_rq = in_serv_queue && bfq_bfqq_रुको_request(in_serv_queue);

	rq = __bfq_dispatch_request(hctx);

	idle_समयr_disabled =
		रुकोing_rq && !bfq_bfqq_रुको_request(in_serv_queue);

	spin_unlock_irq(&bfqd->lock);

	bfq_update_dispatch_stats(hctx->queue, rq, in_serv_queue,
				  idle_समयr_disabled);

	वापस rq;
पूर्ण

/*
 * Task holds one reference to the queue, dropped when task निकासs.  Each rq
 * in-flight on this queue also holds a reference, dropped when rq is मुक्तd.
 *
 * Scheduler lock must be held here. Recall not to use bfqq after calling
 * this function on it.
 */
व्योम bfq_put_queue(काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_queue *item;
	काष्ठा hlist_node *n;
	काष्ठा bfq_group *bfqg = bfqq_group(bfqq);

	अगर (bfqq->bfqd)
		bfq_log_bfqq(bfqq->bfqd, bfqq, "put_queue: %p %d",
			     bfqq, bfqq->ref);

	bfqq->ref--;
	अगर (bfqq->ref)
		वापस;

	अगर (!hlist_unhashed(&bfqq->burst_list_node)) अणु
		hlist_del_init(&bfqq->burst_list_node);
		/*
		 * Decrement also burst size after the removal, अगर the
		 * process associated with bfqq is निकासing, and thus
		 * करोes not contribute to the burst any दीर्घer. This
		 * decrement helps filter out false positives of large
		 * bursts, when some लघु-lived process (often due to
		 * the execution of commands by some service) happens
		 * to start and निकास जबतक a complex application is
		 * starting, and thus spawning several processes that
		 * करो I/O (and that *must not* be treated as a large
		 * burst, see comments on bfq_handle_burst).
		 *
		 * In particular, the decrement is perक्रमmed only अगर:
		 * 1) bfqq is not a merged queue, because, अगर it is,
		 * then this मुक्त of bfqq is not triggered by the निकास
		 * of the process bfqq is associated with, but exactly
		 * by the fact that bfqq has just been merged.
		 * 2) burst_size is greater than 0, to handle
		 * unbalanced decrements. Unbalanced decrements may
		 * happen in te following हाल: bfqq is inserted पूर्णांकo
		 * the current burst list--without incrementing
		 * bust_size--because of a split, but the current
		 * burst list is not the burst list bfqq beदीर्घed to
		 * (see comments on the हाल of a split in
		 * bfq_set_request).
		 */
		अगर (bfqq->bic && bfqq->bfqd->burst_size > 0)
			bfqq->bfqd->burst_size--;
	पूर्ण

	/*
	 * bfqq करोes not exist any दीर्घer, so it cannot be woken by
	 * any other queue, and cannot wake any other queue. Then bfqq
	 * must be हटाओd from the woken list of its possible waker
	 * queue, and all queues in the woken list of bfqq must stop
	 * having a waker queue. Strictly speaking, these updates
	 * should be perक्रमmed when bfqq reमुख्यs with no I/O source
	 * attached to it, which happens beक्रमe bfqq माला_लो मुक्तd. In
	 * particular, this happens when the last process associated
	 * with bfqq निकासs or माला_लो associated with a dअगरferent
	 * queue. However, both events lead to bfqq being मुक्तd soon,
	 * and dangling references would come out only after bfqq माला_लो
	 * मुक्तd. So these updates are करोne here, as a simple and safe
	 * way to handle all हालs.
	 */
	/* हटाओ bfqq from woken list */
	अगर (!hlist_unhashed(&bfqq->woken_list_node))
		hlist_del_init(&bfqq->woken_list_node);

	/* reset waker क्रम all queues in woken list */
	hlist_क्रम_each_entry_safe(item, n, &bfqq->woken_list,
				  woken_list_node) अणु
		item->waker_bfqq = शून्य;
		hlist_del_init(&item->woken_list_node);
	पूर्ण

	अगर (bfqq->bfqd && bfqq->bfqd->last_completed_rq_bfqq == bfqq)
		bfqq->bfqd->last_completed_rq_bfqq = शून्य;

	kmem_cache_मुक्त(bfq_pool, bfqq);
	bfqg_and_blkg_put(bfqg);
पूर्ण

अटल व्योम bfq_put_stable_ref(काष्ठा bfq_queue *bfqq)
अणु
	bfqq->stable_ref--;
	bfq_put_queue(bfqq);
पूर्ण

अटल व्योम bfq_put_coचालक(काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_queue *__bfqq, *next;

	/*
	 * If this queue was scheduled to merge with another queue, be
	 * sure to drop the reference taken on that queue (and others in
	 * the merge chain). See bfq_setup_merge and bfq_merge_bfqqs.
	 */
	__bfqq = bfqq->new_bfqq;
	जबतक (__bfqq) अणु
		अगर (__bfqq == bfqq)
			अवरोध;
		next = __bfqq->new_bfqq;
		bfq_put_queue(__bfqq);
		__bfqq = next;
	पूर्ण
पूर्ण

अटल व्योम bfq_निकास_bfqq(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	अगर (bfqq == bfqd->in_service_queue) अणु
		__bfq_bfqq_expire(bfqd, bfqq, BFQQE_BUDGET_TIMEOUT);
		bfq_schedule_dispatch(bfqd);
	पूर्ण

	bfq_log_bfqq(bfqd, bfqq, "exit_bfqq: %p, %d", bfqq, bfqq->ref);

	bfq_put_coचालक(bfqq);

	bfq_release_process_ref(bfqd, bfqq);
पूर्ण

अटल व्योम bfq_निकास_icq_bfqq(काष्ठा bfq_io_cq *bic, bool is_sync)
अणु
	काष्ठा bfq_queue *bfqq = bic_to_bfqq(bic, is_sync);
	काष्ठा bfq_data *bfqd;

	अगर (bfqq)
		bfqd = bfqq->bfqd; /* शून्य अगर scheduler alपढ़ोy निकासed */

	अगर (bfqq && bfqd) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&bfqd->lock, flags);
		bfqq->bic = शून्य;
		bfq_निकास_bfqq(bfqd, bfqq);
		bic_set_bfqq(bic, शून्य, is_sync);
		spin_unlock_irqrestore(&bfqd->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम bfq_निकास_icq(काष्ठा io_cq *icq)
अणु
	काष्ठा bfq_io_cq *bic = icq_to_bic(icq);

	अगर (bic->stable_merge_bfqq) अणु
		काष्ठा bfq_data *bfqd = bic->stable_merge_bfqq->bfqd;

		/*
		 * bfqd is शून्य अगर scheduler alपढ़ोy निकासed, and in
		 * that हाल this is the last समय bfqq is accessed.
		 */
		अगर (bfqd) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&bfqd->lock, flags);
			bfq_put_stable_ref(bic->stable_merge_bfqq);
			spin_unlock_irqrestore(&bfqd->lock, flags);
		पूर्ण अन्यथा अणु
			bfq_put_stable_ref(bic->stable_merge_bfqq);
		पूर्ण
	पूर्ण

	bfq_निकास_icq_bfqq(bic, true);
	bfq_निकास_icq_bfqq(bic, false);
पूर्ण

/*
 * Update the entity prio values; note that the new values will not
 * be used until the next (re)activation.
 */
अटल व्योम
bfq_set_next_ioprio_data(काष्ठा bfq_queue *bfqq, काष्ठा bfq_io_cq *bic)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	पूर्णांक ioprio_class;
	काष्ठा bfq_data *bfqd = bfqq->bfqd;

	अगर (!bfqd)
		वापस;

	ioprio_class = IOPRIO_PRIO_CLASS(bic->ioprio);
	चयन (ioprio_class) अणु
	शेष:
		pr_err("bdi %s: bfq: bad prio class %d\n",
				bdi_dev_name(bfqq->bfqd->queue->backing_dev_info),
				ioprio_class);
		fallthrough;
	हाल IOPRIO_CLASS_NONE:
		/*
		 * No prio set, inherit CPU scheduling settings.
		 */
		bfqq->new_ioprio = task_nice_ioprio(tsk);
		bfqq->new_ioprio_class = task_nice_ioclass(tsk);
		अवरोध;
	हाल IOPRIO_CLASS_RT:
		bfqq->new_ioprio = IOPRIO_PRIO_DATA(bic->ioprio);
		bfqq->new_ioprio_class = IOPRIO_CLASS_RT;
		अवरोध;
	हाल IOPRIO_CLASS_BE:
		bfqq->new_ioprio = IOPRIO_PRIO_DATA(bic->ioprio);
		bfqq->new_ioprio_class = IOPRIO_CLASS_BE;
		अवरोध;
	हाल IOPRIO_CLASS_IDLE:
		bfqq->new_ioprio_class = IOPRIO_CLASS_IDLE;
		bfqq->new_ioprio = 7;
		अवरोध;
	पूर्ण

	अगर (bfqq->new_ioprio >= IOPRIO_BE_NR) अणु
		pr_crit("bfq_set_next_ioprio_data: new_ioprio %d\n",
			bfqq->new_ioprio);
		bfqq->new_ioprio = IOPRIO_BE_NR;
	पूर्ण

	bfqq->entity.new_weight = bfq_ioprio_to_weight(bfqq->new_ioprio);
	bfq_log_bfqq(bfqd, bfqq, "new_ioprio %d new_weight %d",
		     bfqq->new_ioprio, bfqq->entity.new_weight);
	bfqq->entity.prio_changed = 1;
पूर्ण

अटल काष्ठा bfq_queue *bfq_get_queue(काष्ठा bfq_data *bfqd,
				       काष्ठा bio *bio, bool is_sync,
				       काष्ठा bfq_io_cq *bic,
				       bool respawn);

अटल व्योम bfq_check_ioprio_change(काष्ठा bfq_io_cq *bic, काष्ठा bio *bio)
अणु
	काष्ठा bfq_data *bfqd = bic_to_bfqd(bic);
	काष्ठा bfq_queue *bfqq;
	पूर्णांक ioprio = bic->icq.ioc->ioprio;

	/*
	 * This condition may trigger on a newly created bic, be sure to
	 * drop the lock beक्रमe वापसing.
	 */
	अगर (unlikely(!bfqd) || likely(bic->ioprio == ioprio))
		वापस;

	bic->ioprio = ioprio;

	bfqq = bic_to_bfqq(bic, false);
	अगर (bfqq) अणु
		bfq_release_process_ref(bfqd, bfqq);
		bfqq = bfq_get_queue(bfqd, bio, BLK_RW_ASYNC, bic, true);
		bic_set_bfqq(bic, bfqq, false);
	पूर्ण

	bfqq = bic_to_bfqq(bic, true);
	अगर (bfqq)
		bfq_set_next_ioprio_data(bfqq, bic);
पूर्ण

अटल व्योम bfq_init_bfqq(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			  काष्ठा bfq_io_cq *bic, pid_t pid, पूर्णांक is_sync)
अणु
	u64 now_ns = kसमय_get_ns();

	RB_CLEAR_NODE(&bfqq->entity.rb_node);
	INIT_LIST_HEAD(&bfqq->fअगरo);
	INIT_HLIST_NODE(&bfqq->burst_list_node);
	INIT_HLIST_NODE(&bfqq->woken_list_node);
	INIT_HLIST_HEAD(&bfqq->woken_list);

	bfqq->ref = 0;
	bfqq->bfqd = bfqd;

	अगर (bic)
		bfq_set_next_ioprio_data(bfqq, bic);

	अगर (is_sync) अणु
		/*
		 * No need to mark as has_लघु_tसमय अगर in
		 * idle_class, because no device idling is perक्रमmed
		 * क्रम queues in idle class
		 */
		अगर (!bfq_class_idle(bfqq))
			/* tentatively mark as has_लघु_tसमय */
			bfq_mark_bfqq_has_लघु_tसमय(bfqq);
		bfq_mark_bfqq_sync(bfqq);
		bfq_mark_bfqq_just_created(bfqq);
	पूर्ण अन्यथा
		bfq_clear_bfqq_sync(bfqq);

	/* set end request to minus infinity from now */
	bfqq->tसमय.last_end_request = now_ns + 1;

	bfqq->creation_समय = jअगरfies;

	bfqq->io_start_समय = now_ns;

	bfq_mark_bfqq_IO_bound(bfqq);

	bfqq->pid = pid;

	/* Tentative initial value to trade off between thr and lat */
	bfqq->max_budget = (2 * bfq_max_budget(bfqd)) / 3;
	bfqq->budget_समयout = bfq_smallest_from_now();

	bfqq->wr_coeff = 1;
	bfqq->last_wr_start_finish = jअगरfies;
	bfqq->wr_start_at_चयन_to_srt = bfq_smallest_from_now();
	bfqq->split_समय = bfq_smallest_from_now();

	/*
	 * To not क्रमget the possibly high bandwidth consumed by a
	 * process/queue in the recent past,
	 * bfq_bfqq_softrt_next_start() वापसs a value at least equal
	 * to the current value of bfqq->soft_rt_next_start (see
	 * comments on bfq_bfqq_softrt_next_start).  Set
	 * soft_rt_next_start to now, to mean that bfqq has consumed
	 * no bandwidth so far.
	 */
	bfqq->soft_rt_next_start = jअगरfies;

	/* first request is almost certainly seeky */
	bfqq->seek_history = 1;
पूर्ण

अटल काष्ठा bfq_queue **bfq_async_queue_prio(काष्ठा bfq_data *bfqd,
					       काष्ठा bfq_group *bfqg,
					       पूर्णांक ioprio_class, पूर्णांक ioprio)
अणु
	चयन (ioprio_class) अणु
	हाल IOPRIO_CLASS_RT:
		वापस &bfqg->async_bfqq[0][ioprio];
	हाल IOPRIO_CLASS_NONE:
		ioprio = IOPRIO_NORM;
		fallthrough;
	हाल IOPRIO_CLASS_BE:
		वापस &bfqg->async_bfqq[1][ioprio];
	हाल IOPRIO_CLASS_IDLE:
		वापस &bfqg->async_idle_bfqq;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा bfq_queue *
bfq_करो_early_stable_merge(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			  काष्ठा bfq_io_cq *bic,
			  काष्ठा bfq_queue *last_bfqq_created)
अणु
	काष्ठा bfq_queue *new_bfqq =
		bfq_setup_merge(bfqq, last_bfqq_created);

	अगर (!new_bfqq)
		वापस bfqq;

	अगर (new_bfqq->bic)
		new_bfqq->bic->stably_merged = true;
	bic->stably_merged = true;

	/*
	 * Reusing merge functions. This implies that
	 * bfqq->bic must be set too, क्रम
	 * bfq_merge_bfqqs to correctly save bfqq's
	 * state beक्रमe समाप्तing it.
	 */
	bfqq->bic = bic;
	bfq_merge_bfqqs(bfqd, bic, bfqq, new_bfqq);

	वापस new_bfqq;
पूर्ण

/*
 * Many throughput-sensitive workloads are made of several parallel
 * I/O flows, with all flows generated by the same application, or
 * more generically by the same task (e.g., प्रणाली boot). The most
 * counterproductive action with these workloads is plugging I/O
 * dispatch when one of the bfq_queues associated with these flows
 * reमुख्यs temporarily empty.
 *
 * To aव्योम this plugging, BFQ has been using a burst-handling
 * mechanism क्रम years now. This mechanism has proven effective क्रम
 * throughput, and not detrimental क्रम service guarantees. The
 * following function pushes this mechanism a little bit further,
 * basing on the following two facts.
 *
 * First, all the I/O flows of a the same application or task
 * contribute to the execution/completion of that common application
 * or task. So the perक्रमmance figures that matter are total
 * throughput of the flows and task-wide I/O latency.  In particular,
 * these flows करो not need to be रक्षित from each other, in terms
 * of inभागidual bandwidth or latency.
 *
 * Second, the above fact holds regardless of the number of flows.
 *
 * Putting these two facts together, this commits merges stably the
 * bfq_queues associated with these I/O flows, i.e., with the
 * processes that generate these IO/ flows, regardless of how many the
 * involved processes are.
 *
 * To decide whether a set of bfq_queues is actually associated with
 * the I/O flows of a common application or task, and to merge these
 * queues stably, this function operates as follows: given a bfq_queue,
 * say Q2, currently being created, and the last bfq_queue, say Q1,
 * created beक्रमe Q2, Q2 is merged stably with Q1 अगर
 * - very little समय has elapsed since when Q1 was created
 * - Q2 has the same ioprio as Q1
 * - Q2 beदीर्घs to the same group as Q1
 *
 * Merging bfq_queues also reduces scheduling overhead. A fio test
 * with ten अक्रमom पढ़ोers on /dev/nullb shows a throughput boost of
 * 40%, with a quadcore. Since BFQ's execution समय amounts to ~50% of
 * the total per-request processing समय, the above throughput boost
 * implies that BFQ's overhead is reduced by more than 50%.
 *
 * This new mechanism most certainly obsoletes the current
 * burst-handling heuristics. We keep those heuristics क्रम the moment.
 */
अटल काष्ठा bfq_queue *bfq_करो_or_sched_stable_merge(काष्ठा bfq_data *bfqd,
						      काष्ठा bfq_queue *bfqq,
						      काष्ठा bfq_io_cq *bic)
अणु
	काष्ठा bfq_queue **source_bfqq = bfqq->entity.parent ?
		&bfqq->entity.parent->last_bfqq_created :
		&bfqd->last_bfqq_created;

	काष्ठा bfq_queue *last_bfqq_created = *source_bfqq;

	/*
	 * If last_bfqq_created has not been set yet, then init it. If
	 * it has been set alपढ़ोy, but too दीर्घ ago, then move it
	 * क्रमward to bfqq. Finally, move also अगर bfqq beदीर्घs to a
	 * dअगरferent group than last_bfqq_created, or अगर bfqq has a
	 * dअगरferent ioprio or ioprio_class. If none of these
	 * conditions holds true, then try an early stable merge or
	 * schedule a delayed stable merge.
	 *
	 * A delayed merge is scheduled (instead of perक्रमming an
	 * early merge), in हाल bfqq might soon prove to be more
	 * throughput-beneficial अगर not merged. Currently this is
	 * possible only अगर bfqd is rotational with no queueing. For
	 * such a drive, not merging bfqq is better क्रम throughput अगर
	 * bfqq happens to contain sequential I/O. So, we रुको a
	 * little bit क्रम enough I/O to flow through bfqq. After that,
	 * अगर such an I/O is sequential, then the merge is
	 * canceled. Otherwise the merge is finally perक्रमmed.
	 */
	अगर (!last_bfqq_created ||
	    समय_beक्रमe(last_bfqq_created->creation_समय +
			bfqd->bfq_burst_पूर्णांकerval,
			bfqq->creation_समय) ||
		bfqq->entity.parent != last_bfqq_created->entity.parent ||
		bfqq->ioprio != last_bfqq_created->ioprio ||
		bfqq->ioprio_class != last_bfqq_created->ioprio_class)
		*source_bfqq = bfqq;
	अन्यथा अगर (समय_after_eq(last_bfqq_created->creation_समय +
				 bfqd->bfq_burst_पूर्णांकerval,
				 bfqq->creation_समय)) अणु
		अगर (likely(bfqd->nonrot_with_queueing))
			/*
			 * With this type of drive, leaving
			 * bfqq alone may provide no
			 * throughput benefits compared with
			 * merging bfqq. So merge bfqq now.
			 */
			bfqq = bfq_करो_early_stable_merge(bfqd, bfqq,
							 bic,
							 last_bfqq_created);
		अन्यथा अणु /* schedule tentative stable merge */
			/*
			 * get reference on last_bfqq_created,
			 * to prevent it from being मुक्तd,
			 * until we decide whether to merge
			 */
			last_bfqq_created->ref++;
			/*
			 * need to keep track of stable refs, to
			 * compute process refs correctly
			 */
			last_bfqq_created->stable_ref++;
			/*
			 * Record the bfqq to merge to.
			 */
			bic->stable_merge_bfqq = last_bfqq_created;
		पूर्ण
	पूर्ण

	वापस bfqq;
पूर्ण


अटल काष्ठा bfq_queue *bfq_get_queue(काष्ठा bfq_data *bfqd,
				       काष्ठा bio *bio, bool is_sync,
				       काष्ठा bfq_io_cq *bic,
				       bool respawn)
अणु
	स्थिर पूर्णांक ioprio = IOPRIO_PRIO_DATA(bic->ioprio);
	स्थिर पूर्णांक ioprio_class = IOPRIO_PRIO_CLASS(bic->ioprio);
	काष्ठा bfq_queue **async_bfqq = शून्य;
	काष्ठा bfq_queue *bfqq;
	काष्ठा bfq_group *bfqg;

	rcu_पढ़ो_lock();

	bfqg = bfq_find_set_group(bfqd, __bio_blkcg(bio));
	अगर (!bfqg) अणु
		bfqq = &bfqd->oom_bfqq;
		जाओ out;
	पूर्ण

	अगर (!is_sync) अणु
		async_bfqq = bfq_async_queue_prio(bfqd, bfqg, ioprio_class,
						  ioprio);
		bfqq = *async_bfqq;
		अगर (bfqq)
			जाओ out;
	पूर्ण

	bfqq = kmem_cache_alloc_node(bfq_pool,
				     GFP_NOWAIT | __GFP_ZERO | __GFP_NOWARN,
				     bfqd->queue->node);

	अगर (bfqq) अणु
		bfq_init_bfqq(bfqd, bfqq, bic, current->pid,
			      is_sync);
		bfq_init_entity(&bfqq->entity, bfqg);
		bfq_log_bfqq(bfqd, bfqq, "allocated");
	पूर्ण अन्यथा अणु
		bfqq = &bfqd->oom_bfqq;
		bfq_log_bfqq(bfqd, bfqq, "using oom bfqq");
		जाओ out;
	पूर्ण

	/*
	 * Pin the queue now that it's allocated, scheduler निकास will
	 * prune it.
	 */
	अगर (async_bfqq) अणु
		bfqq->ref++; /*
			      * Extra group reference, w.r.t. sync
			      * queue. This extra reference is हटाओd
			      * only अगर bfqq->bfqg disappears, to
			      * guarantee that this queue is not मुक्तd
			      * until its group goes away.
			      */
		bfq_log_bfqq(bfqd, bfqq, "get_queue, bfqq not in async: %p, %d",
			     bfqq, bfqq->ref);
		*async_bfqq = bfqq;
	पूर्ण

out:
	bfqq->ref++; /* get a process reference to this queue */

	अगर (bfqq != &bfqd->oom_bfqq && is_sync && !respawn)
		bfqq = bfq_करो_or_sched_stable_merge(bfqd, bfqq, bic);

	rcu_पढ़ो_unlock();
	वापस bfqq;
पूर्ण

अटल व्योम bfq_update_io_thinkसमय(काष्ठा bfq_data *bfqd,
				    काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_tसमय *tसमय = &bfqq->tसमय;
	u64 elapsed;

	/*
	 * We are really पूर्णांकerested in how दीर्घ it takes क्रम the queue to
	 * become busy when there is no outstanding IO क्रम this queue. So
	 * ignore हालs when the bfq queue has alपढ़ोy IO queued.
	 */
	अगर (bfqq->dispatched || bfq_bfqq_busy(bfqq))
		वापस;
	elapsed = kसमय_get_ns() - bfqq->tसमय.last_end_request;
	elapsed = min_t(u64, elapsed, 2ULL * bfqd->bfq_slice_idle);

	tसमय->tसमय_samples = (7*tसमय->tसमय_samples + 256) / 8;
	tसमय->tसमय_प्रकारotal = भाग_u64(7*tसमय->tसमय_प्रकारotal + 256*elapsed,  8);
	tसमय->tसमय_mean = भाग64_ul(tसमय->tसमय_प्रकारotal + 128,
				     tसमय->tसमय_samples);
पूर्ण

अटल व्योम
bfq_update_io_seekसमय(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		       काष्ठा request *rq)
अणु
	bfqq->seek_history <<= 1;
	bfqq->seek_history |= BFQ_RQ_SEEKY(bfqd, bfqq->last_request_pos, rq);

	अगर (bfqq->wr_coeff > 1 &&
	    bfqq->wr_cur_max_समय == bfqd->bfq_wr_rt_max_समय &&
	    BFQQ_TOTALLY_SEEKY(bfqq)) अणु
		अगर (समय_is_beक्रमe_jअगरfies(bfqq->wr_start_at_चयन_to_srt +
					   bfq_wr_duration(bfqd))) अणु
			/*
			 * In soft_rt weight raising with the
			 * पूर्णांकeractive-weight-raising period
			 * elapsed (so no चयन back to
			 * पूर्णांकeractive weight raising).
			 */
			bfq_bfqq_end_wr(bfqq);
		पूर्ण अन्यथा अणु /*
			  * stopping soft_rt weight raising
			  * जबतक still in पूर्णांकeractive period,
			  * चयन back to पूर्णांकeractive weight
			  * raising
			  */
			चयन_back_to_पूर्णांकeractive_wr(bfqq, bfqd);
			bfqq->entity.prio_changed = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bfq_update_has_लघु_tसमय(काष्ठा bfq_data *bfqd,
				       काष्ठा bfq_queue *bfqq,
				       काष्ठा bfq_io_cq *bic)
अणु
	bool has_लघु_tसमय = true, state_changed;

	/*
	 * No need to update has_लघु_tसमय अगर bfqq is async or in
	 * idle io prio class, or अगर bfq_slice_idle is zero, because
	 * no device idling is perक्रमmed क्रम bfqq in this हाल.
	 */
	अगर (!bfq_bfqq_sync(bfqq) || bfq_class_idle(bfqq) ||
	    bfqd->bfq_slice_idle == 0)
		वापस;

	/* Idle winकरोw just restored, statistics are meaningless. */
	अगर (समय_is_after_eq_jअगरfies(bfqq->split_समय +
				     bfqd->bfq_wr_min_idle_समय))
		वापस;

	/* Think समय is infinite अगर no process is linked to
	 * bfqq. Otherwise check average think समय to decide whether
	 * to mark as has_लघु_tसमय. To this goal, compare average
	 * think समय with half the I/O-plugging समयout.
	 */
	अगर (atomic_पढ़ो(&bic->icq.ioc->active_ref) == 0 ||
	    (bfq_sample_valid(bfqq->tसमय.tसमय_samples) &&
	     bfqq->tसमय.tसमय_mean > bfqd->bfq_slice_idle>>1))
		has_लघु_tसमय = false;

	state_changed = has_लघु_tसमय != bfq_bfqq_has_लघु_tसमय(bfqq);

	अगर (has_लघु_tसमय)
		bfq_mark_bfqq_has_लघु_tसमय(bfqq);
	अन्यथा
		bfq_clear_bfqq_has_लघु_tसमय(bfqq);

	/*
	 * Until the base value क्रम the total service समय माला_लो
	 * finally computed क्रम bfqq, the inject limit करोes depend on
	 * the think-समय state (लघु|दीर्घ). In particular, the limit
	 * is 0 or 1 अगर the think समय is deemed, respectively, as
	 * लघु or दीर्घ (details in the comments in
	 * bfq_update_inject_limit()). Accordingly, the next
	 * inकाष्ठाions reset the inject limit अगर the think-समय state
	 * has changed and the above base value is still to be
	 * computed.
	 *
	 * However, the reset is perक्रमmed only अगर more than 100 ms
	 * have elapsed since the last update of the inject limit, or
	 * (inclusive) अगर the change is from लघु to दीर्घ think
	 * समय. The reason क्रम this रुकोing is as follows.
	 *
	 * bfqq may have a दीर्घ think समय because of a
	 * synchronization with some other queue, i.e., because the
	 * I/O of some other queue may need to be completed क्रम bfqq
	 * to receive new I/O. Details in the comments on the choice
	 * of the queue क्रम injection in bfq_select_queue().
	 *
	 * As stressed in those comments, अगर such a synchronization is
	 * actually in place, then, without injection on bfqq, the
	 * blocking I/O cannot happen to served जबतक bfqq is in
	 * service. As a consequence, अगर bfqq is granted
	 * I/O-dispatch-plugging, then bfqq reमुख्यs empty, and no I/O
	 * is dispatched, until the idle समयout fires. This is likely
	 * to result in lower bandwidth and higher latencies क्रम bfqq,
	 * and in a severe loss of total throughput.
	 *
	 * On the opposite end, a non-zero inject limit may allow the
	 * I/O that blocks bfqq to be executed soon, and thereक्रमe
	 * bfqq to receive new I/O soon.
	 *
	 * But, अगर the blocking माला_लो actually eliminated, then the
	 * next think-समय sample क्रम bfqq may be very low. This in
	 * turn may cause bfqq's think समय to be deemed
	 * लघु. Without the 100 ms barrier, this new state change
	 * would cause the body of the next अगर to be executed
	 * immediately. But this would set to 0 the inject
	 * limit. Without injection, the blocking I/O would cause the
	 * think समय of bfqq to become दीर्घ again, and thereक्रमe the
	 * inject limit to be उठाओd again, and so on. The only effect
	 * of such a steady oscillation between the two think-समय
	 * states would be to prevent effective injection on bfqq.
	 *
	 * In contrast, अगर the inject limit is not reset during such a
	 * दीर्घ समय पूर्णांकerval as 100 ms, then the number of लघु
	 * think समय samples can grow signअगरicantly beक्रमe the reset
	 * is perक्रमmed. As a consequence, the think समय state can
	 * become stable beक्रमe the reset. Thereक्रमe there will be no
	 * state change when the 100 ms elapse, and no reset of the
	 * inject limit. The inject limit reमुख्यs steadily equal to 1
	 * both during and after the 100 ms. So injection can be
	 * perक्रमmed at all बार, and throughput माला_लो boosted.
	 *
	 * An inject limit equal to 1 is however in conflict, in
	 * general, with the fact that the think समय of bfqq is
	 * लघु, because injection may be likely to delay bfqq's I/O
	 * (as explained in the comments in
	 * bfq_update_inject_limit()). But this करोes not happen in
	 * this special हाल, because bfqq's low think समय is due to
	 * an effective handling of a synchronization, through
	 * injection. In this special हाल, bfqq's I/O करोes not get
	 * delayed by injection; on the contrary, bfqq's I/O is
	 * brought क्रमward, because it is not blocked क्रम
	 * milliseconds.
	 *
	 * In addition, serving the blocking I/O much sooner, and much
	 * more frequently than once per I/O-plugging समयout, makes
	 * it much quicker to detect a waker queue (the concept of
	 * waker queue is defined in the comments in
	 * bfq_add_request()). This makes it possible to start sooner
	 * to boost throughput more effectively, by injecting the I/O
	 * of the waker queue unconditionally on every
	 * bfq_dispatch_request().
	 *
	 * One last, important benefit of not resetting the inject
	 * limit beक्रमe 100 ms is that, during this समय पूर्णांकerval, the
	 * base value क्रम the total service समय is likely to get
	 * finally computed क्रम bfqq, मुक्तing the inject limit from
	 * its relation with the think समय.
	 */
	अगर (state_changed && bfqq->last_serv_समय_ns == 0 &&
	    (समय_is_beक्रमe_eq_jअगरfies(bfqq->decrease_समय_jअगर +
				      msecs_to_jअगरfies(100)) ||
	     !has_लघु_tसमय))
		bfq_reset_inject_limit(bfqd, bfqq);
पूर्ण

/*
 * Called when a new fs request (rq) is added to bfqq.  Check अगर there's
 * something we should करो about it.
 */
अटल व्योम bfq_rq_enqueued(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			    काष्ठा request *rq)
अणु
	अगर (rq->cmd_flags & REQ_META)
		bfqq->meta_pending++;

	bfqq->last_request_pos = blk_rq_pos(rq) + blk_rq_sectors(rq);

	अगर (bfqq == bfqd->in_service_queue && bfq_bfqq_रुको_request(bfqq)) अणु
		bool small_req = bfqq->queued[rq_is_sync(rq)] == 1 &&
				 blk_rq_sectors(rq) < 32;
		bool budget_समयout = bfq_bfqq_budget_समयout(bfqq);

		/*
		 * There is just this request queued: अगर
		 * - the request is small, and
		 * - we are idling to boost throughput, and
		 * - the queue is not to be expired,
		 * then just निकास.
		 *
		 * In this way, अगर the device is being idled to रुको
		 * क्रम a new request from the in-service queue, we
		 * aव्योम unplugging the device and committing the
		 * device to serve just a small request. In contrast
		 * we रुको क्रम the block layer to decide when to
		 * unplug the device: hopefully, new requests will be
		 * merged to this one quickly, then the device will be
		 * unplugged and larger requests will be dispatched.
		 */
		अगर (small_req && idling_boosts_thr_without_issues(bfqd, bfqq) &&
		    !budget_समयout)
			वापस;

		/*
		 * A large enough request arrived, or idling is being
		 * perक्रमmed to preserve service guarantees, or
		 * finally the queue is to be expired: in all these
		 * हालs disk idling is to be stopped, so clear
		 * रुको_request flag and reset समयr.
		 */
		bfq_clear_bfqq_रुको_request(bfqq);
		hrसमयr_try_to_cancel(&bfqd->idle_slice_समयr);

		/*
		 * The queue is not empty, because a new request just
		 * arrived. Hence we can safely expire the queue, in
		 * हाल of budget समयout, without risking that the
		 * बारtamps of the queue are not updated correctly.
		 * See [1] क्रम more details.
		 */
		अगर (budget_समयout)
			bfq_bfqq_expire(bfqd, bfqq, false,
					BFQQE_BUDGET_TIMEOUT);
	पूर्ण
पूर्ण

/* वापसs true अगर it causes the idle समयr to be disabled */
अटल bool __bfq_insert_request(काष्ठा bfq_data *bfqd, काष्ठा request *rq)
अणु
	काष्ठा bfq_queue *bfqq = RQ_BFQQ(rq),
		*new_bfqq = bfq_setup_coचालक(bfqd, bfqq, rq, true,
						 RQ_BIC(rq));
	bool रुकोing, idle_समयr_disabled = false;

	अगर (new_bfqq) अणु
		/*
		 * Release the request's reference to the old bfqq
		 * and make sure one is taken to the shared queue.
		 */
		new_bfqq->allocated++;
		bfqq->allocated--;
		new_bfqq->ref++;
		/*
		 * If the bic associated with the process
		 * issuing this request still poपूर्णांकs to bfqq
		 * (and thus has not been alपढ़ोy redirected
		 * to new_bfqq or even some other bfq_queue),
		 * then complete the merge and redirect it to
		 * new_bfqq.
		 */
		अगर (bic_to_bfqq(RQ_BIC(rq), 1) == bfqq)
			bfq_merge_bfqqs(bfqd, RQ_BIC(rq),
					bfqq, new_bfqq);

		bfq_clear_bfqq_just_created(bfqq);
		/*
		 * rq is about to be enqueued पूर्णांकo new_bfqq,
		 * release rq reference on bfqq
		 */
		bfq_put_queue(bfqq);
		rq->elv.priv[1] = new_bfqq;
		bfqq = new_bfqq;
	पूर्ण

	bfq_update_io_thinkसमय(bfqd, bfqq);
	bfq_update_has_लघु_tसमय(bfqd, bfqq, RQ_BIC(rq));
	bfq_update_io_seekसमय(bfqd, bfqq, rq);

	रुकोing = bfqq && bfq_bfqq_रुको_request(bfqq);
	bfq_add_request(rq);
	idle_समयr_disabled = रुकोing && !bfq_bfqq_रुको_request(bfqq);

	rq->fअगरo_समय = kसमय_get_ns() + bfqd->bfq_fअगरo_expire[rq_is_sync(rq)];
	list_add_tail(&rq->queuelist, &bfqq->fअगरo);

	bfq_rq_enqueued(bfqd, bfqq, rq);

	वापस idle_समयr_disabled;
पूर्ण

#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
अटल व्योम bfq_update_insert_stats(काष्ठा request_queue *q,
				    काष्ठा bfq_queue *bfqq,
				    bool idle_समयr_disabled,
				    अचिन्हित पूर्णांक cmd_flags)
अणु
	अगर (!bfqq)
		वापस;

	/*
	 * bfqq still exists, because it can disappear only after
	 * either it is merged with another queue, or the process it
	 * is associated with निकासs. But both actions must be taken by
	 * the same process currently executing this flow of
	 * inकाष्ठाions.
	 *
	 * In addition, the following queue lock guarantees that
	 * bfqq_group(bfqq) exists as well.
	 */
	spin_lock_irq(&q->queue_lock);
	bfqg_stats_update_io_add(bfqq_group(bfqq), bfqq, cmd_flags);
	अगर (idle_समयr_disabled)
		bfqg_stats_update_idle_समय(bfqq_group(bfqq));
	spin_unlock_irq(&q->queue_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम bfq_update_insert_stats(काष्ठा request_queue *q,
					   काष्ठा bfq_queue *bfqq,
					   bool idle_समयr_disabled,
					   अचिन्हित पूर्णांक cmd_flags) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_BFQ_CGROUP_DEBUG */

अटल व्योम bfq_insert_request(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा request *rq,
			       bool at_head)
अणु
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा bfq_data *bfqd = q->elevator->elevator_data;
	काष्ठा bfq_queue *bfqq;
	bool idle_समयr_disabled = false;
	अचिन्हित पूर्णांक cmd_flags;

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	अगर (!cgroup_subsys_on_dfl(io_cgrp_subsys) && rq->bio)
		bfqg_stats_update_legacy_io(q, rq);
#पूर्ण_अगर
	spin_lock_irq(&bfqd->lock);
	अगर (blk_mq_sched_try_insert_merge(q, rq)) अणु
		spin_unlock_irq(&bfqd->lock);
		वापस;
	पूर्ण

	spin_unlock_irq(&bfqd->lock);

	trace_block_rq_insert(rq);

	spin_lock_irq(&bfqd->lock);
	bfqq = bfq_init_rq(rq);

	/*
	 * Reqs with at_head or passthrough flags set are to be put
	 * directly पूर्णांकo dispatch list. Additional हाल क्रम putting rq
	 * directly पूर्णांकo the dispatch queue: the only active
	 * bfq_queues are bfqq and either its waker bfq_queue or one
	 * of its woken bfq_queues. The rationale behind this
	 * additional condition is as follows:
	 * - consider a bfq_queue, say Q1, detected as a waker of
	 *   another bfq_queue, say Q2
	 * - by definition of a waker, Q1 blocks the I/O of Q2, i.e.,
	 *   some I/O of Q1 needs to be completed क्रम new I/O of Q2
	 *   to arrive.  A notable example of waker is journald
	 * - so, Q1 and Q2 are in any respect the queues of two
	 *   cooperating processes (or of two cooperating sets of
	 *   processes): the goal of Q1's I/O is करोing what needs to
	 *   be करोne so that new Q2's I/O can finally be
	 *   issued. Thereक्रमe, अगर the service of Q1's I/O is delayed,
	 *   then Q2's I/O is delayed too.  Conversely, if Q2's I/O is
	 *   delayed, the goal of Q1's I/O is hindered.
	 * - as a consequence, अगर some I/O of Q1/Q2 arrives जबतक
	 *   Q2/Q1 is the only queue in service, there is असलolutely
	 *   no poपूर्णांक in delaying the service of such an I/O. The
	 *   only possible result is a throughput loss
	 * - so, when the above condition holds, the best option is to
	 *   have the new I/O dispatched as soon as possible
	 * - the most effective and efficient way to attain the above
	 *   goal is to put the new I/O directly in the dispatch
	 *   list
	 * - as an additional restriction, Q1 and Q2 must be the only
	 *   busy queues क्रम this commit to put the I/O of Q2/Q1 in
	 *   the dispatch list.  This is necessary, because, अगर also
	 *   other queues are रुकोing क्रम service, then putting new
	 *   I/O directly in the dispatch list may evidently cause a
	 *   violation of service guarantees क्रम the other queues
	 */
	अगर (!bfqq ||
	    (bfqq != bfqd->in_service_queue &&
	     bfqd->in_service_queue != शून्य &&
	     bfq_tot_busy_queues(bfqd) == 1 + bfq_bfqq_busy(bfqq) &&
	     (bfqq->waker_bfqq == bfqd->in_service_queue ||
	      bfqd->in_service_queue->waker_bfqq == bfqq)) || at_head) अणु
		अगर (at_head)
			list_add(&rq->queuelist, &bfqd->dispatch);
		अन्यथा
			list_add_tail(&rq->queuelist, &bfqd->dispatch);
	पूर्ण अन्यथा अणु
		idle_समयr_disabled = __bfq_insert_request(bfqd, rq);
		/*
		 * Update bfqq, because, अगर a queue merge has occurred
		 * in __bfq_insert_request, then rq has been
		 * redirected पूर्णांकo a new queue.
		 */
		bfqq = RQ_BFQQ(rq);

		अगर (rq_mergeable(rq)) अणु
			elv_rqhash_add(q, rq);
			अगर (!q->last_merge)
				q->last_merge = rq;
		पूर्ण
	पूर्ण

	/*
	 * Cache cmd_flags beक्रमe releasing scheduler lock, because rq
	 * may disappear afterwards (क्रम example, because of a request
	 * merge).
	 */
	cmd_flags = rq->cmd_flags;

	spin_unlock_irq(&bfqd->lock);

	bfq_update_insert_stats(q, bfqq, idle_समयr_disabled,
				cmd_flags);
पूर्ण

अटल व्योम bfq_insert_requests(काष्ठा blk_mq_hw_ctx *hctx,
				काष्ठा list_head *list, bool at_head)
अणु
	जबतक (!list_empty(list)) अणु
		काष्ठा request *rq;

		rq = list_first_entry(list, काष्ठा request, queuelist);
		list_del_init(&rq->queuelist);
		bfq_insert_request(hctx, rq, at_head);
	पूर्ण
पूर्ण

अटल व्योम bfq_update_hw_tag(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा bfq_queue *bfqq = bfqd->in_service_queue;

	bfqd->max_rq_in_driver = max_t(पूर्णांक, bfqd->max_rq_in_driver,
				       bfqd->rq_in_driver);

	अगर (bfqd->hw_tag == 1)
		वापस;

	/*
	 * This sample is valid अगर the number of outstanding requests
	 * is large enough to allow a queueing behavior.  Note that the
	 * sum is not exact, as it's not taking पूर्णांकo account deactivated
	 * requests.
	 */
	अगर (bfqd->rq_in_driver + bfqd->queued <= BFQ_HW_QUEUE_THRESHOLD)
		वापस;

	/*
	 * If active queue hasn't enough requests and can idle, bfq might not
	 * dispatch sufficient requests to hardware. Don't zero hw_tag in this
	 * हाल
	 */
	अगर (bfqq && bfq_bfqq_has_लघु_tसमय(bfqq) &&
	    bfqq->dispatched + bfqq->queued[0] + bfqq->queued[1] <
	    BFQ_HW_QUEUE_THRESHOLD &&
	    bfqd->rq_in_driver < BFQ_HW_QUEUE_THRESHOLD)
		वापस;

	अगर (bfqd->hw_tag_samples++ < BFQ_HW_QUEUE_SAMPLES)
		वापस;

	bfqd->hw_tag = bfqd->max_rq_in_driver > BFQ_HW_QUEUE_THRESHOLD;
	bfqd->max_rq_in_driver = 0;
	bfqd->hw_tag_samples = 0;

	bfqd->nonrot_with_queueing =
		blk_queue_nonrot(bfqd->queue) && bfqd->hw_tag;
पूर्ण

अटल व्योम bfq_completed_request(काष्ठा bfq_queue *bfqq, काष्ठा bfq_data *bfqd)
अणु
	u64 now_ns;
	u32 delta_us;

	bfq_update_hw_tag(bfqd);

	bfqd->rq_in_driver--;
	bfqq->dispatched--;

	अगर (!bfqq->dispatched && !bfq_bfqq_busy(bfqq)) अणु
		/*
		 * Set budget_समयout (which we overload to store the
		 * समय at which the queue reमुख्यs with no backlog and
		 * no outstanding request; used by the weight-raising
		 * mechanism).
		 */
		bfqq->budget_समयout = jअगरfies;

		bfq_weights_tree_हटाओ(bfqd, bfqq);
	पूर्ण

	now_ns = kसमय_get_ns();

	bfqq->tसमय.last_end_request = now_ns;

	/*
	 * Using us instead of ns, to get a reasonable precision in
	 * computing rate in next check.
	 */
	delta_us = भाग_u64(now_ns - bfqd->last_completion, NSEC_PER_USEC);

	/*
	 * If the request took rather दीर्घ to complete, and, according
	 * to the maximum request size recorded, this completion latency
	 * implies that the request was certainly served at a very low
	 * rate (less than 1M sectors/sec), then the whole observation
	 * पूर्णांकerval that lasts up to this समय instant cannot be a
	 * valid समय पूर्णांकerval क्रम computing a new peak rate.  Invoke
	 * bfq_update_rate_reset to have the following three steps
	 * taken:
	 * - बंद the observation पूर्णांकerval at the last (previous)
	 *   request dispatch or completion
	 * - compute rate, अगर possible, क्रम that observation पूर्णांकerval
	 * - reset to zero samples, which will trigger a proper
	 *   re-initialization of the observation पूर्णांकerval on next
	 *   dispatch
	 */
	अगर (delta_us > BFQ_MIN_TT/NSEC_PER_USEC &&
	   (bfqd->last_rq_max_size<<BFQ_RATE_SHIFT)/delta_us <
			1UL<<(BFQ_RATE_SHIFT - 10))
		bfq_update_rate_reset(bfqd, शून्य);
	bfqd->last_completion = now_ns;
	/*
	 * Shared queues are likely to receive I/O at a high
	 * rate. This may deceptively let them be considered as wakers
	 * of other queues. But a false waker will unjustly steal
	 * bandwidth to its supposedly woken queue. So considering
	 * also shared queues in the waking mechanism may cause more
	 * control troubles than throughput benefits. Then करो not set
	 * last_completed_rq_bfqq to bfqq अगर bfqq is a shared queue.
	 */
	अगर (!bfq_bfqq_coop(bfqq))
		bfqd->last_completed_rq_bfqq = bfqq;

	/*
	 * If we are रुकोing to discover whether the request pattern
	 * of the task associated with the queue is actually
	 * isochronous, and both requisites क्रम this condition to hold
	 * are now satisfied, then compute soft_rt_next_start (see the
	 * comments on the function bfq_bfqq_softrt_next_start()). We
	 * करो not compute soft_rt_next_start अगर bfqq is in पूर्णांकeractive
	 * weight raising (see the comments in bfq_bfqq_expire() क्रम
	 * an explanation). We schedule this delayed update when bfqq
	 * expires, अगर it still has in-flight requests.
	 */
	अगर (bfq_bfqq_softrt_update(bfqq) && bfqq->dispatched == 0 &&
	    RB_EMPTY_ROOT(&bfqq->sort_list) &&
	    bfqq->wr_coeff != bfqd->bfq_wr_coeff)
		bfqq->soft_rt_next_start =
			bfq_bfqq_softrt_next_start(bfqd, bfqq);

	/*
	 * If this is the in-service queue, check अगर it needs to be expired,
	 * or अगर we want to idle in हाल it has no pending requests.
	 */
	अगर (bfqd->in_service_queue == bfqq) अणु
		अगर (bfq_bfqq_must_idle(bfqq)) अणु
			अगर (bfqq->dispatched == 0)
				bfq_arm_slice_समयr(bfqd);
			/*
			 * If we get here, we करो not expire bfqq, even
			 * अगर bfqq was in budget समयout or had no
			 * more requests (as controlled in the next
			 * conditional inकाष्ठाions). The reason क्रम
			 * not expiring bfqq is as follows.
			 *
			 * Here bfqq->dispatched > 0 holds, but
			 * bfq_bfqq_must_idle() वापसed true. This
			 * implies that, even अगर no request arrives
			 * क्रम bfqq beक्रमe bfqq->dispatched reaches 0,
			 * bfqq will, however, not be expired on the
			 * completion event that causes bfqq->dispatch
			 * to reach zero. In contrast, on this event,
			 * bfqq will start enjoying device idling
			 * (I/O-dispatch plugging).
			 *
			 * But, अगर we expired bfqq here, bfqq would
			 * not have the chance to enjoy device idling
			 * when bfqq->dispatched finally reaches
			 * zero. This would expose bfqq to violation
			 * of its reserved service guarantees.
			 */
			वापस;
		पूर्ण अन्यथा अगर (bfq_may_expire_क्रम_budg_समयout(bfqq))
			bfq_bfqq_expire(bfqd, bfqq, false,
					BFQQE_BUDGET_TIMEOUT);
		अन्यथा अगर (RB_EMPTY_ROOT(&bfqq->sort_list) &&
			 (bfqq->dispatched == 0 ||
			  !bfq_better_to_idle(bfqq)))
			bfq_bfqq_expire(bfqd, bfqq, false,
					BFQQE_NO_MORE_REQUESTS);
	पूर्ण

	अगर (!bfqd->rq_in_driver)
		bfq_schedule_dispatch(bfqd);
पूर्ण

अटल व्योम bfq_finish_requeue_request_body(काष्ठा bfq_queue *bfqq)
अणु
	bfqq->allocated--;

	bfq_put_queue(bfqq);
पूर्ण

/*
 * The processes associated with bfqq may happen to generate their
 * cumulative I/O at a lower rate than the rate at which the device
 * could serve the same I/O. This is rather probable, e.g., अगर only
 * one process is associated with bfqq and the device is an SSD. It
 * results in bfqq becoming often empty जबतक in service. In this
 * respect, अगर BFQ is allowed to चयन to another queue when bfqq
 * reमुख्यs empty, then the device goes on being fed with I/O requests,
 * and the throughput is not affected. In contrast, अगर BFQ is not
 * allowed to चयन to another queue---because bfqq is sync and
 * I/O-dispatch needs to be plugged जबतक bfqq is temporarily
 * empty---then, during the service of bfqq, there will be frequent
 * "service holes", i.e., समय पूर्णांकervals during which bfqq माला_लो empty
 * and the device can only consume the I/O alपढ़ोy queued in its
 * hardware queues. During service holes, the device may even get to
 * reमुख्यing idle. In the end, during the service of bfqq, the device
 * is driven at a lower speed than the one it can reach with the kind
 * of I/O flowing through bfqq.
 *
 * To counter this loss of throughput, BFQ implements a "request
 * injection mechanism", which tries to fill the above service holes
 * with I/O requests taken from other queues. The hard part in this
 * mechanism is finding the right amount of I/O to inject, so as to
 * both boost throughput and not अवरोध bfqq's bandwidth and latency
 * guarantees. In this respect, the mechanism मुख्यtains a per-queue
 * inject limit, computed as below. While bfqq is empty, the injection
 * mechanism dispatches extra I/O requests only until the total number
 * of I/O requests in flight---i.e., alपढ़ोy dispatched but not yet
 * completed---reमुख्यs lower than this limit.
 *
 * A first definition comes in handy to पूर्णांकroduce the algorithm by
 * which the inject limit is computed.  We define as first request क्रम
 * bfqq, an I/O request क्रम bfqq that arrives जबतक bfqq is in
 * service, and causes bfqq to चयन from empty to non-empty. The
 * algorithm updates the limit as a function of the effect of
 * injection on the service बार of only the first requests of
 * bfqq. The reason क्रम this restriction is that these are the
 * requests whose service समय is affected most, because they are the
 * first to arrive after injection possibly occurred.
 *
 * To evaluate the effect of injection, the algorithm measures the
 * "total service time" of first requests. We define as total service
 * समय of an I/O request, the समय that elapses since when the
 * request is enqueued पूर्णांकo bfqq, to when it is completed. This
 * quantity allows the whole effect of injection to be measured. It is
 * easy to see why. Suppose that some requests of other queues are
 * actually injected जबतक bfqq is empty, and that a new request R
 * then arrives क्रम bfqq. If the device करोes start to serve all or
 * part of the injected requests during the service hole, then,
 * because of this extra service, it may delay the next invocation of
 * the dispatch hook of BFQ. Then, even after R माला_लो eventually
 * dispatched, the device may delay the actual service of R अगर it is
 * still busy serving the extra requests, or अगर it decides to serve,
 * beक्रमe R, some extra request still present in its queues. As a
 * conclusion, the cumulative extra delay caused by injection can be
 * easily evaluated by just comparing the total service समय of first
 * requests with and without injection.
 *
 * The limit-update algorithm works as follows. On the arrival of a
 * first request of bfqq, the algorithm measures the total समय of the
 * request only अगर one of the three हालs below holds, and, क्रम each
 * हाल, it updates the limit as described below:
 *
 * (1) If there is no in-flight request. This gives a baseline क्रम the
 *     total service समय of the requests of bfqq. If the baseline has
 *     not been computed yet, then, after computing it, the limit is
 *     set to 1, to start boosting throughput, and to prepare the
 *     ground क्रम the next हाल. If the baseline has alपढ़ोy been
 *     computed, then it is updated, in हाल it results to be lower
 *     than the previous value.
 *
 * (2) If the limit is higher than 0 and there are in-flight
 *     requests. By comparing the total service समय in this हाल with
 *     the above baseline, it is possible to know at which extent the
 *     current value of the limit is inflating the total service
 *     समय. If the inflation is below a certain threshold, then bfqq
 *     is assumed to be suffering from no perceivable loss of its
 *     service guarantees, and the limit is even tentatively
 *     increased. If the inflation is above the threshold, then the
 *     limit is decreased. Due to the lack of any hysteresis, this
 *     logic makes the limit oscillate even in steady workload
 *     conditions. Yet we opted क्रम it, because it is fast in reaching
 *     the best value क्रम the limit, as a function of the current I/O
 *     workload. To reduce oscillations, this step is disabled क्रम a
 *     लघु समय पूर्णांकerval after the limit happens to be decreased.
 *
 * (3) Periodically, after resetting the limit, to make sure that the
 *     limit eventually drops in हाल the workload changes. This is
 *     needed because, after the limit has gone safely up क्रम a
 *     certain workload, it is impossible to guess whether the
 *     baseline total service समय may have changed, without measuring
 *     it again without injection. A more effective version of this
 *     step might be to just sample the baseline, by पूर्णांकerrupting
 *     injection only once, and then to reset/lower the limit only अगर
 *     the total service समय with the current limit करोes happen to be
 *     too large.
 *
 * More details on each step are provided in the comments on the
 * pieces of code that implement these steps: the branch handling the
 * transition from empty to non empty in bfq_add_request(), the branch
 * handling injection in bfq_select_queue(), and the function
 * bfq_choose_bfqq_क्रम_injection(). These comments also explain some
 * exceptions, made by the injection mechanism in some special हालs.
 */
अटल व्योम bfq_update_inject_limit(काष्ठा bfq_data *bfqd,
				    काष्ठा bfq_queue *bfqq)
अणु
	u64 tot_समय_ns = kसमय_get_ns() - bfqd->last_empty_occupied_ns;
	अचिन्हित पूर्णांक old_limit = bfqq->inject_limit;

	अगर (bfqq->last_serv_समय_ns > 0 && bfqd->rqs_injected) अणु
		u64 threshold = (bfqq->last_serv_समय_ns * 3)>>1;

		अगर (tot_समय_ns >= threshold && old_limit > 0) अणु
			bfqq->inject_limit--;
			bfqq->decrease_समय_jअगर = jअगरfies;
		पूर्ण अन्यथा अगर (tot_समय_ns < threshold &&
			   old_limit <= bfqd->max_rq_in_driver)
			bfqq->inject_limit++;
	पूर्ण

	/*
	 * Either we still have to compute the base value क्रम the
	 * total service समय, and there seem to be the right
	 * conditions to करो it, or we can lower the last base value
	 * computed.
	 *
	 * NOTE: (bfqd->rq_in_driver == 1) means that there is no I/O
	 * request in flight, because this function is in the code
	 * path that handles the completion of a request of bfqq, and,
	 * in particular, this function is executed beक्रमe
	 * bfqd->rq_in_driver is decremented in such a code path.
	 */
	अगर ((bfqq->last_serv_समय_ns == 0 && bfqd->rq_in_driver == 1) ||
	    tot_समय_ns < bfqq->last_serv_समय_ns) अणु
		अगर (bfqq->last_serv_समय_ns == 0) अणु
			/*
			 * Now we certainly have a base value: make sure we
			 * start trying injection.
			 */
			bfqq->inject_limit = max_t(अचिन्हित पूर्णांक, 1, old_limit);
		पूर्ण
		bfqq->last_serv_समय_ns = tot_समय_ns;
	पूर्ण अन्यथा अगर (!bfqd->rqs_injected && bfqd->rq_in_driver == 1)
		/*
		 * No I/O injected and no request still in service in
		 * the drive: these are the exact conditions क्रम
		 * computing the base value of the total service समय
		 * क्रम bfqq. So let's update this value, because it is
		 * rather variable. For example, it varies अगर the size
		 * or the spatial locality of the I/O requests in bfqq
		 * change.
		 */
		bfqq->last_serv_समय_ns = tot_समय_ns;


	/* update complete, not रुकोing क्रम any request completion any दीर्घer */
	bfqd->रुकोed_rq = शून्य;
	bfqd->rqs_injected = false;
पूर्ण

/*
 * Handle either a requeue or a finish क्रम rq. The things to करो are
 * the same in both हालs: all references to rq are to be dropped. In
 * particular, rq is considered completed from the poपूर्णांक of view of
 * the scheduler.
 */
अटल व्योम bfq_finish_requeue_request(काष्ठा request *rq)
अणु
	काष्ठा bfq_queue *bfqq = RQ_BFQQ(rq);
	काष्ठा bfq_data *bfqd;

	/*
	 * rq either is not associated with any icq, or is an alपढ़ोy
	 * requeued request that has not (yet) been re-inserted पूर्णांकo
	 * a bfq_queue.
	 */
	अगर (!rq->elv.icq || !bfqq)
		वापस;

	bfqd = bfqq->bfqd;

	अगर (rq->rq_flags & RQF_STARTED)
		bfqg_stats_update_completion(bfqq_group(bfqq),
					     rq->start_समय_ns,
					     rq->io_start_समय_ns,
					     rq->cmd_flags);

	अगर (likely(rq->rq_flags & RQF_STARTED)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&bfqd->lock, flags);

		अगर (rq == bfqd->रुकोed_rq)
			bfq_update_inject_limit(bfqd, bfqq);

		bfq_completed_request(bfqq, bfqd);
		bfq_finish_requeue_request_body(bfqq);

		spin_unlock_irqrestore(&bfqd->lock, flags);
	पूर्ण अन्यथा अणु
		/*
		 * Request rq may be still/alपढ़ोy in the scheduler,
		 * in which हाल we need to हटाओ it (this should
		 * never happen in हाल of requeue). And we cannot
		 * defer such a check and removal, to aव्योम
		 * inconsistencies in the समय पूर्णांकerval from the end
		 * of this function to the start of the deferred work.
		 * This situation seems to occur only in process
		 * context, as a consequence of a merge. In the
		 * current version of the code, this implies that the
		 * lock is held.
		 */

		अगर (!RB_EMPTY_NODE(&rq->rb_node)) अणु
			bfq_हटाओ_request(rq->q, rq);
			bfqg_stats_update_io_हटाओ(bfqq_group(bfqq),
						    rq->cmd_flags);
		पूर्ण
		bfq_finish_requeue_request_body(bfqq);
	पूर्ण

	/*
	 * Reset निजी fields. In हाल of a requeue, this allows
	 * this function to correctly करो nothing अगर it is spuriously
	 * invoked again on this same request (see the check at the
	 * beginning of the function). Probably, a better general
	 * design would be to prevent blk-mq from invoking the requeue
	 * or finish hooks of an elevator, क्रम a request that is not
	 * referred by that elevator.
	 *
	 * Resetting the following fields would अवरोध the
	 * request-insertion logic अगर rq is re-inserted पूर्णांकo a bfq
	 * पूर्णांकernal queue, without a re-preparation. Here we assume
	 * that re-insertions of requeued requests, without
	 * re-preparation, can happen only क्रम pass_through or at_head
	 * requests (which are not re-inserted पूर्णांकo bfq पूर्णांकernal
	 * queues).
	 */
	rq->elv.priv[0] = शून्य;
	rq->elv.priv[1] = शून्य;
पूर्ण

/*
 * Removes the association between the current task and bfqq, assuming
 * that bic poपूर्णांकs to the bfq iocontext of the task.
 * Returns शून्य अगर a new bfqq should be allocated, or the old bfqq अगर this
 * was the last process referring to that bfqq.
 */
अटल काष्ठा bfq_queue *
bfq_split_bfqq(काष्ठा bfq_io_cq *bic, काष्ठा bfq_queue *bfqq)
अणु
	bfq_log_bfqq(bfqq->bfqd, bfqq, "splitting queue");

	अगर (bfqq_process_refs(bfqq) == 1) अणु
		bfqq->pid = current->pid;
		bfq_clear_bfqq_coop(bfqq);
		bfq_clear_bfqq_split_coop(bfqq);
		वापस bfqq;
	पूर्ण

	bic_set_bfqq(bic, शून्य, 1);

	bfq_put_coचालक(bfqq);

	bfq_release_process_ref(bfqq->bfqd, bfqq);
	वापस शून्य;
पूर्ण

अटल काष्ठा bfq_queue *bfq_get_bfqq_handle_split(काष्ठा bfq_data *bfqd,
						   काष्ठा bfq_io_cq *bic,
						   काष्ठा bio *bio,
						   bool split, bool is_sync,
						   bool *new_queue)
अणु
	काष्ठा bfq_queue *bfqq = bic_to_bfqq(bic, is_sync);

	अगर (likely(bfqq && bfqq != &bfqd->oom_bfqq))
		वापस bfqq;

	अगर (new_queue)
		*new_queue = true;

	अगर (bfqq)
		bfq_put_queue(bfqq);
	bfqq = bfq_get_queue(bfqd, bio, is_sync, bic, split);

	bic_set_bfqq(bic, bfqq, is_sync);
	अगर (split && is_sync) अणु
		अगर ((bic->was_in_burst_list && bfqd->large_burst) ||
		    bic->saved_in_large_burst)
			bfq_mark_bfqq_in_large_burst(bfqq);
		अन्यथा अणु
			bfq_clear_bfqq_in_large_burst(bfqq);
			अगर (bic->was_in_burst_list)
				/*
				 * If bfqq was in the current
				 * burst list beक्रमe being
				 * merged, then we have to add
				 * it back. And we करो not need
				 * to increase burst_size, as
				 * we did not decrement
				 * burst_size when we हटाओd
				 * bfqq from the burst list as
				 * a consequence of a merge
				 * (see comments in
				 * bfq_put_queue). In this
				 * respect, it would be rather
				 * costly to know whether the
				 * current burst list is still
				 * the same burst list from
				 * which bfqq was हटाओd on
				 * the merge. To aव्योम this
				 * cost, अगर bfqq was in a
				 * burst list, then we add
				 * bfqq to the current burst
				 * list without any further
				 * check. This can cause
				 * inappropriate insertions,
				 * but rarely enough to not
				 * harm the detection of large
				 * bursts signअगरicantly.
				 */
				hlist_add_head(&bfqq->burst_list_node,
					       &bfqd->burst_list);
		पूर्ण
		bfqq->split_समय = jअगरfies;
	पूर्ण

	वापस bfqq;
पूर्ण

/*
 * Only reset निजी fields. The actual request preparation will be
 * perक्रमmed by bfq_init_rq, when rq is either inserted or merged. See
 * comments on bfq_init_rq क्रम the reason behind this delayed
 * preparation.
 */
अटल व्योम bfq_prepare_request(काष्ठा request *rq)
अणु
	/*
	 * Regardless of whether we have an icq attached, we have to
	 * clear the scheduler poपूर्णांकers, as they might poपूर्णांक to
	 * previously allocated bic/bfqq काष्ठाs.
	 */
	rq->elv.priv[0] = rq->elv.priv[1] = शून्य;
पूर्ण

/*
 * If needed, init rq, allocate bfq data काष्ठाures associated with
 * rq, and increment reference counters in the destination bfq_queue
 * क्रम rq. Return the destination bfq_queue क्रम rq, or शून्य is rq is
 * not associated with any bfq_queue.
 *
 * This function is invoked by the functions that perक्रमm rq insertion
 * or merging. One may have expected the above preparation operations
 * to be perक्रमmed in bfq_prepare_request, and not delayed to when rq
 * is inserted or merged. The rationale behind this delayed
 * preparation is that, after the prepare_request hook is invoked क्रम
 * rq, rq may still be transक्रमmed पूर्णांकo a request with no icq, i.e., a
 * request not associated with any queue. No bfq hook is invoked to
 * संकेत this transक्रमmation. As a consequence, should these
 * preparation operations be perक्रमmed when the prepare_request hook
 * is invoked, and should rq be transक्रमmed one moment later, bfq
 * would end up in an inconsistent state, because it would have
 * incremented some queue counters क्रम an rq destined to
 * transक्रमmation, without any chance to correctly lower these
 * counters back. In contrast, no transक्रमmation can still happen क्रम
 * rq after rq has been inserted or merged. So, it is safe to execute
 * these preparation operations when rq is finally inserted or merged.
 */
अटल काष्ठा bfq_queue *bfq_init_rq(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा bio *bio = rq->bio;
	काष्ठा bfq_data *bfqd = q->elevator->elevator_data;
	काष्ठा bfq_io_cq *bic;
	स्थिर पूर्णांक is_sync = rq_is_sync(rq);
	काष्ठा bfq_queue *bfqq;
	bool new_queue = false;
	bool bfqq_alपढ़ोy_existing = false, split = false;

	अगर (unlikely(!rq->elv.icq))
		वापस शून्य;

	/*
	 * Assuming that elv.priv[1] is set only अगर everything is set
	 * क्रम this rq. This holds true, because this function is
	 * invoked only क्रम insertion or merging, and, after such
	 * events, a request cannot be manipulated any दीर्घer beक्रमe
	 * being हटाओd from bfq.
	 */
	अगर (rq->elv.priv[1])
		वापस rq->elv.priv[1];

	bic = icq_to_bic(rq->elv.icq);

	bfq_check_ioprio_change(bic, bio);

	bfq_bic_update_cgroup(bic, bio);

	bfqq = bfq_get_bfqq_handle_split(bfqd, bic, bio, false, is_sync,
					 &new_queue);

	अगर (likely(!new_queue)) अणु
		/* If the queue was seeky क्रम too दीर्घ, अवरोध it apart. */
		अगर (bfq_bfqq_coop(bfqq) && bfq_bfqq_split_coop(bfqq) &&
			!bic->stably_merged) अणु
			काष्ठा bfq_queue *old_bfqq = bfqq;

			/* Update bic beक्रमe losing reference to bfqq */
			अगर (bfq_bfqq_in_large_burst(bfqq))
				bic->saved_in_large_burst = true;

			bfqq = bfq_split_bfqq(bic, bfqq);
			split = true;

			अगर (!bfqq) अणु
				bfqq = bfq_get_bfqq_handle_split(bfqd, bic, bio,
								 true, is_sync,
								 शून्य);
				bfqq->waker_bfqq = old_bfqq->waker_bfqq;
				bfqq->tentative_waker_bfqq = शून्य;

				/*
				 * If the waker queue disappears, then
				 * new_bfqq->waker_bfqq must be
				 * reset. So insert new_bfqq पूर्णांकo the
				 * woken_list of the waker. See
				 * bfq_check_waker क्रम details.
				 */
				अगर (bfqq->waker_bfqq)
					hlist_add_head(&bfqq->woken_list_node,
						       &bfqq->waker_bfqq->woken_list);
			पूर्ण अन्यथा
				bfqq_alपढ़ोy_existing = true;
		पूर्ण
	पूर्ण

	bfqq->allocated++;
	bfqq->ref++;
	bfq_log_bfqq(bfqd, bfqq, "get_request %p: bfqq %p, %d",
		     rq, bfqq, bfqq->ref);

	rq->elv.priv[0] = bic;
	rq->elv.priv[1] = bfqq;

	/*
	 * If a bfq_queue has only one process reference, it is owned
	 * by only this bic: we can then set bfqq->bic = bic. in
	 * addition, अगर the queue has also just been split, we have to
	 * resume its state.
	 */
	अगर (likely(bfqq != &bfqd->oom_bfqq) && bfqq_process_refs(bfqq) == 1) अणु
		bfqq->bic = bic;
		अगर (split) अणु
			/*
			 * The queue has just been split from a shared
			 * queue: restore the idle winकरोw and the
			 * possible weight raising period.
			 */
			bfq_bfqq_resume_state(bfqq, bfqd, bic,
					      bfqq_alपढ़ोy_existing);
		पूर्ण
	पूर्ण

	/*
	 * Consider bfqq as possibly beदीर्घing to a burst of newly
	 * created queues only अगर:
	 * 1) A burst is actually happening (bfqd->burst_size > 0)
	 * or
	 * 2) There is no other active queue. In fact, अगर, in
	 *    contrast, there are active queues not beदीर्घing to the
	 *    possible burst bfqq may beदीर्घ to, then there is no gain
	 *    in considering bfqq as beदीर्घing to a burst, and
	 *    thereक्रमe in not weight-raising bfqq. See comments on
	 *    bfq_handle_burst().
	 *
	 * This filtering also helps eliminating false positives,
	 * occurring when bfqq करोes not beदीर्घ to an actual large
	 * burst, but some background task (e.g., a service) happens
	 * to trigger the creation of new queues very बंद to when
	 * bfqq and its possible companion queues are created. See
	 * comments on bfq_handle_burst() क्रम further details also on
	 * this issue.
	 */
	अगर (unlikely(bfq_bfqq_just_created(bfqq) &&
		     (bfqd->burst_size > 0 ||
		      bfq_tot_busy_queues(bfqd) == 0)))
		bfq_handle_burst(bfqd, bfqq);

	वापस bfqq;
पूर्ण

अटल व्योम
bfq_idle_slice_समयr_body(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	क्रमागत bfqq_expiration reason;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bfqd->lock, flags);

	/*
	 * Considering that bfqq may be in race, we should firstly check
	 * whether bfqq is in service beक्रमe करोing something on it. If
	 * the bfqq in race is not in service, it has alपढ़ोy been expired
	 * through __bfq_bfqq_expire func and its रुको_request flags has
	 * been cleared in __bfq_bfqd_reset_in_service func.
	 */
	अगर (bfqq != bfqd->in_service_queue) अणु
		spin_unlock_irqrestore(&bfqd->lock, flags);
		वापस;
	पूर्ण

	bfq_clear_bfqq_रुको_request(bfqq);

	अगर (bfq_bfqq_budget_समयout(bfqq))
		/*
		 * Also here the queue can be safely expired
		 * क्रम budget समयout without wasting
		 * guarantees
		 */
		reason = BFQQE_BUDGET_TIMEOUT;
	अन्यथा अगर (bfqq->queued[0] == 0 && bfqq->queued[1] == 0)
		/*
		 * The queue may not be empty upon समयr expiration,
		 * because we may not disable the समयr when the
		 * first request of the in-service queue arrives
		 * during disk idling.
		 */
		reason = BFQQE_TOO_IDLE;
	अन्यथा
		जाओ schedule_dispatch;

	bfq_bfqq_expire(bfqd, bfqq, true, reason);

schedule_dispatch:
	spin_unlock_irqrestore(&bfqd->lock, flags);
	bfq_schedule_dispatch(bfqd);
पूर्ण

/*
 * Handler of the expiration of the समयr running अगर the in-service queue
 * is idling inside its समय slice.
 */
अटल क्रमागत hrसमयr_restart bfq_idle_slice_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा bfq_data *bfqd = container_of(समयr, काष्ठा bfq_data,
					     idle_slice_समयr);
	काष्ठा bfq_queue *bfqq = bfqd->in_service_queue;

	/*
	 * Theoretical race here: the in-service queue can be शून्य or
	 * dअगरferent from the queue that was idling अगर a new request
	 * arrives क्रम the current queue and there is a full dispatch
	 * cycle that changes the in-service queue.  This can hardly
	 * happen, but in the worst हाल we just expire a queue too
	 * early.
	 */
	अगर (bfqq)
		bfq_idle_slice_समयr_body(bfqd, bfqq);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम __bfq_put_async_bfqq(काष्ठा bfq_data *bfqd,
				 काष्ठा bfq_queue **bfqq_ptr)
अणु
	काष्ठा bfq_queue *bfqq = *bfqq_ptr;

	bfq_log(bfqd, "put_async_bfqq: %p", bfqq);
	अगर (bfqq) अणु
		bfq_bfqq_move(bfqd, bfqq, bfqd->root_group);

		bfq_log_bfqq(bfqd, bfqq, "put_async_bfqq: putting %p, %d",
			     bfqq, bfqq->ref);
		bfq_put_queue(bfqq);
		*bfqq_ptr = शून्य;
	पूर्ण
पूर्ण

/*
 * Release all the bfqg references to its async queues.  If we are
 * deallocating the group these queues may still contain requests, so
 * we reparent them to the root cgroup (i.e., the only one that will
 * exist क्रम sure until all the requests on a device are gone).
 */
व्योम bfq_put_async_queues(काष्ठा bfq_data *bfqd, काष्ठा bfq_group *bfqg)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < 2; i++)
		क्रम (j = 0; j < IOPRIO_BE_NR; j++)
			__bfq_put_async_bfqq(bfqd, &bfqg->async_bfqq[i][j]);

	__bfq_put_async_bfqq(bfqd, &bfqg->async_idle_bfqq);
पूर्ण

/*
 * See the comments on bfq_limit_depth क्रम the purpose of
 * the depths set in the function. Return minimum shallow depth we'll use.
 */
अटल अचिन्हित पूर्णांक bfq_update_depths(काष्ठा bfq_data *bfqd,
				      काष्ठा sbiपंचांगap_queue *bt)
अणु
	अचिन्हित पूर्णांक i, j, min_shallow = अच_पूर्णांक_उच्च;

	/*
	 * In-word depths अगर no bfq_queue is being weight-उठाओd:
	 * leaving 25% of tags only क्रम sync पढ़ोs.
	 *
	 * In next क्रमmulas, right-shअगरt the value
	 * (1U<<bt->sb.shअगरt), instead of computing directly
	 * (1U<<(bt->sb.shअगरt - something)), to be robust against
	 * any possible value of bt->sb.shअगरt, without having to
	 * limit 'something'.
	 */
	/* no more than 50% of tags क्रम async I/O */
	bfqd->word_depths[0][0] = max((1U << bt->sb.shअगरt) >> 1, 1U);
	/*
	 * no more than 75% of tags क्रम sync ग_लिखोs (25% extra tags
	 * w.r.t. async I/O, to prevent async I/O from starving sync
	 * ग_लिखोs)
	 */
	bfqd->word_depths[0][1] = max(((1U << bt->sb.shअगरt) * 3) >> 2, 1U);

	/*
	 * In-word depths in हाल some bfq_queue is being weight-
	 * उठाओd: leaving ~63% of tags क्रम sync पढ़ोs. This is the
	 * highest percentage क्रम which, in our tests, application
	 * start-up बार didn't suffer from any regression due to tag
	 * लघुage.
	 */
	/* no more than ~18% of tags क्रम async I/O */
	bfqd->word_depths[1][0] = max(((1U << bt->sb.shअगरt) * 3) >> 4, 1U);
	/* no more than ~37% of tags क्रम sync ग_लिखोs (~20% extra tags) */
	bfqd->word_depths[1][1] = max(((1U << bt->sb.shअगरt) * 6) >> 4, 1U);

	क्रम (i = 0; i < 2; i++)
		क्रम (j = 0; j < 2; j++)
			min_shallow = min(min_shallow, bfqd->word_depths[i][j]);

	वापस min_shallow;
पूर्ण

अटल व्योम bfq_depth_updated(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा bfq_data *bfqd = hctx->queue->elevator->elevator_data;
	काष्ठा blk_mq_tags *tags = hctx->sched_tags;
	अचिन्हित पूर्णांक min_shallow;

	min_shallow = bfq_update_depths(bfqd, tags->biपंचांगap_tags);
	sbiपंचांगap_queue_min_shallow_depth(tags->biपंचांगap_tags, min_shallow);
पूर्ण

अटल पूर्णांक bfq_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित पूर्णांक index)
अणु
	bfq_depth_updated(hctx);
	वापस 0;
पूर्ण

अटल व्योम bfq_निकास_queue(काष्ठा elevator_queue *e)
अणु
	काष्ठा bfq_data *bfqd = e->elevator_data;
	काष्ठा bfq_queue *bfqq, *n;

	hrसमयr_cancel(&bfqd->idle_slice_समयr);

	spin_lock_irq(&bfqd->lock);
	list_क्रम_each_entry_safe(bfqq, n, &bfqd->idle_list, bfqq_list)
		bfq_deactivate_bfqq(bfqd, bfqq, false, false);
	spin_unlock_irq(&bfqd->lock);

	hrसमयr_cancel(&bfqd->idle_slice_समयr);

	/* release oom-queue reference to root group */
	bfqg_and_blkg_put(bfqd->root_group);

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	blkcg_deactivate_policy(bfqd->queue, &blkcg_policy_bfq);
#अन्यथा
	spin_lock_irq(&bfqd->lock);
	bfq_put_async_queues(bfqd, bfqd->root_group);
	kमुक्त(bfqd->root_group);
	spin_unlock_irq(&bfqd->lock);
#पूर्ण_अगर

	kमुक्त(bfqd);
पूर्ण

अटल व्योम bfq_init_root_group(काष्ठा bfq_group *root_group,
				काष्ठा bfq_data *bfqd)
अणु
	पूर्णांक i;

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	root_group->entity.parent = शून्य;
	root_group->my_entity = शून्य;
	root_group->bfqd = bfqd;
#पूर्ण_अगर
	root_group->rq_pos_tree = RB_ROOT;
	क्रम (i = 0; i < BFQ_IOPRIO_CLASSES; i++)
		root_group->sched_data.service_tree[i] = BFQ_SERVICE_TREE_INIT;
	root_group->sched_data.bfq_class_idle_last_service = jअगरfies;
पूर्ण

अटल पूर्णांक bfq_init_queue(काष्ठा request_queue *q, काष्ठा elevator_type *e)
अणु
	काष्ठा bfq_data *bfqd;
	काष्ठा elevator_queue *eq;

	eq = elevator_alloc(q, e);
	अगर (!eq)
		वापस -ENOMEM;

	bfqd = kzalloc_node(माप(*bfqd), GFP_KERNEL, q->node);
	अगर (!bfqd) अणु
		kobject_put(&eq->kobj);
		वापस -ENOMEM;
	पूर्ण
	eq->elevator_data = bfqd;

	spin_lock_irq(&q->queue_lock);
	q->elevator = eq;
	spin_unlock_irq(&q->queue_lock);

	/*
	 * Our fallback bfqq अगर bfq_find_alloc_queue() runs पूर्णांकo OOM issues.
	 * Grab a permanent reference to it, so that the normal code flow
	 * will not attempt to मुक्त it.
	 */
	bfq_init_bfqq(bfqd, &bfqd->oom_bfqq, शून्य, 1, 0);
	bfqd->oom_bfqq.ref++;
	bfqd->oom_bfqq.new_ioprio = BFQ_DEFAULT_QUEUE_IOPRIO;
	bfqd->oom_bfqq.new_ioprio_class = IOPRIO_CLASS_BE;
	bfqd->oom_bfqq.entity.new_weight =
		bfq_ioprio_to_weight(bfqd->oom_bfqq.new_ioprio);

	/* oom_bfqq करोes not participate to bursts */
	bfq_clear_bfqq_just_created(&bfqd->oom_bfqq);

	/*
	 * Trigger weight initialization, according to ioprio, at the
	 * oom_bfqq's first activation. The oom_bfqq's ioprio and ioprio
	 * class won't be changed any more.
	 */
	bfqd->oom_bfqq.entity.prio_changed = 1;

	bfqd->queue = q;

	INIT_LIST_HEAD(&bfqd->dispatch);

	hrसमयr_init(&bfqd->idle_slice_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);
	bfqd->idle_slice_समयr.function = bfq_idle_slice_समयr;

	bfqd->queue_weights_tree = RB_ROOT_CACHED;
	bfqd->num_groups_with_pending_reqs = 0;

	INIT_LIST_HEAD(&bfqd->active_list);
	INIT_LIST_HEAD(&bfqd->idle_list);
	INIT_HLIST_HEAD(&bfqd->burst_list);

	bfqd->hw_tag = -1;
	bfqd->nonrot_with_queueing = blk_queue_nonrot(bfqd->queue);

	bfqd->bfq_max_budget = bfq_शेष_max_budget;

	bfqd->bfq_fअगरo_expire[0] = bfq_fअगरo_expire[0];
	bfqd->bfq_fअगरo_expire[1] = bfq_fअगरo_expire[1];
	bfqd->bfq_back_max = bfq_back_max;
	bfqd->bfq_back_penalty = bfq_back_penalty;
	bfqd->bfq_slice_idle = bfq_slice_idle;
	bfqd->bfq_समयout = bfq_समयout;

	bfqd->bfq_large_burst_thresh = 8;
	bfqd->bfq_burst_पूर्णांकerval = msecs_to_jअगरfies(180);

	bfqd->low_latency = true;

	/*
	 * Trade-off between responsiveness and fairness.
	 */
	bfqd->bfq_wr_coeff = 30;
	bfqd->bfq_wr_rt_max_समय = msecs_to_jअगरfies(300);
	bfqd->bfq_wr_max_समय = 0;
	bfqd->bfq_wr_min_idle_समय = msecs_to_jअगरfies(2000);
	bfqd->bfq_wr_min_पूर्णांकer_arr_async = msecs_to_jअगरfies(500);
	bfqd->bfq_wr_max_softrt_rate = 7000; /*
					      * Approximate rate required
					      * to playback or record a
					      * high-definition compressed
					      * video.
					      */
	bfqd->wr_busy_queues = 0;

	/*
	 * Begin by assuming, optimistically, that the device peak
	 * rate is equal to 2/3 of the highest reference rate.
	 */
	bfqd->rate_dur_prod = ref_rate[blk_queue_nonrot(bfqd->queue)] *
		ref_wr_duration[blk_queue_nonrot(bfqd->queue)];
	bfqd->peak_rate = ref_rate[blk_queue_nonrot(bfqd->queue)] * 2 / 3;

	spin_lock_init(&bfqd->lock);

	/*
	 * The invocation of the next bfq_create_group_hierarchy
	 * function is the head of a chain of function calls
	 * (bfq_create_group_hierarchy->blkcg_activate_policy->
	 * blk_mq_मुक्तze_queue) that may lead to the invocation of the
	 * has_work hook function. For this reason,
	 * bfq_create_group_hierarchy is invoked only after all
	 * scheduler data has been initialized, apart from the fields
	 * that can be initialized only after invoking
	 * bfq_create_group_hierarchy. This, in particular, enables
	 * has_work to correctly वापस false. Of course, to aव्योम
	 * other inconsistencies, the blk-mq stack must then refrain
	 * from invoking further scheduler hooks beक्रमe this init
	 * function is finished.
	 */
	bfqd->root_group = bfq_create_group_hierarchy(bfqd, q->node);
	अगर (!bfqd->root_group)
		जाओ out_मुक्त;
	bfq_init_root_group(bfqd->root_group, bfqd);
	bfq_init_entity(&bfqd->oom_bfqq.entity, bfqd->root_group);

	wbt_disable_शेष(q);
	वापस 0;

out_मुक्त:
	kमुक्त(bfqd);
	kobject_put(&eq->kobj);
	वापस -ENOMEM;
पूर्ण

अटल व्योम bfq_slab_समाप्त(व्योम)
अणु
	kmem_cache_destroy(bfq_pool);
पूर्ण

अटल पूर्णांक __init bfq_slab_setup(व्योम)
अणु
	bfq_pool = KMEM_CACHE(bfq_queue, 0);
	अगर (!bfq_pool)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार bfq_var_show(अचिन्हित पूर्णांक var, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", var);
पूर्ण

अटल पूर्णांक bfq_var_store(अचिन्हित दीर्घ *var, स्थिर अक्षर *page)
अणु
	अचिन्हित दीर्घ new_val;
	पूर्णांक ret = kम_से_अदीर्घ(page, 10, &new_val);

	अगर (ret)
		वापस ret;
	*var = new_val;
	वापस 0;
पूर्ण

#घोषणा SHOW_FUNCTION(__FUNC, __VAR, __CONV)				\
अटल sमाप_प्रकार __FUNC(काष्ठा elevator_queue *e, अक्षर *page)		\
अणु									\
	काष्ठा bfq_data *bfqd = e->elevator_data;			\
	u64 __data = __VAR;						\
	अगर (__CONV == 1)						\
		__data = jअगरfies_to_msecs(__data);			\
	अन्यथा अगर (__CONV == 2)						\
		__data = भाग_u64(__data, NSEC_PER_MSEC);		\
	वापस bfq_var_show(__data, (page));				\
पूर्ण
SHOW_FUNCTION(bfq_fअगरo_expire_sync_show, bfqd->bfq_fअगरo_expire[1], 2);
SHOW_FUNCTION(bfq_fअगरo_expire_async_show, bfqd->bfq_fअगरo_expire[0], 2);
SHOW_FUNCTION(bfq_back_seek_max_show, bfqd->bfq_back_max, 0);
SHOW_FUNCTION(bfq_back_seek_penalty_show, bfqd->bfq_back_penalty, 0);
SHOW_FUNCTION(bfq_slice_idle_show, bfqd->bfq_slice_idle, 2);
SHOW_FUNCTION(bfq_max_budget_show, bfqd->bfq_user_max_budget, 0);
SHOW_FUNCTION(bfq_समयout_sync_show, bfqd->bfq_समयout, 1);
SHOW_FUNCTION(bfq_strict_guarantees_show, bfqd->strict_guarantees, 0);
SHOW_FUNCTION(bfq_low_latency_show, bfqd->low_latency, 0);
#अघोषित SHOW_FUNCTION

#घोषणा USEC_SHOW_FUNCTION(__FUNC, __VAR)				\
अटल sमाप_प्रकार __FUNC(काष्ठा elevator_queue *e, अक्षर *page)		\
अणु									\
	काष्ठा bfq_data *bfqd = e->elevator_data;			\
	u64 __data = __VAR;						\
	__data = भाग_u64(__data, NSEC_PER_USEC);			\
	वापस bfq_var_show(__data, (page));				\
पूर्ण
USEC_SHOW_FUNCTION(bfq_slice_idle_us_show, bfqd->bfq_slice_idle);
#अघोषित USEC_SHOW_FUNCTION

#घोषणा STORE_FUNCTION(__FUNC, __PTR, MIN, MAX, __CONV)			\
अटल sमाप_प्रकार								\
__FUNC(काष्ठा elevator_queue *e, स्थिर अक्षर *page, माप_प्रकार count)	\
अणु									\
	काष्ठा bfq_data *bfqd = e->elevator_data;			\
	अचिन्हित दीर्घ __data, __min = (MIN), __max = (MAX);		\
	पूर्णांक ret;							\
									\
	ret = bfq_var_store(&__data, (page));				\
	अगर (ret)							\
		वापस ret;						\
	अगर (__data < __min)						\
		__data = __min;						\
	अन्यथा अगर (__data > __max)					\
		__data = __max;						\
	अगर (__CONV == 1)						\
		*(__PTR) = msecs_to_jअगरfies(__data);			\
	अन्यथा अगर (__CONV == 2)						\
		*(__PTR) = (u64)__data * NSEC_PER_MSEC;			\
	अन्यथा								\
		*(__PTR) = __data;					\
	वापस count;							\
पूर्ण
STORE_FUNCTION(bfq_fअगरo_expire_sync_store, &bfqd->bfq_fअगरo_expire[1], 1,
		पूर्णांक_उच्च, 2);
STORE_FUNCTION(bfq_fअगरo_expire_async_store, &bfqd->bfq_fअगरo_expire[0], 1,
		पूर्णांक_उच्च, 2);
STORE_FUNCTION(bfq_back_seek_max_store, &bfqd->bfq_back_max, 0, पूर्णांक_उच्च, 0);
STORE_FUNCTION(bfq_back_seek_penalty_store, &bfqd->bfq_back_penalty, 1,
		पूर्णांक_उच्च, 0);
STORE_FUNCTION(bfq_slice_idle_store, &bfqd->bfq_slice_idle, 0, पूर्णांक_उच्च, 2);
#अघोषित STORE_FUNCTION

#घोषणा USEC_STORE_FUNCTION(__FUNC, __PTR, MIN, MAX)			\
अटल sमाप_प्रकार __FUNC(काष्ठा elevator_queue *e, स्थिर अक्षर *page, माप_प्रकार count)\
अणु									\
	काष्ठा bfq_data *bfqd = e->elevator_data;			\
	अचिन्हित दीर्घ __data, __min = (MIN), __max = (MAX);		\
	पूर्णांक ret;							\
									\
	ret = bfq_var_store(&__data, (page));				\
	अगर (ret)							\
		वापस ret;						\
	अगर (__data < __min)						\
		__data = __min;						\
	अन्यथा अगर (__data > __max)					\
		__data = __max;						\
	*(__PTR) = (u64)__data * NSEC_PER_USEC;				\
	वापस count;							\
पूर्ण
USEC_STORE_FUNCTION(bfq_slice_idle_us_store, &bfqd->bfq_slice_idle, 0,
		    अच_पूर्णांक_उच्च);
#अघोषित USEC_STORE_FUNCTION

अटल sमाप_प्रकार bfq_max_budget_store(काष्ठा elevator_queue *e,
				    स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा bfq_data *bfqd = e->elevator_data;
	अचिन्हित दीर्घ __data;
	पूर्णांक ret;

	ret = bfq_var_store(&__data, (page));
	अगर (ret)
		वापस ret;

	अगर (__data == 0)
		bfqd->bfq_max_budget = bfq_calc_max_budget(bfqd);
	अन्यथा अणु
		अगर (__data > पूर्णांक_उच्च)
			__data = पूर्णांक_उच्च;
		bfqd->bfq_max_budget = __data;
	पूर्ण

	bfqd->bfq_user_max_budget = __data;

	वापस count;
पूर्ण

/*
 * Leaving this name to preserve name compatibility with cfq
 * parameters, but this समयout is used क्रम both sync and async.
 */
अटल sमाप_प्रकार bfq_समयout_sync_store(काष्ठा elevator_queue *e,
				      स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा bfq_data *bfqd = e->elevator_data;
	अचिन्हित दीर्घ __data;
	पूर्णांक ret;

	ret = bfq_var_store(&__data, (page));
	अगर (ret)
		वापस ret;

	अगर (__data < 1)
		__data = 1;
	अन्यथा अगर (__data > पूर्णांक_उच्च)
		__data = पूर्णांक_उच्च;

	bfqd->bfq_समयout = msecs_to_jअगरfies(__data);
	अगर (bfqd->bfq_user_max_budget == 0)
		bfqd->bfq_max_budget = bfq_calc_max_budget(bfqd);

	वापस count;
पूर्ण

अटल sमाप_प्रकार bfq_strict_guarantees_store(काष्ठा elevator_queue *e,
				     स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा bfq_data *bfqd = e->elevator_data;
	अचिन्हित दीर्घ __data;
	पूर्णांक ret;

	ret = bfq_var_store(&__data, (page));
	अगर (ret)
		वापस ret;

	अगर (__data > 1)
		__data = 1;
	अगर (!bfqd->strict_guarantees && __data == 1
	    && bfqd->bfq_slice_idle < 8 * NSEC_PER_MSEC)
		bfqd->bfq_slice_idle = 8 * NSEC_PER_MSEC;

	bfqd->strict_guarantees = __data;

	वापस count;
पूर्ण

अटल sमाप_प्रकार bfq_low_latency_store(काष्ठा elevator_queue *e,
				     स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा bfq_data *bfqd = e->elevator_data;
	अचिन्हित दीर्घ __data;
	पूर्णांक ret;

	ret = bfq_var_store(&__data, (page));
	अगर (ret)
		वापस ret;

	अगर (__data > 1)
		__data = 1;
	अगर (__data == 0 && bfqd->low_latency != 0)
		bfq_end_wr(bfqd);
	bfqd->low_latency = __data;

	वापस count;
पूर्ण

#घोषणा BFQ_ATTR(name) \
	__ATTR(name, 0644, bfq_##name##_show, bfq_##name##_store)

अटल काष्ठा elv_fs_entry bfq_attrs[] = अणु
	BFQ_ATTR(fअगरo_expire_sync),
	BFQ_ATTR(fअगरo_expire_async),
	BFQ_ATTR(back_seek_max),
	BFQ_ATTR(back_seek_penalty),
	BFQ_ATTR(slice_idle),
	BFQ_ATTR(slice_idle_us),
	BFQ_ATTR(max_budget),
	BFQ_ATTR(समयout_sync),
	BFQ_ATTR(strict_guarantees),
	BFQ_ATTR(low_latency),
	__ATTR_शून्य
पूर्ण;

अटल काष्ठा elevator_type iosched_bfq_mq = अणु
	.ops = अणु
		.limit_depth		= bfq_limit_depth,
		.prepare_request	= bfq_prepare_request,
		.requeue_request        = bfq_finish_requeue_request,
		.finish_request		= bfq_finish_requeue_request,
		.निकास_icq		= bfq_निकास_icq,
		.insert_requests	= bfq_insert_requests,
		.dispatch_request	= bfq_dispatch_request,
		.next_request		= elv_rb_latter_request,
		.क्रमmer_request		= elv_rb_क्रमmer_request,
		.allow_merge		= bfq_allow_bio_merge,
		.bio_merge		= bfq_bio_merge,
		.request_merge		= bfq_request_merge,
		.requests_merged	= bfq_requests_merged,
		.request_merged		= bfq_request_merged,
		.has_work		= bfq_has_work,
		.depth_updated		= bfq_depth_updated,
		.init_hctx		= bfq_init_hctx,
		.init_sched		= bfq_init_queue,
		.निकास_sched		= bfq_निकास_queue,
	पूर्ण,

	.icq_size =		माप(काष्ठा bfq_io_cq),
	.icq_align =		__alignof__(काष्ठा bfq_io_cq),
	.elevator_attrs =	bfq_attrs,
	.elevator_name =	"bfq",
	.elevator_owner =	THIS_MODULE,
पूर्ण;
MODULE_ALIAS("bfq-iosched");

अटल पूर्णांक __init bfq_init(व्योम)
अणु
	पूर्णांक ret;

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	ret = blkcg_policy_रेजिस्टर(&blkcg_policy_bfq);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर

	ret = -ENOMEM;
	अगर (bfq_slab_setup())
		जाओ err_pol_unreg;

	/*
	 * Times to load large popular applications क्रम the typical
	 * प्रणालीs installed on the reference devices (see the
	 * comments beक्रमe the definition of the next
	 * array). Actually, we use slightly lower values, as the
	 * estimated peak rate tends to be smaller than the actual
	 * peak rate.  The reason क्रम this last fact is that estimates
	 * are computed over much लघुer समय पूर्णांकervals than the दीर्घ
	 * पूर्णांकervals typically used क्रम benchmarking. Why? First, to
	 * adapt more quickly to variations. Second, because an I/O
	 * scheduler cannot rely on a peak-rate-evaluation workload to
	 * be run क्रम a दीर्घ समय.
	 */
	ref_wr_duration[0] = msecs_to_jअगरfies(7000); /* actually 8 sec */
	ref_wr_duration[1] = msecs_to_jअगरfies(2500); /* actually 3 sec */

	ret = elv_रेजिस्टर(&iosched_bfq_mq);
	अगर (ret)
		जाओ slab_समाप्त;

	वापस 0;

slab_समाप्त:
	bfq_slab_समाप्त();
err_pol_unreg:
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	blkcg_policy_unरेजिस्टर(&blkcg_policy_bfq);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम __निकास bfq_निकास(व्योम)
अणु
	elv_unरेजिस्टर(&iosched_bfq_mq);
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	blkcg_policy_unरेजिस्टर(&blkcg_policy_bfq);
#पूर्ण_अगर
	bfq_slab_समाप्त();
पूर्ण

module_init(bfq_init);
module_निकास(bfq_निकास);

MODULE_AUTHOR("Paolo Valente");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MQ Budget Fair Queueing I/O Scheduler");
