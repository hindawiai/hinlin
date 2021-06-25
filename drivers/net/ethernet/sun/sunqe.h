<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Id: sunqe.h,v 1.13 2000/02/09 11:15:42 davem Exp $
 * sunqe.h: Definitions क्रम the Sun QuadEthernet driver.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SUNQE_H
#घोषणा _SUNQE_H

/* QEC global रेजिस्टरs. */
#घोषणा GLOB_CTRL	0x00UL		/* Control			*/
#घोषणा GLOB_STAT	0x04UL		/* Status			*/
#घोषणा GLOB_PSIZE	0x08UL		/* Packet Size			*/
#घोषणा GLOB_MSIZE	0x0cUL		/* Local-memory Size		*/
#घोषणा GLOB_RSIZE	0x10UL		/* Receive partition size	*/
#घोषणा GLOB_TSIZE	0x14UL		/* Transmit partition size	*/
#घोषणा GLOB_REG_SIZE	0x18UL

#घोषणा GLOB_CTRL_MMODE       0x40000000 /* MACE qec mode            */
#घोषणा GLOB_CTRL_BMODE       0x10000000 /* BigMAC qec mode          */
#घोषणा GLOB_CTRL_EPAR        0x00000020 /* Enable parity            */
#घोषणा GLOB_CTRL_ACNTRL      0x00000018 /* SBUS arbitration control */
#घोषणा GLOB_CTRL_B64         0x00000004 /* 64 byte dvma bursts      */
#घोषणा GLOB_CTRL_B32         0x00000002 /* 32 byte dvma bursts      */
#घोषणा GLOB_CTRL_B16         0x00000000 /* 16 byte dvma bursts      */
#घोषणा GLOB_CTRL_RESET       0x00000001 /* Reset the QEC            */

#घोषणा GLOB_STAT_TX          0x00000008 /* BigMAC Transmit IRQ      */
#घोषणा GLOB_STAT_RX          0x00000004 /* BigMAC Receive IRQ       */
#घोषणा GLOB_STAT_BM          0x00000002 /* BigMAC Global IRQ        */
#घोषणा GLOB_STAT_ER          0x00000001 /* BigMAC Error IRQ         */

#घोषणा GLOB_PSIZE_2048       0x00       /* 2k packet size           */
#घोषणा GLOB_PSIZE_4096       0x01       /* 4k packet size           */
#घोषणा GLOB_PSIZE_6144       0x10       /* 6k packet size           */
#घोषणा GLOB_PSIZE_8192       0x11       /* 8k packet size           */

/* In MACE mode, there are four qe channels.  Each channel has it's own
 * status bits in the QEC status रेजिस्टर.  This macro picks out the
 * ones you want.
 */
#घोषणा GLOB_STAT_PER_QE(status, channel) (((status) >> ((channel) * 4)) & 0xf)

/* The following रेजिस्टरs are क्रम per-qe channel inक्रमmation/status. */
#घोषणा CREG_CTRL	0x00UL	/* Control                   */
#घोषणा CREG_STAT	0x04UL	/* Status                    */
#घोषणा CREG_RXDS	0x08UL	/* RX descriptor ring ptr    */
#घोषणा CREG_TXDS	0x0cUL	/* TX descriptor ring ptr    */
#घोषणा CREG_RIMASK	0x10UL	/* RX Interrupt Mask         */
#घोषणा CREG_TIMASK	0x14UL	/* TX Interrupt Mask         */
#घोषणा CREG_QMASK	0x18UL	/* QEC Error Interrupt Mask  */
#घोषणा CREG_MMASK	0x1cUL	/* MACE Error Interrupt Mask */
#घोषणा CREG_RXWBUFPTR	0x20UL	/* Local memory rx ग_लिखो ptr */
#घोषणा CREG_RXRBUFPTR	0x24UL	/* Local memory rx पढ़ो ptr  */
#घोषणा CREG_TXWBUFPTR	0x28UL	/* Local memory tx ग_लिखो ptr */
#घोषणा CREG_TXRBUFPTR	0x2cUL	/* Local memory tx पढ़ो ptr  */
#घोषणा CREG_CCNT	0x30UL	/* Collision Counter         */
#घोषणा CREG_PIPG	0x34UL	/* Inter-Frame Gap           */
#घोषणा CREG_REG_SIZE	0x38UL

