<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* drivers/net/ethernet/micrel/ks8851.h
 *
 * Copyright 2009 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * KS8851 रेजिस्टर definitions
*/

#अगर_अघोषित __KS8851_H__
#घोषणा __KS8851_H__

#समावेश <linux/eeprom_93cx6.h>

#घोषणा KS_CCR					0x08
#घोषणा CCR_LE					(1 << 10)   /* KSZ8851-16MLL */
#घोषणा CCR_EEPROM				(1 << 9)
#घोषणा CCR_SPI					(1 << 8)    /* KSZ8851SNL    */
#घोषणा CCR_8BIT				(1 << 7)    /* KSZ8851-16MLL */
#घोषणा CCR_16BIT				(1 << 6)    /* KSZ8851-16MLL */
#घोषणा CCR_32BIT				(1 << 5)    /* KSZ8851-16MLL */
#घोषणा CCR_SHARED				(1 << 4)    /* KSZ8851-16MLL */
#घोषणा CCR_48PIN				(1 << 1)    /* KSZ8851-16MLL */
#घोषणा CCR_32PIN				(1 << 0)    /* KSZ8851SNL    */

/* MAC address रेजिस्टरs */
#घोषणा KS_MAR(_m)				(0x14 - (_m))
#घोषणा KS_MARL					0x10
#घोषणा KS_MARM					0x12
#घोषणा KS_MARH					0x14

#घोषणा KS_OBCR					0x20
#घोषणा OBCR_ODS_16mA				(1 << 6)

#घोषणा KS_EEPCR				0x22
#घोषणा EEPCR_EESRWA				(1 << 5)
#घोषणा EEPCR_EESA				(1 << 4)
#घोषणा EEPCR_EESB				(1 << 3)
#घोषणा EEPCR_EEDO				(1 << 2)
#घोषणा EEPCR_EESCK				(1 << 1)
#घोषणा EEPCR_EECS				(1 << 0)

#घोषणा KS_MBIR					0x24
#घोषणा MBIR_TXMBF				(1 << 12)
#घोषणा MBIR_TXMBFA				(1 << 11)
#घोषणा MBIR_RXMBF				(1 << 4)
#घोषणा MBIR_RXMBFA				(1 << 3)

#घोषणा KS_GRR					0x26
#घोषणा GRR_QMU					(1 << 1)
#घोषणा GRR_GSR					(1 << 0)

#घोषणा KS_WFCR					0x2A
#घोषणा WFCR_MPRXE				(1 << 7)
#घोषणा WFCR_WF3E				(1 << 3)
#घोषणा WFCR_WF2E				(1 << 2)
#घोषणा WFCR_WF1E				(1 << 1)
#घोषणा WFCR_WF0E				(1 << 0)

#घोषणा KS_WF0CRC0				0x30
#घोषणा KS_WF0CRC1				0x32
#घोषणा KS_WF0BM0				0x34
#घोषणा KS_WF0BM1				0x36
#घोषणा KS_WF0BM2				0x38
#घोषणा KS_WF0BM3				0x3A

#घोषणा KS_WF1CRC0				0x40
#घोषणा KS_WF1CRC1				0x42
#घोषणा KS_WF1BM0				0x44
#घोषणा KS_WF1BM1				0x46
#घोषणा KS_WF1BM2				0x48
#घोषणा KS_WF1BM3				0x4A

#घोषणा KS_WF2CRC0				0x50
#घोषणा KS_WF2CRC1				0x52
#घोषणा KS_WF2BM0				0x54
#घोषणा KS_WF2BM1				0x56
#घोषणा KS_WF2BM2				0x58
#घोषणा KS_WF2BM3				0x5A

#घोषणा KS_WF3CRC0				0x60
#घोषणा KS_WF3CRC1				0x62
#घोषणा KS_WF3BM0				0x64
#घोषणा KS_WF3BM1				0x66
#घोषणा KS_WF3BM2				0x68
#घोषणा KS_WF3BM3				0x6A

