<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "nci_spi: %s: " fmt, __func__

#समावेश <linux/module.h>

#समावेश <linux/export.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <net/nfc/nci_core.h>

#घोषणा NCI_SPI_ACK_SHIFT		6
#घोषणा NCI_SPI_MSB_PAYLOAD_MASK	0x3F

#घोषणा NCI_SPI_SEND_TIMEOUT	(NCI_CMD_TIMEOUT > NCI_DATA_TIMEOUT ? \
					NCI_CMD_TIMEOUT : NCI_DATA_TIMEOUT)

#घोषणा NCI_SPI_सूचीECT_WRITE	0x01
#घोषणा NCI_SPI_सूचीECT_READ	0x02

#घोषणा ACKNOWLEDGE_NONE	0
#घोषणा ACKNOWLEDGE_ACK		1
#घोषणा ACKNOWLEDGE_NACK	2

#घोषणा CRC_INIT		0xFFFF

अटल पूर्णांक __nci_spi_send(काष्ठा nci_spi *nspi, काष्ठा sk_buff *skb,
			  पूर्णांक cs_change)
अणु
	काष्ठा spi_message m;
	काष्ठा spi_transfer t;

	स_रखो(&t, 0, माप(काष्ठा spi_transfer));
	/* a शून्य skb means we just want the SPI chip select line to उठाओ */
	अगर (skb) अणु
		t.tx_buf = skb->data;
		t.len = skb->len;
	पूर्ण अन्यथा अणु
		/* still set tx_buf non शून्य to make the driver happy */
		t.tx_buf = &t;
		t.len = 0;
	पूर्ण
	t.cs_change = cs_change;
	t.delay.value = nspi->xfer_udelay;
	t.delay.unit = SPI_DELAY_UNIT_USECS;
	t.speed_hz = nspi->xfer_speed_hz;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);

	वापस spi_sync(nspi->spi, &m);
पूर्ण

पूर्णांक nci_spi_send(काष्ठा nci_spi *nspi,
		 काष्ठा completion *ग_लिखो_handshake_completion,
		 काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक payload_len = skb->len;
	अचिन्हित अक्षर *hdr;
	पूर्णांक ret;
	दीर्घ completion_rc;

	/* add the NCI SPI header to the start of the buffer */
	hdr = skb_push(skb, NCI_SPI_HDR_LEN);
	hdr[0] = NCI_SPI_सूचीECT_WRITE;
	hdr[1] = nspi->acknowledge_mode;
	hdr[2] = payload_len >> 8;
	hdr[3] = payload_len & 0xFF;

	अगर (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED) अणु
		u16 crc;

		crc = crc_ccitt(CRC_INIT, skb->data, skb->len);
		skb_put_u8(skb, crc >> 8);
		skb_put_u8(skb, crc & 0xFF);
	पूर्ण

	अगर (ग_लिखो_handshake_completion)	अणु
		/* Trick SPI driver to उठाओ chip select */
		ret = __nci_spi_send(nspi, शून्य, 1);
		अगर (ret)
			जाओ करोne;

		/* रुको क्रम NFC chip hardware handshake to complete */
		अगर (रुको_क्रम_completion_समयout(ग_लिखो_handshake_completion,
						msecs_to_jअगरfies(1000)) == 0) अणु
			ret = -ETIME;
			जाओ करोne;
		पूर्ण
	पूर्ण

	ret = __nci_spi_send(nspi, skb, 0);
	अगर (ret != 0 || nspi->acknowledge_mode == NCI_SPI_CRC_DISABLED)
		जाओ करोne;

	reinit_completion(&nspi->req_completion);
	completion_rc =	रुको_क्रम_completion_पूर्णांकerruptible_समयout(
							&nspi->req_completion,
							NCI_SPI_SEND_TIMEOUT);

	अगर (completion_rc <= 0 || nspi->req_result == ACKNOWLEDGE_NACK)
		ret = -EIO;

करोne:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nci_spi_send);

/* ---- Interface to NCI SPI drivers ---- */

/**
 * nci_spi_allocate_spi - allocate a new nci spi
 *
 * @spi: SPI device
 * @acknowledge_mode: Acknowledge mode used by the NFC device
 * @delay: delay between transactions in us
 * @ndev: nci dev to send incoming nci frames to
 */
काष्ठा nci_spi *nci_spi_allocate_spi(काष्ठा spi_device *spi,
				     u8 acknowledge_mode, अचिन्हित पूर्णांक delay,
				     काष्ठा nci_dev *ndev)
अणु
	काष्ठा nci_spi *nspi;

	nspi = devm_kzalloc(&spi->dev, माप(काष्ठा nci_spi), GFP_KERNEL);
	अगर (!nspi)
		वापस शून्य;

	nspi->acknowledge_mode = acknowledge_mode;
	nspi->xfer_udelay = delay;
	/* Use controller max SPI speed by शेष */
	nspi->xfer_speed_hz = 0;
	nspi->spi = spi;
	nspi->ndev = ndev;
	init_completion(&nspi->req_completion);

	वापस nspi;
पूर्ण
EXPORT_SYMBOL_GPL(nci_spi_allocate_spi);

