<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/ni_usb6501.c
 * Comedi driver क्रम National Instruments USB-6501
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2014 Luca Ellero <luca.ellero@brickedbrain.com>
 */

/*
 * Driver: ni_usb6501
 * Description: National Instruments USB-6501 module
 * Devices: [National Instruments] USB-6501 (ni_usb6501)
 * Author: Luca Ellero <luca.ellero@brickedbrain.com>
 * Updated: 8 Sep 2014
 * Status: works
 *
 *
 * Configuration Options:
 * none
 */

/*
 * NI-6501 - USB PROTOCOL DESCRIPTION
 *
 * Every command is composed by two USB packets:
 *	- request (out)
 *	- response (in)
 *
 * Every packet is at least 12 bytes दीर्घ, here is the meaning of
 * every field (all values are hex):
 *
 *	byte 0 is always 00
 *	byte 1 is always 01
 *	byte 2 is always 00
 *	byte 3 is the total packet length
 *
 *	byte 4 is always 00
 *	byte 5 is the total packet length - 4
 *	byte 6 is always 01
 *	byte 7 is the command
 *
 *	byte 8 is 02 (request) or 00 (response)
 *	byte 9 is 00 (response) or 10 (port request) or 20 (counter request)
 *	byte 10 is always 00
 *	byte 11 is 00 (request) or 02 (response)
 *
 * PORT PACKETS
 *
 *	CMD: 0xE READ_PORT
 *	REQ: 00 01 00 10 00 0C 01 0E 02 10 00 00 00 03 <PORT> 00
 *	RES: 00 01 00 10 00 0C 01 00 00 00 00 02 00 03 <BMAP> 00
 *
 *	CMD: 0xF WRITE_PORT
 *	REQ: 00 01 00 14 00 10 01 0F 02 10 00 00 00 03 <PORT> 00 03 <BMAP> 00 00
 *	RES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 *	CMD: 0x12 SET_PORT_सूची (0 = input, 1 = output)
 *	REQ: 00 01 00 18 00 14 01 12 02 10 00 00
 *	     00 05 <PORT 0> <PORT 1> <PORT 2> 00 05 00 00 00 00 00
 *	RES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 * COUNTER PACKETS
 *
 *	CMD 0x9: START_COUNTER
 *	REQ: 00 01 00 0C 00 08 01 09 02 20 00 00
 *	RES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 *	CMD 0xC: STOP_COUNTER
 *	REQ: 00 01 00 0C 00 08 01 0C 02 20 00 00
 *	RES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 *	CMD 0xE: READ_COUNTER
 *	REQ: 00 01 00 0C 00 08 01 0E 02 20 00 00
 *	RES: 00 01 00 10 00 0C 01 00 00 00 00 02 <u32 counter value, Big Endian>
 *
 *	CMD 0xF: WRITE_COUNTER
 *	REQ: 00 01 00 10 00 0C 01 0F 02 20 00 00 <u32 counter value, Big Endian>
 *	RES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 *
 *	Please  visit https://www.brickedbrain.com अगर you need
 *	additional inक्रमmation or have any questions.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "../comedi_usb.h"

#घोषणा	NI6501_TIMEOUT	1000

/* Port request packets */
अटल स्थिर u8 READ_PORT_REQUEST[]	= अणु0x00, 0x01, 0x00, 0x10,
					   0x00, 0x0C, 0x01, 0x0E,
					   0x02, 0x10, 0x00, 0x00,
					   0x00, 0x03, 0x00, 0x00पूर्ण;

अटल स्थिर u8 WRITE_PORT_REQUEST[]	= अणु0x00, 0x01, 0x00, 0x14,
					   0x00, 0x10, 0x01, 0x0F,
					   0x02, 0x10, 0x00, 0x00,
					   0x00, 0x03, 0x00, 0x00,
					   0x03, 0x00, 0x00, 0x00पूर्ण;

अटल स्थिर u8 SET_PORT_सूची_REQUEST[]	= अणु0x00, 0x01, 0x00, 0x18,
					   0x00, 0x14, 0x01, 0x12,
					   0x02, 0x10, 0x00, 0x00,
					   0x00, 0x05, 0x00, 0x00,
					   0x00, 0x00, 0x05, 0x00,
					   0x00, 0x00, 0x00, 0x00पूर्ण;

/* Counter request packets */
अटल स्थिर u8 START_COUNTER_REQUEST[]	= अणु0x00, 0x01, 0x00, 0x0C,
					   0x00, 0x08, 0x01, 0x09,
					   0x02, 0x20, 0x00, 0x00पूर्ण;

