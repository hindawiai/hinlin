<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com)
 */

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <termios.h>
#समावेश "chan_user.h"
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

काष्ठा tty_chan अणु
	अक्षर *dev;
	पूर्णांक raw;
	काष्ठा termios tt;
पूर्ण;

अटल व्योम *tty_chan_init(अक्षर *str, पूर्णांक device, स्थिर काष्ठा chan_opts *opts)
अणु
	काष्ठा tty_chan *data;

	अगर (*str != ':') अणु
		prपूर्णांकk(UM_KERN_ERR "tty_init : channel type 'tty' must specify "
		       "a device\n");
		वापस शून्य;
	पूर्ण
	str++;

	data = uml_kदो_स्मृति(माप(*data), UM_GFP_KERNEL);
	अगर (data == शून्य)
		वापस शून्य;
	*data = ((काष्ठा tty_chan) अणु .dev 	= str,
				     .raw 	= opts->raw पूर्ण);

	वापस data;
पूर्ण

अटल पूर्णांक tty_खोलो(पूर्णांक input, पूर्णांक output, पूर्णांक primary, व्योम *d,
		    अक्षर **dev_out)
अणु
	काष्ठा tty_chan *data = d;
	पूर्णांक fd, err, mode = 0;

	अगर (input && output)
		mode = O_RDWR;
	अन्यथा अगर (input)
		mode = O_RDONLY;
	अन्यथा अगर (output)
		mode = O_WRONLY;

	fd = खोलो(data->dev, mode);
	अगर (fd < 0)
		वापस -त्रुटि_सं;

	अगर (data->raw) अणु
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

स्थिर काष्ठा chan_ops tty_ops = अणु
	.type		= "tty",
	.init		= tty_chan_init,
	.खोलो		= tty_खोलो,
	.बंद		= generic_बंद,
	.पढ़ो		= generic_पढ़ो,
	.ग_लिखो		= generic_ग_लिखो,
	.console_ग_लिखो	= generic_console_ग_लिखो,
	.winकरोw_size	= generic_winकरोw_size,
	.मुक्त		= generic_मुक्त,
	.winch		= 0,
पूर्ण;
