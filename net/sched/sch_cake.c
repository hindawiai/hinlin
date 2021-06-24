<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause

/* COMMON Applications Kept Enhanced (CAKE) discipline
 *
 * Copyright (C) 2014-2018 Jonathan Morton <chromatix99@gmail.com>
 * Copyright (C) 2015-2018 Toke Hथचiland-Jथचrgensen <toke@toke.dk>
 * Copyright (C) 2014-2018 Dave Tथअht <dave.taht@gmail.com>
 * Copyright (C) 2015-2018 Sebastian Moeller <moeller0@gmx.de>
 * (C) 2015-2018 Kevin Darbyshire-Bryant <kevin@darbyshire-bryant.me.uk>
 * Copyright (C) 2017-2018 Ryan Mounce <ryan@mounce.com.au>
 *
 * The CAKE Principles:
 *		   (or, how to have your cake and eat it too)
 *
 * This is a combination of several shaping, AQM and FQ techniques पूर्णांकo one
 * easy-to-use package:
 *
 * - An overall bandwidth shaper, to move the bottleneck away from dumb CPE
 *   equipment and bloated MACs.  This operates in deficit mode (as in sch_fq),
 *   eliminating the need क्रम any sort of burst parameter (eg. token bucket
 *   depth).  Burst support is limited to that necessary to overcome scheduling
 *   latency.
 *
 * - A Dअगरfserv-aware priority queue, giving more priority to certain classes,
 *   up to a specअगरied fraction of bandwidth.  Above that bandwidth threshold,
 *   the priority is reduced to aव्योम starving other tins.
 *
 * - Each priority tin has a separate Flow Queue प्रणाली, to isolate traffic
 *   flows from each other.  This prevents a burst on one flow from increasing
 *   the delay to another.  Flows are distributed to queues using a
 *   set-associative hash function.
 *
 * - Each queue is actively managed by Cobalt, which is a combination of the
 *   Codel and Blue AQM algorithms.  This serves flows fairly, and संकेतs
 *   congestion early via ECN (अगर available) and/or packet drops, to keep
 *   latency low.  The codel parameters are स्वतः-tuned based on the bandwidth
 *   setting, as is necessary at low bandwidths.
 *
 * The configuration parameters are kept deliberately simple क्रम ease of use.
 * Everything has sane शेषs.  Complete generality of configuration is *not*
 * a goal.
 *
 * The priority queue operates according to a weighted DRR scheme, combined with
 * a bandwidth tracker which reuses the shaper logic to detect which side of the
 * bandwidth sharing threshold the tin is operating.  This determines whether a
 * priority-based weight (high) or a bandwidth-based weight (low) is used क्रम
 * that tin in the current pass.
 *
 * This qdisc was inspired by Eric Dumazet's fq_codel code, which he kindly
 * granted us permission to leverage.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/jhash.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/reciprocal_भाग.h>
#समावेश <net/netlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tcp.h>
#समावेश <net/flow_dissector.h>

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack_core.h>
#पूर्ण_अगर

#घोषणा CAKE_SET_WAYS (8)
#घोषणा CAKE_MAX_TINS (8)
#घोषणा CAKE_QUEUES (1024)
#घोषणा CAKE_FLOW_MASK 63
#घोषणा CAKE_FLOW_NAT_FLAG 64

/* काष्ठा cobalt_params - contains codel and blue parameters
 * @पूर्णांकerval:	codel initial drop rate
 * @target:     maximum persistent sojourn समय & blue update rate
 * @mtu_समय:   serialisation delay of maximum-size packet
 * @p_inc:      increment of blue drop probability (0.32 fxp)
 * @p_dec:      decrement of blue drop probability (0.32 fxp)
 */
काष्ठा cobalt_params अणु
	u64	पूर्णांकerval;
	u64	target;
	u64	mtu_समय;
	u32	p_inc;
	u32	p_dec;
पूर्ण;

/* काष्ठा cobalt_vars - contains codel and blue variables
 * @count:		codel dropping frequency
 * @rec_inv_वर्ग_मूल:	reciprocal value of वर्ग_मूल(count) >> 1
 * @drop_next:		समय to drop next packet, or when we dropped last
 * @blue_समयr:		Blue समय to next drop
 * @p_drop:		BLUE drop probability (0.32 fxp)
 * @dropping:		set अगर in dropping state
 * @ecn_marked:		set अगर marked
 */
काष्ठा cobalt_vars अणु
	u32	count;
	u32	rec_inv_वर्ग_मूल;
	kसमय_प्रकार	drop_next;
	kसमय_प्रकार	blue_समयr;
	u32     p_drop;
	bool	dropping;
	bool    ecn_marked;
पूर्ण;

क्रमागत अणु
	CAKE_SET_NONE = 0,
	CAKE_SET_SPARSE,
	CAKE_SET_SPARSE_WAIT, /* counted in SPARSE, actually in BULK */
	CAKE_SET_BULK,
	CAKE_SET_DECAYING
पूर्ण;

काष्ठा cake_flow अणु
	/* this stuff is all needed per-flow at dequeue समय */
	काष्ठा sk_buff	  *head;
	काष्ठा sk_buff	  *tail;
	काष्ठा list_head  flowchain;
	s32		  deficit;
	u32		  dropped;
	काष्ठा cobalt_vars cvars;
	u16		  srchost; /* index पूर्णांकo cake_host table */
	u16		  dsthost;
	u8		  set;
पूर्ण; /* please try to keep this काष्ठाure <= 64 bytes */

काष्ठा cake_host अणु
	u32 srchost_tag;
	u32 dsthost_tag;
	u16 srchost_bulk_flow_count;
	u16 dsthost_bulk_flow_count;
पूर्ण;

काष्ठा cake_heap_entry अणु
	u16 t:3, b:10;
पूर्ण;

काष्ठा cake_tin_data अणु
	काष्ठा cake_flow flows[CAKE_QUEUES];
	u32	backlogs[CAKE_QUEUES];
	u32	tags[CAKE_QUEUES]; /* क्रम set association */
	u16	overflow_idx[CAKE_QUEUES];
	काष्ठा cake_host hosts[CAKE_QUEUES]; /* क्रम triple isolation */
	u16	flow_quantum;

	काष्ठा cobalt_params cparams;
	u32	drop_overlimit;
	u16	bulk_flow_count;
	u16	sparse_flow_count;
	u16	decaying_flow_count;
	u16	unresponsive_flow_count;

	u32	max_skblen;

	काष्ठा list_head new_flows;
	काष्ठा list_head old_flows;
	काष्ठा list_head decaying_flows;

	/* समय_next = समय_प्रकारhis + ((len * rate_ns) >> rate_shft) */
	kसमय_प्रकार	समय_next_packet;
	u64	tin_rate_ns;
	u64	tin_rate_bps;
	u16	tin_rate_shft;

	u16	tin_quantum;
	s32	tin_deficit;
	u32	tin_backlog;
	u32	tin_dropped;
	u32	tin_ecn_mark;

	u32	packets;
	u64	bytes;

	u32	ack_drops;

	/* moving averages */
	u64 avge_delay;
	u64 peak_delay;
	u64 base_delay;

	/* hash function stats */
	u32	way_directs;
	u32	way_hits;
	u32	way_misses;
	u32	way_collisions;
पूर्ण; /* number of tins is small, so size of this काष्ठा करोesn't matter much */

काष्ठा cake_sched_data अणु
	काष्ठा tcf_proto __rcu *filter_list; /* optional बाह्यal classअगरier */
	काष्ठा tcf_block *block;
	काष्ठा cake_tin_data *tins;

	काष्ठा cake_heap_entry overflow_heap[CAKE_QUEUES * CAKE_MAX_TINS];
	u16		overflow_समयout;

	u16		tin_cnt;
	u8		tin_mode;
	u8		flow_mode;
	u8		ack_filter;
	u8		aपंचांग_mode;

	u32		fwmark_mask;
	u16		fwmark_shft;

	/* समय_next = समय_प्रकारhis + ((len * rate_ns) >> rate_shft) */
	u16		rate_shft;
	kसमय_प्रकार		समय_next_packet;
	kसमय_प्रकार		failsafe_next_packet;
	u64		rate_ns;
	u64		rate_bps;
	u16		rate_flags;
	s16		rate_overhead;
	u16		rate_mpu;
	u64		पूर्णांकerval;
	u64		target;

	/* resource tracking */
	u32		buffer_used;
	u32		buffer_max_used;
	u32		buffer_limit;
	u32		buffer_config_limit;

	/* indices क्रम dequeue */
	u16		cur_tin;
	u16		cur_flow;

	काष्ठा qdisc_watchकरोg watchकरोg;
	स्थिर u8	*tin_index;
	स्थिर u8	*tin_order;

	/* bandwidth capacity estimate */
	kसमय_प्रकार		last_packet_समय;
	kसमय_प्रकार		avg_winकरोw_begin;
	u64		avg_packet_पूर्णांकerval;
	u64		avg_winकरोw_bytes;
	u64		avg_peak_bandwidth;
	kसमय_प्रकार		last_reconfig_समय;

	/* packet length stats */
	u32		avg_netoff;
	u16		max_netlen;
	u16		max_adjlen;
	u16		min_netlen;
	u16		min_adjlen;
पूर्ण;

क्रमागत अणु
	CAKE_FLAG_OVERHEAD	   = BIT(0),
	CAKE_FLAG_AUTORATE_INGRESS = BIT(1),
	CAKE_FLAG_INGRESS	   = BIT(2),
	CAKE_FLAG_WASH		   = BIT(3),
	CAKE_FLAG_SPLIT_GSO	   = BIT(4)
पूर्ण;

/* COBALT operates the Codel and BLUE algorithms in parallel, in order to
 * obtain the best features of each.  Codel is excellent on flows which
 * respond to congestion संकेतs in a TCP-like way.  BLUE is more effective on
 * unresponsive flows.
 */

काष्ठा cobalt_skb_cb अणु
	kसमय_प्रकार enqueue_समय;
	u32     adjusted_len;
पूर्ण;

अटल u64 us_to_ns(u64 us)
अणु
	वापस us * NSEC_PER_USEC;
पूर्ण

अटल काष्ठा cobalt_skb_cb *get_cobalt_cb(स्थिर काष्ठा sk_buff *skb)
अणु
	qdisc_cb_निजी_validate(skb, माप(काष्ठा cobalt_skb_cb));
	वापस (काष्ठा cobalt_skb_cb *)qdisc_skb_cb(skb)->data;
पूर्ण

