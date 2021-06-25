<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2010
 *
 * - Kurt Van Dijck, EIA Electronics
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#समावेश "softing_platform.h"

अटल पूर्णांक softingcs_index;
अटल DEFINE_SPINLOCK(softingcs_index_lock);

अटल पूर्णांक softingcs_reset(काष्ठा platक्रमm_device *pdev, पूर्णांक v);
अटल पूर्णांक softingcs_enable_irq(काष्ठा platक्रमm_device *pdev, पूर्णांक v);

/*
 * platक्रमm_data descriptions
 */
#घोषणा MHZ (1000*1000)
अटल स्थिर काष्ठा softing_platक्रमm_data softingcs_platक्रमm_data[] = अणु
अणु
	.name = "CANcard",
	.manf = 0x0168, .prod = 0x001,
	.generation = 1,
	.nbus = 2,
	.freq = 16 * MHZ, .max_brp = 32, .max_sjw = 4,
	.dpram_size = 0x0800,
	.boot = अणु0x0000, 0x000000, fw_dir "bcard.bin",पूर्ण,
	.load = अणु0x0120, 0x00f600, fw_dir "ldcard.bin",पूर्ण,
	.app = अणु0x0010, 0x0d0000, fw_dir "cancard.bin",पूर्ण,
	.reset = softingcs_reset,
	.enable_irq = softingcs_enable_irq,
पूर्ण, अणु
	.name = "CANcard-NEC",
	.manf = 0x0168, .prod = 0x002,
	.generation = 1,
	.nbus = 2,
	.freq = 16 * MHZ, .max_brp = 32, .max_sjw = 4,
	.dpram_size = 0x0800,
	.boot = अणु0x0000, 0x000000, fw_dir "bcard.bin",पूर्ण,
	.load = अणु0x0120, 0x00f600, fw_dir "ldcard.bin",पूर्ण,
	.app = अणु0x0010, 0x0d0000, fw_dir "cancard.bin",पूर्ण,
	.reset = softingcs_reset,
	.enable_irq = softingcs_enable_irq,
पूर्ण, अणु
	.name = "CANcard-SJA",
	.manf = 0x0168, .prod = 0x004,
	.generation = 1,
	.nbus = 2,
	.freq = 20 * MHZ, .max_brp = 32, .max_sjw = 4,
	.dpram_size = 0x0800,
	.boot = अणु0x0000, 0x000000, fw_dir "bcard.bin",पूर्ण,
	.load = अणु0x0120, 0x00f600, fw_dir "ldcard.bin",पूर्ण,
	.app = अणु0x0010, 0x0d0000, fw_dir "cansja.bin",पूर्ण,
	.reset = softingcs_reset,
	.enable_irq = softingcs_enable_irq,
पूर्ण, अणु
	.name = "CANcard-2",
	.manf = 0x0168, .prod = 0x005,
	.generation = 2,
	.nbus = 2,
	.freq = 24 * MHZ, .max_brp = 64, .max_sjw = 4,
	.dpram_size = 0x1000,
	.boot = अणु0x0000, 0x000000, fw_dir "bcard2.bin",पूर्ण,
	.load = अणु0x0120, 0x00f600, fw_dir "ldcard2.bin",पूर्ण,
	.app = अणु0x0010, 0x0d0000, fw_dir "cancrd2.bin",पूर्ण,
	.reset = softingcs_reset,
	.enable_irq = शून्य,
पूर्ण, अणु
	.name = "Vector-CANcard",
	.manf = 0x0168, .prod = 0x081,
	.generation = 1,
	.nbus = 2,
	.freq = 16 * MHZ, .max_brp = 64, .max_sjw = 4,
	.dpram_size = 0x0800,
	.boot = अणु0x0000, 0x000000, fw_dir "bcard.bin",पूर्ण,
	.load = अणु0x0120, 0x00f600, fw_dir "ldcard.bin",पूर्ण,
	.app = अणु0x0010, 0x0d0000, fw_dir "cancard.bin",पूर्ण,
	.reset = softingcs_reset,
	.enable_irq = softingcs_enable_irq,
पूर्ण, अणु
	.name = "Vector-CANcard-SJA",
	.manf = 0x0168, .prod = 0x084,
	.generation = 1,
	.nbus = 2,
	.freq = 20 * MHZ, .max_brp = 32, .max_sjw = 4,
	.dpram_size = 0x0800,
	.boot = अणु0x0000, 0x000000, fw_dir "bcard.bin",पूर्ण,
	.load = अणु0x0120, 0x00f600, fw_dir "ldcard.bin",पूर्ण,
	.app = अणु0x0010, 0x0d0000, fw_dir "cansja.bin",पूर्ण,
	.reset = softingcs_reset,
	.enable_irq = softingcs_enable_irq,
