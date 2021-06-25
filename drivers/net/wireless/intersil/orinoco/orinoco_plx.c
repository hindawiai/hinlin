<शैली गुरु>
/* orinoco_plx.c
 *
 * Driver क्रम Prism II devices which would usually be driven by orinoco_cs,
 * but are connected to the PCI bus by a PLX9052.
 *
 * Current मुख्यtainers are:
 *	Pavel Roskin <proski AT gnu.org>
 * and	David Gibson <hermes AT gibson.dropbear.id.au>
 *
 * (C) Copyright David Gibson, IBM Corp. 2001-2003.
 * Copyright (C) 2001 Daniel Barlow
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
 * Here's the general details on how the PLX9052 adapter works:
 *
 * - Two PCI I/O address spaces, one 0x80 दीर्घ which contains the
 * PLX9052 रेजिस्टरs, and one that's 0x40 दीर्घ mapped to the PCMCIA
 * slot I/O address space.
 *
 * - One PCI memory address space, mapped to the PCMCIA attribute space
 * (containing the CIS).
 *
 * Using the later, you can पढ़ो through the CIS data to make sure the
 * card is compatible with the driver. Keep in mind that the PCMCIA
 * spec specअगरies the CIS as the lower 8 bits of each word पढ़ो from
 * the CIS, so to पढ़ो the bytes of the CIS, पढ़ो every other byte
 * (0,2,4,...). Passing that test, you need to enable the I/O address
 * space on the PCMCIA card via the PCMCIA COR रेजिस्टर. This is the
 * first byte following the CIS. In my हाल (which may not have any
 * relation to what's on the PRISM2 cards), COR was at offset 0x800
 * within the PCI memory space. Write 0x41 to the COR रेजिस्टर to
 * enable I/O mode and to select level triggered पूर्णांकerrupts. To
 * confirm you actually succeeded, पढ़ो the COR रेजिस्टर back and make
 * sure it actually got set to 0x41, in हाल you have an unexpected
 * card inserted.
 *
 * Following that, you can treat the second PCI I/O address space (the
 * one that's not 0x80 in length) as the PCMCIA I/O space.
 *
 * Note that in the Eumitcom's source क्रम their drivers, they रेजिस्टर
 * the पूर्णांकerrupt as edge triggered when रेजिस्टरing it with the
 * Winकरोws kernel. I करोn't recall how to रेजिस्टर edge triggered on
 * Linux (अगर it can be करोne at all). But in some experimentation, I
 * करोn't see much operational dअगरference between using either
 * पूर्णांकerrupt mode. Don't mess with the पूर्णांकerrupt mode in the COR
 * रेजिस्टर though, as the PLX9052 wants level triggers with the way
 * the serial EEPROM configures it on the WL11000.
 *
 * There's some other little quirks related to timing that I bumped
 * पूर्णांकo, but I करोn't recall right now. Also, there's two variants of
 * the WL11000 I've seen, revision A1 and T2. These seem to dअगरfer
 * slightly in the timings configured in the रुको-state generator in
 * the PLX9052. There have also been some comments from Eumitcom that
 * cards shouldn't be hot swapped, apparently due to risk of cooking
 * the PLX9052. I'm unsure why they believe this, as I can't see
 * anything in the design that would really cause a problem, except
 * क्रम crashing drivers not written to expect it. And having developed
 * drivers क्रम the WL11000, I'd say it's quite tricky to ग_लिखो code
 * that will successfully deal with a hot unplug. Very odd things
 * happen on the I/O side of things. But anyway, be warned. Despite
 * that, I've hot-swapped a number of बार during debugging and
 * driver development क्रम various reasons (stuck WAIT# line after the
 * radio card's firmware locks up).
 */

#घोषणा DRIVER_NAME "orinoco_plx"
#घोषणा PFX DRIVER_NAME ": "

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <pcmcia/cisreg.h>

#समावेश "orinoco.h"
#समावेश "orinoco_pci.h"

#घोषणा COR_OFFSET	(0x3e0)	/* COR attribute offset of Prism2 PC card */
#घोषणा COR_VALUE	(COR_LEVEL_REQ | COR_FUNC_ENA) /* Enable PC card with पूर्णांकerrupt in level trigger */
#घोषणा COR_RESET     (0x80)	/* reset bit in the COR रेजिस्टर */
#घोषणा PLX_RESET_TIME	(500)	/* milliseconds */

#घोषणा PLX_INTCSR		0x4c /* Interrupt Control & Status Register */
#घोषणा PLX_INTCSR_INTEN	(1 << 6) /* Interrupt Enable bit */

/*
 * Do a soft reset of the card using the Configuration Option Register
 */
