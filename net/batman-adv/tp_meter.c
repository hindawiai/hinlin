<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Eकरो Monticelli, Antonio Quartulli
 */

#समावेश "tp_meter.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/cache.h>
#समावेश <linux/compiler.h>
#समावेश <linux/err.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/minmax.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/param.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "hard-interface.h"
#समावेश "log.h"
#समावेश "netlink.h"
#समावेश "originator.h"
#समावेश "send.h"

/**
 * BATADV_TP_DEF_TEST_LENGTH - Default test length अगर not specअगरied by the user
 *  in milliseconds
 */
#घोषणा BATADV_TP_DEF_TEST_LENGTH 10000

/**
 * BATADV_TP_AWND - Advertised winकरोw by the receiver (in bytes)
 */
#घोषणा BATADV_TP_AWND 0x20000000

/**
 * BATADV_TP_RECV_TIMEOUT - Receiver activity समयout. If the receiver करोes not
 *  get anything क्रम such amount of milliseconds, the connection is समाप्तed
 */
#घोषणा BATADV_TP_RECV_TIMEOUT 1000

/**
 * BATADV_TP_MAX_RTO - Maximum sender समयout. If the sender RTO माला_लो beyond
 * such amount of milliseconds, the receiver is considered unreachable and the
 * connection is समाप्तed
 */
#घोषणा BATADV_TP_MAX_RTO 30000

/**
 * BATADV_TP_FIRST_SEQ - First seqno of each session. The number is rather high
 *  in order to immediately trigger a wrap around (test purposes)
 */
#घोषणा BATADV_TP_FIRST_SEQ ((u32)-1 - 2000)

/**
 * BATADV_TP_PLEN - length of the payload (data after the batadv_unicast header)
 *  to simulate
 */
#घोषणा BATADV_TP_PLEN (BATADV_TP_PACKET_LEN - ETH_HLEN - \
			माप(काष्ठा batadv_unicast_packet))

अटल u8 batadv_tp_preअक्रमom[4096] __पढ़ो_mostly;

/**
 * batadv_tp_session_cookie() - generate session cookie based on session ids
 * @session: TP session identअगरier
 * @icmp_uid: icmp pseuकरो uid of the tp session
 *
 * Return: 32 bit tp_meter session cookie
 */
अटल u32 batadv_tp_session_cookie(स्थिर u8 session[2], u8 icmp_uid)
अणु
	u32 cookie;

	cookie = icmp_uid << 16;
	cookie |= session[0] << 8;
	cookie |= session[1];

	वापस cookie;
पूर्ण

/**
 * batadv_tp_cwnd() - compute the new cwnd size
 * @base: base cwnd size value
 * @increment: the value to add to base to get the new size
 * @min: minimum cwnd value (usually MSS)
 *
 * Return the new cwnd size and ensure it करोes not exceed the Advertised
 * Receiver Winकरोw size. It is wrapped around safely.
 * For details refer to Section 3.1 of RFC5681
 *
 * Return: new congestion winकरोw size in bytes
 */
अटल u32 batadv_tp_cwnd(u32 base, u32 increment, u32 min)
अणु
	u32 new_size = base + increment;

	/* check क्रम wrap-around */
	अगर (new_size < base)
		new_size = (u32)अच_दीर्घ_उच्च;

	new_size = min_t(u32, new_size, BATADV_TP_AWND);

	वापस max_t(u32, new_size, min);
पूर्ण

/**
 * batadv_tp_update_cwnd() - update the Congestion Winकरोws
 * @tp_vars: the निजी data of the current TP meter session
 * @mss: maximum segment size of transmission
 *
 * 1) अगर the session is in Slow Start, the CWND has to be increased by 1
 * MSS every unique received ACK
 * 2) अगर the session is in Congestion Aव्योमance, the CWND has to be
 * increased by MSS * MSS / CWND क्रम every unique received ACK
 */
अटल व्योम batadv_tp_update_cwnd(काष्ठा batadv_tp_vars *tp_vars, u32 mss)
अणु
	spin_lock_bh(&tp_vars->cwnd_lock);

	/* slow start... */
	अगर (tp_vars->cwnd <= tp_vars->ss_threshold) अणु
		tp_vars->dec_cwnd = 0;
		tp_vars->cwnd = batadv_tp_cwnd(tp_vars->cwnd, mss, mss);
		spin_unlock_bh(&tp_vars->cwnd_lock);
		वापस;
	पूर्ण

	/* increment CWND at least of 1 (section 3.1 of RFC5681) */
	tp_vars->dec_cwnd += max_t(u32, 1U << 3,
				   ((mss * mss) << 6) / (tp_vars->cwnd << 3));
	अगर (tp_vars->dec_cwnd < (mss << 3)) अणु
		spin_unlock_bh(&tp_vars->cwnd_lock);
		वापस;
	पूर्ण

	tp_vars->cwnd = batadv_tp_cwnd(tp_vars->cwnd, mss, mss);
	tp_vars->dec_cwnd = 0;

	spin_unlock_bh(&tp_vars->cwnd_lock);
पूर्ण

/**
 * batadv_tp_update_rto() - calculate new retransmission समयout
 * @tp_vars: the निजी data of the current TP meter session
 * @new_rtt: new roundtrip समय in msec
 */
अटल व्योम batadv_tp_update_rto(काष्ठा batadv_tp_vars *tp_vars,
				 u32 new_rtt)
अणु
	दीर्घ m = new_rtt;

	/* RTT update
	 * Details in Section 2.2 and 2.3 of RFC6298
	 *
	 * It's tricky to understand. Don't lose hair please.
	 * Inspired by tcp_rtt_estimator() tcp_input.c
	 */
	अगर (tp_vars->srtt != 0) अणु
		m -= (tp_vars->srtt >> 3); /* m is now error in rtt est */
		tp_vars->srtt += m; /* rtt = 7/8 srtt + 1/8 new */
		अगर (m < 0)
			m = -m;

		m -= (tp_vars->rttvar >> 2);
		tp_vars->rttvar += m; /* mdev ~= 3/4 rttvar + 1/4 new */
	पूर्ण अन्यथा अणु
		/* first measure getting in */
		tp_vars->srtt = m << 3;	/* take the measured समय to be srtt */
		tp_vars->rttvar = m << 1; /* new_rtt / 2 */
	पूर्ण

	/* rto = srtt + 4 * rttvar.
	 * rttvar is scaled by 4, thereक्रमe करोesn't need to be multiplied
	 */
	tp_vars->rto = (tp_vars->srtt >> 3) + tp_vars->rttvar;
पूर्ण

/**
 * batadv_tp_batctl_notअगरy() - send client status result to client
 * @reason: reason क्रम tp meter session stop
 * @dst: destination of tp_meter session
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @start_समय: start of transmission in jअगरfies
 * @total_sent: bytes acked to the receiver
 * @cookie: cookie of tp_meter session
 */
