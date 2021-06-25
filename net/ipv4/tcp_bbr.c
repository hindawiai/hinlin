<शैली गुरु>
/* Bottleneck Bandwidth and RTT (BBR) congestion control
 *
 * BBR congestion control computes the sending rate based on the delivery
 * rate (throughput) estimated from ACKs. In a nutshell:
 *
 *   On each ACK, update our model of the network path:
 *      bottleneck_bandwidth = winकरोwed_max(delivered / elapsed, 10 round trips)
 *      min_rtt = winकरोwed_min(rtt, 10 seconds)
 *   pacing_rate = pacing_gain * bottleneck_bandwidth
 *   cwnd = max(cwnd_gain * bottleneck_bandwidth * min_rtt, 4)
 *
 * The core algorithm करोes not react directly to packet losses or delays,
 * although BBR may adjust the size of next send per ACK when loss is
 * observed, or adjust the sending rate अगर it estimates there is a
 * traffic policer, in order to keep the drop rate reasonable.
 *
 * Here is a state transition diagram क्रम BBR:
 *
 *             |
 *             V
 *    +---> STARTUP  ----+
 *    |        |         |
 *    |        V         |
 *    |      DRAIN   ----+
 *    |        |         |
 *    |        V         |
 *    +---> PROBE_BW ----+
 *    |      ^    |      |
 *    |      |    |      |
 *    |      +----+      |
 *    |                  |
 *    +---- PROBE_RTT <--+
 *
 * A BBR flow starts in STARTUP, and ramps up its sending rate quickly.
 * When it estimates the pipe is full, it enters DRAIN to drain the queue.
 * In steady state a BBR flow only uses PROBE_BW and PROBE_RTT.
 * A दीर्घ-lived BBR flow spends the vast majority of its समय reमुख्यing
 * (repeatedly) in PROBE_BW, fully probing and utilizing the pipe's bandwidth
 * in a fair manner, with a small, bounded queue. *If* a flow has been
 * continuously sending क्रम the entire min_rtt winकरोw, and hasn't seen an RTT
 * sample that matches or decreases its min_rtt estimate क्रम 10 seconds, then
 * it briefly enters PROBE_RTT to cut inflight to a minimum value to re-probe
 * the path's two-way propagation delay (min_rtt). When निकासing PROBE_RTT, अगर
 * we estimated that we reached the full bw of the pipe then we enter PROBE_BW;
 * otherwise we enter STARTUP to try to fill the pipe.
 *
 * BBR is described in detail in:
 *   "BBR: Congestion-Based Congestion Control",
 *   Neal Cardwell, Yuchung Cheng, C. Stephen Gunn, Soheil Hassas Yeganeh,
 *   Van Jacobson. ACM Queue, Vol. 14 No. 5, September-October 2016.
 *
 * There is a खुला e-mail list क्रम discussing BBR development and testing:
 *   https://groups.google.com/क्रमum/#!क्रमum/bbr-dev
 *
 * NOTE: BBR might be used with the fq qdisc ("man tc-fq") with pacing enabled,
 * otherwise TCP stack falls back to an पूर्णांकernal pacing using one high
 * resolution समयr per TCP socket and may use more resources.
 */
#समावेश <linux/module.h>
#समावेश <net/tcp.h>
#समावेश <linux/inet_diag.h>
#समावेश <linux/inet.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/win_minmax.h>

/* Scale factor क्रम rate in pkt/uSec unit to aव्योम truncation in bandwidth
 * estimation. The rate unit ~= (1500 bytes / 1 usec / 2^24) ~= 715 bps.
 * This handles bandwidths from 0.06pps (715bps) to 256Mpps (3Tbps) in a u32.
 * Since the minimum winकरोw is >=4 packets, the lower bound isn't
 * an issue. The upper bound isn't an issue with existing technologies.
 */
#घोषणा BW_SCALE 24
#घोषणा BW_UNIT (1 << BW_SCALE)

#घोषणा BBR_SCALE 8	/* scaling factor क्रम fractions in BBR (e.g. gains) */
#घोषणा BBR_UNIT (1 << BBR_SCALE)

/* BBR has the following modes क्रम deciding how fast to send: */
क्रमागत bbr_mode अणु
	BBR_STARTUP,	/* ramp up sending rate rapidly to fill pipe */
	BBR_DRAIN,	/* drain any queue created during startup */
	BBR_PROBE_BW,	/* discover, share bw: pace around estimated bw */
	BBR_PROBE_RTT,	/* cut inflight to min to probe min_rtt */
पूर्ण;

/* BBR congestion control block */
काष्ठा bbr अणु
	u32	min_rtt_us;	        /* min RTT in min_rtt_win_sec winकरोw */
	u32	min_rtt_stamp;	        /* बारtamp of min_rtt_us */
	u32	probe_rtt_करोne_stamp;   /* end समय क्रम BBR_PROBE_RTT mode */
	काष्ठा minmax bw;	/* Max recent delivery rate in pkts/uS << 24 */
	u32	rtt_cnt;	    /* count of packet-समयd rounds elapsed */
	u32     next_rtt_delivered; /* scb->tx.delivered at end of round */
	u64	cycle_mstamp;	     /* समय of this cycle phase start */
	u32     mode:3,		     /* current bbr_mode in state machine */
		prev_ca_state:3,     /* CA state on previous ACK */
		packet_conservation:1,  /* use packet conservation? */
		round_start:1,	     /* start of packet-समयd tx->ack round? */
		idle_restart:1,	     /* restarting after idle? */
		probe_rtt_round_करोne:1,  /* a BBR_PROBE_RTT round at 4 pkts? */
		unused:13,
		lt_is_sampling:1,    /* taking दीर्घ-term ("LT") samples now? */
		lt_rtt_cnt:7,	     /* round trips in दीर्घ-term पूर्णांकerval */
		lt_use_bw:1;	     /* use lt_bw as our bw estimate? */
	u32	lt_bw;		     /* LT est delivery rate in pkts/uS << 24 */
	u32	lt_last_delivered;   /* LT पूर्णांकvl start: tp->delivered */
	u32	lt_last_stamp;	     /* LT पूर्णांकvl start: tp->delivered_mstamp */
	u32	lt_last_lost;	     /* LT पूर्णांकvl start: tp->lost */
	u32	pacing_gain:10,	/* current gain क्रम setting pacing rate */
		cwnd_gain:10,	/* current gain क्रम setting cwnd */
		full_bw_reached:1,   /* reached full bw in Startup? */
		full_bw_cnt:2,	/* number of rounds without large bw gains */
		cycle_idx:3,	/* current index in pacing_gain cycle array */
		has_seen_rtt:1, /* have we seen an RTT sample yet? */
		unused_b:5;
	u32	prior_cwnd;	/* prior cwnd upon entering loss recovery */
	u32	full_bw;	/* recent bw, to estimate अगर pipe is full */

	/* For tracking ACK aggregation: */
	u64	ack_epoch_mstamp;	/* start of ACK sampling epoch */
	u16	extra_acked[2];		/* max excess data ACKed in epoch */
	u32	ack_epoch_acked:20,	/* packets (S)ACKed in sampling epoch */
		extra_acked_win_rtts:5,	/* age of extra_acked, in round trips */
		extra_acked_win_idx:1,	/* current index in extra_acked array */
		unused_c:6;
