<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2021, Linaro Ltd <loic.poulain@linaro.org> */

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/wwan.h>

#घोषणा WWAN_MAX_MINORS 256 /* 256 minors allowed with रेजिस्टर_chrdev() */

अटल DEFINE_MUTEX(wwan_रेजिस्टर_lock); /* WWAN device create|हटाओ lock */
अटल DEFINE_IDA(minors); /* minors क्रम WWAN port अक्षरdevs */
अटल DEFINE_IDA(wwan_dev_ids); /* क्रम unique WWAN device IDs */
अटल काष्ठा class *wwan_class;
अटल पूर्णांक wwan_major;

#घोषणा to_wwan_dev(d) container_of(d, काष्ठा wwan_device, dev)
#घोषणा to_wwan_port(d) container_of(d, काष्ठा wwan_port, dev)

/* WWAN port flags */
#घोषणा WWAN_PORT_TX_OFF	0

/**
 * काष्ठा wwan_device - The काष्ठाure that defines a WWAN device
 *
 * @id: WWAN device unique ID.
 * @dev: Underlying device.
 * @port_id: Current available port ID to pick.
 */
काष्ठा wwan_device अणु
	अचिन्हित पूर्णांक id;
	काष्ठा device dev;
	atomic_t port_id;
पूर्ण;

/**
 * काष्ठा wwan_port - The काष्ठाure that defines a WWAN port
 * @type: Port type
 * @start_count: Port start counter
 * @flags: Store port state and capabilities
 * @ops: Poपूर्णांकer to WWAN port operations
 * @ops_lock: Protect port ops
 * @dev: Underlying device
 * @rxq: Buffer inbound queue
 * @रुकोqueue: The रुकोqueue क्रम port fops (पढ़ो/ग_लिखो/poll)
 */
काष्ठा wwan_port अणु
	क्रमागत wwan_port_type type;
	अचिन्हित पूर्णांक start_count;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा wwan_port_ops *ops;
	काष्ठा mutex ops_lock; /* Serialize ops + protect against removal */
	काष्ठा device dev;
	काष्ठा sk_buff_head rxq;
	रुको_queue_head_t रुकोqueue;
पूर्ण;

अटल व्योम wwan_dev_destroy(काष्ठा device *dev)
अणु
	काष्ठा wwan_device *wwandev = to_wwan_dev(dev);

	ida_मुक्त(&wwan_dev_ids, wwandev->id);
	kमुक्त(wwandev);
पूर्ण

अटल स्थिर काष्ठा device_type wwan_dev_type = अणु
	.name    = "wwan_dev",
	.release = wwan_dev_destroy,
पूर्ण;

अटल पूर्णांक wwan_dev_parent_match(काष्ठा device *dev, स्थिर व्योम *parent)
अणु
	वापस (dev->type == &wwan_dev_type && dev->parent == parent);
पूर्ण

अटल काष्ठा wwan_device *wwan_dev_get_by_parent(काष्ठा device *parent)
अणु
	काष्ठा device *dev;

	dev = class_find_device(wwan_class, शून्य, parent, wwan_dev_parent_match);
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	वापस to_wwan_dev(dev);
पूर्ण

/* This function allocates and रेजिस्टरs a new WWAN device OR अगर a WWAN device
 * alपढ़ोy exist क्रम the given parent, it माला_लो a reference and वापस it.
 * This function is not exported (क्रम now), it is called indirectly via
 * wwan_create_port().
 */
अटल काष्ठा wwan_device *wwan_create_dev(काष्ठा device *parent)
अणु
	काष्ठा wwan_device *wwandev;
	पूर्णांक err, id;

	/* The 'find-alloc-register' operation must be रक्षित against
	 * concurrent execution, a WWAN device is possibly shared between
	 * multiple callers or concurrently unरेजिस्टरed from wwan_हटाओ_dev().
	 */
	mutex_lock(&wwan_रेजिस्टर_lock);

	/* If wwandev alपढ़ोy exists, वापस it */
	wwandev = wwan_dev_get_by_parent(parent);
	अगर (!IS_ERR(wwandev))
		जाओ करोne_unlock;

	id = ida_alloc(&wwan_dev_ids, GFP_KERNEL);
	अगर (id < 0)
		जाओ करोne_unlock;

	wwandev = kzalloc(माप(*wwandev), GFP_KERNEL);
	अगर (!wwandev) अणु
		ida_मुक्त(&wwan_dev_ids, id);
		जाओ करोne_unlock;
	पूर्ण

	wwandev->dev.parent = parent;
	wwandev->dev.class = wwan_class;
	wwandev->dev.type = &wwan_dev_type;
	wwandev->id = id;
	dev_set_name(&wwandev->dev, "wwan%d", wwandev->id);

	err = device_रेजिस्टर(&wwandev->dev);
	अगर (err) अणु
		put_device(&wwandev->dev);
		wwandev = शून्य;
	पूर्ण

