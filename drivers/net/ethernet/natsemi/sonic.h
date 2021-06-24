<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header file क्रम sonic.c
 *
 * (C) Walकरोrf Electronics, Germany
 * Written by Andreas Busse
 *
 * NOTE: most of the काष्ठाure definitions here are endian dependent.
 * If you want to use this driver on big endian machines, the data
 * and pad काष्ठाure members must be exchanged. Also, the काष्ठाures
 * need to be changed accordingly to the bus size.
 *
 * 981229 MSch:	did just that क्रम the 68k Mac port (32 bit, big endian)
 *
 * 990611 David Huggins-Daines <dhd@debian.org>: This machine असलtraction
 * करोes not cope with 16-bit bus sizes very well.  Thereक्रमe I have
 * rewritten it with ugly macros and evil अंतरभूतs.
 *
 * 050625 Finn Thain: पूर्णांकroduced more 32-bit cards and dhd's support
 *        क्रम 16-bit cards (from the mac68k project).
 */

#अगर_अघोषित SONIC_H
#घोषणा SONIC_H


/*
 * SONIC रेजिस्टर offsets
 */

#घोषणा SONIC_CMD              0x00
#घोषणा SONIC_DCR              0x01
#घोषणा SONIC_RCR              0x02
#घोषणा SONIC_TCR              0x03
#घोषणा SONIC_IMR              0x04
#घोषणा SONIC_ISR              0x05

#घोषणा SONIC_UTDA             0x06
#घोषणा SONIC_CTDA             0x07

#घोषणा SONIC_URDA             0x0d
#घोषणा SONIC_CRDA             0x0e
#घोषणा SONIC_EOBC             0x13
#घोषणा SONIC_URRA             0x14
#घोषणा SONIC_RSA              0x15
#घोषणा SONIC_REA              0x16
#घोषणा SONIC_RRP              0x17
#घोषणा SONIC_RWP              0x18
#घोषणा SONIC_RSC              0x2b

#घोषणा SONIC_CEP              0x21
#घोषणा SONIC_CAP2             0x22
#घोषणा SONIC_CAP1             0x23
#घोषणा SONIC_CAP0             0x24
#घोषणा SONIC_CE               0x25
#घोषणा SONIC_CDP              0x26
#घोषणा SONIC_CDC              0x27

#घोषणा SONIC_WT0              0x29
#घोषणा SONIC_WT1              0x2a

#घोषणा SONIC_SR               0x28


/* test-only रेजिस्टरs */

#घोषणा SONIC_TPS		0x08
#घोषणा SONIC_TFC		0x09
#घोषणा SONIC_TSA0		0x0a
#घोषणा SONIC_TSA1		0x0b
#घोषणा SONIC_TFS		0x0c

#घोषणा SONIC_CRBA0		0x0f
#घोषणा SONIC_CRBA1		0x10
#घोषणा SONIC_RBWC0		0x11
#घोषणा SONIC_RBWC1		0x12
#घोषणा SONIC_TTDA		0x20
#घोषणा SONIC_MDT		0x2f

#घोषणा SONIC_TRBA0		0x19
#घोषणा SONIC_TRBA1		0x1a
#घोषणा SONIC_TBWC0		0x1b
#घोषणा SONIC_TBWC1		0x1c
#घोषणा SONIC_LLFA		0x1f

#घोषणा SONIC_ADDR0		0x1d
#घोषणा SONIC_ADDR1		0x1e

/*
 * Error counters
 */

#घोषणा SONIC_CRCT              0x2c
#घोषणा SONIC_FAET              0x2d
#घोषणा SONIC_MPT               0x2e

#घोषणा SONIC_DCR2              0x3f

/*
 * SONIC command bits
 */

#घोषणा SONIC_CR_LCAM           0x0200
#घोषणा SONIC_CR_RRRA           0x0100
#घोषणा SONIC_CR_RST            0x0080
#घोषणा SONIC_CR_ST             0x0020
#घोषणा SONIC_CR_STP            0x0010
#घोषणा SONIC_CR_RXEN           0x0008
#घोषणा SONIC_CR_RXDIS          0x0004
#घोषणा SONIC_CR_TXP            0x0002
#घोषणा SONIC_CR_HTX            0x0001

#घोषणा SONIC_CR_ALL (SONIC_CR_LCAM | SONIC_CR_RRRA | \
		      SONIC_CR_RXEN | SONIC_CR_TXP)