#घोषणा CREG_CTRL_RXOFF       0x00000004  /* Disable this qe's receiver*/
#घोषणा CREG_CTRL_RESET       0x00000002  /* Reset this qe channel     */
#घोषणा CREG_CTRL_TWAKEUP     0x00000001  /* Transmitter Wakeup, 'go'. */

#घोषणा CREG_STAT_EDEFER      0x10000000  /* Excessive Defers          */
#घोषणा CREG_STAT_CLOSS       0x08000000  /* Carrier Loss              */
#घोषणा CREG_STAT_ERETRIES    0x04000000  /* More than 16 retries      */
#घोषणा CREG_STAT_LCOLL       0x02000000  /* Late TX Collision         */
#घोषणा CREG_STAT_FUFLOW      0x01000000  /* FIFO Underflow            */
#घोषणा CREG_STAT_JERROR      0x00800000  /* Jabber Error              */
#घोषणा CREG_STAT_BERROR      0x00400000  /* Babble Error              */
#घोषणा CREG_STAT_TXIRQ       0x00200000  /* Transmit Interrupt        */
#घोषणा CREG_STAT_CCOFLOW     0x00100000  /* TX Coll-counter Overflow  */
#घोषणा CREG_STAT_TXDERROR    0x00080000  /* TX Descriptor is bogus    */
#घोषणा CREG_STAT_TXLERR      0x00040000  /* Late Transmit Error       */
#घोषणा CREG_STAT_TXPERR      0x00020000  /* Transmit Parity Error     */
#घोषणा CREG_STAT_TXSERR      0x00010000  /* Transmit SBUS error ack   */
#घोषणा CREG_STAT_RCCOFLOW    0x00001000  /* RX Coll-counter Overflow  */
#घोषणा CREG_STAT_RUOFLOW     0x00000800  /* Runt Counter Overflow     */
#घोषणा CREG_STAT_MCOFLOW     0x00000400  /* Missed Counter Overflow   */
#घोषणा CREG_STAT_RXFOFLOW    0x00000200  /* RX FIFO Overflow          */
#घोषणा CREG_STAT_RLCOLL      0x00000100  /* RX Late Collision         */
#घोषणा CREG_STAT_FCOFLOW     0x00000080  /* Frame Counter Overflow    */
#घोषणा CREG_STAT_CECOFLOW    0x00000040  /* CRC Error-counter Overflow*/
#घोषणा CREG_STAT_RXIRQ       0x00000020  /* Receive Interrupt         */
#घोषणा CREG_STAT_RXDROP      0x00000010  /* Dropped a RX'd packet     */
#घोषणा CREG_STAT_RXSMALL     0x00000008  /* Receive buffer too small  */
#घोषणा CREG_STAT_RXLERR      0x00000004  /* Receive Late Error        */
#घोषणा CREG_STAT_RXPERR      0x00000002  /* Receive Parity Error      */
#घोषणा CREG_STAT_RXSERR      0x00000001  /* Receive SBUS Error ACK    */

