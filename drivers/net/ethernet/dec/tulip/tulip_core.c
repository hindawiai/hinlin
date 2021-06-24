<शैली गुरु>
/*	tulip_core.c: A DEC 21x4x-family ethernet driver क्रम Linux.

	Copyright 2000,2001  The Linux Kernel Team
	Written/copyright 1994-2001 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	Please submit bugs to http://bugzilla.kernel.org/ .
*/

#घोषणा pr_fmt(fmt) "tulip: " fmt

#घोषणा DRV_NAME	"tulip"

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश "tulip.h"
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/uaccess.h>

#अगर_घोषित CONFIG_SPARC
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

/* A few user-configurable values. */

/* Maximum events (Rx packets, etc.) to handle at each पूर्णांकerrupt. */
अटल अचिन्हित पूर्णांक max_पूर्णांकerrupt_work = 25;

#घोषणा MAX_UNITS 8
/* Used to pass the full-duplex flag, etc. */
अटल पूर्णांक full_duplex[MAX_UNITS];
अटल पूर्णांक options[MAX_UNITS];
अटल पूर्णांक mtu[MAX_UNITS];			/* Jumbo MTU क्रम पूर्णांकerfaces. */

/*  The possible media types that can be set in options[] are: */
स्थिर अक्षर * स्थिर medianame[32] = अणु
	"10baseT", "10base2", "AUI", "100baseTx",
	"10baseT-FDX", "100baseTx-FDX", "100baseT4", "100baseFx",
	"100baseFx-FDX", "MII 10baseT", "MII 10baseT-FDX", "MII",
	"10baseT(forced)", "MII 100baseTx", "MII 100baseTx-FDX", "MII 100baseT4",
	"MII 100baseFx-HDX", "MII 100baseFx-FDX", "Home-PNA 1Mbps", "Invalid-19",
	"","","","", "","","","",  "","","","Transceiver reset",
पूर्ण;

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-buffer Rx काष्ठाure. */
#अगर defined(__alpha__) || defined(__arm__) || defined(__hppa__) || \
	defined(CONFIG_SPARC) || defined(__ia64__) || \
	defined(__sh__) || defined(__mips__)
अटल पूर्णांक rx_copyअवरोध = 1518;
#अन्यथा
अटल पूर्णांक rx_copyअवरोध = 100;
#पूर्ण_अगर

/*
  Set the bus perक्रमmance रेजिस्टर.
	Typical: Set 16 दीर्घword cache alignment, no burst limit.
	Cache alignment bits 15:14	     Burst length 13:8
		0000	No alignment  0x00000000 unlimited		0800 8 दीर्घwords
		4000	8  दीर्घwords		0100 1 दीर्घword		1000 16 दीर्घwords
		8000	16 दीर्घwords		0200 2 दीर्घwords	2000 32 दीर्घwords
		C000	32  दीर्घwords		0400 4 दीर्घwords
	Warning: many older 486 प्रणालीs are broken and require setting 0x00A04800
	   8 दीर्घword cache alignment, 8 दीर्घword burst.
	ToDo: Non-Intel setting could be better.
*/

#अगर defined(__alpha__) || defined(__ia64__)
अटल पूर्णांक csr0 = 0x01A00000 | 0xE000;
#या_अगर defined(__i386__) || defined(__घातerpc__) || defined(__x86_64__)
अटल पूर्णांक csr0 = 0x01A00000 | 0x8000;
#या_अगर defined(CONFIG_SPARC) || defined(__hppa__)
/* The UltraSparc PCI controllers will disconnect at every 64-byte
 * crossing anyways so it makes no sense to tell Tulip to burst
 * any more than that.
 */
अटल पूर्णांक csr0 = 0x01A00000 | 0x9000;
#या_अगर defined(__arm__) || defined(__sh__)
अटल पूर्णांक csr0 = 0x01A00000 | 0x4800;
#या_अगर defined(__mips__)
अटल पूर्णांक csr0 = 0x00200000 | 0x4000;
#अन्यथा
अटल पूर्णांक csr0;
#पूर्ण_अगर

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (4*HZ)


MODULE_AUTHOR("The Linux Kernel Team");
MODULE_DESCRIPTION("Digital 21*4* Tulip ethernet driver");
MODULE_LICENSE("GPL");
module_param(tulip_debug, पूर्णांक, 0);
module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param(csr0, पूर्णांक, 0);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);

#अगर_घोषित TULIP_DEBUG
पूर्णांक tulip_debug = TULIP_DEBUG;
#अन्यथा
पूर्णांक tulip_debug = 1;
#पूर्ण_अगर

अटल व्योम tulip_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tulip_निजी *tp = from_समयr(tp, t, समयr);
	काष्ठा net_device *dev = tp->dev;

	अगर (netअगर_running(dev))
		schedule_work(&tp->media_work);
पूर्ण

/*
 * This table use during operation क्रम capabilities and media समयr.
 *
 * It is indexed via the values in 'enum chips'
 */

स्थिर काष्ठा tulip_chip_table tulip_tbl[] = अणु
  अणु पूर्ण, /* placeholder क्रम array, slot unused currently */
  अणु पूर्ण, /* placeholder क्रम array, slot unused currently */

  /* DC21140 */
  अणु "Digital DS21140 Tulip", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM | HAS_PCI_MWI, tulip_समयr,
	tulip_media_task पूर्ण,

  /* DC21142, DC21143 */
  अणु "Digital DS21142/43 Tulip", 128, 0x0801fbff,
	HAS_MII | HAS_MEDIA_TABLE | ALWAYS_CHECK_MII | HAS_ACPI | HAS_NWAY
	| HAS_INTR_MITIGATION | HAS_PCI_MWI, tulip_समयr, t21142_media_task पूर्ण,

  /* LC82C168 */
  अणु "Lite-On 82c168 PNIC", 256, 0x0001fbef,
	HAS_MII | HAS_PNICNWAY, pnic_समयr, पूर्ण,

  /* MX98713 */
  अणु "Macronix 98713 PMAC", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM, mxic_समयr, पूर्ण,

  /* MX98715 */
  अणु "Macronix 98715 PMAC", 256, 0x0001ebef,
	HAS_MEDIA_TABLE, mxic_समयr, पूर्ण,

  /* MX98725 */
  अणु "Macronix 98725 PMAC", 256, 0x0001ebef,
	HAS_MEDIA_TABLE, mxic_समयr, पूर्ण,

  /* AX88140 */
  अणु "ASIX AX88140", 128, 0x0001fbff,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM | MC_HASH_ONLY
	| IS_ASIX, tulip_समयr, tulip_media_task पूर्ण,

  /* PNIC2 */
  अणु "Lite-On PNIC-II", 256, 0x0801fbff,
	HAS_MII | HAS_NWAY | HAS_8023X | HAS_PCI_MWI, pnic2_समयr, पूर्ण,

  /* COMET */
  अणु "ADMtek Comet", 256, 0x0001abef,
	HAS_MII | MC_HASH_ONLY | COMET_MAC_ADDR, comet_समयr, पूर्ण,

  /* COMPEX9881 */
  अणु "Compex 9881 PMAC", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM, mxic_समयr, पूर्ण,

  /* I21145 */
  अणु "Intel DS21145 Tulip", 128, 0x0801fbff,
	HAS_MII | HAS_MEDIA_TABLE | ALWAYS_CHECK_MII | HAS_ACPI
	| HAS_NWAY | HAS_PCI_MWI, tulip_समयr, tulip_media_task पूर्ण,

  /* DM910X */
#अगर_घोषित CONFIG_TULIP_DM910X
  अणु "Davicom DM9102/DM9102A", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM | HAS_ACPI,
	tulip_समयr, tulip_media_task पूर्ण,
#अन्यथा
  अणु शून्य पूर्ण,
#पूर्ण_अगर

  /* RS7112 */
  अणु "Conexant LANfinity", 256, 0x0001ebef,
	HAS_MII | HAS_ACPI, tulip_समयr, tulip_media_task पूर्ण,

पूर्ण;


अटल स्थिर काष्ठा pci_device_id tulip_pci_tbl[] = अणु
	अणु 0x1011, 0x0009, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DC21140 पूर्ण,
	अणु 0x1011, 0x0019, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DC21143 पूर्ण,
	अणु 0x11AD, 0x0002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, LC82C168 पूर्ण,
	अणु 0x10d9, 0x0512, PCI_ANY_ID, PCI_ANY_ID, 0, 0, MX98713 पूर्ण,
	अणु 0x10d9, 0x0531, PCI_ANY_ID, PCI_ANY_ID, 0, 0, MX98715 पूर्ण,
/*	अणु 0x10d9, 0x0531, PCI_ANY_ID, PCI_ANY_ID, 0, 0, MX98725 पूर्ण,*/
	अणु 0x125B, 0x1400, PCI_ANY_ID, PCI_ANY_ID, 0, 0, AX88140 पूर्ण,
	अणु 0x11AD, 0xc115, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PNIC2 पूर्ण,
	अणु 0x1317, 0x0981, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1317, 0x0985, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1317, 0x1985, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1317, 0x9511, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x13D1, 0xAB02, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x13D1, 0xAB03, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x13D1, 0xAB08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x104A, 0x0981, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x104A, 0x2774, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1259, 0xa120, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x11F6, 0x9881, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMPEX9881 पूर्ण,
	अणु 0x8086, 0x0039, PCI_ANY_ID, PCI_ANY_ID, 0, 0, I21145 पूर्ण,
#अगर_घोषित CONFIG_TULIP_DM910X
	अणु 0x1282, 0x9100, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DM910X पूर्ण,
	अणु 0x1282, 0x9102, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DM910X पूर्ण,