अटल kसमय_प्रकार cobalt_get_enqueue_समय(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस get_cobalt_cb(skb)->enqueue_समय;
पूर्ण

अटल व्योम cobalt_set_enqueue_समय(काष्ठा sk_buff *skb,
				    kसमय_प्रकार now)
अणु
	get_cobalt_cb(skb)->enqueue_समय = now;
पूर्ण

अटल u16 quantum_भाग[CAKE_QUEUES + 1] = अणु0पूर्ण;

/* Dअगरfserv lookup tables */

अटल स्थिर u8 precedence[] = अणु
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7,
पूर्ण;

अटल स्थिर u8 dअगरfserv8[] = अणु
	2, 0, 1, 2, 4, 2, 2, 2,
	1, 2, 1, 2, 1, 2, 1, 2,
	5, 2, 4, 2, 4, 2, 4, 2,
	3, 2, 3, 2, 3, 2, 3, 2,
	6, 2, 3, 2, 3, 2, 3, 2,
	6, 2, 2, 2, 6, 2, 6, 2,
	7, 2, 2, 2, 2, 2, 2, 2,
	7, 2, 2, 2, 2, 2, 2, 2,
पूर्ण;

अटल स्थिर u8 dअगरfserv4[] = अणु
	0, 1, 0, 0, 2, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	2, 0, 2, 0, 2, 0, 2, 0,
	2, 0, 2, 0, 2, 0, 2, 0,
	3, 0, 2, 0, 2, 0, 2, 0,
	3, 0, 0, 0, 3, 0, 3, 0,
	3, 0, 0, 0, 0, 0, 0, 0,
	3, 0, 0, 0, 0, 0, 0, 0,
पूर्ण;

अटल स्थिर u8 dअगरfserv3[] = अणु
	0, 1, 0, 0, 2, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 2, 0, 2, 0,
	2, 0, 0, 0, 0, 0, 0, 0,
	2, 0, 0, 0, 0, 0, 0, 0,
पूर्ण;

अटल स्थिर u8 bestefक्रमt[] = अणु
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
पूर्ण;

/* tin priority order क्रम stats dumping */

अटल स्थिर u8 normal_order[] = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण;
अटल स्थिर u8 bulk_order[] = अणु1, 0, 2, 3पूर्ण;

#घोषणा REC_INV_SQRT_CACHE (16)
अटल u32 cobalt_rec_inv_वर्ग_मूल_cache[REC_INV_SQRT_CACHE] = अणु0पूर्ण;

/* http://en.wikipedia.org/wiki/Methods_of_computing_square_roots
 * new_invवर्ग_मूल = (invवर्ग_मूल / 2) * (3 - count * invवर्ग_मूल^2)
 *
 * Here, invवर्ग_मूल is a fixed poपूर्णांक number (< 1.0), 32bit mantissa, aka Q0.32
 */

अटल व्योम cobalt_newton_step(काष्ठा cobalt_vars *vars)
अणु
	u32 invवर्ग_मूल, invवर्ग_मूल2;
	u64 val;

	invवर्ग_मूल = vars->rec_inv_वर्ग_मूल;
	invवर्ग_मूल2 = ((u64)invवर्ग_मूल * invवर्ग_मूल) >> 32;
	val = (3LL << 32) - ((u64)vars->count * invवर्ग_मूल2);

	val >>= 2; /* aव्योम overflow in following multiply */
	val = (val * invवर्ग_मूल) >> (32 - 2 + 1);

	vars->rec_inv_वर्ग_मूल = val;
पूर्ण

अटल व्योम cobalt_invवर्ग_मूल(काष्ठा cobalt_vars *vars)
अणु
	अगर (vars->count < REC_INV_SQRT_CACHE)
		vars->rec_inv_वर्ग_मूल = cobalt_rec_inv_वर्ग_मूल_cache[vars->count];
	अन्यथा
		cobalt_newton_step(vars);
पूर्ण

/* There is a big dअगरference in timing between the accurate values placed in
 * the cache and the approximations given by a single Newton step क्रम small
 * count values, particularly when stepping from count 1 to 2 or vice versa.
 * Above 16, a single Newton step gives sufficient accuracy in either
 * direction, given the precision stored.
 *
 * The magnitude of the error when stepping up to count 2 is such as to give
 * the value that *should* have been produced at count 4.
 */

अटल व्योम cobalt_cache_init(व्योम)
अणु
	काष्ठा cobalt_vars v;

	स_रखो(&v, 0, माप(v));
	v.rec_inv_वर्ग_मूल = ~0U;
	cobalt_rec_inv_वर्ग_मूल_cache[0] = v.rec_inv_वर्ग_मूल;

	क्रम (v.count = 1; v.count < REC_INV_SQRT_CACHE; v.count++) अणु
		cobalt_newton_step(&v);
		cobalt_newton_step(&v);
		cobalt_newton_step(&v);
		cobalt_newton_step(&v);

		cobalt_rec_inv_वर्ग_मूल_cache[v.count] = v.rec_inv_वर्ग_मूल;
	पूर्ण
पूर्ण

अटल व्योम cobalt_vars_init(काष्ठा cobalt_vars *vars)
अणु
	स_रखो(vars, 0, माप(*vars));

	अगर (!cobalt_rec_inv_वर्ग_मूल_cache[0]) अणु
		cobalt_cache_init();
		cobalt_rec_inv_वर्ग_मूल_cache[0] = ~0;
	पूर्ण
पूर्ण

/* CoDel control_law is t + पूर्णांकerval/वर्ग_मूल(count)
 * We मुख्यtain in rec_inv_वर्ग_मूल the reciprocal value of वर्ग_मूल(count) to aव्योम
 * both वर्ग_मूल() and भागide operation.
 */
अटल kसमय_प्रकार cobalt_control(kसमय_प्रकार t,
			      u64 पूर्णांकerval,
			      u32 rec_inv_वर्ग_मूल)
अणु
	वापस kसमय_add_ns(t, reciprocal_scale(पूर्णांकerval,
						rec_inv_वर्ग_मूल));
पूर्ण

/* Call this when a packet had to be dropped due to queue overflow.  Returns
 * true अगर the BLUE state was quiescent beक्रमe but active after this call.
 */
अटल bool cobalt_queue_full(काष्ठा cobalt_vars *vars,
			      काष्ठा cobalt_params *p,
			      kसमय_प्रकार now)
अणु
	bool up = false;

	अगर (kसमय_प्रकारo_ns(kसमय_sub(now, vars->blue_समयr)) > p->target) अणु
		up = !vars->p_drop;
		vars->p_drop += p->p_inc;
		अगर (vars->p_drop < p->p_inc)
			vars->p_drop = ~0;
		vars->blue_समयr = now;
	पूर्ण
	vars->dropping = true;
	vars->drop_next = now;
	अगर (!vars->count)
		vars->count = 1;

	वापस up;
पूर्ण

/* Call this when the queue was serviced but turned out to be empty.  Returns
 * true अगर the BLUE state was active beक्रमe but quiescent after this call.
 */
अटल bool cobalt_queue_empty(काष्ठा cobalt_vars *vars,
			       काष्ठा cobalt_params *p,
			       kसमय_प्रकार now)
अणु
	bool करोwn = false;

	अगर (vars->p_drop &&
	    kसमय_प्रकारo_ns(kसमय_sub(now, vars->blue_समयr)) > p->target) अणु
		अगर (vars->p_drop < p->p_dec)
			vars->p_drop = 0;
		अन्यथा
			vars->p_drop -= p->p_dec;
		vars->blue_समयr = now;
		करोwn = !vars->p_drop;
	पूर्ण
	vars->dropping = false;

	अगर (vars->count && kसमय_प्रकारo_ns(kसमय_sub(now, vars->drop_next)) >= 0) अणु
		vars->count--;
		cobalt_invवर्ग_मूल(vars);
		vars->drop_next = cobalt_control(vars->drop_next,
						 p->पूर्णांकerval,
						 vars->rec_inv_वर्ग_मूल);
	पूर्ण

	वापस करोwn;
पूर्ण

/* Call this with a freshly dequeued packet क्रम possible congestion marking.
 * Returns true as an inकाष्ठाion to drop the packet, false क्रम delivery.
 */
अटल bool cobalt_should_drop(काष्ठा cobalt_vars *vars,
			       काष्ठा cobalt_params *p,
			       kसमय_प्रकार now,
			       काष्ठा sk_buff *skb,
			       u32 bulk_flows)
अणु
	bool next_due, over_target, drop = false;
	kसमय_प्रकार schedule;
	u64 sojourn;

/* The 'schedule' variable records, in its sign, whether 'now' is beक्रमe or
 * after 'drop_next'.  This allows 'drop_next' to be updated beक्रमe the next
 * scheduling decision is actually branched, without destroying that
 * inक्रमmation.  Similarly, the first 'schedule' value calculated is preserved
 * in the boolean 'next_due'.
 *
 * As क्रम 'drop_next', we take advantage of the fact that 'interval' is both
 * the delay between first exceeding 'target' and the first संकेतling event,
 * *and* the scaling factor क्रम the संकेतling frequency.  It's thereक्रमe very
 * natural to use a single mechanism क्रम both purposes, and eliminates a
 * signअगरicant amount of reference Codel's spaghetti code.  To help with this,
 * both the '0' and '1' entries in the invवर्ग_मूल cache are 0xFFFFFFFF, as बंद
 * as possible to 1.0 in fixed-poपूर्णांक.
 */

	sojourn = kसमय_प्रकारo_ns(kसमय_sub(now, cobalt_get_enqueue_समय(skb)));
	schedule = kसमय_sub(now, vars->drop_next);
	over_target = sojourn > p->target &&
		      sojourn > p->mtu_समय * bulk_flows * 2 &&
		      sojourn > p->mtu_समय * 4;
	next_due = vars->count && kसमय_प्रकारo_ns(schedule) >= 0;

	vars->ecn_marked = false;

	अगर (over_target) अणु
		अगर (!vars->dropping) अणु
			vars->dropping = true;
			vars->drop_next = cobalt_control(now,
							 p->पूर्णांकerval,
							 vars->rec_inv_वर्ग_मूल);
		पूर्ण
		अगर (!vars->count)
			vars->count = 1;
	पूर्ण अन्यथा अगर (vars->dropping) अणु
		vars->dropping = false;
	पूर्ण

	अगर (next_due && vars->dropping) अणु
		/* Use ECN mark अगर possible, otherwise drop */
		drop = !(vars->ecn_marked = INET_ECN_set_ce(skb));

		vars->count++;
		अगर (!vars->count)
			vars->count--;
		cobalt_invवर्ग_मूल(vars);
		vars->drop_next = cobalt_control(vars->drop_next,
						 p->पूर्णांकerval,
						 vars->rec_inv_वर्ग_मूल);
		schedule = kसमय_sub(now, vars->drop_next);
	पूर्ण अन्यथा अणु
		जबतक (next_due) अणु
			vars->count--;
			cobalt_invवर्ग_मूल(vars);
			vars->drop_next = cobalt_control(vars->drop_next,
							 p->पूर्णांकerval,
							 vars->rec_inv_वर्ग_मूल);
			schedule = kसमय_sub(now, vars->drop_next);
			next_due = vars->count && kसमय_प्रकारo_ns(schedule) >= 0;
		पूर्ण
	पूर्ण

	/* Simple BLUE implementation.  Lack of ECN is deliberate. */
	अगर (vars->p_drop)
		drop |= (pअक्रमom_u32() < vars->p_drop);

	/* Overload the drop_next field as an activity समयout */
	अगर (!vars->count)
		vars->drop_next = kसमय_add_ns(now, p->पूर्णांकerval);
	अन्यथा अगर (kसमय_प्रकारo_ns(schedule) > 0 && !drop)
		vars->drop_next = now;

	वापस drop;
पूर्ण

अटल bool cake_update_flowkeys(काष्ठा flow_keys *keys,
				 स्थिर काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	काष्ठा nf_conntrack_tuple tuple = अणुपूर्ण;
	bool rev = !skb->_nfct, upd = false;
	__be32 ip;

	अगर (skb_protocol(skb, true) != htons(ETH_P_IP))
		वापस false;

	अगर (!nf_ct_get_tuple_skb(&tuple, skb))
		वापस false;

	ip = rev ? tuple.dst.u3.ip : tuple.src.u3.ip;
	अगर (ip != keys->addrs.v4addrs.src) अणु
		keys->addrs.v4addrs.src = ip;
		upd = true;
	पूर्ण
	ip = rev ? tuple.src.u3.ip : tuple.dst.u3.ip;
	अगर (ip != keys->addrs.v4addrs.dst) अणु
		keys->addrs.v4addrs.dst = ip;
		upd = true;
	पूर्ण

	अगर (keys->ports.ports) अणु
		__be16 port;

		port = rev ? tuple.dst.u.all : tuple.src.u.all;
		अगर (port != keys->ports.src) अणु
			keys->ports.src = port;
			upd = true;
		पूर्ण
		port = rev ? tuple.src.u.all : tuple.dst.u.all;
		अगर (port != keys->ports.dst) अणु
			port = keys->ports.dst;
			upd = true;
		पूर्ण
	पूर्ण
	वापस upd;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/* Cake has several subtle multiple bit settings. In these हालs you
 *  would be matching triple isolate mode as well.
 */

अटल bool cake_dsrc(पूर्णांक flow_mode)
अणु
	वापस (flow_mode & CAKE_FLOW_DUAL_SRC) == CAKE_FLOW_DUAL_SRC;
पूर्ण

अटल bool cake_ddst(पूर्णांक flow_mode)
अणु
	वापस (flow_mode & CAKE_FLOW_DUAL_DST) == CAKE_FLOW_DUAL_DST;
पूर्ण

अटल u32 cake_hash(काष्ठा cake_tin_data *q, स्थिर काष्ठा sk_buff *skb,
		     पूर्णांक flow_mode, u16 flow_override, u16 host_override)
अणु
	bool hash_flows = (!flow_override && !!(flow_mode & CAKE_FLOW_FLOWS));
	bool hash_hosts = (!host_override && !!(flow_mode & CAKE_FLOW_HOSTS));
	bool nat_enabled = !!(flow_mode & CAKE_FLOW_NAT_FLAG);
	u32 flow_hash = 0, srchost_hash = 0, dsthost_hash = 0;
	u16 reduced_hash, srchost_idx, dsthost_idx;
	काष्ठा flow_keys keys, host_keys;
	bool use_skbhash = skb->l4_hash;

	अगर (unlikely(flow_mode == CAKE_FLOW_NONE))
		वापस 0;

	/* If both overrides are set, or we can use the SKB hash and nat mode is
	 * disabled, we can skip packet dissection entirely. If nat mode is
	 * enabled there's another check below after करोing the conntrack lookup.
	 */
	अगर ((!hash_flows || (use_skbhash && !nat_enabled)) && !hash_hosts)
		जाओ skip_hash;

	skb_flow_dissect_flow_keys(skb, &keys,
				   FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL);

	/* Don't use the SKB hash अगर we change the lookup keys from conntrack */
	अगर (nat_enabled && cake_update_flowkeys(&keys, skb))
		use_skbhash = false;

	/* If we can still use the SKB hash and करोn't need the host hash, we can
	 * skip the rest of the hashing procedure
	 */
	अगर (use_skbhash && !hash_hosts)
		जाओ skip_hash;

	/* flow_hash_from_keys() sorts the addresses by value, so we have
	 * to preserve their order in a separate data काष्ठाure to treat
	 * src and dst host addresses as independently selectable.
	 */
	host_keys = keys;
	host_keys.ports.ports     = 0;
	host_keys.basic.ip_proto  = 0;
	host_keys.keyid.keyid     = 0;
	host_keys.tags.flow_label = 0;

	चयन (host_keys.control.addr_type) अणु
	हाल FLOW_DISSECTOR_KEY_IPV4_ADDRS:
		host_keys.addrs.v4addrs.src = 0;
		dsthost_hash = flow_hash_from_keys(&host_keys);
		host_keys.addrs.v4addrs.src = keys.addrs.v4addrs.src;
		host_keys.addrs.v4addrs.dst = 0;
		srchost_hash = flow_hash_from_keys(&host_keys);
		अवरोध;

	हाल FLOW_DISSECTOR_KEY_IPV6_ADDRS:
		स_रखो(&host_keys.addrs.v6addrs.src, 0,
		       माप(host_keys.addrs.v6addrs.src));
		dsthost_hash = flow_hash_from_keys(&host_keys);
		host_keys.addrs.v6addrs.src = keys.addrs.v6addrs.src;
		स_रखो(&host_keys.addrs.v6addrs.dst, 0,
		       माप(host_keys.addrs.v6addrs.dst));
		srchost_hash = flow_hash_from_keys(&host_keys);
		अवरोध;

	शेष:
		dsthost_hash = 0;
		srchost_hash = 0;
	पूर्ण

	/* This *must* be after the above चयन, since as a
	 * side-effect it sorts the src and dst addresses.
	 */
	अगर (hash_flows && !use_skbhash)
		flow_hash = flow_hash_from_keys(&keys);

skip_hash:
	अगर (flow_override)
		flow_hash = flow_override - 1;
	अन्यथा अगर (use_skbhash)
		flow_hash = skb->hash;
	अगर (host_override) अणु
		dsthost_hash = host_override - 1;
		srchost_hash = host_override - 1;
	पूर्ण

	अगर (!(flow_mode & CAKE_FLOW_FLOWS)) अणु
		अगर (flow_mode & CAKE_FLOW_SRC_IP)
			flow_hash ^= srchost_hash;

		अगर (flow_mode & CAKE_FLOW_DST_IP)
			flow_hash ^= dsthost_hash;
	पूर्ण

	reduced_hash = flow_hash % CAKE_QUEUES;

	/* set-associative hashing */
	/* fast path अगर no hash collision (direct lookup succeeds) */
	अगर (likely(q->tags[reduced_hash] == flow_hash &&
		   q->flows[reduced_hash].set)) अणु
		q->way_directs++;
	पूर्ण अन्यथा अणु
		u32 inner_hash = reduced_hash % CAKE_SET_WAYS;
		u32 outer_hash = reduced_hash - inner_hash;
		bool allocate_src = false;
		bool allocate_dst = false;
		u32 i, k;

		/* check अगर any active queue in the set is reserved क्रम
		 * this flow.
		 */
		क्रम (i = 0, k = inner_hash; i < CAKE_SET_WAYS;
		     i++, k = (k + 1) % CAKE_SET_WAYS) अणु
			अगर (q->tags[outer_hash + k] == flow_hash) अणु
				अगर (i)
					q->way_hits++;

				अगर (!q->flows[outer_hash + k].set) अणु
					/* need to increment host refcnts */
					allocate_src = cake_dsrc(flow_mode);
					allocate_dst = cake_ddst(flow_mode);
				पूर्ण

				जाओ found;
			पूर्ण
		पूर्ण

		/* no queue is reserved क्रम this flow, look क्रम an
		 * empty one.
		 */
		क्रम (i = 0; i < CAKE_SET_WAYS;
			 i++, k = (k + 1) % CAKE_SET_WAYS) अणु
			अगर (!q->flows[outer_hash + k].set) अणु
				q->way_misses++;
				allocate_src = cake_dsrc(flow_mode);
				allocate_dst = cake_ddst(flow_mode);
				जाओ found;
			पूर्ण
		पूर्ण

		/* With no empty queues, शेष to the original
		 * queue, accept the collision, update the host tags.
		 */
		q->way_collisions++;
		अगर (q->flows[outer_hash + k].set == CAKE_SET_BULK) अणु
			q->hosts[q->flows[reduced_hash].srchost].srchost_bulk_flow_count--;
			q->hosts[q->flows[reduced_hash].dsthost].dsthost_bulk_flow_count--;
		पूर्ण
		allocate_src = cake_dsrc(flow_mode);
		allocate_dst = cake_ddst(flow_mode);
found:
		/* reserve queue क्रम future packets in same flow */
		reduced_hash = outer_hash + k;
		q->tags[reduced_hash] = flow_hash;

		अगर (allocate_src) अणु
			srchost_idx = srchost_hash % CAKE_QUEUES;
			inner_hash = srchost_idx % CAKE_SET_WAYS;
			outer_hash = srchost_idx - inner_hash;
			क्रम (i = 0, k = inner_hash; i < CAKE_SET_WAYS;
				i++, k = (k + 1) % CAKE_SET_WAYS) अणु
				अगर (q->hosts[outer_hash + k].srchost_tag ==
				    srchost_hash)
					जाओ found_src;
			पूर्ण
			क्रम (i = 0; i < CAKE_SET_WAYS;
				i++, k = (k + 1) % CAKE_SET_WAYS) अणु
				अगर (!q->hosts[outer_hash + k].srchost_bulk_flow_count)
					अवरोध;
			पूर्ण
			q->hosts[outer_hash + k].srchost_tag = srchost_hash;
found_src:
			srchost_idx = outer_hash + k;
			अगर (q->flows[reduced_hash].set == CAKE_SET_BULK)
				q->hosts[srchost_idx].srchost_bulk_flow_count++;
			q->flows[reduced_hash].srchost = srchost_idx;
		पूर्ण

		अगर (allocate_dst) अणु
			dsthost_idx = dsthost_hash % CAKE_QUEUES;
			inner_hash = dsthost_idx % CAKE_SET_WAYS;
			outer_hash = dsthost_idx - inner_hash;
			क्रम (i = 0, k = inner_hash; i < CAKE_SET_WAYS;
			     i++, k = (k + 1) % CAKE_SET_WAYS) अणु
				अगर (q->hosts[outer_hash + k].dsthost_tag ==
				    dsthost_hash)
					जाओ found_dst;
			पूर्ण
			क्रम (i = 0; i < CAKE_SET_WAYS;
			     i++, k = (k + 1) % CAKE_SET_WAYS) अणु
				अगर (!q->hosts[outer_hash + k].dsthost_bulk_flow_count)
					अवरोध;
			पूर्ण
			q->hosts[outer_hash + k].dsthost_tag = dsthost_hash;
found_dst:
			dsthost_idx = outer_hash + k;
			अगर (q->flows[reduced_hash].set == CAKE_SET_BULK)
				q->hosts[dsthost_idx].dsthost_bulk_flow_count++;
			q->flows[reduced_hash].dsthost = dsthost_idx;
		पूर्ण
	पूर्ण

	वापस reduced_hash;
पूर्ण

/* helper functions : might be changed when/अगर skb use a standard list_head */
/* हटाओ one skb from head of slot queue */

अटल काष्ठा sk_buff *dequeue_head(काष्ठा cake_flow *flow)
अणु
	काष्ठा sk_buff *skb = flow->head;

	अगर (skb) अणु
		flow->head = skb->next;
		skb_mark_not_on_list(skb);
	पूर्ण

	वापस skb;
पूर्ण

/* add skb to flow queue (tail add) */

अटल व्योम flow_queue_add(काष्ठा cake_flow *flow, काष्ठा sk_buff *skb)
अणु
	अगर (!flow->head)
		flow->head = skb;
	अन्यथा
		flow->tail->next = skb;
	flow->tail = skb;
	skb->next = शून्य;
पूर्ण

अटल काष्ठा iphdr *cake_get_iphdr(स्थिर काष्ठा sk_buff *skb,
				    काष्ठा ipv6hdr *buf)
अणु
	अचिन्हित पूर्णांक offset = skb_network_offset(skb);
	काष्ठा iphdr *iph;

	iph = skb_header_poपूर्णांकer(skb, offset, माप(काष्ठा iphdr), buf);

	अगर (!iph)
		वापस शून्य;

	अगर (iph->version == 4 && iph->protocol == IPPROTO_IPV6)
		वापस skb_header_poपूर्णांकer(skb, offset + iph->ihl * 4,
					  माप(काष्ठा ipv6hdr), buf);

	अन्यथा अगर (iph->version == 4)
		वापस iph;

	अन्यथा अगर (iph->version == 6)
		वापस skb_header_poपूर्णांकer(skb, offset, माप(काष्ठा ipv6hdr),
					  buf);

	वापस शून्य;
पूर्ण

अटल काष्ठा tcphdr *cake_get_tcphdr(स्थिर काष्ठा sk_buff *skb,
				      व्योम *buf, अचिन्हित पूर्णांक bufsize)
अणु
	अचिन्हित पूर्णांक offset = skb_network_offset(skb);
	स्थिर काष्ठा ipv6hdr *ipv6h;
	स्थिर काष्ठा tcphdr *tcph;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा ipv6hdr _ipv6h;
	काष्ठा tcphdr _tcph;

	ipv6h = skb_header_poपूर्णांकer(skb, offset, माप(_ipv6h), &_ipv6h);

	अगर (!ipv6h)
		वापस शून्य;

	अगर (ipv6h->version == 4) अणु
		iph = (काष्ठा iphdr *)ipv6h;
		offset += iph->ihl * 4;

		/* special-हाल 6in4 tunnelling, as that is a common way to get
		 * v6 connectivity in the home
		 */
		अगर (iph->protocol == IPPROTO_IPV6) अणु
			ipv6h = skb_header_poपूर्णांकer(skb, offset,
						   माप(_ipv6h), &_ipv6h);

			अगर (!ipv6h || ipv6h->nexthdr != IPPROTO_TCP)
				वापस शून्य;

			offset += माप(काष्ठा ipv6hdr);

		पूर्ण अन्यथा अगर (iph->protocol != IPPROTO_TCP) अणु
			वापस शून्य;
		पूर्ण

	पूर्ण अन्यथा अगर (ipv6h->version == 6) अणु
		अगर (ipv6h->nexthdr != IPPROTO_TCP)
			वापस शून्य;

		offset += माप(काष्ठा ipv6hdr);
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	tcph = skb_header_poपूर्णांकer(skb, offset, माप(_tcph), &_tcph);
	अगर (!tcph || tcph->करोff < 5)
		वापस शून्य;

	वापस skb_header_poपूर्णांकer(skb, offset,
				  min(__tcp_hdrlen(tcph), bufsize), buf);
पूर्ण

अटल स्थिर व्योम *cake_get_tcpopt(स्थिर काष्ठा tcphdr *tcph,
				   पूर्णांक code, पूर्णांक *oplen)
अणु
	/* inspired by tcp_parse_options in tcp_input.c */
	पूर्णांक length = __tcp_hdrlen(tcph) - माप(काष्ठा tcphdr);
	स्थिर u8 *ptr = (स्थिर u8 *)(tcph + 1);

	जबतक (length > 0) अणु
		पूर्णांक opcode = *ptr++;
		पूर्णांक opsize;

		अगर (opcode == TCPOPT_EOL)
			अवरोध;
		अगर (opcode == TCPOPT_NOP) अणु
			length--;
			जारी;
		पूर्ण
		अगर (length < 2)
			अवरोध;
		opsize = *ptr++;
		अगर (opsize < 2 || opsize > length)
			अवरोध;

		अगर (opcode == code) अणु
			*oplen = opsize;
			वापस ptr;
		पूर्ण

		ptr += opsize - 2;
		length -= opsize;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Compare two SACK sequences. A sequence is considered greater अगर it SACKs more
 * bytes than the other. In the हाल where both sequences ACKs bytes that the
 * other करोesn't, A is considered greater. DSACKs in A also makes A be
 * considered greater.
 *
 * @वापस -1, 0 or 1 as normal compare functions
 */
अटल पूर्णांक cake_tcph_sack_compare(स्थिर काष्ठा tcphdr *tcph_a,
				  स्थिर काष्ठा tcphdr *tcph_b)
अणु
	स्थिर काष्ठा tcp_sack_block_wire *sack_a, *sack_b;
	u32 ack_seq_a = ntohl(tcph_a->ack_seq);
	u32 bytes_a = 0, bytes_b = 0;
	पूर्णांक oplen_a, oplen_b;
	bool first = true;

	sack_a = cake_get_tcpopt(tcph_a, TCPOPT_SACK, &oplen_a);
	sack_b = cake_get_tcpopt(tcph_b, TCPOPT_SACK, &oplen_b);

	/* poपूर्णांकers poपूर्णांक to option contents */
	oplen_a -= TCPOLEN_SACK_BASE;
	oplen_b -= TCPOLEN_SACK_BASE;

	अगर (sack_a && oplen_a >= माप(*sack_a) &&
	    (!sack_b || oplen_b < माप(*sack_b)))
		वापस -1;
	अन्यथा अगर (sack_b && oplen_b >= माप(*sack_b) &&
		 (!sack_a || oplen_a < माप(*sack_a)))
		वापस 1;
	अन्यथा अगर ((!sack_a || oplen_a < माप(*sack_a)) &&
		 (!sack_b || oplen_b < माप(*sack_b)))
		वापस 0;

	जबतक (oplen_a >= माप(*sack_a)) अणु
		स्थिर काष्ठा tcp_sack_block_wire *sack_पंचांगp = sack_b;
		u32 start_a = get_unaligned_be32(&sack_a->start_seq);
		u32 end_a = get_unaligned_be32(&sack_a->end_seq);
		पूर्णांक oplen_पंचांगp = oplen_b;
		bool found = false;

		/* DSACK; always considered greater to prevent dropping */
		अगर (beक्रमe(start_a, ack_seq_a))
			वापस -1;

		bytes_a += end_a - start_a;

		जबतक (oplen_पंचांगp >= माप(*sack_पंचांगp)) अणु
			u32 start_b = get_unaligned_be32(&sack_पंचांगp->start_seq);
			u32 end_b = get_unaligned_be32(&sack_पंचांगp->end_seq);

			/* first समय through we count the total size */
			अगर (first)
				bytes_b += end_b - start_b;

			अगर (!after(start_b, start_a) && !beक्रमe(end_b, end_a)) अणु
				found = true;
				अगर (!first)
					अवरोध;
			पूर्ण
			oplen_पंचांगp -= माप(*sack_पंचांगp);
			sack_पंचांगp++;
		पूर्ण

		अगर (!found)
			वापस -1;

		oplen_a -= माप(*sack_a);
		sack_a++;
		first = false;
	पूर्ण

	/* If we made it this far, all ranges SACKed by A are covered by B, so
	 * either the SACKs are equal, or B SACKs more bytes.
	 */
	वापस bytes_b > bytes_a ? 1 : 0;
पूर्ण

अटल व्योम cake_tcph_get_tstamp(स्थिर काष्ठा tcphdr *tcph,
				 u32 *tsval, u32 *tsecr)
अणु
	स्थिर u8 *ptr;
	पूर्णांक opsize;

	ptr = cake_get_tcpopt(tcph, TCPOPT_TIMESTAMP, &opsize);

	अगर (ptr && opsize == TCPOLEN_TIMESTAMP) अणु
		*tsval = get_unaligned_be32(ptr);
		*tsecr = get_unaligned_be32(ptr + 4);
	पूर्ण
पूर्ण

अटल bool cake_tcph_may_drop(स्थिर काष्ठा tcphdr *tcph,
			       u32 tstamp_new, u32 tsecr_new)
अणु
	/* inspired by tcp_parse_options in tcp_input.c */
	पूर्णांक length = __tcp_hdrlen(tcph) - माप(काष्ठा tcphdr);
	स्थिर u8 *ptr = (स्थिर u8 *)(tcph + 1);
	u32 tstamp, tsecr;

	/* 3 reserved flags must be unset to aव्योम future अवरोधage
	 * ACK must be set
	 * ECE/CWR are handled separately
	 * All other flags URG/PSH/RST/SYN/FIN must be unset
	 * 0x0FFF0000 = all TCP flags (confirm ACK=1, others zero)
	 * 0x00C00000 = CWR/ECE (handled separately)
	 * 0x0F3F0000 = 0x0FFF0000 & ~0x00C00000
	 */
	अगर (((tcp_flag_word(tcph) &
	      cpu_to_be32(0x0F3F0000)) != TCP_FLAG_ACK))
		वापस false;

	जबतक (length > 0) अणु
		पूर्णांक opcode = *ptr++;
		पूर्णांक opsize;

		अगर (opcode == TCPOPT_EOL)
			अवरोध;
		अगर (opcode == TCPOPT_NOP) अणु
			length--;
			जारी;
		पूर्ण
		अगर (length < 2)
			अवरोध;
		opsize = *ptr++;
		अगर (opsize < 2 || opsize > length)
			अवरोध;

		चयन (opcode) अणु
		हाल TCPOPT_MD5SIG: /* करोesn't influence state */
			अवरोध;

		हाल TCPOPT_SACK: /* stricter checking perक्रमmed later */
			अगर (opsize % 8 != 2)
				वापस false;
			अवरोध;

		हाल TCPOPT_TIMESTAMP:
			/* only drop बारtamps lower than new */
			अगर (opsize != TCPOLEN_TIMESTAMP)
				वापस false;
			tstamp = get_unaligned_be32(ptr);
			tsecr = get_unaligned_be32(ptr + 4);
			अगर (after(tstamp, tstamp_new) ||
			    after(tsecr, tsecr_new))
				वापस false;
			अवरोध;

		हाल TCPOPT_MSS:  /* these should only be set on SYN */
		हाल TCPOPT_WINDOW:
		हाल TCPOPT_SACK_PERM:
		हाल TCPOPT_FASTOPEN:
		हाल TCPOPT_EXP:
		शेष: /* करोn't drop अगर any unknown options are present */
			वापस false;
		पूर्ण

		ptr += opsize - 2;
		length -= opsize;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा sk_buff *cake_ack_filter(काष्ठा cake_sched_data *q,
				       काष्ठा cake_flow *flow)
अणु
	bool aggressive = q->ack_filter == CAKE_ACK_AGGRESSIVE;
	काष्ठा sk_buff *elig_ack = शून्य, *elig_ack_prev = शून्य;
	काष्ठा sk_buff *skb_check, *skb_prev = शून्य;
	स्थिर काष्ठा ipv6hdr *ipv6h, *ipv6h_check;
	अचिन्हित अक्षर _tcph[64], _tcph_check[64];
	स्थिर काष्ठा tcphdr *tcph, *tcph_check;
	स्थिर काष्ठा iphdr *iph, *iph_check;
	काष्ठा ipv6hdr _iph, _iph_check;
	स्थिर काष्ठा sk_buff *skb;
	पूर्णांक seglen, num_found = 0;
	u32 tstamp = 0, tsecr = 0;
	__be32 elig_flags = 0;
	पूर्णांक sack_comp;

	/* no other possible ACKs to filter */
	अगर (flow->head == flow->tail)
		वापस शून्य;

	skb = flow->tail;
	tcph = cake_get_tcphdr(skb, _tcph, माप(_tcph));
	iph = cake_get_iphdr(skb, &_iph);
	अगर (!tcph)
		वापस शून्य;

	cake_tcph_get_tstamp(tcph, &tstamp, &tsecr);

	/* the 'triggering' packet need only have the ACK flag set.
	 * also check that SYN is not set, as there won't be any previous ACKs.
	 */
	अगर ((tcp_flag_word(tcph) &
	     (TCP_FLAG_ACK | TCP_FLAG_SYN)) != TCP_FLAG_ACK)
		वापस शून्य;

	/* the 'triggering' ACK is at the tail of the queue, we have alपढ़ोy
	 * वापसed अगर it is the only packet in the flow. loop through the rest
	 * of the queue looking क्रम pure ACKs with the same 5-tuple as the
	 * triggering one.
	 */
	क्रम (skb_check = flow->head;
	     skb_check && skb_check != skb;
	     skb_prev = skb_check, skb_check = skb_check->next) अणु
		iph_check = cake_get_iphdr(skb_check, &_iph_check);
		tcph_check = cake_get_tcphdr(skb_check, &_tcph_check,
					     माप(_tcph_check));

		/* only TCP packets with matching 5-tuple are eligible, and only
		 * drop safe headers
		 */
		अगर (!tcph_check || iph->version != iph_check->version ||
		    tcph_check->source != tcph->source ||
		    tcph_check->dest != tcph->dest)
			जारी;

		अगर (iph_check->version == 4) अणु
			अगर (iph_check->saddr != iph->saddr ||
			    iph_check->daddr != iph->daddr)
				जारी;

			seglen = ntohs(iph_check->tot_len) -
				       (4 * iph_check->ihl);
		पूर्ण अन्यथा अगर (iph_check->version == 6) अणु
			ipv6h = (काष्ठा ipv6hdr *)iph;
			ipv6h_check = (काष्ठा ipv6hdr *)iph_check;

			अगर (ipv6_addr_cmp(&ipv6h_check->saddr, &ipv6h->saddr) ||
			    ipv6_addr_cmp(&ipv6h_check->daddr, &ipv6h->daddr))
				जारी;

			seglen = ntohs(ipv6h_check->payload_len);
		पूर्ण अन्यथा अणु
			WARN_ON(1);  /* shouldn't happen */
			जारी;
		पूर्ण

		/* If the ECE/CWR flags changed from the previous eligible
		 * packet in the same flow, we should no दीर्घer be dropping that
		 * previous packet as this would lose inक्रमmation.
		 */
		अगर (elig_ack && (tcp_flag_word(tcph_check) &
				 (TCP_FLAG_ECE | TCP_FLAG_CWR)) != elig_flags) अणु
			elig_ack = शून्य;
			elig_ack_prev = शून्य;
			num_found--;
		पूर्ण

		/* Check TCP options and flags, करोn't drop ACKs with segment
		 * data, and करोn't drop ACKs with a higher cumulative ACK
		 * counter than the triggering packet. Check ACK seqno here to
		 * aव्योम parsing SACK options of packets we are going to exclude
		 * anyway.
		 */
		अगर (!cake_tcph_may_drop(tcph_check, tstamp, tsecr) ||
		    (seglen - __tcp_hdrlen(tcph_check)) != 0 ||
		    after(ntohl(tcph_check->ack_seq), ntohl(tcph->ack_seq)))
			जारी;

		/* Check SACK options. The triggering packet must SACK more data
		 * than the ACK under consideration, or SACK the same range but
		 * have a larger cumulative ACK counter. The latter is a
		 * pathological हाल, but is contained in the following check
		 * anyway, just to be safe.
		 */
		sack_comp = cake_tcph_sack_compare(tcph_check, tcph);

		अगर (sack_comp < 0 ||
		    (ntohl(tcph_check->ack_seq) == ntohl(tcph->ack_seq) &&
		     sack_comp == 0))
			जारी;

		/* At this poपूर्णांक we have found an eligible pure ACK to drop; अगर
		 * we are in aggressive mode, we are करोne. Otherwise, keep
		 * searching unless this is the second eligible ACK we
		 * found.
		 *
		 * Since we want to drop ACK बंदst to the head of the queue,
		 * save the first eligible ACK we find, even अगर we need to loop
		 * again.
		 */
		अगर (!elig_ack) अणु
			elig_ack = skb_check;
			elig_ack_prev = skb_prev;
			elig_flags = (tcp_flag_word(tcph_check)
				      & (TCP_FLAG_ECE | TCP_FLAG_CWR));
		पूर्ण

		अगर (num_found++ > 0)
			जाओ found;
	पूर्ण

	/* We made it through the queue without finding two eligible ACKs . If
	 * we found a single eligible ACK we can drop it in aggressive mode अगर
	 * we can guarantee that this करोes not पूर्णांकerfere with ECN flag
	 * inक्रमmation. We ensure this by dropping it only अगर the enqueued
	 * packet is consecutive with the eligible ACK, and their flags match.
	 */
	अगर (elig_ack && aggressive && elig_ack->next == skb &&
	    (elig_flags == (tcp_flag_word(tcph) &
			    (TCP_FLAG_ECE | TCP_FLAG_CWR))))
		जाओ found;

	वापस शून्य;

found:
	अगर (elig_ack_prev)
		elig_ack_prev->next = elig_ack->next;
	अन्यथा
		flow->head = elig_ack->next;

	skb_mark_not_on_list(elig_ack);

	वापस elig_ack;
पूर्ण

अटल u64 cake_ewma(u64 avg, u64 sample, u32 shअगरt)
अणु
	avg -= avg >> shअगरt;
	avg += sample >> shअगरt;
	वापस avg;
पूर्ण

अटल u32 cake_calc_overhead(काष्ठा cake_sched_data *q, u32 len, u32 off)
अणु
	अगर (q->rate_flags & CAKE_FLAG_OVERHEAD)
		len -= off;

	अगर (q->max_netlen < len)
		q->max_netlen = len;
	अगर (q->min_netlen > len)
		q->min_netlen = len;

	len += q->rate_overhead;

	अगर (len < q->rate_mpu)
		len = q->rate_mpu;

	अगर (q->aपंचांग_mode == CAKE_ATM_ATM) अणु
		len += 47;
		len /= 48;
		len *= 53;
	पूर्ण अन्यथा अगर (q->aपंचांग_mode == CAKE_ATM_PTM) अणु
		/* Add one byte per 64 bytes or part thereof.
		 * This is conservative and easier to calculate than the
		 * precise value.
		 */
		len += (len + 63) / 64;
	पूर्ण

	अगर (q->max_adjlen < len)
		q->max_adjlen = len;
	अगर (q->min_adjlen > len)
		q->min_adjlen = len;

	वापस len;
पूर्ण

अटल u32 cake_overhead(काष्ठा cake_sched_data *q, स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	अचिन्हित पूर्णांक hdr_len, last_len = 0;
	u32 off = skb_network_offset(skb);
	u32 len = qdisc_pkt_len(skb);
	u16 segs = 1;

	q->avg_netoff = cake_ewma(q->avg_netoff, off << 16, 8);

	अगर (!shinfo->gso_size)
		वापस cake_calc_overhead(q, len, off);

	/* borrowed from qdisc_pkt_len_init() */
	hdr_len = skb_transport_header(skb) - skb_mac_header(skb);

	/* + transport layer */
	अगर (likely(shinfo->gso_type & (SKB_GSO_TCPV4 |
						SKB_GSO_TCPV6))) अणु
		स्थिर काष्ठा tcphdr *th;
		काष्ठा tcphdr _tcphdr;

		th = skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
					माप(_tcphdr), &_tcphdr);
		अगर (likely(th))
			hdr_len += __tcp_hdrlen(th);
	पूर्ण अन्यथा अणु
		काष्ठा udphdr _udphdr;

		अगर (skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
				       माप(_udphdr), &_udphdr))
			hdr_len += माप(काष्ठा udphdr);
	पूर्ण

	अगर (unlikely(shinfo->gso_type & SKB_GSO_DODGY))
		segs = DIV_ROUND_UP(skb->len - hdr_len,
				    shinfo->gso_size);
	अन्यथा
		segs = shinfo->gso_segs;

	len = shinfo->gso_size + hdr_len;
	last_len = skb->len - shinfo->gso_size * (segs - 1);

	वापस (cake_calc_overhead(q, len, off) * (segs - 1) +
		cake_calc_overhead(q, last_len, off));
पूर्ण

अटल व्योम cake_heap_swap(काष्ठा cake_sched_data *q, u16 i, u16 j)
अणु
	काष्ठा cake_heap_entry ii = q->overflow_heap[i];
	काष्ठा cake_heap_entry jj = q->overflow_heap[j];

	q->overflow_heap[i] = jj;
	q->overflow_heap[j] = ii;

	q->tins[ii.t].overflow_idx[ii.b] = j;
	q->tins[jj.t].overflow_idx[jj.b] = i;
पूर्ण

अटल u32 cake_heap_get_backlog(स्थिर काष्ठा cake_sched_data *q, u16 i)
अणु
	काष्ठा cake_heap_entry ii = q->overflow_heap[i];

	वापस q->tins[ii.t].backlogs[ii.b];
पूर्ण

अटल व्योम cake_heapअगरy(काष्ठा cake_sched_data *q, u16 i)
अणु
	अटल स्थिर u32 a = CAKE_MAX_TINS * CAKE_QUEUES;
	u32 mb = cake_heap_get_backlog(q, i);
	u32 m = i;

	जबतक (m < a) अणु
		u32 l = m + m + 1;
		u32 r = l + 1;

		अगर (l < a) अणु
			u32 lb = cake_heap_get_backlog(q, l);

			अगर (lb > mb) अणु
				m  = l;
				mb = lb;
			पूर्ण
		पूर्ण

		अगर (r < a) अणु
			u32 rb = cake_heap_get_backlog(q, r);

			अगर (rb > mb) अणु
				m  = r;
				mb = rb;
			पूर्ण
		पूर्ण

		अगर (m != i) अणु
			cake_heap_swap(q, i, m);
			i = m;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cake_heapअगरy_up(काष्ठा cake_sched_data *q, u16 i)
अणु
	जबतक (i > 0 && i < CAKE_MAX_TINS * CAKE_QUEUES) अणु
		u16 p = (i - 1) >> 1;
		u32 ib = cake_heap_get_backlog(q, i);
		u32 pb = cake_heap_get_backlog(q, p);

		अगर (ib > pb) अणु
			cake_heap_swap(q, i, p);
			i = p;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cake_advance_shaper(काष्ठा cake_sched_data *q,
			       काष्ठा cake_tin_data *b,
			       काष्ठा sk_buff *skb,
			       kसमय_प्रकार now, bool drop)
अणु
	u32 len = get_cobalt_cb(skb)->adjusted_len;

	/* अक्षरge packet bandwidth to this tin
	 * and to the global shaper.
	 */
	अगर (q->rate_ns) अणु
		u64 tin_dur = (len * b->tin_rate_ns) >> b->tin_rate_shft;
		u64 global_dur = (len * q->rate_ns) >> q->rate_shft;
		u64 failsafe_dur = global_dur + (global_dur >> 1);

		अगर (kसमय_beक्रमe(b->समय_next_packet, now))
			b->समय_next_packet = kसमय_add_ns(b->समय_next_packet,
							   tin_dur);

		अन्यथा अगर (kसमय_beक्रमe(b->समय_next_packet,
				      kसमय_add_ns(now, tin_dur)))
			b->समय_next_packet = kसमय_add_ns(now, tin_dur);

		q->समय_next_packet = kसमय_add_ns(q->समय_next_packet,
						   global_dur);
		अगर (!drop)
			q->failsafe_next_packet = \
				kसमय_add_ns(q->failsafe_next_packet,
					     failsafe_dur);
	पूर्ण
	वापस len;
पूर्ण

अटल अचिन्हित पूर्णांक cake_drop(काष्ठा Qdisc *sch, काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	kसमय_प्रकार now = kसमय_get();
	u32 idx = 0, tin = 0, len;
	काष्ठा cake_heap_entry qq;
	काष्ठा cake_tin_data *b;
	काष्ठा cake_flow *flow;
	काष्ठा sk_buff *skb;

	अगर (!q->overflow_समयout) अणु
		पूर्णांक i;
		/* Build fresh max-heap */
		क्रम (i = CAKE_MAX_TINS * CAKE_QUEUES / 2; i >= 0; i--)
			cake_heapअगरy(q, i);
	पूर्ण
	q->overflow_समयout = 65535;

	/* select दीर्घest queue क्रम pruning */
	qq  = q->overflow_heap[0];
	tin = qq.t;
	idx = qq.b;

	b = &q->tins[tin];
	flow = &b->flows[idx];
	skb = dequeue_head(flow);
	अगर (unlikely(!skb)) अणु
		/* heap has gone wrong, rebuild it next समय */
		q->overflow_समयout = 0;
		वापस idx + (tin << 16);
	पूर्ण

	अगर (cobalt_queue_full(&flow->cvars, &b->cparams, now))
		b->unresponsive_flow_count++;

	len = qdisc_pkt_len(skb);
	q->buffer_used      -= skb->truesize;
	b->backlogs[idx]    -= len;
	b->tin_backlog      -= len;
	sch->qstats.backlog -= len;
	qdisc_tree_reduce_backlog(sch, 1, len);

	flow->dropped++;
	b->tin_dropped++;
	sch->qstats.drops++;

	अगर (q->rate_flags & CAKE_FLAG_INGRESS)
		cake_advance_shaper(q, b, skb, now, true);

	__qdisc_drop(skb, to_मुक्त);
	sch->q.qlen--;

	cake_heapअगरy(q, 0);

	वापस idx + (tin << 16);
पूर्ण

अटल u8 cake_handle_dअगरfserv(काष्ठा sk_buff *skb, bool wash)
अणु
	स्थिर पूर्णांक offset = skb_network_offset(skb);
	u16 *buf, buf_;
	u8 dscp;

	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		buf = skb_header_poपूर्णांकer(skb, offset, माप(buf_), &buf_);
		अगर (unlikely(!buf))
			वापस 0;

		/* ToS is in the second byte of iphdr */
		dscp = ipv4_get_dsfield((काष्ठा iphdr *)buf) >> 2;

		अगर (wash && dscp) अणु
			स्थिर पूर्णांक wlen = offset + माप(काष्ठा iphdr);

			अगर (!pskb_may_pull(skb, wlen) ||
			    skb_try_make_writable(skb, wlen))
				वापस 0;

			ipv4_change_dsfield(ip_hdr(skb), INET_ECN_MASK, 0);
		पूर्ण

		वापस dscp;

	हाल htons(ETH_P_IPV6):
		buf = skb_header_poपूर्णांकer(skb, offset, माप(buf_), &buf_);
		अगर (unlikely(!buf))
			वापस 0;

		/* Traffic class is in the first and second bytes of ipv6hdr */
		dscp = ipv6_get_dsfield((काष्ठा ipv6hdr *)buf) >> 2;

		अगर (wash && dscp) अणु
			स्थिर पूर्णांक wlen = offset + माप(काष्ठा ipv6hdr);

			अगर (!pskb_may_pull(skb, wlen) ||
			    skb_try_make_writable(skb, wlen))
				वापस 0;

			ipv6_change_dsfield(ipv6_hdr(skb), INET_ECN_MASK, 0);
		पूर्ण

		वापस dscp;

	हाल htons(ETH_P_ARP):
		वापस 0x38;  /* CS7 - Net Control */

	शेष:
		/* If there is no Dअगरfserv field, treat as best-efक्रमt */
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा cake_tin_data *cake_select_tin(काष्ठा Qdisc *sch,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	u32 tin, mark;
	bool wash;
	u8 dscp;

	/* Tin selection: Default to dअगरfserv-based selection, allow overriding
	 * using firewall marks or skb->priority. Call DSCP parsing early अगर
	 * wash is enabled, otherwise defer to below to skip unneeded parsing.
	 */
	mark = (skb->mark & q->fwmark_mask) >> q->fwmark_shft;
	wash = !!(q->rate_flags & CAKE_FLAG_WASH);
	अगर (wash)
		dscp = cake_handle_dअगरfserv(skb, wash);

	अगर (q->tin_mode == CAKE_DIFFSERV_BESTEFFORT)
		tin = 0;

	अन्यथा अगर (mark && mark <= q->tin_cnt)
		tin = q->tin_order[mark - 1];

	अन्यथा अगर (TC_H_MAJ(skb->priority) == sch->handle &&
		 TC_H_MIN(skb->priority) > 0 &&
		 TC_H_MIN(skb->priority) <= q->tin_cnt)
		tin = q->tin_order[TC_H_MIN(skb->priority) - 1];

	अन्यथा अणु
		अगर (!wash)
			dscp = cake_handle_dअगरfserv(skb, wash);
		tin = q->tin_index[dscp];

		अगर (unlikely(tin >= q->tin_cnt))
			tin = 0;
	पूर्ण

	वापस &q->tins[tin];
पूर्ण

अटल u32 cake_classअगरy(काष्ठा Qdisc *sch, काष्ठा cake_tin_data **t,
			 काष्ठा sk_buff *skb, पूर्णांक flow_mode, पूर्णांक *qerr)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	काष्ठा tcf_proto *filter;
	काष्ठा tcf_result res;
	u16 flow = 0, host = 0;
	पूर्णांक result;

	filter = rcu_dereference_bh(q->filter_list);
	अगर (!filter)
		जाओ hash;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	result = tcf_classअगरy(skb, filter, &res, false);

	अगर (result >= 0) अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (result) अणु
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			fallthrough;
		हाल TC_ACT_SHOT:
			वापस 0;
		पूर्ण
#पूर्ण_अगर
		अगर (TC_H_MIN(res.classid) <= CAKE_QUEUES)
			flow = TC_H_MIN(res.classid);
		अगर (TC_H_MAJ(res.classid) <= (CAKE_QUEUES << 16))
			host = TC_H_MAJ(res.classid) >> 16;
	पूर्ण
hash:
	*t = cake_select_tin(sch, skb);
	वापस cake_hash(*t, skb, flow_mode, flow, host) + 1;
पूर्ण

अटल व्योम cake_reconfigure(काष्ठा Qdisc *sch);

अटल s32 cake_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	पूर्णांक len = qdisc_pkt_len(skb);
	पूर्णांक ret;
	काष्ठा sk_buff *ack = शून्य;
	kसमय_प्रकार now = kसमय_get();
	काष्ठा cake_tin_data *b;
	काष्ठा cake_flow *flow;
	u32 idx;

	/* choose flow to insert पूर्णांकo */
	idx = cake_classअगरy(sch, &b, skb, q->flow_mode, &ret);
	अगर (idx == 0) अणु
		अगर (ret & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस ret;
	पूर्ण
	idx--;
	flow = &b->flows[idx];

	/* ensure shaper state isn't stale */
	अगर (!b->tin_backlog) अणु
		अगर (kसमय_beक्रमe(b->समय_next_packet, now))
			b->समय_next_packet = now;

		अगर (!sch->q.qlen) अणु
			अगर (kसमय_beक्रमe(q->समय_next_packet, now)) अणु
				q->failsafe_next_packet = now;
				q->समय_next_packet = now;
			पूर्ण अन्यथा अगर (kसमय_after(q->समय_next_packet, now) &&
				   kसमय_after(q->failsafe_next_packet, now)) अणु
				u64 next = \
					min(kसमय_प्रकारo_ns(q->समय_next_packet),
					    kसमय_प्रकारo_ns(
						   q->failsafe_next_packet));
				sch->qstats.overlimits++;
				qdisc_watchकरोg_schedule_ns(&q->watchकरोg, next);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (unlikely(len > b->max_skblen))
		b->max_skblen = len;

	अगर (skb_is_gso(skb) && q->rate_flags & CAKE_FLAG_SPLIT_GSO) अणु
		काष्ठा sk_buff *segs, *nskb;
		netdev_features_t features = netअगर_skb_features(skb);
		अचिन्हित पूर्णांक slen = 0, numsegs = 0;

		segs = skb_gso_segment(skb, features & ~NETIF_F_GSO_MASK);
		अगर (IS_ERR_OR_शून्य(segs))
			वापस qdisc_drop(skb, sch, to_मुक्त);

		skb_list_walk_safe(segs, segs, nskb) अणु
			skb_mark_not_on_list(segs);
			qdisc_skb_cb(segs)->pkt_len = segs->len;
			cobalt_set_enqueue_समय(segs, now);
			get_cobalt_cb(segs)->adjusted_len = cake_overhead(q,
									  segs);
			flow_queue_add(flow, segs);

			sch->q.qlen++;
			numsegs++;
			slen += segs->len;
			q->buffer_used += segs->truesize;
			b->packets++;
		पूर्ण

		/* stats */
		b->bytes	    += slen;
		b->backlogs[idx]    += slen;
		b->tin_backlog      += slen;
		sch->qstats.backlog += slen;
		q->avg_winकरोw_bytes += slen;

		qdisc_tree_reduce_backlog(sch, 1-numsegs, len-slen);
		consume_skb(skb);
	पूर्ण अन्यथा अणु
		/* not splitting */
		cobalt_set_enqueue_समय(skb, now);
		get_cobalt_cb(skb)->adjusted_len = cake_overhead(q, skb);
		flow_queue_add(flow, skb);

		अगर (q->ack_filter)
			ack = cake_ack_filter(q, flow);

		अगर (ack) अणु
			b->ack_drops++;
			sch->qstats.drops++;
			b->bytes += qdisc_pkt_len(ack);
			len -= qdisc_pkt_len(ack);
			q->buffer_used += skb->truesize - ack->truesize;
			अगर (q->rate_flags & CAKE_FLAG_INGRESS)
				cake_advance_shaper(q, b, ack, now, true);

			qdisc_tree_reduce_backlog(sch, 1, qdisc_pkt_len(ack));
			consume_skb(ack);
		पूर्ण अन्यथा अणु
			sch->q.qlen++;
			q->buffer_used      += skb->truesize;
		पूर्ण

		/* stats */
		b->packets++;
		b->bytes	    += len;
		b->backlogs[idx]    += len;
		b->tin_backlog      += len;
		sch->qstats.backlog += len;
		q->avg_winकरोw_bytes += len;
	पूर्ण

	अगर (q->overflow_समयout)
		cake_heapअगरy_up(q, b->overflow_idx[idx]);

	/* incoming bandwidth capacity estimate */
	अगर (q->rate_flags & CAKE_FLAG_AUTORATE_INGRESS) अणु
		u64 packet_पूर्णांकerval = \
			kसमय_प्रकारo_ns(kसमय_sub(now, q->last_packet_समय));

		अगर (packet_पूर्णांकerval > NSEC_PER_SEC)
			packet_पूर्णांकerval = NSEC_PER_SEC;

		/* filter out लघु-term bursts, eg. wअगरi aggregation */
		q->avg_packet_पूर्णांकerval = \
			cake_ewma(q->avg_packet_पूर्णांकerval,
				  packet_पूर्णांकerval,
				  (packet_पूर्णांकerval > q->avg_packet_पूर्णांकerval ?
					  2 : 8));

		q->last_packet_समय = now;

		अगर (packet_पूर्णांकerval > q->avg_packet_पूर्णांकerval) अणु
			u64 winकरोw_पूर्णांकerval = \
				kसमय_प्रकारo_ns(kसमय_sub(now,
						      q->avg_winकरोw_begin));
			u64 b = q->avg_winकरोw_bytes * (u64)NSEC_PER_SEC;

			b = भाग64_u64(b, winकरोw_पूर्णांकerval);
			q->avg_peak_bandwidth =
				cake_ewma(q->avg_peak_bandwidth, b,
					  b > q->avg_peak_bandwidth ? 2 : 8);
			q->avg_winकरोw_bytes = 0;
			q->avg_winकरोw_begin = now;

			अगर (kसमय_after(now,
					kसमय_add_ms(q->last_reconfig_समय,
						     250))) अणु
				q->rate_bps = (q->avg_peak_bandwidth * 15) >> 4;
				cake_reconfigure(sch);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		q->avg_winकरोw_bytes = 0;
		q->last_packet_समय = now;
	पूर्ण

	/* flowchain */
	अगर (!flow->set || flow->set == CAKE_SET_DECAYING) अणु
		काष्ठा cake_host *srchost = &b->hosts[flow->srchost];
		काष्ठा cake_host *dsthost = &b->hosts[flow->dsthost];
		u16 host_load = 1;

		अगर (!flow->set) अणु
			list_add_tail(&flow->flowchain, &b->new_flows);
		पूर्ण अन्यथा अणु
			b->decaying_flow_count--;
			list_move_tail(&flow->flowchain, &b->new_flows);
		पूर्ण
		flow->set = CAKE_SET_SPARSE;
		b->sparse_flow_count++;

		अगर (cake_dsrc(q->flow_mode))
			host_load = max(host_load, srchost->srchost_bulk_flow_count);

		अगर (cake_ddst(q->flow_mode))
			host_load = max(host_load, dsthost->dsthost_bulk_flow_count);

		flow->deficit = (b->flow_quantum *
				 quantum_भाग[host_load]) >> 16;
	पूर्ण अन्यथा अगर (flow->set == CAKE_SET_SPARSE_WAIT) अणु
		काष्ठा cake_host *srchost = &b->hosts[flow->srchost];
		काष्ठा cake_host *dsthost = &b->hosts[flow->dsthost];

		/* this flow was empty, accounted as a sparse flow, but actually
		 * in the bulk rotation.
		 */
		flow->set = CAKE_SET_BULK;
		b->sparse_flow_count--;
		b->bulk_flow_count++;

		अगर (cake_dsrc(q->flow_mode))
			srchost->srchost_bulk_flow_count++;

		अगर (cake_ddst(q->flow_mode))
			dsthost->dsthost_bulk_flow_count++;

	पूर्ण

	अगर (q->buffer_used > q->buffer_max_used)
		q->buffer_max_used = q->buffer_used;

	अगर (q->buffer_used > q->buffer_limit) अणु
		u32 dropped = 0;

		जबतक (q->buffer_used > q->buffer_limit) अणु
			dropped++;
			cake_drop(sch, to_मुक्त);
		पूर्ण
		b->drop_overlimit += dropped;
	पूर्ण
	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल काष्ठा sk_buff *cake_dequeue_one(काष्ठा Qdisc *sch)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	काष्ठा cake_tin_data *b = &q->tins[q->cur_tin];
	काष्ठा cake_flow *flow = &b->flows[q->cur_flow];
	काष्ठा sk_buff *skb = शून्य;
	u32 len;

	अगर (flow->head) अणु
		skb = dequeue_head(flow);
		len = qdisc_pkt_len(skb);
		b->backlogs[q->cur_flow] -= len;
		b->tin_backlog		 -= len;
		sch->qstats.backlog      -= len;
		q->buffer_used		 -= skb->truesize;
		sch->q.qlen--;

		अगर (q->overflow_समयout)
			cake_heapअगरy(q, b->overflow_idx[q->cur_flow]);
	पूर्ण
	वापस skb;
पूर्ण

/* Discard leftover packets from a tin no दीर्घer in use. */
अटल व्योम cake_clear_tin(काष्ठा Qdisc *sch, u16 tin)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;

	q->cur_tin = tin;
	क्रम (q->cur_flow = 0; q->cur_flow < CAKE_QUEUES; q->cur_flow++)
		जबतक (!!(skb = cake_dequeue_one(sch)))
			kमुक्त_skb(skb);
पूर्ण

अटल काष्ठा sk_buff *cake_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	काष्ठा cake_tin_data *b = &q->tins[q->cur_tin];
	काष्ठा cake_host *srchost, *dsthost;
	kसमय_प्रकार now = kसमय_get();
	काष्ठा cake_flow *flow;
	काष्ठा list_head *head;
	bool first_flow = true;
	काष्ठा sk_buff *skb;
	u16 host_load;
	u64 delay;
	u32 len;

begin:
	अगर (!sch->q.qlen)
		वापस शून्य;

	/* global hard shaper */
	अगर (kसमय_after(q->समय_next_packet, now) &&
	    kसमय_after(q->failsafe_next_packet, now)) अणु
		u64 next = min(kसमय_प्रकारo_ns(q->समय_next_packet),
			       kसमय_प्रकारo_ns(q->failsafe_next_packet));

		sch->qstats.overlimits++;
		qdisc_watchकरोg_schedule_ns(&q->watchकरोg, next);
		वापस शून्य;
	पूर्ण

	/* Choose a class to work on. */
	अगर (!q->rate_ns) अणु
		/* In unlimited mode, can't rely on shaper timings, just balance
		 * with DRR
		 */
		bool wrapped = false, empty = true;

		जबतक (b->tin_deficit < 0 ||
		       !(b->sparse_flow_count + b->bulk_flow_count)) अणु
			अगर (b->tin_deficit <= 0)
				b->tin_deficit += b->tin_quantum;
			अगर (b->sparse_flow_count + b->bulk_flow_count)
				empty = false;

			q->cur_tin++;
			b++;
			अगर (q->cur_tin >= q->tin_cnt) अणु
				q->cur_tin = 0;
				b = q->tins;

				अगर (wrapped) अणु
					/* It's possible क्रम q->qlen to be
					 * nonzero when we actually have no
					 * packets anywhere.
					 */
					अगर (empty)
						वापस शून्य;
				पूर्ण अन्यथा अणु
					wrapped = true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* In shaped mode, choose:
		 * - Highest-priority tin with queue and meeting schedule, or
		 * - The earliest-scheduled tin with queue.
		 */
		kसमय_प्रकार best_समय = KTIME_MAX;
		पूर्णांक tin, best_tin = 0;

		क्रम (tin = 0; tin < q->tin_cnt; tin++) अणु
			b = q->tins + tin;
			अगर ((b->sparse_flow_count + b->bulk_flow_count) > 0) अणु
				kसमय_प्रकार समय_प्रकारo_pkt = \
					kसमय_sub(b->समय_next_packet, now);

				अगर (kसमय_प्रकारo_ns(समय_प्रकारo_pkt) <= 0 ||
				    kसमय_compare(समय_प्रकारo_pkt,
						  best_समय) <= 0) अणु
					best_समय = समय_प्रकारo_pkt;
					best_tin = tin;
				पूर्ण
			पूर्ण
		पूर्ण

		q->cur_tin = best_tin;
		b = q->tins + best_tin;

		/* No poपूर्णांक in going further अगर no packets to deliver. */
		अगर (unlikely(!(b->sparse_flow_count + b->bulk_flow_count)))
			वापस शून्य;
	पूर्ण

retry:
	/* service this class */
	head = &b->decaying_flows;
	अगर (!first_flow || list_empty(head)) अणु
		head = &b->new_flows;
		अगर (list_empty(head)) अणु
			head = &b->old_flows;
			अगर (unlikely(list_empty(head))) अणु
				head = &b->decaying_flows;
				अगर (unlikely(list_empty(head)))
					जाओ begin;
			पूर्ण
		पूर्ण
	पूर्ण
	flow = list_first_entry(head, काष्ठा cake_flow, flowchain);
	q->cur_flow = flow - b->flows;
	first_flow = false;

	/* triple isolation (modअगरied DRR++) */
	srchost = &b->hosts[flow->srchost];
	dsthost = &b->hosts[flow->dsthost];
	host_load = 1;

	/* flow isolation (DRR++) */
	अगर (flow->deficit <= 0) अणु
		/* Keep all flows with deficits out of the sparse and decaying
		 * rotations.  No non-empty flow can go पूर्णांकo the decaying
		 * rotation, so they can't get deficits
		 */
		अगर (flow->set == CAKE_SET_SPARSE) अणु
			अगर (flow->head) अणु
				b->sparse_flow_count--;
				b->bulk_flow_count++;

				अगर (cake_dsrc(q->flow_mode))
					srchost->srchost_bulk_flow_count++;

				अगर (cake_ddst(q->flow_mode))
					dsthost->dsthost_bulk_flow_count++;

				flow->set = CAKE_SET_BULK;
			पूर्ण अन्यथा अणु
				/* we've moved it to the bulk rotation क्रम
				 * correct deficit accounting but we still want
				 * to count it as a sparse flow, not a bulk one.
				 */
				flow->set = CAKE_SET_SPARSE_WAIT;
			पूर्ण
		पूर्ण

		अगर (cake_dsrc(q->flow_mode))
			host_load = max(host_load, srchost->srchost_bulk_flow_count);

		अगर (cake_ddst(q->flow_mode))
			host_load = max(host_load, dsthost->dsthost_bulk_flow_count);

		WARN_ON(host_load > CAKE_QUEUES);

		/* The shअगरted pअक्रमom_u32() is a way to apply dithering to
		 * aव्योम accumulating rounकरोff errors
		 */
		flow->deficit += (b->flow_quantum * quantum_भाग[host_load] +
				  (pअक्रमom_u32() >> 16)) >> 16;
		list_move_tail(&flow->flowchain, &b->old_flows);

		जाओ retry;
	पूर्ण

	/* Retrieve a packet via the AQM */
	जबतक (1) अणु
		skb = cake_dequeue_one(sch);
		अगर (!skb) अणु
			/* this queue was actually empty */
			अगर (cobalt_queue_empty(&flow->cvars, &b->cparams, now))
				b->unresponsive_flow_count--;

			अगर (flow->cvars.p_drop || flow->cvars.count ||
			    kसमय_beक्रमe(now, flow->cvars.drop_next)) अणु
				/* keep in the flowchain until the state has
				 * decayed to rest
				 */
				list_move_tail(&flow->flowchain,
					       &b->decaying_flows);
				अगर (flow->set == CAKE_SET_BULK) अणु
					b->bulk_flow_count--;

					अगर (cake_dsrc(q->flow_mode))
						srchost->srchost_bulk_flow_count--;

					अगर (cake_ddst(q->flow_mode))
						dsthost->dsthost_bulk_flow_count--;

					b->decaying_flow_count++;
				पूर्ण अन्यथा अगर (flow->set == CAKE_SET_SPARSE ||
					   flow->set == CAKE_SET_SPARSE_WAIT) अणु
					b->sparse_flow_count--;
					b->decaying_flow_count++;
				पूर्ण
				flow->set = CAKE_SET_DECAYING;
			पूर्ण अन्यथा अणु
				/* हटाओ empty queue from the flowchain */
				list_del_init(&flow->flowchain);
				अगर (flow->set == CAKE_SET_SPARSE ||
				    flow->set == CAKE_SET_SPARSE_WAIT)
					b->sparse_flow_count--;
				अन्यथा अगर (flow->set == CAKE_SET_BULK) अणु
					b->bulk_flow_count--;

					अगर (cake_dsrc(q->flow_mode))
						srchost->srchost_bulk_flow_count--;

					अगर (cake_ddst(q->flow_mode))
						dsthost->dsthost_bulk_flow_count--;

				पूर्ण अन्यथा
					b->decaying_flow_count--;

				flow->set = CAKE_SET_NONE;
			पूर्ण
			जाओ begin;
		पूर्ण

		/* Last packet in queue may be marked, shouldn't be dropped */
		अगर (!cobalt_should_drop(&flow->cvars, &b->cparams, now, skb,
					(b->bulk_flow_count *
					 !!(q->rate_flags &
					    CAKE_FLAG_INGRESS))) ||
		    !flow->head)
			अवरोध;

		/* drop this packet, get another one */
		अगर (q->rate_flags & CAKE_FLAG_INGRESS) अणु
			len = cake_advance_shaper(q, b, skb,
						  now, true);
			flow->deficit -= len;
			b->tin_deficit -= len;
		पूर्ण
		flow->dropped++;
		b->tin_dropped++;
		qdisc_tree_reduce_backlog(sch, 1, qdisc_pkt_len(skb));
		qdisc_qstats_drop(sch);
		kमुक्त_skb(skb);
		अगर (q->rate_flags & CAKE_FLAG_INGRESS)
			जाओ retry;
	पूर्ण

	b->tin_ecn_mark += !!flow->cvars.ecn_marked;
	qdisc_bstats_update(sch, skb);

	/* collect delay stats */
	delay = kसमय_प्रकारo_ns(kसमय_sub(now, cobalt_get_enqueue_समय(skb)));
	b->avge_delay = cake_ewma(b->avge_delay, delay, 8);
	b->peak_delay = cake_ewma(b->peak_delay, delay,
				  delay > b->peak_delay ? 2 : 8);
	b->base_delay = cake_ewma(b->base_delay, delay,
				  delay < b->base_delay ? 2 : 8);

	len = cake_advance_shaper(q, b, skb, now, false);
	flow->deficit -= len;
	b->tin_deficit -= len;

	अगर (kसमय_after(q->समय_next_packet, now) && sch->q.qlen) अणु
		u64 next = min(kसमय_प्रकारo_ns(q->समय_next_packet),
			       kसमय_प्रकारo_ns(q->failsafe_next_packet));

		qdisc_watchकरोg_schedule_ns(&q->watchकरोg, next);
	पूर्ण अन्यथा अगर (!sch->q.qlen) अणु
		पूर्णांक i;

		क्रम (i = 0; i < q->tin_cnt; i++) अणु
			अगर (q->tins[i].decaying_flow_count) अणु
				kसमय_प्रकार next = \
					kसमय_add_ns(now,
						     q->tins[i].cparams.target);

				qdisc_watchकरोg_schedule_ns(&q->watchकरोg,
							   kसमय_प्रकारo_ns(next));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (q->overflow_समयout)
		q->overflow_समयout--;

	वापस skb;
पूर्ण

अटल व्योम cake_reset(काष्ठा Qdisc *sch)
अणु
	u32 c;

	क्रम (c = 0; c < CAKE_MAX_TINS; c++)
		cake_clear_tin(sch, c);
पूर्ण

अटल स्थिर काष्ठा nla_policy cake_policy[TCA_CAKE_MAX + 1] = अणु
	[TCA_CAKE_BASE_RATE64]   = अणु .type = NLA_U64 पूर्ण,
	[TCA_CAKE_DIFFSERV_MODE] = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_ATM]		 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_FLOW_MODE]     = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_OVERHEAD]      = अणु .type = NLA_S32 पूर्ण,
	[TCA_CAKE_RTT]		 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_TARGET]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_AUTORATE]      = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_MEMORY]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_NAT]		 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_RAW]		 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_WASH]		 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_MPU]		 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_INGRESS]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_ACK_FILTER]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_SPLIT_GSO]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_CAKE_FWMARK]	 = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल व्योम cake_set_rate(काष्ठा cake_tin_data *b, u64 rate, u32 mtu,
			  u64 target_ns, u64 rtt_est_ns)
