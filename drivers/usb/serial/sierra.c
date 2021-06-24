<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
  USB Driver क्रम Sierra Wireless

  Copyright (C) 2006, 2007, 2008  Kevin Lloyd <klloyd@sierrawireless.com>,

  Copyright (C) 2008, 2009  Elina Pasheva, Matthew Safar, Rory Filer
			<linux@sierrawireless.com>

  IMPORTANT DISCLAIMER: This driver is not commercially supported by
  Sierra Wireless. Use at your own risk.

  Portions based on the option driver by Matthias Urlichs <smurf@smurf.noris.de>
  Whom based his on the Keyspan driver by Hugh Blemings <hugh@blemings.org>
*/
/* Uncomment to log function calls */
/* #घोषणा DEBUG */

#घोषणा DRIVER_AUTHOR "Kevin Lloyd, Elina Pasheva, Matthew Safar, Rory Filer"
#घोषणा DRIVER_DESC "USB Driver for Sierra Wireless USB modems"

#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/tty.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

#घोषणा SWIMS_USB_REQUEST_SetPower	0x00
#घोषणा SWIMS_USB_REQUEST_SetNmea	0x07

#घोषणा N_IN_URB_HM	8
#घोषणा N_OUT_URB_HM	64
#घोषणा N_IN_URB	4
#घोषणा N_OUT_URB	4
#घोषणा IN_BUFLEN	4096

#घोषणा MAX_TRANSFER		(PAGE_SIZE - 512)
/* MAX_TRANSFER is chosen so that the VM is not stressed by
   allocations > PAGE_SIZE and the number of packets in a page
   is an पूर्णांकeger 512 is the largest possible packet on EHCI */

अटल bool nmea;

काष्ठा sierra_अगरace_list अणु
	स्थिर u8 *nums;		/* array of पूर्णांकerface numbers */
	माप_प्रकार count;		/* number of elements in array */
पूर्ण;

काष्ठा sierra_पूर्णांकf_निजी अणु
	spinlock_t susp_lock;
	अचिन्हित पूर्णांक suspended:1;
	पूर्णांक in_flight;
	अचिन्हित पूर्णांक खोलो_ports;
पूर्ण;

अटल पूर्णांक sierra_set_घातer_state(काष्ठा usb_device *udev, __u16 swiState)
अणु
	वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			SWIMS_USB_REQUEST_SetPower,	/* __u8 request      */
			USB_TYPE_VENDOR,		/* __u8 request type */
			swiState,			/* __u16 value       */
			0,				/* __u16 index       */
			शून्य,				/* व्योम *data        */
			0,				/* __u16 size 	     */
			USB_CTRL_SET_TIMEOUT);		/* पूर्णांक समयout 	     */
पूर्ण

अटल पूर्णांक sierra_vsc_set_nmea(काष्ठा usb_device *udev, __u16 enable)
अणु
	वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			SWIMS_USB_REQUEST_SetNmea,	/* __u8 request      */
			USB_TYPE_VENDOR,		/* __u8 request type */
			enable,				/* __u16 value       */
			0x0000,				/* __u16 index       */
			शून्य,				/* व्योम *data        */
			0,				/* __u16 size 	     */
			USB_CTRL_SET_TIMEOUT);		/* पूर्णांक समयout       */
पूर्ण

अटल पूर्णांक sierra_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	पूर्णांक num_ports = 0;
	u8 अगरnum, numendpoपूर्णांकs;

	अगरnum = serial->पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;
	numendpoपूर्णांकs = serial->पूर्णांकerface->cur_altsetting->desc.bNumEndpoपूर्णांकs;

	/* Dummy पूर्णांकerface present on some SKUs should be ignored */
	अगर (अगरnum == 0x99)
		num_ports = 0;
	अन्यथा अगर (numendpoपूर्णांकs <= 3)
		num_ports = 1;
	अन्यथा
		num_ports = (numendpoपूर्णांकs-1)/2;
	वापस num_ports;
पूर्ण

अटल bool is_listed(स्थिर u8 अगरnum, स्थिर काष्ठा sierra_अगरace_list *list)
अणु
	पूर्णांक i;

	अगर (!list)
		वापस false;

	क्रम (i = 0; i < list->count; i++) अणु
		अगर (list->nums[i] == अगरnum)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल u8 sierra_पूर्णांकerface_num(काष्ठा usb_serial *serial)
अणु
	वापस serial->पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;
पूर्ण

अटल पूर्णांक sierra_probe(काष्ठा usb_serial *serial,
			स्थिर काष्ठा usb_device_id *id)
अणु
	स्थिर काष्ठा sierra_अगरace_list *ignore_list;
	पूर्णांक result = 0;
	काष्ठा usb_device *udev;
	u8 अगरnum;

	udev = serial->dev;
	अगरnum = sierra_पूर्णांकerface_num(serial);

	/*
	 * If this पूर्णांकerface supports more than 1 alternate
	 * select the 2nd one
	 */
	अगर (serial->पूर्णांकerface->num_altsetting == 2) अणु
		dev_dbg(&udev->dev, "Selecting alt setting for interface %d\n",
			अगरnum);
		/* We know the alternate setting is 1 क्रम the MC8785 */
		usb_set_पूर्णांकerface(udev, अगरnum, 1);
	पूर्ण

	ignore_list = (स्थिर काष्ठा sierra_अगरace_list *)id->driver_info;

	अगर (is_listed(अगरnum, ignore_list)) अणु
		dev_dbg(&serial->dev->dev, "Ignoring interface #%d\n", अगरnum);
		वापस -ENODEV;
	पूर्ण

	वापस result;
