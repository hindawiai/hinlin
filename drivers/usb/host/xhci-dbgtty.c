<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xhci-dbgtty.c - tty glue क्रम xHCI debug capability
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#समावेश "xhci.h"
#समावेश "xhci-dbgcap.h"

अटल पूर्णांक dbc_tty_init(व्योम);
अटल व्योम dbc_tty_निकास(व्योम);

अटल काष्ठा tty_driver *dbc_tty_driver;

अटल अंतरभूत काष्ठा dbc_port *dbc_to_port(काष्ठा xhci_dbc *dbc)
अणु
	वापस dbc->priv;
पूर्ण

अटल अचिन्हित पूर्णांक
dbc_send_packet(काष्ठा dbc_port *port, अक्षर *packet, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक		len;

	len = kfअगरo_len(&port->ग_लिखो_fअगरo);
	अगर (len < size)
		size = len;
	अगर (size != 0)
		size = kfअगरo_out(&port->ग_लिखो_fअगरo, packet, size);
	वापस size;
पूर्ण

अटल पूर्णांक dbc_start_tx(काष्ठा dbc_port *port)
	__releases(&port->port_lock)
	__acquires(&port->port_lock)
अणु
	पूर्णांक			len;
	काष्ठा dbc_request	*req;
	पूर्णांक			status = 0;
	bool			करो_tty_wake = false;
	काष्ठा list_head	*pool = &port->ग_लिखो_pool;

	जबतक (!list_empty(pool)) अणु
		req = list_entry(pool->next, काष्ठा dbc_request, list_pool);
		len = dbc_send_packet(port, req->buf, DBC_MAX_PACKET);
		अगर (len == 0)
			अवरोध;
		करो_tty_wake = true;

		req->length = len;
		list_del(&req->list_pool);

		spin_unlock(&port->port_lock);
		status = dbc_ep_queue(req);
		spin_lock(&port->port_lock);

		अगर (status) अणु
			list_add(&req->list_pool, pool);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (करो_tty_wake && port->port.tty)
		tty_wakeup(port->port.tty);

	वापस status;
पूर्ण

अटल व्योम dbc_start_rx(काष्ठा dbc_port *port)
	__releases(&port->port_lock)
	__acquires(&port->port_lock)
अणु
	काष्ठा dbc_request	*req;
	पूर्णांक			status;
	काष्ठा list_head	*pool = &port->पढ़ो_pool;

	जबतक (!list_empty(pool)) अणु
		अगर (!port->port.tty)
			अवरोध;

		req = list_entry(pool->next, काष्ठा dbc_request, list_pool);
		list_del(&req->list_pool);
		req->length = DBC_MAX_PACKET;

		spin_unlock(&port->port_lock);
		status = dbc_ep_queue(req);
		spin_lock(&port->port_lock);

		अगर (status) अणु
			list_add(&req->list_pool, pool);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
dbc_पढ़ो_complete(काष्ठा xhci_dbc *dbc, काष्ठा dbc_request *req)
अणु
	अचिन्हित दीर्घ		flags;
	काष्ठा dbc_port		*port = dbc_to_port(dbc);

	spin_lock_irqsave(&port->port_lock, flags);
	list_add_tail(&req->list_pool, &port->पढ़ो_queue);
	tasklet_schedule(&port->push);
	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण

अटल व्योम dbc_ग_लिखो_complete(काष्ठा xhci_dbc *dbc, काष्ठा dbc_request *req)
अणु
	अचिन्हित दीर्घ		flags;
	काष्ठा dbc_port		*port = dbc_to_port(dbc);

	spin_lock_irqsave(&port->port_lock, flags);
	list_add(&req->list_pool, &port->ग_लिखो_pool);
	चयन (req->status) अणु
	हाल 0:
		dbc_start_tx(port);
		अवरोध;
	हाल -ESHUTDOWN:
		अवरोध;
	शेष:
		dev_warn(dbc->dev, "unexpected write complete status %d\n",
			  req->status);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण

अटल व्योम xhci_dbc_मुक्त_req(काष्ठा dbc_request *req)
अणु
	kमुक्त(req->buf);
	dbc_मुक्त_request(req);
पूर्ण

अटल पूर्णांक
xhci_dbc_alloc_requests(काष्ठा xhci_dbc *dbc, अचिन्हित पूर्णांक direction,
			काष्ठा list_head *head,
			व्योम (*fn)(काष्ठा xhci_dbc *, काष्ठा dbc_request *))
अणु
	पूर्णांक			i;
	काष्ठा dbc_request	*req;

	क्रम (i = 0; i < DBC_QUEUE_SIZE; i++) अणु
		req = dbc_alloc_request(dbc, direction, GFP_KERNEL);
		अगर (!req)
			अवरोध;

		req->length = DBC_MAX_PACKET;
		req->buf = kदो_स्मृति(req->length, GFP_KERNEL);
		अगर (!req->buf) अणु
			dbc_मुक्त_request(req);
			अवरोध;
		पूर्ण

		req->complete = fn;
		list_add_tail(&req->list_pool, head);
	पूर्ण

	वापस list_empty(head) ? -ENOMEM : 0;
पूर्ण

अटल व्योम
xhci_dbc_मुक्त_requests(काष्ठा list_head *head)
अणु
	काष्ठा dbc_request	*req;

	जबतक (!list_empty(head)) अणु
		req = list_entry(head->next, काष्ठा dbc_request, list_pool);
		list_del(&req->list_pool);
		xhci_dbc_मुक्त_req(req);
	पूर्ण
पूर्ण

अटल पूर्णांक dbc_tty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा dbc_port		*port = driver->driver_state;

	tty->driver_data = port;

	वापस tty_port_install(&port->port, driver, tty);
पूर्ण

अटल पूर्णांक dbc_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा dbc_port		*port = tty->driver_data;

	वापस tty_port_खोलो(&port->port, tty, file);
पूर्ण

अटल व्योम dbc_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा dbc_port		*port = tty->driver_data;

	tty_port_बंद(&port->port, tty, file);
पूर्ण

अटल पूर्णांक dbc_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty,
			 स्थिर अचिन्हित अक्षर *buf,
			 पूर्णांक count)
