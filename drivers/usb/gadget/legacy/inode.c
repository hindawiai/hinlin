<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * inode.c -- user mode fileप्रणाली api क्रम usb gadget controllers
 *
 * Copyright (C) 2003-2004 David Brownell
 * Copyright (C) 2003 Agilent Technologies
 */


/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/uts.h>
#समावेश <linux/रुको.h>
#समावेश <linux/compiler.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/aपन.स>
#समावेश <linux/uपन.स>
#समावेश <linux/refcount.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/usb/gadgetfs.h>
#समावेश <linux/usb/gadget.h>


/*
 * The gadgetfs API maps each endpoपूर्णांक to a file descriptor so that you
 * can use standard synchronous पढ़ो/ग_लिखो calls क्रम I/O.  There's some
 * O_NONBLOCK and O_ASYNC/FASYNC style i/o support.  Example usermode
 * drivers show how this works in practice.  You can also use AIO to
 * eliminate I/O gaps between requests, to help when streaming data.
 *
 * Key parts that must be USB-specअगरic are protocols defining how the
 * पढ़ो/ग_लिखो operations relate to the hardware state machines.  There
 * are two types of files.  One type is क्रम the device, implementing ep0.
 * The other type is क्रम each IN or OUT endpoपूर्णांक.  In both हालs, the
 * user mode driver must configure the hardware beक्रमe using it.
 *
 * - First, dev_config() is called when /dev/gadget/$CHIP is configured
 *   (by writing configuration and device descriptors).  Afterwards it
 *   may serve as a source of device events, used to handle all control
 *   requests other than basic क्रमागतeration.
 *
 * - Then, after a SET_CONFIGURATION control request, ep_config() is
 *   called when each /dev/gadget/ep* file is configured (by writing
 *   endpoपूर्णांक descriptors).  Afterwards these files are used to ग_लिखो()
 *   IN data or to पढ़ो() OUT data.  To halt the endpoपूर्णांक, a "wrong
 *   direction" request is issued (like पढ़ोing an IN endpoपूर्णांक).
 *
 * Unlike "usbfs" the only ioctl()s are क्रम things that are rare, and maybe
 * not possible on all hardware.  For example, precise fault handling with
 * respect to data left in endpoपूर्णांक fअगरos after पातed operations; or
 * selective clearing of endpoपूर्णांक halts, to implement SET_INTERFACE.
 */

#घोषणा	DRIVER_DESC	"USB Gadget filesystem"
#घोषणा	DRIVER_VERSION	"24 Aug 2004"

अटल स्थिर अक्षर driver_desc [] = DRIVER_DESC;
अटल स्थिर अक्षर लघुname [] = "gadgetfs";

MODULE_DESCRIPTION (DRIVER_DESC);
MODULE_AUTHOR ("David Brownell");
MODULE_LICENSE ("GPL");

अटल पूर्णांक ep_खोलो(काष्ठा inode *, काष्ठा file *);


/*----------------------------------------------------------------------*/

#घोषणा GADGETFS_MAGIC		0xaee71ee7

/* /dev/gadget/$CHIP represents ep0 and the whole device */
क्रमागत ep0_state अणु
	/* DISABLED is the initial state. */
	STATE_DEV_DISABLED = 0,

	/* Only one खोलो() of /dev/gadget/$CHIP; only one file tracks
	 * ep0/device i/o modes and binding to the controller.  Driver
	 * must always ग_लिखो descriptors to initialize the device, then
	 * the device becomes UNCONNECTED until क्रमागतeration.
	 */
	STATE_DEV_OPENED,

	/* From then on, ep0 fd is in either of two basic modes:
	 * - (UN)CONNECTED: पढ़ो usb_gadgetfs_event(s) from it
	 * - SETUP: पढ़ो/ग_लिखो will transfer control data and succeed;
	 *   or अगर "wrong direction", perक्रमms protocol stall
	 */
	STATE_DEV_UNCONNECTED,
	STATE_DEV_CONNECTED,
	STATE_DEV_SETUP,

	/* UNBOUND means the driver बंदd ep0, so the device won't be
	 * accessible again (DEV_DISABLED) until all fds are बंदd.
	 */
	STATE_DEV_UNBOUND,
पूर्ण;

/* enough क्रम the whole queue: most events invalidate others */
#घोषणा	N_EVENT			5

काष्ठा dev_data अणु
	spinlock_t			lock;
	refcount_t			count;
	पूर्णांक				udc_usage;
	क्रमागत ep0_state			state;		/* P: lock */
	काष्ठा usb_gadgetfs_event	event [N_EVENT];
	अचिन्हित			ev_next;
	काष्ठा fasync_काष्ठा		*fasync;
	u8				current_config;

	/* drivers पढ़ोing ep0 MUST handle control requests (SETUP)
	 * reported that way; अन्यथा the host will समय out.
	 */
	अचिन्हित			usermode_setup : 1,
					setup_in : 1,
					setup_can_stall : 1,
					setup_out_पढ़ोy : 1,
					setup_out_error : 1,
					setup_पात : 1,
					gadget_रेजिस्टरed : 1;
	अचिन्हित			setup_wLength;

	/* the rest is basically ग_लिखो-once */
	काष्ठा usb_config_descriptor	*config, *hs_config;
	काष्ठा usb_device_descriptor	*dev;
	काष्ठा usb_request		*req;
	काष्ठा usb_gadget		*gadget;
	काष्ठा list_head		epfiles;
	व्योम				*buf;
	रुको_queue_head_t		रुको;
	काष्ठा super_block		*sb;
	काष्ठा dentry			*dentry;

	/* except this scratch i/o buffer क्रम ep0 */
	u8				rbuf [256];
पूर्ण;

अटल अंतरभूत व्योम get_dev (काष्ठा dev_data *data)
अणु
	refcount_inc (&data->count);
पूर्ण

अटल व्योम put_dev (काष्ठा dev_data *data)
अणु
	अगर (likely (!refcount_dec_and_test (&data->count)))
		वापस;
	/* needs no more cleanup */
	BUG_ON (रुकोqueue_active (&data->रुको));
	kमुक्त (data);
पूर्ण

अटल काष्ठा dev_data *dev_new (व्योम)
अणु
	काष्ठा dev_data		*dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;
	dev->state = STATE_DEV_DISABLED;
	refcount_set (&dev->count, 1);
	spin_lock_init (&dev->lock);
	INIT_LIST_HEAD (&dev->epfiles);
	init_रुकोqueue_head (&dev->रुको);
	वापस dev;
पूर्ण

/*----------------------------------------------------------------------*/

/* other /dev/gadget/$ENDPOINT files represent endpoपूर्णांकs */
क्रमागत ep_state अणु
	STATE_EP_DISABLED = 0,
	STATE_EP_READY,
	STATE_EP_ENABLED,
	STATE_EP_UNBOUND,
पूर्ण;

काष्ठा ep_data अणु
	काष्ठा mutex			lock;
	क्रमागत ep_state			state;
	refcount_t			count;
	काष्ठा dev_data			*dev;
	/* must hold dev->lock beक्रमe accessing ep or req */
	काष्ठा usb_ep			*ep;
	काष्ठा usb_request		*req;
	sमाप_प्रकार				status;
	अक्षर				name [16];
	काष्ठा usb_endpoपूर्णांक_descriptor	desc, hs_desc;
	काष्ठा list_head		epfiles;
	रुको_queue_head_t		रुको;
	काष्ठा dentry			*dentry;
पूर्ण;

अटल अंतरभूत व्योम get_ep (काष्ठा ep_data *data)
अणु
	refcount_inc (&data->count);
पूर्ण

अटल व्योम put_ep (काष्ठा ep_data *data)
अणु
	अगर (likely (!refcount_dec_and_test (&data->count)))
		वापस;
	put_dev (data->dev);
	/* needs no more cleanup */
	BUG_ON (!list_empty (&data->epfiles));
	BUG_ON (रुकोqueue_active (&data->रुको));
	kमुक्त (data);
पूर्ण

/*----------------------------------------------------------------------*/

/* most "how to use the hardware" policy choices are in userspace:
 * mapping endpoपूर्णांक roles (which the driver needs) to the capabilities
 * which the usb controller has.  most of those capabilities are exposed
 * implicitly, starting with the driver name and then endpoपूर्णांक names.
 */

अटल स्थिर अक्षर *CHIP;

/*----------------------------------------------------------------------*/

/* NOTE:  करोn't use dev_prपूर्णांकk calls beक्रमe binding to the gadget
 * at the end of ep0 configuration, or after unbind.
 */