/*
 * SONIC data configuration bits
 */

#घोषणा SONIC_DCR_EXBUS         0x8000
#घोषणा SONIC_DCR_LBR           0x2000
#घोषणा SONIC_DCR_PO1           0x1000
#घोषणा SONIC_DCR_PO0           0x0800
#घोषणा SONIC_DCR_SBUS          0x0400
#घोषणा SONIC_DCR_USR1          0x0200
#घोषणा SONIC_DCR_USR0          0x0100
#घोषणा SONIC_DCR_WC1           0x0080
#घोषणा SONIC_DCR_WC0           0x0040
#घोषणा SONIC_DCR_DW            0x0020
#घोषणा SONIC_DCR_BMS           0x0010
#घोषणा SONIC_DCR_RFT1          0x0008
#घोषणा SONIC_DCR_RFT0          0x0004
#घोषणा SONIC_DCR_TFT1          0x0002
#घोषणा SONIC_DCR_TFT0          0x0001

/*
 * Constants क्रम the SONIC receive control रेजिस्टर.
 */

#घोषणा SONIC_RCR_ERR           0x8000
#घोषणा SONIC_RCR_RNT           0x4000
#घोषणा SONIC_RCR_BRD           0x2000
#घोषणा SONIC_RCR_PRO           0x1000
#घोषणा SONIC_RCR_AMC           0x0800
#घोषणा SONIC_RCR_LB1           0x0400
#घोषणा SONIC_RCR_LB0           0x0200

#घोषणा SONIC_RCR_MC            0x0100
#घोषणा SONIC_RCR_BC            0x0080
#घोषणा SONIC_RCR_LPKT          0x0040
#घोषणा SONIC_RCR_CRS           0x0020
#घोषणा SONIC_RCR_COL           0x0010
#घोषणा SONIC_RCR_CRCR          0x0008
#घोषणा SONIC_RCR_FAER          0x0004
#घोषणा SONIC_RCR_LBK           0x0002
#घोषणा SONIC_RCR_PRX           0x0001

#घोषणा SONIC_RCR_LB_OFF        0
#घोषणा SONIC_RCR_LB_MAC        SONIC_RCR_LB0
#घोषणा SONIC_RCR_LB_ENDEC      SONIC_RCR_LB1
#घोषणा SONIC_RCR_LB_TRANS      (SONIC_RCR_LB0 | SONIC_RCR_LB1)

/* शेष RCR setup */

#घोषणा SONIC_RCR_DEFAULT       (SONIC_RCR_BRD)


/*
 * SONIC Transmit Control रेजिस्टर bits
 */

#घोषणा SONIC_TCR_PINTR         0x8000
#घोषणा SONIC_TCR_POWC          0x4000
#घोषणा SONIC_TCR_CRCI          0x2000
#घोषणा SONIC_TCR_EXDIS         0x1000
#घोषणा SONIC_TCR_EXD           0x0400
#घोषणा SONIC_TCR_DEF           0x0200
#घोषणा SONIC_TCR_NCRS          0x0100
#घोषणा SONIC_TCR_CRLS          0x0080
#घोषणा SONIC_TCR_EXC           0x0040
#घोषणा SONIC_TCR_OWC           0x0020
#घोषणा SONIC_TCR_PMB           0x0008
#घोषणा SONIC_TCR_FU            0x0004
#घोषणा SONIC_TCR_BCM           0x0002
#घोषणा SONIC_TCR_PTX           0x0001

#घोषणा SONIC_TCR_DEFAULT       0x0000

/*
 * Constants क्रम the SONIC_INTERRUPT_MASK and
 * SONIC_INTERRUPT_STATUS रेजिस्टरs.
 */

#घोषणा SONIC_INT_BR		0x4000
#घोषणा SONIC_INT_HBL		0x2000
#घोषणा SONIC_INT_LCD		0x1000
#घोषणा SONIC_INT_PINT		0x0800
#घोषणा SONIC_INT_PKTRX		0x0400
#घोषणा SONIC_INT_TXDN		0x0200
#घोषणा SONIC_INT_TXER		0x0100
#घोषणा SONIC_INT_TC		0x0080
#घोषणा SONIC_INT_RDE		0x0040
#घोषणा SONIC_INT_RBE		0x0020
#घोषणा SONIC_INT_RBAE		0x0010
#घोषणा SONIC_INT_CRC		0x0008
#घोषणा SONIC_INT_FAE		0x0004
#घोषणा SONIC_INT_MP		0x0002
#घोषणा SONIC_INT_RFO		0x0001


