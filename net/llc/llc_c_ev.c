<शैली गुरु>
/*
 * llc_c_ev.c - Connection component state transition event qualअगरiers
 *
 * A 'state' consists of a number of possible event matching functions,
 * the actions associated with each being executed when that event is
 * matched; a 'state machine' accepts events in a serial fashion from an
 * event queue. Each event is passed to each successive event matching
 * function until a match is made (the event matching function वापसs
 * success, or '0') or the list of event matching functions is exhausted.
 * If a match is made, the actions associated with the event are executed
 * and the state is changed to that event's transition state. Beक्रमe some
 * events are recognized, even after a match has been made, a certain
 * number of 'event qualifier' functions must also be executed. If these
 * all execute successfully, then the event is finally executed.
 *
 * These event functions must वापस 0 क्रम success, to show a matched
 * event, of 1 अगर the event करोes not match. Event qualअगरier functions
 * must वापस a 0 क्रम success or a non-zero क्रम failure. Each function
 * is simply responsible क्रम verअगरying one single thing and वापसing
 * either a success or failure.
 *
 * All of followed event functions are described in 802.2 LLC Protocol
 * standard करोcument except two functions that we added that will explain
 * in their comments, at below.
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 * 		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
#समावेश <linux/netdevice.h>
#समावेश <net/llc_conn.h>
#समावेश <net/llc_sap.h>
#समावेश <net/sock.h>
#समावेश <net/llc_c_ac.h>
#समावेश <net/llc_c_ev.h>
#समावेश <net/llc_pdu.h>

#अगर 1
#घोषणा dprपूर्णांकk(args...) prपूर्णांकk(KERN_DEBUG args)
#अन्यथा
#घोषणा dprपूर्णांकk(args...)
#पूर्ण_अगर

/**
 *	llc_util_ns_inside_rx_winकरोw - check अगर sequence number is in rx winकरोw
 *	@ns: sequence number of received pdu.
 *	@vr: sequence number which receiver expects to receive.
 *	@rw: receive winकरोw size of receiver.
 *
 *	Checks अगर sequence number of received PDU is in range of receive
 *	winकरोw. Returns 0 क्रम success, 1 otherwise
 */
अटल u16 llc_util_ns_inside_rx_winकरोw(u8 ns, u8 vr, u8 rw)
अणु
	वापस !llc_circular_between(vr, ns,
				     (vr + rw - 1) % LLC_2_SEQ_NBR_MODULO);
पूर्ण

/**
 *	llc_util_nr_inside_tx_winकरोw - check अगर sequence number is in tx winकरोw
 *	@sk: current connection.
 *	@nr: N(R) of received PDU.
 *
 *	This routine checks अगर N(R) of received PDU is in range of transmit
 *	winकरोw; on the other hand checks अगर received PDU acknowledges some
 *	outstanding PDUs that are in transmit winकरोw. Returns 0 क्रम success, 1
 *	otherwise.
 */
अटल u16 llc_util_nr_inside_tx_winकरोw(काष्ठा sock *sk, u8 nr)
अणु
	u8 nr1, nr2;
	काष्ठा sk_buff *skb;
	काष्ठा llc_pdu_sn *pdu;
	काष्ठा llc_sock *llc = llc_sk(sk);
	पूर्णांक rc = 0;

	अगर (llc->dev->flags & IFF_LOOPBACK)
		जाओ out;
	rc = 1;
	अगर (skb_queue_empty(&llc->pdu_unack_q))
		जाओ out;
	skb = skb_peek(&llc->pdu_unack_q);
	pdu = llc_pdu_sn_hdr(skb);
	nr1 = LLC_I_GET_NS(pdu);
	skb = skb_peek_tail(&llc->pdu_unack_q);
	pdu = llc_pdu_sn_hdr(skb);
	nr2 = LLC_I_GET_NS(pdu);
	rc = !llc_circular_between(nr1, nr, (nr2 + 1) % LLC_2_SEQ_NBR_MODULO);
