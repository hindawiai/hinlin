<शैली गुरु>
/*
 * dmxdev.c - DVB demultiplexer device
 *
 * Copyright (C) 2000 Ralph Metzler & Marcus Metzler
 *		      क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#घोषणा pr_fmt(fmt) "dmxdev: " fmt

#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/रुको.h>
#समावेश <linux/uaccess.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_vb2.h>

अटल पूर्णांक debug;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
			__func__, ##arg);				\
पूर्ण जबतक (0)

अटल पूर्णांक dvb_dmxdev_buffer_ग_लिखो(काष्ठा dvb_ringbuffer *buf,
				   स्थिर u8 *src, माप_प्रकार len)
अणु
	sमाप_प्रकार मुक्त;

	अगर (!len)
		वापस 0;
	अगर (!buf->data)
		वापस 0;

	मुक्त = dvb_ringbuffer_मुक्त(buf);
	अगर (len > मुक्त) अणु
		dprपूर्णांकk("buffer overflow\n");
		वापस -EOVERFLOW;
	पूर्ण

	वापस dvb_ringbuffer_ग_लिखो(buf, src, len);
पूर्ण

अटल sमाप_प्रकार dvb_dmxdev_buffer_पढ़ो(काष्ठा dvb_ringbuffer *src,
				      पूर्णांक non_blocking, अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	माप_प्रकार toकरो;
	sमाप_प्रकार avail;
	sमाप_प्रकार ret = 0;

	अगर (!src->data)
		वापस 0;

	अगर (src->error) अणु
		ret = src->error;
		dvb_ringbuffer_flush(src);
		वापस ret;
	पूर्ण

	क्रम (toकरो = count; toकरो > 0; toकरो -= ret) अणु
		अगर (non_blocking && dvb_ringbuffer_empty(src)) अणु
			ret = -EWOULDBLOCK;
			अवरोध;
		पूर्ण

		ret = रुको_event_पूर्णांकerruptible(src->queue,
					       !dvb_ringbuffer_empty(src) ||
					       (src->error != 0));
		अगर (ret < 0)
			अवरोध;

		अगर (src->error) अणु
			ret = src->error;
			dvb_ringbuffer_flush(src);
			अवरोध;
		पूर्ण

		avail = dvb_ringbuffer_avail(src);
		अगर (avail > toकरो)
			avail = toकरो;

		ret = dvb_ringbuffer_पढ़ो_user(src, buf, avail);
		अगर (ret < 0)
			अवरोध;

		buf += ret;
	पूर्ण

	वापस (count - toकरो) ? (count - toकरो) : ret;
पूर्ण

अटल काष्ठा dmx_frontend *get_fe(काष्ठा dmx_demux *demux, पूर्णांक type)
अणु
	काष्ठा list_head *head, *pos;

	head = demux->get_frontends(demux);
	अगर (!head)
		वापस शून्य;
	list_क्रम_each(pos, head)
		अगर (DMX_FE_ENTRY(pos)->source == type)
			वापस DMX_FE_ENTRY(pos);

	वापस शून्य;
पूर्ण

अटल पूर्णांक dvb_dvr_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dvbdev->priv;
	काष्ठा dmx_frontend *front;
	bool need_ringbuffer = false;

	dprपूर्णांकk("%s\n", __func__);

	अगर (mutex_lock_पूर्णांकerruptible(&dmxdev->mutex))
		वापस -ERESTARTSYS;

	अगर (dmxdev->निकास) अणु
		mutex_unlock(&dmxdev->mutex);
		वापस -ENODEV;
	पूर्ण

	dmxdev->may_करो_mmap = 0;

	/*
	 * The logic here is a little tricky due to the अगरdef.
	 *
	 * The ringbuffer is used क्रम both पढ़ो and mmap.
	 *
	 * It is not needed, however, on two situations:
	 *	- Write devices (access with O_WRONLY);
	 *	- For duplex device nodes, खोलोed with O_RDWR.
	 */

	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY)
		need_ringbuffer = true;
	अन्यथा अगर ((file->f_flags & O_ACCMODE) == O_RDWR) अणु
		अगर (!(dmxdev->capabilities & DMXDEV_CAP_DUPLEX)) अणु
#अगर_घोषित CONFIG_DVB_MMAP
			dmxdev->may_करो_mmap = 1;
			need_ringbuffer = true;
