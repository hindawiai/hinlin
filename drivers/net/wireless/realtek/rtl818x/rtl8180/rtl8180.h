<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित RTL8180_H
#घोषणा RTL8180_H

#समावेश "rtl818x.h"

#घोषणा MAX_RX_SIZE IEEE80211_MAX_RTS_THRESHOLD

#घोषणा RF_PARAM_ANALOGPHY	(1 << 0)
#घोषणा RF_PARAM_ANTBDEFAULT	(1 << 1)
#घोषणा RF_PARAM_CARRIERSENSE1	(1 << 2)
#घोषणा RF_PARAM_CARRIERSENSE2	(1 << 3)

#घोषणा BB_ANTATTEN_CHAN14	0x0C
#घोषणा BB_ANTENNA_B 		0x40

#घोषणा BB_HOST_BANG 		(1 << 30)
#घोषणा BB_HOST_BANG_EN 	(1 << 2)
#घोषणा BB_HOST_BANG_CLK 	(1 << 1)
#घोषणा BB_HOST_BANG_DATA	1

#घोषणा ANAPARAM_TXDACOFF_SHIFT	27
#घोषणा ANAPARAM_PWR0_SHIFT	28
#घोषणा ANAPARAM_PWR0_MASK 	(0x07 << ANAPARAM_PWR0_SHIFT)
#घोषणा ANAPARAM_PWR1_SHIFT	20
#घोषणा ANAPARAM_PWR1_MASK	(0x7F << ANAPARAM_PWR1_SHIFT)

/* rtl8180/rtl8185 have 3 queue + beacon queue.
 * mac80211 can use just one, + beacon = 2 tot.
 */
#घोषणा RTL8180_NR_TX_QUEUES 2

/* rtl8187SE have 6 queues + beacon queues
 * mac80211 can use 4 QoS data queue, + beacon = 5 tot
 */
#घोषणा RTL8187SE_NR_TX_QUEUES 5

/* क्रम array अटल allocation, it is the max of above */
#घोषणा RTL818X_NR_TX_QUEUES 5

काष्ठा rtl8180_tx_desc अणु
	__le32 flags;
	__le16 rts_duration;
	__le16 plcp_len;
	__le32 tx_buf;
	जोड़अणु
		__le32 frame_len;
		काष्ठा अणु
			__le16 frame_len_se;
			__le16 frame_duration;
		पूर्ण __packed;
	पूर्ण __packed;
	__le32 next_tx_desc;
	u8 cw;
	u8 retry_limit;
	u8 agc;
	u8 flags2;
	/* rsvd क्रम 8180/8185.
	 * valid क्रम 8187se but we करोnt use it
	 */
	u32 reserved;
	/* all rsvd क्रम 8180/8185 */
	__le16 flags3;
	__le16 frag_qsize;
पूर्ण __packed;

काष्ठा rtl818x_rx_cmd_desc अणु
	__le32 flags;
	u32 reserved;
	__le32 rx_buf;
पूर्ण __packed;

काष्ठा rtl8180_rx_desc अणु
	__le32 flags;
	__le32 flags2;
	__le64 tsft;

पूर्ण __packed;

काष्ठा rtl8187se_rx_desc अणु
	__le32 flags;
	__le64 tsft;
	__le32 flags2;
	__le32 flags3;
	u32 reserved[3];
पूर्ण __packed;

काष्ठा rtl8180_tx_ring अणु
	काष्ठा rtl8180_tx_desc *desc;
	dma_addr_t dma;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक entries;
	काष्ठा sk_buff_head queue;
पूर्ण;

काष्ठा rtl8180_vअगर अणु
	काष्ठा ieee80211_hw *dev;

	/* beaconing */
	काष्ठा delayed_work beacon_work;
	bool enable_beacon;
पूर्ण;

काष्ठा rtl8180_priv अणु
	/* common between rtl818x drivers */
	काष्ठा rtl818x_csr __iomem *map;
	स्थिर काष्ठा rtl818x_rf_ops *rf;
	काष्ठा ieee80211_vअगर *vअगर;

	/* rtl8180 driver specअगरic */
	bool map_pio;
	spinlock_t lock;
	व्योम *rx_ring;
	u8 rx_ring_sz;
	dma_addr_t rx_ring_dma;
	अचिन्हित पूर्णांक rx_idx;
	काष्ठा sk_buff *rx_buf[32];
	काष्ठा rtl8180_tx_ring tx_ring[RTL818X_NR_TX_QUEUES];
	काष्ठा ieee80211_channel channels[14];
	काष्ठा ieee80211_rate rates[12];
	काष्ठा ieee80211_supported_band band;
	काष्ठा ieee80211_tx_queue_params queue_param[4];
	काष्ठा pci_dev *pdev;
	u32 rx_conf;
	u8 slot_समय;
	u16 ack_समय;

	क्रमागत अणु
		RTL818X_CHIP_FAMILY_RTL8180,
		RTL818X_CHIP_FAMILY_RTL8185,
		RTL818X_CHIP_FAMILY_RTL8187SE,
	पूर्ण chip_family;
	u32 anaparam;
	u16 rfparam;
	u8 csthreshold;
	u8 mac_addr[ETH_ALEN];
	u8 rf_type;
	u8 xtal_out;
	u8 xtal_in;
	u8 xtal_cal;
	u8 thermal_meter_val;
	u8 thermal_meter_en;
	u8 antenna_भागersity_en;
	u8 antenna_भागersity_शेष;
	/* sequence # */
	u16 seqno;
पूर्ण;

व्योम rtl8180_ग_लिखो_phy(काष्ठा ieee80211_hw *dev, u8 addr, u32 data);
व्योम rtl8180_set_anaparam(काष्ठा rtl8180_priv *priv, u32 anaparam);
व्योम rtl8180_set_anaparam2(काष्ठा rtl8180_priv *priv, u32 anaparam2);

अटल अंतरभूत u8 rtl818x_ioपढ़ो8(काष्ठा rtl8180_priv *priv, स्थिर u8 __iomem *addr)
अणु
	वापस ioपढ़ो8(addr);
पूर्ण

अटल अंतरभूत u16 rtl818x_ioपढ़ो16(काष्ठा rtl8180_priv *priv, स्थिर __le16 __iomem *addr)
अणु
	वापस ioपढ़ो16(addr);
पूर्ण

अटल अंतरभूत u32 rtl818x_ioपढ़ो32(काष्ठा rtl8180_priv *priv, स्थिर __le32 __iomem *addr)
अणु
	वापस ioपढ़ो32(addr);
पूर्ण

अटल अंतरभूत व्योम rtl818x_ioग_लिखो8(काष्ठा rtl8180_priv *priv,
				    u8 __iomem *addr, u8 val)
अणु
	ioग_लिखो8(val, addr);
पूर्ण

अटल अंतरभूत व्योम rtl818x_ioग_लिखो16(काष्ठा rtl8180_priv *priv,
				     __le16 __iomem *addr, u16 val)
अणु
	ioग_लिखो16(val, addr);
पूर्ण

अटल अंतरभूत व्योम rtl818x_ioग_लिखो32(काष्ठा rtl8180_priv *priv,
				     __le32 __iomem *addr, u32 val)
अणु
	ioग_लिखो32(val, addr);
पूर्ण

#पूर्ण_अगर /* RTL8180_H */
