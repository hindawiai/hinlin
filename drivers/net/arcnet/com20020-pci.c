<शैली गुरु>
/*
 * Linux ARCnet driver - COM20020 PCI support
 * Contemporary Controls PCI20 and SOHARD SH-ARC PCI
 *
 * Written 1994-1999 by Avery Pennarun,
 *    based on an ISA version by David Woodhouse.
 * Written 1999-2000 by Martin Mares <mj@ucw.cz>.
 * Derived from skeleton.c by Donald Becker.
 *
 * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)
 *  क्रम sponsoring the further development of this driver.
 *
 * **********************
 *
 * The original copyright of skeleton.c was as follows:
 *
 * skeleton.c Written 1993 by Donald Becker.
 * Copyright 1993 United States Government as represented by the
 * Director, National Security Agency.  This software may only be used
 * and distributed according to the terms of the GNU General Public License as
 * modअगरied by SRC, incorporated herein by reference.
 *
 * **********************
 *
 * For more details, see drivers/net/arcnet.c
 *
 * **********************
 */

#घोषणा pr_fmt(fmt) "arcnet:" KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>

#समावेश "arcdevice.h"
#समावेश "com20020.h"

/* Module parameters */

अटल पूर्णांक node;
अटल अक्षर device[9];		/* use eg. device="arc1" to change name */
अटल पूर्णांक समयout = 3;
अटल पूर्णांक backplane;
अटल पूर्णांक घड़ीp;
अटल पूर्णांक घड़ीm;

module_param(node, पूर्णांक, 0);
module_param_string(device, device, माप(device), 0);
module_param(समयout, पूर्णांक, 0);
module_param(backplane, पूर्णांक, 0);
module_param(घड़ीp, पूर्णांक, 0);
module_param(घड़ीm, पूर्णांक, 0);
MODULE_LICENSE("GPL");

अटल व्योम led_tx_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness value)
अणु
	काष्ठा com20020_dev *card;
	काष्ठा com20020_priv *priv;
	काष्ठा com20020_pci_card_info *ci;

	card = container_of(led_cdev, काष्ठा com20020_dev, tx_led);

	priv = card->pci_priv;
	ci = priv->ci;

	outb(!!value, priv->misc + ci->leds[card->index].green);
पूर्ण

अटल व्योम led_recon_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness value)
अणु
	काष्ठा com20020_dev *card;
	काष्ठा com20020_priv *priv;
	काष्ठा com20020_pci_card_info *ci;

	card = container_of(led_cdev, काष्ठा com20020_dev, recon_led);

	priv = card->pci_priv;
	ci = priv->ci;

	outb(!!value, priv->misc + ci->leds[card->index].red);
पूर्ण

अटल sमाप_प्रकार backplane_mode_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा net_device *net_dev = to_net_dev(dev);
	काष्ठा arcnet_local *lp = netdev_priv(net_dev);

	वापस प्र_लिखो(buf, "%s\n", lp->backplane ? "true" : "false");
पूर्ण
अटल DEVICE_ATTR_RO(backplane_mode);

अटल काष्ठा attribute *com20020_state_attrs[] = अणु
	&dev_attr_backplane_mode.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group com20020_state_group = अणु
	.name = शून्य,
	.attrs = com20020_state_attrs,
पूर्ण;

अटल व्योम com20020pci_हटाओ(काष्ठा pci_dev *pdev);

