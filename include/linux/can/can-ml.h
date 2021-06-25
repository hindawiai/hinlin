<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/* Copyright (c) 2002-2007 Volkswagen Group Electronic Research
 * Copyright (c) 2017 Pengutronix, Marc Kleine-Budde <kernel@pengutronix.de>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#अगर_अघोषित CAN_ML_H
#घोषणा CAN_ML_H

#समावेश <linux/can.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>

#घोषणा CAN_SFF_RCV_ARRAY_SZ (1 << CAN_SFF_ID_BITS)
#घोषणा CAN_EFF_RCV_HASH_BITS 10
#घोषणा CAN_EFF_RCV_ARRAY_SZ (1 << CAN_EFF_RCV_HASH_BITS)

क्रमागत अणु RX_ERR, RX_ALL, RX_FIL, RX_INV, RX_MAX पूर्ण;

काष्ठा can_dev_rcv_lists अणु
	काष्ठा hlist_head rx[RX_MAX];
	काष्ठा hlist_head rx_sff[CAN_SFF_RCV_ARRAY_SZ];
	काष्ठा hlist_head rx_eff[CAN_EFF_RCV_ARRAY_SZ];
	पूर्णांक entries;
पूर्ण;

काष्ठा can_ml_priv अणु
	काष्ठा can_dev_rcv_lists dev_rcv_lists;
#अगर_घोषित CAN_J1939
	काष्ठा j1939_priv *j1939_priv;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा can_ml_priv *can_get_ml_priv(काष्ठा net_device *dev)
अणु
	वापस netdev_get_ml_priv(dev, ML_PRIV_CAN);
पूर्ण

अटल अंतरभूत व्योम can_set_ml_priv(काष्ठा net_device *dev,
				   काष्ठा can_ml_priv *ml_priv)
अणु
	netdev_set_ml_priv(dev, ml_priv, ML_PRIV_CAN);
पूर्ण

#पूर्ण_अगर /* CAN_ML_H */
