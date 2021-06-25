<शैली गुरु>
/* version dependencies have been confined to a separate file */

/* Tunable parameters */
#घोषणा TX_RING_ENTRIES 64	/* 64-512?*/

#घोषणा RX_RING_ENTRIES 16 /* Do not change */
/* Internal स्थिरants */
#घोषणा TX_RING_BUFFER_SIZE	(TX_RING_ENTRIES*माप(tx_packet))
#घोषणा RX_BUFFER_SIZE 1546 /* ethenet packet size */
#घोषणा METH_RX_BUFF_SIZE 4096
#घोषणा METH_RX_HEAD 34 /* status + 3 quad garbage-fill + 2 byte zero-pad */
#घोषणा RX_BUFFER_OFFSET (माप(rx_status_vector)+2) /* staus vector + 2 bytes of padding */
#घोषणा RX_BUCKET_SIZE 256

/* For more detailed explanations of what each field menas,
   see Nick's great comments to #घोषणाs below (or करोcs, अगर
   you are lucky enough toget hold of them :)*/

/* tx status vector is written over tx command header upon
   dma completion. */

प्रकार काष्ठा tx_status_vector अणु
	u64		sent:1; /* always set to 1...*/
	u64		pad0:34;/* always set to 0 */
	u64		flags:9;			/*I'm too lazy to specअगरy each one separately at the moment*/
	u64		col_retry_cnt:4;	/*collision retry count*/
	u64		len:16;				/*Transmit length in bytes*/
पूर्ण tx_status_vector;

/*
 * Each packet is 128 bytes दीर्घ.
 * It consists of header, 0-3 concatination
 * buffer poपूर्णांकers and up to 120 data bytes.
 */
प्रकार काष्ठा tx_packet_hdr अणु
	u64		pad1:36; /*should be filled with 0 */
	u64		cat_ptr3_valid:1,	/*Concatination poपूर्णांकer valid flags*/
			cat_ptr2_valid:1,
			cat_ptr1_valid:1;
	u64		tx_पूर्णांक_flag:1;		/*Generate TX पूर्णांकrrupt when packet has been sent*/
	u64		term_dma_flag:1;	/*Terminate transmit DMA on transmit पात conditions*/
	u64		data_offset:7;		/*Starting byte offset in ring data block*/
	u64		data_len:16;		/*Length of valid data in bytes-1*/
पूर्ण tx_packet_hdr;
प्रकार जोड़ tx_cat_ptr अणु
	काष्ठा अणु
		u64		pad2:16; /* should be 0 */
		u64		len:16;				/*length of buffer data - 1*/
		u64		start_addr:29;		/*Physical starting address*/
		u64		pad1:3; /* should be zero */
	पूर्ण क्रमm;
	u64 raw;
पूर्ण tx_cat_ptr;

प्रकार काष्ठा tx_packet अणु
	जोड़ अणु
		tx_packet_hdr header;
		tx_status_vector res;
		u64 raw;
	पूर्णheader;
	जोड़ अणु
		tx_cat_ptr cat_buf[3];
		अक्षर dt[120];
	पूर्ण data;
पूर्ण tx_packet;

प्रकार जोड़ rx_status_vector अणु
	अस्थिर काष्ठा अणु
		u64		pad1:1;/*fill it with ones*/
		u64		pad2:15;/*fill with 0*/
		u64		ip_chk_sum:16;
		u64		seq_num:5;
		u64		mac_addr_match:1;
		u64		mcast_addr_match:1;
		u64		carrier_event_seen:1;
		u64		bad_packet:1;
		u64		दीर्घ_event_seen:1;
		u64		invalid_preamble:1;
		u64		broadcast:1;
		u64		multicast:1;
		u64		crc_error:1;
		u64		huh:1;/*???*/
		u64		rx_code_violation:1;
		u64		rx_len:16;
	पूर्ण parsed;
	अस्थिर u64 raw;
पूर्ण rx_status_vector;

प्रकार काष्ठा rx_packet अणु
	rx_status_vector status;
        u64 pad[3]; /* For whatever reason, there needs to be 4 द्विगुन-word offset */
        u16 pad2;
	अक्षर buf[METH_RX_BUFF_SIZE-माप(rx_status_vector)-3*माप(u64)-माप(u16)];/* data */
पूर्ण rx_packet;

#घोषणा TX_INFO_RPTR    0x00FF0000
#घोषणा TX_INFO_WPTR    0x000000FF

	/* Bits in METH_MAC */

