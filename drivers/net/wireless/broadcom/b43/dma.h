<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_DMA_H_
#घोषणा B43_DMA_H_

#समावेश <linux/err.h>

#समावेश "b43.h"


/* DMA-Interrupt reasons. */
#घोषणा B43_DMAIRQ_FATALMASK	((1 << 10) | (1 << 11) | (1 << 12) \
					 | (1 << 14) | (1 << 15))
#घोषणा B43_DMAIRQ_RDESC_UFLOW		(1 << 13)
#घोषणा B43_DMAIRQ_RX_DONE		(1 << 16)

/*** 32-bit DMA Engine. ***/

/* 32-bit DMA controller रेजिस्टरs. */
#घोषणा B43_DMA32_TXCTL				0x00
#घोषणा		B43_DMA32_TXENABLE			0x00000001
#घोषणा		B43_DMA32_TXSUSPEND			0x00000002
#घोषणा		B43_DMA32_TXLOOPBACK		0x00000004
#घोषणा		B43_DMA32_TXFLUSH			0x00000010
#घोषणा		B43_DMA32_TXPARITYDISABLE		0x00000800
#घोषणा		B43_DMA32_TXADDREXT_MASK		0x00030000
#घोषणा		B43_DMA32_TXADDREXT_SHIFT		16
#घोषणा B43_DMA32_TXRING				0x04
#घोषणा B43_DMA32_TXINDEX				0x08
#घोषणा B43_DMA32_TXSTATUS				0x0C
#घोषणा		B43_DMA32_TXDPTR			0x00000FFF
#घोषणा		B43_DMA32_TXSTATE			0x0000F000
#घोषणा			B43_DMA32_TXSTAT_DISABLED	0x00000000
#घोषणा			B43_DMA32_TXSTAT_ACTIVE	0x00001000
#घोषणा			B43_DMA32_TXSTAT_IDLEWAIT	0x00002000
#घोषणा			B43_DMA32_TXSTAT_STOPPED	0x00003000
#घोषणा			B43_DMA32_TXSTAT_SUSP	0x00004000
#घोषणा		B43_DMA32_TXERROR			0x000F0000
#घोषणा			B43_DMA32_TXERR_NOERR	0x00000000
#घोषणा			B43_DMA32_TXERR_PROT	0x00010000
#घोषणा			B43_DMA32_TXERR_UNDERRUN	0x00020000
#घोषणा			B43_DMA32_TXERR_BUFREAD	0x00030000
#घोषणा			B43_DMA32_TXERR_DESCREAD	0x00040000
#घोषणा		B43_DMA32_TXACTIVE			0xFFF00000
#घोषणा B43_DMA32_RXCTL				0x10
#घोषणा		B43_DMA32_RXENABLE			0x00000001
#घोषणा		B43_DMA32_RXFROFF_MASK		0x000000FE
#घोषणा		B43_DMA32_RXFROFF_SHIFT		1
#घोषणा		B43_DMA32_RXसूचीECTFIFO		0x00000100
#घोषणा		B43_DMA32_RXPARITYDISABLE		0x00000800
#घोषणा		B43_DMA32_RXADDREXT_MASK		0x00030000
#घोषणा		B43_DMA32_RXADDREXT_SHIFT		16
#घोषणा B43_DMA32_RXRING				0x14
#घोषणा B43_DMA32_RXINDEX				0x18
#घोषणा B43_DMA32_RXSTATUS				0x1C
#घोषणा		B43_DMA32_RXDPTR			0x00000FFF
#घोषणा		B43_DMA32_RXSTATE			0x0000F000
#घोषणा			B43_DMA32_RXSTAT_DISABLED	0x00000000
#घोषणा			B43_DMA32_RXSTAT_ACTIVE	0x00001000
#घोषणा			B43_DMA32_RXSTAT_IDLEWAIT	0x00002000
#घोषणा			B43_DMA32_RXSTAT_STOPPED	0x00003000
#घोषणा		B43_DMA32_RXERROR			0x000F0000
#घोषणा			B43_DMA32_RXERR_NOERR	0x00000000
#घोषणा			B43_DMA32_RXERR_PROT	0x00010000
#घोषणा			B43_DMA32_RXERR_OVERFLOW	0x00020000
#घोषणा			B43_DMA32_RXERR_BUFWRITE	0x00030000
#घोषणा			B43_DMA32_RXERR_DESCREAD	0x00040000
#घोषणा		B43_DMA32_RXACTIVE			0xFFF00000

