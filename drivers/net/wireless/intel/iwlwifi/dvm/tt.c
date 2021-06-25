<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2007 - 2014 Intel Corporation. All rights reserved.
 * Copyright (C) 2018, 2020 Intel Corporation
 *
 * Portions of this file are derived from the ipw3945 project, as well
 * as portions of the ieee80211 subप्रणाली header files.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *****************************************************************************/


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <net/mac80211.h>
#समावेश "iwl-io.h"
#समावेश "iwl-modparams.h"
#समावेश "iwl-debug.h"
#समावेश "agn.h"
#समावेश "dev.h"
#समावेश "commands.h"
#समावेश "tt.h"

/* शेष Thermal Throttling transaction table
 * Current state   |         Throttling Down               |  Throttling Up
 *=============================================================================
 *                 Condition Nxt State  Condition Nxt State Condition Nxt State
 *-----------------------------------------------------------------------------
 *     IWL_TI_0     T >= 114   CT_KILL  114>T>=105   TI_1      N/A      N/A
 *     IWL_TI_1     T >= 114   CT_KILL  114>T>=110   TI_2     T<=95     TI_0
 *     IWL_TI_2     T >= 114   CT_KILL                        T<=100    TI_1
 *    IWL_CT_KILL      N/A       N/A       N/A        N/A     T<=95     TI_0
 *=============================================================================
 */
अटल स्थिर काष्ठा iwl_tt_trans tt_range_0[IWL_TI_STATE_MAX - 1] = अणु
	अणुIWL_TI_0, IWL_ABSOLUTE_ZERO, 104पूर्ण,
	अणुIWL_TI_1, 105, CT_KILL_THRESHOLD - 1पूर्ण,
	अणुIWL_TI_CT_KILL, CT_KILL_THRESHOLD, IWL_ABSOLUTE_MAXपूर्ण
पूर्ण;
अटल स्थिर काष्ठा iwl_tt_trans tt_range_1[IWL_TI_STATE_MAX - 1] = अणु
	अणुIWL_TI_0, IWL_ABSOLUTE_ZERO, 95पूर्ण,
	अणुIWL_TI_2, 110, CT_KILL_THRESHOLD - 1पूर्ण,
	अणुIWL_TI_CT_KILL, CT_KILL_THRESHOLD, IWL_ABSOLUTE_MAXपूर्ण
पूर्ण;
अटल स्थिर काष्ठा iwl_tt_trans tt_range_2[IWL_TI_STATE_MAX - 1] = अणु
	अणुIWL_TI_1, IWL_ABSOLUTE_ZERO, 100पूर्ण,
	अणुIWL_TI_CT_KILL, CT_KILL_THRESHOLD, IWL_ABSOLUTE_MAXपूर्ण,
	अणुIWL_TI_CT_KILL, CT_KILL_THRESHOLD, IWL_ABSOLUTE_MAXपूर्ण
पूर्ण;
अटल स्थिर काष्ठा iwl_tt_trans tt_range_3[IWL_TI_STATE_MAX - 1] = अणु
	अणुIWL_TI_0, IWL_ABSOLUTE_ZERO, CT_KILL_EXIT_THRESHOLDपूर्ण,
	अणुIWL_TI_CT_KILL, CT_KILL_EXIT_THRESHOLD + 1, IWL_ABSOLUTE_MAXपूर्ण,
	अणुIWL_TI_CT_KILL, CT_KILL_EXIT_THRESHOLD + 1, IWL_ABSOLUTE_MAXपूर्ण
पूर्ण;

/* Advance Thermal Throttling शेष restriction table */
अटल स्थिर काष्ठा iwl_tt_restriction restriction_range[IWL_TI_STATE_MAX] = अणु
	अणुIWL_ANT_OK_MULTI, IWL_ANT_OK_MULTI, true पूर्ण,
	अणुIWL_ANT_OK_SINGLE, IWL_ANT_OK_MULTI, true पूर्ण,
	अणुIWL_ANT_OK_SINGLE, IWL_ANT_OK_SINGLE, false पूर्ण,
	अणुIWL_ANT_OK_NONE, IWL_ANT_OK_NONE, false पूर्ण
पूर्ण;

