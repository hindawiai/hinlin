<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम NI AT-MIO E series cards
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2001 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_aपंचांगio
 * Description: National Instruments AT-MIO-E series
 * Author: ds
 * Devices: [National Instruments] AT-MIO-16E-1 (ni_aपंचांगio),
 *   AT-MIO-16E-2, AT-MIO-16E-10, AT-MIO-16DE-10, AT-MIO-64E-3,
 *   AT-MIO-16XE-50, AT-MIO-16XE-10, AT-AI-16XE-10
 * Status: works
 * Updated: Thu May  1 20:03:02 CDT 2003
 *
 * The driver has 2.6 kernel isapnp support, and will स्वतःmatically probe क्रम
 * a supported board अगर the I/O base is left unspecअगरied with comedi_config.
 * However, many of the isapnp id numbers are unknown. If your board is not
 * recognized, please send the output of 'cat /proc/isapnp' (you may need to
 * modprobe the isa-pnp module क्रम /proc/isapnp to exist) so the id numbers
 * क्रम your board can be added to the driver.
 *
 * Otherwise, you can use the isapnptools package to configure your board.
 * Use isapnp to configure the I/O base and IRQ क्रम the board, and then pass
 * the same values as parameters in comedi_config. A sample isapnp.conf file
 * is included in the etc/ directory of Comedilib.
 *
 * Comedilib includes a utility to स्वतःcalibrate these boards. The boards
 * seem to boot पूर्णांकo a state where the all calibration DACs are at one
 * extreme of their range, thus the शेष calibration is terrible.
 * Calibration at boot is strongly encouraged.
 *
 * To use the extended digital I/O on some of the boards, enable the
 * 8255 driver when configuring the Comedi source tree.
 *
 * External triggering is supported क्रम some events. The channel index
 * (scan_begin_arg, etc.) maps to PFI0 - PFI9.
 *
 * Some of the more esoteric triggering possibilities of these boards are
 * not supported.
 */

/*
 * The real guts of the driver is in ni_mio_common.c, which is included
 * both here and in ni_pcimio.c
 *
 * Interrupt support added by Truxton Fulton <trux@truxton.com>
 *
 * References क्रम specअगरications:
 *	340747b.pdf  Register Level Programmer Manual (obsolete)
 *	340747c.pdf  Register Level Programmer Manual (new)
 *		     DAQ-STC reference manual
 *
 * Other possibly relevant info:
 *	320517c.pdf  User manual (obsolete)
 *	320517f.pdf  User manual (new)
 *	320889a.pdf  delete
 *	320906c.pdf  maximum संकेत ratings
 *	321066a.pdf  about 16x
 *	321791a.pdf  discontinuation of at-mio-16e-10 rev. c
 *	321808a.pdf  about at-mio-16e-10 rev P
 *	321837a.pdf  discontinuation of at-mio-16de-10 rev d
 *	321838a.pdf  about at-mio-16de-10 rev N
 *
 * ISSUES:
 * - need to deal with बाह्यal reference क्रम DAC, and other DAC
 *   properties in board properties
 * - deal with at-mio-16de-10 revision D to N changes, etc.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "../comedidev.h"

#समावेश <linux/isapnp.h>

#समावेश "ni_stc.h"
#समावेश "8255.h"

/* AT specअगरic setup */
अटल स्थिर काष्ठा ni_board_काष्ठा ni_boards[] = अणु
	अणु
		.name		= "at-mio-16e-1",
		.device_id	= 44,
		.isapnp_id	= 0x0000,	/* XXX unknown */
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 8192,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु mb88341 पूर्ण,
	पूर्ण, अणु
		.name		= "at-mio-16e-2",
		.device_id	= 25,
		.isapnp_id	= 0x1900,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 2048,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु mb88341 पूर्ण,
	पूर्ण, अणु
		.name		= "at-mio-16e-10",
		.device_id	= 36,
		.isapnp_id	= 0x2400,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 10000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण, अणु
		.name		= "at-mio-16de-10",
		.device_id	= 37,
		.isapnp_id	= 0x2500,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 512,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 10000,
		.caldac		= अणु ad8804_debug पूर्ण,
		.has_8255	= 1,
	पूर्ण, अणु
		.name		= "at-mio-64e-3",
		.device_id	= 38,
		.isapnp_id	= 0x2600,
		.n_adchan	= 64,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 2048,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण, अणु
		.name		= "at-mio-16xe-50",
		.device_id	= 39,
		.isapnp_id	= 0x2700,
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_8,
		.ai_speed	= 50000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 50000,
		.caldac		= अणु dac8800, dac8043 पूर्ण,
	पूर्ण, अणु
		.name		= "at-mio-16xe-10",
		.device_id	= 50,
		.isapnp_id	= 0x0000,	/* XXX unknown */
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_ni_E_ao_ext,
		.ao_speed	= 1000,
		.caldac		= अणु dac8800, dac8043, ad8522 पूर्ण,
	पूर्ण, अणु
		.name		= "at-ai-16xe-10",
		.device_id	= 51,
		.isapnp_id	= 0x0000,	/* XXX unknown */
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 512,
		.alwaysdither	= 1,		/* unknown */
		.gainlkup	= ai_gain_14,
		.ai_speed	= 10000,
		.caldac		= अणु dac8800, dac8043, ad8522 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक ni_irqpin[] = अणु
	-1, -1, -1, 0, 1, 2, -1, 3, -1, -1, 4, 5, 6, -1, -1, 7
