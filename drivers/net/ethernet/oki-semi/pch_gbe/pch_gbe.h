<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 1999 - 2010 Intel Corporation.
 * Copyright (C) 2010 OKI SEMICONDUCTOR Co., LTD.
 *
 * This code was derived from the Intel e1000e Linux driver.
 */

#अगर_अघोषित _PCH_GBE_H_
#घोषणा _PCH_GBE_H_

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mii.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>

/**
 * pch_gbe_regs_mac_adr - Structure holding values of mac address रेजिस्टरs
 * @high	Denotes the 1st to 4th byte from the initial of MAC address
 * @low		Denotes the 5th to 6th byte from the initial of MAC address
 */
काष्ठा pch_gbe_regs_mac_adr अणु
	u32 high;
	u32 low;
पूर्ण;
/**
 * pch_udc_regs - Structure holding values of MAC रेजिस्टरs
 */
काष्ठा pch_gbe_regs अणु
	u32 INT_ST;
	u32 INT_EN;
	u32 MODE;
	u32 RESET;
	u32 TCPIP_ACC;
	u32 EX_LIST;
	u32 INT_ST_HOLD;
	u32 PHY_INT_CTRL;
	u32 MAC_RX_EN;
	u32 RX_FCTRL;
	u32 PAUSE_REQ;
	u32 RX_MODE;
	u32 TX_MODE;
	u32 RX_FIFO_ST;
	u32 TX_FIFO_ST;
	u32 TX_FID;
	u32 TX_RESULT;
	u32 PAUSE_PKT1;
	u32 PAUSE_PKT2;
	u32 PAUSE_PKT3;
	u32 PAUSE_PKT4;
	u32 PAUSE_PKT5;
	u32 reserve[2];
	काष्ठा pch_gbe_regs_mac_adr mac_adr[16];
	u32 ADDR_MASK;
	u32 MIIM;
	u32 MAC_ADDR_LOAD;
	u32 RGMII_ST;
	u32 RGMII_CTRL;
	u32 reserve3[3];
	u32 DMA_CTRL;
	u32 reserve4[3];
	u32 RX_DSC_BASE;
	u32 RX_DSC_SIZE;
	u32 RX_DSC_HW_P;
	u32 RX_DSC_HW_P_HLD;
	u32 RX_DSC_SW_P;
	u32 reserve5[3];
	u32 TX_DSC_BASE;
	u32 TX_DSC_SIZE;
	u32 TX_DSC_HW_P;
	u32 TX_DSC_HW_P_HLD;
	u32 TX_DSC_SW_P;
	u32 reserve6[3];
	u32 RX_DMA_ST;
	u32 TX_DMA_ST;
	u32 reserve7[2];
	u32 WOL_ST;
	u32 WOL_CTRL;
	u32 WOL_ADDR_MASK;
पूर्ण;

/* Interrupt Status */
/* Interrupt Status Hold */
/* Interrupt Enable */
#घोषणा PCH_GBE_INT_RX_DMA_CMPLT  0x00000001 /* Receive DMA Transfer Complete */
#घोषणा PCH_GBE_INT_RX_VALID      0x00000002 /* MAC Normal Receive Complete */
#घोषणा PCH_GBE_INT_RX_FRAME_ERR  0x00000004 /* Receive frame error */
#घोषणा PCH_GBE_INT_RX_FIFO_ERR   0x00000008 /* Receive FIFO Overflow */
#घोषणा PCH_GBE_INT_RX_DMA_ERR    0x00000010 /* Receive DMA Transfer Error */
#घोषणा PCH_GBE_INT_RX_DSC_EMP    0x00000020 /* Receive Descriptor Empty */
#घोषणा PCH_GBE_INT_TX_CMPLT      0x00000100 /* MAC Transmission Complete */
#घोषणा PCH_GBE_INT_TX_DMA_CMPLT  0x00000200 /* DMA Transfer Complete */
#घोषणा PCH_GBE_INT_TX_FIFO_ERR   0x00000400 /* Transmission FIFO underflow. */
#घोषणा PCH_GBE_INT_TX_DMA_ERR    0x00000800 /* Transmission DMA Error */
#घोषणा PCH_GBE_INT_PAUSE_CMPLT   0x00001000 /* Pause Transmission complete */
#घोषणा PCH_GBE_INT_MIIM_CMPLT    0x00010000 /* MIIM I/F Read completion */
#घोषणा PCH_GBE_INT_PHY_INT       0x00100000 /* Interruption from PHY */
#घोषणा PCH_GBE_INT_WOL_DET       0x01000000 /* Wake On LAN Event detection. */
#घोषणा PCH_GBE_INT_TCPIP_ERR     0x10000000 /* TCP/IP Accelerator Error */

