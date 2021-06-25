<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#अगर_अघोषित _NETLINK_K_H
#घोषणा _NETLINK_K_H

#समावेश <linux/netdevice.h>
#समावेश <net/sock.h>

काष्ठा sock *netlink_init(पूर्णांक unit,
			  व्योम (*cb)(काष्ठा net_device *dev,
				     u16 type, व्योम *msg, पूर्णांक len));
पूर्णांक netlink_send(काष्ठा sock *sock, पूर्णांक group, u16 type, व्योम *msg, पूर्णांक len,
		 काष्ठा net_device *dev);

#पूर्ण_अगर /* _NETLINK_K_H_ */
