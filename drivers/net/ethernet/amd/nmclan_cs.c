<शैली गुरु>
/* ----------------------------------------------------------------------------
Linux PCMCIA ethernet adapter driver क्रम the New Media Ethernet LAN.
  nmclan_cs.c,v 0.16 1995/07/01 06:42:17 rpao Exp rpao

  The Ethernet LAN uses the Advanced Micro Devices (AMD) Am79C940 Media
  Access Controller क्रम Ethernet (MACE).  It is essentially the Am2150
  PCMCIA Ethernet card contained in the Am2150 Demo Kit.

Written by Roger C. Pao <rpao@paonet.org>
  Copyright 1995 Roger C. Pao
  Linux 2.5 cleanups Copyright Red Hat 2003

  This software may be used and distributed according to the terms of
  the GNU General Public License.

Ported to Linux 1.3.* network driver environment by
  Matti Aarnio <mea@utu.fi>

References

  Am2150 Technical Reference Manual, Revision 1.0, August 17, 1993
  Am79C940 (MACE) Data Sheet, 1994
  Am79C90 (C-LANCE) Data Sheet, 1994
  Linux PCMCIA Programmer's Guide v1.17
  /usr/src/linux/net/inet/dev.c, Linux kernel 1.2.8

  Eric Mears, New Media Corporation
  Tom Pollard, New Media Corporation
  Dean Siasoyco, New Media Corporation
  Ken Lesniak, Silicon Graphics, Inc. <lesniak@boston.sgi.com>
  Donald Becker <becker@scyld.com>
  David Hinds <dahinds@users.sourceक्रमge.net>

  The Linux client driver is based on the 3c589_cs.c client driver by
  David Hinds.

  The Linux network driver outline is based on the 3c589_cs.c driver,
  the 8390.c driver, and the example skeleton.c kernel code, which are
  by Donald Becker.

  The Am2150 network driver hardware पूर्णांकerface code is based on the
  OS/9000 driver क्रम the New Media Ethernet LAN by Eric Mears.

  Special thanks क्रम testing and help in debugging this driver goes
  to Ken Lesniak.

-------------------------------------------------------------------------------
Driver Notes and Issues
-------------------------------------------------------------------------------

1. Developed on a Dell 320SLi
   PCMCIA Card Services 2.6.2
   Linux dell 1.2.10 #1 Thu Jun 29 20:23:41 PDT 1995 i386

2. rc.pcmcia may require loading pcmcia_core with io_speed=300:
   'insmod pcmcia_core.o io_speed=300'.
   This will aव्योम problems with fast प्रणालीs which causes rx_framecnt
   to वापस अक्रमom values.

3. If hot extraction करोes not work क्रम you, use 'ifconfig eth0 down'
   beक्रमe extraction.

4. There is a bad slow-करोwn problem in this driver.

5. Future: Multicast processing.  In the meanसमय, करो _not_ compile your
   kernel with multicast ip enabled.

-------------------------------------------------------------------------------
History
-------------------------------------------------------------------------------
Log: nmclan_cs.c,v
 * 2.5.75-ac1 2003/07/11 Alan Cox <alan@lxorguk.ukuu.org.uk>
 * Fixed hang on card eject as we probe it
 * Cleaned up to use new style locking.
 *
 * Revision 0.16  1995/07/01  06:42:17  rpao
 * Bug fix: nmclan_reset() called CardServices incorrectly.
 *
 * Revision 0.15  1995/05/24  08:09:47  rpao
 * Re-implement MULTI_TX dev->tbusy handling.
 *
 * Revision 0.14  1995/05/23  03:19:30  rpao
 * Added, in nmclan_config(), "tuple.Attributes = 0;".
 * Modअगरied MACE ID check to ignore chip revision level.
 * Aव्योम tx_मुक्त_frames race condition between _start_xmit and _पूर्णांकerrupt.
 *
 * Revision 0.13  1995/05/18  05:56:34  rpao
 * Statistics changes.
 * Bug fix: nmclan_reset did not enable TX and RX: call restore_multicast_list.
 * Bug fix: mace_पूर्णांकerrupt checks ~MACE_IMR_DEFAULT.  Fixes driver lockup.
 *
 * Revision 0.12  1995/05/14  00:12:23  rpao
 * Statistics overhaul.
 *

95/05/13 rpao	V0.10a
		Bug fix: MACE statistics counters used wrong I/O ports.
		Bug fix: mace_पूर्णांकerrupt() needed to allow statistics to be
		processed without RX or TX पूर्णांकerrupts pending.
95/05/11 rpao	V0.10
		Multiple transmit request processing.
		Modअगरied statistics to use MACE counters where possible.
95/05/10 rpao	V0.09 Bug fix: Must use IO_DATA_PATH_WIDTH_AUTO.
		*Released
95/05/10 rpao	V0.08
		Bug fix: Make all non-exported functions निजी by using
		अटल keyword.
		Bug fix: Test IntrCnt _beक्रमe_ पढ़ोing MACE_IR.
95/05/10 rpao	V0.07 Statistics.
95/05/09 rpao	V0.06 Fix rx_framecnt problem by addition of PCIC रुको states.

---------------------------------------------------------------------------- */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"nmclan_cs"

/* ----------------------------------------------------------------------------
Conditional Compilation Options
---------------------------------------------------------------------------- */

#घोषणा MULTI_TX			0
#घोषणा RESET_ON_TIMEOUT		1
#घोषणा TX_INTERRUPTABLE		1
#घोषणा RESET_XILINX			0

/* ----------------------------------------------------------------------------
Include Files
---------------------------------------------------------------------------- */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/bitops.h>

#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

/* ----------------------------------------------------------------------------
Defines
---------------------------------------------------------------------------- */

#घोषणा MACE_LADRF_LEN			8
					/* 8 bytes in Logical Address Filter */

/* Loop Control Defines */
#घोषणा MACE_MAX_IR_ITERATIONS		10
#घोषणा MACE_MAX_RX_ITERATIONS		12
	/*
	TBD: Dean brought this up, and I assumed the hardware would
	handle it:

	If MACE_MAX_RX_ITERATIONS is > 1, rx_framecnt may still be
	non-zero when the isr निकासs.  We may not get another पूर्णांकerrupt
	to process the reमुख्यing packets क्रम some समय.
	*/

/*
The Am2150 has a Xilinx XC3042 field programmable gate array (FPGA)
which manages the पूर्णांकerface between the MACE and the PCMCIA bus.  It
also includes buffer management क्रम the 32K x 8 SRAM to control up to
four transmit and 12 receive frames at a समय.
*/
#घोषणा AM2150_MAX_TX_FRAMES		4
#घोषणा AM2150_MAX_RX_FRAMES		12

/* Am2150 Ethernet Card I/O Mapping */
#घोषणा AM2150_RCV			0x00
#घोषणा AM2150_XMT			0x04
#घोषणा AM2150_XMT_SKIP			0x09
#घोषणा AM2150_RCV_NEXT			0x0A
#घोषणा AM2150_RCV_FRAME_COUNT		0x0B
#घोषणा AM2150_MACE_BANK		0x0C
#घोषणा AM2150_MACE_BASE		0x10

