<शैली गुरु>
/*
 * Copyright (c) 2006, 2017 Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/in.h>
#समावेश <net/tcp.h>

#समावेश "rds_single_path.h"
#समावेश "rds.h"
#समावेश "tcp.h"

व्योम rds_tcp_xmit_path_prepare(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;

	tcp_sock_set_cork(tc->t_sock->sk, true);
पूर्ण

व्योम rds_tcp_xmit_path_complete(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;

	tcp_sock_set_cork(tc->t_sock->sk, false);
पूर्ण

/* the core send_sem serializes this with other xmit and shutकरोwn */
अटल पूर्णांक rds_tcp_sendmsg(काष्ठा socket *sock, व्योम *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा kvec vec = अणु
		.iov_base = data,
		.iov_len = len,
	पूर्ण;
	काष्ठा msghdr msg = अणु
		.msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL,
	पूर्ण;

	वापस kernel_sendmsg(sock, &msg, &vec, 1, vec.iov_len);
पूर्ण

/* the core send_sem serializes this with other xmit and shutकरोwn */
पूर्णांक rds_tcp_xmit(काष्ठा rds_connection *conn, काष्ठा rds_message *rm,
		 अचिन्हित पूर्णांक hdr_off, अचिन्हित पूर्णांक sg, अचिन्हित पूर्णांक off)
अणु
	काष्ठा rds_conn_path *cp = rm->m_inc.i_conn_path;
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;
	पूर्णांक करोne = 0;
	पूर्णांक ret = 0;
	पूर्णांक more;

	अगर (hdr_off == 0) अणु
		/*
		 * m_ack_seq is set to the sequence number of the last byte of
		 * header and data.  see rds_tcp_is_acked().
		 */
		tc->t_last_sent_nxt = rds_tcp_ग_लिखो_seq(tc);
		rm->m_ack_seq = tc->t_last_sent_nxt +
				माप(काष्ठा rds_header) +
				be32_to_cpu(rm->m_inc.i_hdr.h_len) - 1;
		smp_mb__beक्रमe_atomic();
		set_bit(RDS_MSG_HAS_ACK_SEQ, &rm->m_flags);
		tc->t_last_expected_una = rm->m_ack_seq + 1;

		अगर (test_bit(RDS_MSG_RETRANSMITTED, &rm->m_flags))
			rm->m_inc.i_hdr.h_flags |= RDS_FLAG_RETRANSMITTED;

		rdsdebug("rm %p tcp nxt %u ack_seq %llu\n",
			 rm, rds_tcp_ग_लिखो_seq(tc),
			 (अचिन्हित दीर्घ दीर्घ)rm->m_ack_seq);
	पूर्ण

	अगर (hdr_off < माप(काष्ठा rds_header)) अणु
		/* see rds_tcp_ग_लिखो_space() */
		set_bit(SOCK_NOSPACE, &tc->t_sock->sk->sk_socket->flags);

		ret = rds_tcp_sendmsg(tc->t_sock,
				      (व्योम *)&rm->m_inc.i_hdr + hdr_off,
				      माप(rm->m_inc.i_hdr) - hdr_off);
		अगर (ret < 0)
			जाओ out;
		करोne += ret;
		अगर (hdr_off + करोne != माप(काष्ठा rds_header))
			जाओ out;
	पूर्ण

	more = rm->data.op_nents > 1 ? (MSG_MORE | MSG_SENDPAGE_NOTLAST) : 0;
	जबतक (sg < rm->data.op_nents) अणु
		पूर्णांक flags = MSG_DONTWAIT | MSG_NOSIGNAL | more;

		ret = tc->t_sock->ops->sendpage(tc->t_sock,
						sg_page(&rm->data.op_sg[sg]),
						rm->data.op_sg[sg].offset + off,
						rm->data.op_sg[sg].length - off,
						flags);
		rdsdebug("tcp sendpage %p:%u:%u ret %d\n", (व्योम *)sg_page(&rm->data.op_sg[sg]),
			 rm->data.op_sg[sg].offset + off, rm->data.op_sg[sg].length - off,
			 ret);
		अगर (ret <= 0)
			अवरोध;

		off += ret;
		करोne += ret;
		अगर (off == rm->data.op_sg[sg].length) अणु
			off = 0;
			sg++;
		पूर्ण
		अगर (sg == rm->data.op_nents - 1)
			more = 0;
	पूर्ण

out:
	अगर (ret <= 0) अणु
		/* ग_लिखो_space will hit after EAGAIN, all अन्यथा fatal */
		अगर (ret == -EAGAIN) अणु
			rds_tcp_stats_inc(s_tcp_sndbuf_full);
			ret = 0;
		पूर्ण अन्यथा अणु
			/* No need to disconnect/reconnect अगर path_drop
			 * has alपढ़ोy been triggered, because, e.g., of
			 * an incoming RST.
			 */
			अगर (rds_conn_path_up(cp)) अणु
				pr_warn("RDS/tcp: send to %pI6c on cp [%d]"
					"returned %d, "
					"disconnecting and reconnecting\n",
					&conn->c_faddr, cp->cp_index, ret);
				rds_conn_path_drop(cp, false);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (करोne == 0)
		करोne = ret;
	वापस करोne;
पूर्ण

/*
 * rm->m_ack_seq is set to the tcp sequence number that corresponds to the
 * last byte of the message, including the header.  This means that the
 * entire message has been received अगर rm->m_ack_seq is "before" the next
 * unacked byte of the TCP sequence space.  We have to करो very careful
 * wrapping 32bit comparisons here.
 */
अटल पूर्णांक rds_tcp_is_acked(काष्ठा rds_message *rm, uपूर्णांक64_t ack)
अणु
	अगर (!test_bit(RDS_MSG_HAS_ACK_SEQ, &rm->m_flags))
		वापस 0;
	वापस (__s32)((u32)rm->m_ack_seq - (u32)ack) < 0;
पूर्ण

व्योम rds_tcp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	व्योम (*ग_लिखो_space)(काष्ठा sock *sk);
	काष्ठा rds_conn_path *cp;
	काष्ठा rds_tcp_connection *tc;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	cp = sk->sk_user_data;
	अगर (!cp) अणु
		ग_लिखो_space = sk->sk_ग_लिखो_space;
		जाओ out;
	पूर्ण

	tc = cp->cp_transport_data;
	rdsdebug("write_space for tc %p\n", tc);
	ग_लिखो_space = tc->t_orig_ग_लिखो_space;
	rds_tcp_stats_inc(s_tcp_ग_लिखो_space_calls);

	rdsdebug("tcp una %u\n", rds_tcp_snd_una(tc));
	tc->t_last_seen_una = rds_tcp_snd_una(tc);
	rds_send_path_drop_acked(cp, rds_tcp_snd_una(tc), rds_tcp_is_acked);

	rcu_पढ़ो_lock();
	अगर ((refcount_पढ़ो(&sk->sk_wmem_alloc) << 1) <= sk->sk_sndbuf &&
	    !rds_destroy_pending(cp->cp_conn))
		queue_delayed_work(rds_wq, &cp->cp_send_w, 0);
	rcu_पढ़ो_unlock();

out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);

	/*
	 * ग_लिखो_space is only called when data leaves tcp's send queue अगर
	 * SOCK_NOSPACE is set.  We set SOCK_NOSPACE every समय we put
	 * data in tcp's send queue because we use ग_लिखो_space to parse the
	 * sequence numbers and notice that rds messages have been fully
	 * received.
	 *
	 * tcp's ग_लिखो_space clears SOCK_NOSPACE अगर the send queue has more
	 * than a certain amount of space. So we need to set it again *after*
	 * we call tcp's ग_लिखो_space or अन्यथा we might only get called on the
	 * first of a series of incoming tcp acks.
	 */
	ग_लिखो_space(sk);

	अगर (sk->sk_socket)
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
पूर्ण
