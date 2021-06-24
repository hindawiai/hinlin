<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * O(1) TX queue with built-in allocator.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#अगर_अघोषित WFX_QUEUE_H
#घोषणा WFX_QUEUE_H

#समावेश <linux/skbuff.h>
#समावेश <linux/atomic.h>

काष्ठा wfx_dev;
काष्ठा wfx_vअगर;

काष्ठा wfx_queue अणु
	काष्ठा sk_buff_head	normal;
	काष्ठा sk_buff_head	cab; // Content After (DTIM) Beacon
	atomic_t		pending_frames;
	पूर्णांक			priority;
पूर्ण;

व्योम wfx_tx_lock(काष्ठा wfx_dev *wdev);
व्योम wfx_tx_unlock(काष्ठा wfx_dev *wdev);
व्योम wfx_tx_flush(काष्ठा wfx_dev *wdev);
व्योम wfx_tx_lock_flush(काष्ठा wfx_dev *wdev);

व्योम wfx_tx_queues_init(काष्ठा wfx_vअगर *wvअगर);
व्योम wfx_tx_queues_check_empty(काष्ठा wfx_vअगर *wvअगर);
bool wfx_tx_queues_has_cab(काष्ठा wfx_vअगर *wvअगर);
व्योम wfx_tx_queues_put(काष्ठा wfx_vअगर *wvअगर, काष्ठा sk_buff *skb);
काष्ठा hअगर_msg *wfx_tx_queues_get(काष्ठा wfx_dev *wdev);

bool wfx_tx_queue_empty(काष्ठा wfx_vअगर *wvअगर, काष्ठा wfx_queue *queue);
व्योम wfx_tx_queue_drop(काष्ठा wfx_vअगर *wvअगर, काष्ठा wfx_queue *queue,
		       काष्ठा sk_buff_head *dropped);

काष्ठा sk_buff *wfx_pending_get(काष्ठा wfx_dev *wdev, u32 packet_id);
व्योम wfx_pending_drop(काष्ठा wfx_dev *wdev, काष्ठा sk_buff_head *dropped);
अचिन्हित पूर्णांक wfx_pending_get_pkt_us_delay(काष्ठा wfx_dev *wdev,
					  काष्ठा sk_buff *skb);
व्योम wfx_pending_dump_old_frames(काष्ठा wfx_dev *wdev, अचिन्हित पूर्णांक limit_ms);

#पूर्ण_अगर /* WFX_QUEUE_H */