/* MACE Registers */
#घोषणा MACE_RCVFIFO			0
#घोषणा MACE_XMTFIFO			1
#घोषणा MACE_XMTFC			2
#घोषणा MACE_XMTFS			3
#घोषणा MACE_XMTRC			4
#घोषणा MACE_RCVFC			5
#घोषणा MACE_RCVFS			6
#घोषणा MACE_FIFOFC			7
#घोषणा MACE_IR				8
#घोषणा MACE_IMR			9
#घोषणा MACE_PR				10
#घोषणा MACE_BIUCC			11
#घोषणा MACE_FIFOCC			12
#घोषणा MACE_MACCC			13
#घोषणा MACE_PLSCC			14
#घोषणा MACE_PHYCC			15
#घोषणा MACE_CHIPIDL			16
#घोषणा MACE_CHIPIDH			17
#घोषणा MACE_IAC			18
/* Reserved */
#घोषणा MACE_LADRF			20
#घोषणा MACE_PADR			21
/* Reserved */
/* Reserved */
#घोषणा MACE_MPC			24
/* Reserved */
#घोषणा MACE_RNTPC			26
#घोषणा MACE_RCVCC			27
/* Reserved */
#घोषणा MACE_UTR			29
#घोषणा MACE_RTR1			30
#घोषणा MACE_RTR2			31

/* MACE Bit Masks */
#घोषणा MACE_XMTRC_EXDEF		0x80
#घोषणा MACE_XMTRC_XMTRC		0x0F

#घोषणा MACE_XMTFS_XMTSV		0x80
#घोषणा MACE_XMTFS_UFLO			0x40
#घोषणा MACE_XMTFS_LCOL			0x20
#घोषणा MACE_XMTFS_MORE			0x10
#घोषणा MACE_XMTFS_ONE			0x08
#घोषणा MACE_XMTFS_DEFER		0x04
#घोषणा MACE_XMTFS_LCAR			0x02
#घोषणा MACE_XMTFS_RTRY			0x01

#घोषणा MACE_RCVFS_RCVSTS		0xF000
#घोषणा MACE_RCVFS_OFLO			0x8000
#घोषणा MACE_RCVFS_CLSN			0x4000
#घोषणा MACE_RCVFS_FRAM			0x2000
#घोषणा MACE_RCVFS_FCS			0x1000

#घोषणा MACE_FIFOFC_RCVFC		0xF0
#घोषणा MACE_FIFOFC_XMTFC		0x0F

#घोषणा MACE_IR_JAB			0x80
#घोषणा MACE_IR_BABL			0x40
#घोषणा MACE_IR_CERR			0x20
#घोषणा MACE_IR_RCVCCO			0x10
#घोषणा MACE_IR_RNTPCO			0x08
#घोषणा MACE_IR_MPCO			0x04
#घोषणा MACE_IR_RCVINT			0x02
#घोषणा MACE_IR_XMTINT			0x01

#घोषणा MACE_MACCC_PROM			0x80
#घोषणा MACE_MACCC_DXMT2PD		0x40
#घोषणा MACE_MACCC_EMBA			0x20
#घोषणा MACE_MACCC_RESERVED		0x10
#घोषणा MACE_MACCC_DRCVPA		0x08
#घोषणा MACE_MACCC_DRCVBC		0x04
#घोषणा MACE_MACCC_ENXMT		0x02
#घोषणा MACE_MACCC_ENRCV		0x01

#घोषणा MACE_PHYCC_LNKFL		0x80
#घोषणा MACE_PHYCC_DLNKTST		0x40
#घोषणा MACE_PHYCC_REVPOL		0x20
#घोषणा MACE_PHYCC_DAPC			0x10
#घोषणा MACE_PHYCC_LRT			0x08
#घोषणा MACE_PHYCC_ASEL			0x04
#घोषणा MACE_PHYCC_RWAKE		0x02
#घोषणा MACE_PHYCC_AWAKE		0x01

#घोषणा MACE_IAC_ADDRCHG		0x80
#घोषणा MACE_IAC_PHYADDR		0x04
#घोषणा MACE_IAC_LOGADDR		0x02

#घोषणा MACE_UTR_RTRE			0x80
#घोषणा MACE_UTR_RTRD			0x40
#घोषणा MACE_UTR_RPA			0x20
#घोषणा MACE_UTR_FCOLL			0x10
#घोषणा MACE_UTR_RCVFCSE		0x08
#घोषणा MACE_UTR_LOOP_INCL_MENDEC	0x06
#घोषणा MACE_UTR_LOOP_NO_MENDEC		0x04
#घोषणा MACE_UTR_LOOP_EXTERNAL		0x02
#घोषणा MACE_UTR_LOOP_NONE		0x00
#घोषणा MACE_UTR_RESERVED		0x01

/* Switch MACE रेजिस्टर bank (only 0 and 1 are valid) */
#घोषणा MACEBANK(win_num) outb((win_num), ioaddr + AM2150_MACE_BANK)

#घोषणा MACE_IMR_DEFAULT \
  (0xFF - \
    ( \
      MACE_IR_CERR | \
      MACE_IR_RCVCCO | \
      MACE_IR_RNTPCO | \
      MACE_IR_MPCO | \
      MACE_IR_RCVINT | \
      MACE_IR_XMTINT \
    ) \
  )
#अघोषित MACE_IMR_DEFAULT
#घोषणा MACE_IMR_DEFAULT 0x00 /* New statistics handling: grab everything */

#घोषणा TX_TIMEOUT		((400*HZ)/1000)

/* ----------------------------------------------------------------------------
Type Definitions
---------------------------------------------------------------------------- */

प्रकार काष्ठा _mace_statistics अणु
    /* MACE_XMTFS */
    पूर्णांक xmtsv;
    पूर्णांक uflo;
    पूर्णांक lcol;
    पूर्णांक more;
    पूर्णांक one;
    पूर्णांक defer;
    पूर्णांक lcar;
    पूर्णांक rtry;

    /* MACE_XMTRC */
    पूर्णांक exdef;
    पूर्णांक xmtrc;

    /* RFS1--Receive Status (RCVSTS) */
    पूर्णांक oflo;
    पूर्णांक clsn;
    पूर्णांक fram;
    पूर्णांक fcs;

    /* RFS2--Runt Packet Count (RNTPC) */
    पूर्णांक rfs_rntpc;

    /* RFS3--Receive Collision Count (RCVCC) */
    पूर्णांक rfs_rcvcc;

    /* MACE_IR */
    पूर्णांक jab;
    पूर्णांक babl;
    पूर्णांक cerr;
    पूर्णांक rcvcco;
    पूर्णांक rntpco;
    पूर्णांक mpco;

    /* MACE_MPC */
    पूर्णांक mpc;

    /* MACE_RNTPC */
    पूर्णांक rntpc;

    /* MACE_RCVCC */
    पूर्णांक rcvcc;
पूर्ण mace_statistics;

प्रकार काष्ठा _mace_निजी अणु
	काष्ठा pcmcia_device	*p_dev;
    mace_statistics mace_stats; /* MACE chip statistics counters */

    /* restore_multicast_list() state variables */
    पूर्णांक multicast_ladrf[MACE_LADRF_LEN]; /* Logical address filter */
    पूर्णांक multicast_num_addrs;

    अक्षर tx_मुक्त_frames; /* Number of मुक्त transmit frame buffers */
    अक्षर tx_irq_disabled; /* MACE TX पूर्णांकerrupt disabled */

    spinlock_t bank_lock; /* Must be held अगर you step off bank 0 */
पूर्ण mace_निजी;

/* ----------------------------------------------------------------------------
Private Global Variables
---------------------------------------------------------------------------- */

अटल स्थिर अक्षर *अगर_names[]=अणु
    "Auto", "10baseT", "BNC",
पूर्ण;

/* ----------------------------------------------------------------------------
Parameters
	These are the parameters that can be set during loading with
	'insmod'.
---------------------------------------------------------------------------- */

MODULE_DESCRIPTION("New Media PCMCIA ethernet driver");
MODULE_LICENSE("GPL");

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0)

/* 0=स्वतः, 1=10baseT, 2 = 10base2, शेष=स्वतः */
INT_MODULE_PARM(अगर_port, 0);


/* ----------------------------------------------------------------------------
Function Prototypes
---------------------------------------------------------------------------- */

