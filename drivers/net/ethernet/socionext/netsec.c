<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/types.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/acpi.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/netlink.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>

#समावेश <net/tcp.h>
#समावेश <net/page_pool.h>
#समावेश <net/ip6_checksum.h>

#घोषणा NETSEC_REG_SOFT_RST			0x104
#घोषणा NETSEC_REG_COM_INIT			0x120

#घोषणा NETSEC_REG_TOP_STATUS			0x200
#घोषणा NETSEC_IRQ_RX				BIT(1)
#घोषणा NETSEC_IRQ_TX				BIT(0)

#घोषणा NETSEC_REG_TOP_INTEN			0x204
#घोषणा NETSEC_REG_INTEN_SET			0x234
#घोषणा NETSEC_REG_INTEN_CLR			0x238

#घोषणा NETSEC_REG_NRM_TX_STATUS		0x400
#घोषणा NETSEC_REG_NRM_TX_INTEN			0x404
#घोषणा NETSEC_REG_NRM_TX_INTEN_SET		0x428
#घोषणा NETSEC_REG_NRM_TX_INTEN_CLR		0x42c
#घोषणा NRM_TX_ST_NTOWNR	BIT(17)
#घोषणा NRM_TX_ST_TR_ERR	BIT(16)
#घोषणा NRM_TX_ST_TXDONE	BIT(15)
#घोषणा NRM_TX_ST_TMREXP	BIT(14)

#घोषणा NETSEC_REG_NRM_RX_STATUS		0x440
#घोषणा NETSEC_REG_NRM_RX_INTEN			0x444
#घोषणा NETSEC_REG_NRM_RX_INTEN_SET		0x468
#घोषणा NETSEC_REG_NRM_RX_INTEN_CLR		0x46c
#घोषणा NRM_RX_ST_RC_ERR	BIT(16)
#घोषणा NRM_RX_ST_PKTCNT	BIT(15)
#घोषणा NRM_RX_ST_TMREXP	BIT(14)

#घोषणा NETSEC_REG_PKT_CMD_BUF			0xd0

#घोषणा NETSEC_REG_CLK_EN			0x100

#घोषणा NETSEC_REG_PKT_CTRL			0x140

#घोषणा NETSEC_REG_DMA_TMR_CTRL			0x20c
#घोषणा NETSEC_REG_F_TAIKI_MC_VER		0x22c
#घोषणा NETSEC_REG_F_TAIKI_VER			0x230
#घोषणा NETSEC_REG_DMA_HM_CTRL			0x214
#घोषणा NETSEC_REG_DMA_MH_CTRL			0x220
#घोषणा NETSEC_REG_ADDR_DIS_CORE		0x218
#घोषणा NETSEC_REG_DMAC_HM_CMD_BUF		0x210
#घोषणा NETSEC_REG_DMAC_MH_CMD_BUF		0x21c

#घोषणा NETSEC_REG_NRM_TX_PKTCNT		0x410

#घोषणा NETSEC_REG_NRM_TX_DONE_PKTCNT		0x414
#घोषणा NETSEC_REG_NRM_TX_DONE_TXINT_PKTCNT	0x418

#घोषणा NETSEC_REG_NRM_TX_TMR			0x41c

#घोषणा NETSEC_REG_NRM_RX_PKTCNT		0x454
#घोषणा NETSEC_REG_NRM_RX_RXINT_PKTCNT		0x458
#घोषणा NETSEC_REG_NRM_TX_TXINT_TMR		0x420
#घोषणा NETSEC_REG_NRM_RX_RXINT_TMR		0x460

#घोषणा NETSEC_REG_NRM_RX_TMR			0x45c

#घोषणा NETSEC_REG_NRM_TX_DESC_START_UP		0x434
#घोषणा NETSEC_REG_NRM_TX_DESC_START_LW		0x408
#घोषणा NETSEC_REG_NRM_RX_DESC_START_UP		0x474
#घोषणा NETSEC_REG_NRM_RX_DESC_START_LW		0x448

#घोषणा NETSEC_REG_NRM_TX_CONFIG		0x430
#घोषणा NETSEC_REG_NRM_RX_CONFIG		0x470

#घोषणा MAC_REG_STATUS				0x1024
#घोषणा MAC_REG_DATA				0x11c0
#घोषणा MAC_REG_CMD				0x11c4
#घोषणा MAC_REG_FLOW_TH				0x11cc
#घोषणा MAC_REG_INTF_SEL			0x11d4
#घोषणा MAC_REG_DESC_INIT			0x11fc
#घोषणा MAC_REG_DESC_SOFT_RST			0x1204
#घोषणा NETSEC_REG_MODE_TRANS_COMP_STATUS	0x500

#घोषणा GMAC_REG_MCR				0x0000
#घोषणा GMAC_REG_MFFR				0x0004
#घोषणा GMAC_REG_GAR				0x0010
#घोषणा GMAC_REG_GDR				0x0014
#घोषणा GMAC_REG_FCR				0x0018
#घोषणा GMAC_REG_BMR				0x1000
#घोषणा GMAC_REG_RDLAR				0x100c
#घोषणा GMAC_REG_TDLAR				0x1010
#घोषणा GMAC_REG_OMR				0x1018

#घोषणा MHZ(n)		((n) * 1000 * 1000)

#घोषणा NETSEC_TX_SHIFT_OWN_FIELD		31
#घोषणा NETSEC_TX_SHIFT_LD_FIELD		30
#घोषणा NETSEC_TX_SHIFT_DRID_FIELD		24
#घोषणा NETSEC_TX_SHIFT_PT_FIELD		21
#घोषणा NETSEC_TX_SHIFT_TDRID_FIELD		16
#घोषणा NETSEC_TX_SHIFT_CC_FIELD		15
#घोषणा NETSEC_TX_SHIFT_FS_FIELD		9
#घोषणा NETSEC_TX_LAST				8
#घोषणा NETSEC_TX_SHIFT_CO			7
#घोषणा NETSEC_TX_SHIFT_SO			6
#घोषणा NETSEC_TX_SHIFT_TRS_FIELD		4

#घोषणा NETSEC_RX_PKT_OWN_FIELD			31
#घोषणा NETSEC_RX_PKT_LD_FIELD			30
#घोषणा NETSEC_RX_PKT_SDRID_FIELD		24
#घोषणा NETSEC_RX_PKT_FR_FIELD			23
#घोषणा NETSEC_RX_PKT_ER_FIELD			21
#घोषणा NETSEC_RX_PKT_ERR_FIELD			16
#घोषणा NETSEC_RX_PKT_TDRID_FIELD		12
#घोषणा NETSEC_RX_PKT_FS_FIELD			9
#घोषणा NETSEC_RX_PKT_LS_FIELD			8
#घोषणा NETSEC_RX_PKT_CO_FIELD			6

#घोषणा NETSEC_RX_PKT_ERR_MASK			3

#घोषणा NETSEC_MAX_TX_PKT_LEN			1518
#घोषणा NETSEC_MAX_TX_JUMBO_PKT_LEN		9018

#घोषणा NETSEC_RING_GMAC			15
#घोषणा NETSEC_RING_MAX				2

#घोषणा NETSEC_TCP_SEG_LEN_MAX			1460
#घोषणा NETSEC_TCP_JUMBO_SEG_LEN_MAX		8960

#घोषणा NETSEC_RX_CKSUM_NOTAVAIL		0
#घोषणा NETSEC_RX_CKSUM_OK			1
#घोषणा NETSEC_RX_CKSUM_NG			2

#घोषणा NETSEC_TOP_IRQ_REG_CODE_LOAD_END	BIT(20)
#घोषणा NETSEC_IRQ_TRANSITION_COMPLETE		BIT(4)

#घोषणा NETSEC_MODE_TRANS_COMP_IRQ_N2T		BIT(20)
#घोषणा NETSEC_MODE_TRANS_COMP_IRQ_T2N		BIT(19)

#घोषणा NETSEC_INT_PKTCNT_MAX			2047

#घोषणा NETSEC_FLOW_START_TH_MAX		95
#घोषणा NETSEC_FLOW_STOP_TH_MAX			95
#घोषणा NETSEC_FLOW_PAUSE_TIME_MIN		5

#घोषणा NETSEC_CLK_EN_REG_DOM_ALL		0x3f

#घोषणा NETSEC_PKT_CTRL_REG_MODE_NRM		BIT(28)
#घोषणा NETSEC_PKT_CTRL_REG_EN_JUMBO		BIT(27)
#घोषणा NETSEC_PKT_CTRL_REG_LOG_CHKSUM_ER	BIT(3)
#घोषणा NETSEC_PKT_CTRL_REG_LOG_HD_INCOMPLETE	BIT(2)
#घोषणा NETSEC_PKT_CTRL_REG_LOG_HD_ER		BIT(1)
#घोषणा NETSEC_PKT_CTRL_REG_DRP_NO_MATCH	BIT(0)

#घोषणा NETSEC_CLK_EN_REG_DOM_G			BIT(5)
#घोषणा NETSEC_CLK_EN_REG_DOM_C			BIT(1)
#घोषणा NETSEC_CLK_EN_REG_DOM_D			BIT(0)

#घोषणा NETSEC_COM_INIT_REG_DB			BIT(2)
#घोषणा NETSEC_COM_INIT_REG_CLS			BIT(1)
#घोषणा NETSEC_COM_INIT_REG_ALL			(NETSEC_COM_INIT_REG_CLS | \
						 NETSEC_COM_INIT_REG_DB)

#घोषणा NETSEC_SOFT_RST_REG_RESET		0
#घोषणा NETSEC_SOFT_RST_REG_RUN			BIT(31)

#घोषणा NETSEC_DMA_CTRL_REG_STOP		1
#घोषणा MH_CTRL__MODE_TRANS			BIT(20)

#घोषणा NETSEC_GMAC_CMD_ST_READ			0
#घोषणा NETSEC_GMAC_CMD_ST_WRITE		BIT(28)
#घोषणा NETSEC_GMAC_CMD_ST_BUSY			BIT(31)

#घोषणा NETSEC_GMAC_BMR_REG_COMMON		0x00412080
#घोषणा NETSEC_GMAC_BMR_REG_RESET		0x00020181
#घोषणा NETSEC_GMAC_BMR_REG_SWR			0x00000001

#घोषणा NETSEC_GMAC_OMR_REG_ST			BIT(13)
#घोषणा NETSEC_GMAC_OMR_REG_SR			BIT(1)

