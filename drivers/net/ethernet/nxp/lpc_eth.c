<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/ethernet/nxp/lpc_eth.c
 *
 * Author: Kevin Wells <kevin.wells@nxp.com>
 *
 * Copyright (C) 2010 NXP Semiconductors
 * Copyright (C) 2012 Roland Stigge <stigge@antcom.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/soc/nxp/lpc32xx-misc.h>

#घोषणा MODNAME "lpc-eth"
#घोषणा DRV_VERSION "1.00"

#घोषणा ENET_MAXF_SIZE 1536
#घोषणा ENET_RX_DESC 48
#घोषणा ENET_TX_DESC 16

#घोषणा NAPI_WEIGHT 16

/*
 * Ethernet MAC controller Register offsets
 */
#घोषणा LPC_ENET_MAC1(x)			(x + 0x000)
#घोषणा LPC_ENET_MAC2(x)			(x + 0x004)
#घोषणा LPC_ENET_IPGT(x)			(x + 0x008)
#घोषणा LPC_ENET_IPGR(x)			(x + 0x00C)
#घोषणा LPC_ENET_CLRT(x)			(x + 0x010)
#घोषणा LPC_ENET_MAXF(x)			(x + 0x014)
#घोषणा LPC_ENET_SUPP(x)			(x + 0x018)
#घोषणा LPC_ENET_TEST(x)			(x + 0x01C)
#घोषणा LPC_ENET_MCFG(x)			(x + 0x020)
#घोषणा LPC_ENET_MCMD(x)			(x + 0x024)
#घोषणा LPC_ENET_MADR(x)			(x + 0x028)
#घोषणा LPC_ENET_MWTD(x)			(x + 0x02C)
#घोषणा LPC_ENET_MRDD(x)			(x + 0x030)
#घोषणा LPC_ENET_MIND(x)			(x + 0x034)
#घोषणा LPC_ENET_SA0(x)				(x + 0x040)
#घोषणा LPC_ENET_SA1(x)				(x + 0x044)
#घोषणा LPC_ENET_SA2(x)				(x + 0x048)
#घोषणा LPC_ENET_COMMAND(x)			(x + 0x100)
#घोषणा LPC_ENET_STATUS(x)			(x + 0x104)
#घोषणा LPC_ENET_RXDESCRIPTOR(x)		(x + 0x108)
#घोषणा LPC_ENET_RXSTATUS(x)			(x + 0x10C)
#घोषणा LPC_ENET_RXDESCRIPTORNUMBER(x)		(x + 0x110)
#घोषणा LPC_ENET_RXPRODUCEINDEX(x)		(x + 0x114)
#घोषणा LPC_ENET_RXCONSUMEINDEX(x)		(x + 0x118)
#घोषणा LPC_ENET_TXDESCRIPTOR(x)		(x + 0x11C)
#घोषणा LPC_ENET_TXSTATUS(x)			(x + 0x120)
#घोषणा LPC_ENET_TXDESCRIPTORNUMBER(x)		(x + 0x124)
#घोषणा LPC_ENET_TXPRODUCEINDEX(x)		(x + 0x128)
#घोषणा LPC_ENET_TXCONSUMEINDEX(x)		(x + 0x12C)
#घोषणा LPC_ENET_TSV0(x)			(x + 0x158)
#घोषणा LPC_ENET_TSV1(x)			(x + 0x15C)
#घोषणा LPC_ENET_RSV(x)				(x + 0x160)
#घोषणा LPC_ENET_FLOWCONTROLCOUNTER(x)		(x + 0x170)
#घोषणा LPC_ENET_FLOWCONTROLSTATUS(x)		(x + 0x174)
#घोषणा LPC_ENET_RXFILTER_CTRL(x)		(x + 0x200)
#घोषणा LPC_ENET_RXFILTERWOLSTATUS(x)		(x + 0x204)
#घोषणा LPC_ENET_RXFILTERWOLCLEAR(x)		(x + 0x208)
#घोषणा LPC_ENET_HASHFILTERL(x)			(x + 0x210)
#घोषणा LPC_ENET_HASHFILTERH(x)			(x + 0x214)
#घोषणा LPC_ENET_INTSTATUS(x)			(x + 0xFE0)
#घोषणा LPC_ENET_INTENABLE(x)			(x + 0xFE4)
#घोषणा LPC_ENET_INTCLEAR(x)			(x + 0xFE8)
#घोषणा LPC_ENET_INTSET(x)			(x + 0xFEC)
#घोषणा LPC_ENET_POWERDOWN(x)			(x + 0xFF4)

/*
 * mac1 रेजिस्टर definitions
 */
#घोषणा LPC_MAC1_RECV_ENABLE			(1 << 0)
#घोषणा LPC_MAC1_PASS_ALL_RX_FRAMES		(1 << 1)
#घोषणा LPC_MAC1_RX_FLOW_CONTROL		(1 << 2)
#घोषणा LPC_MAC1_TX_FLOW_CONTROL		(1 << 3)
#घोषणा LPC_MAC1_LOOPBACK			(1 << 4)
#घोषणा LPC_MAC1_RESET_TX			(1 << 8)
#घोषणा LPC_MAC1_RESET_MCS_TX			(1 << 9)
#घोषणा LPC_MAC1_RESET_RX			(1 << 10)
#घोषणा LPC_MAC1_RESET_MCS_RX			(1 << 11)
#घोषणा LPC_MAC1_SIMULATION_RESET		(1 << 14)
#घोषणा LPC_MAC1_SOFT_RESET			(1 << 15)

/*
 * mac2 रेजिस्टर definitions
 */
#घोषणा LPC_MAC2_FULL_DUPLEX			(1 << 0)
#घोषणा LPC_MAC2_FRAME_LENGTH_CHECKING		(1 << 1)
#घोषणा LPC_MAC2_HUGH_LENGTH_CHECKING		(1 << 2)
#घोषणा LPC_MAC2_DELAYED_CRC			(1 << 3)
#घोषणा LPC_MAC2_CRC_ENABLE			(1 << 4)
#घोषणा LPC_MAC2_PAD_CRC_ENABLE			(1 << 5)
#घोषणा LPC_MAC2_VLAN_PAD_ENABLE		(1 << 6)
#घोषणा LPC_MAC2_AUTO_DETECT_PAD_ENABLE		(1 << 7)
#घोषणा LPC_MAC2_PURE_PREAMBLE_ENFORCEMENT	(1 << 8)
#घोषणा LPC_MAC2_LONG_PREAMBLE_ENFORCEMENT	(1 << 9)
#घोषणा LPC_MAC2_NO_BACKOFF			(1 << 12)
#घोषणा LPC_MAC2_BACK_PRESSURE			(1 << 13)
#घोषणा LPC_MAC2_EXCESS_DEFER			(1 << 14)

/*
 * ipgt रेजिस्टर definitions
 */
#घोषणा LPC_IPGT_LOAD(n)			((n) & 0x7F)

/*
 * ipgr रेजिस्टर definitions
 */
#घोषणा LPC_IPGR_LOAD_PART2(n)			((n) & 0x7F)
#घोषणा LPC_IPGR_LOAD_PART1(n)			(((n) & 0x7F) << 8)

/*
 * clrt रेजिस्टर definitions
 */
#घोषणा LPC_CLRT_LOAD_RETRY_MAX(n)		((n) & 0xF)
#घोषणा LPC_CLRT_LOAD_COLLISION_WINDOW(n)	(((n) & 0x3F) << 8)

/*
 * maxf रेजिस्टर definitions
 */
#घोषणा LPC_MAXF_LOAD_MAX_FRAME_LEN(n)		((n) & 0xFFFF)

/*
 * supp रेजिस्टर definitions
 */
#घोषणा LPC_SUPP_SPEED				(1 << 8)
#घोषणा LPC_SUPP_RESET_RMII			(1 << 11)

/*
 * test रेजिस्टर definitions
 */
#घोषणा LPC_TEST_SHORTCUT_PAUSE_QUANTA		(1 << 0)
#घोषणा LPC_TEST_PAUSE				(1 << 1)
#घोषणा LPC_TEST_BACKPRESSURE			(1 << 2)

/*
 * mcfg रेजिस्टर definitions
 */
