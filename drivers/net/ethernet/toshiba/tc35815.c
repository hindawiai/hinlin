<शैली गुरु>
/*
 * tc35815.c: A TOSHIBA TC35815CF PCI 10/100Mbps ethernet driver क्रम linux.
 *
 * Based on skelton.c by Donald Becker.
 *
 * This driver is a replacement of older and less मुख्यtained version.
 * This is a header of the older version:
 *	-----<snip>-----
 *	Copyright 2001 MontaVista Software Inc.
 *	Author: MontaVista Software, Inc.
 *		ahennessy@mvista.com
 *	Copyright (C) 2000-2001 Toshiba Corporation
 *	अटल स्थिर अक्षर *version =
 *		"tc35815.c:v0.00 26/07/2000 by Toshiba Corporation\n";
 *	-----<snip>-----
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright TOSHIBA CORPORATION 2004-2005
 * All Rights Reserved.
 */

#घोषणा DRV_VERSION	"1.39"
अटल स्थिर अक्षर version[] = "tc35815.c:v" DRV_VERSION "\n";
#घोषणा MODNAME			"tc35815"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prefetch.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>

क्रमागत tc35815_chiptype अणु
	TC35815CF = 0,
	TC35815_NWU,
	TC35815_TX4939,
पूर्ण;

/* indexed by tc35815_chiptype, above */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
पूर्ण chip_info[] = अणु
	अणु "TOSHIBA TC35815CF 10/100BaseTX" पूर्ण,
	अणु "TOSHIBA TC35815 with Wake on LAN" पूर्ण,
	अणु "TOSHIBA TC35815/TX4939" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id tc35815_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_TOSHIBA_2, PCI_DEVICE_ID_TOSHIBA_TC35815CF), .driver_data = TC35815CF पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_TOSHIBA_2, PCI_DEVICE_ID_TOSHIBA_TC35815_NWU), .driver_data = TC35815_NWU पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_TOSHIBA_2, PCI_DEVICE_ID_TOSHIBA_TC35815_TX4939), .driver_data = TC35815_TX4939 पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, tc35815_pci_tbl);

/* see MODULE_PARM_DESC */
अटल काष्ठा tc35815_options अणु
	पूर्णांक speed;
	पूर्णांक duplex;
पूर्ण options;

/*
 * Registers
 */
काष्ठा tc35815_regs अणु
	__u32 DMA_Ctl;		/* 0x00 */
	__u32 TxFrmPtr;
	__u32 TxThrsh;
	__u32 TxPollCtr;
	__u32 BLFrmPtr;
	__u32 RxFragSize;
	__u32 Int_En;
	__u32 FDA_Bas;
	__u32 FDA_Lim;		/* 0x20 */
	__u32 Int_Src;
	__u32 unused0[2];
	__u32 PauseCnt;
	__u32 RemPauCnt;
	__u32 TxCtlFrmStat;
	__u32 unused1;
	__u32 MAC_Ctl;		/* 0x40 */
	__u32 CAM_Ctl;
	__u32 Tx_Ctl;
	__u32 Tx_Stat;
	__u32 Rx_Ctl;
	__u32 Rx_Stat;
	__u32 MD_Data;
	__u32 MD_CA;
	__u32 CAM_Adr;		/* 0x60 */
	__u32 CAM_Data;
	__u32 CAM_Ena;
	__u32 PROM_Ctl;
	__u32 PROM_Data;
	__u32 Algn_Cnt;
	__u32 CRC_Cnt;
	__u32 Miss_Cnt;
पूर्ण;

/*
 * Bit assignments
 */
/* DMA_Ctl bit assign ------------------------------------------------------- */
#घोषणा DMA_RxAlign	       0x00c00000 /* 1:Reception Alignment	     */
#घोषणा DMA_RxAlign_1	       0x00400000
#घोषणा DMA_RxAlign_2	       0x00800000
#घोषणा DMA_RxAlign_3	       0x00c00000
#घोषणा DMA_M66EnStat	       0x00080000 /* 1:66MHz Enable State	     */
#घोषणा DMA_IntMask	       0x00040000 /* 1:Interrupt mask		     */
#घोषणा DMA_SWIntReq	       0x00020000 /* 1:Software Interrupt request    */
#घोषणा DMA_TxWakeUp	       0x00010000 /* 1:Transmit Wake Up		     */
#घोषणा DMA_RxBigE	       0x00008000 /* 1:Receive Big Endian	     */
#घोषणा DMA_TxBigE	       0x00004000 /* 1:Transmit Big Endian	     */
#घोषणा DMA_TestMode	       0x00002000 /* 1:Test Mode		     */
#घोषणा DMA_PowrMgmnt	       0x00001000 /* 1:Power Management		     */
#घोषणा DMA_DmBurst_Mask       0x000001fc /* DMA Burst size		     */

/* RxFragSize bit assign ---------------------------------------------------- */
#घोषणा RxFrag_EnPack	       0x00008000 /* 1:Enable Packing		     */
#घोषणा RxFrag_MinFragMask     0x00000ffc /* Minimum Fragment		     */

/* MAC_Ctl bit assign ------------------------------------------------------- */
#घोषणा MAC_Link10	       0x00008000 /* 1:Link Status 10Mbits	     */
#घोषणा MAC_EnMissRoll	       0x00002000 /* 1:Enable Missed Roll	     */
#घोषणा MAC_MissRoll	       0x00000400 /* 1:Missed Roll		     */
#घोषणा MAC_Loop10	       0x00000080 /* 1:Loop 10 Mbps		     */
#घोषणा MAC_Conn_Auto	       0x00000000 /*00:Connection mode (Automatic)   */
#घोषणा MAC_Conn_10M	       0x00000020 /*01:		       (10Mbps endec)*/
#घोषणा MAC_Conn_Mll	       0x00000040 /*10:		       (Mll घड़ी)   */
#घोषणा MAC_MacLoop	       0x00000010 /* 1:MAC Loopback		     */
#घोषणा MAC_FullDup	       0x00000008 /* 1:Full Duplex 0:Half Duplex     */
#घोषणा MAC_Reset	       0x00000004 /* 1:Software Reset		     */
#घोषणा MAC_HaltImm	       0x00000002 /* 1:Halt Immediate		     */
#घोषणा MAC_HaltReq	       0x00000001 /* 1:Halt request		     */

/* PROM_Ctl bit assign ------------------------------------------------------ */
#घोषणा PROM_Busy	       0x00008000 /* 1:Busy (Start Operation)	     */
#घोषणा PROM_Read	       0x00004000 /*10:Read operation		     */
#घोषणा PROM_Write	       0x00002000 /*01:Write operation		     */
#घोषणा PROM_Erase	       0x00006000 /*11:Erase operation		     */
					  /*00:Enable or Disable Writting,   */
					  /*	  as specअगरied in PROM_Addr. */
#घोषणा PROM_Addr_Ena	       0x00000030 /*11xxxx:PROM Write enable	     */
					  /*00xxxx:	      disable	     */

/* CAM_Ctl bit assign ------------------------------------------------------- */
#घोषणा CAM_CompEn	       0x00000010 /* 1:CAM Compare Enable	     */
#घोषणा CAM_NegCAM	       0x00000008 /* 1:Reject packets CAM recognizes,*/
					  /*			accept other */
#घोषणा CAM_BroadAcc	       0x00000004 /* 1:Broadcast assept		     */
#घोषणा CAM_GroupAcc	       0x00000002 /* 1:Multicast assept		     */
#घोषणा CAM_StationAcc	       0x00000001 /* 1:unicast accept		     */

/* CAM_Ena bit assign ------------------------------------------------------- */
#घोषणा CAM_ENTRY_MAX		       21   /* CAM Data entry max count	     */
#घोषणा CAM_Ena_Mask ((1<<CAM_ENTRY_MAX)-1) /* CAM Enable bits (Max 21bits)  */
#घोषणा CAM_Ena_Bit(index)	(1 << (index))
#घोषणा CAM_ENTRY_DESTINATION	0
#घोषणा CAM_ENTRY_SOURCE	1
#घोषणा CAM_ENTRY_MACCTL	20

/* Tx_Ctl bit assign -------------------------------------------------------- */
#घोषणा Tx_En		       0x00000001 /* 1:Transmit enable		     */
#घोषणा Tx_TxHalt	       0x00000002 /* 1:Transmit Halt Request	     */
#घोषणा Tx_NoPad	       0x00000004 /* 1:Suppress Padding		     */
#घोषणा Tx_NoCRC	       0x00000008 /* 1:Suppress Padding		     */
#घोषणा Tx_FBack	       0x00000010 /* 1:Fast Back-off		     */
#घोषणा Tx_EnUnder	       0x00000100 /* 1:Enable Underrun		     */
#घोषणा Tx_EnExDefer	       0x00000200 /* 1:Enable Excessive Deferral     */
#घोषणा Tx_EnLCarr	       0x00000400 /* 1:Enable Lost Carrier	     */
#घोषणा Tx_EnExColl	       0x00000800 /* 1:Enable Excessive Collision    */
#घोषणा Tx_EnLateColl	       0x00001000 /* 1:Enable Late Collision	     */
#घोषणा Tx_EnTxPar	       0x00002000 /* 1:Enable Transmit Parity	     */
#घोषणा Tx_EnComp	       0x00004000 /* 1:Enable Completion	     */

/* Tx_Stat bit assign ------------------------------------------------------- */
#घोषणा Tx_TxColl_MASK	       0x0000000F /* Tx Collision Count		     */
#घोषणा Tx_ExColl	       0x00000010 /* Excessive Collision	     */
#घोषणा Tx_TXDefer	       0x00000020 /* Transmit Defered		     */
#घोषणा Tx_Paused	       0x00000040 /* Transmit Paused		     */
#घोषणा Tx_IntTx	       0x00000080 /* Interrupt on Tx		     */
#घोषणा Tx_Under	       0x00000100 /* Underrun			     */
#घोषणा Tx_Defer	       0x00000200 /* Deferral			     */
#घोषणा Tx_NCarr	       0x00000400 /* No Carrier			     */
#घोषणा Tx_10Stat	       0x00000800 /* 10Mbps Status		     */
#घोषणा Tx_LateColl	       0x00001000 /* Late Collision		     */
#घोषणा Tx_TxPar	       0x00002000 /* Tx Parity Error		     */
#घोषणा Tx_Comp		       0x00004000 /* Completion			     */
#घोषणा Tx_Halted	       0x00008000 /* Tx Halted			     */
#घोषणा Tx_SQErr	       0x00010000 /* Signal Quality Error(SQE)	     */

/* Rx_Ctl bit assign -------------------------------------------------------- */
#घोषणा Rx_EnGood	       0x00004000 /* 1:Enable Good		     */
#घोषणा Rx_EnRxPar	       0x00002000 /* 1:Enable Receive Parity	     */
#घोषणा Rx_EnLongErr	       0x00000800 /* 1:Enable Long Error	     */
#घोषणा Rx_EnOver	       0x00000400 /* 1:Enable OverFlow		     */
#घोषणा Rx_EnCRCErr	       0x00000200 /* 1:Enable CRC Error		     */
#घोषणा Rx_EnAlign	       0x00000100 /* 1:Enable Alignment		     */
#घोषणा Rx_IgnoreCRC	       0x00000040 /* 1:Ignore CRC Value		     */
#घोषणा Rx_StripCRC	       0x00000010 /* 1:Strip CRC Value		     */
#घोषणा Rx_ShortEn	       0x00000008 /* 1:Short Enable		     */
#घोषणा Rx_LongEn	       0x00000004 /* 1:Long Enable		     */
#घोषणा Rx_RxHalt	       0x00000002 /* 1:Receive Halt Request	     */
#घोषणा Rx_RxEn		       0x00000001 /* 1:Receive Intrrupt Enable	     */

