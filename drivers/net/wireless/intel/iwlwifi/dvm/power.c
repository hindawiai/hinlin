<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2007 - 2014 Intel Corporation. All rights reserved.
 * Copyright (C) 2019 Intel Corporation
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
#समावेश "iwl-debug.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-modparams.h"
#समावेश "dev.h"
#समावेश "agn.h"
#समावेश "commands.h"
#समावेश "power.h"

अटल bool क्रमce_cam = true;
module_param(क्रमce_cam, bool, 0644);
MODULE_PARM_DESC(क्रमce_cam, "force continuously aware mode (no power saving at all)");

/*
 * Setting घातer level allows the card to go to sleep when not busy.
 *
 * We calculate a sleep command based on the required latency, which
 * we get from mac80211. In order to handle thermal throttling, we can
 * also use pre-defined घातer levels.
 */

/*
 * This defines the old घातer levels. They are still used by शेष
 * (level 1) and क्रम thermal throttle (levels 3 through 5)
 */

काष्ठा iwl_घातer_vec_entry अणु
	काष्ठा iwl_घातertable_cmd cmd;
	u8 no_dtim;	/* number of skip dtim */
पूर्ण;

#घोषणा IWL_DTIM_RANGE_0_MAX	2
#घोषणा IWL_DTIM_RANGE_1_MAX	10

#घोषणा NOSLP cpu_to_le16(0), 0, 0
#घोषणा SLP IWL_POWER_DRIVER_ALLOW_SLEEP_MSK, 0, 0
#घोषणा ASLP (IWL_POWER_POWER_SAVE_ENA_MSK |	\
		IWL_POWER_POWER_MANAGEMENT_ENA_MSK | \
		IWL_POWER_ADVANCE_PM_ENA_MSK)
#घोषणा ASLP_TOUT(T) cpu_to_le32(T)
#घोषणा TU_TO_USEC 1024
#घोषणा SLP_TOUT(T) cpu_to_le32((T) * TU_TO_USEC)
#घोषणा SLP_VEC(X0, X1, X2, X3, X4) अणुcpu_to_le32(X0), \
				     cpu_to_le32(X1), \
				     cpu_to_le32(X2), \
				     cpu_to_le32(X3), \
				     cpu_to_le32(X4)पूर्ण
/* शेष घातer management (not Tx घातer) table values */
/* क्रम DTIM period 0 through IWL_DTIM_RANGE_0_MAX */
/* DTIM 0 - 2 */
अटल स्थिर काष्ठा iwl_घातer_vec_entry range_0[IWL_POWER_NUM] = अणु
	अणुअणुSLP, SLP_TOUT(200), SLP_TOUT(500), SLP_VEC(1, 1, 2, 2, 0xFF)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(200), SLP_TOUT(300), SLP_VEC(1, 2, 2, 2, 0xFF)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(50), SLP_TOUT(100), SLP_VEC(2, 2, 2, 2, 0xFF)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(50), SLP_TOUT(25), SLP_VEC(2, 2, 4, 4, 0xFF)पूर्ण, 1पूर्ण,
	अणुअणुSLP, SLP_TOUT(25), SLP_TOUT(25), SLP_VEC(2, 2, 4, 6, 0xFF)पूर्ण, 2पूर्ण
पूर्ण;


/* क्रम DTIM period IWL_DTIM_RANGE_0_MAX + 1 through IWL_DTIM_RANGE_1_MAX */
/* DTIM 3 - 10 */
अटल स्थिर काष्ठा iwl_घातer_vec_entry range_1[IWL_POWER_NUM] = अणु
	अणुअणुSLP, SLP_TOUT(200), SLP_TOUT(500), SLP_VEC(1, 2, 3, 4, 4)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(200), SLP_TOUT(300), SLP_VEC(1, 2, 3, 4, 7)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(50), SLP_TOUT(100), SLP_VEC(2, 4, 6, 7, 9)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(50), SLP_TOUT(25), SLP_VEC(2, 4, 6, 9, 10)पूर्ण, 1पूर्ण,
	अणुअणुSLP, SLP_TOUT(25), SLP_TOUT(25), SLP_VEC(2, 4, 6, 10, 10)पूर्ण, 2पूर्ण
पूर्ण;

