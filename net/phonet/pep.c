<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File: pep.c
 *
 * Phonet pipe protocol end poपूर्णांक socket
 *
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Author: Rथऊmi Denis-Courmont
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <यंत्र/ioctls.h>

#समावेश <linux/phonet.h>
#समावेश <linux/module.h>
#समावेश <net/phonet/phonet.h>
#समावेश <net/phonet/pep.h>
#समावेश <net/phonet/gprs.h>

/* sk_state values:
 * TCP_CLOSE		sock not in use yet
 * TCP_CLOSE_WAIT	disconnected pipe
 * TCP_LISTEN		listening pipe endpoपूर्णांक
 * TCP_SYN_RECV		connected pipe in disabled state
 * TCP_ESTABLISHED	connected pipe in enabled state
 *
 * pep_sock locking:
 *  - sk_state, hlist: sock lock needed
 *  - listener: पढ़ो only
 *  - pipe_handle: पढ़ो only
 */

#घोषणा CREDITS_MAX	10
#घोषणा CREDITS_THR	7

#घोषणा pep_sb_size(s) (((s) + 5) & ~3) /* 2-bytes head, 32-bits aligned */

/* Get the next TLV sub-block. */
अटल अचिन्हित अक्षर *pep_get_sb(काष्ठा sk_buff *skb, u8 *ptype, u8 *plen,
					व्योम *buf)
अणु
	व्योम *data = शून्य;
	काष्ठा अणु
		u8 sb_type;
		u8 sb_len;
	पूर्ण *ph, h;
	पूर्णांक buflen = *plen;

	ph = skb_header_poपूर्णांकer(skb, 0, 2, &h);
	अगर (ph == शून्य || ph->sb_len < 2 || !pskb_may_pull(skb, ph->sb_len))
		वापस शून्य;
	ph->sb_len -= 2;
	*ptype = ph->sb_type;
	*plen = ph->sb_len;

	अगर (buflen > ph->sb_len)
		buflen = ph->sb_len;
	data = skb_header_poपूर्णांकer(skb, 2, buflen, buf);
	__skb_pull(skb, 2 + ph->sb_len);
	वापस data;
पूर्ण

अटल काष्ठा sk_buff *pep_alloc_skb(काष्ठा sock *sk, स्थिर व्योम *payload,
					पूर्णांक len, gfp_t priority)
अणु
	काष्ठा sk_buff *skb = alloc_skb(MAX_PNPIPE_HEADER + len, priority);
	अगर (!skb)
		वापस शून्य;
	skb_set_owner_w(skb, sk);

	skb_reserve(skb, MAX_PNPIPE_HEADER);
	__skb_put(skb, len);
	skb_copy_to_linear_data(skb, payload, len);
	__skb_push(skb, माप(काष्ठा pnpipehdr));
	skb_reset_transport_header(skb);
	वापस skb;
पूर्ण

अटल पूर्णांक pep_reply(काष्ठा sock *sk, काष्ठा sk_buff *oskb, u8 code,
			स्थिर व्योम *data, पूर्णांक len, gfp_t priority)
अणु
	स्थिर काष्ठा pnpipehdr *oph = pnp_hdr(oskb);
	काष्ठा pnpipehdr *ph;
	काष्ठा sk_buff *skb;
	काष्ठा sockaddr_pn peer;

	skb = pep_alloc_skb(sk, data, len, priority);
	अगर (!skb)
		वापस -ENOMEM;

	ph = pnp_hdr(skb);
	ph->utid = oph->utid;
	ph->message_id = oph->message_id + 1; /* REQ -> RESP */
	ph->pipe_handle = oph->pipe_handle;
	ph->error_code = code;

	pn_skb_get_src_sockaddr(oskb, &peer);
	वापस pn_skb_send(sk, skb, &peer);
पूर्ण

अटल पूर्णांक pep_indicate(काष्ठा sock *sk, u8 id, u8 code,
			स्थिर व्योम *data, पूर्णांक len, gfp_t priority)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा pnpipehdr *ph;
	काष्ठा sk_buff *skb;

	skb = pep_alloc_skb(sk, data, len, priority);
	अगर (!skb)
		वापस -ENOMEM;

	ph = pnp_hdr(skb);
	ph->utid = 0;
	ph->message_id = id;
	ph->pipe_handle = pn->pipe_handle;
	ph->error_code = code;
	वापस pn_skb_send(sk, skb, शून्य);
पूर्ण

#घोषणा PAD 0x00

