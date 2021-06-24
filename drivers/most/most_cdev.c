<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cdev.c - Character device component क्रम Mostcore
 *
 * Copyright (C) 2013-2015 Microchip Technology Germany II GmbH & Co. KG
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/poll.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/idr.h>
#समावेश <linux/most.h>

#घोषणा CHRDEV_REGION_SIZE 50

अटल काष्ठा cdev_component अणु
	dev_t devno;
	काष्ठा ida minor_id;
	अचिन्हित पूर्णांक major;
	काष्ठा class *class;
	काष्ठा most_component cc;
पूर्ण comp;

काष्ठा comp_channel अणु
	रुको_queue_head_t wq;
	spinlock_t unlink;	/* synchronization lock to unlink channels */
	काष्ठा cdev cdev;
	काष्ठा device *dev;
	काष्ठा mutex io_mutex;
	काष्ठा most_पूर्णांकerface *अगरace;
	काष्ठा most_channel_config *cfg;
	अचिन्हित पूर्णांक channel_id;
	dev_t devno;
	माप_प्रकार mbo_offs;
	DECLARE_KFIFO_PTR(fअगरo, typeof(काष्ठा mbo *));
	पूर्णांक access_ref;
	काष्ठा list_head list;
पूर्ण;

#घोषणा to_channel(d) container_of(d, काष्ठा comp_channel, cdev)
अटल LIST_HEAD(channel_list);
अटल DEFINE_SPINLOCK(ch_list_lock);

अटल अंतरभूत bool ch_has_mbo(काष्ठा comp_channel *c)
अणु
	वापस channel_has_mbo(c->अगरace, c->channel_id, &comp.cc) > 0;
पूर्ण

अटल अंतरभूत काष्ठा mbo *ch_get_mbo(काष्ठा comp_channel *c, काष्ठा mbo **mbo)
अणु
	अगर (!kfअगरo_peek(&c->fअगरo, mbo)) अणु
		*mbo = most_get_mbo(c->अगरace, c->channel_id, &comp.cc);
		अगर (*mbo)
			kfअगरo_in(&c->fअगरo, mbo, 1);
	पूर्ण
	वापस *mbo;
पूर्ण

अटल काष्ठा comp_channel *get_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक id)
अणु
	काष्ठा comp_channel *c, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ch_list_lock, flags);
	list_क्रम_each_entry_safe(c, पंचांगp, &channel_list, list) अणु
		अगर ((c->अगरace == अगरace) && (c->channel_id == id)) अणु
			spin_unlock_irqrestore(&ch_list_lock, flags);
			वापस c;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ch_list_lock, flags);
	वापस शून्य;
पूर्ण

अटल व्योम stop_channel(काष्ठा comp_channel *c)
अणु
	काष्ठा mbo *mbo;

	जबतक (kfअगरo_out((काष्ठा kfअगरo *)&c->fअगरo, &mbo, 1))
		most_put_mbo(mbo);
	most_stop_channel(c->अगरace, c->channel_id, &comp.cc);
पूर्ण

अटल व्योम destroy_cdev(काष्ठा comp_channel *c)
अणु
	अचिन्हित दीर्घ flags;

	device_destroy(comp.class, c->devno);
	cdev_del(&c->cdev);
	spin_lock_irqsave(&ch_list_lock, flags);
	list_del(&c->list);
	spin_unlock_irqrestore(&ch_list_lock, flags);
पूर्ण

अटल व्योम destroy_channel(काष्ठा comp_channel *c)
अणु
	ida_simple_हटाओ(&comp.minor_id, MINOR(c->devno));
	kfअगरo_मुक्त(&c->fअगरo);
	kमुक्त(c);
पूर्ण

/**
 * comp_खोलो - implements the syscall to खोलो the device
 * @inode: inode poपूर्णांकer
 * @filp: file poपूर्णांकer
 *
 * This stores the channel poपूर्णांकer in the निजी data field of
 * the file काष्ठाure and activates the channel within the core.
 */
अटल पूर्णांक comp_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा comp_channel *c;
	पूर्णांक ret;

	c = to_channel(inode->i_cdev);
	filp->निजी_data = c;

	अगर (((c->cfg->direction == MOST_CH_RX) &&
	     ((filp->f_flags & O_ACCMODE) != O_RDONLY)) ||
	     ((c->cfg->direction == MOST_CH_TX) &&
		((filp->f_flags & O_ACCMODE) != O_WRONLY))) अणु
		वापस -EACCES;
	पूर्ण

	mutex_lock(&c->io_mutex);
	अगर (!c->dev) अणु
		mutex_unlock(&c->io_mutex);
		वापस -ENODEV;
	पूर्ण

	अगर (c->access_ref) अणु
		mutex_unlock(&c->io_mutex);
		वापस -EBUSY;
	पूर्ण

	c->mbo_offs = 0;
	ret = most_start_channel(c->अगरace, c->channel_id, &comp.cc);
	अगर (!ret)
		c->access_ref = 1;
	mutex_unlock(&c->io_mutex);
	वापस ret;
