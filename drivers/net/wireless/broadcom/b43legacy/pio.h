<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43legacy_PIO_H_
#घोषणा B43legacy_PIO_H_

#समावेश "b43legacy.h"

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>


#घोषणा B43legacy_PIO_TXCTL		0x00
#घोषणा B43legacy_PIO_TXDATA		0x02
#घोषणा B43legacy_PIO_TXQबफ_मानE	0x04
#घोषणा B43legacy_PIO_RXCTL		0x08
#घोषणा B43legacy_PIO_RXDATA		0x0A

#घोषणा B43legacy_PIO_TXCTL_WRITELO	(1 << 0)
#घोषणा B43legacy_PIO_TXCTL_WRITEHI	(1 << 1)
#घोषणा B43legacy_PIO_TXCTL_COMPLETE	(1 << 2)
#घोषणा B43legacy_PIO_TXCTL_INIT	(1 << 3)
#घोषणा B43legacy_PIO_TXCTL_SUSPEND	(1 << 7)

#घोषणा B43legacy_PIO_RXCTL_DATAAVAILABLE	(1 << 0)
#घोषणा B43legacy_PIO_RXCTL_READY		(1 << 1)

/* PIO स्थिरants */
#घोषणा B43legacy_PIO_MAXTXDEVQPACKETS	31
#घोषणा B43legacy_PIO_TXQADJUST		80

/* PIO tuning knobs */
#घोषणा B43legacy_PIO_MAXTXPACKETS	256



#अगर_घोषित CONFIG_B43LEGACY_PIO


काष्ठा b43legacy_pioqueue;
काष्ठा b43legacy_xmitstatus;

काष्ठा b43legacy_pio_txpacket अणु
	काष्ठा b43legacy_pioqueue *queue;
	काष्ठा sk_buff *skb;
	काष्ठा list_head list;
पूर्ण;

#घोषणा pio_txpacket_getindex(packet) ((पूर्णांक)((packet) - \
			      (packet)->queue->tx_packets_cache))

काष्ठा b43legacy_pioqueue अणु
	काष्ठा b43legacy_wldev *dev;
	u16 mmio_base;

	bool tx_suspended;
	bool tx_frozen;
	bool need_workarounds; /* Workarounds needed क्रम core.rev < 3 */

	/* Adjusted size of the device पूर्णांकernal TX buffer. */
	u16 tx_devq_size;
	/* Used octets of the device पूर्णांकernal TX buffer. */
	u16 tx_devq_used;
	/* Used packet slots in the device पूर्णांकernal TX buffer. */
	u8 tx_devq_packets;
	/* Packets from the txमुक्त list can
	 * be taken on incoming TX requests.
	 */
	काष्ठा list_head txमुक्त;
	अचिन्हित पूर्णांक nr_txमुक्त;
	/* Packets on the txqueue are queued,
	 * but not completely written to the chip, yet.
	 */
	काष्ठा list_head txqueue;
	/* Packets on the txrunning queue are completely
	 * posted to the device. We are रुकोing क्रम the txstatus.
	 */
	काष्ठा list_head txrunning;
	काष्ठा tasklet_काष्ठा txtask;
	काष्ठा b43legacy_pio_txpacket
			 tx_packets_cache[B43legacy_PIO_MAXTXPACKETS];
पूर्ण;

अटल अंतरभूत
u16 b43legacy_pio_पढ़ो(काष्ठा b43legacy_pioqueue *queue,
		     u16 offset)
अणु
	वापस b43legacy_पढ़ो16(queue->dev, queue->mmio_base + offset);
पूर्ण

अटल अंतरभूत
व्योम b43legacy_pio_ग_लिखो(काष्ठा b43legacy_pioqueue *queue,
		       u16 offset, u16 value)
अणु
	b43legacy_ग_लिखो16(queue->dev, queue->mmio_base + offset, value);
पूर्ण


पूर्णांक b43legacy_pio_init(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_pio_मुक्त(काष्ठा b43legacy_wldev *dev);

पूर्णांक b43legacy_pio_tx(काष्ठा b43legacy_wldev *dev,
		   काष्ठा sk_buff *skb);
व्योम b43legacy_pio_handle_txstatus(काष्ठा b43legacy_wldev *dev,
				 स्थिर काष्ठा b43legacy_txstatus *status);
व्योम b43legacy_pio_rx(काष्ठा b43legacy_pioqueue *queue);

/* Suspend TX queue in hardware. */
व्योम b43legacy_pio_tx_suspend(काष्ठा b43legacy_pioqueue *queue);
व्योम b43legacy_pio_tx_resume(काष्ठा b43legacy_pioqueue *queue);
/* Suspend (मुक्तze) the TX tasklet (software level). */
व्योम b43legacy_pio_मुक्तze_txqueues(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_pio_thaw_txqueues(काष्ठा b43legacy_wldev *dev);

#अन्यथा /* CONFIG_B43LEGACY_PIO */

अटल अंतरभूत
पूर्णांक b43legacy_pio_init(काष्ठा b43legacy_wldev *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत
व्योम b43legacy_pio_मुक्त(काष्ठा b43legacy_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत
पूर्णांक b43legacy_pio_tx(काष्ठा b43legacy_wldev *dev,
		   काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत
व्योम b43legacy_pio_handle_txstatus(काष्ठा b43legacy_wldev *dev,
				 स्थिर काष्ठा b43legacy_txstatus *status)
अणु
पूर्ण
अटल अंतरभूत
व्योम b43legacy_pio_rx(काष्ठा b43legacy_pioqueue *queue)
अणु
पूर्ण
अटल अंतरभूत
व्योम b43legacy_pio_tx_suspend(काष्ठा b43legacy_pioqueue *queue)
अणु
पूर्ण
अटल अंतरभूत
व्योम b43legacy_pio_tx_resume(काष्ठा b43legacy_pioqueue *queue)
अणु
पूर्ण
अटल अंतरभूत
व्योम b43legacy_pio_मुक्तze_txqueues(काष्ठा b43legacy_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत
व्योम b43legacy_pio_thaw_txqueues(काष्ठा b43legacy_wldev *dev)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_B43LEGACY_PIO */
#पूर्ण_अगर /* B43legacy_PIO_H_ */
