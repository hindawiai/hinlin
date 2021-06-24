<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम DAS008 PCMCIA boards
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 * Copyright (C) 2001,2002,2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * PCMCIA support code क्रम this driver is adapted from the dummy_cs.c
 * driver of the Linux PCMCIA Card Services package.
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 */

/*
 * Driver: das08_cs
 * Description: DAS-08 PCMCIA boards
 * Author: Warren Jasper, ds, Frank Hess
 * Devices: [ComputerBoards] PCM-DAS08 (pcm-das08)
 * Status: works
 *
 * This is the PCMCIA-specअगरic support split off from the
 * das08 driver.
 *
 * Configuration Options: none, uses PCMCIA स्वतः config
 *
 * Command support करोes not exist, but could be added क्रम this board.
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pcmcia.h"

#समावेश "das08.h"

अटल स्थिर काष्ठा das08_board_काष्ठा das08_cs_boards[] = अणु
	अणु
		.name		= "pcm-das08",
		.ai_nbits	= 12,
		.ai_pg		= das08_bipolar5,
		.ai_encoding	= das08_pcm_encode12,
		.di_nchan	= 3,
		.करो_nchan	= 3,
		.iosize		= 16,
	पूर्ण,
पूर्ण;

अटल पूर्णांक das08_cs_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context)
अणु
	काष्ठा pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	काष्ठा das08_निजी_काष्ठा *devpriv;
	अचिन्हित दीर्घ iobase;
	पूर्णांक ret;

	/* The das08 driver needs the board_ptr */
	dev->board_ptr = &das08_cs_boards[0];

	link->config_flags |= CONF_AUTO_SET_IO;
	ret = comedi_pcmcia_enable(dev, शून्य);
	अगर (ret)
		वापस ret;
	iobase = link->resource[0]->start;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	वापस das08_common_attach(dev, iobase);
पूर्ण

अटल काष्ठा comedi_driver driver_das08_cs = अणु
	.driver_name	= "das08_cs",
	.module		= THIS_MODULE,
	.स्वतः_attach	= das08_cs_स्वतः_attach,
	.detach		= comedi_pcmcia_disable,
पूर्ण;

अटल पूर्णांक das08_pcmcia_attach(काष्ठा pcmcia_device *link)
अणु
	वापस comedi_pcmcia_स्वतः_config(link, &driver_das08_cs);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id das08_cs_id_table[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x01c5, 0x4001),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, das08_cs_id_table);

अटल काष्ठा pcmcia_driver das08_cs_driver = अणु
	.name		= "pcm-das08",
	.owner		= THIS_MODULE,
	.id_table	= das08_cs_id_table,
	.probe		= das08_pcmcia_attach,
	.हटाओ		= comedi_pcmcia_स्वतः_unconfig,
पूर्ण;
module_comedi_pcmcia_driver(driver_das08_cs, das08_cs_driver);

MODULE_AUTHOR("David A. Schleef <ds@schleef.org>");
MODULE_AUTHOR("Frank Mori Hess <fmhess@users.sourceforge.net>");
MODULE_DESCRIPTION("Comedi driver for ComputerBoards DAS-08 PCMCIA boards");
MODULE_LICENSE("GPL");
