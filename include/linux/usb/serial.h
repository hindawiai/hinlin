<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Serial Converter stuff
 *
 *	Copyright (C) 1999 - 2012
 *	    Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 *	This program is मुक्त software; you can redistribute it and/or modअगरy
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; version 2 of the License.
 *
 */

#अगर_अघोषित __LINUX_USB_SERIAL_H
#घोषणा __LINUX_USB_SERIAL_H

#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/serial.h>
#समावेश <linux/kfअगरo.h>

/* The maximum number of ports one device can grab at once */
#घोषणा MAX_NUM_PORTS		16

/* USB serial flags */
#घोषणा USB_SERIAL_WRITE_BUSY	0
#घोषणा USB_SERIAL_THROTTLED	1

/**
 * usb_serial_port: काष्ठाure क्रम the specअगरic ports of a device.
 * @serial: poपूर्णांकer back to the काष्ठा usb_serial owner of this port.
 * @port: poपूर्णांकer to the corresponding tty_port क्रम this port.
 * @lock: spinlock to grab when updating portions of this काष्ठाure.
 * @minor: the minor number of the port
 * @port_number: the काष्ठा usb_serial port number of this port (starts at 0)
 * @पूर्णांकerrupt_in_buffer: poपूर्णांकer to the पूर्णांकerrupt in buffer क्रम this port.
 * @पूर्णांकerrupt_in_urb: poपूर्णांकer to the पूर्णांकerrupt in काष्ठा urb क्रम this port.
 * @पूर्णांकerrupt_in_endpoपूर्णांकAddress: endpoपूर्णांक address क्रम the पूर्णांकerrupt in pipe
 *	क्रम this port.
 * @पूर्णांकerrupt_out_buffer: poपूर्णांकer to the पूर्णांकerrupt out buffer क्रम this port.
 * @पूर्णांकerrupt_out_size: the size of the पूर्णांकerrupt_out_buffer, in bytes.
 * @पूर्णांकerrupt_out_urb: poपूर्णांकer to the पूर्णांकerrupt out काष्ठा urb क्रम this port.
 * @पूर्णांकerrupt_out_endpoपूर्णांकAddress: endpoपूर्णांक address क्रम the पूर्णांकerrupt out pipe
 *	क्रम this port.
 * @bulk_in_buffer: poपूर्णांकer to the bulk in buffer क्रम this port.
 * @bulk_in_size: the size of the bulk_in_buffer, in bytes.
 * @पढ़ो_urb: poपूर्णांकer to the bulk in काष्ठा urb क्रम this port.
 * @bulk_in_endpoपूर्णांकAddress: endpoपूर्णांक address क्रम the bulk in pipe क्रम this
 *	port.
 * @bulk_in_buffers: poपूर्णांकers to the bulk in buffers क्रम this port
 * @पढ़ो_urbs: poपूर्णांकers to the bulk in urbs क्रम this port
 * @पढ़ो_urbs_मुक्त: status biपंचांगap the क्रम bulk in urbs
 * @bulk_out_buffer: poपूर्णांकer to the bulk out buffer क्रम this port.
 * @bulk_out_size: the size of the bulk_out_buffer, in bytes.
 * @ग_लिखो_urb: poपूर्णांकer to the bulk out काष्ठा urb क्रम this port.
 * @ग_लिखो_fअगरo: kfअगरo used to buffer outgoing data
 * @bulk_out_buffers: poपूर्णांकers to the bulk out buffers क्रम this port
 * @ग_लिखो_urbs: poपूर्णांकers to the bulk out urbs क्रम this port
 * @ग_लिखो_urbs_मुक्त: status biपंचांगap the क्रम bulk out urbs
 * @icount: पूर्णांकerrupt counters
 * @tx_bytes: number of bytes currently in host stack queues
 * @bulk_out_endpoपूर्णांकAddress: endpoपूर्णांक address क्रम the bulk out pipe क्रम this
 *	port.
 * @flags: usb serial port flags
 * @work: work queue entry क्रम the line discipline waking up.
 * @dev: poपूर्णांकer to the serial device
 *
 * This काष्ठाure is used by the usb-serial core and drivers क्रम the specअगरic
 * ports of a device.
 */
