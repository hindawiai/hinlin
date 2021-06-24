<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Authors: Iyappan Subramanian <isubramanian@apm.com>
 *	    Ravi Patel <rapatel@apm.com>
 *	    Keyur Chudgar <kchudgar@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_MAIN_H__
#घोषणा __XGENE_ENET_MAIN_H__

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/efi.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/mdio/mdio-xgene.h>
#समावेश <linux/module.h>
#समावेश <net/ip.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/phy.h>
#समावेश "xgene_enet_hw.h"
#समावेश "xgene_enet_cle.h"
#समावेश "xgene_enet_ring2.h"

#घोषणा ETHER_MIN_PACKET	64
#घोषणा ETHER_STD_PACKET	1518
#घोषणा XGENE_ENET_STD_MTU	1536
#घोषणा XGENE_ENET_MAX_MTU	9600
#घोषणा SKB_BUFFER_SIZE		(XGENE_ENET_STD_MTU - NET_IP_ALIGN)

#घोषणा BUFLEN_16K	(16 * 1024)
#घोषणा NUM_PKT_BUF	1024
#घोषणा NUM_BUFPOOL	32
#घोषणा NUM_NXTBUFPOOL	8
#घोषणा MAX_EXP_BUFFS	256
#घोषणा NUM_MSS_REG	4
#घोषणा XGENE_MIN_ENET_FRAME_SIZE	60

#घोषणा XGENE_MAX_ENET_IRQ	16
#घोषणा XGENE_NUM_RX_RING	8
#घोषणा XGENE_NUM_TX_RING	8
#घोषणा XGENE_NUM_TXC_RING	8

#घोषणा START_CPU_BUFNUM_0	0
#घोषणा START_ETH_BUFNUM_0	2
#घोषणा START_BP_BUFNUM_0	0x22
#घोषणा START_RING_NUM_0	8
#घोषणा START_CPU_BUFNUM_1	12
#घोषणा START_ETH_BUFNUM_1	10
#घोषणा START_BP_BUFNUM_1	0x2A
#घोषणा START_RING_NUM_1	264

#घोषणा XG_START_CPU_BUFNUM_1	12
#घोषणा XG_START_ETH_BUFNUM_1	2
#घोषणा XG_START_BP_BUFNUM_1	0x22
#घोषणा XG_START_RING_NUM_1	264

#घोषणा X2_START_CPU_BUFNUM_0	0
#घोषणा X2_START_ETH_BUFNUM_0	0
#घोषणा X2_START_BP_BUFNUM_0	0x20
#घोषणा X2_START_RING_NUM_0	0
#घोषणा X2_START_CPU_BUFNUM_1	0xc
#घोषणा X2_START_ETH_BUFNUM_1	0
#घोषणा X2_START_BP_BUFNUM_1	0x20
#घोषणा X2_START_RING_NUM_1	256

#घोषणा IRQ_ID_SIZE		16

#घोषणा PHY_POLL_LINK_ON	(10 * HZ)
#घोषणा PHY_POLL_LINK_OFF	(PHY_POLL_LINK_ON / 5)

क्रमागत xgene_enet_id अणु
	XGENE_ENET1 = 1,
	XGENE_ENET2
पूर्ण;

क्रमागत xgene_enet_buf_len अणु
	SIZE_2K = 2048,
	SIZE_4K = 4096,
	SIZE_16K = 16384
पूर्ण;

