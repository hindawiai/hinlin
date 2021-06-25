<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/ni_labpc.c
 * Driver क्रम National Instruments Lab-PC series boards and compatibles
 * Copyright (C) 2001-2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

/*
 * Driver: ni_labpc
 * Description: National Instruments Lab-PC (& compatibles)
 * Devices: [National Instruments] Lab-PC-1200 (lab-pc-1200),
 *   Lab-PC-1200AI (lab-pc-1200ai), Lab-PC+ (lab-pc+)
 * Author: Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Status: works
 *
 * Configuration options - ISA boards:
 *   [0] - I/O port base address
 *   [1] - IRQ (optional, required क्रम समयd or बाह्यally triggered
 *		conversions)
 *   [2] - DMA channel (optional)
 *
 * Tested with lab-pc-1200.  For the older Lab-PC+, not all input
 * ranges and analog references will work, the available ranges/arefs
 * will depend on how you have configured the jumpers on your board
 * (see your owner's manual).
 *
 * Kernel-level ISA plug-and-play support क्रम the lab-pc-1200 boards
 * has not yet been added to the driver, मुख्यly due to the fact that
 * I करोn't know the device id numbers. If you have one of these boards,
 * please file a bug report at https://comedi.org/ so I can get the
 * necessary inक्रमmation from you.
 *
 * The 1200 series boards have onboard calibration dacs क्रम correcting
 * analog input/output offsets and gains. The proper settings क्रम these
 * caldacs are stored on the board's eeprom. To पढ़ो the caldac values
 * from the eeprom and store them पूर्णांकo a file that can be then be used
 * by comedilib, use the comedi_calibrate program.
 *
 * The Lab-pc+ has quirky chanlist requirements when scanning multiple
 * channels. Multiple channel scan sequence must start at highest channel,
 * then decrement करोwn to channel 0. The rest of the cards can scan करोwn
 * like lab-pc+ or scan up from channel zero. Chanlists consisting of all
 * one channel are also legal, and allow you to pace conversions in bursts.
 *
 * NI manuals:
 * 341309a (labpc-1200 रेजिस्टर manual)
 * 320502b (lab-pc+)
 */

#समावेश <linux/module.h>

#समावेश "../comedidev.h"

#समावेश "ni_labpc.h"
#समावेश "ni_labpc_isadma.h"

अटल स्थिर काष्ठा labpc_boardinfo labpc_boards[] = अणु
	अणु
		.name			= "lab-pc-1200",
		.ai_speed		= 10000,
		.ai_scan_up		= 1,
		.has_ao			= 1,
		.is_labpc1200		= 1,
	पूर्ण, अणु
		.name			= "lab-pc-1200ai",
		.ai_speed		= 10000,
		.ai_scan_up		= 1,
		.is_labpc1200		= 1,
	पूर्ण, अणु
		.name			= "lab-pc+",
		.ai_speed		= 12000,
		.has_ao			= 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक labpc_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	अचिन्हित पूर्णांक irq = it->options[1];
	अचिन्हित पूर्णांक dma_chan = it->options[2];
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x20);
	अगर (ret)
		वापस ret;

	ret = labpc_common_attach(dev, irq, 0);
	अगर (ret)
		वापस ret;

	अगर (dev->irq)
		labpc_init_dma_chan(dev, dma_chan);

	वापस 0;
पूर्ण

अटल व्योम labpc_detach(काष्ठा comedi_device *dev)
अणु
	labpc_मुक्त_dma_chan(dev);
	labpc_common_detach(dev);
	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver labpc_driver = अणु
	.driver_name	= "ni_labpc",
	.module		= THIS_MODULE,
	.attach		= labpc_attach,
	.detach		= labpc_detach,
	.num_names	= ARRAY_SIZE(labpc_boards),
	.board_name	= &labpc_boards[0].name,
	.offset		= माप(काष्ठा labpc_boardinfo),
पूर्ण;
module_comedi_driver(labpc_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for NI Lab-PC ISA boards");
MODULE_LICENSE("GPL");
