<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PHY drivers क्रम the sungem ethernet driver.
 *
 * This file could be shared with other drivers.
 *
 * (c) 2002-2007, Benjamin Herrenscmidt (benh@kernel.crashing.org)
 *
 * TODO:
 *  - Add support क्रम PHYs that provide an IRQ line
 *  - Eventually moved the entire polling state machine in
 *    there (out of the eth driver), so that it can easily be
 *    skipped on PHYs that implement it in hardware.
 *  - On LXT971 & BCM5201, Apple uses some chip specअगरic regs
 *    to पढ़ो the link status. Figure out why and अगर it makes
 *    sense to करो the same (magic aneg ?)
 *  - Apple has some additional घातer management code क्रम some
 *    Broadcom PHYs that they "hide" from the OpenSource version
 *    of darwin, still need to reverse engineer that
 */


#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/delay.h>

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

#समावेश <linux/sungem_phy.h>

/* Link modes of the BCM5400 PHY */
अटल स्थिर पूर्णांक phy_BCM5400_link_table[8][3] = अणु
	अणु 0, 0, 0 पूर्ण,	/* No link */
	अणु 0, 0, 0 पूर्ण,	/* 10BT Half Duplex */
	अणु 1, 0, 0 पूर्ण,	/* 10BT Full Duplex */
	अणु 0, 1, 0 पूर्ण,	/* 100BT Half Duplex */
	अणु 0, 1, 0 पूर्ण,	/* 100BT Half Duplex */
	अणु 1, 1, 0 पूर्ण,	/* 100BT Full Duplex*/
	अणु 1, 0, 1 पूर्ण,	/* 1000BT */
	अणु 1, 0, 1 पूर्ण,	/* 1000BT */
पूर्ण;

अटल अंतरभूत पूर्णांक __sungem_phy_पढ़ो(काष्ठा mii_phy* phy, पूर्णांक id, पूर्णांक reg)
अणु
	वापस phy->mdio_पढ़ो(phy->dev, id, reg);
पूर्ण

अटल अंतरभूत व्योम __sungem_phy_ग_लिखो(काष्ठा mii_phy* phy, पूर्णांक id, पूर्णांक reg, पूर्णांक val)
अणु
	phy->mdio_ग_लिखो(phy->dev, id, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक sungem_phy_पढ़ो(काष्ठा mii_phy* phy, पूर्णांक reg)
अणु
	वापस phy->mdio_पढ़ो(phy->dev, phy->mii_id, reg);
पूर्ण

अटल अंतरभूत व्योम sungem_phy_ग_लिखो(काष्ठा mii_phy* phy, पूर्णांक reg, पूर्णांक val)
अणु
	phy->mdio_ग_लिखो(phy->dev, phy->mii_id, reg, val);
पूर्ण

अटल पूर्णांक reset_one_mii_phy(काष्ठा mii_phy* phy, पूर्णांक phy_id)
अणु
	u16 val;
	पूर्णांक limit = 10000;

	val = __sungem_phy_पढ़ो(phy, phy_id, MII_BMCR);
	val &= ~(BMCR_ISOLATE | BMCR_PDOWN);
	val |= BMCR_RESET;
	__sungem_phy_ग_लिखो(phy, phy_id, MII_BMCR, val);

	udelay(100);

	जबतक (--limit) अणु
		val = __sungem_phy_पढ़ो(phy, phy_id, MII_BMCR);
		अगर ((val & BMCR_RESET) == 0)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर ((val & BMCR_ISOLATE) && limit > 0)
		__sungem_phy_ग_लिखो(phy, phy_id, MII_BMCR, val & ~BMCR_ISOLATE);

	वापस limit <= 0;
पूर्ण

अटल पूर्णांक bcm5201_init(काष्ठा mii_phy* phy)
अणु
	u16 data;

	data = sungem_phy_पढ़ो(phy, MII_BCM5201_MULTIPHY);
	data &= ~MII_BCM5201_MULTIPHY_SUPERISOLATE;
	sungem_phy_ग_लिखो(phy, MII_BCM5201_MULTIPHY, data);

	sungem_phy_ग_लिखो(phy, MII_BCM5201_INTERRUPT, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5201_suspend(काष्ठा mii_phy* phy)
अणु
	sungem_phy_ग_लिखो(phy, MII_BCM5201_INTERRUPT, 0);
	sungem_phy_ग_लिखो(phy, MII_BCM5201_MULTIPHY, MII_BCM5201_MULTIPHY_SUPERISOLATE);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5221_init(काष्ठा mii_phy* phy)
अणु
	u16 data;

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_TEST);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_TEST,
		data | MII_BCM5221_TEST_ENABLE_SHADOWS);

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_SHDOW_AUX_STAT2);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_SHDOW_AUX_STAT2,
		data | MII_BCM5221_SHDOW_AUX_STAT2_APD);

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_SHDOW_AUX_MODE4);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_SHDOW_AUX_MODE4,
		data | MII_BCM5221_SHDOW_AUX_MODE4_CLKLOPWR);

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_TEST);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_TEST,
		data & ~MII_BCM5221_TEST_ENABLE_SHADOWS);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5221_suspend(काष्ठा mii_phy* phy)
अणु
	u16 data;

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_TEST);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_TEST,
		data | MII_BCM5221_TEST_ENABLE_SHADOWS);

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_SHDOW_AUX_MODE4);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_SHDOW_AUX_MODE4,
		  data | MII_BCM5221_SHDOW_AUX_MODE4_IDDQMODE);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5241_init(काष्ठा mii_phy* phy)
