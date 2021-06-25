<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2013-2014, 2016-2018 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _RMNET_PRIVATE_H_
#घोषणा _RMNET_PRIVATE_H_

#घोषणा RMNET_MAX_PACKET_SIZE      16384
#घोषणा RMNET_DFLT_PACKET_SIZE     1500
#घोषणा RMNET_NEEDED_HEADROOM      16
#घोषणा RMNET_TX_QUEUE_LEN         1000

/* Replace skb->dev to a भव rmnet device and pass up the stack */
#घोषणा RMNET_EPMODE_VND (1)
/* Pass the frame directly to another device with dev_queue_xmit() */
#घोषणा RMNET_EPMODE_BRIDGE (2)

#पूर्ण_अगर /* _RMNET_PRIVATE_H_ */