#घोषणा CREG_STAT_ERRORS      (CREG_STAT_EDEFER|CREG_STAT_CLOSS|CREG_STAT_ERETRIES|     \
			       CREG_STAT_LCOLL|CREG_STAT_FUFLOW|CREG_STAT_JERROR|       \
			       CREG_STAT_BERROR|CREG_STAT_CCOFLOW|CREG_STAT_TXDERROR|   \
			       CREG_STAT_TXLERR|CREG_STAT_TXPERR|CREG_STAT_TXSERR|      \
			       CREG_STAT_RCCOFLOW|CREG_STAT_RUOFLOW|CREG_STAT_MCOFLOW| \
			       CREG_STAT_RXFOFLOW|CREG_STAT_RLCOLL|CREG_STAT_FCOFLOW|   \
			       CREG_STAT_CECOFLOW|CREG_STAT_RXDROP|CREG_STAT_RXSMALL|   \
			       CREG_STAT_RXLERR|CREG_STAT_RXPERR|CREG_STAT_RXSERR)

#घोषणा CREG_QMASK_COFLOW     0x00100000  /* CollCntr overflow         */
#घोषणा CREG_QMASK_TXDERROR   0x00080000  /* TXD error                 */
#घोषणा CREG_QMASK_TXLERR     0x00040000  /* TX late error             */
#घोषणा CREG_QMASK_TXPERR     0x00020000  /* TX parity error           */
#घोषणा CREG_QMASK_TXSERR     0x00010000  /* TX sbus error ack         */
#घोषणा CREG_QMASK_RXDROP     0x00000010  /* RX drop                   */
#घोषणा CREG_QMASK_RXBERROR   0x00000008  /* RX buffer error           */
#घोषणा CREG_QMASK_RXLEERR    0x00000004  /* RX late error             */
#घोषणा CREG_QMASK_RXPERR     0x00000002  /* RX parity error           */
#घोषणा CREG_QMASK_RXSERR     0x00000001  /* RX sbus error ack         */

#घोषणा CREG_MMASK_EDEFER     0x10000000  /* Excess defer              */
#घोषणा CREG_MMASK_CLOSS      0x08000000  /* Carrier loss              */
#घोषणा CREG_MMASK_ERETRY     0x04000000  /* Excess retry              */
#घोषणा CREG_MMASK_LCOLL      0x02000000  /* Late collision error      */
#घोषणा CREG_MMASK_UFLOW      0x01000000  /* Underflow                 */
#घोषणा CREG_MMASK_JABBER     0x00800000  /* Jabber error              */
#घोषणा CREG_MMASK_BABBLE     0x00400000  /* Babble error              */
#घोषणा CREG_MMASK_OFLOW      0x00000800  /* Overflow                  */
#घोषणा CREG_MMASK_RXCOLL     0x00000400  /* RX Coll-Cntr overflow     */
#घोषणा CREG_MMASK_RPKT       0x00000200  /* Runt pkt overflow         */
#घोषणा CREG_MMASK_MPKT       0x00000100  /* Missed pkt overflow       */

#घोषणा CREG_PIPG_TENAB       0x00000020  /* Enable Throttle           */
#घोषणा CREG_PIPG_MMODE       0x00000010  /* Manual Mode               */
#घोषणा CREG_PIPG_WMASK       0x0000000f  /* SBUS Wait Mask            */

/* Per-channel AMD 79C940 MACE रेजिस्टरs. */
#घोषणा MREGS_RXFIFO	0x00UL	/* Receive FIFO                   */
#घोषणा MREGS_TXFIFO	0x01UL	/* Transmit FIFO                  */
#घोषणा MREGS_TXFCNTL	0x02UL	/* Transmit Frame Control         */
#घोषणा MREGS_TXFSTAT	0x03UL	/* Transmit Frame Status          */
#घोषणा MREGS_TXRCNT	0x04UL	/* Transmit Retry Count           */
#घोषणा MREGS_RXFCNTL	0x05UL	/* Receive Frame Control          */
#घोषणा MREGS_RXFSTAT	0x06UL	/* Receive Frame Status           */
#घोषणा MREGS_FFCNT	0x07UL	/* FIFO Frame Count               */
#घोषणा MREGS_IREG	0x08UL	/* Interrupt Register             */
#घोषणा MREGS_IMASK	0x09UL	/* Interrupt Mask                 */
#घोषणा MREGS_POLL	0x0aUL	/* POLL Register                  */
#घोषणा MREGS_BCONFIG	0x0bUL	/* BIU Config                     */
#घोषणा MREGS_FCONFIG	0x0cUL	/* FIFO Config                    */
#घोषणा MREGS_MCONFIG	0x0dUL	/* MAC Config                     */
#घोषणा MREGS_PLSCONFIG	0x0eUL	/* PLS Config                     */
#घोषणा MREGS_PHYCONFIG	0x0fUL	/* PHY Config                     */
#घोषणा MREGS_CHIPID1	0x10UL	/* Chip-ID, low bits              */
#घोषणा MREGS_CHIPID2	0x11UL	/* Chip-ID, high bits             */
#घोषणा MREGS_IACONFIG	0x12UL	/* Internal Address Config        */
	/* 0x13UL, reserved */
