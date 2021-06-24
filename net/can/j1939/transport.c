<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2010-2011 EIA Electronics,
//                         Kurt Van Dijck <kurt.van.dijck@eia.be>
// Copyright (c) 2018 Protonic,
//                         Robin van der Gracht <robin@protonic.nl>
// Copyright (c) 2017-2019 Pengutronix,
//                         Marc Kleine-Budde <kernel@pengutronix.de>
// Copyright (c) 2017-2019 Pengutronix,
//                         Oleksij Rempel <kernel@pengutronix.de>

#समावेश <linux/can/skb.h>

#समावेश "j1939-priv.h"

#घोषणा J1939_XTP_TX_RETRY_LIMIT 100

#घोषणा J1939_ETP_PGN_CTL 0xc800
#घोषणा J1939_ETP_PGN_DAT 0xc700
#घोषणा J1939_TP_PGN_CTL 0xec00
#घोषणा J1939_TP_PGN_DAT 0xeb00

#घोषणा J1939_TP_CMD_RTS 0x10
#घोषणा J1939_TP_CMD_CTS 0x11
#घोषणा J1939_TP_CMD_EOMA 0x13
#घोषणा J1939_TP_CMD_BAM 0x20
#घोषणा J1939_TP_CMD_ABORT 0xff

#घोषणा J1939_ETP_CMD_RTS 0x14
#घोषणा J1939_ETP_CMD_CTS 0x15
#घोषणा J1939_ETP_CMD_DPO 0x16
#घोषणा J1939_ETP_CMD_EOMA 0x17
#घोषणा J1939_ETP_CMD_ABORT 0xff

क्रमागत j1939_xtp_पात अणु
	J1939_XTP_NO_ABORT = 0,
	J1939_XTP_ABORT_BUSY = 1,
	/* Alपढ़ोy in one or more connection managed sessions and
	 * cannot support another.
	 *
	 * EALREADY:
	 * Operation alपढ़ोy in progress
	 */

	J1939_XTP_ABORT_RESOURCE = 2,
	/* System resources were needed क्रम another task so this
	 * connection managed session was terminated.
	 *
	 * EMSGSIZE:
	 * The socket type requires that message be sent atomically,
	 * and the size of the message to be sent made this
	 * impossible.
	 */

	J1939_XTP_ABORT_TIMEOUT = 3,
	/* A समयout occurred and this is the connection पात to
	 * बंद the session.
	 *
	 * EHOSTUNREACH:
	 * The destination host cannot be reached (probably because
	 * the host is करोwn or a remote router cannot reach it).
	 */

	J1939_XTP_ABORT_GENERIC = 4,
	/* CTS messages received when data transfer is in progress
	 *
	 * EBADMSG:
	 * Not a data message
	 */

	J1939_XTP_ABORT_FAULT = 5,
	/* Maximal retransmit request limit reached
	 *
	 * ENOTRECOVERABLE:
	 * State not recoverable
	 */

	J1939_XTP_ABORT_UNEXPECTED_DATA = 6,
	/* Unexpected data transfer packet
	 *
	 * ENOTCONN:
	 * Transport endpoपूर्णांक is not connected
	 */

	J1939_XTP_ABORT_BAD_SEQ = 7,
	/* Bad sequence number (and software is not able to recover)
	 *
	 * EILSEQ:
	 * Illegal byte sequence
	 */

	J1939_XTP_ABORT_DUP_SEQ = 8,
	/* Duplicate sequence number (and software is not able to
	 * recover)
	 */

	J1939_XTP_ABORT_EDPO_UNEXPECTED = 9,
	/* Unexpected EDPO packet (ETP) or Message size > 1785 bytes
	 * (TP)
	 */

	J1939_XTP_ABORT_BAD_EDPO_PGN = 10,
	/* Unexpected EDPO PGN (PGN in EDPO is bad) */

	J1939_XTP_ABORT_EDPO_OUTOF_CTS = 11,
	/* EDPO number of packets is greater than CTS */

	J1939_XTP_ABORT_BAD_EDPO_OFFSET = 12,
	/* Bad EDPO offset */

	J1939_XTP_ABORT_OTHER_DEPRECATED = 13,
	/* Deprecated. Use 250 instead (Any other reason)  */

	J1939_XTP_ABORT_ECTS_UNXPECTED_PGN = 14,
	/* Unexpected ECTS PGN (PGN in ECTS is bad) */

	J1939_XTP_ABORT_ECTS_TOO_BIG = 15,
	/* ECTS requested packets exceeds message size */

	J1939_XTP_ABORT_OTHER = 250,
	/* Any other reason (अगर a Connection Abort reason is
	 * identअगरied that is not listed in the table use code 250)
	 */
पूर्ण;

अटल अचिन्हित पूर्णांक j1939_tp_block = 255;
अटल अचिन्हित पूर्णांक j1939_tp_packet_delay;
अटल अचिन्हित पूर्णांक j1939_tp_padding = 1;

/* helpers */
अटल स्थिर अक्षर *j1939_xtp_पात_to_str(क्रमागत j1939_xtp_पात पात)
अणु
	चयन (पात) अणु
	हाल J1939_XTP_ABORT_BUSY:
		वापस "Already in one or more connection managed sessions and cannot support another.";
	हाल J1939_XTP_ABORT_RESOURCE:
		वापस "System resources were needed for another task so this connection managed session was terminated.";
	हाल J1939_XTP_ABORT_TIMEOUT:
		वापस "A timeout occurred and this is the connection abort to close the session.";
	हाल J1939_XTP_ABORT_GENERIC:
		वापस "CTS messages received when data transfer is in progress";
	हाल J1939_XTP_ABORT_FAULT:
		वापस "Maximal retransmit request limit reached";
	हाल J1939_XTP_ABORT_UNEXPECTED_DATA:
		वापस "Unexpected data transfer packet";
	हाल J1939_XTP_ABORT_BAD_SEQ:
		वापस "Bad sequence number (and software is not able to recover)";
	हाल J1939_XTP_ABORT_DUP_SEQ:
		वापस "Duplicate sequence number (and software is not able to recover)";
	हाल J1939_XTP_ABORT_EDPO_UNEXPECTED:
		वापस "Unexpected EDPO packet (ETP) or Message size > 1785 bytes (TP)";
	हाल J1939_XTP_ABORT_BAD_EDPO_PGN:
		वापस "Unexpected EDPO PGN (PGN in EDPO is bad)";
	हाल J1939_XTP_ABORT_EDPO_OUTOF_CTS:
		वापस "EDPO number of packets is greater than CTS";
	हाल J1939_XTP_ABORT_BAD_EDPO_OFFSET:
		वापस "Bad EDPO offset";
	हाल J1939_XTP_ABORT_OTHER_DEPRECATED:
		वापस "Deprecated. Use 250 instead (Any other reason)";
	हाल J1939_XTP_ABORT_ECTS_UNXPECTED_PGN:
		वापस "Unexpected ECTS PGN (PGN in ECTS is bad)";
	हाल J1939_XTP_ABORT_ECTS_TOO_BIG:
		वापस "ECTS requested packets exceeds message size";
	हाल J1939_XTP_ABORT_OTHER:
		वापस "Any other reason (if a Connection Abort reason is identified that is not listed in the table use code 250)";
	शेष:
		वापस "<unknown>";
	पूर्ण
पूर्ण

अटल पूर्णांक j1939_xtp_पात_to_त्रुटि_सं(काष्ठा j1939_priv *priv,
				    क्रमागत j1939_xtp_पात पात)
अणु
	पूर्णांक err;

	चयन (पात) अणु
	हाल J1939_XTP_NO_ABORT:
		WARN_ON_ONCE(पात == J1939_XTP_NO_ABORT);
		err = 0;
		अवरोध;
	हाल J1939_XTP_ABORT_BUSY:
		err = EALREADY;
		अवरोध;
	हाल J1939_XTP_ABORT_RESOURCE:
		err = EMSGSIZE;
		अवरोध;
	हाल J1939_XTP_ABORT_TIMEOUT:
		err = EHOSTUNREACH;
		अवरोध;
	हाल J1939_XTP_ABORT_GENERIC:
		err = EBADMSG;
		अवरोध;
	हाल J1939_XTP_ABORT_FAULT:
		err = ENOTRECOVERABLE;
		अवरोध;
	हाल J1939_XTP_ABORT_UNEXPECTED_DATA:
		err = ENOTCONN;
		अवरोध;
	हाल J1939_XTP_ABORT_BAD_SEQ:
		err = EILSEQ;
		अवरोध;
	हाल J1939_XTP_ABORT_DUP_SEQ:
		err = EPROTO;
		अवरोध;
	हाल J1939_XTP_ABORT_EDPO_UNEXPECTED:
		err = EPROTO;
		अवरोध;
	हाल J1939_XTP_ABORT_BAD_EDPO_PGN:
		err = EPROTO;
		अवरोध;
	हाल J1939_XTP_ABORT_EDPO_OUTOF_CTS:
		err = EPROTO;
		अवरोध;
	हाल J1939_XTP_ABORT_BAD_EDPO_OFFSET:
		err = EPROTO;
		अवरोध;
	हाल J1939_XTP_ABORT_OTHER_DEPRECATED:
		err = EPROTO;
		अवरोध;
	हाल J1939_XTP_ABORT_ECTS_UNXPECTED_PGN:
		err = EPROTO;
		अवरोध;
	हाल J1939_XTP_ABORT_ECTS_TOO_BIG:
		err = EPROTO;
		अवरोध;
	हाल J1939_XTP_ABORT_OTHER:
		err = EPROTO;
		अवरोध;
	शेष:
		netdev_warn(priv->ndev, "Unknown abort code %i", पात);
		err = EPROTO;
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत व्योम j1939_session_list_lock(काष्ठा j1939_priv *priv)
अणु
	spin_lock_bh(&priv->active_session_list_lock);