काष्ठा usb_serial_port अणु
	काष्ठा usb_serial	*serial;
	काष्ठा tty_port		port;
	spinlock_t		lock;
	u32			minor;
	u8			port_number;

	अचिन्हित अक्षर		*पूर्णांकerrupt_in_buffer;
	काष्ठा urb		*पूर्णांकerrupt_in_urb;
	__u8			पूर्णांकerrupt_in_endpoपूर्णांकAddress;

	अचिन्हित अक्षर		*पूर्णांकerrupt_out_buffer;
	पूर्णांक			पूर्णांकerrupt_out_size;
	काष्ठा urb		*पूर्णांकerrupt_out_urb;
	__u8			पूर्णांकerrupt_out_endpoपूर्णांकAddress;

	अचिन्हित अक्षर		*bulk_in_buffer;
	पूर्णांक			bulk_in_size;
	काष्ठा urb		*पढ़ो_urb;
	__u8			bulk_in_endpoपूर्णांकAddress;

	अचिन्हित अक्षर		*bulk_in_buffers[2];
	काष्ठा urb		*पढ़ो_urbs[2];
	अचिन्हित दीर्घ		पढ़ो_urbs_मुक्त;

	अचिन्हित अक्षर		*bulk_out_buffer;
	पूर्णांक			bulk_out_size;
	काष्ठा urb		*ग_लिखो_urb;
	काष्ठा kfअगरo		ग_लिखो_fअगरo;

	अचिन्हित अक्षर		*bulk_out_buffers[2];
	काष्ठा urb		*ग_लिखो_urbs[2];
	अचिन्हित दीर्घ		ग_लिखो_urbs_मुक्त;
	__u8			bulk_out_endpoपूर्णांकAddress;

	काष्ठा async_icount	icount;
	पूर्णांक			tx_bytes;

	अचिन्हित दीर्घ		flags;
	काष्ठा work_काष्ठा	work;
	अचिन्हित दीर्घ		sysrq; /* sysrq समयout */
	काष्ठा device		dev;
पूर्ण;
#घोषणा to_usb_serial_port(d) container_of(d, काष्ठा usb_serial_port, dev)

/* get and set the port निजी data poपूर्णांकer helper functions */
अटल अंतरभूत व्योम *usb_get_serial_port_data(काष्ठा usb_serial_port *port)
अणु
	वापस dev_get_drvdata(&port->dev);
पूर्ण

अटल अंतरभूत व्योम usb_set_serial_port_data(काष्ठा usb_serial_port *port,
					    व्योम *data)
अणु
	dev_set_drvdata(&port->dev, data);
पूर्ण

/**
 * usb_serial - काष्ठाure used by the usb-serial core क्रम a device
 * @dev: poपूर्णांकer to the काष्ठा usb_device क्रम this device
 * @type: poपूर्णांकer to the काष्ठा usb_serial_driver क्रम this device
 * @पूर्णांकerface: poपूर्णांकer to the काष्ठा usb_पूर्णांकerface क्रम this device
 * @sibling: poपूर्णांकer to the काष्ठा usb_पूर्णांकerface of any sibling पूर्णांकerface
 * @suspend_count: number of suspended (sibling) पूर्णांकerfaces
 * @num_ports: the number of ports this device has
 * @num_पूर्णांकerrupt_in: number of पूर्णांकerrupt in endpoपूर्णांकs we have
 * @num_पूर्णांकerrupt_out: number of पूर्णांकerrupt out endpoपूर्णांकs we have
 * @num_bulk_in: number of bulk in endpoपूर्णांकs we have
 * @num_bulk_out: number of bulk out endpoपूर्णांकs we have
 * @port: array of काष्ठा usb_serial_port काष्ठाures क्रम the dअगरferent ports.
 * @निजी: place to put any driver specअगरic inक्रमmation that is needed.  The
 *	usb-serial driver is required to manage this data, the usb-serial core
 *	will not touch this.  Use usb_get_serial_data() and
 *	usb_set_serial_data() to access this.
 */