#घोषणा SGI_MAC_RESET		BIT(0)	/* 0: MAC110 active in run mode, 1: Global reset संकेत to MAC110 core is active */
#घोषणा METH_PHY_FDX		BIT(1) /* 0: Disable full duplex, 1: Enable full duplex */
#घोषणा METH_PHY_LOOP	BIT(2) /* 0: Normal operation, follows 10/100mbit and M10T/MII select, 1: loops पूर्णांकernal MII bus */
				       /*    selects ignored */
#घोषणा METH_100MBIT		BIT(3) /* 0: 10meg mode, 1: 100meg mode */
#घोषणा METH_PHY_MII		BIT(4) /* 0: MII selected, 1: SIA selected */
				       /*   Note: when loopback is set this bit becomes collision control.  Setting this bit will */
				       /*         cause a collision to be reported. */

				       /* Bits 5 and 6 are used to determine the Destination address filter mode */
#घोषणा METH_ACCEPT_MY 0			/* 00: Accept PHY address only */
#घोषणा METH_ACCEPT_MCAST 0x20	/* 01: Accept physical, broadcast, and multicast filter matches only */
#घोषणा METH_ACCEPT_AMCAST 0x40	/* 10: Accept physical, broadcast, and all multicast packets */
#घोषणा METH_PROMISC 0x60		/* 11: Promiscious mode */

#घोषणा METH_PHY_LINK_FAIL	BIT(7) /* 0: Link failure detection disabled, 1: Hardware scans क्रम link failure in PHY */

#घोषणा METH_MAC_IPG	0x1ffff00

#घोषणा METH_DEFAULT_IPG ((17<<15) | (11<<22) | (21<<8))
						/* 0x172e5c00 */ /* 23, 23, 23 */ /*0x54A9500 *//*21,21,21*/
				       /* Bits 8 through 14 are used to determine Inter-Packet Gap between "Back to Back" packets */
				       /* The gap depends on the घड़ी speed of the link, 80ns per increment क्रम 100baseT, 800ns  */
				       /* per increment क्रम 10BaseT */

				       /* Bits 15 through 21 are used to determine IPGR1 */

				       /* Bits 22 through 28 are used to determine IPGR2 */

#घोषणा METH_REV_SHIFT 29       /* Bits 29 through 31 are used to determine the revision */
				       /* 000: Initial revision */
				       /* 001: First revision, Improved TX concatenation */


/* DMA control bits */
#घोषणा METH_RX_OFFSET_SHIFT 12 /* Bits 12:14 of DMA control रेजिस्टर indicate starting offset of packet data क्रम RX operation */
#घोषणा METH_RX_DEPTH_SHIFT 4 /* Bits 8:4 define RX fअगरo depth -- when # of RX fअगरo entries != depth, पूर्णांकerrupt is generted */

#घोषणा METH_DMA_TX_EN BIT(1) /* enable TX DMA */
#घोषणा METH_DMA_TX_INT_EN BIT(0) /* enable TX Buffer Empty पूर्णांकerrupt */
#घोषणा METH_DMA_RX_EN BIT(15) /* Enable RX */
#घोषणा METH_DMA_RX_INT_EN BIT(9) /* Enable पूर्णांकerrupt on RX packet */

/* RX FIFO MCL Info bits */
#घोषणा METH_RX_FIFO_WPTR(x)   (((x)>>16)&0xf)
#घोषणा METH_RX_FIFO_RPTR(x)   (((x)>>8)&0xf)
#घोषणा METH_RX_FIFO_DEPTH(x)  ((x)&0x1f)

/* RX status bits */

#घोषणा METH_RX_ST_VALID BIT(63)
#घोषणा METH_RX_ST_RCV_CODE_VIOLATION BIT(16)
#घोषणा METH_RX_ST_DRBL_NBL BIT(17)
#घोषणा METH_RX_ST_CRC_ERR BIT(18)
#घोषणा METH_RX_ST_MCAST_PKT BIT(19)
#घोषणा METH_RX_ST_BCAST_PKT BIT(20)
#घोषणा METH_RX_ST_INV_PREAMBLE_CTX BIT(21)
#घोषणा METH_RX_ST_LONG_EVT_SEEN BIT(22)
#घोषणा METH_RX_ST_BAD_PACKET BIT(23)
#घोषणा METH_RX_ST_CARRIER_EVT_SEEN BIT(24)
#घोषणा METH_RX_ST_MCAST_FILTER_MATCH BIT(25)
#घोषणा METH_RX_ST_PHYS_ADDR_MATCH BIT(26)