#घोषणा NETSEC_GMAC_MCR_REG_IBN			BIT(30)
#घोषणा NETSEC_GMAC_MCR_REG_CST			BIT(25)
#घोषणा NETSEC_GMAC_MCR_REG_JE			BIT(20)
#घोषणा NETSEC_MCR_PS				BIT(15)
#घोषणा NETSEC_GMAC_MCR_REG_FES			BIT(14)
#घोषणा NETSEC_GMAC_MCR_REG_FULL_DUPLEX_COMMON	0x0000280c
#घोषणा NETSEC_GMAC_MCR_REG_HALF_DUPLEX_COMMON	0x0001a00c

#घोषणा NETSEC_FCR_RFE				BIT(2)
#घोषणा NETSEC_FCR_TFE				BIT(1)

#घोषणा NETSEC_GMAC_GAR_REG_GW			BIT(1)
#घोषणा NETSEC_GMAC_GAR_REG_GB			BIT(0)

#घोषणा NETSEC_GMAC_GAR_REG_SHIFT_PA		11
#घोषणा NETSEC_GMAC_GAR_REG_SHIFT_GR		6
#घोषणा GMAC_REG_SHIFT_CR_GAR			2

#घोषणा NETSEC_GMAC_GAR_REG_CR_25_35_MHZ	2
#घोषणा NETSEC_GMAC_GAR_REG_CR_35_60_MHZ	3
#घोषणा NETSEC_GMAC_GAR_REG_CR_60_100_MHZ	0
#घोषणा NETSEC_GMAC_GAR_REG_CR_100_150_MHZ	1
#घोषणा NETSEC_GMAC_GAR_REG_CR_150_250_MHZ	4
#घोषणा NETSEC_GMAC_GAR_REG_CR_250_300_MHZ	5

#घोषणा NETSEC_GMAC_RDLAR_REG_COMMON		0x18000
#घोषणा NETSEC_GMAC_TDLAR_REG_COMMON		0x1c000

#घोषणा NETSEC_REG_NETSEC_VER_F_TAIKI		0x50000

#घोषणा NETSEC_REG_DESC_RING_CONFIG_CFG_UP	BIT(31)
#घोषणा NETSEC_REG_DESC_RING_CONFIG_CH_RST	BIT(30)
#घोषणा NETSEC_REG_DESC_TMR_MODE		4
#घोषणा NETSEC_REG_DESC_ENDIAN			0

#घोषणा NETSEC_MAC_DESC_SOFT_RST_SOFT_RST	1
#घोषणा NETSEC_MAC_DESC_INIT_REG_INIT		1

#घोषणा NETSEC_EEPROM_MAC_ADDRESS		0x00
#घोषणा NETSEC_EEPROM_HM_ME_ADDRESS_H		0x08
#घोषणा NETSEC_EEPROM_HM_ME_ADDRESS_L		0x0C
#घोषणा NETSEC_EEPROM_HM_ME_SIZE		0x10
#घोषणा NETSEC_EEPROM_MH_ME_ADDRESS_H		0x14
#घोषणा NETSEC_EEPROM_MH_ME_ADDRESS_L		0x18
#घोषणा NETSEC_EEPROM_MH_ME_SIZE		0x1C
#घोषणा NETSEC_EEPROM_PKT_ME_ADDRESS		0x20
#घोषणा NETSEC_EEPROM_PKT_ME_SIZE		0x24

#घोषणा DESC_NUM	256

#घोषणा NETSEC_SKB_PAD (NET_SKB_PAD + NET_IP_ALIGN)
#घोषणा NETSEC_RXBUF_HEADROOM (max(XDP_PACKET_HEADROOM, NET_SKB_PAD) + \
			       NET_IP_ALIGN)
#घोषणा NETSEC_RX_BUF_NON_DATA (NETSEC_RXBUF_HEADROOM + \
				SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))
#घोषणा NETSEC_RX_BUF_SIZE	(PAGE_SIZE - NETSEC_RX_BUF_NON_DATA)

#घोषणा DESC_SZ	माप(काष्ठा netsec_de)

#घोषणा NETSEC_F_NETSEC_VER_MAJOR_NUM(x)	((x) & 0xffff0000)

#घोषणा NETSEC_XDP_PASS          0
#घोषणा NETSEC_XDP_CONSUMED      BIT(0)
#घोषणा NETSEC_XDP_TX            BIT(1)
#घोषणा NETSEC_XDP_REसूची         BIT(2)

क्रमागत ring_id अणु
	NETSEC_RING_TX = 0,
	NETSEC_RING_RX
पूर्ण;

क्रमागत buf_type अणु
	TYPE_NETSEC_SKB = 0,
	TYPE_NETSEC_XDP_TX,
	TYPE_NETSEC_XDP_NDO,
पूर्ण;

काष्ठा netsec_desc अणु
	जोड़ अणु
		काष्ठा sk_buff *skb;
		काष्ठा xdp_frame *xdpf;
	पूर्ण;
	dma_addr_t dma_addr;
	व्योम *addr;
	u16 len;
	u8 buf_type;
पूर्ण;

काष्ठा netsec_desc_ring अणु
	dma_addr_t desc_dma;
	काष्ठा netsec_desc *desc;
	व्योम *vaddr;
	u16 head, tail;
	u16 xdp_xmit; /* netsec_xdp_xmit packets */
	काष्ठा page_pool *page_pool;
	काष्ठा xdp_rxq_info xdp_rxq;
	spinlock_t lock; /* XDP tx queue locking */
पूर्ण;

काष्ठा netsec_priv अणु
	काष्ठा netsec_desc_ring desc_ring[NETSEC_RING_MAX];
	काष्ठा ethtool_coalesce et_coalesce;
	काष्ठा bpf_prog *xdp_prog;
	spinlock_t reglock; /* protect reg access */
	काष्ठा napi_काष्ठा napi;
	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	काष्ठा net_device *ndev;
	काष्ठा device_node *phy_np;
	काष्ठा phy_device *phydev;
	काष्ठा mii_bus *mii_bus;
	व्योम __iomem *ioaddr;
	व्योम __iomem *eeprom_base;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	u32 msg_enable;
	u32 freq;
	u32 phy_addr;
	bool rx_cksum_offload_flag;
पूर्ण;

काष्ठा netsec_de अणु /* Netsec Descriptor layout */
	u32 attr;
	u32 data_buf_addr_up;
	u32 data_buf_addr_lw;
	u32 buf_len_info;
पूर्ण;

काष्ठा netsec_tx_pkt_ctrl अणु
	u16 tcp_seg_len;
	bool tcp_seg_offload_flag;
	bool cksum_offload_flag;
पूर्ण;

काष्ठा netsec_rx_pkt_info अणु
	पूर्णांक rx_cksum_result;
	पूर्णांक err_code;
	bool err_flag;
पूर्ण;

अटल व्योम netsec_ग_लिखो(काष्ठा netsec_priv *priv, u32 reg_addr, u32 val)
अणु
	ग_लिखोl(val, priv->ioaddr + reg_addr);
पूर्ण

अटल u32 netsec_पढ़ो(काष्ठा netsec_priv *priv, u32 reg_addr)
अणु
	वापस पढ़ोl(priv->ioaddr + reg_addr);
पूर्ण

/************* MDIO BUS OPS FOLLOW *************/

#घोषणा TIMEOUT_SPINS_MAC		1000
#घोषणा TIMEOUT_SECONDARY_MS_MAC	100

अटल u32 netsec_clk_type(u32 freq)
अणु
	अगर (freq < MHZ(35))
		वापस NETSEC_GMAC_GAR_REG_CR_25_35_MHZ;
	अगर (freq < MHZ(60))
		वापस NETSEC_GMAC_GAR_REG_CR_35_60_MHZ;
	अगर (freq < MHZ(100))
		वापस NETSEC_GMAC_GAR_REG_CR_60_100_MHZ;
	अगर (freq < MHZ(150))
		वापस NETSEC_GMAC_GAR_REG_CR_100_150_MHZ;
	अगर (freq < MHZ(250))
		वापस NETSEC_GMAC_GAR_REG_CR_150_250_MHZ;

	वापस NETSEC_GMAC_GAR_REG_CR_250_300_MHZ;
पूर्ण

अटल पूर्णांक netsec_रुको_जबतक_busy(काष्ठा netsec_priv *priv, u32 addr, u32 mask)
अणु
	u32 समयout = TIMEOUT_SPINS_MAC;

	जबतक (--समयout && netsec_पढ़ो(priv, addr) & mask)
		cpu_relax();
	अगर (समयout)
		वापस 0;

	समयout = TIMEOUT_SECONDARY_MS_MAC;
	जबतक (--समयout && netsec_पढ़ो(priv, addr) & mask)
		usleep_range(1000, 2000);

	अगर (समयout)
		वापस 0;

	netdev_WARN(priv->ndev, "%s: timeout\n", __func__);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक netsec_mac_ग_लिखो(काष्ठा netsec_priv *priv, u32 addr, u32 value)
अणु
	netsec_ग_लिखो(priv, MAC_REG_DATA, value);
	netsec_ग_लिखो(priv, MAC_REG_CMD, addr | NETSEC_GMAC_CMD_ST_WRITE);
	वापस netsec_रुको_जबतक_busy(priv,
				      MAC_REG_CMD, NETSEC_GMAC_CMD_ST_BUSY);
पूर्ण

अटल पूर्णांक netsec_mac_पढ़ो(काष्ठा netsec_priv *priv, u32 addr, u32 *पढ़ो)
अणु
	पूर्णांक ret;

	netsec_ग_लिखो(priv, MAC_REG_CMD, addr | NETSEC_GMAC_CMD_ST_READ);
	ret = netsec_रुको_जबतक_busy(priv,
				     MAC_REG_CMD, NETSEC_GMAC_CMD_ST_BUSY);
	अगर (ret)
		वापस ret;

	*पढ़ो = netsec_पढ़ो(priv, MAC_REG_DATA);

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_mac_रुको_जबतक_busy(काष्ठा netsec_priv *priv,
				      u32 addr, u32 mask)
अणु
	u32 समयout = TIMEOUT_SPINS_MAC;
	पूर्णांक ret, data;

	करो अणु
		ret = netsec_mac_पढ़ो(priv, addr, &data);
		अगर (ret)
			अवरोध;
		cpu_relax();
	पूर्ण जबतक (--समयout && (data & mask));

	अगर (समयout)
		वापस 0;

	समयout = TIMEOUT_SECONDARY_MS_MAC;
	करो अणु
		usleep_range(1000, 2000);

		ret = netsec_mac_पढ़ो(priv, addr, &data);
		अगर (ret)
			अवरोध;
		cpu_relax();
	पूर्ण जबतक (--समयout && (data & mask));

	अगर (समयout && !ret)
		वापस 0;

	netdev_WARN(priv->ndev, "%s: timeout\n", __func__);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक netsec_mac_update_to_phy_state(काष्ठा netsec_priv *priv)
