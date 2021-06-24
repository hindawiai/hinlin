<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * cdc-acm.c
 *
 * Copyright (c) 1999 Armin Fuerst	<fuerst@in.tum.de>
 * Copyright (c) 1999 Pavel Machek	<pavel@ucw.cz>
 * Copyright (c) 1999 Johannes Erdfelt	<johannes@erdfelt.com>
 * Copyright (c) 2000 Vojtech Pavlik	<vojtech@suse.cz>
 * Copyright (c) 2004 Oliver Neukum	<oliver@neukum.name>
 * Copyright (c) 2005 David Kubicek	<dave@awk.cz>
 * Copyright (c) 2011 Johan Hovold	<jhovold@gmail.com>
 *
 * USB Abstract Control Model driver क्रम USB modems and ISDN adapters
 *
 * Sponsored by SuSE
 */

#अघोषित DEBUG
#अघोषित VERBOSE_DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/idr.h>
#समावेश <linux/list.h>

#समावेश "cdc-acm.h"


#घोषणा DRIVER_AUTHOR "Armin Fuerst, Pavel Machek, Johannes Erdfelt, Vojtech Pavlik, David Kubicek, Johan Hovold"
#घोषणा DRIVER_DESC "USB Abstract Control Model driver for USB modems and ISDN adapters"

अटल काष्ठा usb_driver acm_driver;
अटल काष्ठा tty_driver *acm_tty_driver;

अटल DEFINE_IDR(acm_minors);
अटल DEFINE_MUTEX(acm_minors_lock);

अटल व्योम acm_tty_set_termios(काष्ठा tty_काष्ठा *tty,
				काष्ठा ktermios *termios_old);

/*
 * acm_minors accessors
 */

/*
 * Look up an ACM काष्ठाure by minor. If found and not disconnected, increment
 * its refcount and वापस it with its mutex held.
 */
अटल काष्ठा acm *acm_get_by_minor(अचिन्हित पूर्णांक minor)
अणु
	काष्ठा acm *acm;

	mutex_lock(&acm_minors_lock);
	acm = idr_find(&acm_minors, minor);
	अगर (acm) अणु
		mutex_lock(&acm->mutex);
		अगर (acm->disconnected) अणु
			mutex_unlock(&acm->mutex);
			acm = शून्य;
		पूर्ण अन्यथा अणु
			tty_port_get(&acm->port);
			mutex_unlock(&acm->mutex);
		पूर्ण
	पूर्ण
	mutex_unlock(&acm_minors_lock);
	वापस acm;
पूर्ण

/*
 * Try to find an available minor number and अगर found, associate it with 'acm'.
 */
अटल पूर्णांक acm_alloc_minor(काष्ठा acm *acm)
अणु
	पूर्णांक minor;

	mutex_lock(&acm_minors_lock);
	minor = idr_alloc(&acm_minors, acm, 0, ACM_TTY_MINORS, GFP_KERNEL);
	mutex_unlock(&acm_minors_lock);

	वापस minor;
पूर्ण

/* Release the minor number associated with 'acm'.  */
अटल व्योम acm_release_minor(काष्ठा acm *acm)
अणु
	mutex_lock(&acm_minors_lock);
	idr_हटाओ(&acm_minors, acm->minor);
	mutex_unlock(&acm_minors_lock);
पूर्ण

/*
 * Functions क्रम ACM control messages.
 */