अटल व्योम batadv_tp_batctl_notअगरy(क्रमागत batadv_tp_meter_reason reason,
				    स्थिर u8 *dst, काष्ठा batadv_priv *bat_priv,
				    अचिन्हित दीर्घ start_समय, u64 total_sent,
				    u32 cookie)
अणु
	u32 test_समय;
	u8 result;
	u32 total_bytes;

	अगर (!batadv_tp_is_error(reason)) अणु
		result = BATADV_TP_REASON_COMPLETE;
		test_समय = jअगरfies_to_msecs(jअगरfies - start_समय);
		total_bytes = total_sent;
	पूर्ण अन्यथा अणु
		result = reason;
		test_समय = 0;
		total_bytes = 0;
	पूर्ण

	batadv_netlink_tpmeter_notअगरy(bat_priv, dst, result, test_समय,
				      total_bytes, cookie);
पूर्ण

/**
 * batadv_tp_batctl_error_notअगरy() - send client error result to client
 * @reason: reason क्रम tp meter session stop
 * @dst: destination of tp_meter session
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @cookie: cookie of tp_meter session
 */
अटल व्योम batadv_tp_batctl_error_notअगरy(क्रमागत batadv_tp_meter_reason reason,
					  स्थिर u8 *dst,
					  काष्ठा batadv_priv *bat_priv,
					  u32 cookie)
अणु
	batadv_tp_batctl_notअगरy(reason, dst, bat_priv, 0, 0, cookie);
पूर्ण

/**
 * batadv_tp_list_find() - find a tp_vars object in the global list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @dst: the other endpoपूर्णांक MAC address to look क्रम
 *
 * Look क्रम a tp_vars object matching dst as end_poपूर्णांक and वापस it after
 * having increment the refcounter. Return शून्य is not found
 *
 * Return: matching tp_vars or शून्य when no tp_vars with @dst was found
 */
अटल काष्ठा batadv_tp_vars *batadv_tp_list_find(काष्ठा batadv_priv *bat_priv,
						  स्थिर u8 *dst)
अणु
	काष्ठा batadv_tp_vars *pos, *tp_vars = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(pos, &bat_priv->tp_list, list) अणु
		अगर (!batadv_compare_eth(pos->other_end, dst))
			जारी;

		/* most of the समय this function is invoked during the normal
		 * process..it makes sens to pay more when the session is
		 * finished and to speed the process up during the measurement
		 */
		अगर (unlikely(!kref_get_unless_zero(&pos->refcount)))
			जारी;

		tp_vars = pos;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस tp_vars;
पूर्ण

/**
 * batadv_tp_list_find_session() - find tp_vars session object in the global
 *  list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @dst: the other endpoपूर्णांक MAC address to look क्रम
 * @session: session identअगरier
 *
 * Look क्रम a tp_vars object matching dst as end_poपूर्णांक, session as tp meter
 * session and वापस it after having increment the refcounter. Return शून्य
 * is not found
 *
 * Return: matching tp_vars or शून्य when no tp_vars was found
 */
अटल काष्ठा batadv_tp_vars *
batadv_tp_list_find_session(काष्ठा batadv_priv *bat_priv, स्थिर u8 *dst,
			    स्थिर u8 *session)
अणु
	काष्ठा batadv_tp_vars *pos, *tp_vars = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(pos, &bat_priv->tp_list, list) अणु
		अगर (!batadv_compare_eth(pos->other_end, dst))
			जारी;

		अगर (स_भेद(pos->session, session, माप(pos->session)) != 0)
			जारी;

		/* most of the समय this function is invoked during the normal
		 * process..it makes sense to pay more when the session is
		 * finished and to speed the process up during the measurement
		 */
		अगर (unlikely(!kref_get_unless_zero(&pos->refcount)))
			जारी;

		tp_vars = pos;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस tp_vars;
पूर्ण

/**
 * batadv_tp_vars_release() - release batadv_tp_vars from lists and queue क्रम
 *  मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the batadv_tp_vars
 */
अटल व्योम batadv_tp_vars_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_tp_vars *tp_vars;
	काष्ठा batadv_tp_unacked *un, *safe;

	tp_vars = container_of(ref, काष्ठा batadv_tp_vars, refcount);

	/* lock should not be needed because this object is now out of any
	 * context!
	 */
	spin_lock_bh(&tp_vars->unacked_lock);
	list_क्रम_each_entry_safe(un, safe, &tp_vars->unacked_list, list) अणु
		list_del(&un->list);
		kमुक्त(un);
	पूर्ण
	spin_unlock_bh(&tp_vars->unacked_lock);

	kमुक्त_rcu(tp_vars, rcu);
पूर्ण

/**
 * batadv_tp_vars_put() - decrement the batadv_tp_vars refcounter and possibly
 *  release it
 * @tp_vars: the निजी data of the current TP meter session to be मुक्त'd
 */
अटल व्योम batadv_tp_vars_put(काष्ठा batadv_tp_vars *tp_vars)
अणु
	kref_put(&tp_vars->refcount, batadv_tp_vars_release);
पूर्ण

/**
 * batadv_tp_sender_cleanup() - cleanup sender data and drop and समयr
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tp_vars: the निजी data of the current TP meter session to cleanup
 */
अटल व्योम batadv_tp_sender_cleanup(काष्ठा batadv_priv *bat_priv,
				     काष्ठा batadv_tp_vars *tp_vars)
अणु
	cancel_delayed_work(&tp_vars->finish_work);

	spin_lock_bh(&tp_vars->bat_priv->tp_list_lock);
	hlist_del_rcu(&tp_vars->list);
	spin_unlock_bh(&tp_vars->bat_priv->tp_list_lock);

	/* drop list reference */
	batadv_tp_vars_put(tp_vars);

	atomic_dec(&tp_vars->bat_priv->tp_num);

	/* समाप्त the समयr and हटाओ its reference */
	del_समयr_sync(&tp_vars->समयr);
	/* the worker might have rearmed itself thereक्रमe we समाप्त it again. Note
	 * that अगर the worker should run again beक्रमe invoking the following
	 * del_समयr(), it would not re-arm itself once again because the status
	 * is OFF now
	 */
	del_समयr(&tp_vars->समयr);
	batadv_tp_vars_put(tp_vars);
पूर्ण

/**
 * batadv_tp_sender_end() - prपूर्णांक info about ended session and inक्रमm client
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tp_vars: the निजी data of the current TP meter session
 */
अटल व्योम batadv_tp_sender_end(काष्ठा batadv_priv *bat_priv,
				 काष्ठा batadv_tp_vars *tp_vars)
अणु
	u32 session_cookie;

	batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
		   "Test towards %pM finished..shutting down (reason=%d)\n",
		   tp_vars->other_end, tp_vars->reason);

	batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
		   "Last timing stats: SRTT=%ums RTTVAR=%ums RTO=%ums\n",
		   tp_vars->srtt >> 3, tp_vars->rttvar >> 2, tp_vars->rto);

	batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
		   "Final values: cwnd=%u ss_threshold=%u\n",
		   tp_vars->cwnd, tp_vars->ss_threshold);

	session_cookie = batadv_tp_session_cookie(tp_vars->session,
						  tp_vars->icmp_uid);

	batadv_tp_batctl_notअगरy(tp_vars->reason,
				tp_vars->other_end,
				bat_priv,
				tp_vars->start_समय,
				atomic64_पढ़ो(&tp_vars->tot_sent),
				session_cookie);
