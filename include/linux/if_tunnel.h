<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IF_TUNNEL_H_
#घोषणा _IF_TUNNEL_H_

#समावेश <linux/ip.h>
#समावेश <linux/in6.h>
#समावेश <uapi/linux/अगर_tunnel.h>
#समावेश <linux/u64_stats_sync.h>

/*
 * Locking : hash tables are रक्षित by RCU and RTNL
 */

#घोषणा क्रम_each_ip_tunnel_rcu(pos, start) \
	क्रम (pos = rcu_dereference(start); pos; pos = rcu_dereference(pos->next))

#पूर्ण_अगर /* _IF_TUNNEL_H_ */
