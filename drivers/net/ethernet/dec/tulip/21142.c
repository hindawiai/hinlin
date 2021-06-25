<शैली गुरु>
/*
	drivers/net/ethernet/dec/tulip/21142.c

	Copyright 2000,2001  The Linux Kernel Team
	Written/copyright 1994-2001 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	DC21143 manual "21143 PCI/CardBus 10/100Mb/s Ethernet LAN Controller
	Hardware Reference Manual" is currently available at :
	http://developer.पूर्णांकel.com/design/network/manuals/278074.hपंचांग

	Please submit bugs to http://bugzilla.kernel.org/ .
*/

#समावेश <linux/delay.h>
#समावेश "tulip.h"


अटल u16 t21142_csr13[] = अणु 0x0001, 0x0009, 0x0009, 0x0000, 0x0001, पूर्ण;
u16 t21142_csr14[] =	    अणु 0xFFFF, 0x0705, 0x0705, 0x0000, 0x7F3D, पूर्ण;
अटल u16 t21142_csr15[] = अणु 0x0008, 0x0006, 0x000E, 0x0008, 0x0008, पूर्ण;


/* Handle the 21143 uniquely: करो स्वतःselect with NWay, not the EEPROM list
   of available transceivers.  */
व्योम t21142_media_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tulip_निजी *tp =
		container_of(work, काष्ठा tulip_निजी, media_work);
	काष्ठा net_device *dev = tp->dev;
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक csr12 = ioपढ़ो32(ioaddr + CSR12);
	पूर्णांक next_tick = 60*HZ;
	पूर्णांक new_csr6 = 0;
	पूर्णांक csr14 = ioपढ़ो32(ioaddr + CSR14);

	/* CSR12[LS10,LS100] are not reliable during स्वतःnegotiation */
	अगर ((csr14 & 0x80) && (csr12 & 0x7000) != 0x5000)
		csr12 |= 6;
	अगर (tulip_debug > 2)
		dev_info(&dev->dev, "21143 negotiation status %08x, %s\n",
			 csr12, medianame[dev->अगर_port]);
	अगर (tulip_media_cap[dev->अगर_port] & MediaIsMII) अणु
		अगर (tulip_check_duplex(dev) < 0) अणु
			netअगर_carrier_off(dev);
			next_tick = 3*HZ;
		पूर्ण अन्यथा अणु
			netअगर_carrier_on(dev);
			next_tick = 60*HZ;
		पूर्ण
	पूर्ण अन्यथा अगर (tp->nwayset) अणु
		/* Don't screw up a negotiated session! */
		अगर (tulip_debug > 1)
			dev_info(&dev->dev,
				 "Using NWay-set %s media, csr12 %08x\n",
				 medianame[dev->अगर_port], csr12);
	पूर्ण अन्यथा अगर (tp->medialock) अणु
			;
	पूर्ण अन्यथा अगर (dev->अगर_port == 3) अणु
		अगर (csr12 & 2) अणु	/* No 100mbps link beat, revert to 10mbps. */
			अगर (tulip_debug > 1)
				dev_info(&dev->dev,
					 "No 21143 100baseTx link beat, %08x, trying NWay\n",
					 csr12);
			t21142_start_nway(dev);
			next_tick = 3*HZ;
		पूर्ण
	पूर्ण अन्यथा अगर ((csr12 & 0x7000) != 0x5000) अणु
		/* Negotiation failed.  Search media types. */
		अगर (tulip_debug > 1)
			dev_info(&dev->dev,
				 "21143 negotiation failed, status %08x\n",
				 csr12);
		अगर (!(csr12 & 4)) अणु		/* 10mbps link beat good. */
			new_csr6 = 0x82420000;
			dev->अगर_port = 0;
			ioग_लिखो32(0, ioaddr + CSR13);
			ioग_लिखो32(0x0003FFFF, ioaddr + CSR14);
			ioग_लिखो16(t21142_csr15[dev->अगर_port], ioaddr + CSR15);
			ioग_लिखो32(t21142_csr13[dev->अगर_port], ioaddr + CSR13);
		पूर्ण अन्यथा अणु
			/* Select 100mbps port to check क्रम link beat. */
			new_csr6 = 0x83860000;
			dev->अगर_port = 3;
			ioग_लिखो32(0, ioaddr + CSR13);
			ioग_लिखो32(0x0003FFFF, ioaddr + CSR14);
			ioग_लिखो16(8, ioaddr + CSR15);
			ioग_लिखो32(1, ioaddr + CSR13);
		पूर्ण
		अगर (tulip_debug > 1)
			dev_info(&dev->dev, "Testing new 21143 media %s\n",
				 medianame[dev->अगर_port]);
		अगर (new_csr6 != (tp->csr6 & ~0x00D5)) अणु
			tp->csr6 &= 0x00D5;
			tp->csr6 |= new_csr6;
			ioग_लिखो32(0x0301, ioaddr + CSR12);
			tulip_restart_rxtx(tp);
		पूर्ण
		next_tick = 3*HZ;
	पूर्ण

	/* mod_समयr synchronizes us with potential add_समयr calls
	 * from पूर्णांकerrupts.
	 */
	mod_समयr(&tp->समयr, RUN_AT(next_tick));
