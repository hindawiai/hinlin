<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hauppauge HD PVR USB driver - video 4 linux 2 पूर्णांकerface
 *
 * Copyright (C) 2008      Janne Grunau (j@jannau.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश "hdpvr.h"

#घोषणा BULK_URB_TIMEOUT   90 /* 0.09 seconds */

#घोषणा prपूर्णांक_buffer_status() अणु \
		v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,	\
			 "%s:%d buffer stat: %d free, %d proc\n",	\
			 __func__, __LINE__,				\
			 list_size(&dev->मुक्त_buff_list),		\
			 list_size(&dev->rec_buff_list)); पूर्ण

अटल स्थिर काष्ठा v4l2_dv_timings hdpvr_dv_timings[] = अणु
	V4L2_DV_BT_CEA_720X480I59_94,
	V4L2_DV_BT_CEA_720X576I50,
	V4L2_DV_BT_CEA_720X480P59_94,
	V4L2_DV_BT_CEA_720X576P50,
	V4L2_DV_BT_CEA_1280X720P50,
	V4L2_DV_BT_CEA_1280X720P60,
	V4L2_DV_BT_CEA_1920X1080I50,
	V4L2_DV_BT_CEA_1920X1080I60,
पूर्ण;

/* Use 480i59 as the शेष timings */
#घोषणा HDPVR_DEF_DV_TIMINGS_IDX (0)

काष्ठा hdpvr_fh अणु
	काष्ठा v4l2_fh fh;
	bool legacy_mode;
पूर्ण;

अटल uपूर्णांक list_size(काष्ठा list_head *list)
अणु
	काष्ठा list_head *पंचांगp;
	uपूर्णांक count = 0;

	list_क्रम_each(पंचांगp, list) अणु
		count++;
	पूर्ण

	वापस count;
पूर्ण

/*=========================================================================*/
/* urb callback */
अटल व्योम hdpvr_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा hdpvr_buffer *buf = (काष्ठा hdpvr_buffer *)urb->context;
	काष्ठा hdpvr_device *dev = buf->dev;

	/* marking buffer as received and wake रुकोing */
	buf->status = BUFSTAT_READY;
	wake_up_पूर्णांकerruptible(&dev->रुको_data);
पूर्ण

/*=========================================================================*/
/* buffer bits */

/* function expects dev->io_mutex to be hold by caller */
पूर्णांक hdpvr_cancel_queue(काष्ठा hdpvr_device *dev)
अणु
	काष्ठा hdpvr_buffer *buf;

	list_क्रम_each_entry(buf, &dev->rec_buff_list, buff_list) अणु
		usb_समाप्त_urb(buf->urb);
		buf->status = BUFSTAT_AVAILABLE;
	पूर्ण

	list_splice_init(&dev->rec_buff_list, dev->मुक्त_buff_list.prev);

	वापस 0;
पूर्ण

अटल पूर्णांक hdpvr_मुक्त_queue(काष्ठा list_head *q)
अणु
	काष्ठा list_head *पंचांगp;
	काष्ठा list_head *p;
	काष्ठा hdpvr_buffer *buf;
	काष्ठा urb *urb;

	क्रम (p = q->next; p != q;) अणु
		buf = list_entry(p, काष्ठा hdpvr_buffer, buff_list);

		urb = buf->urb;
		usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
				  urb->transfer_buffer, urb->transfer_dma);
		usb_मुक्त_urb(urb);
		पंचांगp = p->next;
		list_del(p);
		kमुक्त(buf);
		p = पंचांगp;
	पूर्ण

	वापस 0;
पूर्ण

/* function expects dev->io_mutex to be hold by caller */
पूर्णांक hdpvr_मुक्त_buffers(काष्ठा hdpvr_device *dev)
अणु
	hdpvr_cancel_queue(dev);

	hdpvr_मुक्त_queue(&dev->मुक्त_buff_list);
	hdpvr_मुक्त_queue(&dev->rec_buff_list);

	वापस 0;
पूर्ण

/* function expects dev->io_mutex to be hold by caller */
पूर्णांक hdpvr_alloc_buffers(काष्ठा hdpvr_device *dev, uपूर्णांक count)
अणु
	uपूर्णांक i;
	पूर्णांक retval = -ENOMEM;
	u8 *mem;
	काष्ठा hdpvr_buffer *buf;
	काष्ठा urb *urb;

	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "allocating %u buffers\n", count);

	क्रम (i = 0; i < count; i++) अणु

		buf = kzalloc(माप(काष्ठा hdpvr_buffer), GFP_KERNEL);
		अगर (!buf) अणु
			v4l2_err(&dev->v4l2_dev, "cannot allocate buffer\n");
			जाओ निकास;
		पूर्ण
		buf->dev = dev;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb)
			जाओ निकास_urb;
		buf->urb = urb;

		mem = usb_alloc_coherent(dev->udev, dev->bulk_in_size, GFP_KERNEL,
					 &urb->transfer_dma);
		अगर (!mem) अणु
			v4l2_err(&dev->v4l2_dev,
				 "cannot allocate usb transfer buffer\n");
			जाओ निकास_urb_buffer;
		पूर्ण

		usb_fill_bulk_urb(buf->urb, dev->udev,
				  usb_rcvbulkpipe(dev->udev,
						  dev->bulk_in_endpoपूर्णांकAddr),
				  mem, dev->bulk_in_size,
				  hdpvr_पढ़ो_bulk_callback, buf);

		buf->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		buf->status = BUFSTAT_AVAILABLE;
		list_add_tail(&buf->buff_list, &dev->मुक्त_buff_list);
	पूर्ण
	वापस 0;