अणु
	/* convert byte-rate पूर्णांकo समय-per-byte
	 * so it will always unwedge in reasonable समय.
	 */
	अटल स्थिर u64 MIN_RATE = 64;
	u32 byte_target = mtu;
	u64 byte_target_ns;
	u8  rate_shft = 0;
	u64 rate_ns = 0;

	b->flow_quantum = 1514;
	अगर (rate) अणु
		b->flow_quantum = max(min(rate >> 12, 1514ULL), 300ULL);
		rate_shft = 34;
		rate_ns = ((u64)NSEC_PER_SEC) << rate_shft;
		rate_ns = भाग64_u64(rate_ns, max(MIN_RATE, rate));
		जबतक (!!(rate_ns >> 34)) अणु
			rate_ns >>= 1;
			rate_shft--;
		पूर्ण
	पूर्ण /* अन्यथा unlimited, ie. zero delay */

	b->tin_rate_bps  = rate;
	b->tin_rate_ns   = rate_ns;
	b->tin_rate_shft = rate_shft;

	byte_target_ns = (byte_target * rate_ns) >> rate_shft;

	b->cparams.target = max((byte_target_ns * 3) / 2, target_ns);
	b->cparams.पूर्णांकerval = max(rtt_est_ns +
				     b->cparams.target - target_ns,
				     b->cparams.target * 2);
	b->cparams.mtu_समय = byte_target_ns;
	b->cparams.p_inc = 1 << 24; /* 1/256 */
	b->cparams.p_dec = 1 << 20; /* 1/4096 */
