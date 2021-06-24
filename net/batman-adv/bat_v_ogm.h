<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Antonio Quartulli
 */

#अगर_अघोषित _NET_BATMAN_ADV_BAT_V_OGM_H_
#घोषणा _NET_BATMAN_ADV_BAT_V_OGM_H_

#समावेश "main.h"

#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

पूर्णांक batadv_v_ogm_init(काष्ठा batadv_priv *bat_priv);
व्योम batadv_v_ogm_मुक्त(काष्ठा batadv_priv *bat_priv);
व्योम batadv_v_ogm_aggr_work(काष्ठा work_काष्ठा *work);
पूर्णांक batadv_v_ogm_अगरace_enable(काष्ठा batadv_hard_अगरace *hard_अगरace);
व्योम batadv_v_ogm_अगरace_disable(काष्ठा batadv_hard_अगरace *hard_अगरace);
काष्ठा batadv_orig_node *batadv_v_ogm_orig_get(काष्ठा batadv_priv *bat_priv,
					       स्थिर u8 *addr);
व्योम batadv_v_ogm_primary_अगरace_set(काष्ठा batadv_hard_अगरace *primary_अगरace);
पूर्णांक batadv_v_ogm_packet_recv(काष्ठा sk_buff *skb,
			     काष्ठा batadv_hard_अगरace *अगर_incoming);

#पूर्ण_अगर /* _NET_BATMAN_ADV_BAT_V_OGM_H_ */
