<शैली गुरु>
/*
 * llc_c_st.c - This module contains state transition of connection component.
 *
 * Description of event functions and actions there is in 802.2 LLC standard,
 * or in "llc_c_ac.c" and "llc_c_ev.c" modules.
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
#समावेश <linux/types.h>
#समावेश <net/llc_अगर.h>
#समावेश <net/llc_sap.h>
#समावेश <net/llc_c_ev.h>
#समावेश <net/llc_c_ac.h>
#समावेश <net/llc_c_st.h>

#घोषणा NONE शून्य

/* COMMON CONNECTION STATE transitions
 * Common transitions क्रम
 * LLC_CONN_STATE_NORMAL,
 * LLC_CONN_STATE_BUSY,
 * LLC_CONN_STATE_REJ,
 * LLC_CONN_STATE_AWAIT,
 * LLC_CONN_STATE_AWAIT_BUSY and
 * LLC_CONN_STATE_AWAIT_REJ states
 */
/* State transitions क्रम LLC_CONN_EV_DISC_REQ event */
अटल स्थिर llc_conn_action_t llc_common_actions_1[] = अणु
	[0] = llc_conn_ac_send_disc_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = llc_conn_ac_set_cause_flag_1,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_1 = अणु
	.ev	       = llc_conn_ev_disc_req,
	.next_state    = LLC_CONN_STATE_D_CONN,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RESET_REQ event */