पूर्ण

/**
 * batadv_tp_sender_shutकरोwn() - let sender thपढ़ो/समयr stop gracefully
 * @tp_vars: the निजी data of the current TP meter session
 * @reason: reason क्रम tp meter session stop
 */
अटल व्योम batadv_tp_sender_shutकरोwn(काष्ठा batadv_tp_vars *tp_vars,
				      क्रमागत batadv_tp_meter_reason reason)
अणु
	अगर (!atomic_dec_and_test(&tp_vars->sending))
		वापस;

	tp_vars->reason = reason;
पूर्ण

/**
 * batadv_tp_sender_finish() - stop sender session after test_length was reached
 * @work: delayed work reference of the related tp_vars
 */
अटल व्योम batadv_tp_sender_finish(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work;
	काष्ठा batadv_tp_vars *tp_vars;

	delayed_work = to_delayed_work(work);
	tp_vars = container_of(delayed_work, काष्ठा batadv_tp_vars,
			       finish_work);

	batadv_tp_sender_shutकरोwn(tp_vars, BATADV_TP_REASON_COMPLETE);
पूर्ण

/**
 * batadv_tp_reset_sender_समयr() - reschedule the sender समयr
 * @tp_vars: the निजी TP meter data क्रम this session
 *
 * Reschedule the समयr using tp_vars->rto as delay
 */
अटल व्योम batadv_tp_reset_sender_समयr(काष्ठा batadv_tp_vars *tp_vars)
अणु
	/* most of the समय this function is invoked जबतक normal packet
	 * reception...
	 */
	अगर (unlikely(atomic_पढ़ो(&tp_vars->sending) == 0))
		/* समयr ref will be dropped in batadv_tp_sender_cleanup */
		वापस;

	mod_समयr(&tp_vars->समयr, jअगरfies + msecs_to_jअगरfies(tp_vars->rto));
पूर्ण

/**
 * batadv_tp_sender_समयout() - समयr that fires in हाल of packet loss
 * @t: address to समयr_list inside tp_vars
 *
 * If fired it means that there was packet loss.
 * Switch to Slow Start, set the ss_threshold to half of the current cwnd and
 * reset the cwnd to 3*MSS
 */
अटल व्योम batadv_tp_sender_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा batadv_tp_vars *tp_vars = from_समयr(tp_vars, t, समयr);
	काष्ठा batadv_priv *bat_priv = tp_vars->bat_priv;

	अगर (atomic_पढ़ो(&tp_vars->sending) == 0)
		वापस;

	/* अगर the user रुकोed दीर्घ enough...shutकरोwn the test */
	अगर (unlikely(tp_vars->rto >= BATADV_TP_MAX_RTO)) अणु
		batadv_tp_sender_shutकरोwn(tp_vars,
					  BATADV_TP_REASON_DST_UNREACHABLE);
		वापस;
	पूर्ण

	/* RTO exponential backoff
	 * Details in Section 5.5 of RFC6298
	 */
	tp_vars->rto <<= 1;

	spin_lock_bh(&tp_vars->cwnd_lock);

	tp_vars->ss_threshold = tp_vars->cwnd >> 1;
	अगर (tp_vars->ss_threshold < BATADV_TP_PLEN * 2)
		tp_vars->ss_threshold = BATADV_TP_PLEN * 2;

	batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
		   "Meter: RTO fired during test towards %pM! cwnd=%u new ss_thr=%u, resetting last_sent to %u\n",
		   tp_vars->other_end, tp_vars->cwnd, tp_vars->ss_threshold,
		   atomic_पढ़ो(&tp_vars->last_acked));

	tp_vars->cwnd = BATADV_TP_PLEN * 3;

	spin_unlock_bh(&tp_vars->cwnd_lock);

	/* resend the non-ACKed packets.. */
	tp_vars->last_sent = atomic_पढ़ो(&tp_vars->last_acked);
	wake_up(&tp_vars->more_bytes);

	batadv_tp_reset_sender_समयr(tp_vars);
पूर्ण

/**
 * batadv_tp_fill_preअक्रमom() - Fill buffer with prefetched अक्रमom bytes
 * @tp_vars: the निजी TP meter data क्रम this session
 * @buf: Buffer to fill with bytes
 * @nbytes: amount of pseuकरोअक्रमom bytes
 */
अटल व्योम batadv_tp_fill_preअक्रमom(काष्ठा batadv_tp_vars *tp_vars,
				     u8 *buf, माप_प्रकार nbytes)
अणु
	u32 local_offset;
	माप_प्रकार bytes_inbuf;
	माप_प्रकार to_copy;
	माप_प्रकार pos = 0;

	spin_lock_bh(&tp_vars->preअक्रमom_lock);
	local_offset = tp_vars->preअक्रमom_offset;
	tp_vars->preअक्रमom_offset += nbytes;
	tp_vars->preअक्रमom_offset %= माप(batadv_tp_preअक्रमom);
	spin_unlock_bh(&tp_vars->preअक्रमom_lock);

	जबतक (nbytes) अणु
		local_offset %= माप(batadv_tp_preअक्रमom);
		bytes_inbuf = माप(batadv_tp_preअक्रमom) - local_offset;
		to_copy = min(nbytes, bytes_inbuf);

		स_नकल(&buf[pos], &batadv_tp_preअक्रमom[local_offset], to_copy);
		pos += to_copy;
		nbytes -= to_copy;
		local_offset = 0;
	पूर्ण
पूर्ण

/**
 * batadv_tp_send_msg() - send a single message
 * @tp_vars: the निजी TP meter data क्रम this session
 * @src: source mac address
 * @orig_node: the originator of the destination
 * @seqno: sequence number of this packet
 * @len: length of the entire packet
 * @session: session identअगरier
 * @uid: local ICMP "socket" index
 * @बारtamp: बारtamp in jअगरfies which is replied in ack
 *
 * Create and send a single TP Meter message.
 *
 * Return: 0 on success, BATADV_TP_REASON_DST_UNREACHABLE अगर the destination is
 * not reachable, BATADV_TP_REASON_MEMORY_ERROR अगर the packet couldn't be
 * allocated
 */
अटल पूर्णांक batadv_tp_send_msg(काष्ठा batadv_tp_vars *tp_vars, स्थिर u8 *src,
			      काष्ठा batadv_orig_node *orig_node,
			      u32 seqno, माप_प्रकार len, स्थिर u8 *session,
			      पूर्णांक uid, u32 बारtamp)