पूर्ण

अटल पूर्णांक cake_config_bestefक्रमt(काष्ठा Qdisc *sch)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	काष्ठा cake_tin_data *b = &q->tins[0];
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 rate = q->rate_bps;

	q->tin_cnt = 1;

	q->tin_index = bestefक्रमt;
	q->tin_order = normal_order;

	cake_set_rate(b, rate, mtu,
		      us_to_ns(q->target), us_to_ns(q->पूर्णांकerval));
	b->tin_quantum = 65535;

	वापस 0;
पूर्ण

अटल पूर्णांक cake_config_precedence(काष्ठा Qdisc *sch)
अणु
	/* convert high-level (user visible) parameters पूर्णांकo पूर्णांकernal क्रमmat */
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 rate = q->rate_bps;
	u32 quantum = 256;
	u32 i;

	q->tin_cnt = 8;
	q->tin_index = precedence;
	q->tin_order = normal_order;

	क्रम (i = 0; i < q->tin_cnt; i++) अणु
		काष्ठा cake_tin_data *b = &q->tins[i];

		cake_set_rate(b, rate, mtu, us_to_ns(q->target),
			      us_to_ns(q->पूर्णांकerval));

		b->tin_quantum = max_t(u16, 1U, quantum);

		/* calculate next class's parameters */
		rate  *= 7;
		rate >>= 3;

		quantum  *= 7;
		quantum >>= 3;
	पूर्ण

	वापस 0;