करोne_unlock:
	mutex_unlock(&wwan_रेजिस्टर_lock);

	वापस wwandev;
पूर्ण

अटल पूर्णांक is_wwan_child(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->class == wwan_class;
पूर्ण

अटल व्योम wwan_हटाओ_dev(काष्ठा wwan_device *wwandev)
अणु
	पूर्णांक ret;

	/* Prevent concurrent picking from wwan_create_dev */
	mutex_lock(&wwan_रेजिस्टर_lock);

	/* WWAN device is created and रेजिस्टरed (get+add) aदीर्घ with its first
	 * child port, and subsequent port registrations only grab a reference
	 * (get). The WWAN device must then be unरेजिस्टरed (del+put) aदीर्घ with
	 * its latest port, and reference simply dropped (put) otherwise.
	 */
	ret = device_क्रम_each_child(&wwandev->dev, शून्य, is_wwan_child);
	अगर (!ret)
		device_unरेजिस्टर(&wwandev->dev);
	अन्यथा
		put_device(&wwandev->dev);

	mutex_unlock(&wwan_रेजिस्टर_lock);
पूर्ण

/* ------- WWAN port management ------- */

अटल व्योम wwan_port_destroy(काष्ठा device *dev)
अणु
	काष्ठा wwan_port *port = to_wwan_port(dev);

	ida_मुक्त(&minors, MINOR(port->dev.devt));
	skb_queue_purge(&port->rxq);
	mutex_destroy(&port->ops_lock);
	kमुक्त(port);
पूर्ण

अटल स्थिर काष्ठा device_type wwan_port_dev_type = अणु
	.name = "wwan_port",
	.release = wwan_port_destroy,
पूर्ण;

अटल पूर्णांक wwan_port_minor_match(काष्ठा device *dev, स्थिर व्योम *minor)
अणु
	वापस (dev->type == &wwan_port_dev_type &&
		MINOR(dev->devt) == *(अचिन्हित पूर्णांक *)minor);
पूर्ण

अटल काष्ठा wwan_port *wwan_port_get_by_minor(अचिन्हित पूर्णांक minor)
अणु
	काष्ठा device *dev;

	dev = class_find_device(wwan_class, शून्य, &minor, wwan_port_minor_match);
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	वापस to_wwan_port(dev);
पूर्ण

/* Keep aligned with wwan_port_type क्रमागत */
अटल स्थिर अक्षर * स्थिर wwan_port_type_str[] = अणु
	"AT",
	"MBIM",
	"QMI",
	"QCDM",
	"FIREHOSE"
पूर्ण;

काष्ठा wwan_port *wwan_create_port(काष्ठा device *parent,
				   क्रमागत wwan_port_type type,
				   स्थिर काष्ठा wwan_port_ops *ops,
				   व्योम *drvdata)
अणु
	काष्ठा wwan_device *wwandev;
	काष्ठा wwan_port *port;
	पूर्णांक minor, err = -ENOMEM;

	अगर (type >= WWAN_PORT_MAX || !ops)
		वापस ERR_PTR(-EINVAL);

	/* A port is always a child of a WWAN device, retrieve (allocate or
	 * pick) the WWAN device based on the provided parent device.
	 */
	wwandev = wwan_create_dev(parent);
	अगर (IS_ERR(wwandev))
		वापस ERR_CAST(wwandev);

	/* A port is exposed as अक्षरacter device, get a minor */
	minor = ida_alloc_range(&minors, 0, WWAN_MAX_MINORS - 1, GFP_KERNEL);
	अगर (minor < 0)
		जाओ error_wwandev_हटाओ;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port) अणु
		ida_मुक्त(&minors, minor);
		जाओ error_wwandev_हटाओ;
	पूर्ण

	port->type = type;
	port->ops = ops;
	mutex_init(&port->ops_lock);
	skb_queue_head_init(&port->rxq);
	init_रुकोqueue_head(&port->रुकोqueue);

	port->dev.parent = &wwandev->dev;
	port->dev.class = wwan_class;
	port->dev.type = &wwan_port_dev_type;
	port->dev.devt = MKDEV(wwan_major, minor);
	dev_set_drvdata(&port->dev, drvdata);

	/* create unique name based on wwan device id, port index and type */
	dev_set_name(&port->dev, "wwan%up%u%s", wwandev->id,
		     atomic_inc_वापस(&wwandev->port_id),
		     wwan_port_type_str[port->type]);

	err = device_रेजिस्टर(&port->dev);
	अगर (err)
		जाओ error_put_device;

	वापस port;