#घोषणा KS_TXCR					0x70
#घोषणा TXCR_TCGICMP				(1 << 8)
#घोषणा TXCR_TCGUDP				(1 << 7)
#घोषणा TXCR_TCGTCP				(1 << 6)
#घोषणा TXCR_TCGIP				(1 << 5)
#घोषणा TXCR_FTXQ				(1 << 4)
#घोषणा TXCR_TXFCE				(1 << 3)
#घोषणा TXCR_TXPE				(1 << 2)
#घोषणा TXCR_TXCRC				(1 << 1)
#घोषणा TXCR_TXE				(1 << 0)

#घोषणा KS_TXSR					0x72
#घोषणा TXSR_TXLC				(1 << 13)
#घोषणा TXSR_TXMC				(1 << 12)
#घोषणा TXSR_TXFID_MASK				(0x3f << 0)
#घोषणा TXSR_TXFID_SHIFT			(0)
#घोषणा TXSR_TXFID_GET(_v)			(((_v) >> 0) & 0x3f)

#घोषणा KS_RXCR1				0x74
#घोषणा RXCR1_FRXQ				(1 << 15)
#घोषणा RXCR1_RXUDPFCC				(1 << 14)
#घोषणा RXCR1_RXTCPFCC				(1 << 13)
#घोषणा RXCR1_RXIPFCC				(1 << 12)
#घोषणा RXCR1_RXPAFMA				(1 << 11)
#घोषणा RXCR1_RXFCE				(1 << 10)
#घोषणा RXCR1_RXEFE				(1 << 9)
#घोषणा RXCR1_RXMAFMA				(1 << 8)
#घोषणा RXCR1_RXBE				(1 << 7)
#घोषणा RXCR1_RXME				(1 << 6)
#घोषणा RXCR1_RXUE				(1 << 5)
#घोषणा RXCR1_RXAE				(1 << 4)
#घोषणा RXCR1_RXINVF				(1 << 1)
#घोषणा RXCR1_RXE				(1 << 0)

#घोषणा KS_RXCR2				0x76
#घोषणा RXCR2_SRDBL_MASK			(0x7 << 5)  /* KSZ8851SNL    */
#घोषणा RXCR2_SRDBL_SHIFT			(5)	    /* KSZ8851SNL    */
#घोषणा RXCR2_SRDBL_4B				(0x0 << 5)  /* KSZ8851SNL    */
#घोषणा RXCR2_SRDBL_8B				(0x1 << 5)  /* KSZ8851SNL    */
#घोषणा RXCR2_SRDBL_16B				(0x2 << 5)  /* KSZ8851SNL    */
#घोषणा RXCR2_SRDBL_32B				(0x3 << 5)  /* KSZ8851SNL    */
#घोषणा RXCR2_SRDBL_FRAME			(0x4 << 5)  /* KSZ8851SNL    */
#घोषणा RXCR2_IUFFP				(1 << 4)
#घोषणा RXCR2_RXIUFCEZ				(1 << 3)
#घोषणा RXCR2_UDPLFE				(1 << 2)
#घोषणा RXCR2_RXICMPFCC				(1 << 1)
#घोषणा RXCR2_RXSAF				(1 << 0)

#घोषणा KS_TXMIR				0x78

#घोषणा KS_RXFHSR				0x7C
#घोषणा RXFSHR_RXFV				(1 << 15)
#घोषणा RXFSHR_RXICMPFCS			(1 << 13)
#घोषणा RXFSHR_RXIPFCS				(1 << 12)
#घोषणा RXFSHR_RXTCPFCS				(1 << 11)
#घोषणा RXFSHR_RXUDPFCS				(1 << 10)
#घोषणा RXFSHR_RXBF				(1 << 7)
#घोषणा RXFSHR_RXMF				(1 << 6)
#घोषणा RXFSHR_RXUF				(1 << 5)
#घोषणा RXFSHR_RXMR				(1 << 4)
#घोषणा RXFSHR_RXFT				(1 << 3)
#घोषणा RXFSHR_RXFTL				(1 << 2)
#घोषणा RXFSHR_RXRF				(1 << 1)
#घोषणा RXFSHR_RXCE				(1 << 0)