अणु
	काष्ठा phy_device *phydev = priv->ndev->phydev;
	u32 value = 0;

	value = phydev->duplex ? NETSEC_GMAC_MCR_REG_FULL_DUPLEX_COMMON :
				 NETSEC_GMAC_MCR_REG_HALF_DUPLEX_COMMON;

	अगर (phydev->speed != SPEED_1000)
		value |= NETSEC_MCR_PS;

	अगर (priv->phy_पूर्णांकerface != PHY_INTERFACE_MODE_GMII &&
	    phydev->speed == SPEED_100)
		value |= NETSEC_GMAC_MCR_REG_FES;

	value |= NETSEC_GMAC_MCR_REG_CST | NETSEC_GMAC_MCR_REG_JE;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(priv->phy_पूर्णांकerface))
		value |= NETSEC_GMAC_MCR_REG_IBN;

	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_MCR, value))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_phy_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक reg_addr);

अटल पूर्णांक netsec_phy_ग_लिखो(काष्ठा mii_bus *bus,
			    पूर्णांक phy_addr, पूर्णांक reg, u16 val)
अणु
	पूर्णांक status;
	काष्ठा netsec_priv *priv = bus->priv;

	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_GDR, val))
		वापस -ETIMEDOUT;
	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_GAR,
			     phy_addr << NETSEC_GMAC_GAR_REG_SHIFT_PA |
			     reg << NETSEC_GMAC_GAR_REG_SHIFT_GR |
			     NETSEC_GMAC_GAR_REG_GW | NETSEC_GMAC_GAR_REG_GB |
			     (netsec_clk_type(priv->freq) <<
			      GMAC_REG_SHIFT_CR_GAR)))
		वापस -ETIMEDOUT;

	status = netsec_mac_रुको_जबतक_busy(priv, GMAC_REG_GAR,
					    NETSEC_GMAC_GAR_REG_GB);

	/* Developerbox implements RTL8211E PHY and there is
	 * a compatibility problem with F_GMAC4.
	 * RTL8211E expects MDC घड़ी must be kept toggling क्रम several
	 * घड़ी cycle with MDIO high beक्रमe entering the IDLE state.
	 * To meet this requirement, netsec driver needs to issue dummy
	 * पढ़ो(e.g. पढ़ो PHYID1(offset 0x2) रेजिस्टर) right after ग_लिखो.
	 */
	netsec_phy_पढ़ो(bus, phy_addr, MII_PHYSID1);

	वापस status;
पूर्ण

अटल पूर्णांक netsec_phy_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक reg_addr)
अणु
	काष्ठा netsec_priv *priv = bus->priv;
	u32 data;
	पूर्णांक ret;

	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_GAR, NETSEC_GMAC_GAR_REG_GB |
			     phy_addr << NETSEC_GMAC_GAR_REG_SHIFT_PA |
			     reg_addr << NETSEC_GMAC_GAR_REG_SHIFT_GR |
			     (netsec_clk_type(priv->freq) <<
			      GMAC_REG_SHIFT_CR_GAR)))
		वापस -ETIMEDOUT;

	ret = netsec_mac_रुको_जबतक_busy(priv, GMAC_REG_GAR,
					 NETSEC_GMAC_GAR_REG_GB);
	अगर (ret)
		वापस ret;

	ret = netsec_mac_पढ़ो(priv, GMAC_REG_GDR, &data);
	अगर (ret)
		वापस ret;

	वापस data;
पूर्ण

/************* ETHTOOL_OPS FOLLOW *************/

अटल व्योम netsec_et_get_drvinfo(काष्ठा net_device *net_device,
				  काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, "netsec", माप(info->driver));
	strlcpy(info->bus_info, dev_name(net_device->dev.parent),
		माप(info->bus_info));
पूर्ण

अटल पूर्णांक netsec_et_get_coalesce(काष्ठा net_device *net_device,
				  काष्ठा ethtool_coalesce *et_coalesce)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(net_device);

	*et_coalesce = priv->et_coalesce;

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_et_set_coalesce(काष्ठा net_device *net_device,
				  काष्ठा ethtool_coalesce *et_coalesce)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(net_device);

	priv->et_coalesce = *et_coalesce;

	अगर (priv->et_coalesce.tx_coalesce_usecs < 50)
		priv->et_coalesce.tx_coalesce_usecs = 50;
	अगर (priv->et_coalesce.tx_max_coalesced_frames < 1)
		priv->et_coalesce.tx_max_coalesced_frames = 1;

	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_DONE_TXINT_PKTCNT,
		     priv->et_coalesce.tx_max_coalesced_frames);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_TXINT_TMR,
		     priv->et_coalesce.tx_coalesce_usecs);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_INTEN_SET, NRM_TX_ST_TXDONE);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_INTEN_SET, NRM_TX_ST_TMREXP);

	अगर (priv->et_coalesce.rx_coalesce_usecs < 50)
		priv->et_coalesce.rx_coalesce_usecs = 50;
	अगर (priv->et_coalesce.rx_max_coalesced_frames < 1)
		priv->et_coalesce.rx_max_coalesced_frames = 1;

	netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_RXINT_PKTCNT,
		     priv->et_coalesce.rx_max_coalesced_frames);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_RXINT_TMR,
		     priv->et_coalesce.rx_coalesce_usecs);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_INTEN_SET, NRM_RX_ST_PKTCNT);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_INTEN_SET, NRM_RX_ST_TMREXP);

	वापस 0;
पूर्ण

अटल u32 netsec_et_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(dev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम netsec_et_set_msglevel(काष्ठा net_device *dev, u32 datum)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(dev);

	priv->msg_enable = datum;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netsec_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo		= netsec_et_get_drvinfo,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
	.get_link		= ethtool_op_get_link,
	.get_coalesce		= netsec_et_get_coalesce,
	.set_coalesce		= netsec_et_set_coalesce,
	.get_msglevel		= netsec_et_get_msglevel,
	.set_msglevel		= netsec_et_set_msglevel,
पूर्ण;

/************* NETDEV_OPS FOLLOW *************/


अटल व्योम netsec_set_rx_de(काष्ठा netsec_priv *priv,
			     काष्ठा netsec_desc_ring *dring, u16 idx,
			     स्थिर काष्ठा netsec_desc *desc)
अणु
	काष्ठा netsec_de *de = dring->vaddr + DESC_SZ * idx;
	u32 attr = (1 << NETSEC_RX_PKT_OWN_FIELD) |
		   (1 << NETSEC_RX_PKT_FS_FIELD) |
		   (1 << NETSEC_RX_PKT_LS_FIELD);

	अगर (idx == DESC_NUM - 1)
		attr |= (1 << NETSEC_RX_PKT_LD_FIELD);

	de->data_buf_addr_up = upper_32_bits(desc->dma_addr);
	de->data_buf_addr_lw = lower_32_bits(desc->dma_addr);
	de->buf_len_info = desc->len;
	de->attr = attr;
	dma_wmb();

	dring->desc[idx].dma_addr = desc->dma_addr;
	dring->desc[idx].addr = desc->addr;
	dring->desc[idx].len = desc->len;
पूर्ण

अटल bool netsec_clean_tx_dring(काष्ठा netsec_priv *priv)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_TX];
	काष्ठा xdp_frame_bulk bq;
	काष्ठा netsec_de *entry;
	पूर्णांक tail = dring->tail;
	अचिन्हित पूर्णांक bytes;
	पूर्णांक cnt = 0;

	spin_lock(&dring->lock);

	bytes = 0;
	xdp_frame_bulk_init(&bq);
	entry = dring->vaddr + DESC_SZ * tail;

	rcu_पढ़ो_lock(); /* need क्रम xdp_वापस_frame_bulk */

	जबतक (!(entry->attr & (1U << NETSEC_TX_SHIFT_OWN_FIELD)) &&
	       cnt < DESC_NUM) अणु
		काष्ठा netsec_desc *desc;
		पूर्णांक eop;

		desc = &dring->desc[tail];
		eop = (entry->attr >> NETSEC_TX_LAST) & 1;
		dma_rmb();

		/* अगर buf_type is either TYPE_NETSEC_SKB or
		 * TYPE_NETSEC_XDP_NDO we mapped it
		 */
		अगर (desc->buf_type != TYPE_NETSEC_XDP_TX)
			dma_unmap_single(priv->dev, desc->dma_addr, desc->len,
					 DMA_TO_DEVICE);

		अगर (!eop)
			जाओ next;

		अगर (desc->buf_type == TYPE_NETSEC_SKB) अणु
			bytes += desc->skb->len;
			dev_kमुक्त_skb(desc->skb);
		पूर्ण अन्यथा अणु
			bytes += desc->xdpf->len;
			अगर (desc->buf_type == TYPE_NETSEC_XDP_TX)
				xdp_वापस_frame_rx_napi(desc->xdpf);
			अन्यथा
				xdp_वापस_frame_bulk(desc->xdpf, &bq);
		पूर्ण
next:
		/* clean up so netsec_uninit_pkt_dring() won't मुक्त the skb
		 * again
		 */
		*desc = (काष्ठा netsec_desc)अणुपूर्ण;

		/* entry->attr is not going to be accessed by the NIC until
		 * netsec_set_tx_de() is called. No need क्रम a dma_wmb() here
		 */
		entry->attr = 1U << NETSEC_TX_SHIFT_OWN_FIELD;
		/* move tail ahead */
		dring->tail = (tail + 1) % DESC_NUM;

		tail = dring->tail;
		entry = dring->vaddr + DESC_SZ * tail;
		cnt++;
	पूर्ण
	xdp_flush_frame_bulk(&bq);

	rcu_पढ़ो_unlock();

	spin_unlock(&dring->lock);

	अगर (!cnt)
		वापस false;

	/* पढ़ोing the रेजिस्टर clears the irq */
	netsec_पढ़ो(priv, NETSEC_REG_NRM_TX_DONE_PKTCNT);

	priv->ndev->stats.tx_packets += cnt;
	priv->ndev->stats.tx_bytes += bytes;

	netdev_completed_queue(priv->ndev, cnt, bytes);

	वापस true;
पूर्ण

अटल व्योम netsec_process_tx(काष्ठा netsec_priv *priv)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	bool cleaned;

	cleaned = netsec_clean_tx_dring(priv);

	अगर (cleaned && netअगर_queue_stopped(ndev)) अणु
		/* Make sure we update the value, anyone stopping the queue
		 * after this will पढ़ो the proper consumer idx
		 */
		smp_wmb();
		netअगर_wake_queue(ndev);
	पूर्ण
पूर्ण

