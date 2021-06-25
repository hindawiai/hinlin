<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * For transport using shared mem काष्ठाure.
 *
 * Copyright (C) 2019 ARM Ltd.
 */

#समावेश <linux/पन.स>
#समावेश <linux/processor.h>
#समावेश <linux/types.h>

#समावेश "common.h"

/*
 * SCMI specअगरication requires all parameters, message headers, वापस
 * arguments or any protocol data to be expressed in little endian
 * क्रमmat only.
 */
काष्ठा scmi_shared_mem अणु
	__le32 reserved;
	__le32 channel_status;
#घोषणा SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR	BIT(1)
#घोषणा SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE	BIT(0)
	__le32 reserved1[2];
	__le32 flags;
#घोषणा SCMI_SHMEM_FLAG_INTR_ENABLED	BIT(0)
	__le32 length;
	__le32 msg_header;
	u8 msg_payload[];
पूर्ण;

व्योम shmem_tx_prepare(काष्ठा scmi_shared_mem __iomem *shmem,
		      काष्ठा scmi_xfer *xfer)
अणु
	/*
	 * Ideally channel must be मुक्त by now unless OS समयout last
	 * request and platक्रमm जारीd to process the same, रुको
	 * until it releases the shared memory, otherwise we may endup
	 * overwriting its response with new message payload or vice-versa
	 */
	spin_until_cond(ioपढ़ो32(&shmem->channel_status) &
			SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE);
	/* Mark channel busy + clear error */
	ioग_लिखो32(0x0, &shmem->channel_status);
	ioग_लिखो32(xfer->hdr.poll_completion ? 0 : SCMI_SHMEM_FLAG_INTR_ENABLED,
		  &shmem->flags);
	ioग_लिखो32(माप(shmem->msg_header) + xfer->tx.len, &shmem->length);
	ioग_लिखो32(pack_scmi_header(&xfer->hdr), &shmem->msg_header);
	अगर (xfer->tx.buf)
		स_नकल_toio(shmem->msg_payload, xfer->tx.buf, xfer->tx.len);
पूर्ण

u32 shmem_पढ़ो_header(काष्ठा scmi_shared_mem __iomem *shmem)
अणु
	वापस ioपढ़ो32(&shmem->msg_header);
पूर्ण

व्योम shmem_fetch_response(काष्ठा scmi_shared_mem __iomem *shmem,
			  काष्ठा scmi_xfer *xfer)
अणु
	xfer->hdr.status = ioपढ़ो32(shmem->msg_payload);
	/* Skip the length of header and status in shmem area i.e 8 bytes */
	xfer->rx.len = min_t(माप_प्रकार, xfer->rx.len,
			     ioपढ़ो32(&shmem->length) - 8);

	/* Take a copy to the rx buffer.. */
	स_नकल_fromio(xfer->rx.buf, shmem->msg_payload + 4, xfer->rx.len);
पूर्ण

व्योम shmem_fetch_notअगरication(काष्ठा scmi_shared_mem __iomem *shmem,
			      माप_प्रकार max_len, काष्ठा scmi_xfer *xfer)
अणु
	/* Skip only the length of header in shmem area i.e 4 bytes */
	xfer->rx.len = min_t(माप_प्रकार, max_len, ioपढ़ो32(&shmem->length) - 4);

	/* Take a copy to the rx buffer.. */
	स_नकल_fromio(xfer->rx.buf, shmem->msg_payload, xfer->rx.len);
पूर्ण

व्योम shmem_clear_channel(काष्ठा scmi_shared_mem __iomem *shmem)
अणु
	ioग_लिखो32(SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE, &shmem->channel_status);
पूर्ण

bool shmem_poll_करोne(काष्ठा scmi_shared_mem __iomem *shmem,
		     काष्ठा scmi_xfer *xfer)
अणु
	u16 xfer_id;

	xfer_id = MSG_XTRACT_TOKEN(ioपढ़ो32(&shmem->msg_header));

	अगर (xfer->hdr.seq != xfer_id)
		वापस false;

	वापस ioपढ़ो32(&shmem->channel_status) &
		(SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR |
		 SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE);
पूर्ण