पूर्ण

अटल अंतरभूत व्योम j1939_session_list_unlock(काष्ठा j1939_priv *priv)
अणु
	spin_unlock_bh(&priv->active_session_list_lock);
पूर्ण

व्योम j1939_session_get(काष्ठा j1939_session *session)
अणु
	kref_get(&session->kref);
पूर्ण

/* session completion functions */
अटल व्योम __j1939_session_drop(काष्ठा j1939_session *session)
अणु
	अगर (!session->transmission)
		वापस;

	j1939_sock_pending_del(session->sk);
	sock_put(session->sk);
पूर्ण

अटल व्योम j1939_session_destroy(काष्ठा j1939_session *session)
अणु
	अगर (session->err)
		j1939_sk_errqueue(session, J1939_ERRQUEUE_ABORT);
	अन्यथा
		j1939_sk_errqueue(session, J1939_ERRQUEUE_ACK);

	netdev_dbg(session->priv->ndev, "%s: 0x%p\n", __func__, session);

	WARN_ON_ONCE(!list_empty(&session->sk_session_queue_entry));
	WARN_ON_ONCE(!list_empty(&session->active_session_list_entry));

	skb_queue_purge(&session->skb_queue);
	__j1939_session_drop(session);
	j1939_priv_put(session->priv);
	kमुक्त(session);
पूर्ण

अटल व्योम __j1939_session_release(काष्ठा kref *kref)
अणु
	काष्ठा j1939_session *session = container_of(kref, काष्ठा j1939_session,
						     kref);

	j1939_session_destroy(session);
पूर्ण

व्योम j1939_session_put(काष्ठा j1939_session *session)
अणु
	kref_put(&session->kref, __j1939_session_release);
पूर्ण

अटल व्योम j1939_session_txसमयr_cancel(काष्ठा j1939_session *session)
अणु
	अगर (hrसमयr_cancel(&session->txसमयr))
		j1939_session_put(session);
पूर्ण

अटल व्योम j1939_session_rxसमयr_cancel(काष्ठा j1939_session *session)
अणु
	अगर (hrसमयr_cancel(&session->rxसमयr))
		j1939_session_put(session);
पूर्ण

व्योम j1939_session_समयrs_cancel(काष्ठा j1939_session *session)
अणु
	j1939_session_txसमयr_cancel(session);
	j1939_session_rxसमयr_cancel(session);
पूर्ण

अटल अंतरभूत bool j1939_cb_is_broadcast(स्थिर काष्ठा j1939_sk_buff_cb *skcb)
अणु
	वापस (!skcb->addr.dst_name && (skcb->addr.da == 0xff));
पूर्ण

अटल व्योम j1939_session_skb_drop_old(काष्ठा j1939_session *session)
अणु
	काष्ठा sk_buff *करो_skb;
	काष्ठा j1939_sk_buff_cb *करो_skcb;
	अचिन्हित पूर्णांक offset_start;
	अचिन्हित दीर्घ flags;

	अगर (skb_queue_len(&session->skb_queue) < 2)
		वापस;

	offset_start = session->pkt.tx_acked * 7;

	spin_lock_irqsave(&session->skb_queue.lock, flags);
	करो_skb = skb_peek(&session->skb_queue);
	करो_skcb = j1939_skb_to_cb(करो_skb);

	अगर ((करो_skcb->offset + करो_skb->len) < offset_start) अणु
		__skb_unlink(करो_skb, &session->skb_queue);
		/* drop ref taken in j1939_session_skb_queue() */
		skb_unref(करो_skb);

		kमुक्त_skb(करो_skb);
	पूर्ण
	spin_unlock_irqrestore(&session->skb_queue.lock, flags);
पूर्ण

व्योम j1939_session_skb_queue(काष्ठा j1939_session *session,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_priv *priv = session->priv;

	j1939_ac_fixup(priv, skb);

	अगर (j1939_address_is_unicast(skcb->addr.da) &&
	    priv->ents[skcb->addr.da].nusers)
		skcb->flags |= J1939_ECU_LOCAL_DST;

	skcb->flags |= J1939_ECU_LOCAL_SRC;

	skb_get(skb);
	skb_queue_tail(&session->skb_queue, skb);
पूर्ण

अटल काष्ठा
sk_buff *j1939_session_skb_get_by_offset(काष्ठा j1939_session *session,
					 अचिन्हित पूर्णांक offset_start)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	काष्ठा j1939_sk_buff_cb *करो_skcb;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा sk_buff *करो_skb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&session->skb_queue.lock, flags);
	skb_queue_walk(&session->skb_queue, करो_skb) अणु
		करो_skcb = j1939_skb_to_cb(करो_skb);

		अगर (offset_start >= करो_skcb->offset &&
		    offset_start < (करो_skcb->offset + करो_skb->len)) अणु
			skb = करो_skb;
		पूर्ण
	पूर्ण

	अगर (skb)
		skb_get(skb);

	spin_unlock_irqrestore(&session->skb_queue.lock, flags);

	अगर (!skb)
		netdev_dbg(priv->ndev, "%s: 0x%p: no skb found for start: %i, queue size: %i\n",
			   __func__, session, offset_start,
			   skb_queue_len(&session->skb_queue));

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *j1939_session_skb_get(काष्ठा j1939_session *session)
अणु
	अचिन्हित पूर्णांक offset_start;

	offset_start = session->pkt.dpo * 7;
	वापस j1939_session_skb_get_by_offset(session, offset_start);
पूर्ण

/* see अगर we are receiver
 * वापसs 0 क्रम broadcasts, although we will receive them
 */
अटल अंतरभूत पूर्णांक j1939_tp_im_receiver(स्थिर काष्ठा j1939_sk_buff_cb *skcb)
अणु
	वापस skcb->flags & J1939_ECU_LOCAL_DST;
पूर्ण

/* see अगर we are sender */
अटल अंतरभूत पूर्णांक j1939_tp_im_transmitter(स्थिर काष्ठा j1939_sk_buff_cb *skcb)
अणु
	वापस skcb->flags & J1939_ECU_LOCAL_SRC;
पूर्ण

/* see अगर we are involved as either receiver or transmitter */
अटल पूर्णांक j1939_tp_im_involved(स्थिर काष्ठा j1939_sk_buff_cb *skcb, bool swap)
अणु
	अगर (swap)
		वापस j1939_tp_im_receiver(skcb);
	अन्यथा
		वापस j1939_tp_im_transmitter(skcb);
पूर्ण

अटल पूर्णांक j1939_tp_im_involved_anydir(काष्ठा j1939_sk_buff_cb *skcb)
अणु
	वापस skcb->flags & (J1939_ECU_LOCAL_SRC | J1939_ECU_LOCAL_DST);
पूर्ण

/* extract pgn from flow-ctl message */
अटल अंतरभूत pgn_t j1939_xtp_ctl_to_pgn(स्थिर u8 *dat)
अणु
	pgn_t pgn;

	pgn = (dat[7] << 16) | (dat[6] << 8) | (dat[5] << 0);
	अगर (j1939_pgn_is_pdu1(pgn))
		pgn &= 0xffff00;
	वापस pgn;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक j1939_tp_ctl_to_size(स्थिर u8 *dat)
