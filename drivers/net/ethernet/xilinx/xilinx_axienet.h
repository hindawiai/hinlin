<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम Xilinx Axi Ethernet device driver.
 *
 * Copyright (c) 2009 Secret Lab Technologies, Ltd.
 * Copyright (c) 2010 - 2012 Xilinx, Inc. All rights reserved.
 */

#अगर_अघोषित XILINX_AXIENET_H
#घोषणा XILINX_AXIENET_H

#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/phylink.h>

/* Packet size info */
#घोषणा XAE_HDR_SIZE			14 /* Size of Ethernet header */
#घोषणा XAE_TRL_SIZE			 4 /* Size of Ethernet trailer (FCS) */
#घोषणा XAE_MTU			      1500 /* Max MTU of an Ethernet frame */
#घोषणा XAE_JUMBO_MTU		      9000 /* Max MTU of a jumbo Eth. frame */

#घोषणा XAE_MAX_FRAME_SIZE	 (XAE_MTU + XAE_HDR_SIZE + XAE_TRL_SIZE)
#घोषणा XAE_MAX_VLAN_FRAME_SIZE  (XAE_MTU + VLAN_ETH_HLEN + XAE_TRL_SIZE)
#घोषणा XAE_MAX_JUMBO_FRAME_SIZE (XAE_JUMBO_MTU + XAE_HDR_SIZE + XAE_TRL_SIZE)

/* Configuration options */

/* Accept all incoming packets. Default: disabled (cleared) */
#घोषणा XAE_OPTION_PROMISC			(1 << 0)

/* Jumbo frame support क्रम Tx & Rx. Default: disabled (cleared) */
#घोषणा XAE_OPTION_JUMBO			(1 << 1)

/* VLAN Rx & Tx frame support. Default: disabled (cleared) */
#घोषणा XAE_OPTION_VLAN				(1 << 2)

/* Enable recognition of flow control frames on Rx. Default: enabled (set) */
#घोषणा XAE_OPTION_FLOW_CONTROL			(1 << 4)

/* Strip FCS and PAD from incoming frames. Note: PAD from VLAN frames is not
 * stripped. Default: disabled (set)
 */
#घोषणा XAE_OPTION_FCS_STRIP			(1 << 5)

/* Generate FCS field and add PAD स्वतःmatically क्रम outgoing frames.
 * Default: enabled (set)
 */
#घोषणा XAE_OPTION_FCS_INSERT			(1 << 6)

/* Enable Length/Type error checking क्रम incoming frames. When this option is
 * set, the MAC will filter frames that have a mismatched type/length field
 * and अगर XAE_OPTION_REPORT_RXERR is set, the user is notअगरied when these
 * types of frames are encountered. When this option is cleared, the MAC will
 * allow these types of frames to be received. Default: enabled (set)
 */
#घोषणा XAE_OPTION_LENTYPE_ERR			(1 << 7)

/* Enable the transmitter. Default: enabled (set) */
#घोषणा XAE_OPTION_TXEN				(1 << 11)

/*  Enable the receiver. Default: enabled (set) */
#घोषणा XAE_OPTION_RXEN				(1 << 12)

/*  Default options set when device is initialized or reset */
#घोषणा XAE_OPTION_DEFAULTS				   \
				(XAE_OPTION_TXEN |	   \
				 XAE_OPTION_FLOW_CONTROL | \
				 XAE_OPTION_RXEN)

/* Axi DMA Register definitions */

#घोषणा XAXIDMA_TX_CR_OFFSET	0x00000000 /* Channel control */
#घोषणा XAXIDMA_TX_SR_OFFSET	0x00000004 /* Status */
#घोषणा XAXIDMA_TX_CDESC_OFFSET	0x00000008 /* Current descriptor poपूर्णांकer */
#घोषणा XAXIDMA_TX_TDESC_OFFSET	0x00000010 /* Tail descriptor poपूर्णांकer */

#घोषणा XAXIDMA_RX_CR_OFFSET	0x00000030 /* Channel control */
#घोषणा XAXIDMA_RX_SR_OFFSET	0x00000034 /* Status */
#घोषणा XAXIDMA_RX_CDESC_OFFSET	0x00000038 /* Current descriptor poपूर्णांकer */
#घोषणा XAXIDMA_RX_TDESC_OFFSET	0x00000040 /* Tail descriptor poपूर्णांकer */