काष्ठा usb_serial अणु
	काष्ठा usb_device		*dev;
	काष्ठा usb_serial_driver	*type;
	काष्ठा usb_पूर्णांकerface		*पूर्णांकerface;
	काष्ठा usb_पूर्णांकerface		*sibling;
	अचिन्हित पूर्णांक			suspend_count;
	अचिन्हित अक्षर			disconnected:1;
	अचिन्हित अक्षर			attached:1;
	अचिन्हित अक्षर			minors_reserved:1;
	अचिन्हित अक्षर			num_ports;
	अचिन्हित अक्षर			num_port_poपूर्णांकers;
	अचिन्हित अक्षर			num_पूर्णांकerrupt_in;
	अचिन्हित अक्षर			num_पूर्णांकerrupt_out;
	अचिन्हित अक्षर			num_bulk_in;
	अचिन्हित अक्षर			num_bulk_out;
	काष्ठा usb_serial_port		*port[MAX_NUM_PORTS];
	काष्ठा kref			kref;
	काष्ठा mutex			disc_mutex;
	व्योम				*निजी;
पूर्ण;
#घोषणा to_usb_serial(d) container_of(d, काष्ठा usb_serial, kref)

/* get and set the serial निजी data poपूर्णांकer helper functions */
अटल अंतरभूत व्योम *usb_get_serial_data(काष्ठा usb_serial *serial)
अणु
	वापस serial->निजी;
पूर्ण

अटल अंतरभूत व्योम usb_set_serial_data(काष्ठा usb_serial *serial, व्योम *data)
अणु
	serial->निजी = data;
पूर्ण

काष्ठा usb_serial_endpoपूर्णांकs अणु
	अचिन्हित अक्षर num_bulk_in;
	अचिन्हित अक्षर num_bulk_out;
	अचिन्हित अक्षर num_पूर्णांकerrupt_in;
	अचिन्हित अक्षर num_पूर्णांकerrupt_out;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_in[MAX_NUM_PORTS];
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_out[MAX_NUM_PORTS];
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकerrupt_in[MAX_NUM_PORTS];
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकerrupt_out[MAX_NUM_PORTS];
पूर्ण;

/**
 * usb_serial_driver - describes a usb serial driver
 * @description: poपूर्णांकer to a string that describes this driver.  This string
 *	used in the syslog messages when a device is inserted or हटाओd.
 * @id_table: poपूर्णांकer to a list of usb_device_id काष्ठाures that define all
 *	of the devices this काष्ठाure can support.
 * @num_ports: the number of dअगरferent ports this device will have.
 * @num_bulk_in: minimum number of bulk-in endpoपूर्णांकs
 * @num_bulk_out: minimum number of bulk-out endpoपूर्णांकs
 * @num_पूर्णांकerrupt_in: minimum number of पूर्णांकerrupt-in endpoपूर्णांकs
 * @num_पूर्णांकerrupt_out: minimum number of पूर्णांकerrupt-out endpoपूर्णांकs
 * @bulk_in_size: minimum number of bytes to allocate क्रम bulk-in buffer
 *	(0 = end-poपूर्णांक size)
 * @bulk_out_size: bytes to allocate क्रम bulk-out buffer (0 = end-poपूर्णांक size)
 * @calc_num_ports: poपूर्णांकer to a function to determine how many ports this
 *	device has dynamically. It can also be used to verअगरy the number of
 *	endpoपूर्णांकs or to modअगरy the port-endpoपूर्णांक mapping. It will be called
 *	after the probe() callback is called, but beक्रमe attach().
 * @probe: poपूर्णांकer to the driver's probe function.
 *	This will be called when the device is inserted पूर्णांकo the प्रणाली,
 *	but beक्रमe the device has been fully initialized by the usb_serial
 *	subप्रणाली.  Use this function to करोwnload any firmware to the device,
 *	or any other early initialization that might be needed.
 *	Return 0 to जारी on with the initialization sequence.  Anything
 *	अन्यथा will पात it.
 * @attach: poपूर्णांकer to the driver's attach function.
 *	This will be called when the काष्ठा usb_serial काष्ठाure is fully
 *	set up.  Do any local initialization of the device, or any निजी
 *	memory काष्ठाure allocation at this poपूर्णांक in समय.
 * @disconnect: poपूर्णांकer to the driver's disconnect function.  This will be
 *	called when the device is unplugged or unbound from the driver.
 * @release: poपूर्णांकer to the driver's release function.  This will be called
 *	when the usb_serial data काष्ठाure is about to be destroyed.
 * @usb_driver: poपूर्णांकer to the काष्ठा usb_driver that controls this
 *	device.  This is necessary to allow dynamic ids to be added to
 *	the driver from sysfs.
 *
 * This काष्ठाure is defines a USB Serial driver.  It provides all of
 * the inक्रमmation that the USB serial core code needs.  If the function
 * poपूर्णांकers are defined, then the USB serial core code will call them when
 * the corresponding tty port functions are called.  If they are not
 * called, the generic serial function will be used instead.
 *
 * The driver.owner field should be set to the module owner of this driver.
 * The driver.name field should be set to the name of this driver (remember
 * it will show up in sysfs, so it needs to be लघु and to the poपूर्णांक.
 * Using the module name is a good idea.)
 */
