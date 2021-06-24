<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_ENET_H_
#घोषणा BCM63XX_ENET_H_

#समावेश <linux/types.h>
#समावेश <linux/mii.h>
#समावेश <linux/mutex.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_iudma.h>

/* शेष number of descriptor */
#घोषणा BCMENET_DEF_RX_DESC	64
#घोषणा BCMENET_DEF_TX_DESC	32

/* maximum burst len क्रम dma (4 bytes unit) */
#घोषणा BCMENET_DMA_MAXBURST	16
#घोषणा BCMENETSW_DMA_MAXBURST	8

/* tx transmit threshold (4 bytes unit), fअगरo is 256 bytes, the value
 * must be low enough so that a DMA transfer of above burst length can
 * not overflow the fअगरo  */
#घोषणा BCMENET_TX_FIFO_TRESH	32

/*
 * hardware maximum rx/tx packet size including FCS, max mtu is
 * actually 2047, but अगर we set max rx size रेजिस्टर to 2047 we won't
 * get overflow inक्रमmation अगर packet size is 2048 or above
 */
#घोषणा BCMENET_MAX_MTU		2046

/*
 * MIB Counters रेजिस्टर definitions
*/
#घोषणा ETH_MIB_TX_GD_OCTETS			0
#घोषणा ETH_MIB_TX_GD_PKTS			1
#घोषणा ETH_MIB_TX_ALL_OCTETS			2
#घोषणा ETH_MIB_TX_ALL_PKTS			3
#घोषणा ETH_MIB_TX_BRDCAST			4
#घोषणा ETH_MIB_TX_MULT				5
#घोषणा ETH_MIB_TX_64				6
#घोषणा ETH_MIB_TX_65_127			7
#घोषणा ETH_MIB_TX_128_255			8
#घोषणा ETH_MIB_TX_256_511			9
#घोषणा ETH_MIB_TX_512_1023			10
#घोषणा ETH_MIB_TX_1024_MAX			11
#घोषणा ETH_MIB_TX_JAB				12
#घोषणा ETH_MIB_TX_OVR				13
#घोषणा ETH_MIB_TX_FRAG				14
#घोषणा ETH_MIB_TX_UNDERRUN			15
#घोषणा ETH_MIB_TX_COL				16
#घोषणा ETH_MIB_TX_1_COL			17
#घोषणा ETH_MIB_TX_M_COL			18
#घोषणा ETH_MIB_TX_EX_COL			19
#घोषणा ETH_MIB_TX_LATE				20
#घोषणा ETH_MIB_TX_DEF				21
#घोषणा ETH_MIB_TX_CRS				22
#घोषणा ETH_MIB_TX_PAUSE			23

#घोषणा ETH_MIB_RX_GD_OCTETS			32
#घोषणा ETH_MIB_RX_GD_PKTS			33
#घोषणा ETH_MIB_RX_ALL_OCTETS			34
#घोषणा ETH_MIB_RX_ALL_PKTS			35
#घोषणा ETH_MIB_RX_BRDCAST			36
#घोषणा ETH_MIB_RX_MULT				37
#घोषणा ETH_MIB_RX_64				38
#घोषणा ETH_MIB_RX_65_127			39
#घोषणा ETH_MIB_RX_128_255			40
#घोषणा ETH_MIB_RX_256_511			41
#घोषणा ETH_MIB_RX_512_1023			42
#घोषणा ETH_MIB_RX_1024_MAX			43
#घोषणा ETH_MIB_RX_JAB				44
#घोषणा ETH_MIB_RX_OVR				45
#घोषणा ETH_MIB_RX_FRAG				46
#घोषणा ETH_MIB_RX_DROP				47
#घोषणा ETH_MIB_RX_CRC_ALIGN			48
#घोषणा ETH_MIB_RX_UND				49
#घोषणा ETH_MIB_RX_CRC				50
#घोषणा ETH_MIB_RX_ALIGN			51
#घोषणा ETH_MIB_RX_SYM				52
#घोषणा ETH_MIB_RX_PAUSE			53
#घोषणा ETH_MIB_RX_CNTRL			54


/*
 * SW MIB Counters रेजिस्टर definitions
*/
#घोषणा ETHSW_MIB_TX_ALL_OCT			0
#घोषणा ETHSW_MIB_TX_DROP_PKTS			2
#घोषणा ETHSW_MIB_TX_QOS_PKTS			3
#घोषणा ETHSW_MIB_TX_BRDCAST			4
#घोषणा ETHSW_MIB_TX_MULT			5
#घोषणा ETHSW_MIB_TX_UNI			6
#घोषणा ETHSW_MIB_TX_COL			7
#घोषणा ETHSW_MIB_TX_1_COL			8
#घोषणा ETHSW_MIB_TX_M_COL			9
#घोषणा ETHSW_MIB_TX_DEF			10
#घोषणा ETHSW_MIB_TX_LATE			11
#घोषणा ETHSW_MIB_TX_EX_COL			12
#घोषणा ETHSW_MIB_TX_PAUSE			14
#घोषणा ETHSW_MIB_TX_QOS_OCT			15