#घोषणा XAXIDMA_CR_RUNSTOP_MASK	0x00000001 /* Start/stop DMA channel */
#घोषणा XAXIDMA_CR_RESET_MASK	0x00000004 /* Reset DMA engine */

#घोषणा XAXIDMA_SR_HALT_MASK	0x00000001 /* Indicates DMA channel halted */

#घोषणा XAXIDMA_BD_NDESC_OFFSET		0x00 /* Next descriptor poपूर्णांकer */
#घोषणा XAXIDMA_BD_BUFA_OFFSET		0x08 /* Buffer address */
#घोषणा XAXIDMA_BD_CTRL_LEN_OFFSET	0x18 /* Control/buffer length */
#घोषणा XAXIDMA_BD_STS_OFFSET		0x1C /* Status */
#घोषणा XAXIDMA_BD_USR0_OFFSET		0x20 /* User IP specअगरic word0 */
#घोषणा XAXIDMA_BD_USR1_OFFSET		0x24 /* User IP specअगरic word1 */
#घोषणा XAXIDMA_BD_USR2_OFFSET		0x28 /* User IP specअगरic word2 */
#घोषणा XAXIDMA_BD_USR3_OFFSET		0x2C /* User IP specअगरic word3 */
#घोषणा XAXIDMA_BD_USR4_OFFSET		0x30 /* User IP specअगरic word4 */
#घोषणा XAXIDMA_BD_ID_OFFSET		0x34 /* Sw ID */
#घोषणा XAXIDMA_BD_HAS_STSCNTRL_OFFSET	0x38 /* Whether has stscntrl strm */
#घोषणा XAXIDMA_BD_HAS_DRE_OFFSET	0x3C /* Whether has DRE */

#घोषणा XAXIDMA_BD_HAS_DRE_SHIFT	8 /* Whether has DRE shअगरt */
#घोषणा XAXIDMA_BD_HAS_DRE_MASK		0xF00 /* Whether has DRE mask */
#घोषणा XAXIDMA_BD_WORDLEN_MASK		0xFF /* Whether has DRE mask */

#घोषणा XAXIDMA_BD_CTRL_LENGTH_MASK	0x007FFFFF /* Requested len */
#घोषणा XAXIDMA_BD_CTRL_TXSOF_MASK	0x08000000 /* First tx packet */
#घोषणा XAXIDMA_BD_CTRL_TXखातापूर्ण_MASK	0x04000000 /* Last tx packet */
#घोषणा XAXIDMA_BD_CTRL_ALL_MASK	0x0C000000 /* All control bits */

#घोषणा XAXIDMA_DELAY_MASK		0xFF000000 /* Delay समयout counter */
#घोषणा XAXIDMA_COALESCE_MASK		0x00FF0000 /* Coalesce counter */

#घोषणा XAXIDMA_DELAY_SHIFT		24
#घोषणा XAXIDMA_COALESCE_SHIFT		16

#घोषणा XAXIDMA_IRQ_IOC_MASK		0x00001000 /* Completion पूर्णांकr */
#घोषणा XAXIDMA_IRQ_DELAY_MASK		0x00002000 /* Delay पूर्णांकerrupt */
#घोषणा XAXIDMA_IRQ_ERROR_MASK		0x00004000 /* Error पूर्णांकerrupt */
#घोषणा XAXIDMA_IRQ_ALL_MASK		0x00007000 /* All पूर्णांकerrupts */

/* Default TX/RX Threshold and रुकोbound values क्रम SGDMA mode */
#घोषणा XAXIDMA_DFT_TX_THRESHOLD	24
#घोषणा XAXIDMA_DFT_TX_WAITBOUND	254
#घोषणा XAXIDMA_DFT_RX_THRESHOLD	24
#घोषणा XAXIDMA_DFT_RX_WAITBOUND	254

#घोषणा XAXIDMA_BD_CTRL_TXSOF_MASK	0x08000000 /* First tx packet */
#घोषणा XAXIDMA_BD_CTRL_TXखातापूर्ण_MASK	0x04000000 /* Last tx packet */
#घोषणा XAXIDMA_BD_CTRL_ALL_MASK	0x0C000000 /* All control bits */

