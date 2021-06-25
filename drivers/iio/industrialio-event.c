<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Industrial I/O event handling
 *
 * Copyright (c) 2008 Jonathan Cameron
 *
 * Based on elements of hwmon and input subप्रणालीs.
 */

#समावेश <linux/anon_inodes.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/iio-opaque.h>
#समावेश "iio_core.h"
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

/**
 * काष्ठा iio_event_पूर्णांकerface - chrdev पूर्णांकerface क्रम an event line
 * @रुको:		रुको queue to allow blocking पढ़ोs of events
 * @det_events:		list of detected events
 * @dev_attr_list:	list of event पूर्णांकerface sysfs attribute
 * @flags:		file operations related flags including busy flag.
 * @group:		event पूर्णांकerface sysfs attribute group
 * @पढ़ो_lock:		lock to protect kfअगरo पढ़ो operations
 * @ioctl_handler:	handler क्रम event ioctl() calls
 */
काष्ठा iio_event_पूर्णांकerface अणु
	रुको_queue_head_t	रुको;
	DECLARE_KFIFO(det_events, काष्ठा iio_event_data, 16);

	काष्ठा list_head	dev_attr_list;
	अचिन्हित दीर्घ		flags;
	काष्ठा attribute_group	group;
	काष्ठा mutex		पढ़ो_lock;
	काष्ठा iio_ioctl_handler	ioctl_handler;
पूर्ण;

bool iio_event_enabled(स्थिर काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक)
अणु
	वापस !!test_bit(IIO_BUSY_BIT_POS, &ev_पूर्णांक->flags);
पूर्ण

/**
 * iio_push_event() - try to add event to the list क्रम userspace पढ़ोing
 * @indio_dev:		IIO device काष्ठाure
 * @ev_code:		What event
 * @बारtamp:		When the event occurred
 *
 * Note: The caller must make sure that this function is not running
 * concurrently क्रम the same indio_dev more than once.
 *
 * This function may be safely used as soon as a valid reference to iio_dev has
 * been obtained via iio_device_alloc(), but any events that are submitted
 * beक्रमe iio_device_रेजिस्टर() has successfully completed will be silently
 * discarded.
 **/
पूर्णांक iio_push_event(काष्ठा iio_dev *indio_dev, u64 ev_code, s64 बारtamp)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक = iio_dev_opaque->event_पूर्णांकerface;
	काष्ठा iio_event_data ev;
	पूर्णांक copied;

	अगर (!ev_पूर्णांक)
		वापस 0;

	/* Does anyone care? */
	अगर (iio_event_enabled(ev_पूर्णांक)) अणु

		ev.id = ev_code;
		ev.बारtamp = बारtamp;

		copied = kfअगरo_put(&ev_पूर्णांक->det_events, ev);
		अगर (copied != 0)
			wake_up_poll(&ev_पूर्णांक->रुको, EPOLLIN);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iio_push_event);

/**
 * iio_event_poll() - poll the event queue to find out अगर it has data
 * @filep:	File काष्ठाure poपूर्णांकer to identअगरy the device
 * @रुको:	Poll table poपूर्णांकer to add the रुको queue on
 *
 * Return: (EPOLLIN | EPOLLRDNORM) अगर data is available क्रम पढ़ोing
 *	   or a negative error code on failure
 */