#घोषणा LPC_MCFG_SCAN_INCREMENT			(1 << 0)
#घोषणा LPC_MCFG_SUPPRESS_PREAMBLE		(1 << 1)
#घोषणा LPC_MCFG_CLOCK_SELECT(n)		(((n) & 0x7) << 2)
#घोषणा LPC_MCFG_CLOCK_HOST_DIV_4		0
#घोषणा LPC_MCFG_CLOCK_HOST_DIV_6		2
#घोषणा LPC_MCFG_CLOCK_HOST_DIV_8		3
#घोषणा LPC_MCFG_CLOCK_HOST_DIV_10		4
#घोषणा LPC_MCFG_CLOCK_HOST_DIV_14		5
#घोषणा LPC_MCFG_CLOCK_HOST_DIV_20		6
#घोषणा LPC_MCFG_CLOCK_HOST_DIV_28		7
#घोषणा LPC_MCFG_RESET_MII_MGMT			(1 << 15)

/*
 * mcmd रेजिस्टर definitions
 */
#घोषणा LPC_MCMD_READ				(1 << 0)
#घोषणा LPC_MCMD_SCAN				(1 << 1)

/*
 * madr रेजिस्टर definitions
 */
#घोषणा LPC_MADR_REGISTER_ADDRESS(n)		((n) & 0x1F)
#घोषणा LPC_MADR_PHY_0ADDRESS(n)		(((n) & 0x1F) << 8)

/*
 * mwtd रेजिस्टर definitions
 */
#घोषणा LPC_MWDT_WRITE(n)			((n) & 0xFFFF)

/*
 * mrdd रेजिस्टर definitions
 */
#घोषणा LPC_MRDD_READ_MASK			0xFFFF

/*
 * mind रेजिस्टर definitions
 */
#घोषणा LPC_MIND_BUSY				(1 << 0)
#घोषणा LPC_MIND_SCANNING			(1 << 1)
#घोषणा LPC_MIND_NOT_VALID			(1 << 2)
#घोषणा LPC_MIND_MII_LINK_FAIL			(1 << 3)

/*
 * command रेजिस्टर definitions
 */
#घोषणा LPC_COMMAND_RXENABLE			(1 << 0)
#घोषणा LPC_COMMAND_TXENABLE			(1 << 1)
#घोषणा LPC_COMMAND_REG_RESET			(1 << 3)
#घोषणा LPC_COMMAND_TXRESET			(1 << 4)
#घोषणा LPC_COMMAND_RXRESET			(1 << 5)
#घोषणा LPC_COMMAND_PASSRUNTFRAME		(1 << 6)
#घोषणा LPC_COMMAND_PASSRXFILTER		(1 << 7)
#घोषणा LPC_COMMAND_TXFLOWCONTROL		(1 << 8)
#घोषणा LPC_COMMAND_RMII			(1 << 9)
#घोषणा LPC_COMMAND_FULLDUPLEX			(1 << 10)

/*
 * status रेजिस्टर definitions
 */
#घोषणा LPC_STATUS_RXACTIVE			(1 << 0)
#घोषणा LPC_STATUS_TXACTIVE			(1 << 1)

/*
 * tsv0 रेजिस्टर definitions
 */
#घोषणा LPC_TSV0_CRC_ERROR			(1 << 0)
#घोषणा LPC_TSV0_LENGTH_CHECK_ERROR		(1 << 1)
#घोषणा LPC_TSV0_LENGTH_OUT_OF_RANGE		(1 << 2)
#घोषणा LPC_TSV0_DONE				(1 << 3)
#घोषणा LPC_TSV0_MULTICAST			(1 << 4)
#घोषणा LPC_TSV0_BROADCAST			(1 << 5)
#घोषणा LPC_TSV0_PACKET_DEFER			(1 << 6)
#घोषणा LPC_TSV0_ESCESSIVE_DEFER		(1 << 7)
#घोषणा LPC_TSV0_ESCESSIVE_COLLISION		(1 << 8)
#घोषणा LPC_TSV0_LATE_COLLISION			(1 << 9)
#घोषणा LPC_TSV0_GIANT				(1 << 10)
#घोषणा LPC_TSV0_UNDERRUN			(1 << 11)
#घोषणा LPC_TSV0_TOTAL_BYTES(n)			(((n) >> 12) & 0xFFFF)
#घोषणा LPC_TSV0_CONTROL_FRAME			(1 << 28)
#घोषणा LPC_TSV0_PAUSE				(1 << 29)
#घोषणा LPC_TSV0_BACKPRESSURE			(1 << 30)
#घोषणा LPC_TSV0_VLAN				(1 << 31)

/*
 * tsv1 रेजिस्टर definitions
 */
#घोषणा LPC_TSV1_TRANSMIT_BYTE_COUNT(n)		((n) & 0xFFFF)
#घोषणा LPC_TSV1_COLLISION_COUNT(n)		(((n) >> 16) & 0xF)

/*
 * rsv रेजिस्टर definitions
 */
#घोषणा LPC_RSV_RECEIVED_BYTE_COUNT(n)		((n) & 0xFFFF)
#घोषणा LPC_RSV_RXDV_EVENT_IGNORED		(1 << 16)
#घोषणा LPC_RSV_RXDV_EVENT_PREVIOUSLY_SEEN	(1 << 17)
#घोषणा LPC_RSV_CARRIER_EVNT_PREVIOUS_SEEN	(1 << 18)
#घोषणा LPC_RSV_RECEIVE_CODE_VIOLATION		(1 << 19)
#घोषणा LPC_RSV_CRC_ERROR			(1 << 20)
#घोषणा LPC_RSV_LENGTH_CHECK_ERROR		(1 << 21)
#घोषणा LPC_RSV_LENGTH_OUT_OF_RANGE		(1 << 22)
#घोषणा LPC_RSV_RECEIVE_OK			(1 << 23)
#घोषणा LPC_RSV_MULTICAST			(1 << 24)
#घोषणा LPC_RSV_BROADCAST			(1 << 25)
#घोषणा LPC_RSV_DRIBBLE_NIBBLE			(1 << 26)
#घोषणा LPC_RSV_CONTROL_FRAME			(1 << 27)
#घोषणा LPC_RSV_PAUSE				(1 << 28)
#घोषणा LPC_RSV_UNSUPPORTED_OPCODE		(1 << 29)
#घोषणा LPC_RSV_VLAN				(1 << 30)

/*
 * flowcontrolcounter रेजिस्टर definitions
 */
#घोषणा LPC_FCCR_MIRRORCOUNTER(n)		((n) & 0xFFFF)
#घोषणा LPC_FCCR_PAUSETIMER(n)			(((n) >> 16) & 0xFFFF)

/*
 * flowcontrolstatus रेजिस्टर definitions
 */
#घोषणा LPC_FCCR_MIRRORCOUNTERCURRENT(n)	((n) & 0xFFFF)

/*
 * rxfilterctrl, rxfilterwolstatus, and rxfilterwolclear shared
 * रेजिस्टर definitions
 */
#घोषणा LPC_RXFLTRW_ACCEPTUNICAST		(1 << 0)
#घोषणा LPC_RXFLTRW_ACCEPTUBROADCAST		(1 << 1)
#घोषणा LPC_RXFLTRW_ACCEPTUMULTICAST		(1 << 2)
#घोषणा LPC_RXFLTRW_ACCEPTUNICASTHASH		(1 << 3)
#घोषणा LPC_RXFLTRW_ACCEPTUMULTICASTHASH	(1 << 4)
#घोषणा LPC_RXFLTRW_ACCEPTPERFECT		(1 << 5)

/*
 * rxfilterctrl रेजिस्टर definitions
 */
#घोषणा LPC_RXFLTRWSTS_MAGICPACKETENWOL		(1 << 12)
#घोषणा LPC_RXFLTRWSTS_RXFILTERENWOL		(1 << 13)

/*
 * rxfilterwolstatus/rxfilterwolclear रेजिस्टर definitions
 */
#घोषणा LPC_RXFLTRWSTS_RXFILTERWOL		(1 << 7)
#घोषणा LPC_RXFLTRWSTS_MAGICPACKETWOL		(1 << 8)