#घोषणा XAXIDMA_BD_STS_ACTUAL_LEN_MASK	0x007FFFFF /* Actual len */
#घोषणा XAXIDMA_BD_STS_COMPLETE_MASK	0x80000000 /* Completed */
#घोषणा XAXIDMA_BD_STS_DEC_ERR_MASK	0x40000000 /* Decode error */
#घोषणा XAXIDMA_BD_STS_SLV_ERR_MASK	0x20000000 /* Slave error */
#घोषणा XAXIDMA_BD_STS_INT_ERR_MASK	0x10000000 /* Internal err */
#घोषणा XAXIDMA_BD_STS_ALL_ERR_MASK	0x70000000 /* All errors */
#घोषणा XAXIDMA_BD_STS_RXSOF_MASK	0x08000000 /* First rx pkt */
#घोषणा XAXIDMA_BD_STS_RXखातापूर्ण_MASK	0x04000000 /* Last rx pkt */
#घोषणा XAXIDMA_BD_STS_ALL_MASK		0xFC000000 /* All status bits */

#घोषणा XAXIDMA_BD_MINIMUM_ALIGNMENT	0x40

/* Axi Ethernet रेजिस्टरs definition */
#घोषणा XAE_RAF_OFFSET		0x00000000 /* Reset and Address filter */
#घोषणा XAE_TPF_OFFSET		0x00000004 /* Tx Pause Frame */
#घोषणा XAE_IFGP_OFFSET		0x00000008 /* Tx Inter-frame gap adjusपंचांगent*/
#घोषणा XAE_IS_OFFSET		0x0000000C /* Interrupt status */
#घोषणा XAE_IP_OFFSET		0x00000010 /* Interrupt pending */
#घोषणा XAE_IE_OFFSET		0x00000014 /* Interrupt enable */
#घोषणा XAE_TTAG_OFFSET		0x00000018 /* Tx VLAN TAG */
#घोषणा XAE_RTAG_OFFSET		0x0000001C /* Rx VLAN TAG */
#घोषणा XAE_UAWL_OFFSET		0x00000020 /* Unicast address word lower */
#घोषणा XAE_UAWU_OFFSET		0x00000024 /* Unicast address word upper */
#घोषणा XAE_TPID0_OFFSET	0x00000028 /* VLAN TPID0 रेजिस्टर */
#घोषणा XAE_TPID1_OFFSET	0x0000002C /* VLAN TPID1 रेजिस्टर */
#घोषणा XAE_PPST_OFFSET		0x00000030 /* PCS PMA Soft Temac Status Reg */
#घोषणा XAE_RCW0_OFFSET		0x00000400 /* Rx Configuration Word 0 */
#घोषणा XAE_RCW1_OFFSET		0x00000404 /* Rx Configuration Word 1 */
#घोषणा XAE_TC_OFFSET		0x00000408 /* Tx Configuration */
#घोषणा XAE_FCC_OFFSET		0x0000040C /* Flow Control Configuration */
#घोषणा XAE_EMMC_OFFSET		0x00000410 /* EMAC mode configuration */
#घोषणा XAE_PHYC_OFFSET		0x00000414 /* RGMII/SGMII configuration */
#घोषणा XAE_ID_OFFSET		0x000004F8 /* Identअगरication रेजिस्टर */
#घोषणा XAE_MDIO_MC_OFFSET	0x00000500 /* MII Management Config */
#घोषणा XAE_MDIO_MCR_OFFSET	0x00000504 /* MII Management Control */
#घोषणा XAE_MDIO_MWD_OFFSET	0x00000508 /* MII Management Write Data */
#घोषणा XAE_MDIO_MRD_OFFSET	0x0000050C /* MII Management Read Data */
#घोषणा XAE_UAW0_OFFSET		0x00000700 /* Unicast address word 0 */
#घोषणा XAE_UAW1_OFFSET		0x00000704 /* Unicast address word 1 */
#घोषणा XAE_FMI_OFFSET		0x00000708 /* Filter Mask Index */
#घोषणा XAE_AF0_OFFSET		0x00000710 /* Address Filter 0 */
#घोषणा XAE_AF1_OFFSET		0x00000714 /* Address Filter 1 */

#घोषणा XAE_TX_VLAN_DATA_OFFSET 0x00004000 /* TX VLAN data table address */
#घोषणा XAE_RX_VLAN_DATA_OFFSET 0x00008000 /* RX VLAN data table address */
#घोषणा XAE_MCAST_TABLE_OFFSET	0x00020000 /* Multicast table address */

