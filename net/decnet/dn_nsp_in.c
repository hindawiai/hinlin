<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Network Services Protocol (Input)
 *
 * Author:      Eduarकरो Marcelo Serrat <emserrat@geocities.com>
 *
 * Changes:
 *
 *    Steve Whitehouse:  Split पूर्णांकo dn_nsp_in.c and dn_nsp_out.c from
 *                       original dn_nsp.c.
 *    Steve Whitehouse:  Updated to work with my new routing architecture.
 *    Steve Whitehouse:  Add changes from Eduarकरो Serrat's patches.
 *    Steve Whitehouse:  Put all ack handling code in a common routine.
 *    Steve Whitehouse:  Put other common bits पूर्णांकo dn_nsp_rx()
 *    Steve Whitehouse:  More checks on skb->len to catch bogus packets
 *                       Fixed various race conditions and possible nasties.
 *    Steve Whitehouse:  Now handles वापसed conninit frames.
 *     David S. Miller:  New socket locking
 *    Steve Whitehouse:  Fixed lockup when socket filtering was enabled.
 *         Paul Koning:  Fix to push CC sockets पूर्णांकo RUN when acks are
 *                       received.
 *    Steve Whitehouse:
 *   Patrick Caulfield:  Checking conninits क्रम correctness & sending of error
 *                       responses.
 *    Steve Whitehouse:  Added backlog congestion level वापस codes.
 *   Patrick Caulfield:
 *    Steve Whitehouse:  Added flow control support (outbound)
 *    Steve Whitehouse:  Prepare क्रम nonlinear skbs
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
#समावेश <net/tcp_states.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/termios.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/netfilter_decnet.h>
#समावेश <net/neighbour.h>
#समावेश <net/dst.h>
#समावेश <net/dn.h>
#समावेश <net/dn_nsp.h>
#समावेश <net/dn_dev.h>
#समावेश <net/dn_route.h>

बाह्य पूर्णांक decnet_log_martians;

अटल व्योम dn_log_martian(काष्ठा sk_buff *skb, स्थिर अक्षर *msg)
अणु
	अगर (decnet_log_martians) अणु
		अक्षर *devname = skb->dev ? skb->dev->name : "???";
		काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
		net_info_ratelimited("DECnet: Martian packet (%s) dev=%s src=0x%04hx dst=0x%04hx srcport=0x%04hx dstport=0x%04hx\n",
				     msg, devname,
				     le16_to_cpu(cb->src),
				     le16_to_cpu(cb->dst),
				     le16_to_cpu(cb->src_port),
				     le16_to_cpu(cb->dst_port));
	पूर्ण
पूर्ण

/*
 * For this function we've flipped the cross-subchannel bit
 * अगर the message is an otherdata or linkservice message. Thus
 * we can use it to work out what to update.
 */
अटल व्योम dn_ack(काष्ठा sock *sk, काष्ठा sk_buff *skb, अचिन्हित लघु ack)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	अचिन्हित लघु type = ((ack >> 12) & 0x0003);
	पूर्णांक wakeup = 0;

	चयन (type) अणु
	हाल 0: /* ACK - Data */
		अगर (dn_after(ack, scp->ackrcv_dat)) अणु
			scp->ackrcv_dat = ack & 0x0fff;
			wakeup |= dn_nsp_check_xmit_queue(sk, skb,
							  &scp->data_xmit_queue,
							  ack);
		पूर्ण
		अवरोध;
	हाल 1: /* NAK - Data */
		अवरोध;
	हाल 2: /* ACK - OtherData */
		अगर (dn_after(ack, scp->ackrcv_oth)) अणु
			scp->ackrcv_oth = ack & 0x0fff;
			wakeup |= dn_nsp_check_xmit_queue(sk, skb,
							  &scp->other_xmit_queue,
							  ack);
		पूर्ण
		अवरोध;
	हाल 3: /* NAK - OtherData */
		अवरोध;
	पूर्ण

	अगर (wakeup && !sock_flag(sk, SOCK_DEAD))
		sk->sk_state_change(sk);
