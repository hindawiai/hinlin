<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम NI PCMCIA MIO E series cards
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_mio_cs
 * Description: National Instruments DAQCard E series
 * Author: ds
 * Status: works
 * Devices: [National Instruments] DAQCard-AI-16XE-50 (ni_mio_cs),
 *   DAQCard-AI-16E-4, DAQCard-6062E, DAQCard-6024E, DAQCard-6036E
 * Updated: Thu Oct 23 19:43:17 CDT 2003
 *
 * See the notes in the ni_aपंचांगio.o driver.
 */

/*
 * The real guts of the driver is in ni_mio_common.c, which is
 * included by all the E series drivers.
 *
 * References क्रम specअगरications:
 *	341080a.pdf  DAQCard E Series Register Level Programmer Manual
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश "../comedi_pcmcia.h"
#समावेश "ni_stc.h"
#समावेश "8255.h"

/*
 *  AT specअगरic setup
 */

अटल स्थिर काष्ठा ni_board_काष्ठा ni_boards[] = अणु
	अणु
		.name		= "DAQCard-ai-16xe-50",
		.device_id	= 0x010d,
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 1024,
		.gainlkup	= ai_gain_8,
		.ai_speed	= 5000,
		.caldac		= अणु dac8800, dac8043 पूर्ण,
	पूर्ण, अणु
		.name		= "DAQCard-ai-16e-4",
		.device_id	= 0x010c,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 1024,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 4000,
		.caldac		= अणु mb88341 पूर्ण,		/* verअगरied */
	पूर्ण, अणु
		.name		= "DAQCard-6062E",
		.device_id	= 0x02c4,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 8192,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fअगरo_depth	= 2048,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1176,
		.caldac		= अणु ad8804_debug पूर्ण,	/* verअगरied */
	 पूर्ण, अणु
		/* specs incorrect! */
		.name		= "DAQCard-6024E",
		.device_id	= 0x075e,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fअगरo_depth	= 1024,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000000,
		.caldac		= अणु ad8804_debug पूर्ण,
	पूर्ण, अणु
		/* specs incorrect! */
		.name		= "DAQCard-6036E",
		.device_id	= 0x0245,
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fअगरo_depth	= 1024,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000000,
		.caldac		= अणु ad8804_debug पूर्ण,
	 पूर्ण,
#अगर 0
	अणु
		.name		= "DAQCard-6715",
		.device_id	= 0x0000,	/* unknown */
		.n_aochan	= 8,
		.ao_maxdata	= 0x0fff,
		.ao_671x	= 8192,
		.caldac		= अणु mb88341, mb88341 पूर्ण,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

#समावेश "ni_mio_common.c"

अटल स्थिर व्योम *ni_getboardtype(काष्ठा comedi_device *dev,
				   काष्ठा pcmcia_device *link)
अणु
	अटल स्थिर काष्ठा ni_board_काष्ठा *board;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ni_boards); i++) अणु
		board = &ni_boards[i];
		अगर (board->device_id == link->card_id)
			वापस board;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक mio_pcmcia_config_loop(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	पूर्णांक base, ret;

	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;

	क्रम (base = 0x000; base < 0x400; base += 0x20) अणु
		p_dev->resource[0]->start = base;
		ret = pcmcia_request_io(p_dev);
		अगर (!ret)
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक mio_cs_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context)
अणु
	काष्ठा pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	अटल स्थिर काष्ठा ni_board_काष्ठा *board;
	पूर्णांक ret;

	board = ni_getboardtype(dev, link);
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	link->config_flags |= CONF_AUTO_SET_IO | CONF_ENABLE_IRQ;
	ret = comedi_pcmcia_enable(dev, mio_pcmcia_config_loop);
	अगर (ret)
		वापस ret;
	dev->iobase = link->resource[0]->start;

	link->priv = dev;
	ret = pcmcia_request_irq(link, ni_E_पूर्णांकerrupt);
	अगर (ret)
		वापस ret;
	dev->irq = link->irq;

	ret = ni_alloc_निजी(dev);
	अगर (ret)
		वापस ret;

	वापस ni_E_init(dev, 0, 1);
पूर्ण

अटल व्योम mio_cs_detach(काष्ठा comedi_device *dev)
अणु
	mio_common_detach(dev);
	comedi_pcmcia_disable(dev);
पूर्ण

अटल काष्ठा comedi_driver driver_ni_mio_cs = अणु
	.driver_name	= "ni_mio_cs",
	.module		= THIS_MODULE,
	.स्वतः_attach	= mio_cs_स्वतः_attach,
	.detach		= mio_cs_detach,
पूर्ण;

अटल पूर्णांक cs_attach(काष्ठा pcmcia_device *link)
अणु
	वापस comedi_pcmcia_स्वतः_config(link, &driver_ni_mio_cs);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id ni_mio_cs_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x010b, 0x010d),	/* DAQCard-ai-16xe-50 */
	PCMCIA_DEVICE_MANF_CARD(0x010b, 0x010c),	/* DAQCard-ai-16e-4 */
	PCMCIA_DEVICE_MANF_CARD(0x010b, 0x02c4),	/* DAQCard-6062E */
	PCMCIA_DEVICE_MANF_CARD(0x010b, 0x075e),	/* DAQCard-6024E */
	PCMCIA_DEVICE_MANF_CARD(0x010b, 0x0245),	/* DAQCard-6036E */
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, ni_mio_cs_ids);

अटल काष्ठा pcmcia_driver ni_mio_cs_driver = अणु
	.name		= "ni_mio_cs",
	.owner		= THIS_MODULE,
	.id_table	= ni_mio_cs_ids,
	.probe		= cs_attach,
	.हटाओ		= comedi_pcmcia_स्वतः_unconfig,
पूर्ण;
module_comedi_pcmcia_driver(driver_ni_mio_cs, ni_mio_cs_driver);

MODULE_DESCRIPTION("Comedi driver for National Instruments DAQCard E series");
MODULE_AUTHOR("David A. Schleef <ds@schleef.org>");
MODULE_LICENSE("GPL");