/* क्रम DTIM period > IWL_DTIM_RANGE_1_MAX */
/* DTIM 11 - */
अटल स्थिर काष्ठा iwl_घातer_vec_entry range_2[IWL_POWER_NUM] = अणु
	अणुअणुSLP, SLP_TOUT(200), SLP_TOUT(500), SLP_VEC(1, 2, 3, 4, 0xFF)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(200), SLP_TOUT(300), SLP_VEC(2, 4, 6, 7, 0xFF)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(50), SLP_TOUT(100), SLP_VEC(2, 7, 9, 9, 0xFF)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(50), SLP_TOUT(25), SLP_VEC(2, 7, 9, 9, 0xFF)पूर्ण, 0पूर्ण,
	अणुअणुSLP, SLP_TOUT(25), SLP_TOUT(25), SLP_VEC(4, 7, 10, 10, 0xFF)पूर्ण, 0पूर्ण
पूर्ण;

/* advance घातer management */
/* DTIM 0 - 2 */
अटल स्थिर काष्ठा iwl_घातer_vec_entry apm_range_0[IWL_POWER_NUM] = अणु
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 6, 8, 0xFF), ASLP_TOUT(2)पूर्ण, 2पूर्ण
पूर्ण;


/* क्रम DTIM period IWL_DTIM_RANGE_0_MAX + 1 through IWL_DTIM_RANGE_1_MAX */
/* DTIM 3 - 10 */
अटल स्थिर काष्ठा iwl_घातer_vec_entry apm_range_1[IWL_POWER_NUM] = अणु
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 6, 8, 0xFF), 0पूर्ण, 2पूर्ण
पूर्ण;

/* क्रम DTIM period > IWL_DTIM_RANGE_1_MAX */
/* DTIM 11 - */
अटल स्थिर काष्ठा iwl_घातer_vec_entry apm_range_2[IWL_POWER_NUM] = अणु
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 4, 6, 0xFF), 0पूर्ण, 0पूर्ण,
	अणुअणुASLP, 0, 0, ASLP_TOUT(50), ASLP_TOUT(50),
		SLP_VEC(1, 2, 6, 8, 0xFF), ASLP_TOUT(2)पूर्ण, 2पूर्ण
पूर्ण;

अटल व्योम iwl_अटल_sleep_cmd(काष्ठा iwl_priv *priv,
				 काष्ठा iwl_घातertable_cmd *cmd,
				 क्रमागत iwl_घातer_level lvl, पूर्णांक period)
अणु
	स्थिर काष्ठा iwl_घातer_vec_entry *table;
	पूर्णांक max_sleep[IWL_POWER_VEC_SIZE] = अणु 0 पूर्ण;
	पूर्णांक i;
	u8 skip;
	u32 slp_itrvl;

	अगर (priv->lib->adv_pm) अणु
		table = apm_range_2;
		अगर (period <= IWL_DTIM_RANGE_1_MAX)
			table = apm_range_1;
		अगर (period <= IWL_DTIM_RANGE_0_MAX)
			table = apm_range_0;
	पूर्ण अन्यथा अणु
		table = range_2;
		अगर (period <= IWL_DTIM_RANGE_1_MAX)
			table = range_1;
		अगर (period <= IWL_DTIM_RANGE_0_MAX)
			table = range_0;
	पूर्ण

	अगर (WARN_ON(lvl < 0 || lvl >= IWL_POWER_NUM))
		स_रखो(cmd, 0, माप(*cmd));
	अन्यथा
		*cmd = table[lvl].cmd;

	अगर (period == 0) अणु
		skip = 0;
		period = 1;
		क्रम (i = 0; i < IWL_POWER_VEC_SIZE; i++)
			max_sleep[i] =  1;

	पूर्ण अन्यथा अणु
		skip = table[lvl].no_dtim;
		क्रम (i = 0; i < IWL_POWER_VEC_SIZE; i++)
			max_sleep[i] = le32_to_cpu(cmd->sleep_पूर्णांकerval[i]);
		max_sleep[IWL_POWER_VEC_SIZE - 1] = skip + 1;
	पूर्ण

	slp_itrvl = le32_to_cpu(cmd->sleep_पूर्णांकerval[IWL_POWER_VEC_SIZE - 1]);
	/* figure out the listen पूर्णांकerval based on dtim period and skip */
	अगर (slp_itrvl == 0xFF)
		cmd->sleep_पूर्णांकerval[IWL_POWER_VEC_SIZE - 1] =
			cpu_to_le32(period * (skip + 1));

	slp_itrvl = le32_to_cpu(cmd->sleep_पूर्णांकerval[IWL_POWER_VEC_SIZE - 1]);
	अगर (slp_itrvl > period)
		cmd->sleep_पूर्णांकerval[IWL_POWER_VEC_SIZE - 1] =
			cpu_to_le32((slp_itrvl / period) * period);

	अगर (skip)
		cmd->flags |= IWL_POWER_SLEEP_OVER_DTIM_MSK;
	अन्यथा
		cmd->flags &= ~IWL_POWER_SLEEP_OVER_DTIM_MSK;

	अगर (priv->trans->trans_cfg->base_params->shaकरोw_reg_enable)
		cmd->flags |= IWL_POWER_SHADOW_REG_ENA;
	अन्यथा
		cmd->flags &= ~IWL_POWER_SHADOW_REG_ENA;

	अगर (iwl_advanced_bt_coexist(priv)) अणु
		अगर (!priv->lib->bt_params->bt_sco_disable)
			cmd->flags |= IWL_POWER_BT_SCO_ENA;
		अन्यथा
			cmd->flags &= ~IWL_POWER_BT_SCO_ENA;
	पूर्ण


	slp_itrvl = le32_to_cpu(cmd->sleep_पूर्णांकerval[IWL_POWER_VEC_SIZE - 1]);
	अगर (slp_itrvl > IWL_CONN_MAX_LISTEN_INTERVAL)
		cmd->sleep_पूर्णांकerval[IWL_POWER_VEC_SIZE - 1] =
			cpu_to_le32(IWL_CONN_MAX_LISTEN_INTERVAL);

	/* enक्रमce max sleep पूर्णांकerval */
	क्रम (i = IWL_POWER_VEC_SIZE - 1; i >= 0 ; i--) अणु
		अगर (le32_to_cpu(cmd->sleep_पूर्णांकerval[i]) >
		    (max_sleep[i] * period))
			cmd->sleep_पूर्णांकerval[i] =
				cpu_to_le32(max_sleep[i] * period);
		अगर (i != (IWL_POWER_VEC_SIZE - 1)) अणु
			अगर (le32_to_cpu(cmd->sleep_पूर्णांकerval[i]) >
			    le32_to_cpu(cmd->sleep_पूर्णांकerval[i+1]))
				cmd->sleep_पूर्णांकerval[i] =
					cmd->sleep_पूर्णांकerval[i+1];
		पूर्ण
	पूर्ण

	अगर (priv->घातer_data.bus_pm)
		cmd->flags |= IWL_POWER_PCI_PM_MSK;
	अन्यथा
		cmd->flags &= ~IWL_POWER_PCI_PM_MSK;

	IWL_DEBUG_POWER(priv, "numSkipDtim = %u, dtimPeriod = %d\n",
			skip, period);
	/* The घातer level here is 0-4 (used as array index), but user expects
	to see 1-5 (according to spec). */
	IWL_DEBUG_POWER(priv, "Sleep command for index %d\n", lvl + 1);