/* Bit Masks क्रम Axi Ethernet RAF रेजिस्टर */
/* Reject receive multicast destination address */
#घोषणा XAE_RAF_MCSTREJ_MASK		0x00000002
/* Reject receive broadcast destination address */
#घोषणा XAE_RAF_BCSTREJ_MASK		0x00000004
#घोषणा XAE_RAF_TXVTAGMODE_MASK		0x00000018 /* Tx VLAN TAG mode */
#घोषणा XAE_RAF_RXVTAGMODE_MASK		0x00000060 /* Rx VLAN TAG mode */
#घोषणा XAE_RAF_TXVSTRPMODE_MASK	0x00000180 /* Tx VLAN STRIP mode */
#घोषणा XAE_RAF_RXVSTRPMODE_MASK	0x00000600 /* Rx VLAN STRIP mode */
#घोषणा XAE_RAF_NEWFNCENBL_MASK		0x00000800 /* New function mode */
/* Extended Multicast Filtering mode */
#घोषणा XAE_RAF_EMULTIFLTRENBL_MASK	0x00001000
#घोषणा XAE_RAF_STATSRST_MASK		0x00002000 /* Stats. Counter Reset */
#घोषणा XAE_RAF_RXBADFRMEN_MASK		0x00004000 /* Recv Bad Frame Enable */
#घोषणा XAE_RAF_TXVTAGMODE_SHIFT	3 /* Tx Tag mode shअगरt bits */
#घोषणा XAE_RAF_RXVTAGMODE_SHIFT	5 /* Rx Tag mode shअगरt bits */
#घोषणा XAE_RAF_TXVSTRPMODE_SHIFT	7 /* Tx strip mode shअगरt bits*/
#घोषणा XAE_RAF_RXVSTRPMODE_SHIFT	9 /* Rx Strip mode shअगरt bits*/

/* Bit Masks क्रम Axi Ethernet TPF and IFGP रेजिस्टरs */
#घोषणा XAE_TPF_TPFV_MASK		0x0000FFFF /* Tx छोड़ो frame value */
/* Transmit पूर्णांकer-frame gap adjusपंचांगent value */
#घोषणा XAE_IFGP0_IFGP_MASK		0x0000007F

/* Bit Masks क्रम Axi Ethernet IS, IE and IP रेजिस्टरs, Same masks apply
 * क्रम all 3 रेजिस्टरs.
 */
/* Hard रेजिस्टर access complete */
#घोषणा XAE_INT_HARDACSCMPLT_MASK	0x00000001
/* Auto negotiation complete */
#घोषणा XAE_INT_AUTONEG_MASK		0x00000002
#घोषणा XAE_INT_RXCMPIT_MASK		0x00000004 /* Rx complete */
#घोषणा XAE_INT_RXRJECT_MASK		0x00000008 /* Rx frame rejected */
#घोषणा XAE_INT_RXFIFOOVR_MASK		0x00000010 /* Rx fअगरo overrun */
#घोषणा XAE_INT_TXCMPIT_MASK		0x00000020 /* Tx complete */
#घोषणा XAE_INT_RXDCMLOCK_MASK		0x00000040 /* Rx Dcm Lock */
#घोषणा XAE_INT_MGTRDY_MASK		0x00000080 /* MGT घड़ी Lock */
#घोषणा XAE_INT_PHYRSTCMPLT_MASK	0x00000100 /* Phy Reset complete */
#घोषणा XAE_INT_ALL_MASK		0x0000003F /* All the पूर्णांकs */

/* INT bits that indicate receive errors */
#घोषणा XAE_INT_RECV_ERROR_MASK				\
	(XAE_INT_RXRJECT_MASK | XAE_INT_RXFIFOOVR_MASK)

/* Bit masks क्रम Axi Ethernet VLAN TPID Word 0 रेजिस्टर */
#घोषणा XAE_TPID_0_MASK		0x0000FFFF /* TPID 0 */
#घोषणा XAE_TPID_1_MASK		0xFFFF0000 /* TPID 1 */

/* Bit masks क्रम Axi Ethernet VLAN TPID Word 1 रेजिस्टर */
#घोषणा XAE_TPID_2_MASK		0x0000FFFF /* TPID 0 */
#घोषणा XAE_TPID_3_MASK		0xFFFF0000 /* TPID 1 */

/* Bit masks क्रम Axi Ethernet RCW1 रेजिस्टर */
#घोषणा XAE_RCW1_RST_MASK	0x80000000 /* Reset */
#घोषणा XAE_RCW1_JUM_MASK	0x40000000 /* Jumbo frame enable */
/* In-Band FCS enable (FCS not stripped) */
#घोषणा XAE_RCW1_FCS_MASK	0x20000000
#घोषणा XAE_RCW1_RX_MASK	0x10000000 /* Receiver enable */
#घोषणा XAE_RCW1_VLAN_MASK	0x08000000 /* VLAN frame enable */
/* Length/type field valid check disable */
#घोषणा XAE_RCW1_LT_DIS_MASK	0x02000000
/* Control frame Length check disable */
#घोषणा XAE_RCW1_CL_DIS_MASK	0x01000000
/* Pause frame source address bits [47:32]. Bits [31:0] are
 * stored in रेजिस्टर RCW0
 */
