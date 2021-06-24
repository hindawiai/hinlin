<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTK_PCI_H_
#घोषणा __RTK_PCI_H_

#समावेश "main.h"

#घोषणा RTK_DEFAULT_TX_DESC_NUM 128
#घोषणा RTK_BEQ_TX_DESC_NUM	256

#घोषणा RTK_MAX_RX_DESC_NUM	512
/* 11K + rx desc size */
#घोषणा RTK_PCI_RX_BUF_SIZE	(11454 + 24)

#घोषणा RTK_PCI_CTRL		0x300
#घोषणा BIT_RST_TRXDMA_INTF	BIT(20)
#घोषणा BIT_RX_TAG_EN		BIT(15)
#घोषणा REG_DBI_WDATA_V1	0x03E8
#घोषणा REG_DBI_RDATA_V1	0x03EC
#घोषणा REG_DBI_FLAG_V1		0x03F0
#घोषणा BIT_DBI_RFLAG		BIT(17)
#घोषणा BIT_DBI_WFLAG		BIT(16)
#घोषणा BITS_DBI_WREN		GENMASK(15, 12)
#घोषणा BITS_DBI_ADDR_MASK	GENMASK(11, 2)

#घोषणा REG_MDIO_V1		0x03F4
#घोषणा REG_PCIE_MIX_CFG	0x03F8
#घोषणा BITS_MDIO_ADDR_MASK	GENMASK(4, 0)
#घोषणा BIT_MDIO_WFLAG_V1	BIT(5)
#घोषणा RTW_PCI_MDIO_PG_SZ	BIT(5)
#घोषणा RTW_PCI_MDIO_PG_OFFS_G1	0
#घोषणा RTW_PCI_MDIO_PG_OFFS_G2	2
#घोषणा RTW_PCI_WR_RETRY_CNT	20

#घोषणा RTK_PCIE_LINK_CFG	0x0719
#घोषणा BIT_CLKREQ_SW_EN	BIT(4)
#घोषणा BIT_L1_SW_EN		BIT(3)
#घोषणा RTK_PCIE_CLKDLY_CTRL	0x0725

#घोषणा BIT_PCI_BCNQ_FLAG	BIT(4)
#घोषणा RTK_PCI_TXBD_DESA_BCNQ	0x308
#घोषणा RTK_PCI_TXBD_DESA_H2CQ	0x1320
#घोषणा RTK_PCI_TXBD_DESA_MGMTQ	0x310
#घोषणा RTK_PCI_TXBD_DESA_BKQ	0x330
#घोषणा RTK_PCI_TXBD_DESA_BEQ	0x328
#घोषणा RTK_PCI_TXBD_DESA_VIQ	0x320
#घोषणा RTK_PCI_TXBD_DESA_VOQ	0x318
#घोषणा RTK_PCI_TXBD_DESA_HI0Q	0x340
#घोषणा RTK_PCI_RXBD_DESA_MPDUQ	0x338

#घोषणा TRX_BD_IDX_MASK		GENMASK(11, 0)
#घोषणा TRX_BD_HW_IDX_MASK	GENMASK(27, 16)

/* BCNQ is specialized क्रम rsvd page, करोes not need to specअगरy a number */
#घोषणा RTK_PCI_TXBD_NUM_H2CQ	0x1328
#घोषणा RTK_PCI_TXBD_NUM_MGMTQ	0x380
#घोषणा RTK_PCI_TXBD_NUM_BKQ	0x38A
#घोषणा RTK_PCI_TXBD_NUM_BEQ	0x388
#घोषणा RTK_PCI_TXBD_NUM_VIQ	0x386
#घोषणा RTK_PCI_TXBD_NUM_VOQ	0x384
#घोषणा RTK_PCI_TXBD_NUM_HI0Q	0x38C
#घोषणा RTK_PCI_RXBD_NUM_MPDUQ	0x382
#घोषणा RTK_PCI_TXBD_IDX_H2CQ	0x132C
#घोषणा RTK_PCI_TXBD_IDX_MGMTQ	0x3B0
#घोषणा RTK_PCI_TXBD_IDX_BKQ	0x3AC
#घोषणा RTK_PCI_TXBD_IDX_BEQ	0x3A8
#घोषणा RTK_PCI_TXBD_IDX_VIQ	0x3A4
#घोषणा RTK_PCI_TXBD_IDX_VOQ	0x3A0
#घोषणा RTK_PCI_TXBD_IDX_HI0Q	0x3B8
#घोषणा RTK_PCI_RXBD_IDX_MPDUQ	0x3B4