/* 32-bit DMA descriptor. */
काष्ठा b43_dmadesc32 अणु
	__le32 control;
	__le32 address;
पूर्ण __packed;
#घोषणा B43_DMA32_DCTL_BYTECNT		0x00001FFF
#घोषणा B43_DMA32_DCTL_ADDREXT_MASK		0x00030000
#घोषणा B43_DMA32_DCTL_ADDREXT_SHIFT	16
#घोषणा B43_DMA32_DCTL_DTABLEEND		0x10000000
#घोषणा B43_DMA32_DCTL_IRQ			0x20000000
#घोषणा B43_DMA32_DCTL_FRAMEEND		0x40000000
#घोषणा B43_DMA32_DCTL_FRAMESTART		0x80000000

/*** 64-bit DMA Engine. ***/

/* 64-bit DMA controller रेजिस्टरs. */
#घोषणा B43_DMA64_TXCTL				0x00
#घोषणा		B43_DMA64_TXENABLE			0x00000001
#घोषणा		B43_DMA64_TXSUSPEND			0x00000002
#घोषणा		B43_DMA64_TXLOOPBACK		0x00000004
#घोषणा		B43_DMA64_TXFLUSH			0x00000010
#घोषणा		B43_DMA64_TXPARITYDISABLE		0x00000800
#घोषणा		B43_DMA64_TXADDREXT_MASK		0x00030000
#घोषणा		B43_DMA64_TXADDREXT_SHIFT		16
#घोषणा B43_DMA64_TXINDEX				0x04
#घोषणा B43_DMA64_TXRINGLO				0x08
#घोषणा B43_DMA64_TXRINGHI				0x0C
#घोषणा B43_DMA64_TXSTATUS				0x10
#घोषणा		B43_DMA64_TXSTATDPTR		0x00001FFF
#घोषणा		B43_DMA64_TXSTAT			0xF0000000
#घोषणा			B43_DMA64_TXSTAT_DISABLED	0x00000000
#घोषणा			B43_DMA64_TXSTAT_ACTIVE	0x10000000
#घोषणा			B43_DMA64_TXSTAT_IDLEWAIT	0x20000000
#घोषणा			B43_DMA64_TXSTAT_STOPPED	0x30000000
#घोषणा			B43_DMA64_TXSTAT_SUSP	0x40000000
#घोषणा B43_DMA64_TXERROR				0x14
#घोषणा		B43_DMA64_TXERRDPTR			0x0001FFFF
#घोषणा		B43_DMA64_TXERR			0xF0000000
#घोषणा			B43_DMA64_TXERR_NOERR	0x00000000
#घोषणा			B43_DMA64_TXERR_PROT	0x10000000
#घोषणा			B43_DMA64_TXERR_UNDERRUN	0x20000000
#घोषणा			B43_DMA64_TXERR_TRANSFER	0x30000000
#घोषणा			B43_DMA64_TXERR_DESCREAD	0x40000000
#घोषणा			B43_DMA64_TXERR_CORE	0x50000000
#घोषणा B43_DMA64_RXCTL				0x20
#घोषणा		B43_DMA64_RXENABLE			0x00000001
#घोषणा		B43_DMA64_RXFROFF_MASK		0x000000FE
#घोषणा		B43_DMA64_RXFROFF_SHIFT		1
#घोषणा		B43_DMA64_RXसूचीECTFIFO		0x00000100
#घोषणा		B43_DMA64_RXPARITYDISABLE		0x00000800
#घोषणा		B43_DMA64_RXADDREXT_MASK		0x00030000
#घोषणा		B43_DMA64_RXADDREXT_SHIFT		16
#घोषणा B43_DMA64_RXINDEX				0x24
#घोषणा B43_DMA64_RXRINGLO				0x28
#घोषणा B43_DMA64_RXRINGHI				0x2C
#घोषणा B43_DMA64_RXSTATUS				0x30
#घोषणा		B43_DMA64_RXSTATDPTR		0x00001FFF
#घोषणा		B43_DMA64_RXSTAT			0xF0000000
#घोषणा			B43_DMA64_RXSTAT_DISABLED	0x00000000
#घोषणा			B43_DMA64_RXSTAT_ACTIVE	0x10000000
#घोषणा			B43_DMA64_RXSTAT_IDLEWAIT	0x20000000
#घोषणा			B43_DMA64_RXSTAT_STOPPED	0x30000000
#घोषणा			B43_DMA64_RXSTAT_SUSP	0x40000000
#घोषणा B43_DMA64_RXERROR				0x34
#घोषणा		B43_DMA64_RXERRDPTR			0x0001FFFF
#घोषणा		B43_DMA64_RXERR			0xF0000000
#घोषणा			B43_DMA64_RXERR_NOERR	0x00000000
#घोषणा			B43_DMA64_RXERR_PROT	0x10000000
#घोषणा			B43_DMA64_RXERR_UNDERRUN	0x20000000
#घोषणा			B43_DMA64_RXERR_TRANSFER	0x30000000
#घोषणा			B43_DMA64_RXERR_DESCREAD	0x40000000
#घोषणा			B43_DMA64_RXERR_CORE	0x50000000