#घोषणा XAE_RCW1_PAUSEADDR_MASK 0x0000FFFF

/* Bit masks क्रम Axi Ethernet TC रेजिस्टर */
#घोषणा XAE_TC_RST_MASK		0x80000000 /* Reset */
#घोषणा XAE_TC_JUM_MASK		0x40000000 /* Jumbo frame enable */
/* In-Band FCS enable (FCS not generated) */
#घोषणा XAE_TC_FCS_MASK		0x20000000
#घोषणा XAE_TC_TX_MASK		0x10000000 /* Transmitter enable */
#घोषणा XAE_TC_VLAN_MASK	0x08000000 /* VLAN frame enable */
/* Inter-frame gap adjusपंचांगent enable */
#घोषणा XAE_TC_IFG_MASK		0x02000000

/* Bit masks क्रम Axi Ethernet FCC रेजिस्टर */
#घोषणा XAE_FCC_FCRX_MASK	0x20000000 /* Rx flow control enable */
#घोषणा XAE_FCC_FCTX_MASK	0x40000000 /* Tx flow control enable */

/* Bit masks क्रम Axi Ethernet EMMC रेजिस्टर */
#घोषणा XAE_EMMC_LINKSPEED_MASK	0xC0000000 /* Link speed */
#घोषणा XAE_EMMC_RGMII_MASK	0x20000000 /* RGMII mode enable */
#घोषणा XAE_EMMC_SGMII_MASK	0x10000000 /* SGMII mode enable */
#घोषणा XAE_EMMC_GPCS_MASK	0x08000000 /* 1000BaseX mode enable */
#घोषणा XAE_EMMC_HOST_MASK	0x04000000 /* Host पूर्णांकerface enable */
#घोषणा XAE_EMMC_TX16BIT	0x02000000 /* 16 bit Tx client enable */
#घोषणा XAE_EMMC_RX16BIT	0x01000000 /* 16 bit Rx client enable */
#घोषणा XAE_EMMC_LINKSPD_10	0x00000000 /* Link Speed mask क्रम 10 Mbit */
#घोषणा XAE_EMMC_LINKSPD_100	0x40000000 /* Link Speed mask क्रम 100 Mbit */
#घोषणा XAE_EMMC_LINKSPD_1000	0x80000000 /* Link Speed mask क्रम 1000 Mbit */

/* Bit masks क्रम Axi Ethernet PHYC रेजिस्टर */
#घोषणा XAE_PHYC_SGMIILINKSPEED_MASK	0xC0000000 /* SGMII link speed mask*/
#घोषणा XAE_PHYC_RGMIILINKSPEED_MASK	0x0000000C /* RGMII link speed */
#घोषणा XAE_PHYC_RGMIIHD_MASK		0x00000002 /* RGMII Half-duplex */
#घोषणा XAE_PHYC_RGMIILINK_MASK		0x00000001 /* RGMII link status */
#घोषणा XAE_PHYC_RGLINKSPD_10		0x00000000 /* RGMII link 10 Mbit */
#घोषणा XAE_PHYC_RGLINKSPD_100		0x00000004 /* RGMII link 100 Mbit */
#घोषणा XAE_PHYC_RGLINKSPD_1000		0x00000008 /* RGMII link 1000 Mbit */
#घोषणा XAE_PHYC_SGLINKSPD_10		0x00000000 /* SGMII link 10 Mbit */
#घोषणा XAE_PHYC_SGLINKSPD_100		0x40000000 /* SGMII link 100 Mbit */
#घोषणा XAE_PHYC_SGLINKSPD_1000		0x80000000 /* SGMII link 1000 Mbit */

/* Bit masks क्रम Axi Ethernet MDIO पूर्णांकerface MC रेजिस्टर */
#घोषणा XAE_MDIO_MC_MDIOEN_MASK		0x00000040 /* MII management enable */
#घोषणा XAE_MDIO_MC_CLOCK_DIVIDE_MAX	0x3F	   /* Maximum MDIO भागisor */