अणु
	वापस (dat[2] << 8) + (dat[1] << 0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक j1939_etp_ctl_to_packet(स्थिर u8 *dat)
अणु
	वापस (dat[4] << 16) | (dat[3] << 8) | (dat[2] << 0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक j1939_etp_ctl_to_size(स्थिर u8 *dat)
अणु
	वापस (dat[4] << 24) | (dat[3] << 16) |
		(dat[2] << 8) | (dat[1] << 0);
पूर्ण

/* find existing session:
 * reverse: swap cb's src & dst
 * there is no problem with matching broadcasts, since
 * broadcasts (no dst, no da) would never call this
 * with reverse == true
 */
अटल bool j1939_session_match(काष्ठा j1939_addr *se_addr,
				काष्ठा j1939_addr *sk_addr, bool reverse)
अणु
	अगर (se_addr->type != sk_addr->type)
		वापस false;

	अगर (reverse) अणु
		अगर (se_addr->src_name) अणु
			अगर (se_addr->src_name != sk_addr->dst_name)
				वापस false;
		पूर्ण अन्यथा अगर (se_addr->sa != sk_addr->da) अणु
			वापस false;
		पूर्ण

		अगर (se_addr->dst_name) अणु
			अगर (se_addr->dst_name != sk_addr->src_name)
				वापस false;
		पूर्ण अन्यथा अगर (se_addr->da != sk_addr->sa) अणु
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (se_addr->src_name) अणु
			अगर (se_addr->src_name != sk_addr->src_name)
				वापस false;
		पूर्ण अन्यथा अगर (se_addr->sa != sk_addr->sa) अणु
			वापस false;
		पूर्ण

		अगर (se_addr->dst_name) अणु
			अगर (se_addr->dst_name != sk_addr->dst_name)
				वापस false;
		पूर्ण अन्यथा अगर (se_addr->da != sk_addr->da) अणु
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा
j1939_session *j1939_session_get_by_addr_locked(काष्ठा j1939_priv *priv,
						काष्ठा list_head *root,
						काष्ठा j1939_addr *addr,
						bool reverse, bool transmitter)
अणु
	काष्ठा j1939_session *session;

	lockdep_निश्चित_held(&priv->active_session_list_lock);

	list_क्रम_each_entry(session, root, active_session_list_entry) अणु
		j1939_session_get(session);
		अगर (j1939_session_match(&session->skcb.addr, addr, reverse) &&
		    session->transmission == transmitter)
			वापस session;
		j1939_session_put(session);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा
j1939_session *j1939_session_get_simple(काष्ठा j1939_priv *priv,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_session *session;

	lockdep_निश्चित_held(&priv->active_session_list_lock);

	list_क्रम_each_entry(session, &priv->active_session_list,
			    active_session_list_entry) अणु
		j1939_session_get(session);
		अगर (session->skcb.addr.type == J1939_SIMPLE &&
		    session->tskey == skcb->tskey && session->sk == skb->sk)
			वापस session;
		j1939_session_put(session);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा
j1939_session *j1939_session_get_by_addr(काष्ठा j1939_priv *priv,
					 काष्ठा j1939_addr *addr,
					 bool reverse, bool transmitter)
अणु
	काष्ठा j1939_session *session;

	j1939_session_list_lock(priv);
	session = j1939_session_get_by_addr_locked(priv,
						   &priv->active_session_list,
						   addr, reverse, transmitter);
	j1939_session_list_unlock(priv);

	वापस session;
पूर्ण

अटल व्योम j1939_skbcb_swap(काष्ठा j1939_sk_buff_cb *skcb)
अणु
	u8 पंचांगp = 0;

	swap(skcb->addr.dst_name, skcb->addr.src_name);
	swap(skcb->addr.da, skcb->addr.sa);

	/* swap SRC and DST flags, leave other untouched */
	अगर (skcb->flags & J1939_ECU_LOCAL_SRC)
		पंचांगp |= J1939_ECU_LOCAL_DST;
	अगर (skcb->flags & J1939_ECU_LOCAL_DST)
		पंचांगp |= J1939_ECU_LOCAL_SRC;
	skcb->flags &= ~(J1939_ECU_LOCAL_SRC | J1939_ECU_LOCAL_DST);
	skcb->flags |= पंचांगp;
पूर्ण

अटल काष्ठा
sk_buff *j1939_tp_tx_dat_new(काष्ठा j1939_priv *priv,
			     स्थिर काष्ठा j1939_sk_buff_cb *re_skcb,
			     bool ctl,
			     bool swap_src_dst)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा j1939_sk_buff_cb *skcb;

	skb = alloc_skb(माप(काष्ठा can_frame) + माप(काष्ठा can_skb_priv),
			GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस ERR_PTR(-ENOMEM);

	skb->dev = priv->ndev;
	can_skb_reserve(skb);
	can_skb_prv(skb)->अगरindex = priv->ndev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;
	/* reserve CAN header */
	skb_reserve(skb, दुरत्व(काष्ठा can_frame, data));

	स_नकल(skb->cb, re_skcb, माप(skb->cb));
	skcb = j1939_skb_to_cb(skb);
	अगर (swap_src_dst)
		j1939_skbcb_swap(skcb);

	अगर (ctl) अणु
		अगर (skcb->addr.type == J1939_ETP)
			skcb->addr.pgn = J1939_ETP_PGN_CTL;
		अन्यथा
			skcb->addr.pgn = J1939_TP_PGN_CTL;
	पूर्ण अन्यथा अणु
		अगर (skcb->addr.type == J1939_ETP)
			skcb->addr.pgn = J1939_ETP_PGN_DAT;
		अन्यथा
			skcb->addr.pgn = J1939_TP_PGN_DAT;
	पूर्ण

	वापस skb;
पूर्ण

/* TP transmit packet functions */
अटल पूर्णांक j1939_tp_tx_dat(काष्ठा j1939_session *session,
			   स्थिर u8 *dat, पूर्णांक len)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	काष्ठा sk_buff *skb;

	skb = j1939_tp_tx_dat_new(priv, &session->skcb,
				  false, false);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	skb_put_data(skb, dat, len);
	अगर (j1939_tp_padding && len < 8)
		स_रखो(skb_put(skb, 8 - len), 0xff, 8 - len);

	वापस j1939_send_one(priv, skb);
पूर्ण

अटल पूर्णांक j1939_xtp_करो_tx_ctl(काष्ठा j1939_priv *priv,
			       स्थिर काष्ठा j1939_sk_buff_cb *re_skcb,
			       bool swap_src_dst, pgn_t pgn, स्थिर u8 *dat)
अणु
	काष्ठा sk_buff *skb;
	u8 *skdat;

	अगर (!j1939_tp_im_involved(re_skcb, swap_src_dst))
		वापस 0;

	skb = j1939_tp_tx_dat_new(priv, re_skcb, true, swap_src_dst);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	skdat = skb_put(skb, 8);
	स_नकल(skdat, dat, 5);
	skdat[5] = (pgn >> 0);
	skdat[6] = (pgn >> 8);
	skdat[7] = (pgn >> 16);

	वापस j1939_send_one(priv, skb);
पूर्ण

अटल अंतरभूत पूर्णांक j1939_tp_tx_ctl(काष्ठा j1939_session *session,
				  bool swap_src_dst, स्थिर u8 *dat)
अणु
	काष्ठा j1939_priv *priv = session->priv;

	वापस j1939_xtp_करो_tx_ctl(priv, &session->skcb,
				   swap_src_dst,
				   session->skcb.addr.pgn, dat);
पूर्ण

अटल पूर्णांक j1939_xtp_tx_पात(काष्ठा j1939_priv *priv,
			      स्थिर काष्ठा j1939_sk_buff_cb *re_skcb,
			      bool swap_src_dst,
			      क्रमागत j1939_xtp_पात err,
			      pgn_t pgn)
अणु
	u8 dat[5];

	अगर (!j1939_tp_im_involved(re_skcb, swap_src_dst))
		वापस 0;

	स_रखो(dat, 0xff, माप(dat));
	dat[0] = J1939_TP_CMD_ABORT;
	dat[1] = err;
	वापस j1939_xtp_करो_tx_ctl(priv, re_skcb, swap_src_dst, pgn, dat);
पूर्ण

व्योम j1939_tp_schedule_txसमयr(काष्ठा j1939_session *session, पूर्णांक msec)
अणु
	j1939_session_get(session);
	hrसमयr_start(&session->txसमयr, ms_to_kसमय(msec),
		      HRTIMER_MODE_REL_SOFT);
पूर्ण

अटल अंतरभूत व्योम j1939_tp_set_rxसमयout(काष्ठा j1939_session *session,
					  पूर्णांक msec)
अणु
	j1939_session_rxसमयr_cancel(session);
	j1939_session_get(session);
	hrसमयr_start(&session->rxसमयr, ms_to_kसमय(msec),
		      HRTIMER_MODE_REL_SOFT);
पूर्ण

अटल पूर्णांक j1939_session_tx_rts(काष्ठा j1939_session *session)
अणु
	u8 dat[8];
	पूर्णांक ret;

	स_रखो(dat, 0xff, माप(dat));

	dat[1] = (session->total_message_size >> 0);
	dat[2] = (session->total_message_size >> 8);
	dat[3] = session->pkt.total;

	अगर (session->skcb.addr.type == J1939_ETP) अणु
		dat[0] = J1939_ETP_CMD_RTS;
		dat[1] = (session->total_message_size >> 0);
		dat[2] = (session->total_message_size >> 8);
		dat[3] = (session->total_message_size >> 16);
		dat[4] = (session->total_message_size >> 24);
	पूर्ण अन्यथा अगर (j1939_cb_is_broadcast(&session->skcb)) अणु
		dat[0] = J1939_TP_CMD_BAM;
		/* fake cts क्रम broadcast */
		session->pkt.tx = 0;
	पूर्ण अन्यथा अणु
		dat[0] = J1939_TP_CMD_RTS;
		dat[4] = dat[3];
	पूर्ण

	अगर (dat[0] == session->last_txcmd)
		/* करोne alपढ़ोy */
		वापस 0;

	ret = j1939_tp_tx_ctl(session, false, dat);
	अगर (ret < 0)
		वापस ret;

	session->last_txcmd = dat[0];
	अगर (dat[0] == J1939_TP_CMD_BAM) अणु
		j1939_tp_schedule_txसमयr(session, 50);
		j1939_tp_set_rxसमयout(session, 250);
	पूर्ण अन्यथा अणु
		j1939_tp_set_rxसमयout(session, 1250);
	पूर्ण

	netdev_dbg(session->priv->ndev, "%s: 0x%p\n", __func__, session);

	वापस 0;
पूर्ण

अटल पूर्णांक j1939_session_tx_dpo(काष्ठा j1939_session *session)
अणु
	अचिन्हित पूर्णांक pkt;
	u8 dat[8];
	पूर्णांक ret;

	स_रखो(dat, 0xff, माप(dat));

	dat[0] = J1939_ETP_CMD_DPO;
	session->pkt.dpo = session->pkt.tx_acked;
	pkt = session->pkt.dpo;
	dat[1] = session->pkt.last - session->pkt.tx_acked;
	dat[2] = (pkt >> 0);
	dat[3] = (pkt >> 8);
	dat[4] = (pkt >> 16);

	ret = j1939_tp_tx_ctl(session, false, dat);
	अगर (ret < 0)
		वापस ret;

	session->last_txcmd = dat[0];
	j1939_tp_set_rxसमयout(session, 1250);
	session->pkt.tx = session->pkt.tx_acked;

	netdev_dbg(session->priv->ndev, "%s: 0x%p\n", __func__, session);

	वापस 0;
पूर्ण

अटल पूर्णांक j1939_session_tx_dat(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	काष्ठा j1939_sk_buff_cb *skcb;
	पूर्णांक offset, pkt_करोne, pkt_end;
	अचिन्हित पूर्णांक len, pdelay;
	काष्ठा sk_buff *se_skb;
	स्थिर u8 *tpdat;
	पूर्णांक ret = 0;
	u8 dat[8];

	se_skb = j1939_session_skb_get_by_offset(session, session->pkt.tx * 7);
	अगर (!se_skb)
		वापस -ENOBUFS;

	skcb = j1939_skb_to_cb(se_skb);
	tpdat = se_skb->data;
	ret = 0;
	pkt_करोne = 0;
	अगर (session->skcb.addr.type != J1939_ETP &&
	    j1939_cb_is_broadcast(&session->skcb))
		pkt_end = session->pkt.total;
	अन्यथा
		pkt_end = session->pkt.last;

	जबतक (session->pkt.tx < pkt_end) अणु
		dat[0] = session->pkt.tx - session->pkt.dpo + 1;
		offset = (session->pkt.tx * 7) - skcb->offset;
		len =  se_skb->len - offset;
		अगर (len > 7)
			len = 7;

		अगर (offset + len > se_skb->len) अणु
			netdev_err_once(priv->ndev,
					"%s: 0x%p: requested data outside of queued buffer: offset %i, len %i, pkt.tx: %i\n",
					__func__, session, skcb->offset, se_skb->len , session->pkt.tx);
			ret = -EOVERFLOW;
			जाओ out_मुक्त;
		पूर्ण

		अगर (!len) अणु
			ret = -ENOBUFS;
			अवरोध;
		पूर्ण

		स_नकल(&dat[1], &tpdat[offset], len);
		ret = j1939_tp_tx_dat(session, dat, len + 1);
		अगर (ret < 0) अणु
			/* ENOBUS == CAN पूर्णांकerface TX queue is full */
			अगर (ret != -ENOBUFS)
				netdev_alert(priv->ndev,
					     "%s: 0x%p: queue data error: %i\n",
					     __func__, session, ret);
			अवरोध;
		पूर्ण

		session->last_txcmd = 0xff;
		pkt_करोne++;
		session->pkt.tx++;
		pdelay = j1939_cb_is_broadcast(&session->skcb) ? 50 :
			j1939_tp_packet_delay;

		अगर (session->pkt.tx < session->pkt.total && pdelay) अणु
			j1939_tp_schedule_txसमयr(session, pdelay);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pkt_करोne)
		j1939_tp_set_rxसमयout(session, 250);

 out_मुक्त:
	अगर (ret)
		kमुक्त_skb(se_skb);
	अन्यथा
		consume_skb(se_skb);

	वापस ret;
पूर्ण

अटल पूर्णांक j1939_xtp_txnext_transmiter(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	पूर्णांक ret = 0;

	अगर (!j1939_tp_im_transmitter(&session->skcb)) अणु
		netdev_alert(priv->ndev, "%s: 0x%p: called by not transmitter!\n",
			     __func__, session);
		वापस -EINVAL;
	पूर्ण

	चयन (session->last_cmd) अणु
	हाल 0:
		ret = j1939_session_tx_rts(session);
		अवरोध;

	हाल J1939_ETP_CMD_CTS:
		अगर (session->last_txcmd != J1939_ETP_CMD_DPO) अणु
			ret = j1939_session_tx_dpo(session);
			अगर (ret)
				वापस ret;
		पूर्ण

		fallthrough;
	हाल J1939_TP_CMD_CTS:
	हाल 0xff: /* did some data */
	हाल J1939_ETP_CMD_DPO:
	हाल J1939_TP_CMD_BAM:
		ret = j1939_session_tx_dat(session);

		अवरोध;
	शेष:
		netdev_alert(priv->ndev, "%s: 0x%p: unexpected last_cmd: %x\n",
			     __func__, session, session->last_cmd);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक j1939_session_tx_cts(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	अचिन्हित पूर्णांक pkt, len;
	पूर्णांक ret;
	u8 dat[8];

	अगर (!j1939_sk_recv_match(priv, &session->skcb))
		वापस -ENOENT;

	len = session->pkt.total - session->pkt.rx;
	len = min3(len, session->pkt.block, j1939_tp_block ?: 255);
	स_रखो(dat, 0xff, माप(dat));

	अगर (session->skcb.addr.type == J1939_ETP) अणु
		pkt = session->pkt.rx + 1;
		dat[0] = J1939_ETP_CMD_CTS;
		dat[1] = len;
		dat[2] = (pkt >> 0);
		dat[3] = (pkt >> 8);
		dat[4] = (pkt >> 16);
	पूर्ण अन्यथा अणु
		dat[0] = J1939_TP_CMD_CTS;
		dat[1] = len;
		dat[2] = session->pkt.rx + 1;
	पूर्ण

	अगर (dat[0] == session->last_txcmd)
		/* करोne alपढ़ोy */
		वापस 0;

	ret = j1939_tp_tx_ctl(session, true, dat);
	अगर (ret < 0)
		वापस ret;

	अगर (len)
		/* only mark cts करोne when len is set */
		session->last_txcmd = dat[0];
	j1939_tp_set_rxसमयout(session, 1250);

	netdev_dbg(session->priv->ndev, "%s: 0x%p\n", __func__, session);

	वापस 0;
पूर्ण

अटल पूर्णांक j1939_session_tx_eoma(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	u8 dat[8];
	पूर्णांक ret;

	अगर (!j1939_sk_recv_match(priv, &session->skcb))
		वापस -ENOENT;

	स_रखो(dat, 0xff, माप(dat));

	अगर (session->skcb.addr.type == J1939_ETP) अणु
		dat[0] = J1939_ETP_CMD_EOMA;
		dat[1] = session->total_message_size >> 0;
		dat[2] = session->total_message_size >> 8;
		dat[3] = session->total_message_size >> 16;
		dat[4] = session->total_message_size >> 24;
	पूर्ण अन्यथा अणु
		dat[0] = J1939_TP_CMD_EOMA;
		dat[1] = session->total_message_size;
		dat[2] = session->total_message_size >> 8;
		dat[3] = session->pkt.total;
	पूर्ण

	अगर (dat[0] == session->last_txcmd)
		/* करोne alपढ़ोy */
		वापस 0;

	ret = j1939_tp_tx_ctl(session, true, dat);
	अगर (ret < 0)
		वापस ret;

	session->last_txcmd = dat[0];

	/* रुको क्रम the EOMA packet to come in */
	j1939_tp_set_rxसमयout(session, 1250);

	netdev_dbg(session->priv->ndev, "%p: 0x%p\n", __func__, session);

	वापस 0;
पूर्ण

अटल पूर्णांक j1939_xtp_txnext_receiver(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	पूर्णांक ret = 0;

	अगर (!j1939_tp_im_receiver(&session->skcb)) अणु
		netdev_alert(priv->ndev, "%s: 0x%p: called by not receiver!\n",
			     __func__, session);
		वापस -EINVAL;
	पूर्ण

	चयन (session->last_cmd) अणु
	हाल J1939_TP_CMD_RTS:
	हाल J1939_ETP_CMD_RTS:
		ret = j1939_session_tx_cts(session);
		अवरोध;

	हाल J1939_ETP_CMD_CTS:
	हाल J1939_TP_CMD_CTS:
	हाल 0xff: /* did some data */
	हाल J1939_ETP_CMD_DPO:
		अगर ((session->skcb.addr.type == J1939_TP &&
		     j1939_cb_is_broadcast(&session->skcb)))
			अवरोध;

		अगर (session->pkt.rx >= session->pkt.total) अणु
			ret = j1939_session_tx_eoma(session);
		पूर्ण अन्यथा अगर (session->pkt.rx >= session->pkt.last) अणु
			session->last_txcmd = 0;
			ret = j1939_session_tx_cts(session);
		पूर्ण
		अवरोध;
	शेष:
		netdev_alert(priv->ndev, "%s: 0x%p: unexpected last_cmd: %x\n",
			     __func__, session, session->last_cmd);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक j1939_simple_txnext(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	काष्ठा sk_buff *se_skb = j1939_session_skb_get(session);
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	अगर (!se_skb)
		वापस 0;

	skb = skb_clone(se_skb, GFP_ATOMIC);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	can_skb_set_owner(skb, se_skb->sk);

	j1939_tp_set_rxसमयout(session, J1939_SIMPLE_ECHO_TIMEOUT_MS);

	ret = j1939_send_one(priv, skb);
	अगर (ret)
		जाओ out_मुक्त;

	j1939_sk_errqueue(session, J1939_ERRQUEUE_SCHED);
	j1939_sk_queue_activate_next(session);

 out_मुक्त:
	अगर (ret)
		kमुक्त_skb(se_skb);
	अन्यथा
		consume_skb(se_skb);

	वापस ret;
पूर्ण

अटल bool j1939_session_deactivate_locked(काष्ठा j1939_session *session)
अणु
	bool active = false;

	lockdep_निश्चित_held(&session->priv->active_session_list_lock);

	अगर (session->state >= J1939_SESSION_ACTIVE &&
	    session->state < J1939_SESSION_ACTIVE_MAX) अणु
		active = true;

		list_del_init(&session->active_session_list_entry);
		session->state = J1939_SESSION_DONE;
		j1939_session_put(session);
	पूर्ण

	वापस active;
पूर्ण

अटल bool j1939_session_deactivate(काष्ठा j1939_session *session)
अणु
	bool active;

	j1939_session_list_lock(session->priv);
	active = j1939_session_deactivate_locked(session);
	j1939_session_list_unlock(session->priv);

	वापस active;
पूर्ण

अटल व्योम
j1939_session_deactivate_activate_next(काष्ठा j1939_session *session)
अणु
	अगर (j1939_session_deactivate(session))
		j1939_sk_queue_activate_next(session);
पूर्ण

अटल व्योम __j1939_session_cancel(काष्ठा j1939_session *session,
				 क्रमागत j1939_xtp_पात err)
अणु
	काष्ठा j1939_priv *priv = session->priv;

	WARN_ON_ONCE(!err);
	lockdep_निश्चित_held(&session->priv->active_session_list_lock);

	session->err = j1939_xtp_पात_to_त्रुटि_सं(priv, err);
	session->state = J1939_SESSION_WAITING_ABORT;
	/* करो not send पातs on incoming broadcasts */
	अगर (!j1939_cb_is_broadcast(&session->skcb)) अणु
		j1939_xtp_tx_पात(priv, &session->skcb,
				   !session->transmission,
				   err, session->skcb.addr.pgn);
	पूर्ण

	अगर (session->sk)
		j1939_sk_send_loop_पात(session->sk, session->err);
पूर्ण

अटल व्योम j1939_session_cancel(काष्ठा j1939_session *session,
				 क्रमागत j1939_xtp_पात err)
अणु
	j1939_session_list_lock(session->priv);

	अगर (session->state >= J1939_SESSION_ACTIVE &&
	    session->state < J1939_SESSION_WAITING_ABORT) अणु
		j1939_tp_set_rxसमयout(session, J1939_XTP_ABORT_TIMEOUT_MS);
		__j1939_session_cancel(session, err);
	पूर्ण

	j1939_session_list_unlock(session->priv);
पूर्ण

अटल क्रमागत hrसमयr_restart j1939_tp_txसमयr(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा j1939_session *session =
		container_of(hrसमयr, काष्ठा j1939_session, txसमयr);
	काष्ठा j1939_priv *priv = session->priv;
	पूर्णांक ret = 0;

	अगर (session->skcb.addr.type == J1939_SIMPLE) अणु
		ret = j1939_simple_txnext(session);
	पूर्ण अन्यथा अणु
		अगर (session->transmission)
			ret = j1939_xtp_txnext_transmiter(session);
		अन्यथा
			ret = j1939_xtp_txnext_receiver(session);
	पूर्ण

	चयन (ret) अणु
	हाल -ENOBUFS:
		/* Retry limit is currently arbitrary chosen */
		अगर (session->tx_retry < J1939_XTP_TX_RETRY_LIMIT) अणु
			session->tx_retry++;
			j1939_tp_schedule_txसमयr(session,
						  10 + pअक्रमom_u32_max(16));
		पूर्ण अन्यथा अणु
			netdev_alert(priv->ndev, "%s: 0x%p: tx retry count reached\n",
				     __func__, session);
			session->err = -ENETUNREACH;
			j1939_session_rxसमयr_cancel(session);
			j1939_session_deactivate_activate_next(session);
		पूर्ण
		अवरोध;
	हाल -ENETDOWN:
		/* In this हाल we should get a netdev_event(), all active
		 * sessions will be cleared by
		 * j1939_cancel_all_active_sessions(). So handle this as an
		 * error, but let j1939_cancel_all_active_sessions() करो the
		 * cleanup including propagation of the error to user space.
		 */
		अवरोध;
	हाल -EOVERFLOW:
		j1939_session_cancel(session, J1939_XTP_ABORT_ECTS_TOO_BIG);
		अवरोध;
	हाल 0:
		session->tx_retry = 0;
		अवरोध;
	शेष:
		netdev_alert(priv->ndev, "%s: 0x%p: tx aborted with unknown reason: %i\n",
			     __func__, session, ret);
		अगर (session->skcb.addr.type != J1939_SIMPLE) अणु
			j1939_session_cancel(session, J1939_XTP_ABORT_OTHER);
		पूर्ण अन्यथा अणु
			session->err = ret;
			j1939_session_rxसमयr_cancel(session);
			j1939_session_deactivate_activate_next(session);
		पूर्ण
	पूर्ण

	j1939_session_put(session);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम j1939_session_completed(काष्ठा j1939_session *session)
अणु
	काष्ठा sk_buff *skb;

	अगर (!session->transmission) अणु
		skb = j1939_session_skb_get(session);
		/* distribute among j1939 receivers */
		j1939_sk_recv(session->priv, skb);
		consume_skb(skb);
	पूर्ण

	j1939_session_deactivate_activate_next(session);
पूर्ण

अटल क्रमागत hrसमयr_restart j1939_tp_rxसमयr(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा j1939_session *session = container_of(hrसमयr,
						     काष्ठा j1939_session,
						     rxसमयr);
	काष्ठा j1939_priv *priv = session->priv;

	अगर (session->state == J1939_SESSION_WAITING_ABORT) अणु
		netdev_alert(priv->ndev, "%s: 0x%p: abort rx timeout. Force session deactivation\n",
			     __func__, session);

		j1939_session_deactivate_activate_next(session);

	पूर्ण अन्यथा अगर (session->skcb.addr.type == J1939_SIMPLE) अणु
		netdev_alert(priv->ndev, "%s: 0x%p: Timeout. Failed to send simple message.\n",
			     __func__, session);

		/* The message is probably stuck in the CAN controller and can
		 * be send as soon as CAN bus is in working state again.
		 */
		session->err = -ETIME;
		j1939_session_deactivate(session);
	पूर्ण अन्यथा अणु
		netdev_alert(priv->ndev, "%s: 0x%p: rx timeout, send abort\n",
			     __func__, session);

		j1939_session_list_lock(session->priv);
		अगर (session->state >= J1939_SESSION_ACTIVE &&
		    session->state < J1939_SESSION_ACTIVE_MAX) अणु
			j1939_session_get(session);
			hrसमयr_start(&session->rxसमयr,
				      ms_to_kसमय(J1939_XTP_ABORT_TIMEOUT_MS),
				      HRTIMER_MODE_REL_SOFT);
			__j1939_session_cancel(session, J1939_XTP_ABORT_TIMEOUT);
		पूर्ण
		j1939_session_list_unlock(session->priv);
	पूर्ण

	j1939_session_put(session);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल bool j1939_xtp_rx_cmd_bad_pgn(काष्ठा j1939_session *session,
				     स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	pgn_t pgn = j1939_xtp_ctl_to_pgn(skb->data);
	काष्ठा j1939_priv *priv = session->priv;
	क्रमागत j1939_xtp_पात पात = J1939_XTP_NO_ABORT;
	u8 cmd = skb->data[0];

	अगर (session->skcb.addr.pgn == pgn)
		वापस false;

	चयन (cmd) अणु
	हाल J1939_TP_CMD_BAM:
		पात = J1939_XTP_NO_ABORT;
		अवरोध;

	हाल J1939_ETP_CMD_RTS:
	हाल J1939_TP_CMD_RTS: /* fall through */
		पात = J1939_XTP_ABORT_BUSY;
		अवरोध;

	हाल J1939_ETP_CMD_CTS:
	हाल J1939_TP_CMD_CTS: /* fall through */
		पात = J1939_XTP_ABORT_ECTS_UNXPECTED_PGN;
		अवरोध;

	हाल J1939_ETP_CMD_DPO:
		पात = J1939_XTP_ABORT_BAD_EDPO_PGN;
		अवरोध;

	हाल J1939_ETP_CMD_EOMA:
	हाल J1939_TP_CMD_EOMA: /* fall through */
		पात = J1939_XTP_ABORT_OTHER;
		अवरोध;

	हाल J1939_ETP_CMD_ABORT: /* && J1939_TP_CMD_ABORT */
		पात = J1939_XTP_NO_ABORT;
		अवरोध;

	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	netdev_warn(priv->ndev, "%s: 0x%p: CMD 0x%02x with PGN 0x%05x for running session with different PGN 0x%05x.\n",
		    __func__, session, cmd, pgn, session->skcb.addr.pgn);
	अगर (पात != J1939_XTP_NO_ABORT)
		j1939_xtp_tx_पात(priv, skcb, true, पात, pgn);

	वापस true;
पूर्ण

अटल व्योम j1939_xtp_rx_पात_one(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb,
				   bool reverse, bool transmitter)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_session *session;
	u8 पात = skb->data[1];

	session = j1939_session_get_by_addr(priv, &skcb->addr, reverse,
					    transmitter);
	अगर (!session)
		वापस;

	अगर (j1939_xtp_rx_cmd_bad_pgn(session, skb))
		जाओ पात_put;

	netdev_info(priv->ndev, "%s: 0x%p: 0x%05x: (%u) %s\n", __func__,
		    session, j1939_xtp_ctl_to_pgn(skb->data), पात,
		    j1939_xtp_पात_to_str(पात));

	j1939_session_समयrs_cancel(session);
	session->err = j1939_xtp_पात_to_त्रुटि_सं(priv, पात);
	अगर (session->sk)
		j1939_sk_send_loop_पात(session->sk, session->err);
	j1939_session_deactivate_activate_next(session);

पात_put:
	j1939_session_put(session);
पूर्ण

/* पात packets may come in 2 directions */
अटल व्योम
j1939_xtp_rx_पात(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb,
		   bool transmitter)
अणु
	j1939_xtp_rx_पात_one(priv, skb, false, transmitter);
	j1939_xtp_rx_पात_one(priv, skb, true, transmitter);
पूर्ण

अटल व्योम
j1939_xtp_rx_eoma_one(काष्ठा j1939_session *session, काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	स्थिर u8 *dat;
	पूर्णांक len;

	अगर (j1939_xtp_rx_cmd_bad_pgn(session, skb))
		वापस;

	dat = skb->data;

	अगर (skcb->addr.type == J1939_ETP)
		len = j1939_etp_ctl_to_size(dat);
	अन्यथा
		len = j1939_tp_ctl_to_size(dat);

	अगर (session->total_message_size != len) अणु
		netdev_warn_once(session->priv->ndev,
				 "%s: 0x%p: Incorrect size. Expected: %i; got: %i.\n",
				 __func__, session, session->total_message_size,
				 len);
	पूर्ण

	netdev_dbg(session->priv->ndev, "%s: 0x%p\n", __func__, session);

	session->pkt.tx_acked = session->pkt.total;
	j1939_session_समयrs_cancel(session);
	/* transmitted without problems */
	j1939_session_completed(session);
पूर्ण

अटल व्योम
j1939_xtp_rx_eoma(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb,
		  bool transmitter)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_session *session;

	session = j1939_session_get_by_addr(priv, &skcb->addr, true,
					    transmitter);
	अगर (!session)
		वापस;

	j1939_xtp_rx_eoma_one(session, skb);
	j1939_session_put(session);
पूर्ण

अटल व्योम
j1939_xtp_rx_cts_one(काष्ठा j1939_session *session, काष्ठा sk_buff *skb)
अणु
	क्रमागत j1939_xtp_पात err = J1939_XTP_ABORT_FAULT;
	अचिन्हित पूर्णांक pkt;
	स्थिर u8 *dat;

	dat = skb->data;

	अगर (j1939_xtp_rx_cmd_bad_pgn(session, skb))
		वापस;

	netdev_dbg(session->priv->ndev, "%s: 0x%p\n", __func__, session);

	अगर (session->last_cmd == dat[0]) अणु
		err = J1939_XTP_ABORT_DUP_SEQ;
		जाओ out_session_cancel;
	पूर्ण

	अगर (session->skcb.addr.type == J1939_ETP)
		pkt = j1939_etp_ctl_to_packet(dat);
	अन्यथा
		pkt = dat[2];

	अगर (!pkt)
		जाओ out_session_cancel;
	अन्यथा अगर (dat[1] > session->pkt.block /* 0xff क्रम etp */)
		जाओ out_session_cancel;

	/* set packet counters only when not CTS(0) */
	session->pkt.tx_acked = pkt - 1;
	j1939_session_skb_drop_old(session);
	session->pkt.last = session->pkt.tx_acked + dat[1];
	अगर (session->pkt.last > session->pkt.total)
		/* safety measure */
		session->pkt.last = session->pkt.total;
	/* TODO: करो not set tx here, करो it in txसमयr */
	session->pkt.tx = session->pkt.tx_acked;

	session->last_cmd = dat[0];
	अगर (dat[1]) अणु
		j1939_tp_set_rxसमयout(session, 1250);
		अगर (session->transmission) अणु
			अगर (session->pkt.tx_acked)
				j1939_sk_errqueue(session,
						  J1939_ERRQUEUE_SCHED);
			j1939_session_txसमयr_cancel(session);
			j1939_tp_schedule_txसमयr(session, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* CTS(0) */
		j1939_tp_set_rxसमयout(session, 550);
	पूर्ण
	वापस;

 out_session_cancel:
	j1939_session_समयrs_cancel(session);
	j1939_session_cancel(session, err);
पूर्ण

अटल व्योम
j1939_xtp_rx_cts(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb, bool transmitter)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_session *session;

	session = j1939_session_get_by_addr(priv, &skcb->addr, true,
					    transmitter);
	अगर (!session)
		वापस;
	j1939_xtp_rx_cts_one(session, skb);
	j1939_session_put(session);
पूर्ण

अटल काष्ठा j1939_session *j1939_session_new(काष्ठा j1939_priv *priv,
					       काष्ठा sk_buff *skb, माप_प्रकार size)
अणु
	काष्ठा j1939_session *session;
	काष्ठा j1939_sk_buff_cb *skcb;

	session = kzalloc(माप(*session), gfp_any());
	अगर (!session)
		वापस शून्य;

	INIT_LIST_HEAD(&session->active_session_list_entry);
	INIT_LIST_HEAD(&session->sk_session_queue_entry);
	kref_init(&session->kref);

	j1939_priv_get(priv);
	session->priv = priv;
	session->total_message_size = size;
	session->state = J1939_SESSION_NEW;

	skb_queue_head_init(&session->skb_queue);
	skb_queue_tail(&session->skb_queue, skb);

	skcb = j1939_skb_to_cb(skb);
	स_नकल(&session->skcb, skcb, माप(session->skcb));

	hrसमयr_init(&session->txसमयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL_SOFT);
	session->txसमयr.function = j1939_tp_txसमयr;
	hrसमयr_init(&session->rxसमयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL_SOFT);
	session->rxसमयr.function = j1939_tp_rxसमयr;

	netdev_dbg(priv->ndev, "%s: 0x%p: sa: %02x, da: %02x\n",
		   __func__, session, skcb->addr.sa, skcb->addr.da);

	वापस session;
पूर्ण

अटल काष्ठा
j1939_session *j1939_session_fresh_new(काष्ठा j1939_priv *priv,
				       पूर्णांक size,
				       स्थिर काष्ठा j1939_sk_buff_cb *rel_skcb)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा j1939_sk_buff_cb *skcb;
	काष्ठा j1939_session *session;

	skb = alloc_skb(size + माप(काष्ठा can_skb_priv), GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस शून्य;

	skb->dev = priv->ndev;
	can_skb_reserve(skb);
	can_skb_prv(skb)->अगरindex = priv->ndev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;
	skcb = j1939_skb_to_cb(skb);
	स_नकल(skcb, rel_skcb, माप(*skcb));

	session = j1939_session_new(priv, skb, size);
	अगर (!session) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	/* alloc data area */
	skb_put(skb, size);
	/* skb is recounted in j1939_session_new() */
	वापस session;
पूर्ण

पूर्णांक j1939_session_activate(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	काष्ठा j1939_session *active = शून्य;
	पूर्णांक ret = 0;

	j1939_session_list_lock(priv);
	अगर (session->skcb.addr.type != J1939_SIMPLE)
		active = j1939_session_get_by_addr_locked(priv,
							  &priv->active_session_list,
							  &session->skcb.addr, false,
							  session->transmission);
	अगर (active) अणु
		j1939_session_put(active);
		ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(session->state != J1939_SESSION_NEW);
		list_add_tail(&session->active_session_list_entry,
			      &priv->active_session_list);
		j1939_session_get(session);
		session->state = J1939_SESSION_ACTIVE;

		netdev_dbg(session->priv->ndev, "%s: 0x%p\n",
			   __func__, session);
	पूर्ण
	j1939_session_list_unlock(priv);

	वापस ret;
पूर्ण

अटल काष्ठा
j1939_session *j1939_xtp_rx_rts_session_new(काष्ठा j1939_priv *priv,
					    काष्ठा sk_buff *skb)
अणु
	क्रमागत j1939_xtp_पात पात = J1939_XTP_NO_ABORT;
	काष्ठा j1939_sk_buff_cb skcb = *j1939_skb_to_cb(skb);
	काष्ठा j1939_session *session;
	स्थिर u8 *dat;
	pgn_t pgn;
	पूर्णांक len;

	netdev_dbg(priv->ndev, "%s\n", __func__);

	dat = skb->data;
	pgn = j1939_xtp_ctl_to_pgn(dat);
	skcb.addr.pgn = pgn;

	अगर (!j1939_sk_recv_match(priv, &skcb))
		वापस शून्य;

	अगर (skcb.addr.type == J1939_ETP) अणु
		len = j1939_etp_ctl_to_size(dat);
		अगर (len > J1939_MAX_ETP_PACKET_SIZE)
			पात = J1939_XTP_ABORT_FAULT;
		अन्यथा अगर (len > priv->tp_max_packet_size)
			पात = J1939_XTP_ABORT_RESOURCE;
		अन्यथा अगर (len <= J1939_MAX_TP_PACKET_SIZE)
			पात = J1939_XTP_ABORT_FAULT;
	पूर्ण अन्यथा अणु
		len = j1939_tp_ctl_to_size(dat);
		अगर (len > J1939_MAX_TP_PACKET_SIZE)
			पात = J1939_XTP_ABORT_FAULT;
		अन्यथा अगर (len > priv->tp_max_packet_size)
			पात = J1939_XTP_ABORT_RESOURCE;
	पूर्ण

	अगर (पात != J1939_XTP_NO_ABORT) अणु
		j1939_xtp_tx_पात(priv, &skcb, true, पात, pgn);
		वापस शून्य;
	पूर्ण

	session = j1939_session_fresh_new(priv, len, &skcb);
	अगर (!session) अणु
		j1939_xtp_tx_पात(priv, &skcb, true,
				   J1939_XTP_ABORT_RESOURCE, pgn);
		वापस शून्य;
	पूर्ण

	/* initialize the control buffer: plain copy */
	session->pkt.total = (len + 6) / 7;
	session->pkt.block = 0xff;
	अगर (skcb.addr.type != J1939_ETP) अणु
		अगर (dat[3] != session->pkt.total)
			netdev_alert(priv->ndev, "%s: 0x%p: strange total, %u != %u\n",
				     __func__, session, session->pkt.total,
				     dat[3]);
		session->pkt.total = dat[3];
		session->pkt.block = min(dat[3], dat[4]);
	पूर्ण

	session->pkt.rx = 0;
	session->pkt.tx = 0;

	WARN_ON_ONCE(j1939_session_activate(session));

	वापस session;
पूर्ण

अटल पूर्णांक j1939_xtp_rx_rts_session_active(काष्ठा j1939_session *session,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_priv *priv = session->priv;

	अगर (!session->transmission) अणु
		अगर (j1939_xtp_rx_cmd_bad_pgn(session, skb))
			वापस -EBUSY;

		/* RTS on active session */
		j1939_session_समयrs_cancel(session);
		j1939_session_cancel(session, J1939_XTP_ABORT_BUSY);
	पूर्ण

	अगर (session->last_cmd != 0) अणु
		/* we received a second rts on the same connection */
		netdev_alert(priv->ndev, "%s: 0x%p: connection exists (%02x %02x). last cmd: %x\n",
			     __func__, session, skcb->addr.sa, skcb->addr.da,
			     session->last_cmd);

		j1939_session_समयrs_cancel(session);
		j1939_session_cancel(session, J1939_XTP_ABORT_BUSY);

		वापस -EBUSY;
	पूर्ण

	अगर (session->skcb.addr.sa != skcb->addr.sa ||
	    session->skcb.addr.da != skcb->addr.da)
		netdev_warn(priv->ndev, "%s: 0x%p: session->skcb.addr.sa=0x%02x skcb->addr.sa=0x%02x session->skcb.addr.da=0x%02x skcb->addr.da=0x%02x\n",
			    __func__, session,
			    session->skcb.addr.sa, skcb->addr.sa,
			    session->skcb.addr.da, skcb->addr.da);
	/* make sure 'sa' & 'da' are correct !
	 * They may be 'not filled in yet' क्रम sending
	 * skb's, since they did not pass the Address Claim ever.
	 */
	session->skcb.addr.sa = skcb->addr.sa;
	session->skcb.addr.da = skcb->addr.da;

	netdev_dbg(session->priv->ndev, "%s: 0x%p\n", __func__, session);

	वापस 0;
पूर्ण

अटल व्योम j1939_xtp_rx_rts(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb,
			     bool transmitter)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_session *session;
	u8 cmd = skb->data[0];

	session = j1939_session_get_by_addr(priv, &skcb->addr, false,
					    transmitter);

	अगर (!session) अणु
		अगर (transmitter) अणु
			/* If we're the transmitter and this function is called,
			 * we received our own RTS. A session has alपढ़ोy been
			 * created.
			 *
			 * For some reasons however it might have been destroyed
			 * alपढ़ोy. So करोn't create a new one here (using
			 * "j1939_xtp_rx_rts_session_new()") as this will be a
			 * receiver session.
			 *
			 * The reasons the session is alपढ़ोy destroyed might
			 * be:
			 * - user space बंदd socket was and the session was
			 *   पातed
			 * - session was पातed due to बाह्यal पात message
			 */
			वापस;
		पूर्ण
		session = j1939_xtp_rx_rts_session_new(priv, skb);
		अगर (!session) अणु
			अगर (cmd == J1939_TP_CMD_BAM && j1939_sk_recv_match(priv, skcb))
				netdev_info(priv->ndev, "%s: failed to create TP BAM session\n",
					    __func__);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (j1939_xtp_rx_rts_session_active(session, skb)) अणु
			j1939_session_put(session);
			वापस;
		पूर्ण
	पूर्ण
	session->last_cmd = cmd;

	अगर (cmd == J1939_TP_CMD_BAM) अणु
		अगर (!session->transmission)
			j1939_tp_set_rxसमयout(session, 750);
	पूर्ण अन्यथा अणु
		अगर (!session->transmission) अणु
			j1939_session_txसमयr_cancel(session);
			j1939_tp_schedule_txसमयr(session, 0);
		पूर्ण
		j1939_tp_set_rxसमयout(session, 1250);
	पूर्ण

	j1939_session_put(session);
पूर्ण

अटल व्योम j1939_xtp_rx_dpo_one(काष्ठा j1939_session *session,
				 काष्ठा sk_buff *skb)
अणु
	स्थिर u8 *dat = skb->data;

	अगर (j1939_xtp_rx_cmd_bad_pgn(session, skb))
		वापस;

	netdev_dbg(session->priv->ndev, "%s: 0x%p\n", __func__, session);

	/* transmitted without problems */
	session->pkt.dpo = j1939_etp_ctl_to_packet(skb->data);
	session->last_cmd = dat[0];
	j1939_tp_set_rxसमयout(session, 750);
पूर्ण

अटल व्योम j1939_xtp_rx_dpo(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb,
			     bool transmitter)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_session *session;

	session = j1939_session_get_by_addr(priv, &skcb->addr, false,
					    transmitter);
	अगर (!session) अणु
		netdev_info(priv->ndev,
			    "%s: no connection found\n", __func__);
		वापस;
	पूर्ण

	j1939_xtp_rx_dpo_one(session, skb);
	j1939_session_put(session);
पूर्ण

अटल व्योम j1939_xtp_rx_dat_one(काष्ठा j1939_session *session,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	काष्ठा j1939_sk_buff_cb *skcb;
	काष्ठा sk_buff *se_skb = शून्य;
	स्थिर u8 *dat;
	u8 *tpdat;
	पूर्णांक offset;
	पूर्णांक nbytes;
	bool final = false;
	bool reमुख्य = false;
	bool करो_cts_eoma = false;
	पूर्णांक packet;

	skcb = j1939_skb_to_cb(skb);
	dat = skb->data;
	अगर (skb->len <= 1)
		/* makes no sense */
		जाओ out_session_cancel;

	चयन (session->last_cmd) अणु
	हाल 0xff:
		अवरोध;
	हाल J1939_ETP_CMD_DPO:
		अगर (skcb->addr.type == J1939_ETP)
			अवरोध;
		fallthrough;
	हाल J1939_TP_CMD_BAM:
	हाल J1939_TP_CMD_CTS: /* fall through */
		अगर (skcb->addr.type != J1939_ETP)
			अवरोध;
		fallthrough;
	शेष:
		netdev_info(priv->ndev, "%s: 0x%p: last %02x\n", __func__,
			    session, session->last_cmd);
		जाओ out_session_cancel;
	पूर्ण

	packet = (dat[0] - 1 + session->pkt.dpo);
	अगर (packet > session->pkt.total ||
	    (session->pkt.rx + 1) > session->pkt.total) अणु
		netdev_info(priv->ndev, "%s: 0x%p: should have been completed\n",
			    __func__, session);
		जाओ out_session_cancel;
	पूर्ण

	se_skb = j1939_session_skb_get_by_offset(session, packet * 7);
	अगर (!se_skb) अणु
		netdev_warn(priv->ndev, "%s: 0x%p: no skb found\n", __func__,
			    session);
		जाओ out_session_cancel;
	पूर्ण

	skcb = j1939_skb_to_cb(se_skb);
	offset = packet * 7 - skcb->offset;
	nbytes = se_skb->len - offset;
	अगर (nbytes > 7)
		nbytes = 7;
	अगर (nbytes <= 0 || (nbytes + 1) > skb->len) अणु
		netdev_info(priv->ndev, "%s: 0x%p: nbytes %i, len %i\n",
			    __func__, session, nbytes, skb->len);
		जाओ out_session_cancel;
	पूर्ण

	tpdat = se_skb->data;
	अगर (!session->transmission) अणु
		स_नकल(&tpdat[offset], &dat[1], nbytes);
	पूर्ण अन्यथा अणु
		पूर्णांक err;

		err = स_भेद(&tpdat[offset], &dat[1], nbytes);
		अगर (err)
			netdev_err_once(priv->ndev,
					"%s: 0x%p: Data of RX-looped back packet (%*ph) doesn't match TX data (%*ph)!\n",
					__func__, session,
					nbytes, &dat[1],
					nbytes, &tpdat[offset]);
	पूर्ण

	अगर (packet == session->pkt.rx)
		session->pkt.rx++;

	अगर (skcb->addr.type != J1939_ETP &&
	    j1939_cb_is_broadcast(&session->skcb)) अणु
		अगर (session->pkt.rx >= session->pkt.total)
			final = true;
		अन्यथा
			reमुख्य = true;
	पूर्ण अन्यथा अणु
		/* never final, an EOMA must follow */
		अगर (session->pkt.rx >= session->pkt.last)
			करो_cts_eoma = true;
	पूर्ण

	अगर (final) अणु
		j1939_session_समयrs_cancel(session);
		j1939_session_completed(session);
	पूर्ण अन्यथा अगर (reमुख्य) अणु
		अगर (!session->transmission)
			j1939_tp_set_rxसमयout(session, 750);
	पूर्ण अन्यथा अगर (करो_cts_eoma) अणु
		j1939_tp_set_rxसमयout(session, 1250);
		अगर (!session->transmission)
			j1939_tp_schedule_txसमयr(session, 0);
	पूर्ण अन्यथा अणु
		j1939_tp_set_rxसमयout(session, 250);
	पूर्ण
	session->last_cmd = 0xff;
	consume_skb(se_skb);
	j1939_session_put(session);

	वापस;

 out_session_cancel:
	kमुक्त_skb(se_skb);
	j1939_session_समयrs_cancel(session);
	j1939_session_cancel(session, J1939_XTP_ABORT_FAULT);
	j1939_session_put(session);
पूर्ण

अटल व्योम j1939_xtp_rx_dat(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb;
	काष्ठा j1939_session *session;

	skcb = j1939_skb_to_cb(skb);

	अगर (j1939_tp_im_transmitter(skcb)) अणु
		session = j1939_session_get_by_addr(priv, &skcb->addr, false,
						    true);
		अगर (!session)
			netdev_info(priv->ndev, "%s: no tx connection found\n",
				    __func__);
		अन्यथा
			j1939_xtp_rx_dat_one(session, skb);
	पूर्ण

	अगर (j1939_tp_im_receiver(skcb)) अणु
		session = j1939_session_get_by_addr(priv, &skcb->addr, false,
						    false);
		अगर (!session)
			netdev_info(priv->ndev, "%s: no rx connection found\n",
				    __func__);
		अन्यथा
			j1939_xtp_rx_dat_one(session, skb);
	पूर्ण

	अगर (j1939_cb_is_broadcast(skcb)) अणु
		session = j1939_session_get_by_addr(priv, &skcb->addr, false,
						    false);
		अगर (session)
			j1939_xtp_rx_dat_one(session, skb);
	पूर्ण
पूर्ण

/* j1939 मुख्य पूर्णांकf */
काष्ठा j1939_session *j1939_tp_send(काष्ठा j1939_priv *priv,
				    काष्ठा sk_buff *skb, माप_प्रकार size)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_session *session;
	पूर्णांक ret;

	अगर (skcb->addr.pgn == J1939_TP_PGN_DAT ||
	    skcb->addr.pgn == J1939_TP_PGN_CTL ||
	    skcb->addr.pgn == J1939_ETP_PGN_DAT ||
	    skcb->addr.pgn == J1939_ETP_PGN_CTL)
		/* aव्योम conflict */
		वापस ERR_PTR(-गलत_तर्क);

	अगर (size > priv->tp_max_packet_size)
		वापस ERR_PTR(-EMSGSIZE);

	अगर (size <= 8)
		skcb->addr.type = J1939_SIMPLE;
	अन्यथा अगर (size > J1939_MAX_TP_PACKET_SIZE)
		skcb->addr.type = J1939_ETP;
	अन्यथा
		skcb->addr.type = J1939_TP;

	अगर (skcb->addr.type == J1939_ETP &&
	    j1939_cb_is_broadcast(skcb))
		वापस ERR_PTR(-EDESTADDRREQ);

	/* fill in addresses from names */
	ret = j1939_ac_fixup(priv, skb);
	अगर (unlikely(ret))
		वापस ERR_PTR(ret);

	/* fix DST flags, it may be used there soon */
	अगर (j1939_address_is_unicast(skcb->addr.da) &&
	    priv->ents[skcb->addr.da].nusers)
		skcb->flags |= J1939_ECU_LOCAL_DST;

	/* src is always local, I'm sending ... */
	skcb->flags |= J1939_ECU_LOCAL_SRC;

	/* prepare new session */
	session = j1939_session_new(priv, skb, size);
	अगर (!session)
		वापस ERR_PTR(-ENOMEM);

	/* skb is recounted in j1939_session_new() */
	sock_hold(skb->sk);
	session->sk = skb->sk;
	session->transmission = true;
	session->pkt.total = (size + 6) / 7;
	session->pkt.block = skcb->addr.type == J1939_ETP ? 255 :
		min(j1939_tp_block ?: 255, session->pkt.total);

	अगर (j1939_cb_is_broadcast(&session->skcb))
		/* set the end-packet क्रम broadcast */
		session->pkt.last = session->pkt.total;

	skcb->tskey = session->sk->sk_tskey++;
	session->tskey = skcb->tskey;

	वापस session;
पूर्ण

अटल व्योम j1939_tp_cmd_recv(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	पूर्णांक extd = J1939_TP;
	u8 cmd = skb->data[0];

	चयन (cmd) अणु
	हाल J1939_ETP_CMD_RTS:
		extd = J1939_ETP;
		fallthrough;
	हाल J1939_TP_CMD_BAM:
	हाल J1939_TP_CMD_RTS: /* fall through */
		अगर (skcb->addr.type != extd)
			वापस;

		अगर (cmd == J1939_TP_CMD_RTS && j1939_cb_is_broadcast(skcb)) अणु
			netdev_alert(priv->ndev, "%s: rts without destination (%02x)\n",
				     __func__, skcb->addr.sa);
			वापस;
		पूर्ण

		अगर (j1939_tp_im_transmitter(skcb))
			j1939_xtp_rx_rts(priv, skb, true);

		अगर (j1939_tp_im_receiver(skcb) || j1939_cb_is_broadcast(skcb))
			j1939_xtp_rx_rts(priv, skb, false);

		अवरोध;

	हाल J1939_ETP_CMD_CTS:
		extd = J1939_ETP;
		fallthrough;
	हाल J1939_TP_CMD_CTS:
		अगर (skcb->addr.type != extd)
			वापस;

		अगर (j1939_tp_im_transmitter(skcb))
			j1939_xtp_rx_cts(priv, skb, false);

		अगर (j1939_tp_im_receiver(skcb))
			j1939_xtp_rx_cts(priv, skb, true);

		अवरोध;

	हाल J1939_ETP_CMD_DPO:
		अगर (skcb->addr.type != J1939_ETP)
			वापस;

		अगर (j1939_tp_im_transmitter(skcb))
			j1939_xtp_rx_dpo(priv, skb, true);

		अगर (j1939_tp_im_receiver(skcb))
			j1939_xtp_rx_dpo(priv, skb, false);

		अवरोध;

	हाल J1939_ETP_CMD_EOMA:
		extd = J1939_ETP;
		fallthrough;
	हाल J1939_TP_CMD_EOMA:
		अगर (skcb->addr.type != extd)
			वापस;

		अगर (j1939_tp_im_transmitter(skcb))
			j1939_xtp_rx_eoma(priv, skb, false);

		अगर (j1939_tp_im_receiver(skcb))
			j1939_xtp_rx_eoma(priv, skb, true);

		अवरोध;

	हाल J1939_ETP_CMD_ABORT: /* && J1939_TP_CMD_ABORT */
		अगर (j1939_tp_im_transmitter(skcb))
			j1939_xtp_rx_पात(priv, skb, true);

		अगर (j1939_tp_im_receiver(skcb))
			j1939_xtp_rx_पात(priv, skb, false);

		अवरोध;
	शेष:
		वापस;
	पूर्ण
पूर्ण

पूर्णांक j1939_tp_recv(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);

	अगर (!j1939_tp_im_involved_anydir(skcb) && !j1939_cb_is_broadcast(skcb))
		वापस 0;

	चयन (skcb->addr.pgn) अणु
	हाल J1939_ETP_PGN_DAT:
		skcb->addr.type = J1939_ETP;
		fallthrough;
	हाल J1939_TP_PGN_DAT:
		j1939_xtp_rx_dat(priv, skb);
		अवरोध;

	हाल J1939_ETP_PGN_CTL:
		skcb->addr.type = J1939_ETP;
		fallthrough;
	हाल J1939_TP_PGN_CTL:
		अगर (skb->len < 8)
			वापस 0; /* Don't care. Nothing to extract here */

		j1939_tp_cmd_recv(priv, skb);
		अवरोध;
	शेष:
		वापस 0; /* no problem */
	पूर्ण
	वापस 1; /* "I processed the message" */
पूर्ण

व्योम j1939_simple_recv(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_session *session;

	अगर (!skb->sk)
		वापस;

	अगर (skb->sk->sk_family != AF_CAN ||
	    skb->sk->sk_protocol != CAN_J1939)
		वापस;

	j1939_session_list_lock(priv);
	session = j1939_session_get_simple(priv, skb);
	j1939_session_list_unlock(priv);
	अगर (!session) अणु
		netdev_warn(priv->ndev,
			    "%s: Received already invalidated message\n",
			    __func__);
		वापस;
	पूर्ण

	j1939_session_समयrs_cancel(session);
	j1939_session_deactivate(session);
	j1939_session_put(session);
पूर्ण

पूर्णांक j1939_cancel_active_session(काष्ठा j1939_priv *priv, काष्ठा sock *sk)
अणु
	काष्ठा j1939_session *session, *saved;

	netdev_dbg(priv->ndev, "%s, sk: %p\n", __func__, sk);
	j1939_session_list_lock(priv);
	list_क्रम_each_entry_safe(session, saved,
				 &priv->active_session_list,
				 active_session_list_entry) अणु
		अगर (!sk || sk == session->sk) अणु
			अगर (hrसमयr_try_to_cancel(&session->txसमयr) == 1)
				j1939_session_put(session);
			अगर (hrसमयr_try_to_cancel(&session->rxसमयr) == 1)
				j1939_session_put(session);

			session->err = ESHUTDOWN;
			j1939_session_deactivate_locked(session);
		पूर्ण
	पूर्ण
	j1939_session_list_unlock(priv);
	वापस NOTIFY_DONE;
पूर्ण

व्योम j1939_tp_init(काष्ठा j1939_priv *priv)
अणु
	spin_lock_init(&priv->active_session_list_lock);
	INIT_LIST_HEAD(&priv->active_session_list);
	priv->tp_max_packet_size = J1939_MAX_ETP_PACKET_SIZE;
पूर्ण
