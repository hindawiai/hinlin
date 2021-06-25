<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Multipath TCP
 *
 * Copyright (c) 2017 - 2019, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "MPTCP: " fmt

#समावेश <linux/kernel.h>
#समावेश <crypto/sha2.h>
#समावेश <net/tcp.h>
#समावेश <net/mptcp.h>
#समावेश "protocol.h"
#समावेश "mib.h"

#समावेश <trace/events/mptcp.h>

अटल bool mptcp_cap_flag_sha256(u8 flags)
अणु
	वापस (flags & MPTCP_CAP_FLAG_MASK) == MPTCP_CAP_HMAC_SHA256;
पूर्ण

अटल व्योम mptcp_parse_option(स्थिर काष्ठा sk_buff *skb,
			       स्थिर अचिन्हित अक्षर *ptr, पूर्णांक opsize,
			       काष्ठा mptcp_options_received *mp_opt)
अणु
	u8 subtype = *ptr >> 4;
	पूर्णांक expected_opsize;
	u8 version;
	u8 flags;
	u8 i;

	चयन (subtype) अणु
	हाल MPTCPOPT_MP_CAPABLE:
		/* strict size checking */
		अगर (!(TCP_SKB_CB(skb)->tcp_flags & TCPHDR_SYN)) अणु
			अगर (skb->len > tcp_hdr(skb)->करोff << 2)
				expected_opsize = TCPOLEN_MPTCP_MPC_ACK_DATA;
			अन्यथा
				expected_opsize = TCPOLEN_MPTCP_MPC_ACK;
		पूर्ण अन्यथा अणु
			अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_ACK)
				expected_opsize = TCPOLEN_MPTCP_MPC_SYNACK;
			अन्यथा
				expected_opsize = TCPOLEN_MPTCP_MPC_SYN;
		पूर्ण
		अगर (opsize != expected_opsize)
			अवरोध;

		/* try to be gentle vs future versions on the initial syn */
		version = *ptr++ & MPTCP_VERSION_MASK;
		अगर (opsize != TCPOLEN_MPTCP_MPC_SYN) अणु
			अगर (version != MPTCP_SUPPORTED_VERSION)
				अवरोध;
		पूर्ण अन्यथा अगर (version < MPTCP_SUPPORTED_VERSION) अणु
			अवरोध;
		पूर्ण

		flags = *ptr++;
		अगर (!mptcp_cap_flag_sha256(flags) ||
		    (flags & MPTCP_CAP_EXTENSIBILITY))
			अवरोध;

		/* RFC 6824, Section 3.1:
		 * "For the Checksum Required bit (labeled "A"), अगर either
		 * host requires the use of checksums, checksums MUST be used.
		 * In other words, the only way क्रम checksums not to be used
		 * is अगर both hosts in their SYNs set A=0."
		 *
		 * Section 3.3.0:
		 * "If a checksum is not present when its use has been
		 * negotiated, the receiver MUST बंद the subflow with a RST as
		 * it is considered broken."
		 *
		 * We करोn't implement DSS checksum - fall back to TCP.
		 */
		अगर (flags & MPTCP_CAP_CHECKSUM_REQD)
			अवरोध;

		mp_opt->mp_capable = 1;
		अगर (opsize >= TCPOLEN_MPTCP_MPC_SYNACK) अणु
			mp_opt->sndr_key = get_unaligned_be64(ptr);
			ptr += 8;
		पूर्ण
		अगर (opsize >= TCPOLEN_MPTCP_MPC_ACK) अणु
			mp_opt->rcvr_key = get_unaligned_be64(ptr);
			ptr += 8;
		पूर्ण
		अगर (opsize == TCPOLEN_MPTCP_MPC_ACK_DATA) अणु
			/* Section 3.1.:
			 * "the data parameters in a MP_CAPABLE are semantically
			 * equivalent to those in a DSS option and can be used
			 * पूर्णांकerchangeably."
			 */
			mp_opt->dss = 1;
			mp_opt->use_map = 1;
			mp_opt->mpc_map = 1;
			mp_opt->data_len = get_unaligned_be16(ptr);
			ptr += 2;
		पूर्ण
		pr_debug("MP_CAPABLE version=%x, flags=%x, optlen=%d sndr=%llu, rcvr=%llu len=%d",
			 version, flags, opsize, mp_opt->sndr_key,
			 mp_opt->rcvr_key, mp_opt->data_len);
		अवरोध;

	हाल MPTCPOPT_MP_JOIN:
		mp_opt->mp_join = 1;
		अगर (opsize == TCPOLEN_MPTCP_MPJ_SYN) अणु
			mp_opt->backup = *ptr++ & MPTCPOPT_BACKUP;
			mp_opt->join_id = *ptr++;
			mp_opt->token = get_unaligned_be32(ptr);
			ptr += 4;
			mp_opt->nonce = get_unaligned_be32(ptr);
			ptr += 4;
			pr_debug("MP_JOIN bkup=%u, id=%u, token=%u, nonce=%u",
				 mp_opt->backup, mp_opt->join_id,
				 mp_opt->token, mp_opt->nonce);
		पूर्ण अन्यथा अगर (opsize == TCPOLEN_MPTCP_MPJ_SYNACK) अणु
			mp_opt->backup = *ptr++ & MPTCPOPT_BACKUP;
			mp_opt->join_id = *ptr++;
			mp_opt->thmac = get_unaligned_be64(ptr);
			ptr += 8;
			mp_opt->nonce = get_unaligned_be32(ptr);
			ptr += 4;
			pr_debug("MP_JOIN bkup=%u, id=%u, thmac=%llu, nonce=%u",
				 mp_opt->backup, mp_opt->join_id,
				 mp_opt->thmac, mp_opt->nonce);
		पूर्ण अन्यथा अगर (opsize == TCPOLEN_MPTCP_MPJ_ACK) अणु
			ptr += 2;
			स_नकल(mp_opt->hmac, ptr, MPTCPOPT_HMAC_LEN);
			pr_debug("MP_JOIN hmac");
		पूर्ण अन्यथा अणु
			mp_opt->mp_join = 0;
		पूर्ण
		अवरोध;

	हाल MPTCPOPT_DSS:
		pr_debug("DSS");
		ptr++;

		/* we must clear 'mpc_map' be able to detect MP_CAPABLE
		 * map vs DSS map in mptcp_incoming_options(), and reस्थिरruct
		 * map info accordingly
		 */
		mp_opt->mpc_map = 0;
		flags = (*ptr++) & MPTCP_DSS_FLAG_MASK;
		mp_opt->data_fin = (flags & MPTCP_DSS_DATA_FIN) != 0;
		mp_opt->dsn64 = (flags & MPTCP_DSS_DSN64) != 0;
		mp_opt->use_map = (flags & MPTCP_DSS_HAS_MAP) != 0;
		mp_opt->ack64 = (flags & MPTCP_DSS_ACK64) != 0;
		mp_opt->use_ack = (flags & MPTCP_DSS_HAS_ACK);

		pr_debug("data_fin=%d dsn64=%d use_map=%d ack64=%d use_ack=%d",
			 mp_opt->data_fin, mp_opt->dsn64,
			 mp_opt->use_map, mp_opt->ack64,
			 mp_opt->use_ack);

		expected_opsize = TCPOLEN_MPTCP_DSS_BASE;

		अगर (mp_opt->use_ack) अणु
			अगर (mp_opt->ack64)
				expected_opsize += TCPOLEN_MPTCP_DSS_ACK64;
			अन्यथा
				expected_opsize += TCPOLEN_MPTCP_DSS_ACK32;
		पूर्ण

		अगर (mp_opt->use_map) अणु
			अगर (mp_opt->dsn64)
				expected_opsize += TCPOLEN_MPTCP_DSS_MAP64;
			अन्यथा
				expected_opsize += TCPOLEN_MPTCP_DSS_MAP32;
		पूर्ण

		/* RFC 6824, Section 3.3:
		 * If a checksum is present, but its use had
		 * not been negotiated in the MP_CAPABLE handshake,
		 * the checksum field MUST be ignored.
		 */
		अगर (opsize != expected_opsize &&
		    opsize != expected_opsize + TCPOLEN_MPTCP_DSS_CHECKSUM)
			अवरोध;

		mp_opt->dss = 1;

		अगर (mp_opt->use_ack) अणु
			अगर (mp_opt->ack64) अणु
				mp_opt->data_ack = get_unaligned_be64(ptr);
				ptr += 8;
			पूर्ण अन्यथा अणु
				mp_opt->data_ack = get_unaligned_be32(ptr);
				ptr += 4;
			पूर्ण

			pr_debug("data_ack=%llu", mp_opt->data_ack);
		पूर्ण

		अगर (mp_opt->use_map) अणु
			अगर (mp_opt->dsn64) अणु
				mp_opt->data_seq = get_unaligned_be64(ptr);
				ptr += 8;
			पूर्ण अन्यथा अणु
				mp_opt->data_seq = get_unaligned_be32(ptr);
				ptr += 4;
			पूर्ण

			mp_opt->subflow_seq = get_unaligned_be32(ptr);
			ptr += 4;

			mp_opt->data_len = get_unaligned_be16(ptr);
			ptr += 2;

			pr_debug("data_seq=%llu subflow_seq=%u data_len=%u",
				 mp_opt->data_seq, mp_opt->subflow_seq,
				 mp_opt->data_len);
		पूर्ण

		अवरोध;

	हाल MPTCPOPT_ADD_ADDR:
		mp_opt->echo = (*ptr++) & MPTCP_ADDR_ECHO;
		अगर (!mp_opt->echo) अणु
			अगर (opsize == TCPOLEN_MPTCP_ADD_ADDR ||
			    opsize == TCPOLEN_MPTCP_ADD_ADDR_PORT)
				mp_opt->addr.family = AF_INET;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
			अन्यथा अगर (opsize == TCPOLEN_MPTCP_ADD_ADDR6 ||
				 opsize == TCPOLEN_MPTCP_ADD_ADDR6_PORT)
				mp_opt->addr.family = AF_INET6;