#अन्यथा
			mutex_unlock(&dmxdev->mutex);
			वापस -EOPNOTSUPP;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	अगर (need_ringbuffer) अणु
		व्योम *mem;

		अगर (!dvbdev->पढ़ोers) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -EBUSY;
		पूर्ण
		mem = vदो_स्मृति(DVR_BUFFER_SIZE);
		अगर (!mem) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ENOMEM;
		पूर्ण
		dvb_ringbuffer_init(&dmxdev->dvr_buffer, mem, DVR_BUFFER_SIZE);
		अगर (dmxdev->may_करो_mmap)
			dvb_vb2_init(&dmxdev->dvr_vb2_ctx, "dvr",
				     file->f_flags & O_NONBLOCK);
		dvbdev->पढ़ोers--;
	पूर्ण

	अगर ((file->f_flags & O_ACCMODE) == O_WRONLY) अणु
		dmxdev->dvr_orig_fe = dmxdev->demux->frontend;

		अगर (!dmxdev->demux->ग_लिखो) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -EOPNOTSUPP;
		पूर्ण

		front = get_fe(dmxdev->demux, DMX_MEMORY_FE);

		अगर (!front) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -EINVAL;
		पूर्ण
		dmxdev->demux->disconnect_frontend(dmxdev->demux);
		dmxdev->demux->connect_frontend(dmxdev->demux, front);
	पूर्ण
	dvbdev->users++;
	mutex_unlock(&dmxdev->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dvr_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dvbdev->priv;

	mutex_lock(&dmxdev->mutex);

	अगर ((file->f_flags & O_ACCMODE) == O_WRONLY) अणु
		dmxdev->demux->disconnect_frontend(dmxdev->demux);
		dmxdev->demux->connect_frontend(dmxdev->demux,
						dmxdev->dvr_orig_fe);
	पूर्ण

	अगर (((file->f_flags & O_ACCMODE) == O_RDONLY) ||
	    dmxdev->may_करो_mmap) अणु
		अगर (dmxdev->may_करो_mmap) अणु
			अगर (dvb_vb2_is_streaming(&dmxdev->dvr_vb2_ctx))
				dvb_vb2_stream_off(&dmxdev->dvr_vb2_ctx);
			dvb_vb2_release(&dmxdev->dvr_vb2_ctx);
		पूर्ण
		dvbdev->पढ़ोers++;
		अगर (dmxdev->dvr_buffer.data) अणु
			व्योम *mem = dmxdev->dvr_buffer.data;
			/*memory barrier*/
			mb();
			spin_lock_irq(&dmxdev->lock);
			dmxdev->dvr_buffer.data = शून्य;
			spin_unlock_irq(&dmxdev->lock);
			vमुक्त(mem);
		पूर्ण
	पूर्ण
	/* TODO */
	dvbdev->users--;
	अगर (dvbdev->users == 1 && dmxdev->निकास == 1) अणु
		mutex_unlock(&dmxdev->mutex);
		wake_up(&dvbdev->रुको_queue);
	पूर्ण अन्यथा
		mutex_unlock(&dmxdev->mutex);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dvb_dvr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dvbdev->priv;
	पूर्णांक ret;

	अगर (!dmxdev->demux->ग_लिखो)
		वापस -EOPNOTSUPP;
	अगर ((file->f_flags & O_ACCMODE) != O_WRONLY)
		वापस -EINVAL;
	अगर (mutex_lock_पूर्णांकerruptible(&dmxdev->mutex))
		वापस -ERESTARTSYS;

	अगर (dmxdev->निकास) अणु
		mutex_unlock(&dmxdev->mutex);
		वापस -ENODEV;
	पूर्ण
	ret = dmxdev->demux->ग_लिखो(dmxdev->demux, buf, count);
	mutex_unlock(&dmxdev->mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार dvb_dvr_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			    loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dvbdev->priv;

	अगर (dmxdev->निकास)
		वापस -ENODEV;

	वापस dvb_dmxdev_buffer_पढ़ो(&dmxdev->dvr_buffer,
				      file->f_flags & O_NONBLOCK,
				      buf, count, ppos);
पूर्ण

अटल पूर्णांक dvb_dvr_set_buffer_size(काष्ठा dmxdev *dmxdev,
				      अचिन्हित दीर्घ size)
अणु
	काष्ठा dvb_ringbuffer *buf = &dmxdev->dvr_buffer;
	व्योम *newmem;
	व्योम *oldmem;

	dprपूर्णांकk("%s\n", __func__);

	अगर (buf->size == size)
		वापस 0;
	अगर (!size)
		वापस -EINVAL;

	newmem = vदो_स्मृति(size);
	अगर (!newmem)
		वापस -ENOMEM;

	oldmem = buf->data;

	spin_lock_irq(&dmxdev->lock);
	buf->data = newmem;
	buf->size = size;

	/* reset and not flush in हाल the buffer shrinks */
	dvb_ringbuffer_reset(buf);
	spin_unlock_irq(&dmxdev->lock);

	vमुक्त(oldmem);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dvb_dmxdev_filter_state_set(काष्ठा dmxdev_filter
					       *dmxdevfilter, पूर्णांक state)
अणु
	spin_lock_irq(&dmxdevfilter->dev->lock);
	dmxdevfilter->state = state;
	spin_unlock_irq(&dmxdevfilter->dev->lock);
पूर्ण

अटल पूर्णांक dvb_dmxdev_set_buffer_size(काष्ठा dmxdev_filter *dmxdevfilter,
				      अचिन्हित दीर्घ size)
अणु
	काष्ठा dvb_ringbuffer *buf = &dmxdevfilter->buffer;
	व्योम *newmem;
	व्योम *oldmem;

	अगर (buf->size == size)
		वापस 0;
	अगर (!size)
		वापस -EINVAL;
	अगर (dmxdevfilter->state >= DMXDEV_STATE_GO)
		वापस -EBUSY;

	newmem = vदो_स्मृति(size);
	अगर (!newmem)
		वापस -ENOMEM;

	oldmem = buf->data;

	spin_lock_irq(&dmxdevfilter->dev->lock);
	buf->data = newmem;
	buf->size = size;

	/* reset and not flush in हाल the buffer shrinks */
	dvb_ringbuffer_reset(buf);
	spin_unlock_irq(&dmxdevfilter->dev->lock);

	vमुक्त(oldmem);

	वापस 0;
पूर्ण

अटल व्योम dvb_dmxdev_filter_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा dmxdev_filter *dmxdevfilter = from_समयr(dmxdevfilter, t, समयr);

	dmxdevfilter->buffer.error = -ETIMEDOUT;
	spin_lock_irq(&dmxdevfilter->dev->lock);
	dmxdevfilter->state = DMXDEV_STATE_TIMEDOUT;
	spin_unlock_irq(&dmxdevfilter->dev->lock);
	wake_up(&dmxdevfilter->buffer.queue);
पूर्ण

अटल व्योम dvb_dmxdev_filter_समयr(काष्ठा dmxdev_filter *dmxdevfilter)
अणु
	काष्ठा dmx_sct_filter_params *para = &dmxdevfilter->params.sec;

	del_समयr(&dmxdevfilter->समयr);
	अगर (para->समयout) अणु
		dmxdevfilter->समयr.expires =
		    jअगरfies + 1 + (HZ / 2 + HZ * para->समयout) / 1000;
		add_समयr(&dmxdevfilter->समयr);
	पूर्ण
पूर्ण

अटल पूर्णांक dvb_dmxdev_section_callback(स्थिर u8 *buffer1, माप_प्रकार buffer1_len,
				       स्थिर u8 *buffer2, माप_प्रकार buffer2_len,
				       काष्ठा dmx_section_filter *filter,
				       u32 *buffer_flags)
अणु
	काष्ठा dmxdev_filter *dmxdevfilter = filter->priv;
	पूर्णांक ret;

	अगर (!dvb_vb2_is_streaming(&dmxdevfilter->vb2_ctx) &&
	    dmxdevfilter->buffer.error) अणु
		wake_up(&dmxdevfilter->buffer.queue);
		वापस 0;
	पूर्ण
	spin_lock(&dmxdevfilter->dev->lock);
	अगर (dmxdevfilter->state != DMXDEV_STATE_GO) अणु
		spin_unlock(&dmxdevfilter->dev->lock);
		वापस 0;
	पूर्ण
	del_समयr(&dmxdevfilter->समयr);
	dprपूर्णांकk("section callback %*ph\n", 6, buffer1);
	अगर (dvb_vb2_is_streaming(&dmxdevfilter->vb2_ctx)) अणु
		ret = dvb_vb2_fill_buffer(&dmxdevfilter->vb2_ctx,
					  buffer1, buffer1_len,
					  buffer_flags);
		अगर (ret == buffer1_len)
			ret = dvb_vb2_fill_buffer(&dmxdevfilter->vb2_ctx,
						  buffer2, buffer2_len,
						  buffer_flags);
	पूर्ण अन्यथा अणु
		ret = dvb_dmxdev_buffer_ग_लिखो(&dmxdevfilter->buffer,
					      buffer1, buffer1_len);
		अगर (ret == buffer1_len) अणु
			ret = dvb_dmxdev_buffer_ग_लिखो(&dmxdevfilter->buffer,
						      buffer2, buffer2_len);
		पूर्ण
	पूर्ण
	अगर (ret < 0)
		dmxdevfilter->buffer.error = ret;
	अगर (dmxdevfilter->params.sec.flags & DMX_ONESHOT)
		dmxdevfilter->state = DMXDEV_STATE_DONE;
	spin_unlock(&dmxdevfilter->dev->lock);
	wake_up(&dmxdevfilter->buffer.queue);
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dmxdev_ts_callback(स्थिर u8 *buffer1, माप_प्रकार buffer1_len,
				  स्थिर u8 *buffer2, माप_प्रकार buffer2_len,
				  काष्ठा dmx_ts_feed *feed,
				  u32 *buffer_flags)
अणु
	काष्ठा dmxdev_filter *dmxdevfilter = feed->priv;
	काष्ठा dvb_ringbuffer *buffer;
#अगर_घोषित CONFIG_DVB_MMAP
	काष्ठा dvb_vb2_ctx *ctx;
#पूर्ण_अगर
	पूर्णांक ret;

	spin_lock(&dmxdevfilter->dev->lock);
	अगर (dmxdevfilter->params.pes.output == DMX_OUT_DECODER) अणु
		spin_unlock(&dmxdevfilter->dev->lock);
		वापस 0;
	पूर्ण

	अगर (dmxdevfilter->params.pes.output == DMX_OUT_TAP ||
	    dmxdevfilter->params.pes.output == DMX_OUT_TSDEMUX_TAP) अणु
		buffer = &dmxdevfilter->buffer;
#अगर_घोषित CONFIG_DVB_MMAP
		ctx = &dmxdevfilter->vb2_ctx;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		buffer = &dmxdevfilter->dev->dvr_buffer;
#अगर_घोषित CONFIG_DVB_MMAP
		ctx = &dmxdevfilter->dev->dvr_vb2_ctx;
#पूर्ण_अगर
	पूर्ण

	अगर (dvb_vb2_is_streaming(ctx)) अणु
		ret = dvb_vb2_fill_buffer(ctx, buffer1, buffer1_len,
					  buffer_flags);
		अगर (ret == buffer1_len)
			ret = dvb_vb2_fill_buffer(ctx, buffer2, buffer2_len,
						  buffer_flags);
	पूर्ण अन्यथा अणु
		अगर (buffer->error) अणु
			spin_unlock(&dmxdevfilter->dev->lock);
			wake_up(&buffer->queue);
			वापस 0;
		पूर्ण
		ret = dvb_dmxdev_buffer_ग_लिखो(buffer, buffer1, buffer1_len);
		अगर (ret == buffer1_len)
			ret = dvb_dmxdev_buffer_ग_लिखो(buffer,
						      buffer2, buffer2_len);
	पूर्ण
	अगर (ret < 0)
		buffer->error = ret;
	spin_unlock(&dmxdevfilter->dev->lock);
	wake_up(&buffer->queue);
	वापस 0;
पूर्ण

/* stop feed but only mark the specअगरied filter as stopped (state set) */
अटल पूर्णांक dvb_dmxdev_feed_stop(काष्ठा dmxdev_filter *dmxdevfilter)
अणु
	काष्ठा dmxdev_feed *feed;

	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_SET);

	चयन (dmxdevfilter->type) अणु
	हाल DMXDEV_TYPE_SEC:
		del_समयr(&dmxdevfilter->समयr);
		dmxdevfilter->feed.sec->stop_filtering(dmxdevfilter->feed.sec);
		अवरोध;
	हाल DMXDEV_TYPE_PES:
		list_क्रम_each_entry(feed, &dmxdevfilter->feed.ts, next)
			feed->ts->stop_filtering(feed->ts);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* start feed associated with the specअगरied filter */
अटल पूर्णांक dvb_dmxdev_feed_start(काष्ठा dmxdev_filter *filter)
अणु
	काष्ठा dmxdev_feed *feed;
	पूर्णांक ret;

	dvb_dmxdev_filter_state_set(filter, DMXDEV_STATE_GO);

	चयन (filter->type) अणु
	हाल DMXDEV_TYPE_SEC:
		वापस filter->feed.sec->start_filtering(filter->feed.sec);
	हाल DMXDEV_TYPE_PES:
		list_क्रम_each_entry(feed, &filter->feed.ts, next) अणु
			ret = feed->ts->start_filtering(feed->ts);
			अगर (ret < 0) अणु
				dvb_dmxdev_feed_stop(filter);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* restart section feed अगर it has filters left associated with it,
   otherwise release the feed */
अटल पूर्णांक dvb_dmxdev_feed_restart(काष्ठा dmxdev_filter *filter)
अणु
	पूर्णांक i;
	काष्ठा dmxdev *dmxdev = filter->dev;
	u16 pid = filter->params.sec.pid;

	क्रम (i = 0; i < dmxdev->filternum; i++)
		अगर (dmxdev->filter[i].state >= DMXDEV_STATE_GO &&
		    dmxdev->filter[i].type == DMXDEV_TYPE_SEC &&
		    dmxdev->filter[i].params.sec.pid == pid) अणु
			dvb_dmxdev_feed_start(&dmxdev->filter[i]);
			वापस 0;
		पूर्ण

	filter->dev->demux->release_section_feed(dmxdev->demux,
						 filter->feed.sec);

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dmxdev_filter_stop(काष्ठा dmxdev_filter *dmxdevfilter)
अणु
	काष्ठा dmxdev_feed *feed;
	काष्ठा dmx_demux *demux;

	अगर (dmxdevfilter->state < DMXDEV_STATE_GO)
		वापस 0;

	चयन (dmxdevfilter->type) अणु
	हाल DMXDEV_TYPE_SEC:
		अगर (!dmxdevfilter->feed.sec)
			अवरोध;
		dvb_dmxdev_feed_stop(dmxdevfilter);
		अगर (dmxdevfilter->filter.sec)
			dmxdevfilter->feed.sec->
			    release_filter(dmxdevfilter->feed.sec,
					   dmxdevfilter->filter.sec);
		dvb_dmxdev_feed_restart(dmxdevfilter);
		dmxdevfilter->feed.sec = शून्य;
		अवरोध;
	हाल DMXDEV_TYPE_PES:
		dvb_dmxdev_feed_stop(dmxdevfilter);
		demux = dmxdevfilter->dev->demux;
		list_क्रम_each_entry(feed, &dmxdevfilter->feed.ts, next) अणु
			demux->release_ts_feed(demux, feed->ts);
			feed->ts = शून्य;
		पूर्ण
		अवरोध;
	शेष:
		अगर (dmxdevfilter->state == DMXDEV_STATE_ALLOCATED)
			वापस 0;
		वापस -EINVAL;
	पूर्ण

	dvb_ringbuffer_flush(&dmxdevfilter->buffer);
	वापस 0;
पूर्ण

अटल व्योम dvb_dmxdev_delete_pids(काष्ठा dmxdev_filter *dmxdevfilter)
अणु
	काष्ठा dmxdev_feed *feed, *पंचांगp;

	/* delete all PIDs */
	list_क्रम_each_entry_safe(feed, पंचांगp, &dmxdevfilter->feed.ts, next) अणु
		list_del(&feed->next);
		kमुक्त(feed);
	पूर्ण

	BUG_ON(!list_empty(&dmxdevfilter->feed.ts));
पूर्ण

अटल अंतरभूत पूर्णांक dvb_dmxdev_filter_reset(काष्ठा dmxdev_filter *dmxdevfilter)
अणु
	अगर (dmxdevfilter->state < DMXDEV_STATE_SET)
		वापस 0;

	अगर (dmxdevfilter->type == DMXDEV_TYPE_PES)
		dvb_dmxdev_delete_pids(dmxdevfilter);

	dmxdevfilter->type = DMXDEV_TYPE_NONE;
	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_ALLOCATED);
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dmxdev_start_feed(काष्ठा dmxdev *dmxdev,
				 काष्ठा dmxdev_filter *filter,
				 काष्ठा dmxdev_feed *feed)
