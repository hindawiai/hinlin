<शैली गुरु>
/* EtherLinkXL.c: A 3Com EtherLink PCI III/XL ethernet driver क्रम linux. */
/*
	Written 1996-1999 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	This driver is क्रम the 3Com "Vortex" and "Boomerang" series ethercards.
	Members of the series include Fast EtherLink 3c590/3c592/3c595/3c597
	and the EtherLink XL 3c900 and 3c905 cards.

	Problem reports and questions should be directed to
	vortex@scyld.com

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

*/

/*
 * FIXME: This driver _could_ support MTU changing, but करोesn't.  See Don's hamachi.c implementation
 * as well as other drivers
 *
 * NOTE: If you make 'vortex_debug' a स्थिरant (#घोषणा vortex_debug 0) the driver shrinks by 2k
 * due to dead code elimination.  There will be some perक्रमmance benefits from this due to
 * elimination of all the tests and reduced cache footprपूर्णांक.
 */


#घोषणा DRV_NAME	"3c59x"



/* A few values that may be tweaked. */
/* Keep the ring sizes a घातer of two क्रम efficiency. */
#घोषणा TX_RING_SIZE	16
#घोषणा RX_RING_SIZE	32
#घोषणा PKT_BUF_SZ		1536			/* Size of each temporary Rx buffer.*/

/* "Knobs" that adjust features and parameters. */
/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
   Setting to > 1512 effectively disables this feature. */
#अगर_अघोषित __arm__
अटल पूर्णांक rx_copyअवरोध = 200;
#अन्यथा
/* ARM प्रणालीs perक्रमm better by disregarding the bus-master
   transfer capability of these cards. -- rmk */
अटल पूर्णांक rx_copyअवरोध = 1513;
#पूर्ण_अगर
/* Allow setting MTU to a larger size, bypassing the normal ethernet setup. */
अटल स्थिर पूर्णांक mtu = 1500;
/* Maximum events (Rx packets, etc.) to handle at each पूर्णांकerrupt. */
अटल पूर्णांक max_पूर्णांकerrupt_work = 32;
/* Tx समयout पूर्णांकerval (millisecs) */
अटल पूर्णांक watchकरोg = 5000;

/* Allow aggregation of Tx पूर्णांकerrupts.  Saves CPU load at the cost
 * of possible Tx stalls अगर the प्रणाली is blocking पूर्णांकerrupts
 * somewhere अन्यथा.  Undefine this to disable.
 */
#घोषणा tx_पूर्णांकerrupt_mitigation 1

/* Put out somewhat more debugging messages. (0: no msg, 1 minimal .. 6). */
#घोषणा vortex_debug debug
#अगर_घोषित VORTEX_DEBUG
अटल पूर्णांक vortex_debug = VORTEX_DEBUG;
#अन्यथा
अटल पूर्णांक vortex_debug = 1;
#पूर्ण_अगर

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/mii.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/eisa.h>
#समावेश <linux/bitops.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/gfp.h>
#समावेश <यंत्र/irq.h>			/* For nr_irqs only. */
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

/* Kernel compatibility defines, some common to David Hinds' PCMCIA package.
   This is only in the support-all-kernels source code. */

#घोषणा RUN_AT(x) (jअगरfies + (x))

#समावेश <linux/delay.h>


अटल स्थिर अक्षर version[] =
	DRV_NAME ": Donald Becker and others.\n";

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("3Com 3c59x/3c9xx ethernet driver ");
MODULE_LICENSE("GPL");


/* Operational parameter that usually are not changed. */

/* The Vortex size is twice that of the original EtherLinkIII series: the
   runसमय रेजिस्टर winकरोw, winकरोw 1, is now always mapped in.
   The Boomerang size is twice as large as the Vortex -- it has additional
   bus master control रेजिस्टरs. */
#घोषणा VORTEX_TOTAL_SIZE 0x20
#घोषणा BOOMERANG_TOTAL_SIZE 0x40

/* Set अगरf a MII transceiver on any पूर्णांकerface requires mdio preamble.
   This only set with the original DP83840 on older 3c905 boards, so the extra
   code size of a per-पूर्णांकerface flag is not worthजबतक. */
अटल अक्षर mii_preamble_required;

#घोषणा PFX DRV_NAME ": "



/*
				Theory of Operation

I. Board Compatibility

This device driver is deचिन्हित क्रम the 3Com FastEtherLink and FastEtherLink
XL, 3Com's PCI to 10/100baseT adapters.  It also works with the 10Mbs
versions of the FastEtherLink cards.  The supported product IDs are
  3c590, 3c592, 3c595, 3c597, 3c900, 3c905

The related ISA 3c515 is supported with a separate driver, 3c515.c, included
with the kernel source or available from
    cesdis.gsfc.nasa.gov:/pub/linux/drivers/3c515.hपंचांगl

II. Board-specअगरic settings

PCI bus devices are configured by the प्रणाली at boot समय, so no jumpers
need to be set on the board.  The प्रणाली BIOS should be set to assign the
PCI INTA संकेत to an otherwise unused प्रणाली IRQ line.

The EEPROM settings क्रम media type and क्रमced-full-duplex are observed.
The EEPROM media type should be left at the शेष "autoselect" unless using
10base2 or AUI connections which cannot be reliably detected.

III. Driver operation

The 3c59x series use an पूर्णांकerface that's very similar to the previous 3c5x9
series.  The primary पूर्णांकerface is two programmed-I/O FIFOs, with an
alternate single-contiguous-region bus-master transfer (see next).

The 3c900 "Boomerang" series uses a full-bus-master पूर्णांकerface with separate
lists of transmit and receive descriptors, similar to the AMD LANCE/PCnet,
DEC Tulip and Intel Speeकरो3.  The first chip version retains a compatible
programmed-I/O पूर्णांकerface that has been हटाओd in 'B' and subsequent board
revisions.

One extension that is advertised in a very large font is that the adapters
are capable of being bus masters.  On the Vortex chip this capability was
only क्रम a single contiguous region making it far less useful than the full
bus master capability.  There is a signअगरicant perक्रमmance impact of taking
an extra पूर्णांकerrupt or polling क्रम the completion of each transfer, as well
as dअगरficulty sharing the single transfer engine between the transmit and
receive thपढ़ोs.  Using DMA transfers is a win only with large blocks or
with the flawed versions of the Intel Orion motherboard PCI controller.

The Boomerang chip's full-bus-master पूर्णांकerface is useful, and has the
currently-unused advantages over other similar chips that queued transmit
packets may be reordered and receive buffer groups are associated with a
single frame.

With full-bus-master support, this driver uses a "RX_COPYBREAK" scheme.
Rather than a fixed पूर्णांकermediate receive buffer, this scheme allocates
full-sized skbuffs as receive buffers.  The value RX_COPYBREAK is used as
the copying अवरोधpoपूर्णांक: it is chosen to trade-off the memory wasted by
passing the full-sized skbuff to the queue layer क्रम all frames vs. the
copying cost of copying a frame to a correctly-sized skbuff.

IIIC. Synchronization
The driver runs as two independent, single-thपढ़ोed flows of control.  One
is the send-packet routine, which enक्रमces single-thपढ़ोed use by the
dev->tbusy flag.  The other thपढ़ो is the पूर्णांकerrupt handler, which is single
thपढ़ोed by the hardware and other software.

IV. Notes

Thanks to Cameron Spitzer and Terry Murphy of 3Com क्रम providing development
3c590, 3c595, and 3c900 boards.
The name "Vortex" is the पूर्णांकernal 3Com project name क्रम the PCI ASIC, and
the EISA version is called "Demon".  According to Terry these names come
from rides at the local amusement park.

The new chips support both ethernet (1.5K) and FDDI (4.5K) packet sizes!
This driver only supports ethernet packets because of the skbuff allocation
limit of 4K.
*/

/* This table drives the PCI probe routines.  It's mostly boilerplate in all
   of the drivers, and will likely be provided by some future kernel.
*/
क्रमागत pci_flags_bit अणु
	PCI_USES_MASTER=4,
पूर्ण;

क्रमागत अणु	IS_VORTEX=1, IS_BOOMERANG=2, IS_CYCLONE=4, IS_TORNADO=8,
	EEPROM_8BIT=0x10,	/* AKPM: Uses 0x230 as the base biपंचांगaps क्रम EEPROM पढ़ोs */
	HAS_PWR_CTRL=0x20, HAS_MII=0x40, HAS_NWAY=0x80, HAS_CB_FNS=0x100,
	INVERT_MII_PWR=0x200, INVERT_LED_PWR=0x400, MAX_COLLISION_RESET=0x800,
	EEPROM_OFFSET=0x1000, HAS_HWCKSM=0x2000, WNO_XCVR_PWR=0x4000,
	EXTRA_PREAMBLE=0x8000, EEPROM_RESET=0x10000, पूर्ण;

क्रमागत vortex_chips अणु
	CH_3C590 = 0,
	CH_3C592,
	CH_3C597,
	CH_3C595_1,
	CH_3C595_2,

	CH_3C595_3,
	CH_3C900_1,
	CH_3C900_2,
	CH_3C900_3,
	CH_3C900_4,

	CH_3C900_5,
	CH_3C900B_FL,
	CH_3C905_1,
	CH_3C905_2,
	CH_3C905B_TX,
	CH_3C905B_1,

	CH_3C905B_2,
	CH_3C905B_FX,
	CH_3C905C,
	CH_3C9202,
	CH_3C980,
	CH_3C9805,

	CH_3CSOHO100_TX,
	CH_3C555,
	CH_3C556,
	CH_3C556B,
	CH_3C575,

	CH_3C575_1,
	CH_3CCFE575,
	CH_3CCFE575CT,
	CH_3CCFE656,
	CH_3CCFEM656,

	CH_3CCFEM656_1,
	CH_3C450,
	CH_3C920,
	CH_3C982A,
	CH_3C982B,

	CH_905BT4,
	CH_920B_EMB_WNM,
पूर्ण;


/* note: this array directly indexed by above क्रमागतs, and MUST
 * be kept in sync with both the क्रमागतs above, and the PCI device
 * table below
 */
अटल काष्ठा vortex_chip_info अणु
	स्थिर अक्षर *name;
	पूर्णांक flags;
	पूर्णांक drv_flags;
	पूर्णांक io_size;
पूर्ण vortex_info_tbl[] = अणु
	अणु"3c590 Vortex 10Mbps",
	 PCI_USES_MASTER, IS_VORTEX, 32, पूर्ण,
	अणु"3c592 EISA 10Mbps Demon/Vortex",					/* AKPM: from Don's 3c59x_cb.c 0.49H */
	 PCI_USES_MASTER, IS_VORTEX, 32, पूर्ण,
	अणु"3c597 EISA Fast Demon/Vortex",					/* AKPM: from Don's 3c59x_cb.c 0.49H */
	 PCI_USES_MASTER, IS_VORTEX, 32, पूर्ण,
	अणु"3c595 Vortex 100baseTx",
	 PCI_USES_MASTER, IS_VORTEX, 32, पूर्ण,
	अणु"3c595 Vortex 100baseT4",
	 PCI_USES_MASTER, IS_VORTEX, 32, पूर्ण,

	अणु"3c595 Vortex 100base-MII",
	 PCI_USES_MASTER, IS_VORTEX, 32, पूर्ण,
	अणु"3c900 Boomerang 10baseT",
	 PCI_USES_MASTER, IS_BOOMERANG|EEPROM_RESET, 64, पूर्ण,
	अणु"3c900 Boomerang 10Mbps Combo",
	 PCI_USES_MASTER, IS_BOOMERANG|EEPROM_RESET, 64, पूर्ण,
	अणु"3c900 Cyclone 10Mbps TPO",						/* AKPM: from Don's 0.99M */
	 PCI_USES_MASTER, IS_CYCLONE|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c900 Cyclone 10Mbps Combo",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_HWCKSM, 128, पूर्ण,

	अणु"3c900 Cyclone 10Mbps TPC",						/* AKPM: from Don's 0.99M */
	 PCI_USES_MASTER, IS_CYCLONE|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c900B-FL Cyclone 10base-FL",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c905 Boomerang 100baseTx",
	 PCI_USES_MASTER, IS_BOOMERANG|HAS_MII|EEPROM_RESET, 64, पूर्ण,
	अणु"3c905 Boomerang 100baseT4",
	 PCI_USES_MASTER, IS_BOOMERANG|HAS_MII|EEPROM_RESET, 64, पूर्ण,
	अणु"3C905B-TX Fast Etherlink XL PCI",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_NWAY|HAS_HWCKSM|EXTRA_PREAMBLE, 128, पूर्ण,
	अणु"3c905B Cyclone 100baseTx",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_NWAY|HAS_HWCKSM|EXTRA_PREAMBLE, 128, पूर्ण,

	अणु"3c905B Cyclone 10/100/BNC",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_NWAY|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c905B-FX Cyclone 100baseFx",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c905C Tornado",
	PCI_USES_MASTER, IS_TORNADO|HAS_NWAY|HAS_HWCKSM|EXTRA_PREAMBLE, 128, पूर्ण,
	अणु"3c920B-EMB-WNM (ATI Radeon 9100 IGP)",
	 PCI_USES_MASTER, IS_TORNADO|HAS_MII|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c980 Cyclone",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_HWCKSM|EXTRA_PREAMBLE, 128, पूर्ण,

	अणु"3c980C Python-T",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_NWAY|HAS_HWCKSM, 128, पूर्ण,
	अणु"3cSOHO100-TX Hurricane",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_NWAY|HAS_HWCKSM|EXTRA_PREAMBLE, 128, पूर्ण,
	अणु"3c555 Laptop Hurricane",
	 PCI_USES_MASTER, IS_CYCLONE|EEPROM_8BIT|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c556 Laptop Tornado",
	 PCI_USES_MASTER, IS_TORNADO|HAS_NWAY|EEPROM_8BIT|HAS_CB_FNS|INVERT_MII_PWR|
									HAS_HWCKSM, 128, पूर्ण,
	अणु"3c556B Laptop Hurricane",
	 PCI_USES_MASTER, IS_TORNADO|HAS_NWAY|EEPROM_OFFSET|HAS_CB_FNS|INVERT_MII_PWR|
	                                WNO_XCVR_PWR|HAS_HWCKSM, 128, पूर्ण,

	अणु"3c575 [Megahertz] 10/100 LAN 	CardBus",
	PCI_USES_MASTER, IS_BOOMERANG|HAS_MII|EEPROM_8BIT, 128, पूर्ण,
	अणु"3c575 Boomerang CardBus",
	 PCI_USES_MASTER, IS_BOOMERANG|HAS_MII|EEPROM_8BIT, 128, पूर्ण,
	अणु"3CCFE575BT Cyclone CardBus",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_NWAY|HAS_CB_FNS|EEPROM_8BIT|
									INVERT_LED_PWR|HAS_HWCKSM, 128, पूर्ण,
	अणु"3CCFE575CT Tornado CardBus",
	 PCI_USES_MASTER, IS_TORNADO|HAS_NWAY|HAS_CB_FNS|EEPROM_8BIT|INVERT_MII_PWR|
									MAX_COLLISION_RESET|HAS_HWCKSM, 128, पूर्ण,
	अणु"3CCFE656 Cyclone CardBus",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_NWAY|HAS_CB_FNS|EEPROM_8BIT|INVERT_MII_PWR|
									INVERT_LED_PWR|HAS_HWCKSM, 128, पूर्ण,

	अणु"3CCFEM656B Cyclone+Winmodem CardBus",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_NWAY|HAS_CB_FNS|EEPROM_8BIT|INVERT_MII_PWR|
									INVERT_LED_PWR|HAS_HWCKSM, 128, पूर्ण,
	अणु"3CXFEM656C Tornado+Winmodem CardBus",			/* From pcmcia-cs-3.1.5 */
	 PCI_USES_MASTER, IS_TORNADO|HAS_NWAY|HAS_CB_FNS|EEPROM_8BIT|INVERT_MII_PWR|
									MAX_COLLISION_RESET|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c450 HomePNA Tornado",						/* AKPM: from Don's 0.99Q */
	 PCI_USES_MASTER, IS_TORNADO|HAS_NWAY|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c920 Tornado",
	 PCI_USES_MASTER, IS_TORNADO|HAS_NWAY|HAS_HWCKSM, 128, पूर्ण,
	अणु"3c982 Hydra Dual Port A",
	 PCI_USES_MASTER, IS_TORNADO|HAS_HWCKSM|HAS_NWAY, 128, पूर्ण,

	अणु"3c982 Hydra Dual Port B",
	 PCI_USES_MASTER, IS_TORNADO|HAS_HWCKSM|HAS_NWAY, 128, पूर्ण,
	अणु"3c905B-T4",
	 PCI_USES_MASTER, IS_CYCLONE|HAS_NWAY|HAS_HWCKSM|EXTRA_PREAMBLE, 128, पूर्ण,
	अणु"3c920B-EMB-WNM Tornado",
	 PCI_USES_MASTER, IS_TORNADO|HAS_NWAY|HAS_HWCKSM, 128, पूर्ण,

	अणुशून्य,पूर्ण, /* शून्य terminated list. */
पूर्ण;


