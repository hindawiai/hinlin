<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _SLIC_H
#घोषणा _SLIC_H

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/u64_stats_sync.h>

#घोषणा SLIC_VGBSTAT_XPERR		0x40000000
#घोषणा SLIC_VGBSTAT_XERRSHFT		25
#घोषणा SLIC_VGBSTAT_XCSERR		0x23
#घोषणा SLIC_VGBSTAT_XUFLOW		0x22
#घोषणा SLIC_VGBSTAT_XHLEN		0x20
#घोषणा SLIC_VGBSTAT_NETERR		0x01000000
#घोषणा SLIC_VGBSTAT_NERRSHFT		16
#घोषणा SLIC_VGBSTAT_NERRMSK		0x1ff
#घोषणा SLIC_VGBSTAT_NCSERR		0x103
#घोषणा SLIC_VGBSTAT_NUFLOW		0x102
#घोषणा SLIC_VGBSTAT_NHLEN		0x100
#घोषणा SLIC_VGBSTAT_LNKERR		0x00000080
#घोषणा SLIC_VGBSTAT_LERRMSK		0xff
#घोषणा SLIC_VGBSTAT_LDEARLY		0x86
#घोषणा SLIC_VGBSTAT_LBOFLO		0x85
#घोषणा SLIC_VGBSTAT_LCODERR		0x84
#घोषणा SLIC_VGBSTAT_LDBLNBL		0x83
#घोषणा SLIC_VGBSTAT_LCRCERR		0x82
#घोषणा SLIC_VGBSTAT_LOFLO		0x81
#घोषणा SLIC_VGBSTAT_LUFLO		0x80

#घोषणा SLIC_IRHDDR_FLEN_MSK		0x0000ffff
#घोषणा SLIC_IRHDDR_SVALID		0x80000000
#घोषणा SLIC_IRHDDR_ERR			0x10000000

#घोषणा SLIC_VRHSTAT_802OE		0x80000000
#घोषणा SLIC_VRHSTAT_TPOFLO		0x10000000
#घोषणा SLIC_VRHSTATB_802UE		0x80000000
#घोषणा SLIC_VRHSTATB_RCVE		0x40000000
#घोषणा SLIC_VRHSTATB_BUFF		0x20000000
#घोषणा SLIC_VRHSTATB_CARRE		0x08000000
#घोषणा SLIC_VRHSTATB_LONGE		0x02000000
#घोषणा SLIC_VRHSTATB_PREA		0x01000000
#घोषणा SLIC_VRHSTATB_CRC		0x00800000
#घोषणा SLIC_VRHSTATB_DRBL		0x00400000
#घोषणा SLIC_VRHSTATB_CODE		0x00200000
#घोषणा SLIC_VRHSTATB_TPCSUM		0x00100000
#घोषणा SLIC_VRHSTATB_TPHLEN		0x00080000
#घोषणा SLIC_VRHSTATB_IPCSUM		0x00040000
#घोषणा SLIC_VRHSTATB_IPLERR		0x00020000
#घोषणा SLIC_VRHSTATB_IPHERR		0x00010000

#घोषणा SLIC_CMD_XMT_REQ		0x01
#घोषणा SLIC_CMD_TYPE_DUMB		3

#घोषणा SLIC_RESET_MAGIC		0xDEAD
#घोषणा SLIC_ICR_INT_OFF		0
#घोषणा SLIC_ICR_INT_ON			1
#घोषणा SLIC_ICR_INT_MASK		2

#घोषणा SLIC_ISR_ERR			0x80000000
#घोषणा SLIC_ISR_RCV			0x40000000
#घोषणा SLIC_ISR_CMD			0x20000000
#घोषणा SLIC_ISR_IO			0x60000000
#घोषणा SLIC_ISR_UPC			0x10000000
#घोषणा SLIC_ISR_LEVENT			0x08000000
#घोषणा SLIC_ISR_RMISS			0x02000000
#घोषणा SLIC_ISR_UPCERR			0x01000000
#घोषणा SLIC_ISR_XDROP			0x00800000
#घोषणा SLIC_ISR_UPCBSY			0x00020000