अणु
	काष्ठा batadv_icmp_tp_packet *icmp;
	काष्ठा sk_buff *skb;
	पूर्णांक r;
	u8 *data;
	माप_प्रकार data_len;

	skb = netdev_alloc_skb_ip_align(शून्य, len + ETH_HLEN);
	अगर (unlikely(!skb))
		वापस BATADV_TP_REASON_MEMORY_ERROR;

	skb_reserve(skb, ETH_HLEN);
	icmp = skb_put(skb, माप(*icmp));

	/* fill the icmp header */
	ether_addr_copy(icmp->dst, orig_node->orig);
	ether_addr_copy(icmp->orig, src);
	icmp->version = BATADV_COMPAT_VERSION;
	icmp->packet_type = BATADV_ICMP;
	icmp->ttl = BATADV_TTL;
	icmp->msg_type = BATADV_TP;
	icmp->uid = uid;

	icmp->subtype = BATADV_TP_MSG;
	स_नकल(icmp->session, session, माप(icmp->session));
	icmp->seqno = htonl(seqno);
	icmp->बारtamp = htonl(बारtamp);

	data_len = len - माप(*icmp);
	data = skb_put(skb, data_len);
	batadv_tp_fill_preअक्रमom(tp_vars, data, data_len);

	r = batadv_send_skb_to_orig(skb, orig_node, शून्य);
	अगर (r == NET_XMIT_SUCCESS)
		वापस 0;

	वापस BATADV_TP_REASON_CANT_SEND;
पूर्ण

/**
 * batadv_tp_recv_ack() - ACK receiving function
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the buffer containing the received packet
 *
 * Process a received TP ACK packet
 */
अटल व्योम batadv_tp_recv_ack(काष्ठा batadv_priv *bat_priv,
			       स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_orig_node *orig_node = शून्य;
	स्थिर काष्ठा batadv_icmp_tp_packet *icmp;
	काष्ठा batadv_tp_vars *tp_vars;
	माप_प्रकार packet_len, mss;
	u32 rtt, recv_ack, cwnd;
	अचिन्हित अक्षर *dev_addr;

	packet_len = BATADV_TP_PLEN;
	mss = BATADV_TP_PLEN;
	packet_len += माप(काष्ठा batadv_unicast_packet);

	icmp = (काष्ठा batadv_icmp_tp_packet *)skb->data;

	/* find the tp_vars */
	tp_vars = batadv_tp_list_find_session(bat_priv, icmp->orig,
					      icmp->session);
	अगर (unlikely(!tp_vars))
		वापस;

	अगर (unlikely(atomic_पढ़ो(&tp_vars->sending) == 0))
		जाओ out;

	/* old ACK? silently drop it.. */
	अगर (batadv_seq_beक्रमe(ntohl(icmp->seqno),
			      (u32)atomic_पढ़ो(&tp_vars->last_acked)))
		जाओ out;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (unlikely(!primary_अगर))
		जाओ out;

	orig_node = batadv_orig_hash_find(bat_priv, icmp->orig);
	अगर (unlikely(!orig_node))
		जाओ out;

	/* update RTO with the new sampled RTT, अगर any */
	rtt = jअगरfies_to_msecs(jअगरfies) - ntohl(icmp->बारtamp);
	अगर (icmp->बारtamp && rtt)
		batadv_tp_update_rto(tp_vars, rtt);

	/* ACK क्रम new data... reset the समयr */
	batadv_tp_reset_sender_समयr(tp_vars);

	recv_ack = ntohl(icmp->seqno);

	/* check अगर this ACK is a duplicate */
	अगर (atomic_पढ़ो(&tp_vars->last_acked) == recv_ack) अणु
		atomic_inc(&tp_vars->dup_acks);
		अगर (atomic_पढ़ो(&tp_vars->dup_acks) != 3)
			जाओ out;

		अगर (recv_ack >= tp_vars->recover)
			जाओ out;

		/* अगर this is the third duplicate ACK करो Fast Retransmit */
		batadv_tp_send_msg(tp_vars, primary_अगर->net_dev->dev_addr,
				   orig_node, recv_ack, packet_len,
				   icmp->session, icmp->uid,
				   jअगरfies_to_msecs(jअगरfies));

		spin_lock_bh(&tp_vars->cwnd_lock);

		/* Fast Recovery */
		tp_vars->fast_recovery = true;
		/* Set recover to the last outstanding seqno when Fast Recovery
		 * is entered. RFC6582, Section 3.2, step 1
		 */
		tp_vars->recover = tp_vars->last_sent;
		tp_vars->ss_threshold = tp_vars->cwnd >> 1;
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Meter: Fast Recovery, (cur cwnd=%u) ss_thr=%u last_sent=%u recv_ack=%u\n",
			   tp_vars->cwnd, tp_vars->ss_threshold,
			   tp_vars->last_sent, recv_ack);
		tp_vars->cwnd = batadv_tp_cwnd(tp_vars->ss_threshold, 3 * mss,
					       mss);
		tp_vars->dec_cwnd = 0;
		tp_vars->last_sent = recv_ack;

		spin_unlock_bh(&tp_vars->cwnd_lock);
	पूर्ण अन्यथा अणु
		/* count the acked data */
		atomic64_add(recv_ack - atomic_पढ़ो(&tp_vars->last_acked),
			     &tp_vars->tot_sent);
		/* reset the duplicate ACKs counter */
		atomic_set(&tp_vars->dup_acks, 0);

		अगर (tp_vars->fast_recovery) अणु
			/* partial ACK */
			अगर (batadv_seq_beक्रमe(recv_ack, tp_vars->recover)) अणु
				/* this is another hole in the winकरोw. React
				 * immediately as specअगरied by NewReno (see
				 * Section 3.2 of RFC6582 क्रम details)
				 */
				dev_addr = primary_अगर->net_dev->dev_addr;
				batadv_tp_send_msg(tp_vars, dev_addr,
						   orig_node, recv_ack,
						   packet_len, icmp->session,
						   icmp->uid,
						   jअगरfies_to_msecs(jअगरfies));
				tp_vars->cwnd = batadv_tp_cwnd(tp_vars->cwnd,
							       mss, mss);
			पूर्ण अन्यथा अणु
				tp_vars->fast_recovery = false;
				/* set cwnd to the value of ss_threshold at the
				 * moment that Fast Recovery was entered.
				 * RFC6582, Section 3.2, step 3
				 */
				cwnd = batadv_tp_cwnd(tp_vars->ss_threshold, 0,
						      mss);
				tp_vars->cwnd = cwnd;
			पूर्ण
			जाओ move_twnd;
		पूर्ण

		अगर (recv_ack - atomic_पढ़ो(&tp_vars->last_acked) >= mss)
			batadv_tp_update_cwnd(tp_vars, mss);
move_twnd:
		/* move the Transmit Winकरोw */
		atomic_set(&tp_vars->last_acked, recv_ack);
	पूर्ण

	wake_up(&tp_vars->more_bytes);
out:
	अगर (likely(primary_अगर))
		batadv_hardअगर_put(primary_अगर);
	अगर (likely(orig_node))
		batadv_orig_node_put(orig_node);
	अगर (likely(tp_vars))
		batadv_tp_vars_put(tp_vars);
