<शैली गुरु>
#अगर_अघोषित LLC_C_EV_H
#घोषणा LLC_C_EV_H
/*
 * Copyright (c) 1997 by Procom Technology,Inc.
 *		 2001 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */

#समावेश <net/sock.h>

/* Connection component state transition event qualअगरiers */
/* Types of events (possible values in 'ev->type') */
#घोषणा LLC_CONN_EV_TYPE_SIMPLE		 1
#घोषणा LLC_CONN_EV_TYPE_CONDITION	 2
#घोषणा LLC_CONN_EV_TYPE_PRIM		 3
#घोषणा LLC_CONN_EV_TYPE_PDU		 4	/* command/response PDU */
#घोषणा LLC_CONN_EV_TYPE_ACK_TMR	 5
#घोषणा LLC_CONN_EV_TYPE_P_TMR		 6
#घोषणा LLC_CONN_EV_TYPE_REJ_TMR	 7
#घोषणा LLC_CONN_EV_TYPE_BUSY_TMR	 8
#घोषणा LLC_CONN_EV_TYPE_RPT_STATUS	 9
#घोषणा LLC_CONN_EV_TYPE_SENDACK_TMR	10

#घोषणा NBR_CONN_EV		   5
/* Connection events which cause state transitions when fully qualअगरied */

#घोषणा LLC_CONN_EV_CONN_REQ				 1
#घोषणा LLC_CONN_EV_CONN_RESP				 2
#घोषणा LLC_CONN_EV_DATA_REQ				 3
#घोषणा LLC_CONN_EV_DISC_REQ				 4
#घोषणा LLC_CONN_EV_RESET_REQ				 5
#घोषणा LLC_CONN_EV_RESET_RESP				 6
#घोषणा LLC_CONN_EV_LOCAL_BUSY_DETECTED			 7
#घोषणा LLC_CONN_EV_LOCAL_BUSY_CLEARED			 8
#घोषणा LLC_CONN_EV_RX_BAD_PDU				 9
#घोषणा LLC_CONN_EV_RX_DISC_CMD_Pbit_SET_X		10
#घोषणा LLC_CONN_EV_RX_DM_RSP_Fbit_SET_X		11
#घोषणा LLC_CONN_EV_RX_FRMR_RSP_Fbit_SET_X		12
#घोषणा LLC_CONN_EV_RX_I_CMD_Pbit_SET_X			13
#घोषणा LLC_CONN_EV_RX_I_CMD_Pbit_SET_X_UNEXPD_Ns	14
#घोषणा LLC_CONN_EV_RX_I_CMD_Pbit_SET_X_INVAL_Ns	15
#घोषणा LLC_CONN_EV_RX_I_RSP_Fbit_SET_X			16
#घोषणा LLC_CONN_EV_RX_I_RSP_Fbit_SET_X_UNEXPD_Ns	17
#घोषणा LLC_CONN_EV_RX_I_RSP_Fbit_SET_X_INVAL_Ns	18
#घोषणा LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_X		19
#घोषणा LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_X		20
#घोषणा LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_X		21
#घोषणा LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_X		22
#घोषणा LLC_CONN_EV_RX_RR_CMD_Pbit_SET_X		23
#घोषणा LLC_CONN_EV_RX_RR_RSP_Fbit_SET_X		24
#घोषणा LLC_CONN_EV_RX_SABME_CMD_Pbit_SET_X		25
#घोषणा LLC_CONN_EV_RX_UA_RSP_Fbit_SET_X		26
#घोषणा LLC_CONN_EV_RX_XXX_CMD_Pbit_SET_X		27
#घोषणा LLC_CONN_EV_RX_XXX_RSP_Fbit_SET_X		28
#घोषणा LLC_CONN_EV_RX_XXX_YYY				29
#घोषणा LLC_CONN_EV_RX_ZZZ_CMD_Pbit_SET_X_INVAL_Nr	30
#घोषणा LLC_CONN_EV_RX_ZZZ_RSP_Fbit_SET_X_INVAL_Nr	31
#घोषणा LLC_CONN_EV_P_TMR_EXP				32
#घोषणा LLC_CONN_EV_ACK_TMR_EXP				33
#घोषणा LLC_CONN_EV_REJ_TMR_EXP				34
#घोषणा LLC_CONN_EV_BUSY_TMR_EXP			35
#घोषणा LLC_CONN_EV_RX_XXX_CMD_Pbit_SET_1		36
#घोषणा LLC_CONN_EV_RX_XXX_CMD_Pbit_SET_0		37
#घोषणा LLC_CONN_EV_RX_I_CMD_Pbit_SET_0_UNEXPD_Ns	38
#घोषणा LLC_CONN_EV_RX_I_RSP_Fbit_SET_0_UNEXPD_Ns	39
#घोषणा LLC_CONN_EV_RX_I_RSP_Fbit_SET_1_UNEXPD_Ns	40
#घोषणा LLC_CONN_EV_RX_I_CMD_Pbit_SET_1_UNEXPD_Ns	41
#घोषणा LLC_CONN_EV_RX_I_CMD_Pbit_SET_0			42
#घोषणा LLC_CONN_EV_RX_I_RSP_Fbit_SET_0			43
#घोषणा LLC_CONN_EV_RX_I_CMD_Pbit_SET_1			44
#घोषणा LLC_CONN_EV_RX_RR_CMD_Pbit_SET_0		45
#घोषणा LLC_CONN_EV_RX_RR_RSP_Fbit_SET_0		46
#घोषणा LLC_CONN_EV_RX_RR_RSP_Fbit_SET_1		47
#घोषणा LLC_CONN_EV_RX_RR_CMD_Pbit_SET_1		48
#घोषणा LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_0		49
#घोषणा LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_0		50
#घोषणा LLC_CONN_EV_RX_RNR_RSP_Fbit_SET_1		51
#घोषणा LLC_CONN_EV_RX_RNR_CMD_Pbit_SET_1		52
#घोषणा LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_0		53
#घोषणा LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_0		54
#घोषणा LLC_CONN_EV_RX_REJ_CMD_Pbit_SET_1		55
#घोषणा LLC_CONN_EV_RX_I_RSP_Fbit_SET_1			56
#घोषणा LLC_CONN_EV_RX_REJ_RSP_Fbit_SET_1		57
#घोषणा LLC_CONN_EV_RX_XXX_RSP_Fbit_SET_1		58
#घोषणा LLC_CONN_EV_TX_BUFF_FULL			59