पूर्ण

अटल व्योम iwl_घातer_sleep_cam_cmd(काष्ठा iwl_priv *priv,
				    काष्ठा iwl_घातertable_cmd *cmd)
अणु
	स_रखो(cmd, 0, माप(*cmd));

	अगर (priv->घातer_data.bus_pm)
		cmd->flags |= IWL_POWER_PCI_PM_MSK;

	IWL_DEBUG_POWER(priv, "Sleep command for CAM\n");
पूर्ण

अटल पूर्णांक iwl_set_घातer(काष्ठा iwl_priv *priv, काष्ठा iwl_घातertable_cmd *cmd)
अणु
	IWL_DEBUG_POWER(priv, "Sending power/sleep command\n");
	IWL_DEBUG_POWER(priv, "Flags value = 0x%08X\n", cmd->flags);
	IWL_DEBUG_POWER(priv, "Tx timeout = %u\n", le32_to_cpu(cmd->tx_data_समयout));
	IWL_DEBUG_POWER(priv, "Rx timeout = %u\n", le32_to_cpu(cmd->rx_data_समयout));
	IWL_DEBUG_POWER(priv, "Sleep interval vector = { %d , %d , %d , %d , %d }\n",
			le32_to_cpu(cmd->sleep_पूर्णांकerval[0]),
			le32_to_cpu(cmd->sleep_पूर्णांकerval[1]),
			le32_to_cpu(cmd->sleep_पूर्णांकerval[2]),
			le32_to_cpu(cmd->sleep_पूर्णांकerval[3]),
			le32_to_cpu(cmd->sleep_पूर्णांकerval[4]));

	वापस iwl_dvm_send_cmd_pdu(priv, POWER_TABLE_CMD, 0,
				माप(काष्ठा iwl_घातertable_cmd), cmd);
पूर्ण

अटल व्योम iwl_घातer_build_cmd(काष्ठा iwl_priv *priv,
				काष्ठा iwl_घातertable_cmd *cmd)
