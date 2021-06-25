<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/anon_inodes.h>
#समावेश <linux/atomic.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/cdev.h>
#समावेश <linux/compat.h>
#समावेश <linux/compiler.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/file.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/poll.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयkeeping.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/gpपन.स>

#समावेश "gpiolib.h"
#समावेश "gpiolib-cdev.h"

/*
 * Array sizes must ensure 64-bit alignment and not create holes in the
 * काष्ठा packing.
 */
अटल_निश्चित(IS_ALIGNED(GPIO_V2_LINES_MAX, 2));
अटल_निश्चित(IS_ALIGNED(GPIO_MAX_NAME_SIZE, 8));

/*
 * Check that uAPI काष्ठाs are 64-bit aligned क्रम 32/64-bit compatibility
 */
अटल_निश्चित(IS_ALIGNED(माप(काष्ठा gpio_v2_line_attribute), 8));
अटल_निश्चित(IS_ALIGNED(माप(काष्ठा gpio_v2_line_config_attribute), 8));
अटल_निश्चित(IS_ALIGNED(माप(काष्ठा gpio_v2_line_config), 8));
अटल_निश्चित(IS_ALIGNED(माप(काष्ठा gpio_v2_line_request), 8));
अटल_निश्चित(IS_ALIGNED(माप(काष्ठा gpio_v2_line_info), 8));
अटल_निश्चित(IS_ALIGNED(माप(काष्ठा gpio_v2_line_info_changed), 8));
अटल_निश्चित(IS_ALIGNED(माप(काष्ठा gpio_v2_line_event), 8));
अटल_निश्चित(IS_ALIGNED(माप(काष्ठा gpio_v2_line_values), 8));

/* Character device पूर्णांकerface to GPIO.
 *
 * The GPIO अक्षरacter device, /dev/gpiochipN, provides userspace an
 * पूर्णांकerface to gpiolib GPIOs via ioctl()s.
 */

/*
 * GPIO line handle management
 */

#अगर_घोषित CONFIG_GPIO_CDEV_V1
/**
 * काष्ठा linehandle_state - contains the state of a userspace handle
 * @gdev: the GPIO device the handle pertains to
 * @label: consumer label used to tag descriptors
 * @descs: the GPIO descriptors held by this handle
 * @num_descs: the number of descriptors held in the descs array
 */
काष्ठा linehandle_state अणु
	काष्ठा gpio_device *gdev;
	स्थिर अक्षर *label;
	काष्ठा gpio_desc *descs[GPIOHANDLES_MAX];
	u32 num_descs;
पूर्ण;

#घोषणा GPIOHANDLE_REQUEST_VALID_FLAGS \
	(GPIOHANDLE_REQUEST_INPUT | \
	GPIOHANDLE_REQUEST_OUTPUT | \
	GPIOHANDLE_REQUEST_ACTIVE_LOW | \
	GPIOHANDLE_REQUEST_BIAS_PULL_UP | \
	GPIOHANDLE_REQUEST_BIAS_PULL_DOWN | \
	GPIOHANDLE_REQUEST_BIAS_DISABLE | \
	GPIOHANDLE_REQUEST_OPEN_DRAIN | \
	GPIOHANDLE_REQUEST_OPEN_SOURCE)

