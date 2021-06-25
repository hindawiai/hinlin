<शैली गुरु>
#अगर_अघोषित LLC_C_AC_H
#घोषणा LLC_C_AC_H
/*
 * Copyright (c) 1997 by Procom Technology,Inc.
 * 		 2001 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
/* Connection component state transition actions */
/*
 * Connection state transition actions
 * (Fb = F bit; Pb = P bit; Xb = X bit)
 */
#घोषणा LLC_CONN_AC_CLR_REMOTE_BUSY			 1
#घोषणा LLC_CONN_AC_CONN_IND				 2
#घोषणा LLC_CONN_AC_CONN_CONFIRM			 3
#घोषणा LLC_CONN_AC_DATA_IND				 4
#घोषणा LLC_CONN_AC_DISC_IND				 5
#घोषणा LLC_CONN_AC_RESET_IND				 6
#घोषणा LLC_CONN_AC_RESET_CONFIRM			 7
#घोषणा LLC_CONN_AC_REPORT_STATUS			 8
#घोषणा LLC_CONN_AC_CLR_REMOTE_BUSY_IF_Fb_EQ_1		 9
#घोषणा LLC_CONN_AC_STOP_REJ_TMR_IF_DATA_FLAG_EQ_2	10
#घोषणा LLC_CONN_AC_SEND_DISC_CMD_Pb_SET_X		11
#घोषणा LLC_CONN_AC_SEND_DM_RSP_Fb_SET_Pb		12
#घोषणा LLC_CONN_AC_SEND_DM_RSP_Fb_SET_1		13
#घोषणा LLC_CONN_AC_SEND_DM_RSP_Fb_SET_F_FLAG		14
#घोषणा LLC_CONN_AC_SEND_FRMR_RSP_Fb_SET_X		15
#घोषणा LLC_CONN_AC_RESEND_FRMR_RSP_Fb_SET_0		16
#घोषणा LLC_CONN_AC_RESEND_FRMR_RSP_Fb_SET_Pb		17
#घोषणा LLC_CONN_AC_SEND_I_CMD_Pb_SET_1			18
#घोषणा LLC_CONN_AC_RESEND_I_CMD_Pb_SET_1		19
#घोषणा LLC_CONN_AC_RESEND_I_CMD_Pb_SET_1_OR_SEND_RR	20
#घोषणा LLC_CONN_AC_SEND_I_XXX_Xb_SET_0			21
#घोषणा LLC_CONN_AC_RESEND_I_XXX_Xb_SET_0		22
#घोषणा LLC_CONN_AC_RESEND_I_XXX_Xb_SET_0_OR_SEND_RR	23
#घोषणा LLC_CONN_AC_RESEND_I_RSP_Fb_SET_1		24
#घोषणा LLC_CONN_AC_SEND_REJ_CMD_Pb_SET_1		25
#घोषणा LLC_CONN_AC_SEND_REJ_RSP_Fb_SET_1		26
#घोषणा LLC_CONN_AC_SEND_REJ_XXX_Xb_SET_0		27
#घोषणा LLC_CONN_AC_SEND_RNR_CMD_Pb_SET_1		28
#घोषणा LLC_CONN_AC_SEND_RNR_RSP_Fb_SET_1		29
#घोषणा LLC_CONN_AC_SEND_RNR_XXX_Xb_SET_0		30
#घोषणा LLC_CONN_AC_SET_REMOTE_BUSY			31
#घोषणा LLC_CONN_AC_OPTIONAL_SEND_RNR_XXX_Xb_SET_0	32
#घोषणा LLC_CONN_AC_SEND_RR_CMD_Pb_SET_1		33
#घोषणा LLC_CONN_AC_SEND_ACK_CMD_Pb_SET_1		34
#घोषणा LLC_CONN_AC_SEND_RR_RSP_Fb_SET_1		35
#घोषणा LLC_CONN_AC_SEND_ACK_RSP_Fb_SET_1		36
#घोषणा LLC_CONN_AC_SEND_RR_XXX_Xb_SET_0		37
#घोषणा LLC_CONN_AC_SEND_ACK_XXX_Xb_SET_0		38
#घोषणा LLC_CONN_AC_SEND_SABME_CMD_Pb_SET_X		39
#घोषणा LLC_CONN_AC_SEND_UA_RSP_Fb_SET_Pb		40
#घोषणा LLC_CONN_AC_SEND_UA_RSP_Fb_SET_F_FLAG		41
#घोषणा LLC_CONN_AC_S_FLAG_SET_0			42
#घोषणा LLC_CONN_AC_S_FLAG_SET_1			43
#घोषणा LLC_CONN_AC_START_P_TMR				44
#घोषणा LLC_CONN_AC_START_ACK_TMR			45
#घोषणा LLC_CONN_AC_START_REJ_TMR			46
#घोषणा LLC_CONN_AC_START_ACK_TMR_IF_NOT_RUNNING	47
#घोषणा LLC_CONN_AC_STOP_ACK_TMR			48
#घोषणा LLC_CONN_AC_STOP_P_TMR				49
#घोषणा LLC_CONN_AC_STOP_REJ_TMR			50
#घोषणा LLC_CONN_AC_STOP_ALL_TMRS			51
#घोषणा LLC_CONN_AC_STOP_OTHER_TMRS			52
#घोषणा LLC_CONN_AC_UPDATE_Nr_RECEIVED			53
#घोषणा LLC_CONN_AC_UPDATE_P_FLAG			54
#घोषणा LLC_CONN_AC_DATA_FLAG_SET_2			55
#घोषणा LLC_CONN_AC_DATA_FLAG_SET_0			56
#घोषणा LLC_CONN_AC_DATA_FLAG_SET_1			57
#घोषणा LLC_CONN_AC_DATA_FLAG_SET_1_IF_DATA_FLAG_EQ_0	58
#घोषणा LLC_CONN_AC_P_FLAG_SET_0			59
#घोषणा LLC_CONN_AC_P_FLAG_SET_P			60
#घोषणा LLC_CONN_AC_REMOTE_BUSY_SET_0			61
#घोषणा LLC_CONN_AC_RETRY_CNT_SET_0			62
#घोषणा LLC_CONN_AC_RETRY_CNT_INC_BY_1			63
#घोषणा LLC_CONN_AC_Vr_SET_0				64
#घोषणा LLC_CONN_AC_Vr_INC_BY_1				65
#घोषणा LLC_CONN_AC_Vs_SET_0				66
#घोषणा LLC_CONN_AC_Vs_SET_Nr				67
#घोषणा LLC_CONN_AC_F_FLAG_SET_P			68
#घोषणा LLC_CONN_AC_STOP_SENDACK_TMR			70
#घोषणा LLC_CONN_AC_START_SENDACK_TMR_IF_NOT_RUNNING	71

