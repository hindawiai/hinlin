<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018-2021, Intel Corporation. */

#अगर_अघोषित _ICE_LAG_H_
#घोषणा _ICE_LAG_H_

#समावेश <linux/netdevice.h>

/* LAG roles क्रम netdev */
क्रमागत ice_lag_role अणु
	ICE_LAG_NONE,
	ICE_LAG_PRIMARY,
	ICE_LAG_BACKUP,
	ICE_LAG_UNSET
पूर्ण;

काष्ठा ice_pf;

/* LAG info काष्ठा */
काष्ठा ice_lag अणु
	काष्ठा ice_pf *pf; /* backlink to PF काष्ठा */
	काष्ठा net_device *netdev; /* this PF's netdev */
	काष्ठा net_device *peer_netdev;
	काष्ठा net_device *upper_netdev; /* upper bonding netdev */
	काष्ठा notअगरier_block notअगर_block;
	u8 bonded:1; /* currently bonded */
	u8 master:1; /* this is a master */
	u8 handler:1; /* did we रेजिस्टर a rx_netdev_handler */
	/* each thing blocking bonding will increment this value by one.
	 * If this value is zero, then bonding is allowed.
	 */
	u16 dis_lag;
	u8 role;
पूर्ण;

पूर्णांक ice_init_lag(काष्ठा ice_pf *pf);
व्योम ice_deinit_lag(काष्ठा ice_pf *pf);
rx_handler_result_t ice_lag_nop_handler(काष्ठा sk_buff **pskb);

/**
 * ice_disable_lag - increment LAG disable count
 * @lag: LAG काष्ठा
 */
अटल अंतरभूत व्योम ice_disable_lag(काष्ठा ice_lag *lag)
अणु
	/* If LAG this PF is not alपढ़ोy disabled, disable it */
	rtnl_lock();
	अगर (!netdev_is_rx_handler_busy(lag->netdev)) अणु
		अगर (!netdev_rx_handler_रेजिस्टर(lag->netdev,
						ice_lag_nop_handler,
						शून्य))
			lag->handler = true;
	पूर्ण
	rtnl_unlock();
	lag->dis_lag++;
पूर्ण

/**
 * ice_enable_lag - decrement disable count क्रम a PF
 * @lag: LAG काष्ठा
 *
 * Decrement the disable counter क्रम a port, and अगर that count reaches
 * zero, then हटाओ the no-op Rx handler from that netdev
 */
अटल अंतरभूत व्योम ice_enable_lag(काष्ठा ice_lag *lag)
अणु
	अगर (lag->dis_lag)
		lag->dis_lag--;
	अगर (!lag->dis_lag && lag->handler) अणु
		rtnl_lock();
		netdev_rx_handler_unरेजिस्टर(lag->netdev);
		rtnl_unlock();
		lag->handler = false;
	पूर्ण
पूर्ण

/**
 * ice_is_lag_dis - is LAG disabled
 * @lag: LAG काष्ठा
 *
 * Return true अगर bonding is disabled
 */
अटल अंतरभूत bool ice_is_lag_dis(काष्ठा ice_lag *lag)
अणु
	वापस !!(lag->dis_lag);
पूर्ण
#पूर्ण_अगर /* _ICE_LAG_H_ */