पूर्ण

/**
 * batadv_tp_avail() - check अगर congestion winकरोw is not full
 * @tp_vars: the निजी data of the current TP meter session
 * @payload_len: size of the payload of a single message
 *
 * Return: true when congestion winकरोw is not full, false otherwise
 */
अटल bool batadv_tp_avail(काष्ठा batadv_tp_vars *tp_vars,
			    माप_प्रकार payload_len)
अणु
	u32 win_left, win_limit;

	win_limit = atomic_पढ़ो(&tp_vars->last_acked) + tp_vars->cwnd;
	win_left = win_limit - tp_vars->last_sent;

	वापस win_left >= payload_len;
पूर्ण

/**
 * batadv_tp_रुको_available() - रुको until congestion winकरोw becomes मुक्त or
 *  समयout is reached
 * @tp_vars: the निजी data of the current TP meter session
 * @plen: size of the payload of a single message
 *
 * Return: 0 अगर the condition evaluated to false after the समयout elapsed,
 *  1 अगर the condition evaluated to true after the समयout elapsed, the
 *  reमुख्यing jअगरfies (at least 1) अगर the condition evaluated to true beक्रमe
 *  the समयout elapsed, or -ERESTARTSYS अगर it was पूर्णांकerrupted by a संकेत.
 */
अटल पूर्णांक batadv_tp_रुको_available(काष्ठा batadv_tp_vars *tp_vars, माप_प्रकार plen)
अणु
	पूर्णांक ret;

	ret = रुको_event_पूर्णांकerruptible_समयout(tp_vars->more_bytes,
					       batadv_tp_avail(tp_vars, plen),
					       HZ / 10);

	वापस ret;
पूर्ण

/**
 * batadv_tp_send() - मुख्य sending thपढ़ो of a tp meter session
 * @arg: address of the related tp_vars
 *
 * Return: nothing, this function never वापसs
 */
अटल पूर्णांक batadv_tp_send(व्योम *arg)
अणु
	काष्ठा batadv_tp_vars *tp_vars = arg;
	काष्ठा batadv_priv *bat_priv = tp_vars->bat_priv;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_orig_node *orig_node = शून्य;
	माप_प्रकार payload_len, packet_len;
	पूर्णांक err = 0;

	अगर (unlikely(tp_vars->role != BATADV_TP_SENDER)) अणु
		err = BATADV_TP_REASON_DST_UNREACHABLE;
		tp_vars->reason = err;
		जाओ out;
	पूर्ण

	orig_node = batadv_orig_hash_find(bat_priv, tp_vars->other_end);
	अगर (unlikely(!orig_node)) अणु
		err = BATADV_TP_REASON_DST_UNREACHABLE;
		tp_vars->reason = err;
		जाओ out;
	पूर्ण

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (unlikely(!primary_अगर)) अणु
		err = BATADV_TP_REASON_DST_UNREACHABLE;
		tp_vars->reason = err;
		जाओ out;
	पूर्ण

	/* assume that all the hard_पूर्णांकerfaces have a correctly
	 * configured MTU, so use the soft_अगरace MTU as MSS.
	 * This might not be true and in that हाल the fragmentation
	 * should be used.
	 * Now, try to send the packet as it is
	 */
	payload_len = BATADV_TP_PLEN;
	BUILD_BUG_ON(माप(काष्ठा batadv_icmp_tp_packet) > BATADV_TP_PLEN);

	batadv_tp_reset_sender_समयr(tp_vars);

	/* queue the worker in अक्षरge of terminating the test */
	queue_delayed_work(batadv_event_workqueue, &tp_vars->finish_work,
			   msecs_to_jअगरfies(tp_vars->test_length));

	जबतक (atomic_पढ़ो(&tp_vars->sending) != 0) अणु
		अगर (unlikely(!batadv_tp_avail(tp_vars, payload_len))) अणु
			batadv_tp_रुको_available(tp_vars, payload_len);
			जारी;
		पूर्ण

		/* to emulate normal unicast traffic, add to the payload len
		 * the size of the unicast header
		 */
		packet_len = payload_len + माप(काष्ठा batadv_unicast_packet);

		err = batadv_tp_send_msg(tp_vars, primary_अगर->net_dev->dev_addr,
					 orig_node, tp_vars->last_sent,
					 packet_len,
					 tp_vars->session, tp_vars->icmp_uid,
					 jअगरfies_to_msecs(jअगरfies));

		/* something went wrong during the preparation/transmission */
		अगर (unlikely(err && err != BATADV_TP_REASON_CANT_SEND)) अणु
			batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
				   "Meter: %s() cannot send packets (%d)\n",
				   __func__, err);
			/* ensure nobody अन्यथा tries to stop the thपढ़ो now */
			अगर (atomic_dec_and_test(&tp_vars->sending))
				tp_vars->reason = err;
			अवरोध;
		पूर्ण

		/* right-shअगरt the TWND */
		अगर (!err)
			tp_vars->last_sent += payload_len;

		cond_resched();
	पूर्ण

out:
	अगर (likely(primary_अगर))
		batadv_hardअगर_put(primary_अगर);
	अगर (likely(orig_node))
		batadv_orig_node_put(orig_node);

	batadv_tp_sender_end(bat_priv, tp_vars);
	batadv_tp_sender_cleanup(bat_priv, tp_vars);

	batadv_tp_vars_put(tp_vars);

	करो_निकास(0);
पूर्ण

/**
 * batadv_tp_start_kthपढ़ो() - start new thपढ़ो which manages the tp meter
 *  sender
 * @tp_vars: the निजी data of the current TP meter session
 */
अटल व्योम batadv_tp_start_kthपढ़ो(काष्ठा batadv_tp_vars *tp_vars)
अणु
	काष्ठा task_काष्ठा *kthपढ़ो;
	काष्ठा batadv_priv *bat_priv = tp_vars->bat_priv;
	u32 session_cookie;

	kref_get(&tp_vars->refcount);
	kthपढ़ो = kthपढ़ो_create(batadv_tp_send, tp_vars, "kbatadv_tp_meter");
	अगर (IS_ERR(kthपढ़ो)) अणु
		session_cookie = batadv_tp_session_cookie(tp_vars->session,
							  tp_vars->icmp_uid);
		pr_err("batadv: cannot create tp meter kthread\n");
		batadv_tp_batctl_error_notअगरy(BATADV_TP_REASON_MEMORY_ERROR,
					      tp_vars->other_end,
					      bat_priv, session_cookie);

		/* drop reserved reference क्रम kthपढ़ो */
		batadv_tp_vars_put(tp_vars);

		/* cleanup of failed tp meter variables */
		batadv_tp_sender_cleanup(bat_priv, tp_vars);
		वापस;
	पूर्ण

	wake_up_process(kthपढ़ो);
पूर्ण

/**
 * batadv_tp_start() - start a new tp meter session
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @dst: the receiver MAC address
 * @test_length: test length in milliseconds
 * @cookie: session cookie
 */
