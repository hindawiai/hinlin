<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006, 2007, 2009 Rusty Russell, IBM Corporation
 * Copyright (C) 2009, 2010, 2011 Red Hat, Inc.
 * Copyright (C) 2009, 2010, 2011 Amit Shah <amit.shah@redhat.com>
 */
#समावेश <linux/cdev.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/fs.h>
#समावेश <linux/splice.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_console.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश "../tty/hvc/hvc_console.h"

#घोषणा is_rproc_enabled IS_ENABLED(CONFIG_REMOTEPROC)

/*
 * This is a global काष्ठा क्रम storing common data क्रम all the devices
 * this driver handles.
 *
 * Mainly, it has a linked list क्रम all the consoles in one place so
 * that callbacks from hvc क्रम get_अक्षरs(), put_अक्षरs() work properly
 * across multiple devices and multiple ports per device.
 */
काष्ठा ports_driver_data अणु
	/* Used क्रम रेजिस्टरing अक्षरdevs */
	काष्ठा class *class;

	/* Used क्रम exporting per-port inक्रमmation to debugfs */
	काष्ठा dentry *debugfs_dir;

	/* List of all the devices we're handling */
	काष्ठा list_head portdevs;

	/*
	 * This is used to keep track of the number of hvc consoles
	 * spawned by this driver.  This number is given as the first
	 * argument to hvc_alloc().  To correctly map an initial
	 * console spawned via hvc_instantiate to the console being
	 * hooked up via hvc_alloc, we need to pass the same vtermno.
	 *
	 * We also just assume the first console being initialised was
	 * the first one that got used as the initial console.
	 */
	अचिन्हित पूर्णांक next_vtermno;

	/* All the console devices handled by this driver */
	काष्ठा list_head consoles;
पूर्ण;
अटल काष्ठा ports_driver_data pdrvdata = अणु .next_vtermno = 1पूर्ण;

अटल DEFINE_SPINLOCK(pdrvdata_lock);
अटल DECLARE_COMPLETION(early_console_added);

/* This काष्ठा holds inक्रमmation that's relevant only क्रम console ports */
काष्ठा console अणु
	/* We'll place all consoles in a list in the pdrvdata काष्ठा */
	काष्ठा list_head list;

	/* The hvc device associated with this console port */
	काष्ठा hvc_काष्ठा *hvc;

	/* The size of the console */
	काष्ठा winsize ws;

	/*
	 * This number identअगरies the number that we used to रेजिस्टर
	 * with hvc in hvc_instantiate() and hvc_alloc(); this is the
	 * number passed on by the hvc callbacks to us to
	 * dअगरferentiate between the other console ports handled by
	 * this driver
	 */
	u32 vtermno;
पूर्ण;

काष्ठा port_buffer अणु
	अक्षर *buf;

	/* size of the buffer in *buf above */
	माप_प्रकार size;

	/* used length of the buffer */
	माप_प्रकार len;
	/* offset in the buf from which to consume data */
	माप_प्रकार offset;

	/* DMA address of buffer */
	dma_addr_t dma;

	/* Device we got DMA memory from */
	काष्ठा device *dev;

	/* List of pending dma buffers to मुक्त */
	काष्ठा list_head list;

	/* If sgpages == 0 then buf is used */
	अचिन्हित पूर्णांक sgpages;

	/* sg is used अगर spages > 0. sg must be the last in is काष्ठा */
	काष्ठा scatterlist sg[];
पूर्ण;

/*
 * This is a per-device काष्ठा that stores data common to all the
 * ports क्रम that device (vdev->priv).
 */
काष्ठा ports_device अणु
	/* Next portdev in the list, head is in the pdrvdata काष्ठा */
	काष्ठा list_head list;

	/*
	 * Workqueue handlers where we process deferred work after
	 * notअगरication
	 */
	काष्ठा work_काष्ठा control_work;
	काष्ठा work_काष्ठा config_work;

	काष्ठा list_head ports;

	/* To protect the list of ports */
	spinlock_t ports_lock;

	/* To protect the vq operations क्रम the control channel */
	spinlock_t c_ivq_lock;
	spinlock_t c_ovq_lock;

	/* max. number of ports this device can hold */
	u32 max_nr_ports;

	/* The virtio device we're associated with */
	काष्ठा virtio_device *vdev;

	/*
	 * A couple of virtqueues क्रम the control channel: one क्रम
	 * guest->host transfers, one क्रम host->guest transfers
	 */
	काष्ठा virtqueue *c_ivq, *c_ovq;

	/*
	 * A control packet buffer क्रम guest->host requests, रक्षित
	 * by c_ovq_lock.
	 */
	काष्ठा virtio_console_control cpkt;

	/* Array of per-port IO virtqueues */
	काष्ठा virtqueue **in_vqs, **out_vqs;

	/* Major number क्रम this device.  Ports will be created as minors. */
	पूर्णांक chr_major;
पूर्ण;

काष्ठा port_stats अणु
	अचिन्हित दीर्घ bytes_sent, bytes_received, bytes_discarded;
पूर्ण;

/* This काष्ठा holds the per-port data */
काष्ठा port अणु
	/* Next port in the list, head is in the ports_device */
	काष्ठा list_head list;

	/* Poपूर्णांकer to the parent virtio_console device */
	काष्ठा ports_device *portdev;

	/* The current buffer from which data has to be fed to पढ़ोers */
	काष्ठा port_buffer *inbuf;

	/*
	 * To protect the operations on the in_vq associated with this
	 * port.  Has to be a spinlock because it can be called from
	 * पूर्णांकerrupt context (get_अक्षर()).
	 */
	spinlock_t inbuf_lock;

	/* Protect the operations on the out_vq. */
	spinlock_t outvq_lock;

	/* The IO vqs क्रम this port */
	काष्ठा virtqueue *in_vq, *out_vq;

	/* File in the debugfs directory that exposes this port's inक्रमmation */
	काष्ठा dentry *debugfs_file;

	/*
	 * Keep count of the bytes sent, received and discarded क्रम
	 * this port क्रम accounting and debugging purposes.  These
	 * counts are not reset across port खोलो / बंद events.
	 */
	काष्ठा port_stats stats;

	/*
	 * The entries in this काष्ठा will be valid अगर this port is
	 * hooked up to an hvc console
	 */
	काष्ठा console cons;

	/* Each port associates with a separate अक्षर device */
	काष्ठा cdev *cdev;
	काष्ठा device *dev;

	/* Reference-counting to handle port hot-unplugs and file operations */
	काष्ठा kref kref;

	/* A रुकोqueue क्रम poll() or blocking पढ़ो operations */
	रुको_queue_head_t रुकोqueue;

	/* The 'name' of the port that we expose via sysfs properties */
	अक्षर *name;

	/* We can notअगरy apps of host connect / disconnect events via SIGIO */
	काष्ठा fasync_काष्ठा *async_queue;

	/* The 'id' to identअगरy the port with the Host */
	u32 id;

	bool outvq_full;

	/* Is the host device खोलो */
	bool host_connected;

	/* We should allow only one process to खोलो a port */
	bool guest_connected;
पूर्ण;

/* This is the very early arch-specअगरied put अक्षरs function. */
अटल पूर्णांक (*early_put_अक्षरs)(u32, स्थिर अक्षर *, पूर्णांक);

अटल काष्ठा port *find_port_by_vtermno(u32 vtermno)
अणु
	काष्ठा port *port;
	काष्ठा console *cons;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdrvdata_lock, flags);
	list_क्रम_each_entry(cons, &pdrvdata.consoles, list) अणु
		अगर (cons->vtermno == vtermno) अणु
			port = container_of(cons, काष्ठा port, cons);
			जाओ out;
		पूर्ण
	पूर्ण
	port = शून्य;
out:
	spin_unlock_irqrestore(&pdrvdata_lock, flags);
	वापस port;
पूर्ण

अटल काष्ठा port *find_port_by_devt_in_portdev(काष्ठा ports_device *portdev,
						 dev_t dev)
अणु
	काष्ठा port *port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&portdev->ports_lock, flags);
	list_क्रम_each_entry(port, &portdev->ports, list) अणु
		अगर (port->cdev->dev == dev) अणु
			kref_get(&port->kref);
			जाओ out;
		पूर्ण
	पूर्ण
	port = शून्य;
out:
	spin_unlock_irqrestore(&portdev->ports_lock, flags);

	वापस port;
पूर्ण

अटल काष्ठा port *find_port_by_devt(dev_t dev)
अणु
	काष्ठा ports_device *portdev;
	काष्ठा port *port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdrvdata_lock, flags);
	list_क्रम_each_entry(portdev, &pdrvdata.portdevs, list) अणु
		port = find_port_by_devt_in_portdev(portdev, dev);
		अगर (port)
			जाओ out;
	पूर्ण
	port = शून्य;
out:
	spin_unlock_irqrestore(&pdrvdata_lock, flags);
	वापस port;
पूर्ण

अटल काष्ठा port *find_port_by_id(काष्ठा ports_device *portdev, u32 id)
अणु
	काष्ठा port *port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&portdev->ports_lock, flags);
	list_क्रम_each_entry(port, &portdev->ports, list)
		अगर (port->id == id)
			जाओ out;
	port = शून्य;