/* Mode */
#घोषणा PCH_GBE_MODE_MII_ETHER      0x00000000  /* GIGA Ethernet Mode [MII] */
#घोषणा PCH_GBE_MODE_GMII_ETHER     0x80000000  /* GIGA Ethernet Mode [GMII] */
#घोषणा PCH_GBE_MODE_HALF_DUPLEX    0x00000000  /* Duplex Mode [half duplex] */
#घोषणा PCH_GBE_MODE_FULL_DUPLEX    0x40000000  /* Duplex Mode [full duplex] */
#घोषणा PCH_GBE_MODE_FR_BST         0x04000000  /* Frame bursting is करोne */

/* Reset */
#घोषणा PCH_GBE_ALL_RST         0x80000000  /* All reset */
#घोषणा PCH_GBE_TX_RST          0x00008000  /* TX MAC, TX FIFO, TX DMA reset */
#घोषणा PCH_GBE_RX_RST          0x00004000  /* RX MAC, RX FIFO, RX DMA reset */

/* TCP/IP Accelerator Control */
#घोषणा PCH_GBE_EX_LIST_EN      0x00000008  /* External List Enable */
#घोषणा PCH_GBE_RX_TCPIPACC_OFF 0x00000004  /* RX TCP/IP ACC Disabled */
#घोषणा PCH_GBE_TX_TCPIPACC_EN  0x00000002  /* TX TCP/IP ACC Enable */
#घोषणा PCH_GBE_RX_TCPIPACC_EN  0x00000001  /* RX TCP/IP ACC Enable */

/* MAC RX Enable */
#घोषणा PCH_GBE_MRE_MAC_RX_EN   0x00000001      /* MAC Receive Enable */

/* RX Flow Control */
#घोषणा PCH_GBE_FL_CTRL_EN      0x80000000  /* Pause packet is enabled */

/* Pause Packet Request */
#घोषणा PCH_GBE_PS_PKT_RQ       0x80000000  /* Pause packet Request */

/* RX Mode */
#घोषणा PCH_GBE_ADD_FIL_EN      0x80000000  /* Address Filtering Enable */
/* Multicast Filtering Enable */
#घोषणा PCH_GBE_MLT_FIL_EN      0x40000000
/* Receive Almost Empty Threshold */
#घोषणा PCH_GBE_RH_ALM_EMP_4    0x00000000      /* 4 words */
#घोषणा PCH_GBE_RH_ALM_EMP_8    0x00004000      /* 8 words */
#घोषणा PCH_GBE_RH_ALM_EMP_16   0x00008000      /* 16 words */
#घोषणा PCH_GBE_RH_ALM_EMP_32   0x0000C000      /* 32 words */
/* Receive Almost Full Threshold */
#घोषणा PCH_GBE_RH_ALM_FULL_4   0x00000000      /* 4 words */
#घोषणा PCH_GBE_RH_ALM_FULL_8   0x00001000      /* 8 words */
#घोषणा PCH_GBE_RH_ALM_FULL_16  0x00002000      /* 16 words */
#घोषणा PCH_GBE_RH_ALM_FULL_32  0x00003000      /* 32 words */
/* RX FIFO Read Trigger Threshold */
#घोषणा PCH_GBE_RH_RD_TRG_4     0x00000000      /* 4 words */
#घोषणा PCH_GBE_RH_RD_TRG_8     0x00000200      /* 8 words */
#घोषणा PCH_GBE_RH_RD_TRG_16    0x00000400      /* 16 words */
#घोषणा PCH_GBE_RH_RD_TRG_32    0x00000600      /* 32 words */
#घोषणा PCH_GBE_RH_RD_TRG_64    0x00000800      /* 64 words */
#घोषणा PCH_GBE_RH_RD_TRG_128   0x00000A00      /* 128 words */
#घोषणा PCH_GBE_RH_RD_TRG_256   0x00000C00      /* 256 words */
#घोषणा PCH_GBE_RH_RD_TRG_512   0x00000E00      /* 512 words */

