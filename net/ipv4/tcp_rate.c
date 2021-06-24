<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <net/tcp.h>

/* The bandwidth estimator estimates the rate at which the network
 * can currently deliver outbound data packets क्रम this flow. At a high
 * level, it operates by taking a delivery rate sample क्रम each ACK.
 *
 * A rate sample records the rate at which the network delivered packets
 * क्रम this flow, calculated over the समय पूर्णांकerval between the transmission
 * of a data packet and the acknowledgment of that packet.
 *
 * Specअगरically, over the पूर्णांकerval between each transmit and corresponding ACK,
 * the estimator generates a delivery rate sample. Typically it uses the rate
 * at which packets were acknowledged. However, the approach of using only the
 * acknowledgment rate faces a challenge under the prevalent ACK decimation or
 * compression: packets can temporarily appear to be delivered much quicker
 * than the bottleneck rate. Since it is physically impossible to करो that in a
 * sustained fashion, when the estimator notices that the ACK rate is faster
 * than the transmit rate, it uses the latter:
 *
 *    send_rate = #pkts_delivered/(last_snd_समय - first_snd_समय)
 *    ack_rate  = #pkts_delivered/(last_ack_समय - first_ack_समय)
 *    bw = min(send_rate, ack_rate)
 *
 * Notice the estimator essentially estimates the goodput, not always the
 * network bottleneck link rate when the sending or receiving is limited by
 * other factors like applications or receiver winकरोw limits.  The estimator
 * deliberately aव्योमs using the पूर्णांकer-packet spacing approach because that
 * approach requires a large number of samples and sophisticated filtering.
 *
 * TCP flows can often be application-limited in request/response workloads.
 * The estimator marks a bandwidth sample as application-limited अगर there
 * was some moment during the sampled winकरोw of packets when there was no data
 * पढ़ोy to send in the ग_लिखो queue.
 */

/* Snapshot the current delivery inक्रमmation in the skb, to generate
 * a rate sample later when the skb is (s)acked in tcp_rate_skb_delivered().
 */