अटल पूर्णांक nmclan_config(काष्ठा pcmcia_device *link);
अटल व्योम nmclan_release(काष्ठा pcmcia_device *link);

अटल व्योम nmclan_reset(काष्ठा net_device *dev);
अटल पूर्णांक mace_config(काष्ठा net_device *dev, काष्ठा अगरmap *map);
अटल पूर्णांक mace_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक mace_बंद(काष्ठा net_device *dev);
अटल netdev_tx_t mace_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev);
अटल व्योम mace_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल irqवापस_t mace_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल काष्ठा net_device_stats *mace_get_stats(काष्ठा net_device *dev);
अटल पूर्णांक mace_rx(काष्ठा net_device *dev, अचिन्हित अक्षर RxCnt);
अटल व्योम restore_multicast_list(काष्ठा net_device *dev);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;


अटल व्योम nmclan_detach(काष्ठा pcmcia_device *p_dev);

अटल स्थिर काष्ठा net_device_ops mace_netdev_ops = अणु
	.nकरो_खोलो		= mace_खोलो,
	.nकरो_stop		= mace_बंद,
	.nकरो_start_xmit		= mace_start_xmit,
	.nकरो_tx_समयout		= mace_tx_समयout,
	.nकरो_set_config		= mace_config,
	.nकरो_get_stats		= mace_get_stats,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक nmclan_probe(काष्ठा pcmcia_device *link)
अणु
    mace_निजी *lp;
    काष्ठा net_device *dev;

    dev_dbg(&link->dev, "nmclan_attach()\n");

    /* Create new ethernet device */
    dev = alloc_etherdev(माप(mace_निजी));
    अगर (!dev)
	    वापस -ENOMEM;
    lp = netdev_priv(dev);
    lp->p_dev = link;
    link->priv = dev;

    spin_lock_init(&lp->bank_lock);
    link->resource[0]->end = 32;
    link->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
    link->config_flags |= CONF_ENABLE_IRQ;
    link->config_index = 1;
    link->config_regs = PRESENT_OPTION;

    lp->tx_मुक्त_frames=AM2150_MAX_TX_FRAMES;

    dev->netdev_ops = &mace_netdev_ops;
    dev->ethtool_ops = &netdev_ethtool_ops;
    dev->watchकरोg_समयo = TX_TIMEOUT;

    वापस nmclan_config(link);
पूर्ण /* nmclan_attach */

अटल व्योम nmclan_detach(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;

    dev_dbg(&link->dev, "nmclan_detach\n");

    unरेजिस्टर_netdev(dev);

    nmclan_release(link);

    मुक्त_netdev(dev);
पूर्ण /* nmclan_detach */

/* ----------------------------------------------------------------------------
mace_पढ़ो
	Reads a MACE रेजिस्टर.  This is bank independent; however, the
	caller must ensure that this call is not पूर्णांकerruptable.  We are
	assuming that during normal operation, the MACE is always in
	bank 0.
---------------------------------------------------------------------------- */
अटल पूर्णांक mace_पढ़ो(mace_निजी *lp, अचिन्हित पूर्णांक ioaddr, पूर्णांक reg)
अणु
  पूर्णांक data = 0xFF;
  अचिन्हित दीर्घ flags;

  चयन (reg >> 4) अणु
    हाल 0: /* रेजिस्टर 0-15 */
      data = inb(ioaddr + AM2150_MACE_BASE + reg);
      अवरोध;
    हाल 1: /* रेजिस्टर 16-31 */
      spin_lock_irqsave(&lp->bank_lock, flags);
      MACEBANK(1);
      data = inb(ioaddr + AM2150_MACE_BASE + (reg & 0x0F));
      MACEBANK(0);
      spin_unlock_irqrestore(&lp->bank_lock, flags);
      अवरोध;
  पूर्ण
  वापस data & 0xFF;
पूर्ण /* mace_पढ़ो */

/* ----------------------------------------------------------------------------
mace_ग_लिखो
	Writes to a MACE रेजिस्टर.  This is bank independent; however,
	the caller must ensure that this call is not पूर्णांकerruptable.  We
	are assuming that during normal operation, the MACE is always in
	bank 0.
---------------------------------------------------------------------------- */
अटल व्योम mace_ग_लिखो(mace_निजी *lp, अचिन्हित पूर्णांक ioaddr, पूर्णांक reg,
		       पूर्णांक data)
अणु
  अचिन्हित दीर्घ flags;

  चयन (reg >> 4) अणु
    हाल 0: /* रेजिस्टर 0-15 */
      outb(data & 0xFF, ioaddr + AM2150_MACE_BASE + reg);
      अवरोध;
    हाल 1: /* रेजिस्टर 16-31 */
      spin_lock_irqsave(&lp->bank_lock, flags);
      MACEBANK(1);
      outb(data & 0xFF, ioaddr + AM2150_MACE_BASE + (reg & 0x0F));
      MACEBANK(0);
      spin_unlock_irqrestore(&lp->bank_lock, flags);
      अवरोध;
  पूर्ण
पूर्ण /* mace_ग_लिखो */

/* ----------------------------------------------------------------------------
mace_init
	Resets the MACE chip.
---------------------------------------------------------------------------- */
अटल पूर्णांक mace_init(mace_निजी *lp, अचिन्हित पूर्णांक ioaddr, अक्षर *enet_addr)
अणु
  पूर्णांक i;
  पूर्णांक ct = 0;

  /* MACE Software reset */
  mace_ग_लिखो(lp, ioaddr, MACE_BIUCC, 1);
  जबतक (mace_पढ़ो(lp, ioaddr, MACE_BIUCC) & 0x01) अणु
    /* Wait क्रम reset bit to be cleared स्वतःmatically after <= 200ns */;
    अगर(++ct > 500)
    अणु
	pr_err("reset failed, card removed?\n");
    	वापस -1;
    पूर्ण
    udelay(1);
  पूर्ण
  mace_ग_लिखो(lp, ioaddr, MACE_BIUCC, 0);

  /* The Am2150 requires that the MACE FIFOs operate in burst mode. */
  mace_ग_लिखो(lp, ioaddr, MACE_FIFOCC, 0x0F);

  mace_ग_लिखो(lp,ioaddr, MACE_RCVFC, 0); /* Disable Auto Strip Receive */
  mace_ग_लिखो(lp, ioaddr, MACE_IMR, 0xFF); /* Disable all पूर्णांकerrupts until _खोलो */

  /*
   * Bit 2-1 PORTSEL[1-0] Port Select.
   * 00 AUI/10Base-2
   * 01 10Base-T
   * 10 DAI Port (reserved in Am2150)
   * 11 GPSI
   * For this card, only the first two are valid.
   * So, PLSCC should be set to
   * 0x00 क्रम 10Base-2
   * 0x02 क्रम 10Base-T
   * Or just set ASEL in PHYCC below!
   */
  चयन (अगर_port) अणु
    हाल 1:
      mace_ग_लिखो(lp, ioaddr, MACE_PLSCC, 0x02);
      अवरोध;
    हाल 2:
      mace_ग_लिखो(lp, ioaddr, MACE_PLSCC, 0x00);
      अवरोध;
    शेष:
      mace_ग_लिखो(lp, ioaddr, MACE_PHYCC, /* ASEL */ 4);
      /* ASEL Auto Select.  When set, the PORTSEL[1-0] bits are overridden,
	 and the MACE device will स्वतःmatically select the operating media
	 पूर्णांकerface port. */
      अवरोध;
  पूर्ण

  mace_ग_लिखो(lp, ioaddr, MACE_IAC, MACE_IAC_ADDRCHG | MACE_IAC_PHYADDR);
  /* Poll ADDRCHG bit */
  ct = 0;
  जबतक (mace_पढ़ो(lp, ioaddr, MACE_IAC) & MACE_IAC_ADDRCHG)
  अणु
  	अगर(++ ct > 500)
  	अणु
		pr_err("ADDRCHG timeout, card removed?\n");
  		वापस -1;
  	पूर्ण
  पूर्ण
  /* Set PADR रेजिस्टर */
  क्रम (i = 0; i < ETH_ALEN; i++)
    mace_ग_लिखो(lp, ioaddr, MACE_PADR, enet_addr[i]);

  /* MAC Configuration Control Register should be written last */
  /* Let set_multicast_list set this. */
  /* mace_ग_लिखो(lp, ioaddr, MACE_MACCC, MACE_MACCC_ENXMT | MACE_MACCC_ENRCV); */
  mace_ग_लिखो(lp, ioaddr, MACE_MACCC, 0x00);
  वापस 0;
पूर्ण /* mace_init */

अटल पूर्णांक nmclan_config(काष्ठा pcmcia_device *link)
अणु
  काष्ठा net_device *dev = link->priv;
  mace_निजी *lp = netdev_priv(dev);
  u8 *buf;
  माप_प्रकार len;
  पूर्णांक i, ret;
  अचिन्हित पूर्णांक ioaddr;

  dev_dbg(&link->dev, "nmclan_config\n");

  link->io_lines = 5;
  ret = pcmcia_request_io(link);
  अगर (ret)
	  जाओ failed;
  ret = pcmcia_request_irq(link, mace_पूर्णांकerrupt);
  अगर (ret)
	  जाओ failed;
  ret = pcmcia_enable_device(link);
  अगर (ret)
	  जाओ failed;

  dev->irq = link->irq;
  dev->base_addr = link->resource[0]->start;

  ioaddr = dev->base_addr;

  /* Read the ethernet address from the CIS. */
  len = pcmcia_get_tuple(link, 0x80, &buf);
  अगर (!buf || len < ETH_ALEN) अणु
	  kमुक्त(buf);
	  जाओ failed;
  पूर्ण
  स_नकल(dev->dev_addr, buf, ETH_ALEN);
  kमुक्त(buf);

  /* Verअगरy configuration by पढ़ोing the MACE ID. */
  अणु
    अक्षर sig[2];

    sig[0] = mace_पढ़ो(lp, ioaddr, MACE_CHIPIDL);
    sig[1] = mace_पढ़ो(lp, ioaddr, MACE_CHIPIDH);
    अगर ((sig[0] == 0x40) && ((sig[1] & 0x0F) == 0x09)) अणु
      dev_dbg(&link->dev, "nmclan_cs configured: mace id=%x %x\n",
	    sig[0], sig[1]);
    पूर्ण अन्यथा अणु
      pr_notice("mace id not found: %x %x should be 0x40 0x?9\n",
		sig[0], sig[1]);
      वापस -ENODEV;
    पूर्ण
  पूर्ण

  अगर(mace_init(lp, ioaddr, dev->dev_addr) == -1)
  	जाओ failed;

  /* The अगर_port symbol can be set when the module is loaded */
  अगर (अगर_port <= 2)
    dev->अगर_port = अगर_port;
  अन्यथा
    pr_notice("invalid if_port requested\n");

  SET_NETDEV_DEV(dev, &link->dev);

  i = रेजिस्टर_netdev(dev);
  अगर (i != 0) अणु
    pr_notice("register_netdev() failed\n");
    जाओ failed;
  पूर्ण

  netdev_info(dev, "nmclan: port %#3lx, irq %d, %s port, hw_addr %pM\n",
	      dev->base_addr, dev->irq, अगर_names[dev->अगर_port], dev->dev_addr);
  वापस 0;

failed:
	nmclan_release(link);
	वापस -ENODEV;
पूर्ण /* nmclan_config */

अटल व्योम nmclan_release(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "nmclan_release\n");
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक nmclan_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक nmclan_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो) अणु
		nmclan_reset(dev);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण


