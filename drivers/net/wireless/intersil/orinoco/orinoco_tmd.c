<शैली गुरु>
/* orinoco_पंचांगd.c
 *
 * Driver क्रम Prism II devices which would usually be driven by orinoco_cs,
 * but are connected to the PCI bus by a TMD7160.
 *
 * Copyright (C) 2003 Joerg Dorchain <joerg AT करोrchain.net>
 * based heavily upon orinoco_plx.c Copyright (C) 2001 Daniel Barlow
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
 *
 * The actual driving is करोne by मुख्य.c, this is just resource
 * allocation stuff.
 *
 * This driver is modeled after the orinoco_plx driver. The मुख्य
 * dअगरference is that the TMD chip has only IO port ranges and करोesn't
 * provide access to the PCMCIA attribute space.
 *
 * Pheecom sells cards with the TMD chip as "ASIC version"
 */

#घोषणा DRIVER_NAME "orinoco_tmd"
#घोषणा PFX DRIVER_NAME ": "

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <pcmcia/cisreg.h>

#समावेश "orinoco.h"
#समावेश "orinoco_pci.h"

#घोषणा COR_VALUE	(COR_LEVEL_REQ | COR_FUNC_ENA) /* Enable PC card with पूर्णांकerrupt in level trigger */
#घोषणा COR_RESET     (0x80)	/* reset bit in the COR रेजिस्टर */
#घोषणा TMD_RESET_TIME	(500)	/* milliseconds */

/*
 * Do a soft reset of the card using the Configuration Option Register
 */
अटल पूर्णांक orinoco_पंचांगd_cor_reset(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा hermes *hw = &priv->hw;
	काष्ठा orinoco_pci_card *card = priv->card;
	अचिन्हित दीर्घ समयout;
	u16 reg;

	ioग_लिखो8(COR_VALUE | COR_RESET, card->bridge_io);
	mdelay(1);

	ioग_लिखो8(COR_VALUE, card->bridge_io);
	mdelay(1);

	/* Just in हाल, रुको more until the card is no दीर्घer busy */
	समयout = jअगरfies + msecs_to_jअगरfies(TMD_RESET_TIME);
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


अटल पूर्णांक orinoco_पंचांगd_init_one(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	काष्ठा orinoco_निजी *priv;
	काष्ठा orinoco_pci_card *card;
	व्योम __iomem *hermes_io, *bridge_io;

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

	bridge_io = pci_iomap(pdev, 1, 0);
	अगर (!bridge_io) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot map bridge registers\n");
		err = -EIO;
		जाओ fail_map_bridge;
	पूर्ण

	hermes_io = pci_iomap(pdev, 2, 0);
	अगर (!hermes_io) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot map chipset registers\n");
		err = -EIO;
		जाओ fail_map_hermes;
	पूर्ण

	/* Allocate network device */
	priv = alloc_orinocodev(माप(*card), &pdev->dev,
				orinoco_पंचांगd_cor_reset, शून्य);
	अगर (!priv) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate network device\n");
		err = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	card = priv->card;
	card->bridge_io = bridge_io;

	hermes_काष्ठा_init(&priv->hw, hermes_io, HERMES_16BIT_REGSPACING);

	err = request_irq(pdev->irq, orinoco_पूर्णांकerrupt, IRQF_SHARED,
			  DRIVER_NAME, priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate IRQ %d\n", pdev->irq);
		err = -EBUSY;
		जाओ fail_irq;
	पूर्ण

	err = orinoco_पंचांगd_cor_reset(priv);
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
		जाओ fail;
	पूर्ण

	pci_set_drvdata(pdev, priv);

	वापस 0;

 fail:
	मुक्त_irq(pdev->irq, priv);

 fail_irq:
	मुक्त_orinocodev(priv);

 fail_alloc:
	pci_iounmap(pdev, hermes_io);

 fail_map_hermes:
	pci_iounmap(pdev, bridge_io);

 fail_map_bridge:
	pci_release_regions(pdev);

 fail_resources:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम orinoco_पंचांगd_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा orinoco_निजी *priv = pci_get_drvdata(pdev);
	काष्ठा orinoco_pci_card *card = priv->card;

	orinoco_अगर_del(priv);
	मुक्त_irq(pdev->irq, priv);
	मुक्त_orinocodev(priv);
	pci_iounmap(pdev, priv->hw.iobase);
	pci_iounmap(pdev, card->bridge_io);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id orinoco_पंचांगd_id_table[] = अणु
	अणु0x15e8, 0x0131, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,      /* NDC and OEMs, e.g. pheecom */
	अणु0,पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, orinoco_पंचांगd_id_table);

अटल काष्ठा pci_driver orinoco_पंचांगd_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= orinoco_पंचांगd_id_table,
	.probe		= orinoco_पंचांगd_init_one,
	.हटाओ		= orinoco_पंचांगd_हटाओ_one,
	.driver.pm	= &orinoco_pci_pm_ops,
पूर्ण;

अटल अक्षर version[] __initdata = DRIVER_NAME " " DRIVER_VERSION
	" (Joerg Dorchain <joerg@dorchain.net>)";
MODULE_AUTHOR("Joerg Dorchain <joerg@dorchain.net>");
MODULE_DESCRIPTION("Driver for wireless LAN cards using the TMD7160 PCI bridge");
MODULE_LICENSE("Dual MPL/GPL");

अटल पूर्णांक __init orinoco_पंचांगd_init(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "%s\n", version);
	वापस pci_रेजिस्टर_driver(&orinoco_पंचांगd_driver);
पूर्ण

अटल व्योम __निकास orinoco_पंचांगd_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&orinoco_पंचांगd_driver);
पूर्ण

module_init(orinoco_पंचांगd_init);
module_निकास(orinoco_पंचांगd_निकास);