/*
 * The पूर्णांकerrupts we allow.
 */

#घोषणा SONIC_IMR_DEFAULT     ( SONIC_INT_BR | \
                                SONIC_INT_LCD | \
                                SONIC_INT_RFO | \
                                SONIC_INT_PKTRX | \
                                SONIC_INT_TXDN | \
                                SONIC_INT_TXER | \
                                SONIC_INT_RDE | \
                                SONIC_INT_RBAE | \
                                SONIC_INT_CRC | \
                                SONIC_INT_FAE | \
                                SONIC_INT_MP)


#घोषणा SONIC_EOL       0x0001
#घोषणा CAM_DESCRIPTORS 16

/* Offsets in the various DMA buffers accessed by the SONIC */

#घोषणा SONIC_BITMODE16 0
#घोषणा SONIC_BITMODE32 1
#घोषणा SONIC_BUS_SCALE(biपंचांगode) ((biपंचांगode) ? 4 : 2)
/* Note!  These are all measured in bus-size units, so use SONIC_BUS_SCALE */
#घोषणा SIZखातापूर्ण_SONIC_RR 4
#घोषणा SONIC_RR_BUFADR_L  0
#घोषणा SONIC_RR_BUFADR_H  1
#घोषणा SONIC_RR_बफ_मानE_L 2
#घोषणा SONIC_RR_बफ_मानE_H 3

#घोषणा SIZखातापूर्ण_SONIC_RD 7
#घोषणा SONIC_RD_STATUS   0
#घोषणा SONIC_RD_PKTLEN   1
#घोषणा SONIC_RD_PKTPTR_L 2
#घोषणा SONIC_RD_PKTPTR_H 3
#घोषणा SONIC_RD_SEQNO    4
#घोषणा SONIC_RD_LINK     5
#घोषणा SONIC_RD_IN_USE   6

#घोषणा SIZखातापूर्ण_SONIC_TD 8
#घोषणा SONIC_TD_STATUS       0
#घोषणा SONIC_TD_CONFIG       1
#घोषणा SONIC_TD_PKTSIZE      2
#घोषणा SONIC_TD_FRAG_COUNT   3
#घोषणा SONIC_TD_FRAG_PTR_L   4
#घोषणा SONIC_TD_FRAG_PTR_H   5
#घोषणा SONIC_TD_FRAG_SIZE    6
#घोषणा SONIC_TD_LINK         7

#घोषणा SIZखातापूर्ण_SONIC_CD 4
#घोषणा SONIC_CD_ENTRY_POINTER 0
#घोषणा SONIC_CD_CAP0          1
#घोषणा SONIC_CD_CAP1          2
#घोषणा SONIC_CD_CAP2          3

#घोषणा SIZखातापूर्ण_SONIC_CDA ((CAM_DESCRIPTORS * SIZखातापूर्ण_SONIC_CD) + 1)
#घोषणा SONIC_CDA_CAM_ENABLE   (CAM_DESCRIPTORS * SIZखातापूर्ण_SONIC_CD)

/*
 * Some tunables क्रम the buffer areas. Power of 2 is required
 * the current driver uses one receive buffer क्रम each descriptor.
 *
 * MSch: use more buffer space क्रम the slow m68k Macs!
 */
#घोषणा SONIC_NUM_RRS   16            /* number of receive resources */
#घोषणा SONIC_NUM_RDS   SONIC_NUM_RRS /* number of receive descriptors */
#घोषणा SONIC_NUM_TDS   16            /* number of transmit descriptors */

#घोषणा SONIC_RRS_MASK  (SONIC_NUM_RRS - 1)
#घोषणा SONIC_RDS_MASK  (SONIC_NUM_RDS - 1)
#घोषणा SONIC_TDS_MASK  (SONIC_NUM_TDS - 1)

#घोषणा SONIC_RBSIZE	1520          /* size of one resource buffer */

/* Again, measured in bus size units! */
#घोषणा SIZखातापूर्ण_SONIC_DESC (SIZखातापूर्ण_SONIC_CDA	\
	+ (SIZखातापूर्ण_SONIC_TD * SONIC_NUM_TDS)	\
	+ (SIZखातापूर्ण_SONIC_RD * SONIC_NUM_RDS)	\
	+ (SIZखातापूर्ण_SONIC_RR * SONIC_NUM_RRS))

