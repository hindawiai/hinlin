<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: wcmd.h
 *
 * Purpose: Handles the management command पूर्णांकerface functions
 *
 * Author: Lynकरोn Chen
 *
 * Date: May 8, 2002
 *
 */

#अगर_अघोषित __WCMD_H__
#घोषणा __WCMD_H__

#समावेश "device.h"

/* Command code */
क्रमागत vnt_cmd अणु
	WLAN_CMD_INIT_MAC80211,
	WLAN_CMD_SETPOWER,
	WLAN_CMD_TBTT_WAKEUP,
	WLAN_CMD_BECON_SEND,
	WLAN_CMD_CHANGE_ANTENNA
पूर्ण;

#घोषणा CMD_Q_SIZE              32

/* Command state */
क्रमागत vnt_cmd_state अणु
	WLAN_CMD_INIT_MAC80211_START,
	WLAN_CMD_SETPOWER_START,
	WLAN_CMD_TBTT_WAKEUP_START,
	WLAN_CMD_BECON_SEND_START,
	WLAN_CMD_CHANGE_ANTENNA_START,
	WLAN_CMD_IDLE
पूर्ण;

काष्ठा vnt_निजी;

व्योम vnt_reset_command_समयr(काष्ठा vnt_निजी *priv);

पूर्णांक vnt_schedule_command(काष्ठा vnt_निजी *priv, क्रमागत vnt_cmd);

व्योम vnt_run_command(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर /* __WCMD_H__ */
