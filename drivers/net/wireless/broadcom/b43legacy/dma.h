<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43legacy_DMA_H_
#घोषणा B43legacy_DMA_H_

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/linkage.h>
#समावेश <linux/atomic.h>

#समावेश "b43legacy.h"


/* DMA-Interrupt reasons. */
#घोषणा B43legacy_DMAIRQ_FATALMASK	((1 << 10) | (1 << 11) | (1 << 12) \
					 | (1 << 14) | (1 << 15))
#घोषणा B43legacy_DMAIRQ_NONFATALMASK	(1 << 13)
#घोषणा B43legacy_DMAIRQ_RX_DONE		(1 << 16)


/*** 32-bit DMA Engine. ***/

/* 32-bit DMA controller रेजिस्टरs. */
#घोषणा B43legacy_DMA32_TXCTL				0x00
#घोषणा		B43legacy_DMA32_TXENABLE		0x00000001
#घोषणा		B43legacy_DMA32_TXSUSPEND		0x00000002
#घोषणा		B43legacy_DMA32_TXLOOPBACK		0x00000004
#घोषणा		B43legacy_DMA32_TXFLUSH			0x00000010
#घोषणा		B43legacy_DMA32_TXADDREXT_MASK		0x00030000
#घोषणा		B43legacy_DMA32_TXADDREXT_SHIFT		16
#घोषणा B43legacy_DMA32_TXRING				0x04
#घोषणा B43legacy_DMA32_TXINDEX				0x08
#घोषणा B43legacy_DMA32_TXSTATUS			0x0C
#घोषणा		B43legacy_DMA32_TXDPTR			0x00000FFF
#घोषणा		B43legacy_DMA32_TXSTATE			0x0000F000
#घोषणा			B43legacy_DMA32_TXSTAT_DISABLED	0x00000000
#घोषणा			B43legacy_DMA32_TXSTAT_ACTIVE	0x00001000
#घोषणा			B43legacy_DMA32_TXSTAT_IDLEWAIT	0x00002000
#घोषणा			B43legacy_DMA32_TXSTAT_STOPPED	0x00003000
#घोषणा			B43legacy_DMA32_TXSTAT_SUSP	0x00004000
#घोषणा		B43legacy_DMA32_TXERROR			0x000F0000
#घोषणा			B43legacy_DMA32_TXERR_NOERR	0x00000000
#घोषणा			B43legacy_DMA32_TXERR_PROT	0x00010000
#घोषणा			B43legacy_DMA32_TXERR_UNDERRUN	0x00020000
#घोषणा			B43legacy_DMA32_TXERR_BUFREAD	0x00030000
#घोषणा			B43legacy_DMA32_TXERR_DESCREAD	0x00040000
#घोषणा		B43legacy_DMA32_TXACTIVE		0xFFF00000
#घोषणा B43legacy_DMA32_RXCTL				0x10
#घोषणा		B43legacy_DMA32_RXENABLE		0x00000001
#घोषणा		B43legacy_DMA32_RXFROFF_MASK		0x000000FE
#घोषणा		B43legacy_DMA32_RXFROFF_SHIFT		1
#घोषणा		B43legacy_DMA32_RXसूचीECTFIFO		0x00000100
#घोषणा		B43legacy_DMA32_RXADDREXT_MASK		0x00030000
#घोषणा		B43legacy_DMA32_RXADDREXT_SHIFT		16
#घोषणा B43legacy_DMA32_RXRING				0x14
#घोषणा B43legacy_DMA32_RXINDEX				0x18
#घोषणा B43legacy_DMA32_RXSTATUS			0x1C
#घोषणा		B43legacy_DMA32_RXDPTR			0x00000FFF
#घोषणा		B43legacy_DMA32_RXSTATE			0x0000F000
#घोषणा			B43legacy_DMA32_RXSTAT_DISABLED	0x00000000
#घोषणा			B43legacy_DMA32_RXSTAT_ACTIVE	0x00001000
#घोषणा			B43legacy_DMA32_RXSTAT_IDLEWAIT	0x00002000
#घोषणा			B43legacy_DMA32_RXSTAT_STOPPED	0x00003000
#घोषणा		B43legacy_DMA32_RXERROR			0x000F0000
#घोषणा			B43legacy_DMA32_RXERR_NOERR	0x00000000
#घोषणा			B43legacy_DMA32_RXERR_PROT	0x00010000
#घोषणा			B43legacy_DMA32_RXERR_OVERFLOW	0x00020000
#घोषणा			B43legacy_DMA32_RXERR_BUFWRITE	0x00030000
#घोषणा			B43legacy_DMA32_RXERR_DESCREAD	0x00040000
#घोषणा		B43legacy_DMA32_RXACTIVE		0xFFF00000

/* 32-bit DMA descriptor. */
काष्ठा b43legacy_dmadesc32 अणु
	__le32 control;
	__le32 address;
पूर्ण __packed;
#घोषणा B43legacy_DMA32_DCTL_BYTECNT		0x00001FFF
#घोषणा B43legacy_DMA32_DCTL_ADDREXT_MASK	0x00030000
#घोषणा B43legacy_DMA32_DCTL_ADDREXT_SHIFT	16
#घोषणा B43legacy_DMA32_DCTL_DTABLEEND		0x10000000
#घोषणा B43legacy_DMA32_DCTL_IRQ		0x20000000
#घोषणा B43legacy_DMA32_DCTL_FRAMEEND		0x40000000
#घोषणा B43legacy_DMA32_DCTL_FRAMESTART		0x80000000


