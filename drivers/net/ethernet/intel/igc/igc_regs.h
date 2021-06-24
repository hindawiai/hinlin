<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2018 Intel Corporation */

#अगर_अघोषित _IGC_REGS_H_
#घोषणा _IGC_REGS_H_

/* General Register Descriptions */
#घोषणा IGC_CTRL		0x00000  /* Device Control - RW */
#घोषणा IGC_STATUS		0x00008  /* Device Status - RO */
#घोषणा IGC_EECD		0x00010  /* EEPROM/Flash Control - RW */
#घोषणा IGC_CTRL_EXT		0x00018  /* Extended Device Control - RW */
#घोषणा IGC_MDIC		0x00020  /* MDI Control - RW */
#घोषणा IGC_MDICNFG		0x00E04  /* MDC/MDIO Configuration - RW */
#घोषणा IGC_CONNSW		0x00034  /* Copper/Fiber चयन control - RW */
#घोषणा IGC_I225_PHPM		0x00E14  /* I225 PHY Power Management */
#घोषणा IGC_GPHY_VERSION	0x0001E  /* I225 gPHY Firmware Version */

/* Internal Packet Buffer Size Registers */
#घोषणा IGC_RXPBS		0x02404  /* Rx Packet Buffer Size - RW */
#घोषणा IGC_TXPBS		0x03404  /* Tx Packet Buffer Size - RW */

/* NVM  Register Descriptions */
#घोषणा IGC_EERD		0x12014  /* EEprom mode पढ़ो - RW */
#घोषणा IGC_EEWR		0x12018  /* EEprom mode ग_लिखो - RW */

/* Flow Control Register Descriptions */
#घोषणा IGC_FCAL		0x00028  /* FC Address Low - RW */
#घोषणा IGC_FCAH		0x0002C  /* FC Address High - RW */
#घोषणा IGC_FCT			0x00030  /* FC Type - RW */
#घोषणा IGC_FCTTV		0x00170  /* FC Transmit Timer - RW */
#घोषणा IGC_FCRTL		0x02160  /* FC Receive Threshold Low - RW */
#घोषणा IGC_FCRTH		0x02168  /* FC Receive Threshold High - RW */
#घोषणा IGC_FCRTV		0x02460  /* FC Refresh Timer Value - RW */

/* Semaphore रेजिस्टरs */
#घोषणा IGC_SW_FW_SYNC		0x05B5C  /* SW-FW Synchronization - RW */
#घोषणा IGC_SWSM		0x05B50  /* SW Semaphore */
#घोषणा IGC_FWSM		0x05B54  /* FW Semaphore */

/* Function Active and Power State to MNG */
#घोषणा IGC_FACTPS		0x05B30

/* Interrupt Register Description */
#घोषणा IGC_EICR		0x01580  /* Ext. Interrupt Cause पढ़ो - W0 */
#घोषणा IGC_EICS		0x01520  /* Ext. Interrupt Cause Set - W0 */
#घोषणा IGC_EIMS		0x01524  /* Ext. Interrupt Mask Set/Read - RW */
#घोषणा IGC_EIMC		0x01528  /* Ext. Interrupt Mask Clear - WO */
#घोषणा IGC_EIAC		0x0152C  /* Ext. Interrupt Auto Clear - RW */
#घोषणा IGC_EIAM		0x01530  /* Ext. Interrupt Auto Mask - RW */
#घोषणा IGC_ICR			0x01500  /* Intr Cause Read - RC/W1C */
#घोषणा IGC_ICS			0x01504  /* Intr Cause Set - WO */
#घोषणा IGC_IMS			0x01508  /* Intr Mask Set/Read - RW */
#घोषणा IGC_IMC			0x0150C  /* Intr Mask Clear - WO */
#घोषणा IGC_IAM			0x01510  /* Intr Ack Auto Mask- RW */
/* Intr Throttle - RW */
#घोषणा IGC_EITR(_n)		(0x01680 + (0x4 * (_n)))
/* Interrupt Vector Allocation - RW */
#घोषणा IGC_IVAR0		0x01700
#घोषणा IGC_IVAR_MISC		0x01740  /* IVAR क्रम "other" causes - RW */
#घोषणा IGC_GPIE		0x01514  /* General Purpose Intr Enable - RW */