निकास_urb_buffer:
	usb_मुक्त_urb(urb);
निकास_urb:
	kमुक्त(buf);
निकास:
	hdpvr_मुक्त_buffers(dev);
	वापस retval;
पूर्ण

अटल पूर्णांक hdpvr_submit_buffers(काष्ठा hdpvr_device *dev)
अणु
	काष्ठा hdpvr_buffer *buf;
	काष्ठा urb *urb;
	पूर्णांक ret = 0, err_count = 0;

	mutex_lock(&dev->io_mutex);

	जबतक (dev->status == STATUS_STREAMING &&
	       !list_empty(&dev->मुक्त_buff_list)) अणु

		buf = list_entry(dev->मुक्त_buff_list.next, काष्ठा hdpvr_buffer,
				 buff_list);
		अगर (buf->status != BUFSTAT_AVAILABLE) अणु
			v4l2_err(&dev->v4l2_dev,
				 "buffer not marked as available\n");
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		urb = buf->urb;
		urb->status = 0;
		urb->actual_length = 0;
		ret = usb_submit_urb(urb, GFP_KERNEL);
		अगर (ret) अणु
			v4l2_err(&dev->v4l2_dev,
				 "usb_submit_urb in %s returned %d\n",
				 __func__, ret);
			अगर (++err_count > 2)
				अवरोध;
			जारी;
		पूर्ण
		buf->status = BUFSTAT_INPROGRESS;
		list_move_tail(&buf->buff_list, &dev->rec_buff_list);
	पूर्ण
err:
	prपूर्णांक_buffer_status();
	mutex_unlock(&dev->io_mutex);
	वापस ret;
पूर्ण

अटल काष्ठा hdpvr_buffer *hdpvr_get_next_buffer(काष्ठा hdpvr_device *dev)
अणु
	काष्ठा hdpvr_buffer *buf;

	mutex_lock(&dev->io_mutex);

	अगर (list_empty(&dev->rec_buff_list)) अणु
		mutex_unlock(&dev->io_mutex);
		वापस शून्य;
	पूर्ण

	buf = list_entry(dev->rec_buff_list.next, काष्ठा hdpvr_buffer,
			 buff_list);
	mutex_unlock(&dev->io_mutex);

	वापस buf;
पूर्ण

अटल व्योम hdpvr_transmit_buffers(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdpvr_device *dev = container_of(work, काष्ठा hdpvr_device,
						worker);

	जबतक (dev->status == STATUS_STREAMING) अणु

		अगर (hdpvr_submit_buffers(dev)) अणु
			v4l2_err(&dev->v4l2_dev, "couldn't submit buffers\n");
			जाओ error;
		पूर्ण
		अगर (रुको_event_पूर्णांकerruptible(dev->रुको_buffer,
				!list_empty(&dev->मुक्त_buff_list) ||
					     dev->status != STATUS_STREAMING))
			जाओ error;
	पूर्ण

	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "transmit worker exited\n");
	वापस;
error:
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "transmit buffers errored\n");
	dev->status = STATUS_ERROR;
पूर्ण

/* function expects dev->io_mutex to be hold by caller */
अटल पूर्णांक hdpvr_start_streaming(काष्ठा hdpvr_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा hdpvr_video_info vidinf;

	अगर (dev->status == STATUS_STREAMING)
		वापस 0;
	अगर (dev->status != STATUS_IDLE)
		वापस -EAGAIN;

	ret = get_video_info(dev, &vidinf);
	अगर (ret < 0)
		वापस ret;

	अगर (!vidinf.valid) अणु
		msleep(250);
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
				"no video signal at input %d\n", dev->options.video_input);
		वापस -EAGAIN;
	पूर्ण

	v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
			"video signal: %dx%d@%dhz\n", vidinf.width,
			vidinf.height, vidinf.fps);

	/* start streaming 2 request */
	ret = usb_control_msg(dev->udev,
			usb_sndctrlpipe(dev->udev, 0),
			0xb8, 0x38, 0x1, 0, शून्य, 0, 8000);
	v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
			"encoder start control request returned %d\n", ret);
	अगर (ret < 0)
		वापस ret;

	ret = hdpvr_config_call(dev, CTRL_START_STREAMING_VALUE, 0x00);
	अगर (ret)
		वापस ret;

	dev->status = STATUS_STREAMING;

	INIT_WORK(&dev->worker, hdpvr_transmit_buffers);
	schedule_work(&dev->worker);

	v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
			"streaming started\n");

	वापस 0;
पूर्ण


