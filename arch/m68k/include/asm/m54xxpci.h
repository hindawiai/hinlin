<शैली गुरु>
/****************************************************************************/

/*
 *	m54xxpci.h -- ColdFire 547x and 548x PCI bus support
 *
 *	(C) Copyright 2011,  Greg Ungerer <gerg@uclinux.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/****************************************************************************/
#अगर_अघोषित	M54XXPCI_H
#घोषणा	M54XXPCI_H
/****************************************************************************/

/*
 *	The core set of PCI support रेजिस्टरs are mapped पूर्णांकo the MBAR region.
 */
#घोषणा	PCIIDR		(CONFIG_MBAR + 0xb00)	/* PCI device/venकरोr ID */
#घोषणा	PCISCR		(CONFIG_MBAR + 0xb04)	/* PCI status/command */
#घोषणा	PCICCRIR	(CONFIG_MBAR + 0xb08)	/* PCI class/revision */
#घोषणा	PCICR1		(CONFIG_MBAR + 0xb0c)	/* PCI configuration 1 */
#घोषणा	PCIBAR0		(CONFIG_MBAR + 0xb10)	/* PCI base address 0 */
#घोषणा	PCIBAR1		(CONFIG_MBAR + 0xb14)	/* PCI base address 1 */
#घोषणा	PCICCPR		(CONFIG_MBAR + 0xb28)	/* PCI cardbus CIS poपूर्णांकer */
#घोषणा	PCISID		(CONFIG_MBAR + 0xb2c)	/* PCI subप्रणाली IDs */
#घोषणा	PCIERBAR	(CONFIG_MBAR + 0xb30)	/* PCI expansion ROM */
#घोषणा	PCICPR		(CONFIG_MBAR + 0xb34)	/* PCI capabilities poपूर्णांकer */
#घोषणा	PCICR2		(CONFIG_MBAR + 0xb3c)	/* PCI configuration 2 */

#घोषणा	PCIGSCR		(CONFIG_MBAR + 0xb60)	/* Global status/control */
#घोषणा	PCITBATR0	(CONFIG_MBAR + 0xb64)	/* Target base translation 0 */
#घोषणा	PCITBATR1	(CONFIG_MBAR + 0xb68)	/* Target base translation 1 */
#घोषणा	PCITCR		(CONFIG_MBAR + 0xb6c)	/* Target control */
#घोषणा	PCIIW0BTAR	(CONFIG_MBAR + 0xb70)	/* Initiator winकरोw 0 */
#घोषणा	PCIIW1BTAR	(CONFIG_MBAR + 0xb74)	/* Initiator winकरोw 1 */
#घोषणा	PCIIW2BTAR	(CONFIG_MBAR + 0xb78)	/* Initiator winकरोw 2 */
#घोषणा	PCIIWCR		(CONFIG_MBAR + 0xb80)	/* Initiator winकरोw config */
#घोषणा	PCIICR		(CONFIG_MBAR + 0xb84)	/* Initiator control */
#घोषणा	PCIISR		(CONFIG_MBAR + 0xb88)	/* Initiator status */
#घोषणा	PCICAR		(CONFIG_MBAR + 0xbf8)	/* Configuration address */

#घोषणा	PCITPSR		(CONFIG_MBAR + 0x8400)	/* TX packet size */
#घोषणा	PCITSAR		(CONFIG_MBAR + 0x8404)	/* TX start address */
#घोषणा	PCITTCR		(CONFIG_MBAR + 0x8408)	/* TX transaction control */
#घोषणा	PCITER		(CONFIG_MBAR + 0x840c)	/* TX enables */
#घोषणा	PCITNAR		(CONFIG_MBAR + 0x8410)	/* TX next address */
#घोषणा	PCITLWR		(CONFIG_MBAR + 0x8414)	/* TX last word */
#घोषणा	PCITDCR		(CONFIG_MBAR + 0x8418)	/* TX करोne counts */
#घोषणा	PCITSR		(CONFIG_MBAR + 0x841c)	/* TX status */
#घोषणा	PCITFDR		(CONFIG_MBAR + 0x8440)	/* TX FIFO data */
#घोषणा	PCITFSR		(CONFIG_MBAR + 0x8444)	/* TX FIFO status */
#घोषणा	PCITFCR		(CONFIG_MBAR + 0x8448)	/* TX FIFO control */
#घोषणा	PCITFAR		(CONFIG_MBAR + 0x844c)	/* TX FIFO alarm */
#घोषणा	PCITFRPR	(CONFIG_MBAR + 0x8450)	/* TX FIFO पढ़ो poपूर्णांकer */
#घोषणा	PCITFWPR	(CONFIG_MBAR + 0x8454)	/* TX FIFO ग_लिखो poपूर्णांकer */