#घोषणा KS_RXFHBCR				0x7E
#घोषणा RXFHBCR_CNT_MASK			(0xfff << 0)

#घोषणा KS_TXQCR				0x80
#घोषणा TXQCR_AETFE				(1 << 2)    /* KSZ8851SNL    */
#घोषणा TXQCR_TXQMAM				(1 << 1)
#घोषणा TXQCR_METFE				(1 << 0)

#घोषणा KS_RXQCR				0x82
#घोषणा RXQCR_RXDTTS				(1 << 12)
#घोषणा RXQCR_RXDBCTS				(1 << 11)
#घोषणा RXQCR_RXFCTS				(1 << 10)
#घोषणा RXQCR_RXIPHTOE				(1 << 9)
#घोषणा RXQCR_RXDTTE				(1 << 7)
#घोषणा RXQCR_RXDBCTE				(1 << 6)
#घोषणा RXQCR_RXFCTE				(1 << 5)
#घोषणा RXQCR_ADRFE				(1 << 4)
#घोषणा RXQCR_SDA				(1 << 3)
#घोषणा RXQCR_RRXEF				(1 << 0)

#घोषणा KS_TXFDPR				0x84
#घोषणा TXFDPR_TXFPAI				(1 << 14)
#घोषणा TXFDPR_TXFP_MASK			(0x7ff << 0)
#घोषणा TXFDPR_TXFP_SHIFT			(0)

#घोषणा KS_RXFDPR				0x86
#घोषणा RXFDPR_RXFPAI				(1 << 14)
#घोषणा RXFDPR_WST				(1 << 12)   /* KSZ8851-16MLL */
#घोषणा RXFDPR_EMS				(1 << 11)   /* KSZ8851-16MLL */
#घोषणा RXFDPR_RXFP_MASK			(0x7ff << 0)
#घोषणा RXFDPR_RXFP_SHIFT			(0)

#घोषणा KS_RXDTTR				0x8C
#घोषणा KS_RXDBCTR				0x8E

#घोषणा KS_IER					0x90
#घोषणा KS_ISR					0x92
#घोषणा IRQ_LCI					(1 << 15)
#घोषणा IRQ_TXI					(1 << 14)
#घोषणा IRQ_RXI					(1 << 13)
#घोषणा IRQ_RXOI				(1 << 11)
#घोषणा IRQ_TXPSI				(1 << 9)
#घोषणा IRQ_RXPSI				(1 << 8)
#घोषणा IRQ_TXSAI				(1 << 6)
#घोषणा IRQ_RXWFDI				(1 << 5)
#घोषणा IRQ_RXMPDI				(1 << 4)
#घोषणा IRQ_LDI					(1 << 3)
#घोषणा IRQ_EDI					(1 << 2)
#घोषणा IRQ_SPIBEI				(1 << 1)    /* KSZ8851SNL    */
#घोषणा IRQ_DEDI				(1 << 0)

#घोषणा KS_RXFCTR				0x9C
#घोषणा KS_RXFC					0x9D
#घोषणा RXFCTR_RXFC_MASK			(0xff << 8)
#घोषणा RXFCTR_RXFC_SHIFT			(8)
#घोषणा RXFCTR_RXFC_GET(_v)			(((_v) >> 8) & 0xff)
#घोषणा RXFCTR_RXFCT_MASK			(0xff << 0)
#घोषणा RXFCTR_RXFCT_SHIFT			(0)

#घोषणा KS_TXNTFSR				0x9E

#घोषणा KS_MAHTR0				0xA0
#घोषणा KS_MAHTR1				0xA2
#घोषणा KS_MAHTR2				0xA4
#घोषणा KS_MAHTR3				0xA6

