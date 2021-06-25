<शैली गुरु>
/*
 * llc_s_st.c - Defines SAP component state machine transitions.
 *
 * The followed transitions are SAP component state machine transitions
 * which are described in 802.2 LLC protocol standard करोcument.
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 *		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
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
#समावेश <net/llc_s_ev.h>
#समावेश <net/llc_s_ac.h>
#समावेश <net/llc_s_st.h>

/* dummy last-transition indicator; common to all state transition groups
 * last entry क्रम this state
 * all members are zeros, .bss zeroes it
 */
अटल काष्ठा llc_sap_state_trans llc_sap_state_trans_end;

/* state LLC_SAP_STATE_INACTIVE transition क्रम
 * LLC_SAP_EV_ACTIVATION_REQ event
 */
अटल स्थिर llc_sap_action_t llc_sap_inactive_state_actions_1[] = अणु
	[0] = llc_sap_action_report_status,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_inactive_state_trans_1 = अणु
	.ev =		llc_sap_ev_activation_req,
	.next_state =	LLC_SAP_STATE_ACTIVE,
	.ev_actions =	llc_sap_inactive_state_actions_1,
पूर्ण;

/* array of poपूर्णांकers; one to each transition */
अटल काष्ठा llc_sap_state_trans *llc_sap_inactive_state_transitions[] = अणु
	[0] = &llc_sap_inactive_state_trans_1,
	[1] = &llc_sap_state_trans_end,
पूर्ण;

/* state LLC_SAP_STATE_ACTIVE transition क्रम LLC_SAP_EV_RX_UI event */
अटल स्थिर llc_sap_action_t llc_sap_active_state_actions_1[] = अणु
	[0] = llc_sap_action_unitdata_ind,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_active_state_trans_1 = अणु
	.ev =		llc_sap_ev_rx_ui,
	.next_state =	LLC_SAP_STATE_ACTIVE,
	.ev_actions =	llc_sap_active_state_actions_1,
पूर्ण;

/* state LLC_SAP_STATE_ACTIVE transition क्रम LLC_SAP_EV_UNITDATA_REQ event */
अटल स्थिर llc_sap_action_t llc_sap_active_state_actions_2[] = अणु
	[0] = llc_sap_action_send_ui,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_active_state_trans_2 = अणु
	.ev =		llc_sap_ev_unitdata_req,
	.next_state =	LLC_SAP_STATE_ACTIVE,
	.ev_actions =	llc_sap_active_state_actions_2,
पूर्ण;

/* state LLC_SAP_STATE_ACTIVE transition क्रम LLC_SAP_EV_XID_REQ event */
अटल स्थिर llc_sap_action_t llc_sap_active_state_actions_3[] = अणु
	[0] = llc_sap_action_send_xid_c,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_active_state_trans_3 = अणु
	.ev =		llc_sap_ev_xid_req,
	.next_state =	LLC_SAP_STATE_ACTIVE,
	.ev_actions =	llc_sap_active_state_actions_3,
पूर्ण;

/* state LLC_SAP_STATE_ACTIVE transition क्रम LLC_SAP_EV_RX_XID_C event */
अटल स्थिर llc_sap_action_t llc_sap_active_state_actions_4[] = अणु
	[0] = llc_sap_action_send_xid_r,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_active_state_trans_4 = अणु
	.ev =		llc_sap_ev_rx_xid_c,
	.next_state =	LLC_SAP_STATE_ACTIVE,
	.ev_actions =	llc_sap_active_state_actions_4,
पूर्ण;

/* state LLC_SAP_STATE_ACTIVE transition क्रम LLC_SAP_EV_RX_XID_R event */
अटल स्थिर llc_sap_action_t llc_sap_active_state_actions_5[] = अणु
	[0] = llc_sap_action_xid_ind,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_active_state_trans_5 = अणु
	.ev =		llc_sap_ev_rx_xid_r,
	.next_state =	LLC_SAP_STATE_ACTIVE,
	.ev_actions =	llc_sap_active_state_actions_5,
पूर्ण;

/* state LLC_SAP_STATE_ACTIVE transition क्रम LLC_SAP_EV_TEST_REQ event */
अटल स्थिर llc_sap_action_t llc_sap_active_state_actions_6[] = अणु
	[0] = llc_sap_action_send_test_c,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_active_state_trans_6 = अणु
	.ev =		llc_sap_ev_test_req,
	.next_state =	LLC_SAP_STATE_ACTIVE,
	.ev_actions =	llc_sap_active_state_actions_6,
पूर्ण;

/* state LLC_SAP_STATE_ACTIVE transition क्रम LLC_SAP_EV_RX_TEST_C event */
अटल स्थिर llc_sap_action_t llc_sap_active_state_actions_7[] = अणु
	[0] = llc_sap_action_send_test_r,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_active_state_trans_7 = अणु
	.ev =		llc_sap_ev_rx_test_c,
	.next_state =	LLC_SAP_STATE_ACTIVE,
	.ev_actions =	llc_sap_active_state_actions_7
पूर्ण;

/* state LLC_SAP_STATE_ACTIVE transition क्रम LLC_SAP_EV_RX_TEST_R event */
अटल स्थिर llc_sap_action_t llc_sap_active_state_actions_8[] = अणु
	[0] = llc_sap_action_test_ind,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_active_state_trans_8 = अणु
	.ev =		llc_sap_ev_rx_test_r,
	.next_state =	LLC_SAP_STATE_ACTIVE,
	.ev_actions =	llc_sap_active_state_actions_8,
पूर्ण;

/* state LLC_SAP_STATE_ACTIVE transition क्रम
 * LLC_SAP_EV_DEACTIVATION_REQ event
 */
अटल स्थिर llc_sap_action_t llc_sap_active_state_actions_9[] = अणु
	[0] = llc_sap_action_report_status,
	[1] = शून्य,
पूर्ण;

अटल काष्ठा llc_sap_state_trans llc_sap_active_state_trans_9 = अणु
	.ev =		llc_sap_ev_deactivation_req,
	.next_state =	LLC_SAP_STATE_INACTIVE,
	.ev_actions =	llc_sap_active_state_actions_9
पूर्ण;

/* array of poपूर्णांकers; one to each transition */
अटल काष्ठा llc_sap_state_trans *llc_sap_active_state_transitions[] = अणु
	[0] = &llc_sap_active_state_trans_2,
	[1] = &llc_sap_active_state_trans_1,
	[2] = &llc_sap_active_state_trans_3,
	[3] = &llc_sap_active_state_trans_4,
	[4] = &llc_sap_active_state_trans_5,
	[5] = &llc_sap_active_state_trans_6,
	[6] = &llc_sap_active_state_trans_7,
	[7] = &llc_sap_active_state_trans_8,
	[8] = &llc_sap_active_state_trans_9,
	[9] = &llc_sap_state_trans_end,
पूर्ण;

/* SAP state transition table */
काष्ठा llc_sap_state llc_sap_state_table[LLC_NR_SAP_STATES] = अणु
	[LLC_SAP_STATE_INACTIVE - 1] = अणु
		.curr_state	= LLC_SAP_STATE_INACTIVE,
		.transitions	= llc_sap_inactive_state_transitions,
	पूर्ण,
	[LLC_SAP_STATE_ACTIVE - 1] = अणु
		.curr_state	= LLC_SAP_STATE_ACTIVE,
		.transitions	= llc_sap_active_state_transitions,
	पूर्ण,
पूर्ण;
