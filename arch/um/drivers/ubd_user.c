<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 Anton Ivanov (aivanov@brocade.com)
 * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)
 * Copyright (C) 2001 Ridgerun,Inc (glonnon@ridgerun.com)
 */

#समावेश <मानकघोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <netinet/in.h>
#समावेश <sys/समय.स>
#समावेश <sys/socket.h>
#समावेश <sys/mman.h>
#समावेश <sys/param.h>
#समावेश <endian.h>
#समावेश <byteswap.h>

#समावेश "ubd.h"
#समावेश <os.h>
#समावेश <poll.h>

काष्ठा pollfd kernel_pollfd;

पूर्णांक start_io_thपढ़ो(अचिन्हित दीर्घ sp, पूर्णांक *fd_out)
अणु
	पूर्णांक pid, fds[2], err;

	err = os_pipe(fds, 1, 1);
	अगर(err < 0)अणु
		prपूर्णांकk("start_io_thread - os_pipe failed, err = %d\n", -err);
		जाओ out;
	पूर्ण

	kernel_fd = fds[0];
	kernel_pollfd.fd = kernel_fd;
	kernel_pollfd.events = POLLIN;
	*fd_out = fds[1];

	err = os_set_fd_block(*fd_out, 0);
	err = os_set_fd_block(kernel_fd, 0);
	अगर (err) अणु
		prपूर्णांकk("start_io_thread - failed to set nonblocking I/O.\n");
		जाओ out_बंद;
	पूर्ण

	pid = clone(io_thपढ़ो, (व्योम *) sp, CLONE_खाताS | CLONE_VM, शून्य);
	अगर(pid < 0)अणु
		err = -त्रुटि_सं;
		prपूर्णांकk("start_io_thread - clone failed : errno = %d\n", त्रुटि_सं);
		जाओ out_बंद;
	पूर्ण

	वापस(pid);

 out_बंद:
	os_बंद_file(fds[0]);
	os_बंद_file(fds[1]);
	kernel_fd = -1;
	*fd_out = -1;
 out:
	वापस err;
पूर्ण

पूर्णांक ubd_पढ़ो_poll(पूर्णांक समयout)
अणु
	kernel_pollfd.events = POLLIN;
	वापस poll(&kernel_pollfd, 1, समयout);
पूर्ण
पूर्णांक ubd_ग_लिखो_poll(पूर्णांक समयout)
अणु
	kernel_pollfd.events = POLLOUT;
	वापस poll(&kernel_pollfd, 1, समयout);
पूर्ण