#घोषणा KS_FCLWR				0xB0
#घोषणा KS_FCHWR				0xB2
#घोषणा KS_FCOWR				0xB4

#घोषणा KS_CIDER				0xC0
#घोषणा CIDER_ID				0x8870
#घोषणा CIDER_REV_MASK				(0x7 << 1)
#घोषणा CIDER_REV_SHIFT				(1)
#घोषणा CIDER_REV_GET(_v)			(((_v) >> 1) & 0x7)

#घोषणा KS_CGCR					0xC6

#घोषणा KS_IACR					0xC8
#घोषणा IACR_RDEN				(1 << 12)
#घोषणा IACR_TSEL_MASK				(0x3 << 10)
#घोषणा IACR_TSEL_SHIFT				(10)
#घोषणा IACR_TSEL_MIB				(0x3 << 10)
#घोषणा IACR_ADDR_MASK				(0x1f << 0)
#घोषणा IACR_ADDR_SHIFT				(0)

#घोषणा KS_IADLR				0xD0
#घोषणा KS_IAHDR				0xD2

#घोषणा KS_PMECR				0xD4
#घोषणा PMECR_PME_DELAY				(1 << 14)
#घोषणा PMECR_PME_POL				(1 << 12)
#घोषणा PMECR_WOL_WAKEUP			(1 << 11)
#घोषणा PMECR_WOL_MAGICPKT			(1 << 10)
#घोषणा PMECR_WOL_LINKUP			(1 << 9)
#घोषणा PMECR_WOL_ENERGY			(1 << 8)
#घोषणा PMECR_AUTO_WAKE_EN			(1 << 7)
#घोषणा PMECR_WAKEUP_NORMAL			(1 << 6)
#घोषणा PMECR_WKEVT_MASK			(0xf << 2)
#घोषणा PMECR_WKEVT_SHIFT			(2)
#घोषणा PMECR_WKEVT_GET(_v)			(((_v) >> 2) & 0xf)
#घोषणा PMECR_WKEVT_ENERGY			(0x1 << 2)
#घोषणा PMECR_WKEVT_LINK			(0x2 << 2)
#घोषणा PMECR_WKEVT_MAGICPKT			(0x4 << 2)
#घोषणा PMECR_WKEVT_FRAME			(0x8 << 2)
#घोषणा PMECR_PM_MASK				(0x3 << 0)
#घोषणा PMECR_PM_SHIFT				(0)
#घोषणा PMECR_PM_NORMAL				(0x0 << 0)
#घोषणा PMECR_PM_ENERGY				(0x1 << 0)
#घोषणा PMECR_PM_SOFTDOWN			(0x2 << 0)
#घोषणा PMECR_PM_POWERSAVE			(0x3 << 0)

/* Standard MII PHY data */
#घोषणा KS_P1MBCR				0xE4
#घोषणा KS_P1MBSR				0xE6
#घोषणा KS_PHY1ILR				0xE8
#घोषणा KS_PHY1IHR				0xEA
#घोषणा KS_P1ANAR				0xEC
#घोषणा KS_P1ANLPR				0xEE

#घोषणा KS_P1SCLMD				0xF4

#घोषणा KS_P1CR					0xF6
#घोषणा P1CR_LEDOFF				(1 << 15)
#घोषणा P1CR_TXIDS				(1 << 14)
#घोषणा P1CR_RESTARTAN				(1 << 13)
#घोषणा P1CR_DISAUTOMDIX			(1 << 10)
#घोषणा P1CR_FORCEMDIX				(1 << 9)
#घोषणा P1CR_AUTONEGEN				(1 << 7)
#घोषणा P1CR_FORCE100				(1 << 6)
#घोषणा P1CR_FORCEFDX				(1 << 5)
#घोषणा P1CR_ADV_FLOW				(1 << 4)
#घोषणा P1CR_ADV_100BT_FDX			(1 << 3)
#घोषणा P1CR_ADV_100BT_HDX			(1 << 2)
#घोषणा P1CR_ADV_10BT_FDX			(1 << 1)
#घोषणा P1CR_ADV_10BT_HDX			(1 << 0)

