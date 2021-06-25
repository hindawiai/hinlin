<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com)
 */

#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <यंत्र/atomic.h>
#समावेश <init.h>
#समावेश <irq_kern.h>
#समावेश <os.h>
#समावेश "port.h"

काष्ठा port_list अणु
	काष्ठा list_head list;
	atomic_t रुको_count;
	पूर्णांक has_connection;
	काष्ठा completion करोne;
	पूर्णांक port;
	पूर्णांक fd;
	spinlock_t lock;
	काष्ठा list_head pending;
	काष्ठा list_head connections;
पूर्ण;

काष्ठा port_dev अणु
	काष्ठा port_list *port;
	पूर्णांक helper_pid;
	पूर्णांक telnetd_pid;
पूर्ण;

काष्ठा connection अणु
	काष्ठा list_head list;
	पूर्णांक fd;
	पूर्णांक helper_pid;
	पूर्णांक socket[2];
	पूर्णांक telnetd_pid;
	काष्ठा port_list *port;
पूर्ण;

अटल irqवापस_t pipe_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा connection *conn = data;
	पूर्णांक fd;

	fd = os_rcv_fd(conn->socket[0], &conn->helper_pid);
	अगर (fd < 0) अणु
		अगर (fd == -EAGAIN)
			वापस IRQ_NONE;

		prपूर्णांकk(KERN_ERR "pipe_interrupt : os_rcv_fd returned %d\n",
		       -fd);
		os_बंद_file(conn->fd);
	पूर्ण

	list_del(&conn->list);

	conn->fd = fd;
	list_add(&conn->list, &conn->port->connections);

	complete(&conn->port->करोne);
	वापस IRQ_HANDLED;
पूर्ण

#घोषणा NO_WAITER_MSG \
    "****\n" \
    "There are currently no UML consoles waiting for port connections.\n" \
    "Either disconnect from one to make it available or activate some more\n" \
    "by enabling more consoles in the UML /etc/inittab.\n" \
    "****\n"