/*
 * पूर्णांकstatus, पूर्णांकenable, पूर्णांकclear, and Intset shared रेजिस्टर
 * definitions
 */
#घोषणा LPC_MACINT_RXOVERRUNINTEN		(1 << 0)
#घोषणा LPC_MACINT_RXERRORONINT			(1 << 1)
#घोषणा LPC_MACINT_RXFINISHEDINTEN		(1 << 2)
#घोषणा LPC_MACINT_RXDONEINTEN			(1 << 3)
#घोषणा LPC_MACINT_TXUNDERRUNINTEN		(1 << 4)
#घोषणा LPC_MACINT_TXERRORINTEN			(1 << 5)
#घोषणा LPC_MACINT_TXFINISHEDINTEN		(1 << 6)
#घोषणा LPC_MACINT_TXDONEINTEN			(1 << 7)
#घोषणा LPC_MACINT_SOFTINTEN			(1 << 12)
#घोषणा LPC_MACINT_WAKEUPINTEN			(1 << 13)

/*
 * घातerकरोwn रेजिस्टर definitions
 */
#घोषणा LPC_POWERDOWN_MACAHB			(1 << 31)

अटल phy_पूर्णांकerface_t lpc_phy_पूर्णांकerface_mode(काष्ठा device *dev)
अणु
	अगर (dev && dev->of_node) अणु
		स्थिर अक्षर *mode = of_get_property(dev->of_node,
						   "phy-mode", शून्य);
		अगर (mode && !म_भेद(mode, "mii"))
			वापस PHY_INTERFACE_MODE_MII;
	पूर्ण
	वापस PHY_INTERFACE_MODE_RMII;
पूर्ण

अटल bool use_iram_क्रम_net(काष्ठा device *dev)
अणु
	अगर (dev && dev->of_node)
		वापस of_property_पढ़ो_bool(dev->of_node, "use-iram");
	वापस false;
पूर्ण

/* Receive Status inक्रमmation word */
#घोषणा RXSTATUS_SIZE			0x000007FF
#घोषणा RXSTATUS_CONTROL		(1 << 18)
#घोषणा RXSTATUS_VLAN			(1 << 19)
#घोषणा RXSTATUS_FILTER			(1 << 20)
#घोषणा RXSTATUS_MULTICAST		(1 << 21)
#घोषणा RXSTATUS_BROADCAST		(1 << 22)
#घोषणा RXSTATUS_CRC			(1 << 23)
#घोषणा RXSTATUS_SYMBOL			(1 << 24)
#घोषणा RXSTATUS_LENGTH			(1 << 25)
#घोषणा RXSTATUS_RANGE			(1 << 26)
#घोषणा RXSTATUS_ALIGN			(1 << 27)
#घोषणा RXSTATUS_OVERRUN		(1 << 28)
#घोषणा RXSTATUS_NODESC			(1 << 29)
#घोषणा RXSTATUS_LAST			(1 << 30)
#घोषणा RXSTATUS_ERROR			(1 << 31)

#घोषणा RXSTATUS_STATUS_ERROR \
	(RXSTATUS_NODESC | RXSTATUS_OVERRUN | RXSTATUS_ALIGN | \
	 RXSTATUS_RANGE | RXSTATUS_LENGTH | RXSTATUS_SYMBOL | RXSTATUS_CRC)

/* Receive Descriptor control word */
#घोषणा RXDESC_CONTROL_SIZE		0x000007FF
#घोषणा RXDESC_CONTROL_INT		(1 << 31)

/* Transmit Status inक्रमmation word */
#घोषणा TXSTATUS_COLLISIONS_GET(x)	(((x) >> 21) & 0xF)
#घोषणा TXSTATUS_DEFER			(1 << 25)
#घोषणा TXSTATUS_EXCESSDEFER		(1 << 26)
#घोषणा TXSTATUS_EXCESSCOLL		(1 << 27)
#घोषणा TXSTATUS_LATECOLL		(1 << 28)
#घोषणा TXSTATUS_UNDERRUN		(1 << 29)
#घोषणा TXSTATUS_NODESC			(1 << 30)
#घोषणा TXSTATUS_ERROR			(1 << 31)

/* Transmit Descriptor control word */
#घोषणा TXDESC_CONTROL_SIZE		0x000007FF
#घोषणा TXDESC_CONTROL_OVERRIDE		(1 << 26)
#घोषणा TXDESC_CONTROL_HUGE		(1 << 27)
#घोषणा TXDESC_CONTROL_PAD		(1 << 28)
#घोषणा TXDESC_CONTROL_CRC		(1 << 29)
#घोषणा TXDESC_CONTROL_LAST		(1 << 30)
#घोषणा TXDESC_CONTROL_INT		(1 << 31)

/*
 * Structure of a TX/RX descriptors and RX status
 */
काष्ठा txrx_desc_t अणु
	__le32 packet;
	__le32 control;
पूर्ण;
काष्ठा rx_status_t अणु
	__le32 statusinfo;
	__le32 statushashcrc;
पूर्ण;

/*
 * Device driver data काष्ठाure
 */
काष्ठा netdata_local अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा net_device	*ndev;
	काष्ठा device_node	*phy_node;
	spinlock_t		lock;
	व्योम __iomem		*net_base;
	u32			msg_enable;
	अचिन्हित पूर्णांक		skblen[ENET_TX_DESC];
	अचिन्हित पूर्णांक		last_tx_idx;
	अचिन्हित पूर्णांक		num_used_tx_buffs;
	काष्ठा mii_bus		*mii_bus;
	काष्ठा clk		*clk;
	dma_addr_t		dma_buff_base_p;
	व्योम			*dma_buff_base_v;
	माप_प्रकार			dma_buff_size;
	काष्ठा txrx_desc_t	*tx_desc_v;
	u32			*tx_stat_v;
	व्योम			*tx_buff_v;
	काष्ठा txrx_desc_t	*rx_desc_v;
	काष्ठा rx_status_t	*rx_stat_v;
	व्योम			*rx_buff_v;
	पूर्णांक			link;
	पूर्णांक			speed;
	पूर्णांक			duplex;
	काष्ठा napi_काष्ठा	napi;
पूर्ण;

/*
 * MAC support functions
 */
अटल व्योम __lpc_set_mac(काष्ठा netdata_local *pldat, u8 *mac)
अणु
	u32 पंचांगp;

	/* Set station address */
	पंचांगp = mac[0] | ((u32)mac[1] << 8);
	ग_लिखोl(पंचांगp, LPC_ENET_SA2(pldat->net_base));
	पंचांगp = mac[2] | ((u32)mac[3] << 8);
	ग_लिखोl(पंचांगp, LPC_ENET_SA1(pldat->net_base));
	पंचांगp = mac[4] | ((u32)mac[5] << 8);
	ग_लिखोl(पंचांगp, LPC_ENET_SA0(pldat->net_base));

	netdev_dbg(pldat->ndev, "Ethernet MAC address %pM\n", mac);
पूर्ण

अटल व्योम __lpc_get_mac(काष्ठा netdata_local *pldat, u8 *mac)
अणु
	u32 पंचांगp;

	/* Get station address */
	पंचांगp = पढ़ोl(LPC_ENET_SA2(pldat->net_base));
	mac[0] = पंचांगp & 0xFF;
	mac[1] = पंचांगp >> 8;
	पंचांगp = पढ़ोl(LPC_ENET_SA1(pldat->net_base));
	mac[2] = पंचांगp & 0xFF;
	mac[3] = पंचांगp >> 8;
	पंचांगp = पढ़ोl(LPC_ENET_SA0(pldat->net_base));
	mac[4] = पंचांगp & 0xFF;
	mac[5] = पंचांगp >> 8;
पूर्ण