अटल पूर्णांक send_acknowledge(काष्ठा nci_spi *nspi, u8 acknowledge)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *hdr;
	u16 crc;
	पूर्णांक ret;

	skb = nci_skb_alloc(nspi->ndev, 0, GFP_KERNEL);

	/* add the NCI SPI header to the start of the buffer */
	hdr = skb_push(skb, NCI_SPI_HDR_LEN);
	hdr[0] = NCI_SPI_सूचीECT_WRITE;
	hdr[1] = NCI_SPI_CRC_ENABLED;
	hdr[2] = acknowledge << NCI_SPI_ACK_SHIFT;
	hdr[3] = 0;

	crc = crc_ccitt(CRC_INIT, skb->data, skb->len);
	skb_put_u8(skb, crc >> 8);
	skb_put_u8(skb, crc & 0xFF);

	ret = __nci_spi_send(nspi, skb, 0);

	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *__nci_spi_पढ़ो(काष्ठा nci_spi *nspi)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा spi_message m;
	अचिन्हित अक्षर req[2], resp_hdr[2];
	काष्ठा spi_transfer tx, rx;
	अचिन्हित लघु rx_len = 0;
	पूर्णांक ret;

	spi_message_init(&m);

	स_रखो(&tx, 0, माप(काष्ठा spi_transfer));
	req[0] = NCI_SPI_सूचीECT_READ;
	req[1] = nspi->acknowledge_mode;
	tx.tx_buf = req;
	tx.len = 2;
	tx.cs_change = 0;
	tx.speed_hz = nspi->xfer_speed_hz;
	spi_message_add_tail(&tx, &m);

	स_रखो(&rx, 0, माप(काष्ठा spi_transfer));
	rx.rx_buf = resp_hdr;
	rx.len = 2;
	rx.cs_change = 1;
	rx.speed_hz = nspi->xfer_speed_hz;
	spi_message_add_tail(&rx, &m);

	ret = spi_sync(nspi->spi, &m);
	अगर (ret)
		वापस शून्य;

	अगर (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED)
		rx_len = ((resp_hdr[0] & NCI_SPI_MSB_PAYLOAD_MASK) << 8) +
				resp_hdr[1] + NCI_SPI_CRC_LEN;
	अन्यथा
		rx_len = (resp_hdr[0] << 8) | resp_hdr[1];

	skb = nci_skb_alloc(nspi->ndev, rx_len, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	spi_message_init(&m);

	स_रखो(&rx, 0, माप(काष्ठा spi_transfer));
	rx.rx_buf = skb_put(skb, rx_len);
	rx.len = rx_len;
	rx.cs_change = 0;
	rx.delay.value = nspi->xfer_udelay;
	rx.delay.unit = SPI_DELAY_UNIT_USECS;
	rx.speed_hz = nspi->xfer_speed_hz;
	spi_message_add_tail(&rx, &m);

	ret = spi_sync(nspi->spi, &m);
	अगर (ret)
		जाओ receive_error;

	अगर (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED) अणु
		*(u8 *)skb_push(skb, 1) = resp_hdr[1];
		*(u8 *)skb_push(skb, 1) = resp_hdr[0];
	पूर्ण

	वापस skb;

receive_error:
	kमुक्त_skb(skb);

	वापस शून्य;
पूर्ण

अटल पूर्णांक nci_spi_check_crc(काष्ठा sk_buff *skb)
अणु
	u16 crc_data = (skb->data[skb->len - 2] << 8) |
			skb->data[skb->len - 1];
	पूर्णांक ret;

	ret = (crc_ccitt(CRC_INIT, skb->data, skb->len - NCI_SPI_CRC_LEN)
			== crc_data);

	skb_trim(skb, skb->len - NCI_SPI_CRC_LEN);

	वापस ret;
पूर्ण

अटल u8 nci_spi_get_ack(काष्ठा sk_buff *skb)
अणु
	u8 ret;

	ret = skb->data[0] >> NCI_SPI_ACK_SHIFT;

	/* Remove NFCC part of the header: ACK, NACK and MSB payload len */
	skb_pull(skb, 2);

	वापस ret;
पूर्ण

/**
 * nci_spi_पढ़ो - पढ़ो frame from NCI SPI drivers
 *
 * @nspi: The nci spi
 * Context: can sleep
 *
 * This call may only be used from a context that may sleep.  The sleep
 * is non-पूर्णांकerruptible, and has no समयout.
 *
 * It वापसs an allocated skb containing the frame on success, or शून्य.
 */
काष्ठा sk_buff *nci_spi_पढ़ो(काष्ठा nci_spi *nspi)
अणु
	काष्ठा sk_buff *skb;

	/* Retrieve frame from SPI */
	skb = __nci_spi_पढ़ो(nspi);
	अगर (!skb)
		जाओ करोne;

	अगर (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED) अणु
		अगर (!nci_spi_check_crc(skb)) अणु
			send_acknowledge(nspi, ACKNOWLEDGE_NACK);
			जाओ करोne;
		पूर्ण

		/* In हाल of acknowledged mode: अगर ACK or NACK received,
		 * unblock completion of latest frame sent.
		 */
		nspi->req_result = nci_spi_get_ack(skb);
		अगर (nspi->req_result)
			complete(&nspi->req_completion);
	पूर्ण

	/* If there is no payload (ACK/NACK only frame),
	 * मुक्त the socket buffer
	 */
	अगर (!skb->len) अणु
		kमुक्त_skb(skb);
		skb = शून्य;
		जाओ करोne;
	पूर्ण

	अगर (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED)
		send_acknowledge(nspi, ACKNOWLEDGE_ACK);

करोne:

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(nci_spi_पढ़ो);

MODULE_LICENSE("GPL");
