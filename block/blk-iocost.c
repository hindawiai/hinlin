<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * IO cost model based controller.
 *
 * Copyright (C) 2019 Tejun Heo <tj@kernel.org>
 * Copyright (C) 2019 Andy Newell <newella@fb.com>
 * Copyright (C) 2019 Facebook
 *
 * One challenge of controlling IO resources is the lack of trivially
 * observable cost metric.  This is distinguished from CPU and memory where
 * wallघड़ी समय and the number of bytes can serve as accurate enough
 * approximations.
 *
 * Bandwidth and iops are the most commonly used metrics क्रम IO devices but
 * depending on the type and specअगरics of the device, dअगरferent IO patterns
 * easily lead to multiple orders of magnitude variations rendering them
 * useless क्रम the purpose of IO capacity distribution.  While on-device
 * समय, with a lot of clutches, could serve as a useful approximation क्रम
 * non-queued rotational devices, this is no दीर्घer viable with modern
 * devices, even the rotational ones.
 *
 * While there is no cost metric we can trivially observe, it isn't a
 * complete mystery.  For example, on a rotational device, seek cost
 * करोminates जबतक a contiguous transfer contributes a smaller amount
 * proportional to the size.  If we can अक्षरacterize at least the relative
 * costs of these dअगरferent types of IOs, it should be possible to
 * implement a reasonable work-conserving proportional IO resource
 * distribution.
 *
 * 1. IO Cost Model
 *
 * IO cost model estimates the cost of an IO given its basic parameters and
 * history (e.g. the end sector of the last IO).  The cost is measured in
 * device समय.  If a given IO is estimated to cost 10ms, the device should
 * be able to process ~100 of those IOs in a second.
 *
 * Currently, there's only one builtin cost model - linear.  Each IO is
 * classअगरied as sequential or अक्रमom and given a base cost accordingly.
 * On top of that, a size cost proportional to the length of the IO is
 * added.  While simple, this model captures the operational
 * अक्षरacteristics of a wide varienty of devices well enough.  Default
 * parameters क्रम several dअगरferent classes of devices are provided and the
 * parameters can be configured from userspace via
 * /sys/fs/cgroup/io.cost.model.
 *
 * If needed, tools/cgroup/iocost_coef_gen.py can be used to generate
 * device-specअगरic coefficients.
 *
 * 2. Control Strategy
 *
 * The device भव समय (vसमय) is used as the primary control metric.
 * The control strategy is composed of the following three parts.
 *
 * 2-1. Vसमय Distribution
 *
 * When a cgroup becomes active in terms of IOs, its hierarchical share is
 * calculated.  Please consider the following hierarchy where the numbers
 * inside parentheses denote the configured weights.
 *
 *           root
 *         /       \
 *      A (w:100)  B (w:300)
 *      /       \
 *  A0 (w:100)  A1 (w:100)
 *
 * If B is idle and only A0 and A1 are actively issuing IOs, as the two are
 * of equal weight, each माला_लो 50% share.  If then B starts issuing IOs, B
 * माला_लो 300/(100+300) or 75% share, and A0 and A1 equally splits the rest,
 * 12.5% each.  The distribution mechanism only cares about these flattened
 * shares.  They're called hweights (hierarchical weights) and always add
 * upto 1 (WEIGHT_ONE).
 *
 * A given cgroup's vसमय runs slower in inverse proportion to its hweight.
 * For example, with 12.5% weight, A0's समय runs 8 बार slower (100/12.5)
 * against the device vसमय - an IO which takes 10ms on the underlying
 * device is considered to take 80ms on A0.
 *
 * This स्थिरitutes the basis of IO capacity distribution.  Each cgroup's
 * vसमय is running at a rate determined by its hweight.  A cgroup tracks
 * the vसमय consumed by past IOs and can issue a new IO अगर करोing so
 * wouldn't outrun the current device vसमय.  Otherwise, the IO is
 * suspended until the vसमय has progressed enough to cover it.
 *
 * 2-2. Vrate Adjusपंचांगent
 *
 * It's unrealistic to expect the cost model to be perfect.  There are too
 * many devices and even on the same device the overall perक्रमmance
 * fluctuates depending on numerous factors such as IO mixture and device
 * पूर्णांकernal garbage collection.  The controller needs to adapt dynamically.
 *
 * This is achieved by adjusting the overall IO rate according to how busy
 * the device is.  If the device becomes overloaded, we're sending करोwn too
 * many IOs and should generally slow करोwn.  If there are रुकोing issuers
 * but the device isn't saturated, we're issuing too few and should
 * generally speed up.
 *
 * To slow करोwn, we lower the vrate - the rate at which the device vसमय
 * passes compared to the wall घड़ी.  For example, अगर the vसमय is running
 * at the vrate of 75%, all cgroups added up would only be able to issue
 * 750ms worth of IOs per second, and vice-versa क्रम speeding up.
 *
 * Device business is determined using two criteria - rq रुको and
 * completion latencies.
 *
 * When a device माला_लो saturated, the on-device and then the request queues
 * fill up and a bio which is पढ़ोy to be issued has to रुको क्रम a request
 * to become available.  When this delay becomes noticeable, it's a clear
 * indication that the device is saturated and we lower the vrate.  This
 * saturation संकेत is fairly conservative as it only triggers when both
 * hardware and software queues are filled up, and is used as the शेष
 * busy संकेत.
 *
 * As devices can have deep queues and be unfair in how the queued commands
 * are executed, soley depending on rq रुको may not result in satisfactory
 * control quality.  For a better control quality, completion latency QoS
 * parameters can be configured so that the device is considered saturated
 * अगर N'th percentile completion latency rises above the set poपूर्णांक.
 *
 * The completion latency requirements are a function of both the
 * underlying device अक्षरacteristics and the desired IO latency quality of
 * service.  There is an inherent trade-off - the tighter the latency QoS,
 * the higher the bandwidth lossage.  Latency QoS is disabled by शेष
 * and can be set through /sys/fs/cgroup/io.cost.qos.
 *
 * 2-3. Work Conservation
 *
 * Imagine two cgroups A and B with equal weights.  A is issuing a small IO
 * periodically जबतक B is sending out enough parallel IOs to saturate the
 * device on its own.  Let's say A's usage amounts to 100ms worth of IO
 * cost per second, i.e., 10% of the device capacity.  The naive
 * distribution of half and half would lead to 60% utilization of the
 * device, a signअगरicant reduction in the total amount of work करोne
 * compared to मुक्त-क्रम-all competition.  This is too high a cost to pay
 * क्रम IO control.
 *
 * To conserve the total amount of work करोne, we keep track of how much
 * each active cgroup is actually using and yield part of its weight अगर
 * there are other cgroups which can make use of it.  In the above हाल,
 * A's weight will be lowered so that it hovers above the actual usage and
 * B would be able to use the rest.
 *
 * As we करोn't want to penalize a cgroup क्रम करोnating its weight, the
 * surplus weight adjusपंचांगent factors in a margin and has an immediate
 * snapback mechanism in हाल the cgroup needs more IO vसमय क्रम itself.
 *
 * Note that adjusting करोwn surplus weights has the same effects as
 * accelerating vसमय क्रम other cgroups and work conservation can also be
 * implemented by adjusting vrate dynamically.  However, squaring who can
 * करोnate and should take back how much requires hweight propagations
 * anyway making it easier to implement and understand as a separate
 * mechanism.
 *
 * 3. Monitoring
 *
 * Instead of debugfs or other clumsy monitoring mechanisms, this
 * controller uses a drgn based monitoring script -
 * tools/cgroup/iocost_monitor.py.  For details on drgn, please see
 * https://github.com/osanकरोv/drgn.  The output looks like the following.
 *
 *  sdb RUN   per=300ms cur_per=234.218:v203.695 busy= +1 vrate= 62.12%
 *                 active      weight      hweight% inflt% dbt  delay usages%
 *  test/a              *    50/   50  33.33/ 33.33  27.65   2  0*041 033:033:033
 *  test/b              *   100/  100  66.67/ 66.67  17.56   0  0*000 066:079:077
 *
 * - per	: Timer period
 * - cur_per	: Internal wall and device vसमय घड़ी
 * - vrate	: Device भव समय rate against wall घड़ी
 * - weight	: Surplus-adjusted and configured weights
 * - hweight	: Surplus-adjusted and configured hierarchical weights
 * - inflt	: The percentage of in-flight IO cost at the end of last period
 * - del_ms	: Deferred issuer delay induction level and duration
 * - usages	: Usage history
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/समय64.h>
#समावेश <linux/parser.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/blk-cgroup.h>
#समावेश <यंत्र/local.h>
#समावेश <यंत्र/local64.h>
#समावेश "blk-rq-qos.h"
#समावेश "blk-stat.h"
#समावेश "blk-wbt.h"

#अगर_घोषित CONFIG_TRACEPOINTS

/* copied from TRACE_CGROUP_PATH, see cgroup-पूर्णांकernal.h */
#घोषणा TRACE_IOCG_PATH_LEN 1024
अटल DEFINE_SPINLOCK(trace_iocg_path_lock);
अटल अक्षर trace_iocg_path[TRACE_IOCG_PATH_LEN];

