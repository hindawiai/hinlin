<शैली गुरु>
/*
	drivers/net/ethernet/dec/tulip/media.c

	Copyright 2000,2001  The Linux Kernel Team
	Written/copyright 1994-2001 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	Please submit bugs to http://bugzilla.kernel.org/ .
*/

#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश "tulip.h"


/* The maximum data घड़ी rate is 2.5 Mhz.  The minimum timing is usually
   met by back-to-back PCI I/O cycles, but we insert a delay to aव्योम
   "overclocking" issues or future 66Mhz PCI. */
#घोषणा mdio_delay() ioपढ़ो32(mdio_addr)

/* Read and ग_लिखो the MII रेजिस्टरs using software-generated serial
   MDIO protocol.  It is just dअगरferent enough from the EEPROM protocol
   to not share code.  The maxium data घड़ी rate is 2.5 Mhz. */
#घोषणा MDIO_SHIFT_CLK		0x10000
#घोषणा MDIO_DATA_WRITE0	0x00000
#घोषणा MDIO_DATA_WRITE1	0x20000
#घोषणा MDIO_ENB		0x00000 /* Ignore the 0x02000 databook setting. */
#घोषणा MDIO_ENB_IN		0x40000
#घोषणा MDIO_DATA_READ		0x80000

अटल स्थिर अचिन्हित अक्षर comet_miireg2offset[32] = अणु
	0xB4, 0xB8, 0xBC, 0xC0,  0xC4, 0xC8, 0xCC, 0,  0,0,0,0,  0,0,0,0,
	0,0xD0,0,0,  0,0,0,0,  0,0,0,0, 0, 0xD4, 0xD8, 0xDC, पूर्ण;


/* MII transceiver control section.
   Read and ग_लिखो the MII रेजिस्टरs using software-generated serial
   MDIO protocol.
   See IEEE 802.3-2002.pdf (Section 2, Chapter "22.2.4 Management functions")
   or DP83840A data sheet क्रम more details.
   */

पूर्णांक tulip_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक i;
	पूर्णांक पढ़ो_cmd = (0xf6 << 10) | ((phy_id & 0x1f) << 5) | location;
	पूर्णांक retval = 0;
	व्योम __iomem *ioaddr = tp->base_addr;
	व्योम __iomem *mdio_addr = ioaddr + CSR9;
	अचिन्हित दीर्घ flags;

	अगर (location & ~0x1f)
		वापस 0xffff;

	अगर (tp->chip_id == COMET  &&  phy_id == 30) अणु
		अगर (comet_miireg2offset[location])
			वापस ioपढ़ो32(ioaddr + comet_miireg2offset[location]);
		वापस 0xffff;
	पूर्ण

	spin_lock_irqsave(&tp->mii_lock, flags);
	अगर (tp->chip_id == LC82C168) अणु
		ioग_लिखो32(0x60020000 + (phy_id<<23) + (location<<18), ioaddr + 0xA0);
		ioपढ़ो32(ioaddr + 0xA0);
		ioपढ़ो32(ioaddr + 0xA0);
		क्रम (i = 1000; i >= 0; --i) अणु
			barrier();
			अगर ( ! ((retval = ioपढ़ो32(ioaddr + 0xA0)) & 0x80000000))
				अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&tp->mii_lock, flags);
		वापस retval & 0xffff;
	पूर्ण

	/* Establish sync by sending at least 32 logic ones. */
	क्रम (i = 32; i >= 0; i--) अणु
		ioग_लिखो32(MDIO_ENB | MDIO_DATA_WRITE1, mdio_addr);
		mdio_delay();
		ioग_लिखो32(MDIO_ENB | MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, mdio_addr);
		mdio_delay();
	पूर्ण
	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 15; i >= 0; i--) अणु
		पूर्णांक dataval = (पढ़ो_cmd & (1 << i)) ? MDIO_DATA_WRITE1 : 0;

		ioग_लिखो32(MDIO_ENB | dataval, mdio_addr);
		mdio_delay();
		ioग_लिखो32(MDIO_ENB | dataval | MDIO_SHIFT_CLK, mdio_addr);
		mdio_delay();
	पूर्ण
	/* Read the two transition, 16 data, and wire-idle bits. */
	क्रम (i = 19; i > 0; i--) अणु
		ioग_लिखो32(MDIO_ENB_IN, mdio_addr);
		mdio_delay();
		retval = (retval << 1) | ((ioपढ़ो32(mdio_addr) & MDIO_DATA_READ) ? 1 : 0);
		ioग_लिखो32(MDIO_ENB_IN | MDIO_SHIFT_CLK, mdio_addr);
		mdio_delay();
	पूर्ण

	spin_unlock_irqrestore(&tp->mii_lock, flags);
	वापस (retval>>1) & 0xffff;