out:
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ev_conn_req(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->prim == LLC_CONN_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_data_req(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->prim == LLC_DATA_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_disc_req(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->prim == LLC_DISC_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rst_req(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->prim == LLC_RESET_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_local_busy_detected(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->type == LLC_CONN_EV_TYPE_SIMPLE &&
	       ev->prim_type == LLC_CONN_EV_LOCAL_BUSY_DETECTED ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_local_busy_cleared(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->type == LLC_CONN_EV_TYPE_SIMPLE &&
	       ev->prim_type == LLC_CONN_EV_LOCAL_BUSY_CLEARED ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_bad_pdu(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_disc_cmd_pbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_CMD(pdu) == LLC_2_PDU_CMD_DISC ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_dm_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_RSP(pdu) == LLC_2_PDU_RSP_DM ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_frmr_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_RSP(pdu) == LLC_2_PDU_RSP_FRMR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस llc_conn_space(sk, skb) &&
	       LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_0(pdu) &&
	       LLC_I_GET_NS(pdu) == llc_sk(sk)->vR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस llc_conn_space(sk, skb) &&
	       LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_1(pdu) &&
	       LLC_I_GET_NS(pdu) == llc_sk(sk)->vR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	स्थिर u8 vr = llc_sk(sk)->vR;
	स्थिर u8 ns = LLC_I_GET_NS(pdu);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_0(pdu) && ns != vr &&
	       !llc_util_ns_inside_rx_winकरोw(ns, vr, llc_sk(sk)->rw) ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_1_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	स्थिर u8 vr = llc_sk(sk)->vR;
	स्थिर u8 ns = LLC_I_GET_NS(pdu);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_1(pdu) && ns != vr &&
	       !llc_util_ns_inside_rx_winकरोw(ns, vr, llc_sk(sk)->rw) ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_x_inval_ns(काष्ठा sock *sk,
					     काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn * pdu = llc_pdu_sn_hdr(skb);
	स्थिर u8 vr = llc_sk(sk)->vR;
	स्थिर u8 ns = LLC_I_GET_NS(pdu);
	स्थिर u16 rc = LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
		ns != vr &&
		 llc_util_ns_inside_rx_winकरोw(ns, vr, llc_sk(sk)->rw) ? 0 : 1;
	अगर (!rc)
		dprपूर्णांकk("%s: matched, state=%d, ns=%d, vr=%d\n",
			__func__, llc_sk(sk)->state, ns, vr);
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस llc_conn_space(sk, skb) &&
	       LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_0(pdu) &&
	       LLC_I_GET_NS(pdu) == llc_sk(sk)->vR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_1(pdu) &&
	       LLC_I_GET_NS(pdu) == llc_sk(sk)->vR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस llc_conn_space(sk, skb) &&
	       LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_GET_NS(pdu) == llc_sk(sk)->vR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_0_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	स्थिर u8 vr = llc_sk(sk)->vR;
	स्थिर u8 ns = LLC_I_GET_NS(pdu);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_0(pdu) && ns != vr &&
	       !llc_util_ns_inside_rx_winकरोw(ns, vr, llc_sk(sk)->rw) ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_1_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	स्थिर u8 vr = llc_sk(sk)->vR;
	स्थिर u8 ns = LLC_I_GET_NS(pdu);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_1(pdu) && ns != vr &&
	       !llc_util_ns_inside_rx_winकरोw(ns, vr, llc_sk(sk)->rw) ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_x_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	स्थिर u8 vr = llc_sk(sk)->vR;
	स्थिर u8 ns = LLC_I_GET_NS(pdu);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_I(pdu) && ns != vr &&
	       !llc_util_ns_inside_rx_winकरोw(ns, vr, llc_sk(sk)->rw) ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_x_inval_ns(काष्ठा sock *sk,
					     काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	स्थिर u8 vr = llc_sk(sk)->vR;
	स्थिर u8 ns = LLC_I_GET_NS(pdu);
	स्थिर u16 rc = LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
		ns != vr &&
		 llc_util_ns_inside_rx_winकरोw(ns, vr, llc_sk(sk)->rw) ? 0 : 1;
	अगर (!rc)
		dprपूर्णांकk("%s: matched, state=%d, ns=%d, vr=%d\n",
			__func__, llc_sk(sk)->state, ns, vr);
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ev_rx_rej_cmd_pbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_0(pdu) &&
	       LLC_S_PDU_CMD(pdu) == LLC_2_PDU_CMD_REJ ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rej_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_1(pdu) &&
	       LLC_S_PDU_CMD(pdu) == LLC_2_PDU_CMD_REJ ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rej_rsp_fbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_0(pdu) &&
	       LLC_S_PDU_RSP(pdu) == LLC_2_PDU_RSP_REJ ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rej_rsp_fbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_1(pdu) &&
	       LLC_S_PDU_RSP(pdu) == LLC_2_PDU_RSP_REJ ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rej_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PDU_RSP(pdu) == LLC_2_PDU_RSP_REJ ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rnr_cmd_pbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_0(pdu) &&
	       LLC_S_PDU_CMD(pdu) == LLC_2_PDU_CMD_RNR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rnr_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_1(pdu) &&
	       LLC_S_PDU_CMD(pdu) == LLC_2_PDU_CMD_RNR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rnr_rsp_fbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_0(pdu) &&
	       LLC_S_PDU_RSP(pdu) == LLC_2_PDU_RSP_RNR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rnr_rsp_fbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_1(pdu) &&
	       LLC_S_PDU_RSP(pdu) == LLC_2_PDU_RSP_RNR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rr_cmd_pbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_0(pdu) &&
	       LLC_S_PDU_CMD(pdu) == LLC_2_PDU_CMD_RR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rr_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_1(pdu) &&
	       LLC_S_PDU_CMD(pdu) == LLC_2_PDU_CMD_RR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rr_rsp_fbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस llc_conn_space(sk, skb) &&
	       LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_0(pdu) &&
	       LLC_S_PDU_RSP(pdu) == LLC_2_PDU_RSP_RR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_rr_rsp_fbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	वापस llc_conn_space(sk, skb) &&
	       LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_1(pdu) &&
	       LLC_S_PDU_RSP(pdu) == LLC_2_PDU_RSP_RR ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_sabme_cmd_pbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_CMD(pdu) == LLC_2_PDU_CMD_SABME ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_ua_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_RSP(pdu) == LLC_2_PDU_RSP_UA ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_rx_xxx_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u16 rc = 1;
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	अगर (LLC_PDU_IS_CMD(pdu)) अणु
		अगर (LLC_PDU_TYPE_IS_I(pdu) || LLC_PDU_TYPE_IS_S(pdu)) अणु
			अगर (LLC_I_PF_IS_1(pdu))
				rc = 0;
		पूर्ण अन्यथा अगर (LLC_PDU_TYPE_IS_U(pdu) && LLC_U_PF_IS_1(pdu))
			rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ev_rx_xxx_cmd_pbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u16 rc = 1;
	स्थिर काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	अगर (LLC_PDU_IS_CMD(pdu)) अणु
		अगर (LLC_PDU_TYPE_IS_I(pdu) || LLC_PDU_TYPE_IS_S(pdu))
			rc = 0;
		अन्यथा अगर (LLC_PDU_TYPE_IS_U(pdu))
			चयन (LLC_U_PDU_CMD(pdu)) अणु
			हाल LLC_2_PDU_CMD_SABME:
			हाल LLC_2_PDU_CMD_DISC:
				rc = 0;
				अवरोध;
			पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ev_rx_xxx_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u16 rc = 1;
	स्थिर काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	अगर (LLC_PDU_IS_RSP(pdu)) अणु
		अगर (LLC_PDU_TYPE_IS_I(pdu) || LLC_PDU_TYPE_IS_S(pdu))
			rc = 0;
		अन्यथा अगर (LLC_PDU_TYPE_IS_U(pdu))
			चयन (LLC_U_PDU_RSP(pdu)) अणु
			हाल LLC_2_PDU_RSP_UA:
			हाल LLC_2_PDU_RSP_DM:
			हाल LLC_2_PDU_RSP_FRMR:
				rc = 0;
				अवरोध;
			पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक llc_conn_ev_rx_zzz_cmd_pbit_set_x_inval_nr(काष्ठा sock *sk,
					       काष्ठा sk_buff *skb)
अणु
	u16 rc = 1;
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	स्थिर u8 vs = llc_sk(sk)->vS;
	स्थिर u8 nr = LLC_I_GET_NR(pdu);

	अगर (LLC_PDU_IS_CMD(pdu) &&
	    (LLC_PDU_TYPE_IS_I(pdu) || LLC_PDU_TYPE_IS_S(pdu)) &&
	    nr != vs && llc_util_nr_inside_tx_winकरोw(sk, nr)) अणु
		dprपूर्णांकk("%s: matched, state=%d, vs=%d, nr=%d\n",
			__func__, llc_sk(sk)->state, vs, nr);
		rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ev_rx_zzz_rsp_fbit_set_x_inval_nr(काष्ठा sock *sk,
					       काष्ठा sk_buff *skb)
अणु
	u16 rc = 1;
	स्थिर काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	स्थिर u8 vs = llc_sk(sk)->vS;
	स्थिर u8 nr = LLC_I_GET_NR(pdu);

	अगर (LLC_PDU_IS_RSP(pdu) &&
	    (LLC_PDU_TYPE_IS_I(pdu) || LLC_PDU_TYPE_IS_S(pdu)) &&
	    nr != vs && llc_util_nr_inside_tx_winकरोw(sk, nr)) अणु
		rc = 0;
		dprपूर्णांकk("%s: matched, state=%d, vs=%d, nr=%d\n",
			__func__, llc_sk(sk)->state, vs, nr);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ev_rx_any_frame(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ev_p_पंचांगr_exp(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->type != LLC_CONN_EV_TYPE_P_TMR;
पूर्ण

पूर्णांक llc_conn_ev_ack_पंचांगr_exp(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->type != LLC_CONN_EV_TYPE_ACK_TMR;
पूर्ण

पूर्णांक llc_conn_ev_rej_पंचांगr_exp(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->type != LLC_CONN_EV_TYPE_REJ_TMR;
पूर्ण

पूर्णांक llc_conn_ev_busy_पंचांगr_exp(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->type != LLC_CONN_EV_TYPE_BUSY_TMR;
पूर्ण

पूर्णांक llc_conn_ev_init_p_f_cycle(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस 1;
पूर्ण

पूर्णांक llc_conn_ev_tx_buffer_full(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	वापस ev->type == LLC_CONN_EV_TYPE_SIMPLE &&
	       ev->prim_type == LLC_CONN_EV_TX_BUFF_FULL ? 0 : 1;
पूर्ण

/* Event qualअगरier functions
 *
 * these functions simply verअगरy the value of a state flag associated with
 * the connection and वापस either a 0 क्रम success or a non-zero value
 * क्रम not-success; verअगरy the event is the type we expect
 */
पूर्णांक llc_conn_ev_qlfy_data_flag_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस llc_sk(sk)->data_flag != 1;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_data_flag_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस llc_sk(sk)->data_flag;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_data_flag_eq_2(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस llc_sk(sk)->data_flag != 2;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_p_flag_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस llc_sk(sk)->p_flag != 1;
पूर्ण

/**
 *	llc_conn_ev_qlfy_last_frame_eq_1 - checks अगर frame is last in tx winकरोw
 *	@sk: current connection काष्ठाure.
 *	@skb: current event.
 *
 *	This function determines when frame which is sent, is last frame of
 *	transmit winकरोw, अगर it is then this function वापस zero अन्यथा वापस
 *	one.  This function is used क्रम sending last frame of transmit winकरोw
 *	as I-क्रमmat command with p-bit set to one. Returns 0 अगर frame is last
 *	frame, 1 otherwise.
 */
पूर्णांक llc_conn_ev_qlfy_last_frame_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस !(skb_queue_len(&llc_sk(sk)->pdu_unack_q) + 1 == llc_sk(sk)->k);
पूर्ण

/**
 *	llc_conn_ev_qlfy_last_frame_eq_0 - checks अगर frame isn't last in tx winकरोw
 *	@sk: current connection काष्ठाure.
 *	@skb: current event.
 *
 *	This function determines when frame which is sent, isn't last frame of
 *	transmit winकरोw, अगर it isn't then this function वापस zero अन्यथा वापस
 *	one. Returns 0 अगर frame isn't last frame, 1 otherwise.
 */
पूर्णांक llc_conn_ev_qlfy_last_frame_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस skb_queue_len(&llc_sk(sk)->pdu_unack_q) + 1 == llc_sk(sk)->k;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_p_flag_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस llc_sk(sk)->p_flag;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_p_flag_eq_f(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u8 f_bit;

	llc_pdu_decode_pf_bit(skb, &f_bit);
	वापस llc_sk(sk)->p_flag == f_bit ? 0 : 1;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_remote_busy_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस llc_sk(sk)->remote_busy_flag;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_remote_busy_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस !llc_sk(sk)->remote_busy_flag;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_retry_cnt_lt_n2(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस !(llc_sk(sk)->retry_count < llc_sk(sk)->n2);
पूर्ण

पूर्णांक llc_conn_ev_qlfy_retry_cnt_gte_n2(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस !(llc_sk(sk)->retry_count >= llc_sk(sk)->n2);
पूर्ण

पूर्णांक llc_conn_ev_qlfy_s_flag_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस !llc_sk(sk)->s_flag;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_s_flag_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस llc_sk(sk)->s_flag;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_cause_flag_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस !llc_sk(sk)->cause_flag;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_cause_flag_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस llc_sk(sk)->cause_flag;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_set_status_conn(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->status = LLC_STATUS_CONN;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_set_status_disc(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->status = LLC_STATUS_DISC;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_set_status_failed(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->status = LLC_STATUS_FAILED;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_set_status_remote_busy(काष्ठा sock *sk,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->status = LLC_STATUS_REMOTE_BUSY;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_set_status_refuse(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->status = LLC_STATUS_REFUSE;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_set_status_conflict(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->status = LLC_STATUS_CONFLICT;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ev_qlfy_set_status_rst_करोne(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->status = LLC_STATUS_RESET_DONE;
	वापस 0;
पूर्ण