अणु
	kसमय_प्रकार समयout = kसमय_set(0, 0);
	काष्ठा dmx_pes_filter_params *para = &filter->params.pes;
	क्रमागत dmx_output otype;
	पूर्णांक ret;
	पूर्णांक ts_type;
	क्रमागत dmx_ts_pes ts_pes;
	काष्ठा dmx_ts_feed *tsfeed;

	feed->ts = शून्य;
	otype = para->output;

	ts_pes = para->pes_type;

	अगर (ts_pes < DMX_PES_OTHER)
		ts_type = TS_DECODER;
	अन्यथा
		ts_type = 0;

	अगर (otype == DMX_OUT_TS_TAP)
		ts_type |= TS_PACKET;
	अन्यथा अगर (otype == DMX_OUT_TSDEMUX_TAP)
		ts_type |= TS_PACKET | TS_DEMUX;
	अन्यथा अगर (otype == DMX_OUT_TAP)
		ts_type |= TS_PACKET | TS_DEMUX | TS_PAYLOAD_ONLY;

	ret = dmxdev->demux->allocate_ts_feed(dmxdev->demux, &feed->ts,
					      dvb_dmxdev_ts_callback);
	अगर (ret < 0)
		वापस ret;

	tsfeed = feed->ts;
	tsfeed->priv = filter;

	ret = tsfeed->set(tsfeed, feed->pid, ts_type, ts_pes, समयout);
	अगर (ret < 0) अणु
		dmxdev->demux->release_ts_feed(dmxdev->demux, tsfeed);
		वापस ret;
	पूर्ण

	ret = tsfeed->start_filtering(tsfeed);
	अगर (ret < 0) अणु
		dmxdev->demux->release_ts_feed(dmxdev->demux, tsfeed);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dmxdev_filter_start(काष्ठा dmxdev_filter *filter)