/* Inक्रमmation that need to be kept क्रम each board. */
काष्ठा sonic_local अणु
	/* Bus size.  0 == 16 bits, 1 == 32 bits. */
	पूर्णांक dma_biपंचांगode;
	/* Register offset within the दीर्घword (independent of endianness,
	   and varies from one type of Macपूर्णांकosh SONIC to another
	   (Aarrgh)) */
	पूर्णांक reg_offset;
	व्योम *descriptors;
	/* Crud.  These areas have to be within the same 64K.  Thereक्रमe
       we allocate a desriptors page, and poपूर्णांक these to places within it. */
	व्योम *cda;  /* CAM descriptor area */
	व्योम *tda;  /* Transmit descriptor area */
	व्योम *rra;  /* Receive resource area */
	व्योम *rda;  /* Receive descriptor area */
	काष्ठा sk_buff* अस्थिर rx_skb[SONIC_NUM_RRS];	/* packets to be received */
	काष्ठा sk_buff* अस्थिर tx_skb[SONIC_NUM_TDS];	/* packets to be transmitted */
	अचिन्हित पूर्णांक tx_len[SONIC_NUM_TDS]; /* lengths of tx DMA mappings */
	/* Logical DMA addresses on MIPS, bus addresses on m68k
	 * (so "laddr" is a bit misleading) */
	dma_addr_t descriptors_laddr;
	u32 cda_laddr;              /* logical DMA address of CDA */
	u32 tda_laddr;              /* logical DMA address of TDA */
	u32 rra_laddr;              /* logical DMA address of RRA */
	u32 rda_laddr;              /* logical DMA address of RDA */
	dma_addr_t rx_laddr[SONIC_NUM_RRS]; /* logical DMA addresses of rx skbuffs */
	dma_addr_t tx_laddr[SONIC_NUM_TDS]; /* logical DMA addresses of tx skbuffs */
	अचिन्हित पूर्णांक cur_rx;
	अचिन्हित पूर्णांक cur_tx;           /* first unacked transmit packet */
	अचिन्हित पूर्णांक eol_rx;
	अचिन्हित पूर्णांक eol_tx;           /* last unacked transmit packet */
	पूर्णांक msg_enable;
	काष्ठा device *device;         /* generic device */
	काष्ठा net_device_stats stats;
	spinlock_t lock;
पूर्ण;

#घोषणा TX_TIMEOUT (3 * HZ)

/* Index to functions, as function prototypes. */

