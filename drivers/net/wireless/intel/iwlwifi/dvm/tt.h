<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2014 Intel Corporation. All rights reserved.
 *
 * Portions of this file are derived from the ipw3945 project, as well
 * as portions of the ieee80211 subप्रणाली header files.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *****************************************************************************/
#अगर_अघोषित __iwl_tt_setting_h__
#घोषणा __iwl_tt_setting_h__

#समावेश "commands.h"

#घोषणा IWL_ABSOLUTE_ZERO		0
#घोषणा IWL_ABSOLUTE_MAX		0xFFFFFFFF
#घोषणा IWL_TT_INCREASE_MARGIN	5
#घोषणा IWL_TT_CT_KILL_MARGIN	3

क्रमागत iwl_antenna_ok अणु
	IWL_ANT_OK_NONE,
	IWL_ANT_OK_SINGLE,
	IWL_ANT_OK_MULTI,
पूर्ण;

/* Thermal Throttling State Machine states */
क्रमागत  iwl_tt_state अणु
	IWL_TI_0,	/* normal temperature, प्रणाली घातer state */
	IWL_TI_1,	/* high temperature detect, low घातer state */
	IWL_TI_2,	/* higher temperature detected, lower घातer state */
	IWL_TI_CT_KILL, /* critical temperature detected, lowest घातer state */
	IWL_TI_STATE_MAX
पूर्ण;

/**
 * काष्ठा iwl_tt_restriction - Thermal Throttling restriction table
 * @tx_stream: number of tx stream allowed
 * @is_ht: ht enable/disable
 * @rx_stream: number of rx stream allowed
 *
 * This table is used by advance thermal throttling management
 * based on the current thermal throttling state, and determines
 * the number of tx/rx streams and the status of HT operation.
 */
काष्ठा iwl_tt_restriction अणु
	क्रमागत iwl_antenna_ok tx_stream;
	क्रमागत iwl_antenna_ok rx_stream;
	bool is_ht;
पूर्ण;

/**
 * काष्ठा iwl_tt_trans - Thermal Throttling transaction table
 * @next_state:  next thermal throttling mode
 * @tt_low: low temperature threshold to change state
 * @tt_high: high temperature threshold to change state
 *
 * This is used by the advanced thermal throttling algorithm
 * to determine the next thermal state to go based on the
 * current temperature.
 */
काष्ठा iwl_tt_trans अणु
	क्रमागत iwl_tt_state next_state;
	u32 tt_low;
	u32 tt_high;
पूर्ण;

/**
 * काष्ठा iwl_tt_mgnt - Thermal Throttling Management काष्ठाure
 * @advanced_tt:    advanced thermal throttle required
 * @state:          current Thermal Throttling state
 * @tt_घातer_mode:  Thermal Throttling घातer mode index
 *		    being used to set घातer level when
 *		    when thermal throttling state != IWL_TI_0
 *		    the tt_घातer_mode should set to dअगरferent
 *		    घातer mode based on the current tt state
 * @tt_previous_temperature: last measured temperature
 * @iwl_tt_restriction: ptr to restriction tbl, used by advance
 *		    thermal throttling to determine how many tx/rx streams
 *		    should be used in tt state; and can HT be enabled or not
 * @iwl_tt_trans: ptr to adv trans table, used by advance thermal throttling
 *		    state transaction
 * @ct_समाप्त_toggle: used to toggle the CSR bit when checking uCode temperature
 * @ct_समाप्त_निकास_पंचांग: समयr to निकास thermal समाप्त
 */
काष्ठा iwl_tt_mgmt अणु
	क्रमागत iwl_tt_state state;
	bool advanced_tt;
	u8 tt_घातer_mode;
	bool ct_समाप्त_toggle;
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	s32 tt_previous_temp;
#पूर्ण_अगर
	काष्ठा iwl_tt_restriction *restriction;
	काष्ठा iwl_tt_trans *transaction;
	काष्ठा समयr_list ct_समाप्त_निकास_पंचांग;
	काष्ठा समयr_list ct_समाप्त_रुकोing_पंचांग;
पूर्ण;

u8 iwl_tt_current_घातer_mode(काष्ठा iwl_priv *priv);
bool iwl_tt_is_low_घातer_state(काष्ठा iwl_priv *priv);
bool iwl_ht_enabled(काष्ठा iwl_priv *priv);
क्रमागत iwl_antenna_ok iwl_tx_ant_restriction(काष्ठा iwl_priv *priv);
क्रमागत iwl_antenna_ok iwl_rx_ant_restriction(काष्ठा iwl_priv *priv);
व्योम iwl_tt_enter_ct_समाप्त(काष्ठा iwl_priv *priv);
व्योम iwl_tt_निकास_ct_समाप्त(काष्ठा iwl_priv *priv);
व्योम iwl_tt_handler(काष्ठा iwl_priv *priv);
व्योम iwl_tt_initialize(काष्ठा iwl_priv *priv);
व्योम iwl_tt_निकास(काष्ठा iwl_priv *priv);

#पूर्ण_अगर  /* __iwl_tt_setting_h__ */