/* MSI-X Table Register Descriptions */
#घोषणा IGC_PBACL		0x05B68  /* MSIx PBA Clear - R/W 1 to clear */

/* RSS रेजिस्टरs */
#घोषणा IGC_MRQC		0x05818 /* Multiple Receive Control - RW */

/* Filtering Registers */
#घोषणा IGC_ETQF(_n)		(0x05CB0 + (4 * (_n))) /* EType Queue Fltr */

/* ETQF रेजिस्टर bit definitions */
#घोषणा IGC_ETQF_FILTER_ENABLE	BIT(26)
#घोषणा IGC_ETQF_QUEUE_ENABLE	BIT(31)
#घोषणा IGC_ETQF_QUEUE_SHIFT	16
#घोषणा IGC_ETQF_QUEUE_MASK	0x00070000
#घोषणा IGC_ETQF_ETYPE_MASK	0x0000FFFF

/* Redirection Table - RW Array */
#घोषणा IGC_RETA(_i)		(0x05C00 + ((_i) * 4))
/* RSS Ranकरोm Key - RW Array */
#घोषणा IGC_RSSRK(_i)		(0x05C80 + ((_i) * 4))

/* Receive Register Descriptions */
#घोषणा IGC_RCTL		0x00100  /* Rx Control - RW */
#घोषणा IGC_SRRCTL(_n)		(0x0C00C + ((_n) * 0x40))
#घोषणा IGC_PSRTYPE(_i)		(0x05480 + ((_i) * 4))
#घोषणा IGC_RDBAL(_n)		(0x0C000 + ((_n) * 0x40))
#घोषणा IGC_RDBAH(_n)		(0x0C004 + ((_n) * 0x40))
#घोषणा IGC_RDLEN(_n)		(0x0C008 + ((_n) * 0x40))
#घोषणा IGC_RDH(_n)		(0x0C010 + ((_n) * 0x40))
#घोषणा IGC_RDT(_n)		(0x0C018 + ((_n) * 0x40))
#घोषणा IGC_RXDCTL(_n)		(0x0C028 + ((_n) * 0x40))
#घोषणा IGC_RQDPC(_n)		(0x0C030 + ((_n) * 0x40))
#घोषणा IGC_RXCSUM		0x05000  /* Rx Checksum Control - RW */
#घोषणा IGC_RLPML		0x05004  /* Rx Long Packet Max Length */
#घोषणा IGC_RFCTL		0x05008  /* Receive Filter Control*/
#घोषणा IGC_MTA			0x05200  /* Multicast Table Array - RW Array */
#घोषणा IGC_RA			0x05400  /* Receive Address - RW Array */
#घोषणा IGC_UTA			0x0A000  /* Unicast Table Array - RW */
#घोषणा IGC_RAL(_n)		(0x05400 + ((_n) * 0x08))
#घोषणा IGC_RAH(_n)		(0x05404 + ((_n) * 0x08))
#घोषणा IGC_VLANPQF		0x055B0  /* VLAN Priority Queue Filter - RW */

/* Transmit Register Descriptions */
#घोषणा IGC_TCTL		0x00400  /* Tx Control - RW */
#घोषणा IGC_TIPG		0x00410  /* Tx Inter-packet gap - RW */
#घोषणा IGC_TDBAL(_n)		(0x0E000 + ((_n) * 0x40))
#घोषणा IGC_TDBAH(_n)		(0x0E004 + ((_n) * 0x40))
#घोषणा IGC_TDLEN(_n)		(0x0E008 + ((_n) * 0x40))
#घोषणा IGC_TDH(_n)		(0x0E010 + ((_n) * 0x40))
#घोषणा IGC_TDT(_n)		(0x0E018 + ((_n) * 0x40))
#घोषणा IGC_TXDCTL(_n)		(0x0E028 + ((_n) * 0x40))

/* MMD Register Descriptions */
#घोषणा IGC_MMDAC		13 /* MMD Access Control */
#घोषणा IGC_MMDAAD		14 /* MMD Access Address/Data */

