<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_PIO_H_
#घोषणा B43_PIO_H_

#समावेश "b43.h"

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>


/*** Registers क्रम PIO queues up to revision 7. ***/
/* TX queue. */
#घोषणा B43_PIO_TXCTL			0x00
#घोषणा  B43_PIO_TXCTL_WRITELO		0x0001
#घोषणा  B43_PIO_TXCTL_WRITEHI		0x0002
#घोषणा  B43_PIO_TXCTL_खातापूर्ण		0x0004
#घोषणा  B43_PIO_TXCTL_FREADY		0x0008
#घोषणा  B43_PIO_TXCTL_FLUSHREQ		0x0020
#घोषणा  B43_PIO_TXCTL_FLUSHPEND	0x0040
#घोषणा  B43_PIO_TXCTL_SUSPREQ		0x0080
#घोषणा  B43_PIO_TXCTL_QSUSP		0x0100
#घोषणा  B43_PIO_TXCTL_COMMCNT		0xFC00
#घोषणा  B43_PIO_TXCTL_COMMCNT_SHIFT	10
#घोषणा B43_PIO_TXDATA			0x02
#घोषणा B43_PIO_TXQबफ_मानE		0x04
/* RX queue. */
#घोषणा B43_PIO_RXCTL			0x00
#घोषणा  B43_PIO_RXCTL_FRAMERDY		0x0001
#घोषणा  B43_PIO_RXCTL_DATARDY		0x0002
#घोषणा B43_PIO_RXDATA			0x02

/*** Registers क्रम PIO queues revision 8 and later. ***/
/* TX queue */
#घोषणा B43_PIO8_TXCTL			0x00
#घोषणा  B43_PIO8_TXCTL_0_7		0x00000001
#घोषणा  B43_PIO8_TXCTL_8_15		0x00000002
#घोषणा  B43_PIO8_TXCTL_16_23		0x00000004
#घोषणा  B43_PIO8_TXCTL_24_31		0x00000008
#घोषणा  B43_PIO8_TXCTL_खातापूर्ण		0x00000010
#घोषणा  B43_PIO8_TXCTL_FREADY		0x00000080
#घोषणा  B43_PIO8_TXCTL_SUSPREQ		0x00000100
#घोषणा  B43_PIO8_TXCTL_QSUSP		0x00000200
#घोषणा  B43_PIO8_TXCTL_FLUSHREQ	0x00000400
#घोषणा  B43_PIO8_TXCTL_FLUSHPEND	0x00000800
#घोषणा B43_PIO8_TXDATA			0x04
/* RX queue */
#घोषणा B43_PIO8_RXCTL			0x00
#घोषणा  B43_PIO8_RXCTL_FRAMERDY	0x00000001
#घोषणा  B43_PIO8_RXCTL_DATARDY		0x00000002
#घोषणा B43_PIO8_RXDATA			0x04


/* The maximum number of TX-packets the HW can handle. */
#घोषणा B43_PIO_MAX_NR_TXPACKETS	32


काष्ठा b43_pio_txpacket अणु
	/* Poपूर्णांकer to the TX queue we beदीर्घ to. */
	काष्ठा b43_pio_txqueue *queue;
	/* The TX data packet. */
	काष्ठा sk_buff *skb;
	/* Index in the (काष्ठा b43_pio_txqueue)->packets array. */
	u8 index;

	काष्ठा list_head list;
पूर्ण;

काष्ठा b43_pio_txqueue अणु
	काष्ठा b43_wldev *dev;
	u16 mmio_base;

	/* The device queue buffer size in bytes. */
	u16 buffer_size;
	/* The number of used bytes in the device queue buffer. */
	u16 buffer_used;
	/* The number of packets that can still get queued.
	 * This is decremented on queueing a packet and incremented
	 * after receiving the transmit status. */
	u16 मुक्त_packet_slots;

	/* True, अगर the mac80211 queue was stopped due to overflow at TX. */
	bool stopped;
	/* Our b43 queue index number */
	u8 index;
	/* The mac80211 QoS queue priority. */
	u8 queue_prio;

	/* Buffer क्रम TX packet meta data. */
	काष्ठा b43_pio_txpacket packets[B43_PIO_MAX_NR_TXPACKETS];
	काष्ठा list_head packets_list;

	/* Shortcut to the 802.11 core revision. This is to
	 * aव्योम horrible poपूर्णांकer dereferencing in the fastpaths. */
	u8 rev;
पूर्ण;

काष्ठा b43_pio_rxqueue अणु
	काष्ठा b43_wldev *dev;
	u16 mmio_base;

	/* Shortcut to the 802.11 core revision. This is to
	 * aव्योम horrible poपूर्णांकer dereferencing in the fastpaths. */
	u8 rev;
पूर्ण;


अटल अंतरभूत u16 b43_piotx_पढ़ो16(काष्ठा b43_pio_txqueue *q, u16 offset)
अणु
	वापस b43_पढ़ो16(q->dev, q->mmio_base + offset);
पूर्ण

अटल अंतरभूत u32 b43_piotx_पढ़ो32(काष्ठा b43_pio_txqueue *q, u16 offset)
अणु
	वापस b43_पढ़ो32(q->dev, q->mmio_base + offset);
पूर्ण

अटल अंतरभूत व्योम b43_piotx_ग_लिखो16(काष्ठा b43_pio_txqueue *q,
				     u16 offset, u16 value)
अणु
	b43_ग_लिखो16(q->dev, q->mmio_base + offset, value);
पूर्ण

अटल अंतरभूत व्योम b43_piotx_ग_लिखो32(काष्ठा b43_pio_txqueue *q,
				     u16 offset, u32 value)
अणु
	b43_ग_लिखो32(q->dev, q->mmio_base + offset, value);
पूर्ण


अटल अंतरभूत u16 b43_piorx_पढ़ो16(काष्ठा b43_pio_rxqueue *q, u16 offset)
अणु
	वापस b43_पढ़ो16(q->dev, q->mmio_base + offset);
पूर्ण

अटल अंतरभूत u32 b43_piorx_पढ़ो32(काष्ठा b43_pio_rxqueue *q, u16 offset)
अणु
	वापस b43_पढ़ो32(q->dev, q->mmio_base + offset);
पूर्ण

अटल अंतरभूत व्योम b43_piorx_ग_लिखो16(काष्ठा b43_pio_rxqueue *q,
				     u16 offset, u16 value)
अणु
	b43_ग_लिखो16(q->dev, q->mmio_base + offset, value);
पूर्ण

अटल अंतरभूत व्योम b43_piorx_ग_लिखो32(काष्ठा b43_pio_rxqueue *q,
				     u16 offset, u32 value)
अणु
	b43_ग_लिखो32(q->dev, q->mmio_base + offset, value);
पूर्ण


पूर्णांक b43_pio_init(काष्ठा b43_wldev *dev);
व्योम b43_pio_मुक्त(काष्ठा b43_wldev *dev);

पूर्णांक b43_pio_tx(काष्ठा b43_wldev *dev, काष्ठा sk_buff *skb);
व्योम b43_pio_handle_txstatus(काष्ठा b43_wldev *dev,
			     स्थिर काष्ठा b43_txstatus *status);
व्योम b43_pio_rx(काष्ठा b43_pio_rxqueue *q);

व्योम b43_pio_tx_suspend(काष्ठा b43_wldev *dev);
व्योम b43_pio_tx_resume(काष्ठा b43_wldev *dev);

#पूर्ण_अगर /* B43_PIO_H_ */
