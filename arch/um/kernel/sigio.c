<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com)
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <irq_kern.h>
#समावेश <os.h>
#समावेश <sigपन.स>

/* Protected by sigio_lock() called from ग_लिखो_sigio_workaround */
अटल पूर्णांक sigio_irq_fd = -1;

अटल irqवापस_t sigio_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	अक्षर c;

	os_पढ़ो_file(sigio_irq_fd, &c, माप(c));
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक ग_लिखो_sigio_irq(पूर्णांक fd)
अणु
	पूर्णांक err;

	err = um_request_irq(SIGIO_WRITE_IRQ, fd, IRQ_READ, sigio_पूर्णांकerrupt,
			     0, "write sigio", शून्य);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "write_sigio_irq : um_request_irq failed, "
		       "err = %d\n", err);
		वापस -1;
	पूर्ण
	sigio_irq_fd = fd;
	वापस 0;
पूर्ण

/* These are called from os-Linux/sigio.c to protect its pollfds arrays. */
अटल DEFINE_MUTEX(sigio_mutex);

व्योम sigio_lock(व्योम)
अणु
	mutex_lock(&sigio_mutex);
पूर्ण

व्योम sigio_unlock(व्योम)
अणु
	mutex_unlock(&sigio_mutex);
पूर्ण
