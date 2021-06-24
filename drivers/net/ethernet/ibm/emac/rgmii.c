<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/ethernet/ibm/emac/rgmii.c
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller, RGMII bridge support.
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Copyright (c) 2004, 2005 Zultys Technologies.
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *
 * Based on original work by
 * 	Matt Porter <mporter@kernel.crashing.org>
 * 	Copyright 2004 MontaVista Software, Inc.
 */
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/पन.स>

#समावेश "emac.h"
#समावेश "debug.h"

// XXX FIXME: Axon seems to support a subset of the RGMII, we
// thus need to take that पूर्णांकo account and possibly change some
// of the bit settings below that करोn't seem to quite match the
// AXON spec

/* RGMIIx_FER */
#घोषणा RGMII_FER_MASK(idx)	(0x7 << ((idx) * 4))
#घोषणा RGMII_FER_RTBI(idx)	(0x4 << ((idx) * 4))
#घोषणा RGMII_FER_RGMII(idx)	(0x5 << ((idx) * 4))
#घोषणा RGMII_FER_TBI(idx)	(0x6 << ((idx) * 4))
#घोषणा RGMII_FER_GMII(idx)	(0x7 << ((idx) * 4))
#घोषणा RGMII_FER_MII(idx)	RGMII_FER_GMII(idx)

/* RGMIIx_SSR */
#घोषणा RGMII_SSR_MASK(idx)	(0x7 << ((idx) * 8))
#घोषणा RGMII_SSR_10(idx)	(0x1 << ((idx) * 8))
#घोषणा RGMII_SSR_100(idx)	(0x2 << ((idx) * 8))
#घोषणा RGMII_SSR_1000(idx)	(0x4 << ((idx) * 8))

/* RGMII bridge supports only GMII/TBI and RGMII/RTBI PHYs */
अटल अंतरभूत पूर्णांक rgmii_valid_mode(पूर्णांक phy_mode)
अणु
	वापस  phy_पूर्णांकerface_mode_is_rgmii(phy_mode) ||
		phy_mode == PHY_INTERFACE_MODE_GMII ||
		phy_mode == PHY_INTERFACE_MODE_MII ||
		phy_mode == PHY_INTERFACE_MODE_TBI ||
		phy_mode == PHY_INTERFACE_MODE_RTBI;
पूर्ण

अटल अंतरभूत u32 rgmii_mode_mask(पूर्णांक mode, पूर्णांक input)
अणु
	चयन (mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		वापस RGMII_FER_RGMII(input);
	हाल PHY_INTERFACE_MODE_TBI:
		वापस RGMII_FER_TBI(input);
	हाल PHY_INTERFACE_MODE_GMII:
		वापस RGMII_FER_GMII(input);
	हाल PHY_INTERFACE_MODE_MII:
		वापस RGMII_FER_MII(input);
	हाल PHY_INTERFACE_MODE_RTBI:
		वापस RGMII_FER_RTBI(input);
	शेष:
		BUG();
	पूर्ण
पूर्ण

पूर्णांक rgmii_attach(काष्ठा platक्रमm_device *ofdev, पूर्णांक input, पूर्णांक mode)
अणु
	काष्ठा rgmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा rgmii_regs __iomem *p = dev->base;

	RGMII_DBG(dev, "attach(%d)" NL, input);

	/* Check अगर we need to attach to a RGMII */
	अगर (input < 0 || !rgmii_valid_mode(mode)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: unsupported settings !\n",
		       ofdev->dev.of_node);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&dev->lock);

	/* Enable this input */
	out_be32(&p->fer, in_be32(&p->fer) | rgmii_mode_mask(mode, input));

	prपूर्णांकk(KERN_NOTICE "%pOF: input %d in %s mode\n",
	       ofdev->dev.of_node, input, phy_modes(mode));

	++dev->users;

	mutex_unlock(&dev->lock);

	वापस 0;
पूर्ण

व्योम rgmii_set_speed(काष्ठा platक्रमm_device *ofdev, पूर्णांक input, पूर्णांक speed)
अणु
	काष्ठा rgmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा rgmii_regs __iomem *p = dev->base;
	u32 ssr;

	mutex_lock(&dev->lock);

	ssr = in_be32(&p->ssr) & ~RGMII_SSR_MASK(input);

	RGMII_DBG(dev, "speed(%d, %d)" NL, input, speed);

	अगर (speed == SPEED_1000)
		ssr |= RGMII_SSR_1000(input);
	अन्यथा अगर (speed == SPEED_100)
		ssr |= RGMII_SSR_100(input);
	अन्यथा अगर (speed == SPEED_10)
		ssr |= RGMII_SSR_10(input);

	out_be32(&p->ssr, ssr);

	mutex_unlock(&dev->lock);
पूर्ण

व्योम rgmii_get_mdio(काष्ठा platक्रमm_device *ofdev, पूर्णांक input)
अणु
	काष्ठा rgmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा rgmii_regs __iomem *p = dev->base;
	u32 fer;

	RGMII_DBG2(dev, "get_mdio(%d)" NL, input);

	अगर (!(dev->flags & EMAC_RGMII_FLAG_HAS_MDIO))
		वापस;

	mutex_lock(&dev->lock);

	fer = in_be32(&p->fer);
	fer |= 0x00080000u >> input;
	out_be32(&p->fer, fer);
	(व्योम)in_be32(&p->fer);

	DBG2(dev, " fer = 0x%08x\n", fer);