अटल व्योम __lpc_params_setup(काष्ठा netdata_local *pldat)
अणु
	u32 पंचांगp;

	अगर (pldat->duplex == DUPLEX_FULL) अणु
		पंचांगp = पढ़ोl(LPC_ENET_MAC2(pldat->net_base));
		पंचांगp |= LPC_MAC2_FULL_DUPLEX;
		ग_लिखोl(पंचांगp, LPC_ENET_MAC2(pldat->net_base));
		पंचांगp = पढ़ोl(LPC_ENET_COMMAND(pldat->net_base));
		पंचांगp |= LPC_COMMAND_FULLDUPLEX;
		ग_लिखोl(पंचांगp, LPC_ENET_COMMAND(pldat->net_base));
		ग_लिखोl(LPC_IPGT_LOAD(0x15), LPC_ENET_IPGT(pldat->net_base));
	पूर्ण अन्यथा अणु
		पंचांगp = पढ़ोl(LPC_ENET_MAC2(pldat->net_base));
		पंचांगp &= ~LPC_MAC2_FULL_DUPLEX;
		ग_लिखोl(पंचांगp, LPC_ENET_MAC2(pldat->net_base));
		पंचांगp = पढ़ोl(LPC_ENET_COMMAND(pldat->net_base));
		पंचांगp &= ~LPC_COMMAND_FULLDUPLEX;
		ग_लिखोl(पंचांगp, LPC_ENET_COMMAND(pldat->net_base));
		ग_लिखोl(LPC_IPGT_LOAD(0x12), LPC_ENET_IPGT(pldat->net_base));
	पूर्ण

	अगर (pldat->speed == SPEED_100)
		ग_लिखोl(LPC_SUPP_SPEED, LPC_ENET_SUPP(pldat->net_base));
	अन्यथा
		ग_लिखोl(0, LPC_ENET_SUPP(pldat->net_base));
पूर्ण

अटल व्योम __lpc_eth_reset(काष्ठा netdata_local *pldat)
अणु
	/* Reset all MAC logic */
	ग_लिखोl((LPC_MAC1_RESET_TX | LPC_MAC1_RESET_MCS_TX | LPC_MAC1_RESET_RX |
		LPC_MAC1_RESET_MCS_RX | LPC_MAC1_SIMULATION_RESET |
		LPC_MAC1_SOFT_RESET), LPC_ENET_MAC1(pldat->net_base));
	ग_लिखोl((LPC_COMMAND_REG_RESET | LPC_COMMAND_TXRESET |
		LPC_COMMAND_RXRESET), LPC_ENET_COMMAND(pldat->net_base));
पूर्ण

अटल पूर्णांक __lpc_mii_mngt_reset(काष्ठा netdata_local *pldat)
अणु
	/* Reset MII management hardware */
	ग_लिखोl(LPC_MCFG_RESET_MII_MGMT, LPC_ENET_MCFG(pldat->net_base));

	/* Setup MII घड़ी to slowest rate with a /28 भागider */
	ग_लिखोl(LPC_MCFG_CLOCK_SELECT(LPC_MCFG_CLOCK_HOST_DIV_28),
	       LPC_ENET_MCFG(pldat->net_base));

	वापस 0;
पूर्ण

अटल अंतरभूत phys_addr_t __va_to_pa(व्योम *addr, काष्ठा netdata_local *pldat)
अणु
	phys_addr_t phaddr;

	phaddr = addr - pldat->dma_buff_base_v;
	phaddr += pldat->dma_buff_base_p;

	वापस phaddr;
पूर्ण

अटल व्योम lpc_eth_enable_पूर्णांक(व्योम __iomem *regbase)
अणु
	ग_लिखोl((LPC_MACINT_RXDONEINTEN | LPC_MACINT_TXDONEINTEN),
	       LPC_ENET_INTENABLE(regbase));
पूर्ण

अटल व्योम lpc_eth_disable_पूर्णांक(व्योम __iomem *regbase)
अणु
	ग_लिखोl(0, LPC_ENET_INTENABLE(regbase));
पूर्ण

/* Setup TX/RX descriptors */
अटल व्योम __lpc_txrx_desc_setup(काष्ठा netdata_local *pldat)
अणु
	u32 *ptxstat;
	व्योम *tbuff;
	पूर्णांक i;
	काष्ठा txrx_desc_t *ptxrxdesc;
	काष्ठा rx_status_t *prxstat;

	tbuff = PTR_ALIGN(pldat->dma_buff_base_v, 16);

	/* Setup TX descriptors, status, and buffers */
	pldat->tx_desc_v = tbuff;
	tbuff += माप(काष्ठा txrx_desc_t) * ENET_TX_DESC;

	pldat->tx_stat_v = tbuff;
	tbuff += माप(u32) * ENET_TX_DESC;

	tbuff = PTR_ALIGN(tbuff, 16);
	pldat->tx_buff_v = tbuff;
	tbuff += ENET_MAXF_SIZE * ENET_TX_DESC;

	/* Setup RX descriptors, status, and buffers */
	pldat->rx_desc_v = tbuff;
	tbuff += माप(काष्ठा txrx_desc_t) * ENET_RX_DESC;

	tbuff = PTR_ALIGN(tbuff, 16);
	pldat->rx_stat_v = tbuff;
	tbuff += माप(काष्ठा rx_status_t) * ENET_RX_DESC;

	tbuff = PTR_ALIGN(tbuff, 16);
	pldat->rx_buff_v = tbuff;
	tbuff += ENET_MAXF_SIZE * ENET_RX_DESC;

	/* Map the TX descriptors to the TX buffers in hardware */
	क्रम (i = 0; i < ENET_TX_DESC; i++) अणु
		ptxstat = &pldat->tx_stat_v[i];
		ptxrxdesc = &pldat->tx_desc_v[i];

		ptxrxdesc->packet = __va_to_pa(
				pldat->tx_buff_v + i * ENET_MAXF_SIZE, pldat);
		ptxrxdesc->control = 0;
		*ptxstat = 0;
	पूर्ण

	/* Map the RX descriptors to the RX buffers in hardware */
	क्रम (i = 0; i < ENET_RX_DESC; i++) अणु
		prxstat = &pldat->rx_stat_v[i];
		ptxrxdesc = &pldat->rx_desc_v[i];

		ptxrxdesc->packet = __va_to_pa(
				pldat->rx_buff_v + i * ENET_MAXF_SIZE, pldat);
		ptxrxdesc->control = RXDESC_CONTROL_INT | (ENET_MAXF_SIZE - 1);
		prxstat->statusinfo = 0;
		prxstat->statushashcrc = 0;
	पूर्ण

	/* Setup base addresses in hardware to poपूर्णांक to buffers and
	 * descriptors
	 */
	ग_लिखोl((ENET_TX_DESC - 1),
	       LPC_ENET_TXDESCRIPTORNUMBER(pldat->net_base));
	ग_लिखोl(__va_to_pa(pldat->tx_desc_v, pldat),
	       LPC_ENET_TXDESCRIPTOR(pldat->net_base));
	ग_लिखोl(__va_to_pa(pldat->tx_stat_v, pldat),
	       LPC_ENET_TXSTATUS(pldat->net_base));
	ग_लिखोl((ENET_RX_DESC - 1),
	       LPC_ENET_RXDESCRIPTORNUMBER(pldat->net_base));
	ग_लिखोl(__va_to_pa(pldat->rx_desc_v, pldat),
	       LPC_ENET_RXDESCRIPTOR(pldat->net_base));
	ग_लिखोl(__va_to_pa(pldat->rx_stat_v, pldat),
	       LPC_ENET_RXSTATUS(pldat->net_base));
पूर्ण

