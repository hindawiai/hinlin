<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/mutex.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/buffer_impl.h>
#समावेश <linux/sched.h>
#समावेश <linux/poll.h>

काष्ठा iio_kfअगरo अणु
	काष्ठा iio_buffer buffer;
	काष्ठा kfअगरo kf;
	काष्ठा mutex user_lock;
	पूर्णांक update_needed;
पूर्ण;

#घोषणा iio_to_kfअगरo(r) container_of(r, काष्ठा iio_kfअगरo, buffer)

अटल अंतरभूत पूर्णांक __iio_allocate_kfअगरo(काष्ठा iio_kfअगरo *buf,
			माप_प्रकार bytes_per_datum, अचिन्हित पूर्णांक length)
अणु
	अगर ((length == 0) || (bytes_per_datum == 0))
		वापस -EINVAL;

	/*
	 * Make sure we करोn't overflow an अचिन्हित पूर्णांक after kfअगरo rounds up to
	 * the next घातer of 2.
	 */
	अगर (roundup_घात_of_two(length) > अच_पूर्णांक_उच्च / bytes_per_datum)
		वापस -EINVAL;

	वापस __kfअगरo_alloc((काष्ठा __kfअगरo *)&buf->kf, length,
			     bytes_per_datum, GFP_KERNEL);
पूर्ण

