<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB HandSpring Visor, Palm m50x, and Sony Clie driver
 * (supports all of the Palm OS USB devices)
 *
 *	Copyright (C) 1999 - 2004
 *	    Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/usb/cdc.h>
#समावेश "visor.h"

/*
 * Version Inक्रमmation
 */
#घोषणा DRIVER_AUTHOR "Greg Kroah-Hartman <greg@kroah.com>"
#घोषणा DRIVER_DESC "USB HandSpring Visor / Palm OS driver"

/* function prototypes क्रम a handspring visor */
अटल पूर्णांक  visor_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
अटल व्योम visor_बंद(काष्ठा usb_serial_port *port);
अटल पूर्णांक  visor_probe(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id);
अटल पूर्णांक  visor_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds);
अटल पूर्णांक  clie_5_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds);
अटल व्योम visor_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb);
अटल पूर्णांक  clie_3_5_startup(काष्ठा usb_serial *serial);
अटल पूर्णांक palm_os_3_probe(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id);
अटल पूर्णांक palm_os_4_probe(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id);

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(HANDSPRING_VENDOR_ID, HANDSPRING_VISOR_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_3_probe पूर्ण,
	अणु USB_DEVICE(HANDSPRING_VENDOR_ID, HANDSPRING_TREO_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(HANDSPRING_VENDOR_ID, HANDSPRING_TREO600_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(GSPDA_VENDOR_ID, GSPDA_XPLORE_M68_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M500_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M505_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M515_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_I705_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M100_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M125_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M130_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_TUNGSTEN_T_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_TREO_650),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_TUNGSTEN_Z_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_ZIRE_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_4_0_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_S360_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_4_1_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_NX60_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_NZ90V_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_TJ25_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(ACER_VENDOR_ID, ACER_S10_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE_INTERFACE_CLASS(SAMSUNG_VENDOR_ID, SAMSUNG_SCH_I330_ID, 0xff),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(SAMSUNG_VENDOR_ID, SAMSUNG_SPH_I500_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(TAPWAVE_VENDOR_ID, TAPWAVE_ZODIAC_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(GARMIN_VENDOR_ID, GARMIN_IQUE_3600_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(ACEECA_VENDOR_ID, ACEECA_MEZ1000_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(KYOCERA_VENDOR_ID, KYOCERA_7135_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु USB_DEVICE(FOSSIL_VENDOR_ID, FOSSIL_ABACUS_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id clie_id_5_table[] = अणु
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_UX50_ID),
		.driver_info = (kernel_uदीर्घ_t)&palm_os_4_probe पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id clie_id_3_5_table[] = अणु
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_3_5_ID) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_combined[] = अणु
	अणु USB_DEVICE(HANDSPRING_VENDOR_ID, HANDSPRING_VISOR_ID) पूर्ण,
	अणु USB_DEVICE(HANDSPRING_VENDOR_ID, HANDSPRING_TREO_ID) पूर्ण,
	अणु USB_DEVICE(HANDSPRING_VENDOR_ID, HANDSPRING_TREO600_ID) पूर्ण,
	अणु USB_DEVICE(GSPDA_VENDOR_ID, GSPDA_XPLORE_M68_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M500_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M505_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M515_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_I705_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M100_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M125_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_M130_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_TUNGSTEN_T_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_TREO_650) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_TUNGSTEN_Z_ID) पूर्ण,
	अणु USB_DEVICE(PALM_VENDOR_ID, PALM_ZIRE_ID) पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_3_5_ID) पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_4_0_ID) पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_S360_ID) पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_4_1_ID) पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_NX60_ID) पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_NZ90V_ID) पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_UX50_ID) पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_CLIE_TJ25_ID) पूर्ण,
	अणु USB_DEVICE(SAMSUNG_VENDOR_ID, SAMSUNG_SCH_I330_ID) पूर्ण,
	अणु USB_DEVICE(SAMSUNG_VENDOR_ID, SAMSUNG_SPH_I500_ID) पूर्ण,
	अणु USB_DEVICE(TAPWAVE_VENDOR_ID, TAPWAVE_ZODIAC_ID) पूर्ण,
	अणु USB_DEVICE(GARMIN_VENDOR_ID, GARMIN_IQUE_3600_ID) पूर्ण,
	अणु USB_DEVICE(ACEECA_VENDOR_ID, ACEECA_MEZ1000_ID) पूर्ण,
	अणु USB_DEVICE(KYOCERA_VENDOR_ID, KYOCERA_7135_ID) पूर्ण,
	अणु USB_DEVICE(FOSSIL_VENDOR_ID, FOSSIL_ABACUS_ID) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table_combined);