/* Rx_Stat bit assign ------------------------------------------------------- */
#घोषणा Rx_Halted	       0x00008000 /* Rx Halted			     */
#घोषणा Rx_Good		       0x00004000 /* Rx Good			     */
#घोषणा Rx_RxPar	       0x00002000 /* Rx Parity Error		     */
#घोषणा Rx_TypePkt	       0x00001000 /* Rx Type Packet		     */
#घोषणा Rx_LongErr	       0x00000800 /* Rx Long Error		     */
#घोषणा Rx_Over		       0x00000400 /* Rx Overflow		     */
#घोषणा Rx_CRCErr	       0x00000200 /* Rx CRC Error		     */
#घोषणा Rx_Align	       0x00000100 /* Rx Alignment Error		     */
#घोषणा Rx_10Stat	       0x00000080 /* Rx 10Mbps Status		     */
#घोषणा Rx_IntRx	       0x00000040 /* Rx Interrupt		     */
#घोषणा Rx_CtlRecd	       0x00000020 /* Rx Control Receive		     */
#घोषणा Rx_InLenErr	       0x00000010 /* Rx In Range Frame Length Error  */

#घोषणा Rx_Stat_Mask	       0x0000FFF0 /* Rx All Status Mask		     */

/* Int_En bit assign -------------------------------------------------------- */
#घोषणा Int_NRAbtEn	       0x00000800 /* 1:Non-recoverable Abort Enable  */
#घोषणा Int_TxCtlCmpEn	       0x00000400 /* 1:Transmit Ctl Complete Enable  */
#घोषणा Int_DmParErrEn	       0x00000200 /* 1:DMA Parity Error Enable	     */
#घोषणा Int_DParDEn	       0x00000100 /* 1:Data Parity Error Enable	     */
#घोषणा Int_EarNotEn	       0x00000080 /* 1:Early Notअगरy Enable	     */
#घोषणा Int_DParErrEn	       0x00000040 /* 1:Detected Parity Error Enable  */
#घोषणा Int_SSysErrEn	       0x00000020 /* 1:Signalled System Error Enable */
#घोषणा Int_RMasAbtEn	       0x00000010 /* 1:Received Master Abort Enable  */
#घोषणा Int_RTargAbtEn	       0x00000008 /* 1:Received Target Abort Enable  */
#घोषणा Int_STargAbtEn	       0x00000004 /* 1:Signalled Target Abort Enable */
#घोषणा Int_BLExEn	       0x00000002 /* 1:Buffer List Exhausted Enable  */
#घोषणा Int_FDAExEn	       0x00000001 /* 1:Free Descriptor Area	     */
					  /*		   Exhausted Enable  */

/* Int_Src bit assign ------------------------------------------------------- */
#घोषणा Int_NRabt	       0x00004000 /* 1:Non Recoverable error	     */
#घोषणा Int_DmParErrStat       0x00002000 /* 1:DMA Parity Error & Clear	     */
#घोषणा Int_BLEx	       0x00001000 /* 1:Buffer List Empty & Clear     */
#घोषणा Int_FDAEx	       0x00000800 /* 1:FDA Empty & Clear	     */
#घोषणा Int_IntNRAbt	       0x00000400 /* 1:Non Recoverable Abort	     */
#घोषणा Int_IntCmp	       0x00000200 /* 1:MAC control packet complete   */
#घोषणा Int_IntExBD	       0x00000100 /* 1:Interrupt Extra BD & Clear    */
#घोषणा Int_DmParErr	       0x00000080 /* 1:DMA Parity Error & Clear	     */
#घोषणा Int_IntEarNot	       0x00000040 /* 1:Receive Data ग_लिखो & Clear    */
#घोषणा Int_SWInt	       0x00000020 /* 1:Software request & Clear	     */
#घोषणा Int_IntBLEx	       0x00000010 /* 1:Buffer List Empty & Clear     */
#घोषणा Int_IntFDAEx	       0x00000008 /* 1:FDA Empty & Clear	     */
#घोषणा Int_IntPCI	       0x00000004 /* 1:PCI controller & Clear	     */
#घोषणा Int_IntMacRx	       0x00000002 /* 1:Rx controller & Clear	     */
#घोषणा Int_IntMacTx	       0x00000001 /* 1:Tx controller & Clear	     */

/* MD_CA bit assign --------------------------------------------------------- */
#घोषणा MD_CA_PreSup	       0x00001000 /* 1:Preamble Suppress		     */
#घोषणा MD_CA_Busy	       0x00000800 /* 1:Busy (Start Operation)	     */
#घोषणा MD_CA_Wr	       0x00000400 /* 1:Write 0:Read		     */


/*
 * Descriptors
 */

/* Frame descriptor */
काष्ठा FDesc अणु
	अस्थिर __u32 FDNext;
	अस्थिर __u32 FDSystem;
	अस्थिर __u32 FDStat;
	अस्थिर __u32 FDCtl;
पूर्ण;

/* Buffer descriptor */
काष्ठा BDesc अणु
	अस्थिर __u32 BuffData;
	अस्थिर __u32 BDCtl;
पूर्ण;

#घोषणा FD_ALIGN	16

/* Frame Descriptor bit assign ---------------------------------------------- */
#घोषणा FD_FDLength_MASK       0x0000FFFF /* Length MASK		     */
#घोषणा FD_BDCnt_MASK	       0x001F0000 /* BD count MASK in FD	     */
#घोषणा FD_FrmOpt_MASK	       0x7C000000 /* Frame option MASK		     */
#घोषणा FD_FrmOpt_BigEndian    0x40000000 /* Tx/Rx */
#घोषणा FD_FrmOpt_IntTx	       0x20000000 /* Tx only */
#घोषणा FD_FrmOpt_NoCRC	       0x10000000 /* Tx only */
#घोषणा FD_FrmOpt_NoPadding    0x08000000 /* Tx only */
#घोषणा FD_FrmOpt_Packing      0x04000000 /* Rx only */
#घोषणा FD_CownsFD	       0x80000000 /* FD Controller owner bit	     */
#घोषणा FD_Next_EOL	       0x00000001 /* FD EOL indicator		     */
#घोषणा FD_BDCnt_SHIFT	       16

/* Buffer Descriptor bit assign --------------------------------------------- */
#घोषणा BD_BuffLength_MASK     0x0000FFFF /* Receive Data Size		     */
#घोषणा BD_RxBDID_MASK	       0x00FF0000 /* BD ID Number MASK		     */
#घोषणा BD_RxBDSeqN_MASK       0x7F000000 /* Rx BD Sequence Number	     */
#घोषणा BD_CownsBD	       0x80000000 /* BD Controller owner bit	     */
#घोषणा BD_RxBDID_SHIFT	       16
#घोषणा BD_RxBDSeqN_SHIFT      24


/* Some useful स्थिरants. */

#घोषणा TX_CTL_CMD	(Tx_EnTxPar | Tx_EnLateColl | \
	Tx_EnExColl | Tx_EnLCarr | Tx_EnExDefer | Tx_EnUnder | \
	Tx_En)	/* maybe  0x7b01 */
/* Do not use Rx_StripCRC -- it causes trouble on BLEx/FDAEx condition */
#घोषणा RX_CTL_CMD	(Rx_EnGood | Rx_EnRxPar | Rx_EnLongErr | Rx_EnOver \
	| Rx_EnCRCErr | Rx_EnAlign | Rx_RxEn) /* maybe 0x6f01 */
#घोषणा INT_EN_CMD  (Int_NRAbtEn | \
	Int_DmParErrEn | Int_DParDEn | Int_DParErrEn | \
	Int_SSysErrEn  | Int_RMasAbtEn | Int_RTargAbtEn | \
	Int_STargAbtEn | \
	Int_BLExEn  | Int_FDAExEn) /* maybe 0xb7f*/
#घोषणा DMA_CTL_CMD	DMA_BURST_SIZE
#घोषणा HAVE_DMA_RXALIGN(lp)	likely((lp)->chiptype != TC35815CF)

/* Tuning parameters */
#घोषणा DMA_BURST_SIZE	32
#घोषणा TX_THRESHOLD	1024
/* used threshold with packet max byte क्रम low pci transfer ability.*/
#घोषणा TX_THRESHOLD_MAX 1536
/* setting threshold max value when overrun error occurred this count. */
#घोषणा TX_THRESHOLD_KEEP_LIMIT 10

/* 16 + RX_BUF_NUM * 8 + RX_FD_NUM * 16 + TX_FD_NUM * 32 <= PAGE_SIZE*FD_PAGE_NUM */
#घोषणा FD_PAGE_NUM 4
#घोषणा RX_BUF_NUM	128	/* < 256 */
#घोषणा RX_FD_NUM	256	/* >= 32 */
#घोषणा TX_FD_NUM	128
#अगर RX_CTL_CMD & Rx_LongEn
#घोषणा RX_BUF_SIZE	PAGE_SIZE
#या_अगर RX_CTL_CMD & Rx_StripCRC
#घोषणा RX_BUF_SIZE	\
	L1_CACHE_ALIGN(ETH_FRAME_LEN + VLAN_HLEN + NET_IP_ALIGN)
#अन्यथा
#घोषणा RX_BUF_SIZE	\
	L1_CACHE_ALIGN(ETH_FRAME_LEN + VLAN_HLEN + ETH_FCS_LEN + NET_IP_ALIGN)
#पूर्ण_अगर
#घोषणा RX_FD_RESERVE	(2 / 2)	/* max 2 BD per RxFD */
#घोषणा NAPI_WEIGHT	16

काष्ठा TxFD अणु
	काष्ठा FDesc fd;
	काष्ठा BDesc bd;
	काष्ठा BDesc unused;
पूर्ण;

काष्ठा RxFD अणु
	काष्ठा FDesc fd;
	काष्ठा BDesc bd[];	/* variable length */
पूर्ण;

काष्ठा FrFD अणु
	काष्ठा FDesc fd;
	काष्ठा BDesc bd[RX_BUF_NUM];
पूर्ण;


#घोषणा tc_पढ़ोl(addr)	ioपढ़ो32(addr)
#घोषणा tc_ग_लिखोl(d, addr)	ioग_लिखो32(d, addr)

#घोषणा TC35815_TX_TIMEOUT  msecs_to_jअगरfies(400)

