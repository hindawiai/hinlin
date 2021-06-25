<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2019 Solarflare Communications Inc.
 * Copyright 2019-2020 Xilinx Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#अगर_अघोषित EFX_EF100_TX_H
#घोषणा EFX_EF100_TX_H

#समावेश "net_driver.h"

पूर्णांक ef100_tx_probe(काष्ठा efx_tx_queue *tx_queue);
व्योम ef100_tx_init(काष्ठा efx_tx_queue *tx_queue);
व्योम ef100_tx_ग_लिखो(काष्ठा efx_tx_queue *tx_queue);
अचिन्हित पूर्णांक ef100_tx_max_skb_descs(काष्ठा efx_nic *efx);

व्योम ef100_ev_tx(काष्ठा efx_channel *channel, स्थिर efx_qword_t *p_event);

netdev_tx_t ef100_enqueue_skb(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb);
#पूर्ण_अगर