#घोषणा MREGS_FILTER	0x14UL	/* Logical Address Filter         */
#घोषणा MREGS_ETHADDR	0x15UL	/* Our Ethernet Address           */
	/* 0x16UL, reserved */
	/* 0x17UL, reserved */
#घोषणा MREGS_MPCNT	0x18UL	/* Missed Packet Count            */
	/* 0x19UL, reserved */
#घोषणा MREGS_RPCNT	0x1aUL	/* Runt Packet Count              */
#घोषणा MREGS_RCCNT	0x1bUL	/* RX Collision Count             */
	/* 0x1cUL, reserved */
#घोषणा MREGS_UTEST	0x1dUL	/* User Test                      */
#घोषणा MREGS_RTEST1	0x1eUL	/* Reserved Test 1                */
#घोषणा MREGS_RTEST2	0x1fUL	/* Reserved Test 2                */
#घोषणा MREGS_REG_SIZE	0x20UL

#घोषणा MREGS_TXFCNTL_DRETRY        0x80 /* Retry disable                  */
#घोषणा MREGS_TXFCNTL_DFCS          0x08 /* Disable TX FCS                 */
#घोषणा MREGS_TXFCNTL_AUTOPAD       0x01 /* TX स्वतः pad                    */

#घोषणा MREGS_TXFSTAT_VALID         0x80 /* TX valid                       */
#घोषणा MREGS_TXFSTAT_UNDERFLOW     0x40 /* TX underflow                   */
#घोषणा MREGS_TXFSTAT_LCOLL         0x20 /* TX late collision              */
#घोषणा MREGS_TXFSTAT_MRETRY        0x10 /* TX > 1 retries                 */
#घोषणा MREGS_TXFSTAT_ORETRY        0x08 /* TX 1 retry                     */
#घोषणा MREGS_TXFSTAT_PDEFER        0x04 /* TX pkt deferred                */
#घोषणा MREGS_TXFSTAT_CLOSS         0x02 /* TX carrier lost                */
#घोषणा MREGS_TXFSTAT_RERROR        0x01 /* TX retry error                 */

#घोषणा MREGS_TXRCNT_EDEFER         0x80 /* TX Excess defers               */
#घोषणा MREGS_TXRCNT_CMASK          0x0f /* TX retry count                 */

#घोषणा MREGS_RXFCNTL_LOWLAT        0x08 /* RX low latency                 */
#घोषणा MREGS_RXFCNTL_AREJECT       0x04 /* RX addr match rej              */
#घोषणा MREGS_RXFCNTL_AUTOSTRIP     0x01 /* RX स्वतः strip                  */

#घोषणा MREGS_RXFSTAT_OVERFLOW      0x80 /* RX overflow                    */
#घोषणा MREGS_RXFSTAT_LCOLL         0x40 /* RX late collision              */
#घोषणा MREGS_RXFSTAT_FERROR        0x20 /* RX framing error               */
#घोषणा MREGS_RXFSTAT_FCSERROR      0x10 /* RX FCS error                   */
#घोषणा MREGS_RXFSTAT_RBCNT         0x0f /* RX msg byte count              */

