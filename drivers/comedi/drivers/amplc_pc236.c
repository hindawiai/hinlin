<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/amplc_pc236.c
 * Driver क्रम Amplicon PC36AT DIO boards.
 *
 * Copyright (C) 2002 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */
/*
 * Driver: amplc_pc236
 * Description: Amplicon PC36AT
 * Author: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Amplicon] PC36AT (pc36at)
 * Updated: Fri, 25 Jul 2014 15:32:40 +0000
 * Status: works
 *
 * Configuration options - PC36AT:
 *   [0] - I/O port base address
 *   [1] - IRQ (optional)
 *
 * The PC36AT board has a single 8255 appearing as subdevice 0.
 *
 * Subdevice 1 pretends to be a digital input device, but it always वापसs
 * 0 when पढ़ो. However, अगर you run a command with scan_begin_src=TRIG_EXT,
 * a rising edge on port C bit 3 acts as an बाह्यal trigger, which can be
 * used to wake up tasks.  This is like the comedi_parport device, but the
 * only way to physically disable the पूर्णांकerrupt on the PC36AT is to हटाओ
 * the IRQ jumper.  If no पूर्णांकerrupt is connected, then subdevice 1 is
 * unused.
 */

#समावेश <linux/module.h>

#समावेश "../comedidev.h"

#समावेश "amplc_pc236.h"

अटल पूर्णांक pc236_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा pc236_निजी *devpriv;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x4);
	अगर (ret)
		वापस ret;

	वापस amplc_pc236_common_attach(dev, dev->iobase, it->options[1], 0);
पूर्ण

अटल स्थिर काष्ठा pc236_board pc236_boards[] = अणु
	अणु
		.name = "pc36at",
	पूर्ण,
पूर्ण;

अटल काष्ठा comedi_driver amplc_pc236_driver = अणु
	.driver_name = "amplc_pc236",
	.module = THIS_MODULE,
	.attach = pc236_attach,
	.detach = comedi_legacy_detach,
	.board_name = &pc236_boards[0].name,
	.offset = माप(काष्ठा pc236_board),
	.num_names = ARRAY_SIZE(pc236_boards),
पूर्ण;

module_comedi_driver(amplc_pc236_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Amplicon PC36AT DIO boards");
MODULE_LICENSE("GPL");
