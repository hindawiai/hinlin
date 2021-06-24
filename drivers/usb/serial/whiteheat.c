<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB ConnectTech WhiteHEAT driver
 *
 *	Copyright (C) 2002
 *	    Connect Tech Inc.
 *
 *	Copyright (C) 1999 - 2001
 *	    Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/termbits.h>
#समावेश <linux/usb.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/serial.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/usb/ezusb.h>
#समावेश "whiteheat.h"			/* WhiteHEAT specअगरic commands */

#अगर_अघोषित CMSPAR
#घोषणा CMSPAR 0
#पूर्ण_अगर

/*
 * Version Inक्रमmation
 */
#घोषणा DRIVER_AUTHOR "Greg Kroah-Hartman <greg@kroah.com>, Stuart MacDonald <stuartm@connecttech.com>"
#घोषणा DRIVER_DESC "USB ConnectTech WhiteHEAT driver"

#घोषणा CONNECT_TECH_VENDOR_ID		0x0710
#घोषणा CONNECT_TECH_FAKE_WHITE_HEAT_ID	0x0001
#घोषणा CONNECT_TECH_WHITE_HEAT_ID	0x8001

/*
   ID tables क्रम whiteheat are unusual, because we want to dअगरferent
   things क्रम dअगरferent versions of the device.  Eventually, this
   will be करोable from a single table.  But, क्रम now, we define two
   separate ID tables, and then a third table that combines them
   just क्रम the purpose of exporting the स्वतःloading inक्रमmation.
*/
अटल स्थिर काष्ठा usb_device_id id_table_std[] = अणु
	अणु USB_DEVICE(CONNECT_TECH_VENDOR_ID, CONNECT_TECH_WHITE_HEAT_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_prerक्रमागतeration[] = अणु
	अणु USB_DEVICE(CONNECT_TECH_VENDOR_ID, CONNECT_TECH_FAKE_WHITE_HEAT_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_combined[] = अणु
	अणु USB_DEVICE(CONNECT_TECH_VENDOR_ID, CONNECT_TECH_WHITE_HEAT_ID) पूर्ण,
	अणु USB_DEVICE(CONNECT_TECH_VENDOR_ID, CONNECT_TECH_FAKE_WHITE_HEAT_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table_combined);


/* function prototypes क्रम the Connect Tech WhiteHEAT prerक्रमागतeration device */
अटल पूर्णांक  whiteheat_firmware_करोwnload(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id);
अटल पूर्णांक  whiteheat_firmware_attach(काष्ठा usb_serial *serial);

/* function prototypes क्रम the Connect Tech WhiteHEAT serial converter */
अटल पूर्णांक  whiteheat_attach(काष्ठा usb_serial *serial);
अटल व्योम whiteheat_release(काष्ठा usb_serial *serial);
अटल पूर्णांक  whiteheat_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम whiteheat_port_हटाओ(काष्ठा usb_serial_port *port);
अटल पूर्णांक  whiteheat_खोलो(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port);
अटल व्योम whiteheat_बंद(काष्ठा usb_serial_port *port);
अटल व्योम whiteheat_get_serial(काष्ठा tty_काष्ठा *tty,
			काष्ठा serial_काष्ठा *ss);
अटल व्योम whiteheat_set_termios(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port, काष्ठा ktermios *old);
अटल पूर्णांक  whiteheat_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक  whiteheat_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल व्योम whiteheat_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state);

अटल काष्ठा usb_serial_driver whiteheat_fake_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"whiteheatnofirm",
	पूर्ण,
	.description =		"Connect Tech - WhiteHEAT - (prerenumeration)",
	.id_table =		id_table_prerक्रमागतeration,
	.num_ports =		1,
	.probe =		whiteheat_firmware_करोwnload,
	.attach =		whiteheat_firmware_attach,
पूर्ण;

अटल काष्ठा usb_serial_driver whiteheat_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"whiteheat",
	पूर्ण,
	.description =		"Connect Tech - WhiteHEAT",
	.id_table =		id_table_std,
	.num_ports =		4,
	.num_bulk_in =		5,
	.num_bulk_out =		5,
	.attach =		whiteheat_attach,
	.release =		whiteheat_release,
	.port_probe =		whiteheat_port_probe,
	.port_हटाओ =		whiteheat_port_हटाओ,
	.खोलो =			whiteheat_खोलो,
	.बंद =		whiteheat_बंद,
	.get_serial =		whiteheat_get_serial,
	.set_termios =		whiteheat_set_termios,
	.अवरोध_ctl =		whiteheat_अवरोध_ctl,
	.tiocmget =		whiteheat_tiocmget,
	.tiocmset =		whiteheat_tiocmset,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&whiteheat_fake_device, &whiteheat_device, शून्य
पूर्ण;

काष्ठा whiteheat_command_निजी अणु
	काष्ठा mutex		mutex;
	__u8			port_running;
	__u8			command_finished;
	रुको_queue_head_t	रुको_command; /* क्रम handling sleeping whilst
						 रुकोing क्रम a command to
						 finish */
	__u8			result_buffer[64];
पूर्ण;

काष्ठा whiteheat_निजी अणु
	__u8			mcr;		/* FIXME: no locking on mcr */
पूर्ण;


/* local function prototypes */
अटल पूर्णांक start_command_port(काष्ठा usb_serial *serial);
अटल व्योम stop_command_port(काष्ठा usb_serial *serial);
अटल व्योम command_port_ग_लिखो_callback(काष्ठा urb *urb);
अटल व्योम command_port_पढ़ो_callback(काष्ठा urb *urb);

अटल पूर्णांक firm_send_command(काष्ठा usb_serial_port *port, __u8 command,
						__u8 *data, __u8 datasize);
अटल पूर्णांक firm_खोलो(काष्ठा usb_serial_port *port);
अटल पूर्णांक firm_बंद(काष्ठा usb_serial_port *port);
अटल व्योम firm_setup_port(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक firm_set_rts(काष्ठा usb_serial_port *port, __u8 onoff);
अटल पूर्णांक firm_set_dtr(काष्ठा usb_serial_port *port, __u8 onoff);
अटल पूर्णांक firm_set_अवरोध(काष्ठा usb_serial_port *port, __u8 onoff);
अटल पूर्णांक firm_purge(काष्ठा usb_serial_port *port, __u8 rxtx);
अटल पूर्णांक firm_get_dtr_rts(काष्ठा usb_serial_port *port);
अटल पूर्णांक firm_report_tx_करोne(काष्ठा usb_serial_port *port);


#घोषणा COMMAND_PORT		4
#घोषणा COMMAND_TIMEOUT		(2*HZ)	/* 2 second समयout क्रम a command */
#घोषणा	COMMAND_TIMEOUT_MS	2000


/*****************************************************************************
 * Connect Tech's White Heat prerक्रमागतeration driver functions
 *****************************************************************************/

/* steps to करोwnload the firmware to the WhiteHEAT device:
 - hold the reset (by writing to the reset bit of the CPUCS रेजिस्टर)
 - करोwnload the VEND_AX.HEX file to the chip using VENDOR_REQUEST-ANCHOR_LOAD
 - release the reset (by writing to the CPUCS रेजिस्टर)
 - करोwnload the WH.HEX file क्रम all addresses greater than 0x1b3f using
   VENDOR_REQUEST-ANCHOR_EXTERNAL_RAM_LOAD
 - hold the reset
 - करोwnload the WH.HEX file क्रम all addresses less than 0x1b40 using
   VENDOR_REQUEST_ANCHOR_LOAD
 - release the reset
 - device rक्रमागतerated itself and comes up as new device id with all
   firmware करोwnload completed.
*/
अटल पूर्णांक whiteheat_firmware_करोwnload(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक response;

	response = ezusb_fx1_ihex_firmware_करोwnload(serial->dev, "whiteheat_loader.fw");
	अगर (response >= 0) अणु
		response = ezusb_fx1_ihex_firmware_करोwnload(serial->dev, "whiteheat.fw");
		अगर (response >= 0)
			वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण


अटल पूर्णांक whiteheat_firmware_attach(काष्ठा usb_serial *serial)
अणु
	/* We want this device to fail to have a driver asचिन्हित to it */
	वापस 1;
पूर्ण


/*****************************************************************************
 * Connect Tech's White Heat serial driver functions
 *****************************************************************************/

अटल पूर्णांक whiteheat_attach(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *command_port;
	काष्ठा whiteheat_command_निजी *command_info;
	काष्ठा whiteheat_hw_info *hw_info;
	पूर्णांक pipe;
	पूर्णांक ret;
	पूर्णांक alen;
	__u8 *command;
	__u8 *result;

	command_port = serial->port[COMMAND_PORT];

	pipe = usb_sndbulkpipe(serial->dev,
			command_port->bulk_out_endpoपूर्णांकAddress);
	command = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!command)
		जाओ no_command_buffer;
	command[0] = WHITEHEAT_GET_HW_INFO;
	command[1] = 0;

	result = kदो_स्मृति(माप(*hw_info) + 1, GFP_KERNEL);
	अगर (!result)
		जाओ no_result_buffer;
	/*
	 * When the module is reloaded the firmware is still there and
	 * the endpoपूर्णांकs are still in the usb core unchanged. This is the
	 * unlinking bug in disguise. Same क्रम the call below.
	 */
	usb_clear_halt(serial->dev, pipe);
	ret = usb_bulk_msg(serial->dev, pipe, command, 2,
						&alen, COMMAND_TIMEOUT_MS);
	अगर (ret) अणु
		dev_err(&serial->dev->dev, "%s: Couldn't send command [%d]\n",
			serial->type->description, ret);
		जाओ no_firmware;
	पूर्ण अन्यथा अगर (alen != 2) अणु
		dev_err(&serial->dev->dev, "%s: Send command incomplete [%d]\n",
			serial->type->description, alen);
		जाओ no_firmware;
	पूर्ण

	pipe = usb_rcvbulkpipe(serial->dev,
				command_port->bulk_in_endpoपूर्णांकAddress);
	/* See the comment on the usb_clear_halt() above */
	usb_clear_halt(serial->dev, pipe);
	ret = usb_bulk_msg(serial->dev, pipe, result,
			माप(*hw_info) + 1, &alen, COMMAND_TIMEOUT_MS);
	अगर (ret) अणु
		dev_err(&serial->dev->dev, "%s: Couldn't get results [%d]\n",
			serial->type->description, ret);
		जाओ no_firmware;
	पूर्ण अन्यथा अगर (alen != माप(*hw_info) + 1) अणु
		dev_err(&serial->dev->dev, "%s: Get results incomplete [%d]\n",
			serial->type->description, alen);
		जाओ no_firmware;
	पूर्ण अन्यथा अगर (result[0] != command[0]) अणु
		dev_err(&serial->dev->dev, "%s: Command failed [%d]\n",
			serial->type->description, result[0]);
		जाओ no_firmware;
	पूर्ण

	hw_info = (काष्ठा whiteheat_hw_info *)&result[1];

	dev_info(&serial->dev->dev, "%s: Firmware v%d.%02d\n",
		 serial->type->description,
		 hw_info->sw_major_rev, hw_info->sw_minor_rev);

	command_info = kदो_स्मृति(माप(काष्ठा whiteheat_command_निजी),
								GFP_KERNEL);
	अगर (!command_info)
		जाओ no_command_निजी;

	mutex_init(&command_info->mutex);
	command_info->port_running = 0;
	init_रुकोqueue_head(&command_info->रुको_command);
	usb_set_serial_port_data(command_port, command_info);
	command_port->ग_लिखो_urb->complete = command_port_ग_लिखो_callback;
	command_port->पढ़ो_urb->complete = command_port_पढ़ो_callback;
	kमुक्त(result);
	kमुक्त(command);

	वापस 0;

no_firmware:
	/* Firmware likely not running */
	dev_err(&serial->dev->dev,
		"%s: Unable to retrieve firmware version, try replugging\n",
		serial->type->description);
	dev_err(&serial->dev->dev,
		"%s: If the firmware is not running (status led not blinking)\n",
		serial->type->description);
	dev_err(&serial->dev->dev,
		"%s: please contact support@connecttech.com\n",
		serial->type->description);
	kमुक्त(result);
	kमुक्त(command);
	वापस -ENODEV;

no_command_निजी:
	kमुक्त(result);
no_result_buffer:
	kमुक्त(command);
no_command_buffer:
	वापस -ENOMEM;
पूर्ण

अटल व्योम whiteheat_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *command_port;

	/* मुक्त up our निजी data क्रम our command port */
	command_port = serial->port[COMMAND_PORT];
	kमुक्त(usb_get_serial_port_data(command_port));
पूर्ण

अटल पूर्णांक whiteheat_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा whiteheat_निजी *info;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	usb_set_serial_port_data(port, info);

	वापस 0;
पूर्ण

अटल व्योम whiteheat_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा whiteheat_निजी *info;

	info = usb_get_serial_port_data(port);
	kमुक्त(info);
पूर्ण

अटल पूर्णांक whiteheat_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	पूर्णांक retval;

	retval = start_command_port(port->serial);
	अगर (retval)
		जाओ निकास;

	/* send an खोलो port command */
	retval = firm_खोलो(port);
	अगर (retval) अणु
		stop_command_port(port->serial);
		जाओ निकास;
	पूर्ण

	retval = firm_purge(port, WHITEHEAT_PURGE_RX | WHITEHEAT_PURGE_TX);
	अगर (retval) अणु
		firm_बंद(port);
		stop_command_port(port->serial);
		जाओ निकास;
	पूर्ण

	अगर (tty)
		firm_setup_port(tty);

	/* Work around HCD bugs */
	usb_clear_halt(port->serial->dev, port->पढ़ो_urb->pipe);
	usb_clear_halt(port->serial->dev, port->ग_लिखो_urb->pipe);

	retval = usb_serial_generic_खोलो(tty, port);
	अगर (retval) अणु
		firm_बंद(port);
		stop_command_port(port->serial);
		जाओ निकास;
	पूर्ण
निकास:
	वापस retval;
पूर्ण


अटल व्योम whiteheat_बंद(काष्ठा usb_serial_port *port)
अणु
	firm_report_tx_करोne(port);
	firm_बंद(port);

	usb_serial_generic_बंद(port);

	stop_command_port(port->serial);
पूर्ण

अटल पूर्णांक whiteheat_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा whiteheat_निजी *info = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक modem_संकेतs = 0;

	firm_get_dtr_rts(port);
	अगर (info->mcr & UART_MCR_DTR)
		modem_संकेतs |= TIOCM_DTR;
	अगर (info->mcr & UART_MCR_RTS)
		modem_संकेतs |= TIOCM_RTS;

	वापस modem_संकेतs;
पूर्ण

अटल पूर्णांक whiteheat_tiocmset(काष्ठा tty_काष्ठा *tty,
			       अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा whiteheat_निजी *info = usb_get_serial_port_data(port);

	अगर (set & TIOCM_RTS)
		info->mcr |= UART_MCR_RTS;
	अगर (set & TIOCM_DTR)
		info->mcr |= UART_MCR_DTR;

	अगर (clear & TIOCM_RTS)
		info->mcr &= ~UART_MCR_RTS;
	अगर (clear & TIOCM_DTR)
		info->mcr &= ~UART_MCR_DTR;

	firm_set_dtr(port, info->mcr & UART_MCR_DTR);
	firm_set_rts(port, info->mcr & UART_MCR_RTS);
	वापस 0;
पूर्ण


अटल व्योम whiteheat_get_serial(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	ss->baud_base = 460800;
पूर्ण


अटल व्योम whiteheat_set_termios(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	firm_setup_port(tty);
पूर्ण

अटल व्योम whiteheat_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	firm_set_अवरोध(port, अवरोध_state);
पूर्ण


/*****************************************************************************
 * Connect Tech's White Heat callback routines
 *****************************************************************************/
अटल व्योम command_port_ग_लिखो_callback(काष्ठा urb *urb)
अणु
	पूर्णांक status = urb->status;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "nonzero urb status: %d\n", status);
		वापस;
	पूर्ण
पूर्ण


अटल व्योम command_port_पढ़ो_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *command_port = urb->context;
	काष्ठा whiteheat_command_निजी *command_info;
	पूर्णांक status = urb->status;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक result;

	command_info = usb_get_serial_port_data(command_port);
	अगर (!command_info) अणु
		dev_dbg(&urb->dev->dev, "%s - command_info is NULL, exiting.\n", __func__);
		वापस;
	पूर्ण
	अगर (!urb->actual_length) अणु
		dev_dbg(&urb->dev->dev, "%s - empty response, exiting.\n", __func__);
		वापस;
	पूर्ण
	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero urb status: %d\n", __func__, status);
		अगर (status != -ENOENT)
			command_info->command_finished = WHITEHEAT_CMD_FAILURE;
		wake_up(&command_info->रुको_command);
		वापस;
	पूर्ण

	usb_serial_debug_data(&command_port->dev, __func__, urb->actual_length, data);

	अगर (data[0] == WHITEHEAT_CMD_COMPLETE) अणु
		command_info->command_finished = WHITEHEAT_CMD_COMPLETE;
		wake_up(&command_info->रुको_command);
	पूर्ण अन्यथा अगर (data[0] == WHITEHEAT_CMD_FAILURE) अणु
		command_info->command_finished = WHITEHEAT_CMD_FAILURE;
		wake_up(&command_info->रुको_command);
	पूर्ण अन्यथा अगर (data[0] == WHITEHEAT_EVENT) अणु
		/* These are unsolicited reports from the firmware, hence no
		   रुकोing command to wakeup */
		dev_dbg(&urb->dev->dev, "%s - event received\n", __func__);
	पूर्ण अन्यथा अगर ((data[0] == WHITEHEAT_GET_DTR_RTS) &&
		(urb->actual_length - 1 <= माप(command_info->result_buffer))) अणु
		स_नकल(command_info->result_buffer, &data[1],
						urb->actual_length - 1);
		command_info->command_finished = WHITEHEAT_CMD_COMPLETE;
		wake_up(&command_info->रुको_command);
	पूर्ण अन्यथा
		dev_dbg(&urb->dev->dev, "%s - bad reply from firmware\n", __func__);

	/* Continue trying to always पढ़ो */
	result = usb_submit_urb(command_port->पढ़ो_urb, GFP_ATOMIC);
	अगर (result)
		dev_dbg(&urb->dev->dev, "%s - failed resubmitting read urb, error %d\n",
			__func__, result);
पूर्ण


/*****************************************************************************
 * Connect Tech's White Heat firmware पूर्णांकerface
 *****************************************************************************/
अटल पूर्णांक firm_send_command(काष्ठा usb_serial_port *port, __u8 command,
						__u8 *data, __u8 datasize)
अणु
	काष्ठा usb_serial_port *command_port;
	काष्ठा whiteheat_command_निजी *command_info;
	काष्ठा whiteheat_निजी *info;
	काष्ठा device *dev = &port->dev;
	__u8 *transfer_buffer;
	पूर्णांक retval = 0;
	पूर्णांक t;

	dev_dbg(dev, "%s - command %d\n", __func__, command);

	command_port = port->serial->port[COMMAND_PORT];
	command_info = usb_get_serial_port_data(command_port);

	अगर (command_port->bulk_out_size < datasize + 1)
		वापस -EIO;

	mutex_lock(&command_info->mutex);
	command_info->command_finished = false;

	transfer_buffer = (__u8 *)command_port->ग_लिखो_urb->transfer_buffer;
	transfer_buffer[0] = command;
	स_नकल(&transfer_buffer[1], data, datasize);
	command_port->ग_लिखो_urb->transfer_buffer_length = datasize + 1;
	retval = usb_submit_urb(command_port->ग_लिखो_urb, GFP_NOIO);
	अगर (retval) अणु
		dev_dbg(dev, "%s - submit urb failed\n", __func__);
		जाओ निकास;
	पूर्ण

	/* रुको क्रम the command to complete */
	t = रुको_event_समयout(command_info->रुको_command,
		(bool)command_info->command_finished, COMMAND_TIMEOUT);
	अगर (!t)
		usb_समाप्त_urb(command_port->ग_लिखो_urb);

	अगर (command_info->command_finished == false) अणु
		dev_dbg(dev, "%s - command timed out.\n", __func__);
		retval = -ETIMEDOUT;
		जाओ निकास;
	पूर्ण

	अगर (command_info->command_finished == WHITEHEAT_CMD_FAILURE) अणु
		dev_dbg(dev, "%s - command failed.\n", __func__);
		retval = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (command_info->command_finished == WHITEHEAT_CMD_COMPLETE) अणु
		dev_dbg(dev, "%s - command completed.\n", __func__);
		चयन (command) अणु
		हाल WHITEHEAT_GET_DTR_RTS:
			info = usb_get_serial_port_data(port);
			स_नकल(&info->mcr, command_info->result_buffer,
					माप(काष्ठा whiteheat_dr_info));
				अवरोध;
		पूर्ण
	पूर्ण
निकास:
	mutex_unlock(&command_info->mutex);
	वापस retval;
पूर्ण


अटल पूर्णांक firm_खोलो(काष्ठा usb_serial_port *port)
अणु
	काष्ठा whiteheat_simple खोलो_command;

	खोलो_command.port = port->port_number + 1;
	वापस firm_send_command(port, WHITEHEAT_OPEN,
		(__u8 *)&खोलो_command, माप(खोलो_command));
पूर्ण


अटल पूर्णांक firm_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा whiteheat_simple बंद_command;

	बंद_command.port = port->port_number + 1;
	वापस firm_send_command(port, WHITEHEAT_CLOSE,
			(__u8 *)&बंद_command, माप(बंद_command));
पूर्ण


अटल व्योम firm_setup_port(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा device *dev = &port->dev;
	काष्ठा whiteheat_port_settings port_settings;
	अचिन्हित पूर्णांक cflag = tty->termios.c_cflag;
	speed_t baud;

	port_settings.port = port->port_number + 1;

	/* get the byte size */
	चयन (cflag & CSIZE) अणु
	हाल CS5:	port_settings.bits = 5;   अवरोध;
	हाल CS6:	port_settings.bits = 6;   अवरोध;
	हाल CS7:	port_settings.bits = 7;   अवरोध;
	शेष:
	हाल CS8:	port_settings.bits = 8;   अवरोध;
	पूर्ण
	dev_dbg(dev, "%s - data bits = %d\n", __func__, port_settings.bits);

	/* determine the parity */
	अगर (cflag & PARENB)
		अगर (cflag & CMSPAR)
			अगर (cflag & PARODD)
				port_settings.parity = WHITEHEAT_PAR_MARK;
			अन्यथा
				port_settings.parity = WHITEHEAT_PAR_SPACE;
		अन्यथा
			अगर (cflag & PARODD)
				port_settings.parity = WHITEHEAT_PAR_ODD;
			अन्यथा
				port_settings.parity = WHITEHEAT_PAR_EVEN;
	अन्यथा
		port_settings.parity = WHITEHEAT_PAR_NONE;
	dev_dbg(dev, "%s - parity = %c\n", __func__, port_settings.parity);

	/* figure out the stop bits requested */
	अगर (cflag & CSTOPB)
		port_settings.stop = 2;
	अन्यथा
		port_settings.stop = 1;
	dev_dbg(dev, "%s - stop bits = %d\n", __func__, port_settings.stop);

	/* figure out the flow control settings */
	अगर (cflag & CRTSCTS)
		port_settings.hflow = (WHITEHEAT_HFLOW_CTS |
						WHITEHEAT_HFLOW_RTS);
	अन्यथा
		port_settings.hflow = WHITEHEAT_HFLOW_NONE;
	dev_dbg(dev, "%s - hardware flow control = %s %s %s %s\n", __func__,
	    (port_settings.hflow & WHITEHEAT_HFLOW_CTS) ? "CTS" : "",
	    (port_settings.hflow & WHITEHEAT_HFLOW_RTS) ? "RTS" : "",
	    (port_settings.hflow & WHITEHEAT_HFLOW_DSR) ? "DSR" : "",
	    (port_settings.hflow & WHITEHEAT_HFLOW_DTR) ? "DTR" : "");

	/* determine software flow control */
	अगर (I_IXOFF(tty))
		port_settings.sflow = WHITEHEAT_SFLOW_RXTX;
	अन्यथा
		port_settings.sflow = WHITEHEAT_SFLOW_NONE;
	dev_dbg(dev, "%s - software flow control = %c\n", __func__, port_settings.sflow);

	port_settings.xon = START_CHAR(tty);
	port_settings.xoff = STOP_CHAR(tty);
	dev_dbg(dev, "%s - XON = %2x, XOFF = %2x\n", __func__, port_settings.xon, port_settings.xoff);

	/* get the baud rate wanted */
	baud = tty_get_baud_rate(tty);
	port_settings.baud = cpu_to_le32(baud);
	dev_dbg(dev, "%s - baud rate = %u\n", __func__, baud);

	/* fixme: should set validated settings */
	tty_encode_baud_rate(tty, baud, baud);

	/* handle any settings that aren't specअगरied in the tty काष्ठाure */
	port_settings.lloop = 0;

	/* now send the message to the device */
	firm_send_command(port, WHITEHEAT_SETUP_PORT,
			(__u8 *)&port_settings, माप(port_settings));
पूर्ण


अटल पूर्णांक firm_set_rts(काष्ठा usb_serial_port *port, __u8 onoff)
अणु
	काष्ठा whiteheat_set_rdb rts_command;

	rts_command.port = port->port_number + 1;
	rts_command.state = onoff;
	वापस firm_send_command(port, WHITEHEAT_SET_RTS,
			(__u8 *)&rts_command, माप(rts_command));
पूर्ण


अटल पूर्णांक firm_set_dtr(काष्ठा usb_serial_port *port, __u8 onoff)
अणु
	काष्ठा whiteheat_set_rdb dtr_command;

	dtr_command.port = port->port_number + 1;
	dtr_command.state = onoff;
	वापस firm_send_command(port, WHITEHEAT_SET_DTR,
			(__u8 *)&dtr_command, माप(dtr_command));
पूर्ण


अटल पूर्णांक firm_set_अवरोध(काष्ठा usb_serial_port *port, __u8 onoff)
अणु
	काष्ठा whiteheat_set_rdb अवरोध_command;

	अवरोध_command.port = port->port_number + 1;
	अवरोध_command.state = onoff;
	वापस firm_send_command(port, WHITEHEAT_SET_BREAK,
			(__u8 *)&अवरोध_command, माप(अवरोध_command));
पूर्ण


अटल पूर्णांक firm_purge(काष्ठा usb_serial_port *port, __u8 rxtx)
अणु
	काष्ठा whiteheat_purge purge_command;

	purge_command.port = port->port_number + 1;
	purge_command.what = rxtx;
	वापस firm_send_command(port, WHITEHEAT_PURGE,
			(__u8 *)&purge_command, माप(purge_command));
पूर्ण


अटल पूर्णांक firm_get_dtr_rts(काष्ठा usb_serial_port *port)
अणु
	काष्ठा whiteheat_simple get_dr_command;

	get_dr_command.port = port->port_number + 1;
	वापस firm_send_command(port, WHITEHEAT_GET_DTR_RTS,
			(__u8 *)&get_dr_command, माप(get_dr_command));
पूर्ण


अटल पूर्णांक firm_report_tx_करोne(काष्ठा usb_serial_port *port)
अणु
	काष्ठा whiteheat_simple बंद_command;

	बंद_command.port = port->port_number + 1;
	वापस firm_send_command(port, WHITEHEAT_REPORT_TX_DONE,
			(__u8 *)&बंद_command, माप(बंद_command));
पूर्ण


/*****************************************************************************
 * Connect Tech's White Heat utility functions
 *****************************************************************************/
अटल पूर्णांक start_command_port(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *command_port;
	काष्ठा whiteheat_command_निजी *command_info;
	पूर्णांक retval = 0;

	command_port = serial->port[COMMAND_PORT];
	command_info = usb_get_serial_port_data(command_port);
	mutex_lock(&command_info->mutex);
	अगर (!command_info->port_running) अणु
		/* Work around HCD bugs */
		usb_clear_halt(serial->dev, command_port->पढ़ो_urb->pipe);

		retval = usb_submit_urb(command_port->पढ़ो_urb, GFP_KERNEL);
		अगर (retval) अणु
			dev_err(&serial->dev->dev,
				"%s - failed submitting read urb, error %d\n",
				__func__, retval);
			जाओ निकास;
		पूर्ण
	पूर्ण
	command_info->port_running++;

निकास:
	mutex_unlock(&command_info->mutex);
	वापस retval;
पूर्ण


अटल व्योम stop_command_port(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *command_port;
	काष्ठा whiteheat_command_निजी *command_info;

	command_port = serial->port[COMMAND_PORT];
	command_info = usb_get_serial_port_data(command_port);
	mutex_lock(&command_info->mutex);
	command_info->port_running--;
	अगर (!command_info->port_running)
		usb_समाप्त_urb(command_port->पढ़ो_urb);
	mutex_unlock(&command_info->mutex);
पूर्ण

module_usb_serial_driver(serial_drivers, id_table_combined);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

MODULE_FIRMWARE("whiteheat.fw");
MODULE_FIRMWARE("whiteheat_loader.fw");