#घोषणा MREGS_FFCNT_RX              0xf0 /* RX FIFO frame cnt              */
#घोषणा MREGS_FFCNT_TX              0x0f /* TX FIFO frame cnt              */

#घोषणा MREGS_IREG_JABBER           0x80 /* IRQ Jabber error               */
#घोषणा MREGS_IREG_BABBLE           0x40 /* IRQ Babble error               */
#घोषणा MREGS_IREG_COLL             0x20 /* IRQ Collision error            */
#घोषणा MREGS_IREG_RCCO             0x10 /* IRQ Collision cnt overflow     */
#घोषणा MREGS_IREG_RPKTCO           0x08 /* IRQ Runt packet count overflow */
#घोषणा MREGS_IREG_MPKTCO           0x04 /* IRQ missed packet cnt overflow */
#घोषणा MREGS_IREG_RXIRQ            0x02 /* IRQ RX'd a packet              */
#घोषणा MREGS_IREG_TXIRQ            0x01 /* IRQ TX'd a packet              */

#घोषणा MREGS_IMASK_BABBLE          0x40 /* IMASK Babble errors            */
#घोषणा MREGS_IMASK_COLL            0x20 /* IMASK Collision errors         */
#घोषणा MREGS_IMASK_MPKTCO          0x04 /* IMASK Missed pkt cnt overflow  */
#घोषणा MREGS_IMASK_RXIRQ           0x02 /* IMASK RX पूर्णांकerrupts            */
#घोषणा MREGS_IMASK_TXIRQ           0x01 /* IMASK TX पूर्णांकerrupts            */

#घोषणा MREGS_POLL_TXVALID          0x80 /* TX is valid                    */
#घोषणा MREGS_POLL_TDTR             0x40 /* TX data transfer request       */
#घोषणा MREGS_POLL_RDTR             0x20 /* RX data transfer request       */

#घोषणा MREGS_BCONFIG_BSWAP         0x40 /* Byte Swap                      */
#घोषणा MREGS_BCONFIG_4TS           0x00 /* 4byte transmit start poपूर्णांक     */
#घोषणा MREGS_BCONFIG_16TS          0x10 /* 16byte transmit start poपूर्णांक    */
#घोषणा MREGS_BCONFIG_64TS          0x20 /* 64byte transmit start poपूर्णांक    */
#घोषणा MREGS_BCONFIG_112TS         0x30 /* 112byte transmit start poपूर्णांक   */
#घोषणा MREGS_BCONFIG_RESET         0x01 /* SW-Reset the MACE              */

#घोषणा MREGS_FCONFIG_TXF8          0x00 /* TX fअगरo 8 ग_लिखो cycles         */
#घोषणा MREGS_FCONFIG_TXF32         0x80 /* TX fअगरo 32 ग_लिखो cycles        */
#घोषणा MREGS_FCONFIG_TXF16         0x40 /* TX fअगरo 16 ग_लिखो cycles        */
#घोषणा MREGS_FCONFIG_RXF64         0x20 /* RX fअगरo 64 ग_लिखो cycles        */
#घोषणा MREGS_FCONFIG_RXF32         0x10 /* RX fअगरo 32 ग_लिखो cycles        */
#घोषणा MREGS_FCONFIG_RXF16         0x00 /* RX fअगरo 16 ग_लिखो cycles        */
#घोषणा MREGS_FCONFIG_TFWU          0x08 /* TX fअगरo watermark update       */
#घोषणा MREGS_FCONFIG_RFWU          0x04 /* RX fअगरo watermark update       */
#घोषणा MREGS_FCONFIG_TBENAB        0x02 /* TX burst enable                */
#घोषणा MREGS_FCONFIG_RBENAB        0x01 /* RX burst enable                */