/* 64-bit DMA descriptor. */
काष्ठा b43_dmadesc64 अणु
	__le32 control0;
	__le32 control1;
	__le32 address_low;
	__le32 address_high;
पूर्ण __packed;
#घोषणा B43_DMA64_DCTL0_DTABLEEND		0x10000000
#घोषणा B43_DMA64_DCTL0_IRQ			0x20000000
#घोषणा B43_DMA64_DCTL0_FRAMEEND		0x40000000
#घोषणा B43_DMA64_DCTL0_FRAMESTART		0x80000000
#घोषणा B43_DMA64_DCTL1_BYTECNT		0x00001FFF
#घोषणा B43_DMA64_DCTL1_ADDREXT_MASK	0x00030000
#घोषणा B43_DMA64_DCTL1_ADDREXT_SHIFT	16

काष्ठा b43_dmadesc_generic अणु
	जोड़ अणु
		काष्ठा b43_dmadesc32 dma32;
		काष्ठा b43_dmadesc64 dma64;
	पूर्ण __packed;
पूर्ण __packed;

/* Misc DMA स्थिरants */
#घोषणा B43_DMA32_RINGMEMSIZE		4096
#घोषणा B43_DMA64_RINGMEMSIZE		8192
/* Offset of frame with actual data */
#घोषणा B43_DMA0_RX_FW598_FO		38
#घोषणा B43_DMA0_RX_FW351_FO		30

/* DMA engine tuning knobs */
#घोषणा B43_TXRING_SLOTS		256
#घोषणा B43_RXRING_SLOTS		256
#घोषणा B43_DMA0_RX_FW598_बफ_मानE	(B43_DMA0_RX_FW598_FO + IEEE80211_MAX_FRAME_LEN)
#घोषणा B43_DMA0_RX_FW351_बफ_मानE	(B43_DMA0_RX_FW351_FO + IEEE80211_MAX_FRAME_LEN)

/* Poपूर्णांकer poison */
#घोषणा B43_DMA_PTR_POISON		((व्योम *)ERR_PTR(-ENOMEM))
#घोषणा b43_dma_ptr_is_poisoned(ptr)	(unlikely((ptr) == B43_DMA_PTR_POISON))


काष्ठा sk_buff;
काष्ठा b43_निजी;
काष्ठा b43_txstatus;

काष्ठा b43_dmadesc_meta अणु
	/* The kernel DMA-able buffer. */
	काष्ठा sk_buff *skb;
	/* DMA base bus-address of the descriptor buffer. */
	dma_addr_t dmaaddr;
	/* ieee80211 TX status. Only used once per 802.11 frag. */
	bool is_last_fragment;
पूर्ण;

काष्ठा b43_dmaring;