अणु
	काष्ठा dmxdev *dmxdev = filter->dev;
	काष्ठा dmxdev_feed *feed;
	व्योम *mem;
	पूर्णांक ret, i;

	अगर (filter->state < DMXDEV_STATE_SET)
		वापस -EINVAL;

	अगर (filter->state >= DMXDEV_STATE_GO)
		dvb_dmxdev_filter_stop(filter);

	अगर (!filter->buffer.data) अणु
		mem = vदो_स्मृति(filter->buffer.size);
		अगर (!mem)
			वापस -ENOMEM;
		spin_lock_irq(&filter->dev->lock);
		filter->buffer.data = mem;
		spin_unlock_irq(&filter->dev->lock);
	पूर्ण

	dvb_ringbuffer_flush(&filter->buffer);

	चयन (filter->type) अणु
	हाल DMXDEV_TYPE_SEC:
	अणु
		काष्ठा dmx_sct_filter_params *para = &filter->params.sec;
		काष्ठा dmx_section_filter **secfilter = &filter->filter.sec;
		काष्ठा dmx_section_feed **secfeed = &filter->feed.sec;

		*secfilter = शून्य;
		*secfeed = शून्य;


		/* find active filter/feed with same PID */
		क्रम (i = 0; i < dmxdev->filternum; i++) अणु
			अगर (dmxdev->filter[i].state >= DMXDEV_STATE_GO &&
			    dmxdev->filter[i].type == DMXDEV_TYPE_SEC &&
			    dmxdev->filter[i].params.sec.pid == para->pid) अणु
				*secfeed = dmxdev->filter[i].feed.sec;
				अवरोध;
			पूर्ण
		पूर्ण

		/* अगर no feed found, try to allocate new one */
		अगर (!*secfeed) अणु
			ret = dmxdev->demux->allocate_section_feed(dmxdev->demux,
								   secfeed,
								   dvb_dmxdev_section_callback);
			अगर (ret < 0) अणु
				pr_err("DVB (%s): could not alloc feed\n",
				       __func__);
				वापस ret;
			पूर्ण

			ret = (*secfeed)->set(*secfeed, para->pid,
					      (para->flags & DMX_CHECK_CRC) ? 1 : 0);
			अगर (ret < 0) अणु
				pr_err("DVB (%s): could not set feed\n",
				       __func__);
				dvb_dmxdev_feed_restart(filter);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			dvb_dmxdev_feed_stop(filter);
		पूर्ण

		ret = (*secfeed)->allocate_filter(*secfeed, secfilter);
		अगर (ret < 0) अणु
			dvb_dmxdev_feed_restart(filter);
			filter->feed.sec->start_filtering(*secfeed);
			dprपूर्णांकk("could not get filter\n");
			वापस ret;
		पूर्ण

		(*secfilter)->priv = filter;

		स_नकल(&((*secfilter)->filter_value[3]),
		       &(para->filter.filter[1]), DMX_FILTER_SIZE - 1);
		स_नकल(&(*secfilter)->filter_mask[3],
		       &para->filter.mask[1], DMX_FILTER_SIZE - 1);
		स_नकल(&(*secfilter)->filter_mode[3],
		       &para->filter.mode[1], DMX_FILTER_SIZE - 1);

		(*secfilter)->filter_value[0] = para->filter.filter[0];
		(*secfilter)->filter_mask[0] = para->filter.mask[0];
		(*secfilter)->filter_mode[0] = para->filter.mode[0];
		(*secfilter)->filter_mask[1] = 0;
		(*secfilter)->filter_mask[2] = 0;

		filter->toकरो = 0;

		ret = filter->feed.sec->start_filtering(filter->feed.sec);
		अगर (ret < 0)
			वापस ret;

		dvb_dmxdev_filter_समयr(filter);
		अवरोध;
	पूर्ण
	हाल DMXDEV_TYPE_PES:
		list_क्रम_each_entry(feed, &filter->feed.ts, next) अणु
			ret = dvb_dmxdev_start_feed(dmxdev, filter, feed);
			अगर (ret < 0) अणु
				dvb_dmxdev_filter_stop(filter);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dvb_dmxdev_filter_state_set(filter, DMXDEV_STATE_GO);
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_demux_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dvbdev->priv;
	पूर्णांक i;
	काष्ठा dmxdev_filter *dmxdevfilter;

	अगर (!dmxdev->filter)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&dmxdev->mutex))
		वापस -ERESTARTSYS;

	क्रम (i = 0; i < dmxdev->filternum; i++)
		अगर (dmxdev->filter[i].state == DMXDEV_STATE_FREE)
			अवरोध;

	अगर (i == dmxdev->filternum) अणु
		mutex_unlock(&dmxdev->mutex);
		वापस -EMखाता;
	पूर्ण

	dmxdevfilter = &dmxdev->filter[i];
	mutex_init(&dmxdevfilter->mutex);
	file->निजी_data = dmxdevfilter;

