<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2008 Intel Corporation. */

#अगर_अघोषित _IXGB_HW_H_
#घोषणा _IXGB_HW_H_

#समावेश <linux/mdपन.स>

#समावेश "ixgb_osdep.h"

/* Enums */
प्रकार क्रमागत अणु
	ixgb_mac_unknown = 0,
	ixgb_82597,
	ixgb_num_macs
पूर्ण ixgb_mac_type;

/* Types of physical layer modules */
प्रकार क्रमागत अणु
	ixgb_phy_type_unknown = 0,
	ixgb_phy_type_g6005,	/* 850nm, MM fiber, XPAK transceiver */
	ixgb_phy_type_g6104,	/* 1310nm, SM fiber, XPAK transceiver */
	ixgb_phy_type_txn17201,	/* 850nm, MM fiber, XPAK transceiver */
	ixgb_phy_type_txn17401,	/* 1310nm, SM fiber, XENPAK transceiver */
	ixgb_phy_type_bcm	/* SUN specअगरic board */
पूर्ण ixgb_phy_type;

/* XPAK transceiver venकरोrs, क्रम the SR adapters */
प्रकार क्रमागत अणु
	ixgb_xpak_venकरोr_पूर्णांकel,
	ixgb_xpak_venकरोr_infineon
पूर्ण ixgb_xpak_venकरोr;

/* Media Types */
प्रकार क्रमागत अणु
	ixgb_media_type_unknown = 0,
	ixgb_media_type_fiber = 1,
	ixgb_media_type_copper = 2,
	ixgb_num_media_types
पूर्ण ixgb_media_type;

/* Flow Control Settings */
प्रकार क्रमागत अणु
	ixgb_fc_none = 0,
	ixgb_fc_rx_छोड़ो = 1,
	ixgb_fc_tx_छोड़ो = 2,
	ixgb_fc_full = 3,
	ixgb_fc_शेष = 0xFF
पूर्ण ixgb_fc_type;

/* PCI bus types */
प्रकार क्रमागत अणु
	ixgb_bus_type_unknown = 0,
	ixgb_bus_type_pci,
	ixgb_bus_type_pcix
पूर्ण ixgb_bus_type;

/* PCI bus speeds */
प्रकार क्रमागत अणु
	ixgb_bus_speed_unknown = 0,
	ixgb_bus_speed_33,
	ixgb_bus_speed_66,
	ixgb_bus_speed_100,
	ixgb_bus_speed_133,
	ixgb_bus_speed_reserved
पूर्ण ixgb_bus_speed;

/* PCI bus widths */
प्रकार क्रमागत अणु
	ixgb_bus_width_unknown = 0,
	ixgb_bus_width_32,
	ixgb_bus_width_64
पूर्ण ixgb_bus_width;

#घोषणा IXGB_EEPROM_SIZE    64	/* Size in words */

#घोषणा SPEED_10000  10000
#घोषणा FULL_DUPLEX  2

#घोषणा MIN_NUMBER_OF_DESCRIPTORS       8
#घोषणा MAX_NUMBER_OF_DESCRIPTORS  0xFFF8	/* 13 bits in RDLEN/TDLEN, 128B aligned     */

#घोषणा IXGB_DELAY_BEFORE_RESET        10	/* allow 10ms after idling rx/tx units      */
#घोषणा IXGB_DELAY_AFTER_RESET          1	/* allow 1ms after the reset                */
#घोषणा IXGB_DELAY_AFTER_EE_RESET      10	/* allow 10ms after the EEPROM reset        */

#घोषणा IXGB_DELAY_USECS_AFTER_LINK_RESET    13	/* allow 13 microseconds after the reset    */
					   /* NOTE: this is MICROSECONDS               */
#घोषणा MAX_RESET_ITERATIONS            8	/* number of iterations to get things right */

/* General Registers */
#घोषणा IXGB_CTRL0   0x00000	/* Device Control Register 0 - RW */
#घोषणा IXGB_CTRL1   0x00008	/* Device Control Register 1 - RW */
#घोषणा IXGB_STATUS  0x00010	/* Device Status Register - RO */
#घोषणा IXGB_EECD    0x00018	/* EEPROM/Flash Control/Data Register - RW */
#घोषणा IXGB_MFS     0x00020	/* Maximum Frame Size - RW */

/* Interrupt */
#घोषणा IXGB_ICR     0x00080	/* Interrupt Cause Read - R/clr */
#घोषणा IXGB_ICS     0x00088	/* Interrupt Cause Set - RW */
#घोषणा IXGB_IMS     0x00090	/* Interrupt Mask Set/Read - RW */
#घोषणा IXGB_IMC     0x00098	/* Interrupt Mask Clear - WO */

/* Receive */
#घोषणा IXGB_RCTL    0x00100	/* RX Control - RW */
#घोषणा IXGB_FCRTL   0x00108	/* Flow Control Receive Threshold Low - RW */
#घोषणा IXGB_FCRTH   0x00110	/* Flow Control Receive Threshold High - RW */
#घोषणा IXGB_RDBAL   0x00118	/* RX Descriptor Base Low - RW */
#घोषणा IXGB_RDBAH   0x0011C	/* RX Descriptor Base High - RW */
#घोषणा IXGB_RDLEN   0x00120	/* RX Descriptor Length - RW */
#घोषणा IXGB_RDH     0x00128	/* RX Descriptor Head - RW */
#घोषणा IXGB_RDT     0x00130	/* RX Descriptor Tail - RW */
#घोषणा IXGB_RDTR    0x00138	/* RX Delay Timer Ring - RW */
#घोषणा IXGB_RXDCTL  0x00140	/* Receive Descriptor Control - RW */
#घोषणा IXGB_RAIDC   0x00148	/* Receive Adaptive Interrupt Delay Control - RW */
#घोषणा IXGB_RXCSUM  0x00158	/* Receive Checksum Control - RW */
#घोषणा IXGB_RA      0x00180	/* Receive Address Array Base - RW */
#घोषणा IXGB_RAL     0x00180	/* Receive Address Low [0:15] - RW */
#घोषणा IXGB_RAH     0x00184	/* Receive Address High [0:15] - RW */
#घोषणा IXGB_MTA     0x00200	/* Multicast Table Array [0:127] - RW */
#घोषणा IXGB_VFTA    0x00400	/* VLAN Filter Table Array [0:127] - RW */
#घोषणा IXGB_REQ_RX_DESCRIPTOR_MULTIPLE 8