अणु
	u16 data;

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_TEST);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_TEST,
		data | MII_BCM5221_TEST_ENABLE_SHADOWS);

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_SHDOW_AUX_STAT2);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_SHDOW_AUX_STAT2,
		data | MII_BCM5221_SHDOW_AUX_STAT2_APD);

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_SHDOW_AUX_MODE4);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_SHDOW_AUX_MODE4,
		data & ~MII_BCM5241_SHDOW_AUX_MODE4_STANDBYPWR);

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_TEST);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_TEST,
		data & ~MII_BCM5221_TEST_ENABLE_SHADOWS);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5241_suspend(काष्ठा mii_phy* phy)
अणु
	u16 data;

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_TEST);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_TEST,
		data | MII_BCM5221_TEST_ENABLE_SHADOWS);

	data = sungem_phy_पढ़ो(phy, MII_BCM5221_SHDOW_AUX_MODE4);
	sungem_phy_ग_लिखो(phy, MII_BCM5221_SHDOW_AUX_MODE4,
		  data | MII_BCM5241_SHDOW_AUX_MODE4_STANDBYPWR);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5400_init(काष्ठा mii_phy* phy)
अणु
	u16 data;

	/* Configure क्रम gigabit full duplex */
	data = sungem_phy_पढ़ो(phy, MII_BCM5400_AUXCONTROL);
	data |= MII_BCM5400_AUXCONTROL_PWR10BASET;
	sungem_phy_ग_लिखो(phy, MII_BCM5400_AUXCONTROL, data);

	data = sungem_phy_पढ़ो(phy, MII_BCM5400_GB_CONTROL);
	data |= MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP;
	sungem_phy_ग_लिखो(phy, MII_BCM5400_GB_CONTROL, data);

	udelay(100);

	/* Reset and configure cascaded 10/100 PHY */
	(व्योम)reset_one_mii_phy(phy, 0x1f);

	data = __sungem_phy_पढ़ो(phy, 0x1f, MII_BCM5201_MULTIPHY);
	data |= MII_BCM5201_MULTIPHY_SERIALMODE;
	__sungem_phy_ग_लिखो(phy, 0x1f, MII_BCM5201_MULTIPHY, data);

	data = sungem_phy_पढ़ो(phy, MII_BCM5400_AUXCONTROL);
	data &= ~MII_BCM5400_AUXCONTROL_PWR10BASET;
	sungem_phy_ग_लिखो(phy, MII_BCM5400_AUXCONTROL, data);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5400_suspend(काष्ठा mii_phy* phy)
अणु
#अगर 0 /* Commented out in Darwin... someone has those dawn करोcs ? */
	sungem_phy_ग_लिखो(phy, MII_BMCR, BMCR_PDOWN);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक bcm5401_init(काष्ठा mii_phy* phy)
अणु
	u16 data;
	पूर्णांक rev;

	rev = sungem_phy_पढ़ो(phy, MII_PHYSID2) & 0x000f;
	अगर (rev == 0 || rev == 3) अणु
		/* Some revisions of 5401 appear to need this
		 * initialisation sequence to disable, according
		 * to OF, "tap power management"
		 *
		 * WARNING ! OF and Darwin करोn't agree on the
		 * रेजिस्टर addresses. OF seem to पूर्णांकerpret the
		 * रेजिस्टर numbers below as decimal
		 *
		 * Note: This should (and करोes) match tg3_init_5401phy_dsp
		 *       in the tg3.c driver. -DaveM
		 */
		sungem_phy_ग_लिखो(phy, 0x18, 0x0c20);
		sungem_phy_ग_लिखो(phy, 0x17, 0x0012);
		sungem_phy_ग_लिखो(phy, 0x15, 0x1804);
		sungem_phy_ग_लिखो(phy, 0x17, 0x0013);
		sungem_phy_ग_लिखो(phy, 0x15, 0x1204);
		sungem_phy_ग_लिखो(phy, 0x17, 0x8006);
		sungem_phy_ग_लिखो(phy, 0x15, 0x0132);
		sungem_phy_ग_लिखो(phy, 0x17, 0x8006);
		sungem_phy_ग_लिखो(phy, 0x15, 0x0232);
		sungem_phy_ग_लिखो(phy, 0x17, 0x201f);
		sungem_phy_ग_लिखो(phy, 0x15, 0x0a20);
	पूर्ण

	/* Configure क्रम gigabit full duplex */
	data = sungem_phy_पढ़ो(phy, MII_BCM5400_GB_CONTROL);
	data |= MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP;
	sungem_phy_ग_लिखो(phy, MII_BCM5400_GB_CONTROL, data);

	udelay(10);

	/* Reset and configure cascaded 10/100 PHY */
	(व्योम)reset_one_mii_phy(phy, 0x1f);

	data = __sungem_phy_पढ़ो(phy, 0x1f, MII_BCM5201_MULTIPHY);
	data |= MII_BCM5201_MULTIPHY_SERIALMODE;
	__sungem_phy_ग_लिखो(phy, 0x1f, MII_BCM5201_MULTIPHY, data);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5401_suspend(काष्ठा mii_phy* phy)
अणु
#अगर 0 /* Commented out in Darwin... someone has those dawn करोcs ? */
	sungem_phy_ग_लिखो(phy, MII_BMCR, BMCR_PDOWN);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक bcm5411_init(काष्ठा mii_phy* phy)
