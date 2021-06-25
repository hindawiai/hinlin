<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/ethernet/ibm/emac/zmii.c
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller, ZMII bridge support.
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
 *      Armin Kuster <akuster@mvista.com>
 * 	Copyright 2001 MontaVista Softare Inc.
 */
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/पन.स>

#समावेश "emac.h"
#समावेश "core.h"

/* ZMIIx_FER */
#घोषणा ZMII_FER_MDI(idx)	(0x80000000 >> ((idx) * 4))
#घोषणा ZMII_FER_MDI_ALL	(ZMII_FER_MDI(0) | ZMII_FER_MDI(1) | \
				 ZMII_FER_MDI(2) | ZMII_FER_MDI(3))

#घोषणा ZMII_FER_SMII(idx)	(0x40000000 >> ((idx) * 4))
#घोषणा ZMII_FER_RMII(idx)	(0x20000000 >> ((idx) * 4))
#घोषणा ZMII_FER_MII(idx)	(0x10000000 >> ((idx) * 4))

/* ZMIIx_SSR */
#घोषणा ZMII_SSR_SCI(idx)	(0x40000000 >> ((idx) * 4))
#घोषणा ZMII_SSR_FSS(idx)	(0x20000000 >> ((idx) * 4))
#घोषणा ZMII_SSR_SP(idx)	(0x10000000 >> ((idx) * 4))

/* ZMII only supports MII, RMII and SMII
 * we also support स्वतःdetection क्रम backward compatibility
 */