/* Transmit */
#घोषणा IXGB_TCTL    0x00600	/* TX Control - RW */
#घोषणा IXGB_TDBAL   0x00608	/* TX Descriptor Base Low - RW */
#घोषणा IXGB_TDBAH   0x0060C	/* TX Descriptor Base High - RW */
#घोषणा IXGB_TDLEN   0x00610	/* TX Descriptor Length - RW */
#घोषणा IXGB_TDH     0x00618	/* TX Descriptor Head - RW */
#घोषणा IXGB_TDT     0x00620	/* TX Descriptor Tail - RW */
#घोषणा IXGB_TIDV    0x00628	/* TX Interrupt Delay Value - RW */
#घोषणा IXGB_TXDCTL  0x00630	/* Transmit Descriptor Control - RW */
#घोषणा IXGB_TSPMT   0x00638	/* TCP Segmentation PAD & Min Threshold - RW */
#घोषणा IXGB_PAP     0x00640	/* Pause and Pace - RW */
#घोषणा IXGB_REQ_TX_DESCRIPTOR_MULTIPLE 8

/* Physical */
#घोषणा IXGB_PCSC1   0x00700	/* PCS Control 1 - RW */
#घोषणा IXGB_PCSC2   0x00708	/* PCS Control 2 - RW */
#घोषणा IXGB_PCSS1   0x00710	/* PCS Status 1 - RO */
#घोषणा IXGB_PCSS2   0x00718	/* PCS Status 2 - RO */
#घोषणा IXGB_XPCSS   0x00720	/* 10GBASE-X PCS Status (or XGXS Lane Status) - RO */
#घोषणा IXGB_UCCR    0x00728	/* Unilink Circuit Control Register */
#घोषणा IXGB_XPCSTC  0x00730	/* 10GBASE-X PCS Test Control */
#घोषणा IXGB_MACA    0x00738	/* MDI Autoscan Command and Address - RW */
#घोषणा IXGB_APAE    0x00740	/* Autoscan PHY Address Enable - RW */
#घोषणा IXGB_ARD     0x00748	/* Autoscan Read Data - RO */
#घोषणा IXGB_AIS     0x00750	/* Autoscan Interrupt Status - RO */
#घोषणा IXGB_MSCA    0x00758	/* MDI Single Command and Address - RW */
#घोषणा IXGB_MSRWD   0x00760	/* MDI Single Read and Write Data - RW, RO */

/* Wake-up */
#घोषणा IXGB_WUFC    0x00808	/* Wake Up Filter Control - RW */
#घोषणा IXGB_WUS     0x00810	/* Wake Up Status - RO */
#घोषणा IXGB_FFLT    0x01000	/* Flexible Filter Length Table - RW */
#घोषणा IXGB_FFMT    0x01020	/* Flexible Filter Mask Table - RW */
#घोषणा IXGB_FTVT    0x01420	/* Flexible Filter Value Table - RW */