#घोषणा TRACE_IOCG_PATH(type, iocg, ...)					\
	करो अणु									\
		अचिन्हित दीर्घ flags;						\
		अगर (trace_iocost_##type##_enabled()) अणु				\
			spin_lock_irqsave(&trace_iocg_path_lock, flags);	\
			cgroup_path(iocg_to_blkg(iocg)->blkcg->css.cgroup,	\
				    trace_iocg_path, TRACE_IOCG_PATH_LEN);	\
			trace_iocost_##type(iocg, trace_iocg_path,		\
					      ##__VA_ARGS__);			\
			spin_unlock_irqrestore(&trace_iocg_path_lock, flags);	\
		पूर्ण								\
	पूर्ण जबतक (0)

#अन्यथा	/* CONFIG_TRACE_POINTS */
#घोषणा TRACE_IOCG_PATH(type, iocg, ...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर	/* CONFIG_TRACE_POINTS */

क्रमागत अणु
	MILLION			= 1000000,

	/* समयr period is calculated from latency requirements, bound it */
	MIN_PERIOD		= USEC_PER_MSEC,
	MAX_PERIOD		= USEC_PER_SEC,

	/*
	 * iocg->vसमय is targeted at 50% behind the device vसमय, which
	 * serves as its IO credit buffer.  Surplus weight adjusपंचांगent is
	 * immediately canceled अगर the vसमय margin runs below 10%.
	 */
	MARGIN_MIN_PCT		= 10,
	MARGIN_LOW_PCT		= 20,
	MARGIN_TARGET_PCT	= 50,

	INUSE_ADJ_STEP_PCT	= 25,

	/* Have some play in समयr operations */
	TIMER_SLACK_PCT		= 1,

	/* 1/64k is granular enough and can easily be handled w/ u32 */
	WEIGHT_ONE		= 1 << 16,

	/*
	 * As vसमय is used to calculate the cost of each IO, it needs to
	 * be fairly high precision.  For example, it should be able to
	 * represent the cost of a single page worth of discard with
	 * suffअगरicient accuracy.  At the same समय, it should be able to
	 * represent reasonably दीर्घ enough durations to be useful and
	 * convenient during operation.
	 *
	 * 1s worth of vसमय is 2^37.  This gives us both sub-nanosecond
	 * granularity and days of wrap-around समय even at extreme vrates.
	 */
	VTIME_PER_SEC_SHIFT	= 37,
	VTIME_PER_SEC		= 1LLU << VTIME_PER_SEC_SHIFT,
	VTIME_PER_USEC		= VTIME_PER_SEC / USEC_PER_SEC,
	VTIME_PER_NSEC		= VTIME_PER_SEC / NSEC_PER_SEC,

	/* bound vrate adjusपंचांगents within two orders of magnitude */
	VRATE_MIN_PPM		= 10000,	/* 1% */
	VRATE_MAX_PPM		= 100000000,	/* 10000% */

	VRATE_MIN		= VTIME_PER_USEC * VRATE_MIN_PPM / MILLION,
	VRATE_CLAMP_ADJ_PCT	= 4,

	/* अगर IOs end up रुकोing क्रम requests, issue less */
	RQ_WAIT_BUSY_PCT	= 5,

	/* unbusy hysterisis */
	UNBUSY_THR_PCT		= 75,

	/*
	 * The effect of delay is indirect and non-linear and a huge amount of
	 * future debt can accumulate abruptly जबतक unthrottled. Linearly scale
	 * up delay as debt is going up and then let it decay exponentially.
	 * This gives us quick ramp ups जबतक delay is accumulating and दीर्घ
	 * tails which can help reducing the frequency of debt explosions on
	 * unthrottle. The parameters are experimentally determined.
	 *
	 * The delay mechanism provides adequate protection and behavior in many
	 * हालs. However, this is far from ideal and falls लघुs on both
	 * fronts. The debtors are often throttled too harshly costing a
	 * signअगरicant level of fairness and possibly total work जबतक the
	 * protection against their impacts on the प्रणाली can be choppy and
	 * unreliable.
	 *
	 * The लघुcoming primarily stems from the fact that, unlike क्रम page
	 * cache, the kernel करोesn't have well-defined back-pressure propagation
	 * mechanism and policies क्रम anonymous memory. Fully addressing this
	 * issue will likely require substantial improvements in the area.
	 */
	MIN_DELAY_THR_PCT	= 500,
	MAX_DELAY_THR_PCT	= 25000,
	MIN_DELAY		= 250,
	MAX_DELAY		= 250 * USEC_PER_MSEC,

	/* halve debts अगर avg usage over 100ms is under 50% */
	DFGV_USAGE_PCT		= 50,
	DFGV_PERIOD		= 100 * USEC_PER_MSEC,

	/* करोn't let cmds which take a very दीर्घ समय pin lagging क्रम too दीर्घ */
	MAX_LAGGING_PERIODS	= 10,

	/* चयन अगरf the conditions are met क्रम दीर्घer than this */
	AUTOP_CYCLE_NSEC	= 10LLU * NSEC_PER_SEC,

	/*
	 * Count IO size in 4k pages.  The 12bit shअगरt helps keeping
	 * size-proportional components of cost calculation in बंदr
	 * numbers of digits to per-IO cost components.
	 */
	IOC_PAGE_SHIFT		= 12,
	IOC_PAGE_SIZE		= 1 << IOC_PAGE_SHIFT,
	IOC_SECT_TO_PAGE_SHIFT	= IOC_PAGE_SHIFT - SECTOR_SHIFT,

	/* अगर apart further than 16M, consider अक्रमio क्रम linear model */
	LCOEF_RANDIO_PAGES	= 4096,
पूर्ण;

क्रमागत ioc_running अणु
	IOC_IDLE,
	IOC_RUNNING,
	IOC_STOP,
पूर्ण;

/* io.cost.qos controls including per-dev enable of the whole controller */
क्रमागत अणु
	QOS_ENABLE,
	QOS_CTRL,
	NR_QOS_CTRL_PARAMS,
पूर्ण;

/* io.cost.qos params */
क्रमागत अणु
	QOS_RPPM,
	QOS_RLAT,
	QOS_WPPM,
	QOS_WLAT,
	QOS_MIN,
	QOS_MAX,
	NR_QOS_PARAMS,
पूर्ण;

/* io.cost.model controls */
क्रमागत अणु
	COST_CTRL,
	COST_MODEL,
	NR_COST_CTRL_PARAMS,
पूर्ण;

/* builtin linear cost model coefficients */
क्रमागत अणु
	I_LCOEF_RBPS,
	I_LCOEF_RSEQIOPS,
	I_LCOEF_RRANDIOPS,
	I_LCOEF_WBPS,
	I_LCOEF_WSEQIOPS,
	I_LCOEF_WRANDIOPS,
	NR_I_LCOEFS,
पूर्ण;

क्रमागत अणु
	LCOEF_RPAGE,
	LCOEF_RSEQIO,
	LCOEF_RRANDIO,
	LCOEF_WPAGE,
	LCOEF_WSEQIO,
	LCOEF_WRANDIO,
	NR_LCOEFS,
पूर्ण;

क्रमागत अणु
	AUTOP_INVALID,
	AUTOP_HDD,
	AUTOP_SSD_QD1,
	AUTOP_SSD_DFL,
	AUTOP_SSD_FAST,
पूर्ण;

काष्ठा ioc_params अणु
	u32				qos[NR_QOS_PARAMS];
	u64				i_lcoefs[NR_I_LCOEFS];
	u64				lcoefs[NR_LCOEFS];
	u32				too_fast_vrate_pct;
	u32				too_slow_vrate_pct;
पूर्ण;

काष्ठा ioc_margins अणु
	s64				min;
	s64				low;
	s64				target;
पूर्ण;

काष्ठा ioc_missed अणु
	local_t				nr_met;
	local_t				nr_missed;
	u32				last_met;
	u32				last_missed;
पूर्ण;

काष्ठा ioc_pcpu_stat अणु
	काष्ठा ioc_missed		missed[2];

	local64_t			rq_रुको_ns;
	u64				last_rq_रुको_ns;
पूर्ण;

/* per device */
काष्ठा ioc अणु
	काष्ठा rq_qos			rqos;

	bool				enabled;

	काष्ठा ioc_params		params;
	काष्ठा ioc_margins		margins;
	u32				period_us;
	u32				समयr_slack_ns;
	u64				vrate_min;
	u64				vrate_max;

	spinlock_t			lock;
	काष्ठा समयr_list		समयr;
	काष्ठा list_head		active_iocgs;	/* active cgroups */
	काष्ठा ioc_pcpu_stat __percpu	*pcpu_stat;

	क्रमागत ioc_running		running;
	atomic64_t			vसमय_rate;
	u64				vसमय_base_rate;
	s64				vसमय_err;

	seqcount_spinlock_t		period_seqcount;
	u64				period_at;	/* wallघड़ी startसमय */
	u64				period_at_vसमय; /* vसमय startसमय */

	atomic64_t			cur_period;	/* inc'd each period */
	पूर्णांक				busy_level;	/* saturation history */

	bool				weights_updated;
	atomic_t			hweight_gen;	/* क्रम lazy hweights */

	/* debt क्रमgivness */
	u64				dfgv_period_at;
	u64				dfgv_period_rem;
	u64				dfgv_usage_us_sum;

	u64				स्वतःp_too_fast_at;
	u64				स्वतःp_too_slow_at;
	पूर्णांक				स्वतःp_idx;
	bool				user_qos_params:1;
	bool				user_cost_model:1;
पूर्ण;

काष्ठा iocg_pcpu_stat अणु
	local64_t			असल_vusage;
पूर्ण;

काष्ठा iocg_stat अणु
	u64				usage_us;
	u64				रुको_us;
	u64				indebt_us;
	u64				indelay_us;
पूर्ण;

/* per device-cgroup pair */
काष्ठा ioc_gq अणु
	काष्ठा blkg_policy_data		pd;
	काष्ठा ioc			*ioc;

	/*
	 * A iocg can get its weight from two sources - an explicit
	 * per-device-cgroup configuration or the शेष weight of the
	 * cgroup.  `cfg_weight` is the explicit per-device-cgroup
	 * configuration.  `weight` is the effective considering both
	 * sources.
	 *
	 * When an idle cgroup becomes active its `active` goes from 0 to
	 * `weight`.  `inuse` is the surplus adjusted active weight.
	 * `active` and `inuse` are used to calculate `hweight_active` and
	 * `hweight_inuse`.
	 *
	 * `last_inuse` remembers `inuse` जबतक an iocg is idle to persist
	 * surplus adjusपंचांगents.
	 *
	 * `inuse` may be adjusted dynamically during period. `saved_*` are used
	 * to determine and track adjusपंचांगents.
	 */
	u32				cfg_weight;
	u32				weight;
	u32				active;
	u32				inuse;

	u32				last_inuse;
	s64				saved_margin;

	sector_t			cursor;		/* to detect अक्रमio */

	/*
	 * `vसमय` is this iocg's vसमय cursor which progresses as IOs are
	 * issued.  If lagging behind device vसमय, the delta represents
	 * the currently available IO budget.  If running ahead, the
	 * overage.
	 *
	 * `vसमय_करोne` is the same but progressed on completion rather
	 * than issue.  The delta behind `vसमय` represents the cost of
	 * currently in-flight IOs.
	 */
	atomic64_t			vसमय;
	atomic64_t			करोne_vसमय;
	u64				असल_vdebt;

	/* current delay in effect and when it started */
	u64				delay;
	u64				delay_at;

	/*
	 * The period this iocg was last active in.  Used क्रम deactivation
	 * and invalidating `vसमय`.
	 */
	atomic64_t			active_period;
	काष्ठा list_head		active_list;

	/* see __propagate_weights() and current_hweight() क्रम details */
	u64				child_active_sum;
	u64				child_inuse_sum;
	u64				child_adjusted_sum;
	पूर्णांक				hweight_gen;
	u32				hweight_active;
	u32				hweight_inuse;
	u32				hweight_करोnating;
	u32				hweight_after_करोnation;

	काष्ठा list_head		walk_list;
	काष्ठा list_head		surplus_list;

	काष्ठा रुको_queue_head		रुकोq;
	काष्ठा hrसमयr			रुकोq_समयr;

	/* बारtamp at the latest activation */
	u64				activated_at;

	/* statistics */
	काष्ठा iocg_pcpu_stat __percpu	*pcpu_stat;
	काष्ठा iocg_stat		local_stat;
	काष्ठा iocg_stat		desc_stat;
	काष्ठा iocg_stat		last_stat;
	u64				last_stat_असल_vusage;
	u64				usage_delta_us;
	u64				रुको_since;
	u64				indebt_since;
	u64				indelay_since;

	/* this iocg's depth in the hierarchy and ancestors including self */
	पूर्णांक				level;
	काष्ठा ioc_gq			*ancestors[];
पूर्ण;

/* per cgroup */
काष्ठा ioc_cgrp अणु
	काष्ठा blkcg_policy_data	cpd;
	अचिन्हित पूर्णांक			dfl_weight;
पूर्ण;

काष्ठा ioc_now अणु
	u64				now_ns;
	u64				now;
	u64				vnow;
	u64				vrate;
पूर्ण;

काष्ठा iocg_रुको अणु
	काष्ठा रुको_queue_entry		रुको;
	काष्ठा bio			*bio;
	u64				असल_cost;
	bool				committed;
पूर्ण;

काष्ठा iocg_wake_ctx अणु
	काष्ठा ioc_gq			*iocg;
	u32				hw_inuse;
	s64				vbudget;
पूर्ण;

अटल स्थिर काष्ठा ioc_params स्वतःp[] = अणु
	[AUTOP_HDD] = अणु
		.qos				= अणु
			[QOS_RLAT]		=        250000, /* 250ms */
			[QOS_WLAT]		=        250000,
			[QOS_MIN]		= VRATE_MIN_PPM,
			[QOS_MAX]		= VRATE_MAX_PPM,
		पूर्ण,
		.i_lcoefs			= अणु
			[I_LCOEF_RBPS]		=     174019176,
			[I_LCOEF_RSEQIOPS]	=         41708,
			[I_LCOEF_RRANDIOPS]	=           370,
			[I_LCOEF_WBPS]		=     178075866,
			[I_LCOEF_WSEQIOPS]	=         42705,
			[I_LCOEF_WRANDIOPS]	=           378,
		पूर्ण,
	पूर्ण,
	[AUTOP_SSD_QD1] = अणु
		.qos				= अणु
			[QOS_RLAT]		=         25000, /* 25ms */
			[QOS_WLAT]		=         25000,
			[QOS_MIN]		= VRATE_MIN_PPM,
			[QOS_MAX]		= VRATE_MAX_PPM,
		पूर्ण,
		.i_lcoefs			= अणु
			[I_LCOEF_RBPS]		=     245855193,
			[I_LCOEF_RSEQIOPS]	=         61575,
			[I_LCOEF_RRANDIOPS]	=          6946,
			[I_LCOEF_WBPS]		=     141365009,
			[I_LCOEF_WSEQIOPS]	=         33716,
			[I_LCOEF_WRANDIOPS]	=         26796,
		पूर्ण,
	पूर्ण,
	[AUTOP_SSD_DFL] = अणु
		.qos				= अणु
			[QOS_RLAT]		=         25000, /* 25ms */
			[QOS_WLAT]		=         25000,
			[QOS_MIN]		= VRATE_MIN_PPM,
			[QOS_MAX]		= VRATE_MAX_PPM,
		पूर्ण,
		.i_lcoefs			= अणु
			[I_LCOEF_RBPS]		=     488636629,
			[I_LCOEF_RSEQIOPS]	=          8932,
			[I_LCOEF_RRANDIOPS]	=          8518,
			[I_LCOEF_WBPS]		=     427891549,
			[I_LCOEF_WSEQIOPS]	=         28755,
			[I_LCOEF_WRANDIOPS]	=         21940,
		पूर्ण,
		.too_fast_vrate_pct		=           500,
	पूर्ण,
	[AUTOP_SSD_FAST] = अणु
		.qos				= अणु
			[QOS_RLAT]		=          5000, /* 5ms */
			[QOS_WLAT]		=          5000,
			[QOS_MIN]		= VRATE_MIN_PPM,
			[QOS_MAX]		= VRATE_MAX_PPM,
		पूर्ण,
		.i_lcoefs			= अणु
			[I_LCOEF_RBPS]		=    3102524156LLU,
			[I_LCOEF_RSEQIOPS]	=        724816,
			[I_LCOEF_RRANDIOPS]	=        778122,
			[I_LCOEF_WBPS]		=    1742780862LLU,
			[I_LCOEF_WSEQIOPS]	=        425702,
			[I_LCOEF_WRANDIOPS]	=	 443193,
		पूर्ण,
		.too_slow_vrate_pct		=            10,
	पूर्ण,
पूर्ण;

/*
 * vrate adjust percentages indexed by ioc->busy_level.  We adjust up on
 * vसमय credit लघुage and करोwn on device saturation.
 */
अटल u32 vrate_adj_pct[] =
	अणु 0, 0, 0, 0,
	  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	  4, 4, 4, 4, 4, 4, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 16 पूर्ण;

अटल काष्ठा blkcg_policy blkcg_policy_iocost;

/* accessors and helpers */
अटल काष्ठा ioc *rqos_to_ioc(काष्ठा rq_qos *rqos)
अणु
	वापस container_of(rqos, काष्ठा ioc, rqos);
पूर्ण

अटल काष्ठा ioc *q_to_ioc(काष्ठा request_queue *q)
अणु
	वापस rqos_to_ioc(rq_qos_id(q, RQ_QOS_COST));
पूर्ण

अटल स्थिर अक्षर *q_name(काष्ठा request_queue *q)
अणु
	अगर (blk_queue_रेजिस्टरed(q))
		वापस kobject_name(q->kobj.parent);
	अन्यथा
		वापस "<unknown>";
पूर्ण

अटल स्थिर अक्षर __maybe_unused *ioc_name(काष्ठा ioc *ioc)
अणु
	वापस q_name(ioc->rqos.q);
पूर्ण

अटल काष्ठा ioc_gq *pd_to_iocg(काष्ठा blkg_policy_data *pd)
अणु
	वापस pd ? container_of(pd, काष्ठा ioc_gq, pd) : शून्य;
पूर्ण

अटल काष्ठा ioc_gq *blkg_to_iocg(काष्ठा blkcg_gq *blkg)
अणु
	वापस pd_to_iocg(blkg_to_pd(blkg, &blkcg_policy_iocost));
पूर्ण

अटल काष्ठा blkcg_gq *iocg_to_blkg(काष्ठा ioc_gq *iocg)
अणु
	वापस pd_to_blkg(&iocg->pd);
पूर्ण

अटल काष्ठा ioc_cgrp *blkcg_to_iocc(काष्ठा blkcg *blkcg)
अणु
	वापस container_of(blkcg_to_cpd(blkcg, &blkcg_policy_iocost),
			    काष्ठा ioc_cgrp, cpd);
पूर्ण

/*
 * Scale @असल_cost to the inverse of @hw_inuse.  The lower the hierarchical
 * weight, the more expensive each IO.  Must round up.
 */
अटल u64 असल_cost_to_cost(u64 असल_cost, u32 hw_inuse)
अणु
	वापस DIV64_U64_ROUND_UP(असल_cost * WEIGHT_ONE, hw_inuse);
पूर्ण

/*
 * The inverse of असल_cost_to_cost().  Must round up.
 */
अटल u64 cost_to_असल_cost(u64 cost, u32 hw_inuse)
अणु
	वापस DIV64_U64_ROUND_UP(cost * hw_inuse, WEIGHT_ONE);
पूर्ण

अटल व्योम iocg_commit_bio(काष्ठा ioc_gq *iocg, काष्ठा bio *bio,
			    u64 असल_cost, u64 cost)
अणु
	काष्ठा iocg_pcpu_stat *gcs;

	bio->bi_iocost_cost = cost;
	atomic64_add(cost, &iocg->vसमय);

	gcs = get_cpu_ptr(iocg->pcpu_stat);
	local64_add(असल_cost, &gcs->असल_vusage);
	put_cpu_ptr(gcs);
पूर्ण

अटल व्योम iocg_lock(काष्ठा ioc_gq *iocg, bool lock_ioc, अचिन्हित दीर्घ *flags)
अणु
	अगर (lock_ioc) अणु
		spin_lock_irqsave(&iocg->ioc->lock, *flags);
		spin_lock(&iocg->रुकोq.lock);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&iocg->रुकोq.lock, *flags);
	पूर्ण
पूर्ण

अटल व्योम iocg_unlock(काष्ठा ioc_gq *iocg, bool unlock_ioc, अचिन्हित दीर्घ *flags)
अणु
	अगर (unlock_ioc) अणु
		spin_unlock(&iocg->रुकोq.lock);
		spin_unlock_irqrestore(&iocg->ioc->lock, *flags);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&iocg->रुकोq.lock, *flags);
	पूर्ण
पूर्ण

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/iocost.h>

अटल व्योम ioc_refresh_margins(काष्ठा ioc *ioc)
अणु
	काष्ठा ioc_margins *margins = &ioc->margins;
	u32 period_us = ioc->period_us;
	u64 vrate = ioc->vसमय_base_rate;

	margins->min = (period_us * MARGIN_MIN_PCT / 100) * vrate;
	margins->low = (period_us * MARGIN_LOW_PCT / 100) * vrate;
	margins->target = (period_us * MARGIN_TARGET_PCT / 100) * vrate;
पूर्ण

/* latency Qos params changed, update period_us and all the dependent params */
अटल व्योम ioc_refresh_period_us(काष्ठा ioc *ioc)
अणु
	u32 ppm, lat, multi, period_us;

	lockdep_निश्चित_held(&ioc->lock);

	/* pick the higher latency target */
	अगर (ioc->params.qos[QOS_RLAT] >= ioc->params.qos[QOS_WLAT]) अणु
		ppm = ioc->params.qos[QOS_RPPM];
		lat = ioc->params.qos[QOS_RLAT];
	पूर्ण अन्यथा अणु
		ppm = ioc->params.qos[QOS_WPPM];
		lat = ioc->params.qos[QOS_WLAT];
	पूर्ण

	/*
	 * We want the period to be दीर्घ enough to contain a healthy number
	 * of IOs जबतक लघु enough क्रम granular control.  Define it as a
	 * multiple of the latency target.  Ideally, the multiplier should
	 * be scaled according to the percentile so that it would nominally
	 * contain a certain number of requests.  Let's be simpler and
	 * scale it linearly so that it's 2x >= pct(90) and 10x at pct(50).
	 */
	अगर (ppm)
		multi = max_t(u32, (MILLION - ppm) / 50000, 2);
	अन्यथा
		multi = 2;
	period_us = multi * lat;
	period_us = clamp_t(u32, period_us, MIN_PERIOD, MAX_PERIOD);

	/* calculate dependent params */
	ioc->period_us = period_us;
	ioc->समयr_slack_ns = भाग64_u64(
		(u64)period_us * NSEC_PER_USEC * TIMER_SLACK_PCT,
		100);
	ioc_refresh_margins(ioc);
पूर्ण

अटल पूर्णांक ioc_स्वतःp_idx(काष्ठा ioc *ioc)
अणु
	पूर्णांक idx = ioc->स्वतःp_idx;
	स्थिर काष्ठा ioc_params *p = &स्वतःp[idx];
	u32 vrate_pct;
	u64 now_ns;

	/* rotational? */
	अगर (!blk_queue_nonrot(ioc->rqos.q))
		वापस AUTOP_HDD;

	/* handle SATA SSDs w/ broken NCQ */
	अगर (blk_queue_depth(ioc->rqos.q) == 1)
		वापस AUTOP_SSD_QD1;

	/* use one of the normal ssd sets */
	अगर (idx < AUTOP_SSD_DFL)
		वापस AUTOP_SSD_DFL;

	/* अगर user is overriding anything, मुख्यtain what was there */
	अगर (ioc->user_qos_params || ioc->user_cost_model)
		वापस idx;

	/* step up/करोwn based on the vrate */
	vrate_pct = भाग64_u64(ioc->vसमय_base_rate * 100, VTIME_PER_USEC);
	now_ns = kसमय_get_ns();

	अगर (p->too_fast_vrate_pct && p->too_fast_vrate_pct <= vrate_pct) अणु
		अगर (!ioc->स्वतःp_too_fast_at)
			ioc->स्वतःp_too_fast_at = now_ns;
		अगर (now_ns - ioc->स्वतःp_too_fast_at >= AUTOP_CYCLE_NSEC)
			वापस idx + 1;
	पूर्ण अन्यथा अणु
		ioc->स्वतःp_too_fast_at = 0;
	पूर्ण

	अगर (p->too_slow_vrate_pct && p->too_slow_vrate_pct >= vrate_pct) अणु
		अगर (!ioc->स्वतःp_too_slow_at)
			ioc->स्वतःp_too_slow_at = now_ns;
		अगर (now_ns - ioc->स्वतःp_too_slow_at >= AUTOP_CYCLE_NSEC)
			वापस idx - 1;
	पूर्ण अन्यथा अणु
		ioc->स्वतःp_too_slow_at = 0;
	पूर्ण

	वापस idx;
पूर्ण

/*
 * Take the followings as input
 *
 *  @bps	maximum sequential throughput
 *  @seqiops	maximum sequential 4k iops
 *  @अक्रमiops	maximum अक्रमom 4k iops
 *
 * and calculate the linear model cost coefficients.
 *
 *  *@page	per-page cost		1s / (@bps / 4096)
 *  *@seqio	base cost of a seq IO	max((1s / @seqiops) - *@page, 0)
 *  @अक्रमiops	base cost of a अक्रम IO	max((1s / @अक्रमiops) - *@page, 0)
 */
