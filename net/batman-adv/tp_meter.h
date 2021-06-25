<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Eकरो Monticelli, Antonio Quartulli
 */

#अगर_अघोषित _NET_BATMAN_ADV_TP_METER_H_
#घोषणा _NET_BATMAN_ADV_TP_METER_H_

#समावेश "main.h"

#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>

व्योम batadv_tp_meter_init(व्योम);
व्योम batadv_tp_start(काष्ठा batadv_priv *bat_priv, स्थिर u8 *dst,
		     u32 test_length, u32 *cookie);
व्योम batadv_tp_stop(काष्ठा batadv_priv *bat_priv, स्थिर u8 *dst,
		    u8 वापस_value);
व्योम batadv_tp_meter_recv(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb);

#पूर्ण_अगर /* _NET_BATMAN_ADV_TP_METER_H_ */