#अगर_घोषित CONFIG_DVB_MMAP
	dmxdev->may_करो_mmap = 1;
#अन्यथा
	dmxdev->may_करो_mmap = 0;
#पूर्ण_अगर

	dvb_ringbuffer_init(&dmxdevfilter->buffer, शून्य, 8192);
	dvb_vb2_init(&dmxdevfilter->vb2_ctx, "demux_filter",
		     file->f_flags & O_NONBLOCK);
	dmxdevfilter->type = DMXDEV_TYPE_NONE;
	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_ALLOCATED);
	समयr_setup(&dmxdevfilter->समयr, dvb_dmxdev_filter_समयout, 0);

	dvbdev->users++;

	mutex_unlock(&dmxdev->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dmxdev_filter_मुक्त(काष्ठा dmxdev *dmxdev,
				  काष्ठा dmxdev_filter *dmxdevfilter)
अणु
	mutex_lock(&dmxdev->mutex);
	mutex_lock(&dmxdevfilter->mutex);
	अगर (dvb_vb2_is_streaming(&dmxdevfilter->vb2_ctx))
		dvb_vb2_stream_off(&dmxdevfilter->vb2_ctx);
	dvb_vb2_release(&dmxdevfilter->vb2_ctx);


	dvb_dmxdev_filter_stop(dmxdevfilter);
	dvb_dmxdev_filter_reset(dmxdevfilter);

	अगर (dmxdevfilter->buffer.data) अणु
		व्योम *mem = dmxdevfilter->buffer.data;

		spin_lock_irq(&dmxdev->lock);
		dmxdevfilter->buffer.data = शून्य;
		spin_unlock_irq(&dmxdev->lock);
		vमुक्त(mem);
	पूर्ण

	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_FREE);
	wake_up(&dmxdevfilter->buffer.queue);
	mutex_unlock(&dmxdevfilter->mutex);
	mutex_unlock(&dmxdev->mutex);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम invert_mode(काष्ठा dmx_filter *filter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DMX_FILTER_SIZE; i++)
		filter->mode[i] ^= 0xff;
पूर्ण

अटल पूर्णांक dvb_dmxdev_add_pid(काष्ठा dmxdev *dmxdev,
			      काष्ठा dmxdev_filter *filter, u16 pid)