पूर्ण

व्योम tulip_mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक val)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक i;
	पूर्णांक cmd = (0x5002 << 16) | ((phy_id & 0x1f) << 23) | (location<<18) | (val & 0xffff);
	व्योम __iomem *ioaddr = tp->base_addr;
	व्योम __iomem *mdio_addr = ioaddr + CSR9;
	अचिन्हित दीर्घ flags;

	अगर (location & ~0x1f)
		वापस;

	अगर (tp->chip_id == COMET && phy_id == 30) अणु
		अगर (comet_miireg2offset[location])
			ioग_लिखो32(val, ioaddr + comet_miireg2offset[location]);
		वापस;
	पूर्ण

	spin_lock_irqsave(&tp->mii_lock, flags);
	अगर (tp->chip_id == LC82C168) अणु
		ioग_लिखो32(cmd, ioaddr + 0xA0);
		क्रम (i = 1000; i >= 0; --i) अणु
			barrier();
			अगर ( ! (ioपढ़ो32(ioaddr + 0xA0) & 0x80000000))
				अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&tp->mii_lock, flags);
		वापस;
	पूर्ण

	/* Establish sync by sending 32 logic ones. */
	क्रम (i = 32; i >= 0; i--) अणु
		ioग_लिखो32(MDIO_ENB | MDIO_DATA_WRITE1, mdio_addr);
		mdio_delay();
		ioग_लिखो32(MDIO_ENB | MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, mdio_addr);
		mdio_delay();
	पूर्ण
	/* Shअगरt the command bits out. */
	क्रम (i = 31; i >= 0; i--) अणु
		पूर्णांक dataval = (cmd & (1 << i)) ? MDIO_DATA_WRITE1 : 0;
		ioग_लिखो32(MDIO_ENB | dataval, mdio_addr);
		mdio_delay();
		ioग_लिखो32(MDIO_ENB | dataval | MDIO_SHIFT_CLK, mdio_addr);
		mdio_delay();
	पूर्ण
	/* Clear out extra bits. */
	क्रम (i = 2; i > 0; i--) अणु
		ioग_लिखो32(MDIO_ENB_IN, mdio_addr);
		mdio_delay();
		ioग_लिखो32(MDIO_ENB_IN | MDIO_SHIFT_CLK, mdio_addr);
		mdio_delay();
	पूर्ण

	spin_unlock_irqrestore(&tp->mii_lock, flags);
पूर्ण