/* Misc DMA स्थिरants */
#घोषणा B43legacy_DMA_RINGMEMSIZE	PAGE_SIZE
#घोषणा B43legacy_DMA0_RX_FRAMखातापूर्णFSET	30
#घोषणा B43legacy_DMA3_RX_FRAMखातापूर्णFSET	0


/* DMA engine tuning knobs */
#घोषणा B43legacy_TXRING_SLOTS		128
#घोषणा B43legacy_RXRING_SLOTS		64
#घोषणा B43legacy_DMA0_RX_BUFFERSIZE	(2304 + 100)
#घोषणा B43legacy_DMA3_RX_BUFFERSIZE	16



#अगर_घोषित CONFIG_B43LEGACY_DMA


काष्ठा sk_buff;
काष्ठा b43legacy_निजी;
काष्ठा b43legacy_txstatus;


काष्ठा b43legacy_dmadesc_meta अणु
	/* The kernel DMA-able buffer. */
	काष्ठा sk_buff *skb;
	/* DMA base bus-address of the descriptor buffer. */
	dma_addr_t dmaaddr;
	/* ieee80211 TX status. Only used once per 802.11 frag. */
	bool is_last_fragment;
पूर्ण;

क्रमागत b43legacy_dmatype अणु
	B43legacy_DMA_30BIT = 30,
	B43legacy_DMA_32BIT = 32,
पूर्ण;

काष्ठा b43legacy_dmaring अणु
	/* Kernel भव base address of the ring memory. */
	व्योम *descbase;
	/* Meta data about all descriptors. */
	काष्ठा b43legacy_dmadesc_meta *meta;
	/* Cache of TX headers क्रम each slot.
	 * This is to aव्योम an allocation on each TX.
	 * This is शून्य क्रम an RX ring.
	 */
	u8 *txhdr_cache;
	/* (Unadjusted) DMA base bus-address of the ring memory. */
	dma_addr_t dmabase;
	/* Number of descriptor slots in the ring. */
	पूर्णांक nr_slots;
	/* Number of used descriptor slots. */
	पूर्णांक used_slots;
	/* Currently used slot in the ring. */
	पूर्णांक current_slot;
	/* Frameoffset in octets. */
	u32 frameoffset;
	/* Descriptor buffer size. */
	u16 rx_buffersize;
	/* The MMIO base रेजिस्टर of the DMA controller. */
	u16 mmio_base;
	/* DMA controller index number (0-5). */
	पूर्णांक index;
	/* Boolean. Is this a TX ring? */
	bool tx;
	/* The type of DMA engine used. */
	क्रमागत b43legacy_dmatype type;
	/* Boolean. Is this ring stopped at ieee80211 level? */
	bool stopped;
	/* The QOS priority asचिन्हित to this ring. Only used क्रम TX rings.
	 * This is the mac80211 "queue" value. */
	u8 queue_prio;
	काष्ठा b43legacy_wldev *dev;
#अगर_घोषित CONFIG_B43LEGACY_DEBUG
	/* Maximum number of used slots. */
	पूर्णांक max_used_slots;
	/* Last समय we injected a ring overflow. */
	अचिन्हित दीर्घ last_injected_overflow;
#पूर्ण_अगर /* CONFIG_B43LEGACY_DEBUG*/
पूर्ण;


अटल अंतरभूत
u32 b43legacy_dma_पढ़ो(काष्ठा b43legacy_dmaring *ring,
		       u16 offset)
अणु
	वापस b43legacy_पढ़ो32(ring->dev, ring->mmio_base + offset);
पूर्ण

अटल अंतरभूत
व्योम b43legacy_dma_ग_लिखो(काष्ठा b43legacy_dmaring *ring,
			 u16 offset, u32 value)
अणु
	b43legacy_ग_लिखो32(ring->dev, ring->mmio_base + offset, value);
पूर्ण


पूर्णांक b43legacy_dma_init(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_dma_मुक्त(काष्ठा b43legacy_wldev *dev);

व्योम b43legacy_dma_tx_suspend(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_dma_tx_resume(काष्ठा b43legacy_wldev *dev);

पूर्णांक b43legacy_dma_tx(काष्ठा b43legacy_wldev *dev,
		     काष्ठा sk_buff *skb);
व्योम b43legacy_dma_handle_txstatus(काष्ठा b43legacy_wldev *dev,
				   स्थिर काष्ठा b43legacy_txstatus *status);

व्योम b43legacy_dma_rx(काष्ठा b43legacy_dmaring *ring);

#अन्यथा /* CONFIG_B43LEGACY_DMA */


अटल अंतरभूत
पूर्णांक b43legacy_dma_init(काष्ठा b43legacy_wldev *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत
व्योम b43legacy_dma_मुक्त(काष्ठा b43legacy_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत
पूर्णांक b43legacy_dma_tx(काष्ठा b43legacy_wldev *dev,
		     काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत
व्योम b43legacy_dma_handle_txstatus(काष्ठा b43legacy_wldev *dev,
				   स्थिर काष्ठा b43legacy_txstatus *status)
अणु
पूर्ण
अटल अंतरभूत
व्योम b43legacy_dma_rx(काष्ठा b43legacy_dmaring *ring)
अणु
पूर्ण
अटल अंतरभूत
व्योम b43legacy_dma_tx_suspend(काष्ठा b43legacy_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत
व्योम b43legacy_dma_tx_resume(काष्ठा b43legacy_wldev *dev)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_B43LEGACY_DMA */
#पूर्ण_अगर /* B43legacy_DMA_H_ */