#घोषणा METH_RX_STATUS_ERRORS \
	( \
	METH_RX_ST_RCV_CODE_VIOLATION| \
	METH_RX_ST_CRC_ERR| \
	METH_RX_ST_INV_PREAMBLE_CTX| \
	METH_RX_ST_LONG_EVT_SEEN| \
	METH_RX_ST_BAD_PACKET| \
	METH_RX_ST_CARRIER_EVT_SEEN \
	)
	/* Bits in METH_INT */
	/* Write _1_ to corresponding bit to clear */
#घोषणा METH_INT_TX_EMPTY	BIT(0)	/* 0: No पूर्णांकerrupt pending, 1: The TX ring buffer is empty */
#घोषणा METH_INT_TX_PKT		BIT(1)	/* 0: No पूर्णांकerrupt pending */
					      	/* 1: A TX message had the INT request bit set, the packet has been sent. */
#घोषणा METH_INT_TX_LINK_FAIL	BIT(2)	/* 0: No पूर्णांकerrupt pending, 1: PHY has reported a link failure */
#घोषणा METH_INT_MEM_ERROR	BIT(3)	/* 0: No पूर्णांकerrupt pending */
						/* 1: A memory error occurred during DMA, DMA stopped, Fatal */
#घोषणा METH_INT_TX_ABORT		BIT(4)	/* 0: No पूर्णांकerrupt pending, 1: The TX पातed operation, DMA stopped, FATAL */
#घोषणा METH_INT_RX_THRESHOLD	BIT(5)	/* 0: No पूर्णांकerrupt pending, 1: Selected receive threshold condition Valid */
#घोषणा METH_INT_RX_UNDERFLOW	BIT(6)	/* 0: No पूर्णांकerrupt pending, 1: FIFO was empty, packet could not be queued */
#घोषणा METH_INT_RX_OVERFLOW		BIT(7)	/* 0: No पूर्णांकerrupt pending, 1: DMA FIFO Overflow, DMA stopped, FATAL */

/*#घोषणा METH_INT_RX_RPTR_MASK 0x0001F00*/		/* Bits 8 through 12 alias of RX पढ़ो-poपूर्णांकer */
#घोषणा METH_INT_RX_RPTR_MASK 0x0000F00		/* Bits 8 through 11 alias of RX पढ़ो-poपूर्णांकer - so, is Rx FIFO 16 or 32 entry?*/

						/* Bits 13 through 15 are always 0. */

#घोषणा METH_INT_TX_RPTR_MASK	0x1FF0000        /* Bits 16 through 24 alias of TX पढ़ो-poपूर्णांकer */

#घोषणा METH_INT_RX_SEQ_MASK	0x2E000000	/* Bits 25 through 29 are the starting seq number क्रम the message at the */

						/* top of the queue */

#घोषणा METH_INT_ERROR	(METH_INT_TX_LINK_FAIL| \
			METH_INT_MEM_ERROR| \
			METH_INT_TX_ABORT| \
			METH_INT_RX_OVERFLOW| \
			METH_INT_RX_UNDERFLOW)

#घोषणा METH_INT_MCAST_HASH		BIT(30) /* If RX DMA is enabled the hash select logic output is latched here */

/* TX status bits */
#घोषणा METH_TX_ST_DONE      BIT(63) /* TX complete */
#घोषणा METH_TX_ST_SUCCESS   BIT(23) /* Packet was transmitted successfully */
#घोषणा METH_TX_ST_TOOLONG   BIT(24) /* TX पात due to excessive length */
#घोषणा METH_TX_ST_UNDERRUN  BIT(25) /* TX पात due to underrun (?) */
#घोषणा METH_TX_ST_EXCCOLL   BIT(26) /* TX पात due to excess collisions */
#घोषणा METH_TX_ST_DEFER     BIT(27) /* TX पात due to excess deferals */
#घोषणा METH_TX_ST_LATECOLL  BIT(28) /* TX पात due to late collision */


/* Tx command header bits */
#घोषणा METH_TX_CMD_INT_EN BIT(24) /* Generate TX पूर्णांकerrupt when packet is sent */

/* Phy MDIO पूर्णांकerface busy flag */
#घोषणा MDIO_BUSY    BIT(16)
#घोषणा MDIO_DATA_MASK 0xFFFF
/* PHY defines */
#घोषणा PHY_QS6612X    0x0181441    /* Quality TX */
#घोषणा PHY_ICS1889    0x0015F41    /* ICS FX */
#घोषणा PHY_ICS1890    0x0015F42    /* ICS TX */
#घोषणा PHY_DP83840    0x20005C0    /* National TX */

#घोषणा ADVANCE_RX_PTR(x)  x=(x+1)&(RX_RING_ENTRIES-1)
