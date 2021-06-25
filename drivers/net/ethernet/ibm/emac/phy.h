<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/ibm/emac/phy.h
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller, PHY support
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Benjamin Herrenschmidt <benh@kernel.crashing.org>
 * February 2003
 *
 * Minor additions by Eugene Surovegin <ebs@ebshome.net>, 2004
 *
 * This file basically duplicates sungem_phy.अणुc,hपूर्ण with dअगरferent PHYs
 * supported. I'm looking पूर्णांकo merging that in a single mii layer more
 * flexible than mii.c
 */

#अगर_अघोषित __IBM_NEWEMAC_PHY_H
#घोषणा __IBM_NEWEMAC_PHY_H

काष्ठा mii_phy;

/* Operations supported by any kind of PHY */
काष्ठा mii_phy_ops अणु
	पूर्णांक (*init) (काष्ठा mii_phy * phy);
	पूर्णांक (*suspend) (काष्ठा mii_phy * phy, पूर्णांक wol_options);
	पूर्णांक (*setup_aneg) (काष्ठा mii_phy * phy, u32 advertise);
	पूर्णांक (*setup_क्रमced) (काष्ठा mii_phy * phy, पूर्णांक speed, पूर्णांक fd);
	पूर्णांक (*poll_link) (काष्ठा mii_phy * phy);
	पूर्णांक (*पढ़ो_link) (काष्ठा mii_phy * phy);
पूर्ण;

/* Structure used to अटलally define an mii/gii based PHY */
काष्ठा mii_phy_def अणु
	u32 phy_id;		/* Concatenated ID1 << 16 | ID2 */
	u32 phy_id_mask;	/* Signअगरicant bits */
	u32 features;		/* Ethtool SUPPORTED_* defines or
				   0 क्रम स्वतःdetect */
	पूर्णांक magic_aneg;		/* Autoneg करोes all speed test क्रम us */
	स्थिर अक्षर *name;
	स्थिर काष्ठा mii_phy_ops *ops;
पूर्ण;

/* An instance of a PHY, partially borrowed from mii_अगर_info */
काष्ठा mii_phy अणु
	काष्ठा mii_phy_def *def;
	u32 advertising;	/* Ethtool ADVERTISED_* defines */
	u32 features;		/* Copied from mii_phy_def.features
				   or determined स्वतःmaticaly */
	पूर्णांक address;		/* PHY address */
	पूर्णांक mode;		/* PHY mode */
	पूर्णांक gpcs_address;	/* GPCS PHY address */

	/* 1: स्वतःneg enabled, 0: disabled */
	पूर्णांक स्वतःneg;

	/* क्रमced speed & duplex (no स्वतःneg)
	 * partner speed & duplex & छोड़ो (स्वतःneg)
	 */
	पूर्णांक speed;
	पूर्णांक duplex;
	पूर्णांक छोड़ो;
	पूर्णांक asym_छोड़ो;

	/* Provided by host chip */
	काष्ठा net_device *dev;
	पूर्णांक (*mdio_पढ़ो) (काष्ठा net_device * dev, पूर्णांक addr, पूर्णांक reg);
	व्योम (*mdio_ग_लिखो) (काष्ठा net_device * dev, पूर्णांक addr, पूर्णांक reg,
			    पूर्णांक val);
पूर्ण;

/* Pass in a काष्ठा mii_phy with dev, mdio_पढ़ो and mdio_ग_लिखो
 * filled, the reमुख्यing fields will be filled on वापस
 */
पूर्णांक emac_mii_phy_probe(काष्ठा mii_phy *phy, पूर्णांक address);
पूर्णांक emac_mii_reset_phy(काष्ठा mii_phy *phy);
पूर्णांक emac_mii_reset_gpcs(काष्ठा mii_phy *phy);

#पूर्ण_अगर /* __IBM_NEWEMAC_PHY_H */
