<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Linus Lथञssing
 */

#अगर_अघोषित _NET_BATMAN_ADV_BAT_ALGO_H_
#घोषणा _NET_BATMAN_ADV_BAT_ALGO_H_

#समावेश "main.h"

#समावेश <linux/netlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>

बाह्य अक्षर batadv_routing_algo[];
बाह्य काष्ठा list_head batadv_hardअगर_list;

व्योम batadv_algo_init(व्योम);
काष्ठा batadv_algo_ops *batadv_algo_get(स्थिर अक्षर *name);
पूर्णांक batadv_algo_रेजिस्टर(काष्ठा batadv_algo_ops *bat_algo_ops);
पूर्णांक batadv_algo_select(काष्ठा batadv_priv *bat_priv, स्थिर अक्षर *name);
पूर्णांक batadv_algo_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);

#पूर्ण_अगर /* _NET_BATMAN_ADV_BAT_ALGO_H_ */