#पूर्ण_अगर
			अन्यथा
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (opsize == TCPOLEN_MPTCP_ADD_ADDR_BASE ||
			    opsize == TCPOLEN_MPTCP_ADD_ADDR_BASE_PORT)
				mp_opt->addr.family = AF_INET;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
			अन्यथा अगर (opsize == TCPOLEN_MPTCP_ADD_ADDR6_BASE ||
				 opsize == TCPOLEN_MPTCP_ADD_ADDR6_BASE_PORT)
				mp_opt->addr.family = AF_INET6;
#पूर्ण_अगर
			अन्यथा
				अवरोध;
		पूर्ण

		mp_opt->add_addr = 1;
		mp_opt->addr.id = *ptr++;
		अगर (mp_opt->addr.family == AF_INET) अणु
			स_नकल((u8 *)&mp_opt->addr.addr.s_addr, (u8 *)ptr, 4);
			ptr += 4;
			अगर (opsize == TCPOLEN_MPTCP_ADD_ADDR_PORT ||
			    opsize == TCPOLEN_MPTCP_ADD_ADDR_BASE_PORT) अणु
				mp_opt->addr.port = htons(get_unaligned_be16(ptr));
				ptr += 2;
			पूर्ण
		पूर्ण
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
		अन्यथा अणु
			स_नकल(mp_opt->addr.addr6.s6_addr, (u8 *)ptr, 16);
			ptr += 16;
			अगर (opsize == TCPOLEN_MPTCP_ADD_ADDR6_PORT ||
			    opsize == TCPOLEN_MPTCP_ADD_ADDR6_BASE_PORT) अणु
				mp_opt->addr.port = htons(get_unaligned_be16(ptr));
				ptr += 2;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		अगर (!mp_opt->echo) अणु
			mp_opt->ahmac = get_unaligned_be64(ptr);
			ptr += 8;
		पूर्ण
		pr_debug("ADD_ADDR%s: id=%d, ahmac=%llu, echo=%d, port=%d",
			 (mp_opt->addr.family == AF_INET6) ? "6" : "",
			 mp_opt->addr.id, mp_opt->ahmac, mp_opt->echo, ntohs(mp_opt->addr.port));
		अवरोध;

	हाल MPTCPOPT_RM_ADDR:
		अगर (opsize < TCPOLEN_MPTCP_RM_ADDR_BASE + 1 ||
		    opsize > TCPOLEN_MPTCP_RM_ADDR_BASE + MPTCP_RM_IDS_MAX)
			अवरोध;

		ptr++;

		mp_opt->rm_addr = 1;
		mp_opt->rm_list.nr = opsize - TCPOLEN_MPTCP_RM_ADDR_BASE;
		क्रम (i = 0; i < mp_opt->rm_list.nr; i++)
			mp_opt->rm_list.ids[i] = *ptr++;
		pr_debug("RM_ADDR: rm_list_nr=%d", mp_opt->rm_list.nr);
		अवरोध;

	हाल MPTCPOPT_MP_PRIO:
		अगर (opsize != TCPOLEN_MPTCP_PRIO)
			अवरोध;

		mp_opt->mp_prio = 1;
		mp_opt->backup = *ptr++ & MPTCP_PRIO_BKUP;
		pr_debug("MP_PRIO: prio=%d", mp_opt->backup);
		अवरोध;

	हाल MPTCPOPT_MP_FASTCLOSE:
		अगर (opsize != TCPOLEN_MPTCP_FASTCLOSE)
			अवरोध;

		ptr += 2;
		mp_opt->rcvr_key = get_unaligned_be64(ptr);
		ptr += 8;
		mp_opt->fastबंद = 1;
		अवरोध;

	हाल MPTCPOPT_RST:
		अगर (opsize != TCPOLEN_MPTCP_RST)
			अवरोध;

		अगर (!(TCP_SKB_CB(skb)->tcp_flags & TCPHDR_RST))
			अवरोध;
		mp_opt->reset = 1;
		flags = *ptr++;
		mp_opt->reset_transient = flags & MPTCP_RST_TRANSIENT;
		mp_opt->reset_reason = *ptr;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम mptcp_get_options(स्थिर काष्ठा sk_buff *skb,
		       काष्ठा mptcp_options_received *mp_opt)
