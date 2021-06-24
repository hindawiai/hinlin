<शैली गुरु>
/* orinoco_pci.c
 *
 * Driver क्रम Prism 2.5/3 devices that have a direct PCI पूर्णांकerface
 * (i.e. these are not PCMCIA cards in a PCMCIA-to-PCI bridge).
 * The card contains only one PCI region, which contains all the usual
 * hermes रेजिस्टरs, as well as the COR रेजिस्टर.
 *
 * Current मुख्यtainers are:
 *	Pavel Roskin <proski AT gnu.org>
 * and	David Gibson <hermes AT gibson.dropbear.id.au>
 *
 * Some of this code is borrowed from orinoco_plx.c
 *	Copyright (C) 2001 Daniel Barlow <dan AT telent.net>
 * Some of this code is "inspired" by linux-wlan-ng-0.1.10, but nothing
 * has been copied from it. linux-wlan-ng-0.1.10 is originally :
 *	Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 * This file originally written by:
 *	Copyright (C) 2001 Jean Tourrilhes <jt AT hpl.hp.com>
 * And is now मुख्यtained by:
 *	(C) Copyright David Gibson, IBM Corp. 2002-2003.
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

#घोषणा DRIVER_NAME "orinoco_pci"
#घोषणा PFX DRIVER_NAME ": "

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>

#समावेश "orinoco.h"
#समावेश "orinoco_pci.h"

/* Offset of the COR रेजिस्टर of the PCI card */
#घोषणा HERMES_PCI_COR		(0x26)

/* Biपंचांगask to reset the card */
#घोषणा HERMES_PCI_COR_MASK	(0x0080)

/* Magic समयouts क्रम करोing the reset.
 * Those बार are straight from wlan-ng, and it is claimed that they
 * are necessary. Alan will समाप्त me. Take your समय and grab a coffee. */
#घोषणा HERMES_PCI_COR_ONT	(250)		/* ms */
#घोषणा HERMES_PCI_COR_OFFT	(500)		/* ms */
#घोषणा HERMES_PCI_COR_BUSYT	(500)		/* ms */

/*
 * Do a soft reset of the card using the Configuration Option Register
 * We need this to get going...
 * This is the part of the code that is strongly inspired from wlan-ng
 *
 * Note : This code is करोne with irq enabled. This mean that many
 * पूर्णांकerrupts will occur जबतक we are there. This is why we use the
 * jअगरfies to regulate समय instead of a straight mdelay(). Usually we
 * need only around 245 iteration of the loop to करो 250 ms delay.
 *
 * Note bis : Don't try to access HERMES_CMD during the reset phase.
 * It just won't work !
 */
अटल पूर्णांक orinoco_pci_cor_reset(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा hermes *hw = &priv->hw;
	अचिन्हित दीर्घ समयout;
	u16 reg;

	/* Assert the reset until the card notices */
	hermes_ग_लिखो_regn(hw, PCI_COR, HERMES_PCI_COR_MASK);
	mdelay(HERMES_PCI_COR_ONT);

	/* Give समय क्रम the card to recover from this hard efक्रमt */
	hermes_ग_लिखो_regn(hw, PCI_COR, 0x0000);
	mdelay(HERMES_PCI_COR_OFFT);

	/* The card is पढ़ोy when it's no दीर्घer busy */
	समयout = jअगरfies + msecs_to_jअगरfies(HERMES_PCI_COR_BUSYT);
	reg = hermes_पढ़ो_regn(hw, CMD);
	जबतक (समय_beक्रमe(jअगरfies, समयout) && (reg & HERMES_CMD_BUSY)) अणु
		mdelay(1);
		reg = hermes_पढ़ो_regn(hw, CMD);
	पूर्ण

	/* Still busy? */
	अगर (reg & HERMES_CMD_BUSY) अणु
		prपूर्णांकk(KERN_ERR PFX "Busy timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_pci_init_one(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	काष्ठा orinoco_निजी *priv;
	काष्ठा orinoco_pci_card *card;
	व्योम __iomem *hermes_io;

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

	hermes_io = pci_iomap(pdev, 0, 0);
	अगर (!hermes_io) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot remap chipset registers\n");
		err = -EIO;
		जाओ fail_map_hermes;
	पूर्ण

	/* Allocate network device */
	priv = alloc_orinocodev(माप(*card), &pdev->dev,
				orinoco_pci_cor_reset, शून्य);
	अगर (!priv) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate network device\n");
		err = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	card = priv->card;

	hermes_काष्ठा_init(&priv->hw, hermes_io, HERMES_32BIT_REGSPACING);

	err = request_irq(pdev->irq, orinoco_पूर्णांकerrupt, IRQF_SHARED,
			  DRIVER_NAME, priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate IRQ %d\n", pdev->irq);
		err = -EBUSY;
		जाओ fail_irq;
	पूर्ण

	err = orinoco_pci_cor_reset(priv);
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
	pci_release_regions(pdev);

 fail_resources:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम orinoco_pci_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा orinoco_निजी *priv = pci_get_drvdata(pdev);

	orinoco_अगर_del(priv);
	wiphy_unरेजिस्टर(priv_to_wiphy(priv));
	मुक्त_irq(pdev->irq, priv);
	मुक्त_orinocodev(priv);
	pci_iounmap(pdev, priv->hw.iobase);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id orinoco_pci_id_table[] = अणु
	/* Intersil Prism 3 */
	अणु0x1260, 0x3872, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	/* Intersil Prism 2.5 */
	अणु0x1260, 0x3873, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	/* Samsung MagicLAN SWL-2210P */
	अणु0x167d, 0xa000, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, orinoco_pci_id_table);

अटल काष्ठा pci_driver orinoco_pci_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= orinoco_pci_id_table,
	.probe		= orinoco_pci_init_one,
	.हटाओ		= orinoco_pci_हटाओ_one,
	.driver.pm	= &orinoco_pci_pm_ops,
पूर्ण;

अटल अक्षर version[] __initdata = DRIVER_NAME " " DRIVER_VERSION
	" (Pavel Roskin <proski@gnu.org>,"
	" David Gibson <hermes@gibson.dropbear.id.au> &"
	" Jean Tourrilhes <jt@hpl.hp.com>)";
MODULE_AUTHOR("Pavel Roskin <proski@gnu.org> &"
	      " David Gibson <hermes@gibson.dropbear.id.au>");
MODULE_DESCRIPTION("Driver for wireless LAN cards using direct PCI interface");
MODULE_LICENSE("Dual MPL/GPL");

अटल पूर्णांक __init orinoco_pci_init(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "%s\n", version);
	वापस pci_रेजिस्टर_driver(&orinoco_pci_driver);
पूर्ण

अटल व्योम __निकास orinoco_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&orinoco_pci_driver);
पूर्ण

module_init(orinoco_pci_init);
module_निकास(orinoco_pci_निकास);
