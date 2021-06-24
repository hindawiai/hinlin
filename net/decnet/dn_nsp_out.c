<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Network Services Protocol (Output)
 *
 * Author:      Eduarकरो Marcelo Serrat <emserrat@geocities.com>
 *
 * Changes:
 *
 *    Steve Whitehouse:  Split पूर्णांकo dn_nsp_in.c and dn_nsp_out.c from
 *                       original dn_nsp.c.
 *    Steve Whitehouse:  Updated to work with my new routing architecture.
 *    Steve Whitehouse:  Added changes from Eduarकरो Serrat's patches.
 *    Steve Whitehouse:  Now conninits have the "return" bit set.
 *    Steve Whitehouse:  Fixes to check alloc'd skbs are non शून्य!
 *                       Moved output state machine पूर्णांकo one function
 *    Steve Whitehouse:  New output state machine
 *         Paul Koning:  Connect Confirm message fix.
 *      Eduarकरो Serrat:  Fix to stop dn_nsp_करो_disc() sending malक्रमmed packets.
 *    Steve Whitehouse:  dn_nsp_output() and मित्रs needed a spring clean
 *    Steve Whitehouse:  Moved dn_nsp_send() in here from route.h
 */

/******************************************************************************
    (c) 1995-1998 E.M. Serrat		emserrat@geocities.com

*******************************************************************************/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inet.h>
#समावेश <linux/route.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/termios.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/अगर_packet.h>
#समावेश <net/neighbour.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/dn.h>
#समावेश <net/dn_nsp.h>
#समावेश <net/dn_dev.h>
#समावेश <net/dn_route.h>


अटल पूर्णांक nsp_backoff[NSP_MAXRXTSHIFT + 1] = अणु 1, 2, 4, 8, 16, 32, 64, 64, 64, 64, 64, 64, 64 पूर्ण;