#घोषणा ETHSW_MIB_RX_ALL_OCT			17
#घोषणा ETHSW_MIB_RX_UND			19
#घोषणा ETHSW_MIB_RX_PAUSE			20
#घोषणा ETHSW_MIB_RX_64				21
#घोषणा ETHSW_MIB_RX_65_127			22
#घोषणा ETHSW_MIB_RX_128_255			23
#घोषणा ETHSW_MIB_RX_256_511			24
#घोषणा ETHSW_MIB_RX_512_1023			25
#घोषणा ETHSW_MIB_RX_1024_1522			26
#घोषणा ETHSW_MIB_RX_OVR			27
#घोषणा ETHSW_MIB_RX_JAB			28
#घोषणा ETHSW_MIB_RX_ALIGN			29
#घोषणा ETHSW_MIB_RX_CRC			30
#घोषणा ETHSW_MIB_RX_GD_OCT			31
#घोषणा ETHSW_MIB_RX_DROP			33
#घोषणा ETHSW_MIB_RX_UNI			34
#घोषणा ETHSW_MIB_RX_MULT			35
#घोषणा ETHSW_MIB_RX_BRDCAST			36
#घोषणा ETHSW_MIB_RX_SA_CHANGE			37
#घोषणा ETHSW_MIB_RX_FRAG			38
#घोषणा ETHSW_MIB_RX_OVR_DISC			39
#घोषणा ETHSW_MIB_RX_SYM			40
#घोषणा ETHSW_MIB_RX_QOS_PKTS			41
#घोषणा ETHSW_MIB_RX_QOS_OCT			42
#घोषणा ETHSW_MIB_RX_1523_2047			44
#घोषणा ETHSW_MIB_RX_2048_4095			45
#घोषणा ETHSW_MIB_RX_4096_8191			46
#घोषणा ETHSW_MIB_RX_8192_9728			47


काष्ठा bcm_enet_mib_counters अणु
	u64 tx_gd_octets;
	u32 tx_gd_pkts;
	u32 tx_all_octets;
	u32 tx_all_pkts;
	u32 tx_unicast;
	u32 tx_brdcast;
	u32 tx_mult;
	u32 tx_64;
	u32 tx_65_127;
	u32 tx_128_255;
	u32 tx_256_511;
	u32 tx_512_1023;
	u32 tx_1024_max;
	u32 tx_1523_2047;
	u32 tx_2048_4095;
	u32 tx_4096_8191;
	u32 tx_8192_9728;
	u32 tx_jab;
	u32 tx_drop;
	u32 tx_ovr;
	u32 tx_frag;
	u32 tx_underrun;
	u32 tx_col;
	u32 tx_1_col;
	u32 tx_m_col;
	u32 tx_ex_col;
	u32 tx_late;
	u32 tx_def;
	u32 tx_crs;
	u32 tx_छोड़ो;
	u64 rx_gd_octets;
	u32 rx_gd_pkts;
	u32 rx_all_octets;
	u32 rx_all_pkts;
	u32 rx_brdcast;
	u32 rx_unicast;
	u32 rx_mult;
	u32 rx_64;
	u32 rx_65_127;
	u32 rx_128_255;
	u32 rx_256_511;
	u32 rx_512_1023;
	u32 rx_1024_max;
	u32 rx_jab;
	u32 rx_ovr;
	u32 rx_frag;
	u32 rx_drop;
	u32 rx_crc_align;
	u32 rx_und;
	u32 rx_crc;
	u32 rx_align;
	u32 rx_sym;
	u32 rx_छोड़ो;
	u32 rx_cntrl;
पूर्ण;


