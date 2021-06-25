<शैली गुरु>
/*
	drivers/net/ethernet/dec/tulip/pnic.c

	Copyright 2000,2001  The Linux Kernel Team
	Written/copyright 1994-2001 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	Please submit bugs to http://bugzilla.kernel.org/ .
*/

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश "tulip.h"


व्योम pnic_करो_nway(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	u32 phy_reg = ioपढ़ो32(ioaddr + 0xB8);
	u32 new_csr6 = tp->csr6 & ~0x40C40200;

	अगर (phy_reg & 0x78000000) अणु /* Ignore baseT4 */
		अगर (phy_reg & 0x20000000)		dev->अगर_port = 5;
		अन्यथा अगर (phy_reg & 0x40000000)	dev->अगर_port = 3;
		अन्यथा अगर (phy_reg & 0x10000000)	dev->अगर_port = 4;
		अन्यथा अगर (phy_reg & 0x08000000)	dev->अगर_port = 0;
		tp->nwayset = 1;
		new_csr6 = (dev->अगर_port & 1) ? 0x01860000 : 0x00420000;
		ioग_लिखो32(0x32 | (dev->अगर_port & 1), ioaddr + CSR12);
		अगर (dev->अगर_port & 1)
			ioग_लिखो32(0x1F868, ioaddr + 0xB8);
		अगर (phy_reg & 0x30000000) अणु
			tp->full_duplex = 1;
			new_csr6 |= 0x00000200;
		पूर्ण
		अगर (tulip_debug > 1)
			netdev_dbg(dev, "PNIC autonegotiated status %08x, %s\n",
				   phy_reg, medianame[dev->अगर_port]);
		अगर (tp->csr6 != new_csr6) अणु
			tp->csr6 = new_csr6;
			/* Restart Tx */
			tulip_restart_rxtx(tp);
			netअगर_trans_update(dev);
		पूर्ण
	पूर्ण
पूर्ण

व्योम pnic_lnk_change(काष्ठा net_device *dev, पूर्णांक csr5)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक phy_reg = ioपढ़ो32(ioaddr + 0xB8);

	अगर (tulip_debug > 1)
		netdev_dbg(dev, "PNIC link changed state %08x, CSR5 %08x\n",
			   phy_reg, csr5);
	अगर (ioपढ़ो32(ioaddr + CSR5) & TPLnkFail) अणु
		ioग_लिखो32((ioपढ़ो32(ioaddr + CSR7) & ~TPLnkFail) | TPLnkPass, ioaddr + CSR7);
		/* If we use an बाह्यal MII, then we mustn't use the
		 * पूर्णांकernal negotiation.
		 */
		अगर (tulip_media_cap[dev->अगर_port] & MediaIsMII)
			वापस;
		अगर (! tp->nwayset || समय_after(jअगरfies, dev_trans_start(dev) + 1*HZ)) अणु
			tp->csr6 = 0x00420000 | (tp->csr6 & 0x0000fdff);
			ioग_लिखो32(tp->csr6, ioaddr + CSR6);
			ioग_लिखो32(0x30, ioaddr + CSR12);
			ioग_लिखो32(0x0201F078, ioaddr + 0xB8); /* Turn on स्वतःnegotiation. */
			netअगर_trans_update(dev);
		पूर्ण
	पूर्ण अन्यथा अगर (ioपढ़ो32(ioaddr + CSR5) & TPLnkPass) अणु
		अगर (tulip_media_cap[dev->अगर_port] & MediaIsMII) अणु
			spin_lock(&tp->lock);
			tulip_check_duplex(dev);
			spin_unlock(&tp->lock);
		पूर्ण अन्यथा अणु
			pnic_करो_nway(dev);
		पूर्ण
		ioग_लिखो32((ioपढ़ो32(ioaddr + CSR7) & ~TPLnkPass) | TPLnkFail, ioaddr + CSR7);
	पूर्ण
पूर्ण

व्योम pnic_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tulip_निजी *tp = from_समयr(tp, t, समयr);
	काष्ठा net_device *dev = tp->dev;
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक next_tick = 60*HZ;

	अगर(!ioपढ़ो32(ioaddr + CSR7)) अणु
		/* the समयr was called due to a work overflow
		 * in the पूर्णांकerrupt handler. Skip the connection
		 * checks, the nic is definitively speaking with
		 * his link partner.
		 */
		जाओ too_good_connection;
	पूर्ण

	अगर (tulip_media_cap[dev->अगर_port] & MediaIsMII) अणु
		spin_lock_irq(&tp->lock);
		अगर (tulip_check_duplex(dev) > 0)
			next_tick = 3*HZ;
		spin_unlock_irq(&tp->lock);
	पूर्ण अन्यथा अणु
		पूर्णांक csr12 = ioपढ़ो32(ioaddr + CSR12);
		पूर्णांक new_csr6 = tp->csr6 & ~0x40C40200;
		पूर्णांक phy_reg = ioपढ़ो32(ioaddr + 0xB8);
		पूर्णांक csr5 = ioपढ़ो32(ioaddr + CSR5);

		अगर (tulip_debug > 1)
			netdev_dbg(dev, "PNIC timer PHY status %08x, %s CSR5 %08x\n",
				   phy_reg, medianame[dev->अगर_port], csr5);
		अगर (phy_reg & 0x04000000) अणु	/* Remote link fault */
			ioग_लिखो32(0x0201F078, ioaddr + 0xB8);
			next_tick = 1*HZ;
			tp->nwayset = 0;
		पूर्ण अन्यथा अगर (phy_reg & 0x78000000) अणु /* Ignore baseT4 */
			pnic_करो_nway(dev);
			next_tick = 60*HZ;
		पूर्ण अन्यथा अगर (csr5 & TPLnkFail) अणु /* 100baseTx link beat */
			अगर (tulip_debug > 1)
				netdev_dbg(dev, "%s link beat failed, CSR12 %04x, CSR5 %08x, PHY %03x\n",
					   medianame[dev->अगर_port],
					   csr12,
					   ioपढ़ो32(ioaddr + CSR5),
					   ioपढ़ो32(ioaddr + 0xB8));
			next_tick = 3*HZ;
			अगर (tp->medialock) अणु
			पूर्ण अन्यथा अगर (tp->nwayset  &&  (dev->अगर_port & 1)) अणु
				next_tick = 1*HZ;
			पूर्ण अन्यथा अगर (dev->अगर_port == 0) अणु
				dev->अगर_port = 3;
				ioग_लिखो32(0x33, ioaddr + CSR12);
				new_csr6 = 0x01860000;
				ioग_लिखो32(0x1F868, ioaddr + 0xB8);
			पूर्ण अन्यथा अणु
				dev->अगर_port = 0;
				ioग_लिखो32(0x32, ioaddr + CSR12);
				new_csr6 = 0x00420000;
				ioग_लिखो32(0x1F078, ioaddr + 0xB8);
			पूर्ण
			अगर (tp->csr6 != new_csr6) अणु
				tp->csr6 = new_csr6;
				/* Restart Tx */
				tulip_restart_rxtx(tp);
				netअगर_trans_update(dev);
				अगर (tulip_debug > 1)
					dev_info(&dev->dev,
						 "Changing PNIC configuration to %s %s-duplex, CSR6 %08x\n",
						 medianame[dev->अगर_port],
						 tp->full_duplex ? "full" : "half",
						 new_csr6);
			पूर्ण
		पूर्ण
	पूर्ण
too_good_connection:
	mod_समयr(&tp->समयr, RUN_AT(next_tick));
	अगर(!ioपढ़ो32(ioaddr + CSR7)) अणु
		अगर (tulip_debug > 1)
			dev_info(&dev->dev, "sw timer wakeup\n");
		disable_irq(dev->irq);
		tulip_refill_rx(dev);
		enable_irq(dev->irq);
		ioग_लिखो32(tulip_tbl[tp->chip_id].valid_पूर्णांकrs, ioaddr + CSR7);
	पूर्ण
पूर्ण