अटल व्योम dn_nsp_send(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा dst_entry *dst;
	काष्ठा flowidn fld;

	skb_reset_transport_header(skb);
	scp->stamp = jअगरfies;

	dst = sk_dst_check(sk, 0);
	अगर (dst) अणु
try_again:
		skb_dst_set(skb, dst);
		dst_output(&init_net, skb->sk, skb);
		वापस;
	पूर्ण

	स_रखो(&fld, 0, माप(fld));
	fld.flowidn_oअगर = sk->sk_bound_dev_अगर;
	fld.saddr = dn_saddr2dn(&scp->addr);
	fld.daddr = dn_saddr2dn(&scp->peer);
	dn_sk_ports_copy(&fld, scp);
	fld.flowidn_proto = DNPROTO_NSP;
	अगर (dn_route_output_sock(&sk->sk_dst_cache, &fld, sk, 0) == 0) अणु
		dst = sk_dst_get(sk);
		sk->sk_route_caps = dst->dev->features;
		जाओ try_again;
	पूर्ण

	sk->sk_err = EHOSTUNREACH;
	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_state_change(sk);
पूर्ण


/*
 * If sk == शून्य, then we assume that we are supposed to be making
 * a routing layer skb. If sk != शून्य, then we are supposed to be
 * creating an skb क्रम the NSP layer.
 *
 * The eventual aim is क्रम each socket to have a cached header size
 * क्रम its outgoing packets, and to set hdr from this when sk != शून्य.
 */
काष्ठा sk_buff *dn_alloc_skb(काष्ठा sock *sk, पूर्णांक size, gfp_t pri)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक hdr = 64;

	अगर ((skb = alloc_skb(size + hdr, pri)) == शून्य)
		वापस शून्य;

	skb->protocol = htons(ETH_P_DNA_RT);
	skb->pkt_type = PACKET_OUTGOING;

	अगर (sk)
		skb_set_owner_w(skb, sk);

	skb_reserve(skb, hdr);

	वापस skb;
पूर्ण

/*
 * Calculate persist समयr based upon the smoothed round
 * trip समय and the variance. Backoff according to the
 * nsp_backoff[] array.
 */
अचिन्हित दीर्घ dn_nsp_persist(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	अचिन्हित दीर्घ t = ((scp->nsp_srtt >> 2) + scp->nsp_rttvar) >> 1;

	t *= nsp_backoff[scp->nsp_rxtshअगरt];

	अगर (t < HZ) t = HZ;
	अगर (t > (600*HZ)) t = (600*HZ);

	अगर (scp->nsp_rxtshअगरt < NSP_MAXRXTSHIFT)
		scp->nsp_rxtshअगरt++;

	/* prपूर्णांकk(KERN_DEBUG "rxtshift %lu, t=%lu\n", scp->nsp_rxtshअगरt, t); */

	वापस t;
पूर्ण

/*
 * This is called each समय we get an estimate क्रम the rtt
 * on the link.
 */
अटल व्योम dn_nsp_rtt(काष्ठा sock *sk, दीर्घ rtt)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	दीर्घ srtt = (दीर्घ)scp->nsp_srtt;
	दीर्घ rttvar = (दीर्घ)scp->nsp_rttvar;
	दीर्घ delta;

	/*
	 * If the jअगरfies घड़ी flips over in the middle of बारtamp
	 * gathering this value might turn out negative, so we make sure
	 * that is it always positive here.
	 */
	अगर (rtt < 0)
		rtt = -rtt;
	/*
	 * Add new rtt to smoothed average
	 */
	delta = ((rtt << 3) - srtt);
	srtt += (delta >> 3);
	अगर (srtt >= 1)
		scp->nsp_srtt = (अचिन्हित दीर्घ)srtt;
	अन्यथा
		scp->nsp_srtt = 1;

	/*
	 * Add new rtt varience to smoothed varience
	 */
	delta >>= 1;
	rttvar += ((((delta>0)?(delta):(-delta)) - rttvar) >> 2);
	अगर (rttvar >= 1)
		scp->nsp_rttvar = (अचिन्हित दीर्घ)rttvar;
	अन्यथा
		scp->nsp_rttvar = 1;

	/* prपूर्णांकk(KERN_DEBUG "srtt=%lu rttvar=%lu\n", scp->nsp_srtt, scp->nsp_rttvar); */
पूर्ण

/**
 * dn_nsp_clone_and_send - Send a data packet by cloning it
 * @skb: The packet to clone and transmit
 * @gfp: memory allocation flag
 *
 * Clone a queued data or other data packet and transmit it.
 *
 * Returns: The number of बार the packet has been sent previously
 */
अटल अंतरभूत अचिन्हित पूर्णांक dn_nsp_clone_and_send(काष्ठा sk_buff *skb,
					     gfp_t gfp)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	काष्ठा sk_buff *skb2;
	पूर्णांक ret = 0;

	अगर ((skb2 = skb_clone(skb, gfp)) != शून्य) अणु
		ret = cb->xmit_count;
		cb->xmit_count++;
		cb->stamp = jअगरfies;
		skb2->sk = skb->sk;
		dn_nsp_send(skb2);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dn_nsp_output - Try and send something from socket queues
 * @sk: The socket whose queues are to be investigated
 *
 * Try and send the packet on the end of the data and other data queues.
 * Other data माला_लो priority over data, and अगर we retransmit a packet we
 * reduce the winकरोw by भागiding it in two.
 *
 */
व्योम dn_nsp_output(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक reduce_win = 0;

	/*
	 * First we check क्रम otherdata/linkservice messages
	 */
	अगर ((skb = skb_peek(&scp->other_xmit_queue)) != शून्य)
		reduce_win = dn_nsp_clone_and_send(skb, GFP_ATOMIC);

	/*
	 * If we may not send any data, we करोn't.
	 * If we are still trying to get some other data करोwn the
	 * channel, we करोn't try and send any data.
	 */
	अगर (reduce_win || (scp->flowrem_sw != DN_SEND))
		जाओ recalc_winकरोw;

	अगर ((skb = skb_peek(&scp->data_xmit_queue)) != शून्य)
		reduce_win = dn_nsp_clone_and_send(skb, GFP_ATOMIC);

	/*
	 * If we've sent any frame more than once, we cut the
	 * send winकरोw size in half. There is always a minimum
	 * winकरोw size of one available.
	 */
recalc_winकरोw:
	अगर (reduce_win) अणु
		scp->snd_winकरोw >>= 1;
		अगर (scp->snd_winकरोw < NSP_MIN_WINDOW)
			scp->snd_winकरोw = NSP_MIN_WINDOW;
	पूर्ण
पूर्ण

पूर्णांक dn_nsp_xmit_समयout(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	dn_nsp_output(sk);

	अगर (!skb_queue_empty(&scp->data_xmit_queue) ||
	    !skb_queue_empty(&scp->other_xmit_queue))
		scp->persist = dn_nsp_persist(sk);

	वापस 0;
पूर्ण

अटल अंतरभूत __le16 *dn_mk_common_header(काष्ठा dn_scp *scp, काष्ठा sk_buff *skb, अचिन्हित अक्षर msgflag, पूर्णांक len)
अणु
	अचिन्हित अक्षर *ptr = skb_push(skb, len);

	BUG_ON(len < 5);

	*ptr++ = msgflag;
	*((__le16 *)ptr) = scp->addrrem;
	ptr += 2;
	*((__le16 *)ptr) = scp->addrloc;
	ptr += 2;
	वापस (__le16 __क्रमce *)ptr;
पूर्ण

अटल __le16 *dn_mk_ack_header(काष्ठा sock *sk, काष्ठा sk_buff *skb, अचिन्हित अक्षर msgflag, पूर्णांक hlen, पूर्णांक other)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	अचिन्हित लघु acknum = scp->numdat_rcv & 0x0FFF;
	अचिन्हित लघु ackcrs = scp->numoth_rcv & 0x0FFF;
	__le16 *ptr;

	BUG_ON(hlen < 9);

	scp->ackxmt_dat = acknum;
	scp->ackxmt_oth = ackcrs;
	acknum |= 0x8000;
	ackcrs |= 0x8000;

	/* If this is an "other data/ack" message, swap acknum and ackcrs */
	अगर (other)
		swap(acknum, ackcrs);

	/* Set "cross subchannel" bit in ackcrs */
	ackcrs |= 0x2000;

	ptr = dn_mk_common_header(scp, skb, msgflag, hlen);

	*ptr++ = cpu_to_le16(acknum);
	*ptr++ = cpu_to_le16(ackcrs);

	वापस ptr;
पूर्ण

अटल __le16 *dn_nsp_mk_data_header(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक oth)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	__le16 *ptr = dn_mk_ack_header(sk, skb, cb->nsp_flags, 11, oth);

	अगर (unlikely(oth)) अणु
		cb->segnum = scp->numoth;
		seq_add(&scp->numoth, 1);
	पूर्ण अन्यथा अणु
		cb->segnum = scp->numdat;
		seq_add(&scp->numdat, 1);
	पूर्ण
	*(ptr++) = cpu_to_le16(cb->segnum);

	वापस ptr;
पूर्ण

व्योम dn_nsp_queue_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			gfp_t gfp, पूर्णांक oth)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	अचिन्हित दीर्घ t = ((scp->nsp_srtt >> 2) + scp->nsp_rttvar) >> 1;

	cb->xmit_count = 0;
	dn_nsp_mk_data_header(sk, skb, oth);

	/*
	 * Slow start: If we have been idle क्रम more than
	 * one RTT, then reset winकरोw to min size.
	 */
	अगर ((jअगरfies - scp->stamp) > t)
		scp->snd_winकरोw = NSP_MIN_WINDOW;

	अगर (oth)
		skb_queue_tail(&scp->other_xmit_queue, skb);
	अन्यथा
		skb_queue_tail(&scp->data_xmit_queue, skb);

	अगर (scp->flowrem_sw != DN_SEND)
		वापस;

	dn_nsp_clone_and_send(skb, gfp);
पूर्ण


पूर्णांक dn_nsp_check_xmit_queue(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा sk_buff_head *q, अचिन्हित लघु acknum)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा sk_buff *skb2, *n, *ack = शून्य;
	पूर्णांक wakeup = 0;
	पूर्णांक try_retrans = 0;
	अचिन्हित दीर्घ refसमय = cb->stamp;
	अचिन्हित दीर्घ pktसमय;
	अचिन्हित लघु xmit_count;
	अचिन्हित लघु segnum;

	skb_queue_walk_safe(q, skb2, n) अणु
		काष्ठा dn_skb_cb *cb2 = DN_SKB_CB(skb2);

		अगर (dn_beक्रमe_or_equal(cb2->segnum, acknum))
			ack = skb2;

		/* prपूर्णांकk(KERN_DEBUG "ack: %s %04x %04x\n", ack ? "ACK" : "SKIP", (पूर्णांक)cb2->segnum, (पूर्णांक)acknum); */

		अगर (ack == शून्य)
			जारी;

		/* prपूर्णांकk(KERN_DEBUG "check_xmit_queue: %04x, %d\n", acknum, cb2->xmit_count); */

		/* Does _last_ packet acked have xmit_count > 1 */
		try_retrans = 0;
		/* Remember to wake up the sending process */
		wakeup = 1;
		/* Keep various statistics */
		pktसमय = cb2->stamp;
		xmit_count = cb2->xmit_count;
		segnum = cb2->segnum;
		/* Remove and drop ack'ed packet */
		skb_unlink(ack, q);
		kमुक्त_skb(ack);
		ack = शून्य;

		/*
		 * We करोn't expect to see acknowledgements क्रम packets we
		 * haven't sent yet.
		 */
		WARN_ON(xmit_count == 0);

		/*
		 * If the packet has only been sent once, we can use it
		 * to calculate the RTT and also खोलो the winकरोw a little
		 * further.
		 */
		अगर (xmit_count == 1) अणु
			अगर (dn_equal(segnum, acknum))
				dn_nsp_rtt(sk, (दीर्घ)(pktसमय - refसमय));

			अगर (scp->snd_winकरोw < scp->max_winकरोw)
				scp->snd_winकरोw++;
		पूर्ण

		/*
		 * Packet has been sent more than once. If this is the last
		 * packet to be acknowledged then we want to send the next
		 * packet in the send queue again (assumes the remote host करोes
		 * go-back-N error control).
		 */
		अगर (xmit_count > 1)
			try_retrans = 1;
	पूर्ण

	अगर (try_retrans)
		dn_nsp_output(sk);

	वापस wakeup;
पूर्ण

व्योम dn_nsp_send_data_ack(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb = शून्य;

	अगर ((skb = dn_alloc_skb(sk, 9, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reserve(skb, 9);
	dn_mk_ack_header(sk, skb, 0x04, 9, 0);
	dn_nsp_send(skb);
पूर्ण

व्योम dn_nsp_send_oth_ack(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb = शून्य;

	अगर ((skb = dn_alloc_skb(sk, 9, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reserve(skb, 9);
	dn_mk_ack_header(sk, skb, 0x14, 9, 1);
	dn_nsp_send(skb);
पूर्ण


व्योम dn_send_conn_ack (काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nsp_conn_ack_msg *msg;

	अगर ((skb = dn_alloc_skb(sk, 3, sk->sk_allocation)) == शून्य)
		वापस;

	msg = skb_put(skb, 3);
	msg->msgflg = 0x24;
	msg->dstaddr = scp->addrrem;

	dn_nsp_send(skb);
पूर्ण

अटल पूर्णांक dn_nsp_retrans_conn_conf(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	अगर (scp->state == DN_CC)
		dn_send_conn_conf(sk, GFP_ATOMIC);

	वापस 0;
पूर्ण

व्योम dn_send_conn_conf(काष्ठा sock *sk, gfp_t gfp)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nsp_conn_init_msg *msg;
	__u8 len = (__u8)le16_to_cpu(scp->conndata_out.opt_optl);

	अगर ((skb = dn_alloc_skb(sk, 50 + len, gfp)) == शून्य)
		वापस;

	msg = skb_put(skb, माप(*msg));
	msg->msgflg = 0x28;
	msg->dstaddr = scp->addrrem;
	msg->srcaddr = scp->addrloc;
	msg->services = scp->services_loc;
	msg->info = scp->info_loc;
	msg->segsize = cpu_to_le16(scp->segsize_loc);

	skb_put_u8(skb, len);

	अगर (len > 0)
		skb_put_data(skb, scp->conndata_out.opt_data, len);


	dn_nsp_send(skb);

	scp->persist = dn_nsp_persist(sk);
	scp->persist_fxn = dn_nsp_retrans_conn_conf;
पूर्ण


अटल __अंतरभूत__ व्योम dn_nsp_करो_disc(काष्ठा sock *sk, अचिन्हित अक्षर msgflg,
			अचिन्हित लघु reason, gfp_t gfp,
			काष्ठा dst_entry *dst,
			पूर्णांक ddl, अचिन्हित अक्षर *dd, __le16 rem, __le16 loc)
अणु
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक size = 7 + ddl + ((msgflg == NSP_DISCINIT) ? 1 : 0);
	अचिन्हित अक्षर *msg;

	अगर ((dst == शून्य) || (rem == 0)) अणु
		net_dbg_ratelimited("DECnet: dn_nsp_do_disc: BUG! Please report this to SteveW@ACM.org rem=%u dst=%p\n",
				    le16_to_cpu(rem), dst);
		वापस;
	पूर्ण

	अगर ((skb = dn_alloc_skb(sk, size, gfp)) == शून्य)
		वापस;

	msg = skb_put(skb, size);
	*msg++ = msgflg;
	*(__le16 *)msg = rem;
	msg += 2;
	*(__le16 *)msg = loc;
	msg += 2;
	*(__le16 *)msg = cpu_to_le16(reason);
	msg += 2;
	अगर (msgflg == NSP_DISCINIT)
		*msg++ = ddl;

	अगर (ddl) अणु
		स_नकल(msg, dd, ddl);
	पूर्ण

	/*
	 * This करोesn't go via the dn_nsp_send() function since we need
	 * to be able to send disc packets out which have no socket
	 * associations.
	 */
	skb_dst_set(skb, dst_clone(dst));
	dst_output(&init_net, skb->sk, skb);
पूर्ण


व्योम dn_nsp_send_disc(काष्ठा sock *sk, अचिन्हित अक्षर msgflg,
			अचिन्हित लघु reason, gfp_t gfp)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	पूर्णांक ddl = 0;

	अगर (msgflg == NSP_DISCINIT)
		ddl = le16_to_cpu(scp->discdata_out.opt_optl);

	अगर (reason == 0)
		reason = le16_to_cpu(scp->discdata_out.opt_status);

	dn_nsp_करो_disc(sk, msgflg, reason, gfp, __sk_dst_get(sk), ddl,
		scp->discdata_out.opt_data, scp->addrrem, scp->addrloc);
पूर्ण


व्योम dn_nsp_वापस_disc(काष्ठा sk_buff *skb, अचिन्हित अक्षर msgflg,
			अचिन्हित लघु reason)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	पूर्णांक ddl = 0;
	gfp_t gfp = GFP_ATOMIC;

	dn_nsp_करो_disc(शून्य, msgflg, reason, gfp, skb_dst(skb), ddl,
			शून्य, cb->src_port, cb->dst_port);
पूर्ण


व्योम dn_nsp_send_link(काष्ठा sock *sk, अचिन्हित अक्षर lsflags, अक्षर fcval)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *ptr;
	gfp_t gfp = GFP_ATOMIC;

	अगर ((skb = dn_alloc_skb(sk, DN_MAX_NSP_DATA_HEADER + 2, gfp)) == शून्य)
		वापस;

	skb_reserve(skb, DN_MAX_NSP_DATA_HEADER);
	ptr = skb_put(skb, 2);
	DN_SKB_CB(skb)->nsp_flags = 0x10;
	*ptr++ = lsflags;
	*ptr = fcval;

	dn_nsp_queue_xmit(sk, skb, gfp, 1);

	scp->persist = dn_nsp_persist(sk);
	scp->persist_fxn = dn_nsp_xmit_समयout;
पूर्ण

अटल पूर्णांक dn_nsp_retrans_conninit(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	अगर (scp->state == DN_CI)
		dn_nsp_send_conninit(sk, NSP_RCI);

	वापस 0;
पूर्ण

व्योम dn_nsp_send_conninit(काष्ठा sock *sk, अचिन्हित अक्षर msgflg)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा nsp_conn_init_msg *msg;
	अचिन्हित अक्षर aux;
	अचिन्हित अक्षर menuver;
	काष्ठा dn_skb_cb *cb;
	अचिन्हित अक्षर type = 1;
	gfp_t allocation = (msgflg == NSP_CI) ? sk->sk_allocation : GFP_ATOMIC;
	काष्ठा sk_buff *skb = dn_alloc_skb(sk, 200, allocation);

	अगर (!skb)
		वापस;

	cb  = DN_SKB_CB(skb);
	msg = skb_put(skb, माप(*msg));

	msg->msgflg	= msgflg;
	msg->dstaddr	= 0x0000;		/* Remote Node will assign it*/

	msg->srcaddr	= scp->addrloc;
	msg->services	= scp->services_loc;	/* Requested flow control    */
	msg->info	= scp->info_loc;	/* Version Number            */
	msg->segsize	= cpu_to_le16(scp->segsize_loc);	/* Max segment size  */

	अगर (scp->peer.sdn_objnum)
		type = 0;

	skb_put(skb, dn_sockaddr2username(&scp->peer,
					  skb_tail_poपूर्णांकer(skb), type));
	skb_put(skb, dn_sockaddr2username(&scp->addr,
					  skb_tail_poपूर्णांकer(skb), 2));

	menuver = DN_MENUVER_ACC | DN_MENUVER_USR;
	अगर (scp->peer.sdn_flags & SDF_PROXY)
		menuver |= DN_MENUVER_PRX;
	अगर (scp->peer.sdn_flags & SDF_UICPROXY)
		menuver |= DN_MENUVER_UIC;

	skb_put_u8(skb, menuver);	/* Menu Version		*/

	aux = scp->accessdata.acc_userl;
	skb_put_u8(skb, aux);
	अगर (aux > 0)
		skb_put_data(skb, scp->accessdata.acc_user, aux);

	aux = scp->accessdata.acc_passl;
	skb_put_u8(skb, aux);
	अगर (aux > 0)
		skb_put_data(skb, scp->accessdata.acc_pass, aux);

	aux = scp->accessdata.acc_accl;
	skb_put_u8(skb, aux);
	अगर (aux > 0)
		skb_put_data(skb, scp->accessdata.acc_acc, aux);

	aux = (__u8)le16_to_cpu(scp->conndata_out.opt_optl);
	skb_put_u8(skb, aux);
	अगर (aux > 0)
		skb_put_data(skb, scp->conndata_out.opt_data, aux);

	scp->persist = dn_nsp_persist(sk);
	scp->persist_fxn = dn_nsp_retrans_conninit;

	cb->rt_flags = DN_RT_F_RQR;

	dn_nsp_send(skb);
पूर्ण