काष्ठा bcm_enet_priv अणु

	/* base remapped address of device */
	व्योम __iomem *base;

	/* mac irq, rx_dma irq, tx_dma irq */
	पूर्णांक irq;
	पूर्णांक irq_rx;
	पूर्णांक irq_tx;

	/* hw view of rx & tx dma ring */
	dma_addr_t rx_desc_dma;
	dma_addr_t tx_desc_dma;

	/* allocated size (in bytes) क्रम rx & tx dma ring */
	अचिन्हित पूर्णांक rx_desc_alloc_size;
	अचिन्हित पूर्णांक tx_desc_alloc_size;


	काष्ठा napi_काष्ठा napi;

	/* dma channel id क्रम rx */
	पूर्णांक rx_chan;

	/* number of dma desc in rx ring */
	पूर्णांक rx_ring_size;

	/* cpu view of rx dma ring */
	काष्ठा bcm_enet_desc *rx_desc_cpu;

	/* current number of armed descriptor given to hardware क्रम rx */
	पूर्णांक rx_desc_count;

	/* next rx descriptor to fetch from hardware */
	पूर्णांक rx_curr_desc;

	/* next dirty rx descriptor to refill */
	पूर्णांक rx_dirty_desc;

	/* size of allocated rx buffers */
	अचिन्हित पूर्णांक rx_buf_size;

	/* allocated rx buffer offset */
	अचिन्हित पूर्णांक rx_buf_offset;

	/* size of allocated rx frag */
	अचिन्हित पूर्णांक rx_frag_size;

	/* list of buffer given to hw क्रम rx */
	व्योम **rx_buf;

	/* used when rx skb allocation failed, so we defer rx queue
	 * refill */
	काष्ठा समयr_list rx_समयout;

	/* lock rx_समयout against rx normal operation */
	spinlock_t rx_lock;


	/* dma channel id क्रम tx */
	पूर्णांक tx_chan;

	/* number of dma desc in tx ring */
	पूर्णांक tx_ring_size;

	/* maximum dma burst size */
	पूर्णांक dma_maxburst;

	/* cpu view of rx dma ring */
	काष्ठा bcm_enet_desc *tx_desc_cpu;

	/* number of available descriptor क्रम tx */
	पूर्णांक tx_desc_count;

	/* next tx descriptor avaiable */
	पूर्णांक tx_curr_desc;

	/* next dirty tx descriptor to reclaim */
	पूर्णांक tx_dirty_desc;

	/* list of skb given to hw क्रम tx */
	काष्ठा sk_buff **tx_skb;

	/* lock used by tx reclaim and xmit */
	spinlock_t tx_lock;


	/* set अगर पूर्णांकernal phy is ignored and बाह्यal mii पूर्णांकerface
	 * is selected */
	पूर्णांक use_बाह्यal_mii;

	/* set अगर a phy is connected, phy address must be known,
	 * probing is not possible */
	पूर्णांक has_phy;
	पूर्णांक phy_id;

	/* set अगर connected phy has an associated irq */
	पूर्णांक has_phy_पूर्णांकerrupt;
	पूर्णांक phy_पूर्णांकerrupt;

	/* used when a phy is connected (phylib used) */
	काष्ठा mii_bus *mii_bus;
	पूर्णांक old_link;
	पूर्णांक old_duplex;
	पूर्णांक old_छोड़ो;

	/* used when no phy is connected */
	पूर्णांक क्रमce_speed_100;
	पूर्णांक क्रमce_duplex_full;

	/* छोड़ो parameters */
	पूर्णांक छोड़ो_स्वतः;
	पूर्णांक छोड़ो_rx;
	पूर्णांक छोड़ो_tx;

	/* stats */
	काष्ठा bcm_enet_mib_counters mib;

	/* after mib पूर्णांकerrupt, mib रेजिस्टरs update is करोne in this
	 * work queue */
	काष्ठा work_काष्ठा mib_update_task;

	/* lock mib update between userspace request and workqueue */
	काष्ठा mutex mib_update_lock;

	/* mac घड़ी */
	काष्ठा clk *mac_clk;

	/* phy घड़ी अगर पूर्णांकernal phy is used */
	काष्ठा clk *phy_clk;

	/* network device reference */
	काष्ठा net_device *net_dev;

	/* platक्रमm device reference */
	काष्ठा platक्रमm_device *pdev;

	/* maximum hardware transmit/receive size */
	अचिन्हित पूर्णांक hw_mtu;

	bool enet_is_sw;

	/* port mapping क्रम चयन devices */
	पूर्णांक num_ports;
	काष्ठा bcm63xx_enetsw_port used_ports[ENETSW_MAX_PORT];
	पूर्णांक sw_port_link[ENETSW_MAX_PORT];

	/* used to poll चयन port state */
	काष्ठा समयr_list swphy_poll;
	spinlock_t enetsw_mdio_lock;

	/* dma channel enable mask */
	u32 dma_chan_en_mask;

	/* dma channel पूर्णांकerrupt mask */
	u32 dma_chan_पूर्णांक_mask;

	/* DMA engine has पूर्णांकernal SRAM */
	bool dma_has_sram;

	/* dma channel width */
	अचिन्हित पूर्णांक dma_chan_width;

	/* dma descriptor shअगरt value */
	अचिन्हित पूर्णांक dma_desc_shअगरt;
पूर्ण;


#पूर्ण_अगर /* ! BCM63XX_ENET_H_ */
