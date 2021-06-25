<शैली गुरु>
#अगर_अघोषित TLAN_H
#घोषणा TLAN_H
/********************************************************************
 *
 *  Linux ThunderLAN Driver
 *
 *  tlan.h
 *  by James Banks
 *
 *  (C) 1997-1998 Caldera, Inc.
 *  (C) 1999-2001 Torben Mathiasen
 *
 *  This software may be used and distributed according to the terms
 *  of the GNU General Public License, incorporated herein by reference.
 *
 *
 *  Dec 10, 1999	Torben Mathiasen <torben.mathiasen@compaq.com>
 *			New Maपूर्णांकainer
 *
 ********************************************************************/


#समावेश <linux/पन.स>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>



	/*****************************************************************
	 * TLan Definitions
	 *
	 ****************************************************************/

#घोषणा TLAN_MIN_FRAME_SIZE	64
#घोषणा TLAN_MAX_FRAME_SIZE	1600

#घोषणा TLAN_NUM_RX_LISTS	32
#घोषणा TLAN_NUM_TX_LISTS	64

#घोषणा TLAN_IGNORE		0
#घोषणा TLAN_RECORD		1

#घोषणा TLAN_DBG(lvl, क्रमmat, args...)					\
	करो अणु								\
		अगर (debug&lvl)						\
			prपूर्णांकk(KERN_DEBUG "TLAN: " क्रमmat, ##args);	\
	पूर्ण जबतक (0)

#घोषणा TLAN_DEBUG_GNRL		0x0001
#घोषणा TLAN_DEBUG_TX		0x0002
#घोषणा TLAN_DEBUG_RX		0x0004
#घोषणा TLAN_DEBUG_LIST		0x0008
#घोषणा TLAN_DEBUG_PROBE	0x0010

#घोषणा TX_TIMEOUT		(10*HZ)	 /* We need समय क्रम स्वतः-neg */
#घोषणा MAX_TLAN_BOARDS		8	 /* Max number of boards installed
					    at a समय */


	/*****************************************************************
	 * Device Identअगरication Definitions
	 *
	 ****************************************************************/

#घोषणा PCI_DEVICE_ID_NETELLIGENT_10_T2			0xB012
#घोषणा PCI_DEVICE_ID_NETELLIGENT_10_100_WS_5100	0xB030
#अगर_अघोषित PCI_DEVICE_ID_OLICOM_OC2183
#घोषणा PCI_DEVICE_ID_OLICOM_OC2183			0x0013
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_OLICOM_OC2325
#घोषणा PCI_DEVICE_ID_OLICOM_OC2325			0x0012
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_OLICOM_OC2326
#घोषणा PCI_DEVICE_ID_OLICOM_OC2326			0x0014
#पूर्ण_अगर

काष्ठा tlan_adapter_entry अणु
	u16	venकरोr_id;
	u16	device_id;
	अक्षर	*device_label;
	u32	flags;
	u16	addr_ofs;
पूर्ण;

#घोषणा TLAN_ADAPTER_NONE		0x00000000
#घोषणा TLAN_ADAPTER_UNMANAGED_PHY	0x00000001
#घोषणा TLAN_ADAPTER_BIT_RATE_PHY	0x00000002
#घोषणा TLAN_ADAPTER_USE_INTERN_10	0x00000004
#घोषणा TLAN_ADAPTER_ACTIVITY_LED	0x00000008

#घोषणा TLAN_SPEED_DEFAULT	0
#घोषणा TLAN_SPEED_10		10
#घोषणा TLAN_SPEED_100		100

#घोषणा TLAN_DUPLEX_DEFAULT	0
#घोषणा TLAN_DUPLEX_HALF	1
#घोषणा TLAN_DUPLEX_FULL	2



	/*****************************************************************
	 * EISA Definitions
	 *
	 ****************************************************************/

#घोषणा EISA_ID      0xc80   /* EISA ID Registers */
#घोषणा EISA_ID0     0xc80   /* EISA ID Register 0 */
#घोषणा EISA_ID1     0xc81   /* EISA ID Register 1 */
#घोषणा EISA_ID2     0xc82   /* EISA ID Register 2 */
#घोषणा EISA_ID3     0xc83   /* EISA ID Register 3 */
#घोषणा EISA_CR      0xc84   /* EISA Control Register */
#घोषणा EISA_REG0    0xc88   /* EISA Configuration Register 0 */
#घोषणा EISA_REG1    0xc89   /* EISA Configuration Register 1 */
#घोषणा EISA_REG2    0xc8a   /* EISA Configuration Register 2 */
#घोषणा EISA_REG3    0xc8f   /* EISA Configuration Register 3 */
#घोषणा EISA_APROM   0xc90   /* Ethernet Address PROM */



	/*****************************************************************
	 * Rx/Tx List Definitions
	 *
	 ****************************************************************/

#घोषणा TLAN_BUFFERS_PER_LIST	10
#घोषणा TLAN_LAST_BUFFER	0x80000000
#घोषणा TLAN_CSTAT_UNUSED	0x8000
#घोषणा TLAN_CSTAT_FRM_CMP	0x4000
#घोषणा TLAN_CSTAT_READY	0x3000
#घोषणा TLAN_CSTAT_EOC		0x0800
#घोषणा TLAN_CSTAT_RX_ERROR	0x0400
#घोषणा TLAN_CSTAT_PASS_CRC	0x0200
#घोषणा TLAN_CSTAT_DP_PR	0x0100


काष्ठा tlan_buffer अणु
	u32	count;
	u32	address;
पूर्ण;


काष्ठा tlan_list अणु
	u32		क्रमward;
	u16		c_stat;
	u16		frame_size;
	काष्ठा tlan_buffer buffer[TLAN_BUFFERS_PER_LIST];
पूर्ण;


प्रकार u8 TLanBuffer[TLAN_MAX_FRAME_SIZE];




	/*****************************************************************
	 * PHY definitions
	 *
	 ****************************************************************/

#घोषणा TLAN_PHY_MAX_ADDR	0x1F
#घोषणा TLAN_PHY_NONE		0x20




	/*****************************************************************
	 * TLAN Private Inक्रमmation Structure
	 *
	 ****************************************************************/

काष्ठा tlan_priv अणु
	काष्ठा net_device       *next_device;
	काष्ठा pci_dev		*pci_dev;
	काष्ठा net_device       *dev;
	व्योम			*dma_storage;
	dma_addr_t		dma_storage_dma;
	अचिन्हित पूर्णांक		dma_size;
	u8			*pad_buffer;
	काष्ठा tlan_list	*rx_list;
	dma_addr_t		rx_list_dma;
	u8			*rx_buffer;
	dma_addr_t		rx_buffer_dma;
	u32			rx_head;
	u32			rx_tail;
	u32			rx_eoc_count;
	काष्ठा tlan_list	*tx_list;
	dma_addr_t		tx_list_dma;
	u8			*tx_buffer;
	dma_addr_t		tx_buffer_dma;
	u32			tx_head;
	u32			tx_in_progress;
	u32			tx_tail;
	u32			tx_busy_count;
	u32			phy_online;
	u32			समयr_set_at;
	u32			समयr_type;
	काष्ठा समयr_list	समयr;
	काष्ठा समयr_list	media_समयr;
	काष्ठा board		*adapter;
	u32			adapter_rev;
	u32			aui;
	u32			debug;
	u32			duplex;
	u32			phy[2];
	u32			phy_num;
	u32			speed;
	u8			tlan_rev;
	u8			tlan_full_duplex;
	spinlock_t		lock;
	काष्ठा work_काष्ठा			tlan_tqueue;
पूर्ण;




	/*****************************************************************
	 * TLan Driver Timer Definitions
	 *
	 ****************************************************************/

#घोषणा TLAN_TIMER_ACTIVITY		2
#घोषणा TLAN_TIMER_PHY_PDOWN		3
#घोषणा TLAN_TIMER_PHY_PUP		4
#घोषणा TLAN_TIMER_PHY_RESET		5
#घोषणा TLAN_TIMER_PHY_START_LINK	6
#घोषणा TLAN_TIMER_PHY_FINISH_AN	7
#घोषणा TLAN_TIMER_FINISH_RESET		8

#घोषणा TLAN_TIMER_ACT_DELAY		(HZ/10)




	/*****************************************************************
	 * TLan Driver Eeprom Definitions
	 *
	 ****************************************************************/

#घोषणा TLAN_EEPROM_ACK		0
#घोषणा TLAN_EEPROM_STOP	1

#घोषणा TLAN_EEPROM_SIZE	256



	/*****************************************************************
	 * Host Register Offsets and Contents
	 *
	 ****************************************************************/

#घोषणा TLAN_HOST_CMD			0x00
#घोषणा	TLAN_HC_GO		0x80000000
#घोषणा		TLAN_HC_STOP		0x40000000
#घोषणा		TLAN_HC_ACK		0x20000000
#घोषणा		TLAN_HC_CS_MASK		0x1FE00000
#घोषणा		TLAN_HC_EOC		0x00100000
#घोषणा		TLAN_HC_RT		0x00080000
#घोषणा		TLAN_HC_NES		0x00040000
#घोषणा		TLAN_HC_AD_RST		0x00008000
#घोषणा		TLAN_HC_LD_TMR		0x00004000
#घोषणा		TLAN_HC_LD_THR		0x00002000
#घोषणा		TLAN_HC_REQ_INT		0x00001000
#घोषणा		TLAN_HC_INT_OFF		0x00000800
#घोषणा		TLAN_HC_INT_ON		0x00000400
#घोषणा		TLAN_HC_AC_MASK		0x000000FF
#घोषणा TLAN_CH_PARM			0x04
#घोषणा TLAN_DIO_ADR			0x08
#घोषणा		TLAN_DA_ADR_INC		0x8000
#घोषणा		TLAN_DA_RAM_ADR		0x4000
#घोषणा TLAN_HOST_INT			0x0A
#घोषणा		TLAN_HI_IV_MASK		0x1FE0
#घोषणा		TLAN_HI_IT_MASK		0x001C
#घोषणा TLAN_DIO_DATA			0x0C


/* ThunderLAN Internal Register DIO Offsets */

#घोषणा TLAN_NET_CMD			0x00
#घोषणा		TLAN_NET_CMD_NRESET	0x80
#घोषणा		TLAN_NET_CMD_NWRAP	0x40
#घोषणा		TLAN_NET_CMD_CSF	0x20
#घोषणा		TLAN_NET_CMD_CAF	0x10
#घोषणा		TLAN_NET_CMD_NOBRX	0x08
#घोषणा		TLAN_NET_CMD_DUPLEX	0x04
#घोषणा		TLAN_NET_CMD_TRFRAM	0x02
#घोषणा		TLAN_NET_CMD_TXPACE	0x01
#घोषणा TLAN_NET_SIO			0x01
#घोषणा	TLAN_NET_SIO_MINTEN	0x80
#घोषणा		TLAN_NET_SIO_ECLOK	0x40
#घोषणा		TLAN_NET_SIO_ETXEN	0x20
#घोषणा		TLAN_NET_SIO_EDATA	0x10
#घोषणा		TLAN_NET_SIO_NMRST	0x08
#घोषणा		TLAN_NET_SIO_MCLK	0x04
#घोषणा		TLAN_NET_SIO_MTXEN	0x02
#घोषणा		TLAN_NET_SIO_MDATA	0x01
#घोषणा TLAN_NET_STS			0x02
#घोषणा		TLAN_NET_STS_MIRQ	0x80
#घोषणा		TLAN_NET_STS_HBEAT	0x40
#घोषणा		TLAN_NET_STS_TXSTOP	0x20
#घोषणा		TLAN_NET_STS_RXSTOP	0x10
#घोषणा		TLAN_NET_STS_RSRVD	0x0F
#घोषणा TLAN_NET_MASK			0x03
#घोषणा		TLAN_NET_MASK_MASK7	0x80
#घोषणा		TLAN_NET_MASK_MASK6	0x40
#घोषणा		TLAN_NET_MASK_MASK5	0x20
#घोषणा		TLAN_NET_MASK_MASK4	0x10
#घोषणा		TLAN_NET_MASK_RSRVD	0x0F
#घोषणा TLAN_NET_CONFIG			0x04
#घोषणा	TLAN_NET_CFG_RCLK	0x8000
#घोषणा		TLAN_NET_CFG_TCLK	0x4000
#घोषणा		TLAN_NET_CFG_BIT	0x2000
#घोषणा		TLAN_NET_CFG_RXCRC	0x1000
#घोषणा		TLAN_NET_CFG_PEF	0x0800
#घोषणा		TLAN_NET_CFG_1FRAG	0x0400
#घोषणा		TLAN_NET_CFG_1CHAN	0x0200
#घोषणा		TLAN_NET_CFG_MTEST	0x0100
#घोषणा		TLAN_NET_CFG_PHY_EN	0x0080
#घोषणा		TLAN_NET_CFG_MSMASK	0x007F
#घोषणा TLAN_MAN_TEST			0x06
#घोषणा TLAN_DEF_VENDOR_ID		0x08
#घोषणा TLAN_DEF_DEVICE_ID		0x0A
#घोषणा TLAN_DEF_REVISION		0x0C
#घोषणा TLAN_DEF_SUBCLASS		0x0D
#घोषणा TLAN_DEF_MIN_LAT		0x0E
#घोषणा TLAN_DEF_MAX_LAT		0x0F
#घोषणा TLAN_AREG_0			0x10
#घोषणा TLAN_AREG_1			0x16
#घोषणा TLAN_AREG_2			0x1C
#घोषणा TLAN_AREG_3			0x22
#घोषणा TLAN_HASH_1			0x28
#घोषणा TLAN_HASH_2			0x2C
#घोषणा TLAN_GOOD_TX_FRMS		0x30
#घोषणा TLAN_TX_UNDERUNS		0x33
#घोषणा TLAN_GOOD_RX_FRMS		0x34
#घोषणा TLAN_RX_OVERRUNS		0x37
#घोषणा TLAN_DEFERRED_TX		0x38
#घोषणा TLAN_CRC_ERRORS			0x3A
#घोषणा TLAN_CODE_ERRORS		0x3B
#घोषणा TLAN_MULTICOL_FRMS		0x3C
#घोषणा TLAN_SINGLECOL_FRMS		0x3E
#घोषणा TLAN_EXCESSCOL_FRMS		0x40
#घोषणा TLAN_LATE_COLS			0x41
#घोषणा TLAN_CARRIER_LOSS		0x42
#घोषणा TLAN_ACOMMIT			0x43
#घोषणा TLAN_LED_REG			0x44
#घोषणा		TLAN_LED_ACT		0x10
#घोषणा		TLAN_LED_LINK		0x01
#घोषणा TLAN_BSIZE_REG			0x45
#घोषणा TLAN_MAX_RX			0x46
#घोषणा TLAN_INT_DIS			0x48
#घोषणा		TLAN_ID_TX_EOC		0x04
#घोषणा		TLAN_ID_RX_खातापूर्ण		0x02
#घोषणा		TLAN_ID_RX_EOC		0x01



/* ThunderLAN Interrupt Codes */

#घोषणा TLAN_INT_NUMBER_OF_INTS	8

#घोषणा TLAN_INT_NONE			0x0000
#घोषणा TLAN_INT_TX_खातापूर्ण			0x0001
#घोषणा TLAN_INT_STAT_OVERFLOW		0x0002
#घोषणा TLAN_INT_RX_खातापूर्ण			0x0003
#घोषणा TLAN_INT_DUMMY			0x0004
#घोषणा TLAN_INT_TX_EOC			0x0005
#घोषणा TLAN_INT_STATUS_CHECK		0x0006
#घोषणा TLAN_INT_RX_EOC			0x0007



/* ThunderLAN MII Registers */

/* Generic MII/PHY Registers */

#घोषणा MII_GEN_CTL			0x00
#घोषणा	MII_GC_RESET		0x8000
#घोषणा		MII_GC_LOOPBK		0x4000
#घोषणा		MII_GC_SPEEDSEL		0x2000
#घोषणा		MII_GC_AUTOENB		0x1000
#घोषणा		MII_GC_PDOWN		0x0800
#घोषणा		MII_GC_ISOLATE		0x0400
#घोषणा		MII_GC_AUTORSRT		0x0200
#घोषणा		MII_GC_DUPLEX		0x0100
#घोषणा		MII_GC_COLTEST		0x0080
#घोषणा		MII_GC_RESERVED		0x007F
#घोषणा MII_GEN_STS			0x01
#घोषणा		MII_GS_100BT4		0x8000
#घोषणा		MII_GS_100BTXFD		0x4000
#घोषणा		MII_GS_100BTXHD		0x2000
#घोषणा		MII_GS_10BTFD		0x1000
#घोषणा		MII_GS_10BTHD		0x0800
#घोषणा		MII_GS_RESERVED		0x07C0
#घोषणा		MII_GS_AUTOCMPLT	0x0020
#घोषणा		MII_GS_RFLT		0x0010
#घोषणा		MII_GS_AUTONEG		0x0008
#घोषणा		MII_GS_LINK		0x0004
#घोषणा		MII_GS_JABBER		0x0002
#घोषणा		MII_GS_EXTCAP		0x0001
#घोषणा MII_GEN_ID_HI			0x02
#घोषणा MII_GEN_ID_LO			0x03
#घोषणा	MII_GIL_OUI		0xFC00
#घोषणा	MII_GIL_MODEL		0x03F0
#घोषणा	MII_GIL_REVISION	0x000F
#घोषणा MII_AN_ADV			0x04
#घोषणा MII_AN_LPA			0x05
#घोषणा MII_AN_EXP			0x06

/* ThunderLAN Specअगरic MII/PHY Registers */

#घोषणा TLAN_TLPHY_ID			0x10
#घोषणा TLAN_TLPHY_CTL			0x11
#घोषणा	TLAN_TC_IGLINK		0x8000
#घोषणा		TLAN_TC_SWAPOL		0x4000
#घोषणा		TLAN_TC_AUISEL		0x2000
#घोषणा		TLAN_TC_SQEEN		0x1000
#घोषणा		TLAN_TC_MTEST		0x0800
#घोषणा		TLAN_TC_RESERVED	0x07F8
#घोषणा		TLAN_TC_NFEW		0x0004
#घोषणा		TLAN_TC_INTEN		0x0002
#घोषणा		TLAN_TC_TINT		0x0001
#घोषणा TLAN_TLPHY_STS			0x12
#घोषणा		TLAN_TS_MINT		0x8000
#घोषणा		TLAN_TS_PHOK		0x4000
#घोषणा		TLAN_TS_POLOK		0x2000
#घोषणा		TLAN_TS_TPENERGY	0x1000
#घोषणा		TLAN_TS_RESERVED	0x0FFF
#घोषणा TLAN_TLPHY_PAR			0x19
#घोषणा		TLAN_PHY_CIM_STAT	0x0020
#घोषणा		TLAN_PHY_SPEED_100	0x0040
#घोषणा		TLAN_PHY_DUPLEX_FULL	0x0080
#घोषणा		TLAN_PHY_AN_EN_STAT     0x0400

/* National Sem. & Level1 PHY id's */
#घोषणा NAT_SEM_ID1			0x2000
#घोषणा NAT_SEM_ID2			0x5C01
#घोषणा LEVEL1_ID1			0x7810
#घोषणा LEVEL1_ID2			0x0000

#घोषणा CIRC_INC(a, b) अगर (++a >= b) a = 0

/* Routines to access पूर्णांकernal रेजिस्टरs. */

अटल अंतरभूत u8 tlan_dio_पढ़ो8(u16 base_addr, u16 पूर्णांकernal_addr)
अणु
	outw(पूर्णांकernal_addr, base_addr + TLAN_DIO_ADR);
	वापस inb((base_addr + TLAN_DIO_DATA) + (पूर्णांकernal_addr & 0x3));

पूर्ण




अटल अंतरभूत u16 tlan_dio_पढ़ो16(u16 base_addr, u16 पूर्णांकernal_addr)
अणु
	outw(पूर्णांकernal_addr, base_addr + TLAN_DIO_ADR);
	वापस inw((base_addr + TLAN_DIO_DATA) + (पूर्णांकernal_addr & 0x2));

पूर्ण




अटल अंतरभूत u32 tlan_dio_पढ़ो32(u16 base_addr, u16 पूर्णांकernal_addr)
अणु
	outw(पूर्णांकernal_addr, base_addr + TLAN_DIO_ADR);
	वापस inl(base_addr + TLAN_DIO_DATA);

पूर्ण




अटल अंतरभूत व्योम tlan_dio_ग_लिखो8(u16 base_addr, u16 पूर्णांकernal_addr, u8 data)
अणु
	outw(पूर्णांकernal_addr, base_addr + TLAN_DIO_ADR);
	outb(data, base_addr + TLAN_DIO_DATA + (पूर्णांकernal_addr & 0x3));

पूर्ण




अटल अंतरभूत व्योम tlan_dio_ग_लिखो16(u16 base_addr, u16 पूर्णांकernal_addr, u16 data)
अणु
	outw(पूर्णांकernal_addr, base_addr + TLAN_DIO_ADR);
	outw(data, base_addr + TLAN_DIO_DATA + (पूर्णांकernal_addr & 0x2));

पूर्ण




अटल अंतरभूत व्योम tlan_dio_ग_लिखो32(u16 base_addr, u16 पूर्णांकernal_addr, u32 data)
अणु
	outw(पूर्णांकernal_addr, base_addr + TLAN_DIO_ADR);
	outl(data, base_addr + TLAN_DIO_DATA + (पूर्णांकernal_addr & 0x2));

पूर्ण

#घोषणा tlan_clear_bit(bit, port)	outb_p(inb_p(port) & ~bit, port)
#घोषणा tlan_get_bit(bit, port)	((पूर्णांक) (inb_p(port) & bit))
#घोषणा tlan_set_bit(bit, port)	outb_p(inb_p(port) | bit, port)

/*
 * given 6 bytes, view them as 8 6-bit numbers and वापस the XOR of those
 * the code below is about seven बार as fast as the original code
 *
 * The original code was:
 *
 * u32	xor(u32 a, u32 b) अणु	वापस ((a && !b ) || (! a && b )); पूर्ण
 *
 * #घोषणा XOR8(a, b, c, d, e, f, g, h)	\
 *	xor(a, xor(b, xor(c, xor(d, xor(e, xor(f, xor(g, h)) ) ) ) ) )
 * #घोषणा DA(a, bit)		(( (u8) a[bit/8] ) & ( (u8) (1 << bit%8)) )
 *
 *	hash  = XOR8(DA(a,0), DA(a, 6), DA(a,12), DA(a,18), DA(a,24),
 *		      DA(a,30), DA(a,36), DA(a,42));
 *	hash |= XOR8(DA(a,1), DA(a, 7), DA(a,13), DA(a,19), DA(a,25),
 *		      DA(a,31), DA(a,37), DA(a,43)) << 1;
 *	hash |= XOR8(DA(a,2), DA(a, 8), DA(a,14), DA(a,20), DA(a,26),
 *		      DA(a,32), DA(a,38), DA(a,44)) << 2;
 *	hash |= XOR8(DA(a,3), DA(a, 9), DA(a,15), DA(a,21), DA(a,27),
 *		      DA(a,33), DA(a,39), DA(a,45)) << 3;
 *	hash |= XOR8(DA(a,4), DA(a,10), DA(a,16), DA(a,22), DA(a,28),
 *		      DA(a,34), DA(a,40), DA(a,46)) << 4;
 *	hash |= XOR8(DA(a,5), DA(a,11), DA(a,17), DA(a,23), DA(a,29),
 *		      DA(a,35), DA(a,41), DA(a,47)) << 5;
 *
 */
अटल अंतरभूत u32 tlan_hash_func(स्थिर u8 *a)
अणु
	u8     hash;

	hash = (a[0]^a[3]);		/* & 077 */
	hash ^= ((a[0]^a[3])>>6);	/* & 003 */
	hash ^= ((a[1]^a[4])<<2);	/* & 074 */
	hash ^= ((a[1]^a[4])>>4);	/* & 017 */
	hash ^= ((a[2]^a[5])<<4);	/* & 060 */
	hash ^= ((a[2]^a[5])>>2);	/* & 077 */

	वापस hash & 077;
पूर्ण
#पूर्ण_अगर
