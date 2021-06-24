<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#अगर_अघोषित _QTN_FMAC_SHM_IPC_H_
#घोषणा _QTN_FMAC_SHM_IPC_H_

#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>

#समावेश "shm_ipc_defs.h"

#घोषणा QTN_SHM_IPC_ACK_TIMEOUT		(2 * HZ)

काष्ठा qtnf_shm_ipc_पूर्णांक अणु
	व्योम (*fn)(व्योम *arg);
	व्योम *arg;
पूर्ण;

काष्ठा qtnf_shm_ipc_rx_callback अणु
	व्योम (*fn)(व्योम *arg, स्थिर u8 __iomem *buf, माप_प्रकार len);
	व्योम *arg;
पूर्ण;

क्रमागत qtnf_shm_ipc_direction अणु
	QTNF_SHM_IPC_OUTBOUND		= BIT(0),
	QTNF_SHM_IPC_INBOUND		= BIT(1),
पूर्ण;

काष्ठा qtnf_shm_ipc अणु
	काष्ठा qtnf_shm_ipc_region __iomem *shm_region;
	क्रमागत qtnf_shm_ipc_direction direction;
	माप_प्रकार tx_packet_count;
	माप_प्रकार rx_packet_count;

	माप_प्रकार tx_समयout_count;

	u8 रुकोing_क्रम_ack;

	काष्ठा qtnf_shm_ipc_पूर्णांक पूर्णांकerrupt;
	काष्ठा qtnf_shm_ipc_rx_callback rx_callback;

	व्योम (*irq_handler)(काष्ठा qtnf_shm_ipc *ipc);

	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा work_काष्ठा irq_work;
	काष्ठा completion tx_completion;
पूर्ण;

पूर्णांक qtnf_shm_ipc_init(काष्ठा qtnf_shm_ipc *ipc,
		      क्रमागत qtnf_shm_ipc_direction direction,
		      काष्ठा qtnf_shm_ipc_region __iomem *shm_region,
		      काष्ठा workqueue_काष्ठा *workqueue,
		      स्थिर काष्ठा qtnf_shm_ipc_पूर्णांक *पूर्णांकerrupt,
		      स्थिर काष्ठा qtnf_shm_ipc_rx_callback *rx_callback);
व्योम qtnf_shm_ipc_मुक्त(काष्ठा qtnf_shm_ipc *ipc);
पूर्णांक qtnf_shm_ipc_send(काष्ठा qtnf_shm_ipc *ipc, स्थिर u8 *buf, माप_प्रकार size);

अटल अंतरभूत व्योम qtnf_shm_ipc_irq_handler(काष्ठा qtnf_shm_ipc *ipc)
अणु
	ipc->irq_handler(ipc);
पूर्ण

#पूर्ण_अगर /* _QTN_FMAC_SHM_IPC_H_ */