/* Statistics Register Descriptions */
#घोषणा IGC_CRCERRS	0x04000  /* CRC Error Count - R/clr */
#घोषणा IGC_ALGNERRC	0x04004  /* Alignment Error Count - R/clr */
#घोषणा IGC_RXERRC	0x0400C  /* Receive Error Count - R/clr */
#घोषणा IGC_MPC		0x04010  /* Missed Packet Count - R/clr */
#घोषणा IGC_SCC		0x04014  /* Single Collision Count - R/clr */
#घोषणा IGC_ECOL	0x04018  /* Excessive Collision Count - R/clr */
#घोषणा IGC_MCC		0x0401C  /* Multiple Collision Count - R/clr */
#घोषणा IGC_LATECOL	0x04020  /* Late Collision Count - R/clr */
#घोषणा IGC_COLC	0x04028  /* Collision Count - R/clr */
#घोषणा IGC_RERC	0x0402C  /* Receive Error Count - R/clr */
#घोषणा IGC_DC		0x04030  /* Defer Count - R/clr */
#घोषणा IGC_TNCRS	0x04034  /* Tx-No CRS - R/clr */
#घोषणा IGC_HTDPMC	0x0403C  /* Host Transmit Discarded by MAC - R/clr */
#घोषणा IGC_RLEC	0x04040  /* Receive Length Error Count - R/clr */
#घोषणा IGC_XONRXC	0x04048  /* XON Rx Count - R/clr */
#घोषणा IGC_XONTXC	0x0404C  /* XON Tx Count - R/clr */
#घोषणा IGC_XOFFRXC	0x04050  /* XOFF Rx Count - R/clr */
#घोषणा IGC_XOFFTXC	0x04054  /* XOFF Tx Count - R/clr */
#घोषणा IGC_FCRUC	0x04058  /* Flow Control Rx Unsupported Count- R/clr */
#घोषणा IGC_PRC64	0x0405C  /* Packets Rx (64 bytes) - R/clr */
#घोषणा IGC_PRC127	0x04060  /* Packets Rx (65-127 bytes) - R/clr */
#घोषणा IGC_PRC255	0x04064  /* Packets Rx (128-255 bytes) - R/clr */
#घोषणा IGC_PRC511	0x04068  /* Packets Rx (255-511 bytes) - R/clr */
#घोषणा IGC_PRC1023	0x0406C  /* Packets Rx (512-1023 bytes) - R/clr */
#घोषणा IGC_PRC1522	0x04070  /* Packets Rx (1024-1522 bytes) - R/clr */
#घोषणा IGC_GPRC	0x04074  /* Good Packets Rx Count - R/clr */
#घोषणा IGC_BPRC	0x04078  /* Broadcast Packets Rx Count - R/clr */
#घोषणा IGC_MPRC	0x0407C  /* Multicast Packets Rx Count - R/clr */
#घोषणा IGC_GPTC	0x04080  /* Good Packets Tx Count - R/clr */
#घोषणा IGC_GORCL	0x04088  /* Good Octets Rx Count Low - R/clr */
#घोषणा IGC_GORCH	0x0408C  /* Good Octets Rx Count High - R/clr */
#घोषणा IGC_GOTCL	0x04090  /* Good Octets Tx Count Low - R/clr */
#घोषणा IGC_GOTCH	0x04094  /* Good Octets Tx Count High - R/clr */
#घोषणा IGC_RNBC	0x040A0  /* Rx No Buffers Count - R/clr */
#घोषणा IGC_RUC		0x040A4  /* Rx Undersize Count - R/clr */
#घोषणा IGC_RFC		0x040A8  /* Rx Fragment Count - R/clr */
#घोषणा IGC_ROC		0x040AC  /* Rx Oversize Count - R/clr */
#घोषणा IGC_RJC		0x040B0  /* Rx Jabber Count - R/clr */
#घोषणा IGC_MGTPRC	0x040B4  /* Management Packets Rx Count - R/clr */
#घोषणा IGC_MGTPDC	0x040B8  /* Management Packets Dropped Count - R/clr */
#घोषणा IGC_MGTPTC	0x040BC  /* Management Packets Tx Count - R/clr */
#घोषणा IGC_TORL	0x040C0  /* Total Octets Rx Low - R/clr */
#घोषणा IGC_TORH	0x040C4  /* Total Octets Rx High - R/clr */
#घोषणा IGC_TOTL	0x040C8  /* Total Octets Tx Low - R/clr */
#घोषणा IGC_TOTH	0x040CC  /* Total Octets Tx High - R/clr */
#घोषणा IGC_TPR		0x040D0  /* Total Packets Rx - R/clr */
#घोषणा IGC_TPT		0x040D4  /* Total Packets Tx - R/clr */
#घोषणा IGC_PTC64	0x040D8  /* Packets Tx (64 bytes) - R/clr */
#घोषणा IGC_PTC127	0x040DC  /* Packets Tx (65-127 bytes) - R/clr */
#घोषणा IGC_PTC255	0x040E0  /* Packets Tx (128-255 bytes) - R/clr */
#घोषणा IGC_PTC511	0x040E4  /* Packets Tx (256-511 bytes) - R/clr */
#घोषणा IGC_PTC1023	0x040E8  /* Packets Tx (512-1023 bytes) - R/clr */
#घोषणा IGC_PTC1522	0x040EC  /* Packets Tx (1024-1522 Bytes) - R/clr */
#घोषणा IGC_MPTC	0x040F0  /* Multicast Packets Tx Count - R/clr */
#घोषणा IGC_BPTC	0x040F4  /* Broadcast Packets Tx Count - R/clr */
#घोषणा IGC_TSCTC	0x040F8  /* TCP Segmentation Context Tx - R/clr */
#घोषणा IGC_IAC		0x04100  /* Interrupt Assertion Count */
#घोषणा IGC_RPTHC	0x04104  /* Rx Packets To Host */
#घोषणा IGC_TLPIC	0x04148  /* EEE Tx LPI Count */
#घोषणा IGC_RLPIC	0x0414C  /* EEE Rx LPI Count */
#घोषणा IGC_HGPTC	0x04118  /* Host Good Packets Tx Count */
#घोषणा IGC_RXDMTC	0x04120  /* Rx Descriptor Minimum Threshold Count */
#घोषणा IGC_HGORCL	0x04128  /* Host Good Octets Received Count Low */
#घोषणा IGC_HGORCH	0x0412C  /* Host Good Octets Received Count High */
#घोषणा IGC_HGOTCL	0x04130  /* Host Good Octets Transmit Count Low */
#घोषणा IGC_HGOTCH	0x04134  /* Host Good Octets Transmit Count High */
#घोषणा IGC_LENERRS	0x04138  /* Length Errors Count */