पूर्ण

/**
 * comp_बंद - implements the syscall to बंद the device
 * @inode: inode poपूर्णांकer
 * @filp: file poपूर्णांकer
 *
 * This stops the channel within the core.
 */
अटल पूर्णांक comp_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा comp_channel *c = to_channel(inode->i_cdev);

	mutex_lock(&c->io_mutex);
	spin_lock(&c->unlink);
	c->access_ref = 0;
	spin_unlock(&c->unlink);
	अगर (c->dev) अणु
		stop_channel(c);
		mutex_unlock(&c->io_mutex);
	पूर्ण अन्यथा अणु
		mutex_unlock(&c->io_mutex);
		destroy_channel(c);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * comp_ग_लिखो - implements the syscall to ग_लिखो to the device
 * @filp: file poपूर्णांकer
 * @buf: poपूर्णांकer to user buffer
 * @count: number of bytes to ग_लिखो
 * @offset: offset from where to start writing
 */
अटल sमाप_प्रकार comp_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *offset)
अणु
	पूर्णांक ret;
	माप_प्रकार to_copy, left;
	काष्ठा mbo *mbo = शून्य;
	काष्ठा comp_channel *c = filp->निजी_data;

	mutex_lock(&c->io_mutex);
	जबतक (c->dev && !ch_get_mbo(c, &mbo)) अणु
		mutex_unlock(&c->io_mutex);

		अगर ((filp->f_flags & O_NONBLOCK))
			वापस -EAGAIN;
		अगर (रुको_event_पूर्णांकerruptible(c->wq, ch_has_mbo(c) || !c->dev))
			वापस -ERESTARTSYS;
		mutex_lock(&c->io_mutex);
	पूर्ण

	अगर (unlikely(!c->dev)) अणु
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण

	to_copy = min(count, c->cfg->buffer_size - c->mbo_offs);
	left = copy_from_user(mbo->virt_address + c->mbo_offs, buf, to_copy);
	अगर (left == to_copy) अणु
		ret = -EFAULT;
		जाओ unlock;
	पूर्ण

	c->mbo_offs += to_copy - left;
	अगर (c->mbo_offs >= c->cfg->buffer_size ||
	    c->cfg->data_type == MOST_CH_CONTROL ||
	    c->cfg->data_type == MOST_CH_ASYNC) अणु
		kfअगरo_skip(&c->fअगरo);
		mbo->buffer_length = c->mbo_offs;
		c->mbo_offs = 0;
		most_submit_mbo(mbo);
	पूर्ण

	ret = to_copy - left;
unlock:
	mutex_unlock(&c->io_mutex);
	वापस ret;
पूर्ण

/**
 * comp_पढ़ो - implements the syscall to पढ़ो from the device
 * @filp: file poपूर्णांकer
 * @buf: poपूर्णांकer to user buffer
 * @count: number of bytes to पढ़ो
 * @offset: offset from where to start पढ़ोing
 */
अटल sमाप_प्रकार
comp_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	माप_प्रकार to_copy, not_copied, copied;
	काष्ठा mbo *mbo = शून्य;
	काष्ठा comp_channel *c = filp->निजी_data;

	mutex_lock(&c->io_mutex);
	जबतक (c->dev && !kfअगरo_peek(&c->fअगरo, &mbo)) अणु
		mutex_unlock(&c->io_mutex);
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		अगर (रुको_event_पूर्णांकerruptible(c->wq,
					     (!kfअगरo_is_empty(&c->fअगरo) ||
					      (!c->dev))))
			वापस -ERESTARTSYS;
		mutex_lock(&c->io_mutex);
	पूर्ण

	/* make sure we करोn't submit to gone devices */
	अगर (unlikely(!c->dev)) अणु
		mutex_unlock(&c->io_mutex);
		वापस -ENODEV;
	पूर्ण

	to_copy = min_t(माप_प्रकार,
			count,
			mbo->processed_length - c->mbo_offs);

	not_copied = copy_to_user(buf,
				  mbo->virt_address + c->mbo_offs,
				  to_copy);

	copied = to_copy - not_copied;

	c->mbo_offs += copied;
	अगर (c->mbo_offs >= mbo->processed_length) अणु
		kfअगरo_skip(&c->fअगरo);
		most_put_mbo(mbo);
		c->mbo_offs = 0;
	पूर्ण
	mutex_unlock(&c->io_mutex);
	वापस copied;
