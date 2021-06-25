<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * include file क्रम HSR and PRP.
 */

#अगर_अघोषित __HSR_DEVICE_H
#घोषणा __HSR_DEVICE_H

#समावेश <linux/netdevice.h>
#समावेश "hsr_main.h"

व्योम hsr_del_ports(काष्ठा hsr_priv *hsr);
व्योम hsr_dev_setup(काष्ठा net_device *dev);
पूर्णांक hsr_dev_finalize(काष्ठा net_device *hsr_dev, काष्ठा net_device *slave[2],
		     अचिन्हित अक्षर multicast_spec, u8 protocol_version,
		     काष्ठा netlink_ext_ack *extack);
व्योम hsr_check_carrier_and_operstate(काष्ठा hsr_priv *hsr);
पूर्णांक hsr_get_max_mtu(काष्ठा hsr_priv *hsr);
#पूर्ण_अगर /* __HSR_DEVICE_H */