/* Statistics */
#घोषणा IXGB_TPRL    0x02000	/* Total Packets Received (Low) */
#घोषणा IXGB_TPRH    0x02004	/* Total Packets Received (High) */
#घोषणा IXGB_GPRCL   0x02008	/* Good Packets Received Count (Low) */
#घोषणा IXGB_GPRCH   0x0200C	/* Good Packets Received Count (High) */
#घोषणा IXGB_BPRCL   0x02010	/* Broadcast Packets Received Count (Low) */
#घोषणा IXGB_BPRCH   0x02014	/* Broadcast Packets Received Count (High) */
#घोषणा IXGB_MPRCL   0x02018	/* Multicast Packets Received Count (Low) */
#घोषणा IXGB_MPRCH   0x0201C	/* Multicast Packets Received Count (High) */
#घोषणा IXGB_UPRCL   0x02020	/* Unicast Packets Received Count (Low) */
#घोषणा IXGB_UPRCH   0x02024	/* Unicast Packets Received Count (High) */
#घोषणा IXGB_VPRCL   0x02028	/* VLAN Packets Received Count (Low) */
#घोषणा IXGB_VPRCH   0x0202C	/* VLAN Packets Received Count (High) */
#घोषणा IXGB_JPRCL   0x02030	/* Jumbo Packets Received Count (Low) */
#घोषणा IXGB_JPRCH   0x02034	/* Jumbo Packets Received Count (High) */
#घोषणा IXGB_GORCL   0x02038	/* Good Octets Received Count (Low) */
#घोषणा IXGB_GORCH   0x0203C	/* Good Octets Received Count (High) */
#घोषणा IXGB_TORL    0x02040	/* Total Octets Received (Low) */
#घोषणा IXGB_TORH    0x02044	/* Total Octets Received (High) */
#घोषणा IXGB_RNBC    0x02048	/* Receive No Buffers Count */
#घोषणा IXGB_RUC     0x02050	/* Receive Undersize Count */
#घोषणा IXGB_ROC     0x02058	/* Receive Oversize Count */
#घोषणा IXGB_RLEC    0x02060	/* Receive Length Error Count */
#घोषणा IXGB_CRCERRS 0x02068	/* CRC Error Count */
#घोषणा IXGB_ICBC    0x02070	/* Illegal control byte in mid-packet Count */
#घोषणा IXGB_ECBC    0x02078	/* Error Control byte in mid-packet Count */
#घोषणा IXGB_MPC     0x02080	/* Missed Packets Count */
#घोषणा IXGB_TPTL    0x02100	/* Total Packets Transmitted (Low) */
#घोषणा IXGB_TPTH    0x02104	/* Total Packets Transmitted (High) */
#घोषणा IXGB_GPTCL   0x02108	/* Good Packets Transmitted Count (Low) */
#घोषणा IXGB_GPTCH   0x0210C	/* Good Packets Transmitted Count (High) */
#घोषणा IXGB_BPTCL   0x02110	/* Broadcast Packets Transmitted Count (Low) */
#घोषणा IXGB_BPTCH   0x02114	/* Broadcast Packets Transmitted Count (High) */
#घोषणा IXGB_MPTCL   0x02118	/* Multicast Packets Transmitted Count (Low) */
#घोषणा IXGB_MPTCH   0x0211C	/* Multicast Packets Transmitted Count (High) */
#घोषणा IXGB_UPTCL   0x02120	/* Unicast Packets Transmitted Count (Low) */
#घोषणा IXGB_UPTCH   0x02124	/* Unicast Packets Transmitted Count (High) */
#घोषणा IXGB_VPTCL   0x02128	/* VLAN Packets Transmitted Count (Low) */
#घोषणा IXGB_VPTCH   0x0212C	/* VLAN Packets Transmitted Count (High) */
#घोषणा IXGB_JPTCL   0x02130	/* Jumbo Packets Transmitted Count (Low) */
#घोषणा IXGB_JPTCH   0x02134	/* Jumbo Packets Transmitted Count (High) */
#घोषणा IXGB_GOTCL   0x02138	/* Good Octets Transmitted Count (Low) */
#घोषणा IXGB_GOTCH   0x0213C	/* Good Octets Transmitted Count (High) */
#घोषणा IXGB_TOTL    0x02140	/* Total Octets Transmitted Count (Low) */
#घोषणा IXGB_TOTH    0x02144	/* Total Octets Transmitted Count (High) */
#घोषणा IXGB_DC      0x02148	/* Defer Count */
#घोषणा IXGB_PLT64C  0x02150	/* Packet Transmitted was less than 64 bytes Count */
#घोषणा IXGB_TSCTC   0x02170	/* TCP Segmentation Context Transmitted Count */
#घोषणा IXGB_TSCTFC  0x02178	/* TCP Segmentation Context Tx Fail Count */
#घोषणा IXGB_IBIC    0x02180	/* Illegal byte during Idle stream count */
#घोषणा IXGB_RFC     0x02188	/* Remote Fault Count */
#घोषणा IXGB_LFC     0x02190	/* Local Fault Count */
#घोषणा IXGB_PFRC    0x02198	/* Pause Frame Receive Count */
#घोषणा IXGB_PFTC    0x021A0	/* Pause Frame Transmit Count */
#घोषणा IXGB_MCFRC   0x021A8	/* MAC Control Frames (non-Pause) Received Count */
#घोषणा IXGB_MCFTC   0x021B0	/* MAC Control Frames (non-Pause) Transmitted Count */
#घोषणा IXGB_XONRXC  0x021B8	/* XON Received Count */
#घोषणा IXGB_XONTXC  0x021C0	/* XON Transmitted Count */
#घोषणा IXGB_XOFFRXC 0x021C8	/* XOFF Received Count */
#घोषणा IXGB_XOFFTXC 0x021D0	/* XOFF Transmitted Count */
#घोषणा IXGB_RJC     0x021D8	/* Receive Jabber Count */

/* CTRL0 Bit Masks */
#घोषणा IXGB_CTRL0_LRST     0x00000008
#घोषणा IXGB_CTRL0_JFE      0x00000010
#घोषणा IXGB_CTRL0_XLE      0x00000020
#घोषणा IXGB_CTRL0_MDCS     0x00000040
#घोषणा IXGB_CTRL0_CMDC     0x00000080
#घोषणा IXGB_CTRL0_SDP0     0x00040000
#घोषणा IXGB_CTRL0_SDP1     0x00080000
#घोषणा IXGB_CTRL0_SDP2     0x00100000
#घोषणा IXGB_CTRL0_SDP3     0x00200000
#घोषणा IXGB_CTRL0_SDP0_सूची 0x00400000
#घोषणा IXGB_CTRL0_SDP1_सूची 0x00800000
#घोषणा IXGB_CTRL0_SDP2_सूची 0x01000000
#घोषणा IXGB_CTRL0_SDP3_सूची 0x02000000
#घोषणा IXGB_CTRL0_RST      0x04000000
#घोषणा IXGB_CTRL0_RPE      0x08000000
#घोषणा IXGB_CTRL0_TPE      0x10000000
#घोषणा IXGB_CTRL0_VME      0x40000000

/* CTRL1 Bit Masks */
#घोषणा IXGB_CTRL1_GPI0_EN     0x00000001
#घोषणा IXGB_CTRL1_GPI1_EN     0x00000002
#घोषणा IXGB_CTRL1_GPI2_EN     0x00000004
#घोषणा IXGB_CTRL1_GPI3_EN     0x00000008
#घोषणा IXGB_CTRL1_SDP4        0x00000010
#घोषणा IXGB_CTRL1_SDP5        0x00000020
#घोषणा IXGB_CTRL1_SDP6        0x00000040
#घोषणा IXGB_CTRL1_SDP7        0x00000080
#घोषणा IXGB_CTRL1_SDP4_सूची    0x00000100
#घोषणा IXGB_CTRL1_SDP5_सूची    0x00000200
#घोषणा IXGB_CTRL1_SDP6_सूची    0x00000400
#घोषणा IXGB_CTRL1_SDP7_सूची    0x00000800
#घोषणा IXGB_CTRL1_EE_RST      0x00002000
#घोषणा IXGB_CTRL1_RO_DIS      0x00020000
#घोषणा IXGB_CTRL1_PCIXHM_MASK 0x00C00000
#घोषणा IXGB_CTRL1_PCIXHM_1_2  0x00000000
#घोषणा IXGB_CTRL1_PCIXHM_5_8  0x00400000
#घोषणा IXGB_CTRL1_PCIXHM_3_4  0x00800000
#घोषणा IXGB_CTRL1_PCIXHM_7_8  0x00C00000