/* function expects dev->io_mutex to be hold by caller */
अटल पूर्णांक hdpvr_stop_streaming(काष्ठा hdpvr_device *dev)
अणु
	पूर्णांक actual_length;
	uपूर्णांक c = 0;
	u8 *buf;

	अगर (dev->status == STATUS_IDLE)
		वापस 0;
	अन्यथा अगर (dev->status != STATUS_STREAMING)
		वापस -EAGAIN;

	buf = kदो_स्मृति(dev->bulk_in_size, GFP_KERNEL);
	अगर (!buf)
		v4l2_err(&dev->v4l2_dev, "failed to allocate temporary buffer for emptying the internal device buffer. Next capture start will be slow\n");

	dev->status = STATUS_SHUTTING_DOWN;
	hdpvr_config_call(dev, CTRL_STOP_STREAMING_VALUE, 0x00);
	mutex_unlock(&dev->io_mutex);

	wake_up_पूर्णांकerruptible(&dev->रुको_buffer);
	msleep(50);

	flush_work(&dev->worker);

	mutex_lock(&dev->io_mutex);
	/* समाप्त the still outstanding urbs */
	hdpvr_cancel_queue(dev);

	/* emptying the device buffer beक्रमeshutting it करोwn */
	जबतक (buf && ++c < 500 &&
	       !usb_bulk_msg(dev->udev,
			     usb_rcvbulkpipe(dev->udev,
					     dev->bulk_in_endpoपूर्णांकAddr),
			     buf, dev->bulk_in_size, &actual_length,
			     BULK_URB_TIMEOUT)) अणु
		v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
			 "%2d: got %d bytes\n", c, actual_length);
	पूर्ण
	kमुक्त(buf);
	v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
		 "used %d urbs to empty device buffers\n", c-1);
	msleep(10);

	dev->status = STATUS_IDLE;

	वापस 0;
पूर्ण


/*=======================================================================*/
/*
 * video 4 linux 2 file operations
 */

अटल पूर्णांक hdpvr_खोलो(काष्ठा file *file)
अणु
	काष्ठा hdpvr_fh *fh = kzalloc(माप(*fh), GFP_KERNEL);

	अगर (fh == शून्य)
		वापस -ENOMEM;
	fh->legacy_mode = true;
	v4l2_fh_init(&fh->fh, video_devdata(file));
	v4l2_fh_add(&fh->fh);
	file->निजी_data = fh;
	वापस 0;
पूर्ण

अटल पूर्णांक hdpvr_release(काष्ठा file *file)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);

	mutex_lock(&dev->io_mutex);
	अगर (file->निजी_data == dev->owner) अणु
		hdpvr_stop_streaming(dev);
		dev->owner = शून्य;
	पूर्ण
	mutex_unlock(&dev->io_mutex);

	वापस v4l2_fh_release(file);
पूर्ण

/*
 * hdpvr_v4l2_पढ़ो()
 * will allocate buffers when called क्रम the first समय
 */
अटल sमाप_प्रकार hdpvr_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count,
			  loff_t *pos)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_buffer *buf = शून्य;
	काष्ठा urb *urb;
	अचिन्हित पूर्णांक ret = 0;
	पूर्णांक rem, cnt;

	अगर (*pos)
		वापस -ESPIPE;

	mutex_lock(&dev->io_mutex);
	अगर (dev->status == STATUS_IDLE) अणु
		अगर (hdpvr_start_streaming(dev)) अणु
			v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
				 "start_streaming failed\n");
			ret = -EIO;
			msleep(200);
			dev->status = STATUS_IDLE;
			mutex_unlock(&dev->io_mutex);
			जाओ err;
		पूर्ण
		dev->owner = file->निजी_data;
		prपूर्णांक_buffer_status();
	पूर्ण
	mutex_unlock(&dev->io_mutex);

	/* रुको क्रम the first buffer */
	अगर (!(file->f_flags & O_NONBLOCK)) अणु
		अगर (रुको_event_पूर्णांकerruptible(dev->रुको_data,
					     !list_empty_careful(&dev->rec_buff_list)))
			वापस -ERESTARTSYS;
	पूर्ण

	buf = hdpvr_get_next_buffer(dev);

	जबतक (count > 0 && buf) अणु

		अगर (buf->status != BUFSTAT_READY &&
		    dev->status != STATUS_DISCONNECTED) अणु
			पूर्णांक err;
			/* वापस nonblocking */
			अगर (file->f_flags & O_NONBLOCK) अणु
				अगर (!ret)
					ret = -EAGAIN;
				जाओ err;
			पूर्ण

			err = रुको_event_पूर्णांकerruptible_समयout(dev->रुको_data,
				buf->status == BUFSTAT_READY,
				msecs_to_jअगरfies(1000));
			अगर (err < 0) अणु
				ret = err;
				जाओ err;
			पूर्ण
			अगर (!err) अणु
				v4l2_info(&dev->v4l2_dev,
					  "timeout: restart streaming\n");
				mutex_lock(&dev->io_mutex);
				hdpvr_stop_streaming(dev);
				mutex_unlock(&dev->io_mutex);
				/*
				 * The FW needs about 4 seconds after streaming
				 * stopped beक्रमe it is पढ़ोy to restart
				 * streaming.
				 */
				msleep(4000);
				err = hdpvr_start_streaming(dev);
				अगर (err) अणु
					ret = err;
					जाओ err;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (buf->status != BUFSTAT_READY)
			अवरोध;

		/* set reमुख्यing bytes to copy */
		urb = buf->urb;
		rem = urb->actual_length - buf->pos;
		cnt = rem > count ? count : rem;

		अगर (copy_to_user(buffer, urb->transfer_buffer + buf->pos,
				 cnt)) अणु
			v4l2_err(&dev->v4l2_dev, "read: copy_to_user failed\n");
			अगर (!ret)
				ret = -EFAULT;
			जाओ err;
		पूर्ण

		buf->pos += cnt;
		count -= cnt;
		buffer += cnt;
		ret += cnt;

		/* finished, take next buffer */
		अगर (buf->pos == urb->actual_length) अणु
			mutex_lock(&dev->io_mutex);
			buf->pos = 0;
			buf->status = BUFSTAT_AVAILABLE;

			list_move_tail(&buf->buff_list, &dev->मुक्त_buff_list);

			prपूर्णांक_buffer_status();

			mutex_unlock(&dev->io_mutex);

			wake_up_पूर्णांकerruptible(&dev->रुको_buffer);

			buf = hdpvr_get_next_buffer(dev);
		पूर्ण
	पूर्ण