पूर्ण

/* पूर्णांकerfaces with higher memory requirements */
अटल स्थिर u8 hi_memory_typeA_अगरaces[] = अणु 0, 2 पूर्ण;
अटल स्थिर काष्ठा sierra_अगरace_list typeA_पूर्णांकerface_list = अणु
	.nums	= hi_memory_typeA_अगरaces,
	.count	= ARRAY_SIZE(hi_memory_typeA_अगरaces),
पूर्ण;

अटल स्थिर u8 hi_memory_typeB_अगरaces[] = अणु 3, 4, 5, 6 पूर्ण;
अटल स्थिर काष्ठा sierra_अगरace_list typeB_पूर्णांकerface_list = अणु
	.nums	= hi_memory_typeB_अगरaces,
	.count	= ARRAY_SIZE(hi_memory_typeB_अगरaces),
पूर्ण;

/* 'ignorelist' of पूर्णांकerfaces not served by this driver */
अटल स्थिर u8 direct_ip_non_serial_अगरaces[] = अणु 7, 8, 9, 10, 11, 19, 20 पूर्ण;
अटल स्थिर काष्ठा sierra_अगरace_list direct_ip_पूर्णांकerface_ignore = अणु
	.nums	= direct_ip_non_serial_अगरaces,
	.count	= ARRAY_SIZE(direct_ip_non_serial_अगरaces),
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x0F3D, 0x0112) पूर्ण, /* Airprime/Sierra PC 5220 */
	अणु USB_DEVICE(0x03F0, 0x1B1D) पूर्ण,	/* HP ev2200 a.k.a MC5720 */
	अणु USB_DEVICE(0x03F0, 0x211D) पूर्ण, /* HP ev2210 a.k.a MC5725 */
	अणु USB_DEVICE(0x03F0, 0x1E1D) पूर्ण,	/* HP hs2300 a.k.a MC8775 */

	अणु USB_DEVICE(0x1199, 0x0017) पूर्ण,	/* Sierra Wireless EM5625 */
	अणु USB_DEVICE(0x1199, 0x0018) पूर्ण,	/* Sierra Wireless MC5720 */
	अणु USB_DEVICE(0x1199, 0x0218) पूर्ण,	/* Sierra Wireless MC5720 */
	अणु USB_DEVICE(0x1199, 0x0020) पूर्ण,	/* Sierra Wireless MC5725 */
	अणु USB_DEVICE(0x1199, 0x0220) पूर्ण,	/* Sierra Wireless MC5725 */
	अणु USB_DEVICE(0x1199, 0x0022) पूर्ण,	/* Sierra Wireless EM5725 */
	अणु USB_DEVICE(0x1199, 0x0024) पूर्ण,	/* Sierra Wireless MC5727 */
	अणु USB_DEVICE(0x1199, 0x0224) पूर्ण,	/* Sierra Wireless MC5727 */
	अणु USB_DEVICE(0x1199, 0x0019) पूर्ण,	/* Sierra Wireless AirCard 595 */
	अणु USB_DEVICE(0x1199, 0x0021) पूर्ण,	/* Sierra Wireless AirCard 597E */
	अणु USB_DEVICE(0x1199, 0x0112) पूर्ण, /* Sierra Wireless AirCard 580 */
	अणु USB_DEVICE(0x1199, 0x0120) पूर्ण,	/* Sierra Wireless USB Dongle 595U */
	अणु USB_DEVICE(0x1199, 0x0301) पूर्ण,	/* Sierra Wireless USB Dongle 250U */
	/* Sierra Wireless C597 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1199, 0x0023, 0xFF, 0xFF, 0xFF) पूर्ण,
	/* Sierra Wireless T598 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1199, 0x0025, 0xFF, 0xFF, 0xFF) पूर्ण,
	अणु USB_DEVICE(0x1199, 0x0026) पूर्ण, /* Sierra Wireless T11 */
	अणु USB_DEVICE(0x1199, 0x0027) पूर्ण, /* Sierra Wireless AC402 */
	अणु USB_DEVICE(0x1199, 0x0028) पूर्ण, /* Sierra Wireless MC5728 */
	अणु USB_DEVICE(0x1199, 0x0029) पूर्ण, /* Sierra Wireless Device */

	अणु USB_DEVICE(0x1199, 0x6802) पूर्ण,	/* Sierra Wireless MC8755 */
	अणु USB_DEVICE(0x1199, 0x6803) पूर्ण,	/* Sierra Wireless MC8765 */
	अणु USB_DEVICE(0x1199, 0x6804) पूर्ण,	/* Sierra Wireless MC8755 */
	अणु USB_DEVICE(0x1199, 0x6805) पूर्ण,	/* Sierra Wireless MC8765 */
	अणु USB_DEVICE(0x1199, 0x6808) पूर्ण,	/* Sierra Wireless MC8755 */
	अणु USB_DEVICE(0x1199, 0x6809) पूर्ण,	/* Sierra Wireless MC8765 */
	अणु USB_DEVICE(0x1199, 0x6812) पूर्ण,	/* Sierra Wireless MC8775 & AC 875U */
	अणु USB_DEVICE(0x1199, 0x6813) पूर्ण,	/* Sierra Wireless MC8775 */
	अणु USB_DEVICE(0x1199, 0x6815) पूर्ण,	/* Sierra Wireless MC8775 */
	अणु USB_DEVICE(0x1199, 0x6816) पूर्ण,	/* Sierra Wireless MC8775 */
	अणु USB_DEVICE(0x1199, 0x6820) पूर्ण,	/* Sierra Wireless AirCard 875 */
	अणु USB_DEVICE(0x1199, 0x6821) पूर्ण,	/* Sierra Wireless AirCard 875U */
	अणु USB_DEVICE(0x1199, 0x6822) पूर्ण,	/* Sierra Wireless AirCard 875E */
	अणु USB_DEVICE(0x1199, 0x6832) पूर्ण,	/* Sierra Wireless MC8780 */
	अणु USB_DEVICE(0x1199, 0x6833) पूर्ण,	/* Sierra Wireless MC8781 */
	अणु USB_DEVICE(0x1199, 0x6834) पूर्ण,	/* Sierra Wireless MC8780 */
	अणु USB_DEVICE(0x1199, 0x6835) पूर्ण,	/* Sierra Wireless MC8781 */
	अणु USB_DEVICE(0x1199, 0x6838) पूर्ण,	/* Sierra Wireless MC8780 */
	अणु USB_DEVICE(0x1199, 0x6839) पूर्ण,	/* Sierra Wireless MC8781 */
	अणु USB_DEVICE(0x1199, 0x683A) पूर्ण,	/* Sierra Wireless MC8785 */
	अणु USB_DEVICE(0x1199, 0x683B) पूर्ण,	/* Sierra Wireless MC8785 Composite */
	/* Sierra Wireless MC8790, MC8791, MC8792 Composite */
	अणु USB_DEVICE(0x1199, 0x683C) पूर्ण,
	अणु USB_DEVICE(0x1199, 0x683D) पूर्ण,	/* Sierra Wireless MC8791 Composite */
	/* Sierra Wireless MC8790, MC8791, MC8792 */
	अणु USB_DEVICE(0x1199, 0x683E) पूर्ण,
	अणु USB_DEVICE(0x1199, 0x6850) पूर्ण,	/* Sierra Wireless AirCard 880 */
	अणु USB_DEVICE(0x1199, 0x6851) पूर्ण,	/* Sierra Wireless AirCard 881 */
	अणु USB_DEVICE(0x1199, 0x6852) पूर्ण,	/* Sierra Wireless AirCard 880 E */
	अणु USB_DEVICE(0x1199, 0x6853) पूर्ण,	/* Sierra Wireless AirCard 881 E */
	अणु USB_DEVICE(0x1199, 0x6855) पूर्ण,	/* Sierra Wireless AirCard 880 U */
	अणु USB_DEVICE(0x1199, 0x6856) पूर्ण,	/* Sierra Wireless AirCard 881 U */
	अणु USB_DEVICE(0x1199, 0x6859) पूर्ण,	/* Sierra Wireless AirCard 885 E */
	अणु USB_DEVICE(0x1199, 0x685A) पूर्ण,	/* Sierra Wireless AirCard 885 E */
	/* Sierra Wireless C885 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1199, 0x6880, 0xFF, 0xFF, 0xFF)पूर्ण,
	/* Sierra Wireless C888, Air Card 501, USB 303, USB 304 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1199, 0x6890, 0xFF, 0xFF, 0xFF)पूर्ण,
	/* Sierra Wireless C22/C33 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1199, 0x6891, 0xFF, 0xFF, 0xFF)पूर्ण,
	/* Sierra Wireless HSPA Non-Composite Device */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1199, 0x6892, 0xFF, 0xFF, 0xFF)पूर्ण,
	अणु USB_DEVICE(0x1199, 0x6893) पूर्ण,	/* Sierra Wireless Device */
	/* Sierra Wireless Direct IP modems */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1199, 0x68A3, 0xFF, 0xFF, 0xFF),
	  .driver_info = (kernel_uदीर्घ_t)&direct_ip_पूर्णांकerface_ignore
	पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1199, 0x68AA, 0xFF, 0xFF, 0xFF),
	  .driver_info = (kernel_uदीर्घ_t)&direct_ip_पूर्णांकerface_ignore
	पूर्ण,
	अणु USB_DEVICE(0x1199, 0x68AB) पूर्ण, /* Sierra Wireless AR8550 */
	/* AT&T Direct IP LTE modems */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x0F3D, 0x68AA, 0xFF, 0xFF, 0xFF),
	  .driver_info = (kernel_uदीर्घ_t)&direct_ip_पूर्णांकerface_ignore
	पूर्ण,
	/* Airprime/Sierra Wireless Direct IP modems */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x0F3D, 0x68A3, 0xFF, 0xFF, 0xFF),
	  .driver_info = (kernel_uदीर्घ_t)&direct_ip_पूर्णांकerface_ignore
	पूर्ण,

	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);


