<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  compress_core.c - compress offload core
 *
 *  Copyright (C) 2011 Intel Corporation
 *  Authors:	Vinod Koul <vinod.koul@linux.पूर्णांकel.com>
 *		Pierre-Louis Bossart <pierre-louis.bossart@linux.पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#घोषणा FORMAT(fmt) "%s: %d: " fmt, __func__, __LINE__
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " FORMAT(fmt)

#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/math64.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/uपन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/compat.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/info.h>
#समावेश <sound/compress_params.h>
#समावेश <sound/compress_offload.h>
#समावेश <sound/compress_driver.h>

/* काष्ठा snd_compr_codec_caps overflows the ioctl bit size क्रम some
 * architectures, so we need to disable the relevant ioctls.
 */
#अगर _IOC_SIZEBITS < 14
#घोषणा COMPR_CODEC_CAPS_OVERFLOW
#पूर्ण_अगर

/* TODO:
 * - add substream support क्रम multiple devices in हाल of
 *	SND_DYNAMIC_MINORS is not used
 * - Multiple node representation
 *	driver should be able to रेजिस्टर multiple nodes
 */

अटल DEFINE_MUTEX(device_mutex);

काष्ठा snd_compr_file अणु
	अचिन्हित दीर्घ caps;
	काष्ठा snd_compr_stream stream;
पूर्ण;

अटल व्योम error_delayed_work(काष्ठा work_काष्ठा *work);

/*
 * a note on stream states used:
 * we use following states in the compressed core
 * SNDRV_PCM_STATE_OPEN: When stream has been खोलोed.
 * SNDRV_PCM_STATE_SETUP: When stream has been initialized. This is करोne by
 *	calling SNDRV_COMPRESS_SET_PARAMS. Running streams will come to this
 *	state at stop by calling SNDRV_COMPRESS_STOP, or at end of drain.
 * SNDRV_PCM_STATE_PREPARED: When a stream has been written to (क्रम
 *	playback only). User after setting up stream ग_लिखोs the data buffer
 *	beक्रमe starting the stream.
 * SNDRV_PCM_STATE_RUNNING: When stream has been started and is
 *	decoding/encoding and rendering/capturing data.
 * SNDRV_PCM_STATE_DRAINING: When stream is draining current data. This is करोne
 *	by calling SNDRV_COMPRESS_DRAIN.
 * SNDRV_PCM_STATE_PAUSED: When stream is छोड़ोd. This is करोne by calling
 *	SNDRV_COMPRESS_PAUSE. It can be stopped or resumed by calling
 *	SNDRV_COMPRESS_STOP or SNDRV_COMPRESS_RESUME respectively.
 */