अणु
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	स्थिर अचिन्हित अक्षर *ptr;
	पूर्णांक length;

	/* initialize option status */
	mp_opt->mp_capable = 0;
	mp_opt->mp_join = 0;
	mp_opt->add_addr = 0;
	mp_opt->ahmac = 0;
	mp_opt->fastबंद = 0;
	mp_opt->addr.port = 0;
	mp_opt->rm_addr = 0;
	mp_opt->dss = 0;
	mp_opt->mp_prio = 0;
	mp_opt->reset = 0;

	length = (th->करोff * 4) - माप(काष्ठा tcphdr);
	ptr = (स्थिर अचिन्हित अक्षर *)(th + 1);

	जबतक (length > 0) अणु
		पूर्णांक opcode = *ptr++;
		पूर्णांक opsize;

		चयन (opcode) अणु
		हाल TCPOPT_EOL:
			वापस;
		हाल TCPOPT_NOP:	/* Ref: RFC 793 section 3.1 */
			length--;
			जारी;
		शेष:
			अगर (length < 2)
				वापस;
			opsize = *ptr++;
			अगर (opsize < 2) /* "silly options" */
				वापस;
			अगर (opsize > length)
				वापस;	/* करोn't parse partial options */
			अगर (opcode == TCPOPT_MPTCP)
				mptcp_parse_option(skb, ptr, opsize, mp_opt);
			ptr += opsize - 2;
			length -= opsize;
		पूर्ण
	पूर्ण
पूर्ण

bool mptcp_syn_options(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक *size, काष्ठा mptcp_out_options *opts)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);

	/* we will use snd_isn to detect first pkt [re]transmission
	 * in mptcp_established_options_mp()
	 */
	subflow->snd_isn = TCP_SKB_CB(skb)->end_seq;
	अगर (subflow->request_mptcp) अणु
		opts->suboptions = OPTION_MPTCP_MPC_SYN;
		*size = TCPOLEN_MPTCP_MPC_SYN;
		वापस true;
	पूर्ण अन्यथा अगर (subflow->request_join) अणु
		pr_debug("remote_token=%u, nonce=%u", subflow->remote_token,
			 subflow->local_nonce);
		opts->suboptions = OPTION_MPTCP_MPJ_SYN;
		opts->join_id = subflow->local_id;
		opts->token = subflow->remote_token;
		opts->nonce = subflow->local_nonce;
		opts->backup = subflow->request_bkup;
		*size = TCPOLEN_MPTCP_MPJ_SYN;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* MP_JOIN client subflow must रुको क्रम 4th ack beक्रमe sending any data:
 * TCP can't schedule delack समयr beक्रमe the subflow is fully established.
 * MPTCP uses the delack समयr to करो 3rd ack retransmissions
 */