error_put_device:
	put_device(&port->dev);
error_wwandev_हटाओ:
	wwan_हटाओ_dev(wwandev);

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(wwan_create_port);

व्योम wwan_हटाओ_port(काष्ठा wwan_port *port)
अणु
	काष्ठा wwan_device *wwandev = to_wwan_dev(port->dev.parent);

	mutex_lock(&port->ops_lock);
	अगर (port->start_count)
		port->ops->stop(port);
	port->ops = शून्य; /* Prevent any new port operations (e.g. from fops) */
	mutex_unlock(&port->ops_lock);

	wake_up_पूर्णांकerruptible(&port->रुकोqueue);

	skb_queue_purge(&port->rxq);
	dev_set_drvdata(&port->dev, शून्य);
	device_unरेजिस्टर(&port->dev);

	/* Release related wwan device */
	wwan_हटाओ_dev(wwandev);
पूर्ण
EXPORT_SYMBOL_GPL(wwan_हटाओ_port);

व्योम wwan_port_rx(काष्ठा wwan_port *port, काष्ठा sk_buff *skb)
अणु
	skb_queue_tail(&port->rxq, skb);
	wake_up_पूर्णांकerruptible(&port->रुकोqueue);
पूर्ण
EXPORT_SYMBOL_GPL(wwan_port_rx);

व्योम wwan_port_txon(काष्ठा wwan_port *port)
अणु
	clear_bit(WWAN_PORT_TX_OFF, &port->flags);
	wake_up_पूर्णांकerruptible(&port->रुकोqueue);
पूर्ण
EXPORT_SYMBOL_GPL(wwan_port_txon);

व्योम wwan_port_txoff(काष्ठा wwan_port *port)
अणु
	set_bit(WWAN_PORT_TX_OFF, &port->flags);
पूर्ण
EXPORT_SYMBOL_GPL(wwan_port_txoff);

व्योम *wwan_port_get_drvdata(काष्ठा wwan_port *port)
अणु
	वापस dev_get_drvdata(&port->dev);
पूर्ण
EXPORT_SYMBOL_GPL(wwan_port_get_drvdata);

अटल पूर्णांक wwan_port_op_start(काष्ठा wwan_port *port)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&port->ops_lock);
	अगर (!port->ops) अणु /* Port got unplugged */
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	/* If port is alपढ़ोy started, करोn't start again */
	अगर (!port->start_count)
		ret = port->ops->start(port);

	अगर (!ret)
		port->start_count++;

out_unlock:
	mutex_unlock(&port->ops_lock);

	वापस ret;
पूर्ण

अटल व्योम wwan_port_op_stop(काष्ठा wwan_port *port)
अणु
	mutex_lock(&port->ops_lock);
	port->start_count--;
	अगर (port->ops && !port->start_count)
		port->ops->stop(port);
	mutex_unlock(&port->ops_lock);
पूर्ण