/* Receive Descriptor bit definitions */
#घोषणा PCH_GBE_RXD_ACC_STAT_BCAST          0x00000400
#घोषणा PCH_GBE_RXD_ACC_STAT_MCAST          0x00000200
#घोषणा PCH_GBE_RXD_ACC_STAT_UCAST          0x00000100
#घोषणा PCH_GBE_RXD_ACC_STAT_TCPIPOK        0x000000C0
#घोषणा PCH_GBE_RXD_ACC_STAT_IPOK           0x00000080
#घोषणा PCH_GBE_RXD_ACC_STAT_TCPOK          0x00000040
#घोषणा PCH_GBE_RXD_ACC_STAT_IP6ERR         0x00000020
#घोषणा PCH_GBE_RXD_ACC_STAT_OFLIST         0x00000010
#घोषणा PCH_GBE_RXD_ACC_STAT_TYPEIP         0x00000008
#घोषणा PCH_GBE_RXD_ACC_STAT_MACL           0x00000004
#घोषणा PCH_GBE_RXD_ACC_STAT_PPPOE          0x00000002
#घोषणा PCH_GBE_RXD_ACC_STAT_VTAGT          0x00000001
#घोषणा PCH_GBE_RXD_GMAC_STAT_PAUSE         0x0200
#घोषणा PCH_GBE_RXD_GMAC_STAT_MARBR         0x0100
#घोषणा PCH_GBE_RXD_GMAC_STAT_MARMLT        0x0080
#घोषणा PCH_GBE_RXD_GMAC_STAT_MARIND        0x0040
#घोषणा PCH_GBE_RXD_GMAC_STAT_MARNOTMT      0x0020
#घोषणा PCH_GBE_RXD_GMAC_STAT_TLONG         0x0010
#घोषणा PCH_GBE_RXD_GMAC_STAT_TSHRT         0x0008
#घोषणा PCH_GBE_RXD_GMAC_STAT_NOTOCTAL      0x0004
#घोषणा PCH_GBE_RXD_GMAC_STAT_NBLERR        0x0002
#घोषणा PCH_GBE_RXD_GMAC_STAT_CRCERR        0x0001

/* Transmit Descriptor bit definitions */
#घोषणा PCH_GBE_TXD_CTRL_TCPIP_ACC_OFF      0x0008
#घोषणा PCH_GBE_TXD_CTRL_ITAG               0x0004
#घोषणा PCH_GBE_TXD_CTRL_ICRC               0x0002
#घोषणा PCH_GBE_TXD_CTRL_APAD               0x0001
#घोषणा PCH_GBE_TXD_WORDS_SHIFT             2
#घोषणा PCH_GBE_TXD_GMAC_STAT_CMPLT         0x2000
#घोषणा PCH_GBE_TXD_GMAC_STAT_ABT           0x1000
#घोषणा PCH_GBE_TXD_GMAC_STAT_EXCOL         0x0800
#घोषणा PCH_GBE_TXD_GMAC_STAT_SNGCOL        0x0400
#घोषणा PCH_GBE_TXD_GMAC_STAT_MLTCOL        0x0200
#घोषणा PCH_GBE_TXD_GMAC_STAT_CRSER         0x0100
#घोषणा PCH_GBE_TXD_GMAC_STAT_TLNG          0x0080
#घोषणा PCH_GBE_TXD_GMAC_STAT_TSHRT         0x0040
#घोषणा PCH_GBE_TXD_GMAC_STAT_LTCOL         0x0020
#घोषणा PCH_GBE_TXD_GMAC_STAT_TFUNDFLW      0x0010
#घोषणा PCH_GBE_TXD_GMAC_STAT_RTYCNT_MASK   0x000F