व्योम tcp_rate_skb_sent(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	 /* In general we need to start delivery rate samples from the
	  * समय we received the most recent ACK, to ensure we include
	  * the full समय the network needs to deliver all in-flight
	  * packets. If there are no packets in flight yet, then we
	  * know that any ACKs after now indicate that the network was
	  * able to deliver those packets completely in the sampling
	  * पूर्णांकerval between now and the next ACK.
	  *
	  * Note that we use packets_out instead of tcp_packets_in_flight(tp)
	  * because the latter is a guess based on RTO and loss-marking
	  * heuristics. We करोn't want spurious RTOs or loss markings to cause
	  * a spuriously small समय पूर्णांकerval, causing a spuriously high
	  * bandwidth estimate.
	  */
	अगर (!tp->packets_out) अणु
		u64 tstamp_us = tcp_skb_बारtamp_us(skb);

		tp->first_tx_mstamp  = tstamp_us;
		tp->delivered_mstamp = tstamp_us;
	पूर्ण

	TCP_SKB_CB(skb)->tx.first_tx_mstamp	= tp->first_tx_mstamp;
	TCP_SKB_CB(skb)->tx.delivered_mstamp	= tp->delivered_mstamp;
	TCP_SKB_CB(skb)->tx.delivered		= tp->delivered;
	TCP_SKB_CB(skb)->tx.is_app_limited	= tp->app_limited ? 1 : 0;
पूर्ण

/* When an skb is sacked or acked, we fill in the rate sample with the (prior)
 * delivery inक्रमmation when the skb was last transmitted.
 *
 * If an ACK (s)acks multiple skbs (e.g., stretched-acks), this function is
 * called multiple बार. We favor the inक्रमmation from the most recently
 * sent skb, i.e., the skb with the highest prior_delivered count.
 */
व्योम tcp_rate_skb_delivered(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    काष्ठा rate_sample *rs)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_skb_cb *scb = TCP_SKB_CB(skb);

	अगर (!scb->tx.delivered_mstamp)
		वापस;

	अगर (!rs->prior_delivered ||
	    after(scb->tx.delivered, rs->prior_delivered)) अणु
		rs->prior_delivered  = scb->tx.delivered;
		rs->prior_mstamp     = scb->tx.delivered_mstamp;
		rs->is_app_limited   = scb->tx.is_app_limited;
		rs->is_retrans	     = scb->sacked & TCPCB_RETRANS;

		/* Record send समय of most recently ACKed packet: */
		tp->first_tx_mstamp  = tcp_skb_बारtamp_us(skb);
		/* Find the duration of the "send phase" of this winकरोw: */
		rs->पूर्णांकerval_us = tcp_stamp_us_delta(tp->first_tx_mstamp,
						     scb->tx.first_tx_mstamp);

	पूर्ण
	/* Mark off the skb delivered once it's sacked to aव्योम being
	 * used again when it's cumulatively acked. For acked packets
	 * we करोn't need to reset since it'll be मुक्तd soon.
	 */
	अगर (scb->sacked & TCPCB_SACKED_ACKED)
		scb->tx.delivered_mstamp = 0;
पूर्ण

/* Update the connection delivery inक्रमmation and generate a rate sample. */
व्योम tcp_rate_gen(काष्ठा sock *sk, u32 delivered, u32 lost,
		  bool is_sack_reneg, काष्ठा rate_sample *rs)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 snd_us, ack_us;

	/* Clear app limited अगर bubble is acked and gone. */
	अगर (tp->app_limited && after(tp->delivered, tp->app_limited))
		tp->app_limited = 0;

	/* TODO: there are multiple places throughout tcp_ack() to get
	 * current समय. Refactor the code using a new "tcp_acktag_state"
	 * to carry current समय, flags, stats like "tcp_sacktag_state".
	 */
	अगर (delivered)
		tp->delivered_mstamp = tp->tcp_mstamp;

	rs->acked_sacked = delivered;	/* freshly ACKed or SACKed */
	rs->losses = lost;		/* freshly marked lost */
	/* Return an invalid sample अगर no timing inक्रमmation is available or
	 * in recovery from loss with SACK reneging. Rate samples taken during
	 * a SACK reneging event may overestimate bw by including packets that
	 * were SACKed beक्रमe the reneg.
	 */
	अगर (!rs->prior_mstamp || is_sack_reneg) अणु
		rs->delivered = -1;
		rs->पूर्णांकerval_us = -1;
		वापस;
	पूर्ण
	rs->delivered   = tp->delivered - rs->prior_delivered;

	/* Model sending data and receiving ACKs as separate pipeline phases
	 * क्रम a winकरोw. Usually the ACK phase is दीर्घer, but with ACK
	 * compression the send phase can be दीर्घer. To be safe we use the
	 * दीर्घer phase.
	 */
	snd_us = rs->पूर्णांकerval_us;				/* send phase */
	ack_us = tcp_stamp_us_delta(tp->tcp_mstamp,
				    rs->prior_mstamp); /* ack phase */
	rs->पूर्णांकerval_us = max(snd_us, ack_us);

	/* Record both segment send and ack receive पूर्णांकervals */
	rs->snd_पूर्णांकerval_us = snd_us;
	rs->rcv_पूर्णांकerval_us = ack_us;

	/* Normally we expect पूर्णांकerval_us >= min-rtt.
	 * Note that rate may still be over-estimated when a spuriously
	 * retransmistted skb was first (s)acked because "interval_us"
	 * is under-estimated (up to an RTT). However continuously
	 * measuring the delivery rate during loss recovery is crucial
	 * क्रम connections suffer heavy or proदीर्घed losses.
	 */
	अगर (unlikely(rs->पूर्णांकerval_us < tcp_min_rtt(tp))) अणु
		अगर (!rs->is_retrans)
			pr_debug("tcp rate: %ld %d %u %u %u\n",
				 rs->पूर्णांकerval_us, rs->delivered,
				 inet_csk(sk)->icsk_ca_state,
				 tp->rx_opt.sack_ok, tcp_min_rtt(tp));
		rs->पूर्णांकerval_us = -1;
		वापस;
	पूर्ण

	/* Record the last non-app-limited or the highest app-limited bw */
	अगर (!rs->is_app_limited ||
	    ((u64)rs->delivered * tp->rate_पूर्णांकerval_us >=
	     (u64)tp->rate_delivered * rs->पूर्णांकerval_us)) अणु
		tp->rate_delivered = rs->delivered;
		tp->rate_पूर्णांकerval_us = rs->पूर्णांकerval_us;
		tp->rate_app_limited = rs->is_app_limited;
	पूर्ण
पूर्ण

/* If a gap is detected between sends, mark the socket application-limited. */
व्योम tcp_rate_check_app_limited(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (/* We have less than one packet to send. */
	    tp->ग_लिखो_seq - tp->snd_nxt < tp->mss_cache &&
	    /* Nothing in sending host's qdisc queues or NIC tx queue. */
	    sk_wmem_alloc_get(sk) < SKB_TRUESIZE(1) &&
	    /* We are not limited by CWND. */
	    tcp_packets_in_flight(tp) < tp->snd_cwnd &&
	    /* All lost packets have been retransmitted. */
	    tp->lost_out <= tp->retrans_out)
		tp->app_limited =
			(tp->delivered + tcp_packets_in_flight(tp)) ? : 1;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_rate_check_app_limited);