पूर्ण

/*	List of known Dअगरfserv codepoपूर्णांकs:
 *
 *	Least Efक्रमt (CS1, LE)
 *	Best Efक्रमt (CS0)
 *	Max Reliability & LLT "Lo" (TOS1)
 *	Max Throughput (TOS2)
 *	Min Delay (TOS4)
 *	LLT "La" (TOS5)
 *	Assured Forwarding 1 (AF1x) - x3
 *	Assured Forwarding 2 (AF2x) - x3
 *	Assured Forwarding 3 (AF3x) - x3
 *	Assured Forwarding 4 (AF4x) - x3
 *	Precedence Class 2 (CS2)
 *	Precedence Class 3 (CS3)
 *	Precedence Class 4 (CS4)
 *	Precedence Class 5 (CS5)
 *	Precedence Class 6 (CS6)
 *	Precedence Class 7 (CS7)
 *	Voice Admit (VA)
 *	Expedited Forwarding (EF)

 *	Total 25 codepoपूर्णांकs.
 */

/*	List of traffic classes in RFC 4594, updated by RFC 8622:
 *		(roughly descending order of contended priority)
 *		(roughly ascending order of uncontended throughput)
 *
 *	Network Control (CS6,CS7)      - routing traffic
 *	Telephony (EF,VA)         - aka. VoIP streams
 *	Signalling (CS5)               - VoIP setup
 *	Mulसमयdia Conferencing (AF4x) - aka. video calls
 *	Realसमय Interactive (CS4)     - eg. games
 *	Mulसमयdia Streaming (AF3x)    - eg. YouTube, NetFlix, Twitch
 *	Broadcast Video (CS3)
 *	Low Latency Data (AF2x,TOS4)      - eg. database
 *	Ops, Admin, Management (CS2,TOS1) - eg. ssh
 *	Standard Service (CS0 & unrecognised codepoपूर्णांकs)
 *	High Throughput Data (AF1x,TOS2)  - eg. web traffic
 *	Low Priority Data (CS1,LE)        - eg. BitTorrent

 *	Total 12 traffic classes.
 */