अटल पूर्णांक iio_request_update_kfअगरo(काष्ठा iio_buffer *r)
अणु
	पूर्णांक ret = 0;
	काष्ठा iio_kfअगरo *buf = iio_to_kfअगरo(r);

	mutex_lock(&buf->user_lock);
	अगर (buf->update_needed) अणु
		kfअगरo_मुक्त(&buf->kf);
		ret = __iio_allocate_kfअगरo(buf, buf->buffer.bytes_per_datum,
				   buf->buffer.length);
		अगर (ret >= 0)
			buf->update_needed = false;
	पूर्ण अन्यथा अणु
		kfअगरo_reset_out(&buf->kf);
	पूर्ण
	mutex_unlock(&buf->user_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक iio_mark_update_needed_kfअगरo(काष्ठा iio_buffer *r)
अणु
	काष्ठा iio_kfअगरo *kf = iio_to_kfअगरo(r);
	kf->update_needed = true;
	वापस 0;
पूर्ण

अटल पूर्णांक iio_set_bytes_per_datum_kfअगरo(काष्ठा iio_buffer *r, माप_प्रकार bpd)
अणु
	अगर (r->bytes_per_datum != bpd) अणु
		r->bytes_per_datum = bpd;
		iio_mark_update_needed_kfअगरo(r);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iio_set_length_kfअगरo(काष्ठा iio_buffer *r, अचिन्हित पूर्णांक length)
अणु
	/* Aव्योम an invalid state */
	अगर (length < 2)
		length = 2;
	अगर (r->length != length) अणु
		r->length = length;
		iio_mark_update_needed_kfअगरo(r);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iio_store_to_kfअगरo(काष्ठा iio_buffer *r,
			      स्थिर व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा iio_kfअगरo *kf = iio_to_kfअगरo(r);
	ret = kfअगरo_in(&kf->kf, data, 1);
	अगर (ret != 1)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक iio_पढ़ो_kfअगरo(काष्ठा iio_buffer *r, माप_प्रकार n, अक्षर __user *buf)
अणु
	पूर्णांक ret, copied;
	काष्ठा iio_kfअगरo *kf = iio_to_kfअगरo(r);

	अगर (mutex_lock_पूर्णांकerruptible(&kf->user_lock))
		वापस -ERESTARTSYS;

	अगर (!kfअगरo_initialized(&kf->kf) || n < kfअगरo_esize(&kf->kf))
		ret = -EINVAL;
	अन्यथा
		ret = kfअगरo_to_user(&kf->kf, buf, n, &copied);
	mutex_unlock(&kf->user_lock);
	अगर (ret < 0)
		वापस ret;

	वापस copied;
पूर्ण

अटल माप_प्रकार iio_kfअगरo_buf_data_available(काष्ठा iio_buffer *r)
अणु
	काष्ठा iio_kfअगरo *kf = iio_to_kfअगरo(r);
	माप_प्रकार samples;

	mutex_lock(&kf->user_lock);
	samples = kfअगरo_len(&kf->kf);
	mutex_unlock(&kf->user_lock);

	वापस samples;
पूर्ण

अटल व्योम iio_kfअगरo_buffer_release(काष्ठा iio_buffer *buffer)
अणु
	काष्ठा iio_kfअगरo *kf = iio_to_kfअगरo(buffer);

	mutex_destroy(&kf->user_lock);
	kfअगरo_मुक्त(&kf->kf);
	kमुक्त(kf);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_access_funcs kfअगरo_access_funcs = अणु
	.store_to = &iio_store_to_kfअगरo,
	.पढ़ो = &iio_पढ़ो_kfअगरo,
	.data_available = iio_kfअगरo_buf_data_available,
	.request_update = &iio_request_update_kfअगरo,
	.set_bytes_per_datum = &iio_set_bytes_per_datum_kfअगरo,
	.set_length = &iio_set_length_kfअगरo,
	.release = &iio_kfअगरo_buffer_release,

	.modes = INDIO_BUFFER_SOFTWARE | INDIO_BUFFER_TRIGGERED,
पूर्ण;

काष्ठा iio_buffer *iio_kfअगरo_allocate(व्योम)
अणु
	काष्ठा iio_kfअगरo *kf;

	kf = kzalloc(माप(*kf), GFP_KERNEL);
	अगर (!kf)
		वापस शून्य;

	kf->update_needed = true;
	iio_buffer_init(&kf->buffer);
	kf->buffer.access = &kfअगरo_access_funcs;
	kf->buffer.length = 2;
	mutex_init(&kf->user_lock);

	वापस &kf->buffer;
पूर्ण
EXPORT_SYMBOL(iio_kfअगरo_allocate);

व्योम iio_kfअगरo_मुक्त(काष्ठा iio_buffer *r)
अणु
	iio_buffer_put(r);
पूर्ण
EXPORT_SYMBOL(iio_kfअगरo_मुक्त);

अटल व्योम devm_iio_kfअगरo_release(काष्ठा device *dev, व्योम *res)
अणु
	iio_kfअगरo_मुक्त(*(काष्ठा iio_buffer **)res);
पूर्ण

/**
 * devm_iio_kfअगरo_allocate - Resource-managed iio_kfअगरo_allocate()
 * @dev:		Device to allocate kfअगरo buffer क्रम
 *
 * RETURNS:
 * Poपूर्णांकer to allocated iio_buffer on success, शून्य on failure.
 */
अटल काष्ठा iio_buffer *devm_iio_kfअगरo_allocate(काष्ठा device *dev)
अणु
	काष्ठा iio_buffer **ptr, *r;

	ptr = devres_alloc(devm_iio_kfअगरo_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	r = iio_kfअगरo_allocate();
	अगर (r) अणु
		*ptr = r;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस r;
पूर्ण

/**
 * devm_iio_kfअगरo_buffer_setup_ext - Allocate a kfअगरo buffer & attach it to an IIO device
 * @dev: Device object to which to attach the lअगरe-समय of this kfअगरo buffer
 * @indio_dev: The device the buffer should be attached to
 * @mode_flags: The mode flags क्रम this buffer (INDIO_BUFFER_SOFTWARE and/or
 *		INDIO_BUFFER_TRIGGERED).
 * @setup_ops: The setup_ops required to configure the HW part of the buffer (optional)
 * @buffer_attrs: Extra sysfs buffer attributes क्रम this IIO buffer
 *
 * This function allocates a kfअगरo buffer via devm_iio_kfअगरo_allocate() and
 * attaches it to the IIO device via iio_device_attach_buffer().
 * This is meant to be a bit of a लघु-hand/helper function as there are a few
 * drivers that seem to करो this.
 */
पूर्णांक devm_iio_kfअगरo_buffer_setup_ext(काष्ठा device *dev,
				    काष्ठा iio_dev *indio_dev,
				    पूर्णांक mode_flags,
				    स्थिर काष्ठा iio_buffer_setup_ops *setup_ops,
				    स्थिर काष्ठा attribute **buffer_attrs)
अणु
	काष्ठा iio_buffer *buffer;

	अगर (!mode_flags)
		वापस -EINVAL;

	buffer = devm_iio_kfअगरo_allocate(dev);
	अगर (!buffer)
		वापस -ENOMEM;

	mode_flags &= kfअगरo_access_funcs.modes;

	indio_dev->modes |= mode_flags;
	indio_dev->setup_ops = setup_ops;

	buffer->attrs = buffer_attrs;

	वापस iio_device_attach_buffer(indio_dev, buffer);
पूर्ण
EXPORT_SYMBOL_GPL(devm_iio_kfअगरo_buffer_setup_ext);

MODULE_LICENSE("GPL");