अटल व्योम calc_lcoefs(u64 bps, u64 seqiops, u64 अक्रमiops,
			u64 *page, u64 *seqio, u64 *अक्रमio)
अणु
	u64 v;

	*page = *seqio = *अक्रमio = 0;

	अगर (bps)
		*page = DIV64_U64_ROUND_UP(VTIME_PER_SEC,
					   DIV_ROUND_UP_ULL(bps, IOC_PAGE_SIZE));

	अगर (seqiops) अणु
		v = DIV64_U64_ROUND_UP(VTIME_PER_SEC, seqiops);
		अगर (v > *page)
			*seqio = v - *page;
	पूर्ण

	अगर (अक्रमiops) अणु
		v = DIV64_U64_ROUND_UP(VTIME_PER_SEC, अक्रमiops);
		अगर (v > *page)
			*अक्रमio = v - *page;
	पूर्ण
पूर्ण

अटल व्योम ioc_refresh_lcoefs(काष्ठा ioc *ioc)
अणु
	u64 *u = ioc->params.i_lcoefs;
	u64 *c = ioc->params.lcoefs;

	calc_lcoefs(u[I_LCOEF_RBPS], u[I_LCOEF_RSEQIOPS], u[I_LCOEF_RRANDIOPS],
		    &c[LCOEF_RPAGE], &c[LCOEF_RSEQIO], &c[LCOEF_RRANDIO]);
	calc_lcoefs(u[I_LCOEF_WBPS], u[I_LCOEF_WSEQIOPS], u[I_LCOEF_WRANDIOPS],
		    &c[LCOEF_WPAGE], &c[LCOEF_WSEQIO], &c[LCOEF_WRANDIO]);
पूर्ण

अटल bool ioc_refresh_params(काष्ठा ioc *ioc, bool क्रमce)
अणु
	स्थिर काष्ठा ioc_params *p;
	पूर्णांक idx;

	lockdep_निश्चित_held(&ioc->lock);

	idx = ioc_स्वतःp_idx(ioc);
	p = &स्वतःp[idx];

	अगर (idx == ioc->स्वतःp_idx && !क्रमce)
		वापस false;

	अगर (idx != ioc->स्वतःp_idx)
		atomic64_set(&ioc->vसमय_rate, VTIME_PER_USEC);

	ioc->स्वतःp_idx = idx;
	ioc->स्वतःp_too_fast_at = 0;
	ioc->स्वतःp_too_slow_at = 0;

	अगर (!ioc->user_qos_params)
		स_नकल(ioc->params.qos, p->qos, माप(p->qos));
	अगर (!ioc->user_cost_model)
		स_नकल(ioc->params.i_lcoefs, p->i_lcoefs, माप(p->i_lcoefs));

	ioc_refresh_period_us(ioc);
	ioc_refresh_lcoefs(ioc);

	ioc->vrate_min = DIV64_U64_ROUND_UP((u64)ioc->params.qos[QOS_MIN] *
					    VTIME_PER_USEC, MILLION);
	ioc->vrate_max = भाग64_u64((u64)ioc->params.qos[QOS_MAX] *
				   VTIME_PER_USEC, MILLION);

	वापस true;
पूर्ण

/*
 * When an iocg accumulates too much vसमय or माला_लो deactivated, we throw away
 * some vसमय, which lowers the overall device utilization. As the exact amount
 * which is being thrown away is known, we can compensate by accelerating the
 * vrate accordingly so that the extra vसमय generated in the current period
 * matches what got lost.
 */
अटल व्योम ioc_refresh_vrate(काष्ठा ioc *ioc, काष्ठा ioc_now *now)
अणु
	s64 pleft = ioc->period_at + ioc->period_us - now->now;
	s64 vperiod = ioc->period_us * ioc->vसमय_base_rate;
	s64 vcomp, vcomp_min, vcomp_max;

	lockdep_निश्चित_held(&ioc->lock);

	/* we need some समय left in this period */
	अगर (pleft <= 0)
		जाओ करोne;

	/*
	 * Calculate how much vrate should be adjusted to offset the error.
	 * Limit the amount of adjusपंचांगent and deduct the adjusted amount from
	 * the error.
	 */
	vcomp = -भाग64_s64(ioc->vसमय_err, pleft);
	vcomp_min = -(ioc->vसमय_base_rate >> 1);
	vcomp_max = ioc->vसमय_base_rate;
	vcomp = clamp(vcomp, vcomp_min, vcomp_max);

	ioc->vसमय_err += vcomp * pleft;

	atomic64_set(&ioc->vसमय_rate, ioc->vसमय_base_rate + vcomp);
करोne:
	/* bound how much error can accumulate */
	ioc->vसमय_err = clamp(ioc->vसमय_err, -vperiod, vperiod);
पूर्ण

अटल व्योम ioc_adjust_base_vrate(काष्ठा ioc *ioc, u32 rq_रुको_pct,
				  पूर्णांक nr_lagging, पूर्णांक nr_लघुages,
				  पूर्णांक prev_busy_level, u32 *missed_ppm)
अणु
	u64 vrate = ioc->vसमय_base_rate;
	u64 vrate_min = ioc->vrate_min, vrate_max = ioc->vrate_max;

	अगर (!ioc->busy_level || (ioc->busy_level < 0 && nr_lagging)) अणु
		अगर (ioc->busy_level != prev_busy_level || nr_lagging)
			trace_iocost_ioc_vrate_adj(ioc, atomic64_पढ़ो(&ioc->vसमय_rate),
						   missed_ppm, rq_रुको_pct,
						   nr_lagging, nr_लघुages);

		वापस;
	पूर्ण

	/*
	 * If vrate is out of bounds, apply clamp gradually as the
	 * bounds can change abruptly.  Otherwise, apply busy_level
	 * based adjusपंचांगent.
	 */
	अगर (vrate < vrate_min) अणु
		vrate = भाग64_u64(vrate * (100 + VRATE_CLAMP_ADJ_PCT), 100);
		vrate = min(vrate, vrate_min);
	पूर्ण अन्यथा अगर (vrate > vrate_max) अणु
		vrate = भाग64_u64(vrate * (100 - VRATE_CLAMP_ADJ_PCT), 100);
		vrate = max(vrate, vrate_max);
	पूर्ण अन्यथा अणु
		पूर्णांक idx = min_t(पूर्णांक, असल(ioc->busy_level),
				ARRAY_SIZE(vrate_adj_pct) - 1);
		u32 adj_pct = vrate_adj_pct[idx];

		अगर (ioc->busy_level > 0)
			adj_pct = 100 - adj_pct;
		अन्यथा
			adj_pct = 100 + adj_pct;

		vrate = clamp(DIV64_U64_ROUND_UP(vrate * adj_pct, 100),
			      vrate_min, vrate_max);
	पूर्ण

	trace_iocost_ioc_vrate_adj(ioc, vrate, missed_ppm, rq_रुको_pct,
				   nr_lagging, nr_लघुages);

	ioc->vसमय_base_rate = vrate;
	ioc_refresh_margins(ioc);
पूर्ण

/* take a snapshot of the current [v]समय and vrate */
अटल व्योम ioc_now(काष्ठा ioc *ioc, काष्ठा ioc_now *now)
अणु
	अचिन्हित seq;

	now->now_ns = kसमय_get();
	now->now = kसमय_प्रकारo_us(now->now_ns);
	now->vrate = atomic64_पढ़ो(&ioc->vसमय_rate);

	/*
	 * The current vसमय is
	 *
	 *   vसमय at period start + (wallघड़ी समय since the start) * vrate
	 *
	 * As a consistent snapshot of `period_at_vसमय` and `period_at` is
	 * needed, they're seqcount रक्षित.
	 */
	करो अणु
		seq = पढ़ो_seqcount_begin(&ioc->period_seqcount);
		now->vnow = ioc->period_at_vसमय +
			(now->now - ioc->period_at) * now->vrate;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&ioc->period_seqcount, seq));
पूर्ण

अटल व्योम ioc_start_period(काष्ठा ioc *ioc, काष्ठा ioc_now *now)
अणु
	WARN_ON_ONCE(ioc->running != IOC_RUNNING);

	ग_लिखो_seqcount_begin(&ioc->period_seqcount);
	ioc->period_at = now->now;
	ioc->period_at_vसमय = now->vnow;
	ग_लिखो_seqcount_end(&ioc->period_seqcount);

	ioc->समयr.expires = jअगरfies + usecs_to_jअगरfies(ioc->period_us);
	add_समयr(&ioc->समयr);
पूर्ण

/*
 * Update @iocg's `active` and `inuse` to @active and @inuse, update level
 * weight sums and propagate upwards accordingly. If @save, the current margin
 * is saved to be used as reference क्रम later inuse in-period adjusपंचांगents.
 */
अटल व्योम __propagate_weights(काष्ठा ioc_gq *iocg, u32 active, u32 inuse,
				bool save, काष्ठा ioc_now *now)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	पूर्णांक lvl;

	lockdep_निश्चित_held(&ioc->lock);

	/*
	 * For an active leaf node, its inuse shouldn't be zero or exceed
	 * @active. An active पूर्णांकernal node's inuse is solely determined by the
	 * inuse to active ratio of its children regardless of @inuse.
	 */
	अगर (list_empty(&iocg->active_list) && iocg->child_active_sum) अणु
		inuse = DIV64_U64_ROUND_UP(active * iocg->child_inuse_sum,
					   iocg->child_active_sum);
	पूर्ण अन्यथा अणु
		inuse = clamp_t(u32, inuse, 1, active);
	पूर्ण

	iocg->last_inuse = iocg->inuse;
	अगर (save)
		iocg->saved_margin = now->vnow - atomic64_पढ़ो(&iocg->vसमय);

	अगर (active == iocg->active && inuse == iocg->inuse)
		वापस;

	क्रम (lvl = iocg->level - 1; lvl >= 0; lvl--) अणु
		काष्ठा ioc_gq *parent = iocg->ancestors[lvl];
		काष्ठा ioc_gq *child = iocg->ancestors[lvl + 1];
		u32 parent_active = 0, parent_inuse = 0;

		/* update the level sums */
		parent->child_active_sum += (s32)(active - child->active);
		parent->child_inuse_sum += (s32)(inuse - child->inuse);
		/* apply the updates */
		child->active = active;
		child->inuse = inuse;

		/*
		 * The delta between inuse and active sums indicates that
		 * much of weight is being given away.  Parent's inuse
		 * and active should reflect the ratio.
		 */
		अगर (parent->child_active_sum) अणु
			parent_active = parent->weight;
			parent_inuse = DIV64_U64_ROUND_UP(
				parent_active * parent->child_inuse_sum,
				parent->child_active_sum);
		पूर्ण

		/* करो we need to keep walking up? */
		अगर (parent_active == parent->active &&
		    parent_inuse == parent->inuse)
			अवरोध;

		active = parent_active;
		inuse = parent_inuse;
	पूर्ण

	ioc->weights_updated = true;
पूर्ण

अटल व्योम commit_weights(काष्ठा ioc *ioc)
अणु
	lockdep_निश्चित_held(&ioc->lock);

	अगर (ioc->weights_updated) अणु
		/* paired with rmb in current_hweight(), see there */
		smp_wmb();
		atomic_inc(&ioc->hweight_gen);
		ioc->weights_updated = false;
	पूर्ण
पूर्ण

अटल व्योम propagate_weights(काष्ठा ioc_gq *iocg, u32 active, u32 inuse,
			      bool save, काष्ठा ioc_now *now)
अणु
	__propagate_weights(iocg, active, inuse, save, now);
	commit_weights(iocg->ioc);
पूर्ण

अटल व्योम current_hweight(काष्ठा ioc_gq *iocg, u32 *hw_activep, u32 *hw_inusep)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	पूर्णांक lvl;
	u32 hwa, hwi;
	पूर्णांक ioc_gen;

	/* hot path - अगर uptodate, use cached */
	ioc_gen = atomic_पढ़ो(&ioc->hweight_gen);
	अगर (ioc_gen == iocg->hweight_gen)
		जाओ out;

	/*
	 * Paired with wmb in commit_weights(). If we saw the updated
	 * hweight_gen, all the weight updates from __propagate_weights() are
	 * visible too.
	 *
	 * We can race with weight updates during calculation and get it
	 * wrong.  However, hweight_gen would have changed and a future
	 * पढ़ोer will recalculate and we're guaranteed to discard the
	 * wrong result soon.
	 */
	smp_rmb();

	hwa = hwi = WEIGHT_ONE;
	क्रम (lvl = 0; lvl <= iocg->level - 1; lvl++) अणु
		काष्ठा ioc_gq *parent = iocg->ancestors[lvl];
		काष्ठा ioc_gq *child = iocg->ancestors[lvl + 1];
		u64 active_sum = READ_ONCE(parent->child_active_sum);
		u64 inuse_sum = READ_ONCE(parent->child_inuse_sum);
		u32 active = READ_ONCE(child->active);
		u32 inuse = READ_ONCE(child->inuse);

		/* we can race with deactivations and either may पढ़ो as zero */
		अगर (!active_sum || !inuse_sum)
			जारी;

		active_sum = max_t(u64, active, active_sum);
		hwa = भाग64_u64((u64)hwa * active, active_sum);

		inuse_sum = max_t(u64, inuse, inuse_sum);
		hwi = भाग64_u64((u64)hwi * inuse, inuse_sum);
	पूर्ण

	iocg->hweight_active = max_t(u32, hwa, 1);
	iocg->hweight_inuse = max_t(u32, hwi, 1);
	iocg->hweight_gen = ioc_gen;
out:
	अगर (hw_activep)
		*hw_activep = iocg->hweight_active;
	अगर (hw_inusep)
		*hw_inusep = iocg->hweight_inuse;
पूर्ण

/*
 * Calculate the hweight_inuse @iocg would get with max @inuse assuming all the
 * other weights stay unchanged.
 */
अटल u32 current_hweight_max(काष्ठा ioc_gq *iocg)
अणु
	u32 hwm = WEIGHT_ONE;
	u32 inuse = iocg->active;
	u64 child_inuse_sum;
	पूर्णांक lvl;

	lockdep_निश्चित_held(&iocg->ioc->lock);

	क्रम (lvl = iocg->level - 1; lvl >= 0; lvl--) अणु
		काष्ठा ioc_gq *parent = iocg->ancestors[lvl];
		काष्ठा ioc_gq *child = iocg->ancestors[lvl + 1];

		child_inuse_sum = parent->child_inuse_sum + inuse - child->inuse;
		hwm = भाग64_u64((u64)hwm * inuse, child_inuse_sum);
		inuse = DIV64_U64_ROUND_UP(parent->active * child_inuse_sum,
					   parent->child_active_sum);
	पूर्ण

	वापस max_t(u32, hwm, 1);
पूर्ण

अटल व्योम weight_updated(काष्ठा ioc_gq *iocg, काष्ठा ioc_now *now)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	काष्ठा blkcg_gq *blkg = iocg_to_blkg(iocg);
	काष्ठा ioc_cgrp *iocc = blkcg_to_iocc(blkg->blkcg);
	u32 weight;

	lockdep_निश्चित_held(&ioc->lock);

	weight = iocg->cfg_weight ?: iocc->dfl_weight;
	अगर (weight != iocg->weight && iocg->active)
		propagate_weights(iocg, weight, iocg->inuse, true, now);
	iocg->weight = weight;
पूर्ण

अटल bool iocg_activate(काष्ठा ioc_gq *iocg, काष्ठा ioc_now *now)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	u64 last_period, cur_period;
	u64 vसमय, vtarget;
	पूर्णांक i;

	/*
	 * If seem to be alपढ़ोy active, just update the stamp to tell the
	 * समयr that we're still active.  We don't mind occassional races.
	 */
	अगर (!list_empty(&iocg->active_list)) अणु
		ioc_now(ioc, now);
		cur_period = atomic64_पढ़ो(&ioc->cur_period);
		अगर (atomic64_पढ़ो(&iocg->active_period) != cur_period)
			atomic64_set(&iocg->active_period, cur_period);
		वापस true;
	पूर्ण

	/* racy check on पूर्णांकernal node IOs, treat as root level IOs */
	अगर (iocg->child_active_sum)
		वापस false;

	spin_lock_irq(&ioc->lock);

	ioc_now(ioc, now);

	/* update period */
	cur_period = atomic64_पढ़ो(&ioc->cur_period);
	last_period = atomic64_पढ़ो(&iocg->active_period);
	atomic64_set(&iocg->active_period, cur_period);

	/* alपढ़ोy activated or अवरोधing leaf-only स्थिरraपूर्णांक? */
	अगर (!list_empty(&iocg->active_list))
		जाओ succeed_unlock;
	क्रम (i = iocg->level - 1; i > 0; i--)
		अगर (!list_empty(&iocg->ancestors[i]->active_list))
			जाओ fail_unlock;

	अगर (iocg->child_active_sum)
		जाओ fail_unlock;

	/*
	 * Always start with the target budget. On deactivation, we throw away
	 * anything above it.
	 */
	vtarget = now->vnow - ioc->margins.target;
	vसमय = atomic64_पढ़ो(&iocg->vसमय);

	atomic64_add(vtarget - vसमय, &iocg->vसमय);
	atomic64_add(vtarget - vसमय, &iocg->करोne_vसमय);
	vसमय = vtarget;

	/*
	 * Activate, propagate weight and start period समयr अगर not
	 * running.  Reset hweight_gen to aव्योम accidental match from
	 * wrapping.
	 */
	iocg->hweight_gen = atomic_पढ़ो(&ioc->hweight_gen) - 1;
	list_add(&iocg->active_list, &ioc->active_iocgs);

	propagate_weights(iocg, iocg->weight,
			  iocg->last_inuse ?: iocg->weight, true, now);

	TRACE_IOCG_PATH(iocg_activate, iocg, now,
			last_period, cur_period, vसमय);

	iocg->activated_at = now->now;

	अगर (ioc->running == IOC_IDLE) अणु
		ioc->running = IOC_RUNNING;
		ioc->dfgv_period_at = now->now;
		ioc->dfgv_period_rem = 0;
		ioc_start_period(ioc, now);
	पूर्ण