अणु
	u16 data;

	/* Here's some more Apple black magic to setup
	 * some voltage stuffs.
	 */
	sungem_phy_ग_लिखो(phy, 0x1c, 0x8c23);
	sungem_phy_ग_लिखो(phy, 0x1c, 0x8ca3);
	sungem_phy_ग_लिखो(phy, 0x1c, 0x8c23);

	/* Here, Apple seems to want to reset it, करो
	 * it as well
	 */
	sungem_phy_ग_लिखो(phy, MII_BMCR, BMCR_RESET);
	sungem_phy_ग_लिखो(phy, MII_BMCR, 0x1340);

	data = sungem_phy_पढ़ो(phy, MII_BCM5400_GB_CONTROL);
	data |= MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP;
	sungem_phy_ग_लिखो(phy, MII_BCM5400_GB_CONTROL, data);

	udelay(10);

	/* Reset and configure cascaded 10/100 PHY */
	(व्योम)reset_one_mii_phy(phy, 0x1f);

	वापस 0;
पूर्ण

अटल पूर्णांक genmii_setup_aneg(काष्ठा mii_phy *phy, u32 advertise)
अणु
	u16 ctl, adv;

	phy->स्वतःneg = 1;
	phy->speed = SPEED_10;
	phy->duplex = DUPLEX_HALF;
	phy->छोड़ो = 0;
	phy->advertising = advertise;

	/* Setup standard advertise */
	adv = sungem_phy_पढ़ो(phy, MII_ADVERTISE);
	adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
	अगर (advertise & ADVERTISED_10baseT_Half)
		adv |= ADVERTISE_10HALF;
	अगर (advertise & ADVERTISED_10baseT_Full)
		adv |= ADVERTISE_10FULL;
	अगर (advertise & ADVERTISED_100baseT_Half)
		adv |= ADVERTISE_100HALF;
	अगर (advertise & ADVERTISED_100baseT_Full)
		adv |= ADVERTISE_100FULL;
	sungem_phy_ग_लिखो(phy, MII_ADVERTISE, adv);

	/* Start/Restart aneg */
	ctl = sungem_phy_पढ़ो(phy, MII_BMCR);
	ctl |= (BMCR_ANENABLE | BMCR_ANRESTART);
	sungem_phy_ग_लिखो(phy, MII_BMCR, ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक genmii_setup_क्रमced(काष्ठा mii_phy *phy, पूर्णांक speed, पूर्णांक fd)
अणु
	u16 ctl;

	phy->स्वतःneg = 0;
	phy->speed = speed;
	phy->duplex = fd;
	phy->छोड़ो = 0;

	ctl = sungem_phy_पढ़ो(phy, MII_BMCR);
	ctl &= ~(BMCR_FULLDPLX|BMCR_SPEED100|BMCR_ANENABLE);

	/* First reset the PHY */
	sungem_phy_ग_लिखो(phy, MII_BMCR, ctl | BMCR_RESET);

	/* Select speed & duplex */
	चयन(speed) अणु
	हाल SPEED_10:
		अवरोध;
	हाल SPEED_100:
		ctl |= BMCR_SPEED100;
		अवरोध;
	हाल SPEED_1000:
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (fd == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;
	sungem_phy_ग_लिखो(phy, MII_BMCR, ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक genmii_poll_link(काष्ठा mii_phy *phy)
अणु
	u16 status;

	(व्योम)sungem_phy_पढ़ो(phy, MII_BMSR);
	status = sungem_phy_पढ़ो(phy, MII_BMSR);
	अगर ((status & BMSR_LSTATUS) == 0)
		वापस 0;
	अगर (phy->स्वतःneg && !(status & BMSR_ANEGCOMPLETE))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक genmii_पढ़ो_link(काष्ठा mii_phy *phy)
अणु
	u16 lpa;

	अगर (phy->स्वतःneg) अणु
		lpa = sungem_phy_पढ़ो(phy, MII_LPA);

		अगर (lpa & (LPA_10FULL | LPA_100FULL))
			phy->duplex = DUPLEX_FULL;
		अन्यथा
			phy->duplex = DUPLEX_HALF;
		अगर (lpa & (LPA_100FULL | LPA_100HALF))
			phy->speed = SPEED_100;
		अन्यथा
			phy->speed = SPEED_10;
		phy->छोड़ो = 0;
	पूर्ण
	/* On non-aneg, we assume what we put in BMCR is the speed,
	 * though magic-aneg shouldn't prevent this हाल from occurring
	 */

	 वापस 0;
पूर्ण

अटल पूर्णांक generic_suspend(काष्ठा mii_phy* phy)
अणु
	sungem_phy_ग_लिखो(phy, MII_BMCR, BMCR_PDOWN);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5421_init(काष्ठा mii_phy* phy)
अणु
	u16 data;
	अचिन्हित पूर्णांक id;

	id = (sungem_phy_पढ़ो(phy, MII_PHYSID1) << 16 | sungem_phy_पढ़ो(phy, MII_PHYSID2));

	/* Revision 0 of 5421 needs some fixups */
	अगर (id == 0x002060e0) अणु
		/* This is borrowed from MacOS
		 */
		sungem_phy_ग_लिखो(phy, 0x18, 0x1007);
		data = sungem_phy_पढ़ो(phy, 0x18);
		sungem_phy_ग_लिखो(phy, 0x18, data | 0x0400);
		sungem_phy_ग_लिखो(phy, 0x18, 0x0007);
		data = sungem_phy_पढ़ो(phy, 0x18);
		sungem_phy_ग_लिखो(phy, 0x18, data | 0x0800);
		sungem_phy_ग_लिखो(phy, 0x17, 0x000a);
		data = sungem_phy_पढ़ो(phy, 0x15);
		sungem_phy_ग_लिखो(phy, 0x15, data | 0x0200);
	पूर्ण

	/* Pick up some init code from OF क्रम K2 version */
	अगर ((id & 0xfffffff0) == 0x002062e0) अणु
		sungem_phy_ग_लिखो(phy, 4, 0x01e1);
		sungem_phy_ग_लिखो(phy, 9, 0x0300);
	पूर्ण

	/* Check अगर we can enable स्वतःmatic low घातer */
#अगर_घोषित CONFIG_PPC_PMAC
	अगर (phy->platक्रमm_data) अणु
		काष्ठा device_node *np = of_get_parent(phy->platक्रमm_data);
		पूर्णांक can_low_घातer = 1;
		अगर (np == शून्य || of_get_property(np, "no-autolowpower", शून्य))
			can_low_घातer = 0;
		अगर (can_low_घातer) अणु
			/* Enable स्वतःmatic low-घातer */
			sungem_phy_ग_लिखो(phy, 0x1c, 0x9002);
			sungem_phy_ग_लिखो(phy, 0x1c, 0xa821);
			sungem_phy_ग_लिखो(phy, 0x1c, 0x941d);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54xx_setup_aneg(काष्ठा mii_phy *phy, u32 advertise)
अणु
	u16 ctl, adv;

	phy->स्वतःneg = 1;
	phy->speed = SPEED_10;
	phy->duplex = DUPLEX_HALF;
	phy->छोड़ो = 0;
	phy->advertising = advertise;

	/* Setup standard advertise */
	adv = sungem_phy_पढ़ो(phy, MII_ADVERTISE);
	adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
	अगर (advertise & ADVERTISED_10baseT_Half)
		adv |= ADVERTISE_10HALF;
	अगर (advertise & ADVERTISED_10baseT_Full)
		adv |= ADVERTISE_10FULL;
	अगर (advertise & ADVERTISED_100baseT_Half)
		adv |= ADVERTISE_100HALF;
	अगर (advertise & ADVERTISED_100baseT_Full)
		adv |= ADVERTISE_100FULL;
	अगर (advertise & ADVERTISED_Pause)
		adv |= ADVERTISE_PAUSE_CAP;
	अगर (advertise & ADVERTISED_Asym_Pause)
		adv |= ADVERTISE_PAUSE_ASYM;
	sungem_phy_ग_लिखो(phy, MII_ADVERTISE, adv);

	/* Setup 1000BT advertise */
	adv = sungem_phy_पढ़ो(phy, MII_1000BASETCONTROL);
	adv &= ~(MII_1000BASETCONTROL_FULLDUPLEXCAP|MII_1000BASETCONTROL_HALFDUPLEXCAP);
	अगर (advertise & SUPPORTED_1000baseT_Half)
		adv |= MII_1000BASETCONTROL_HALFDUPLEXCAP;
	अगर (advertise & SUPPORTED_1000baseT_Full)
		adv |= MII_1000BASETCONTROL_FULLDUPLEXCAP;
	sungem_phy_ग_लिखो(phy, MII_1000BASETCONTROL, adv);

	/* Start/Restart aneg */
	ctl = sungem_phy_पढ़ो(phy, MII_BMCR);
	ctl |= (BMCR_ANENABLE | BMCR_ANRESTART);
	sungem_phy_ग_लिखो(phy, MII_BMCR, ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54xx_setup_क्रमced(काष्ठा mii_phy *phy, पूर्णांक speed, पूर्णांक fd)
अणु
	u16 ctl;

	phy->स्वतःneg = 0;
	phy->speed = speed;
	phy->duplex = fd;
	phy->छोड़ो = 0;

	ctl = sungem_phy_पढ़ो(phy, MII_BMCR);
	ctl &= ~(BMCR_FULLDPLX|BMCR_SPEED100|BMCR_SPD2|BMCR_ANENABLE);

	/* First reset the PHY */
	sungem_phy_ग_लिखो(phy, MII_BMCR, ctl | BMCR_RESET);

	/* Select speed & duplex */
	चयन(speed) अणु
	हाल SPEED_10:
		अवरोध;
	हाल SPEED_100:
		ctl |= BMCR_SPEED100;
		अवरोध;
	हाल SPEED_1000:
		ctl |= BMCR_SPD2;
	पूर्ण
	अगर (fd == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;

	// XXX Should we set the sungem to GII now on 1000BT ?

	sungem_phy_ग_लिखो(phy, MII_BMCR, ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54xx_पढ़ो_link(काष्ठा mii_phy *phy)
अणु
	पूर्णांक link_mode;
	u16 val;

	अगर (phy->स्वतःneg) अणु
	    	val = sungem_phy_पढ़ो(phy, MII_BCM5400_AUXSTATUS);
		link_mode = ((val & MII_BCM5400_AUXSTATUS_LINKMODE_MASK) >>
			     MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT);
		phy->duplex = phy_BCM5400_link_table[link_mode][0] ?
			DUPLEX_FULL : DUPLEX_HALF;
		phy->speed = phy_BCM5400_link_table[link_mode][2] ?
				SPEED_1000 :
				(phy_BCM5400_link_table[link_mode][1] ?
				 SPEED_100 : SPEED_10);
		val = sungem_phy_पढ़ो(phy, MII_LPA);
		phy->छोड़ो = (phy->duplex == DUPLEX_FULL) &&
			((val & LPA_PAUSE) != 0);
	पूर्ण
	/* On non-aneg, we assume what we put in BMCR is the speed,
	 * though magic-aneg shouldn't prevent this हाल from occurring
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक marvell88e1111_init(काष्ठा mii_phy* phy)
अणु
	u16 rev;

	/* magic init sequence क्रम rev 0 */
	rev = sungem_phy_पढ़ो(phy, MII_PHYSID2) & 0x000f;
	अगर (rev == 0) अणु
		sungem_phy_ग_लिखो(phy, 0x1d, 0x000a);
		sungem_phy_ग_लिखो(phy, 0x1e, 0x0821);

		sungem_phy_ग_लिखो(phy, 0x1d, 0x0006);
		sungem_phy_ग_लिखो(phy, 0x1e, 0x8600);

		sungem_phy_ग_लिखो(phy, 0x1d, 0x000b);
		sungem_phy_ग_लिखो(phy, 0x1e, 0x0100);

		sungem_phy_ग_लिखो(phy, 0x1d, 0x0004);
		sungem_phy_ग_लिखो(phy, 0x1e, 0x4850);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा BCM5421_MODE_MASK	(1 << 5)

अटल पूर्णांक bcm5421_poll_link(काष्ठा mii_phy* phy)
अणु
	u32 phy_reg;
	पूर्णांक mode;

	/* find out in what mode we are */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x1000);
	phy_reg = sungem_phy_पढ़ो(phy, MII_NCONFIG);

	mode = (phy_reg & BCM5421_MODE_MASK) >> 5;

	अगर ( mode == BCM54XX_COPPER)
		वापस genmii_poll_link(phy);

	/* try to find out whether we have a link */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x2000);
	phy_reg = sungem_phy_पढ़ो(phy, MII_NCONFIG);

	अगर (phy_reg & 0x0020)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक bcm5421_पढ़ो_link(काष्ठा mii_phy* phy)
अणु
	u32 phy_reg;
	पूर्णांक mode;

	/* find out in what mode we are */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x1000);
	phy_reg = sungem_phy_पढ़ो(phy, MII_NCONFIG);

	mode = (phy_reg & BCM5421_MODE_MASK ) >> 5;

	अगर ( mode == BCM54XX_COPPER)
		वापस bcm54xx_पढ़ो_link(phy);

	phy->speed = SPEED_1000;

	/* find out whether we are running half- or full duplex */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x2000);
	phy_reg = sungem_phy_पढ़ो(phy, MII_NCONFIG);

	अगर ( (phy_reg & 0x0080) >> 7)
		phy->duplex |=  DUPLEX_HALF;
	अन्यथा
		phy->duplex |=  DUPLEX_FULL;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5421_enable_fiber(काष्ठा mii_phy* phy, पूर्णांक स्वतःneg)
अणु
	/* enable fiber mode */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x9020);
	/* LEDs active in both modes, स्वतःsense prio = fiber */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x945f);

	अगर (!स्वतःneg) अणु
		/* चयन off fibre स्वतःneg */
		sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0xfc01);
		sungem_phy_ग_लिखो(phy, 0x0b, 0x0004);
	पूर्ण

	phy->स्वतःneg = स्वतःneg;

	वापस 0;