अटल स्थिर काष्ठा pci_device_id vortex_pci_tbl[] = अणु
	अणु 0x10B7, 0x5900, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C590 पूर्ण,
	अणु 0x10B7, 0x5920, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C592 पूर्ण,
	अणु 0x10B7, 0x5970, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C597 पूर्ण,
	अणु 0x10B7, 0x5950, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C595_1 पूर्ण,
	अणु 0x10B7, 0x5951, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C595_2 पूर्ण,

	अणु 0x10B7, 0x5952, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C595_3 पूर्ण,
	अणु 0x10B7, 0x9000, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_1 पूर्ण,
	अणु 0x10B7, 0x9001, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_2 पूर्ण,
	अणु 0x10B7, 0x9004, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_3 पूर्ण,
	अणु 0x10B7, 0x9005, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_4 पूर्ण,

	अणु 0x10B7, 0x9006, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_5 पूर्ण,
	अणु 0x10B7, 0x900A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900B_FL पूर्ण,
	अणु 0x10B7, 0x9050, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905_1 पूर्ण,
	अणु 0x10B7, 0x9051, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905_2 पूर्ण,
	अणु 0x10B7, 0x9054, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905B_TX पूर्ण,
	अणु 0x10B7, 0x9055, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905B_1 पूर्ण,

	अणु 0x10B7, 0x9058, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905B_2 पूर्ण,
	अणु 0x10B7, 0x905A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905B_FX पूर्ण,
	अणु 0x10B7, 0x9200, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905C पूर्ण,
	अणु 0x10B7, 0x9202, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C9202 पूर्ण,
	अणु 0x10B7, 0x9800, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C980 पूर्ण,
	अणु 0x10B7, 0x9805, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C9805 पूर्ण,

	अणु 0x10B7, 0x7646, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CSOHO100_TX पूर्ण,
	अणु 0x10B7, 0x5055, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C555 पूर्ण,
	अणु 0x10B7, 0x6055, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C556 पूर्ण,
	अणु 0x10B7, 0x6056, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C556B पूर्ण,
	अणु 0x10B7, 0x5b57, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C575 पूर्ण,

	अणु 0x10B7, 0x5057, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C575_1 पूर्ण,
	अणु 0x10B7, 0x5157, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFE575 पूर्ण,
	अणु 0x10B7, 0x5257, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFE575CT पूर्ण,
	अणु 0x10B7, 0x6560, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFE656 पूर्ण,
	अणु 0x10B7, 0x6562, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFEM656 पूर्ण,

	अणु 0x10B7, 0x6564, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFEM656_1 पूर्ण,
	अणु 0x10B7, 0x4500, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C450 पूर्ण,
	अणु 0x10B7, 0x9201, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C920 पूर्ण,
	अणु 0x10B7, 0x1201, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C982A पूर्ण,
	अणु 0x10B7, 0x1202, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C982B पूर्ण,

	अणु 0x10B7, 0x9056, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_905BT4 पूर्ण,
	अणु 0x10B7, 0x9210, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_920B_EMB_WNM पूर्ण,

	अणु0,पूर्ण						/* 0 terminated list. */
पूर्ण;
MODULE_DEVICE_TABLE(pci, vortex_pci_tbl);


/* Operational definitions.
   These are not used by other compilation units and thus are not
   exported in a ".h" file.

   First the winकरोws.  There are eight रेजिस्टर winकरोws, with the command
   and status रेजिस्टरs available in each.
   */
#घोषणा EL3_CMD 0x0e
#घोषणा EL3_STATUS 0x0e

/* The top five bits written to EL3_CMD are a command, the lower
   11 bits are the parameter, अगर applicable.
   Note that 11 parameters bits was fine क्रम ethernet, but the new chip
   can handle FDDI length frames (~4500 octets) and now parameters count
   32-bit 'Dwords' rather than octets. */

क्रमागत vortex_cmd अणु
	TotalReset = 0<<11, SelectWinकरोw = 1<<11, StartCoax = 2<<11,
	RxDisable = 3<<11, RxEnable = 4<<11, RxReset = 5<<11,
	UpStall = 6<<11, UpUnstall = (6<<11)+1,
	DownStall = (6<<11)+2, DownUnstall = (6<<11)+3,
	RxDiscard = 8<<11, TxEnable = 9<<11, TxDisable = 10<<11, TxReset = 11<<11,
	FakeIntr = 12<<11, AckIntr = 13<<11, SetIntrEnb = 14<<11,
	SetStatusEnb = 15<<11, SetRxFilter = 16<<11, SetRxThreshold = 17<<11,
	SetTxThreshold = 18<<11, SetTxStart = 19<<11,
	StartDMAUp = 20<<11, StartDMADown = (20<<11)+1, StatsEnable = 21<<11,
	StatsDisable = 22<<11, StopCoax = 23<<11, SetFilterBit = 25<<11,पूर्ण;

/* The SetRxFilter command accepts the following classes: */
क्रमागत RxFilter अणु
	RxStation = 1, RxMulticast = 2, RxBroadcast = 4, RxProm = 8 पूर्ण;

/* Bits in the general status रेजिस्टर. */
क्रमागत vortex_status अणु
	IntLatch = 0x0001, HostError = 0x0002, TxComplete = 0x0004,
	TxAvailable = 0x0008, RxComplete = 0x0010, RxEarly = 0x0020,
	IntReq = 0x0040, StatsFull = 0x0080,
	DMADone = 1<<8, DownComplete = 1<<9, UpComplete = 1<<10,
	DMAInProgress = 1<<11,			/* DMA controller is still busy.*/
	CmdInProgress = 1<<12,			/* EL3_CMD is still busy.*/
पूर्ण;

/* Register winकरोw 1 offsets, the winकरोw used in normal operation.
   On the Vortex this winकरोw is always mapped at offsets 0x10-0x1f. */
क्रमागत Winकरोw1 अणु
	TX_FIFO = 0x10,  RX_FIFO = 0x10,  RxErrors = 0x14,
	RxStatus = 0x18,  Timer=0x1A, TxStatus = 0x1B,
	TxFree = 0x1C, /* Reमुख्यing मुक्त bytes in Tx buffer. */
पूर्ण;
क्रमागत Winकरोw0 अणु
	Wn0EepromCmd = 10,		/* Winकरोw 0: EEPROM command रेजिस्टर. */
	Wn0EepromData = 12,		/* Winकरोw 0: EEPROM results रेजिस्टर. */
	IntrStatus=0x0E,		/* Valid in all winकरोws. */
पूर्ण;
क्रमागत Win0_EEPROM_bits अणु
	EEPROM_Read = 0x80, EEPROM_WRITE = 0x40, EEPROM_ERASE = 0xC0,
	EEPROM_EWENB = 0x30,		/* Enable erasing/writing क्रम 10 msec. */
	EEPROM_EWDIS = 0x00,		/* Disable EWENB beक्रमe 10 msec समयout. */
पूर्ण;
/* EEPROM locations. */
क्रमागत eeprom_offset अणु
	PhysAddr01=0, PhysAddr23=1, PhysAddr45=2, ModelID=3,
	EtherLink3ID=7, IFXcvrIO=8, IRQLine=9,
	NodeAddr01=10, NodeAddr23=11, NodeAddr45=12,
	DriverTune=13, Checksum=15पूर्ण;

क्रमागत Winकरोw2 अणु			/* Winकरोw 2. */
	Wn2_ResetOptions=12,
पूर्ण;
क्रमागत Winकरोw3 अणु			/* Winकरोw 3: MAC/config bits. */
	Wn3_Config=0, Wn3_MaxPktSize=4, Wn3_MAC_Ctrl=6, Wn3_Options=8,
पूर्ण;

#घोषणा BFEXT(value, offset, bitcount)  \
    ((((अचिन्हित दीर्घ)(value)) >> (offset)) & ((1 << (bitcount)) - 1))

#घोषणा BFINS(lhs, rhs, offset, bitcount)					\
	(((lhs) & ~((((1 << (bitcount)) - 1)) << (offset))) |	\
	(((rhs) & ((1 << (bitcount)) - 1)) << (offset)))

#घोषणा RAM_SIZE(v)		BFEXT(v, 0, 3)
#घोषणा RAM_WIDTH(v)	BFEXT(v, 3, 1)
#घोषणा RAM_SPEED(v)	BFEXT(v, 4, 2)
#घोषणा ROM_SIZE(v)		BFEXT(v, 6, 2)
#घोषणा RAM_SPLIT(v)	BFEXT(v, 16, 2)
#घोषणा XCVR(v)			BFEXT(v, 20, 4)
#घोषणा AUTOSELECT(v)	BFEXT(v, 24, 1)

क्रमागत Winकरोw4 अणु		/* Winकरोw 4: Xcvr/media bits. */
	Wn4_FIFODiag = 4, Wn4_NetDiag = 6, Wn4_PhysicalMgmt=8, Wn4_Media = 10,
पूर्ण;
क्रमागत Win4_Media_bits अणु
	Media_SQE = 0x0008,		/* Enable SQE error counting क्रम AUI. */
	Media_10TP = 0x00C0,	/* Enable link beat and jabber क्रम 10baseT. */
	Media_Lnk = 0x0080,		/* Enable just link beat क्रम 100TX/100FX. */
	Media_LnkBeat = 0x0800,
पूर्ण;
क्रमागत Winकरोw7 अणु					/* Winकरोw 7: Bus Master control. */
	Wn7_MasterAddr = 0, Wn7_VlanEtherType=4, Wn7_MasterLen = 6,
	Wn7_MasterStatus = 12,
पूर्ण;
/* Boomerang bus master control रेजिस्टरs. */
क्रमागत MasterCtrl अणु
	PktStatus = 0x20, DownListPtr = 0x24, FragAddr = 0x28, FragLen = 0x2c,
	TxFreeThreshold = 0x2f, UpPktStatus = 0x30, UpListPtr = 0x38,
पूर्ण;

/* The Rx and Tx descriptor lists.
   Caution Alpha hackers: these types are 32 bits!  Note also the 8 byte
   alignment contraपूर्णांक on tx_ring[] and rx_ring[]. */
#घोषणा LAST_FRAG 	0x80000000			/* Last Addr/Len pair in descriptor. */
#घोषणा DN_COMPLETE	0x00010000			/* This packet has been करोwnloaded */
काष्ठा boom_rx_desc अणु
	__le32 next;					/* Last entry poपूर्णांकs to 0.   */
	__le32 status;
	__le32 addr;					/* Up to 63 addr/len pairs possible. */
	__le32 length;					/* Set LAST_FRAG to indicate last pair. */
पूर्ण;
/* Values क्रम the Rx status entry. */
क्रमागत rx_desc_status अणु
	RxDComplete=0x00008000, RxDError=0x4000,
	/* See boomerang_rx() क्रम actual error bits */
	IPChksumErr=1<<25, TCPChksumErr=1<<26, UDPChksumErr=1<<27,
	IPChksumValid=1<<29, TCPChksumValid=1<<30, UDPChksumValid=1<<31,
पूर्ण;

#अगर_घोषित MAX_SKB_FRAGS
#घोषणा DO_ZEROCOPY 1
#अन्यथा
#घोषणा DO_ZEROCOPY 0
#पूर्ण_अगर

काष्ठा boom_tx_desc अणु
	__le32 next;					/* Last entry poपूर्णांकs to 0.   */
	__le32 status;					/* bits 0:12 length, others see below.  */
#अगर DO_ZEROCOPY
	काष्ठा अणु
		__le32 addr;
		__le32 length;
	पूर्ण frag[1+MAX_SKB_FRAGS];
#अन्यथा
		__le32 addr;
		__le32 length;
#पूर्ण_अगर
पूर्ण;

/* Values क्रम the Tx status entry. */
क्रमागत tx_desc_status अणु
	CRCDisable=0x2000, TxDComplete=0x8000,
	AddIPChksum=0x02000000, AddTCPChksum=0x04000000, AddUDPChksum=0x08000000,
	TxIntrUploaded=0x80000000,		/* IRQ when in FIFO, but maybe not sent. */
पूर्ण;

/* Chip features we care about in vp->capabilities, पढ़ो from the EEPROM. */
क्रमागत ChipCaps अणु CapBusMaster=0x20, CapPwrMgmt=0x2000 पूर्ण;

काष्ठा vortex_extra_stats अणु
	अचिन्हित दीर्घ tx_deferred;
	अचिन्हित दीर्घ tx_max_collisions;
	अचिन्हित दीर्घ tx_multiple_collisions;
	अचिन्हित दीर्घ tx_single_collisions;
	अचिन्हित दीर्घ rx_bad_ssd;
पूर्ण;

काष्ठा vortex_निजी अणु
	/* The Rx and Tx rings should be quad-word-aligned. */
	काष्ठा boom_rx_desc* rx_ring;
	काष्ठा boom_tx_desc* tx_ring;
	dma_addr_t rx_ring_dma;
	dma_addr_t tx_ring_dma;
	/* The addresses of transmit- and receive-in-place skbuffs. */
	काष्ठा sk_buff* rx_skbuff[RX_RING_SIZE];
	काष्ठा sk_buff* tx_skbuff[TX_RING_SIZE];
	अचिन्हित पूर्णांक cur_rx, cur_tx;		/* The next मुक्त ring entry */
	अचिन्हित पूर्णांक dirty_tx;	/* The ring entries to be मुक्त()ed. */
	काष्ठा vortex_extra_stats xstats;	/* NIC-specअगरic extra stats */
	काष्ठा sk_buff *tx_skb;				/* Packet being eaten by bus master ctrl.  */
	dma_addr_t tx_skb_dma;				/* Allocated DMA address क्रम bus master ctrl DMA.   */

	/* PCI configuration space inक्रमmation. */
	काष्ठा device *gendev;
	व्योम __iomem *ioaddr;			/* IO address space */
	व्योम __iomem *cb_fn_base;		/* CardBus function status addr space. */

	/* Some values here only क्रम perक्रमmance evaluation and path-coverage */
	पूर्णांक rx_nocopy, rx_copy, queued_packet, rx_csumhits;
	पूर्णांक card_idx;

	/* The reमुख्यder are related to chip state, mostly media selection. */
	काष्ठा समयr_list समयr;			/* Media selection समयr. */
	पूर्णांक options;						/* User-settable misc. driver options. */
	अचिन्हित पूर्णांक media_override:4, 		/* Passed-in media type. */
		शेष_media:4,				/* Read from the EEPROM/Wn3_Config. */
		full_duplex:1, स्वतःselect:1,
		bus_master:1,					/* Vortex can only करो a fragment bus-m. */
		full_bus_master_tx:1, full_bus_master_rx:2, /* Boomerang  */
		flow_ctrl:1,					/* Use 802.3x flow control (PAUSE only) */
		partner_flow_ctrl:1,			/* Partner supports flow control */
		has_nway:1,
		enable_wol:1,					/* Wake-on-LAN is enabled */
		pm_state_valid:1,				/* pci_dev->saved_config_space has sane contents */
		खोलो:1,
		medialock:1,
		large_frames:1,			/* accept large frames */
		handling_irq:1;			/* निजी in_irq indicator */
	/* अणुget|setपूर्ण_wol operations are alपढ़ोy serialized by rtnl.
	 * no additional locking is required क्रम the enable_wol and acpi_set_WOL()
	 */
	पूर्णांक drv_flags;
	u16 status_enable;
	u16 पूर्णांकr_enable;
	u16 available_media;				/* From Wn3_Options. */
	u16 capabilities, info1, info2;		/* Various, from EEPROM. */
	u16 advertising;					/* NWay media advertisement */
	अचिन्हित अक्षर phys[2];				/* MII device addresses. */
	u16 deferred;						/* Resend these पूर्णांकerrupts when we
										 * bale from the ISR */
	u16 io_size;						/* Size of PCI region (क्रम release_region) */

	/* Serialises access to hardware other than MII and variables below.
	 * The lock hierarchy is rtnl_lock > अणुlock, mii_lockपूर्ण > winकरोw_lock. */
	spinlock_t lock;

	spinlock_t mii_lock;		/* Serialises access to MII */
	काष्ठा mii_अगर_info mii;		/* MII lib hooks/info */
	spinlock_t winकरोw_lock;		/* Serialises access to winकरोwed regs */
	पूर्णांक winकरोw;			/* Register winकरोw */
पूर्ण;

अटल व्योम winकरोw_set(काष्ठा vortex_निजी *vp, पूर्णांक winकरोw)
अणु
	अगर (winकरोw != vp->winकरोw) अणु
		ioग_लिखो16(SelectWinकरोw + winकरोw, vp->ioaddr + EL3_CMD);
		vp->winकरोw = winकरोw;
	पूर्ण
पूर्ण

#घोषणा DEFINE_WINDOW_IO(size)						\
अटल u ## size							\
winकरोw_पढ़ो ## size(काष्ठा vortex_निजी *vp, पूर्णांक winकरोw, पूर्णांक addr)	\
अणु									\
	अचिन्हित दीर्घ flags;						\
	u ## size ret;							\
	spin_lock_irqsave(&vp->winकरोw_lock, flags);			\
	winकरोw_set(vp, winकरोw);						\
	ret = ioपढ़ो ## size(vp->ioaddr + addr);			\
	spin_unlock_irqrestore(&vp->winकरोw_lock, flags);		\
	वापस ret;							\
पूर्ण									\
अटल व्योम								\
winकरोw_ग_लिखो ## size(काष्ठा vortex_निजी *vp, u ## size value,	\
		     पूर्णांक winकरोw, पूर्णांक addr)				\
अणु									\
	अचिन्हित दीर्घ flags;						\
	spin_lock_irqsave(&vp->winकरोw_lock, flags);			\
	winकरोw_set(vp, winकरोw);						\
	ioग_लिखो ## size(value, vp->ioaddr + addr);			\
	spin_unlock_irqrestore(&vp->winकरोw_lock, flags);		\
पूर्ण
DEFINE_WINDOW_IO(8)
DEFINE_WINDOW_IO(16)
DEFINE_WINDOW_IO(32)

#अगर_घोषित CONFIG_PCI
#घोषणा DEVICE_PCI(dev) ((dev_is_pci(dev)) ? to_pci_dev((dev)) : शून्य)
#अन्यथा
#घोषणा DEVICE_PCI(dev) शून्य
#पूर्ण_अगर

#घोषणा VORTEX_PCI(vp)							\
	((काष्ठा pci_dev *) (((vp)->gendev) ? DEVICE_PCI((vp)->gendev) : शून्य))

#अगर_घोषित CONFIG_EISA
#घोषणा DEVICE_EISA(dev) (((dev)->bus == &eisa_bus_type) ? to_eisa_device((dev)) : शून्य)
#अन्यथा
#घोषणा DEVICE_EISA(dev) शून्य
#पूर्ण_अगर

#घोषणा VORTEX_EISA(vp)							\
	((काष्ठा eisa_device *) (((vp)->gendev) ? DEVICE_EISA((vp)->gendev) : शून्य))

/* The action to take with a media selection समयr tick.
   Note that we deviate from the 3Com order by checking 10base2 beक्रमe AUI.
 */
क्रमागत xcvr_types अणु
	XCVR_10baseT=0, XCVR_AUI, XCVR_10baseTOnly, XCVR_10base2, XCVR_100baseTx,
	XCVR_100baseFx, XCVR_MII=6, XCVR_NWAY=8, XCVR_ExtMII=9, XCVR_Default=10,
पूर्ण;