/* software context of a descriptor ring */
काष्ठा xgene_enet_desc_ring अणु
	काष्ठा net_device *ndev;
	u16 id;
	u16 num;
	u16 head;
	u16 tail;
	u16 exp_buf_tail;
	u16 slots;
	u16 irq;
	अक्षर irq_name[IRQ_ID_SIZE];
	u32 size;
	u32 state[X2_NUM_RING_CONFIG];
	व्योम __iomem *cmd_base;
	व्योम __iomem *cmd;
	dma_addr_t dma;
	dma_addr_t irq_mbox_dma;
	व्योम *irq_mbox_addr;
	u16 dst_ring_num;
	u16 nbufpool;
	पूर्णांक npagepool;
	u8 index;
	u32 flags;
	काष्ठा sk_buff *(*rx_skb);
	काष्ठा sk_buff *(*cp_skb);
	dma_addr_t *frag_dma_addr;
	काष्ठा page *(*frag_page);
	क्रमागत xgene_enet_ring_cfgsize cfgsize;
	काष्ठा xgene_enet_desc_ring *cp_ring;
	काष्ठा xgene_enet_desc_ring *buf_pool;
	काष्ठा xgene_enet_desc_ring *page_pool;
	काष्ठा napi_काष्ठा napi;
	जोड़ अणु
		व्योम *desc_addr;
		काष्ठा xgene_enet_raw_desc *raw_desc;
		काष्ठा xgene_enet_raw_desc16 *raw_desc16;
	पूर्ण;
	__le64 *exp_bufs;
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_dropped;
	u64 tx_errors;
	u64 rx_packets;
	u64 rx_bytes;
	u64 rx_dropped;
	u64 rx_errors;
	u64 rx_length_errors;
	u64 rx_crc_errors;
	u64 rx_frame_errors;
	u64 rx_fअगरo_errors;
पूर्ण;

काष्ठा xgene_mac_ops अणु
	व्योम (*init)(काष्ठा xgene_enet_pdata *pdata);
	व्योम (*reset)(काष्ठा xgene_enet_pdata *pdata);
	व्योम (*tx_enable)(काष्ठा xgene_enet_pdata *pdata);
	व्योम (*rx_enable)(काष्ठा xgene_enet_pdata *pdata);
	व्योम (*tx_disable)(काष्ठा xgene_enet_pdata *pdata);
	व्योम (*rx_disable)(काष्ठा xgene_enet_pdata *pdata);
	व्योम (*get_drop_cnt)(काष्ठा xgene_enet_pdata *pdata, u32 *rx, u32 *tx);
	व्योम (*set_speed)(काष्ठा xgene_enet_pdata *pdata);
	व्योम (*set_mac_addr)(काष्ठा xgene_enet_pdata *pdata);
	व्योम (*set_framesize)(काष्ठा xgene_enet_pdata *pdata, पूर्णांक framesize);
	व्योम (*set_mss)(काष्ठा xgene_enet_pdata *pdata, u16 mss, u8 index);
	व्योम (*link_state)(काष्ठा work_काष्ठा *work);
	व्योम (*enable_tx_छोड़ो)(काष्ठा xgene_enet_pdata *pdata, bool enable);
	व्योम (*flowctl_rx)(काष्ठा xgene_enet_pdata *pdata, bool enable);
	व्योम (*flowctl_tx)(काष्ठा xgene_enet_pdata *pdata, bool enable);
पूर्ण;

काष्ठा xgene_port_ops अणु
	पूर्णांक (*reset)(काष्ठा xgene_enet_pdata *pdata);
	व्योम (*clear)(काष्ठा xgene_enet_pdata *pdata,
		      काष्ठा xgene_enet_desc_ring *ring);
	व्योम (*cle_bypass)(काष्ठा xgene_enet_pdata *pdata,
			   u32 dst_ring_num, u16 bufpool_id, u16 nxtbufpool_id);
	व्योम (*shutकरोwn)(काष्ठा xgene_enet_pdata *pdata);
पूर्ण;

काष्ठा xgene_ring_ops अणु
	u8 num_ring_config;
	u8 num_ring_id_shअगरt;
	काष्ठा xgene_enet_desc_ring * (*setup)(काष्ठा xgene_enet_desc_ring *);
	व्योम (*clear)(काष्ठा xgene_enet_desc_ring *);
	व्योम (*wr_cmd)(काष्ठा xgene_enet_desc_ring *, पूर्णांक);
	u32 (*len)(काष्ठा xgene_enet_desc_ring *);
	व्योम (*coalesce)(काष्ठा xgene_enet_desc_ring *);