/* STATUS Bit Masks */
#घोषणा IXGB_STATUS_LU            0x00000002
#घोषणा IXGB_STATUS_AIP           0x00000004
#घोषणा IXGB_STATUS_TXOFF         0x00000010
#घोषणा IXGB_STATUS_XAUIME        0x00000020
#घोषणा IXGB_STATUS_RES           0x00000040
#घोषणा IXGB_STATUS_RIS           0x00000080
#घोषणा IXGB_STATUS_RIE           0x00000100
#घोषणा IXGB_STATUS_RLF           0x00000200
#घोषणा IXGB_STATUS_RRF           0x00000400
#घोषणा IXGB_STATUS_PCI_SPD       0x00000800
#घोषणा IXGB_STATUS_BUS64         0x00001000
#घोषणा IXGB_STATUS_PCIX_MODE     0x00002000
#घोषणा IXGB_STATUS_PCIX_SPD_MASK 0x0000C000
#घोषणा IXGB_STATUS_PCIX_SPD_66   0x00000000
#घोषणा IXGB_STATUS_PCIX_SPD_100  0x00004000
#घोषणा IXGB_STATUS_PCIX_SPD_133  0x00008000
#घोषणा IXGB_STATUS_REV_ID_MASK   0x000F0000
#घोषणा IXGB_STATUS_REV_ID_SHIFT  16

/* EECD Bit Masks */
#घोषणा IXGB_EECD_SK       0x00000001
#घोषणा IXGB_EECD_CS       0x00000002
#घोषणा IXGB_EECD_DI       0x00000004
#घोषणा IXGB_EECD_DO       0x00000008
#घोषणा IXGB_EECD_FWE_MASK 0x00000030
#घोषणा IXGB_EECD_FWE_DIS  0x00000010
#घोषणा IXGB_EECD_FWE_EN   0x00000020

/* MFS */
#घोषणा IXGB_MFS_SHIFT 16

/* Interrupt Register Bit Masks (used क्रम ICR, ICS, IMS, and IMC) */
#घोषणा IXGB_INT_TXDW     0x00000001
#घोषणा IXGB_INT_TXQE     0x00000002
#घोषणा IXGB_INT_LSC      0x00000004
#घोषणा IXGB_INT_RXSEQ    0x00000008
#घोषणा IXGB_INT_RXDMT0   0x00000010
#घोषणा IXGB_INT_RXO      0x00000040
#घोषणा IXGB_INT_RXT0     0x00000080
#घोषणा IXGB_INT_AUTOSCAN 0x00000200
#घोषणा IXGB_INT_GPI0     0x00000800
#घोषणा IXGB_INT_GPI1     0x00001000
#घोषणा IXGB_INT_GPI2     0x00002000
#घोषणा IXGB_INT_GPI3     0x00004000

/* RCTL Bit Masks */
#घोषणा IXGB_RCTL_RXEN        0x00000002
#घोषणा IXGB_RCTL_SBP         0x00000004
#घोषणा IXGB_RCTL_UPE         0x00000008
#घोषणा IXGB_RCTL_MPE         0x00000010
#घोषणा IXGB_RCTL_RDMTS_MASK  0x00000300
#घोषणा IXGB_RCTL_RDMTS_1_2   0x00000000
#घोषणा IXGB_RCTL_RDMTS_1_4   0x00000100
#घोषणा IXGB_RCTL_RDMTS_1_8   0x00000200
#घोषणा IXGB_RCTL_MO_MASK     0x00003000
#घोषणा IXGB_RCTL_MO_47_36    0x00000000
#घोषणा IXGB_RCTL_MO_46_35    0x00001000
#घोषणा IXGB_RCTL_MO_45_34    0x00002000
#घोषणा IXGB_RCTL_MO_43_32    0x00003000
#घोषणा IXGB_RCTL_MO_SHIFT    12
#घोषणा IXGB_RCTL_BAM         0x00008000
#घोषणा IXGB_RCTL_BSIZE_MASK  0x00030000
#घोषणा IXGB_RCTL_BSIZE_2048  0x00000000
#घोषणा IXGB_RCTL_BSIZE_4096  0x00010000
#घोषणा IXGB_RCTL_BSIZE_8192  0x00020000
#घोषणा IXGB_RCTL_BSIZE_16384 0x00030000
#घोषणा IXGB_RCTL_VFE         0x00040000
#घोषणा IXGB_RCTL_CFIEN       0x00080000
#घोषणा IXGB_RCTL_CFI         0x00100000
#घोषणा IXGB_RCTL_RPDA_MASK   0x00600000
#घोषणा IXGB_RCTL_RPDA_MC_MAC 0x00000000
#घोषणा IXGB_RCTL_MC_ONLY     0x00400000
#घोषणा IXGB_RCTL_CFF         0x00800000
#घोषणा IXGB_RCTL_SECRC       0x04000000
#घोषणा IXGB_RDT_FPDB         0x80000000

#घोषणा IXGB_RCTL_IDLE_RX_UNIT 0

/* FCRTL Bit Masks */
#घोषणा IXGB_FCRTL_XONE       0x80000000