पूर्ण;

#समावेश "ni_mio_common.c"

अटल स्थिर काष्ठा pnp_device_id device_ids[] = अणु
	अणु.id = "NIC1900", .driver_data = 0पूर्ण,
	अणु.id = "NIC2400", .driver_data = 0पूर्ण,
	अणु.id = "NIC2500", .driver_data = 0पूर्ण,
	अणु.id = "NIC2600", .driver_data = 0पूर्ण,
	अणु.id = "NIC2700", .driver_data = 0पूर्ण,
	अणु.id = ""पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp, device_ids);

अटल पूर्णांक ni_isapnp_find_board(काष्ठा pnp_dev **dev)
अणु
	काष्ठा pnp_dev *isapnp_dev = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ni_boards); i++) अणु
		isapnp_dev =
			pnp_find_dev(शून्य,
				     ISAPNP_VENDOR('N', 'I', 'C'),
				     ISAPNP_FUNCTION(ni_boards[i].isapnp_id),
				     शून्य);

		अगर (!isapnp_dev || !isapnp_dev->card)
			जारी;

		अगर (pnp_device_attach(isapnp_dev) < 0)
			जारी;

		अगर (pnp_activate_dev(isapnp_dev) < 0) अणु
			pnp_device_detach(isapnp_dev);
			वापस -EAGAIN;
		पूर्ण

		अगर (!pnp_port_valid(isapnp_dev, 0) ||
		    !pnp_irq_valid(isapnp_dev, 0)) अणु
			pnp_device_detach(isapnp_dev);
			वापस -ENOMEM;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(ni_boards))
		वापस -ENODEV;
	*dev = isapnp_dev;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ni_board_काष्ठा *ni_aपंचांगio_probe(काष्ठा comedi_device *dev)
अणु
	पूर्णांक device_id = ni_पढ़ो_eeprom(dev, 511);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ni_boards); i++) अणु
		स्थिर काष्ठा ni_board_काष्ठा *board = &ni_boards[i];

		अगर (board->device_id == device_id)
			वापस board;
	पूर्ण
	अगर (device_id == 255)
		dev_err(dev->class_dev, "can't find board\n");
	अन्यथा अगर (device_id == 0)
		dev_err(dev->class_dev,
			"EEPROM read error (?) or device not found\n");
	अन्यथा
		dev_err(dev->class_dev,
			"unknown device ID %d -- contact author\n", device_id);

	वापस शून्य;
पूर्ण

अटल पूर्णांक ni_aपंचांगio_attach(काष्ठा comedi_device *dev,
			   काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board;
	काष्ठा pnp_dev *isapnp_dev;
	पूर्णांक ret;
	अचिन्हित दीर्घ iobase;
	अचिन्हित पूर्णांक irq;

	ret = ni_alloc_निजी(dev);
	अगर (ret)
		वापस ret;

	iobase = it->options[0];
	irq = it->options[1];
	isapnp_dev = शून्य;
	अगर (iobase == 0) अणु
		ret = ni_isapnp_find_board(&isapnp_dev);
		अगर (ret < 0)
			वापस ret;

		iobase = pnp_port_start(isapnp_dev, 0);
		irq = pnp_irq(isapnp_dev, 0);
		comedi_set_hw_dev(dev, &isapnp_dev->dev);
	पूर्ण

	ret = comedi_request_region(dev, iobase, 0x20);
	अगर (ret)
		वापस ret;

	board = ni_aपंचांगio_probe(dev);
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	/* irq stuff */

	अगर (irq != 0) अणु
		अगर (irq > 15 || ni_irqpin[irq] == -1)
			वापस -EINVAL;
		ret = request_irq(irq, ni_E_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret < 0)
			वापस -EINVAL;
		dev->irq = irq;
	पूर्ण

	/* generic E series stuff in ni_mio_common.c */

	ret = ni_E_init(dev, ni_irqpin[dev->irq], 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम ni_aपंचांगio_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा pnp_dev *isapnp_dev;

	mio_common_detach(dev);
	comedi_legacy_detach(dev);

	isapnp_dev = dev->hw_dev ? to_pnp_dev(dev->hw_dev) : शून्य;
	अगर (isapnp_dev)
		pnp_device_detach(isapnp_dev);
पूर्ण

अटल काष्ठा comedi_driver ni_aपंचांगio_driver = अणु
	.driver_name	= "ni_atmio",
	.module		= THIS_MODULE,
	.attach		= ni_aपंचांगio_attach,
	.detach		= ni_aपंचांगio_detach,
पूर्ण;
module_comedi_driver(ni_aपंचांगio_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");

