<शैली गुरु>
/* orinoco_nortel.c
 *
 * Driver क्रम Prism II devices which would usually be driven by orinoco_cs,
 * but are connected to the PCI bus by a PCI-to-PCMCIA adapter used in
 * Nortel emobility, Symbol LA-4113 and Symbol LA-4123.
 *
 * Copyright (C) 2002 Tobias Hoffmann
 *           (C) 2003 Christoph Jungegger <disकरोs@traum404.de>
 *
 * Some of this code is borrowed from orinoco_plx.c
 *	Copyright (C) 2001 Daniel Barlow
 * Some of this code is borrowed from orinoco_pci.c
 *  Copyright (C) 2001 Jean Tourrilhes
 * Some of this code is "inspired" by linux-wlan-ng-0.1.10, but nothing
 * has been copied from it. linux-wlan-ng-0.1.10 is originally :
 *	Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in
 * which हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use your
 * version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 */

#घोषणा DRIVER_NAME "orinoco_nortel"
#घोषणा PFX DRIVER_NAME ": "

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <pcmcia/cisreg.h>

#समावेश "orinoco.h"
#समावेश "orinoco_pci.h"

#घोषणा COR_OFFSET    (0xe0)	/* COR attribute offset of Prism2 PC card */
#घोषणा COR_VALUE     (COR_LEVEL_REQ | COR_FUNC_ENA)	/* Enable PC card with पूर्णांकerrupt in level trigger */


/*
 * Do a soft reset of the card using the Configuration Option Register
 * We need this to get going...
 * This is the part of the code that is strongly inspired from wlan-ng
 *
 * Note bis : Don't try to access HERMES_CMD during the reset phase.
 * It just won't work !
 */