अटल स्थिर काष्ठा media_table अणु
	अक्षर *name;
	अचिन्हित पूर्णांक media_bits:16,		/* Bits to set in Wn4_Media रेजिस्टर. */
		mask:8,						/* The transceiver-present bit in Wn3_Config.*/
		next:8;						/* The media type to try next. */
	पूर्णांक रुको;						/* Time beक्रमe we check media status. */
पूर्ण media_tbl[] = अणु
  अणु	"10baseT",   Media_10TP,0x08, XCVR_10base2, (14*HZ)/10पूर्ण,
  अणु "10Mbs AUI", Media_SQE, 0x20, XCVR_Default, (1*HZ)/10पूर्ण,
  अणु "undefined", 0,			0x80, XCVR_10baseT, 10000पूर्ण,
  अणु "10base2",   0,			0x10, XCVR_AUI,		(1*HZ)/10पूर्ण,
  अणु "100baseTX", Media_Lnk, 0x02, XCVR_100baseFx, (14*HZ)/10पूर्ण,
  अणु "100baseFX", Media_Lnk, 0x04, XCVR_MII,		(14*HZ)/10पूर्ण,
  अणु "MII",		 0,			0x41, XCVR_10baseT, 3*HZ पूर्ण,
  अणु "undefined", 0,			0x01, XCVR_10baseT, 10000पूर्ण,
  अणु "Autonegotiate", 0,		0x41, XCVR_10baseT, 3*HZपूर्ण,
  अणु "MII-External",	 0,		0x41, XCVR_10baseT, 3*HZ पूर्ण,
  अणु "Default",	 0,			0xFF, XCVR_10baseT, 10000पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	स्थिर अक्षर str[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "tx_deferred" पूर्ण,
	अणु "tx_max_collisions" पूर्ण,
	अणु "tx_multiple_collisions" पूर्ण,
	अणु "tx_single_collisions" पूर्ण,
	अणु "rx_bad_ssd" पूर्ण,
पूर्ण;

/* number of ETHTOOL_GSTATS u64's */
#घोषणा VORTEX_NUM_STATS    5

अटल पूर्णांक vortex_probe1(काष्ठा device *gendev, व्योम __iomem *ioaddr, पूर्णांक irq,
				   पूर्णांक chip_idx, पूर्णांक card_idx);
अटल पूर्णांक vortex_up(काष्ठा net_device *dev);
अटल व्योम vortex_करोwn(काष्ठा net_device *dev, पूर्णांक final);
अटल पूर्णांक vortex_खोलो(काष्ठा net_device *dev);
अटल व्योम mdio_sync(काष्ठा vortex_निजी *vp, पूर्णांक bits);
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *vp, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value);
अटल व्योम vortex_समयr(काष्ठा समयr_list *t);
अटल netdev_tx_t vortex_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev);
अटल netdev_tx_t boomerang_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev);
अटल पूर्णांक vortex_rx(काष्ठा net_device *dev);
अटल पूर्णांक boomerang_rx(काष्ठा net_device *dev);
अटल irqवापस_t vortex_boomerang_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t _vortex_पूर्णांकerrupt(पूर्णांक irq, काष्ठा net_device *dev);
अटल irqवापस_t _boomerang_पूर्णांकerrupt(पूर्णांक irq, काष्ठा net_device *dev);
अटल पूर्णांक vortex_बंद(काष्ठा net_device *dev);
अटल व्योम dump_tx_ring(काष्ठा net_device *dev);
अटल व्योम update_stats(व्योम __iomem *ioaddr, काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *vortex_get_stats(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
#अगर_घोषित CONFIG_PCI
अटल पूर्णांक vortex_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
#पूर्ण_अगर
अटल व्योम vortex_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम acpi_set_WOL(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops vortex_ethtool_ops;
अटल व्योम set_8021q_mode(काष्ठा net_device *dev, पूर्णांक enable);

/* This driver uses 'options' to pass the media type, full-duplex flag, etc. */
/* Option count limit only -- unlimited पूर्णांकerfaces are supported. */
#घोषणा MAX_UNITS 8
अटल पूर्णांक options[MAX_UNITS] = अणु [0 ... MAX_UNITS-1] = -1 पूर्ण;
अटल पूर्णांक full_duplex[MAX_UNITS] = अणु[0 ... MAX_UNITS-1] = -1 पूर्ण;
अटल पूर्णांक hw_checksums[MAX_UNITS] = अणु[0 ... MAX_UNITS-1] = -1 पूर्ण;
अटल पूर्णांक flow_ctrl[MAX_UNITS] = अणु[0 ... MAX_UNITS-1] = -1 पूर्ण;
अटल पूर्णांक enable_wol[MAX_UNITS] = अणु[0 ... MAX_UNITS-1] = -1 पूर्ण;
अटल पूर्णांक use_mmio[MAX_UNITS] = अणु[0 ... MAX_UNITS-1] = -1 पूर्ण;
अटल पूर्णांक global_options = -1;
अटल पूर्णांक global_full_duplex = -1;
अटल पूर्णांक global_enable_wol = -1;
अटल पूर्णांक global_use_mmio = -1;

/* Variables to work-around the Compaq PCI BIOS32 problem. */
अटल पूर्णांक compaq_ioaddr, compaq_irq, compaq_device_id = 0x5900;
अटल काष्ठा net_device *compaq_net_device;

अटल पूर्णांक vortex_cards_found;

module_param(debug, पूर्णांक, 0);
module_param(global_options, पूर्णांक, 0);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param(global_full_duplex, पूर्णांक, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
module_param_array(hw_checksums, पूर्णांक, शून्य, 0);
module_param_array(flow_ctrl, पूर्णांक, शून्य, 0);
module_param(global_enable_wol, पूर्णांक, 0);
module_param_array(enable_wol, पूर्णांक, शून्य, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
module_param_hw(compaq_ioaddr, पूर्णांक, ioport, 0);
module_param_hw(compaq_irq, पूर्णांक, irq, 0);
module_param(compaq_device_id, पूर्णांक, 0);
module_param(watchकरोg, पूर्णांक, 0);
module_param(global_use_mmio, पूर्णांक, 0);
module_param_array(use_mmio, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(debug, "3c59x debug level (0-6)");
MODULE_PARM_DESC(options, "3c59x: Bits 0-3: media type, bit 4: bus mastering, bit 9: full duplex");
MODULE_PARM_DESC(global_options, "3c59x: same as options, but applies to all NICs if options is unset");
MODULE_PARM_DESC(full_duplex, "3c59x full duplex setting(s) (1)");
MODULE_PARM_DESC(global_full_duplex, "3c59x: same as full_duplex, but applies to all NICs if full_duplex is unset");
MODULE_PARM_DESC(hw_checksums, "3c59x Hardware checksum checking by adapter(s) (0-1)");
MODULE_PARM_DESC(flow_ctrl, "3c59x 802.3x flow control usage (PAUSE only) (0-1)");
MODULE_PARM_DESC(enable_wol, "3c59x: Turn on Wake-on-LAN for adapter(s) (0-1)");
MODULE_PARM_DESC(global_enable_wol, "3c59x: same as enable_wol, but applies to all NICs if enable_wol is unset");
MODULE_PARM_DESC(rx_copyअवरोध, "3c59x copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "3c59x maximum events handled per interrupt");
MODULE_PARM_DESC(compaq_ioaddr, "3c59x PCI I/O base address (Compaq BIOS problem workaround)");
MODULE_PARM_DESC(compaq_irq, "3c59x PCI IRQ number (Compaq BIOS problem workaround)");
MODULE_PARM_DESC(compaq_device_id, "3c59x PCI device ID (Compaq BIOS problem workaround)");
MODULE_PARM_DESC(watchकरोg, "3c59x transmit timeout in milliseconds");
MODULE_PARM_DESC(global_use_mmio, "3c59x: same as use_mmio, but applies to all NICs if options is unset");
MODULE_PARM_DESC(use_mmio, "3c59x: use memory-mapped PCI I/O resource (0-1)");

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम poll_vortex(काष्ठा net_device *dev)
अणु
	vortex_boomerang_पूर्णांकerrupt(dev->irq, dev);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM

अटल पूर्णांक vortex_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);

	अगर (!ndev || !netअगर_running(ndev))
		वापस 0;

	netअगर_device_detach(ndev);
	vortex_करोwn(ndev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक vortex_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	पूर्णांक err;

	अगर (!ndev || !netअगर_running(ndev))
		वापस 0;

	err = vortex_up(ndev);
	अगर (err)
		वापस err;

	netअगर_device_attach(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vortex_pm_ops = अणु
	.suspend = vortex_suspend,
	.resume = vortex_resume,
	.मुक्तze = vortex_suspend,
	.thaw = vortex_resume,
	.घातeroff = vortex_suspend,
	.restore = vortex_resume,
पूर्ण;

#घोषणा VORTEX_PM_OPS (&vortex_pm_ops)

#अन्यथा /* !CONFIG_PM */

#घोषणा VORTEX_PM_OPS शून्य

#पूर्ण_अगर /* !CONFIG_PM */

#अगर_घोषित CONFIG_EISA
अटल स्थिर काष्ठा eisa_device_id vortex_eisa_ids[] = अणु
	अणु "TCM5920", CH_3C592 पूर्ण,
	अणु "TCM5970", CH_3C597 पूर्ण,
	अणु "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(eisa, vortex_eisa_ids);

अटल पूर्णांक vortex_eisa_probe(काष्ठा device *device)
अणु
	व्योम __iomem *ioaddr;
	काष्ठा eisa_device *edev;

	edev = to_eisa_device(device);

	अगर (!request_region(edev->base_addr, VORTEX_TOTAL_SIZE, DRV_NAME))
		वापस -EBUSY;

	ioaddr = ioport_map(edev->base_addr, VORTEX_TOTAL_SIZE);

	अगर (vortex_probe1(device, ioaddr, ioपढ़ो16(ioaddr + 0xC88) >> 12,
					  edev->id.driver_data, vortex_cards_found)) अणु
		release_region(edev->base_addr, VORTEX_TOTAL_SIZE);
		वापस -ENODEV;
	पूर्ण

	vortex_cards_found++;

	वापस 0;
पूर्ण

अटल पूर्णांक vortex_eisa_हटाओ(काष्ठा device *device)
अणु
	काष्ठा eisa_device *edev;
	काष्ठा net_device *dev;
	काष्ठा vortex_निजी *vp;
	व्योम __iomem *ioaddr;

	edev = to_eisa_device(device);
	dev = eisa_get_drvdata(edev);

	अगर (!dev) अणु
		pr_err("vortex_eisa_remove called for Compaq device!\n");
		BUG();
	पूर्ण

	vp = netdev_priv(dev);
	ioaddr = vp->ioaddr;

	unरेजिस्टर_netdev(dev);
	ioग_लिखो16(TotalReset|0x14, ioaddr + EL3_CMD);
	release_region(edev->base_addr, VORTEX_TOTAL_SIZE);

	मुक्त_netdev(dev);
	वापस 0;
पूर्ण

अटल काष्ठा eisa_driver vortex_eisa_driver = अणु
	.id_table = vortex_eisa_ids,
	.driver   = अणु
		.name    = "3c59x",
		.probe   = vortex_eisa_probe,
		.हटाओ  = vortex_eisa_हटाओ
	पूर्ण
पूर्ण;

#पूर्ण_अगर /* CONFIG_EISA */

/* वापसs count found (>= 0), or negative on error */
अटल पूर्णांक __init vortex_eisa_init(व्योम)
अणु
	पूर्णांक eisa_found = 0;
	पूर्णांक orig_cards_found = vortex_cards_found;

#अगर_घोषित CONFIG_EISA
	पूर्णांक err;

	err = eisa_driver_रेजिस्टर (&vortex_eisa_driver);
	अगर (!err) अणु
		/*
		 * Because of the way EISA bus is probed, we cannot assume
		 * any device have been found when we निकास from
		 * eisa_driver_रेजिस्टर (the bus root driver may not be
		 * initialized yet). So we blindly assume something was
		 * found, and let the sysfs magic happened...
		 */
		eisa_found = 1;
	पूर्ण
#पूर्ण_अगर

	/* Special code to work-around the Compaq PCI BIOS32 problem. */
	अगर (compaq_ioaddr) अणु
		vortex_probe1(शून्य, ioport_map(compaq_ioaddr, VORTEX_TOTAL_SIZE),
			      compaq_irq, compaq_device_id, vortex_cards_found++);
	पूर्ण

	वापस vortex_cards_found - orig_cards_found + eisa_found;
पूर्ण

/* वापसs count (>= 0), or negative on error */
अटल पूर्णांक vortex_init_one(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc, unit, pci_bar;
	काष्ठा vortex_chip_info *vci;
	व्योम __iomem *ioaddr;

	/* wake up and enable device */
	rc = pci_enable_device(pdev);
	अगर (rc < 0)
		जाओ out;

	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc < 0)
		जाओ out_disable;

	unit = vortex_cards_found;

	अगर (global_use_mmio < 0 && (unit >= MAX_UNITS || use_mmio[unit] < 0)) अणु
		/* Determine the शेष अगर the user didn't override us */
		vci = &vortex_info_tbl[ent->driver_data];
		pci_bar = vci->drv_flags & (IS_CYCLONE | IS_TORNADO) ? 1 : 0;
	पूर्ण अन्यथा अगर (unit < MAX_UNITS && use_mmio[unit] >= 0)
		pci_bar = use_mmio[unit] ? 1 : 0;
	अन्यथा
		pci_bar = global_use_mmio ? 1 : 0;

	ioaddr = pci_iomap(pdev, pci_bar, 0);
	अगर (!ioaddr) /* If mapping fails, fall-back to BAR 0... */
		ioaddr = pci_iomap(pdev, 0, 0);
	अगर (!ioaddr) अणु
		rc = -ENOMEM;
		जाओ out_release;
	पूर्ण

	rc = vortex_probe1(&pdev->dev, ioaddr, pdev->irq,
			   ent->driver_data, unit);
	अगर (rc < 0)
		जाओ out_iounmap;

	vortex_cards_found++;
	जाओ out;

out_iounmap:
	pci_iounmap(pdev, ioaddr);
out_release:
	pci_release_regions(pdev);
out_disable:
	pci_disable_device(pdev);
out:
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_device_ops boomrang_netdev_ops = अणु
	.nकरो_खोलो		= vortex_खोलो,
	.nकरो_stop		= vortex_बंद,
	.nकरो_start_xmit		= boomerang_start_xmit,
	.nकरो_tx_समयout		= vortex_tx_समयout,
	.nकरो_get_stats		= vortex_get_stats,
#अगर_घोषित CONFIG_PCI
	.nकरो_करो_ioctl 		= vortex_ioctl,
#पूर्ण_अगर
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= poll_vortex,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_device_ops vortex_netdev_ops = अणु
	.nकरो_खोलो		= vortex_खोलो,
	.nकरो_stop		= vortex_बंद,
	.nकरो_start_xmit		= vortex_start_xmit,
	.nकरो_tx_समयout		= vortex_tx_समयout,
	.nकरो_get_stats		= vortex_get_stats,
#अगर_घोषित CONFIG_PCI
	.nकरो_करो_ioctl 		= vortex_ioctl,
#पूर्ण_अगर
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= poll_vortex,
#पूर्ण_अगर
पूर्ण;

/*
 * Start up the PCI/EISA device which is described by *gendev.
 * Return 0 on success.
 *
 * NOTE: pdev can be शून्य, क्रम the हाल of a Compaq device
 */
अटल पूर्णांक vortex_probe1(काष्ठा device *gendev, व्योम __iomem *ioaddr, पूर्णांक irq,
			 पूर्णांक chip_idx, पूर्णांक card_idx)
अणु
	काष्ठा vortex_निजी *vp;
	पूर्णांक option;
	अचिन्हित पूर्णांक eeprom[0x40], checksum = 0;		/* EEPROM contents */
	पूर्णांक i, step;
	काष्ठा net_device *dev;
	अटल पूर्णांक prपूर्णांकed_version;
	पूर्णांक retval, prपूर्णांक_info;
	काष्ठा vortex_chip_info * स्थिर vci = &vortex_info_tbl[chip_idx];
	स्थिर अक्षर *prपूर्णांक_name = "3c59x";
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा eisa_device *edev = शून्य;

	अगर (!prपूर्णांकed_version) अणु
		pr_info("%s", version);
		prपूर्णांकed_version = 1;
	पूर्ण

	अगर (gendev) अणु
		अगर ((pdev = DEVICE_PCI(gendev))) अणु
			prपूर्णांक_name = pci_name(pdev);
		पूर्ण

		अगर ((edev = DEVICE_EISA(gendev))) अणु
			prपूर्णांक_name = dev_name(&edev->dev);
		पूर्ण
	पूर्ण

	dev = alloc_etherdev(माप(*vp));
	retval = -ENOMEM;
	अगर (!dev)
		जाओ out;

	SET_NETDEV_DEV(dev, gendev);
	vp = netdev_priv(dev);

	option = global_options;

	/* The lower four bits are the media type. */
	अगर (dev->mem_start) अणु
		/*
		 * The 'options' param is passed in as the third arg to the
		 * LILO 'ether=' argument क्रम non-modular use
		 */
		option = dev->mem_start;
	पूर्ण
	अन्यथा अगर (card_idx < MAX_UNITS) अणु
		अगर (options[card_idx] >= 0)
			option = options[card_idx];
	पूर्ण

	अगर (option > 0) अणु
		अगर (option & 0x8000)
			vortex_debug = 7;
		अगर (option & 0x4000)
			vortex_debug = 2;
		अगर (option & 0x0400)
			vp->enable_wol = 1;
	पूर्ण

	prपूर्णांक_info = (vortex_debug > 1);
	अगर (prपूर्णांक_info)
		pr_info("See Documentation/networking/device_drivers/ethernet/3com/vortex.rst\n");

	pr_info("%s: 3Com %s %s at %p.\n",
	       prपूर्णांक_name,
	       pdev ? "PCI" : "EISA",
	       vci->name,
	       ioaddr);

	dev->base_addr = (अचिन्हित दीर्घ)ioaddr;
	dev->irq = irq;
	dev->mtu = mtu;
	vp->ioaddr = ioaddr;
	vp->large_frames = mtu > 1500;
	vp->drv_flags = vci->drv_flags;
	vp->has_nway = (vci->drv_flags & HAS_NWAY) ? 1 : 0;
	vp->io_size = vci->io_size;
	vp->card_idx = card_idx;
	vp->winकरोw = -1;

	/* module list only क्रम Compaq device */
	अगर (gendev == शून्य) अणु
		compaq_net_device = dev;
	पूर्ण

	/* PCI-only startup logic */
	अगर (pdev) अणु
		/* enable bus-mastering अगर necessary */
		अगर (vci->flags & PCI_USES_MASTER)
			pci_set_master(pdev);

		अगर (vci->drv_flags & IS_VORTEX) अणु
			u8 pci_latency;
			u8 new_latency = 248;

			/* Check the PCI latency value.  On the 3c590 series the latency समयr
			   must be set to the maximum value to aव्योम data corruption that occurs
			   when the समयr expires during a transfer.  This bug exists the Vortex
			   chip only. */
			pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &pci_latency);
			अगर (pci_latency < new_latency) अणु
				pr_info("%s: Overriding PCI latency timer (CFLT) setting of %d, new value is %d.\n",
					prपूर्णांक_name, pci_latency, new_latency);
				pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, new_latency);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_init(&vp->lock);
	spin_lock_init(&vp->mii_lock);
	spin_lock_init(&vp->winकरोw_lock);
	vp->gendev = gendev;
	vp->mii.dev = dev;
	vp->mii.mdio_पढ़ो = mdio_पढ़ो;
	vp->mii.mdio_ग_लिखो = mdio_ग_लिखो;
	vp->mii.phy_id_mask = 0x1f;
	vp->mii.reg_num_mask = 0x1f;

	/* Makes sure rings are at least 16 byte aligned. */
	vp->rx_ring = dma_alloc_coherent(gendev, माप(काष्ठा boom_rx_desc) * RX_RING_SIZE
					   + माप(काष्ठा boom_tx_desc) * TX_RING_SIZE,
					   &vp->rx_ring_dma, GFP_KERNEL);
	retval = -ENOMEM;
	अगर (!vp->rx_ring)
		जाओ मुक्त_device;

	vp->tx_ring = (काष्ठा boom_tx_desc *)(vp->rx_ring + RX_RING_SIZE);
	vp->tx_ring_dma = vp->rx_ring_dma + माप(काष्ठा boom_rx_desc) * RX_RING_SIZE;

	/* अगर we are a PCI driver, we store info in pdev->driver_data
	 * instead of a module list */
	अगर (pdev)
		pci_set_drvdata(pdev, dev);
	अगर (edev)
		eisa_set_drvdata(edev, dev);

	vp->media_override = 7;
	अगर (option >= 0) अणु
		vp->media_override = ((option & 7) == 2)  ?  0  :  option & 15;
		अगर (vp->media_override != 7)
			vp->medialock = 1;
		vp->full_duplex = (option & 0x200) ? 1 : 0;
		vp->bus_master = (option & 16) ? 1 : 0;
	पूर्ण

	अगर (global_full_duplex > 0)
		vp->full_duplex = 1;
	अगर (global_enable_wol > 0)
		vp->enable_wol = 1;

	अगर (card_idx < MAX_UNITS) अणु
		अगर (full_duplex[card_idx] > 0)
			vp->full_duplex = 1;
		अगर (flow_ctrl[card_idx] > 0)
			vp->flow_ctrl = 1;
		अगर (enable_wol[card_idx] > 0)
			vp->enable_wol = 1;
	पूर्ण

	vp->mii.क्रमce_media = vp->full_duplex;
	vp->options = option;
	/* Read the station address from the EEPROM. */
	अणु
		पूर्णांक base;

		अगर (vci->drv_flags & EEPROM_8BIT)
			base = 0x230;
		अन्यथा अगर (vci->drv_flags & EEPROM_OFFSET)
			base = EEPROM_Read + 0x30;
		अन्यथा
			base = EEPROM_Read;

		क्रम (i = 0; i < 0x40; i++) अणु
			पूर्णांक समयr;
			winकरोw_ग_लिखो16(vp, base + i, 0, Wn0EepromCmd);
			/* Pause क्रम at least 162 us. क्रम the पढ़ो to take place. */
			क्रम (समयr = 10; समयr >= 0; समयr--) अणु
				udelay(162);
				अगर ((winकरोw_पढ़ो16(vp, 0, Wn0EepromCmd) &
				     0x8000) == 0)
					अवरोध;
			पूर्ण
			eeprom[i] = winकरोw_पढ़ो16(vp, 0, Wn0EepromData);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < 0x18; i++)
		checksum ^= eeprom[i];
	checksum = (checksum ^ (checksum >> 8)) & 0xff;
	अगर (checksum != 0x00) अणु		/* Grrr, needless incompatible change 3Com. */
		जबतक (i < 0x21)
			checksum ^= eeprom[i++];
		checksum = (checksum ^ (checksum >> 8)) & 0xff;
	पूर्ण
	अगर ((checksum != 0x00) && !(vci->drv_flags & IS_TORNADO))
		pr_cont(" ***INVALID CHECKSUM %4.4x*** ", checksum);
	क्रम (i = 0; i < 3; i++)
		((__be16 *)dev->dev_addr)[i] = htons(eeprom[i + 10]);
	अगर (prपूर्णांक_info)
		pr_cont(" %pM", dev->dev_addr);
	/* Unक्रमtunately an all zero eeprom passes the checksum and this
	   माला_लो found in the wild in failure हालs. Crypto is hard 8) */
	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		retval = -EINVAL;
		pr_err("*** EEPROM MAC address is invalid.\n");
		जाओ मुक्त_ring;	/* With every pack */
	पूर्ण
	क्रम (i = 0; i < 6; i++)
		winकरोw_ग_लिखो8(vp, dev->dev_addr[i], 2, i);

	अगर (prपूर्णांक_info)
		pr_cont(", IRQ %d\n", dev->irq);
	/* Tell them about an invalid IRQ. */
	अगर (dev->irq <= 0 || dev->irq >= nr_irqs)
		pr_warn(" *** Warning: IRQ %d is unlikely to work! ***\n",
			dev->irq);

	step = (winकरोw_पढ़ो8(vp, 4, Wn4_NetDiag) & 0x1e) >> 1;
	अगर (prपूर्णांक_info) अणु
		pr_info("  product code %02x%02x rev %02x.%d date %02d-%02d-%02d\n",
			eeprom[6]&0xff, eeprom[6]>>8, eeprom[0x14],
			step, (eeprom[4]>>5) & 15, eeprom[4] & 31, eeprom[4]>>9);
	पूर्ण


	अगर (pdev && vci->drv_flags & HAS_CB_FNS) अणु
		अचिन्हित लघु n;

		vp->cb_fn_base = pci_iomap(pdev, 2, 0);
		अगर (!vp->cb_fn_base) अणु
			retval = -ENOMEM;
			जाओ मुक्त_ring;
		पूर्ण

		अगर (prपूर्णांक_info) अणु
			pr_info("%s: CardBus functions mapped %16.16llx->%p\n",
				prपूर्णांक_name,
				(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 2),
				vp->cb_fn_base);
		पूर्ण

		n = winकरोw_पढ़ो16(vp, 2, Wn2_ResetOptions) & ~0x4010;
		अगर (vp->drv_flags & INVERT_LED_PWR)
			n |= 0x10;
		अगर (vp->drv_flags & INVERT_MII_PWR)
			n |= 0x4000;
		winकरोw_ग_लिखो16(vp, n, 2, Wn2_ResetOptions);
		अगर (vp->drv_flags & WNO_XCVR_PWR) अणु
			winकरोw_ग_लिखो16(vp, 0x0800, 0, 0);
		पूर्ण
	पूर्ण

	/* Extract our inक्रमmation from the EEPROM data. */
	vp->info1 = eeprom[13];
	vp->info2 = eeprom[15];
	vp->capabilities = eeprom[16];

	अगर (vp->info1 & 0x8000) अणु
		vp->full_duplex = 1;
		अगर (prपूर्णांक_info)
			pr_info("Full duplex capable\n");
	पूर्ण

	अणु
		अटल स्थिर अक्षर * स्थिर ram_split[] = अणु"5:3", "3:1", "1:1", "3:5"पूर्ण;
		अचिन्हित पूर्णांक config;
		vp->available_media = winकरोw_पढ़ो16(vp, 3, Wn3_Options);
		अगर ((vp->available_media & 0xff) == 0)		/* Broken 3c916 */
			vp->available_media = 0x40;
		config = winकरोw_पढ़ो32(vp, 3, Wn3_Config);
		अगर (prपूर्णांक_info) अणु
			pr_debug("  Internal config register is %4.4x, transceivers %#x.\n",
				config, winकरोw_पढ़ो16(vp, 3, Wn3_Options));
			pr_info("  %dK %s-wide RAM %s Rx:Tx split, %s%s interface.\n",
				   8 << RAM_SIZE(config),
				   RAM_WIDTH(config) ? "word" : "byte",
				   ram_split[RAM_SPLIT(config)],
				   AUTOSELECT(config) ? "autoselect/" : "",
				   XCVR(config) > XCVR_ExtMII ? "<invalid transceiver>" :
				   media_tbl[XCVR(config)].name);
		पूर्ण
		vp->शेष_media = XCVR(config);
		अगर (vp->शेष_media == XCVR_NWAY)
			vp->has_nway = 1;
		vp->स्वतःselect = AUTOSELECT(config);
	पूर्ण

	अगर (vp->media_override != 7) अणु
		pr_info("%s:  Media override to transceiver type %d (%s).\n",
				prपूर्णांक_name, vp->media_override,
				media_tbl[vp->media_override].name);
		dev->अगर_port = vp->media_override;
	पूर्ण अन्यथा
		dev->अगर_port = vp->शेष_media;

	अगर ((vp->available_media & 0x40) || (vci->drv_flags & HAS_NWAY) ||
		dev->अगर_port == XCVR_MII || dev->अगर_port == XCVR_NWAY) अणु
		पूर्णांक phy, phy_idx = 0;
		mii_preamble_required++;
		अगर (vp->drv_flags & EXTRA_PREAMBLE)
			mii_preamble_required++;
		mdio_sync(vp, 32);
		mdio_पढ़ो(dev, 24, MII_BMSR);
		क्रम (phy = 0; phy < 32 && phy_idx < 1; phy++) अणु
			पूर्णांक mii_status, phyx;

			/*
			 * For the 3c905CX we look at index 24 first, because it bogusly
			 * reports an बाह्यal PHY at all indices
			 */
			अगर (phy == 0)
				phyx = 24;
			अन्यथा अगर (phy <= 24)
				phyx = phy - 1;
			अन्यथा
				phyx = phy;
			mii_status = mdio_पढ़ो(dev, phyx, MII_BMSR);
			अगर (mii_status  &&  mii_status != 0xffff) अणु
				vp->phys[phy_idx++] = phyx;
				अगर (prपूर्णांक_info) अणु
					pr_info("  MII transceiver found at address %d, status %4x.\n",
						phyx, mii_status);
				पूर्ण
				अगर ((mii_status & 0x0040) == 0)
					mii_preamble_required++;
			पूर्ण
		पूर्ण
		mii_preamble_required--;
		अगर (phy_idx == 0) अणु
			pr_warn("  ***WARNING*** No MII transceivers found!\n");
			vp->phys[0] = 24;
		पूर्ण अन्यथा अणु
			vp->advertising = mdio_पढ़ो(dev, vp->phys[0], MII_ADVERTISE);
			अगर (vp->full_duplex) अणु
				/* Only advertise the FD media types. */
				vp->advertising &= ~0x02A0;
				mdio_ग_लिखो(dev, vp->phys[0], 4, vp->advertising);
			पूर्ण
		पूर्ण
		vp->mii.phy_id = vp->phys[0];
	पूर्ण

	अगर (vp->capabilities & CapBusMaster) अणु
		vp->full_bus_master_tx = 1;
		अगर (prपूर्णांक_info) अणु
			pr_info("  Enabling bus-master transmits and %s receives.\n",
			(vp->info2 & 1) ? "early" : "whole-frame" );
		पूर्ण
		vp->full_bus_master_rx = (vp->info2 & 1) ? 1 : 2;
		vp->bus_master = 0;		/* AKPM: vortex only */
	पूर्ण

	/* The 3c59x-specअगरic entries in the device काष्ठाure. */
	अगर (vp->full_bus_master_tx) अणु
		dev->netdev_ops = &boomrang_netdev_ops;
		/* Actually, it still should work with iommu. */
		अगर (card_idx < MAX_UNITS &&
		    ((hw_checksums[card_idx] == -1 && (vp->drv_flags & HAS_HWCKSM)) ||
				hw_checksums[card_idx] == 1)) अणु
			dev->features |= NETIF_F_IP_CSUM | NETIF_F_SG;
		पूर्ण
	पूर्ण अन्यथा
		dev->netdev_ops =  &vortex_netdev_ops;

	अगर (prपूर्णांक_info) अणु
		pr_info("%s: scatter/gather %sabled. h/w checksums %sabled\n",
				prपूर्णांक_name,
				(dev->features & NETIF_F_SG) ? "en":"dis",
				(dev->features & NETIF_F_IP_CSUM) ? "en":"dis");
	पूर्ण

	dev->ethtool_ops = &vortex_ethtool_ops;
	dev->watchकरोg_समयo = (watchकरोg * HZ) / 1000;

	अगर (pdev) अणु
		vp->pm_state_valid = 1;
		pci_save_state(pdev);
 		acpi_set_WOL(dev);
	पूर्ण
	retval = रेजिस्टर_netdev(dev);
	अगर (retval == 0)
		वापस 0;

मुक्त_ring:
	dma_मुक्त_coherent(&pdev->dev,
		माप(काष्ठा boom_rx_desc) * RX_RING_SIZE +
		माप(काष्ठा boom_tx_desc) * TX_RING_SIZE,
		vp->rx_ring, vp->rx_ring_dma);
मुक्त_device:
	मुक्त_netdev(dev);
	pr_err(PFX "vortex_probe1 fails.  Returns %d\n", retval);
out:
	वापस retval;
पूर्ण

अटल व्योम
issue_and_रुको(काष्ठा net_device *dev, पूर्णांक cmd)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	पूर्णांक i;

	ioग_लिखो16(cmd, ioaddr + EL3_CMD);
	क्रम (i = 0; i < 2000; i++) अणु
		अगर (!(ioपढ़ो16(ioaddr + EL3_STATUS) & CmdInProgress))
			वापस;
	पूर्ण

	/* OK, that didn't work.  Do it the slow way.  One second */
	क्रम (i = 0; i < 100000; i++) अणु
		अगर (!(ioपढ़ो16(ioaddr + EL3_STATUS) & CmdInProgress)) अणु
			अगर (vortex_debug > 1)
				pr_info("%s: command 0x%04x took %d usecs\n",
					   dev->name, cmd, i * 10);
			वापस;
		पूर्ण
		udelay(10);
	पूर्ण
	pr_err("%s: command 0x%04x did not complete! Status=0x%x\n",
			   dev->name, cmd, ioपढ़ो16(ioaddr + EL3_STATUS));
पूर्ण

अटल व्योम
vortex_set_duplex(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);

	pr_info("%s:  setting %s-duplex.\n",
		dev->name, (vp->full_duplex) ? "full" : "half");

	/* Set the full-duplex bit. */
	winकरोw_ग_लिखो16(vp,
		       ((vp->info1 & 0x8000) || vp->full_duplex ? 0x20 : 0) |
		       (vp->large_frames ? 0x40 : 0) |
		       ((vp->full_duplex && vp->flow_ctrl && vp->partner_flow_ctrl) ?
			0x100 : 0),
		       3, Wn3_MAC_Ctrl);
पूर्ण

अटल व्योम vortex_check_media(काष्ठा net_device *dev, अचिन्हित पूर्णांक init)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	अचिन्हित पूर्णांक ok_to_prपूर्णांक = 0;

	अगर (vortex_debug > 3)
		ok_to_prपूर्णांक = 1;

	अगर (mii_check_media(&vp->mii, ok_to_prपूर्णांक, init)) अणु
		vp->full_duplex = vp->mii.full_duplex;
		vortex_set_duplex(dev);
	पूर्ण अन्यथा अगर (init) अणु
		vortex_set_duplex(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक
vortex_up(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	अचिन्हित पूर्णांक config;
	पूर्णांक i, mii_reg5, err = 0;

	अगर (VORTEX_PCI(vp)) अणु
		pci_set_घातer_state(VORTEX_PCI(vp), PCI_D0);	/* Go active */
		अगर (vp->pm_state_valid)
			pci_restore_state(VORTEX_PCI(vp));
		err = pci_enable_device(VORTEX_PCI(vp));
		अगर (err) अणु
			pr_warn("%s: Could not enable device\n", dev->name);
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* Beक्रमe initializing select the active media port. */
	config = winकरोw_पढ़ो32(vp, 3, Wn3_Config);

	अगर (vp->media_override != 7) अणु
		pr_info("%s: Media override to transceiver %d (%s).\n",
			   dev->name, vp->media_override,
			   media_tbl[vp->media_override].name);
		dev->अगर_port = vp->media_override;
	पूर्ण अन्यथा अगर (vp->स्वतःselect) अणु
		अगर (vp->has_nway) अणु
			अगर (vortex_debug > 1)
				pr_info("%s: using NWAY device table, not %d\n",
								dev->name, dev->अगर_port);
			dev->अगर_port = XCVR_NWAY;
		पूर्ण अन्यथा अणु
			/* Find first available media type, starting with 100baseTx. */
			dev->अगर_port = XCVR_100baseTx;
			जबतक (! (vp->available_media & media_tbl[dev->अगर_port].mask))
				dev->अगर_port = media_tbl[dev->अगर_port].next;
			अगर (vortex_debug > 1)
				pr_info("%s: first available media type: %s\n",
					dev->name, media_tbl[dev->अगर_port].name);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->अगर_port = vp->शेष_media;
		अगर (vortex_debug > 1)
			pr_info("%s: using default media %s\n",
				dev->name, media_tbl[dev->अगर_port].name);
	पूर्ण

	समयr_setup(&vp->समयr, vortex_समयr, 0);
	mod_समयr(&vp->समयr, RUN_AT(media_tbl[dev->अगर_port].रुको));

	अगर (vortex_debug > 1)
		pr_debug("%s: Initial media type %s.\n",
			   dev->name, media_tbl[dev->अगर_port].name);

	vp->full_duplex = vp->mii.क्रमce_media;
	config = BFINS(config, dev->अगर_port, 20, 4);
	अगर (vortex_debug > 6)
		pr_debug("vortex_up(): writing 0x%x to InternalConfig\n", config);
	winकरोw_ग_लिखो32(vp, config, 3, Wn3_Config);

	अगर (dev->अगर_port == XCVR_MII || dev->अगर_port == XCVR_NWAY) अणु
		mdio_पढ़ो(dev, vp->phys[0], MII_BMSR);
		mii_reg5 = mdio_पढ़ो(dev, vp->phys[0], MII_LPA);
		vp->partner_flow_ctrl = ((mii_reg5 & 0x0400) != 0);
		vp->mii.full_duplex = vp->full_duplex;

		vortex_check_media(dev, 1);
	पूर्ण
	अन्यथा
		vortex_set_duplex(dev);

	issue_and_रुको(dev, TxReset);
	/*
	 * Don't reset the PHY - that upsets स्वतःnegotiation during DHCP operations.
	 */
	issue_and_रुको(dev, RxReset|0x04);


	ioग_लिखो16(SetStatusEnb | 0x00, ioaddr + EL3_CMD);

	अगर (vortex_debug > 1) अणु
		pr_debug("%s: vortex_up() irq %d media status %4.4x.\n",
			   dev->name, dev->irq, winकरोw_पढ़ो16(vp, 4, Wn4_Media));
	पूर्ण

	/* Set the station address and mask in winकरोw 2 each समय खोलोed. */
	क्रम (i = 0; i < 6; i++)
		winकरोw_ग_लिखो8(vp, dev->dev_addr[i], 2, i);
	क्रम (; i < 12; i+=2)
		winकरोw_ग_लिखो16(vp, 0, 2, i);

	अगर (vp->cb_fn_base) अणु
		अचिन्हित लघु n = winकरोw_पढ़ो16(vp, 2, Wn2_ResetOptions) & ~0x4010;
		अगर (vp->drv_flags & INVERT_LED_PWR)
			n |= 0x10;
		अगर (vp->drv_flags & INVERT_MII_PWR)
			n |= 0x4000;
		winकरोw_ग_लिखो16(vp, n, 2, Wn2_ResetOptions);
	पूर्ण

	अगर (dev->अगर_port == XCVR_10base2)
		/* Start the thinnet transceiver. We should really रुको 50ms...*/
		ioग_लिखो16(StartCoax, ioaddr + EL3_CMD);
	अगर (dev->अगर_port != XCVR_NWAY) अणु
		winकरोw_ग_लिखो16(vp,
			       (winकरोw_पढ़ो16(vp, 4, Wn4_Media) &
				~(Media_10TP|Media_SQE)) |
			       media_tbl[dev->अगर_port].media_bits,
			       4, Wn4_Media);
	पूर्ण

	/* Switch to the stats winकरोw, and clear all stats by पढ़ोing. */
	ioग_लिखो16(StatsDisable, ioaddr + EL3_CMD);
	क्रम (i = 0; i < 10; i++)
		winकरोw_पढ़ो8(vp, 6, i);
	winकरोw_पढ़ो16(vp, 6, 10);
	winकरोw_पढ़ो16(vp, 6, 12);
	/* New: On the Vortex we must also clear the BadSSD counter. */
	winकरोw_पढ़ो8(vp, 4, 12);
	/* ..and on the Boomerang we enable the extra statistics bits. */
	winकरोw_ग_लिखो16(vp, 0x0040, 4, Wn4_NetDiag);

	अगर (vp->full_bus_master_rx) अणु /* Boomerang bus master. */
		vp->cur_rx = 0;
		/* Initialize the RxEarly रेजिस्टर as recommended. */
		ioग_लिखो16(SetRxThreshold + (1536>>2), ioaddr + EL3_CMD);
		ioग_लिखो32(0x0020, ioaddr + PktStatus);
		ioग_लिखो32(vp->rx_ring_dma, ioaddr + UpListPtr);
	पूर्ण
	अगर (vp->full_bus_master_tx) अणु 		/* Boomerang bus master Tx. */
		vp->cur_tx = vp->dirty_tx = 0;
		अगर (vp->drv_flags & IS_BOOMERANG)
			ioग_लिखो8(PKT_BUF_SZ>>8, ioaddr + TxFreeThreshold); /* Room क्रम a packet. */
		/* Clear the Rx, Tx rings. */
		क्रम (i = 0; i < RX_RING_SIZE; i++)	/* AKPM: this is करोne in vortex_खोलो, too */
			vp->rx_ring[i].status = 0;
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			vp->tx_skbuff[i] = शून्य;
		ioग_लिखो32(0, ioaddr + DownListPtr);
	पूर्ण
	/* Set receiver mode: presumably accept b-हाल and phys addr only. */
	set_rx_mode(dev);
	/* enable 802.1q tagged frames */
	set_8021q_mode(dev, 1);
	ioग_लिखो16(StatsEnable, ioaddr + EL3_CMD); /* Turn on statistics. */

	ioग_लिखो16(RxEnable, ioaddr + EL3_CMD); /* Enable the receiver. */
	ioग_लिखो16(TxEnable, ioaddr + EL3_CMD); /* Enable transmitter. */
	/* Allow status bits to be seen. */
	vp->status_enable = SetStatusEnb | HostError|IntReq|StatsFull|TxComplete|
		(vp->full_bus_master_tx ? DownComplete : TxAvailable) |
		(vp->full_bus_master_rx ? UpComplete : RxComplete) |
		(vp->bus_master ? DMADone : 0);
	vp->पूर्णांकr_enable = SetIntrEnb | IntLatch | TxAvailable |
		(vp->full_bus_master_rx ? 0 : RxComplete) |
		StatsFull | HostError | TxComplete | IntReq
		| (vp->bus_master ? DMADone : 0) | UpComplete | DownComplete;
	ioग_लिखो16(vp->status_enable, ioaddr + EL3_CMD);
	/* Ack all pending events, and set active indicator mask. */
	ioग_लिखो16(AckIntr | IntLatch | TxAvailable | RxEarly | IntReq,
		 ioaddr + EL3_CMD);
	ioग_लिखो16(vp->पूर्णांकr_enable, ioaddr + EL3_CMD);
	अगर (vp->cb_fn_base)			/* The PCMCIA people are idiots.  */
		ioग_लिखो32(0x8000, vp->cb_fn_base + 4);
	netअगर_start_queue (dev);
	netdev_reset_queue(dev);
err_out:
	वापस err;
पूर्ण

अटल पूर्णांक
vortex_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	पूर्णांक i;
	पूर्णांक retval;
	dma_addr_t dma;

	/* Use the now-standard shared IRQ implementation. */
	अगर ((retval = request_irq(dev->irq, vortex_boomerang_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev))) अणु
		pr_err("%s: Could not reserve IRQ %d\n", dev->name, dev->irq);
		जाओ err;
	पूर्ण

	अगर (vp->full_bus_master_rx) अणु /* Boomerang bus master. */
		अगर (vortex_debug > 2)
			pr_debug("%s:  Filling in the Rx ring.\n", dev->name);
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			काष्ठा sk_buff *skb;
			vp->rx_ring[i].next = cpu_to_le32(vp->rx_ring_dma + माप(काष्ठा boom_rx_desc) * (i+1));
			vp->rx_ring[i].status = 0;	/* Clear complete bit. */
			vp->rx_ring[i].length = cpu_to_le32(PKT_BUF_SZ | LAST_FRAG);

			skb = __netdev_alloc_skb(dev, PKT_BUF_SZ + NET_IP_ALIGN,
						 GFP_KERNEL);
			vp->rx_skbuff[i] = skb;
			अगर (skb == शून्य)
				अवरोध;			/* Bad news!  */

			skb_reserve(skb, NET_IP_ALIGN);	/* Align IP on 16 byte boundaries */
			dma = dma_map_single(vp->gendev, skb->data,
					     PKT_BUF_SZ, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(vp->gendev, dma))
				अवरोध;
			vp->rx_ring[i].addr = cpu_to_le32(dma);
		पूर्ण
		अगर (i != RX_RING_SIZE) अणु
			pr_emerg("%s: no memory for rx ring\n", dev->name);
			retval = -ENOMEM;
			जाओ err_मुक्त_skb;
		पूर्ण
		/* Wrap the ring. */
		vp->rx_ring[i-1].next = cpu_to_le32(vp->rx_ring_dma);
	पूर्ण

	retval = vortex_up(dev);
	अगर (!retval)
		जाओ out;

err_मुक्त_skb:
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		अगर (vp->rx_skbuff[i]) अणु
			dev_kमुक्त_skb(vp->rx_skbuff[i]);
			vp->rx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण
	मुक्त_irq(dev->irq, dev);
err:
	अगर (vortex_debug > 1)
		pr_err("%s: vortex_open() fails: returning %d\n", dev->name, retval);
out:
	वापस retval;
पूर्ण

अटल व्योम
vortex_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा vortex_निजी *vp = from_समयr(vp, t, समयr);
	काष्ठा net_device *dev = vp->mii.dev;
	व्योम __iomem *ioaddr = vp->ioaddr;
	पूर्णांक next_tick = 60*HZ;
	पूर्णांक ok = 0;
	पूर्णांक media_status;

	अगर (vortex_debug > 2) अणु
		pr_debug("%s: Media selection timer tick happened, %s.\n",
			   dev->name, media_tbl[dev->अगर_port].name);
		pr_debug("dev->watchdog_timeo=%d\n", dev->watchकरोg_समयo);
	पूर्ण

	media_status = winकरोw_पढ़ो16(vp, 4, Wn4_Media);
	चयन (dev->अगर_port) अणु
	हाल XCVR_10baseT:  हाल XCVR_100baseTx:  हाल XCVR_100baseFx:
		अगर (media_status & Media_LnkBeat) अणु
			netअगर_carrier_on(dev);
			ok = 1;
			अगर (vortex_debug > 1)
				pr_debug("%s: Media %s has link beat, %x.\n",
					   dev->name, media_tbl[dev->अगर_port].name, media_status);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(dev);
			अगर (vortex_debug > 1) अणु
				pr_debug("%s: Media %s has no link beat, %x.\n",
					   dev->name, media_tbl[dev->अगर_port].name, media_status);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल XCVR_MII: हाल XCVR_NWAY:
		अणु
			ok = 1;
			vortex_check_media(dev, 0);
		पूर्ण
		अवरोध;
	  शेष:					/* Other media types handled by Tx समयouts. */
		अगर (vortex_debug > 1)
		  pr_debug("%s: Media %s has no indication, %x.\n",
				 dev->name, media_tbl[dev->अगर_port].name, media_status);
		ok = 1;
	पूर्ण

	अगर (dev->flags & IFF_SLAVE || !netअगर_carrier_ok(dev))
		next_tick = 5*HZ;

	अगर (vp->medialock)
		जाओ leave_media_alone;

	अगर (!ok) अणु
		अचिन्हित पूर्णांक config;

		spin_lock_irq(&vp->lock);

		करो अणु
			dev->अगर_port = media_tbl[dev->अगर_port].next;
		पूर्ण जबतक ( ! (vp->available_media & media_tbl[dev->अगर_port].mask));
		अगर (dev->अगर_port == XCVR_Default) अणु /* Go back to शेष. */
		  dev->अगर_port = vp->शेष_media;
		  अगर (vortex_debug > 1)
			pr_debug("%s: Media selection failing, using default %s port.\n",
				   dev->name, media_tbl[dev->अगर_port].name);
		पूर्ण अन्यथा अणु
			अगर (vortex_debug > 1)
				pr_debug("%s: Media selection failed, now trying %s port.\n",
					   dev->name, media_tbl[dev->अगर_port].name);
			next_tick = media_tbl[dev->अगर_port].रुको;
		पूर्ण
		winकरोw_ग_लिखो16(vp,
			       (media_status & ~(Media_10TP|Media_SQE)) |
			       media_tbl[dev->अगर_port].media_bits,
			       4, Wn4_Media);

		config = winकरोw_पढ़ो32(vp, 3, Wn3_Config);
		config = BFINS(config, dev->अगर_port, 20, 4);
		winकरोw_ग_लिखो32(vp, config, 3, Wn3_Config);

		ioग_लिखो16(dev->अगर_port == XCVR_10base2 ? StartCoax : StopCoax,
			 ioaddr + EL3_CMD);
		अगर (vortex_debug > 1)
			pr_debug("wrote 0x%08x to Wn3_Config\n", config);
		/* AKPM: FIXME: Should reset Rx & Tx here.  P60 of 3c90xc.pdf */

		spin_unlock_irq(&vp->lock);
	पूर्ण

leave_media_alone:
	अगर (vortex_debug > 2)
	  pr_debug("%s: Media selection timer finished, %s.\n",
			 dev->name, media_tbl[dev->अगर_port].name);

	mod_समयr(&vp->समयr, RUN_AT(next_tick));
	अगर (vp->deferred)
		ioग_लिखो16(FakeIntr, ioaddr + EL3_CMD);
पूर्ण

अटल व्योम vortex_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;

	pr_err("%s: transmit timed out, tx_status %2.2x status %4.4x.\n",
		   dev->name, ioपढ़ो8(ioaddr + TxStatus),
		   ioपढ़ो16(ioaddr + EL3_STATUS));
	pr_err("  diagnostics: net %04x media %04x dma %08x fifo %04x\n",
			winकरोw_पढ़ो16(vp, 4, Wn4_NetDiag),
			winकरोw_पढ़ो16(vp, 4, Wn4_Media),
			ioपढ़ो32(ioaddr + PktStatus),
			winकरोw_पढ़ो16(vp, 4, Wn4_FIFODiag));
	/* Slight code bloat to be user मित्रly. */
	अगर ((ioपढ़ो8(ioaddr + TxStatus) & 0x88) == 0x88)
		pr_err("%s: Transmitter encountered 16 collisions --"
			   " network cable problem?\n", dev->name);
	अगर (ioपढ़ो16(ioaddr + EL3_STATUS) & IntLatch) अणु
		pr_err("%s: Interrupt posted but not delivered --"
			   " IRQ blocked by another device?\n", dev->name);
		/* Bad idea here.. but we might as well handle a few events. */
		vortex_boomerang_पूर्णांकerrupt(dev->irq, dev);
	पूर्ण

	अगर (vortex_debug > 0)
		dump_tx_ring(dev);

	issue_and_रुको(dev, TxReset);

	dev->stats.tx_errors++;
	अगर (vp->full_bus_master_tx) अणु
		pr_debug("%s: Resetting the Tx ring pointer.\n", dev->name);
		अगर (vp->cur_tx - vp->dirty_tx > 0  &&  ioपढ़ो32(ioaddr + DownListPtr) == 0)
			ioग_लिखो32(vp->tx_ring_dma + (vp->dirty_tx % TX_RING_SIZE) * माप(काष्ठा boom_tx_desc),
				 ioaddr + DownListPtr);
		अगर (vp->cur_tx - vp->dirty_tx < TX_RING_SIZE) अणु
			netअगर_wake_queue (dev);
			netdev_reset_queue (dev);
		पूर्ण
		अगर (vp->drv_flags & IS_BOOMERANG)
			ioग_लिखो8(PKT_BUF_SZ>>8, ioaddr + TxFreeThreshold);
		ioग_लिखो16(DownUnstall, ioaddr + EL3_CMD);
	पूर्ण अन्यथा अणु
		dev->stats.tx_dropped++;
		netअगर_wake_queue(dev);
		netdev_reset_queue(dev);
	पूर्ण
	/* Issue Tx Enable */
	ioग_लिखो16(TxEnable, ioaddr + EL3_CMD);
	netअगर_trans_update(dev); /* prevent tx समयout */
पूर्ण

/*
 * Handle uncommon पूर्णांकerrupt sources.  This is a separate routine to minimize
 * the cache impact.
 */
अटल व्योम
vortex_error(काष्ठा net_device *dev, पूर्णांक status)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	पूर्णांक करो_tx_reset = 0, reset_mask = 0;
	अचिन्हित अक्षर tx_status = 0;

	अगर (vortex_debug > 2) अणु
		pr_err("%s: vortex_error(), status=0x%x\n", dev->name, status);
	पूर्ण

	अगर (status & TxComplete) अणु			/* Really "TxError" क्रम us. */
		tx_status = ioपढ़ो8(ioaddr + TxStatus);
		/* Presumably a tx-समयout. We must merely re-enable. */
		अगर (vortex_debug > 2 ||
		    (tx_status != 0x88 && vortex_debug > 0)) अणु
			pr_err("%s: Transmit error, Tx status register %2.2x.\n",
				   dev->name, tx_status);
			अगर (tx_status == 0x82) अणु
				pr_err("Probably a duplex mismatch.  See "
						"Documentation/networking/device_drivers/ethernet/3com/vortex.rst\n");
			पूर्ण
			dump_tx_ring(dev);
		पूर्ण
		अगर (tx_status & 0x14)  dev->stats.tx_fअगरo_errors++;
		अगर (tx_status & 0x38)  dev->stats.tx_पातed_errors++;
		अगर (tx_status & 0x08)  vp->xstats.tx_max_collisions++;
		ioग_लिखो8(0, ioaddr + TxStatus);
		अगर (tx_status & 0x30) अणु			/* txJabber or txUnderrun */
			करो_tx_reset = 1;
		पूर्ण अन्यथा अगर ((tx_status & 0x08) && (vp->drv_flags & MAX_COLLISION_RESET))  अणु	/* maxCollisions */
			करो_tx_reset = 1;
			reset_mask = 0x0108;		/* Reset पूर्णांकerface logic, but not करोwnload logic */
		पूर्ण अन्यथा अणु				/* Merely re-enable the transmitter. */
			ioग_लिखो16(TxEnable, ioaddr + EL3_CMD);
		पूर्ण
	पूर्ण

	अगर (status & RxEarly)				/* Rx early is unused. */
		ioग_लिखो16(AckIntr | RxEarly, ioaddr + EL3_CMD);

	अगर (status & StatsFull) अणु			/* Empty statistics. */
		अटल पूर्णांक DoneDidThat;
		अगर (vortex_debug > 4)
			pr_debug("%s: Updating stats.\n", dev->name);
		update_stats(ioaddr, dev);
		/* HACK: Disable statistics as an पूर्णांकerrupt source. */
		/* This occurs when we have the wrong media type! */
		अगर (DoneDidThat == 0  &&
			ioपढ़ो16(ioaddr + EL3_STATUS) & StatsFull) अणु
			pr_warn("%s: Updating statistics failed, disabling stats as an interrupt source\n",
				dev->name);
			ioग_लिखो16(SetIntrEnb |
				  (winकरोw_पढ़ो16(vp, 5, 10) & ~StatsFull),
				  ioaddr + EL3_CMD);
			vp->पूर्णांकr_enable &= ~StatsFull;
			DoneDidThat++;
		पूर्ण
	पूर्ण
	अगर (status & IntReq) अणु		/* Restore all पूर्णांकerrupt sources.  */
		ioग_लिखो16(vp->status_enable, ioaddr + EL3_CMD);
		ioग_लिखो16(vp->पूर्णांकr_enable, ioaddr + EL3_CMD);
	पूर्ण
	अगर (status & HostError) अणु
		u16 fअगरo_diag;
		fअगरo_diag = winकरोw_पढ़ो16(vp, 4, Wn4_FIFODiag);
		pr_err("%s: Host error, FIFO diagnostic register %4.4x.\n",
			   dev->name, fअगरo_diag);
		/* Adapter failure requires Tx/Rx reset and reinit. */
		अगर (vp->full_bus_master_tx) अणु
			पूर्णांक bus_status = ioपढ़ो32(ioaddr + PktStatus);
			/* 0x80000000 PCI master पात. */
			/* 0x40000000 PCI target पात. */
			अगर (vortex_debug)
				pr_err("%s: PCI bus error, bus status %8.8x\n", dev->name, bus_status);

			/* In this हाल, blow the card away */
			/* Must not enter D3 or we can't legally issue the reset! */
			vortex_करोwn(dev, 0);
			issue_and_रुको(dev, TotalReset | 0xff);
			vortex_up(dev);		/* AKPM: bug.  vortex_up() assumes that the rx ring is full. It may not be. */
		पूर्ण अन्यथा अगर (fअगरo_diag & 0x0400)
			करो_tx_reset = 1;
		अगर (fअगरo_diag & 0x3000) अणु
			/* Reset Rx fअगरo and upload logic */
			issue_and_रुको(dev, RxReset|0x07);
			/* Set the Rx filter to the current state. */
			set_rx_mode(dev);
			/* enable 802.1q VLAN tagged frames */
			set_8021q_mode(dev, 1);
			ioग_लिखो16(RxEnable, ioaddr + EL3_CMD); /* Re-enable the receiver. */
			ioग_लिखो16(AckIntr | HostError, ioaddr + EL3_CMD);
		पूर्ण
	पूर्ण

	अगर (करो_tx_reset) अणु
		issue_and_रुको(dev, TxReset|reset_mask);
		ioग_लिखो16(TxEnable, ioaddr + EL3_CMD);
		अगर (!vp->full_bus_master_tx)
			netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

अटल netdev_tx_t
vortex_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	पूर्णांक skblen = skb->len;

	/* Put out the द्विगुनword header... */
	ioग_लिखो32(skb->len, ioaddr + TX_FIFO);
	अगर (vp->bus_master) अणु
		/* Set the bus-master controller to transfer the packet. */
		पूर्णांक len = (skb->len + 3) & ~3;
		vp->tx_skb_dma = dma_map_single(vp->gendev, skb->data, len,
						DMA_TO_DEVICE);
		अगर (dma_mapping_error(vp->gendev, vp->tx_skb_dma)) अणु
			dev_kमुक्त_skb_any(skb);
			dev->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण

		spin_lock_irq(&vp->winकरोw_lock);
		winकरोw_set(vp, 7);
		ioग_लिखो32(vp->tx_skb_dma, ioaddr + Wn7_MasterAddr);
		ioग_लिखो16(len, ioaddr + Wn7_MasterLen);
		spin_unlock_irq(&vp->winकरोw_lock);
		vp->tx_skb = skb;
		skb_tx_बारtamp(skb);
		ioग_लिखो16(StartDMADown, ioaddr + EL3_CMD);
		/* netअगर_wake_queue() will be called at the DMADone पूर्णांकerrupt. */
	पूर्ण अन्यथा अणु
		/* ... and the packet rounded to a द्विगुनword. */
		skb_tx_बारtamp(skb);
		ioग_लिखो32_rep(ioaddr + TX_FIFO, skb->data, (skb->len + 3) >> 2);
		dev_consume_skb_any (skb);
		अगर (ioपढ़ो16(ioaddr + TxFree) > 1536) अणु
			netअगर_start_queue (dev);	/* AKPM: redundant? */
		पूर्ण अन्यथा अणु
			/* Interrupt us when the FIFO has room क्रम max-sized packet. */
			netअगर_stop_queue(dev);
			ioग_लिखो16(SetTxThreshold + (1536>>2), ioaddr + EL3_CMD);
		पूर्ण
	पूर्ण

	netdev_sent_queue(dev, skblen);

	/* Clear the Tx status stack. */
	अणु
		पूर्णांक tx_status;
		पूर्णांक i = 32;

		जबतक (--i > 0	&&	(tx_status = ioपढ़ो8(ioaddr + TxStatus)) > 0) अणु
			अगर (tx_status & 0x3C) अणु		/* A Tx-disabling error occurred.  */
				अगर (vortex_debug > 2)
				  pr_debug("%s: Tx error, status %2.2x.\n",
						 dev->name, tx_status);
				अगर (tx_status & 0x04) dev->stats.tx_fअगरo_errors++;
				अगर (tx_status & 0x38) dev->stats.tx_पातed_errors++;
				अगर (tx_status & 0x30) अणु
					issue_and_रुको(dev, TxReset);
				पूर्ण
				ioग_लिखो16(TxEnable, ioaddr + EL3_CMD);
			पूर्ण
			ioग_लिखो8(0x00, ioaddr + TxStatus); /* Pop the status stack. */
		पूर्ण
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t
boomerang_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	/* Calculate the next Tx descriptor entry. */
	पूर्णांक entry = vp->cur_tx % TX_RING_SIZE;
	पूर्णांक skblen = skb->len;
	काष्ठा boom_tx_desc *prev_entry = &vp->tx_ring[(vp->cur_tx-1) % TX_RING_SIZE];
	अचिन्हित दीर्घ flags;
	dma_addr_t dma_addr;

	अगर (vortex_debug > 6) अणु
		pr_debug("boomerang_start_xmit()\n");
		pr_debug("%s: Trying to send a packet, Tx index %d.\n",
			   dev->name, vp->cur_tx);
	पूर्ण

	/*
	 * We can't allow a recursion from our पूर्णांकerrupt handler back पूर्णांकo the
	 * tx routine, as they take the same spin lock, and that causes
	 * deadlock.  Just वापस NETDEV_TX_BUSY and let the stack try again in
	 * a bit
	 */
	अगर (vp->handling_irq)
		वापस NETDEV_TX_BUSY;

	अगर (vp->cur_tx - vp->dirty_tx >= TX_RING_SIZE) अणु
		अगर (vortex_debug > 0)
			pr_warn("%s: BUG! Tx Ring full, refusing to send buffer\n",
				dev->name);
		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	vp->tx_skbuff[entry] = skb;

	vp->tx_ring[entry].next = 0;
#अगर DO_ZEROCOPY
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
			vp->tx_ring[entry].status = cpu_to_le32(skb->len | TxIntrUploaded);
	अन्यथा
			vp->tx_ring[entry].status = cpu_to_le32(skb->len | TxIntrUploaded | AddTCPChksum | AddUDPChksum);

	अगर (!skb_shinfo(skb)->nr_frags) अणु
		dma_addr = dma_map_single(vp->gendev, skb->data, skb->len,
					  DMA_TO_DEVICE);
		अगर (dma_mapping_error(vp->gendev, dma_addr))
			जाओ out_dma_err;

		vp->tx_ring[entry].frag[0].addr = cpu_to_le32(dma_addr);
		vp->tx_ring[entry].frag[0].length = cpu_to_le32(skb->len | LAST_FRAG);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		dma_addr = dma_map_single(vp->gendev, skb->data,
					  skb_headlen(skb), DMA_TO_DEVICE);
		अगर (dma_mapping_error(vp->gendev, dma_addr))
			जाओ out_dma_err;

		vp->tx_ring[entry].frag[0].addr = cpu_to_le32(dma_addr);
		vp->tx_ring[entry].frag[0].length = cpu_to_le32(skb_headlen(skb));

		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

			dma_addr = skb_frag_dma_map(vp->gendev, frag,
						    0,
						    skb_frag_size(frag),
						    DMA_TO_DEVICE);
			अगर (dma_mapping_error(vp->gendev, dma_addr)) अणु
				क्रम(i = i-1; i >= 0; i--)
					dma_unmap_page(vp->gendev,
						       le32_to_cpu(vp->tx_ring[entry].frag[i+1].addr),
						       le32_to_cpu(vp->tx_ring[entry].frag[i+1].length),
						       DMA_TO_DEVICE);

				dma_unmap_single(vp->gendev,
						 le32_to_cpu(vp->tx_ring[entry].frag[0].addr),
						 le32_to_cpu(vp->tx_ring[entry].frag[0].length),
						 DMA_TO_DEVICE);

				जाओ out_dma_err;
			पूर्ण

			vp->tx_ring[entry].frag[i+1].addr =
						cpu_to_le32(dma_addr);

			अगर (i == skb_shinfo(skb)->nr_frags-1)
					vp->tx_ring[entry].frag[i+1].length = cpu_to_le32(skb_frag_size(frag)|LAST_FRAG);
			अन्यथा
					vp->tx_ring[entry].frag[i+1].length = cpu_to_le32(skb_frag_size(frag));
		पूर्ण
	पूर्ण
#अन्यथा
	dma_addr = dma_map_single(vp->gendev, skb->data, skb->len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(vp->gendev, dma_addr))
		जाओ out_dma_err;
	vp->tx_ring[entry].addr = cpu_to_le32(dma_addr);
	vp->tx_ring[entry].length = cpu_to_le32(skb->len | LAST_FRAG);
	vp->tx_ring[entry].status = cpu_to_le32(skb->len | TxIntrUploaded);
#पूर्ण_अगर

	spin_lock_irqsave(&vp->lock, flags);
	/* Wait क्रम the stall to complete. */
	issue_and_रुको(dev, DownStall);
	prev_entry->next = cpu_to_le32(vp->tx_ring_dma + entry * माप(काष्ठा boom_tx_desc));
	अगर (ioपढ़ो32(ioaddr + DownListPtr) == 0) अणु
		ioग_लिखो32(vp->tx_ring_dma + entry * माप(काष्ठा boom_tx_desc), ioaddr + DownListPtr);
		vp->queued_packet++;
	पूर्ण

	vp->cur_tx++;
	netdev_sent_queue(dev, skblen);

	अगर (vp->cur_tx - vp->dirty_tx > TX_RING_SIZE - 1) अणु
		netअगर_stop_queue (dev);
	पूर्ण अन्यथा अणु					/* Clear previous पूर्णांकerrupt enable. */
#अगर defined(tx_पूर्णांकerrupt_mitigation)
		/* Dubious. If in boomeang_पूर्णांकerrupt "faster" cyclone अगरdef
		 * were selected, this would corrupt DN_COMPLETE. No?
		 */
		prev_entry->status &= cpu_to_le32(~TxIntrUploaded);
#पूर्ण_अगर
	पूर्ण
	skb_tx_बारtamp(skb);
	ioग_लिखो16(DownUnstall, ioaddr + EL3_CMD);
	spin_unlock_irqrestore(&vp->lock, flags);
out:
	वापस NETDEV_TX_OK;
out_dma_err:
	dev_err(vp->gendev, "Error mapping dma buffer\n");
	जाओ out;
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */

/*
 * This is the ISR क्रम the vortex series chips.
 * full_bus_master_tx == 0 && full_bus_master_rx == 0
 */

अटल irqवापस_t
_vortex_पूर्णांकerrupt(पूर्णांक irq, काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr;
	पूर्णांक status;
	पूर्णांक work_करोne = max_पूर्णांकerrupt_work;
	पूर्णांक handled = 0;
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;

	ioaddr = vp->ioaddr;

	status = ioपढ़ो16(ioaddr + EL3_STATUS);

	अगर (vortex_debug > 6)
		pr_debug("vortex_interrupt(). status=0x%4x\n", status);

	अगर ((status & IntLatch) == 0)
		जाओ handler_निकास;		/* No पूर्णांकerrupt: shared IRQs cause this */
	handled = 1;

	अगर (status & IntReq) अणु
		status |= vp->deferred;
		vp->deferred = 0;
	पूर्ण

	अगर (status == 0xffff)		/* h/w no दीर्घer present (hotplug)? */
		जाओ handler_निकास;

	अगर (vortex_debug > 4)
		pr_debug("%s: interrupt, status %4.4x, latency %d ticks.\n",
			   dev->name, status, ioपढ़ो8(ioaddr + Timer));

	spin_lock(&vp->winकरोw_lock);
	winकरोw_set(vp, 7);

	करो अणु
		अगर (vortex_debug > 5)
				pr_debug("%s: In interrupt loop, status %4.4x.\n",
					   dev->name, status);
		अगर (status & RxComplete)
			vortex_rx(dev);

		अगर (status & TxAvailable) अणु
			अगर (vortex_debug > 5)
				pr_debug("	TX room bit was handled.\n");
			/* There's room in the FIFO क्रम a full-sized packet. */
			ioग_लिखो16(AckIntr | TxAvailable, ioaddr + EL3_CMD);
			netअगर_wake_queue (dev);
		पूर्ण

		अगर (status & DMADone) अणु
			अगर (ioपढ़ो16(ioaddr + Wn7_MasterStatus) & 0x1000) अणु
				ioग_लिखो16(0x1000, ioaddr + Wn7_MasterStatus); /* Ack the event. */
				dma_unmap_single(vp->gendev, vp->tx_skb_dma, (vp->tx_skb->len + 3) & ~3, DMA_TO_DEVICE);
				pkts_compl++;
				bytes_compl += vp->tx_skb->len;
				dev_consume_skb_irq(vp->tx_skb); /* Release the transferred buffer */
				अगर (ioपढ़ो16(ioaddr + TxFree) > 1536) अणु
					/*
					 * AKPM: FIXME: I करोn't think we need this.  If the queue was stopped due to
					 * insufficient FIFO room, the TxAvailable test will succeed and call
					 * netअगर_wake_queue()
					 */
					netअगर_wake_queue(dev);
				पूर्ण अन्यथा अणु /* Interrupt when FIFO has room क्रम max-sized packet. */
					ioग_लिखो16(SetTxThreshold + (1536>>2), ioaddr + EL3_CMD);
					netअगर_stop_queue(dev);
				पूर्ण
			पूर्ण
		पूर्ण
		/* Check क्रम all uncommon पूर्णांकerrupts at once. */
		अगर (status & (HostError | RxEarly | StatsFull | TxComplete | IntReq)) अणु
			अगर (status == 0xffff)
				अवरोध;
			अगर (status & RxEarly)
				vortex_rx(dev);
			spin_unlock(&vp->winकरोw_lock);
			vortex_error(dev, status);
			spin_lock(&vp->winकरोw_lock);
			winकरोw_set(vp, 7);
		पूर्ण

		अगर (--work_करोne < 0) अणु
			pr_warn("%s: Too much work in interrupt, status %4.4x\n",
				dev->name, status);
			/* Disable all pending पूर्णांकerrupts. */
			करो अणु
				vp->deferred |= status;
				ioग_लिखो16(SetStatusEnb | (~vp->deferred & vp->status_enable),
					 ioaddr + EL3_CMD);
				ioग_लिखो16(AckIntr | (vp->deferred & 0x7ff), ioaddr + EL3_CMD);
			पूर्ण जबतक ((status = ioपढ़ो16(ioaddr + EL3_CMD)) & IntLatch);
			/* The समयr will reenable पूर्णांकerrupts. */
			mod_समयr(&vp->समयr, jअगरfies + 1*HZ);
			अवरोध;
		पूर्ण
		/* Acknowledge the IRQ. */
		ioग_लिखो16(AckIntr | IntReq | IntLatch, ioaddr + EL3_CMD);
	पूर्ण जबतक ((status = ioपढ़ो16(ioaddr + EL3_STATUS)) & (IntLatch | RxComplete));

	netdev_completed_queue(dev, pkts_compl, bytes_compl);
	spin_unlock(&vp->winकरोw_lock);

	अगर (vortex_debug > 4)
		pr_debug("%s: exiting interrupt, status %4.4x.\n",
			   dev->name, status);
handler_निकास:
	वापस IRQ_RETVAL(handled);
पूर्ण

/*
 * This is the ISR क्रम the boomerang series chips.
 * full_bus_master_tx == 1 && full_bus_master_rx == 1
 */

अटल irqवापस_t
_boomerang_पूर्णांकerrupt(पूर्णांक irq, काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr;
	पूर्णांक status;
	पूर्णांक work_करोne = max_पूर्णांकerrupt_work;
	पूर्णांक handled = 0;
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;

	ioaddr = vp->ioaddr;

	vp->handling_irq = 1;

	status = ioपढ़ो16(ioaddr + EL3_STATUS);

	अगर (vortex_debug > 6)
		pr_debug("boomerang_interrupt. status=0x%4x\n", status);

	अगर ((status & IntLatch) == 0)
		जाओ handler_निकास;		/* No पूर्णांकerrupt: shared IRQs can cause this */
	handled = 1;

	अगर (status == 0xffff) अणु		/* h/w no दीर्घer present (hotplug)? */
		अगर (vortex_debug > 1)
			pr_debug("boomerang_interrupt(1): status = 0xffff\n");
		जाओ handler_निकास;
	पूर्ण

	अगर (status & IntReq) अणु
		status |= vp->deferred;
		vp->deferred = 0;
	पूर्ण

	अगर (vortex_debug > 4)
		pr_debug("%s: interrupt, status %4.4x, latency %d ticks.\n",
			   dev->name, status, ioपढ़ो8(ioaddr + Timer));
	करो अणु
		अगर (vortex_debug > 5)
				pr_debug("%s: In interrupt loop, status %4.4x.\n",
					   dev->name, status);
		अगर (status & UpComplete) अणु
			ioग_लिखो16(AckIntr | UpComplete, ioaddr + EL3_CMD);
			अगर (vortex_debug > 5)
				pr_debug("boomerang_interrupt->boomerang_rx\n");
			boomerang_rx(dev);
		पूर्ण

		अगर (status & DownComplete) अणु
			अचिन्हित पूर्णांक dirty_tx = vp->dirty_tx;

			ioग_लिखो16(AckIntr | DownComplete, ioaddr + EL3_CMD);
			जबतक (vp->cur_tx - dirty_tx > 0) अणु
				पूर्णांक entry = dirty_tx % TX_RING_SIZE;
#अगर 1	/* AKPM: the latter is faster, but cyclone-only */
				अगर (ioपढ़ो32(ioaddr + DownListPtr) ==
					vp->tx_ring_dma + entry * माप(काष्ठा boom_tx_desc))
					अवरोध;			/* It still hasn't been processed. */
#अन्यथा
				अगर ((vp->tx_ring[entry].status & DN_COMPLETE) == 0)
					अवरोध;			/* It still hasn't been processed. */
#पूर्ण_अगर

				अगर (vp->tx_skbuff[entry]) अणु
					काष्ठा sk_buff *skb = vp->tx_skbuff[entry];
#अगर DO_ZEROCOPY
					पूर्णांक i;
					dma_unmap_single(vp->gendev,
							le32_to_cpu(vp->tx_ring[entry].frag[0].addr),
							le32_to_cpu(vp->tx_ring[entry].frag[0].length)&0xFFF,
							DMA_TO_DEVICE);

					क्रम (i=1; i<=skb_shinfo(skb)->nr_frags; i++)
							dma_unmap_page(vp->gendev,
											 le32_to_cpu(vp->tx_ring[entry].frag[i].addr),
											 le32_to_cpu(vp->tx_ring[entry].frag[i].length)&0xFFF,
											 DMA_TO_DEVICE);
#अन्यथा
					dma_unmap_single(vp->gendev,
						le32_to_cpu(vp->tx_ring[entry].addr), skb->len, DMA_TO_DEVICE);
#पूर्ण_अगर
					pkts_compl++;
					bytes_compl += skb->len;
					dev_consume_skb_irq(skb);
					vp->tx_skbuff[entry] = शून्य;
				पूर्ण अन्यथा अणु
					pr_debug("boomerang_interrupt: no skb!\n");
				पूर्ण
				/* dev->stats.tx_packets++;  Counted below. */
				dirty_tx++;
			पूर्ण
			vp->dirty_tx = dirty_tx;
			अगर (vp->cur_tx - dirty_tx <= TX_RING_SIZE - 1) अणु
				अगर (vortex_debug > 6)
					pr_debug("boomerang_interrupt: wake queue\n");
				netअगर_wake_queue (dev);
			पूर्ण
		पूर्ण

		/* Check क्रम all uncommon पूर्णांकerrupts at once. */
		अगर (status & (HostError | RxEarly | StatsFull | TxComplete | IntReq))
			vortex_error(dev, status);

		अगर (--work_करोne < 0) अणु
			pr_warn("%s: Too much work in interrupt, status %4.4x\n",
				dev->name, status);
			/* Disable all pending पूर्णांकerrupts. */
			करो अणु
				vp->deferred |= status;
				ioग_लिखो16(SetStatusEnb | (~vp->deferred & vp->status_enable),
					 ioaddr + EL3_CMD);
				ioग_लिखो16(AckIntr | (vp->deferred & 0x7ff), ioaddr + EL3_CMD);
			पूर्ण जबतक ((status = ioपढ़ो16(ioaddr + EL3_CMD)) & IntLatch);
			/* The समयr will reenable पूर्णांकerrupts. */
			mod_समयr(&vp->समयr, jअगरfies + 1*HZ);
			अवरोध;
		पूर्ण
		/* Acknowledge the IRQ. */
		ioग_लिखो16(AckIntr | IntReq | IntLatch, ioaddr + EL3_CMD);
		अगर (vp->cb_fn_base)			/* The PCMCIA people are idiots.  */
			ioग_लिखो32(0x8000, vp->cb_fn_base + 4);

	पूर्ण जबतक ((status = ioपढ़ो16(ioaddr + EL3_STATUS)) & IntLatch);
	netdev_completed_queue(dev, pkts_compl, bytes_compl);

	अगर (vortex_debug > 4)
		pr_debug("%s: exiting interrupt, status %4.4x.\n",
			   dev->name, status);
handler_निकास:
	vp->handling_irq = 0;
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल irqवापस_t
vortex_boomerang_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	irqवापस_t ret;

	spin_lock_irqsave(&vp->lock, flags);

	अगर (vp->full_bus_master_rx)
		ret = _boomerang_पूर्णांकerrupt(dev->irq, dev);
	अन्यथा
		ret = _vortex_पूर्णांकerrupt(dev->irq, dev);

	spin_unlock_irqrestore(&vp->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक vortex_rx(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	पूर्णांक i;
	लघु rx_status;

	अगर (vortex_debug > 5)
		pr_debug("vortex_rx(): status %4.4x, rx_status %4.4x.\n",
			   ioपढ़ो16(ioaddr+EL3_STATUS), ioपढ़ो16(ioaddr+RxStatus));
	जबतक ((rx_status = ioपढ़ो16(ioaddr + RxStatus)) > 0) अणु
		अगर (rx_status & 0x4000) अणु /* Error, update stats. */
			अचिन्हित अक्षर rx_error = ioपढ़ो8(ioaddr + RxErrors);
			अगर (vortex_debug > 2)
				pr_debug(" Rx error: status %2.2x.\n", rx_error);
			dev->stats.rx_errors++;
			अगर (rx_error & 0x01)  dev->stats.rx_over_errors++;
			अगर (rx_error & 0x02)  dev->stats.rx_length_errors++;
			अगर (rx_error & 0x04)  dev->stats.rx_frame_errors++;
			अगर (rx_error & 0x08)  dev->stats.rx_crc_errors++;
			अगर (rx_error & 0x10)  dev->stats.rx_length_errors++;
		पूर्ण अन्यथा अणु
			/* The packet length: up to 4.5K!. */
			पूर्णांक pkt_len = rx_status & 0x1fff;
			काष्ठा sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 5);
			अगर (vortex_debug > 4)
				pr_debug("Receiving packet size %d status %4.4x.\n",
					   pkt_len, rx_status);
			अगर (skb != शून्य) अणु
				skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
				/* 'skb_put()' poपूर्णांकs to the start of sk_buff data area. */
				अगर (vp->bus_master &&
					! (ioपढ़ो16(ioaddr + Wn7_MasterStatus) & 0x8000)) अणु
					dma_addr_t dma = dma_map_single(vp->gendev, skb_put(skb, pkt_len),
									   pkt_len, DMA_FROM_DEVICE);
					ioग_लिखो32(dma, ioaddr + Wn7_MasterAddr);
					ioग_लिखो16((skb->len + 3) & ~3, ioaddr + Wn7_MasterLen);
					ioग_लिखो16(StartDMAUp, ioaddr + EL3_CMD);
					जबतक (ioपढ़ो16(ioaddr + Wn7_MasterStatus) & 0x8000)
						;
					dma_unmap_single(vp->gendev, dma, pkt_len, DMA_FROM_DEVICE);
				पूर्ण अन्यथा अणु
					ioपढ़ो32_rep(ioaddr + RX_FIFO,
					             skb_put(skb, pkt_len),
						     (pkt_len + 3) >> 2);
				पूर्ण
				ioग_लिखो16(RxDiscard, ioaddr + EL3_CMD); /* Pop top Rx packet. */
				skb->protocol = eth_type_trans(skb, dev);
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				/* Wait a limited समय to go to next packet. */
				क्रम (i = 200; i >= 0; i--)
					अगर ( ! (ioपढ़ो16(ioaddr + EL3_STATUS) & CmdInProgress))
						अवरोध;
				जारी;
			पूर्ण अन्यथा अगर (vortex_debug > 0)
				pr_notice("%s: No memory to allocate a sk_buff of size %d.\n",
					dev->name, pkt_len);
			dev->stats.rx_dropped++;
		पूर्ण
		issue_and_रुको(dev, RxDiscard);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
boomerang_rx(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	पूर्णांक entry = vp->cur_rx % RX_RING_SIZE;
	व्योम __iomem *ioaddr = vp->ioaddr;
	पूर्णांक rx_status;
	पूर्णांक rx_work_limit = RX_RING_SIZE;

	अगर (vortex_debug > 5)
		pr_debug("boomerang_rx(): status %4.4x\n", ioपढ़ो16(ioaddr+EL3_STATUS));

	जबतक ((rx_status = le32_to_cpu(vp->rx_ring[entry].status)) & RxDComplete)अणु
		अगर (--rx_work_limit < 0)
			अवरोध;
		अगर (rx_status & RxDError) अणु /* Error, update stats. */
			अचिन्हित अक्षर rx_error = rx_status >> 16;
			अगर (vortex_debug > 2)
				pr_debug(" Rx error: status %2.2x.\n", rx_error);
			dev->stats.rx_errors++;
			अगर (rx_error & 0x01)  dev->stats.rx_over_errors++;
			अगर (rx_error & 0x02)  dev->stats.rx_length_errors++;
			अगर (rx_error & 0x04)  dev->stats.rx_frame_errors++;
			अगर (rx_error & 0x08)  dev->stats.rx_crc_errors++;
			अगर (rx_error & 0x10)  dev->stats.rx_length_errors++;
		पूर्ण अन्यथा अणु
			/* The packet length: up to 4.5K!. */
			पूर्णांक pkt_len = rx_status & 0x1fff;
			काष्ठा sk_buff *skb, *newskb;
			dma_addr_t newdma;
			dma_addr_t dma = le32_to_cpu(vp->rx_ring[entry].addr);

			अगर (vortex_debug > 4)
				pr_debug("Receiving packet size %d status %4.4x.\n",
					   pkt_len, rx_status);

			/* Check अगर the packet is दीर्घ enough to just accept without
			   copying to a properly sized skbuff. */
			अगर (pkt_len < rx_copyअवरोध &&
			    (skb = netdev_alloc_skb(dev, pkt_len + 2)) != शून्य) अणु
				skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
				dma_sync_single_क्रम_cpu(vp->gendev, dma, PKT_BUF_SZ, DMA_FROM_DEVICE);
				/* 'skb_put()' poपूर्णांकs to the start of sk_buff data area. */
				skb_put_data(skb, vp->rx_skbuff[entry]->data,
					     pkt_len);
				dma_sync_single_क्रम_device(vp->gendev, dma, PKT_BUF_SZ, DMA_FROM_DEVICE);
				vp->rx_copy++;
			पूर्ण अन्यथा अणु
				/* Pre-allocate the replacement skb.  If it or its
				 * mapping fails then recycle the buffer thats alपढ़ोy
				 * in place
				 */
				newskb = netdev_alloc_skb_ip_align(dev, PKT_BUF_SZ);
				अगर (!newskb) अणु
					dev->stats.rx_dropped++;
					जाओ clear_complete;
				पूर्ण
				newdma = dma_map_single(vp->gendev, newskb->data,
							PKT_BUF_SZ, DMA_FROM_DEVICE);
				अगर (dma_mapping_error(vp->gendev, newdma)) अणु
					dev->stats.rx_dropped++;
					consume_skb(newskb);
					जाओ clear_complete;
				पूर्ण

				/* Pass up the skbuff alपढ़ोy on the Rx ring. */
				skb = vp->rx_skbuff[entry];
				vp->rx_skbuff[entry] = newskb;
				vp->rx_ring[entry].addr = cpu_to_le32(newdma);
				skb_put(skb, pkt_len);
				dma_unmap_single(vp->gendev, dma, PKT_BUF_SZ, DMA_FROM_DEVICE);
				vp->rx_nocopy++;
			पूर्ण
			skb->protocol = eth_type_trans(skb, dev);
			अणु					/* Use hardware checksum info. */
				पूर्णांक csum_bits = rx_status & 0xee000000;
				अगर (csum_bits &&
					(csum_bits == (IPChksumValid | TCPChksumValid) ||
					 csum_bits == (IPChksumValid | UDPChksumValid))) अणु
					skb->ip_summed = CHECKSUM_UNNECESSARY;
					vp->rx_csumhits++;
				पूर्ण
			पूर्ण
			netअगर_rx(skb);
			dev->stats.rx_packets++;
		पूर्ण

clear_complete:
		vp->rx_ring[entry].status = 0;	/* Clear complete bit. */
		ioग_लिखो16(UpUnstall, ioaddr + EL3_CMD);
		entry = (++vp->cur_rx) % RX_RING_SIZE;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
vortex_करोwn(काष्ठा net_device *dev, पूर्णांक final_करोwn)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;

	netdev_reset_queue(dev);
	netअगर_stop_queue(dev);

	del_समयr_sync(&vp->समयr);

	/* Turn off statistics ASAP.  We update dev->stats below. */
	ioग_लिखो16(StatsDisable, ioaddr + EL3_CMD);

	/* Disable the receiver and transmitter. */
	ioग_लिखो16(RxDisable, ioaddr + EL3_CMD);
	ioग_लिखो16(TxDisable, ioaddr + EL3_CMD);

	/* Disable receiving 802.1q tagged frames */
	set_8021q_mode(dev, 0);

	अगर (dev->अगर_port == XCVR_10base2)
		/* Turn off thinnet घातer.  Green! */
		ioग_लिखो16(StopCoax, ioaddr + EL3_CMD);

	ioग_लिखो16(SetIntrEnb | 0x0000, ioaddr + EL3_CMD);

	update_stats(ioaddr, dev);
	अगर (vp->full_bus_master_rx)
		ioग_लिखो32(0, ioaddr + UpListPtr);
	अगर (vp->full_bus_master_tx)
		ioग_लिखो32(0, ioaddr + DownListPtr);

	अगर (final_करोwn && VORTEX_PCI(vp)) अणु
		vp->pm_state_valid = 1;
		pci_save_state(VORTEX_PCI(vp));
		acpi_set_WOL(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक
vortex_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	पूर्णांक i;

	अगर (netअगर_device_present(dev))
		vortex_करोwn(dev, 1);

	अगर (vortex_debug > 1) अणु
		pr_debug("%s: vortex_close() status %4.4x, Tx status %2.2x.\n",
			   dev->name, ioपढ़ो16(ioaddr + EL3_STATUS), ioपढ़ो8(ioaddr + TxStatus));
		pr_debug("%s: vortex close stats: rx_nocopy %d rx_copy %d"
			   " tx_queued %d Rx pre-checksummed %d.\n",
			   dev->name, vp->rx_nocopy, vp->rx_copy, vp->queued_packet, vp->rx_csumhits);
	पूर्ण

#अगर DO_ZEROCOPY
	अगर (vp->rx_csumhits &&
	    (vp->drv_flags & HAS_HWCKSM) == 0 &&
	    (vp->card_idx >= MAX_UNITS || hw_checksums[vp->card_idx] == -1)) अणु
		pr_warn("%s supports hardware checksums, and we're not using them!\n",
			dev->name);
	पूर्ण
#पूर्ण_अगर

	मुक्त_irq(dev->irq, dev);

	अगर (vp->full_bus_master_rx) अणु /* Free Boomerang bus master Rx buffers. */
		क्रम (i = 0; i < RX_RING_SIZE; i++)
			अगर (vp->rx_skbuff[i]) अणु
				dma_unmap_single(vp->gendev, le32_to_cpu(vp->rx_ring[i].addr),
									PKT_BUF_SZ, DMA_FROM_DEVICE);
				dev_kमुक्त_skb(vp->rx_skbuff[i]);
				vp->rx_skbuff[i] = शून्य;
			पूर्ण
	पूर्ण
	अगर (vp->full_bus_master_tx) अणु /* Free Boomerang bus master Tx buffers. */
		क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
			अगर (vp->tx_skbuff[i]) अणु
				काष्ठा sk_buff *skb = vp->tx_skbuff[i];
#अगर DO_ZEROCOPY
				पूर्णांक k;

				क्रम (k=0; k<=skb_shinfo(skb)->nr_frags; k++)
						dma_unmap_single(vp->gendev,
										 le32_to_cpu(vp->tx_ring[i].frag[k].addr),
										 le32_to_cpu(vp->tx_ring[i].frag[k].length)&0xFFF,
										 DMA_TO_DEVICE);
#अन्यथा
				dma_unmap_single(vp->gendev, le32_to_cpu(vp->tx_ring[i].addr), skb->len, DMA_TO_DEVICE);
#पूर्ण_अगर
				dev_kमुक्त_skb(skb);
				vp->tx_skbuff[i] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
dump_tx_ring(काष्ठा net_device *dev)
अणु
	अगर (vortex_debug > 0) अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
		व्योम __iomem *ioaddr = vp->ioaddr;

		अगर (vp->full_bus_master_tx) अणु
			पूर्णांक i;
			पूर्णांक stalled = ioपढ़ो32(ioaddr + PktStatus) & 0x04;	/* Possible racy. But it's only debug stuff */

			pr_err("  Flags; bus-master %d, dirty %d(%d) current %d(%d)\n",
					vp->full_bus_master_tx,
					vp->dirty_tx, vp->dirty_tx % TX_RING_SIZE,
					vp->cur_tx, vp->cur_tx % TX_RING_SIZE);
			pr_err("  Transmit list %8.8x vs. %p.\n",
				   ioपढ़ो32(ioaddr + DownListPtr),
				   &vp->tx_ring[vp->dirty_tx % TX_RING_SIZE]);
			issue_and_रुको(dev, DownStall);
			क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
				अचिन्हित पूर्णांक length;

#अगर DO_ZEROCOPY
				length = le32_to_cpu(vp->tx_ring[i].frag[0].length);
#अन्यथा
				length = le32_to_cpu(vp->tx_ring[i].length);
#पूर्ण_अगर
				pr_err("  %d: @%p  length %8.8x status %8.8x\n",
					   i, &vp->tx_ring[i], length,
					   le32_to_cpu(vp->tx_ring[i].status));
			पूर्ण
			अगर (!stalled)
				ioग_लिखो16(DownUnstall, ioaddr + EL3_CMD);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा net_device_stats *vortex_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	अचिन्हित दीर्घ flags;

	अगर (netअगर_device_present(dev)) अणु	/* AKPM: Used to be netअगर_running */
		spin_lock_irqsave (&vp->lock, flags);
		update_stats(ioaddr, dev);
		spin_unlock_irqrestore (&vp->lock, flags);
	पूर्ण
	वापस &dev->stats;
पूर्ण

/*  Update statistics.
	Unlike with the EL3 we need not worry about पूर्णांकerrupts changing
	the winकरोw setting from underneath us, but we must still guard
	against a race condition with a StatsUpdate पूर्णांकerrupt updating the
	table.  This is करोne by checking that the ASM (!) code generated uses
	atomic updates with '+='.
	*/
अटल व्योम update_stats(व्योम __iomem *ioaddr, काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);

	/* Unlike the 3c5x9 we need not turn off stats updates जबतक पढ़ोing. */
	/* Switch to the stats winकरोw, and पढ़ो everything. */
	dev->stats.tx_carrier_errors		+= winकरोw_पढ़ो8(vp, 6, 0);
	dev->stats.tx_heartbeat_errors		+= winकरोw_पढ़ो8(vp, 6, 1);
	dev->stats.tx_winकरोw_errors		+= winकरोw_पढ़ो8(vp, 6, 4);
	dev->stats.rx_fअगरo_errors		+= winकरोw_पढ़ो8(vp, 6, 5);
	dev->stats.tx_packets			+= winकरोw_पढ़ो8(vp, 6, 6);
	dev->stats.tx_packets			+= (winकरोw_पढ़ो8(vp, 6, 9) &
						    0x30) << 4;
	/* Rx packets	*/			winकरोw_पढ़ो8(vp, 6, 7);   /* Must पढ़ो to clear */
	/* Don't bother with रेजिस्टर 9, an extension of रेजिस्टरs 6&7.
	   If we करो use the 6&7 values the atomic update assumption above
	   is invalid. */
	dev->stats.rx_bytes 			+= winकरोw_पढ़ो16(vp, 6, 10);
	dev->stats.tx_bytes 			+= winकरोw_पढ़ो16(vp, 6, 12);
	/* Extra stats क्रम get_ethtool_stats() */
	vp->xstats.tx_multiple_collisions	+= winकरोw_पढ़ो8(vp, 6, 2);
	vp->xstats.tx_single_collisions         += winकरोw_पढ़ो8(vp, 6, 3);
	vp->xstats.tx_deferred			+= winकरोw_पढ़ो8(vp, 6, 8);
	vp->xstats.rx_bad_ssd			+= winकरोw_पढ़ो8(vp, 4, 12);

	dev->stats.collisions = vp->xstats.tx_multiple_collisions
		+ vp->xstats.tx_single_collisions
		+ vp->xstats.tx_max_collisions;

	अणु
		u8 up = winकरोw_पढ़ो8(vp, 4, 13);
		dev->stats.rx_bytes += (up & 0x0f) << 16;
		dev->stats.tx_bytes += (up & 0xf0) << 12;
	पूर्ण
पूर्ण

अटल पूर्णांक vortex_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);

	वापस mii_nway_restart(&vp->mii);
पूर्ण

अटल पूर्णांक vortex_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);

	mii_ethtool_get_link_ksettings(&vp->mii, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक vortex_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);

	वापस mii_ethtool_set_link_ksettings(&vp->mii, cmd);
पूर्ण

अटल u32 vortex_get_msglevel(काष्ठा net_device *dev)
अणु
	वापस vortex_debug;
पूर्ण

अटल व्योम vortex_set_msglevel(काष्ठा net_device *dev, u32 dbg)
अणु
	vortex_debug = dbg;
पूर्ण

अटल पूर्णांक vortex_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस VORTEX_NUM_STATS;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम vortex_get_ethtool_stats(काष्ठा net_device *dev,
	काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vp->lock, flags);
	update_stats(ioaddr, dev);
	spin_unlock_irqrestore(&vp->lock, flags);

	data[0] = vp->xstats.tx_deferred;
	data[1] = vp->xstats.tx_max_collisions;
	data[2] = vp->xstats.tx_multiple_collisions;
	data[3] = vp->xstats.tx_single_collisions;
	data[4] = vp->xstats.rx_bad_ssd;
पूर्ण


अटल व्योम vortex_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, &ethtool_stats_keys, माप(ethtool_stats_keys));
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vortex_get_drvinfo(काष्ठा net_device *dev,
					काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	अगर (VORTEX_PCI(vp)) अणु
		strlcpy(info->bus_info, pci_name(VORTEX_PCI(vp)),
			माप(info->bus_info));
	पूर्ण अन्यथा अणु
		अगर (VORTEX_EISA(vp))
			strlcpy(info->bus_info, dev_name(vp->gendev),
				माप(info->bus_info));
		अन्यथा
			snम_लिखो(info->bus_info, माप(info->bus_info),
				"EISA 0x%lx %d", dev->base_addr, dev->irq);
	पूर्ण
पूर्ण

अटल व्योम vortex_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);

	अगर (!VORTEX_PCI(vp))
		वापस;

	wol->supported = WAKE_MAGIC;

	wol->wolopts = 0;
	अगर (vp->enable_wol)
		wol->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक vortex_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);

	अगर (!VORTEX_PCI(vp))
		वापस -EOPNOTSUPP;

	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EINVAL;

	अगर (wol->wolopts & WAKE_MAGIC)
		vp->enable_wol = 1;
	अन्यथा
		vp->enable_wol = 0;
	acpi_set_WOL(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vortex_ethtool_ops = अणु
	.get_drvinfo		= vortex_get_drvinfo,
	.get_strings            = vortex_get_strings,
	.get_msglevel           = vortex_get_msglevel,
	.set_msglevel           = vortex_set_msglevel,
	.get_ethtool_stats      = vortex_get_ethtool_stats,
	.get_sset_count		= vortex_get_sset_count,
	.get_link               = ethtool_op_get_link,
	.nway_reset             = vortex_nway_reset,
	.get_wol                = vortex_get_wol,
	.set_wol                = vortex_set_wol,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_link_ksettings     = vortex_get_link_ksettings,
	.set_link_ksettings     = vortex_set_link_ksettings,
पूर्ण;

#अगर_घोषित CONFIG_PCI
/*
 *	Must घातer the device up to करो MDIO operations
 */
अटल पूर्णांक vortex_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	पूर्णांक err;
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	pci_घातer_t state = 0;

	अगर(VORTEX_PCI(vp))
		state = VORTEX_PCI(vp)->current_state;

	/* The kernel core really should have pci_get_घातer_state() */

	अगर(state != 0)
		pci_set_घातer_state(VORTEX_PCI(vp), PCI_D0);
	err = generic_mii_ioctl(&vp->mii, अगर_mii(rq), cmd, शून्य);
	अगर(state != 0)
		pci_set_घातer_state(VORTEX_PCI(vp), state);

	वापस err;
पूर्ण
#पूर्ण_अगर


/* Pre-Cyclone chips have no करोcumented multicast filter, so the only
   multicast setting is to receive all multicast frames.  At least
   the chip has a very clean way to set the mode, unlike many others. */
अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;
	पूर्णांक new_mode;

	अगर (dev->flags & IFF_PROMISC) अणु
		अगर (vortex_debug > 3)
			pr_notice("%s: Setting promiscuous mode.\n", dev->name);
		new_mode = SetRxFilter|RxStation|RxMulticast|RxBroadcast|RxProm;
	पूर्ण अन्यथा	अगर (!netdev_mc_empty(dev) || dev->flags & IFF_ALLMULTI) अणु
		new_mode = SetRxFilter|RxStation|RxMulticast|RxBroadcast;
	पूर्ण अन्यथा
		new_mode = SetRxFilter | RxStation | RxBroadcast;

	ioग_लिखो16(new_mode, ioaddr + EL3_CMD);
पूर्ण

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
/* Setup the card so that it can receive frames with an 802.1q VLAN tag.
   Note that this must be करोne after each RxReset due to some backwards
   compatibility logic in the Cyclone and Tornaकरो ASICs */

/* The Ethernet Type used क्रम 802.1q tagged frames */
#घोषणा VLAN_ETHER_TYPE 0x8100

अटल व्योम set_8021q_mode(काष्ठा net_device *dev, पूर्णांक enable)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	पूर्णांक mac_ctrl;

	अगर ((vp->drv_flags&IS_CYCLONE) || (vp->drv_flags&IS_TORNADO)) अणु
		/* cyclone and tornaकरो chipsets can recognize 802.1q
		 * tagged frames and treat them correctly */

		पूर्णांक max_pkt_size = dev->mtu+14;	/* MTU+Ethernet header */
		अगर (enable)
			max_pkt_size += 4;	/* 802.1Q VLAN tag */

		winकरोw_ग_लिखो16(vp, max_pkt_size, 3, Wn3_MaxPktSize);

		/* set VlanEtherType to let the hardware checksumming
		   treat tagged frames correctly */
		winकरोw_ग_लिखो16(vp, VLAN_ETHER_TYPE, 7, Wn7_VlanEtherType);
	पूर्ण अन्यथा अणु
		/* on older cards we have to enable large frames */

		vp->large_frames = dev->mtu > 1500 || enable;

		mac_ctrl = winकरोw_पढ़ो16(vp, 3, Wn3_MAC_Ctrl);
		अगर (vp->large_frames)
			mac_ctrl |= 0x40;
		अन्यथा
			mac_ctrl &= ~0x40;
		winकरोw_ग_लिखो16(vp, mac_ctrl, 3, Wn3_MAC_Ctrl);
	पूर्ण
पूर्ण
#अन्यथा

अटल व्योम set_8021q_mode(काष्ठा net_device *dev, पूर्णांक enable)
अणु
पूर्ण


#पूर्ण_अगर

/* MII transceiver control section.
   Read and ग_लिखो the MII रेजिस्टरs using software-generated serial
   MDIO protocol.  See the MII specअगरications or DP83840A data sheet
   क्रम details. */

/* The maximum data घड़ी rate is 2.5 Mhz.  The minimum timing is usually
   met by back-to-back PCI I/O cycles, but we insert a delay to aव्योम
   "overclocking" issues. */
अटल व्योम mdio_delay(काष्ठा vortex_निजी *vp)
अणु
	winकरोw_पढ़ो32(vp, 4, Wn4_PhysicalMgmt);
पूर्ण

#घोषणा MDIO_SHIFT_CLK	0x01
#घोषणा MDIO_सूची_WRITE	0x04
#घोषणा MDIO_DATA_WRITE0 (0x00 | MDIO_सूची_WRITE)
#घोषणा MDIO_DATA_WRITE1 (0x02 | MDIO_सूची_WRITE)
#घोषणा MDIO_DATA_READ	0x02
#घोषणा MDIO_ENB_IN		0x00

/* Generate the preamble required क्रम initial synchronization and
   a few older transceivers. */
अटल व्योम mdio_sync(काष्ठा vortex_निजी *vp, पूर्णांक bits)
अणु
	/* Establish sync by sending at least 32 logic ones. */
	जबतक (-- bits >= 0) अणु
		winकरोw_ग_लिखो16(vp, MDIO_DATA_WRITE1, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		winकरोw_ग_लिखो16(vp, MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	पूर्ण
पूर्ण

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	पूर्णांक i;
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	पूर्णांक पढ़ो_cmd = (0xf6 << 10) | (phy_id << 5) | location;
	अचिन्हित पूर्णांक retval = 0;

	spin_lock_bh(&vp->mii_lock);

	अगर (mii_preamble_required)
		mdio_sync(vp, 32);

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 14; i >= 0; i--) अणु
		पूर्णांक dataval = (पढ़ो_cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
		winकरोw_ग_लिखो16(vp, dataval, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		winकरोw_ग_लिखो16(vp, dataval | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	पूर्ण
	/* Read the two transition, 16 data, and wire-idle bits. */
	क्रम (i = 19; i > 0; i--) अणु
		winकरोw_ग_लिखो16(vp, MDIO_ENB_IN, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		retval = (retval << 1) |
			((winकरोw_पढ़ो16(vp, 4, Wn4_PhysicalMgmt) &
			  MDIO_DATA_READ) ? 1 : 0);
		winकरोw_ग_लिखो16(vp, MDIO_ENB_IN | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	पूर्ण

	spin_unlock_bh(&vp->mii_lock);

	वापस retval & 0x20000 ? 0xffff : retval>>1 & 0xffff;
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	पूर्णांक ग_लिखो_cmd = 0x50020000 | (phy_id << 23) | (location << 18) | value;
	पूर्णांक i;

	spin_lock_bh(&vp->mii_lock);

	अगर (mii_preamble_required)
		mdio_sync(vp, 32);

	/* Shअगरt the command bits out. */
	क्रम (i = 31; i >= 0; i--) अणु
		पूर्णांक dataval = (ग_लिखो_cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
		winकरोw_ग_लिखो16(vp, dataval, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		winकरोw_ग_लिखो16(vp, dataval | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	पूर्ण
	/* Leave the पूर्णांकerface idle. */
	क्रम (i = 1; i >= 0; i--) अणु
		winकरोw_ग_लिखो16(vp, MDIO_ENB_IN, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		winकरोw_ग_लिखो16(vp, MDIO_ENB_IN | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	पूर्ण

	spin_unlock_bh(&vp->mii_lock);
पूर्ण

/* ACPI: Advanced Configuration and Power Interface. */
/* Set Wake-On-LAN mode and put the board पूर्णांकo D3 (घातer-करोwn) state. */
अटल व्योम acpi_set_WOL(काष्ठा net_device *dev)
अणु
	काष्ठा vortex_निजी *vp = netdev_priv(dev);
	व्योम __iomem *ioaddr = vp->ioaddr;

	device_set_wakeup_enable(vp->gendev, vp->enable_wol);

	अगर (vp->enable_wol) अणु
		/* Power up on: 1==Downloaded Filter, 2==Magic Packets, 4==Link Status. */
		winकरोw_ग_लिखो16(vp, 2, 7, 0x0c);
		/* The RxFilter must accept the WOL frames. */
		ioग_लिखो16(SetRxFilter|RxStation|RxMulticast|RxBroadcast, ioaddr + EL3_CMD);
		ioग_लिखो16(RxEnable, ioaddr + EL3_CMD);

		अगर (pci_enable_wake(VORTEX_PCI(vp), PCI_D3hot, 1)) अणु
			pr_info("%s: WOL not supported.\n", pci_name(VORTEX_PCI(vp)));

			vp->enable_wol = 0;
			वापस;
		पूर्ण

		अगर (VORTEX_PCI(vp)->current_state < PCI_D3hot)
			वापस;

		/* Change the घातer state to D3; RxEnable करोesn't take effect. */
		pci_set_घातer_state(VORTEX_PCI(vp), PCI_D3hot);
	पूर्ण
पूर्ण


अटल व्योम vortex_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा vortex_निजी *vp;

	अगर (!dev) अणु
		pr_err("vortex_remove_one called for Compaq device!\n");
		BUG();
	पूर्ण

	vp = netdev_priv(dev);

	अगर (vp->cb_fn_base)
		pci_iounmap(pdev, vp->cb_fn_base);

	unरेजिस्टर_netdev(dev);

	pci_set_घातer_state(pdev, PCI_D0);	/* Go active */
	अगर (vp->pm_state_valid)
		pci_restore_state(pdev);
	pci_disable_device(pdev);

	/* Should really use issue_and_रुको() here */
	ioग_लिखो16(TotalReset | ((vp->drv_flags & EEPROM_RESET) ? 0x04 : 0x14),
	     vp->ioaddr + EL3_CMD);

	pci_iounmap(pdev, vp->ioaddr);

	dma_मुक्त_coherent(&pdev->dev,
			माप(काष्ठा boom_rx_desc) * RX_RING_SIZE +
			माप(काष्ठा boom_tx_desc) * TX_RING_SIZE,
			vp->rx_ring, vp->rx_ring_dma);

	pci_release_regions(pdev);

	मुक्त_netdev(dev);
पूर्ण


अटल काष्ठा pci_driver vortex_driver = अणु
	.name		= "3c59x",
	.probe		= vortex_init_one,
	.हटाओ		= vortex_हटाओ_one,
	.id_table	= vortex_pci_tbl,
	.driver.pm	= VORTEX_PM_OPS,
पूर्ण;


अटल पूर्णांक vortex_have_pci;
अटल पूर्णांक vortex_have_eisa;


अटल पूर्णांक __init vortex_init(व्योम)
अणु
	पूर्णांक pci_rc, eisa_rc;

	pci_rc = pci_रेजिस्टर_driver(&vortex_driver);
	eisa_rc = vortex_eisa_init();

	अगर (pci_rc == 0)
		vortex_have_pci = 1;
	अगर (eisa_rc > 0)
		vortex_have_eisa = 1;

	वापस (vortex_have_pci + vortex_have_eisa) ? 0 : -ENODEV;
पूर्ण


अटल व्योम __निकास vortex_eisa_cleanup(व्योम)
अणु
	व्योम __iomem *ioaddr;

#अगर_घोषित CONFIG_EISA
	/* Take care of the EISA devices */
	eisa_driver_unरेजिस्टर(&vortex_eisa_driver);
#पूर्ण_अगर

	अगर (compaq_net_device) अणु
		ioaddr = ioport_map(compaq_net_device->base_addr,
		                    VORTEX_TOTAL_SIZE);

		unरेजिस्टर_netdev(compaq_net_device);
		ioग_लिखो16(TotalReset, ioaddr + EL3_CMD);
		release_region(compaq_net_device->base_addr,
		               VORTEX_TOTAL_SIZE);

		मुक्त_netdev(compaq_net_device);
	पूर्ण
पूर्ण


अटल व्योम __निकास vortex_cleanup(व्योम)
अणु
	अगर (vortex_have_pci)
		pci_unरेजिस्टर_driver(&vortex_driver);
	अगर (vortex_have_eisa)
		vortex_eisa_cleanup();
पूर्ण


module_init(vortex_init);
module_निकास(vortex_cleanup);