काष्ठा sierra_port_निजी अणु
	spinlock_t lock;	/* lock the काष्ठाure */
	पूर्णांक outstanding_urbs;	/* number of out urbs in flight */
	काष्ठा usb_anchor active;
	काष्ठा usb_anchor delayed;

	पूर्णांक num_out_urbs;
	पूर्णांक num_in_urbs;
	/* Input endpoपूर्णांकs and buffers क्रम this port */
	काष्ठा urb *in_urbs[N_IN_URB_HM];

	/* Settings क्रम the port */
	पूर्णांक rts_state;	/* Handshaking pins (outमाला_दो) */
	पूर्णांक dtr_state;
	पूर्णांक cts_state;	/* Handshaking pins (inमाला_दो) */
	पूर्णांक dsr_state;
	पूर्णांक dcd_state;
	पूर्णांक ri_state;
पूर्ण;

अटल पूर्णांक sierra_send_setup(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा sierra_port_निजी *portdata;
	__u16 पूर्णांकerface = 0;
	पूर्णांक val = 0;
	पूर्णांक करो_send = 0;
	पूर्णांक retval;

	portdata = usb_get_serial_port_data(port);

	अगर (portdata->dtr_state)
		val |= 0x01;
	अगर (portdata->rts_state)
		val |= 0x02;

	/* If composite device then properly report पूर्णांकerface */
	अगर (serial->num_ports == 1) अणु
		पूर्णांकerface = sierra_पूर्णांकerface_num(serial);
		/* Control message is sent only to पूर्णांकerfaces with
		 * पूर्णांकerrupt_in endpoपूर्णांकs
		 */
		अगर (port->पूर्णांकerrupt_in_urb) अणु
			/* send control message */
			करो_send = 1;
		पूर्ण
	पूर्ण

	/* Otherwise the need to करो non-composite mapping */
	अन्यथा अणु
		अगर (port->bulk_out_endpoपूर्णांकAddress == 2)
			पूर्णांकerface = 0;
		अन्यथा अगर (port->bulk_out_endpoपूर्णांकAddress == 4)
			पूर्णांकerface = 1;
		अन्यथा अगर (port->bulk_out_endpoपूर्णांकAddress == 5)
			पूर्णांकerface = 2;

		करो_send = 1;
	पूर्ण
	अगर (!करो_send)
		वापस 0;

	retval = usb_स्वतःpm_get_पूर्णांकerface(serial->पूर्णांकerface);
	अगर (retval < 0)
		वापस retval;

	retval = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
		0x22, 0x21, val, पूर्णांकerface, शून्य, 0, USB_CTRL_SET_TIMEOUT);
	usb_स्वतःpm_put_पूर्णांकerface(serial->पूर्णांकerface);

	वापस retval;