पूर्ण

व्योम rgmii_put_mdio(काष्ठा platक्रमm_device *ofdev, पूर्णांक input)
अणु
	काष्ठा rgmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा rgmii_regs __iomem *p = dev->base;
	u32 fer;

	RGMII_DBG2(dev, "put_mdio(%d)" NL, input);

	अगर (!(dev->flags & EMAC_RGMII_FLAG_HAS_MDIO))
		वापस;

	fer = in_be32(&p->fer);
	fer &= ~(0x00080000u >> input);
	out_be32(&p->fer, fer);
	(व्योम)in_be32(&p->fer);

	DBG2(dev, " fer = 0x%08x\n", fer);

	mutex_unlock(&dev->lock);
पूर्ण

व्योम rgmii_detach(काष्ठा platक्रमm_device *ofdev, पूर्णांक input)
अणु
	काष्ठा rgmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा rgmii_regs __iomem *p;

	BUG_ON(!dev || dev->users == 0);
	p = dev->base;

	mutex_lock(&dev->lock);

	RGMII_DBG(dev, "detach(%d)" NL, input);

	/* Disable this input */
	out_be32(&p->fer, in_be32(&p->fer) & ~RGMII_FER_MASK(input));

	--dev->users;

	mutex_unlock(&dev->lock);
पूर्ण

पूर्णांक rgmii_get_regs_len(काष्ठा platक्रमm_device *ofdev)
अणु
	वापस माप(काष्ठा emac_ethtool_regs_subhdr) +
		माप(काष्ठा rgmii_regs);
पूर्ण

व्योम *rgmii_dump_regs(काष्ठा platक्रमm_device *ofdev, व्योम *buf)
अणु
	काष्ठा rgmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा emac_ethtool_regs_subhdr *hdr = buf;
	काष्ठा rgmii_regs *regs = (काष्ठा rgmii_regs *)(hdr + 1);

	hdr->version = 0;
	hdr->index = 0; /* क्रम now, are there chips with more than one
			 * rgmii ? अगर yes, then we'll add a cell_index
			 * like we करो क्रम emac
			 */
	स_नकल_fromio(regs, dev->base, माप(काष्ठा rgmii_regs));
	वापस regs + 1;
पूर्ण


अटल पूर्णांक rgmii_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा rgmii_instance *dev;
	काष्ठा resource regs;
	पूर्णांक rc;

	rc = -ENOMEM;
	dev = kzalloc(माप(काष्ठा rgmii_instance), GFP_KERNEL);
	अगर (dev == शून्य)
		जाओ err_gone;

	mutex_init(&dev->lock);
	dev->ofdev = ofdev;

	rc = -ENXIO;
	अगर (of_address_to_resource(np, 0, &regs)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get registers address\n", np);
		जाओ err_मुक्त;
	पूर्ण

	rc = -ENOMEM;
	dev->base = (काष्ठा rgmii_regs __iomem *)ioremap(regs.start,
						 माप(काष्ठा rgmii_regs));
	अगर (dev->base == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't map device registers!\n", np);
		जाओ err_मुक्त;
	पूर्ण

	/* Check क्रम RGMII flags */
	अगर (of_get_property(ofdev->dev.of_node, "has-mdio", शून्य))
		dev->flags |= EMAC_RGMII_FLAG_HAS_MDIO;

	/* CAB lacks the right properties, fix this up */
	अगर (of_device_is_compatible(ofdev->dev.of_node, "ibm,rgmii-axon"))
		dev->flags |= EMAC_RGMII_FLAG_HAS_MDIO;

	DBG2(dev, " Boot FER = 0x%08x, SSR = 0x%08x\n",
	     in_be32(&dev->base->fer), in_be32(&dev->base->ssr));

	/* Disable all inमाला_दो by शेष */
	out_be32(&dev->base->fer, 0);

	prपूर्णांकk(KERN_INFO
	       "RGMII %pOF initialized with%s MDIO support\n",
	       ofdev->dev.of_node,
	       (dev->flags & EMAC_RGMII_FLAG_HAS_MDIO) ? "" : "out");

	wmb();
	platक्रमm_set_drvdata(ofdev, dev);

	वापस 0;

 err_मुक्त:
	kमुक्त(dev);
 err_gone:
	वापस rc;
पूर्ण

अटल पूर्णांक rgmii_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा rgmii_instance *dev = platक्रमm_get_drvdata(ofdev);

	WARN_ON(dev->users != 0);

	iounmap(dev->base);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rgmii_match[] =
अणु
	अणु
		.compatible	= "ibm,rgmii",
	पूर्ण,
	अणु
		.type		= "emac-rgmii",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rgmii_driver = अणु
	.driver = अणु
		.name = "emac-rgmii",
		.of_match_table = rgmii_match,
	पूर्ण,
	.probe = rgmii_probe,
	.हटाओ = rgmii_हटाओ,
पूर्ण;

पूर्णांक __init rgmii_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rgmii_driver);
पूर्ण

व्योम rgmii_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rgmii_driver);
पूर्ण
