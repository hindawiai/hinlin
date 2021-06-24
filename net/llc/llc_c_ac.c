<शैली गुरु>
/*
 * llc_c_ac.c - actions perक्रमmed during connection state transition.
 *
 * Description:
 *   Functions in this module are implementation of connection component actions
 *   Details of actions can be found in IEEE-802.2 standard करोcument.
 *   All functions have one connection and one event as input argument. All of
 *   them वापस 0 On success and 1 otherwise.
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
#समावेश <linux/slab.h>
#समावेश <net/llc_conn.h>
#समावेश <net/llc_sap.h>
#समावेश <net/sock.h>
#समावेश <net/llc_c_ev.h>
#समावेश <net/llc_c_ac.h>
#समावेश <net/llc_c_st.h>
#समावेश <net/llc_pdu.h>
#समावेश <net/llc.h>


अटल पूर्णांक llc_conn_ac_inc_vs_by_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
अटल व्योम llc_process_पंचांगr_ev(काष्ठा sock *sk, काष्ठा sk_buff *skb);
अटल पूर्णांक llc_conn_ac_data_confirm(काष्ठा sock *sk, काष्ठा sk_buff *ev);

अटल पूर्णांक llc_conn_ac_inc_npta_value(काष्ठा sock *sk, काष्ठा sk_buff *skb);

अटल पूर्णांक llc_conn_ac_send_rr_rsp_f_set_ackpf(काष्ठा sock *sk,
					       काष्ठा sk_buff *skb);

अटल पूर्णांक llc_conn_ac_set_p_flag_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);

#घोषणा INCORRECT 0

पूर्णांक llc_conn_ac_clear_remote_busy(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (llc->remote_busy_flag) अणु
		u8 nr;
		काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

		llc->remote_busy_flag = 0;
		del_समयr(&llc->busy_state_समयr.समयr);
		nr = LLC_I_GET_NR(pdu);
		llc_conn_resend_i_pdu_as_cmd(sk, nr, 0);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_conn_ind(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->ind_prim = LLC_CONN_PRIM;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_conn_confirm(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->cfm_prim = LLC_CONN_PRIM;
	वापस 0;
पूर्ण

अटल पूर्णांक llc_conn_ac_data_confirm(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->cfm_prim = LLC_DATA_PRIM;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_data_ind(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_conn_rtn_pdu(sk, skb);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_disc_ind(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);
	u8 reason = 0;
	पूर्णांक rc = 0;

	अगर (ev->type == LLC_CONN_EV_TYPE_PDU) अणु
		काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

		अगर (LLC_PDU_IS_RSP(pdu) &&
		    LLC_PDU_TYPE_IS_U(pdu) &&
		    LLC_U_PDU_RSP(pdu) == LLC_2_PDU_RSP_DM)
			reason = LLC_DISC_REASON_RX_DM_RSP_PDU;
		अन्यथा अगर (LLC_PDU_IS_CMD(pdu) &&
			   LLC_PDU_TYPE_IS_U(pdu) &&
			   LLC_U_PDU_CMD(pdu) == LLC_2_PDU_CMD_DISC)
			reason = LLC_DISC_REASON_RX_DISC_CMD_PDU;
	पूर्ण अन्यथा अगर (ev->type == LLC_CONN_EV_TYPE_ACK_TMR)
		reason = LLC_DISC_REASON_ACK_TMR_EXP;
	अन्यथा
		rc = -EINVAL;
	अगर (!rc) अणु
		ev->reason   = reason;
		ev->ind_prim = LLC_DISC_PRIM;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ac_disc_confirm(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->reason   = ev->status;
	ev->cfm_prim = LLC_DISC_PRIM;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_rst_ind(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u8 reason = 0;
	पूर्णांक rc = 1;
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);
	काष्ठा llc_sock *llc = llc_sk(sk);

	चयन (ev->type) अणु
	हाल LLC_CONN_EV_TYPE_PDU:
		अगर (LLC_PDU_IS_RSP(pdu) &&
		    LLC_PDU_TYPE_IS_U(pdu) &&
		    LLC_U_PDU_RSP(pdu) == LLC_2_PDU_RSP_FRMR) अणु
			reason = LLC_RESET_REASON_LOCAL;
			rc = 0;
		पूर्ण अन्यथा अगर (LLC_PDU_IS_CMD(pdu) &&
			   LLC_PDU_TYPE_IS_U(pdu) &&
			   LLC_U_PDU_CMD(pdu) == LLC_2_PDU_CMD_SABME) अणु
			reason = LLC_RESET_REASON_REMOTE;
			rc = 0;
		पूर्ण
		अवरोध;
	हाल LLC_CONN_EV_TYPE_ACK_TMR:
	हाल LLC_CONN_EV_TYPE_P_TMR:
	हाल LLC_CONN_EV_TYPE_REJ_TMR:
	हाल LLC_CONN_EV_TYPE_BUSY_TMR:
		अगर (llc->retry_count > llc->n2) अणु
			reason = LLC_RESET_REASON_LOCAL;
			rc = 0;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (!rc) अणु
		ev->reason   = reason;
		ev->ind_prim = LLC_RESET_PRIM;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ac_rst_confirm(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->reason   = 0;
	ev->cfm_prim = LLC_RESET_PRIM;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_clear_remote_busy_अगर_f_eq_1(काष्ठा sock *sk,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	अगर (LLC_PDU_IS_RSP(pdu) &&
	    LLC_PDU_TYPE_IS_I(pdu) &&
	    LLC_I_PF_IS_1(pdu) && llc_sk(sk)->ack_pf)
		llc_conn_ac_clear_remote_busy(sk, skb);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_stop_rej_पंचांगr_अगर_data_flag_eq_2(काष्ठा sock *sk,
					       काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (llc->data_flag == 2)
		del_समयr(&llc->rej_sent_समयr.समयr);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_send_disc_cmd_p_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_CMD);
		llc_pdu_init_as_disc_cmd(nskb, 1);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
		llc_conn_ac_set_p_flag_1(sk, skb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_dm_rsp_f_set_p(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;
		u8 f_bit;

		llc_pdu_decode_pf_bit(skb, &f_bit);
		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_dm_rsp(nskb, f_bit);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_dm_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_dm_rsp(nskb, 1);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_frmr_rsp_f_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u8 f_bit;
	पूर्णांक rc = -ENOBUFS;
	काष्ठा sk_buff *nskb;
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	काष्ठा llc_sock *llc = llc_sk(sk);

	llc->rx_pdu_hdr = *((u32 *)pdu);
	अगर (LLC_PDU_IS_CMD(pdu))
		llc_pdu_decode_pf_bit(skb, &f_bit);
	अन्यथा
		f_bit = 0;
	nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U,
			       माप(काष्ठा llc_frmr_info));
	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_frmr_rsp(nskb, pdu, f_bit, llc->vS,
					 llc->vR, INCORRECT);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_resend_frmr_rsp_f_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U,
					       माप(काष्ठा llc_frmr_info));

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;
		काष्ठा llc_pdu_sn *pdu = (काष्ठा llc_pdu_sn *)&llc->rx_pdu_hdr;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_frmr_rsp(nskb, pdu, 0, llc->vS,
					 llc->vR, INCORRECT);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_resend_frmr_rsp_f_set_p(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u8 f_bit;
	पूर्णांक rc = -ENOBUFS;
	काष्ठा sk_buff *nskb;
	काष्ठा llc_sock *llc = llc_sk(sk);

	llc_pdu_decode_pf_bit(skb, &f_bit);
	nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U,
			       माप(काष्ठा llc_frmr_info));
	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;
		काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_frmr_rsp(nskb, pdu, f_bit, llc->vS,
					 llc->vR, INCORRECT);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_i_cmd_p_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा llc_sap *sap = llc->sap;

	llc_pdu_header_init(skb, LLC_PDU_TYPE_I, sap->laddr.lsap,
			    llc->daddr.lsap, LLC_PDU_CMD);
	llc_pdu_init_as_i_cmd(skb, 1, llc->vS, llc->vR);
	rc = llc_mac_hdr_init(skb, llc->dev->dev_addr, llc->daddr.mac);
	अगर (likely(!rc)) अणु
		skb_get(skb);
		llc_conn_send_pdu(sk, skb);
		llc_conn_ac_inc_vs_by_1(sk, skb);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक llc_conn_ac_send_i_cmd_p_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा llc_sap *sap = llc->sap;

	llc_pdu_header_init(skb, LLC_PDU_TYPE_I, sap->laddr.lsap,
			    llc->daddr.lsap, LLC_PDU_CMD);
	llc_pdu_init_as_i_cmd(skb, 0, llc->vS, llc->vR);
	rc = llc_mac_hdr_init(skb, llc->dev->dev_addr, llc->daddr.mac);
	अगर (likely(!rc)) अणु
		skb_get(skb);
		llc_conn_send_pdu(sk, skb);
		llc_conn_ac_inc_vs_by_1(sk, skb);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ac_send_i_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा llc_sap *sap = llc->sap;

	llc_pdu_header_init(skb, LLC_PDU_TYPE_I, sap->laddr.lsap,
			    llc->daddr.lsap, LLC_PDU_CMD);
	llc_pdu_init_as_i_cmd(skb, 0, llc->vS, llc->vR);
	rc = llc_mac_hdr_init(skb, llc->dev->dev_addr, llc->daddr.mac);
	अगर (likely(!rc)) अणु
		skb_get(skb);
		llc_conn_send_pdu(sk, skb);
		llc_conn_ac_inc_vs_by_1(sk, skb);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_resend_i_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	u8 nr = LLC_I_GET_NR(pdu);

	llc_conn_resend_i_pdu_as_cmd(sk, nr, 0);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_resend_i_xxx_x_set_0_or_send_rr(काष्ठा sock *sk,
						काष्ठा sk_buff *skb)
अणु
	u8 nr;
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rr_rsp(nskb, 0, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (likely(!rc))
			llc_conn_send_pdu(sk, nskb);
		अन्यथा
			kमुक्त_skb(skb);
	पूर्ण
	अगर (rc) अणु
		nr = LLC_I_GET_NR(pdu);
		rc = 0;
		llc_conn_resend_i_pdu_as_cmd(sk, nr, 0);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक llc_conn_ac_resend_i_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	u8 nr = LLC_I_GET_NR(pdu);

	llc_conn_resend_i_pdu_as_rsp(sk, nr, 1);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_send_rej_cmd_p_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_CMD);
		llc_pdu_init_as_rej_cmd(nskb, 1, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_rej_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rej_rsp(nskb, 1, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_rej_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rej_rsp(nskb, 0, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_rnr_cmd_p_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_CMD);
		llc_pdu_init_as_rnr_cmd(nskb, 1, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_rnr_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rnr_rsp(nskb, 1, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_rnr_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rnr_rsp(nskb, 0, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_set_remote_busy(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (!llc->remote_busy_flag) अणु
		llc->remote_busy_flag = 1;
		mod_समयr(&llc->busy_state_समयr.समयr,
			 jअगरfies + llc->busy_state_समयr.expire);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_opt_send_rnr_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rnr_rsp(nskb, 0, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_rr_cmd_p_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_CMD);
		llc_pdu_init_as_rr_cmd(nskb, 1, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_rr_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;
		u8 f_bit = 1;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rr_rsp(nskb, f_bit, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_ack_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rr_rsp(nskb, 1, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_rr_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rr_rsp(nskb, 0, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_ack_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rr_rsp(nskb, 0, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

व्योम llc_conn_set_p_flag(काष्ठा sock *sk, u8 value)
अणु
	पूर्णांक state_changed = llc_sk(sk)->p_flag && !value;

	llc_sk(sk)->p_flag = value;

	अगर (state_changed)
		sk->sk_state_change(sk);
पूर्ण

पूर्णांक llc_conn_ac_send_sabme_cmd_p_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;
		u8 *dmac = llc->daddr.mac;

		अगर (llc->dev->flags & IFF_LOOPBACK)
			dmac = llc->dev->dev_addr;
		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_CMD);
		llc_pdu_init_as_sabme_cmd(nskb, 1);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, dmac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
		llc_conn_set_p_flag(sk, 1);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_send_ua_rsp_f_set_p(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u8 f_bit;
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U, 0);

	llc_pdu_decode_pf_bit(skb, &f_bit);
	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		nskb->dev = llc->dev;
		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_ua_rsp(nskb, f_bit);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

पूर्णांक llc_conn_ac_set_s_flag_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->s_flag = 0;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_s_flag_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->s_flag = 1;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_start_p_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	llc_conn_set_p_flag(sk, 1);
	mod_समयr(&llc->pf_cycle_समयr.समयr,
		  jअगरfies + llc->pf_cycle_समयr.expire);
	वापस 0;
पूर्ण

/**
 *	llc_conn_ac_send_ack_अगर_needed - check अगर ack is needed
 *	@sk: current connection काष्ठाure
 *	@skb: current event
 *
 *	Checks number of received PDUs which have not been acknowledged, yet,
 *	If number of them reaches to "npta"(Number of PDUs To Acknowledge) then
 *	sends an RR response as acknowledgement क्रम them.  Returns 0 क्रम
 *	success, 1 otherwise.
 */