/* TX Mode */
#घोषणा PCH_GBE_TM_NO_RTRY     0x80000000 /* No Retransmission */
#घोषणा PCH_GBE_TM_LONG_PKT    0x40000000 /* Long Packt TX Enable */
#घोषणा PCH_GBE_TM_ST_AND_FD   0x20000000 /* Stare and Forward */
#घोषणा PCH_GBE_TM_SHORT_PKT   0x10000000 /* Short Packet TX Enable */
#घोषणा PCH_GBE_TM_LTCOL_RETX  0x08000000 /* Retransmission at Late Collision */
/* Frame Start Threshold */
#घोषणा PCH_GBE_TM_TH_TX_STRT_4    0x00000000    /* 4 words */
#घोषणा PCH_GBE_TM_TH_TX_STRT_8    0x00004000    /* 8 words */
#घोषणा PCH_GBE_TM_TH_TX_STRT_16   0x00008000    /* 16 words */
#घोषणा PCH_GBE_TM_TH_TX_STRT_32   0x0000C000    /* 32 words */
/* Transmit Almost Empty Threshold */
#घोषणा PCH_GBE_TM_TH_ALM_EMP_4    0x00000000    /* 4 words */
#घोषणा PCH_GBE_TM_TH_ALM_EMP_8    0x00000800    /* 8 words */
#घोषणा PCH_GBE_TM_TH_ALM_EMP_16   0x00001000    /* 16 words */
#घोषणा PCH_GBE_TM_TH_ALM_EMP_32   0x00001800    /* 32 words */
#घोषणा PCH_GBE_TM_TH_ALM_EMP_64   0x00002000    /* 64 words */
#घोषणा PCH_GBE_TM_TH_ALM_EMP_128  0x00002800    /* 128 words */
#घोषणा PCH_GBE_TM_TH_ALM_EMP_256  0x00003000    /* 256 words */
#घोषणा PCH_GBE_TM_TH_ALM_EMP_512  0x00003800    /* 512 words */
/* Transmit Almost Full Threshold */
#घोषणा PCH_GBE_TM_TH_ALM_FULL_4   0x00000000    /* 4 words */
#घोषणा PCH_GBE_TM_TH_ALM_FULL_8   0x00000200    /* 8 words */
#घोषणा PCH_GBE_TM_TH_ALM_FULL_16  0x00000400    /* 16 words */
#घोषणा PCH_GBE_TM_TH_ALM_FULL_32  0x00000600    /* 32 words */

/* RX FIFO Status */
#घोषणा PCH_GBE_RF_ALM_FULL     0x80000000  /* RX FIFO is almost full. */
#घोषणा PCH_GBE_RF_ALM_EMP      0x40000000  /* RX FIFO is almost empty. */
#घोषणा PCH_GBE_RF_RD_TRG       0x20000000  /* Become more than RH_RD_TRG. */
#घोषणा PCH_GBE_RF_STRWD        0x1FFE0000  /* The word count of RX FIFO. */
#घोषणा PCH_GBE_RF_RCVING       0x00010000  /* Stored in RX FIFO. */

/* MAC Address Mask */
#घोषणा PCH_GBE_BUSY                0x80000000

/* MIIM  */
#घोषणा PCH_GBE_MIIM_OPER_WRITE     0x04000000
#घोषणा PCH_GBE_MIIM_OPER_READ      0x00000000
#घोषणा PCH_GBE_MIIM_OPER_READY     0x04000000
#घोषणा PCH_GBE_MIIM_PHY_ADDR_SHIFT 21
#घोषणा PCH_GBE_MIIM_REG_ADDR_SHIFT 16

/* RGMII Status */
#घोषणा PCH_GBE_LINK_UP             0x80000008
#घोषणा PCH_GBE_RXC_SPEED_MSK       0x00000006
#घोषणा PCH_GBE_RXC_SPEED_2_5M      0x00000000    /* 2.5MHz */
#घोषणा PCH_GBE_RXC_SPEED_25M       0x00000002    /* 25MHz  */
#घोषणा PCH_GBE_RXC_SPEED_125M      0x00000004    /* 100MHz */
#घोषणा PCH_GBE_DUPLEX_FULL         0x00000001

/* RGMII Control */
#घोषणा PCH_GBE_CRS_SEL             0x00000010
#घोषणा PCH_GBE_RGMII_RATE_125M     0x00000000
#घोषणा PCH_GBE_RGMII_RATE_25M      0x00000008
#घोषणा PCH_GBE_RGMII_RATE_2_5M     0x0000000C
#घोषणा PCH_GBE_RGMII_MODE_GMII     0x00000000
#घोषणा PCH_GBE_RGMII_MODE_RGMII    0x00000002
#घोषणा PCH_GBE_CHIP_TYPE_EXTERNAL  0x00000000
#घोषणा PCH_GBE_CHIP_TYPE_INTERNAL  0x00000001