अटल व्योम __lpc_eth_init(काष्ठा netdata_local *pldat)
अणु
	u32 पंचांगp;

	/* Disable controller and reset */
	पंचांगp = पढ़ोl(LPC_ENET_COMMAND(pldat->net_base));
	पंचांगp &= ~LPC_COMMAND_RXENABLE | LPC_COMMAND_TXENABLE;
	ग_लिखोl(पंचांगp, LPC_ENET_COMMAND(pldat->net_base));
	पंचांगp = पढ़ोl(LPC_ENET_MAC1(pldat->net_base));
	पंचांगp &= ~LPC_MAC1_RECV_ENABLE;
	ग_लिखोl(पंचांगp, LPC_ENET_MAC1(pldat->net_base));

	/* Initial MAC setup */
	ग_लिखोl(LPC_MAC1_PASS_ALL_RX_FRAMES, LPC_ENET_MAC1(pldat->net_base));
	ग_लिखोl((LPC_MAC2_PAD_CRC_ENABLE | LPC_MAC2_CRC_ENABLE),
	       LPC_ENET_MAC2(pldat->net_base));
	ग_लिखोl(ENET_MAXF_SIZE, LPC_ENET_MAXF(pldat->net_base));

	/* Collision winकरोw, gap */
	ग_लिखोl((LPC_CLRT_LOAD_RETRY_MAX(0xF) |
		LPC_CLRT_LOAD_COLLISION_WINDOW(0x37)),
	       LPC_ENET_CLRT(pldat->net_base));
	ग_लिखोl(LPC_IPGR_LOAD_PART2(0x12), LPC_ENET_IPGR(pldat->net_base));

	अगर (lpc_phy_पूर्णांकerface_mode(&pldat->pdev->dev) == PHY_INTERFACE_MODE_MII)
		ग_लिखोl(LPC_COMMAND_PASSRUNTFRAME,
		       LPC_ENET_COMMAND(pldat->net_base));
	अन्यथा अणु
		ग_लिखोl((LPC_COMMAND_PASSRUNTFRAME | LPC_COMMAND_RMII),
		       LPC_ENET_COMMAND(pldat->net_base));
		ग_लिखोl(LPC_SUPP_RESET_RMII, LPC_ENET_SUPP(pldat->net_base));
	पूर्ण

	__lpc_params_setup(pldat);

	/* Setup TX and RX descriptors */
	__lpc_txrx_desc_setup(pldat);

	/* Setup packet filtering */
	ग_लिखोl((LPC_RXFLTRW_ACCEPTUBROADCAST | LPC_RXFLTRW_ACCEPTPERFECT),
	       LPC_ENET_RXFILTER_CTRL(pldat->net_base));

	/* Get the next TX buffer output index */
	pldat->num_used_tx_buffs = 0;
	pldat->last_tx_idx =
		पढ़ोl(LPC_ENET_TXCONSUMEINDEX(pldat->net_base));

	/* Clear and enable पूर्णांकerrupts */
	ग_लिखोl(0xFFFF, LPC_ENET_INTCLEAR(pldat->net_base));
	smp_wmb();
	lpc_eth_enable_पूर्णांक(pldat->net_base);

	/* Enable controller */
	पंचांगp = पढ़ोl(LPC_ENET_COMMAND(pldat->net_base));
	पंचांगp |= LPC_COMMAND_RXENABLE | LPC_COMMAND_TXENABLE;
	ग_लिखोl(पंचांगp, LPC_ENET_COMMAND(pldat->net_base));
	पंचांगp = पढ़ोl(LPC_ENET_MAC1(pldat->net_base));
	पंचांगp |= LPC_MAC1_RECV_ENABLE;
	ग_लिखोl(पंचांगp, LPC_ENET_MAC1(pldat->net_base));
पूर्ण

अटल व्योम __lpc_eth_shutकरोwn(काष्ठा netdata_local *pldat)
अणु
	/* Reset ethernet and घातer करोwn PHY */
	__lpc_eth_reset(pldat);
	ग_लिखोl(0, LPC_ENET_MAC1(pldat->net_base));
	ग_लिखोl(0, LPC_ENET_MAC2(pldat->net_base));
पूर्ण

/*
 * MAC<--->PHY support functions
 */
अटल पूर्णांक lpc_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक phyreg)
अणु
	काष्ठा netdata_local *pldat = bus->priv;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(100);
	पूर्णांक lps;

	ग_लिखोl(((phy_id << 8) | phyreg), LPC_ENET_MADR(pldat->net_base));
	ग_लिखोl(LPC_MCMD_READ, LPC_ENET_MCMD(pldat->net_base));

	/* Wait क्रम unbusy status */
	जबतक (पढ़ोl(LPC_ENET_MIND(pldat->net_base)) & LPC_MIND_BUSY) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -EIO;
		cpu_relax();
	पूर्ण

	lps = पढ़ोl(LPC_ENET_MRDD(pldat->net_base));
	ग_लिखोl(0, LPC_ENET_MCMD(pldat->net_base));

	वापस lps;
पूर्ण

अटल पूर्णांक lpc_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक phyreg,
			u16 phydata)
अणु
	काष्ठा netdata_local *pldat = bus->priv;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(100);

	ग_लिखोl(((phy_id << 8) | phyreg), LPC_ENET_MADR(pldat->net_base));
	ग_लिखोl(phydata, LPC_ENET_MWTD(pldat->net_base));

	/* Wait क्रम completion */
	जबतक (पढ़ोl(LPC_ENET_MIND(pldat->net_base)) & LPC_MIND_BUSY) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -EIO;
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc_mdio_reset(काष्ठा mii_bus *bus)
अणु
	वापस __lpc_mii_mngt_reset((काष्ठा netdata_local *)bus->priv);
पूर्ण

अटल व्योम lpc_handle_link_change(काष्ठा net_device *ndev)
अणु
	काष्ठा netdata_local *pldat = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;
	अचिन्हित दीर्घ flags;

	bool status_change = false;

	spin_lock_irqsave(&pldat->lock, flags);

	अगर (phydev->link) अणु
		अगर ((pldat->speed != phydev->speed) ||
		    (pldat->duplex != phydev->duplex)) अणु
			pldat->speed = phydev->speed;
			pldat->duplex = phydev->duplex;
			status_change = true;
		पूर्ण
	पूर्ण

	अगर (phydev->link != pldat->link) अणु
		अगर (!phydev->link) अणु
			pldat->speed = 0;
			pldat->duplex = -1;
		पूर्ण
		pldat->link = phydev->link;

		status_change = true;
	पूर्ण

	spin_unlock_irqrestore(&pldat->lock, flags);

	अगर (status_change)
		__lpc_params_setup(pldat);
पूर्ण