अटल व्योम *netsec_alloc_rx_data(काष्ठा netsec_priv *priv,
				  dma_addr_t *dma_handle, u16 *desc_len)

अणु

	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_RX];
	काष्ठा page *page;

	page = page_pool_dev_alloc_pages(dring->page_pool);
	अगर (!page)
		वापस शून्य;

	/* We allocate the same buffer length क्रम XDP and non-XDP हालs.
	 * page_pool API will map the whole page, skip what's needed क्रम
	 * network payloads and/or XDP
	 */
	*dma_handle = page_pool_get_dma_addr(page) + NETSEC_RXBUF_HEADROOM;
	/* Make sure the incoming payload fits in the page क्रम XDP and non-XDP
	 * हालs and reserve enough space क्रम headroom + skb_shared_info
	 */
	*desc_len = NETSEC_RX_BUF_SIZE;

	वापस page_address(page);
पूर्ण

अटल व्योम netsec_rx_fill(काष्ठा netsec_priv *priv, u16 from, u16 num)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_RX];
	u16 idx = from;

	जबतक (num) अणु
		netsec_set_rx_de(priv, dring, idx, &dring->desc[idx]);
		idx++;
		अगर (idx >= DESC_NUM)
			idx = 0;
		num--;
	पूर्ण
पूर्ण

अटल व्योम netsec_xdp_ring_tx_db(काष्ठा netsec_priv *priv, u16 pkts)
अणु
	अगर (likely(pkts))
		netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_PKTCNT, pkts);
पूर्ण

अटल व्योम netsec_finalize_xdp_rx(काष्ठा netsec_priv *priv, u32 xdp_res,
				   u16 pkts)
अणु
	अगर (xdp_res & NETSEC_XDP_REसूची)
		xdp_करो_flush_map();

	अगर (xdp_res & NETSEC_XDP_TX)
		netsec_xdp_ring_tx_db(priv, pkts);
पूर्ण

अटल व्योम netsec_set_tx_de(काष्ठा netsec_priv *priv,
			     काष्ठा netsec_desc_ring *dring,
			     स्थिर काष्ठा netsec_tx_pkt_ctrl *tx_ctrl,
			     स्थिर काष्ठा netsec_desc *desc, व्योम *buf)
अणु
	पूर्णांक idx = dring->head;
	काष्ठा netsec_de *de;
	u32 attr;

	de = dring->vaddr + (DESC_SZ * idx);

	attr = (1 << NETSEC_TX_SHIFT_OWN_FIELD) |
	       (1 << NETSEC_TX_SHIFT_PT_FIELD) |
	       (NETSEC_RING_GMAC << NETSEC_TX_SHIFT_TDRID_FIELD) |
	       (1 << NETSEC_TX_SHIFT_FS_FIELD) |
	       (1 << NETSEC_TX_LAST) |
	       (tx_ctrl->cksum_offload_flag << NETSEC_TX_SHIFT_CO) |
	       (tx_ctrl->tcp_seg_offload_flag << NETSEC_TX_SHIFT_SO) |
	       (1 << NETSEC_TX_SHIFT_TRS_FIELD);
	अगर (idx == DESC_NUM - 1)
		attr |= (1 << NETSEC_TX_SHIFT_LD_FIELD);

	de->data_buf_addr_up = upper_32_bits(desc->dma_addr);
	de->data_buf_addr_lw = lower_32_bits(desc->dma_addr);
	de->buf_len_info = (tx_ctrl->tcp_seg_len << 16) | desc->len;
	de->attr = attr;

	dring->desc[idx] = *desc;
	अगर (desc->buf_type == TYPE_NETSEC_SKB)
		dring->desc[idx].skb = buf;
	अन्यथा अगर (desc->buf_type == TYPE_NETSEC_XDP_TX ||
		 desc->buf_type == TYPE_NETSEC_XDP_NDO)
		dring->desc[idx].xdpf = buf;

	/* move head ahead */
	dring->head = (dring->head + 1) % DESC_NUM;
पूर्ण

/* The current driver only supports 1 Txq, this should run under spin_lock() */
अटल u32 netsec_xdp_queue_one(काष्ठा netsec_priv *priv,
				काष्ठा xdp_frame *xdpf, bool is_nकरो)

अणु
	काष्ठा netsec_desc_ring *tx_ring = &priv->desc_ring[NETSEC_RING_TX];
	काष्ठा page *page = virt_to_page(xdpf->data);
	काष्ठा netsec_tx_pkt_ctrl tx_ctrl = अणुपूर्ण;
	काष्ठा netsec_desc tx_desc;
	dma_addr_t dma_handle;
	u16 filled;

	अगर (tx_ring->head >= tx_ring->tail)
		filled = tx_ring->head - tx_ring->tail;
	अन्यथा
		filled = tx_ring->head + DESC_NUM - tx_ring->tail;

	अगर (DESC_NUM - filled <= 1)
		वापस NETSEC_XDP_CONSUMED;

	अगर (is_nकरो) अणु
		/* this is क्रम nकरो_xdp_xmit, the buffer needs mapping beक्रमe
		 * sending
		 */
		dma_handle = dma_map_single(priv->dev, xdpf->data, xdpf->len,
					    DMA_TO_DEVICE);
		अगर (dma_mapping_error(priv->dev, dma_handle))
			वापस NETSEC_XDP_CONSUMED;
		tx_desc.buf_type = TYPE_NETSEC_XDP_NDO;
	पूर्ण अन्यथा अणु
		/* This is the device Rx buffer from page_pool. No need to remap
		 * just sync and send it
		 */
		काष्ठा netsec_desc_ring *rx_ring =
			&priv->desc_ring[NETSEC_RING_RX];
		क्रमागत dma_data_direction dma_dir =
			page_pool_get_dma_dir(rx_ring->page_pool);

		dma_handle = page_pool_get_dma_addr(page) + xdpf->headroom +
			माप(*xdpf);
		dma_sync_single_क्रम_device(priv->dev, dma_handle, xdpf->len,
					   dma_dir);
		tx_desc.buf_type = TYPE_NETSEC_XDP_TX;
	पूर्ण

	tx_desc.dma_addr = dma_handle;
	tx_desc.addr = xdpf->data;
	tx_desc.len = xdpf->len;

	netdev_sent_queue(priv->ndev, xdpf->len);
	netsec_set_tx_de(priv, tx_ring, &tx_ctrl, &tx_desc, xdpf);

	वापस NETSEC_XDP_TX;
पूर्ण

अटल u32 netsec_xdp_xmit_back(काष्ठा netsec_priv *priv, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा netsec_desc_ring *tx_ring = &priv->desc_ring[NETSEC_RING_TX];
	काष्ठा xdp_frame *xdpf = xdp_convert_buff_to_frame(xdp);
	u32 ret;

	अगर (unlikely(!xdpf))
		वापस NETSEC_XDP_CONSUMED;

	spin_lock(&tx_ring->lock);
	ret = netsec_xdp_queue_one(priv, xdpf, false);
	spin_unlock(&tx_ring->lock);

	वापस ret;
पूर्ण

अटल u32 netsec_run_xdp(काष्ठा netsec_priv *priv, काष्ठा bpf_prog *prog,
			  काष्ठा xdp_buff *xdp)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_RX];
	अचिन्हित पूर्णांक sync, len = xdp->data_end - xdp->data;
	u32 ret = NETSEC_XDP_PASS;
	काष्ठा page *page;
	पूर्णांक err;
	u32 act;

	act = bpf_prog_run_xdp(prog, xdp);

	/* Due xdp_adjust_tail: DMA sync क्रम_device cover max len CPU touch */
	sync = xdp->data_end - xdp->data_hard_start - NETSEC_RXBUF_HEADROOM;
	sync = max(sync, len);

	चयन (act) अणु
	हाल XDP_PASS:
		ret = NETSEC_XDP_PASS;
		अवरोध;
	हाल XDP_TX:
		ret = netsec_xdp_xmit_back(priv, xdp);
		अगर (ret != NETSEC_XDP_TX) अणु
			page = virt_to_head_page(xdp->data);
			page_pool_put_page(dring->page_pool, page, sync, true);
		पूर्ण
		अवरोध;
	हाल XDP_REसूचीECT:
		err = xdp_करो_redirect(priv->ndev, xdp, prog);
		अगर (!err) अणु
			ret = NETSEC_XDP_REसूची;
		पूर्ण अन्यथा अणु
			ret = NETSEC_XDP_CONSUMED;
			page = virt_to_head_page(xdp->data);
			page_pool_put_page(dring->page_pool, page, sync, true);
		पूर्ण
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(priv->ndev, prog, act);
		fallthrough;	/* handle पातs by dropping packet */
	हाल XDP_DROP:
		ret = NETSEC_XDP_CONSUMED;
		page = virt_to_head_page(xdp->data);
		page_pool_put_page(dring->page_pool, page, sync, true);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक netsec_process_rx(काष्ठा netsec_priv *priv, पूर्णांक budget)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_RX];
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा netsec_rx_pkt_info rx_info;
	क्रमागत dma_data_direction dma_dir;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा xdp_buff xdp;
	u16 xdp_xmit = 0;
	u32 xdp_act = 0;
	पूर्णांक करोne = 0;

	xdp_init_buff(&xdp, PAGE_SIZE, &dring->xdp_rxq);

	rcu_पढ़ो_lock();
	xdp_prog = READ_ONCE(priv->xdp_prog);
	dma_dir = page_pool_get_dma_dir(dring->page_pool);

	जबतक (करोne < budget) अणु
		u16 idx = dring->tail;
		काष्ठा netsec_de *de = dring->vaddr + (DESC_SZ * idx);
		काष्ठा netsec_desc *desc = &dring->desc[idx];
		काष्ठा page *page = virt_to_page(desc->addr);
		u32 xdp_result = NETSEC_XDP_PASS;
		काष्ठा sk_buff *skb = शून्य;
		u16 pkt_len, desc_len;
		dma_addr_t dma_handle;
		व्योम *buf_addr;

		अगर (de->attr & (1U << NETSEC_RX_PKT_OWN_FIELD)) अणु
			/* पढ़ोing the रेजिस्टर clears the irq */
			netsec_पढ़ो(priv, NETSEC_REG_NRM_RX_PKTCNT);
			अवरोध;
		पूर्ण

		/* This  barrier is needed to keep us from पढ़ोing
		 * any other fields out of the netsec_de until we have
		 * verअगरied the descriptor has been written back
		 */
		dma_rmb();
		करोne++;

		pkt_len = de->buf_len_info >> 16;
		rx_info.err_code = (de->attr >> NETSEC_RX_PKT_ERR_FIELD) &
			NETSEC_RX_PKT_ERR_MASK;
		rx_info.err_flag = (de->attr >> NETSEC_RX_PKT_ER_FIELD) & 1;
		अगर (rx_info.err_flag) अणु
			netअगर_err(priv, drv, priv->ndev,
				  "%s: rx fail err(%d)\n", __func__,
				  rx_info.err_code);
			ndev->stats.rx_dropped++;
			dring->tail = (dring->tail + 1) % DESC_NUM;
			/* reuse buffer page frag */
			netsec_rx_fill(priv, idx, 1);
			जारी;
		पूर्ण
		rx_info.rx_cksum_result =
			(de->attr >> NETSEC_RX_PKT_CO_FIELD) & 3;

		/* allocate a fresh buffer and map it to the hardware.
		 * This will eventually replace the old buffer in the hardware
		 */
		buf_addr = netsec_alloc_rx_data(priv, &dma_handle, &desc_len);

		अगर (unlikely(!buf_addr))
			अवरोध;

		dma_sync_single_क्रम_cpu(priv->dev, desc->dma_addr, pkt_len,
					dma_dir);
		prefetch(desc->addr);

		xdp_prepare_buff(&xdp, desc->addr, NETSEC_RXBUF_HEADROOM,
				 pkt_len, false);

		अगर (xdp_prog) अणु
			xdp_result = netsec_run_xdp(priv, xdp_prog, &xdp);
			अगर (xdp_result != NETSEC_XDP_PASS) अणु
				xdp_act |= xdp_result;
				अगर (xdp_result == NETSEC_XDP_TX)
					xdp_xmit++;
				जाओ next;
			पूर्ण
		पूर्ण
		skb = build_skb(desc->addr, desc->len + NETSEC_RX_BUF_NON_DATA);

		अगर (unlikely(!skb)) अणु
			/* If skb fails recycle_direct will either unmap and
			 * मुक्त the page or refill the cache depending on the
			 * cache state. Since we paid the allocation cost अगर
			 * building an skb fails try to put the page पूर्णांकo cache
			 */
			page_pool_put_page(dring->page_pool, page, pkt_len,
					   true);
			netअगर_err(priv, drv, priv->ndev,
				  "rx failed to build skb\n");
			अवरोध;
		पूर्ण
		page_pool_release_page(dring->page_pool, page);

		skb_reserve(skb, xdp.data - xdp.data_hard_start);
		skb_put(skb, xdp.data_end - xdp.data);
		skb->protocol = eth_type_trans(skb, priv->ndev);

		अगर (priv->rx_cksum_offload_flag &&
		    rx_info.rx_cksum_result == NETSEC_RX_CKSUM_OK)
			skb->ip_summed = CHECKSUM_UNNECESSARY;