#घोषणा RTK_PCI_TXBD_RWPTR_CLR	0x39C
#घोषणा RTK_PCI_TXBD_H2CQ_CSR	0x1330

#घोषणा BIT_CLR_H2CQ_HOST_IDX	BIT(16)
#घोषणा BIT_CLR_H2CQ_HW_IDX	BIT(8)

#घोषणा RTK_PCI_HIMR0		0x0B0
#घोषणा RTK_PCI_HISR0		0x0B4
#घोषणा RTK_PCI_HIMR1		0x0B8
#घोषणा RTK_PCI_HISR1		0x0BC
#घोषणा RTK_PCI_HIMR2		0x10B0
#घोषणा RTK_PCI_HISR2		0x10B4
#घोषणा RTK_PCI_HIMR3		0x10B8
#घोषणा RTK_PCI_HISR3		0x10BC
/* IMR 0 */
#घोषणा IMR_TIMER2		BIT(31)
#घोषणा IMR_TIMER1		BIT(30)
#घोषणा IMR_PSTIMEOUT		BIT(29)
#घोषणा IMR_GTINT4		BIT(28)
#घोषणा IMR_GTINT3		BIT(27)
#घोषणा IMR_TBDER		BIT(26)
#घोषणा IMR_TBDOK		BIT(25)
#घोषणा IMR_TSF_BIT32_TOGGLE	BIT(24)
#घोषणा IMR_BCNDMAINT0		BIT(20)
#घोषणा IMR_BCNDOK0		BIT(16)
#घोषणा IMR_HSISR_IND_ON_INT	BIT(15)
#घोषणा IMR_BCNDMAINT_E		BIT(14)
#घोषणा IMR_ATIMEND		BIT(12)
#घोषणा IMR_HISR1_IND_INT	BIT(11)
#घोषणा IMR_C2HCMD		BIT(10)
#घोषणा IMR_CPWM2		BIT(9)
#घोषणा IMR_CPWM		BIT(8)
#घोषणा IMR_HIGHDOK		BIT(7)
#घोषणा IMR_MGNTDOK		BIT(6)
#घोषणा IMR_BKDOK		BIT(5)
#घोषणा IMR_BEDOK		BIT(4)
#घोषणा IMR_VIDOK		BIT(3)
#घोषणा IMR_VODOK		BIT(2)
#घोषणा IMR_RDU			BIT(1)
#घोषणा IMR_ROK			BIT(0)
/* IMR 1 */
#घोषणा IMR_TXFIFO_TH_INT	BIT(30)
#घोषणा IMR_BTON_STS_UPDATE	BIT(29)
#घोषणा IMR_MCUERR		BIT(28)
#घोषणा IMR_BCNDMAINT7		BIT(27)
#घोषणा IMR_BCNDMAINT6		BIT(26)
#घोषणा IMR_BCNDMAINT5		BIT(25)
#घोषणा IMR_BCNDMAINT4		BIT(24)
#घोषणा IMR_BCNDMAINT3		BIT(23)
#घोषणा IMR_BCNDMAINT2		BIT(22)
#घोषणा IMR_BCNDMAINT1		BIT(21)
#घोषणा IMR_BCNDOK7		BIT(20)
#घोषणा IMR_BCNDOK6		BIT(19)
#घोषणा IMR_BCNDOK5		BIT(18)
#घोषणा IMR_BCNDOK4		BIT(17)
#घोषणा IMR_BCNDOK3		BIT(16)
#घोषणा IMR_BCNDOK2		BIT(15)
#घोषणा IMR_BCNDOK1		BIT(14)
#घोषणा IMR_ATIMEND_E		BIT(13)
#घोषणा IMR_ATIMEND		BIT(12)
#घोषणा IMR_TXERR		BIT(11)
#घोषणा IMR_RXERR		BIT(10)
#घोषणा IMR_TXFOVW		BIT(9)
#घोषणा IMR_RXFOVW		BIT(8)
#घोषणा IMR_CPU_MGQ_TXDONE	BIT(5)
#घोषणा IMR_PS_TIMER_C		BIT(4)
#घोषणा IMR_PS_TIMER_B		BIT(3)
#घोषणा IMR_PS_TIMER_A		BIT(2)
#घोषणा IMR_CPUMGQ_TX_TIMER	BIT(1)
/* IMR 3 */
#घोषणा IMR_H2CDOK		BIT(16)

