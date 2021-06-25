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

#अगर_अघोषित EFX_EF100_RX_H
#घोषणा EFX_EF100_RX_H

#समावेश "net_driver.h"

bool ef100_rx_buf_hash_valid(स्थिर u8 *prefix);
व्योम efx_ef100_ev_rx(काष्ठा efx_channel *channel, स्थिर efx_qword_t *p_event);
व्योम ef100_rx_ग_लिखो(काष्ठा efx_rx_queue *rx_queue);
व्योम __ef100_rx_packet(काष्ठा efx_channel *channel);

#पूर्ण_अगर