अटल पूर्णांक acm_ctrl_msg(काष्ठा acm *acm, पूर्णांक request, पूर्णांक value,
							व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक retval;

	retval = usb_स्वतःpm_get_पूर्णांकerface(acm->control);
	अगर (retval)
		वापस retval;

	retval = usb_control_msg(acm->dev, usb_sndctrlpipe(acm->dev, 0),
		request, USB_RT_ACM, value,
		acm->control->altsetting[0].desc.bInterfaceNumber,
		buf, len, 5000);

	dev_dbg(&acm->control->dev,
		"%s - rq 0x%02x, val %#x, len %#x, result %d\n",
		__func__, request, value, len, retval);

	usb_स्वतःpm_put_पूर्णांकerface(acm->control);

	वापस retval < 0 ? retval : 0;
पूर्ण

/* devices aren't required to support these requests.
 * the cdc acm descriptor tells whether they करो...
 */
अटल अंतरभूत पूर्णांक acm_set_control(काष्ठा acm *acm, पूर्णांक control)
अणु
	अगर (acm->quirks & QUIRK_CONTROL_LINE_STATE)
		वापस -EOPNOTSUPP;

	वापस acm_ctrl_msg(acm, USB_CDC_REQ_SET_CONTROL_LINE_STATE,
			control, शून्य, 0);
पूर्ण

#घोषणा acm_set_line(acm, line) \
	acm_ctrl_msg(acm, USB_CDC_REQ_SET_LINE_CODING, 0, line, माप *(line))
#घोषणा acm_send_अवरोध(acm, ms) \
	acm_ctrl_msg(acm, USB_CDC_REQ_SEND_BREAK, ms, शून्य, 0)

अटल व्योम acm_poison_urbs(काष्ठा acm *acm)
अणु
	पूर्णांक i;

	usb_poison_urb(acm->ctrlurb);
	क्रम (i = 0; i < ACM_NW; i++)
		usb_poison_urb(acm->wb[i].urb);
	क्रम (i = 0; i < acm->rx_buflimit; i++)
		usb_poison_urb(acm->पढ़ो_urbs[i]);
पूर्ण

अटल व्योम acm_unpoison_urbs(काष्ठा acm *acm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < acm->rx_buflimit; i++)
		usb_unpoison_urb(acm->पढ़ो_urbs[i]);
	क्रम (i = 0; i < ACM_NW; i++)
		usb_unpoison_urb(acm->wb[i].urb);
	usb_unpoison_urb(acm->ctrlurb);
पूर्ण


/*
 * Write buffer management.
 * All of these assume proper locks taken by the caller.
 */

अटल पूर्णांक acm_wb_alloc(काष्ठा acm *acm)
अणु
	पूर्णांक i, wbn;
	काष्ठा acm_wb *wb;

	wbn = 0;
	i = 0;
	क्रम (;;) अणु
		wb = &acm->wb[wbn];
		अगर (!wb->use) अणु
			wb->use = true;
			wb->len = 0;
			वापस wbn;
		पूर्ण
		wbn = (wbn + 1) % ACM_NW;
		अगर (++i >= ACM_NW)
			वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक acm_wb_is_avail(काष्ठा acm *acm)
अणु
	पूर्णांक i, n;
	अचिन्हित दीर्घ flags;

	n = ACM_NW;
	spin_lock_irqsave(&acm->ग_लिखो_lock, flags);
	क्रम (i = 0; i < ACM_NW; i++)
		अगर(acm->wb[i].use)
			n--;
	spin_unlock_irqrestore(&acm->ग_लिखो_lock, flags);
	वापस n;
पूर्ण

/*
 * Finish ग_लिखो. Caller must hold acm->ग_लिखो_lock
 */
अटल व्योम acm_ग_लिखो_करोne(काष्ठा acm *acm, काष्ठा acm_wb *wb)
अणु
	wb->use = false;
	acm->transmitting--;
	usb_स्वतःpm_put_पूर्णांकerface_async(acm->control);
पूर्ण

/*
 * Poke ग_लिखो.
 *
 * the caller is responsible क्रम locking
 */

अटल पूर्णांक acm_start_wb(काष्ठा acm *acm, काष्ठा acm_wb *wb)
अणु
	पूर्णांक rc;

	acm->transmitting++;

	wb->urb->transfer_buffer = wb->buf;
	wb->urb->transfer_dma = wb->dmah;
	wb->urb->transfer_buffer_length = wb->len;
	wb->urb->dev = acm->dev;

	rc = usb_submit_urb(wb->urb, GFP_ATOMIC);
	अगर (rc < 0) अणु
		अगर (rc != -EPERM)
			dev_err(&acm->data->dev,
				"%s - usb_submit_urb(write bulk) failed: %d\n",
				__func__, rc);
		acm_ग_लिखो_करोne(acm, wb);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * attributes exported through sysfs
 */
अटल sमाप_प्रकार bmCapabilities_show
(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा acm *acm = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस प्र_लिखो(buf, "%d", acm->ctrl_caps);
पूर्ण
अटल DEVICE_ATTR_RO(bmCapabilities);

अटल sमाप_प्रकार wCountryCodes_show
(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा acm *acm = usb_get_पूर्णांकfdata(पूर्णांकf);

	स_नकल(buf, acm->country_codes, acm->country_code_size);
	वापस acm->country_code_size;
पूर्ण

अटल DEVICE_ATTR_RO(wCountryCodes);

अटल sमाप_प्रकार iCountryCodeRelDate_show
(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा acm *acm = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस प्र_लिखो(buf, "%d", acm->country_rel_date);
पूर्ण

अटल DEVICE_ATTR_RO(iCountryCodeRelDate);
/*
 * Interrupt handlers क्रम various ACM device responses
 */

अटल व्योम acm_process_notअगरication(काष्ठा acm *acm, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक newctrl;
	पूर्णांक dअगरference;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_cdc_notअगरication *dr = (काष्ठा usb_cdc_notअगरication *)buf;
	अचिन्हित अक्षर *data = buf + माप(काष्ठा usb_cdc_notअगरication);

	चयन (dr->bNotअगरicationType) अणु
	हाल USB_CDC_NOTIFY_NETWORK_CONNECTION:
		dev_dbg(&acm->control->dev,
			"%s - network connection: %d\n", __func__, dr->wValue);
		अवरोध;

	हाल USB_CDC_NOTIFY_SERIAL_STATE:
		अगर (le16_to_cpu(dr->wLength) != 2) अणु
			dev_dbg(&acm->control->dev,
				"%s - malformed serial state\n", __func__);
			अवरोध;
		पूर्ण

		newctrl = get_unaligned_le16(data);
		dev_dbg(&acm->control->dev,
			"%s - serial state: 0x%x\n", __func__, newctrl);

		अगर (!acm->clocal && (acm->ctrlin & ~newctrl & ACM_CTRL_DCD)) अणु
			dev_dbg(&acm->control->dev,
				"%s - calling hangup\n", __func__);
			tty_port_tty_hangup(&acm->port, false);
		पूर्ण

		dअगरference = acm->ctrlin ^ newctrl;
		spin_lock_irqsave(&acm->पढ़ो_lock, flags);
		acm->ctrlin = newctrl;
		acm->oldcount = acm->iocount;

		अगर (dअगरference & ACM_CTRL_DSR)
			acm->iocount.dsr++;
		अगर (dअगरference & ACM_CTRL_DCD)
			acm->iocount.dcd++;
		अगर (newctrl & ACM_CTRL_BRK) अणु
			acm->iocount.brk++;
			tty_insert_flip_अक्षर(&acm->port, 0, TTY_BREAK);
		पूर्ण
		अगर (newctrl & ACM_CTRL_RI)
			acm->iocount.rng++;
		अगर (newctrl & ACM_CTRL_FRAMING)
			acm->iocount.frame++;
		अगर (newctrl & ACM_CTRL_PARITY)
			acm->iocount.parity++;
		अगर (newctrl & ACM_CTRL_OVERRUN)
			acm->iocount.overrun++;
		spin_unlock_irqrestore(&acm->पढ़ो_lock, flags);

		अगर (dअगरference)
			wake_up_all(&acm->wioctl);

		अवरोध;

	शेष:
		dev_dbg(&acm->control->dev,
			"%s - unknown notification %d received: index %d len %d\n",
			__func__,
			dr->bNotअगरicationType, dr->wIndex, dr->wLength);
	पूर्ण
पूर्ण

/* control पूर्णांकerface reports status changes with "interrupt" transfers */
अटल व्योम acm_ctrl_irq(काष्ठा urb *urb)
अणु
	काष्ठा acm *acm = urb->context;
	काष्ठा usb_cdc_notअगरication *dr = urb->transfer_buffer;
	अचिन्हित पूर्णांक current_size = urb->actual_length;
	अचिन्हित पूर्णांक expected_size, copy_size, alloc_size;
	पूर्णांक retval;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&acm->control->dev,
			"%s - urb shutting down with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(&acm->control->dev,
			"%s - nonzero urb status received: %d\n",
			__func__, status);
		जाओ निकास;
	पूर्ण

	usb_mark_last_busy(acm->dev);

	अगर (acm->nb_index)
		dr = (काष्ठा usb_cdc_notअगरication *)acm->notअगरication_buffer;

	/* size = notअगरication-header + (optional) data */
	expected_size = माप(काष्ठा usb_cdc_notअगरication) +
					le16_to_cpu(dr->wLength);

	अगर (current_size < expected_size) अणु
		/* notअगरication is transmitted fragmented, reassemble */
		अगर (acm->nb_size < expected_size) अणु
			u8 *new_buffer;
			alloc_size = roundup_घात_of_two(expected_size);
			/* Final मुक्तing is करोne on disconnect. */
			new_buffer = kपुनः_स्मृति(acm->notअगरication_buffer,
					      alloc_size, GFP_ATOMIC);
			अगर (!new_buffer) अणु
				acm->nb_index = 0;
				जाओ निकास;
			पूर्ण

			acm->notअगरication_buffer = new_buffer;
			acm->nb_size = alloc_size;
			dr = (काष्ठा usb_cdc_notअगरication *)acm->notअगरication_buffer;
		पूर्ण

		copy_size = min(current_size,
				expected_size - acm->nb_index);

		स_नकल(&acm->notअगरication_buffer[acm->nb_index],
		       urb->transfer_buffer, copy_size);
		acm->nb_index += copy_size;
		current_size = acm->nb_index;
	पूर्ण

	अगर (current_size >= expected_size) अणु
		/* notअगरication complete */
		acm_process_notअगरication(acm, (अचिन्हित अक्षर *)dr);
		acm->nb_index = 0;
	पूर्ण

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval && retval != -EPERM && retval != -ENODEV)
		dev_err(&acm->control->dev,
			"%s - usb_submit_urb failed: %d\n", __func__, retval);
	अन्यथा
		dev_vdbg(&acm->control->dev,
			"control resubmission terminated %d\n", retval);
पूर्ण

अटल पूर्णांक acm_submit_पढ़ो_urb(काष्ठा acm *acm, पूर्णांक index, gfp_t mem_flags)
अणु
	पूर्णांक res;

	अगर (!test_and_clear_bit(index, &acm->पढ़ो_urbs_मुक्त))
		वापस 0;

	res = usb_submit_urb(acm->पढ़ो_urbs[index], mem_flags);
	अगर (res) अणु
		अगर (res != -EPERM && res != -ENODEV) अणु
			dev_err(&acm->data->dev,
				"urb %d failed submission with %d\n",
				index, res);
		पूर्ण अन्यथा अणु
			dev_vdbg(&acm->data->dev, "intended failure %d\n", res);
		पूर्ण
		set_bit(index, &acm->पढ़ो_urbs_मुक्त);
		वापस res;
	पूर्ण अन्यथा अणु
		dev_vdbg(&acm->data->dev, "submitted urb %d\n", index);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acm_submit_पढ़ो_urbs(काष्ठा acm *acm, gfp_t mem_flags)
अणु
	पूर्णांक res;
	पूर्णांक i;

	क्रम (i = 0; i < acm->rx_buflimit; ++i) अणु
		res = acm_submit_पढ़ो_urb(acm, i, mem_flags);
		अगर (res)
			वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम acm_process_पढ़ो_urb(काष्ठा acm *acm, काष्ठा urb *urb)
अणु
	अगर (!urb->actual_length)
		वापस;

	tty_insert_flip_string(&acm->port, urb->transfer_buffer,
			urb->actual_length);
	tty_flip_buffer_push(&acm->port);
पूर्ण

अटल व्योम acm_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा acm_rb *rb = urb->context;
	काष्ठा acm *acm = rb->instance;
	पूर्णांक status = urb->status;
	bool stopped = false;
	bool stalled = false;
	bool coolकरोwn = false;

	dev_vdbg(&acm->data->dev, "got urb %d, len %d, status %d\n",
		rb->index, urb->actual_length, status);

	चयन (status) अणु
	हाल 0:
		usb_mark_last_busy(acm->dev);
		acm_process_पढ़ो_urb(acm, urb);
		अवरोध;
	हाल -EPIPE:
		set_bit(EVENT_RX_STALL, &acm->flags);
		stalled = true;
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		dev_dbg(&acm->data->dev,
			"%s - urb shutting down with status: %d\n",
			__func__, status);
		stopped = true;
		अवरोध;
	हाल -EOVERFLOW:
	हाल -EPROTO:
		dev_dbg(&acm->data->dev,
			"%s - cooling babbling device\n", __func__);
		usb_mark_last_busy(acm->dev);
		set_bit(rb->index, &acm->urbs_in_error_delay);
		set_bit(ACM_ERROR_DELAY, &acm->flags);
		coolकरोwn = true;
		अवरोध;
	शेष:
		dev_dbg(&acm->data->dev,
			"%s - nonzero urb status received: %d\n",
			__func__, status);
		अवरोध;
	पूर्ण

	/*
	 * Make sure URB processing is करोne beक्रमe marking as मुक्त to aव्योम
	 * racing with unthrottle() on another CPU. Matches the barriers
	 * implied by the test_and_clear_bit() in acm_submit_पढ़ो_urb().
	 */
	smp_mb__beक्रमe_atomic();
	set_bit(rb->index, &acm->पढ़ो_urbs_मुक्त);
	/*
	 * Make sure URB is marked as मुक्त beक्रमe checking the throttled flag
	 * to aव्योम racing with unthrottle() on another CPU. Matches the
	 * smp_mb() in unthrottle().
	 */
	smp_mb__after_atomic();

	अगर (stopped || stalled || coolकरोwn) अणु
		अगर (stalled)
			schedule_delayed_work(&acm->dwork, 0);
		अन्यथा अगर (coolकरोwn)
			schedule_delayed_work(&acm->dwork, HZ / 2);
		वापस;
	पूर्ण

	अगर (test_bit(ACM_THROTTLED, &acm->flags))
		वापस;

	acm_submit_पढ़ो_urb(acm, rb->index, GFP_ATOMIC);
पूर्ण

/* data पूर्णांकerface wrote those outgoing bytes */
अटल व्योम acm_ग_लिखो_bulk(काष्ठा urb *urb)
अणु
	काष्ठा acm_wb *wb = urb->context;
	काष्ठा acm *acm = wb->instance;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = urb->status;

	अगर (status || (urb->actual_length != urb->transfer_buffer_length))
		dev_vdbg(&acm->data->dev, "wrote len %d/%d, status %d\n",
			urb->actual_length,
			urb->transfer_buffer_length,
			status);

	spin_lock_irqsave(&acm->ग_लिखो_lock, flags);
	acm_ग_लिखो_करोne(acm, wb);
	spin_unlock_irqrestore(&acm->ग_लिखो_lock, flags);
	set_bit(EVENT_TTY_WAKEUP, &acm->flags);
	schedule_delayed_work(&acm->dwork, 0);
पूर्ण

अटल व्योम acm_softपूर्णांक(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i;
	काष्ठा acm *acm = container_of(work, काष्ठा acm, dwork.work);

	अगर (test_bit(EVENT_RX_STALL, &acm->flags)) अणु
		smp_mb(); /* against acm_suspend() */
		अगर (!acm->susp_count) अणु
			क्रम (i = 0; i < acm->rx_buflimit; i++)
				usb_समाप्त_urb(acm->पढ़ो_urbs[i]);
			usb_clear_halt(acm->dev, acm->in);
			acm_submit_पढ़ो_urbs(acm, GFP_KERNEL);
			clear_bit(EVENT_RX_STALL, &acm->flags);
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(ACM_ERROR_DELAY, &acm->flags)) अणु
		क्रम (i = 0; i < acm->rx_buflimit; i++)
			अगर (test_and_clear_bit(i, &acm->urbs_in_error_delay))
				acm_submit_पढ़ो_urb(acm, i, GFP_KERNEL);
	पूर्ण

	अगर (test_and_clear_bit(EVENT_TTY_WAKEUP, &acm->flags))
		tty_port_tty_wakeup(&acm->port);
पूर्ण

/*
 * TTY handlers
 */

अटल पूर्णांक acm_tty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा acm *acm;
	पूर्णांक retval;

	acm = acm_get_by_minor(tty->index);
	अगर (!acm)
		वापस -ENODEV;

	retval = tty_standard_install(driver, tty);
	अगर (retval)
		जाओ error_init_termios;

	/*
	 * Suppress initial echoing क्रम some devices which might send data
	 * immediately after acm driver has been installed.
	 */
	अगर (acm->quirks & DISABLE_ECHO)
		tty->termios.c_lflag &= ~ECHO;

	tty->driver_data = acm;

	वापस 0;

error_init_termios:
	tty_port_put(&acm->port);
	वापस retval;
पूर्ण

अटल पूर्णांक acm_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा acm *acm = tty->driver_data;

	वापस tty_port_खोलो(&acm->port, tty, filp);
पूर्ण

अटल व्योम acm_port_dtr_rts(काष्ठा tty_port *port, पूर्णांक उठाओ)
अणु
	काष्ठा acm *acm = container_of(port, काष्ठा acm, port);
	पूर्णांक val;
	पूर्णांक res;

	अगर (उठाओ)
		val = ACM_CTRL_DTR | ACM_CTRL_RTS;
	अन्यथा
		val = 0;

	/* FIXME: add missing ctrlout locking throughout driver */
	acm->ctrlout = val;

	res = acm_set_control(acm, val);
	अगर (res && (acm->ctrl_caps & USB_CDC_CAP_LINE))
		/* This is broken in too many devices to spam the logs */
		dev_dbg(&acm->control->dev, "failed to set dtr/rts\n");
पूर्ण

अटल पूर्णांक acm_port_activate(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा acm *acm = container_of(port, काष्ठा acm, port);
	पूर्णांक retval = -ENODEV;
	पूर्णांक i;

	mutex_lock(&acm->mutex);
	अगर (acm->disconnected)
		जाओ disconnected;

	retval = usb_स्वतःpm_get_पूर्णांकerface(acm->control);
	अगर (retval)
		जाओ error_get_पूर्णांकerface;

	/*
	 * FIXME: Why करो we need this? Allocating 64K of physically contiguous
	 * memory is really nasty...
	 */
	set_bit(TTY_NO_WRITE_SPLIT, &tty->flags);
	acm->control->needs_remote_wakeup = 1;

	acm->ctrlurb->dev = acm->dev;
	retval = usb_submit_urb(acm->ctrlurb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&acm->control->dev,
			"%s - usb_submit_urb(ctrl irq) failed\n", __func__);
		जाओ error_submit_urb;
	पूर्ण

	acm_tty_set_termios(tty, शून्य);

	/*
	 * Unthrottle device in हाल the TTY was बंदd जबतक throttled.
	 */
	clear_bit(ACM_THROTTLED, &acm->flags);

	retval = acm_submit_पढ़ो_urbs(acm, GFP_KERNEL);
	अगर (retval)
		जाओ error_submit_पढ़ो_urbs;

	usb_स्वतःpm_put_पूर्णांकerface(acm->control);

	mutex_unlock(&acm->mutex);

	वापस 0;

error_submit_पढ़ो_urbs:
	क्रम (i = 0; i < acm->rx_buflimit; i++)
		usb_समाप्त_urb(acm->पढ़ो_urbs[i]);
	usb_समाप्त_urb(acm->ctrlurb);
error_submit_urb:
	usb_स्वतःpm_put_पूर्णांकerface(acm->control);
error_get_पूर्णांकerface:
disconnected:
	mutex_unlock(&acm->mutex);

	वापस usb_translate_errors(retval);
पूर्ण

अटल व्योम acm_port_deकाष्ठा(काष्ठा tty_port *port)
अणु
	काष्ठा acm *acm = container_of(port, काष्ठा acm, port);

	acm_release_minor(acm);
	usb_put_पूर्णांकf(acm->control);
	kमुक्त(acm->country_codes);
	kमुक्त(acm);
पूर्ण

अटल व्योम acm_port_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा acm *acm = container_of(port, काष्ठा acm, port);
	काष्ठा urb *urb;
	काष्ठा acm_wb *wb;

	/*
	 * Need to grab ग_लिखो_lock to prevent race with resume, but no need to
	 * hold it due to the tty-port initialised flag.
	 */
	acm_poison_urbs(acm);
	spin_lock_irq(&acm->ग_लिखो_lock);
	spin_unlock_irq(&acm->ग_लिखो_lock);

	usb_स्वतःpm_get_पूर्णांकerface_no_resume(acm->control);
	acm->control->needs_remote_wakeup = 0;
	usb_स्वतःpm_put_पूर्णांकerface(acm->control);

	क्रम (;;) अणु
		urb = usb_get_from_anchor(&acm->delayed);
		अगर (!urb)
			अवरोध;
		wb = urb->context;
		wb->use = false;
		usb_स्वतःpm_put_पूर्णांकerface_async(acm->control);
	पूर्ण

	acm_unpoison_urbs(acm);

पूर्ण

अटल व्योम acm_tty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा acm *acm = tty->driver_data;

	tty_port_put(&acm->port);
पूर्ण

अटल व्योम acm_tty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा acm *acm = tty->driver_data;

	tty_port_hangup(&acm->port);
पूर्ण

अटल व्योम acm_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा acm *acm = tty->driver_data;

	tty_port_बंद(&acm->port, tty, filp);
पूर्ण

अटल पूर्णांक acm_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty,
					स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा acm *acm = tty->driver_data;
	पूर्णांक stat;
	अचिन्हित दीर्घ flags;
	पूर्णांक wbn;
	काष्ठा acm_wb *wb;

	अगर (!count)
		वापस 0;

	dev_vdbg(&acm->data->dev, "%d bytes from tty layer\n", count);

	spin_lock_irqsave(&acm->ग_लिखो_lock, flags);
	wbn = acm_wb_alloc(acm);
	अगर (wbn < 0) अणु
		spin_unlock_irqrestore(&acm->ग_लिखो_lock, flags);
		वापस 0;
	पूर्ण
	wb = &acm->wb[wbn];

	अगर (!acm->dev) अणु
		wb->use = false;
		spin_unlock_irqrestore(&acm->ग_लिखो_lock, flags);
		वापस -ENODEV;
	पूर्ण

	count = (count > acm->ग_लिखोsize) ? acm->ग_लिखोsize : count;
	dev_vdbg(&acm->data->dev, "writing %d bytes\n", count);
	स_नकल(wb->buf, buf, count);
	wb->len = count;

	stat = usb_स्वतःpm_get_पूर्णांकerface_async(acm->control);
	अगर (stat) अणु
		wb->use = false;
		spin_unlock_irqrestore(&acm->ग_लिखो_lock, flags);
		वापस stat;
	पूर्ण

	अगर (acm->susp_count) अणु
		usb_anchor_urb(wb->urb, &acm->delayed);
		spin_unlock_irqrestore(&acm->ग_लिखो_lock, flags);
		वापस count;
	पूर्ण

	stat = acm_start_wb(acm, wb);
	spin_unlock_irqrestore(&acm->ग_लिखो_lock, flags);

	अगर (stat < 0)
		वापस stat;
	वापस count;
पूर्ण

अटल पूर्णांक acm_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा acm *acm = tty->driver_data;
	/*
	 * Do not let the line discipline to know that we have a reserve,
	 * or it might get too enthusiastic.
	 */
	वापस acm_wb_is_avail(acm) ? acm->ग_लिखोsize : 0;
पूर्ण

अटल पूर्णांक acm_tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा acm *acm = tty->driver_data;
	/*
	 * अगर the device was unplugged then any reमुख्यing अक्षरacters fell out
	 * of the connector ;)
	 */
	अगर (acm->disconnected)
		वापस 0;
	/*
	 * This is inaccurate (overcounts), but it works.
	 */
	वापस (ACM_NW - acm_wb_is_avail(acm)) * acm->ग_लिखोsize;
पूर्ण

अटल व्योम acm_tty_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा acm *acm = tty->driver_data;

	set_bit(ACM_THROTTLED, &acm->flags);
पूर्ण

अटल व्योम acm_tty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा acm *acm = tty->driver_data;

	clear_bit(ACM_THROTTLED, &acm->flags);

	/* Matches the smp_mb__after_atomic() in acm_पढ़ो_bulk_callback(). */
	smp_mb();

	acm_submit_पढ़ो_urbs(acm, GFP_KERNEL);
पूर्ण

अटल पूर्णांक acm_tty_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक state)
अणु
	काष्ठा acm *acm = tty->driver_data;
	पूर्णांक retval;

	retval = acm_send_अवरोध(acm, state ? 0xffff : 0);
	अगर (retval < 0)
		dev_dbg(&acm->control->dev,
			"%s - send break failed\n", __func__);
	वापस retval;
पूर्ण

अटल पूर्णांक acm_tty_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा acm *acm = tty->driver_data;

	वापस (acm->ctrlout & ACM_CTRL_DTR ? TIOCM_DTR : 0) |
	       (acm->ctrlout & ACM_CTRL_RTS ? TIOCM_RTS : 0) |
	       (acm->ctrlin  & ACM_CTRL_DSR ? TIOCM_DSR : 0) |
	       (acm->ctrlin  & ACM_CTRL_RI  ? TIOCM_RI  : 0) |
	       (acm->ctrlin  & ACM_CTRL_DCD ? TIOCM_CD  : 0) |
	       TIOCM_CTS;
पूर्ण

अटल पूर्णांक acm_tty_tiocmset(काष्ठा tty_काष्ठा *tty,
			    अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा acm *acm = tty->driver_data;
	अचिन्हित पूर्णांक newctrl;

	newctrl = acm->ctrlout;
	set = (set & TIOCM_DTR ? ACM_CTRL_DTR : 0) |
					(set & TIOCM_RTS ? ACM_CTRL_RTS : 0);
	clear = (clear & TIOCM_DTR ? ACM_CTRL_DTR : 0) |
					(clear & TIOCM_RTS ? ACM_CTRL_RTS : 0);

	newctrl = (newctrl & ~clear) | set;

	अगर (acm->ctrlout == newctrl)
		वापस 0;
	वापस acm_set_control(acm, acm->ctrlout = newctrl);
पूर्ण

अटल पूर्णांक get_serial_info(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा acm *acm = tty->driver_data;

	ss->line = acm->minor;
	ss->बंद_delay	= jअगरfies_to_msecs(acm->port.बंद_delay) / 10;
	ss->closing_रुको = acm->port.closing_रुको == ASYNC_CLOSING_WAIT_NONE ?
				ASYNC_CLOSING_WAIT_NONE :
				jअगरfies_to_msecs(acm->port.closing_रुको) / 10;
	वापस 0;
पूर्ण

अटल पूर्णांक set_serial_info(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा acm *acm = tty->driver_data;
	अचिन्हित पूर्णांक closing_रुको, बंद_delay;
	पूर्णांक retval = 0;

	बंद_delay = msecs_to_jअगरfies(ss->बंद_delay * 10);
	closing_रुको = ss->closing_रुको == ASYNC_CLOSING_WAIT_NONE ?
			ASYNC_CLOSING_WAIT_NONE :
			msecs_to_jअगरfies(ss->closing_रुको * 10);

	mutex_lock(&acm->port.mutex);

	अगर (!capable(CAP_SYS_ADMIN)) अणु
		अगर ((बंद_delay != acm->port.बंद_delay) ||
		    (closing_रुको != acm->port.closing_रुको))
			retval = -EPERM;
	पूर्ण अन्यथा अणु
		acm->port.बंद_delay  = बंद_delay;
		acm->port.closing_रुको = closing_रुको;
	पूर्ण

	mutex_unlock(&acm->port.mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक रुको_serial_change(काष्ठा acm *acm, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rv = 0;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा async_icount old, new;

	करो अणु
		spin_lock_irq(&acm->पढ़ो_lock);
		old = acm->oldcount;
		new = acm->iocount;
		acm->oldcount = new;
		spin_unlock_irq(&acm->पढ़ो_lock);

		अगर ((arg & TIOCM_DSR) &&
			old.dsr != new.dsr)
			अवरोध;
		अगर ((arg & TIOCM_CD)  &&
			old.dcd != new.dcd)
			अवरोध;
		अगर ((arg & TIOCM_RI) &&
			old.rng != new.rng)
			अवरोध;

		add_रुको_queue(&acm->wioctl, &रुको);
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
		हटाओ_रुको_queue(&acm->wioctl, &रुको);
		अगर (acm->disconnected) अणु
			अगर (arg & TIOCM_CD)
				अवरोध;
			अन्यथा
				rv = -ENODEV;
		पूर्ण अन्यथा अणु
			अगर (संकेत_pending(current))
				rv = -ERESTARTSYS;
		पूर्ण
	पूर्ण जबतक (!rv);

	

	वापस rv;
पूर्ण

अटल पूर्णांक acm_tty_get_icount(काष्ठा tty_काष्ठा *tty,
					काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा acm *acm = tty->driver_data;

	icount->dsr = acm->iocount.dsr;
	icount->rng = acm->iocount.rng;
	icount->dcd = acm->iocount.dcd;
	icount->frame = acm->iocount.frame;
	icount->overrun = acm->iocount.overrun;
	icount->parity = acm->iocount.parity;
	icount->brk = acm->iocount.brk;

	वापस 0;
पूर्ण

अटल पूर्णांक acm_tty_ioctl(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा acm *acm = tty->driver_data;
	पूर्णांक rv = -ENOIOCTLCMD;

	चयन (cmd) अणु
	हाल TIOCMIWAIT:
		rv = usb_स्वतःpm_get_पूर्णांकerface(acm->control);
		अगर (rv < 0) अणु
			rv = -EIO;
			अवरोध;
		पूर्ण
		rv = रुको_serial_change(acm, arg);
		usb_स्वतःpm_put_पूर्णांकerface(acm->control);
		अवरोध;
	पूर्ण

	वापस rv;
पूर्ण

अटल व्योम acm_tty_set_termios(काष्ठा tty_काष्ठा *tty,
						काष्ठा ktermios *termios_old)
अणु
	काष्ठा acm *acm = tty->driver_data;
	काष्ठा ktermios *termios = &tty->termios;
	काष्ठा usb_cdc_line_coding newline;
	पूर्णांक newctrl = acm->ctrlout;

	newline.dwDTERate = cpu_to_le32(tty_get_baud_rate(tty));
	newline.bCharFormat = termios->c_cflag & CSTOPB ? 2 : 0;
	newline.bParityType = termios->c_cflag & PARENB ?
				(termios->c_cflag & PARODD ? 1 : 2) +
				(termios->c_cflag & CMSPAR ? 2 : 0) : 0;
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		newline.bDataBits = 5;
		अवरोध;
	हाल CS6:
		newline.bDataBits = 6;
		अवरोध;
	हाल CS7:
		newline.bDataBits = 7;
		अवरोध;
	हाल CS8:
	शेष:
		newline.bDataBits = 8;
		अवरोध;
	पूर्ण
	/* FIXME: Needs to clear unsupported bits in the termios */
	acm->clocal = ((termios->c_cflag & CLOCAL) != 0);

	अगर (C_BAUD(tty) == B0) अणु
		newline.dwDTERate = acm->line.dwDTERate;
		newctrl &= ~ACM_CTRL_DTR;
	पूर्ण अन्यथा अगर (termios_old && (termios_old->c_cflag & CBAUD) == B0) अणु
		newctrl |=  ACM_CTRL_DTR;
	पूर्ण

	अगर (newctrl != acm->ctrlout)
		acm_set_control(acm, acm->ctrlout = newctrl);

	अगर (स_भेद(&acm->line, &newline, माप newline)) अणु
		स_नकल(&acm->line, &newline, माप newline);
		dev_dbg(&acm->control->dev, "%s - set line: %d %d %d %d\n",
			__func__,
			le32_to_cpu(newline.dwDTERate),
			newline.bCharFormat, newline.bParityType,
			newline.bDataBits);
		acm_set_line(acm, &acm->line);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tty_port_operations acm_port_ops = अणु
	.dtr_rts = acm_port_dtr_rts,
	.shutकरोwn = acm_port_shutकरोwn,
	.activate = acm_port_activate,
	.deकाष्ठा = acm_port_deकाष्ठा,
पूर्ण;

/*
 * USB probe and disconnect routines.
 */

/* Little helpers: ग_लिखो/पढ़ो buffers मुक्त */
अटल व्योम acm_ग_लिखो_buffers_मुक्त(काष्ठा acm *acm)
अणु
	पूर्णांक i;
	काष्ठा acm_wb *wb;

	क्रम (wb = &acm->wb[0], i = 0; i < ACM_NW; i++, wb++)
		usb_मुक्त_coherent(acm->dev, acm->ग_लिखोsize, wb->buf, wb->dmah);
पूर्ण

अटल व्योम acm_पढ़ो_buffers_मुक्त(काष्ठा acm *acm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < acm->rx_buflimit; i++)
		usb_मुक्त_coherent(acm->dev, acm->पढ़ोsize,
			  acm->पढ़ो_buffers[i].base, acm->पढ़ो_buffers[i].dma);
पूर्ण

/* Little helper: ग_लिखो buffers allocate */
अटल पूर्णांक acm_ग_लिखो_buffers_alloc(काष्ठा acm *acm)
अणु
	पूर्णांक i;
	काष्ठा acm_wb *wb;

	क्रम (wb = &acm->wb[0], i = 0; i < ACM_NW; i++, wb++) अणु
		wb->buf = usb_alloc_coherent(acm->dev, acm->ग_लिखोsize, GFP_KERNEL,
		    &wb->dmah);
		अगर (!wb->buf) अणु
			जबतक (i != 0) अणु
				--i;
				--wb;
				usb_मुक्त_coherent(acm->dev, acm->ग_लिखोsize,
				    wb->buf, wb->dmah);
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acm_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_cdc_जोड़_desc *जोड़_header = शून्य;
	काष्ठा usb_cdc_call_mgmt_descriptor *cmgmd = शून्य;
	अचिन्हित अक्षर *buffer = पूर्णांकf->altsetting->extra;
	पूर्णांक buflen = पूर्णांकf->altsetting->extralen;
	काष्ठा usb_पूर्णांकerface *control_पूर्णांकerface;
	काष्ठा usb_पूर्णांकerface *data_पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *epctrl = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *epपढ़ो = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *epग_लिखो = शून्य;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_cdc_parsed_header h;
	काष्ठा acm *acm;
	पूर्णांक minor;
	पूर्णांक ctrlsize, पढ़ोsize;
	u8 *buf;
	पूर्णांक call_पूर्णांकf_num = -1;
	पूर्णांक data_पूर्णांकf_num = -1;
	अचिन्हित दीर्घ quirks;
	पूर्णांक num_rx_buf;
	पूर्णांक i;
	पूर्णांक combined_पूर्णांकerfaces = 0;
	काष्ठा device *tty_dev;
	पूर्णांक rv = -ENOMEM;
	पूर्णांक res;

	/* normal quirks */
	quirks = (अचिन्हित दीर्घ)id->driver_info;

	अगर (quirks == IGNORE_DEVICE)
		वापस -ENODEV;

	स_रखो(&h, 0x00, माप(काष्ठा usb_cdc_parsed_header));

	num_rx_buf = (quirks == SINGLE_RX_URB) ? 1 : ACM_NR;

	/* handle quirks deadly to normal probing*/
	अगर (quirks == NO_UNION_NORMAL) अणु
		data_पूर्णांकerface = usb_अगरnum_to_अगर(usb_dev, 1);
		control_पूर्णांकerface = usb_अगरnum_to_अगर(usb_dev, 0);
		/* we would crash */
		अगर (!data_पूर्णांकerface || !control_पूर्णांकerface)
			वापस -ENODEV;
		जाओ skip_normal_probe;
	पूर्ण

	/* normal probing*/
	अगर (!buffer) अणु
		dev_err(&पूर्णांकf->dev, "Weird descriptor references\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!buflen) अणु
		अगर (पूर्णांकf->cur_altsetting->endpoपूर्णांक &&
				पूर्णांकf->cur_altsetting->endpoपूर्णांक->extralen &&
				पूर्णांकf->cur_altsetting->endpoपूर्णांक->extra) अणु
			dev_dbg(&पूर्णांकf->dev,
				"Seeking extra descriptors on endpoint\n");
			buflen = पूर्णांकf->cur_altsetting->endpoपूर्णांक->extralen;
			buffer = पूर्णांकf->cur_altsetting->endpoपूर्णांक->extra;
		पूर्ण अन्यथा अणु
			dev_err(&पूर्णांकf->dev,
				"Zero length descriptor references\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	cdc_parse_cdc_header(&h, पूर्णांकf, buffer, buflen);
	जोड़_header = h.usb_cdc_जोड़_desc;
	cmgmd = h.usb_cdc_call_mgmt_descriptor;
	अगर (cmgmd)
		call_पूर्णांकf_num = cmgmd->bDataInterface;

	अगर (!जोड़_header) अणु
		अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs == 3) अणु
			dev_dbg(&पूर्णांकf->dev, "No union descriptor, assuming single interface\n");
			combined_पूर्णांकerfaces = 1;
			control_पूर्णांकerface = data_पूर्णांकerface = पूर्णांकf;
			जाओ look_क्रम_collapsed_पूर्णांकerface;
		पूर्ण अन्यथा अगर (call_पूर्णांकf_num > 0) अणु
			dev_dbg(&पूर्णांकf->dev, "No union descriptor, using call management descriptor\n");
			data_पूर्णांकf_num = call_पूर्णांकf_num;
			data_पूर्णांकerface = usb_अगरnum_to_अगर(usb_dev, data_पूर्णांकf_num);
			control_पूर्णांकerface = पूर्णांकf;
		पूर्ण अन्यथा अणु
			dev_dbg(&पूर्णांकf->dev, "No union descriptor, giving up\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक class = -1;

		data_पूर्णांकf_num = जोड़_header->bSlaveInterface0;
		control_पूर्णांकerface = usb_अगरnum_to_अगर(usb_dev, जोड़_header->bMasterInterface0);
		data_पूर्णांकerface = usb_अगरnum_to_अगर(usb_dev, data_पूर्णांकf_num);

		अगर (control_पूर्णांकerface)
			class = control_पूर्णांकerface->cur_altsetting->desc.bInterfaceClass;

		अगर (class != USB_CLASS_COMM && class != USB_CLASS_CDC_DATA) अणु
			dev_dbg(&पूर्णांकf->dev, "Broken union descriptor, assuming single interface\n");
			combined_पूर्णांकerfaces = 1;
			control_पूर्णांकerface = data_पूर्णांकerface = पूर्णांकf;
			जाओ look_क्रम_collapsed_पूर्णांकerface;
		पूर्ण
	पूर्ण

	अगर (!control_पूर्णांकerface || !data_पूर्णांकerface) अणु
		dev_dbg(&पूर्णांकf->dev, "no interfaces\n");
		वापस -ENODEV;
	पूर्ण

	अगर (data_पूर्णांकf_num != call_पूर्णांकf_num)
		dev_dbg(&पूर्णांकf->dev, "Separate call control interface. That is not fully supported.\n");

	अगर (control_पूर्णांकerface == data_पूर्णांकerface) अणु
		/* some broken devices deचिन्हित क्रम winकरोws work this way */
		dev_warn(&पूर्णांकf->dev,"Control and data interfaces are not separated!\n");
		combined_पूर्णांकerfaces = 1;
		/* a popular other OS करोesn't use it */
		quirks |= NO_CAP_LINE;
		अगर (data_पूर्णांकerface->cur_altsetting->desc.bNumEndpoपूर्णांकs != 3) अणु
			dev_err(&पूर्णांकf->dev, "This needs exactly 3 endpoints\n");
			वापस -EINVAL;
		पूर्ण
look_क्रम_collapsed_पूर्णांकerface:
		res = usb_find_common_endpoपूर्णांकs(data_पूर्णांकerface->cur_altsetting,
				&epपढ़ो, &epग_लिखो, &epctrl, शून्य);
		अगर (res)
			वापस res;

		जाओ made_compressed_probe;
	पूर्ण

skip_normal_probe:

	/*workaround क्रम चयनed पूर्णांकerfaces */
	अगर (data_पूर्णांकerface->cur_altsetting->desc.bInterfaceClass != USB_CLASS_CDC_DATA) अणु
		अगर (control_पूर्णांकerface->cur_altsetting->desc.bInterfaceClass == USB_CLASS_CDC_DATA) अणु
			dev_dbg(&पूर्णांकf->dev,
				"Your device has switched interfaces.\n");
			swap(control_पूर्णांकerface, data_पूर्णांकerface);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Accept probe requests only क्रम the control पूर्णांकerface */
	अगर (!combined_पूर्णांकerfaces && पूर्णांकf != control_पूर्णांकerface)
		वापस -ENODEV;

	अगर (data_पूर्णांकerface->cur_altsetting->desc.bNumEndpoपूर्णांकs < 2 ||
	    control_पूर्णांकerface->cur_altsetting->desc.bNumEndpoपूर्णांकs == 0)
		वापस -EINVAL;

	epctrl = &control_पूर्णांकerface->cur_altsetting->endpoपूर्णांक[0].desc;
	epपढ़ो = &data_पूर्णांकerface->cur_altsetting->endpoपूर्णांक[0].desc;
	epग_लिखो = &data_पूर्णांकerface->cur_altsetting->endpoपूर्णांक[1].desc;


	/* workaround क्रम चयनed endpoपूर्णांकs */
	अगर (!usb_endpoपूर्णांक_dir_in(epपढ़ो)) अणु
		/* descriptors are swapped */
		dev_dbg(&पूर्णांकf->dev,
			"The data interface has switched endpoints\n");
		swap(epपढ़ो, epग_लिखो);
	पूर्ण
made_compressed_probe:
	dev_dbg(&पूर्णांकf->dev, "interfaces are valid\n");

	acm = kzalloc(माप(काष्ठा acm), GFP_KERNEL);
	अगर (!acm)
		वापस -ENOMEM;

	tty_port_init(&acm->port);
	acm->port.ops = &acm_port_ops;

	ctrlsize = usb_endpoपूर्णांक_maxp(epctrl);
	पढ़ोsize = usb_endpoपूर्णांक_maxp(epपढ़ो) *
				(quirks == SINGLE_RX_URB ? 1 : 2);
	acm->combined_पूर्णांकerfaces = combined_पूर्णांकerfaces;
	acm->ग_लिखोsize = usb_endpoपूर्णांक_maxp(epग_लिखो) * 20;
	acm->control = control_पूर्णांकerface;
	acm->data = data_पूर्णांकerface;

	usb_get_पूर्णांकf(acm->control); /* unकरोne in deकाष्ठा() */

	minor = acm_alloc_minor(acm);
	अगर (minor < 0)
		जाओ err_put_port;

	acm->minor = minor;
	acm->dev = usb_dev;
	अगर (h.usb_cdc_acm_descriptor)
		acm->ctrl_caps = h.usb_cdc_acm_descriptor->bmCapabilities;
	अगर (quirks & NO_CAP_LINE)
		acm->ctrl_caps &= ~USB_CDC_CAP_LINE;
	acm->ctrlsize = ctrlsize;
	acm->पढ़ोsize = पढ़ोsize;
	acm->rx_buflimit = num_rx_buf;
	INIT_DELAYED_WORK(&acm->dwork, acm_softपूर्णांक);
	init_रुकोqueue_head(&acm->wioctl);
	spin_lock_init(&acm->ग_लिखो_lock);
	spin_lock_init(&acm->पढ़ो_lock);
	mutex_init(&acm->mutex);
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(epपढ़ो)) अणु
		acm->bInterval = epपढ़ो->bInterval;
		acm->in = usb_rcvपूर्णांकpipe(usb_dev, epपढ़ो->bEndpoपूर्णांकAddress);
	पूर्ण अन्यथा अणु
		acm->in = usb_rcvbulkpipe(usb_dev, epपढ़ो->bEndpoपूर्णांकAddress);
	पूर्ण
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(epग_लिखो))
		acm->out = usb_sndपूर्णांकpipe(usb_dev, epग_लिखो->bEndpoपूर्णांकAddress);
	अन्यथा
		acm->out = usb_sndbulkpipe(usb_dev, epग_लिखो->bEndpoपूर्णांकAddress);
	init_usb_anchor(&acm->delayed);
	acm->quirks = quirks;

	buf = usb_alloc_coherent(usb_dev, ctrlsize, GFP_KERNEL, &acm->ctrl_dma);
	अगर (!buf)
		जाओ err_put_port;
	acm->ctrl_buffer = buf;

	अगर (acm_ग_लिखो_buffers_alloc(acm) < 0)
		जाओ err_मुक्त_ctrl_buffer;

	acm->ctrlurb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!acm->ctrlurb)
		जाओ err_मुक्त_ग_लिखो_buffers;

	क्रम (i = 0; i < num_rx_buf; i++) अणु
		काष्ठा acm_rb *rb = &(acm->पढ़ो_buffers[i]);
		काष्ठा urb *urb;

		rb->base = usb_alloc_coherent(acm->dev, पढ़ोsize, GFP_KERNEL,
								&rb->dma);
		अगर (!rb->base)
			जाओ err_मुक्त_पढ़ो_urbs;
		rb->index = i;
		rb->instance = acm;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb)
			जाओ err_मुक्त_पढ़ो_urbs;

		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_dma = rb->dma;
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(epपढ़ो))
			usb_fill_पूर्णांक_urb(urb, acm->dev, acm->in, rb->base,
					 acm->पढ़ोsize,
					 acm_पढ़ो_bulk_callback, rb,
					 acm->bInterval);
		अन्यथा
			usb_fill_bulk_urb(urb, acm->dev, acm->in, rb->base,
					  acm->पढ़ोsize,
					  acm_पढ़ो_bulk_callback, rb);

		acm->पढ़ो_urbs[i] = urb;
		__set_bit(i, &acm->पढ़ो_urbs_मुक्त);
	पूर्ण
	क्रम (i = 0; i < ACM_NW; i++) अणु
		काष्ठा acm_wb *snd = &(acm->wb[i]);

		snd->urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!snd->urb)
			जाओ err_मुक्त_ग_लिखो_urbs;

		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(epग_लिखो))
			usb_fill_पूर्णांक_urb(snd->urb, usb_dev, acm->out,
				शून्य, acm->ग_लिखोsize, acm_ग_लिखो_bulk, snd, epग_लिखो->bInterval);
		अन्यथा
			usb_fill_bulk_urb(snd->urb, usb_dev, acm->out,
				शून्य, acm->ग_लिखोsize, acm_ग_लिखो_bulk, snd);
		snd->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		अगर (quirks & SEND_ZERO_PACKET)
			snd->urb->transfer_flags |= URB_ZERO_PACKET;
		snd->instance = acm;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, acm);

	i = device_create_file(&पूर्णांकf->dev, &dev_attr_bmCapabilities);
	अगर (i < 0)
		जाओ err_मुक्त_ग_लिखो_urbs;

	अगर (h.usb_cdc_country_functional_desc) अणु /* export the country data */
		काष्ठा usb_cdc_country_functional_desc * cfd =
					h.usb_cdc_country_functional_desc;

		acm->country_codes = kदो_स्मृति(cfd->bLength - 4, GFP_KERNEL);
		अगर (!acm->country_codes)
			जाओ skip_countries;
		acm->country_code_size = cfd->bLength - 4;
		स_नकल(acm->country_codes, (u8 *)&cfd->wCountyCode0,
							cfd->bLength - 4);
		acm->country_rel_date = cfd->iCountryCodeRelDate;

		i = device_create_file(&पूर्णांकf->dev, &dev_attr_wCountryCodes);
		अगर (i < 0) अणु
			kमुक्त(acm->country_codes);
			acm->country_codes = शून्य;
			acm->country_code_size = 0;
			जाओ skip_countries;
		पूर्ण

		i = device_create_file(&पूर्णांकf->dev,
						&dev_attr_iCountryCodeRelDate);
		अगर (i < 0) अणु
			device_हटाओ_file(&पूर्णांकf->dev, &dev_attr_wCountryCodes);
			kमुक्त(acm->country_codes);
			acm->country_codes = शून्य;
			acm->country_code_size = 0;
			जाओ skip_countries;
		पूर्ण
	पूर्ण

skip_countries:
	usb_fill_पूर्णांक_urb(acm->ctrlurb, usb_dev,
			 usb_rcvपूर्णांकpipe(usb_dev, epctrl->bEndpoपूर्णांकAddress),
			 acm->ctrl_buffer, ctrlsize, acm_ctrl_irq, acm,
			 /* works around buggy devices */
			 epctrl->bInterval ? epctrl->bInterval : 16);
	acm->ctrlurb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	acm->ctrlurb->transfer_dma = acm->ctrl_dma;
	acm->notअगरication_buffer = शून्य;
	acm->nb_index = 0;
	acm->nb_size = 0;

	acm->line.dwDTERate = cpu_to_le32(9600);
	acm->line.bDataBits = 8;
	acm_set_line(acm, &acm->line);

	अगर (!acm->combined_पूर्णांकerfaces) अणु
		rv = usb_driver_claim_पूर्णांकerface(&acm_driver, data_पूर्णांकerface, acm);
		अगर (rv)
			जाओ err_हटाओ_files;
	पूर्ण

	tty_dev = tty_port_रेजिस्टर_device(&acm->port, acm_tty_driver, minor,
			&control_पूर्णांकerface->dev);
	अगर (IS_ERR(tty_dev)) अणु
		rv = PTR_ERR(tty_dev);
		जाओ err_release_data_पूर्णांकerface;
	पूर्ण

	अगर (quirks & CLEAR_HALT_CONDITIONS) अणु
		usb_clear_halt(usb_dev, acm->in);
		usb_clear_halt(usb_dev, acm->out);
	पूर्ण

	dev_info(&पूर्णांकf->dev, "ttyACM%d: USB ACM device\n", minor);

	वापस 0;

err_release_data_पूर्णांकerface:
	अगर (!acm->combined_पूर्णांकerfaces) अणु
		/* Clear driver data so that disconnect() वापसs early. */
		usb_set_पूर्णांकfdata(data_पूर्णांकerface, शून्य);
		usb_driver_release_पूर्णांकerface(&acm_driver, data_पूर्णांकerface);
	पूर्ण
err_हटाओ_files:
	अगर (acm->country_codes) अणु
		device_हटाओ_file(&acm->control->dev,
				&dev_attr_wCountryCodes);
		device_हटाओ_file(&acm->control->dev,
				&dev_attr_iCountryCodeRelDate);
	पूर्ण
	device_हटाओ_file(&acm->control->dev, &dev_attr_bmCapabilities);
err_मुक्त_ग_लिखो_urbs:
	क्रम (i = 0; i < ACM_NW; i++)
		usb_मुक्त_urb(acm->wb[i].urb);
err_मुक्त_पढ़ो_urbs:
	क्रम (i = 0; i < num_rx_buf; i++)
		usb_मुक्त_urb(acm->पढ़ो_urbs[i]);
	acm_पढ़ो_buffers_मुक्त(acm);
	usb_मुक्त_urb(acm->ctrlurb);
err_मुक्त_ग_लिखो_buffers:
	acm_ग_लिखो_buffers_मुक्त(acm);
err_मुक्त_ctrl_buffer:
	usb_मुक्त_coherent(usb_dev, ctrlsize, acm->ctrl_buffer, acm->ctrl_dma);
err_put_port:
	tty_port_put(&acm->port);

	वापस rv;
पूर्ण

अटल व्योम acm_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा acm *acm = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक i;

	/* sibling पूर्णांकerface is alपढ़ोy cleaning up */
	अगर (!acm)
		वापस;

	acm->disconnected = true;
	/*
	 * there is a circular dependency. acm_softपूर्णांक() can resubmit
	 * the URBs in error handling so we need to block any
	 * submission right away
	 */
	acm_poison_urbs(acm);
	mutex_lock(&acm->mutex);
	अगर (acm->country_codes) अणु
		device_हटाओ_file(&acm->control->dev,
				&dev_attr_wCountryCodes);
		device_हटाओ_file(&acm->control->dev,
				&dev_attr_iCountryCodeRelDate);
	पूर्ण
	wake_up_all(&acm->wioctl);
	device_हटाओ_file(&acm->control->dev, &dev_attr_bmCapabilities);
	usb_set_पूर्णांकfdata(acm->control, शून्य);
	usb_set_पूर्णांकfdata(acm->data, शून्य);
	mutex_unlock(&acm->mutex);

	tty = tty_port_tty_get(&acm->port);
	अगर (tty) अणु
		tty_vhangup(tty);
		tty_kref_put(tty);
	पूर्ण

	cancel_delayed_work_sync(&acm->dwork);

	tty_unरेजिस्टर_device(acm_tty_driver, acm->minor);

	usb_मुक्त_urb(acm->ctrlurb);
	क्रम (i = 0; i < ACM_NW; i++)
		usb_मुक्त_urb(acm->wb[i].urb);
	क्रम (i = 0; i < acm->rx_buflimit; i++)
		usb_मुक्त_urb(acm->पढ़ो_urbs[i]);
	acm_ग_लिखो_buffers_मुक्त(acm);
	usb_मुक्त_coherent(acm->dev, acm->ctrlsize, acm->ctrl_buffer, acm->ctrl_dma);
	acm_पढ़ो_buffers_मुक्त(acm);

	kमुक्त(acm->notअगरication_buffer);

	अगर (!acm->combined_पूर्णांकerfaces)
		usb_driver_release_पूर्णांकerface(&acm_driver, पूर्णांकf == acm->control ?
					acm->data : acm->control);

	tty_port_put(&acm->port);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक acm_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा acm *acm = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक cnt;

	spin_lock_irq(&acm->ग_लिखो_lock);
	अगर (PMSG_IS_AUTO(message)) अणु
		अगर (acm->transmitting) अणु
			spin_unlock_irq(&acm->ग_लिखो_lock);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	cnt = acm->susp_count++;
	spin_unlock_irq(&acm->ग_लिखो_lock);

	अगर (cnt)
		वापस 0;

	acm_poison_urbs(acm);
	cancel_delayed_work_sync(&acm->dwork);
	acm->urbs_in_error_delay = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक acm_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा acm *acm = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा urb *urb;
	पूर्णांक rv = 0;

	spin_lock_irq(&acm->ग_लिखो_lock);

	अगर (--acm->susp_count)
		जाओ out;

	acm_unpoison_urbs(acm);

	अगर (tty_port_initialized(&acm->port)) अणु
		rv = usb_submit_urb(acm->ctrlurb, GFP_ATOMIC);

		क्रम (;;) अणु
			urb = usb_get_from_anchor(&acm->delayed);
			अगर (!urb)
				अवरोध;

			acm_start_wb(acm, urb->context);
		पूर्ण

		/*
		 * delayed error checking because we must
		 * करो the ग_लिखो path at all cost
		 */
		अगर (rv < 0)
			जाओ out;

		rv = acm_submit_पढ़ो_urbs(acm, GFP_ATOMIC);
	पूर्ण
out:
	spin_unlock_irq(&acm->ग_लिखो_lock);

	वापस rv;
पूर्ण

अटल पूर्णांक acm_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा acm *acm = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (tty_port_initialized(&acm->port))
		tty_port_tty_hangup(&acm->port, false);

	वापस acm_resume(पूर्णांकf);
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक acm_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा acm *acm = usb_get_पूर्णांकfdata(पूर्णांकf);

	clear_bit(EVENT_RX_STALL, &acm->flags);
	acm->nb_index = 0; /* pending control transfers are lost */

	वापस 0;
पूर्ण

#घोषणा NOKIA_PCSUITE_ACM_INFO(x) \
		USB_DEVICE_AND_INTERFACE_INFO(0x0421, x, \
		USB_CLASS_COMM, USB_CDC_SUBCLASS_ACM, \
		USB_CDC_ACM_PROTO_VENDOR)

#घोषणा SAMSUNG_PCSUITE_ACM_INFO(x) \
		USB_DEVICE_AND_INTERFACE_INFO(0x04e7, x, \
		USB_CLASS_COMM, USB_CDC_SUBCLASS_ACM, \
		USB_CDC_ACM_PROTO_VENDOR)

/*
 * USB driver काष्ठाure.
 */

अटल स्थिर काष्ठा usb_device_id acm_ids[] = अणु
	/* quirky and broken devices */
	अणु USB_DEVICE(0x0424, 0x274e), /* Microchip Technology, Inc. (क्रमmerly SMSC) */
	  .driver_info = DISABLE_ECHO, पूर्ण, /* DISABLE ECHO in termios flag */
	अणु USB_DEVICE(0x076d, 0x0006), /* Denso Cradle CU-321 */
	.driver_info = NO_UNION_NORMAL, पूर्ण,/* has no जोड़ descriptor */
	अणु USB_DEVICE(0x17ef, 0x7000), /* Lenovo USB modem */
	.driver_info = NO_UNION_NORMAL, पूर्ण,/* has no जोड़ descriptor */
	अणु USB_DEVICE(0x0870, 0x0001), /* Metricom GS Modem */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x045b, 0x023c),	/* Renesas USB Download mode */
	.driver_info = DISABLE_ECHO,	/* Don't echo banner */
	पूर्ण,
	अणु USB_DEVICE(0x045b, 0x0248),	/* Renesas USB Download mode */
	.driver_info = DISABLE_ECHO,	/* Don't echo banner */
	पूर्ण,
	अणु USB_DEVICE(0x045b, 0x024D),	/* Renesas USB Download mode */
	.driver_info = DISABLE_ECHO,	/* Don't echo banner */
	पूर्ण,
	अणु USB_DEVICE(0x0e8d, 0x0003), /* FIREFLY, MediaTek Inc; andrey.arapov@gmail.com */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x0e8d, 0x2000), /* MediaTek Inc Preloader */
	.driver_info = DISABLE_ECHO, /* DISABLE ECHO in termios flag */
	पूर्ण,
	अणु USB_DEVICE(0x0e8d, 0x3329), /* MediaTek Inc GPS */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x0482, 0x0203), /* KYOCERA AH-K3001V */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x079b, 0x000f), /* BT On-Air USB MODEM */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x0ace, 0x1602), /* ZyDAS 56K USB MODEM */
	.driver_info = SINGLE_RX_URB,
	पूर्ण,
	अणु USB_DEVICE(0x0ace, 0x1608), /* ZyDAS 56K USB MODEM */
	.driver_info = SINGLE_RX_URB, /* firmware bug */
	पूर्ण,
	अणु USB_DEVICE(0x0ace, 0x1611), /* ZyDAS 56K USB MODEM - new version */
	.driver_info = SINGLE_RX_URB, /* firmware bug */
	पूर्ण,
	अणु USB_DEVICE(0x11ca, 0x0201), /* VeriFone Mx870 Gadget Serial */
	.driver_info = SINGLE_RX_URB,
	पूर्ण,
	अणु USB_DEVICE(0x1965, 0x0018), /* Uniden UBC125XLT */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x22b8, 0x7000), /* Motorola Q Phone */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x0803, 0x3095), /* Zoom Telephonics Model 3095F USB MODEM */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x0572, 0x1321), /* Conexant USB MODEM CX93010 */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x0572, 0x1324), /* Conexant USB MODEM RD02-D400 */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x0572, 0x1328), /* Shiro / Aztech USB MODEM UM-3100 */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x0572, 0x1349), /* Hiro (Conexant) USB MODEM H50228 */
	.driver_info = NO_UNION_NORMAL, /* has no जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x20df, 0x0001), /* Simtec Electronics Entropy Key */
	.driver_info = QUIRK_CONTROL_LINE_STATE, पूर्ण,
	अणु USB_DEVICE(0x2184, 0x001c) पूर्ण,	/* GW Instek AFG-2225 */
	अणु USB_DEVICE(0x2184, 0x0036) पूर्ण,	/* GW Instek AFG-125 */
	अणु USB_DEVICE(0x22b8, 0x6425), /* Motorola MOTOMAGX phones */
	पूर्ण,
	/* Motorola H24 HSPA module: */
	अणु USB_DEVICE(0x22b8, 0x2d91) पूर्ण, /* modem                                */
	अणु USB_DEVICE(0x22b8, 0x2d92),   /* modem           + diagnostics        */
	.driver_info = NO_UNION_NORMAL, /* handle only modem पूर्णांकerface          */
	पूर्ण,
	अणु USB_DEVICE(0x22b8, 0x2d93),   /* modem + AT port                      */
	.driver_info = NO_UNION_NORMAL, /* handle only modem पूर्णांकerface          */
	पूर्ण,
	अणु USB_DEVICE(0x22b8, 0x2d95),   /* modem + AT port + diagnostics        */
	.driver_info = NO_UNION_NORMAL, /* handle only modem पूर्णांकerface          */
	पूर्ण,
	अणु USB_DEVICE(0x22b8, 0x2d96),   /* modem                         + NMEA */
	.driver_info = NO_UNION_NORMAL, /* handle only modem पूर्णांकerface          */
	पूर्ण,
	अणु USB_DEVICE(0x22b8, 0x2d97),   /* modem           + diagnostics + NMEA */
	.driver_info = NO_UNION_NORMAL, /* handle only modem पूर्णांकerface          */
	पूर्ण,
	अणु USB_DEVICE(0x22b8, 0x2d99),   /* modem + AT port               + NMEA */
	.driver_info = NO_UNION_NORMAL, /* handle only modem पूर्णांकerface          */
	पूर्ण,
	अणु USB_DEVICE(0x22b8, 0x2d9a),   /* modem + AT port + diagnostics + NMEA */
	.driver_info = NO_UNION_NORMAL, /* handle only modem पूर्णांकerface          */
	पूर्ण,

	अणु USB_DEVICE(0x0572, 0x1329), /* Hummingbird huc56s (Conexant) */
	.driver_info = NO_UNION_NORMAL, /* जोड़ descriptor misplaced on
					   data पूर्णांकerface instead of
					   communications पूर्णांकerface.
					   Maybe we should define a new
					   quirk क्रम this. */
	पूर्ण,
	अणु USB_DEVICE(0x0572, 0x1340), /* Conexant CX93010-2x UCMxx */
	.driver_info = NO_UNION_NORMAL,
	पूर्ण,
	अणु USB_DEVICE(0x05f9, 0x4002), /* PSC Scanning, Magellan 800i */
	.driver_info = NO_UNION_NORMAL,
	पूर्ण,
	अणु USB_DEVICE(0x1bbb, 0x0003), /* Alcatel OT-I650 */
	.driver_info = NO_UNION_NORMAL, /* reports zero length descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x1576, 0x03b1), /* Maretron USB100 */
	.driver_info = NO_UNION_NORMAL, /* reports zero length descriptor */
	पूर्ण,
	अणु USB_DEVICE(0xfff0, 0x0100), /* DATECS FP-2000 */
	.driver_info = NO_UNION_NORMAL, /* reports zero length descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x09d8, 0x0320), /* Elatec GmbH TWN3 */
	.driver_info = NO_UNION_NORMAL, /* has misplaced जोड़ descriptor */
	पूर्ण,
	अणु USB_DEVICE(0x0ca6, 0xa050), /* Castles VEGA3000 */
	.driver_info = NO_UNION_NORMAL, /* reports zero length descriptor */
	पूर्ण,

	अणु USB_DEVICE(0x2912, 0x0001), /* ATOL FPrपूर्णांक */
	.driver_info = CLEAR_HALT_CONDITIONS,
	पूर्ण,

	/* Nokia S60 phones expose two ACM channels. The first is
	 * a modem and is picked up by the standard AT-command
	 * inक्रमmation below. The second is 'vendor-specific' but
	 * is treated as a serial device at the S60 end, so we want
	 * to expose it on Linux too. */
	अणु NOKIA_PCSUITE_ACM_INFO(0x042D), पूर्ण, /* Nokia 3250 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x04D8), पूर्ण, /* Nokia 5500 Sport */
	अणु NOKIA_PCSUITE_ACM_INFO(0x04C9), पूर्ण, /* Nokia E50 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0419), पूर्ण, /* Nokia E60 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x044D), पूर्ण, /* Nokia E61 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0001), पूर्ण, /* Nokia E61i */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0475), पूर्ण, /* Nokia E62 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0508), पूर्ण, /* Nokia E65 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0418), पूर्ण, /* Nokia E70 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0425), पूर्ण, /* Nokia N71 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0486), पूर्ण, /* Nokia N73 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x04DF), पूर्ण, /* Nokia N75 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x000e), पूर्ण, /* Nokia N77 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0445), पूर्ण, /* Nokia N80 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x042F), पूर्ण, /* Nokia N91 & N91 8GB */
	अणु NOKIA_PCSUITE_ACM_INFO(0x048E), पूर्ण, /* Nokia N92 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0420), पूर्ण, /* Nokia N93 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x04E6), पूर्ण, /* Nokia N93i  */
	अणु NOKIA_PCSUITE_ACM_INFO(0x04B2), पूर्ण, /* Nokia 5700 XpressMusic */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0134), पूर्ण, /* Nokia 6110 Navigator (China) */
	अणु NOKIA_PCSUITE_ACM_INFO(0x046E), पूर्ण, /* Nokia 6110 Navigator */
	अणु NOKIA_PCSUITE_ACM_INFO(0x002f), पूर्ण, /* Nokia 6120 classic &  */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0088), पूर्ण, /* Nokia 6121 classic */
	अणु NOKIA_PCSUITE_ACM_INFO(0x00fc), पूर्ण, /* Nokia 6124 classic */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0042), पूर्ण, /* Nokia E51 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x00b0), पूर्ण, /* Nokia E66 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x00ab), पूर्ण, /* Nokia E71 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0481), पूर्ण, /* Nokia N76 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0007), पूर्ण, /* Nokia N81 & N81 8GB */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0071), पूर्ण, /* Nokia N82 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x04F0), पूर्ण, /* Nokia N95 & N95-3 NAM */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0070), पूर्ण, /* Nokia N95 8GB  */
	अणु NOKIA_PCSUITE_ACM_INFO(0x00e9), पूर्ण, /* Nokia 5320 XpressMusic */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0099), पूर्ण, /* Nokia 6210 Navigator, RM-367 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0128), पूर्ण, /* Nokia 6210 Navigator, RM-419 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x008f), पूर्ण, /* Nokia 6220 Classic */
	अणु NOKIA_PCSUITE_ACM_INFO(0x00a0), पूर्ण, /* Nokia 6650 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x007b), पूर्ण, /* Nokia N78 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0094), पूर्ण, /* Nokia N85 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x003a), पूर्ण, /* Nokia N96 & N96-3  */
	अणु NOKIA_PCSUITE_ACM_INFO(0x00e9), पूर्ण, /* Nokia 5320 XpressMusic */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0108), पूर्ण, /* Nokia 5320 XpressMusic 2G */
	अणु NOKIA_PCSUITE_ACM_INFO(0x01f5), पूर्ण, /* Nokia N97, RM-505 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x02e3), पूर्ण, /* Nokia 5230, RM-588 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0178), पूर्ण, /* Nokia E63 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x010e), पूर्ण, /* Nokia E75 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x02d9), पूर्ण, /* Nokia 6760 Slide */
	अणु NOKIA_PCSUITE_ACM_INFO(0x01d0), पूर्ण, /* Nokia E52 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0223), पूर्ण, /* Nokia E72 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0275), पूर्ण, /* Nokia X6 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x026c), पूर्ण, /* Nokia N97 Mini */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0154), पूर्ण, /* Nokia 5800 XpressMusic */
	अणु NOKIA_PCSUITE_ACM_INFO(0x04ce), पूर्ण, /* Nokia E90 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x01d4), पूर्ण, /* Nokia E55 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0302), पूर्ण, /* Nokia N8 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x0335), पूर्ण, /* Nokia E7 */
	अणु NOKIA_PCSUITE_ACM_INFO(0x03cd), पूर्ण, /* Nokia C7 */
	अणु SAMSUNG_PCSUITE_ACM_INFO(0x6651), पूर्ण, /* Samsung GTi8510 (INNOV8) */

	/* Support क्रम Owen devices */
	अणु USB_DEVICE(0x03eb, 0x0030), पूर्ण, /* Owen SI30 */

	/* NOTE: non-Nokia COMM/ACM/0xff is likely MSFT RNDIS... NOT a modem! */