/* RXDCTL Bit Masks */
#घोषणा IXGB_RXDCTL_PTHRESH_MASK  0x000001FF
#घोषणा IXGB_RXDCTL_PTHRESH_SHIFT 0
#घोषणा IXGB_RXDCTL_HTHRESH_MASK  0x0003FE00
#घोषणा IXGB_RXDCTL_HTHRESH_SHIFT 9
#घोषणा IXGB_RXDCTL_WTHRESH_MASK  0x07FC0000
#घोषणा IXGB_RXDCTL_WTHRESH_SHIFT 18

/* RAIDC Bit Masks */
#घोषणा IXGB_RAIDC_HIGHTHRS_MASK 0x0000003F
#घोषणा IXGB_RAIDC_DELAY_MASK    0x000FF800
#घोषणा IXGB_RAIDC_DELAY_SHIFT   11
#घोषणा IXGB_RAIDC_POLL_MASK     0x1FF00000
#घोषणा IXGB_RAIDC_POLL_SHIFT    20
#घोषणा IXGB_RAIDC_RXT_GATE      0x40000000
#घोषणा IXGB_RAIDC_EN            0x80000000

#घोषणा IXGB_RAIDC_POLL_1000_INTERRUPTS_PER_SECOND      1220
#घोषणा IXGB_RAIDC_POLL_5000_INTERRUPTS_PER_SECOND      244
#घोषणा IXGB_RAIDC_POLL_10000_INTERRUPTS_PER_SECOND     122
#घोषणा IXGB_RAIDC_POLL_20000_INTERRUPTS_PER_SECOND     61

/* RXCSUM Bit Masks */
#घोषणा IXGB_RXCSUM_IPOFL 0x00000100
#घोषणा IXGB_RXCSUM_TUOFL 0x00000200

/* RAH Bit Masks */
#घोषणा IXGB_RAH_ASEL_MASK 0x00030000
#घोषणा IXGB_RAH_ASEL_DEST 0x00000000
#घोषणा IXGB_RAH_ASEL_SRC  0x00010000
#घोषणा IXGB_RAH_AV        0x80000000

/* TCTL Bit Masks */
#घोषणा IXGB_TCTL_TCE  0x00000001
#घोषणा IXGB_TCTL_TXEN 0x00000002
#घोषणा IXGB_TCTL_TPDE 0x00000004

#घोषणा IXGB_TCTL_IDLE_TX_UNIT  0

/* TXDCTL Bit Masks */
#घोषणा IXGB_TXDCTL_PTHRESH_MASK  0x0000007F
#घोषणा IXGB_TXDCTL_HTHRESH_MASK  0x00007F00
#घोषणा IXGB_TXDCTL_HTHRESH_SHIFT 8
#घोषणा IXGB_TXDCTL_WTHRESH_MASK  0x007F0000
#घोषणा IXGB_TXDCTL_WTHRESH_SHIFT 16

/* TSPMT Bit Masks */
#घोषणा IXGB_TSPMT_TSMT_MASK   0x0000FFFF
#घोषणा IXGB_TSPMT_TSPBP_MASK  0xFFFF0000
#घोषणा IXGB_TSPMT_TSPBP_SHIFT 16

/* PAP Bit Masks */
#घोषणा IXGB_PAP_TXPC_MASK 0x0000FFFF
#घोषणा IXGB_PAP_TXPV_MASK 0x000F0000
#घोषणा IXGB_PAP_TXPV_10G  0x00000000
#घोषणा IXGB_PAP_TXPV_1G   0x00010000
#घोषणा IXGB_PAP_TXPV_2G   0x00020000
#घोषणा IXGB_PAP_TXPV_3G   0x00030000
#घोषणा IXGB_PAP_TXPV_4G   0x00040000
#घोषणा IXGB_PAP_TXPV_5G   0x00050000
#घोषणा IXGB_PAP_TXPV_6G   0x00060000
#घोषणा IXGB_PAP_TXPV_7G   0x00070000
#घोषणा IXGB_PAP_TXPV_8G   0x00080000
#घोषणा IXGB_PAP_TXPV_9G   0x00090000
#घोषणा IXGB_PAP_TXPV_WAN  0x000F0000

/* PCSC1 Bit Masks */
#घोषणा IXGB_PCSC1_LOOPBACK 0x00004000

/* PCSC2 Bit Masks */
#घोषणा IXGB_PCSC2_PCS_TYPE_MASK  0x00000003
#घोषणा IXGB_PCSC2_PCS_TYPE_10GBX 0x00000001

/* PCSS1 Bit Masks */
#घोषणा IXGB_PCSS1_LOCAL_FAULT    0x00000080
#घोषणा IXGB_PCSS1_RX_LINK_STATUS 0x00000004

/* PCSS2 Bit Masks */
#घोषणा IXGB_PCSS2_DEV_PRES_MASK 0x0000C000
#घोषणा IXGB_PCSS2_DEV_PRES      0x00004000
#घोषणा IXGB_PCSS2_TX_LF         0x00000800
#घोषणा IXGB_PCSS2_RX_LF         0x00000400
#घोषणा IXGB_PCSS2_10GBW         0x00000004
#घोषणा IXGB_PCSS2_10GBX         0x00000002
#घोषणा IXGB_PCSS2_10GBR         0x00000001

/* XPCSS Bit Masks */
#घोषणा IXGB_XPCSS_ALIGN_STATUS 0x00001000
#घोषणा IXGB_XPCSS_PATTERN_TEST 0x00000800
#घोषणा IXGB_XPCSS_LANE_3_SYNC  0x00000008
#घोषणा IXGB_XPCSS_LANE_2_SYNC  0x00000004
#घोषणा IXGB_XPCSS_LANE_1_SYNC  0x00000002
#घोषणा IXGB_XPCSS_LANE_0_SYNC  0x00000001

