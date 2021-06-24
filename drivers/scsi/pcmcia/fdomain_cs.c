<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/*
 * Driver क्रम Future Doमुख्य-compatible PCMCIA SCSI cards
 * Copyright 2019 Ondrej Zary
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <scsi/scsi_host.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश "fdomain.h"

MODULE_AUTHOR("Ondrej Zary, David Hinds");
MODULE_DESCRIPTION("Future Domain PCMCIA SCSI driver");
MODULE_LICENSE("Dual MPL/GPL");

अटल पूर्णांक fकरोमुख्य_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	p_dev->io_lines = 10;
	p_dev->resource[0]->end = FDOMAIN_REGION_SIZE;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक fकरोमुख्य_probe(काष्ठा pcmcia_device *link)
अणु
	पूर्णांक ret;
	काष्ठा Scsi_Host *sh;

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;
	link->config_regs = PRESENT_OPTION;

	ret = pcmcia_loop_config(link, fकरोमुख्य_config_check, शून्य);
	अगर (ret)
		वापस ret;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ fail_disable;

	अगर (!request_region(link->resource[0]->start, FDOMAIN_REGION_SIZE,
			    "fdomain_cs"))
		जाओ fail_disable;

	sh = fकरोमुख्य_create(link->resource[0]->start, link->irq, 7, &link->dev);
	अगर (!sh) अणु
		dev_err(&link->dev, "Controller initialization failed");
		ret = -ENODEV;
		जाओ fail_release;
	पूर्ण

	link->priv = sh;

	वापस 0;

fail_release:
	release_region(link->resource[0]->start, FDOMAIN_REGION_SIZE);
fail_disable:
	pcmcia_disable_device(link);
	वापस ret;
पूर्ण

अटल व्योम fकरोमुख्य_हटाओ(काष्ठा pcmcia_device *link)
अणु
	fकरोमुख्य_destroy(link->priv);
	release_region(link->resource[0]->start, FDOMAIN_REGION_SIZE);
	pcmcia_disable_device(link);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id fकरोमुख्य_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID12("IBM Corp.", "SCSI PCMCIA Card", 0xe3736c88,
				0x859cad20),
	PCMCIA_DEVICE_PROD_ID1("SCSI PCMCIA Adapter Card", 0x8dacb57e),
	PCMCIA_DEVICE_PROD_ID12(" SIMPLE TECHNOLOGY Corporation",
				"SCSI PCMCIA Credit Card Controller",
				0x182bdafe, 0xc80d106f),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, fकरोमुख्य_ids);

अटल काष्ठा pcmcia_driver fकरोमुख्य_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "fdomain_cs",
	.probe		= fकरोमुख्य_probe,
	.हटाओ		= fकरोमुख्य_हटाओ,
	.id_table       = fकरोमुख्य_ids,
पूर्ण;

module_pcmcia_driver(fकरोमुख्य_cs_driver);