out:
	spin_unlock_irqrestore(&portdev->ports_lock, flags);

	वापस port;
पूर्ण

अटल काष्ठा port *find_port_by_vq(काष्ठा ports_device *portdev,
				    काष्ठा virtqueue *vq)
अणु
	काष्ठा port *port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&portdev->ports_lock, flags);
	list_क्रम_each_entry(port, &portdev->ports, list)
		अगर (port->in_vq == vq || port->out_vq == vq)
			जाओ out;
	port = शून्य;
out:
	spin_unlock_irqrestore(&portdev->ports_lock, flags);
	वापस port;
पूर्ण

अटल bool is_console_port(काष्ठा port *port)
अणु
	अगर (port->cons.hvc)
		वापस true;
	वापस false;
पूर्ण

अटल bool is_rproc_serial(स्थिर काष्ठा virtio_device *vdev)
अणु
	वापस is_rproc_enabled && vdev->id.device == VIRTIO_ID_RPROC_SERIAL;
पूर्ण

अटल अंतरभूत bool use_multiport(काष्ठा ports_device *portdev)
अणु
	/*
	 * This condition can be true when put_अक्षरs is called from
	 * early_init
	 */
	अगर (!portdev->vdev)
		वापस false;
	वापस __virtio_test_bit(portdev->vdev, VIRTIO_CONSOLE_F_MULTIPORT);
पूर्ण

अटल DEFINE_SPINLOCK(dma_bufs_lock);
अटल LIST_HEAD(pending_मुक्त_dma_bufs);

अटल व्योम मुक्त_buf(काष्ठा port_buffer *buf, bool can_sleep)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < buf->sgpages; i++) अणु
		काष्ठा page *page = sg_page(&buf->sg[i]);
		अगर (!page)
			अवरोध;
		put_page(page);
	पूर्ण

	अगर (!buf->dev) अणु
		kमुक्त(buf->buf);
	पूर्ण अन्यथा अगर (is_rproc_enabled) अणु
		अचिन्हित दीर्घ flags;

		/* dma_मुक्त_coherent requires पूर्णांकerrupts to be enabled. */
		अगर (!can_sleep) अणु
			/* queue up dma-buffers to be मुक्तd later */
			spin_lock_irqsave(&dma_bufs_lock, flags);
			list_add_tail(&buf->list, &pending_मुक्त_dma_bufs);
			spin_unlock_irqrestore(&dma_bufs_lock, flags);
			वापस;
		पूर्ण
		dma_मुक्त_coherent(buf->dev, buf->size, buf->buf, buf->dma);

		/* Release device refcnt and allow it to be मुक्तd */
		put_device(buf->dev);
	पूर्ण

	kमुक्त(buf);
पूर्ण