/* Bit masks क्रम Axi Ethernet MDIO पूर्णांकerface MCR रेजिस्टर */
#घोषणा XAE_MDIO_MCR_PHYAD_MASK		0x1F000000 /* Phy Address Mask */
#घोषणा XAE_MDIO_MCR_PHYAD_SHIFT	24	   /* Phy Address Shअगरt */
#घोषणा XAE_MDIO_MCR_REGAD_MASK		0x001F0000 /* Reg Address Mask */
#घोषणा XAE_MDIO_MCR_REGAD_SHIFT	16	   /* Reg Address Shअगरt */
#घोषणा XAE_MDIO_MCR_OP_MASK		0x0000C000 /* Operation Code Mask */
#घोषणा XAE_MDIO_MCR_OP_SHIFT		13	   /* Operation Code Shअगरt */
#घोषणा XAE_MDIO_MCR_OP_READ_MASK	0x00008000 /* Op Code Read Mask */
#घोषणा XAE_MDIO_MCR_OP_WRITE_MASK	0x00004000 /* Op Code Write Mask */
#घोषणा XAE_MDIO_MCR_INITIATE_MASK	0x00000800 /* Ready Mask */
#घोषणा XAE_MDIO_MCR_READY_MASK		0x00000080 /* Ready Mask */

/* Bit masks क्रम Axi Ethernet MDIO पूर्णांकerface MIS, MIP, MIE, MIC रेजिस्टरs */
#घोषणा XAE_MDIO_INT_MIIM_RDY_MASK	0x00000001 /* MIIM Interrupt */

/* Bit masks क्रम Axi Ethernet UAW1 रेजिस्टर */
/* Station address bits [47:32]; Station address
 * bits [31:0] are stored in रेजिस्टर UAW0
 */
#घोषणा XAE_UAW1_UNICASTADDR_MASK	0x0000FFFF

/* Bit masks क्रम Axi Ethernet FMI रेजिस्टर */
#घोषणा XAE_FMI_PM_MASK			0x80000000 /* Promis. mode enable */
#घोषणा XAE_FMI_IND_MASK		0x00000003 /* Index Mask */

#घोषणा XAE_MDIO_DIV_DFT		29 /* Default MDIO घड़ी भागisor */

/* Defines क्रम dअगरferent options क्रम C_PHY_TYPE parameter in Axi Ethernet IP */
#घोषणा XAE_PHY_TYPE_MII		0
#घोषणा XAE_PHY_TYPE_GMII		1
#घोषणा XAE_PHY_TYPE_RGMII_1_3		2
#घोषणा XAE_PHY_TYPE_RGMII_2_0		3
#घोषणा XAE_PHY_TYPE_SGMII		4
#घोषणा XAE_PHY_TYPE_1000BASE_X		5

 /* Total number of entries in the hardware multicast table. */
#घोषणा XAE_MULTICAST_CAM_TABLE_NUM	4

/* Axi Ethernet Synthesis features */
#घोषणा XAE_FEATURE_PARTIAL_RX_CSUM	(1 << 0)
#घोषणा XAE_FEATURE_PARTIAL_TX_CSUM	(1 << 1)
#घोषणा XAE_FEATURE_FULL_RX_CSUM	(1 << 2)
#घोषणा XAE_FEATURE_FULL_TX_CSUM	(1 << 3)
#घोषणा XAE_FEATURE_DMA_64BIT		(1 << 4)

#घोषणा XAE_NO_CSUM_OFFLOAD		0

#घोषणा XAE_FULL_CSUM_STATUS_MASK	0x00000038
#घोषणा XAE_IP_UDP_CSUM_VALIDATED	0x00000003
#घोषणा XAE_IP_TCP_CSUM_VALIDATED	0x00000002

#घोषणा DELAY_OF_ONE_MILLISEC		1000

/* Xilinx PCS/PMA PHY रेजिस्टर क्रम चयनing 1000BaseX or SGMII */
#घोषणा XLNX_MII_STD_SELECT_REG		0x11
#घोषणा XLNX_MII_STD_SELECT_SGMII	BIT(0)