अटल पूर्णांक cake_config_dअगरfserv8(काष्ठा Qdisc *sch)
अणु
/*	Pruned list of traffic classes क्रम typical applications:
 *
 *		Network Control          (CS6, CS7)
 *		Minimum Latency          (EF, VA, CS5, CS4)
 *		Interactive Shell        (CS2, TOS1)
 *		Low Latency Transactions (AF2x, TOS4)
 *		Video Streaming          (AF4x, AF3x, CS3)
 *		Bog Standard             (CS0 etc.)
 *		High Throughput          (AF1x, TOS2)
 *		Background Traffic       (CS1, LE)
 *
 *		Total 8 traffic classes.
 */

	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 rate = q->rate_bps;
	u32 quantum = 256;
	u32 i;

	q->tin_cnt = 8;

	/* codepoपूर्णांक to class mapping */
	q->tin_index = dअगरfserv8;
	q->tin_order = normal_order;

	/* class अक्षरacteristics */
	क्रम (i = 0; i < q->tin_cnt; i++) अणु
		काष्ठा cake_tin_data *b = &q->tins[i];

		cake_set_rate(b, rate, mtu, us_to_ns(q->target),
			      us_to_ns(q->पूर्णांकerval));

		b->tin_quantum = max_t(u16, 1U, quantum);

		/* calculate next class's parameters */
		rate  *= 7;
		rate >>= 3;

		quantum  *= 7;
		quantum >>= 3;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cake_config_dअगरfserv4(काष्ठा Qdisc *sch)
