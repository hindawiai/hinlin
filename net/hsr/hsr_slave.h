<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * include file क्रम HSR and PRP.
 */

#अगर_अघोषित __HSR_SLAVE_H
#घोषणा __HSR_SLAVE_H

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश "hsr_main.h"

पूर्णांक hsr_add_port(काष्ठा hsr_priv *hsr, काष्ठा net_device *dev,
		 क्रमागत hsr_port_type pt, काष्ठा netlink_ext_ack *extack);
व्योम hsr_del_port(काष्ठा hsr_port *port);
bool hsr_port_exists(स्थिर काष्ठा net_device *dev);

अटल अंतरभूत काष्ठा hsr_port *hsr_port_get_rtnl(स्थिर काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();
	वापस hsr_port_exists(dev) ?
				rtnl_dereference(dev->rx_handler_data) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hsr_port *hsr_port_get_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस hsr_port_exists(dev) ?
				rcu_dereference(dev->rx_handler_data) : शून्य;
पूर्ण

bool hsr_invalid_dan_ingress_frame(__be16 protocol);

#पूर्ण_अगर /* __HSR_SLAVE_H */
