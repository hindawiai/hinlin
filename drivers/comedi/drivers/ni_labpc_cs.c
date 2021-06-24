<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम National Instruments daqcard-1200 boards
 * Copyright (C) 2001, 2002, 2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * PCMCIA crap is adapted from dummy_cs.c 1.31 2001/08/24 12:13:13
 * from the pcmcia package.
 * The initial developer of the pcmcia dummy_cs.c code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.
 */

/*
 * Driver: ni_labpc_cs
 * Description: National Instruments Lab-PC (& compatibles)
 * Author: Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Devices: [National Instruments] DAQCard-1200 (daqcard-1200)
 * Status: works
 *
 * Thanks go to Fredrik Lingvall क्रम much testing and perseverance in
 * helping to debug daqcard-1200 support.
 *
 * The 1200 series boards have onboard calibration dacs क्रम correcting
 * analog input/output offsets and gains. The proper settings क्रम these
 * caldacs are stored on the board's eeprom. To पढ़ो the caldac values
 * from the eeprom and store them पूर्णांकo a file that can be then be used by
 * comedilib, use the comedi_calibrate program.
 *
 * Configuration options: none
 *
 * The daqcard-1200 has quirky chanlist requirements when scanning multiple
 * channels. Multiple channel scan sequence must start at highest channel,
 * then decrement करोwn to channel 0.  Chanlists consisting of all one channel
 * are also legal, and allow you to pace conversions in bursts.
 *
 * NI manuals:
 *   340988a (daqcard-1200)
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pcmcia.h"

#समावेश "ni_labpc.h"

अटल स्थिर काष्ठा labpc_boardinfo labpc_cs_boards[] = अणु
	अणु
		.name			= "daqcard-1200",
		.ai_speed		= 10000,
		.has_ao			= 1,
		.is_labpc1200		= 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक labpc_cs_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context)
अणु
	काष्ठा pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	पूर्णांक ret;

	/* The ni_labpc driver needs the board_ptr */
	dev->board_ptr = &labpc_cs_boards[0];

	link->config_flags |= CONF_AUTO_SET_IO |
			      CONF_ENABLE_IRQ | CONF_ENABLE_PULSE_IRQ;
	ret = comedi_pcmcia_enable(dev, शून्य);
	अगर (ret)
		वापस ret;
	dev->iobase = link->resource[0]->start;

	अगर (!link->irq)
		वापस -EINVAL;

	वापस labpc_common_attach(dev, link->irq, IRQF_SHARED);
पूर्ण

अटल व्योम labpc_cs_detach(काष्ठा comedi_device *dev)
अणु
	labpc_common_detach(dev);
	comedi_pcmcia_disable(dev);
पूर्ण

अटल काष्ठा comedi_driver driver_labpc_cs = अणु
	.driver_name	= "ni_labpc_cs",
	.module		= THIS_MODULE,
	.स्वतः_attach	= labpc_cs_स्वतः_attach,
	.detach		= labpc_cs_detach,
पूर्ण;

अटल पूर्णांक labpc_cs_attach(काष्ठा pcmcia_device *link)
अणु
	वापस comedi_pcmcia_स्वतः_config(link, &driver_labpc_cs);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id labpc_cs_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x010b, 0x0103),	/* daqcard-1200 */
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, labpc_cs_ids);

अटल काष्ठा pcmcia_driver labpc_cs_driver = अणु
	.name		= "daqcard-1200",
	.owner		= THIS_MODULE,
	.id_table	= labpc_cs_ids,
	.probe		= labpc_cs_attach,
	.हटाओ		= comedi_pcmcia_स्वतः_unconfig,
पूर्ण;
module_comedi_pcmcia_driver(driver_labpc_cs, labpc_cs_driver);

MODULE_DESCRIPTION("Comedi driver for National Instruments Lab-PC");
MODULE_AUTHOR("Frank Mori Hess <fmhess@users.sourceforge.net>");
MODULE_LICENSE("GPL");