अटल व्योम schedule_3rdack_retransmission(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित दीर्घ समयout;

	/* reschedule with a समयout above RTT, as we must look only क्रम drop */
	अगर (tp->srtt_us)
		समयout = tp->srtt_us << 1;
	अन्यथा
		समयout = TCP_TIMEOUT_INIT;

	WARN_ON_ONCE(icsk->icsk_ack.pending & ICSK_ACK_TIMER);
	icsk->icsk_ack.pending |= ICSK_ACK_SCHED | ICSK_ACK_TIMER;
	icsk->icsk_ack.समयout = समयout;
	sk_reset_समयr(sk, &icsk->icsk_delack_समयr, समयout);
पूर्ण

अटल व्योम clear_3rdack_retransmission(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	sk_stop_समयr(sk, &icsk->icsk_delack_समयr);
	icsk->icsk_ack.समयout = 0;
	icsk->icsk_ack.ato = 0;
	icsk->icsk_ack.pending &= ~(ICSK_ACK_SCHED | ICSK_ACK_TIMER);
पूर्ण

अटल bool mptcp_established_options_mp(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					 bool snd_data_fin_enable,
					 अचिन्हित पूर्णांक *size,
					 अचिन्हित पूर्णांक reमुख्यing,
					 काष्ठा mptcp_out_options *opts)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_ext *mpext;
	अचिन्हित पूर्णांक data_len;

	/* When skb is not available, we better over-estimate the emitted
	 * options len. A full DSS option (28 bytes) is दीर्घer than
	 * TCPOLEN_MPTCP_MPC_ACK_DATA(22) or TCPOLEN_MPTCP_MPJ_ACK(24), so
	 * tell the caller to defer the estimate to
	 * mptcp_established_options_dss(), which will reserve enough space.
	 */
	अगर (!skb)
		वापस false;

	/* MPC/MPJ needed only on 3rd ack packet, DATA_FIN and TCP shutकरोwn take precedence */
	अगर (subflow->fully_established || snd_data_fin_enable ||
	    subflow->snd_isn != TCP_SKB_CB(skb)->seq ||
	    sk->sk_state != TCP_ESTABLISHED)
		वापस false;

	अगर (subflow->mp_capable) अणु
		mpext = mptcp_get_ext(skb);
		data_len = mpext ? mpext->data_len : 0;

		/* we will check ext_copy.data_len in mptcp_ग_लिखो_options() to
		 * discriminate between TCPOLEN_MPTCP_MPC_ACK_DATA and
		 * TCPOLEN_MPTCP_MPC_ACK
		 */
		opts->ext_copy.data_len = data_len;
		opts->suboptions = OPTION_MPTCP_MPC_ACK;
		opts->sndr_key = subflow->local_key;
		opts->rcvr_key = subflow->remote_key;

		/* Section 3.1.
		 * The MP_CAPABLE option is carried on the SYN, SYN/ACK, and ACK
		 * packets that start the first subflow of an MPTCP connection,
		 * as well as the first packet that carries data
		 */
		अगर (data_len > 0)
			*size = ALIGN(TCPOLEN_MPTCP_MPC_ACK_DATA, 4);
		अन्यथा
			*size = TCPOLEN_MPTCP_MPC_ACK;

		pr_debug("subflow=%p, local_key=%llu, remote_key=%llu map_len=%d",
			 subflow, subflow->local_key, subflow->remote_key,
			 data_len);

		वापस true;
	पूर्ण अन्यथा अगर (subflow->mp_join) अणु
		opts->suboptions = OPTION_MPTCP_MPJ_ACK;
		स_नकल(opts->hmac, subflow->hmac, MPTCPOPT_HMAC_LEN);
		*size = TCPOLEN_MPTCP_MPJ_ACK;
		pr_debug("subflow=%p", subflow);

		schedule_3rdack_retransmission(sk);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम mptcp_ग_लिखो_data_fin(काष्ठा mptcp_subflow_context *subflow,
				 काष्ठा sk_buff *skb, काष्ठा mptcp_ext *ext)
अणु
	/* The ग_लिखो_seq value has alपढ़ोy been incremented, so the actual
	 * sequence number क्रम the DATA_FIN is one less.
	 */
	u64 data_fin_tx_seq = READ_ONCE(mptcp_sk(subflow->conn)->ग_लिखो_seq) - 1;

	अगर (!ext->use_map || !skb->len) अणु
		/* RFC6824 requires a DSS mapping with specअगरic values
		 * अगर DATA_FIN is set but no data payload is mapped
		 */
		ext->data_fin = 1;
		ext->use_map = 1;
		ext->dsn64 = 1;
		ext->data_seq = data_fin_tx_seq;
		ext->subflow_seq = 0;
		ext->data_len = 1;
	पूर्ण अन्यथा अगर (ext->data_seq + ext->data_len == data_fin_tx_seq) अणु
		/* If there's an existing DSS mapping and it is the
		 * final mapping, DATA_FIN consumes 1 additional byte of
		 * mapping space.
		 */
		ext->data_fin = 1;
		ext->data_len++;
	पूर्ण
पूर्ण

अटल bool mptcp_established_options_dss(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					  bool snd_data_fin_enable,
					  अचिन्हित पूर्णांक *size,
					  अचिन्हित पूर्णांक reमुख्यing,
					  काष्ठा mptcp_out_options *opts)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);
	अचिन्हित पूर्णांक dss_size = 0;
	काष्ठा mptcp_ext *mpext;
	अचिन्हित पूर्णांक ack_size;
	bool ret = false;
	u64 ack_seq;

	mpext = skb ? mptcp_get_ext(skb) : शून्य;

	अगर (!skb || (mpext && mpext->use_map) || snd_data_fin_enable) अणु
		अचिन्हित पूर्णांक map_size;

		map_size = TCPOLEN_MPTCP_DSS_BASE + TCPOLEN_MPTCP_DSS_MAP64;

		reमुख्यing -= map_size;
		dss_size = map_size;
		अगर (mpext)
			opts->ext_copy = *mpext;

		अगर (skb && snd_data_fin_enable)
			mptcp_ग_लिखो_data_fin(subflow, skb, &opts->ext_copy);
		ret = true;
	पूर्ण

	/* passive sockets msk will set the 'can_ack' after accept(), even
	 * अगर the first subflow may have the alपढ़ोy the remote key handy
	 */
	opts->ext_copy.use_ack = 0;
	अगर (!READ_ONCE(msk->can_ack)) अणु
		*size = ALIGN(dss_size, 4);
		वापस ret;
	पूर्ण

	ack_seq = READ_ONCE(msk->ack_seq);
	अगर (READ_ONCE(msk->use_64bit_ack)) अणु
		ack_size = TCPOLEN_MPTCP_DSS_ACK64;
		opts->ext_copy.data_ack = ack_seq;
		opts->ext_copy.ack64 = 1;
	पूर्ण अन्यथा अणु
		ack_size = TCPOLEN_MPTCP_DSS_ACK32;
		opts->ext_copy.data_ack32 = (uपूर्णांक32_t)ack_seq;
		opts->ext_copy.ack64 = 0;
	पूर्ण
	opts->ext_copy.use_ack = 1;
	WRITE_ONCE(msk->old_wspace, __mptcp_space((काष्ठा sock *)msk));

	/* Add kind/length/subtype/flag overhead अगर mapping is not populated */
	अगर (dss_size == 0)
		ack_size += TCPOLEN_MPTCP_DSS_BASE;

	dss_size += ack_size;

	*size = ALIGN(dss_size, 4);
	वापस true;
पूर्ण

अटल u64 add_addr_generate_hmac(u64 key1, u64 key2,
				  काष्ठा mptcp_addr_info *addr)
अणु
	u16 port = ntohs(addr->port);
	u8 hmac[SHA256_DIGEST_SIZE];
	u8 msg[19];
	पूर्णांक i = 0;

	msg[i++] = addr->id;
	अगर (addr->family == AF_INET) अणु
		स_नकल(&msg[i], &addr->addr.s_addr, 4);
		i += 4;
	पूर्ण
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अन्यथा अगर (addr->family == AF_INET6) अणु
		स_नकल(&msg[i], &addr->addr6.s6_addr, 16);
		i += 16;
	पूर्ण
#पूर्ण_अगर
	msg[i++] = port >> 8;
	msg[i++] = port & 0xFF;

	mptcp_crypto_hmac_sha(key1, key2, msg, i, hmac);

	वापस get_unaligned_be64(&hmac[SHA256_DIGEST_SIZE - माप(u64)]);
पूर्ण

अटल bool mptcp_established_options_add_addr(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					       अचिन्हित पूर्णांक *size,
					       अचिन्हित पूर्णांक reमुख्यing,
					       काष्ठा mptcp_out_options *opts)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);
	bool drop_other_suboptions = false;
	अचिन्हित पूर्णांक opt_size = *size;
	bool echo;
	bool port;
	पूर्णांक len;

	अगर ((mptcp_pm_should_add_संकेत_ipv6(msk) ||
	     mptcp_pm_should_add_संकेत_port(msk) ||
	     mptcp_pm_should_add_संकेत_echo(msk)) &&
	    skb && skb_is_tcp_pure_ack(skb)) अणु
		pr_debug("drop other suboptions");
		opts->suboptions = 0;
		opts->ext_copy.use_ack = 0;
		opts->ext_copy.use_map = 0;
		reमुख्यing += opt_size;
		drop_other_suboptions = true;
	पूर्ण

	अगर (!mptcp_pm_should_add_संकेत(msk) ||
	    !(mptcp_pm_add_addr_संकेत(msk, reमुख्यing, &opts->addr, &echo, &port)))
		वापस false;

	len = mptcp_add_addr_len(opts->addr.family, echo, port);
	अगर (reमुख्यing < len)
		वापस false;

	*size = len;
	अगर (drop_other_suboptions)
		*size -= opt_size;
	opts->suboptions |= OPTION_MPTCP_ADD_ADDR;
	अगर (!echo) अणु
		opts->ahmac = add_addr_generate_hmac(msk->local_key,
						     msk->remote_key,
						     &opts->addr);
	पूर्ण
	pr_debug("addr_id=%d, ahmac=%llu, echo=%d, port=%d",
		 opts->addr.id, opts->ahmac, echo, ntohs(opts->addr.port));

	वापस true;
पूर्ण