#घोषणा MREGS_MCONFIG_PROMISC       0x80 /* Promiscuous mode enable        */
#घोषणा MREGS_MCONFIG_TPDDISAB      0x40 /* TX 2part deferral enable       */
#घोषणा MREGS_MCONFIG_MBAENAB       0x20 /* Modअगरied backoff enable        */
#घोषणा MREGS_MCONFIG_RPADISAB      0x08 /* RX physical addr disable       */
#घोषणा MREGS_MCONFIG_RBDISAB       0x04 /* RX broadcast disable           */
#घोषणा MREGS_MCONFIG_TXENAB        0x02 /* Enable transmitter             */
#घोषणा MREGS_MCONFIG_RXENAB        0x01 /* Enable receiver                */

#घोषणा MREGS_PLSCONFIG_TXMS        0x08 /* TX mode select                 */
#घोषणा MREGS_PLSCONFIG_GPSI        0x06 /* Use GPSI connector             */
#घोषणा MREGS_PLSCONFIG_DAI         0x04 /* Use DAI connector              */
#घोषणा MREGS_PLSCONFIG_TP          0x02 /* Use TwistedPair connector      */
#घोषणा MREGS_PLSCONFIG_AUI         0x00 /* Use AUI connector              */
#घोषणा MREGS_PLSCONFIG_IOENAB      0x01 /* PLS I/O enable                 */

#घोषणा MREGS_PHYCONFIG_LSTAT       0x80 /* Link status                    */
#घोषणा MREGS_PHYCONFIG_LTESTDIS    0x40 /* Disable link test logic        */
#घोषणा MREGS_PHYCONFIG_RXPOLARITY  0x20 /* RX polarity                    */
#घोषणा MREGS_PHYCONFIG_APCDISAB    0x10 /* AutoPolarityCorrect disab      */
#घोषणा MREGS_PHYCONFIG_LTENAB      0x08 /* Select low threshold           */
#घोषणा MREGS_PHYCONFIG_AUTO        0x04 /* Connector port स्वतः-sel        */
#घोषणा MREGS_PHYCONFIG_RWU         0x02 /* Remote WakeUp                  */
#घोषणा MREGS_PHYCONFIG_AW          0x01 /* Auto Wakeup                    */

#घोषणा MREGS_IACONFIG_ACHNGE       0x80 /* Do address change              */
#घोषणा MREGS_IACONFIG_PARESET      0x04 /* Physical address reset         */
#घोषणा MREGS_IACONFIG_LARESET      0x02 /* Logical address reset          */

#घोषणा MREGS_UTEST_RTRENAB         0x80 /* Enable resv test रेजिस्टर      */
#घोषणा MREGS_UTEST_RTRDISAB        0x40 /* Disab resv test रेजिस्टर       */
#घोषणा MREGS_UTEST_RPACCEPT        0x20 /* Accept runt packets            */
#घोषणा MREGS_UTEST_FCOLL           0x10 /* Force collision status         */
#घोषणा MREGS_UTEST_FCSENAB         0x08 /* Enable FCS on RX               */
#घोषणा MREGS_UTEST_INTLOOPM        0x06 /* Intern lpback w/MENDEC         */
#घोषणा MREGS_UTEST_INTLOOP         0x04 /* Intern lpback                  */
#घोषणा MREGS_UTEST_EXTLOOP         0x02 /* Extern lpback                  */
#घोषणा MREGS_UTEST_NOLOOP          0x00 /* No loopback                    */

काष्ठा qe_rxd अणु
	u32 rx_flags;
	u32 rx_addr;
पूर्ण;

#घोषणा RXD_OWN      0x80000000 /* Ownership.      */
#घोषणा RXD_UPDATE   0x10000000 /* Being Updated?  */
#घोषणा RXD_LENGTH   0x000007ff /* Packet Length.  */

काष्ठा qe_txd अणु
	u32 tx_flags;
	u32 tx_addr;
पूर्ण;