पूर्ण

अटल पूर्णांक sierra_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित पूर्णांक value;
	काष्ठा sierra_port_निजी *portdata;

	portdata = usb_get_serial_port_data(port);

	value = ((portdata->rts_state) ? TIOCM_RTS : 0) |
		((portdata->dtr_state) ? TIOCM_DTR : 0) |
		((portdata->cts_state) ? TIOCM_CTS : 0) |
		((portdata->dsr_state) ? TIOCM_DSR : 0) |
		((portdata->dcd_state) ? TIOCM_CAR : 0) |
		((portdata->ri_state) ? TIOCM_RNG : 0);

	वापस value;
पूर्ण

अटल पूर्णांक sierra_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा sierra_port_निजी *portdata;

	portdata = usb_get_serial_port_data(port);

	अगर (set & TIOCM_RTS)
		portdata->rts_state = 1;
	अगर (set & TIOCM_DTR)
		portdata->dtr_state = 1;

	अगर (clear & TIOCM_RTS)
		portdata->rts_state = 0;
	अगर (clear & TIOCM_DTR)
		portdata->dtr_state = 0;
	वापस sierra_send_setup(port);
पूर्ण

अटल व्योम sierra_release_urb(काष्ठा urb *urb)
अणु
	अगर (urb) अणु
		kमुक्त(urb->transfer_buffer);
		usb_मुक्त_urb(urb);
	पूर्ण
पूर्ण

अटल व्योम sierra_outdat_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा sierra_port_निजी *portdata = usb_get_serial_port_data(port);
	काष्ठा sierra_पूर्णांकf_निजी *पूर्णांकfdata;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	पूर्णांकfdata = usb_get_serial_data(port->serial);

	/* मुक्त up the transfer buffer, as usb_मुक्त_urb() करोes not करो this */
	kमुक्त(urb->transfer_buffer);
	usb_स्वतःpm_put_पूर्णांकerface_async(port->serial->पूर्णांकerface);
	अगर (status)
		dev_dbg(&port->dev, "%s - nonzero write bulk status "
		    "received: %d\n", __func__, status);

	spin_lock_irqsave(&portdata->lock, flags);
	--portdata->outstanding_urbs;
	spin_unlock_irqrestore(&portdata->lock, flags);
	spin_lock_irqsave(&पूर्णांकfdata->susp_lock, flags);
	--पूर्णांकfdata->in_flight;
	spin_unlock_irqrestore(&पूर्णांकfdata->susp_lock, flags);

	usb_serial_port_softपूर्णांक(port);
पूर्ण

