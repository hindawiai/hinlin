<शैली गुरु>
/*
 * Broadcom 43xx PCMCIA-SSB bridge module
 *
 * Copyright (c) 2007 Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>

अटल स्थिर काष्ठा pcmcia_device_id ssb_host_pcmcia_tbl[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x2D0, 0x448),
	PCMCIA_DEVICE_MANF_CARD(0x2D0, 0x476),
	PCMCIA_DEVICE_शून्य,
पूर्ण;

MODULE_DEVICE_TABLE(pcmcia, ssb_host_pcmcia_tbl);

अटल पूर्णांक ssb_host_pcmcia_probe(काष्ठा pcmcia_device *dev)
अणु
	काष्ठा ssb_bus *ssb;
	पूर्णांक err = -ENOMEM;
	पूर्णांक res = 0;

	ssb = kzalloc(माप(*ssb), GFP_KERNEL);
	अगर (!ssb)
		जाओ out_error;

	err = -ENODEV;

	dev->config_flags |= CONF_ENABLE_IRQ;

	dev->resource[2]->flags |=  WIN_ENABLE | WIN_DATA_WIDTH_16 |
			 WIN_USE_WAIT;
	dev->resource[2]->start = 0;
	dev->resource[2]->end = SSB_CORE_SIZE;
	res = pcmcia_request_winकरोw(dev, dev->resource[2], 250);
	अगर (res != 0)
		जाओ err_kमुक्त_ssb;

	res = pcmcia_map_mem_page(dev, dev->resource[2], 0);
	अगर (res != 0)
		जाओ err_disable;

	अगर (!dev->irq)
		जाओ err_disable;

	res = pcmcia_enable_device(dev);
	अगर (res != 0)
		जाओ err_disable;

	err = ssb_bus_pcmciabus_रेजिस्टर(ssb, dev, dev->resource[2]->start);
	अगर (err)
		जाओ err_disable;
	dev->priv = ssb;

	वापस 0;

err_disable:
	pcmcia_disable_device(dev);
err_kमुक्त_ssb:
	kमुक्त(ssb);
out_error:
	dev_err(&dev->dev, "Initialization failed (%d, %d)\n", res, err);
	वापस err;
पूर्ण

अटल व्योम ssb_host_pcmcia_हटाओ(काष्ठा pcmcia_device *dev)
अणु
	काष्ठा ssb_bus *ssb = dev->priv;

	ssb_bus_unरेजिस्टर(ssb);
	pcmcia_disable_device(dev);
	kमुक्त(ssb);
	dev->priv = शून्य;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ssb_host_pcmcia_suspend(काष्ठा pcmcia_device *dev)
अणु
	काष्ठा ssb_bus *ssb = dev->priv;

	वापस ssb_bus_suspend(ssb);
पूर्ण

अटल पूर्णांक ssb_host_pcmcia_resume(काष्ठा pcmcia_device *dev)
अणु
	काष्ठा ssb_bus *ssb = dev->priv;

	वापस ssb_bus_resume(ssb);
पूर्ण
#अन्यथा /* CONFIG_PM */
# define ssb_host_pcmcia_suspend		शून्य
# define ssb_host_pcmcia_resume		शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा pcmcia_driver ssb_host_pcmcia_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "ssb-pcmcia",
	.id_table	= ssb_host_pcmcia_tbl,
	.probe		= ssb_host_pcmcia_probe,
	.हटाओ		= ssb_host_pcmcia_हटाओ,
	.suspend	= ssb_host_pcmcia_suspend,
	.resume		= ssb_host_pcmcia_resume,
पूर्ण;

अटल पूर्णांक pcmcia_init_failed;

/*
 * These are not module init/निकास functions!
 * The module_pcmcia_driver() helper cannot be used here.
 */
पूर्णांक ssb_host_pcmcia_init(व्योम)
अणु
	pcmcia_init_failed = pcmcia_रेजिस्टर_driver(&ssb_host_pcmcia_driver);

	वापस pcmcia_init_failed;
पूर्ण

व्योम ssb_host_pcmcia_निकास(व्योम)
अणु
	अगर (!pcmcia_init_failed)
		pcmcia_unरेजिस्टर_driver(&ssb_host_pcmcia_driver);
पूर्ण