अटल bool mptcp_established_options_rm_addr(काष्ठा sock *sk,
					      अचिन्हित पूर्णांक *size,
					      अचिन्हित पूर्णांक reमुख्यing,
					      काष्ठा mptcp_out_options *opts)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);
	काष्ठा mptcp_rm_list rm_list;
	पूर्णांक i, len;

	अगर (!mptcp_pm_should_rm_संकेत(msk) ||
	    !(mptcp_pm_rm_addr_संकेत(msk, reमुख्यing, &rm_list)))
		वापस false;

	len = mptcp_rm_addr_len(&rm_list);
	अगर (len < 0)
		वापस false;
	अगर (reमुख्यing < len)
		वापस false;

	*size = len;
	opts->suboptions |= OPTION_MPTCP_RM_ADDR;
	opts->rm_list = rm_list;

	क्रम (i = 0; i < opts->rm_list.nr; i++)
		pr_debug("rm_list_ids[%d]=%d", i, opts->rm_list.ids[i]);

	वापस true;
पूर्ण

अटल bool mptcp_established_options_mp_prio(काष्ठा sock *sk,
					      अचिन्हित पूर्णांक *size,
					      अचिन्हित पूर्णांक reमुख्यing,
					      काष्ठा mptcp_out_options *opts)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);

	अगर (!subflow->send_mp_prio)
		वापस false;

	/* account क्रम the trailing 'nop' option */
	अगर (reमुख्यing < TCPOLEN_MPTCP_PRIO_ALIGN)
		वापस false;

	*size = TCPOLEN_MPTCP_PRIO_ALIGN;
	opts->suboptions |= OPTION_MPTCP_PRIO;
	opts->backup = subflow->request_bkup;

	pr_debug("prio=%d", opts->backup);

	वापस true;
पूर्ण

अटल noअंतरभूत व्योम mptcp_established_options_rst(काष्ठा sock *sk, काष्ठा sk_buff *skb,
						   अचिन्हित पूर्णांक *size,
						   अचिन्हित पूर्णांक reमुख्यing,
						   काष्ठा mptcp_out_options *opts)
अणु
	स्थिर काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);

	अगर (reमुख्यing < TCPOLEN_MPTCP_RST)
		वापस;

	*size = TCPOLEN_MPTCP_RST;
	opts->suboptions |= OPTION_MPTCP_RST;
	opts->reset_transient = subflow->reset_transient;
	opts->reset_reason = subflow->reset_reason;
पूर्ण

bool mptcp_established_options(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			       अचिन्हित पूर्णांक *size, अचिन्हित पूर्णांक reमुख्यing,
			       काष्ठा mptcp_out_options *opts)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);
	अचिन्हित पूर्णांक opt_size = 0;
	bool snd_data_fin;
	bool ret = false;

	opts->suboptions = 0;

	अगर (unlikely(__mptcp_check_fallback(msk)))
		वापस false;

	अगर (unlikely(skb && TCP_SKB_CB(skb)->tcp_flags & TCPHDR_RST)) अणु
		mptcp_established_options_rst(sk, skb, size, reमुख्यing, opts);
		वापस true;
	पूर्ण

	snd_data_fin = mptcp_data_fin_enabled(msk);
	अगर (mptcp_established_options_mp(sk, skb, snd_data_fin, &opt_size, reमुख्यing, opts))
		ret = true;
	अन्यथा अगर (mptcp_established_options_dss(sk, skb, snd_data_fin, &opt_size, reमुख्यing, opts))
		ret = true;

	/* we reserved enough space क्रम the above options, and exceeding the
	 * TCP option space would be fatal
	 */
	अगर (WARN_ON_ONCE(opt_size > reमुख्यing))
		वापस false;

	*size += opt_size;
	reमुख्यing -= opt_size;
	अगर (mptcp_established_options_add_addr(sk, skb, &opt_size, reमुख्यing, opts)) अणु
		*size += opt_size;
		reमुख्यing -= opt_size;
		ret = true;
	पूर्ण अन्यथा अगर (mptcp_established_options_rm_addr(sk, &opt_size, reमुख्यing, opts)) अणु
		*size += opt_size;
		reमुख्यing -= opt_size;
		ret = true;
	पूर्ण

	अगर (mptcp_established_options_mp_prio(sk, &opt_size, reमुख्यing, opts)) अणु
		*size += opt_size;
		reमुख्यing -= opt_size;
		ret = true;
	पूर्ण

	वापस ret;
पूर्ण

bool mptcp_synack_options(स्थिर काष्ठा request_sock *req, अचिन्हित पूर्णांक *size,
			  काष्ठा mptcp_out_options *opts)
अणु
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);

	अगर (subflow_req->mp_capable) अणु
		opts->suboptions = OPTION_MPTCP_MPC_SYNACK;
		opts->sndr_key = subflow_req->local_key;
		*size = TCPOLEN_MPTCP_MPC_SYNACK;
		pr_debug("subflow_req=%p, local_key=%llu",
			 subflow_req, subflow_req->local_key);
		वापस true;
	पूर्ण अन्यथा अगर (subflow_req->mp_join) अणु
		opts->suboptions = OPTION_MPTCP_MPJ_SYNACK;
		opts->backup = subflow_req->backup;
		opts->join_id = subflow_req->local_id;
		opts->thmac = subflow_req->thmac;
		opts->nonce = subflow_req->local_nonce;
		pr_debug("req=%p, bkup=%u, id=%u, thmac=%llu, nonce=%u",
			 subflow_req, opts->backup, opts->join_id,
			 opts->thmac, opts->nonce);
		*size = TCPOLEN_MPTCP_MPJ_SYNACK;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool check_fully_established(काष्ठा mptcp_sock *msk, काष्ठा sock *ssk,
				    काष्ठा mptcp_subflow_context *subflow,
				    काष्ठा sk_buff *skb,
				    काष्ठा mptcp_options_received *mp_opt)