/* Time sync रेजिस्टरs */
#घोषणा IGC_TSICR	0x0B66C  /* Time Sync Interrupt Cause */
#घोषणा IGC_TSIM	0x0B674  /* Time Sync Interrupt Mask Register */
#घोषणा IGC_TSAUXC	0x0B640  /* Timesync Auxiliary Control रेजिस्टर */
#घोषणा IGC_TSYNCRXCTL	0x0B620  /* Rx Time Sync Control रेजिस्टर - RW */
#घोषणा IGC_TSYNCTXCTL	0x0B614  /* Tx Time Sync Control रेजिस्टर - RW */
#घोषणा IGC_TSYNCRXCFG	0x05F50  /* Time Sync Rx Configuration - RW */
#घोषणा IGC_TSSDP	0x0003C  /* Time Sync SDP Configuration Register - RW */
#घोषणा IGC_TRGTTIML0	0x0B644 /* Target Time Register 0 Low  - RW */
#घोषणा IGC_TRGTTIMH0	0x0B648 /* Target Time Register 0 High - RW */
#घोषणा IGC_TRGTTIML1	0x0B64C /* Target Time Register 1 Low  - RW */
#घोषणा IGC_TRGTTIMH1	0x0B650 /* Target Time Register 1 High - RW */
#घोषणा IGC_FREQOUT0	0x0B654 /* Frequency Out 0 Control Register - RW */
#घोषणा IGC_FREQOUT1	0x0B658 /* Frequency Out 1 Control Register - RW */
#घोषणा IGC_AUXSTMPL0	0x0B65C /* Auxiliary Time Stamp 0 Register Low  - RO */
#घोषणा IGC_AUXSTMPH0	0x0B660 /* Auxiliary Time Stamp 0 Register High - RO */
#घोषणा IGC_AUXSTMPL1	0x0B664 /* Auxiliary Time Stamp 1 Register Low  - RO */
#घोषणा IGC_AUXSTMPH1	0x0B668 /* Auxiliary Time Stamp 1 Register High - RO */