/* ----------------------------------------------------------------------------
nmclan_reset
	Reset and restore all of the Xilinx and MACE रेजिस्टरs.
---------------------------------------------------------------------------- */
अटल व्योम nmclan_reset(काष्ठा net_device *dev)
अणु
  mace_निजी *lp = netdev_priv(dev);

#अगर RESET_XILINX
  काष्ठा pcmcia_device *link = &lp->link;
  u8 OrigCorValue;

  /* Save original COR value */
  pcmcia_पढ़ो_config_byte(link, CISREG_COR, &OrigCorValue);

  /* Reset Xilinx */
  dev_dbg(&link->dev, "nmclan_reset: OrigCorValue=0x%x, resetting...\n",
	OrigCorValue);
  pcmcia_ग_लिखो_config_byte(link, CISREG_COR, COR_SOFT_RESET);
  /* Need to रुको क्रम 20 ms क्रम PCMCIA to finish reset. */

  /* Restore original COR configuration index */
  pcmcia_ग_लिखो_config_byte(link, CISREG_COR,
			  (COR_LEVEL_REQ | (OrigCorValue & COR_CONFIG_MASK)));
  /* Xilinx is now completely reset aदीर्घ with the MACE chip. */
  lp->tx_मुक्त_frames=AM2150_MAX_TX_FRAMES;

#पूर्ण_अगर /* #अगर RESET_XILINX */

  /* Xilinx is now completely reset aदीर्घ with the MACE chip. */
  lp->tx_मुक्त_frames=AM2150_MAX_TX_FRAMES;

  /* Reinitialize the MACE chip क्रम operation. */
  mace_init(lp, dev->base_addr, dev->dev_addr);
  mace_ग_लिखो(lp, dev->base_addr, MACE_IMR, MACE_IMR_DEFAULT);

  /* Restore the multicast list and enable TX and RX. */
  restore_multicast_list(dev);
पूर्ण /* nmclan_reset */

/* ----------------------------------------------------------------------------
mace_config
	[Someone tell me what this is supposed to करो?  Is अगर_port a defined
	standard?  If so, there should be defines to indicate 1=10Base-T,
	2=10Base-2, etc. including limited स्वतःmatic detection.]
---------------------------------------------------------------------------- */
अटल पूर्णांक mace_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)
अणु
  अगर ((map->port != (u_अक्षर)(-1)) && (map->port != dev->अगर_port)) अणु
    अगर (map->port <= 2) अणु
      dev->अगर_port = map->port;
      netdev_info(dev, "switched to %s port\n", अगर_names[dev->अगर_port]);
    पूर्ण अन्यथा
      वापस -EINVAL;
  पूर्ण
  वापस 0;
पूर्ण /* mace_config */

/* ----------------------------------------------------------------------------
mace_खोलो
	Open device driver.
---------------------------------------------------------------------------- */
अटल पूर्णांक mace_खोलो(काष्ठा net_device *dev)
अणु
  अचिन्हित पूर्णांक ioaddr = dev->base_addr;
  mace_निजी *lp = netdev_priv(dev);
  काष्ठा pcmcia_device *link = lp->p_dev;

  अगर (!pcmcia_dev_present(link))
    वापस -ENODEV;

  link->खोलो++;

  MACEBANK(0);

  netअगर_start_queue(dev);
  nmclan_reset(dev);

  वापस 0; /* Always succeed */
पूर्ण /* mace_खोलो */

/* ----------------------------------------------------------------------------
mace_बंद
	Closes device driver.
---------------------------------------------------------------------------- */
अटल पूर्णांक mace_बंद(काष्ठा net_device *dev)
अणु
  अचिन्हित पूर्णांक ioaddr = dev->base_addr;
  mace_निजी *lp = netdev_priv(dev);
  काष्ठा pcmcia_device *link = lp->p_dev;

  dev_dbg(&link->dev, "%s: shutting down ethercard.\n", dev->name);

  /* Mask off all पूर्णांकerrupts from the MACE chip. */
  outb(0xFF, ioaddr + AM2150_MACE_BASE + MACE_IMR);

  link->खोलो--;
  netअगर_stop_queue(dev);

  वापस 0;
