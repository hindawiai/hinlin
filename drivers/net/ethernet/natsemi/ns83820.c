<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#घोषणा VERSION "0.23"
/* ns83820.c by Benjamin LaHaise with contributions.
 *
 * Questions/comments/discussion to linux-ns83820@kvack.org.
 *
 * $Revision: 1.34.2.23 $
 *
 * Copyright 2001 Benjamin LaHaise.
 * Copyright 2001, 2002 Red Hat.
 *
 * Mmmm, chocolate vanilla mocha...
 *
 * ChangeLog
 * =========
 *	20010414	0.1 - created
 *	20010622	0.2 - basic rx and tx.
 *	20010711	0.3 - added duplex and link state detection support.
 *	20010713	0.4 - zero copy, no hangs.
 *			0.5 - 64 bit dma support (davem will hate me क्रम this)
 *			    - disable jumbo frames to aव्योम tx hangs
 *			    - work around tx deadlocks on my 1.02 card via
 *			      fiddling with TXCFG
 *	20010810	0.6 - use pci dma api क्रम ringbuffers, work on ia64
 *	20010816	0.7 - misc cleanups
 *	20010826	0.8 - fix critical zero copy bugs
 *			0.9 - पूर्णांकernal experiment
 *	20010827	0.10 - fix ia64 unaligned access.
 *	20010906	0.11 - accept all packets with checksum errors as
 *			       otherwise fragments get lost
 *			     - fix >> 32 bugs
 *			0.12 - add statistics counters
 *			     - add allmulti/promisc support
 *	20011009	0.13 - hotplug support, other smaller pci api cleanups
 *	20011204	0.13a - optical transceiver support added
 *				by Michael Clark <michael@metaparadigm.com>
 *	20011205	0.13b - call रेजिस्टर_netdev earlier in initialization
 *				suppress duplicate link status messages
 *	20011117 	0.14 - ethtool GDRVINFO, GLINK support from jgarzik
 *	20011204 	0.15	get ppc (big endian) working
 *	20011218	0.16	various cleanups
 *	20020310	0.17	speedups
 *	20020610	0.18 -	actually use the pci dma api क्रम highmem
 *			     -	हटाओ pci latency रेजिस्टर fiddling
 *			0.19 -	better bist support
 *			     -	add ihr and reset_phy parameters
 *			     -	gmii bus probing
 *			     -	fix missed txok पूर्णांकroduced during perक्रमmance
 *				tuning
 *			0.20 -	fix stupid RFEN thinko.  i am such a smurf.
 *	20040828	0.21 -	add hardware vlan accleration
 *				by Neil Horman <nhorman@redhat.com>
 *	20050406	0.22 -	improved DAC अगरdefs from Andi Kleen
 *			     -	removal of dead code from Adrian Bunk
 *			     -	fix half duplex collision behaviour
 * Driver Overview
 * ===============
 *
 * This driver was originally written क्रम the National Semiconductor
 * 83820 chip, a 10/100/1000 Mbps 64 bit PCI ethernet NIC.  Hopefully
 * this code will turn out to be a) clean, b) correct, and c) fast.
 * With that in mind, I'm aiming to split the code up as much as
 * reasonably possible.  At present there are X major sections that
 * अवरोध करोwn पूर्णांकo a) packet receive, b) packet transmit, c) link
 * management, d) initialization and configuration.  Where possible,
 * these code paths are deचिन्हित to run in parallel.
 *
 * This driver has been tested and found to work with the following
 * cards (in no particular order):
 *
 *	Cameo		SOHO-GA2000T	SOHO-GA2500T
 *	D-Link		DGE-500T
 *	PureData	PDP8023Z-TG
 *	SMC		SMC9452TX	SMC9462TX
 *	Netgear		GA621
 *
 * Special thanks to SMC क्रम providing hardware to test this driver on.
 *
 * Reports of success or failure would be greatly appreciated.
 */
//#घोषणा dprपूर्णांकk		prपूर्णांकk
#घोषणा dprपूर्णांकk(x...)		करो अणु पूर्ण जबतक (0)

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>	/* क्रम iph */
#समावेश <linux/in.h>	/* क्रम IPPROTO_... */
#समावेश <linux/compiler.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#घोषणा DRV_NAME "ns83820"

/* Global parameters.  See module_param near the bottom. */
अटल पूर्णांक ihr = 2;
अटल पूर्णांक reset_phy = 0;
अटल पूर्णांक lnksts = 0;		/* CFG_LNKSTS bit polarity */

/* Dprपूर्णांकk is used क्रम more पूर्णांकeresting debug events */
#अघोषित Dprपूर्णांकk
#घोषणा	Dprपूर्णांकk			dprपूर्णांकk

/* tunables */
#घोषणा RX_BUF_SIZE	1500	/* 8192 */
#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
#घोषणा NS83820_VLAN_ACCEL_SUPPORT
#पूर्ण_अगर

/* Must not exceed ~65000. */
#घोषणा NR_RX_DESC	64
#घोषणा NR_TX_DESC	128

/* not tunable */
#घोषणा REAL_RX_BUF_SIZE (RX_BUF_SIZE + 14)	/* rx/tx mac addr + type */

#घोषणा MIN_TX_DESC_FREE	8

/* रेजिस्टर defines */
#घोषणा CFGCS		0x04

#घोषणा CR_TXE		0x00000001
#घोषणा CR_TXD		0x00000002
/* Ramit : Here's a tip, don't करो a RXD immediately followed by an RXE
 * The Receive engine skips one descriptor and moves
 * onto the next one!! */
#घोषणा CR_RXE		0x00000004
#घोषणा CR_RXD		0x00000008
#घोषणा CR_TXR		0x00000010
#घोषणा CR_RXR		0x00000020
#घोषणा CR_SWI		0x00000080
#घोषणा CR_RST		0x00000100

#घोषणा PTSCR_EEBIST_FAIL       0x00000001
#घोषणा PTSCR_EEBIST_EN         0x00000002
#घोषणा PTSCR_EELOAD_EN         0x00000004
#घोषणा PTSCR_RBIST_FAIL        0x000001b8
#घोषणा PTSCR_RBIST_DONE        0x00000200
#घोषणा PTSCR_RBIST_EN          0x00000400
#घोषणा PTSCR_RBIST_RST         0x00002000

#घोषणा MEAR_EEDI		0x00000001
#घोषणा MEAR_EEDO		0x00000002
#घोषणा MEAR_EECLK		0x00000004
#घोषणा MEAR_EESEL		0x00000008
#घोषणा MEAR_MDIO		0x00000010
#घोषणा MEAR_MDसूची		0x00000020
#घोषणा MEAR_MDC		0x00000040

#घोषणा ISR_TXDESC3	0x40000000
#घोषणा ISR_TXDESC2	0x20000000
#घोषणा ISR_TXDESC1	0x10000000
#घोषणा ISR_TXDESC0	0x08000000
#घोषणा ISR_RXDESC3	0x04000000
#घोषणा ISR_RXDESC2	0x02000000
#घोषणा ISR_RXDESC1	0x01000000
#घोषणा ISR_RXDESC0	0x00800000
#घोषणा ISR_TXRCMP	0x00400000
#घोषणा ISR_RXRCMP	0x00200000
#घोषणा ISR_DPERR	0x00100000
#घोषणा ISR_SSERR	0x00080000
#घोषणा ISR_RMABT	0x00040000
#घोषणा ISR_RTABT	0x00020000
#घोषणा ISR_RXSOVR	0x00010000
#घोषणा ISR_HIBINT	0x00008000
#घोषणा ISR_PHY		0x00004000
#घोषणा ISR_PME		0x00002000
#घोषणा ISR_SWI		0x00001000
#घोषणा ISR_MIB		0x00000800
#घोषणा ISR_TXURN	0x00000400
#घोषणा ISR_TXIDLE	0x00000200
#घोषणा ISR_TXERR	0x00000100
#घोषणा ISR_TXDESC	0x00000080
#घोषणा ISR_TXOK	0x00000040
#घोषणा ISR_RXORN	0x00000020
#घोषणा ISR_RXIDLE	0x00000010
#घोषणा ISR_RXEARLY	0x00000008
#घोषणा ISR_RXERR	0x00000004
#घोषणा ISR_RXDESC	0x00000002
#घोषणा ISR_RXOK	0x00000001

#घोषणा TXCFG_CSI	0x80000000
#घोषणा TXCFG_HBI	0x40000000
#घोषणा TXCFG_MLB	0x20000000
#घोषणा TXCFG_ATP	0x10000000
#घोषणा TXCFG_ECRETRY	0x00800000
#घोषणा TXCFG_BRST_DIS	0x00080000
#घोषणा TXCFG_MXDMA1024	0x00000000
#घोषणा TXCFG_MXDMA512	0x00700000
#घोषणा TXCFG_MXDMA256	0x00600000
#घोषणा TXCFG_MXDMA128	0x00500000
#घोषणा TXCFG_MXDMA64	0x00400000
#घोषणा TXCFG_MXDMA32	0x00300000
#घोषणा TXCFG_MXDMA16	0x00200000
#घोषणा TXCFG_MXDMA8	0x00100000

#घोषणा CFG_LNKSTS	0x80000000
#घोषणा CFG_SPDSTS	0x60000000
#घोषणा CFG_SPDSTS1	0x40000000
#घोषणा CFG_SPDSTS0	0x20000000
#घोषणा CFG_DUPSTS	0x10000000
#घोषणा CFG_TBI_EN	0x01000000
#घोषणा CFG_MODE_1000	0x00400000
/* Ramit : Dont' ever use AUTO_1000, it never works and is buggy.
 * Read the Phy response and then configure the MAC accordingly */
#घोषणा CFG_AUTO_1000	0x00200000
#घोषणा CFG_PINT_CTL	0x001c0000
#घोषणा CFG_PINT_DUPSTS	0x00100000
#घोषणा CFG_PINT_LNKSTS	0x00080000
#घोषणा CFG_PINT_SPDSTS	0x00040000
#घोषणा CFG_TMRTEST	0x00020000
#घोषणा CFG_MRM_DIS	0x00010000
#घोषणा CFG_MWI_DIS	0x00008000
#घोषणा CFG_T64ADDR	0x00004000
#घोषणा CFG_PCI64_DET	0x00002000
#घोषणा CFG_DATA64_EN	0x00001000
#घोषणा CFG_M64ADDR	0x00000800
#घोषणा CFG_PHY_RST	0x00000400
#घोषणा CFG_PHY_DIS	0x00000200
#घोषणा CFG_EXTSTS_EN	0x00000100
#घोषणा CFG_REQALG	0x00000080
#घोषणा CFG_SB		0x00000040
#घोषणा CFG_POW		0x00000020
#घोषणा CFG_EXD		0x00000010
#घोषणा CFG_PESEL	0x00000008
#घोषणा CFG_BROM_DIS	0x00000004
#घोषणा CFG_EXT_125	0x00000002
#घोषणा CFG_BEM		0x00000001

#घोषणा EXTSTS_UDPPKT	0x00200000
#घोषणा EXTSTS_TCPPKT	0x00080000
#घोषणा EXTSTS_IPPKT	0x00020000
#घोषणा EXTSTS_VPKT	0x00010000
#घोषणा EXTSTS_VTG_MASK	0x0000ffff

#घोषणा SPDSTS_POLARITY	(CFG_SPDSTS1 | CFG_SPDSTS0 | CFG_DUPSTS | (lnksts ? CFG_LNKSTS : 0))

#घोषणा MIBC_MIBS	0x00000008
#घोषणा MIBC_ACLR	0x00000004
#घोषणा MIBC_FRZ	0x00000002
#घोषणा MIBC_WRN	0x00000001

#घोषणा PCR_PSEN	(1 << 31)
#घोषणा PCR_PS_MCAST	(1 << 30)
#घोषणा PCR_PS_DA	(1 << 29)
#घोषणा PCR_STHI_8	(3 << 23)
#घोषणा PCR_STLO_4	(1 << 23)
#घोषणा PCR_FFHI_8K	(3 << 21)
#घोषणा PCR_FFLO_4K	(1 << 21)
#घोषणा PCR_PAUSE_CNT	0xFFFE

