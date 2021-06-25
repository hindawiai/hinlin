<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
  USB Driver layer क्रम GSM modems

  Copyright (C) 2005  Matthias Urlichs <smurf@smurf.noris.de>

  Portions copied from the Keyspan driver by Hugh Blemings <hugh@blemings.org>

  History: see the git log.

  Work sponsored by: Sigos GmbH, Germany <info@sigos.de>

  This driver exists because the "normal" serial driver करोesn't work too well
  with GSM modems. Issues:
  - data loss -- one single Receive URB is not nearly enough
  - controlling the baud rate करोesn't make sense
*/

#घोषणा DRIVER_AUTHOR "Matthias Urlichs <smurf@smurf.noris.de>"
#घोषणा DRIVER_DESC "USB Driver for GSM modems"

#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/serial.h>
#समावेश "usb-wwan.h"

/*
 * Generate DTR/RTS संकेतs on the port using the SET_CONTROL_LINE_STATE request
 * in CDC ACM.
 */
अटल पूर्णांक usb_wwan_send_setup(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा usb_wwan_port_निजी *portdata;
	पूर्णांक val = 0;
	पूर्णांक अगरnum;
	पूर्णांक res;

	portdata = usb_get_serial_port_data(port);

	अगर (portdata->dtr_state)
		val |= 0x01;
	अगर (portdata->rts_state)
		val |= 0x02;

	अगरnum = serial->पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;

	res = usb_स्वतःpm_get_पूर्णांकerface(serial->पूर्णांकerface);
	अगर (res)
		वापस res;

	res = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				0x22, 0x21, val, अगरnum, शून्य, 0,
				USB_CTRL_SET_TIMEOUT);

	usb_स्वतःpm_put_पूर्णांकerface(port->serial->पूर्णांकerface);

	वापस res;
पूर्ण

व्योम usb_wwan_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा usb_wwan_port_निजी *portdata;
	काष्ठा usb_wwan_पूर्णांकf_निजी *पूर्णांकfdata;

	पूर्णांकfdata = usb_get_serial_data(port->serial);

	अगर (!पूर्णांकfdata->use_send_setup)
		वापस;

	portdata = usb_get_serial_port_data(port);
	/* FIXME: locking */
	portdata->rts_state = on;
	portdata->dtr_state = on;

	usb_wwan_send_setup(port);
पूर्ण
EXPORT_SYMBOL(usb_wwan_dtr_rts);

पूर्णांक usb_wwan_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित पूर्णांक value;
	काष्ठा usb_wwan_port_निजी *portdata;

	portdata = usb_get_serial_port_data(port);

	value = ((portdata->rts_state) ? TIOCM_RTS : 0) |
	    ((portdata->dtr_state) ? TIOCM_DTR : 0) |
	    ((portdata->cts_state) ? TIOCM_CTS : 0) |
	    ((portdata->dsr_state) ? TIOCM_DSR : 0) |
	    ((portdata->dcd_state) ? TIOCM_CAR : 0) |
	    ((portdata->ri_state) ? TIOCM_RNG : 0);

	वापस value;
पूर्ण
EXPORT_SYMBOL(usb_wwan_tiocmget);