succeed_unlock:
	spin_unlock_irq(&ioc->lock);
	वापस true;

fail_unlock:
	spin_unlock_irq(&ioc->lock);
	वापस false;
पूर्ण

अटल bool iocg_kick_delay(काष्ठा ioc_gq *iocg, काष्ठा ioc_now *now)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	काष्ठा blkcg_gq *blkg = iocg_to_blkg(iocg);
	u64 tdelta, delay, new_delay;
	s64 vover, vover_pct;
	u32 hwa;

	lockdep_निश्चित_held(&iocg->रुकोq.lock);

	/* calculate the current delay in effect - 1/2 every second */
	tdelta = now->now - iocg->delay_at;
	अगर (iocg->delay)
		delay = iocg->delay >> भाग64_u64(tdelta, USEC_PER_SEC);
	अन्यथा
		delay = 0;

	/* calculate the new delay from the debt amount */
	current_hweight(iocg, &hwa, शून्य);
	vover = atomic64_पढ़ो(&iocg->vसमय) +
		असल_cost_to_cost(iocg->असल_vdebt, hwa) - now->vnow;
	vover_pct = भाग64_s64(100 * vover,
			      ioc->period_us * ioc->vसमय_base_rate);

	अगर (vover_pct <= MIN_DELAY_THR_PCT)
		new_delay = 0;
	अन्यथा अगर (vover_pct >= MAX_DELAY_THR_PCT)
		new_delay = MAX_DELAY;
	अन्यथा
		new_delay = MIN_DELAY +
			भाग_u64((MAX_DELAY - MIN_DELAY) *
				(vover_pct - MIN_DELAY_THR_PCT),
				MAX_DELAY_THR_PCT - MIN_DELAY_THR_PCT);

	/* pick the higher one and apply */
	अगर (new_delay > delay) अणु
		iocg->delay = new_delay;
		iocg->delay_at = now->now;
		delay = new_delay;
	पूर्ण

	अगर (delay >= MIN_DELAY) अणु
		अगर (!iocg->indelay_since)
			iocg->indelay_since = now->now;
		blkcg_set_delay(blkg, delay * NSEC_PER_USEC);
		वापस true;
	पूर्ण अन्यथा अणु
		अगर (iocg->indelay_since) अणु
			iocg->local_stat.indelay_us += now->now - iocg->indelay_since;
			iocg->indelay_since = 0;
		पूर्ण
		iocg->delay = 0;
		blkcg_clear_delay(blkg);
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम iocg_incur_debt(काष्ठा ioc_gq *iocg, u64 असल_cost,
			    काष्ठा ioc_now *now)
अणु
	काष्ठा iocg_pcpu_stat *gcs;

	lockdep_निश्चित_held(&iocg->ioc->lock);
	lockdep_निश्चित_held(&iocg->रुकोq.lock);
	WARN_ON_ONCE(list_empty(&iocg->active_list));

	/*
	 * Once in debt, debt handling owns inuse. @iocg stays at the minimum
	 * inuse करोnating all of it share to others until its debt is paid off.
	 */
	अगर (!iocg->असल_vdebt && असल_cost) अणु
		iocg->indebt_since = now->now;
		propagate_weights(iocg, iocg->active, 0, false, now);
	पूर्ण

	iocg->असल_vdebt += असल_cost;

	gcs = get_cpu_ptr(iocg->pcpu_stat);
	local64_add(असल_cost, &gcs->असल_vusage);
	put_cpu_ptr(gcs);
पूर्ण

अटल व्योम iocg_pay_debt(काष्ठा ioc_gq *iocg, u64 असल_vpay,
			  काष्ठा ioc_now *now)
अणु
	lockdep_निश्चित_held(&iocg->ioc->lock);
	lockdep_निश्चित_held(&iocg->रुकोq.lock);

	/* make sure that nobody messed with @iocg */
	WARN_ON_ONCE(list_empty(&iocg->active_list));
	WARN_ON_ONCE(iocg->inuse > 1);

	iocg->असल_vdebt -= min(असल_vpay, iocg->असल_vdebt);

	/* अगर debt is paid in full, restore inuse */
	अगर (!iocg->असल_vdebt) अणु
		iocg->local_stat.indebt_us += now->now - iocg->indebt_since;
		iocg->indebt_since = 0;

		propagate_weights(iocg, iocg->active, iocg->last_inuse,
				  false, now);
	पूर्ण
पूर्ण

अटल पूर्णांक iocg_wake_fn(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode,
			पूर्णांक flags, व्योम *key)
अणु
	काष्ठा iocg_रुको *रुको = container_of(wq_entry, काष्ठा iocg_रुको, रुको);
	काष्ठा iocg_wake_ctx *ctx = (काष्ठा iocg_wake_ctx *)key;
	u64 cost = असल_cost_to_cost(रुको->असल_cost, ctx->hw_inuse);

	ctx->vbudget -= cost;

	अगर (ctx->vbudget < 0)
		वापस -1;

	iocg_commit_bio(ctx->iocg, रुको->bio, रुको->असल_cost, cost);

	/*
	 * स्वतःहटाओ_wake_function() हटाओs the रुको entry only when it
	 * actually changed the task state.  We want the रुको always
	 * हटाओd.  Remove explicitly and use शेष_wake_function().
	 */
	list_del_init(&wq_entry->entry);
	रुको->committed = true;

	शेष_wake_function(wq_entry, mode, flags, key);
	वापस 0;
पूर्ण

/*
 * Calculate the accumulated budget, pay debt अगर @pay_debt and wake up रुकोers
 * accordingly. When @pay_debt is %true, the caller must be holding ioc->lock in
 * addition to iocg->रुकोq.lock.
 */
अटल व्योम iocg_kick_रुकोq(काष्ठा ioc_gq *iocg, bool pay_debt,
			    काष्ठा ioc_now *now)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	काष्ठा iocg_wake_ctx ctx = अणु .iocg = iocg पूर्ण;
	u64 vलघुage, expires, oexpires;
	s64 vbudget;
	u32 hwa;

	lockdep_निश्चित_held(&iocg->रुकोq.lock);

	current_hweight(iocg, &hwa, शून्य);
	vbudget = now->vnow - atomic64_पढ़ो(&iocg->vसमय);

	/* pay off debt */
	अगर (pay_debt && iocg->असल_vdebt && vbudget > 0) अणु
		u64 असल_vbudget = cost_to_असल_cost(vbudget, hwa);
		u64 असल_vpay = min_t(u64, असल_vbudget, iocg->असल_vdebt);
		u64 vpay = असल_cost_to_cost(असल_vpay, hwa);

		lockdep_निश्चित_held(&ioc->lock);

		atomic64_add(vpay, &iocg->vसमय);
		atomic64_add(vpay, &iocg->करोne_vसमय);
		iocg_pay_debt(iocg, असल_vpay, now);
		vbudget -= vpay;
	पूर्ण

	अगर (iocg->असल_vdebt || iocg->delay)
		iocg_kick_delay(iocg, now);

	/*
	 * Debt can still be outstanding अगर we haven't paid all yet or the
	 * caller raced and called without @pay_debt. Shouldn't wake up रुकोers
	 * under debt. Make sure @vbudget reflects the outstanding amount and is
	 * not positive.
	 */
	अगर (iocg->असल_vdebt) अणु
		s64 vdebt = असल_cost_to_cost(iocg->असल_vdebt, hwa);
		vbudget = min_t(s64, 0, vbudget - vdebt);
	पूर्ण

	/*
	 * Wake up the ones which are due and see how much vसमय we'll need क्रम
	 * the next one. As paying off debt restores hw_inuse, it must be पढ़ो
	 * after the above debt payment.
	 */
	ctx.vbudget = vbudget;
	current_hweight(iocg, शून्य, &ctx.hw_inuse);

	__wake_up_locked_key(&iocg->रुकोq, TASK_NORMAL, &ctx);

	अगर (!रुकोqueue_active(&iocg->रुकोq)) अणु
		अगर (iocg->रुको_since) अणु
			iocg->local_stat.रुको_us += now->now - iocg->रुको_since;
			iocg->रुको_since = 0;
		पूर्ण
		वापस;
	पूर्ण

	अगर (!iocg->रुको_since)
		iocg->रुको_since = now->now;

	अगर (WARN_ON_ONCE(ctx.vbudget >= 0))
		वापस;

	/* determine next wakeup, add a समयr margin to guarantee chunking */
	vलघुage = -ctx.vbudget;
	expires = now->now_ns +
		DIV64_U64_ROUND_UP(vलघुage, ioc->vसमय_base_rate) *
		NSEC_PER_USEC;
	expires += ioc->समयr_slack_ns;

	/* अगर alपढ़ोy active and बंद enough, करोn't bother */
	oexpires = kसमय_प्रकारo_ns(hrसमयr_get_softexpires(&iocg->रुकोq_समयr));
	अगर (hrसमयr_is_queued(&iocg->रुकोq_समयr) &&
	    असल(oexpires - expires) <= ioc->समयr_slack_ns)
		वापस;

	hrसमयr_start_range_ns(&iocg->रुकोq_समयr, ns_to_kसमय(expires),
			       ioc->समयr_slack_ns, HRTIMER_MODE_ABS);
पूर्ण