अटल पूर्णांक wwan_port_op_tx(काष्ठा wwan_port *port, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	mutex_lock(&port->ops_lock);
	अगर (!port->ops) अणु /* Port got unplugged */
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	ret = port->ops->tx(port, skb);

out_unlock:
	mutex_unlock(&port->ops_lock);

	वापस ret;
पूर्ण

अटल bool is_पढ़ो_blocked(काष्ठा wwan_port *port)
अणु
	वापस skb_queue_empty(&port->rxq) && port->ops;
पूर्ण

अटल bool is_ग_लिखो_blocked(काष्ठा wwan_port *port)
अणु
	वापस test_bit(WWAN_PORT_TX_OFF, &port->flags) && port->ops;
पूर्ण

अटल पूर्णांक wwan_रुको_rx(काष्ठा wwan_port *port, bool nonblock)
अणु
	अगर (!is_पढ़ो_blocked(port))
		वापस 0;

	अगर (nonblock)
		वापस -EAGAIN;

	अगर (रुको_event_पूर्णांकerruptible(port->रुकोqueue, !is_पढ़ो_blocked(port)))
		वापस -ERESTARTSYS;

	वापस 0;
पूर्ण

अटल पूर्णांक wwan_रुको_tx(काष्ठा wwan_port *port, bool nonblock)
अणु
	अगर (!is_ग_लिखो_blocked(port))
		वापस 0;

	अगर (nonblock)
		वापस -EAGAIN;

	अगर (रुको_event_पूर्णांकerruptible(port->रुकोqueue, !is_ग_लिखो_blocked(port)))
		वापस -ERESTARTSYS;

	वापस 0;
पूर्ण

अटल पूर्णांक wwan_port_fops_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा wwan_port *port;
	पूर्णांक err = 0;

	port = wwan_port_get_by_minor(iminor(inode));
	अगर (IS_ERR(port))
		वापस PTR_ERR(port);

	file->निजी_data = port;
	stream_खोलो(inode, file);

	err = wwan_port_op_start(port);
	अगर (err)
		put_device(&port->dev);

	वापस err;
पूर्ण

अटल पूर्णांक wwan_port_fops_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा wwan_port *port = filp->निजी_data;

	wwan_port_op_stop(port);
	put_device(&port->dev);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार wwan_port_fops_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wwan_port *port = filp->निजी_data;
	काष्ठा sk_buff *skb;
	माप_प्रकार copied;
	पूर्णांक ret;

	ret = wwan_रुको_rx(port, !!(filp->f_flags & O_NONBLOCK));
	अगर (ret)
		वापस ret;

	skb = skb_dequeue(&port->rxq);
	अगर (!skb)
		वापस -EIO;

	copied = min_t(माप_प्रकार, count, skb->len);
	अगर (copy_to_user(buf, skb->data, copied)) अणु
		kमुक्त_skb(skb);
		वापस -EFAULT;
	पूर्ण
	skb_pull(skb, copied);

	/* skb is not fully consumed, keep it in the queue */
	अगर (skb->len)
		skb_queue_head(&port->rxq, skb);
	अन्यथा
		consume_skb(skb);

	वापस copied;
पूर्ण

अटल sमाप_प्रकार wwan_port_fops_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा wwan_port *port = filp->निजी_data;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	ret = wwan_रुको_tx(port, !!(filp->f_flags & O_NONBLOCK));
	अगर (ret)
		वापस ret;

	skb = alloc_skb(count, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	अगर (copy_from_user(skb_put(skb, count), buf, count)) अणु
		kमुक्त_skb(skb);
		वापस -EFAULT;
	पूर्ण

	ret = wwan_port_op_tx(port, skb);
	अगर (ret) अणु
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण

अटल __poll_t wwan_port_fops_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा wwan_port *port = filp->निजी_data;
	__poll_t mask = 0;

	poll_रुको(filp, &port->रुकोqueue, रुको);

	अगर (!is_ग_लिखो_blocked(port))
		mask |= EPOLLOUT | EPOLLWRNORM;
	अगर (!is_पढ़ो_blocked(port))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (!port->ops)
		mask |= EPOLLHUP | EPOLLERR;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations wwan_port_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = wwan_port_fops_खोलो,
	.release = wwan_port_fops_release,
	.पढ़ो = wwan_port_fops_पढ़ो,
	.ग_लिखो = wwan_port_fops_ग_लिखो,
	.poll = wwan_port_fops_poll,
	.llseek = noop_llseek,
पूर्ण;

अटल पूर्णांक __init wwan_init(व्योम)
अणु
	wwan_class = class_create(THIS_MODULE, "wwan");
	अगर (IS_ERR(wwan_class))
		वापस PTR_ERR(wwan_class);

	/* chrdev used क्रम wwan ports */
	wwan_major = रेजिस्टर_chrdev(0, "wwan_port", &wwan_port_fops);
	अगर (wwan_major < 0) अणु
		class_destroy(wwan_class);
		वापस wwan_major;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास wwan_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev(wwan_major, "wwan_port");
	class_destroy(wwan_class);
पूर्ण

module_init(wwan_init);
module_निकास(wwan_निकास);

MODULE_AUTHOR("Loic Poulain <loic.poulain@linaro.org>");
MODULE_DESCRIPTION("WWAN core");
MODULE_LICENSE("GPL v2");