अणु
/*  Further pruned list of traffic classes क्रम four-class प्रणाली:
 *
 *	    Latency Sensitive  (CS7, CS6, EF, VA, CS5, CS4)
 *	    Streaming Media    (AF4x, AF3x, CS3, AF2x, TOS4, CS2, TOS1)
 *	    Best Efक्रमt        (CS0, AF1x, TOS2, and those not specअगरied)
 *	    Background Traffic (CS1, LE)
 *
 *		Total 4 traffic classes.
 */

	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 rate = q->rate_bps;
	u32 quantum = 1024;

	q->tin_cnt = 4;

	/* codepoपूर्णांक to class mapping */
	q->tin_index = dअगरfserv4;
	q->tin_order = bulk_order;

	/* class अक्षरacteristics */
	cake_set_rate(&q->tins[0], rate, mtu,
		      us_to_ns(q->target), us_to_ns(q->पूर्णांकerval));
	cake_set_rate(&q->tins[1], rate >> 4, mtu,
		      us_to_ns(q->target), us_to_ns(q->पूर्णांकerval));
	cake_set_rate(&q->tins[2], rate >> 1, mtu,
		      us_to_ns(q->target), us_to_ns(q->पूर्णांकerval));
	cake_set_rate(&q->tins[3], rate >> 2, mtu,
		      us_to_ns(q->target), us_to_ns(q->पूर्णांकerval));

	/* bandwidth-sharing weights */
	q->tins[0].tin_quantum = quantum;
	q->tins[1].tin_quantum = quantum >> 4;
	q->tins[2].tin_quantum = quantum >> 1;
	q->tins[3].tin_quantum = quantum >> 2;

	वापस 0;
पूर्ण

अटल पूर्णांक cake_config_dअगरfserv3(काष्ठा Qdisc *sch)
अणु
/*  Simplअगरied Dअगरfserv काष्ठाure with 3 tins.
 *		Low Priority		(CS1, LE)
 *		Best Efक्रमt
 *		Latency Sensitive	(TOS4, VA, EF, CS6, CS7)
 */
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 rate = q->rate_bps;
	u32 quantum = 1024;

	q->tin_cnt = 3;

	/* codepoपूर्णांक to class mapping */
	q->tin_index = dअगरfserv3;
	q->tin_order = bulk_order;

	/* class अक्षरacteristics */
	cake_set_rate(&q->tins[0], rate, mtu,
		      us_to_ns(q->target), us_to_ns(q->पूर्णांकerval));
	cake_set_rate(&q->tins[1], rate >> 4, mtu,
		      us_to_ns(q->target), us_to_ns(q->पूर्णांकerval));
	cake_set_rate(&q->tins[2], rate >> 2, mtu,
		      us_to_ns(q->target), us_to_ns(q->पूर्णांकerval));

	/* bandwidth-sharing weights */
	q->tins[0].tin_quantum = quantum;
	q->tins[1].tin_quantum = quantum >> 4;
	q->tins[2].tin_quantum = quantum >> 2;

	वापस 0;
पूर्ण

अटल व्योम cake_reconfigure(काष्ठा Qdisc *sch)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	पूर्णांक c, ft;

	चयन (q->tin_mode) अणु
	हाल CAKE_DIFFSERV_BESTEFFORT:
		ft = cake_config_bestefक्रमt(sch);
		अवरोध;

	हाल CAKE_DIFFSERV_PRECEDENCE:
		ft = cake_config_precedence(sch);
		अवरोध;

	हाल CAKE_DIFFSERV_DIFFSERV8:
		ft = cake_config_dअगरfserv8(sch);
		अवरोध;

	हाल CAKE_DIFFSERV_DIFFSERV4:
		ft = cake_config_dअगरfserv4(sch);
		अवरोध;

	हाल CAKE_DIFFSERV_DIFFSERV3:
	शेष:
		ft = cake_config_dअगरfserv3(sch);
		अवरोध;
	पूर्ण

	क्रम (c = q->tin_cnt; c < CAKE_MAX_TINS; c++) अणु
		cake_clear_tin(sch, c);
		q->tins[c].cparams.mtu_समय = q->tins[ft].cparams.mtu_समय;
	पूर्ण

	q->rate_ns   = q->tins[ft].tin_rate_ns;
	q->rate_shft = q->tins[ft].tin_rate_shft;

	अगर (q->buffer_config_limit) अणु
		q->buffer_limit = q->buffer_config_limit;
	पूर्ण अन्यथा अगर (q->rate_bps) अणु
		u64 t = q->rate_bps * q->पूर्णांकerval;

		करो_भाग(t, USEC_PER_SEC / 4);
		q->buffer_limit = max_t(u32, t, 4U << 20);
	पूर्ण अन्यथा अणु
		q->buffer_limit = ~0;
	पूर्ण

	sch->flags &= ~TCQ_F_CAN_BYPASS;

	q->buffer_limit = min(q->buffer_limit,
			      max(sch->limit * psched_mtu(qdisc_dev(sch)),
				  q->buffer_config_limit));
पूर्ण

अटल पूर्णांक cake_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_CAKE_MAX + 1];
	पूर्णांक err;

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_CAKE_MAX, opt, cake_policy,
					  extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_CAKE_NAT]) अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
		q->flow_mode &= ~CAKE_FLOW_NAT_FLAG;
		q->flow_mode |= CAKE_FLOW_NAT_FLAG *
			!!nla_get_u32(tb[TCA_CAKE_NAT]);
#अन्यथा
		NL_SET_ERR_MSG_ATTR(extack, tb[TCA_CAKE_NAT],
				    "No conntrack support in kernel");
		वापस -EOPNOTSUPP;
#पूर्ण_अगर
	पूर्ण

	अगर (tb[TCA_CAKE_BASE_RATE64])
		q->rate_bps = nla_get_u64(tb[TCA_CAKE_BASE_RATE64]);

	अगर (tb[TCA_CAKE_DIFFSERV_MODE])
		q->tin_mode = nla_get_u32(tb[TCA_CAKE_DIFFSERV_MODE]);

	अगर (tb[TCA_CAKE_WASH]) अणु
		अगर (!!nla_get_u32(tb[TCA_CAKE_WASH]))
			q->rate_flags |= CAKE_FLAG_WASH;
		अन्यथा
			q->rate_flags &= ~CAKE_FLAG_WASH;
	पूर्ण

	अगर (tb[TCA_CAKE_FLOW_MODE])
		q->flow_mode = ((q->flow_mode & CAKE_FLOW_NAT_FLAG) |
				(nla_get_u32(tb[TCA_CAKE_FLOW_MODE]) &
					CAKE_FLOW_MASK));

	अगर (tb[TCA_CAKE_ATM])
		q->aपंचांग_mode = nla_get_u32(tb[TCA_CAKE_ATM]);

	अगर (tb[TCA_CAKE_OVERHEAD]) अणु
		q->rate_overhead = nla_get_s32(tb[TCA_CAKE_OVERHEAD]);
		q->rate_flags |= CAKE_FLAG_OVERHEAD;

		q->max_netlen = 0;
		q->max_adjlen = 0;
		q->min_netlen = ~0;
		q->min_adjlen = ~0;
	पूर्ण

	अगर (tb[TCA_CAKE_RAW]) अणु
		q->rate_flags &= ~CAKE_FLAG_OVERHEAD;

		q->max_netlen = 0;
		q->max_adjlen = 0;
		q->min_netlen = ~0;
		q->min_adjlen = ~0;
	पूर्ण

	अगर (tb[TCA_CAKE_MPU])
		q->rate_mpu = nla_get_u32(tb[TCA_CAKE_MPU]);

	अगर (tb[TCA_CAKE_RTT]) अणु
		q->पूर्णांकerval = nla_get_u32(tb[TCA_CAKE_RTT]);

		अगर (!q->पूर्णांकerval)
			q->पूर्णांकerval = 1;
	पूर्ण

	अगर (tb[TCA_CAKE_TARGET]) अणु
		q->target = nla_get_u32(tb[TCA_CAKE_TARGET]);

		अगर (!q->target)
			q->target = 1;
	पूर्ण

	अगर (tb[TCA_CAKE_AUTORATE]) अणु
		अगर (!!nla_get_u32(tb[TCA_CAKE_AUTORATE]))
			q->rate_flags |= CAKE_FLAG_AUTORATE_INGRESS;
		अन्यथा
			q->rate_flags &= ~CAKE_FLAG_AUTORATE_INGRESS;
	पूर्ण

	अगर (tb[TCA_CAKE_INGRESS]) अणु
		अगर (!!nla_get_u32(tb[TCA_CAKE_INGRESS]))
			q->rate_flags |= CAKE_FLAG_INGRESS;
		अन्यथा
			q->rate_flags &= ~CAKE_FLAG_INGRESS;
	पूर्ण

	अगर (tb[TCA_CAKE_ACK_FILTER])
		q->ack_filter = nla_get_u32(tb[TCA_CAKE_ACK_FILTER]);

	अगर (tb[TCA_CAKE_MEMORY])
		q->buffer_config_limit = nla_get_u32(tb[TCA_CAKE_MEMORY]);

	अगर (tb[TCA_CAKE_SPLIT_GSO]) अणु
		अगर (!!nla_get_u32(tb[TCA_CAKE_SPLIT_GSO]))
			q->rate_flags |= CAKE_FLAG_SPLIT_GSO;
		अन्यथा
			q->rate_flags &= ~CAKE_FLAG_SPLIT_GSO;
	पूर्ण

	अगर (tb[TCA_CAKE_FWMARK]) अणु
		q->fwmark_mask = nla_get_u32(tb[TCA_CAKE_FWMARK]);
		q->fwmark_shft = q->fwmark_mask ? __ffs(q->fwmark_mask) : 0;
	पूर्ण

	अगर (q->tins) अणु
		sch_tree_lock(sch);
		cake_reconfigure(sch);
		sch_tree_unlock(sch);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cake_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);

	qdisc_watchकरोg_cancel(&q->watchकरोg);
	tcf_block_put(q->block);
	kvमुक्त(q->tins);