पूर्ण

#घोषणा BCM5461_FIBER_LINK	(1 << 2)
#घोषणा BCM5461_MODE_MASK	(3 << 1)

अटल पूर्णांक bcm5461_poll_link(काष्ठा mii_phy* phy)
अणु
	u32 phy_reg;
	पूर्णांक mode;

	/* find out in what mode we are */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x7c00);
	phy_reg = sungem_phy_पढ़ो(phy, MII_NCONFIG);

	mode = (phy_reg & BCM5461_MODE_MASK ) >> 1;

	अगर ( mode == BCM54XX_COPPER)
		वापस genmii_poll_link(phy);

	/* find out whether we have a link */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x7000);
	phy_reg = sungem_phy_पढ़ो(phy, MII_NCONFIG);

	अगर (phy_reg & BCM5461_FIBER_LINK)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा BCM5461_FIBER_DUPLEX	(1 << 3)

अटल पूर्णांक bcm5461_पढ़ो_link(काष्ठा mii_phy* phy)
अणु
	u32 phy_reg;
	पूर्णांक mode;

	/* find out in what mode we are */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x7c00);
	phy_reg = sungem_phy_पढ़ो(phy, MII_NCONFIG);

	mode = (phy_reg & BCM5461_MODE_MASK ) >> 1;

	अगर ( mode == BCM54XX_COPPER) अणु
		वापस bcm54xx_पढ़ो_link(phy);
	पूर्ण

	phy->speed = SPEED_1000;

	/* find out whether we are running half- or full duplex */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0x7000);
	phy_reg = sungem_phy_पढ़ो(phy, MII_NCONFIG);

	अगर (phy_reg & BCM5461_FIBER_DUPLEX)
		phy->duplex |=  DUPLEX_FULL;
	अन्यथा
		phy->duplex |=  DUPLEX_HALF;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5461_enable_fiber(काष्ठा mii_phy* phy, पूर्णांक स्वतःneg)