अटल क्रमागत hrसमयr_restart iocg_रुकोq_समयr_fn(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा ioc_gq *iocg = container_of(समयr, काष्ठा ioc_gq, रुकोq_समयr);
	bool pay_debt = READ_ONCE(iocg->असल_vdebt);
	काष्ठा ioc_now now;
	अचिन्हित दीर्घ flags;

	ioc_now(iocg->ioc, &now);

	iocg_lock(iocg, pay_debt, &flags);
	iocg_kick_रुकोq(iocg, pay_debt, &now);
	iocg_unlock(iocg, pay_debt, &flags);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम ioc_lat_stat(काष्ठा ioc *ioc, u32 *missed_ppm_ar, u32 *rq_रुको_pct_p)
अणु
	u32 nr_met[2] = अणु पूर्ण;
	u32 nr_missed[2] = अणु पूर्ण;
	u64 rq_रुको_ns = 0;
	पूर्णांक cpu, rw;

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा ioc_pcpu_stat *stat = per_cpu_ptr(ioc->pcpu_stat, cpu);
		u64 this_rq_रुको_ns;

		क्रम (rw = READ; rw <= WRITE; rw++) अणु
			u32 this_met = local_पढ़ो(&stat->missed[rw].nr_met);
			u32 this_missed = local_पढ़ो(&stat->missed[rw].nr_missed);

			nr_met[rw] += this_met - stat->missed[rw].last_met;
			nr_missed[rw] += this_missed - stat->missed[rw].last_missed;
			stat->missed[rw].last_met = this_met;
			stat->missed[rw].last_missed = this_missed;
		पूर्ण

		this_rq_रुको_ns = local64_पढ़ो(&stat->rq_रुको_ns);
		rq_रुको_ns += this_rq_रुको_ns - stat->last_rq_रुको_ns;
		stat->last_rq_रुको_ns = this_rq_रुको_ns;
	पूर्ण

	क्रम (rw = READ; rw <= WRITE; rw++) अणु
		अगर (nr_met[rw] + nr_missed[rw])
			missed_ppm_ar[rw] =
				DIV64_U64_ROUND_UP((u64)nr_missed[rw] * MILLION,
						   nr_met[rw] + nr_missed[rw]);
		अन्यथा
			missed_ppm_ar[rw] = 0;
	पूर्ण

	*rq_रुको_pct_p = भाग64_u64(rq_रुको_ns * 100,
				   ioc->period_us * NSEC_PER_USEC);
पूर्ण

/* was iocg idle this period? */
अटल bool iocg_is_idle(काष्ठा ioc_gq *iocg)
अणु
	काष्ठा ioc *ioc = iocg->ioc;

	/* did something get issued this period? */
	अगर (atomic64_पढ़ो(&iocg->active_period) ==
	    atomic64_पढ़ो(&ioc->cur_period))
		वापस false;

	/* is something in flight? */
	अगर (atomic64_पढ़ो(&iocg->करोne_vसमय) != atomic64_पढ़ो(&iocg->vसमय))
		वापस false;

	वापस true;
पूर्ण

/*
 * Call this function on the target leaf @iocg's to build pre-order traversal
 * list of all the ancestors in @inner_walk. The inner nodes are linked through
 * ->walk_list and the caller is responsible क्रम dissolving the list after use.
 */
अटल व्योम iocg_build_inner_walk(काष्ठा ioc_gq *iocg,
				  काष्ठा list_head *inner_walk)
अणु
	पूर्णांक lvl;

	WARN_ON_ONCE(!list_empty(&iocg->walk_list));

	/* find the first ancestor which hasn't been visited yet */
	क्रम (lvl = iocg->level - 1; lvl >= 0; lvl--) अणु
		अगर (!list_empty(&iocg->ancestors[lvl]->walk_list))
			अवरोध;
	पूर्ण

	/* walk करोwn and visit the inner nodes to get pre-order traversal */
	जबतक (++lvl <= iocg->level - 1) अणु
		काष्ठा ioc_gq *inner = iocg->ancestors[lvl];

		/* record traversal order */
		list_add_tail(&inner->walk_list, inner_walk);
	पूर्ण
पूर्ण

/* collect per-cpu counters and propagate the deltas to the parent */
अटल व्योम iocg_flush_stat_one(काष्ठा ioc_gq *iocg, काष्ठा ioc_now *now)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	काष्ठा iocg_stat new_stat;
	u64 असल_vusage = 0;
	u64 vusage_delta;
	पूर्णांक cpu;

	lockdep_निश्चित_held(&iocg->ioc->lock);

	/* collect per-cpu counters */
	क्रम_each_possible_cpu(cpu) अणु
		असल_vusage += local64_पढ़ो(
				per_cpu_ptr(&iocg->pcpu_stat->असल_vusage, cpu));
	पूर्ण
	vusage_delta = असल_vusage - iocg->last_stat_असल_vusage;
	iocg->last_stat_असल_vusage = असल_vusage;

	iocg->usage_delta_us = भाग64_u64(vusage_delta, ioc->vसमय_base_rate);
	iocg->local_stat.usage_us += iocg->usage_delta_us;

	/* propagate upwards */
	new_stat.usage_us =
		iocg->local_stat.usage_us + iocg->desc_stat.usage_us;
	new_stat.रुको_us =
		iocg->local_stat.रुको_us + iocg->desc_stat.रुको_us;
	new_stat.indebt_us =
		iocg->local_stat.indebt_us + iocg->desc_stat.indebt_us;
	new_stat.indelay_us =
		iocg->local_stat.indelay_us + iocg->desc_stat.indelay_us;

	/* propagate the deltas to the parent */
	अगर (iocg->level > 0) अणु
		काष्ठा iocg_stat *parent_stat =
			&iocg->ancestors[iocg->level - 1]->desc_stat;

		parent_stat->usage_us +=
			new_stat.usage_us - iocg->last_stat.usage_us;
		parent_stat->रुको_us +=
			new_stat.रुको_us - iocg->last_stat.रुको_us;
		parent_stat->indebt_us +=
			new_stat.indebt_us - iocg->last_stat.indebt_us;
		parent_stat->indelay_us +=
			new_stat.indelay_us - iocg->last_stat.indelay_us;
	पूर्ण

	iocg->last_stat = new_stat;
पूर्ण

/* get stat counters पढ़ोy क्रम पढ़ोing on all active iocgs */
अटल व्योम iocg_flush_stat(काष्ठा list_head *target_iocgs, काष्ठा ioc_now *now)
अणु
	LIST_HEAD(inner_walk);
	काष्ठा ioc_gq *iocg, *tiocg;

	/* flush leaves and build inner node walk list */
	list_क्रम_each_entry(iocg, target_iocgs, active_list) अणु
		iocg_flush_stat_one(iocg, now);
		iocg_build_inner_walk(iocg, &inner_walk);
	पूर्ण

	/* keep flushing upwards by walking the inner list backwards */
	list_क्रम_each_entry_safe_reverse(iocg, tiocg, &inner_walk, walk_list) अणु
		iocg_flush_stat_one(iocg, now);
		list_del_init(&iocg->walk_list);
	पूर्ण
पूर्ण

/*
 * Determine what @iocg's hweight_inuse should be after करोnating unused
 * capacity. @hwm is the upper bound and used to संकेत no करोnation. This
 * function also throws away @iocg's excess budget.
 */
अटल u32 hweight_after_करोnation(काष्ठा ioc_gq *iocg, u32 old_hwi, u32 hwm,
				  u32 usage, काष्ठा ioc_now *now)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	u64 vसमय = atomic64_पढ़ो(&iocg->vसमय);
	s64 excess, delta, target, new_hwi;

	/* debt handling owns inuse क्रम debtors */
	अगर (iocg->असल_vdebt)
		वापस 1;

	/* see whether minimum margin requirement is met */
	अगर (रुकोqueue_active(&iocg->रुकोq) ||
	    समय_after64(vसमय, now->vnow - ioc->margins.min))
		वापस hwm;

	/* throw away excess above target */
	excess = now->vnow - vसमय - ioc->margins.target;
	अगर (excess > 0) अणु
		atomic64_add(excess, &iocg->vसमय);
		atomic64_add(excess, &iocg->करोne_vसमय);
		vसमय += excess;
		ioc->vसमय_err -= भाग64_u64(excess * old_hwi, WEIGHT_ONE);
	पूर्ण

	/*
	 * Let's say the distance between iocg's and device's vबार as a
	 * fraction of period duration is delta. Assuming that the iocg will
	 * consume the usage determined above, we want to determine new_hwi so
	 * that delta equals MARGIN_TARGET at the end of the next period.
	 *
	 * We need to execute usage worth of IOs जबतक spending the sum of the
	 * new budget (1 - MARGIN_TARGET) and the leftover from the last period
	 * (delta):
	 *
	 *   usage = (1 - MARGIN_TARGET + delta) * new_hwi
	 *
	 * Thereक्रमe, the new_hwi is:
	 *
	 *   new_hwi = usage / (1 - MARGIN_TARGET + delta)
	 */
	delta = भाग64_s64(WEIGHT_ONE * (now->vnow - vसमय),
			  now->vnow - ioc->period_at_vसमय);
	target = WEIGHT_ONE * MARGIN_TARGET_PCT / 100;
	new_hwi = भाग64_s64(WEIGHT_ONE * usage, WEIGHT_ONE - target + delta);

	वापस clamp_t(s64, new_hwi, 1, hwm);
पूर्ण

/*
 * For work-conservation, an iocg which isn't using all of its share should
 * करोnate the leftover to other iocgs. There are two ways to achieve this - 1.
 * bumping up vrate accordingly 2. lowering the करोnating iocg's inuse weight.
 *
 * #1 is mathematically simpler but has the drawback of requiring synchronous
 * global hweight_inuse updates when idle iocg's get activated or inuse weights
 * change due to करोnation snapbacks as it has the possibility of grossly
 * overshooting what's allowed by the model and vrate.
 *
 * #2 is inherently safe with local operations. The करोnating iocg can easily
 * snap back to higher weights when needed without worrying about impacts on
 * other nodes as the impacts will be inherently correct. This also makes idle
 * iocg activations safe. The only effect activations have is decreasing
 * hweight_inuse of others, the right solution to which is क्रम those iocgs to
 * snap back to higher weights.
 *
 * So, we go with #2. The challenge is calculating how each करोnating iocg's
 * inuse should be adjusted to achieve the target करोnation amounts. This is करोne
 * using Andy's method described in the following pdf.
 *
 *   https://drive.google.com/file/d/1PsJwxPFtjUnwOY1QJ5AeICCcsL7BM3bo
 *
 * Given the weights and target after-करोnation hweight_inuse values, Andy's
 * method determines how the proportional distribution should look like at each
 * sibling level to मुख्यtain the relative relationship between all non-करोnating
 * pairs. To roughly summarize, it भागides the tree पूर्णांकo करोnating and
 * non-करोnating parts, calculates global करोnation rate which is used to
 * determine the target hweight_inuse क्रम each node, and then derives per-level
 * proportions.
 *
 * The following pdf shows that global distribution calculated this way can be
 * achieved by scaling inuse weights of करोnating leaves and propagating the
 * adjusपंचांगents upwards proportionally.
 *
 *   https://drive.google.com/file/d/1vONz1-fzVO7oY5DXXsLjSxEtYYQbOvsE
 *
 * Combining the above two, we can determine how each leaf iocg's inuse should
 * be adjusted to achieve the target करोnation.
 *
 *   https://drive.google.com/file/d/1WcrltBOSPN0qXVdBgnKm4mdp9FhuEFQN
 *
 * The अंतरभूत comments use symbols from the last pdf.
 *
 *   b is the sum of the असलolute budमाला_लो in the subtree. 1 क्रम the root node.
 *   f is the sum of the असलolute budमाला_लो of non-करोnating nodes in the subtree.
 *   t is the sum of the असलolute budमाला_लो of करोnating nodes in the subtree.
 *   w is the weight of the node. w = w_f + w_t
 *   w_f is the non-करोnating portion of w. w_f = w * f / b
 *   w_b is the करोnating portion of w. w_t = w * t / b
 *   s is the sum of all sibling weights. s = Sum(w) क्रम siblings
 *   s_f and s_t are the non-करोnating and करोnating portions of s.
 *
 * Subscript p denotes the parent's counterpart and ' the adjusted value - e.g.
 * w_pt is the करोnating portion of the parent's weight and w'_pt the same value
 * after adjusपंचांगents. Subscript r denotes the root node's values.
 */
अटल व्योम transfer_surpluses(काष्ठा list_head *surpluses, काष्ठा ioc_now *now)
अणु
	LIST_HEAD(over_hwa);
	LIST_HEAD(inner_walk);
	काष्ठा ioc_gq *iocg, *tiocg, *root_iocg;
	u32 after_sum, over_sum, over_target, gamma;

	/*
	 * It's pretty unlikely but possible क्रम the total sum of
	 * hweight_after_करोnation's to be higher than WEIGHT_ONE, which will
	 * confuse the following calculations. If such condition is detected,
	 * scale करोwn everyone over its full share equally to keep the sum below
	 * WEIGHT_ONE.
	 */
	after_sum = 0;
	over_sum = 0;
	list_क्रम_each_entry(iocg, surpluses, surplus_list) अणु
		u32 hwa;

		current_hweight(iocg, &hwa, शून्य);
		after_sum += iocg->hweight_after_करोnation;

		अगर (iocg->hweight_after_करोnation > hwa) अणु
			over_sum += iocg->hweight_after_करोnation;
			list_add(&iocg->walk_list, &over_hwa);
		पूर्ण
	पूर्ण

	अगर (after_sum >= WEIGHT_ONE) अणु
		/*
		 * The delta should be deducted from the over_sum, calculate
		 * target over_sum value.
		 */
		u32 over_delta = after_sum - (WEIGHT_ONE - 1);
		WARN_ON_ONCE(over_sum <= over_delta);
		over_target = over_sum - over_delta;
	पूर्ण अन्यथा अणु
		over_target = 0;
	पूर्ण

	list_क्रम_each_entry_safe(iocg, tiocg, &over_hwa, walk_list) अणु
		अगर (over_target)
			iocg->hweight_after_करोnation =
				भाग_u64((u64)iocg->hweight_after_करोnation *
					over_target, over_sum);
		list_del_init(&iocg->walk_list);
	पूर्ण

	/*
	 * Build pre-order inner node walk list and prepare क्रम करोnation
	 * adjusपंचांगent calculations.
	 */
	list_क्रम_each_entry(iocg, surpluses, surplus_list) अणु
		iocg_build_inner_walk(iocg, &inner_walk);
	पूर्ण

	root_iocg = list_first_entry(&inner_walk, काष्ठा ioc_gq, walk_list);
	WARN_ON_ONCE(root_iocg->level > 0);

	list_क्रम_each_entry(iocg, &inner_walk, walk_list) अणु
		iocg->child_adjusted_sum = 0;
		iocg->hweight_करोnating = 0;
		iocg->hweight_after_करोnation = 0;
	पूर्ण

	/*
	 * Propagate the करोnating budget (b_t) and after करोnation budget (b'_t)
	 * up the hierarchy.
	 */
	list_क्रम_each_entry(iocg, surpluses, surplus_list) अणु
		काष्ठा ioc_gq *parent = iocg->ancestors[iocg->level - 1];

		parent->hweight_करोnating += iocg->hweight_करोnating;
		parent->hweight_after_करोnation += iocg->hweight_after_करोnation;
	पूर्ण

	list_क्रम_each_entry_reverse(iocg, &inner_walk, walk_list) अणु
		अगर (iocg->level > 0) अणु
			काष्ठा ioc_gq *parent = iocg->ancestors[iocg->level - 1];

			parent->hweight_करोnating += iocg->hweight_करोnating;
			parent->hweight_after_करोnation += iocg->hweight_after_करोnation;
		पूर्ण
	पूर्ण

	/*
	 * Calculate inner hwa's (b) and make sure the करोnation values are
	 * within the accepted ranges as we're करोing low res calculations with
	 * roundups.
	 */
	list_क्रम_each_entry(iocg, &inner_walk, walk_list) अणु
		अगर (iocg->level) अणु
			काष्ठा ioc_gq *parent = iocg->ancestors[iocg->level - 1];

			iocg->hweight_active = DIV64_U64_ROUND_UP(
				(u64)parent->hweight_active * iocg->active,
				parent->child_active_sum);

		पूर्ण

		iocg->hweight_करोnating = min(iocg->hweight_करोnating,
					     iocg->hweight_active);
		iocg->hweight_after_करोnation = min(iocg->hweight_after_करोnation,
						   iocg->hweight_करोnating - 1);
		अगर (WARN_ON_ONCE(iocg->hweight_active <= 1 ||
				 iocg->hweight_करोnating <= 1 ||
				 iocg->hweight_after_करोnation == 0)) अणु
			pr_warn("iocg: invalid donation weights in ");
			pr_cont_cgroup_path(iocg_to_blkg(iocg)->blkcg->css.cgroup);
			pr_cont(": active=%u donating=%u after=%u\n",
				iocg->hweight_active, iocg->hweight_करोnating,
				iocg->hweight_after_करोnation);
		पूर्ण
	पूर्ण

	/*
	 * Calculate the global करोnation rate (gamma) - the rate to adjust
	 * non-करोnating budमाला_लो by.
	 *
	 * No need to use 64bit multiplication here as the first opeअक्रम is
	 * guaranteed to be smaller than WEIGHT_ONE (1<<16).
	 *
	 * We know that there are beneficiary nodes and the sum of the करोnating
	 * hweights can't be whole; however, due to the round-ups during hweight
	 * calculations, root_iocg->hweight_करोnating might still end up equal to
	 * or greater than whole. Limit the range when calculating the भागider.
	 *
	 * gamma = (1 - t_r') / (1 - t_r)
	 */
	gamma = DIV_ROUND_UP(
		(WEIGHT_ONE - root_iocg->hweight_after_करोnation) * WEIGHT_ONE,
		WEIGHT_ONE - min_t(u32, root_iocg->hweight_करोnating, WEIGHT_ONE - 1));

	/*
	 * Calculate adjusted hwi, child_adjusted_sum and inuse क्रम the inner
	 * nodes.
	 */
	list_क्रम_each_entry(iocg, &inner_walk, walk_list) अणु
		काष्ठा ioc_gq *parent;
		u32 inuse, wpt, wptp;
		u64 st, sf;

		अगर (iocg->level == 0) अणु
			/* adjusted weight sum क्रम 1st level: s' = s * b_pf / b'_pf */
			iocg->child_adjusted_sum = DIV64_U64_ROUND_UP(
				iocg->child_active_sum * (WEIGHT_ONE - iocg->hweight_करोnating),
				WEIGHT_ONE - iocg->hweight_after_करोnation);
			जारी;
		पूर्ण

		parent = iocg->ancestors[iocg->level - 1];

		/* b' = gamma * b_f + b_t' */
		iocg->hweight_inuse = DIV64_U64_ROUND_UP(
			(u64)gamma * (iocg->hweight_active - iocg->hweight_करोnating),
			WEIGHT_ONE) + iocg->hweight_after_करोnation;

		/* w' = s' * b' / b'_p */
		inuse = DIV64_U64_ROUND_UP(
			(u64)parent->child_adjusted_sum * iocg->hweight_inuse,
			parent->hweight_inuse);

		/* adjusted weight sum क्रम children: s' = s_f + s_t * w'_pt / w_pt */
		st = DIV64_U64_ROUND_UP(
			iocg->child_active_sum * iocg->hweight_करोnating,
			iocg->hweight_active);
		sf = iocg->child_active_sum - st;
		wpt = DIV64_U64_ROUND_UP(
			(u64)iocg->active * iocg->hweight_करोnating,
			iocg->hweight_active);
		wptp = DIV64_U64_ROUND_UP(
			(u64)inuse * iocg->hweight_after_करोnation,
			iocg->hweight_inuse);

		iocg->child_adjusted_sum = sf + DIV64_U64_ROUND_UP(st * wptp, wpt);
	पूर्ण

	/*
	 * All inner nodes now have ->hweight_inuse and ->child_adjusted_sum and
	 * we can finally determine leaf adjusपंचांगents.
	 */
	list_क्रम_each_entry(iocg, surpluses, surplus_list) अणु
		काष्ठा ioc_gq *parent = iocg->ancestors[iocg->level - 1];
		u32 inuse;

		/*
		 * In-debt iocgs participated in the करोnation calculation with
		 * the minimum target hweight_inuse. Configuring inuse
		 * accordingly would work fine but debt handling expects
		 * @iocg->inuse stay at the minimum and we करोn't wanna
		 * पूर्णांकerfere.
		 */
		अगर (iocg->असल_vdebt) अणु
			WARN_ON_ONCE(iocg->inuse > 1);
			जारी;
		पूर्ण

		/* w' = s' * b' / b'_p, note that b' == b'_t क्रम करोnating leaves */
		inuse = DIV64_U64_ROUND_UP(
			parent->child_adjusted_sum * iocg->hweight_after_करोnation,
			parent->hweight_inuse);

		TRACE_IOCG_PATH(inuse_transfer, iocg, now,
				iocg->inuse, inuse,
				iocg->hweight_inuse,
				iocg->hweight_after_करोnation);

		__propagate_weights(iocg, iocg->active, inuse, true, now);
	पूर्ण

	/* walk list should be dissolved after use */
	list_क्रम_each_entry_safe(iocg, tiocg, &inner_walk, walk_list)
		list_del_init(&iocg->walk_list);
पूर्ण

/*
 * A low weight iocg can amass a large amount of debt, क्रम example, when
 * anonymous memory माला_लो reclaimed aggressively. If the प्रणाली has a lot of
 * memory paired with a slow IO device, the debt can span multiple seconds or
 * more. If there are no other subsequent IO issuers, the in-debt iocg may end
 * up blocked paying its debt जबतक the IO device is idle.
 *
 * The following protects against such हालs. If the device has been
 * sufficiently idle क्रम a जबतक, the debts are halved and delays are
 * recalculated.
 */
अटल व्योम ioc_क्रमgive_debts(काष्ठा ioc *ioc, u64 usage_us_sum, पूर्णांक nr_debtors,
			      काष्ठा ioc_now *now)
अणु
	काष्ठा ioc_gq *iocg;
	u64 dur, usage_pct, nr_cycles;

	/* अगर no debtor, reset the cycle */
	अगर (!nr_debtors) अणु
		ioc->dfgv_period_at = now->now;
		ioc->dfgv_period_rem = 0;
		ioc->dfgv_usage_us_sum = 0;
		वापस;
	पूर्ण

	/*
	 * Debtors can pass through a lot of ग_लिखोs choking the device and we
	 * करोn't want to be क्रमgiving debts जबतक the device is struggling from
	 * ग_लिखो bursts. If we're missing latency tarमाला_लो, consider the device
	 * fully utilized.
	 */
	अगर (ioc->busy_level > 0)
		usage_us_sum = max_t(u64, usage_us_sum, ioc->period_us);

	ioc->dfgv_usage_us_sum += usage_us_sum;
	अगर (समय_beक्रमe64(now->now, ioc->dfgv_period_at + DFGV_PERIOD))
		वापस;

	/*
	 * At least DFGV_PERIOD has passed since the last period. Calculate the
	 * average usage and reset the period counters.
	 */
	dur = now->now - ioc->dfgv_period_at;
	usage_pct = भाग64_u64(100 * ioc->dfgv_usage_us_sum, dur);

	ioc->dfgv_period_at = now->now;
	ioc->dfgv_usage_us_sum = 0;

	/* अगर was too busy, reset everything */
	अगर (usage_pct > DFGV_USAGE_PCT) अणु
		ioc->dfgv_period_rem = 0;
		वापस;
	पूर्ण

	/*
	 * Usage is lower than threshold. Let's क्रमgive some debts. Debt
	 * क्रमgiveness runs off of the usual ioc समयr but its period usually
	 * करोesn't match ioc's. Compensate the dअगरference by perक्रमming the
	 * reduction as many बार as would fit in the duration since the last
	 * run and carrying over the left-over duration in @ioc->dfgv_period_rem
	 * - अगर ioc period is 75% of DFGV_PERIOD, one out of three consecutive
	 * reductions is द्विगुनd.
	 */
	nr_cycles = dur + ioc->dfgv_period_rem;
	ioc->dfgv_period_rem = करो_भाग(nr_cycles, DFGV_PERIOD);

	list_क्रम_each_entry(iocg, &ioc->active_iocgs, active_list) अणु
		u64 __maybe_unused old_debt, __maybe_unused old_delay;

		अगर (!iocg->असल_vdebt && !iocg->delay)
			जारी;

		spin_lock(&iocg->रुकोq.lock);

		old_debt = iocg->असल_vdebt;
		old_delay = iocg->delay;

		अगर (iocg->असल_vdebt)
			iocg->असल_vdebt = iocg->असल_vdebt >> nr_cycles ?: 1;
		अगर (iocg->delay)
			iocg->delay = iocg->delay >> nr_cycles ?: 1;

		iocg_kick_रुकोq(iocg, true, now);

		TRACE_IOCG_PATH(iocg_क्रमgive_debt, iocg, now, usage_pct,
				old_debt, iocg->असल_vdebt,
				old_delay, iocg->delay);

		spin_unlock(&iocg->रुकोq.lock);
	पूर्ण
पूर्ण

/*
 * Check the active iocgs' state to aव्योम oversleeping and deactive
 * idle iocgs.
 *
 * Since रुकोers determine the sleep durations based on the vrate
 * they saw at the समय of sleep, अगर vrate has increased, some
 * रुकोers could be sleeping क्रम too दीर्घ. Wake up tardy रुकोers
 * which should have woken up in the last period and expire idle
 * iocgs.
 */
अटल पूर्णांक ioc_check_iocgs(काष्ठा ioc *ioc, काष्ठा ioc_now *now)
अणु
	पूर्णांक nr_debtors = 0;
	काष्ठा ioc_gq *iocg, *tiocg;

	list_क्रम_each_entry_safe(iocg, tiocg, &ioc->active_iocgs, active_list) अणु
		अगर (!रुकोqueue_active(&iocg->रुकोq) && !iocg->असल_vdebt &&
		    !iocg->delay && !iocg_is_idle(iocg))
			जारी;

		spin_lock(&iocg->रुकोq.lock);

		/* flush रुको and indebt stat deltas */
		अगर (iocg->रुको_since) अणु
			iocg->local_stat.रुको_us += now->now - iocg->रुको_since;
			iocg->रुको_since = now->now;
		पूर्ण
		अगर (iocg->indebt_since) अणु
			iocg->local_stat.indebt_us +=
				now->now - iocg->indebt_since;
			iocg->indebt_since = now->now;
		पूर्ण
		अगर (iocg->indelay_since) अणु
			iocg->local_stat.indelay_us +=
				now->now - iocg->indelay_since;
			iocg->indelay_since = now->now;
		पूर्ण

		अगर (रुकोqueue_active(&iocg->रुकोq) || iocg->असल_vdebt ||
		    iocg->delay) अणु
			/* might be oversleeping vसमय / hweight changes, kick */
			iocg_kick_रुकोq(iocg, true, now);
			अगर (iocg->असल_vdebt || iocg->delay)
				nr_debtors++;
		पूर्ण अन्यथा अगर (iocg_is_idle(iocg)) अणु
			/* no रुकोer and idle, deactivate */
			u64 vसमय = atomic64_पढ़ो(&iocg->vसमय);
			s64 excess;

			/*
			 * @iocg has been inactive क्रम a full duration and will
			 * have a high budget. Account anything above target as
			 * error and throw away. On reactivation, it'll start
			 * with the target budget.
			 */
			excess = now->vnow - vसमय - ioc->margins.target;
			अगर (excess > 0) अणु
				u32 old_hwi;

				current_hweight(iocg, शून्य, &old_hwi);
				ioc->vसमय_err -= भाग64_u64(excess * old_hwi,
							    WEIGHT_ONE);
			पूर्ण

			TRACE_IOCG_PATH(iocg_idle, iocg, now,
					atomic64_पढ़ो(&iocg->active_period),
					atomic64_पढ़ो(&ioc->cur_period), vसमय);
			__propagate_weights(iocg, 0, 0, false, now);
			list_del_init(&iocg->active_list);
		पूर्ण

		spin_unlock(&iocg->रुकोq.lock);
	पूर्ण

	commit_weights(ioc);
	वापस nr_debtors;
पूर्ण

अटल व्योम ioc_समयr_fn(काष्ठा समयr_list *समयr)
अणु
	काष्ठा ioc *ioc = container_of(समयr, काष्ठा ioc, समयr);
	काष्ठा ioc_gq *iocg, *tiocg;
	काष्ठा ioc_now now;
	LIST_HEAD(surpluses);
	पूर्णांक nr_debtors, nr_लघुages = 0, nr_lagging = 0;
	u64 usage_us_sum = 0;
	u32 ppm_rthr = MILLION - ioc->params.qos[QOS_RPPM];
	u32 ppm_wthr = MILLION - ioc->params.qos[QOS_WPPM];
	u32 missed_ppm[2], rq_रुको_pct;
	u64 period_vसमय;
	पूर्णांक prev_busy_level;

	/* how were the latencies during the period? */
	ioc_lat_stat(ioc, missed_ppm, &rq_रुको_pct);

	/* take care of active iocgs */
	spin_lock_irq(&ioc->lock);

	ioc_now(ioc, &now);

	period_vसमय = now.vnow - ioc->period_at_vसमय;
	अगर (WARN_ON_ONCE(!period_vसमय)) अणु
		spin_unlock_irq(&ioc->lock);
		वापस;
	पूर्ण

	nr_debtors = ioc_check_iocgs(ioc, &now);

	/*
	 * Wait and indebt stat are flushed above and the करोnation calculation
	 * below needs updated usage stat. Let's bring stat up-to-date.
	 */
	iocg_flush_stat(&ioc->active_iocgs, &now);

	/* calc usage and see whether some weights need to be moved around */
	list_क्रम_each_entry(iocg, &ioc->active_iocgs, active_list) अणु
		u64 vकरोne, vसमय, usage_us;
		u32 hw_active, hw_inuse;

		/*
		 * Collect unused and wind vसमय बंदr to vnow to prevent
		 * iocgs from accumulating a large amount of budget.
		 */
		vकरोne = atomic64_पढ़ो(&iocg->करोne_vसमय);
		vसमय = atomic64_पढ़ो(&iocg->vसमय);
		current_hweight(iocg, &hw_active, &hw_inuse);

		/*
		 * Latency QoS detection करोesn't account क्रम IOs which are
		 * in-flight क्रम दीर्घer than a period.  Detect them by
		 * comparing vकरोne against period start.  If lagging behind
		 * IOs from past periods, करोn't increase vrate.
		 */
		अगर ((ppm_rthr != MILLION || ppm_wthr != MILLION) &&
		    !atomic_पढ़ो(&iocg_to_blkg(iocg)->use_delay) &&
		    समय_after64(vसमय, vकरोne) &&
		    समय_after64(vसमय, now.vnow -
				 MAX_LAGGING_PERIODS * period_vसमय) &&
		    समय_beक्रमe64(vकरोne, now.vnow - period_vसमय))
			nr_lagging++;

		/*
		 * Determine असलolute usage factoring in in-flight IOs to aव्योम
		 * high-latency completions appearing as idle.
		 */
		usage_us = iocg->usage_delta_us;
		usage_us_sum += usage_us;

		/* see whether there's surplus vसमय */
		WARN_ON_ONCE(!list_empty(&iocg->surplus_list));
		अगर (hw_inuse < hw_active ||
		    (!रुकोqueue_active(&iocg->रुकोq) &&
		     समय_beक्रमe64(vसमय, now.vnow - ioc->margins.low))) अणु
			u32 hwa, old_hwi, hwm, new_hwi, usage;
			u64 usage_dur;

			अगर (vकरोne != vसमय) अणु
				u64 inflight_us = DIV64_U64_ROUND_UP(
					cost_to_असल_cost(vसमय - vकरोne, hw_inuse),
					ioc->vसमय_base_rate);

				usage_us = max(usage_us, inflight_us);
			पूर्ण

			/* convert to hweight based usage ratio */
			अगर (समय_after64(iocg->activated_at, ioc->period_at))
				usage_dur = max_t(u64, now.now - iocg->activated_at, 1);
			अन्यथा
				usage_dur = max_t(u64, now.now - ioc->period_at, 1);

			usage = clamp_t(u32,
				DIV64_U64_ROUND_UP(usage_us * WEIGHT_ONE,
						   usage_dur),
				1, WEIGHT_ONE);

			/*
			 * Alपढ़ोy करोnating or accumulated enough to start.
			 * Determine the करोnation amount.
			 */
			current_hweight(iocg, &hwa, &old_hwi);
			hwm = current_hweight_max(iocg);
			new_hwi = hweight_after_करोnation(iocg, old_hwi, hwm,
							 usage, &now);
			अगर (new_hwi < hwm) अणु
				iocg->hweight_करोnating = hwa;
				iocg->hweight_after_करोnation = new_hwi;
				list_add(&iocg->surplus_list, &surpluses);
			पूर्ण अन्यथा अणु
				TRACE_IOCG_PATH(inuse_लघुage, iocg, &now,
						iocg->inuse, iocg->active,
						iocg->hweight_inuse, new_hwi);

				__propagate_weights(iocg, iocg->active,
						    iocg->active, true, &now);
				nr_लघुages++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* genuinely लघु on vसमय */
			nr_लघुages++;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&surpluses) && nr_लघुages)
		transfer_surpluses(&surpluses, &now);

	commit_weights(ioc);

	/* surplus list should be dissolved after use */
	list_क्रम_each_entry_safe(iocg, tiocg, &surpluses, surplus_list)
		list_del_init(&iocg->surplus_list);

	/*
	 * If q is getting clogged or we're missing too much, we're issuing
	 * too much IO and should lower vसमय rate.  If we're not missing
	 * and experiencing लघुages but not surpluses, we're too stingy
	 * and should increase vसमय rate.
	 */
	prev_busy_level = ioc->busy_level;
	अगर (rq_रुको_pct > RQ_WAIT_BUSY_PCT ||
	    missed_ppm[READ] > ppm_rthr ||
	    missed_ppm[WRITE] > ppm_wthr) अणु
		/* clearly missing QoS tarमाला_लो, slow करोwn vrate */
		ioc->busy_level = max(ioc->busy_level, 0);
		ioc->busy_level++;
	पूर्ण अन्यथा अगर (rq_रुको_pct <= RQ_WAIT_BUSY_PCT * UNBUSY_THR_PCT / 100 &&
		   missed_ppm[READ] <= ppm_rthr * UNBUSY_THR_PCT / 100 &&
		   missed_ppm[WRITE] <= ppm_wthr * UNBUSY_THR_PCT / 100) अणु
		/* QoS tarमाला_लो are being met with >25% margin */
		अगर (nr_लघुages) अणु
			/*
			 * We're throttling जबतक the device has spare
			 * capacity.  If vrate was being slowed करोwn, stop.
			 */
			ioc->busy_level = min(ioc->busy_level, 0);

			/*
			 * If there are IOs spanning multiple periods, रुको
			 * them out beक्रमe pushing the device harder.
			 */
			अगर (!nr_lagging)
				ioc->busy_level--;
		पूर्ण अन्यथा अणु
			/*
			 * Nobody is being throttled and the users aren't
			 * issuing enough IOs to saturate the device.  We
			 * simply करोn't know how बंद the device is to
			 * saturation.  Coast.
			 */
			ioc->busy_level = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* inside the hysterisis margin, we're good */
		ioc->busy_level = 0;
	पूर्ण

	ioc->busy_level = clamp(ioc->busy_level, -1000, 1000);

	ioc_adjust_base_vrate(ioc, rq_रुको_pct, nr_lagging, nr_लघुages,
			      prev_busy_level, missed_ppm);

	ioc_refresh_params(ioc, false);

	ioc_क्रमgive_debts(ioc, usage_us_sum, nr_debtors, &now);

	/*
	 * This period is करोne.  Move onto the next one.  If nothing's
	 * going on with the device, stop the समयr.
	 */
	atomic64_inc(&ioc->cur_period);

	अगर (ioc->running != IOC_STOP) अणु
		अगर (!list_empty(&ioc->active_iocgs)) अणु
			ioc_start_period(ioc, &now);
		पूर्ण अन्यथा अणु
			ioc->busy_level = 0;
			ioc->vसमय_err = 0;
			ioc->running = IOC_IDLE;
		पूर्ण

		ioc_refresh_vrate(ioc, &now);
	पूर्ण

	spin_unlock_irq(&ioc->lock);
