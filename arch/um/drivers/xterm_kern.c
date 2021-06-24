<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* 
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/irqवापस.h>
#समावेश <यंत्र/irq.h>
#समावेश <irq_kern.h>
#समावेश <os.h>

काष्ठा xterm_रुको अणु
	काष्ठा completion पढ़ोy;
	पूर्णांक fd;
	पूर्णांक pid;
	पूर्णांक new_fd;
पूर्ण;

अटल irqवापस_t xterm_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xterm_रुको *xterm = data;
	पूर्णांक fd;

	fd = os_rcv_fd(xterm->fd, &xterm->pid);
	अगर (fd == -EAGAIN)
		वापस IRQ_NONE;

	xterm->new_fd = fd;
	complete(&xterm->पढ़ोy);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक xterm_fd(पूर्णांक socket, पूर्णांक *pid_out)
अणु
	काष्ठा xterm_रुको *data;
	पूर्णांक err, ret;

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (data == शून्य) अणु
		prपूर्णांकk(KERN_ERR "xterm_fd : failed to allocate xterm_wait\n");
		वापस -ENOMEM;
	पूर्ण

	/* This is a locked semaphore... */
	*data = ((काष्ठा xterm_रुको) अणु .fd 		= socket,
				       .pid 		= -1,
				       .new_fd	 	= -1 पूर्ण);
	init_completion(&data->पढ़ोy);

	err = um_request_irq(XTERM_IRQ, socket, IRQ_READ, xterm_पूर्णांकerrupt,
			     IRQF_SHARED, "xterm", data);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "xterm_fd : failed to get IRQ for xterm, "
		       "err = %d\n",  err);
		ret = err;
		जाओ out;
	पूर्ण

	/* ... so here we रुको क्रम an xterm पूर्णांकerrupt.
	 *
	 * XXX Note, अगर the xterm करोesn't work क्रम some reason (eg. DISPLAY
	 * isn't set) this will hang... */
	रुको_क्रम_completion(&data->पढ़ोy);

	um_मुक्त_irq(XTERM_IRQ, data);

	ret = data->new_fd;
	*pid_out = data->pid;
 out:
	kमुक्त(data);

	वापस ret;
पूर्ण