अणु
	काष्ठा dmxdev_feed *feed;

	अगर ((filter->type != DMXDEV_TYPE_PES) ||
	    (filter->state < DMXDEV_STATE_SET))
		वापस -EINVAL;

	/* only TS packet filters may have multiple PIDs */
	अगर ((filter->params.pes.output != DMX_OUT_TSDEMUX_TAP) &&
	    (!list_empty(&filter->feed.ts)))
		वापस -EINVAL;

	feed = kzalloc(माप(काष्ठा dmxdev_feed), GFP_KERNEL);
	अगर (feed == शून्य)
		वापस -ENOMEM;

	feed->pid = pid;
	list_add(&feed->next, &filter->feed.ts);

	अगर (filter->state >= DMXDEV_STATE_GO)
		वापस dvb_dmxdev_start_feed(dmxdev, filter, feed);

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dmxdev_हटाओ_pid(काष्ठा dmxdev *dmxdev,
				  काष्ठा dmxdev_filter *filter, u16 pid)
अणु
	काष्ठा dmxdev_feed *feed, *पंचांगp;

	अगर ((filter->type != DMXDEV_TYPE_PES) ||
	    (filter->state < DMXDEV_STATE_SET))
		वापस -EINVAL;

	list_क्रम_each_entry_safe(feed, पंचांगp, &filter->feed.ts, next) अणु
		अगर ((feed->pid == pid) && (feed->ts != शून्य)) अणु
			feed->ts->stop_filtering(feed->ts);
			filter->dev->demux->release_ts_feed(filter->dev->demux,
							    feed->ts);
			list_del(&feed->next);
			kमुक्त(feed);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dmxdev_filter_set(काष्ठा dmxdev *dmxdev,
				 काष्ठा dmxdev_filter *dmxdevfilter,
				 काष्ठा dmx_sct_filter_params *params)
अणु
	dprपूर्णांकk("%s: PID=0x%04x, flags=%02x, timeout=%d\n",
		__func__, params->pid, params->flags, params->समयout);

	dvb_dmxdev_filter_stop(dmxdevfilter);

	dmxdevfilter->type = DMXDEV_TYPE_SEC;
	स_नकल(&dmxdevfilter->params.sec,
	       params, माप(काष्ठा dmx_sct_filter_params));
	invert_mode(&dmxdevfilter->params.sec.filter);
	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_SET);

	अगर (params->flags & DMX_IMMEDIATE_START)
		वापस dvb_dmxdev_filter_start(dmxdevfilter);

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dmxdev_pes_filter_set(काष्ठा dmxdev *dmxdev,
				     काष्ठा dmxdev_filter *dmxdevfilter,
				     काष्ठा dmx_pes_filter_params *params)
अणु
	पूर्णांक ret;

	dvb_dmxdev_filter_stop(dmxdevfilter);
	dvb_dmxdev_filter_reset(dmxdevfilter);

	अगर ((अचिन्हित पूर्णांक)params->pes_type > DMX_PES_OTHER)
		वापस -EINVAL;

	dmxdevfilter->type = DMXDEV_TYPE_PES;
	स_नकल(&dmxdevfilter->params, params,
	       माप(काष्ठा dmx_pes_filter_params));
	INIT_LIST_HEAD(&dmxdevfilter->feed.ts);

	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_SET);

	ret = dvb_dmxdev_add_pid(dmxdev, dmxdevfilter,
				 dmxdevfilter->params.pes.pid);
	अगर (ret < 0)
		वापस ret;

	अगर (params->flags & DMX_IMMEDIATE_START)
		वापस dvb_dmxdev_filter_start(dmxdevfilter);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dvb_dmxdev_पढ़ो_sec(काष्ठा dmxdev_filter *dfil,
				   काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक result, hcount;
	पूर्णांक करोne = 0;

	अगर (dfil->toकरो <= 0) अणु
		hcount = 3 + dfil->toकरो;
		अगर (hcount > count)
			hcount = count;
		result = dvb_dmxdev_buffer_पढ़ो(&dfil->buffer,
						file->f_flags & O_NONBLOCK,
						buf, hcount, ppos);
		अगर (result < 0) अणु
			dfil->toकरो = 0;
			वापस result;
		पूर्ण
		अगर (copy_from_user(dfil->secheader - dfil->toकरो, buf, result))
			वापस -EFAULT;
		buf += result;
		करोne = result;
		count -= result;
		dfil->toकरो -= result;
		अगर (dfil->toकरो > -3)
			वापस करोne;
		dfil->toकरो = ((dfil->secheader[1] << 8) | dfil->secheader[2]) & 0xfff;
		अगर (!count)
			वापस करोne;
	पूर्ण
	अगर (count > dfil->toकरो)
		count = dfil->toकरो;
	result = dvb_dmxdev_buffer_पढ़ो(&dfil->buffer,
					file->f_flags & O_NONBLOCK,
					buf, count, ppos);
	अगर (result < 0)
		वापस result;
	dfil->toकरो -= result;
	वापस (result + करोne);
पूर्ण

अटल sमाप_प्रकार
dvb_demux_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
	       loff_t *ppos)