पूर्णांक usb_wwan_tiocmset(काष्ठा tty_काष्ठा *tty,
		      अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_wwan_port_निजी *portdata;
	काष्ठा usb_wwan_पूर्णांकf_निजी *पूर्णांकfdata;

	portdata = usb_get_serial_port_data(port);
	पूर्णांकfdata = usb_get_serial_data(port->serial);

	अगर (!पूर्णांकfdata->use_send_setup)
		वापस -EINVAL;

	/* FIXME: what locks portdata fields ? */
	अगर (set & TIOCM_RTS)
		portdata->rts_state = 1;
	अगर (set & TIOCM_DTR)
		portdata->dtr_state = 1;

	अगर (clear & TIOCM_RTS)
		portdata->rts_state = 0;
	अगर (clear & TIOCM_DTR)
		portdata->dtr_state = 0;
	वापस usb_wwan_send_setup(port);
पूर्ण
EXPORT_SYMBOL(usb_wwan_tiocmset);

पूर्णांक usb_wwan_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
		   स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा usb_wwan_port_निजी *portdata;
	काष्ठा usb_wwan_पूर्णांकf_निजी *पूर्णांकfdata;
	पूर्णांक i;
	पूर्णांक left, toकरो;
	काष्ठा urb *this_urb = शून्य;	/* spurious */
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	portdata = usb_get_serial_port_data(port);
	पूर्णांकfdata = usb_get_serial_data(port->serial);

	dev_dbg(&port->dev, "%s: write (%d chars)\n", __func__, count);

	i = 0;
	left = count;
	क्रम (i = 0; left > 0 && i < N_OUT_URB; i++) अणु
		toकरो = left;
		अगर (toकरो > OUT_BUFLEN)
			toकरो = OUT_BUFLEN;

		this_urb = portdata->out_urbs[i];
		अगर (test_and_set_bit(i, &portdata->out_busy)) अणु
			अगर (समय_beक्रमe(jअगरfies,
					portdata->tx_start_समय[i] + 10 * HZ))
				जारी;
			usb_unlink_urb(this_urb);
			जारी;
		पूर्ण
		dev_dbg(&port->dev, "%s: endpoint %d buf %d\n", __func__,
			usb_pipeendpoपूर्णांक(this_urb->pipe), i);

		err = usb_स्वतःpm_get_पूर्णांकerface_async(port->serial->पूर्णांकerface);
		अगर (err < 0) अणु
			clear_bit(i, &portdata->out_busy);
			अवरोध;
		पूर्ण

		/* send the data */
		स_नकल(this_urb->transfer_buffer, buf, toकरो);
		this_urb->transfer_buffer_length = toकरो;

		spin_lock_irqsave(&पूर्णांकfdata->susp_lock, flags);
		अगर (पूर्णांकfdata->suspended) अणु
			usb_anchor_urb(this_urb, &portdata->delayed);
			spin_unlock_irqrestore(&पूर्णांकfdata->susp_lock, flags);
		पूर्ण अन्यथा अणु
			पूर्णांकfdata->in_flight++;
			spin_unlock_irqrestore(&पूर्णांकfdata->susp_lock, flags);
			err = usb_submit_urb(this_urb, GFP_ATOMIC);
			अगर (err) अणु
				dev_err(&port->dev,
					"%s: submit urb %d failed: %d\n",
					__func__, i, err);
				clear_bit(i, &portdata->out_busy);
				spin_lock_irqsave(&पूर्णांकfdata->susp_lock, flags);
				पूर्णांकfdata->in_flight--;
				spin_unlock_irqrestore(&पूर्णांकfdata->susp_lock,
						       flags);
				usb_स्वतःpm_put_पूर्णांकerface_async(port->serial->पूर्णांकerface);
				अवरोध;
			पूर्ण
		पूर्ण

		portdata->tx_start_समय[i] = jअगरfies;
		buf += toकरो;
		left -= toकरो;
	पूर्ण

	count -= left;
	dev_dbg(&port->dev, "%s: wrote (did %d)\n", __func__, count);
	वापस count;
पूर्ण
EXPORT_SYMBOL(usb_wwan_ग_लिखो);

अटल व्योम usb_wwan_indat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक err;
	पूर्णांक endpoपूर्णांक;
	काष्ठा usb_serial_port *port;
	काष्ठा device *dev;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	endpoपूर्णांक = usb_pipeendpoपूर्णांक(urb->pipe);
	port = urb->context;
	dev = &port->dev;

	अगर (status) अणु
		dev_dbg(dev, "%s: nonzero status: %d on endpoint %02x.\n",
			__func__, status, endpoपूर्णांक);

		/* करोn't resubmit on fatal errors */
		अगर (status == -ESHUTDOWN || status == -ENOENT)
			वापस;
	पूर्ण अन्यथा अणु
		अगर (urb->actual_length) अणु
			tty_insert_flip_string(&port->port, data,
					urb->actual_length);
			tty_flip_buffer_push(&port->port);
		पूर्ण अन्यथा
			dev_dbg(dev, "%s: empty read urb received\n", __func__);
	पूर्ण
	/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err) अणु
		अगर (err != -EPERM && err != -ENODEV) अणु
			dev_err(dev, "%s: resubmit read urb failed. (%d)\n",
				__func__, err);
			/* busy also in error unless we are समाप्तed */
			usb_mark_last_busy(port->serial->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		usb_mark_last_busy(port->serial->dev);
	पूर्ण
पूर्ण

अटल व्योम usb_wwan_outdat_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा usb_wwan_port_निजी *portdata;
	काष्ठा usb_wwan_पूर्णांकf_निजी *पूर्णांकfdata;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	port = urb->context;
	पूर्णांकfdata = usb_get_serial_data(port->serial);

	usb_serial_port_softपूर्णांक(port);
	usb_स्वतःpm_put_पूर्णांकerface_async(port->serial->पूर्णांकerface);
	portdata = usb_get_serial_port_data(port);
	spin_lock_irqsave(&पूर्णांकfdata->susp_lock, flags);
	पूर्णांकfdata->in_flight--;
	spin_unlock_irqrestore(&पूर्णांकfdata->susp_lock, flags);

	क्रम (i = 0; i < N_OUT_URB; ++i) अणु
		अगर (portdata->out_urbs[i] == urb) अणु
			smp_mb__beक्रमe_atomic();
			clear_bit(i, &portdata->out_busy);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक usb_wwan_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_wwan_port_निजी *portdata;
	पूर्णांक i;
	पूर्णांक data_len = 0;
	काष्ठा urb *this_urb;

	portdata = usb_get_serial_port_data(port);

	क्रम (i = 0; i < N_OUT_URB; i++) अणु
		this_urb = portdata->out_urbs[i];
		अगर (this_urb && !test_bit(i, &portdata->out_busy))
			data_len += OUT_BUFLEN;
	पूर्ण

	dev_dbg(&port->dev, "%s: %d\n", __func__, data_len);
	वापस data_len;
पूर्ण
EXPORT_SYMBOL(usb_wwan_ग_लिखो_room);

पूर्णांक usb_wwan_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_wwan_port_निजी *portdata;
	पूर्णांक i;
	पूर्णांक data_len = 0;
	काष्ठा urb *this_urb;

	portdata = usb_get_serial_port_data(port);

	क्रम (i = 0; i < N_OUT_URB; i++) अणु
		this_urb = portdata->out_urbs[i];
		/* FIXME: This locking is insufficient as this_urb may
		   go unused during the test */
		अगर (this_urb && test_bit(i, &portdata->out_busy))
			data_len += this_urb->transfer_buffer_length;
	पूर्ण
	dev_dbg(&port->dev, "%s: %d\n", __func__, data_len);
	वापस data_len;
पूर्ण
EXPORT_SYMBOL(usb_wwan_अक्षरs_in_buffer);

पूर्णांक usb_wwan_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_wwan_port_निजी *portdata;
	काष्ठा usb_wwan_पूर्णांकf_निजी *पूर्णांकfdata;
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक i, err;
	काष्ठा urb *urb;

	portdata = usb_get_serial_port_data(port);
	पूर्णांकfdata = usb_get_serial_data(serial);

	अगर (port->पूर्णांकerrupt_in_urb) अणु
		err = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
		अगर (err) अणु
			dev_err(&port->dev, "%s: submit int urb failed: %d\n",
				__func__, err);
		पूर्ण
	पूर्ण

	/* Start पढ़ोing from the IN endpoपूर्णांक */
	क्रम (i = 0; i < N_IN_URB; i++) अणु
		urb = portdata->in_urbs[i];
		अगर (!urb)
			जारी;
		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err) अणु
			dev_err(&port->dev,
				"%s: submit read urb %d failed: %d\n",
				__func__, i, err);
		पूर्ण
	पूर्ण

	spin_lock_irq(&पूर्णांकfdata->susp_lock);
	अगर (++पूर्णांकfdata->खोलो_ports == 1)
		serial->पूर्णांकerface->needs_remote_wakeup = 1;
	spin_unlock_irq(&पूर्णांकfdata->susp_lock);
	/* this balances a get in the generic USB serial code */
	usb_स्वतःpm_put_पूर्णांकerface(serial->पूर्णांकerface);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(usb_wwan_खोलो);