प्रकार पूर्णांक (*llc_conn_action_t)(काष्ठा sock *sk, काष्ठा sk_buff *skb);

पूर्णांक llc_conn_ac_clear_remote_busy(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_conn_ind(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_conn_confirm(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_data_ind(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_disc_ind(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_rst_ind(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_rst_confirm(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_clear_remote_busy_अगर_f_eq_1(काष्ठा sock *sk,
					    काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_stop_rej_पंचांगr_अगर_data_flag_eq_2(काष्ठा sock *sk,
					       काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_disc_cmd_p_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_dm_rsp_f_set_p(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_dm_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_frmr_rsp_f_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_resend_frmr_rsp_f_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_resend_frmr_rsp_f_set_p(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_i_cmd_p_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_i_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_resend_i_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_resend_i_xxx_x_set_0_or_send_rr(काष्ठा sock *sk,
						काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_resend_i_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_rej_cmd_p_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_rej_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_rej_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_rnr_cmd_p_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_rnr_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_rnr_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_remote_busy(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_opt_send_rnr_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_rr_cmd_p_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_rr_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_ack_rsp_f_set_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_rr_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_ack_xxx_x_set_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_sabme_cmd_p_set_x(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_ua_rsp_f_set_p(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_s_flag_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_s_flag_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_start_p_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_start_ack_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_start_rej_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_start_ack_पंचांगr_अगर_not_running(काष्ठा sock *sk,
					     काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_stop_ack_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_stop_p_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_stop_rej_समयr(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_stop_all_समयrs(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_stop_other_समयrs(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_upd_nr_received(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_inc_tx_win_size(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_dec_tx_win_size(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_upd_p_flag(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_data_flag_2(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_data_flag_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_data_flag_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_data_flag_1_अगर_data_flag_eq_0(काष्ठा sock *sk,
						  काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_p_flag_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_remote_busy_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_retry_cnt_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_cause_flag_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_cause_flag_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_inc_retry_cnt_by_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_vr_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_inc_vr_by_1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_vs_0(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_set_vs_nr(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_rst_vs(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_upd_vs(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_disc(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_reset(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_disc_confirm(काष्ठा sock *sk, काष्ठा sk_buff *skb);
u8 llc_circular_between(u8 a, u8 b, u8 c);
पूर्णांक llc_conn_ac_send_ack_अगर_needed(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_adjust_npta_by_rr(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_adjust_npta_by_rnr(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_rst_sendack_flag(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_i_rsp_as_ack(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_conn_ac_send_i_as_ack(काष्ठा sock *sk, काष्ठा sk_buff *skb);

व्योम llc_conn_busy_पंचांगr_cb(काष्ठा समयr_list *t);
व्योम llc_conn_pf_cycle_पंचांगr_cb(काष्ठा समयr_list *t);
व्योम llc_conn_ack_पंचांगr_cb(काष्ठा समयr_list *t);
व्योम llc_conn_rej_पंचांगr_cb(काष्ठा समयr_list *t);

व्योम llc_conn_set_p_flag(काष्ठा sock *sk, u8 value);
#पूर्ण_अगर /* LLC_C_AC_H */