अणु
	/* here we can process OoO, in-winकरोw pkts, only in-sequence 4th ack
	 * will make the subflow fully established
	 */
	अगर (likely(subflow->fully_established)) अणु
		/* on passive sockets, check क्रम 3rd ack retransmission
		 * note that msk is always set by subflow_syn_recv_sock()
		 * क्रम mp_join subflows
		 */
		अगर (TCP_SKB_CB(skb)->seq == subflow->ssn_offset + 1 &&
		    TCP_SKB_CB(skb)->end_seq == TCP_SKB_CB(skb)->seq &&
		    subflow->mp_join && mp_opt->mp_join &&
		    READ_ONCE(msk->pm.server_side))
			tcp_send_ack(ssk);
		जाओ fully_established;
	पूर्ण

	/* we must process OoO packets beक्रमe the first subflow is fully
	 * established. OoO packets are instead a protocol violation
	 * क्रम MP_JOIN subflows as the peer must not send any data
	 * beक्रमe receiving the क्रमth ack - cfr. RFC 8684 section 3.2.
	 */
	अगर (TCP_SKB_CB(skb)->seq != subflow->ssn_offset + 1) अणु
		अगर (subflow->mp_join)
			जाओ reset;
		वापस subflow->mp_capable;
	पूर्ण

	अगर (mp_opt->dss && mp_opt->use_ack) अणु
		/* subflows are fully established as soon as we get any
		 * additional ack.
		 */
		subflow->fully_established = 1;
		WRITE_ONCE(msk->fully_established, true);
		जाओ fully_established;
	पूर्ण

	अगर (mp_opt->add_addr) अणु
		WRITE_ONCE(msk->fully_established, true);
		वापस true;
	पूर्ण

	/* If the first established packet करोes not contain MP_CAPABLE + data
	 * then fallback to TCP. Fallback scenarios requires a reset क्रम
	 * MP_JOIN subflows.
	 */
	अगर (!mp_opt->mp_capable) अणु
		अगर (subflow->mp_join)
			जाओ reset;
		subflow->mp_capable = 0;
		pr_fallback(msk);
		__mptcp_करो_fallback(msk);
		वापस false;
	पूर्ण

	अगर (unlikely(!READ_ONCE(msk->pm.server_side)))
		pr_warn_once("bogus mpc option on established client sk");
	mptcp_subflow_fully_established(subflow, mp_opt);

fully_established:
	/* अगर the subflow is not alपढ़ोy linked पूर्णांकo the conn_list, we can't
	 * notअगरy the PM: this subflow is still on the listener queue
	 * and the PM possibly acquiring the subflow lock could race with
	 * the listener बंद
	 */
	अगर (likely(subflow->pm_notअगरied) || list_empty(&subflow->node))
		वापस true;

	subflow->pm_notअगरied = 1;
	अगर (subflow->mp_join) अणु
		clear_3rdack_retransmission(ssk);
		mptcp_pm_subflow_established(msk);
	पूर्ण अन्यथा अणु
		mptcp_pm_fully_established(msk, ssk, GFP_ATOMIC);
	पूर्ण
	वापस true;

reset:
	mptcp_subflow_reset(ssk);
	वापस false;
पूर्ण

अटल u64 expand_ack(u64 old_ack, u64 cur_ack, bool use_64bit)
अणु
	u32 old_ack32, cur_ack32;

	अगर (use_64bit)
		वापस cur_ack;

	old_ack32 = (u32)old_ack;
	cur_ack32 = (u32)cur_ack;
	cur_ack = (old_ack & GENMASK_ULL(63, 32)) + cur_ack32;
	अगर (unlikely(beक्रमe(cur_ack32, old_ack32)))
		वापस cur_ack + (1LL << 32);
	वापस cur_ack;
पूर्ण

अटल व्योम ack_update_msk(काष्ठा mptcp_sock *msk,
			   काष्ठा sock *ssk,
			   काष्ठा mptcp_options_received *mp_opt)
अणु
	u64 new_wnd_end, new_snd_una, snd_nxt = READ_ONCE(msk->snd_nxt);
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	u64 old_snd_una;

	mptcp_data_lock(sk);

	/* aव्योम ack expansion on update conflict, to reduce the risk of
	 * wrongly expanding to a future ack sequence number, which is way
	 * more dangerous than missing an ack
	 */
	old_snd_una = msk->snd_una;
	new_snd_una = expand_ack(old_snd_una, mp_opt->data_ack, mp_opt->ack64);

	/* ACK क्रम data not even sent yet? Ignore. */
	अगर (after64(new_snd_una, snd_nxt))
		new_snd_una = old_snd_una;

	new_wnd_end = new_snd_una + tcp_sk(ssk)->snd_wnd;

	अगर (after64(new_wnd_end, msk->wnd_end))
		msk->wnd_end = new_wnd_end;

	/* this assumes mptcp_incoming_options() is invoked after tcp_ack() */
	अगर (after64(msk->wnd_end, READ_ONCE(msk->snd_nxt)))
		__mptcp_check_push(sk, ssk);

	अगर (after64(new_snd_una, old_snd_una)) अणु
		msk->snd_una = new_snd_una;
		__mptcp_data_acked(sk);
	पूर्ण
	mptcp_data_unlock(sk);

	trace_ack_update_msk(mp_opt->data_ack,
			     old_snd_una, new_snd_una,
			     new_wnd_end, msk->wnd_end);
पूर्ण

bool mptcp_update_rcv_data_fin(काष्ठा mptcp_sock *msk, u64 data_fin_seq, bool use_64bit)
अणु
	/* Skip अगर DATA_FIN was alपढ़ोy received.
	 * If updating simultaneously with the recvmsg loop, values
	 * should match. If they mismatch, the peer is misbehaving and
	 * we will prefer the most recent inक्रमmation.
	 */
	अगर (READ_ONCE(msk->rcv_data_fin))
		वापस false;

	WRITE_ONCE(msk->rcv_data_fin_seq,
		   expand_ack(READ_ONCE(msk->ack_seq), data_fin_seq, use_64bit));
	WRITE_ONCE(msk->rcv_data_fin, 1);

	वापस true;
पूर्ण

अटल bool add_addr_hmac_valid(काष्ठा mptcp_sock *msk,
				काष्ठा mptcp_options_received *mp_opt)
अणु
	u64 hmac = 0;

	अगर (mp_opt->echo)
		वापस true;

	hmac = add_addr_generate_hmac(msk->remote_key,
				      msk->local_key,
				      &mp_opt->addr);

	pr_debug("msk=%p, ahmac=%llu, mp_opt->ahmac=%llu\n",
		 msk, (अचिन्हित दीर्घ दीर्घ)hmac,
		 (अचिन्हित दीर्घ दीर्घ)mp_opt->ahmac);

	वापस hmac == mp_opt->ahmac;
पूर्ण