#घोषणा KS_P1SR					0xF8
#घोषणा P1SR_HP_MDIX				(1 << 15)
#घोषणा P1SR_REV_POL				(1 << 13)
#घोषणा P1SR_OP_100M				(1 << 10)
#घोषणा P1SR_OP_FDX				(1 << 9)
#घोषणा P1SR_OP_MDI				(1 << 7)
#घोषणा P1SR_AN_DONE				(1 << 6)
#घोषणा P1SR_LINK_GOOD				(1 << 5)
#घोषणा P1SR_PNTR_FLOW				(1 << 4)
#घोषणा P1SR_PNTR_100BT_FDX			(1 << 3)
#घोषणा P1SR_PNTR_100BT_HDX			(1 << 2)
#घोषणा P1SR_PNTR_10BT_FDX			(1 << 1)
#घोषणा P1SR_PNTR_10BT_HDX			(1 << 0)

/* TX Frame control */
#घोषणा TXFR_TXIC				(1 << 15)
#घोषणा TXFR_TXFID_MASK				(0x3f << 0)
#घोषणा TXFR_TXFID_SHIFT			(0)

/**
 * काष्ठा ks8851_rxctrl - KS8851 driver rx control
 * @mchash: Multicast hash-table data.
 * @rxcr1: KS_RXCR1 रेजिस्टर setting
 * @rxcr2: KS_RXCR2 रेजिस्टर setting
 *
 * Representation of the settings needs to control the receive filtering
 * such as the multicast hash-filter and the receive रेजिस्टर settings. This
 * is used to make the job of working out अगर the receive settings change and
 * then issuing the new settings to the worker that will send the necessary
 * commands.
 */
काष्ठा ks8851_rxctrl अणु
	u16	mchash[4];
	u16	rxcr1;
	u16	rxcr2;
पूर्ण;

/**
 * जोड़ ks8851_tx_hdr - tx header data
 * @txb: The header as bytes
 * @txw: The header as 16bit, little-endian words
 *
 * A dual representation of the tx header data to allow
 * access to inभागidual bytes, and to allow 16bit accesses
 * with 16bit alignment.
 */
जोड़ ks8851_tx_hdr अणु
	u8	txb[6];
	__le16	txw[3];
पूर्ण;

/**
 * काष्ठा ks8851_net - KS8851 driver निजी data
 * @netdev: The network device we're bound to
 * @statelock: Lock on this काष्ठाure क्रम tx list.
 * @mii: The MII state inक्रमmation क्रम the mii calls.
 * @rxctrl: RX settings क्रम @rxctrl_work.
 * @rxctrl_work: Work queue क्रम updating RX mode and multicast lists
 * @txq: Queue of packets क्रम transmission.
 * @txh: Space क्रम generating packet TX header in DMA-able data
 * @rxd: Space क्रम receiving SPI data, in DMA-able space.
 * @txd: Space क्रम transmitting SPI data, in DMA-able space.
 * @msg_enable: The message flags controlling driver output (see ethtool).
 * @fid: Incrementing frame id tag.
 * @rc_ier: Cached copy of KS_IER.
 * @rc_ccr: Cached copy of KS_CCR.
 * @rc_rxqcr: Cached copy of KS_RXQCR.
 * @eeprom: 93CX6 EEPROM state क्रम accessing on-board EEPROM.
 * @vdd_reg:	Optional regulator supplying the chip
 * @vdd_io: Optional digital घातer supply क्रम IO
 * @gpio: Optional reset_n gpio
 * @mii_bus: Poपूर्णांकer to MII bus काष्ठाure
 * @lock: Bus access lock callback
 * @unlock: Bus access unlock callback
 * @rdreg16: 16bit रेजिस्टर पढ़ो callback
 * @wrreg16: 16bit रेजिस्टर ग_लिखो callback
 * @rdfअगरo: FIFO पढ़ो callback
 * @wrfअगरo: FIFO ग_लिखो callback
 * @start_xmit: start_xmit() implementation callback
 * @rx_skb: rx_skb() implementation callback
 * @flush_tx_work: flush_tx_work() implementation callback
 *
 * The @statelock is used to protect inक्रमmation in the काष्ठाure which may
 * need to be accessed via several sources, such as the network driver layer
 * or one of the work queues.
 *
 * We align the buffers we may use क्रम rx/tx to ensure that अगर the SPI driver
 * wants to DMA map them, it will not have any problems with data the driver
 * modअगरies.
 */