अणु
	bool enabled = priv->hw->conf.flags & IEEE80211_CONF_PS;
	पूर्णांक dtimper;

	अगर (क्रमce_cam) अणु
		iwl_घातer_sleep_cam_cmd(priv, cmd);
		वापस;
	पूर्ण

	dtimper = priv->hw->conf.ps_dtim_period ?: 1;

	अगर (priv->wowlan)
		iwl_अटल_sleep_cmd(priv, cmd, IWL_POWER_INDEX_5, dtimper);
	अन्यथा अगर (!priv->lib->no_idle_support &&
		 priv->hw->conf.flags & IEEE80211_CONF_IDLE)
		iwl_अटल_sleep_cmd(priv, cmd, IWL_POWER_INDEX_5, 20);
	अन्यथा अगर (iwl_tt_is_low_घातer_state(priv)) अणु
		/* in thermal throttling low घातer state */
		iwl_अटल_sleep_cmd(priv, cmd,
		    iwl_tt_current_घातer_mode(priv), dtimper);
	पूर्ण अन्यथा अगर (!enabled)
		iwl_घातer_sleep_cam_cmd(priv, cmd);
	अन्यथा अगर (priv->घातer_data.debug_sleep_level_override >= 0)
		iwl_अटल_sleep_cmd(priv, cmd,
				     priv->घातer_data.debug_sleep_level_override,
				     dtimper);
	अन्यथा अणु
		/* Note that the user parameter is 1-5 (according to spec),
		but we pass 0-4 because it acts as an array index. */
		अगर (iwlwअगरi_mod_params.घातer_level > IWL_POWER_INDEX_1 &&
		    iwlwअगरi_mod_params.घातer_level <= IWL_POWER_NUM)
			iwl_अटल_sleep_cmd(priv, cmd,
				iwlwअगरi_mod_params.घातer_level - 1, dtimper);
		अन्यथा
			iwl_अटल_sleep_cmd(priv, cmd,
				IWL_POWER_INDEX_1, dtimper);
	पूर्ण
पूर्ण

पूर्णांक iwl_घातer_set_mode(काष्ठा iwl_priv *priv, काष्ठा iwl_घातertable_cmd *cmd,
		       bool क्रमce)
अणु
	पूर्णांक ret;
	bool update_chains;

	lockdep_निश्चित_held(&priv->mutex);

	/* Don't update the RX chain when chain noise calibration is running */
	update_chains = priv->chain_noise_data.state == IWL_CHAIN_NOISE_DONE ||
			priv->chain_noise_data.state == IWL_CHAIN_NOISE_ALIVE;

	अगर (!स_भेद(&priv->घातer_data.sleep_cmd, cmd, माप(*cmd)) && !क्रमce)
		वापस 0;

	अगर (!iwl_is_पढ़ोy_rf(priv))
		वापस -EIO;

	/* scan complete use sleep_घातer_next, need to be updated */
	स_नकल(&priv->घातer_data.sleep_cmd_next, cmd, माप(*cmd));
	अगर (test_bit(STATUS_SCANNING, &priv->status) && !क्रमce) अणु
		IWL_DEBUG_INFO(priv, "Defer power set mode while scanning\n");
		वापस 0;
	पूर्ण

	अगर (cmd->flags & IWL_POWER_DRIVER_ALLOW_SLEEP_MSK)
		iwl_dvm_set_pmi(priv, true);

	ret = iwl_set_घातer(priv, cmd);
	अगर (!ret) अणु
		अगर (!(cmd->flags & IWL_POWER_DRIVER_ALLOW_SLEEP_MSK))
			iwl_dvm_set_pmi(priv, false);

		अगर (update_chains)
			iwl_update_chain_flags(priv);
		अन्यथा
			IWL_DEBUG_POWER(priv,
					"Cannot update the power, chain noise "
					"calibration running: %d\n",
					priv->chain_noise_data.state);

		स_नकल(&priv->घातer_data.sleep_cmd, cmd, माप(*cmd));
	पूर्ण अन्यथा
		IWL_ERR(priv, "set power fail, ret = %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक iwl_घातer_update_mode(काष्ठा iwl_priv *priv, bool क्रमce)
अणु
	काष्ठा iwl_घातertable_cmd cmd;

	iwl_घातer_build_cmd(priv, &cmd);
	वापस iwl_घातer_set_mode(priv, &cmd, क्रमce);
पूर्ण

/* initialize to शेष */
व्योम iwl_घातer_initialize(काष्ठा iwl_priv *priv)
अणु
	priv->घातer_data.bus_pm = priv->trans->pm_support;

	priv->घातer_data.debug_sleep_level_override = -1;

	स_रखो(&priv->घातer_data.sleep_cmd, 0,
		माप(priv->घातer_data.sleep_cmd));
पूर्ण