/* Inक्रमmation that need to be kept क्रम each controller. */
काष्ठा tc35815_local अणु
	काष्ठा pci_dev *pci_dev;

	काष्ठा net_device *dev;
	काष्ठा napi_काष्ठा napi;

	/* statistics */
	काष्ठा अणु
		पूर्णांक max_tx_qlen;
		पूर्णांक tx_पूर्णांकs;
		पूर्णांक rx_पूर्णांकs;
		पूर्णांक tx_underrun;
	पूर्ण lstats;

	/* Tx control lock.  This protects the transmit buffer ring
	 * state aदीर्घ with the "tx full" state of the driver.  This
	 * means all netअगर_queue flow control actions are रक्षित
	 * by this lock as well.
	 */
	spinlock_t lock;
	spinlock_t rx_lock;

	काष्ठा mii_bus *mii_bus;
	पूर्णांक duplex;
	पूर्णांक speed;
	पूर्णांक link;
	काष्ठा work_काष्ठा restart_work;

	/*
	 * Transmitting: Batch Mode.
	 *	1 BD in 1 TxFD.
	 * Receiving: Non-Packing Mode.
	 *	1 circular FD क्रम Free Buffer List.
	 *	RX_BUF_NUM BD in Free Buffer FD.
	 *	One Free Buffer BD has ETH_FRAME_LEN data buffer.
	 */
	व्योम *fd_buf;	/* क्रम TxFD, RxFD, FrFD */
	dma_addr_t fd_buf_dma;
	काष्ठा TxFD *tfd_base;
	अचिन्हित पूर्णांक tfd_start;
	अचिन्हित पूर्णांक tfd_end;
	काष्ठा RxFD *rfd_base;
	काष्ठा RxFD *rfd_limit;
	काष्ठा RxFD *rfd_cur;
	काष्ठा FrFD *fbl_ptr;
	अचिन्हित पूर्णांक fbl_count;
	काष्ठा अणु
		काष्ठा sk_buff *skb;
		dma_addr_t skb_dma;
	पूर्ण tx_skbs[TX_FD_NUM], rx_skbs[RX_BUF_NUM];
	u32 msg_enable;
	क्रमागत tc35815_chiptype chiptype;
पूर्ण;

अटल अंतरभूत dma_addr_t fd_virt_to_bus(काष्ठा tc35815_local *lp, व्योम *virt)
अणु
	वापस lp->fd_buf_dma + ((u8 *)virt - (u8 *)lp->fd_buf);
पूर्ण
#अगर_घोषित DEBUG
अटल अंतरभूत व्योम *fd_bus_to_virt(काष्ठा tc35815_local *lp, dma_addr_t bus)
अणु
	वापस (व्योम *)((u8 *)lp->fd_buf + (bus - lp->fd_buf_dma));
पूर्ण
#पूर्ण_अगर
अटल काष्ठा sk_buff *alloc_rxbuf_skb(काष्ठा net_device *dev,
				       काष्ठा pci_dev *hwdev,
				       dma_addr_t *dma_handle)
अणु
	काष्ठा sk_buff *skb;
	skb = netdev_alloc_skb(dev, RX_BUF_SIZE);
	अगर (!skb)
		वापस शून्य;
	*dma_handle = dma_map_single(&hwdev->dev, skb->data, RX_BUF_SIZE,
				     DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&hwdev->dev, *dma_handle)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण
	skb_reserve(skb, 2);	/* make IP header 4byte aligned */
	वापस skb;
पूर्ण

अटल व्योम मुक्त_rxbuf_skb(काष्ठा pci_dev *hwdev, काष्ठा sk_buff *skb, dma_addr_t dma_handle)
अणु
	dma_unmap_single(&hwdev->dev, dma_handle, RX_BUF_SIZE,
			 DMA_FROM_DEVICE);
	dev_kमुक्त_skb_any(skb);
पूर्ण

/* Index to functions, as function prototypes. */

अटल पूर्णांक	tc35815_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t	tc35815_send_packet(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev);
अटल irqवापस_t	tc35815_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक	tc35815_rx(काष्ठा net_device *dev, पूर्णांक limit);
अटल पूर्णांक	tc35815_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
अटल व्योम	tc35815_txकरोne(काष्ठा net_device *dev);
अटल पूर्णांक	tc35815_बंद(काष्ठा net_device *dev);
अटल काष्ठा	net_device_stats *tc35815_get_stats(काष्ठा net_device *dev);
अटल व्योम	tc35815_set_multicast_list(काष्ठा net_device *dev);
अटल व्योम	tc35815_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम	tc35815_poll_controller(काष्ठा net_device *dev);
#पूर्ण_अगर
अटल स्थिर काष्ठा ethtool_ops tc35815_ethtool_ops;

/* Example routines you must ग_लिखो ;->. */
अटल व्योम	tc35815_chip_reset(काष्ठा net_device *dev);
अटल व्योम	tc35815_chip_init(काष्ठा net_device *dev);

#अगर_घोषित DEBUG
अटल व्योम	panic_queues(काष्ठा net_device *dev);
#पूर्ण_अगर

अटल व्योम tc35815_restart_work(काष्ठा work_काष्ठा *work);

अटल पूर्णांक tc_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा net_device *dev = bus->priv;
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;

	tc_ग_लिखोl(MD_CA_Busy | (mii_id << 5) | (regnum & 0x1f), &tr->MD_CA);
	udelay(12); /* it takes 32 x 400ns at least */
	जबतक (tc_पढ़ोl(&tr->MD_CA) & MD_CA_Busy) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -EIO;
		cpu_relax();
	पूर्ण
	वापस tc_पढ़ोl(&tr->MD_Data) & 0xffff;
पूर्ण

