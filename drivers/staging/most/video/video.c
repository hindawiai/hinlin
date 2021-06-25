<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * video.c - V4L2 component क्रम Mostcore
 *
 * Copyright (C) 2015, Microchip Technology Germany II GmbH & Co. KG
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/suspend.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/mutex.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <linux/most.h>

#घोषणा V4L2_CMP_MAX_INPUT  1

अटल काष्ठा most_component comp;

काष्ठा most_video_dev अणु
	काष्ठा most_पूर्णांकerface *अगरace;
	पूर्णांक ch_idx;
	काष्ठा list_head list;
	bool mute;

	काष्ठा list_head pending_mbos;
	spinlock_t list_lock;

	काष्ठा v4l2_device v4l2_dev;
	atomic_t access_ref;
	काष्ठा video_device *vdev;
	अचिन्हित पूर्णांक ctrl_input;

	काष्ठा mutex lock;

	रुको_queue_head_t रुको_data;
पूर्ण;

काष्ठा comp_fh अणु
	/* must be the first field of this काष्ठा! */
	काष्ठा v4l2_fh fh;
	काष्ठा most_video_dev *mdev;
	u32 offs;
पूर्ण;

अटल काष्ठा list_head video_devices = LIST_HEAD_INIT(video_devices);
अटल DEFINE_SPINLOCK(list_lock);

अटल अंतरभूत bool data_पढ़ोy(काष्ठा most_video_dev *mdev)
अणु
	वापस !list_empty(&mdev->pending_mbos);
पूर्ण

अटल अंतरभूत काष्ठा mbo *get_top_mbo(काष्ठा most_video_dev *mdev)
अणु
	वापस list_first_entry(&mdev->pending_mbos, काष्ठा mbo, list);
पूर्ण

अटल पूर्णांक comp_vdev_खोलो(काष्ठा file *filp)
अणु
	पूर्णांक ret;
	काष्ठा video_device *vdev = video_devdata(filp);
	काष्ठा most_video_dev *mdev = video_drvdata(filp);
	काष्ठा comp_fh *fh;

	चयन (vdev->vfl_type) अणु
	हाल VFL_TYPE_VIDEO:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	fh = kzalloc(माप(*fh), GFP_KERNEL);
	अगर (!fh)
		वापस -ENOMEM;

	अगर (!atomic_inc_and_test(&mdev->access_ref)) अणु
		v4l2_err(&mdev->v4l2_dev, "too many clients\n");
		ret = -EBUSY;
		जाओ err_dec;
	पूर्ण

	fh->mdev = mdev;
	v4l2_fh_init(&fh->fh, vdev);
	filp->निजी_data = fh;

	v4l2_fh_add(&fh->fh);

	ret = most_start_channel(mdev->अगरace, mdev->ch_idx, &comp);
	अगर (ret) अणु
		v4l2_err(&mdev->v4l2_dev, "most_start_channel() failed\n");
		जाओ err_rm;
	पूर्ण

	वापस 0;

err_rm:
	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);

err_dec:
	atomic_dec(&mdev->access_ref);
	kमुक्त(fh);
	वापस ret;
पूर्ण