/* All of the device info needed क्रम the Handspring Visor,
   and Palm 4.0 devices */
अटल काष्ठा usb_serial_driver handspring_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"visor",
	पूर्ण,
	.description =		"Handspring Visor / Palm OS",
	.id_table =		id_table,
	.num_ports =		2,
	.bulk_out_size =	256,
	.खोलो =			visor_खोलो,
	.बंद =		visor_बंद,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
	.probe =		visor_probe,
	.calc_num_ports =	visor_calc_num_ports,
	.पढ़ो_पूर्णांक_callback =	visor_पढ़ो_पूर्णांक_callback,
पूर्ण;

/* All of the device info needed क्रम the Clie UX50, TH55 Palm 5.0 devices */
अटल काष्ठा usb_serial_driver clie_5_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"clie_5",
	पूर्ण,
	.description =		"Sony Clie 5.0",
	.id_table =		clie_id_5_table,
	.num_ports =		2,
	.num_bulk_out =		2,
	.bulk_out_size =	256,
	.खोलो =			visor_खोलो,
	.बंद =		visor_बंद,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
	.probe =		visor_probe,
	.calc_num_ports =	clie_5_calc_num_ports,
	.पढ़ो_पूर्णांक_callback =	visor_पढ़ो_पूर्णांक_callback,
पूर्ण;

/* device info क्रम the Sony Clie OS version 3.5 */
अटल काष्ठा usb_serial_driver clie_3_5_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"clie_3.5",
	पूर्ण,
	.description =		"Sony Clie 3.5",
	.id_table =		clie_id_3_5_table,
	.num_ports =		1,
	.bulk_out_size =	256,
	.खोलो =			visor_खोलो,
	.बंद =		visor_बंद,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
	.attach =		clie_3_5_startup,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&handspring_device, &clie_5_device, &clie_3_5_device, शून्य
पूर्ण;

/******************************************************************************
 * Handspring Visor specअगरic driver functions
 ******************************************************************************/
अटल पूर्णांक visor_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	पूर्णांक result = 0;

	अगर (!port->पढ़ो_urb) अणु
		/* this is needed क्रम some brain dead Sony devices */
		dev_err(&port->dev, "Device lied about number of ports, please use a lower one.\n");
		वापस -ENODEV;
	पूर्ण

	/* Start पढ़ोing from the device */
	result = usb_serial_generic_खोलो(tty, port);
	अगर (result)
		जाओ निकास;

	अगर (port->पूर्णांकerrupt_in_urb) अणु
		dev_dbg(&port->dev, "adding interrupt input for treo\n");
		result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
		अगर (result)
			dev_err(&port->dev,
			    "%s - failed submitting interrupt urb, error %d\n",
							__func__, result);
	पूर्ण
निकास:
	वापस result;
पूर्ण