व्योम batadv_tp_start(काष्ठा batadv_priv *bat_priv, स्थिर u8 *dst,
		     u32 test_length, u32 *cookie)
अणु
	काष्ठा batadv_tp_vars *tp_vars;
	u8 session_id[2];
	u8 icmp_uid;
	u32 session_cookie;

	get_अक्रमom_bytes(session_id, माप(session_id));
	get_अक्रमom_bytes(&icmp_uid, 1);
	session_cookie = batadv_tp_session_cookie(session_id, icmp_uid);
	*cookie = session_cookie;

	/* look क्रम an alपढ़ोy existing test towards this node */
	spin_lock_bh(&bat_priv->tp_list_lock);
	tp_vars = batadv_tp_list_find(bat_priv, dst);
	अगर (tp_vars) अणु
		spin_unlock_bh(&bat_priv->tp_list_lock);
		batadv_tp_vars_put(tp_vars);
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Meter: test to or from the same node already ongoing, aborting\n");
		batadv_tp_batctl_error_notअगरy(BATADV_TP_REASON_ALREADY_ONGOING,
					      dst, bat_priv, session_cookie);
		वापस;
	पूर्ण

	अगर (!atomic_add_unless(&bat_priv->tp_num, 1, BATADV_TP_MAX_NUM)) अणु
		spin_unlock_bh(&bat_priv->tp_list_lock);
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Meter: too many ongoing sessions, aborting (SEND)\n");
		batadv_tp_batctl_error_notअगरy(BATADV_TP_REASON_TOO_MANY, dst,
					      bat_priv, session_cookie);
		वापस;
	पूर्ण

	tp_vars = kदो_स्मृति(माप(*tp_vars), GFP_ATOMIC);
	अगर (!tp_vars) अणु
		spin_unlock_bh(&bat_priv->tp_list_lock);
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Meter: %s cannot allocate list elements\n",
			   __func__);
		batadv_tp_batctl_error_notअगरy(BATADV_TP_REASON_MEMORY_ERROR,
					      dst, bat_priv, session_cookie);
		वापस;
	पूर्ण

	/* initialize tp_vars */
	ether_addr_copy(tp_vars->other_end, dst);
	kref_init(&tp_vars->refcount);
	tp_vars->role = BATADV_TP_SENDER;
	atomic_set(&tp_vars->sending, 1);
	स_नकल(tp_vars->session, session_id, माप(session_id));
	tp_vars->icmp_uid = icmp_uid;

	tp_vars->last_sent = BATADV_TP_FIRST_SEQ;
	atomic_set(&tp_vars->last_acked, BATADV_TP_FIRST_SEQ);
	tp_vars->fast_recovery = false;
	tp_vars->recover = BATADV_TP_FIRST_SEQ;

	/* initialise the CWND to 3*MSS (Section 3.1 in RFC5681).
	 * For baपंचांगan-adv the MSS is the size of the payload received by the
	 * soft_पूर्णांकerface, hence its MTU
	 */
	tp_vars->cwnd = BATADV_TP_PLEN * 3;
	/* at the beginning initialise the SS threshold to the biggest possible
	 * winकरोw size, hence the AWND size
	 */
	tp_vars->ss_threshold = BATADV_TP_AWND;

	/* RTO initial value is 3 seconds.
	 * Details in Section 2.1 of RFC6298
	 */
	tp_vars->rto = 1000;
	tp_vars->srtt = 0;
	tp_vars->rttvar = 0;

	atomic64_set(&tp_vars->tot_sent, 0);

	kref_get(&tp_vars->refcount);
	समयr_setup(&tp_vars->समयr, batadv_tp_sender_समयout, 0);

	tp_vars->bat_priv = bat_priv;
	tp_vars->start_समय = jअगरfies;

	init_रुकोqueue_head(&tp_vars->more_bytes);

	spin_lock_init(&tp_vars->unacked_lock);
	INIT_LIST_HEAD(&tp_vars->unacked_list);

	spin_lock_init(&tp_vars->cwnd_lock);

	tp_vars->preअक्रमom_offset = 0;
	spin_lock_init(&tp_vars->preअक्रमom_lock);

	kref_get(&tp_vars->refcount);
	hlist_add_head_rcu(&tp_vars->list, &bat_priv->tp_list);
	spin_unlock_bh(&bat_priv->tp_list_lock);

	tp_vars->test_length = test_length;
	अगर (!tp_vars->test_length)
		tp_vars->test_length = BATADV_TP_DEF_TEST_LENGTH;

	batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
		   "Meter: starting throughput meter towards %pM (length=%ums)\n",
		   dst, test_length);

	/* init work item क्रम finished tp tests */
	INIT_DELAYED_WORK(&tp_vars->finish_work, batadv_tp_sender_finish);

	/* start tp kthपढ़ो. This way the ग_लिखो() call issued from userspace can
	 * happily वापस and aव्योम to block
	 */
	batadv_tp_start_kthपढ़ो(tp_vars);

	/* करोn't वापस reference to new tp_vars */
	batadv_tp_vars_put(tp_vars);
पूर्ण

/**
 * batadv_tp_stop() - stop currently running tp meter session
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @dst: the receiver MAC address
 * @वापस_value: reason क्रम tp meter session stop
 */
व्योम batadv_tp_stop(काष्ठा batadv_priv *bat_priv, स्थिर u8 *dst,
		    u8 वापस_value)
अणु
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा batadv_tp_vars *tp_vars;

	batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
		   "Meter: stopping test towards %pM\n", dst);

	orig_node = batadv_orig_hash_find(bat_priv, dst);
	अगर (!orig_node)
		वापस;

	tp_vars = batadv_tp_list_find(bat_priv, orig_node->orig);
	अगर (!tp_vars) अणु
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Meter: trying to interrupt an already over connection\n");
		जाओ out;
	पूर्ण

	batadv_tp_sender_shutकरोwn(tp_vars, वापस_value);
	batadv_tp_vars_put(tp_vars);
out:
	batadv_orig_node_put(orig_node);
पूर्ण

/**
 * batadv_tp_reset_receiver_समयr() - reset the receiver shutकरोwn समयr
 * @tp_vars: the निजी data of the current TP meter session
 *
 * start the receiver shutकरोwn समयr or reset it अगर alपढ़ोy started
 */
अटल व्योम batadv_tp_reset_receiver_समयr(काष्ठा batadv_tp_vars *tp_vars)
अणु
	mod_समयr(&tp_vars->समयr,
		  jअगरfies + msecs_to_jअगरfies(BATADV_TP_RECV_TIMEOUT));
पूर्ण

/**
 * batadv_tp_receiver_shutकरोwn() - stop a tp meter receiver when समयout is
 *  reached without received ack
 * @t: address to समयr_list inside tp_vars
 */