/* Write */
अटल पूर्णांक sierra_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
					स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा sierra_port_निजी *portdata;
	काष्ठा sierra_पूर्णांकf_निजी *पूर्णांकfdata;
	काष्ठा usb_serial *serial = port->serial;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर *buffer;
	काष्ठा urb *urb;
	माप_प्रकार ग_लिखोsize = min((माप_प्रकार)count, (माप_प्रकार)MAX_TRANSFER);
	पूर्णांक retval = 0;

	/* verअगरy that we actually have some data to ग_लिखो */
	अगर (count == 0)
		वापस 0;

	portdata = usb_get_serial_port_data(port);
	पूर्णांकfdata = usb_get_serial_data(serial);

	dev_dbg(&port->dev, "%s: write (%zd bytes)\n", __func__, ग_लिखोsize);
	spin_lock_irqsave(&portdata->lock, flags);
	dev_dbg(&port->dev, "%s - outstanding_urbs: %d\n", __func__,
		portdata->outstanding_urbs);
	अगर (portdata->outstanding_urbs > portdata->num_out_urbs) अणु
		spin_unlock_irqrestore(&portdata->lock, flags);
		dev_dbg(&port->dev, "%s - write limit hit\n", __func__);
		वापस 0;
	पूर्ण
	portdata->outstanding_urbs++;
	dev_dbg(&port->dev, "%s - 1, outstanding_urbs: %d\n", __func__,
		portdata->outstanding_urbs);
	spin_unlock_irqrestore(&portdata->lock, flags);

	retval = usb_स्वतःpm_get_पूर्णांकerface_async(serial->पूर्णांकerface);
	अगर (retval < 0) अणु
		spin_lock_irqsave(&portdata->lock, flags);
		portdata->outstanding_urbs--;
		spin_unlock_irqrestore(&portdata->lock, flags);
		जाओ error_simple;
	पूर्ण

	buffer = kदो_स्मृति(ग_लिखोsize, GFP_ATOMIC);
	अगर (!buffer) अणु
		retval = -ENOMEM;
		जाओ error_no_buffer;
	पूर्ण

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		retval = -ENOMEM;
		जाओ error_no_urb;
	पूर्ण

	स_नकल(buffer, buf, ग_लिखोsize);

	usb_serial_debug_data(&port->dev, __func__, ग_लिखोsize, buffer);

	usb_fill_bulk_urb(urb, serial->dev,
			  usb_sndbulkpipe(serial->dev,
					  port->bulk_out_endpoपूर्णांकAddress),
			  buffer, ग_लिखोsize, sierra_outdat_callback, port);

	/* Handle the need to send a zero length packet */
	urb->transfer_flags |= URB_ZERO_PACKET;

	spin_lock_irqsave(&पूर्णांकfdata->susp_lock, flags);

	अगर (पूर्णांकfdata->suspended) अणु
		usb_anchor_urb(urb, &portdata->delayed);
		spin_unlock_irqrestore(&पूर्णांकfdata->susp_lock, flags);
		जाओ skip_घातer;
	पूर्ण अन्यथा अणु
		usb_anchor_urb(urb, &portdata->active);
	पूर्ण
	/* send it करोwn the pipe */
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval) अणु
		usb_unanchor_urb(urb);
		spin_unlock_irqrestore(&पूर्णांकfdata->susp_lock, flags);
		dev_err(&port->dev, "%s - usb_submit_urb(write bulk) failed "
			"with status = %d\n", __func__, retval);
		जाओ error;
	पूर्ण अन्यथा अणु
		पूर्णांकfdata->in_flight++;
		spin_unlock_irqrestore(&पूर्णांकfdata->susp_lock, flags);
	पूर्ण

skip_घातer:
	/* we are करोne with this urb, so let the host driver
	 * really मुक्त it when it is finished with it */
	usb_मुक्त_urb(urb);

	वापस ग_लिखोsize;
error:
	usb_मुक्त_urb(urb);
error_no_urb:
	kमुक्त(buffer);
error_no_buffer:
	spin_lock_irqsave(&portdata->lock, flags);
	--portdata->outstanding_urbs;
	dev_dbg(&port->dev, "%s - 2. outstanding_urbs: %d\n", __func__,
		portdata->outstanding_urbs);
	spin_unlock_irqrestore(&portdata->lock, flags);
	usb_स्वतःpm_put_पूर्णांकerface_async(serial->पूर्णांकerface);
error_simple:
	वापस retval;
पूर्ण

अटल व्योम sierra_indat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक err;
	पूर्णांक endpoपूर्णांक;
	काष्ठा usb_serial_port *port;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	endpoपूर्णांक = usb_pipeendpoपूर्णांक(urb->pipe);
	port = urb->context;

	अगर (status) अणु
		dev_dbg(&port->dev, "%s: nonzero status: %d on"
			" endpoint %02x\n", __func__, status, endpoपूर्णांक);
	पूर्ण अन्यथा अणु
		अगर (urb->actual_length) अणु
			tty_insert_flip_string(&port->port, data,
				urb->actual_length);
			tty_flip_buffer_push(&port->port);

			usb_serial_debug_data(&port->dev, __func__,
					      urb->actual_length, data);
		पूर्ण अन्यथा अणु
			dev_dbg(&port->dev, "%s: empty read urb"
				" received\n", __func__);
		पूर्ण
	पूर्ण

	/* Resubmit urb so we जारी receiving */
	अगर (status != -ESHUTDOWN && status != -EPERM) अणु
		usb_mark_last_busy(port->serial->dev);
		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (err && err != -EPERM)
			dev_err(&port->dev, "resubmit read urb failed."
				"(%d)\n", err);
	पूर्ण
पूर्ण