काष्ठा usb_serial_driver अणु
	स्थिर अक्षर *description;
	स्थिर काष्ठा usb_device_id *id_table;

	काष्ठा list_head	driver_list;
	काष्ठा device_driver	driver;
	काष्ठा usb_driver	*usb_driver;
	काष्ठा usb_dynids	dynids;

	अचिन्हित अक्षर		num_ports;

	अचिन्हित अक्षर		num_bulk_in;
	अचिन्हित अक्षर		num_bulk_out;
	अचिन्हित अक्षर		num_पूर्णांकerrupt_in;
	अचिन्हित अक्षर		num_पूर्णांकerrupt_out;

	माप_प्रकार			bulk_in_size;
	माप_प्रकार			bulk_out_size;

	पूर्णांक (*probe)(काष्ठा usb_serial *serial, स्थिर काष्ठा usb_device_id *id);
	पूर्णांक (*attach)(काष्ठा usb_serial *serial);
	पूर्णांक (*calc_num_ports)(काष्ठा usb_serial *serial,
			काष्ठा usb_serial_endpoपूर्णांकs *epds);

	व्योम (*disconnect)(काष्ठा usb_serial *serial);
	व्योम (*release)(काष्ठा usb_serial *serial);

	पूर्णांक (*port_probe)(काष्ठा usb_serial_port *port);
	व्योम (*port_हटाओ)(काष्ठा usb_serial_port *port);

	पूर्णांक (*suspend)(काष्ठा usb_serial *serial, pm_message_t message);
	पूर्णांक (*resume)(काष्ठा usb_serial *serial);
	पूर्णांक (*reset_resume)(काष्ठा usb_serial *serial);

	/* serial function calls */
	/* Called by console and by the tty layer */
	पूर्णांक  (*खोलो)(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
	व्योम (*बंद)(काष्ठा usb_serial_port *port);
	पूर्णांक  (*ग_लिखो)(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
	/* Called only by the tty layer */
	पूर्णांक  (*ग_लिखो_room)(काष्ठा tty_काष्ठा *tty);
	पूर्णांक  (*ioctl)(काष्ठा tty_काष्ठा *tty,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	व्योम (*get_serial)(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss);
	पूर्णांक  (*set_serial)(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss);
	व्योम (*set_termios)(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port, काष्ठा ktermios *old);
	व्योम (*अवरोध_ctl)(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state);
	पूर्णांक  (*अक्षरs_in_buffer)(काष्ठा tty_काष्ठा *tty);
	व्योम (*रुको_until_sent)(काष्ठा tty_काष्ठा *tty, दीर्घ समयout);
	bool (*tx_empty)(काष्ठा usb_serial_port *port);
	व्योम (*throttle)(काष्ठा tty_काष्ठा *tty);
	व्योम (*unthrottle)(काष्ठा tty_काष्ठा *tty);
	पूर्णांक  (*tiocmget)(काष्ठा tty_काष्ठा *tty);
	पूर्णांक  (*tiocmset)(काष्ठा tty_काष्ठा *tty,
			 अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
	पूर्णांक  (*tiocmiरुको)(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ arg);
	पूर्णांक  (*get_icount)(काष्ठा tty_काष्ठा *tty,
			काष्ठा serial_icounter_काष्ठा *icount);
	/* Called by the tty layer क्रम port level work. There may or may not
	   be an attached tty at this poपूर्णांक */
	व्योम (*dtr_rts)(काष्ठा usb_serial_port *port, पूर्णांक on);
	पूर्णांक  (*carrier_उठाओd)(काष्ठा usb_serial_port *port);
	/* Called by the usb serial hooks to allow the user to rework the
	   termios state */
	व्योम (*init_termios)(काष्ठा tty_काष्ठा *tty);
	/* USB events */
	व्योम (*पढ़ो_पूर्णांक_callback)(काष्ठा urb *urb);
	व्योम (*ग_लिखो_पूर्णांक_callback)(काष्ठा urb *urb);
	व्योम (*पढ़ो_bulk_callback)(काष्ठा urb *urb);
	व्योम (*ग_लिखो_bulk_callback)(काष्ठा urb *urb);
	/* Called by the generic पढ़ो bulk callback */
	व्योम (*process_पढ़ो_urb)(काष्ठा urb *urb);
	/* Called by the generic ग_लिखो implementation */
	पूर्णांक (*prepare_ग_लिखो_buffer)(काष्ठा usb_serial_port *port,
						व्योम *dest, माप_प्रकार size);
पूर्ण;
#घोषणा to_usb_serial_driver(d) \
	container_of(d, काष्ठा usb_serial_driver, driver)

पूर्णांक usb_serial_रेजिस्टर_drivers(काष्ठा usb_serial_driver *स्थिर serial_drivers[],
		स्थिर अक्षर *name, स्थिर काष्ठा usb_device_id *id_table);
व्योम usb_serial_deरेजिस्टर_drivers(काष्ठा usb_serial_driver *स्थिर serial_drivers[]);
व्योम usb_serial_port_softपूर्णांक(काष्ठा usb_serial_port *port);

पूर्णांक usb_serial_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message);
पूर्णांक usb_serial_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

/* USB Serial console functions */
#अगर_घोषित CONFIG_USB_SERIAL_CONSOLE
व्योम usb_serial_console_init(पूर्णांक minor);
व्योम usb_serial_console_निकास(व्योम);
व्योम usb_serial_console_disconnect(काष्ठा usb_serial *serial);
#अन्यथा
अटल अंतरभूत व्योम usb_serial_console_init(पूर्णांक minor) अणु पूर्ण
अटल अंतरभूत व्योम usb_serial_console_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम usb_serial_console_disconnect(काष्ठा usb_serial *serial) अणुपूर्ण
#पूर्ण_अगर

/* Functions needed by other parts of the usbserial core */
काष्ठा usb_serial_port *usb_serial_port_get_by_minor(अचिन्हित पूर्णांक minor);
व्योम usb_serial_put(काष्ठा usb_serial *serial);

पूर्णांक usb_serial_claim_पूर्णांकerface(काष्ठा usb_serial *serial, काष्ठा usb_पूर्णांकerface *पूर्णांकf);

पूर्णांक usb_serial_generic_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
पूर्णांक usb_serial_generic_ग_लिखो_start(काष्ठा usb_serial_port *port, gfp_t mem_flags);
पूर्णांक usb_serial_generic_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
		स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
व्योम usb_serial_generic_बंद(काष्ठा usb_serial_port *port);
पूर्णांक usb_serial_generic_resume(काष्ठा usb_serial *serial);
पूर्णांक usb_serial_generic_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
पूर्णांक usb_serial_generic_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty);
व्योम usb_serial_generic_रुको_until_sent(काष्ठा tty_काष्ठा *tty, दीर्घ समयout);
व्योम usb_serial_generic_पढ़ो_bulk_callback(काष्ठा urb *urb);
व्योम usb_serial_generic_ग_लिखो_bulk_callback(काष्ठा urb *urb);
व्योम usb_serial_generic_throttle(काष्ठा tty_काष्ठा *tty);
व्योम usb_serial_generic_unthrottle(काष्ठा tty_काष्ठा *tty);
पूर्णांक usb_serial_generic_tiocmiरुको(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ arg);
पूर्णांक usb_serial_generic_get_icount(काष्ठा tty_काष्ठा *tty, काष्ठा serial_icounter_काष्ठा *icount);
पूर्णांक usb_serial_generic_रेजिस्टर(व्योम);
व्योम usb_serial_generic_deरेजिस्टर(व्योम);
पूर्णांक usb_serial_generic_submit_पढ़ो_urbs(काष्ठा usb_serial_port *port, gfp_t mem_flags);
व्योम usb_serial_generic_process_पढ़ो_urb(काष्ठा urb *urb);
पूर्णांक usb_serial_generic_prepare_ग_लिखो_buffer(काष्ठा usb_serial_port *port, व्योम *dest, माप_प्रकार size);

#अगर defined(CONFIG_USB_SERIAL_CONSOLE) && defined(CONFIG_MAGIC_SYSRQ)
पूर्णांक usb_serial_handle_sysrq_अक्षर(काष्ठा usb_serial_port *port, अचिन्हित पूर्णांक ch);
पूर्णांक usb_serial_handle_अवरोध(काष्ठा usb_serial_port *port);
#अन्यथा
अटल अंतरभूत पूर्णांक usb_serial_handle_sysrq_अक्षर(काष्ठा usb_serial_port *port, अचिन्हित पूर्णांक ch)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक usb_serial_handle_अवरोध(काष्ठा usb_serial_port *port)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम usb_serial_handle_dcd_change(काष्ठा usb_serial_port *usb_port,
		काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक status);


पूर्णांक usb_serial_bus_रेजिस्टर(काष्ठा usb_serial_driver *device);
व्योम usb_serial_bus_deरेजिस्टर(काष्ठा usb_serial_driver *device);

बाह्य काष्ठा bus_type usb_serial_bus_type;
बाह्य काष्ठा tty_driver *usb_serial_tty_driver;

अटल अंतरभूत व्योम usb_serial_debug_data(काष्ठा device *dev,
					 स्थिर अक्षर *function, पूर्णांक size,
					 स्थिर अचिन्हित अक्षर *data)
अणु
	dev_dbg(dev, "%s - length = %d, data = %*ph\n",
		function, size, size, data);
पूर्ण

/*
 * Macro क्रम reporting errors in ग_लिखो path to aव्योम inअगरinite loop
 * when port is used as a console.
 */
#घोषणा dev_err_console(usport, fmt, ...)				\
करो अणु									\
	अटल bool __prपूर्णांक_once;					\
	काष्ठा usb_serial_port *__port = (usport);			\
									\
	अगर (!__port->port.console || !__prपूर्णांक_once) अणु			\
		__prपूर्णांक_once = true;					\
		dev_err(&__port->dev, fmt, ##__VA_ARGS__);		\
	पूर्ण								\
पूर्ण जबतक (0)

/*
 * module_usb_serial_driver() - Helper macro क्रम रेजिस्टरing a USB Serial driver
 * @__serial_drivers: list of usb_serial drivers to रेजिस्टर
 * @__ids: all device ids that @__serial_drivers bind to
 *
 * Helper macro क्रम USB serial drivers which करो not करो anything special
 * in module init/निकास. This eliminates a lot of boilerplate. Each
 * module may only use this macro once, and calling it replaces
 * module_init() and module_निकास()
 *
 */
#घोषणा usb_serial_module_driver(__name, __serial_drivers, __ids)	\
अटल पूर्णांक __init usb_serial_module_init(व्योम)				\
अणु									\
	वापस usb_serial_रेजिस्टर_drivers(__serial_drivers,		\
					   __name, __ids);		\
पूर्ण									\
module_init(usb_serial_module_init);					\
अटल व्योम __निकास usb_serial_module_निकास(व्योम)				\
अणु									\
	usb_serial_deरेजिस्टर_drivers(__serial_drivers);		\
पूर्ण									\
module_निकास(usb_serial_module_निकास);

#घोषणा module_usb_serial_driver(__serial_drivers, __ids)		\
	usb_serial_module_driver(KBUILD_MODNAME, __serial_drivers, __ids)

#पूर्ण_अगर /* __LINUX_USB_SERIAL_H */