अटल पूर्णांक linehandle_validate_flags(u32 flags)
अणु
	/* Return an error अगर an unknown flag is set */
	अगर (flags & ~GPIOHANDLE_REQUEST_VALID_FLAGS)
		वापस -EINVAL;

	/*
	 * Do not allow both INPUT & OUTPUT flags to be set as they are
	 * contradictory.
	 */
	अगर ((flags & GPIOHANDLE_REQUEST_INPUT) &&
	    (flags & GPIOHANDLE_REQUEST_OUTPUT))
		वापस -EINVAL;

	/*
	 * Do not allow OPEN_SOURCE & OPEN_DRAIN flags in a single request. If
	 * the hardware actually supports enabling both at the same समय the
	 * electrical result would be disastrous.
	 */
	अगर ((flags & GPIOHANDLE_REQUEST_OPEN_DRAIN) &&
	    (flags & GPIOHANDLE_REQUEST_OPEN_SOURCE))
		वापस -EINVAL;

	/* OPEN_DRAIN and OPEN_SOURCE flags only make sense क्रम output mode. */
	अगर (!(flags & GPIOHANDLE_REQUEST_OUTPUT) &&
	    ((flags & GPIOHANDLE_REQUEST_OPEN_DRAIN) ||
	     (flags & GPIOHANDLE_REQUEST_OPEN_SOURCE)))
		वापस -EINVAL;

	/* Bias flags only allowed क्रम input or output mode. */
	अगर (!((flags & GPIOHANDLE_REQUEST_INPUT) ||
	      (flags & GPIOHANDLE_REQUEST_OUTPUT)) &&
	    ((flags & GPIOHANDLE_REQUEST_BIAS_DISABLE) ||
	     (flags & GPIOHANDLE_REQUEST_BIAS_PULL_UP) ||
	     (flags & GPIOHANDLE_REQUEST_BIAS_PULL_DOWN)))
		वापस -EINVAL;

	/* Only one bias flag can be set. */
	अगर (((flags & GPIOHANDLE_REQUEST_BIAS_DISABLE) &&
	     (flags & (GPIOHANDLE_REQUEST_BIAS_PULL_DOWN |
		       GPIOHANDLE_REQUEST_BIAS_PULL_UP))) ||
	    ((flags & GPIOHANDLE_REQUEST_BIAS_PULL_DOWN) &&
	     (flags & GPIOHANDLE_REQUEST_BIAS_PULL_UP)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम linehandle_flags_to_desc_flags(u32 lflags, अचिन्हित दीर्घ *flagsp)
अणु
	assign_bit(FLAG_ACTIVE_LOW, flagsp,
		   lflags & GPIOHANDLE_REQUEST_ACTIVE_LOW);
	assign_bit(FLAG_OPEN_DRAIN, flagsp,
		   lflags & GPIOHANDLE_REQUEST_OPEN_DRAIN);
	assign_bit(FLAG_OPEN_SOURCE, flagsp,
		   lflags & GPIOHANDLE_REQUEST_OPEN_SOURCE);
	assign_bit(FLAG_PULL_UP, flagsp,
		   lflags & GPIOHANDLE_REQUEST_BIAS_PULL_UP);
	assign_bit(FLAG_PULL_DOWN, flagsp,
		   lflags & GPIOHANDLE_REQUEST_BIAS_PULL_DOWN);
	assign_bit(FLAG_BIAS_DISABLE, flagsp,
		   lflags & GPIOHANDLE_REQUEST_BIAS_DISABLE);
पूर्ण

अटल दीर्घ linehandle_set_config(काष्ठा linehandle_state *lh,
				  व्योम __user *ip)
अणु
	काष्ठा gpiohandle_config gcnf;
	काष्ठा gpio_desc *desc;
	पूर्णांक i, ret;
	u32 lflags;

	अगर (copy_from_user(&gcnf, ip, माप(gcnf)))
		वापस -EFAULT;

	lflags = gcnf.flags;
	ret = linehandle_validate_flags(lflags);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < lh->num_descs; i++) अणु
		desc = lh->descs[i];
		linehandle_flags_to_desc_flags(gcnf.flags, &desc->flags);

		/*
		 * Lines have to be requested explicitly क्रम input
		 * or output, अन्यथा the line will be treated "as is".
		 */
		अगर (lflags & GPIOHANDLE_REQUEST_OUTPUT) अणु
			पूर्णांक val = !!gcnf.शेष_values[i];

			ret = gpiod_direction_output(desc, val);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर (lflags & GPIOHANDLE_REQUEST_INPUT) अणु
			ret = gpiod_direction_input(desc);
			अगर (ret)
				वापस ret;
		पूर्ण

		blocking_notअगरier_call_chain(&desc->gdev->notअगरier,
					     GPIO_V2_LINE_CHANGED_CONFIG,
					     desc);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ linehandle_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	काष्ठा linehandle_state *lh = file->निजी_data;
	व्योम __user *ip = (व्योम __user *)arg;
	काष्ठा gpiohandle_data ghd;
	DECLARE_BITMAP(vals, GPIOHANDLES_MAX);
	पूर्णांक i;

	अगर (cmd == GPIOHANDLE_GET_LINE_VALUES_IOCTL) अणु
		/* NOTE: It's ok to पढ़ो values of output lines. */
		पूर्णांक ret = gpiod_get_array_value_complex(false,
							true,
							lh->num_descs,
							lh->descs,
							शून्य,
							vals);
		अगर (ret)
			वापस ret;

		स_रखो(&ghd, 0, माप(ghd));
		क्रम (i = 0; i < lh->num_descs; i++)
			ghd.values[i] = test_bit(i, vals);

		अगर (copy_to_user(ip, &ghd, माप(ghd)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण अन्यथा अगर (cmd == GPIOHANDLE_SET_LINE_VALUES_IOCTL) अणु
		/*
		 * All line descriptors were created at once with the same
		 * flags so just check अगर the first one is really output.
		 */
		अगर (!test_bit(FLAG_IS_OUT, &lh->descs[0]->flags))
			वापस -EPERM;

		अगर (copy_from_user(&ghd, ip, माप(ghd)))
			वापस -EFAULT;

		/* Clamp all values to [0,1] */
		क्रम (i = 0; i < lh->num_descs; i++)
			__assign_bit(i, vals, ghd.values[i]);

		/* Reuse the array setting function */
		वापस gpiod_set_array_value_complex(false,
						     true,
						     lh->num_descs,
						     lh->descs,
						     शून्य,
						     vals);
	पूर्ण अन्यथा अगर (cmd == GPIOHANDLE_SET_CONFIG_IOCTL) अणु
		वापस linehandle_set_config(lh, ip);
	पूर्ण
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ linehandle_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				    अचिन्हित दीर्घ arg)
अणु
	वापस linehandle_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल व्योम linehandle_मुक्त(काष्ठा linehandle_state *lh)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < lh->num_descs; i++)
		अगर (lh->descs[i])
			gpiod_मुक्त(lh->descs[i]);
	kमुक्त(lh->label);
	put_device(&lh->gdev->dev);
	kमुक्त(lh);
पूर्ण

अटल पूर्णांक linehandle_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	linehandle_मुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations linehandle_fileops = अणु
	.release = linehandle_release,
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
	.unlocked_ioctl = linehandle_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = linehandle_ioctl_compat,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक linehandle_create(काष्ठा gpio_device *gdev, व्योम __user *ip)
अणु
	काष्ठा gpiohandle_request handlereq;
	काष्ठा linehandle_state *lh;
	काष्ठा file *file;
	पूर्णांक fd, i, ret;
	u32 lflags;

	अगर (copy_from_user(&handlereq, ip, माप(handlereq)))
		वापस -EFAULT;
	अगर ((handlereq.lines == 0) || (handlereq.lines > GPIOHANDLES_MAX))
		वापस -EINVAL;

	lflags = handlereq.flags;

	ret = linehandle_validate_flags(lflags);
	अगर (ret)
		वापस ret;

	lh = kzalloc(माप(*lh), GFP_KERNEL);
	अगर (!lh)
		वापस -ENOMEM;
	lh->gdev = gdev;
	get_device(&gdev->dev);

	अगर (handlereq.consumer_label[0] != '\0') अणु
		/* label is only initialized अगर consumer_label is set */
		lh->label = kstrndup(handlereq.consumer_label,
				     माप(handlereq.consumer_label) - 1,
				     GFP_KERNEL);
		अगर (!lh->label) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_lh;
		पूर्ण
	पूर्ण

	lh->num_descs = handlereq.lines;

	/* Request each GPIO */
	क्रम (i = 0; i < handlereq.lines; i++) अणु
		u32 offset = handlereq.lineoffsets[i];
		काष्ठा gpio_desc *desc = gpiochip_get_desc(gdev->chip, offset);

		अगर (IS_ERR(desc)) अणु
			ret = PTR_ERR(desc);
			जाओ out_मुक्त_lh;
		पूर्ण

		ret = gpiod_request(desc, lh->label);
		अगर (ret)
			जाओ out_मुक्त_lh;
		lh->descs[i] = desc;
		linehandle_flags_to_desc_flags(handlereq.flags, &desc->flags);

		ret = gpiod_set_transitory(desc, false);
		अगर (ret < 0)
			जाओ out_मुक्त_lh;

		/*
		 * Lines have to be requested explicitly क्रम input
		 * or output, अन्यथा the line will be treated "as is".
		 */
		अगर (lflags & GPIOHANDLE_REQUEST_OUTPUT) अणु
			पूर्णांक val = !!handlereq.शेष_values[i];

			ret = gpiod_direction_output(desc, val);
			अगर (ret)
				जाओ out_मुक्त_lh;
		पूर्ण अन्यथा अगर (lflags & GPIOHANDLE_REQUEST_INPUT) अणु
			ret = gpiod_direction_input(desc);
			अगर (ret)
				जाओ out_मुक्त_lh;
		पूर्ण

		blocking_notअगरier_call_chain(&desc->gdev->notअगरier,
					     GPIO_V2_LINE_CHANGED_REQUESTED, desc);

		dev_dbg(&gdev->dev, "registered chardev handle for line %d\n",
			offset);
	पूर्ण

	fd = get_unused_fd_flags(O_RDONLY | O_CLOEXEC);
	अगर (fd < 0) अणु
		ret = fd;
		जाओ out_मुक्त_lh;
	पूर्ण

	file = anon_inode_getfile("gpio-linehandle",
				  &linehandle_fileops,
				  lh,
				  O_RDONLY | O_CLOEXEC);
	अगर (IS_ERR(file)) अणु
		ret = PTR_ERR(file);
		जाओ out_put_unused_fd;
	पूर्ण

	handlereq.fd = fd;
	अगर (copy_to_user(ip, &handlereq, माप(handlereq))) अणु
		/*
		 * fput() will trigger the release() callback, so करो not go onto
		 * the regular error cleanup path here.
		 */
		fput(file);
		put_unused_fd(fd);
		वापस -EFAULT;
	पूर्ण

	fd_install(fd, file);

	dev_dbg(&gdev->dev, "registered chardev handle for %d lines\n",
		lh->num_descs);

	वापस 0;

out_put_unused_fd:
	put_unused_fd(fd);
out_मुक्त_lh:
	linehandle_मुक्त(lh);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_GPIO_CDEV_V1 */

/**
 * काष्ठा line - contains the state of a requested line
 * @desc: the GPIO descriptor क्रम this line.
 * @req: the corresponding line request
 * @irq: the पूर्णांकerrupt triggered in response to events on this GPIO
 * @eflags: the edge flags, GPIO_V2_LINE_FLAG_EDGE_RISING and/or
 * GPIO_V2_LINE_FLAG_EDGE_FALLING, indicating the edge detection applied
 * @बारtamp_ns: cache क्रम the बारtamp storing it between hardirq and
 * IRQ thपढ़ो, used to bring the बारtamp बंद to the actual event
 * @req_seqno: the seqno क्रम the current edge event in the sequence of
 * events क्रम the corresponding line request. This is drawn from the @req.
 * @line_seqno: the seqno क्रम the current edge event in the sequence of
 * events क्रम this line.
 * @work: the worker that implements software debouncing
 * @sw_debounced: flag indicating अगर the software debouncer is active
 * @level: the current debounced physical level of the line
 */
काष्ठा line अणु
	काष्ठा gpio_desc *desc;
	/*
	 * -- edge detector specअगरic fields --
	 */
	काष्ठा linereq *req;
	अचिन्हित पूर्णांक irq;
	/*
	 * eflags is set by edge_detector_setup(), edge_detector_stop() and
	 * edge_detector_update(), which are themselves mutually exclusive,
	 * and is accessed by edge_irq_thपढ़ो() and debounce_work_func(),
	 * which can both live with a slightly stale value.
	 */
	u64 eflags;
	/*
	 * बारtamp_ns and req_seqno are accessed only by
	 * edge_irq_handler() and edge_irq_thपढ़ो(), which are themselves
	 * mutually exclusive, so no additional protection is necessary.
	 */
	u64 बारtamp_ns;
	u32 req_seqno;
	/*
	 * line_seqno is accessed by either edge_irq_thपढ़ो() or
	 * debounce_work_func(), which are themselves mutually exclusive,
	 * so no additional protection is necessary.
	 */
	u32 line_seqno;
	/*
	 * -- debouncer specअगरic fields --
	 */
	काष्ठा delayed_work work;
	/*
	 * sw_debounce is accessed by linereq_set_config(), which is the
	 * only setter, and linereq_get_values(), which can live with a
	 * slightly stale value.
	 */
	अचिन्हित पूर्णांक sw_debounced;
	/*
	 * level is accessed by debounce_work_func(), which is the only
	 * setter, and linereq_get_values() which can live with a slightly
	 * stale value.
	 */
	अचिन्हित पूर्णांक level;
पूर्ण;

/**
 * काष्ठा linereq - contains the state of a userspace line request
 * @gdev: the GPIO device the line request pertains to
 * @label: consumer label used to tag GPIO descriptors
 * @num_lines: the number of lines in the lines array
 * @रुको: रुको queue that handles blocking पढ़ोs of events
 * @event_buffer_size: the number of elements allocated in @events
 * @events: KFIFO क्रम the GPIO events
 * @seqno: the sequence number क्रम edge events generated on all lines in
 * this line request.  Note that this is not used when @num_lines is 1, as
 * the line_seqno is then the same and is cheaper to calculate.
 * @config_mutex: mutex क्रम serializing ioctl() calls to ensure consistency
 * of configuration, particularly multi-step accesses to desc flags.
 * @lines: the lines held by this line request, with @num_lines elements.
 */
काष्ठा linereq अणु
	काष्ठा gpio_device *gdev;
	स्थिर अक्षर *label;
	u32 num_lines;
	रुको_queue_head_t रुको;
	u32 event_buffer_size;
	DECLARE_KFIFO_PTR(events, काष्ठा gpio_v2_line_event);
	atomic_t seqno;
	काष्ठा mutex config_mutex;
	काष्ठा line lines[];
पूर्ण;

#घोषणा GPIO_V2_LINE_BIAS_FLAGS \
	(GPIO_V2_LINE_FLAG_BIAS_PULL_UP | \
	 GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN | \
	 GPIO_V2_LINE_FLAG_BIAS_DISABLED)

#घोषणा GPIO_V2_LINE_सूचीECTION_FLAGS \
	(GPIO_V2_LINE_FLAG_INPUT | \
	 GPIO_V2_LINE_FLAG_OUTPUT)

#घोषणा GPIO_V2_LINE_DRIVE_FLAGS \
	(GPIO_V2_LINE_FLAG_OPEN_DRAIN | \
	 GPIO_V2_LINE_FLAG_OPEN_SOURCE)

#घोषणा GPIO_V2_LINE_EDGE_FLAGS \
	(GPIO_V2_LINE_FLAG_EDGE_RISING | \
	 GPIO_V2_LINE_FLAG_EDGE_FALLING)

#घोषणा GPIO_V2_LINE_FLAG_EDGE_BOTH GPIO_V2_LINE_EDGE_FLAGS

#घोषणा GPIO_V2_LINE_VALID_FLAGS \
	(GPIO_V2_LINE_FLAG_ACTIVE_LOW | \
	 GPIO_V2_LINE_सूचीECTION_FLAGS | \
	 GPIO_V2_LINE_DRIVE_FLAGS | \
	 GPIO_V2_LINE_EDGE_FLAGS | \
	 GPIO_V2_LINE_FLAG_EVENT_CLOCK_REALTIME | \
	 GPIO_V2_LINE_BIAS_FLAGS)

अटल व्योम linereq_put_event(काष्ठा linereq *lr,
			      काष्ठा gpio_v2_line_event *le)
अणु
	bool overflow = false;

	spin_lock(&lr->रुको.lock);
	अगर (kfअगरo_is_full(&lr->events)) अणु
		overflow = true;
		kfअगरo_skip(&lr->events);
	पूर्ण
	kfअगरo_in(&lr->events, le, 1);
	spin_unlock(&lr->रुको.lock);
	अगर (!overflow)
		wake_up_poll(&lr->रुको, EPOLLIN);
	अन्यथा
		pr_debug_ratelimited("event FIFO is full - event dropped\n");
पूर्ण

अटल u64 line_event_बारtamp(काष्ठा line *line)
अणु
	अगर (test_bit(FLAG_EVENT_CLOCK_REALTIME, &line->desc->flags))
		वापस kसमय_get_real_ns();

	वापस kसमय_get_ns();
पूर्ण

अटल irqवापस_t edge_irq_thपढ़ो(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा line *line = p;
	काष्ठा linereq *lr = line->req;
	काष्ठा gpio_v2_line_event le;
	u64 eflags;

	/* Do not leak kernel stack to userspace */
	स_रखो(&le, 0, माप(le));

	अगर (line->बारtamp_ns) अणु
		le.बारtamp_ns = line->बारtamp_ns;
	पूर्ण अन्यथा अणु
		/*
		 * We may be running from a nested thपढ़ोed पूर्णांकerrupt in
		 * which हाल we didn't get the बारtamp from
		 * edge_irq_handler().
		 */
		le.बारtamp_ns = line_event_बारtamp(line);
		अगर (lr->num_lines != 1)
			line->req_seqno = atomic_inc_वापस(&lr->seqno);
	पूर्ण
	line->बारtamp_ns = 0;

	eflags = READ_ONCE(line->eflags);
	अगर (eflags == GPIO_V2_LINE_FLAG_EDGE_BOTH) अणु
		पूर्णांक level = gpiod_get_value_cansleep(line->desc);

		अगर (level)
			/* Emit low-to-high event */
			le.id = GPIO_V2_LINE_EVENT_RISING_EDGE;
		अन्यथा
			/* Emit high-to-low event */
			le.id = GPIO_V2_LINE_EVENT_FALLING_EDGE;
	पूर्ण अन्यथा अगर (eflags == GPIO_V2_LINE_FLAG_EDGE_RISING) अणु
		/* Emit low-to-high event */
		le.id = GPIO_V2_LINE_EVENT_RISING_EDGE;
	पूर्ण अन्यथा अगर (eflags == GPIO_V2_LINE_FLAG_EDGE_FALLING) अणु
		/* Emit high-to-low event */
		le.id = GPIO_V2_LINE_EVENT_FALLING_EDGE;
	पूर्ण अन्यथा अणु
		वापस IRQ_NONE;
	पूर्ण
	line->line_seqno++;
	le.line_seqno = line->line_seqno;
	le.seqno = (lr->num_lines == 1) ? le.line_seqno : line->req_seqno;
	le.offset = gpio_chip_hwgpio(line->desc);

	linereq_put_event(lr, &le);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t edge_irq_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा line *line = p;
	काष्ठा linereq *lr = line->req;

	/*
	 * Just store the बारtamp in hardirq context so we get it as
	 * बंद in समय as possible to the actual event.
	 */
	line->बारtamp_ns = line_event_बारtamp(line);

	अगर (lr->num_lines != 1)
		line->req_seqno = atomic_inc_वापस(&lr->seqno);

	वापस IRQ_WAKE_THREAD;
पूर्ण

/*
 * वापसs the current debounced logical value.
 */
अटल bool debounced_value(काष्ठा line *line)
अणु
	bool value;

	/*
	 * minor race - debouncer may be stopped here, so edge_detector_stop()
	 * must leave the value unchanged so the following will पढ़ो the level
	 * from when the debouncer was last running.
	 */
	value = READ_ONCE(line->level);

	अगर (test_bit(FLAG_ACTIVE_LOW, &line->desc->flags))
		value = !value;

	वापस value;
पूर्ण

अटल irqवापस_t debounce_irq_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा line *line = p;

	mod_delayed_work(प्रणाली_wq, &line->work,
		usecs_to_jअगरfies(READ_ONCE(line->desc->debounce_period_us)));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम debounce_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gpio_v2_line_event le;
	काष्ठा line *line = container_of(work, काष्ठा line, work.work);
	काष्ठा linereq *lr;
	पूर्णांक level;
	u64 eflags;

	level = gpiod_get_raw_value_cansleep(line->desc);
	अगर (level < 0) अणु
		pr_debug_ratelimited("debouncer failed to read line value\n");
		वापस;
	पूर्ण

	अगर (READ_ONCE(line->level) == level)
		वापस;

	WRITE_ONCE(line->level, level);

	/* -- edge detection -- */
	eflags = READ_ONCE(line->eflags);
	अगर (!eflags)
		वापस;

	/* चयन from physical level to logical - अगर they dअगरfer */
	अगर (test_bit(FLAG_ACTIVE_LOW, &line->desc->flags))
		level = !level;

	/* ignore edges that are not being monitored */
	अगर (((eflags == GPIO_V2_LINE_FLAG_EDGE_RISING) && !level) ||
	    ((eflags == GPIO_V2_LINE_FLAG_EDGE_FALLING) && level))
		वापस;

	/* Do not leak kernel stack to userspace */
	स_रखो(&le, 0, माप(le));

	lr = line->req;
	le.बारtamp_ns = line_event_बारtamp(line);
	le.offset = gpio_chip_hwgpio(line->desc);
	line->line_seqno++;
	le.line_seqno = line->line_seqno;
	le.seqno = (lr->num_lines == 1) ?
		le.line_seqno : atomic_inc_वापस(&lr->seqno);

	अगर (level)
		/* Emit low-to-high event */
		le.id = GPIO_V2_LINE_EVENT_RISING_EDGE;
	अन्यथा
		/* Emit high-to-low event */
		le.id = GPIO_V2_LINE_EVENT_FALLING_EDGE;

	linereq_put_event(lr, &le);
पूर्ण

अटल पूर्णांक debounce_setup(काष्ठा line *line,
			  अचिन्हित पूर्णांक debounce_period_us)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret, level, irq;

	/* try hardware */
	ret = gpiod_set_debounce(line->desc, debounce_period_us);
	अगर (!ret) अणु
		WRITE_ONCE(line->desc->debounce_period_us, debounce_period_us);
		वापस ret;
	पूर्ण
	अगर (ret != -ENOTSUPP)
		वापस ret;

	अगर (debounce_period_us) अणु
		/* setup software debounce */
		level = gpiod_get_raw_value_cansleep(line->desc);
		अगर (level < 0)
			वापस level;

		irq = gpiod_to_irq(line->desc);
		अगर (irq < 0)
			वापस -ENXIO;

		WRITE_ONCE(line->level, level);
		irqflags = IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING;
		ret = request_irq(irq, debounce_irq_handler, irqflags,
				  line->req->label, line);
		अगर (ret)
			वापस ret;

		WRITE_ONCE(line->sw_debounced, 1);
		line->irq = irq;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool gpio_v2_line_config_debounced(काष्ठा gpio_v2_line_config *lc,
					  अचिन्हित पूर्णांक line_idx)
अणु
	अचिन्हित पूर्णांक i;
	u64 mask = BIT_ULL(line_idx);

	क्रम (i = 0; i < lc->num_attrs; i++) अणु
		अगर ((lc->attrs[i].attr.id == GPIO_V2_LINE_ATTR_ID_DEBOUNCE) &&
		    (lc->attrs[i].mask & mask))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल u32 gpio_v2_line_config_debounce_period(काष्ठा gpio_v2_line_config *lc,
					       अचिन्हित पूर्णांक line_idx)
अणु
	अचिन्हित पूर्णांक i;
	u64 mask = BIT_ULL(line_idx);

	क्रम (i = 0; i < lc->num_attrs; i++) अणु
		अगर ((lc->attrs[i].attr.id == GPIO_V2_LINE_ATTR_ID_DEBOUNCE) &&
		    (lc->attrs[i].mask & mask))
			वापस lc->attrs[i].attr.debounce_period_us;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम edge_detector_stop(काष्ठा line *line)
अणु
	अगर (line->irq) अणु
		मुक्त_irq(line->irq, line);
		line->irq = 0;
	पूर्ण

	cancel_delayed_work_sync(&line->work);
	WRITE_ONCE(line->sw_debounced, 0);
	WRITE_ONCE(line->eflags, 0);
	अगर (line->desc)
		WRITE_ONCE(line->desc->debounce_period_us, 0);
	/* करो not change line->level - see comment in debounced_value() */
पूर्ण

अटल पूर्णांक edge_detector_setup(काष्ठा line *line,
			       काष्ठा gpio_v2_line_config *lc,
			       अचिन्हित पूर्णांक line_idx,
			       u64 eflags)
अणु
	u32 debounce_period_us;
	अचिन्हित दीर्घ irqflags = 0;
	पूर्णांक irq, ret;

	अगर (eflags && !kfअगरo_initialized(&line->req->events)) अणु
		ret = kfअगरo_alloc(&line->req->events,
				  line->req->event_buffer_size, GFP_KERNEL);
		अगर (ret)
			वापस ret;
	पूर्ण
	WRITE_ONCE(line->eflags, eflags);
	अगर (gpio_v2_line_config_debounced(lc, line_idx)) अणु
		debounce_period_us = gpio_v2_line_config_debounce_period(lc, line_idx);
		ret = debounce_setup(line, debounce_period_us);
		अगर (ret)
			वापस ret;
		WRITE_ONCE(line->desc->debounce_period_us, debounce_period_us);
	पूर्ण

	/* detection disabled or sw debouncer will provide edge detection */
	अगर (!eflags || READ_ONCE(line->sw_debounced))
		वापस 0;

	irq = gpiod_to_irq(line->desc);
	अगर (irq < 0)
		वापस -ENXIO;

	अगर (eflags & GPIO_V2_LINE_FLAG_EDGE_RISING)
		irqflags |= test_bit(FLAG_ACTIVE_LOW, &line->desc->flags) ?
			IRQF_TRIGGER_FALLING : IRQF_TRIGGER_RISING;
	अगर (eflags & GPIO_V2_LINE_FLAG_EDGE_FALLING)
		irqflags |= test_bit(FLAG_ACTIVE_LOW, &line->desc->flags) ?
			IRQF_TRIGGER_RISING : IRQF_TRIGGER_FALLING;
	irqflags |= IRQF_ONESHOT;

	/* Request a thपढ़ो to पढ़ो the events */
	ret = request_thपढ़ोed_irq(irq, edge_irq_handler, edge_irq_thपढ़ो,
				   irqflags, line->req->label, line);
	अगर (ret)
		वापस ret;

	line->irq = irq;
	वापस 0;
पूर्ण

अटल पूर्णांक edge_detector_update(काष्ठा line *line,
				काष्ठा gpio_v2_line_config *lc,
				अचिन्हित पूर्णांक line_idx,
				u64 eflags, bool polarity_change)
अणु
	अचिन्हित पूर्णांक debounce_period_us =
		gpio_v2_line_config_debounce_period(lc, line_idx);

	अगर ((READ_ONCE(line->eflags) == eflags) && !polarity_change &&
	    (READ_ONCE(line->desc->debounce_period_us) == debounce_period_us))
		वापस 0;

	/* sw debounced and still will be...*/
	अगर (debounce_period_us && READ_ONCE(line->sw_debounced)) अणु
		WRITE_ONCE(line->eflags, eflags);
		WRITE_ONCE(line->desc->debounce_period_us, debounce_period_us);
		वापस 0;
	पूर्ण

	/* reconfiguring edge detection or sw debounce being disabled */
	अगर ((line->irq && !READ_ONCE(line->sw_debounced)) ||
	    (!debounce_period_us && READ_ONCE(line->sw_debounced)))
		edge_detector_stop(line);

	वापस edge_detector_setup(line, lc, line_idx, eflags);
पूर्ण

अटल u64 gpio_v2_line_config_flags(काष्ठा gpio_v2_line_config *lc,
				     अचिन्हित पूर्णांक line_idx)
अणु
	अचिन्हित पूर्णांक i;
	u64 mask = BIT_ULL(line_idx);

	क्रम (i = 0; i < lc->num_attrs; i++) अणु
		अगर ((lc->attrs[i].attr.id == GPIO_V2_LINE_ATTR_ID_FLAGS) &&
		    (lc->attrs[i].mask & mask))
			वापस lc->attrs[i].attr.flags;
	पूर्ण
	वापस lc->flags;
पूर्ण

अटल पूर्णांक gpio_v2_line_config_output_value(काष्ठा gpio_v2_line_config *lc,
					    अचिन्हित पूर्णांक line_idx)
अणु
	अचिन्हित पूर्णांक i;
	u64 mask = BIT_ULL(line_idx);

	क्रम (i = 0; i < lc->num_attrs; i++) अणु
		अगर ((lc->attrs[i].attr.id == GPIO_V2_LINE_ATTR_ID_OUTPUT_VALUES) &&
		    (lc->attrs[i].mask & mask))
			वापस !!(lc->attrs[i].attr.values & mask);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_v2_line_flags_validate(u64 flags)
अणु
	/* Return an error अगर an unknown flag is set */
	अगर (flags & ~GPIO_V2_LINE_VALID_FLAGS)
		वापस -EINVAL;

	/*
	 * Do not allow both INPUT and OUTPUT flags to be set as they are
	 * contradictory.
	 */
	अगर ((flags & GPIO_V2_LINE_FLAG_INPUT) &&
	    (flags & GPIO_V2_LINE_FLAG_OUTPUT))
		वापस -EINVAL;

	/* Edge detection requires explicit input. */
	अगर ((flags & GPIO_V2_LINE_EDGE_FLAGS) &&
	    !(flags & GPIO_V2_LINE_FLAG_INPUT))
		वापस -EINVAL;

	/*
	 * Do not allow OPEN_SOURCE and OPEN_DRAIN flags in a single
	 * request. If the hardware actually supports enabling both at the
	 * same समय the electrical result would be disastrous.
	 */
	अगर ((flags & GPIO_V2_LINE_FLAG_OPEN_DRAIN) &&
	    (flags & GPIO_V2_LINE_FLAG_OPEN_SOURCE))
		वापस -EINVAL;

	/* Drive requires explicit output direction. */
	अगर ((flags & GPIO_V2_LINE_DRIVE_FLAGS) &&
	    !(flags & GPIO_V2_LINE_FLAG_OUTPUT))
		वापस -EINVAL;

	/* Bias requires explicit direction. */
	अगर ((flags & GPIO_V2_LINE_BIAS_FLAGS) &&
	    !(flags & GPIO_V2_LINE_सूचीECTION_FLAGS))
		वापस -EINVAL;

	/* Only one bias flag can be set. */
	अगर (((flags & GPIO_V2_LINE_FLAG_BIAS_DISABLED) &&
	     (flags & (GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN |
		       GPIO_V2_LINE_FLAG_BIAS_PULL_UP))) ||
	    ((flags & GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN) &&
	     (flags & GPIO_V2_LINE_FLAG_BIAS_PULL_UP)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_v2_line_config_validate(काष्ठा gpio_v2_line_config *lc,
					अचिन्हित पूर्णांक num_lines)
अणु
	अचिन्हित पूर्णांक i;
	u64 flags;
	पूर्णांक ret;

	अगर (lc->num_attrs > GPIO_V2_LINE_NUM_ATTRS_MAX)
		वापस -EINVAL;

	अगर (स_प्रथम_inv(lc->padding, 0, माप(lc->padding)))
		वापस -EINVAL;

	क्रम (i = 0; i < num_lines; i++) अणु
		flags = gpio_v2_line_config_flags(lc, i);
		ret = gpio_v2_line_flags_validate(flags);
		अगर (ret)
			वापस ret;

		/* debounce requires explicit input */
		अगर (gpio_v2_line_config_debounced(lc, i) &&
		    !(flags & GPIO_V2_LINE_FLAG_INPUT))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gpio_v2_line_config_flags_to_desc_flags(u64 flags,
						    अचिन्हित दीर्घ *flagsp)
अणु
	assign_bit(FLAG_ACTIVE_LOW, flagsp,
		   flags & GPIO_V2_LINE_FLAG_ACTIVE_LOW);

	अगर (flags & GPIO_V2_LINE_FLAG_OUTPUT)
		set_bit(FLAG_IS_OUT, flagsp);
	अन्यथा अगर (flags & GPIO_V2_LINE_FLAG_INPUT)
		clear_bit(FLAG_IS_OUT, flagsp);

	assign_bit(FLAG_EDGE_RISING, flagsp,
		   flags & GPIO_V2_LINE_FLAG_EDGE_RISING);
	assign_bit(FLAG_EDGE_FALLING, flagsp,
		   flags & GPIO_V2_LINE_FLAG_EDGE_FALLING);

	assign_bit(FLAG_OPEN_DRAIN, flagsp,
		   flags & GPIO_V2_LINE_FLAG_OPEN_DRAIN);
	assign_bit(FLAG_OPEN_SOURCE, flagsp,
		   flags & GPIO_V2_LINE_FLAG_OPEN_SOURCE);

	assign_bit(FLAG_PULL_UP, flagsp,
		   flags & GPIO_V2_LINE_FLAG_BIAS_PULL_UP);
	assign_bit(FLAG_PULL_DOWN, flagsp,
		   flags & GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN);
	assign_bit(FLAG_BIAS_DISABLE, flagsp,
		   flags & GPIO_V2_LINE_FLAG_BIAS_DISABLED);

	assign_bit(FLAG_EVENT_CLOCK_REALTIME, flagsp,
		   flags & GPIO_V2_LINE_FLAG_EVENT_CLOCK_REALTIME);
पूर्ण

अटल दीर्घ linereq_get_values(काष्ठा linereq *lr, व्योम __user *ip)
अणु
	काष्ठा gpio_v2_line_values lv;
	DECLARE_BITMAP(vals, GPIO_V2_LINES_MAX);
	काष्ठा gpio_desc **descs;
	अचिन्हित पूर्णांक i, didx, num_get;
	bool val;
	पूर्णांक ret;

	/* NOTE: It's ok to पढ़ो values of output lines. */
	अगर (copy_from_user(&lv, ip, माप(lv)))
		वापस -EFAULT;

	क्रम (num_get = 0, i = 0; i < lr->num_lines; i++) अणु
		अगर (lv.mask & BIT_ULL(i)) अणु
			num_get++;
			descs = &lr->lines[i].desc;
		पूर्ण
	पूर्ण

	अगर (num_get == 0)
		वापस -EINVAL;

	अगर (num_get != 1) अणु
		descs = kदो_स्मृति_array(num_get, माप(*descs), GFP_KERNEL);
		अगर (!descs)
			वापस -ENOMEM;
		क्रम (didx = 0, i = 0; i < lr->num_lines; i++) अणु
			अगर (lv.mask & BIT_ULL(i)) अणु
				descs[didx] = lr->lines[i].desc;
				didx++;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = gpiod_get_array_value_complex(false, true, num_get,
					    descs, शून्य, vals);

	अगर (num_get != 1)
		kमुक्त(descs);
	अगर (ret)
		वापस ret;

	lv.bits = 0;
	क्रम (didx = 0, i = 0; i < lr->num_lines; i++) अणु
		अगर (lv.mask & BIT_ULL(i)) अणु
			अगर (lr->lines[i].sw_debounced)
				val = debounced_value(&lr->lines[i]);
			अन्यथा
				val = test_bit(didx, vals);
			अगर (val)
				lv.bits |= BIT_ULL(i);
			didx++;
		पूर्ण
	पूर्ण

	अगर (copy_to_user(ip, &lv, माप(lv)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ linereq_set_values_unlocked(काष्ठा linereq *lr,
					काष्ठा gpio_v2_line_values *lv)
अणु
	DECLARE_BITMAP(vals, GPIO_V2_LINES_MAX);
	काष्ठा gpio_desc **descs;
	अचिन्हित पूर्णांक i, didx, num_set;
	पूर्णांक ret;

	biपंचांगap_zero(vals, GPIO_V2_LINES_MAX);
	क्रम (num_set = 0, i = 0; i < lr->num_lines; i++) अणु
		अगर (lv->mask & BIT_ULL(i)) अणु
			अगर (!test_bit(FLAG_IS_OUT, &lr->lines[i].desc->flags))
				वापस -EPERM;
			अगर (lv->bits & BIT_ULL(i))
				__set_bit(num_set, vals);
			num_set++;
			descs = &lr->lines[i].desc;
		पूर्ण
	पूर्ण
	अगर (num_set == 0)
		वापस -EINVAL;

	अगर (num_set != 1) अणु
		/* build compacted desc array and values */
		descs = kदो_स्मृति_array(num_set, माप(*descs), GFP_KERNEL);
		अगर (!descs)
			वापस -ENOMEM;
		क्रम (didx = 0, i = 0; i < lr->num_lines; i++) अणु
			अगर (lv->mask & BIT_ULL(i)) अणु
				descs[didx] = lr->lines[i].desc;
				didx++;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = gpiod_set_array_value_complex(false, true, num_set,
					    descs, शून्य, vals);

	अगर (num_set != 1)
		kमुक्त(descs);
	वापस ret;
पूर्ण

अटल दीर्घ linereq_set_values(काष्ठा linereq *lr, व्योम __user *ip)
अणु
	काष्ठा gpio_v2_line_values lv;
	पूर्णांक ret;

	अगर (copy_from_user(&lv, ip, माप(lv)))
		वापस -EFAULT;

	mutex_lock(&lr->config_mutex);

	ret = linereq_set_values_unlocked(lr, &lv);

	mutex_unlock(&lr->config_mutex);

	वापस ret;
पूर्ण

अटल दीर्घ linereq_set_config_unlocked(काष्ठा linereq *lr,
					काष्ठा gpio_v2_line_config *lc)
अणु
	काष्ठा gpio_desc *desc;
	अचिन्हित पूर्णांक i;
	u64 flags;
	bool polarity_change;
	पूर्णांक ret;

	क्रम (i = 0; i < lr->num_lines; i++) अणु
		desc = lr->lines[i].desc;
		flags = gpio_v2_line_config_flags(lc, i);
		polarity_change =
			(!!test_bit(FLAG_ACTIVE_LOW, &desc->flags) !=
			 ((flags & GPIO_V2_LINE_FLAG_ACTIVE_LOW) != 0));

		gpio_v2_line_config_flags_to_desc_flags(flags, &desc->flags);
		/*
		 * Lines have to be requested explicitly क्रम input
		 * or output, अन्यथा the line will be treated "as is".
		 */
		अगर (flags & GPIO_V2_LINE_FLAG_OUTPUT) अणु
			पूर्णांक val = gpio_v2_line_config_output_value(lc, i);

			edge_detector_stop(&lr->lines[i]);
			ret = gpiod_direction_output(desc, val);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर (flags & GPIO_V2_LINE_FLAG_INPUT) अणु
			ret = gpiod_direction_input(desc);
			अगर (ret)
				वापस ret;

			ret = edge_detector_update(&lr->lines[i], lc, i,
					flags & GPIO_V2_LINE_EDGE_FLAGS,
					polarity_change);
			अगर (ret)
				वापस ret;
		पूर्ण

		blocking_notअगरier_call_chain(&desc->gdev->notअगरier,
					     GPIO_V2_LINE_CHANGED_CONFIG,
					     desc);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ linereq_set_config(काष्ठा linereq *lr, व्योम __user *ip)
अणु
	काष्ठा gpio_v2_line_config lc;
	पूर्णांक ret;

	अगर (copy_from_user(&lc, ip, माप(lc)))
		वापस -EFAULT;

	ret = gpio_v2_line_config_validate(&lc, lr->num_lines);
	अगर (ret)
		वापस ret;

	mutex_lock(&lr->config_mutex);

	ret = linereq_set_config_unlocked(lr, &lc);

	mutex_unlock(&lr->config_mutex);

	वापस ret;
पूर्ण

अटल दीर्घ linereq_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा linereq *lr = file->निजी_data;
	व्योम __user *ip = (व्योम __user *)arg;

	अगर (cmd == GPIO_V2_LINE_GET_VALUES_IOCTL)
		वापस linereq_get_values(lr, ip);
	अन्यथा अगर (cmd == GPIO_V2_LINE_SET_VALUES_IOCTL)
		वापस linereq_set_values(lr, ip);
	अन्यथा अगर (cmd == GPIO_V2_LINE_SET_CONFIG_IOCTL)
		वापस linereq_set_config(lr, ip);

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ linereq_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	वापस linereq_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल __poll_t linereq_poll(काष्ठा file *file,
			    काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा linereq *lr = file->निजी_data;
	__poll_t events = 0;

	poll_रुको(file, &lr->रुको, रुको);

	अगर (!kfअगरo_is_empty_spinlocked_noirqsave(&lr->events,
						 &lr->रुको.lock))
		events = EPOLLIN | EPOLLRDNORM;

	वापस events;
पूर्ण

अटल sमाप_प्रकार linereq_पढ़ो(काष्ठा file *file,
			    अक्षर __user *buf,
			    माप_प्रकार count,
			    loff_t *f_ps)
अणु
	काष्ठा linereq *lr = file->निजी_data;
	काष्ठा gpio_v2_line_event le;
	sमाप_प्रकार bytes_पढ़ो = 0;
	पूर्णांक ret;

	अगर (count < माप(le))
		वापस -EINVAL;

	करो अणु
		spin_lock(&lr->रुको.lock);
		अगर (kfअगरo_is_empty(&lr->events)) अणु
			अगर (bytes_पढ़ो) अणु
				spin_unlock(&lr->रुको.lock);
				वापस bytes_पढ़ो;
			पूर्ण

			अगर (file->f_flags & O_NONBLOCK) अणु
				spin_unlock(&lr->रुको.lock);
				वापस -EAGAIN;
			पूर्ण

			ret = रुको_event_पूर्णांकerruptible_locked(lr->रुको,
					!kfअगरo_is_empty(&lr->events));
			अगर (ret) अणु
				spin_unlock(&lr->रुको.lock);
				वापस ret;
			पूर्ण
		पूर्ण

		ret = kfअगरo_out(&lr->events, &le, 1);
		spin_unlock(&lr->रुको.lock);
		अगर (ret != 1) अणु
			/*
			 * This should never happen - we were holding the
			 * lock from the moment we learned the fअगरo is no
			 * दीर्घer empty until now.
			 */
			ret = -EIO;
			अवरोध;
		पूर्ण

		अगर (copy_to_user(buf + bytes_पढ़ो, &le, माप(le)))
			वापस -EFAULT;
		bytes_पढ़ो += माप(le);
	पूर्ण जबतक (count >= bytes_पढ़ो + माप(le));

	वापस bytes_पढ़ो;
पूर्ण

अटल व्योम linereq_मुक्त(काष्ठा linereq *lr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < lr->num_lines; i++) अणु
		edge_detector_stop(&lr->lines[i]);
		अगर (lr->lines[i].desc)
			gpiod_मुक्त(lr->lines[i].desc);
	पूर्ण
	kfअगरo_मुक्त(&lr->events);
	kमुक्त(lr->label);
	put_device(&lr->gdev->dev);
	kमुक्त(lr);
पूर्ण

अटल पूर्णांक linereq_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा linereq *lr = file->निजी_data;

	linereq_मुक्त(lr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations line_fileops = अणु
	.release = linereq_release,
	.पढ़ो = linereq_पढ़ो,
	.poll = linereq_poll,
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
	.unlocked_ioctl = linereq_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = linereq_ioctl_compat,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक linereq_create(काष्ठा gpio_device *gdev, व्योम __user *ip)
अणु
	काष्ठा gpio_v2_line_request ulr;
	काष्ठा gpio_v2_line_config *lc;
	काष्ठा linereq *lr;
	काष्ठा file *file;
	u64 flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक fd, ret;

	अगर (copy_from_user(&ulr, ip, माप(ulr)))
		वापस -EFAULT;

	अगर ((ulr.num_lines == 0) || (ulr.num_lines > GPIO_V2_LINES_MAX))
		वापस -EINVAL;

	अगर (स_प्रथम_inv(ulr.padding, 0, माप(ulr.padding)))
		वापस -EINVAL;

	lc = &ulr.config;
	ret = gpio_v2_line_config_validate(lc, ulr.num_lines);
	अगर (ret)
		वापस ret;

	lr = kzalloc(काष्ठा_size(lr, lines, ulr.num_lines), GFP_KERNEL);
	अगर (!lr)
		वापस -ENOMEM;

	lr->gdev = gdev;
	get_device(&gdev->dev);

	क्रम (i = 0; i < ulr.num_lines; i++) अणु
		lr->lines[i].req = lr;
		WRITE_ONCE(lr->lines[i].sw_debounced, 0);
		INIT_DELAYED_WORK(&lr->lines[i].work, debounce_work_func);
	पूर्ण

	अगर (ulr.consumer[0] != '\0') अणु
		/* label is only initialized अगर consumer is set */
		lr->label = kstrndup(ulr.consumer, माप(ulr.consumer) - 1,
				     GFP_KERNEL);
		अगर (!lr->label) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_linereq;
		पूर्ण
	पूर्ण

	mutex_init(&lr->config_mutex);
	init_रुकोqueue_head(&lr->रुको);
	lr->event_buffer_size = ulr.event_buffer_size;
	अगर (lr->event_buffer_size == 0)
		lr->event_buffer_size = ulr.num_lines * 16;
	अन्यथा अगर (lr->event_buffer_size > GPIO_V2_LINES_MAX * 16)
		lr->event_buffer_size = GPIO_V2_LINES_MAX * 16;

	atomic_set(&lr->seqno, 0);
	lr->num_lines = ulr.num_lines;

	/* Request each GPIO */
	क्रम (i = 0; i < ulr.num_lines; i++) अणु
		u32 offset = ulr.offsets[i];
		काष्ठा gpio_desc *desc = gpiochip_get_desc(gdev->chip, offset);

		अगर (IS_ERR(desc)) अणु
			ret = PTR_ERR(desc);
			जाओ out_मुक्त_linereq;
		पूर्ण

		ret = gpiod_request(desc, lr->label);
		अगर (ret)
			जाओ out_मुक्त_linereq;

		lr->lines[i].desc = desc;
		flags = gpio_v2_line_config_flags(lc, i);
		gpio_v2_line_config_flags_to_desc_flags(flags, &desc->flags);

		ret = gpiod_set_transitory(desc, false);
		अगर (ret < 0)
			जाओ out_मुक्त_linereq;

		/*
		 * Lines have to be requested explicitly क्रम input
		 * or output, अन्यथा the line will be treated "as is".
		 */
		अगर (flags & GPIO_V2_LINE_FLAG_OUTPUT) अणु
			पूर्णांक val = gpio_v2_line_config_output_value(lc, i);

			ret = gpiod_direction_output(desc, val);
			अगर (ret)
				जाओ out_मुक्त_linereq;
		पूर्ण अन्यथा अगर (flags & GPIO_V2_LINE_FLAG_INPUT) अणु
			ret = gpiod_direction_input(desc);
			अगर (ret)
				जाओ out_मुक्त_linereq;

			ret = edge_detector_setup(&lr->lines[i], lc, i,
					flags & GPIO_V2_LINE_EDGE_FLAGS);
			अगर (ret)
				जाओ out_मुक्त_linereq;
		पूर्ण

		blocking_notअगरier_call_chain(&desc->gdev->notअगरier,
					     GPIO_V2_LINE_CHANGED_REQUESTED, desc);

		dev_dbg(&gdev->dev, "registered chardev handle for line %d\n",
			offset);
	पूर्ण

	fd = get_unused_fd_flags(O_RDONLY | O_CLOEXEC);
	अगर (fd < 0) अणु
		ret = fd;
		जाओ out_मुक्त_linereq;
	पूर्ण

	file = anon_inode_getfile("gpio-line", &line_fileops, lr,
				  O_RDONLY | O_CLOEXEC);
	अगर (IS_ERR(file)) अणु
		ret = PTR_ERR(file);
		जाओ out_put_unused_fd;
	पूर्ण

	ulr.fd = fd;
	अगर (copy_to_user(ip, &ulr, माप(ulr))) अणु
		/*
		 * fput() will trigger the release() callback, so करो not go onto
		 * the regular error cleanup path here.
		 */
		fput(file);
		put_unused_fd(fd);
		वापस -EFAULT;
	पूर्ण

	fd_install(fd, file);

	dev_dbg(&gdev->dev, "registered chardev handle for %d lines\n",
		lr->num_lines);

	वापस 0;

out_put_unused_fd:
	put_unused_fd(fd);
out_मुक्त_linereq:
	linereq_मुक्त(lr);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_GPIO_CDEV_V1

/*
 * GPIO line event management
 */

/**
 * काष्ठा lineevent_state - contains the state of a userspace event
 * @gdev: the GPIO device the event pertains to
 * @label: consumer label used to tag descriptors
 * @desc: the GPIO descriptor held by this event
 * @eflags: the event flags this line was requested with
 * @irq: the पूर्णांकerrupt that trigger in response to events on this GPIO
 * @रुको: रुको queue that handles blocking पढ़ोs of events
 * @events: KFIFO क्रम the GPIO events
 * @बारtamp: cache क्रम the बारtamp storing it between hardirq
 * and IRQ thपढ़ो, used to bring the बारtamp बंद to the actual
 * event
 */
काष्ठा lineevent_state अणु
	काष्ठा gpio_device *gdev;
	स्थिर अक्षर *label;
	काष्ठा gpio_desc *desc;
	u32 eflags;
	पूर्णांक irq;
	रुको_queue_head_t रुको;
	DECLARE_KFIFO(events, काष्ठा gpioevent_data, 16);
	u64 बारtamp;
पूर्ण;

#घोषणा GPIOEVENT_REQUEST_VALID_FLAGS \
	(GPIOEVENT_REQUEST_RISING_EDGE | \
	GPIOEVENT_REQUEST_FALLING_EDGE)

अटल __poll_t lineevent_poll(काष्ठा file *file,
			       काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा lineevent_state *le = file->निजी_data;
	__poll_t events = 0;

	poll_रुको(file, &le->रुको, रुको);

	अगर (!kfअगरo_is_empty_spinlocked_noirqsave(&le->events, &le->रुको.lock))
		events = EPOLLIN | EPOLLRDNORM;

	वापस events;
पूर्ण

काष्ठा compat_gpioeevent_data अणु
	compat_u64	बारtamp;
	u32		id;
पूर्ण;

अटल sमाप_प्रकार lineevent_पढ़ो(काष्ठा file *file,
			      अक्षर __user *buf,
			      माप_प्रकार count,
			      loff_t *f_ps)
अणु
	काष्ठा lineevent_state *le = file->निजी_data;
	काष्ठा gpioevent_data ge;
	sमाप_प्रकार bytes_पढ़ो = 0;
	sमाप_प्रकार ge_size;
	पूर्णांक ret;

	/*
	 * When compatible प्रणाली call is being used the काष्ठा gpioevent_data,
	 * in हाल of at least ia32, has dअगरferent size due to the alignment
	 * dअगरferences. Because we have first member 64 bits followed by one of
	 * 32 bits there is no gap between them. The only dअगरference is the
	 * padding at the end of the data काष्ठाure. Hence, we calculate the
	 * actual माप() and pass this as an argument to copy_to_user() to
	 * drop unneeded bytes from the output.
	 */
	अगर (compat_need_64bit_alignment_fixup())
		ge_size = माप(काष्ठा compat_gpioeevent_data);
	अन्यथा
		ge_size = माप(काष्ठा gpioevent_data);
	अगर (count < ge_size)
		वापस -EINVAL;

	करो अणु
		spin_lock(&le->रुको.lock);
		अगर (kfअगरo_is_empty(&le->events)) अणु
			अगर (bytes_पढ़ो) अणु
				spin_unlock(&le->रुको.lock);
				वापस bytes_पढ़ो;
			पूर्ण

			अगर (file->f_flags & O_NONBLOCK) अणु
				spin_unlock(&le->रुको.lock);
				वापस -EAGAIN;
			पूर्ण

			ret = रुको_event_पूर्णांकerruptible_locked(le->रुको,
					!kfअगरo_is_empty(&le->events));
			अगर (ret) अणु
				spin_unlock(&le->रुको.lock);
				वापस ret;
			पूर्ण
		पूर्ण

		ret = kfअगरo_out(&le->events, &ge, 1);
		spin_unlock(&le->रुको.lock);
		अगर (ret != 1) अणु
			/*
			 * This should never happen - we were holding the lock
			 * from the moment we learned the fअगरo is no दीर्घer
			 * empty until now.
			 */
			ret = -EIO;
			अवरोध;
		पूर्ण

		अगर (copy_to_user(buf + bytes_पढ़ो, &ge, ge_size))
			वापस -EFAULT;
		bytes_पढ़ो += ge_size;
	पूर्ण जबतक (count >= bytes_पढ़ो + ge_size);

	वापस bytes_पढ़ो;
पूर्ण

अटल व्योम lineevent_मुक्त(काष्ठा lineevent_state *le)
अणु
	अगर (le->irq)
		मुक्त_irq(le->irq, le);
	अगर (le->desc)
		gpiod_मुक्त(le->desc);
	kमुक्त(le->label);
	put_device(&le->gdev->dev);
	kमुक्त(le);
पूर्ण

अटल पूर्णांक lineevent_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	lineevent_मुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल दीर्घ lineevent_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा lineevent_state *le = file->निजी_data;
	व्योम __user *ip = (व्योम __user *)arg;
	काष्ठा gpiohandle_data ghd;

	/*
	 * We can get the value क्रम an event line but not set it,
	 * because it is input by definition.
	 */
	अगर (cmd == GPIOHANDLE_GET_LINE_VALUES_IOCTL) अणु
		पूर्णांक val;

		स_रखो(&ghd, 0, माप(ghd));

		val = gpiod_get_value_cansleep(le->desc);
		अगर (val < 0)
			वापस val;
		ghd.values[0] = val;

		अगर (copy_to_user(ip, &ghd, माप(ghd)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ lineevent_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	वापस lineevent_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations lineevent_fileops = अणु
	.release = lineevent_release,
	.पढ़ो = lineevent_पढ़ो,
	.poll = lineevent_poll,
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
	.unlocked_ioctl = lineevent_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = lineevent_ioctl_compat,
#पूर्ण_अगर
पूर्ण;

अटल irqवापस_t lineevent_irq_thपढ़ो(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा lineevent_state *le = p;
	काष्ठा gpioevent_data ge;
	पूर्णांक ret;

	/* Do not leak kernel stack to userspace */
	स_रखो(&ge, 0, माप(ge));

	/*
	 * We may be running from a nested thपढ़ोed पूर्णांकerrupt in which हाल
	 * we didn't get the बारtamp from lineevent_irq_handler().
	 */
	अगर (!le->बारtamp)
		ge.बारtamp = kसमय_get_ns();
	अन्यथा
		ge.बारtamp = le->बारtamp;

	अगर (le->eflags & GPIOEVENT_REQUEST_RISING_EDGE
	    && le->eflags & GPIOEVENT_REQUEST_FALLING_EDGE) अणु
		पूर्णांक level = gpiod_get_value_cansleep(le->desc);

		अगर (level)
			/* Emit low-to-high event */
			ge.id = GPIOEVENT_EVENT_RISING_EDGE;
		अन्यथा
			/* Emit high-to-low event */
			ge.id = GPIOEVENT_EVENT_FALLING_EDGE;
	पूर्ण अन्यथा अगर (le->eflags & GPIOEVENT_REQUEST_RISING_EDGE) अणु
		/* Emit low-to-high event */
		ge.id = GPIOEVENT_EVENT_RISING_EDGE;
	पूर्ण अन्यथा अगर (le->eflags & GPIOEVENT_REQUEST_FALLING_EDGE) अणु
		/* Emit high-to-low event */
		ge.id = GPIOEVENT_EVENT_FALLING_EDGE;
	पूर्ण अन्यथा अणु
		वापस IRQ_NONE;
	पूर्ण

	ret = kfअगरo_in_spinlocked_noirqsave(&le->events, &ge,
					    1, &le->रुको.lock);
	अगर (ret)
		wake_up_poll(&le->रुको, EPOLLIN);
	अन्यथा
		pr_debug_ratelimited("event FIFO is full - event dropped\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t lineevent_irq_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा lineevent_state *le = p;

	/*
	 * Just store the बारtamp in hardirq context so we get it as
	 * बंद in समय as possible to the actual event.
	 */
	le->बारtamp = kसमय_get_ns();

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक lineevent_create(काष्ठा gpio_device *gdev, व्योम __user *ip)
अणु
	काष्ठा gpioevent_request eventreq;
	काष्ठा lineevent_state *le;
	काष्ठा gpio_desc *desc;
	काष्ठा file *file;
	u32 offset;
	u32 lflags;
	u32 eflags;
	पूर्णांक fd;
	पूर्णांक ret;
	पूर्णांक irq, irqflags = 0;

	अगर (copy_from_user(&eventreq, ip, माप(eventreq)))
		वापस -EFAULT;

	offset = eventreq.lineoffset;
	lflags = eventreq.handleflags;
	eflags = eventreq.eventflags;

	desc = gpiochip_get_desc(gdev->chip, offset);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	/* Return an error अगर a unknown flag is set */
	अगर ((lflags & ~GPIOHANDLE_REQUEST_VALID_FLAGS) ||
	    (eflags & ~GPIOEVENT_REQUEST_VALID_FLAGS))
		वापस -EINVAL;

	/* This is just wrong: we करोn't look क्रम events on output lines */
	अगर ((lflags & GPIOHANDLE_REQUEST_OUTPUT) ||
	    (lflags & GPIOHANDLE_REQUEST_OPEN_DRAIN) ||
	    (lflags & GPIOHANDLE_REQUEST_OPEN_SOURCE))
		वापस -EINVAL;

	/* Only one bias flag can be set. */
	अगर (((lflags & GPIOHANDLE_REQUEST_BIAS_DISABLE) &&
	     (lflags & (GPIOHANDLE_REQUEST_BIAS_PULL_DOWN |
			GPIOHANDLE_REQUEST_BIAS_PULL_UP))) ||
	    ((lflags & GPIOHANDLE_REQUEST_BIAS_PULL_DOWN) &&
	     (lflags & GPIOHANDLE_REQUEST_BIAS_PULL_UP)))
		वापस -EINVAL;

	le = kzalloc(माप(*le), GFP_KERNEL);
	अगर (!le)
		वापस -ENOMEM;
	le->gdev = gdev;
	get_device(&gdev->dev);

	अगर (eventreq.consumer_label[0] != '\0') अणु
		/* label is only initialized अगर consumer_label is set */
		le->label = kstrndup(eventreq.consumer_label,
				     माप(eventreq.consumer_label) - 1,
				     GFP_KERNEL);
		अगर (!le->label) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_le;
		पूर्ण
	पूर्ण

	ret = gpiod_request(desc, le->label);
	अगर (ret)
		जाओ out_मुक्त_le;
	le->desc = desc;
	le->eflags = eflags;

	linehandle_flags_to_desc_flags(lflags, &desc->flags);

	ret = gpiod_direction_input(desc);
	अगर (ret)
		जाओ out_मुक्त_le;

	blocking_notअगरier_call_chain(&desc->gdev->notअगरier,
				     GPIO_V2_LINE_CHANGED_REQUESTED, desc);

	irq = gpiod_to_irq(desc);
	अगर (irq <= 0) अणु
		ret = -ENODEV;
		जाओ out_मुक्त_le;
	पूर्ण
	le->irq = irq;

	अगर (eflags & GPIOEVENT_REQUEST_RISING_EDGE)
		irqflags |= test_bit(FLAG_ACTIVE_LOW, &desc->flags) ?
			IRQF_TRIGGER_FALLING : IRQF_TRIGGER_RISING;
	अगर (eflags & GPIOEVENT_REQUEST_FALLING_EDGE)
		irqflags |= test_bit(FLAG_ACTIVE_LOW, &desc->flags) ?
			IRQF_TRIGGER_RISING : IRQF_TRIGGER_FALLING;
	irqflags |= IRQF_ONESHOT;

	INIT_KFIFO(le->events);
	init_रुकोqueue_head(&le->रुको);

	/* Request a thपढ़ो to पढ़ो the events */
	ret = request_thपढ़ोed_irq(le->irq,
				   lineevent_irq_handler,
				   lineevent_irq_thपढ़ो,
				   irqflags,
				   le->label,
				   le);
	अगर (ret)
		जाओ out_मुक्त_le;

	fd = get_unused_fd_flags(O_RDONLY | O_CLOEXEC);
	अगर (fd < 0) अणु
		ret = fd;
		जाओ out_मुक्त_le;
	पूर्ण

	file = anon_inode_getfile("gpio-event",
				  &lineevent_fileops,
				  le,
				  O_RDONLY | O_CLOEXEC);
	अगर (IS_ERR(file)) अणु
		ret = PTR_ERR(file);
		जाओ out_put_unused_fd;
	पूर्ण

	eventreq.fd = fd;
	अगर (copy_to_user(ip, &eventreq, माप(eventreq))) अणु
		/*
		 * fput() will trigger the release() callback, so करो not go onto
		 * the regular error cleanup path here.
		 */
		fput(file);
		put_unused_fd(fd);
		वापस -EFAULT;
	पूर्ण

	fd_install(fd, file);

	वापस 0;

out_put_unused_fd:
	put_unused_fd(fd);
out_मुक्त_le:
	lineevent_मुक्त(le);
	वापस ret;
पूर्ण

अटल व्योम gpio_v2_line_info_to_v1(काष्ठा gpio_v2_line_info *info_v2,
				    काष्ठा gpioline_info *info_v1)
अणु
	u64 flagsv2 = info_v2->flags;

	स_नकल(info_v1->name, info_v2->name, माप(info_v1->name));
	स_नकल(info_v1->consumer, info_v2->consumer, माप(info_v1->consumer));
	info_v1->line_offset = info_v2->offset;
	info_v1->flags = 0;

	अगर (flagsv2 & GPIO_V2_LINE_FLAG_USED)
		info_v1->flags |= GPIOLINE_FLAG_KERNEL;

	अगर (flagsv2 & GPIO_V2_LINE_FLAG_OUTPUT)
		info_v1->flags |= GPIOLINE_FLAG_IS_OUT;

	अगर (flagsv2 & GPIO_V2_LINE_FLAG_ACTIVE_LOW)
		info_v1->flags |= GPIOLINE_FLAG_ACTIVE_LOW;

	अगर (flagsv2 & GPIO_V2_LINE_FLAG_OPEN_DRAIN)
		info_v1->flags |= GPIOLINE_FLAG_OPEN_DRAIN;
	अगर (flagsv2 & GPIO_V2_LINE_FLAG_OPEN_SOURCE)
		info_v1->flags |= GPIOLINE_FLAG_OPEN_SOURCE;

	अगर (flagsv2 & GPIO_V2_LINE_FLAG_BIAS_PULL_UP)
		info_v1->flags |= GPIOLINE_FLAG_BIAS_PULL_UP;
	अगर (flagsv2 & GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN)
		info_v1->flags |= GPIOLINE_FLAG_BIAS_PULL_DOWN;
	अगर (flagsv2 & GPIO_V2_LINE_FLAG_BIAS_DISABLED)
		info_v1->flags |= GPIOLINE_FLAG_BIAS_DISABLE;
पूर्ण

अटल व्योम gpio_v2_line_info_changed_to_v1(
		काष्ठा gpio_v2_line_info_changed *lic_v2,
		काष्ठा gpioline_info_changed *lic_v1)
अणु
	gpio_v2_line_info_to_v1(&lic_v2->info, &lic_v1->info);
	lic_v1->बारtamp = lic_v2->बारtamp_ns;
	lic_v1->event_type = lic_v2->event_type;
पूर्ण

#पूर्ण_अगर /* CONFIG_GPIO_CDEV_V1 */

अटल व्योम gpio_desc_to_lineinfo(काष्ठा gpio_desc *desc,
				  काष्ठा gpio_v2_line_info *info)
अणु
	काष्ठा gpio_chip *gc = desc->gdev->chip;
	bool ok_क्रम_pinctrl;
	अचिन्हित दीर्घ flags;
	u32 debounce_period_us;
	अचिन्हित पूर्णांक num_attrs = 0;

	स_रखो(info, 0, माप(*info));
	info->offset = gpio_chip_hwgpio(desc);

	/*
	 * This function takes a mutex so we must check this beक्रमe taking
	 * the spinlock.
	 *
	 * FIXME: find a non-racy way to retrieve this inक्रमmation. Maybe a
	 * lock common to both frameworks?
	 */
	ok_क्रम_pinctrl =
		pinctrl_gpio_can_use_line(gc->base + info->offset);

	spin_lock_irqsave(&gpio_lock, flags);

	अगर (desc->name)
		strscpy(info->name, desc->name, माप(info->name));

	अगर (desc->label)
		strscpy(info->consumer, desc->label, माप(info->consumer));

	/*
	 * Userspace only need to know that the kernel is using this GPIO so
	 * it can't use it.
	 */
	info->flags = 0;
	अगर (test_bit(FLAG_REQUESTED, &desc->flags) ||
	    test_bit(FLAG_IS_HOGGED, &desc->flags) ||
	    test_bit(FLAG_USED_AS_IRQ, &desc->flags) ||
	    test_bit(FLAG_EXPORT, &desc->flags) ||
	    test_bit(FLAG_SYSFS, &desc->flags) ||
	    !gpiochip_line_is_valid(gc, info->offset) ||
	    !ok_क्रम_pinctrl)
		info->flags |= GPIO_V2_LINE_FLAG_USED;

	अगर (test_bit(FLAG_IS_OUT, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_OUTPUT;
	अन्यथा
		info->flags |= GPIO_V2_LINE_FLAG_INPUT;

	अगर (test_bit(FLAG_ACTIVE_LOW, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_ACTIVE_LOW;

	अगर (test_bit(FLAG_OPEN_DRAIN, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_OPEN_DRAIN;
	अगर (test_bit(FLAG_OPEN_SOURCE, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_OPEN_SOURCE;

	अगर (test_bit(FLAG_BIAS_DISABLE, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_BIAS_DISABLED;
	अगर (test_bit(FLAG_PULL_DOWN, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN;
	अगर (test_bit(FLAG_PULL_UP, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_BIAS_PULL_UP;

	अगर (test_bit(FLAG_EDGE_RISING, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_EDGE_RISING;
	अगर (test_bit(FLAG_EDGE_FALLING, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_EDGE_FALLING;

	अगर (test_bit(FLAG_EVENT_CLOCK_REALTIME, &desc->flags))
		info->flags |= GPIO_V2_LINE_FLAG_EVENT_CLOCK_REALTIME;

	debounce_period_us = READ_ONCE(desc->debounce_period_us);
	अगर (debounce_period_us) अणु
		info->attrs[num_attrs].id = GPIO_V2_LINE_ATTR_ID_DEBOUNCE;
		info->attrs[num_attrs].debounce_period_us = debounce_period_us;
		num_attrs++;
	पूर्ण
	info->num_attrs = num_attrs;

	spin_unlock_irqrestore(&gpio_lock, flags);
पूर्ण

काष्ठा gpio_अक्षरdev_data अणु
	काष्ठा gpio_device *gdev;
	रुको_queue_head_t रुको;
	DECLARE_KFIFO(events, काष्ठा gpio_v2_line_info_changed, 32);
	काष्ठा notअगरier_block lineinfo_changed_nb;
	अचिन्हित दीर्घ *watched_lines;
#अगर_घोषित CONFIG_GPIO_CDEV_V1
	atomic_t watch_abi_version;
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक chipinfo_get(काष्ठा gpio_अक्षरdev_data *cdev, व्योम __user *ip)
अणु
	काष्ठा gpio_device *gdev = cdev->gdev;
	काष्ठा gpiochip_info chipinfo;

	स_रखो(&chipinfo, 0, माप(chipinfo));

	strscpy(chipinfo.name, dev_name(&gdev->dev), माप(chipinfo.name));
	strscpy(chipinfo.label, gdev->label, माप(chipinfo.label));
	chipinfo.lines = gdev->ngpio;
	अगर (copy_to_user(ip, &chipinfo, माप(chipinfo)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_GPIO_CDEV_V1
/*
 * वापसs 0 अगर the versions match, अन्यथा the previously selected ABI version
 */
अटल पूर्णांक lineinfo_ensure_abi_version(काष्ठा gpio_अक्षरdev_data *cdata,
				       अचिन्हित पूर्णांक version)
अणु
	पूर्णांक abiv = atomic_cmpxchg(&cdata->watch_abi_version, 0, version);

	अगर (abiv == version)
		वापस 0;

	वापस abiv;
पूर्ण

अटल पूर्णांक lineinfo_get_v1(काष्ठा gpio_अक्षरdev_data *cdev, व्योम __user *ip,
			   bool watch)
अणु
	काष्ठा gpio_desc *desc;
	काष्ठा gpioline_info lineinfo;
	काष्ठा gpio_v2_line_info lineinfo_v2;

	अगर (copy_from_user(&lineinfo, ip, माप(lineinfo)))
		वापस -EFAULT;

	/* this द्विगुनs as a range check on line_offset */
	desc = gpiochip_get_desc(cdev->gdev->chip, lineinfo.line_offset);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	अगर (watch) अणु
		अगर (lineinfo_ensure_abi_version(cdev, 1))
			वापस -EPERM;

		अगर (test_and_set_bit(lineinfo.line_offset, cdev->watched_lines))
			वापस -EBUSY;
	पूर्ण

	gpio_desc_to_lineinfo(desc, &lineinfo_v2);
	gpio_v2_line_info_to_v1(&lineinfo_v2, &lineinfo);

	अगर (copy_to_user(ip, &lineinfo, माप(lineinfo))) अणु
		अगर (watch)
			clear_bit(lineinfo.line_offset, cdev->watched_lines);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lineinfo_get(काष्ठा gpio_अक्षरdev_data *cdev, व्योम __user *ip,
			bool watch)
अणु
	काष्ठा gpio_desc *desc;
	काष्ठा gpio_v2_line_info lineinfo;

	अगर (copy_from_user(&lineinfo, ip, माप(lineinfo)))
		वापस -EFAULT;

	अगर (स_प्रथम_inv(lineinfo.padding, 0, माप(lineinfo.padding)))
		वापस -EINVAL;

	desc = gpiochip_get_desc(cdev->gdev->chip, lineinfo.offset);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	अगर (watch) अणु
#अगर_घोषित CONFIG_GPIO_CDEV_V1
		अगर (lineinfo_ensure_abi_version(cdev, 2))
			वापस -EPERM;
#पूर्ण_अगर
		अगर (test_and_set_bit(lineinfo.offset, cdev->watched_lines))
			वापस -EBUSY;
	पूर्ण
	gpio_desc_to_lineinfo(desc, &lineinfo);

	अगर (copy_to_user(ip, &lineinfo, माप(lineinfo))) अणु
		अगर (watch)
			clear_bit(lineinfo.offset, cdev->watched_lines);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lineinfo_unwatch(काष्ठा gpio_अक्षरdev_data *cdev, व्योम __user *ip)
अणु
	__u32 offset;

	अगर (copy_from_user(&offset, ip, माप(offset)))
		वापस -EFAULT;

	अगर (offset >= cdev->gdev->ngpio)
		वापस -EINVAL;

	अगर (!test_and_clear_bit(offset, cdev->watched_lines))
		वापस -EBUSY;

	वापस 0;
पूर्ण

/*
 * gpio_ioctl() - ioctl handler क्रम the GPIO अक्षरdev
 */
अटल दीर्घ gpio_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा gpio_अक्षरdev_data *cdev = file->निजी_data;
	काष्ठा gpio_device *gdev = cdev->gdev;
	व्योम __user *ip = (व्योम __user *)arg;

	/* We fail any subsequent ioctl():s when the chip is gone */
	अगर (!gdev->chip)
		वापस -ENODEV;

	/* Fill in the काष्ठा and pass to userspace */
	अगर (cmd == GPIO_GET_CHIPINFO_IOCTL) अणु
		वापस chipinfo_get(cdev, ip);
#अगर_घोषित CONFIG_GPIO_CDEV_V1
	पूर्ण अन्यथा अगर (cmd == GPIO_GET_LINEHANDLE_IOCTL) अणु
		वापस linehandle_create(gdev, ip);
	पूर्ण अन्यथा अगर (cmd == GPIO_GET_LINEEVENT_IOCTL) अणु
		वापस lineevent_create(gdev, ip);
	पूर्ण अन्यथा अगर (cmd == GPIO_GET_LINEINFO_IOCTL ||
		   cmd == GPIO_GET_LINEINFO_WATCH_IOCTL) अणु
		वापस lineinfo_get_v1(cdev, ip,
				       cmd == GPIO_GET_LINEINFO_WATCH_IOCTL);
#पूर्ण_अगर /* CONFIG_GPIO_CDEV_V1 */
	पूर्ण अन्यथा अगर (cmd == GPIO_V2_GET_LINEINFO_IOCTL ||
		   cmd == GPIO_V2_GET_LINEINFO_WATCH_IOCTL) अणु
		वापस lineinfo_get(cdev, ip,
				    cmd == GPIO_V2_GET_LINEINFO_WATCH_IOCTL);
	पूर्ण अन्यथा अगर (cmd == GPIO_V2_GET_LINE_IOCTL) अणु
		वापस linereq_create(gdev, ip);
	पूर्ण अन्यथा अगर (cmd == GPIO_GET_LINEINFO_UNWATCH_IOCTL) अणु
		वापस lineinfo_unwatch(cdev, ip);
	पूर्ण
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ gpio_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	वापस gpio_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा gpio_अक्षरdev_data *
to_gpio_अक्षरdev_data(काष्ठा notअगरier_block *nb)
अणु
	वापस container_of(nb, काष्ठा gpio_अक्षरdev_data, lineinfo_changed_nb);
पूर्ण

अटल पूर्णांक lineinfo_changed_notअगरy(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा gpio_अक्षरdev_data *cdev = to_gpio_अक्षरdev_data(nb);
	काष्ठा gpio_v2_line_info_changed chg;
	काष्ठा gpio_desc *desc = data;
	पूर्णांक ret;

	अगर (!test_bit(gpio_chip_hwgpio(desc), cdev->watched_lines))
		वापस NOTIFY_DONE;

	स_रखो(&chg, 0, माप(chg));
	chg.event_type = action;
	chg.बारtamp_ns = kसमय_get_ns();
	gpio_desc_to_lineinfo(desc, &chg.info);

	ret = kfअगरo_in_spinlocked(&cdev->events, &chg, 1, &cdev->रुको.lock);
	अगर (ret)
		wake_up_poll(&cdev->रुको, EPOLLIN);
	अन्यथा
		pr_debug_ratelimited("lineinfo event FIFO is full - event dropped\n");

	वापस NOTIFY_OK;
पूर्ण

अटल __poll_t lineinfo_watch_poll(काष्ठा file *file,
				    काष्ठा poll_table_काष्ठा *pollt)
अणु
	काष्ठा gpio_अक्षरdev_data *cdev = file->निजी_data;
	__poll_t events = 0;

	poll_रुको(file, &cdev->रुको, pollt);

	अगर (!kfअगरo_is_empty_spinlocked_noirqsave(&cdev->events,
						 &cdev->रुको.lock))
		events = EPOLLIN | EPOLLRDNORM;

	वापस events;
पूर्ण

अटल sमाप_प्रकार lineinfo_watch_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *off)
अणु
	काष्ठा gpio_अक्षरdev_data *cdev = file->निजी_data;
	काष्ठा gpio_v2_line_info_changed event;
	sमाप_प्रकार bytes_पढ़ो = 0;
	पूर्णांक ret;
	माप_प्रकार event_size;

#अगर_अघोषित CONFIG_GPIO_CDEV_V1
	event_size = माप(काष्ठा gpio_v2_line_info_changed);
	अगर (count < event_size)
		वापस -EINVAL;
#पूर्ण_अगर

	करो अणु
		spin_lock(&cdev->रुको.lock);
		अगर (kfअगरo_is_empty(&cdev->events)) अणु
			अगर (bytes_पढ़ो) अणु
				spin_unlock(&cdev->रुको.lock);
				वापस bytes_पढ़ो;
			पूर्ण

			अगर (file->f_flags & O_NONBLOCK) अणु
				spin_unlock(&cdev->रुको.lock);
				वापस -EAGAIN;
			पूर्ण

			ret = रुको_event_पूर्णांकerruptible_locked(cdev->रुको,
					!kfअगरo_is_empty(&cdev->events));
			अगर (ret) अणु
				spin_unlock(&cdev->रुको.lock);
				वापस ret;
			पूर्ण
		पूर्ण
#अगर_घोषित CONFIG_GPIO_CDEV_V1
		/* must be after kfअगरo check so watch_abi_version is set */
		अगर (atomic_पढ़ो(&cdev->watch_abi_version) == 2)
			event_size = माप(काष्ठा gpio_v2_line_info_changed);
		अन्यथा
			event_size = माप(काष्ठा gpioline_info_changed);
		अगर (count < event_size) अणु
			spin_unlock(&cdev->रुको.lock);
			वापस -EINVAL;
		पूर्ण
#पूर्ण_अगर
		ret = kfअगरo_out(&cdev->events, &event, 1);
		spin_unlock(&cdev->रुको.lock);
		अगर (ret != 1) अणु
			ret = -EIO;
			अवरोध;
			/* We should never get here. See lineevent_पढ़ो(). */
		पूर्ण

#अगर_घोषित CONFIG_GPIO_CDEV_V1
		अगर (event_size == माप(काष्ठा gpio_v2_line_info_changed)) अणु
			अगर (copy_to_user(buf + bytes_पढ़ो, &event, event_size))
				वापस -EFAULT;
		पूर्ण अन्यथा अणु
			काष्ठा gpioline_info_changed event_v1;

			gpio_v2_line_info_changed_to_v1(&event, &event_v1);
			अगर (copy_to_user(buf + bytes_पढ़ो, &event_v1,
					 event_size))
				वापस -EFAULT;
		पूर्ण
#अन्यथा
		अगर (copy_to_user(buf + bytes_पढ़ो, &event, event_size))
			वापस -EFAULT;
#पूर्ण_अगर
		bytes_पढ़ो += event_size;
	पूर्ण जबतक (count >= bytes_पढ़ो + माप(event));

	वापस bytes_पढ़ो;
पूर्ण

/**
 * gpio_chrdev_खोलो() - खोलो the अक्षरdev क्रम ioctl operations
 * @inode: inode क्रम this अक्षरdev
 * @file: file काष्ठा क्रम storing निजी data
 * Returns 0 on success
 */
अटल पूर्णांक gpio_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gpio_device *gdev = container_of(inode->i_cdev,
						काष्ठा gpio_device, chrdev);
	काष्ठा gpio_अक्षरdev_data *cdev;
	पूर्णांक ret = -ENOMEM;

	/* Fail on खोलो अगर the backing gpiochip is gone */
	अगर (!gdev->chip)
		वापस -ENODEV;

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस -ENOMEM;

	cdev->watched_lines = biपंचांगap_zalloc(gdev->chip->ngpio, GFP_KERNEL);
	अगर (!cdev->watched_lines)
		जाओ out_मुक्त_cdev;

	init_रुकोqueue_head(&cdev->रुको);
	INIT_KFIFO(cdev->events);
	cdev->gdev = gdev;

	cdev->lineinfo_changed_nb.notअगरier_call = lineinfo_changed_notअगरy;
	ret = blocking_notअगरier_chain_रेजिस्टर(&gdev->notअगरier,
					       &cdev->lineinfo_changed_nb);
	अगर (ret)
		जाओ out_मुक्त_biपंचांगap;

	get_device(&gdev->dev);
	file->निजी_data = cdev;

	ret = nonseekable_खोलो(inode, file);
	अगर (ret)
		जाओ out_unरेजिस्टर_notअगरier;

	वापस ret;

out_unरेजिस्टर_notअगरier:
	blocking_notअगरier_chain_unरेजिस्टर(&gdev->notअगरier,
					   &cdev->lineinfo_changed_nb);
out_मुक्त_biपंचांगap:
	biपंचांगap_मुक्त(cdev->watched_lines);
out_मुक्त_cdev:
	kमुक्त(cdev);
	वापस ret;
पूर्ण

/**
 * gpio_chrdev_release() - बंद अक्षरdev after ioctl operations
 * @inode: inode क्रम this अक्षरdev
 * @file: file काष्ठा क्रम storing निजी data
 * Returns 0 on success
 */
अटल पूर्णांक gpio_chrdev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gpio_अक्षरdev_data *cdev = file->निजी_data;
	काष्ठा gpio_device *gdev = cdev->gdev;

	biपंचांगap_मुक्त(cdev->watched_lines);
	blocking_notअगरier_chain_unरेजिस्टर(&gdev->notअगरier,
					   &cdev->lineinfo_changed_nb);
	put_device(&gdev->dev);
	kमुक्त(cdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations gpio_fileops = अणु
	.release = gpio_chrdev_release,
	.खोलो = gpio_chrdev_खोलो,
	.poll = lineinfo_watch_poll,
	.पढ़ो = lineinfo_watch_पढ़ो,
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.unlocked_ioctl = gpio_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = gpio_ioctl_compat,
#पूर्ण_अगर
पूर्ण;

पूर्णांक gpiolib_cdev_रेजिस्टर(काष्ठा gpio_device *gdev, dev_t devt)
अणु
	पूर्णांक ret;

	cdev_init(&gdev->chrdev, &gpio_fileops);
	gdev->chrdev.owner = THIS_MODULE;
	gdev->dev.devt = MKDEV(MAJOR(devt), gdev->id);

	ret = cdev_device_add(&gdev->chrdev, &gdev->dev);
	अगर (ret)
		वापस ret;

	chip_dbg(gdev->chip, "added GPIO chardev (%d:%d)\n",
		 MAJOR(devt), gdev->id);

	वापस 0;
पूर्ण

व्योम gpiolib_cdev_unरेजिस्टर(काष्ठा gpio_device *gdev)
अणु
	cdev_device_del(&gdev->chrdev, &gdev->dev);
पूर्ण