पूर्ण

अटल __poll_t comp_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा comp_channel *c = filp->निजी_data;
	__poll_t mask = 0;

	poll_रुको(filp, &c->wq, रुको);

	mutex_lock(&c->io_mutex);
	अगर (c->cfg->direction == MOST_CH_RX) अणु
		अगर (!c->dev || !kfअगरo_is_empty(&c->fअगरo))
			mask |= EPOLLIN | EPOLLRDNORM;
	पूर्ण अन्यथा अणु
		अगर (!c->dev || !kfअगरo_is_empty(&c->fअगरo) || ch_has_mbo(c))
			mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण
	mutex_unlock(&c->io_mutex);
	वापस mask;
पूर्ण

/**
 * Initialization of काष्ठा file_operations
 */
अटल स्थिर काष्ठा file_operations channel_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = comp_पढ़ो,
	.ग_लिखो = comp_ग_लिखो,
	.खोलो = comp_खोलो,
	.release = comp_बंद,
	.poll = comp_poll,
पूर्ण;

/**
 * comp_disconnect_channel - disconnect a channel
 * @अगरace: poपूर्णांकer to पूर्णांकerface instance
 * @channel_id: channel index
 *
 * This मुक्तs allocated memory and हटाओs the cdev that represents this
 * channel in user space.
 */
अटल पूर्णांक comp_disconnect_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_id)
अणु
	काष्ठा comp_channel *c;

	c = get_channel(अगरace, channel_id);
	अगर (!c)
		वापस -EINVAL;

	mutex_lock(&c->io_mutex);
	spin_lock(&c->unlink);
	c->dev = शून्य;
	spin_unlock(&c->unlink);
	destroy_cdev(c);
	अगर (c->access_ref) अणु
		stop_channel(c);
		wake_up_पूर्णांकerruptible(&c->wq);
		mutex_unlock(&c->io_mutex);
	पूर्ण अन्यथा अणु
		mutex_unlock(&c->io_mutex);
		destroy_channel(c);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * comp_rx_completion - completion handler क्रम rx channels
 * @mbo: poपूर्णांकer to buffer object that has completed
 *
 * This searches क्रम the channel linked to this MBO and stores it in the local
 * fअगरo buffer.
 */
अटल पूर्णांक comp_rx_completion(काष्ठा mbo *mbo)
अणु
	काष्ठा comp_channel *c;

	अगर (!mbo)
		वापस -EINVAL;

	c = get_channel(mbo->अगरp, mbo->hdm_channel_id);
	अगर (!c)
		वापस -EINVAL;

	spin_lock(&c->unlink);
	अगर (!c->access_ref || !c->dev) अणु
		spin_unlock(&c->unlink);
		वापस -ENODEV;
	पूर्ण
	kfअगरo_in(&c->fअगरo, &mbo, 1);
	spin_unlock(&c->unlink);
#अगर_घोषित DEBUG_MESG
	अगर (kfअगरo_is_full(&c->fअगरo))
		dev_warn(c->dev, "Fifo is full\n");
#पूर्ण_अगर
	wake_up_पूर्णांकerruptible(&c->wq);
	वापस 0;
पूर्ण

/**
 * comp_tx_completion - completion handler क्रम tx channels
 * @अगरace: poपूर्णांकer to पूर्णांकerface instance
 * @channel_id: channel index/ID
 *
 * This wakes sleeping processes in the रुको-queue.
 */
अटल पूर्णांक comp_tx_completion(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_id)
अणु
	काष्ठा comp_channel *c;

	c = get_channel(अगरace, channel_id);
	अगर (!c)
		वापस -EINVAL;

	अगर ((channel_id < 0) || (channel_id >= अगरace->num_channels)) अणु
		dev_warn(c->dev, "Channel ID out of range\n");
		वापस -EINVAL;
	पूर्ण

	wake_up_पूर्णांकerruptible(&c->wq);
	वापस 0;
पूर्ण