अटल व्योम batadv_tp_receiver_shutकरोwn(काष्ठा समयr_list *t)
अणु
	काष्ठा batadv_tp_vars *tp_vars = from_समयr(tp_vars, t, समयr);
	काष्ठा batadv_tp_unacked *un, *safe;
	काष्ठा batadv_priv *bat_priv;

	bat_priv = tp_vars->bat_priv;

	/* अगर there is recent activity rearm the समयr */
	अगर (!batadv_has_समयd_out(tp_vars->last_recv_समय,
				  BATADV_TP_RECV_TIMEOUT)) अणु
		/* reset the receiver shutकरोwn समयr */
		batadv_tp_reset_receiver_समयr(tp_vars);
		वापस;
	पूर्ण

	batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
		   "Shutting down for inactivity (more than %dms) from %pM\n",
		   BATADV_TP_RECV_TIMEOUT, tp_vars->other_end);

	spin_lock_bh(&tp_vars->bat_priv->tp_list_lock);
	hlist_del_rcu(&tp_vars->list);
	spin_unlock_bh(&tp_vars->bat_priv->tp_list_lock);

	/* drop list reference */
	batadv_tp_vars_put(tp_vars);

	atomic_dec(&bat_priv->tp_num);

	spin_lock_bh(&tp_vars->unacked_lock);
	list_क्रम_each_entry_safe(un, safe, &tp_vars->unacked_list, list) अणु
		list_del(&un->list);
		kमुक्त(un);
	पूर्ण
	spin_unlock_bh(&tp_vars->unacked_lock);

	/* drop reference of समयr */
	batadv_tp_vars_put(tp_vars);
पूर्ण

/**
 * batadv_tp_send_ack() - send an ACK packet
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @dst: the mac address of the destination originator
 * @seq: the sequence number to ACK
 * @बारtamp: the बारtamp to echo back in the ACK
 * @session: session identअगरier
 * @socket_index: local ICMP socket identअगरier
 *
 * Return: 0 on success, a positive पूर्णांकeger representing the reason of the
 * failure otherwise
 */
अटल पूर्णांक batadv_tp_send_ack(काष्ठा batadv_priv *bat_priv, स्थिर u8 *dst,
			      u32 seq, __be32 बारtamp, स्थिर u8 *session,
			      पूर्णांक socket_index)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा batadv_icmp_tp_packet *icmp;
	काष्ठा sk_buff *skb;
	पूर्णांक r, ret;

	orig_node = batadv_orig_hash_find(bat_priv, dst);
	अगर (unlikely(!orig_node)) अणु
		ret = BATADV_TP_REASON_DST_UNREACHABLE;
		जाओ out;
	पूर्ण

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (unlikely(!primary_अगर)) अणु
		ret = BATADV_TP_REASON_DST_UNREACHABLE;
		जाओ out;
	पूर्ण

	skb = netdev_alloc_skb_ip_align(शून्य, माप(*icmp) + ETH_HLEN);
	अगर (unlikely(!skb)) अणु
		ret = BATADV_TP_REASON_MEMORY_ERROR;
		जाओ out;
	पूर्ण

	skb_reserve(skb, ETH_HLEN);
	icmp = skb_put(skb, माप(*icmp));
	icmp->packet_type = BATADV_ICMP;
	icmp->version = BATADV_COMPAT_VERSION;
	icmp->ttl = BATADV_TTL;
	icmp->msg_type = BATADV_TP;
	ether_addr_copy(icmp->dst, orig_node->orig);
	ether_addr_copy(icmp->orig, primary_अगर->net_dev->dev_addr);
	icmp->uid = socket_index;

	icmp->subtype = BATADV_TP_ACK;
	स_नकल(icmp->session, session, माप(icmp->session));
	icmp->seqno = htonl(seq);
	icmp->बारtamp = बारtamp;

	/* send the ack */
	r = batadv_send_skb_to_orig(skb, orig_node, शून्य);
	अगर (unlikely(r < 0) || r == NET_XMIT_DROP) अणु
		ret = BATADV_TP_REASON_DST_UNREACHABLE;
		जाओ out;
	पूर्ण
	ret = 0;

out:
	अगर (likely(orig_node))
		batadv_orig_node_put(orig_node);
	अगर (likely(primary_अगर))
		batadv_hardअगर_put(primary_अगर);

	वापस ret;
पूर्ण

/**
 * batadv_tp_handle_out_of_order() - store an out of order packet
 * @tp_vars: the निजी data of the current TP meter session
 * @skb: the buffer containing the received packet
 *
 * Store the out of order packet in the unacked list क्रम late processing. This
 * packets are kept in this list so that they can be ACKed at once as soon as
 * all the previous packets have been received
 *
 * Return: true अगर the packed has been successfully processed, false otherwise
 */