पूर्ण


व्योम t21142_start_nway(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक csr14 = ((tp->sym_advertise & 0x0780) << 9)  |
		((tp->sym_advertise & 0x0020) << 1) | 0xffbf;

	dev->अगर_port = 0;
	tp->nway = tp->mediasense = 1;
	tp->nwayset = tp->lpar = 0;
	अगर (tulip_debug > 1)
		netdev_dbg(dev, "Restarting 21143 autonegotiation, csr14=%08x\n",
			   csr14);
	ioग_लिखो32(0x0001, ioaddr + CSR13);
	udelay(100);
	ioग_लिखो32(csr14, ioaddr + CSR14);
	tp->csr6 = 0x82420000 | (tp->sym_advertise & 0x0040 ? FullDuplex : 0);
	ioग_लिखो32(tp->csr6, ioaddr + CSR6);
	अगर (tp->mtable  &&  tp->mtable->csr15dir) अणु
		ioग_लिखो32(tp->mtable->csr15dir, ioaddr + CSR15);
		ioग_लिखो32(tp->mtable->csr15val, ioaddr + CSR15);
	पूर्ण अन्यथा
		ioग_लिखो16(0x0008, ioaddr + CSR15);
	ioग_लिखो32(0x1301, ioaddr + CSR12); 		/* Trigger NWAY. */
पूर्ण



व्योम t21142_lnk_change(काष्ठा net_device *dev, पूर्णांक csr5)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक csr12 = ioपढ़ो32(ioaddr + CSR12);
	पूर्णांक csr14 = ioपढ़ो32(ioaddr + CSR14);

	/* CSR12[LS10,LS100] are not reliable during स्वतःnegotiation */
	अगर ((csr14 & 0x80) && (csr12 & 0x7000) != 0x5000)
		csr12 |= 6;
	अगर (tulip_debug > 1)
		dev_info(&dev->dev,
			 "21143 link status interrupt %08x, CSR5 %x, %08x\n",
			 csr12, csr5, csr14);

	/* If NWay finished and we have a negotiated partner capability. */
	अगर (tp->nway  &&  !tp->nwayset  &&  (csr12 & 0x7000) == 0x5000) अणु
		पूर्णांक setup_करोne = 0;
		पूर्णांक negotiated = tp->sym_advertise & (csr12 >> 16);
		tp->lpar = csr12 >> 16;
		tp->nwayset = 1;
		/* If partner cannot negotiate, it is 10Mbps Half Duplex */
		अगर (!(csr12 & 0x8000))		dev->अगर_port = 0;
		अन्यथा अगर (negotiated & 0x0100)	dev->अगर_port = 5;
		अन्यथा अगर (negotiated & 0x0080)	dev->अगर_port = 3;
		अन्यथा अगर (negotiated & 0x0040)	dev->अगर_port = 4;
		अन्यथा अगर (negotiated & 0x0020)	dev->अगर_port = 0;
		अन्यथा अणु
			tp->nwayset = 0;
			अगर ((csr12 & 2) == 0  &&  (tp->sym_advertise & 0x0180))
				dev->अगर_port = 3;
		पूर्ण
		tp->full_duplex = (tulip_media_cap[dev->अगर_port] & MediaAlwaysFD) ? 1:0;

		अगर (tulip_debug > 1) अणु
			अगर (tp->nwayset)
				dev_info(&dev->dev,
					 "Switching to %s based on link negotiation %04x & %04x = %04x\n",
					 medianame[dev->अगर_port],
					 tp->sym_advertise, tp->lpar,
					 negotiated);
			अन्यथा
				dev_info(&dev->dev,
					 "Autonegotiation failed, using %s, link beat status %04x\n",
					 medianame[dev->अगर_port], csr12);
		पूर्ण

		अगर (tp->mtable) अणु
			पूर्णांक i;
			क्रम (i = 0; i < tp->mtable->leafcount; i++)
				अगर (tp->mtable->mleaf[i].media == dev->अगर_port) अणु
					पूर्णांक startup = ! ((tp->chip_id == DC21143 && (tp->revision == 48 || tp->revision == 65)));
					tp->cur_index = i;
					tulip_select_media(dev, startup);
					setup_करोne = 1;
					अवरोध;
				पूर्ण
		पूर्ण
		अगर ( ! setup_करोne) अणु
			tp->csr6 = (dev->अगर_port & 1 ? 0x838E0000 : 0x82420000) | (tp->csr6 & 0x20ff);
			अगर (tp->full_duplex)
				tp->csr6 |= 0x0200;
			ioग_लिखो32(1, ioaddr + CSR13);
		पूर्ण
#अगर 0							/* Restart shouldn't be needed. */
		ioग_लिखो32(tp->csr6 | RxOn, ioaddr + CSR6);
		अगर (tulip_debug > 2)
			netdev_dbg(dev, " Restarting Tx and Rx, CSR5 is %08x\n",
				   ioपढ़ो32(ioaddr + CSR5));
#पूर्ण_अगर
		tulip_start_rxtx(tp);
		अगर (tulip_debug > 2)
			netdev_dbg(dev, " Setting CSR6 %08x/%x CSR12 %08x\n",
				   tp->csr6, ioपढ़ो32(ioaddr + CSR6),
				   ioपढ़ो32(ioaddr + CSR12));
	पूर्ण अन्यथा अगर ((tp->nwayset  &&  (csr5 & 0x08000000) &&
		    (dev->अगर_port == 3  ||  dev->अगर_port == 5) &&
		    (csr12 & 2) == 2) ||
		   (tp->nway && (csr5 & (TPLnkFail)))) अणु
		/* Link blew? Maybe restart NWay. */
		del_समयr_sync(&tp->समयr);
		t21142_start_nway(dev);
		tp->समयr.expires = RUN_AT(3*HZ);
		add_समयr(&tp->समयr);
	पूर्ण अन्यथा अगर (dev->अगर_port == 3  ||  dev->अगर_port == 5) अणु
		अगर (tulip_debug > 1)
			dev_info(&dev->dev, "21143 %s link beat %s\n",
				 medianame[dev->अगर_port],
				 (csr12 & 2) ? "failed" : "good");
		अगर ((csr12 & 2)  &&  ! tp->medialock) अणु
			del_समयr_sync(&tp->समयr);
			t21142_start_nway(dev);
			tp->समयr.expires = RUN_AT(3*HZ);
			add_समयr(&tp->समयr);
		पूर्ण अन्यथा अगर (dev->अगर_port == 5)
			ioग_लिखो32(csr14 & ~0x080, ioaddr + CSR14);
	पूर्ण अन्यथा अगर (dev->अगर_port == 0  ||  dev->अगर_port == 4) अणु
		अगर ((csr12 & 4) == 0)
			dev_info(&dev->dev, "21143 10baseT link beat good\n");
	पूर्ण अन्यथा अगर (!(csr12 & 4)) अणु		/* 10mbps link beat good. */
		अगर (tulip_debug)
			dev_info(&dev->dev, "21143 10mbps sensed media\n");
		dev->अगर_port = 0;
	पूर्ण अन्यथा अगर (tp->nwayset) अणु
		अगर (tulip_debug)
			dev_info(&dev->dev, "21143 using NWay-set %s, csr6 %08x\n",
				 medianame[dev->अगर_port], tp->csr6);
	पूर्ण अन्यथा अणु		/* 100mbps link beat good. */
		अगर (tulip_debug)
			dev_info(&dev->dev, "21143 100baseTx sensed media\n");
		dev->अगर_port = 3;
		tp->csr6 = 0x838E0000 | (tp->csr6 & 0x20ff);
		ioग_लिखो32(0x0003FF7F, ioaddr + CSR14);
		ioग_लिखो32(0x0301, ioaddr + CSR12);
		tulip_restart_rxtx(tp);
	पूर्ण
पूर्ण