#घोषणा LLC_CONN_EV_INIT_P_F_CYCLE			100
/*
 * Connection event qualअगरiers; क्रम some events a certain combination of
 * these qualअगरiers must be TRUE beक्रमe event recognized valid क्रम state;
 * these स्थिरants act as indexes पूर्णांकo the Event Qualअगरier function
 * table
 */
#घोषणा LLC_CONN_EV_QFY_DATA_FLAG_EQ_1		 1
#घोषणा LLC_CONN_EV_QFY_DATA_FLAG_EQ_0		 2
#घोषणा LLC_CONN_EV_QFY_DATA_FLAG_EQ_2		 3
#घोषणा LLC_CONN_EV_QFY_P_FLAG_EQ_1		 4
#घोषणा LLC_CONN_EV_QFY_P_FLAG_EQ_0		 5
#घोषणा LLC_CONN_EV_QFY_P_FLAG_EQ_Fbit		 6
#घोषणा LLC_CONN_EV_QFY_REMOTE_BUSY_EQ_0	 7
#घोषणा LLC_CONN_EV_QFY_RETRY_CNT_LT_N2		 8
#घोषणा LLC_CONN_EV_QFY_RETRY_CNT_GTE_N2	 9
#घोषणा LLC_CONN_EV_QFY_S_FLAG_EQ_1		10
#घोषणा LLC_CONN_EV_QFY_S_FLAG_EQ_0		11
#घोषणा LLC_CONN_EV_QFY_INIT_P_F_CYCLE		12

काष्ठा llc_conn_state_ev अणु
	u8 type;
	u8 prim;
	u8 prim_type;
	u8 reason;
	u8 status;
	u8 ind_prim;
	u8 cfm_prim;
पूर्ण;

अटल __अंतरभूत__ काष्ठा llc_conn_state_ev *llc_conn_ev(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा llc_conn_state_ev *)skb->cb;
पूर्ण

प्रकार पूर्णांक (*llc_conn_ev_t)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
प्रकार पूर्णांक (*llc_conn_ev_qfyr_t)(काष्ठा sock *sk, काष्ठा sk_buff *skb);

पूर्णांक llc_conn_ev_conn_req(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_data_req(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_disc_req(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rst_req(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_local_busy_detected(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_local_busy_cleared(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_bad_pdu(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_disc_cmd_pbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_dm_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_frmr_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_x_inval_ns(काष्ठा sock *sk,
					     काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_x_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_x_inval_ns(काष्ठा sock *sk,
					     काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rej_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_sabme_cmd_pbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_ua_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_xxx_cmd_pbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_xxx_rsp_fbit_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_zzz_cmd_pbit_set_x_inval_nr(काष्ठा sock *sk,
					       काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_zzz_rsp_fbit_set_x_inval_nr(काष्ठा sock *sk,
					       काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_p_पंचांगr_exp(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_ack_पंचांगr_exp(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rej_पंचांगr_exp(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_busy_पंचांगr_exp(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_sendack_पंचांगr_exp(काष्ठा sock *sk, काष्ठा sk_buff *skb);
/* NOT_USED functions and their variations */
पूर्णांक llc_conn_ev_rx_xxx_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_xxx_rsp_fbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_0_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_1_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_0_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_1_unexpd_ns(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_i_rsp_fbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rr_cmd_pbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rr_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rr_rsp_fbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rr_rsp_fbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rnr_cmd_pbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rnr_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rnr_rsp_fbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rnr_rsp_fbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rej_cmd_pbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rej_cmd_pbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rej_rsp_fbit_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_rej_rsp_fbit_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_rx_any_frame(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_tx_buffer_full(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_init_p_f_cycle(काष्ठा sock *sk, काष्ठा sk_buff *skb);

/* Available connection action qualअगरiers */
पूर्णांक llc_conn_ev_qlfy_data_flag_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_data_flag_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_data_flag_eq_2(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_p_flag_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_last_frame_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_last_frame_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_p_flag_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_p_flag_eq_f(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_remote_busy_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_remote_busy_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_retry_cnt_lt_n2(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_retry_cnt_gte_n2(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_s_flag_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_s_flag_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_cause_flag_eq_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_cause_flag_eq_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_set_status_conn(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_set_status_disc(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_set_status_failed(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_set_status_remote_busy(काष्ठा sock *sk,
					    काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_set_status_refuse(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_set_status_conflict(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ev_qlfy_set_status_rst_करोne(काष्ठा sock *sk, काष्ठा sk_buff *skb);

अटल __अंतरभूत__ पूर्णांक llc_conn_space(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस atomic_पढ़ो(&sk->sk_rmem_alloc) + skb->truesize <
	       (अचिन्हित पूर्णांक)sk->sk_rcvbuf;
पूर्ण
#पूर्ण_अगर /* LLC_C_EV_H */