#घोषणा RXCFG_AEP	0x80000000
#घोषणा RXCFG_ARP	0x40000000
#घोषणा RXCFG_STRIPCRC	0x20000000
#घोषणा RXCFG_RX_FD	0x10000000
#घोषणा RXCFG_ALP	0x08000000
#घोषणा RXCFG_AIRL	0x04000000
#घोषणा RXCFG_MXDMA512	0x00700000
#घोषणा RXCFG_DRTH	0x0000003e
#घोषणा RXCFG_DRTH0	0x00000002

#घोषणा RFCR_RFEN	0x80000000
#घोषणा RFCR_AAB	0x40000000
#घोषणा RFCR_AAM	0x20000000
#घोषणा RFCR_AAU	0x10000000
#घोषणा RFCR_APM	0x08000000
#घोषणा RFCR_APAT	0x07800000
#घोषणा RFCR_APAT3	0x04000000
#घोषणा RFCR_APAT2	0x02000000
#घोषणा RFCR_APAT1	0x01000000
#घोषणा RFCR_APAT0	0x00800000
#घोषणा RFCR_AARP	0x00400000
#घोषणा RFCR_MHEN	0x00200000
#घोषणा RFCR_UHEN	0x00100000
#घोषणा RFCR_ULM	0x00080000

#घोषणा VRCR_RUDPE	0x00000080
#घोषणा VRCR_RTCPE	0x00000040
#घोषणा VRCR_RIPE	0x00000020
#घोषणा VRCR_IPEN	0x00000010
#घोषणा VRCR_DUTF	0x00000008
#घोषणा VRCR_DVTF	0x00000004
#घोषणा VRCR_VTREN	0x00000002
#घोषणा VRCR_VTDEN	0x00000001

#घोषणा VTCR_PPCHK	0x00000008
#घोषणा VTCR_GCHK	0x00000004
#घोषणा VTCR_VPPTI	0x00000002
#घोषणा VTCR_VGTI	0x00000001

#घोषणा CR		0x00
#घोषणा CFG		0x04
#घोषणा MEAR		0x08
#घोषणा PTSCR		0x0c
#घोषणा	ISR		0x10
#घोषणा	IMR		0x14
#घोषणा	IER		0x18
#घोषणा	IHR		0x1c
#घोषणा TXDP		0x20
#घोषणा TXDP_HI		0x24
#घोषणा TXCFG		0x28
#घोषणा GPIOR		0x2c
#घोषणा RXDP		0x30
#घोषणा RXDP_HI		0x34
#घोषणा RXCFG		0x38
#घोषणा PQCR		0x3c
#घोषणा WCSR		0x40
#घोषणा PCR		0x44
#घोषणा RFCR		0x48
#घोषणा RFDR		0x4c

#घोषणा SRR		0x58

#घोषणा VRCR		0xbc
#घोषणा VTCR		0xc0
#घोषणा VDR		0xc4
#घोषणा CCSR		0xcc

#घोषणा TBICR		0xe0
#घोषणा TBISR		0xe4
#घोषणा TANAR		0xe8
#घोषणा TANLPAR		0xec
#घोषणा TANER		0xf0
#घोषणा TESR		0xf4

#घोषणा TBICR_MR_AN_ENABLE	0x00001000
#घोषणा TBICR_MR_RESTART_AN	0x00000200

#घोषणा TBISR_MR_LINK_STATUS	0x00000020
#घोषणा TBISR_MR_AN_COMPLETE	0x00000004

#घोषणा TANAR_PS2 		0x00000100
#घोषणा TANAR_PS1 		0x00000080
#घोषणा TANAR_HALF_DUP 		0x00000040
#घोषणा TANAR_FULL_DUP 		0x00000020

#घोषणा GPIOR_GP5_OE		0x00000200
#घोषणा GPIOR_GP4_OE		0x00000100
#घोषणा GPIOR_GP3_OE		0x00000080
#घोषणा GPIOR_GP2_OE		0x00000040
#घोषणा GPIOR_GP1_OE		0x00000020
#घोषणा GPIOR_GP3_OUT		0x00000004
#घोषणा GPIOR_GP1_OUT		0x00000001

#घोषणा LINK_AUTONEGOTIATE	0x01
#घोषणा LINK_DOWN		0x02
#घोषणा LINK_UP			0x04

#घोषणा HW_ADDR_LEN	माप(dma_addr_t)
#घोषणा desc_addr_set(desc, addr)				\
	करो अणु							\
		((desc)[0] = cpu_to_le32(addr));		\
		अगर (HW_ADDR_LEN == 8)		 		\
			(desc)[1] = cpu_to_le32(((u64)addr) >> 32);	\
	पूर्ण जबतक(0)
#घोषणा desc_addr_get(desc)					\
	(le32_to_cpu((desc)[0]) | \
	(HW_ADDR_LEN == 8 ? ((dma_addr_t)le32_to_cpu((desc)[1]))<<32 : 0))

#घोषणा DESC_LINK		0
#घोषणा DESC_BUFPTR		(DESC_LINK + HW_ADDR_LEN/4)
#घोषणा DESC_CMDSTS		(DESC_BUFPTR + HW_ADDR_LEN/4)
#घोषणा DESC_EXTSTS		(DESC_CMDSTS + 4/4)

#घोषणा CMDSTS_OWN	0x80000000
#घोषणा CMDSTS_MORE	0x40000000
#घोषणा CMDSTS_INTR	0x20000000
#घोषणा CMDSTS_ERR	0x10000000
#घोषणा CMDSTS_OK	0x08000000
#घोषणा CMDSTS_RUNT	0x00200000
#घोषणा CMDSTS_LEN_MASK	0x0000ffff

#घोषणा CMDSTS_DEST_MASK	0x01800000
#घोषणा CMDSTS_DEST_SELF	0x00800000
#घोषणा CMDSTS_DEST_MULTI	0x01000000

#घोषणा DESC_SIZE	8		/* Should be cache line sized */

काष्ठा rx_info अणु
	spinlock_t	lock;
	पूर्णांक		up;
	अचिन्हित दीर्घ	idle;

	काष्ठा sk_buff	*skbs[NR_RX_DESC];

	__le32		*next_rx_desc;
	u16		next_rx, next_empty;

	__le32		*descs;
	dma_addr_t	phy_descs;
पूर्ण;


काष्ठा ns83820 अणु
	u8			__iomem *base;

	काष्ठा pci_dev		*pci_dev;
	काष्ठा net_device	*ndev;

	काष्ठा rx_info		rx_info;
	काष्ठा tasklet_काष्ठा	rx_tasklet;

	अचिन्हित		ihr;
	काष्ठा work_काष्ठा	tq_refill;

	/* protects everything below.  irqsave when using. */
	spinlock_t		misc_lock;

	u32			CFG_cache;

	u32			MEAR_cache;
	u32			IMR_cache;

	अचिन्हित		linkstate;

	spinlock_t	tx_lock;

	u16		tx_करोne_idx;
	u16		tx_idx;
	अस्थिर u16	tx_मुक्त_idx;	/* idx of मुक्त desc chain */
	u16		tx_पूर्णांकr_idx;

	atomic_t	nr_tx_skbs;
	काष्ठा sk_buff	*tx_skbs[NR_TX_DESC];

	अक्षर		pad[16] __attribute__((aligned(16)));
	__le32		*tx_descs;
	dma_addr_t	tx_phy_descs;

	काष्ठा समयr_list	tx_watchकरोg;
पूर्ण;