पूर्ण

अटल पूर्णांक cake_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	पूर्णांक i, j, err;

	sch->limit = 10240;
	q->tin_mode = CAKE_DIFFSERV_DIFFSERV3;
	q->flow_mode  = CAKE_FLOW_TRIPLE;

	q->rate_bps = 0; /* unlimited by शेष */

	q->पूर्णांकerval = 100000; /* 100ms शेष */
	q->target   =   5000; /* 5ms: codel RFC argues
			       * क्रम 5 to 10% of पूर्णांकerval
			       */
	q->rate_flags |= CAKE_FLAG_SPLIT_GSO;
	q->cur_tin = 0;
	q->cur_flow  = 0;

	qdisc_watchकरोg_init(&q->watchकरोg, sch);

	अगर (opt) अणु
		err = cake_change(sch, opt, extack);

		अगर (err)
			वापस err;
	पूर्ण

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		वापस err;

	quantum_भाग[0] = ~0;
	क्रम (i = 1; i <= CAKE_QUEUES; i++)
		quantum_भाग[i] = 65535 / i;

	q->tins = kvसुस्मृति(CAKE_MAX_TINS, माप(काष्ठा cake_tin_data),
			   GFP_KERNEL);
	अगर (!q->tins)
		जाओ nomem;

	क्रम (i = 0; i < CAKE_MAX_TINS; i++) अणु
		काष्ठा cake_tin_data *b = q->tins + i;

		INIT_LIST_HEAD(&b->new_flows);
		INIT_LIST_HEAD(&b->old_flows);
		INIT_LIST_HEAD(&b->decaying_flows);
		b->sparse_flow_count = 0;
		b->bulk_flow_count = 0;
		b->decaying_flow_count = 0;

		क्रम (j = 0; j < CAKE_QUEUES; j++) अणु
			काष्ठा cake_flow *flow = b->flows + j;
			u32 k = j * CAKE_MAX_TINS + i;

			INIT_LIST_HEAD(&flow->flowchain);
			cobalt_vars_init(&flow->cvars);

			q->overflow_heap[k].t = i;
			q->overflow_heap[k].b = j;
			b->overflow_idx[j] = k;
		पूर्ण
	पूर्ण

	cake_reconfigure(sch);
	q->avg_peak_bandwidth = q->rate_bps;
	q->min_netlen = ~0;
	q->min_adjlen = ~0;
	वापस 0;

nomem:
	cake_destroy(sch);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक cake_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!opts)
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(skb, TCA_CAKE_BASE_RATE64, q->rate_bps,
			      TCA_CAKE_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_FLOW_MODE,
			q->flow_mode & CAKE_FLOW_MASK))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_RTT, q->पूर्णांकerval))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_TARGET, q->target))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_MEMORY, q->buffer_config_limit))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_AUTORATE,
			!!(q->rate_flags & CAKE_FLAG_AUTORATE_INGRESS)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_INGRESS,
			!!(q->rate_flags & CAKE_FLAG_INGRESS)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_ACK_FILTER, q->ack_filter))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_NAT,
			!!(q->flow_mode & CAKE_FLOW_NAT_FLAG)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_DIFFSERV_MODE, q->tin_mode))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_WASH,
			!!(q->rate_flags & CAKE_FLAG_WASH)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_OVERHEAD, q->rate_overhead))
		जाओ nla_put_failure;

	अगर (!(q->rate_flags & CAKE_FLAG_OVERHEAD))
		अगर (nla_put_u32(skb, TCA_CAKE_RAW, 0))
			जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_ATM, q->aपंचांग_mode))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_MPU, q->rate_mpu))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_SPLIT_GSO,
			!!(q->rate_flags & CAKE_FLAG_SPLIT_GSO)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CAKE_FWMARK, q->fwmark_mask))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, opts);

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक cake_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा nlattr *stats = nla_nest_start_noflag(d->skb, TCA_STATS_APP);
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tstats, *ts;
	पूर्णांक i;

	अगर (!stats)
		वापस -1;

#घोषणा PUT_STAT_U32(attr, data) करो अणु				       \
		अगर (nla_put_u32(d->skb, TCA_CAKE_STATS_ ## attr, data)) \
			जाओ nla_put_failure;			       \
	पूर्ण जबतक (0)
#घोषणा PUT_STAT_U64(attr, data) करो अणु				       \
		अगर (nla_put_u64_64bit(d->skb, TCA_CAKE_STATS_ ## attr, \
					data, TCA_CAKE_STATS_PAD)) \
			जाओ nla_put_failure;			       \
	पूर्ण जबतक (0)

	PUT_STAT_U64(CAPACITY_ESTIMATE64, q->avg_peak_bandwidth);
	PUT_STAT_U32(MEMORY_LIMIT, q->buffer_limit);
	PUT_STAT_U32(MEMORY_USED, q->buffer_max_used);
	PUT_STAT_U32(AVG_NETOFF, ((q->avg_netoff + 0x8000) >> 16));
	PUT_STAT_U32(MAX_NETLEN, q->max_netlen);
	PUT_STAT_U32(MAX_ADJLEN, q->max_adjlen);
	PUT_STAT_U32(MIN_NETLEN, q->min_netlen);
	PUT_STAT_U32(MIN_ADJLEN, q->min_adjlen);

#अघोषित PUT_STAT_U32
#अघोषित PUT_STAT_U64

	tstats = nla_nest_start_noflag(d->skb, TCA_CAKE_STATS_TIN_STATS);
	अगर (!tstats)
		जाओ nla_put_failure;

#घोषणा PUT_TSTAT_U32(attr, data) करो अणु					\
		अगर (nla_put_u32(d->skb, TCA_CAKE_TIN_STATS_ ## attr, data)) \
			जाओ nla_put_failure;				\
	पूर्ण जबतक (0)
#घोषणा PUT_TSTAT_U64(attr, data) करो अणु					\
		अगर (nla_put_u64_64bit(d->skb, TCA_CAKE_TIN_STATS_ ## attr, \
					data, TCA_CAKE_TIN_STATS_PAD))	\
			जाओ nla_put_failure;				\
	पूर्ण जबतक (0)

	क्रम (i = 0; i < q->tin_cnt; i++) अणु
		काष्ठा cake_tin_data *b = &q->tins[q->tin_order[i]];

		ts = nla_nest_start_noflag(d->skb, i + 1);
		अगर (!ts)
			जाओ nla_put_failure;

		PUT_TSTAT_U64(THRESHOLD_RATE64, b->tin_rate_bps);
		PUT_TSTAT_U64(SENT_BYTES64, b->bytes);
		PUT_TSTAT_U32(BACKLOG_BYTES, b->tin_backlog);

		PUT_TSTAT_U32(TARGET_US,
			      kसमय_प्रकारo_us(ns_to_kसमय(b->cparams.target)));
		PUT_TSTAT_U32(INTERVAL_US,
			      kसमय_प्रकारo_us(ns_to_kसमय(b->cparams.पूर्णांकerval)));

		PUT_TSTAT_U32(SENT_PACKETS, b->packets);
		PUT_TSTAT_U32(DROPPED_PACKETS, b->tin_dropped);
		PUT_TSTAT_U32(ECN_MARKED_PACKETS, b->tin_ecn_mark);
		PUT_TSTAT_U32(ACKS_DROPPED_PACKETS, b->ack_drops);

		PUT_TSTAT_U32(PEAK_DELAY_US,
			      kसमय_प्रकारo_us(ns_to_kसमय(b->peak_delay)));
		PUT_TSTAT_U32(AVG_DELAY_US,
			      kसमय_प्रकारo_us(ns_to_kसमय(b->avge_delay)));
		PUT_TSTAT_U32(BASE_DELAY_US,
			      kसमय_प्रकारo_us(ns_to_kसमय(b->base_delay)));

		PUT_TSTAT_U32(WAY_INसूचीECT_HITS, b->way_hits);
		PUT_TSTAT_U32(WAY_MISSES, b->way_misses);
		PUT_TSTAT_U32(WAY_COLLISIONS, b->way_collisions);

		PUT_TSTAT_U32(SPARSE_FLOWS, b->sparse_flow_count +
					    b->decaying_flow_count);
		PUT_TSTAT_U32(BULK_FLOWS, b->bulk_flow_count);
		PUT_TSTAT_U32(UNRESPONSIVE_FLOWS, b->unresponsive_flow_count);
		PUT_TSTAT_U32(MAX_SKBLEN, b->max_skblen);

		PUT_TSTAT_U32(FLOW_QUANTUM, b->flow_quantum);
		nla_nest_end(d->skb, ts);
	पूर्ण

#अघोषित PUT_TSTAT_U32
#अघोषित PUT_TSTAT_U64

	nla_nest_end(d->skb, tstats);
	वापस nla_nest_end(d->skb, stats);

nla_put_failure:
	nla_nest_cancel(d->skb, stats);
	वापस -1;
पूर्ण

अटल काष्ठा Qdisc *cake_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ cake_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ cake_bind(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
			       u32 classid)
अणु
	वापस 0;
पूर्ण

अटल व्योम cake_unbind(काष्ठा Qdisc *q, अचिन्हित दीर्घ cl)
अणु
पूर्ण

अटल काष्ठा tcf_block *cake_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);

	अगर (cl)
		वापस शून्य;
	वापस q->block;
पूर्ण

अटल पूर्णांक cake_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			   काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	tcm->tcm_handle |= TC_H_MIN(cl);
	वापस 0;
पूर्ण

अटल पूर्णांक cake_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				 काष्ठा gnet_dump *d)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	स्थिर काष्ठा cake_flow *flow = शून्य;
	काष्ठा gnet_stats_queue qs = अणु 0 पूर्ण;
	काष्ठा nlattr *stats;
	u32 idx = cl - 1;

	अगर (idx < CAKE_QUEUES * q->tin_cnt) अणु
		स्थिर काष्ठा cake_tin_data *b = \
			&q->tins[q->tin_order[idx / CAKE_QUEUES]];
		स्थिर काष्ठा sk_buff *skb;

		flow = &b->flows[idx % CAKE_QUEUES];

		अगर (flow->head) अणु
			sch_tree_lock(sch);
			skb = flow->head;
			जबतक (skb) अणु
				qs.qlen++;
				skb = skb->next;
			पूर्ण
			sch_tree_unlock(sch);
		पूर्ण
		qs.backlog = b->backlogs[idx % CAKE_QUEUES];
		qs.drops = flow->dropped;
	पूर्ण
	अगर (gnet_stats_copy_queue(d, शून्य, &qs, qs.qlen) < 0)
		वापस -1;
	अगर (flow) अणु
		kसमय_प्रकार now = kसमय_get();

		stats = nla_nest_start_noflag(d->skb, TCA_STATS_APP);
		अगर (!stats)
			वापस -1;

#घोषणा PUT_STAT_U32(attr, data) करो अणु				       \
		अगर (nla_put_u32(d->skb, TCA_CAKE_STATS_ ## attr, data)) \
			जाओ nla_put_failure;			       \
	पूर्ण जबतक (0)
#घोषणा PUT_STAT_S32(attr, data) करो अणु				       \
		अगर (nla_put_s32(d->skb, TCA_CAKE_STATS_ ## attr, data)) \
			जाओ nla_put_failure;			       \
	पूर्ण जबतक (0)

		PUT_STAT_S32(DEFICIT, flow->deficit);
		PUT_STAT_U32(DROPPING, flow->cvars.dropping);
		PUT_STAT_U32(COBALT_COUNT, flow->cvars.count);
		PUT_STAT_U32(P_DROP, flow->cvars.p_drop);
		अगर (flow->cvars.p_drop) अणु
			PUT_STAT_S32(BLUE_TIMER_US,
				     kसमय_प्रकारo_us(
					     kसमय_sub(now,
						       flow->cvars.blue_समयr)));
		पूर्ण
		अगर (flow->cvars.dropping) अणु
			PUT_STAT_S32(DROP_NEXT_US,
				     kसमय_प्रकारo_us(
					     kसमय_sub(now,
						       flow->cvars.drop_next)));
		पूर्ण

		अगर (nla_nest_end(d->skb, stats) < 0)
			वापस -1;
	पूर्ण

	वापस 0;

nla_put_failure:
	nla_nest_cancel(d->skb, stats);
	वापस -1;
पूर्ण

अटल व्योम cake_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा cake_sched_data *q = qdisc_priv(sch);
	अचिन्हित पूर्णांक i, j;

	अगर (arg->stop)
		वापस;

	क्रम (i = 0; i < q->tin_cnt; i++) अणु
		काष्ठा cake_tin_data *b = &q->tins[q->tin_order[i]];

		क्रम (j = 0; j < CAKE_QUEUES; j++) अणु
			अगर (list_empty(&b->flows[j].flowchain) ||
			    arg->count < arg->skip) अणु
				arg->count++;
				जारी;
			पूर्ण
			अगर (arg->fn(sch, i * CAKE_QUEUES + j + 1, arg) < 0) अणु
				arg->stop = 1;
				अवरोध;
			पूर्ण
			arg->count++;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops cake_class_ops = अणु
	.leaf		=	cake_leaf,
	.find		=	cake_find,
	.tcf_block	=	cake_tcf_block,
	.bind_tcf	=	cake_bind,
	.unbind_tcf	=	cake_unbind,
	.dump		=	cake_dump_class,
	.dump_stats	=	cake_dump_class_stats,
	.walk		=	cake_walk,
पूर्ण;

अटल काष्ठा Qdisc_ops cake_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		=	&cake_class_ops,
	.id		=	"cake",
	.priv_size	=	माप(काष्ठा cake_sched_data),
	.enqueue	=	cake_enqueue,
	.dequeue	=	cake_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	cake_init,
	.reset		=	cake_reset,
	.destroy	=	cake_destroy,
	.change		=	cake_change,
	.dump		=	cake_dump,
	.dump_stats	=	cake_dump_stats,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init cake_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&cake_qdisc_ops);
पूर्ण

अटल व्योम __निकास cake_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&cake_qdisc_ops);
पूर्ण

module_init(cake_module_init)
module_निकास(cake_module_निकास)
MODULE_AUTHOR("Jonathan Morton");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("The CAKE shaper.");