पूर्ण /* mace_बंद */

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	snम_लिखो(info->bus_info, माप(info->bus_info),
		"PCMCIA 0x%lx", dev->base_addr);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
पूर्ण;

/* ----------------------------------------------------------------------------
mace_start_xmit
	This routine begins the packet transmit function.  When completed,
	it will generate a transmit पूर्णांकerrupt.

	According to /usr/src/linux/net/inet/dev.c, अगर _start_xmit
	वापसs 0, the "packet is now solely the responsibility of the
	driver."  If _start_xmit returns non-zero, the "transmission
	failed, put skb back पूर्णांकo a list."
---------------------------------------------------------------------------- */

अटल व्योम mace_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
  mace_निजी *lp = netdev_priv(dev);
  काष्ठा pcmcia_device *link = lp->p_dev;

  netdev_notice(dev, "transmit timed out -- ");
#अगर RESET_ON_TIMEOUT
  pr_cont("resetting card\n");
  pcmcia_reset_card(link->socket);
#अन्यथा /* #अगर RESET_ON_TIMEOUT */
  pr_cont("NOT resetting card\n");
#पूर्ण_अगर /* #अगर RESET_ON_TIMEOUT */
  netअगर_trans_update(dev); /* prevent tx समयout */
  netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t mace_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
  mace_निजी *lp = netdev_priv(dev);
  अचिन्हित पूर्णांक ioaddr = dev->base_addr;

  netअगर_stop_queue(dev);

  pr_debug("%s: mace_start_xmit(length = %ld) called.\n",
	dev->name, (दीर्घ)skb->len);

#अगर (!TX_INTERRUPTABLE)
  /* Disable MACE TX पूर्णांकerrupts. */
  outb(MACE_IMR_DEFAULT | MACE_IR_XMTINT,
    ioaddr + AM2150_MACE_BASE + MACE_IMR);
  lp->tx_irq_disabled=1;
#पूर्ण_अगर /* #अगर (!TX_INTERRUPTABLE) */

  अणु
    /* This block must not be पूर्णांकerrupted by another transmit request!
       mace_tx_समयout will take care of समयr-based retransmissions from
       the upper layers.  The पूर्णांकerrupt handler is guaranteed never to
       service a transmit पूर्णांकerrupt जबतक we are in here.
    */

    dev->stats.tx_bytes += skb->len;
    lp->tx_मुक्त_frames--;

    /* WARNING: Write the _exact_ number of bytes written in the header! */
    /* Put out the word header [must be an outw()] . . . */
    outw(skb->len, ioaddr + AM2150_XMT);
    /* . . . and the packet [may be any combination of outw() and outb()] */
    outsw(ioaddr + AM2150_XMT, skb->data, skb->len >> 1);
    अगर (skb->len & 1) अणु
      /* Odd byte transfer */
      outb(skb->data[skb->len-1], ioaddr + AM2150_XMT);
    पूर्ण

#अगर MULTI_TX
    अगर (lp->tx_मुक्त_frames > 0)
      netअगर_start_queue(dev);
#पूर्ण_अगर /* #अगर MULTI_TX */
  पूर्ण

#अगर (!TX_INTERRUPTABLE)
  /* Re-enable MACE TX पूर्णांकerrupts. */
  lp->tx_irq_disabled=0;
  outb(MACE_IMR_DEFAULT, ioaddr + AM2150_MACE_BASE + MACE_IMR);
#पूर्ण_अगर /* #अगर (!TX_INTERRUPTABLE) */

  dev_kमुक्त_skb(skb);

  वापस NETDEV_TX_OK;
पूर्ण /* mace_start_xmit */

/* ----------------------------------------------------------------------------
mace_पूर्णांकerrupt
	The पूर्णांकerrupt handler.
---------------------------------------------------------------------------- */
अटल irqवापस_t mace_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
  काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
  mace_निजी *lp = netdev_priv(dev);
  अचिन्हित पूर्णांक ioaddr;
  पूर्णांक status;
  पूर्णांक IntrCnt = MACE_MAX_IR_ITERATIONS;

  अगर (dev == शून्य) अणु
    pr_debug("mace_interrupt(): irq 0x%X for unknown device.\n",
	  irq);
    वापस IRQ_NONE;
  पूर्ण

  ioaddr = dev->base_addr;

  अगर (lp->tx_irq_disabled) अणु
    स्थिर अक्षर *msg;
    अगर (lp->tx_irq_disabled)
      msg = "Interrupt with tx_irq_disabled";
    अन्यथा
      msg = "Re-entering the interrupt handler";
    netdev_notice(dev, "%s [isr=%02X, imr=%02X]\n",
		  msg,
		  inb(ioaddr + AM2150_MACE_BASE + MACE_IR),
		  inb(ioaddr + AM2150_MACE_BASE + MACE_IMR));
    /* WARNING: MACE_IR has been पढ़ो! */
    वापस IRQ_NONE;
  पूर्ण

  अगर (!netअगर_device_present(dev)) अणु
    netdev_dbg(dev, "interrupt from dead card\n");
    वापस IRQ_NONE;
  पूर्ण

  करो अणु
    /* WARNING: MACE_IR is a READ/CLEAR port! */
    status = inb(ioaddr + AM2150_MACE_BASE + MACE_IR);
    अगर (!(status & ~MACE_IMR_DEFAULT) && IntrCnt == MACE_MAX_IR_ITERATIONS)
      वापस IRQ_NONE;

    pr_debug("mace_interrupt: irq 0x%X status 0x%X.\n", irq, status);

    अगर (status & MACE_IR_RCVINT) अणु
      mace_rx(dev, MACE_MAX_RX_ITERATIONS);
    पूर्ण

    अगर (status & MACE_IR_XMTINT) अणु
      अचिन्हित अक्षर fअगरofc;
      अचिन्हित अक्षर xmtrc;
      अचिन्हित अक्षर xmtfs;

      fअगरofc = inb(ioaddr + AM2150_MACE_BASE + MACE_FIFOFC);
      अगर ((fअगरofc & MACE_FIFOFC_XMTFC)==0) अणु
	dev->stats.tx_errors++;
	outb(0xFF, ioaddr + AM2150_XMT_SKIP);
      पूर्ण

      /* Transmit Retry Count (XMTRC, reg 4) */
      xmtrc = inb(ioaddr + AM2150_MACE_BASE + MACE_XMTRC);
      अगर (xmtrc & MACE_XMTRC_EXDEF) lp->mace_stats.exdef++;
      lp->mace_stats.xmtrc += (xmtrc & MACE_XMTRC_XMTRC);

      अगर (
        (xmtfs = inb(ioaddr + AM2150_MACE_BASE + MACE_XMTFS)) &
        MACE_XMTFS_XMTSV /* Transmit Status Valid */
      ) अणु
	lp->mace_stats.xmtsv++;

	अगर (xmtfs & ~MACE_XMTFS_XMTSV) अणु
	  अगर (xmtfs & MACE_XMTFS_UFLO) अणु
	    /* Underflow.  Indicates that the Transmit FIFO emptied beक्रमe
	       the end of frame was reached. */
	    lp->mace_stats.uflo++;
	  पूर्ण
	  अगर (xmtfs & MACE_XMTFS_LCOL) अणु
	    /* Late Collision */
	    lp->mace_stats.lcol++;
	  पूर्ण
	  अगर (xmtfs & MACE_XMTFS_MORE) अणु
	    /* MORE than one retry was needed */
	    lp->mace_stats.more++;
	  पूर्ण
	  अगर (xmtfs & MACE_XMTFS_ONE) अणु
	    /* Exactly ONE retry occurred */
	    lp->mace_stats.one++;
	  पूर्ण
	  अगर (xmtfs & MACE_XMTFS_DEFER) अणु
	    /* Transmission was defered */
	    lp->mace_stats.defer++;
	  पूर्ण
	  अगर (xmtfs & MACE_XMTFS_LCAR) अणु
	    /* Loss of carrier */
	    lp->mace_stats.lcar++;
	  पूर्ण
	  अगर (xmtfs & MACE_XMTFS_RTRY) अणु
	    /* Retry error: transmit पातed after 16 attempts */
	    lp->mace_stats.rtry++;
	  पूर्ण
        पूर्ण /* अगर (xmtfs & ~MACE_XMTFS_XMTSV) */

      पूर्ण /* अगर (xmtfs & MACE_XMTFS_XMTSV) */

      dev->stats.tx_packets++;
      lp->tx_मुक्त_frames++;
      netअगर_wake_queue(dev);
    पूर्ण /* अगर (status & MACE_IR_XMTINT) */

    अगर (status & ~MACE_IMR_DEFAULT & ~MACE_IR_RCVINT & ~MACE_IR_XMTINT) अणु
      अगर (status & MACE_IR_JAB) अणु
        /* Jabber Error.  Excessive transmit duration (20-150ms). */
        lp->mace_stats.jab++;
      पूर्ण
      अगर (status & MACE_IR_BABL) अणु
        /* Babble Error.  >1518 bytes transmitted. */
        lp->mace_stats.babl++;
      पूर्ण
      अगर (status & MACE_IR_CERR) अणु
	/* Collision Error.  CERR indicates the असलence of the
	   Signal Quality Error Test message after a packet
	   transmission. */
        lp->mace_stats.cerr++;
      पूर्ण
      अगर (status & MACE_IR_RCVCCO) अणु
        /* Receive Collision Count Overflow; */
        lp->mace_stats.rcvcco++;
      पूर्ण
      अगर (status & MACE_IR_RNTPCO) अणु
        /* Runt Packet Count Overflow */
        lp->mace_stats.rntpco++;
      पूर्ण
      अगर (status & MACE_IR_MPCO) अणु
        /* Missed Packet Count Overflow */
        lp->mace_stats.mpco++;
      पूर्ण
    पूर्ण /* अगर (status & ~MACE_IMR_DEFAULT & ~MACE_IR_RCVINT & ~MACE_IR_XMTINT) */

  पूर्ण जबतक ((status & ~MACE_IMR_DEFAULT) && (--IntrCnt));

  वापस IRQ_HANDLED;