#घोषणा SLIC_ISR_PING_MASK		0x00700000
#घोषणा SLIC_ISR_UPCERR_MASK		(SLIC_ISR_UPCERR | SLIC_ISR_UPCBSY)
#घोषणा SLIC_ISR_UPC_MASK		(SLIC_ISR_UPC | SLIC_ISR_UPCERR_MASK)
#घोषणा SLIC_WCS_START			0x80000000
#घोषणा SLIC_WCS_COMPARE		0x40000000
#घोषणा SLIC_RCVWCS_BEGIN		0x40000000
#घोषणा SLIC_RCVWCS_FINISH		0x80000000

#घोषणा SLIC_MIICR_REG_16		0x00100000
#घोषणा SLIC_MRV_REG16_XOVERON		0x0068

#घोषणा SLIC_GIG_LINKUP			0x0001
#घोषणा SLIC_GIG_FULLDUPLEX		0x0002
#घोषणा SLIC_GIG_SPEED_MASK		0x000C
#घोषणा SLIC_GIG_SPEED_1000		0x0008
#घोषणा SLIC_GIG_SPEED_100		0x0004
#घोषणा SLIC_GIG_SPEED_10		0x0000

#घोषणा SLIC_GMCR_RESET			0x80000000
#घोषणा SLIC_GMCR_GBIT			0x20000000
#घोषणा SLIC_GMCR_FULLD			0x10000000
#घोषणा SLIC_GMCR_GAPBB_SHIFT		14
#घोषणा SLIC_GMCR_GAPR1_SHIFT		7
#घोषणा SLIC_GMCR_GAPR2_SHIFT		0
#घोषणा SLIC_GMCR_GAPBB_1000		0x60
#घोषणा SLIC_GMCR_GAPR1_1000		0x2C
#घोषणा SLIC_GMCR_GAPR2_1000		0x40
#घोषणा SLIC_GMCR_GAPBB_100		0x70
#घोषणा SLIC_GMCR_GAPR1_100		0x2C
#घोषणा SLIC_GMCR_GAPR2_100		0x40

#घोषणा SLIC_XCR_RESET			0x80000000
#घोषणा SLIC_XCR_XMTEN			0x40000000
#घोषणा SLIC_XCR_PAUSEEN		0x20000000
#घोषणा SLIC_XCR_LOADRNG		0x10000000

#घोषणा SLIC_GXCR_RESET			0x80000000
#घोषणा SLIC_GXCR_XMTEN			0x40000000
#घोषणा SLIC_GXCR_PAUSEEN		0x20000000

#घोषणा SLIC_GRCR_RESET			0x80000000
#घोषणा SLIC_GRCR_RCVEN			0x40000000
#घोषणा SLIC_GRCR_RCVALL		0x20000000
#घोषणा SLIC_GRCR_RCVBAD		0x10000000
#घोषणा SLIC_GRCR_CTLEN			0x08000000
#घोषणा SLIC_GRCR_ADDRAEN		0x02000000
#घोषणा SLIC_GRCR_HASHSIZE_SHIFT	17
#घोषणा SLIC_GRCR_HASHSIZE		14

/* Reset Register */
#घोषणा SLIC_REG_RESET			0x0000
/* Interrupt Control Register */
#घोषणा SLIC_REG_ICR			0x0008
/* Interrupt status poपूर्णांकer */
#घोषणा SLIC_REG_ISP			0x0010
/* Interrupt status */
#घोषणा SLIC_REG_ISR			0x0018
/* Header buffer address reg
 * 31-8 - phy addr of set of contiguous hdr buffers
 *  7-0 - number of buffers passed
 * Buffers are 256 bytes दीर्घ on 256-byte boundaries.
 */
#घोषणा SLIC_REG_HBAR			0x0020
/* Data buffer handle & address reg
 * 4 sets of रेजिस्टरs; Buffers are 2K bytes दीर्घ 2 per 4K page.
 */