#घोषणा TXD_OWN      0x80000000 /* Ownership.      */
#घोषणा TXD_SOP      0x40000000 /* Start Of Packet */
#घोषणा TXD_EOP      0x20000000 /* End Of Packet   */
#घोषणा TXD_UPDATE   0x10000000 /* Being Updated?  */
#घोषणा TXD_LENGTH   0x000007ff /* Packet Length.  */

#घोषणा TX_RING_MAXSIZE   256
#घोषणा RX_RING_MAXSIZE   256

#घोषणा TX_RING_SIZE      16
#घोषणा RX_RING_SIZE      16

#घोषणा NEXT_RX(num)       (((num) + 1) & (RX_RING_MAXSIZE - 1))
#घोषणा NEXT_TX(num)       (((num) + 1) & (TX_RING_MAXSIZE - 1))
#घोषणा PREV_RX(num)       (((num) - 1) & (RX_RING_MAXSIZE - 1))
#घोषणा PREV_TX(num)       (((num) - 1) & (TX_RING_MAXSIZE - 1))

#घोषणा TX_BUFFS_AVAIL(qp)                                    \
        (((qp)->tx_old <= (qp)->tx_new) ?                     \
	  (qp)->tx_old + (TX_RING_SIZE - 1) - (qp)->tx_new :  \
			    (qp)->tx_old - (qp)->tx_new - 1)

काष्ठा qe_init_block अणु
	काष्ठा qe_rxd qe_rxd[RX_RING_MAXSIZE];
	काष्ठा qe_txd qe_txd[TX_RING_MAXSIZE];
पूर्ण;

#घोषणा qib_offset(mem, elem) \
((__u32)((अचिन्हित दीर्घ)(&(((काष्ठा qe_init_block *)0)->mem[elem]))))

काष्ठा sunqe;

काष्ठा sunqec अणु
	व्योम __iomem		*gregs;		/* QEC Global Registers         */
	काष्ठा sunqe		*qes[4];	/* Each child MACE              */
	अचिन्हित पूर्णांक            qec_bursts;	/* Support burst sizes          */
	काष्ठा platक्रमm_device	*op;		/* QEC's OF device              */
	काष्ठा sunqec		*next_module;	/* List of all QECs in प्रणाली   */
पूर्ण;

#घोषणा PKT_BUF_SZ	1664
#घोषणा RXD_PKT_SZ	1664

काष्ठा sunqe_buffers अणु
	u8	tx_buf[TX_RING_SIZE][PKT_BUF_SZ];
	u8	__pad[2];
	u8	rx_buf[RX_RING_SIZE][PKT_BUF_SZ];
पूर्ण;

#घोषणा qebuf_offset(mem, elem) \
((__u32)((अचिन्हित दीर्घ)(&(((काष्ठा sunqe_buffers *)0)->mem[elem][0]))))

काष्ठा sunqe अणु
	व्योम __iomem			*qcregs;		/* QEC per-channel Registers   */
	व्योम __iomem			*mregs;		/* Per-channel MACE Registers  */
	काष्ठा qe_init_block      	*qe_block;	/* RX and TX descriptors       */
	dma_addr_t			qblock_dvma;	/* RX and TX descriptors       */
	spinlock_t			lock;		/* Protects txfull state       */
	पूर्णांक                        	rx_new, rx_old;	/* RX ring extents	       */
	पूर्णांक			   	tx_new, tx_old;	/* TX ring extents	       */
	काष्ठा sunqe_buffers		*buffers;	/* CPU visible address.        */
	dma_addr_t			buffers_dvma;	/* DVMA visible address.       */
	काष्ठा sunqec			*parent;
	u8				mconfig;	/* Base MACE mconfig value     */
	काष्ठा platक्रमm_device		*op;		/* QE's OF device काष्ठा       */
	काष्ठा net_device		*dev;		/* QE's netdevice काष्ठा       */
	पूर्णांक				channel;	/* Who am I?                   */
पूर्ण;

#पूर्ण_अगर /* !(_SUNQE_H) */
