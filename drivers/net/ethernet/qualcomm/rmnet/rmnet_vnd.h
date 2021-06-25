<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2013-2017, The Linux Foundation. All rights reserved.
 *
 * RMNET Data Virtual Network Device APIs
 */

#अगर_अघोषित _RMNET_VND_H_
#घोषणा _RMNET_VND_H_

पूर्णांक rmnet_vnd_करो_flow_control(काष्ठा net_device *dev, पूर्णांक enable);
पूर्णांक rmnet_vnd_newlink(u8 id, काष्ठा net_device *rmnet_dev,
		      काष्ठा rmnet_port *port,
		      काष्ठा net_device *real_dev,
		      काष्ठा rmnet_endpoपूर्णांक *ep,
		      काष्ठा netlink_ext_ack *extack);
पूर्णांक rmnet_vnd_dellink(u8 id, काष्ठा rmnet_port *port,
		      काष्ठा rmnet_endpoपूर्णांक *ep);
व्योम rmnet_vnd_rx_fixup(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
व्योम rmnet_vnd_tx_fixup(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
व्योम rmnet_vnd_setup(काष्ठा net_device *dev);
पूर्णांक rmnet_vnd_validate_real_dev_mtu(काष्ठा net_device *real_dev);
पूर्णांक rmnet_vnd_update_dev_mtu(काष्ठा rmnet_port *port,
			     काष्ठा net_device *real_dev);
#पूर्ण_अगर /* _RMNET_VND_H_ */