err:
	अगर (!ret && !buf)
		ret = -EAGAIN;
	वापस ret;
पूर्ण

अटल __poll_t hdpvr_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	__poll_t req_events = poll_requested_events(रुको);
	काष्ठा hdpvr_buffer *buf = शून्य;
	काष्ठा hdpvr_device *dev = video_drvdata(filp);
	__poll_t mask = v4l2_ctrl_poll(filp, रुको);

	अगर (!(req_events & (EPOLLIN | EPOLLRDNORM)))
		वापस mask;

	mutex_lock(&dev->io_mutex);

	अगर (dev->status == STATUS_IDLE) अणु
		अगर (hdpvr_start_streaming(dev)) अणु
			v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
				 "start_streaming failed\n");
			dev->status = STATUS_IDLE;
		पूर्ण अन्यथा अणु
			dev->owner = filp->निजी_data;
		पूर्ण

		prपूर्णांक_buffer_status();
	पूर्ण
	mutex_unlock(&dev->io_mutex);

	buf = hdpvr_get_next_buffer(dev);
	/* only रुको अगर no data is available */
	अगर (!buf || buf->status != BUFSTAT_READY) अणु
		poll_रुको(filp, &dev->रुको_data, रुको);
		buf = hdpvr_get_next_buffer(dev);
	पूर्ण
	अगर (buf && buf->status == BUFSTAT_READY)
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण


अटल स्थिर काष्ठा v4l2_file_operations hdpvr_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= hdpvr_खोलो,
	.release	= hdpvr_release,
	.पढ़ो		= hdpvr_पढ़ो,
	.poll		= hdpvr_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