पूर्ण;

#घोषणा CYCLE_LEN	8	/* number of phases in a pacing gain cycle */

/* Winकरोw length of bw filter (in rounds): */
अटल स्थिर पूर्णांक bbr_bw_rtts = CYCLE_LEN + 2;
/* Winकरोw length of min_rtt filter (in sec): */
अटल स्थिर u32 bbr_min_rtt_win_sec = 10;
/* Minimum समय (in ms) spent at bbr_cwnd_min_target in BBR_PROBE_RTT mode: */
अटल स्थिर u32 bbr_probe_rtt_mode_ms = 200;
/* Skip TSO below the following bandwidth (bits/sec): */
अटल स्थिर पूर्णांक bbr_min_tso_rate = 1200000;

/* Pace at ~1% below estimated bw, on average, to reduce queue at bottleneck.
 * In order to help drive the network toward lower queues and low latency जबतक
 * मुख्यtaining high utilization, the average pacing rate aims to be slightly
 * lower than the estimated bandwidth. This is an important aspect of the
 * design.
 */
अटल स्थिर पूर्णांक bbr_pacing_margin_percent = 1;

/* We use a high_gain value of 2/ln(2) because it's the smallest pacing gain
 * that will allow a smoothly increasing pacing rate that will द्विगुन each RTT
 * and send the same number of packets per RTT that an un-paced, slow-starting
 * Reno or CUBIC flow would:
 */
अटल स्थिर पूर्णांक bbr_high_gain  = BBR_UNIT * 2885 / 1000 + 1;
/* The pacing gain of 1/high_gain in BBR_DRAIN is calculated to typically drain
 * the queue created in BBR_STARTUP in a single round:
 */
अटल स्थिर पूर्णांक bbr_drain_gain = BBR_UNIT * 1000 / 2885;
/* The gain क्रम deriving steady-state cwnd tolerates delayed/stretched ACKs: */
अटल स्थिर पूर्णांक bbr_cwnd_gain  = BBR_UNIT * 2;
/* The pacing_gain values क्रम the PROBE_BW gain cycle, to discover/share bw: */
अटल स्थिर पूर्णांक bbr_pacing_gain[] = अणु
	BBR_UNIT * 5 / 4,	/* probe क्रम more available bw */
	BBR_UNIT * 3 / 4,	/* drain queue and/or yield bw to other flows */
	BBR_UNIT, BBR_UNIT, BBR_UNIT,	/* cruise at 1.0*bw to utilize pipe, */
	BBR_UNIT, BBR_UNIT, BBR_UNIT	/* without creating excess queue... */
पूर्ण;
/* Ranकरोmize the starting gain cycling phase over N phases: */
अटल स्थिर u32 bbr_cycle_अक्रम = 7;

/* Try to keep at least this many packets in flight, अगर things go smoothly. For
 * smooth functioning, a sliding winकरोw protocol ACKing every other packet
 * needs at least 4 packets in flight:
 */
अटल स्थिर u32 bbr_cwnd_min_target = 4;

/* To estimate अगर BBR_STARTUP mode (i.e. high_gain) has filled pipe... */
/* If bw has increased signअगरicantly (1.25x), there may be more bw available: */
अटल स्थिर u32 bbr_full_bw_thresh = BBR_UNIT * 5 / 4;
/* But after 3 rounds w/o signअगरicant bw growth, estimate pipe is full: */
अटल स्थिर u32 bbr_full_bw_cnt = 3;

/* "long-term" ("LT") bandwidth estimator parameters... */
/* The minimum number of rounds in an LT bw sampling पूर्णांकerval: */
अटल स्थिर u32 bbr_lt_पूर्णांकvl_min_rtts = 4;
/* If lost/delivered ratio > 20%, पूर्णांकerval is "lossy" and we may be policed: */
अटल स्थिर u32 bbr_lt_loss_thresh = 50;
/* If 2 पूर्णांकervals have a bw ratio <= 1/8, their bw is "consistent": */
अटल स्थिर u32 bbr_lt_bw_ratio = BBR_UNIT / 8;
/* If 2 पूर्णांकervals have a bw dअगरf <= 4 Kbit/sec their bw is "consistent": */
अटल स्थिर u32 bbr_lt_bw_dअगरf = 4000 / 8;
/* If we estimate we're policed, use lt_bw क्रम this many round trips: */
अटल स्थिर u32 bbr_lt_bw_max_rtts = 48;

/* Gain factor क्रम adding extra_acked to target cwnd: */
अटल स्थिर पूर्णांक bbr_extra_acked_gain = BBR_UNIT;
/* Winकरोw length of extra_acked winकरोw. */
अटल स्थिर u32 bbr_extra_acked_win_rtts = 5;
/* Max allowed val क्रम ack_epoch_acked, after which sampling epoch is reset */
अटल स्थिर u32 bbr_ack_epoch_acked_reset_thresh = 1U << 20;
/* Time period क्रम clamping cwnd increment due to ack aggregation */
अटल स्थिर u32 bbr_extra_acked_max_us = 100 * 1000;

अटल व्योम bbr_check_probe_rtt_करोne(काष्ठा sock *sk);