अटल पूर्णांक comp_vdev_बंद(काष्ठा file *filp)
अणु
	काष्ठा comp_fh *fh = filp->निजी_data;
	काष्ठा most_video_dev *mdev = fh->mdev;
	काष्ठा mbo *mbo, *पंचांगp;

	/*
	 * We need to put MBOs back beक्रमe we call most_stop_channel()
	 * to deallocate MBOs.
	 * From the other hand mostcore still calling rx_completion()
	 * to deliver MBOs until most_stop_channel() is called.
	 * Use mute to work around this issue.
	 * This must be implemented in core.
	 */

	spin_lock_irq(&mdev->list_lock);
	mdev->mute = true;
	list_क्रम_each_entry_safe(mbo, पंचांगp, &mdev->pending_mbos, list) अणु
		list_del(&mbo->list);
		spin_unlock_irq(&mdev->list_lock);
		most_put_mbo(mbo);
		spin_lock_irq(&mdev->list_lock);
	पूर्ण
	spin_unlock_irq(&mdev->list_lock);
	most_stop_channel(mdev->अगरace, mdev->ch_idx, &comp);
	mdev->mute = false;

	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);

	atomic_dec(&mdev->access_ref);
	kमुक्त(fh);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार comp_vdev_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा comp_fh *fh = filp->निजी_data;
	काष्ठा most_video_dev *mdev = fh->mdev;
	पूर्णांक ret = 0;

	अगर (*pos)
		वापस -ESPIPE;

	अगर (!mdev)
		वापस -ENODEV;

	/* रुको क्रम the first buffer */
	अगर (!(filp->f_flags & O_NONBLOCK)) अणु
		अगर (रुको_event_पूर्णांकerruptible(mdev->रुको_data, data_पढ़ोy(mdev)))
			वापस -ERESTARTSYS;
	पूर्ण

	अगर (!data_पढ़ोy(mdev))
		वापस -EAGAIN;

	जबतक (count > 0 && data_पढ़ोy(mdev)) अणु
		काष्ठा mbo *स्थिर mbo = get_top_mbo(mdev);
		पूर्णांक स्थिर rem = mbo->processed_length - fh->offs;
		पूर्णांक स्थिर cnt = rem < count ? rem : count;

		अगर (copy_to_user(buf, mbo->virt_address + fh->offs, cnt)) अणु
			v4l2_err(&mdev->v4l2_dev, "read: copy_to_user failed\n");
			अगर (!ret)
				ret = -EFAULT;
			वापस ret;
		पूर्ण

		fh->offs += cnt;
		count -= cnt;
		buf += cnt;
		ret += cnt;

		अगर (cnt >= rem) अणु
			fh->offs = 0;
			spin_lock_irq(&mdev->list_lock);
			list_del(&mbo->list);
			spin_unlock_irq(&mdev->list_lock);
			most_put_mbo(mbo);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल __poll_t comp_vdev_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा comp_fh *fh = filp->निजी_data;
	काष्ठा most_video_dev *mdev = fh->mdev;
	__poll_t mask = 0;

	/* only रुको अगर no data is available */
	अगर (!data_पढ़ोy(mdev))
		poll_रुको(filp, &mdev->रुको_data, रुको);
	अगर (data_पढ़ोy(mdev))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल व्योम comp_set_क्रमmat_काष्ठा(काष्ठा v4l2_क्रमmat *f)
अणु
	f->fmt.pix.width = 8;
	f->fmt.pix.height = 8;
	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = 188 * 2;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_REC709;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.priv = 0;
पूर्ण

अटल पूर्णांक comp_set_क्रमmat(काष्ठा most_video_dev *mdev, अचिन्हित पूर्णांक cmd,
			   काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	अगर (क्रमmat->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_MPEG)
		वापस -EINVAL;

	अगर (cmd == VIDIOC_TRY_FMT)
		वापस 0;

	comp_set_क्रमmat_काष्ठा(क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा comp_fh *fh = priv;
	काष्ठा most_video_dev *mdev = fh->mdev;

	strscpy(cap->driver, "v4l2_component", माप(cap->driver));
	strscpy(cap->card, "MOST", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "%s", mdev->अगरace->description);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index)
		वापस -EINVAL;

	म_नकल(f->description, "MPEG");
	f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	f->flags = V4L2_FMT_FLAG_COMPRESSED;
	f->pixelक्रमmat = V4L2_PIX_FMT_MPEG;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	comp_set_क्रमmat_काष्ठा(f);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा comp_fh *fh = priv;
	काष्ठा most_video_dev *mdev = fh->mdev;

	वापस comp_set_क्रमmat(mdev, VIDIOC_TRY_FMT, f);
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा comp_fh *fh = priv;
	काष्ठा most_video_dev *mdev = fh->mdev;

	वापस comp_set_क्रमmat(mdev, VIDIOC_S_FMT, f);
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *norm)
अणु
	*norm = V4L2_STD_UNKNOWN;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *input)
अणु
	काष्ठा comp_fh *fh = priv;
	काष्ठा most_video_dev *mdev = fh->mdev;

	अगर (input->index >= V4L2_CMP_MAX_INPUT)
		वापस -EINVAL;

	म_नकल(input->name, "MOST Video");
	input->type |= V4L2_INPUT_TYPE_CAMERA;
	input->audioset = 0;

	input->std = mdev->vdev->tvnorms;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा comp_fh *fh = priv;
	काष्ठा most_video_dev *mdev = fh->mdev;
	*i = mdev->ctrl_input;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक index)
