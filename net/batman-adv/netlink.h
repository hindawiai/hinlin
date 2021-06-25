<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Matthias Schअगरfer
 */

#अगर_अघोषित _NET_BATMAN_ADV_NETLINK_H_
#घोषणा _NET_BATMAN_ADV_NETLINK_H_

#समावेश "main.h"

#समावेश <linux/netlink.h>
#समावेश <linux/types.h>
#समावेश <net/genetlink.h>

व्योम batadv_netlink_रेजिस्टर(व्योम);
व्योम batadv_netlink_unरेजिस्टर(व्योम);
पूर्णांक batadv_netlink_get_अगरindex(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक attrtype);

पूर्णांक batadv_netlink_tpmeter_notअगरy(काष्ठा batadv_priv *bat_priv, स्थिर u8 *dst,
				  u8 result, u32 test_समय, u64 total_bytes,
				  u32 cookie);

पूर्णांक batadv_netlink_notअगरy_mesh(काष्ठा batadv_priv *bat_priv);
पूर्णांक batadv_netlink_notअगरy_hardअगर(काष्ठा batadv_priv *bat_priv,
				 काष्ठा batadv_hard_अगरace *hard_अगरace);
पूर्णांक batadv_netlink_notअगरy_vlan(काष्ठा batadv_priv *bat_priv,
			       काष्ठा batadv_softअगर_vlan *vlan);

बाह्य काष्ठा genl_family batadv_netlink_family;

#पूर्ण_अगर /* _NET_BATMAN_ADV_NETLINK_H_ */
