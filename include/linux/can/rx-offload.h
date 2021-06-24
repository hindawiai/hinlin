<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/can/rx-offload.h
 *
 * Copyright (c) 2014 David Jander, Protonic Holland
 * Copyright (c) 2014-2017 Pengutronix, Marc Kleine-Budde <kernel@pengutronix.de>
 */

#अगर_अघोषित _CAN_RX_OFFLOAD_H
#घोषणा _CAN_RX_OFFLOAD_H

#समावेश <linux/netdevice.h>
#समावेश <linux/can.h>

काष्ठा can_rx_offload अणु
	काष्ठा net_device *dev;

	काष्ठा sk_buff *(*mailbox_पढ़ो)(काष्ठा can_rx_offload *offload,
					अचिन्हित पूर्णांक mb, u32 *बारtamp,
					bool drop);

	काष्ठा sk_buff_head skb_queue;
	u32 skb_queue_len_max;

	अचिन्हित पूर्णांक mb_first;
	अचिन्हित पूर्णांक mb_last;

	काष्ठा napi_काष्ठा napi;

	bool inc;
पूर्ण;

पूर्णांक can_rx_offload_add_बारtamp(काष्ठा net_device *dev,
				 काष्ठा can_rx_offload *offload);
पूर्णांक can_rx_offload_add_fअगरo(काष्ठा net_device *dev,
			    काष्ठा can_rx_offload *offload,
			    अचिन्हित पूर्णांक weight);
पूर्णांक can_rx_offload_add_manual(काष्ठा net_device *dev,
			      काष्ठा can_rx_offload *offload,
			      अचिन्हित पूर्णांक weight);
पूर्णांक can_rx_offload_irq_offload_बारtamp(काष्ठा can_rx_offload *offload,
					 u64 reg);
पूर्णांक can_rx_offload_irq_offload_fअगरo(काष्ठा can_rx_offload *offload);
पूर्णांक can_rx_offload_queue_sorted(काष्ठा can_rx_offload *offload,
				काष्ठा sk_buff *skb, u32 बारtamp);
अचिन्हित पूर्णांक can_rx_offload_get_echo_skb(काष्ठा can_rx_offload *offload,
					 अचिन्हित पूर्णांक idx, u32 बारtamp,
					 अचिन्हित पूर्णांक *frame_len_ptr);
पूर्णांक can_rx_offload_queue_tail(काष्ठा can_rx_offload *offload,
			      काष्ठा sk_buff *skb);
व्योम can_rx_offload_del(काष्ठा can_rx_offload *offload);
व्योम can_rx_offload_enable(काष्ठा can_rx_offload *offload);

अटल अंतरभूत व्योम can_rx_offload_schedule(काष्ठा can_rx_offload *offload)
अणु
	napi_schedule(&offload->napi);
पूर्ण

अटल अंतरभूत व्योम can_rx_offload_disable(काष्ठा can_rx_offload *offload)
अणु
	napi_disable(&offload->napi);
पूर्ण

#पूर्ण_अगर /* !_CAN_RX_OFFLOAD_H */