/**
 * काष्ठा axidma_bd - Axi Dma buffer descriptor layout
 * @next:         MM2S/S2MM Next Descriptor Poपूर्णांकer
 * @next_msb:     MM2S/S2MM Next Descriptor Poपूर्णांकer (high 32 bits)
 * @phys:         MM2S/S2MM Buffer Address
 * @phys_msb:     MM2S/S2MM Buffer Address (high 32 bits)
 * @reserved3:    Reserved and not used
 * @reserved4:    Reserved and not used
 * @cntrl:        MM2S/S2MM Control value
 * @status:       MM2S/S2MM Status value
 * @app0:         MM2S/S2MM User Application Field 0.
 * @app1:         MM2S/S2MM User Application Field 1.
 * @app2:         MM2S/S2MM User Application Field 2.
 * @app3:         MM2S/S2MM User Application Field 3.
 * @app4:         MM2S/S2MM User Application Field 4.
 */
काष्ठा axidma_bd अणु
	u32 next;	/* Physical address of next buffer descriptor */
	u32 next_msb;	/* high 32 bits क्रम IP >= v7.1, reserved on older IP */
	u32 phys;
	u32 phys_msb;	/* क्रम IP >= v7.1, reserved क्रम older IP */
	u32 reserved3;
	u32 reserved4;
	u32 cntrl;
	u32 status;
	u32 app0;
	u32 app1;	/* TX start << 16 | insert */
	u32 app2;	/* TX csum seed */
	u32 app3;
	u32 app4;   /* Last field used by HW */
	काष्ठा sk_buff *skb;
पूर्ण __aligned(XAXIDMA_BD_MINIMUM_ALIGNMENT);

#घोषणा XAE_NUM_MISC_CLOCKS 3

/**
 * काष्ठा axienet_local - axienet निजी per device data
 * @ndev:	Poपूर्णांकer क्रम net_device to which it will be attached.
 * @dev:	Poपूर्णांकer to device काष्ठाure
 * @phy_node:	Poपूर्णांकer to device node काष्ठाure
 * @phylink:	Poपूर्णांकer to phylink instance
 * @phylink_config: phylink configuration settings
 * @pcs_phy:	Reference to PCS/PMA PHY अगर used
 * @चयन_x_sgmii: Whether चयनable 1000BaseX/SGMII mode is enabled in the core
 * @axi_clk:	AXI4-Lite bus घड़ी
 * @misc_clks:	Misc ethernet घड़ीs (AXI4-Stream, Ref, MGT घड़ीs)
 * @mii_bus:	Poपूर्णांकer to MII bus काष्ठाure
 * @mii_clk_भाग: MII bus घड़ी भागider value
 * @regs_start: Resource start क्रम axienet device addresses
 * @regs:	Base address क्रम the axienet_local device address space
 * @dma_regs:	Base address क्रम the axidma device address space
 * @dma_err_task: Work काष्ठाure to process Axi DMA errors
 * @tx_irq:	Axidma TX IRQ number
 * @rx_irq:	Axidma RX IRQ number
 * @eth_irq:	Ethernet core IRQ number
 * @phy_mode:	Phy type to identअगरy between MII/GMII/RGMII/SGMII/1000 Base-X
 * @options:	AxiEthernet option word
 * @features:	Stores the extended features supported by the axienet hw
 * @tx_bd_v:	Virtual address of the TX buffer descriptor ring
 * @tx_bd_p:	Physical address(start address) of the TX buffer descr. ring
 * @tx_bd_num:	Size of TX buffer descriptor ring
 * @rx_bd_v:	Virtual address of the RX buffer descriptor ring
 * @rx_bd_p:	Physical address(start address) of the RX buffer descr. ring
 * @rx_bd_num:	Size of RX buffer descriptor ring
 * @tx_bd_ci:	Stores the index of the Tx buffer descriptor in the ring being
 *		accessed currently. Used जबतक alloc. BDs beक्रमe a TX starts
 * @tx_bd_tail:	Stores the index of the Tx buffer descriptor in the ring being
 *		accessed currently. Used जबतक processing BDs after the TX
 *		completed.
 * @rx_bd_ci:	Stores the index of the Rx buffer descriptor in the ring being
 *		accessed currently.
 * @max_frm_size: Stores the maximum size of the frame that can be that
 *		  Txed/Rxed in the existing hardware. If jumbo option is
 *		  supported, the maximum frame size would be 9k. Else it is
 *		  1522 bytes (assuming support क्रम basic VLAN)
 * @rxmem:	Stores rx memory size क्रम jumbo frame handling.
 * @csum_offload_on_tx_path:	Stores the checksum selection on TX side.
 * @csum_offload_on_rx_path:	Stores the checksum selection on RX side.
 * @coalesce_count_rx:	Store the irq coalesce on RX side.
 * @coalesce_count_tx:	Store the irq coalesce on TX side.
 */