व्योम mptcp_incoming_options(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);
	काष्ठा mptcp_options_received mp_opt;
	काष्ठा mptcp_ext *mpext;

	अगर (__mptcp_check_fallback(msk)) अणु
		/* Keep it simple and unconditionally trigger send data cleanup and
		 * pending queue spooling. We will need to acquire the data lock
		 * क्रम more accurate checks, and once the lock is acquired, such
		 * helpers are cheap.
		 */
		mptcp_data_lock(subflow->conn);
		अगर (sk_stream_memory_मुक्त(sk))
			__mptcp_check_push(subflow->conn, sk);
		__mptcp_data_acked(subflow->conn);
		mptcp_data_unlock(subflow->conn);
		वापस;
	पूर्ण

	mptcp_get_options(skb, &mp_opt);
	अगर (!check_fully_established(msk, sk, subflow, skb, &mp_opt))
		वापस;

	अगर (mp_opt.fastबंद &&
	    msk->local_key == mp_opt.rcvr_key) अणु
		WRITE_ONCE(msk->rcv_fastबंद, true);
		mptcp_schedule_work((काष्ठा sock *)msk);
	पूर्ण

	अगर (mp_opt.add_addr && add_addr_hmac_valid(msk, &mp_opt)) अणु
		अगर (!mp_opt.echo) अणु
			mptcp_pm_add_addr_received(msk, &mp_opt.addr);
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_ADDADDR);
		पूर्ण अन्यथा अणु
			mptcp_pm_add_addr_echoed(msk, &mp_opt.addr);
			mptcp_pm_del_add_समयr(msk, &mp_opt.addr, true);
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_ECHOADD);
		पूर्ण

		अगर (mp_opt.addr.port)
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_PORTADD);

		mp_opt.add_addr = 0;
	पूर्ण

	अगर (mp_opt.rm_addr) अणु
		mptcp_pm_rm_addr_received(msk, &mp_opt.rm_list);
		mp_opt.rm_addr = 0;
	पूर्ण

	अगर (mp_opt.mp_prio) अणु
		mptcp_pm_mp_prio_received(sk, mp_opt.backup);
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPPRIORX);
		mp_opt.mp_prio = 0;
	पूर्ण

	अगर (mp_opt.reset) अणु
		subflow->reset_seen = 1;
		subflow->reset_reason = mp_opt.reset_reason;
		subflow->reset_transient = mp_opt.reset_transient;
	पूर्ण

	अगर (!mp_opt.dss)
		वापस;

	/* we can't रुको क्रम recvmsg() to update the ack_seq, otherwise
	 * monodirectional flows will stuck
	 */
	अगर (mp_opt.use_ack)
		ack_update_msk(msk, sk, &mp_opt);

	/* Zero-data-length packets are dropped by the caller and not
	 * propagated to the MPTCP layer, so the skb extension करोes not
	 * need to be allocated or populated. DATA_FIN inक्रमmation, अगर
	 * present, needs to be updated here beक्रमe the skb is मुक्तd.
	 */
	अगर (TCP_SKB_CB(skb)->seq == TCP_SKB_CB(skb)->end_seq) अणु
		अगर (mp_opt.data_fin && mp_opt.data_len == 1 &&
		    mptcp_update_rcv_data_fin(msk, mp_opt.data_seq, mp_opt.dsn64) &&
		    schedule_work(&msk->work))
			sock_hold(subflow->conn);

		वापस;
	पूर्ण

	mpext = skb_ext_add(skb, SKB_EXT_MPTCP);
	अगर (!mpext)
		वापस;

	स_रखो(mpext, 0, माप(*mpext));

	अगर (mp_opt.use_map) अणु
		अगर (mp_opt.mpc_map) अणु
			/* this is an MP_CAPABLE carrying MPTCP data
			 * we know this map the first chunk of data
			 */
			mptcp_crypto_key_sha(subflow->remote_key, शून्य,
					     &mpext->data_seq);
			mpext->data_seq++;
			mpext->subflow_seq = 1;
			mpext->dsn64 = 1;
			mpext->mpc_map = 1;
			mpext->data_fin = 0;
		पूर्ण अन्यथा अणु
			mpext->data_seq = mp_opt.data_seq;
			mpext->subflow_seq = mp_opt.subflow_seq;
			mpext->dsn64 = mp_opt.dsn64;
			mpext->data_fin = mp_opt.data_fin;
		पूर्ण
		mpext->data_len = mp_opt.data_len;
		mpext->use_map = 1;
	पूर्ण
पूर्ण

अटल व्योम mptcp_set_rwin(स्थिर काष्ठा tcp_sock *tp)
अणु
	स्थिर काष्ठा sock *ssk = (स्थिर काष्ठा sock *)tp;
	स्थिर काष्ठा mptcp_subflow_context *subflow;
	काष्ठा mptcp_sock *msk;
	u64 ack_seq;

	subflow = mptcp_subflow_ctx(ssk);
	msk = mptcp_sk(subflow->conn);

	ack_seq = READ_ONCE(msk->ack_seq) + tp->rcv_wnd;

	अगर (after64(ack_seq, READ_ONCE(msk->rcv_wnd_sent)))
		WRITE_ONCE(msk->rcv_wnd_sent, ack_seq);
पूर्ण

व्योम mptcp_ग_लिखो_options(__be32 *ptr, स्थिर काष्ठा tcp_sock *tp,
			 काष्ठा mptcp_out_options *opts)
अणु
	अगर ((OPTION_MPTCP_MPC_SYN | OPTION_MPTCP_MPC_SYNACK |
	     OPTION_MPTCP_MPC_ACK) & opts->suboptions) अणु
		u8 len;

		अगर (OPTION_MPTCP_MPC_SYN & opts->suboptions)
			len = TCPOLEN_MPTCP_MPC_SYN;
		अन्यथा अगर (OPTION_MPTCP_MPC_SYNACK & opts->suboptions)
			len = TCPOLEN_MPTCP_MPC_SYNACK;
		अन्यथा अगर (opts->ext_copy.data_len)
			len = TCPOLEN_MPTCP_MPC_ACK_DATA;
		अन्यथा
			len = TCPOLEN_MPTCP_MPC_ACK;

		*ptr++ = mptcp_option(MPTCPOPT_MP_CAPABLE, len,
				      MPTCP_SUPPORTED_VERSION,
				      MPTCP_CAP_HMAC_SHA256);

		अगर (!((OPTION_MPTCP_MPC_SYNACK | OPTION_MPTCP_MPC_ACK) &
		    opts->suboptions))
			जाओ mp_capable_करोne;

		put_unaligned_be64(opts->sndr_key, ptr);
		ptr += 2;
		अगर (!((OPTION_MPTCP_MPC_ACK) & opts->suboptions))
			जाओ mp_capable_करोne;

		put_unaligned_be64(opts->rcvr_key, ptr);
		ptr += 2;
		अगर (!opts->ext_copy.data_len)
			जाओ mp_capable_करोne;

		put_unaligned_be32(opts->ext_copy.data_len << 16 |
				   TCPOPT_NOP << 8 | TCPOPT_NOP, ptr);
		ptr += 1;
	पूर्ण

mp_capable_करोne:
	अगर (OPTION_MPTCP_ADD_ADDR & opts->suboptions) अणु
		u8 len = TCPOLEN_MPTCP_ADD_ADDR_BASE;
		u8 echo = MPTCP_ADDR_ECHO;

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
		अगर (opts->addr.family == AF_INET6)
			len = TCPOLEN_MPTCP_ADD_ADDR6_BASE;
#पूर्ण_अगर

		अगर (opts->addr.port)
			len += TCPOLEN_MPTCP_PORT_LEN;

		अगर (opts->ahmac) अणु
			len += माप(opts->ahmac);
			echo = 0;
		पूर्ण

		*ptr++ = mptcp_option(MPTCPOPT_ADD_ADDR,
				      len, echo, opts->addr.id);
		अगर (opts->addr.family == AF_INET) अणु
			स_नकल((u8 *)ptr, (u8 *)&opts->addr.addr.s_addr, 4);
			ptr += 1;
		पूर्ण
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
		अन्यथा अगर (opts->addr.family == AF_INET6) अणु
			स_नकल((u8 *)ptr, opts->addr.addr6.s6_addr, 16);
			ptr += 4;
		पूर्ण
