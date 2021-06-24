<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _NET_FAILOVER_H
#घोषणा _NET_FAILOVER_H

#समावेश <net/failover.h>

/* failover state */
काष्ठा net_failover_info अणु
	/* primary netdev with same MAC */
	काष्ठा net_device __rcu *primary_dev;

	/* standby netdev */
	काष्ठा net_device __rcu *standby_dev;

	/* primary netdev stats */
	काष्ठा rtnl_link_stats64 primary_stats;

	/* standby netdev stats */
	काष्ठा rtnl_link_stats64 standby_stats;

	/* aggregated stats */
	काष्ठा rtnl_link_stats64 failover_stats;

	/* spinlock जबतक updating stats */
	spinlock_t stats_lock;
पूर्ण;

काष्ठा failover *net_failover_create(काष्ठा net_device *standby_dev);
व्योम net_failover_destroy(काष्ठा failover *failover);

#घोषणा FAILOVER_VLAN_FEATURES	(NETIF_F_HW_CSUM | NETIF_F_SG | \
				 NETIF_F_FRAGLIST | NETIF_F_ALL_TSO | \
				 NETIF_F_HIGHDMA | NETIF_F_LRO)

#घोषणा FAILOVER_ENC_FEATURES	(NETIF_F_HW_CSUM | NETIF_F_SG | \
				 NETIF_F_RXCSUM | NETIF_F_ALL_TSO)

#पूर्ण_अगर /* _NET_FAILOVER_H */