#घोषणा IGC_IMIR(_i)	(0x05A80 + ((_i) * 4))  /* Immediate Interrupt */
#घोषणा IGC_IMIREXT(_i)	(0x05AA0 + ((_i) * 4))  /* Immediate INTR Ext*/

#घोषणा IGC_FTQF(_n)	(0x059E0 + (4 * (_n)))  /* 5-tuple Queue Fltr */

/* Transmit Scheduling Registers */
#घोषणा IGC_TQAVCTRL		0x3570
#घोषणा IGC_TXQCTL(_n)		(0x3344 + 0x4 * (_n))
#घोषणा IGC_BASET_L		0x3314
#घोषणा IGC_BASET_H		0x3318
#घोषणा IGC_QBVCYCLET		0x331C
#घोषणा IGC_QBVCYCLET_S		0x3320

#घोषणा IGC_STQT(_n)		(0x3324 + 0x4 * (_n))
#घोषणा IGC_ENDQT(_n)		(0x3334 + 0x4 * (_n))
#घोषणा IGC_DTXMXPKTSZ		0x355C

/* System Time Registers */
#घोषणा IGC_SYSTIML	0x0B600  /* System समय रेजिस्टर Low - RO */
#घोषणा IGC_SYSTIMH	0x0B604  /* System समय रेजिस्टर High - RO */
#घोषणा IGC_SYSTIMR	0x0B6F8  /* System समय रेजिस्टर Residue */
#घोषणा IGC_TIMINCA	0x0B608  /* Increment attributes रेजिस्टर - RW */

#घोषणा IGC_TXSTMPL	0x0B618  /* Tx बारtamp value Low - RO */
#घोषणा IGC_TXSTMPH	0x0B61C  /* Tx बारtamp value High - RO */

/* Management रेजिस्टरs */
#घोषणा IGC_MANC	0x05820  /* Management Control - RW */

/* Shaकरोw Ram Write Register - RW */
#घोषणा IGC_SRWR	0x12018

/* Wake Up रेजिस्टरs */
#घोषणा IGC_WUC		0x05800  /* Wakeup Control - RW */
#घोषणा IGC_WUFC	0x05808  /* Wakeup Filter Control - RW */
#घोषणा IGC_WUS		0x05810  /* Wakeup Status - R/W1C */
#घोषणा IGC_WUPL	0x05900  /* Wakeup Packet Length - RW */

/* Wake Up packet memory */
#घोषणा IGC_WUPM_REG(_i)	(0x05A00 + ((_i) * 4))

/* Energy Efficient Ethernet "EEE" रेजिस्टरs */
#घोषणा IGC_EEER	0x0E30 /* Energy Efficient Ethernet "EEE"*/
#घोषणा IGC_IPCNFG	0x0E38 /* Internal PHY Configuration */
#घोषणा IGC_EEE_SU	0x0E34 /* EEE Setup */

/* LTR रेजिस्टरs */
#घोषणा IGC_LTRC	0x01A0 /* Latency Tolerance Reporting Control */
#घोषणा IGC_DMACR	0x02508 /* DMA Coalescing Control Register */
#घोषणा IGC_LTRMINV	0x5BB0 /* LTR Minimum Value */
#घोषणा IGC_LTRMAXV	0x5BB4 /* LTR Maximum Value */

/* क्रमward declaration */
काष्ठा igc_hw;
u32 igc_rd32(काष्ठा igc_hw *hw, u32 reg);

/* ग_लिखो operations, indexed using DWORDS */
#घोषणा wr32(reg, val) \
करो अणु \
	u8 __iomem *hw_addr = READ_ONCE((hw)->hw_addr); \
	ग_लिखोl((val), &hw_addr[(reg)]); \
पूर्ण जबतक (0)

#घोषणा rd32(reg) (igc_rd32(hw, reg))

#घोषणा wrfl() ((व्योम)rd32(IGC_STATUS))

#घोषणा array_wr32(reg, offset, value) \
	wr32((reg) + ((offset) << 2), (value))

#घोषणा array_rd32(reg, offset) (igc_rd32(hw, (reg) + ((offset) << 2)))

#पूर्ण_अगर
