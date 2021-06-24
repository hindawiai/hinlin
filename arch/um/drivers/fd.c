<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <termios.h>
#समावेश "chan_user.h"
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

काष्ठा fd_chan अणु
	पूर्णांक fd;
	पूर्णांक raw;
	काष्ठा termios tt;
	अक्षर str[माप("1234567890\0")];
पूर्ण;

अटल व्योम *fd_init(अक्षर *str, पूर्णांक device, स्थिर काष्ठा chan_opts *opts)
अणु
	काष्ठा fd_chan *data;
	अक्षर *end;
	पूर्णांक n;

	अगर (*str != ':') अणु
		prपूर्णांकk(UM_KERN_ERR "fd_init : channel type 'fd' must specify a "
		       "file descriptor\n");
		वापस शून्य;
	पूर्ण
	str++;
	n = म_से_अदीर्घ(str, &end, 0);
	अगर ((*end != '\0') || (end == str)) अणु
		prपूर्णांकk(UM_KERN_ERR "fd_init : couldn't parse file descriptor "
		       "'%s'\n", str);
		वापस शून्य;
	पूर्ण

	data = uml_kदो_स्मृति(माप(*data), UM_GFP_KERNEL);
	अगर (data == शून्य)
		वापस शून्य;

	*data = ((काष्ठा fd_chan) अणु .fd  	= n,
				    .raw  	= opts->raw पूर्ण);
	वापस data;
पूर्ण

अटल पूर्णांक fd_खोलो(पूर्णांक input, पूर्णांक output, पूर्णांक primary, व्योम *d, अक्षर **dev_out)
अणु
	काष्ठा fd_chan *data = d;
	पूर्णांक err;

	अगर (data->raw && isatty(data->fd)) अणु
		CATCH_EINTR(err = tcgetattr(data->fd, &data->tt));
		अगर (err)
			वापस err;

		err = raw(data->fd);
		अगर (err)
			वापस err;
	पूर्ण
	प्र_लिखो(data->str, "%d", data->fd);
	*dev_out = data->str;
	वापस data->fd;
पूर्ण

अटल व्योम fd_बंद(पूर्णांक fd, व्योम *d)
अणु
	काष्ठा fd_chan *data = d;
	पूर्णांक err;

	अगर (!data->raw || !isatty(fd))
		वापस;

	CATCH_EINTR(err = tcsetattr(fd, TCSAFLUSH, &data->tt));
	अगर (err)
		prपूर्णांकk(UM_KERN_ERR "Failed to restore terminal state - "
		       "errno = %d\n", -err);
	data->raw = 0;
पूर्ण

स्थिर काष्ठा chan_ops fd_ops = अणु
	.type		= "fd",
	.init		= fd_init,
	.खोलो		= fd_खोलो,
	.बंद		= fd_बंद,
	.पढ़ो		= generic_पढ़ो,
	.ग_लिखो		= generic_ग_लिखो,
	.console_ग_लिखो	= generic_console_ग_लिखो,
	.winकरोw_size	= generic_winकरोw_size,
	.मुक्त		= generic_मुक्त,
	.winch		= 1,
पूर्ण;