अटल पूर्णांक sonic_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक sonic_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल irqवापस_t sonic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल व्योम sonic_rx(काष्ठा net_device *dev);
अटल पूर्णांक sonic_बंद(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *sonic_get_stats(काष्ठा net_device *dev);
अटल व्योम sonic_multicast_list(काष्ठा net_device *dev);
अटल पूर्णांक sonic_init(काष्ठा net_device *dev, bool may_sleep);
अटल व्योम sonic_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम sonic_msg_init(काष्ठा net_device *dev);
अटल पूर्णांक sonic_alloc_descriptors(काष्ठा net_device *dev);

/* Internal अंतरभूतs क्रम पढ़ोing/writing DMA buffers.  Note that bus
   size and endianness matter here, whereas they करोn't क्रम रेजिस्टरs,
   as far as we can tell. */
/* OpenBSD calls this "SWO".  I'd like to think that sonic_buf_put()
   is a much better name. */
अटल अंतरभूत व्योम sonic_buf_put(u16 *base, पूर्णांक biपंचांगode,
				 पूर्णांक offset, __u16 val)
अणु
	अगर (biपंचांगode)
#अगर_घोषित __BIG_ENDIAN
		__raw_ग_लिखोw(val, base + (offset * 2) + 1);
#अन्यथा
		__raw_ग_लिखोw(val, base + (offset * 2) + 0);
#पूर्ण_अगर
	अन्यथा
		__raw_ग_लिखोw(val, base + (offset * 1) + 0);
पूर्ण

अटल अंतरभूत __u16 sonic_buf_get(u16 *base, पूर्णांक biपंचांगode,
				  पूर्णांक offset)
अणु
	अगर (biपंचांगode)
#अगर_घोषित __BIG_ENDIAN
		वापस __raw_पढ़ोw(base + (offset * 2) + 1);
#अन्यथा
		वापस __raw_पढ़ोw(base + (offset * 2) + 0);
#पूर्ण_अगर
	अन्यथा
		वापस __raw_पढ़ोw(base + (offset * 1) + 0);
पूर्ण

/* Inlines that you should actually use क्रम पढ़ोing/writing DMA buffers */
अटल अंतरभूत व्योम sonic_cda_put(काष्ठा net_device* dev, पूर्णांक entry,
				 पूर्णांक offset, __u16 val)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	sonic_buf_put(lp->cda, lp->dma_biपंचांगode,
		      (entry * SIZखातापूर्ण_SONIC_CD) + offset, val);
पूर्ण

अटल अंतरभूत __u16 sonic_cda_get(काष्ठा net_device* dev, पूर्णांक entry,
				  पूर्णांक offset)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	वापस sonic_buf_get(lp->cda, lp->dma_biपंचांगode,
			     (entry * SIZखातापूर्ण_SONIC_CD) + offset);
पूर्ण

अटल अंतरभूत व्योम sonic_set_cam_enable(काष्ठा net_device* dev, __u16 val)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	sonic_buf_put(lp->cda, lp->dma_biपंचांगode, SONIC_CDA_CAM_ENABLE, val);
पूर्ण

अटल अंतरभूत __u16 sonic_get_cam_enable(काष्ठा net_device* dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	वापस sonic_buf_get(lp->cda, lp->dma_biपंचांगode, SONIC_CDA_CAM_ENABLE);
पूर्ण

अटल अंतरभूत व्योम sonic_tda_put(काष्ठा net_device* dev, पूर्णांक entry,
				 पूर्णांक offset, __u16 val)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	sonic_buf_put(lp->tda, lp->dma_biपंचांगode,
		      (entry * SIZखातापूर्ण_SONIC_TD) + offset, val);
पूर्ण

अटल अंतरभूत __u16 sonic_tda_get(काष्ठा net_device* dev, पूर्णांक entry,
				  पूर्णांक offset)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	वापस sonic_buf_get(lp->tda, lp->dma_biपंचांगode,
			     (entry * SIZखातापूर्ण_SONIC_TD) + offset);
पूर्ण

अटल अंतरभूत व्योम sonic_rda_put(काष्ठा net_device* dev, पूर्णांक entry,
				 पूर्णांक offset, __u16 val)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	sonic_buf_put(lp->rda, lp->dma_biपंचांगode,
		      (entry * SIZखातापूर्ण_SONIC_RD) + offset, val);
पूर्ण

अटल अंतरभूत __u16 sonic_rda_get(काष्ठा net_device* dev, पूर्णांक entry,
				  पूर्णांक offset)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	वापस sonic_buf_get(lp->rda, lp->dma_biपंचांगode,
			     (entry * SIZखातापूर्ण_SONIC_RD) + offset);
पूर्ण

अटल अंतरभूत व्योम sonic_rra_put(काष्ठा net_device* dev, पूर्णांक entry,
				 पूर्णांक offset, __u16 val)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	sonic_buf_put(lp->rra, lp->dma_biपंचांगode,
		      (entry * SIZखातापूर्ण_SONIC_RR) + offset, val);
पूर्ण

अटल अंतरभूत __u16 sonic_rra_get(काष्ठा net_device* dev, पूर्णांक entry,
				  पूर्णांक offset)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	वापस sonic_buf_get(lp->rra, lp->dma_biपंचांगode,
			     (entry * SIZखातापूर्ण_SONIC_RR) + offset);
पूर्ण

अटल अंतरभूत u16 sonic_rr_addr(काष्ठा net_device *dev, पूर्णांक entry)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);

	वापस lp->rra_laddr +
	       entry * SIZखातापूर्ण_SONIC_RR * SONIC_BUS_SCALE(lp->dma_biपंचांगode);
पूर्ण

अटल अंतरभूत u16 sonic_rr_entry(काष्ठा net_device *dev, u16 addr)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);

	वापस (addr - (u16)lp->rra_laddr) / (SIZखातापूर्ण_SONIC_RR *
					      SONIC_BUS_SCALE(lp->dma_biपंचांगode));
पूर्ण

अटल स्थिर अक्षर version[] =
    "sonic.c:v0.92 20.9.98 tsbogend@alpha.franken.de\n";

#पूर्ण_अगर /* SONIC_H */
