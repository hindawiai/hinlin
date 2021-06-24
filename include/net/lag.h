<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IF_LAG_H
#घोषणा _LINUX_IF_LAG_H

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_team.h>
#समावेश <net/bonding.h>

अटल अंतरभूत bool net_lag_port_dev_txable(स्थिर काष्ठा net_device *port_dev)
अणु
	अगर (netअगर_is_team_port(port_dev))
		वापस team_port_dev_txable(port_dev);
	अन्यथा
		वापस bond_is_active_slave_dev(port_dev);
पूर्ण

#पूर्ण_अगर /* _LINUX_IF_LAG_H */