#घोषणा SLIC_REG_DBAR			0x0028
/* Xmt Cmd buf addr regs.
 * 1 per XMT पूर्णांकerface
 * 31-5 - phy addr of host command buffer
 *  4-0 - length of cmd in multiples of 32 bytes
 * Buffers are 32 bytes up to 512 bytes दीर्घ
 */
#घोषणा SLIC_REG_CBAR			0x0030
/* Write control store */
#घोषणा	SLIC_REG_WCS			0x0034
/*Response buffer address reg.
 * 31-8 - phy addr of set of contiguous response buffers
 * 7-0 - number of buffers passed
 * Buffers are 32 bytes दीर्घ on 32-byte boundaries.
 */
#घोषणा	SLIC_REG_RBAR			0x0038
/* Read statistics (UPR) */
#घोषणा	SLIC_REG_RSTAT			0x0040
/* Read link status */
#घोषणा	SLIC_REG_LSTAT			0x0048
/* Write Mac Config */
#घोषणा	SLIC_REG_WMCFG			0x0050
/* Write phy रेजिस्टर */
#घोषणा SLIC_REG_WPHY			0x0058
/* Rcv Cmd buf addr reg */
#घोषणा	SLIC_REG_RCBAR			0x0060
/* Read SLIC Config*/
#घोषणा SLIC_REG_RCONFIG		0x0068
/* Interrupt aggregation समय */
#घोषणा SLIC_REG_INTAGG			0x0070
/* Write XMIT config reg */
#घोषणा	SLIC_REG_WXCFG			0x0078
/* Write RCV config reg */
#घोषणा	SLIC_REG_WRCFG			0x0080
/* Write rcv addr a low */
#घोषणा	SLIC_REG_WRADDRAL		0x0088
/* Write rcv addr a high */
#घोषणा	SLIC_REG_WRADDRAH		0x0090
/* Write rcv addr b low */
#घोषणा	SLIC_REG_WRADDRBL		0x0098
/* Write rcv addr b high */
#घोषणा	SLIC_REG_WRADDRBH		0x00a0
/* Low bits of mcast mask */
#घोषणा	SLIC_REG_MCASTLOW		0x00a8
/* High bits of mcast mask */
#घोषणा	SLIC_REG_MCASTHIGH		0x00b0
/* Ping the card */
#घोषणा SLIC_REG_PING			0x00b8
/* Dump command */
#घोषणा SLIC_REG_DUMP_CMD		0x00c0
/* Dump data poपूर्णांकer */
#घोषणा SLIC_REG_DUMP_DATA		0x00c8
/* Read card's pci_status रेजिस्टर */
#घोषणा	SLIC_REG_PCISTATUS		0x00d0
/* Write hostid field */
#घोषणा SLIC_REG_WRHOSTID		0x00d8
/* Put card in a low घातer state */
#घोषणा SLIC_REG_LOW_POWER		0x00e0
/* Force slic पूर्णांकo quiescent state  beक्रमe soft reset */
#घोषणा SLIC_REG_QUIESCE		0x00e8
/* Reset पूर्णांकerface queues */
#घोषणा SLIC_REG_RESET_IFACE		0x00f0
/* Register is only written when it has changed.
 * Bits 63-32 क्रम host i/f addrs.
 */
#घोषणा SLIC_REG_ADDR_UPPER		0x00f8
/* 64 bit Header buffer address reg */
#घोषणा SLIC_REG_HBAR64			0x0100
/* 64 bit Data buffer handle & address reg */
#घोषणा SLIC_REG_DBAR64			0x0108
/* 64 bit Xmt Cmd buf addr regs. */
#घोषणा SLIC_REG_CBAR64			0x0110
/* 64 bit Response buffer address reg.*/
#घोषणा SLIC_REG_RBAR64			0x0118
/* 64 bit Rcv Cmd buf addr reg*/
#घोषणा	SLIC_REG_RCBAR64		0x0120
/* Read statistics (64 bit UPR) */
#घोषणा	SLIC_REG_RSTAT64		0x0128
/* Download Gigabit RCV sequencer ucode */
#घोषणा SLIC_REG_RCV_WCS		0x0130
/* Write VlanId field */
#घोषणा SLIC_REG_WRVLANID		0x0138
/* Read Transक्रमmer info */
#घोषणा SLIC_REG_READ_XF_INFO		0x0140
/* Write Transक्रमmer info */
#घोषणा SLIC_REG_WRITE_XF_INFO		0x0148
/* Write card ticks per second */
#घोषणा SLIC_REG_TICKS_PER_SEC		0x0170
#घोषणा SLIC_REG_HOSTID			0x1554

