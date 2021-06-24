<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: wcmd.c
 *
 * Purpose: Handles the management command पूर्णांकerface functions
 *
 * Author: Lynकरोn Chen
 *
 * Date: May 8, 2003
 *
 * Functions:
 *	vnt_cmd_complete - Command Complete function
 *	vnt_schedule_command - Push Command and रुको Command Scheduler to करो
 *	vnt_cmd_समयr_रुको- Call back समयr
 *
 * Revision History:
 *
 */

#समावेश "device.h"
#समावेश "mac.h"
#समावेश "wcmd.h"
#समावेश "power.h"
#समावेश "usbpipe.h"
#समावेश "rxtx.h"
#समावेश "rf.h"

अटल व्योम vnt_cmd_समयr_रुको(काष्ठा vnt_निजी *priv, अचिन्हित दीर्घ msecs)
अणु
	schedule_delayed_work(&priv->run_command_work, msecs_to_jअगरfies(msecs));
पूर्ण

अटल पूर्णांक vnt_cmd_complete(काष्ठा vnt_निजी *priv)
अणु
	priv->command_state = WLAN_CMD_IDLE;
	अगर (priv->मुक्त_cmd_queue == CMD_Q_SIZE) अणु
		/* Command Queue Empty */
		priv->cmd_running = false;
		वापस true;
	पूर्ण

	priv->command = priv->cmd_queue[priv->cmd_dequeue_idx];

	ADD_ONE_WITH_WRAP_AROUND(priv->cmd_dequeue_idx, CMD_Q_SIZE);
	priv->मुक्त_cmd_queue++;
	priv->cmd_running = true;

	चयन (priv->command) अणु
	हाल WLAN_CMD_INIT_MAC80211:
		priv->command_state = WLAN_CMD_INIT_MAC80211_START;
		अवरोध;

	हाल WLAN_CMD_TBTT_WAKEUP:
		priv->command_state = WLAN_CMD_TBTT_WAKEUP_START;
		अवरोध;

	हाल WLAN_CMD_BECON_SEND:
		priv->command_state = WLAN_CMD_BECON_SEND_START;
		अवरोध;

	हाल WLAN_CMD_SETPOWER:
		priv->command_state = WLAN_CMD_SETPOWER_START;
		अवरोध;

	हाल WLAN_CMD_CHANGE_ANTENNA:
		priv->command_state = WLAN_CMD_CHANGE_ANTENNA_START;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	vnt_cmd_समयr_रुको(priv, 0);

	वापस true;
पूर्ण

व्योम vnt_run_command(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vnt_निजी *priv =
		container_of(work, काष्ठा vnt_निजी, run_command_work.work);

	अगर (test_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags))
		वापस;

	अगर (!priv->cmd_running)
		वापस;

	चयन (priv->command_state) अणु
	हाल WLAN_CMD_INIT_MAC80211_START:
		अगर (priv->mac_hw)
			अवरोध;

		dev_info(&priv->usb->dev, "Starting mac80211\n");

		अगर (vnt_init(priv)) अणु
			/* If fail all ends TODO retry */
			dev_err(&priv->usb->dev, "failed to start\n");
			usb_set_पूर्णांकfdata(priv->पूर्णांकf, शून्य);
			ieee80211_मुक्त_hw(priv->hw);
			वापस;
		पूर्ण

		अवरोध;

	हाल WLAN_CMD_TBTT_WAKEUP_START:
		vnt_next_tbtt_wakeup(priv);
		अवरोध;

	हाल WLAN_CMD_BECON_SEND_START:
		अगर (!priv->vअगर)
			अवरोध;

		vnt_beacon_make(priv, priv->vअगर);

		vnt_mac_reg_bits_on(priv, MAC_REG_TCR, TCR_AUTOBCNTX);

		अवरोध;

	हाल WLAN_CMD_SETPOWER_START:

		vnt_rf_setघातer(priv, priv->hw->conf.chandef.chan);

		अवरोध;

	हाल WLAN_CMD_CHANGE_ANTENNA_START:
		dev_dbg(&priv->usb->dev, "Change from Antenna%d to",
			priv->rx_antenna_sel);

		अगर (priv->rx_antenna_sel == 0) अणु
			priv->rx_antenna_sel = 1;
			अगर (priv->tx_rx_ant_inv)
				vnt_set_antenna_mode(priv, ANT_RXA);
			अन्यथा
				vnt_set_antenna_mode(priv, ANT_RXB);
		पूर्ण अन्यथा अणु
			priv->rx_antenna_sel = 0;
			अगर (priv->tx_rx_ant_inv)
				vnt_set_antenna_mode(priv, ANT_RXB);
			अन्यथा
				vnt_set_antenna_mode(priv, ANT_RXA);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	vnt_cmd_complete(priv);
पूर्ण

पूर्णांक vnt_schedule_command(काष्ठा vnt_निजी *priv, क्रमागत vnt_cmd command)
अणु
	अगर (priv->मुक्त_cmd_queue == 0)
		वापस false;

	priv->cmd_queue[priv->cmd_enqueue_idx] = command;

	ADD_ONE_WITH_WRAP_AROUND(priv->cmd_enqueue_idx, CMD_Q_SIZE);
	priv->मुक्त_cmd_queue--;

	अगर (!priv->cmd_running)
		vnt_cmd_complete(priv);

	वापस true;
पूर्ण

व्योम vnt_reset_command_समयr(काष्ठा vnt_निजी *priv)
अणु
	priv->मुक्त_cmd_queue = CMD_Q_SIZE;
	priv->cmd_dequeue_idx = 0;
	priv->cmd_enqueue_idx = 0;
	priv->command_state = WLAN_CMD_IDLE;
	priv->cmd_running = false;
पूर्ण