bool iwl_tt_is_low_घातer_state(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;

	अगर (tt->state >= IWL_TI_1)
		वापस true;
	वापस false;
पूर्ण

u8 iwl_tt_current_घातer_mode(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;

	वापस tt->tt_घातer_mode;
पूर्ण

bool iwl_ht_enabled(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;
	काष्ठा iwl_tt_restriction *restriction;

	अगर (!priv->thermal_throttle.advanced_tt)
		वापस true;
	restriction = tt->restriction + tt->state;
	वापस restriction->is_ht;
पूर्ण

अटल bool iwl_within_ct_समाप्त_margin(काष्ठा iwl_priv *priv)
अणु
	s32 temp = priv->temperature; /* degrees CELSIUS except specअगरied */
	bool within_margin = false;

	अगर (!priv->thermal_throttle.advanced_tt)
		within_margin = ((temp + IWL_TT_CT_KILL_MARGIN) >=
				CT_KILL_THRESHOLD_LEGACY) ? true : false;
	अन्यथा
		within_margin = ((temp + IWL_TT_CT_KILL_MARGIN) >=
				CT_KILL_THRESHOLD) ? true : false;
	वापस within_margin;
पूर्ण

bool iwl_check_क्रम_ct_समाप्त(काष्ठा iwl_priv *priv)
अणु
	bool is_ct_समाप्त = false;

	अगर (iwl_within_ct_समाप्त_margin(priv)) अणु
		iwl_tt_enter_ct_समाप्त(priv);
		is_ct_समाप्त = true;
	पूर्ण
	वापस is_ct_समाप्त;
पूर्ण

क्रमागत iwl_antenna_ok iwl_tx_ant_restriction(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;
	काष्ठा iwl_tt_restriction *restriction;

	अगर (!priv->thermal_throttle.advanced_tt)
		वापस IWL_ANT_OK_MULTI;
	restriction = tt->restriction + tt->state;
	वापस restriction->tx_stream;
पूर्ण

क्रमागत iwl_antenna_ok iwl_rx_ant_restriction(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;
	काष्ठा iwl_tt_restriction *restriction;

	अगर (!priv->thermal_throttle.advanced_tt)
		वापस IWL_ANT_OK_MULTI;
	restriction = tt->restriction + tt->state;
	वापस restriction->rx_stream;
पूर्ण

#घोषणा CT_KILL_EXIT_DURATION (5)	/* 5 seconds duration */
#घोषणा CT_KILL_WAITING_DURATION (300)	/* 300ms duration */

/*
 * toggle the bit to wake up uCode and check the temperature
 * अगर the temperature is below CT, uCode will stay awake and send card
 * state notअगरication with CT_KILL bit clear to inक्रमm Thermal Throttling
 * Management to change state. Otherwise, uCode will go back to sleep
 * without करोing anything, driver should जारी the 5 seconds समयr
 * to wake up uCode क्रम temperature check until temperature drop below CT
 */
अटल व्योम iwl_tt_check_निकास_ct_समाप्त(काष्ठा समयr_list *t)
अणु
	काष्ठा iwl_priv *priv = from_समयr(priv, t,
					   thermal_throttle.ct_समाप्त_निकास_पंचांग);
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	अगर (tt->state == IWL_TI_CT_KILL) अणु
		अगर (priv->thermal_throttle.ct_समाप्त_toggle) अणु
			iwl_ग_लिखो32(priv->trans, CSR_UCODE_DRV_GP1_CLR,
				    CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);
			priv->thermal_throttle.ct_समाप्त_toggle = false;
		पूर्ण अन्यथा अणु
			iwl_ग_लिखो32(priv->trans, CSR_UCODE_DRV_GP1_SET,
				    CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);
			priv->thermal_throttle.ct_समाप्त_toggle = true;
		पूर्ण
		iwl_पढ़ो32(priv->trans, CSR_UCODE_DRV_GP1);
		अगर (iwl_trans_grab_nic_access(priv->trans))
			iwl_trans_release_nic_access(priv->trans);

		/* Reschedule the ct_समाप्त समयr to occur in
		 * CT_KILL_EXIT_DURATION seconds to ensure we get a
		 * thermal update */
		IWL_DEBUG_TEMP(priv, "schedule ct_kill exit timer\n");
		mod_समयr(&priv->thermal_throttle.ct_समाप्त_निकास_पंचांग,
			  jअगरfies + CT_KILL_EXIT_DURATION * HZ);
	पूर्ण
पूर्ण

अटल व्योम iwl_perक्रमm_ct_समाप्त_task(काष्ठा iwl_priv *priv,
			   bool stop)
अणु
	अगर (stop) अणु
		IWL_DEBUG_TEMP(priv, "Stop all queues\n");
		अगर (priv->mac80211_रेजिस्टरed)
			ieee80211_stop_queues(priv->hw);
		IWL_DEBUG_TEMP(priv,
				"Schedule 5 seconds CT_KILL Timer\n");
		mod_समयr(&priv->thermal_throttle.ct_समाप्त_निकास_पंचांग,
			  jअगरfies + CT_KILL_EXIT_DURATION * HZ);
	पूर्ण अन्यथा अणु
		IWL_DEBUG_TEMP(priv, "Wake all queues\n");
		अगर (priv->mac80211_रेजिस्टरed)
			ieee80211_wake_queues(priv->hw);
	पूर्ण
पूर्ण

अटल व्योम iwl_tt_पढ़ोy_क्रम_ct_समाप्त(काष्ठा समयr_list *t)
अणु
	काष्ठा iwl_priv *priv = from_समयr(priv, t,
					   thermal_throttle.ct_समाप्त_रुकोing_पंचांग);
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	/* temperature समयr expired, पढ़ोy to go पूर्णांकo CT_KILL state */
	अगर (tt->state != IWL_TI_CT_KILL) अणु
		IWL_DEBUG_TEMP(priv, "entering CT_KILL state when "
				"temperature timer expired\n");
		tt->state = IWL_TI_CT_KILL;
		set_bit(STATUS_CT_KILL, &priv->status);
		iwl_perक्रमm_ct_समाप्त_task(priv, true);
	पूर्ण
पूर्ण

अटल व्योम iwl_prepare_ct_समाप्त_task(काष्ठा iwl_priv *priv)
अणु
	IWL_DEBUG_TEMP(priv, "Prepare to enter IWL_TI_CT_KILL\n");
	/* make request to retrieve statistics inक्रमmation */
	iwl_send_statistics_request(priv, 0, false);
	/* Reschedule the ct_समाप्त रुको समयr */
	mod_समयr(&priv->thermal_throttle.ct_समाप्त_रुकोing_पंचांग,
		 jअगरfies + msecs_to_jअगरfies(CT_KILL_WAITING_DURATION));
पूर्ण

#घोषणा IWL_MINIMAL_POWER_THRESHOLD		(CT_KILL_THRESHOLD_LEGACY)
#घोषणा IWL_REDUCED_PERFORMANCE_THRESHOLD_2	(100)
#घोषणा IWL_REDUCED_PERFORMANCE_THRESHOLD_1	(90)

/*
 * Legacy thermal throttling
 * 1) Aव्योम NIC deकाष्ठाion due to high temperatures
 *	Chip will identअगरy dangerously high temperatures that can
 *	harm the device and will घातer करोwn
 * 2) Aव्योम the NIC घातer करोwn due to high temperature
 *	Throttle early enough to lower the घातer consumption beक्रमe
 *	drastic steps are needed
 */
अटल व्योम iwl_legacy_tt_handler(काष्ठा iwl_priv *priv, s32 temp, bool क्रमce)
अणु
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;
	क्रमागत iwl_tt_state old_state;

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	अगर ((tt->tt_previous_temp) &&
	    (temp > tt->tt_previous_temp) &&
	    ((temp - tt->tt_previous_temp) >
	    IWL_TT_INCREASE_MARGIN)) अणु
		IWL_DEBUG_TEMP(priv,
			"Temperature increase %d degree Celsius\n",
			(temp - tt->tt_previous_temp));
	पूर्ण
#पूर्ण_अगर
	old_state = tt->state;
	/* in Celsius */
	अगर (temp >= IWL_MINIMAL_POWER_THRESHOLD)
		tt->state = IWL_TI_CT_KILL;
	अन्यथा अगर (temp >= IWL_REDUCED_PERFORMANCE_THRESHOLD_2)
		tt->state = IWL_TI_2;
	अन्यथा अगर (temp >= IWL_REDUCED_PERFORMANCE_THRESHOLD_1)
		tt->state = IWL_TI_1;
	अन्यथा
		tt->state = IWL_TI_0;

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	tt->tt_previous_temp = temp;
#पूर्ण_अगर
	/* stop ct_समाप्त_रुकोing_पंचांग समयr */
	del_समयr_sync(&priv->thermal_throttle.ct_समाप्त_रुकोing_पंचांग);
	अगर (tt->state != old_state) अणु
		चयन (tt->state) अणु
		हाल IWL_TI_0:
			/*
			 * When the प्रणाली is पढ़ोy to go back to IWL_TI_0
			 * we only have to call iwl_घातer_update_mode() to
			 * करो so.
			 */
			अवरोध;
		हाल IWL_TI_1:
			tt->tt_घातer_mode = IWL_POWER_INDEX_3;
			अवरोध;
		हाल IWL_TI_2:
			tt->tt_घातer_mode = IWL_POWER_INDEX_4;
			अवरोध;
		शेष:
			tt->tt_घातer_mode = IWL_POWER_INDEX_5;
			अवरोध;
		पूर्ण
		mutex_lock(&priv->mutex);
		अगर (old_state == IWL_TI_CT_KILL)
			clear_bit(STATUS_CT_KILL, &priv->status);
		अगर (tt->state != IWL_TI_CT_KILL &&
		    iwl_घातer_update_mode(priv, true)) अणु
			/* TT state not updated
			 * try again during next temperature पढ़ो
			 */
			अगर (old_state == IWL_TI_CT_KILL)
				set_bit(STATUS_CT_KILL, &priv->status);
			tt->state = old_state;
			IWL_ERR(priv, "Cannot update power mode, "
					"TT state not updated\n");
		पूर्ण अन्यथा अणु
			अगर (tt->state == IWL_TI_CT_KILL) अणु
				अगर (क्रमce) अणु
					set_bit(STATUS_CT_KILL, &priv->status);
					iwl_perक्रमm_ct_समाप्त_task(priv, true);
				पूर्ण अन्यथा अणु
					iwl_prepare_ct_समाप्त_task(priv);
					tt->state = old_state;
				पूर्ण
			पूर्ण अन्यथा अगर (old_state == IWL_TI_CT_KILL) अणु
				iwl_perक्रमm_ct_समाप्त_task(priv, false);
			पूर्ण
			IWL_DEBUG_TEMP(priv, "Temperature state changed %u\n",
					tt->state);
			IWL_DEBUG_TEMP(priv, "Power Index change to %u\n",
					tt->tt_घातer_mode);
		पूर्ण
		mutex_unlock(&priv->mutex);
	पूर्ण
पूर्ण

/*
 * Advance thermal throttling
 * 1) Aव्योम NIC deकाष्ठाion due to high temperatures
 *	Chip will identअगरy dangerously high temperatures that can
 *	harm the device and will घातer करोwn
 * 2) Aव्योम the NIC घातer करोwn due to high temperature
 *	Throttle early enough to lower the घातer consumption beक्रमe
 *	drastic steps are needed
 *	Actions include relaxing the घातer करोwn sleep thresholds and
 *	decreasing the number of TX streams
 * 3) Aव्योम throughput perक्रमmance impact as much as possible
 *
 *=============================================================================
 *                 Condition Nxt State  Condition Nxt State Condition Nxt State
 *-----------------------------------------------------------------------------
 *     IWL_TI_0     T >= 114   CT_KILL  114>T>=105   TI_1      N/A      N/A
 *     IWL_TI_1     T >= 114   CT_KILL  114>T>=110   TI_2     T<=95     TI_0
 *     IWL_TI_2     T >= 114   CT_KILL                        T<=100    TI_1
 *    IWL_CT_KILL      N/A       N/A       N/A        N/A     T<=95     TI_0
 *=============================================================================
 */
अटल व्योम iwl_advance_tt_handler(काष्ठा iwl_priv *priv, s32 temp, bool क्रमce)
अणु
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;
	पूर्णांक i;
	bool changed = false;
	क्रमागत iwl_tt_state old_state;
	काष्ठा iwl_tt_trans *transaction;

	old_state = tt->state;
	क्रम (i = 0; i < IWL_TI_STATE_MAX - 1; i++) अणु
		/* based on the current TT state,
		 * find the curresponding transaction table
		 * each table has (IWL_TI_STATE_MAX - 1) entries
		 * tt->transaction + ((old_state * (IWL_TI_STATE_MAX - 1))
		 * will advance to the correct table.
		 * then based on the current temperature
		 * find the next state need to transaction to
		 * go through all the possible (IWL_TI_STATE_MAX - 1) entries
		 * in the current table to see अगर transaction is needed
		 */
		transaction = tt->transaction +
			((old_state * (IWL_TI_STATE_MAX - 1)) + i);
		अगर (temp >= transaction->tt_low &&
		    temp <= transaction->tt_high) अणु
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
			अगर ((tt->tt_previous_temp) &&
			    (temp > tt->tt_previous_temp) &&
			    ((temp - tt->tt_previous_temp) >
			    IWL_TT_INCREASE_MARGIN)) अणु
				IWL_DEBUG_TEMP(priv,
					"Temperature increase %d "
					"degree Celsius\n",
					(temp - tt->tt_previous_temp));
			पूर्ण
			tt->tt_previous_temp = temp;
#पूर्ण_अगर
			अगर (old_state !=
			    transaction->next_state) अणु
				changed = true;
				tt->state =
					transaction->next_state;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	/* stop ct_समाप्त_रुकोing_पंचांग समयr */
	del_समयr_sync(&priv->thermal_throttle.ct_समाप्त_रुकोing_पंचांग);
	अगर (changed) अणु
		अगर (tt->state >= IWL_TI_1) अणु
			/* क्रमce PI = IWL_POWER_INDEX_5 in the हाल of TI > 0 */
			tt->tt_घातer_mode = IWL_POWER_INDEX_5;

			अगर (!iwl_ht_enabled(priv)) अणु
				काष्ठा iwl_rxon_context *ctx;

				क्रम_each_context(priv, ctx) अणु
					काष्ठा iwl_rxon_cmd *rxon;

					rxon = &ctx->staging;

					/* disable HT */
					rxon->flags &= ~(
						RXON_FLG_CHANNEL_MODE_MSK |
						RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK |
						RXON_FLG_HT40_PROT_MSK |
						RXON_FLG_HT_PROT_MSK);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* check HT capability and set
				 * according to the प्रणाली HT capability
				 * in हाल get disabled beक्रमe */
				iwl_set_rxon_ht(priv, &priv->current_ht_config);
			पूर्ण

		पूर्ण अन्यथा अणु
			/*
			 * restore प्रणाली घातer setting -- it will be
			 * recalculated स्वतःmatically.
			 */

			/* check HT capability and set
			 * according to the प्रणाली HT capability
			 * in हाल get disabled beक्रमe */
			iwl_set_rxon_ht(priv, &priv->current_ht_config);
		पूर्ण
		mutex_lock(&priv->mutex);
		अगर (old_state == IWL_TI_CT_KILL)
			clear_bit(STATUS_CT_KILL, &priv->status);
		अगर (tt->state != IWL_TI_CT_KILL &&
		    iwl_घातer_update_mode(priv, true)) अणु
			/* TT state not updated
			 * try again during next temperature पढ़ो
			 */
			IWL_ERR(priv, "Cannot update power mode, "
					"TT state not updated\n");
			अगर (old_state == IWL_TI_CT_KILL)
				set_bit(STATUS_CT_KILL, &priv->status);
			tt->state = old_state;
		पूर्ण अन्यथा अणु
			IWL_DEBUG_TEMP(priv,
					"Thermal Throttling to new state: %u\n",
					tt->state);
			अगर (old_state != IWL_TI_CT_KILL &&
			    tt->state == IWL_TI_CT_KILL) अणु
				अगर (क्रमce) अणु
					IWL_DEBUG_TEMP(priv,
						"Enter IWL_TI_CT_KILL\n");
					set_bit(STATUS_CT_KILL, &priv->status);
					iwl_perक्रमm_ct_समाप्त_task(priv, true);
				पूर्ण अन्यथा अणु
					tt->state = old_state;
					iwl_prepare_ct_समाप्त_task(priv);
				पूर्ण
			पूर्ण अन्यथा अगर (old_state == IWL_TI_CT_KILL &&
				  tt->state != IWL_TI_CT_KILL) अणु
				IWL_DEBUG_TEMP(priv, "Exit IWL_TI_CT_KILL\n");
				iwl_perक्रमm_ct_समाप्त_task(priv, false);
			पूर्ण
		पूर्ण
		mutex_unlock(&priv->mutex);
	पूर्ण
पूर्ण

/* Card State Notअगरication indicated reach critical temperature
 * अगर PSP not enable, no Thermal Throttling function will be perक्रमmed
 * just set the GP1 bit to acknowledge the event
 * otherwise, go पूर्णांकo IWL_TI_CT_KILL state
 * since Card State Notअगरication will not provide any temperature पढ़ोing
 * क्रम Legacy mode
 * so just pass the CT_KILL temperature to iwl_legacy_tt_handler()
 * क्रम advance mode
 * pass CT_KILL_THRESHOLD+1 to make sure move पूर्णांकo IWL_TI_CT_KILL state
 */
अटल व्योम iwl_bg_ct_enter(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv = container_of(work, काष्ठा iwl_priv, ct_enter);
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	अगर (!iwl_is_पढ़ोy(priv))
		वापस;

	अगर (tt->state != IWL_TI_CT_KILL) अणु
		IWL_ERR(priv, "Device reached critical temperature "
			      "- ucode going to sleep!\n");
		अगर (!priv->thermal_throttle.advanced_tt)
			iwl_legacy_tt_handler(priv,
					      IWL_MINIMAL_POWER_THRESHOLD,
					      true);
		अन्यथा
			iwl_advance_tt_handler(priv,
					       CT_KILL_THRESHOLD + 1, true);
	पूर्ण
पूर्ण

/* Card State Notअगरication indicated out of critical temperature
 * since Card State Notअगरication will not provide any temperature पढ़ोing
 * so pass the IWL_REDUCED_PERFORMANCE_THRESHOLD_2 temperature
 * to iwl_legacy_tt_handler() to get out of IWL_CT_KILL state
 */
अटल व्योम iwl_bg_ct_निकास(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv = container_of(work, काष्ठा iwl_priv, ct_निकास);
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	अगर (!iwl_is_पढ़ोy(priv))
		वापस;

	/* stop ct_समाप्त_निकास_पंचांग समयr */
	del_समयr_sync(&priv->thermal_throttle.ct_समाप्त_निकास_पंचांग);

	अगर (tt->state == IWL_TI_CT_KILL) अणु
		IWL_ERR(priv,
			"Device temperature below critical"
			"- ucode awake!\n");
		/*
		 * निकास from CT_KILL state
		 * reset the current temperature पढ़ोing
		 */
		priv->temperature = 0;
		अगर (!priv->thermal_throttle.advanced_tt)
			iwl_legacy_tt_handler(priv,
				      IWL_REDUCED_PERFORMANCE_THRESHOLD_2,
				      true);
		अन्यथा
			iwl_advance_tt_handler(priv, CT_KILL_EXIT_THRESHOLD,
					       true);
	पूर्ण
पूर्ण

व्योम iwl_tt_enter_ct_समाप्त(काष्ठा iwl_priv *priv)
अणु
	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	IWL_DEBUG_TEMP(priv, "Queueing critical temperature enter.\n");
	queue_work(priv->workqueue, &priv->ct_enter);
पूर्ण

व्योम iwl_tt_निकास_ct_समाप्त(काष्ठा iwl_priv *priv)
अणु
	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	IWL_DEBUG_TEMP(priv, "Queueing critical temperature exit.\n");
	queue_work(priv->workqueue, &priv->ct_निकास);
पूर्ण

अटल व्योम iwl_bg_tt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv = container_of(work, काष्ठा iwl_priv, tt_work);
	s32 temp = priv->temperature; /* degrees CELSIUS except specअगरied */

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	अगर (!priv->thermal_throttle.advanced_tt)
		iwl_legacy_tt_handler(priv, temp, false);
	अन्यथा
		iwl_advance_tt_handler(priv, temp, false);
पूर्ण

व्योम iwl_tt_handler(काष्ठा iwl_priv *priv)
अणु
	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	IWL_DEBUG_TEMP(priv, "Queueing thermal throttling work.\n");
	queue_work(priv->workqueue, &priv->tt_work);
पूर्ण

/* Thermal throttling initialization
 * For advance thermal throttling:
 *     Initialize Thermal Index and temperature threshold table
 *     Initialize thermal throttling restriction table
 */
व्योम iwl_tt_initialize(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;
	पूर्णांक size = माप(काष्ठा iwl_tt_trans) * (IWL_TI_STATE_MAX - 1);
	काष्ठा iwl_tt_trans *transaction;

	IWL_DEBUG_TEMP(priv, "Initialize Thermal Throttling\n");

	स_रखो(tt, 0, माप(काष्ठा iwl_tt_mgmt));

	tt->state = IWL_TI_0;
	समयr_setup(&priv->thermal_throttle.ct_समाप्त_निकास_पंचांग,
		    iwl_tt_check_निकास_ct_समाप्त, 0);
	समयr_setup(&priv->thermal_throttle.ct_समाप्त_रुकोing_पंचांग,
		    iwl_tt_पढ़ोy_क्रम_ct_समाप्त, 0);
	/* setup deferred ct समाप्त work */
	INIT_WORK(&priv->tt_work, iwl_bg_tt_work);
	INIT_WORK(&priv->ct_enter, iwl_bg_ct_enter);
	INIT_WORK(&priv->ct_निकास, iwl_bg_ct_निकास);

	अगर (priv->lib->adv_thermal_throttle) अणु
		IWL_DEBUG_TEMP(priv, "Advanced Thermal Throttling\n");
		tt->restriction = kसुस्मृति(IWL_TI_STATE_MAX,
					  माप(काष्ठा iwl_tt_restriction),
					  GFP_KERNEL);
		tt->transaction = kसुस्मृति(IWL_TI_STATE_MAX *
					  (IWL_TI_STATE_MAX - 1),
					  माप(काष्ठा iwl_tt_trans),
					  GFP_KERNEL);
		अगर (!tt->restriction || !tt->transaction) अणु
			IWL_ERR(priv, "Fallback to Legacy Throttling\n");
			priv->thermal_throttle.advanced_tt = false;
			kमुक्त(tt->restriction);
			tt->restriction = शून्य;
			kमुक्त(tt->transaction);
			tt->transaction = शून्य;
		पूर्ण अन्यथा अणु
			transaction = tt->transaction +
				(IWL_TI_0 * (IWL_TI_STATE_MAX - 1));
			स_नकल(transaction, &tt_range_0[0], size);
			transaction = tt->transaction +
				(IWL_TI_1 * (IWL_TI_STATE_MAX - 1));
			स_नकल(transaction, &tt_range_1[0], size);
			transaction = tt->transaction +
				(IWL_TI_2 * (IWL_TI_STATE_MAX - 1));
			स_नकल(transaction, &tt_range_2[0], size);
			transaction = tt->transaction +
				(IWL_TI_CT_KILL * (IWL_TI_STATE_MAX - 1));
			स_नकल(transaction, &tt_range_3[0], size);
			size = माप(काष्ठा iwl_tt_restriction) *
				IWL_TI_STATE_MAX;
			स_नकल(tt->restriction,
				&restriction_range[0], size);
			priv->thermal_throttle.advanced_tt = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		IWL_DEBUG_TEMP(priv, "Legacy Thermal Throttling\n");
		priv->thermal_throttle.advanced_tt = false;
	पूर्ण
पूर्ण

/* cleanup thermal throttling management related memory and समयr */
व्योम iwl_tt_निकास(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;

	/* stop ct_समाप्त_निकास_पंचांग समयr अगर activated */
	del_समयr_sync(&priv->thermal_throttle.ct_समाप्त_निकास_पंचांग);
	/* stop ct_समाप्त_रुकोing_पंचांग समयr अगर activated */
	del_समयr_sync(&priv->thermal_throttle.ct_समाप्त_रुकोing_पंचांग);
	cancel_work_sync(&priv->tt_work);
	cancel_work_sync(&priv->ct_enter);
	cancel_work_sync(&priv->ct_निकास);

	अगर (priv->thermal_throttle.advanced_tt) अणु
		/* मुक्त advance thermal throttling memory */
		kमुक्त(tt->restriction);
		tt->restriction = शून्य;
		kमुक्त(tt->transaction);
		tt->transaction = शून्य;
	पूर्ण
पूर्ण