अटल पूर्णांक com20020pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा com20020_pci_card_info *ci;
	काष्ठा com20020_pci_channel_map *mm;
	काष्ठा net_device *dev;
	काष्ठा arcnet_local *lp;
	काष्ठा com20020_priv *priv;
	पूर्णांक i, ioaddr, ret;
	काष्ठा resource *r;

	ret = 0;

	अगर (pci_enable_device(pdev))
		वापस -EIO;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा com20020_priv),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ci = (काष्ठा com20020_pci_card_info *)id->driver_data;
	priv->ci = ci;
	mm = &ci->misc_map;

	pci_set_drvdata(pdev, priv);

	INIT_LIST_HEAD(&priv->list_dev);

	अगर (mm->size) अणु
		ioaddr = pci_resource_start(pdev, mm->bar) + mm->offset;
		r = devm_request_region(&pdev->dev, ioaddr, mm->size,
					"com20020-pci");
		अगर (!r) अणु
			pr_err("IO region %xh-%xh already allocated.\n",
			       ioaddr, ioaddr + mm->size - 1);
			वापस -EBUSY;
		पूर्ण
		priv->misc = ioaddr;
	पूर्ण

	क्रम (i = 0; i < ci->devcount; i++) अणु
		काष्ठा com20020_pci_channel_map *cm = &ci->chan_map_tbl[i];
		काष्ठा com20020_dev *card;
		पूर्णांक dev_id_mask = 0xf;

		dev = alloc_arcdev(device);
		अगर (!dev) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		dev->dev_port = i;

		dev->netdev_ops = &com20020_netdev_ops;

		lp = netdev_priv(dev);

		arc_prपूर्णांकk(D_NORMAL, dev, "%s Controls\n", ci->name);
		ioaddr = pci_resource_start(pdev, cm->bar) + cm->offset;

		r = devm_request_region(&pdev->dev, ioaddr, cm->size,
					"com20020-pci");
		अगर (!r) अणु
			pr_err("IO region %xh-%xh already allocated\n",
			       ioaddr, ioaddr + cm->size - 1);
			ret = -EBUSY;
			जाओ err_मुक्त_arcdev;
		पूर्ण

		/* Dummy access after Reset
		 * ARCNET controller needs
		 * this access to detect bustype
		 */
		arcnet_outb(0x00, ioaddr, COM20020_REG_W_COMMAND);
		arcnet_inb(ioaddr, COM20020_REG_R_DIAGSTAT);

		SET_NETDEV_DEV(dev, &pdev->dev);
		dev->base_addr = ioaddr;
		dev->dev_addr[0] = node;
		dev->sysfs_groups[0] = &com20020_state_group;
		dev->irq = pdev->irq;
		lp->card_name = "PCI COM20020";
		lp->card_flags = ci->flags;
		lp->backplane = backplane;
		lp->घड़ीp = घड़ीp & 7;
		lp->घड़ीm = घड़ीm & 3;
		lp->समयout = समयout;
		lp->hw.owner = THIS_MODULE;

		lp->backplane = (inb(priv->misc) >> (2 + i)) & 0x1;

		अगर (!म_भेदन(ci->name, "EAE PLX-PCI FB2", 15))
			lp->backplane = 1;

		/* Get the dev_id from the PLX rotary coder */
		अगर (!म_भेदन(ci->name, "EAE PLX-PCI MA1", 15))
			dev_id_mask = 0x3;
		dev->dev_id = (inb(priv->misc + ci->rotary) >> 4) & dev_id_mask;

		snम_लिखो(dev->name, माप(dev->name), "arc%d-%d", dev->dev_id, i);

		अगर (arcnet_inb(ioaddr, COM20020_REG_R_STATUS) == 0xFF) अणु
			pr_err("IO address %Xh is empty!\n", ioaddr);
			ret = -EIO;
			जाओ err_मुक्त_arcdev;
		पूर्ण
		अगर (com20020_check(dev)) अणु
			ret = -EIO;
			जाओ err_मुक्त_arcdev;
		पूर्ण

		card = devm_kzalloc(&pdev->dev, माप(काष्ठा com20020_dev),
				    GFP_KERNEL);
		अगर (!card) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_arcdev;
		पूर्ण

		card->index = i;
		card->pci_priv = priv;
		card->tx_led.brightness_set = led_tx_set;
		card->tx_led.शेष_trigger = devm_kaप्र_लिखो(&pdev->dev,
						GFP_KERNEL, "arc%d-%d-tx",
						dev->dev_id, i);
		card->tx_led.name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
						"pci:green:tx:%d-%d",
						dev->dev_id, i);

		card->tx_led.dev = &dev->dev;
		card->recon_led.brightness_set = led_recon_set;
		card->recon_led.शेष_trigger = devm_kaप्र_लिखो(&pdev->dev,
						GFP_KERNEL, "arc%d-%d-recon",
						dev->dev_id, i);
		card->recon_led.name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
						"pci:red:recon:%d-%d",
						dev->dev_id, i);
		card->recon_led.dev = &dev->dev;
		card->dev = dev;

		ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &card->tx_led);
		अगर (ret)
			जाओ err_मुक्त_arcdev;

		ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &card->recon_led);
		अगर (ret)
			जाओ err_मुक्त_arcdev;

		dev_set_drvdata(&dev->dev, card);

		ret = com20020_found(dev, IRQF_SHARED);
		अगर (ret)
			जाओ err_मुक्त_arcdev;

		devm_arcnet_led_init(dev, dev->dev_id, i);

		list_add(&card->list, &priv->list_dev);
		जारी;

