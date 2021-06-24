<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Linus Lथञssing, Marek Lindner
 */

#अगर_अघोषित _NET_BATMAN_ADV_BAT_V_ELP_H_
#घोषणा _NET_BATMAN_ADV_BAT_V_ELP_H_

#समावेश "main.h"

#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>

पूर्णांक batadv_v_elp_अगरace_enable(काष्ठा batadv_hard_अगरace *hard_अगरace);
व्योम batadv_v_elp_अगरace_disable(काष्ठा batadv_hard_अगरace *hard_अगरace);
व्योम batadv_v_elp_अगरace_activate(काष्ठा batadv_hard_अगरace *primary_अगरace,
				 काष्ठा batadv_hard_अगरace *hard_अगरace);
व्योम batadv_v_elp_primary_अगरace_set(काष्ठा batadv_hard_अगरace *primary_अगरace);
पूर्णांक batadv_v_elp_packet_recv(काष्ठा sk_buff *skb,
			     काष्ठा batadv_hard_अगरace *अगर_incoming);
व्योम batadv_v_elp_throughput_metric_update(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर /* _NET_BATMAN_ADV_BAT_V_ELP_H_ */