अटल व्योम reclaim_dma_bufs(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा port_buffer *buf, *पंचांगp;
	LIST_HEAD(पंचांगp_list);

	अगर (list_empty(&pending_मुक्त_dma_bufs))
		वापस;

	/* Create a copy of the pending_मुक्त_dma_bufs जबतक holding the lock */
	spin_lock_irqsave(&dma_bufs_lock, flags);
	list_cut_position(&पंचांगp_list, &pending_मुक्त_dma_bufs,
			  pending_मुक्त_dma_bufs.prev);
	spin_unlock_irqrestore(&dma_bufs_lock, flags);

	/* Release the dma buffers, without irqs enabled */
	list_क्रम_each_entry_safe(buf, पंचांगp, &पंचांगp_list, list) अणु
		list_del(&buf->list);
		मुक्त_buf(buf, true);
	पूर्ण
पूर्ण

अटल काष्ठा port_buffer *alloc_buf(काष्ठा virtio_device *vdev, माप_प्रकार buf_size,
				     पूर्णांक pages)
अणु
	काष्ठा port_buffer *buf;

	reclaim_dma_bufs();

	/*
	 * Allocate buffer and the sg list. The sg list array is allocated
	 * directly after the port_buffer काष्ठा.
	 */
	buf = kदो_स्मृति(काष्ठा_size(buf, sg, pages), GFP_KERNEL);
	अगर (!buf)
		जाओ fail;

	buf->sgpages = pages;
	अगर (pages > 0) अणु
		buf->dev = शून्य;
		buf->buf = शून्य;
		वापस buf;
	पूर्ण

	अगर (is_rproc_serial(vdev)) अणु
		/*
		 * Allocate DMA memory from ancestor. When a virtio
		 * device is created by remoteproc, the DMA memory is
		 * associated with the parent device:
		 * virtioY => remoteprocX#vdevYbuffer.
		 */
		buf->dev = vdev->dev.parent;
		अगर (!buf->dev)
			जाओ मुक्त_buf;

		/* Increase device refcnt to aव्योम मुक्तing it */
		get_device(buf->dev);
		buf->buf = dma_alloc_coherent(buf->dev, buf_size, &buf->dma,
					      GFP_KERNEL);
	पूर्ण अन्यथा अणु
		buf->dev = शून्य;
		buf->buf = kदो_स्मृति(buf_size, GFP_KERNEL);
	पूर्ण

	अगर (!buf->buf)
		जाओ मुक्त_buf;
	buf->len = 0;
	buf->offset = 0;
	buf->size = buf_size;
	वापस buf;

मुक्त_buf:
	kमुक्त(buf);
fail:
	वापस शून्य;
पूर्ण

/* Callers should take appropriate locks */
अटल काष्ठा port_buffer *get_inbuf(काष्ठा port *port)
अणु
	काष्ठा port_buffer *buf;
	अचिन्हित पूर्णांक len;

	अगर (port->inbuf)
		वापस port->inbuf;

	buf = virtqueue_get_buf(port->in_vq, &len);
	अगर (buf) अणु
		buf->len = len;
		buf->offset = 0;
		port->stats.bytes_received += len;
	पूर्ण
	वापस buf;
पूर्ण

/*
 * Create a scatter-gather list representing our input buffer and put
 * it in the queue.
 *
 * Callers should take appropriate locks.
 */
अटल पूर्णांक add_inbuf(काष्ठा virtqueue *vq, काष्ठा port_buffer *buf)
अणु
	काष्ठा scatterlist sg[1];
	पूर्णांक ret;

	sg_init_one(sg, buf->buf, buf->size);

	ret = virtqueue_add_inbuf(vq, sg, 1, buf, GFP_ATOMIC);
	virtqueue_kick(vq);
	अगर (!ret)
		ret = vq->num_मुक्त;
	वापस ret;
पूर्ण

/* Discard any unपढ़ो data this port has. Callers lockers. */
अटल व्योम discard_port_data(काष्ठा port *port)
अणु
	काष्ठा port_buffer *buf;
	अचिन्हित पूर्णांक err;

	अगर (!port->portdev) अणु
		/* Device has been unplugged.  vqs are alपढ़ोy gone. */
		वापस;
	पूर्ण
	buf = get_inbuf(port);

	err = 0;
	जबतक (buf) अणु
		port->stats.bytes_discarded += buf->len - buf->offset;
		अगर (add_inbuf(port->in_vq, buf) < 0) अणु
			err++;
			मुक्त_buf(buf, false);
		पूर्ण
		port->inbuf = शून्य;
		buf = get_inbuf(port);
	पूर्ण
	अगर (err)
		dev_warn(port->dev, "Errors adding %d buffers back to vq\n",
			 err);
पूर्ण

अटल bool port_has_data(काष्ठा port *port)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	ret = false;
	spin_lock_irqsave(&port->inbuf_lock, flags);
	port->inbuf = get_inbuf(port);
	अगर (port->inbuf)
		ret = true;

	spin_unlock_irqrestore(&port->inbuf_lock, flags);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार __send_control_msg(काष्ठा ports_device *portdev, u32 port_id,
				  अचिन्हित पूर्णांक event, अचिन्हित पूर्णांक value)
अणु
	काष्ठा scatterlist sg[1];
	काष्ठा virtqueue *vq;
	अचिन्हित पूर्णांक len;

	अगर (!use_multiport(portdev))
		वापस 0;

	vq = portdev->c_ovq;

	spin_lock(&portdev->c_ovq_lock);

	portdev->cpkt.id = cpu_to_virtio32(portdev->vdev, port_id);
	portdev->cpkt.event = cpu_to_virtio16(portdev->vdev, event);
	portdev->cpkt.value = cpu_to_virtio16(portdev->vdev, value);

	sg_init_one(sg, &portdev->cpkt, माप(काष्ठा virtio_console_control));

	अगर (virtqueue_add_outbuf(vq, sg, 1, &portdev->cpkt, GFP_ATOMIC) == 0) अणु
		virtqueue_kick(vq);
		जबतक (!virtqueue_get_buf(vq, &len)
			&& !virtqueue_is_broken(vq))
			cpu_relax();
	पूर्ण

	spin_unlock(&portdev->c_ovq_lock);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार send_control_msg(काष्ठा port *port, अचिन्हित पूर्णांक event,
				अचिन्हित पूर्णांक value)
अणु
	/* Did the port get unplugged beक्रमe userspace बंदd it? */
	अगर (port->portdev)
		वापस __send_control_msg(port->portdev, port->id, event, value);
	वापस 0;
पूर्ण


/* Callers must take the port->outvq_lock */
अटल व्योम reclaim_consumed_buffers(काष्ठा port *port)
अणु
	काष्ठा port_buffer *buf;
	अचिन्हित पूर्णांक len;

	अगर (!port->portdev) अणु
		/* Device has been unplugged.  vqs are alपढ़ोy gone. */
		वापस;
	पूर्ण
	जबतक ((buf = virtqueue_get_buf(port->out_vq, &len))) अणु
		मुक्त_buf(buf, false);
		port->outvq_full = false;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार __send_to_port(काष्ठा port *port, काष्ठा scatterlist *sg,
			      पूर्णांक nents, माप_प्रकार in_count,
			      व्योम *data, bool nonblock)
अणु
	काष्ठा virtqueue *out_vq;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;

	out_vq = port->out_vq;

	spin_lock_irqsave(&port->outvq_lock, flags);

	reclaim_consumed_buffers(port);

	err = virtqueue_add_outbuf(out_vq, sg, nents, data, GFP_ATOMIC);

	/* Tell Host to go! */
	virtqueue_kick(out_vq);

	अगर (err) अणु
		in_count = 0;
		जाओ करोne;
	पूर्ण

	अगर (out_vq->num_मुक्त == 0)
		port->outvq_full = true;

	अगर (nonblock)
		जाओ करोne;

	/*
	 * Wait till the host acknowledges it pushed out the data we
	 * sent.  This is करोne क्रम data from the hvc_console; the tty
	 * operations are perक्रमmed with spinlocks held so we can't
	 * sleep here.  An alternative would be to copy the data to a
	 * buffer and relax the spinning requirement.  The करोwnside is
	 * we need to kदो_स्मृति a GFP_ATOMIC buffer each समय the
	 * console driver ग_लिखोs something out.
	 */
	जबतक (!virtqueue_get_buf(out_vq, &len)
		&& !virtqueue_is_broken(out_vq))
		cpu_relax();
करोne:
	spin_unlock_irqrestore(&port->outvq_lock, flags);

	port->stats.bytes_sent += in_count;
	/*
	 * We're expected to वापस the amount of data we wrote -- all
	 * of it
	 */
	वापस in_count;
पूर्ण

/*
 * Give out the data that's requested from the buffer that we have
 * queued up.
 */
अटल sमाप_प्रकार fill_पढ़ोbuf(काष्ठा port *port, अक्षर __user *out_buf,
			    माप_प्रकार out_count, bool to_user)
अणु
	काष्ठा port_buffer *buf;
	अचिन्हित दीर्घ flags;

	अगर (!out_count || !port_has_data(port))
		वापस 0;

	buf = port->inbuf;
	out_count = min(out_count, buf->len - buf->offset);

	अगर (to_user) अणु
		sमाप_प्रकार ret;

		ret = copy_to_user(out_buf, buf->buf + buf->offset, out_count);
		अगर (ret)
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		स_नकल((__क्रमce अक्षर *)out_buf, buf->buf + buf->offset,
		       out_count);
	पूर्ण

	buf->offset += out_count;

	अगर (buf->offset == buf->len) अणु
		/*
		 * We're करोne using all the data in this buffer.
		 * Re-queue so that the Host can send us more data.
		 */
		spin_lock_irqsave(&port->inbuf_lock, flags);
		port->inbuf = शून्य;

		अगर (add_inbuf(port->in_vq, buf) < 0)
			dev_warn(port->dev, "failed add_buf\n");

		spin_unlock_irqrestore(&port->inbuf_lock, flags);
	पूर्ण
	/* Return the number of bytes actually copied */
	वापस out_count;
पूर्ण

/* The condition that must be true क्रम polling to end */
अटल bool will_पढ़ो_block(काष्ठा port *port)
अणु
	अगर (!port->guest_connected) अणु
		/* Port got hot-unplugged. Let's निकास. */
		वापस false;
	पूर्ण
	वापस !port_has_data(port) && port->host_connected;
पूर्ण

अटल bool will_ग_लिखो_block(काष्ठा port *port)
अणु
	bool ret;

	अगर (!port->guest_connected) अणु
		/* Port got hot-unplugged. Let's निकास. */
		वापस false;
	पूर्ण
	अगर (!port->host_connected)
		वापस true;

	spin_lock_irq(&port->outvq_lock);
	/*
	 * Check अगर the Host has consumed any buffers since we last
	 * sent data (this is only applicable क्रम nonblocking ports).
	 */
	reclaim_consumed_buffers(port);
	ret = port->outvq_full;
	spin_unlock_irq(&port->outvq_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार port_fops_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
			      माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा port *port;
	sमाप_प्रकार ret;

	port = filp->निजी_data;

	/* Port is hot-unplugged. */
	अगर (!port->guest_connected)
		वापस -ENODEV;

	अगर (!port_has_data(port)) अणु
		/*
		 * If nothing's connected on the host just वापस 0 in
		 * हाल of list_empty; this tells the userspace app
		 * that there's no connection
		 */
		अगर (!port->host_connected)
			वापस 0;
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		ret = रुको_event_मुक्तzable(port->रुकोqueue,
					   !will_पढ़ो_block(port));
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	/* Port got hot-unplugged जबतक we were रुकोing above. */
	अगर (!port->guest_connected)
		वापस -ENODEV;
	/*
	 * We could've received a disconnection message जबतक we were
	 * रुकोing क्रम more data.
	 *
	 * This check is not clubbed in the अगर() statement above as we
	 * might receive some data as well as the host could get
	 * disconnected after we got woken up from our रुको.  So we
	 * really want to give off whatever data we have and only then
	 * check क्रम host_connected.
	 */
	अगर (!port_has_data(port) && !port->host_connected)
		वापस 0;

	वापस fill_पढ़ोbuf(port, ubuf, count, true);
पूर्ण

अटल पूर्णांक रुको_port_writable(काष्ठा port *port, bool nonblock)
अणु
	पूर्णांक ret;

	अगर (will_ग_लिखो_block(port)) अणु
		अगर (nonblock)
			वापस -EAGAIN;

		ret = रुको_event_मुक्तzable(port->रुकोqueue,
					   !will_ग_लिखो_block(port));
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	/* Port got hot-unplugged. */
	अगर (!port->guest_connected)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार port_fops_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
			       माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा port *port;
	काष्ठा port_buffer *buf;
	sमाप_प्रकार ret;
	bool nonblock;
	काष्ठा scatterlist sg[1];

	/* Userspace could be out to fool us */
	अगर (!count)
		वापस 0;

	port = filp->निजी_data;

	nonblock = filp->f_flags & O_NONBLOCK;

	ret = रुको_port_writable(port, nonblock);
	अगर (ret < 0)
		वापस ret;

	count = min((माप_प्रकार)(32 * 1024), count);

	buf = alloc_buf(port->portdev->vdev, count, 0);
	अगर (!buf)
		वापस -ENOMEM;

	ret = copy_from_user(buf->buf, ubuf, count);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ मुक्त_buf;
	पूर्ण

	/*
	 * We now ask send_buf() to not spin क्रम generic ports -- we
	 * can re-use the same code path that non-blocking file
	 * descriptors take क्रम blocking file descriptors since the
	 * रुको is alपढ़ोy करोne and we're certain the ग_लिखो will go
	 * through to the host.
	 */
	nonblock = true;
	sg_init_one(sg, buf->buf, count);
	ret = __send_to_port(port, sg, 1, count, buf, nonblock);

	अगर (nonblock && ret > 0)
		जाओ out;

मुक्त_buf:
	मुक्त_buf(buf, true);
out:
	वापस ret;
पूर्ण

काष्ठा sg_list अणु
	अचिन्हित पूर्णांक n;
	अचिन्हित पूर्णांक size;
	माप_प्रकार len;
	काष्ठा scatterlist *sg;
पूर्ण;

अटल पूर्णांक pipe_to_sg(काष्ठा pipe_inode_info *pipe, काष्ठा pipe_buffer *buf,
			काष्ठा splice_desc *sd)
अणु
	काष्ठा sg_list *sgl = sd->u.data;
	अचिन्हित पूर्णांक offset, len;

	अगर (sgl->n == sgl->size)
		वापस 0;

	/* Try lock this page */
	अगर (pipe_buf_try_steal(pipe, buf)) अणु
		/* Get reference and unlock page क्रम moving */
		get_page(buf->page);
		unlock_page(buf->page);

		len = min(buf->len, sd->len);
		sg_set_page(&(sgl->sg[sgl->n]), buf->page, len, buf->offset);
	पूर्ण अन्यथा अणु
		/* Failback to copying a page */
		काष्ठा page *page = alloc_page(GFP_KERNEL);
		अक्षर *src;

		अगर (!page)
			वापस -ENOMEM;

		offset = sd->pos & ~PAGE_MASK;

		len = sd->len;
		अगर (len + offset > PAGE_SIZE)
			len = PAGE_SIZE - offset;

		src = kmap_atomic(buf->page);
		स_नकल(page_address(page) + offset, src + buf->offset, len);
		kunmap_atomic(src);

		sg_set_page(&(sgl->sg[sgl->n]), page, len, offset);
	पूर्ण
	sgl->n++;
	sgl->len += len;

	वापस len;
पूर्ण

/* Faster zero-copy ग_लिखो by splicing */
अटल sमाप_प्रकार port_fops_splice_ग_लिखो(काष्ठा pipe_inode_info *pipe,
				      काष्ठा file *filp, loff_t *ppos,
				      माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा port *port = filp->निजी_data;
	काष्ठा sg_list sgl;
	sमाप_प्रकार ret;
	काष्ठा port_buffer *buf;
	काष्ठा splice_desc sd = अणु
		.total_len = len,
		.flags = flags,
		.pos = *ppos,
		.u.data = &sgl,
	पूर्ण;
	अचिन्हित पूर्णांक occupancy;

	/*
	 * Rproc_serial करोes not yet support splice. To support splice
	 * pipe_to_sg() must allocate dma-buffers and copy content from
	 * regular pages to dma pages. And alloc_buf and मुक्त_buf must
	 * support allocating and मुक्तing such a list of dma-buffers.
	 */
	अगर (is_rproc_serial(port->out_vq->vdev))
		वापस -EINVAL;

	pipe_lock(pipe);
	ret = 0;
	अगर (pipe_empty(pipe->head, pipe->tail))
		जाओ error_out;

	ret = रुको_port_writable(port, filp->f_flags & O_NONBLOCK);
	अगर (ret < 0)
		जाओ error_out;

	occupancy = pipe_occupancy(pipe->head, pipe->tail);
	buf = alloc_buf(port->portdev->vdev, 0, occupancy);

	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ error_out;
	पूर्ण

	sgl.n = 0;
	sgl.len = 0;
	sgl.size = occupancy;
	sgl.sg = buf->sg;
	sg_init_table(sgl.sg, sgl.size);
	ret = __splice_from_pipe(pipe, &sd, pipe_to_sg);
	pipe_unlock(pipe);
	अगर (likely(ret > 0))
		ret = __send_to_port(port, buf->sg, sgl.n, sgl.len, buf, true);

	अगर (unlikely(ret <= 0))
		मुक्त_buf(buf, true);
	वापस ret;

error_out:
	pipe_unlock(pipe);
	वापस ret;
पूर्ण

अटल __poll_t port_fops_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा port *port;
	__poll_t ret;

	port = filp->निजी_data;
	poll_रुको(filp, &port->रुकोqueue, रुको);

	अगर (!port->guest_connected) अणु
		/* Port got unplugged */
		वापस EPOLLHUP;
	पूर्ण
	ret = 0;
	अगर (!will_पढ़ो_block(port))
		ret |= EPOLLIN | EPOLLRDNORM;
	अगर (!will_ग_लिखो_block(port))
		ret |= EPOLLOUT;
	अगर (!port->host_connected)
		ret |= EPOLLHUP;

	वापस ret;
पूर्ण

अटल व्योम हटाओ_port(काष्ठा kref *kref);

अटल पूर्णांक port_fops_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा port *port;

	port = filp->निजी_data;

	/* Notअगरy host of port being बंदd */
	send_control_msg(port, VIRTIO_CONSOLE_PORT_OPEN, 0);

	spin_lock_irq(&port->inbuf_lock);
	port->guest_connected = false;

	discard_port_data(port);

	spin_unlock_irq(&port->inbuf_lock);

	spin_lock_irq(&port->outvq_lock);
	reclaim_consumed_buffers(port);
	spin_unlock_irq(&port->outvq_lock);

	reclaim_dma_bufs();
	/*
	 * Locks aren't necessary here as a port can't be खोलोed after
	 * unplug, and अगर a port isn't unplugged, a kref would alपढ़ोy
	 * exist क्रम the port.  Plus, taking ports_lock here would
	 * create a dependency on other locks taken by functions
	 * inside हटाओ_port अगर we're the last holder of the port,
	 * creating many problems.
	 */
	kref_put(&port->kref, हटाओ_port);

	वापस 0;
पूर्ण

अटल पूर्णांक port_fops_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cdev *cdev = inode->i_cdev;
	काष्ठा port *port;
	पूर्णांक ret;

	/* We get the port with a kref here */
	port = find_port_by_devt(cdev->dev);
	अगर (!port) अणु
		/* Port was unplugged beक्रमe we could proceed */
		वापस -ENXIO;
	पूर्ण
	filp->निजी_data = port;

	/*
	 * Don't allow opening of console port devices -- that's करोne
	 * via /dev/hvc
	 */
	अगर (is_console_port(port)) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	/* Allow only one process to खोलो a particular port at a समय */
	spin_lock_irq(&port->inbuf_lock);
	अगर (port->guest_connected) अणु
		spin_unlock_irq(&port->inbuf_lock);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	port->guest_connected = true;
	spin_unlock_irq(&port->inbuf_lock);

	spin_lock_irq(&port->outvq_lock);
	/*
	 * There might be a chance that we missed reclaiming a few
	 * buffers in the winकरोw of the port getting previously बंदd
	 * and खोलोing now.
	 */
	reclaim_consumed_buffers(port);
	spin_unlock_irq(&port->outvq_lock);

	nonseekable_खोलो(inode, filp);

	/* Notअगरy host of port being खोलोed */
	send_control_msg(filp->निजी_data, VIRTIO_CONSOLE_PORT_OPEN, 1);

	वापस 0;
out:
	kref_put(&port->kref, हटाओ_port);
	वापस ret;
पूर्ण

अटल पूर्णांक port_fops_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक mode)
अणु
	काष्ठा port *port;

	port = filp->निजी_data;
	वापस fasync_helper(fd, filp, mode, &port->async_queue);
पूर्ण

/*
 * The file operations that we support: programs in the guest can खोलो
 * a console device, पढ़ो from it, ग_लिखो to it, poll क्रम data and
 * बंद it.  The devices are at
 *   /dev/vport<device number>p<port number>
 */
अटल स्थिर काष्ठा file_operations port_fops = अणु
	.owner = THIS_MODULE,
	.खोलो  = port_fops_खोलो,
	.पढ़ो  = port_fops_पढ़ो,
	.ग_लिखो = port_fops_ग_लिखो,
	.splice_ग_लिखो = port_fops_splice_ग_लिखो,
	.poll  = port_fops_poll,
	.release = port_fops_release,
	.fasync = port_fops_fasync,
	.llseek = no_llseek,
पूर्ण;

/*
 * The put_अक्षरs() callback is pretty straightक्रमward.
 *
 * We turn the अक्षरacters पूर्णांकo a scatter-gather list, add it to the
 * output queue and then kick the Host.  Then we sit here रुकोing क्रम
 * it to finish: inefficient in theory, but in practice
 * implementations will करो it immediately.
 */
अटल पूर्णांक put_अक्षरs(u32 vtermno, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा port *port;
	काष्ठा scatterlist sg[1];
	व्योम *data;
	पूर्णांक ret;

	अगर (unlikely(early_put_अक्षरs))
		वापस early_put_अक्षरs(vtermno, buf, count);

	port = find_port_by_vtermno(vtermno);
	अगर (!port)
		वापस -EPIPE;

	data = kmemdup(buf, count, GFP_ATOMIC);
	अगर (!data)
		वापस -ENOMEM;

	sg_init_one(sg, data, count);
	ret = __send_to_port(port, sg, 1, count, data, false);
	kमुक्त(data);
	वापस ret;
पूर्ण

/*
 * get_अक्षरs() is the callback from the hvc_console infraकाष्ठाure
 * when an पूर्णांकerrupt is received.
 *
 * We call out to fill_पढ़ोbuf that माला_लो us the required data from the
 * buffers that are queued up.
 */
अटल पूर्णांक get_अक्षरs(u32 vtermno, अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा port *port;

	/* If we've not set up the port yet, we have no input to give. */
	अगर (unlikely(early_put_अक्षरs))
		वापस 0;

	port = find_port_by_vtermno(vtermno);
	अगर (!port)
		वापस -EPIPE;

	/* If we करोn't have an input queue yet, we can't get input. */
	BUG_ON(!port->in_vq);

	वापस fill_पढ़ोbuf(port, (__क्रमce अक्षर __user *)buf, count, false);
पूर्ण

अटल व्योम resize_console(काष्ठा port *port)
अणु
	काष्ठा virtio_device *vdev;

	/* The port could have been hot-unplugged */
	अगर (!port || !is_console_port(port))
		वापस;

	vdev = port->portdev->vdev;

	/* Don't test F_SIZE at all if we're rproc: not a valid feature! */
	अगर (!is_rproc_serial(vdev) &&
	    virtio_has_feature(vdev, VIRTIO_CONSOLE_F_SIZE))
		hvc_resize(port->cons.hvc, port->cons.ws);
पूर्ण

/* We set the configuration at this poपूर्णांक, since we now have a tty */
अटल पूर्णांक notअगरier_add_vio(काष्ठा hvc_काष्ठा *hp, पूर्णांक data)
अणु
	काष्ठा port *port;

	port = find_port_by_vtermno(hp->vtermno);
	अगर (!port)
		वापस -EINVAL;

	hp->irq_requested = 1;
	resize_console(port);

	वापस 0;
पूर्ण

अटल व्योम notअगरier_del_vio(काष्ठा hvc_काष्ठा *hp, पूर्णांक data)
अणु
	hp->irq_requested = 0;
पूर्ण

/* The operations क्रम console ports. */
अटल स्थिर काष्ठा hv_ops hv_ops = अणु
	.get_अक्षरs = get_अक्षरs,
	.put_अक्षरs = put_अक्षरs,
	.notअगरier_add = notअगरier_add_vio,
	.notअगरier_del = notअगरier_del_vio,
	.notअगरier_hangup = notअगरier_del_vio,
पूर्ण;

/*
 * Console drivers are initialized very early so boot messages can go
 * out, so we करो things slightly dअगरferently from the generic virtio
 * initialization of the net and block drivers.
 *
 * At this stage, the console is output-only.  It's too early to set
 * up a virtqueue, so we let the drivers करो some boutique early-output
 * thing.
 */
पूर्णांक __init virtio_cons_early_init(पूर्णांक (*put_अक्षरs)(u32, स्थिर अक्षर *, पूर्णांक))
अणु
	early_put_अक्षरs = put_अक्षरs;
	वापस hvc_instantiate(0, 0, &hv_ops);
पूर्ण

अटल पूर्णांक init_port_console(काष्ठा port *port)
अणु
	पूर्णांक ret;

	/*
	 * The Host's telling us this port is a console port.  Hook it
	 * up with an hvc console.
	 *
	 * To set up and manage our भव console, we call
	 * hvc_alloc().
	 *
	 * The first argument of hvc_alloc() is the भव console
	 * number.  The second argument is the parameter क्रम the
	 * notअगरication mechanism (like irq number).  We currently
	 * leave this as zero, virtqueues have implicit notअगरications.
	 *
	 * The third argument is a "struct hv_ops" containing the
	 * put_अक्षरs() get_अक्षरs(), notअगरier_add() and notअगरier_del()
	 * poपूर्णांकers.  The final argument is the output buffer size: we
	 * can करो any size, so we put PAGE_SIZE here.
	 */
	port->cons.vtermno = pdrvdata.next_vtermno;

	port->cons.hvc = hvc_alloc(port->cons.vtermno, 0, &hv_ops, PAGE_SIZE);
	अगर (IS_ERR(port->cons.hvc)) अणु
		ret = PTR_ERR(port->cons.hvc);
		dev_err(port->dev,
			"error %d allocating hvc for port\n", ret);
		port->cons.hvc = शून्य;
		वापस ret;
	पूर्ण
	spin_lock_irq(&pdrvdata_lock);
	pdrvdata.next_vtermno++;
	list_add_tail(&port->cons.list, &pdrvdata.consoles);
	spin_unlock_irq(&pdrvdata_lock);
	port->guest_connected = true;

	/*
	 * Start using the new console output अगर this is the first
	 * console to come up.
	 */
	अगर (early_put_अक्षरs)
		early_put_अक्षरs = शून्य;

	/* Notअगरy host of port being खोलोed */
	send_control_msg(port, VIRTIO_CONSOLE_PORT_OPEN, 1);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_port_name(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा port *port;

	port = dev_get_drvdata(dev);

	वापस प्र_लिखो(buffer, "%s\n", port->name);
पूर्ण

अटल DEVICE_ATTR(name, S_IRUGO, show_port_name, शून्य);

अटल काष्ठा attribute *port_sysfs_entries[] = अणु
	&dev_attr_name.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group port_attribute_group = अणु
	.name = शून्य,		/* put in device directory */
	.attrs = port_sysfs_entries,
पूर्ण;

अटल पूर्णांक port_debugfs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा port *port = s->निजी;

	seq_म_लिखो(s, "name: %s\n", port->name ? port->name : "");
	seq_म_लिखो(s, "guest_connected: %d\n", port->guest_connected);
	seq_म_लिखो(s, "host_connected: %d\n", port->host_connected);
	seq_म_लिखो(s, "outvq_full: %d\n", port->outvq_full);
	seq_म_लिखो(s, "bytes_sent: %lu\n", port->stats.bytes_sent);
	seq_म_लिखो(s, "bytes_received: %lu\n", port->stats.bytes_received);
	seq_म_लिखो(s, "bytes_discarded: %lu\n", port->stats.bytes_discarded);
	seq_म_लिखो(s, "is_console: %s\n",
		   is_console_port(port) ? "yes" : "no");
	seq_म_लिखो(s, "console_vtermno: %u\n", port->cons.vtermno);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(port_debugfs);

अटल व्योम set_console_size(काष्ठा port *port, u16 rows, u16 cols)
अणु
	अगर (!port || !is_console_port(port))
		वापस;

	port->cons.ws.ws_row = rows;
	port->cons.ws.ws_col = cols;
पूर्ण

अटल पूर्णांक fill_queue(काष्ठा virtqueue *vq, spinlock_t *lock)
अणु
	काष्ठा port_buffer *buf;
	पूर्णांक nr_added_bufs;
	पूर्णांक ret;

	nr_added_bufs = 0;
	करो अणु
		buf = alloc_buf(vq->vdev, PAGE_SIZE, 0);
		अगर (!buf)
			वापस -ENOMEM;

		spin_lock_irq(lock);
		ret = add_inbuf(vq, buf);
		अगर (ret < 0) अणु
			spin_unlock_irq(lock);
			मुक्त_buf(buf, true);
			वापस ret;
		पूर्ण
		nr_added_bufs++;
		spin_unlock_irq(lock);
	पूर्ण जबतक (ret > 0);

	वापस nr_added_bufs;
पूर्ण

अटल व्योम send_sigio_to_port(काष्ठा port *port)
अणु
	अगर (port->async_queue && port->guest_connected)
		समाप्त_fasync(&port->async_queue, SIGIO, POLL_OUT);
पूर्ण

अटल पूर्णांक add_port(काष्ठा ports_device *portdev, u32 id)
अणु
	अक्षर debugfs_name[16];
	काष्ठा port *port;
	dev_t devt;
	पूर्णांक err;

	port = kदो_स्मृति(माप(*port), GFP_KERNEL);
	अगर (!port) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण
	kref_init(&port->kref);

	port->portdev = portdev;
	port->id = id;

	port->name = शून्य;
	port->inbuf = शून्य;
	port->cons.hvc = शून्य;
	port->async_queue = शून्य;

	port->cons.ws.ws_row = port->cons.ws.ws_col = 0;
	port->cons.vtermno = 0;

	port->host_connected = port->guest_connected = false;
	port->stats = (काष्ठा port_stats) अणु 0 पूर्ण;

	port->outvq_full = false;

	port->in_vq = portdev->in_vqs[port->id];
	port->out_vq = portdev->out_vqs[port->id];

	port->cdev = cdev_alloc();
	अगर (!port->cdev) अणु
		dev_err(&port->portdev->vdev->dev, "Error allocating cdev\n");
		err = -ENOMEM;
		जाओ मुक्त_port;
	पूर्ण
	port->cdev->ops = &port_fops;

	devt = MKDEV(portdev->chr_major, id);
	err = cdev_add(port->cdev, devt, 1);
	अगर (err < 0) अणु
		dev_err(&port->portdev->vdev->dev,
			"Error %d adding cdev for port %u\n", err, id);
		जाओ मुक्त_cdev;
	पूर्ण
	port->dev = device_create(pdrvdata.class, &port->portdev->vdev->dev,
				  devt, port, "vport%up%u",
				  port->portdev->vdev->index, id);
	अगर (IS_ERR(port->dev)) अणु
		err = PTR_ERR(port->dev);
		dev_err(&port->portdev->vdev->dev,
			"Error %d creating device for port %u\n",
			err, id);
		जाओ मुक्त_cdev;
	पूर्ण

	spin_lock_init(&port->inbuf_lock);
	spin_lock_init(&port->outvq_lock);
	init_रुकोqueue_head(&port->रुकोqueue);

	/* We can safely ignore ENOSPC because it means
	 * the queue alपढ़ोy has buffers. Buffers are हटाओd
	 * only by virtcons_हटाओ(), not by unplug_port()
	 */
	err = fill_queue(port->in_vq, &port->inbuf_lock);
	अगर (err < 0 && err != -ENOSPC) अणु
		dev_err(port->dev, "Error allocating inbufs\n");
		जाओ मुक्त_device;
	पूर्ण

	अगर (is_rproc_serial(port->portdev->vdev))
		/*
		 * For rproc_serial assume remote processor is connected.
		 * rproc_serial करोes not want the console port, only
		 * the generic port implementation.
		 */
		port->host_connected = true;
	अन्यथा अगर (!use_multiport(port->portdev)) अणु
		/*
		 * If we're not using multiport support,
		 * this has to be a console port.
		 */
		err = init_port_console(port);
		अगर (err)
			जाओ मुक्त_inbufs;
	पूर्ण

	spin_lock_irq(&portdev->ports_lock);
	list_add_tail(&port->list, &port->portdev->ports);
	spin_unlock_irq(&portdev->ports_lock);

	/*
	 * Tell the Host we're set so that it can send us various
	 * configuration parameters क्रम this port (eg, port name,
	 * caching, whether this is a console port, etc.)
	 */
	send_control_msg(port, VIRTIO_CONSOLE_PORT_READY, 1);

	/*
	 * Finally, create the debugfs file that we can use to
	 * inspect a port's state at any समय
	 */
	snम_लिखो(debugfs_name, माप(debugfs_name), "vport%up%u",
		 port->portdev->vdev->index, id);
	port->debugfs_file = debugfs_create_file(debugfs_name, 0444,
						 pdrvdata.debugfs_dir,
						 port, &port_debugfs_fops);
	वापस 0;

मुक्त_inbufs:
मुक्त_device:
	device_destroy(pdrvdata.class, port->dev->devt);
मुक्त_cdev:
	cdev_del(port->cdev);
मुक्त_port:
	kमुक्त(port);
fail:
	/* The host might want to notअगरy management sw about port add failure */
	__send_control_msg(portdev, id, VIRTIO_CONSOLE_PORT_READY, 0);
	वापस err;
पूर्ण

/* No users reमुख्य, हटाओ all port-specअगरic data. */
अटल व्योम हटाओ_port(काष्ठा kref *kref)
अणु
	काष्ठा port *port;

	port = container_of(kref, काष्ठा port, kref);

	kमुक्त(port);
पूर्ण

अटल व्योम हटाओ_port_data(काष्ठा port *port)
अणु
	spin_lock_irq(&port->inbuf_lock);
	/* Remove unused data this port might have received. */
	discard_port_data(port);
	spin_unlock_irq(&port->inbuf_lock);

	spin_lock_irq(&port->outvq_lock);
	reclaim_consumed_buffers(port);
	spin_unlock_irq(&port->outvq_lock);
पूर्ण

/*
 * Port got unplugged.  Remove port from portdev's list and drop the
 * kref reference.  If no userspace has this port खोलोed, it will
 * result in immediate removal the port.
 */
अटल व्योम unplug_port(काष्ठा port *port)
अणु
	spin_lock_irq(&port->portdev->ports_lock);
	list_del(&port->list);
	spin_unlock_irq(&port->portdev->ports_lock);

	spin_lock_irq(&port->inbuf_lock);
	अगर (port->guest_connected) अणु
		/* Let the app know the port is going करोwn. */
		send_sigio_to_port(port);

		/* Do this after sigio is actually sent */
		port->guest_connected = false;
		port->host_connected = false;

		wake_up_पूर्णांकerruptible(&port->रुकोqueue);
	पूर्ण
	spin_unlock_irq(&port->inbuf_lock);

	अगर (is_console_port(port)) अणु
		spin_lock_irq(&pdrvdata_lock);
		list_del(&port->cons.list);
		spin_unlock_irq(&pdrvdata_lock);
		hvc_हटाओ(port->cons.hvc);
	पूर्ण

	हटाओ_port_data(port);

	/*
	 * We should just assume the device itself has gone off --
	 * अन्यथा a बंद on an खोलो port later will try to send out a
	 * control message.
	 */
	port->portdev = शून्य;

	sysfs_हटाओ_group(&port->dev->kobj, &port_attribute_group);
	device_destroy(pdrvdata.class, port->dev->devt);
	cdev_del(port->cdev);

	debugfs_हटाओ(port->debugfs_file);
	kमुक्त(port->name);

	/*
	 * Locks around here are not necessary - a port can't be
	 * खोलोed after we हटाओd the port काष्ठा from ports_list
	 * above.
	 */
	kref_put(&port->kref, हटाओ_port);
पूर्ण

/* Any निजी messages that the Host and Guest want to share */
अटल व्योम handle_control_message(काष्ठा virtio_device *vdev,
				   काष्ठा ports_device *portdev,
				   काष्ठा port_buffer *buf)
अणु
	काष्ठा virtio_console_control *cpkt;
	काष्ठा port *port;
	माप_प्रकार name_size;
	पूर्णांक err;

	cpkt = (काष्ठा virtio_console_control *)(buf->buf + buf->offset);

	port = find_port_by_id(portdev, virtio32_to_cpu(vdev, cpkt->id));
	अगर (!port &&
	    cpkt->event != cpu_to_virtio16(vdev, VIRTIO_CONSOLE_PORT_ADD)) अणु
		/* No valid header at start of buffer.  Drop it. */
		dev_dbg(&portdev->vdev->dev,
			"Invalid index %u in control packet\n", cpkt->id);
		वापस;
	पूर्ण

	चयन (virtio16_to_cpu(vdev, cpkt->event)) अणु
	हाल VIRTIO_CONSOLE_PORT_ADD:
		अगर (port) अणु
			dev_dbg(&portdev->vdev->dev,
				"Port %u already added\n", port->id);
			send_control_msg(port, VIRTIO_CONSOLE_PORT_READY, 1);
			अवरोध;
		पूर्ण
		अगर (virtio32_to_cpu(vdev, cpkt->id) >=
		    portdev->max_nr_ports) अणु
			dev_warn(&portdev->vdev->dev,
				"Request for adding port with "
				"out-of-bound id %u, max. supported id: %u\n",
				cpkt->id, portdev->max_nr_ports - 1);
			अवरोध;
		पूर्ण
		add_port(portdev, virtio32_to_cpu(vdev, cpkt->id));
		अवरोध;
	हाल VIRTIO_CONSOLE_PORT_REMOVE:
		unplug_port(port);
		अवरोध;
	हाल VIRTIO_CONSOLE_CONSOLE_PORT:
		अगर (!cpkt->value)
			अवरोध;
		अगर (is_console_port(port))
			अवरोध;

		init_port_console(port);
		complete(&early_console_added);
		/*
		 * Could हटाओ the port here in हाल init fails - but
		 * have to notअगरy the host first.
		 */
		अवरोध;
	हाल VIRTIO_CONSOLE_RESIZE: अणु
		काष्ठा अणु
			__u16 rows;
			__u16 cols;
		पूर्ण size;

		अगर (!is_console_port(port))
			अवरोध;

		स_नकल(&size, buf->buf + buf->offset + माप(*cpkt),
		       माप(size));
		set_console_size(port, size.rows, size.cols);

		port->cons.hvc->irq_requested = 1;
		resize_console(port);
		अवरोध;
	पूर्ण
	हाल VIRTIO_CONSOLE_PORT_OPEN:
		port->host_connected = virtio16_to_cpu(vdev, cpkt->value);
		wake_up_पूर्णांकerruptible(&port->रुकोqueue);
		/*
		 * If the host port got बंदd and the host had any
		 * unconsumed buffers, we'll be able to reclaim them
		 * now.
		 */
		spin_lock_irq(&port->outvq_lock);
		reclaim_consumed_buffers(port);
		spin_unlock_irq(&port->outvq_lock);

		/*
		 * If the guest is connected, it'll be पूर्णांकerested in
		 * knowing the host connection state changed.
		 */
		spin_lock_irq(&port->inbuf_lock);
		send_sigio_to_port(port);
		spin_unlock_irq(&port->inbuf_lock);
		अवरोध;
	हाल VIRTIO_CONSOLE_PORT_NAME:
		/*
		 * If we woke up after hibernation, we can get this
		 * again.  Skip it in that हाल.
		 */
		अगर (port->name)
			अवरोध;

		/*
		 * Skip the size of the header and the cpkt to get the size
		 * of the name that was sent
		 */
		name_size = buf->len - buf->offset - माप(*cpkt) + 1;

		port->name = kदो_स्मृति(name_size, GFP_KERNEL);
		अगर (!port->name) अणु
			dev_err(port->dev,
				"Not enough space to store port name\n");
			अवरोध;
		पूर्ण
		म_नकलन(port->name, buf->buf + buf->offset + माप(*cpkt),
			name_size - 1);
		port->name[name_size - 1] = 0;

		/*
		 * Since we only have one sysfs attribute, 'name',
		 * create it only अगर we have a name क्रम the port.
		 */
		err = sysfs_create_group(&port->dev->kobj,
					 &port_attribute_group);
		अगर (err) अणु
			dev_err(port->dev,
				"Error %d creating sysfs device attributes\n",
				err);
		पूर्ण अन्यथा अणु
			/*
			 * Generate a udev event so that appropriate
			 * symlinks can be created based on udev
			 * rules.
			 */
			kobject_uevent(&port->dev->kobj, KOBJ_CHANGE);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम control_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ports_device *portdev;
	काष्ठा virtqueue *vq;
	काष्ठा port_buffer *buf;
	अचिन्हित पूर्णांक len;

	portdev = container_of(work, काष्ठा ports_device, control_work);
	vq = portdev->c_ivq;

	spin_lock(&portdev->c_ivq_lock);
	जबतक ((buf = virtqueue_get_buf(vq, &len))) अणु
		spin_unlock(&portdev->c_ivq_lock);

		buf->len = len;
		buf->offset = 0;

		handle_control_message(vq->vdev, portdev, buf);

		spin_lock(&portdev->c_ivq_lock);
		अगर (add_inbuf(portdev->c_ivq, buf) < 0) अणु
			dev_warn(&portdev->vdev->dev,
				 "Error adding buffer to queue\n");
			मुक्त_buf(buf, false);
		पूर्ण
	पूर्ण
	spin_unlock(&portdev->c_ivq_lock);
पूर्ण

अटल व्योम flush_bufs(काष्ठा virtqueue *vq, bool can_sleep)
अणु
	काष्ठा port_buffer *buf;
	अचिन्हित पूर्णांक len;

	जबतक ((buf = virtqueue_get_buf(vq, &len)))
		मुक्त_buf(buf, can_sleep);
पूर्ण

अटल व्योम out_पूर्णांकr(काष्ठा virtqueue *vq)
अणु
	काष्ठा port *port;

	port = find_port_by_vq(vq->vdev->priv, vq);
	अगर (!port) अणु
		flush_bufs(vq, false);
		वापस;
	पूर्ण

	wake_up_पूर्णांकerruptible(&port->रुकोqueue);
पूर्ण

अटल व्योम in_पूर्णांकr(काष्ठा virtqueue *vq)
अणु
	काष्ठा port *port;
	अचिन्हित दीर्घ flags;

	port = find_port_by_vq(vq->vdev->priv, vq);
	अगर (!port) अणु
		flush_bufs(vq, false);
		वापस;
	पूर्ण

	spin_lock_irqsave(&port->inbuf_lock, flags);
	port->inbuf = get_inbuf(port);

	/*
	 * Normally the port should not accept data when the port is
	 * बंदd. For generic serial ports, the host won't (shouldn't)
	 * send data till the guest is connected. But this condition
	 * can be reached when a console port is not yet connected (no
	 * tty is spawned) and the other side sends out data over the
	 * vring, or when a remote devices start sending data beक्रमe
	 * the ports are खोलोed.
	 *
	 * A generic serial port will discard data अगर not connected,
	 * जबतक console ports and rproc-serial ports accepts data at
	 * any समय. rproc-serial is initiated with guest_connected to
	 * false because port_fops_खोलो expects this. Console ports are
	 * hooked up with an HVC console and is initialized with
	 * guest_connected to true.
	 */

	अगर (!port->guest_connected && !is_rproc_serial(port->portdev->vdev))
		discard_port_data(port);

	/* Send a SIGIO indicating new data in हाल the process asked क्रम it */
	send_sigio_to_port(port);

	spin_unlock_irqrestore(&port->inbuf_lock, flags);

	wake_up_पूर्णांकerruptible(&port->रुकोqueue);

	अगर (is_console_port(port) && hvc_poll(port->cons.hvc))
		hvc_kick();
पूर्ण

अटल व्योम control_पूर्णांकr(काष्ठा virtqueue *vq)
अणु
	काष्ठा ports_device *portdev;

	portdev = vq->vdev->priv;
	schedule_work(&portdev->control_work);
पूर्ण

अटल व्योम config_पूर्णांकr(काष्ठा virtio_device *vdev)
अणु
	काष्ठा ports_device *portdev;

	portdev = vdev->priv;

	अगर (!use_multiport(portdev))
		schedule_work(&portdev->config_work);
पूर्ण

अटल व्योम config_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ports_device *portdev;

	portdev = container_of(work, काष्ठा ports_device, config_work);
	अगर (!use_multiport(portdev)) अणु
		काष्ठा virtio_device *vdev;
		काष्ठा port *port;
		u16 rows, cols;

		vdev = portdev->vdev;
		virtio_cपढ़ो(vdev, काष्ठा virtio_console_config, cols, &cols);
		virtio_cपढ़ो(vdev, काष्ठा virtio_console_config, rows, &rows);

		port = find_port_by_id(portdev, 0);
		set_console_size(port, rows, cols);

		/*
		 * We'll use this way of resizing only क्रम legacy
		 * support.  For newer userspace
		 * (VIRTIO_CONSOLE_F_MULTPORT+), use control messages
		 * to indicate console size changes so that it can be
		 * करोne per-port.
		 */
		resize_console(port);
	पूर्ण
पूर्ण

अटल पूर्णांक init_vqs(काष्ठा ports_device *portdev)
अणु
	vq_callback_t **io_callbacks;
	अक्षर **io_names;
	काष्ठा virtqueue **vqs;
	u32 i, j, nr_ports, nr_queues;
	पूर्णांक err;

	nr_ports = portdev->max_nr_ports;
	nr_queues = use_multiport(portdev) ? (nr_ports + 1) * 2 : 2;

	vqs = kदो_स्मृति_array(nr_queues, माप(काष्ठा virtqueue *), GFP_KERNEL);
	io_callbacks = kदो_स्मृति_array(nr_queues, माप(vq_callback_t *),
				     GFP_KERNEL);
	io_names = kदो_स्मृति_array(nr_queues, माप(अक्षर *), GFP_KERNEL);
	portdev->in_vqs = kदो_स्मृति_array(nr_ports, माप(काष्ठा virtqueue *),
					GFP_KERNEL);
	portdev->out_vqs = kदो_स्मृति_array(nr_ports, माप(काष्ठा virtqueue *),
					 GFP_KERNEL);
	अगर (!vqs || !io_callbacks || !io_names || !portdev->in_vqs ||
	    !portdev->out_vqs) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	/*
	 * For backward compat (newer host but older guest), the host
	 * spawns a console port first and also inits the vqs क्रम port
	 * 0 beक्रमe others.
	 */
	j = 0;
	io_callbacks[j] = in_पूर्णांकr;
	io_callbacks[j + 1] = out_पूर्णांकr;
	io_names[j] = "input";
	io_names[j + 1] = "output";
	j += 2;

	अगर (use_multiport(portdev)) अणु
		io_callbacks[j] = control_पूर्णांकr;
		io_callbacks[j + 1] = शून्य;
		io_names[j] = "control-i";
		io_names[j + 1] = "control-o";

		क्रम (i = 1; i < nr_ports; i++) अणु
			j += 2;
			io_callbacks[j] = in_पूर्णांकr;
			io_callbacks[j + 1] = out_पूर्णांकr;
			io_names[j] = "input";
			io_names[j + 1] = "output";
		पूर्ण
	पूर्ण
	/* Find the queues. */
	err = virtio_find_vqs(portdev->vdev, nr_queues, vqs,
			      io_callbacks,
			      (स्थिर अक्षर **)io_names, शून्य);
	अगर (err)
		जाओ मुक्त;

	j = 0;
	portdev->in_vqs[0] = vqs[0];
	portdev->out_vqs[0] = vqs[1];
	j += 2;
	अगर (use_multiport(portdev)) अणु
		portdev->c_ivq = vqs[j];
		portdev->c_ovq = vqs[j + 1];

		क्रम (i = 1; i < nr_ports; i++) अणु
			j += 2;
			portdev->in_vqs[i] = vqs[j];
			portdev->out_vqs[i] = vqs[j + 1];
		पूर्ण
	पूर्ण
	kमुक्त(io_names);
	kमुक्त(io_callbacks);
	kमुक्त(vqs);

	वापस 0;

मुक्त:
	kमुक्त(portdev->out_vqs);
	kमुक्त(portdev->in_vqs);
	kमुक्त(io_names);
	kमुक्त(io_callbacks);
	kमुक्त(vqs);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations portdev_fops = अणु
	.owner = THIS_MODULE,
पूर्ण;

अटल व्योम हटाओ_vqs(काष्ठा ports_device *portdev)
अणु
	काष्ठा virtqueue *vq;

	virtio_device_क्रम_each_vq(portdev->vdev, vq) अणु
		काष्ठा port_buffer *buf;

		flush_bufs(vq, true);
		जबतक ((buf = virtqueue_detach_unused_buf(vq)))
			मुक्त_buf(buf, true);
	पूर्ण
	portdev->vdev->config->del_vqs(portdev->vdev);
	kमुक्त(portdev->in_vqs);
	kमुक्त(portdev->out_vqs);
पूर्ण

अटल व्योम virtcons_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा ports_device *portdev;
	काष्ठा port *port, *port2;

	portdev = vdev->priv;

	spin_lock_irq(&pdrvdata_lock);
	list_del(&portdev->list);
	spin_unlock_irq(&pdrvdata_lock);

	/* Disable पूर्णांकerrupts क्रम vqs */
	vdev->config->reset(vdev);
	/* Finish up work that's lined up */
	अगर (use_multiport(portdev))
		cancel_work_sync(&portdev->control_work);
	अन्यथा
		cancel_work_sync(&portdev->config_work);

	list_क्रम_each_entry_safe(port, port2, &portdev->ports, list)
		unplug_port(port);

	unरेजिस्टर_chrdev(portdev->chr_major, "virtio-portsdev");

	/*
	 * When yanking out a device, we immediately lose the
	 * (device-side) queues.  So there's no poपूर्णांक in keeping the
	 * guest side around till we drop our final reference.  This
	 * also means that any ports which are in an खोलो state will
	 * have to just stop using the port, as the vqs are going
	 * away.
	 */
	हटाओ_vqs(portdev);
	kमुक्त(portdev);
पूर्ण

/*
 * Once we're further in boot, we get probed like any other virtio
 * device.
 *
 * If the host also supports multiple console ports, we check the
 * config space to see how many ports the host has spawned.  We
 * initialize each port found.
 */
अटल पूर्णांक virtcons_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा ports_device *portdev;
	पूर्णांक err;
	bool multiport;
	bool early = early_put_अक्षरs != शून्य;

	/* We only need a config space अगर features are offered */
	अगर (!vdev->config->get &&
	    (virtio_has_feature(vdev, VIRTIO_CONSOLE_F_SIZE)
	     || virtio_has_feature(vdev, VIRTIO_CONSOLE_F_MULTIPORT))) अणु
		dev_err(&vdev->dev, "%s failure: config access disabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	/* Ensure to पढ़ो early_put_अक्षरs now */
	barrier();

	portdev = kदो_स्मृति(माप(*portdev), GFP_KERNEL);
	अगर (!portdev) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* Attach this portdev to this virtio_device, and vice-versa. */
	portdev->vdev = vdev;
	vdev->priv = portdev;

	portdev->chr_major = रेजिस्टर_chrdev(0, "virtio-portsdev",
					     &portdev_fops);
	अगर (portdev->chr_major < 0) अणु
		dev_err(&vdev->dev,
			"Error %d registering chrdev for device %u\n",
			portdev->chr_major, vdev->index);
		err = portdev->chr_major;
		जाओ मुक्त;
	पूर्ण

	multiport = false;
	portdev->max_nr_ports = 1;

	/* Don't test MULTIPORT at all if we're rproc: not a valid feature! */
	अगर (!is_rproc_serial(vdev) &&
	    virtio_cपढ़ो_feature(vdev, VIRTIO_CONSOLE_F_MULTIPORT,
				 काष्ठा virtio_console_config, max_nr_ports,
				 &portdev->max_nr_ports) == 0) अणु
		multiport = true;
	पूर्ण

	err = init_vqs(portdev);
	अगर (err < 0) अणु
		dev_err(&vdev->dev, "Error %d initializing vqs\n", err);
		जाओ मुक्त_chrdev;
	पूर्ण

	spin_lock_init(&portdev->ports_lock);
	INIT_LIST_HEAD(&portdev->ports);
	INIT_LIST_HEAD(&portdev->list);

	virtio_device_पढ़ोy(portdev->vdev);

	INIT_WORK(&portdev->config_work, &config_work_handler);
	INIT_WORK(&portdev->control_work, &control_work_handler);

	अगर (multiport) अणु
		spin_lock_init(&portdev->c_ivq_lock);
		spin_lock_init(&portdev->c_ovq_lock);

		err = fill_queue(portdev->c_ivq, &portdev->c_ivq_lock);
		अगर (err < 0) अणु
			dev_err(&vdev->dev,
				"Error allocating buffers for control queue\n");
			/*
			 * The host might want to notअगरy mgmt sw about device
			 * add failure.
			 */
			__send_control_msg(portdev, VIRTIO_CONSOLE_BAD_ID,
					   VIRTIO_CONSOLE_DEVICE_READY, 0);
			/* Device was functional: we need full cleanup. */
			virtcons_हटाओ(vdev);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * For backward compatibility: Create a console port
		 * अगर we're running on older host.
		 */
		add_port(portdev, 0);
	पूर्ण

	spin_lock_irq(&pdrvdata_lock);
	list_add_tail(&portdev->list, &pdrvdata.portdevs);
	spin_unlock_irq(&pdrvdata_lock);

	__send_control_msg(portdev, VIRTIO_CONSOLE_BAD_ID,
			   VIRTIO_CONSOLE_DEVICE_READY, 1);

	/*
	 * If there was an early virtio console, assume that there are no
	 * other consoles. We need to रुको until the hvc_alloc matches the
	 * hvc_instantiate, otherwise tty_खोलो will complain, resulting in
	 * a "Warning: unable to open an initial console" boot failure.
	 * Without multiport this is करोne in add_port above. With multiport
	 * this might take some host<->guest communication - thus we have to
	 * रुको.
	 */
	अगर (multiport && early)
		रुको_क्रम_completion(&early_console_added);

	वापस 0;

मुक्त_chrdev:
	unरेजिस्टर_chrdev(portdev->chr_major, "virtio-portsdev");
मुक्त:
	kमुक्त(portdev);
fail:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_CONSOLE, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(virtio, id_table);

अटल स्थिर अचिन्हित पूर्णांक features[] = अणु
	VIRTIO_CONSOLE_F_SIZE,
	VIRTIO_CONSOLE_F_MULTIPORT,
पूर्ण;

अटल स्थिर काष्ठा virtio_device_id rproc_serial_id_table[] = अणु
#अगर IS_ENABLED(CONFIG_REMOTEPROC)
	अणु VIRTIO_ID_RPROC_SERIAL, VIRTIO_DEV_ANY_ID पूर्ण,
#पूर्ण_अगर
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(virtio, rproc_serial_id_table);

अटल स्थिर अचिन्हित पूर्णांक rproc_serial_features[] = अणु
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtcons_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	काष्ठा ports_device *portdev;
	काष्ठा port *port;

	portdev = vdev->priv;

	vdev->config->reset(vdev);

	अगर (use_multiport(portdev))
		virtqueue_disable_cb(portdev->c_ivq);
	cancel_work_sync(&portdev->control_work);
	cancel_work_sync(&portdev->config_work);
	/*
	 * Once more: अगर control_work_handler() was running, it would
	 * enable the cb as the last step.
	 */
	अगर (use_multiport(portdev))
		virtqueue_disable_cb(portdev->c_ivq);

	list_क्रम_each_entry(port, &portdev->ports, list) अणु
		virtqueue_disable_cb(port->in_vq);
		virtqueue_disable_cb(port->out_vq);
		/*
		 * We'll ask the host later अगर the new invocation has
		 * the port खोलोed or बंदd.
		 */
		port->host_connected = false;
		हटाओ_port_data(port);
	पूर्ण
	हटाओ_vqs(portdev);

	वापस 0;
पूर्ण

अटल पूर्णांक virtcons_restore(काष्ठा virtio_device *vdev)
अणु
	काष्ठा ports_device *portdev;
	काष्ठा port *port;
	पूर्णांक ret;

	portdev = vdev->priv;

	ret = init_vqs(portdev);
	अगर (ret)
		वापस ret;

	virtio_device_पढ़ोy(portdev->vdev);

	अगर (use_multiport(portdev))
		fill_queue(portdev->c_ivq, &portdev->c_ivq_lock);

	list_क्रम_each_entry(port, &portdev->ports, list) अणु
		port->in_vq = portdev->in_vqs[port->id];
		port->out_vq = portdev->out_vqs[port->id];

		fill_queue(port->in_vq, &port->inbuf_lock);

		/* Get port खोलो/बंद status on the host */
		send_control_msg(port, VIRTIO_CONSOLE_PORT_READY, 1);

		/*
		 * If a port was खोलो at the समय of suspending, we
		 * have to let the host know that it's still खोलो.
		 */
		अगर (port->guest_connected)
			send_control_msg(port, VIRTIO_CONSOLE_PORT_OPEN, 1);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा virtio_driver virtio_console = अणु
	.feature_table = features,
	.feature_table_size = ARRAY_SIZE(features),
	.driver.name =	KBUILD_MODNAME,
	.driver.owner =	THIS_MODULE,
	.id_table =	id_table,
	.probe =	virtcons_probe,
	.हटाओ =	virtcons_हटाओ,
	.config_changed = config_पूर्णांकr,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze =	virtcons_मुक्तze,
	.restore =	virtcons_restore,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा virtio_driver virtio_rproc_serial = अणु
	.feature_table = rproc_serial_features,
	.feature_table_size = ARRAY_SIZE(rproc_serial_features),
	.driver.name =	"virtio_rproc_serial",
	.driver.owner =	THIS_MODULE,
	.id_table =	rproc_serial_id_table,
	.probe =	virtcons_probe,
	.हटाओ =	virtcons_हटाओ,
पूर्ण;

अटल पूर्णांक __init init(व्योम)
अणु
	पूर्णांक err;

	pdrvdata.class = class_create(THIS_MODULE, "virtio-ports");
	अगर (IS_ERR(pdrvdata.class)) अणु
		err = PTR_ERR(pdrvdata.class);
		pr_err("Error %d creating virtio-ports class\n", err);
		वापस err;
	पूर्ण

	pdrvdata.debugfs_dir = debugfs_create_dir("virtio-ports", शून्य);
	INIT_LIST_HEAD(&pdrvdata.consoles);
	INIT_LIST_HEAD(&pdrvdata.portdevs);

	err = रेजिस्टर_virtio_driver(&virtio_console);
	अगर (err < 0) अणु
		pr_err("Error %d registering virtio driver\n", err);
		जाओ मुक्त;
	पूर्ण
	err = रेजिस्टर_virtio_driver(&virtio_rproc_serial);
	अगर (err < 0) अणु
		pr_err("Error %d registering virtio rproc serial driver\n",
		       err);
		जाओ unरेजिस्टर;
	पूर्ण
	वापस 0;
unरेजिस्टर:
	unरेजिस्टर_virtio_driver(&virtio_console);
मुक्त:
	debugfs_हटाओ_recursive(pdrvdata.debugfs_dir);
	class_destroy(pdrvdata.class);
	वापस err;
पूर्ण

अटल व्योम __निकास fini(व्योम)
अणु
	reclaim_dma_bufs();

	unरेजिस्टर_virtio_driver(&virtio_console);
	unरेजिस्टर_virtio_driver(&virtio_rproc_serial);

	class_destroy(pdrvdata.class);
	debugfs_हटाओ_recursive(pdrvdata.debugfs_dir);
पूर्ण
module_init(init);
module_निकास(fini);

MODULE_DESCRIPTION("Virtio console driver");
MODULE_LICENSE("GPL");