err_मुक्त_arcdev:
		मुक्त_arcdev(dev);
		अवरोध;
	पूर्ण
	अगर (ret)
		com20020pci_हटाओ(pdev);
	वापस ret;
पूर्ण

अटल व्योम com20020pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा com20020_dev *card, *पंचांगpcard;
	काष्ठा com20020_priv *priv;

	priv = pci_get_drvdata(pdev);

	list_क्रम_each_entry_safe(card, पंचांगpcard, &priv->list_dev, list) अणु
		काष्ठा net_device *dev = card->dev;

		unरेजिस्टर_netdev(dev);
		मुक्त_irq(dev->irq, dev);
		मुक्त_arcdev(dev);
	पूर्ण
पूर्ण

अटल काष्ठा com20020_pci_card_info card_info_10mbit = अणु
	.name = "ARC-PCI",
	.devcount = 1,
	.chan_map_tbl = अणु
		अणु
			.bar = 2,
			.offset = 0x00,
			.size = 0x08,
		पूर्ण,
	पूर्ण,
	.flags = ARC_CAN_10MBIT,
पूर्ण;

अटल काष्ठा com20020_pci_card_info card_info_5mbit = अणु
	.name = "ARC-PCI",
	.devcount = 1,
	.chan_map_tbl = अणु
		अणु
			.bar = 2,
			.offset = 0x00,
			.size = 0x08,
		पूर्ण,
	पूर्ण,
	.flags = ARC_IS_5MBIT,
पूर्ण;

अटल काष्ठा com20020_pci_card_info card_info_sohard = अणु
	.name = "PLX-PCI",
	.devcount = 1,
	/* SOHARD needs PCI base addr 4 */
	.chan_map_tbl = अणु
		अणु
			.bar = 4,
			.offset = 0x00,
			.size = 0x08
		पूर्ण,
	पूर्ण,
	.flags = ARC_CAN_10MBIT,
पूर्ण;

अटल काष्ठा com20020_pci_card_info card_info_eae_arc1 = अणु
	.name = "EAE PLX-PCI ARC1",
	.devcount = 1,
	.chan_map_tbl = अणु
		अणु
			.bar = 2,
			.offset = 0x00,
			.size = 0x08,
		पूर्ण,
	पूर्ण,
	.misc_map = अणु
		.bar = 2,
		.offset = 0x10,
		.size = 0x04,
	पूर्ण,
	.leds = अणु
		अणु
			.green = 0x0,
			.red = 0x1,
		पूर्ण,
	पूर्ण,
	.rotary = 0x0,
	.flags = ARC_CAN_10MBIT,
पूर्ण;

अटल काष्ठा com20020_pci_card_info card_info_eae_ma1 = अणु
	.name = "EAE PLX-PCI MA1",
	.devcount = 2,
	.chan_map_tbl = अणु
		अणु
			.bar = 2,
			.offset = 0x00,
			.size = 0x08,
		पूर्ण, अणु
			.bar = 2,
			.offset = 0x08,
			.size = 0x08,
		पूर्ण
	पूर्ण,
	.misc_map = अणु
		.bar = 2,
		.offset = 0x10,
		.size = 0x04,
	पूर्ण,
	.leds = अणु
		अणु
			.green = 0x0,
			.red = 0x1,
		पूर्ण, अणु
			.green = 0x2,
			.red = 0x3,
		पूर्ण,
	पूर्ण,
	.rotary = 0x0,
	.flags = ARC_CAN_10MBIT,