अटल अंतरभूत पूर्णांक zmii_valid_mode(पूर्णांक mode)
अणु
	वापस  mode == PHY_INTERFACE_MODE_MII ||
		mode == PHY_INTERFACE_MODE_RMII ||
		mode == PHY_INTERFACE_MODE_SMII ||
		mode == PHY_INTERFACE_MODE_NA;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *zmii_mode_name(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल PHY_INTERFACE_MODE_MII:
		वापस "MII";
	हाल PHY_INTERFACE_MODE_RMII:
		वापस "RMII";
	हाल PHY_INTERFACE_MODE_SMII:
		वापस "SMII";
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत u32 zmii_mode_mask(पूर्णांक mode, पूर्णांक input)
अणु
	चयन (mode) अणु
	हाल PHY_INTERFACE_MODE_MII:
		वापस ZMII_FER_MII(input);
	हाल PHY_INTERFACE_MODE_RMII:
		वापस ZMII_FER_RMII(input);
	हाल PHY_INTERFACE_MODE_SMII:
		वापस ZMII_FER_SMII(input);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक zmii_attach(काष्ठा platक्रमm_device *ofdev, पूर्णांक input,
		phy_पूर्णांकerface_t *mode)
अणु
	काष्ठा zmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा zmii_regs __iomem *p = dev->base;

	ZMII_DBG(dev, "init(%d, %d)" NL, input, *mode);

	अगर (!zmii_valid_mode(*mode)) अणु
		/* Probably an EMAC connected to RGMII,
		 * but it still may need ZMII क्रम MDIO so
		 * we करोn't fail here.
		 */
		dev->users++;
		वापस 0;
	पूर्ण

	mutex_lock(&dev->lock);

	/* Autodetect ZMII mode अगर not specअगरied.
	 * This is only क्रम backward compatibility with the old driver.
	 * Please, always specअगरy PHY mode in your board port to aव्योम
	 * any surprises.
	 */
	अगर (dev->mode == PHY_INTERFACE_MODE_NA) अणु
		अगर (*mode == PHY_INTERFACE_MODE_NA) अणु
			u32 r = dev->fer_save;

			ZMII_DBG(dev, "autodetecting mode, FER = 0x%08x" NL, r);

			अगर (r & (ZMII_FER_MII(0) | ZMII_FER_MII(1)))
				dev->mode = PHY_INTERFACE_MODE_MII;
			अन्यथा अगर (r & (ZMII_FER_RMII(0) | ZMII_FER_RMII(1)))
				dev->mode = PHY_INTERFACE_MODE_RMII;
			अन्यथा
				dev->mode = PHY_INTERFACE_MODE_SMII;
		पूर्ण अन्यथा अणु
			dev->mode = *mode;
		पूर्ण
		prपूर्णांकk(KERN_NOTICE "%pOF: bridge in %s mode\n",
		       ofdev->dev.of_node,
		       zmii_mode_name(dev->mode));
	पूर्ण अन्यथा अणु
		/* All inमाला_दो must use the same mode */
		अगर (*mode != PHY_INTERFACE_MODE_NA && *mode != dev->mode) अणु
			prपूर्णांकk(KERN_ERR
			       "%pOF: invalid mode %d specified for input %d\n",
			       ofdev->dev.of_node, *mode, input);
			mutex_unlock(&dev->lock);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Report back correct PHY mode,
	 * it may be used during PHY initialization.
	 */
	*mode = dev->mode;

	/* Enable this input */
	out_be32(&p->fer, in_be32(&p->fer) | zmii_mode_mask(dev->mode, input));
	++dev->users;

	mutex_unlock(&dev->lock);

	वापस 0;
पूर्ण

व्योम zmii_get_mdio(काष्ठा platक्रमm_device *ofdev, पूर्णांक input)
अणु
	काष्ठा zmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	u32 fer;

	ZMII_DBG2(dev, "get_mdio(%d)" NL, input);

	mutex_lock(&dev->lock);

	fer = in_be32(&dev->base->fer) & ~ZMII_FER_MDI_ALL;
	out_be32(&dev->base->fer, fer | ZMII_FER_MDI(input));
पूर्ण

व्योम zmii_put_mdio(काष्ठा platक्रमm_device *ofdev, पूर्णांक input)
अणु
	काष्ठा zmii_instance *dev = platक्रमm_get_drvdata(ofdev);

	ZMII_DBG2(dev, "put_mdio(%d)" NL, input);
	mutex_unlock(&dev->lock);
पूर्ण


व्योम zmii_set_speed(काष्ठा platक्रमm_device *ofdev, पूर्णांक input, पूर्णांक speed)
अणु
	काष्ठा zmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	u32 ssr;

	mutex_lock(&dev->lock);

	ssr = in_be32(&dev->base->ssr);

	ZMII_DBG(dev, "speed(%d, %d)" NL, input, speed);

	अगर (speed == SPEED_100)
		ssr |= ZMII_SSR_SP(input);
	अन्यथा
		ssr &= ~ZMII_SSR_SP(input);

	out_be32(&dev->base->ssr, ssr);

	mutex_unlock(&dev->lock);
पूर्ण

व्योम zmii_detach(काष्ठा platक्रमm_device *ofdev, पूर्णांक input)
अणु
	काष्ठा zmii_instance *dev = platक्रमm_get_drvdata(ofdev);

	BUG_ON(!dev || dev->users == 0);

	mutex_lock(&dev->lock);

	ZMII_DBG(dev, "detach(%d)" NL, input);

	/* Disable this input */
	out_be32(&dev->base->fer,
		 in_be32(&dev->base->fer) & ~zmii_mode_mask(dev->mode, input));

	--dev->users;

	mutex_unlock(&dev->lock);
पूर्ण

पूर्णांक zmii_get_regs_len(काष्ठा platक्रमm_device *ofdev)
अणु
	वापस माप(काष्ठा emac_ethtool_regs_subhdr) +
		माप(काष्ठा zmii_regs);
पूर्ण

व्योम *zmii_dump_regs(काष्ठा platक्रमm_device *ofdev, व्योम *buf)
अणु
	काष्ठा zmii_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा emac_ethtool_regs_subhdr *hdr = buf;
	काष्ठा zmii_regs *regs = (काष्ठा zmii_regs *)(hdr + 1);

	hdr->version = 0;
	hdr->index = 0; /* क्रम now, are there chips with more than one
			 * zmii ? अगर yes, then we'll add a cell_index
			 * like we करो क्रम emac
			 */
	स_नकल_fromio(regs, dev->base, माप(काष्ठा zmii_regs));
	वापस regs + 1;
पूर्ण

अटल पूर्णांक zmii_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा zmii_instance *dev;
	काष्ठा resource regs;
	पूर्णांक rc;

	rc = -ENOMEM;
	dev = kzalloc(माप(काष्ठा zmii_instance), GFP_KERNEL);
	अगर (dev == शून्य)
		जाओ err_gone;

	mutex_init(&dev->lock);
	dev->ofdev = ofdev;
	dev->mode = PHY_INTERFACE_MODE_NA;

	rc = -ENXIO;
	अगर (of_address_to_resource(np, 0, &regs)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get registers address\n", np);
		जाओ err_मुक्त;
	पूर्ण

	rc = -ENOMEM;
	dev->base = (काष्ठा zmii_regs __iomem *)ioremap(regs.start,
						माप(काष्ठा zmii_regs));
	अगर (dev->base == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't map device registers!\n", np);
		जाओ err_मुक्त;
	पूर्ण

	/* We may need FER value क्रम स्वतःdetection later */
	dev->fer_save = in_be32(&dev->base->fer);

	/* Disable all inमाला_दो by शेष */
	out_be32(&dev->base->fer, 0);

	prपूर्णांकk(KERN_INFO "ZMII %pOF initialized\n", ofdev->dev.of_node);
	wmb();
	platक्रमm_set_drvdata(ofdev, dev);

	वापस 0;

 err_मुक्त:
	kमुक्त(dev);
 err_gone:
	वापस rc;
पूर्ण

अटल पूर्णांक zmii_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा zmii_instance *dev = platक्रमm_get_drvdata(ofdev);

	WARN_ON(dev->users != 0);

	iounmap(dev->base);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zmii_match[] =
अणु
	अणु
		.compatible	= "ibm,zmii",
	पूर्ण,
	/* For backward compat with old DT */
	अणु
		.type		= "emac-zmii",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver zmii_driver = अणु
	.driver = अणु
		.name = "emac-zmii",
		.of_match_table = zmii_match,
	पूर्ण,
	.probe = zmii_probe,
	.हटाओ = zmii_हटाओ,
पूर्ण;

पूर्णांक __init zmii_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&zmii_driver);
पूर्ण

व्योम zmii_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&zmii_driver);
पूर्ण