अटल व्योम sierra_instat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक err;
	पूर्णांक status = urb->status;
	काष्ठा usb_serial_port *port =  urb->context;
	काष्ठा sierra_port_निजी *portdata = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;

	dev_dbg(&port->dev, "%s: urb %p port %p has data %p\n", __func__,
		urb, port, portdata);

	अगर (status == 0) अणु
		काष्ठा usb_ctrlrequest *req_pkt = urb->transfer_buffer;

		अगर (!req_pkt) अणु
			dev_dbg(&port->dev, "%s: NULL req_pkt\n",
				__func__);
			वापस;
		पूर्ण
		अगर ((req_pkt->bRequestType == 0xA1) &&
				(req_pkt->bRequest == 0x20)) अणु
			पूर्णांक old_dcd_state;
			अचिन्हित अक्षर संकेतs = *((अचिन्हित अक्षर *)
					urb->transfer_buffer +
					माप(काष्ठा usb_ctrlrequest));

			dev_dbg(&port->dev, "%s: signal x%x\n", __func__,
				संकेतs);

			old_dcd_state = portdata->dcd_state;
			portdata->cts_state = 1;
			portdata->dcd_state = ((संकेतs & 0x01) ? 1 : 0);
			portdata->dsr_state = ((संकेतs & 0x02) ? 1 : 0);
			portdata->ri_state = ((संकेतs & 0x08) ? 1 : 0);

			अगर (old_dcd_state && !portdata->dcd_state)
				tty_port_tty_hangup(&port->port, true);
		पूर्ण अन्यथा अणु
			dev_dbg(&port->dev, "%s: type %x req %x\n",
				__func__, req_pkt->bRequestType,
				req_pkt->bRequest);
		पूर्ण
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "%s: error %d\n", __func__, status);

	/* Resubmit urb so we जारी receiving IRQ data */
	अगर (status != -ESHUTDOWN && status != -ENOENT) अणु
		usb_mark_last_busy(serial->dev);
		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (err && err != -EPERM)
			dev_err(&port->dev, "%s: resubmit intr urb "
				"failed. (%d)\n", __func__, err);
	पूर्ण
पूर्ण

अटल पूर्णांक sierra_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा sierra_port_निजी *portdata = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	/* try to give a good number back based on अगर we have any मुक्त urbs at
	 * this poपूर्णांक in समय */
	spin_lock_irqsave(&portdata->lock, flags);
	अगर (portdata->outstanding_urbs > (portdata->num_out_urbs * 2) / 3) अणु
		spin_unlock_irqrestore(&portdata->lock, flags);
		dev_dbg(&port->dev, "%s - write limit hit\n", __func__);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&portdata->lock, flags);

	वापस 2048;
पूर्ण

अटल पूर्णांक sierra_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा sierra_port_निजी *portdata = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक अक्षरs;

	/* NOTE: This overcounts somewhat. */
	spin_lock_irqsave(&portdata->lock, flags);
	अक्षरs = portdata->outstanding_urbs * MAX_TRANSFER;
	spin_unlock_irqrestore(&portdata->lock, flags);

	dev_dbg(&port->dev, "%s - %d\n", __func__, अक्षरs);

	वापस अक्षरs;
पूर्ण