/* XPCSTC Bit Masks */
#घोषणा IXGB_XPCSTC_BERT_TRIG       0x00200000
#घोषणा IXGB_XPCSTC_BERT_SST        0x00100000
#घोषणा IXGB_XPCSTC_BERT_PSZ_MASK   0x000C0000
#घोषणा IXGB_XPCSTC_BERT_PSZ_SHIFT  17
#घोषणा IXGB_XPCSTC_BERT_PSZ_INF    0x00000003
#घोषणा IXGB_XPCSTC_BERT_PSZ_68     0x00000001
#घोषणा IXGB_XPCSTC_BERT_PSZ_1028   0x00000000

/* MSCA bit Masks */
/* New Protocol Address */
#घोषणा IXGB_MSCA_NP_ADDR_MASK      0x0000FFFF
#घोषणा IXGB_MSCA_NP_ADDR_SHIFT     0
/* Either Device Type or Register Address,depending on ST_CODE */
#घोषणा IXGB_MSCA_DEV_TYPE_MASK     0x001F0000
#घोषणा IXGB_MSCA_DEV_TYPE_SHIFT    16
#घोषणा IXGB_MSCA_PHY_ADDR_MASK     0x03E00000
#घोषणा IXGB_MSCA_PHY_ADDR_SHIFT    21
#घोषणा IXGB_MSCA_OP_CODE_MASK      0x0C000000
/* OP_CODE == 00, Address cycle, New Protocol           */
/* OP_CODE == 01, Write operation                       */
/* OP_CODE == 10, Read operation                        */
/* OP_CODE == 11, Read, स्वतः increment, New Protocol    */
#घोषणा IXGB_MSCA_ADDR_CYCLE        0x00000000
#घोषणा IXGB_MSCA_WRITE             0x04000000
#घोषणा IXGB_MSCA_READ              0x08000000
#घोषणा IXGB_MSCA_READ_AUTOINC      0x0C000000
#घोषणा IXGB_MSCA_OP_CODE_SHIFT     26
#घोषणा IXGB_MSCA_ST_CODE_MASK      0x30000000
/* ST_CODE == 00, New Protocol  */
/* ST_CODE == 01, Old Protocol  */
#घोषणा IXGB_MSCA_NEW_PROTOCOL      0x00000000
#घोषणा IXGB_MSCA_OLD_PROTOCOL      0x10000000
#घोषणा IXGB_MSCA_ST_CODE_SHIFT     28
/* Initiate command, self-clearing when command completes */
#घोषणा IXGB_MSCA_MDI_COMMAND       0x40000000
/*MDI In Progress Enable. */
#घोषणा IXGB_MSCA_MDI_IN_PROG_EN    0x80000000

/* MSRWD bit masks */
#घोषणा IXGB_MSRWD_WRITE_DATA_MASK  0x0000FFFF
#घोषणा IXGB_MSRWD_WRITE_DATA_SHIFT 0
#घोषणा IXGB_MSRWD_READ_DATA_MASK   0xFFFF0000
#घोषणा IXGB_MSRWD_READ_DATA_SHIFT  16

/* Definitions क्रम the optics devices on the MDIO bus. */
#घोषणा IXGB_PHY_ADDRESS             0x0	/* Single PHY, multiple "Devices" */

#घोषणा MDIO_PMA_PMD_XPAK_VENDOR_NAME       0x803A	/* XPAK/XENPAK devices only */

/* Venकरोr-specअगरic MDIO रेजिस्टरs */
#घोषणा G6XXX_PMA_PMD_VS1                   0xC001	/* Venकरोr-specअगरic रेजिस्टर */
#घोषणा G6XXX_XGXS_XAUI_VS2                 0x18	/* Venकरोr-specअगरic रेजिस्टर */

#घोषणा G6XXX_PMA_PMD_VS1_PLL_RESET         0x80
#घोषणा G6XXX_PMA_PMD_VS1_REMOVE_PLL_RESET  0x00
#घोषणा G6XXX_XGXS_XAUI_VS2_INPUT_MASK      0x0F	/* XAUI lanes synchronized */

/* Layout of a single receive descriptor.  The controller assumes that this
 * काष्ठाure is packed पूर्णांकo 16 bytes, which is a safe assumption with most
 * compilers.  However, some compilers may insert padding between the fields,
 * in which हाल the काष्ठाure must be packed in some compiler-specअगरic
 * manner. */
काष्ठा ixgb_rx_desc अणु
	__le64 buff_addr;
	__le16 length;
	__le16 reserved;
	u8 status;
	u8 errors;
	__le16 special;
पूर्ण;

#घोषणा IXGB_RX_DESC_STATUS_DD    0x01
#घोषणा IXGB_RX_DESC_STATUS_EOP   0x02
#घोषणा IXGB_RX_DESC_STATUS_IXSM  0x04
#घोषणा IXGB_RX_DESC_STATUS_VP    0x08
#घोषणा IXGB_RX_DESC_STATUS_TCPCS 0x20
#घोषणा IXGB_RX_DESC_STATUS_IPCS  0x40
#घोषणा IXGB_RX_DESC_STATUS_PIF   0x80

#घोषणा IXGB_RX_DESC_ERRORS_CE   0x01
#घोषणा IXGB_RX_DESC_ERRORS_SE   0x02
#घोषणा IXGB_RX_DESC_ERRORS_P    0x08
#घोषणा IXGB_RX_DESC_ERRORS_TCPE 0x20
#घोषणा IXGB_RX_DESC_ERRORS_IPE  0x40
#घोषणा IXGB_RX_DESC_ERRORS_RXE  0x80