#घोषणा	PCIRPSR		(CONFIG_MBAR + 0x8480)	/* RX packet size */
#घोषणा	PCIRSAR		(CONFIG_MBAR + 0x8484)	/* RX start address */
#घोषणा	PCIRTCR		(CONFIG_MBAR + 0x8488)	/* RX transaction control */
#घोषणा	PCIRER		(CONFIG_MBAR + 0x848c)	/* RX enables */
#घोषणा	PCIRNAR		(CONFIG_MBAR + 0x8490)	/* RX next address */
#घोषणा	PCIRDCR		(CONFIG_MBAR + 0x8498)	/* RX करोne counts */
#घोषणा	PCIRSR		(CONFIG_MBAR + 0x849c)	/* RX status */
#घोषणा	PCIRFDR		(CONFIG_MBAR + 0x84c0)	/* RX FIFO data */
#घोषणा	PCIRFSR		(CONFIG_MBAR + 0x84c4)	/* RX FIFO status */
#घोषणा	PCIRFCR		(CONFIG_MBAR + 0x84c8)	/* RX FIFO control */
#घोषणा	PCIRFAR		(CONFIG_MBAR + 0x84cc)	/* RX FIFO alarm */
#घोषणा	PCIRFRPR	(CONFIG_MBAR + 0x84d0)	/* RX FIFO पढ़ो poपूर्णांकer */
#घोषणा	PCIRFWPR	(CONFIG_MBAR + 0x84d4)	/* RX FIFO ग_लिखो poपूर्णांकer */

#घोषणा	PACR		(CONFIG_MBAR + 0xc00)	/* PCI arbiter control */
#घोषणा	PASR		(CONFIG_MBAR + 0xc04)	/* PCI arbiter status */

/*
 *	Definitions क्रम the Global status and control रेजिस्टर.
 */
#घोषणा	PCIGSCR_PE	0x20000000		/* Parity error detected */
#घोषणा	PCIGSCR_SE	0x10000000		/* System error detected */
#घोषणा	PCIGSCR_XCLKBIN	0x07000000		/* XLB2CLKIN mask */
#घोषणा	PCIGSCR_PEE	0x00002000		/* Parity error पूर्णांकr enable */
#घोषणा	PCIGSCR_SEE	0x00001000		/* System error पूर्णांकr enable */
#घोषणा	PCIGSCR_RESET	0x00000001		/* Reset bit */

/*
 *	Bit definitions क्रम the PCICAR configuration address रेजिस्टर.
 */
#घोषणा	PCICAR_E	0x80000000		/* Enable config space */
#घोषणा	PCICAR_BUSN	16			/* Move bus bits */
#घोषणा	PCICAR_DEVFNN	8			/* Move devfn bits */
#घोषणा	PCICAR_DWORDN	0			/* Move dword bits */

/*
 *	The initiator winकरोws hold the memory and IO mapping inक्रमmation.
 *	This macro creates the रेजिस्टर values from the desired addresses.
 */
#घोषणा	WXBTAR(hostaddr, pciaddr, size)	\
			(((hostaddr) & 0xff000000) | \
			((((size) - 1) & 0xff000000) >> 8) | \
			(((pciaddr) & 0xff000000) >> 16))

#घोषणा	PCIIWCR_W0_MEM	0x00000000		/* Winकरोw 0 is memory */
#घोषणा	PCIIWCR_W0_IO	0x08000000		/* Winकरोw 0 is IO */
#घोषणा	PCIIWCR_W0_MRD	0x00000000		/* Winकरोw 0 memory पढ़ो */
#घोषणा	PCIIWCR_W0_MRDL	0x02000000		/* Winकरोw 0 memory पढ़ो line */
#घोषणा	PCIIWCR_W0_MRDM	0x04000000		/* Winकरोw 0 memory पढ़ो mult */
#घोषणा	PCIIWCR_W0_E	0x01000000		/* Winकरोw 0 enable */

#घोषणा	PCIIWCR_W1_MEM	0x00000000		/* Winकरोw 0 is memory */
#घोषणा	PCIIWCR_W1_IO	0x00080000		/* Winकरोw 0 is IO */
#घोषणा	PCIIWCR_W1_MRD	0x00000000		/* Winकरोw 0 memory पढ़ो */
#घोषणा	PCIIWCR_W1_MRDL	0x00020000		/* Winकरोw 0 memory पढ़ो line */
#घोषणा	PCIIWCR_W1_MRDM	0x00040000		/* Winकरोw 0 memory पढ़ो mult */
#घोषणा	PCIIWCR_W1_E	0x00010000		/* Winकरोw 0 enable */

/*
 *	Bit definitions क्रम the PCIBATR रेजिस्टरs.
 */
#घोषणा	PCITBATR0_E	0x00000001		/* Enable winकरोw 0 */
#घोषणा	PCITBATR1_E	0x00000001		/* Enable winकरोw 1 */

/*
 *	PCI arbiter support definitions and macros.
 */
#घोषणा	PACR_INTMPRI	0x00000001
#घोषणा	PACR_EXTMPRI(x)	(((x) & 0x1f) << 1)
#घोषणा	PACR_INTMINTE	0x00010000
#घोषणा	PACR_EXTMINTE(x) (((x) & 0x1f) << 17)
#घोषणा	PACR_PKMD	0x40000000
#घोषणा	PACR_DS		0x80000000

#घोषणा	PCICR1_CL(x)	((x) & 0xf)		/* Cacheline size field */
#घोषणा	PCICR1_LT(x)	(((x) & 0xff) << 8)	/* Latency समयr field */

/****************************************************************************/
#पूर्ण_अगर	/* M54XXPCI_H */