#अगर IS_ENABLED(CONFIG_INPUT_IMS_PCU)
	अणु USB_DEVICE(0x04d8, 0x0082),	/* Application mode */
	.driver_info = IGNORE_DEVICE,
	पूर्ण,
	अणु USB_DEVICE(0x04d8, 0x0083),	/* Bootloader mode */
	.driver_info = IGNORE_DEVICE,
	पूर्ण,
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IR_TOY)
	अणु USB_DEVICE(0x04d8, 0xfd08),
	.driver_info = IGNORE_DEVICE,
	पूर्ण,

	अणु USB_DEVICE(0x04d8, 0xf58b),
	.driver_info = IGNORE_DEVICE,
	पूर्ण,
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_SERIAL_XR)
	अणु USB_DEVICE(0x04e2, 0x1400), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1401), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1402), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1403), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1410), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1411), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1412), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1414), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1420), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1422), .driver_info = IGNORE_DEVICE पूर्ण,
	अणु USB_DEVICE(0x04e2, 0x1424), .driver_info = IGNORE_DEVICE पूर्ण,
#पूर्ण_अगर

	/*Samsung phone in firmware update mode */
	अणु USB_DEVICE(0x04e8, 0x685d),
	.driver_info = IGNORE_DEVICE,
	पूर्ण,

	/* Exclude Infineon Flash Loader utility */
	अणु USB_DEVICE(0x058b, 0x0041),
	.driver_info = IGNORE_DEVICE,
	पूर्ण,

	/* Exclude ETAS ES58x */
	अणु USB_DEVICE(0x108c, 0x0159), /* ES581.4 */
	.driver_info = IGNORE_DEVICE,
	पूर्ण,
	अणु USB_DEVICE(0x108c, 0x0168), /* ES582.1 */
	.driver_info = IGNORE_DEVICE,
	पूर्ण,
	अणु USB_DEVICE(0x108c, 0x0169), /* ES584.1 */
	.driver_info = IGNORE_DEVICE,
	पूर्ण,

	अणु USB_DEVICE(0x1bc7, 0x0021), /* Telit 3G ACM only composition */
	.driver_info = SEND_ZERO_PACKET,
	पूर्ण,
	अणु USB_DEVICE(0x1bc7, 0x0023), /* Telit 3G ACM + ECM composition */
	.driver_info = SEND_ZERO_PACKET,
	पूर्ण,

	/* Exclude Goodix Fingerprपूर्णांक Reader */
	अणु USB_DEVICE(0x27c6, 0x5395),
	.driver_info = IGNORE_DEVICE,
	पूर्ण,

	/* control पूर्णांकerfaces without any protocol set */
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_ACM,
		USB_CDC_PROTO_NONE) पूर्ण,

	/* control पूर्णांकerfaces with various AT-command sets */
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_ACM,
		USB_CDC_ACM_PROTO_AT_V25TER) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_ACM,
		USB_CDC_ACM_PROTO_AT_PCCA101) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_ACM,
		USB_CDC_ACM_PROTO_AT_PCCA101_WAKE) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_ACM,
		USB_CDC_ACM_PROTO_AT_GSM) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_ACM,
		USB_CDC_ACM_PROTO_AT_3G) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_ACM,
		USB_CDC_ACM_PROTO_AT_CDMA) पूर्ण,

	अणु USB_DEVICE(0x1519, 0x0452), /* Intel 7260 modem */
	.driver_info = SEND_ZERO_PACKET,
	पूर्ण,

	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, acm_ids);