next:
		अगर (skb)
			napi_gro_receive(&priv->napi, skb);
		अगर (skb || xdp_result) अणु
			ndev->stats.rx_packets++;
			ndev->stats.rx_bytes += xdp.data_end - xdp.data;
		पूर्ण

		/* Update the descriptor with fresh buffers */
		desc->len = desc_len;
		desc->dma_addr = dma_handle;
		desc->addr = buf_addr;

		netsec_rx_fill(priv, idx, 1);
		dring->tail = (dring->tail + 1) % DESC_NUM;
	पूर्ण
	netsec_finalize_xdp_rx(priv, xdp_act, xdp_xmit);

	rcu_पढ़ो_unlock();

	वापस करोne;
पूर्ण

अटल पूर्णांक netsec_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा netsec_priv *priv;
	पूर्णांक करोne;

	priv = container_of(napi, काष्ठा netsec_priv, napi);

	netsec_process_tx(priv);
	करोne = netsec_process_rx(priv, budget);

	अगर (करोne < budget && napi_complete_करोne(napi, करोne)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&priv->reglock, flags);
		netsec_ग_लिखो(priv, NETSEC_REG_INTEN_SET,
			     NETSEC_IRQ_RX | NETSEC_IRQ_TX);
		spin_unlock_irqrestore(&priv->reglock, flags);
	पूर्ण

	वापस करोne;
पूर्ण


अटल पूर्णांक netsec_desc_used(काष्ठा netsec_desc_ring *dring)
अणु
	पूर्णांक used;

	अगर (dring->head >= dring->tail)
		used = dring->head - dring->tail;
	अन्यथा
		used = dring->head + DESC_NUM - dring->tail;

	वापस used;
पूर्ण

अटल पूर्णांक netsec_check_stop_tx(काष्ठा netsec_priv *priv, पूर्णांक used)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_TX];

	/* keep tail from touching the queue */
	अगर (DESC_NUM - used < 2) अणु
		netअगर_stop_queue(priv->ndev);

		/* Make sure we पढ़ो the updated value in हाल
		 * descriptors got मुक्तd
		 */
		smp_rmb();

		used = netsec_desc_used(dring);
		अगर (DESC_NUM - used < 2)
			वापस NETDEV_TX_BUSY;

		netअगर_wake_queue(priv->ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_tx_t netsec_netdev_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *ndev)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(ndev);
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_TX];
	काष्ठा netsec_tx_pkt_ctrl tx_ctrl = अणुपूर्ण;
	काष्ठा netsec_desc tx_desc;
	u16 tso_seg_len = 0;
	पूर्णांक filled;

	spin_lock_bh(&dring->lock);
	filled = netsec_desc_used(dring);
	अगर (netsec_check_stop_tx(priv, filled)) अणु
		spin_unlock_bh(&dring->lock);
		net_warn_ratelimited("%s %s Tx queue full\n",
				     dev_name(priv->dev), ndev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		tx_ctrl.cksum_offload_flag = true;

	अगर (skb_is_gso(skb))
		tso_seg_len = skb_shinfo(skb)->gso_size;

	अगर (tso_seg_len > 0) अणु
		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			ip_hdr(skb)->tot_len = 0;
			tcp_hdr(skb)->check =
				~tcp_v4_check(0, ip_hdr(skb)->saddr,
					      ip_hdr(skb)->daddr, 0);
		पूर्ण अन्यथा अणु
			tcp_v6_gso_csum_prep(skb);
		पूर्ण

		tx_ctrl.tcp_seg_offload_flag = true;
		tx_ctrl.tcp_seg_len = tso_seg_len;
	पूर्ण

	tx_desc.dma_addr = dma_map_single(priv->dev, skb->data,
					  skb_headlen(skb), DMA_TO_DEVICE);
	अगर (dma_mapping_error(priv->dev, tx_desc.dma_addr)) अणु
		spin_unlock_bh(&dring->lock);
		netअगर_err(priv, drv, priv->ndev,
			  "%s: DMA mapping failed\n", __func__);
		ndev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	tx_desc.addr = skb->data;
	tx_desc.len = skb_headlen(skb);
	tx_desc.buf_type = TYPE_NETSEC_SKB;

	skb_tx_बारtamp(skb);
	netdev_sent_queue(priv->ndev, skb->len);

	netsec_set_tx_de(priv, dring, &tx_ctrl, &tx_desc, skb);
	spin_unlock_bh(&dring->lock);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_PKTCNT, 1); /* submit another tx */

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम netsec_uninit_pkt_dring(काष्ठा netsec_priv *priv, पूर्णांक id)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[id];
	काष्ठा netsec_desc *desc;
	u16 idx;

	अगर (!dring->vaddr || !dring->desc)
		वापस;
	क्रम (idx = 0; idx < DESC_NUM; idx++) अणु
		desc = &dring->desc[idx];
		अगर (!desc->addr)
			जारी;

		अगर (id == NETSEC_RING_RX) अणु
			काष्ठा page *page = virt_to_page(desc->addr);

			page_pool_put_full_page(dring->page_pool, page, false);
		पूर्ण अन्यथा अगर (id == NETSEC_RING_TX) अणु
			dma_unmap_single(priv->dev, desc->dma_addr, desc->len,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb(desc->skb);
		पूर्ण
	पूर्ण

	/* Rx is currently using page_pool */
	अगर (id == NETSEC_RING_RX) अणु
		अगर (xdp_rxq_info_is_reg(&dring->xdp_rxq))
			xdp_rxq_info_unreg(&dring->xdp_rxq);
		page_pool_destroy(dring->page_pool);
	पूर्ण

	स_रखो(dring->desc, 0, माप(काष्ठा netsec_desc) * DESC_NUM);
	स_रखो(dring->vaddr, 0, DESC_SZ * DESC_NUM);

	dring->head = 0;
	dring->tail = 0;

	अगर (id == NETSEC_RING_TX)
		netdev_reset_queue(priv->ndev);
पूर्ण

अटल व्योम netsec_मुक्त_dring(काष्ठा netsec_priv *priv, पूर्णांक id)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[id];

	अगर (dring->vaddr) अणु
		dma_मुक्त_coherent(priv->dev, DESC_SZ * DESC_NUM,
				  dring->vaddr, dring->desc_dma);
		dring->vaddr = शून्य;
	पूर्ण

	kमुक्त(dring->desc);
	dring->desc = शून्य;
पूर्ण

अटल पूर्णांक netsec_alloc_dring(काष्ठा netsec_priv *priv, क्रमागत ring_id id)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[id];

	dring->vaddr = dma_alloc_coherent(priv->dev, DESC_SZ * DESC_NUM,
					  &dring->desc_dma, GFP_KERNEL);
	अगर (!dring->vaddr)
		जाओ err;

	dring->desc = kसुस्मृति(DESC_NUM, माप(*dring->desc), GFP_KERNEL);
	अगर (!dring->desc)
		जाओ err;

	वापस 0;
err:
	netsec_मुक्त_dring(priv, id);

	वापस -ENOMEM;
पूर्ण

अटल व्योम netsec_setup_tx_dring(काष्ठा netsec_priv *priv)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_TX];
	पूर्णांक i;

	क्रम (i = 0; i < DESC_NUM; i++) अणु
		काष्ठा netsec_de *de;

		de = dring->vaddr + (DESC_SZ * i);
		/* de->attr is not going to be accessed by the NIC
		 * until netsec_set_tx_de() is called.
		 * No need क्रम a dma_wmb() here
		 */
		de->attr = 1U << NETSEC_TX_SHIFT_OWN_FIELD;
	पूर्ण
पूर्ण

