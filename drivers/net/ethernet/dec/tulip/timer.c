<शैली गुरु>
/*
	drivers/net/ethernet/dec/tulip/समयr.c

	Copyright 2000,2001  The Linux Kernel Team
	Written/copyright 1994-2001 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	Please submit bugs to http://bugzilla.kernel.org/ .
*/


#समावेश "tulip.h"


व्योम tulip_media_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tulip_निजी *tp =
		container_of(work, काष्ठा tulip_निजी, media_work);
	काष्ठा net_device *dev = tp->dev;
	व्योम __iomem *ioaddr = tp->base_addr;
	u32 csr12 = ioपढ़ो32(ioaddr + CSR12);
	पूर्णांक next_tick = 2*HZ;
	अचिन्हित दीर्घ flags;

	अगर (tulip_debug > 2) अणु
		netdev_dbg(dev, "Media selection tick, %s, status %08x mode %08x SIA %08x %08x %08x %08x\n",
			   medianame[dev->अगर_port],
			   ioपढ़ो32(ioaddr + CSR5), ioपढ़ो32(ioaddr + CSR6),
			   csr12, ioपढ़ो32(ioaddr + CSR13),
			   ioपढ़ो32(ioaddr + CSR14), ioपढ़ो32(ioaddr + CSR15));
	पूर्ण
	चयन (tp->chip_id) अणु
	हाल DC21140:
	हाल DC21142:
	हाल MX98713:
	हाल COMPEX9881:
	हाल DM910X:
	शेष: अणु
		काष्ठा medialeaf *mleaf;
		अचिन्हित अक्षर *p;
		अगर (tp->mtable == शून्य) अणु	/* No EEPROM info, use generic code. */
			/* Not much that can be करोne.
			   Assume this a generic MII or SYM transceiver. */
			next_tick = 60*HZ;
			अगर (tulip_debug > 2)
				netdev_dbg(dev, "network media monitor CSR6 %08x CSR12 0x%02x\n",
					   ioपढ़ो32(ioaddr + CSR6),
					   csr12 & 0xff);
			अवरोध;
		पूर्ण
		mleaf = &tp->mtable->mleaf[tp->cur_index];
		p = mleaf->leafdata;
		चयन (mleaf->type) अणु
		हाल 0: हाल 4: अणु
			/* Type 0 serial or 4 SYM transceiver.  Check the link beat bit. */
			पूर्णांक offset = mleaf->type == 4 ? 5 : 2;
			s8 bitnum = p[offset];
			अगर (p[offset+1] & 0x80) अणु
				अगर (tulip_debug > 1)
					netdev_dbg(dev, "Transceiver monitor tick CSR12=%#02x, no media sense\n",
						   csr12);
				अगर (mleaf->type == 4) अणु
					अगर (mleaf->media == 3 && (csr12 & 0x02))
						जाओ select_next_media;
				पूर्ण
				अवरोध;
			पूर्ण
			अगर (tulip_debug > 2)
				netdev_dbg(dev, "Transceiver monitor tick: CSR12=%#02x bit %d is %d, expecting %d\n",
					   csr12, (bitnum >> 1) & 7,
					   (csr12 & (1 << ((bitnum >> 1) & 7))) != 0,
					   (bitnum >= 0));
			/* Check that the specअगरied bit has the proper value. */
			अगर ((bitnum < 0) !=
				((csr12 & (1 << ((bitnum >> 1) & 7))) != 0)) अणु
				अगर (tulip_debug > 2)
					netdev_dbg(dev, "Link beat detected for %s\n",
						   medianame[mleaf->media & MEDIA_MASK]);
				अगर ((p[2] & 0x61) == 0x01)	/* Bogus Znyx board. */
					जाओ actually_mii;
				netअगर_carrier_on(dev);
				अवरोध;
			पूर्ण
			netअगर_carrier_off(dev);
			अगर (tp->medialock)
				अवरोध;
	  select_next_media:
			अगर (--tp->cur_index < 0) अणु
				/* We start again, but should instead look क्रम शेष. */
				tp->cur_index = tp->mtable->leafcount - 1;
			पूर्ण
			dev->अगर_port = tp->mtable->mleaf[tp->cur_index].media;
			अगर (tulip_media_cap[dev->अगर_port] & MediaIsFD)
				जाओ select_next_media; /* Skip FD entries. */
			अगर (tulip_debug > 1)
				netdev_dbg(dev, "No link beat on media %s, trying transceiver type %s\n",
					   medianame[mleaf->media & MEDIA_MASK],
					   medianame[tp->mtable->mleaf[tp->cur_index].media]);
			tulip_select_media(dev, 0);
			/* Restart the transmit process. */
			tulip_restart_rxtx(tp);
			next_tick = (24*HZ)/10;
			अवरोध;
		पूर्ण
		हाल 1:  हाल 3:		/* 21140, 21142 MII */
		actually_mii:
			अगर (tulip_check_duplex(dev) < 0) अणु
				netअगर_carrier_off(dev);
				next_tick = 3*HZ;
			पूर्ण अन्यथा अणु
				netअगर_carrier_on(dev);
				next_tick = 60*HZ;
			पूर्ण
			अवरोध;
		हाल 2:					/* 21142 serial block has no link beat. */
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अवरोध;
	पूर्ण


	spin_lock_irqsave(&tp->lock, flags);
	अगर (tp->समयout_recovery) अणु
		tulip_tx_समयout_complete(tp, ioaddr);
		tp->समयout_recovery = 0;
	पूर्ण
	spin_unlock_irqrestore(&tp->lock, flags);

	/* mod_समयr synchronizes us with potential add_समयr calls
	 * from पूर्णांकerrupts.
	 */
	mod_समयr(&tp->समयr, RUN_AT(next_tick));
पूर्ण


व्योम mxic_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tulip_निजी *tp = from_समयr(tp, t, समयr);
	काष्ठा net_device *dev = tp->dev;
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक next_tick = 60*HZ;

	अगर (tulip_debug > 3) अणु
		dev_info(&dev->dev, "MXIC negotiation status %08x\n",
			 ioपढ़ो32(ioaddr + CSR12));
	पूर्ण
	अगर (next_tick) अणु
		mod_समयr(&tp->समयr, RUN_AT(next_tick));
	पूर्ण
पूर्ण


व्योम comet_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tulip_निजी *tp = from_समयr(tp, t, समयr);
	काष्ठा net_device *dev = tp->dev;
	पूर्णांक next_tick = 2*HZ;

	अगर (tulip_debug > 1)
		netdev_dbg(dev, "Comet link status %04x partner capability %04x\n",
			   tulip_mdio_पढ़ो(dev, tp->phys[0], 1),
			   tulip_mdio_पढ़ो(dev, tp->phys[0], 5));
	/* mod_समयr synchronizes us with potential add_समयr calls
	 * from पूर्णांकerrupts.
	 */
	अगर (tulip_check_duplex(dev) < 0)
		अणु netअगर_carrier_off(dev); पूर्ण
	अन्यथा
		अणु netअगर_carrier_on(dev); पूर्ण
	mod_समयr(&tp->समयr, RUN_AT(next_tick));
पूर्ण

