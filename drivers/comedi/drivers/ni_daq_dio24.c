<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम National Instruments PCMCIA DAQ-Card DIO-24
 * Copyright (C) 2002 Daniel Vecino Castel <dvecino@able.es>
 *
 * PCMCIA crap at end of file is adapted from dummy_cs.c 1.31
 * 2001/08/24 12:13:13 from the pcmcia package.
 * The initial developer of the pcmcia dummy_cs.c code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 */

/*
 * Driver: ni_daq_dio24
 * Description: National Instruments PCMCIA DAQ-Card DIO-24
 * Author: Daniel Vecino Castel <dvecino@able.es>
 * Devices: [National Instruments] PCMCIA DAQ-Card DIO-24 (ni_daq_dio24)
 * Status: ?
 * Updated: Thu, 07 Nov 2002 21:53:06 -0800
 *
 * This is just a wrapper around the 8255.o driver to properly handle
 * the PCMCIA पूर्णांकerface.
 */

#समावेश <linux/module.h>
#समावेश "../comedi_pcmcia.h"

#समावेश "8255.h"

अटल पूर्णांक dio24_स्वतः_attach(काष्ठा comedi_device *dev,
			     अचिन्हित दीर्घ context)
अणु
	काष्ठा pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	link->config_flags |= CONF_AUTO_SET_IO;
	ret = comedi_pcmcia_enable(dev, शून्य);
	अगर (ret)
		वापस ret;
	dev->iobase = link->resource[0]->start;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	/* 8255 dio */
	s = &dev->subdevices[0];
	वापस subdev_8255_init(dev, s, शून्य, 0x00);
पूर्ण

अटल काष्ठा comedi_driver driver_dio24 = अणु
	.driver_name	= "ni_daq_dio24",
	.module		= THIS_MODULE,
	.स्वतः_attach	= dio24_स्वतः_attach,
	.detach		= comedi_pcmcia_disable,
पूर्ण;

अटल पूर्णांक dio24_cs_attach(काष्ठा pcmcia_device *link)
अणु
	वापस comedi_pcmcia_स्वतः_config(link, &driver_dio24);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id dio24_cs_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x010b, 0x475c),	/* daqcard-dio24 */
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, dio24_cs_ids);

अटल काष्ठा pcmcia_driver dio24_cs_driver = अणु
	.name		= "ni_daq_dio24",
	.owner		= THIS_MODULE,
	.id_table	= dio24_cs_ids,
	.probe		= dio24_cs_attach,
	.हटाओ		= comedi_pcmcia_स्वतः_unconfig,
पूर्ण;
module_comedi_pcmcia_driver(driver_dio24, dio24_cs_driver);

MODULE_AUTHOR("Daniel Vecino Castel <dvecino@able.es>");
MODULE_DESCRIPTION(
	"Comedi driver for National Instruments PCMCIA DAQ-Card DIO-24");
MODULE_LICENSE("GPL");