/*=======================================================================*/
/*
 * V4L2 ioctl handling
 */

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);

	strscpy(cap->driver, "hdpvr", माप(cap->driver));
	strscpy(cap->card, "Hauppauge HD PVR", माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *_fh,
			v4l2_std_id std)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_fh *fh = _fh;
	u8 std_type = 1;

	अगर (!fh->legacy_mode && dev->options.video_input == HDPVR_COMPONENT)
		वापस -ENODATA;
	अगर (dev->status != STATUS_IDLE)
		वापस -EBUSY;
	अगर (std & V4L2_STD_525_60)
		std_type = 0;
	dev->cur_std = std;
	dev->width = 720;
	dev->height = std_type ? 576 : 480;

	वापस hdpvr_config_call(dev, CTRL_VIDEO_STD_TYPE, std_type);
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *_fh,
			v4l2_std_id *std)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_fh *fh = _fh;

	अगर (!fh->legacy_mode && dev->options.video_input == HDPVR_COMPONENT)
		वापस -ENODATA;
	*std = dev->cur_std;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querystd(काष्ठा file *file, व्योम *_fh, v4l2_std_id *a)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_video_info vid_info;
	काष्ठा hdpvr_fh *fh = _fh;
	पूर्णांक ret;

	*a = V4L2_STD_UNKNOWN;
	अगर (dev->options.video_input == HDPVR_COMPONENT)
		वापस fh->legacy_mode ? 0 : -ENODATA;
	ret = get_video_info(dev, &vid_info);
	अगर (vid_info.valid && vid_info.width == 720 &&
	    (vid_info.height == 480 || vid_info.height == 576)) अणु
		*a = (vid_info.height == 480) ?
			V4L2_STD_525_60 : V4L2_STD_625_50;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_s_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_fh *fh = _fh;
	पूर्णांक i;

	fh->legacy_mode = false;
	अगर (dev->options.video_input)
		वापस -ENODATA;
	अगर (dev->status != STATUS_IDLE)
		वापस -EBUSY;
	क्रम (i = 0; i < ARRAY_SIZE(hdpvr_dv_timings); i++)
		अगर (v4l2_match_dv_timings(timings, hdpvr_dv_timings + i, 0, false))
			अवरोध;
	अगर (i == ARRAY_SIZE(hdpvr_dv_timings))
		वापस -EINVAL;
	dev->cur_dv_timings = hdpvr_dv_timings[i];
	dev->width = hdpvr_dv_timings[i].bt.width;
	dev->height = hdpvr_dv_timings[i].bt.height;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_fh *fh = _fh;

	fh->legacy_mode = false;
	अगर (dev->options.video_input)
		वापस -ENODATA;
	*timings = dev->cur_dv_timings;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_query_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_fh *fh = _fh;
	काष्ठा hdpvr_video_info vid_info;
	bool पूर्णांकerlaced;
	पूर्णांक ret = 0;
	पूर्णांक i;

	fh->legacy_mode = false;
	अगर (dev->options.video_input)
		वापस -ENODATA;
	ret = get_video_info(dev, &vid_info);
	अगर (ret)
		वापस ret;
	अगर (!vid_info.valid)
		वापस -ENOLCK;
	पूर्णांकerlaced = vid_info.fps <= 30;
	क्रम (i = 0; i < ARRAY_SIZE(hdpvr_dv_timings); i++) अणु
		स्थिर काष्ठा v4l2_bt_timings *bt = &hdpvr_dv_timings[i].bt;
		अचिन्हित hsize;
		अचिन्हित vsize;
		अचिन्हित fps;

		hsize = V4L2_DV_BT_FRAME_WIDTH(bt);
		vsize = V4L2_DV_BT_FRAME_HEIGHT(bt);
		fps = (अचिन्हित)bt->pixelघड़ी / (hsize * vsize);
		अगर (bt->width != vid_info.width ||
		    bt->height != vid_info.height ||
		    bt->पूर्णांकerlaced != पूर्णांकerlaced ||
		    (fps != vid_info.fps && fps + 1 != vid_info.fps))
			जारी;
		*timings = hdpvr_dv_timings[i];
		अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(hdpvr_dv_timings))
		ret = -दुस्फल;

	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_fh *fh = _fh;

	fh->legacy_mode = false;
	स_रखो(timings->reserved, 0, माप(timings->reserved));
	अगर (dev->options.video_input)
		वापस -ENODATA;
	अगर (timings->index >= ARRAY_SIZE(hdpvr_dv_timings))
		वापस -EINVAL;
	timings->timings = hdpvr_dv_timings[timings->index];
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_dv_timings_cap(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_dv_timings_cap *cap)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_fh *fh = _fh;

	fh->legacy_mode = false;
	अगर (dev->options.video_input)
		वापस -ENODATA;
	cap->type = V4L2_DV_BT_656_1120;
	cap->bt.min_width = 720;
	cap->bt.max_width = 1920;
	cap->bt.min_height = 480;
	cap->bt.max_height = 1080;
	cap->bt.min_pixelघड़ी = 27000000;
	cap->bt.max_pixelघड़ी = 74250000;
	cap->bt.standards = V4L2_DV_BT_STD_CEA861;
	cap->bt.capabilities = V4L2_DV_BT_CAP_INTERLACED | V4L2_DV_BT_CAP_PROGRESSIVE;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *iname[] = अणु
	[HDPVR_COMPONENT] = "Component",
	[HDPVR_SVIDEO]    = "S-Video",
	[HDPVR_COMPOSITE] = "Composite",
पूर्ण;

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *_fh, काष्ठा v4l2_input *i)
अणु
	अचिन्हित पूर्णांक n;

	n = i->index;
	अगर (n >= HDPVR_VIDEO_INPUTS)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;

	strscpy(i->name, iname[n], माप(i->name));

	i->audioset = 1<<HDPVR_RCA_FRONT | 1<<HDPVR_RCA_BACK | 1<<HDPVR_SPDIF;

	i->capabilities = n ? V4L2_IN_CAP_STD : V4L2_IN_CAP_DV_TIMINGS;
	i->std = n ? V4L2_STD_ALL : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *_fh,
			  अचिन्हित पूर्णांक index)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	पूर्णांक retval;

	अगर (index >= HDPVR_VIDEO_INPUTS)
		वापस -EINVAL;

	अगर (dev->status != STATUS_IDLE)
		वापस -EBUSY;

	retval = hdpvr_config_call(dev, CTRL_VIDEO_INPUT_VALUE, index+1);
	अगर (!retval) अणु
		dev->options.video_input = index;
		/*
		 * Unक्रमtunately gstreamer calls ENUMSTD and bails out अगर it
		 * won't find any क्रमmats, even though component input is
		 * selected. This means that we have to leave tvnorms at
		 * V4L2_STD_ALL. We cannot use the 'legacy' trick since
		 * tvnorms is set at the device node level and not at the
		 * filehandle level.
		 *
		 * Comment this out क्रम now, but अगर the legacy mode can be
		 * हटाओd in the future, then this code should be enabled
		 * again.
		dev->video_dev.tvnorms =
			(index != HDPVR_COMPONENT) ? V4L2_STD_ALL : 0;
		 */
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *निजी_data,
			  अचिन्हित पूर्णांक *index)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);

	*index = dev->options.video_input;
	वापस 0;
पूर्ण