अणु
	काष्ठा dmxdev_filter *dmxdevfilter = file->निजी_data;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex))
		वापस -ERESTARTSYS;

	अगर (dmxdevfilter->type == DMXDEV_TYPE_SEC)
		ret = dvb_dmxdev_पढ़ो_sec(dmxdevfilter, file, buf, count, ppos);
	अन्यथा
		ret = dvb_dmxdev_buffer_पढ़ो(&dmxdevfilter->buffer,
					     file->f_flags & O_NONBLOCK,
					     buf, count, ppos);

	mutex_unlock(&dmxdevfilter->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_demux_करो_ioctl(काष्ठा file *file,
			      अचिन्हित पूर्णांक cmd, व्योम *parg)
अणु
	काष्ठा dmxdev_filter *dmxdevfilter = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dmxdevfilter->dev;
	अचिन्हित दीर्घ arg = (अचिन्हित दीर्घ)parg;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&dmxdev->mutex))
		वापस -ERESTARTSYS;

	चयन (cmd) अणु
	हाल DMX_START:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		अगर (dmxdevfilter->state < DMXDEV_STATE_SET)
			ret = -EINVAL;
		अन्यथा
			ret = dvb_dmxdev_filter_start(dmxdevfilter);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_STOP:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		ret = dvb_dmxdev_filter_stop(dmxdevfilter);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_SET_FILTER:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		ret = dvb_dmxdev_filter_set(dmxdev, dmxdevfilter, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_SET_PES_FILTER:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		ret = dvb_dmxdev_pes_filter_set(dmxdev, dmxdevfilter, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_SET_BUFFER_SIZE:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		ret = dvb_dmxdev_set_buffer_size(dmxdevfilter, arg);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_GET_PES_PIDS:
		अगर (!dmxdev->demux->get_pes_pids) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		dmxdev->demux->get_pes_pids(dmxdev->demux, parg);
		अवरोध;

	हाल DMX_GET_STC:
		अगर (!dmxdev->demux->get_stc) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = dmxdev->demux->get_stc(dmxdev->demux,
					     ((काष्ठा dmx_stc *)parg)->num,
					     &((काष्ठा dmx_stc *)parg)->stc,
					     &((काष्ठा dmx_stc *)parg)->base);
		अवरोध;

	हाल DMX_ADD_PID:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		ret = dvb_dmxdev_add_pid(dmxdev, dmxdevfilter, *(u16 *)parg);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_REMOVE_PID:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		ret = dvb_dmxdev_हटाओ_pid(dmxdev, dmxdevfilter, *(u16 *)parg);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

#अगर_घोषित CONFIG_DVB_MMAP
	हाल DMX_REQBUFS:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		ret = dvb_vb2_reqbufs(&dmxdevfilter->vb2_ctx, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_QUERYBUF:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		ret = dvb_vb2_querybuf(&dmxdevfilter->vb2_ctx, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_EXPBUF:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		ret = dvb_vb2_expbuf(&dmxdevfilter->vb2_ctx, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_QBUF:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		ret = dvb_vb2_qbuf(&dmxdevfilter->vb2_ctx, parg);
		अगर (ret == 0 && !dvb_vb2_is_streaming(&dmxdevfilter->vb2_ctx))
			ret = dvb_vb2_stream_on(&dmxdevfilter->vb2_ctx);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;

	हाल DMX_DQBUF:
		अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
			mutex_unlock(&dmxdev->mutex);
			वापस -ERESTARTSYS;
		पूर्ण
		ret = dvb_vb2_dqbuf(&dmxdevfilter->vb2_ctx, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		अवरोध;
#पूर्ण_अगर
	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण
	mutex_unlock(&dmxdev->mutex);
	वापस ret;
पूर्ण

अटल दीर्घ dvb_demux_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	वापस dvb_usercopy(file, cmd, arg, dvb_demux_करो_ioctl);
पूर्ण

अटल __poll_t dvb_demux_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा dmxdev_filter *dmxdevfilter = file->निजी_data;
	__poll_t mask = 0;

	poll_रुको(file, &dmxdevfilter->buffer.queue, रुको);

	अगर ((!dmxdevfilter) || dmxdevfilter->dev->निकास)
		वापस EPOLLERR;
	अगर (dvb_vb2_is_streaming(&dmxdevfilter->vb2_ctx))
		वापस dvb_vb2_poll(&dmxdevfilter->vb2_ctx, file, रुको);

	अगर (dmxdevfilter->state != DMXDEV_STATE_GO &&
	    dmxdevfilter->state != DMXDEV_STATE_DONE &&
	    dmxdevfilter->state != DMXDEV_STATE_TIMEDOUT)
		वापस 0;

	अगर (dmxdevfilter->buffer.error)
		mask |= (EPOLLIN | EPOLLRDNORM | EPOLLPRI | EPOLLERR);

	अगर (!dvb_ringbuffer_empty(&dmxdevfilter->buffer))
		mask |= (EPOLLIN | EPOLLRDNORM | EPOLLPRI);

	वापस mask;
पूर्ण

#अगर_घोषित CONFIG_DVB_MMAP
अटल पूर्णांक dvb_demux_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा dmxdev_filter *dmxdevfilter = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dmxdevfilter->dev;
	पूर्णांक ret;

	अगर (!dmxdev->may_करो_mmap)
		वापस -ENOTTY;

	अगर (mutex_lock_पूर्णांकerruptible(&dmxdev->mutex))
		वापस -ERESTARTSYS;

	अगर (mutex_lock_पूर्णांकerruptible(&dmxdevfilter->mutex)) अणु
		mutex_unlock(&dmxdev->mutex);
		वापस -ERESTARTSYS;
	पूर्ण
	ret = dvb_vb2_mmap(&dmxdevfilter->vb2_ctx, vma);

	mutex_unlock(&dmxdevfilter->mutex);
	mutex_unlock(&dmxdev->mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dvb_demux_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dmxdev_filter *dmxdevfilter = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dmxdevfilter->dev;
	पूर्णांक ret;

	ret = dvb_dmxdev_filter_मुक्त(dmxdev, dmxdevfilter);

	mutex_lock(&dmxdev->mutex);
	dmxdev->dvbdev->users--;
	अगर (dmxdev->dvbdev->users == 1 && dmxdev->निकास == 1) अणु
		mutex_unlock(&dmxdev->mutex);
		wake_up(&dmxdev->dvbdev->रुको_queue);
	पूर्ण अन्यथा
		mutex_unlock(&dmxdev->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations dvb_demux_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dvb_demux_पढ़ो,
	.unlocked_ioctl = dvb_demux_ioctl,
	.compat_ioctl = dvb_demux_ioctl,
	.खोलो = dvb_demux_खोलो,
	.release = dvb_demux_release,
	.poll = dvb_demux_poll,
	.llseek = शेष_llseek,
#अगर_घोषित CONFIG_DVB_MMAP
	.mmap = dvb_demux_mmap,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा dvb_device dvbdev_demux = अणु
	.priv = शून्य,
	.users = 1,
	.ग_लिखोrs = 1,
#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-demux",
#पूर्ण_अगर
	.fops = &dvb_demux_fops
पूर्ण;

अटल पूर्णांक dvb_dvr_करो_ioctl(काष्ठा file *file,
			    अचिन्हित पूर्णांक cmd, व्योम *parg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dvbdev->priv;
	अचिन्हित दीर्घ arg = (अचिन्हित दीर्घ)parg;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dmxdev->mutex))
		वापस -ERESTARTSYS;

	चयन (cmd) अणु
	हाल DMX_SET_BUFFER_SIZE:
		ret = dvb_dvr_set_buffer_size(dmxdev, arg);
		अवरोध;

#अगर_घोषित CONFIG_DVB_MMAP
	हाल DMX_REQBUFS:
		ret = dvb_vb2_reqbufs(&dmxdev->dvr_vb2_ctx, parg);
		अवरोध;

	हाल DMX_QUERYBUF:
		ret = dvb_vb2_querybuf(&dmxdev->dvr_vb2_ctx, parg);
		अवरोध;

	हाल DMX_EXPBUF:
		ret = dvb_vb2_expbuf(&dmxdev->dvr_vb2_ctx, parg);
		अवरोध;

	हाल DMX_QBUF:
		ret = dvb_vb2_qbuf(&dmxdev->dvr_vb2_ctx, parg);
		अगर (ret == 0 && !dvb_vb2_is_streaming(&dmxdev->dvr_vb2_ctx))
			ret = dvb_vb2_stream_on(&dmxdev->dvr_vb2_ctx);
		अवरोध;

	हाल DMX_DQBUF:
		ret = dvb_vb2_dqbuf(&dmxdev->dvr_vb2_ctx, parg);
		अवरोध;
#पूर्ण_अगर
	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण
	mutex_unlock(&dmxdev->mutex);
	वापस ret;
पूर्ण

अटल दीर्घ dvb_dvr_ioctl(काष्ठा file *file,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस dvb_usercopy(file, cmd, arg, dvb_dvr_करो_ioctl);
पूर्ण

अटल __poll_t dvb_dvr_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dvbdev->priv;
	__poll_t mask = 0;

	dprपूर्णांकk("%s\n", __func__);

	poll_रुको(file, &dmxdev->dvr_buffer.queue, रुको);

	अगर (dmxdev->निकास)
		वापस EPOLLERR;
	अगर (dvb_vb2_is_streaming(&dmxdev->dvr_vb2_ctx))
		वापस dvb_vb2_poll(&dmxdev->dvr_vb2_ctx, file, रुको);

	अगर (((file->f_flags & O_ACCMODE) == O_RDONLY) ||
	    dmxdev->may_करो_mmap) अणु
		अगर (dmxdev->dvr_buffer.error)
			mask |= (EPOLLIN | EPOLLRDNORM | EPOLLPRI | EPOLLERR);

		अगर (!dvb_ringbuffer_empty(&dmxdev->dvr_buffer))
			mask |= (EPOLLIN | EPOLLRDNORM | EPOLLPRI);
	पूर्ण अन्यथा
		mask |= (EPOLLOUT | EPOLLWRNORM | EPOLLPRI);

	वापस mask;
पूर्ण

#अगर_घोषित CONFIG_DVB_MMAP
अटल पूर्णांक dvb_dvr_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dmxdev *dmxdev = dvbdev->priv;
	पूर्णांक ret;

	अगर (!dmxdev->may_करो_mmap)
		वापस -ENOTTY;

	अगर (dmxdev->निकास)
		वापस -ENODEV;

	अगर (mutex_lock_पूर्णांकerruptible(&dmxdev->mutex))
		वापस -ERESTARTSYS;

	ret = dvb_vb2_mmap(&dmxdev->dvr_vb2_ctx, vma);
	mutex_unlock(&dmxdev->mutex);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations dvb_dvr_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dvb_dvr_पढ़ो,
	.ग_लिखो = dvb_dvr_ग_लिखो,
	.unlocked_ioctl = dvb_dvr_ioctl,
	.खोलो = dvb_dvr_खोलो,
	.release = dvb_dvr_release,
	.poll = dvb_dvr_poll,
	.llseek = शेष_llseek,
#अगर_घोषित CONFIG_DVB_MMAP
	.mmap = dvb_dvr_mmap,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा dvb_device dvbdev_dvr = अणु
	.priv = शून्य,
	.पढ़ोers = 1,
	.users = 1,
#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-dvr",
#पूर्ण_अगर
	.fops = &dvb_dvr_fops
पूर्ण;
पूर्णांक dvb_dmxdev_init(काष्ठा dmxdev *dmxdev, काष्ठा dvb_adapter *dvb_adapter)
अणु
	पूर्णांक i;

	अगर (dmxdev->demux->खोलो(dmxdev->demux) < 0)
		वापस -EUSERS;

	dmxdev->filter = vदो_स्मृति(array_size(माप(काष्ठा dmxdev_filter),
					    dmxdev->filternum));
	अगर (!dmxdev->filter)
		वापस -ENOMEM;

	mutex_init(&dmxdev->mutex);
	spin_lock_init(&dmxdev->lock);
	क्रम (i = 0; i < dmxdev->filternum; i++) अणु
		dmxdev->filter[i].dev = dmxdev;
		dmxdev->filter[i].buffer.data = शून्य;
		dvb_dmxdev_filter_state_set(&dmxdev->filter[i],
					    DMXDEV_STATE_FREE);
	पूर्ण

	dvb_रेजिस्टर_device(dvb_adapter, &dmxdev->dvbdev, &dvbdev_demux, dmxdev,
			    DVB_DEVICE_DEMUX, dmxdev->filternum);
	dvb_रेजिस्टर_device(dvb_adapter, &dmxdev->dvr_dvbdev, &dvbdev_dvr,
			    dmxdev, DVB_DEVICE_DVR, dmxdev->filternum);

	dvb_ringbuffer_init(&dmxdev->dvr_buffer, शून्य, 8192);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(dvb_dmxdev_init);

व्योम dvb_dmxdev_release(काष्ठा dmxdev *dmxdev)
अणु
	dmxdev->निकास = 1;
	अगर (dmxdev->dvbdev->users > 1) अणु
		रुको_event(dmxdev->dvbdev->रुको_queue,
				dmxdev->dvbdev->users == 1);
	पूर्ण
	अगर (dmxdev->dvr_dvbdev->users > 1) अणु
		रुको_event(dmxdev->dvr_dvbdev->रुको_queue,
				dmxdev->dvr_dvbdev->users == 1);
	पूर्ण

	dvb_unरेजिस्टर_device(dmxdev->dvbdev);
	dvb_unरेजिस्टर_device(dmxdev->dvr_dvbdev);

	vमुक्त(dmxdev->filter);
	dmxdev->filter = शून्य;
	dmxdev->demux->बंद(dmxdev->demux);
पूर्ण

EXPORT_SYMBOL(dvb_dmxdev_release);