/* Do we estimate that STARTUP filled the pipe? */
अटल bool bbr_full_bw_reached(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा bbr *bbr = inet_csk_ca(sk);

	वापस bbr->full_bw_reached;
पूर्ण

/* Return the winकरोwed max recent bandwidth sample, in pkts/uS << BW_SCALE. */
अटल u32 bbr_max_bw(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	वापस minmax_get(&bbr->bw);
पूर्ण

/* Return the estimated bandwidth of the path, in pkts/uS << BW_SCALE. */
अटल u32 bbr_bw(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	वापस bbr->lt_use_bw ? bbr->lt_bw : bbr_max_bw(sk);
पूर्ण

/* Return maximum extra acked in past k-2k round trips,
 * where k = bbr_extra_acked_win_rtts.
 */
अटल u16 bbr_extra_acked(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	वापस max(bbr->extra_acked[0], bbr->extra_acked[1]);
पूर्ण

/* Return rate in bytes per second, optionally with a gain.
 * The order here is chosen carefully to aव्योम overflow of u64. This should
 * work क्रम input rates of up to 2.9Tbit/sec and gain of 2.89x.
 */
अटल u64 bbr_rate_bytes_per_sec(काष्ठा sock *sk, u64 rate, पूर्णांक gain)
अणु
	अचिन्हित पूर्णांक mss = tcp_sk(sk)->mss_cache;

	rate *= mss;
	rate *= gain;
	rate >>= BBR_SCALE;
	rate *= USEC_PER_SEC / 100 * (100 - bbr_pacing_margin_percent);
	वापस rate >> BW_SCALE;
पूर्ण

/* Convert a BBR bw and gain factor to a pacing rate in bytes per second. */
अटल अचिन्हित दीर्घ bbr_bw_to_pacing_rate(काष्ठा sock *sk, u32 bw, पूर्णांक gain)
अणु
	u64 rate = bw;

	rate = bbr_rate_bytes_per_sec(sk, rate, gain);
	rate = min_t(u64, rate, sk->sk_max_pacing_rate);
	वापस rate;
पूर्ण

/* Initialize pacing rate to: high_gain * init_cwnd / RTT. */
अटल व्योम bbr_init_pacing_rate_from_rtt(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u64 bw;
	u32 rtt_us;

	अगर (tp->srtt_us) अणु		/* any RTT sample yet? */
		rtt_us = max(tp->srtt_us >> 3, 1U);
		bbr->has_seen_rtt = 1;
	पूर्ण अन्यथा अणु			 /* no RTT sample yet */
		rtt_us = USEC_PER_MSEC;	 /* use nominal शेष RTT */
	पूर्ण
	bw = (u64)tp->snd_cwnd * BW_UNIT;
	करो_भाग(bw, rtt_us);
	sk->sk_pacing_rate = bbr_bw_to_pacing_rate(sk, bw, bbr_high_gain);
पूर्ण

/* Pace using current bw estimate and a gain factor. */
अटल व्योम bbr_set_pacing_rate(काष्ठा sock *sk, u32 bw, पूर्णांक gain)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	अचिन्हित दीर्घ rate = bbr_bw_to_pacing_rate(sk, bw, gain);

	अगर (unlikely(!bbr->has_seen_rtt && tp->srtt_us))
		bbr_init_pacing_rate_from_rtt(sk);
	अगर (bbr_full_bw_reached(sk) || rate > sk->sk_pacing_rate)
		sk->sk_pacing_rate = rate;
पूर्ण

/* override sysctl_tcp_min_tso_segs */
अटल u32 bbr_min_tso_segs(काष्ठा sock *sk)
अणु
	वापस sk->sk_pacing_rate < (bbr_min_tso_rate >> 3) ? 1 : 2;
पूर्ण

अटल u32 bbr_tso_segs_goal(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 segs, bytes;

	/* Sort of tcp_tso_स्वतःsize() but ignoring
	 * driver provided sk_gso_max_size.
	 */
	bytes = min_t(अचिन्हित दीर्घ,
		      sk->sk_pacing_rate >> READ_ONCE(sk->sk_pacing_shअगरt),
		      GSO_MAX_SIZE - 1 - MAX_TCP_HEADER);
	segs = max_t(u32, bytes / tp->mss_cache, bbr_min_tso_segs(sk));

	वापस min(segs, 0x7FU);
पूर्ण

/* Save "last known good" cwnd so we can restore it after losses or PROBE_RTT */
अटल व्योम bbr_save_cwnd(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	अगर (bbr->prev_ca_state < TCP_CA_Recovery && bbr->mode != BBR_PROBE_RTT)
		bbr->prior_cwnd = tp->snd_cwnd;  /* this cwnd is good enough */
	अन्यथा  /* loss recovery or BBR_PROBE_RTT have temporarily cut cwnd */
		bbr->prior_cwnd = max(bbr->prior_cwnd, tp->snd_cwnd);
पूर्ण

अटल व्योम bbr_cwnd_event(काष्ठा sock *sk, क्रमागत tcp_ca_event event)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	अगर (event == CA_EVENT_TX_START && tp->app_limited) अणु
		bbr->idle_restart = 1;
		bbr->ack_epoch_mstamp = tp->tcp_mstamp;
		bbr->ack_epoch_acked = 0;
		/* Aव्योम poपूर्णांकless buffer overflows: pace at est. bw अगर we करोn't
		 * need more speed (we're restarting from idle and app-limited).
		 */
		अगर (bbr->mode == BBR_PROBE_BW)
			bbr_set_pacing_rate(sk, bbr_bw(sk), BBR_UNIT);
		अन्यथा अगर (bbr->mode == BBR_PROBE_RTT)
			bbr_check_probe_rtt_करोne(sk);
	पूर्ण
पूर्ण

/* Calculate bdp based on min RTT and the estimated bottleneck bandwidth:
 *
 * bdp = उच्चमान(bw * min_rtt * gain)
 *
 * The key factor, gain, controls the amount of queue. While a small gain
 * builds a smaller queue, it becomes more vulnerable to noise in RTT
 * measurements (e.g., delayed ACKs or other ACK compression effects). This
 * noise may cause BBR to under-estimate the rate.
 */
अटल u32 bbr_bdp(काष्ठा sock *sk, u32 bw, पूर्णांक gain)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u32 bdp;
	u64 w;

	/* If we've never had a valid RTT sample, cap cwnd at the initial
	 * शेष. This should only happen when the connection is not using TCP
	 * बारtamps and has retransmitted all of the SYN/SYNACK/data packets
	 * ACKed so far. In this हाल, an RTO can cut cwnd to 1, in which
	 * हाल we need to slow-start up toward something safe: TCP_INIT_CWND.
	 */
	अगर (unlikely(bbr->min_rtt_us == ~0U))	 /* no valid RTT samples yet? */
		वापस TCP_INIT_CWND;  /* be safe: cap at शेष initial cwnd*/

	w = (u64)bw * bbr->min_rtt_us;

	/* Apply a gain to the given value, हटाओ the BW_SCALE shअगरt, and
	 * round the value up to aव्योम a negative feedback loop.
	 */
	bdp = (((w * gain) >> BBR_SCALE) + BW_UNIT - 1) / BW_UNIT;

	वापस bdp;
पूर्ण

/* To achieve full perक्रमmance in high-speed paths, we budget enough cwnd to
 * fit full-sized skbs in-flight on both end hosts to fully utilize the path:
 *   - one skb in sending host Qdisc,
 *   - one skb in sending host TSO/GSO engine
 *   - one skb being received by receiver host LRO/GRO/delayed-ACK engine
 * Don't worry, at low rates (bbr_min_tso_rate) this won't bloat cwnd because
 * in such हालs tso_segs_goal is 1. The minimum cwnd is 4 packets,
 * which allows 2 outstanding 2-packet sequences, to try to keep pipe
 * full even with ACK-every-other-packet delayed ACKs.
 */
अटल u32 bbr_quantization_budget(काष्ठा sock *sk, u32 cwnd)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	/* Allow enough full-sized skbs in flight to utilize end प्रणालीs. */
	cwnd += 3 * bbr_tso_segs_goal(sk);

	/* Reduce delayed ACKs by rounding up cwnd to the next even number. */
	cwnd = (cwnd + 1) & ~1U;

	/* Ensure gain cycling माला_लो inflight above BDP even क्रम small BDPs. */
	अगर (bbr->mode == BBR_PROBE_BW && bbr->cycle_idx == 0)
		cwnd += 2;

	वापस cwnd;
पूर्ण

/* Find inflight based on min RTT and the estimated bottleneck bandwidth. */
अटल u32 bbr_inflight(काष्ठा sock *sk, u32 bw, पूर्णांक gain)
अणु
	u32 inflight;

	inflight = bbr_bdp(sk, bw, gain);
	inflight = bbr_quantization_budget(sk, inflight);

	वापस inflight;
पूर्ण

/* With pacing at lower layers, there's often less data "in the network" than
 * "in flight". With TSQ and departure समय pacing at lower layers (e.g. fq),
 * we often have several skbs queued in the pacing layer with a pre-scheduled
 * earliest departure समय (EDT). BBR adapts its pacing rate based on the
 * inflight level that it estimates has alपढ़ोy been "baked in" by previous
 * departure समय decisions. We calculate a rough estimate of the number of our
 * packets that might be in the network at the earliest departure समय क्रम the
 * next skb scheduled:
 *   in_network_at_edt = inflight_at_edt - (EDT - now) * bw
 * If we're increasing inflight, then we want to know अगर the transmit of the
 * EDT skb will push inflight above the target, so inflight_at_edt includes
 * bbr_tso_segs_goal() from the skb departing at EDT. If decreasing inflight,
 * then estimate अगर inflight will sink too low just beक्रमe the EDT transmit.
 */
अटल u32 bbr_packets_in_net_at_edt(काष्ठा sock *sk, u32 inflight_now)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u64 now_ns, edt_ns, पूर्णांकerval_us;
	u32 पूर्णांकerval_delivered, inflight_at_edt;

	now_ns = tp->tcp_घड़ी_cache;
	edt_ns = max(tp->tcp_wstamp_ns, now_ns);
	पूर्णांकerval_us = भाग_u64(edt_ns - now_ns, NSEC_PER_USEC);
	पूर्णांकerval_delivered = (u64)bbr_bw(sk) * पूर्णांकerval_us >> BW_SCALE;
	inflight_at_edt = inflight_now;
	अगर (bbr->pacing_gain > BBR_UNIT)              /* increasing inflight */
		inflight_at_edt += bbr_tso_segs_goal(sk);  /* include EDT skb */
	अगर (पूर्णांकerval_delivered >= inflight_at_edt)
		वापस 0;
	वापस inflight_at_edt - पूर्णांकerval_delivered;
पूर्ण

/* Find the cwnd increment based on estimate of ack aggregation */
अटल u32 bbr_ack_aggregation_cwnd(काष्ठा sock *sk)
अणु
	u32 max_aggr_cwnd, aggr_cwnd = 0;

	अगर (bbr_extra_acked_gain && bbr_full_bw_reached(sk)) अणु
		max_aggr_cwnd = ((u64)bbr_bw(sk) * bbr_extra_acked_max_us)
				/ BW_UNIT;
		aggr_cwnd = (bbr_extra_acked_gain * bbr_extra_acked(sk))
			     >> BBR_SCALE;
		aggr_cwnd = min(aggr_cwnd, max_aggr_cwnd);
	पूर्ण

	वापस aggr_cwnd;
पूर्ण

/* An optimization in BBR to reduce losses: On the first round of recovery, we
 * follow the packet conservation principle: send P packets per P packets acked.
 * After that, we slow-start and send at most 2*P packets per P packets acked.
 * After recovery finishes, or upon unकरो, we restore the cwnd we had when
 * recovery started (capped by the target cwnd based on estimated BDP).
 *
 * TODO(ycheng/ncardwell): implement a rate-based approach.
 */
अटल bool bbr_set_cwnd_to_recover_or_restore(
	काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs, u32 acked, u32 *new_cwnd)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u8 prev_state = bbr->prev_ca_state, state = inet_csk(sk)->icsk_ca_state;
	u32 cwnd = tp->snd_cwnd;

	/* An ACK क्रम P pkts should release at most 2*P packets. We करो this
	 * in two steps. First, here we deduct the number of lost packets.
	 * Then, in bbr_set_cwnd() we slow start up toward the target cwnd.
	 */
	अगर (rs->losses > 0)
		cwnd = max_t(s32, cwnd - rs->losses, 1);

	अगर (state == TCP_CA_Recovery && prev_state != TCP_CA_Recovery) अणु
		/* Starting 1st round of Recovery, so करो packet conservation. */
		bbr->packet_conservation = 1;
		bbr->next_rtt_delivered = tp->delivered;  /* start round now */
		/* Cut unused cwnd from app behavior, TSQ, or TSO deferral: */
		cwnd = tcp_packets_in_flight(tp) + acked;
	पूर्ण अन्यथा अगर (prev_state >= TCP_CA_Recovery && state < TCP_CA_Recovery) अणु
		/* Exiting loss recovery; restore cwnd saved beक्रमe recovery. */
		cwnd = max(cwnd, bbr->prior_cwnd);
		bbr->packet_conservation = 0;
	पूर्ण
	bbr->prev_ca_state = state;

	अगर (bbr->packet_conservation) अणु
		*new_cwnd = max(cwnd, tcp_packets_in_flight(tp) + acked);
		वापस true;	/* yes, using packet conservation */
	पूर्ण
	*new_cwnd = cwnd;
	वापस false;
पूर्ण

/* Slow-start up toward target cwnd (अगर bw estimate is growing, or packet loss
 * has drawn us करोwn below target), or snap करोwn to target अगर we're above it.
 */
अटल व्योम bbr_set_cwnd(काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs,
			 u32 acked, u32 bw, पूर्णांक gain)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u32 cwnd = tp->snd_cwnd, target_cwnd = 0;

	अगर (!acked)
		जाओ करोne;  /* no packet fully ACKed; just apply caps */

	अगर (bbr_set_cwnd_to_recover_or_restore(sk, rs, acked, &cwnd))
		जाओ करोne;

	target_cwnd = bbr_bdp(sk, bw, gain);

	/* Increment the cwnd to account क्रम excess ACKed data that seems
	 * due to aggregation (of data and/or ACKs) visible in the ACK stream.
	 */
	target_cwnd += bbr_ack_aggregation_cwnd(sk);
	target_cwnd = bbr_quantization_budget(sk, target_cwnd);

	/* If we're below target cwnd, slow start cwnd toward target cwnd. */
	अगर (bbr_full_bw_reached(sk))  /* only cut cwnd अगर we filled the pipe */
		cwnd = min(cwnd + acked, target_cwnd);
	अन्यथा अगर (cwnd < target_cwnd || tp->delivered < TCP_INIT_CWND)
		cwnd = cwnd + acked;
	cwnd = max(cwnd, bbr_cwnd_min_target);

करोne:
	tp->snd_cwnd = min(cwnd, tp->snd_cwnd_clamp);	/* apply global cap */
	अगर (bbr->mode == BBR_PROBE_RTT)  /* drain queue, refresh min_rtt */
		tp->snd_cwnd = min(tp->snd_cwnd, bbr_cwnd_min_target);
पूर्ण

/* End cycle phase अगर it's time and/or we hit the phase's in-flight target. */
अटल bool bbr_is_next_cycle_phase(काष्ठा sock *sk,
				    स्थिर काष्ठा rate_sample *rs)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	bool is_full_length =
		tcp_stamp_us_delta(tp->delivered_mstamp, bbr->cycle_mstamp) >
		bbr->min_rtt_us;
	u32 inflight, bw;

	/* The pacing_gain of 1.0 paces at the estimated bw to try to fully
	 * use the pipe without increasing the queue.
	 */
	अगर (bbr->pacing_gain == BBR_UNIT)
		वापस is_full_length;		/* just use wall घड़ी समय */

	inflight = bbr_packets_in_net_at_edt(sk, rs->prior_in_flight);
	bw = bbr_max_bw(sk);

	/* A pacing_gain > 1.0 probes क्रम bw by trying to उठाओ inflight to at
	 * least pacing_gain*BDP; this may take more than min_rtt अगर min_rtt is
	 * small (e.g. on a LAN). We करो not persist अगर packets are lost, since
	 * a path with small buffers may not hold that much.
	 */
	अगर (bbr->pacing_gain > BBR_UNIT)
		वापस is_full_length &&
			(rs->losses ||  /* perhaps pacing_gain*BDP won't fit */
			 inflight >= bbr_inflight(sk, bw, bbr->pacing_gain));

	/* A pacing_gain < 1.0 tries to drain extra queue we added अगर bw
	 * probing didn't find more bw. If inflight falls to match BDP then we
	 * estimate queue is drained; persisting would underutilize the pipe.
	 */
	वापस is_full_length ||
		inflight <= bbr_inflight(sk, bw, BBR_UNIT);
पूर्ण

अटल व्योम bbr_advance_cycle_phase(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	bbr->cycle_idx = (bbr->cycle_idx + 1) & (CYCLE_LEN - 1);
	bbr->cycle_mstamp = tp->delivered_mstamp;
पूर्ण

/* Gain cycling: cycle pacing gain to converge to fair share of available bw. */
अटल व्योम bbr_update_cycle_phase(काष्ठा sock *sk,
				   स्थिर काष्ठा rate_sample *rs)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	अगर (bbr->mode == BBR_PROBE_BW && bbr_is_next_cycle_phase(sk, rs))
		bbr_advance_cycle_phase(sk);
पूर्ण

अटल व्योम bbr_reset_startup_mode(काष्ठा sock *sk)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	bbr->mode = BBR_STARTUP;
पूर्ण

अटल व्योम bbr_reset_probe_bw_mode(काष्ठा sock *sk)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	bbr->mode = BBR_PROBE_BW;
	bbr->cycle_idx = CYCLE_LEN - 1 - pअक्रमom_u32_max(bbr_cycle_अक्रम);
	bbr_advance_cycle_phase(sk);	/* flip to next phase of gain cycle */
पूर्ण

अटल व्योम bbr_reset_mode(काष्ठा sock *sk)
अणु
	अगर (!bbr_full_bw_reached(sk))
		bbr_reset_startup_mode(sk);
	अन्यथा
		bbr_reset_probe_bw_mode(sk);
पूर्ण

/* Start a new दीर्घ-term sampling पूर्णांकerval. */
अटल व्योम bbr_reset_lt_bw_sampling_पूर्णांकerval(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	bbr->lt_last_stamp = भाग_u64(tp->delivered_mstamp, USEC_PER_MSEC);
	bbr->lt_last_delivered = tp->delivered;
	bbr->lt_last_lost = tp->lost;
	bbr->lt_rtt_cnt = 0;
पूर्ण

/* Completely reset दीर्घ-term bandwidth sampling. */
अटल व्योम bbr_reset_lt_bw_sampling(काष्ठा sock *sk)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	bbr->lt_bw = 0;
	bbr->lt_use_bw = 0;
	bbr->lt_is_sampling = false;
	bbr_reset_lt_bw_sampling_पूर्णांकerval(sk);
पूर्ण

/* Long-term bw sampling पूर्णांकerval is करोne. Estimate whether we're policed. */
अटल व्योम bbr_lt_bw_पूर्णांकerval_करोne(काष्ठा sock *sk, u32 bw)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u32 dअगरf;

	अगर (bbr->lt_bw) अणु  /* करो we have bw from a previous पूर्णांकerval? */
		/* Is new bw बंद to the lt_bw from the previous पूर्णांकerval? */
		dअगरf = असल(bw - bbr->lt_bw);
		अगर ((dअगरf * BBR_UNIT <= bbr_lt_bw_ratio * bbr->lt_bw) ||
		    (bbr_rate_bytes_per_sec(sk, dअगरf, BBR_UNIT) <=
		     bbr_lt_bw_dअगरf)) अणु
			/* All criteria are met; estimate we're policed. */
			bbr->lt_bw = (bw + bbr->lt_bw) >> 1;  /* avg 2 पूर्णांकvls */
			bbr->lt_use_bw = 1;
			bbr->pacing_gain = BBR_UNIT;  /* try to aव्योम drops */
			bbr->lt_rtt_cnt = 0;
			वापस;
		पूर्ण
	पूर्ण
	bbr->lt_bw = bw;
	bbr_reset_lt_bw_sampling_पूर्णांकerval(sk);
पूर्ण

/* Token-bucket traffic policers are common (see "An Internet-Wide Analysis of
 * Traffic Policing", SIGCOMM 2016). BBR detects token-bucket policers and
 * explicitly models their policed rate, to reduce unnecessary losses. We
 * estimate that we're policed अगर we see 2 consecutive sampling पूर्णांकervals with
 * consistent throughput and high packet loss. If we think we're being policed,
 * set lt_bw to the "long-term" average delivery rate from those 2 पूर्णांकervals.
 */
अटल व्योम bbr_lt_bw_sampling(काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u32 lost, delivered;
	u64 bw;
	u32 t;

	अगर (bbr->lt_use_bw) अणु	/* alपढ़ोy using दीर्घ-term rate, lt_bw? */
		अगर (bbr->mode == BBR_PROBE_BW && bbr->round_start &&
		    ++bbr->lt_rtt_cnt >= bbr_lt_bw_max_rtts) अणु
			bbr_reset_lt_bw_sampling(sk);    /* stop using lt_bw */
			bbr_reset_probe_bw_mode(sk);  /* restart gain cycling */
		पूर्ण
		वापस;
	पूर्ण

	/* Wait क्रम the first loss beक्रमe sampling, to let the policer exhaust
	 * its tokens and estimate the steady-state rate allowed by the policer.
	 * Starting samples earlier includes bursts that over-estimate the bw.
	 */
	अगर (!bbr->lt_is_sampling) अणु
		अगर (!rs->losses)
			वापस;
		bbr_reset_lt_bw_sampling_पूर्णांकerval(sk);
		bbr->lt_is_sampling = true;
	पूर्ण

	/* To aव्योम underestimates, reset sampling अगर we run out of data. */
	अगर (rs->is_app_limited) अणु
		bbr_reset_lt_bw_sampling(sk);
		वापस;
	पूर्ण

	अगर (bbr->round_start)
		bbr->lt_rtt_cnt++;	/* count round trips in this पूर्णांकerval */
	अगर (bbr->lt_rtt_cnt < bbr_lt_पूर्णांकvl_min_rtts)
		वापस;		/* sampling पूर्णांकerval needs to be दीर्घer */
	अगर (bbr->lt_rtt_cnt > 4 * bbr_lt_पूर्णांकvl_min_rtts) अणु
		bbr_reset_lt_bw_sampling(sk);  /* पूर्णांकerval is too दीर्घ */
		वापस;
	पूर्ण

	/* End sampling पूर्णांकerval when a packet is lost, so we estimate the
	 * policer tokens were exhausted. Stopping the sampling beक्रमe the
	 * tokens are exhausted under-estimates the policed rate.
	 */
	अगर (!rs->losses)
		वापस;

	/* Calculate packets lost and delivered in sampling पूर्णांकerval. */
	lost = tp->lost - bbr->lt_last_lost;
	delivered = tp->delivered - bbr->lt_last_delivered;
	/* Is loss rate (lost/delivered) >= lt_loss_thresh? If not, रुको. */
	अगर (!delivered || (lost << BBR_SCALE) < bbr_lt_loss_thresh * delivered)
		वापस;

	/* Find average delivery rate in this sampling पूर्णांकerval. */
	t = भाग_u64(tp->delivered_mstamp, USEC_PER_MSEC) - bbr->lt_last_stamp;
	अगर ((s32)t < 1)
		वापस;		/* पूर्णांकerval is less than one ms, so रुको */
	/* Check अगर can multiply without overflow */
	अगर (t >= ~0U / USEC_PER_MSEC) अणु
		bbr_reset_lt_bw_sampling(sk);  /* पूर्णांकerval too दीर्घ; reset */
		वापस;
	पूर्ण
	t *= USEC_PER_MSEC;
	bw = (u64)delivered * BW_UNIT;
	करो_भाग(bw, t);
	bbr_lt_bw_पूर्णांकerval_करोne(sk, bw);
पूर्ण

/* Estimate the bandwidth based on how fast packets are delivered */
अटल व्योम bbr_update_bw(काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u64 bw;

	bbr->round_start = 0;
	अगर (rs->delivered < 0 || rs->पूर्णांकerval_us <= 0)
		वापस; /* Not a valid observation */

	/* See अगर we've reached the next RTT */
	अगर (!beक्रमe(rs->prior_delivered, bbr->next_rtt_delivered)) अणु
		bbr->next_rtt_delivered = tp->delivered;
		bbr->rtt_cnt++;
		bbr->round_start = 1;
		bbr->packet_conservation = 0;
	पूर्ण

	bbr_lt_bw_sampling(sk, rs);

	/* Divide delivered by the पूर्णांकerval to find a (lower bound) bottleneck
	 * bandwidth sample. Delivered is in packets and पूर्णांकerval_us in uS and
	 * ratio will be <<1 क्रम most connections. So delivered is first scaled.
	 */
	bw = भाग64_दीर्घ((u64)rs->delivered * BW_UNIT, rs->पूर्णांकerval_us);

	/* If this sample is application-limited, it is likely to have a very
	 * low delivered count that represents application behavior rather than
	 * the available network rate. Such a sample could drag करोwn estimated
	 * bw, causing needless slow-करोwn. Thus, to जारी to send at the
	 * last measured network rate, we filter out app-limited samples unless
	 * they describe the path bw at least as well as our bw model.
	 *
	 * So the goal during app-limited phase is to proceed with the best
	 * network rate no matter how दीर्घ. We स्वतःmatically leave this
	 * phase when app ग_लिखोs faster than the network can deliver :)
	 */
	अगर (!rs->is_app_limited || bw >= bbr_max_bw(sk)) अणु
		/* Incorporate new sample पूर्णांकo our max bw filter. */
		minmax_running_max(&bbr->bw, bbr_bw_rtts, bbr->rtt_cnt, bw);
	पूर्ण
पूर्ण

/* Estimates the winकरोwed max degree of ack aggregation.
 * This is used to provision extra in-flight data to keep sending during
 * पूर्णांकer-ACK silences.
 *
 * Degree of ack aggregation is estimated as extra data acked beyond expected.
 *
 * max_extra_acked = "maximum recent excess data ACKed beyond max_bw * interval"
 * cwnd += max_extra_acked
 *
 * Max extra_acked is clamped by cwnd and bw * bbr_extra_acked_max_us (100 ms).
 * Max filter is an approximate sliding winकरोw of 5-10 (packet समयd) round
 * trips.
 */
अटल व्योम bbr_update_ack_aggregation(काष्ठा sock *sk,
				       स्थिर काष्ठा rate_sample *rs)
अणु
	u32 epoch_us, expected_acked, extra_acked;
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!bbr_extra_acked_gain || rs->acked_sacked <= 0 ||
	    rs->delivered < 0 || rs->पूर्णांकerval_us <= 0)
		वापस;

	अगर (bbr->round_start) अणु
		bbr->extra_acked_win_rtts = min(0x1F,
						bbr->extra_acked_win_rtts + 1);
		अगर (bbr->extra_acked_win_rtts >= bbr_extra_acked_win_rtts) अणु
			bbr->extra_acked_win_rtts = 0;
			bbr->extra_acked_win_idx = bbr->extra_acked_win_idx ?
						   0 : 1;
			bbr->extra_acked[bbr->extra_acked_win_idx] = 0;
		पूर्ण
	पूर्ण

	/* Compute how many packets we expected to be delivered over epoch. */
	epoch_us = tcp_stamp_us_delta(tp->delivered_mstamp,
				      bbr->ack_epoch_mstamp);
	expected_acked = ((u64)bbr_bw(sk) * epoch_us) / BW_UNIT;

	/* Reset the aggregation epoch अगर ACK rate is below expected rate or
	 * signअगरicantly large no. of ack received since epoch (potentially
	 * quite old epoch).
	 */
	अगर (bbr->ack_epoch_acked <= expected_acked ||
	    (bbr->ack_epoch_acked + rs->acked_sacked >=
	     bbr_ack_epoch_acked_reset_thresh)) अणु
		bbr->ack_epoch_acked = 0;
		bbr->ack_epoch_mstamp = tp->delivered_mstamp;
		expected_acked = 0;
	पूर्ण

	/* Compute excess data delivered, beyond what was expected. */
	bbr->ack_epoch_acked = min_t(u32, 0xFFFFF,
				     bbr->ack_epoch_acked + rs->acked_sacked);
	extra_acked = bbr->ack_epoch_acked - expected_acked;
	extra_acked = min(extra_acked, tp->snd_cwnd);
	अगर (extra_acked > bbr->extra_acked[bbr->extra_acked_win_idx])
		bbr->extra_acked[bbr->extra_acked_win_idx] = extra_acked;
पूर्ण

/* Estimate when the pipe is full, using the change in delivery rate: BBR
 * estimates that STARTUP filled the pipe अगर the estimated bw hasn't changed by
 * at least bbr_full_bw_thresh (25%) after bbr_full_bw_cnt (3) non-app-limited
 * rounds. Why 3 rounds: 1: rwin स्वतःtuning grows the rwin, 2: we fill the
 * higher rwin, 3: we get higher delivery rate samples. Or transient
 * cross-traffic or radio noise can go away. CUBIC Hystart shares a similar
 * design goal, but uses delay and पूर्णांकer-ACK spacing instead of bandwidth.
 */
अटल व्योम bbr_check_full_bw_reached(काष्ठा sock *sk,
				      स्थिर काष्ठा rate_sample *rs)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u32 bw_thresh;

	अगर (bbr_full_bw_reached(sk) || !bbr->round_start || rs->is_app_limited)
		वापस;

	bw_thresh = (u64)bbr->full_bw * bbr_full_bw_thresh >> BBR_SCALE;
	अगर (bbr_max_bw(sk) >= bw_thresh) अणु
		bbr->full_bw = bbr_max_bw(sk);
		bbr->full_bw_cnt = 0;
		वापस;
	पूर्ण
	++bbr->full_bw_cnt;
	bbr->full_bw_reached = bbr->full_bw_cnt >= bbr_full_bw_cnt;
पूर्ण

/* If pipe is probably full, drain the queue and then enter steady-state. */
अटल व्योम bbr_check_drain(काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	अगर (bbr->mode == BBR_STARTUP && bbr_full_bw_reached(sk)) अणु
		bbr->mode = BBR_DRAIN;	/* drain queue we created */
		tcp_sk(sk)->snd_ssthresh =
				bbr_inflight(sk, bbr_max_bw(sk), BBR_UNIT);
	पूर्ण	/* fall through to check अगर in-flight is alपढ़ोy small: */
	अगर (bbr->mode == BBR_DRAIN &&
	    bbr_packets_in_net_at_edt(sk, tcp_packets_in_flight(tcp_sk(sk))) <=
	    bbr_inflight(sk, bbr_max_bw(sk), BBR_UNIT))
		bbr_reset_probe_bw_mode(sk);  /* we estimate queue is drained */
पूर्ण

अटल व्योम bbr_check_probe_rtt_करोne(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	अगर (!(bbr->probe_rtt_करोne_stamp &&
	      after(tcp_jअगरfies32, bbr->probe_rtt_करोne_stamp)))
		वापस;

	bbr->min_rtt_stamp = tcp_jअगरfies32;  /* रुको a जबतक until PROBE_RTT */
	tp->snd_cwnd = max(tp->snd_cwnd, bbr->prior_cwnd);
	bbr_reset_mode(sk);
पूर्ण

/* The goal of PROBE_RTT mode is to have BBR flows cooperatively and
 * periodically drain the bottleneck queue, to converge to measure the true
 * min_rtt (unloaded propagation delay). This allows the flows to keep queues
 * small (reducing queuing delay and packet loss) and achieve fairness among
 * BBR flows.
 *
 * The min_rtt filter winकरोw is 10 seconds. When the min_rtt estimate expires,
 * we enter PROBE_RTT mode and cap the cwnd at bbr_cwnd_min_target=4 packets.
 * After at least bbr_probe_rtt_mode_ms=200ms and at least one packet-समयd
 * round trip elapsed with that flight size <= 4, we leave PROBE_RTT mode and
 * re-enter the previous mode. BBR uses 200ms to approximately bound the
 * perक्रमmance penalty of PROBE_RTT's cwnd capping to roughly 2% (200ms/10s).
 *
 * Note that flows need only pay 2% अगर they are busy sending over the last 10
 * seconds. Interactive applications (e.g., Web, RPCs, video chunks) often have
 * natural silences or low-rate periods within 10 seconds where the rate is low
 * enough क्रम दीर्घ enough to drain its queue in the bottleneck. We pick up
 * these min RTT measurements opportunistically with our min_rtt filter. :-)
 */
अटल व्योम bbr_update_min_rtt(काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	bool filter_expired;

	/* Track min RTT seen in the min_rtt_win_sec filter winकरोw: */
	filter_expired = after(tcp_jअगरfies32,
			       bbr->min_rtt_stamp + bbr_min_rtt_win_sec * HZ);
	अगर (rs->rtt_us >= 0 &&
	    (rs->rtt_us < bbr->min_rtt_us ||
	     (filter_expired && !rs->is_ack_delayed))) अणु
		bbr->min_rtt_us = rs->rtt_us;
		bbr->min_rtt_stamp = tcp_jअगरfies32;
	पूर्ण

	अगर (bbr_probe_rtt_mode_ms > 0 && filter_expired &&
	    !bbr->idle_restart && bbr->mode != BBR_PROBE_RTT) अणु
		bbr->mode = BBR_PROBE_RTT;  /* dip, drain queue */
		bbr_save_cwnd(sk);  /* note cwnd so we can restore it */
		bbr->probe_rtt_करोne_stamp = 0;
	पूर्ण

	अगर (bbr->mode == BBR_PROBE_RTT) अणु
		/* Ignore low rate samples during this mode. */
		tp->app_limited =
			(tp->delivered + tcp_packets_in_flight(tp)) ? : 1;
		/* Maपूर्णांकain min packets in flight क्रम max(200 ms, 1 round). */
		अगर (!bbr->probe_rtt_करोne_stamp &&
		    tcp_packets_in_flight(tp) <= bbr_cwnd_min_target) अणु
			bbr->probe_rtt_करोne_stamp = tcp_jअगरfies32 +
				msecs_to_jअगरfies(bbr_probe_rtt_mode_ms);
			bbr->probe_rtt_round_करोne = 0;
			bbr->next_rtt_delivered = tp->delivered;
		पूर्ण अन्यथा अगर (bbr->probe_rtt_करोne_stamp) अणु
			अगर (bbr->round_start)
				bbr->probe_rtt_round_करोne = 1;
			अगर (bbr->probe_rtt_round_करोne)
				bbr_check_probe_rtt_करोne(sk);
		पूर्ण
	पूर्ण
	/* Restart after idle ends only once we process a new S/ACK क्रम data */
	अगर (rs->delivered > 0)
		bbr->idle_restart = 0;
पूर्ण

अटल व्योम bbr_update_gains(काष्ठा sock *sk)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	चयन (bbr->mode) अणु
	हाल BBR_STARTUP:
		bbr->pacing_gain = bbr_high_gain;
		bbr->cwnd_gain	 = bbr_high_gain;
		अवरोध;
	हाल BBR_DRAIN:
		bbr->pacing_gain = bbr_drain_gain;	/* slow, to drain */
		bbr->cwnd_gain	 = bbr_high_gain;	/* keep cwnd */
		अवरोध;
	हाल BBR_PROBE_BW:
		bbr->pacing_gain = (bbr->lt_use_bw ?
				    BBR_UNIT :
				    bbr_pacing_gain[bbr->cycle_idx]);
		bbr->cwnd_gain	 = bbr_cwnd_gain;
		अवरोध;
	हाल BBR_PROBE_RTT:
		bbr->pacing_gain = BBR_UNIT;
		bbr->cwnd_gain	 = BBR_UNIT;
		अवरोध;
	शेष:
		WARN_ONCE(1, "BBR bad mode: %u\n", bbr->mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bbr_update_model(काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs)
अणु
	bbr_update_bw(sk, rs);
	bbr_update_ack_aggregation(sk, rs);
	bbr_update_cycle_phase(sk, rs);
	bbr_check_full_bw_reached(sk, rs);
	bbr_check_drain(sk, rs);
	bbr_update_min_rtt(sk, rs);
	bbr_update_gains(sk);
पूर्ण

अटल व्योम bbr_मुख्य(काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);
	u32 bw;

	bbr_update_model(sk, rs);

	bw = bbr_bw(sk);
	bbr_set_pacing_rate(sk, bw, bbr->pacing_gain);
	bbr_set_cwnd(sk, rs, rs->acked_sacked, bw, bbr->cwnd_gain);
पूर्ण

अटल व्योम bbr_init(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	bbr->prior_cwnd = 0;
	tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	bbr->rtt_cnt = 0;
	bbr->next_rtt_delivered = 0;
	bbr->prev_ca_state = TCP_CA_Open;
	bbr->packet_conservation = 0;

	bbr->probe_rtt_करोne_stamp = 0;
	bbr->probe_rtt_round_करोne = 0;
	bbr->min_rtt_us = tcp_min_rtt(tp);
	bbr->min_rtt_stamp = tcp_jअगरfies32;

	minmax_reset(&bbr->bw, bbr->rtt_cnt, 0);  /* init max bw to 0 */

	bbr->has_seen_rtt = 0;
	bbr_init_pacing_rate_from_rtt(sk);

	bbr->round_start = 0;
	bbr->idle_restart = 0;
	bbr->full_bw_reached = 0;
	bbr->full_bw = 0;
	bbr->full_bw_cnt = 0;
	bbr->cycle_mstamp = 0;
	bbr->cycle_idx = 0;
	bbr_reset_lt_bw_sampling(sk);
	bbr_reset_startup_mode(sk);

	bbr->ack_epoch_mstamp = tp->tcp_mstamp;
	bbr->ack_epoch_acked = 0;
	bbr->extra_acked_win_rtts = 0;
	bbr->extra_acked_win_idx = 0;
	bbr->extra_acked[0] = 0;
	bbr->extra_acked[1] = 0;

	cmpxchg(&sk->sk_pacing_status, SK_PACING_NONE, SK_PACING_NEEDED);
पूर्ण

अटल u32 bbr_sndbuf_expand(काष्ठा sock *sk)
अणु
	/* Provision 3 * cwnd since BBR may slow-start even during recovery. */
	वापस 3;
पूर्ण

/* In theory BBR करोes not need to unकरो the cwnd since it करोes not
 * always reduce cwnd on losses (see bbr_मुख्य()). Keep it क्रम now.
 */
अटल u32 bbr_unकरो_cwnd(काष्ठा sock *sk)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	bbr->full_bw = 0;   /* spurious slow-करोwn; reset full pipe detection */
	bbr->full_bw_cnt = 0;
	bbr_reset_lt_bw_sampling(sk);
	वापस tcp_sk(sk)->snd_cwnd;
पूर्ण

/* Entering loss recovery, so save cwnd क्रम when we निकास or unकरो recovery. */
अटल u32 bbr_ssthresh(काष्ठा sock *sk)
अणु
	bbr_save_cwnd(sk);
	वापस tcp_sk(sk)->snd_ssthresh;
पूर्ण

अटल माप_प्रकार bbr_get_info(काष्ठा sock *sk, u32 ext, पूर्णांक *attr,
			   जोड़ tcp_cc_info *info)
अणु
	अगर (ext & (1 << (INET_DIAG_BBRINFO - 1)) ||
	    ext & (1 << (INET_DIAG_VEGASINFO - 1))) अणु
		काष्ठा tcp_sock *tp = tcp_sk(sk);
		काष्ठा bbr *bbr = inet_csk_ca(sk);
		u64 bw = bbr_bw(sk);

		bw = bw * tp->mss_cache * USEC_PER_SEC >> BW_SCALE;
		स_रखो(&info->bbr, 0, माप(info->bbr));
		info->bbr.bbr_bw_lo		= (u32)bw;
		info->bbr.bbr_bw_hi		= (u32)(bw >> 32);
		info->bbr.bbr_min_rtt		= bbr->min_rtt_us;
		info->bbr.bbr_pacing_gain	= bbr->pacing_gain;
		info->bbr.bbr_cwnd_gain		= bbr->cwnd_gain;
		*attr = INET_DIAG_BBRINFO;
		वापस माप(info->bbr);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bbr_set_state(काष्ठा sock *sk, u8 new_state)
अणु
	काष्ठा bbr *bbr = inet_csk_ca(sk);

	अगर (new_state == TCP_CA_Loss) अणु
		काष्ठा rate_sample rs = अणु .losses = 1 पूर्ण;

		bbr->prev_ca_state = TCP_CA_Loss;
		bbr->full_bw = 0;
		bbr->round_start = 1;	/* treat RTO like end of a round */
		bbr_lt_bw_sampling(sk, &rs);
	पूर्ण
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_bbr_cong_ops __पढ़ो_mostly = अणु
	.flags		= TCP_CONG_NON_RESTRICTED,
	.name		= "bbr",
	.owner		= THIS_MODULE,
	.init		= bbr_init,
	.cong_control	= bbr_मुख्य,
	.sndbuf_expand	= bbr_sndbuf_expand,
	.unकरो_cwnd	= bbr_unकरो_cwnd,
	.cwnd_event	= bbr_cwnd_event,
	.ssthresh	= bbr_ssthresh,
	.min_tso_segs	= bbr_min_tso_segs,
	.get_info	= bbr_get_info,
	.set_state	= bbr_set_state,
पूर्ण;

अटल पूर्णांक __init bbr_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा bbr) > ICSK_CA_PRIV_SIZE);
	वापस tcp_रेजिस्टर_congestion_control(&tcp_bbr_cong_ops);
पूर्ण

अटल व्योम __निकास bbr_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_bbr_cong_ops);
पूर्ण

module_init(bbr_रेजिस्टर);
module_निकास(bbr_unरेजिस्टर);

MODULE_AUTHOR("Van Jacobson <vanj@google.com>");
MODULE_AUTHOR("Neal Cardwell <ncardwell@google.com>");
MODULE_AUTHOR("Yuchung Cheng <ycheng@google.com>");
MODULE_AUTHOR("Soheil Hassas Yeganeh <soheil@google.com>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("TCP BBR (Bottleneck Bandwidth and RTT)");