अटल पूर्णांक port_accept(काष्ठा port_list *port)
अणु
	काष्ठा connection *conn;
	पूर्णांक fd, socket[2], pid;

	fd = port_connection(port->fd, socket, &pid);
	अगर (fd < 0) अणु
		अगर (fd != -EAGAIN)
			prपूर्णांकk(KERN_ERR "port_accept : port_connection "
			       "returned %d\n", -fd);
		जाओ out;
	पूर्ण

	conn = kदो_स्मृति(माप(*conn), GFP_ATOMIC);
	अगर (conn == शून्य) अणु
		prपूर्णांकk(KERN_ERR "port_accept : failed to allocate "
		       "connection\n");
		जाओ out_बंद;
	पूर्ण
	*conn = ((काष्ठा connection)
		अणु .list 	= LIST_HEAD_INIT(conn->list),
		  .fd 		= fd,
		  .socket  	= अणु socket[0], socket[1] पूर्ण,
		  .telnetd_pid 	= pid,
		  .port 	= port पूर्ण);

	अगर (um_request_irq(TELNETD_IRQ, socket[0], IRQ_READ, pipe_पूर्णांकerrupt,
			  IRQF_SHARED, "telnetd", conn) < 0) अणु
		prपूर्णांकk(KERN_ERR "port_accept : failed to get IRQ for "
		       "telnetd\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (atomic_पढ़ो(&port->रुको_count) == 0) अणु
		os_ग_लिखो_file(fd, NO_WAITER_MSG, माप(NO_WAITER_MSG));
		prपूर्णांकk(KERN_ERR "No one waiting for port\n");
	पूर्ण
	list_add(&conn->list, &port->pending);
	वापस 1;

 out_मुक्त:
	kमुक्त(conn);
 out_बंद:
	os_बंद_file(fd);
	os_समाप्त_process(pid, 1);
 out:
	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(ports_mutex);
अटल LIST_HEAD(ports);

अटल व्योम port_work_proc(काष्ठा work_काष्ठा *unused)
अणु
	काष्ठा port_list *port;
	काष्ठा list_head *ele;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	list_क्रम_each(ele, &ports) अणु
		port = list_entry(ele, काष्ठा port_list, list);
		अगर (!port->has_connection)
			जारी;

		जबतक (port_accept(port))
			;
		port->has_connection = 0;
	पूर्ण
	local_irq_restore(flags);
पूर्ण

DECLARE_WORK(port_work, port_work_proc);

अटल irqवापस_t port_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा port_list *port = data;

	port->has_connection = 1;
	schedule_work(&port_work);
	वापस IRQ_HANDLED;
पूर्ण

व्योम *port_data(पूर्णांक port_num)
अणु
	काष्ठा list_head *ele;
	काष्ठा port_list *port;
	काष्ठा port_dev *dev = शून्य;
	पूर्णांक fd;

	mutex_lock(&ports_mutex);
	list_क्रम_each(ele, &ports) अणु
		port = list_entry(ele, काष्ठा port_list, list);
		अगर (port->port == port_num)
			जाओ found;
	पूर्ण
	port = kदो_स्मृति(माप(काष्ठा port_list), GFP_KERNEL);
	अगर (port == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Allocation of port list failed\n");
		जाओ out;
	पूर्ण

	fd = port_listen_fd(port_num);
	अगर (fd < 0) अणु
		prपूर्णांकk(KERN_ERR "binding to port %d failed, errno = %d\n",
		       port_num, -fd);
		जाओ out_मुक्त;
	पूर्ण

	अगर (um_request_irq(ACCEPT_IRQ, fd, IRQ_READ, port_पूर्णांकerrupt,
			  IRQF_SHARED, "port", port) < 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to get IRQ for port %d\n", port_num);
		जाओ out_बंद;
	पूर्ण

	*port = ((काष्ठा port_list)
		अणु .list 	 	= LIST_HEAD_INIT(port->list),
		  .रुको_count		= ATOMIC_INIT(0),
		  .has_connection 	= 0,
		  .port 	 	= port_num,
		  .fd  			= fd,
		  .pending 		= LIST_HEAD_INIT(port->pending),
		  .connections 		= LIST_HEAD_INIT(port->connections) पूर्ण);
	spin_lock_init(&port->lock);
	init_completion(&port->करोne);
	list_add(&port->list, &ports);

 found:
	dev = kदो_स्मृति(माप(काष्ठा port_dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Allocation of port device entry failed\n");
		जाओ out;
	पूर्ण

	*dev = ((काष्ठा port_dev) अणु .port  		= port,
				    .helper_pid  	= -1,
				    .telnetd_pid  	= -1 पूर्ण);
	जाओ out;

 out_बंद:
	os_बंद_file(fd);
 out_मुक्त:
	kमुक्त(port);
 out:
	mutex_unlock(&ports_mutex);
	वापस dev;
पूर्ण

पूर्णांक port_रुको(व्योम *data)
अणु
	काष्ठा port_dev *dev = data;
	काष्ठा connection *conn;
	काष्ठा port_list *port = dev->port;
	पूर्णांक fd;

	atomic_inc(&port->रुको_count);
	जबतक (1) अणु
		fd = -ERESTARTSYS;
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&port->करोne))
			जाओ out;

		spin_lock(&port->lock);

		conn = list_entry(port->connections.next, काष्ठा connection,
				  list);
		list_del(&conn->list);
		spin_unlock(&port->lock);

		os_shutकरोwn_socket(conn->socket[0], 1, 1);
		os_बंद_file(conn->socket[0]);
		os_shutकरोwn_socket(conn->socket[1], 1, 1);
		os_बंद_file(conn->socket[1]);

		/* This is करोne here because मुक्तing an IRQ can't be करोne
		 * within the IRQ handler.  So, pipe_पूर्णांकerrupt always ups
		 * the semaphore regardless of whether it got a successful
		 * connection.  Then we loop here throwing out failed
		 * connections until a good one is found.
		 */
		um_मुक्त_irq(TELNETD_IRQ, conn);

		अगर (conn->fd >= 0)
			अवरोध;
		os_बंद_file(conn->fd);
		kमुक्त(conn);
	पूर्ण

	fd = conn->fd;
	dev->helper_pid = conn->helper_pid;
	dev->telnetd_pid = conn->telnetd_pid;
	kमुक्त(conn);
 out:
	atomic_dec(&port->रुको_count);
	वापस fd;
पूर्ण

व्योम port_हटाओ_dev(व्योम *d)
अणु
	काष्ठा port_dev *dev = d;

	अगर (dev->helper_pid != -1)
		os_समाप्त_process(dev->helper_pid, 0);
	अगर (dev->telnetd_pid != -1)
		os_समाप्त_process(dev->telnetd_pid, 1);
	dev->helper_pid = -1;
	dev->telnetd_pid = -1;
पूर्ण

व्योम port_kern_मुक्त(व्योम *d)
अणु
	काष्ठा port_dev *dev = d;

	port_हटाओ_dev(dev);
	kमुक्त(dev);
पूर्ण

अटल व्योम मुक्त_port(व्योम)
अणु
	काष्ठा list_head *ele;
	काष्ठा port_list *port;

	list_क्रम_each(ele, &ports) अणु
		port = list_entry(ele, काष्ठा port_list, list);
		मुक्त_irq_by_fd(port->fd);
		os_बंद_file(port->fd);
	पूर्ण
पूर्ण

__uml_निकासcall(मुक्त_port);