अटल पूर्णांक lpc_mii_probe(काष्ठा net_device *ndev)
अणु
	काष्ठा netdata_local *pldat = netdev_priv(ndev);
	काष्ठा phy_device *phydev;

	/* Attach to the PHY */
	अगर (lpc_phy_पूर्णांकerface_mode(&pldat->pdev->dev) == PHY_INTERFACE_MODE_MII)
		netdev_info(ndev, "using MII interface\n");
	अन्यथा
		netdev_info(ndev, "using RMII interface\n");

	अगर (pldat->phy_node)
		phydev =  of_phy_find_device(pldat->phy_node);
	अन्यथा
		phydev = phy_find_first(pldat->mii_bus);
	अगर (!phydev) अणु
		netdev_err(ndev, "no PHY found\n");
		वापस -ENODEV;
	पूर्ण

	phydev = phy_connect(ndev, phydev_name(phydev),
			     &lpc_handle_link_change,
			     lpc_phy_पूर्णांकerface_mode(&pldat->pdev->dev));
	अगर (IS_ERR(phydev)) अणु
		netdev_err(ndev, "Could not attach to PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण

	phy_set_max_speed(phydev, SPEED_100);

	pldat->link = 0;
	pldat->speed = 0;
	pldat->duplex = -1;

	phy_attached_info(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc_mii_init(काष्ठा netdata_local *pldat)
अणु
	काष्ठा device_node *node;
	पूर्णांक err = -ENXIO;

	pldat->mii_bus = mdiobus_alloc();
	अगर (!pldat->mii_bus) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	/* Setup MII mode */
	अगर (lpc_phy_पूर्णांकerface_mode(&pldat->pdev->dev) == PHY_INTERFACE_MODE_MII)
		ग_लिखोl(LPC_COMMAND_PASSRUNTFRAME,
		       LPC_ENET_COMMAND(pldat->net_base));
	अन्यथा अणु
		ग_लिखोl((LPC_COMMAND_PASSRUNTFRAME | LPC_COMMAND_RMII),
		       LPC_ENET_COMMAND(pldat->net_base));
		ग_लिखोl(LPC_SUPP_RESET_RMII, LPC_ENET_SUPP(pldat->net_base));
	पूर्ण

	pldat->mii_bus->name = "lpc_mii_bus";
	pldat->mii_bus->पढ़ो = &lpc_mdio_पढ़ो;
	pldat->mii_bus->ग_लिखो = &lpc_mdio_ग_लिखो;
	pldat->mii_bus->reset = &lpc_mdio_reset;
	snम_लिखो(pldat->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pldat->pdev->name, pldat->pdev->id);
	pldat->mii_bus->priv = pldat;
	pldat->mii_bus->parent = &pldat->pdev->dev;

	node = of_get_child_by_name(pldat->pdev->dev.of_node, "mdio");
	err = of_mdiobus_रेजिस्टर(pldat->mii_bus, node);
	of_node_put(node);
	अगर (err)
		जाओ err_out_unरेजिस्टर_bus;

	err = lpc_mii_probe(pldat->ndev);
	अगर (err)
		जाओ err_out_unरेजिस्टर_bus;

	वापस 0;

err_out_unरेजिस्टर_bus:
	mdiobus_unरेजिस्टर(pldat->mii_bus);
	mdiobus_मुक्त(pldat->mii_bus);
err_out:
	वापस err;
पूर्ण

अटल व्योम __lpc_handle_xmit(काष्ठा net_device *ndev)
अणु
	काष्ठा netdata_local *pldat = netdev_priv(ndev);
	u32 txcidx, *ptxstat, txstat;

	txcidx = पढ़ोl(LPC_ENET_TXCONSUMEINDEX(pldat->net_base));
	जबतक (pldat->last_tx_idx != txcidx) अणु
		अचिन्हित पूर्णांक skblen = pldat->skblen[pldat->last_tx_idx];

		/* A buffer is available, get buffer status */
		ptxstat = &pldat->tx_stat_v[pldat->last_tx_idx];
		txstat = *ptxstat;

		/* Next buffer and decrement used buffer counter */
		pldat->num_used_tx_buffs--;
		pldat->last_tx_idx++;
		अगर (pldat->last_tx_idx >= ENET_TX_DESC)
			pldat->last_tx_idx = 0;

		/* Update collision counter */
		ndev->stats.collisions += TXSTATUS_COLLISIONS_GET(txstat);

		/* Any errors occurred? */
		अगर (txstat & TXSTATUS_ERROR) अणु
			अगर (txstat & TXSTATUS_UNDERRUN) अणु
				/* FIFO underrun */
				ndev->stats.tx_fअगरo_errors++;
			पूर्ण
			अगर (txstat & TXSTATUS_LATECOLL) अणु
				/* Late collision */
				ndev->stats.tx_पातed_errors++;
			पूर्ण
			अगर (txstat & TXSTATUS_EXCESSCOLL) अणु
				/* Excessive collision */
				ndev->stats.tx_पातed_errors++;
			पूर्ण
			अगर (txstat & TXSTATUS_EXCESSDEFER) अणु
				/* Defer limit */
				ndev->stats.tx_पातed_errors++;
			पूर्ण
			ndev->stats.tx_errors++;
		पूर्ण अन्यथा अणु
			/* Update stats */
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += skblen;
		पूर्ण

		txcidx = पढ़ोl(LPC_ENET_TXCONSUMEINDEX(pldat->net_base));
	पूर्ण

	अगर (pldat->num_used_tx_buffs <= ENET_TX_DESC/2) अणु
		अगर (netअगर_queue_stopped(ndev))
			netअगर_wake_queue(ndev);
	पूर्ण
पूर्ण

अटल पूर्णांक __lpc_handle_recv(काष्ठा net_device *ndev, पूर्णांक budget)
अणु
	काष्ठा netdata_local *pldat = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	u32 rxconsidx, len, ethst;
	काष्ठा rx_status_t *prxstat;
	पूर्णांक rx_करोne = 0;

	/* Get the current RX buffer indexes */
	rxconsidx = पढ़ोl(LPC_ENET_RXCONSUMEINDEX(pldat->net_base));
	जबतक (rx_करोne < budget && rxconsidx !=
			पढ़ोl(LPC_ENET_RXPRODUCEINDEX(pldat->net_base))) अणु
		/* Get poपूर्णांकer to receive status */
		prxstat = &pldat->rx_stat_v[rxconsidx];
		len = (prxstat->statusinfo & RXSTATUS_SIZE) + 1;

		/* Status error? */
		ethst = prxstat->statusinfo;
		अगर ((ethst & (RXSTATUS_ERROR | RXSTATUS_STATUS_ERROR)) ==
		    (RXSTATUS_ERROR | RXSTATUS_RANGE))
			ethst &= ~RXSTATUS_ERROR;

		अगर (ethst & RXSTATUS_ERROR) अणु
			पूर्णांक si = prxstat->statusinfo;
			/* Check statuses */
			अगर (si & RXSTATUS_OVERRUN) अणु
				/* Overrun error */
				ndev->stats.rx_fअगरo_errors++;
			पूर्ण अन्यथा अगर (si & RXSTATUS_CRC) अणु
				/* CRC error */
				ndev->stats.rx_crc_errors++;
			पूर्ण अन्यथा अगर (si & RXSTATUS_LENGTH) अणु
				/* Length error */
				ndev->stats.rx_length_errors++;
			पूर्ण अन्यथा अगर (si & RXSTATUS_ERROR) अणु
				/* Other error */
				ndev->stats.rx_length_errors++;
			पूर्ण
			ndev->stats.rx_errors++;
		पूर्ण अन्यथा अणु
			/* Packet is good */
			skb = dev_alloc_skb(len);
			अगर (!skb) अणु
				ndev->stats.rx_dropped++;
			पूर्ण अन्यथा अणु
				/* Copy packet from buffer */
				skb_put_data(skb,
					     pldat->rx_buff_v + rxconsidx * ENET_MAXF_SIZE,
					     len);

				/* Pass to upper layer */
				skb->protocol = eth_type_trans(skb, ndev);
				netअगर_receive_skb(skb);
				ndev->stats.rx_packets++;
				ndev->stats.rx_bytes += len;
			पूर्ण
		पूर्ण

		/* Increment consume index */
		rxconsidx = rxconsidx + 1;
		अगर (rxconsidx >= ENET_RX_DESC)
			rxconsidx = 0;
		ग_लिखोl(rxconsidx,
		       LPC_ENET_RXCONSUMEINDEX(pldat->net_base));
		rx_करोne++;
	पूर्ण

	वापस rx_करोne;
पूर्ण

अटल पूर्णांक lpc_eth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा netdata_local *pldat = container_of(napi,
			काष्ठा netdata_local, napi);
	काष्ठा net_device *ndev = pldat->ndev;
	पूर्णांक rx_करोne = 0;
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(ndev, 0);

	__netअगर_tx_lock(txq, smp_processor_id());
	__lpc_handle_xmit(ndev);
	__netअगर_tx_unlock(txq);
	rx_करोne = __lpc_handle_recv(ndev, budget);

	अगर (rx_करोne < budget) अणु
		napi_complete_करोne(napi, rx_करोne);
		lpc_eth_enable_पूर्णांक(pldat->net_base);
	पूर्ण

	वापस rx_करोne;
पूर्ण

अटल irqवापस_t __lpc_eth_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा netdata_local *pldat = netdev_priv(ndev);
	u32 पंचांगp;

	spin_lock(&pldat->lock);

	पंचांगp = पढ़ोl(LPC_ENET_INTSTATUS(pldat->net_base));
	/* Clear पूर्णांकerrupts */
	ग_लिखोl(पंचांगp, LPC_ENET_INTCLEAR(pldat->net_base));

	lpc_eth_disable_पूर्णांक(pldat->net_base);
	अगर (likely(napi_schedule_prep(&pldat->napi)))
		__napi_schedule(&pldat->napi);

	spin_unlock(&pldat->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lpc_eth_बंद(काष्ठा net_device *ndev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा netdata_local *pldat = netdev_priv(ndev);

	अगर (netअगर_msg_अगरकरोwn(pldat))
		dev_dbg(&pldat->pdev->dev, "shutting down %s\n", ndev->name);

	napi_disable(&pldat->napi);
	netअगर_stop_queue(ndev);

	अगर (ndev->phydev)
		phy_stop(ndev->phydev);

	spin_lock_irqsave(&pldat->lock, flags);
	__lpc_eth_reset(pldat);
	netअगर_carrier_off(ndev);
	ग_लिखोl(0, LPC_ENET_MAC1(pldat->net_base));
	ग_लिखोl(0, LPC_ENET_MAC2(pldat->net_base));
	spin_unlock_irqrestore(&pldat->lock, flags);

	clk_disable_unprepare(pldat->clk);

	वापस 0;
पूर्ण

अटल netdev_tx_t lpc_eth_hard_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *ndev)
अणु
	काष्ठा netdata_local *pldat = netdev_priv(ndev);
	u32 len, txidx;
	u32 *ptxstat;
	काष्ठा txrx_desc_t *ptxrxdesc;

	len = skb->len;

	spin_lock_irq(&pldat->lock);

	अगर (pldat->num_used_tx_buffs >= (ENET_TX_DESC - 1)) अणु
		/* This function should never be called when there are no
		 * buffers
		 */
		netअगर_stop_queue(ndev);
		spin_unlock_irq(&pldat->lock);
		WARN(1, "BUG! TX request when no free TX buffers!\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Get the next TX descriptor index */
	txidx = पढ़ोl(LPC_ENET_TXPRODUCEINDEX(pldat->net_base));

	/* Setup control क्रम the transfer */
	ptxstat = &pldat->tx_stat_v[txidx];
	*ptxstat = 0;
	ptxrxdesc = &pldat->tx_desc_v[txidx];
	ptxrxdesc->control =
		(len - 1) | TXDESC_CONTROL_LAST | TXDESC_CONTROL_INT;

	/* Copy data to the DMA buffer */
	स_नकल(pldat->tx_buff_v + txidx * ENET_MAXF_SIZE, skb->data, len);

	/* Save the buffer and increment the buffer counter */
	pldat->skblen[txidx] = len;
	pldat->num_used_tx_buffs++;

	/* Start transmit */
	txidx++;
	अगर (txidx >= ENET_TX_DESC)
		txidx = 0;
	ग_लिखोl(txidx, LPC_ENET_TXPRODUCEINDEX(pldat->net_base));

	/* Stop queue अगर no more TX buffers */
	अगर (pldat->num_used_tx_buffs >= (ENET_TX_DESC - 1))
		netअगर_stop_queue(ndev);

	spin_unlock_irq(&pldat->lock);

	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक lpc_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा netdata_local *pldat = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;
	स_नकल(ndev->dev_addr, addr->sa_data, ETH_ALEN);

	spin_lock_irqsave(&pldat->lock, flags);

	/* Set station address */
	__lpc_set_mac(pldat, ndev->dev_addr);

	spin_unlock_irqrestore(&pldat->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम lpc_eth_set_multicast_list(काष्ठा net_device *ndev)
अणु
	काष्ठा netdata_local *pldat = netdev_priv(ndev);
	काष्ठा netdev_hw_addr_list *mcptr = &ndev->mc;
	काष्ठा netdev_hw_addr *ha;
	u32 पंचांगp32, hash_val, hashlo, hashhi;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pldat->lock, flags);

	/* Set station address */
	__lpc_set_mac(pldat, ndev->dev_addr);

	पंचांगp32 =  LPC_RXFLTRW_ACCEPTUBROADCAST | LPC_RXFLTRW_ACCEPTPERFECT;

	अगर (ndev->flags & IFF_PROMISC)
		पंचांगp32 |= LPC_RXFLTRW_ACCEPTUNICAST |
			LPC_RXFLTRW_ACCEPTUMULTICAST;
	अगर (ndev->flags & IFF_ALLMULTI)
		पंचांगp32 |= LPC_RXFLTRW_ACCEPTUMULTICAST;

	अगर (netdev_hw_addr_list_count(mcptr))
		पंचांगp32 |= LPC_RXFLTRW_ACCEPTUMULTICASTHASH;

	ग_लिखोl(पंचांगp32, LPC_ENET_RXFILTER_CTRL(pldat->net_base));


	/* Set initial hash table */
	hashlo = 0x0;
	hashhi = 0x0;

	/* 64 bits : multicast address in hash table */
	netdev_hw_addr_list_क्रम_each(ha, mcptr) अणु
		hash_val = (ether_crc(6, ha->addr) >> 23) & 0x3F;

		अगर (hash_val >= 32)
			hashhi |= 1 << (hash_val - 32);
		अन्यथा
			hashlo |= 1 << hash_val;
	पूर्ण

	ग_लिखोl(hashlo, LPC_ENET_HASHFILTERL(pldat->net_base));
	ग_लिखोl(hashhi, LPC_ENET_HASHFILTERH(pldat->net_base));

	spin_unlock_irqrestore(&pldat->lock, flags);
पूर्ण

अटल पूर्णांक lpc_eth_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा netdata_local *pldat = netdev_priv(ndev);
	पूर्णांक ret;

	अगर (netअगर_msg_अगरup(pldat))
		dev_dbg(&pldat->pdev->dev, "enabling %s\n", ndev->name);

	ret = clk_prepare_enable(pldat->clk);
	अगर (ret)
		वापस ret;

	/* Suspended PHY makes LPC ethernet core block, so resume now */
	phy_resume(ndev->phydev);

	/* Reset and initialize */
	__lpc_eth_reset(pldat);
	__lpc_eth_init(pldat);

	/* schedule a link state check */
	phy_start(ndev->phydev);
	netअगर_start_queue(ndev);
	napi_enable(&pldat->napi);

	वापस 0;
पूर्ण

/*
 * Ethtool ops
 */
अटल व्योम lpc_eth_ethtool_getdrvinfo(काष्ठा net_device *ndev,
	काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, MODNAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, dev_name(ndev->dev.parent),
		माप(info->bus_info));
पूर्ण

अटल u32 lpc_eth_ethtool_geपंचांगsglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा netdata_local *pldat = netdev_priv(ndev);

	वापस pldat->msg_enable;
पूर्ण

अटल व्योम lpc_eth_ethtool_seपंचांगsglevel(काष्ठा net_device *ndev, u32 level)
अणु
	काष्ठा netdata_local *pldat = netdev_priv(ndev);

	pldat->msg_enable = level;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops lpc_eth_ethtool_ops = अणु
	.get_drvinfo	= lpc_eth_ethtool_getdrvinfo,
	.get_msglevel	= lpc_eth_ethtool_geपंचांगsglevel,
	.set_msglevel	= lpc_eth_ethtool_seपंचांगsglevel,
	.get_link	= ethtool_op_get_link,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops lpc_netdev_ops = अणु
	.nकरो_खोलो		= lpc_eth_खोलो,
	.nकरो_stop		= lpc_eth_बंद,
	.nकरो_start_xmit		= lpc_eth_hard_start_xmit,
	.nकरो_set_rx_mode	= lpc_eth_set_multicast_list,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_set_mac_address	= lpc_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक lpc_eth_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा netdata_local *pldat;
	काष्ठा net_device *ndev;
	dma_addr_t dma_handle;
	काष्ठा resource *res;
	पूर्णांक irq, ret;

	/* Setup network पूर्णांकerface क्रम RMII or MII mode */
	lpc32xx_set_phy_पूर्णांकerface_mode(lpc_phy_पूर्णांकerface_mode(dev));

	/* Get platक्रमm resources */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!res || irq < 0) अणु
		dev_err(dev, "error getting resources.\n");
		ret = -ENXIO;
		जाओ err_निकास;
	पूर्ण

	/* Allocate net driver data काष्ठाure */
	ndev = alloc_etherdev(माप(काष्ठा netdata_local));
	अगर (!ndev) अणु
		dev_err(dev, "could not allocate device.\n");
		ret = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

	SET_NETDEV_DEV(ndev, dev);

	pldat = netdev_priv(ndev);
	pldat->pdev = pdev;
	pldat->ndev = ndev;

	spin_lock_init(&pldat->lock);

	/* Save resources */
	ndev->irq = irq;

	/* Get घड़ी क्रम the device */
	pldat->clk = clk_get(dev, शून्य);
	अगर (IS_ERR(pldat->clk)) अणु
		dev_err(dev, "error getting clock.\n");
		ret = PTR_ERR(pldat->clk);
		जाओ err_out_मुक्त_dev;
	पूर्ण

	/* Enable network घड़ी */
	ret = clk_prepare_enable(pldat->clk);
	अगर (ret)
		जाओ err_out_clk_put;

	/* Map IO space */
	pldat->net_base = ioremap(res->start, resource_size(res));
	अगर (!pldat->net_base) अणु
		dev_err(dev, "failed to map registers\n");
		ret = -ENOMEM;
		जाओ err_out_disable_घड़ीs;
	पूर्ण
	ret = request_irq(ndev->irq, __lpc_eth_पूर्णांकerrupt, 0,
			  ndev->name, ndev);
	अगर (ret) अणु
		dev_err(dev, "error requesting interrupt.\n");
		जाओ err_out_iounmap;
	पूर्ण

	/* Setup driver functions */
	ndev->netdev_ops = &lpc_netdev_ops;
	ndev->ethtool_ops = &lpc_eth_ethtool_ops;
	ndev->watchकरोg_समयo = msecs_to_jअगरfies(2500);

	/* Get size of DMA buffers/descriptors region */
	pldat->dma_buff_size = (ENET_TX_DESC + ENET_RX_DESC) * (ENET_MAXF_SIZE +
		माप(काष्ठा txrx_desc_t) + माप(काष्ठा rx_status_t));

	अगर (use_iram_क्रम_net(dev)) अणु
		अगर (pldat->dma_buff_size >
		    lpc32xx_वापस_iram(&pldat->dma_buff_base_v, &dma_handle)) अणु
			pldat->dma_buff_base_v = शून्य;
			pldat->dma_buff_size = 0;
			netdev_err(ndev,
				"IRAM not big enough for net buffers, using SDRAM instead.\n");
		पूर्ण
	पूर्ण

	अगर (pldat->dma_buff_base_v == शून्य) अणु
		ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
		अगर (ret)
			जाओ err_out_मुक्त_irq;

		pldat->dma_buff_size = PAGE_ALIGN(pldat->dma_buff_size);

		/* Allocate a chunk of memory क्रम the DMA ethernet buffers
		 * and descriptors
		 */
		pldat->dma_buff_base_v =
			dma_alloc_coherent(dev,
					   pldat->dma_buff_size, &dma_handle,
					   GFP_KERNEL);
		अगर (pldat->dma_buff_base_v == शून्य) अणु
			ret = -ENOMEM;
			जाओ err_out_मुक्त_irq;
		पूर्ण
	पूर्ण
	pldat->dma_buff_base_p = dma_handle;

	netdev_dbg(ndev, "IO address space     :%pR\n", res);
	netdev_dbg(ndev, "IO address size      :%zd\n",
			(माप_प्रकार)resource_size(res));
	netdev_dbg(ndev, "IO address (mapped)  :0x%p\n",
			pldat->net_base);
	netdev_dbg(ndev, "IRQ number           :%d\n", ndev->irq);
	netdev_dbg(ndev, "DMA buffer size      :%zd\n", pldat->dma_buff_size);
	netdev_dbg(ndev, "DMA buffer P address :%pad\n",
			&pldat->dma_buff_base_p);
	netdev_dbg(ndev, "DMA buffer V address :0x%p\n",
			pldat->dma_buff_base_v);

	pldat->phy_node = of_parse_phandle(np, "phy-handle", 0);

	/* Get MAC address from current HW setting (POR state is all zeros) */
	__lpc_get_mac(pldat, ndev->dev_addr);

	अगर (!is_valid_ether_addr(ndev->dev_addr)) अणु
		of_get_mac_address(np, ndev->dev_addr);
	पूर्ण
	अगर (!is_valid_ether_addr(ndev->dev_addr))
		eth_hw_addr_अक्रमom(ndev);

	/* then shut everything करोwn to save घातer */
	__lpc_eth_shutकरोwn(pldat);

	/* Set शेष parameters */
	pldat->msg_enable = NETIF_MSG_LINK;

	/* Force an MII पूर्णांकerface reset and घड़ी setup */
	__lpc_mii_mngt_reset(pldat);

	/* Force शेष PHY पूर्णांकerface setup in chip, this will probably be
	 * changed by the PHY driver
	 */
	pldat->link = 0;
	pldat->speed = 100;
	pldat->duplex = DUPLEX_FULL;
	__lpc_params_setup(pldat);

	netअगर_napi_add(ndev, &pldat->napi, lpc_eth_poll, NAPI_WEIGHT);

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		dev_err(dev, "Cannot register net device, aborting.\n");
		जाओ err_out_dma_unmap;
	पूर्ण
	platक्रमm_set_drvdata(pdev, ndev);

	ret = lpc_mii_init(pldat);
	अगर (ret)
		जाओ err_out_unरेजिस्टर_netdev;

	netdev_info(ndev, "LPC mac at 0x%08lx irq %d\n",
	       (अचिन्हित दीर्घ)res->start, ndev->irq);

	device_init_wakeup(dev, 1);
	device_set_wakeup_enable(dev, 0);

	वापस 0;

err_out_unरेजिस्टर_netdev:
	unरेजिस्टर_netdev(ndev);
err_out_dma_unmap:
	अगर (!use_iram_क्रम_net(dev) ||
	    pldat->dma_buff_size > lpc32xx_वापस_iram(शून्य, शून्य))
		dma_मुक्त_coherent(dev, pldat->dma_buff_size,
				  pldat->dma_buff_base_v,
				  pldat->dma_buff_base_p);
err_out_मुक्त_irq:
	मुक्त_irq(ndev->irq, ndev);
err_out_iounmap:
	iounmap(pldat->net_base);
err_out_disable_घड़ीs:
	clk_disable_unprepare(pldat->clk);
err_out_clk_put:
	clk_put(pldat->clk);
err_out_मुक्त_dev:
	मुक्त_netdev(ndev);
err_निकास:
	pr_err("%s: not found (%d).\n", MODNAME, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक lpc_eth_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा netdata_local *pldat = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);

	अगर (!use_iram_क्रम_net(&pldat->pdev->dev) ||
	    pldat->dma_buff_size > lpc32xx_वापस_iram(शून्य, शून्य))
		dma_मुक्त_coherent(&pldat->pdev->dev, pldat->dma_buff_size,
				  pldat->dma_buff_base_v,
				  pldat->dma_buff_base_p);
	मुक्त_irq(ndev->irq, ndev);
	iounmap(pldat->net_base);
	mdiobus_unरेजिस्टर(pldat->mii_bus);
	mdiobus_मुक्त(pldat->mii_bus);
	clk_disable_unprepare(pldat->clk);
	clk_put(pldat->clk);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक lpc_eth_drv_suspend(काष्ठा platक्रमm_device *pdev,
	pm_message_t state)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा netdata_local *pldat = netdev_priv(ndev);

	अगर (device_may_wakeup(&pdev->dev))
		enable_irq_wake(ndev->irq);

	अगर (ndev) अणु
		अगर (netअगर_running(ndev)) अणु
			netअगर_device_detach(ndev);
			__lpc_eth_shutकरोwn(pldat);
			clk_disable_unprepare(pldat->clk);

			/*
			 * Reset again now घड़ी is disable to be sure
			 * EMC_MDC is करोwn
			 */
			__lpc_eth_reset(pldat);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc_eth_drv_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा netdata_local *pldat;

	अगर (device_may_wakeup(&pdev->dev))
		disable_irq_wake(ndev->irq);

	अगर (ndev) अणु
		अगर (netअगर_running(ndev)) अणु
			pldat = netdev_priv(ndev);

			/* Enable पूर्णांकerface घड़ी */
			clk_enable(pldat->clk);

			/* Reset and initialize */
			__lpc_eth_reset(pldat);
			__lpc_eth_init(pldat);

			netअगर_device_attach(ndev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id lpc_eth_match[] = अणु
	अणु .compatible = "nxp,lpc-eth" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc_eth_match);

अटल काष्ठा platक्रमm_driver lpc_eth_driver = अणु
	.probe		= lpc_eth_drv_probe,
	.हटाओ		= lpc_eth_drv_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= lpc_eth_drv_suspend,
	.resume		= lpc_eth_drv_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= MODNAME,
		.of_match_table = lpc_eth_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lpc_eth_driver);

MODULE_AUTHOR("Kevin Wells <kevin.wells@nxp.com>");
MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("LPC Ethernet Driver");
MODULE_LICENSE("GPL");