#घोषणा PCI_VENDOR_ID_ALACRITECH		0x139A
#घोषणा PCI_DEVICE_ID_ALACRITECH_MOJAVE		0x0005
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_1000X1	0x0005
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_1000X1_2	0x0006
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_1000X1F	0x0007
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_CICADA	0x0008
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SES1001T	0x2006
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SES1001F	0x2007
#घोषणा PCI_DEVICE_ID_ALACRITECH_OASIS		0x0007
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SEN2002XT	0x000B
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SEN2002XF	0x000C
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SEN2001XT	0x000D
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SEN2001XF	0x000E
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SEN2104EF	0x000F
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SEN2104ET	0x0010
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SEN2102EF	0x0011
#घोषणा PCI_SUBDEVICE_ID_ALACRITECH_SEN2102ET	0x0012

/* Note: घातer of two required क्रम number descriptors  */
#घोषणा SLIC_NUM_RX_LES			256
#घोषणा SLIC_RX_BUFF_SIZE		2048
#घोषणा SLIC_RX_BUFF_ALIGN		256
#घोषणा SLIC_RX_BUFF_HDR_SIZE		34
#घोषणा SLIC_MAX_REQ_RX_DESCS		1

#घोषणा SLIC_NUM_TX_DESCS		256
#घोषणा SLIC_TX_DESC_ALIGN		32
#घोषणा SLIC_MIN_TX_WAKEUP_DESCS	10
#घोषणा SLIC_MAX_REQ_TX_DESCS		1
#घोषणा SLIC_MAX_TX_COMPLETIONS		100

#घोषणा SLIC_NUM_STAT_DESCS		128
#घोषणा SLIC_STATS_DESC_ALIGN		256

#घोषणा SLIC_NUM_STAT_DESC_ARRAYS	4
#घोषणा SLIC_INVALID_STAT_DESC_IDX	0xffffffff

#घोषणा SLIC_NAPI_WEIGHT		64

#घोषणा SLIC_UPR_LSTAT			0
#घोषणा SLIC_UPR_CONFIG			1

#घोषणा SLIC_EEPROM_SIZE		128
#घोषणा SLIC_EEPROM_MAGIC		0xa5a5

#घोषणा SLIC_FIRMWARE_MOJAVE		"slicoss/gbdownload.sys"
#घोषणा SLIC_FIRMWARE_OASIS		"slicoss/oasisdownload.sys"
#घोषणा SLIC_RCV_FIRMWARE_MOJAVE	"slicoss/gbrcvucode.sys"
#घोषणा SLIC_RCV_FIRMWARE_OASIS		"slicoss/oasisrcvucode.sys"
#घोषणा SLIC_FIRMWARE_MIN_SIZE		64
#घोषणा SLIC_FIRMWARE_MAX_SECTIONS	3

#घोषणा SLIC_MODEL_MOJAVE		0
#घोषणा SLIC_MODEL_OASIS		1

#घोषणा SLIC_INC_STATS_COUNTER(st, counter)	\
करो अणु						\
	u64_stats_update_begin(&(st)->syncp);	\
	(st)->counter++;			\
	u64_stats_update_end(&(st)->syncp);	\
पूर्ण जबतक (0)

#घोषणा SLIC_GET_STATS_COUNTER(newst, st, counter)			\
अणु									\
	अचिन्हित पूर्णांक start;						\
	करो अणु							\
		start = u64_stats_fetch_begin_irq(&(st)->syncp);	\
		newst = (st)->counter;					\
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&(st)->syncp, start));	\
पूर्ण

