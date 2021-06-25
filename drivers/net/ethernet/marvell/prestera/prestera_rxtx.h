<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved. */

#अगर_अघोषित _PRESTERA_RXTX_H_
#घोषणा _PRESTERA_RXTX_H_

#समावेश <linux/netdevice.h>

काष्ठा prestera_चयन;
काष्ठा prestera_port;

पूर्णांक prestera_rxtx_चयन_init(काष्ठा prestera_चयन *sw);
व्योम prestera_rxtx_चयन_fini(काष्ठा prestera_चयन *sw);

पूर्णांक prestera_rxtx_port_init(काष्ठा prestera_port *port);

netdev_tx_t prestera_rxtx_xmit(काष्ठा prestera_port *port, काष्ठा sk_buff *skb);

#पूर्ण_अगर /* _PRESTERA_RXTX_H_ */