पूर्ण

/*
 * This function is a universal ack processor.
 */
अटल पूर्णांक dn_process_ack(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक oth)
अणु
	__le16 *ptr = (__le16 *)skb->data;
	पूर्णांक len = 0;
	अचिन्हित लघु ack;

	अगर (skb->len < 2)
		वापस len;

	अगर ((ack = le16_to_cpu(*ptr)) & 0x8000) अणु
		skb_pull(skb, 2);
		ptr++;
		len += 2;
		अगर ((ack & 0x4000) == 0) अणु
			अगर (oth)
				ack ^= 0x2000;
			dn_ack(sk, skb, ack);
		पूर्ण
	पूर्ण

	अगर (skb->len < 2)
		वापस len;

	अगर ((ack = le16_to_cpu(*ptr)) & 0x8000) अणु
		skb_pull(skb, 2);
		len += 2;
		अगर ((ack & 0x4000) == 0) अणु
			अगर (oth)
				ack ^= 0x2000;
			dn_ack(sk, skb, ack);
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण


/**
 * dn_check_idf - Check an image data field क्रमmat is correct.
 * @pptr: Poपूर्णांकer to poपूर्णांकer to image data
 * @len: Poपूर्णांकer to length of image data
 * @max: The maximum allowed length of the data in the image data field
 * @follow_on: Check that this many bytes exist beyond the end of the image data
 *
 * Returns: 0 अगर ok, -1 on error
 */
अटल अंतरभूत पूर्णांक dn_check_idf(अचिन्हित अक्षर **pptr, पूर्णांक *len, अचिन्हित अक्षर max, अचिन्हित अक्षर follow_on)
अणु
	अचिन्हित अक्षर *ptr = *pptr;
	अचिन्हित अक्षर flen = *ptr++;

	(*len)--;
	अगर (flen > max)
		वापस -1;
	अगर ((flen + follow_on) > *len)
		वापस -1;

	*len -= flen;
	*pptr = ptr + flen;
	वापस 0;
पूर्ण

/*
 * Table of reason codes to pass back to node which sent us a badly
 * क्रमmed message, plus text messages क्रम the log. A zero entry in
 * the reason field means "don't reply" otherwise a disc init is sent with
 * the specअगरied reason code.
 */
अटल काष्ठा अणु
	अचिन्हित लघु reason;
	स्थिर अक्षर *text;
पूर्ण ci_err_table[] = अणु
 अणु 0,             "CI: Truncated message" पूर्ण,
 अणु NSP_REASON_ID, "CI: Destination username error" पूर्ण,
 अणु NSP_REASON_ID, "CI: Destination username type" पूर्ण,
 अणु NSP_REASON_US, "CI: Source username error" पूर्ण,
 अणु 0,             "CI: Truncated at menuver" पूर्ण,
 अणु 0,             "CI: Truncated before access or user data" पूर्ण,
 अणु NSP_REASON_IO, "CI: Access data format error" पूर्ण,
 अणु NSP_REASON_IO, "CI: User data format error" पूर्ण
पूर्ण;

/*
 * This function uses a slightly dअगरferent lookup method
 * to find its sockets, since it searches on object name/number
 * rather than port numbers. Various tests are करोne to ensure that
 * the incoming data is in the correct क्रमmat beक्रमe it is queued to
 * a socket.
 */