अटल __poll_t iio_event_poll(काष्ठा file *filep,
			     काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा iio_dev *indio_dev = filep->निजी_data;
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक = iio_dev_opaque->event_पूर्णांकerface;
	__poll_t events = 0;

	अगर (!indio_dev->info)
		वापस events;

	poll_रुको(filep, &ev_पूर्णांक->रुको, रुको);

	अगर (!kfअगरo_is_empty(&ev_पूर्णांक->det_events))
		events = EPOLLIN | EPOLLRDNORM;

	वापस events;
पूर्ण

अटल sमाप_प्रकार iio_event_chrdev_पढ़ो(काष्ठा file *filep,
				     अक्षर __user *buf,
				     माप_प्रकार count,
				     loff_t *f_ps)
अणु
	काष्ठा iio_dev *indio_dev = filep->निजी_data;
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक = iio_dev_opaque->event_पूर्णांकerface;
	अचिन्हित पूर्णांक copied;
	पूर्णांक ret;

	अगर (!indio_dev->info)
		वापस -ENODEV;

	अगर (count < माप(काष्ठा iio_event_data))
		वापस -EINVAL;

	करो अणु
		अगर (kfअगरo_is_empty(&ev_पूर्णांक->det_events)) अणु
			अगर (filep->f_flags & O_NONBLOCK)
				वापस -EAGAIN;

			ret = रुको_event_पूर्णांकerruptible(ev_पूर्णांक->रुको,
					!kfअगरo_is_empty(&ev_पूर्णांक->det_events) ||
					indio_dev->info == शून्य);
			अगर (ret)
				वापस ret;
			अगर (indio_dev->info == शून्य)
				वापस -ENODEV;
		पूर्ण

		अगर (mutex_lock_पूर्णांकerruptible(&ev_पूर्णांक->पढ़ो_lock))
			वापस -ERESTARTSYS;
		ret = kfअगरo_to_user(&ev_पूर्णांक->det_events, buf, count, &copied);
		mutex_unlock(&ev_पूर्णांक->पढ़ो_lock);

		अगर (ret)
			वापस ret;

		/*
		 * If we couldn't पढ़ो anything from the fअगरo (a dअगरferent
		 * thपढ़ो might have been faster) we either वापस -EAGAIN अगर
		 * the file descriptor is non-blocking, otherwise we go back to
		 * sleep and रुको क्रम more data to arrive.
		 */
		अगर (copied == 0 && (filep->f_flags & O_NONBLOCK))
			वापस -EAGAIN;

	पूर्ण जबतक (copied == 0);

	वापस copied;
पूर्ण

अटल पूर्णांक iio_event_chrdev_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा iio_dev *indio_dev = filep->निजी_data;
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक = iio_dev_opaque->event_पूर्णांकerface;

	clear_bit(IIO_BUSY_BIT_POS, &ev_पूर्णांक->flags);

	iio_device_put(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations iio_event_chrdev_fileops = अणु
	.पढ़ो =  iio_event_chrdev_पढ़ो,
	.poll =  iio_event_poll,
	.release = iio_event_chrdev_release,
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
पूर्ण;

अटल पूर्णांक iio_event_getfd(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक = iio_dev_opaque->event_पूर्णांकerface;
	पूर्णांक fd;

	अगर (ev_पूर्णांक == शून्य)
		वापस -ENODEV;

	fd = mutex_lock_पूर्णांकerruptible(&indio_dev->mlock);
	अगर (fd)
		वापस fd;

	अगर (test_and_set_bit(IIO_BUSY_BIT_POS, &ev_पूर्णांक->flags)) अणु
		fd = -EBUSY;
		जाओ unlock;
	पूर्ण

	iio_device_get(indio_dev);

	fd = anon_inode_getfd("iio:event", &iio_event_chrdev_fileops,
				indio_dev, O_RDONLY | O_CLOEXEC);
	अगर (fd < 0) अणु
		clear_bit(IIO_BUSY_BIT_POS, &ev_पूर्णांक->flags);
		iio_device_put(indio_dev);
	पूर्ण अन्यथा अणु
		kfअगरo_reset_out(&ev_पूर्णांक->det_events);
	पूर्ण

unlock:
	mutex_unlock(&indio_dev->mlock);
	वापस fd;
पूर्ण

अटल स्थिर अक्षर * स्थिर iio_ev_type_text[] = अणु
	[IIO_EV_TYPE_THRESH] = "thresh",
	[IIO_EV_TYPE_MAG] = "mag",
	[IIO_EV_TYPE_ROC] = "roc",
	[IIO_EV_TYPE_THRESH_ADAPTIVE] = "thresh_adaptive",
	[IIO_EV_TYPE_MAG_ADAPTIVE] = "mag_adaptive",
	[IIO_EV_TYPE_CHANGE] = "change",
पूर्ण;

अटल स्थिर अक्षर * स्थिर iio_ev_dir_text[] = अणु
	[IIO_EV_सूची_EITHER] = "either",
	[IIO_EV_सूची_RISING] = "rising",
	[IIO_EV_सूची_FALLING] = "falling"
पूर्ण;

अटल स्थिर अक्षर * स्थिर iio_ev_info_text[] = अणु
	[IIO_EV_INFO_ENABLE] = "en",
	[IIO_EV_INFO_VALUE] = "value",
	[IIO_EV_INFO_HYSTERESIS] = "hysteresis",
	[IIO_EV_INFO_PERIOD] = "period",
	[IIO_EV_INFO_HIGH_PASS_FILTER_3DB] = "high_pass_filter_3db",
	[IIO_EV_INFO_LOW_PASS_FILTER_3DB] = "low_pass_filter_3db",
	[IIO_EV_INFO_TIMEOUT] = "timeout",
पूर्ण;

अटल क्रमागत iio_event_direction iio_ev_attr_dir(काष्ठा iio_dev_attr *attr)
अणु
	वापस attr->c->event_spec[attr->address & 0xffff].dir;
पूर्ण

अटल क्रमागत iio_event_type iio_ev_attr_type(काष्ठा iio_dev_attr *attr)
अणु
	वापस attr->c->event_spec[attr->address & 0xffff].type;
पूर्ण

अटल क्रमागत iio_event_info iio_ev_attr_info(काष्ठा iio_dev_attr *attr)
अणु
	वापस (attr->address >> 16) & 0xffff;
पूर्ण

अटल sमाप_प्रकार iio_ev_state_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf,
				  माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक ret;
	bool val;

	ret = strtobool(buf, &val);
	अगर (ret < 0)
		वापस ret;

	ret = indio_dev->info->ग_लिखो_event_config(indio_dev,
		this_attr->c, iio_ev_attr_type(this_attr),
		iio_ev_attr_dir(this_attr), val);

	वापस (ret < 0) ? ret : len;
पूर्ण

अटल sमाप_प्रकार iio_ev_state_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक val;

	val = indio_dev->info->पढ़ो_event_config(indio_dev,
		this_attr->c, iio_ev_attr_type(this_attr),
		iio_ev_attr_dir(this_attr));
	अगर (val < 0)
		वापस val;
	अन्यथा
		वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार iio_ev_value_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक val, val2, val_arr[2];
	पूर्णांक ret;

	ret = indio_dev->info->पढ़ो_event_value(indio_dev,
		this_attr->c, iio_ev_attr_type(this_attr),
		iio_ev_attr_dir(this_attr), iio_ev_attr_info(this_attr),
		&val, &val2);
	अगर (ret < 0)
		वापस ret;
	val_arr[0] = val;
	val_arr[1] = val2;
	वापस iio_क्रमmat_value(buf, ret, 2, val_arr);
पूर्ण

अटल sमाप_प्रकार iio_ev_value_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf,
				  माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक val, val2;
	पूर्णांक ret;

	अगर (!indio_dev->info->ग_लिखो_event_value)
		वापस -EINVAL;

	ret = iio_str_to_fixpoपूर्णांक(buf, 100000, &val, &val2);
	अगर (ret)
		वापस ret;
	ret = indio_dev->info->ग_लिखो_event_value(indio_dev,
		this_attr->c, iio_ev_attr_type(this_attr),
		iio_ev_attr_dir(this_attr), iio_ev_attr_info(this_attr),
		val, val2);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल पूर्णांक iio_device_add_event(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक spec_index,
	क्रमागत iio_event_type type, क्रमागत iio_event_direction dir,
	क्रमागत iio_shared_by shared_by, स्थिर अचिन्हित दीर्घ *mask)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	sमाप_प्रकार (*show)(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा device *, काष्ठा device_attribute *,
		स्थिर अक्षर *, माप_प्रकार);
	अचिन्हित पूर्णांक attrcount = 0;
	अचिन्हित पूर्णांक i;
	अक्षर *postfix;
	पूर्णांक ret;

	क्रम_each_set_bit(i, mask, माप(*mask)*8) अणु
		अगर (i >= ARRAY_SIZE(iio_ev_info_text))
			वापस -EINVAL;
		अगर (dir != IIO_EV_सूची_NONE)
			postfix = kaप्र_लिखो(GFP_KERNEL, "%s_%s_%s",
					iio_ev_type_text[type],
					iio_ev_dir_text[dir],
					iio_ev_info_text[i]);
		अन्यथा
			postfix = kaप्र_लिखो(GFP_KERNEL, "%s_%s",
					iio_ev_type_text[type],
					iio_ev_info_text[i]);
		अगर (postfix == शून्य)
			वापस -ENOMEM;

		अगर (i == IIO_EV_INFO_ENABLE) अणु
			show = iio_ev_state_show;
			store = iio_ev_state_store;
		पूर्ण अन्यथा अणु
			show = iio_ev_value_show;
			store = iio_ev_value_store;
		पूर्ण

		ret = __iio_add_chan_devattr(postfix, chan, show, store,
			 (i << 16) | spec_index, shared_by, &indio_dev->dev,
			 शून्य,
			&iio_dev_opaque->event_पूर्णांकerface->dev_attr_list);
		kमुक्त(postfix);

		अगर ((ret == -EBUSY) && (shared_by != IIO_SEPARATE))
			जारी;

		अगर (ret)
			वापस ret;

		attrcount++;
	पूर्ण

	वापस attrcount;
पूर्ण

अटल पूर्णांक iio_device_add_event_sysfs(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan)
अणु
	पूर्णांक ret = 0, i, attrcount = 0;
	क्रमागत iio_event_direction dir;
	क्रमागत iio_event_type type;

	क्रम (i = 0; i < chan->num_event_specs; i++) अणु
		type = chan->event_spec[i].type;
		dir = chan->event_spec[i].dir;

		ret = iio_device_add_event(indio_dev, chan, i, type, dir,
			IIO_SEPARATE, &chan->event_spec[i].mask_separate);
		अगर (ret < 0)
			वापस ret;
		attrcount += ret;

		ret = iio_device_add_event(indio_dev, chan, i, type, dir,
			IIO_SHARED_BY_TYPE,
			&chan->event_spec[i].mask_shared_by_type);
		अगर (ret < 0)
			वापस ret;
		attrcount += ret;

		ret = iio_device_add_event(indio_dev, chan, i, type, dir,
			IIO_SHARED_BY_सूची,
			&chan->event_spec[i].mask_shared_by_dir);
		अगर (ret < 0)
			वापस ret;
		attrcount += ret;

		ret = iio_device_add_event(indio_dev, chan, i, type, dir,
			IIO_SHARED_BY_ALL,
			&chan->event_spec[i].mask_shared_by_all);
		अगर (ret < 0)
			वापस ret;
		attrcount += ret;
	पूर्ण
	ret = attrcount;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __iio_add_event_config_attrs(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक j, ret, attrcount = 0;

	/* Dynamically created from the channels array */
	क्रम (j = 0; j < indio_dev->num_channels; j++) अणु
		ret = iio_device_add_event_sysfs(indio_dev,
						 &indio_dev->channels[j]);
		अगर (ret < 0)
			वापस ret;
		attrcount += ret;
	पूर्ण
	वापस attrcount;
पूर्ण

अटल bool iio_check_क्रम_dynamic_events(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < indio_dev->num_channels; j++) अणु
		अगर (indio_dev->channels[j].num_event_specs != 0)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम iio_setup_ev_पूर्णांक(काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक)
अणु
	INIT_KFIFO(ev_पूर्णांक->det_events);
	init_रुकोqueue_head(&ev_पूर्णांक->रुको);
	mutex_init(&ev_पूर्णांक->पढ़ो_lock);
पूर्ण

अटल दीर्घ iio_event_ioctl(काष्ठा iio_dev *indio_dev, काष्ठा file *filp,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक __user *ip = (पूर्णांक __user *)arg;
	पूर्णांक fd;

	अगर (cmd == IIO_GET_EVENT_FD_IOCTL) अणु
		fd = iio_event_getfd(indio_dev);
		अगर (fd < 0)
			वापस fd;
		अगर (copy_to_user(ip, &fd, माप(fd)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	वापस IIO_IOCTL_UNHANDLED;
पूर्ण

अटल स्थिर अक्षर *iio_event_group_name = "events";
पूर्णांक iio_device_रेजिस्टर_eventset(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक;
	काष्ठा iio_dev_attr *p;
	पूर्णांक ret = 0, attrcount_orig = 0, attrcount, attrn;
	काष्ठा attribute **attr;

	अगर (!(indio_dev->info->event_attrs ||
	      iio_check_क्रम_dynamic_events(indio_dev)))
		वापस 0;

	ev_पूर्णांक = kzalloc(माप(काष्ठा iio_event_पूर्णांकerface), GFP_KERNEL);
	अगर (ev_पूर्णांक == शून्य)
		वापस -ENOMEM;

	iio_dev_opaque->event_पूर्णांकerface = ev_पूर्णांक;

	INIT_LIST_HEAD(&ev_पूर्णांक->dev_attr_list);

	iio_setup_ev_पूर्णांक(ev_पूर्णांक);
	अगर (indio_dev->info->event_attrs != शून्य) अणु
		attr = indio_dev->info->event_attrs->attrs;
		जबतक (*attr++ != शून्य)
			attrcount_orig++;
	पूर्ण
	attrcount = attrcount_orig;
	अगर (indio_dev->channels) अणु
		ret = __iio_add_event_config_attrs(indio_dev);
		अगर (ret < 0)
			जाओ error_मुक्त_setup_event_lines;
		attrcount += ret;
	पूर्ण

	ev_पूर्णांक->group.name = iio_event_group_name;
	ev_पूर्णांक->group.attrs = kसुस्मृति(attrcount + 1,
				      माप(ev_पूर्णांक->group.attrs[0]),
				      GFP_KERNEL);
	अगर (ev_पूर्णांक->group.attrs == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_setup_event_lines;
	पूर्ण
	अगर (indio_dev->info->event_attrs)
		स_नकल(ev_पूर्णांक->group.attrs,
		       indio_dev->info->event_attrs->attrs,
		       माप(ev_पूर्णांक->group.attrs[0]) * attrcount_orig);
	attrn = attrcount_orig;
	/* Add all elements from the list. */
	list_क्रम_each_entry(p, &ev_पूर्णांक->dev_attr_list, l)
		ev_पूर्णांक->group.attrs[attrn++] = &p->dev_attr.attr;

	ret = iio_device_रेजिस्टर_sysfs_group(indio_dev, &ev_पूर्णांक->group);
	अगर (ret)
		जाओ error_मुक्त_setup_event_lines;

	ev_पूर्णांक->ioctl_handler.ioctl = iio_event_ioctl;
	iio_device_ioctl_handler_रेजिस्टर(&iio_dev_opaque->indio_dev,
					  &ev_पूर्णांक->ioctl_handler);

	वापस 0;

error_मुक्त_setup_event_lines:
	iio_मुक्त_chan_devattr_list(&ev_पूर्णांक->dev_attr_list);
	kमुक्त(ev_पूर्णांक);
	iio_dev_opaque->event_पूर्णांकerface = शून्य;
	वापस ret;
पूर्ण

/**
 * iio_device_wakeup_eventset - Wakes up the event रुकोqueue
 * @indio_dev: The IIO device
 *
 * Wakes up the event रुकोqueue used क्रम poll() and blocking पढ़ो().
 * Should usually be called when the device is unरेजिस्टरed.
 */
व्योम iio_device_wakeup_eventset(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	अगर (iio_dev_opaque->event_पूर्णांकerface == शून्य)
		वापस;
	wake_up(&iio_dev_opaque->event_पूर्णांकerface->रुको);
पूर्ण

व्योम iio_device_unरेजिस्टर_eventset(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक = iio_dev_opaque->event_पूर्णांकerface;

	अगर (ev_पूर्णांक == शून्य)
		वापस;

	iio_device_ioctl_handler_unरेजिस्टर(&ev_पूर्णांक->ioctl_handler);
	iio_मुक्त_chan_devattr_list(&ev_पूर्णांक->dev_attr_list);
	kमुक्त(ev_पूर्णांक->group.attrs);
	kमुक्त(ev_पूर्णांक);
	iio_dev_opaque->event_पूर्णांकerface = शून्य;
पूर्ण