अणु
	काष्ठा comp_fh *fh = priv;
	काष्ठा most_video_dev *mdev = fh->mdev;

	अगर (index >= V4L2_CMP_MAX_INPUT)
		वापस -EINVAL;
	mdev->ctrl_input = index;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations comp_fops = अणु
	.owner      = THIS_MODULE,
	.खोलो       = comp_vdev_खोलो,
	.release    = comp_vdev_बंद,
	.पढ़ो       = comp_vdev_पढ़ो,
	.poll       = comp_vdev_poll,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap            = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap    = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap       = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap     = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap       = vidioc_s_fmt_vid_cap,
	.vidioc_g_std               = vidioc_g_std,
	.vidioc_क्रमागत_input          = vidioc_क्रमागत_input,
	.vidioc_g_input             = vidioc_g_input,
	.vidioc_s_input             = vidioc_s_input,
पूर्ण;

अटल स्थिर काष्ठा video_device comp_videodev_ढाँचा = अणु
	.fops = &comp_fops,
	.release = video_device_release,
	.ioctl_ops = &video_ioctl_ops,
	.tvnorms = V4L2_STD_UNKNOWN,
	.device_caps = V4L2_CAP_READWRITE | V4L2_CAP_VIDEO_CAPTURE,
पूर्ण;

/**************************************************************************/

अटल काष्ठा most_video_dev *get_comp_dev(
	काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx)
अणु
	काष्ठा most_video_dev *mdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list_lock, flags);
	list_क्रम_each_entry(mdev, &video_devices, list) अणु
		अगर (mdev->अगरace == अगरace && mdev->ch_idx == channel_idx) अणु
			spin_unlock_irqrestore(&list_lock, flags);
			वापस mdev;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&list_lock, flags);
	वापस शून्य;
पूर्ण

अटल पूर्णांक comp_rx_data(काष्ठा mbo *mbo)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा most_video_dev *mdev =
		get_comp_dev(mbo->अगरp, mbo->hdm_channel_id);

	अगर (!mdev)
		वापस -EIO;

	spin_lock_irqsave(&mdev->list_lock, flags);
	अगर (unlikely(mdev->mute)) अणु
		spin_unlock_irqrestore(&mdev->list_lock, flags);
		वापस -EIO;
	पूर्ण

	list_add_tail(&mbo->list, &mdev->pending_mbos);
	spin_unlock_irqrestore(&mdev->list_lock, flags);
	wake_up_पूर्णांकerruptible(&mdev->रुको_data);
	वापस 0;
पूर्ण

अटल पूर्णांक comp_रेजिस्टर_videodev(काष्ठा most_video_dev *mdev)
अणु
	पूर्णांक ret;

	init_रुकोqueue_head(&mdev->रुको_data);

	/* allocate and fill v4l2 video काष्ठा */
	mdev->vdev = video_device_alloc();
	अगर (!mdev->vdev)
		वापस -ENOMEM;

	/* Fill the video capture device काष्ठा */
	*mdev->vdev = comp_videodev_ढाँचा;
	mdev->vdev->v4l2_dev = &mdev->v4l2_dev;
	mdev->vdev->lock = &mdev->lock;
	snम_लिखो(mdev->vdev->name, माप(mdev->vdev->name), "MOST: %s",
		 mdev->v4l2_dev.name);

	/* Register the v4l2 device */
	video_set_drvdata(mdev->vdev, mdev);
	ret = video_रेजिस्टर_device(mdev->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&mdev->v4l2_dev, "video_register_device failed (%d)\n",
			 ret);
		video_device_release(mdev->vdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम comp_unरेजिस्टर_videodev(काष्ठा most_video_dev *mdev)
अणु
	video_unरेजिस्टर_device(mdev->vdev);
पूर्ण

अटल व्योम comp_v4l2_dev_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा most_video_dev *mdev =
		container_of(v4l2_dev, काष्ठा most_video_dev, v4l2_dev);

	v4l2_device_unरेजिस्टर(v4l2_dev);
	kमुक्त(mdev);
पूर्ण

अटल पूर्णांक comp_probe_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
			      काष्ठा most_channel_config *ccfg, अक्षर *name,
			      अक्षर *args)
