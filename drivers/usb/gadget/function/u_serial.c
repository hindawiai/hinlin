<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * u_serial.c - utilities क्रम USB gadget "serial port"/TTY support
 *
 * Copyright (C) 2003 Al Borchers (alborchers@steinerpoपूर्णांक.com)
 * Copyright (C) 2008 David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 *
 * This code also borrows from usbserial.c, which is
 * Copyright (C) 1999 - 2002 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2000 Peter Berger (pberger@brimson.com)
 * Copyright (C) 2000 Al Borchers (alborchers@steinerpoपूर्णांक.com)
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kfअगरo.h>

#समावेश "u_serial.h"


/*
 * This component encapsulates the TTY layer glue needed to provide basic
 * "serial port" functionality through the USB gadget stack.  Each such
 * port is exposed through a /dev/ttyGS* node.
 *
 * After this module has been loaded, the inभागidual TTY port can be requested
 * (gserial_alloc_line()) and it will stay available until they are हटाओd
 * (gserial_मुक्त_line()). Each one may be connected to a USB function
 * (gserial_connect), or disconnected (with gserial_disconnect) when the USB
 * host issues a config change event. Data can only flow when the port is
 * connected to the host.
 *
 * A given TTY port can be made available in multiple configurations.
 * For example, each one might expose a ttyGS0 node which provides a
 * login application.  In one हाल that might use CDC ACM पूर्णांकerface 0,
 * जबतक another configuration might use पूर्णांकerface 3 क्रम that.  The
 * work to handle that (including descriptor management) is not part
 * of this component.
 *
 * Configurations may expose more than one TTY port.  For example, अगर
 * ttyGS0 provides login service, then ttyGS1 might provide dialer access
 * क्रम a telephone or fax link.  And ttyGS2 might be something that just
 * needs a simple byte stream पूर्णांकerface क्रम some messaging protocol that
 * is managed in userspace ... OBEX, PTP, and MTP have been mentioned.
 *
 *
 * gserial is the lअगरecycle पूर्णांकerface, used by USB functions
 * gs_port is the I/O nexus, used by the tty driver
 * tty_काष्ठा links to the tty/fileप्रणाली framework
 *
 * gserial <---> gs_port ... links will be null when the USB link is
 * inactive; managed by gserial_अणुconnect,disconnectपूर्ण().  each gserial
 * instance can wrap its own USB control protocol.
 *	gserial->ioport == usb_ep->driver_data ... gs_port
 *	gs_port->port_usb ... gserial
 *
 * gs_port <---> tty_काष्ठा ... links will be null when the TTY file
 * isn't खोलोed; managed by gs_खोलो()/gs_बंद()
 *	gserial->port_tty ... tty_काष्ठा
 *	tty_काष्ठा->driver_data ... gserial
 */

/* RX and TX queues can buffer QUEUE_SIZE packets beक्रमe they hit the
 * next layer of buffering.  For TX that's a circular buffer; क्रम RX
 * consider it a NOP.  A third layer is provided by the TTY code.
 */
#घोषणा QUEUE_SIZE		16
#घोषणा WRITE_BUF_SIZE		8192		/* TX only */
#घोषणा GS_CONSOLE_BUF_SIZE	8192

/* console info */
काष्ठा gs_console अणु
	काष्ठा console		console;
	काष्ठा work_काष्ठा	work;
	spinlock_t		lock;
	काष्ठा usb_request	*req;
	काष्ठा kfअगरo		buf;
	माप_प्रकार			missed;
पूर्ण;

/*
 * The port काष्ठाure holds info क्रम each port, one क्रम each minor number
 * (and thus क्रम each /dev/ node).
 */
काष्ठा gs_port अणु
	काष्ठा tty_port		port;
	spinlock_t		port_lock;	/* guard port_* access */

	काष्ठा gserial		*port_usb;
#अगर_घोषित CONFIG_U_SERIAL_CONSOLE
	काष्ठा gs_console	*console;
#पूर्ण_अगर

	u8			port_num;

	काष्ठा list_head	पढ़ो_pool;
	पूर्णांक पढ़ो_started;
	पूर्णांक पढ़ो_allocated;
	काष्ठा list_head	पढ़ो_queue;
	अचिन्हित		n_पढ़ो;
	काष्ठा delayed_work	push;

	काष्ठा list_head	ग_लिखो_pool;
	पूर्णांक ग_लिखो_started;
	पूर्णांक ग_लिखो_allocated;
	काष्ठा kfअगरo		port_ग_लिखो_buf;
	रुको_queue_head_t	drain_रुको;	/* रुको जबतक ग_लिखोs drain */
	bool                    ग_लिखो_busy;
	रुको_queue_head_t	बंद_रुको;
	bool			suspended;	/* port suspended */
	bool			start_delayed;	/* delay start when suspended */

	/* REVISIT this state ... */
	काष्ठा usb_cdc_line_coding port_line_coding;	/* 8-N-1 etc */
पूर्ण;

अटल काष्ठा porपंचांगaster अणु
	काष्ठा mutex	lock;			/* protect खोलो/बंद */
	काष्ठा gs_port	*port;
पूर्ण ports[MAX_U_SERIAL_PORTS];

#घोषणा GS_CLOSE_TIMEOUT		15		/* seconds */