अटल पूर्णांक snd_compr_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा snd_compr *compr;
	काष्ठा snd_compr_file *data;
	काष्ठा snd_compr_runसमय *runसमय;
	क्रमागत snd_compr_direction dirn;
	पूर्णांक maj = imajor(inode);
	पूर्णांक ret;

	अगर ((f->f_flags & O_ACCMODE) == O_WRONLY)
		dirn = SND_COMPRESS_PLAYBACK;
	अन्यथा अगर ((f->f_flags & O_ACCMODE) == O_RDONLY)
		dirn = SND_COMPRESS_CAPTURE;
	अन्यथा
		वापस -EINVAL;

	अगर (maj == snd_major)
		compr = snd_lookup_minor_data(iminor(inode),
					SNDRV_DEVICE_TYPE_COMPRESS);
	अन्यथा
		वापस -EBADFD;

	अगर (compr == शून्य) अणु
		pr_err("no device data!!!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dirn != compr->direction) अणु
		pr_err("this device doesn't support this direction\n");
		snd_card_unref(compr->card);
		वापस -EINVAL;
	पूर्ण

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		snd_card_unref(compr->card);
		वापस -ENOMEM;
	पूर्ण

	INIT_DELAYED_WORK(&data->stream.error_work, error_delayed_work);

	data->stream.ops = compr->ops;
	data->stream.direction = dirn;
	data->stream.निजी_data = compr->निजी_data;
	data->stream.device = compr;
	runसमय = kzalloc(माप(*runसमय), GFP_KERNEL);
	अगर (!runसमय) अणु
		kमुक्त(data);
		snd_card_unref(compr->card);
		वापस -ENOMEM;
	पूर्ण
	runसमय->state = SNDRV_PCM_STATE_OPEN;
	init_रुकोqueue_head(&runसमय->sleep);
	data->stream.runसमय = runसमय;
	f->निजी_data = (व्योम *)data;
	mutex_lock(&compr->lock);
	ret = compr->ops->खोलो(&data->stream);
	mutex_unlock(&compr->lock);
	अगर (ret) अणु
		kमुक्त(runसमय);
		kमुक्त(data);
	पूर्ण
	snd_card_unref(compr->card);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_compr_मुक्त(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा snd_compr_file *data = f->निजी_data;
	काष्ठा snd_compr_runसमय *runसमय = data->stream.runसमय;

	cancel_delayed_work_sync(&data->stream.error_work);

	चयन (runसमय->state) अणु
	हाल SNDRV_PCM_STATE_RUNNING:
	हाल SNDRV_PCM_STATE_DRAINING:
	हाल SNDRV_PCM_STATE_PAUSED:
		data->stream.ops->trigger(&data->stream, SNDRV_PCM_TRIGGER_STOP);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	data->stream.ops->मुक्त(&data->stream);
	अगर (!data->stream.runसमय->dma_buffer_p)
		kमुक्त(data->stream.runसमय->buffer);
	kमुक्त(data->stream.runसमय);
	kमुक्त(data);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_compr_update_tstamp(काष्ठा snd_compr_stream *stream,
		काष्ठा snd_compr_tstamp *tstamp)
अणु
	अगर (!stream->ops->poपूर्णांकer)
		वापस -ENOTSUPP;
	stream->ops->poपूर्णांकer(stream, tstamp);
	pr_debug("dsp consumed till %d total %d bytes\n",
		tstamp->byte_offset, tstamp->copied_total);
	अगर (stream->direction == SND_COMPRESS_PLAYBACK)
		stream->runसमय->total_bytes_transferred = tstamp->copied_total;
	अन्यथा
		stream->runसमय->total_bytes_available = tstamp->copied_total;
	वापस 0;
पूर्ण

अटल माप_प्रकार snd_compr_calc_avail(काष्ठा snd_compr_stream *stream,
		काष्ठा snd_compr_avail *avail)
अणु
	स_रखो(avail, 0, माप(*avail));
	snd_compr_update_tstamp(stream, &avail->tstamp);
	/* Still need to वापस avail even अगर tstamp can't be filled in */

	अगर (stream->runसमय->total_bytes_available == 0 &&
			stream->runसमय->state == SNDRV_PCM_STATE_SETUP &&
			stream->direction == SND_COMPRESS_PLAYBACK) अणु
		pr_debug("detected init and someone forgot to do a write\n");
		वापस stream->runसमय->buffer_size;
	पूर्ण
	pr_debug("app wrote %lld, DSP consumed %lld\n",
			stream->runसमय->total_bytes_available,
			stream->runसमय->total_bytes_transferred);
	अगर (stream->runसमय->total_bytes_available ==
				stream->runसमय->total_bytes_transferred) अणु
		अगर (stream->direction == SND_COMPRESS_PLAYBACK) अणु
			pr_debug("both pointers are same, returning full avail\n");
			वापस stream->runसमय->buffer_size;
		पूर्ण अन्यथा अणु
			pr_debug("both pointers are same, returning no avail\n");
			वापस 0;
		पूर्ण
	पूर्ण

	avail->avail = stream->runसमय->total_bytes_available -
			stream->runसमय->total_bytes_transferred;
	अगर (stream->direction == SND_COMPRESS_PLAYBACK)
		avail->avail = stream->runसमय->buffer_size - avail->avail;

	pr_debug("ret avail as %lld\n", avail->avail);
	वापस avail->avail;
पूर्ण

अटल अंतरभूत माप_प्रकार snd_compr_get_avail(काष्ठा snd_compr_stream *stream)
अणु
	काष्ठा snd_compr_avail avail;

	वापस snd_compr_calc_avail(stream, &avail);
पूर्ण

अटल पूर्णांक
snd_compr_ioctl_avail(काष्ठा snd_compr_stream *stream, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_compr_avail ioctl_avail;
	माप_प्रकार avail;

	avail = snd_compr_calc_avail(stream, &ioctl_avail);
	ioctl_avail.avail = avail;

	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_OPEN:
		वापस -EBADFD;
	हाल SNDRV_PCM_STATE_XRUN:
		वापस -EPIPE;
	शेष:
		अवरोध;
	पूर्ण

	अगर (copy_to_user((__u64 __user *)arg,
				&ioctl_avail, माप(ioctl_avail)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_compr_ग_लिखो_data(काष्ठा snd_compr_stream *stream,
	       स्थिर अक्षर __user *buf, माप_प्रकार count)
अणु
	व्योम *dstn;
	माप_प्रकार copy;
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;
	/* 64-bit Modulus */
	u64 app_poपूर्णांकer = भाग64_u64(runसमय->total_bytes_available,
				    runसमय->buffer_size);
	app_poपूर्णांकer = runसमय->total_bytes_available -
		      (app_poपूर्णांकer * runसमय->buffer_size);

	dstn = runसमय->buffer + app_poपूर्णांकer;
	pr_debug("copying %ld at %lld\n",
			(अचिन्हित दीर्घ)count, app_poपूर्णांकer);
	अगर (count < runसमय->buffer_size - app_poपूर्णांकer) अणु
		अगर (copy_from_user(dstn, buf, count))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		copy = runसमय->buffer_size - app_poपूर्णांकer;
		अगर (copy_from_user(dstn, buf, copy))
			वापस -EFAULT;
		अगर (copy_from_user(runसमय->buffer, buf + copy, count - copy))
			वापस -EFAULT;
	पूर्ण
	/* अगर DSP cares, let it know data has been written */
	अगर (stream->ops->ack)
		stream->ops->ack(stream, count);
	वापस count;
पूर्ण

अटल sमाप_प्रकार snd_compr_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा snd_compr_file *data = f->निजी_data;
	काष्ठा snd_compr_stream *stream;
	माप_प्रकार avail;
	पूर्णांक retval;

	अगर (snd_BUG_ON(!data))
		वापस -EFAULT;

	stream = &data->stream;
	mutex_lock(&stream->device->lock);
	/* ग_लिखो is allowed when stream is running or has been steup */
	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_SETUP:
	हाल SNDRV_PCM_STATE_PREPARED:
	हाल SNDRV_PCM_STATE_RUNNING:
		अवरोध;
	शेष:
		mutex_unlock(&stream->device->lock);
		वापस -EBADFD;
	पूर्ण

	avail = snd_compr_get_avail(stream);
	pr_debug("avail returned %ld\n", (अचिन्हित दीर्घ)avail);
	/* calculate how much we can ग_लिखो to buffer */
	अगर (avail > count)
		avail = count;

	अगर (stream->ops->copy) अणु
		अक्षर __user* cbuf = (अक्षर __user*)buf;
		retval = stream->ops->copy(stream, cbuf, avail);
	पूर्ण अन्यथा अणु
		retval = snd_compr_ग_लिखो_data(stream, buf, avail);
	पूर्ण
	अगर (retval > 0)
		stream->runसमय->total_bytes_available += retval;

	/* जबतक initiating the stream, ग_लिखो should be called beक्रमe START
	 * call, so in setup move state */
	अगर (stream->runसमय->state == SNDRV_PCM_STATE_SETUP) अणु
		stream->runसमय->state = SNDRV_PCM_STATE_PREPARED;
		pr_debug("stream prepared, Houston we are good to go\n");
	पूर्ण

	mutex_unlock(&stream->device->lock);
	वापस retval;
पूर्ण


अटल sमाप_प्रकार snd_compr_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
		माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा snd_compr_file *data = f->निजी_data;
	काष्ठा snd_compr_stream *stream;
	माप_प्रकार avail;
	पूर्णांक retval;

	अगर (snd_BUG_ON(!data))
		वापस -EFAULT;

	stream = &data->stream;
	mutex_lock(&stream->device->lock);

	/* पढ़ो is allowed when stream is running, छोड़ोd, draining and setup
	 * (yes setup is state which we transition to after stop, so अगर user
	 * wants to पढ़ो data after stop we allow that)
	 */
	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_OPEN:
	हाल SNDRV_PCM_STATE_PREPARED:
	हाल SNDRV_PCM_STATE_SUSPENDED:
	हाल SNDRV_PCM_STATE_DISCONNECTED:
		retval = -EBADFD;
		जाओ out;
	हाल SNDRV_PCM_STATE_XRUN:
		retval = -EPIPE;
		जाओ out;
	पूर्ण

	avail = snd_compr_get_avail(stream);
	pr_debug("avail returned %ld\n", (अचिन्हित दीर्घ)avail);
	/* calculate how much we can पढ़ो from buffer */
	अगर (avail > count)
		avail = count;

	अगर (stream->ops->copy) अणु
		retval = stream->ops->copy(stream, buf, avail);
	पूर्ण अन्यथा अणु
		retval = -ENXIO;
		जाओ out;
	पूर्ण
	अगर (retval > 0)
		stream->runसमय->total_bytes_transferred += retval;

out:
	mutex_unlock(&stream->device->lock);
	वापस retval;
पूर्ण

अटल पूर्णांक snd_compr_mmap(काष्ठा file *f, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस -ENXIO;
पूर्ण

अटल __poll_t snd_compr_get_poll(काष्ठा snd_compr_stream *stream)
अणु
	अगर (stream->direction == SND_COMPRESS_PLAYBACK)
		वापस EPOLLOUT | EPOLLWRNORM;
	अन्यथा
		वापस EPOLLIN | EPOLLRDNORM;
पूर्ण

अटल __poll_t snd_compr_poll(काष्ठा file *f, poll_table *रुको)
अणु
	काष्ठा snd_compr_file *data = f->निजी_data;
	काष्ठा snd_compr_stream *stream;
	माप_प्रकार avail;
	__poll_t retval = 0;

	अगर (snd_BUG_ON(!data))
		वापस EPOLLERR;

	stream = &data->stream;

	mutex_lock(&stream->device->lock);

	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_OPEN:
	हाल SNDRV_PCM_STATE_XRUN:
		retval = snd_compr_get_poll(stream) | EPOLLERR;
		जाओ out;
	शेष:
		अवरोध;
	पूर्ण

	poll_रुको(f, &stream->runसमय->sleep, रुको);

	avail = snd_compr_get_avail(stream);
	pr_debug("avail is %ld\n", (अचिन्हित दीर्घ)avail);
	/* check अगर we have at least one fragment to fill */
	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_DRAINING:
		/* stream has been woken up after drain is complete
		 * draining करोne so set stream state to stopped
		 */
		retval = snd_compr_get_poll(stream);
		stream->runसमय->state = SNDRV_PCM_STATE_SETUP;
		अवरोध;
	हाल SNDRV_PCM_STATE_RUNNING:
	हाल SNDRV_PCM_STATE_PREPARED:
	हाल SNDRV_PCM_STATE_PAUSED:
		अगर (avail >= stream->runसमय->fragment_size)
			retval = snd_compr_get_poll(stream);
		अवरोध;
	शेष:
		retval = snd_compr_get_poll(stream) | EPOLLERR;
		अवरोध;
	पूर्ण
out:
	mutex_unlock(&stream->device->lock);
	वापस retval;
पूर्ण

अटल पूर्णांक
snd_compr_get_caps(काष्ठा snd_compr_stream *stream, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक retval;
	काष्ठा snd_compr_caps caps;

	अगर (!stream->ops->get_caps)
		वापस -ENXIO;

	स_रखो(&caps, 0, माप(caps));
	retval = stream->ops->get_caps(stream, &caps);
	अगर (retval)
		जाओ out;
	अगर (copy_to_user((व्योम __user *)arg, &caps, माप(caps)))
		retval = -EFAULT;
out:
	वापस retval;
पूर्ण

#अगर_अघोषित COMPR_CODEC_CAPS_OVERFLOW
अटल पूर्णांक
snd_compr_get_codec_caps(काष्ठा snd_compr_stream *stream, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक retval;
	काष्ठा snd_compr_codec_caps *caps;

	अगर (!stream->ops->get_codec_caps)
		वापस -ENXIO;

	caps = kzalloc(माप(*caps), GFP_KERNEL);
	अगर (!caps)
		वापस -ENOMEM;

	retval = stream->ops->get_codec_caps(stream, caps);
	अगर (retval)
		जाओ out;
	अगर (copy_to_user((व्योम __user *)arg, caps, माप(*caps)))
		retval = -EFAULT;

out:
	kमुक्त(caps);
	वापस retval;
पूर्ण
#पूर्ण_अगर /* !COMPR_CODEC_CAPS_OVERFLOW */

पूर्णांक snd_compr_दो_स्मृति_pages(काष्ठा snd_compr_stream *stream, माप_प्रकार size)
अणु
	काष्ठा snd_dma_buffer *dmab;
	पूर्णांक ret;

	अगर (snd_BUG_ON(!(stream) || !(stream)->runसमय))
		वापस -EINVAL;
	dmab = kzalloc(माप(*dmab), GFP_KERNEL);
	अगर (!dmab)
		वापस -ENOMEM;
	dmab->dev = stream->dma_buffer.dev;
	ret = snd_dma_alloc_pages(dmab->dev.type, dmab->dev.dev, size, dmab);
	अगर (ret < 0) अणु
		kमुक्त(dmab);
		वापस ret;
	पूर्ण

	snd_compr_set_runसमय_buffer(stream, dmab);
	stream->runसमय->dma_bytes = size;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(snd_compr_दो_स्मृति_pages);

पूर्णांक snd_compr_मुक्त_pages(काष्ठा snd_compr_stream *stream)
अणु
	काष्ठा snd_compr_runसमय *runसमय;

	अगर (snd_BUG_ON(!(stream) || !(stream)->runसमय))
		वापस -EINVAL;
	runसमय = stream->runसमय;
	अगर (runसमय->dma_area == शून्य)
		वापस 0;
	अगर (runसमय->dma_buffer_p != &stream->dma_buffer) अणु
		/* It's a newly allocated buffer. Release it now. */
		snd_dma_मुक्त_pages(runसमय->dma_buffer_p);
		kमुक्त(runसमय->dma_buffer_p);
	पूर्ण

	snd_compr_set_runसमय_buffer(stream, शून्य);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_compr_मुक्त_pages);

/* revisit this with snd_pcm_pपुनः_स्मृतिate_xxx */
अटल पूर्णांक snd_compr_allocate_buffer(काष्ठा snd_compr_stream *stream,
		काष्ठा snd_compr_params *params)
अणु
	अचिन्हित पूर्णांक buffer_size;
	व्योम *buffer = शून्य;

	buffer_size = params->buffer.fragment_size * params->buffer.fragments;
	अगर (stream->ops->copy) अणु
		buffer = शून्य;
		/* अगर copy is defined the driver will be required to copy
		 * the data from core
		 */
	पूर्ण अन्यथा अणु
		अगर (stream->runसमय->dma_buffer_p) अणु

			अगर (buffer_size > stream->runसमय->dma_buffer_p->bytes)
				dev_err(&stream->device->dev,
						"Not enough DMA buffer");
			अन्यथा
				buffer = stream->runसमय->dma_buffer_p->area;

		पूर्ण अन्यथा अणु
			buffer = kदो_स्मृति(buffer_size, GFP_KERNEL);
		पूर्ण

		अगर (!buffer)
			वापस -ENOMEM;
	पूर्ण
	stream->runसमय->fragment_size = params->buffer.fragment_size;
	stream->runसमय->fragments = params->buffer.fragments;
	stream->runसमय->buffer = buffer;
	stream->runसमय->buffer_size = buffer_size;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_compress_check_input(काष्ठा snd_compr_params *params)
अणु
	/* first let's check the buffer parameter's */
	अगर (params->buffer.fragment_size == 0 ||
	    params->buffer.fragments > U32_MAX / params->buffer.fragment_size ||
	    params->buffer.fragments == 0)
		वापस -EINVAL;

	/* now codec parameters */
	अगर (params->codec.id == 0 || params->codec.id > SND_AUDIOCODEC_MAX)
		वापस -EINVAL;

	अगर (params->codec.ch_in == 0 || params->codec.ch_out == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_compr_set_params(काष्ठा snd_compr_stream *stream, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_compr_params *params;
	पूर्णांक retval;

	अगर (stream->runसमय->state == SNDRV_PCM_STATE_OPEN) अणु
		/*
		 * we should allow parameter change only when stream has been
		 * खोलोed not in other हालs
		 */
		params = memdup_user((व्योम __user *)arg, माप(*params));
		अगर (IS_ERR(params))
			वापस PTR_ERR(params);

		retval = snd_compress_check_input(params);
		अगर (retval)
			जाओ out;

		retval = snd_compr_allocate_buffer(stream, params);
		अगर (retval) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण

		retval = stream->ops->set_params(stream, params);
		अगर (retval)
			जाओ out;

		stream->metadata_set = false;
		stream->next_track = false;

		stream->runसमय->state = SNDRV_PCM_STATE_SETUP;
	पूर्ण अन्यथा अणु
		वापस -EPERM;
	पूर्ण
out:
	kमुक्त(params);
	वापस retval;
पूर्ण

अटल पूर्णांक
snd_compr_get_params(काष्ठा snd_compr_stream *stream, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_codec *params;
	पूर्णांक retval;

	अगर (!stream->ops->get_params)
		वापस -EBADFD;

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;
	retval = stream->ops->get_params(stream, params);
	अगर (retval)
		जाओ out;
	अगर (copy_to_user((अक्षर __user *)arg, params, माप(*params)))
		retval = -EFAULT;

out:
	kमुक्त(params);
	वापस retval;
पूर्ण

अटल पूर्णांक
snd_compr_get_metadata(काष्ठा snd_compr_stream *stream, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_compr_metadata metadata;
	पूर्णांक retval;

	अगर (!stream->ops->get_metadata)
		वापस -ENXIO;

	अगर (copy_from_user(&metadata, (व्योम __user *)arg, माप(metadata)))
		वापस -EFAULT;

	retval = stream->ops->get_metadata(stream, &metadata);
	अगर (retval != 0)
		वापस retval;

	अगर (copy_to_user((व्योम __user *)arg, &metadata, माप(metadata)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_compr_set_metadata(काष्ठा snd_compr_stream *stream, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_compr_metadata metadata;
	पूर्णांक retval;

	अगर (!stream->ops->set_metadata)
		वापस -ENXIO;
	/*
	* we should allow parameter change only when stream has been
	* खोलोed not in other हालs
	*/
	अगर (copy_from_user(&metadata, (व्योम __user *)arg, माप(metadata)))
		वापस -EFAULT;

	retval = stream->ops->set_metadata(stream, &metadata);
	stream->metadata_set = true;

	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक
snd_compr_tstamp(काष्ठा snd_compr_stream *stream, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_compr_tstamp tstamp = अणु0पूर्ण;
	पूर्णांक ret;

	ret = snd_compr_update_tstamp(stream, &tstamp);
	अगर (ret == 0)
		ret = copy_to_user((काष्ठा snd_compr_tstamp __user *)arg,
			&tstamp, माप(tstamp)) ? -EFAULT : 0;
	वापस ret;
पूर्ण

अटल पूर्णांक snd_compr_छोड़ो(काष्ठा snd_compr_stream *stream)
अणु
	पूर्णांक retval;

	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_RUNNING:
		retval = stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_PAUSE_PUSH);
		अगर (!retval)
			stream->runसमय->state = SNDRV_PCM_STATE_PAUSED;
		अवरोध;
	हाल SNDRV_PCM_STATE_DRAINING:
		अगर (!stream->device->use_छोड़ो_in_draining)
			वापस -EPERM;
		retval = stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_PAUSE_PUSH);
		अगर (!retval)
			stream->छोड़ो_in_draining = true;
		अवरोध;
	शेष:
		वापस -EPERM;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक snd_compr_resume(काष्ठा snd_compr_stream *stream)
अणु
	पूर्णांक retval;

	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_PAUSED:
		retval = stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_PAUSE_RELEASE);
		अगर (!retval)
			stream->runसमय->state = SNDRV_PCM_STATE_RUNNING;
		अवरोध;
	हाल SNDRV_PCM_STATE_DRAINING:
		अगर (!stream->छोड़ो_in_draining)
			वापस -EPERM;
		retval = stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_PAUSE_RELEASE);
		अगर (!retval)
			stream->छोड़ो_in_draining = false;
		अवरोध;
	शेष:
		वापस -EPERM;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक snd_compr_start(काष्ठा snd_compr_stream *stream)
अणु
	पूर्णांक retval;

	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_SETUP:
		अगर (stream->direction != SND_COMPRESS_CAPTURE)
			वापस -EPERM;
		अवरोध;
	हाल SNDRV_PCM_STATE_PREPARED:
		अवरोध;
	शेष:
		वापस -EPERM;
	पूर्ण

	retval = stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_START);
	अगर (!retval)
		stream->runसमय->state = SNDRV_PCM_STATE_RUNNING;
	वापस retval;
पूर्ण

अटल पूर्णांक snd_compr_stop(काष्ठा snd_compr_stream *stream)
अणु
	पूर्णांक retval;

	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_OPEN:
	हाल SNDRV_PCM_STATE_SETUP:
	हाल SNDRV_PCM_STATE_PREPARED:
		वापस -EPERM;
	शेष:
		अवरोध;
	पूर्ण

	retval = stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_STOP);
	अगर (!retval) अणु
		/* clear flags and stop any drain रुको */
		stream->partial_drain = false;
		stream->metadata_set = false;
		stream->छोड़ो_in_draining = false;
		snd_compr_drain_notअगरy(stream);
		stream->runसमय->total_bytes_available = 0;
		stream->runसमय->total_bytes_transferred = 0;
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम error_delayed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_compr_stream *stream;

	stream = container_of(work, काष्ठा snd_compr_stream, error_work.work);

	mutex_lock(&stream->device->lock);

	stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_STOP);
	wake_up(&stream->runसमय->sleep);

	mutex_unlock(&stream->device->lock);
पूर्ण

/*
 * snd_compr_stop_error: Report a fatal error on a stream
 * @stream: poपूर्णांकer to stream
 * @state: state to transition the stream to
 *
 * Stop the stream and set its state.
 *
 * Should be called with compressed device lock held.
 */
पूर्णांक snd_compr_stop_error(काष्ठा snd_compr_stream *stream,
			 snd_pcm_state_t state)
अणु
	अगर (stream->runसमय->state == state)
		वापस 0;

	stream->runसमय->state = state;

	pr_debug("Changing state to: %d\n", state);

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &stream->error_work, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_compr_stop_error);

अटल पूर्णांक snd_compress_रुको_क्रम_drain(काष्ठा snd_compr_stream *stream)
अणु
	पूर्णांक ret;

	/*
	 * We are called with lock held. So drop the lock जबतक we रुको क्रम
	 * drain complete notअगरication from the driver
	 *
	 * It is expected that driver will notअगरy the drain completion and then
	 * stream will be moved to SETUP state, even अगर draining resulted in an
	 * error. We can trigger next track after this.
	 */
	stream->runसमय->state = SNDRV_PCM_STATE_DRAINING;
	mutex_unlock(&stream->device->lock);

	/* we रुको क्रम drain to complete here, drain can वापस when
	 * पूर्णांकerruption occurred, रुको वापसed error or success.
	 * For the first two हालs we करोn't करो anything dअगरferent here and
	 * वापस after waking up
	 */

	ret = रुको_event_पूर्णांकerruptible(stream->runसमय->sleep,
			(stream->runसमय->state != SNDRV_PCM_STATE_DRAINING));
	अगर (ret == -ERESTARTSYS)
		pr_debug("wait aborted by a signal\n");
	अन्यथा अगर (ret)
		pr_debug("wait for drain failed with %d\n", ret);


	wake_up(&stream->runसमय->sleep);
	mutex_lock(&stream->device->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक snd_compr_drain(काष्ठा snd_compr_stream *stream)
अणु
	पूर्णांक retval;

	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_OPEN:
	हाल SNDRV_PCM_STATE_SETUP:
	हाल SNDRV_PCM_STATE_PREPARED:
	हाल SNDRV_PCM_STATE_PAUSED:
		वापस -EPERM;
	हाल SNDRV_PCM_STATE_XRUN:
		वापस -EPIPE;
	शेष:
		अवरोध;
	पूर्ण

	retval = stream->ops->trigger(stream, SND_COMPR_TRIGGER_DRAIN);
	अगर (retval) अणु
		pr_debug("SND_COMPR_TRIGGER_DRAIN failed %d\n", retval);
		wake_up(&stream->runसमय->sleep);
		वापस retval;
	पूर्ण

	वापस snd_compress_रुको_क्रम_drain(stream);
पूर्ण

अटल पूर्णांक snd_compr_next_track(काष्ठा snd_compr_stream *stream)
अणु
	पूर्णांक retval;

	/* only a running stream can transition to next track */
	अगर (stream->runसमय->state != SNDRV_PCM_STATE_RUNNING)
		वापस -EPERM;

	/* next track करोesn't have any meaning क्रम capture streams */
	अगर (stream->direction == SND_COMPRESS_CAPTURE)
		वापस -EPERM;

	/* you can संकेत next track अगर this is पूर्णांकended to be a gapless stream
	 * and current track metadata is set
	 */
	अगर (stream->metadata_set == false)
		वापस -EPERM;

	retval = stream->ops->trigger(stream, SND_COMPR_TRIGGER_NEXT_TRACK);
	अगर (retval != 0)
		वापस retval;
	stream->metadata_set = false;
	stream->next_track = true;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_compr_partial_drain(काष्ठा snd_compr_stream *stream)
अणु
	पूर्णांक retval;

	चयन (stream->runसमय->state) अणु
	हाल SNDRV_PCM_STATE_OPEN:
	हाल SNDRV_PCM_STATE_SETUP:
	हाल SNDRV_PCM_STATE_PREPARED:
	हाल SNDRV_PCM_STATE_PAUSED:
		वापस -EPERM;
	हाल SNDRV_PCM_STATE_XRUN:
		वापस -EPIPE;
	शेष:
		अवरोध;
	पूर्ण

	/* partial drain करोesn't have any meaning क्रम capture streams */
	अगर (stream->direction == SND_COMPRESS_CAPTURE)
		वापस -EPERM;

	/* stream can be drained only when next track has been संकेतled */
	अगर (stream->next_track == false)
		वापस -EPERM;

	stream->partial_drain = true;
	retval = stream->ops->trigger(stream, SND_COMPR_TRIGGER_PARTIAL_DRAIN);
	अगर (retval) अणु
		pr_debug("Partial drain returned failure\n");
		wake_up(&stream->runसमय->sleep);
		वापस retval;
	पूर्ण

	stream->next_track = false;
	वापस snd_compress_रुको_क्रम_drain(stream);
पूर्ण

अटल दीर्घ snd_compr_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_compr_file *data = f->निजी_data;
	काष्ठा snd_compr_stream *stream;
	पूर्णांक retval = -ENOTTY;

	अगर (snd_BUG_ON(!data))
		वापस -EFAULT;

	stream = &data->stream;

	mutex_lock(&stream->device->lock);
	चयन (_IOC_NR(cmd)) अणु
	हाल _IOC_NR(SNDRV_COMPRESS_IOCTL_VERSION):
		retval = put_user(SNDRV_COMPRESS_VERSION,
				(पूर्णांक __user *)arg) ? -EFAULT : 0;
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_GET_CAPS):
		retval = snd_compr_get_caps(stream, arg);
		अवरोध;
#अगर_अघोषित COMPR_CODEC_CAPS_OVERFLOW
	हाल _IOC_NR(SNDRV_COMPRESS_GET_CODEC_CAPS):
		retval = snd_compr_get_codec_caps(stream, arg);
		अवरोध;
#पूर्ण_अगर
	हाल _IOC_NR(SNDRV_COMPRESS_SET_PARAMS):
		retval = snd_compr_set_params(stream, arg);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_GET_PARAMS):
		retval = snd_compr_get_params(stream, arg);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_SET_METADATA):
		retval = snd_compr_set_metadata(stream, arg);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_GET_METADATA):
		retval = snd_compr_get_metadata(stream, arg);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_TSTAMP):
		retval = snd_compr_tstamp(stream, arg);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_AVAIL):
		retval = snd_compr_ioctl_avail(stream, arg);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_PAUSE):
		retval = snd_compr_छोड़ो(stream);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_RESUME):
		retval = snd_compr_resume(stream);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_START):
		retval = snd_compr_start(stream);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_STOP):
		retval = snd_compr_stop(stream);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_DRAIN):
		retval = snd_compr_drain(stream);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_PARTIAL_DRAIN):
		retval = snd_compr_partial_drain(stream);
		अवरोध;
	हाल _IOC_NR(SNDRV_COMPRESS_NEXT_TRACK):
		retval = snd_compr_next_track(stream);
		अवरोध;

	पूर्ण
	mutex_unlock(&stream->device->lock);
	वापस retval;