अटल पूर्णांक tc_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum, u16 val)
अणु
	काष्ठा net_device *dev = bus->priv;
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;

	tc_ग_लिखोl(val, &tr->MD_Data);
	tc_ग_लिखोl(MD_CA_Busy | MD_CA_Wr | (mii_id << 5) | (regnum & 0x1f),
		  &tr->MD_CA);
	udelay(12); /* it takes 32 x 400ns at least */
	जबतक (tc_पढ़ोl(&tr->MD_CA) & MD_CA_Busy) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -EIO;
		cpu_relax();
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tc_handle_link_change(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	अचिन्हित दीर्घ flags;
	पूर्णांक status_change = 0;

	spin_lock_irqsave(&lp->lock, flags);
	अगर (phydev->link &&
	    (lp->speed != phydev->speed || lp->duplex != phydev->duplex)) अणु
		काष्ठा tc35815_regs __iomem *tr =
			(काष्ठा tc35815_regs __iomem *)dev->base_addr;
		u32 reg;

		reg = tc_पढ़ोl(&tr->MAC_Ctl);
		reg |= MAC_HaltReq;
		tc_ग_लिखोl(reg, &tr->MAC_Ctl);
		अगर (phydev->duplex == DUPLEX_FULL)
			reg |= MAC_FullDup;
		अन्यथा
			reg &= ~MAC_FullDup;
		tc_ग_लिखोl(reg, &tr->MAC_Ctl);
		reg &= ~MAC_HaltReq;
		tc_ग_लिखोl(reg, &tr->MAC_Ctl);

		/*
		 * TX4939 PCFG.SPEEDn bit will be changed on
		 * NETDEV_CHANGE event.
		 */
		/*
		 * WORKAROUND: enable LostCrS only अगर half duplex
		 * operation.
		 * (TX4939 करोes not have EnLCarr)
		 */
		अगर (phydev->duplex == DUPLEX_HALF &&
		    lp->chiptype != TC35815_TX4939)
			tc_ग_लिखोl(tc_पढ़ोl(&tr->Tx_Ctl) | Tx_EnLCarr,
				  &tr->Tx_Ctl);

		lp->speed = phydev->speed;
		lp->duplex = phydev->duplex;
		status_change = 1;
	पूर्ण

	अगर (phydev->link != lp->link) अणु
		अगर (phydev->link) अणु
			/* delayed promiscuous enabling */
			अगर (dev->flags & IFF_PROMISC)
				tc35815_set_multicast_list(dev);
		पूर्ण अन्यथा अणु
			lp->speed = 0;
			lp->duplex = -1;
		पूर्ण
		lp->link = phydev->link;

		status_change = 1;
	पूर्ण
	spin_unlock_irqrestore(&lp->lock, flags);

	अगर (status_change && netअगर_msg_link(lp)) अणु
		phy_prपूर्णांक_status(phydev);
		pr_debug("%s: MII BMCR %04x BMSR %04x LPA %04x\n",
			 dev->name,
			 phy_पढ़ो(phydev, MII_BMCR),
			 phy_पढ़ो(phydev, MII_BMSR),
			 phy_पढ़ो(phydev, MII_LPA));
	पूर्ण
पूर्ण

अटल पूर्णांक tc_mii_probe(काष्ठा net_device *dev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	काष्ठा phy_device *phydev;

	phydev = phy_find_first(lp->mii_bus);
	अगर (!phydev) अणु
		prपूर्णांकk(KERN_ERR "%s: no PHY found\n", dev->name);
		वापस -ENODEV;
	पूर्ण

	/* attach the mac to the phy */
	phydev = phy_connect(dev, phydev_name(phydev),
			     &tc_handle_link_change,
			     lp->chiptype == TC35815_TX4939 ? PHY_INTERFACE_MODE_RMII : PHY_INTERFACE_MODE_MII);
	अगर (IS_ERR(phydev)) अणु
		prपूर्णांकk(KERN_ERR "%s: Could not attach to PHY\n", dev->name);
		वापस PTR_ERR(phydev);
	पूर्ण

	phy_attached_info(phydev);

	/* mask with MAC supported features */
	phy_set_max_speed(phydev, SPEED_100);
	अगर (options.speed == 10) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT, mask);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT, mask);
	पूर्ण अन्यथा अगर (options.speed == 100) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT, mask);
		linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT, mask);
	पूर्ण
	अगर (options.duplex == 1) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT, mask);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT, mask);
	पूर्ण अन्यथा अगर (options.duplex == 2) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT, mask);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT, mask);
	पूर्ण
	linkmode_andnot(phydev->supported, phydev->supported, mask);
	linkmode_copy(phydev->advertising, phydev->supported);

	lp->link = 0;
	lp->speed = 0;
	lp->duplex = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक tc_mii_init(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	पूर्णांक err;

	lp->mii_bus = mdiobus_alloc();
	अगर (lp->mii_bus == शून्य) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	lp->mii_bus->name = "tc35815_mii_bus";
	lp->mii_bus->पढ़ो = tc_mdio_पढ़ो;
	lp->mii_bus->ग_लिखो = tc_mdio_ग_लिखो;
	snम_लिखो(lp->mii_bus->id, MII_BUS_ID_SIZE, "%x",
		 (lp->pci_dev->bus->number << 8) | lp->pci_dev->devfn);
	lp->mii_bus->priv = dev;
	lp->mii_bus->parent = &lp->pci_dev->dev;
	err = mdiobus_रेजिस्टर(lp->mii_bus);
	अगर (err)
		जाओ err_out_मुक्त_mii_bus;
	err = tc_mii_probe(dev);
	अगर (err)
		जाओ err_out_unरेजिस्टर_bus;
	वापस 0;

err_out_unरेजिस्टर_bus:
	mdiobus_unरेजिस्टर(lp->mii_bus);
err_out_मुक्त_mii_bus:
	mdiobus_मुक्त(lp->mii_bus);
err_out:
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_CPU_TX49XX
/*
 * Find a platक्रमm_device providing a MAC address.  The platक्रमm code
 * should provide a "tc35815-mac" device with a MAC address in its
 * platक्रमm_data.
 */
अटल पूर्णांक tc35815_mac_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा platक्रमm_device *plat_dev = to_platक्रमm_device(dev);
	स्थिर काष्ठा pci_dev *pci_dev = data;
	अचिन्हित पूर्णांक id = pci_dev->irq;
	वापस !म_भेद(plat_dev->name, "tc35815-mac") && plat_dev->id == id;
पूर्ण

अटल पूर्णांक tc35815_पढ़ो_plat_dev_addr(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	काष्ठा device *pd = bus_find_device(&platक्रमm_bus_type, शून्य,
					    lp->pci_dev, tc35815_mac_match);
	अगर (pd) अणु
		अगर (pd->platक्रमm_data)
			स_नकल(dev->dev_addr, pd->platक्रमm_data, ETH_ALEN);
		put_device(pd);
		वापस is_valid_ether_addr(dev->dev_addr) ? 0 : -ENODEV;
	पूर्ण
	वापस -ENODEV;
पूर्ण
#अन्यथा
अटल पूर्णांक tc35815_पढ़ो_plat_dev_addr(काष्ठा net_device *dev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tc35815_init_dev_addr(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	पूर्णांक i;

	जबतक (tc_पढ़ोl(&tr->PROM_Ctl) & PROM_Busy)
		;
	क्रम (i = 0; i < 6; i += 2) अणु
		अचिन्हित लघु data;
		tc_ग_लिखोl(PROM_Busy | PROM_Read | (i / 2 + 2), &tr->PROM_Ctl);
		जबतक (tc_पढ़ोl(&tr->PROM_Ctl) & PROM_Busy)
			;
		data = tc_पढ़ोl(&tr->PROM_Data);
		dev->dev_addr[i] = data & 0xff;
		dev->dev_addr[i+1] = data >> 8;
	पूर्ण
	अगर (!is_valid_ether_addr(dev->dev_addr))
		वापस tc35815_पढ़ो_plat_dev_addr(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops tc35815_netdev_ops = अणु
	.nकरो_खोलो		= tc35815_खोलो,
	.nकरो_stop		= tc35815_बंद,
	.nकरो_start_xmit		= tc35815_send_packet,
	.nकरो_get_stats		= tc35815_get_stats,
	.nकरो_set_rx_mode	= tc35815_set_multicast_list,
	.nकरो_tx_समयout		= tc35815_tx_समयout,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= tc35815_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक tc35815_init_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	व्योम __iomem *ioaddr = शून्य;
	काष्ठा net_device *dev;
	काष्ठा tc35815_local *lp;
	पूर्णांक rc;

	अटल पूर्णांक prपूर्णांकed_version;
	अगर (!prपूर्णांकed_version++) अणु
		prपूर्णांकk(version);
		dev_prपूर्णांकk(KERN_DEBUG, &pdev->dev,
			   "speed:%d duplex:%d\n",
			   options.speed, options.duplex);
	पूर्ण

	अगर (!pdev->irq) अणु
		dev_warn(&pdev->dev, "no IRQ assigned.\n");
		वापस -ENODEV;
	पूर्ण

	/* dev zeroed in alloc_etherdev */
	dev = alloc_etherdev(माप(*lp));
	अगर (dev == शून्य)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);
	lp = netdev_priv(dev);
	lp->dev = dev;

	/* enable device (incl. PCI PM wakeup), and bus-mastering */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		जाओ err_out;
	rc = pcim_iomap_regions(pdev, 1 << 1, MODNAME);
	अगर (rc)
		जाओ err_out;
	pci_set_master(pdev);
	ioaddr = pcim_iomap_table(pdev)[1];

	/* Initialize the device काष्ठाure. */
	dev->netdev_ops = &tc35815_netdev_ops;
	dev->ethtool_ops = &tc35815_ethtool_ops;
	dev->watchकरोg_समयo = TC35815_TX_TIMEOUT;
	netअगर_napi_add(dev, &lp->napi, tc35815_poll, NAPI_WEIGHT);

	dev->irq = pdev->irq;
	dev->base_addr = (अचिन्हित दीर्घ)ioaddr;

	INIT_WORK(&lp->restart_work, tc35815_restart_work);
	spin_lock_init(&lp->lock);
	spin_lock_init(&lp->rx_lock);
	lp->pci_dev = pdev;
	lp->chiptype = ent->driver_data;

	lp->msg_enable = NETIF_MSG_TX_ERR | NETIF_MSG_HW | NETIF_MSG_DRV | NETIF_MSG_LINK;
	pci_set_drvdata(pdev, dev);

	/* Soft reset the chip. */
	tc35815_chip_reset(dev);

	/* Retrieve the ethernet address. */
	अगर (tc35815_init_dev_addr(dev)) अणु
		dev_warn(&pdev->dev, "not valid ether addr\n");
		eth_hw_addr_अक्रमom(dev);
	पूर्ण

	rc = रेजिस्टर_netdev(dev);
	अगर (rc)
		जाओ err_out;

	prपूर्णांकk(KERN_INFO "%s: %s at 0x%lx, %pM, IRQ %d\n",
		dev->name,
		chip_info[ent->driver_data].name,
		dev->base_addr,
		dev->dev_addr,
		dev->irq);

	rc = tc_mii_init(dev);
	अगर (rc)
		जाओ err_out_unरेजिस्टर;

	वापस 0;

err_out_unरेजिस्टर:
	unरेजिस्टर_netdev(dev);
err_out:
	मुक्त_netdev(dev);
	वापस rc;
पूर्ण


अटल व्योम tc35815_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा tc35815_local *lp = netdev_priv(dev);

	phy_disconnect(dev->phydev);
	mdiobus_unरेजिस्टर(lp->mii_bus);
	mdiobus_मुक्त(lp->mii_bus);
	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
पूर्ण

अटल पूर्णांक
tc35815_init_queues(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	पूर्णांक i;
	अचिन्हित दीर्घ fd_addr;

	अगर (!lp->fd_buf) अणु
		BUG_ON(माप(काष्ठा FDesc) +
		       माप(काष्ठा BDesc) * RX_BUF_NUM +
		       माप(काष्ठा FDesc) * RX_FD_NUM +
		       माप(काष्ठा TxFD) * TX_FD_NUM >
		       PAGE_SIZE * FD_PAGE_NUM);

		lp->fd_buf = dma_alloc_coherent(&lp->pci_dev->dev,
						PAGE_SIZE * FD_PAGE_NUM,
						&lp->fd_buf_dma, GFP_ATOMIC);
		अगर (!lp->fd_buf)
			वापस -ENOMEM;
		क्रम (i = 0; i < RX_BUF_NUM; i++) अणु
			lp->rx_skbs[i].skb =
				alloc_rxbuf_skb(dev, lp->pci_dev,
						&lp->rx_skbs[i].skb_dma);
			अगर (!lp->rx_skbs[i].skb) अणु
				जबतक (--i >= 0) अणु
					मुक्त_rxbuf_skb(lp->pci_dev,
						       lp->rx_skbs[i].skb,
						       lp->rx_skbs[i].skb_dma);
					lp->rx_skbs[i].skb = शून्य;
				पूर्ण
				dma_मुक्त_coherent(&lp->pci_dev->dev,
						  PAGE_SIZE * FD_PAGE_NUM,
						  lp->fd_buf, lp->fd_buf_dma);
				lp->fd_buf = शून्य;
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		prपूर्णांकk(KERN_DEBUG "%s: FD buf %p DataBuf",
		       dev->name, lp->fd_buf);
		prपूर्णांकk("\n");
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < FD_PAGE_NUM; i++)
			clear_page((व्योम *)((अचिन्हित दीर्घ)lp->fd_buf +
					    i * PAGE_SIZE));
	पूर्ण
	fd_addr = (अचिन्हित दीर्घ)lp->fd_buf;

	/* Free Descriptors (क्रम Receive) */
	lp->rfd_base = (काष्ठा RxFD *)fd_addr;
	fd_addr += माप(काष्ठा RxFD) * RX_FD_NUM;
	क्रम (i = 0; i < RX_FD_NUM; i++)
		lp->rfd_base[i].fd.FDCtl = cpu_to_le32(FD_CownsFD);
	lp->rfd_cur = lp->rfd_base;
	lp->rfd_limit = (काष्ठा RxFD *)fd_addr - (RX_FD_RESERVE + 1);

	/* Transmit Descriptors */
	lp->tfd_base = (काष्ठा TxFD *)fd_addr;
	fd_addr += माप(काष्ठा TxFD) * TX_FD_NUM;
	क्रम (i = 0; i < TX_FD_NUM; i++) अणु
		lp->tfd_base[i].fd.FDNext = cpu_to_le32(fd_virt_to_bus(lp, &lp->tfd_base[i+1]));
		lp->tfd_base[i].fd.FDSystem = cpu_to_le32(0xffffffff);
		lp->tfd_base[i].fd.FDCtl = cpu_to_le32(0);
	पूर्ण
	lp->tfd_base[TX_FD_NUM-1].fd.FDNext = cpu_to_le32(fd_virt_to_bus(lp, &lp->tfd_base[0]));
	lp->tfd_start = 0;
	lp->tfd_end = 0;

	/* Buffer List (क्रम Receive) */
	lp->fbl_ptr = (काष्ठा FrFD *)fd_addr;
	lp->fbl_ptr->fd.FDNext = cpu_to_le32(fd_virt_to_bus(lp, lp->fbl_ptr));
	lp->fbl_ptr->fd.FDCtl = cpu_to_le32(RX_BUF_NUM | FD_CownsFD);
	/*
	 * move all allocated skbs to head of rx_skbs[] array.
	 * fbl_count mighe not be RX_BUF_NUM अगर alloc_rxbuf_skb() in
	 * tc35815_rx() had failed.
	 */
	lp->fbl_count = 0;
	क्रम (i = 0; i < RX_BUF_NUM; i++) अणु
		अगर (lp->rx_skbs[i].skb) अणु
			अगर (i != lp->fbl_count) अणु
				lp->rx_skbs[lp->fbl_count].skb =
					lp->rx_skbs[i].skb;
				lp->rx_skbs[lp->fbl_count].skb_dma =
					lp->rx_skbs[i].skb_dma;
			पूर्ण
			lp->fbl_count++;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < RX_BUF_NUM; i++) अणु
		अगर (i >= lp->fbl_count) अणु
			lp->fbl_ptr->bd[i].BuffData = 0;
			lp->fbl_ptr->bd[i].BDCtl = 0;
			जारी;
		पूर्ण
		lp->fbl_ptr->bd[i].BuffData =
			cpu_to_le32(lp->rx_skbs[i].skb_dma);
		/* BDID is index of FrFD.bd[] */
		lp->fbl_ptr->bd[i].BDCtl =
			cpu_to_le32(BD_CownsBD | (i << BD_RxBDID_SHIFT) |
				    RX_BUF_SIZE);
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: TxFD %p RxFD %p FrFD %p\n",
	       dev->name, lp->tfd_base, lp->rfd_base, lp->fbl_ptr);
	वापस 0;
पूर्ण

अटल व्योम
tc35815_clear_queues(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < TX_FD_NUM; i++) अणु
		u32 fdप्रणाली = le32_to_cpu(lp->tfd_base[i].fd.FDSystem);
		काष्ठा sk_buff *skb =
			fdप्रणाली != 0xffffffff ?
			lp->tx_skbs[fdप्रणाली].skb : शून्य;
#अगर_घोषित DEBUG
		अगर (lp->tx_skbs[i].skb != skb) अणु
			prपूर्णांकk("%s: tx_skbs mismatch(%d).\n", dev->name, i);
			panic_queues(dev);
		पूर्ण
#अन्यथा
		BUG_ON(lp->tx_skbs[i].skb != skb);
#पूर्ण_अगर
		अगर (skb) अणु
			dma_unmap_single(&lp->pci_dev->dev,
					 lp->tx_skbs[i].skb_dma, skb->len,
					 DMA_TO_DEVICE);
			lp->tx_skbs[i].skb = शून्य;
			lp->tx_skbs[i].skb_dma = 0;
			dev_kमुक्त_skb_any(skb);
		पूर्ण
		lp->tfd_base[i].fd.FDSystem = cpu_to_le32(0xffffffff);
	पूर्ण

	tc35815_init_queues(dev);
पूर्ण

अटल व्योम
tc35815_मुक्त_queues(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	पूर्णांक i;

	अगर (lp->tfd_base) अणु
		क्रम (i = 0; i < TX_FD_NUM; i++) अणु
			u32 fdप्रणाली = le32_to_cpu(lp->tfd_base[i].fd.FDSystem);
			काष्ठा sk_buff *skb =
				fdप्रणाली != 0xffffffff ?
				lp->tx_skbs[fdप्रणाली].skb : शून्य;
#अगर_घोषित DEBUG
			अगर (lp->tx_skbs[i].skb != skb) अणु
				prपूर्णांकk("%s: tx_skbs mismatch(%d).\n", dev->name, i);
				panic_queues(dev);
			पूर्ण
#अन्यथा
			BUG_ON(lp->tx_skbs[i].skb != skb);
#पूर्ण_अगर
			अगर (skb) अणु
				dma_unmap_single(&lp->pci_dev->dev,
						 lp->tx_skbs[i].skb_dma,
						 skb->len, DMA_TO_DEVICE);
				dev_kमुक्त_skb(skb);
				lp->tx_skbs[i].skb = शून्य;
				lp->tx_skbs[i].skb_dma = 0;
			पूर्ण
			lp->tfd_base[i].fd.FDSystem = cpu_to_le32(0xffffffff);
		पूर्ण
	पूर्ण

	lp->rfd_base = शून्य;
	lp->rfd_limit = शून्य;
	lp->rfd_cur = शून्य;
	lp->fbl_ptr = शून्य;

	क्रम (i = 0; i < RX_BUF_NUM; i++) अणु
		अगर (lp->rx_skbs[i].skb) अणु
			मुक्त_rxbuf_skb(lp->pci_dev, lp->rx_skbs[i].skb,
				       lp->rx_skbs[i].skb_dma);
			lp->rx_skbs[i].skb = शून्य;
		पूर्ण
	पूर्ण
	अगर (lp->fd_buf) अणु
		dma_मुक्त_coherent(&lp->pci_dev->dev, PAGE_SIZE * FD_PAGE_NUM,
				  lp->fd_buf, lp->fd_buf_dma);
		lp->fd_buf = शून्य;
	पूर्ण
पूर्ण

अटल व्योम
dump_txfd(काष्ठा TxFD *fd)
अणु
	prपूर्णांकk("TxFD(%p): %08x %08x %08x %08x\n", fd,
	       le32_to_cpu(fd->fd.FDNext),
	       le32_to_cpu(fd->fd.FDSystem),
	       le32_to_cpu(fd->fd.FDStat),
	       le32_to_cpu(fd->fd.FDCtl));
	prपूर्णांकk("BD: ");
	prपूर्णांकk(" %08x %08x",
	       le32_to_cpu(fd->bd.BuffData),
	       le32_to_cpu(fd->bd.BDCtl));
	prपूर्णांकk("\n");
पूर्ण

अटल पूर्णांक
dump_rxfd(काष्ठा RxFD *fd)
अणु
	पूर्णांक i, bd_count = (le32_to_cpu(fd->fd.FDCtl) & FD_BDCnt_MASK) >> FD_BDCnt_SHIFT;
	अगर (bd_count > 8)
		bd_count = 8;
	prपूर्णांकk("RxFD(%p): %08x %08x %08x %08x\n", fd,
	       le32_to_cpu(fd->fd.FDNext),
	       le32_to_cpu(fd->fd.FDSystem),
	       le32_to_cpu(fd->fd.FDStat),
	       le32_to_cpu(fd->fd.FDCtl));
	अगर (le32_to_cpu(fd->fd.FDCtl) & FD_CownsFD)
		वापस 0;
	prपूर्णांकk("BD: ");
	क्रम (i = 0; i < bd_count; i++)
		prपूर्णांकk(" %08x %08x",
		       le32_to_cpu(fd->bd[i].BuffData),
		       le32_to_cpu(fd->bd[i].BDCtl));
	prपूर्णांकk("\n");
	वापस bd_count;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम
dump_frfd(काष्ठा FrFD *fd)
अणु
	पूर्णांक i;
	prपूर्णांकk("FrFD(%p): %08x %08x %08x %08x\n", fd,
	       le32_to_cpu(fd->fd.FDNext),
	       le32_to_cpu(fd->fd.FDSystem),
	       le32_to_cpu(fd->fd.FDStat),
	       le32_to_cpu(fd->fd.FDCtl));
	prपूर्णांकk("BD: ");
	क्रम (i = 0; i < RX_BUF_NUM; i++)
		prपूर्णांकk(" %08x %08x",
		       le32_to_cpu(fd->bd[i].BuffData),
		       le32_to_cpu(fd->bd[i].BDCtl));
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम
panic_queues(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	पूर्णांक i;

	prपूर्णांकk("TxFD base %p, start %u, end %u\n",
	       lp->tfd_base, lp->tfd_start, lp->tfd_end);
	prपूर्णांकk("RxFD base %p limit %p cur %p\n",
	       lp->rfd_base, lp->rfd_limit, lp->rfd_cur);
	prपूर्णांकk("FrFD %p\n", lp->fbl_ptr);
	क्रम (i = 0; i < TX_FD_NUM; i++)
		dump_txfd(&lp->tfd_base[i]);
	क्रम (i = 0; i < RX_FD_NUM; i++) अणु
		पूर्णांक bd_count = dump_rxfd(&lp->rfd_base[i]);
		i += (bd_count + 1) / 2;	/* skip BDs */
	पूर्ण
	dump_frfd(lp->fbl_ptr);
	panic("%s: Illegal queue state.", dev->name);
पूर्ण
#पूर्ण_अगर

अटल व्योम prपूर्णांक_eth(स्थिर u8 *add)
अणु
	prपूर्णांकk(KERN_DEBUG "print_eth(%p)\n", add);
	prपूर्णांकk(KERN_DEBUG " %pM => %pM : %02x%02x\n",
		add + 6, add, add[12], add[13]);
पूर्ण

अटल पूर्णांक tc35815_tx_full(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	वापस (lp->tfd_start + 1) % TX_FD_NUM == lp->tfd_end;
पूर्ण

अटल व्योम tc35815_restart(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	पूर्णांक ret;

	अगर (dev->phydev) अणु
		ret = phy_init_hw(dev->phydev);
		अगर (ret)
			prपूर्णांकk(KERN_ERR "%s: PHY init failed.\n", dev->name);
	पूर्ण

	spin_lock_bh(&lp->rx_lock);
	spin_lock_irq(&lp->lock);
	tc35815_chip_reset(dev);
	tc35815_clear_queues(dev);
	tc35815_chip_init(dev);
	/* Reconfigure CAM again since tc35815_chip_init() initialize it. */
	tc35815_set_multicast_list(dev);
	spin_unlock_irq(&lp->lock);
	spin_unlock_bh(&lp->rx_lock);

	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम tc35815_restart_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tc35815_local *lp =
		container_of(work, काष्ठा tc35815_local, restart_work);
	काष्ठा net_device *dev = lp->dev;

	tc35815_restart(dev);
पूर्ण

अटल व्योम tc35815_schedule_restart(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	अचिन्हित दीर्घ flags;

	/* disable पूर्णांकerrupts */
	spin_lock_irqsave(&lp->lock, flags);
	tc_ग_लिखोl(0, &tr->Int_En);
	tc_ग_लिखोl(tc_पढ़ोl(&tr->DMA_Ctl) | DMA_IntMask, &tr->DMA_Ctl);
	schedule_work(&lp->restart_work);
	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

अटल व्योम tc35815_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;

	prपूर्णांकk(KERN_WARNING "%s: transmit timed out, status %#x\n",
	       dev->name, tc_पढ़ोl(&tr->Tx_Stat));

	/* Try to restart the adaptor. */
	tc35815_schedule_restart(dev);
	dev->stats.tx_errors++;
पूर्ण

/*
 * Open/initialize the controller. This is called (in the current kernel)
 * someसमय after booting when the 'ifconfig' program is run.
 *
 * This routine should set everything up anew at each खोलो, even
 * रेजिस्टरs that "should" only need to be set once at boot, so that
 * there is non-reboot way to recover अगर something goes wrong.
 */
अटल पूर्णांक
tc35815_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);

	/*
	 * This is used अगर the पूर्णांकerrupt line can turned off (shared).
	 * See 3c503.c क्रम an example of selecting the IRQ at config-समय.
	 */
	अगर (request_irq(dev->irq, tc35815_पूर्णांकerrupt, IRQF_SHARED,
			dev->name, dev))
		वापस -EAGAIN;

	tc35815_chip_reset(dev);

	अगर (tc35815_init_queues(dev) != 0) अणु
		मुक्त_irq(dev->irq, dev);
		वापस -EAGAIN;
	पूर्ण

	napi_enable(&lp->napi);

	/* Reset the hardware here. Don't क्रमget to set the station address. */
	spin_lock_irq(&lp->lock);
	tc35815_chip_init(dev);
	spin_unlock_irq(&lp->lock);

	netअगर_carrier_off(dev);
	/* schedule a link state check */
	phy_start(dev->phydev);

	/* We are now पढ़ोy to accept transmit requeusts from
	 * the queueing layer of the networking.
	 */
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

/* This will only be invoked अगर your driver is _not_ in XOFF state.
 * What this means is that you need not check it, and that this
 * invariant will hold अगर you make sure that the netअगर_*_queue()
 * calls are करोne at the proper बार.
 */
अटल netdev_tx_t
tc35815_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	काष्ठा TxFD *txfd;
	अचिन्हित दीर्घ flags;

	/* If some error occurs जबतक trying to transmit this
	 * packet, you should वापस '1' from this function.
	 * In such a हाल you _may not_ करो anything to the
	 * SKB, it is still owned by the network queueing
	 * layer when an error is वापसed.  This means you
	 * may not modअगरy any SKB fields, you may not मुक्त
	 * the SKB, etc.
	 */

	/* This is the most common हाल क्रम modern hardware.
	 * The spinlock protects this code from the TX complete
	 * hardware पूर्णांकerrupt handler.  Queue flow control is
	 * thus managed under this lock as well.
	 */
	spin_lock_irqsave(&lp->lock, flags);

	/* failsafe... (handle txकरोne now अगर half of FDs are used) */
	अगर ((lp->tfd_start + TX_FD_NUM - lp->tfd_end) % TX_FD_NUM >
	    TX_FD_NUM / 2)
		tc35815_txकरोne(dev);

	अगर (netअगर_msg_pktdata(lp))
		prपूर्णांक_eth(skb->data);
#अगर_घोषित DEBUG
	अगर (lp->tx_skbs[lp->tfd_start].skb) अणु
		prपूर्णांकk("%s: tx_skbs conflict.\n", dev->name);
		panic_queues(dev);
	पूर्ण
#अन्यथा
	BUG_ON(lp->tx_skbs[lp->tfd_start].skb);
#पूर्ण_अगर
	lp->tx_skbs[lp->tfd_start].skb = skb;
	lp->tx_skbs[lp->tfd_start].skb_dma = dma_map_single(&lp->pci_dev->dev,
							    skb->data,
							    skb->len,
							    DMA_TO_DEVICE);

	/*add to ring */
	txfd = &lp->tfd_base[lp->tfd_start];
	txfd->bd.BuffData = cpu_to_le32(lp->tx_skbs[lp->tfd_start].skb_dma);
	txfd->bd.BDCtl = cpu_to_le32(skb->len);
	txfd->fd.FDSystem = cpu_to_le32(lp->tfd_start);
	txfd->fd.FDCtl = cpu_to_le32(FD_CownsFD | (1 << FD_BDCnt_SHIFT));

	अगर (lp->tfd_start == lp->tfd_end) अणु
		काष्ठा tc35815_regs __iomem *tr =
			(काष्ठा tc35815_regs __iomem *)dev->base_addr;
		/* Start DMA Transmitter. */
		txfd->fd.FDNext |= cpu_to_le32(FD_Next_EOL);
		txfd->fd.FDCtl |= cpu_to_le32(FD_FrmOpt_IntTx);
		अगर (netअगर_msg_tx_queued(lp)) अणु
			prपूर्णांकk("%s: starting TxFD.\n", dev->name);
			dump_txfd(txfd);
		पूर्ण
		tc_ग_लिखोl(fd_virt_to_bus(lp, txfd), &tr->TxFrmPtr);
	पूर्ण अन्यथा अणु
		txfd->fd.FDNext &= cpu_to_le32(~FD_Next_EOL);
		अगर (netअगर_msg_tx_queued(lp)) अणु
			prपूर्णांकk("%s: queueing TxFD.\n", dev->name);
			dump_txfd(txfd);
		पूर्ण
	पूर्ण
	lp->tfd_start = (lp->tfd_start + 1) % TX_FD_NUM;

	/* If we just used up the very last entry in the
	 * TX ring on this device, tell the queueing
	 * layer to send no more.
	 */
	अगर (tc35815_tx_full(dev)) अणु
		अगर (netअगर_msg_tx_queued(lp))
			prपूर्णांकk(KERN_WARNING "%s: TxFD Exhausted.\n", dev->name);
		netअगर_stop_queue(dev);
	पूर्ण

	/* When the TX completion hw पूर्णांकerrupt arrives, this
	 * is when the transmit statistics are updated.
	 */

	spin_unlock_irqrestore(&lp->lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

#घोषणा FATAL_ERROR_INT \
	(Int_IntPCI | Int_DmParErr | Int_IntNRAbt)
अटल व्योम tc35815_fatal_error_पूर्णांकerrupt(काष्ठा net_device *dev, u32 status)
अणु
	अटल पूर्णांक count;
	prपूर्णांकk(KERN_WARNING "%s: Fatal Error Interrupt (%#x):",
	       dev->name, status);
	अगर (status & Int_IntPCI)
		prपूर्णांकk(" IntPCI");
	अगर (status & Int_DmParErr)
		prपूर्णांकk(" DmParErr");
	अगर (status & Int_IntNRAbt)
		prपूर्णांकk(" IntNRAbt");
	prपूर्णांकk("\n");
	अगर (count++ > 100)
		panic("%s: Too many fatal errors.", dev->name);
	prपूर्णांकk(KERN_WARNING "%s: Resetting ...\n", dev->name);
	/* Try to restart the adaptor. */
	tc35815_schedule_restart(dev);
पूर्ण

अटल पूर्णांक tc35815_करो_पूर्णांकerrupt(काष्ठा net_device *dev, u32 status, पूर्णांक limit)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	पूर्णांक ret = -1;

	/* Fatal errors... */
	अगर (status & FATAL_ERROR_INT) अणु
		tc35815_fatal_error_पूर्णांकerrupt(dev, status);
		वापस 0;
	पूर्ण
	/* recoverable errors */
	अगर (status & Int_IntFDAEx) अणु
		अगर (netअगर_msg_rx_err(lp))
			dev_warn(&dev->dev,
				 "Free Descriptor Area Exhausted (%#x).\n",
				 status);
		dev->stats.rx_dropped++;
		ret = 0;
	पूर्ण
	अगर (status & Int_IntBLEx) अणु
		अगर (netअगर_msg_rx_err(lp))
			dev_warn(&dev->dev,
				 "Buffer List Exhausted (%#x).\n",
				 status);
		dev->stats.rx_dropped++;
		ret = 0;
	पूर्ण
	अगर (status & Int_IntExBD) अणु
		अगर (netअगर_msg_rx_err(lp))
			dev_warn(&dev->dev,
				 "Excessive Buffer Descriptors (%#x).\n",
				 status);
		dev->stats.rx_length_errors++;
		ret = 0;
	पूर्ण

	/* normal notअगरication */
	अगर (status & Int_IntMacRx) अणु
		/* Got a packet(s). */
		ret = tc35815_rx(dev, limit);
		lp->lstats.rx_पूर्णांकs++;
	पूर्ण
	अगर (status & Int_IntMacTx) अणु
		/* Transmit complete. */
		lp->lstats.tx_पूर्णांकs++;
		spin_lock_irq(&lp->lock);
		tc35815_txकरोne(dev);
		spin_unlock_irq(&lp->lock);
		अगर (ret < 0)
			ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * The typical workload of the driver:
 * Handle the network पूर्णांकerface पूर्णांकerrupts.
 */
अटल irqवापस_t tc35815_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	u32 dmactl = tc_पढ़ोl(&tr->DMA_Ctl);

	अगर (!(dmactl & DMA_IntMask)) अणु
		/* disable पूर्णांकerrupts */
		tc_ग_लिखोl(dmactl | DMA_IntMask, &tr->DMA_Ctl);
		अगर (napi_schedule_prep(&lp->napi))
			__napi_schedule(&lp->napi);
		अन्यथा अणु
			prपूर्णांकk(KERN_ERR "%s: interrupt taken in poll\n",
			       dev->name);
			BUG();
		पूर्ण
		(व्योम)tc_पढ़ोl(&tr->Int_Src);	/* flush */
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम tc35815_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	tc35815_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/* We have a good packet(s), get it/them out of the buffers. */
अटल पूर्णांक
tc35815_rx(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक fdctl;
	पूर्णांक i;
	पूर्णांक received = 0;

	जबतक (!((fdctl = le32_to_cpu(lp->rfd_cur->fd.FDCtl)) & FD_CownsFD)) अणु
		पूर्णांक status = le32_to_cpu(lp->rfd_cur->fd.FDStat);
		पूर्णांक pkt_len = fdctl & FD_FDLength_MASK;
		पूर्णांक bd_count = (fdctl & FD_BDCnt_MASK) >> FD_BDCnt_SHIFT;
#अगर_घोषित DEBUG
		काष्ठा RxFD *next_rfd;
#पूर्ण_अगर
#अगर (RX_CTL_CMD & Rx_StripCRC) == 0
		pkt_len -= ETH_FCS_LEN;
#पूर्ण_अगर

		अगर (netअगर_msg_rx_status(lp))
			dump_rxfd(lp->rfd_cur);
		अगर (status & Rx_Good) अणु
			काष्ठा sk_buff *skb;
			अचिन्हित अक्षर *data;
			पूर्णांक cur_bd;

			अगर (--limit < 0)
				अवरोध;
			BUG_ON(bd_count > 1);
			cur_bd = (le32_to_cpu(lp->rfd_cur->bd[0].BDCtl)
				  & BD_RxBDID_MASK) >> BD_RxBDID_SHIFT;
#अगर_घोषित DEBUG
			अगर (cur_bd >= RX_BUF_NUM) अणु
				prपूर्णांकk("%s: invalid BDID.\n", dev->name);
				panic_queues(dev);
			पूर्ण
			BUG_ON(lp->rx_skbs[cur_bd].skb_dma !=
			       (le32_to_cpu(lp->rfd_cur->bd[0].BuffData) & ~3));
			अगर (!lp->rx_skbs[cur_bd].skb) अणु
				prपूर्णांकk("%s: NULL skb.\n", dev->name);
				panic_queues(dev);
			पूर्ण
#अन्यथा
			BUG_ON(cur_bd >= RX_BUF_NUM);
#पूर्ण_अगर
			skb = lp->rx_skbs[cur_bd].skb;
			prefetch(skb->data);
			lp->rx_skbs[cur_bd].skb = शून्य;
			dma_unmap_single(&lp->pci_dev->dev,
					 lp->rx_skbs[cur_bd].skb_dma,
					 RX_BUF_SIZE, DMA_FROM_DEVICE);
			अगर (!HAVE_DMA_RXALIGN(lp) && NET_IP_ALIGN != 0)
				स_हटाओ(skb->data, skb->data - NET_IP_ALIGN,
					pkt_len);
			data = skb_put(skb, pkt_len);
			अगर (netअगर_msg_pktdata(lp))
				prपूर्णांक_eth(data);
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_receive_skb(skb);
			received++;
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		पूर्ण अन्यथा अणु
			dev->stats.rx_errors++;
			अगर (netअगर_msg_rx_err(lp))
				dev_info(&dev->dev, "Rx error (status %x)\n",
					 status & Rx_Stat_Mask);
			/* WORKAROUND: LongErr and CRCErr means Overflow. */
			अगर ((status & Rx_LongErr) && (status & Rx_CRCErr)) अणु
				status &= ~(Rx_LongErr|Rx_CRCErr);
				status |= Rx_Over;
			पूर्ण
			अगर (status & Rx_LongErr)
				dev->stats.rx_length_errors++;
			अगर (status & Rx_Over)
				dev->stats.rx_fअगरo_errors++;
			अगर (status & Rx_CRCErr)
				dev->stats.rx_crc_errors++;
			अगर (status & Rx_Align)
				dev->stats.rx_frame_errors++;
		पूर्ण

		अगर (bd_count > 0) अणु
			/* put Free Buffer back to controller */
			पूर्णांक bdctl = le32_to_cpu(lp->rfd_cur->bd[bd_count - 1].BDCtl);
			अचिन्हित अक्षर id =
				(bdctl & BD_RxBDID_MASK) >> BD_RxBDID_SHIFT;
#अगर_घोषित DEBUG
			अगर (id >= RX_BUF_NUM) अणु
				prपूर्णांकk("%s: invalid BDID.\n", dev->name);
				panic_queues(dev);
			पूर्ण
#अन्यथा
			BUG_ON(id >= RX_BUF_NUM);
#पूर्ण_अगर
			/* मुक्त old buffers */
			lp->fbl_count--;
			जबतक (lp->fbl_count < RX_BUF_NUM)
			अणु
				अचिन्हित अक्षर curid =
					(id + 1 + lp->fbl_count) % RX_BUF_NUM;
				काष्ठा BDesc *bd = &lp->fbl_ptr->bd[curid];
#अगर_घोषित DEBUG
				bdctl = le32_to_cpu(bd->BDCtl);
				अगर (bdctl & BD_CownsBD) अणु
					prपूर्णांकk("%s: Freeing invalid BD.\n",
					       dev->name);
					panic_queues(dev);
				पूर्ण
#पूर्ण_अगर
				/* pass BD to controller */
				अगर (!lp->rx_skbs[curid].skb) अणु
					lp->rx_skbs[curid].skb =
						alloc_rxbuf_skb(dev,
								lp->pci_dev,
								&lp->rx_skbs[curid].skb_dma);
					अगर (!lp->rx_skbs[curid].skb)
						अवरोध; /* try on next reception */
					bd->BuffData = cpu_to_le32(lp->rx_skbs[curid].skb_dma);
				पूर्ण
				/* Note: BDLength was modअगरied by chip. */
				bd->BDCtl = cpu_to_le32(BD_CownsBD |
							(curid << BD_RxBDID_SHIFT) |
							RX_BUF_SIZE);
				lp->fbl_count++;
			पूर्ण
		पूर्ण

		/* put RxFD back to controller */
#अगर_घोषित DEBUG
		next_rfd = fd_bus_to_virt(lp,
					  le32_to_cpu(lp->rfd_cur->fd.FDNext));
		अगर (next_rfd < lp->rfd_base || next_rfd > lp->rfd_limit) अणु
			prपूर्णांकk("%s: RxFD FDNext invalid.\n", dev->name);
			panic_queues(dev);
		पूर्ण
#पूर्ण_अगर
		क्रम (i = 0; i < (bd_count + 1) / 2 + 1; i++) अणु
			/* pass FD to controller */
#अगर_घोषित DEBUG
			lp->rfd_cur->fd.FDNext = cpu_to_le32(0xdeaddead);
#अन्यथा
			lp->rfd_cur->fd.FDNext = cpu_to_le32(FD_Next_EOL);
#पूर्ण_अगर
			lp->rfd_cur->fd.FDCtl = cpu_to_le32(FD_CownsFD);
			lp->rfd_cur++;
		पूर्ण
		अगर (lp->rfd_cur > lp->rfd_limit)
			lp->rfd_cur = lp->rfd_base;
#अगर_घोषित DEBUG
		अगर (lp->rfd_cur != next_rfd)
			prपूर्णांकk("rfd_cur = %p, next_rfd %p\n",
			       lp->rfd_cur, next_rfd);
#पूर्ण_अगर
	पूर्ण

	वापस received;
पूर्ण

अटल पूर्णांक tc35815_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा tc35815_local *lp = container_of(napi, काष्ठा tc35815_local, napi);
	काष्ठा net_device *dev = lp->dev;
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	पूर्णांक received = 0, handled;
	u32 status;

	अगर (budget <= 0)
		वापस received;

	spin_lock(&lp->rx_lock);
	status = tc_पढ़ोl(&tr->Int_Src);
	करो अणु
		/* BLEx, FDAEx will be cleared later */
		tc_ग_लिखोl(status & ~(Int_BLEx | Int_FDAEx),
			  &tr->Int_Src);	/* ग_लिखो to clear */

		handled = tc35815_करो_पूर्णांकerrupt(dev, status, budget - received);
		अगर (status & (Int_BLEx | Int_FDAEx))
			tc_ग_लिखोl(status & (Int_BLEx | Int_FDAEx),
				  &tr->Int_Src);
		अगर (handled >= 0) अणु
			received += handled;
			अगर (received >= budget)
				अवरोध;
		पूर्ण
		status = tc_पढ़ोl(&tr->Int_Src);
	पूर्ण जबतक (status);
	spin_unlock(&lp->rx_lock);

	अगर (received < budget) अणु
		napi_complete_करोne(napi, received);
		/* enable पूर्णांकerrupts */
		tc_ग_लिखोl(tc_पढ़ोl(&tr->DMA_Ctl) & ~DMA_IntMask, &tr->DMA_Ctl);
	पूर्ण
	वापस received;
पूर्ण

#घोषणा TX_STA_ERR	(Tx_ExColl|Tx_Under|Tx_Defer|Tx_NCarr|Tx_LateColl|Tx_TxPar|Tx_SQErr)

अटल व्योम
tc35815_check_tx_stat(काष्ठा net_device *dev, पूर्णांक status)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	स्थिर अक्षर *msg = शून्य;

	/* count collisions */
	अगर (status & Tx_ExColl)
		dev->stats.collisions += 16;
	अगर (status & Tx_TxColl_MASK)
		dev->stats.collisions += status & Tx_TxColl_MASK;

	/* TX4939 करोes not have NCarr */
	अगर (lp->chiptype == TC35815_TX4939)
		status &= ~Tx_NCarr;
	/* WORKAROUND: ignore LostCrS in full duplex operation */
	अगर (!lp->link || lp->duplex == DUPLEX_FULL)
		status &= ~Tx_NCarr;

	अगर (!(status & TX_STA_ERR)) अणु
		/* no error. */
		dev->stats.tx_packets++;
		वापस;
	पूर्ण

	dev->stats.tx_errors++;
	अगर (status & Tx_ExColl) अणु
		dev->stats.tx_पातed_errors++;
		msg = "Excessive Collision.";
	पूर्ण
	अगर (status & Tx_Under) अणु
		dev->stats.tx_fअगरo_errors++;
		msg = "Tx FIFO Underrun.";
		अगर (lp->lstats.tx_underrun < TX_THRESHOLD_KEEP_LIMIT) अणु
			lp->lstats.tx_underrun++;
			अगर (lp->lstats.tx_underrun >= TX_THRESHOLD_KEEP_LIMIT) अणु
				काष्ठा tc35815_regs __iomem *tr =
					(काष्ठा tc35815_regs __iomem *)dev->base_addr;
				tc_ग_लिखोl(TX_THRESHOLD_MAX, &tr->TxThrsh);
				msg = "Tx FIFO Underrun.Change Tx threshold to max.";
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (status & Tx_Defer) अणु
		dev->stats.tx_fअगरo_errors++;
		msg = "Excessive Deferral.";
	पूर्ण
	अगर (status & Tx_NCarr) अणु
		dev->stats.tx_carrier_errors++;
		msg = "Lost Carrier Sense.";
	पूर्ण
	अगर (status & Tx_LateColl) अणु
		dev->stats.tx_पातed_errors++;
		msg = "Late Collision.";
	पूर्ण
	अगर (status & Tx_TxPar) अणु
		dev->stats.tx_fअगरo_errors++;
		msg = "Transmit Parity Error.";
	पूर्ण
	अगर (status & Tx_SQErr) अणु
		dev->stats.tx_heartbeat_errors++;
		msg = "Signal Quality Error.";
	पूर्ण
	अगर (msg && netअगर_msg_tx_err(lp))
		prपूर्णांकk(KERN_WARNING "%s: %s (%#x)\n", dev->name, msg, status);
पूर्ण

/* This handles TX complete events posted by the device
 * via पूर्णांकerrupts.
 */
अटल व्योम
tc35815_txकरोne(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	काष्ठा TxFD *txfd;
	अचिन्हित पूर्णांक fdctl;

	txfd = &lp->tfd_base[lp->tfd_end];
	जबतक (lp->tfd_start != lp->tfd_end &&
	       !((fdctl = le32_to_cpu(txfd->fd.FDCtl)) & FD_CownsFD)) अणु
		पूर्णांक status = le32_to_cpu(txfd->fd.FDStat);
		काष्ठा sk_buff *skb;
		अचिन्हित दीर्घ fdnext = le32_to_cpu(txfd->fd.FDNext);
		u32 fdप्रणाली = le32_to_cpu(txfd->fd.FDSystem);

		अगर (netअगर_msg_tx_करोne(lp)) अणु
			prपूर्णांकk("%s: complete TxFD.\n", dev->name);
			dump_txfd(txfd);
		पूर्ण
		tc35815_check_tx_stat(dev, status);

		skb = fdप्रणाली != 0xffffffff ?
			lp->tx_skbs[fdप्रणाली].skb : शून्य;
#अगर_घोषित DEBUG
		अगर (lp->tx_skbs[lp->tfd_end].skb != skb) अणु
			prपूर्णांकk("%s: tx_skbs mismatch.\n", dev->name);
			panic_queues(dev);
		पूर्ण
#अन्यथा
		BUG_ON(lp->tx_skbs[lp->tfd_end].skb != skb);
#पूर्ण_अगर
		अगर (skb) अणु
			dev->stats.tx_bytes += skb->len;
			dma_unmap_single(&lp->pci_dev->dev,
					 lp->tx_skbs[lp->tfd_end].skb_dma,
					 skb->len, DMA_TO_DEVICE);
			lp->tx_skbs[lp->tfd_end].skb = शून्य;
			lp->tx_skbs[lp->tfd_end].skb_dma = 0;
			dev_kमुक्त_skb_any(skb);
		पूर्ण
		txfd->fd.FDSystem = cpu_to_le32(0xffffffff);

		lp->tfd_end = (lp->tfd_end + 1) % TX_FD_NUM;
		txfd = &lp->tfd_base[lp->tfd_end];
#अगर_घोषित DEBUG
		अगर ((fdnext & ~FD_Next_EOL) != fd_virt_to_bus(lp, txfd)) अणु
			prपूर्णांकk("%s: TxFD FDNext invalid.\n", dev->name);
			panic_queues(dev);
		पूर्ण
#पूर्ण_अगर
		अगर (fdnext & FD_Next_EOL) अणु
			/* DMA Transmitter has been stopping... */
			अगर (lp->tfd_end != lp->tfd_start) अणु
				काष्ठा tc35815_regs __iomem *tr =
					(काष्ठा tc35815_regs __iomem *)dev->base_addr;
				पूर्णांक head = (lp->tfd_start + TX_FD_NUM - 1) % TX_FD_NUM;
				काष्ठा TxFD *txhead = &lp->tfd_base[head];
				पूर्णांक qlen = (lp->tfd_start + TX_FD_NUM
					    - lp->tfd_end) % TX_FD_NUM;

#अगर_घोषित DEBUG
				अगर (!(le32_to_cpu(txfd->fd.FDCtl) & FD_CownsFD)) अणु
					prपूर्णांकk("%s: TxFD FDCtl invalid.\n", dev->name);
					panic_queues(dev);
				पूर्ण
#पूर्ण_अगर
				/* log max queue length */
				अगर (lp->lstats.max_tx_qlen < qlen)
					lp->lstats.max_tx_qlen = qlen;


				/* start DMA Transmitter again */
				txhead->fd.FDNext |= cpu_to_le32(FD_Next_EOL);
				txhead->fd.FDCtl |= cpu_to_le32(FD_FrmOpt_IntTx);
				अगर (netअगर_msg_tx_queued(lp)) अणु
					prपूर्णांकk("%s: start TxFD on queue.\n",
					       dev->name);
					dump_txfd(txfd);
				पूर्ण
				tc_ग_लिखोl(fd_virt_to_bus(lp, txfd), &tr->TxFrmPtr);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* If we had stopped the queue due to a "tx full"
	 * condition, and space has now been made available,
	 * wake up the queue.
	 */
	अगर (netअगर_queue_stopped(dev) && !tc35815_tx_full(dev))
		netअगर_wake_queue(dev);
पूर्ण

/* The inverse routine to tc35815_खोलो(). */
अटल पूर्णांक
tc35815_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);

	netअगर_stop_queue(dev);
	napi_disable(&lp->napi);
	अगर (dev->phydev)
		phy_stop(dev->phydev);
	cancel_work_sync(&lp->restart_work);

	/* Flush the Tx and disable Rx here. */
	tc35815_chip_reset(dev);
	मुक्त_irq(dev->irq, dev);

	tc35815_मुक्त_queues(dev);

	वापस 0;

पूर्ण

/*
 * Get the current statistics.
 * This may be called with the card खोलो or बंदd.
 */
अटल काष्ठा net_device_stats *tc35815_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	अगर (netअगर_running(dev))
		/* Update the statistics from the device रेजिस्टरs. */
		dev->stats.rx_missed_errors += tc_पढ़ोl(&tr->Miss_Cnt);

	वापस &dev->stats;
पूर्ण

अटल व्योम tc35815_set_cam_entry(काष्ठा net_device *dev, पूर्णांक index, अचिन्हित अक्षर *addr)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	पूर्णांक cam_index = index * 6;
	u32 cam_data;
	u32 saved_addr;

	saved_addr = tc_पढ़ोl(&tr->CAM_Adr);

	अगर (netअगर_msg_hw(lp))
		prपूर्णांकk(KERN_DEBUG "%s: CAM %d: %pM\n",
			dev->name, index, addr);
	अगर (index & 1) अणु
		/* पढ़ो modअगरy ग_लिखो */
		tc_ग_लिखोl(cam_index - 2, &tr->CAM_Adr);
		cam_data = tc_पढ़ोl(&tr->CAM_Data) & 0xffff0000;
		cam_data |= addr[0] << 8 | addr[1];
		tc_ग_लिखोl(cam_data, &tr->CAM_Data);
		/* ग_लिखो whole word */
		tc_ग_लिखोl(cam_index + 2, &tr->CAM_Adr);
		cam_data = (addr[2] << 24) | (addr[3] << 16) | (addr[4] << 8) | addr[5];
		tc_ग_लिखोl(cam_data, &tr->CAM_Data);
	पूर्ण अन्यथा अणु
		/* ग_लिखो whole word */
		tc_ग_लिखोl(cam_index, &tr->CAM_Adr);
		cam_data = (addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3];
		tc_ग_लिखोl(cam_data, &tr->CAM_Data);
		/* पढ़ो modअगरy ग_लिखो */
		tc_ग_लिखोl(cam_index + 4, &tr->CAM_Adr);
		cam_data = tc_पढ़ोl(&tr->CAM_Data) & 0x0000ffff;
		cam_data |= addr[4] << 24 | (addr[5] << 16);
		tc_ग_लिखोl(cam_data, &tr->CAM_Data);
	पूर्ण

	tc_ग_लिखोl(saved_addr, &tr->CAM_Adr);
पूर्ण


/*
 * Set or clear the multicast filter क्रम this adaptor.
 * num_addrs == -1	Promiscuous mode, receive all packets
 * num_addrs == 0	Normal mode, clear multicast list
 * num_addrs > 0	Multicast mode, receive normal and MC packets,
 *			and करो best-efक्रमt filtering.
 */
अटल व्योम
tc35815_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;

	अगर (dev->flags & IFF_PROMISC) अणु
		/* With some (all?) 100MHalf HUB, controller will hang
		 * अगर we enabled promiscuous mode beक्रमe linkup...
		 */
		काष्ठा tc35815_local *lp = netdev_priv(dev);

		अगर (!lp->link)
			वापस;
		/* Enable promiscuous mode */
		tc_ग_लिखोl(CAM_CompEn | CAM_BroadAcc | CAM_GroupAcc | CAM_StationAcc, &tr->CAM_Ctl);
	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI) ||
		  netdev_mc_count(dev) > CAM_ENTRY_MAX - 3) अणु
		/* CAM 0, 1, 20 are reserved. */
		/* Disable promiscuous mode, use normal mode. */
		tc_ग_लिखोl(CAM_CompEn | CAM_BroadAcc | CAM_GroupAcc, &tr->CAM_Ctl);
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक i;
		पूर्णांक ena_bits = CAM_Ena_Bit(CAM_ENTRY_SOURCE);

		tc_ग_लिखोl(0, &tr->CAM_Ctl);
		/* Walk the address list, and load the filter */
		i = 0;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			/* entry 0,1 is reserved. */
			tc35815_set_cam_entry(dev, i + 2, ha->addr);
			ena_bits |= CAM_Ena_Bit(i + 2);
			i++;
		पूर्ण
		tc_ग_लिखोl(ena_bits, &tr->CAM_Ena);
		tc_ग_लिखोl(CAM_CompEn | CAM_BroadAcc, &tr->CAM_Ctl);
	पूर्ण अन्यथा अणु
		tc_ग_लिखोl(CAM_Ena_Bit(CAM_ENTRY_SOURCE), &tr->CAM_Ena);
		tc_ग_लिखोl(CAM_CompEn | CAM_BroadAcc, &tr->CAM_Ctl);
	पूर्ण
पूर्ण

अटल व्योम tc35815_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);

	strlcpy(info->driver, MODNAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(lp->pci_dev), माप(info->bus_info));
पूर्ण

अटल u32 tc35815_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	वापस lp->msg_enable;
पूर्ण

अटल व्योम tc35815_set_msglevel(काष्ठा net_device *dev, u32 datum)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	lp->msg_enable = datum;
पूर्ण

अटल पूर्णांक tc35815_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस माप(lp->lstats) / माप(पूर्णांक);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम tc35815_get_ethtool_stats(काष्ठा net_device *dev, काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	data[0] = lp->lstats.max_tx_qlen;
	data[1] = lp->lstats.tx_पूर्णांकs;
	data[2] = lp->lstats.rx_पूर्णांकs;
	data[3] = lp->lstats.tx_underrun;
पूर्ण

अटल काष्ठा अणु
	स्थिर अक्षर str[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "max_tx_qlen" पूर्ण,
	अणु "tx_ints" पूर्ण,
	अणु "rx_ints" पूर्ण,
	अणु "tx_underrun" पूर्ण,
पूर्ण;

अटल व्योम tc35815_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	स_नकल(data, ethtool_stats_keys, माप(ethtool_stats_keys));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops tc35815_ethtool_ops = अणु
	.get_drvinfo		= tc35815_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_msglevel		= tc35815_get_msglevel,
	.set_msglevel		= tc35815_set_msglevel,
	.get_strings		= tc35815_get_strings,
	.get_sset_count		= tc35815_get_sset_count,
	.get_ethtool_stats	= tc35815_get_ethtool_stats,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल व्योम tc35815_chip_reset(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	पूर्णांक i;
	/* reset the controller */
	tc_ग_लिखोl(MAC_Reset, &tr->MAC_Ctl);
	udelay(4); /* 3200ns */
	i = 0;
	जबतक (tc_पढ़ोl(&tr->MAC_Ctl) & MAC_Reset) अणु
		अगर (i++ > 100) अणु
			prपूर्णांकk(KERN_ERR "%s: MAC reset failed.\n", dev->name);
			अवरोध;
		पूर्ण
		mdelay(1);
	पूर्ण
	tc_ग_लिखोl(0, &tr->MAC_Ctl);

	/* initialize रेजिस्टरs to शेष value */
	tc_ग_लिखोl(0, &tr->DMA_Ctl);
	tc_ग_लिखोl(0, &tr->TxThrsh);
	tc_ग_लिखोl(0, &tr->TxPollCtr);
	tc_ग_लिखोl(0, &tr->RxFragSize);
	tc_ग_लिखोl(0, &tr->Int_En);
	tc_ग_लिखोl(0, &tr->FDA_Bas);
	tc_ग_लिखोl(0, &tr->FDA_Lim);
	tc_ग_लिखोl(0xffffffff, &tr->Int_Src);	/* Write 1 to clear */
	tc_ग_लिखोl(0, &tr->CAM_Ctl);
	tc_ग_लिखोl(0, &tr->Tx_Ctl);
	tc_ग_लिखोl(0, &tr->Rx_Ctl);
	tc_ग_लिखोl(0, &tr->CAM_Ena);
	(व्योम)tc_पढ़ोl(&tr->Miss_Cnt);	/* Read to clear */

	/* initialize पूर्णांकernal SRAM */
	tc_ग_लिखोl(DMA_TestMode, &tr->DMA_Ctl);
	क्रम (i = 0; i < 0x1000; i += 4) अणु
		tc_ग_लिखोl(i, &tr->CAM_Adr);
		tc_ग_लिखोl(0, &tr->CAM_Data);
	पूर्ण
	tc_ग_लिखोl(0, &tr->DMA_Ctl);
पूर्ण

अटल व्योम tc35815_chip_init(काष्ठा net_device *dev)
अणु
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	काष्ठा tc35815_regs __iomem *tr =
		(काष्ठा tc35815_regs __iomem *)dev->base_addr;
	अचिन्हित दीर्घ txctl = TX_CTL_CMD;

	/* load station address to CAM */
	tc35815_set_cam_entry(dev, CAM_ENTRY_SOURCE, dev->dev_addr);

	/* Enable CAM (broadcast and unicast) */
	tc_ग_लिखोl(CAM_Ena_Bit(CAM_ENTRY_SOURCE), &tr->CAM_Ena);
	tc_ग_लिखोl(CAM_CompEn | CAM_BroadAcc, &tr->CAM_Ctl);

	/* Use DMA_RxAlign_2 to make IP header 4-byte aligned. */
	अगर (HAVE_DMA_RXALIGN(lp))
		tc_ग_लिखोl(DMA_BURST_SIZE | DMA_RxAlign_2, &tr->DMA_Ctl);
	अन्यथा
		tc_ग_लिखोl(DMA_BURST_SIZE, &tr->DMA_Ctl);
	tc_ग_लिखोl(0, &tr->TxPollCtr);	/* Batch mode */
	tc_ग_लिखोl(TX_THRESHOLD, &tr->TxThrsh);
	tc_ग_लिखोl(INT_EN_CMD, &tr->Int_En);

	/* set queues */
	tc_ग_लिखोl(fd_virt_to_bus(lp, lp->rfd_base), &tr->FDA_Bas);
	tc_ग_लिखोl((अचिन्हित दीर्घ)lp->rfd_limit - (अचिन्हित दीर्घ)lp->rfd_base,
		  &tr->FDA_Lim);
	/*
	 * Activation method:
	 * First, enable the MAC Transmitter and the DMA Receive circuits.
	 * Then enable the DMA Transmitter and the MAC Receive circuits.
	 */
	tc_ग_लिखोl(fd_virt_to_bus(lp, lp->fbl_ptr), &tr->BLFrmPtr);	/* start DMA receiver */
	tc_ग_लिखोl(RX_CTL_CMD, &tr->Rx_Ctl);	/* start MAC receiver */

	/* start MAC transmitter */
	/* TX4939 करोes not have EnLCarr */
	अगर (lp->chiptype == TC35815_TX4939)
		txctl &= ~Tx_EnLCarr;
	/* WORKAROUND: ignore LostCrS in full duplex operation */
	अगर (!dev->phydev || !lp->link || lp->duplex == DUPLEX_FULL)
		txctl &= ~Tx_EnLCarr;
	tc_ग_लिखोl(txctl, &tr->Tx_Ctl);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tc35815_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा tc35815_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	pci_save_state(pdev);
	अगर (!netअगर_running(dev))
		वापस 0;
	netअगर_device_detach(dev);
	अगर (dev->phydev)
		phy_stop(dev->phydev);
	spin_lock_irqsave(&lp->lock, flags);
	tc35815_chip_reset(dev);
	spin_unlock_irqrestore(&lp->lock, flags);
	pci_set_घातer_state(pdev, PCI_D3hot);
	वापस 0;
पूर्ण

अटल पूर्णांक tc35815_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	pci_restore_state(pdev);
	अगर (!netअगर_running(dev))
		वापस 0;
	pci_set_घातer_state(pdev, PCI_D0);
	tc35815_restart(dev);
	netअगर_carrier_off(dev);
	अगर (dev->phydev)
		phy_start(dev->phydev);
	netअगर_device_attach(dev);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा pci_driver tc35815_pci_driver = अणु
	.name		= MODNAME,
	.id_table	= tc35815_pci_tbl,
	.probe		= tc35815_init_one,
	.हटाओ		= tc35815_हटाओ_one,
#अगर_घोषित CONFIG_PM
	.suspend	= tc35815_suspend,
	.resume		= tc35815_resume,
#पूर्ण_अगर
पूर्ण;

module_param_named(speed, options.speed, पूर्णांक, 0);
MODULE_PARM_DESC(speed, "0:auto, 10:10Mbps, 100:100Mbps");
module_param_named(duplex, options.duplex, पूर्णांक, 0);
MODULE_PARM_DESC(duplex, "0:auto, 1:half, 2:full");

module_pci_driver(tc35815_pci_driver);
MODULE_DESCRIPTION("TOSHIBA TC35815 PCI 10M/100M Ethernet driver");
MODULE_LICENSE("GPL");