पूर्ण /* mace_पूर्णांकerrupt */

/* ----------------------------------------------------------------------------
mace_rx
	Receives packets.
---------------------------------------------------------------------------- */
अटल पूर्णांक mace_rx(काष्ठा net_device *dev, अचिन्हित अक्षर RxCnt)
अणु
  mace_निजी *lp = netdev_priv(dev);
  अचिन्हित पूर्णांक ioaddr = dev->base_addr;
  अचिन्हित अक्षर rx_framecnt;
  अचिन्हित लघु rx_status;

  जबतक (
    ((rx_framecnt = inb(ioaddr + AM2150_RCV_FRAME_COUNT)) > 0) &&
    (rx_framecnt <= 12) && /* rx_framecnt==0xFF अगर card is extracted. */
    (RxCnt--)
  ) अणु
    rx_status = inw(ioaddr + AM2150_RCV);

    pr_debug("%s: in mace_rx(), framecnt 0x%X, rx_status"
	  " 0x%X.\n", dev->name, rx_framecnt, rx_status);

    अगर (rx_status & MACE_RCVFS_RCVSTS) अणु /* Error, update stats. */
      dev->stats.rx_errors++;
      अगर (rx_status & MACE_RCVFS_OFLO) अणु
        lp->mace_stats.oflo++;
      पूर्ण
      अगर (rx_status & MACE_RCVFS_CLSN) अणु
        lp->mace_stats.clsn++;
      पूर्ण
      अगर (rx_status & MACE_RCVFS_FRAM) अणु
	lp->mace_stats.fram++;
      पूर्ण
      अगर (rx_status & MACE_RCVFS_FCS) अणु
        lp->mace_stats.fcs++;
      पूर्ण
    पूर्ण अन्यथा अणु
      लघु pkt_len = (rx_status & ~MACE_RCVFS_RCVSTS) - 4;
        /* Auto Strip is off, always subtract 4 */
      काष्ठा sk_buff *skb;

      lp->mace_stats.rfs_rntpc += inb(ioaddr + AM2150_RCV);
        /* runt packet count */
      lp->mace_stats.rfs_rcvcc += inb(ioaddr + AM2150_RCV);
        /* rcv collision count */

      pr_debug("    receiving packet size 0x%X rx_status"
	    " 0x%X.\n", pkt_len, rx_status);

      skb = netdev_alloc_skb(dev, pkt_len + 2);

      अगर (skb != शून्य) अणु
	skb_reserve(skb, 2);
	insw(ioaddr + AM2150_RCV, skb_put(skb, pkt_len), pkt_len>>1);
	अगर (pkt_len & 1)
	    *(skb_tail_poपूर्णांकer(skb) - 1) = inb(ioaddr + AM2150_RCV);
	skb->protocol = eth_type_trans(skb, dev);

	netअगर_rx(skb); /* Send the packet to the upper (protocol) layers. */

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += pkt_len;
	outb(0xFF, ioaddr + AM2150_RCV_NEXT); /* skip to next frame */
	जारी;
      पूर्ण अन्यथा अणु
	pr_debug("%s: couldn't allocate a sk_buff of size"
	      " %d.\n", dev->name, pkt_len);
	dev->stats.rx_dropped++;
      पूर्ण
    पूर्ण
    outb(0xFF, ioaddr + AM2150_RCV_NEXT); /* skip to next frame */
  पूर्ण /* जबतक */

  वापस 0;
पूर्ण /* mace_rx */

/* ----------------------------------------------------------------------------
pr_linux_stats
---------------------------------------------------------------------------- */
अटल व्योम pr_linux_stats(काष्ठा net_device_stats *pstats)
अणु
  pr_debug("pr_linux_stats\n");
  pr_debug(" rx_packets=%-7ld        tx_packets=%ld\n",
	(दीर्घ)pstats->rx_packets, (दीर्घ)pstats->tx_packets);
  pr_debug(" rx_errors=%-7ld         tx_errors=%ld\n",
	(दीर्घ)pstats->rx_errors, (दीर्घ)pstats->tx_errors);
  pr_debug(" rx_dropped=%-7ld        tx_dropped=%ld\n",
	(दीर्घ)pstats->rx_dropped, (दीर्घ)pstats->tx_dropped);
  pr_debug(" multicast=%-7ld         collisions=%ld\n",
	(दीर्घ)pstats->multicast, (दीर्घ)pstats->collisions);

  pr_debug(" rx_length_errors=%-7ld  rx_over_errors=%ld\n",
	(दीर्घ)pstats->rx_length_errors, (दीर्घ)pstats->rx_over_errors);
  pr_debug(" rx_crc_errors=%-7ld     rx_frame_errors=%ld\n",
	(दीर्घ)pstats->rx_crc_errors, (दीर्घ)pstats->rx_frame_errors);
  pr_debug(" rx_fifo_errors=%-7ld    rx_missed_errors=%ld\n",
	(दीर्घ)pstats->rx_fअगरo_errors, (दीर्घ)pstats->rx_missed_errors);

  pr_debug(" tx_aborted_errors=%-7ld tx_carrier_errors=%ld\n",
	(दीर्घ)pstats->tx_पातed_errors, (दीर्घ)pstats->tx_carrier_errors);
  pr_debug(" tx_fifo_errors=%-7ld    tx_heartbeat_errors=%ld\n",
	(दीर्घ)pstats->tx_fअगरo_errors, (दीर्घ)pstats->tx_heartbeat_errors);
  pr_debug(" tx_window_errors=%ld\n",
	(दीर्घ)pstats->tx_winकरोw_errors);