#घोषणा IXGB_RX_DESC_SPECIAL_VLAN_MASK  0x0FFF	/* VLAN ID is in lower 12 bits */
#घोषणा IXGB_RX_DESC_SPECIAL_PRI_MASK   0xE000	/* Priority is in upper 3 bits */
#घोषणा IXGB_RX_DESC_SPECIAL_PRI_SHIFT  0x000D	/* Priority is in upper 3 of 16 */

/* Layout of a single transmit descriptor.  The controller assumes that this
 * काष्ठाure is packed पूर्णांकo 16 bytes, which is a safe assumption with most
 * compilers.  However, some compilers may insert padding between the fields,
 * in which हाल the काष्ठाure must be packed in some compiler-specअगरic
 * manner. */
काष्ठा ixgb_tx_desc अणु
	__le64 buff_addr;
	__le32 cmd_type_len;
	u8 status;
	u8 popts;
	__le16 vlan;
पूर्ण;

#घोषणा IXGB_TX_DESC_LENGTH_MASK    0x000FFFFF
#घोषणा IXGB_TX_DESC_TYPE_MASK      0x00F00000
#घोषणा IXGB_TX_DESC_TYPE_SHIFT     20
#घोषणा IXGB_TX_DESC_CMD_MASK       0xFF000000
#घोषणा IXGB_TX_DESC_CMD_SHIFT      24
#घोषणा IXGB_TX_DESC_CMD_EOP        0x01000000
#घोषणा IXGB_TX_DESC_CMD_TSE        0x04000000
#घोषणा IXGB_TX_DESC_CMD_RS         0x08000000
#घोषणा IXGB_TX_DESC_CMD_VLE        0x40000000
#घोषणा IXGB_TX_DESC_CMD_IDE        0x80000000

#घोषणा IXGB_TX_DESC_TYPE           0x00100000

#घोषणा IXGB_TX_DESC_STATUS_DD  0x01

#घोषणा IXGB_TX_DESC_POPTS_IXSM 0x01
#घोषणा IXGB_TX_DESC_POPTS_TXSM 0x02
#घोषणा IXGB_TX_DESC_SPECIAL_PRI_SHIFT  IXGB_RX_DESC_SPECIAL_PRI_SHIFT	/* Priority is in upper 3 of 16 */

काष्ठा ixgb_context_desc अणु
	u8 ipcss;
	u8 ipcso;
	__le16 ipcse;
	u8 tucss;
	u8 tucso;
	__le16 tucse;
	__le32 cmd_type_len;
	u8 status;
	u8 hdr_len;
	__le16 mss;
पूर्ण;

#घोषणा IXGB_CONTEXT_DESC_CMD_TCP 0x01000000
#घोषणा IXGB_CONTEXT_DESC_CMD_IP  0x02000000
#घोषणा IXGB_CONTEXT_DESC_CMD_TSE 0x04000000
#घोषणा IXGB_CONTEXT_DESC_CMD_RS  0x08000000
#घोषणा IXGB_CONTEXT_DESC_CMD_IDE 0x80000000

#घोषणा IXGB_CONTEXT_DESC_TYPE 0x00000000

#घोषणा IXGB_CONTEXT_DESC_STATUS_DD 0x01

/* Filters */
#घोषणा IXGB_MC_TBL_SIZE          128	/* Multicast Filter Table (4096 bits) */
#घोषणा IXGB_VLAN_FILTER_TBL_SIZE 128	/* VLAN Filter Table (4096 bits) */
#घोषणा IXGB_RAR_ENTRIES		  3	/* Number of entries in Rx Address array */

#घोषणा IXGB_MEMORY_REGISTER_BASE_ADDRESS   0
#घोषणा ENET_HEADER_SIZE			14
#घोषणा ENET_FCS_LENGTH			 4
#घोषणा IXGB_MAX_NUM_MULTICAST_ADDRESSES	128
#घोषणा IXGB_MIN_ENET_FRAME_SIZE_WITHOUT_FCS	60
#घोषणा IXGB_MAX_ENET_FRAME_SIZE_WITHOUT_FCS	1514
#घोषणा IXGB_MAX_JUMBO_FRAME_SIZE		0x3F00

/* Phy Addresses */
#घोषणा IXGB_OPTICAL_PHY_ADDR 0x0	/* Optical Module phy address */
#घोषणा IXGB_XAUII_PHY_ADDR   0x1	/* Xauii transceiver phy address */
#घोषणा IXGB_DIAG_PHY_ADDR    0x1F	/* Diagnostic Device phy address */

/* This काष्ठाure takes a 64k flash and maps it क्रम identअगरication commands */
काष्ठा ixgb_flash_buffer अणु
	u8 manufacturer_id;
	u8 device_id;
	u8 filler1[0x2AA8];
	u8 cmd2;
	u8 filler2[0x2AAA];
	u8 cmd1;
	u8 filler3[0xAAAA];
पूर्ण;

/* Flow control parameters */
काष्ठा ixgb_fc अणु
	u32 high_water;	/* Flow Control High-water          */
	u32 low_water;	/* Flow Control Low-water           */
	u16 छोड़ो_समय;	/* Flow Control Pause समयr         */
	bool send_xon;		/* Flow control send XON            */
	ixgb_fc_type type;	/* Type of flow control             */
पूर्ण;

/* The historical शेषs क्रम the flow control values are given below. */
#घोषणा FC_DEFAULT_HI_THRESH        (0x8000)	/* 32KB */
#घोषणा FC_DEFAULT_LO_THRESH        (0x4000)	/* 16KB */
#घोषणा FC_DEFAULT_TX_TIMER         (0x100)	/* ~130 us */

/* Phy definitions */
#घोषणा IXGB_MAX_PHY_REG_ADDRESS    0xFFFF
#घोषणा IXGB_MAX_PHY_ADDRESS        31
#घोषणा IXGB_MAX_PHY_DEV_TYPE       31