अटल पूर्णांक netsec_setup_rx_dring(काष्ठा netsec_priv *priv)
अणु
	काष्ठा netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_RX];
	काष्ठा bpf_prog *xdp_prog = READ_ONCE(priv->xdp_prog);
	काष्ठा page_pool_params pp_params = अणु
		.order = 0,
		/* पूर्णांकernal DMA mapping in page_pool */
		.flags = PP_FLAG_DMA_MAP | PP_FLAG_DMA_SYNC_DEV,
		.pool_size = DESC_NUM,
		.nid = NUMA_NO_NODE,
		.dev = priv->dev,
		.dma_dir = xdp_prog ? DMA_BIसूचीECTIONAL : DMA_FROM_DEVICE,
		.offset = NETSEC_RXBUF_HEADROOM,
		.max_len = NETSEC_RX_BUF_SIZE,
	पूर्ण;
	पूर्णांक i, err;

	dring->page_pool = page_pool_create(&pp_params);
	अगर (IS_ERR(dring->page_pool)) अणु
		err = PTR_ERR(dring->page_pool);
		dring->page_pool = शून्य;
		जाओ err_out;
	पूर्ण

	err = xdp_rxq_info_reg(&dring->xdp_rxq, priv->ndev, 0, priv->napi.napi_id);
	अगर (err)
		जाओ err_out;

	err = xdp_rxq_info_reg_mem_model(&dring->xdp_rxq, MEM_TYPE_PAGE_POOL,
					 dring->page_pool);
	अगर (err)
		जाओ err_out;

	क्रम (i = 0; i < DESC_NUM; i++) अणु
		काष्ठा netsec_desc *desc = &dring->desc[i];
		dma_addr_t dma_handle;
		व्योम *buf;
		u16 len;

		buf = netsec_alloc_rx_data(priv, &dma_handle, &len);

		अगर (!buf) अणु
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण
		desc->dma_addr = dma_handle;
		desc->addr = buf;
		desc->len = len;
	पूर्ण

	netsec_rx_fill(priv, 0, DESC_NUM);

	वापस 0;

err_out:
	netsec_uninit_pkt_dring(priv, NETSEC_RING_RX);
	वापस err;
पूर्ण

अटल पूर्णांक netsec_netdev_load_ucode_region(काष्ठा netsec_priv *priv, u32 reg,
					   u32 addr_h, u32 addr_l, u32 size)
अणु
	u64 base = (u64)addr_h << 32 | addr_l;
	व्योम __iomem *ucode;
	u32 i;

	ucode = ioremap(base, size * माप(u32));
	अगर (!ucode)
		वापस -ENOMEM;

	क्रम (i = 0; i < size; i++)
		netsec_ग_लिखो(priv, reg, पढ़ोl(ucode + i * 4));

	iounmap(ucode);
	वापस 0;
पूर्ण

अटल पूर्णांक netsec_netdev_load_microcode(काष्ठा netsec_priv *priv)
अणु
	u32 addr_h, addr_l, size;
	पूर्णांक err;

	addr_h = पढ़ोl(priv->eeprom_base + NETSEC_EEPROM_HM_ME_ADDRESS_H);
	addr_l = पढ़ोl(priv->eeprom_base + NETSEC_EEPROM_HM_ME_ADDRESS_L);
	size = पढ़ोl(priv->eeprom_base + NETSEC_EEPROM_HM_ME_SIZE);
	err = netsec_netdev_load_ucode_region(priv, NETSEC_REG_DMAC_HM_CMD_BUF,
					      addr_h, addr_l, size);
	अगर (err)
		वापस err;

	addr_h = पढ़ोl(priv->eeprom_base + NETSEC_EEPROM_MH_ME_ADDRESS_H);
	addr_l = पढ़ोl(priv->eeprom_base + NETSEC_EEPROM_MH_ME_ADDRESS_L);
	size = पढ़ोl(priv->eeprom_base + NETSEC_EEPROM_MH_ME_SIZE);
	err = netsec_netdev_load_ucode_region(priv, NETSEC_REG_DMAC_MH_CMD_BUF,
					      addr_h, addr_l, size);
	अगर (err)
		वापस err;

	addr_h = 0;
	addr_l = पढ़ोl(priv->eeprom_base + NETSEC_EEPROM_PKT_ME_ADDRESS);
	size = पढ़ोl(priv->eeprom_base + NETSEC_EEPROM_PKT_ME_SIZE);
	err = netsec_netdev_load_ucode_region(priv, NETSEC_REG_PKT_CMD_BUF,
					      addr_h, addr_l, size);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_reset_hardware(काष्ठा netsec_priv *priv,
				 bool load_ucode)
अणु
	u32 value;
	पूर्णांक err;

	/* stop DMA engines */
	अगर (!netsec_पढ़ो(priv, NETSEC_REG_ADDR_DIS_CORE)) अणु
		netsec_ग_लिखो(priv, NETSEC_REG_DMA_HM_CTRL,
			     NETSEC_DMA_CTRL_REG_STOP);
		netsec_ग_लिखो(priv, NETSEC_REG_DMA_MH_CTRL,
			     NETSEC_DMA_CTRL_REG_STOP);

		जबतक (netsec_पढ़ो(priv, NETSEC_REG_DMA_HM_CTRL) &
		       NETSEC_DMA_CTRL_REG_STOP)
			cpu_relax();

		जबतक (netsec_पढ़ो(priv, NETSEC_REG_DMA_MH_CTRL) &
		       NETSEC_DMA_CTRL_REG_STOP)
			cpu_relax();
	पूर्ण

	netsec_ग_लिखो(priv, NETSEC_REG_SOFT_RST, NETSEC_SOFT_RST_REG_RESET);
	netsec_ग_लिखो(priv, NETSEC_REG_SOFT_RST, NETSEC_SOFT_RST_REG_RUN);
	netsec_ग_लिखो(priv, NETSEC_REG_COM_INIT, NETSEC_COM_INIT_REG_ALL);

	जबतक (netsec_पढ़ो(priv, NETSEC_REG_COM_INIT) != 0)
		cpu_relax();

	/* set desc_start addr */
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_DESC_START_UP,
		     upper_32_bits(priv->desc_ring[NETSEC_RING_RX].desc_dma));
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_DESC_START_LW,
		     lower_32_bits(priv->desc_ring[NETSEC_RING_RX].desc_dma));

	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_DESC_START_UP,
		     upper_32_bits(priv->desc_ring[NETSEC_RING_TX].desc_dma));
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_DESC_START_LW,
		     lower_32_bits(priv->desc_ring[NETSEC_RING_TX].desc_dma));

	/* set normal tx dring ring config */
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_CONFIG,
		     1 << NETSEC_REG_DESC_ENDIAN);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_CONFIG,
		     1 << NETSEC_REG_DESC_ENDIAN);

	अगर (load_ucode) अणु
		err = netsec_netdev_load_microcode(priv);
		अगर (err) अणु
			netअगर_err(priv, probe, priv->ndev,
				  "%s: failed to load microcode (%d)\n",
				  __func__, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* start DMA engines */
	netsec_ग_लिखो(priv, NETSEC_REG_DMA_TMR_CTRL, priv->freq / 1000000 - 1);
	netsec_ग_लिखो(priv, NETSEC_REG_ADDR_DIS_CORE, 0);

	usleep_range(1000, 2000);

	अगर (!(netsec_पढ़ो(priv, NETSEC_REG_TOP_STATUS) &
	      NETSEC_TOP_IRQ_REG_CODE_LOAD_END)) अणु
		netअगर_err(priv, probe, priv->ndev,
			  "microengine start failed\n");
		वापस -ENXIO;
	पूर्ण
	netsec_ग_लिखो(priv, NETSEC_REG_TOP_STATUS,
		     NETSEC_TOP_IRQ_REG_CODE_LOAD_END);

	value = NETSEC_PKT_CTRL_REG_MODE_NRM;
	अगर (priv->ndev->mtu > ETH_DATA_LEN)
		value |= NETSEC_PKT_CTRL_REG_EN_JUMBO;

	/* change to normal mode */
	netsec_ग_लिखो(priv, NETSEC_REG_DMA_MH_CTRL, MH_CTRL__MODE_TRANS);
	netsec_ग_लिखो(priv, NETSEC_REG_PKT_CTRL, value);

	जबतक ((netsec_पढ़ो(priv, NETSEC_REG_MODE_TRANS_COMP_STATUS) &
		NETSEC_MODE_TRANS_COMP_IRQ_T2N) == 0)
		cpu_relax();

	/* clear any pending EMPTY/ERR irq status */
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_STATUS, ~0);

	/* Disable TX & RX पूर्णांकr */
	netsec_ग_लिखो(priv, NETSEC_REG_INTEN_CLR, ~0);

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_start_gmac(काष्ठा netsec_priv *priv)
अणु
	काष्ठा phy_device *phydev = priv->ndev->phydev;
	u32 value = 0;
	पूर्णांक ret;

	अगर (phydev->speed != SPEED_1000)
		value = (NETSEC_GMAC_MCR_REG_CST |
			 NETSEC_GMAC_MCR_REG_HALF_DUPLEX_COMMON);

	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_MCR, value))
		वापस -ETIMEDOUT;
	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_BMR,
			     NETSEC_GMAC_BMR_REG_RESET))
		वापस -ETIMEDOUT;

	/* Wait soft reset */
	usleep_range(1000, 5000);

	ret = netsec_mac_पढ़ो(priv, GMAC_REG_BMR, &value);
	अगर (ret)
		वापस ret;
	अगर (value & NETSEC_GMAC_BMR_REG_SWR)
		वापस -EAGAIN;

	netsec_ग_लिखो(priv, MAC_REG_DESC_SOFT_RST, 1);
	अगर (netsec_रुको_जबतक_busy(priv, MAC_REG_DESC_SOFT_RST, 1))
		वापस -ETIMEDOUT;

	netsec_ग_लिखो(priv, MAC_REG_DESC_INIT, 1);
	अगर (netsec_रुको_जबतक_busy(priv, MAC_REG_DESC_INIT, 1))
		वापस -ETIMEDOUT;

	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_BMR,
			     NETSEC_GMAC_BMR_REG_COMMON))
		वापस -ETIMEDOUT;
	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_RDLAR,
			     NETSEC_GMAC_RDLAR_REG_COMMON))
		वापस -ETIMEDOUT;
	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_TDLAR,
			     NETSEC_GMAC_TDLAR_REG_COMMON))
		वापस -ETIMEDOUT;
	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_MFFR, 0x80000001))
		वापस -ETIMEDOUT;

	ret = netsec_mac_update_to_phy_state(priv);
	अगर (ret)
		वापस ret;

	ret = netsec_mac_पढ़ो(priv, GMAC_REG_OMR, &value);
	अगर (ret)
		वापस ret;

	value |= NETSEC_GMAC_OMR_REG_SR;
	value |= NETSEC_GMAC_OMR_REG_ST;

	netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_INTEN_CLR, ~0);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_INTEN_CLR, ~0);

	netsec_et_set_coalesce(priv->ndev, &priv->et_coalesce);

	अगर (netsec_mac_ग_लिखो(priv, GMAC_REG_OMR, value))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_stop_gmac(काष्ठा netsec_priv *priv)