#पूर्ण_अगर

		अगर (!opts->addr.port) अणु
			अगर (opts->ahmac) अणु
				put_unaligned_be64(opts->ahmac, ptr);
				ptr += 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			u16 port = ntohs(opts->addr.port);

			अगर (opts->ahmac) अणु
				u8 *bptr = (u8 *)ptr;

				put_unaligned_be16(port, bptr);
				bptr += 2;
				put_unaligned_be64(opts->ahmac, bptr);
				bptr += 8;
				put_unaligned_be16(TCPOPT_NOP << 8 |
						   TCPOPT_NOP, bptr);

				ptr += 3;
			पूर्ण अन्यथा अणु
				put_unaligned_be32(port << 16 |
						   TCPOPT_NOP << 8 |
						   TCPOPT_NOP, ptr);
				ptr += 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (OPTION_MPTCP_RM_ADDR & opts->suboptions) अणु
		u8 i = 1;

		*ptr++ = mptcp_option(MPTCPOPT_RM_ADDR,
				      TCPOLEN_MPTCP_RM_ADDR_BASE + opts->rm_list.nr,
				      0, opts->rm_list.ids[0]);

		जबतक (i < opts->rm_list.nr) अणु
			u8 id1, id2, id3, id4;

			id1 = opts->rm_list.ids[i];
			id2 = i + 1 < opts->rm_list.nr ? opts->rm_list.ids[i + 1] : TCPOPT_NOP;
			id3 = i + 2 < opts->rm_list.nr ? opts->rm_list.ids[i + 2] : TCPOPT_NOP;
			id4 = i + 3 < opts->rm_list.nr ? opts->rm_list.ids[i + 3] : TCPOPT_NOP;
			put_unaligned_be32(id1 << 24 | id2 << 16 | id3 << 8 | id4, ptr);
			ptr += 1;
			i += 4;
		पूर्ण
	पूर्ण

	अगर (OPTION_MPTCP_PRIO & opts->suboptions) अणु
		स्थिर काष्ठा sock *ssk = (स्थिर काष्ठा sock *)tp;
		काष्ठा mptcp_subflow_context *subflow;

		subflow = mptcp_subflow_ctx(ssk);
		subflow->send_mp_prio = 0;

		*ptr++ = mptcp_option(MPTCPOPT_MP_PRIO,
				      TCPOLEN_MPTCP_PRIO,
				      opts->backup, TCPOPT_NOP);
	पूर्ण

	अगर (OPTION_MPTCP_MPJ_SYN & opts->suboptions) अणु
		*ptr++ = mptcp_option(MPTCPOPT_MP_JOIN,
				      TCPOLEN_MPTCP_MPJ_SYN,
				      opts->backup, opts->join_id);
		put_unaligned_be32(opts->token, ptr);
		ptr += 1;
		put_unaligned_be32(opts->nonce, ptr);
		ptr += 1;
	पूर्ण

	अगर (OPTION_MPTCP_MPJ_SYNACK & opts->suboptions) अणु
		*ptr++ = mptcp_option(MPTCPOPT_MP_JOIN,
				      TCPOLEN_MPTCP_MPJ_SYNACK,
				      opts->backup, opts->join_id);
		put_unaligned_be64(opts->thmac, ptr);
		ptr += 2;
		put_unaligned_be32(opts->nonce, ptr);
		ptr += 1;
	पूर्ण

	अगर (OPTION_MPTCP_MPJ_ACK & opts->suboptions) अणु
		*ptr++ = mptcp_option(MPTCPOPT_MP_JOIN,
				      TCPOLEN_MPTCP_MPJ_ACK, 0, 0);
		स_नकल(ptr, opts->hmac, MPTCPOPT_HMAC_LEN);
		ptr += 5;
	पूर्ण

	अगर (OPTION_MPTCP_RST & opts->suboptions)
		*ptr++ = mptcp_option(MPTCPOPT_RST,
				      TCPOLEN_MPTCP_RST,
				      opts->reset_transient,
				      opts->reset_reason);

	अगर (opts->ext_copy.use_ack || opts->ext_copy.use_map) अणु
		काष्ठा mptcp_ext *mpext = &opts->ext_copy;
		u8 len = TCPOLEN_MPTCP_DSS_BASE;
		u8 flags = 0;

		अगर (mpext->use_ack) अणु
			flags = MPTCP_DSS_HAS_ACK;
			अगर (mpext->ack64) अणु
				len += TCPOLEN_MPTCP_DSS_ACK64;
				flags |= MPTCP_DSS_ACK64;
			पूर्ण अन्यथा अणु
				len += TCPOLEN_MPTCP_DSS_ACK32;
			पूर्ण
		पूर्ण

		अगर (mpext->use_map) अणु
			len += TCPOLEN_MPTCP_DSS_MAP64;

			/* Use only 64-bit mapping flags क्रम now, add
			 * support क्रम optional 32-bit mappings later.
			 */
			flags |= MPTCP_DSS_HAS_MAP | MPTCP_DSS_DSN64;
			अगर (mpext->data_fin)
				flags |= MPTCP_DSS_DATA_FIN;
		पूर्ण

		*ptr++ = mptcp_option(MPTCPOPT_DSS, len, 0, flags);

		अगर (mpext->use_ack) अणु
			अगर (mpext->ack64) अणु
				put_unaligned_be64(mpext->data_ack, ptr);
				ptr += 2;
			पूर्ण अन्यथा अणु
				put_unaligned_be32(mpext->data_ack32, ptr);
				ptr += 1;
			पूर्ण
		पूर्ण

		अगर (mpext->use_map) अणु
			put_unaligned_be64(mpext->data_seq, ptr);
			ptr += 2;
			put_unaligned_be32(mpext->subflow_seq, ptr);
			ptr += 1;
			put_unaligned_be32(mpext->data_len << 16 |
					   TCPOPT_NOP << 8 | TCPOPT_NOP, ptr);
		पूर्ण
	पूर्ण

	अगर (tp)
		mptcp_set_rwin(tp);
पूर्ण

__be32 mptcp_get_reset_option(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा mptcp_ext *ext = mptcp_get_ext(skb);
	u8 flags, reason;

	अगर (ext) अणु
		flags = ext->reset_transient;
		reason = ext->reset_reason;

		वापस mptcp_option(MPTCPOPT_RST, TCPOLEN_MPTCP_RST,
				    flags, reason);
	पूर्ण

	वापस htonl(0u);
पूर्ण
EXPORT_SYMBOL_GPL(mptcp_get_reset_option);