पूर्ण, अणु
	.name = "Vector-CANcard-2",
	.manf = 0x0168, .prod = 0x085,
	.generation = 2,
	.nbus = 2,
	.freq = 24 * MHZ, .max_brp = 64, .max_sjw = 4,
	.dpram_size = 0x1000,
	.boot = अणु0x0000, 0x000000, fw_dir "bcard2.bin",पूर्ण,
	.load = अणु0x0120, 0x00f600, fw_dir "ldcard2.bin",पूर्ण,
	.app = अणु0x0010, 0x0d0000, fw_dir "cancrd2.bin",पूर्ण,
	.reset = softingcs_reset,
	.enable_irq = शून्य,
पूर्ण, अणु
	.name = "EDICcard-NEC",
	.manf = 0x0168, .prod = 0x102,
	.generation = 1,
	.nbus = 2,
	.freq = 16 * MHZ, .max_brp = 64, .max_sjw = 4,
	.dpram_size = 0x0800,
	.boot = अणु0x0000, 0x000000, fw_dir "bcard.bin",पूर्ण,
	.load = अणु0x0120, 0x00f600, fw_dir "ldcard.bin",पूर्ण,
	.app = अणु0x0010, 0x0d0000, fw_dir "cancard.bin",पूर्ण,
	.reset = softingcs_reset,
	.enable_irq = softingcs_enable_irq,
पूर्ण, अणु
	.name = "EDICcard-2",
	.manf = 0x0168, .prod = 0x105,
	.generation = 2,
	.nbus = 2,
	.freq = 24 * MHZ, .max_brp = 64, .max_sjw = 4,
	.dpram_size = 0x1000,
	.boot = अणु0x0000, 0x000000, fw_dir "bcard2.bin",पूर्ण,
	.load = अणु0x0120, 0x00f600, fw_dir "ldcard2.bin",पूर्ण,
	.app = अणु0x0010, 0x0d0000, fw_dir "cancrd2.bin",पूर्ण,
	.reset = softingcs_reset,
	.enable_irq = शून्य,
पूर्ण, अणु
	0, 0,
पूर्ण,
पूर्ण;

MODULE_FIRMWARE(fw_dir "bcard.bin");
MODULE_FIRMWARE(fw_dir "ldcard.bin");
MODULE_FIRMWARE(fw_dir "cancard.bin");
MODULE_FIRMWARE(fw_dir "cansja.bin");

MODULE_FIRMWARE(fw_dir "bcard2.bin");
MODULE_FIRMWARE(fw_dir "ldcard2.bin");
MODULE_FIRMWARE(fw_dir "cancrd2.bin");

अटल स्थिर काष्ठा softing_platक्रमm_data
*softingcs_find_platक्रमm_data(अचिन्हित पूर्णांक manf, अचिन्हित पूर्णांक prod)
अणु
	स्थिर काष्ठा softing_platक्रमm_data *lp;

	क्रम (lp = softingcs_platक्रमm_data; lp->manf; ++lp) अणु
		अगर ((lp->manf == manf) && (lp->prod == prod))
			वापस lp;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * platक्रमmdata callbacks
 */
अटल पूर्णांक softingcs_reset(काष्ठा platक्रमm_device *pdev, पूर्णांक v)
अणु
	काष्ठा pcmcia_device *pcmcia = to_pcmcia_dev(pdev->dev.parent);

	dev_dbg(&pdev->dev, "pcmcia config [2] %02x\n", v ? 0 : 0x20);
	वापस pcmcia_ग_लिखो_config_byte(pcmcia, 2, v ? 0 : 0x20);
पूर्ण

अटल पूर्णांक softingcs_enable_irq(काष्ठा platक्रमm_device *pdev, पूर्णांक v)
अणु
	काष्ठा pcmcia_device *pcmcia = to_pcmcia_dev(pdev->dev.parent);

	dev_dbg(&pdev->dev, "pcmcia config [0] %02x\n", v ? 0x60 : 0);
	वापस pcmcia_ग_लिखो_config_byte(pcmcia, 0, v ? 0x60 : 0);
पूर्ण

/*
 * pcmcia check
 */
अटल पूर्णांक softingcs_probe_config(काष्ठा pcmcia_device *pcmcia, व्योम *priv_data)
अणु
	काष्ठा softing_platक्रमm_data *pdat = priv_data;
	काष्ठा resource *pres;
	पूर्णांक memspeed = 0;

	WARN_ON(!pdat);
	pres = pcmcia->resource[PCMCIA_IOMEM_0];
	अगर (resource_size(pres) < 0x1000)
		वापस -दुस्फल;

	pres->flags |= WIN_MEMORY_TYPE_CM | WIN_ENABLE;
	अगर (pdat->generation < 2) अणु
		pres->flags |= WIN_USE_WAIT | WIN_DATA_WIDTH_8;
		memspeed = 3;
	पूर्ण अन्यथा अणु
		pres->flags |= WIN_DATA_WIDTH_16;
	पूर्ण
	वापस pcmcia_request_winकरोw(pcmcia, pres, memspeed);