अणु
	काष्ठा dbc_port		*port = tty->driver_data;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&port->port_lock, flags);
	अगर (count)
		count = kfअगरo_in(&port->ग_लिखो_fअगरo, buf, count);
	dbc_start_tx(port);
	spin_unlock_irqrestore(&port->port_lock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक dbc_tty_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	काष्ठा dbc_port		*port = tty->driver_data;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			status;

	spin_lock_irqsave(&port->port_lock, flags);
	status = kfअगरo_put(&port->ग_लिखो_fअगरo, ch);
	spin_unlock_irqrestore(&port->port_lock, flags);

	वापस status;
पूर्ण

अटल व्योम dbc_tty_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा dbc_port		*port = tty->driver_data;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&port->port_lock, flags);
	dbc_start_tx(port);
	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण

अटल पूर्णांक dbc_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा dbc_port		*port = tty->driver_data;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			room = 0;

	spin_lock_irqsave(&port->port_lock, flags);
	room = kfअगरo_avail(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&port->port_lock, flags);

	वापस room;
पूर्ण

अटल पूर्णांक dbc_tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा dbc_port		*port = tty->driver_data;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			अक्षरs = 0;

	spin_lock_irqsave(&port->port_lock, flags);
	अक्षरs = kfअगरo_len(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&port->port_lock, flags);

	वापस अक्षरs;
पूर्ण

अटल व्योम dbc_tty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा dbc_port		*port = tty->driver_data;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&port->port_lock, flags);
	tasklet_schedule(&port->push);
	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण

अटल स्थिर काष्ठा tty_operations dbc_tty_ops = अणु
	.install		= dbc_tty_install,
	.खोलो			= dbc_tty_खोलो,
	.बंद			= dbc_tty_बंद,
	.ग_लिखो			= dbc_tty_ग_लिखो,
	.put_अक्षर		= dbc_tty_put_अक्षर,
	.flush_अक्षरs		= dbc_tty_flush_अक्षरs,
	.ग_लिखो_room		= dbc_tty_ग_लिखो_room,
	.अक्षरs_in_buffer	= dbc_tty_अक्षरs_in_buffer,
	.unthrottle		= dbc_tty_unthrottle,
पूर्ण;