काष्ठा axienet_local अणु
	काष्ठा net_device *ndev;
	काष्ठा device *dev;

	काष्ठा device_node *phy_node;

	काष्ठा phylink *phylink;
	काष्ठा phylink_config phylink_config;

	काष्ठा mdio_device *pcs_phy;

	bool चयन_x_sgmii;

	काष्ठा clk *axi_clk;
	काष्ठा clk_bulk_data misc_clks[XAE_NUM_MISC_CLOCKS];

	काष्ठा mii_bus *mii_bus;
	u8 mii_clk_भाग;

	resource_माप_प्रकार regs_start;
	व्योम __iomem *regs;
	व्योम __iomem *dma_regs;

	काष्ठा work_काष्ठा dma_err_task;

	पूर्णांक tx_irq;
	पूर्णांक rx_irq;
	पूर्णांक eth_irq;
	phy_पूर्णांकerface_t phy_mode;

	u32 options;
	u32 features;

	काष्ठा axidma_bd *tx_bd_v;
	dma_addr_t tx_bd_p;
	u32 tx_bd_num;
	काष्ठा axidma_bd *rx_bd_v;
	dma_addr_t rx_bd_p;
	u32 rx_bd_num;
	u32 tx_bd_ci;
	u32 tx_bd_tail;
	u32 rx_bd_ci;

	u32 max_frm_size;
	u32 rxmem;

	पूर्णांक csum_offload_on_tx_path;
	पूर्णांक csum_offload_on_rx_path;

	u32 coalesce_count_rx;
	u32 coalesce_count_tx;
पूर्ण;

/**
 * काष्ठा axiethernet_option - Used to set axi ethernet hardware options
 * @opt:	Option to be set.
 * @reg:	Register offset to be written क्रम setting the option
 * @m_or:	Mask to be ORed क्रम setting the option in the रेजिस्टर
 */
काष्ठा axienet_option अणु
	u32 opt;
	u32 reg;
	u32 m_or;
पूर्ण;

/**
 * axienet_ior - Memory mapped Axi Ethernet रेजिस्टर पढ़ो
 * @lp:         Poपूर्णांकer to axienet local काष्ठाure
 * @offset:     Address offset from the base address of Axi Ethernet core
 *
 * Return: The contents of the Axi Ethernet रेजिस्टर
 *
 * This function वापसs the contents of the corresponding रेजिस्टर.
 */
अटल अंतरभूत u32 axienet_ior(काष्ठा axienet_local *lp, off_t offset)
अणु
	वापस ioपढ़ो32(lp->regs + offset);
पूर्ण

अटल अंतरभूत u32 axinet_ior_पढ़ो_mcr(काष्ठा axienet_local *lp)
अणु
	वापस axienet_ior(lp, XAE_MDIO_MCR_OFFSET);
पूर्ण

अटल अंतरभूत व्योम axienet_lock_mii(काष्ठा axienet_local *lp)
अणु
	अगर (lp->mii_bus)
		mutex_lock(&lp->mii_bus->mdio_lock);
पूर्ण

अटल अंतरभूत व्योम axienet_unlock_mii(काष्ठा axienet_local *lp)
अणु
	अगर (lp->mii_bus)
		mutex_unlock(&lp->mii_bus->mdio_lock);
पूर्ण

/**
 * axienet_iow - Memory mapped Axi Ethernet रेजिस्टर ग_लिखो
 * @lp:         Poपूर्णांकer to axienet local काष्ठाure
 * @offset:     Address offset from the base address of Axi Ethernet core
 * @value:      Value to be written पूर्णांकo the Axi Ethernet रेजिस्टर
 *
 * This function ग_लिखोs the desired value पूर्णांकo the corresponding Axi Ethernet
 * रेजिस्टर.
 */
अटल अंतरभूत व्योम axienet_iow(काष्ठा axienet_local *lp, off_t offset,
			       u32 value)
अणु
	ioग_लिखो32(value, lp->regs + offset);
पूर्ण

/* Function prototypes visible in xilinx_axienet_mdio.c क्रम other files */
पूर्णांक axienet_mdio_enable(काष्ठा axienet_local *lp);
व्योम axienet_mdio_disable(काष्ठा axienet_local *lp);
पूर्णांक axienet_mdio_setup(काष्ठा axienet_local *lp);
व्योम axienet_mdio_tearकरोwn(काष्ठा axienet_local *lp);

#पूर्ण_अगर /* XILINX_AXI_ENET_H */