पूर्ण;

अटल काष्ठा com20020_pci_card_info card_info_eae_fb2 = अणु
	.name = "EAE PLX-PCI FB2",
	.devcount = 1,
	.chan_map_tbl = अणु
		अणु
			.bar = 2,
			.offset = 0x00,
			.size = 0x08,
		पूर्ण,
	पूर्ण,
	.misc_map = अणु
		.bar = 2,
		.offset = 0x10,
		.size = 0x04,
	पूर्ण,
	.leds = अणु
		अणु
			.green = 0x0,
			.red = 0x1,
		पूर्ण,
	पूर्ण,
	.rotary = 0x0,
	.flags = ARC_CAN_10MBIT,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id com20020pci_id_table[] = अणु
	अणु
		0x1571, 0xa001,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		0,
	पूर्ण,
	अणु
		0x1571, 0xa002,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		0,
	पूर्ण,
	अणु
		0x1571, 0xa003,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		0
	पूर्ण,
	अणु
		0x1571, 0xa004,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		0,
	पूर्ण,
	अणु
		0x1571, 0xa005,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		0
	पूर्ण,
	अणु
		0x1571, 0xa006,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		0
	पूर्ण,
	अणु
		0x1571, 0xa007,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		0
	पूर्ण,
	अणु
		0x1571, 0xa008,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		0
	पूर्ण,
	अणु
		0x1571, 0xa009,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_5mbit
	पूर्ण,
	अणु
		0x1571, 0xa00a,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_5mbit
	पूर्ण,
	अणु
		0x1571, 0xa00b,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_5mbit
	पूर्ण,
	अणु
		0x1571, 0xa00c,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_5mbit
	पूर्ण,
	अणु
		0x1571, 0xa00d,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_5mbit
	पूर्ण,
	अणु
		0x1571, 0xa00e,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_5mbit
	पूर्ण,
	अणु
		0x1571, 0xa201,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_10mbit
	पूर्ण,
	अणु
		0x1571, 0xa202,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_10mbit
	पूर्ण,
	अणु
		0x1571, 0xa203,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_10mbit
	पूर्ण,
	अणु
		0x1571, 0xa204,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_10mbit
	पूर्ण,
	अणु
		0x1571, 0xa205,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_10mbit
	पूर्ण,
	अणु
		0x1571, 0xa206,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_10mbit
	पूर्ण,
	अणु
		0x10B5, 0x9030,
		0x10B5, 0x2978,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_sohard
	पूर्ण,
	अणु
		0x10B5, 0x9050,
		0x10B5, 0x2273,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_sohard
	पूर्ण,
	अणु
		0x10B5, 0x9050,
		0x10B5, 0x3263,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_eae_arc1
	पूर्ण,
	अणु
		0x10B5, 0x9050,
		0x10B5, 0x3292,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_eae_ma1
	पूर्ण,
	अणु
		0x10B5, 0x9050,
		0x10B5, 0x3294,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_eae_fb2
	पूर्ण,
	अणु
		0x14BA, 0x6000,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_10mbit
	पूर्ण,
	अणु
		0x10B5, 0x2200,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&card_info_10mbit
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, com20020pci_id_table);

अटल काष्ठा pci_driver com20020pci_driver = अणु
	.name		= "com20020",
	.id_table	= com20020pci_id_table,
	.probe		= com20020pci_probe,
	.हटाओ		= com20020pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init com20020pci_init(व्योम)
अणु
	अगर (BUGLVL(D_NORMAL))
		pr_info("%s\n", "COM20020 PCI support");
	वापस pci_रेजिस्टर_driver(&com20020pci_driver);
पूर्ण

अटल व्योम __निकास com20020pci_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&com20020pci_driver);
पूर्ण

module_init(com20020pci_init)
module_निकास(com20020pci_cleanup)