काष्ठा slic_upr अणु
	dma_addr_t paddr;
	अचिन्हित पूर्णांक type;
	काष्ठा list_head list;
पूर्ण;

काष्ठा slic_upr_list अणु
	bool pending;
	काष्ठा list_head list;
	/* upr list lock */
	spinlock_t lock;
पूर्ण;

/* SLIC EEPROM काष्ठाure क्रम Mojave */
काष्ठा slic_mojave_eeprom अणु
	__le16 id;		/* 00 EEPROM/FLASH Magic code 'A5A5'*/
	__le16 eeprom_code_size;/* 01 Size of EEPROM Codes (bytes * 4)*/
	__le16 flash_size;	/* 02 Flash size */
	__le16 eeprom_size;	/* 03 EEPROM Size */
	__le16 venकरोr_id;	/* 04 Venकरोr ID */
	__le16 dev_id;		/* 05 Device ID */
	u8 rev_id;		/* 06 Revision ID */
	u8 class_code[3];	/* 07 Class Code */
	u8 irqpin_dbg;		/* 08 Debug Interrupt pin */
	u8 irqpin;		/*    Network Interrupt Pin */
	u8 min_grant;		/* 09 Minimum grant */
	u8 max_lat;		/*    Maximum Latency */
	__le16 pci_stat;	/* 10 PCI Status */
	__le16 sub_venकरोr_id;	/* 11 Subप्रणाली Venकरोr Id */
	__le16 sub_id;		/* 12 Subप्रणाली ID */
	__le16 dev_id_dbg;	/* 13 Debug Device Id */
	__le16 ramrom;		/* 14 Dram/Rom function */
	__le16 dram_size2pci;	/* 15 DRAM size to PCI (bytes * 64K) */
	__le16 rom_size2pci;	/* 16 ROM extension size to PCI (bytes * 4k) */
	u8 pad[2];		/* 17 Padding */
	u8 मुक्तसमय;		/* 18 FreeTime setting */
	u8 अगरctrl;		/* 10-bit पूर्णांकerface control (Mojave only) */
	__le16 dram_size;	/* 19 DRAM size (bytes * 64k) */
	u8 mac[ETH_ALEN];	/* 20 MAC addresses */
	u8 mac2[ETH_ALEN];
	u8 pad2[6];
	u16 dev_id2;		/* Device ID क्रम 2nd PCI function */
	u8 irqpin2;		/* Interrupt pin क्रम 2nd PCI function */
	u8 class_code2[3];	/* Class Code क्रम 2nd PCI function */
	u16 cfg_byte6;		/* Config Byte 6 */
	u16 pme_cap;		/* Power Mgment capabilities */
	u16 nwclk_ctrl;		/* NetworkClockControls */
	u8 fru_क्रमmat;		/* Alacritech FRU क्रमmat type */
	u8 fru_assembly[6];	/* Alacritech FRU inक्रमmation */
	u8 fru_rev[2];
	u8 fru_serial[14];
	u8 fru_pad[3];
	u8 oem_fru[28];		/* optional OEM FRU क्रमmat type */
	u8 pad3[4];		/* Pad to 128 bytes - includes 2 cksum bytes
				 * (अगर OEM FRU info exists) and two unusable
				 * bytes at the end
				 */
पूर्ण;