अटल व्योम sierra_stop_rx_urbs(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक i;
	काष्ठा sierra_port_निजी *portdata = usb_get_serial_port_data(port);

	क्रम (i = 0; i < portdata->num_in_urbs; i++)
		usb_समाप्त_urb(portdata->in_urbs[i]);

	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
पूर्ण

अटल पूर्णांक sierra_submit_rx_urbs(काष्ठा usb_serial_port *port, gfp_t mem_flags)
अणु
	पूर्णांक ok_cnt;
	पूर्णांक err = -EINVAL;
	पूर्णांक i;
	काष्ठा urb *urb;
	काष्ठा sierra_port_निजी *portdata = usb_get_serial_port_data(port);

	ok_cnt = 0;
	क्रम (i = 0; i < portdata->num_in_urbs; i++) अणु
		urb = portdata->in_urbs[i];
		अगर (!urb)
			जारी;
		err = usb_submit_urb(urb, mem_flags);
		अगर (err) अणु
			dev_err(&port->dev, "%s: submit urb failed: %d\n",
				__func__, err);
		पूर्ण अन्यथा अणु
			ok_cnt++;
		पूर्ण
	पूर्ण

	अगर (ok_cnt && port->पूर्णांकerrupt_in_urb) अणु
		err = usb_submit_urb(port->पूर्णांकerrupt_in_urb, mem_flags);
		अगर (err) अणु
			dev_err(&port->dev, "%s: submit intr urb failed: %d\n",
				__func__, err);
		पूर्ण
	पूर्ण

	अगर (ok_cnt > 0) /* at least one rx urb submitted */
		वापस 0;
	अन्यथा
		वापस err;
पूर्ण

अटल काष्ठा urb *sierra_setup_urb(काष्ठा usb_serial *serial, पूर्णांक endpoपूर्णांक,
					पूर्णांक dir, व्योम *ctx, पूर्णांक len,
					gfp_t mem_flags,
					usb_complete_t callback)
अणु
	काष्ठा urb	*urb;
	u8		*buf;

	urb = usb_alloc_urb(0, mem_flags);
	अगर (!urb)
		वापस शून्य;

	buf = kदो_स्मृति(len, mem_flags);
	अगर (buf) अणु
		/* Fill URB using supplied data */
		usb_fill_bulk_urb(urb, serial->dev,
			usb_sndbulkpipe(serial->dev, endpoपूर्णांक) | dir,
			buf, len, callback, ctx);

		dev_dbg(&serial->dev->dev, "%s %c u : %p d:%p\n", __func__,
				dir == USB_सूची_IN ? 'i' : 'o', urb, buf);
	पूर्ण अन्यथा अणु
		sierra_release_urb(urb);
		urb = शून्य;
	पूर्ण

	वापस urb;
पूर्ण

अटल व्योम sierra_बंद(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक i;
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा sierra_port_निजी *portdata;
	काष्ठा sierra_पूर्णांकf_निजी *पूर्णांकfdata = usb_get_serial_data(serial);
	काष्ठा urb *urb;

	portdata = usb_get_serial_port_data(port);

	/*
	 * Need to take susp_lock to make sure port is not alपढ़ोy being
	 * resumed, but no need to hold it due to initialized
	 */
	spin_lock_irq(&पूर्णांकfdata->susp_lock);
	अगर (--पूर्णांकfdata->खोलो_ports == 0)
		serial->पूर्णांकerface->needs_remote_wakeup = 0;
	spin_unlock_irq(&पूर्णांकfdata->susp_lock);

	क्रम (;;) अणु
		urb = usb_get_from_anchor(&portdata->delayed);
		अगर (!urb)
			अवरोध;
		kमुक्त(urb->transfer_buffer);
		usb_मुक्त_urb(urb);
		usb_स्वतःpm_put_पूर्णांकerface_async(serial->पूर्णांकerface);
		spin_lock_irq(&portdata->lock);
		portdata->outstanding_urbs--;
		spin_unlock_irq(&portdata->lock);
	पूर्ण

	sierra_stop_rx_urbs(port);
	usb_समाप्त_anchored_urbs(&portdata->active);

	क्रम (i = 0; i < portdata->num_in_urbs; i++) अणु
		sierra_release_urb(portdata->in_urbs[i]);
		portdata->in_urbs[i] = शून्य;
	पूर्ण

	usb_स्वतःpm_get_पूर्णांकerface_no_resume(serial->पूर्णांकerface);
पूर्ण

अटल पूर्णांक sierra_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा sierra_port_निजी *portdata;
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा sierra_पूर्णांकf_निजी *पूर्णांकfdata = usb_get_serial_data(serial);
	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक endpoपूर्णांक;
	काष्ठा urb *urb;

	portdata = usb_get_serial_port_data(port);

	endpoपूर्णांक = port->bulk_in_endpoपूर्णांकAddress;
	क्रम (i = 0; i < portdata->num_in_urbs; i++) अणु
		urb = sierra_setup_urb(serial, endpoपूर्णांक, USB_सूची_IN, port,
					IN_BUFLEN, GFP_KERNEL,
					sierra_indat_callback);
		portdata->in_urbs[i] = urb;
	पूर्ण
	/* clear halt condition */
	usb_clear_halt(serial->dev,
			usb_sndbulkpipe(serial->dev, endpoपूर्णांक) | USB_सूची_IN);

	err = sierra_submit_rx_urbs(port, GFP_KERNEL);
	अगर (err)
		जाओ err_submit;

	spin_lock_irq(&पूर्णांकfdata->susp_lock);
	अगर (++पूर्णांकfdata->खोलो_ports == 1)
		serial->पूर्णांकerface->needs_remote_wakeup = 1;
	spin_unlock_irq(&पूर्णांकfdata->susp_lock);
	usb_स्वतःpm_put_पूर्णांकerface(serial->पूर्णांकerface);

	वापस 0;

err_submit:
	sierra_stop_rx_urbs(port);

	क्रम (i = 0; i < portdata->num_in_urbs; i++) अणु
		sierra_release_urb(portdata->in_urbs[i]);
		portdata->in_urbs[i] = शून्य;
	पूर्ण

	वापस err;
पूर्ण


अटल व्योम sierra_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा sierra_port_निजी *portdata;

	portdata = usb_get_serial_port_data(port);
	portdata->rts_state = on;
	portdata->dtr_state = on;

	sierra_send_setup(port);
पूर्ण

अटल पूर्णांक sierra_startup(काष्ठा usb_serial *serial)
अणु
	काष्ठा sierra_पूर्णांकf_निजी *पूर्णांकfdata;

	पूर्णांकfdata = kzalloc(माप(*पूर्णांकfdata), GFP_KERNEL);
	अगर (!पूर्णांकfdata)
		वापस -ENOMEM;

	spin_lock_init(&पूर्णांकfdata->susp_lock);

	usb_set_serial_data(serial, पूर्णांकfdata);

	/* Set Device mode to D0 */
	sierra_set_घातer_state(serial->dev, 0x0000);

	/* Check NMEA and set */
	अगर (nmea)
		sierra_vsc_set_nmea(serial->dev, 1);

	वापस 0;
पूर्ण

अटल व्योम sierra_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा sierra_पूर्णांकf_निजी *पूर्णांकfdata;

	पूर्णांकfdata = usb_get_serial_data(serial);
	kमुक्त(पूर्णांकfdata);
पूर्ण

अटल पूर्णांक sierra_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा sierra_port_निजी *portdata;
	स्थिर काष्ठा sierra_अगरace_list *himemory_list;
	u8 अगरnum;

	portdata = kzalloc(माप(*portdata), GFP_KERNEL);
	अगर (!portdata)
		वापस -ENOMEM;

	spin_lock_init(&portdata->lock);
	init_usb_anchor(&portdata->active);
	init_usb_anchor(&portdata->delayed);

	/* Assume low memory requirements */
	portdata->num_out_urbs = N_OUT_URB;
	portdata->num_in_urbs  = N_IN_URB;

	/* Determine actual memory requirements */
	अगर (serial->num_ports == 1) अणु
		/* Get पूर्णांकerface number क्रम composite device */
		अगरnum = sierra_पूर्णांकerface_num(serial);
		himemory_list = &typeB_पूर्णांकerface_list;
	पूर्ण अन्यथा अणु
		/* This is really the usb-serial port number of the पूर्णांकerface
		 * rather than the पूर्णांकerface number.
		 */
		अगरnum = port->port_number;
		himemory_list = &typeA_पूर्णांकerface_list;
	पूर्ण

	अगर (is_listed(अगरnum, himemory_list)) अणु
		portdata->num_out_urbs = N_OUT_URB_HM;
		portdata->num_in_urbs  = N_IN_URB_HM;
	पूर्ण

	dev_dbg(&port->dev,
			"Memory usage (urbs) interface #%d, in=%d, out=%d\n",
			अगरnum, portdata->num_in_urbs, portdata->num_out_urbs);

	usb_set_serial_port_data(port, portdata);

	वापस 0;
पूर्ण

अटल व्योम sierra_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा sierra_port_निजी *portdata;

	portdata = usb_get_serial_port_data(port);
	usb_set_serial_port_data(port, शून्य);
	kमुक्त(portdata);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम stop_पढ़ो_ग_लिखो_urbs(काष्ठा usb_serial *serial)
अणु
	पूर्णांक i;
	काष्ठा usb_serial_port *port;
	काष्ठा sierra_port_निजी *portdata;

	/* Stop पढ़ोing/writing urbs */
	क्रम (i = 0; i < serial->num_ports; ++i) अणु
		port = serial->port[i];
		portdata = usb_get_serial_port_data(port);
		अगर (!portdata)
			जारी;
		sierra_stop_rx_urbs(port);
		usb_समाप्त_anchored_urbs(&portdata->active);
	पूर्ण
पूर्ण

अटल पूर्णांक sierra_suspend(काष्ठा usb_serial *serial, pm_message_t message)
अणु
	काष्ठा sierra_पूर्णांकf_निजी *पूर्णांकfdata = usb_get_serial_data(serial);

	spin_lock_irq(&पूर्णांकfdata->susp_lock);
	अगर (PMSG_IS_AUTO(message)) अणु
		अगर (पूर्णांकfdata->in_flight) अणु
			spin_unlock_irq(&पूर्णांकfdata->susp_lock);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	पूर्णांकfdata->suspended = 1;
	spin_unlock_irq(&पूर्णांकfdata->susp_lock);

	stop_पढ़ो_ग_लिखो_urbs(serial);

	वापस 0;
पूर्ण

/* Caller must hold susp_lock. */
अटल पूर्णांक sierra_submit_delayed_urbs(काष्ठा usb_serial_port *port)
अणु
	काष्ठा sierra_port_निजी *portdata = usb_get_serial_port_data(port);
	काष्ठा sierra_पूर्णांकf_निजी *पूर्णांकfdata;
	काष्ठा urb *urb;
	पूर्णांक ec = 0;
	पूर्णांक err;

	पूर्णांकfdata = usb_get_serial_data(port->serial);

	क्रम (;;) अणु
		urb = usb_get_from_anchor(&portdata->delayed);
		अगर (!urb)
			अवरोध;

		usb_anchor_urb(urb, &portdata->active);
		पूर्णांकfdata->in_flight++;
		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (err) अणु
			dev_err(&port->dev, "%s - submit urb failed: %d",
					__func__, err);
			ec++;
			पूर्णांकfdata->in_flight--;
			usb_unanchor_urb(urb);
			kमुक्त(urb->transfer_buffer);
			usb_मुक्त_urb(urb);

			spin_lock(&portdata->lock);
			portdata->outstanding_urbs--;
			spin_unlock(&portdata->lock);
		पूर्ण
	पूर्ण

	अगर (ec)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक sierra_resume(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा sierra_पूर्णांकf_निजी *पूर्णांकfdata = usb_get_serial_data(serial);
	पूर्णांक ec = 0;
	पूर्णांक i, err;

	spin_lock_irq(&पूर्णांकfdata->susp_lock);
	क्रम (i = 0; i < serial->num_ports; i++) अणु
		port = serial->port[i];

		अगर (!tty_port_initialized(&port->port))
			जारी;

		err = sierra_submit_delayed_urbs(port);
		अगर (err)
			ec++;

		err = sierra_submit_rx_urbs(port, GFP_ATOMIC);
		अगर (err)
			ec++;
	पूर्ण
	पूर्णांकfdata->suspended = 0;
	spin_unlock_irq(&पूर्णांकfdata->susp_lock);

	वापस ec ? -EIO : 0;
पूर्ण

#अन्यथा
#घोषणा sierra_suspend शून्य
#घोषणा sierra_resume शून्य
#पूर्ण_अगर

अटल काष्ठा usb_serial_driver sierra_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"sierra",
	पूर्ण,
	.description       = "Sierra USB modem",
	.id_table          = id_table,
	.calc_num_ports	   = sierra_calc_num_ports,
	.probe		   = sierra_probe,
	.खोलो              = sierra_खोलो,
	.बंद             = sierra_बंद,
	.dtr_rts	   = sierra_dtr_rts,
	.ग_लिखो             = sierra_ग_लिखो,
	.ग_लिखो_room        = sierra_ग_लिखो_room,
	.अक्षरs_in_buffer   = sierra_अक्षरs_in_buffer,
	.tiocmget          = sierra_tiocmget,
	.tiocmset          = sierra_tiocmset,
	.attach            = sierra_startup,
	.release           = sierra_release,
	.port_probe        = sierra_port_probe,
	.port_हटाओ       = sierra_port_हटाओ,
	.suspend	   = sierra_suspend,
	.resume		   = sierra_resume,
	.पढ़ो_पूर्णांक_callback = sierra_instat_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&sierra_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");

module_param(nmea, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(nmea, "NMEA streaming");
