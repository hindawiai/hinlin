<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <termios.h>
#समावेश "chan_user.h"
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>
#समावेश "xterm.h"

काष्ठा xterm_chan अणु
	पूर्णांक pid;
	पूर्णांक helper_pid;
	पूर्णांक chan_fd;
	अक्षर *title;
	पूर्णांक device;
	पूर्णांक raw;
	काष्ठा termios tt;
पूर्ण;

अटल व्योम *xterm_init(अक्षर *str, पूर्णांक device, स्थिर काष्ठा chan_opts *opts)
अणु
	काष्ठा xterm_chan *data;

	data = uml_kदो_स्मृति(माप(*data), UM_GFP_KERNEL);
	अगर (data == शून्य)
		वापस शून्य;
	*data = ((काष्ठा xterm_chan) अणु .pid 		= -1,
				       .helper_pid 	= -1,
				       .chan_fd		= -1,
				       .device 		= device,
				       .title 		= opts->xterm_title,
				       .raw  		= opts->raw पूर्ण );
	वापस data;
पूर्ण

/* Only changed by xterm_setup, which is a setup */
अटल अक्षर *terminal_emulator = "xterm";
अटल अक्षर *title_चयन = "-T";
अटल अक्षर *exec_चयन = "-e";

अटल पूर्णांक __init xterm_setup(अक्षर *line, पूर्णांक *add)
अणु
	*add = 0;
	terminal_emulator = line;

	line = म_अक्षर(line, ',');
	अगर (line == शून्य)
		वापस 0;

	*line++ = '\0';
	अगर (*line)
		title_चयन = line;

	line = म_अक्षर(line, ',');
	अगर (line == शून्य)
		वापस 0;

	*line++ = '\0';
	अगर (*line)
		exec_चयन = line;

	वापस 0;
पूर्ण

__uml_setup("xterm=", xterm_setup,
"xterm=<terminal emulator>,<title switch>,<exec switch>\n"
"    Specifies an alternate terminal emulator to use for the debugger,\n"
"    consoles, and serial lines when they are attached to the xterm channel.\n"
"    The values are the terminal emulator binary, the switch it uses to set\n"
"    its title, and the switch it uses to execute a subprocess,\n"
"    respectively.  The title switch must have the form '<switch> title',\n"
"    not '<switch>=title'.  Similarly, the exec switch must have the form\n"
"    '<switch> command arg1 arg2 ...'.\n"
"    The default values are 'xterm=xterm,-T,-e'.  Values for gnome-terminal\n"
"    are 'xterm=gnome-terminal,-t,-x'.\n\n"
);

अटल पूर्णांक xterm_खोलो(पूर्णांक input, पूर्णांक output, पूर्णांक primary, व्योम *d,
		      अक्षर **dev_out)
अणु
	काष्ठा xterm_chan *data = d;
	पूर्णांक pid, fd, new, err;
	अक्षर title[256], file[] = "/tmp/xterm-pipeXXXXXX";
	अक्षर *argv[] = अणु terminal_emulator, title_चयन, title, exec_चयन,
			 OS_LIB_PATH "/uml/port-helper", "-uml-socket",
			 file, शून्य पूर्ण;

	अगर (access(argv[4], X_OK) < 0)
		argv[4] = "port-helper";

	/*
	 * Check that DISPLAY is set, this करोesn't guarantee the xterm
	 * will work but w/o it we can be pretty sure it won't.
	 */
	अगर (दो_पर्या("DISPLAY") == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "xterm_open: $DISPLAY not set.\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * This business of getting a descriptor to a temp file,
	 * deleting the file and closing the descriptor is just to get
	 * a known-unused name क्रम the Unix socket that we really
	 * want.
	 */
	fd = mkstemp(file);
	अगर (fd < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "xterm_open : mkstemp failed, errno = %d\n",
		       त्रुटि_सं);
		वापस err;
	पूर्ण

	अगर (unlink(file)) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "xterm_open : unlink failed, errno = %d\n",
		       त्रुटि_सं);
		बंद(fd);
		वापस err;
	पूर्ण
	बंद(fd);

	fd = os_create_unix_socket(file, माप(file), 1);
	अगर (fd < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "xterm_open : create_unix_socket failed, "
		       "errno = %d\n", -fd);
		वापस fd;
	पूर्ण

	प्र_लिखो(title, data->title, data->device);
	pid = run_helper(शून्य, शून्य, argv);
	अगर (pid < 0) अणु
		err = pid;
		prपूर्णांकk(UM_KERN_ERR "xterm_open : run_helper failed, "
		       "errno = %d\n", -err);
		जाओ out_बंद1;
	पूर्ण

	err = os_set_fd_block(fd, 0);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "xterm_open : failed to set descriptor "
		       "non-blocking, err = %d\n", -err);
		जाओ out_समाप्त;
	पूर्ण

	data->chan_fd = fd;
	new = xterm_fd(fd, &data->helper_pid);
	अगर (new < 0) अणु
		err = new;
		prपूर्णांकk(UM_KERN_ERR "xterm_open : os_rcv_fd failed, err = %d\n",
		       -err);
		जाओ out_समाप्त;
	पूर्ण

	err = os_set_fd_block(new, 0);
	अगर (err) अणु
		prपूर्णांकk(UM_KERN_ERR "xterm_open : failed to set xterm "
		       "descriptor non-blocking, err = %d\n", -err);
		जाओ out_बंद2;
	पूर्ण

	CATCH_EINTR(err = tcgetattr(new, &data->tt));
	अगर (err) अणु
		new = err;
		जाओ out_बंद2;
	पूर्ण

	अगर (data->raw) अणु
		err = raw(new);
		अगर (err) अणु
			new = err;
			जाओ out_बंद2;
		पूर्ण
	पूर्ण

	unlink(file);
	data->pid = pid;
	*dev_out = शून्य;

	वापस new;

 out_बंद2:
	बंद(new);
 out_समाप्त:
	os_समाप्त_process(pid, 1);
 out_बंद1:
	बंद(fd);

	वापस err;
पूर्ण

अटल व्योम xterm_बंद(पूर्णांक fd, व्योम *d)
अणु
	काष्ठा xterm_chan *data = d;

	अगर (data->pid != -1)
		os_समाप्त_process(data->pid, 1);
	data->pid = -1;

	अगर (data->helper_pid != -1)
		os_समाप्त_process(data->helper_pid, 0);
	data->helper_pid = -1;

	अगर (data->chan_fd != -1)
		os_बंद_file(data->chan_fd);
	os_बंद_file(fd);
पूर्ण

स्थिर काष्ठा chan_ops xterm_ops = अणु
	.type		= "xterm",
	.init		= xterm_init,
	.खोलो		= xterm_खोलो,
	.बंद		= xterm_बंद,
	.पढ़ो		= generic_पढ़ो,
	.ग_लिखो		= generic_ग_लिखो,
	.console_ग_लिखो	= generic_console_ग_लिखो,
	.winकरोw_size	= generic_winकरोw_size,
	.मुक्त		= generic_मुक्त,
	.winch		= 1,
पूर्ण;