अटल स्थिर u8 STOP_COUNTER_REQUEST[]	= अणु0x00, 0x01, 0x00, 0x0C,
					   0x00, 0x08, 0x01, 0x0C,
					   0x02, 0x20, 0x00, 0x00पूर्ण;

अटल स्थिर u8 READ_COUNTER_REQUEST[]	= अणु0x00, 0x01, 0x00, 0x0C,
					   0x00, 0x08, 0x01, 0x0E,
					   0x02, 0x20, 0x00, 0x00पूर्ण;

अटल स्थिर u8 WRITE_COUNTER_REQUEST[]	= अणु0x00, 0x01, 0x00, 0x10,
					   0x00, 0x0C, 0x01, 0x0F,
					   0x02, 0x20, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x00पूर्ण;

/* Response packets */
अटल स्थिर u8 GENERIC_RESPONSE[]	= अणु0x00, 0x01, 0x00, 0x0C,
					   0x00, 0x08, 0x01, 0x00,
					   0x00, 0x00, 0x00, 0x02पूर्ण;

अटल स्थिर u8 READ_PORT_RESPONSE[]	= अणु0x00, 0x01, 0x00, 0x10,
					   0x00, 0x0C, 0x01, 0x00,
					   0x00, 0x00, 0x00, 0x02,
					   0x00, 0x03, 0x00, 0x00पूर्ण;

अटल स्थिर u8 READ_COUNTER_RESPONSE[]	= अणु0x00, 0x01, 0x00, 0x10,
					   0x00, 0x0C, 0x01, 0x00,
					   0x00, 0x00, 0x00, 0x02,
					   0x00, 0x00, 0x00, 0x00पूर्ण;

क्रमागत commands अणु
	READ_PORT,
	WRITE_PORT,
	SET_PORT_सूची,
	START_COUNTER,
	STOP_COUNTER,
	READ_COUNTER,
	WRITE_COUNTER
पूर्ण;

काष्ठा ni6501_निजी अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_rx;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_tx;
	काष्ठा mutex mut;
	u8 *usb_rx_buf;
	u8 *usb_tx_buf;
पूर्ण;

अटल पूर्णांक ni6501_port_command(काष्ठा comedi_device *dev, पूर्णांक command,
			       अचिन्हित पूर्णांक val, u8 *biपंचांगap)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा ni6501_निजी *devpriv = dev->निजी;
	पूर्णांक request_size, response_size;
	u8 *tx = devpriv->usb_tx_buf;
	पूर्णांक ret;

	अगर (command != SET_PORT_सूची && !biपंचांगap)
		वापस -EINVAL;

	mutex_lock(&devpriv->mut);

	चयन (command) अणु
	हाल READ_PORT:
		request_size = माप(READ_PORT_REQUEST);
		response_size = माप(READ_PORT_RESPONSE);
		स_नकल(tx, READ_PORT_REQUEST, request_size);
		tx[14] = val & 0xff;
		अवरोध;
	हाल WRITE_PORT:
		request_size = माप(WRITE_PORT_REQUEST);
		response_size = माप(GENERIC_RESPONSE);
		स_नकल(tx, WRITE_PORT_REQUEST, request_size);
		tx[14] = val & 0xff;
		tx[17] = *biपंचांगap;
		अवरोध;
	हाल SET_PORT_सूची:
		request_size = माप(SET_PORT_सूची_REQUEST);
		response_size = माप(GENERIC_RESPONSE);
		स_नकल(tx, SET_PORT_सूची_REQUEST, request_size);
		tx[14] = val & 0xff;
		tx[15] = (val >> 8) & 0xff;
		tx[16] = (val >> 16) & 0xff;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	ret = usb_bulk_msg(usb,
			   usb_sndbulkpipe(usb,
					   devpriv->ep_tx->bEndpoपूर्णांकAddress),
			   devpriv->usb_tx_buf,
			   request_size,
			   शून्य,
			   NI6501_TIMEOUT);
	अगर (ret)
		जाओ end;

	ret = usb_bulk_msg(usb,
			   usb_rcvbulkpipe(usb,
					   devpriv->ep_rx->bEndpoपूर्णांकAddress),
			   devpriv->usb_rx_buf,
			   response_size,
			   शून्य,
			   NI6501_TIMEOUT);
	अगर (ret)
		जाओ end;

	/* Check अगर results are valid */

	अगर (command == READ_PORT) अणु
		*biपंचांगap = devpriv->usb_rx_buf[14];
		/* mask biपंचांगap क्रम comparing */
		devpriv->usb_rx_buf[14] = 0x00;

		अगर (स_भेद(devpriv->usb_rx_buf, READ_PORT_RESPONSE,
			   माप(READ_PORT_RESPONSE))) अणु
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (स_भेद(devpriv->usb_rx_buf, GENERIC_RESPONSE,
			  माप(GENERIC_RESPONSE))) अणु
		ret = -EINVAL;
	पूर्ण
