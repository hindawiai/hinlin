<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*	Copyright (C) 2009 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
 *	Copyright (C) 2009 Alban Browaeys <prahal@yahoo.com>
 *	Copyright (C) 2009 Felix Fietkau <nbd@खोलोwrt.org>
 *	Copyright (C) 2009 Luis Correia <luis.f.correia@gmail.com>
 *	Copyright (C) 2009 Mattias Nissler <mattias.nissler@gmx.de>
 *	Copyright (C) 2009 Mark Asselstine <asselsm@gmail.com>
 *	Copyright (C) 2009 Xose Vazquez Perez <xose.vazquez@gmail.com>
 *	Copyright (C) 2009 Bart Zolnierkiewicz <bzolnier@gmail.com>
 *	<http://rt2x00.serialmonkey.com>
 */

/*	Module: rt2800mmio
 *	Abstract: क्रमward declarations क्रम the rt2800mmio module.
 */

#अगर_अघोषित RT2800MMIO_H
#घोषणा RT2800MMIO_H

/*
 * Queue रेजिस्टर offset macros
 */
#घोषणा TX_QUEUE_REG_OFFSET	0x10
#घोषणा TX_BASE_PTR(__x)	(TX_BASE_PTR0 + ((__x) * TX_QUEUE_REG_OFFSET))
#घोषणा TX_MAX_CNT(__x)		(TX_MAX_CNT0 + ((__x) * TX_QUEUE_REG_OFFSET))
#घोषणा TX_CTX_IDX(__x)		(TX_CTX_IDX0 + ((__x) * TX_QUEUE_REG_OFFSET))
#घोषणा TX_DTX_IDX(__x)		(TX_DTX_IDX0 + ((__x) * TX_QUEUE_REG_OFFSET))

/*
 * DMA descriptor defines.
 */
#घोषणा TXD_DESC_SIZE			(4 * माप(__le32))
#घोषणा RXD_DESC_SIZE			(4 * माप(__le32))

/*
 * TX descriptor क्रमmat क्रम TX, PRIO and Beacon Ring.
 */

/*
 * Word0
 */
#घोषणा TXD_W0_SD_PTR0			FIELD32(0xffffffff)

/*
 * Word1
 */
#घोषणा TXD_W1_SD_LEN1			FIELD32(0x00003fff)
#घोषणा TXD_W1_LAST_SEC1		FIELD32(0x00004000)
#घोषणा TXD_W1_BURST			FIELD32(0x00008000)
#घोषणा TXD_W1_SD_LEN0			FIELD32(0x3fff0000)
#घोषणा TXD_W1_LAST_SEC0		FIELD32(0x40000000)
#घोषणा TXD_W1_DMA_DONE			FIELD32(0x80000000)

/*
 * Word2
 */
#घोषणा TXD_W2_SD_PTR1			FIELD32(0xffffffff)

/*
 * Word3
 * WIV: Wireless Info Valid. 1: Driver filled WI, 0: DMA needs to copy WI
 * QSEL: Select on-chip FIFO ID क्रम 2nd-stage output scheduler.
 *       0:MGMT, 1:HCCA 2:EDCA
 */
#घोषणा TXD_W3_WIV			FIELD32(0x01000000)
#घोषणा TXD_W3_QSEL			FIELD32(0x06000000)
#घोषणा TXD_W3_TCO			FIELD32(0x20000000)
#घोषणा TXD_W3_UCO			FIELD32(0x40000000)
#घोषणा TXD_W3_ICO			FIELD32(0x80000000)

/*
 * RX descriptor क्रमmat क्रम RX Ring.
 */

/*
 * Word0
 */
#घोषणा RXD_W0_SDP0			FIELD32(0xffffffff)

/*
 * Word1
 */
#घोषणा RXD_W1_SDL1			FIELD32(0x00003fff)
#घोषणा RXD_W1_SDL0			FIELD32(0x3fff0000)
#घोषणा RXD_W1_LS0			FIELD32(0x40000000)
#घोषणा RXD_W1_DMA_DONE			FIELD32(0x80000000)

/*
 * Word2
 */
#घोषणा RXD_W2_SDP1			FIELD32(0xffffffff)