अटल स्थिर llc_conn_action_t llc_common_actions_2[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = llc_conn_ac_set_cause_flag_1,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_2 = अणु
	.ev	       = llc_conn_ev_rst_req,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_SABME_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_common_actions_3[] = अणु
	[0] = llc_conn_ac_stop_all_समयrs,
	[1] = llc_conn_ac_set_vs_0,
	[2] = llc_conn_ac_set_vr_0,
	[3] = llc_conn_ac_send_ua_rsp_f_set_p,
	[4] = llc_conn_ac_rst_ind,
	[5] = llc_conn_ac_set_p_flag_0,
	[6] = llc_conn_ac_set_remote_busy_0,
	[7] = llc_conn_reset,
	[8] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_3 = अणु
	.ev	       = llc_conn_ev_rx_sabme_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DISC_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_common_actions_4[] = अणु
	[0] = llc_conn_ac_stop_all_समयrs,
	[1] = llc_conn_ac_send_ua_rsp_f_set_p,
	[2] = llc_conn_ac_disc_ind,
	[3] = llc_conn_disc,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_4 = अणु
	.ev	       = llc_conn_ev_rx_disc_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_FRMR_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_common_actions_5[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = llc_conn_ac_rst_ind,
	[5] = llc_conn_ac_set_cause_flag_0,
	[6] = llc_conn_reset,
	[7] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_5 = अणु
	.ev	       = llc_conn_ev_rx_frmr_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_5,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DM_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_common_actions_6[] = अणु
	[0] = llc_conn_ac_disc_ind,
	[1] = llc_conn_ac_stop_all_समयrs,
	[2] = llc_conn_disc,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_6 = अणु
	.ev	       = llc_conn_ev_rx_dm_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_6,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_ZZZ_CMD_Pbit_SET_X_INVAL_Nr event */
अटल स्थिर llc_conn_action_t llc_common_actions_7a[] = अणु
	[0] = llc_conn_ac_send_frmr_rsp_f_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_7a = अणु
	.ev	       = llc_conn_ev_rx_zzz_cmd_pbit_set_x_inval_nr,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_7a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_X_INVAL_Ns event */
अटल स्थिर llc_conn_action_t llc_common_actions_7b[] = अणु
	[0] = llc_conn_ac_send_frmr_rsp_f_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_7b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_x_inval_ns,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_7b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_ZZZ_RSP_Fbit_SET_X_INVAL_Nr event */
अटल स्थिर llc_conn_action_t llc_common_actions_8a[] = अणु
	[0] = llc_conn_ac_send_frmr_rsp_f_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_8a = अणु
	.ev	       = llc_conn_ev_rx_zzz_rsp_fbit_set_x_inval_nr,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_8a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_X_INVAL_Ns event */
अटल स्थिर llc_conn_action_t llc_common_actions_8b[] = अणु
	[0] = llc_conn_ac_send_frmr_rsp_f_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_8b = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_x_inval_ns,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_8b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_BAD_PDU event */
अटल स्थिर llc_conn_action_t llc_common_actions_8c[] = अणु
	[0] = llc_conn_ac_send_frmr_rsp_f_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_8c = अणु
	.ev	       = llc_conn_ev_rx_bad_pdu,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_8c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_UA_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_common_actions_9[] = अणु
	[0] = llc_conn_ac_send_frmr_rsp_f_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_9 = अणु
	.ev	       = llc_conn_ev_rx_ua_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_common_actions_9,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_XXX_RSP_Fbit_SET_1 event */
#अगर 0
अटल स्थिर llc_conn_ev_qfyr_t llc_common_ev_qfyrs_10[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_common_actions_10[] = अणु
	[0] = llc_conn_ac_send_frmr_rsp_f_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_10 = अणु
	.ev	       = llc_conn_ev_rx_xxx_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = llc_common_ev_qfyrs_10,
	.ev_actions    = llc_common_actions_10,
पूर्ण;
#पूर्ण_अगर

/* State transitions क्रम LLC_CONN_EV_P_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_common_ev_qfyrs_11a[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_common_actions_11a[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = llc_conn_ac_set_cause_flag_0,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_11a = अणु
	.ev	       = llc_conn_ev_p_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = llc_common_ev_qfyrs_11a,
	.ev_actions    = llc_common_actions_11a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_common_ev_qfyrs_11b[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_common_actions_11b[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = llc_conn_ac_set_cause_flag_0,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_11b = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = llc_common_ev_qfyrs_11b,
	.ev_actions    = llc_common_actions_11b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_REJ_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_common_ev_qfyrs_11c[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_common_actions_11c[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = llc_conn_ac_set_cause_flag_0,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_11c = अणु
	.ev	       = llc_conn_ev_rej_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = llc_common_ev_qfyrs_11c,
	.ev_actions    = llc_common_actions_11c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_BUSY_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_common_ev_qfyrs_11d[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_common_actions_11d[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_stop_other_समयrs,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = llc_conn_ac_set_cause_flag_0,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_common_state_trans_11d = अणु
	.ev	       = llc_conn_ev_busy_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = llc_common_ev_qfyrs_11d,
	.ev_actions    = llc_common_actions_11d,
पूर्ण;

/*
 * Common dummy state transition; must be last entry क्रम all state
 * transition groups - it'll be on .bss, so will be zeroed.
 */
अटल काष्ठा llc_conn_state_trans llc_common_state_trans_end;

/* LLC_CONN_STATE_ADM transitions */
/* State transitions क्रम LLC_CONN_EV_CONN_REQ event */
अटल स्थिर llc_conn_action_t llc_adm_actions_1[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_set_retry_cnt_0,
	[3] = llc_conn_ac_set_s_flag_0,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_adm_state_trans_1 = अणु
	.ev	       = llc_conn_ev_conn_req,
	.next_state    = LLC_CONN_STATE_SETUP,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_adm_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_SABME_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_adm_actions_2[] = अणु
	[0] = llc_conn_ac_send_ua_rsp_f_set_p,
	[1] = llc_conn_ac_set_vs_0,
	[2] = llc_conn_ac_set_vr_0,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = llc_conn_ac_set_p_flag_0,
	[5] = llc_conn_ac_set_remote_busy_0,
	[6] = llc_conn_ac_conn_ind,
	[7] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_adm_state_trans_2 = अणु
	.ev	       = llc_conn_ev_rx_sabme_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_adm_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DISC_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_adm_actions_3[] = अणु
	[0] = llc_conn_ac_send_dm_rsp_f_set_p,
	[1] = llc_conn_disc,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_adm_state_trans_3 = अणु
	.ev	       = llc_conn_ev_rx_disc_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_adm_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_XXX_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_adm_actions_4[] = अणु
	[0] = llc_conn_ac_send_dm_rsp_f_set_1,
	[1] = llc_conn_disc,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_adm_state_trans_4 = अणु
	.ev	       = llc_conn_ev_rx_xxx_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_adm_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_XXX_YYY event */
अटल स्थिर llc_conn_action_t llc_adm_actions_5[] = अणु
	[0] = llc_conn_disc,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_adm_state_trans_5 = अणु
	.ev	       = llc_conn_ev_rx_any_frame,
	.next_state    = LLC_CONN_OUT_OF_SVC,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_adm_actions_5,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_adm_state_transitions[] = अणु
	[0] = &llc_adm_state_trans_1,		/* Request */
	[1] = &llc_common_state_trans_end,
	[2] = &llc_common_state_trans_end,	/* local_busy */
	[3] = &llc_common_state_trans_end,	/* init_pf_cycle */
	[4] = &llc_common_state_trans_end,	/* समयr */
	[5] = &llc_adm_state_trans_2,		/* Receive frame */
	[6] = &llc_adm_state_trans_3,
	[7] = &llc_adm_state_trans_4,
	[8] = &llc_adm_state_trans_5,
	[9] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_SETUP transitions */
/* State transitions क्रम LLC_CONN_EV_RX_SABME_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_setup_actions_1[] = अणु
	[0] = llc_conn_ac_send_ua_rsp_f_set_p,
	[1] = llc_conn_ac_set_vs_0,
	[2] = llc_conn_ac_set_vr_0,
	[3] = llc_conn_ac_set_s_flag_1,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_setup_state_trans_1 = अणु
	.ev	       = llc_conn_ev_rx_sabme_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_SETUP,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_setup_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_UA_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_ev_qfyr_t llc_setup_ev_qfyrs_2[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = llc_conn_ev_qlfy_set_status_conn,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_setup_actions_2[] = अणु
	[0] = llc_conn_ac_stop_ack_समयr,
	[1] = llc_conn_ac_set_vs_0,
	[2] = llc_conn_ac_set_vr_0,
	[3] = llc_conn_ac_upd_p_flag,
	[4] = llc_conn_ac_set_remote_busy_0,
	[5] = llc_conn_ac_conn_confirm,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_setup_state_trans_2 = अणु
	.ev	       = llc_conn_ev_rx_ua_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_setup_ev_qfyrs_2,
	.ev_actions    = llc_setup_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_setup_ev_qfyrs_3[] = अणु
	[0] = llc_conn_ev_qlfy_s_flag_eq_1,
	[1] = llc_conn_ev_qlfy_set_status_conn,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_setup_actions_3[] = अणु
	[0] = llc_conn_ac_set_p_flag_0,
	[1] = llc_conn_ac_set_remote_busy_0,
	[2] = llc_conn_ac_conn_confirm,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_setup_state_trans_3 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_setup_ev_qfyrs_3,
	.ev_actions    = llc_setup_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DISC_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_ev_qfyr_t llc_setup_ev_qfyrs_4[] = अणु
	[0] = llc_conn_ev_qlfy_set_status_disc,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_setup_actions_4[] = अणु
	[0] = llc_conn_ac_send_dm_rsp_f_set_p,
	[1] = llc_conn_ac_stop_ack_समयr,
	[2] = llc_conn_ac_conn_confirm,
	[3] = llc_conn_disc,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_setup_state_trans_4 = अणु
	.ev	       = llc_conn_ev_rx_disc_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_setup_ev_qfyrs_4,
	.ev_actions    = llc_setup_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DM_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_ev_qfyr_t llc_setup_ev_qfyrs_5[] = अणु
	[0] = llc_conn_ev_qlfy_set_status_disc,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_setup_actions_5[] = अणु
	[0] = llc_conn_ac_stop_ack_समयr,
	[1] = llc_conn_ac_conn_confirm,
	[2] = llc_conn_disc,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_setup_state_trans_5 = अणु
	.ev	       = llc_conn_ev_rx_dm_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_setup_ev_qfyrs_5,
	.ev_actions    = llc_setup_actions_5,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_setup_ev_qfyrs_7[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = llc_conn_ev_qlfy_s_flag_eq_0,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_setup_actions_7[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_setup_state_trans_7 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_SETUP,
	.ev_qualअगरiers = llc_setup_ev_qfyrs_7,
	.ev_actions    = llc_setup_actions_7,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_setup_ev_qfyrs_8[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = llc_conn_ev_qlfy_s_flag_eq_0,
	[2] = llc_conn_ev_qlfy_set_status_failed,
	[3] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_setup_actions_8[] = अणु
	[0] = llc_conn_ac_conn_confirm,
	[1] = llc_conn_disc,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_setup_state_trans_8 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_setup_ev_qfyrs_8,
	.ev_actions    = llc_setup_actions_8,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_setup_state_transitions[] = अणु
	 [0] = &llc_common_state_trans_end,	/* Request */
	 [1] = &llc_common_state_trans_end,	/* local busy */
	 [2] = &llc_common_state_trans_end,	/* init_pf_cycle */
	 [3] = &llc_setup_state_trans_3,	/* Timer */
	 [4] = &llc_setup_state_trans_7,
	 [5] = &llc_setup_state_trans_8,
	 [6] = &llc_common_state_trans_end,
	 [7] = &llc_setup_state_trans_1,	/* Receive frame */
	 [8] = &llc_setup_state_trans_2,
	 [9] = &llc_setup_state_trans_4,
	[10] = &llc_setup_state_trans_5,
	[11] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_NORMAL transitions */
/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_1[] = अणु
	[0] = llc_conn_ev_qlfy_remote_busy_eq_0,
	[1] = llc_conn_ev_qlfy_p_flag_eq_0,
	[2] = llc_conn_ev_qlfy_last_frame_eq_0,
	[3] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_1[] = अणु
	[0] = llc_conn_ac_send_i_as_ack,
	[1] = llc_conn_ac_start_ack_पंचांगr_अगर_not_running,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_1 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_1,
	.ev_actions    = llc_normal_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_2[] = अणु
	[0] = llc_conn_ev_qlfy_remote_busy_eq_0,
	[1] = llc_conn_ev_qlfy_p_flag_eq_0,
	[2] = llc_conn_ev_qlfy_last_frame_eq_1,
	[3] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_2[] = अणु
	[0] = llc_conn_ac_send_i_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_2 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_2,
	.ev_actions    = llc_normal_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_2_1[] = अणु
	[0] = llc_conn_ev_qlfy_remote_busy_eq_1,
	[1] = llc_conn_ev_qlfy_set_status_remote_busy,
	[2] = शून्य,
पूर्ण;

/* just one member, शून्य, .bss zeroes it */
अटल स्थिर llc_conn_action_t llc_normal_actions_2_1[1];

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_2_1 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_2_1,
	.ev_actions    = llc_normal_actions_2_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_DETECTED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_3[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_3[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rnr_xxx_x_set_0,
	[2] = llc_conn_ac_set_data_flag_0,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_3 = अणु
	.ev	       = llc_conn_ev_local_busy_detected,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_3,
	.ev_actions    = llc_normal_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_DETECTED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_4[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_4[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rnr_xxx_x_set_0,
	[2] = llc_conn_ac_set_data_flag_0,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_4 = अणु
	.ev	       = llc_conn_ev_local_busy_detected,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_4,
	.ev_actions    = llc_normal_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_5a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_5a[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rej_xxx_x_set_0,
	[2] = llc_conn_ac_upd_nr_received,
	[3] = llc_conn_ac_upd_p_flag,
	[4] = llc_conn_ac_start_rej_समयr,
	[5] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_5a = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_5a,
	.ev_actions    = llc_normal_actions_5a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_5b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_5b[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rej_xxx_x_set_0,
	[2] = llc_conn_ac_upd_nr_received,
	[3] = llc_conn_ac_upd_p_flag,
	[4] = llc_conn_ac_start_rej_समयr,
	[5] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_5b = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_5b,
	.ev_actions    = llc_normal_actions_5b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_5c[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_5c[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rej_xxx_x_set_0,
	[2] = llc_conn_ac_upd_nr_received,
	[3] = llc_conn_ac_upd_p_flag,
	[4] = llc_conn_ac_start_rej_समयr,
	[5] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_5c = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_5c,
	.ev_actions    = llc_normal_actions_5c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_6a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_6a[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rej_xxx_x_set_0,
	[2] = llc_conn_ac_upd_nr_received,
	[3] = llc_conn_ac_start_rej_समयr,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_6a = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_6a,
	.ev_actions    = llc_normal_actions_6a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_6b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_6b[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rej_xxx_x_set_0,
	[2] = llc_conn_ac_upd_nr_received,
	[3] = llc_conn_ac_start_rej_समयr,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_6b = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_6b,
	.ev_actions    = llc_normal_actions_6b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_normal_actions_7[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rej_rsp_f_set_1,
	[2] = llc_conn_ac_upd_nr_received,
	[3] = llc_conn_ac_start_rej_समयr,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_7 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_normal_actions_7,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_8a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_8[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[5] = llc_conn_ac_send_ack_अगर_needed,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_8a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_8a,
	.ev_actions    = llc_normal_actions_8,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_8b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_8b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_8b,
	.ev_actions    = llc_normal_actions_8,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_9a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_9a[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_data_ind,
	[3] = llc_conn_ac_send_ack_अगर_needed,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_9a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_9a,
	.ev_actions    = llc_normal_actions_9a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_9b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_9b[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_data_ind,
	[3] = llc_conn_ac_send_ack_अगर_needed,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_9b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_9b,
	.ev_actions    = llc_normal_actions_9b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_normal_actions_10[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_send_ack_rsp_f_set_1,
	[2] = llc_conn_ac_rst_sendack_flag,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_data_ind,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_10 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_normal_actions_10,
पूर्ण;

/* State transitions क्रम * LLC_CONN_EV_RX_RR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_normal_actions_11a[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_11a = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_normal_actions_11a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_normal_actions_11b[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_11b = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_normal_actions_11b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_11c[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_11c[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_inc_tx_win_size,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_11c = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_11c,
	.ev_actions    = llc_normal_actions_11c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_normal_actions_12[] = अणु
	[0] = llc_conn_ac_send_ack_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_adjust_npta_by_rr,
	[3] = llc_conn_ac_rst_sendack_flag,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_12 = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_normal_actions_12,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_normal_actions_13a[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_13a = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_normal_actions_13a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_normal_actions_13b[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_13b = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_normal_actions_13b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_13c[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_13c[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_13c = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_13c,
	.ev_actions    = llc_normal_actions_13c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_normal_actions_14[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_adjust_npta_by_rnr,
	[3] = llc_conn_ac_rst_sendack_flag,
	[4] = llc_conn_ac_set_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_14 = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_normal_actions_14,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_15a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_15a[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_dec_tx_win_size,
	[4] = llc_conn_ac_resend_i_xxx_x_set_0,
	[5] = llc_conn_ac_clear_remote_busy,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_15a = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_15a,
	.ev_actions    = llc_normal_actions_15a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_15b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_15b[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_dec_tx_win_size,
	[4] = llc_conn_ac_resend_i_xxx_x_set_0,
	[5] = llc_conn_ac_clear_remote_busy,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_15b = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_15b,
	.ev_actions    = llc_normal_actions_15b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_16a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_16a[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_dec_tx_win_size,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_16a = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_16a,
	.ev_actions    = llc_normal_actions_16a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_16b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_16b[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_dec_tx_win_size,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_16b = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_16b,
	.ev_actions    = llc_normal_actions_16b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_normal_actions_17[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_dec_tx_win_size,
	[3] = llc_conn_ac_resend_i_rsp_f_set_1,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_17 = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_normal_actions_17,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_INIT_P_F_CYCLE event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_18[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_18[] = अणु
	[0] = llc_conn_ac_send_rr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_18 = अणु
	.ev	       = llc_conn_ev_init_p_f_cycle,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_18,
	.ev_actions    = llc_normal_actions_18,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_P_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_19[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_19[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rr_cmd_p_set_1,
	[2] = llc_conn_ac_rst_vs,
	[3] = llc_conn_ac_start_p_समयr,
	[4] = llc_conn_ac_inc_retry_cnt_by_1,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_19 = अणु
	.ev	       = llc_conn_ev_p_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_19,
	.ev_actions    = llc_normal_actions_19,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_20a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_20a[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rr_cmd_p_set_1,
	[2] = llc_conn_ac_rst_vs,
	[3] = llc_conn_ac_start_p_समयr,
	[4] = llc_conn_ac_inc_retry_cnt_by_1,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_20a = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_20a,
	.ev_actions    = llc_normal_actions_20a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_BUSY_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_20b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_20b[] = अणु
	[0] = llc_conn_ac_rst_sendack_flag,
	[1] = llc_conn_ac_send_rr_cmd_p_set_1,
	[2] = llc_conn_ac_rst_vs,
	[3] = llc_conn_ac_start_p_समयr,
	[4] = llc_conn_ac_inc_retry_cnt_by_1,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_20b = अणु
	.ev	       = llc_conn_ev_busy_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_20b,
	.ev_actions    = llc_normal_actions_20b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_TX_BUFF_FULL event */
अटल स्थिर llc_conn_ev_qfyr_t llc_normal_ev_qfyrs_21[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_normal_actions_21[] = अणु
	[0] = llc_conn_ac_send_rr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_normal_state_trans_21 = अणु
	.ev	       = llc_conn_ev_tx_buffer_full,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_normal_ev_qfyrs_21,
	.ev_actions    = llc_normal_actions_21,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_normal_state_transitions[] = अणु
	 [0] = &llc_normal_state_trans_1,	/* Requests */
	 [1] = &llc_normal_state_trans_2,
	 [2] = &llc_normal_state_trans_2_1,
	 [3] = &llc_common_state_trans_1,
	 [4] = &llc_common_state_trans_2,
	 [5] = &llc_common_state_trans_end,
	 [6] = &llc_normal_state_trans_21,
	 [7] = &llc_normal_state_trans_3,	/* Local busy */
	 [8] = &llc_normal_state_trans_4,
	 [9] = &llc_common_state_trans_end,
	[10] = &llc_normal_state_trans_18,	/* Init pf cycle */
	[11] = &llc_common_state_trans_end,
	[12] = &llc_common_state_trans_11a,	/* Timers */
	[13] = &llc_common_state_trans_11b,
	[14] = &llc_common_state_trans_11c,
	[15] = &llc_common_state_trans_11d,
	[16] = &llc_normal_state_trans_19,
	[17] = &llc_normal_state_trans_20a,
	[18] = &llc_normal_state_trans_20b,
	[19] = &llc_common_state_trans_end,
	[20] = &llc_normal_state_trans_8b,	/* Receive frames */
	[21] = &llc_normal_state_trans_9b,
	[22] = &llc_normal_state_trans_10,
	[23] = &llc_normal_state_trans_11b,
	[24] = &llc_normal_state_trans_11c,
	[25] = &llc_normal_state_trans_5a,
	[26] = &llc_normal_state_trans_5b,
	[27] = &llc_normal_state_trans_5c,
	[28] = &llc_normal_state_trans_6a,
	[29] = &llc_normal_state_trans_6b,
	[30] = &llc_normal_state_trans_7,
	[31] = &llc_normal_state_trans_8a,
	[32] = &llc_normal_state_trans_9a,
	[33] = &llc_normal_state_trans_11a,
	[34] = &llc_normal_state_trans_12,
	[35] = &llc_normal_state_trans_13a,
	[36] = &llc_normal_state_trans_13b,
	[37] = &llc_normal_state_trans_13c,
	[38] = &llc_normal_state_trans_14,
	[39] = &llc_normal_state_trans_15a,
	[40] = &llc_normal_state_trans_15b,
	[41] = &llc_normal_state_trans_16a,
	[42] = &llc_normal_state_trans_16b,
	[43] = &llc_normal_state_trans_17,
	[44] = &llc_common_state_trans_3,
	[45] = &llc_common_state_trans_4,
	[46] = &llc_common_state_trans_5,
	[47] = &llc_common_state_trans_6,
	[48] = &llc_common_state_trans_7a,
	[49] = &llc_common_state_trans_7b,
	[50] = &llc_common_state_trans_8a,
	[51] = &llc_common_state_trans_8b,
	[52] = &llc_common_state_trans_8c,
	[53] = &llc_common_state_trans_9,
	/* [54] = &llc_common_state_trans_10, */
	[54] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_BUSY transitions */
/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_1[] = अणु
	[0] = llc_conn_ev_qlfy_remote_busy_eq_0,
	[1] = llc_conn_ev_qlfy_p_flag_eq_0,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_1[] = अणु
	[0] = llc_conn_ac_send_i_xxx_x_set_0,
	[1] = llc_conn_ac_start_ack_पंचांगr_अगर_not_running,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_1 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_1,
	.ev_actions    = llc_busy_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_2[] = अणु
	[0] = llc_conn_ev_qlfy_remote_busy_eq_0,
	[1] = llc_conn_ev_qlfy_p_flag_eq_1,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_2[] = अणु
	[0] = llc_conn_ac_send_i_xxx_x_set_0,
	[1] = llc_conn_ac_start_ack_पंचांगr_अगर_not_running,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_2 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_2,
	.ev_actions    = llc_busy_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_2_1[] = अणु
	[0] = llc_conn_ev_qlfy_remote_busy_eq_1,
	[1] = llc_conn_ev_qlfy_set_status_remote_busy,
	[2] = शून्य,
पूर्ण;

/* just one member, शून्य, .bss zeroes it */
अटल स्थिर llc_conn_action_t llc_busy_actions_2_1[1];

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_2_1 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_2_1,
	.ev_actions    = llc_busy_actions_2_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_CLEARED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_3[] = अणु
	[0] = llc_conn_ev_qlfy_data_flag_eq_1,
	[1] = llc_conn_ev_qlfy_p_flag_eq_0,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_3[] = अणु
	[0] = llc_conn_ac_send_rej_xxx_x_set_0,
	[1] = llc_conn_ac_start_rej_समयr,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_3 = अणु
	.ev	       = llc_conn_ev_local_busy_cleared,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_3,
	.ev_actions    = llc_busy_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_CLEARED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_4[] = अणु
	[0] = llc_conn_ev_qlfy_data_flag_eq_1,
	[1] = llc_conn_ev_qlfy_p_flag_eq_1,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_4[] = अणु
	[0] = llc_conn_ac_send_rej_xxx_x_set_0,
	[1] = llc_conn_ac_start_rej_समयr,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_4 = अणु
	.ev	       = llc_conn_ev_local_busy_cleared,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_4,
	.ev_actions    = llc_busy_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_CLEARED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_5[] = अणु
	[0] = llc_conn_ev_qlfy_data_flag_eq_0,
	[1] = llc_conn_ev_qlfy_p_flag_eq_0,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_5[] = अणु
	[0] = llc_conn_ac_send_rr_xxx_x_set_0,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_5 = अणु
	.ev	       = llc_conn_ev_local_busy_cleared,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_5,
	.ev_actions    = llc_busy_actions_5,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_CLEARED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_6[] = अणु
	[0] = llc_conn_ev_qlfy_data_flag_eq_0,
	[1] = llc_conn_ev_qlfy_p_flag_eq_1,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_6[] = अणु
	[0] = llc_conn_ac_send_rr_xxx_x_set_0,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_6 = अणु
	.ev	       = llc_conn_ev_local_busy_cleared,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_6,
	.ev_actions    = llc_busy_actions_6,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_CLEARED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_7[] = अणु
	[0] = llc_conn_ev_qlfy_data_flag_eq_2,
	[1] = llc_conn_ev_qlfy_p_flag_eq_0,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_7[] = अणु
	[0] = llc_conn_ac_send_rr_xxx_x_set_0,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_7 = अणु
	.ev	       = llc_conn_ev_local_busy_cleared,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_7,
	.ev_actions    = llc_busy_actions_7,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_CLEARED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_8[] = अणु
	[0] = llc_conn_ev_qlfy_data_flag_eq_2,
	[1] = llc_conn_ev_qlfy_p_flag_eq_1,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_8[] = अणु
	[0] = llc_conn_ac_send_rr_xxx_x_set_0,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_8 = अणु
	.ev	       = llc_conn_ev_local_busy_cleared,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_8,
	.ev_actions    = llc_busy_actions_8,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_X_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_9a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_9a[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_upd_p_flag,
	[2] = llc_conn_ac_upd_nr_received,
	[3] = llc_conn_ac_set_data_flag_1_अगर_data_flag_eq_0,
	[4] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_9a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_x_unexpd_ns,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_9a,
	.ev_actions    = llc_busy_actions_9a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_9b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_9b[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_upd_p_flag,
	[2] = llc_conn_ac_upd_nr_received,
	[3] = llc_conn_ac_set_data_flag_1_अगर_data_flag_eq_0,
	[4] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_9b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_9b,
	.ev_actions    = llc_busy_actions_9b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_10a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_10a[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_data_flag_1_अगर_data_flag_eq_0,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_10a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_10a,
	.ev_actions    = llc_busy_actions_10a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_10b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_10b[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_data_flag_1_अगर_data_flag_eq_0,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_10b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_10b,
	.ev_actions    = llc_busy_actions_10b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_busy_actions_11[] = अणु
	[0] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_data_flag_1_अगर_data_flag_eq_0,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_11 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_busy_actions_11,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_busy_actions_12[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_stop_rej_पंचांगr_अगर_data_flag_eq_2,
	[5] = llc_conn_ac_set_data_flag_0,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_12 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_busy_actions_12,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_13a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_13a[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[4] = llc_conn_ac_upd_nr_received,
	[5] = llc_conn_ac_stop_rej_पंचांगr_अगर_data_flag_eq_2,
	[6] = llc_conn_ac_set_data_flag_0,
	[7] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[8] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_13a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_13a,
	.ev_actions    = llc_busy_actions_13a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_13b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_13b[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[4] = llc_conn_ac_upd_nr_received,
	[5] = llc_conn_ac_stop_rej_पंचांगr_अगर_data_flag_eq_2,
	[6] = llc_conn_ac_set_data_flag_0,
	[7] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[8] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_13b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_13b,
	.ev_actions    = llc_busy_actions_13b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_14a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_14a[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_stop_rej_पंचांगr_अगर_data_flag_eq_2,
	[5] = llc_conn_ac_set_data_flag_0,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_14a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_14a,
	.ev_actions    = llc_busy_actions_14a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_14b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_14b[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_stop_rej_पंचांगr_अगर_data_flag_eq_2,
	[5] = llc_conn_ac_set_data_flag_0,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_14b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_14b,
	.ev_actions    = llc_busy_actions_14b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_busy_actions_15a[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_15a = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_busy_actions_15a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_busy_actions_15b[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_15b = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_busy_actions_15b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_15c[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_15c[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_15c = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_15c,
	.ev_actions    = llc_busy_actions_15c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_busy_actions_16[] = अणु
	[0] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_16 = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_busy_actions_16,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_busy_actions_17a[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_17a = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_busy_actions_17a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_busy_actions_17b[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_17b = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_busy_actions_17b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_17c[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_17c[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_17c = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_17c,
	.ev_actions    = llc_busy_actions_17c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_busy_actions_18[] = अणु
	[0] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_18 = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_busy_actions_18,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_19a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_19a[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_19a = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_19a,
	.ev_actions    = llc_busy_actions_19a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_19b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_19b[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_19b = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_19b,
	.ev_actions    = llc_busy_actions_19b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_20a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_20a[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_resend_i_xxx_x_set_0,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_20a = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_20a,
	.ev_actions    = llc_busy_actions_20a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_20b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_20b[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_resend_i_xxx_x_set_0,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_20b = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_20b,
	.ev_actions    = llc_busy_actions_20b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_busy_actions_21[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_21 = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_busy_actions_21,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_INIT_P_F_CYCLE event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_22[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_22[] = अणु
	[0] = llc_conn_ac_send_rnr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_22 = अणु
	.ev	       = llc_conn_ev_init_p_f_cycle,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_22,
	.ev_actions    = llc_busy_actions_22,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_P_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_23[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_23[] = अणु
	[0] = llc_conn_ac_send_rnr_cmd_p_set_1,
	[1] = llc_conn_ac_rst_vs,
	[2] = llc_conn_ac_start_p_समयr,
	[3] = llc_conn_ac_inc_retry_cnt_by_1,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_23 = अणु
	.ev	       = llc_conn_ev_p_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_23,
	.ev_actions    = llc_busy_actions_23,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_24a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_24a[] = अणु
	[0] = llc_conn_ac_send_rnr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = llc_conn_ac_rst_vs,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_24a = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_24a,
	.ev_actions    = llc_busy_actions_24a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_BUSY_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_24b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_24b[] = अणु
	[0] = llc_conn_ac_send_rnr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = llc_conn_ac_rst_vs,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_24b = अणु
	.ev	       = llc_conn_ev_busy_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_24b,
	.ev_actions    = llc_busy_actions_24b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_REJ_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_25[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_25[] = अणु
	[0] = llc_conn_ac_send_rnr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = llc_conn_ac_rst_vs,
	[4] = llc_conn_ac_set_data_flag_1,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_25 = अणु
	.ev	       = llc_conn_ev_rej_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_25,
	.ev_actions    = llc_busy_actions_25,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_REJ_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_busy_ev_qfyrs_26[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_busy_actions_26[] = अणु
	[0] = llc_conn_ac_set_data_flag_1,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_busy_state_trans_26 = अणु
	.ev	       = llc_conn_ev_rej_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_busy_ev_qfyrs_26,
	.ev_actions    = llc_busy_actions_26,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_busy_state_transitions[] = अणु
	 [0] = &llc_common_state_trans_1,	/* Request */
	 [1] = &llc_common_state_trans_2,
	 [2] = &llc_busy_state_trans_1,
	 [3] = &llc_busy_state_trans_2,
	 [4] = &llc_busy_state_trans_2_1,
	 [5] = &llc_common_state_trans_end,
	 [6] = &llc_busy_state_trans_3,		/* Local busy */
	 [7] = &llc_busy_state_trans_4,
	 [8] = &llc_busy_state_trans_5,
	 [9] = &llc_busy_state_trans_6,
	[10] = &llc_busy_state_trans_7,
	[11] = &llc_busy_state_trans_8,
	[12] = &llc_common_state_trans_end,
	[13] = &llc_busy_state_trans_22,	/* Initiate PF cycle */
	[14] = &llc_common_state_trans_end,
	[15] = &llc_common_state_trans_11a,	/* Timer */
	[16] = &llc_common_state_trans_11b,
	[17] = &llc_common_state_trans_11c,
	[18] = &llc_common_state_trans_11d,
	[19] = &llc_busy_state_trans_23,
	[20] = &llc_busy_state_trans_24a,
	[21] = &llc_busy_state_trans_24b,
	[22] = &llc_busy_state_trans_25,
	[23] = &llc_busy_state_trans_26,
	[24] = &llc_common_state_trans_end,
	[25] = &llc_busy_state_trans_9a,	/* Receive frame */
	[26] = &llc_busy_state_trans_9b,
	[27] = &llc_busy_state_trans_10a,
	[28] = &llc_busy_state_trans_10b,
	[29] = &llc_busy_state_trans_11,
	[30] = &llc_busy_state_trans_12,
	[31] = &llc_busy_state_trans_13a,
	[32] = &llc_busy_state_trans_13b,
	[33] = &llc_busy_state_trans_14a,
	[34] = &llc_busy_state_trans_14b,
	[35] = &llc_busy_state_trans_15a,
	[36] = &llc_busy_state_trans_15b,
	[37] = &llc_busy_state_trans_15c,
	[38] = &llc_busy_state_trans_16,
	[39] = &llc_busy_state_trans_17a,
	[40] = &llc_busy_state_trans_17b,
	[41] = &llc_busy_state_trans_17c,
	[42] = &llc_busy_state_trans_18,
	[43] = &llc_busy_state_trans_19a,
	[44] = &llc_busy_state_trans_19b,
	[45] = &llc_busy_state_trans_20a,
	[46] = &llc_busy_state_trans_20b,
	[47] = &llc_busy_state_trans_21,
	[48] = &llc_common_state_trans_3,
	[49] = &llc_common_state_trans_4,
	[50] = &llc_common_state_trans_5,
	[51] = &llc_common_state_trans_6,
	[52] = &llc_common_state_trans_7a,
	[53] = &llc_common_state_trans_7b,
	[54] = &llc_common_state_trans_8a,
	[55] = &llc_common_state_trans_8b,
	[56] = &llc_common_state_trans_8c,
	[57] = &llc_common_state_trans_9,
	/* [58] = &llc_common_state_trans_10, */
	[58] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_REJ transitions */
/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_1[] = अणु
	[0] = llc_conn_ev_qlfy_remote_busy_eq_0,
	[1] = llc_conn_ev_qlfy_p_flag_eq_0,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_1[] = अणु
	[0] = llc_conn_ac_send_i_xxx_x_set_0,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_1 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_1,
	.ev_actions    = llc_reject_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_2[] = अणु
	[0] = llc_conn_ev_qlfy_remote_busy_eq_0,
	[1] = llc_conn_ev_qlfy_p_flag_eq_1,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_2[] = अणु
	[0] = llc_conn_ac_send_i_xxx_x_set_0,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_2 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_2,
	.ev_actions    = llc_reject_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_2_1[] = अणु
	[0] = llc_conn_ev_qlfy_remote_busy_eq_1,
	[1] = llc_conn_ev_qlfy_set_status_remote_busy,
	[2] = शून्य,
पूर्ण;

/* just one member, शून्य, .bss zeroes it */
अटल स्थिर llc_conn_action_t llc_reject_actions_2_1[1];

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_2_1 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_2_1,
	.ev_actions    = llc_reject_actions_2_1,
पूर्ण;


/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_DETECTED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_3[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_3[] = अणु
	[0] = llc_conn_ac_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_set_data_flag_2,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_3 = अणु
	.ev	       = llc_conn_ev_local_busy_detected,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_3,
	.ev_actions    = llc_reject_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_DETECTED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_4[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_4[] = अणु
	[0] = llc_conn_ac_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_set_data_flag_2,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_4 = अणु
	.ev	       = llc_conn_ev_local_busy_detected,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_4,
	.ev_actions    = llc_reject_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_reject_actions_5a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_p_flag,
	[2] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_5a = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_5a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_reject_actions_5b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_p_flag,
	[2] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_5b = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_5b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_5c[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_5c[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_p_flag,
	[2] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_5c = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_5c,
	.ev_actions    = llc_reject_actions_5c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_reject_actions_6[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_6 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_6,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_7a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_7a[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_send_ack_xxx_x_set_0,
	[4] = llc_conn_ac_upd_nr_received,
	[5] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[6] = llc_conn_ac_stop_rej_समयr,
	[7] = शून्य,

पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_7a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_7a,
	.ev_actions    = llc_reject_actions_7a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_7b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_7b[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_send_ack_xxx_x_set_0,
	[4] = llc_conn_ac_upd_nr_received,
	[5] = llc_conn_ac_clear_remote_busy_अगर_f_eq_1,
	[6] = llc_conn_ac_stop_rej_समयr,
	[7] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_7b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_7b,
	.ev_actions    = llc_reject_actions_7b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_8a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_8a[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_ack_xxx_x_set_0,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_stop_rej_समयr,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_8a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_8a,
	.ev_actions    = llc_reject_actions_8a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_8b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_8b[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_ack_xxx_x_set_0,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_stop_rej_समयr,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_8b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_8b,
	.ev_actions    = llc_reject_actions_8b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_reject_actions_9[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_ack_rsp_f_set_1,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_stop_rej_समयr,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_9 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_9,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_reject_actions_10a[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_10a = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_10a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_reject_actions_10b[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_10b = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_10b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_10c[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_10c[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_10c = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_10c,
	.ev_actions    = llc_reject_actions_10c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_reject_actions_11[] = अणु
	[0] = llc_conn_ac_send_ack_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_11 = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_11,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_reject_actions_12a[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_12a = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_12a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_reject_actions_12b[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_12b = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_12b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_12c[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_12c[] = अणु
	[0] = llc_conn_ac_upd_p_flag,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_12c = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_12c,
	.ev_actions    = llc_reject_actions_12c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_reject_actions_13[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_13 = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_13,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_14a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_14a[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_14a = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_14a,
	.ev_actions    = llc_reject_actions_14a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_14b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_14b[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_p_flag,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_14b = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_14b,
	.ev_actions    = llc_reject_actions_14b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_15a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_15a[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_resend_i_xxx_x_set_0,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_15a = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_15a,
	.ev_actions    = llc_reject_actions_15a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_15b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_15b[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_resend_i_xxx_x_set_0,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_15b = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_15b,
	.ev_actions    = llc_reject_actions_15b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_reject_actions_16[] = अणु
	[0] = llc_conn_ac_set_vs_nr,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_resend_i_rsp_f_set_1,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_16 = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_reject_actions_16,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_INIT_P_F_CYCLE event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_17[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_17[] = अणु
	[0] = llc_conn_ac_send_rr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_17 = अणु
	.ev	       = llc_conn_ev_init_p_f_cycle,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_17,
	.ev_actions    = llc_reject_actions_17,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_REJ_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_18[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_18[] = अणु
	[0] = llc_conn_ac_send_rej_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = llc_conn_ac_start_rej_समयr,
	[3] = llc_conn_ac_inc_retry_cnt_by_1,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_18 = अणु
	.ev	       = llc_conn_ev_rej_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_18,
	.ev_actions    = llc_reject_actions_18,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_P_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_19[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_19[] = अणु
	[0] = llc_conn_ac_send_rr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = llc_conn_ac_start_rej_समयr,
	[3] = llc_conn_ac_inc_retry_cnt_by_1,
	[4] = llc_conn_ac_rst_vs,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_19 = अणु
	.ev	       = llc_conn_ev_p_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_19,
	.ev_actions    = llc_reject_actions_19,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_20a[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_20a[] = अणु
	[0] = llc_conn_ac_send_rr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = llc_conn_ac_start_rej_समयr,
	[3] = llc_conn_ac_inc_retry_cnt_by_1,
	[4] = llc_conn_ac_rst_vs,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_20a = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_20a,
	.ev_actions    = llc_reject_actions_20a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_BUSY_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_reject_ev_qfyrs_20b[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_0,
	[1] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_reject_actions_20b[] = अणु
	[0] = llc_conn_ac_send_rr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = llc_conn_ac_start_rej_समयr,
	[3] = llc_conn_ac_inc_retry_cnt_by_1,
	[4] = llc_conn_ac_rst_vs,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_reject_state_trans_20b = अणु
	.ev	       = llc_conn_ev_busy_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = llc_reject_ev_qfyrs_20b,
	.ev_actions    = llc_reject_actions_20b,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_reject_state_transitions[] = अणु
	 [0] = &llc_common_state_trans_1,	/* Request */
	 [1] = &llc_common_state_trans_2,
	 [2] = &llc_common_state_trans_end,
	 [3] = &llc_reject_state_trans_1,
	 [4] = &llc_reject_state_trans_2,
	 [5] = &llc_reject_state_trans_2_1,
	 [6] = &llc_reject_state_trans_3,	/* Local busy */
	 [7] = &llc_reject_state_trans_4,
	 [8] = &llc_common_state_trans_end,
	 [9] = &llc_reject_state_trans_17,	/* Initiate PF cycle */
	[10] = &llc_common_state_trans_end,
	[11] = &llc_common_state_trans_11a,	/* Timer */
	[12] = &llc_common_state_trans_11b,
	[13] = &llc_common_state_trans_11c,
	[14] = &llc_common_state_trans_11d,
	[15] = &llc_reject_state_trans_18,
	[16] = &llc_reject_state_trans_19,
	[17] = &llc_reject_state_trans_20a,
	[18] = &llc_reject_state_trans_20b,
	[19] = &llc_common_state_trans_end,
	[20] = &llc_common_state_trans_3,	/* Receive frame */
	[21] = &llc_common_state_trans_4,
	[22] = &llc_common_state_trans_5,
	[23] = &llc_common_state_trans_6,
	[24] = &llc_common_state_trans_7a,
	[25] = &llc_common_state_trans_7b,
	[26] = &llc_common_state_trans_8a,
	[27] = &llc_common_state_trans_8b,
	[28] = &llc_common_state_trans_8c,
	[29] = &llc_common_state_trans_9,
	/* [30] = &llc_common_state_trans_10, */
	[30] = &llc_reject_state_trans_5a,
	[31] = &llc_reject_state_trans_5b,
	[32] = &llc_reject_state_trans_5c,
	[33] = &llc_reject_state_trans_6,
	[34] = &llc_reject_state_trans_7a,
	[35] = &llc_reject_state_trans_7b,
	[36] = &llc_reject_state_trans_8a,
	[37] = &llc_reject_state_trans_8b,
	[38] = &llc_reject_state_trans_9,
	[39] = &llc_reject_state_trans_10a,
	[40] = &llc_reject_state_trans_10b,
	[41] = &llc_reject_state_trans_10c,
	[42] = &llc_reject_state_trans_11,
	[43] = &llc_reject_state_trans_12a,
	[44] = &llc_reject_state_trans_12b,
	[45] = &llc_reject_state_trans_12c,
	[46] = &llc_reject_state_trans_13,
	[47] = &llc_reject_state_trans_14a,
	[48] = &llc_reject_state_trans_14b,
	[49] = &llc_reject_state_trans_15a,
	[50] = &llc_reject_state_trans_15b,
	[51] = &llc_reject_state_trans_16,
	[52] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_AWAIT transitions */
/* State transitions क्रम LLC_CONN_EV_DATA_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_aरुको_ev_qfyrs_1_0[] = अणु
	[0] = llc_conn_ev_qlfy_set_status_refuse,
	[1] = शून्य,
पूर्ण;

/* just one member, शून्य, .bss zeroes it */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_1_0[1];

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_1_0 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = llc_aरुको_ev_qfyrs_1_0,
	.ev_actions    = llc_aरुको_actions_1_0,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_DETECTED event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_1[] = अणु
	[0] = llc_conn_ac_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_set_data_flag_0,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_1 = अणु
	.ev	       = llc_conn_ev_local_busy_detected,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_2[] = अणु
	[0] = llc_conn_ac_send_rej_xxx_x_set_0,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_stop_p_समयr,
	[4] = llc_conn_ac_resend_i_xxx_x_set_0,
	[5] = llc_conn_ac_start_rej_समयr,
	[6] = llc_conn_ac_clear_remote_busy,
	[7] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_2 = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_3a[] = अणु
	[0] = llc_conn_ac_send_rej_xxx_x_set_0,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_start_rej_समयr,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_3a = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_3a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_3b[] = अणु
	[0] = llc_conn_ac_send_rej_xxx_x_set_0,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_start_rej_समयr,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_3b = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_3b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_4[] = अणु
	[0] = llc_conn_ac_send_rej_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_start_rej_समयr,
	[4] = llc_conn_ac_start_p_समयr,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_4 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_5[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_upd_vs,
	[5] = llc_conn_ac_resend_i_xxx_x_set_0_or_send_rr,
	[6] = llc_conn_ac_clear_remote_busy,
	[7] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_5 = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_5,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_6a[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_rr_xxx_x_set_0,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_upd_vs,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_6a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_6a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_6b[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_rr_xxx_x_set_0,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_upd_vs,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_6b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_6b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_7[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_rr_rsp_f_set_1,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_upd_vs,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_7 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_7,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_8a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_8a = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_8a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_8b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_8b = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_8b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_9a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_9a = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_9a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_9b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_9b = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_9b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_9c[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_9c = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_9c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_9d[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_9d = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_9d,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_10a[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_10a = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_10a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_10b[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_10b = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_10b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_11[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_set_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_11 = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_11,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_12a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_12a = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_12a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_12b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_12b = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_12b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_actions_13[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_set_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_13 = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_actions_13,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_P_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_aरुको_ev_qfyrs_14[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_aरुको_actions_14[] = अणु
	[0] = llc_conn_ac_send_rr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_state_trans_14 = अणु
	.ev	       = llc_conn_ev_p_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = llc_aरुको_ev_qfyrs_14,
	.ev_actions    = llc_aरुको_actions_14,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_aरुको_state_transitions[] = अणु
	 [0] = &llc_common_state_trans_1,	/* Request */
	 [1] = &llc_common_state_trans_2,
	 [2] = &llc_aरुको_state_trans_1_0,
	 [3] = &llc_common_state_trans_end,
	 [4] = &llc_aरुको_state_trans_1,	/* Local busy */
	 [5] = &llc_common_state_trans_end,
	 [6] = &llc_common_state_trans_end,	/* Initiate PF Cycle */
	 [7] = &llc_common_state_trans_11a,	/* Timer */
	 [8] = &llc_common_state_trans_11b,
	 [9] = &llc_common_state_trans_11c,
	[10] = &llc_common_state_trans_11d,
	[11] = &llc_aरुको_state_trans_14,
	[12] = &llc_common_state_trans_end,
	[13] = &llc_common_state_trans_3,	/* Receive frame */
	[14] = &llc_common_state_trans_4,
	[15] = &llc_common_state_trans_5,
	[16] = &llc_common_state_trans_6,
	[17] = &llc_common_state_trans_7a,
	[18] = &llc_common_state_trans_7b,
	[19] = &llc_common_state_trans_8a,
	[20] = &llc_common_state_trans_8b,
	[21] = &llc_common_state_trans_8c,
	[22] = &llc_common_state_trans_9,
	/* [23] = &llc_common_state_trans_10, */
	[23] = &llc_aरुको_state_trans_2,
	[24] = &llc_aरुको_state_trans_3a,
	[25] = &llc_aरुको_state_trans_3b,
	[26] = &llc_aरुको_state_trans_4,
	[27] = &llc_aरुको_state_trans_5,
	[28] = &llc_aरुको_state_trans_6a,
	[29] = &llc_aरुको_state_trans_6b,
	[30] = &llc_aरुको_state_trans_7,
	[31] = &llc_aरुको_state_trans_8a,
	[32] = &llc_aरुको_state_trans_8b,
	[33] = &llc_aरुको_state_trans_9a,
	[34] = &llc_aरुको_state_trans_9b,
	[35] = &llc_aरुको_state_trans_9c,
	[36] = &llc_aरुको_state_trans_9d,
	[37] = &llc_aरुको_state_trans_10a,
	[38] = &llc_aरुको_state_trans_10b,
	[39] = &llc_aरुको_state_trans_11,
	[40] = &llc_aरुको_state_trans_12a,
	[41] = &llc_aरुको_state_trans_12b,
	[42] = &llc_aरुको_state_trans_13,
	[43] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_AWAIT_BUSY transitions */
/* State transitions क्रम LLC_CONN_EV_DATA_CONN_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_aरुको_busy_ev_qfyrs_1_0[] = अणु
	[0] = llc_conn_ev_qlfy_set_status_refuse,
	[1] = शून्य,
पूर्ण;

/* just one member, शून्य, .bss zeroes it */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_1_0[1];

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_1_0 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = llc_aरुको_busy_ev_qfyrs_1_0,
	.ev_actions    = llc_aरुको_busy_actions_1_0,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_CLEARED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_aरुको_busy_ev_qfyrs_1[] = अणु
	[0] = llc_conn_ev_qlfy_data_flag_eq_1,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_1[] = अणु
	[0] = llc_conn_ac_send_rej_xxx_x_set_0,
	[1] = llc_conn_ac_start_rej_समयr,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_1 = अणु
	.ev	       = llc_conn_ev_local_busy_cleared,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = llc_aरुको_busy_ev_qfyrs_1,
	.ev_actions    = llc_aरुको_busy_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_CLEARED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_aरुको_busy_ev_qfyrs_2[] = अणु
	[0] = llc_conn_ev_qlfy_data_flag_eq_0,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_2[] = अणु
	[0] = llc_conn_ac_send_rr_xxx_x_set_0,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_2 = अणु
	.ev	       = llc_conn_ev_local_busy_cleared,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = llc_aरुको_busy_ev_qfyrs_2,
	.ev_actions    = llc_aरुको_busy_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_CLEARED event */
अटल स्थिर llc_conn_ev_qfyr_t llc_aरुको_busy_ev_qfyrs_3[] = अणु
	[0] = llc_conn_ev_qlfy_data_flag_eq_2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_3[] = अणु
	[0] = llc_conn_ac_send_rr_xxx_x_set_0,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_3 = अणु
	.ev	       = llc_conn_ev_local_busy_cleared,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = llc_aरुको_busy_ev_qfyrs_3,
	.ev_actions    = llc_aरुको_busy_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_4[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_stop_p_समयr,
	[4] = llc_conn_ac_set_data_flag_1,
	[5] = llc_conn_ac_clear_remote_busy,
	[6] = llc_conn_ac_resend_i_xxx_x_set_0,
	[7] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_4 = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_5a[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_set_data_flag_1,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_5a = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_5a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_5b[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_set_data_flag_1,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_5b = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_5b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_6[] = अणु
	[0] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_set_data_flag_1,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_6 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_6,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_7[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_inc_vr_by_1,
	[2] = llc_conn_ac_data_ind,
	[3] = llc_conn_ac_stop_p_समयr,
	[4] = llc_conn_ac_upd_nr_received,
	[5] = llc_conn_ac_upd_vs,
	[6] = llc_conn_ac_set_data_flag_0,
	[7] = llc_conn_ac_clear_remote_busy,
	[8] = llc_conn_ac_resend_i_xxx_x_set_0,
	[9] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_7 = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_7,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_8a[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_inc_vr_by_1,
	[2] = llc_conn_ac_data_ind,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_upd_vs,
	[5] = llc_conn_ac_set_data_flag_0,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_8a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_8a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_8b[] = अणु
	[0] = llc_conn_ac_opt_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_inc_vr_by_1,
	[2] = llc_conn_ac_data_ind,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_upd_vs,
	[5] = llc_conn_ac_set_data_flag_0,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_8b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_8b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_9[] = अणु
	[0] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[1] = llc_conn_ac_inc_vr_by_1,
	[2] = llc_conn_ac_data_ind,
	[3] = llc_conn_ac_upd_nr_received,
	[4] = llc_conn_ac_upd_vs,
	[5] = llc_conn_ac_set_data_flag_0,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_9 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_9,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_10a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_10a = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_10a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_10b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_10b = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_10b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_11a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_11a = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_11a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_11b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_11b = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_11b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_11c[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_11c = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_11c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_11d[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_11d = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_11d,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_12a[] = अणु
	[0] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_12a = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_12a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_12b[] = अणु
	[0] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_12b = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_12b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_13[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_set_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_13 = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_13,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_14a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_14a = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_14a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_14b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_14b = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_14b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_15[] = अणु
	[0] = llc_conn_ac_send_rnr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_set_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_15 = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_busy_actions_15,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_P_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_aरुको_busy_ev_qfyrs_16[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_aरुको_busy_actions_16[] = अणु
	[0] = llc_conn_ac_send_rnr_cmd_p_set_1,
	[1] = llc_conn_ac_start_p_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_busy_state_trans_16 = अणु
	.ev	       = llc_conn_ev_p_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = llc_aरुको_busy_ev_qfyrs_16,
	.ev_actions    = llc_aरुको_busy_actions_16,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_aरुको_busy_state_transitions[] = अणु
	 [0] = &llc_common_state_trans_1,		/* Request */
	 [1] = &llc_common_state_trans_2,
	 [2] = &llc_aरुको_busy_state_trans_1_0,
	 [3] = &llc_common_state_trans_end,
	 [4] = &llc_aरुको_busy_state_trans_1,		/* Local busy */
	 [5] = &llc_aरुको_busy_state_trans_2,
	 [6] = &llc_aरुको_busy_state_trans_3,
	 [7] = &llc_common_state_trans_end,
	 [8] = &llc_common_state_trans_end,		/* Initiate PF cycle */
	 [9] = &llc_common_state_trans_11a,		/* Timer */
	[10] = &llc_common_state_trans_11b,
	[11] = &llc_common_state_trans_11c,
	[12] = &llc_common_state_trans_11d,
	[13] = &llc_aरुको_busy_state_trans_16,
	[14] = &llc_common_state_trans_end,
	[15] = &llc_aरुको_busy_state_trans_4,		/* Receive frame */
	[16] = &llc_aरुको_busy_state_trans_5a,
	[17] = &llc_aरुको_busy_state_trans_5b,
	[18] = &llc_aरुको_busy_state_trans_6,
	[19] = &llc_aरुको_busy_state_trans_7,
	[20] = &llc_aरुको_busy_state_trans_8a,
	[21] = &llc_aरुको_busy_state_trans_8b,
	[22] = &llc_aरुको_busy_state_trans_9,
	[23] = &llc_aरुको_busy_state_trans_10a,
	[24] = &llc_aरुको_busy_state_trans_10b,
	[25] = &llc_aरुको_busy_state_trans_11a,
	[26] = &llc_aरुको_busy_state_trans_11b,
	[27] = &llc_aरुको_busy_state_trans_11c,
	[28] = &llc_aरुको_busy_state_trans_11d,
	[29] = &llc_aरुको_busy_state_trans_12a,
	[30] = &llc_aरुको_busy_state_trans_12b,
	[31] = &llc_aरुको_busy_state_trans_13,
	[32] = &llc_aरुको_busy_state_trans_14a,
	[33] = &llc_aरुको_busy_state_trans_14b,
	[34] = &llc_aरुको_busy_state_trans_15,
	[35] = &llc_common_state_trans_3,
	[36] = &llc_common_state_trans_4,
	[37] = &llc_common_state_trans_5,
	[38] = &llc_common_state_trans_6,
	[39] = &llc_common_state_trans_7a,
	[40] = &llc_common_state_trans_7b,
	[41] = &llc_common_state_trans_8a,
	[42] = &llc_common_state_trans_8b,
	[43] = &llc_common_state_trans_8c,
	[44] = &llc_common_state_trans_9,
	/* [45] = &llc_common_state_trans_10, */
	[45] = &llc_common_state_trans_end,
पूर्ण;

/* ----------------- LLC_CONN_STATE_AWAIT_REJ transitions --------------- */
/* State transitions क्रम LLC_CONN_EV_DATA_CONN_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_aरुको_reject_ev_qfyrs_1_0[] = अणु
	[0] = llc_conn_ev_qlfy_set_status_refuse,
	[1] = शून्य,
पूर्ण;

/* just one member, शून्य, .bss zeroes it */
अटल स्थिर llc_conn_action_t llc_aरुको_reject_actions_1_0[1];

अटल काष्ठा llc_conn_state_trans llc_aरुको_reject_state_trans_1_0 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = llc_aरुको_reject_ev_qfyrs_1_0,
	.ev_actions    = llc_aरुको_reject_actions_1_0,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_LOCAL_BUSY_DETECTED event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_1[] = अणु
	[0] = llc_conn_ac_send_rnr_xxx_x_set_0,
	[1] = llc_conn_ac_set_data_flag_2,
	[2] = शून्य
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_1 = अणु
	.ev	       = llc_conn_ev_local_busy_detected,
	.next_state    = LLC_CONN_STATE_AWAIT_BUSY,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_2a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = शून्य
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_2a = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_2a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_2b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = शून्य
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_2b = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0_unexpd_ns,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_2b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_3[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = शून्य
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_3 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_4[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_stop_rej_समयr,
	[4] = llc_conn_ac_upd_nr_received,
	[5] = llc_conn_ac_upd_vs,
	[6] = llc_conn_ac_resend_i_xxx_x_set_0_or_send_rr,
	[7] = llc_conn_ac_clear_remote_busy,
	[8] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_4 = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_5a[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_rr_xxx_x_set_0,
	[3] = llc_conn_ac_stop_rej_समयr,
	[4] = llc_conn_ac_upd_nr_received,
	[5] = llc_conn_ac_upd_vs,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_5a = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_5a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_5b[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_rr_xxx_x_set_0,
	[3] = llc_conn_ac_stop_rej_समयr,
	[4] = llc_conn_ac_upd_nr_received,
	[5] = llc_conn_ac_upd_vs,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_5b = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_5b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_6[] = अणु
	[0] = llc_conn_ac_inc_vr_by_1,
	[1] = llc_conn_ac_data_ind,
	[2] = llc_conn_ac_send_rr_rsp_f_set_1,
	[3] = llc_conn_ac_stop_rej_समयr,
	[4] = llc_conn_ac_upd_nr_received,
	[5] = llc_conn_ac_upd_vs,
	[6] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_6 = अणु
	.ev	       = llc_conn_ev_rx_i_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_6,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_7a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_7a = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_7a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_7b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_7b = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_7b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_I_RSP_Fbit_SET_1_UNEXPD_Ns event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_7c[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_resend_i_xxx_x_set_0,
	[4] = llc_conn_ac_clear_remote_busy,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_7c = अणु
	.ev	       = llc_conn_ev_rx_i_rsp_fbit_set_1_unexpd_ns,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_7c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_8a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_8a = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_8a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_8b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_8b = अणु
	.ev	       = llc_conn_ev_rx_rr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_8b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_8c[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_8c = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_8c,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_8d[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_clear_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_8d = अणु
	.ev	       = llc_conn_ev_rx_rej_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_8d,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_9a[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_9a = अणु
	.ev	       = llc_conn_ev_rx_rr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_9a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_9b[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_clear_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_9b = अणु
	.ev	       = llc_conn_ev_rx_rej_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_9b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_10[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_stop_p_समयr,
	[3] = llc_conn_ac_set_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_10 = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_1,
	.next_state    = LLC_CONN_STATE_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_10,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_11a[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_11a = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_11a,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_0 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_11b[] = अणु
	[0] = llc_conn_ac_upd_nr_received,
	[1] = llc_conn_ac_upd_vs,
	[2] = llc_conn_ac_set_remote_busy,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_11b = अणु
	.ev	       = llc_conn_ev_rx_rnr_rsp_fbit_set_0,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_11b,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_1 event */
अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_12[] = अणु
	[0] = llc_conn_ac_send_rr_rsp_f_set_1,
	[1] = llc_conn_ac_upd_nr_received,
	[2] = llc_conn_ac_upd_vs,
	[3] = llc_conn_ac_set_remote_busy,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_12 = अणु
	.ev	       = llc_conn_ev_rx_rnr_cmd_pbit_set_1,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_aरुको_rejct_actions_12,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_P_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_aरुको_rejct_ev_qfyrs_13[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_aरुको_rejct_actions_13[] = अणु
	[0] = llc_conn_ac_send_rej_cmd_p_set_1,
	[1] = llc_conn_ac_stop_p_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_aरुको_rejct_state_trans_13 = अणु
	.ev	       = llc_conn_ev_p_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_AWAIT_REJ,
	.ev_qualअगरiers = llc_aरुको_rejct_ev_qfyrs_13,
	.ev_actions    = llc_aरुको_rejct_actions_13,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_aरुको_rejct_state_transitions[] = अणु
	 [0] = &llc_aरुको_reject_state_trans_1_0,
	 [1] = &llc_common_state_trans_1,		/* requests */
	 [2] = &llc_common_state_trans_2,
	 [3] = &llc_common_state_trans_end,
	 [4] = &llc_aरुको_rejct_state_trans_1,		/* local busy */
	 [5] = &llc_common_state_trans_end,
	 [6] = &llc_common_state_trans_end,		/* Initiate PF cycle */
	 [7] = &llc_aरुको_rejct_state_trans_13,	/* समयrs */
	 [8] = &llc_common_state_trans_11a,
	 [9] = &llc_common_state_trans_11b,
	[10] = &llc_common_state_trans_11c,
	[11] = &llc_common_state_trans_11d,
	[12] = &llc_common_state_trans_end,
	[13] = &llc_aरुको_rejct_state_trans_2a,	/* receive frames */
	[14] = &llc_aरुको_rejct_state_trans_2b,
	[15] = &llc_aरुको_rejct_state_trans_3,
	[16] = &llc_aरुको_rejct_state_trans_4,
	[17] = &llc_aरुको_rejct_state_trans_5a,
	[18] = &llc_aरुको_rejct_state_trans_5b,
	[19] = &llc_aरुको_rejct_state_trans_6,
	[20] = &llc_aरुको_rejct_state_trans_7a,
	[21] = &llc_aरुको_rejct_state_trans_7b,
	[22] = &llc_aरुको_rejct_state_trans_7c,
	[23] = &llc_aरुको_rejct_state_trans_8a,
	[24] = &llc_aरुको_rejct_state_trans_8b,
	[25] = &llc_aरुको_rejct_state_trans_8c,
	[26] = &llc_aरुको_rejct_state_trans_8d,
	[27] = &llc_aरुको_rejct_state_trans_9a,
	[28] = &llc_aरुको_rejct_state_trans_9b,
	[29] = &llc_aरुको_rejct_state_trans_10,
	[30] = &llc_aरुको_rejct_state_trans_11a,
	[31] = &llc_aरुको_rejct_state_trans_11b,
	[32] = &llc_aरुको_rejct_state_trans_12,
	[33] = &llc_common_state_trans_3,
	[34] = &llc_common_state_trans_4,
	[35] = &llc_common_state_trans_5,
	[36] = &llc_common_state_trans_6,
	[37] = &llc_common_state_trans_7a,
	[38] = &llc_common_state_trans_7b,
	[39] = &llc_common_state_trans_8a,
	[40] = &llc_common_state_trans_8b,
	[41] = &llc_common_state_trans_8c,
	[42] = &llc_common_state_trans_9,
	/* [43] = &llc_common_state_trans_10, */
	[43] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_D_CONN transitions */
/* State transitions क्रम LLC_CONN_EV_RX_SABME_CMD_Pbit_SET_X event,
 * cause_flag = 1 */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_1[] = अणु
	[0] = llc_conn_ev_qlfy_cause_flag_eq_1,
	[1] = llc_conn_ev_qlfy_set_status_conflict,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_d_conn_actions_1[] = अणु
	[0] = llc_conn_ac_send_dm_rsp_f_set_p,
	[1] = llc_conn_ac_stop_ack_समयr,
	[2] = llc_conn_ac_disc_confirm,
	[3] = llc_conn_disc,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_1 = अणु
	.ev	       = llc_conn_ev_rx_sabme_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_1,
	.ev_actions    = llc_d_conn_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_SABME_CMD_Pbit_SET_X event,
 * cause_flag = 0
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_1_1[] = अणु
	[0] = llc_conn_ev_qlfy_cause_flag_eq_0,
	[1] = llc_conn_ev_qlfy_set_status_conflict,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_d_conn_actions_1_1[] = अणु
	[0] = llc_conn_ac_send_dm_rsp_f_set_p,
	[1] = llc_conn_ac_stop_ack_समयr,
	[2] = llc_conn_disc,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_1_1 = अणु
	.ev	       = llc_conn_ev_rx_sabme_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_1_1,
	.ev_actions    = llc_d_conn_actions_1_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_UA_RSP_Fbit_SET_X event,
 * cause_flag = 1
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_2[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = llc_conn_ev_qlfy_cause_flag_eq_1,
	[2] = llc_conn_ev_qlfy_set_status_disc,
	[3] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_d_conn_actions_2[] = अणु
	[0] = llc_conn_ac_stop_ack_समयr,
	[1] = llc_conn_ac_disc_confirm,
	[2] = llc_conn_disc,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_2 = अणु
	.ev	       = llc_conn_ev_rx_ua_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_2,
	.ev_actions    = llc_d_conn_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_UA_RSP_Fbit_SET_X event,
 * cause_flag = 0
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_2_1[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = llc_conn_ev_qlfy_cause_flag_eq_0,
	[2] = llc_conn_ev_qlfy_set_status_disc,
	[3] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_d_conn_actions_2_1[] = अणु
	[0] = llc_conn_ac_stop_ack_समयr,
	[1] = llc_conn_disc,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_2_1 = अणु
	.ev	       = llc_conn_ev_rx_ua_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_2_1,
	.ev_actions    = llc_d_conn_actions_2_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DISC_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_d_conn_actions_3[] = अणु
	[0] = llc_conn_ac_send_ua_rsp_f_set_p,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_3 = अणु
	.ev	       = llc_conn_ev_rx_disc_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_D_CONN,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_d_conn_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DM_RSP_Fbit_SET_X event,
 * cause_flag = 1
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_4[] = अणु
	[0] = llc_conn_ev_qlfy_cause_flag_eq_1,
	[1] = llc_conn_ev_qlfy_set_status_disc,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_d_conn_actions_4[] = अणु
	[0] = llc_conn_ac_stop_ack_समयr,
	[1] = llc_conn_ac_disc_confirm,
	[2] = llc_conn_disc,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_4 = अणु
	.ev	       = llc_conn_ev_rx_dm_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_4,
	.ev_actions    = llc_d_conn_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DM_RSP_Fbit_SET_X event,
 * cause_flag = 0
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_4_1[] = अणु
	[0] = llc_conn_ev_qlfy_cause_flag_eq_0,
	[1] = llc_conn_ev_qlfy_set_status_disc,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_d_conn_actions_4_1[] = अणु
	[0] = llc_conn_ac_stop_ack_समयr,
	[1] = llc_conn_disc,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_4_1 = अणु
	.ev	       = llc_conn_ev_rx_dm_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_4_1,
	.ev_actions    = llc_d_conn_actions_4_1,
पूर्ण;

/*
 * State transition क्रम
 * LLC_CONN_EV_DATA_CONN_REQ event
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_5[] = अणु
	[0] = llc_conn_ev_qlfy_set_status_refuse,
	[1] = शून्य,
पूर्ण;

/* just one member, शून्य, .bss zeroes it */
अटल स्थिर llc_conn_action_t llc_d_conn_actions_5[1];

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_5 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_D_CONN,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_5,
	.ev_actions    = llc_d_conn_actions_5,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_6[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_d_conn_actions_6[] = अणु
	[0] = llc_conn_ac_send_disc_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_6 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_D_CONN,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_6,
	.ev_actions    = llc_d_conn_actions_6,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event, cause_flag = 1 */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_7[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = llc_conn_ev_qlfy_cause_flag_eq_1,
	[2] = llc_conn_ev_qlfy_set_status_failed,
	[3] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_d_conn_actions_7[] = अणु
	[0] = llc_conn_ac_disc_confirm,
	[1] = llc_conn_disc,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_7 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_7,
	.ev_actions    = llc_d_conn_actions_7,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event, cause_flag = 0 */
अटल स्थिर llc_conn_ev_qfyr_t llc_d_conn_ev_qfyrs_8[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = llc_conn_ev_qlfy_cause_flag_eq_0,
	[2] = llc_conn_ev_qlfy_set_status_failed,
	[3] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_d_conn_actions_8[] = अणु
	[0] = llc_conn_disc,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_d_conn_state_trans_8 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_d_conn_ev_qfyrs_8,
	.ev_actions    = llc_d_conn_actions_8,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_d_conn_state_transitions[] = अणु
	 [0] = &llc_d_conn_state_trans_5,	/* Request */
	 [1] = &llc_common_state_trans_end,
	 [2] = &llc_common_state_trans_end,	/* Local busy */
	 [3] = &llc_common_state_trans_end,	/* Initiate PF cycle */
	 [4] = &llc_d_conn_state_trans_6,	/* Timer */
	 [5] = &llc_d_conn_state_trans_7,
	 [6] = &llc_d_conn_state_trans_8,
	 [7] = &llc_common_state_trans_end,
	 [8] = &llc_d_conn_state_trans_1,	/* Receive frame */
	 [9] = &llc_d_conn_state_trans_1_1,
	[10] = &llc_d_conn_state_trans_2,
	[11] = &llc_d_conn_state_trans_2_1,
	[12] = &llc_d_conn_state_trans_3,
	[13] = &llc_d_conn_state_trans_4,
	[14] = &llc_d_conn_state_trans_4_1,
	[15] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_RESET transitions */
/* State transitions क्रम LLC_CONN_EV_RX_SABME_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_rst_actions_1[] = अणु
	[0] = llc_conn_ac_set_vs_0,
	[1] = llc_conn_ac_set_vr_0,
	[2] = llc_conn_ac_set_s_flag_1,
	[3] = llc_conn_ac_send_ua_rsp_f_set_p,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_1 = अणु
	.ev	       = llc_conn_ev_rx_sabme_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_rst_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_UA_RSP_Fbit_SET_X event,
 * cause_flag = 1
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_2[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = llc_conn_ev_qlfy_cause_flag_eq_1,
	[2] = llc_conn_ev_qlfy_set_status_conn,
	[3] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_rst_actions_2[] = अणु
	[0] = llc_conn_ac_stop_ack_समयr,
	[1] = llc_conn_ac_set_vs_0,
	[2] = llc_conn_ac_set_vr_0,
	[3] = llc_conn_ac_upd_p_flag,
	[4] = llc_conn_ac_rst_confirm,
	[5] = llc_conn_ac_set_remote_busy_0,
	[6] = llc_conn_reset,
	[7] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_2 = अणु
	.ev	       = llc_conn_ev_rx_ua_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_2,
	.ev_actions    = llc_rst_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_UA_RSP_Fbit_SET_X event,
 * cause_flag = 0
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_2_1[] = अणु
	[0] = llc_conn_ev_qlfy_p_flag_eq_f,
	[1] = llc_conn_ev_qlfy_cause_flag_eq_0,
	[2] = llc_conn_ev_qlfy_set_status_rst_करोne,
	[3] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_rst_actions_2_1[] = अणु
	[0] = llc_conn_ac_stop_ack_समयr,
	[1] = llc_conn_ac_set_vs_0,
	[2] = llc_conn_ac_set_vr_0,
	[3] = llc_conn_ac_upd_p_flag,
	[4] = llc_conn_ac_rst_confirm,
	[5] = llc_conn_ac_set_remote_busy_0,
	[6] = llc_conn_reset,
	[7] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_2_1 = अणु
	.ev	       = llc_conn_ev_rx_ua_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_2_1,
	.ev_actions    = llc_rst_actions_2_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_3[] = अणु
	[0] = llc_conn_ev_qlfy_s_flag_eq_1,
	[1] = llc_conn_ev_qlfy_set_status_rst_करोne,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_rst_actions_3[] = अणु
	[0] = llc_conn_ac_set_p_flag_0,
	[1] = llc_conn_ac_set_remote_busy_0,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_3 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_3,
	.ev_actions    = llc_rst_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DISC_CMD_Pbit_SET_X event,
 * cause_flag = 1
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_4[] = अणु
	[0] = llc_conn_ev_qlfy_cause_flag_eq_1,
	[1] = llc_conn_ev_qlfy_set_status_disc,
	[2] = शून्य,
पूर्ण;
अटल स्थिर llc_conn_action_t llc_rst_actions_4[] = अणु
	[0] = llc_conn_ac_send_dm_rsp_f_set_p,
	[1] = llc_conn_ac_disc_ind,
	[2] = llc_conn_ac_stop_ack_समयr,
	[3] = llc_conn_disc,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_4 = अणु
	.ev	       = llc_conn_ev_rx_disc_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_4,
	.ev_actions    = llc_rst_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DISC_CMD_Pbit_SET_X event,
 * cause_flag = 0
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_4_1[] = अणु
	[0] = llc_conn_ev_qlfy_cause_flag_eq_0,
	[1] = llc_conn_ev_qlfy_set_status_refuse,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_rst_actions_4_1[] = अणु
	[0] = llc_conn_ac_send_dm_rsp_f_set_p,
	[1] = llc_conn_ac_stop_ack_समयr,
	[2] = llc_conn_disc,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_4_1 = अणु
	.ev	       = llc_conn_ev_rx_disc_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_4_1,
	.ev_actions    = llc_rst_actions_4_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DM_RSP_Fbit_SET_X event,
 * cause_flag = 1
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_5[] = अणु
	[0] = llc_conn_ev_qlfy_cause_flag_eq_1,
	[1] = llc_conn_ev_qlfy_set_status_disc,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_rst_actions_5[] = अणु
	[0] = llc_conn_ac_disc_ind,
	[1] = llc_conn_ac_stop_ack_समयr,
	[2] = llc_conn_disc,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_5 = अणु
	.ev	       = llc_conn_ev_rx_dm_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_5,
	.ev_actions    = llc_rst_actions_5,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DM_RSP_Fbit_SET_X event,
 * cause_flag = 0
 */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_5_1[] = अणु
	[0] = llc_conn_ev_qlfy_cause_flag_eq_0,
	[1] = llc_conn_ev_qlfy_set_status_refuse,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_rst_actions_5_1[] = अणु
	[0] = llc_conn_ac_stop_ack_समयr,
	[1] = llc_conn_disc,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_5_1 = अणु
	.ev	       = llc_conn_ev_rx_dm_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_5_1,
	.ev_actions    = llc_rst_actions_5_1,
पूर्ण;

/* State transitions क्रम DATA_CONN_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_6[] = अणु
	[0] = llc_conn_ev_qlfy_set_status_refuse,
	[1] = शून्य,
पूर्ण;

/* just one member, शून्य, .bss zeroes it */
अटल स्थिर llc_conn_action_t llc_rst_actions_6[1];

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_6 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_6,
	.ev_actions    = llc_rst_actions_6,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_7[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = llc_conn_ev_qlfy_s_flag_eq_0,
	[2] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_rst_actions_7[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_7 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_7,
	.ev_actions    = llc_rst_actions_7,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_8[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = llc_conn_ev_qlfy_s_flag_eq_0,
	[2] = llc_conn_ev_qlfy_cause_flag_eq_1,
	[3] = llc_conn_ev_qlfy_set_status_failed,
	[4] = शून्य,
पूर्ण;
अटल स्थिर llc_conn_action_t llc_rst_actions_8[] = अणु
	[0] = llc_conn_ac_disc_ind,
	[1] = llc_conn_disc,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_8 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_8,
	.ev_actions    = llc_rst_actions_8,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_rst_ev_qfyrs_8_1[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = llc_conn_ev_qlfy_s_flag_eq_0,
	[2] = llc_conn_ev_qlfy_cause_flag_eq_0,
	[3] = llc_conn_ev_qlfy_set_status_failed,
	[4] = शून्य,
पूर्ण;
अटल स्थिर llc_conn_action_t llc_rst_actions_8_1[] = अणु
	[0] = llc_conn_ac_disc_ind,
	[1] = llc_conn_disc,
	[2] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_rst_state_trans_8_1 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = llc_rst_ev_qfyrs_8_1,
	.ev_actions    = llc_rst_actions_8_1,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_rst_state_transitions[] = अणु
	 [0] = &llc_rst_state_trans_6,		/* Request */
	 [1] = &llc_common_state_trans_end,
	 [2] = &llc_common_state_trans_end,	/* Local busy */
	 [3] = &llc_common_state_trans_end,	/* Initiate PF cycle */
	 [4] = &llc_rst_state_trans_3,		/* Timer */
	 [5] = &llc_rst_state_trans_7,
	 [6] = &llc_rst_state_trans_8,
	 [7] = &llc_rst_state_trans_8_1,
	 [8] = &llc_common_state_trans_end,
	 [9] = &llc_rst_state_trans_1,		/* Receive frame */
	[10] = &llc_rst_state_trans_2,
	[11] = &llc_rst_state_trans_2_1,
	[12] = &llc_rst_state_trans_4,
	[13] = &llc_rst_state_trans_4_1,
	[14] = &llc_rst_state_trans_5,
	[15] = &llc_rst_state_trans_5_1,
	[16] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_ERROR transitions */
/* State transitions क्रम LLC_CONN_EV_RX_SABME_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_error_actions_1[] = अणु
	[0] = llc_conn_ac_set_vs_0,
	[1] = llc_conn_ac_set_vr_0,
	[2] = llc_conn_ac_send_ua_rsp_f_set_p,
	[3] = llc_conn_ac_rst_ind,
	[4] = llc_conn_ac_set_p_flag_0,
	[5] = llc_conn_ac_set_remote_busy_0,
	[6] = llc_conn_ac_stop_ack_समयr,
	[7] = llc_conn_reset,
	[8] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_error_state_trans_1 = अणु
	.ev	       = llc_conn_ev_rx_sabme_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_NORMAL,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_error_actions_1,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DISC_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_error_actions_2[] = अणु
	[0] = llc_conn_ac_send_ua_rsp_f_set_p,
	[1] = llc_conn_ac_disc_ind,
	[2] = llc_conn_ac_stop_ack_समयr,
	[3] = llc_conn_disc,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_error_state_trans_2 = अणु
	.ev	       = llc_conn_ev_rx_disc_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_error_actions_2,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_DM_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_error_actions_3[] = अणु
	[0] = llc_conn_ac_disc_ind,
	[1] = llc_conn_ac_stop_ack_समयr,
	[2] = llc_conn_disc,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_error_state_trans_3 = अणु
	.ev	       = llc_conn_ev_rx_dm_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_error_actions_3,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_FRMR_RSP_Fbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_error_actions_4[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_set_retry_cnt_0,
	[3] = llc_conn_ac_set_cause_flag_0,
	[4] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_error_state_trans_4 = अणु
	.ev	       = llc_conn_ev_rx_frmr_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_error_actions_4,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_XXX_CMD_Pbit_SET_X event */
अटल स्थिर llc_conn_action_t llc_error_actions_5[] = अणु
	[0] = llc_conn_ac_resend_frmr_rsp_f_set_p,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_error_state_trans_5 = अणु
	.ev	       = llc_conn_ev_rx_xxx_cmd_pbit_set_x,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_error_actions_5,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_RX_XXX_RSP_Fbit_SET_X event */
अटल काष्ठा llc_conn_state_trans llc_error_state_trans_6 = अणु
	.ev	       = llc_conn_ev_rx_xxx_rsp_fbit_set_x,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = NONE,
	.ev_actions    = NONE,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_error_ev_qfyrs_7[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_lt_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_error_actions_7[] = अणु
	[0] = llc_conn_ac_resend_frmr_rsp_f_set_0,
	[1] = llc_conn_ac_start_ack_समयr,
	[2] = llc_conn_ac_inc_retry_cnt_by_1,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_error_state_trans_7 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = llc_error_ev_qfyrs_7,
	.ev_actions    = llc_error_actions_7,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_ACK_TMR_EXP event */
अटल स्थिर llc_conn_ev_qfyr_t llc_error_ev_qfyrs_8[] = अणु
	[0] = llc_conn_ev_qlfy_retry_cnt_gte_n2,
	[1] = शून्य,
पूर्ण;

अटल स्थिर llc_conn_action_t llc_error_actions_8[] = अणु
	[0] = llc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = llc_conn_ac_set_s_flag_0,
	[2] = llc_conn_ac_start_ack_समयr,
	[3] = llc_conn_ac_set_retry_cnt_0,
	[4] = llc_conn_ac_set_cause_flag_0,
	[5] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_error_state_trans_8 = अणु
	.ev	       = llc_conn_ev_ack_पंचांगr_exp,
	.next_state    = LLC_CONN_STATE_RESET,
	.ev_qualअगरiers = llc_error_ev_qfyrs_8,
	.ev_actions    = llc_error_actions_8,
पूर्ण;

/* State transitions क्रम LLC_CONN_EV_DATA_CONN_REQ event */
अटल स्थिर llc_conn_ev_qfyr_t llc_error_ev_qfyrs_9[] = अणु
	[0] = llc_conn_ev_qlfy_set_status_refuse,
	[1] = शून्य,
पूर्ण;

/* just one member, शून्य, .bss zeroes it */
अटल स्थिर llc_conn_action_t llc_error_actions_9[1];

अटल काष्ठा llc_conn_state_trans llc_error_state_trans_9 = अणु
	.ev	       = llc_conn_ev_data_req,
	.next_state    = LLC_CONN_STATE_ERROR,
	.ev_qualअगरiers = llc_error_ev_qfyrs_9,
	.ev_actions    = llc_error_actions_9,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_error_state_transitions[] = अणु
	 [0] = &llc_error_state_trans_9,	/* Request */
	 [1] = &llc_common_state_trans_end,
	 [2] = &llc_common_state_trans_end,	/* Local busy */
	 [3] = &llc_common_state_trans_end,	/* Initiate PF cycle */
	 [4] = &llc_error_state_trans_7,	/* Timer */
	 [5] = &llc_error_state_trans_8,
	 [6] = &llc_common_state_trans_end,
	 [7] = &llc_error_state_trans_1,	/* Receive frame */
	 [8] = &llc_error_state_trans_2,
	 [9] = &llc_error_state_trans_3,
	[10] = &llc_error_state_trans_4,
	[11] = &llc_error_state_trans_5,
	[12] = &llc_error_state_trans_6,
	[13] = &llc_common_state_trans_end,
पूर्ण;

/* LLC_CONN_STATE_TEMP transitions */
/* State transitions क्रम LLC_CONN_EV_DISC_REQ event */
अटल स्थिर llc_conn_action_t llc_temp_actions_1[] = अणु
	[0] = llc_conn_ac_stop_all_समयrs,
	[1] = llc_conn_ac_send_disc_cmd_p_set_x,
	[2] = llc_conn_disc,
	[3] = शून्य,
पूर्ण;

अटल काष्ठा llc_conn_state_trans llc_temp_state_trans_1 = अणु
	.ev	       = llc_conn_ev_disc_req,
	.next_state    = LLC_CONN_STATE_ADM,
	.ev_qualअगरiers = NONE,
	.ev_actions    = llc_temp_actions_1,
पूर्ण;

/*
 * Array of poपूर्णांकers;
 * one to each transition
 */
अटल काष्ठा llc_conn_state_trans *llc_temp_state_transitions[] = अणु
	[0] = &llc_temp_state_trans_1,		/* requests */
	[1] = &llc_common_state_trans_end,
	[2] = &llc_common_state_trans_end,	/* local busy */
	[3] = &llc_common_state_trans_end,	/* init_pf_cycle */
	[4] = &llc_common_state_trans_end,	/* समयr */
	[5] = &llc_common_state_trans_end,	/* receive */
पूर्ण;

/* Connection State Transition Table */
काष्ठा llc_conn_state llc_conn_state_table[NBR_CONN_STATES] = अणु
	[LLC_CONN_STATE_ADM - 1] = अणु
		.current_state	= LLC_CONN_STATE_ADM,
		.transitions	= llc_adm_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_SETUP - 1] = अणु
		.current_state	= LLC_CONN_STATE_SETUP,
		.transitions	= llc_setup_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_NORMAL - 1] = अणु
		.current_state	= LLC_CONN_STATE_NORMAL,
		.transitions	= llc_normal_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_BUSY - 1] = अणु
		.current_state	= LLC_CONN_STATE_BUSY,
		.transitions	= llc_busy_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_REJ - 1] = अणु
		.current_state	= LLC_CONN_STATE_REJ,
		.transitions	= llc_reject_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_AWAIT - 1] = अणु
		.current_state	= LLC_CONN_STATE_AWAIT,
		.transitions	= llc_aरुको_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_AWAIT_BUSY - 1] = अणु
		.current_state	= LLC_CONN_STATE_AWAIT_BUSY,
		.transitions	= llc_aरुको_busy_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_AWAIT_REJ - 1] = अणु
		.current_state	= LLC_CONN_STATE_AWAIT_REJ,
		.transitions	= llc_aरुको_rejct_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_D_CONN - 1] = अणु
		.current_state	= LLC_CONN_STATE_D_CONN,
		.transitions	= llc_d_conn_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_RESET - 1] = अणु
		.current_state	= LLC_CONN_STATE_RESET,
		.transitions	= llc_rst_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_ERROR - 1] = अणु
		.current_state	= LLC_CONN_STATE_ERROR,
		.transitions	= llc_error_state_transitions,
	पूर्ण,
	[LLC_CONN_STATE_TEMP - 1] = अणु
		.current_state	= LLC_CONN_STATE_TEMP,
		.transitions	= llc_temp_state_transitions,
	पूर्ण,
पूर्ण;