पूर्ण

/* support of 32bit userspace on 64bit platक्रमms */
#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ snd_compr_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg)
अणु
	वापस snd_compr_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations snd_compr_file_ops = अणु
		.owner =	THIS_MODULE,
		.खोलो =		snd_compr_खोलो,
		.release =	snd_compr_मुक्त,
		.ग_लिखो =	snd_compr_ग_लिखो,
		.पढ़ो =		snd_compr_पढ़ो,
		.unlocked_ioctl = snd_compr_ioctl,
#अगर_घोषित CONFIG_COMPAT
		.compat_ioctl = snd_compr_ioctl_compat,
#पूर्ण_अगर
		.mmap =		snd_compr_mmap,
		.poll =		snd_compr_poll,
पूर्ण;

अटल पूर्णांक snd_compress_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	पूर्णांक ret;
	काष्ठा snd_compr *compr;

	अगर (snd_BUG_ON(!device || !device->device_data))
		वापस -EBADFD;
	compr = device->device_data;

	pr_debug("reg device %s, direction %d\n", compr->name,
			compr->direction);
	/* रेजिस्टर compressed device */
	ret = snd_रेजिस्टर_device(SNDRV_DEVICE_TYPE_COMPRESS,
				  compr->card, compr->device,
				  &snd_compr_file_ops, compr, &compr->dev);
	अगर (ret < 0) अणु
		pr_err("snd_register_device failed %d\n", ret);
		वापस ret;
	पूर्ण
	वापस ret;