पूर्ण

अटल u64 adjust_inuse_and_calc_cost(काष्ठा ioc_gq *iocg, u64 vसमय,
				      u64 असल_cost, काष्ठा ioc_now *now)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	काष्ठा ioc_margins *margins = &ioc->margins;
	u32 __maybe_unused old_inuse = iocg->inuse, __maybe_unused old_hwi;
	u32 hwi, adj_step;
	s64 margin;
	u64 cost, new_inuse;

	current_hweight(iocg, शून्य, &hwi);
	old_hwi = hwi;
	cost = असल_cost_to_cost(असल_cost, hwi);
	margin = now->vnow - vसमय - cost;

	/* debt handling owns inuse क्रम debtors */
	अगर (iocg->असल_vdebt)
		वापस cost;

	/*
	 * We only increase inuse during period and करो so अगर the margin has
	 * deteriorated since the previous adjusपंचांगent.
	 */
	अगर (margin >= iocg->saved_margin || margin >= margins->low ||
	    iocg->inuse == iocg->active)
		वापस cost;

	spin_lock_irq(&ioc->lock);

	/* we own inuse only when @iocg is in the normal active state */
	अगर (iocg->असल_vdebt || list_empty(&iocg->active_list)) अणु
		spin_unlock_irq(&ioc->lock);
		वापस cost;
	पूर्ण

	/*
	 * Bump up inuse till @असल_cost fits in the existing budget.
	 * adj_step must be determined after acquiring ioc->lock - we might
	 * have raced and lost to another thपढ़ो क्रम activation and could
	 * be पढ़ोing 0 iocg->active beक्रमe ioc->lock which will lead to
	 * infinite loop.
	 */
	new_inuse = iocg->inuse;
	adj_step = DIV_ROUND_UP(iocg->active * INUSE_ADJ_STEP_PCT, 100);
	करो अणु
		new_inuse = new_inuse + adj_step;
		propagate_weights(iocg, iocg->active, new_inuse, true, now);
		current_hweight(iocg, शून्य, &hwi);
		cost = असल_cost_to_cost(असल_cost, hwi);
	पूर्ण जबतक (समय_after64(vसमय + cost, now->vnow) &&
		 iocg->inuse != iocg->active);

	spin_unlock_irq(&ioc->lock);

	TRACE_IOCG_PATH(inuse_adjust, iocg, now,
			old_inuse, iocg->inuse, old_hwi, hwi);

	वापस cost;
पूर्ण

अटल व्योम calc_vसमय_cost_builtin(काष्ठा bio *bio, काष्ठा ioc_gq *iocg,
				    bool is_merge, u64 *costp)
अणु
	काष्ठा ioc *ioc = iocg->ioc;
	u64 coef_seqio, coef_अक्रमio, coef_page;
	u64 pages = max_t(u64, bio_sectors(bio) >> IOC_SECT_TO_PAGE_SHIFT, 1);
	u64 seek_pages = 0;
	u64 cost = 0;

	चयन (bio_op(bio)) अणु
	हाल REQ_OP_READ:
		coef_seqio	= ioc->params.lcoefs[LCOEF_RSEQIO];
		coef_अक्रमio	= ioc->params.lcoefs[LCOEF_RRANDIO];
		coef_page	= ioc->params.lcoefs[LCOEF_RPAGE];
		अवरोध;
	हाल REQ_OP_WRITE:
		coef_seqio	= ioc->params.lcoefs[LCOEF_WSEQIO];
		coef_अक्रमio	= ioc->params.lcoefs[LCOEF_WRANDIO];
		coef_page	= ioc->params.lcoefs[LCOEF_WPAGE];
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	अगर (iocg->cursor) अणु
		seek_pages = असल(bio->bi_iter.bi_sector - iocg->cursor);
		seek_pages >>= IOC_SECT_TO_PAGE_SHIFT;
	पूर्ण

	अगर (!is_merge) अणु
		अगर (seek_pages > LCOEF_RANDIO_PAGES) अणु
			cost += coef_अक्रमio;
		पूर्ण अन्यथा अणु
			cost += coef_seqio;
		पूर्ण
	पूर्ण
	cost += pages * coef_page;
out:
	*costp = cost;
पूर्ण

अटल u64 calc_vसमय_cost(काष्ठा bio *bio, काष्ठा ioc_gq *iocg, bool is_merge)
अणु
	u64 cost;

	calc_vसमय_cost_builtin(bio, iocg, is_merge, &cost);
	वापस cost;
पूर्ण

अटल व्योम calc_size_vसमय_cost_builtin(काष्ठा request *rq, काष्ठा ioc *ioc,
					 u64 *costp)
अणु
	अचिन्हित पूर्णांक pages = blk_rq_stats_sectors(rq) >> IOC_SECT_TO_PAGE_SHIFT;

	चयन (req_op(rq)) अणु
	हाल REQ_OP_READ:
		*costp = pages * ioc->params.lcoefs[LCOEF_RPAGE];
		अवरोध;
	हाल REQ_OP_WRITE:
		*costp = pages * ioc->params.lcoefs[LCOEF_WPAGE];
		अवरोध;
	शेष:
		*costp = 0;
	पूर्ण
पूर्ण

अटल u64 calc_size_vसमय_cost(काष्ठा request *rq, काष्ठा ioc *ioc)
अणु
	u64 cost;

	calc_size_vसमय_cost_builtin(rq, ioc, &cost);
	वापस cost;
पूर्ण