/* SLIC EEPROM काष्ठाure क्रम Oasis */
काष्ठा slic_oasis_eeprom अणु
	__le16 id;		/* 00 EEPROM/FLASH Magic code 'A5A5' */
	__le16 eeprom_code_size;/* 01 Size of EEPROM Codes (bytes * 4)*/
	__le16 spidev0_cfg;	/* 02 Flash Config क्रम SPI device 0 */
	__le16 spidev1_cfg;	/* 03 Flash Config क्रम SPI device 1 */
	__le16 venकरोr_id;	/* 04 Venकरोr ID */
	__le16 dev_id;		/* 05 Device ID (function 0) */
	u8 rev_id;		/* 06 Revision ID */
	u8 class_code0[3];	/* 07 Class Code क्रम PCI function 0 */
	u8 irqpin1;		/* 08 Interrupt pin क्रम PCI function 1*/
	u8 class_code1[3];	/* 09 Class Code क्रम PCI function 1 */
	u8 irqpin2;		/* 10 Interrupt pin क्रम PCI function 2*/
	u8 irqpin0;		/*    Interrupt pin क्रम PCI function 0*/
	u8 min_grant;		/* 11 Minimum grant */
	u8 max_lat;		/*    Maximum Latency */
	__le16 sub_venकरोr_id;	/* 12 Subप्रणाली Venकरोr Id */
	__le16 sub_id;		/* 13 Subप्रणाली ID */
	__le16 flash_size;	/* 14 Flash size (bytes / 4K) */
	__le16 dram_size2pci;	/* 15 DRAM size to PCI (bytes / 64K) */
	__le16 rom_size2pci;	/* 16 Flash (ROM extension) size to PCI
				 *   (bytes / 4K)
				 */
	__le16 dev_id1;		/* 17 Device Id (function 1) */
	__le16 dev_id2;		/* 18 Device Id (function 2) */
	__le16 dev_stat_cfg;	/* 19 Device Status Config Bytes 6-7 */
	__le16 pme_cap;		/* 20 Power Mgment capabilities */
	u8 msi_cap;		/* 21 MSI capabilities */
	u8 घड़ी_भाग;		/*    Clock भागider */
	__le16 pci_stat_lo;	/* 22 PCI Status bits 15:0 */
	__le16 pci_stat_hi;	/* 23 PCI Status bits 31:16 */
	__le16 dram_cfg_lo;	/* 24 DRAM Configuration bits 15:0 */
	__le16 dram_cfg_hi;	/* 25 DRAM Configuration bits 31:16 */
	__le16 dram_size;	/* 26 DRAM size (bytes / 64K) */
	__le16 gpio_tbi_ctrl;	/* 27 GPIO/TBI controls क्रम functions 1/0 */
	__le16 eeprom_size;	/* 28 EEPROM Size */
	u8 mac[ETH_ALEN];	/* 29 MAC addresses (2 ports) */
	u8 mac2[ETH_ALEN];
	u8 fru_क्रमmat;		/* 35 Alacritech FRU क्रमmat type */
	u8 fru_assembly[6];	/* Alacritech FRU inक्रमmation */
	u8 fru_rev[2];
	u8 fru_serial[14];
	u8 fru_pad[3];
	u8 oem_fru[28];		/* optional OEM FRU inक्रमmation */
	u8 pad[4];		/* Pad to 128 bytes - includes 2 checksum bytes
				 * (अगर OEM FRU info exists) and two unusable
				 * bytes at the end
				 */
पूर्ण;

काष्ठा slic_stats अणु
	u64 rx_packets;
	u64 rx_bytes;
	u64 rx_mcasts;
	u64 rx_errors;
	u64 tx_packets;
	u64 tx_bytes;
	/* HW STATS */
	u64 rx_buff_miss;
	u64 tx_dropped;
	u64 irq_errs;
	/* transport layer */
	u64 rx_tpcsum;
	u64 rx_tpoflow;
	u64 rx_tphlen;
	/* ip layer */
	u64 rx_ipcsum;
	u64 rx_iplen;
	u64 rx_iphlen;
	/* link layer */
	u64 rx_early;
	u64 rx_buffoflow;
	u64 rx_lcode;
	u64 rx_drbl;
	u64 rx_crc;
	u64 rx_oflow802;
	u64 rx_uflow802;
	/* oasis only */
	u64 tx_carrier;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

काष्ठा slic_shmem_data अणु
	__le32 isr;
	__le32 link;
पूर्ण;

काष्ठा slic_shmem अणु
	dma_addr_t isr_paddr;
	dma_addr_t link_paddr;
	काष्ठा slic_shmem_data *shmem_data;
पूर्ण;