/* DMA Control */
#घोषणा PCH_GBE_RX_DMA_EN       0x00000002   /* Enables Receive DMA */
#घोषणा PCH_GBE_TX_DMA_EN       0x00000001   /* Enables Transmission DMA */

/* RX DMA STATUS */
#घोषणा PCH_GBE_IDLE_CHECK       0xFFFFFFFE

/* Wake On LAN Status */
#घोषणा PCH_GBE_WLS_BR          0x00000008 /* Broadcas Address */
#घोषणा PCH_GBE_WLS_MLT         0x00000004 /* Multicast Address */

/* The Frame रेजिस्टरed in Address Recognizer */
#घोषणा PCH_GBE_WLS_IND         0x00000002
#घोषणा PCH_GBE_WLS_MP          0x00000001 /* Magic packet Address */

/* Wake On LAN Control */
#घोषणा PCH_GBE_WLC_WOL_MODE    0x00010000
#घोषणा PCH_GBE_WLC_IGN_TLONG   0x00000100
#घोषणा PCH_GBE_WLC_IGN_TSHRT   0x00000080
#घोषणा PCH_GBE_WLC_IGN_OCTER   0x00000040
#घोषणा PCH_GBE_WLC_IGN_NBLER   0x00000020
#घोषणा PCH_GBE_WLC_IGN_CRCER   0x00000010
#घोषणा PCH_GBE_WLC_BR          0x00000008
#घोषणा PCH_GBE_WLC_MLT         0x00000004
#घोषणा PCH_GBE_WLC_IND         0x00000002
#घोषणा PCH_GBE_WLC_MP          0x00000001

/* Wake On LAN Address Mask */
#घोषणा PCH_GBE_WLA_BUSY        0x80000000



/* TX/RX descriptor defines */
#घोषणा PCH_GBE_MAX_TXD                     4096
#घोषणा PCH_GBE_DEFAULT_TXD                  256
#घोषणा PCH_GBE_MIN_TXD                        8
#घोषणा PCH_GBE_MAX_RXD                     4096
#घोषणा PCH_GBE_DEFAULT_RXD                  256
#घोषणा PCH_GBE_MIN_RXD                        8

/* Number of Transmit and Receive Descriptors must be a multiple of 8 */
#घोषणा PCH_GBE_TX_DESC_MULTIPLE               8
#घोषणा PCH_GBE_RX_DESC_MULTIPLE               8

/* Read/Write operation is करोne through MII Management IF */
#घोषणा PCH_GBE_HAL_MIIM_READ          ((u32)0x00000000)
#घोषणा PCH_GBE_HAL_MIIM_WRITE         ((u32)0x04000000)

/* flow control values */
#घोषणा PCH_GBE_FC_NONE			0
#घोषणा PCH_GBE_FC_RX_PAUSE		1
#घोषणा PCH_GBE_FC_TX_PAUSE		2
#घोषणा PCH_GBE_FC_FULL			3
#घोषणा PCH_GBE_FC_DEFAULT		PCH_GBE_FC_FULL

/**
 * काष्ठा pch_gbe_mac_info - MAC inक्रमmation
 * @addr[6]:		Store the MAC address
 * @fc:			Mode of flow control
 * @fc_स्वतःneg:		Auto negotiation enable क्रम flow control setting
 * @tx_fc_enable:	Enable flag of Transmit flow control
 * @max_frame_size:	Max transmit frame size
 * @min_frame_size:	Min transmit frame size
 * @स्वतःneg:		Auto negotiation enable
 * @link_speed:		Link speed
 * @link_duplex:	Link duplex
 */
काष्ठा pch_gbe_mac_info अणु
	u8 addr[6];
	u8 fc;
	u8 fc_स्वतःneg;
	u8 tx_fc_enable;
	u32 max_frame_size;
	u32 min_frame_size;
	u8 स्वतःneg;
	u16 link_speed;
	u16 link_duplex;
पूर्ण;