अटल पूर्णांक orinoco_plx_cor_reset(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा hermes *hw = &priv->hw;
	काष्ठा orinoco_pci_card *card = priv->card;
	अचिन्हित दीर्घ समयout;
	u16 reg;

	ioग_लिखो8(COR_VALUE | COR_RESET, card->attr_io + COR_OFFSET);
	mdelay(1);

	ioग_लिखो8(COR_VALUE, card->attr_io + COR_OFFSET);
	mdelay(1);

	/* Just in हाल, रुको more until the card is no दीर्घer busy */
	समयout = jअगरfies + msecs_to_jअगरfies(PLX_RESET_TIME);
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

अटल पूर्णांक orinoco_plx_hw_init(काष्ठा orinoco_pci_card *card)
अणु
	पूर्णांक i;
	u32 csr_reg;
	अटल स्थिर u8 cis_magic[] = अणु
		0x01, 0x03, 0x00, 0x00, 0xff, 0x17, 0x04, 0x67
	पूर्ण;

	prपूर्णांकk(KERN_DEBUG PFX "CIS: ");
	क्रम (i = 0; i < 16; i++)
		prपूर्णांकk("%02X:", ioपढ़ो8(card->attr_io + (i << 1)));
	prपूर्णांकk("\n");

	/* Verअगरy whether a supported PC card is present */
	/* FIXME: we probably need to be smarted about this */
	क्रम (i = 0; i < माप(cis_magic); i++) अणु
		अगर (cis_magic[i] != ioपढ़ो8(card->attr_io + (i << 1))) अणु
			prपूर्णांकk(KERN_ERR PFX "The CIS value of Prism2 PC "
			       "card is unexpected\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* bjoern: We need to tell the card to enable पूर्णांकerrupts, in
	   हाल the serial eprom didn't करो this alपढ़ोy.  See the
	   PLX9052 data book, p8-1 and 8-24 क्रम reference. */
	csr_reg = ioपढ़ो32(card->bridge_io + PLX_INTCSR);
	अगर (!(csr_reg & PLX_INTCSR_INTEN)) अणु
		csr_reg |= PLX_INTCSR_INTEN;
		ioग_लिखो32(csr_reg, card->bridge_io + PLX_INTCSR);
		csr_reg = ioपढ़ो32(card->bridge_io + PLX_INTCSR);
		अगर (!(csr_reg & PLX_INTCSR_INTEN)) अणु
			prपूर्णांकk(KERN_ERR PFX "Cannot enable interrupts\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_plx_init_one(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	काष्ठा orinoco_निजी *priv;
	काष्ठा orinoco_pci_card *card;
	व्योम __iomem *hermes_io, *attr_io, *bridge_io;

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

	attr_io = pci_iomap(pdev, 2, 0);
	अगर (!attr_io) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot map PCMCIA attributes\n");
		err = -EIO;
		जाओ fail_map_attr;
	पूर्ण

	hermes_io = pci_iomap(pdev, 3, 0);
	अगर (!hermes_io) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot map chipset registers\n");
		err = -EIO;
		जाओ fail_map_hermes;
	पूर्ण

	/* Allocate network device */
	priv = alloc_orinocodev(माप(*card), &pdev->dev,
				orinoco_plx_cor_reset, शून्य);
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

	err = orinoco_plx_hw_init(card);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Hardware initialization failed\n");
		जाओ fail;
	पूर्ण

	err = orinoco_plx_cor_reset(priv);
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

अटल व्योम orinoco_plx_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा orinoco_निजी *priv = pci_get_drvdata(pdev);
	काष्ठा orinoco_pci_card *card = priv->card;

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

अटल स्थिर काष्ठा pci_device_id orinoco_plx_id_table[] = अणु
	अणु0x111a, 0x1023, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* Siemens SpeedStream SS1023 */
	अणु0x1385, 0x4100, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* Netgear MA301 */
	अणु0x15e8, 0x0130, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* Correga  - करोes this work? */
	अणु0x1638, 0x1100, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* SMC EZConnect SMC2602W,
							   Eumitcom PCI WL11000,
							   Addtron AWA-100 */
	अणु0x16ab, 0x1100, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* Global Sun Tech GL24110P */
	अणु0x16ab, 0x1101, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* Reported working, but unknown */
	अणु0x16ab, 0x1102, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* Linksys WDT11 */
	अणु0x16ec, 0x3685, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* USR 2415 */
	अणु0xec80, 0xec00, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* Belkin F5D6000 tested by
							   Brendan W. McAdams <rit AT jacked-in.org> */
	अणु0x10b7, 0x7770, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,	/* 3Com AirConnect PCI tested by
							   Damien Persohn <damien AT persohn.net> */
	अणु0,पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, orinoco_plx_id_table);

अटल काष्ठा pci_driver orinoco_plx_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= orinoco_plx_id_table,
	.probe		= orinoco_plx_init_one,
	.हटाओ		= orinoco_plx_हटाओ_one,
	.driver.pm	= &orinoco_pci_pm_ops,
पूर्ण;

अटल अक्षर version[] __initdata = DRIVER_NAME " " DRIVER_VERSION
	" (Pavel Roskin <proski@gnu.org>,"
	" David Gibson <hermes@gibson.dropbear.id.au>,"
	" Daniel Barlow <dan@telent.net>)";
MODULE_AUTHOR("Daniel Barlow <dan@telent.net>");
MODULE_DESCRIPTION("Driver for wireless LAN cards using the PLX9052 PCI bridge");
MODULE_LICENSE("Dual MPL/GPL");

अटल पूर्णांक __init orinoco_plx_init(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "%s\n", version);
	वापस pci_रेजिस्टर_driver(&orinoco_plx_driver);
पूर्ण

अटल व्योम __निकास orinoco_plx_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&orinoco_plx_driver);
पूर्ण

module_init(orinoco_plx_init);
module_निकास(orinoco_plx_निकास);
