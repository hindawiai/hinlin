<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <termios.h>
#समावेश <unistd.h>
#समावेश <netinet/in.h>
#समावेश "chan_user.h"
#समावेश <os.h>
#समावेश "port.h"
#समावेश <um_दो_स्मृति.h>

काष्ठा port_chan अणु
	पूर्णांक raw;
	काष्ठा termios tt;
	व्योम *kernel_data;
	अक्षर dev[माप("32768\0")];
पूर्ण;

अटल व्योम *port_init(अक्षर *str, पूर्णांक device, स्थिर काष्ठा chan_opts *opts)
अणु
	काष्ठा port_chan *data;
	व्योम *kern_data;
	अक्षर *end;
	पूर्णांक port;

	अगर (*str != ':') अणु
		prपूर्णांकk(UM_KERN_ERR "port_init : channel type 'port' must "
		       "specify a port number\n");
		वापस शून्य;
	पूर्ण
	str++;
	port = म_से_अदीर्घ(str, &end, 0);
	अगर ((*end != '\0') || (end == str)) अणु
		prपूर्णांकk(UM_KERN_ERR "port_init : couldn't parse port '%s'\n",
		       str);
		वापस शून्य;
	पूर्ण

	kern_data = port_data(port);
	अगर (kern_data == शून्य)
		वापस शून्य;

	data = uml_kदो_स्मृति(माप(*data), UM_GFP_KERNEL);
	अगर (data == शून्य)
		जाओ err;

	*data = ((काष्ठा port_chan) अणु .raw  		= opts->raw,
				      .kernel_data 	= kern_data पूर्ण);
	प्र_लिखो(data->dev, "%d", port);

	वापस data;
 err:
	port_kern_मुक्त(kern_data);
	वापस शून्य;
पूर्ण

अटल व्योम port_मुक्त(व्योम *d)
अणु
	काष्ठा port_chan *data = d;

	port_kern_मुक्त(data->kernel_data);
	kमुक्त(data);
पूर्ण

अटल पूर्णांक port_खोलो(पूर्णांक input, पूर्णांक output, पूर्णांक primary, व्योम *d,
		     अक्षर **dev_out)
अणु
	काष्ठा port_chan *data = d;
	पूर्णांक fd, err;

	fd = port_रुको(data->kernel_data);
	अगर ((fd >= 0) && data->raw) अणु
		CATCH_EINTR(err = tcgetattr(fd, &data->tt));
		अगर (err)
			वापस err;

		err = raw(fd);
		अगर (err)
			वापस err;
	पूर्ण
	*dev_out = data->dev;
	वापस fd;
पूर्ण

अटल व्योम port_बंद(पूर्णांक fd, व्योम *d)
अणु
	काष्ठा port_chan *data = d;

	port_हटाओ_dev(data->kernel_data);
	os_बंद_file(fd);
पूर्ण

स्थिर काष्ठा chan_ops port_ops = अणु
	.type		= "port",
	.init		= port_init,
	.खोलो		= port_खोलो,
	.बंद		= port_बंद,
	.पढ़ो	        = generic_पढ़ो,
	.ग_लिखो		= generic_ग_लिखो,
	.console_ग_लिखो	= generic_console_ग_लिखो,
	.winकरोw_size	= generic_winकरोw_size,
	.मुक्त		= port_मुक्त,
	.winch		= 1,
पूर्ण;

पूर्णांक port_listen_fd(पूर्णांक port)
अणु
	काष्ठा sockaddr_in addr;
	पूर्णांक fd, err, arg;

	fd = socket(PF_INET, SOCK_STREAM, 0);
	अगर (fd == -1)
		वापस -त्रुटि_सं;

	arg = 1;
	अगर (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &arg, माप(arg)) < 0) अणु
		err = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	अगर (bind(fd, (काष्ठा sockaddr *) &addr, माप(addr)) < 0) अणु
		err = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	अगर (listen(fd, 1) < 0) अणु
		err = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	err = os_set_fd_block(fd, 0);
	अगर (err < 0)
		जाओ out;

	वापस fd;
 out:
	बंद(fd);
	वापस err;
पूर्ण

काष्ठा port_pre_exec_data अणु
	पूर्णांक sock_fd;
	पूर्णांक pipe_fd;
पूर्ण;

अटल व्योम port_pre_exec(व्योम *arg)
अणु
	काष्ठा port_pre_exec_data *data = arg;

	dup2(data->sock_fd, 0);
	dup2(data->sock_fd, 1);
	dup2(data->sock_fd, 2);
	बंद(data->sock_fd);
	dup2(data->pipe_fd, 3);
	shutकरोwn(3, SHUT_RD);
	बंद(data->pipe_fd);
पूर्ण

पूर्णांक port_connection(पूर्णांक fd, पूर्णांक *socket, पूर्णांक *pid_out)
अणु
	पूर्णांक new, err;
	अक्षर *argv[] = अणु "/usr/sbin/in.telnetd", "-L",
			 OS_LIB_PATH "/uml/port-helper", शून्य पूर्ण;
	काष्ठा port_pre_exec_data data;

	new = accept(fd, शून्य, 0);
	अगर (new < 0)
		वापस -त्रुटि_सं;

	err = os_pipe(socket, 0, 0);
	अगर (err < 0)
		जाओ out_बंद;

	data = ((काष्ठा port_pre_exec_data)
		अणु .sock_fd  		= new,
		  .pipe_fd 		= socket[1] पूर्ण);

	err = run_helper(port_pre_exec, &data, argv);
	अगर (err < 0)
		जाओ out_shutकरोwn;

	*pid_out = err;
	वापस new;

 out_shutकरोwn:
	shutकरोwn(socket[0], SHUT_RDWR);
	बंद(socket[0]);
	shutकरोwn(socket[1], SHUT_RDWR);
	बंद(socket[1]);
 out_बंद:
	बंद(new);
	वापस err;
पूर्ण