अटल व्योम dbc_rx_push(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा dbc_request	*req;
	काष्ठा tty_काष्ठा	*tty;
	अचिन्हित दीर्घ		flags;
	bool			करो_push = false;
	bool			disconnect = false;
	काष्ठा dbc_port		*port = from_tasklet(port, t, push);
	काष्ठा list_head	*queue = &port->पढ़ो_queue;

	spin_lock_irqsave(&port->port_lock, flags);
	tty = port->port.tty;
	जबतक (!list_empty(queue)) अणु
		req = list_first_entry(queue, काष्ठा dbc_request, list_pool);

		अगर (tty && tty_throttled(tty))
			अवरोध;

		चयन (req->status) अणु
		हाल 0:
			अवरोध;
		हाल -ESHUTDOWN:
			disconnect = true;
			अवरोध;
		शेष:
			pr_warn("ttyDBC0: unexpected RX status %d\n",
				req->status);
			अवरोध;
		पूर्ण

		अगर (req->actual) अणु
			अक्षर		*packet = req->buf;
			अचिन्हित पूर्णांक	n, size = req->actual;
			पूर्णांक		count;

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
				port->n_पढ़ो += count;
				अवरोध;
			पूर्ण
			port->n_पढ़ो = 0;
		पूर्ण

		list_move(&req->list_pool, &port->पढ़ो_pool);
	पूर्ण

	अगर (करो_push)
		tty_flip_buffer_push(&port->port);

	अगर (!list_empty(queue) && tty) अणु
		अगर (!tty_throttled(tty)) अणु
			अगर (करो_push)
				tasklet_schedule(&port->push);
			अन्यथा
				pr_warn("ttyDBC0: RX not scheduled?\n");
		पूर्ण
	पूर्ण

	अगर (!disconnect)
		dbc_start_rx(port);

	spin_unlock_irqrestore(&port->port_lock, flags);
पूर्ण

अटल पूर्णांक dbc_port_activate(काष्ठा tty_port *_port, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ	flags;
	काष्ठा dbc_port	*port = container_of(_port, काष्ठा dbc_port, port);

	spin_lock_irqsave(&port->port_lock, flags);
	dbc_start_rx(port);
	spin_unlock_irqrestore(&port->port_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tty_port_operations dbc_port_ops = अणु
	.activate =	dbc_port_activate,
पूर्ण;

अटल व्योम
xhci_dbc_tty_init_port(काष्ठा xhci_dbc *dbc, काष्ठा dbc_port *port)
अणु
	tty_port_init(&port->port);
	spin_lock_init(&port->port_lock);
	tasklet_setup(&port->push, dbc_rx_push);
	INIT_LIST_HEAD(&port->पढ़ो_pool);
	INIT_LIST_HEAD(&port->पढ़ो_queue);
	INIT_LIST_HEAD(&port->ग_लिखो_pool);

	port->port.ops =	&dbc_port_ops;
	port->n_पढ़ो =		0;
पूर्ण

अटल व्योम
xhci_dbc_tty_निकास_port(काष्ठा dbc_port *port)
अणु
	tasklet_समाप्त(&port->push);
	tty_port_destroy(&port->port);
पूर्ण

अटल पूर्णांक xhci_dbc_tty_रेजिस्टर_device(काष्ठा xhci_dbc *dbc)
अणु
	पूर्णांक			ret;
	काष्ठा device		*tty_dev;
	काष्ठा dbc_port		*port = dbc_to_port(dbc);

	अगर (port->रेजिस्टरed)
		वापस -EBUSY;

	xhci_dbc_tty_init_port(dbc, port);
	tty_dev = tty_port_रेजिस्टर_device(&port->port,
					   dbc_tty_driver, 0, शून्य);
	अगर (IS_ERR(tty_dev)) अणु
		ret = PTR_ERR(tty_dev);
		जाओ रेजिस्टर_fail;
	पूर्ण

	ret = kfअगरo_alloc(&port->ग_लिखो_fअगरo, DBC_WRITE_BUF_SIZE, GFP_KERNEL);
	अगर (ret)
		जाओ buf_alloc_fail;

	ret = xhci_dbc_alloc_requests(dbc, BULK_IN, &port->पढ़ो_pool,
				      dbc_पढ़ो_complete);
	अगर (ret)
		जाओ request_fail;

	ret = xhci_dbc_alloc_requests(dbc, BULK_OUT, &port->ग_लिखो_pool,
				      dbc_ग_लिखो_complete);
	अगर (ret)
		जाओ request_fail;

	port->रेजिस्टरed = true;

	वापस 0;

request_fail:
	xhci_dbc_मुक्त_requests(&port->पढ़ो_pool);
	xhci_dbc_मुक्त_requests(&port->ग_लिखो_pool);
	kfअगरo_मुक्त(&port->ग_लिखो_fअगरo);

buf_alloc_fail:
	tty_unरेजिस्टर_device(dbc_tty_driver, 0);

रेजिस्टर_fail:
	xhci_dbc_tty_निकास_port(port);

	dev_err(dbc->dev, "can't register tty port, err %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम xhci_dbc_tty_unरेजिस्टर_device(काष्ठा xhci_dbc *dbc)
अणु
	काष्ठा dbc_port		*port = dbc_to_port(dbc);

	अगर (!port->रेजिस्टरed)
		वापस;
	tty_unरेजिस्टर_device(dbc_tty_driver, 0);
	xhci_dbc_tty_निकास_port(port);
	port->रेजिस्टरed = false;

	kfअगरo_मुक्त(&port->ग_लिखो_fअगरo);
	xhci_dbc_मुक्त_requests(&port->पढ़ो_pool);
	xhci_dbc_मुक्त_requests(&port->पढ़ो_queue);
	xhci_dbc_मुक्त_requests(&port->ग_लिखो_pool);
पूर्ण

अटल स्थिर काष्ठा dbc_driver dbc_driver = अणु
	.configure		= xhci_dbc_tty_रेजिस्टर_device,
	.disconnect		= xhci_dbc_tty_unरेजिस्टर_device,
पूर्ण;

पूर्णांक xhci_dbc_tty_probe(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा xhci_dbc		*dbc = xhci->dbc;
	काष्ठा dbc_port		*port;
	पूर्णांक			status;

	/* dbc_tty_init will be called by module init() in the future */
	status = dbc_tty_init();
	अगर (status)
		वापस status;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port) अणु
		status = -ENOMEM;
		जाओ out;
	पूर्ण

	dbc->driver = &dbc_driver;
	dbc->priv = port;


	dbc_tty_driver->driver_state = port;

	वापस 0;
out:
	/* dbc_tty_निकास will be called by module_निकास() in the future */
	dbc_tty_निकास();
	वापस status;
पूर्ण

/*
 * unकरो what probe did, assume dbc is stopped alपढ़ोy.
 * we also assume tty_unरेजिस्टर_device() is called beक्रमe this
 */
व्योम xhci_dbc_tty_हटाओ(काष्ठा xhci_dbc *dbc)
अणु
	काष्ठा dbc_port         *port = dbc_to_port(dbc);

	dbc->driver = शून्य;
	dbc->priv = शून्य;
	kमुक्त(port);

	/* dbc_tty_निकास will be called by  module_निकास() in the future */
	dbc_tty_निकास();
पूर्ण

अटल पूर्णांक dbc_tty_init(व्योम)
अणु
	पूर्णांक		ret;

	dbc_tty_driver = tty_alloc_driver(1, TTY_DRIVER_REAL_RAW |
					  TTY_DRIVER_DYNAMIC_DEV);
	अगर (IS_ERR(dbc_tty_driver))
		वापस PTR_ERR(dbc_tty_driver);

	dbc_tty_driver->driver_name = "dbc_serial";
	dbc_tty_driver->name = "ttyDBC";

	dbc_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	dbc_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	dbc_tty_driver->init_termios = tty_std_termios;
	dbc_tty_driver->init_termios.c_cflag =
			B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	dbc_tty_driver->init_termios.c_ispeed = 9600;
	dbc_tty_driver->init_termios.c_ospeed = 9600;

	tty_set_operations(dbc_tty_driver, &dbc_tty_ops);

	ret = tty_रेजिस्टर_driver(dbc_tty_driver);
	अगर (ret) अणु
		pr_err("Can't register dbc tty driver\n");
		put_tty_driver(dbc_tty_driver);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम dbc_tty_निकास(व्योम)
अणु
	अगर (dbc_tty_driver) अणु
		tty_unरेजिस्टर_driver(dbc_tty_driver);
		put_tty_driver(dbc_tty_driver);
		dbc_tty_driver = शून्य;
	पूर्ण
पूर्ण