काष्ठा slic_rx_info_oasis अणु
	__le32 frame_status;
	__le32 frame_status_b;
	__le32 समय_stamp;
	__le32 checksum;
पूर्ण;

काष्ठा slic_rx_info_mojave अणु
	__le32 frame_status;
	__le16 byte_cnt;
	__le16 tp_chksum;
	__le16 ctx_hash;
	__le16 mac_hash;
	__le16 buff_lnk;
पूर्ण;

काष्ठा slic_stat_desc अणु
	__le32 hnd;
	__u8 pad[8];
	__le32 status;
	__u8 pad2[16];
पूर्ण;

काष्ठा slic_stat_queue अणु
	काष्ठा slic_stat_desc *descs[SLIC_NUM_STAT_DESC_ARRAYS];
	dma_addr_t paddr[SLIC_NUM_STAT_DESC_ARRAYS];
	अचिन्हित पूर्णांक addr_offset[SLIC_NUM_STAT_DESC_ARRAYS];
	अचिन्हित पूर्णांक active_array;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक करोne_idx;
	माप_प्रकार mem_size;
पूर्ण;

काष्ठा slic_tx_desc अणु
	__le32 hnd;
	__le32 rsvd;
	u8 cmd;
	u8 flags;
	__le16 rsvd2;
	__le32 totlen;
	__le32 paddrl;
	__le32 paddrh;
	__le32 len;
	__le32 type;
पूर्ण;

काष्ठा slic_tx_buffer अणु
	काष्ठा sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDR(map_addr);
	DEFINE_DMA_UNMAP_LEN(map_len);
	काष्ठा slic_tx_desc *desc;
	dma_addr_t desc_paddr;
पूर्ण;

काष्ठा slic_tx_queue अणु
	काष्ठा dma_pool *dma_pool;
	काष्ठा slic_tx_buffer *txbuffs;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक put_idx;
	अचिन्हित पूर्णांक करोne_idx;
पूर्ण;

काष्ठा slic_rx_desc अणु
	u8 pad[16];
	__le32 buffer;
	__le32 length;
	__le32 status;
पूर्ण;

काष्ठा slic_rx_buffer अणु
	काष्ठा sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDR(map_addr);
	DEFINE_DMA_UNMAP_LEN(map_len);
	अचिन्हित पूर्णांक addr_offset;
पूर्ण;

काष्ठा slic_rx_queue अणु
	काष्ठा slic_rx_buffer *rxbuffs;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक करोne_idx;
	अचिन्हित पूर्णांक put_idx;
पूर्ण;

काष्ठा slic_device अणु
	काष्ठा pci_dev *pdev;
	काष्ठा net_device *netdev;
	व्योम __iomem *regs;
	/* upper address setting lock */
	spinlock_t upper_lock;
	काष्ठा slic_shmem shmem;
	काष्ठा napi_काष्ठा napi;
	काष्ठा slic_rx_queue rxq;
	काष्ठा slic_tx_queue txq;
	काष्ठा slic_stat_queue stq;
	काष्ठा slic_stats stats;
	काष्ठा slic_upr_list upr_list;
	/* link configuration lock */
	spinlock_t link_lock;
	bool promisc;
	पूर्णांक speed;
	अचिन्हित पूर्णांक duplex;
	bool is_fiber;
	अचिन्हित अक्षर model;
पूर्ण;

अटल अंतरभूत u32 slic_पढ़ो(काष्ठा slic_device *sdev, अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32(sdev->regs + reg);
पूर्ण

अटल अंतरभूत व्योम slic_ग_लिखो(काष्ठा slic_device *sdev, अचिन्हित पूर्णांक reg,
			      u32 val)
अणु
	ioग_लिखो32(val, sdev->regs + reg);
पूर्ण

अटल अंतरभूत व्योम slic_flush_ग_लिखो(काष्ठा slic_device *sdev)
अणु
	(व्योम)ioपढ़ो32(sdev->regs + SLIC_REG_HOSTID);
पूर्ण

#पूर्ण_अगर /* _SLIC_H */