/* Set up the transceiver control रेजिस्टरs क्रम the selected media type. */
व्योम tulip_select_media(काष्ठा net_device *dev, पूर्णांक startup)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	काष्ठा mediatable *mtable = tp->mtable;
	u32 new_csr6;
	पूर्णांक i;

	अगर (mtable) अणु
		काष्ठा medialeaf *mleaf = &mtable->mleaf[tp->cur_index];
		अचिन्हित अक्षर *p = mleaf->leafdata;
		चयन (mleaf->type) अणु
		हाल 0:					/* 21140 non-MII xcvr. */
			अगर (tulip_debug > 1)
				netdev_dbg(dev, "Using a 21140 non-MII transceiver with control setting %02x\n",
					   p[1]);
			dev->अगर_port = p[0];
			अगर (startup)
				ioग_लिखो32(mtable->csr12dir | 0x100, ioaddr + CSR12);
			ioग_लिखो32(p[1], ioaddr + CSR12);
			new_csr6 = 0x02000000 | ((p[2] & 0x71) << 18);
			अवरोध;
		हाल 2: हाल 4: अणु
			u16 setup[5];
			u32 csr13val, csr14val, csr15dir, csr15val;
			क्रम (i = 0; i < 5; i++)
				setup[i] = get_u16(&p[i*2 + 1]);

			dev->अगर_port = p[0] & MEDIA_MASK;
			अगर (tulip_media_cap[dev->अगर_port] & MediaAlwaysFD)
				tp->full_duplex = 1;

			अगर (startup && mtable->has_reset) अणु
				काष्ठा medialeaf *rleaf = &mtable->mleaf[mtable->has_reset];
				अचिन्हित अक्षर *rst = rleaf->leafdata;
				अगर (tulip_debug > 1)
					netdev_dbg(dev, "Resetting the transceiver\n");
				क्रम (i = 0; i < rst[0]; i++)
					ioग_लिखो32(get_u16(rst + 1 + (i<<1)) << 16, ioaddr + CSR15);
			पूर्ण
			अगर (tulip_debug > 1)
				netdev_dbg(dev, "21143 non-MII %s transceiver control %04x/%04x\n",
					   medianame[dev->अगर_port],
					   setup[0], setup[1]);
			अगर (p[0] & 0x40) अणु	/* SIA (CSR13-15) setup values are provided. */
				csr13val = setup[0];
				csr14val = setup[1];
				csr15dir = (setup[3]<<16) | setup[2];
				csr15val = (setup[4]<<16) | setup[2];
				ioग_लिखो32(0, ioaddr + CSR13);
				ioग_लिखो32(csr14val, ioaddr + CSR14);
				ioग_लिखो32(csr15dir, ioaddr + CSR15);	/* Direction */
				ioग_लिखो32(csr15val, ioaddr + CSR15);	/* Data */
				ioग_लिखो32(csr13val, ioaddr + CSR13);
			पूर्ण अन्यथा अणु
				csr13val = 1;
				csr14val = 0;
				csr15dir = (setup[0]<<16) | 0x0008;
				csr15val = (setup[1]<<16) | 0x0008;
				अगर (dev->अगर_port <= 4)
					csr14val = t21142_csr14[dev->अगर_port];
				अगर (startup) अणु
					ioग_लिखो32(0, ioaddr + CSR13);
					ioग_लिखो32(csr14val, ioaddr + CSR14);
				पूर्ण
				ioग_लिखो32(csr15dir, ioaddr + CSR15);	/* Direction */
				ioग_लिखो32(csr15val, ioaddr + CSR15);	/* Data */
				अगर (startup) ioग_लिखो32(csr13val, ioaddr + CSR13);
			पूर्ण
			अगर (tulip_debug > 1)
				netdev_dbg(dev, "Setting CSR15 to %08x/%08x\n",
					   csr15dir, csr15val);
			अगर (mleaf->type == 4)
				new_csr6 = 0x82020000 | ((setup[2] & 0x71) << 18);
			अन्यथा
				new_csr6 = 0x82420000;
			अवरोध;
		पूर्ण
		हाल 1: हाल 3: अणु
			पूर्णांक phy_num = p[0];
			पूर्णांक init_length = p[1];
			u16 *misc_info, पंचांगp_info;

			dev->अगर_port = 11;
			new_csr6 = 0x020E0000;
			अगर (mleaf->type == 3) अणु	/* 21142 */
				u16 *init_sequence = (u16*)(p+2);
				u16 *reset_sequence = &((u16*)(p+3))[init_length];
				पूर्णांक reset_length = p[2 + init_length*2];
				misc_info = reset_sequence + reset_length;
				अगर (startup) अणु
					पूर्णांक समयout = 10;	/* max 1 ms */
					क्रम (i = 0; i < reset_length; i++)
						ioग_लिखो32(get_u16(&reset_sequence[i]) << 16, ioaddr + CSR15);

					/* flush posted ग_लिखोs */
					ioपढ़ो32(ioaddr + CSR15);

					/* Sect 3.10.3 in DP83840A.pdf (p39) */
					udelay(500);

					/* Section 4.2 in DP83840A.pdf (p43) */
					/* and IEEE 802.3 "22.2.4.1.1 Reset" */
					जबतक (समयout-- &&
						(tulip_mdio_पढ़ो (dev, phy_num, MII_BMCR) & BMCR_RESET))
						udelay(100);
				पूर्ण
				क्रम (i = 0; i < init_length; i++)
					ioग_लिखो32(get_u16(&init_sequence[i]) << 16, ioaddr + CSR15);

				ioपढ़ो32(ioaddr + CSR15);	/* flush posted ग_लिखोs */
			पूर्ण अन्यथा अणु
				u8 *init_sequence = p + 2;
				u8 *reset_sequence = p + 3 + init_length;
				पूर्णांक reset_length = p[2 + init_length];
				misc_info = (u16*)(reset_sequence + reset_length);
				अगर (startup) अणु
					पूर्णांक समयout = 10;	/* max 1 ms */
					ioग_लिखो32(mtable->csr12dir | 0x100, ioaddr + CSR12);
					क्रम (i = 0; i < reset_length; i++)
						ioग_लिखो32(reset_sequence[i], ioaddr + CSR12);

					/* flush posted ग_लिखोs */
					ioपढ़ो32(ioaddr + CSR12);

					/* Sect 3.10.3 in DP83840A.pdf (p39) */
					udelay(500);

					/* Section 4.2 in DP83840A.pdf (p43) */
					/* and IEEE 802.3 "22.2.4.1.1 Reset" */
					जबतक (समयout-- &&
						(tulip_mdio_पढ़ो (dev, phy_num, MII_BMCR) & BMCR_RESET))
						udelay(100);
				पूर्ण
				क्रम (i = 0; i < init_length; i++)
					ioग_लिखो32(init_sequence[i], ioaddr + CSR12);

				ioपढ़ो32(ioaddr + CSR12);	/* flush posted ग_लिखोs */
			पूर्ण

			पंचांगp_info = get_u16(&misc_info[1]);
			अगर (पंचांगp_info)
				tp->advertising[phy_num] = पंचांगp_info | 1;
			अगर (पंचांगp_info && startup < 2) अणु
				अगर (tp->mii_advertise == 0)
					tp->mii_advertise = tp->advertising[phy_num];
				अगर (tulip_debug > 1)
					netdev_dbg(dev, " Advertising %04x on MII %d\n",
						   tp->mii_advertise,
						   tp->phys[phy_num]);
				tulip_mdio_ग_लिखो(dev, tp->phys[phy_num], 4, tp->mii_advertise);
			पूर्ण
			अवरोध;
		पूर्ण
		हाल 5: हाल 6: अणु
			new_csr6 = 0; /* FIXME */

			अगर (startup && mtable->has_reset) अणु
				काष्ठा medialeaf *rleaf = &mtable->mleaf[mtable->has_reset];
				अचिन्हित अक्षर *rst = rleaf->leafdata;
				अगर (tulip_debug > 1)
					netdev_dbg(dev, "Resetting the transceiver\n");
				क्रम (i = 0; i < rst[0]; i++)
					ioग_लिखो32(get_u16(rst + 1 + (i<<1)) << 16, ioaddr + CSR15);
			पूर्ण

			अवरोध;
		पूर्ण
		शेष:
			netdev_dbg(dev, " Invalid media table selection %d\n",
				   mleaf->type);
			new_csr6 = 0x020E0000;
		पूर्ण
		अगर (tulip_debug > 1)
			netdev_dbg(dev, "Using media type %s, CSR12 is %02x\n",
				   medianame[dev->अगर_port],
				   ioपढ़ो32(ioaddr + CSR12) & 0xff);
	पूर्ण अन्यथा अगर (tp->chip_id == LC82C168) अणु
		अगर (startup && ! tp->medialock)
			dev->अगर_port = tp->mii_cnt ? 11 : 0;
		अगर (tulip_debug > 1)
			netdev_dbg(dev, "PNIC PHY status is %3.3x, media %s\n",
				   ioपढ़ो32(ioaddr + 0xB8),
				   medianame[dev->अगर_port]);
		अगर (tp->mii_cnt) अणु
			new_csr6 = 0x810C0000;
			ioग_लिखो32(0x0001, ioaddr + CSR15);
			ioग_लिखो32(0x0201B07A, ioaddr + 0xB8);
		पूर्ण अन्यथा अगर (startup) अणु
			/* Start with 10mbps to करो स्वतःnegotiation. */
			ioग_लिखो32(0x32, ioaddr + CSR12);
			new_csr6 = 0x00420000;
			ioग_लिखो32(0x0001B078, ioaddr + 0xB8);
			ioग_लिखो32(0x0201B078, ioaddr + 0xB8);
		पूर्ण अन्यथा अगर (dev->अगर_port == 3  ||  dev->अगर_port == 5) अणु
			ioग_लिखो32(0x33, ioaddr + CSR12);
			new_csr6 = 0x01860000;
			/* Trigger स्वतःnegotiation. */
			ioग_लिखो32(startup ? 0x0201F868 : 0x0001F868, ioaddr + 0xB8);
		पूर्ण अन्यथा अणु
			ioग_लिखो32(0x32, ioaddr + CSR12);
			new_csr6 = 0x00420000;
			ioग_लिखो32(0x1F078, ioaddr + 0xB8);
		पूर्ण
	पूर्ण अन्यथा अणु					/* Unknown chip type with no media table. */
		अगर (tp->शेष_port == 0)
			dev->अगर_port = tp->mii_cnt ? 11 : 3;
		अगर (tulip_media_cap[dev->अगर_port] & MediaIsMII) अणु
			new_csr6 = 0x020E0000;
		पूर्ण अन्यथा अगर (tulip_media_cap[dev->अगर_port] & MediaIsFx) अणु
			new_csr6 = 0x02860000;
		पूर्ण अन्यथा
			new_csr6 = 0x03860000;
		अगर (tulip_debug > 1)
			netdev_dbg(dev, "No media description table, assuming %s transceiver, CSR12 %02x\n",
				   medianame[dev->अगर_port],
				   ioपढ़ो32(ioaddr + CSR12));
	पूर्ण

	tp->csr6 = new_csr6 | (tp->csr6 & 0xfdff) | (tp->full_duplex ? 0x0200 : 0);

	mdelay(1);