अटल व्योम ioc_rqos_throttle(काष्ठा rq_qos *rqos, काष्ठा bio *bio)
अणु
	काष्ठा blkcg_gq *blkg = bio->bi_blkg;
	काष्ठा ioc *ioc = rqos_to_ioc(rqos);
	काष्ठा ioc_gq *iocg = blkg_to_iocg(blkg);
	काष्ठा ioc_now now;
	काष्ठा iocg_रुको रुको;
	u64 असल_cost, cost, vसमय;
	bool use_debt, ioc_locked;
	अचिन्हित दीर्घ flags;

	/* bypass IOs अगर disabled, still initializing, or क्रम root cgroup */
	अगर (!ioc->enabled || !iocg || !iocg->level)
		वापस;

	/* calculate the असलolute vसमय cost */
	असल_cost = calc_vसमय_cost(bio, iocg, false);
	अगर (!असल_cost)
		वापस;

	अगर (!iocg_activate(iocg, &now))
		वापस;

	iocg->cursor = bio_end_sector(bio);
	vसमय = atomic64_पढ़ो(&iocg->vसमय);
	cost = adjust_inuse_and_calc_cost(iocg, vसमय, असल_cost, &now);

	/*
	 * If no one's रुकोing and within budget, issue right away.  The
	 * tests are racy but the races aren't प्रणालीic - we only miss once
	 * in a जबतक which is fine.
	 */
	अगर (!रुकोqueue_active(&iocg->रुकोq) && !iocg->असल_vdebt &&
	    समय_beक्रमe_eq64(vसमय + cost, now.vnow)) अणु
		iocg_commit_bio(iocg, bio, असल_cost, cost);
		वापस;
	पूर्ण

	/*
	 * We're over budget. This can be handled in two ways. IOs which may
	 * cause priority inversions are punted to @ioc->aux_iocg and अक्षरged as
	 * debt. Otherwise, the issuer is blocked on @iocg->रुकोq. Debt handling
	 * requires @ioc->lock, रुकोq handling @iocg->रुकोq.lock. Determine
	 * whether debt handling is needed and acquire locks accordingly.
	 */
	use_debt = bio_issue_as_root_blkg(bio) || fatal_संकेत_pending(current);
	ioc_locked = use_debt || READ_ONCE(iocg->असल_vdebt);
retry_lock:
	iocg_lock(iocg, ioc_locked, &flags);

	/*
	 * @iocg must stay activated क्रम debt and रुकोq handling. Deactivation
	 * is synchronized against both ioc->lock and रुकोq.lock and we won't
	 * get deactivated as दीर्घ as we're waiting or has debt, so we're good
	 * अगर we're activated here. In the unlikely cases that we aren't, just
	 * issue the IO.
	 */
	अगर (unlikely(list_empty(&iocg->active_list))) अणु
		iocg_unlock(iocg, ioc_locked, &flags);
		iocg_commit_bio(iocg, bio, असल_cost, cost);
		वापस;
	पूर्ण

	/*
	 * We're over budget. If @bio has to be issued regardless, remember
	 * the असल_cost instead of advancing vसमय. iocg_kick_रुकोq() will pay
	 * off the debt beक्रमe waking more IOs.
	 *
	 * This way, the debt is continuously paid off each period with the
	 * actual budget available to the cgroup. If we just wound vसमय, we
	 * would incorrectly use the current hw_inuse क्रम the entire amount
	 * which, क्रम example, can lead to the cgroup staying blocked क्रम a
	 * दीर्घ समय even with substantially उठाओd hw_inuse.
	 *
	 * An iocg with vdebt should stay online so that the समयr can keep
	 * deducting its vdebt and [de]activate use_delay mechanism
	 * accordingly. We करोn't want to race against the समयr trying to
	 * clear them and leave @iocg inactive w/ dangling use_delay heavily
	 * penalizing the cgroup and its descendants.
	 */
	अगर (use_debt) अणु
		iocg_incur_debt(iocg, असल_cost, &now);
		अगर (iocg_kick_delay(iocg, &now))
			blkcg_schedule_throttle(rqos->q,
					(bio->bi_opf & REQ_SWAP) == REQ_SWAP);
		iocg_unlock(iocg, ioc_locked, &flags);
		वापस;
	पूर्ण

	/* guarantee that iocgs w/ रुकोers have maximum inuse */
	अगर (!iocg->असल_vdebt && iocg->inuse != iocg->active) अणु
		अगर (!ioc_locked) अणु
			iocg_unlock(iocg, false, &flags);
			ioc_locked = true;
			जाओ retry_lock;
		पूर्ण
		propagate_weights(iocg, iocg->active, iocg->active, true,
				  &now);
	पूर्ण

	/*
	 * Append self to the रुकोq and schedule the wakeup समयr अगर we're
	 * the first रुकोer.  The समयr duration is calculated based on the
	 * current vrate.  vसमय and hweight changes can make it too लघु
	 * or too दीर्घ.  Each रुको entry records the असलolute cost it's
	 * रुकोing क्रम to allow re-evaluation using a custom रुको entry.
	 *
	 * If too लघु, the समयr simply reschedules itself.  If too दीर्घ,
	 * the period समयr will notice and trigger wakeups.
	 *
	 * All रुकोers are on iocg->रुकोq and the रुको states are
	 * synchronized using रुकोq.lock.
	 */
	init_रुकोqueue_func_entry(&रुको.रुको, iocg_wake_fn);
	रुको.रुको.निजी = current;
	रुको.bio = bio;
	रुको.असल_cost = असल_cost;
	रुको.committed = false;	/* will be set true by waker */

	__add_रुको_queue_entry_tail(&iocg->रुकोq, &रुको.रुको);
	iocg_kick_रुकोq(iocg, ioc_locked, &now);

	iocg_unlock(iocg, ioc_locked, &flags);

	जबतक (true) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (रुको.committed)
			अवरोध;
		io_schedule();
	पूर्ण

	/* waker alपढ़ोy committed us, proceed */
	finish_रुको(&iocg->रुकोq, &रुको.रुको);
पूर्ण

अटल व्योम ioc_rqos_merge(काष्ठा rq_qos *rqos, काष्ठा request *rq,
			   काष्ठा bio *bio)
अणु
	काष्ठा ioc_gq *iocg = blkg_to_iocg(bio->bi_blkg);
	काष्ठा ioc *ioc = rqos_to_ioc(rqos);
	sector_t bio_end = bio_end_sector(bio);
	काष्ठा ioc_now now;
	u64 vसमय, असल_cost, cost;
	अचिन्हित दीर्घ flags;

	/* bypass अगर disabled, still initializing, or क्रम root cgroup */
	अगर (!ioc->enabled || !iocg || !iocg->level)
		वापस;

	असल_cost = calc_vसमय_cost(bio, iocg, true);
	अगर (!असल_cost)
		वापस;

	ioc_now(ioc, &now);

	vसमय = atomic64_पढ़ो(&iocg->vसमय);
	cost = adjust_inuse_and_calc_cost(iocg, vसमय, असल_cost, &now);

	/* update cursor अगर backmerging पूर्णांकo the request at the cursor */
	अगर (blk_rq_pos(rq) < bio_end &&
	    blk_rq_pos(rq) + blk_rq_sectors(rq) == iocg->cursor)
		iocg->cursor = bio_end;

	/*
	 * Charge अगर there's enough vसमय budget and the existing request has
	 * cost asचिन्हित.
	 */
	अगर (rq->bio && rq->bio->bi_iocost_cost &&
	    समय_beक्रमe_eq64(atomic64_पढ़ो(&iocg->vसमय) + cost, now.vnow)) अणु
		iocg_commit_bio(iocg, bio, असल_cost, cost);
		वापस;
	पूर्ण

	/*
	 * Otherwise, account it as debt अगर @iocg is online, which it should
	 * be क्रम the vast majority of हालs. See debt handling in
	 * ioc_rqos_throttle() क्रम details.
	 */
	spin_lock_irqsave(&ioc->lock, flags);
	spin_lock(&iocg->रुकोq.lock);

	अगर (likely(!list_empty(&iocg->active_list))) अणु
		iocg_incur_debt(iocg, असल_cost, &now);
		अगर (iocg_kick_delay(iocg, &now))
			blkcg_schedule_throttle(rqos->q,
					(bio->bi_opf & REQ_SWAP) == REQ_SWAP);
	पूर्ण अन्यथा अणु
		iocg_commit_bio(iocg, bio, असल_cost, cost);
	पूर्ण

	spin_unlock(&iocg->रुकोq.lock);
	spin_unlock_irqrestore(&ioc->lock, flags);
पूर्ण

अटल व्योम ioc_rqos_करोne_bio(काष्ठा rq_qos *rqos, काष्ठा bio *bio)
अणु
	काष्ठा ioc_gq *iocg = blkg_to_iocg(bio->bi_blkg);

	अगर (iocg && bio->bi_iocost_cost)
		atomic64_add(bio->bi_iocost_cost, &iocg->करोne_vसमय);
पूर्ण

अटल व्योम ioc_rqos_करोne(काष्ठा rq_qos *rqos, काष्ठा request *rq)
अणु
	काष्ठा ioc *ioc = rqos_to_ioc(rqos);
	काष्ठा ioc_pcpu_stat *ccs;
	u64 on_q_ns, rq_रुको_ns, size_nsec;
	पूर्णांक pidx, rw;

	अगर (!ioc->enabled || !rq->alloc_समय_ns || !rq->start_समय_ns)
		वापस;

	चयन (req_op(rq) & REQ_OP_MASK) अणु
	हाल REQ_OP_READ:
		pidx = QOS_RLAT;
		rw = READ;
		अवरोध;
	हाल REQ_OP_WRITE:
		pidx = QOS_WLAT;
		rw = WRITE;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	on_q_ns = kसमय_get_ns() - rq->alloc_समय_ns;
	rq_रुको_ns = rq->start_समय_ns - rq->alloc_समय_ns;
	size_nsec = भाग64_u64(calc_size_vसमय_cost(rq, ioc), VTIME_PER_NSEC);

	ccs = get_cpu_ptr(ioc->pcpu_stat);

	अगर (on_q_ns <= size_nsec ||
	    on_q_ns - size_nsec <= ioc->params.qos[pidx] * NSEC_PER_USEC)
		local_inc(&ccs->missed[rw].nr_met);
	अन्यथा
		local_inc(&ccs->missed[rw].nr_missed);

	local64_add(rq_रुको_ns, &ccs->rq_रुको_ns);

	put_cpu_ptr(ccs);
पूर्ण

अटल व्योम ioc_rqos_queue_depth_changed(काष्ठा rq_qos *rqos)
अणु
	काष्ठा ioc *ioc = rqos_to_ioc(rqos);

	spin_lock_irq(&ioc->lock);
	ioc_refresh_params(ioc, false);
	spin_unlock_irq(&ioc->lock);
पूर्ण

अटल व्योम ioc_rqos_निकास(काष्ठा rq_qos *rqos)
अणु
	काष्ठा ioc *ioc = rqos_to_ioc(rqos);

	blkcg_deactivate_policy(rqos->q, &blkcg_policy_iocost);

	spin_lock_irq(&ioc->lock);
	ioc->running = IOC_STOP;
	spin_unlock_irq(&ioc->lock);

	del_समयr_sync(&ioc->समयr);
	मुक्त_percpu(ioc->pcpu_stat);
	kमुक्त(ioc);
पूर्ण

अटल काष्ठा rq_qos_ops ioc_rqos_ops = अणु
	.throttle = ioc_rqos_throttle,
	.merge = ioc_rqos_merge,
	.करोne_bio = ioc_rqos_करोne_bio,
	.करोne = ioc_rqos_करोne,
	.queue_depth_changed = ioc_rqos_queue_depth_changed,
	.निकास = ioc_rqos_निकास,
पूर्ण;

अटल पूर्णांक blk_iocost_init(काष्ठा request_queue *q)
अणु
	काष्ठा ioc *ioc;
	काष्ठा rq_qos *rqos;
	पूर्णांक i, cpu, ret;

	ioc = kzalloc(माप(*ioc), GFP_KERNEL);
	अगर (!ioc)
		वापस -ENOMEM;

	ioc->pcpu_stat = alloc_percpu(काष्ठा ioc_pcpu_stat);
	अगर (!ioc->pcpu_stat) अणु
		kमुक्त(ioc);
		वापस -ENOMEM;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा ioc_pcpu_stat *ccs = per_cpu_ptr(ioc->pcpu_stat, cpu);

		क्रम (i = 0; i < ARRAY_SIZE(ccs->missed); i++) अणु
			local_set(&ccs->missed[i].nr_met, 0);
			local_set(&ccs->missed[i].nr_missed, 0);
		पूर्ण
		local64_set(&ccs->rq_रुको_ns, 0);
	पूर्ण

	rqos = &ioc->rqos;
	rqos->id = RQ_QOS_COST;
	rqos->ops = &ioc_rqos_ops;
	rqos->q = q;

	spin_lock_init(&ioc->lock);
	समयr_setup(&ioc->समयr, ioc_समयr_fn, 0);
	INIT_LIST_HEAD(&ioc->active_iocgs);

	ioc->running = IOC_IDLE;
	ioc->vसमय_base_rate = VTIME_PER_USEC;
	atomic64_set(&ioc->vसमय_rate, VTIME_PER_USEC);
	seqcount_spinlock_init(&ioc->period_seqcount, &ioc->lock);
	ioc->period_at = kसमय_प्रकारo_us(kसमय_get());
	atomic64_set(&ioc->cur_period, 0);
	atomic_set(&ioc->hweight_gen, 0);

	spin_lock_irq(&ioc->lock);
	ioc->स्वतःp_idx = AUTOP_INVALID;
	ioc_refresh_params(ioc, true);
	spin_unlock_irq(&ioc->lock);

	/*
	 * rqos must be added beक्रमe activation to allow iocg_pd_init() to
	 * lookup the ioc from q. This means that the rqos methods may get
	 * called beक्रमe policy activation completion, can't assume that the
	 * target bio has an iocg associated and need to test क्रम शून्य iocg.
	 */
	rq_qos_add(q, rqos);
	ret = blkcg_activate_policy(q, &blkcg_policy_iocost);
	अगर (ret) अणु
		rq_qos_del(q, rqos);
		मुक्त_percpu(ioc->pcpu_stat);
		kमुक्त(ioc);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा blkcg_policy_data *ioc_cpd_alloc(gfp_t gfp)
अणु
	काष्ठा ioc_cgrp *iocc;

	iocc = kzalloc(माप(काष्ठा ioc_cgrp), gfp);
	अगर (!iocc)
		वापस शून्य;

	iocc->dfl_weight = CGROUP_WEIGHT_DFL * WEIGHT_ONE;
	वापस &iocc->cpd;
पूर्ण

अटल व्योम ioc_cpd_मुक्त(काष्ठा blkcg_policy_data *cpd)
अणु
	kमुक्त(container_of(cpd, काष्ठा ioc_cgrp, cpd));
पूर्ण

अटल काष्ठा blkg_policy_data *ioc_pd_alloc(gfp_t gfp, काष्ठा request_queue *q,
					     काष्ठा blkcg *blkcg)
अणु
	पूर्णांक levels = blkcg->css.cgroup->level + 1;
	काष्ठा ioc_gq *iocg;

	iocg = kzalloc_node(काष्ठा_size(iocg, ancestors, levels), gfp, q->node);
	अगर (!iocg)
		वापस शून्य;

	iocg->pcpu_stat = alloc_percpu_gfp(काष्ठा iocg_pcpu_stat, gfp);
	अगर (!iocg->pcpu_stat) अणु
		kमुक्त(iocg);
		वापस शून्य;
	पूर्ण

	वापस &iocg->pd;
पूर्ण

