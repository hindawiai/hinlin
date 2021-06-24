<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#समावेश <linux/types.h>
#समावेश <linux/पन.स>

#समावेश "shm_ipc.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"qtnfmac shm_ipc: %s: " fmt, __func__

अटल bool qtnf_shm_ipc_has_new_data(काष्ठा qtnf_shm_ipc *ipc)
अणु
	स्थिर u32 flags = पढ़ोl(&ipc->shm_region->headroom.hdr.flags);

	वापस (flags & QTNF_SHM_IPC_NEW_DATA);
पूर्ण

अटल व्योम qtnf_shm_handle_new_data(काष्ठा qtnf_shm_ipc *ipc)
अणु
	माप_प्रकार size;
	bool rx_buff_ok = true;
	काष्ठा qtnf_shm_ipc_region_header __iomem *shm_reg_hdr;

	shm_reg_hdr = &ipc->shm_region->headroom.hdr;

	size = पढ़ोw(&shm_reg_hdr->data_len);

	अगर (unlikely(size == 0 || size > QTN_IPC_MAX_DATA_SZ)) अणु
		pr_err("wrong rx packet size: %zu\n", size);
		rx_buff_ok = false;
	पूर्ण

	अगर (likely(rx_buff_ok)) अणु
		ipc->rx_packet_count++;
		ipc->rx_callback.fn(ipc->rx_callback.arg,
				    ipc->shm_region->data, size);
	पूर्ण

	ग_लिखोl(QTNF_SHM_IPC_ACK, &shm_reg_hdr->flags);
	पढ़ोl(&shm_reg_hdr->flags); /* flush PCIe ग_लिखो */

	ipc->पूर्णांकerrupt.fn(ipc->पूर्णांकerrupt.arg);
पूर्ण

अटल व्योम qtnf_shm_ipc_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qtnf_shm_ipc *ipc = container_of(work, काष्ठा qtnf_shm_ipc,
						irq_work);

	जबतक (qtnf_shm_ipc_has_new_data(ipc))
		qtnf_shm_handle_new_data(ipc);
पूर्ण

अटल व्योम qtnf_shm_ipc_irq_inbound_handler(काष्ठा qtnf_shm_ipc *ipc)
अणु
	u32 flags;

	flags = पढ़ोl(&ipc->shm_region->headroom.hdr.flags);

	अगर (flags & QTNF_SHM_IPC_NEW_DATA)
		queue_work(ipc->workqueue, &ipc->irq_work);
पूर्ण

अटल व्योम qtnf_shm_ipc_irq_outbound_handler(काष्ठा qtnf_shm_ipc *ipc)
अणु
	u32 flags;

	अगर (!READ_ONCE(ipc->रुकोing_क्रम_ack))
		वापस;

	flags = पढ़ोl(&ipc->shm_region->headroom.hdr.flags);

	अगर (flags & QTNF_SHM_IPC_ACK) अणु
		WRITE_ONCE(ipc->रुकोing_क्रम_ack, 0);
		complete(&ipc->tx_completion);
	पूर्ण
पूर्ण

पूर्णांक qtnf_shm_ipc_init(काष्ठा qtnf_shm_ipc *ipc,
		      क्रमागत qtnf_shm_ipc_direction direction,
		      काष्ठा qtnf_shm_ipc_region __iomem *shm_region,
		      काष्ठा workqueue_काष्ठा *workqueue,
		      स्थिर काष्ठा qtnf_shm_ipc_पूर्णांक *पूर्णांकerrupt,
		      स्थिर काष्ठा qtnf_shm_ipc_rx_callback *rx_callback)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा qtnf_shm_ipc_region, data) !=
		     QTN_IPC_REG_HDR_SZ);
	BUILD_BUG_ON(माप(काष्ठा qtnf_shm_ipc_region) > QTN_IPC_REG_SZ);

	ipc->shm_region = shm_region;
	ipc->direction = direction;
	ipc->पूर्णांकerrupt = *पूर्णांकerrupt;
	ipc->rx_callback = *rx_callback;
	ipc->tx_packet_count = 0;
	ipc->rx_packet_count = 0;
	ipc->workqueue = workqueue;
	ipc->रुकोing_क्रम_ack = 0;
	ipc->tx_समयout_count = 0;

	चयन (direction) अणु
	हाल QTNF_SHM_IPC_OUTBOUND:
		ipc->irq_handler = qtnf_shm_ipc_irq_outbound_handler;
		अवरोध;
	हाल QTNF_SHM_IPC_INBOUND:
		ipc->irq_handler = qtnf_shm_ipc_irq_inbound_handler;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	INIT_WORK(&ipc->irq_work, qtnf_shm_ipc_irq_work);
	init_completion(&ipc->tx_completion);

	वापस 0;
पूर्ण

व्योम qtnf_shm_ipc_मुक्त(काष्ठा qtnf_shm_ipc *ipc)
अणु
	complete_all(&ipc->tx_completion);
पूर्ण

पूर्णांक qtnf_shm_ipc_send(काष्ठा qtnf_shm_ipc *ipc, स्थिर u8 *buf, माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	काष्ठा qtnf_shm_ipc_region_header __iomem *shm_reg_hdr;

	shm_reg_hdr = &ipc->shm_region->headroom.hdr;

	अगर (unlikely(size > QTN_IPC_MAX_DATA_SZ))
		वापस -E2BIG;

	ipc->tx_packet_count++;

	ग_लिखोw(size, &shm_reg_hdr->data_len);
	स_नकल_toio(ipc->shm_region->data, buf, size);

	/* sync previous ग_लिखोs beक्रमe proceeding */
	dma_wmb();

	WRITE_ONCE(ipc->रुकोing_क्रम_ack, 1);

	/* sync previous memory ग_लिखो beक्रमe announcing new data पढ़ोy */
	wmb();

	ग_लिखोl(QTNF_SHM_IPC_NEW_DATA, &shm_reg_hdr->flags);
	पढ़ोl(&shm_reg_hdr->flags); /* flush PCIe ग_लिखो */

	ipc->पूर्णांकerrupt.fn(ipc->पूर्णांकerrupt.arg);

	अगर (!रुको_क्रम_completion_समयout(&ipc->tx_completion,
					 QTN_SHM_IPC_ACK_TIMEOUT)) अणु
		ret = -ETIMEDOUT;
		ipc->tx_समयout_count++;
		pr_err("TX ACK timeout\n");
	पूर्ण

	/* now we're not रुकोing क्रम ACK even in हाल of समयout */
	WRITE_ONCE(ipc->रुकोing_क्रम_ack, 0);

	वापस ret;
पूर्ण