पूर्ण

/*
  Check the MII negotiated duplex and change the CSR6 setting अगर
  required.
  Return 0 अगर everything is OK.
  Return < 0 अगर the transceiver is missing or has no link beat.
  */
पूर्णांक tulip_check_duplex(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	अचिन्हित पूर्णांक bmsr, lpa, negotiated, new_csr6;

	bmsr = tulip_mdio_पढ़ो(dev, tp->phys[0], MII_BMSR);
	lpa = tulip_mdio_पढ़ो(dev, tp->phys[0], MII_LPA);
	अगर (tulip_debug > 1)
		dev_info(&dev->dev, "MII status %04x, Link partner report %04x\n",
			 bmsr, lpa);
	अगर (bmsr == 0xffff)
		वापस -2;
	अगर ((bmsr & BMSR_LSTATUS) == 0) अणु
		पूर्णांक new_bmsr = tulip_mdio_पढ़ो(dev, tp->phys[0], MII_BMSR);
		अगर ((new_bmsr & BMSR_LSTATUS) == 0) अणु
			अगर (tulip_debug  > 1)
				dev_info(&dev->dev,
					 "No link beat on the MII interface, status %04x\n",
					 new_bmsr);
			वापस -1;
		पूर्ण
	पूर्ण
	negotiated = lpa & tp->advertising[0];
	tp->full_duplex = mii_duplex(tp->full_duplex_lock, negotiated);

	new_csr6 = tp->csr6;

	अगर (negotiated & LPA_100) new_csr6 &= ~TxThreshold;
	अन्यथा			  new_csr6 |= TxThreshold;
	अगर (tp->full_duplex) new_csr6 |= FullDuplex;
	अन्यथा		     new_csr6 &= ~FullDuplex;

	अगर (new_csr6 != tp->csr6) अणु
		tp->csr6 = new_csr6;
		tulip_restart_rxtx(tp);

		अगर (tulip_debug > 0)
			dev_info(&dev->dev,
				 "Setting %s-duplex based on MII#%d link partner capability of %04x\n",
				 tp->full_duplex ? "full" : "half",
				 tp->phys[0], lpa);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम tulip_find_mii(काष्ठा net_device *dev, पूर्णांक board_idx)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक phyn, phy_idx = 0;
	पूर्णांक mii_reg0;
	पूर्णांक mii_advert;
	अचिन्हित पूर्णांक to_advert, new_bmcr, ane_चयन;

	/* Find the connected MII xcvrs.
	   Doing this in खोलो() would allow detecting बाह्यal xcvrs later,
	   but takes much समय. */
	क्रम (phyn = 1; phyn <= 32 && phy_idx < ARRAY_SIZE(tp->phys); phyn++) अणु
		पूर्णांक phy = phyn & 0x1f;
		पूर्णांक mii_status = tulip_mdio_पढ़ो (dev, phy, MII_BMSR);
		अगर ((mii_status & 0x8301) == 0x8001 ||
		    ((mii_status & BMSR_100BASE4) == 0 &&
		     (mii_status & 0x7800) != 0)) अणु
			/* preserve Becker logic, gain indentation level */
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण

		mii_reg0 = tulip_mdio_पढ़ो (dev, phy, MII_BMCR);
		mii_advert = tulip_mdio_पढ़ो (dev, phy, MII_ADVERTISE);
		ane_चयन = 0;

		/* अगर not advertising at all, gen an
		 * advertising value from the capability
		 * bits in BMSR
		 */
		अगर ((mii_advert & ADVERTISE_ALL) == 0) अणु
			अचिन्हित पूर्णांक पंचांगpadv = tulip_mdio_पढ़ो (dev, phy, MII_BMSR);
			mii_advert = ((पंचांगpadv >> 6) & 0x3e0) | 1;
		पूर्ण

		अगर (tp->mii_advertise) अणु
			tp->advertising[phy_idx] =
			to_advert = tp->mii_advertise;
		पूर्ण अन्यथा अगर (tp->advertising[phy_idx]) अणु
			to_advert = tp->advertising[phy_idx];
		पूर्ण अन्यथा अणु
			tp->advertising[phy_idx] =
			tp->mii_advertise =
			to_advert = mii_advert;
		पूर्ण

		tp->phys[phy_idx++] = phy;

		pr_info("tulip%d:  MII transceiver #%d config %04x status %04x advertising %04x\n",
			board_idx, phy, mii_reg0, mii_status, mii_advert);

		/* Fixup क्रम DLink with miswired PHY. */
		अगर (mii_advert != to_advert) अणु
			pr_debug("tulip%d:  Advertising %04x on PHY %d, previously advertising %04x\n",
				 board_idx, to_advert, phy, mii_advert);
			tulip_mdio_ग_लिखो (dev, phy, 4, to_advert);
		पूर्ण

		/* Enable स्वतःnegotiation: some boards शेष to off. */
		अगर (tp->शेष_port == 0) अणु
			new_bmcr = mii_reg0 | BMCR_ANENABLE;
			अगर (new_bmcr != mii_reg0) अणु
				new_bmcr |= BMCR_ANRESTART;
				ane_चयन = 1;
			पूर्ण
		पूर्ण
		/* ...or disable nway, अगर क्रमcing media */
		अन्यथा अणु
			new_bmcr = mii_reg0 & ~BMCR_ANENABLE;
			अगर (new_bmcr != mii_reg0)
				ane_चयन = 1;
		पूर्ण

		/* clear out bits we never want at this poपूर्णांक */
		new_bmcr &= ~(BMCR_CTST | BMCR_FULLDPLX | BMCR_ISOLATE |
			      BMCR_PDOWN | BMCR_SPEED100 | BMCR_LOOPBACK |
			      BMCR_RESET);

		अगर (tp->full_duplex)
			new_bmcr |= BMCR_FULLDPLX;
		अगर (tulip_media_cap[tp->शेष_port] & MediaIs100)
			new_bmcr |= BMCR_SPEED100;

		अगर (new_bmcr != mii_reg0) अणु
			/* some phys need the ANE चयन to
			 * happen beक्रमe क्रमced media settings
			 * will "take."  However, we ग_लिखो the
			 * same value twice in order not to
			 * confuse the sane phys.
			 */
			अगर (ane_चयन) अणु
				tulip_mdio_ग_लिखो (dev, phy, MII_BMCR, new_bmcr);
				udelay (10);
			पूर्ण
			tulip_mdio_ग_लिखो (dev, phy, MII_BMCR, new_bmcr);
		पूर्ण
	पूर्ण
	tp->mii_cnt = phy_idx;
	अगर (tp->mtable && tp->mtable->has_mii && phy_idx == 0) अणु
		pr_info("tulip%d: ***WARNING***: No MII transceiver found!\n",
			board_idx);
		tp->phys[0] = 1;
	पूर्ण
पूर्ण