/*
 * Word3
 * AMSDU: RX with 802.3 header, not 802.11 header.
 * DECRYPTED: This frame is being decrypted.
 */
#घोषणा RXD_W3_BA			FIELD32(0x00000001)
#घोषणा RXD_W3_DATA			FIELD32(0x00000002)
#घोषणा RXD_W3_शून्यDATA			FIELD32(0x00000004)
#घोषणा RXD_W3_FRAG			FIELD32(0x00000008)
#घोषणा RXD_W3_UNICAST_TO_ME		FIELD32(0x00000010)
#घोषणा RXD_W3_MULTICAST		FIELD32(0x00000020)
#घोषणा RXD_W3_BROADCAST		FIELD32(0x00000040)
#घोषणा RXD_W3_MY_BSS			FIELD32(0x00000080)
#घोषणा RXD_W3_CRC_ERROR		FIELD32(0x00000100)
#घोषणा RXD_W3_CIPHER_ERROR		FIELD32(0x00000600)
#घोषणा RXD_W3_AMSDU			FIELD32(0x00000800)
#घोषणा RXD_W3_HTC			FIELD32(0x00001000)
#घोषणा RXD_W3_RSSI			FIELD32(0x00002000)
#घोषणा RXD_W3_L2PAD			FIELD32(0x00004000)
#घोषणा RXD_W3_AMPDU			FIELD32(0x00008000)
#घोषणा RXD_W3_DECRYPTED		FIELD32(0x00010000)
#घोषणा RXD_W3_PLCP_SIGNAL		FIELD32(0x00020000)
#घोषणा RXD_W3_PLCP_RSSI		FIELD32(0x00040000)

अचिन्हित पूर्णांक rt2800mmio_get_dma_करोne(काष्ठा data_queue *queue);

/* TX descriptor initialization */
__le32 *rt2800mmio_get_txwi(काष्ठा queue_entry *entry);
व्योम rt2800mmio_ग_लिखो_tx_desc(काष्ठा queue_entry *entry,
			      काष्ठा txentry_desc *txdesc);

/* RX control handlers */
व्योम rt2800mmio_fill_rxकरोne(काष्ठा queue_entry *entry,
			    काष्ठा rxकरोne_entry_desc *rxdesc);

/* Interrupt functions */
व्योम rt2800mmio_txstatus_tasklet(काष्ठा tasklet_काष्ठा *t);
व्योम rt2800mmio_pretbtt_tasklet(काष्ठा tasklet_काष्ठा *t);
व्योम rt2800mmio_tbtt_tasklet(काष्ठा tasklet_काष्ठा *t);
व्योम rt2800mmio_rxकरोne_tasklet(काष्ठा tasklet_काष्ठा *t);
व्योम rt2800mmio_स्वतःwake_tasklet(काष्ठा tasklet_काष्ठा *t);
irqवापस_t rt2800mmio_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
व्योम rt2800mmio_toggle_irq(काष्ठा rt2x00_dev *rt2x00dev,
			   क्रमागत dev_state state);

/* Queue handlers */
व्योम rt2800mmio_start_queue(काष्ठा data_queue *queue);
व्योम rt2800mmio_kick_queue(काष्ठा data_queue *queue);
व्योम rt2800mmio_flush_queue(काष्ठा data_queue *queue, bool drop);
व्योम rt2800mmio_stop_queue(काष्ठा data_queue *queue);
व्योम rt2800mmio_queue_init(काष्ठा data_queue *queue);

/* Initialization functions */
पूर्णांक rt2800mmio_probe_hw(काष्ठा rt2x00_dev *rt2x00dev);
bool rt2800mmio_get_entry_state(काष्ठा queue_entry *entry);
व्योम rt2800mmio_clear_entry(काष्ठा queue_entry *entry);
पूर्णांक rt2800mmio_init_queues(काष्ठा rt2x00_dev *rt2x00dev);
पूर्णांक rt2800mmio_init_रेजिस्टरs(काष्ठा rt2x00_dev *rt2x00dev);

/* Device state चयन handlers. */
पूर्णांक rt2800mmio_enable_radio(काष्ठा rt2x00_dev *rt2x00dev);

#पूर्ण_अगर /* RT2800MMIO_H */