अटल स्थिर अक्षर *audio_iname[] = अणु
	[HDPVR_RCA_FRONT] = "RCA front",
	[HDPVR_RCA_BACK]  = "RCA back",
	[HDPVR_SPDIF]     = "SPDIF",
पूर्ण;

अटल पूर्णांक vidioc_क्रमागतaudio(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_audio *audio)
अणु
	अचिन्हित पूर्णांक n;

	n = audio->index;
	अगर (n >= HDPVR_AUDIO_INPUTS)
		वापस -EINVAL;

	audio->capability = V4L2_AUDCAP_STEREO;

	strscpy(audio->name, audio_iname[n], माप(audio->name));

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_audio(काष्ठा file *file, व्योम *निजी_data,
			  स्थिर काष्ठा v4l2_audio *audio)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	पूर्णांक retval;

	अगर (audio->index >= HDPVR_AUDIO_INPUTS)
		वापस -EINVAL;

	अगर (dev->status != STATUS_IDLE)
		वापस -EBUSY;

	retval = hdpvr_set_audio(dev, audio->index+1, dev->options.audio_codec);
	अगर (!retval)
		dev->options.audio_input = audio->index;

	वापस retval;
पूर्ण

अटल पूर्णांक vidioc_g_audio(काष्ठा file *file, व्योम *निजी_data,
			  काष्ठा v4l2_audio *audio)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);

	audio->index = dev->options.audio_input;
	audio->capability = V4L2_AUDCAP_STEREO;
	strscpy(audio->name, audio_iname[audio->index], माप(audio->name));
	वापस 0;
पूर्ण

अटल पूर्णांक hdpvr_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा hdpvr_device *dev =
		container_of(ctrl->handler, काष्ठा hdpvr_device, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		अगर (ctrl->val == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
		    dev->video_bitrate->val >= dev->video_bitrate_peak->val)
			dev->video_bitrate_peak->val =
					dev->video_bitrate->val + 100000;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hdpvr_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा hdpvr_device *dev =
		container_of(ctrl->handler, काष्ठा hdpvr_device, hdl);
	काष्ठा hdpvr_options *opt = &dev->options;
	पूर्णांक ret = -EINVAL;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		ret = hdpvr_config_call(dev, CTRL_BRIGHTNESS, ctrl->val);
		अगर (ret)
			अवरोध;
		dev->options.brightness = ctrl->val;
		वापस 0;
	हाल V4L2_CID_CONTRAST:
		ret = hdpvr_config_call(dev, CTRL_CONTRAST, ctrl->val);
		अगर (ret)
			अवरोध;
		dev->options.contrast = ctrl->val;
		वापस 0;
	हाल V4L2_CID_SATURATION:
		ret = hdpvr_config_call(dev, CTRL_SATURATION, ctrl->val);
		अगर (ret)
			अवरोध;
		dev->options.saturation = ctrl->val;
		वापस 0;
	हाल V4L2_CID_HUE:
		ret = hdpvr_config_call(dev, CTRL_HUE, ctrl->val);
		अगर (ret)
			अवरोध;
		dev->options.hue = ctrl->val;
		वापस 0;
	हाल V4L2_CID_SHARPNESS:
		ret = hdpvr_config_call(dev, CTRL_SHARPNESS, ctrl->val);
		अगर (ret)
			अवरोध;
		dev->options.sharpness = ctrl->val;
		वापस 0;
	हाल V4L2_CID_MPEG_AUDIO_ENCODING:
		अगर (dev->flags & HDPVR_FLAG_AC3_CAP) अणु
			opt->audio_codec = ctrl->val;
			वापस hdpvr_set_audio(dev, opt->audio_input + 1,
					      opt->audio_codec);
		पूर्ण
		वापस 0;
	हाल V4L2_CID_MPEG_VIDEO_ENCODING:
		वापस 0;
/*	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES: */
/*		अगर (ctrl->value == 0 && !(opt->gop_mode & 0x2)) अणु */
/*			opt->gop_mode |= 0x2; */
/*			hdpvr_config_call(dev, CTRL_GOP_MODE_VALUE, */
/*					  opt->gop_mode); */
/*		पूर्ण */
/*		अगर (ctrl->value == 128 && opt->gop_mode & 0x2) अणु */
/*			opt->gop_mode &= ~0x2; */
/*			hdpvr_config_call(dev, CTRL_GOP_MODE_VALUE, */
/*					  opt->gop_mode); */
/*		पूर्ण */
/*		अवरोध; */
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE: अणु
		uपूर्णांक peak_bitrate = dev->video_bitrate_peak->val / 100000;
		uपूर्णांक bitrate = dev->video_bitrate->val / 100000;

		अगर (ctrl->is_new) अणु
			अगर (ctrl->val == V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
				opt->bitrate_mode = HDPVR_CONSTANT;
			अन्यथा
				opt->bitrate_mode = HDPVR_VARIABLE_AVERAGE;
			hdpvr_config_call(dev, CTRL_BITRATE_MODE_VALUE,
					  opt->bitrate_mode);
			v4l2_ctrl_activate(dev->video_bitrate_peak,
				ctrl->val != V4L2_MPEG_VIDEO_BITRATE_MODE_CBR);
		पूर्ण

		अगर (dev->video_bitrate_peak->is_new ||
		    dev->video_bitrate->is_new) अणु
			opt->bitrate = bitrate;
			opt->peak_bitrate = peak_bitrate;
			hdpvr_set_bitrate(dev);
		पूर्ण
		वापस 0;
	पूर्ण
	हाल V4L2_CID_MPEG_STREAM_TYPE:
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *निजी_data,
				    काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index != 0)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_MPEG;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *_fh,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(file);
	काष्ठा hdpvr_fh *fh = _fh;
	पूर्णांक ret;

	/*
	 * The original driver would always वापसs the current detected
	 * resolution as the क्रमmat (and EFAULT अगर it couldn't be detected).
	 * With the पूर्णांकroduction of VIDIOC_QUERY_DV_TIMINGS there is now a
	 * better way of करोing this, but to stay compatible with existing
	 * applications we assume legacy mode every समय an application खोलोs
	 * the device. Only अगर one of the new DV_TIMINGS ioctls is called
	 * will the filehandle go पूर्णांकo 'normal' mode where g_fmt वापसs the
	 * last set क्रमmat.
	 */
	अगर (fh->legacy_mode) अणु
		काष्ठा hdpvr_video_info vid_info;

		ret = get_video_info(dev, &vid_info);
		अगर (ret < 0)
			वापस ret;
		अगर (!vid_info.valid)
			वापस -EFAULT;
		f->fmt.pix.width = vid_info.width;
		f->fmt.pix.height = vid_info.height;
	पूर्ण अन्यथा अणु
		f->fmt.pix.width = dev->width;
		f->fmt.pix.height = dev->height;
	पूर्ण
	f->fmt.pix.pixelक्रमmat	= V4L2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage	= dev->bulk_in_size;
	f->fmt.pix.bytesperline	= 0;
	अगर (f->fmt.pix.width == 720) अणु
		/* SDTV क्रमmats */
		f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
		f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	पूर्ण अन्यथा अणु
		/* HDTV क्रमmats */
		f->fmt.pix.colorspace = V4L2_COLORSPACE_REC709;
		f->fmt.pix.field = V4L2_FIELD_NONE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_encoder_cmd(काष्ठा file *filp, व्योम *priv,
			       काष्ठा v4l2_encoder_cmd *a)
अणु
	काष्ठा hdpvr_device *dev = video_drvdata(filp);
	पूर्णांक res = 0;

	mutex_lock(&dev->io_mutex);
	a->flags = 0;

	चयन (a->cmd) अणु
	हाल V4L2_ENC_CMD_START:
		अगर (dev->owner && filp->निजी_data != dev->owner) अणु
			res = -EBUSY;
			अवरोध;
		पूर्ण
		अगर (dev->status == STATUS_STREAMING)
			अवरोध;
		res = hdpvr_start_streaming(dev);
		अगर (!res)
			dev->owner = filp->निजी_data;
		अन्यथा
			dev->status = STATUS_IDLE;
		अवरोध;
	हाल V4L2_ENC_CMD_STOP:
		अगर (dev->owner && filp->निजी_data != dev->owner) अणु
			res = -EBUSY;
			अवरोध;
		पूर्ण
		अगर (dev->status == STATUS_IDLE)
			अवरोध;
		res = hdpvr_stop_streaming(dev);
		अगर (!res)
			dev->owner = शून्य;
		अवरोध;
	शेष:
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
			 "Unsupported encoder cmd %d\n", a->cmd);
		res = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&dev->io_mutex);
	वापस res;