पूर्ण /* pr_linux_stats */

/* ----------------------------------------------------------------------------
pr_mace_stats
---------------------------------------------------------------------------- */
अटल व्योम pr_mace_stats(mace_statistics *pstats)
अणु
  pr_debug("pr_mace_stats\n");

  pr_debug(" xmtsv=%-7d             uflo=%d\n",
	pstats->xmtsv, pstats->uflo);
  pr_debug(" lcol=%-7d              more=%d\n",
	pstats->lcol, pstats->more);
  pr_debug(" one=%-7d               defer=%d\n",
	pstats->one, pstats->defer);
  pr_debug(" lcar=%-7d              rtry=%d\n",
	pstats->lcar, pstats->rtry);

  /* MACE_XMTRC */
  pr_debug(" exdef=%-7d             xmtrc=%d\n",
	pstats->exdef, pstats->xmtrc);

  /* RFS1--Receive Status (RCVSTS) */
  pr_debug(" oflo=%-7d              clsn=%d\n",
	pstats->oflo, pstats->clsn);
  pr_debug(" fram=%-7d              fcs=%d\n",
	pstats->fram, pstats->fcs);

  /* RFS2--Runt Packet Count (RNTPC) */
  /* RFS3--Receive Collision Count (RCVCC) */
  pr_debug(" rfs_rntpc=%-7d         rfs_rcvcc=%d\n",
	pstats->rfs_rntpc, pstats->rfs_rcvcc);

  /* MACE_IR */
  pr_debug(" jab=%-7d               babl=%d\n",
	pstats->jab, pstats->babl);
  pr_debug(" cerr=%-7d              rcvcco=%d\n",
	pstats->cerr, pstats->rcvcco);
  pr_debug(" rntpco=%-7d            mpco=%d\n",
	pstats->rntpco, pstats->mpco);

  /* MACE_MPC */
  pr_debug(" mpc=%d\n", pstats->mpc);

  /* MACE_RNTPC */
  pr_debug(" rntpc=%d\n", pstats->rntpc);

  /* MACE_RCVCC */
  pr_debug(" rcvcc=%d\n", pstats->rcvcc);

पूर्ण /* pr_mace_stats */

/* ----------------------------------------------------------------------------
update_stats
	Update statistics.  We change to रेजिस्टर winकरोw 1, so this
	should be run single-thपढ़ोed अगर the device is active. This is
	expected to be a rare operation, and it's simpler क्रम the rest
	of the driver to assume that winकरोw 0 is always valid rather
	than use a special winकरोw-state variable.

	oflo & uflo should _never_ occur since it would mean the Xilinx
	was not able to transfer data between the MACE FIFO and the
	card's SRAM fast enough.  If this happens, something is
	seriously wrong with the hardware.
---------------------------------------------------------------------------- */
अटल व्योम update_stats(अचिन्हित पूर्णांक ioaddr, काष्ठा net_device *dev)
अणु
  mace_निजी *lp = netdev_priv(dev);

  lp->mace_stats.rcvcc += mace_पढ़ो(lp, ioaddr, MACE_RCVCC);
  lp->mace_stats.rntpc += mace_पढ़ो(lp, ioaddr, MACE_RNTPC);
  lp->mace_stats.mpc += mace_पढ़ो(lp, ioaddr, MACE_MPC);
  /* At this poपूर्णांक, mace_stats is fully updated क्रम this call.
     We may now update the netdev stats. */

  /* The MACE has no equivalent क्रम netdev stats field which are commented
     out. */

  /* dev->stats.multicast; */
  dev->stats.collisions =
    lp->mace_stats.rcvcco * 256 + lp->mace_stats.rcvcc;
    /* Collision: The MACE may retry sending a packet 15 बार
       beक्रमe giving up.  The retry count is in XMTRC.
       Does each retry स्थिरitute a collision?
       If so, why करोesn't the RCVCC record these collisions? */

  /* detailed rx_errors: */
  dev->stats.rx_length_errors =
    lp->mace_stats.rntpco * 256 + lp->mace_stats.rntpc;
  /* dev->stats.rx_over_errors */
  dev->stats.rx_crc_errors = lp->mace_stats.fcs;
  dev->stats.rx_frame_errors = lp->mace_stats.fram;
  dev->stats.rx_fअगरo_errors = lp->mace_stats.oflo;
  dev->stats.rx_missed_errors =
    lp->mace_stats.mpco * 256 + lp->mace_stats.mpc;

  /* detailed tx_errors */
  dev->stats.tx_पातed_errors = lp->mace_stats.rtry;
  dev->stats.tx_carrier_errors = lp->mace_stats.lcar;
    /* LCAR usually results from bad cabling. */
  dev->stats.tx_fअगरo_errors = lp->mace_stats.uflo;
  dev->stats.tx_heartbeat_errors = lp->mace_stats.cerr;
  /* dev->stats.tx_winकरोw_errors; */
पूर्ण /* update_stats */

/* ----------------------------------------------------------------------------
mace_get_stats
	Gathers ethernet statistics from the MACE chip.
---------------------------------------------------------------------------- */
अटल काष्ठा net_device_stats *mace_get_stats(काष्ठा net_device *dev)
अणु
  mace_निजी *lp = netdev_priv(dev);

  update_stats(dev->base_addr, dev);

  pr_debug("%s: updating the statistics.\n", dev->name);
  pr_linux_stats(&dev->stats);
  pr_mace_stats(&lp->mace_stats);

  वापस &dev->stats;
पूर्ण /* net_device_stats */

/* ----------------------------------------------------------------------------
updateCRC
	Modअगरied from Am79C90 data sheet.
---------------------------------------------------------------------------- */

#अगर_घोषित BROKEN_MULTICAST

अटल व्योम updateCRC(पूर्णांक *CRC, पूर्णांक bit)
अणु
  अटल स्थिर पूर्णांक poly[]=अणु
    1,1,1,0, 1,1,0,1,
    1,0,1,1, 1,0,0,0,
    1,0,0,0, 0,0,1,1,
    0,0,1,0, 0,0,0,0
  पूर्ण; /* CRC polynomial.  poly[n] = coefficient of the x**n term of the
	CRC generator polynomial. */

  पूर्णांक j;

  /* shअगरt CRC and control bit (CRC[32]) */
  क्रम (j = 32; j > 0; j--)
    CRC[j] = CRC[j-1];
  CRC[0] = 0;

  /* If bit XOR(control bit) = 1, set CRC = CRC XOR polynomial. */
  अगर (bit ^ CRC[32])
    क्रम (j = 0; j < 32; j++)
      CRC[j] ^= poly[j];
पूर्ण /* updateCRC */

/* ----------------------------------------------------------------------------
BuildLAF
	Build logical address filter.
	Modअगरied from Am79C90 data sheet.

Input
	ladrf: logical address filter (contents initialized to 0)
	adr: ethernet address
---------------------------------------------------------------------------- */
अटल व्योम BuildLAF(पूर्णांक *ladrf, पूर्णांक *adr)
अणु
  पूर्णांक CRC[33]=अणु1पूर्ण; /* CRC रेजिस्टर, 1 word/bit + extra control bit */

  पूर्णांक i, byte; /* temporary array indices */
  पूर्णांक hashcode; /* the output object */

  CRC[32]=0;

  क्रम (byte = 0; byte < 6; byte++)
    क्रम (i = 0; i < 8; i++)
      updateCRC(CRC, (adr[byte] >> i) & 1);

  hashcode = 0;
  क्रम (i = 0; i < 6; i++)
    hashcode = (hashcode << 1) + CRC[i];

  byte = hashcode >> 3;
  ladrf[byte] |= (1 << (hashcode & 7));