अटल अंतरभूत काष्ठा ns83820 *PRIV(काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

#घोषणा __kick_rx(dev)	ग_लिखोl(CR_RXE, dev->base + CR)

अटल अंतरभूत व्योम kick_rx(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	dprपूर्णांकk("kick_rx: maybe kicking\n");
	अगर (test_and_clear_bit(0, &dev->rx_info.idle)) अणु
		dprपूर्णांकk("actually kicking\n");
		ग_लिखोl(dev->rx_info.phy_descs +
			(4 * DESC_SIZE * dev->rx_info.next_rx),
		       dev->base + RXDP);
		अगर (dev->rx_info.next_rx == dev->rx_info.next_empty)
			prपूर्णांकk(KERN_DEBUG "%s: uh-oh: next_rx == next_empty???\n",
				ndev->name);
		__kick_rx(dev);
	पूर्ण
पूर्ण

//मुक्त = (tx_करोne_idx + NR_TX_DESC-2 - मुक्त_idx) % NR_TX_DESC
#घोषणा start_tx_okay(dev)	\
	(((NR_TX_DESC-2 + dev->tx_करोne_idx - dev->tx_मुक्त_idx) % NR_TX_DESC) > MIN_TX_DESC_FREE)

/* Packet Receiver
 *
 * The hardware supports linked lists of receive descriptors क्रम
 * which ownership is transferred back and क्रमth by means of an
 * ownership bit.  While the hardware करोes support the use of a
 * ring क्रम receive descriptors, we only make use of a chain in
 * an attempt to reduce bus traffic under heavy load scenarios.
 * This will also make bugs a bit more obvious.  The current code
 * only makes use of a single rx chain; I hope to implement
 * priority based rx क्रम version 1.0.  Goal: even under overload
 * conditions, still route realसमय traffic with as low jitter as
 * possible.
 */
अटल अंतरभूत व्योम build_rx_desc(काष्ठा ns83820 *dev, __le32 *desc, dma_addr_t link, dma_addr_t buf, u32 cmdsts, u32 extsts)
अणु
	desc_addr_set(desc + DESC_LINK, link);
	desc_addr_set(desc + DESC_BUFPTR, buf);
	desc[DESC_EXTSTS] = cpu_to_le32(extsts);
	mb();
	desc[DESC_CMDSTS] = cpu_to_le32(cmdsts);
पूर्ण

#घोषणा nr_rx_empty(dev) ((NR_RX_DESC-2 + dev->rx_info.next_rx - dev->rx_info.next_empty) % NR_RX_DESC)
अटल अंतरभूत पूर्णांक ns83820_add_rx_skb(काष्ठा ns83820 *dev, काष्ठा sk_buff *skb)
अणु
	अचिन्हित next_empty;
	u32 cmdsts;
	__le32 *sg;
	dma_addr_t buf;

	next_empty = dev->rx_info.next_empty;

	/* करोn't overrun last rx marker */
	अगर (unlikely(nr_rx_empty(dev) <= 2)) अणु
		kमुक्त_skb(skb);
		वापस 1;
	पूर्ण

#अगर 0
	dprपूर्णांकk("next_empty[%d] nr_used[%d] next_rx[%d]\n",
		dev->rx_info.next_empty,
		dev->rx_info.nr_used,
		dev->rx_info.next_rx
		);
#पूर्ण_अगर

	sg = dev->rx_info.descs + (next_empty * DESC_SIZE);
	BUG_ON(शून्य != dev->rx_info.skbs[next_empty]);
	dev->rx_info.skbs[next_empty] = skb;

	dev->rx_info.next_empty = (next_empty + 1) % NR_RX_DESC;
	cmdsts = REAL_RX_BUF_SIZE | CMDSTS_INTR;
	buf = dma_map_single(&dev->pci_dev->dev, skb->data, REAL_RX_BUF_SIZE,
			     DMA_FROM_DEVICE);
	build_rx_desc(dev, sg, 0, buf, cmdsts, 0);
	/* update link of previous rx */
	अगर (likely(next_empty != dev->rx_info.next_rx))
		dev->rx_info.descs[((NR_RX_DESC + next_empty - 1) % NR_RX_DESC) * DESC_SIZE] = cpu_to_le32(dev->rx_info.phy_descs + (next_empty * DESC_SIZE * 4));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rx_refill(काष्ठा net_device *ndev, gfp_t gfp)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	अचिन्हित i;
	अचिन्हित दीर्घ flags = 0;

	अगर (unlikely(nr_rx_empty(dev) <= 2))
		वापस 0;

	dprपूर्णांकk("rx_refill(%p)\n", ndev);
	अगर (gfp == GFP_ATOMIC)
		spin_lock_irqsave(&dev->rx_info.lock, flags);
	क्रम (i=0; i<NR_RX_DESC; i++) अणु
		काष्ठा sk_buff *skb;
		दीर्घ res;

		/* extra 16 bytes क्रम alignment */
		skb = __netdev_alloc_skb(ndev, REAL_RX_BUF_SIZE+16, gfp);
		अगर (unlikely(!skb))
			अवरोध;

		skb_reserve(skb, skb->data - PTR_ALIGN(skb->data, 16));
		अगर (gfp != GFP_ATOMIC)
			spin_lock_irqsave(&dev->rx_info.lock, flags);
		res = ns83820_add_rx_skb(dev, skb);
		अगर (gfp != GFP_ATOMIC)
			spin_unlock_irqrestore(&dev->rx_info.lock, flags);
		अगर (res) अणु
			i = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (gfp == GFP_ATOMIC)
		spin_unlock_irqrestore(&dev->rx_info.lock, flags);

	वापस i ? 0 : -ENOMEM;
पूर्ण

अटल व्योम rx_refill_atomic(काष्ठा net_device *ndev)
अणु
	rx_refill(ndev, GFP_ATOMIC);
पूर्ण

/* REFILL */
अटल अंतरभूत व्योम queue_refill(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ns83820 *dev = container_of(work, काष्ठा ns83820, tq_refill);
	काष्ठा net_device *ndev = dev->ndev;

	rx_refill(ndev, GFP_KERNEL);
	अगर (dev->rx_info.up)
		kick_rx(ndev);
पूर्ण

अटल अंतरभूत व्योम clear_rx_desc(काष्ठा ns83820 *dev, अचिन्हित i)
अणु
	build_rx_desc(dev, dev->rx_info.descs + (DESC_SIZE * i), 0, 0, CMDSTS_OWN, 0);
पूर्ण

अटल व्योम phy_पूर्णांकr(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	अटल स्थिर अक्षर *speeds[] = अणु "10", "100", "1000", "1000(?)", "1000F" पूर्ण;
	u32 cfg, new_cfg;
	u32 tanar, tanlpar;
	पूर्णांक speed, fullduplex, newlinkstate;

	cfg = पढ़ोl(dev->base + CFG) ^ SPDSTS_POLARITY;

	अगर (dev->CFG_cache & CFG_TBI_EN) अणु
		u32 __maybe_unused tbisr;

		/* we have an optical transceiver */
		tbisr = पढ़ोl(dev->base + TBISR);
		tanar = पढ़ोl(dev->base + TANAR);
		tanlpar = पढ़ोl(dev->base + TANLPAR);
		dprपूर्णांकk("phy_intr: tbisr=%08x, tanar=%08x, tanlpar=%08x\n",
			tbisr, tanar, tanlpar);

		अगर ( (fullduplex = (tanlpar & TANAR_FULL_DUP) &&
		      (tanar & TANAR_FULL_DUP)) ) अणु

			/* both of us are full duplex */
			ग_लिखोl(पढ़ोl(dev->base + TXCFG)
			       | TXCFG_CSI | TXCFG_HBI | TXCFG_ATP,
			       dev->base + TXCFG);
			ग_लिखोl(पढ़ोl(dev->base + RXCFG) | RXCFG_RX_FD,
			       dev->base + RXCFG);
			/* Light up full duplex LED */
			ग_लिखोl(पढ़ोl(dev->base + GPIOR) | GPIOR_GP1_OUT,
			       dev->base + GPIOR);

		पूर्ण अन्यथा अगर (((tanlpar & TANAR_HALF_DUP) &&
			    (tanar & TANAR_HALF_DUP)) ||
			   ((tanlpar & TANAR_FULL_DUP) &&
			    (tanar & TANAR_HALF_DUP)) ||
			   ((tanlpar & TANAR_HALF_DUP) &&
			    (tanar & TANAR_FULL_DUP))) अणु

			/* one or both of us are half duplex */
			ग_लिखोl((पढ़ोl(dev->base + TXCFG)
				& ~(TXCFG_CSI | TXCFG_HBI)) | TXCFG_ATP,
			       dev->base + TXCFG);
			ग_लिखोl(पढ़ोl(dev->base + RXCFG) & ~RXCFG_RX_FD,
			       dev->base + RXCFG);
			/* Turn off full duplex LED */
			ग_लिखोl(पढ़ोl(dev->base + GPIOR) & ~GPIOR_GP1_OUT,
			       dev->base + GPIOR);
		पूर्ण

		speed = 4; /* 1000F */

	पूर्ण अन्यथा अणु
		/* we have a copper transceiver */
		new_cfg = dev->CFG_cache & ~(CFG_SB | CFG_MODE_1000 | CFG_SPDSTS);

		अगर (cfg & CFG_SPDSTS1)
			new_cfg |= CFG_MODE_1000;
		अन्यथा
			new_cfg &= ~CFG_MODE_1000;

		speed = ((cfg / CFG_SPDSTS0) & 3);
		fullduplex = (cfg & CFG_DUPSTS);

		अगर (fullduplex) अणु
			new_cfg |= CFG_SB;
			ग_लिखोl(पढ़ोl(dev->base + TXCFG)
					| TXCFG_CSI | TXCFG_HBI,
			       dev->base + TXCFG);
			ग_लिखोl(पढ़ोl(dev->base + RXCFG) | RXCFG_RX_FD,
			       dev->base + RXCFG);
		पूर्ण अन्यथा अणु
			ग_लिखोl(पढ़ोl(dev->base + TXCFG)
					& ~(TXCFG_CSI | TXCFG_HBI),
			       dev->base + TXCFG);
			ग_लिखोl(पढ़ोl(dev->base + RXCFG) & ~(RXCFG_RX_FD),
			       dev->base + RXCFG);
		पूर्ण

		अगर ((cfg & CFG_LNKSTS) &&
		    ((new_cfg ^ dev->CFG_cache) != 0)) अणु
			ग_लिखोl(new_cfg, dev->base + CFG);
			dev->CFG_cache = new_cfg;
		पूर्ण

		dev->CFG_cache &= ~CFG_SPDSTS;
		dev->CFG_cache |= cfg & CFG_SPDSTS;
	पूर्ण

	newlinkstate = (cfg & CFG_LNKSTS) ? LINK_UP : LINK_DOWN;

	अगर (newlinkstate & LINK_UP &&
	    dev->linkstate != newlinkstate) अणु
		netअगर_start_queue(ndev);
		netअगर_wake_queue(ndev);
		prपूर्णांकk(KERN_INFO "%s: link now %s mbps, %s duplex and up.\n",
			ndev->name,
			speeds[speed],
			fullduplex ? "full" : "half");
	पूर्ण अन्यथा अगर (newlinkstate & LINK_DOWN &&
		   dev->linkstate != newlinkstate) अणु
		netअगर_stop_queue(ndev);
		prपूर्णांकk(KERN_INFO "%s: link now down.\n", ndev->name);
	पूर्ण

	dev->linkstate = newlinkstate;
पूर्ण

अटल पूर्णांक ns83820_setup_rx(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	अचिन्हित i;
	पूर्णांक ret;

	dprपूर्णांकk("ns83820_setup_rx(%p)\n", ndev);

	dev->rx_info.idle = 1;
	dev->rx_info.next_rx = 0;
	dev->rx_info.next_rx_desc = dev->rx_info.descs;
	dev->rx_info.next_empty = 0;

	क्रम (i=0; i<NR_RX_DESC; i++)
		clear_rx_desc(dev, i);

	ग_लिखोl(0, dev->base + RXDP_HI);
	ग_लिखोl(dev->rx_info.phy_descs, dev->base + RXDP);

	ret = rx_refill(ndev, GFP_KERNEL);
	अगर (!ret) अणु
		dprपूर्णांकk("starting receiver\n");
		/* prevent the पूर्णांकerrupt handler from stomping on us */
		spin_lock_irq(&dev->rx_info.lock);

		ग_लिखोl(0x0001, dev->base + CCSR);
		ग_लिखोl(0, dev->base + RFCR);
		ग_लिखोl(0x7fc00000, dev->base + RFCR);
		ग_लिखोl(0xffc00000, dev->base + RFCR);

		dev->rx_info.up = 1;

		phy_पूर्णांकr(ndev);

		/* Okay, let it rip */
		spin_lock(&dev->misc_lock);
		dev->IMR_cache |= ISR_PHY;
		dev->IMR_cache |= ISR_RXRCMP;
		//dev->IMR_cache |= ISR_RXERR;
		//dev->IMR_cache |= ISR_RXOK;
		dev->IMR_cache |= ISR_RXORN;
		dev->IMR_cache |= ISR_RXSOVR;
		dev->IMR_cache |= ISR_RXDESC;
		dev->IMR_cache |= ISR_RXIDLE;
		dev->IMR_cache |= ISR_TXDESC;
		dev->IMR_cache |= ISR_TXIDLE;

		ग_लिखोl(dev->IMR_cache, dev->base + IMR);
		ग_लिखोl(1, dev->base + IER);
		spin_unlock(&dev->misc_lock);

		kick_rx(ndev);

		spin_unlock_irq(&dev->rx_info.lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ns83820_cleanup_rx(काष्ठा ns83820 *dev)
अणु
	अचिन्हित i;
	अचिन्हित दीर्घ flags;

	dprपूर्णांकk("ns83820_cleanup_rx(%p)\n", dev);

	/* disable receive पूर्णांकerrupts */
	spin_lock_irqsave(&dev->misc_lock, flags);
	dev->IMR_cache &= ~(ISR_RXOK | ISR_RXDESC | ISR_RXERR | ISR_RXEARLY | ISR_RXIDLE);
	ग_लिखोl(dev->IMR_cache, dev->base + IMR);
	spin_unlock_irqrestore(&dev->misc_lock, flags);

	/* synchronize with the पूर्णांकerrupt handler and समाप्त it */
	dev->rx_info.up = 0;
	synchronize_irq(dev->pci_dev->irq);

	/* touch the pci bus... */
	पढ़ोl(dev->base + IMR);

	/* assumes the transmitter is alपढ़ोy disabled and reset */
	ग_लिखोl(0, dev->base + RXDP_HI);
	ग_लिखोl(0, dev->base + RXDP);

	क्रम (i=0; i<NR_RX_DESC; i++) अणु
		काष्ठा sk_buff *skb = dev->rx_info.skbs[i];
		dev->rx_info.skbs[i] = शून्य;
		clear_rx_desc(dev, i);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम ns83820_rx_kick(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	/*अगर (nr_rx_empty(dev) >= NR_RX_DESC/4)*/ अणु
		अगर (dev->rx_info.up) अणु
			rx_refill_atomic(ndev);
			kick_rx(ndev);
		पूर्ण
	पूर्ण

	अगर (dev->rx_info.up && nr_rx_empty(dev) > NR_RX_DESC*3/4)
		schedule_work(&dev->tq_refill);
	अन्यथा
		kick_rx(ndev);
	अगर (dev->rx_info.idle)
		prपूर्णांकk(KERN_DEBUG "%s: BAD\n", ndev->name);
पूर्ण

/* rx_irq
 *
 */
अटल व्योम rx_irq(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	काष्ठा rx_info *info = &dev->rx_info;
	अचिन्हित next_rx;
	पूर्णांक rx_rc, len;
	u32 cmdsts;
	__le32 *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक nr = 0;

	dprपूर्णांकk("rx_irq(%p)\n", ndev);
	dprपूर्णांकk("rxdp: %08x, descs: %08lx next_rx[%d]: %p next_empty[%d]: %p\n",
		पढ़ोl(dev->base + RXDP),
		(दीर्घ)(dev->rx_info.phy_descs),
		(पूर्णांक)dev->rx_info.next_rx,
		(dev->rx_info.descs + (DESC_SIZE * dev->rx_info.next_rx)),
		(पूर्णांक)dev->rx_info.next_empty,
		(dev->rx_info.descs + (DESC_SIZE * dev->rx_info.next_empty))
		);

	spin_lock_irqsave(&info->lock, flags);
	अगर (!info->up)
		जाओ out;

	dprपूर्णांकk("walking descs\n");
	next_rx = info->next_rx;
	desc = info->next_rx_desc;
	जबतक ((CMDSTS_OWN & (cmdsts = le32_to_cpu(desc[DESC_CMDSTS]))) &&
	       (cmdsts != CMDSTS_OWN)) अणु
		काष्ठा sk_buff *skb;
		u32 extsts = le32_to_cpu(desc[DESC_EXTSTS]);
		dma_addr_t bufptr = desc_addr_get(desc + DESC_BUFPTR);

		dprपूर्णांकk("cmdsts: %08x\n", cmdsts);
		dprपूर्णांकk("link: %08x\n", cpu_to_le32(desc[DESC_LINK]));
		dprपूर्णांकk("extsts: %08x\n", extsts);

		skb = info->skbs[next_rx];
		info->skbs[next_rx] = शून्य;
		info->next_rx = (next_rx + 1) % NR_RX_DESC;

		mb();
		clear_rx_desc(dev, next_rx);

		dma_unmap_single(&dev->pci_dev->dev, bufptr, RX_BUF_SIZE,
				 DMA_FROM_DEVICE);
		len = cmdsts & CMDSTS_LEN_MASK;
#अगर_घोषित NS83820_VLAN_ACCEL_SUPPORT
		/* NH: As was mentioned below, this chip is kinda
		 * brain dead about vlan tag stripping.  Frames
		 * that are 64 bytes with a vlan header appended
		 * like arp frames, or pings, are flagged as Runts
		 * when the tag is stripped and hardware.  This
		 * also means that the OK bit in the descriptor
		 * is cleared when the frame comes in so we have
		 * to करो a specअगरic length check here to make sure
		 * the frame would have been ok, had we not stripped
		 * the tag.
		 */
		अगर (likely((CMDSTS_OK & cmdsts) ||
			((cmdsts & CMDSTS_RUNT) && len >= 56))) अणु
#अन्यथा
		अगर (likely(CMDSTS_OK & cmdsts)) अणु
#पूर्ण_अगर
			skb_put(skb, len);
			अगर (unlikely(!skb))
				जाओ netdev_mangle_me_harder_failed;
			अगर (cmdsts & CMDSTS_DEST_MULTI)
				ndev->stats.multicast++;
			ndev->stats.rx_packets++;
			ndev->stats.rx_bytes += len;
			अगर ((extsts & 0x002a0000) && !(extsts & 0x00540000)) अणु
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			पूर्ण अन्यथा अणु
				skb_checksum_none_निश्चित(skb);
			पूर्ण
			skb->protocol = eth_type_trans(skb, ndev);
#अगर_घोषित NS83820_VLAN_ACCEL_SUPPORT
			अगर(extsts & EXTSTS_VPKT) अणु
				अचिन्हित लघु tag;

				tag = ntohs(extsts & EXTSTS_VTG_MASK);
				__vlan_hwaccel_put_tag(skb, htons(ETH_P_IPV6), tag);
			पूर्ण
#पूर्ण_अगर
			rx_rc = netअगर_rx(skb);
			अगर (NET_RX_DROP == rx_rc) अणु
netdev_mangle_me_harder_failed:
				ndev->stats.rx_dropped++;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_kमुक्त_skb_irq(skb);
		पूर्ण

		nr++;
		next_rx = info->next_rx;
		desc = info->descs + (DESC_SIZE * next_rx);
	पूर्ण
	info->next_rx = next_rx;
	info->next_rx_desc = info->descs + (DESC_SIZE * next_rx);

out:
	अगर (0 && !nr) अणु
		Dprपूर्णांकk("dazed: cmdsts_f: %08x\n", cmdsts);
	पूर्ण

	spin_unlock_irqrestore(&info->lock, flags);
पूर्ण

अटल व्योम rx_action(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ns83820 *dev = from_tasklet(dev, t, rx_tasklet);
	काष्ठा net_device *ndev = dev->ndev;
	rx_irq(ndev);
	ग_लिखोl(ihr, dev->base + IHR);

	spin_lock_irq(&dev->misc_lock);
	dev->IMR_cache |= ISR_RXDESC;
	ग_लिखोl(dev->IMR_cache, dev->base + IMR);
	spin_unlock_irq(&dev->misc_lock);

	rx_irq(ndev);
	ns83820_rx_kick(ndev);
पूर्ण

/* Packet Transmit code
 */
अटल अंतरभूत व्योम kick_tx(काष्ठा ns83820 *dev)
अणु
	dprपूर्णांकk("kick_tx(%p): tx_idx=%d free_idx=%d\n",
		dev, dev->tx_idx, dev->tx_मुक्त_idx);
	ग_लिखोl(CR_TXE, dev->base + CR);
पूर्ण

/* No spinlock needed on the transmit irq path as the पूर्णांकerrupt handler is
 * serialized.
 */
अटल व्योम करो_tx_करोne(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	u32 cmdsts, tx_करोne_idx;
	__le32 *desc;

	dprपूर्णांकk("do_tx_done(%p)\n", ndev);
	tx_करोne_idx = dev->tx_करोne_idx;
	desc = dev->tx_descs + (tx_करोne_idx * DESC_SIZE);

	dprपूर्णांकk("tx_done_idx=%d free_idx=%d cmdsts=%08x\n",
		tx_करोne_idx, dev->tx_मुक्त_idx, le32_to_cpu(desc[DESC_CMDSTS]));
	जबतक ((tx_करोne_idx != dev->tx_मुक्त_idx) &&
	       !(CMDSTS_OWN & (cmdsts = le32_to_cpu(desc[DESC_CMDSTS]))) ) अणु
		काष्ठा sk_buff *skb;
		अचिन्हित len;
		dma_addr_t addr;

		अगर (cmdsts & CMDSTS_ERR)
			ndev->stats.tx_errors++;
		अगर (cmdsts & CMDSTS_OK)
			ndev->stats.tx_packets++;
		अगर (cmdsts & CMDSTS_OK)
			ndev->stats.tx_bytes += cmdsts & 0xffff;

		dprपूर्णांकk("tx_done_idx=%d free_idx=%d cmdsts=%08x\n",
			tx_करोne_idx, dev->tx_मुक्त_idx, cmdsts);
		skb = dev->tx_skbs[tx_करोne_idx];
		dev->tx_skbs[tx_करोne_idx] = शून्य;
		dprपूर्णांकk("done(%p)\n", skb);

		len = cmdsts & CMDSTS_LEN_MASK;
		addr = desc_addr_get(desc + DESC_BUFPTR);
		अगर (skb) अणु
			dma_unmap_single(&dev->pci_dev->dev, addr, len,
					 DMA_TO_DEVICE);
			dev_consume_skb_irq(skb);
			atomic_dec(&dev->nr_tx_skbs);
		पूर्ण अन्यथा
			dma_unmap_page(&dev->pci_dev->dev, addr, len,
				       DMA_TO_DEVICE);

		tx_करोne_idx = (tx_करोne_idx + 1) % NR_TX_DESC;
		dev->tx_करोne_idx = tx_करोne_idx;
		desc[DESC_CMDSTS] = cpu_to_le32(0);
		mb();
		desc = dev->tx_descs + (tx_करोne_idx * DESC_SIZE);
	पूर्ण

	/* Allow network stack to resume queueing packets after we've
	 * finished transmitting at least 1/4 of the packets in the queue.
	 */
	अगर (netअगर_queue_stopped(ndev) && start_tx_okay(dev)) अणु
		dprपूर्णांकk("start_queue(%p)\n", ndev);
		netअगर_start_queue(ndev);
		netअगर_wake_queue(ndev);
	पूर्ण
पूर्ण

अटल व्योम ns83820_cleanup_tx(काष्ठा ns83820 *dev)
अणु
	अचिन्हित i;

	क्रम (i=0; i<NR_TX_DESC; i++) अणु
		काष्ठा sk_buff *skb = dev->tx_skbs[i];
		dev->tx_skbs[i] = शून्य;
		अगर (skb) अणु
			__le32 *desc = dev->tx_descs + (i * DESC_SIZE);
			dma_unmap_single(&dev->pci_dev->dev,
					 desc_addr_get(desc + DESC_BUFPTR),
					 le32_to_cpu(desc[DESC_CMDSTS]) & CMDSTS_LEN_MASK,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb_irq(skb);
			atomic_dec(&dev->nr_tx_skbs);
		पूर्ण
	पूर्ण

	स_रखो(dev->tx_descs, 0, NR_TX_DESC * DESC_SIZE * 4);
पूर्ण

/* transmit routine.  This code relies on the network layer serializing
 * its calls in, but will run happily in parallel with the पूर्णांकerrupt
 * handler.  This code currently has provisions क्रम fragmenting tx buffers
 * जबतक trying to track करोwn a bug in either the zero copy code or
 * the tx fअगरo (hence the MAX_FRAG_LEN).
 */
अटल netdev_tx_t ns83820_hard_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	u32 मुक्त_idx, cmdsts, extsts;
	पूर्णांक nr_मुक्त, nr_frags;
	अचिन्हित tx_करोne_idx, last_idx;
	dma_addr_t buf;
	अचिन्हित len;
	skb_frag_t *frag;
	पूर्णांक stopped = 0;
	पूर्णांक करो_पूर्णांकr = 0;
	अस्थिर __le32 *first_desc;

	dprपूर्णांकk("ns83820_hard_start_xmit\n");

	nr_frags =  skb_shinfo(skb)->nr_frags;
again:
	अगर (unlikely(dev->CFG_cache & CFG_LNKSTS)) अणु
		netअगर_stop_queue(ndev);
		अगर (unlikely(dev->CFG_cache & CFG_LNKSTS))
			वापस NETDEV_TX_BUSY;
		netअगर_start_queue(ndev);
	पूर्ण

	last_idx = मुक्त_idx = dev->tx_मुक्त_idx;
	tx_करोne_idx = dev->tx_करोne_idx;
	nr_मुक्त = (tx_करोne_idx + NR_TX_DESC-2 - मुक्त_idx) % NR_TX_DESC;
	nr_मुक्त -= 1;
	अगर (nr_मुक्त <= nr_frags) अणु
		dprपूर्णांकk("stop_queue - not enough(%p)\n", ndev);
		netअगर_stop_queue(ndev);

		/* Check again: we may have raced with a tx करोne irq */
		अगर (dev->tx_करोne_idx != tx_करोne_idx) अणु
			dprपूर्णांकk("restart queue(%p)\n", ndev);
			netअगर_start_queue(ndev);
			जाओ again;
		पूर्ण
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (मुक्त_idx == dev->tx_पूर्णांकr_idx) अणु
		करो_पूर्णांकr = 1;
		dev->tx_पूर्णांकr_idx = (dev->tx_पूर्णांकr_idx + NR_TX_DESC/4) % NR_TX_DESC;
	पूर्ण

	nr_मुक्त -= nr_frags;
	अगर (nr_मुक्त < MIN_TX_DESC_FREE) अणु
		dprपूर्णांकk("stop_queue - last entry(%p)\n", ndev);
		netअगर_stop_queue(ndev);
		stopped = 1;
	पूर्ण

	frag = skb_shinfo(skb)->frags;
	अगर (!nr_frags)
		frag = शून्य;
	extsts = 0;
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		extsts |= EXTSTS_IPPKT;
		अगर (IPPROTO_TCP == ip_hdr(skb)->protocol)
			extsts |= EXTSTS_TCPPKT;
		अन्यथा अगर (IPPROTO_UDP == ip_hdr(skb)->protocol)
			extsts |= EXTSTS_UDPPKT;
	पूर्ण

#अगर_घोषित NS83820_VLAN_ACCEL_SUPPORT
	अगर (skb_vlan_tag_present(skb)) अणु
		/* fetch the vlan tag info out of the
		 * ancillary data अगर the vlan code
		 * is using hw vlan acceleration
		 */
		लघु tag = skb_vlan_tag_get(skb);
		extsts |= (EXTSTS_VPKT | htons(tag));
	पूर्ण
#पूर्ण_अगर

	len = skb->len;
	अगर (nr_frags)
		len -= skb->data_len;
	buf = dma_map_single(&dev->pci_dev->dev, skb->data, len,
			     DMA_TO_DEVICE);

	first_desc = dev->tx_descs + (मुक्त_idx * DESC_SIZE);

	क्रम (;;) अणु
		अस्थिर __le32 *desc = dev->tx_descs + (मुक्त_idx * DESC_SIZE);

		dprपूर्णांकk("frag[%3u]: %4u @ 0x%08Lx\n", मुक्त_idx, len,
			(अचिन्हित दीर्घ दीर्घ)buf);
		last_idx = मुक्त_idx;
		मुक्त_idx = (मुक्त_idx + 1) % NR_TX_DESC;
		desc[DESC_LINK] = cpu_to_le32(dev->tx_phy_descs + (मुक्त_idx * DESC_SIZE * 4));
		desc_addr_set(desc + DESC_BUFPTR, buf);
		desc[DESC_EXTSTS] = cpu_to_le32(extsts);

		cmdsts = ((nr_frags) ? CMDSTS_MORE : करो_पूर्णांकr ? CMDSTS_INTR : 0);
		cmdsts |= (desc == first_desc) ? 0 : CMDSTS_OWN;
		cmdsts |= len;
		desc[DESC_CMDSTS] = cpu_to_le32(cmdsts);

		अगर (!nr_frags)
			अवरोध;

		buf = skb_frag_dma_map(&dev->pci_dev->dev, frag, 0,
				       skb_frag_size(frag), DMA_TO_DEVICE);
		dprपूर्णांकk("frag: buf=%08Lx  page=%08lx offset=%08lx\n",
			(दीर्घ दीर्घ)buf, (दीर्घ) page_to_pfn(frag->page),
			frag->page_offset);
		len = skb_frag_size(frag);
		frag++;
		nr_frags--;
	पूर्ण
	dprपूर्णांकk("done pkt\n");

	spin_lock_irq(&dev->tx_lock);
	dev->tx_skbs[last_idx] = skb;
	first_desc[DESC_CMDSTS] |= cpu_to_le32(CMDSTS_OWN);
	dev->tx_मुक्त_idx = मुक्त_idx;
	atomic_inc(&dev->nr_tx_skbs);
	spin_unlock_irq(&dev->tx_lock);

	kick_tx(dev);

	/* Check again: we may have raced with a tx करोne irq */
	अगर (stopped && (dev->tx_करोne_idx != tx_करोne_idx) && start_tx_okay(dev))
		netअगर_start_queue(ndev);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ns83820_update_stats(काष्ठा ns83820 *dev)
अणु
	काष्ठा net_device *ndev = dev->ndev;
	u8 __iomem *base = dev->base;

	/* the DP83820 will मुक्तze counters, so we need to पढ़ो all of them */
	ndev->stats.rx_errors		+= पढ़ोl(base + 0x60) & 0xffff;
	ndev->stats.rx_crc_errors	+= पढ़ोl(base + 0x64) & 0xffff;
	ndev->stats.rx_missed_errors	+= पढ़ोl(base + 0x68) & 0xffff;
	ndev->stats.rx_frame_errors	+= पढ़ोl(base + 0x6c) & 0xffff;
	/*ndev->stats.rx_symbol_errors +=*/ पढ़ोl(base + 0x70);
	ndev->stats.rx_length_errors	+= पढ़ोl(base + 0x74) & 0xffff;
	ndev->stats.rx_length_errors	+= पढ़ोl(base + 0x78) & 0xffff;
	/*ndev->stats.rx_baकरोpcode_errors += */ पढ़ोl(base + 0x7c);
	/*ndev->stats.rx_छोड़ो_count += */  पढ़ोl(base + 0x80);
	/*ndev->stats.tx_छोड़ो_count += */  पढ़ोl(base + 0x84);
	ndev->stats.tx_carrier_errors	+= पढ़ोl(base + 0x88) & 0xff;
पूर्ण

अटल काष्ठा net_device_stats *ns83820_get_stats(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);

	/* somewhat overसमाप्त */
	spin_lock_irq(&dev->misc_lock);
	ns83820_update_stats(dev);
	spin_unlock_irq(&dev->misc_lock);

	वापस &ndev->stats;
पूर्ण

/* Let ethtool retrieve info */
अटल पूर्णांक ns83820_get_link_ksettings(काष्ठा net_device *ndev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	u32 cfg, tbicr;
	पूर्णांक fullduplex   = 0;
	u32 supported;

	/*
	 * Here's the list of available ethtool commands from other drivers:
	 *	cmd->advertising =
	 *	ethtool_cmd_speed_set(cmd, ...)
	 *	cmd->duplex =
	 *	cmd->port = 0;
	 *	cmd->phy_address =
	 *	cmd->transceiver = 0;
	 *	cmd->स्वतःneg =
	 *	cmd->maxtxpkt = 0;
	 *	cmd->maxrxpkt = 0;
	 */

	/* पढ़ो current configuration */
	cfg   = पढ़ोl(dev->base + CFG) ^ SPDSTS_POLARITY;
	पढ़ोl(dev->base + TANAR);
	tbicr = पढ़ोl(dev->base + TBICR);

	fullduplex = (cfg & CFG_DUPSTS) ? 1 : 0;

	supported = SUPPORTED_Autoneg;

	अगर (dev->CFG_cache & CFG_TBI_EN) अणु
		/* we have optical पूर्णांकerface */
		supported |= SUPPORTED_1000baseT_Half |
					SUPPORTED_1000baseT_Full |
					SUPPORTED_FIBRE;
		cmd->base.port       = PORT_FIBRE;
	पूर्ण अन्यथा अणु
		/* we have copper */
		supported |= SUPPORTED_10baseT_Half |
			SUPPORTED_10baseT_Full | SUPPORTED_100baseT_Half |
			SUPPORTED_100baseT_Full | SUPPORTED_1000baseT_Half |
			SUPPORTED_1000baseT_Full |
			SUPPORTED_MII;
		cmd->base.port = PORT_MII;
	पूर्ण

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);

	cmd->base.duplex = fullduplex ? DUPLEX_FULL : DUPLEX_HALF;
	चयन (cfg / CFG_SPDSTS0 & 3) अणु
	हाल 2:
		cmd->base.speed = SPEED_1000;
		अवरोध;
	हाल 1:
		cmd->base.speed = SPEED_100;
		अवरोध;
	शेष:
		cmd->base.speed = SPEED_10;
		अवरोध;
	पूर्ण
	cmd->base.स्वतःneg = (tbicr & TBICR_MR_AN_ENABLE)
		? AUTONEG_ENABLE : AUTONEG_DISABLE;
	वापस 0;
पूर्ण

/* Let ethool change settings*/
अटल पूर्णांक ns83820_set_link_ksettings(काष्ठा net_device *ndev,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	u32 cfg, tanar;
	पूर्णांक have_optical = 0;
	पूर्णांक fullduplex   = 0;

	/* पढ़ो current configuration */
	cfg = पढ़ोl(dev->base + CFG) ^ SPDSTS_POLARITY;
	tanar = पढ़ोl(dev->base + TANAR);

	अगर (dev->CFG_cache & CFG_TBI_EN) अणु
		/* we have optical */
		have_optical = 1;
		fullduplex   = (tanar & TANAR_FULL_DUP);

	पूर्ण अन्यथा अणु
		/* we have copper */
		fullduplex = cfg & CFG_DUPSTS;
	पूर्ण

	spin_lock_irq(&dev->misc_lock);
	spin_lock(&dev->tx_lock);

	/* Set duplex */
	अगर (cmd->base.duplex != fullduplex) अणु
		अगर (have_optical) अणु
			/*set full duplex*/
			अगर (cmd->base.duplex == DUPLEX_FULL) अणु
				/* क्रमce full duplex */
				ग_लिखोl(पढ़ोl(dev->base + TXCFG)
					| TXCFG_CSI | TXCFG_HBI | TXCFG_ATP,
					dev->base + TXCFG);
				ग_लिखोl(पढ़ोl(dev->base + RXCFG) | RXCFG_RX_FD,
					dev->base + RXCFG);
				/* Light up full duplex LED */
				ग_लिखोl(पढ़ोl(dev->base + GPIOR) | GPIOR_GP1_OUT,
					dev->base + GPIOR);
			पूर्ण अन्यथा अणु
				/*TODO: set half duplex */
			पूर्ण

		पूर्ण अन्यथा अणु
			/*we have copper*/
			/* TODO: Set duplex क्रम copper cards */
		पूर्ण
		prपूर्णांकk(KERN_INFO "%s: Duplex set via ethtool\n",
		ndev->name);
	पूर्ण

	/* Set स्वतःnegotiation */
	अगर (1) अणु
		अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
			/* restart स्वतः negotiation */
			ग_लिखोl(TBICR_MR_AN_ENABLE | TBICR_MR_RESTART_AN,
				dev->base + TBICR);
			ग_लिखोl(TBICR_MR_AN_ENABLE, dev->base + TBICR);
				dev->linkstate = LINK_AUTONEGOTIATE;

			prपूर्णांकk(KERN_INFO "%s: autoneg enabled via ethtool\n",
				ndev->name);
		पूर्ण अन्यथा अणु
			/* disable स्वतः negotiation */
			ग_लिखोl(0x00000000, dev->base + TBICR);
		पूर्ण

		prपूर्णांकk(KERN_INFO "%s: autoneg %s via ethtool\n", ndev->name,
				cmd->base.स्वतःneg ? "ENABLED" : "DISABLED");
	पूर्ण

	phy_पूर्णांकr(ndev);
	spin_unlock(&dev->tx_lock);
	spin_unlock_irq(&dev->misc_lock);

	वापस 0;
पूर्ण
/* end ethtool get/set support -df */

अटल व्योम ns83820_get_drvinfo(काष्ठा net_device *ndev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	strlcpy(info->driver, "ns83820", माप(info->driver));
	strlcpy(info->version, VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(dev->pci_dev), माप(info->bus_info));
पूर्ण

अटल u32 ns83820_get_link(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	u32 cfg = पढ़ोl(dev->base + CFG) ^ SPDSTS_POLARITY;
	वापस cfg & CFG_LNKSTS ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_drvinfo     = ns83820_get_drvinfo,
	.get_link        = ns83820_get_link,
	.get_link_ksettings = ns83820_get_link_ksettings,
	.set_link_ksettings = ns83820_set_link_ksettings,
पूर्ण;

अटल अंतरभूत व्योम ns83820_disable_पूर्णांकerrupts(काष्ठा ns83820 *dev)
अणु
	ग_लिखोl(0, dev->base + IMR);
	ग_लिखोl(0, dev->base + IER);
	पढ़ोl(dev->base + IER);
पूर्ण

/* this function is called in irq context from the ISR */
अटल व्योम ns83820_mib_isr(काष्ठा ns83820 *dev)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->misc_lock, flags);
	ns83820_update_stats(dev);
	spin_unlock_irqrestore(&dev->misc_lock, flags);
पूर्ण

अटल व्योम ns83820_करो_isr(काष्ठा net_device *ndev, u32 isr);
अटल irqवापस_t ns83820_irq(पूर्णांक foo, व्योम *data)
अणु
	काष्ठा net_device *ndev = data;
	काष्ठा ns83820 *dev = PRIV(ndev);
	u32 isr;
	dprपूर्णांकk("ns83820_irq(%p)\n", ndev);

	dev->ihr = 0;

	isr = पढ़ोl(dev->base + ISR);
	dprपूर्णांकk("irq: %08x\n", isr);
	ns83820_करो_isr(ndev, isr);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ns83820_करो_isr(काष्ठा net_device *ndev, u32 isr)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	अचिन्हित दीर्घ flags;

#अगर_घोषित DEBUG
	अगर (isr & ~(ISR_PHY | ISR_RXDESC | ISR_RXEARLY | ISR_RXOK | ISR_RXERR | ISR_TXIDLE | ISR_TXOK | ISR_TXDESC))
		Dprपूर्णांकk("odd isr? 0x%08x\n", isr);
#पूर्ण_अगर

	अगर (ISR_RXIDLE & isr) अणु
		dev->rx_info.idle = 1;
		Dprपूर्णांकk("oh dear, we are idle\n");
		ns83820_rx_kick(ndev);
	पूर्ण

	अगर ((ISR_RXDESC | ISR_RXOK) & isr) अणु
		prefetch(dev->rx_info.next_rx_desc);

		spin_lock_irqsave(&dev->misc_lock, flags);
		dev->IMR_cache &= ~(ISR_RXDESC | ISR_RXOK);
		ग_लिखोl(dev->IMR_cache, dev->base + IMR);
		spin_unlock_irqrestore(&dev->misc_lock, flags);

		tasklet_schedule(&dev->rx_tasklet);
		//rx_irq(ndev);
		//ग_लिखोl(4, dev->base + IHR);
	पूर्ण

	अगर ((ISR_RXIDLE | ISR_RXORN | ISR_RXDESC | ISR_RXOK | ISR_RXERR) & isr)
		ns83820_rx_kick(ndev);

	अगर (unlikely(ISR_RXSOVR & isr)) अणु
		//prपूर्णांकk("overrun: rxsovr\n");
		ndev->stats.rx_fअगरo_errors++;
	पूर्ण

	अगर (unlikely(ISR_RXORN & isr)) अणु
		//prपूर्णांकk("overrun: rxorn\n");
		ndev->stats.rx_fअगरo_errors++;
	पूर्ण

	अगर ((ISR_RXRCMP & isr) && dev->rx_info.up)
		ग_लिखोl(CR_RXE, dev->base + CR);

	अगर (ISR_TXIDLE & isr) अणु
		u32 txdp;
		txdp = पढ़ोl(dev->base + TXDP);
		dprपूर्णांकk("txdp: %08x\n", txdp);
		txdp -= dev->tx_phy_descs;
		dev->tx_idx = txdp / (DESC_SIZE * 4);
		अगर (dev->tx_idx >= NR_TX_DESC) अणु
			prपूर्णांकk(KERN_ALERT "%s: BUG -- txdp out of range\n", ndev->name);
			dev->tx_idx = 0;
		पूर्ण
		/* The may have been a race between a pci originated पढ़ो
		 * and the descriptor update from the cpu.  Just in हाल,
		 * kick the transmitter अगर the hardware thinks it is on a
		 * dअगरferent descriptor than we are.
		 */
		अगर (dev->tx_idx != dev->tx_मुक्त_idx)
			kick_tx(dev);
	पूर्ण

	/* Defer tx ring processing until more than a minimum amount of
	 * work has accumulated
	 */
	अगर ((ISR_TXDESC | ISR_TXIDLE | ISR_TXOK | ISR_TXERR) & isr) अणु
		spin_lock_irqsave(&dev->tx_lock, flags);
		करो_tx_करोne(ndev);
		spin_unlock_irqrestore(&dev->tx_lock, flags);

		/* Disable TxOk अगर there are no outstanding tx packets.
		 */
		अगर ((dev->tx_करोne_idx == dev->tx_मुक्त_idx) &&
		    (dev->IMR_cache & ISR_TXOK)) अणु
			spin_lock_irqsave(&dev->misc_lock, flags);
			dev->IMR_cache &= ~ISR_TXOK;
			ग_लिखोl(dev->IMR_cache, dev->base + IMR);
			spin_unlock_irqrestore(&dev->misc_lock, flags);
		पूर्ण
	पूर्ण

	/* The TxIdle पूर्णांकerrupt can come in beक्रमe the transmit has
	 * completed.  Normally we reap packets off of the combination
	 * of TxDesc and TxIdle and leave TxOk disabled (since it
	 * occurs on every packet), but when no further irqs of this
	 * nature are expected, we must enable TxOk.
	 */
	अगर ((ISR_TXIDLE & isr) && (dev->tx_करोne_idx != dev->tx_मुक्त_idx)) अणु
		spin_lock_irqsave(&dev->misc_lock, flags);
		dev->IMR_cache |= ISR_TXOK;
		ग_लिखोl(dev->IMR_cache, dev->base + IMR);
		spin_unlock_irqrestore(&dev->misc_lock, flags);
	पूर्ण

	/* MIB पूर्णांकerrupt: one of the statistics counters is about to overflow */
	अगर (unlikely(ISR_MIB & isr))
		ns83820_mib_isr(dev);

	/* PHY: Link up/करोwn/negotiation state change */
	अगर (unlikely(ISR_PHY & isr))
		phy_पूर्णांकr(ndev);

#अगर 0	/* Still working on the पूर्णांकerrupt mitigation strategy */
	अगर (dev->ihr)
		ग_लिखोl(dev->ihr, dev->base + IHR);
#पूर्ण_अगर
पूर्ण

अटल व्योम ns83820_करो_reset(काष्ठा ns83820 *dev, u32 which)
अणु
	Dprपूर्णांकk("resetting chip...\n");
	ग_लिखोl(which, dev->base + CR);
	करो अणु
		schedule();
	पूर्ण जबतक (पढ़ोl(dev->base + CR) & which);
	Dprपूर्णांकk("okay!\n");
पूर्ण

अटल पूर्णांक ns83820_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);

	/* FIXME: protect against पूर्णांकerrupt handler? */
	del_समयr_sync(&dev->tx_watchकरोg);

	ns83820_disable_पूर्णांकerrupts(dev);

	dev->rx_info.up = 0;
	synchronize_irq(dev->pci_dev->irq);

	ns83820_करो_reset(dev, CR_RST);

	synchronize_irq(dev->pci_dev->irq);

	spin_lock_irq(&dev->misc_lock);
	dev->IMR_cache &= ~(ISR_TXURN | ISR_TXIDLE | ISR_TXERR | ISR_TXDESC | ISR_TXOK);
	spin_unlock_irq(&dev->misc_lock);

	ns83820_cleanup_rx(dev);
	ns83820_cleanup_tx(dev);

	वापस 0;
पूर्ण

अटल व्योम ns83820_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
        u32 tx_करोne_idx;
	__le32 *desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->tx_lock, flags);

	tx_करोne_idx = dev->tx_करोne_idx;
	desc = dev->tx_descs + (tx_करोne_idx * DESC_SIZE);

	prपूर्णांकk(KERN_INFO "%s: tx_timeout: tx_done_idx=%d free_idx=%d cmdsts=%08x\n",
		ndev->name,
		tx_करोne_idx, dev->tx_मुक्त_idx, le32_to_cpu(desc[DESC_CMDSTS]));

#अगर defined(DEBUG)
	अणु
		u32 isr;
		isr = पढ़ोl(dev->base + ISR);
		prपूर्णांकk("irq: %08x imr: %08x\n", isr, dev->IMR_cache);
		ns83820_करो_isr(ndev, isr);
	पूर्ण
#पूर्ण_अगर

	करो_tx_करोne(ndev);

	tx_करोne_idx = dev->tx_करोne_idx;
	desc = dev->tx_descs + (tx_करोne_idx * DESC_SIZE);

	prपूर्णांकk(KERN_INFO "%s: after: tx_done_idx=%d free_idx=%d cmdsts=%08x\n",
		ndev->name,
		tx_करोne_idx, dev->tx_मुक्त_idx, le32_to_cpu(desc[DESC_CMDSTS]));

	spin_unlock_irqrestore(&dev->tx_lock, flags);
पूर्ण

अटल व्योम ns83820_tx_watch(काष्ठा समयr_list *t)
अणु
	काष्ठा ns83820 *dev = from_समयr(dev, t, tx_watchकरोg);
	काष्ठा net_device *ndev = dev->ndev;

#अगर defined(DEBUG)
	prपूर्णांकk("ns83820_tx_watch: %u %u %d\n",
		dev->tx_करोne_idx, dev->tx_मुक्त_idx, atomic_पढ़ो(&dev->nr_tx_skbs)
		);
#पूर्ण_अगर

	अगर (समय_after(jअगरfies, dev_trans_start(ndev) + 1*HZ) &&
	    dev->tx_करोne_idx != dev->tx_मुक्त_idx) अणु
		prपूर्णांकk(KERN_DEBUG "%s: ns83820_tx_watch: %u %u %d\n",
			ndev->name,
			dev->tx_करोne_idx, dev->tx_मुक्त_idx,
			atomic_पढ़ो(&dev->nr_tx_skbs));
		ns83820_tx_समयout(ndev, अच_पूर्णांक_उच्च);
	पूर्ण

	mod_समयr(&dev->tx_watchकरोg, jअगरfies + 2*HZ);
पूर्ण

अटल पूर्णांक ns83820_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	अचिन्हित i;
	u32 desc;
	पूर्णांक ret;

	dprपूर्णांकk("ns83820_open\n");

	ग_लिखोl(0, dev->base + PQCR);

	ret = ns83820_setup_rx(ndev);
	अगर (ret)
		जाओ failed;

	स_रखो(dev->tx_descs, 0, 4 * NR_TX_DESC * DESC_SIZE);
	क्रम (i=0; i<NR_TX_DESC; i++) अणु
		dev->tx_descs[(i * DESC_SIZE) + DESC_LINK]
				= cpu_to_le32(
				  dev->tx_phy_descs
				  + ((i+1) % NR_TX_DESC) * DESC_SIZE * 4);
	पूर्ण

	dev->tx_idx = 0;
	dev->tx_करोne_idx = 0;
	desc = dev->tx_phy_descs;
	ग_लिखोl(0, dev->base + TXDP_HI);
	ग_लिखोl(desc, dev->base + TXDP);

	समयr_setup(&dev->tx_watchकरोg, ns83820_tx_watch, 0);
	mod_समयr(&dev->tx_watchकरोg, jअगरfies + 2*HZ);

	netअगर_start_queue(ndev);	/* FIXME: रुको क्रम phy to come up */

	वापस 0;

failed:
	ns83820_stop(ndev);
	वापस ret;
पूर्ण

अटल व्योम ns83820_geपंचांगac(काष्ठा ns83820 *dev, u8 *mac)
अणु
	अचिन्हित i;
	क्रम (i=0; i<3; i++) अणु
		u32 data;

		/* Read from the perfect match memory: this is loaded by
		 * the chip from the EEPROM via the EELOAD self test.
		 */
		ग_लिखोl(i*2, dev->base + RFCR);
		data = पढ़ोl(dev->base + RFDR);

		*mac++ = data;
		*mac++ = data >> 8;
	पूर्ण
पूर्ण

अटल व्योम ns83820_set_multicast(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	u8 __iomem *rfcr = dev->base + RFCR;
	u32 and_mask = 0xffffffff;
	u32 or_mask = 0;
	u32 val;

	अगर (ndev->flags & IFF_PROMISC)
		or_mask |= RFCR_AAU | RFCR_AAM;
	अन्यथा
		and_mask &= ~(RFCR_AAU | RFCR_AAM);

	अगर (ndev->flags & IFF_ALLMULTI || netdev_mc_count(ndev))
		or_mask |= RFCR_AAM;
	अन्यथा
		and_mask &= ~RFCR_AAM;

	spin_lock_irq(&dev->misc_lock);
	val = (पढ़ोl(rfcr) & and_mask) | or_mask;
	/* Ramit : RFCR Write Fix करोc says RFEN must be 0 modअगरy other bits */
	ग_लिखोl(val & ~RFCR_RFEN, rfcr);
	ग_लिखोl(val, rfcr);
	spin_unlock_irq(&dev->misc_lock);
पूर्ण

अटल व्योम ns83820_run_bist(काष्ठा net_device *ndev, स्थिर अक्षर *name, u32 enable, u32 करोne, u32 fail)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	पूर्णांक समयd_out = 0;
	अचिन्हित दीर्घ start;
	u32 status;
	पूर्णांक loops = 0;

	dprपूर्णांकk("%s: start %s\n", ndev->name, name);

	start = jअगरfies;

	ग_लिखोl(enable, dev->base + PTSCR);
	क्रम (;;) अणु
		loops++;
		status = पढ़ोl(dev->base + PTSCR);
		अगर (!(status & enable))
			अवरोध;
		अगर (status & करोne)
			अवरोध;
		अगर (status & fail)
			अवरोध;
		अगर (समय_after_eq(jअगरfies, start + HZ)) अणु
			समयd_out = 1;
			अवरोध;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	अगर (status & fail)
		prपूर्णांकk(KERN_INFO "%s: %s failed! (0x%08x & 0x%08x)\n",
			ndev->name, name, status, fail);
	अन्यथा अगर (समयd_out)
		prपूर्णांकk(KERN_INFO "%s: run_bist %s timed out! (%08x)\n",
			ndev->name, name, status);

	dprपूर्णांकk("%s: done %s in %d loops\n", ndev->name, name, loops);
पूर्ण

#अगर_घोषित PHY_CODE_IS_FINISHED
अटल व्योम ns83820_mii_ग_लिखो_bit(काष्ठा ns83820 *dev, पूर्णांक bit)
अणु
	/* drive MDC low */
	dev->MEAR_cache &= ~MEAR_MDC;
	ग_लिखोl(dev->MEAR_cache, dev->base + MEAR);
	पढ़ोl(dev->base + MEAR);

	/* enable output, set bit */
	dev->MEAR_cache |= MEAR_MDसूची;
	अगर (bit)
		dev->MEAR_cache |= MEAR_MDIO;
	अन्यथा
		dev->MEAR_cache &= ~MEAR_MDIO;

	/* set the output bit */
	ग_लिखोl(dev->MEAR_cache, dev->base + MEAR);
	पढ़ोl(dev->base + MEAR);

	/* Wait.  Max घड़ी rate is 2.5MHz, this way we come in under 1MHz */
	udelay(1);

	/* drive MDC high causing the data bit to be latched */
	dev->MEAR_cache |= MEAR_MDC;
	ग_लिखोl(dev->MEAR_cache, dev->base + MEAR);
	पढ़ोl(dev->base + MEAR);

	/* Wait again... */
	udelay(1);
पूर्ण

अटल पूर्णांक ns83820_mii_पढ़ो_bit(काष्ठा ns83820 *dev)
अणु
	पूर्णांक bit;

	/* drive MDC low, disable output */
	dev->MEAR_cache &= ~MEAR_MDC;
	dev->MEAR_cache &= ~MEAR_MDसूची;
	ग_लिखोl(dev->MEAR_cache, dev->base + MEAR);
	पढ़ोl(dev->base + MEAR);

	/* Wait.  Max घड़ी rate is 2.5MHz, this way we come in under 1MHz */
	udelay(1);

	/* drive MDC high causing the data bit to be latched */
	bit = (पढ़ोl(dev->base + MEAR) & MEAR_MDIO) ? 1 : 0;
	dev->MEAR_cache |= MEAR_MDC;
	ग_लिखोl(dev->MEAR_cache, dev->base + MEAR);

	/* Wait again... */
	udelay(1);

	वापस bit;
पूर्ण

अटल अचिन्हित ns83820_mii_पढ़ो_reg(काष्ठा ns83820 *dev, अचिन्हित phy, अचिन्हित reg)
अणु
	अचिन्हित data = 0;
	पूर्णांक i;

	/* पढ़ो some garbage so that we eventually sync up */
	क्रम (i=0; i<64; i++)
		ns83820_mii_पढ़ो_bit(dev);

	ns83820_mii_ग_लिखो_bit(dev, 0);	/* start */
	ns83820_mii_ग_लिखो_bit(dev, 1);
	ns83820_mii_ग_लिखो_bit(dev, 1);	/* opcode पढ़ो */
	ns83820_mii_ग_लिखो_bit(dev, 0);

	/* ग_लिखो out the phy address: 5 bits, msb first */
	क्रम (i=0; i<5; i++)
		ns83820_mii_ग_लिखो_bit(dev, phy & (0x10 >> i));

	/* ग_लिखो out the रेजिस्टर address, 5 bits, msb first */
	क्रम (i=0; i<5; i++)
		ns83820_mii_ग_लिखो_bit(dev, reg & (0x10 >> i));

	ns83820_mii_पढ़ो_bit(dev);	/* turn around cycles */
	ns83820_mii_पढ़ो_bit(dev);

	/* पढ़ो in the रेजिस्टर data, 16 bits msb first */
	क्रम (i=0; i<16; i++) अणु
		data <<= 1;
		data |= ns83820_mii_पढ़ो_bit(dev);
	पूर्ण

	वापस data;
पूर्ण

अटल अचिन्हित ns83820_mii_ग_लिखो_reg(काष्ठा ns83820 *dev, अचिन्हित phy, अचिन्हित reg, अचिन्हित data)
अणु
	पूर्णांक i;

	/* पढ़ो some garbage so that we eventually sync up */
	क्रम (i=0; i<64; i++)
		ns83820_mii_पढ़ो_bit(dev);

	ns83820_mii_ग_लिखो_bit(dev, 0);	/* start */
	ns83820_mii_ग_लिखो_bit(dev, 1);
	ns83820_mii_ग_लिखो_bit(dev, 0);	/* opcode पढ़ो */
	ns83820_mii_ग_लिखो_bit(dev, 1);

	/* ग_लिखो out the phy address: 5 bits, msb first */
	क्रम (i=0; i<5; i++)
		ns83820_mii_ग_लिखो_bit(dev, phy & (0x10 >> i));

	/* ग_लिखो out the रेजिस्टर address, 5 bits, msb first */
	क्रम (i=0; i<5; i++)
		ns83820_mii_ग_लिखो_bit(dev, reg & (0x10 >> i));

	ns83820_mii_पढ़ो_bit(dev);	/* turn around cycles */
	ns83820_mii_पढ़ो_bit(dev);

	/* पढ़ो in the रेजिस्टर data, 16 bits msb first */
	क्रम (i=0; i<16; i++)
		ns83820_mii_ग_लिखो_bit(dev, (data >> (15 - i)) & 1);

	वापस data;
पूर्ण

अटल व्योम ns83820_probe_phy(काष्ठा net_device *ndev)
अणु
	काष्ठा ns83820 *dev = PRIV(ndev);
	पूर्णांक j;
	अचिन्हित a, b;

	क्रम (j = 0; j < 0x16; j += 4) अणु
		dprपूर्णांकk("%s: [0x%02x] %04x %04x %04x %04x\n",
			ndev->name, j,
			ns83820_mii_पढ़ो_reg(dev, 1, 0 + j),
			ns83820_mii_पढ़ो_reg(dev, 1, 1 + j),
			ns83820_mii_पढ़ो_reg(dev, 1, 2 + j),
			ns83820_mii_पढ़ो_reg(dev, 1, 3 + j)
			);
	पूर्ण

	/* पढ़ो firmware version: memory addr is 0x8402 and 0x8403 */
	ns83820_mii_ग_लिखो_reg(dev, 1, 0x16, 0x000d);
	ns83820_mii_ग_लिखो_reg(dev, 1, 0x1e, 0x810e);
	a = ns83820_mii_पढ़ो_reg(dev, 1, 0x1d);

	ns83820_mii_ग_लिखो_reg(dev, 1, 0x16, 0x000d);
	ns83820_mii_ग_लिखो_reg(dev, 1, 0x1e, 0x810e);
	b = ns83820_mii_पढ़ो_reg(dev, 1, 0x1d);
	dprपूर्णांकk("version: 0x%04x 0x%04x\n", a, b);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= ns83820_खोलो,
	.nकरो_stop		= ns83820_stop,
	.nकरो_start_xmit		= ns83820_hard_start_xmit,
	.nकरो_get_stats		= ns83820_get_stats,
	.nकरो_set_rx_mode	= ns83820_set_multicast,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_tx_समयout		= ns83820_tx_समयout,
पूर्ण;

अटल पूर्णांक ns83820_init_one(काष्ठा pci_dev *pci_dev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net_device *ndev;
	काष्ठा ns83820 *dev;
	दीर्घ addr;
	पूर्णांक err;
	पूर्णांक using_dac = 0;

	/* See अगर we can set the dma mask early on; failure is fatal. */
	अगर (माप(dma_addr_t) == 8 &&
		!dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(64))) अणु
		using_dac = 1;
	पूर्ण अन्यथा अगर (!dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32))) अणु
		using_dac = 0;
	पूर्ण अन्यथा अणु
		dev_warn(&pci_dev->dev, "dma_set_mask failed!\n");
		वापस -ENODEV;
	पूर्ण

	ndev = alloc_etherdev(माप(काष्ठा ns83820));
	err = -ENOMEM;
	अगर (!ndev)
		जाओ out;

	dev = PRIV(ndev);
	dev->ndev = ndev;

	spin_lock_init(&dev->rx_info.lock);
	spin_lock_init(&dev->tx_lock);
	spin_lock_init(&dev->misc_lock);
	dev->pci_dev = pci_dev;

	SET_NETDEV_DEV(ndev, &pci_dev->dev);

	INIT_WORK(&dev->tq_refill, queue_refill);
	tasklet_setup(&dev->rx_tasklet, rx_action);

	err = pci_enable_device(pci_dev);
	अगर (err) अणु
		dev_info(&pci_dev->dev, "pci_enable_dev failed: %d\n", err);
		जाओ out_मुक्त;
	पूर्ण

	pci_set_master(pci_dev);
	addr = pci_resource_start(pci_dev, 1);
	dev->base = ioremap(addr, PAGE_SIZE);
	dev->tx_descs = dma_alloc_coherent(&pci_dev->dev,
					   4 * DESC_SIZE * NR_TX_DESC,
					   &dev->tx_phy_descs, GFP_KERNEL);
	dev->rx_info.descs = dma_alloc_coherent(&pci_dev->dev,
						4 * DESC_SIZE * NR_RX_DESC,
						&dev->rx_info.phy_descs, GFP_KERNEL);
	err = -ENOMEM;
	अगर (!dev->base || !dev->tx_descs || !dev->rx_info.descs)
		जाओ out_disable;

	dprपूर्णांकk("%p: %08lx  %p: %08lx\n",
		dev->tx_descs, (दीर्घ)dev->tx_phy_descs,
		dev->rx_info.descs, (दीर्घ)dev->rx_info.phy_descs);

	ns83820_disable_पूर्णांकerrupts(dev);

	dev->IMR_cache = 0;

	err = request_irq(pci_dev->irq, ns83820_irq, IRQF_SHARED,
			  DRV_NAME, ndev);
	अगर (err) अणु
		dev_info(&pci_dev->dev, "unable to register irq %d, err %d\n",
			pci_dev->irq, err);
		जाओ out_disable;
	पूर्ण

	/*
	 * FIXME: we are holding rtnl_lock() over obscenely दीर्घ area only
	 * because some of the setup code uses dev->name.  It's Wrong(पंचांग) -
	 * we should be using driver-specअगरic names क्रम all that stuff.
	 * For now that will करो, but we really need to come back and समाप्त
	 * most of the dev_alloc_name() users later.
	 */
	rtnl_lock();
	err = dev_alloc_name(ndev, ndev->name);
	अगर (err < 0) अणु
		dev_info(&pci_dev->dev, "unable to get netdev name: %d\n", err);
		जाओ out_मुक्त_irq;
	पूर्ण

	prपूर्णांकk("%s: ns83820.c: 0x22c: %08x, subsystem: %04x:%04x\n",
		ndev->name, le32_to_cpu(पढ़ोl(dev->base + 0x22c)),
		pci_dev->subप्रणाली_venकरोr, pci_dev->subप्रणाली_device);

	ndev->netdev_ops = &netdev_ops;
	ndev->ethtool_ops = &ops;
	ndev->watchकरोg_समयo = 5 * HZ;
	pci_set_drvdata(pci_dev, ndev);

	ns83820_करो_reset(dev, CR_RST);

	/* Must reset the ram bist beक्रमe running it */
	ग_लिखोl(PTSCR_RBIST_RST, dev->base + PTSCR);
	ns83820_run_bist(ndev, "sram bist",   PTSCR_RBIST_EN,
			 PTSCR_RBIST_DONE, PTSCR_RBIST_FAIL);
	ns83820_run_bist(ndev, "eeprom bist", PTSCR_EEBIST_EN, 0,
			 PTSCR_EEBIST_FAIL);
	ns83820_run_bist(ndev, "eeprom load", PTSCR_EELOAD_EN, 0, 0);

	/* I love config रेजिस्टरs */
	dev->CFG_cache = पढ़ोl(dev->base + CFG);

	अगर ((dev->CFG_cache & CFG_PCI64_DET)) अणु
		prपूर्णांकk(KERN_INFO "%s: detected 64 bit PCI data bus.\n",
			ndev->name);
		/*dev->CFG_cache |= CFG_DATA64_EN;*/
		अगर (!(dev->CFG_cache & CFG_DATA64_EN))
			prपूर्णांकk(KERN_INFO "%s: EEPROM did not enable 64 bit bus.  Disabled.\n",
				ndev->name);
	पूर्ण अन्यथा
		dev->CFG_cache &= ~(CFG_DATA64_EN);

	dev->CFG_cache &= (CFG_TBI_EN  | CFG_MRM_DIS   | CFG_MWI_DIS |
			   CFG_T64ADDR | CFG_DATA64_EN | CFG_EXT_125 |
			   CFG_M64ADDR);
	dev->CFG_cache |= CFG_PINT_DUPSTS | CFG_PINT_LNKSTS | CFG_PINT_SPDSTS |
			  CFG_EXTSTS_EN   | CFG_EXD         | CFG_PESEL;
	dev->CFG_cache |= CFG_REQALG;
	dev->CFG_cache |= CFG_POW;
	dev->CFG_cache |= CFG_TMRTEST;

	/* When compiled with 64 bit addressing, we must always enable
	 * the 64 bit descriptor क्रमmat.
	 */
	अगर (माप(dma_addr_t) == 8)
		dev->CFG_cache |= CFG_M64ADDR;
	अगर (using_dac)
		dev->CFG_cache |= CFG_T64ADDR;

	/* Big endian mode करोes not seem to करो what the करोcs suggest */
	dev->CFG_cache &= ~CFG_BEM;

	/* setup optical transceiver अगर we have one */
	अगर (dev->CFG_cache & CFG_TBI_EN) अणु
		prपूर्णांकk(KERN_INFO "%s: enabling optical transceiver\n",
			ndev->name);
		ग_लिखोl(पढ़ोl(dev->base + GPIOR) | 0x3e8, dev->base + GPIOR);

		/* setup स्वतः negotiation feature advertisement */
		ग_लिखोl(पढ़ोl(dev->base + TANAR)
		       | TANAR_HALF_DUP | TANAR_FULL_DUP,
		       dev->base + TANAR);

		/* start स्वतः negotiation */
		ग_लिखोl(TBICR_MR_AN_ENABLE | TBICR_MR_RESTART_AN,
		       dev->base + TBICR);
		ग_लिखोl(TBICR_MR_AN_ENABLE, dev->base + TBICR);
		dev->linkstate = LINK_AUTONEGOTIATE;

		dev->CFG_cache |= CFG_MODE_1000;
	पूर्ण

	ग_लिखोl(dev->CFG_cache, dev->base + CFG);
	dprपूर्णांकk("CFG: %08x\n", dev->CFG_cache);

	अगर (reset_phy) अणु
		prपूर्णांकk(KERN_INFO "%s: resetting phy\n", ndev->name);
		ग_लिखोl(dev->CFG_cache | CFG_PHY_RST, dev->base + CFG);
		msleep(10);
		ग_लिखोl(dev->CFG_cache, dev->base + CFG);
	पूर्ण

#अगर 0	/* Huh?  This sets the PCI latency रेजिस्टर.  Should be करोne via
	 * the PCI layer.  FIXME.
	 */
	अगर (पढ़ोl(dev->base + SRR))
		ग_लिखोl(पढ़ोl(dev->base+0x20c) | 0xfe00, dev->base + 0x20c);
#पूर्ण_अगर

	/* Note!  The DMA burst size पूर्णांकeracts with packet
	 * transmission, such that the largest packet that
	 * can be transmitted is 8192 - FLTH - burst size.
	 * If only the transmit fअगरo was larger...
	 */
	/* Ramit : 1024 DMA is not a good idea, it ends up banging
	 * some DELL and COMPAQ SMP प्रणालीs */
	ग_लिखोl(TXCFG_CSI | TXCFG_HBI | TXCFG_ATP | TXCFG_MXDMA512
		| ((1600 / 32) * 0x100),
		dev->base + TXCFG);

	/* Flush the पूर्णांकerrupt holकरोff समयr */
	ग_लिखोl(0x000, dev->base + IHR);
	ग_लिखोl(0x100, dev->base + IHR);
	ग_लिखोl(0x000, dev->base + IHR);

	/* Set Rx to full duplex, करोn't accept runt, errored, दीर्घ or length
	 * range errored packets.  Use 512 byte DMA.
	 */
	/* Ramit : 1024 DMA is not a good idea, it ends up banging
	 * some DELL and COMPAQ SMP प्रणालीs
	 * Turn on ALP, only we are accpeting Jumbo Packets */
	ग_लिखोl(RXCFG_AEP | RXCFG_ARP | RXCFG_AIRL | RXCFG_RX_FD
		| RXCFG_STRIPCRC
		//| RXCFG_ALP
		| (RXCFG_MXDMA512) | 0, dev->base + RXCFG);

	/* Disable priority queueing */
	ग_लिखोl(0, dev->base + PQCR);

	/* Enable IP checksum validation and detetion of VLAN headers.
	 * Note: करो not set the reject options as at least the 0x102
	 * revision of the chip करोes not properly accept IP fragments
	 * at least क्रम UDP.
	 */
	/* Ramit : Be sure to turn on RXCFG_ARP अगर VLAN's are enabled, since
	 * the MAC it calculates the packetsize AFTER stripping the VLAN
	 * header, and अगर a VLAN Tagged packet of 64 bytes is received (like
	 * a ping with a VLAN header) then the card, strips the 4 byte VLAN
	 * tag and then checks the packet size, so अगर RXCFG_ARP is not enabled,
	 * it discrards it!.  These guys......
	 * also turn on tag stripping अगर hardware acceleration is enabled
	 */
#अगर_घोषित NS83820_VLAN_ACCEL_SUPPORT
#घोषणा VRCR_INIT_VALUE (VRCR_IPEN|VRCR_VTDEN|VRCR_VTREN)
#अन्यथा
#घोषणा VRCR_INIT_VALUE (VRCR_IPEN|VRCR_VTDEN)
#पूर्ण_अगर
	ग_लिखोl(VRCR_INIT_VALUE, dev->base + VRCR);

	/* Enable per-packet TCP/UDP/IP checksumming
	 * and per packet vlan tag insertion अगर
	 * vlan hardware acceleration is enabled
	 */
#अगर_घोषित NS83820_VLAN_ACCEL_SUPPORT
#घोषणा VTCR_INIT_VALUE (VTCR_PPCHK|VTCR_VPPTI)
#अन्यथा
#घोषणा VTCR_INIT_VALUE VTCR_PPCHK
#पूर्ण_अगर
	ग_लिखोl(VTCR_INIT_VALUE, dev->base + VTCR);

	/* Ramit : Enable async and sync छोड़ो frames */
	/* ग_लिखोl(0, dev->base + PCR); */
	ग_लिखोl((PCR_PS_MCAST | PCR_PS_DA | PCR_PSEN | PCR_FFLO_4K |
		PCR_FFHI_8K | PCR_STLO_4 | PCR_STHI_8 | PCR_PAUSE_CNT),
		dev->base + PCR);

	/* Disable Wake On Lan */
	ग_लिखोl(0, dev->base + WCSR);

	ns83820_geपंचांगac(dev, ndev->dev_addr);

	/* Yes, we support dumb IP checksum on transmit */
	ndev->features |= NETIF_F_SG;
	ndev->features |= NETIF_F_IP_CSUM;

	ndev->min_mtu = 0;

#अगर_घोषित NS83820_VLAN_ACCEL_SUPPORT
	/* We also support hardware vlan acceleration */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
#पूर्ण_अगर

	अगर (using_dac) अणु
		prपूर्णांकk(KERN_INFO "%s: using 64 bit addressing.\n",
			ndev->name);
		ndev->features |= NETIF_F_HIGHDMA;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: ns83820 v" VERSION ": DP83820 v%u.%u: %pM io=0x%08lx irq=%d f=%s\n",
		ndev->name,
		(अचिन्हित)पढ़ोl(dev->base + SRR) >> 8,
		(अचिन्हित)पढ़ोl(dev->base + SRR) & 0xff,
		ndev->dev_addr, addr, pci_dev->irq,
		(ndev->features & NETIF_F_HIGHDMA) ? "h,sg" : "sg"
		);

#अगर_घोषित PHY_CODE_IS_FINISHED
	ns83820_probe_phy(ndev);
#पूर्ण_अगर

	err = रेजिस्टर_netdevice(ndev);
	अगर (err) अणु
		prपूर्णांकk(KERN_INFO "ns83820: unable to register netdev: %d\n", err);
		जाओ out_cleanup;
	पूर्ण
	rtnl_unlock();

	वापस 0;

out_cleanup:
	ns83820_disable_पूर्णांकerrupts(dev); /* paranoia */
out_मुक्त_irq:
	rtnl_unlock();
	मुक्त_irq(pci_dev->irq, ndev);
out_disable:
	अगर (dev->base)
		iounmap(dev->base);
	dma_मुक्त_coherent(&pci_dev->dev, 4 * DESC_SIZE * NR_TX_DESC,
			  dev->tx_descs, dev->tx_phy_descs);
	dma_मुक्त_coherent(&pci_dev->dev, 4 * DESC_SIZE * NR_RX_DESC,
			  dev->rx_info.descs, dev->rx_info.phy_descs);
	pci_disable_device(pci_dev);
out_मुक्त:
	मुक्त_netdev(ndev);
out:
	वापस err;
पूर्ण

अटल व्योम ns83820_हटाओ_one(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा net_device *ndev = pci_get_drvdata(pci_dev);
	काष्ठा ns83820 *dev = PRIV(ndev); /* ok even अगर शून्य */

	अगर (!ndev)			/* paranoia */
		वापस;

	ns83820_disable_पूर्णांकerrupts(dev); /* paranoia */

	unरेजिस्टर_netdev(ndev);
	मुक्त_irq(dev->pci_dev->irq, ndev);
	iounmap(dev->base);
	dma_मुक्त_coherent(&dev->pci_dev->dev, 4 * DESC_SIZE * NR_TX_DESC,
			  dev->tx_descs, dev->tx_phy_descs);
	dma_मुक्त_coherent(&dev->pci_dev->dev, 4 * DESC_SIZE * NR_RX_DESC,
			  dev->rx_info.descs, dev->rx_info.phy_descs);
	pci_disable_device(dev->pci_dev);
	मुक्त_netdev(ndev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ns83820_pci_tbl[] = अणु
	अणु 0x100b, 0x0022, PCI_ANY_ID, PCI_ANY_ID, 0, .driver_data = 0, पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver driver = अणु
	.name		= "ns83820",
	.id_table	= ns83820_pci_tbl,
	.probe		= ns83820_init_one,
	.हटाओ		= ns83820_हटाओ_one,
#अगर 0	/* FIXME: implement */
	.suspend	= ,
	.resume		= ,
#पूर्ण_अगर
पूर्ण;


अटल पूर्णांक __init ns83820_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "ns83820.c: National Semiconductor DP83820 10/100/1000 driver.\n");
	वापस pci_रेजिस्टर_driver(&driver);
पूर्ण

अटल व्योम __निकास ns83820_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&driver);
पूर्ण

MODULE_AUTHOR("Benjamin LaHaise <bcrl@kvack.org>");
MODULE_DESCRIPTION("National Semiconductor DP83820 10/100/1000 driver");
MODULE_LICENSE("GPL");

MODULE_DEVICE_TABLE(pci, ns83820_pci_tbl);

module_param(lnksts, पूर्णांक, 0);
MODULE_PARM_DESC(lnksts, "Polarity of LNKSTS bit");

module_param(ihr, पूर्णांक, 0);
MODULE_PARM_DESC(ihr, "Time in 100 us increments to delay interrupts (range 0-127)");

module_param(reset_phy, पूर्णांक, 0);
MODULE_PARM_DESC(reset_phy, "Set to 1 to reset the PHY on startup");

module_init(ns83820_init);
module_निकास(ns83820_निकास);