अणु
	पूर्णांक ret;
	काष्ठा most_video_dev *mdev = get_comp_dev(अगरace, channel_idx);

	अगर (mdev) अणु
		pr_err("channel already linked\n");
		वापस -EEXIST;
	पूर्ण

	अगर (ccfg->direction != MOST_CH_RX) अणु
		pr_err("wrong direction, expect rx\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ccfg->data_type != MOST_CH_SYNC &&
	    ccfg->data_type != MOST_CH_ISOC) अणु
		pr_err("wrong channel type, expect sync or isoc\n");
		वापस -EINVAL;
	पूर्ण

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	mutex_init(&mdev->lock);
	atomic_set(&mdev->access_ref, -1);
	spin_lock_init(&mdev->list_lock);
	INIT_LIST_HEAD(&mdev->pending_mbos);
	mdev->अगरace = अगरace;
	mdev->ch_idx = channel_idx;
	mdev->v4l2_dev.release = comp_v4l2_dev_release;

	/* Create the v4l2_device */
	strscpy(mdev->v4l2_dev.name, name, माप(mdev->v4l2_dev.name));
	ret = v4l2_device_रेजिस्टर(शून्य, &mdev->v4l2_dev);
	अगर (ret) अणु
		pr_err("v4l2_device_register() failed\n");
		kमुक्त(mdev);
		वापस ret;
	पूर्ण

	ret = comp_रेजिस्टर_videodev(mdev);
	अगर (ret)
		जाओ err_unreg;

	spin_lock_irq(&list_lock);
	list_add(&mdev->list, &video_devices);
	spin_unlock_irq(&list_lock);
	वापस 0;

err_unreg:
	v4l2_device_disconnect(&mdev->v4l2_dev);
	v4l2_device_put(&mdev->v4l2_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक comp_disconnect_channel(काष्ठा most_पूर्णांकerface *अगरace,
				   पूर्णांक channel_idx)
अणु
	काष्ठा most_video_dev *mdev = get_comp_dev(अगरace, channel_idx);

	अगर (!mdev) अणु
		pr_err("no such channel is linked\n");
		वापस -ENOENT;
	पूर्ण

	spin_lock_irq(&list_lock);
	list_del(&mdev->list);
	spin_unlock_irq(&list_lock);

	comp_unरेजिस्टर_videodev(mdev);
	v4l2_device_disconnect(&mdev->v4l2_dev);
	v4l2_device_put(&mdev->v4l2_dev);
	वापस 0;
पूर्ण

अटल काष्ठा most_component comp = अणु
	.mod = THIS_MODULE,
	.name = "video",
	.probe_channel = comp_probe_channel,
	.disconnect_channel = comp_disconnect_channel,
	.rx_completion = comp_rx_data,
पूर्ण;

अटल पूर्णांक __init comp_init(व्योम)
अणु
	पूर्णांक err;

	err = most_रेजिस्टर_component(&comp);
	अगर (err)
		वापस err;
	err = most_रेजिस्टर_configfs_subsys(&comp);
	अगर (err) अणु
		most_deरेजिस्टर_component(&comp);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास comp_निकास(व्योम)
अणु
	काष्ठा most_video_dev *mdev, *पंचांगp;

	/*
	 * As the mostcore currently करोesn't call disconnect_channel()
	 * क्रम linked channels जबतक we call most_deरेजिस्टर_component()
	 * we simulate this call here.
	 * This must be fixed in core.
	 */
	spin_lock_irq(&list_lock);
	list_क्रम_each_entry_safe(mdev, पंचांगp, &video_devices, list) अणु
		list_del(&mdev->list);
		spin_unlock_irq(&list_lock);

		comp_unरेजिस्टर_videodev(mdev);
		v4l2_device_disconnect(&mdev->v4l2_dev);
		v4l2_device_put(&mdev->v4l2_dev);
		spin_lock_irq(&list_lock);
	पूर्ण
	spin_unlock_irq(&list_lock);

	most_deरेजिस्टर_configfs_subsys(&comp);
	most_deरेजिस्टर_component(&comp);
	BUG_ON(!list_empty(&video_devices));
पूर्ण

module_init(comp_init);
module_निकास(comp_निकास);

MODULE_DESCRIPTION("V4L2 Component Module for Mostcore");
MODULE_AUTHOR("Andrey Shvetsov <andrey.shvetsov@k2l.de>");
MODULE_LICENSE("GPL");