अटल काष्ठा usb_driver acm_driver = अणु
	.name =		"cdc_acm",
	.probe =	acm_probe,
	.disconnect =	acm_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend =	acm_suspend,
	.resume =	acm_resume,
	.reset_resume =	acm_reset_resume,
#पूर्ण_अगर
	.pre_reset =	acm_pre_reset,
	.id_table =	acm_ids,
#अगर_घोषित CONFIG_PM
	.supports_स्वतःsuspend = 1,
#पूर्ण_अगर
	.disable_hub_initiated_lpm = 1,
पूर्ण;

/*
 * TTY driver काष्ठाures.
 */

अटल स्थिर काष्ठा tty_operations acm_ops = अणु
	.install =		acm_tty_install,
	.खोलो =			acm_tty_खोलो,
	.बंद =		acm_tty_बंद,
	.cleanup =		acm_tty_cleanup,
	.hangup =		acm_tty_hangup,
	.ग_लिखो =		acm_tty_ग_लिखो,
	.ग_लिखो_room =		acm_tty_ग_लिखो_room,
	.ioctl =		acm_tty_ioctl,
	.throttle =		acm_tty_throttle,
	.unthrottle =		acm_tty_unthrottle,
	.अक्षरs_in_buffer =	acm_tty_अक्षरs_in_buffer,
	.अवरोध_ctl =		acm_tty_अवरोध_ctl,
	.set_termios =		acm_tty_set_termios,
	.tiocmget =		acm_tty_tiocmget,
	.tiocmset =		acm_tty_tiocmset,
	.get_serial =		get_serial_info,
	.set_serial =		set_serial_info,
	.get_icount =		acm_tty_get_icount,