/* too wordy: dev_prपूर्णांकk(level , &(d)->gadget->dev , fmt , ## args) */
#घोषणा xprपूर्णांकk(d,level,fmt,args...) \
	prपूर्णांकk(level "%s: " fmt , लघुname , ## args)

#अगर_घोषित DEBUG
#घोषणा DBG(dev,fmt,args...) \
	xprपूर्णांकk(dev , KERN_DEBUG , fmt , ## args)
#अन्यथा
#घोषणा DBG(dev,fmt,args...) \
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */

#अगर_घोषित VERBOSE_DEBUG
#घोषणा VDEBUG	DBG
#अन्यथा
#घोषणा VDEBUG(dev,fmt,args...) \
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */

#घोषणा ERROR(dev,fmt,args...) \
	xprपूर्णांकk(dev , KERN_ERR , fmt , ## args)
#घोषणा INFO(dev,fmt,args...) \
	xprपूर्णांकk(dev , KERN_INFO , fmt , ## args)


/*----------------------------------------------------------------------*/

/* SYNCHRONOUS ENDPOINT OPERATIONS (bulk/पूर्णांकr/iso)
 *
 * After खोलोing, configure non-control endpoपूर्णांकs.  Then use normal
 * stream पढ़ो() and ग_लिखो() requests; and maybe ioctl() to get more
 * precise FIFO status when recovering from cancellation.
 */

अटल व्योम epio_complete (काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा ep_data	*epdata = ep->driver_data;

	अगर (!req->context)
		वापस;
	अगर (req->status)
		epdata->status = req->status;
	अन्यथा
		epdata->status = req->actual;
	complete ((काष्ठा completion *)req->context);
पूर्ण

/* tasklock endpoपूर्णांक, वापसing when it's connected.
 * still need dev->lock to use epdata->ep.
 */
अटल पूर्णांक
get_पढ़ोy_ep (अचिन्हित f_flags, काष्ठा ep_data *epdata, bool is_ग_लिखो)
अणु
	पूर्णांक	val;

	अगर (f_flags & O_NONBLOCK) अणु
		अगर (!mutex_trylock(&epdata->lock))
			जाओ nonblock;
		अगर (epdata->state != STATE_EP_ENABLED &&
		    (!is_ग_लिखो || epdata->state != STATE_EP_READY)) अणु
			mutex_unlock(&epdata->lock);
nonblock:
			val = -EAGAIN;
		पूर्ण अन्यथा
			val = 0;
		वापस val;
	पूर्ण

	val = mutex_lock_पूर्णांकerruptible(&epdata->lock);
	अगर (val < 0)
		वापस val;

	चयन (epdata->state) अणु
	हाल STATE_EP_ENABLED:
		वापस 0;
	हाल STATE_EP_READY:			/* not configured yet */
		अगर (is_ग_लिखो)
			वापस 0;
		fallthrough;
	हाल STATE_EP_UNBOUND:			/* clean disconnect */
		अवरोध;
	// हाल STATE_EP_DISABLED:		/* "can't happen" */
	शेष:				/* error! */
		pr_debug ("%s: ep %p not available, state %d\n",
				लघुname, epdata, epdata->state);
	पूर्ण
	mutex_unlock(&epdata->lock);
	वापस -ENODEV;
पूर्ण

अटल sमाप_प्रकार
ep_io (काष्ठा ep_data *epdata, व्योम *buf, अचिन्हित len)
अणु
	DECLARE_COMPLETION_ONSTACK (करोne);
	पूर्णांक value;

	spin_lock_irq (&epdata->dev->lock);
	अगर (likely (epdata->ep != शून्य)) अणु
		काष्ठा usb_request	*req = epdata->req;

		req->context = &करोne;
		req->complete = epio_complete;
		req->buf = buf;
		req->length = len;
		value = usb_ep_queue (epdata->ep, req, GFP_ATOMIC);
	पूर्ण अन्यथा
		value = -ENODEV;
	spin_unlock_irq (&epdata->dev->lock);

	अगर (likely (value == 0)) अणु
		value = रुको_क्रम_completion_पूर्णांकerruptible(&करोne);
		अगर (value != 0) अणु
			spin_lock_irq (&epdata->dev->lock);
			अगर (likely (epdata->ep != शून्य)) अणु
				DBG (epdata->dev, "%s i/o interrupted\n",
						epdata->name);
				usb_ep_dequeue (epdata->ep, epdata->req);
				spin_unlock_irq (&epdata->dev->lock);

				रुको_क्रम_completion(&करोne);
				अगर (epdata->status == -ECONNRESET)
					epdata->status = -EINTR;
			पूर्ण अन्यथा अणु
				spin_unlock_irq (&epdata->dev->lock);

				DBG (epdata->dev, "endpoint gone\n");
				epdata->status = -ENODEV;
			पूर्ण
		पूर्ण
		वापस epdata->status;
	पूर्ण
	वापस value;
पूर्ण

अटल पूर्णांक
ep_release (काष्ठा inode *inode, काष्ठा file *fd)
अणु
	काष्ठा ep_data		*data = fd->निजी_data;
	पूर्णांक value;

	value = mutex_lock_पूर्णांकerruptible(&data->lock);
	अगर (value < 0)
		वापस value;

	/* clean up अगर this can be reखोलोed */
	अगर (data->state != STATE_EP_UNBOUND) अणु
		data->state = STATE_EP_DISABLED;
		data->desc.bDescriptorType = 0;
		data->hs_desc.bDescriptorType = 0;
		usb_ep_disable(data->ep);
	पूर्ण
	mutex_unlock(&data->lock);
	put_ep (data);
	वापस 0;
पूर्ण

अटल दीर्घ ep_ioctl(काष्ठा file *fd, अचिन्हित code, अचिन्हित दीर्घ value)
अणु
	काष्ठा ep_data		*data = fd->निजी_data;
	पूर्णांक			status;

	अगर ((status = get_पढ़ोy_ep (fd->f_flags, data, false)) < 0)
		वापस status;

	spin_lock_irq (&data->dev->lock);
	अगर (likely (data->ep != शून्य)) अणु
		चयन (code) अणु
		हाल GADGETFS_FIFO_STATUS:
			status = usb_ep_fअगरo_status (data->ep);
			अवरोध;
		हाल GADGETFS_FIFO_FLUSH:
			usb_ep_fअगरo_flush (data->ep);
			अवरोध;
		हाल GADGETFS_CLEAR_HALT:
			status = usb_ep_clear_halt (data->ep);
			अवरोध;
		शेष:
			status = -ENOTTY;
		पूर्ण
	पूर्ण अन्यथा
		status = -ENODEV;
	spin_unlock_irq (&data->dev->lock);
	mutex_unlock(&data->lock);
	वापस status;
पूर्ण

/*----------------------------------------------------------------------*/

/* ASYNCHRONOUS ENDPOINT I/O OPERATIONS (bulk/पूर्णांकr/iso) */

काष्ठा kiocb_priv अणु
	काष्ठा usb_request	*req;
	काष्ठा ep_data		*epdata;
	काष्ठा kiocb		*iocb;
	काष्ठा mm_काष्ठा	*mm;
	काष्ठा work_काष्ठा	work;
	व्योम			*buf;
	काष्ठा iov_iter		to;
	स्थिर व्योम		*to_मुक्त;
	अचिन्हित		actual;
पूर्ण;

अटल पूर्णांक ep_aio_cancel(काष्ठा kiocb *iocb)
अणु
	काष्ठा kiocb_priv	*priv = iocb->निजी;
	काष्ठा ep_data		*epdata;
	पूर्णांक			value;

	local_irq_disable();
	epdata = priv->epdata;
	// spin_lock(&epdata->dev->lock);
	अगर (likely(epdata && epdata->ep && priv->req))
		value = usb_ep_dequeue (epdata->ep, priv->req);
	अन्यथा
		value = -EINVAL;
	// spin_unlock(&epdata->dev->lock);
	local_irq_enable();

	वापस value;
पूर्ण

अटल व्योम ep_user_copy_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kiocb_priv *priv = container_of(work, काष्ठा kiocb_priv, work);
	काष्ठा mm_काष्ठा *mm = priv->mm;
	काष्ठा kiocb *iocb = priv->iocb;
	माप_प्रकार ret;

	kthपढ़ो_use_mm(mm);
	ret = copy_to_iter(priv->buf, priv->actual, &priv->to);
	kthपढ़ो_unuse_mm(mm);
	अगर (!ret)
		ret = -EFAULT;

	/* completing the iocb can drop the ctx and mm, करोn't touch mm after */
	iocb->ki_complete(iocb, ret, ret);

	kमुक्त(priv->buf);
	kमुक्त(priv->to_मुक्त);
	kमुक्त(priv);
पूर्ण

अटल व्योम ep_aio_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा kiocb		*iocb = req->context;
	काष्ठा kiocb_priv	*priv = iocb->निजी;
	काष्ठा ep_data		*epdata = priv->epdata;

	/* lock against disconnect (and ideally, cancel) */
	spin_lock(&epdata->dev->lock);
	priv->req = शून्य;
	priv->epdata = शून्य;

	/* अगर this was a ग_लिखो or a पढ़ो वापसing no data then we
	 * करोn't need to copy anything to userspace, so we can
	 * complete the aio request immediately.
	 */
	अगर (priv->to_मुक्त == शून्य || unlikely(req->actual == 0)) अणु
		kमुक्त(req->buf);
		kमुक्त(priv->to_मुक्त);
		kमुक्त(priv);
		iocb->निजी = शून्य;
		/* aio_complete() reports bytes-transferred _and_ faults */

		iocb->ki_complete(iocb,
				req->actual ? req->actual : (दीर्घ)req->status,
				req->status);
	पूर्ण अन्यथा अणु
		/* ep_copy_to_user() won't report both; we hide some faults */
		अगर (unlikely(0 != req->status))
			DBG(epdata->dev, "%s fault %d len %d\n",
				ep->name, req->status, req->actual);

		priv->buf = req->buf;
		priv->actual = req->actual;
		INIT_WORK(&priv->work, ep_user_copy_worker);
		schedule_work(&priv->work);
	पूर्ण

	usb_ep_मुक्त_request(ep, req);
	spin_unlock(&epdata->dev->lock);
	put_ep(epdata);
पूर्ण

अटल sमाप_प्रकार ep_aio(काष्ठा kiocb *iocb,
		      काष्ठा kiocb_priv *priv,
		      काष्ठा ep_data *epdata,
		      अक्षर *buf,
		      माप_प्रकार len)
अणु
	काष्ठा usb_request *req;
	sमाप_प्रकार value;

	iocb->निजी = priv;
	priv->iocb = iocb;

	kiocb_set_cancel_fn(iocb, ep_aio_cancel);
	get_ep(epdata);
	priv->epdata = epdata;
	priv->actual = 0;
	priv->mm = current->mm; /* mm tearकरोwn रुकोs क्रम iocbs in निकास_aio() */

	/* each kiocb is coupled to one usb_request, but we can't
	 * allocate or submit those अगर the host disconnected.
	 */
	spin_lock_irq(&epdata->dev->lock);
	value = -ENODEV;
	अगर (unlikely(epdata->ep == शून्य))
		जाओ fail;

	req = usb_ep_alloc_request(epdata->ep, GFP_ATOMIC);
	value = -ENOMEM;
	अगर (unlikely(!req))
		जाओ fail;

	priv->req = req;
	req->buf = buf;
	req->length = len;
	req->complete = ep_aio_complete;
	req->context = iocb;
	value = usb_ep_queue(epdata->ep, req, GFP_ATOMIC);
	अगर (unlikely(0 != value)) अणु
		usb_ep_मुक्त_request(epdata->ep, req);
		जाओ fail;
	पूर्ण
	spin_unlock_irq(&epdata->dev->lock);
	वापस -EIOCBQUEUED;

fail:
	spin_unlock_irq(&epdata->dev->lock);
	kमुक्त(priv->to_मुक्त);
	kमुक्त(priv);
	put_ep(epdata);
	वापस value;
पूर्ण

अटल sमाप_प्रकार
ep_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा ep_data *epdata = file->निजी_data;
	माप_प्रकार len = iov_iter_count(to);
	sमाप_प्रकार value;
	अक्षर *buf;

	अगर ((value = get_पढ़ोy_ep(file->f_flags, epdata, false)) < 0)
		वापस value;

	/* halt any endpoपूर्णांक by करोing a "wrong direction" i/o call */
	अगर (usb_endpoपूर्णांक_dir_in(&epdata->desc)) अणु
		अगर (usb_endpoपूर्णांक_xfer_isoc(&epdata->desc) ||
		    !is_sync_kiocb(iocb)) अणु
			mutex_unlock(&epdata->lock);
			वापस -EINVAL;
		पूर्ण
		DBG (epdata->dev, "%s halt\n", epdata->name);
		spin_lock_irq(&epdata->dev->lock);
		अगर (likely(epdata->ep != शून्य))
			usb_ep_set_halt(epdata->ep);
		spin_unlock_irq(&epdata->dev->lock);
		mutex_unlock(&epdata->lock);
		वापस -EBADMSG;
	पूर्ण

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (unlikely(!buf)) अणु
		mutex_unlock(&epdata->lock);
		वापस -ENOMEM;
	पूर्ण
	अगर (is_sync_kiocb(iocb)) अणु
		value = ep_io(epdata, buf, len);
		अगर (value >= 0 && (copy_to_iter(buf, value, to) != value))
			value = -EFAULT;
	पूर्ण अन्यथा अणु
		काष्ठा kiocb_priv *priv = kzalloc(माप *priv, GFP_KERNEL);
		value = -ENOMEM;
		अगर (!priv)
			जाओ fail;
		priv->to_मुक्त = dup_iter(&priv->to, to, GFP_KERNEL);
		अगर (!priv->to_मुक्त) अणु
			kमुक्त(priv);
			जाओ fail;
		पूर्ण
		value = ep_aio(iocb, priv, epdata, buf, len);
		अगर (value == -EIOCBQUEUED)
			buf = शून्य;
	पूर्ण
fail:
	kमुक्त(buf);
	mutex_unlock(&epdata->lock);
	वापस value;
पूर्ण

अटल sमाप_प्रकार ep_config(काष्ठा ep_data *, स्थिर अक्षर *, माप_प्रकार);

अटल sमाप_प्रकार
ep_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा ep_data *epdata = file->निजी_data;
	माप_प्रकार len = iov_iter_count(from);
	bool configured;
	sमाप_प्रकार value;
	अक्षर *buf;

	अगर ((value = get_पढ़ोy_ep(file->f_flags, epdata, true)) < 0)
		वापस value;

	configured = epdata->state == STATE_EP_ENABLED;

	/* halt any endpoपूर्णांक by करोing a "wrong direction" i/o call */
	अगर (configured && !usb_endpoपूर्णांक_dir_in(&epdata->desc)) अणु
		अगर (usb_endpoपूर्णांक_xfer_isoc(&epdata->desc) ||
		    !is_sync_kiocb(iocb)) अणु
			mutex_unlock(&epdata->lock);
			वापस -EINVAL;
		पूर्ण
		DBG (epdata->dev, "%s halt\n", epdata->name);
		spin_lock_irq(&epdata->dev->lock);
		अगर (likely(epdata->ep != शून्य))
			usb_ep_set_halt(epdata->ep);
		spin_unlock_irq(&epdata->dev->lock);
		mutex_unlock(&epdata->lock);
		वापस -EBADMSG;
	पूर्ण

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (unlikely(!buf)) अणु
		mutex_unlock(&epdata->lock);
		वापस -ENOMEM;
	पूर्ण

	अगर (unlikely(!copy_from_iter_full(buf, len, from))) अणु
		value = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (unlikely(!configured)) अणु
		value = ep_config(epdata, buf, len);
	पूर्ण अन्यथा अगर (is_sync_kiocb(iocb)) अणु
		value = ep_io(epdata, buf, len);
	पूर्ण अन्यथा अणु
		काष्ठा kiocb_priv *priv = kzalloc(माप *priv, GFP_KERNEL);
		value = -ENOMEM;
		अगर (priv) अणु
			value = ep_aio(iocb, priv, epdata, buf, len);
			अगर (value == -EIOCBQUEUED)
				buf = शून्य;
		पूर्ण
	पूर्ण
out:
	kमुक्त(buf);
	mutex_unlock(&epdata->lock);
	वापस value;
पूर्ण

/*----------------------------------------------------------------------*/

/* used after endpoपूर्णांक configuration */
अटल स्थिर काष्ठा file_operations ep_io_operations = अणु
	.owner =	THIS_MODULE,

	.खोलो =		ep_खोलो,
	.release =	ep_release,
	.llseek =	no_llseek,
	.unlocked_ioctl = ep_ioctl,
	.पढ़ो_iter =	ep_पढ़ो_iter,
	.ग_लिखो_iter =	ep_ग_लिखो_iter,
पूर्ण;

/* ENDPOINT INITIALIZATION
 *
 *     fd = खोलो ("/dev/gadget/$ENDPOINT", O_RDWR)
 *     status = ग_लिखो (fd, descriptors, माप descriptors)
 *
 * That ग_लिखो establishes the endpoपूर्णांक configuration, configuring
 * the controller to process bulk, पूर्णांकerrupt, or isochronous transfers
 * at the right maxpacket size, and so on.
 *
 * The descriptors are message type 1, identअगरied by a host order u32
 * at the beginning of what's written.  Descriptor order is: full/low
 * speed descriptor, then optional high speed descriptor.
 */
अटल sमाप_प्रकार
ep_config (काष्ठा ep_data *data, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usb_ep		*ep;
	u32			tag;
	पूर्णांक			value, length = len;

	अगर (data->state != STATE_EP_READY) अणु
		value = -EL2HLT;
		जाओ fail;
	पूर्ण

	value = len;
	अगर (len < USB_DT_ENDPOINT_SIZE + 4)
		जाओ fail0;

	/* we might need to change message क्रमmat someday */
	स_नकल(&tag, buf, 4);
	अगर (tag != 1) अणु
		DBG(data->dev, "config %s, bad tag %d\n", data->name, tag);
		जाओ fail0;
	पूर्ण
	buf += 4;
	len -= 4;

	/* NOTE:  audio endpoपूर्णांक extensions not accepted here;
	 * just करोn't include the extra bytes.
	 */

	/* full/low speed descriptor, then high speed */
	स_नकल(&data->desc, buf, USB_DT_ENDPOINT_SIZE);
	अगर (data->desc.bLength != USB_DT_ENDPOINT_SIZE
			|| data->desc.bDescriptorType != USB_DT_ENDPOINT)
		जाओ fail0;
	अगर (len != USB_DT_ENDPOINT_SIZE) अणु
		अगर (len != 2 * USB_DT_ENDPOINT_SIZE)
			जाओ fail0;
		स_नकल(&data->hs_desc, buf + USB_DT_ENDPOINT_SIZE,
			USB_DT_ENDPOINT_SIZE);
		अगर (data->hs_desc.bLength != USB_DT_ENDPOINT_SIZE
				|| data->hs_desc.bDescriptorType
					!= USB_DT_ENDPOINT) अणु
			DBG(data->dev, "config %s, bad hs length or type\n",
					data->name);
			जाओ fail0;
		पूर्ण
	पूर्ण

	spin_lock_irq (&data->dev->lock);
	अगर (data->dev->state == STATE_DEV_UNBOUND) अणु
		value = -ENOENT;
		जाओ gone;
	पूर्ण अन्यथा अणु
		ep = data->ep;
		अगर (ep == शून्य) अणु
			value = -ENODEV;
			जाओ gone;
		पूर्ण
	पूर्ण
	चयन (data->dev->gadget->speed) अणु
	हाल USB_SPEED_LOW:
	हाल USB_SPEED_FULL:
		ep->desc = &data->desc;
		अवरोध;
	हाल USB_SPEED_HIGH:
		/* fails अगर caller didn't provide that descriptor... */
		ep->desc = &data->hs_desc;
		अवरोध;
	शेष:
		DBG(data->dev, "unconnected, %s init abandoned\n",
				data->name);
		value = -EINVAL;
		जाओ gone;
	पूर्ण
	value = usb_ep_enable(ep);
	अगर (value == 0) अणु
		data->state = STATE_EP_ENABLED;
		value = length;
	पूर्ण
gone:
	spin_unlock_irq (&data->dev->lock);
	अगर (value < 0) अणु
fail:
		data->desc.bDescriptorType = 0;
		data->hs_desc.bDescriptorType = 0;
	पूर्ण
	वापस value;
fail0:
	value = -EINVAL;
	जाओ fail;
पूर्ण

अटल पूर्णांक
ep_खोलो (काष्ठा inode *inode, काष्ठा file *fd)
अणु
	काष्ठा ep_data		*data = inode->i_निजी;
	पूर्णांक			value = -EBUSY;

	अगर (mutex_lock_पूर्णांकerruptible(&data->lock) != 0)
		वापस -EINTR;
	spin_lock_irq (&data->dev->lock);
	अगर (data->dev->state == STATE_DEV_UNBOUND)
		value = -ENOENT;
	अन्यथा अगर (data->state == STATE_EP_DISABLED) अणु
		value = 0;
		data->state = STATE_EP_READY;
		get_ep (data);
		fd->निजी_data = data;
		VDEBUG (data->dev, "%s ready\n", data->name);
	पूर्ण अन्यथा
		DBG (data->dev, "%s state %d\n",
			data->name, data->state);
	spin_unlock_irq (&data->dev->lock);
	mutex_unlock(&data->lock);
	वापस value;
पूर्ण

/*----------------------------------------------------------------------*/

/* EP0 IMPLEMENTATION can be partly in userspace.
 *
 * Drivers that use this facility receive various events, including
 * control requests the kernel करोesn't handle.  Drivers that don't
 * use this facility may be too simple-minded क्रम real applications.
 */

अटल अंतरभूत व्योम ep0_पढ़ोable (काष्ठा dev_data *dev)
अणु
	wake_up (&dev->रुको);
	समाप्त_fasync (&dev->fasync, SIGIO, POLL_IN);
पूर्ण

अटल व्योम clean_req (काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा dev_data		*dev = ep->driver_data;

	अगर (req->buf != dev->rbuf) अणु
		kमुक्त(req->buf);
		req->buf = dev->rbuf;
	पूर्ण
	req->complete = epio_complete;
	dev->setup_out_पढ़ोy = 0;
पूर्ण

अटल व्योम ep0_complete (काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा dev_data		*dev = ep->driver_data;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			मुक्त = 1;

	/* क्रम control OUT, data must still get to userspace */
	spin_lock_irqsave(&dev->lock, flags);
	अगर (!dev->setup_in) अणु
		dev->setup_out_error = (req->status != 0);
		अगर (!dev->setup_out_error)
			मुक्त = 0;
		dev->setup_out_पढ़ोy = 1;
		ep0_पढ़ोable (dev);
	पूर्ण

	/* clean up as appropriate */
	अगर (मुक्त && req->buf != &dev->rbuf)
		clean_req (ep, req);
	req->complete = epio_complete;
	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

अटल पूर्णांक setup_req (काष्ठा usb_ep *ep, काष्ठा usb_request *req, u16 len)
अणु
	काष्ठा dev_data	*dev = ep->driver_data;

	अगर (dev->setup_out_पढ़ोy) अणु
		DBG (dev, "ep0 request busy!\n");
		वापस -EBUSY;
	पूर्ण
	अगर (len > माप (dev->rbuf))
		req->buf = kदो_स्मृति(len, GFP_ATOMIC);
	अगर (req->buf == शून्य) अणु
		req->buf = dev->rbuf;
		वापस -ENOMEM;
	पूर्ण
	req->complete = ep0_complete;
	req->length = len;
	req->zero = 0;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
ep0_पढ़ो (काष्ठा file *fd, अक्षर __user *buf, माप_प्रकार len, loff_t *ptr)
अणु
	काष्ठा dev_data			*dev = fd->निजी_data;
	sमाप_प्रकार				retval;
	क्रमागत ep0_state			state;

	spin_lock_irq (&dev->lock);
	अगर (dev->state <= STATE_DEV_OPENED) अणु
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* report fd mode change beक्रमe acting on it */
	अगर (dev->setup_पात) अणु
		dev->setup_पात = 0;
		retval = -EIDRM;
		जाओ करोne;
	पूर्ण

	/* control DATA stage */
	अगर ((state = dev->state) == STATE_DEV_SETUP) अणु

		अगर (dev->setup_in) अणु		/* stall IN */
			VDEBUG(dev, "ep0in stall\n");
			(व्योम) usb_ep_set_halt (dev->gadget->ep0);
			retval = -EL2HLT;
			dev->state = STATE_DEV_CONNECTED;

		पूर्ण अन्यथा अगर (len == 0) अणु		/* ack SET_CONFIGURATION etc */
			काष्ठा usb_ep		*ep = dev->gadget->ep0;
			काष्ठा usb_request	*req = dev->req;

			अगर ((retval = setup_req (ep, req, 0)) == 0) अणु
				++dev->udc_usage;
				spin_unlock_irq (&dev->lock);
				retval = usb_ep_queue (ep, req, GFP_KERNEL);
				spin_lock_irq (&dev->lock);
				--dev->udc_usage;
			पूर्ण
			dev->state = STATE_DEV_CONNECTED;

			/* assume that was SET_CONFIGURATION */
			अगर (dev->current_config) अणु
				अचिन्हित घातer;

				अगर (gadget_is_dualspeed(dev->gadget)
						&& (dev->gadget->speed
							== USB_SPEED_HIGH))
					घातer = dev->hs_config->bMaxPower;
				अन्यथा
					घातer = dev->config->bMaxPower;
				usb_gadget_vbus_draw(dev->gadget, 2 * घातer);
			पूर्ण

		पूर्ण अन्यथा अणु			/* collect OUT data */
			अगर ((fd->f_flags & O_NONBLOCK) != 0
					&& !dev->setup_out_पढ़ोy) अणु
				retval = -EAGAIN;
				जाओ करोne;
			पूर्ण
			spin_unlock_irq (&dev->lock);
			retval = रुको_event_पूर्णांकerruptible (dev->रुको,
					dev->setup_out_पढ़ोy != 0);

			/* FIXME state could change from under us */
			spin_lock_irq (&dev->lock);
			अगर (retval)
				जाओ करोne;

			अगर (dev->state != STATE_DEV_SETUP) अणु
				retval = -ECANCELED;
				जाओ करोne;
			पूर्ण
			dev->state = STATE_DEV_CONNECTED;

			अगर (dev->setup_out_error)
				retval = -EIO;
			अन्यथा अणु
				len = min (len, (माप_प्रकार)dev->req->actual);
				++dev->udc_usage;
				spin_unlock_irq(&dev->lock);
				अगर (copy_to_user (buf, dev->req->buf, len))
					retval = -EFAULT;
				अन्यथा
					retval = len;
				spin_lock_irq(&dev->lock);
				--dev->udc_usage;
				clean_req (dev->gadget->ep0, dev->req);
				/* NOTE userspace can't yet choose to stall */
			पूर्ण
		पूर्ण
		जाओ करोne;
	पूर्ण

	/* अन्यथा normal: वापस event data */
	अगर (len < माप dev->event [0]) अणु
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण
	len -= len % माप (काष्ठा usb_gadgetfs_event);
	dev->usermode_setup = 1;

scan:
	/* वापस queued events right away */
	अगर (dev->ev_next != 0) अणु
		अचिन्हित		i, n;

		n = len / माप (काष्ठा usb_gadgetfs_event);
		अगर (dev->ev_next < n)
			n = dev->ev_next;

		/* ep0 i/o has special semantics during STATE_DEV_SETUP */
		क्रम (i = 0; i < n; i++) अणु
			अगर (dev->event [i].type == GADGETFS_SETUP) अणु
				dev->state = STATE_DEV_SETUP;
				n = i + 1;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irq (&dev->lock);
		len = n * माप (काष्ठा usb_gadgetfs_event);
		अगर (copy_to_user (buf, &dev->event, len))
			retval = -EFAULT;
		अन्यथा
			retval = len;
		अगर (len > 0) अणु
			/* NOTE this करोesn't guard against broken drivers;
			 * concurrent ep0 पढ़ोers may lose events.
			 */
			spin_lock_irq (&dev->lock);
			अगर (dev->ev_next > n) अणु
				स_हटाओ(&dev->event[0], &dev->event[n],
					माप (काष्ठा usb_gadgetfs_event)
						* (dev->ev_next - n));
			पूर्ण
			dev->ev_next -= n;
			spin_unlock_irq (&dev->lock);
		पूर्ण
		वापस retval;
	पूर्ण
	अगर (fd->f_flags & O_NONBLOCK) अणु
		retval = -EAGAIN;
		जाओ करोne;
	पूर्ण

	चयन (state) अणु
	शेष:
		DBG (dev, "fail %s, state %d\n", __func__, state);
		retval = -ESRCH;
		अवरोध;
	हाल STATE_DEV_UNCONNECTED:
	हाल STATE_DEV_CONNECTED:
		spin_unlock_irq (&dev->lock);
		DBG (dev, "%s wait\n", __func__);

		/* रुको क्रम events */
		retval = रुको_event_पूर्णांकerruptible (dev->रुको,
				dev->ev_next != 0);
		अगर (retval < 0)
			वापस retval;
		spin_lock_irq (&dev->lock);
		जाओ scan;
	पूर्ण

करोne:
	spin_unlock_irq (&dev->lock);
	वापस retval;
पूर्ण

अटल काष्ठा usb_gadgetfs_event *
next_event (काष्ठा dev_data *dev, क्रमागत usb_gadgetfs_event_type type)
अणु
	काष्ठा usb_gadgetfs_event	*event;
	अचिन्हित			i;

	चयन (type) अणु
	/* these events purge the queue */
	हाल GADGETFS_DISCONNECT:
		अगर (dev->state == STATE_DEV_SETUP)
			dev->setup_पात = 1;
		fallthrough;
	हाल GADGETFS_CONNECT:
		dev->ev_next = 0;
		अवरोध;
	हाल GADGETFS_SETUP:		/* previous request समयd out */
	हाल GADGETFS_SUSPEND:		/* same effect */
		/* these events can't be repeated */
		क्रम (i = 0; i != dev->ev_next; i++) अणु
			अगर (dev->event [i].type != type)
				जारी;
			DBG(dev, "discard old event[%d] %d\n", i, type);
			dev->ev_next--;
			अगर (i == dev->ev_next)
				अवरोध;
			/* indices start at zero, क्रम simplicity */
			स_हटाओ (&dev->event [i], &dev->event [i + 1],
				माप (काष्ठा usb_gadgetfs_event)
					* (dev->ev_next - i));
		पूर्ण
		अवरोध;
	शेष:
		BUG ();
	पूर्ण
	VDEBUG(dev, "event[%d] = %d\n", dev->ev_next, type);
	event = &dev->event [dev->ev_next++];
	BUG_ON (dev->ev_next > N_EVENT);
	स_रखो (event, 0, माप *event);
	event->type = type;
	वापस event;
पूर्ण

अटल sमाप_प्रकार
ep0_ग_लिखो (काष्ठा file *fd, स्थिर अक्षर __user *buf, माप_प्रकार len, loff_t *ptr)
अणु
	काष्ठा dev_data		*dev = fd->निजी_data;
	sमाप_प्रकार			retval = -ESRCH;

	/* report fd mode change beक्रमe acting on it */
	अगर (dev->setup_पात) अणु
		dev->setup_पात = 0;
		retval = -EIDRM;

	/* data and/or status stage क्रम control request */
	पूर्ण अन्यथा अगर (dev->state == STATE_DEV_SETUP) अणु

		len = min_t(माप_प्रकार, len, dev->setup_wLength);
		अगर (dev->setup_in) अणु
			retval = setup_req (dev->gadget->ep0, dev->req, len);
			अगर (retval == 0) अणु
				dev->state = STATE_DEV_CONNECTED;
				++dev->udc_usage;
				spin_unlock_irq (&dev->lock);
				अगर (copy_from_user (dev->req->buf, buf, len))
					retval = -EFAULT;
				अन्यथा अणु
					अगर (len < dev->setup_wLength)
						dev->req->zero = 1;
					retval = usb_ep_queue (
						dev->gadget->ep0, dev->req,
						GFP_KERNEL);
				पूर्ण
				spin_lock_irq(&dev->lock);
				--dev->udc_usage;
				अगर (retval < 0) अणु
					clean_req (dev->gadget->ep0, dev->req);
				पूर्ण अन्यथा
					retval = len;

				वापस retval;
			पूर्ण

		/* can stall some OUT transfers */
		पूर्ण अन्यथा अगर (dev->setup_can_stall) अणु
			VDEBUG(dev, "ep0out stall\n");
			(व्योम) usb_ep_set_halt (dev->gadget->ep0);
			retval = -EL2HLT;
			dev->state = STATE_DEV_CONNECTED;
		पूर्ण अन्यथा अणु
			DBG(dev, "bogus ep0out stall!\n");
		पूर्ण
	पूर्ण अन्यथा
		DBG (dev, "fail %s, state %d\n", __func__, dev->state);

	वापस retval;
पूर्ण

अटल पूर्णांक
ep0_fasync (पूर्णांक f, काष्ठा file *fd, पूर्णांक on)
अणु
	काष्ठा dev_data		*dev = fd->निजी_data;
	// caller must F_SETOWN beक्रमe संकेत delivery happens
	VDEBUG (dev, "%s %s\n", __func__, on ? "on" : "off");
	वापस fasync_helper (f, fd, on, &dev->fasync);
पूर्ण

अटल काष्ठा usb_gadget_driver gadgetfs_driver;

अटल पूर्णांक
dev_release (काष्ठा inode *inode, काष्ठा file *fd)
अणु
	काष्ठा dev_data		*dev = fd->निजी_data;

	/* closing ep0 === shutकरोwn all */

	अगर (dev->gadget_रेजिस्टरed) अणु
		usb_gadget_unरेजिस्टर_driver (&gadgetfs_driver);
		dev->gadget_रेजिस्टरed = false;
	पूर्ण

	/* at this poपूर्णांक "good" hardware has disconnected the
	 * device from USB; the host won't see it any more.
	 * alternatively, all host requests will समय out.
	 */

	kमुक्त (dev->buf);
	dev->buf = शून्य;

	/* other endpoपूर्णांकs were all decoupled from this device */
	spin_lock_irq(&dev->lock);
	dev->state = STATE_DEV_DISABLED;
	spin_unlock_irq(&dev->lock);

	put_dev (dev);
	वापस 0;
पूर्ण

अटल __poll_t
ep0_poll (काष्ठा file *fd, poll_table *रुको)
अणु
       काष्ठा dev_data         *dev = fd->निजी_data;
       __poll_t                mask = 0;

	अगर (dev->state <= STATE_DEV_OPENED)
		वापस DEFAULT_POLLMASK;

	poll_रुको(fd, &dev->रुको, रुको);

	spin_lock_irq(&dev->lock);

	/* report fd mode change beक्रमe acting on it */
	अगर (dev->setup_पात) अणु
		dev->setup_पात = 0;
		mask = EPOLLHUP;
		जाओ out;
	पूर्ण

	अगर (dev->state == STATE_DEV_SETUP) अणु
		अगर (dev->setup_in || dev->setup_can_stall)
			mask = EPOLLOUT;
	पूर्ण अन्यथा अणु
		अगर (dev->ev_next != 0)
			mask = EPOLLIN;
	पूर्ण
out:
	spin_unlock_irq(&dev->lock);
	वापस mask;
पूर्ण

अटल दीर्घ dev_ioctl (काष्ठा file *fd, अचिन्हित code, अचिन्हित दीर्घ value)
अणु
	काष्ठा dev_data		*dev = fd->निजी_data;
	काष्ठा usb_gadget	*gadget = dev->gadget;
	दीर्घ ret = -ENOTTY;

	spin_lock_irq(&dev->lock);
	अगर (dev->state == STATE_DEV_OPENED ||
			dev->state == STATE_DEV_UNBOUND) अणु
		/* Not bound to a UDC */
	पूर्ण अन्यथा अगर (gadget->ops->ioctl) अणु
		++dev->udc_usage;
		spin_unlock_irq(&dev->lock);

		ret = gadget->ops->ioctl (gadget, code, value);

		spin_lock_irq(&dev->lock);
		--dev->udc_usage;
	पूर्ण
	spin_unlock_irq(&dev->lock);

	वापस ret;
पूर्ण

/*----------------------------------------------------------------------*/

/* The in-kernel gadget driver handles most ep0 issues, in particular
 * क्रमागतerating the single configuration (as provided from user space).
 *
 * Unrecognized ep0 requests may be handled in user space.
 */

अटल व्योम make_qualअगरier (काष्ठा dev_data *dev)
अणु
	काष्ठा usb_qualअगरier_descriptor		qual;
	काष्ठा usb_device_descriptor		*desc;

	qual.bLength = माप qual;
	qual.bDescriptorType = USB_DT_DEVICE_QUALIFIER;
	qual.bcdUSB = cpu_to_le16 (0x0200);

	desc = dev->dev;
	qual.bDeviceClass = desc->bDeviceClass;
	qual.bDeviceSubClass = desc->bDeviceSubClass;
	qual.bDeviceProtocol = desc->bDeviceProtocol;

	/* assumes ep0 uses the same value क्रम both speeds ... */
	qual.bMaxPacketSize0 = dev->gadget->ep0->maxpacket;

	qual.bNumConfigurations = 1;
	qual.bRESERVED = 0;

	स_नकल (dev->rbuf, &qual, माप qual);
पूर्ण

अटल पूर्णांक
config_buf (काष्ठा dev_data *dev, u8 type, अचिन्हित index)
अणु
	पूर्णांक		len;
	पूर्णांक		hs = 0;

	/* only one configuration */
	अगर (index > 0)
		वापस -EINVAL;

	अगर (gadget_is_dualspeed(dev->gadget)) अणु
		hs = (dev->gadget->speed == USB_SPEED_HIGH);
		अगर (type == USB_DT_OTHER_SPEED_CONFIG)
			hs = !hs;
	पूर्ण
	अगर (hs) अणु
		dev->req->buf = dev->hs_config;
		len = le16_to_cpu(dev->hs_config->wTotalLength);
	पूर्ण अन्यथा अणु
		dev->req->buf = dev->config;
		len = le16_to_cpu(dev->config->wTotalLength);
	पूर्ण
	((u8 *)dev->req->buf) [1] = type;
	वापस len;
पूर्ण

अटल पूर्णांक
gadgetfs_setup (काष्ठा usb_gadget *gadget, स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा dev_data			*dev = get_gadget_data (gadget);
	काष्ठा usb_request		*req = dev->req;
	पूर्णांक				value = -EOPNOTSUPP;
	काष्ठा usb_gadgetfs_event	*event;
	u16				w_value = le16_to_cpu(ctrl->wValue);
	u16				w_length = le16_to_cpu(ctrl->wLength);

	spin_lock (&dev->lock);
	dev->setup_पात = 0;
	अगर (dev->state == STATE_DEV_UNCONNECTED) अणु
		अगर (gadget_is_dualspeed(gadget)
				&& gadget->speed == USB_SPEED_HIGH
				&& dev->hs_config == शून्य) अणु
			spin_unlock(&dev->lock);
			ERROR (dev, "no high speed config??\n");
			वापस -EINVAL;
		पूर्ण

		dev->state = STATE_DEV_CONNECTED;

		INFO (dev, "connected\n");
		event = next_event (dev, GADGETFS_CONNECT);
		event->u.speed = gadget->speed;
		ep0_पढ़ोable (dev);

	/* host may have given up रुकोing क्रम response.  we can miss control
	 * requests handled lower करोwn (device/endpoपूर्णांक status and features);
	 * then ep0_अणुपढ़ो,ग_लिखोपूर्ण will report the wrong status. controller
	 * driver will have पातed pending i/o.
	 */
	पूर्ण अन्यथा अगर (dev->state == STATE_DEV_SETUP)
		dev->setup_पात = 1;

	req->buf = dev->rbuf;
	req->context = शून्य;
	चयन (ctrl->bRequest) अणु

	हाल USB_REQ_GET_DESCRIPTOR:
		अगर (ctrl->bRequestType != USB_सूची_IN)
			जाओ unrecognized;
		चयन (w_value >> 8) अणु

		हाल USB_DT_DEVICE:
			value = min (w_length, (u16) माप *dev->dev);
			dev->dev->bMaxPacketSize0 = dev->gadget->ep0->maxpacket;
			req->buf = dev->dev;
			अवरोध;
		हाल USB_DT_DEVICE_QUALIFIER:
			अगर (!dev->hs_config)
				अवरोध;
			value = min (w_length, (u16)
				माप (काष्ठा usb_qualअगरier_descriptor));
			make_qualअगरier (dev);
			अवरोध;
		हाल USB_DT_OTHER_SPEED_CONFIG:
		हाल USB_DT_CONFIG:
			value = config_buf (dev,
					w_value >> 8,
					w_value & 0xff);
			अगर (value >= 0)
				value = min (w_length, (u16) value);
			अवरोध;
		हाल USB_DT_STRING:
			जाओ unrecognized;

		शेष:		// all others are errors
			अवरोध;
		पूर्ण
		अवरोध;

	/* currently one config, two speeds */
	हाल USB_REQ_SET_CONFIGURATION:
		अगर (ctrl->bRequestType != 0)
			जाओ unrecognized;
		अगर (0 == (u8) w_value) अणु
			value = 0;
			dev->current_config = 0;
			usb_gadget_vbus_draw(gadget, 8 /* mA */ );
			// user mode expected to disable endpoपूर्णांकs
		पूर्ण अन्यथा अणु
			u8	config, घातer;

			अगर (gadget_is_dualspeed(gadget)
					&& gadget->speed == USB_SPEED_HIGH) अणु
				config = dev->hs_config->bConfigurationValue;
				घातer = dev->hs_config->bMaxPower;
			पूर्ण अन्यथा अणु
				config = dev->config->bConfigurationValue;
				घातer = dev->config->bMaxPower;
			पूर्ण

			अगर (config == (u8) w_value) अणु
				value = 0;
				dev->current_config = config;
				usb_gadget_vbus_draw(gadget, 2 * घातer);
			पूर्ण
		पूर्ण

		/* report SET_CONFIGURATION like any other control request,
		 * except that usermode may not stall this.  the next
		 * request mustn't be allowed start until this finishes:
		 * endpoपूर्णांकs and thपढ़ोs set up, etc.
		 *
		 * NOTE:  older PXA hardware (beक्रमe PXA 255: without UDCCFR)
		 * has bad/racey स्वतःmagic that prevents synchronizing here.
		 * even kernel mode drivers often miss them.
		 */
		अगर (value == 0) अणु
			INFO (dev, "configuration #%d\n", dev->current_config);
			usb_gadget_set_state(gadget, USB_STATE_CONFIGURED);
			अगर (dev->usermode_setup) अणु
				dev->setup_can_stall = 0;
				जाओ delegate;
			पूर्ण
		पूर्ण
		अवरोध;

#अगर_अघोषित	CONFIG_USB_PXA25X
	/* PXA स्वतःmagically handles this request too */
	हाल USB_REQ_GET_CONFIGURATION:
		अगर (ctrl->bRequestType != 0x80)
			जाओ unrecognized;
		*(u8 *)req->buf = dev->current_config;
		value = min (w_length, (u16) 1);
		अवरोध;
#पूर्ण_अगर

	शेष:
unrecognized:
		VDEBUG (dev, "%s req%02x.%02x v%04x i%04x l%d\n",
			dev->usermode_setup ? "delegate" : "fail",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, le16_to_cpu(ctrl->wIndex), w_length);

		/* अगर there's an ep0 reader, don't stall */
		अगर (dev->usermode_setup) अणु
			dev->setup_can_stall = 1;
delegate:
			dev->setup_in = (ctrl->bRequestType & USB_सूची_IN)
						? 1 : 0;
			dev->setup_wLength = w_length;
			dev->setup_out_पढ़ोy = 0;
			dev->setup_out_error = 0;

			/* पढ़ो DATA stage क्रम OUT right away */
			अगर (unlikely (!dev->setup_in && w_length)) अणु
				value = setup_req (gadget->ep0, dev->req,
							w_length);
				अगर (value < 0)
					अवरोध;

				++dev->udc_usage;
				spin_unlock (&dev->lock);
				value = usb_ep_queue (gadget->ep0, dev->req,
							GFP_KERNEL);
				spin_lock (&dev->lock);
				--dev->udc_usage;
				अगर (value < 0) अणु
					clean_req (gadget->ep0, dev->req);
					अवरोध;
				पूर्ण

				/* we can't currently stall these */
				dev->setup_can_stall = 0;
			पूर्ण

			/* state changes when पढ़ोer collects event */
			event = next_event (dev, GADGETFS_SETUP);
			event->u.setup = *ctrl;
			ep0_पढ़ोable (dev);
			spin_unlock (&dev->lock);
			वापस 0;
		पूर्ण
	पूर्ण

	/* proceed with data transfer and status phases? */
	अगर (value >= 0 && dev->state != STATE_DEV_SETUP) अणु
		req->length = value;
		req->zero = value < w_length;

		++dev->udc_usage;
		spin_unlock (&dev->lock);
		value = usb_ep_queue (gadget->ep0, req, GFP_KERNEL);
		spin_lock(&dev->lock);
		--dev->udc_usage;
		spin_unlock(&dev->lock);
		अगर (value < 0) अणु
			DBG (dev, "ep_queue --> %d\n", value);
			req->status = 0;
		पूर्ण
		वापस value;
	पूर्ण

	/* device stalls when value < 0 */
	spin_unlock (&dev->lock);
	वापस value;
पूर्ण

अटल व्योम destroy_ep_files (काष्ठा dev_data *dev)
अणु
	DBG (dev, "%s %d\n", __func__, dev->state);

	/* dev->state must prevent पूर्णांकerference */
	spin_lock_irq (&dev->lock);
	जबतक (!list_empty(&dev->epfiles)) अणु
		काष्ठा ep_data	*ep;
		काष्ठा inode	*parent;
		काष्ठा dentry	*dentry;

		/* अवरोध link to FS */
		ep = list_first_entry (&dev->epfiles, काष्ठा ep_data, epfiles);
		list_del_init (&ep->epfiles);
		spin_unlock_irq (&dev->lock);

		dentry = ep->dentry;
		ep->dentry = शून्य;
		parent = d_inode(dentry->d_parent);

		/* अवरोध link to controller */
		mutex_lock(&ep->lock);
		अगर (ep->state == STATE_EP_ENABLED)
			(व्योम) usb_ep_disable (ep->ep);
		ep->state = STATE_EP_UNBOUND;
		usb_ep_मुक्त_request (ep->ep, ep->req);
		ep->ep = शून्य;
		mutex_unlock(&ep->lock);

		wake_up (&ep->रुको);
		put_ep (ep);

		/* अवरोध link to dcache */
		inode_lock(parent);
		d_delete (dentry);
		dput (dentry);
		inode_unlock(parent);

		spin_lock_irq (&dev->lock);
	पूर्ण
	spin_unlock_irq (&dev->lock);
पूर्ण


अटल काष्ठा dentry *
gadgetfs_create_file (काष्ठा super_block *sb, अक्षर स्थिर *name,
		व्योम *data, स्थिर काष्ठा file_operations *fops);

अटल पूर्णांक activate_ep_files (काष्ठा dev_data *dev)
अणु
	काष्ठा usb_ep	*ep;
	काष्ठा ep_data	*data;

	gadget_क्रम_each_ep (ep, dev->gadget) अणु

		data = kzalloc(माप(*data), GFP_KERNEL);
		अगर (!data)
			जाओ enomem0;
		data->state = STATE_EP_DISABLED;
		mutex_init(&data->lock);
		init_रुकोqueue_head (&data->रुको);

		म_नकलन (data->name, ep->name, माप (data->name) - 1);
		refcount_set (&data->count, 1);
		data->dev = dev;
		get_dev (dev);

		data->ep = ep;
		ep->driver_data = data;

		data->req = usb_ep_alloc_request (ep, GFP_KERNEL);
		अगर (!data->req)
			जाओ enomem1;

		data->dentry = gadgetfs_create_file (dev->sb, data->name,
				data, &ep_io_operations);
		अगर (!data->dentry)
			जाओ enomem2;
		list_add_tail (&data->epfiles, &dev->epfiles);
	पूर्ण
	वापस 0;

enomem2:
	usb_ep_मुक्त_request (ep, data->req);
enomem1:
	put_dev (dev);
	kमुक्त (data);
enomem0:
	DBG (dev, "%s enomem\n", __func__);
	destroy_ep_files (dev);
	वापस -ENOMEM;
पूर्ण

अटल व्योम
gadgetfs_unbind (काष्ठा usb_gadget *gadget)
अणु
	काष्ठा dev_data		*dev = get_gadget_data (gadget);

	DBG (dev, "%s\n", __func__);

	spin_lock_irq (&dev->lock);
	dev->state = STATE_DEV_UNBOUND;
	जबतक (dev->udc_usage > 0) अणु
		spin_unlock_irq(&dev->lock);
		usleep_range(1000, 2000);
		spin_lock_irq(&dev->lock);
	पूर्ण
	spin_unlock_irq (&dev->lock);

	destroy_ep_files (dev);
	gadget->ep0->driver_data = शून्य;
	set_gadget_data (gadget, शून्य);

	/* we've alपढ़ोy been disconnected ... no i/o is active */
	अगर (dev->req)
		usb_ep_मुक्त_request (gadget->ep0, dev->req);
	DBG (dev, "%s done\n", __func__);
	put_dev (dev);
पूर्ण

अटल काष्ठा dev_data		*the_device;

अटल पूर्णांक gadgetfs_bind(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा dev_data		*dev = the_device;

	अगर (!dev)
		वापस -ESRCH;
	अगर (0 != म_भेद (CHIP, gadget->name)) अणु
		pr_err("%s expected %s controller not %s\n",
			लघुname, CHIP, gadget->name);
		वापस -ENODEV;
	पूर्ण

	set_gadget_data (gadget, dev);
	dev->gadget = gadget;
	gadget->ep0->driver_data = dev;

	/* pपुनः_स्मृतिate control response and buffer */
	dev->req = usb_ep_alloc_request (gadget->ep0, GFP_KERNEL);
	अगर (!dev->req)
		जाओ enomem;
	dev->req->context = शून्य;
	dev->req->complete = epio_complete;

	अगर (activate_ep_files (dev) < 0)
		जाओ enomem;

	INFO (dev, "bound to %s driver\n", gadget->name);
	spin_lock_irq(&dev->lock);
	dev->state = STATE_DEV_UNCONNECTED;
	spin_unlock_irq(&dev->lock);
	get_dev (dev);
	वापस 0;

enomem:
	gadgetfs_unbind (gadget);
	वापस -ENOMEM;
पूर्ण

अटल व्योम
gadgetfs_disconnect (काष्ठा usb_gadget *gadget)
अणु
	काष्ठा dev_data		*dev = get_gadget_data (gadget);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave (&dev->lock, flags);
	अगर (dev->state == STATE_DEV_UNCONNECTED)
		जाओ निकास;
	dev->state = STATE_DEV_UNCONNECTED;

	INFO (dev, "disconnected\n");
	next_event (dev, GADGETFS_DISCONNECT);
	ep0_पढ़ोable (dev);
निकास:
	spin_unlock_irqrestore (&dev->lock, flags);
पूर्ण

अटल व्योम
gadgetfs_suspend (काष्ठा usb_gadget *gadget)
अणु
	काष्ठा dev_data		*dev = get_gadget_data (gadget);
	अचिन्हित दीर्घ		flags;

	INFO (dev, "suspended from state %d\n", dev->state);
	spin_lock_irqsave(&dev->lock, flags);
	चयन (dev->state) अणु
	हाल STATE_DEV_SETUP:		// VERY odd... host died??
	हाल STATE_DEV_CONNECTED:
	हाल STATE_DEV_UNCONNECTED:
		next_event (dev, GADGETFS_SUSPEND);
		ep0_पढ़ोable (dev);
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

अटल काष्ठा usb_gadget_driver gadgetfs_driver = अणु
	.function	= (अक्षर *) driver_desc,
	.bind		= gadgetfs_bind,
	.unbind		= gadgetfs_unbind,
	.setup		= gadgetfs_setup,
	.reset		= gadgetfs_disconnect,
	.disconnect	= gadgetfs_disconnect,
	.suspend	= gadgetfs_suspend,

	.driver	= अणु
		.name		= लघुname,
	पूर्ण,
पूर्ण;

/*----------------------------------------------------------------------*/
/* DEVICE INITIALIZATION
 *
 *     fd = खोलो ("/dev/gadget/$CHIP", O_RDWR)
 *     status = ग_लिखो (fd, descriptors, माप descriptors)
 *
 * That ग_लिखो establishes the device configuration, so the kernel can
 * bind to the controller ... guaranteeing it can handle क्रमागतeration
 * at all necessary speeds.  Descriptor order is:
 *
 * . message tag (u32, host order) ... क्रम now, must be zero; it
 *	would change to support features like multi-config devices
 * . full/low speed config ... all wTotalLength bytes (with पूर्णांकerface,
 *	class, altsetting, endpoपूर्णांक, and other descriptors)
 * . high speed config ... all descriptors, क्रम high speed operation;
 *	this one's optional except क्रम high-speed hardware
 * . device descriptor
 *
 * Endpoपूर्णांकs are not yet enabled. Drivers must रुको until device
 * configuration and पूर्णांकerface altsetting changes create
 * the need to configure (or unconfigure) them.
 *
 * After initialization, the device stays active क्रम as दीर्घ as that
 * $CHIP file is खोलो.  Events must then be पढ़ो from that descriptor,
 * such as configuration notअगरications.
 */

अटल पूर्णांक is_valid_config(काष्ठा usb_config_descriptor *config,
		अचिन्हित पूर्णांक total)
अणु
	वापस config->bDescriptorType == USB_DT_CONFIG
		&& config->bLength == USB_DT_CONFIG_SIZE
		&& total >= USB_DT_CONFIG_SIZE
		&& config->bConfigurationValue != 0
		&& (config->bmAttributes & USB_CONFIG_ATT_ONE) != 0
		&& (config->bmAttributes & USB_CONFIG_ATT_WAKEUP) == 0;
	/* FIXME अगर gadget->is_otg, _must_ include an otg descriptor */
	/* FIXME check lengths: walk to end */
पूर्ण

अटल sमाप_प्रकार
dev_config (काष्ठा file *fd, स्थिर अक्षर __user *buf, माप_प्रकार len, loff_t *ptr)
अणु
	काष्ठा dev_data		*dev = fd->निजी_data;
	sमाप_प्रकार			value, length = len;
	अचिन्हित		total;
	u32			tag;
	अक्षर			*kbuf;

	spin_lock_irq(&dev->lock);
	अगर (dev->state > STATE_DEV_OPENED) अणु
		value = ep0_ग_लिखो(fd, buf, len, ptr);
		spin_unlock_irq(&dev->lock);
		वापस value;
	पूर्ण
	spin_unlock_irq(&dev->lock);

	अगर ((len < (USB_DT_CONFIG_SIZE + USB_DT_DEVICE_SIZE + 4)) ||
	    (len > PAGE_SIZE * 4))
		वापस -EINVAL;

	/* we might need to change message क्रमmat someday */
	अगर (copy_from_user (&tag, buf, 4))
		वापस -EFAULT;
	अगर (tag != 0)
		वापस -EINVAL;
	buf += 4;
	length -= 4;

	kbuf = memdup_user(buf, length);
	अगर (IS_ERR(kbuf))
		वापस PTR_ERR(kbuf);

	spin_lock_irq (&dev->lock);
	value = -EINVAL;
	अगर (dev->buf) अणु
		kमुक्त(kbuf);
		जाओ fail;
	पूर्ण
	dev->buf = kbuf;

	/* full or low speed config */
	dev->config = (व्योम *) kbuf;
	total = le16_to_cpu(dev->config->wTotalLength);
	अगर (!is_valid_config(dev->config, total) ||
			total > length - USB_DT_DEVICE_SIZE)
		जाओ fail;
	kbuf += total;
	length -= total;

	/* optional high speed config */
	अगर (kbuf [1] == USB_DT_CONFIG) अणु
		dev->hs_config = (व्योम *) kbuf;
		total = le16_to_cpu(dev->hs_config->wTotalLength);
		अगर (!is_valid_config(dev->hs_config, total) ||
				total > length - USB_DT_DEVICE_SIZE)
			जाओ fail;
		kbuf += total;
		length -= total;
	पूर्ण अन्यथा अणु
		dev->hs_config = शून्य;
	पूर्ण

	/* could support multiple configs, using another encoding! */

	/* device descriptor (tweaked क्रम paranoia) */
	अगर (length != USB_DT_DEVICE_SIZE)
		जाओ fail;
	dev->dev = (व्योम *)kbuf;
	अगर (dev->dev->bLength != USB_DT_DEVICE_SIZE
			|| dev->dev->bDescriptorType != USB_DT_DEVICE
			|| dev->dev->bNumConfigurations != 1)
		जाओ fail;
	dev->dev->bcdUSB = cpu_to_le16 (0x0200);

	/* triggers gadgetfs_bind(); then we can क्रमागतerate. */
	spin_unlock_irq (&dev->lock);
	अगर (dev->hs_config)
		gadgetfs_driver.max_speed = USB_SPEED_HIGH;
	अन्यथा
		gadgetfs_driver.max_speed = USB_SPEED_FULL;

	value = usb_gadget_probe_driver(&gadgetfs_driver);
	अगर (value != 0) अणु
		kमुक्त (dev->buf);
		dev->buf = शून्य;
	पूर्ण अन्यथा अणु
		/* at this poपूर्णांक "good" hardware has क्रम the first समय
		 * let the USB the host see us.  alternatively, अगर users
		 * unplug/replug that will clear all the error state.
		 *
		 * note:  everything running beक्रमe here was guaranteed
		 * to choke driver model style diagnostics.  from here
		 * on, they can work ... except in cleanup paths that
		 * kick in after the ep0 descriptor is बंदd.
		 */
		value = len;
		dev->gadget_रेजिस्टरed = true;
	पूर्ण
	वापस value;

fail:
	spin_unlock_irq (&dev->lock);
	pr_debug ("%s: %s fail %zd, %p\n", लघुname, __func__, value, dev);
	kमुक्त (dev->buf);
	dev->buf = शून्य;
	वापस value;
पूर्ण

अटल पूर्णांक
dev_खोलो (काष्ठा inode *inode, काष्ठा file *fd)
अणु
	काष्ठा dev_data		*dev = inode->i_निजी;
	पूर्णांक			value = -EBUSY;

	spin_lock_irq(&dev->lock);
	अगर (dev->state == STATE_DEV_DISABLED) अणु
		dev->ev_next = 0;
		dev->state = STATE_DEV_OPENED;
		fd->निजी_data = dev;
		get_dev (dev);
		value = 0;
	पूर्ण
	spin_unlock_irq(&dev->lock);
	वापस value;
पूर्ण

अटल स्थिर काष्ठा file_operations ep0_operations = अणु
	.llseek =	no_llseek,

	.खोलो =		dev_खोलो,
	.पढ़ो =		ep0_पढ़ो,
	.ग_लिखो =	dev_config,
	.fasync =	ep0_fasync,
	.poll =		ep0_poll,
	.unlocked_ioctl = dev_ioctl,
	.release =	dev_release,
पूर्ण;

/*----------------------------------------------------------------------*/

/* खाताSYSTEM AND SUPERBLOCK OPERATIONS
 *
 * Mounting the fileप्रणाली creates a controller file, used first क्रम
 * device configuration then later क्रम event monitoring.
 */


/* FIXME PAM etc could set this security policy without mount options
 * अगर epfiles inherited ownership and permissons from ep0 ...
 */

अटल अचिन्हित शेष_uid;
अटल अचिन्हित शेष_gid;
अटल अचिन्हित शेष_perm = S_IRUSR | S_IWUSR;

module_param (शेष_uid, uपूर्णांक, 0644);
module_param (शेष_gid, uपूर्णांक, 0644);
module_param (शेष_perm, uपूर्णांक, 0644);


अटल काष्ठा inode *
gadgetfs_make_inode (काष्ठा super_block *sb,
		व्योम *data, स्थिर काष्ठा file_operations *fops,
		पूर्णांक mode)
अणु
	काष्ठा inode *inode = new_inode (sb);

	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode->i_mode = mode;
		inode->i_uid = make_kuid(&init_user_ns, शेष_uid);
		inode->i_gid = make_kgid(&init_user_ns, शेष_gid);
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय
				= current_समय(inode);
		inode->i_निजी = data;
		inode->i_fop = fops;
	पूर्ण
	वापस inode;
पूर्ण

/* creates in fs root directory, so non-renamable and non-linkable.
 * so inode and dentry are paired, until device reconfig.
 */
अटल काष्ठा dentry *
gadgetfs_create_file (काष्ठा super_block *sb, अक्षर स्थिर *name,
		व्योम *data, स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा dentry	*dentry;
	काष्ठा inode	*inode;

	dentry = d_alloc_name(sb->s_root, name);
	अगर (!dentry)
		वापस शून्य;

	inode = gadgetfs_make_inode (sb, data, fops,
			S_IFREG | (शेष_perm & S_IRWXUGO));
	अगर (!inode) अणु
		dput(dentry);
		वापस शून्य;
	पूर्ण
	d_add (dentry, inode);
	वापस dentry;
पूर्ण

अटल स्थिर काष्ठा super_operations gadget_fs_operations = अणु
	.statfs =	simple_statfs,
	.drop_inode =	generic_delete_inode,
पूर्ण;

अटल पूर्णांक
gadgetfs_fill_super (काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा inode	*inode;
	काष्ठा dev_data	*dev;

	अगर (the_device)
		वापस -ESRCH;

	CHIP = usb_get_gadget_udc_name();
	अगर (!CHIP)
		वापस -ENODEV;

	/* superblock */
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = GADGETFS_MAGIC;
	sb->s_op = &gadget_fs_operations;
	sb->s_समय_gran = 1;

	/* root inode */
	inode = gadgetfs_make_inode (sb,
			शून्य, &simple_dir_operations,
			S_IFसूची | S_IRUGO | S_IXUGO);
	अगर (!inode)
		जाओ Enomem;
	inode->i_op = &simple_dir_inode_operations;
	अगर (!(sb->s_root = d_make_root (inode)))
		जाओ Enomem;

	/* the ep0 file is named after the controller we expect;
	 * user mode code can use it क्रम sanity checks, like we करो.
	 */
	dev = dev_new ();
	अगर (!dev)
		जाओ Enomem;

	dev->sb = sb;
	dev->dentry = gadgetfs_create_file(sb, CHIP, dev, &ep0_operations);
	अगर (!dev->dentry) अणु
		put_dev(dev);
		जाओ Enomem;
	पूर्ण

	/* other endpoपूर्णांक files are available after hardware setup,
	 * from binding to a controller.
	 */
	the_device = dev;
	वापस 0;

Enomem:
	kमुक्त(CHIP);
	CHIP = शून्य;

	वापस -ENOMEM;
पूर्ण

/* "mount -t gadgetfs path /dev/gadget" ends up here */
अटल पूर्णांक gadgetfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, gadgetfs_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations gadgetfs_context_ops = अणु
	.get_tree	= gadgetfs_get_tree,
पूर्ण;

अटल पूर्णांक gadgetfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &gadgetfs_context_ops;
	वापस 0;
पूर्ण

अटल व्योम
gadgetfs_समाप्त_sb (काष्ठा super_block *sb)
अणु
	समाप्त_litter_super (sb);
	अगर (the_device) अणु
		put_dev (the_device);
		the_device = शून्य;
	पूर्ण
	kमुक्त(CHIP);
	CHIP = शून्य;
पूर्ण

/*----------------------------------------------------------------------*/

अटल काष्ठा file_प्रणाली_type gadgetfs_type = अणु
	.owner		= THIS_MODULE,
	.name		= लघुname,
	.init_fs_context = gadgetfs_init_fs_context,
	.समाप्त_sb	= gadgetfs_समाप्त_sb,
पूर्ण;
MODULE_ALIAS_FS("gadgetfs");

/*----------------------------------------------------------------------*/

अटल पूर्णांक __init init (व्योम)
अणु
	पूर्णांक status;

	status = रेजिस्टर_fileप्रणाली (&gadgetfs_type);
	अगर (status == 0)
		pr_info ("%s: %s, version " DRIVER_VERSION "\n",
			लघुname, driver_desc);
	वापस status;
पूर्ण
module_init (init);

अटल व्योम __निकास cleanup (व्योम)
अणु
	pr_debug ("unregister %s\n", लघुname);
	unरेजिस्टर_fileप्रणाली (&gadgetfs_type);
पूर्ण
module_निकास (cleanup);