/* Bus parameters */
काष्ठा ixgb_bus अणु
	ixgb_bus_speed speed;
	ixgb_bus_width width;
	ixgb_bus_type type;
पूर्ण;

काष्ठा ixgb_hw अणु
	u8 __iomem *hw_addr;/* Base Address of the hardware     */
	व्योम *back;		/* Poपूर्णांकer to OS-dependent काष्ठा   */
	काष्ठा ixgb_fc fc;	/* Flow control parameters          */
	काष्ठा ixgb_bus bus;	/* Bus parameters                   */
	u32 phy_id;	/* Phy Identअगरier                   */
	u32 phy_addr;	/* XGMII address of Phy             */
	ixgb_mac_type mac_type;	/* Identअगरier क्रम MAC controller    */
	ixgb_phy_type phy_type;	/* Transceiver/phy identअगरier       */
	u32 max_frame_size;	/* Maximum frame size supported     */
	u32 mc_filter_type;	/* Multicast filter hash type       */
	u32 num_mc_addrs;	/* Number of current Multicast addrs */
	u8 curr_mac_addr[ETH_ALEN];	/* Inभागidual address currently programmed in MAC */
	u32 num_tx_desc;	/* Number of Transmit descriptors   */
	u32 num_rx_desc;	/* Number of Receive descriptors    */
	u32 rx_buffer_size;	/* Size of Receive buffer           */
	bool link_up;		/* true अगर link is valid            */
	bool adapter_stopped;	/* State of adapter                 */
	u16 device_id;	/* device id from PCI configuration space */
	u16 venकरोr_id;	/* venकरोr id from PCI configuration space */
	u8 revision_id;	/* revision id from PCI configuration space */
	u16 subप्रणाली_venकरोr_id;	/* subप्रणाली venकरोr id from PCI configuration space */
	u16 subप्रणाली_id;	/* subप्रणाली id from PCI configuration space */
	u32 bar0;		/* Base Address रेजिस्टरs           */
	u32 bar1;
	u32 bar2;
	u32 bar3;
	u16 pci_cmd_word;	/* PCI command रेजिस्टर id from PCI configuration space */
	__le16 eeprom[IXGB_EEPROM_SIZE];	/* EEPROM contents पढ़ो at init समय  */
	अचिन्हित दीर्घ io_base;	/* Our I/O mapped location */
	u32 lastLFC;
	u32 lastRFC;
पूर्ण;

/* Statistics reported by the hardware */
काष्ठा ixgb_hw_stats अणु
	u64 tprl;
	u64 tprh;
	u64 gprcl;
	u64 gprch;
	u64 bprcl;
	u64 bprch;
	u64 mprcl;
	u64 mprch;
	u64 uprcl;
	u64 uprch;
	u64 vprcl;
	u64 vprch;
	u64 jprcl;
	u64 jprch;
	u64 gorcl;
	u64 gorch;
	u64 torl;
	u64 torh;
	u64 rnbc;
	u64 ruc;
	u64 roc;
	u64 rlec;
	u64 crcerrs;
	u64 icbc;
	u64 ecbc;
	u64 mpc;
	u64 tptl;
	u64 tpth;
	u64 gptcl;
	u64 gptch;
	u64 bptcl;
	u64 bptch;
	u64 mptcl;
	u64 mptch;
	u64 uptcl;
	u64 uptch;
	u64 vptcl;
	u64 vptch;
	u64 jptcl;
	u64 jptch;
	u64 gotcl;
	u64 gotch;
	u64 totl;
	u64 toth;
	u64 dc;
	u64 plt64c;
	u64 tsctc;
	u64 tsctfc;
	u64 ibic;
	u64 rfc;
	u64 lfc;
	u64 pfrc;
	u64 pftc;
	u64 mcfrc;
	u64 mcftc;
	u64 xonrxc;
	u64 xontxc;
	u64 xoffrxc;
	u64 xofftxc;
	u64 rjc;
पूर्ण;

/* Function Prototypes */
bool ixgb_adapter_stop(काष्ठा ixgb_hw *hw);
bool ixgb_init_hw(काष्ठा ixgb_hw *hw);
bool ixgb_adapter_start(काष्ठा ixgb_hw *hw);
व्योम ixgb_check_क्रम_link(काष्ठा ixgb_hw *hw);
bool ixgb_check_क्रम_bad_link(काष्ठा ixgb_hw *hw);

व्योम ixgb_rar_set(काष्ठा ixgb_hw *hw, u8 *addr, u32 index);

/* Filters (multicast, vlan, receive) */
व्योम ixgb_mc_addr_list_update(काष्ठा ixgb_hw *hw, u8 *mc_addr_list,
			      u32 mc_addr_count, u32 pad);

/* Vfta functions */
व्योम ixgb_ग_लिखो_vfta(काष्ठा ixgb_hw *hw, u32 offset, u32 value);

/* Access functions to eeprom data */
व्योम ixgb_get_ee_mac_addr(काष्ठा ixgb_hw *hw, u8 *mac_addr);
u32 ixgb_get_ee_pba_number(काष्ठा ixgb_hw *hw);
u16 ixgb_get_ee_device_id(काष्ठा ixgb_hw *hw);
bool ixgb_get_eeprom_data(काष्ठा ixgb_hw *hw);
__le16 ixgb_get_eeprom_word(काष्ठा ixgb_hw *hw, u16 index);

/* Everything अन्यथा */
व्योम ixgb_led_on(काष्ठा ixgb_hw *hw);
व्योम ixgb_led_off(काष्ठा ixgb_hw *hw);
व्योम ixgb_ग_लिखो_pci_cfg(काष्ठा ixgb_hw *hw,
			 u32 reg,
			 u16 * value);


#पूर्ण_अगर /* _IXGB_HW_H_ */