पूर्ण

अटल पूर्णांक snd_compress_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा snd_compr *compr;

	compr = device->device_data;
	snd_unरेजिस्टर_device(&compr->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_VERBOSE_PROCFS
अटल व्योम snd_compress_proc_info_पढ़ो(काष्ठा snd_info_entry *entry,
					काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_compr *compr = (काष्ठा snd_compr *)entry->निजी_data;

	snd_iम_लिखो(buffer, "card: %d\n", compr->card->number);
	snd_iम_लिखो(buffer, "device: %d\n", compr->device);
	snd_iम_लिखो(buffer, "stream: %s\n",
			compr->direction == SND_COMPRESS_PLAYBACK
				? "PLAYBACK" : "CAPTURE");
	snd_iम_लिखो(buffer, "id: %s\n", compr->id);
पूर्ण

अटल पूर्णांक snd_compress_proc_init(काष्ठा snd_compr *compr)
अणु
	काष्ठा snd_info_entry *entry;
	अक्षर name[16];

	प्र_लिखो(name, "compr%i", compr->device);
	entry = snd_info_create_card_entry(compr->card, name,
					   compr->card->proc_root);
	अगर (!entry)
		वापस -ENOMEM;
	entry->mode = S_IFसूची | 0555;
	compr->proc_root = entry;

	entry = snd_info_create_card_entry(compr->card, "info",
					   compr->proc_root);
	अगर (entry)
		snd_info_set_text_ops(entry, compr,
				      snd_compress_proc_info_पढ़ो);
	compr->proc_info_entry = entry;

	वापस 0;
पूर्ण

अटल व्योम snd_compress_proc_करोne(काष्ठा snd_compr *compr)
अणु
	snd_info_मुक्त_entry(compr->proc_info_entry);
	compr->proc_info_entry = शून्य;
	snd_info_मुक्त_entry(compr->proc_root);
	compr->proc_root = शून्य;
पूर्ण

अटल अंतरभूत व्योम snd_compress_set_id(काष्ठा snd_compr *compr, स्थिर अक्षर *id)
अणु
	strscpy(compr->id, id, माप(compr->id));
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_compress_proc_init(काष्ठा snd_compr *compr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम snd_compress_proc_करोne(काष्ठा snd_compr *compr)
अणु
पूर्ण

अटल अंतरभूत व्योम snd_compress_set_id(काष्ठा snd_compr *compr, स्थिर अक्षर *id)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_compress_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_compr *compr;

	compr = device->device_data;
	snd_compress_proc_करोne(compr);
	put_device(&compr->dev);
	वापस 0;
पूर्ण

/*
 * snd_compress_new: create new compress device
 * @card: sound card poपूर्णांकer
 * @device: device number
 * @dirn: device direction, should be of type क्रमागत snd_compr_direction
 * @compr: compress device poपूर्णांकer
 */
पूर्णांक snd_compress_new(काष्ठा snd_card *card, पूर्णांक device,
			पूर्णांक dirn, स्थिर अक्षर *id, काष्ठा snd_compr *compr)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_compress_dev_मुक्त,
		.dev_रेजिस्टर = snd_compress_dev_रेजिस्टर,
		.dev_disconnect = snd_compress_dev_disconnect,
	पूर्ण;
	पूर्णांक ret;

	compr->card = card;
	compr->device = device;
	compr->direction = dirn;

	snd_compress_set_id(compr, id);

	snd_device_initialize(&compr->dev, card);
	dev_set_name(&compr->dev, "comprC%iD%i", card->number, device);

	ret = snd_device_new(card, SNDRV_DEV_COMPRESS, compr, &ops);
	अगर (ret == 0)
		snd_compress_proc_init(compr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_compress_new);

अटल पूर्णांक snd_compress_add_device(काष्ठा snd_compr *device)
अणु
	पूर्णांक ret;

	अगर (!device->card)
		वापस -EINVAL;

	/* रेजिस्टर the card */
	ret = snd_card_रेजिस्टर(device->card);
	अगर (ret)
		जाओ out;
	वापस 0;

out:
	pr_err("failed with %d\n", ret);
	वापस ret;

पूर्ण

अटल पूर्णांक snd_compress_हटाओ_device(काष्ठा snd_compr *device)
अणु
	वापस snd_card_मुक्त(device->card);
पूर्ण

/**
 * snd_compress_रेजिस्टर - रेजिस्टर compressed device
 *
 * @device: compressed device to रेजिस्टर
 */
पूर्णांक snd_compress_रेजिस्टर(काष्ठा snd_compr *device)
अणु
	पूर्णांक retval;

	अगर (device->name == शून्य || device->ops == शून्य)
		वापस -EINVAL;

	pr_debug("Registering compressed device %s\n", device->name);
	अगर (snd_BUG_ON(!device->ops->खोलो))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!device->ops->मुक्त))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!device->ops->set_params))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!device->ops->trigger))
		वापस -EINVAL;

	mutex_init(&device->lock);

	/* रेजिस्टर a compressed card */
	mutex_lock(&device_mutex);
	retval = snd_compress_add_device(device);
	mutex_unlock(&device_mutex);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(snd_compress_रेजिस्टर);

पूर्णांक snd_compress_deरेजिस्टर(काष्ठा snd_compr *device)
अणु
	pr_debug("Removing compressed device %s\n", device->name);
	mutex_lock(&device_mutex);
	snd_compress_हटाओ_device(device);
	mutex_unlock(&device_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_compress_deरेजिस्टर);

MODULE_DESCRIPTION("ALSA Compressed offload framework");
MODULE_AUTHOR("Vinod Koul <vinod.koul@linux.intel.com>");
MODULE_LICENSE("GPL v2");