अटल पूर्णांक pipe_handler_request(काष्ठा sock *sk, u8 id, u8 code,
				स्थिर व्योम *data, पूर्णांक len)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा pnpipehdr *ph;
	काष्ठा sk_buff *skb;

	skb = pep_alloc_skb(sk, data, len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	ph = pnp_hdr(skb);
	ph->utid = id; /* whatever */
	ph->message_id = id;
	ph->pipe_handle = pn->pipe_handle;
	ph->error_code = code;
	वापस pn_skb_send(sk, skb, शून्य);
पूर्ण

अटल पूर्णांक pipe_handler_send_created_ind(काष्ठा sock *sk)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	u8 data[4] = अणु
		PN_PIPE_SB_NEGOTIATED_FC, pep_sb_size(2),
		pn->tx_fc, pn->rx_fc,
	पूर्ण;

	वापस pep_indicate(sk, PNS_PIPE_CREATED_IND, 1 /* sub-blocks */,
				data, 4, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक pep_accept_conn(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अटल स्थिर u8 data[20] = अणु
		PAD, PAD, PAD, 2 /* sub-blocks */,
		PN_PIPE_SB_REQUIRED_FC_TX, pep_sb_size(5), 3, PAD,
			PN_MULTI_CREDIT_FLOW_CONTROL,
			PN_ONE_CREDIT_FLOW_CONTROL,
			PN_LEGACY_FLOW_CONTROL,
			PAD,
		PN_PIPE_SB_PREFERRED_FC_RX, pep_sb_size(5), 3, PAD,
			PN_MULTI_CREDIT_FLOW_CONTROL,
			PN_ONE_CREDIT_FLOW_CONTROL,
			PN_LEGACY_FLOW_CONTROL,
			PAD,
	पूर्ण;

	might_sleep();
	वापस pep_reply(sk, skb, PN_PIPE_NO_ERROR, data, माप(data),
				GFP_KERNEL);
पूर्ण

अटल पूर्णांक pep_reject_conn(काष्ठा sock *sk, काष्ठा sk_buff *skb, u8 code,
				gfp_t priority)
अणु
	अटल स्थिर u8 data[4] = अणु PAD, PAD, PAD, 0 /* sub-blocks */ पूर्ण;
	WARN_ON(code == PN_PIPE_NO_ERROR);
	वापस pep_reply(sk, skb, code, data, माप(data), priority);
पूर्ण

/* Control requests are not sent by the pipe service and have a specअगरic
 * message क्रमmat. */
अटल पूर्णांक pep_ctrlreq_error(काष्ठा sock *sk, काष्ठा sk_buff *oskb, u8 code,
				gfp_t priority)
अणु
	स्थिर काष्ठा pnpipehdr *oph = pnp_hdr(oskb);
	काष्ठा sk_buff *skb;
	काष्ठा pnpipehdr *ph;
	काष्ठा sockaddr_pn dst;
	u8 data[4] = अणु
		oph->pep_type, /* PEP type */
		code, /* error code, at an unusual offset */
		PAD, PAD,
	पूर्ण;

	skb = pep_alloc_skb(sk, data, 4, priority);
	अगर (!skb)
		वापस -ENOMEM;

	ph = pnp_hdr(skb);
	ph->utid = oph->utid;
	ph->message_id = PNS_PEP_CTRL_RESP;
	ph->pipe_handle = oph->pipe_handle;
	ph->data0 = oph->data[0]; /* CTRL id */

	pn_skb_get_src_sockaddr(oskb, &dst);
	वापस pn_skb_send(sk, skb, &dst);
पूर्ण

अटल पूर्णांक pipe_snd_status(काष्ठा sock *sk, u8 type, u8 status, gfp_t priority)
अणु
	u8 data[4] = अणु type, PAD, PAD, status पूर्ण;

	वापस pep_indicate(sk, PNS_PEP_STATUS_IND, PN_PEP_TYPE_COMMON,
				data, 4, priority);
पूर्ण

/* Send our RX flow control inक्रमmation to the sender.
 * Socket must be locked. */
अटल व्योम pipe_grant_credits(काष्ठा sock *sk, gfp_t priority)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);

	BUG_ON(sk->sk_state != TCP_ESTABLISHED);

	चयन (pn->rx_fc) अणु
	हाल PN_LEGACY_FLOW_CONTROL: /* TODO */
		अवरोध;
	हाल PN_ONE_CREDIT_FLOW_CONTROL:
		अगर (pipe_snd_status(sk, PN_PEP_IND_FLOW_CONTROL,
					PEP_IND_READY, priority) == 0)
			pn->rx_credits = 1;
		अवरोध;
	हाल PN_MULTI_CREDIT_FLOW_CONTROL:
		अगर ((pn->rx_credits + CREDITS_THR) > CREDITS_MAX)
			अवरोध;
		अगर (pipe_snd_status(sk, PN_PEP_IND_ID_MCFC_GRANT_CREDITS,
					CREDITS_MAX - pn->rx_credits,
					priority) == 0)
			pn->rx_credits = CREDITS_MAX;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pipe_rcv_status(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा pnpipehdr *hdr;
	पूर्णांक wake = 0;

	अगर (!pskb_may_pull(skb, माप(*hdr) + 4))
		वापस -EINVAL;

	hdr = pnp_hdr(skb);
	अगर (hdr->pep_type != PN_PEP_TYPE_COMMON) अणु
		net_dbg_ratelimited("Phonet unknown PEP type: %u\n",
				    (अचिन्हित पूर्णांक)hdr->pep_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (hdr->data[0]) अणु
	हाल PN_PEP_IND_FLOW_CONTROL:
		चयन (pn->tx_fc) अणु
		हाल PN_LEGACY_FLOW_CONTROL:
			चयन (hdr->data[3]) अणु
			हाल PEP_IND_BUSY:
				atomic_set(&pn->tx_credits, 0);
				अवरोध;
			हाल PEP_IND_READY:
				atomic_set(&pn->tx_credits, wake = 1);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल PN_ONE_CREDIT_FLOW_CONTROL:
			अगर (hdr->data[3] == PEP_IND_READY)
				atomic_set(&pn->tx_credits, wake = 1);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल PN_PEP_IND_ID_MCFC_GRANT_CREDITS:
		अगर (pn->tx_fc != PN_MULTI_CREDIT_FLOW_CONTROL)
			अवरोध;
		atomic_add(wake = hdr->data[3], &pn->tx_credits);
		अवरोध;

	शेष:
		net_dbg_ratelimited("Phonet unknown PEP indication: %u\n",
				    (अचिन्हित पूर्णांक)hdr->data[0]);
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (wake)
		sk->sk_ग_लिखो_space(sk);
	वापस 0;
पूर्ण

अटल पूर्णांक pipe_rcv_created(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा pnpipehdr *hdr = pnp_hdr(skb);
	u8 n_sb = hdr->data0;

	pn->rx_fc = pn->tx_fc = PN_LEGACY_FLOW_CONTROL;
	__skb_pull(skb, माप(*hdr));
	जबतक (n_sb > 0) अणु
		u8 type, buf[2], len = माप(buf);
		u8 *data = pep_get_sb(skb, &type, &len, buf);

		अगर (data == शून्य)
			वापस -EINVAL;
		चयन (type) अणु
		हाल PN_PIPE_SB_NEGOTIATED_FC:
			अगर (len < 2 || (data[0] | data[1]) > 3)
				अवरोध;
			pn->tx_fc = data[0] & 3;
			pn->rx_fc = data[1] & 3;
			अवरोध;
		पूर्ण
		n_sb--;
	पूर्ण
	वापस 0;
पूर्ण

/* Queue an skb to a connected sock.
 * Socket lock must be held. */
अटल पूर्णांक pipe_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा pnpipehdr *hdr = pnp_hdr(skb);
	काष्ठा sk_buff_head *queue;
	पूर्णांक err = 0;

	BUG_ON(sk->sk_state == TCP_CLOSE_WAIT);

	चयन (hdr->message_id) अणु
	हाल PNS_PEP_CONNECT_REQ:
		pep_reject_conn(sk, skb, PN_PIPE_ERR_PEP_IN_USE, GFP_ATOMIC);
		अवरोध;

	हाल PNS_PEP_DISCONNECT_REQ:
		pep_reply(sk, skb, PN_PIPE_NO_ERROR, शून्य, 0, GFP_ATOMIC);
		sk->sk_state = TCP_CLOSE_WAIT;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		अवरोध;

	हाल PNS_PEP_ENABLE_REQ:
		/* Wait क्रम PNS_PIPE_(ENABLED|REसूचीECTED)_IND */
		pep_reply(sk, skb, PN_PIPE_NO_ERROR, शून्य, 0, GFP_ATOMIC);
		अवरोध;

	हाल PNS_PEP_RESET_REQ:
		चयन (hdr->state_after_reset) अणु
		हाल PN_PIPE_DISABLE:
			pn->init_enable = 0;
			अवरोध;
		हाल PN_PIPE_ENABLE:
			pn->init_enable = 1;
			अवरोध;
		शेष: /* not allowed to send an error here!? */
			err = -EINVAL;
			जाओ out;
		पूर्ण
		fallthrough;
	हाल PNS_PEP_DISABLE_REQ:
		atomic_set(&pn->tx_credits, 0);
		pep_reply(sk, skb, PN_PIPE_NO_ERROR, शून्य, 0, GFP_ATOMIC);
		अवरोध;

	हाल PNS_PEP_CTRL_REQ:
		अगर (skb_queue_len(&pn->ctrlreq_queue) >= PNPIPE_CTRLREQ_MAX) अणु
			atomic_inc(&sk->sk_drops);
			अवरोध;
		पूर्ण
		__skb_pull(skb, 4);
		queue = &pn->ctrlreq_queue;
		जाओ queue;

	हाल PNS_PIPE_ALIGNED_DATA:
		__skb_pull(skb, 1);
		fallthrough;
	हाल PNS_PIPE_DATA:
		__skb_pull(skb, 3); /* Pipe data header */
		अगर (!pn_flow_safe(pn->rx_fc)) अणु
			err = sock_queue_rcv_skb(sk, skb);
			अगर (!err)
				वापस NET_RX_SUCCESS;
			err = -ENOBUFS;
			अवरोध;
		पूर्ण

		अगर (pn->rx_credits == 0) अणु
			atomic_inc(&sk->sk_drops);
			err = -ENOBUFS;
			अवरोध;
		पूर्ण
		pn->rx_credits--;
		queue = &sk->sk_receive_queue;
		जाओ queue;

	हाल PNS_PEP_STATUS_IND:
		pipe_rcv_status(sk, skb);
		अवरोध;

	हाल PNS_PIPE_REसूचीECTED_IND:
		err = pipe_rcv_created(sk, skb);
		अवरोध;

	हाल PNS_PIPE_CREATED_IND:
		err = pipe_rcv_created(sk, skb);
		अगर (err)
			अवरोध;
		fallthrough;
	हाल PNS_PIPE_RESET_IND:
		अगर (!pn->init_enable)
			अवरोध;
		fallthrough;
	हाल PNS_PIPE_ENABLED_IND:
		अगर (!pn_flow_safe(pn->tx_fc)) अणु
			atomic_set(&pn->tx_credits, 1);
			sk->sk_ग_लिखो_space(sk);
		पूर्ण
		अगर (sk->sk_state == TCP_ESTABLISHED)
			अवरोध; /* Nothing to करो */
		sk->sk_state = TCP_ESTABLISHED;
		pipe_grant_credits(sk, GFP_ATOMIC);
		अवरोध;

	हाल PNS_PIPE_DISABLED_IND:
		sk->sk_state = TCP_SYN_RECV;
		pn->rx_credits = 0;
		अवरोध;

	शेष:
		net_dbg_ratelimited("Phonet unknown PEP message: %u\n",
				    hdr->message_id);
		err = -EINVAL;
	पूर्ण
out:
	kमुक्त_skb(skb);
	वापस (err == -ENOBUFS) ? NET_RX_DROP : NET_RX_SUCCESS;

queue:
	skb->dev = शून्य;
	skb_set_owner_r(skb, sk);
	skb_queue_tail(queue, skb);
	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_पढ़ोy(sk);
	वापस NET_RX_SUCCESS;
पूर्ण

/* Destroy connected sock. */
अटल व्योम pipe_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&pn->ctrlreq_queue);
पूर्ण

अटल u8 pipe_negotiate_fc(स्थिर u8 *fcs, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;
	u8 final_fc = PN_NO_FLOW_CONTROL;

	क्रम (i = 0; i < n; i++) अणु
		u8 fc = fcs[i];

		अगर (fc > final_fc && fc < PN_MAX_FLOW_CONTROL)
			final_fc = fc;
	पूर्ण
	वापस final_fc;
पूर्ण

अटल पूर्णांक pep_connresp_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा pnpipehdr *hdr;
	u8 n_sb;

	अगर (!pskb_pull(skb, माप(*hdr) + 4))
		वापस -EINVAL;

	hdr = pnp_hdr(skb);
	अगर (hdr->error_code != PN_PIPE_NO_ERROR)
		वापस -ECONNREFUSED;

	/* Parse sub-blocks */
	n_sb = hdr->data[3];
	जबतक (n_sb > 0) अणु
		u8 type, buf[6], len = माप(buf);
		स्थिर u8 *data = pep_get_sb(skb, &type, &len, buf);

		अगर (data == शून्य)
			वापस -EINVAL;

		चयन (type) अणु
		हाल PN_PIPE_SB_REQUIRED_FC_TX:
			अगर (len < 2 || len < data[0])
				अवरोध;
			pn->tx_fc = pipe_negotiate_fc(data + 2, len - 2);
			अवरोध;

		हाल PN_PIPE_SB_PREFERRED_FC_RX:
			अगर (len < 2 || len < data[0])
				अवरोध;
			pn->rx_fc = pipe_negotiate_fc(data + 2, len - 2);
			अवरोध;

		पूर्ण
		n_sb--;
	पूर्ण

	वापस pipe_handler_send_created_ind(sk);
पूर्ण

अटल पूर्णांक pep_enableresp_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pnpipehdr *hdr = pnp_hdr(skb);

	अगर (hdr->error_code != PN_PIPE_NO_ERROR)
		वापस -ECONNREFUSED;

	वापस pep_indicate(sk, PNS_PIPE_ENABLED_IND, 0 /* sub-blocks */,
		शून्य, 0, GFP_ATOMIC);

पूर्ण

अटल व्योम pipe_start_flow_control(काष्ठा sock *sk)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);

	अगर (!pn_flow_safe(pn->tx_fc)) अणु
		atomic_set(&pn->tx_credits, 1);
		sk->sk_ग_लिखो_space(sk);
	पूर्ण
	pipe_grant_credits(sk, GFP_ATOMIC);
पूर्ण

/* Queue an skb to an actively connected sock.
 * Socket lock must be held. */
अटल पूर्णांक pipe_handler_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा pnpipehdr *hdr = pnp_hdr(skb);
	पूर्णांक err = NET_RX_SUCCESS;

	चयन (hdr->message_id) अणु
	हाल PNS_PIPE_ALIGNED_DATA:
		__skb_pull(skb, 1);
		fallthrough;
	हाल PNS_PIPE_DATA:
		__skb_pull(skb, 3); /* Pipe data header */
		अगर (!pn_flow_safe(pn->rx_fc)) अणु
			err = sock_queue_rcv_skb(sk, skb);
			अगर (!err)
				वापस NET_RX_SUCCESS;
			err = NET_RX_DROP;
			अवरोध;
		पूर्ण

		अगर (pn->rx_credits == 0) अणु
			atomic_inc(&sk->sk_drops);
			err = NET_RX_DROP;
			अवरोध;
		पूर्ण
		pn->rx_credits--;
		skb->dev = शून्य;
		skb_set_owner_r(skb, sk);
		skb_queue_tail(&sk->sk_receive_queue, skb);
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_data_पढ़ोy(sk);
		वापस NET_RX_SUCCESS;

	हाल PNS_PEP_CONNECT_RESP:
		अगर (sk->sk_state != TCP_SYN_SENT)
			अवरोध;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		अगर (pep_connresp_rcv(sk, skb)) अणु
			sk->sk_state = TCP_CLOSE_WAIT;
			अवरोध;
		पूर्ण
		अगर (pn->init_enable == PN_PIPE_DISABLE)
			sk->sk_state = TCP_SYN_RECV;
		अन्यथा अणु
			sk->sk_state = TCP_ESTABLISHED;
			pipe_start_flow_control(sk);
		पूर्ण
		अवरोध;

	हाल PNS_PEP_ENABLE_RESP:
		अगर (sk->sk_state != TCP_SYN_SENT)
			अवरोध;

		अगर (pep_enableresp_rcv(sk, skb)) अणु
			sk->sk_state = TCP_CLOSE_WAIT;
			अवरोध;
		पूर्ण

		sk->sk_state = TCP_ESTABLISHED;
		pipe_start_flow_control(sk);
		अवरोध;

	हाल PNS_PEP_DISCONNECT_RESP:
		/* sock should alपढ़ोy be dead, nothing to करो */
		अवरोध;

	हाल PNS_PEP_STATUS_IND:
		pipe_rcv_status(sk, skb);
		अवरोध;
	पूर्ण
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

/* Listening sock must be locked */
अटल काष्ठा sock *pep_find_pipe(स्थिर काष्ठा hlist_head *hlist,
					स्थिर काष्ठा sockaddr_pn *dst,
					u8 pipe_handle)
अणु
	काष्ठा sock *sknode;
	u16 करोbj = pn_sockaddr_get_object(dst);

	sk_क्रम_each(sknode, hlist) अणु
		काष्ठा pep_sock *pnnode = pep_sk(sknode);

		/* Ports match, but addresses might not: */
		अगर (pnnode->pn_sk.sobject != करोbj)
			जारी;
		अगर (pnnode->pipe_handle != pipe_handle)
			जारी;
		अगर (sknode->sk_state == TCP_CLOSE_WAIT)
			जारी;

		sock_hold(sknode);
		वापस sknode;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Deliver an skb to a listening sock.
 * Socket lock must be held.
 * We then queue the skb to the right connected sock (अगर any).
 */
अटल पूर्णांक pep_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा sock *sknode;
	काष्ठा pnpipehdr *hdr;
	काष्ठा sockaddr_pn dst;
	u8 pipe_handle;

	अगर (!pskb_may_pull(skb, माप(*hdr)))
		जाओ drop;

	hdr = pnp_hdr(skb);
	pipe_handle = hdr->pipe_handle;
	अगर (pipe_handle == PN_PIPE_INVALID_HANDLE)
		जाओ drop;

	pn_skb_get_dst_sockaddr(skb, &dst);

	/* Look क्रम an existing pipe handle */
	sknode = pep_find_pipe(&pn->hlist, &dst, pipe_handle);
	अगर (sknode)
		वापस sk_receive_skb(sknode, skb, 1);

	चयन (hdr->message_id) अणु
	हाल PNS_PEP_CONNECT_REQ:
		अगर (sk->sk_state != TCP_LISTEN || sk_acceptq_is_full(sk)) अणु
			pep_reject_conn(sk, skb, PN_PIPE_ERR_PEP_IN_USE,
					GFP_ATOMIC);
			अवरोध;
		पूर्ण
		skb_queue_head(&sk->sk_receive_queue, skb);
		sk_acceptq_added(sk);
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_data_पढ़ोy(sk);
		वापस NET_RX_SUCCESS;

	हाल PNS_PEP_DISCONNECT_REQ:
		pep_reply(sk, skb, PN_PIPE_NO_ERROR, शून्य, 0, GFP_ATOMIC);
		अवरोध;

	हाल PNS_PEP_CTRL_REQ:
		pep_ctrlreq_error(sk, skb, PN_PIPE_INVALID_HANDLE, GFP_ATOMIC);
		अवरोध;

	हाल PNS_PEP_RESET_REQ:
	हाल PNS_PEP_ENABLE_REQ:
	हाल PNS_PEP_DISABLE_REQ:
		/* invalid handle is not even allowed here! */
		अवरोध;

	शेष:
		अगर ((1 << sk->sk_state)
				& ~(TCPF_CLOSE|TCPF_LISTEN|TCPF_CLOSE_WAIT))
			/* actively connected socket */
			वापस pipe_handler_करो_rcv(sk, skb);
	पूर्ण
drop:
	kमुक्त_skb(skb);
	वापस NET_RX_SUCCESS;
पूर्ण

अटल पूर्णांक pipe_करो_हटाओ(काष्ठा sock *sk)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा pnpipehdr *ph;
	काष्ठा sk_buff *skb;

	skb = pep_alloc_skb(sk, शून्य, 0, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	ph = pnp_hdr(skb);
	ph->utid = 0;
	ph->message_id = PNS_PIPE_REMOVE_REQ;
	ph->pipe_handle = pn->pipe_handle;
	ph->data0 = PAD;
	वापस pn_skb_send(sk, skb, शून्य);
पूर्ण

/* associated socket ceases to exist */
अटल व्योम pep_sock_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	पूर्णांक अगरindex = 0;

	sock_hold(sk); /* keep a reference after sk_common_release() */
	sk_common_release(sk);

	lock_sock(sk);
	अगर ((1 << sk->sk_state) & (TCPF_SYN_RECV|TCPF_ESTABLISHED)) अणु
		अगर (sk->sk_backlog_rcv == pipe_करो_rcv)
			/* Forcefully हटाओ dangling Phonet pipe */
			pipe_करो_हटाओ(sk);
		अन्यथा
			pipe_handler_request(sk, PNS_PEP_DISCONNECT_REQ, PAD,
						शून्य, 0);
	पूर्ण
	sk->sk_state = TCP_CLOSE;

	अगरindex = pn->अगरindex;
	pn->अगरindex = 0;
	release_sock(sk);

	अगर (अगरindex)
		gprs_detach(sk);
	sock_put(sk);
पूर्ण

अटल काष्ठा sock *pep_sock_accept(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक *errp,
				    bool kern)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk), *newpn;
	काष्ठा sock *newsk = शून्य;
	काष्ठा sk_buff *skb;
	काष्ठा pnpipehdr *hdr;
	काष्ठा sockaddr_pn dst, src;
	पूर्णांक err;
	u16 peer_type;
	u8 pipe_handle, enabled, n_sb;
	u8 aligned = 0;

	skb = skb_recv_datagram(sk, 0, flags & O_NONBLOCK, errp);
	अगर (!skb)
		वापस शून्य;

	lock_sock(sk);
	अगर (sk->sk_state != TCP_LISTEN) अणु
		err = -EINVAL;
		जाओ drop;
	पूर्ण
	sk_acceptq_हटाओd(sk);

	err = -EPROTO;
	अगर (!pskb_may_pull(skb, माप(*hdr) + 4))
		जाओ drop;

	hdr = pnp_hdr(skb);
	pipe_handle = hdr->pipe_handle;
	चयन (hdr->state_after_connect) अणु
	हाल PN_PIPE_DISABLE:
		enabled = 0;
		अवरोध;
	हाल PN_PIPE_ENABLE:
		enabled = 1;
		अवरोध;
	शेष:
		pep_reject_conn(sk, skb, PN_PIPE_ERR_INVALID_PARAM,
				GFP_KERNEL);
		जाओ drop;
	पूर्ण
	peer_type = hdr->other_pep_type << 8;

	/* Parse sub-blocks (options) */
	n_sb = hdr->data[3];
	जबतक (n_sb > 0) अणु
		u8 type, buf[1], len = माप(buf);
		स्थिर u8 *data = pep_get_sb(skb, &type, &len, buf);

		अगर (data == शून्य)
			जाओ drop;
		चयन (type) अणु
		हाल PN_PIPE_SB_CONNECT_REQ_PEP_SUB_TYPE:
			अगर (len < 1)
				जाओ drop;
			peer_type = (peer_type & 0xff00) | data[0];
			अवरोध;
		हाल PN_PIPE_SB_ALIGNED_DATA:
			aligned = data[0] != 0;
			अवरोध;
		पूर्ण
		n_sb--;
	पूर्ण

	/* Check क्रम duplicate pipe handle */
	newsk = pep_find_pipe(&pn->hlist, &dst, pipe_handle);
	अगर (unlikely(newsk)) अणु
		__sock_put(newsk);
		newsk = शून्य;
		pep_reject_conn(sk, skb, PN_PIPE_ERR_PEP_IN_USE, GFP_KERNEL);
		जाओ drop;
	पूर्ण

	/* Create a new to-be-accepted sock */
	newsk = sk_alloc(sock_net(sk), PF_PHONET, GFP_KERNEL, sk->sk_prot,
			 kern);
	अगर (!newsk) अणु
		pep_reject_conn(sk, skb, PN_PIPE_ERR_OVERLOAD, GFP_KERNEL);
		err = -ENOBUFS;
		जाओ drop;
	पूर्ण

	sock_init_data(शून्य, newsk);
	newsk->sk_state = TCP_SYN_RECV;
	newsk->sk_backlog_rcv = pipe_करो_rcv;
	newsk->sk_protocol = sk->sk_protocol;
	newsk->sk_deकाष्ठा = pipe_deकाष्ठा;

	newpn = pep_sk(newsk);
	pn_skb_get_dst_sockaddr(skb, &dst);
	pn_skb_get_src_sockaddr(skb, &src);
	newpn->pn_sk.sobject = pn_sockaddr_get_object(&dst);
	newpn->pn_sk.करोbject = pn_sockaddr_get_object(&src);
	newpn->pn_sk.resource = pn_sockaddr_get_resource(&dst);
	sock_hold(sk);
	newpn->listener = sk;
	skb_queue_head_init(&newpn->ctrlreq_queue);
	newpn->pipe_handle = pipe_handle;
	atomic_set(&newpn->tx_credits, 0);
	newpn->अगरindex = 0;
	newpn->peer_type = peer_type;
	newpn->rx_credits = 0;
	newpn->rx_fc = newpn->tx_fc = PN_LEGACY_FLOW_CONTROL;
	newpn->init_enable = enabled;
	newpn->aligned = aligned;

	err = pep_accept_conn(newsk, skb);
	अगर (err) अणु
		sock_put(newsk);
		newsk = शून्य;
		जाओ drop;
	पूर्ण
	sk_add_node(newsk, &pn->hlist);
drop:
	release_sock(sk);
	kमुक्त_skb(skb);
	*errp = err;
	वापस newsk;
पूर्ण

अटल पूर्णांक pep_sock_connect(काष्ठा sock *sk, काष्ठा sockaddr *addr, पूर्णांक len)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	पूर्णांक err;
	u8 data[4] = अणु 0 /* sub-blocks */, PAD, PAD, PAD पूर्ण;

	अगर (pn->pipe_handle == PN_PIPE_INVALID_HANDLE)
		pn->pipe_handle = 1; /* anything but INVALID_HANDLE */

	err = pipe_handler_request(sk, PNS_PEP_CONNECT_REQ,
				pn->init_enable, data, 4);
	अगर (err) अणु
		pn->pipe_handle = PN_PIPE_INVALID_HANDLE;
		वापस err;
	पूर्ण

	sk->sk_state = TCP_SYN_SENT;

	वापस 0;
पूर्ण

अटल पूर्णांक pep_sock_enable(काष्ठा sock *sk, काष्ठा sockaddr *addr, पूर्णांक len)
अणु
	पूर्णांक err;

	err = pipe_handler_request(sk, PNS_PEP_ENABLE_REQ, PAD,
				शून्य, 0);
	अगर (err)
		वापस err;

	sk->sk_state = TCP_SYN_SENT;

	वापस 0;
पूर्ण

अटल पूर्णांक pep_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	पूर्णांक answ;
	पूर्णांक ret = -ENOIOCTLCMD;

	चयन (cmd) अणु
	हाल SIOCINQ:
		अगर (sk->sk_state == TCP_LISTEN) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		lock_sock(sk);
		अगर (sock_flag(sk, SOCK_URGINLINE) &&
		    !skb_queue_empty(&pn->ctrlreq_queue))
			answ = skb_peek(&pn->ctrlreq_queue)->len;
		अन्यथा अगर (!skb_queue_empty(&sk->sk_receive_queue))
			answ = skb_peek(&sk->sk_receive_queue)->len;
		अन्यथा
			answ = 0;
		release_sock(sk);
		ret = put_user(answ, (पूर्णांक __user *)arg);
		अवरोध;

	हाल SIOCPNENABLEPIPE:
		lock_sock(sk);
		अगर (sk->sk_state == TCP_SYN_SENT)
			ret =  -EBUSY;
		अन्यथा अगर (sk->sk_state == TCP_ESTABLISHED)
			ret = -EISCONN;
		अन्यथा
			ret = pep_sock_enable(sk, शून्य, 0);
		release_sock(sk);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pep_init(काष्ठा sock *sk)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);

	sk->sk_deकाष्ठा = pipe_deकाष्ठा;
	INIT_HLIST_HEAD(&pn->hlist);
	pn->listener = शून्य;
	skb_queue_head_init(&pn->ctrlreq_queue);
	atomic_set(&pn->tx_credits, 0);
	pn->अगरindex = 0;
	pn->peer_type = 0;
	pn->pipe_handle = PN_PIPE_INVALID_HANDLE;
	pn->rx_credits = 0;
	pn->rx_fc = pn->tx_fc = PN_LEGACY_FLOW_CONTROL;
	pn->init_enable = 1;
	pn->aligned = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक pep_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	पूर्णांक val = 0, err = 0;

	अगर (level != SOL_PNPIPE)
		वापस -ENOPROTOOPT;
	अगर (optlen >= माप(पूर्णांक)) अणु
		अगर (copy_from_sockptr(&val, optval, माप(पूर्णांक)))
			वापस -EFAULT;
	पूर्ण

	lock_sock(sk);
	चयन (optname) अणु
	हाल PNPIPE_ENCAP:
		अगर (val && val != PNPIPE_ENCAP_IP) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (!pn->अगरindex == !val)
			अवरोध; /* Nothing to करो! */
		अगर (!capable(CAP_NET_ADMIN)) अणु
			err = -EPERM;
			अवरोध;
		पूर्ण
		अगर (val) अणु
			release_sock(sk);
			err = gprs_attach(sk);
			अगर (err > 0) अणु
				pn->अगरindex = err;
				err = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			pn->अगरindex = 0;
			release_sock(sk);
			gprs_detach(sk);
			err = 0;
		पूर्ण
		जाओ out_norel;

	हाल PNPIPE_HANDLE:
		अगर ((sk->sk_state == TCP_CLOSE) &&
			(val >= 0) && (val < PN_PIPE_INVALID_HANDLE))
			pn->pipe_handle = val;
		अन्यथा
			err = -EINVAL;
		अवरोध;

	हाल PNPIPE_INITSTATE:
		pn->init_enable = !!val;
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
	पूर्ण
	release_sock(sk);

out_norel:
	वापस err;
पूर्ण

अटल पूर्णांक pep_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
				अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	पूर्णांक len, val;

	अगर (level != SOL_PNPIPE)
		वापस -ENOPROTOOPT;
	अगर (get_user(len, optlen))
		वापस -EFAULT;

	चयन (optname) अणु
	हाल PNPIPE_ENCAP:
		val = pn->अगरindex ? PNPIPE_ENCAP_IP : PNPIPE_ENCAP_NONE;
		अवरोध;

	हाल PNPIPE_IFINDEX:
		val = pn->अगरindex;
		अवरोध;

	हाल PNPIPE_HANDLE:
		val = pn->pipe_handle;
		अगर (val == PN_PIPE_INVALID_HANDLE)
			वापस -EINVAL;
		अवरोध;

	हाल PNPIPE_INITSTATE:
		val = pn->init_enable;
		अवरोध;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	len = min_t(अचिन्हित पूर्णांक, माप(पूर्णांक), len);
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (put_user(val, (पूर्णांक __user *) optval))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक pipe_skb_send(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा pnpipehdr *ph;
	पूर्णांक err;

	अगर (pn_flow_safe(pn->tx_fc) &&
	    !atomic_add_unless(&pn->tx_credits, -1, 0)) अणु
		kमुक्त_skb(skb);
		वापस -ENOBUFS;
	पूर्ण

	skb_push(skb, 3 + pn->aligned);
	skb_reset_transport_header(skb);
	ph = pnp_hdr(skb);
	ph->utid = 0;
	अगर (pn->aligned) अणु
		ph->message_id = PNS_PIPE_ALIGNED_DATA;
		ph->data0 = 0; /* padding */
	पूर्ण अन्यथा
		ph->message_id = PNS_PIPE_DATA;
	ph->pipe_handle = pn->pipe_handle;
	err = pn_skb_send(sk, skb, शून्य);

	अगर (err && pn_flow_safe(pn->tx_fc))
		atomic_inc(&pn->tx_credits);
	वापस err;

पूर्ण

अटल पूर्णांक pep_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा sk_buff *skb;
	दीर्घ समयo;
	पूर्णांक flags = msg->msg_flags;
	पूर्णांक err, करोne;

	अगर (len > अच_लघु_उच्च)
		वापस -EMSGSIZE;

	अगर ((msg->msg_flags & ~(MSG_DONTWAIT|MSG_EOR|MSG_NOSIGNAL|
				MSG_CMSG_COMPAT)) ||
			!(msg->msg_flags & MSG_EOR))
		वापस -EOPNOTSUPP;

	skb = sock_alloc_send_skb(sk, MAX_PNPIPE_HEADER + len,
					flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		वापस err;

	skb_reserve(skb, MAX_PHONET_HEADER + 3 + pn->aligned);
	err = स_नकल_from_msg(skb_put(skb, len), msg, len);
	अगर (err < 0)
		जाओ outमुक्त;

	lock_sock(sk);
	समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);
	अगर ((1 << sk->sk_state) & (TCPF_LISTEN|TCPF_CLOSE)) अणु
		err = -ENOTCONN;
		जाओ out;
	पूर्ण
	अगर (sk->sk_state != TCP_ESTABLISHED) अणु
		/* Wait until the pipe माला_लो to enabled state */
disabled:
		err = sk_stream_रुको_connect(sk, &समयo);
		अगर (err)
			जाओ out;

		अगर (sk->sk_state == TCP_CLOSE_WAIT) अणु
			err = -ECONNRESET;
			जाओ out;
		पूर्ण
	पूर्ण
	BUG_ON(sk->sk_state != TCP_ESTABLISHED);

	/* Wait until flow control allows TX */
	करोne = atomic_पढ़ो(&pn->tx_credits);
	जबतक (!करोne) अणु
		DEFINE_WAIT_FUNC(रुको, woken_wake_function);

		अगर (!समयo) अणु
			err = -EAGAIN;
			जाओ out;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			err = sock_पूर्णांकr_त्रुटि_सं(समयo);
			जाओ out;
		पूर्ण

		add_रुको_queue(sk_sleep(sk), &रुको);
		करोne = sk_रुको_event(sk, &समयo, atomic_पढ़ो(&pn->tx_credits), &रुको);
		हटाओ_रुको_queue(sk_sleep(sk), &रुको);

		अगर (sk->sk_state != TCP_ESTABLISHED)
			जाओ disabled;
	पूर्ण

	err = pipe_skb_send(sk, skb);
	अगर (err >= 0)
		err = len; /* success! */
	skb = शून्य;
out:
	release_sock(sk);
outमुक्त:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

पूर्णांक pep_ग_लिखोable(काष्ठा sock *sk)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);

	वापस atomic_पढ़ो(&pn->tx_credits);
पूर्ण

पूर्णांक pep_ग_लिखो(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *rskb, *fs;
	पूर्णांक flen = 0;

	अगर (pep_sk(sk)->aligned)
		वापस pipe_skb_send(sk, skb);

	rskb = alloc_skb(MAX_PNPIPE_HEADER, GFP_ATOMIC);
	अगर (!rskb) अणु
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण
	skb_shinfo(rskb)->frag_list = skb;
	rskb->len += skb->len;
	rskb->data_len += rskb->len;
	rskb->truesize += rskb->len;

	/* Aव्योम nested fragments */
	skb_walk_frags(skb, fs)
		flen += fs->len;
	skb->next = skb_shinfo(skb)->frag_list;
	skb_frag_list_init(skb);
	skb->len -= flen;
	skb->data_len -= flen;
	skb->truesize -= flen;

	skb_reserve(rskb, MAX_PHONET_HEADER + 3);
	वापस pipe_skb_send(sk, rskb);
पूर्ण

काष्ठा sk_buff *pep_पढ़ो(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb = skb_dequeue(&sk->sk_receive_queue);

	अगर (sk->sk_state == TCP_ESTABLISHED)
		pipe_grant_credits(sk, GFP_ATOMIC);
	वापस skb;
पूर्ण

अटल पूर्णांक pep_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
		       पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (flags & ~(MSG_OOB|MSG_PEEK|MSG_TRUNC|MSG_DONTWAIT|MSG_WAITALL|
			MSG_NOSIGNAL|MSG_CMSG_COMPAT))
		वापस -EOPNOTSUPP;

	अगर (unlikely(1 << sk->sk_state & (TCPF_LISTEN | TCPF_CLOSE)))
		वापस -ENOTCONN;

	अगर ((flags & MSG_OOB) || sock_flag(sk, SOCK_URGINLINE)) अणु
		/* Dequeue and acknowledge control request */
		काष्ठा pep_sock *pn = pep_sk(sk);

		अगर (flags & MSG_PEEK)
			वापस -EOPNOTSUPP;
		skb = skb_dequeue(&pn->ctrlreq_queue);
		अगर (skb) अणु
			pep_ctrlreq_error(sk, skb, PN_PIPE_NO_ERROR,
						GFP_KERNEL);
			msg->msg_flags |= MSG_OOB;
			जाओ copy;
		पूर्ण
		अगर (flags & MSG_OOB)
			वापस -EINVAL;
	पूर्ण

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	lock_sock(sk);
	अगर (skb == शून्य) अणु
		अगर (err == -ENOTCONN && sk->sk_state == TCP_CLOSE_WAIT)
			err = -ECONNRESET;
		release_sock(sk);
		वापस err;
	पूर्ण

	अगर (sk->sk_state == TCP_ESTABLISHED)
		pipe_grant_credits(sk, GFP_KERNEL);
	release_sock(sk);
copy:
	msg->msg_flags |= MSG_EOR;
	अगर (skb->len > len)
		msg->msg_flags |= MSG_TRUNC;
	अन्यथा
		len = skb->len;

	err = skb_copy_datagram_msg(skb, 0, msg, len);
	अगर (!err)
		err = (flags & MSG_TRUNC) ? skb->len : len;

	skb_मुक्त_datagram(sk, skb);
	वापस err;
पूर्ण

अटल व्योम pep_sock_unhash(काष्ठा sock *sk)
अणु
	काष्ठा pep_sock *pn = pep_sk(sk);
	काष्ठा sock *skparent = शून्य;

	lock_sock(sk);

	अगर (pn->listener != शून्य) अणु
		skparent = pn->listener;
		pn->listener = शून्य;
		release_sock(sk);

		pn = pep_sk(skparent);
		lock_sock(skparent);
		sk_del_node_init(sk);
		sk = skparent;
	पूर्ण

	/* Unhash a listening sock only when it is बंदd
	 * and all of its active connected pipes are बंदd. */
	अगर (hlist_empty(&pn->hlist))
		pn_sock_unhash(&pn->pn_sk.sk);
	release_sock(sk);

	अगर (skparent)
		sock_put(skparent);
पूर्ण

अटल काष्ठा proto pep_proto = अणु
	.बंद		= pep_sock_बंद,
	.accept		= pep_sock_accept,
	.connect	= pep_sock_connect,
	.ioctl		= pep_ioctl,
	.init		= pep_init,
	.setsockopt	= pep_setsockopt,
	.माला_लोockopt	= pep_माला_लोockopt,
	.sendmsg	= pep_sendmsg,
	.recvmsg	= pep_recvmsg,
	.backlog_rcv	= pep_करो_rcv,
	.hash		= pn_sock_hash,
	.unhash		= pep_sock_unhash,
	.get_port	= pn_sock_get_port,
	.obj_size	= माप(काष्ठा pep_sock),
	.owner		= THIS_MODULE,
	.name		= "PNPIPE",
पूर्ण;

अटल स्थिर काष्ठा phonet_protocol pep_pn_proto = अणु
	.ops		= &phonet_stream_ops,
	.prot		= &pep_proto,
	.sock_type	= SOCK_SEQPACKET,
पूर्ण;

अटल पूर्णांक __init pep_रेजिस्टर(व्योम)
अणु
	वापस phonet_proto_रेजिस्टर(PN_PROTO_PIPE, &pep_pn_proto);
पूर्ण

अटल व्योम __निकास pep_unरेजिस्टर(व्योम)
अणु
	phonet_proto_unरेजिस्टर(PN_PROTO_PIPE, &pep_pn_proto);
पूर्ण

module_init(pep_रेजिस्टर);
module_निकास(pep_unरेजिस्टर);
MODULE_AUTHOR("Remi Denis-Courmont, Nokia");
MODULE_DESCRIPTION("Phonet pipe protocol");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO(PF_PHONET, PN_PROTO_PIPE);
