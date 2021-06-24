<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LIRC base driver
 *
 * by Artur Liघातski <aliघातski@पूर्णांकeria.pl>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/file.h>
#समावेश <linux/idr.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>

#समावेश "rc-core-priv.h"
#समावेश <uapi/linux/lirc.h>

#घोषणा LIRCBUF_SIZE	1024

अटल dev_t lirc_base_dev;

/* Used to keep track of allocated lirc devices */
अटल DEFINE_IDA(lirc_ida);

/* Only used क्रम sysfs but defined to व्योम otherwise */
अटल काष्ठा class *lirc_class;

/**
 * lirc_raw_event() - Send raw IR data to lirc to be relayed to userspace
 *
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 */
व्योम lirc_raw_event(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lirc_fh *fh;
	पूर्णांक sample;

	/* Packet start */
	अगर (ev.reset) अणु
		/*
		 * Userspace expects a दीर्घ space event beक्रमe the start of
		 * the संकेत to use as a sync.  This may be करोne with repeat
		 * packets and normal samples.  But अगर a reset has been sent
		 * then we assume that a दीर्घ समय has passed, so we send a
		 * space with the maximum समय value.
		 */
		sample = LIRC_SPACE(LIRC_VALUE_MASK);
		dev_dbg(&dev->dev, "delivering reset sync space to lirc_dev\n");

	/* Carrier reports */
	पूर्ण अन्यथा अगर (ev.carrier_report) अणु
		sample = LIRC_FREQUENCY(ev.carrier);
		dev_dbg(&dev->dev, "carrier report (freq: %d)\n", sample);

	/* Packet end */
	पूर्ण अन्यथा अगर (ev.समयout) अणु
		अगर (dev->gap)
			वापस;

		dev->gap_start = kसमय_get();
		dev->gap = true;
		dev->gap_duration = ev.duration;

		sample = LIRC_TIMEOUT(ev.duration);
		dev_dbg(&dev->dev, "timeout report (duration: %d)\n", sample);

	/* Normal sample */
	पूर्ण अन्यथा अणु
		अगर (dev->gap) अणु
			dev->gap_duration += kसमय_प्रकारo_us(kसमय_sub(kसमय_get(),
							 dev->gap_start));

			/* Cap by LIRC_VALUE_MASK */
			dev->gap_duration = min_t(u64, dev->gap_duration,
						  LIRC_VALUE_MASK);

			spin_lock_irqsave(&dev->lirc_fh_lock, flags);
			list_क्रम_each_entry(fh, &dev->lirc_fh, list)
				kfअगरo_put(&fh->rawir,
					  LIRC_SPACE(dev->gap_duration));
			spin_unlock_irqrestore(&dev->lirc_fh_lock, flags);
			dev->gap = false;
		पूर्ण

		sample = ev.pulse ? LIRC_PULSE(ev.duration) :
					LIRC_SPACE(ev.duration);
		dev_dbg(&dev->dev, "delivering %uus %s to lirc_dev\n",
			ev.duration, TO_STR(ev.pulse));
	पूर्ण

	/*
	 * bpf करोes not care about the gap generated above; that exists
	 * क्रम backwards compatibility
	 */
	lirc_bpf_run(dev, sample);

	spin_lock_irqsave(&dev->lirc_fh_lock, flags);
	list_क्रम_each_entry(fh, &dev->lirc_fh, list) अणु
		अगर (LIRC_IS_TIMEOUT(sample) && !fh->send_समयout_reports)
			जारी;
		अगर (kfअगरo_put(&fh->rawir, sample))
			wake_up_poll(&fh->रुको_poll, EPOLLIN | EPOLLRDNORM);
	पूर्ण
	spin_unlock_irqrestore(&dev->lirc_fh_lock, flags);
पूर्ण

/**
 * lirc_scancode_event() - Send scancode data to lirc to be relayed to
 *		userspace. This can be called in atomic context.
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @lsc:	the काष्ठा lirc_scancode describing the decoded scancode
 */
व्योम lirc_scancode_event(काष्ठा rc_dev *dev, काष्ठा lirc_scancode *lsc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lirc_fh *fh;

	lsc->बारtamp = kसमय_get_ns();

	spin_lock_irqsave(&dev->lirc_fh_lock, flags);
	list_क्रम_each_entry(fh, &dev->lirc_fh, list) अणु
		अगर (kfअगरo_put(&fh->scancodes, *lsc))
			wake_up_poll(&fh->रुको_poll, EPOLLIN | EPOLLRDNORM);
	पूर्ण
	spin_unlock_irqrestore(&dev->lirc_fh_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(lirc_scancode_event);

अटल पूर्णांक lirc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rc_dev *dev = container_of(inode->i_cdev, काष्ठा rc_dev,
					  lirc_cdev);
	काष्ठा lirc_fh *fh = kzalloc(माप(*fh), GFP_KERNEL);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (!fh)
		वापस -ENOMEM;

	get_device(&dev->dev);

	अगर (!dev->रेजिस्टरed) अणु
		retval = -ENODEV;
		जाओ out_fh;
	पूर्ण

	अगर (dev->driver_type == RC_DRIVER_IR_RAW) अणु
		अगर (kfअगरo_alloc(&fh->rawir, MAX_IR_EVENT_SIZE, GFP_KERNEL)) अणु
			retval = -ENOMEM;
			जाओ out_fh;
		पूर्ण
	पूर्ण

	अगर (dev->driver_type != RC_DRIVER_IR_RAW_TX) अणु
		अगर (kfअगरo_alloc(&fh->scancodes, 32, GFP_KERNEL)) अणु
			retval = -ENOMEM;
			जाओ out_rawir;
		पूर्ण
	पूर्ण

	fh->send_mode = LIRC_MODE_PULSE;
	fh->rc = dev;
	fh->send_समयout_reports = true;

	अगर (dev->driver_type == RC_DRIVER_SCANCODE)
		fh->rec_mode = LIRC_MODE_SCANCODE;
	अन्यथा
		fh->rec_mode = LIRC_MODE_MODE2;

	retval = rc_खोलो(dev);
	अगर (retval)
		जाओ out_kfअगरo;

	init_रुकोqueue_head(&fh->रुको_poll);

	file->निजी_data = fh;
	spin_lock_irqsave(&dev->lirc_fh_lock, flags);
	list_add(&fh->list, &dev->lirc_fh);
	spin_unlock_irqrestore(&dev->lirc_fh_lock, flags);

	stream_खोलो(inode, file);

	वापस 0;
out_kfअगरo:
	अगर (dev->driver_type != RC_DRIVER_IR_RAW_TX)
		kfअगरo_मुक्त(&fh->scancodes);
out_rawir:
	अगर (dev->driver_type == RC_DRIVER_IR_RAW)
		kfअगरo_मुक्त(&fh->rawir);
out_fh:
	kमुक्त(fh);
	put_device(&dev->dev);

	वापस retval;
पूर्ण

अटल पूर्णांक lirc_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा lirc_fh *fh = file->निजी_data;
	काष्ठा rc_dev *dev = fh->rc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lirc_fh_lock, flags);
	list_del(&fh->list);
	spin_unlock_irqrestore(&dev->lirc_fh_lock, flags);

	अगर (dev->driver_type == RC_DRIVER_IR_RAW)
		kfअगरo_मुक्त(&fh->rawir);
	अगर (dev->driver_type != RC_DRIVER_IR_RAW_TX)
		kfअगरo_मुक्त(&fh->scancodes);
	kमुक्त(fh);

	rc_बंद(dev);
	put_device(&dev->dev);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार lirc_transmit(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार n, loff_t *ppos)
अणु
	काष्ठा lirc_fh *fh = file->निजी_data;
	काष्ठा rc_dev *dev = fh->rc;
	अचिन्हित पूर्णांक *txbuf;
	काष्ठा ir_raw_event *raw = शून्य;
	sमाप_प्रकार ret;
	माप_प्रकार count;
	kसमय_प्रकार start;
	s64 toरुको;
	अचिन्हित पूर्णांक duration = 0; /* संकेत duration in us */
	पूर्णांक i;

	ret = mutex_lock_पूर्णांकerruptible(&dev->lock);
	अगर (ret)
		वापस ret;

	अगर (!dev->रेजिस्टरed) अणु
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	अगर (!dev->tx_ir) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (fh->send_mode == LIRC_MODE_SCANCODE) अणु
		काष्ठा lirc_scancode scan;

		अगर (n != माप(scan)) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		अगर (copy_from_user(&scan, buf, माप(scan))) अणु
			ret = -EFAULT;
			जाओ out_unlock;
		पूर्ण

		अगर (scan.flags || scan.keycode || scan.बारtamp ||
		    scan.rc_proto > RC_PROTO_MAX) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		/* We only have encoders क्रम 32-bit protocols. */
		अगर (scan.scancode > U32_MAX ||
		    !rc_validate_scancode(scan.rc_proto, scan.scancode)) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		raw = kदो_स्मृति_array(LIRCBUF_SIZE, माप(*raw), GFP_KERNEL);
		अगर (!raw) अणु
			ret = -ENOMEM;
			जाओ out_unlock;
		पूर्ण

		ret = ir_raw_encode_scancode(scan.rc_proto, scan.scancode,
					     raw, LIRCBUF_SIZE);
		अगर (ret < 0)
			जाओ out_kमुक्त_raw;

		count = ret;

		txbuf = kदो_स्मृति_array(count, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
		अगर (!txbuf) अणु
			ret = -ENOMEM;
			जाओ out_kमुक्त_raw;
		पूर्ण

		क्रम (i = 0; i < count; i++)
			txbuf[i] = raw[i].duration;

		अगर (dev->s_tx_carrier) अणु
			पूर्णांक carrier = ir_raw_encode_carrier(scan.rc_proto);

			अगर (carrier > 0)
				dev->s_tx_carrier(dev, carrier);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (n < माप(अचिन्हित पूर्णांक) || n % माप(अचिन्हित पूर्णांक)) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		count = n / माप(अचिन्हित पूर्णांक);
		अगर (count > LIRCBUF_SIZE || count % 2 == 0) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		txbuf = memdup_user(buf, n);
		अगर (IS_ERR(txbuf)) अणु
			ret = PTR_ERR(txbuf);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अगर (txbuf[i] > IR_MAX_DURATION - duration || !txbuf[i]) अणु
			ret = -EINVAL;
			जाओ out_kमुक्त;
		पूर्ण

		duration += txbuf[i];
	पूर्ण

	start = kसमय_get();

	ret = dev->tx_ir(dev, txbuf, count);
	अगर (ret < 0)
		जाओ out_kमुक्त;

	kमुक्त(txbuf);
	kमुक्त(raw);
	mutex_unlock(&dev->lock);

	/*
	 * The lircd gap calculation expects the ग_लिखो function to
	 * रुको क्रम the actual IR संकेत to be transmitted beक्रमe
	 * वापसing.
	 */
	toरुको = kसमय_us_delta(kसमय_add_us(start, duration),
				kसमय_get());
	अगर (toरुको > 0) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(usecs_to_jअगरfies(toरुको));
	पूर्ण

	वापस n;
out_kमुक्त:
	kमुक्त(txbuf);
out_kमुक्त_raw:
	kमुक्त(raw);
out_unlock:
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल दीर्घ lirc_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा lirc_fh *fh = file->निजी_data;
	काष्ठा rc_dev *dev = fh->rc;
	u32 __user *argp = (u32 __user *)(arg);
	u32 val = 0;
	पूर्णांक ret;

	अगर (_IOC_सूची(cmd) & _IOC_WRITE) अणु
		ret = get_user(val, argp);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&dev->lock);
	अगर (ret)
		वापस ret;

	अगर (!dev->रेजिस्टरed) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (cmd) अणु
	हाल LIRC_GET_FEATURES:
		अगर (dev->driver_type == RC_DRIVER_SCANCODE)
			val |= LIRC_CAN_REC_SCANCODE;

		अगर (dev->driver_type == RC_DRIVER_IR_RAW) अणु
			val |= LIRC_CAN_REC_MODE2;
			अगर (dev->rx_resolution)
				val |= LIRC_CAN_GET_REC_RESOLUTION;
		पूर्ण

		अगर (dev->tx_ir) अणु
			val |= LIRC_CAN_SEND_PULSE;
			अगर (dev->s_tx_mask)
				val |= LIRC_CAN_SET_TRANSMITTER_MASK;
			अगर (dev->s_tx_carrier)
				val |= LIRC_CAN_SET_SEND_CARRIER;
			अगर (dev->s_tx_duty_cycle)
				val |= LIRC_CAN_SET_SEND_DUTY_CYCLE;
		पूर्ण

		अगर (dev->s_rx_carrier_range)
			val |= LIRC_CAN_SET_REC_CARRIER |
				LIRC_CAN_SET_REC_CARRIER_RANGE;

		अगर (dev->s_learning_mode)
			val |= LIRC_CAN_USE_WIDEBAND_RECEIVER;

		अगर (dev->s_carrier_report)
			val |= LIRC_CAN_MEASURE_CARRIER;

		अगर (dev->max_समयout)
			val |= LIRC_CAN_SET_REC_TIMEOUT;

		अवरोध;

	/* mode support */
	हाल LIRC_GET_REC_MODE:
		अगर (dev->driver_type == RC_DRIVER_IR_RAW_TX)
			ret = -ENOTTY;
		अन्यथा
			val = fh->rec_mode;
		अवरोध;

	हाल LIRC_SET_REC_MODE:
		चयन (dev->driver_type) अणु
		हाल RC_DRIVER_IR_RAW_TX:
			ret = -ENOTTY;
			अवरोध;
		हाल RC_DRIVER_SCANCODE:
			अगर (val != LIRC_MODE_SCANCODE)
				ret = -EINVAL;
			अवरोध;
		हाल RC_DRIVER_IR_RAW:
			अगर (!(val == LIRC_MODE_MODE2 ||
			      val == LIRC_MODE_SCANCODE))
				ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (!ret)
			fh->rec_mode = val;
		अवरोध;

	हाल LIRC_GET_SEND_MODE:
		अगर (!dev->tx_ir)
			ret = -ENOTTY;
		अन्यथा
			val = fh->send_mode;
		अवरोध;

	हाल LIRC_SET_SEND_MODE:
		अगर (!dev->tx_ir)
			ret = -ENOTTY;
		अन्यथा अगर (!(val == LIRC_MODE_PULSE || val == LIRC_MODE_SCANCODE))
			ret = -EINVAL;
		अन्यथा
			fh->send_mode = val;
		अवरोध;

	/* TX settings */
	हाल LIRC_SET_TRANSMITTER_MASK:
		अगर (!dev->s_tx_mask)
			ret = -ENOTTY;
		अन्यथा
			ret = dev->s_tx_mask(dev, val);
		अवरोध;

	हाल LIRC_SET_SEND_CARRIER:
		अगर (!dev->s_tx_carrier)
			ret = -ENOTTY;
		अन्यथा
			ret = dev->s_tx_carrier(dev, val);
		अवरोध;

	हाल LIRC_SET_SEND_DUTY_CYCLE:
		अगर (!dev->s_tx_duty_cycle)
			ret = -ENOTTY;
		अन्यथा अगर (val <= 0 || val >= 100)
			ret = -EINVAL;
		अन्यथा
			ret = dev->s_tx_duty_cycle(dev, val);
		अवरोध;

	/* RX settings */
	हाल LIRC_SET_REC_CARRIER:
		अगर (!dev->s_rx_carrier_range)
			ret = -ENOTTY;
		अन्यथा अगर (val <= 0)
			ret = -EINVAL;
		अन्यथा
			ret = dev->s_rx_carrier_range(dev, fh->carrier_low,
						      val);
		अवरोध;

	हाल LIRC_SET_REC_CARRIER_RANGE:
		अगर (!dev->s_rx_carrier_range)
			ret = -ENOTTY;
		अन्यथा अगर (val <= 0)
			ret = -EINVAL;
		अन्यथा
			fh->carrier_low = val;
		अवरोध;

	हाल LIRC_GET_REC_RESOLUTION:
		अगर (!dev->rx_resolution)
			ret = -ENOTTY;
		अन्यथा
			val = dev->rx_resolution;
		अवरोध;

	हाल LIRC_SET_WIDEBAND_RECEIVER:
		अगर (!dev->s_learning_mode)
			ret = -ENOTTY;
		अन्यथा
			ret = dev->s_learning_mode(dev, !!val);
		अवरोध;

	हाल LIRC_SET_MEASURE_CARRIER_MODE:
		अगर (!dev->s_carrier_report)
			ret = -ENOTTY;
		अन्यथा
			ret = dev->s_carrier_report(dev, !!val);
		अवरोध;

	/* Generic समयout support */
	हाल LIRC_GET_MIN_TIMEOUT:
		अगर (!dev->max_समयout)
			ret = -ENOTTY;
		अन्यथा
			val = dev->min_समयout;
		अवरोध;

	हाल LIRC_GET_MAX_TIMEOUT:
		अगर (!dev->max_समयout)
			ret = -ENOTTY;
		अन्यथा
			val = dev->max_समयout;
		अवरोध;

	हाल LIRC_SET_REC_TIMEOUT:
		अगर (!dev->max_समयout) अणु
			ret = -ENOTTY;
		पूर्ण अन्यथा अणु
			अगर (val < dev->min_समयout || val > dev->max_समयout)
				ret = -EINVAL;
			अन्यथा अगर (dev->s_समयout)
				ret = dev->s_समयout(dev, val);
			अन्यथा
				dev->समयout = val;
		पूर्ण
		अवरोध;

	हाल LIRC_GET_REC_TIMEOUT:
		अगर (!dev->समयout)
			ret = -ENOTTY;
		अन्यथा
			val = dev->समयout;
		अवरोध;

	हाल LIRC_SET_REC_TIMEOUT_REPORTS:
		अगर (dev->driver_type != RC_DRIVER_IR_RAW)
			ret = -ENOTTY;
		अन्यथा
			fh->send_समयout_reports = !!val;
		अवरोध;

	शेष:
		ret = -ENOTTY;
	पूर्ण

	अगर (!ret && _IOC_सूची(cmd) & _IOC_READ)
		ret = put_user(val, argp);

out:
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल __poll_t lirc_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा lirc_fh *fh = file->निजी_data;
	काष्ठा rc_dev *rcdev = fh->rc;
	__poll_t events = 0;

	poll_रुको(file, &fh->रुको_poll, रुको);

	अगर (!rcdev->रेजिस्टरed) अणु
		events = EPOLLHUP | EPOLLERR;
	पूर्ण अन्यथा अगर (rcdev->driver_type != RC_DRIVER_IR_RAW_TX) अणु
		अगर (fh->rec_mode == LIRC_MODE_SCANCODE &&
		    !kfअगरo_is_empty(&fh->scancodes))
			events = EPOLLIN | EPOLLRDNORM;

		अगर (fh->rec_mode == LIRC_MODE_MODE2 &&
		    !kfअगरo_is_empty(&fh->rawir))
			events = EPOLLIN | EPOLLRDNORM;
	पूर्ण

	वापस events;
पूर्ण

अटल sमाप_प्रकार lirc_पढ़ो_mode2(काष्ठा file *file, अक्षर __user *buffer,
			       माप_प्रकार length)
अणु
	काष्ठा lirc_fh *fh = file->निजी_data;
	काष्ठा rc_dev *rcdev = fh->rc;
	अचिन्हित पूर्णांक copied;
	पूर्णांक ret;

	अगर (length < माप(अचिन्हित पूर्णांक) || length % माप(अचिन्हित पूर्णांक))
		वापस -EINVAL;

	करो अणु
		अगर (kfअगरo_is_empty(&fh->rawir)) अणु
			अगर (file->f_flags & O_NONBLOCK)
				वापस -EAGAIN;

			ret = रुको_event_पूर्णांकerruptible(fh->रुको_poll,
					!kfअगरo_is_empty(&fh->rawir) ||
					!rcdev->रेजिस्टरed);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (!rcdev->रेजिस्टरed)
			वापस -ENODEV;

		ret = mutex_lock_पूर्णांकerruptible(&rcdev->lock);
		अगर (ret)
			वापस ret;
		ret = kfअगरo_to_user(&fh->rawir, buffer, length, &copied);
		mutex_unlock(&rcdev->lock);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (copied == 0);

	वापस copied;
पूर्ण

अटल sमाप_प्रकार lirc_पढ़ो_scancode(काष्ठा file *file, अक्षर __user *buffer,
				  माप_प्रकार length)
अणु
	काष्ठा lirc_fh *fh = file->निजी_data;
	काष्ठा rc_dev *rcdev = fh->rc;
	अचिन्हित पूर्णांक copied;
	पूर्णांक ret;

	अगर (length < माप(काष्ठा lirc_scancode) ||
	    length % माप(काष्ठा lirc_scancode))
		वापस -EINVAL;

	करो अणु
		अगर (kfअगरo_is_empty(&fh->scancodes)) अणु
			अगर (file->f_flags & O_NONBLOCK)
				वापस -EAGAIN;

			ret = रुको_event_पूर्णांकerruptible(fh->रुको_poll,
					!kfअगरo_is_empty(&fh->scancodes) ||
					!rcdev->रेजिस्टरed);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (!rcdev->रेजिस्टरed)
			वापस -ENODEV;

		ret = mutex_lock_पूर्णांकerruptible(&rcdev->lock);
		अगर (ret)
			वापस ret;
		ret = kfअगरo_to_user(&fh->scancodes, buffer, length, &copied);
		mutex_unlock(&rcdev->lock);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (copied == 0);

	वापस copied;
पूर्ण

अटल sमाप_प्रकार lirc_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार length,
			 loff_t *ppos)
अणु
	काष्ठा lirc_fh *fh = file->निजी_data;
	काष्ठा rc_dev *rcdev = fh->rc;

	अगर (rcdev->driver_type == RC_DRIVER_IR_RAW_TX)
		वापस -EINVAL;

	अगर (!rcdev->रेजिस्टरed)
		वापस -ENODEV;

	अगर (fh->rec_mode == LIRC_MODE_MODE2)
		वापस lirc_पढ़ो_mode2(file, buffer, length);
	अन्यथा /* LIRC_MODE_SCANCODE */
		वापस lirc_पढ़ो_scancode(file, buffer, length);
पूर्ण

अटल स्थिर काष्ठा file_operations lirc_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= lirc_transmit,
	.unlocked_ioctl	= lirc_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.पढ़ो		= lirc_पढ़ो,
	.poll		= lirc_poll,
	.खोलो		= lirc_खोलो,
	.release	= lirc_बंद,
	.llseek		= no_llseek,
पूर्ण;

अटल व्योम lirc_release_device(काष्ठा device *ld)
अणु
	काष्ठा rc_dev *rcdev = container_of(ld, काष्ठा rc_dev, lirc_dev);

	put_device(&rcdev->dev);
पूर्ण

पूर्णांक lirc_रेजिस्टर(काष्ठा rc_dev *dev)
अणु
	स्थिर अक्षर *rx_type, *tx_type;
	पूर्णांक err, minor;

	minor = ida_simple_get(&lirc_ida, 0, RC_DEV_MAX, GFP_KERNEL);
	अगर (minor < 0)
		वापस minor;

	device_initialize(&dev->lirc_dev);
	dev->lirc_dev.class = lirc_class;
	dev->lirc_dev.parent = &dev->dev;
	dev->lirc_dev.release = lirc_release_device;
	dev->lirc_dev.devt = MKDEV(MAJOR(lirc_base_dev), minor);
	dev_set_name(&dev->lirc_dev, "lirc%d", minor);

	INIT_LIST_HEAD(&dev->lirc_fh);
	spin_lock_init(&dev->lirc_fh_lock);

	cdev_init(&dev->lirc_cdev, &lirc_fops);

	err = cdev_device_add(&dev->lirc_cdev, &dev->lirc_dev);
	अगर (err)
		जाओ out_ida;

	get_device(&dev->dev);

	चयन (dev->driver_type) अणु
	हाल RC_DRIVER_SCANCODE:
		rx_type = "scancode";
		अवरोध;
	हाल RC_DRIVER_IR_RAW:
		rx_type = "raw IR";
		अवरोध;
	शेष:
		rx_type = "no";
		अवरोध;
	पूर्ण

	अगर (dev->tx_ir)
		tx_type = "raw IR";
	अन्यथा
		tx_type = "no";

	dev_info(&dev->dev, "lirc_dev: driver %s registered at minor = %d, %s receiver, %s transmitter",
		 dev->driver_name, minor, rx_type, tx_type);

	वापस 0;

out_ida:
	ida_simple_हटाओ(&lirc_ida, minor);
	वापस err;
पूर्ण

व्योम lirc_unरेजिस्टर(काष्ठा rc_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lirc_fh *fh;

	dev_dbg(&dev->dev, "lirc_dev: driver %s unregistered from minor = %d\n",
		dev->driver_name, MINOR(dev->lirc_dev.devt));

	spin_lock_irqsave(&dev->lirc_fh_lock, flags);
	list_क्रम_each_entry(fh, &dev->lirc_fh, list)
		wake_up_poll(&fh->रुको_poll, EPOLLHUP | EPOLLERR);
	spin_unlock_irqrestore(&dev->lirc_fh_lock, flags);

	cdev_device_del(&dev->lirc_cdev, &dev->lirc_dev);
	ida_simple_हटाओ(&lirc_ida, MINOR(dev->lirc_dev.devt));
पूर्ण

पूर्णांक __init lirc_dev_init(व्योम)
अणु
	पूर्णांक retval;

	lirc_class = class_create(THIS_MODULE, "lirc");
	अगर (IS_ERR(lirc_class)) अणु
		pr_err("class_create failed\n");
		वापस PTR_ERR(lirc_class);
	पूर्ण

	retval = alloc_chrdev_region(&lirc_base_dev, 0, RC_DEV_MAX, "lirc");
	अगर (retval) अणु
		class_destroy(lirc_class);
		pr_err("alloc_chrdev_region failed\n");
		वापस retval;
	पूर्ण

	pr_debug("IR Remote Control driver registered, major %d\n",
		 MAJOR(lirc_base_dev));

	वापस 0;
पूर्ण

व्योम __निकास lirc_dev_निकास(व्योम)
अणु
	class_destroy(lirc_class);
	unरेजिस्टर_chrdev_region(lirc_base_dev, RC_DEV_MAX);
पूर्ण

काष्ठा rc_dev *rc_dev_get_from_fd(पूर्णांक fd)
अणु
	काष्ठा fd f = fdget(fd);
	काष्ठा lirc_fh *fh;
	काष्ठा rc_dev *dev;

	अगर (!f.file)
		वापस ERR_PTR(-EBADF);

	अगर (f.file->f_op != &lirc_fops) अणु
		fdput(f);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	fh = f.file->निजी_data;
	dev = fh->rc;

	get_device(&dev->dev);
	fdput(f);

	वापस dev;
पूर्ण

MODULE_ALIAS("lirc_dev");