अटल काष्ठा sock *dn_find_listener(काष्ठा sk_buff *skb, अचिन्हित लघु *reason)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	काष्ठा nsp_conn_init_msg *msg = (काष्ठा nsp_conn_init_msg *)skb->data;
	काष्ठा sockaddr_dn dstaddr;
	काष्ठा sockaddr_dn srcaddr;
	अचिन्हित अक्षर type = 0;
	पूर्णांक dstlen;
	पूर्णांक srclen;
	अचिन्हित अक्षर *ptr;
	पूर्णांक len;
	पूर्णांक err = 0;
	अचिन्हित अक्षर menuver;

	स_रखो(&dstaddr, 0, माप(काष्ठा sockaddr_dn));
	स_रखो(&srcaddr, 0, माप(काष्ठा sockaddr_dn));

	/*
	 * 1. Decode & हटाओ message header
	 */
	cb->src_port = msg->srcaddr;
	cb->dst_port = msg->dstaddr;
	cb->services = msg->services;
	cb->info     = msg->info;
	cb->segsize  = le16_to_cpu(msg->segsize);

	अगर (!pskb_may_pull(skb, माप(*msg)))
		जाओ err_out;

	skb_pull(skb, माप(*msg));

	len = skb->len;
	ptr = skb->data;

	/*
	 * 2. Check destination end username क्रमmat
	 */
	dstlen = dn_username2sockaddr(ptr, len, &dstaddr, &type);
	err++;
	अगर (dstlen < 0)
		जाओ err_out;

	err++;
	अगर (type > 1)
		जाओ err_out;

	len -= dstlen;
	ptr += dstlen;

	/*
	 * 3. Check source end username क्रमmat
	 */
	srclen = dn_username2sockaddr(ptr, len, &srcaddr, &type);
	err++;
	अगर (srclen < 0)
		जाओ err_out;

	len -= srclen;
	ptr += srclen;
	err++;
	अगर (len < 1)
		जाओ err_out;

	menuver = *ptr;
	ptr++;
	len--;

	/*
	 * 4. Check that optional data actually exists अगर menuver says it करोes
	 */
	err++;
	अगर ((menuver & (DN_MENUVER_ACC | DN_MENUVER_USR)) && (len < 1))
		जाओ err_out;

	/*
	 * 5. Check optional access data क्रमmat
	 */
	err++;
	अगर (menuver & DN_MENUVER_ACC) अणु
		अगर (dn_check_idf(&ptr, &len, 39, 1))
			जाओ err_out;
		अगर (dn_check_idf(&ptr, &len, 39, 1))
			जाओ err_out;
		अगर (dn_check_idf(&ptr, &len, 39, (menuver & DN_MENUVER_USR) ? 1 : 0))
			जाओ err_out;
	पूर्ण

	/*
	 * 6. Check optional user data क्रमmat
	 */
	err++;
	अगर (menuver & DN_MENUVER_USR) अणु
		अगर (dn_check_idf(&ptr, &len, 16, 0))
			जाओ err_out;
	पूर्ण

	/*
	 * 7. Look up socket based on destination end username
	 */
	वापस dn_sklist_find_listener(&dstaddr);
err_out:
	dn_log_martian(skb, ci_err_table[err].text);
	*reason = ci_err_table[err].reason;
	वापस शून्य;
पूर्ण