#पूर्ण_अगर
	अणु 0x1113, 0x1216, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1113, 0x1217, PCI_ANY_ID, PCI_ANY_ID, 0, 0, MX98715 पूर्ण,
	अणु 0x1113, 0x9511, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1186, 0x1541, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1186, 0x1561, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1186, 0x1591, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x14f1, 0x1803, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CONEXANT पूर्ण,
	अणु 0x1626, 0x8410, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1737, 0xAB09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x1737, 0xAB08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x17B3, 0xAB08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु 0x10b7, 0x9300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण, /* 3Com 3CSOHO100B-TX */
	अणु 0x14ea, 0xab08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण, /* Planex FNW-3602-TX */
	अणु 0x1414, 0x0001, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण, /* Microsoft MN-120 */
	अणु 0x1414, 0x0002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET पूर्ण,
	अणु पूर्ण /* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, tulip_pci_tbl);


/* A full-duplex map क्रम media types. */
स्थिर अक्षर tulip_media_cap[32] =
अणु0,0,0,16,  3,19,16,24,  27,4,7,5, 0,20,23,20,  28,31,0,0, पूर्ण;

अटल व्योम tulip_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम tulip_init_ring(काष्ठा net_device *dev);
अटल व्योम tulip_मुक्त_ring(काष्ठा net_device *dev);
अटल netdev_tx_t tulip_start_xmit(काष्ठा sk_buff *skb,
					  काष्ठा net_device *dev);