end:
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल पूर्णांक ni6501_counter_command(काष्ठा comedi_device *dev, पूर्णांक command,
				  u32 *val)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा ni6501_निजी *devpriv = dev->निजी;
	पूर्णांक request_size, response_size;
	u8 *tx = devpriv->usb_tx_buf;
	पूर्णांक ret;

	अगर ((command == READ_COUNTER || command ==  WRITE_COUNTER) && !val)
		वापस -EINVAL;

	mutex_lock(&devpriv->mut);

	चयन (command) अणु
	हाल START_COUNTER:
		request_size = माप(START_COUNTER_REQUEST);
		response_size = माप(GENERIC_RESPONSE);
		स_नकल(tx, START_COUNTER_REQUEST, request_size);
		अवरोध;
	हाल STOP_COUNTER:
		request_size = माप(STOP_COUNTER_REQUEST);
		response_size = माप(GENERIC_RESPONSE);
		स_नकल(tx, STOP_COUNTER_REQUEST, request_size);
		अवरोध;
	हाल READ_COUNTER:
		request_size = माप(READ_COUNTER_REQUEST);
		response_size = माप(READ_COUNTER_RESPONSE);
		स_नकल(tx, READ_COUNTER_REQUEST, request_size);
		अवरोध;
	हाल WRITE_COUNTER:
		request_size = माप(WRITE_COUNTER_REQUEST);
		response_size = माप(GENERIC_RESPONSE);
		स_नकल(tx, WRITE_COUNTER_REQUEST, request_size);
		/* Setup tx packet: bytes 12,13,14,15 hold the */
		/* u32 counter value (Big Endian)	       */
		*((__be32 *)&tx[12]) = cpu_to_be32(*val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	ret = usb_bulk_msg(usb,
			   usb_sndbulkpipe(usb,
					   devpriv->ep_tx->bEndpoपूर्णांकAddress),
			   devpriv->usb_tx_buf,
			   request_size,
			   शून्य,
			   NI6501_TIMEOUT);
	अगर (ret)
		जाओ end;

	ret = usb_bulk_msg(usb,
			   usb_rcvbulkpipe(usb,
					   devpriv->ep_rx->bEndpoपूर्णांकAddress),
			   devpriv->usb_rx_buf,
			   response_size,
			   शून्य,
			   NI6501_TIMEOUT);
	अगर (ret)
		जाओ end;

	/* Check अगर results are valid */

	अगर (command == READ_COUNTER) अणु
		पूर्णांक i;

		/* Read counter value: bytes 12,13,14,15 of rx packet */
		/* hold the u32 counter value (Big Endian)	      */
		*val = be32_to_cpu(*((__be32 *)&devpriv->usb_rx_buf[12]));

		/* mask counter value क्रम comparing */
		क्रम (i = 12; i < माप(READ_COUNTER_RESPONSE); ++i)
			devpriv->usb_rx_buf[i] = 0x00;

		अगर (स_भेद(devpriv->usb_rx_buf, READ_COUNTER_RESPONSE,
			   माप(READ_COUNTER_RESPONSE))) अणु
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (स_भेद(devpriv->usb_rx_buf, GENERIC_RESPONSE,
			  माप(GENERIC_RESPONSE))) अणु
		ret = -EINVAL;
	पूर्ण
end:
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल पूर्णांक ni6501_dio_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	ret = ni6501_port_command(dev, SET_PORT_सूची, s->io_bits, शून्य);
	अगर (ret)
		वापस ret;

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni6501_dio_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;
	u8 port;
	u8 biपंचांगap;

	mask = comedi_dio_update_state(s, data);

	क्रम (port = 0; port < 3; port++) अणु
		अगर (mask & (0xFF << port * 8)) अणु
			biपंचांगap = (s->state >> port * 8) & 0xFF;
			ret = ni6501_port_command(dev, WRITE_PORT,
						  port, &biपंचांगap);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	data[1] = 0;

	क्रम (port = 0; port < 3; port++) अणु
		ret = ni6501_port_command(dev, READ_PORT, port, &biपंचांगap);
		अगर (ret)
			वापस ret;
		data[1] |= biपंचांगap << port * 8;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni6501_cnt_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;
	u32 val = 0;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ARM:
		ret = ni6501_counter_command(dev, START_COUNTER, शून्य);
		अवरोध;
	हाल INSN_CONFIG_DISARM:
		ret = ni6501_counter_command(dev, STOP_COUNTER, शून्य);
		अवरोध;
	हाल INSN_CONFIG_RESET:
		ret = ni6501_counter_command(dev, STOP_COUNTER, शून्य);
		अगर (ret)
			अवरोध;
		ret = ni6501_counter_command(dev, WRITE_COUNTER, &val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक ni6501_cnt_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;
	u32 val;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		ret = ni6501_counter_command(dev, READ_COUNTER,	&val);
		अगर (ret)
			वापस ret;
		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni6501_cnt_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	अगर (insn->n) अणु
		u32 val = data[insn->n - 1];

		ret = ni6501_counter_command(dev, WRITE_COUNTER, &val);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni6501_alloc_usb_buffers(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni6501_निजी *devpriv = dev->निजी;
	माप_प्रकार size;

	size = usb_endpoपूर्णांक_maxp(devpriv->ep_rx);
	devpriv->usb_rx_buf = kzalloc(size, GFP_KERNEL);
	अगर (!devpriv->usb_rx_buf)
		वापस -ENOMEM;

	size = usb_endpoपूर्णांक_maxp(devpriv->ep_tx);
	devpriv->usb_tx_buf = kzalloc(size, GFP_KERNEL);
	अगर (!devpriv->usb_tx_buf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ni6501_find_endpoपूर्णांकs(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा ni6501_निजी *devpriv = dev->निजी;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc = पूर्णांकf->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	पूर्णांक i;

	अगर (अगरace_desc->desc.bNumEndpoपूर्णांकs != 2) अणु
		dev_err(dev->class_dev, "Wrong number of endpoints\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep_desc = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_is_bulk_in(ep_desc)) अणु
			अगर (!devpriv->ep_rx)
				devpriv->ep_rx = ep_desc;
			जारी;
		पूर्ण

		अगर (usb_endpoपूर्णांक_is_bulk_out(ep_desc)) अणु
			अगर (!devpriv->ep_tx)
				devpriv->ep_tx = ep_desc;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!devpriv->ep_rx || !devpriv->ep_tx)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक ni6501_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा ni6501_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	mutex_init(&devpriv->mut);
	usb_set_पूर्णांकfdata(पूर्णांकf, devpriv);

	ret = ni6501_find_endpoपूर्णांकs(dev);
	अगर (ret)
		वापस ret;

	ret = ni6501_alloc_usb_buffers(dev);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	/* Digital Input/Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= ni6501_dio_insn_bits;
	s->insn_config	= ni6501_dio_insn_config;

	/* Counter subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_LSAMPL;
	s->n_chan	= 1;
	s->maxdata	= 0xffffffff;
	s->insn_पढ़ो	= ni6501_cnt_insn_पढ़ो;
	s->insn_ग_लिखो	= ni6501_cnt_insn_ग_लिखो;
	s->insn_config	= ni6501_cnt_insn_config;

	वापस 0;
पूर्ण

अटल व्योम ni6501_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा ni6501_निजी *devpriv = dev->निजी;

	अगर (!devpriv)
		वापस;

	mutex_destroy(&devpriv->mut);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	kमुक्त(devpriv->usb_rx_buf);
	kमुक्त(devpriv->usb_tx_buf);
पूर्ण

अटल काष्ठा comedi_driver ni6501_driver = अणु
	.module		= THIS_MODULE,
	.driver_name	= "ni6501",
	.स्वतः_attach	= ni6501_स्वतः_attach,
	.detach		= ni6501_detach,
पूर्ण;

अटल पूर्णांक ni6501_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	वापस comedi_usb_स्वतः_config(पूर्णांकf, &ni6501_driver, id->driver_info);
पूर्ण

अटल स्थिर काष्ठा usb_device_id ni6501_usb_table[] = अणु
	अणु USB_DEVICE(0x3923, 0x718a) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, ni6501_usb_table);

अटल काष्ठा usb_driver ni6501_usb_driver = अणु
	.name		= "ni6501",
	.id_table	= ni6501_usb_table,
	.probe		= ni6501_usb_probe,
	.disconnect	= comedi_usb_स्वतः_unconfig,
पूर्ण;
module_comedi_usb_driver(ni6501_driver, ni6501_usb_driver);

MODULE_AUTHOR("Luca Ellero");
MODULE_DESCRIPTION("Comedi driver for National Instruments USB-6501");
MODULE_LICENSE("GPL");
