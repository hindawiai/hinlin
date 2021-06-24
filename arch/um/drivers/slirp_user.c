<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <sys/रुको.h>
#समावेश <net_user.h>
#समावेश <os.h>
#समावेश "slirp.h"

अटल पूर्णांक slirp_user_init(व्योम *data, व्योम *dev)
अणु
	काष्ठा slirp_data *pri = data;

	pri->dev = dev;
	वापस 0;
पूर्ण

काष्ठा slirp_pre_exec_data अणु
	पूर्णांक मानक_निवेश_fd;
	पूर्णांक मानक_निकास_fd;
पूर्ण;

अटल व्योम slirp_pre_exec(व्योम *arg)
अणु
	काष्ठा slirp_pre_exec_data *data = arg;

	अगर (data->मानक_निवेश_fd != -1)
		dup2(data->मानक_निवेश_fd, 0);
	अगर (data->मानक_निकास_fd != -1)
		dup2(data->मानक_निकास_fd, 1);
पूर्ण

अटल पूर्णांक slirp_tramp(अक्षर **argv, पूर्णांक fd)
अणु
	काष्ठा slirp_pre_exec_data pe_data;
	पूर्णांक pid;

	pe_data.मानक_निवेश_fd = fd;
	pe_data.मानक_निकास_fd = fd;
	pid = run_helper(slirp_pre_exec, &pe_data, argv);

	वापस pid;
पूर्ण

अटल पूर्णांक slirp_खोलो(व्योम *data)
अणु
	काष्ठा slirp_data *pri = data;
	पूर्णांक fds[2], pid, err;

	err = os_pipe(fds, 1, 1);
	अगर (err)
		वापस err;

	err = slirp_tramp(pri->argw.argv, fds[1]);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "slirp_tramp failed - errno = %d\n", -err);
		जाओ out;
	पूर्ण
	pid = err;

	pri->slave = fds[1];
	pri->slip.pos = 0;
	pri->slip.esc = 0;
	pri->pid = err;

	वापस fds[0];
out:
	बंद(fds[0]);
	बंद(fds[1]);
	वापस err;
पूर्ण

अटल व्योम slirp_बंद(पूर्णांक fd, व्योम *data)
अणु
	काष्ठा slirp_data *pri = data;
	पूर्णांक err;

	बंद(fd);
	बंद(pri->slave);

	pri->slave = -1;

	अगर (pri->pid<1) अणु
		prपूर्णांकk(UM_KERN_ERR "slirp_close: no child process to shut "
		       "down\n");
		वापस;
	पूर्ण

#अगर 0
	अगर (समाप्त(pri->pid, SIGHUP)<0) अणु
		prपूर्णांकk(UM_KERN_ERR "slirp_close: sending hangup to %d failed "
		       "(%d)\n", pri->pid, त्रुटि_सं);
	पूर्ण
#पूर्ण_अगर
	err = helper_रुको(pri->pid);
	अगर (err < 0)
		वापस;

	pri->pid = -1;
पूर्ण

पूर्णांक slirp_user_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा slirp_data *pri)
अणु
	वापस slip_proto_पढ़ो(fd, buf, len, &pri->slip);
पूर्ण

पूर्णांक slirp_user_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा slirp_data *pri)
अणु
	वापस slip_proto_ग_लिखो(fd, buf, len, &pri->slip);
पूर्ण

स्थिर काष्ठा net_user_info slirp_user_info = अणु
	.init		= slirp_user_init,
	.खोलो		= slirp_खोलो,
	.बंद	 	= slirp_बंद,
	.हटाओ	 	= शून्य,
	.add_address	= शून्य,
	.delete_address = शून्य,
	.mtu		= BUF_SIZE,
	.max_packet	= BUF_SIZE,
पूर्ण;