काष्ठा ks8851_net अणु
	काष्ठा net_device	*netdev;
	spinlock_t		statelock;

	जोड़ ks8851_tx_hdr	txh ____cacheline_aligned;
	u8			rxd[8];
	u8			txd[8];

	u32			msg_enable ____cacheline_aligned;
	u16			tx_space;
	u8			fid;

	u16			rc_ier;
	u16			rc_rxqcr;
	u16			rc_ccr;

	काष्ठा mii_अगर_info	mii;
	काष्ठा ks8851_rxctrl	rxctrl;

	काष्ठा work_काष्ठा	rxctrl_work;

	काष्ठा sk_buff_head	txq;

	काष्ठा eeprom_93cx6	eeprom;
	काष्ठा regulator	*vdd_reg;
	काष्ठा regulator	*vdd_io;
	पूर्णांक			gpio;
	काष्ठा mii_bus		*mii_bus;

	व्योम			(*lock)(काष्ठा ks8851_net *ks,
					अचिन्हित दीर्घ *flags);
	व्योम			(*unlock)(काष्ठा ks8851_net *ks,
					  अचिन्हित दीर्घ *flags);
	अचिन्हित पूर्णांक		(*rdreg16)(काष्ठा ks8851_net *ks,
					   अचिन्हित पूर्णांक reg);
	व्योम			(*wrreg16)(काष्ठा ks8851_net *ks,
					   अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
	व्योम			(*rdfअगरo)(काष्ठा ks8851_net *ks, u8 *buff,
					  अचिन्हित पूर्णांक len);
	व्योम			(*wrfअगरo)(काष्ठा ks8851_net *ks,
					  काष्ठा sk_buff *txp, bool irq);
	netdev_tx_t		(*start_xmit)(काष्ठा sk_buff *skb,
					      काष्ठा net_device *dev);
	व्योम			(*rx_skb)(काष्ठा ks8851_net *ks,
					  काष्ठा sk_buff *skb);
	व्योम			(*flush_tx_work)(काष्ठा ks8851_net *ks);
पूर्ण;

पूर्णांक ks8851_probe_common(काष्ठा net_device *netdev, काष्ठा device *dev,
			पूर्णांक msg_en);
पूर्णांक ks8851_हटाओ_common(काष्ठा device *dev);
पूर्णांक ks8851_suspend(काष्ठा device *dev);
पूर्णांक ks8851_resume(काष्ठा device *dev);

अटल __maybe_unused SIMPLE_DEV_PM_OPS(ks8851_pm_ops,
					ks8851_suspend, ks8851_resume);

/**
 * ks8851_करोne_tx - update and then मुक्त skbuff after transmitting
 * @ks: The device state
 * @txb: The buffer transmitted
 */
अटल व्योम __maybe_unused ks8851_करोne_tx(काष्ठा ks8851_net *ks,
					  काष्ठा sk_buff *txb)
अणु
	काष्ठा net_device *dev = ks->netdev;

	dev->stats.tx_bytes += txb->len;
	dev->stats.tx_packets++;

	dev_kमुक्त_skb(txb);
पूर्ण

#पूर्ण_अगर /* __KS8851_H__ */