पूर्ण

अटल पूर्णांक vidioc_try_encoder_cmd(काष्ठा file *filp, व्योम *priv,
					काष्ठा v4l2_encoder_cmd *a)
अणु
	a->flags = 0;
	चयन (a->cmd) अणु
	हाल V4L2_ENC_CMD_START:
	हाल V4L2_ENC_CMD_STOP:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops hdpvr_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,
	.vidioc_s_std		= vidioc_s_std,
	.vidioc_g_std		= vidioc_g_std,
	.vidioc_querystd	= vidioc_querystd,
	.vidioc_s_dv_timings	= vidioc_s_dv_timings,
	.vidioc_g_dv_timings	= vidioc_g_dv_timings,
	.vidioc_query_dv_timings= vidioc_query_dv_timings,
	.vidioc_क्रमागत_dv_timings	= vidioc_क्रमागत_dv_timings,
	.vidioc_dv_timings_cap	= vidioc_dv_timings_cap,
	.vidioc_क्रमागत_input	= vidioc_क्रमागत_input,
	.vidioc_g_input		= vidioc_g_input,
	.vidioc_s_input		= vidioc_s_input,
	.vidioc_क्रमागतaudio	= vidioc_क्रमागतaudio,
	.vidioc_g_audio		= vidioc_g_audio,
	.vidioc_s_audio		= vidioc_s_audio,
	.vidioc_क्रमागत_fmt_vid_cap= vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_encoder_cmd	= vidioc_encoder_cmd,
	.vidioc_try_encoder_cmd	= vidioc_try_encoder_cmd,
	.vidioc_log_status	= v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल व्योम hdpvr_device_release(काष्ठा video_device *vdev)