अटल व्योम dn_nsp_conn_init(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (sk_acceptq_is_full(sk)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	sk_acceptq_added(sk);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_state_change(sk);
पूर्ण

अटल व्योम dn_nsp_conn_conf(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	काष्ठा dn_scp *scp = DN_SK(sk);
	अचिन्हित अक्षर *ptr;

	अगर (skb->len < 4)
		जाओ out;

	ptr = skb->data;
	cb->services = *ptr++;
	cb->info = *ptr++;
	cb->segsize = le16_to_cpu(*(__le16 *)ptr);

	अगर ((scp->state == DN_CI) || (scp->state == DN_CD)) अणु
		scp->persist = 0;
		scp->addrrem = cb->src_port;
		sk->sk_state = TCP_ESTABLISHED;
		scp->state = DN_RUN;
		scp->services_rem = cb->services;
		scp->info_rem = cb->info;
		scp->segsize_rem = cb->segsize;

		अगर ((scp->services_rem & NSP_FC_MASK) == NSP_FC_NONE)
			scp->max_winकरोw = decnet_no_fc_max_cwnd;

		अगर (skb->len > 0) अणु
			u16 dlen = *skb->data;
			अगर ((dlen <= 16) && (dlen <= skb->len)) अणु
				scp->conndata_in.opt_optl = cpu_to_le16(dlen);
				skb_copy_from_linear_data_offset(skb, 1,
					      scp->conndata_in.opt_data, dlen);
			पूर्ण
		पूर्ण
		dn_nsp_send_link(sk, DN_NOCHANGE, 0);
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
	पूर्ण

out:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम dn_nsp_conn_ack(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	अगर (scp->state == DN_CI) अणु
		scp->state = DN_CD;
		scp->persist = 0;
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

अटल व्योम dn_nsp_disc_init(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	अचिन्हित लघु reason;

	अगर (skb->len < 2)
		जाओ out;

	reason = le16_to_cpu(*(__le16 *)skb->data);
	skb_pull(skb, 2);

	scp->discdata_in.opt_status = cpu_to_le16(reason);
	scp->discdata_in.opt_optl   = 0;
	स_रखो(scp->discdata_in.opt_data, 0, 16);

	अगर (skb->len > 0) अणु
		u16 dlen = *skb->data;
		अगर ((dlen <= 16) && (dlen <= skb->len)) अणु
			scp->discdata_in.opt_optl = cpu_to_le16(dlen);
			skb_copy_from_linear_data_offset(skb, 1, scp->discdata_in.opt_data, dlen);
		पूर्ण
	पूर्ण

	scp->addrrem = cb->src_port;
	sk->sk_state = TCP_CLOSE;

	चयन (scp->state) अणु
	हाल DN_CI:
	हाल DN_CD:
		scp->state = DN_RJ;
		sk->sk_err = ECONNREFUSED;
		अवरोध;
	हाल DN_RUN:
		sk->sk_shutकरोwn |= SHUTDOWN_MASK;
		scp->state = DN_DN;
		अवरोध;
	हाल DN_DI:
		scp->state = DN_DIC;
		अवरोध;
	पूर्ण

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		अगर (sk->sk_socket->state != SS_UNCONNECTED)
			sk->sk_socket->state = SS_DISCONNECTING;
		sk->sk_state_change(sk);
	पूर्ण

	/*
	 * It appears that its possible क्रम remote machines to send disc
	 * init messages with no port identअगरier अगर we are in the CI and
	 * possibly also the CD state. Obviously we shouldn't reply with
	 * a message अगर we करोn't know what the end poपूर्णांक is.
	 */
	अगर (scp->addrrem) अणु
		dn_nsp_send_disc(sk, NSP_DISCCONF, NSP_REASON_DC, GFP_ATOMIC);
	पूर्ण
	scp->persist_fxn = dn_destroy_समयr;
	scp->persist = dn_nsp_persist(sk);

out:
	kमुक्त_skb(skb);
पूर्ण

/*
 * disc_conf messages are also called no_resources or no_link
 * messages depending upon the "reason" field.
 */
अटल व्योम dn_nsp_disc_conf(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	अचिन्हित लघु reason;

	अगर (skb->len != 2)
		जाओ out;

	reason = le16_to_cpu(*(__le16 *)skb->data);

	sk->sk_state = TCP_CLOSE;

	चयन (scp->state) अणु
	हाल DN_CI:
		scp->state = DN_NR;
		अवरोध;
	हाल DN_DR:
		अगर (reason == NSP_REASON_DC)
			scp->state = DN_DRC;
		अगर (reason == NSP_REASON_NL)
			scp->state = DN_CN;
		अवरोध;
	हाल DN_DI:
		scp->state = DN_DIC;
		अवरोध;
	हाल DN_RUN:
		sk->sk_shutकरोwn |= SHUTDOWN_MASK;
		fallthrough;
	हाल DN_CC:
		scp->state = DN_CN;
	पूर्ण

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		अगर (sk->sk_socket->state != SS_UNCONNECTED)
			sk->sk_socket->state = SS_DISCONNECTING;
		sk->sk_state_change(sk);
	पूर्ण

	scp->persist_fxn = dn_destroy_समयr;
	scp->persist = dn_nsp_persist(sk);

out:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम dn_nsp_linkservice(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	अचिन्हित लघु segnum;
	अचिन्हित अक्षर lsflags;
	चिन्हित अक्षर fcval;
	पूर्णांक wake_up = 0;
	अक्षर *ptr = skb->data;
	अचिन्हित अक्षर fctype = scp->services_rem & NSP_FC_MASK;

	अगर (skb->len != 4)
		जाओ out;

	segnum = le16_to_cpu(*(__le16 *)ptr);
	ptr += 2;
	lsflags = *(अचिन्हित अक्षर *)ptr++;
	fcval = *ptr;

	/*
	 * Here we ignore erroneous packets which should really
	 * should cause a connection पात. It is not critical
	 * क्रम now though.
	 */
	अगर (lsflags & 0xf8)
		जाओ out;

	अगर (seq_next(scp->numoth_rcv, segnum)) अणु
		seq_add(&scp->numoth_rcv, 1);
		चयन(lsflags & 0x04) अणु /* FCVAL INT */
		हाल 0x00: /* Normal Request */
			चयन(lsflags & 0x03) अणु /* FCVAL MOD */
			हाल 0x00: /* Request count */
				अगर (fcval < 0) अणु
					अचिन्हित अक्षर p_fcval = -fcval;
					अगर ((scp->flowrem_dat > p_fcval) &&
					    (fctype == NSP_FC_SCMC)) अणु
						scp->flowrem_dat -= p_fcval;
					पूर्ण
				पूर्ण अन्यथा अगर (fcval > 0) अणु
					scp->flowrem_dat += fcval;
					wake_up = 1;
				पूर्ण
				अवरोध;
			हाल 0x01: /* Stop outgoing data */
				scp->flowrem_sw = DN_DONTSEND;
				अवरोध;
			हाल 0x02: /* Ok to start again */
				scp->flowrem_sw = DN_SEND;
				dn_nsp_output(sk);
				wake_up = 1;
			पूर्ण
			अवरोध;
		हाल 0x04: /* Interrupt Request */
			अगर (fcval > 0) अणु
				scp->flowrem_oth += fcval;
				wake_up = 1;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (wake_up && !sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
	पूर्ण

	dn_nsp_send_oth_ack(sk);

out:
	kमुक्त_skb(skb);
पूर्ण

/*
 * Copy of sock_queue_rcv_skb (from sock.h) without
 * bh_lock_sock() (its alपढ़ोy held when this is called) which
 * also allows data and other data to be queued to a socket.
 */
अटल __अंतरभूत__ पूर्णांक dn_queue_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक sig, काष्ठा sk_buff_head *queue)
अणु
	पूर्णांक err;

	/* Cast skb->rcvbuf to अचिन्हित... It's poपूर्णांकless, but reduces
	   number of warnings when compiling with -W --ANK
	 */
	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) + skb->truesize >=
	    (अचिन्हित पूर्णांक)sk->sk_rcvbuf) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = sk_filter(sk, skb);
	अगर (err)
		जाओ out;

	skb_set_owner_r(skb, sk);
	skb_queue_tail(queue, skb);

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_पढ़ोy(sk);
out:
	वापस err;
पूर्ण

अटल व्योम dn_nsp_otherdata(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	अचिन्हित लघु segnum;
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	पूर्णांक queued = 0;

	अगर (skb->len < 2)
		जाओ out;

	cb->segnum = segnum = le16_to_cpu(*(__le16 *)skb->data);
	skb_pull(skb, 2);

	अगर (seq_next(scp->numoth_rcv, segnum)) अणु

		अगर (dn_queue_skb(sk, skb, SIGURG, &scp->other_receive_queue) == 0) अणु
			seq_add(&scp->numoth_rcv, 1);
			scp->other_report = 0;
			queued = 1;
		पूर्ण
	पूर्ण

	dn_nsp_send_oth_ack(sk);
out:
	अगर (!queued)
		kमुक्त_skb(skb);
पूर्ण

अटल व्योम dn_nsp_data(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक queued = 0;
	अचिन्हित लघु segnum;
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	काष्ठा dn_scp *scp = DN_SK(sk);

	अगर (skb->len < 2)
		जाओ out;

	cb->segnum = segnum = le16_to_cpu(*(__le16 *)skb->data);
	skb_pull(skb, 2);

	अगर (seq_next(scp->numdat_rcv, segnum)) अणु
		अगर (dn_queue_skb(sk, skb, SIGIO, &sk->sk_receive_queue) == 0) अणु
			seq_add(&scp->numdat_rcv, 1);
			queued = 1;
		पूर्ण

		अगर ((scp->flowloc_sw == DN_SEND) && dn_congested(sk)) अणु
			scp->flowloc_sw = DN_DONTSEND;
			dn_nsp_send_link(sk, DN_DONTSEND, 0);
		पूर्ण
	पूर्ण

	dn_nsp_send_data_ack(sk);
out:
	अगर (!queued)
		kमुक्त_skb(skb);
पूर्ण

/*
 * If one of our conninit messages is वापसed, this function
 * deals with it. It माला_दो the socket पूर्णांकo the NO_COMMUNICATION
 * state.
 */
अटल व्योम dn_वापसed_conn_init(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	अगर (scp->state == DN_CI) अणु
		scp->state = DN_NC;
		sk->sk_state = TCP_CLOSE;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक dn_nsp_no_socket(काष्ठा sk_buff *skb, अचिन्हित लघु reason)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	पूर्णांक ret = NET_RX_DROP;

	/* Must not reply to वापसed packets */
	अगर (cb->rt_flags & DN_RT_F_RTS)
		जाओ out;

	अगर ((reason != NSP_REASON_OK) && ((cb->nsp_flags & 0x0c) == 0x08)) अणु
		चयन (cb->nsp_flags & 0x70) अणु
		हाल 0x10:
		हाल 0x60: /* (Retransmitted) Connect Init */
			dn_nsp_वापस_disc(skb, NSP_DISCINIT, reason);
			ret = NET_RX_SUCCESS;
			अवरोध;
		हाल 0x20: /* Connect Confirm */
			dn_nsp_वापस_disc(skb, NSP_DISCCONF, reason);
			ret = NET_RX_SUCCESS;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक dn_nsp_rx_packet(काष्ठा net *net, काष्ठा sock *sk2,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	काष्ठा sock *sk = शून्य;
	अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *)skb->data;
	अचिन्हित लघु reason = NSP_REASON_NL;

	अगर (!pskb_may_pull(skb, 2))
		जाओ मुक्त_out;

	skb_reset_transport_header(skb);
	cb->nsp_flags = *ptr++;

	अगर (decnet_debug_level & 2)
		prपूर्णांकk(KERN_DEBUG "dn_nsp_rx: Message type 0x%02x\n", (पूर्णांक)cb->nsp_flags);

	अगर (cb->nsp_flags & 0x83)
		जाओ मुक्त_out;

	/*
	 * Filter out conninits and useless packet types
	 */
	अगर ((cb->nsp_flags & 0x0c) == 0x08) अणु
		चयन (cb->nsp_flags & 0x70) अणु
		हाल 0x00: /* NOP */
		हाल 0x70: /* Reserved */
		हाल 0x50: /* Reserved, Phase II node init */
			जाओ मुक्त_out;
		हाल 0x10:
		हाल 0x60:
			अगर (unlikely(cb->rt_flags & DN_RT_F_RTS))
				जाओ मुक्त_out;
			sk = dn_find_listener(skb, &reason);
			जाओ got_it;
		पूर्ण
	पूर्ण

	अगर (!pskb_may_pull(skb, 3))
		जाओ मुक्त_out;

	/*
	 * Grab the destination address.
	 */
	cb->dst_port = *(__le16 *)ptr;
	cb->src_port = 0;
	ptr += 2;

	/*
	 * If not a connack, grab the source address too.
	 */
	अगर (pskb_may_pull(skb, 5)) अणु
		cb->src_port = *(__le16 *)ptr;
		ptr += 2;
		skb_pull(skb, 5);
	पूर्ण

	/*
	 * Returned packets...
	 * Swap src & dst and look up in the normal way.
	 */
	अगर (unlikely(cb->rt_flags & DN_RT_F_RTS)) अणु
		swap(cb->dst_port, cb->src_port);
		swap(cb->dst, cb->src);
	पूर्ण

	/*
	 * Find the socket to which this skb is destined.
	 */
	sk = dn_find_by_skb(skb);
got_it:
	अगर (sk != शून्य) अणु
		काष्ठा dn_scp *scp = DN_SK(sk);

		/* Reset backoff */
		scp->nsp_rxtshअगरt = 0;

		/*
		 * We linearize everything except data segments here.
		 */
		अगर (cb->nsp_flags & ~0x60) अणु
			अगर (unlikely(skb_linearize(skb)))
				जाओ मुक्त_out;
		पूर्ण

		वापस sk_receive_skb(sk, skb, 0);
	पूर्ण

	वापस dn_nsp_no_socket(skb, reason);

मुक्त_out:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

पूर्णांक dn_nsp_rx(काष्ठा sk_buff *skb)
अणु
	वापस NF_HOOK(NFPROTO_DECNET, NF_DN_LOCAL_IN,
		       &init_net, शून्य, skb, skb->dev, शून्य,
		       dn_nsp_rx_packet);
पूर्ण

/*
 * This is the मुख्य receive routine क्रम sockets. It is called
 * from the above when the socket is not busy, and also from
 * sock_release() when there is a backlog queued up.
 */
पूर्णांक dn_nsp_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);

	अगर (cb->rt_flags & DN_RT_F_RTS) अणु
		अगर (cb->nsp_flags == 0x18 || cb->nsp_flags == 0x68)
			dn_वापसed_conn_init(sk, skb);
		अन्यथा
			kमुक्त_skb(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

	/*
	 * Control packet.
	 */
	अगर ((cb->nsp_flags & 0x0c) == 0x08) अणु
		चयन (cb->nsp_flags & 0x70) अणु
		हाल 0x10:
		हाल 0x60:
			dn_nsp_conn_init(sk, skb);
			अवरोध;
		हाल 0x20:
			dn_nsp_conn_conf(sk, skb);
			अवरोध;
		हाल 0x30:
			dn_nsp_disc_init(sk, skb);
			अवरोध;
		हाल 0x40:
			dn_nsp_disc_conf(sk, skb);
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अगर (cb->nsp_flags == 0x24) अणु
		/*
		 * Special क्रम connacks, 'cos they don't have
		 * ack data or ack otherdata info.
		 */
		dn_nsp_conn_ack(sk, skb);
	पूर्ण अन्यथा अणु
		पूर्णांक other = 1;

		/* both data and ack frames can kick a CC socket पूर्णांकo RUN */
		अगर ((scp->state == DN_CC) && !sock_flag(sk, SOCK_DEAD)) अणु
			scp->state = DN_RUN;
			sk->sk_state = TCP_ESTABLISHED;
			sk->sk_state_change(sk);
		पूर्ण

		अगर ((cb->nsp_flags & 0x1c) == 0)
			other = 0;
		अगर (cb->nsp_flags == 0x04)
			other = 0;

		/*
		 * Read out ack data here, this applies equally
		 * to data, other data, link serivce and both
		 * ack data and ack otherdata.
		 */
		dn_process_ack(sk, skb, other);

		/*
		 * If we've some sort of data here then call a
		 * suitable routine क्रम dealing with it, otherwise
		 * the packet is an ack and can be discarded.
		 */
		अगर ((cb->nsp_flags & 0x0c) == 0) अणु

			अगर (scp->state != DN_RUN)
				जाओ मुक्त_out;

			चयन (cb->nsp_flags) अणु
			हाल 0x10: /* LS */
				dn_nsp_linkservice(sk, skb);
				अवरोध;
			हाल 0x30: /* OD */
				dn_nsp_otherdata(sk, skb);
				अवरोध;
			शेष:
				dn_nsp_data(sk, skb);
			पूर्ण

		पूर्ण अन्यथा अणु /* Ack, chuck it out here */
मुक्त_out:
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	वापस NET_RX_SUCCESS;
पूर्ण