पूर्ण

अटल व्योम softingcs_हटाओ(काष्ठा pcmcia_device *pcmcia)
अणु
	काष्ठा platक्रमm_device *pdev = pcmcia->priv;

	/* मुक्त bits */
	platक्रमm_device_unरेजिस्टर(pdev);
	/* release pcmcia stuff */
	pcmcia_disable_device(pcmcia);
पूर्ण

/*
 * platक्रमm_device wrapper
 * pdev->resource has 2 entries: io & irq
 */
अटल व्योम softingcs_pdev_release(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	kमुक्त(pdev);
पूर्ण

अटल पूर्णांक softingcs_probe(काष्ठा pcmcia_device *pcmcia)
अणु
	पूर्णांक ret;
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा softing_platक्रमm_data *pdat;
	काष्ठा resource *pres;
	काष्ठा dev अणु
		काष्ठा platक्रमm_device pdev;
		काष्ठा resource res[2];
	पूर्ण *dev;

	/* find matching platक्रमm_data */
	pdat = softingcs_find_platक्रमm_data(pcmcia->manf_id, pcmcia->card_id);
	अगर (!pdat)
		वापस -ENOTTY;

	/* setup pcmcia device */
	pcmcia->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IOMEM |
		CONF_AUTO_SET_VPP | CONF_AUTO_CHECK_VCC;
	ret = pcmcia_loop_config(pcmcia, softingcs_probe_config, (व्योम *)pdat);
	अगर (ret)
		जाओ pcmcia_failed;

	ret = pcmcia_enable_device(pcmcia);
	अगर (ret < 0)
		जाओ pcmcia_failed;

	pres = pcmcia->resource[PCMCIA_IOMEM_0];
	अगर (!pres) अणु
		ret = -EBADF;
		जाओ pcmcia_bad;
	पूर्ण

	/* create softing platक्रमm device */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ mem_failed;
	पूर्ण
	dev->pdev.resource = dev->res;
	dev->pdev.num_resources = ARRAY_SIZE(dev->res);
	dev->pdev.dev.release = softingcs_pdev_release;

	pdev = &dev->pdev;
	pdev->dev.platक्रमm_data = (व्योम *)pdat;
	pdev->dev.parent = &pcmcia->dev;
	pcmcia->priv = pdev;

	/* platक्रमm device resources */
	pdev->resource[0].flags = IORESOURCE_MEM;
	pdev->resource[0].start = pres->start;
	pdev->resource[0].end = pres->end;

	pdev->resource[1].flags = IORESOURCE_IRQ;
	pdev->resource[1].start = pcmcia->irq;
	pdev->resource[1].end = pdev->resource[1].start;

	/* platक्रमm device setup */
	spin_lock(&softingcs_index_lock);
	pdev->id = softingcs_index++;
	spin_unlock(&softingcs_index_lock);
	pdev->name = "softing";
	dev_set_name(&pdev->dev, "softingcs.%i", pdev->id);
	ret = platक्रमm_device_रेजिस्टर(pdev);
	अगर (ret < 0)
		जाओ platक्रमm_failed;

	dev_info(&pcmcia->dev, "created %s\n", dev_name(&pdev->dev));
	वापस 0;

platक्रमm_failed:
	kमुक्त(dev);
mem_failed:
pcmcia_bad:
pcmcia_failed:
	pcmcia_disable_device(pcmcia);
	pcmcia->priv = शून्य;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id softingcs_ids[] = अणु
	/* softing */
	PCMCIA_DEVICE_MANF_CARD(0x0168, 0x0001),
	PCMCIA_DEVICE_MANF_CARD(0x0168, 0x0002),
	PCMCIA_DEVICE_MANF_CARD(0x0168, 0x0004),
	PCMCIA_DEVICE_MANF_CARD(0x0168, 0x0005),
	/* vector, manufacturer? */
	PCMCIA_DEVICE_MANF_CARD(0x0168, 0x0081),
	PCMCIA_DEVICE_MANF_CARD(0x0168, 0x0084),
	PCMCIA_DEVICE_MANF_CARD(0x0168, 0x0085),
	/* EDIC */
	PCMCIA_DEVICE_MANF_CARD(0x0168, 0x0102),
	PCMCIA_DEVICE_MANF_CARD(0x0168, 0x0105),
	PCMCIA_DEVICE_शून्य,
पूर्ण;

MODULE_DEVICE_TABLE(pcmcia, softingcs_ids);

अटल काष्ठा pcmcia_driver softingcs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "softingcs",
	.id_table	= softingcs_ids,
	.probe		= softingcs_probe,
	.हटाओ		= softingcs_हटाओ,
पूर्ण;

module_pcmcia_driver(softingcs_driver);

MODULE_DESCRIPTION("softing CANcard driver"
		", links PCMCIA card to softing driver");
MODULE_LICENSE("GPL v2");