पूर्णांक llc_conn_ac_send_ack_अगर_needed(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u8 pf_bit;
	काष्ठा llc_sock *llc = llc_sk(sk);

	llc_pdu_decode_pf_bit(skb, &pf_bit);
	llc->ack_pf |= pf_bit & 1;
	अगर (!llc->ack_must_be_send) अणु
		llc->first_pdu_Ns = llc->vR;
		llc->ack_must_be_send = 1;
		llc->ack_pf = pf_bit & 1;
	पूर्ण
	अगर (((llc->vR - llc->first_pdu_Ns + 1 + LLC_2_SEQ_NBR_MODULO)
			% LLC_2_SEQ_NBR_MODULO) >= llc->npta) अणु
		llc_conn_ac_send_rr_rsp_f_set_ackpf(sk, skb);
		llc->ack_must_be_send	= 0;
		llc->ack_pf		= 0;
		llc_conn_ac_inc_npta_value(sk, skb);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	llc_conn_ac_rst_sendack_flag - resets ack_must_be_send flag
 *	@sk: current connection काष्ठाure
 *	@skb: current event
 *
 *	This action resets ack_must_be_send flag of given connection, this flag
 *	indicates अगर there is any PDU which has not been acknowledged yet.
 *	Returns 0 क्रम success, 1 otherwise.
 */
पूर्णांक llc_conn_ac_rst_sendack_flag(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->ack_must_be_send = llc_sk(sk)->ack_pf = 0;
	वापस 0;
पूर्ण

/**
 *	llc_conn_ac_send_i_rsp_f_set_ackpf - acknowledge received PDUs
 *	@sk: current connection काष्ठाure
 *	@skb: current event
 *
 *	Sends an I response PDU with f-bit set to ack_pf flag as acknowledge to
 *	all received PDUs which have not been acknowledged, yet. ack_pf flag is
 *	set to one अगर one PDU with p-bit set to one is received.  Returns 0 क्रम
 *	success, 1 otherwise.
 */
अटल पूर्णांक llc_conn_ac_send_i_rsp_f_set_ackpf(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा llc_sap *sap = llc->sap;

	llc_pdu_header_init(skb, LLC_PDU_TYPE_I, sap->laddr.lsap,
			    llc->daddr.lsap, LLC_PDU_RSP);
	llc_pdu_init_as_i_cmd(skb, llc->ack_pf, llc->vS, llc->vR);
	rc = llc_mac_hdr_init(skb, llc->dev->dev_addr, llc->daddr.mac);
	अगर (likely(!rc)) अणु
		skb_get(skb);
		llc_conn_send_pdu(sk, skb);
		llc_conn_ac_inc_vs_by_1(sk, skb);
	पूर्ण
	वापस rc;
पूर्ण

/**
 *	llc_conn_ac_send_i_as_ack - sends an I-क्रमmat PDU to acknowledge rx PDUs
 *	@sk: current connection काष्ठाure.
 *	@skb: current event.
 *
 *	This action sends an I-क्रमmat PDU as acknowledge to received PDUs which
 *	have not been acknowledged, yet, अगर there is any. By using of this
 *	action number of acknowledgements decreases, this technic is called
 *	piggy backing. Returns 0 क्रम success, 1 otherwise.
 */
पूर्णांक llc_conn_ac_send_i_as_ack(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);
	पूर्णांक ret;

	अगर (llc->ack_must_be_send) अणु
		ret = llc_conn_ac_send_i_rsp_f_set_ackpf(sk, skb);
		llc->ack_must_be_send = 0 ;
		llc->ack_pf = 0;
	पूर्ण अन्यथा अणु
		ret = llc_conn_ac_send_i_cmd_p_set_0(sk, skb);
	पूर्ण

	वापस ret;
पूर्ण

/**
 *	llc_conn_ac_send_rr_rsp_f_set_ackpf - ack all rx PDUs not yet acked
 *	@sk: current connection काष्ठाure.
 *	@skb: current event.
 *
 *	This action sends an RR response with f-bit set to ack_pf flag as
 *	acknowledge to all received PDUs which have not been acknowledged, yet,
 *	अगर there is any. ack_pf flag indicates अगर a PDU has been received with
 *	p-bit set to one. Returns 0 क्रम success, 1 otherwise.
 */
अटल पूर्णांक llc_conn_ac_send_rr_rsp_f_set_ackpf(काष्ठा sock *sk,
					       काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -ENOBUFS;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	अगर (nskb) अणु
		काष्ठा llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rr_rsp(nskb, llc->ack_pf, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		अगर (unlikely(rc))
			जाओ मुक्त;
		llc_conn_send_pdu(sk, nskb);
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

/**
 *	llc_conn_ac_inc_npta_value - tries to make value of npta greater
 *	@sk: current connection काष्ठाure.
 *	@skb: current event.
 *
 *	After "inc_cntr" बार calling of this action, "npta" increase by one.
 *	this action tries to make vale of "npta" greater as possible; number of
 *	acknowledgements decreases by increasing of "npta". Returns 0 क्रम
 *	success, 1 otherwise.
 */
अटल पूर्णांक llc_conn_ac_inc_npta_value(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (!llc->inc_cntr) अणु
		llc->dec_step = 0;
		llc->dec_cntr = llc->inc_cntr = 2;
		++llc->npta;
		अगर (llc->npta > (u8) ~LLC_2_SEQ_NBR_MODULO)
			llc->npta = (u8) ~LLC_2_SEQ_NBR_MODULO;
	पूर्ण अन्यथा
		--llc->inc_cntr;
	वापस 0;
पूर्ण

/**
 *	llc_conn_ac_adjust_npta_by_rr - decreases "npta" by one
 *	@sk: current connection काष्ठाure.
 *	@skb: current event.
 *
 *	After receiving "dec_cntr" बार RR command, this action decreases
 *	"npta" by one. Returns 0 क्रम success, 1 otherwise.
 */
पूर्णांक llc_conn_ac_adjust_npta_by_rr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (!llc->connect_step && !llc->remote_busy_flag) अणु
		अगर (!llc->dec_step) अणु
			अगर (!llc->dec_cntr) अणु
				llc->inc_cntr = llc->dec_cntr = 2;
				अगर (llc->npta > 0)
					llc->npta = llc->npta - 1;
			पूर्ण अन्यथा
				llc->dec_cntr -=1;
		पूर्ण
	पूर्ण अन्यथा
		llc->connect_step = 0 ;
	वापस 0;
पूर्ण

/**
 *	llc_conn_ac_adjust_npta_by_rnr - decreases "npta" by one
 *	@sk: current connection काष्ठाure.
 *	@skb: current event.
 *
 *	After receiving "dec_cntr" बार RNR command, this action decreases
 *	"npta" by one. Returns 0 क्रम success, 1 otherwise.
 */
पूर्णांक llc_conn_ac_adjust_npta_by_rnr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (llc->remote_busy_flag)
		अगर (!llc->dec_step) अणु
			अगर (!llc->dec_cntr) अणु
				llc->inc_cntr = llc->dec_cntr = 2;
				अगर (llc->npta > 0)
					--llc->npta;
			पूर्ण अन्यथा
				--llc->dec_cntr;
		पूर्ण
	वापस 0;
पूर्ण

/**
 *	llc_conn_ac_dec_tx_win_size - decreases tx winकरोw size
 *	@sk: current connection काष्ठाure.
 *	@skb: current event.
 *
 *	After receiving of a REJ command or response, transmit winकरोw size is
 *	decreased by number of PDUs which are outstanding yet. Returns 0 क्रम
 *	success, 1 otherwise.
 */
पूर्णांक llc_conn_ac_dec_tx_win_size(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);
	u8 unacked_pdu = skb_queue_len(&llc->pdu_unack_q);

	अगर (llc->k - unacked_pdu < 1)
		llc->k = 1;
	अन्यथा
		llc->k -= unacked_pdu;
	वापस 0;
पूर्ण

/**
 *	llc_conn_ac_inc_tx_win_size - tx winकरोw size is inc by 1
 *	@sk: current connection काष्ठाure.
 *	@skb: current event.
 *
 *	After receiving an RR response with f-bit set to one, transmit winकरोw
 *	size is increased by one. Returns 0 क्रम success, 1 otherwise.
 */
पूर्णांक llc_conn_ac_inc_tx_win_size(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	llc->k += 1;
	अगर (llc->k > (u8) ~LLC_2_SEQ_NBR_MODULO)
		llc->k = (u8) ~LLC_2_SEQ_NBR_MODULO;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_stop_all_समयrs(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk_stop_all_समयrs(sk, false);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_stop_other_समयrs(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	del_समयr(&llc->rej_sent_समयr.समयr);
	del_समयr(&llc->pf_cycle_समयr.समयr);
	del_समयr(&llc->busy_state_समयr.समयr);
	llc->ack_must_be_send = 0;
	llc->ack_pf = 0;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_start_ack_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	mod_समयr(&llc->ack_समयr.समयr, jअगरfies + llc->ack_समयr.expire);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_start_rej_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	mod_समयr(&llc->rej_sent_समयr.समयr,
		  jअगरfies + llc->rej_sent_समयr.expire);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_start_ack_पंचांगr_अगर_not_running(काष्ठा sock *sk,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	अगर (!समयr_pending(&llc->ack_समयr.समयr))
		mod_समयr(&llc->ack_समयr.समयr,
			  jअगरfies + llc->ack_समयr.expire);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_stop_ack_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	del_समयr(&llc_sk(sk)->ack_समयr.समयr);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_stop_p_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(sk);

	del_समयr(&llc->pf_cycle_समयr.समयr);
	llc_conn_set_p_flag(sk, 0);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_stop_rej_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	del_समयr(&llc_sk(sk)->rej_sent_समयr.समयr);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_upd_nr_received(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक acked;
	u16 unacked = 0;
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	काष्ठा llc_sock *llc = llc_sk(sk);

	llc->last_nr = PDU_SUPV_GET_Nr(pdu);
	acked = llc_conn_हटाओ_acked_pdus(sk, llc->last_nr, &unacked);
	/* On loopback we करोn't queue I frames in unack_pdu_q queue. */
	अगर (acked > 0 || (llc->dev->flags & IFF_LOOPBACK)) अणु
		llc->retry_count = 0;
		del_समयr(&llc->ack_समयr.समयr);
		अगर (llc->failed_data_req) अणु
			/* alपढ़ोy, we did not accept data from upper layer
			 * (tx_winकरोw full or unacceptable state). Now, we
			 * can send data and must inक्रमm to upper layer.
			 */
			llc->failed_data_req = 0;
			llc_conn_ac_data_confirm(sk, skb);
		पूर्ण
		अगर (unacked)
			mod_समयr(&llc->ack_समयr.समयr,
				  jअगरfies + llc->ack_समयr.expire);
	पूर्ण अन्यथा अगर (llc->failed_data_req) अणु
		u8 f_bit;

		llc_pdu_decode_pf_bit(skb, &f_bit);
		अगर (f_bit == 1) अणु
			llc->failed_data_req = 0;
			llc_conn_ac_data_confirm(sk, skb);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_upd_p_flag(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	अगर (LLC_PDU_IS_RSP(pdu)) अणु
		u8 f_bit;

		llc_pdu_decode_pf_bit(skb, &f_bit);
		अगर (f_bit) अणु
			llc_conn_set_p_flag(sk, 0);
			llc_conn_ac_stop_p_समयr(sk, skb);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_data_flag_2(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->data_flag = 2;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_data_flag_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->data_flag = 0;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_data_flag_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->data_flag = 1;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_data_flag_1_अगर_data_flag_eq_0(काष्ठा sock *sk,
						  काष्ठा sk_buff *skb)
अणु
	अगर (!llc_sk(sk)->data_flag)
		llc_sk(sk)->data_flag = 1;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_p_flag_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_conn_set_p_flag(sk, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक llc_conn_ac_set_p_flag_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_conn_set_p_flag(sk, 1);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_remote_busy_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->remote_busy_flag = 0;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_cause_flag_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->cause_flag = 0;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_cause_flag_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->cause_flag = 1;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_retry_cnt_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->retry_count = 0;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_inc_retry_cnt_by_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->retry_count++;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_vr_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->vR = 0;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_inc_vr_by_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->vR = PDU_GET_NEXT_Vr(llc_sk(sk)->vR);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_vs_0(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->vS = 0;
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_set_vs_nr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->vS = llc_sk(sk)->last_nr;
	वापस 0;
पूर्ण

अटल पूर्णांक llc_conn_ac_inc_vs_by_1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->vS = (llc_sk(sk)->vS + 1) % LLC_2_SEQ_NBR_MODULO;
	वापस 0;
पूर्ण

अटल व्योम llc_conn_पंचांगr_common_cb(काष्ठा sock *sk, u8 type)
अणु
	काष्ठा sk_buff *skb = alloc_skb(0, GFP_ATOMIC);

	bh_lock_sock(sk);
	अगर (skb) अणु
		काष्ठा llc_conn_state_ev *ev = llc_conn_ev(skb);

		skb_set_owner_r(skb, sk);
		ev->type = type;
		llc_process_पंचांगr_ev(sk, skb);
	पूर्ण
	bh_unlock_sock(sk);
पूर्ण

व्योम llc_conn_pf_cycle_पंचांगr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा llc_sock *llc = from_समयr(llc, t, pf_cycle_समयr.समयr);

	llc_conn_पंचांगr_common_cb(&llc->sk, LLC_CONN_EV_TYPE_P_TMR);
पूर्ण

व्योम llc_conn_busy_पंचांगr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा llc_sock *llc = from_समयr(llc, t, busy_state_समयr.समयr);

	llc_conn_पंचांगr_common_cb(&llc->sk, LLC_CONN_EV_TYPE_BUSY_TMR);
पूर्ण

व्योम llc_conn_ack_पंचांगr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा llc_sock *llc = from_समयr(llc, t, ack_समयr.समयr);

	llc_conn_पंचांगr_common_cb(&llc->sk, LLC_CONN_EV_TYPE_ACK_TMR);
पूर्ण

व्योम llc_conn_rej_पंचांगr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा llc_sock *llc = from_समयr(llc, t, rej_sent_समयr.समयr);

	llc_conn_पंचांगr_common_cb(&llc->sk, LLC_CONN_EV_TYPE_REJ_TMR);
पूर्ण

पूर्णांक llc_conn_ac_rst_vs(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk(sk)->X = llc_sk(sk)->vS;
	llc_conn_ac_set_vs_nr(sk, skb);
	वापस 0;
पूर्ण

पूर्णांक llc_conn_ac_upd_vs(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	u8 nr = PDU_SUPV_GET_Nr(pdu);

	अगर (llc_circular_between(llc_sk(sk)->vS, nr, llc_sk(sk)->X))
		llc_conn_ac_set_vs_nr(sk, skb);
	वापस 0;
पूर्ण

/*
 * Non-standard actions; these not contained in IEEE specअगरication; क्रम
 * our own usage
 */
/**
 *	llc_conn_disc - हटाओs connection from SAP list and मुक्तs it
 *	@sk: बंदd connection
 *	@skb: occurred event
 */
पूर्णांक llc_conn_disc(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	/* FIXME: this thing seems to want to die */
	वापस 0;
पूर्ण

/**
 *	llc_conn_reset - resets connection
 *	@sk : reseting connection.
 *	@skb: occurred event.
 *
 *	Stop all समयrs, empty all queues and reset all flags.
 */
पूर्णांक llc_conn_reset(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	llc_sk_reset(sk);
	वापस 0;
पूर्ण

/**
 *	llc_circular_between - designates that b is between a and c or not
 *	@a: lower bound
 *	@b: element to see अगर is between a and b
 *	@c: upper bound
 *
 *	This function designates that b is between a and c or not (क्रम example,
 *	0 is between 127 and 1). Returns 1 अगर b is between a and c, 0
 *	otherwise.
 */
u8 llc_circular_between(u8 a, u8 b, u8 c)
अणु
	b = b - a;
	c = c - a;
	वापस b <= c;
पूर्ण

/**
 *	llc_process_पंचांगr_ev - समयr backend
 *	@sk: active connection
 *	@skb: occurred event
 *
 *	This function is called from समयr callback functions. When connection
 *	is busy (during sending a data frame) समयr expiration event must be
 *	queued. Otherwise this event can be sent to connection state machine.
 *	Queued events will process by llc_backlog_rcv function after sending
 *	data frame.
 */
अटल व्योम llc_process_पंचांगr_ev(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (llc_sk(sk)->state == LLC_CONN_OUT_OF_SVC) अणु
		prपूर्णांकk(KERN_WARNING "%s: timer called on closed connection\n",
		       __func__);
		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		अगर (!sock_owned_by_user(sk))
			llc_conn_state_process(sk, skb);
		अन्यथा अणु
			llc_set_backlog_type(skb, LLC_EVENT);
			__sk_add_backlog(sk, skb);
		पूर्ण
	पूर्ण
पूर्ण