पूर्ण;

/*
 * Init / निकास.
 */

अटल पूर्णांक __init acm_init(व्योम)
अणु
	पूर्णांक retval;
	acm_tty_driver = alloc_tty_driver(ACM_TTY_MINORS);
	अगर (!acm_tty_driver)
		वापस -ENOMEM;
	acm_tty_driver->driver_name = "acm",
	acm_tty_driver->name = "ttyACM",
	acm_tty_driver->major = ACM_TTY_MAJOR,
	acm_tty_driver->minor_start = 0,
	acm_tty_driver->type = TTY_DRIVER_TYPE_SERIAL,
	acm_tty_driver->subtype = SERIAL_TYPE_NORMAL,
	acm_tty_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	acm_tty_driver->init_termios = tty_std_termios;
	acm_tty_driver->init_termios.c_cflag = B9600 | CS8 | CREAD |
								HUPCL | CLOCAL;
	tty_set_operations(acm_tty_driver, &acm_ops);

	retval = tty_रेजिस्टर_driver(acm_tty_driver);
	अगर (retval) अणु
		put_tty_driver(acm_tty_driver);
		वापस retval;
	पूर्ण

	retval = usb_रेजिस्टर(&acm_driver);
	अगर (retval) अणु
		tty_unरेजिस्टर_driver(acm_tty_driver);
		put_tty_driver(acm_tty_driver);
		वापस retval;
	पूर्ण

	prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": " DRIVER_DESC "\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास acm_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&acm_driver);
	tty_unरेजिस्टर_driver(acm_tty_driver);
	put_tty_driver(acm_tty_driver);
	idr_destroy(&acm_minors);
पूर्ण

module_init(acm_init);
module_निकास(acm_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV_MAJOR(ACM_TTY_MAJOR);
