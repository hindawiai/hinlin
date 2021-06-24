<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner
 */

#अगर_अघोषित _NET_BATMAN_ADV_GATEWAY_COMMON_H_
#घोषणा _NET_BATMAN_ADV_GATEWAY_COMMON_H_

#समावेश "main.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>

/**
 * क्रमागत batadv_bandwidth_units - bandwidth unit types
 */
क्रमागत batadv_bandwidth_units अणु
	/** @BATADV_BW_UNIT_KBIT: unit type kbit */
	BATADV_BW_UNIT_KBIT,

	/** @BATADV_BW_UNIT_MBIT: unit type mbit */
	BATADV_BW_UNIT_MBIT,
पूर्ण;

#घोषणा BATADV_GW_MODE_OFF_NAME	"off"
#घोषणा BATADV_GW_MODE_CLIENT_NAME	"client"
#घोषणा BATADV_GW_MODE_SERVER_NAME	"server"

sमाप_प्रकार batadv_gw_bandwidth_set(काष्ठा net_device *net_dev, अक्षर *buff,
				माप_प्रकार count);
व्योम batadv_gw_tvlv_container_update(काष्ठा batadv_priv *bat_priv);
व्योम batadv_gw_init(काष्ठा batadv_priv *bat_priv);
व्योम batadv_gw_मुक्त(काष्ठा batadv_priv *bat_priv);
bool batadv_parse_throughput(काष्ठा net_device *net_dev, अक्षर *buff,
			     स्थिर अक्षर *description, u32 *throughput);

#पूर्ण_अगर /* _NET_BATMAN_ADV_GATEWAY_COMMON_H_ */