अणु
	/* select fiber mode, enable 1000 base-X रेजिस्टरs */
	sungem_phy_ग_लिखो(phy, MII_NCONFIG, 0xfc0b);

	अगर (स्वतःneg) अणु
		/* enable fiber with no स्वतःnegotiation */
		sungem_phy_ग_लिखो(phy, MII_ADVERTISE, 0x01e0);
		sungem_phy_ग_लिखो(phy, MII_BMCR, 0x1140);
	पूर्ण अन्यथा अणु
		/* enable fiber with स्वतःnegotiation */
		sungem_phy_ग_लिखो(phy, MII_BMCR, 0x0140);
	पूर्ण

	phy->स्वतःneg = स्वतःneg;

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_setup_aneg(काष्ठा mii_phy *phy, u32 advertise)
अणु
	u16 ctl, adv;

	phy->स्वतःneg = 1;
	phy->speed = SPEED_10;
	phy->duplex = DUPLEX_HALF;
	phy->छोड़ो = 0;
	phy->advertising = advertise;

	/* Setup standard advertise */
	adv = sungem_phy_पढ़ो(phy, MII_ADVERTISE);
	adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
	अगर (advertise & ADVERTISED_10baseT_Half)
		adv |= ADVERTISE_10HALF;
	अगर (advertise & ADVERTISED_10baseT_Full)
		adv |= ADVERTISE_10FULL;
	अगर (advertise & ADVERTISED_100baseT_Half)
		adv |= ADVERTISE_100HALF;
	अगर (advertise & ADVERTISED_100baseT_Full)
		adv |= ADVERTISE_100FULL;
	अगर (advertise & ADVERTISED_Pause)
		adv |= ADVERTISE_PAUSE_CAP;
	अगर (advertise & ADVERTISED_Asym_Pause)
		adv |= ADVERTISE_PAUSE_ASYM;
	sungem_phy_ग_लिखो(phy, MII_ADVERTISE, adv);

	/* Setup 1000BT advertise & enable crossover detect
	 * XXX How करो we advertise 1000BT ? Darwin source is
	 * confusing here, they पढ़ो from specअगरic control and
	 * ग_लिखो to control... Someone has specs क्रम those
	 * beasts ?
	 */
	adv = sungem_phy_पढ़ो(phy, MII_M1011_PHY_SPEC_CONTROL);
	adv |= MII_M1011_PHY_SPEC_CONTROL_AUTO_MDIX;
	adv &= ~(MII_1000BASETCONTROL_FULLDUPLEXCAP |
			MII_1000BASETCONTROL_HALFDUPLEXCAP);
	अगर (advertise & SUPPORTED_1000baseT_Half)
		adv |= MII_1000BASETCONTROL_HALFDUPLEXCAP;
	अगर (advertise & SUPPORTED_1000baseT_Full)
		adv |= MII_1000BASETCONTROL_FULLDUPLEXCAP;
	sungem_phy_ग_लिखो(phy, MII_1000BASETCONTROL, adv);

	/* Start/Restart aneg */
	ctl = sungem_phy_पढ़ो(phy, MII_BMCR);
	ctl |= (BMCR_ANENABLE | BMCR_ANRESTART);
	sungem_phy_ग_लिखो(phy, MII_BMCR, ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_setup_क्रमced(काष्ठा mii_phy *phy, पूर्णांक speed, पूर्णांक fd)
अणु
	u16 ctl, ctl2;

	phy->स्वतःneg = 0;
	phy->speed = speed;
	phy->duplex = fd;
	phy->छोड़ो = 0;

	ctl = sungem_phy_पढ़ो(phy, MII_BMCR);
	ctl &= ~(BMCR_FULLDPLX|BMCR_SPEED100|BMCR_SPD2|BMCR_ANENABLE);
	ctl |= BMCR_RESET;

	/* Select speed & duplex */
	चयन(speed) अणु
	हाल SPEED_10:
		अवरोध;
	हाल SPEED_100:
		ctl |= BMCR_SPEED100;
		अवरोध;
	/* I'm not sure about the one below, again, Darwin source is
	 * quite confusing and I lack chip specs
	 */
	हाल SPEED_1000:
		ctl |= BMCR_SPD2;
	पूर्ण
	अगर (fd == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;

	/* Disable crossover. Again, the way Apple करोes it is strange,
	 * though I करोn't assume they are wrong ;)
	 */
	ctl2 = sungem_phy_पढ़ो(phy, MII_M1011_PHY_SPEC_CONTROL);
	ctl2 &= ~(MII_M1011_PHY_SPEC_CONTROL_MANUAL_MDIX |
		MII_M1011_PHY_SPEC_CONTROL_AUTO_MDIX |
		MII_1000BASETCONTROL_FULLDUPLEXCAP |
		MII_1000BASETCONTROL_HALFDUPLEXCAP);
	अगर (speed == SPEED_1000)
		ctl2 |= (fd == DUPLEX_FULL) ?
			MII_1000BASETCONTROL_FULLDUPLEXCAP :
			MII_1000BASETCONTROL_HALFDUPLEXCAP;
	sungem_phy_ग_लिखो(phy, MII_1000BASETCONTROL, ctl2);

	// XXX Should we set the sungem to GII now on 1000BT ?

	sungem_phy_ग_लिखो(phy, MII_BMCR, ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_पढ़ो_link(काष्ठा mii_phy *phy)
अणु
	u16 status, pmask;

	अगर (phy->स्वतःneg) अणु
		status = sungem_phy_पढ़ो(phy, MII_M1011_PHY_SPEC_STATUS);
		अगर ((status & MII_M1011_PHY_SPEC_STATUS_RESOLVED) == 0)
			वापस -EAGAIN;
		अगर (status & MII_M1011_PHY_SPEC_STATUS_1000)
			phy->speed = SPEED_1000;
		अन्यथा अगर (status & MII_M1011_PHY_SPEC_STATUS_100)
			phy->speed = SPEED_100;
		अन्यथा
			phy->speed = SPEED_10;
		अगर (status & MII_M1011_PHY_SPEC_STATUS_FULLDUPLEX)
			phy->duplex = DUPLEX_FULL;
		अन्यथा
			phy->duplex = DUPLEX_HALF;
		pmask = MII_M1011_PHY_SPEC_STATUS_TX_PAUSE |
			MII_M1011_PHY_SPEC_STATUS_RX_PAUSE;
		phy->छोड़ो = (status & pmask) == pmask;
	पूर्ण
	/* On non-aneg, we assume what we put in BMCR is the speed,
	 * though magic-aneg shouldn't prevent this हाल from occurring
	 */

	वापस 0;
पूर्ण

#घोषणा MII_BASIC_FEATURES \
	(SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |	\
	 SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |	\
	 SUPPORTED_Autoneg | SUPPORTED_TP | SUPPORTED_MII |	\
	 SUPPORTED_Pause)

/* On gigabit capable PHYs, we advertise Pause support but not asym छोड़ो
 * support क्रम now as I'm not sure it's supported and Darwin doesn't करो
 * it neither. --BenH.
 */
#घोषणा MII_GBIT_FEATURES \
	(MII_BASIC_FEATURES |	\
	 SUPPORTED_1000baseT_Half | SUPPORTED_1000baseT_Full)

/* Broadcom BCM 5201 */
अटल स्थिर काष्ठा mii_phy_ops bcm5201_phy_ops = अणु
	.init		= bcm5201_init,
	.suspend	= bcm5201_suspend,
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link,
पूर्ण;

अटल काष्ठा mii_phy_def bcm5201_phy_def = अणु
	.phy_id		= 0x00406210,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5201",
	.features	= MII_BASIC_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5201_phy_ops
पूर्ण;

/* Broadcom BCM 5221 */
अटल स्थिर काष्ठा mii_phy_ops bcm5221_phy_ops = अणु
	.suspend	= bcm5221_suspend,
	.init		= bcm5221_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link,
पूर्ण;

अटल काष्ठा mii_phy_def bcm5221_phy_def = अणु
	.phy_id		= 0x004061e0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5221",
	.features	= MII_BASIC_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5221_phy_ops
पूर्ण;

/* Broadcom BCM 5241 */
अटल स्थिर काष्ठा mii_phy_ops bcm5241_phy_ops = अणु
	.suspend	= bcm5241_suspend,
	.init		= bcm5241_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link,
पूर्ण;
अटल काष्ठा mii_phy_def bcm5241_phy_def = अणु
	.phy_id		= 0x0143bc30,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5241",
	.features	= MII_BASIC_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5241_phy_ops
पूर्ण;

/* Broadcom BCM 5400 */
अटल स्थिर काष्ठा mii_phy_ops bcm5400_phy_ops = अणु
	.init		= bcm5400_init,
	.suspend	= bcm5400_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_क्रमced	= bcm54xx_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= bcm54xx_पढ़ो_link,
पूर्ण;

अटल काष्ठा mii_phy_def bcm5400_phy_def = अणु
	.phy_id		= 0x00206040,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5400",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5400_phy_ops
पूर्ण;

/* Broadcom BCM 5401 */
अटल स्थिर काष्ठा mii_phy_ops bcm5401_phy_ops = अणु
	.init		= bcm5401_init,
	.suspend	= bcm5401_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_क्रमced	= bcm54xx_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= bcm54xx_पढ़ो_link,
पूर्ण;

अटल काष्ठा mii_phy_def bcm5401_phy_def = अणु
	.phy_id		= 0x00206050,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5401",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5401_phy_ops
पूर्ण;

/* Broadcom BCM 5411 */
अटल स्थिर काष्ठा mii_phy_ops bcm5411_phy_ops = अणु
	.init		= bcm5411_init,
	.suspend	= generic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_क्रमced	= bcm54xx_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= bcm54xx_पढ़ो_link,
पूर्ण;

अटल काष्ठा mii_phy_def bcm5411_phy_def = अणु
	.phy_id		= 0x00206070,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5411",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5411_phy_ops
पूर्ण;

/* Broadcom BCM 5421 */
अटल स्थिर काष्ठा mii_phy_ops bcm5421_phy_ops = अणु
	.init		= bcm5421_init,
	.suspend	= generic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_क्रमced	= bcm54xx_setup_क्रमced,
	.poll_link	= bcm5421_poll_link,
	.पढ़ो_link	= bcm5421_पढ़ो_link,
	.enable_fiber   = bcm5421_enable_fiber,
पूर्ण;

अटल काष्ठा mii_phy_def bcm5421_phy_def = अणु
	.phy_id		= 0x002060e0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5421",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5421_phy_ops
पूर्ण;

/* Broadcom BCM 5421 built-in K2 */
अटल स्थिर काष्ठा mii_phy_ops bcm5421k2_phy_ops = अणु
	.init		= bcm5421_init,
	.suspend	= generic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_क्रमced	= bcm54xx_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= bcm54xx_पढ़ो_link,
पूर्ण;

अटल काष्ठा mii_phy_def bcm5421k2_phy_def = अणु
	.phy_id		= 0x002062e0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5421-K2",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5421k2_phy_ops
पूर्ण;

अटल स्थिर काष्ठा mii_phy_ops bcm5461_phy_ops = अणु
	.init		= bcm5421_init,
	.suspend	= generic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_क्रमced	= bcm54xx_setup_क्रमced,
	.poll_link	= bcm5461_poll_link,
	.पढ़ो_link	= bcm5461_पढ़ो_link,
	.enable_fiber   = bcm5461_enable_fiber,
पूर्ण;

अटल काष्ठा mii_phy_def bcm5461_phy_def = अणु
	.phy_id		= 0x002060c0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5461",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5461_phy_ops
पूर्ण;

/* Broadcom BCM 5462 built-in Vesta */
अटल स्थिर काष्ठा mii_phy_ops bcm5462V_phy_ops = अणु
	.init		= bcm5421_init,
	.suspend	= generic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_क्रमced	= bcm54xx_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= bcm54xx_पढ़ो_link,
पूर्ण;

अटल काष्ठा mii_phy_def bcm5462V_phy_def = अणु
	.phy_id		= 0x002060d0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5462-Vesta",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &bcm5462V_phy_ops
पूर्ण;

/* Marvell 88E1101 amd 88E1111 */
अटल स्थिर काष्ठा mii_phy_ops marvell88e1101_phy_ops = अणु
	.suspend	= generic_suspend,
	.setup_aneg	= marvell_setup_aneg,
	.setup_क्रमced	= marvell_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= marvell_पढ़ो_link
पूर्ण;

अटल स्थिर काष्ठा mii_phy_ops marvell88e1111_phy_ops = अणु
	.init		= marvell88e1111_init,
	.suspend	= generic_suspend,
	.setup_aneg	= marvell_setup_aneg,
	.setup_क्रमced	= marvell_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= marvell_पढ़ो_link
पूर्ण;

/* two revs in darwin क्रम the 88e1101 ... I could use a datasheet
 * to get the proper names...
 */
अटल काष्ठा mii_phy_def marvell88e1101v1_phy_def = अणु
	.phy_id		= 0x01410c20,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Marvell 88E1101v1",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &marvell88e1101_phy_ops
पूर्ण;
अटल काष्ठा mii_phy_def marvell88e1101v2_phy_def = अणु
	.phy_id		= 0x01410c60,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Marvell 88E1101v2",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &marvell88e1101_phy_ops
पूर्ण;
अटल काष्ठा mii_phy_def marvell88e1111_phy_def = अणु
	.phy_id		= 0x01410cc0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Marvell 88E1111",
	.features	= MII_GBIT_FEATURES,
	.magic_aneg	= 1,
	.ops		= &marvell88e1111_phy_ops
पूर्ण;

/* Generic implementation क्रम most 10/100 PHYs */
अटल स्थिर काष्ठा mii_phy_ops generic_phy_ops = अणु
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link
पूर्ण;

अटल काष्ठा mii_phy_def genmii_phy_def = अणु
	.phy_id		= 0x00000000,
	.phy_id_mask	= 0x00000000,
	.name		= "Generic MII",
	.features	= MII_BASIC_FEATURES,
	.magic_aneg	= 0,
	.ops		= &generic_phy_ops
पूर्ण;

अटल काष्ठा mii_phy_def* mii_phy_table[] = अणु
	&bcm5201_phy_def,
	&bcm5221_phy_def,
	&bcm5241_phy_def,
	&bcm5400_phy_def,
	&bcm5401_phy_def,
	&bcm5411_phy_def,
	&bcm5421_phy_def,
	&bcm5421k2_phy_def,
	&bcm5461_phy_def,
	&bcm5462V_phy_def,
	&marvell88e1101v1_phy_def,
	&marvell88e1101v2_phy_def,
	&marvell88e1111_phy_def,
	&genmii_phy_def,
	शून्य
पूर्ण;

पूर्णांक sungem_phy_probe(काष्ठा mii_phy *phy, पूर्णांक mii_id)
अणु
	पूर्णांक rc;
	u32 id;
	काष्ठा mii_phy_def* def;
	पूर्णांक i;

	/* We करो not reset the mii_phy काष्ठाure as the driver
	 * may re-probe the PHY regulary
	 */
	phy->mii_id = mii_id;

	/* Take PHY out of isloate mode and reset it. */
	rc = reset_one_mii_phy(phy, mii_id);
	अगर (rc)
		जाओ fail;

	/* Read ID and find matching entry */
	id = (sungem_phy_पढ़ो(phy, MII_PHYSID1) << 16 | sungem_phy_पढ़ो(phy, MII_PHYSID2));
	prपूर्णांकk(KERN_DEBUG KBUILD_MODNAME ": " "PHY ID: %x, addr: %x\n",
	       id, mii_id);
	क्रम (i=0; (def = mii_phy_table[i]) != शून्य; i++)
		अगर ((id & def->phy_id_mask) == def->phy_id)
			अवरोध;
	/* Should never be शून्य (we have a generic entry), but... */
	अगर (def == शून्य)
		जाओ fail;

	phy->def = def;

	वापस 0;
fail:
	phy->speed = 0;
	phy->duplex = 0;
	phy->छोड़ो = 0;
	phy->advertising = 0;
	वापस -ENODEV;
पूर्ण

EXPORT_SYMBOL(sungem_phy_probe);
MODULE_LICENSE("GPL");