अटल bool batadv_tp_handle_out_of_order(काष्ठा batadv_tp_vars *tp_vars,
					  स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा batadv_icmp_tp_packet *icmp;
	काष्ठा batadv_tp_unacked *un, *new;
	u32 payload_len;
	bool added = false;

	new = kदो_स्मृति(माप(*new), GFP_ATOMIC);
	अगर (unlikely(!new))
		वापस false;

	icmp = (काष्ठा batadv_icmp_tp_packet *)skb->data;

	new->seqno = ntohl(icmp->seqno);
	payload_len = skb->len - माप(काष्ठा batadv_unicast_packet);
	new->len = payload_len;

	spin_lock_bh(&tp_vars->unacked_lock);
	/* अगर the list is empty immediately attach this new object */
	अगर (list_empty(&tp_vars->unacked_list)) अणु
		list_add(&new->list, &tp_vars->unacked_list);
		जाओ out;
	पूर्ण

	/* otherwise loop over the list and either drop the packet because this
	 * is a duplicate or store it at the right position.
	 *
	 * The iteration is करोne in the reverse way because it is likely that
	 * the last received packet (the one being processed now) has a bigger
	 * seqno than all the others alपढ़ोy stored.
	 */
	list_क्रम_each_entry_reverse(un, &tp_vars->unacked_list, list) अणु
		/* check क्रम duplicates */
		अगर (new->seqno == un->seqno) अणु
			अगर (new->len > un->len)
				un->len = new->len;
			kमुक्त(new);
			added = true;
			अवरोध;
		पूर्ण

		/* look क्रम the right position */
		अगर (batadv_seq_beक्रमe(new->seqno, un->seqno))
			जारी;

		/* as soon as an entry having a bigger seqno is found, the new
		 * one is attached _after_ it. In this way the list is kept in
		 * ascending order
		 */
		list_add_tail(&new->list, &un->list);
		added = true;
		अवरोध;
	पूर्ण

	/* received packet with smallest seqno out of order; add it to front */
	अगर (!added)
		list_add(&new->list, &tp_vars->unacked_list);

out:
	spin_unlock_bh(&tp_vars->unacked_lock);

	वापस true;
पूर्ण

/**
 * batadv_tp_ack_unordered() - update number received bytes in current stream
 *  without gaps
 * @tp_vars: the निजी data of the current TP meter session
 */
अटल व्योम batadv_tp_ack_unordered(काष्ठा batadv_tp_vars *tp_vars)
अणु
	काष्ठा batadv_tp_unacked *un, *safe;
	u32 to_ack;

	/* go through the unacked packet list and possibly ACK them as
	 * well
	 */
	spin_lock_bh(&tp_vars->unacked_lock);
	list_क्रम_each_entry_safe(un, safe, &tp_vars->unacked_list, list) अणु
		/* the list is ordered, thereक्रमe it is possible to stop as soon
		 * there is a gap between the last acked seqno and the seqno of
		 * the packet under inspection
		 */
		अगर (batadv_seq_beक्रमe(tp_vars->last_recv, un->seqno))
			अवरोध;

		to_ack = un->seqno + un->len - tp_vars->last_recv;

		अगर (batadv_seq_beक्रमe(tp_vars->last_recv, un->seqno + un->len))
			tp_vars->last_recv += to_ack;

		list_del(&un->list);
		kमुक्त(un);
	पूर्ण
	spin_unlock_bh(&tp_vars->unacked_lock);
पूर्ण

/**
 * batadv_tp_init_recv() - वापस matching or create new receiver tp_vars
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @icmp: received icmp tp msg
 *
 * Return: corresponding tp_vars or शून्य on errors
 */
अटल काष्ठा batadv_tp_vars *
batadv_tp_init_recv(काष्ठा batadv_priv *bat_priv,
		    स्थिर काष्ठा batadv_icmp_tp_packet *icmp)
अणु
	काष्ठा batadv_tp_vars *tp_vars;

	spin_lock_bh(&bat_priv->tp_list_lock);
	tp_vars = batadv_tp_list_find_session(bat_priv, icmp->orig,
					      icmp->session);
	अगर (tp_vars)
		जाओ out_unlock;

	अगर (!atomic_add_unless(&bat_priv->tp_num, 1, BATADV_TP_MAX_NUM)) अणु
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Meter: too many ongoing sessions, aborting (RECV)\n");
		जाओ out_unlock;
	पूर्ण

	tp_vars = kदो_स्मृति(माप(*tp_vars), GFP_ATOMIC);
	अगर (!tp_vars)
		जाओ out_unlock;

	ether_addr_copy(tp_vars->other_end, icmp->orig);
	tp_vars->role = BATADV_TP_RECEIVER;
	स_नकल(tp_vars->session, icmp->session, माप(tp_vars->session));
	tp_vars->last_recv = BATADV_TP_FIRST_SEQ;
	tp_vars->bat_priv = bat_priv;
	kref_init(&tp_vars->refcount);

	spin_lock_init(&tp_vars->unacked_lock);
	INIT_LIST_HEAD(&tp_vars->unacked_list);

	kref_get(&tp_vars->refcount);
	hlist_add_head_rcu(&tp_vars->list, &bat_priv->tp_list);

	kref_get(&tp_vars->refcount);
	समयr_setup(&tp_vars->समयr, batadv_tp_receiver_shutकरोwn, 0);

	batadv_tp_reset_receiver_समयr(tp_vars);

out_unlock:
	spin_unlock_bh(&bat_priv->tp_list_lock);

	वापस tp_vars;
पूर्ण

/**
 * batadv_tp_recv_msg() - process a single data message
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the buffer containing the received packet
 *
 * Process a received TP MSG packet
 */
अटल व्योम batadv_tp_recv_msg(काष्ठा batadv_priv *bat_priv,
			       स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा batadv_icmp_tp_packet *icmp;
	काष्ठा batadv_tp_vars *tp_vars;
	माप_प्रकार packet_size;
	u32 seqno;

	icmp = (काष्ठा batadv_icmp_tp_packet *)skb->data;

	seqno = ntohl(icmp->seqno);
	/* check अगर this is the first seqno. This means that अगर the
	 * first packet is lost, the tp meter करोes not work anymore!
	 */
	अगर (seqno == BATADV_TP_FIRST_SEQ) अणु
		tp_vars = batadv_tp_init_recv(bat_priv, icmp);
		अगर (!tp_vars) अणु
			batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
				   "Meter: seqno != BATADV_TP_FIRST_SEQ cannot initiate connection\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		tp_vars = batadv_tp_list_find_session(bat_priv, icmp->orig,
						      icmp->session);
		अगर (!tp_vars) अणु
			batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
				   "Unexpected packet from %pM!\n",
				   icmp->orig);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (unlikely(tp_vars->role != BATADV_TP_RECEIVER)) अणु
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Meter: dropping packet: not expected (role=%u)\n",
			   tp_vars->role);
		जाओ out;
	पूर्ण

	tp_vars->last_recv_समय = jअगरfies;

	/* अगर the packet is a duplicate, it may be the हाल that an ACK has been
	 * lost. Resend the ACK
	 */
	अगर (batadv_seq_beक्रमe(seqno, tp_vars->last_recv))
		जाओ send_ack;

	/* अगर the packet is out of order enqueue it */
	अगर (ntohl(icmp->seqno) != tp_vars->last_recv) अणु
		/* निकास immediately (and करो not send any ACK) अगर the packet has
		 * not been enqueued correctly
		 */
		अगर (!batadv_tp_handle_out_of_order(tp_vars, skb))
			जाओ out;

		/* send a duplicate ACK */
		जाओ send_ack;
	पूर्ण

	/* अगर everything was fine count the ACKed bytes */
	packet_size = skb->len - माप(काष्ठा batadv_unicast_packet);
	tp_vars->last_recv += packet_size;

	/* check अगर this ordered message filled a gap.... */
	batadv_tp_ack_unordered(tp_vars);

send_ack:
	/* send the ACK. If the received packet was out of order, the ACK that
	 * is going to be sent is a duplicate (the sender will count them and
	 * possibly enter Fast Retransmit as soon as it has reached 3)
	 */
	batadv_tp_send_ack(bat_priv, icmp->orig, tp_vars->last_recv,
			   icmp->बारtamp, icmp->session, icmp->uid);
out:
	अगर (likely(tp_vars))
		batadv_tp_vars_put(tp_vars);
पूर्ण

/**
 * batadv_tp_meter_recv() - मुख्य TP Meter receiving function
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the buffer containing the received packet
 */
व्योम batadv_tp_meter_recv(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_icmp_tp_packet *icmp;

	icmp = (काष्ठा batadv_icmp_tp_packet *)skb->data;

	चयन (icmp->subtype) अणु
	हाल BATADV_TP_MSG:
		batadv_tp_recv_msg(bat_priv, skb);
		अवरोध;
	हाल BATADV_TP_ACK:
		batadv_tp_recv_ack(bat_priv, skb);
		अवरोध;
	शेष:
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Received unknown TP Metric packet type %u\n",
			   icmp->subtype);
	पूर्ण
	consume_skb(skb);
पूर्ण

/**
 * batadv_tp_meter_init() - initialize global tp_meter काष्ठाures
 */
व्योम __init batadv_tp_meter_init(व्योम)
अणु
	get_अक्रमom_bytes(batadv_tp_preअक्रमom, माप(batadv_tp_preअक्रमom));
पूर्ण