/**
 * काष्ठा pch_gbe_phy_info - PHY inक्रमmation
 * @addr:		PHY address
 * @id:			PHY's identअगरier
 * @revision:		PHY's revision
 * @reset_delay_us:	HW reset delay समय[us]
 * @स्वतःneg_advertised:	Autoneg advertised
 */
काष्ठा pch_gbe_phy_info अणु
	u32 addr;
	u32 id;
	u32 revision;
	u32 reset_delay_us;
	u16 स्वतःneg_advertised;
पूर्ण;

/*!
 * @ingroup Gigabit Ether driver Layer
 * @काष्ठा  pch_gbe_hw
 * @brief   Hardware inक्रमmation
 */
काष्ठा pch_gbe_hw अणु
	व्योम *back;

	काष्ठा pch_gbe_regs  __iomem *reg;
	spinlock_t miim_lock;

	काष्ठा pch_gbe_mac_info mac;
	काष्ठा pch_gbe_phy_info phy;
पूर्ण;

/**
 * काष्ठा pch_gbe_rx_desc - Receive Descriptor
 * @buffer_addr:	RX Frame Buffer Address
 * @tcp_ip_status:	TCP/IP Accelerator Status
 * @rx_words_eob:	RX word count and Byte position
 * @gbec_status:	GMAC Status
 * @dma_status:		DMA Status
 * @reserved1:		Reserved
 * @reserved2:		Reserved
 */
काष्ठा pch_gbe_rx_desc अणु
	u32 buffer_addr;
	u32 tcp_ip_status;
	u16 rx_words_eob;
	u16 gbec_status;
	u8 dma_status;
	u8 reserved1;
	u16 reserved2;
पूर्ण;

/**
 * काष्ठा pch_gbe_tx_desc - Transmit Descriptor
 * @buffer_addr:	TX Frame Buffer Address
 * @length:		Data buffer length
 * @reserved1:		Reserved
 * @tx_words_eob:	TX word count and Byte position
 * @tx_frame_ctrl:	TX Frame Control
 * @dma_status:		DMA Status
 * @reserved2:		Reserved
 * @gbec_status:	GMAC Status
 */
काष्ठा pch_gbe_tx_desc अणु
	u32 buffer_addr;
	u16 length;
	u16 reserved1;
	u16 tx_words_eob;
	u16 tx_frame_ctrl;
	u8 dma_status;
	u8 reserved2;
	u16 gbec_status;
पूर्ण;


/**
 * काष्ठा pch_gbe_buffer - Buffer inक्रमmation
 * @skb:	poपूर्णांकer to a socket buffer
 * @dma:	DMA address
 * @समय_stamp:	समय stamp
 * @length:	data size
 */
काष्ठा pch_gbe_buffer अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
	अचिन्हित अक्षर *rx_buffer;
	अचिन्हित दीर्घ समय_stamp;
	u16 length;
	bool mapped;
पूर्ण;

/**
 * काष्ठा pch_gbe_tx_ring - tx ring inक्रमmation
 * @desc:	poपूर्णांकer to the descriptor ring memory
 * @dma:	physical address of the descriptor ring
 * @size:	length of descriptor ring in bytes
 * @count:	number of descriptors in the ring
 * @next_to_use:	next descriptor to associate a buffer with
 * @next_to_clean:	next descriptor to check क्रम DD status bit
 * @buffer_info:	array of buffer inक्रमmation काष्ठाs
 */
काष्ठा pch_gbe_tx_ring अणु
	काष्ठा pch_gbe_tx_desc *desc;
	dma_addr_t dma;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक next_to_use;
	अचिन्हित पूर्णांक next_to_clean;
	काष्ठा pch_gbe_buffer *buffer_info;
पूर्ण;

/**
 * काष्ठा pch_gbe_rx_ring - rx ring inक्रमmation
 * @desc:	poपूर्णांकer to the descriptor ring memory
 * @dma:	physical address of the descriptor ring
 * @size:	length of descriptor ring in bytes
 * @count:	number of descriptors in the ring
 * @next_to_use:	next descriptor to associate a buffer with
 * @next_to_clean:	next descriptor to check क्रम DD status bit
 * @buffer_info:	array of buffer inक्रमmation काष्ठाs
 */