अटल पूर्णांक orinoco_nortel_cor_reset(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा orinoco_pci_card *card = priv->card;

	/* Assert the reset until the card notices */
	ioग_लिखो16(8, card->bridge_io + 2);
	ioपढ़ो16(card->attr_io + COR_OFFSET);
	ioग_लिखो16(0x80, card->attr_io + COR_OFFSET);
	mdelay(1);

	/* Give समय क्रम the card to recover from this hard efक्रमt */
	ioग_लिखो16(0, card->attr_io + COR_OFFSET);
	ioग_लिखो16(0, card->attr_io + COR_OFFSET);
	mdelay(1);

	/* Set COR as usual */
	ioग_लिखो16(COR_VALUE, card->attr_io + COR_OFFSET);
	ioग_लिखो16(COR_VALUE, card->attr_io + COR_OFFSET);
	mdelay(1);

	ioग_लिखो16(0x228, card->bridge_io + 2);

	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_nortel_hw_init(काष्ठा orinoco_pci_card *card)
अणु
	पूर्णांक i;
	u32 reg;

	/* Setup bridge */
	अगर (ioपढ़ो16(card->bridge_io) & 1) अणु
		prपूर्णांकk(KERN_ERR PFX "brg1 answer1 wrong\n");
		वापस -EBUSY;
	पूर्ण
	ioग_लिखो16(0x118, card->bridge_io + 2);
	ioग_लिखो16(0x108, card->bridge_io + 2);
	mdelay(30);
	ioग_लिखो16(0x8, card->bridge_io + 2);
	क्रम (i = 0; i < 30; i++) अणु
		mdelay(30);
		अगर (ioपढ़ो16(card->bridge_io) & 0x10)
			अवरोध;
	पूर्ण
	अगर (i == 30) अणु
		prपूर्णांकk(KERN_ERR PFX "brg1 timed out\n");
		वापस -EBUSY;
	पूर्ण
	अगर (ioपढ़ो16(card->attr_io + COR_OFFSET) & 1) अणु
		prपूर्णांकk(KERN_ERR PFX "brg2 answer1 wrong\n");
		वापस -EBUSY;
	पूर्ण
	अगर (ioपढ़ो16(card->attr_io + COR_OFFSET + 2) & 1) अणु
		prपूर्णांकk(KERN_ERR PFX "brg2 answer2 wrong\n");
		वापस -EBUSY;
	पूर्ण
	अगर (ioपढ़ो16(card->attr_io + COR_OFFSET + 4) & 1) अणु
		prपूर्णांकk(KERN_ERR PFX "brg2 answer3 wrong\n");
		वापस -EBUSY;
	पूर्ण

	/* Set the PCMCIA COR रेजिस्टर */
	ioग_लिखो16(COR_VALUE, card->attr_io + COR_OFFSET);
	mdelay(1);
	reg = ioपढ़ो16(card->attr_io + COR_OFFSET);
	अगर (reg != COR_VALUE) अणु
		prपूर्णांकk(KERN_ERR PFX "Error setting COR value (reg=%x)\n",
		       reg);
		वापस -EBUSY;
	पूर्ण

	/* Set LEDs */
	ioग_लिखो16(1, card->bridge_io + 10);
	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_nortel_init_one(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	काष्ठा orinoco_निजी *priv;
	काष्ठा orinoco_pci_card *card;
	व्योम __iomem *hermes_io, *bridge_io, *attr_io;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot enable PCI device\n");
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, DRIVER_NAME);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot obtain PCI resources\n");
		जाओ fail_resources;
	पूर्ण

	bridge_io = pci_iomap(pdev, 0, 0);
	अगर (!bridge_io) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot map bridge registers\n");
		err = -EIO;
		जाओ fail_map_bridge;
	पूर्ण

	attr_io = pci_iomap(pdev, 1, 0);
	अगर (!attr_io) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot map PCMCIA attributes\n");
		err = -EIO;
		जाओ fail_map_attr;
	पूर्ण

	hermes_io = pci_iomap(pdev, 2, 0);
	अगर (!hermes_io) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot map chipset registers\n");
		err = -EIO;
		जाओ fail_map_hermes;
	पूर्ण

	/* Allocate network device */
	priv = alloc_orinocodev(माप(*card), &pdev->dev,
				orinoco_nortel_cor_reset, शून्य);
	अगर (!priv) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate network device\n");
		err = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	card = priv->card;
	card->bridge_io = bridge_io;
	card->attr_io = attr_io;

	hermes_काष्ठा_init(&priv->hw, hermes_io, HERMES_16BIT_REGSPACING);

	err = request_irq(pdev->irq, orinoco_पूर्णांकerrupt, IRQF_SHARED,
			  DRIVER_NAME, priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate IRQ %d\n", pdev->irq);
		err = -EBUSY;
		जाओ fail_irq;
	पूर्ण

	err = orinoco_nortel_hw_init(card);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Hardware initialization failed\n");
		जाओ fail;
	पूर्ण

	err = orinoco_nortel_cor_reset(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Initial reset failed\n");
		जाओ fail;
	पूर्ण

	err = orinoco_init(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "orinoco_init() failed\n");
		जाओ fail;
	पूर्ण

	err = orinoco_अगर_add(priv, 0, 0, शून्य);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "orinoco_if_add() failed\n");
		जाओ fail_wiphy;
	पूर्ण

	pci_set_drvdata(pdev, priv);

	वापस 0;

 fail_wiphy:
	wiphy_unरेजिस्टर(priv_to_wiphy(priv));
 fail:
	मुक्त_irq(pdev->irq, priv);

 fail_irq:
	मुक्त_orinocodev(priv);

 fail_alloc:
	pci_iounmap(pdev, hermes_io);

 fail_map_hermes:
	pci_iounmap(pdev, attr_io);

 fail_map_attr:
	pci_iounmap(pdev, bridge_io);

 fail_map_bridge:
	pci_release_regions(pdev);

 fail_resources:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम orinoco_nortel_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा orinoco_निजी *priv = pci_get_drvdata(pdev);
	काष्ठा orinoco_pci_card *card = priv->card;

	/* Clear LEDs */
	ioग_लिखो16(0, card->bridge_io + 10);

	orinoco_अगर_del(priv);
	wiphy_unरेजिस्टर(priv_to_wiphy(priv));
	मुक्त_irq(pdev->irq, priv);
	मुक्त_orinocodev(priv);
	pci_iounmap(pdev, priv->hw.iobase);
	pci_iounmap(pdev, card->attr_io);
	pci_iounmap(pdev, card->bridge_io);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id orinoco_nortel_id_table[] = अणु
	/* Nortel emobility PCI */
	अणु0x126c, 0x8030, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	/* Symbol LA-4123 PCI */
	अणु0x1562, 0x0001, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, orinoco_nortel_id_table);

अटल काष्ठा pci_driver orinoco_nortel_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= orinoco_nortel_id_table,
	.probe		= orinoco_nortel_init_one,
	.हटाओ		= orinoco_nortel_हटाओ_one,
	.driver.pm	= &orinoco_pci_pm_ops,
पूर्ण;

अटल अक्षर version[] __initdata = DRIVER_NAME " " DRIVER_VERSION
	" (Tobias Hoffmann & Christoph Jungegger <disdos@traum404.de>)";
MODULE_AUTHOR("Christoph Jungegger <disdos@traum404.de>");
MODULE_DESCRIPTION("Driver for wireless LAN cards using the Nortel PCI bridge");
MODULE_LICENSE("Dual MPL/GPL");

अटल पूर्णांक __init orinoco_nortel_init(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "%s\n", version);
	वापस pci_रेजिस्टर_driver(&orinoco_nortel_driver);
पूर्ण

अटल व्योम __निकास orinoco_nortel_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&orinoco_nortel_driver);
पूर्ण

module_init(orinoco_nortel_init);
module_निकास(orinoco_nortel_निकास);