/* Lowlevel DMA operations that dअगरfer between 32bit and 64bit DMA. */
काष्ठा b43_dma_ops अणु
	काष्ठा b43_dmadesc_generic *(*idx2desc) (काष्ठा b43_dmaring * ring,
						 पूर्णांक slot,
						 काष्ठा b43_dmadesc_meta **
						 meta);
	व्योम (*fill_descriptor) (काष्ठा b43_dmaring * ring,
				 काष्ठा b43_dmadesc_generic * desc,
				 dma_addr_t dmaaddr, u16 bufsize, पूर्णांक start,
				 पूर्णांक end, पूर्णांक irq);
	व्योम (*poke_tx) (काष्ठा b43_dmaring * ring, पूर्णांक slot);
	व्योम (*tx_suspend) (काष्ठा b43_dmaring * ring);
	व्योम (*tx_resume) (काष्ठा b43_dmaring * ring);
	पूर्णांक (*get_current_rxslot) (काष्ठा b43_dmaring * ring);
	व्योम (*set_current_rxslot) (काष्ठा b43_dmaring * ring, पूर्णांक slot);
पूर्ण;

क्रमागत b43_dmatype अणु
	B43_DMA_30BIT	= 30,
	B43_DMA_32BIT	= 32,
	B43_DMA_64BIT	= 64,
पूर्ण;

क्रमागत b43_addrtype अणु
	B43_DMA_ADDR_LOW,
	B43_DMA_ADDR_HIGH,
	B43_DMA_ADDR_EXT,
पूर्ण;

काष्ठा b43_dmaring अणु
	/* Lowlevel DMA ops. */
	स्थिर काष्ठा b43_dma_ops *ops;
	/* Kernel भव base address of the ring memory. */
	व्योम *descbase;
	/* Meta data about all descriptors. */
	काष्ठा b43_dmadesc_meta *meta;
	/* Cache of TX headers क्रम each TX frame.
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
	क्रमागत b43_dmatype type;
	/* Boolean. Is this ring stopped at ieee80211 level? */
	bool stopped;
	/* The QOS priority asचिन्हित to this ring. Only used क्रम TX rings.
	 * This is the mac80211 "queue" value. */
	u8 queue_prio;
	काष्ठा b43_wldev *dev;
#अगर_घोषित CONFIG_B43_DEBUG
	/* Maximum number of used slots. */
	पूर्णांक max_used_slots;
	/* Last समय we injected a ring overflow. */
	अचिन्हित दीर्घ last_injected_overflow;
	/* Statistics: Number of successfully transmitted packets */
	u64 nr_succeed_tx_packets;
	/* Statistics: Number of failed TX packets */
	u64 nr_failed_tx_packets;
	/* Statistics: Total number of TX plus all retries. */
	u64 nr_total_packet_tries;
#पूर्ण_अगर /* CONFIG_B43_DEBUG */
पूर्ण;

अटल अंतरभूत u32 b43_dma_पढ़ो(काष्ठा b43_dmaring *ring, u16 offset)
अणु
	वापस b43_पढ़ो32(ring->dev, ring->mmio_base + offset);
पूर्ण

अटल अंतरभूत व्योम b43_dma_ग_लिखो(काष्ठा b43_dmaring *ring, u16 offset, u32 value)
अणु
	b43_ग_लिखो32(ring->dev, ring->mmio_base + offset, value);
पूर्ण

पूर्णांक b43_dma_init(काष्ठा b43_wldev *dev);
व्योम b43_dma_मुक्त(काष्ठा b43_wldev *dev);

व्योम b43_dma_tx_suspend(काष्ठा b43_wldev *dev);
व्योम b43_dma_tx_resume(काष्ठा b43_wldev *dev);

पूर्णांक b43_dma_tx(काष्ठा b43_wldev *dev,
	       काष्ठा sk_buff *skb);
व्योम b43_dma_handle_txstatus(काष्ठा b43_wldev *dev,
			     स्थिर काष्ठा b43_txstatus *status);

व्योम b43_dma_handle_rx_overflow(काष्ठा b43_dmaring *ring);

व्योम b43_dma_rx(काष्ठा b43_dmaring *ring);

व्योम b43_dma_direct_fअगरo_rx(काष्ठा b43_wldev *dev,
			    अचिन्हित पूर्णांक engine_index, bool enable);

#पूर्ण_अगर /* B43_DMA_H_ */