काष्ठा pch_gbe_rx_ring अणु
	काष्ठा pch_gbe_rx_desc *desc;
	dma_addr_t dma;
	अचिन्हित अक्षर *rx_buff_pool;
	dma_addr_t rx_buff_pool_logic;
	अचिन्हित पूर्णांक rx_buff_pool_size;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक next_to_use;
	अचिन्हित पूर्णांक next_to_clean;
	काष्ठा pch_gbe_buffer *buffer_info;
पूर्ण;

/**
 * काष्ठा pch_gbe_hw_stats - Statistics counters collected by the MAC
 * @rx_packets:		    total packets received
 * @tx_packets:		    total packets transmitted
 * @rx_bytes:		    total bytes received
 * @tx_bytes:		    total bytes transmitted
 * @rx_errors:		    bad packets received
 * @tx_errors:		    packet transmit problems
 * @rx_dropped:		    no space in Linux buffers
 * @tx_dropped:		    no space available in Linux
 * @multicast:		    multicast packets received
 * @collisions:		    collisions
 * @rx_crc_errors:	    received packet with crc error
 * @rx_frame_errors:	    received frame alignment error
 * @rx_alloc_buff_failed:   allocate failure of a receive buffer
 * @tx_length_errors:	    transmit length error
 * @tx_पातed_errors:	    transmit पातed error
 * @tx_carrier_errors:	    transmit carrier error
 * @tx_समयout_count:	    Number of transmit समयout
 * @tx_restart_count:	    Number of transmit restert
 * @पूर्णांकr_rx_dsc_empty_count:	Interrupt count of receive descriptor empty
 * @पूर्णांकr_rx_frame_err_count:	Interrupt count of receive frame error
 * @पूर्णांकr_rx_fअगरo_err_count:	Interrupt count of receive FIFO error
 * @पूर्णांकr_rx_dma_err_count:	Interrupt count of receive DMA error
 * @पूर्णांकr_tx_fअगरo_err_count:	Interrupt count of transmit FIFO error
 * @पूर्णांकr_tx_dma_err_count:	Interrupt count of transmit DMA error
 * @पूर्णांकr_tcpip_err_count:	Interrupt count of TCP/IP Accelerator
 */
काष्ठा pch_gbe_hw_stats अणु
	u32 rx_packets;
	u32 tx_packets;
	u32 rx_bytes;
	u32 tx_bytes;
	u32 rx_errors;
	u32 tx_errors;
	u32 rx_dropped;
	u32 tx_dropped;
	u32 multicast;
	u32 collisions;
	u32 rx_crc_errors;
	u32 rx_frame_errors;
	u32 rx_alloc_buff_failed;
	u32 tx_length_errors;
	u32 tx_पातed_errors;
	u32 tx_carrier_errors;
	u32 tx_समयout_count;
	u32 tx_restart_count;
	u32 पूर्णांकr_rx_dsc_empty_count;
	u32 पूर्णांकr_rx_frame_err_count;
	u32 पूर्णांकr_rx_fअगरo_err_count;
	u32 पूर्णांकr_rx_dma_err_count;
	u32 पूर्णांकr_tx_fअगरo_err_count;
	u32 पूर्णांकr_tx_dma_err_count;
	u32 पूर्णांकr_tcpip_err_count;
पूर्ण;

/**
 * काष्ठा pch_gbe_privdata - PCI Device ID driver data
 * @phy_tx_clk_delay:		Bool, configure the PHY TX delay in software
 * @phy_disable_hibernate:	Bool, disable PHY hibernation
 * @platक्रमm_init:		Platक्रमm initialization callback, called from
 *				probe, prior to PHY initialization.
 */
काष्ठा pch_gbe_privdata अणु
	bool phy_tx_clk_delay;
	bool phy_disable_hibernate;
	पूर्णांक (*platक्रमm_init)(काष्ठा pci_dev *pdev);
पूर्ण;