अटल व्योम visor_बंद(काष्ठा usb_serial_port *port)
अणु
	अचिन्हित अक्षर *transfer_buffer;

	usb_serial_generic_बंद(port);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	transfer_buffer = kदो_स्मृति(0x12, GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस;
	usb_control_msg(port->serial->dev,
					 usb_rcvctrlpipe(port->serial->dev, 0),
					 VISOR_CLOSE_NOTIFICATION, 0xc2,
					 0x0000, 0x0000,
					 transfer_buffer, 0x12, 300);
	kमुक्त(transfer_buffer);
पूर्ण

अटल व्योम visor_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	पूर्णांक status = urb->status;
	पूर्णांक result;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&port->dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(&port->dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		जाओ निकास;
	पूर्ण

	/*
	 * This inक्रमmation is still unknown what it can be used क्रम.
	 * If anyone has an idea, please let the author know...
	 *
	 * Rumor has it this endpoपूर्णांक is used to notअगरy when data
	 * is पढ़ोy to be पढ़ो from the bulk ones.
	 */
	usb_serial_debug_data(&port->dev, __func__, urb->actual_length,
			      urb->transfer_buffer);

निकास:
	result = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (result)
		dev_err(&urb->dev->dev,
				"%s - Error %d submitting interrupt urb\n",
							__func__, result);
पूर्ण

अटल पूर्णांक palm_os_3_probe(काष्ठा usb_serial *serial,
						स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा device *dev = &serial->dev->dev;
	काष्ठा visor_connection_info *connection_info;
	अचिन्हित अक्षर *transfer_buffer;
	अक्षर *string;
	पूर्णांक retval = 0;
	पूर्णांक i;
	पूर्णांक num_ports = 0;

	transfer_buffer = kदो_स्मृति(माप(*connection_info), GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस -ENOMEM;

	/* send a get connection info request */
	retval = usb_control_msg(serial->dev,
				  usb_rcvctrlpipe(serial->dev, 0),
				  VISOR_GET_CONNECTION_INFORMATION,
				  0xc2, 0x0000, 0x0000, transfer_buffer,
				  माप(*connection_info), 300);
	अगर (retval < 0) अणु
		dev_err(dev, "%s - error %d getting connection information\n",
			__func__, retval);
		जाओ निकास;
	पूर्ण

	अगर (retval != माप(*connection_info)) अणु
		dev_err(dev, "Invalid connection information received from device\n");
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	connection_info = (काष्ठा visor_connection_info *)transfer_buffer;

	num_ports = le16_to_cpu(connection_info->num_ports);

	/* Handle devices that report invalid stuff here. */
	अगर (num_ports == 0 || num_ports > 2) अणु
		dev_warn(dev, "%s: No valid connect info available\n",
			serial->type->description);
		num_ports = 2;
	पूर्ण

	क्रम (i = 0; i < num_ports; ++i) अणु
		चयन (connection_info->connections[i].port_function_id) अणु
		हाल VISOR_FUNCTION_GENERIC:
			string = "Generic";
			अवरोध;
		हाल VISOR_FUNCTION_DEBUGGER:
			string = "Debugger";
			अवरोध;
		हाल VISOR_FUNCTION_HOTSYNC:
			string = "HotSync";
			अवरोध;
		हाल VISOR_FUNCTION_CONSOLE:
			string = "Console";
			अवरोध;
		हाल VISOR_FUNCTION_REMOTE_खाता_SYS:
			string = "Remote File System";
			अवरोध;
		शेष:
			string = "unknown";
			अवरोध;
		पूर्ण
		dev_info(dev, "%s: port %d, is for %s use\n",
			serial->type->description,
			connection_info->connections[i].port, string);
	पूर्ण
	dev_info(dev, "%s: Number of ports: %d\n", serial->type->description,
		num_ports);

	/*
	 * save off our num_ports info so that we can use it in the
	 * calc_num_ports callback
	 */
	usb_set_serial_data(serial, (व्योम *)(दीर्घ)num_ports);

	/* ask क्रम the number of bytes available, but ignore the
	   response as it is broken */
	retval = usb_control_msg(serial->dev,
				  usb_rcvctrlpipe(serial->dev, 0),
				  VISOR_REQUEST_BYTES_AVAILABLE,
				  0xc2, 0x0000, 0x0005, transfer_buffer,
				  0x02, 300);
	अगर (retval < 0)
		dev_err(dev, "%s - error %d getting bytes available request\n",
			__func__, retval);
	retval = 0;

निकास:
	kमुक्त(transfer_buffer);

	वापस retval;
पूर्ण

अटल पूर्णांक palm_os_4_probe(काष्ठा usb_serial *serial,
						स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा device *dev = &serial->dev->dev;
	काष्ठा palm_ext_connection_info *connection_info;
	अचिन्हित अक्षर *transfer_buffer;
	पूर्णांक retval;

	transfer_buffer =  kदो_स्मृति(माप(*connection_info), GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस -ENOMEM;

	retval = usb_control_msg(serial->dev,
				  usb_rcvctrlpipe(serial->dev, 0),
				  PALM_GET_EXT_CONNECTION_INFORMATION,
				  0xc2, 0x0000, 0x0000, transfer_buffer,
				  माप(*connection_info), 300);
	अगर (retval < 0)
		dev_err(dev, "%s - error %d getting connection info\n",
			__func__, retval);
	अन्यथा
		usb_serial_debug_data(dev, __func__, retval, transfer_buffer);

	kमुक्त(transfer_buffer);
	वापस 0;
पूर्ण


अटल पूर्णांक visor_probe(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक retval = 0;
	पूर्णांक (*startup)(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id);

	/*
	 * some Samsung Android phones in modem mode have the same ID
	 * as SPH-I500, but they are ACM devices, so करोnt bind to them
	 */
	अगर (id->idVenकरोr == SAMSUNG_VENDOR_ID &&
		id->idProduct == SAMSUNG_SPH_I500_ID &&
		serial->dev->descriptor.bDeviceClass == USB_CLASS_COMM &&
		serial->dev->descriptor.bDeviceSubClass ==
			USB_CDC_SUBCLASS_ACM)
		वापस -ENODEV;

	अगर (serial->dev->actconfig->desc.bConfigurationValue != 1) अणु
		dev_err(&serial->dev->dev, "active config #%d != 1 ??\n",
			serial->dev->actconfig->desc.bConfigurationValue);
		वापस -ENODEV;
	पूर्ण

	अगर (id->driver_info) अणु
		startup = (व्योम *)id->driver_info;
		retval = startup(serial, id);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक visor_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	अचिन्हित पूर्णांक vid = le16_to_cpu(serial->dev->descriptor.idVenकरोr);
	पूर्णांक num_ports = (पूर्णांक)(दीर्घ)(usb_get_serial_data(serial));

	अगर (num_ports)
		usb_set_serial_data(serial, शून्य);

	/*
	 * Only swap the bulk endpoपूर्णांकs क्रम the Handspring devices with
	 * पूर्णांकerrupt in endpoपूर्णांकs, which क्रम now are the Treo devices.
	 */
	अगर (!(vid == HANDSPRING_VENDOR_ID || vid == KYOCERA_VENDOR_ID) ||
			epds->num_पूर्णांकerrupt_in == 0)
		जाओ out;

	अगर (epds->num_bulk_in < 2 || epds->num_पूर्णांकerrupt_in < 2) अणु
		dev_err(&serial->पूर्णांकerface->dev, "missing endpoints\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * It appears that Treos and Kyoceras want to use the
	 * 1st bulk in endpoपूर्णांक to communicate with the 2nd bulk out endpoपूर्णांक,
	 * so let's swap the 1st and 2nd bulk in and पूर्णांकerrupt endpoपूर्णांकs.
	 * Note that swapping the bulk out endpoपूर्णांकs would अवरोध lots of
	 * apps that want to communicate on the second port.
	 */
	swap(epds->bulk_in[0], epds->bulk_in[1]);
	swap(epds->पूर्णांकerrupt_in[0], epds->पूर्णांकerrupt_in[1]);
out:
	वापस num_ports;
पूर्ण

अटल पूर्णांक clie_5_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	/*
	 * TH55 रेजिस्टरs 2 ports.
	 * Communication in from the UX50/TH55 uses the first bulk-in
	 * endpoपूर्णांक, जबतक communication out to the UX50/TH55 uses the second
	 * bulk-out endpoपूर्णांक.
	 */

	/*
	 * FIXME: Should we swap the descriptors instead of using the same
	 *        bulk-out endpoपूर्णांक क्रम both ports?
	 */
	epds->bulk_out[0] = epds->bulk_out[1];

	वापस serial->type->num_ports;
पूर्ण

अटल पूर्णांक clie_3_5_startup(काष्ठा usb_serial *serial)
अणु
	काष्ठा device *dev = &serial->dev->dev;
	पूर्णांक result;
	u8 *data;

	data = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/*
	 * Note that PEG-300 series devices expect the following two calls.
	 */

	/* get the config number */
	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
				  USB_REQ_GET_CONFIGURATION, USB_सूची_IN,
				  0, 0, data, 1, 3000);
	अगर (result < 0) अणु
		dev_err(dev, "%s: get config number failed: %d\n",
							__func__, result);
		जाओ out;
	पूर्ण
	अगर (result != 1) अणु
		dev_err(dev, "%s: get config number bad return length: %d\n",
							__func__, result);
		result = -EIO;
		जाओ out;
	पूर्ण

	/* get the पूर्णांकerface number */
	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
				  USB_REQ_GET_INTERFACE,
				  USB_सूची_IN | USB_RECIP_INTERFACE,
				  0, 0, data, 1, 3000);
	अगर (result < 0) अणु
		dev_err(dev, "%s: get interface number failed: %d\n",
							__func__, result);
		जाओ out;
	पूर्ण
	अगर (result != 1) अणु
		dev_err(dev,
			"%s: get interface number bad return length: %d\n",
							__func__, result);
		result = -EIO;
		जाओ out;
	पूर्ण

	result = 0;
out:
	kमुक्त(data);

	वापस result;
पूर्ण

module_usb_serial_driver(serial_drivers, id_table_combined);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