/**
 * comp_probe - probe function of the driver module
 * @अगरace: poपूर्णांकer to पूर्णांकerface instance
 * @channel_id: channel index/ID
 * @cfg: poपूर्णांकer to actual channel configuration
 * @name: name of the device to be created
 *
 * This allocates achannel object and creates the device node in /dev
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक comp_probe(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_id,
		      काष्ठा most_channel_config *cfg, अक्षर *name, अक्षर *args)
अणु
	काष्ठा comp_channel *c;
	अचिन्हित दीर्घ cl_flags;
	पूर्णांक retval;
	पूर्णांक current_minor;

	अगर (!cfg || !name)
		वापस -EINVAL;

	c = get_channel(अगरace, channel_id);
	अगर (c)
		वापस -EEXIST;

	current_minor = ida_simple_get(&comp.minor_id, 0, 0, GFP_KERNEL);
	अगर (current_minor < 0)
		वापस current_minor;

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c) अणु
		retval = -ENOMEM;
		जाओ err_हटाओ_ida;
	पूर्ण

	c->devno = MKDEV(comp.major, current_minor);
	cdev_init(&c->cdev, &channel_fops);
	c->cdev.owner = THIS_MODULE;
	retval = cdev_add(&c->cdev, c->devno, 1);
	अगर (retval < 0)
		जाओ err_मुक्त_c;
	c->अगरace = अगरace;
	c->cfg = cfg;
	c->channel_id = channel_id;
	c->access_ref = 0;
	spin_lock_init(&c->unlink);
	INIT_KFIFO(c->fअगरo);
	retval = kfअगरo_alloc(&c->fअगरo, cfg->num_buffers, GFP_KERNEL);
	अगर (retval)
		जाओ err_del_cdev_and_मुक्त_channel;
	init_रुकोqueue_head(&c->wq);
	mutex_init(&c->io_mutex);
	spin_lock_irqsave(&ch_list_lock, cl_flags);
	list_add_tail(&c->list, &channel_list);
	spin_unlock_irqrestore(&ch_list_lock, cl_flags);
	c->dev = device_create(comp.class, शून्य, c->devno, शून्य, "%s", name);

	अगर (IS_ERR(c->dev)) अणु
		retval = PTR_ERR(c->dev);
		जाओ err_मुक्त_kfअगरo_and_del_list;
	पूर्ण
	kobject_uevent(&c->dev->kobj, KOBJ_ADD);
	वापस 0;

err_मुक्त_kfअगरo_and_del_list:
	kfअगरo_मुक्त(&c->fअगरo);
	list_del(&c->list);
err_del_cdev_and_मुक्त_channel:
	cdev_del(&c->cdev);
err_मुक्त_c:
	kमुक्त(c);
err_हटाओ_ida:
	ida_simple_हटाओ(&comp.minor_id, current_minor);
	वापस retval;
पूर्ण

अटल काष्ठा cdev_component comp = अणु
	.cc = अणु
		.mod = THIS_MODULE,
		.name = "cdev",
		.probe_channel = comp_probe,
		.disconnect_channel = comp_disconnect_channel,
		.rx_completion = comp_rx_completion,
		.tx_completion = comp_tx_completion,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mod_init(व्योम)
अणु
	पूर्णांक err;

	comp.class = class_create(THIS_MODULE, "most_cdev");
	अगर (IS_ERR(comp.class))
		वापस PTR_ERR(comp.class);

	ida_init(&comp.minor_id);

	err = alloc_chrdev_region(&comp.devno, 0, CHRDEV_REGION_SIZE, "cdev");
	अगर (err < 0)
		जाओ dest_ida;
	comp.major = MAJOR(comp.devno);
	err = most_रेजिस्टर_component(&comp.cc);
	अगर (err)
		जाओ मुक्त_cdev;
	err = most_रेजिस्टर_configfs_subsys(&comp.cc);
	अगर (err)
		जाओ deरेजिस्टर_comp;
	वापस 0;

deरेजिस्टर_comp:
	most_deरेजिस्टर_component(&comp.cc);
मुक्त_cdev:
	unरेजिस्टर_chrdev_region(comp.devno, CHRDEV_REGION_SIZE);
dest_ida:
	ida_destroy(&comp.minor_id);
	class_destroy(comp.class);
	वापस err;
पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
	काष्ठा comp_channel *c, *पंचांगp;

	most_deरेजिस्टर_configfs_subsys(&comp.cc);
	most_deरेजिस्टर_component(&comp.cc);

	list_क्रम_each_entry_safe(c, पंचांगp, &channel_list, list) अणु
		destroy_cdev(c);
		destroy_channel(c);
	पूर्ण
	unरेजिस्टर_chrdev_region(comp.devno, CHRDEV_REGION_SIZE);
	ida_destroy(&comp.minor_id);
	class_destroy(comp.class);
पूर्ण

module_init(mod_init);
module_निकास(mod_निकास);
MODULE_AUTHOR("Christian Gromm <christian.gromm@microchip.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("character device component for mostcore");