अणु
	u32 value;
	पूर्णांक ret;

	ret = netsec_mac_पढ़ो(priv, GMAC_REG_OMR, &value);
	अगर (ret)
		वापस ret;
	value &= ~NETSEC_GMAC_OMR_REG_SR;
	value &= ~NETSEC_GMAC_OMR_REG_ST;

	/* disable all पूर्णांकerrupts */
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_INTEN_CLR, ~0);
	netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_INTEN_CLR, ~0);

	वापस netsec_mac_ग_लिखो(priv, GMAC_REG_OMR, value);
पूर्ण

अटल व्योम netsec_phy_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(ndev);

	अगर (ndev->phydev->link)
		netsec_start_gmac(priv);
	अन्यथा
		netsec_stop_gmac(priv);

	phy_prपूर्णांक_status(ndev->phydev);
पूर्ण

अटल irqवापस_t netsec_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा netsec_priv *priv = dev_id;
	u32 val, status = netsec_पढ़ो(priv, NETSEC_REG_TOP_STATUS);
	अचिन्हित दीर्घ flags;

	/* Disable पूर्णांकerrupts */
	अगर (status & NETSEC_IRQ_TX) अणु
		val = netsec_पढ़ो(priv, NETSEC_REG_NRM_TX_STATUS);
		netsec_ग_लिखो(priv, NETSEC_REG_NRM_TX_STATUS, val);
	पूर्ण
	अगर (status & NETSEC_IRQ_RX) अणु
		val = netsec_पढ़ो(priv, NETSEC_REG_NRM_RX_STATUS);
		netsec_ग_लिखो(priv, NETSEC_REG_NRM_RX_STATUS, val);
	पूर्ण

	spin_lock_irqsave(&priv->reglock, flags);
	netsec_ग_लिखो(priv, NETSEC_REG_INTEN_CLR, NETSEC_IRQ_RX | NETSEC_IRQ_TX);
	spin_unlock_irqrestore(&priv->reglock, flags);

	napi_schedule(&priv->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक netsec_netdev_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	pm_runसमय_get_sync(priv->dev);

	netsec_setup_tx_dring(priv);
	ret = netsec_setup_rx_dring(priv);
	अगर (ret) अणु
		netअगर_err(priv, probe, priv->ndev,
			  "%s: fail setup ring\n", __func__);
		जाओ err1;
	पूर्ण

	ret = request_irq(priv->ndev->irq, netsec_irq_handler,
			  IRQF_SHARED, "netsec", priv);
	अगर (ret) अणु
		netअगर_err(priv, drv, priv->ndev, "request_irq failed\n");
		जाओ err2;
	पूर्ण

	अगर (dev_of_node(priv->dev)) अणु
		अगर (!of_phy_connect(priv->ndev, priv->phy_np,
				    netsec_phy_adjust_link, 0,
				    priv->phy_पूर्णांकerface)) अणु
			netअगर_err(priv, link, priv->ndev, "missing PHY\n");
			ret = -ENODEV;
			जाओ err3;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = phy_connect_direct(priv->ndev, priv->phydev,
					 netsec_phy_adjust_link,
					 priv->phy_पूर्णांकerface);
		अगर (ret) अणु
			netअगर_err(priv, link, priv->ndev,
				  "phy_connect_direct() failed (%d)\n", ret);
			जाओ err3;
		पूर्ण
	पूर्ण

	phy_start(ndev->phydev);

	netsec_start_gmac(priv);
	napi_enable(&priv->napi);
	netअगर_start_queue(ndev);

	/* Enable TX+RX पूर्णांकr. */
	netsec_ग_लिखो(priv, NETSEC_REG_INTEN_SET, NETSEC_IRQ_RX | NETSEC_IRQ_TX);

	वापस 0;
err3:
	मुक्त_irq(priv->ndev->irq, priv);
err2:
	netsec_uninit_pkt_dring(priv, NETSEC_RING_RX);
err1:
	pm_runसमय_put_sync(priv->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक netsec_netdev_stop(काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;
	काष्ठा netsec_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(priv->ndev);
	dma_wmb();

	napi_disable(&priv->napi);

	netsec_ग_लिखो(priv, NETSEC_REG_INTEN_CLR, ~0);
	netsec_stop_gmac(priv);

	मुक्त_irq(priv->ndev->irq, priv);

	netsec_uninit_pkt_dring(priv, NETSEC_RING_TX);
	netsec_uninit_pkt_dring(priv, NETSEC_RING_RX);

	phy_stop(ndev->phydev);
	phy_disconnect(ndev->phydev);

	ret = netsec_reset_hardware(priv, false);

	pm_runसमय_put_sync(priv->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक netsec_netdev_init(काष्ठा net_device *ndev)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;
	u16 data;

	BUILD_BUG_ON_NOT_POWER_OF_2(DESC_NUM);

	ret = netsec_alloc_dring(priv, NETSEC_RING_TX);
	अगर (ret)
		वापस ret;

	ret = netsec_alloc_dring(priv, NETSEC_RING_RX);
	अगर (ret)
		जाओ err1;

	/* set phy घातer करोwn */
	data = netsec_phy_पढ़ो(priv->mii_bus, priv->phy_addr, MII_BMCR);
	netsec_phy_ग_लिखो(priv->mii_bus, priv->phy_addr, MII_BMCR,
			 data | BMCR_PDOWN);

	ret = netsec_reset_hardware(priv, true);
	अगर (ret)
		जाओ err2;

	/* Restore phy घातer state */
	netsec_phy_ग_लिखो(priv->mii_bus, priv->phy_addr, MII_BMCR, data);

	spin_lock_init(&priv->desc_ring[NETSEC_RING_TX].lock);
	spin_lock_init(&priv->desc_ring[NETSEC_RING_RX].lock);

	वापस 0;
err2:
	netsec_मुक्त_dring(priv, NETSEC_RING_RX);
err1:
	netsec_मुक्त_dring(priv, NETSEC_RING_TX);
	वापस ret;
पूर्ण

अटल व्योम netsec_netdev_uninit(काष्ठा net_device *ndev)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(ndev);

	netsec_मुक्त_dring(priv, NETSEC_RING_RX);
	netsec_मुक्त_dring(priv, NETSEC_RING_TX);
पूर्ण

अटल पूर्णांक netsec_netdev_set_features(काष्ठा net_device *ndev,
				      netdev_features_t features)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(ndev);

	priv->rx_cksum_offload_flag = !!(features & NETIF_F_RXCSUM);

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_xdp_xmit(काष्ठा net_device *ndev, पूर्णांक n,
			   काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(ndev);
	काष्ठा netsec_desc_ring *tx_ring = &priv->desc_ring[NETSEC_RING_TX];
	पूर्णांक i, nxmit = 0;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	spin_lock(&tx_ring->lock);
	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdpf = frames[i];
		पूर्णांक err;

		err = netsec_xdp_queue_one(priv, xdpf, true);
		अगर (err != NETSEC_XDP_TX)
			अवरोध;

		tx_ring->xdp_xmit++;
		nxmit++;
	पूर्ण
	spin_unlock(&tx_ring->lock);

	अगर (unlikely(flags & XDP_XMIT_FLUSH)) अणु
		netsec_xdp_ring_tx_db(priv, tx_ring->xdp_xmit);
		tx_ring->xdp_xmit = 0;
	पूर्ण

	वापस nxmit;
पूर्ण

अटल पूर्णांक netsec_xdp_setup(काष्ठा netsec_priv *priv, काष्ठा bpf_prog *prog,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा bpf_prog *old_prog;

	/* For now just support only the usual MTU sized frames */
	अगर (prog && dev->mtu > 1500) अणु
		NL_SET_ERR_MSG_MOD(extack, "Jumbo frames not supported on XDP");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (netअगर_running(dev))
		netsec_netdev_stop(dev);

	/* Detach old prog, अगर any */
	old_prog = xchg(&priv->xdp_prog, prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);

	अगर (netअगर_running(dev))
		netsec_netdev_खोलो(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_xdp(काष्ठा net_device *ndev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा netsec_priv *priv = netdev_priv(ndev);

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस netsec_xdp_setup(priv, xdp->prog, xdp->extack);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops netsec_netdev_ops = अणु
	.nकरो_init		= netsec_netdev_init,
	.nकरो_uninit		= netsec_netdev_uninit,
	.nकरो_खोलो		= netsec_netdev_खोलो,
	.nकरो_stop		= netsec_netdev_stop,
	.nकरो_start_xmit		= netsec_netdev_start_xmit,
	.nकरो_set_features	= netsec_netdev_set_features,
	.nकरो_set_mac_address    = eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= phy_करो_ioctl,
	.nकरो_xdp_xmit		= netsec_xdp_xmit,
	.nकरो_bpf		= netsec_xdp,
पूर्ण;

अटल पूर्णांक netsec_of_probe(काष्ठा platक्रमm_device *pdev,
			   काष्ठा netsec_priv *priv, u32 *phy_addr)
अणु
	पूर्णांक err;

	err = of_get_phy_mode(pdev->dev.of_node, &priv->phy_पूर्णांकerface);
	अगर (err) अणु
		dev_err(&pdev->dev, "missing required property 'phy-mode'\n");
		वापस err;
	पूर्ण

	priv->phy_np = of_parse_phandle(pdev->dev.of_node, "phy-handle", 0);
	अगर (!priv->phy_np) अणु
		dev_err(&pdev->dev, "missing required property 'phy-handle'\n");
		वापस -EINVAL;
	पूर्ण

	*phy_addr = of_mdio_parse_addr(&pdev->dev, priv->phy_np);

	priv->clk = devm_clk_get(&pdev->dev, शून्य); /* get by 'phy_ref_clk' */
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "phy_ref_clk not found\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण
	priv->freq = clk_get_rate(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_acpi_probe(काष्ठा platक्रमm_device *pdev,
			     काष्ठा netsec_priv *priv, u32 *phy_addr)
अणु
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_ACPI))
		वापस -ENODEV;

	/* ACPI प्रणालीs are assumed to configure the PHY in firmware, so
	 * there is really no need to discover the PHY mode from the DSDT.
	 * Since firmware is known to exist in the field that configures the
	 * PHY correctly but passes the wrong mode string in the phy-mode
	 * device property, we have no choice but to ignore it.
	 */
	priv->phy_पूर्णांकerface = PHY_INTERFACE_MODE_NA;

	ret = device_property_पढ़ो_u32(&pdev->dev, "phy-channel", phy_addr);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"missing required property 'phy-channel'\n");
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(&pdev->dev,
				       "socionext,phy-clock-frequency",
				       &priv->freq);
	अगर (ret)
		dev_err(&pdev->dev,
			"missing required property 'socionext,phy-clock-frequency'\n");
	वापस ret;
पूर्ण

अटल व्योम netsec_unरेजिस्टर_mdio(काष्ठा netsec_priv *priv)
अणु
	काष्ठा phy_device *phydev = priv->phydev;

	अगर (!dev_of_node(priv->dev) && phydev) अणु
		phy_device_हटाओ(phydev);
		phy_device_मुक्त(phydev);
	पूर्ण

	mdiobus_unरेजिस्टर(priv->mii_bus);
पूर्ण

अटल पूर्णांक netsec_रेजिस्टर_mdio(काष्ठा netsec_priv *priv, u32 phy_addr)
अणु
	काष्ठा mii_bus *bus;
	पूर्णांक ret;

	bus = devm_mdiobus_alloc(priv->dev);
	अगर (!bus)
		वापस -ENOMEM;

	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s", dev_name(priv->dev));
	bus->priv = priv;
	bus->name = "SNI NETSEC MDIO";
	bus->पढ़ो = netsec_phy_पढ़ो;
	bus->ग_लिखो = netsec_phy_ग_लिखो;
	bus->parent = priv->dev;
	priv->mii_bus = bus;

	अगर (dev_of_node(priv->dev)) अणु
		काष्ठा device_node *mdio_node, *parent = dev_of_node(priv->dev);

		mdio_node = of_get_child_by_name(parent, "mdio");
		अगर (mdio_node) अणु
			parent = mdio_node;
		पूर्ण अन्यथा अणु
			/* older f/w करोesn't populate the mdio subnode,
			 * allow relaxed upgrade of f/w in due समय.
			 */
			dev_info(priv->dev, "Upgrade f/w for mdio subnode!\n");
		पूर्ण

		ret = of_mdiobus_रेजिस्टर(bus, parent);
		of_node_put(mdio_node);

		अगर (ret) अणु
			dev_err(priv->dev, "mdiobus register err(%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Mask out all PHYs from स्वतः probing. */
		bus->phy_mask = ~0;
		ret = mdiobus_रेजिस्टर(bus);
		अगर (ret) अणु
			dev_err(priv->dev, "mdiobus register err(%d)\n", ret);
			वापस ret;
		पूर्ण

		priv->phydev = get_phy_device(bus, phy_addr, false);
		अगर (IS_ERR(priv->phydev)) अणु
			ret = PTR_ERR(priv->phydev);
			dev_err(priv->dev, "get_phy_device err(%d)\n", ret);
			priv->phydev = शून्य;
			वापस -ENODEV;
		पूर्ण

		ret = phy_device_रेजिस्टर(priv->phydev);
		अगर (ret) अणु
			mdiobus_unरेजिस्टर(bus);
			dev_err(priv->dev,
				"phy_device_register err(%d)\n", ret);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक netsec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *mmio_res, *eeprom_res, *irq_res;
	u8 *mac, macbuf[ETH_ALEN];
	काष्ठा netsec_priv *priv;
	u32 hw_ver, phy_addr = 0;
	काष्ठा net_device *ndev;
	पूर्णांक ret;

	mmio_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mmio_res) अणु
		dev_err(&pdev->dev, "No MMIO resource found.\n");
		वापस -ENODEV;
	पूर्ण

	eeprom_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!eeprom_res) अणु
		dev_info(&pdev->dev, "No EEPROM resource found.\n");
		वापस -ENODEV;
	पूर्ण

	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq_res) अणु
		dev_err(&pdev->dev, "No IRQ resource found.\n");
		वापस -ENODEV;
	पूर्ण

	ndev = alloc_etherdev(माप(*priv));
	अगर (!ndev)
		वापस -ENOMEM;

	priv = netdev_priv(ndev);

	spin_lock_init(&priv->reglock);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	platक्रमm_set_drvdata(pdev, priv);
	ndev->irq = irq_res->start;
	priv->dev = &pdev->dev;
	priv->ndev = ndev;

	priv->msg_enable = NETIF_MSG_TX_ERR | NETIF_MSG_HW | NETIF_MSG_DRV |
			   NETIF_MSG_LINK | NETIF_MSG_PROBE;

	priv->ioaddr = devm_ioremap(&pdev->dev, mmio_res->start,
				    resource_size(mmio_res));
	अगर (!priv->ioaddr) अणु
		dev_err(&pdev->dev, "devm_ioremap() failed\n");
		ret = -ENXIO;
		जाओ मुक्त_ndev;
	पूर्ण

	priv->eeprom_base = devm_ioremap(&pdev->dev, eeprom_res->start,
					 resource_size(eeprom_res));
	अगर (!priv->eeprom_base) अणु
		dev_err(&pdev->dev, "devm_ioremap() failed for EEPROM\n");
		ret = -ENXIO;
		जाओ मुक्त_ndev;
	पूर्ण

	mac = device_get_mac_address(&pdev->dev, macbuf, माप(macbuf));
	अगर (mac)
		ether_addr_copy(ndev->dev_addr, mac);

	अगर (priv->eeprom_base &&
	    (!mac || !is_valid_ether_addr(ndev->dev_addr))) अणु
		व्योम __iomem *macp = priv->eeprom_base +
					NETSEC_EEPROM_MAC_ADDRESS;

		ndev->dev_addr[0] = पढ़ोb(macp + 3);
		ndev->dev_addr[1] = पढ़ोb(macp + 2);
		ndev->dev_addr[2] = पढ़ोb(macp + 1);
		ndev->dev_addr[3] = पढ़ोb(macp + 0);
		ndev->dev_addr[4] = पढ़ोb(macp + 7);
		ndev->dev_addr[5] = पढ़ोb(macp + 6);
	पूर्ण

	अगर (!is_valid_ether_addr(ndev->dev_addr)) अणु
		dev_warn(&pdev->dev, "No MAC address found, using random\n");
		eth_hw_addr_अक्रमom(ndev);
	पूर्ण

	अगर (dev_of_node(&pdev->dev))
		ret = netsec_of_probe(pdev, priv, &phy_addr);
	अन्यथा
		ret = netsec_acpi_probe(pdev, priv, &phy_addr);
	अगर (ret)
		जाओ मुक्त_ndev;

	priv->phy_addr = phy_addr;

	अगर (!priv->freq) अणु
		dev_err(&pdev->dev, "missing PHY reference clock frequency\n");
		ret = -ENODEV;
		जाओ मुक्त_ndev;
	पूर्ण

	/* शेष क्रम throughput */
	priv->et_coalesce.rx_coalesce_usecs = 500;
	priv->et_coalesce.rx_max_coalesced_frames = 8;
	priv->et_coalesce.tx_coalesce_usecs = 500;
	priv->et_coalesce.tx_max_coalesced_frames = 8;

	ret = device_property_पढ़ो_u32(&pdev->dev, "max-frame-size",
				       &ndev->max_mtu);
	अगर (ret < 0)
		ndev->max_mtu = ETH_DATA_LEN;

	/* runसमय_pm coverage just क्रम probe, खोलो/बंद also cover it */
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	hw_ver = netsec_पढ़ो(priv, NETSEC_REG_F_TAIKI_VER);
	/* this driver only supports F_TAIKI style NETSEC */
	अगर (NETSEC_F_NETSEC_VER_MAJOR_NUM(hw_ver) !=
	    NETSEC_F_NETSEC_VER_MAJOR_NUM(NETSEC_REG_NETSEC_VER_F_TAIKI)) अणु
		ret = -ENODEV;
		जाओ pm_disable;
	पूर्ण

	dev_info(&pdev->dev, "hardware revision %d.%d\n",
		 hw_ver >> 16, hw_ver & 0xffff);

	netअगर_napi_add(ndev, &priv->napi, netsec_napi_poll, NAPI_POLL_WEIGHT);

	ndev->netdev_ops = &netsec_netdev_ops;
	ndev->ethtool_ops = &netsec_ethtool_ops;

	ndev->features |= NETIF_F_HIGHDMA | NETIF_F_RXCSUM | NETIF_F_GSO |
				NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	ndev->hw_features = ndev->features;

	priv->rx_cksum_offload_flag = true;

	ret = netsec_रेजिस्टर_mdio(priv, phy_addr);
	अगर (ret)
		जाओ unreg_napi;

	अगर (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(40)))
		dev_warn(&pdev->dev, "Failed to set DMA mask\n");

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		netअगर_err(priv, probe, ndev, "register_netdev() failed\n");
		जाओ unreg_mii;
	पूर्ण

	pm_runसमय_put_sync(&pdev->dev);
	वापस 0;

unreg_mii:
	netsec_unरेजिस्टर_mdio(priv);
unreg_napi:
	netअगर_napi_del(&priv->napi);
pm_disable:
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
मुक्त_ndev:
	मुक्त_netdev(ndev);
	dev_err(&pdev->dev, "init failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक netsec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा netsec_priv *priv = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_netdev(priv->ndev);

	netsec_unरेजिस्टर_mdio(priv);

	netअगर_napi_del(&priv->napi);

	pm_runसमय_disable(&pdev->dev);
	मुक्त_netdev(priv->ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक netsec_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा netsec_priv *priv = dev_get_drvdata(dev);

	netsec_ग_लिखो(priv, NETSEC_REG_CLK_EN, 0);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक netsec_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा netsec_priv *priv = dev_get_drvdata(dev);

	clk_prepare_enable(priv->clk);

	netsec_ग_लिखो(priv, NETSEC_REG_CLK_EN, NETSEC_CLK_EN_REG_DOM_D |
					       NETSEC_CLK_EN_REG_DOM_C |
					       NETSEC_CLK_EN_REG_DOM_G);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops netsec_pm_ops = अणु
	SET_RUNTIME_PM_OPS(netsec_runसमय_suspend, netsec_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id netsec_dt_ids[] = अणु
	अणु .compatible = "socionext,synquacer-netsec" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, netsec_dt_ids);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id netsec_acpi_ids[] = अणु
	अणु "SCX0001" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, netsec_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver netsec_driver = अणु
	.probe	= netsec_probe,
	.हटाओ	= netsec_हटाओ,
	.driver = अणु
		.name = "netsec",
		.pm = &netsec_pm_ops,
		.of_match_table = netsec_dt_ids,
		.acpi_match_table = ACPI_PTR(netsec_acpi_ids),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(netsec_driver);

MODULE_AUTHOR("Jassi Brar <jaswinder.singh@linaro.org>");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_DESCRIPTION("NETSEC Ethernet driver");
MODULE_LICENSE("GPL");