#अगर_घोषित PCMCIA_DEBUG
  अगर (0)
    prपूर्णांकk(KERN_DEBUG "    adr =%pM\n", adr);
  prपूर्णांकk(KERN_DEBUG "    hashcode = %d(decimal), ladrf[0:63] =", hashcode);
  क्रम (i = 0; i < 8; i++)
    pr_cont(" %02X", ladrf[i]);
  pr_cont("\n");
#पूर्ण_अगर
पूर्ण /* BuildLAF */

/* ----------------------------------------------------------------------------
restore_multicast_list
	Restores the multicast filter क्रम MACE chip to the last
	set_multicast_list() call.

Input
	multicast_num_addrs
	multicast_ladrf[]
---------------------------------------------------------------------------- */
अटल व्योम restore_multicast_list(काष्ठा net_device *dev)
अणु
  mace_निजी *lp = netdev_priv(dev);
  पूर्णांक num_addrs = lp->multicast_num_addrs;
  पूर्णांक *ladrf = lp->multicast_ladrf;
  अचिन्हित पूर्णांक ioaddr = dev->base_addr;
  पूर्णांक i;

  pr_debug("%s: restoring Rx mode to %d addresses.\n",
	dev->name, num_addrs);

  अगर (num_addrs > 0) अणु

    pr_debug("Attempt to restore multicast list detected.\n");

    mace_ग_लिखो(lp, ioaddr, MACE_IAC, MACE_IAC_ADDRCHG | MACE_IAC_LOGADDR);
    /* Poll ADDRCHG bit */
    जबतक (mace_पढ़ो(lp, ioaddr, MACE_IAC) & MACE_IAC_ADDRCHG)
      ;
    /* Set LADRF रेजिस्टर */
    क्रम (i = 0; i < MACE_LADRF_LEN; i++)
      mace_ग_लिखो(lp, ioaddr, MACE_LADRF, ladrf[i]);

    mace_ग_लिखो(lp, ioaddr, MACE_UTR, MACE_UTR_RCVFCSE | MACE_UTR_LOOP_EXTERNAL);
    mace_ग_लिखो(lp, ioaddr, MACE_MACCC, MACE_MACCC_ENXMT | MACE_MACCC_ENRCV);

  पूर्ण अन्यथा अगर (num_addrs < 0) अणु

    /* Promiscuous mode: receive all packets */
    mace_ग_लिखो(lp, ioaddr, MACE_UTR, MACE_UTR_LOOP_EXTERNAL);
    mace_ग_लिखो(lp, ioaddr, MACE_MACCC,
      MACE_MACCC_PROM | MACE_MACCC_ENXMT | MACE_MACCC_ENRCV
    );

  पूर्ण अन्यथा अणु

    /* Normal mode */
    mace_ग_लिखो(lp, ioaddr, MACE_UTR, MACE_UTR_LOOP_EXTERNAL);
    mace_ग_लिखो(lp, ioaddr, MACE_MACCC, MACE_MACCC_ENXMT | MACE_MACCC_ENRCV);

  पूर्ण
पूर्ण /* restore_multicast_list */

/* ----------------------------------------------------------------------------
set_multicast_list
	Set or clear the multicast filter क्रम this adaptor.

Input
	num_addrs == -1	Promiscuous mode, receive all packets
	num_addrs == 0	Normal mode, clear multicast list
	num_addrs > 0	Multicast mode, receive normal and MC packets, and करो
			best-efक्रमt filtering.
Output
	multicast_num_addrs
	multicast_ladrf[]
---------------------------------------------------------------------------- */

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
  mace_निजी *lp = netdev_priv(dev);
  पूर्णांक adr[ETH_ALEN] = अणु0पूर्ण; /* Ethernet address */
  काष्ठा netdev_hw_addr *ha;

#अगर_घोषित PCMCIA_DEBUG
  अणु
    अटल पूर्णांक old;
    अगर (netdev_mc_count(dev) != old) अणु
      old = netdev_mc_count(dev);
      pr_debug("%s: setting Rx mode to %d addresses.\n",
	    dev->name, old);
    पूर्ण
  पूर्ण
#पूर्ण_अगर

  /* Set multicast_num_addrs. */
  lp->multicast_num_addrs = netdev_mc_count(dev);

  /* Set multicast_ladrf. */
  अगर (num_addrs > 0) अणु
    /* Calculate multicast logical address filter */
    स_रखो(lp->multicast_ladrf, 0, MACE_LADRF_LEN);
    netdev_क्रम_each_mc_addr(ha, dev) अणु
      स_नकल(adr, ha->addr, ETH_ALEN);
      BuildLAF(lp->multicast_ladrf, adr);
    पूर्ण
  पूर्ण

  restore_multicast_list(dev);

पूर्ण /* set_multicast_list */

#पूर्ण_अगर /* BROKEN_MULTICAST */

अटल व्योम restore_multicast_list(काष्ठा net_device *dev)
अणु
  अचिन्हित पूर्णांक ioaddr = dev->base_addr;
  mace_निजी *lp = netdev_priv(dev);

  pr_debug("%s: restoring Rx mode to %d addresses.\n", dev->name,
	lp->multicast_num_addrs);

  अगर (dev->flags & IFF_PROMISC) अणु
    /* Promiscuous mode: receive all packets */
    mace_ग_लिखो(lp,ioaddr, MACE_UTR, MACE_UTR_LOOP_EXTERNAL);
    mace_ग_लिखो(lp, ioaddr, MACE_MACCC,
      MACE_MACCC_PROM | MACE_MACCC_ENXMT | MACE_MACCC_ENRCV
    );
  पूर्ण अन्यथा अणु
    /* Normal mode */
    mace_ग_लिखो(lp, ioaddr, MACE_UTR, MACE_UTR_LOOP_EXTERNAL);
    mace_ग_लिखो(lp, ioaddr, MACE_MACCC, MACE_MACCC_ENXMT | MACE_MACCC_ENRCV);
  पूर्ण
पूर्ण /* restore_multicast_list */

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
  mace_निजी *lp = netdev_priv(dev);

#अगर_घोषित PCMCIA_DEBUG
  अणु
    अटल पूर्णांक old;
    अगर (netdev_mc_count(dev) != old) अणु
      old = netdev_mc_count(dev);
      pr_debug("%s: setting Rx mode to %d addresses.\n",
	    dev->name, old);
    पूर्ण
  पूर्ण
#पूर्ण_अगर

  lp->multicast_num_addrs = netdev_mc_count(dev);
  restore_multicast_list(dev);

पूर्ण /* set_multicast_list */

अटल स्थिर काष्ठा pcmcia_device_id nmclan_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID12("New Media Corporation", "Ethernet", 0x085a850b, 0x00b2e941),
	PCMCIA_DEVICE_PROD_ID12("Portable Add-ons", "Ethernet+", 0xebf1d60, 0xad673aaf),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, nmclan_ids);

अटल काष्ठा pcmcia_driver nmclan_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "nmclan_cs",
	.probe		= nmclan_probe,
	.हटाओ		= nmclan_detach,
	.id_table       = nmclan_ids,
	.suspend	= nmclan_suspend,
	.resume		= nmclan_resume,
पूर्ण;
module_pcmcia_driver(nmclan_cs_driver);