क्रमागत rtw_pci_flags अणु
	RTW_PCI_FLAG_NAPI_RUNNING,

	NUM_OF_RTW_PCI_FLAGS,
पूर्ण;

/* one element is reserved to know अगर the ring is बंदd */
अटल अंतरभूत पूर्णांक avail_desc(u32 wp, u32 rp, u32 len)
अणु
	अगर (rp > wp)
		वापस rp - wp - 1;
	अन्यथा
		वापस len - wp + rp - 1;
पूर्ण

#घोषणा RTK_PCI_TXBD_OWN_OFFSET 15
#घोषणा RTK_PCI_TXBD_BCN_WORK	0x383

काष्ठा rtw_pci_tx_buffer_desc अणु
	__le16 buf_size;
	__le16 psb_len;
	__le32 dma;
पूर्ण;

काष्ठा rtw_pci_tx_data अणु
	dma_addr_t dma;
	u8 sn;
पूर्ण;

काष्ठा rtw_pci_ring अणु
	u8 *head;
	dma_addr_t dma;

	u8 desc_size;

	u32 len;
	u32 wp;
	u32 rp;
पूर्ण;

काष्ठा rtw_pci_tx_ring अणु
	काष्ठा rtw_pci_ring r;
	काष्ठा sk_buff_head queue;
	bool queue_stopped;
पूर्ण;

काष्ठा rtw_pci_rx_buffer_desc अणु
	__le16 buf_size;
	__le16 total_pkt_size;
	__le32 dma;
पूर्ण;

काष्ठा rtw_pci_rx_ring अणु
	काष्ठा rtw_pci_ring r;
	काष्ठा sk_buff *buf[RTK_MAX_RX_DESC_NUM];
पूर्ण;

#घोषणा RX_TAG_MAX	8192

काष्ठा rtw_pci अणु
	काष्ठा pci_dev *pdev;

	/* Used क्रम PCI पूर्णांकerrupt. */
	spinlock_t hwirq_lock;
	/* Used क्रम PCI TX ring/queueing, and enable INT. */
	spinlock_t irq_lock;
	u32 irq_mask[4];
	bool irq_enabled;
	bool running;

	/* napi काष्ठाure */
	काष्ठा net_device netdev;
	काष्ठा napi_काष्ठा napi;

	u16 rx_tag;
	DECLARE_BITMAP(tx_queued, RTK_MAX_TX_QUEUE_NUM);
	काष्ठा rtw_pci_tx_ring tx_rings[RTK_MAX_TX_QUEUE_NUM];
	काष्ठा rtw_pci_rx_ring rx_rings[RTK_MAX_RX_QUEUE_NUM];
	u16 link_ctrl;
	DECLARE_BITMAP(flags, NUM_OF_RTW_PCI_FLAGS);

	व्योम __iomem *mmap;
पूर्ण;

बाह्य स्थिर काष्ठा dev_pm_ops rtw_pm_ops;

पूर्णांक rtw_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id);
व्योम rtw_pci_हटाओ(काष्ठा pci_dev *pdev);
व्योम rtw_pci_shutकरोwn(काष्ठा pci_dev *pdev);

अटल अंतरभूत u32 max_num_of_tx_queue(u8 queue)
अणु
	u32 max_num;

	चयन (queue) अणु
	हाल RTW_TX_QUEUE_BE:
		max_num = RTK_BEQ_TX_DESC_NUM;
		अवरोध;
	हाल RTW_TX_QUEUE_BCN:
		max_num = 1;
		अवरोध;
	शेष:
		max_num = RTK_DEFAULT_TX_DESC_NUM;
		अवरोध;
	पूर्ण

	वापस max_num;
पूर्ण

अटल अंतरभूत काष्ठा
rtw_pci_tx_data *rtw_pci_get_tx_data(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	BUILD_BUG_ON(माप(काष्ठा rtw_pci_tx_data) >
		     माप(info->status.status_driver_data));

	वापस (काष्ठा rtw_pci_tx_data *)info->status.status_driver_data;
पूर्ण

अटल अंतरभूत
काष्ठा rtw_pci_tx_buffer_desc *get_tx_buffer_desc(काष्ठा rtw_pci_tx_ring *ring,
						  u32 size)
अणु
	u8 *buf_desc;

	buf_desc = ring->r.head + ring->r.wp * size;
	वापस (काष्ठा rtw_pci_tx_buffer_desc *)buf_desc;
पूर्ण

#पूर्ण_अगर