अणु
	काष्ठा hdpvr_device *dev = video_get_drvdata(vdev);

	hdpvr_delete(dev);
	flush_work(&dev->worker);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	v4l2_ctrl_handler_मुक्त(&dev->hdl);

	/* deरेजिस्टर I2C adapter */
#अगर IS_ENABLED(CONFIG_I2C)
	mutex_lock(&dev->i2c_mutex);
	i2c_del_adapter(&dev->i2c_adapter);
	mutex_unlock(&dev->i2c_mutex);
#पूर्ण_अगर /* CONFIG_I2C */

	kमुक्त(dev->usbc_buf);
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा video_device hdpvr_video_ढाँचा = अणु
	.fops			= &hdpvr_fops,
	.release		= hdpvr_device_release,
	.ioctl_ops		= &hdpvr_ioctl_ops,
	.tvnorms		= V4L2_STD_ALL,
	.device_caps		= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_AUDIO |
				  V4L2_CAP_READWRITE,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops hdpvr_ctrl_ops = अणु
	.try_ctrl = hdpvr_try_ctrl,
	.s_ctrl = hdpvr_s_ctrl,
पूर्ण;

पूर्णांक hdpvr_रेजिस्टर_videodev(काष्ठा hdpvr_device *dev, काष्ठा device *parent,
			    पूर्णांक devnum)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dev->hdl;
	bool ac3 = dev->flags & HDPVR_FLAG_AC3_CAP;
	पूर्णांक res;

	dev->cur_std = V4L2_STD_525_60;
	dev->width = 720;
	dev->height = 480;
	dev->cur_dv_timings = hdpvr_dv_timings[HDPVR_DEF_DV_TIMINGS_IDX];
	v4l2_ctrl_handler_init(hdl, 11);
	अगर (dev->fw_ver > 0x15) अणु
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0x0, 0xff, 1, 0x80);
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_CONTRAST, 0x0, 0xff, 1, 0x40);
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_SATURATION, 0x0, 0xff, 1, 0x40);
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_HUE, 0x0, 0x1e, 1, 0xf);
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_SHARPNESS, 0x0, 0xff, 1, 0x80);
	पूर्ण अन्यथा अणु
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0x0, 0xff, 1, 0x86);
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_CONTRAST, 0x0, 0xff, 1, 0x80);
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_SATURATION, 0x0, 0xff, 1, 0x80);
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_HUE, 0x0, 0xff, 1, 0x80);
		v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
			V4L2_CID_SHARPNESS, 0x0, 0xff, 1, 0x80);
	पूर्ण

	v4l2_ctrl_new_std_menu(hdl, &hdpvr_ctrl_ops,
		V4L2_CID_MPEG_STREAM_TYPE,
		V4L2_MPEG_STREAM_TYPE_MPEG2_TS,
		0x1, V4L2_MPEG_STREAM_TYPE_MPEG2_TS);
	v4l2_ctrl_new_std_menu(hdl, &hdpvr_ctrl_ops,
		V4L2_CID_MPEG_AUDIO_ENCODING,
		ac3 ? V4L2_MPEG_AUDIO_ENCODING_AC3 : V4L2_MPEG_AUDIO_ENCODING_AAC,
		0x7, ac3 ? dev->options.audio_codec : V4L2_MPEG_AUDIO_ENCODING_AAC);
	v4l2_ctrl_new_std_menu(hdl, &hdpvr_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_ENCODING,
		V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC, 0x3,
		V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC);

	dev->video_mode = v4l2_ctrl_new_std_menu(hdl, &hdpvr_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
		V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 0,
		V4L2_MPEG_VIDEO_BITRATE_MODE_CBR);

	dev->video_bitrate = v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE,
		1000000, 13500000, 100000, 6500000);
	dev->video_bitrate_peak = v4l2_ctrl_new_std(hdl, &hdpvr_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_PEAK,
		1100000, 20200000, 100000, 9000000);
	dev->v4l2_dev.ctrl_handler = hdl;
	अगर (hdl->error) अणु
		res = hdl->error;
		v4l2_err(&dev->v4l2_dev, "Could not register controls\n");
		जाओ error;
	पूर्ण
	v4l2_ctrl_cluster(3, &dev->video_mode);
	res = v4l2_ctrl_handler_setup(hdl);
	अगर (res < 0) अणु
		v4l2_err(&dev->v4l2_dev, "Could not setup controls\n");
		जाओ error;
	पूर्ण

	/* setup and रेजिस्टर video device */
	dev->video_dev = hdpvr_video_ढाँचा;
	strscpy(dev->video_dev.name, "Hauppauge HD PVR",
		माप(dev->video_dev.name));
	dev->video_dev.v4l2_dev = &dev->v4l2_dev;
	video_set_drvdata(&dev->video_dev, dev);

	res = video_रेजिस्टर_device(&dev->video_dev, VFL_TYPE_VIDEO, devnum);
	अगर (res < 0) अणु
		v4l2_err(&dev->v4l2_dev, "video_device registration failed\n");
		जाओ error;
	पूर्ण

	वापस 0;
error:
	v4l2_ctrl_handler_मुक्त(hdl);
	वापस res;
पूर्ण
