<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000_DEFINES_H_
#घोषणा _E1000_DEFINES_H_

/* Number of Transmit and Receive Descriptors must be a multiple of 8 */
#घोषणा REQ_TX_DESCRIPTOR_MULTIPLE	8
#घोषणा REQ_RX_DESCRIPTOR_MULTIPLE	8

/* IVAR valid bit */
#घोषणा E1000_IVAR_VALID	0x80

/* Receive Descriptor bit definitions */
#घोषणा E1000_RXD_STAT_DD	0x01    /* Descriptor Done */
#घोषणा E1000_RXD_STAT_EOP	0x02    /* End of Packet */
#घोषणा E1000_RXD_STAT_IXSM	0x04    /* Ignore checksum */
#घोषणा E1000_RXD_STAT_VP	0x08    /* IEEE VLAN Packet */
#घोषणा E1000_RXD_STAT_UDPCS	0x10    /* UDP xsum calculated */
#घोषणा E1000_RXD_STAT_TCPCS	0x20    /* TCP xsum calculated */
#घोषणा E1000_RXD_STAT_IPCS	0x40    /* IP xsum calculated */
#घोषणा E1000_RXD_ERR_SE	0x02    /* Symbol Error */
#घोषणा E1000_RXD_SPC_VLAN_MASK	0x0FFF  /* VLAN ID is in lower 12 bits */

#घोषणा E1000_RXDEXT_STATERR_LB	0x00040000
#घोषणा E1000_RXDEXT_STATERR_CE	0x01000000
#घोषणा E1000_RXDEXT_STATERR_SE	0x02000000
#घोषणा E1000_RXDEXT_STATERR_SEQ	0x04000000
#घोषणा E1000_RXDEXT_STATERR_CXE	0x10000000
#घोषणा E1000_RXDEXT_STATERR_TCPE	0x20000000
#घोषणा E1000_RXDEXT_STATERR_IPE	0x40000000
#घोषणा E1000_RXDEXT_STATERR_RXE	0x80000000

/* Same mask, but क्रम extended and packet split descriptors */
#घोषणा E1000_RXDEXT_ERR_FRAME_ERR_MASK ( \
	E1000_RXDEXT_STATERR_CE  | \
	E1000_RXDEXT_STATERR_SE  | \
	E1000_RXDEXT_STATERR_SEQ | \
	E1000_RXDEXT_STATERR_CXE | \
	E1000_RXDEXT_STATERR_RXE)

/* Device Control */
#घोषणा E1000_CTRL_RST		0x04000000  /* Global reset */

/* Device Status */
#घोषणा E1000_STATUS_FD		0x00000001      /* Full duplex.0=half,1=full */
#घोषणा E1000_STATUS_LU		0x00000002      /* Link up.0=no,1=link */
#घोषणा E1000_STATUS_TXOFF	0x00000010      /* transmission छोड़ोd */
#घोषणा E1000_STATUS_SPEED_10	0x00000000      /* Speed 10Mb/s */
#घोषणा E1000_STATUS_SPEED_100	0x00000040      /* Speed 100Mb/s */
#घोषणा E1000_STATUS_SPEED_1000	0x00000080      /* Speed 1000Mb/s */

#घोषणा SPEED_10	10
#घोषणा SPEED_100	100
#घोषणा SPEED_1000	1000
#घोषणा HALF_DUPLEX	1
#घोषणा FULL_DUPLEX	2

/* Transmit Descriptor bit definitions */
#घोषणा E1000_TXD_POPTS_IXSM	0x01       /* Insert IP checksum */
#घोषणा E1000_TXD_POPTS_TXSM	0x02       /* Insert TCP/UDP checksum */
#घोषणा E1000_TXD_CMD_DEXT	0x20000000 /* Desc extension (0 = legacy) */
#घोषणा E1000_TXD_STAT_DD	0x00000001 /* Desc Done */

#घोषणा MAX_JUMBO_FRAME_SIZE		0x3F00
#घोषणा MAX_STD_JUMBO_FRAME_SIZE	9216

/* 802.1q VLAN Packet Size */
#घोषणा VLAN_TAG_SIZE		4    /* 802.3ac tag (not DMA'd) */

/* Error Codes */
#घोषणा E1000_SUCCESS		0
#घोषणा E1000_ERR_CONFIG	3
#घोषणा E1000_ERR_MAC_INIT	5
#घोषणा E1000_ERR_MBX		15

/* SRRCTL bit definitions */
#घोषणा E1000_SRRCTL_BSIZEPKT_SHIFT		10 /* Shअगरt _right_ */
#घोषणा E1000_SRRCTL_BSIZEHDRSIZE_MASK		0x00000F00
#घोषणा E1000_SRRCTL_BSIZEHDRSIZE_SHIFT		2  /* Shअगरt _left_ */
#घोषणा E1000_SRRCTL_DESCTYPE_ADV_ONEBUF	0x02000000
#घोषणा E1000_SRRCTL_DESCTYPE_HDR_SPLIT_ALWAYS	0x0A000000
#घोषणा E1000_SRRCTL_DESCTYPE_MASK		0x0E000000
#घोषणा E1000_SRRCTL_DROP_EN			0x80000000

#घोषणा E1000_SRRCTL_BSIZEPKT_MASK	0x0000007F
#घोषणा E1000_SRRCTL_BSIZEHDR_MASK	0x00003F00

/* Additional Descriptor Control definitions */
#घोषणा E1000_TXDCTL_QUEUE_ENABLE	0x02000000 /* Enable specअगरic Tx Que */
#घोषणा E1000_RXDCTL_QUEUE_ENABLE	0x02000000 /* Enable specअगरic Rx Que */

/* Direct Cache Access (DCA) definitions */
#घोषणा E1000_DCA_TXCTRL_TX_WB_RO_EN	BIT(11) /* Tx Desc ग_लिखोback RO bit */

#घोषणा E1000_VF_INIT_TIMEOUT	200 /* Number of retries to clear RSTI */

#पूर्ण_अगर /* _E1000_DEFINES_H_ */
