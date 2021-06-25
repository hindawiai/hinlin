<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* The industrial I/O core
 *
 * Copyright (c) 2008 Jonathan Cameron
 *
 * Handling of buffer allocation / resizing.
 *
 * Things to look at here.
 * - Better memory allocation techniques?
 * - Alternative access techniques?
 */
#समावेश <linux/anon_inodes.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/device.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/cdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/iio-opaque.h>
#समावेश "iio_core.h"
#समावेश "iio_core_trigger.h"
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/buffer_impl.h>

अटल स्थिर अक्षर * स्थिर iio_endian_prefix[] = अणु
	[IIO_BE] = "be",
	[IIO_LE] = "le",
पूर्ण;

अटल bool iio_buffer_is_active(काष्ठा iio_buffer *buf)
अणु
	वापस !list_empty(&buf->buffer_list);
पूर्ण

अटल माप_प्रकार iio_buffer_data_available(काष्ठा iio_buffer *buf)
अणु
	वापस buf->access->data_available(buf);
पूर्ण

अटल पूर्णांक iio_buffer_flush_hwfअगरo(काष्ठा iio_dev *indio_dev,
				   काष्ठा iio_buffer *buf, माप_प्रकार required)
अणु
	अगर (!indio_dev->info->hwfअगरo_flush_to_buffer)
		वापस -ENODEV;

	वापस indio_dev->info->hwfअगरo_flush_to_buffer(indio_dev, required);
पूर्ण

अटल bool iio_buffer_पढ़ोy(काष्ठा iio_dev *indio_dev, काष्ठा iio_buffer *buf,
			     माप_प्रकार to_रुको, पूर्णांक to_flush)
अणु
	माप_प्रकार avail;
	पूर्णांक flushed = 0;

	/* wakeup अगर the device was unरेजिस्टरed */
	अगर (!indio_dev->info)
		वापस true;

	/* drain the buffer अगर it was disabled */
	अगर (!iio_buffer_is_active(buf)) अणु
		to_रुको = min_t(माप_प्रकार, to_रुको, 1);
		to_flush = 0;
	पूर्ण

	avail = iio_buffer_data_available(buf);

	अगर (avail >= to_रुको) अणु
		/* क्रमce a flush क्रम non-blocking पढ़ोs */
		अगर (!to_रुको && avail < to_flush)
			iio_buffer_flush_hwfअगरo(indio_dev, buf,
						to_flush - avail);
		वापस true;
	पूर्ण

	अगर (to_flush)
		flushed = iio_buffer_flush_hwfअगरo(indio_dev, buf,
						  to_रुको - avail);
	अगर (flushed <= 0)
		वापस false;

	अगर (avail + flushed >= to_रुको)
		वापस true;

	वापस false;
पूर्ण

/**
 * iio_buffer_पढ़ो() - chrdev पढ़ो क्रम buffer access
 * @filp:	File काष्ठाure poपूर्णांकer क्रम the अक्षर device
 * @buf:	Destination buffer क्रम iio buffer पढ़ो
 * @n:		First n bytes to पढ़ो
 * @f_ps:	Long offset provided by the user as a seek position
 *
 * This function relies on all buffer implementations having an
 * iio_buffer as their first element.
 *
 * Return: negative values corresponding to error codes or ret != 0
 *	   क्रम ending the पढ़ोing activity
 **/
अटल sमाप_प्रकार iio_buffer_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			       माप_प्रकार n, loff_t *f_ps)
अणु
	काष्ठा iio_dev_buffer_pair *ib = filp->निजी_data;
	काष्ठा iio_buffer *rb = ib->buffer;
	काष्ठा iio_dev *indio_dev = ib->indio_dev;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	माप_प्रकार datum_size;
	माप_प्रकार to_रुको;
	पूर्णांक ret = 0;

	अगर (!indio_dev->info)
		वापस -ENODEV;

	अगर (!rb || !rb->access->पढ़ो)
		वापस -EINVAL;

	datum_size = rb->bytes_per_datum;

	/*
	 * If datum_size is 0 there will never be anything to पढ़ो from the
	 * buffer, so संकेत end of file now.
	 */
	अगर (!datum_size)
		वापस 0;

	अगर (filp->f_flags & O_NONBLOCK)
		to_रुको = 0;
	अन्यथा
		to_रुको = min_t(माप_प्रकार, n / datum_size, rb->watermark);

	add_रुको_queue(&rb->pollq, &रुको);
	करो अणु
		अगर (!indio_dev->info) अणु
			ret = -ENODEV;
			अवरोध;
		पूर्ण

		अगर (!iio_buffer_पढ़ोy(indio_dev, rb, to_रुको, n / datum_size)) अणु
			अगर (संकेत_pending(current)) अणु
				ret = -ERESTARTSYS;
				अवरोध;
			पूर्ण

			रुको_woken(&रुको, TASK_INTERRUPTIBLE,
				   MAX_SCHEDULE_TIMEOUT);
			जारी;
		पूर्ण

		ret = rb->access->पढ़ो(rb, n, buf);
		अगर (ret == 0 && (filp->f_flags & O_NONBLOCK))
			ret = -EAGAIN;
	पूर्ण जबतक (ret == 0);
	हटाओ_रुको_queue(&rb->pollq, &रुको);

	वापस ret;
पूर्ण

/**
 * iio_buffer_poll() - poll the buffer to find out अगर it has data
 * @filp:	File काष्ठाure poपूर्णांकer क्रम device access
 * @रुको:	Poll table काष्ठाure poपूर्णांकer क्रम which the driver adds
 *		a रुको queue
 *
 * Return: (EPOLLIN | EPOLLRDNORM) अगर data is available क्रम पढ़ोing
 *	   or 0 क्रम other हालs
 */