पूर्ण;

काष्ठा xgene_cle_ops अणु
	पूर्णांक (*cle_init)(काष्ठा xgene_enet_pdata *pdata);
पूर्ण;

/* ethernet निजी data */
काष्ठा xgene_enet_pdata अणु
	काष्ठा net_device *ndev;
	काष्ठा mii_bus *mdio_bus;
	पूर्णांक phy_speed;
	काष्ठा clk *clk;
	काष्ठा platक्रमm_device *pdev;
	क्रमागत xgene_enet_id enet_id;
	काष्ठा xgene_enet_desc_ring *tx_ring[XGENE_NUM_TX_RING];
	काष्ठा xgene_enet_desc_ring *rx_ring[XGENE_NUM_RX_RING];
	u16 tx_level[XGENE_NUM_TX_RING];
	u16 txc_level[XGENE_NUM_TX_RING];
	अक्षर *dev_name;
	u32 rx_buff_cnt;
	u32 tx_qcnt_hi;
	u32 irqs[XGENE_MAX_ENET_IRQ];
	u8 rxq_cnt;
	u8 txq_cnt;
	u8 cq_cnt;
	व्योम __iomem *eth_csr_addr;
	व्योम __iomem *eth_ring_अगर_addr;
	व्योम __iomem *eth_diag_csr_addr;
	व्योम __iomem *mcx_mac_addr;
	व्योम __iomem *mcx_mac_csr_addr;
	व्योम __iomem *mcx_stats_addr;
	व्योम __iomem *base_addr;
	व्योम __iomem *pcs_addr;
	व्योम __iomem *ring_csr_addr;
	व्योम __iomem *ring_cmd_addr;
	पूर्णांक phy_mode;
	क्रमागत xgene_enet_rm rm;
	काष्ठा xgene_enet_cle cle;
	u64 *extd_stats;
	u64 false_rflr;
	u64 vlan_rjbr;
	spinlock_t stats_lock; /* statistics lock */
	स्थिर काष्ठा xgene_mac_ops *mac_ops;
	spinlock_t mac_lock; /* mac lock */
	स्थिर काष्ठा xgene_port_ops *port_ops;
	काष्ठा xgene_ring_ops *ring_ops;
	स्थिर काष्ठा xgene_cle_ops *cle_ops;
	काष्ठा delayed_work link_work;
	u32 port_id;
	u8 cpu_bufnum;
	u8 eth_bufnum;
	u8 bp_bufnum;
	u16 ring_num;
	u32 mss[NUM_MSS_REG];
	u32 mss_refcnt[NUM_MSS_REG];
	spinlock_t mss_lock;  /* mss lock */
	u8 tx_delay;
	u8 rx_delay;
	bool mdio_driver;
	काष्ठा gpio_desc *sfp_rdy;
	bool sfp_gpio_en;
	u32 छोड़ो_स्वतःneg;
	bool tx_छोड़ो;
	bool rx_छोड़ो;
पूर्ण;

काष्ठा xgene_indirect_ctl अणु
	व्योम __iomem *addr;
	व्योम __iomem *ctl;
	व्योम __iomem *cmd;
	व्योम __iomem *cmd_करोne;
पूर्ण;

अटल अंतरभूत काष्ठा device *ndev_to_dev(काष्ठा net_device *ndev)
अणु
	वापस ndev->dev.parent;
पूर्ण

अटल अंतरभूत u16 xgene_enet_dst_ring_num(काष्ठा xgene_enet_desc_ring *ring)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ring->ndev);

	वापस ((u16)pdata->rm << 10) | ring->num;
पूर्ण

व्योम xgene_enet_set_ethtool_ops(काष्ठा net_device *netdev);
पूर्णांक xgene_extd_stats_init(काष्ठा xgene_enet_pdata *pdata);

#पूर्ण_अगर /* __XGENE_ENET_MAIN_H__ */