अटल व्योम ioc_pd_init(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा ioc_gq *iocg = pd_to_iocg(pd);
	काष्ठा blkcg_gq *blkg = pd_to_blkg(&iocg->pd);
	काष्ठा ioc *ioc = q_to_ioc(blkg->q);
	काष्ठा ioc_now now;
	काष्ठा blkcg_gq *tblkg;
	अचिन्हित दीर्घ flags;

	ioc_now(ioc, &now);

	iocg->ioc = ioc;
	atomic64_set(&iocg->vसमय, now.vnow);
	atomic64_set(&iocg->करोne_vसमय, now.vnow);
	atomic64_set(&iocg->active_period, atomic64_पढ़ो(&ioc->cur_period));
	INIT_LIST_HEAD(&iocg->active_list);
	INIT_LIST_HEAD(&iocg->walk_list);
	INIT_LIST_HEAD(&iocg->surplus_list);
	iocg->hweight_active = WEIGHT_ONE;
	iocg->hweight_inuse = WEIGHT_ONE;

	init_रुकोqueue_head(&iocg->रुकोq);
	hrसमयr_init(&iocg->रुकोq_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	iocg->रुकोq_समयr.function = iocg_रुकोq_समयr_fn;

	iocg->level = blkg->blkcg->css.cgroup->level;

	क्रम (tblkg = blkg; tblkg; tblkg = tblkg->parent) अणु
		काष्ठा ioc_gq *tiocg = blkg_to_iocg(tblkg);
		iocg->ancestors[tiocg->level] = tiocg;
	पूर्ण

	spin_lock_irqsave(&ioc->lock, flags);
	weight_updated(iocg, &now);
	spin_unlock_irqrestore(&ioc->lock, flags);
पूर्ण

अटल व्योम ioc_pd_मुक्त(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा ioc_gq *iocg = pd_to_iocg(pd);
	काष्ठा ioc *ioc = iocg->ioc;
	अचिन्हित दीर्घ flags;

	अगर (ioc) अणु
		spin_lock_irqsave(&ioc->lock, flags);

		अगर (!list_empty(&iocg->active_list)) अणु
			काष्ठा ioc_now now;

			ioc_now(ioc, &now);
			propagate_weights(iocg, 0, 0, false, &now);
			list_del_init(&iocg->active_list);
		पूर्ण

		WARN_ON_ONCE(!list_empty(&iocg->walk_list));
		WARN_ON_ONCE(!list_empty(&iocg->surplus_list));

		spin_unlock_irqrestore(&ioc->lock, flags);

		hrसमयr_cancel(&iocg->रुकोq_समयr);
	पूर्ण
	मुक्त_percpu(iocg->pcpu_stat);
	kमुक्त(iocg);
पूर्ण

अटल माप_प्रकार ioc_pd_stat(काष्ठा blkg_policy_data *pd, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा ioc_gq *iocg = pd_to_iocg(pd);
	काष्ठा ioc *ioc = iocg->ioc;
	माप_प्रकार pos = 0;

	अगर (!ioc->enabled)
		वापस 0;

	अगर (iocg->level == 0) अणु
		अचिन्हित vp10k = DIV64_U64_ROUND_CLOSEST(
			ioc->vसमय_base_rate * 10000,
			VTIME_PER_USEC);
		pos += scnम_लिखो(buf + pos, size - pos, " cost.vrate=%u.%02u",
				  vp10k / 100, vp10k % 100);
	पूर्ण

	pos += scnम_लिखो(buf + pos, size - pos, " cost.usage=%llu",
			 iocg->last_stat.usage_us);

	अगर (blkcg_debug_stats)
		pos += scnम_लिखो(buf + pos, size - pos,
				 " cost.wait=%llu cost.indebt=%llu cost.indelay=%llu",
				 iocg->last_stat.रुको_us,
				 iocg->last_stat.indebt_us,
				 iocg->last_stat.indelay_us);

	वापस pos;
पूर्ण

अटल u64 ioc_weight_prfill(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
			     पूर्णांक off)
अणु
	स्थिर अक्षर *dname = blkg_dev_name(pd->blkg);
	काष्ठा ioc_gq *iocg = pd_to_iocg(pd);

	अगर (dname && iocg->cfg_weight)
		seq_म_लिखो(sf, "%s %u\n", dname, iocg->cfg_weight / WEIGHT_ONE);
	वापस 0;
पूर्ण


अटल पूर्णांक ioc_weight_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(seq_css(sf));
	काष्ठा ioc_cgrp *iocc = blkcg_to_iocc(blkcg);

	seq_म_लिखो(sf, "default %u\n", iocc->dfl_weight / WEIGHT_ONE);
	blkcg_prपूर्णांक_blkgs(sf, blkcg, ioc_weight_prfill,
			  &blkcg_policy_iocost, seq_cft(sf)->निजी, false);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ioc_weight_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(of_css(of));
	काष्ठा ioc_cgrp *iocc = blkcg_to_iocc(blkcg);
	काष्ठा blkg_conf_ctx ctx;
	काष्ठा ioc_now now;
	काष्ठा ioc_gq *iocg;
	u32 v;
	पूर्णांक ret;

	अगर (!म_अक्षर(buf, ':')) अणु
		काष्ठा blkcg_gq *blkg;

		अगर (!माला_पूछो(buf, "default %u", &v) && !माला_पूछो(buf, "%u", &v))
			वापस -EINVAL;

		अगर (v < CGROUP_WEIGHT_MIN || v > CGROUP_WEIGHT_MAX)
			वापस -EINVAL;

		spin_lock(&blkcg->lock);
		iocc->dfl_weight = v * WEIGHT_ONE;
		hlist_क्रम_each_entry(blkg, &blkcg->blkg_list, blkcg_node) अणु
			काष्ठा ioc_gq *iocg = blkg_to_iocg(blkg);

			अगर (iocg) अणु
				spin_lock_irq(&iocg->ioc->lock);
				ioc_now(iocg->ioc, &now);
				weight_updated(iocg, &now);
				spin_unlock_irq(&iocg->ioc->lock);
			पूर्ण
		पूर्ण
		spin_unlock(&blkcg->lock);

		वापस nbytes;
	पूर्ण

	ret = blkg_conf_prep(blkcg, &blkcg_policy_iocost, buf, &ctx);
	अगर (ret)
		वापस ret;

	iocg = blkg_to_iocg(ctx.blkg);

	अगर (!म_भेदन(ctx.body, "default", 7)) अणु
		v = 0;
	पूर्ण अन्यथा अणु
		अगर (!माला_पूछो(ctx.body, "%u", &v))
			जाओ einval;
		अगर (v < CGROUP_WEIGHT_MIN || v > CGROUP_WEIGHT_MAX)
			जाओ einval;
	पूर्ण

	spin_lock(&iocg->ioc->lock);
	iocg->cfg_weight = v * WEIGHT_ONE;
	ioc_now(iocg->ioc, &now);
	weight_updated(iocg, &now);
	spin_unlock(&iocg->ioc->lock);

	blkg_conf_finish(&ctx);
	वापस nbytes;

einval:
	blkg_conf_finish(&ctx);
	वापस -EINVAL;
पूर्ण

अटल u64 ioc_qos_prfill(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
			  पूर्णांक off)
अणु
	स्थिर अक्षर *dname = blkg_dev_name(pd->blkg);
	काष्ठा ioc *ioc = pd_to_iocg(pd)->ioc;

	अगर (!dname)
		वापस 0;

	seq_म_लिखो(sf, "%s enable=%d ctrl=%s rpct=%u.%02u rlat=%u wpct=%u.%02u wlat=%u min=%u.%02u max=%u.%02u\n",
		   dname, ioc->enabled, ioc->user_qos_params ? "user" : "auto",
		   ioc->params.qos[QOS_RPPM] / 10000,
		   ioc->params.qos[QOS_RPPM] % 10000 / 100,
		   ioc->params.qos[QOS_RLAT],
		   ioc->params.qos[QOS_WPPM] / 10000,
		   ioc->params.qos[QOS_WPPM] % 10000 / 100,
		   ioc->params.qos[QOS_WLAT],
		   ioc->params.qos[QOS_MIN] / 10000,
		   ioc->params.qos[QOS_MIN] % 10000 / 100,
		   ioc->params.qos[QOS_MAX] / 10000,
		   ioc->params.qos[QOS_MAX] % 10000 / 100);
	वापस 0;
पूर्ण

अटल पूर्णांक ioc_qos_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(seq_css(sf));

	blkcg_prपूर्णांक_blkgs(sf, blkcg, ioc_qos_prfill,
			  &blkcg_policy_iocost, seq_cft(sf)->निजी, false);
	वापस 0;
पूर्ण

अटल स्थिर match_table_t qos_ctrl_tokens = अणु
	अणु QOS_ENABLE,		"enable=%u"	पूर्ण,
	अणु QOS_CTRL,		"ctrl=%s"	पूर्ण,
	अणु NR_QOS_CTRL_PARAMS,	शून्य		पूर्ण,
पूर्ण;

अटल स्थिर match_table_t qos_tokens = अणु
	अणु QOS_RPPM,		"rpct=%s"	पूर्ण,
	अणु QOS_RLAT,		"rlat=%u"	पूर्ण,
	अणु QOS_WPPM,		"wpct=%s"	पूर्ण,
	अणु QOS_WLAT,		"wlat=%u"	पूर्ण,
	अणु QOS_MIN,		"min=%s"	पूर्ण,
	अणु QOS_MAX,		"max=%s"	पूर्ण,
	अणु NR_QOS_PARAMS,	शून्य		पूर्ण,
पूर्ण;

अटल sमाप_प्रकार ioc_qos_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *input,
			     माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा block_device *bdev;
	काष्ठा ioc *ioc;
	u32 qos[NR_QOS_PARAMS];
	bool enable, user;
	अक्षर *p;
	पूर्णांक ret;

	bdev = blkcg_conf_खोलो_bdev(&input);
	अगर (IS_ERR(bdev))
		वापस PTR_ERR(bdev);

	ioc = q_to_ioc(bdev->bd_disk->queue);
	अगर (!ioc) अणु
		ret = blk_iocost_init(bdev->bd_disk->queue);
		अगर (ret)
			जाओ err;
		ioc = q_to_ioc(bdev->bd_disk->queue);
	पूर्ण

	spin_lock_irq(&ioc->lock);
	स_नकल(qos, ioc->params.qos, माप(qos));
	enable = ioc->enabled;
	user = ioc->user_qos_params;
	spin_unlock_irq(&ioc->lock);

	जबतक ((p = strsep(&input, " \t\n"))) अणु
		substring_t args[MAX_OPT_ARGS];
		अक्षर buf[32];
		पूर्णांक tok;
		s64 v;

		अगर (!*p)
			जारी;

		चयन (match_token(p, qos_ctrl_tokens, args)) अणु
		हाल QOS_ENABLE:
			match_u64(&args[0], &v);
			enable = v;
			जारी;
		हाल QOS_CTRL:
			match_strlcpy(buf, &args[0], माप(buf));
			अगर (!म_भेद(buf, "auto"))
				user = false;
			अन्यथा अगर (!म_भेद(buf, "user"))
				user = true;
			अन्यथा
				जाओ einval;
			जारी;
		पूर्ण

		tok = match_token(p, qos_tokens, args);
		चयन (tok) अणु
		हाल QOS_RPPM:
		हाल QOS_WPPM:
			अगर (match_strlcpy(buf, &args[0], माप(buf)) >=
			    माप(buf))
				जाओ einval;
			अगर (cgroup_parse_भग्न(buf, 2, &v))
				जाओ einval;
			अगर (v < 0 || v > 10000)
				जाओ einval;
			qos[tok] = v * 100;
			अवरोध;
		हाल QOS_RLAT:
		हाल QOS_WLAT:
			अगर (match_u64(&args[0], &v))
				जाओ einval;
			qos[tok] = v;
			अवरोध;
		हाल QOS_MIN:
		हाल QOS_MAX:
			अगर (match_strlcpy(buf, &args[0], माप(buf)) >=
			    माप(buf))
				जाओ einval;
			अगर (cgroup_parse_भग्न(buf, 2, &v))
				जाओ einval;
			अगर (v < 0)
				जाओ einval;
			qos[tok] = clamp_t(s64, v * 100,
					   VRATE_MIN_PPM, VRATE_MAX_PPM);
			अवरोध;
		शेष:
			जाओ einval;
		पूर्ण
		user = true;
	पूर्ण

	अगर (qos[QOS_MIN] > qos[QOS_MAX])
		जाओ einval;

	spin_lock_irq(&ioc->lock);

	अगर (enable) अणु
		blk_stat_enable_accounting(ioc->rqos.q);
		blk_queue_flag_set(QUEUE_FLAG_RQ_ALLOC_TIME, ioc->rqos.q);
		ioc->enabled = true;
	पूर्ण अन्यथा अणु
		blk_queue_flag_clear(QUEUE_FLAG_RQ_ALLOC_TIME, ioc->rqos.q);
		ioc->enabled = false;
	पूर्ण

	अगर (user) अणु
		स_नकल(ioc->params.qos, qos, माप(qos));
		ioc->user_qos_params = true;
	पूर्ण अन्यथा अणु
		ioc->user_qos_params = false;
	पूर्ण

	ioc_refresh_params(ioc, true);
	spin_unlock_irq(&ioc->lock);

	blkdev_put_no_खोलो(bdev);
	वापस nbytes;
einval:
	ret = -EINVAL;
err:
	blkdev_put_no_खोलो(bdev);
	वापस ret;
पूर्ण

अटल u64 ioc_cost_model_prfill(काष्ठा seq_file *sf,
				 काष्ठा blkg_policy_data *pd, पूर्णांक off)
अणु
	स्थिर अक्षर *dname = blkg_dev_name(pd->blkg);
	काष्ठा ioc *ioc = pd_to_iocg(pd)->ioc;
	u64 *u = ioc->params.i_lcoefs;

	अगर (!dname)
		वापस 0;

	seq_म_लिखो(sf, "%s ctrl=%s model=linear "
		   "rbps=%llu rseqiops=%llu rrandiops=%llu "
		   "wbps=%llu wseqiops=%llu wrandiops=%llu\n",
		   dname, ioc->user_cost_model ? "user" : "auto",
		   u[I_LCOEF_RBPS], u[I_LCOEF_RSEQIOPS], u[I_LCOEF_RRANDIOPS],
		   u[I_LCOEF_WBPS], u[I_LCOEF_WSEQIOPS], u[I_LCOEF_WRANDIOPS]);
	वापस 0;
पूर्ण

अटल पूर्णांक ioc_cost_model_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(seq_css(sf));

	blkcg_prपूर्णांक_blkgs(sf, blkcg, ioc_cost_model_prfill,
			  &blkcg_policy_iocost, seq_cft(sf)->निजी, false);
	वापस 0;
पूर्ण

अटल स्थिर match_table_t cost_ctrl_tokens = अणु
	अणु COST_CTRL,		"ctrl=%s"	पूर्ण,
	अणु COST_MODEL,		"model=%s"	पूर्ण,
	अणु NR_COST_CTRL_PARAMS,	शून्य		पूर्ण,
पूर्ण;

अटल स्थिर match_table_t i_lcoef_tokens = अणु
	अणु I_LCOEF_RBPS,		"rbps=%u"	पूर्ण,
	अणु I_LCOEF_RSEQIOPS,	"rseqiops=%u"	पूर्ण,
	अणु I_LCOEF_RRANDIOPS,	"rrandiops=%u"	पूर्ण,
	अणु I_LCOEF_WBPS,		"wbps=%u"	पूर्ण,
	अणु I_LCOEF_WSEQIOPS,	"wseqiops=%u"	पूर्ण,
	अणु I_LCOEF_WRANDIOPS,	"wrandiops=%u"	पूर्ण,
	अणु NR_I_LCOEFS,		शून्य		पूर्ण,
पूर्ण;

अटल sमाप_प्रकार ioc_cost_model_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *input,
				    माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा block_device *bdev;
	काष्ठा ioc *ioc;
	u64 u[NR_I_LCOEFS];
	bool user;
	अक्षर *p;
	पूर्णांक ret;

	bdev = blkcg_conf_खोलो_bdev(&input);
	अगर (IS_ERR(bdev))
		वापस PTR_ERR(bdev);

	ioc = q_to_ioc(bdev->bd_disk->queue);
	अगर (!ioc) अणु
		ret = blk_iocost_init(bdev->bd_disk->queue);
		अगर (ret)
			जाओ err;
		ioc = q_to_ioc(bdev->bd_disk->queue);
	पूर्ण

	spin_lock_irq(&ioc->lock);
	स_नकल(u, ioc->params.i_lcoefs, माप(u));
	user = ioc->user_cost_model;
	spin_unlock_irq(&ioc->lock);

	जबतक ((p = strsep(&input, " \t\n"))) अणु
		substring_t args[MAX_OPT_ARGS];
		अक्षर buf[32];
		पूर्णांक tok;
		u64 v;

		अगर (!*p)
			जारी;

		चयन (match_token(p, cost_ctrl_tokens, args)) अणु
		हाल COST_CTRL:
			match_strlcpy(buf, &args[0], माप(buf));
			अगर (!म_भेद(buf, "auto"))
				user = false;
			अन्यथा अगर (!म_भेद(buf, "user"))
				user = true;
			अन्यथा
				जाओ einval;
			जारी;
		हाल COST_MODEL:
			match_strlcpy(buf, &args[0], माप(buf));
			अगर (म_भेद(buf, "linear"))
				जाओ einval;
			जारी;
		पूर्ण

		tok = match_token(p, i_lcoef_tokens, args);
		अगर (tok == NR_I_LCOEFS)
			जाओ einval;
		अगर (match_u64(&args[0], &v))
			जाओ einval;
		u[tok] = v;
		user = true;
	पूर्ण

	spin_lock_irq(&ioc->lock);
	अगर (user) अणु
		स_नकल(ioc->params.i_lcoefs, u, माप(u));
		ioc->user_cost_model = true;
	पूर्ण अन्यथा अणु
		ioc->user_cost_model = false;
	पूर्ण
	ioc_refresh_params(ioc, true);
	spin_unlock_irq(&ioc->lock);

	blkdev_put_no_खोलो(bdev);
	वापस nbytes;

einval:
	ret = -EINVAL;
err:
	blkdev_put_no_खोलो(bdev);
	वापस ret;
पूर्ण

अटल काष्ठा cftype ioc_files[] = अणु
	अणु
		.name = "weight",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = ioc_weight_show,
		.ग_लिखो = ioc_weight_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cost.qos",
		.flags = CFTYPE_ONLY_ON_ROOT,
		.seq_show = ioc_qos_show,
		.ग_लिखो = ioc_qos_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cost.model",
		.flags = CFTYPE_ONLY_ON_ROOT,
		.seq_show = ioc_cost_model_show,
		.ग_लिखो = ioc_cost_model_ग_लिखो,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा blkcg_policy blkcg_policy_iocost = अणु
	.dfl_cftypes	= ioc_files,
	.cpd_alloc_fn	= ioc_cpd_alloc,
	.cpd_मुक्त_fn	= ioc_cpd_मुक्त,
	.pd_alloc_fn	= ioc_pd_alloc,
	.pd_init_fn	= ioc_pd_init,
	.pd_मुक्त_fn	= ioc_pd_मुक्त,
	.pd_stat_fn	= ioc_pd_stat,
पूर्ण;

अटल पूर्णांक __init ioc_init(व्योम)
अणु
	वापस blkcg_policy_रेजिस्टर(&blkcg_policy_iocost);
पूर्ण

अटल व्योम __निकास ioc_निकास(व्योम)
अणु
	blkcg_policy_unरेजिस्टर(&blkcg_policy_iocost);
पूर्ण

module_init(ioc_init);
module_निकास(ioc_निकास);