/**
 * काष्ठा pch_gbe_adapter - board specअगरic निजी data काष्ठाure
 * @stats_lock:	Spinlock काष्ठाure क्रम status
 * @ethtool_lock:	Spinlock काष्ठाure क्रम ethtool
 * @irq_sem:		Semaphore क्रम पूर्णांकerrupt
 * @netdev:		Poपूर्णांकer of network device काष्ठाure
 * @pdev:		Poपूर्णांकer of pci device काष्ठाure
 * @polling_netdev:	Poपूर्णांकer of polling network device काष्ठाure
 * @napi:		NAPI काष्ठाure
 * @hw:			Poपूर्णांकer of hardware काष्ठाure
 * @stats:		Hardware status
 * @reset_task:		Reset task
 * @mii:		MII inक्रमmation काष्ठाure
 * @watchकरोg_समयr:	Watchकरोg समयr list
 * @wake_up_evt:	Wake up event
 * @config_space:	Configuration space
 * @msg_enable:		Driver message level
 * @led_status:		LED status
 * @tx_ring:		Poपूर्णांकer of Tx descriptor ring काष्ठाure
 * @rx_ring:		Poपूर्णांकer of Rx descriptor ring काष्ठाure
 * @rx_buffer_len:	Receive buffer length
 * @tx_queue_len:	Transmit queue length
 * @pch_gbe_privdata:	PCI Device ID driver_data
 */

काष्ठा pch_gbe_adapter अणु
	spinlock_t stats_lock;
	spinlock_t ethtool_lock;
	atomic_t irq_sem;
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;
	पूर्णांक irq;
	काष्ठा net_device *polling_netdev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा pch_gbe_hw hw;
	काष्ठा pch_gbe_hw_stats stats;
	काष्ठा work_काष्ठा reset_task;
	काष्ठा mii_अगर_info mii;
	काष्ठा समयr_list watchकरोg_समयr;
	u32 wake_up_evt;
	u32 *config_space;
	अचिन्हित दीर्घ led_status;
	काष्ठा pch_gbe_tx_ring *tx_ring;
	काष्ठा pch_gbe_rx_ring *rx_ring;
	अचिन्हित दीर्घ rx_buffer_len;
	अचिन्हित दीर्घ tx_queue_len;
	bool rx_stop_flag;
	पूर्णांक hwts_tx_en;
	पूर्णांक hwts_rx_en;
	काष्ठा pci_dev *ptp_pdev;
	काष्ठा pch_gbe_privdata *pdata;
पूर्ण;

#घोषणा pch_gbe_hw_to_adapter(hw)	container_of(hw, काष्ठा pch_gbe_adapter, hw)

बाह्य स्थिर अक्षर pch_driver_version[];

/* pch_gbe_मुख्य.c */
पूर्णांक pch_gbe_up(काष्ठा pch_gbe_adapter *adapter);
व्योम pch_gbe_करोwn(काष्ठा pch_gbe_adapter *adapter);
व्योम pch_gbe_reinit_locked(काष्ठा pch_gbe_adapter *adapter);
व्योम pch_gbe_reset(काष्ठा pch_gbe_adapter *adapter);
पूर्णांक pch_gbe_setup_tx_resources(काष्ठा pch_gbe_adapter *adapter,
			       काष्ठा pch_gbe_tx_ring *txdr);
पूर्णांक pch_gbe_setup_rx_resources(काष्ठा pch_gbe_adapter *adapter,
			       काष्ठा pch_gbe_rx_ring *rxdr);
व्योम pch_gbe_मुक्त_tx_resources(काष्ठा pch_gbe_adapter *adapter,
			       काष्ठा pch_gbe_tx_ring *tx_ring);
व्योम pch_gbe_मुक्त_rx_resources(काष्ठा pch_gbe_adapter *adapter,
			       काष्ठा pch_gbe_rx_ring *rx_ring);
व्योम pch_gbe_update_stats(काष्ठा pch_gbe_adapter *adapter);

/* pch_gbe_param.c */
व्योम pch_gbe_check_options(काष्ठा pch_gbe_adapter *adapter);

/* pch_gbe_ethtool.c */
व्योम pch_gbe_set_ethtool_ops(काष्ठा net_device *netdev);

/* pch_gbe_mac.c */
s32 pch_gbe_mac_क्रमce_mac_fc(काष्ठा pch_gbe_hw *hw);
u16 pch_gbe_mac_ctrl_miim(काष्ठा pch_gbe_hw *hw, u32 addr, u32 dir, u32 reg,
			  u16 data);
#पूर्ण_अगर /* _PCH_GBE_H_ */
