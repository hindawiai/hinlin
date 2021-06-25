<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interrupt bottom half.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#अगर_अघोषित WFX_BH_H
#घोषणा WFX_BH_H

#समावेश <linux/atomic.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

काष्ठा wfx_dev;

काष्ठा wfx_hअगर अणु
	काष्ठा work_काष्ठा bh;
	काष्ठा completion ctrl_पढ़ोy;
	रुको_queue_head_t tx_buffers_empty;
	atomic_t ctrl_reg;
	पूर्णांक rx_seqnum;
	पूर्णांक tx_seqnum;
	पूर्णांक tx_buffers_used;
पूर्ण;

व्योम wfx_bh_रेजिस्टर(काष्ठा wfx_dev *wdev);
व्योम wfx_bh_unरेजिस्टर(काष्ठा wfx_dev *wdev);
व्योम wfx_bh_request_rx(काष्ठा wfx_dev *wdev);
व्योम wfx_bh_request_tx(काष्ठा wfx_dev *wdev);
व्योम wfx_bh_poll_irq(काष्ठा wfx_dev *wdev);

#पूर्ण_अगर /* WFX_BH_H */