अटल व्योम unbusy_queued_urb(काष्ठा urb *urb,
					काष्ठा usb_wwan_port_निजी *portdata)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_OUT_URB; i++) अणु
		अगर (urb == portdata->out_urbs[i]) अणु
			clear_bit(i, &portdata->out_busy);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम usb_wwan_बंद(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक i;
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा usb_wwan_port_निजी *portdata;
	काष्ठा usb_wwan_पूर्णांकf_निजी *पूर्णांकfdata = usb_get_serial_data(serial);
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
		unbusy_queued_urb(urb, portdata);
		usb_स्वतःpm_put_पूर्णांकerface_async(serial->पूर्णांकerface);
	पूर्ण

	क्रम (i = 0; i < N_IN_URB; i++)
		usb_समाप्त_urb(portdata->in_urbs[i]);
	क्रम (i = 0; i < N_OUT_URB; i++)
		usb_समाप्त_urb(portdata->out_urbs[i]);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	usb_स्वतःpm_get_पूर्णांकerface_no_resume(serial->पूर्णांकerface);
पूर्ण
EXPORT_SYMBOL(usb_wwan_बंद);

अटल काष्ठा urb *usb_wwan_setup_urb(काष्ठा usb_serial_port *port,
				      पूर्णांक endpoपूर्णांक,
				      पूर्णांक dir, व्योम *ctx, अक्षर *buf, पूर्णांक len,
				      व्योम (*callback) (काष्ठा urb *))
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा usb_wwan_पूर्णांकf_निजी *पूर्णांकfdata = usb_get_serial_data(serial);
	काष्ठा urb *urb;

	urb = usb_alloc_urb(0, GFP_KERNEL);	/* No ISO */
	अगर (!urb)
		वापस शून्य;

	usb_fill_bulk_urb(urb, serial->dev,
			  usb_sndbulkpipe(serial->dev, endpoपूर्णांक) | dir,
			  buf, len, callback, ctx);

	अगर (पूर्णांकfdata->use_zlp && dir == USB_सूची_OUT)
		urb->transfer_flags |= URB_ZERO_PACKET;

	वापस urb;
पूर्ण

पूर्णांक usb_wwan_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_wwan_port_निजी *portdata;
	काष्ठा urb *urb;
	u8 *buffer;
	पूर्णांक i;

	अगर (!port->bulk_in_size || !port->bulk_out_size)
		वापस -ENODEV;

	portdata = kzalloc(माप(*portdata), GFP_KERNEL);
	अगर (!portdata)
		वापस -ENOMEM;

	init_usb_anchor(&portdata->delayed);

	क्रम (i = 0; i < N_IN_URB; i++) अणु
		buffer = (u8 *)__get_मुक्त_page(GFP_KERNEL);
		अगर (!buffer)
			जाओ bail_out_error;
		portdata->in_buffer[i] = buffer;

		urb = usb_wwan_setup_urb(port, port->bulk_in_endpoपूर्णांकAddress,
						USB_सूची_IN, port,
						buffer, IN_BUFLEN,
						usb_wwan_indat_callback);
		portdata->in_urbs[i] = urb;
	पूर्ण

	क्रम (i = 0; i < N_OUT_URB; i++) अणु
		buffer = kदो_स्मृति(OUT_BUFLEN, GFP_KERNEL);
		अगर (!buffer)
			जाओ bail_out_error2;
		portdata->out_buffer[i] = buffer;

		urb = usb_wwan_setup_urb(port, port->bulk_out_endpoपूर्णांकAddress,
						USB_सूची_OUT, port,
						buffer, OUT_BUFLEN,
						usb_wwan_outdat_callback);
		portdata->out_urbs[i] = urb;
	पूर्ण

	usb_set_serial_port_data(port, portdata);

	वापस 0;

bail_out_error2:
	क्रम (i = 0; i < N_OUT_URB; i++) अणु
		usb_मुक्त_urb(portdata->out_urbs[i]);
		kमुक्त(portdata->out_buffer[i]);
	पूर्ण
bail_out_error:
	क्रम (i = 0; i < N_IN_URB; i++) अणु
		usb_मुक्त_urb(portdata->in_urbs[i]);
		मुक्त_page((अचिन्हित दीर्घ)portdata->in_buffer[i]);
	पूर्ण
	kमुक्त(portdata);

	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(usb_wwan_port_probe);

व्योम usb_wwan_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक i;
	काष्ठा usb_wwan_port_निजी *portdata;

	portdata = usb_get_serial_port_data(port);
	usb_set_serial_port_data(port, शून्य);

	क्रम (i = 0; i < N_IN_URB; i++) अणु
		usb_मुक्त_urb(portdata->in_urbs[i]);
		मुक्त_page((अचिन्हित दीर्घ)portdata->in_buffer[i]);
	पूर्ण
	क्रम (i = 0; i < N_OUT_URB; i++) अणु
		usb_मुक्त_urb(portdata->out_urbs[i]);
		kमुक्त(portdata->out_buffer[i]);
	पूर्ण

	kमुक्त(portdata);
पूर्ण
EXPORT_SYMBOL(usb_wwan_port_हटाओ);

#अगर_घोषित CONFIG_PM
अटल व्योम stop_urbs(काष्ठा usb_serial *serial)
अणु
	पूर्णांक i, j;
	काष्ठा usb_serial_port *port;
	काष्ठा usb_wwan_port_निजी *portdata;

	क्रम (i = 0; i < serial->num_ports; ++i) अणु
		port = serial->port[i];
		portdata = usb_get_serial_port_data(port);
		अगर (!portdata)
			जारी;
		क्रम (j = 0; j < N_IN_URB; j++)
			usb_समाप्त_urb(portdata->in_urbs[j]);
		क्रम (j = 0; j < N_OUT_URB; j++)
			usb_समाप्त_urb(portdata->out_urbs[j]);
		usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
	पूर्ण
पूर्ण

पूर्णांक usb_wwan_suspend(काष्ठा usb_serial *serial, pm_message_t message)
अणु
	काष्ठा usb_wwan_पूर्णांकf_निजी *पूर्णांकfdata = usb_get_serial_data(serial);

	spin_lock_irq(&पूर्णांकfdata->susp_lock);
	अगर (PMSG_IS_AUTO(message)) अणु
		अगर (पूर्णांकfdata->in_flight) अणु
			spin_unlock_irq(&पूर्णांकfdata->susp_lock);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	पूर्णांकfdata->suspended = 1;
	spin_unlock_irq(&पूर्णांकfdata->susp_lock);

	stop_urbs(serial);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(usb_wwan_suspend);

/* Caller must hold susp_lock. */
अटल पूर्णांक usb_wwan_submit_delayed_urbs(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा usb_wwan_पूर्णांकf_निजी *data = usb_get_serial_data(serial);
	काष्ठा usb_wwan_port_निजी *portdata;
	काष्ठा urb *urb;
	पूर्णांक err_count = 0;
	पूर्णांक err;

	portdata = usb_get_serial_port_data(port);

	क्रम (;;) अणु
		urb = usb_get_from_anchor(&portdata->delayed);
		अगर (!urb)
			अवरोध;

		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (err) अणु
			dev_err(&port->dev, "%s: submit urb failed: %d\n",
					__func__, err);
			err_count++;
			unbusy_queued_urb(urb, portdata);
			usb_स्वतःpm_put_पूर्णांकerface_async(serial->पूर्णांकerface);
			जारी;
		पूर्ण
		data->in_flight++;
	पूर्ण

	अगर (err_count)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक usb_wwan_resume(काष्ठा usb_serial *serial)
अणु
	पूर्णांक i, j;
	काष्ठा usb_serial_port *port;
	काष्ठा usb_wwan_पूर्णांकf_निजी *पूर्णांकfdata = usb_get_serial_data(serial);
	काष्ठा usb_wwan_port_निजी *portdata;
	काष्ठा urb *urb;
	पूर्णांक err;
	पूर्णांक err_count = 0;

	spin_lock_irq(&पूर्णांकfdata->susp_lock);
	क्रम (i = 0; i < serial->num_ports; i++) अणु
		port = serial->port[i];

		अगर (!tty_port_initialized(&port->port))
			जारी;

		portdata = usb_get_serial_port_data(port);

		अगर (port->पूर्णांकerrupt_in_urb) अणु
			err = usb_submit_urb(port->पूर्णांकerrupt_in_urb,
					GFP_ATOMIC);
			अगर (err) अणु
				dev_err(&port->dev,
					"%s: submit int urb failed: %d\n",
					__func__, err);
				err_count++;
			पूर्ण
		पूर्ण

		err = usb_wwan_submit_delayed_urbs(port);
		अगर (err)
			err_count++;

		क्रम (j = 0; j < N_IN_URB; j++) अणु
			urb = portdata->in_urbs[j];
			err = usb_submit_urb(urb, GFP_ATOMIC);
			अगर (err < 0) अणु
				dev_err(&port->dev,
					"%s: submit read urb %d failed: %d\n",
					__func__, i, err);
				err_count++;
			पूर्ण
		पूर्ण
	पूर्ण
	पूर्णांकfdata->suspended = 0;
	spin_unlock_irq(&पूर्णांकfdata->susp_lock);

	अगर (err_count)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(usb_wwan_resume);
#पूर्ण_अगर

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
