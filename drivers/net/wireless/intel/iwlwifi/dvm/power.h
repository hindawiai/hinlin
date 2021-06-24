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
#अगर_अघोषित __iwl_घातer_setting_h__
#घोषणा __iwl_घातer_setting_h__

#समावेश "commands.h"

काष्ठा iwl_घातer_mgr अणु
	काष्ठा iwl_घातertable_cmd sleep_cmd;
	काष्ठा iwl_घातertable_cmd sleep_cmd_next;
	पूर्णांक debug_sleep_level_override;
	bool bus_pm;
पूर्ण;

पूर्णांक iwl_घातer_set_mode(काष्ठा iwl_priv *priv, काष्ठा iwl_घातertable_cmd *cmd,
		       bool क्रमce);
पूर्णांक iwl_घातer_update_mode(काष्ठा iwl_priv *priv, bool क्रमce);
व्योम iwl_घातer_initialize(काष्ठा iwl_priv *priv);

बाह्य bool no_sleep_स्वतःadjust;

#पूर्ण_अगर  /* __iwl_घातer_setting_h__ */