अटल __poll_t iio_buffer_poll(काष्ठा file *filp,
				काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा iio_dev_buffer_pair *ib = filp->निजी_data;
	काष्ठा iio_buffer *rb = ib->buffer;
	काष्ठा iio_dev *indio_dev = ib->indio_dev;

	अगर (!indio_dev->info || rb == शून्य)
		वापस 0;

	poll_रुको(filp, &rb->pollq, रुको);
	अगर (iio_buffer_पढ़ोy(indio_dev, rb, rb->watermark, 0))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

sमाप_प्रकार iio_buffer_पढ़ो_wrapper(काष्ठा file *filp, अक्षर __user *buf,
				माप_प्रकार n, loff_t *f_ps)
अणु
	काष्ठा iio_dev_buffer_pair *ib = filp->निजी_data;
	काष्ठा iio_buffer *rb = ib->buffer;

	/* check अगर buffer was खोलोed through new API */
	अगर (test_bit(IIO_BUSY_BIT_POS, &rb->flags))
		वापस -EBUSY;

	वापस iio_buffer_पढ़ो(filp, buf, n, f_ps);
पूर्ण

__poll_t iio_buffer_poll_wrapper(काष्ठा file *filp,
				 काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा iio_dev_buffer_pair *ib = filp->निजी_data;
	काष्ठा iio_buffer *rb = ib->buffer;

	/* check अगर buffer was खोलोed through new API */
	अगर (test_bit(IIO_BUSY_BIT_POS, &rb->flags))
		वापस 0;

	वापस iio_buffer_poll(filp, रुको);
पूर्ण

/**
 * iio_buffer_wakeup_poll - Wakes up the buffer रुकोqueue
 * @indio_dev: The IIO device
 *
 * Wakes up the event रुकोqueue used क्रम poll(). Should usually
 * be called when the device is unरेजिस्टरed.
 */
व्योम iio_buffer_wakeup_poll(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_buffer *buffer;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < iio_dev_opaque->attached_buffers_cnt; i++) अणु
		buffer = iio_dev_opaque->attached_buffers[i];
		wake_up(&buffer->pollq);
	पूर्ण
पूर्ण

व्योम iio_buffer_init(काष्ठा iio_buffer *buffer)
अणु
	INIT_LIST_HEAD(&buffer->demux_list);
	INIT_LIST_HEAD(&buffer->buffer_list);
	init_रुकोqueue_head(&buffer->pollq);
	kref_init(&buffer->ref);
	अगर (!buffer->watermark)
		buffer->watermark = 1;
पूर्ण
EXPORT_SYMBOL(iio_buffer_init);

व्योम iio_device_detach_buffers(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_buffer *buffer;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < iio_dev_opaque->attached_buffers_cnt; i++) अणु
		buffer = iio_dev_opaque->attached_buffers[i];
		iio_buffer_put(buffer);
	पूर्ण

	kमुक्त(iio_dev_opaque->attached_buffers);
पूर्ण

अटल sमाप_प्रकार iio_show_scan_index(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", to_iio_dev_attr(attr)->c->scan_index);
पूर्ण

अटल sमाप_प्रकार iio_show_fixed_type(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	u8 type = this_attr->c->scan_type.endianness;

	अगर (type == IIO_CPU) अणु
#अगर_घोषित __LITTLE_ENDIAN
		type = IIO_LE;
#अन्यथा
		type = IIO_BE;
#पूर्ण_अगर
	पूर्ण
	अगर (this_attr->c->scan_type.repeat > 1)
		वापस sysfs_emit(buf, "%s:%c%d/%dX%d>>%u\n",
		       iio_endian_prefix[type],
		       this_attr->c->scan_type.sign,
		       this_attr->c->scan_type.realbits,
		       this_attr->c->scan_type.storagebits,
		       this_attr->c->scan_type.repeat,
		       this_attr->c->scan_type.shअगरt);
	अन्यथा
		वापस sysfs_emit(buf, "%s:%c%d/%d>>%u\n",
		       iio_endian_prefix[type],
		       this_attr->c->scan_type.sign,
		       this_attr->c->scan_type.realbits,
		       this_attr->c->scan_type.storagebits,
		       this_attr->c->scan_type.shअगरt);
पूर्ण

अटल sमाप_प्रकार iio_scan_el_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;

	/* Ensure ret is 0 or 1. */
	ret = !!test_bit(to_iio_dev_attr(attr)->address,
		       buffer->scan_mask);

	वापस sysfs_emit(buf, "%d\n", ret);
पूर्ण

/* Note शून्य used as error indicator as it करोesn't make sense. */
अटल स्थिर अचिन्हित दीर्घ *iio_scan_mask_match(स्थिर अचिन्हित दीर्घ *av_masks,
					  अचिन्हित पूर्णांक masklength,
					  स्थिर अचिन्हित दीर्घ *mask,
					  bool strict)
अणु
	अगर (biपंचांगap_empty(mask, masklength))
		वापस शून्य;
	जबतक (*av_masks) अणु
		अगर (strict) अणु
			अगर (biपंचांगap_equal(mask, av_masks, masklength))
				वापस av_masks;
		पूर्ण अन्यथा अणु
			अगर (biपंचांगap_subset(mask, av_masks, masklength))
				वापस av_masks;
		पूर्ण
		av_masks += BITS_TO_LONGS(masklength);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool iio_validate_scan_mask(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *mask)
अणु
	अगर (!indio_dev->setup_ops->validate_scan_mask)
		वापस true;

	वापस indio_dev->setup_ops->validate_scan_mask(indio_dev, mask);
पूर्ण

/**
 * iio_scan_mask_set() - set particular bit in the scan mask
 * @indio_dev: the iio device
 * @buffer: the buffer whose scan mask we are पूर्णांकerested in
 * @bit: the bit to be set.
 *
 * Note that at this poपूर्णांक we have no way of knowing what other
 * buffers might request, hence this code only verअगरies that the
 * inभागidual buffers request is plausible.
 */
अटल पूर्णांक iio_scan_mask_set(काष्ठा iio_dev *indio_dev,
		      काष्ठा iio_buffer *buffer, पूर्णांक bit)
अणु
	स्थिर अचिन्हित दीर्घ *mask;
	अचिन्हित दीर्घ *trialmask;

	trialmask = biपंचांगap_zalloc(indio_dev->masklength, GFP_KERNEL);
	अगर (trialmask == शून्य)
		वापस -ENOMEM;
	अगर (!indio_dev->masklength) अणु
		WARN(1, "Trying to set scanmask prior to registering buffer\n");
		जाओ err_invalid_mask;
	पूर्ण
	biपंचांगap_copy(trialmask, buffer->scan_mask, indio_dev->masklength);
	set_bit(bit, trialmask);

	अगर (!iio_validate_scan_mask(indio_dev, trialmask))
		जाओ err_invalid_mask;

	अगर (indio_dev->available_scan_masks) अणु
		mask = iio_scan_mask_match(indio_dev->available_scan_masks,
					   indio_dev->masklength,
					   trialmask, false);
		अगर (!mask)
			जाओ err_invalid_mask;
	पूर्ण
	biपंचांगap_copy(buffer->scan_mask, trialmask, indio_dev->masklength);

	biपंचांगap_मुक्त(trialmask);

	वापस 0;

err_invalid_mask:
	biपंचांगap_मुक्त(trialmask);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक iio_scan_mask_clear(काष्ठा iio_buffer *buffer, पूर्णांक bit)
अणु
	clear_bit(bit, buffer->scan_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक iio_scan_mask_query(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_buffer *buffer, पूर्णांक bit)
अणु
	अगर (bit > indio_dev->masklength)
		वापस -EINVAL;

	अगर (!buffer->scan_mask)
		वापस 0;

	/* Ensure वापस value is 0 or 1. */
	वापस !!test_bit(bit, buffer->scan_mask);
पूर्ण;

अटल sमाप_प्रकार iio_scan_el_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf,
				 माप_प्रकार len)
अणु
	पूर्णांक ret;
	bool state;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा iio_buffer *buffer = this_attr->buffer;

	ret = strtobool(buf, &state);
	अगर (ret < 0)
		वापस ret;
	mutex_lock(&indio_dev->mlock);
	अगर (iio_buffer_is_active(buffer)) अणु
		ret = -EBUSY;
		जाओ error_ret;
	पूर्ण
	ret = iio_scan_mask_query(indio_dev, buffer, this_attr->address);
	अगर (ret < 0)
		जाओ error_ret;
	अगर (!state && ret) अणु
		ret = iio_scan_mask_clear(buffer, this_attr->address);
		अगर (ret)
			जाओ error_ret;
	पूर्ण अन्यथा अगर (state && !ret) अणु
		ret = iio_scan_mask_set(indio_dev, buffer, this_attr->address);
		अगर (ret)
			जाओ error_ret;
	पूर्ण

error_ret:
	mutex_unlock(&indio_dev->mlock);

	वापस ret < 0 ? ret : len;

पूर्ण

अटल sमाप_प्रकार iio_scan_el_ts_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;

	वापस sysfs_emit(buf, "%d\n", buffer->scan_बारtamp);
पूर्ण

अटल sमाप_प्रकार iio_scan_el_ts_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf,
				    माप_प्रकार len)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;
	bool state;

	ret = strtobool(buf, &state);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&indio_dev->mlock);
	अगर (iio_buffer_is_active(buffer)) अणु
		ret = -EBUSY;
		जाओ error_ret;
	पूर्ण
	buffer->scan_बारtamp = state;
error_ret:
	mutex_unlock(&indio_dev->mlock);

	वापस ret ? ret : len;
पूर्ण

अटल पूर्णांक iio_buffer_add_channel_sysfs(काष्ठा iio_dev *indio_dev,
					काष्ठा iio_buffer *buffer,
					स्थिर काष्ठा iio_chan_spec *chan)
अणु
	पूर्णांक ret, attrcount = 0;

	ret = __iio_add_chan_devattr("index",
				     chan,
				     &iio_show_scan_index,
				     शून्य,
				     0,
				     IIO_SEPARATE,
				     &indio_dev->dev,
				     buffer,
				     &buffer->buffer_attr_list);
	अगर (ret)
		वापस ret;
	attrcount++;
	ret = __iio_add_chan_devattr("type",
				     chan,
				     &iio_show_fixed_type,
				     शून्य,
				     0,
				     0,
				     &indio_dev->dev,
				     buffer,
				     &buffer->buffer_attr_list);
	अगर (ret)
		वापस ret;
	attrcount++;
	अगर (chan->type != IIO_TIMESTAMP)
		ret = __iio_add_chan_devattr("en",
					     chan,
					     &iio_scan_el_show,
					     &iio_scan_el_store,
					     chan->scan_index,
					     0,
					     &indio_dev->dev,
					     buffer,
					     &buffer->buffer_attr_list);
	अन्यथा
		ret = __iio_add_chan_devattr("en",
					     chan,
					     &iio_scan_el_ts_show,
					     &iio_scan_el_ts_store,
					     chan->scan_index,
					     0,
					     &indio_dev->dev,
					     buffer,
					     &buffer->buffer_attr_list);
	अगर (ret)
		वापस ret;
	attrcount++;
	ret = attrcount;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iio_buffer_पढ़ो_length(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;

	वापस sysfs_emit(buf, "%d\n", buffer->length);
पूर्ण

अटल sमाप_प्रकार iio_buffer_ग_लिखो_length(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val == buffer->length)
		वापस len;

	mutex_lock(&indio_dev->mlock);
	अगर (iio_buffer_is_active(buffer)) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		buffer->access->set_length(buffer, val);
		ret = 0;
	पूर्ण
	अगर (ret)
		जाओ out;
	अगर (buffer->length && buffer->length < buffer->watermark)
		buffer->watermark = buffer->length;
out:
	mutex_unlock(&indio_dev->mlock);

	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार iio_buffer_show_enable(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;

	वापस sysfs_emit(buf, "%d\n", iio_buffer_is_active(buffer));
पूर्ण

अटल अचिन्हित पूर्णांक iio_storage_bytes_क्रम_si(काष्ठा iio_dev *indio_dev,
					     अचिन्हित पूर्णांक scan_index)
अणु
	स्थिर काष्ठा iio_chan_spec *ch;
	अचिन्हित पूर्णांक bytes;

	ch = iio_find_channel_from_si(indio_dev, scan_index);
	bytes = ch->scan_type.storagebits / 8;
	अगर (ch->scan_type.repeat > 1)
		bytes *= ch->scan_type.repeat;
	वापस bytes;
पूर्ण

अटल अचिन्हित पूर्णांक iio_storage_bytes_क्रम_बारtamp(काष्ठा iio_dev *indio_dev)
अणु
	वापस iio_storage_bytes_क्रम_si(indio_dev,
					indio_dev->scan_index_बारtamp);
पूर्ण

अटल पूर्णांक iio_compute_scan_bytes(काष्ठा iio_dev *indio_dev,
				स्थिर अचिन्हित दीर्घ *mask, bool बारtamp)
अणु
	अचिन्हित bytes = 0;
	पूर्णांक length, i, largest = 0;

	/* How much space will the demuxed element take? */
	क्रम_each_set_bit(i, mask,
			 indio_dev->masklength) अणु
		length = iio_storage_bytes_क्रम_si(indio_dev, i);
		bytes = ALIGN(bytes, length);
		bytes += length;
		largest = max(largest, length);
	पूर्ण

	अगर (बारtamp) अणु
		length = iio_storage_bytes_क्रम_बारtamp(indio_dev);
		bytes = ALIGN(bytes, length);
		bytes += length;
		largest = max(largest, length);
	पूर्ण

	bytes = ALIGN(bytes, largest);
	वापस bytes;
पूर्ण

अटल व्योम iio_buffer_activate(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_buffer *buffer)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	iio_buffer_get(buffer);
	list_add(&buffer->buffer_list, &iio_dev_opaque->buffer_list);
पूर्ण

अटल व्योम iio_buffer_deactivate(काष्ठा iio_buffer *buffer)
अणु
	list_del_init(&buffer->buffer_list);
	wake_up_पूर्णांकerruptible(&buffer->pollq);
	iio_buffer_put(buffer);
पूर्ण

अटल व्योम iio_buffer_deactivate_all(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_buffer *buffer, *_buffer;

	list_क्रम_each_entry_safe(buffer, _buffer,
			&iio_dev_opaque->buffer_list, buffer_list)
		iio_buffer_deactivate(buffer);
पूर्ण

अटल पूर्णांक iio_buffer_enable(काष्ठा iio_buffer *buffer,
	काष्ठा iio_dev *indio_dev)
अणु
	अगर (!buffer->access->enable)
		वापस 0;
	वापस buffer->access->enable(buffer, indio_dev);
पूर्ण

अटल पूर्णांक iio_buffer_disable(काष्ठा iio_buffer *buffer,
	काष्ठा iio_dev *indio_dev)
अणु
	अगर (!buffer->access->disable)
		वापस 0;
	वापस buffer->access->disable(buffer, indio_dev);
पूर्ण

अटल व्योम iio_buffer_update_bytes_per_datum(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_buffer *buffer)
अणु
	अचिन्हित पूर्णांक bytes;

	अगर (!buffer->access->set_bytes_per_datum)
		वापस;

	bytes = iio_compute_scan_bytes(indio_dev, buffer->scan_mask,
		buffer->scan_बारtamp);

	buffer->access->set_bytes_per_datum(buffer, bytes);
पूर्ण

अटल पूर्णांक iio_buffer_request_update(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_buffer *buffer)
अणु
	पूर्णांक ret;

	iio_buffer_update_bytes_per_datum(indio_dev, buffer);
	अगर (buffer->access->request_update) अणु
		ret = buffer->access->request_update(buffer);
		अगर (ret) अणु
			dev_dbg(&indio_dev->dev,
			       "Buffer not started: buffer parameter update failed (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iio_मुक्त_scan_mask(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *mask)
अणु
	/* If the mask is dynamically allocated मुक्त it, otherwise करो nothing */
	अगर (!indio_dev->available_scan_masks)
		biपंचांगap_मुक्त(mask);
पूर्ण

काष्ठा iio_device_config अणु
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक watermark;
	स्थिर अचिन्हित दीर्घ *scan_mask;
	अचिन्हित पूर्णांक scan_bytes;
	bool scan_बारtamp;
पूर्ण;

अटल पूर्णांक iio_verअगरy_update(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_buffer *insert_buffer, काष्ठा iio_buffer *हटाओ_buffer,
	काष्ठा iio_device_config *config)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	अचिन्हित दीर्घ *compound_mask;
	स्थिर अचिन्हित दीर्घ *scan_mask;
	bool strict_scanmask = false;
	काष्ठा iio_buffer *buffer;
	bool scan_बारtamp;
	अचिन्हित पूर्णांक modes;

	अगर (insert_buffer &&
	    biपंचांगap_empty(insert_buffer->scan_mask, indio_dev->masklength)) अणु
		dev_dbg(&indio_dev->dev,
			"At least one scan element must be enabled first\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(config, 0, माप(*config));
	config->watermark = ~0;

	/*
	 * If there is just one buffer and we are removing it there is nothing
	 * to verअगरy.
	 */
	अगर (हटाओ_buffer && !insert_buffer &&
		list_is_singular(&iio_dev_opaque->buffer_list))
			वापस 0;

	modes = indio_dev->modes;

	list_क्रम_each_entry(buffer, &iio_dev_opaque->buffer_list, buffer_list) अणु
		अगर (buffer == हटाओ_buffer)
			जारी;
		modes &= buffer->access->modes;
		config->watermark = min(config->watermark, buffer->watermark);
	पूर्ण

	अगर (insert_buffer) अणु
		modes &= insert_buffer->access->modes;
		config->watermark = min(config->watermark,
			insert_buffer->watermark);
	पूर्ण

	/* Definitely possible क्रम devices to support both of these. */
	अगर ((modes & INDIO_BUFFER_TRIGGERED) && indio_dev->trig) अणु
		config->mode = INDIO_BUFFER_TRIGGERED;
	पूर्ण अन्यथा अगर (modes & INDIO_BUFFER_HARDWARE) अणु
		/*
		 * Keep things simple क्रम now and only allow a single buffer to
		 * be connected in hardware mode.
		 */
		अगर (insert_buffer && !list_empty(&iio_dev_opaque->buffer_list))
			वापस -EINVAL;
		config->mode = INDIO_BUFFER_HARDWARE;
		strict_scanmask = true;
	पूर्ण अन्यथा अगर (modes & INDIO_BUFFER_SOFTWARE) अणु
		config->mode = INDIO_BUFFER_SOFTWARE;
	पूर्ण अन्यथा अणु
		/* Can only occur on first buffer */
		अगर (indio_dev->modes & INDIO_BUFFER_TRIGGERED)
			dev_dbg(&indio_dev->dev, "Buffer not started: no trigger\n");
		वापस -EINVAL;
	पूर्ण

	/* What scan mask करो we actually have? */
	compound_mask = biपंचांगap_zalloc(indio_dev->masklength, GFP_KERNEL);
	अगर (compound_mask == शून्य)
		वापस -ENOMEM;

	scan_बारtamp = false;

	list_क्रम_each_entry(buffer, &iio_dev_opaque->buffer_list, buffer_list) अणु
		अगर (buffer == हटाओ_buffer)
			जारी;
		biपंचांगap_or(compound_mask, compound_mask, buffer->scan_mask,
			  indio_dev->masklength);
		scan_बारtamp |= buffer->scan_बारtamp;
	पूर्ण

	अगर (insert_buffer) अणु
		biपंचांगap_or(compound_mask, compound_mask,
			  insert_buffer->scan_mask, indio_dev->masklength);
		scan_बारtamp |= insert_buffer->scan_बारtamp;
	पूर्ण

	अगर (indio_dev->available_scan_masks) अणु
		scan_mask = iio_scan_mask_match(indio_dev->available_scan_masks,
				    indio_dev->masklength,
				    compound_mask,
				    strict_scanmask);
		biपंचांगap_मुक्त(compound_mask);
		अगर (scan_mask == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
	    scan_mask = compound_mask;
	पूर्ण

	config->scan_bytes = iio_compute_scan_bytes(indio_dev,
				    scan_mask, scan_बारtamp);
	config->scan_mask = scan_mask;
	config->scan_बारtamp = scan_बारtamp;

	वापस 0;
पूर्ण

/**
 * काष्ठा iio_demux_table - table describing demux स_नकल ops
 * @from:	index to copy from
 * @to:		index to copy to
 * @length:	how many bytes to copy
 * @l:		list head used क्रम management
 */
काष्ठा iio_demux_table अणु
	अचिन्हित from;
	अचिन्हित to;
	अचिन्हित length;
	काष्ठा list_head l;
पूर्ण;

अटल व्योम iio_buffer_demux_मुक्त(काष्ठा iio_buffer *buffer)
अणु
	काष्ठा iio_demux_table *p, *q;
	list_क्रम_each_entry_safe(p, q, &buffer->demux_list, l) अणु
		list_del(&p->l);
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल पूर्णांक iio_buffer_add_demux(काष्ठा iio_buffer *buffer,
	काष्ठा iio_demux_table **p, अचिन्हित पूर्णांक in_loc, अचिन्हित पूर्णांक out_loc,
	अचिन्हित पूर्णांक length)
अणु

	अगर (*p && (*p)->from + (*p)->length == in_loc &&
		(*p)->to + (*p)->length == out_loc) अणु
		(*p)->length += length;
	पूर्ण अन्यथा अणु
		*p = kदो_स्मृति(माप(**p), GFP_KERNEL);
		अगर (*p == शून्य)
			वापस -ENOMEM;
		(*p)->from = in_loc;
		(*p)->to = out_loc;
		(*p)->length = length;
		list_add_tail(&(*p)->l, &buffer->demux_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iio_buffer_update_demux(काष्ठा iio_dev *indio_dev,
				   काष्ठा iio_buffer *buffer)
अणु
	पूर्णांक ret, in_ind = -1, out_ind, length;
	अचिन्हित in_loc = 0, out_loc = 0;
	काष्ठा iio_demux_table *p = शून्य;

	/* Clear out any old demux */
	iio_buffer_demux_मुक्त(buffer);
	kमुक्त(buffer->demux_bounce);
	buffer->demux_bounce = शून्य;

	/* First work out which scan mode we will actually have */
	अगर (biपंचांगap_equal(indio_dev->active_scan_mask,
			 buffer->scan_mask,
			 indio_dev->masklength))
		वापस 0;

	/* Now we have the two masks, work from least sig and build up sizes */
	क्रम_each_set_bit(out_ind,
			 buffer->scan_mask,
			 indio_dev->masklength) अणु
		in_ind = find_next_bit(indio_dev->active_scan_mask,
				       indio_dev->masklength,
				       in_ind + 1);
		जबतक (in_ind != out_ind) अणु
			length = iio_storage_bytes_क्रम_si(indio_dev, in_ind);
			/* Make sure we are aligned */
			in_loc = roundup(in_loc, length) + length;
			in_ind = find_next_bit(indio_dev->active_scan_mask,
					       indio_dev->masklength,
					       in_ind + 1);
		पूर्ण
		length = iio_storage_bytes_क्रम_si(indio_dev, in_ind);
		out_loc = roundup(out_loc, length);
		in_loc = roundup(in_loc, length);
		ret = iio_buffer_add_demux(buffer, &p, in_loc, out_loc, length);
		अगर (ret)
			जाओ error_clear_mux_table;
		out_loc += length;
		in_loc += length;
	पूर्ण
	/* Relies on scan_बारtamp being last */
	अगर (buffer->scan_बारtamp) अणु
		length = iio_storage_bytes_क्रम_बारtamp(indio_dev);
		out_loc = roundup(out_loc, length);
		in_loc = roundup(in_loc, length);
		ret = iio_buffer_add_demux(buffer, &p, in_loc, out_loc, length);
		अगर (ret)
			जाओ error_clear_mux_table;
		out_loc += length;
		in_loc += length;
	पूर्ण
	buffer->demux_bounce = kzalloc(out_loc, GFP_KERNEL);
	अगर (buffer->demux_bounce == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_clear_mux_table;
	पूर्ण
	वापस 0;

error_clear_mux_table:
	iio_buffer_demux_मुक्त(buffer);

	वापस ret;
पूर्ण

अटल पूर्णांक iio_update_demux(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_buffer *buffer;
	पूर्णांक ret;

	list_क्रम_each_entry(buffer, &iio_dev_opaque->buffer_list, buffer_list) अणु
		ret = iio_buffer_update_demux(indio_dev, buffer);
		अगर (ret < 0)
			जाओ error_clear_mux_table;
	पूर्ण
	वापस 0;

error_clear_mux_table:
	list_क्रम_each_entry(buffer, &iio_dev_opaque->buffer_list, buffer_list)
		iio_buffer_demux_मुक्त(buffer);

	वापस ret;
पूर्ण

अटल पूर्णांक iio_enable_buffers(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_device_config *config)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_buffer *buffer;
	पूर्णांक ret;

	indio_dev->active_scan_mask = config->scan_mask;
	indio_dev->scan_बारtamp = config->scan_बारtamp;
	indio_dev->scan_bytes = config->scan_bytes;
	indio_dev->currenपंचांगode = config->mode;

	iio_update_demux(indio_dev);

	/* Wind up again */
	अगर (indio_dev->setup_ops->preenable) अणु
		ret = indio_dev->setup_ops->preenable(indio_dev);
		अगर (ret) अणु
			dev_dbg(&indio_dev->dev,
			       "Buffer not started: buffer preenable failed (%d)\n", ret);
			जाओ err_unकरो_config;
		पूर्ण
	पूर्ण

	अगर (indio_dev->info->update_scan_mode) अणु
		ret = indio_dev->info
			->update_scan_mode(indio_dev,
					   indio_dev->active_scan_mask);
		अगर (ret < 0) अणु
			dev_dbg(&indio_dev->dev,
				"Buffer not started: update scan mode failed (%d)\n",
				ret);
			जाओ err_run_postdisable;
		पूर्ण
	पूर्ण

	अगर (indio_dev->info->hwfअगरo_set_watermark)
		indio_dev->info->hwfअगरo_set_watermark(indio_dev,
			config->watermark);

	list_क्रम_each_entry(buffer, &iio_dev_opaque->buffer_list, buffer_list) अणु
		ret = iio_buffer_enable(buffer, indio_dev);
		अगर (ret)
			जाओ err_disable_buffers;
	पूर्ण

	अगर (indio_dev->currenपंचांगode == INDIO_BUFFER_TRIGGERED) अणु
		ret = iio_trigger_attach_poll_func(indio_dev->trig,
						   indio_dev->pollfunc);
		अगर (ret)
			जाओ err_disable_buffers;
	पूर्ण

	अगर (indio_dev->setup_ops->postenable) अणु
		ret = indio_dev->setup_ops->postenable(indio_dev);
		अगर (ret) अणु
			dev_dbg(&indio_dev->dev,
			       "Buffer not started: postenable failed (%d)\n", ret);
			जाओ err_detach_pollfunc;
		पूर्ण
	पूर्ण

	वापस 0;

err_detach_pollfunc:
	अगर (indio_dev->currenपंचांगode == INDIO_BUFFER_TRIGGERED) अणु
		iio_trigger_detach_poll_func(indio_dev->trig,
					     indio_dev->pollfunc);
	पूर्ण
err_disable_buffers:
	list_क्रम_each_entry_जारी_reverse(buffer, &iio_dev_opaque->buffer_list,
					     buffer_list)
		iio_buffer_disable(buffer, indio_dev);
err_run_postdisable:
	अगर (indio_dev->setup_ops->postdisable)
		indio_dev->setup_ops->postdisable(indio_dev);
err_unकरो_config:
	indio_dev->currenपंचांगode = INDIO_सूचीECT_MODE;
	indio_dev->active_scan_mask = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक iio_disable_buffers(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_buffer *buffer;
	पूर्णांक ret = 0;
	पूर्णांक ret2;

	/* Wind करोwn existing buffers - अगरf there are any */
	अगर (list_empty(&iio_dev_opaque->buffer_list))
		वापस 0;

	/*
	 * If things go wrong at some step in disable we still need to जारी
	 * to perक्रमm the other steps, otherwise we leave the device in a
	 * inconsistent state. We वापस the error code क्रम the first error we
	 * encountered.
	 */

	अगर (indio_dev->setup_ops->predisable) अणु
		ret2 = indio_dev->setup_ops->predisable(indio_dev);
		अगर (ret2 && !ret)
			ret = ret2;
	पूर्ण

	अगर (indio_dev->currenपंचांगode == INDIO_BUFFER_TRIGGERED) अणु
		iio_trigger_detach_poll_func(indio_dev->trig,
					     indio_dev->pollfunc);
	पूर्ण

	list_क्रम_each_entry(buffer, &iio_dev_opaque->buffer_list, buffer_list) अणु
		ret2 = iio_buffer_disable(buffer, indio_dev);
		अगर (ret2 && !ret)
			ret = ret2;
	पूर्ण

	अगर (indio_dev->setup_ops->postdisable) अणु
		ret2 = indio_dev->setup_ops->postdisable(indio_dev);
		अगर (ret2 && !ret)
			ret = ret2;
	पूर्ण

	iio_मुक्त_scan_mask(indio_dev, indio_dev->active_scan_mask);
	indio_dev->active_scan_mask = शून्य;
	indio_dev->currenपंचांगode = INDIO_सूचीECT_MODE;

	वापस ret;
पूर्ण

अटल पूर्णांक __iio_update_buffers(काष्ठा iio_dev *indio_dev,
		       काष्ठा iio_buffer *insert_buffer,
		       काष्ठा iio_buffer *हटाओ_buffer)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_device_config new_config;
	पूर्णांक ret;

	ret = iio_verअगरy_update(indio_dev, insert_buffer, हटाओ_buffer,
		&new_config);
	अगर (ret)
		वापस ret;

	अगर (insert_buffer) अणु
		ret = iio_buffer_request_update(indio_dev, insert_buffer);
		अगर (ret)
			जाओ err_मुक्त_config;
	पूर्ण

	ret = iio_disable_buffers(indio_dev);
	अगर (ret)
		जाओ err_deactivate_all;

	अगर (हटाओ_buffer)
		iio_buffer_deactivate(हटाओ_buffer);
	अगर (insert_buffer)
		iio_buffer_activate(indio_dev, insert_buffer);

	/* If no buffers in list, we are करोne */
	अगर (list_empty(&iio_dev_opaque->buffer_list))
		वापस 0;

	ret = iio_enable_buffers(indio_dev, &new_config);
	अगर (ret)
		जाओ err_deactivate_all;

	वापस 0;

err_deactivate_all:
	/*
	 * We've alपढ़ोy verअगरied that the config is valid earlier. If things go
	 * wrong in either enable or disable the most likely reason is an IO
	 * error from the device. In this हाल there is no good recovery
	 * strategy. Just make sure to disable everything and leave the device
	 * in a sane state.  With a bit of luck the device might come back to
	 * lअगरe again later and userspace can try again.
	 */
	iio_buffer_deactivate_all(indio_dev);

err_मुक्त_config:
	iio_मुक्त_scan_mask(indio_dev, new_config.scan_mask);
	वापस ret;
पूर्ण

पूर्णांक iio_update_buffers(काष्ठा iio_dev *indio_dev,
		       काष्ठा iio_buffer *insert_buffer,
		       काष्ठा iio_buffer *हटाओ_buffer)
अणु
	पूर्णांक ret;

	अगर (insert_buffer == हटाओ_buffer)
		वापस 0;

	mutex_lock(&indio_dev->info_exist_lock);
	mutex_lock(&indio_dev->mlock);

	अगर (insert_buffer && iio_buffer_is_active(insert_buffer))
		insert_buffer = शून्य;

	अगर (हटाओ_buffer && !iio_buffer_is_active(हटाओ_buffer))
		हटाओ_buffer = शून्य;

	अगर (!insert_buffer && !हटाओ_buffer) अणु
		ret = 0;
		जाओ out_unlock;
	पूर्ण

	अगर (indio_dev->info == शून्य) अणु
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	ret = __iio_update_buffers(indio_dev, insert_buffer, हटाओ_buffer);

out_unlock:
	mutex_unlock(&indio_dev->mlock);
	mutex_unlock(&indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_update_buffers);

व्योम iio_disable_all_buffers(काष्ठा iio_dev *indio_dev)
अणु
	iio_disable_buffers(indio_dev);
	iio_buffer_deactivate_all(indio_dev);
पूर्ण

अटल sमाप_प्रकार iio_buffer_store_enable(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf,
				       माप_प्रकार len)
अणु
	पूर्णांक ret;
	bool requested_state;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;
	bool inlist;

	ret = strtobool(buf, &requested_state);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&indio_dev->mlock);

	/* Find out अगर it is in the list */
	inlist = iio_buffer_is_active(buffer);
	/* Alपढ़ोy in desired state */
	अगर (inlist == requested_state)
		जाओ करोne;

	अगर (requested_state)
		ret = __iio_update_buffers(indio_dev, buffer, शून्य);
	अन्यथा
		ret = __iio_update_buffers(indio_dev, शून्य, buffer);

करोne:
	mutex_unlock(&indio_dev->mlock);
	वापस (ret < 0) ? ret : len;
पूर्ण

अटल sमाप_प्रकार iio_buffer_show_watermark(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;

	वापस sysfs_emit(buf, "%u\n", buffer->watermark);
पूर्ण

अटल sमाप_प्रकार iio_buffer_store_watermark(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf,
					  माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;
	अगर (!val)
		वापस -EINVAL;

	mutex_lock(&indio_dev->mlock);

	अगर (val > buffer->length) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (iio_buffer_is_active(buffer)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	buffer->watermark = val;
out:
	mutex_unlock(&indio_dev->mlock);

	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार iio_dma_show_data_available(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;

	वापस sysfs_emit(buf, "%zu\n", iio_buffer_data_available(buffer));
पूर्ण

अटल DEVICE_ATTR(length, S_IRUGO | S_IWUSR, iio_buffer_पढ़ो_length,
		   iio_buffer_ग_लिखो_length);
अटल काष्ठा device_attribute dev_attr_length_ro = __ATTR(length,
	S_IRUGO, iio_buffer_पढ़ो_length, शून्य);
अटल DEVICE_ATTR(enable, S_IRUGO | S_IWUSR,
		   iio_buffer_show_enable, iio_buffer_store_enable);
अटल DEVICE_ATTR(watermark, S_IRUGO | S_IWUSR,
		   iio_buffer_show_watermark, iio_buffer_store_watermark);
अटल काष्ठा device_attribute dev_attr_watermark_ro = __ATTR(watermark,
	S_IRUGO, iio_buffer_show_watermark, शून्य);
अटल DEVICE_ATTR(data_available, S_IRUGO,
		iio_dma_show_data_available, शून्य);

अटल काष्ठा attribute *iio_buffer_attrs[] = अणु
	&dev_attr_length.attr,
	&dev_attr_enable.attr,
	&dev_attr_watermark.attr,
	&dev_attr_data_available.attr,
पूर्ण;

#घोषणा to_dev_attr(_attr) container_of(_attr, काष्ठा device_attribute, attr)

अटल काष्ठा attribute *iio_buffer_wrap_attr(काष्ठा iio_buffer *buffer,
					      काष्ठा attribute *attr)
अणु
	काष्ठा device_attribute *dattr = to_dev_attr(attr);
	काष्ठा iio_dev_attr *iio_attr;

	iio_attr = kzalloc(माप(*iio_attr), GFP_KERNEL);
	अगर (!iio_attr)
		वापस शून्य;

	iio_attr->buffer = buffer;
	स_नकल(&iio_attr->dev_attr, dattr, माप(iio_attr->dev_attr));
	iio_attr->dev_attr.attr.name = kstrdup_स्थिर(attr->name, GFP_KERNEL);
	sysfs_attr_init(&iio_attr->dev_attr.attr);

	list_add(&iio_attr->l, &buffer->buffer_attr_list);

	वापस &iio_attr->dev_attr.attr;
पूर्ण

अटल पूर्णांक iio_buffer_रेजिस्टर_legacy_sysfs_groups(काष्ठा iio_dev *indio_dev,
						   काष्ठा attribute **buffer_attrs,
						   पूर्णांक buffer_attrcount,
						   पूर्णांक scan_el_attrcount)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा attribute_group *group;
	काष्ठा attribute **attrs;
	पूर्णांक ret;

	attrs = kसुस्मृति(buffer_attrcount + 1, माप(*attrs), GFP_KERNEL);
	अगर (!attrs)
		वापस -ENOMEM;

	स_नकल(attrs, buffer_attrs, buffer_attrcount * माप(*attrs));

	group = &iio_dev_opaque->legacy_buffer_group;
	group->attrs = attrs;
	group->name = "buffer";

	ret = iio_device_रेजिस्टर_sysfs_group(indio_dev, group);
	अगर (ret)
		जाओ error_मुक्त_buffer_attrs;

	attrs = kसुस्मृति(scan_el_attrcount + 1, माप(*attrs), GFP_KERNEL);
	अगर (!attrs) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_buffer_attrs;
	पूर्ण

	स_नकल(attrs, &buffer_attrs[buffer_attrcount],
	       scan_el_attrcount * माप(*attrs));

	group = &iio_dev_opaque->legacy_scan_el_group;
	group->attrs = attrs;
	group->name = "scan_elements";

	ret = iio_device_रेजिस्टर_sysfs_group(indio_dev, group);
	अगर (ret)
		जाओ error_मुक्त_scan_el_attrs;

	वापस 0;

error_मुक्त_buffer_attrs:
	kमुक्त(iio_dev_opaque->legacy_buffer_group.attrs);
error_मुक्त_scan_el_attrs:
	kमुक्त(iio_dev_opaque->legacy_scan_el_group.attrs);

	वापस ret;
पूर्ण

अटल व्योम iio_buffer_unरेजिस्टर_legacy_sysfs_groups(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	kमुक्त(iio_dev_opaque->legacy_buffer_group.attrs);
	kमुक्त(iio_dev_opaque->legacy_scan_el_group.attrs);
पूर्ण

अटल पूर्णांक iio_buffer_chrdev_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा iio_dev_buffer_pair *ib = filep->निजी_data;
	काष्ठा iio_dev *indio_dev = ib->indio_dev;
	काष्ठा iio_buffer *buffer = ib->buffer;

	wake_up(&buffer->pollq);

	kमुक्त(ib);
	clear_bit(IIO_BUSY_BIT_POS, &buffer->flags);
	iio_device_put(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations iio_buffer_chrdev_fileops = अणु
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
	.पढ़ो = iio_buffer_पढ़ो,
	.poll = iio_buffer_poll,
	.release = iio_buffer_chrdev_release,
पूर्ण;

अटल दीर्घ iio_device_buffer_getfd(काष्ठा iio_dev *indio_dev, अचिन्हित दीर्घ arg)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	पूर्णांक __user *ival = (पूर्णांक __user *)arg;
	काष्ठा iio_dev_buffer_pair *ib;
	काष्ठा iio_buffer *buffer;
	पूर्णांक fd, idx, ret;

	अगर (copy_from_user(&idx, ival, माप(idx)))
		वापस -EFAULT;

	अगर (idx >= iio_dev_opaque->attached_buffers_cnt)
		वापस -ENODEV;

	iio_device_get(indio_dev);

	buffer = iio_dev_opaque->attached_buffers[idx];

	अगर (test_and_set_bit(IIO_BUSY_BIT_POS, &buffer->flags)) अणु
		ret = -EBUSY;
		जाओ error_iio_dev_put;
	पूर्ण

	ib = kzalloc(माप(*ib), GFP_KERNEL);
	अगर (!ib) अणु
		ret = -ENOMEM;
		जाओ error_clear_busy_bit;
	पूर्ण

	ib->indio_dev = indio_dev;
	ib->buffer = buffer;

	fd = anon_inode_getfd("iio:buffer", &iio_buffer_chrdev_fileops,
			      ib, O_RDWR | O_CLOEXEC);
	अगर (fd < 0) अणु
		ret = fd;
		जाओ error_मुक्त_ib;
	पूर्ण

	अगर (copy_to_user(ival, &fd, माप(fd))) अणु
		put_unused_fd(fd);
		ret = -EFAULT;
		जाओ error_मुक्त_ib;
	पूर्ण

	वापस 0;

error_मुक्त_ib:
	kमुक्त(ib);
error_clear_busy_bit:
	clear_bit(IIO_BUSY_BIT_POS, &buffer->flags);
error_iio_dev_put:
	iio_device_put(indio_dev);
	वापस ret;
पूर्ण

अटल दीर्घ iio_device_buffer_ioctl(काष्ठा iio_dev *indio_dev, काष्ठा file *filp,
				    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल IIO_BUFFER_GET_FD_IOCTL:
		वापस iio_device_buffer_getfd(indio_dev, arg);
	शेष:
		वापस IIO_IOCTL_UNHANDLED;
	पूर्ण
पूर्ण

अटल पूर्णांक __iio_buffer_alloc_sysfs_and_mask(काष्ठा iio_buffer *buffer,
					     काष्ठा iio_dev *indio_dev,
					     पूर्णांक index)
अणु
	काष्ठा iio_dev_attr *p;
	काष्ठा attribute **attr;
	पूर्णांक ret, i, attrn, scan_el_attrcount, buffer_attrcount;
	स्थिर काष्ठा iio_chan_spec *channels;

	buffer_attrcount = 0;
	अगर (buffer->attrs) अणु
		जबतक (buffer->attrs[buffer_attrcount] != शून्य)
			buffer_attrcount++;
	पूर्ण

	scan_el_attrcount = 0;
	INIT_LIST_HEAD(&buffer->buffer_attr_list);
	channels = indio_dev->channels;
	अगर (channels) अणु
		/* new magic */
		क्रम (i = 0; i < indio_dev->num_channels; i++) अणु
			अगर (channels[i].scan_index < 0)
				जारी;

			ret = iio_buffer_add_channel_sysfs(indio_dev, buffer,
							 &channels[i]);
			अगर (ret < 0)
				जाओ error_cleanup_dynamic;
			scan_el_attrcount += ret;
			अगर (channels[i].type == IIO_TIMESTAMP)
				indio_dev->scan_index_बारtamp =
					channels[i].scan_index;
		पूर्ण
		अगर (indio_dev->masklength && buffer->scan_mask == शून्य) अणु
			buffer->scan_mask = biपंचांगap_zalloc(indio_dev->masklength,
							  GFP_KERNEL);
			अगर (buffer->scan_mask == शून्य) अणु
				ret = -ENOMEM;
				जाओ error_cleanup_dynamic;
			पूर्ण
		पूर्ण
	पूर्ण

	attrn = buffer_attrcount + scan_el_attrcount + ARRAY_SIZE(iio_buffer_attrs);
	attr = kसुस्मृति(attrn + 1, माप(* attr), GFP_KERNEL);
	अगर (!attr) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_scan_mask;
	पूर्ण

	स_नकल(attr, iio_buffer_attrs, माप(iio_buffer_attrs));
	अगर (!buffer->access->set_length)
		attr[0] = &dev_attr_length_ro.attr;

	अगर (buffer->access->flags & INDIO_BUFFER_FLAG_FIXED_WATERMARK)
		attr[2] = &dev_attr_watermark_ro.attr;

	अगर (buffer->attrs)
		स_नकल(&attr[ARRAY_SIZE(iio_buffer_attrs)], buffer->attrs,
		       माप(काष्ठा attribute *) * buffer_attrcount);

	buffer_attrcount += ARRAY_SIZE(iio_buffer_attrs);

	क्रम (i = 0; i < buffer_attrcount; i++) अणु
		काष्ठा attribute *wrapped;

		wrapped = iio_buffer_wrap_attr(buffer, attr[i]);
		अगर (!wrapped) अणु
			ret = -ENOMEM;
			जाओ error_मुक्त_scan_mask;
		पूर्ण
		attr[i] = wrapped;
	पूर्ण

	attrn = 0;
	list_क्रम_each_entry(p, &buffer->buffer_attr_list, l)
		attr[attrn++] = &p->dev_attr.attr;

	buffer->buffer_group.name = kaप्र_लिखो(GFP_KERNEL, "buffer%d", index);
	अगर (!buffer->buffer_group.name) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_buffer_attrs;
	पूर्ण

	buffer->buffer_group.attrs = attr;

	ret = iio_device_रेजिस्टर_sysfs_group(indio_dev, &buffer->buffer_group);
	अगर (ret)
		जाओ error_मुक्त_buffer_attr_group_name;

	/* we only need to रेजिस्टर the legacy groups क्रम the first buffer */
	अगर (index > 0)
		वापस 0;

	ret = iio_buffer_रेजिस्टर_legacy_sysfs_groups(indio_dev, attr,
						      buffer_attrcount,
						      scan_el_attrcount);
	अगर (ret)
		जाओ error_मुक्त_buffer_attr_group_name;

	वापस 0;

error_मुक्त_buffer_attr_group_name:
	kमुक्त(buffer->buffer_group.name);
error_मुक्त_buffer_attrs:
	kमुक्त(buffer->buffer_group.attrs);
error_मुक्त_scan_mask:
	biपंचांगap_मुक्त(buffer->scan_mask);
error_cleanup_dynamic:
	iio_मुक्त_chan_devattr_list(&buffer->buffer_attr_list);

	वापस ret;
पूर्ण

अटल व्योम __iio_buffer_मुक्त_sysfs_and_mask(काष्ठा iio_buffer *buffer)
अणु
	biपंचांगap_मुक्त(buffer->scan_mask);
	kमुक्त(buffer->buffer_group.name);
	kमुक्त(buffer->buffer_group.attrs);
	iio_मुक्त_chan_devattr_list(&buffer->buffer_attr_list);
पूर्ण

पूर्णांक iio_buffers_alloc_sysfs_and_mask(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	स्थिर काष्ठा iio_chan_spec *channels;
	काष्ठा iio_buffer *buffer;
	पूर्णांक unwind_idx;
	पूर्णांक ret, i;
	माप_प्रकार sz;

	channels = indio_dev->channels;
	अगर (channels) अणु
		पूर्णांक ml = indio_dev->masklength;

		क्रम (i = 0; i < indio_dev->num_channels; i++)
			ml = max(ml, channels[i].scan_index + 1);
		indio_dev->masklength = ml;
	पूर्ण

	अगर (!iio_dev_opaque->attached_buffers_cnt)
		वापस 0;

	क्रम (i = 0; i < iio_dev_opaque->attached_buffers_cnt; i++) अणु
		buffer = iio_dev_opaque->attached_buffers[i];
		ret = __iio_buffer_alloc_sysfs_and_mask(buffer, indio_dev, i);
		अगर (ret) अणु
			unwind_idx = i;
			जाओ error_unwind_sysfs_and_mask;
		पूर्ण
	पूर्ण
	unwind_idx = iio_dev_opaque->attached_buffers_cnt - 1;

	sz = माप(*(iio_dev_opaque->buffer_ioctl_handler));
	iio_dev_opaque->buffer_ioctl_handler = kzalloc(sz, GFP_KERNEL);
	अगर (!iio_dev_opaque->buffer_ioctl_handler) अणु
		ret = -ENOMEM;
		जाओ error_unwind_sysfs_and_mask;
	पूर्ण

	iio_dev_opaque->buffer_ioctl_handler->ioctl = iio_device_buffer_ioctl;
	iio_device_ioctl_handler_रेजिस्टर(indio_dev,
					  iio_dev_opaque->buffer_ioctl_handler);

	वापस 0;

error_unwind_sysfs_and_mask:
	क्रम (; unwind_idx >= 0; unwind_idx--) अणु
		buffer = iio_dev_opaque->attached_buffers[unwind_idx];
		__iio_buffer_मुक्त_sysfs_and_mask(buffer);
	पूर्ण
	वापस ret;
पूर्ण

व्योम iio_buffers_मुक्त_sysfs_and_mask(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_buffer *buffer;
	पूर्णांक i;

	अगर (!iio_dev_opaque->attached_buffers_cnt)
		वापस;

	iio_device_ioctl_handler_unरेजिस्टर(iio_dev_opaque->buffer_ioctl_handler);
	kमुक्त(iio_dev_opaque->buffer_ioctl_handler);

	iio_buffer_unरेजिस्टर_legacy_sysfs_groups(indio_dev);

	क्रम (i = iio_dev_opaque->attached_buffers_cnt - 1; i >= 0; i--) अणु
		buffer = iio_dev_opaque->attached_buffers[i];
		__iio_buffer_मुक्त_sysfs_and_mask(buffer);
	पूर्ण
पूर्ण

/**
 * iio_validate_scan_mask_onehot() - Validates that exactly one channel is selected
 * @indio_dev: the iio device
 * @mask: scan mask to be checked
 *
 * Return true अगर exactly one bit is set in the scan mask, false otherwise. It
 * can be used क्रम devices where only one channel can be active क्रम sampling at
 * a समय.
 */
bool iio_validate_scan_mask_onehot(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *mask)
अणु
	वापस biपंचांगap_weight(mask, indio_dev->masklength) == 1;
पूर्ण
EXPORT_SYMBOL_GPL(iio_validate_scan_mask_onehot);

अटल स्थिर व्योम *iio_demux(काष्ठा iio_buffer *buffer,
				 स्थिर व्योम *datain)
अणु
	काष्ठा iio_demux_table *t;

	अगर (list_empty(&buffer->demux_list))
		वापस datain;
	list_क्रम_each_entry(t, &buffer->demux_list, l)
		स_नकल(buffer->demux_bounce + t->to,
		       datain + t->from, t->length);

	वापस buffer->demux_bounce;
पूर्ण

अटल पूर्णांक iio_push_to_buffer(काष्ठा iio_buffer *buffer, स्थिर व्योम *data)
अणु
	स्थिर व्योम *dataout = iio_demux(buffer, data);
	पूर्णांक ret;

	ret = buffer->access->store_to(buffer, dataout);
	अगर (ret)
		वापस ret;

	/*
	 * We can't just test क्रम watermark to decide अगर we wake the poll queue
	 * because पढ़ो may request less samples than the watermark.
	 */
	wake_up_पूर्णांकerruptible_poll(&buffer->pollq, EPOLLIN | EPOLLRDNORM);
	वापस 0;
पूर्ण

/**
 * iio_push_to_buffers() - push to a रेजिस्टरed buffer.
 * @indio_dev:		iio_dev काष्ठाure क्रम device.
 * @data:		Full scan.
 */
पूर्णांक iio_push_to_buffers(काष्ठा iio_dev *indio_dev, स्थिर व्योम *data)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	पूर्णांक ret;
	काष्ठा iio_buffer *buf;

	list_क्रम_each_entry(buf, &iio_dev_opaque->buffer_list, buffer_list) अणु
		ret = iio_push_to_buffer(buf, data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iio_push_to_buffers);

/**
 * iio_buffer_release() - Free a buffer's resources
 * @ref: Poपूर्णांकer to the kref embedded in the iio_buffer काष्ठा
 *
 * This function is called when the last reference to the buffer has been
 * dropped. It will typically मुक्त all resources allocated by the buffer. Do not
 * call this function manually, always use iio_buffer_put() when करोne using a
 * buffer.
 */
अटल व्योम iio_buffer_release(काष्ठा kref *ref)
अणु
	काष्ठा iio_buffer *buffer = container_of(ref, काष्ठा iio_buffer, ref);

	buffer->access->release(buffer);
पूर्ण

/**
 * iio_buffer_get() - Grab a reference to the buffer
 * @buffer: The buffer to grab a reference क्रम, may be शून्य
 *
 * Returns the poपूर्णांकer to the buffer that was passed पूर्णांकo the function.
 */
काष्ठा iio_buffer *iio_buffer_get(काष्ठा iio_buffer *buffer)
अणु
	अगर (buffer)
		kref_get(&buffer->ref);

	वापस buffer;
पूर्ण
EXPORT_SYMBOL_GPL(iio_buffer_get);

/**
 * iio_buffer_put() - Release the reference to the buffer
 * @buffer: The buffer to release the reference क्रम, may be शून्य
 */
व्योम iio_buffer_put(काष्ठा iio_buffer *buffer)
अणु
	अगर (buffer)
		kref_put(&buffer->ref, iio_buffer_release);
पूर्ण
EXPORT_SYMBOL_GPL(iio_buffer_put);

/**
 * iio_device_attach_buffer - Attach a buffer to a IIO device
 * @indio_dev: The device the buffer should be attached to
 * @buffer: The buffer to attach to the device
 *
 * Return 0 अगर successful, negative अगर error.
 *
 * This function attaches a buffer to a IIO device. The buffer stays attached to
 * the device until the device is मुक्तd. For legacy reasons, the first attached
 * buffer will also be asचिन्हित to 'indio_dev->buffer'.
 * The array allocated here, will be मुक्त'd via the iio_device_detach_buffers()
 * call which is handled by the iio_device_मुक्त().
 */
पूर्णांक iio_device_attach_buffer(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_buffer *buffer)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_buffer **new, **old = iio_dev_opaque->attached_buffers;
	अचिन्हित पूर्णांक cnt = iio_dev_opaque->attached_buffers_cnt;

	cnt++;

	new = kपुनः_स्मृति(old, माप(*new) * cnt, GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;
	iio_dev_opaque->attached_buffers = new;

	buffer = iio_buffer_get(buffer);

	/* first buffer is legacy; attach it to the IIO device directly */
	अगर (!indio_dev->buffer)
		indio_dev->buffer = buffer;

	iio_dev_opaque->attached_buffers[cnt - 1] = buffer;
	iio_dev_opaque->attached_buffers_cnt = cnt;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iio_device_attach_buffer);