#अगर_घोषित VERBOSE_DEBUG
#अगर_अघोषित pr_vdebug
#घोषणा pr_vdebug(fmt, arg...) \
	pr_debug(fmt, ##arg)
#पूर्ण_अगर /* pr_vdebug */
#अन्यथा
#अगर_अघोषित pr_vdebug
#घोषणा pr_vdebug(fmt, arg...) \
	(अणु अगर (0) pr_debug(fmt, ##arg); पूर्ण)
#पूर्ण_अगर /* pr_vdebug */
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/* I/O glue between TTY (upper) and USB function (lower) driver layers */

/*
 * gs_alloc_req
 *
 * Allocate a usb_request and its buffer.  Returns a poपूर्णांकer to the
 * usb_request or शून्य अगर there is an error.
 */
काष्ठा usb_request *
gs_alloc_req(काष्ठा usb_ep *ep, अचिन्हित len, gfp_t kदो_स्मृति_flags)
अणु
	काष्ठा usb_request *req;

	req = usb_ep_alloc_request(ep, kदो_स्मृति_flags);

	अगर (req != शून्य) अणु
		req->length = len;
		req->buf = kदो_स्मृति(len, kदो_स्मृति_flags);
		अगर (req->buf == शून्य) अणु
			usb_ep_मुक्त_request(ep, req);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस req;
पूर्ण
EXPORT_SYMBOL_GPL(gs_alloc_req);

/*
 * gs_मुक्त_req
 *
 * Free a usb_request and its buffer.
 */
व्योम gs_मुक्त_req(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	kमुक्त(req->buf);
	usb_ep_मुक्त_request(ep, req);
पूर्ण
EXPORT_SYMBOL_GPL(gs_मुक्त_req);

/*
 * gs_send_packet
 *
 * If there is data to send, a packet is built in the given
 * buffer and the size is वापसed.  If there is no data to
 * send, 0 is वापसed.
 *
 * Called with port_lock held.
 */
अटल अचिन्हित
gs_send_packet(काष्ठा gs_port *port, अक्षर *packet, अचिन्हित size)
अणु
	अचिन्हित len;

	len = kfअगरo_len(&port->port_ग_लिखो_buf);
	अगर (len < size)
		size = len;
	अगर (size != 0)
		size = kfअगरo_out(&port->port_ग_लिखो_buf, packet, size);
	वापस size;
पूर्ण

/*
 * gs_start_tx
 *
 * This function finds available ग_लिखो requests, calls
 * gs_send_packet to fill these packets with data, and
 * जारीs until either there are no more ग_लिखो requests
 * available or no more data to send.  This function is
 * run whenever data arrives or ग_लिखो requests are available.
 *
 * Context: caller owns port_lock; port_usb is non-null.
 */
अटल पूर्णांक gs_start_tx(काष्ठा gs_port *port)
/*
__releases(&port->port_lock)
__acquires(&port->port_lock)
*/
अणु
	काष्ठा list_head	*pool = &port->ग_लिखो_pool;
	काष्ठा usb_ep		*in;
	पूर्णांक			status = 0;
	bool			करो_tty_wake = false;

	अगर (!port->port_usb)
		वापस status;

	in = port->port_usb->in;

	जबतक (!port->ग_लिखो_busy && !list_empty(pool)) अणु
		काष्ठा usb_request	*req;
		पूर्णांक			len;

		अगर (port->ग_लिखो_started >= QUEUE_SIZE)
			अवरोध;

		req = list_entry(pool->next, काष्ठा usb_request, list);
		len = gs_send_packet(port, req->buf, in->maxpacket);
		अगर (len == 0) अणु
			wake_up_पूर्णांकerruptible(&port->drain_रुको);
			अवरोध;
		पूर्ण
		करो_tty_wake = true;

		req->length = len;
		list_del(&req->list);
		req->zero = kfअगरo_is_empty(&port->port_ग_लिखो_buf);

		pr_vdebug("ttyGS%d: tx len=%d, %3ph ...\n", port->port_num, len, req->buf);

		/* Drop lock जबतक we call out of driver; completions
		 * could be issued जबतक we करो so.  Disconnection may
		 * happen too; maybe immediately beक्रमe we queue this!
		 *
		 * NOTE that we may keep sending data क्रम a जबतक after
		 * the TTY बंदd (dev->ioport->port_tty is शून्य).
		 */
		port->ग_लिखो_busy = true;
		spin_unlock(&port->port_lock);
		status = usb_ep_queue(in, req, GFP_ATOMIC);
		spin_lock(&port->port_lock);
		port->ग_लिखो_busy = false;

		अगर (status) अणु
			pr_debug("%s: %s %s err %d\n",
					__func__, "queue", in->name, status);
			list_add(&req->list, pool);
			अवरोध;
		पूर्ण

		port->ग_लिखो_started++;

		/* पात immediately after disconnect */
		अगर (!port->port_usb)
			अवरोध;
	पूर्ण

	अगर (करो_tty_wake && port->port.tty)
		tty_wakeup(port->port.tty);
	वापस status;
पूर्ण

/*
 * Context: caller owns port_lock, and port_usb is set
 */
अटल अचिन्हित gs_start_rx(काष्ठा gs_port *port)
/*
__releases(&port->port_lock)
__acquires(&port->port_lock)
*/
अणु
	काष्ठा list_head	*pool = &port->पढ़ो_pool;
	काष्ठा usb_ep		*out = port->port_usb->out;

	जबतक (!list_empty(pool)) अणु
		काष्ठा usb_request	*req;
		पूर्णांक			status;
		काष्ठा tty_काष्ठा	*tty;

		/* no more rx अगर बंदd */
		tty = port->port.tty;
		अगर (!tty)
			अवरोध;

		अगर (port->पढ़ो_started >= QUEUE_SIZE)
			अवरोध;

		req = list_entry(pool->next, काष्ठा usb_request, list);
		list_del(&req->list);
		req->length = out->maxpacket;

		/* drop lock जबतक we call out; the controller driver
		 * may need to call us back (e.g. क्रम disconnect)
		 */
		spin_unlock(&port->port_lock);
		status = usb_ep_queue(out, req, GFP_ATOMIC);
		spin_lock(&port->port_lock);

		अगर (status) अणु
			pr_debug("%s: %s %s err %d\n",
					__func__, "queue", out->name, status);
			list_add(&req->list, pool);
			अवरोध;
		पूर्ण
		port->पढ़ो_started++;

		/* पात immediately after disconnect */
		अगर (!port->port_usb)
			अवरोध;
	पूर्ण
	वापस port->पढ़ो_started;
पूर्ण

/*
 * RX work takes data out of the RX queue and hands it up to the TTY
 * layer until it refuses to take any more data (or is throttled back).
 * Then it issues पढ़ोs क्रम any further data.
 *
 * If the RX queue becomes full enough that no usb_request is queued,
 * the OUT endpoपूर्णांक may begin NAKing as soon as its FIFO fills up.
 * So QUEUE_SIZE packets plus however many the FIFO holds (usually two)
 * can be buffered beक्रमe the TTY layer's buffers (currently 64 KB).
 */
अटल व्योम gs_rx_push(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work	*w = to_delayed_work(work);
	काष्ठा gs_port		*port = container_of(w, काष्ठा gs_port, push);
	काष्ठा tty_काष्ठा	*tty;
	काष्ठा list_head	*queue = &port->पढ़ो_queue;
	bool			disconnect = false;
	bool			करो_push = false;

	/* hand any queued data to the tty */
	spin_lock_irq(&port->port_lock);
	tty = port->port.tty;
	जबतक (!list_empty(queue)) अणु
		काष्ठा usb_request	*req;

		req = list_first_entry(queue, काष्ठा usb_request, list);

		/* leave data queued अगर tty was rx throttled */
		अगर (tty && tty_throttled(tty))
			अवरोध;

		चयन (req->status) अणु
		हाल -ESHUTDOWN:
			disconnect = true;
			pr_vdebug("ttyGS%d: shutdown\n", port->port_num);
			अवरोध;

		शेष:
			/* presumably a transient fault */
			pr_warn("ttyGS%d: unexpected RX status %d\n",
				port->port_num, req->status);
			fallthrough;
		हाल 0:
			/* normal completion */
			अवरोध;
		पूर्ण

		/* push data to (खोलो) tty */
		अगर (req->actual && tty) अणु
			अक्षर		*packet = req->buf;
			अचिन्हित	size = req->actual;
			अचिन्हित	n;
			पूर्णांक		count;

			/* we may have pushed part of this packet alपढ़ोy... */
			n = port->n_पढ़ो;
			अगर (n) अणु
				packet += n;
				size -= n;
			पूर्ण

			count = tty_insert_flip_string(&port->port, packet,
					size);
			अगर (count)
				करो_push = true;
			अगर (count != size) अणु
				/* stop pushing; TTY layer can't handle more */
				port->n_पढ़ो += count;
				pr_vdebug("ttyGS%d: rx block %d/%d\n",
					  port->port_num, count, req->actual);
				अवरोध;
			पूर्ण
			port->n_पढ़ो = 0;
		पूर्ण

		list_move(&req->list, &port->पढ़ो_pool);
		port->पढ़ो_started--;
	पूर्ण

	/* Push from tty to ldisc; this is handled by a workqueue,
	 * so we won't get callbacks and can hold port_lock
	 */
	अगर (करो_push)
		tty_flip_buffer_push(&port->port);


	/* We want our data queue to become empty ASAP, keeping data
	 * in the tty and ldisc (not here).  If we couldn't push any
	 * this समय around, RX may be starved, so रुको until next jअगरfy.
	 *
	 * We may leave non-empty queue only when there is a tty, and
	 * either it is throttled or there is no more room in flip buffer.
	 */
	अगर (!list_empty(queue) && !tty_throttled(tty))
		schedule_delayed_work(&port->push, 1);

	/* If we're still connected, refill the USB RX queue. */
	अगर (!disconnect && port->port_usb)
		gs_start_rx(port);

	spin_unlock_irq(&port->port_lock);
पूर्ण

अटल व्योम gs_पढ़ो_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा gs_port	*port = ep->driver_data;

	/* Queue all received data until the tty layer is पढ़ोy क्रम it. */
	spin_lock(&port->port_lock);
	list_add_tail(&req->list, &port->पढ़ो_queue);
	schedule_delayed_work(&port->push, 0);
	spin_unlock(&port->port_lock);
पूर्ण

अटल व्योम gs_ग_लिखो_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा gs_port	*port = ep->driver_data;

	spin_lock(&port->port_lock);
	list_add(&req->list, &port->ग_लिखो_pool);
	port->ग_लिखो_started--;

	चयन (req->status) अणु
	शेष:
		/* presumably a transient fault */
		pr_warn("%s: unexpected %s status %d\n",
			__func__, ep->name, req->status);
		fallthrough;
	हाल 0:
		/* normal completion */
		gs_start_tx(port);
		अवरोध;

	हाल -ESHUTDOWN:
		/* disconnect */
		pr_vdebug("%s: %s shutdown\n", __func__, ep->name);
		अवरोध;
	पूर्ण

	spin_unlock(&port->port_lock);
पूर्ण

अटल व्योम gs_मुक्त_requests(काष्ठा usb_ep *ep, काष्ठा list_head *head,
							 पूर्णांक *allocated)
अणु
	काष्ठा usb_request	*req;

	जबतक (!list_empty(head)) अणु
		req = list_entry(head->next, काष्ठा usb_request, list);
		list_del(&req->list);
		gs_मुक्त_req(ep, req);
		अगर (allocated)
			(*allocated)--;
	पूर्ण
पूर्ण

अटल पूर्णांक gs_alloc_requests(काष्ठा usb_ep *ep, काष्ठा list_head *head,
		व्योम (*fn)(काष्ठा usb_ep *, काष्ठा usb_request *),
		पूर्णांक *allocated)
अणु
	पूर्णांक			i;
	काष्ठा usb_request	*req;
	पूर्णांक n = allocated ? QUEUE_SIZE - *allocated : QUEUE_SIZE;

	/* Pre-allocate up to QUEUE_SIZE transfers, but अगर we can't
	 * करो quite that many this समय, करोn't fail ... we just won't
	 * be as speedy as we might otherwise be.
	 */
	क्रम (i = 0; i < n; i++) अणु
		req = gs_alloc_req(ep, ep->maxpacket, GFP_ATOMIC);
		अगर (!req)
			वापस list_empty(head) ? -ENOMEM : 0;
		req->complete = fn;
		list_add_tail(&req->list, head);
		अगर (allocated)
			(*allocated)++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * gs_start_io - start USB I/O streams
 * @port: port to use
 * Context: holding port_lock; port_tty and port_usb are non-null
 *
 * We only start I/O when something is connected to both sides of
 * this port.  If nothing is listening on the host side, we may
 * be poपूर्णांकlessly filling up our TX buffers and FIFO.
 */
अटल पूर्णांक gs_start_io(काष्ठा gs_port *port)
अणु
	काष्ठा list_head	*head = &port->पढ़ो_pool;
	काष्ठा usb_ep		*ep = port->port_usb->out;
	पूर्णांक			status;
	अचिन्हित		started;

	/* Allocate RX and TX I/O buffers.  We can't easily करो this much
	 * earlier (with GFP_KERNEL) because the requests are coupled to
	 * endpoपूर्णांकs, as are the packet sizes we'll be using.  Dअगरferent
	 * configurations may use dअगरferent endpoपूर्णांकs with a given port;
	 * and high speed vs full speed changes packet sizes too.
	 */
	status = gs_alloc_requests(ep, head, gs_पढ़ो_complete,
		&port->पढ़ो_allocated);
	अगर (status)
		वापस status;

	status = gs_alloc_requests(port->port_usb->in, &port->ग_लिखो_pool,
			gs_ग_लिखो_complete, &port->ग_लिखो_allocated);
	अगर (status) अणु
		gs_मुक्त_requests(ep, head, &port->पढ़ो_allocated);
		वापस status;
	पूर्ण

	/* queue पढ़ो requests */
	port->n_पढ़ो = 0;
	started = gs_start_rx(port);

	अगर (started) अणु
		gs_start_tx(port);
		/* Unblock any pending ग_लिखोs पूर्णांकo our circular buffer, in हाल
		 * we didn't in gs_start_tx() */
		tty_wakeup(port->port.tty);
	पूर्ण अन्यथा अणु
		gs_मुक्त_requests(ep, head, &port->पढ़ो_allocated);
		gs_मुक्त_requests(port->port_usb->in, &port->ग_लिखो_pool,
			&port->ग_लिखो_allocated);
		status = -EIO;
	पूर्ण

	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

/* TTY Driver */

/*
 * gs_खोलो sets up the link between a gs_port and its associated TTY.
 * That link is broken *only* by TTY बंद(), and all driver methods
 * know that.
 */
अटल पूर्णांक gs_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	पूर्णांक		port_num = tty->index;
	काष्ठा gs_port	*port;
	पूर्णांक		status = 0;

	mutex_lock(&ports[port_num].lock);
	port = ports[port_num].port;
	अगर (!port) अणु
		status = -ENODEV;
		जाओ out;
	पूर्ण

	spin_lock_irq(&port->port_lock);

	/* allocate circular buffer on first खोलो */
	अगर (!kfअगरo_initialized(&port->port_ग_लिखो_buf)) अणु

		spin_unlock_irq(&port->port_lock);

		/*
		 * porपंचांगaster's mutex still protects from simultaneous खोलो(),
		 * and बंद() can't happen, yet.
		 */

		status = kfअगरo_alloc(&port->port_ग_लिखो_buf,
				     WRITE_BUF_SIZE, GFP_KERNEL);
		अगर (status) अणु
			pr_debug("gs_open: ttyGS%d (%p,%p) no buffer\n",
				 port_num, tty, file);
			जाओ out;
		पूर्ण

		spin_lock_irq(&port->port_lock);
	पूर्ण

	/* alपढ़ोy खोलो?  Great. */
	अगर (port->port.count++)
		जाओ निकास_unlock_port;

	tty->driver_data = port;
	port->port.tty = tty;

	/* अगर connected, start the I/O stream */
	अगर (port->port_usb) अणु
		/* अगर port is suspended, रुको resume to start I/0 stream */
		अगर (!port->suspended) अणु
			काष्ठा gserial	*gser = port->port_usb;

			pr_debug("gs_open: start ttyGS%d\n", port->port_num);
			gs_start_io(port);

			अगर (gser->connect)
				gser->connect(gser);
		पूर्ण अन्यथा अणु
			pr_debug("delay start of ttyGS%d\n", port->port_num);
			port->start_delayed = true;
		पूर्ण
	पूर्ण

	pr_debug("gs_open: ttyGS%d (%p,%p)\n", port->port_num, tty, file);

निकास_unlock_port:
	spin_unlock_irq(&port->port_lock);
out:
	mutex_unlock(&ports[port_num].lock);
	वापस status;
पूर्ण

अटल पूर्णांक gs_बंद_flush_करोne(काष्ठा gs_port *p)
अणु
	पूर्णांक cond;

	/* वापस true on disconnect or empty buffer or अगर raced with खोलो() */
	spin_lock_irq(&p->port_lock);
	cond = p->port_usb == शून्य || !kfअगरo_len(&p->port_ग_लिखो_buf) ||
		p->port.count > 1;
	spin_unlock_irq(&p->port_lock);

	वापस cond;
पूर्ण

अटल व्योम gs_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा gs_port *port = tty->driver_data;
	काष्ठा gserial	*gser;

	spin_lock_irq(&port->port_lock);

	अगर (port->port.count != 1) अणु
raced_with_खोलो:
		अगर (port->port.count == 0)
			WARN_ON(1);
		अन्यथा
			--port->port.count;
		जाओ निकास;
	पूर्ण

	pr_debug("gs_close: ttyGS%d (%p,%p) ...\n", port->port_num, tty, file);

	gser = port->port_usb;
	अगर (gser && !port->suspended && gser->disconnect)
		gser->disconnect(gser);

	/* रुको क्रम circular ग_लिखो buffer to drain, disconnect, or at
	 * most GS_CLOSE_TIMEOUT seconds; then discard the rest
	 */
	अगर (kfअगरo_len(&port->port_ग_लिखो_buf) > 0 && gser) अणु
		spin_unlock_irq(&port->port_lock);
		रुको_event_पूर्णांकerruptible_समयout(port->drain_रुको,
					gs_बंद_flush_करोne(port),
					GS_CLOSE_TIMEOUT * HZ);
		spin_lock_irq(&port->port_lock);

		अगर (port->port.count != 1)
			जाओ raced_with_खोलो;

		gser = port->port_usb;
	पूर्ण

	/* Iff we're disconnected, there can be no I/O in flight so it's
	 * ok to मुक्त the circular buffer; अन्यथा just scrub it.  And करोn't
	 * let the push async work fire again until we're re-खोलोed.
	 */
	अगर (gser == शून्य)
		kfअगरo_मुक्त(&port->port_ग_लिखो_buf);
	अन्यथा
		kfअगरo_reset(&port->port_ग_लिखो_buf);

	port->start_delayed = false;
	port->port.count = 0;
	port->port.tty = शून्य;

	pr_debug("gs_close: ttyGS%d (%p,%p) done!\n",
			port->port_num, tty, file);

	wake_up(&port->बंद_रुको);
निकास:
	spin_unlock_irq(&port->port_lock);
पूर्ण

अटल पूर्णांक gs_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा gs_port	*port = tty->driver_data;
	अचिन्हित दीर्घ	flags;

	pr_vdebug("gs_write: ttyGS%d (%p) writing %d bytes\n",
			port->port_num, tty, count);

	spin_lock_irqsave(&port->port_lock, flags);
	अगर (count)
		count = kfअगरo_in(&port->port_ग_लिखो_buf, buf, count);
	/* treat count == 0 as flush_अक्षरs() */
	अगर (port->port_usb)
		gs_start_tx(port);
	spin_unlock_irqrestore(&port->port_lock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक gs_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	काष्ठा gs_port	*port = tty->driver_data;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		status;

	pr_vdebug("gs_put_char: (%d,%p) char=0x%x, called from %ps\n",
		port->port_num, tty, ch, __builtin_वापस_address(0));

	spin_lock_irqsave(&port->port_lock, flags);
	status = kfअगरo_put(&port->port_ग_लिखो_buf, ch);
	spin_unlock_irqrestore(&port->port_lock, flags);

	वापस status;
पूर्ण

अटल व्योम gs_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gs_port	*port = tty->driver_data;
	अचिन्हित दीर्घ	flags;

	pr_vdebug("gs_flush_chars: (%d,%p)\n", port->port_num, tty);

	spin_lock_irqsave(&port->port_lock, flags);
	अगर (port->port_usb)
		gs_start_tx(port);
	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण

अटल पूर्णांक gs_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gs_port	*port = tty->driver_data;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		room = 0;

	spin_lock_irqsave(&port->port_lock, flags);
	अगर (port->port_usb)
		room = kfअगरo_avail(&port->port_ग_लिखो_buf);
	spin_unlock_irqrestore(&port->port_lock, flags);

	pr_vdebug("gs_write_room: (%d,%p) room=%d\n",
		port->port_num, tty, room);

	वापस room;
पूर्ण

अटल पूर्णांक gs_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gs_port	*port = tty->driver_data;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		अक्षरs = 0;

	spin_lock_irqsave(&port->port_lock, flags);
	अक्षरs = kfअगरo_len(&port->port_ग_लिखो_buf);
	spin_unlock_irqrestore(&port->port_lock, flags);

	pr_vdebug("gs_chars_in_buffer: (%d,%p) chars=%d\n",
		port->port_num, tty, अक्षरs);

	वापस अक्षरs;
पूर्ण

/* unकरो side effects of setting TTY_THROTTLED */
अटल व्योम gs_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gs_port		*port = tty->driver_data;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&port->port_lock, flags);
	अगर (port->port_usb) अणु
		/* Kickstart पढ़ो queue processing.  We करोn't करो xon/xoff,
		 * rts/cts, or other handshaking with the host, but अगर the
		 * पढ़ो queue backs up enough we'll be NAKing OUT packets.
		 */
		pr_vdebug("ttyGS%d: unthrottle\n", port->port_num);
		schedule_delayed_work(&port->push, 0);
	पूर्ण
	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण

अटल पूर्णांक gs_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक duration)
अणु
	काष्ठा gs_port	*port = tty->driver_data;
	पूर्णांक		status = 0;
	काष्ठा gserial	*gser;

	pr_vdebug("gs_break_ctl: ttyGS%d, send break (%d) \n",
			port->port_num, duration);

	spin_lock_irq(&port->port_lock);
	gser = port->port_usb;
	अगर (gser && gser->send_अवरोध)
		status = gser->send_अवरोध(gser, duration);
	spin_unlock_irq(&port->port_lock);

	वापस status;
पूर्ण

अटल स्थिर काष्ठा tty_operations gs_tty_ops = अणु
	.खोलो =			gs_खोलो,
	.बंद =		gs_बंद,
	.ग_लिखो =		gs_ग_लिखो,
	.put_अक्षर =		gs_put_अक्षर,
	.flush_अक्षरs =		gs_flush_अक्षरs,
	.ग_लिखो_room =		gs_ग_लिखो_room,
	.अक्षरs_in_buffer =	gs_अक्षरs_in_buffer,
	.unthrottle =		gs_unthrottle,
	.अवरोध_ctl =		gs_अवरोध_ctl,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल काष्ठा tty_driver *gs_tty_driver;

#अगर_घोषित CONFIG_U_SERIAL_CONSOLE

अटल व्योम gs_console_complete_out(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा gs_console *cons = req->context;

	चयन (req->status) अणु
	शेष:
		pr_warn("%s: unexpected %s status %d\n",
			__func__, ep->name, req->status);
		fallthrough;
	हाल 0:
		/* normal completion */
		spin_lock(&cons->lock);
		req->length = 0;
		schedule_work(&cons->work);
		spin_unlock(&cons->lock);
		अवरोध;
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		/* disconnect */
		pr_vdebug("%s: %s shutdown\n", __func__, ep->name);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __gs_console_push(काष्ठा gs_console *cons)
अणु
	काष्ठा usb_request *req = cons->req;
	काष्ठा usb_ep *ep;
	माप_प्रकार size;

	अगर (!req)
		वापस;	/* disconnected */

	अगर (req->length)
		वापस;	/* busy */

	ep = cons->console.data;
	size = kfअगरo_out(&cons->buf, req->buf, ep->maxpacket);
	अगर (!size)
		वापस;

	अगर (cons->missed && ep->maxpacket >= 64) अणु
		अक्षर buf[64];
		माप_प्रकार len;

		len = प्र_लिखो(buf, "\n[missed %zu bytes]\n", cons->missed);
		kfअगरo_in(&cons->buf, buf, len);
		cons->missed = 0;
	पूर्ण

	req->length = size;
	अगर (usb_ep_queue(ep, req, GFP_ATOMIC))
		req->length = 0;
पूर्ण

अटल व्योम gs_console_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gs_console *cons = container_of(work, काष्ठा gs_console, work);

	spin_lock_irq(&cons->lock);

	__gs_console_push(cons);

	spin_unlock_irq(&cons->lock);
पूर्ण

अटल व्योम gs_console_ग_लिखो(काष्ठा console *co,
			     स्थिर अक्षर *buf, अचिन्हित count)
अणु
	काष्ठा gs_console *cons = container_of(co, काष्ठा gs_console, console);
	अचिन्हित दीर्घ flags;
	माप_प्रकार n;

	spin_lock_irqsave(&cons->lock, flags);

	n = kfअगरo_in(&cons->buf, buf, count);
	अगर (n < count)
		cons->missed += count - n;

	अगर (cons->req && !cons->req->length)
		schedule_work(&cons->work);

	spin_unlock_irqrestore(&cons->lock, flags);
पूर्ण

अटल काष्ठा tty_driver *gs_console_device(काष्ठा console *co, पूर्णांक *index)
अणु
	*index = co->index;
	वापस gs_tty_driver;
पूर्ण

अटल पूर्णांक gs_console_connect(काष्ठा gs_port *port)
अणु
	काष्ठा gs_console *cons = port->console;
	काष्ठा usb_request *req;
	काष्ठा usb_ep *ep;

	अगर (!cons)
		वापस 0;

	ep = port->port_usb->in;
	req = gs_alloc_req(ep, ep->maxpacket, GFP_ATOMIC);
	अगर (!req)
		वापस -ENOMEM;
	req->complete = gs_console_complete_out;
	req->context = cons;
	req->length = 0;

	spin_lock(&cons->lock);
	cons->req = req;
	cons->console.data = ep;
	spin_unlock(&cons->lock);

	pr_debug("ttyGS%d: console connected!\n", port->port_num);

	schedule_work(&cons->work);

	वापस 0;
पूर्ण

अटल व्योम gs_console_disconnect(काष्ठा gs_port *port)
अणु
	काष्ठा gs_console *cons = port->console;
	काष्ठा usb_request *req;
	काष्ठा usb_ep *ep;

	अगर (!cons)
		वापस;

	spin_lock(&cons->lock);

	req = cons->req;
	ep = cons->console.data;
	cons->req = शून्य;

	spin_unlock(&cons->lock);

	अगर (!req)
		वापस;

	usb_ep_dequeue(ep, req);
	gs_मुक्त_req(ep, req);
पूर्ण

अटल पूर्णांक gs_console_init(काष्ठा gs_port *port)
अणु
	काष्ठा gs_console *cons;
	पूर्णांक err;

	अगर (port->console)
		वापस 0;

	cons = kzalloc(माप(*port->console), GFP_KERNEL);
	अगर (!cons)
		वापस -ENOMEM;

	म_नकल(cons->console.name, "ttyGS");
	cons->console.ग_लिखो = gs_console_ग_लिखो;
	cons->console.device = gs_console_device;
	cons->console.flags = CON_PRINTBUFFER;
	cons->console.index = port->port_num;

	INIT_WORK(&cons->work, gs_console_work);
	spin_lock_init(&cons->lock);

	err = kfअगरo_alloc(&cons->buf, GS_CONSOLE_BUF_SIZE, GFP_KERNEL);
	अगर (err) अणु
		pr_err("ttyGS%d: allocate console buffer failed\n", port->port_num);
		kमुक्त(cons);
		वापस err;
	पूर्ण

	port->console = cons;
	रेजिस्टर_console(&cons->console);

	spin_lock_irq(&port->port_lock);
	अगर (port->port_usb)
		gs_console_connect(port);
	spin_unlock_irq(&port->port_lock);

	वापस 0;
पूर्ण

अटल व्योम gs_console_निकास(काष्ठा gs_port *port)
अणु
	काष्ठा gs_console *cons = port->console;

	अगर (!cons)
		वापस;

	unरेजिस्टर_console(&cons->console);

	spin_lock_irq(&port->port_lock);
	अगर (cons->req)
		gs_console_disconnect(port);
	spin_unlock_irq(&port->port_lock);

	cancel_work_sync(&cons->work);
	kfअगरo_मुक्त(&cons->buf);
	kमुक्त(cons);
	port->console = शून्य;
पूर्ण

sमाप_प्रकार gserial_set_console(अचिन्हित अक्षर port_num, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा gs_port *port;
	bool enable;
	पूर्णांक ret;

	ret = strtobool(page, &enable);
	अगर (ret)
		वापस ret;

	mutex_lock(&ports[port_num].lock);
	port = ports[port_num].port;

	अगर (WARN_ON(port == शून्य)) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (enable)
		ret = gs_console_init(port);
	अन्यथा
		gs_console_निकास(port);
out:
	mutex_unlock(&ports[port_num].lock);

	वापस ret < 0 ? ret : count;
पूर्ण
EXPORT_SYMBOL_GPL(gserial_set_console);

sमाप_प्रकार gserial_get_console(अचिन्हित अक्षर port_num, अक्षर *page)
अणु
	काष्ठा gs_port *port;
	sमाप_प्रकार ret;

	mutex_lock(&ports[port_num].lock);
	port = ports[port_num].port;

	अगर (WARN_ON(port == शून्य))
		ret = -ENXIO;
	अन्यथा
		ret = प्र_लिखो(page, "%u\n", !!port->console);

	mutex_unlock(&ports[port_num].lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gserial_get_console);

#अन्यथा

अटल पूर्णांक gs_console_connect(काष्ठा gs_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम gs_console_disconnect(काष्ठा gs_port *port)
अणु
पूर्ण

अटल पूर्णांक gs_console_init(काष्ठा gs_port *port)
अणु
	वापस -ENOSYS;
पूर्ण

अटल व्योम gs_console_निकास(काष्ठा gs_port *port)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक
gs_port_alloc(अचिन्हित port_num, काष्ठा usb_cdc_line_coding *coding)
अणु
	काष्ठा gs_port	*port;
	पूर्णांक		ret = 0;

	mutex_lock(&ports[port_num].lock);
	अगर (ports[port_num].port) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	port = kzalloc(माप(काष्ठा gs_port), GFP_KERNEL);
	अगर (port == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	tty_port_init(&port->port);
	spin_lock_init(&port->port_lock);
	init_रुकोqueue_head(&port->drain_रुको);
	init_रुकोqueue_head(&port->बंद_रुको);

	INIT_DELAYED_WORK(&port->push, gs_rx_push);

	INIT_LIST_HEAD(&port->पढ़ो_pool);
	INIT_LIST_HEAD(&port->पढ़ो_queue);
	INIT_LIST_HEAD(&port->ग_लिखो_pool);

	port->port_num = port_num;
	port->port_line_coding = *coding;

	ports[port_num].port = port;
out:
	mutex_unlock(&ports[port_num].lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gs_बंदd(काष्ठा gs_port *port)
अणु
	पूर्णांक cond;

	spin_lock_irq(&port->port_lock);
	cond = port->port.count == 0;
	spin_unlock_irq(&port->port_lock);

	वापस cond;
पूर्ण

अटल व्योम gserial_मुक्त_port(काष्ठा gs_port *port)
अणु
	cancel_delayed_work_sync(&port->push);
	/* रुको क्रम old खोलोs to finish */
	रुको_event(port->बंद_रुको, gs_बंदd(port));
	WARN_ON(port->port_usb != शून्य);
	tty_port_destroy(&port->port);
	kमुक्त(port);
पूर्ण

व्योम gserial_मुक्त_line(अचिन्हित अक्षर port_num)
अणु
	काष्ठा gs_port	*port;

	mutex_lock(&ports[port_num].lock);
	अगर (WARN_ON(!ports[port_num].port)) अणु
		mutex_unlock(&ports[port_num].lock);
		वापस;
	पूर्ण
	port = ports[port_num].port;
	gs_console_निकास(port);
	ports[port_num].port = शून्य;
	mutex_unlock(&ports[port_num].lock);

	gserial_मुक्त_port(port);
	tty_unरेजिस्टर_device(gs_tty_driver, port_num);
पूर्ण
EXPORT_SYMBOL_GPL(gserial_मुक्त_line);

पूर्णांक gserial_alloc_line_no_console(अचिन्हित अक्षर *line_num)
अणु
	काष्ठा usb_cdc_line_coding	coding;
	काष्ठा gs_port			*port;
	काष्ठा device			*tty_dev;
	पूर्णांक				ret;
	पूर्णांक				port_num;

	coding.dwDTERate = cpu_to_le32(9600);
	coding.bCharFormat = 8;
	coding.bParityType = USB_CDC_NO_PARITY;
	coding.bDataBits = USB_CDC_1_STOP_BITS;

	क्रम (port_num = 0; port_num < MAX_U_SERIAL_PORTS; port_num++) अणु
		ret = gs_port_alloc(port_num, &coding);
		अगर (ret == -EBUSY)
			जारी;
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण
	अगर (ret)
		वापस ret;

	/* ... and sysfs class devices, so mdev/udev make /dev/ttyGS* */

	port = ports[port_num].port;
	tty_dev = tty_port_रेजिस्टर_device(&port->port,
			gs_tty_driver, port_num, शून्य);
	अगर (IS_ERR(tty_dev)) अणु
		pr_err("%s: failed to register tty for port %d, err %ld\n",
				__func__, port_num, PTR_ERR(tty_dev));

		ret = PTR_ERR(tty_dev);
		mutex_lock(&ports[port_num].lock);
		ports[port_num].port = शून्य;
		mutex_unlock(&ports[port_num].lock);
		gserial_मुक्त_port(port);
		जाओ err;
	पूर्ण
	*line_num = port_num;
err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gserial_alloc_line_no_console);

पूर्णांक gserial_alloc_line(अचिन्हित अक्षर *line_num)
अणु
	पूर्णांक ret = gserial_alloc_line_no_console(line_num);

	अगर (!ret && !*line_num)
		gs_console_init(ports[*line_num].port);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gserial_alloc_line);

/**
 * gserial_connect - notअगरy TTY I/O glue that USB link is active
 * @gser: the function, set up with endpoपूर्णांकs and descriptors
 * @port_num: which port is active
 * Context: any (usually from irq)
 *
 * This is called activate endpoपूर्णांकs and let the TTY layer know that
 * the connection is active ... not unlike "carrier detect".  It won't
 * necessarily start I/O queues; unless the TTY is held खोलो by any
 * task, there would be no poपूर्णांक.  However, the endpoपूर्णांकs will be
 * activated so the USB host can perक्रमm I/O, subject to basic USB
 * hardware flow control.
 *
 * Caller needs to have set up the endpoपूर्णांकs and USB function in @dev
 * beक्रमe calling this, as well as the appropriate (speed-specअगरic)
 * endpoपूर्णांक descriptors, and also have allocate @port_num by calling
 * @gserial_alloc_line().
 *
 * Returns negative त्रुटि_सं or zero.
 * On success, ep->driver_data will be overwritten.
 */
पूर्णांक gserial_connect(काष्ठा gserial *gser, u8 port_num)
अणु
	काष्ठा gs_port	*port;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		status;

	अगर (port_num >= MAX_U_SERIAL_PORTS)
		वापस -ENXIO;

	port = ports[port_num].port;
	अगर (!port) अणु
		pr_err("serial line %d not allocated.\n", port_num);
		वापस -EINVAL;
	पूर्ण
	अगर (port->port_usb) अणु
		pr_err("serial line %d is in use.\n", port_num);
		वापस -EBUSY;
	पूर्ण

	/* activate the endpoपूर्णांकs */
	status = usb_ep_enable(gser->in);
	अगर (status < 0)
		वापस status;
	gser->in->driver_data = port;

	status = usb_ep_enable(gser->out);
	अगर (status < 0)
		जाओ fail_out;
	gser->out->driver_data = port;

	/* then tell the tty glue that I/O can work */
	spin_lock_irqsave(&port->port_lock, flags);
	gser->ioport = port;
	port->port_usb = gser;

	/* REVISIT unclear how best to handle this state...
	 * we करोn't really couple it with the Linux TTY.
	 */
	gser->port_line_coding = port->port_line_coding;

	/* REVISIT अगर रुकोing on "carrier detect", संकेत. */

	/* अगर it's alपढ़ोy खोलो, start I/O ... and notअगरy the serial
	 * protocol about खोलो/बंद status (connect/disconnect).
	 */
	अगर (port->port.count) अणु
		pr_debug("gserial_connect: start ttyGS%d\n", port->port_num);
		gs_start_io(port);
		अगर (gser->connect)
			gser->connect(gser);
	पूर्ण अन्यथा अणु
		अगर (gser->disconnect)
			gser->disconnect(gser);
	पूर्ण

	status = gs_console_connect(port);
	spin_unlock_irqrestore(&port->port_lock, flags);

	वापस status;

fail_out:
	usb_ep_disable(gser->in);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(gserial_connect);
/**
 * gserial_disconnect - notअगरy TTY I/O glue that USB link is inactive
 * @gser: the function, on which gserial_connect() was called
 * Context: any (usually from irq)
 *
 * This is called to deactivate endpoपूर्णांकs and let the TTY layer know
 * that the connection went inactive ... not unlike "hangup".
 *
 * On वापस, the state is as अगर gserial_connect() had never been called;
 * there is no active USB I/O on these endpoपूर्णांकs.
 */
व्योम gserial_disconnect(काष्ठा gserial *gser)
अणु
	काष्ठा gs_port	*port = gser->ioport;
	अचिन्हित दीर्घ	flags;

	अगर (!port)
		वापस;

	/* tell the TTY glue not to करो I/O here any more */
	spin_lock_irqsave(&port->port_lock, flags);

	gs_console_disconnect(port);

	/* REVISIT as above: how best to track this? */
	port->port_line_coding = gser->port_line_coding;

	port->port_usb = शून्य;
	gser->ioport = शून्य;
	अगर (port->port.count > 0) अणु
		wake_up_पूर्णांकerruptible(&port->drain_रुको);
		अगर (port->port.tty)
			tty_hangup(port->port.tty);
	पूर्ण
	port->suspended = false;
	spin_unlock_irqrestore(&port->port_lock, flags);

	/* disable endpoपूर्णांकs, पातing करोwn any active I/O */
	usb_ep_disable(gser->out);
	usb_ep_disable(gser->in);

	/* finally, मुक्त any unused/unusable I/O buffers */
	spin_lock_irqsave(&port->port_lock, flags);
	अगर (port->port.count == 0)
		kfअगरo_मुक्त(&port->port_ग_लिखो_buf);
	gs_मुक्त_requests(gser->out, &port->पढ़ो_pool, शून्य);
	gs_मुक्त_requests(gser->out, &port->पढ़ो_queue, शून्य);
	gs_मुक्त_requests(gser->in, &port->ग_लिखो_pool, शून्य);

	port->पढ़ो_allocated = port->पढ़ो_started =
		port->ग_लिखो_allocated = port->ग_लिखो_started = 0;

	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gserial_disconnect);

व्योम gserial_suspend(काष्ठा gserial *gser)
अणु
	काष्ठा gs_port	*port = gser->ioport;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&port->port_lock, flags);
	port->suspended = true;
	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gserial_suspend);

व्योम gserial_resume(काष्ठा gserial *gser)
अणु
	काष्ठा gs_port *port = gser->ioport;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&port->port_lock, flags);
	port->suspended = false;
	अगर (!port->start_delayed) अणु
		spin_unlock_irqrestore(&port->port_lock, flags);
		वापस;
	पूर्ण

	pr_debug("delayed start ttyGS%d\n", port->port_num);
	gs_start_io(port);
	अगर (gser->connect)
		gser->connect(gser);
	port->start_delayed = false;
	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gserial_resume);

अटल पूर्णांक userial_init(व्योम)
अणु
	अचिन्हित			i;
	पूर्णांक				status;

	gs_tty_driver = alloc_tty_driver(MAX_U_SERIAL_PORTS);
	अगर (!gs_tty_driver)
		वापस -ENOMEM;

	gs_tty_driver->driver_name = "g_serial";
	gs_tty_driver->name = "ttyGS";
	/* uses dynamically asचिन्हित dev_t values */

	gs_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	gs_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	gs_tty_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	gs_tty_driver->init_termios = tty_std_termios;

	/* 9600-8-N-1 ... matches शेषs expected by "usbser.sys" on
	 * MS-Winकरोws.  Otherwise, most of these flags shouldn't affect
	 * anything unless we were to actually hook up to a serial line.
	 */
	gs_tty_driver->init_termios.c_cflag =
			B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	gs_tty_driver->init_termios.c_ispeed = 9600;
	gs_tty_driver->init_termios.c_ospeed = 9600;

	tty_set_operations(gs_tty_driver, &gs_tty_ops);
	क्रम (i = 0; i < MAX_U_SERIAL_PORTS; i++)
		mutex_init(&ports[i].lock);

	/* export the driver ... */
	status = tty_रेजिस्टर_driver(gs_tty_driver);
	अगर (status) अणु
		pr_err("%s: cannot register, err %d\n",
				__func__, status);
		जाओ fail;
	पूर्ण

	pr_debug("%s: registered %d ttyGS* device%s\n", __func__,
			MAX_U_SERIAL_PORTS,
			(MAX_U_SERIAL_PORTS == 1) ? "" : "s");

	वापस status;
fail:
	put_tty_driver(gs_tty_driver);
	gs_tty_driver = शून्य;
	वापस status;
पूर्ण
module_init(userial_init);

अटल व्योम userial_cleanup(व्योम)
अणु
	tty_unरेजिस्टर_driver(gs_tty_driver);
	put_tty_driver(gs_tty_driver);
	gs_tty_driver = शून्य;
पूर्ण
module_निकास(userial_cleanup);

MODULE_LICENSE("GPL");