अटल पूर्णांक tulip_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक tulip_बंद(काष्ठा net_device *dev);
अटल व्योम tulip_up(काष्ठा net_device *dev);
अटल व्योम tulip_करोwn(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *tulip_get_stats(काष्ठा net_device *dev);
अटल पूर्णांक निजी_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल व्योम tulip_set_wolopts(काष्ठा pci_dev *pdev, u32 wolopts);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम poll_tulip(काष्ठा net_device *dev);
#पूर्ण_अगर

अटल व्योम tulip_set_घातer_state (काष्ठा tulip_निजी *tp,
				   पूर्णांक sleep, पूर्णांक snooze)
अणु
	अगर (tp->flags & HAS_ACPI) अणु
		u32 पंचांगp, newपंचांगp;
		pci_पढ़ो_config_dword (tp->pdev, CFDD, &पंचांगp);
		newपंचांगp = पंचांगp & ~(CFDD_Sleep | CFDD_Snooze);
		अगर (sleep)
			newपंचांगp |= CFDD_Sleep;
		अन्यथा अगर (snooze)
			newपंचांगp |= CFDD_Snooze;
		अगर (पंचांगp != newपंचांगp)
			pci_ग_लिखो_config_dword (tp->pdev, CFDD, newपंचांगp);
	पूर्ण

पूर्ण


अटल व्योम tulip_up(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक next_tick = 3*HZ;
	u32 reg;
	पूर्णांक i;

#अगर_घोषित CONFIG_TULIP_NAPI
	napi_enable(&tp->napi);
#पूर्ण_अगर

	/* Wake the chip from sleep/snooze mode. */
	tulip_set_घातer_state (tp, 0, 0);

	/* Disable all WOL events */
	pci_enable_wake(tp->pdev, PCI_D3hot, 0);
	pci_enable_wake(tp->pdev, PCI_D3cold, 0);
	tulip_set_wolopts(tp->pdev, 0);

	/* On some chip revs we must set the MII/SYM port beक्रमe the reset!? */
	अगर (tp->mii_cnt  ||  (tp->mtable  &&  tp->mtable->has_mii))
		ioग_लिखो32(0x00040000, ioaddr + CSR6);

	/* Reset the chip, holding bit 0 set at least 50 PCI cycles. */
	ioग_लिखो32(0x00000001, ioaddr + CSR0);
	pci_पढ़ो_config_dword(tp->pdev, PCI_COMMAND, &reg);  /* flush ग_लिखो */
	udelay(100);

	/* Deनिश्चित reset.
	   Wait the specअगरied 50 PCI cycles after a reset by initializing
	   Tx and Rx queues and the address filter list. */
	ioग_लिखो32(tp->csr0, ioaddr + CSR0);
	pci_पढ़ो_config_dword(tp->pdev, PCI_COMMAND, &reg);  /* flush ग_लिखो */
	udelay(100);

	अगर (tulip_debug > 1)
		netdev_dbg(dev, "tulip_up(), irq==%d\n", tp->pdev->irq);

	ioग_लिखो32(tp->rx_ring_dma, ioaddr + CSR3);
	ioग_लिखो32(tp->tx_ring_dma, ioaddr + CSR4);
	tp->cur_rx = tp->cur_tx = 0;
	tp->dirty_rx = tp->dirty_tx = 0;

	अगर (tp->flags & MC_HASH_ONLY) अणु
		u32 addr_low = get_unaligned_le32(dev->dev_addr);
		u32 addr_high = get_unaligned_le16(dev->dev_addr + 4);
		अगर (tp->chip_id == AX88140) अणु
			ioग_लिखो32(0, ioaddr + CSR13);
			ioग_लिखो32(addr_low,  ioaddr + CSR14);
			ioग_लिखो32(1, ioaddr + CSR13);
			ioग_लिखो32(addr_high, ioaddr + CSR14);
		पूर्ण अन्यथा अगर (tp->flags & COMET_MAC_ADDR) अणु
			ioग_लिखो32(addr_low,  ioaddr + 0xA4);
			ioग_लिखो32(addr_high, ioaddr + 0xA8);
			ioग_लिखो32(0, ioaddr + CSR27);
			ioग_लिखो32(0, ioaddr + CSR28);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* This is set_rx_mode(), but without starting the transmitter. */
		u16 *eaddrs = (u16 *)dev->dev_addr;
		u16 *setup_frm = &tp->setup_frame[15*6];
		dma_addr_t mapping;

		/* 21140 bug: you must add the broadcast address. */
		स_रखो(tp->setup_frame, 0xff, माप(tp->setup_frame));
		/* Fill the final entry of the table with our physical address. */
		*setup_frm++ = eaddrs[0]; *setup_frm++ = eaddrs[0];
		*setup_frm++ = eaddrs[1]; *setup_frm++ = eaddrs[1];
		*setup_frm++ = eaddrs[2]; *setup_frm++ = eaddrs[2];

		mapping = dma_map_single(&tp->pdev->dev, tp->setup_frame,
					 माप(tp->setup_frame),
					 DMA_TO_DEVICE);
		tp->tx_buffers[tp->cur_tx].skb = शून्य;
		tp->tx_buffers[tp->cur_tx].mapping = mapping;

		/* Put the setup frame on the Tx list. */
		tp->tx_ring[tp->cur_tx].length = cpu_to_le32(0x08000000 | 192);
		tp->tx_ring[tp->cur_tx].buffer1 = cpu_to_le32(mapping);
		tp->tx_ring[tp->cur_tx].status = cpu_to_le32(DescOwned);

		tp->cur_tx++;
	पूर्ण

	tp->saved_अगर_port = dev->अगर_port;
	अगर (dev->अगर_port == 0)
		dev->अगर_port = tp->शेष_port;

	/* Allow selecting a शेष media. */
	i = 0;
	अगर (tp->mtable == शून्य)
		जाओ media_picked;
	अगर (dev->अगर_port) अणु
		पूर्णांक looking_क्रम = tulip_media_cap[dev->अगर_port] & MediaIsMII ? 11 :
			(dev->अगर_port == 12 ? 0 : dev->अगर_port);
		क्रम (i = 0; i < tp->mtable->leafcount; i++)
			अगर (tp->mtable->mleaf[i].media == looking_क्रम) अणु
				dev_info(&dev->dev,
					 "Using user-specified media %s\n",
					 medianame[dev->अगर_port]);
				जाओ media_picked;
			पूर्ण
	पूर्ण
	अगर ((tp->mtable->शेषmedia & 0x0800) == 0) अणु
		पूर्णांक looking_क्रम = tp->mtable->शेषmedia & MEDIA_MASK;
		क्रम (i = 0; i < tp->mtable->leafcount; i++)
			अगर (tp->mtable->mleaf[i].media == looking_क्रम) अणु
				dev_info(&dev->dev,
					 "Using EEPROM-set media %s\n",
					 medianame[looking_क्रम]);
				जाओ media_picked;
			पूर्ण
	पूर्ण
	/* Start sensing first non-full-duplex media. */
	क्रम (i = tp->mtable->leafcount - 1;
		 (tulip_media_cap[tp->mtable->mleaf[i].media] & MediaAlwaysFD) && i > 0; i--)
		;
media_picked:

	tp->csr6 = 0;
	tp->cur_index = i;
	tp->nwayset = 0;

	अगर (dev->अगर_port) अणु
		अगर (tp->chip_id == DC21143  &&
		    (tulip_media_cap[dev->अगर_port] & MediaIsMII)) अणु
			/* We must reset the media CSRs when we क्रमce-select MII mode. */
			ioग_लिखो32(0x0000, ioaddr + CSR13);
			ioग_लिखो32(0x0000, ioaddr + CSR14);
			ioग_लिखो32(0x0008, ioaddr + CSR15);
		पूर्ण
		tulip_select_media(dev, 1);
	पूर्ण अन्यथा अगर (tp->chip_id == DC21142) अणु
		अगर (tp->mii_cnt) अणु
			tulip_select_media(dev, 1);
			अगर (tulip_debug > 1)
				dev_info(&dev->dev,
					 "Using MII transceiver %d, status %04x\n",
					 tp->phys[0],
					 tulip_mdio_पढ़ो(dev, tp->phys[0], 1));
			ioग_लिखो32(csr6_mask_deख_स्थितिe, ioaddr + CSR6);
			tp->csr6 = csr6_mask_hdcap;
			dev->अगर_port = 11;
			ioग_लिखो32(0x0000, ioaddr + CSR13);
			ioग_लिखो32(0x0000, ioaddr + CSR14);
		पूर्ण अन्यथा
			t21142_start_nway(dev);
	पूर्ण अन्यथा अगर (tp->chip_id == PNIC2) अणु
	        /* क्रम initial startup advertise 10/100 Full and Half */
	        tp->sym_advertise = 0x01E0;
                /* enable स्वतःnegotiate end पूर्णांकerrupt */
	        ioग_लिखो32(ioपढ़ो32(ioaddr+CSR5)| 0x00008010, ioaddr + CSR5);
	        ioग_लिखो32(ioपढ़ो32(ioaddr+CSR7)| 0x00008010, ioaddr + CSR7);
		pnic2_start_nway(dev);
	पूर्ण अन्यथा अगर (tp->chip_id == LC82C168  &&  ! tp->medialock) अणु
		अगर (tp->mii_cnt) अणु
			dev->अगर_port = 11;
			tp->csr6 = 0x814C0000 | (tp->full_duplex ? 0x0200 : 0);
			ioग_लिखो32(0x0001, ioaddr + CSR15);
		पूर्ण अन्यथा अगर (ioपढ़ो32(ioaddr + CSR5) & TPLnkPass)
			pnic_करो_nway(dev);
		अन्यथा अणु
			/* Start with 10mbps to करो स्वतःnegotiation. */
			ioग_लिखो32(0x32, ioaddr + CSR12);
			tp->csr6 = 0x00420000;
			ioग_लिखो32(0x0001B078, ioaddr + 0xB8);
			ioग_लिखो32(0x0201B078, ioaddr + 0xB8);
			next_tick = 1*HZ;
		पूर्ण
	पूर्ण अन्यथा अगर ((tp->chip_id == MX98713 || tp->chip_id == COMPEX9881) &&
		   ! tp->medialock) अणु
		dev->अगर_port = 0;
		tp->csr6 = 0x01880000 | (tp->full_duplex ? 0x0200 : 0);
		ioग_लिखो32(0x0f370000 | ioपढ़ो16(ioaddr + 0x80), ioaddr + 0x80);
	पूर्ण अन्यथा अगर (tp->chip_id == MX98715 || tp->chip_id == MX98725) अणु
		/* Provided by BOLO, Macronix - 12/10/1998. */
		dev->अगर_port = 0;
		tp->csr6 = 0x01a80200;
		ioग_लिखो32(0x0f370000 | ioपढ़ो16(ioaddr + 0x80), ioaddr + 0x80);
		ioग_लिखो32(0x11000 | ioपढ़ो16(ioaddr + 0xa0), ioaddr + 0xa0);
	पूर्ण अन्यथा अगर (tp->chip_id == COMET || tp->chip_id == CONEXANT) अणु
		/* Enable स्वतःmatic Tx underrun recovery. */
		ioग_लिखो32(ioपढ़ो32(ioaddr + 0x88) | 1, ioaddr + 0x88);
		dev->अगर_port = tp->mii_cnt ? 11 : 0;
		tp->csr6 = 0x00040000;
	पूर्ण अन्यथा अगर (tp->chip_id == AX88140) अणु
		tp->csr6 = tp->mii_cnt ? 0x00040100 : 0x00000100;
	पूर्ण अन्यथा
		tulip_select_media(dev, 1);

	/* Start the chip's Tx to process setup frame. */
	tulip_stop_rxtx(tp);
	barrier();
	udelay(5);
	ioग_लिखो32(tp->csr6 | TxOn, ioaddr + CSR6);

	/* Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ioग_लिखो32(tulip_tbl[tp->chip_id].valid_पूर्णांकrs, ioaddr + CSR5);
	ioग_लिखो32(tulip_tbl[tp->chip_id].valid_पूर्णांकrs, ioaddr + CSR7);
	tulip_start_rxtx(tp);
	ioग_लिखो32(0, ioaddr + CSR2);		/* Rx poll demand */

	अगर (tulip_debug > 2) अणु
		netdev_dbg(dev, "Done tulip_up(), CSR0 %08x, CSR5 %08x CSR6 %08x\n",
			   ioपढ़ो32(ioaddr + CSR0),
			   ioपढ़ो32(ioaddr + CSR5),
			   ioपढ़ो32(ioaddr + CSR6));
	पूर्ण

	/* Set the समयr to चयन to check क्रम link beat and perhaps चयन
	   to an alternate media type. */
	tp->समयr.expires = RUN_AT(next_tick);
	add_समयr(&tp->समयr);
#अगर_घोषित CONFIG_TULIP_NAPI
	समयr_setup(&tp->oom_समयr, oom_समयr, 0);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
tulip_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक retval;

	tulip_init_ring (dev);

	retval = request_irq(tp->pdev->irq, tulip_पूर्णांकerrupt, IRQF_SHARED,
			     dev->name, dev);
	अगर (retval)
		जाओ मुक्त_ring;

	tulip_up (dev);

	netअगर_start_queue (dev);

	वापस 0;

मुक्त_ring:
	tulip_मुक्त_ring (dev);
	वापस retval;
पूर्ण


अटल व्योम tulip_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave (&tp->lock, flags);

	अगर (tulip_media_cap[dev->अगर_port] & MediaIsMII) अणु
		/* Do nothing -- the media monitor should handle this. */
		अगर (tulip_debug > 1)
			dev_warn(&dev->dev,
				 "Transmit timeout using MII device\n");
	पूर्ण अन्यथा अगर (tp->chip_id == DC21140 || tp->chip_id == DC21142 ||
		   tp->chip_id == MX98713 || tp->chip_id == COMPEX9881 ||
		   tp->chip_id == DM910X) अणु
		dev_warn(&dev->dev,
			 "21140 transmit timed out, status %08x, SIA %08x %08x %08x %08x, resetting...\n",
			 ioपढ़ो32(ioaddr + CSR5), ioपढ़ो32(ioaddr + CSR12),
			 ioपढ़ो32(ioaddr + CSR13), ioपढ़ो32(ioaddr + CSR14),
			 ioपढ़ो32(ioaddr + CSR15));
		tp->समयout_recovery = 1;
		schedule_work(&tp->media_work);
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (tp->chip_id == PNIC2) अणु
		dev_warn(&dev->dev,
			 "PNIC2 transmit timed out, status %08x, CSR6/7 %08x / %08x CSR12 %08x, resetting...\n",
			 (पूर्णांक)ioपढ़ो32(ioaddr + CSR5),
			 (पूर्णांक)ioपढ़ो32(ioaddr + CSR6),
			 (पूर्णांक)ioपढ़ो32(ioaddr + CSR7),
			 (पूर्णांक)ioपढ़ो32(ioaddr + CSR12));
	पूर्ण अन्यथा अणु
		dev_warn(&dev->dev,
			 "Transmit timed out, status %08x, CSR12 %08x, resetting...\n",
			 ioपढ़ो32(ioaddr + CSR5), ioपढ़ो32(ioaddr + CSR12));
		dev->अगर_port = 0;
	पूर्ण

#अगर defined(way_too_many_messages)
	अगर (tulip_debug > 3) अणु
		पूर्णांक i;
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			u8 *buf = (u8 *)(tp->rx_ring[i].buffer1);
			पूर्णांक j;
			prपूर्णांकk(KERN_DEBUG
			       "%2d: %08x %08x %08x %08x  %02x %02x %02x\n",
			       i,
			       (अचिन्हित पूर्णांक)tp->rx_ring[i].status,
			       (अचिन्हित पूर्णांक)tp->rx_ring[i].length,
			       (अचिन्हित पूर्णांक)tp->rx_ring[i].buffer1,
			       (अचिन्हित पूर्णांक)tp->rx_ring[i].buffer2,
			       buf[0], buf[1], buf[2]);
			क्रम (j = 0; ((j < 1600) && buf[j] != 0xee); j++)
				अगर (j < 100)
					pr_cont(" %02x", buf[j]);
			pr_cont(" j=%d\n", j);
		पूर्ण
		prपूर्णांकk(KERN_DEBUG "  Rx ring %p: ", tp->rx_ring);
		क्रम (i = 0; i < RX_RING_SIZE; i++)
			pr_cont(" %08x", (अचिन्हित पूर्णांक)tp->rx_ring[i].status);
		prपूर्णांकk(KERN_DEBUG "  Tx ring %p: ", tp->tx_ring);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			pr_cont(" %08x", (अचिन्हित पूर्णांक)tp->tx_ring[i].status);
		pr_cont("\n");
	पूर्ण
#पूर्ण_अगर

	tulip_tx_समयout_complete(tp, ioaddr);

out_unlock:
	spin_unlock_irqrestore (&tp->lock, flags);
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue (dev);
पूर्ण


/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल व्योम tulip_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक i;

	tp->susp_rx = 0;
	tp->tसमयr = 0;
	tp->nir = 0;

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		tp->rx_ring[i].status = 0x00000000;
		tp->rx_ring[i].length = cpu_to_le32(PKT_BUF_SZ);
		tp->rx_ring[i].buffer2 = cpu_to_le32(tp->rx_ring_dma + माप(काष्ठा tulip_rx_desc) * (i + 1));
		tp->rx_buffers[i].skb = शून्य;
		tp->rx_buffers[i].mapping = 0;
	पूर्ण
	/* Mark the last entry as wrapping the ring. */
	tp->rx_ring[i-1].length = cpu_to_le32(PKT_BUF_SZ | DESC_RING_WRAP);
	tp->rx_ring[i-1].buffer2 = cpu_to_le32(tp->rx_ring_dma);

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		dma_addr_t mapping;

		/* Note the receive buffer must be दीर्घword aligned.
		   netdev_alloc_skb() provides 16 byte alignment.  But करो *not*
		   use skb_reserve() to align the IP header! */
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, PKT_BUF_SZ);
		tp->rx_buffers[i].skb = skb;
		अगर (skb == शून्य)
			अवरोध;
		mapping = dma_map_single(&tp->pdev->dev, skb->data,
					 PKT_BUF_SZ, DMA_FROM_DEVICE);
		tp->rx_buffers[i].mapping = mapping;
		tp->rx_ring[i].status = cpu_to_le32(DescOwned);	/* Owned by Tulip chip */
		tp->rx_ring[i].buffer1 = cpu_to_le32(mapping);
	पूर्ण
	tp->dirty_rx = (अचिन्हित पूर्णांक)(i - RX_RING_SIZE);

	/* The Tx buffer descriptor is filled in as needed, but we
	   करो need to clear the ownership bit. */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		tp->tx_buffers[i].skb = शून्य;
		tp->tx_buffers[i].mapping = 0;
		tp->tx_ring[i].status = 0x00000000;
		tp->tx_ring[i].buffer2 = cpu_to_le32(tp->tx_ring_dma + माप(काष्ठा tulip_tx_desc) * (i + 1));
	पूर्ण
	tp->tx_ring[i-1].buffer2 = cpu_to_le32(tp->tx_ring_dma);
पूर्ण

अटल netdev_tx_t
tulip_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक entry;
	u32 flag;
	dma_addr_t mapping;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tp->lock, flags);

	/* Calculate the next Tx descriptor entry. */
	entry = tp->cur_tx % TX_RING_SIZE;

	tp->tx_buffers[entry].skb = skb;
	mapping = dma_map_single(&tp->pdev->dev, skb->data, skb->len,
				 DMA_TO_DEVICE);
	tp->tx_buffers[entry].mapping = mapping;
	tp->tx_ring[entry].buffer1 = cpu_to_le32(mapping);

	अगर (tp->cur_tx - tp->dirty_tx < TX_RING_SIZE/2) अणु/* Typical path */
		flag = 0x60000000; /* No पूर्णांकerrupt */
	पूर्ण अन्यथा अगर (tp->cur_tx - tp->dirty_tx == TX_RING_SIZE/2) अणु
		flag = 0xe0000000; /* Tx-करोne पूर्णांकr. */
	पूर्ण अन्यथा अगर (tp->cur_tx - tp->dirty_tx < TX_RING_SIZE - 2) अणु
		flag = 0x60000000; /* No Tx-करोne पूर्णांकr. */
	पूर्ण अन्यथा अणु		/* Leave room क्रम set_rx_mode() to fill entries. */
		flag = 0xe0000000; /* Tx-करोne पूर्णांकr. */
		netअगर_stop_queue(dev);
	पूर्ण
	अगर (entry == TX_RING_SIZE-1)
		flag = 0xe0000000 | DESC_RING_WRAP;

	tp->tx_ring[entry].length = cpu_to_le32(skb->len | flag);
	/* अगर we were using Transmit Automatic Polling, we would need a
	 * wmb() here. */
	tp->tx_ring[entry].status = cpu_to_le32(DescOwned);
	wmb();

	tp->cur_tx++;

	/* Trigger an immediate transmit demand. */
	ioग_लिखो32(0, tp->base_addr + CSR1);

	spin_unlock_irqrestore(&tp->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम tulip_clean_tx_ring(काष्ठा tulip_निजी *tp)
अणु
	अचिन्हित पूर्णांक dirty_tx;

	क्रम (dirty_tx = tp->dirty_tx ; tp->cur_tx - dirty_tx > 0;
		dirty_tx++) अणु
		पूर्णांक entry = dirty_tx % TX_RING_SIZE;
		पूर्णांक status = le32_to_cpu(tp->tx_ring[entry].status);

		अगर (status < 0) अणु
			tp->dev->stats.tx_errors++;	/* It wasn't Txed */
			tp->tx_ring[entry].status = 0;
		पूर्ण

		/* Check क्रम Tx filter setup frames. */
		अगर (tp->tx_buffers[entry].skb == शून्य) अणु
			/* test because dummy frames not mapped */
			अगर (tp->tx_buffers[entry].mapping)
				dma_unmap_single(&tp->pdev->dev,
						 tp->tx_buffers[entry].mapping,
						 माप(tp->setup_frame),
						 DMA_TO_DEVICE);
			जारी;
		पूर्ण

		dma_unmap_single(&tp->pdev->dev,
				 tp->tx_buffers[entry].mapping,
				 tp->tx_buffers[entry].skb->len,
				 DMA_TO_DEVICE);

		/* Free the original skb. */
		dev_kमुक्त_skb_irq(tp->tx_buffers[entry].skb);
		tp->tx_buffers[entry].skb = शून्य;
		tp->tx_buffers[entry].mapping = 0;
	पूर्ण
पूर्ण

अटल व्योम tulip_करोwn (काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	अचिन्हित दीर्घ flags;

	cancel_work_sync(&tp->media_work);

#अगर_घोषित CONFIG_TULIP_NAPI
	napi_disable(&tp->napi);
#पूर्ण_अगर

	del_समयr_sync (&tp->समयr);
#अगर_घोषित CONFIG_TULIP_NAPI
	del_समयr_sync (&tp->oom_समयr);
#पूर्ण_अगर
	spin_lock_irqsave (&tp->lock, flags);

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	ioग_लिखो32 (0x00000000, ioaddr + CSR7);

	/* Stop the Tx and Rx processes. */
	tulip_stop_rxtx(tp);

	/* prepare receive buffers */
	tulip_refill_rx(dev);

	/* release any unconsumed transmit buffers */
	tulip_clean_tx_ring(tp);

	अगर (ioपढ़ो32(ioaddr + CSR6) != 0xffffffff)
		dev->stats.rx_missed_errors += ioपढ़ो32(ioaddr + CSR8) & 0xffff;

	spin_unlock_irqrestore (&tp->lock, flags);

	समयr_setup(&tp->समयr, tulip_tbl[tp->chip_id].media_समयr, 0);

	dev->अगर_port = tp->saved_अगर_port;

	/* Leave the driver in snooze, not sleep, mode. */
	tulip_set_घातer_state (tp, 0, 1);
पूर्ण

अटल व्योम tulip_मुक्त_ring (काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक i;

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = tp->rx_buffers[i].skb;
		dma_addr_t mapping = tp->rx_buffers[i].mapping;

		tp->rx_buffers[i].skb = शून्य;
		tp->rx_buffers[i].mapping = 0;

		tp->rx_ring[i].status = 0;	/* Not owned by Tulip chip. */
		tp->rx_ring[i].length = 0;
		/* An invalid address. */
		tp->rx_ring[i].buffer1 = cpu_to_le32(0xBADF00D0);
		अगर (skb) अणु
			dma_unmap_single(&tp->pdev->dev, mapping, PKT_BUF_SZ,
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb (skb);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = tp->tx_buffers[i].skb;

		अगर (skb != शून्य) अणु
			dma_unmap_single(&tp->pdev->dev,
					 tp->tx_buffers[i].mapping, skb->len,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb (skb);
		पूर्ण
		tp->tx_buffers[i].skb = शून्य;
		tp->tx_buffers[i].mapping = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tulip_बंद (काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;

	netअगर_stop_queue (dev);

	tulip_करोwn (dev);

	अगर (tulip_debug > 1)
		netdev_dbg(dev, "Shutting down ethercard, status was %02x\n",
			   ioपढ़ो32 (ioaddr + CSR5));

	मुक्त_irq (tp->pdev->irq, dev);

	tulip_मुक्त_ring (dev);

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *tulip_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;

	अगर (netअगर_running(dev)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave (&tp->lock, flags);

		dev->stats.rx_missed_errors += ioपढ़ो32(ioaddr + CSR8) & 0xffff;

		spin_unlock_irqrestore(&tp->lock, flags);
	पूर्ण

	वापस &dev->stats;
पूर्ण


अटल व्योम tulip_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा tulip_निजी *np = netdev_priv(dev);
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(np->pdev), माप(info->bus_info));
पूर्ण


अटल पूर्णांक tulip_ethtool_set_wol(काष्ठा net_device *dev,
				 काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);

	अगर (wolinfo->wolopts & (~tp->wolinfo.supported))
		   वापस -EOPNOTSUPP;

	tp->wolinfo.wolopts = wolinfo->wolopts;
	device_set_wakeup_enable(&tp->pdev->dev, tp->wolinfo.wolopts);
	वापस 0;
पूर्ण

अटल व्योम tulip_ethtool_get_wol(काष्ठा net_device *dev,
				  काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);

	wolinfo->supported = tp->wolinfo.supported;
	wolinfo->wolopts = tp->wolinfo.wolopts;
	वापस;
पूर्ण


अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_drvinfo = tulip_get_drvinfo,
	.set_wol     = tulip_ethtool_set_wol,
	.get_wol     = tulip_ethtool_get_wol,
पूर्ण;

/* Provide ioctl() calls to examine the MII xcvr state. */
अटल पूर्णांक निजी_ioctl (काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	स्थिर अचिन्हित पूर्णांक phy_idx = 0;
	पूर्णांक phy = tp->phys[phy_idx] & 0x1f;
	अचिन्हित पूर्णांक regnum = data->reg_num;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		अगर (tp->mii_cnt)
			data->phy_id = phy;
		अन्यथा अगर (tp->flags & HAS_NWAY)
			data->phy_id = 32;
		अन्यथा अगर (tp->chip_id == COMET)
			data->phy_id = 1;
		अन्यथा
			वापस -ENODEV;
		fallthrough;

	हाल SIOCGMIIREG:		/* Read MII PHY रेजिस्टर. */
		अगर (data->phy_id == 32 && (tp->flags & HAS_NWAY)) अणु
			पूर्णांक csr12 = ioपढ़ो32 (ioaddr + CSR12);
			पूर्णांक csr14 = ioपढ़ो32 (ioaddr + CSR14);
			चयन (regnum) अणु
			हाल 0:
                                अगर (((csr14<<5) & 0x1000) ||
                                        (dev->अगर_port == 5 && tp->nwayset))
                                        data->val_out = 0x1000;
                                अन्यथा
                                        data->val_out = (tulip_media_cap[dev->अगर_port]&MediaIs100 ? 0x2000 : 0)
                                                | (tulip_media_cap[dev->अगर_port]&MediaIsFD ? 0x0100 : 0);
				अवरोध;
			हाल 1:
                                data->val_out =
					0x1848 +
					((csr12&0x7000) == 0x5000 ? 0x20 : 0) +
					((csr12&0x06) == 6 ? 0 : 4);
                                data->val_out |= 0x6048;
				अवरोध;
			हाल 4:
                                /* Advertised value, bogus 10baseTx-FD value from CSR6. */
                                data->val_out =
					((ioपढ़ो32(ioaddr + CSR6) >> 3) & 0x0040) +
					((csr14 >> 1) & 0x20) + 1;
                                data->val_out |= ((csr14 >> 9) & 0x03C0);
				अवरोध;
			हाल 5: data->val_out = tp->lpar; अवरोध;
			शेष: data->val_out = 0; अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			data->val_out = tulip_mdio_पढ़ो (dev, data->phy_id & 0x1f, regnum);
		पूर्ण
		वापस 0;

	हाल SIOCSMIIREG:		/* Write MII PHY रेजिस्टर. */
		अगर (regnum & ~0x1f)
			वापस -EINVAL;
		अगर (data->phy_id == phy) अणु
			u16 value = data->val_in;
			चयन (regnum) अणु
			हाल 0:	/* Check क्रम स्वतःnegotiation on or reset. */
				tp->full_duplex_lock = (value & 0x9000) ? 0 : 1;
				अगर (tp->full_duplex_lock)
					tp->full_duplex = (value & 0x0100) ? 1 : 0;
				अवरोध;
			हाल 4:
				tp->advertising[phy_idx] =
				tp->mii_advertise = data->val_in;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (data->phy_id == 32 && (tp->flags & HAS_NWAY)) अणु
			u16 value = data->val_in;
			अगर (regnum == 0) अणु
			  अगर ((value & 0x1200) == 0x1200) अणु
			    अगर (tp->chip_id == PNIC2) अणु
                                   pnic2_start_nway (dev);
                            पूर्ण अन्यथा अणु
				   t21142_start_nway (dev);
                            पूर्ण
			  पूर्ण
			पूर्ण अन्यथा अगर (regnum == 4)
				tp->sym_advertise = value;
		पूर्ण अन्यथा अणु
			tulip_mdio_ग_लिखो (dev, data->phy_id & 0x1f, regnum, data->val_in);
		पूर्ण
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण


/* Set or clear the multicast filter क्रम this adaptor.
   Note that we only use exclusion around actually queueing the
   new frame, not around filling tp->setup_frame.  This is non-deterministic
   when re-entered but still correct. */

अटल व्योम build_setup_frame_hash(u16 *setup_frm, काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	u16 hash_table[32];
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;
	u16 *eaddrs;

	स_रखो(hash_table, 0, माप(hash_table));
	__set_bit_le(255, hash_table);			/* Broadcast entry */
	/* This should work on big-endian machines as well. */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		पूर्णांक index = ether_crc_le(ETH_ALEN, ha->addr) & 0x1ff;

		__set_bit_le(index, hash_table);
	पूर्ण
	क्रम (i = 0; i < 32; i++) अणु
		*setup_frm++ = hash_table[i];
		*setup_frm++ = hash_table[i];
	पूर्ण
	setup_frm = &tp->setup_frame[13*6];

	/* Fill the final entry with our physical address. */
	eaddrs = (u16 *)dev->dev_addr;
	*setup_frm++ = eaddrs[0]; *setup_frm++ = eaddrs[0];
	*setup_frm++ = eaddrs[1]; *setup_frm++ = eaddrs[1];
	*setup_frm++ = eaddrs[2]; *setup_frm++ = eaddrs[2];
पूर्ण

अटल व्योम build_setup_frame_perfect(u16 *setup_frm, काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	u16 *eaddrs;

	/* We have <= 14 addresses so we can use the wonderful
	   16 address perfect filtering of the Tulip. */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		eaddrs = (u16 *) ha->addr;
		*setup_frm++ = *eaddrs; *setup_frm++ = *eaddrs++;
		*setup_frm++ = *eaddrs; *setup_frm++ = *eaddrs++;
		*setup_frm++ = *eaddrs; *setup_frm++ = *eaddrs++;
	पूर्ण
	/* Fill the unused entries with the broadcast address. */
	स_रखो(setup_frm, 0xff, (15 - netdev_mc_count(dev)) * 12);
	setup_frm = &tp->setup_frame[15*6];

	/* Fill the final entry with our physical address. */
	eaddrs = (u16 *)dev->dev_addr;
	*setup_frm++ = eaddrs[0]; *setup_frm++ = eaddrs[0];
	*setup_frm++ = eaddrs[1]; *setup_frm++ = eaddrs[1];
	*setup_frm++ = eaddrs[2]; *setup_frm++ = eaddrs[2];
पूर्ण


अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक csr6;

	csr6 = ioपढ़ो32(ioaddr + CSR6) & ~0x00D5;

	tp->csr6 &= ~0x00D5;
	अगर (dev->flags & IFF_PROMISC) अणु			/* Set promiscuous. */
		tp->csr6 |= AcceptAllMulticast | AcceptAllPhys;
		csr6 |= AcceptAllMulticast | AcceptAllPhys;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > 1000) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to filter well -- accept all multicasts. */
		tp->csr6 |= AcceptAllMulticast;
		csr6 |= AcceptAllMulticast;
	पूर्ण अन्यथा	अगर (tp->flags & MC_HASH_ONLY) अणु
		/* Some work-alikes have only a 64-entry hash filter table. */
		/* Should verअगरy correctness on big-endian/__घातerpc__ */
		काष्ठा netdev_hw_addr *ha;
		अगर (netdev_mc_count(dev) > 64) अणु
			/* Arbitrary non-effective limit. */
			tp->csr6 |= AcceptAllMulticast;
			csr6 |= AcceptAllMulticast;
		पूर्ण अन्यथा अणु
			u32 mc_filter[2] = अणु0, 0पूर्ण;		 /* Multicast hash filter */
			पूर्णांक filterbit;
			netdev_क्रम_each_mc_addr(ha, dev) अणु
				अगर (tp->flags & COMET_MAC_ADDR)
					filterbit = ether_crc_le(ETH_ALEN,
								 ha->addr);
				अन्यथा
					filterbit = ether_crc(ETH_ALEN,
							      ha->addr) >> 26;
				filterbit &= 0x3f;
				mc_filter[filterbit >> 5] |= 1 << (filterbit & 31);
				अगर (tulip_debug > 2)
					dev_info(&dev->dev,
						 "Added filter for %pM  %08x bit %d\n",
						 ha->addr,
						 ether_crc(ETH_ALEN, ha->addr),
						 filterbit);
			पूर्ण
			अगर (mc_filter[0] == tp->mc_filter[0]  &&
				mc_filter[1] == tp->mc_filter[1])
				;				/* No change. */
			अन्यथा अगर (tp->flags & IS_ASIX) अणु
				ioग_लिखो32(2, ioaddr + CSR13);
				ioग_लिखो32(mc_filter[0], ioaddr + CSR14);
				ioग_लिखो32(3, ioaddr + CSR13);
				ioग_लिखो32(mc_filter[1], ioaddr + CSR14);
			पूर्ण अन्यथा अगर (tp->flags & COMET_MAC_ADDR) अणु
				ioग_लिखो32(mc_filter[0], ioaddr + CSR27);
				ioग_लिखो32(mc_filter[1], ioaddr + CSR28);
			पूर्ण
			tp->mc_filter[0] = mc_filter[0];
			tp->mc_filter[1] = mc_filter[1];
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		u32 tx_flags = 0x08000000 | 192;

		/* Note that only the low-address लघुword of setup_frame is valid!
		   The values are द्विगुनd क्रम big-endian architectures. */
		अगर (netdev_mc_count(dev) > 14) अणु
			/* Must use a multicast hash table. */
			build_setup_frame_hash(tp->setup_frame, dev);
			tx_flags = 0x08400000 | 192;
		पूर्ण अन्यथा अणु
			build_setup_frame_perfect(tp->setup_frame, dev);
		पूर्ण

		spin_lock_irqsave(&tp->lock, flags);

		अगर (tp->cur_tx - tp->dirty_tx > TX_RING_SIZE - 2) अणु
			/* Same setup recently queued, we need not add it. */
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक entry;
			पूर्णांक dummy = -1;

			/* Now add this frame to the Tx list. */

			entry = tp->cur_tx++ % TX_RING_SIZE;

			अगर (entry != 0) अणु
				/* Aव्योम a chip errata by prefixing a dummy entry. */
				tp->tx_buffers[entry].skb = शून्य;
				tp->tx_buffers[entry].mapping = 0;
				tp->tx_ring[entry].length =
					(entry == TX_RING_SIZE-1) ? cpu_to_le32(DESC_RING_WRAP) : 0;
				tp->tx_ring[entry].buffer1 = 0;
				/* Must set DescOwned later to aव्योम race with chip */
				dummy = entry;
				entry = tp->cur_tx++ % TX_RING_SIZE;

			पूर्ण

			tp->tx_buffers[entry].skb = शून्य;
			tp->tx_buffers[entry].mapping =
				dma_map_single(&tp->pdev->dev,
					       tp->setup_frame,
					       माप(tp->setup_frame),
					       DMA_TO_DEVICE);
			/* Put the setup frame on the Tx list. */
			अगर (entry == TX_RING_SIZE-1)
				tx_flags |= DESC_RING_WRAP;		/* Wrap ring. */
			tp->tx_ring[entry].length = cpu_to_le32(tx_flags);
			tp->tx_ring[entry].buffer1 =
				cpu_to_le32(tp->tx_buffers[entry].mapping);
			tp->tx_ring[entry].status = cpu_to_le32(DescOwned);
			अगर (dummy >= 0)
				tp->tx_ring[dummy].status = cpu_to_le32(DescOwned);
			अगर (tp->cur_tx - tp->dirty_tx >= TX_RING_SIZE - 2)
				netअगर_stop_queue(dev);

			/* Trigger an immediate transmit demand. */
			ioग_लिखो32(0, ioaddr + CSR1);
		पूर्ण

		spin_unlock_irqrestore(&tp->lock, flags);
	पूर्ण

	ioग_लिखो32(csr6, ioaddr + CSR6);
पूर्ण

#अगर_घोषित CONFIG_TULIP_MWI
अटल व्योम tulip_mwi_config(काष्ठा pci_dev *pdev, काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	u8 cache;
	u16 pci_command;
	u32 csr0;

	अगर (tulip_debug > 3)
		netdev_dbg(dev, "tulip_mwi_config()\n");

	tp->csr0 = csr0 = 0;

	/* अगर we have any cache line size at all, we can करो MRM and MWI */
	csr0 |= MRM | MWI;

	/* Enable MWI in the standard PCI command bit.
	 * Check क्रम the हाल where MWI is desired but not available
	 */
	pci_try_set_mwi(pdev);

	/* पढ़ो result from hardware (in हाल bit refused to enable) */
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &pci_command);
	अगर ((csr0 & MWI) && (!(pci_command & PCI_COMMAND_INVALIDATE)))
		csr0 &= ~MWI;

	/* अगर cache line size hardwired to zero, no MWI */
	pci_पढ़ो_config_byte(pdev, PCI_CACHE_LINE_SIZE, &cache);
	अगर ((csr0 & MWI) && (cache == 0)) अणु
		csr0 &= ~MWI;
		pci_clear_mwi(pdev);
	पूर्ण

	/* assign per-cacheline-size cache alignment and
	 * burst length values
	 */
	चयन (cache) अणु
	हाल 8:
		csr0 |= MRL | (1 << CALShअगरt) | (16 << BurstLenShअगरt);
		अवरोध;
	हाल 16:
		csr0 |= MRL | (2 << CALShअगरt) | (16 << BurstLenShअगरt);
		अवरोध;
	हाल 32:
		csr0 |= MRL | (3 << CALShअगरt) | (32 << BurstLenShअगरt);
		अवरोध;
	शेष:
		cache = 0;
		अवरोध;
	पूर्ण

	/* अगर we have a good cache line size, we by now have a good
	 * csr0, so save it and निकास
	 */
	अगर (cache)
		जाओ out;

	/* we करोn't have a good csr0 or cache line size, disable MWI */
	अगर (csr0 & MWI) अणु
		pci_clear_mwi(pdev);
		csr0 &= ~MWI;
	पूर्ण

	/* sane शेषs क्रम burst length and cache alignment
	 * originally from de4x5 driver
	 */
	csr0 |= (8 << BurstLenShअगरt) | (1 << CALShअगरt);

out:
	tp->csr0 = csr0;
	अगर (tulip_debug > 2)
		netdev_dbg(dev, "MWI config cacheline=%d, csr0=%08x\n",
			   cache, csr0);
पूर्ण
#पूर्ण_अगर

/*
 *	Chips that have the MRM/reserved bit quirk and the burst quirk. That
 *	is the DM910X and the on chip ULi devices
 */

अटल पूर्णांक tulip_uli_dm_quirk(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->venकरोr == 0x1282 && pdev->device == 0x9102)
		वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops tulip_netdev_ops = अणु
	.nकरो_खोलो		= tulip_खोलो,
	.nकरो_start_xmit		= tulip_start_xmit,
	.nकरो_tx_समयout		= tulip_tx_समयout,
	.nकरो_stop		= tulip_बंद,
	.nकरो_get_stats		= tulip_get_stats,
	.nकरो_करो_ioctl 		= निजी_ioctl,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	 = poll_tulip,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pci_device_id early_486_chipsets[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82424) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_496) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक tulip_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा tulip_निजी *tp;
	/* See note below on the multiport cards. */
	अटल अचिन्हित अक्षर last_phys_addr[ETH_ALEN] = अणु
		0x00, 'L', 'i', 'n', 'u', 'x'
	पूर्ण;
#अगर defined(__i386__) || defined(__x86_64__)	/* Patch up x86 BIOS bug. */
	अटल पूर्णांक last_irq;
#पूर्ण_अगर
	पूर्णांक i, irq;
	अचिन्हित लघु sum;
	अचिन्हित अक्षर *ee_data;
	काष्ठा net_device *dev;
	व्योम __iomem *ioaddr;
	अटल पूर्णांक board_idx = -1;
	पूर्णांक chip_idx = ent->driver_data;
	स्थिर अक्षर *chip_name = tulip_tbl[chip_idx].chip_name;
	अचिन्हित पूर्णांक eeprom_missing = 0;
	अचिन्हित पूर्णांक क्रमce_csr0 = 0;

	board_idx++;

	/*
	 *	Lan media wire a tulip chip to a wan पूर्णांकerface. Needs a very
	 *	dअगरferent driver (lmc driver)
	 */

        अगर (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_LMC) अणु
		pr_err("skipping LMC card\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_SBE &&
		   (pdev->subप्रणाली_device == PCI_SUBDEVICE_ID_SBE_T3E3 ||
		    pdev->subप्रणाली_device == PCI_SUBDEVICE_ID_SBE_2T3E3_P0 ||
		    pdev->subप्रणाली_device == PCI_SUBDEVICE_ID_SBE_2T3E3_P1)) अणु
		pr_err("skipping SBE T3E3 port\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 *	DM910x chips should be handled by the dmfe driver, except
	 *	on-board chips on SPARC प्रणालीs.  Also, early DM9100s need
	 *	software CRC which only the dmfe driver supports.
	 */

#अगर_घोषित CONFIG_TULIP_DM910X
	अगर (chip_idx == DM910X) अणु
		काष्ठा device_node *dp;

		अगर (pdev->venकरोr == 0x1282 && pdev->device == 0x9100 &&
		    pdev->revision < 0x30) अणु
			pr_info("skipping early DM9100 with Crc bug (use dmfe)\n");
			वापस -ENODEV;
		पूर्ण

		dp = pci_device_to_OF_node(pdev);
		अगर (!(dp && of_get_property(dp, "local-mac-address", शून्य))) अणु
			pr_info("skipping DM910x expansion card (use dmfe)\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 *	Looks क्रम early PCI chipsets where people report hangs
	 *	without the workarounds being on.
	 */

	/* 1. Intel Saturn. Switch to 8 दीर्घ words burst, 8 दीर्घ word cache
	      aligned.  Aries might need this too. The Saturn errata are not
	      pretty पढ़ोing but thankfully it's an old 486 chipset.

	   2. The dपढ़ोed SiS496 486 chipset. Same workaround as Intel
	      Saturn.
	*/

	अगर (pci_dev_present(early_486_chipsets)) अणु
		csr0 = MRL | MRM | (8 << BurstLenShअगरt) | (1 << CALShअगरt);
		क्रमce_csr0 = 1;
	पूर्ण

	/* bugfix: the ASIX must have a burst limit or horrible things happen. */
	अगर (chip_idx == AX88140) अणु
		अगर ((csr0 & 0x3f00) == 0)
			csr0 |= 0x2000;
	पूर्ण

	/* PNIC करोesn't have MWI/MRL/MRM... */
	अगर (chip_idx == LC82C168)
		csr0 &= ~0xfff10000; /* zero reserved bits 31:20, 16 */

	/* DM9102A has troubles with MRM & clear reserved bits 24:22, 20, 16, 7:1 */
	अगर (tulip_uli_dm_quirk(pdev)) अणु
		csr0 &= ~0x01f100ff;
#अगर defined(CONFIG_SPARC)
                csr0 = (csr0 & ~0xff00) | 0xe000;
#पूर्ण_अगर
	पूर्ण
	/*
	 *	And back to business
	 */

	i = pci_enable_device(pdev);
	अगर (i) अणु
		pr_err("Cannot enable tulip board #%d, aborting\n", board_idx);
		वापस i;
	पूर्ण

	irq = pdev->irq;

	/* alloc_etherdev ensures aligned and zeroed निजी काष्ठाures */
	dev = alloc_etherdev (माप (*tp));
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);
	अगर (pci_resource_len (pdev, 0) < tulip_tbl[chip_idx].io_size) अणु
		pr_err("%s: I/O region (0x%llx@0x%llx) too small, aborting\n",
		       pci_name(pdev),
		       (अचिन्हित दीर्घ दीर्घ)pci_resource_len (pdev, 0),
		       (अचिन्हित दीर्घ दीर्घ)pci_resource_start (pdev, 0));
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	/* grab all resources from both PIO and MMIO regions, as we
	 * करोn't want anyone अन्यथा messing around with our hardware */
	अगर (pci_request_regions (pdev, DRV_NAME))
		जाओ err_out_मुक्त_netdev;

	ioaddr =  pci_iomap(pdev, TULIP_BAR, tulip_tbl[chip_idx].io_size);

	अगर (!ioaddr)
		जाओ err_out_मुक्त_res;

	/*
	 * initialize निजी data काष्ठाure 'tp'
	 * it is zeroed and aligned in alloc_etherdev
	 */
	tp = netdev_priv(dev);
	tp->dev = dev;

	tp->rx_ring = dma_alloc_coherent(&pdev->dev,
					 माप(काष्ठा tulip_rx_desc) * RX_RING_SIZE +
					 माप(काष्ठा tulip_tx_desc) * TX_RING_SIZE,
					 &tp->rx_ring_dma, GFP_KERNEL);
	अगर (!tp->rx_ring)
		जाओ err_out_mtable;
	tp->tx_ring = (काष्ठा tulip_tx_desc *)(tp->rx_ring + RX_RING_SIZE);
	tp->tx_ring_dma = tp->rx_ring_dma + माप(काष्ठा tulip_rx_desc) * RX_RING_SIZE;

	tp->chip_id = chip_idx;
	tp->flags = tulip_tbl[chip_idx].flags;

	tp->wolinfo.supported = 0;
	tp->wolinfo.wolopts = 0;
	/* COMET: Enable घातer management only क्रम AN983B */
	अगर (chip_idx == COMET ) अणु
		u32 sig;
		pci_पढ़ो_config_dword (pdev, 0x80, &sig);
		अगर (sig == 0x09811317) अणु
			tp->flags |= COMET_PM;
			tp->wolinfo.supported = WAKE_PHY | WAKE_MAGIC;
			pr_info("%s: Enabled WOL support for AN983B\n",
				__func__);
		पूर्ण
	पूर्ण
	tp->pdev = pdev;
	tp->base_addr = ioaddr;
	tp->revision = pdev->revision;
	tp->csr0 = csr0;
	spin_lock_init(&tp->lock);
	spin_lock_init(&tp->mii_lock);
	समयr_setup(&tp->समयr, tulip_tbl[tp->chip_id].media_समयr, 0);

	INIT_WORK(&tp->media_work, tulip_tbl[tp->chip_id].media_task);

#अगर_घोषित CONFIG_TULIP_MWI
	अगर (!क्रमce_csr0 && (tp->flags & HAS_PCI_MWI))
		tulip_mwi_config (pdev, dev);
#पूर्ण_अगर

	/* Stop the chip's Tx and Rx processes. */
	tulip_stop_rxtx(tp);

	pci_set_master(pdev);

#अगर_घोषित CONFIG_GSC
	अगर (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_HP) अणु
		चयन (pdev->subप्रणाली_device) अणु
		शेष:
			अवरोध;
		हाल 0x1061:
		हाल 0x1062:
		हाल 0x1063:
		हाल 0x1098:
		हाल 0x1099:
		हाल 0x10EE:
			tp->flags |= HAS_SWAPPED_SEEPROM | NEEDS_FAKE_MEDIA_TABLE;
			chip_name = "GSC DS21140 Tulip";
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Clear the missed-packet counter. */
	ioपढ़ो32(ioaddr + CSR8);

	/* The station address ROM is पढ़ो byte serially.  The रेजिस्टर must
	   be polled, रुकोing क्रम the value to be पढ़ो bit serially from the
	   EEPROM.
	   */
	ee_data = tp->eeprom;
	स_रखो(ee_data, 0, माप(tp->eeprom));
	sum = 0;
	अगर (chip_idx == LC82C168) अणु
		क्रम (i = 0; i < 3; i++) अणु
			पूर्णांक value, boguscnt = 100000;
			ioग_लिखो32(0x600 | i, ioaddr + 0x98);
			करो अणु
				value = ioपढ़ो32(ioaddr + CSR9);
			पूर्ण जबतक (value < 0  && --boguscnt > 0);
			put_unaligned_le16(value, ((__le16 *)dev->dev_addr) + i);
			sum += value & 0xffff;
		पूर्ण
	पूर्ण अन्यथा अगर (chip_idx == COMET) अणु
		/* No need to पढ़ो the EEPROM. */
		put_unaligned_le32(ioपढ़ो32(ioaddr + 0xA4), dev->dev_addr);
		put_unaligned_le16(ioपढ़ो32(ioaddr + 0xA8), dev->dev_addr + 4);
		क्रम (i = 0; i < 6; i ++)
			sum += dev->dev_addr[i];
	पूर्ण अन्यथा अणु
		/* A serial EEPROM पूर्णांकerface, we पढ़ो now and sort it out later. */
		पूर्णांक sa_offset = 0;
		पूर्णांक ee_addr_size = tulip_पढ़ो_eeprom(dev, 0xff, 8) & 0x40000 ? 8 : 6;
		पूर्णांक ee_max_addr = ((1 << ee_addr_size) - 1) * माप(u16);

		अगर (ee_max_addr > माप(tp->eeprom))
			ee_max_addr = माप(tp->eeprom);

		क्रम (i = 0; i < ee_max_addr ; i += माप(u16)) अणु
			u16 data = tulip_पढ़ो_eeprom(dev, i/2, ee_addr_size);
			ee_data[i] = data & 0xff;
			ee_data[i + 1] = data >> 8;
		पूर्ण

		/* DEC now has a specअगरication (see Notes) but early board makers
		   just put the address in the first EEPROM locations. */
		/* This करोes  स_भेद(ee_data, ee_data+16, 8) */
		क्रम (i = 0; i < 8; i ++)
			अगर (ee_data[i] != ee_data[16+i])
				sa_offset = 20;
		अगर (chip_idx == CONEXANT) अणु
			/* Check that the tuple type and length is correct. */
			अगर (ee_data[0x198] == 0x04  &&  ee_data[0x199] == 6)
				sa_offset = 0x19A;
		पूर्ण अन्यथा अगर (ee_data[0] == 0xff  &&  ee_data[1] == 0xff &&
				   ee_data[2] == 0) अणु
			sa_offset = 2;		/* Grrr, damn Matrox boards. */
		पूर्ण
#अगर_घोषित CONFIG_MIPS_COBALT
               अगर ((pdev->bus->number == 0) &&
                   ((PCI_SLOT(pdev->devfn) == 7) ||
                    (PCI_SLOT(pdev->devfn) == 12))) अणु
                       /* Cobalt MAC address in first EEPROM locations. */
                       sa_offset = 0;
		       /* Ensure our media table fixup get's applied */
		       स_नकल(ee_data + 16, ee_data, 8);
               पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_GSC
		/* Check to see अगर we have a broken srom */
		अगर (ee_data[0] == 0x61 && ee_data[1] == 0x10) अणु
			/* pci_venकरोr_id and subप्रणाली_id are swapped */
			ee_data[0] = ee_data[2];
			ee_data[1] = ee_data[3];
			ee_data[2] = 0x61;
			ee_data[3] = 0x10;

			/* HSC-PCI boards need to be byte-swaped and shअगरted
			 * up 1 word.  This shअगरt needs to happen at the end
			 * of the MAC first because of the 2 byte overlap.
			 */
			क्रम (i = 4; i >= 0; i -= 2) अणु
				ee_data[17 + i + 3] = ee_data[17 + i];
				ee_data[16 + i + 5] = ee_data[16 + i];
			पूर्ण
		पूर्ण
#पूर्ण_अगर

		क्रम (i = 0; i < 6; i ++) अणु
			dev->dev_addr[i] = ee_data[i + sa_offset];
			sum += ee_data[i + sa_offset];
		पूर्ण
	पूर्ण
	/* Lite-On boards have the address byte-swapped. */
	अगर ((dev->dev_addr[0] == 0xA0 ||
	     dev->dev_addr[0] == 0xC0 ||
	     dev->dev_addr[0] == 0x02) &&
	    dev->dev_addr[1] == 0x00)
		क्रम (i = 0; i < 6; i+=2) अणु
			अक्षर पंचांगp = dev->dev_addr[i];
			dev->dev_addr[i] = dev->dev_addr[i+1];
			dev->dev_addr[i+1] = पंचांगp;
		पूर्ण
	/* On the Zynx 315 Etherarray and other multiport boards only the
	   first Tulip has an EEPROM.
	   On Sparc प्रणालीs the mac address is held in the OBP property
	   "local-mac-address".
	   The addresses of the subsequent ports are derived from the first.
	   Many PCI BIOSes also incorrectly report the IRQ line, so we correct
	   that here as well. */
	अगर (sum == 0  || sum == 6*0xff) अणु
#अगर defined(CONFIG_SPARC)
		काष्ठा device_node *dp = pci_device_to_OF_node(pdev);
		स्थिर अचिन्हित अक्षर *addr;
		पूर्णांक len;
#पूर्ण_अगर
		eeprom_missing = 1;
		क्रम (i = 0; i < 5; i++)
			dev->dev_addr[i] = last_phys_addr[i];
		dev->dev_addr[i] = last_phys_addr[i] + 1;
#अगर defined(CONFIG_SPARC)
		addr = of_get_property(dp, "local-mac-address", &len);
		अगर (addr && len == ETH_ALEN)
			स_नकल(dev->dev_addr, addr, ETH_ALEN);
#पूर्ण_अगर
#अगर defined(__i386__) || defined(__x86_64__)	/* Patch up x86 BIOS bug. */
		अगर (last_irq)
			irq = last_irq;
#पूर्ण_अगर
	पूर्ण

	क्रम (i = 0; i < 6; i++)
		last_phys_addr[i] = dev->dev_addr[i];
#अगर defined(__i386__) || defined(__x86_64__)	/* Patch up x86 BIOS bug. */
	last_irq = irq;
#पूर्ण_अगर

	/* The lower four bits are the media type. */
	अगर (board_idx >= 0  &&  board_idx < MAX_UNITS) अणु
		अगर (options[board_idx] & MEDIA_MASK)
			tp->शेष_port = options[board_idx] & MEDIA_MASK;
		अगर ((options[board_idx] & FullDuplex) || full_duplex[board_idx] > 0)
			tp->full_duplex = 1;
		अगर (mtu[board_idx] > 0)
			dev->mtu = mtu[board_idx];
	पूर्ण
	अगर (dev->mem_start & MEDIA_MASK)
		tp->शेष_port = dev->mem_start & MEDIA_MASK;
	अगर (tp->शेष_port) अणु
		pr_info(DRV_NAME "%d: Transceiver selection forced to %s\n",
			board_idx, medianame[tp->शेष_port & MEDIA_MASK]);
		tp->medialock = 1;
		अगर (tulip_media_cap[tp->शेष_port] & MediaAlwaysFD)
			tp->full_duplex = 1;
	पूर्ण
	अगर (tp->full_duplex)
		tp->full_duplex_lock = 1;

	अगर (tulip_media_cap[tp->शेष_port] & MediaIsMII) अणु
		अटल स्थिर u16 media2advert[] = अणु
			0x20, 0x40, 0x03e0, 0x60, 0x80, 0x100, 0x200
		पूर्ण;
		tp->mii_advertise = media2advert[tp->शेष_port - 9];
		tp->mii_advertise |= (tp->flags & HAS_8023X); /* Matching bits! */
	पूर्ण

	अगर (tp->flags & HAS_MEDIA_TABLE) अणु
		प्र_लिखो(dev->name, DRV_NAME "%d", board_idx);	/* hack */
		tulip_parse_eeprom(dev);
		म_नकल(dev->name, "eth%d");			/* un-hack */
	पूर्ण

	अगर ((tp->flags & ALWAYS_CHECK_MII) ||
		(tp->mtable  &&  tp->mtable->has_mii) ||
		( ! tp->mtable  &&  (tp->flags & HAS_MII))) अणु
		अगर (tp->mtable  &&  tp->mtable->has_mii) अणु
			क्रम (i = 0; i < tp->mtable->leafcount; i++)
				अगर (tp->mtable->mleaf[i].media == 11) अणु
					tp->cur_index = i;
					tp->saved_अगर_port = dev->अगर_port;
					tulip_select_media(dev, 2);
					dev->अगर_port = tp->saved_अगर_port;
					अवरोध;
				पूर्ण
		पूर्ण

		/* Find the connected MII xcvrs.
		   Doing this in खोलो() would allow detecting बाह्यal xcvrs
		   later, but takes much समय. */
		tulip_find_mii (dev, board_idx);
	पूर्ण

	/* The Tulip-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &tulip_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
#अगर_घोषित CONFIG_TULIP_NAPI
	netअगर_napi_add(dev, &tp->napi, tulip_poll, 16);
#पूर्ण_अगर
	dev->ethtool_ops = &ops;

	अगर (रेजिस्टर_netdev(dev))
		जाओ err_out_मुक्त_ring;

	pci_set_drvdata(pdev, dev);

	dev_info(&dev->dev,
#अगर_घोषित CONFIG_TULIP_MMIO
		 "%s rev %d at MMIO %#llx,%s %pM, IRQ %d\n",
#अन्यथा
		 "%s rev %d at Port %#llx,%s %pM, IRQ %d\n",
#पूर्ण_अगर
		 chip_name, pdev->revision,
		 (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, TULIP_BAR),
		 eeprom_missing ? " EEPROM not present," : "",
		 dev->dev_addr, irq);

        अगर (tp->chip_id == PNIC2)
		tp->link_change = pnic2_lnk_change;
	अन्यथा अगर (tp->flags & HAS_NWAY)
		tp->link_change = t21142_lnk_change;
	अन्यथा अगर (tp->flags & HAS_PNICNWAY)
		tp->link_change = pnic_lnk_change;

	/* Reset the xcvr पूर्णांकerface and turn on heartbeat. */
	चयन (chip_idx) अणु
	हाल DC21140:
	हाल DM910X:
	शेष:
		अगर (tp->mtable)
			ioग_लिखो32(tp->mtable->csr12dir | 0x100, ioaddr + CSR12);
		अवरोध;
	हाल DC21142:
		अगर (tp->mii_cnt  ||  tulip_media_cap[dev->अगर_port] & MediaIsMII) अणु
			ioग_लिखो32(csr6_mask_deख_स्थितिe, ioaddr + CSR6);
			ioग_लिखो32(0x0000, ioaddr + CSR13);
			ioग_लिखो32(0x0000, ioaddr + CSR14);
			ioग_लिखो32(csr6_mask_hdcap, ioaddr + CSR6);
		पूर्ण अन्यथा
			t21142_start_nway(dev);
		अवरोध;
	हाल PNIC2:
	        /* just करो a reset क्रम sanity sake */
		ioग_लिखो32(0x0000, ioaddr + CSR13);
		ioग_लिखो32(0x0000, ioaddr + CSR14);
		अवरोध;
	हाल LC82C168:
		अगर ( ! tp->mii_cnt) अणु
			tp->nway = 1;
			tp->nwayset = 0;
			ioग_लिखो32(csr6_tपंचांग | csr6_ca, ioaddr + CSR6);
			ioग_लिखो32(0x30, ioaddr + CSR12);
			ioग_लिखो32(0x0001F078, ioaddr + CSR6);
			ioग_लिखो32(0x0201F078, ioaddr + CSR6); /* Turn on स्वतःnegotiation. */
		पूर्ण
		अवरोध;
	हाल MX98713:
	हाल COMPEX9881:
		ioग_लिखो32(0x00000000, ioaddr + CSR6);
		ioग_लिखो32(0x000711C0, ioaddr + CSR14); /* Turn on NWay. */
		ioग_लिखो32(0x00000001, ioaddr + CSR13);
		अवरोध;
	हाल MX98715:
	हाल MX98725:
		ioग_लिखो32(0x01a80000, ioaddr + CSR6);
		ioग_लिखो32(0xFFFFFFFF, ioaddr + CSR14);
		ioग_लिखो32(0x00001000, ioaddr + CSR12);
		अवरोध;
	हाल COMET:
		/* No initialization necessary. */
		अवरोध;
	पूर्ण

	/* put the chip in snooze mode until खोलोed */
	tulip_set_घातer_state (tp, 0, 1);

	वापस 0;

err_out_मुक्त_ring:
	dma_मुक्त_coherent(&pdev->dev,
			  माप(काष्ठा tulip_rx_desc) * RX_RING_SIZE +
			  माप(काष्ठा tulip_tx_desc) * TX_RING_SIZE,
			  tp->rx_ring, tp->rx_ring_dma);

err_out_mtable:
	kमुक्त (tp->mtable);
	pci_iounmap(pdev, ioaddr);

err_out_मुक्त_res:
	pci_release_regions (pdev);

err_out_मुक्त_netdev:
	मुक्त_netdev (dev);
	वापस -ENODEV;
पूर्ण


/* set the रेजिस्टरs according to the given wolopts */
अटल व्योम tulip_set_wolopts (काष्ठा pci_dev *pdev, u32 wolopts)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;

	अगर (tp->flags & COMET_PM) अणु
		अचिन्हित पूर्णांक पंचांगp;

		पंचांगp = ioपढ़ो32(ioaddr + CSR18);
		पंचांगp &= ~(comet_csr18_pmes_sticky | comet_csr18_apm_mode | comet_csr18_d3a);
		पंचांगp |= comet_csr18_pm_mode;
		ioग_लिखो32(पंचांगp, ioaddr + CSR18);

		/* Set the Wake-up Control/Status Register to the given WOL options*/
		पंचांगp = ioपढ़ो32(ioaddr + CSR13);
		पंचांगp &= ~(comet_csr13_linkoffe | comet_csr13_linkone | comet_csr13_wfre | comet_csr13_lsce | comet_csr13_mpre);
		अगर (wolopts & WAKE_MAGIC)
			पंचांगp |= comet_csr13_mpre;
		अगर (wolopts & WAKE_PHY)
			पंचांगp |= comet_csr13_linkoffe | comet_csr13_linkone | comet_csr13_lsce;
		/* Clear the event flags */
		पंचांगp |= comet_csr13_wfr | comet_csr13_mpr | comet_csr13_lsc;
		ioग_लिखो32(पंचांगp, ioaddr + CSR13);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused tulip_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा tulip_निजी *tp = netdev_priv(dev);

	अगर (!dev)
		वापस -EINVAL;

	अगर (!netअगर_running(dev))
		जाओ save_state;

	tulip_करोwn(dev);

	netअगर_device_detach(dev);
	/* FIXME: it needlessly adds an error path. */
	मुक्त_irq(tp->pdev->irq, dev);

save_state:
	tulip_set_wolopts(to_pci_dev(dev_d), tp->wolinfo.wolopts);
	device_set_wakeup_enable(dev_d, !!tp->wolinfo.wolopts);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tulip_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक retval = 0;

	अगर (!dev)
		वापस -EINVAL;

	अगर (!netअगर_running(dev))
		वापस 0;

	retval = request_irq(pdev->irq, tulip_पूर्णांकerrupt, IRQF_SHARED,
			     dev->name, dev);
	अगर (retval) अणु
		pr_err("request_irq failed in resume\n");
		वापस retval;
	पूर्ण

	अगर (tp->flags & COMET_PM) अणु
		device_set_wakeup_enable(dev_d, 0);

		/* Clear the PMES flag */
		पंचांगp = ioपढ़ो32(ioaddr + CSR20);
		पंचांगp |= comet_csr20_pmes;
		ioग_लिखो32(पंचांगp, ioaddr + CSR20);

		/* Disable all wake-up events */
		tulip_set_wolopts(pdev, 0);
	पूर्ण
	netअगर_device_attach(dev);

	अगर (netअगर_running(dev))
		tulip_up(dev);

	वापस 0;
पूर्ण

अटल व्योम tulip_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata (pdev);
	काष्ठा tulip_निजी *tp;

	अगर (!dev)
		वापस;

	tp = netdev_priv(dev);
	unरेजिस्टर_netdev(dev);
	dma_मुक्त_coherent(&pdev->dev,
			  माप(काष्ठा tulip_rx_desc) * RX_RING_SIZE +
			  माप(काष्ठा tulip_tx_desc) * TX_RING_SIZE,
			  tp->rx_ring, tp->rx_ring_dma);
	kमुक्त (tp->mtable);
	pci_iounmap(pdev, tp->base_addr);
	मुक्त_netdev (dev);
	pci_release_regions (pdev);
	pci_disable_device(pdev);

	/* pci_घातer_off (pdev, -1); */
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */

अटल व्योम poll_tulip (काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	स्थिर पूर्णांक irq = tp->pdev->irq;

	/* disable_irq here is not very nice, but with the lockless
	   पूर्णांकerrupt handler we have no other choice. */
	disable_irq(irq);
	tulip_पूर्णांकerrupt (irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tulip_pm_ops, tulip_suspend, tulip_resume);

अटल काष्ठा pci_driver tulip_driver = अणु
	.name		= DRV_NAME,
	.id_table	= tulip_pci_tbl,
	.probe		= tulip_init_one,
	.हटाओ		= tulip_हटाओ_one,
	.driver.pm	= &tulip_pm_ops,
पूर्ण;


अटल पूर्णांक __init tulip_init (व्योम)
अणु
	अगर (!csr0) अणु
		pr_warn("tulip: unknown CPU architecture, using default csr0\n");
		/* शेष to 8 दीर्घword cache line alignment */
		csr0 = 0x00A00000 | 0x4800;
	पूर्ण

	/* copy module parms पूर्णांकo globals */
	tulip_rx_copyअवरोध = rx_copyअवरोध;
	tulip_max_पूर्णांकerrupt_work = max_पूर्णांकerrupt_work;

	/* probe क्रम and init boards */
	वापस pci_रेजिस्टर_driver(&tulip_driver);
पूर्ण


अटल व्योम __निकास tulip_cleanup (व्योम)
अणु
	pci_unरेजिस्टर_driver (&tulip_driver);
पूर्ण


module_init(tulip_init);
module_निकास(tulip_cleanup);
