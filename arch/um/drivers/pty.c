<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <termios.h>
#समावेश <sys/स्थिति.स>
#समावेश "chan_user.h"
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

काष्ठा pty_chan अणु
	व्योम (*announce)(अक्षर *dev_name, पूर्णांक dev);
	पूर्णांक dev;
	पूर्णांक raw;
	काष्ठा termios tt;
	अक्षर dev_name[माप("/dev/pts/0123456\0")];
पूर्ण;

अटल व्योम *pty_chan_init(अक्षर *str, पूर्णांक device, स्थिर काष्ठा chan_opts *opts)
अणु
	काष्ठा pty_chan *data;

	data = uml_kदो_स्मृति(माप(*data), UM_GFP_KERNEL);
	अगर (data == शून्य)
		वापस शून्य;

	*data = ((काष्ठा pty_chan) अणु .announce  	= opts->announce,
				     .dev  		= device,
				     .raw  		= opts->raw पूर्ण);
	वापस data;
पूर्ण

अटल पूर्णांक pts_खोलो(पूर्णांक input, पूर्णांक output, पूर्णांक primary, व्योम *d,
		    अक्षर **dev_out)
अणु
	काष्ठा pty_chan *data = d;
	अक्षर *dev;
	पूर्णांक fd, err;

	fd = get_pty();
	अगर (fd < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "open_pts : Failed to open pts\n");
		वापस err;
	पूर्ण

	अगर (data->raw) अणु
		CATCH_EINTR(err = tcgetattr(fd, &data->tt));
		अगर (err)
			जाओ out_बंद;

		err = raw(fd);
		अगर (err)
			जाओ out_बंद;
	पूर्ण

	dev = ptsname(fd);
	प्र_लिखो(data->dev_name, "%s", dev);
	*dev_out = data->dev_name;

	अगर (data->announce)
		(*data->announce)(dev, data->dev);

	वापस fd;

out_बंद:
	बंद(fd);
	वापस err;
पूर्ण

अटल पूर्णांक geपंचांगaster(अक्षर *line)
अणु
	काष्ठा stat buf;
	अक्षर *pty, *bank, *cp;
	पूर्णांक master, err;

	pty = &line[म_माप("/dev/ptyp")];
	क्रम (bank = "pqrs"; *bank; bank++) अणु
		line[म_माप("/dev/pty")] = *bank;
		*pty = '0';
		/* Did we hit the end ? */
		अगर ((stat(line, &buf) < 0) && (त्रुटि_सं == ENOENT))
			अवरोध;

		क्रम (cp = "0123456789abcdef"; *cp; cp++) अणु
			*pty = *cp;
			master = खोलो(line, O_RDWR);
			अगर (master >= 0) अणु
				अक्षर *tp = &line[म_माप("/dev/")];

				/* verअगरy slave side is usable */
				*tp = 't';
				err = access(line, R_OK | W_OK);
				*tp = 'p';
				अगर (!err)
					वापस master;
				बंद(master);
			पूर्ण
		पूर्ण
	पूर्ण

	prपूर्णांकk(UM_KERN_ERR "getmaster - no usable host pty devices\n");
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक pty_खोलो(पूर्णांक input, पूर्णांक output, पूर्णांक primary, व्योम *d,
		    अक्षर **dev_out)
अणु
	काष्ठा pty_chan *data = d;
	पूर्णांक fd, err;
	अक्षर dev[माप("/dev/ptyxx\0")] = "/dev/ptyxx";

	fd = geपंचांगaster(dev);
	अगर (fd < 0)
		वापस fd;

	अगर (data->raw) अणु
		err = raw(fd);
		अगर (err) अणु
			बंद(fd);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (data->announce)
		(*data->announce)(dev, data->dev);

	प्र_लिखो(data->dev_name, "%s", dev);
	*dev_out = data->dev_name;

	वापस fd;
पूर्ण

स्थिर काष्ठा chan_ops pty_ops = अणु
	.type		= "pty",
	.init		= pty_chan_init,
	.खोलो		= pty_खोलो,
	.बंद		= generic_बंद,
	.पढ़ो		= generic_पढ़ो,
	.ग_लिखो		= generic_ग_लिखो,
	.console_ग_लिखो	= generic_console_ग_लिखो,
	.winकरोw_size	= generic_winकरोw_size,
	.मुक्त		= generic_मुक्त,
	.winch		= 0,
पूर्ण;

स्थिर काष्ठा chan_ops pts_ops = अणु
	.type		= "pts",
	.init		= pty_chan_init,
	.खोलो		= pts_खोलो,
	.बंद		= generic_बंद,
	.पढ़ो		= generic_पढ़ो,
	.ग_लिखो		= generic_ग_लिखो,
	.console_ग_लिखो	= generic_console_ग_लिखो,
	.winकरोw_size	= generic_winकरोw_size,
	.मुक्त		= generic_मुक्त,
	.winch		= 0,
पूर्ण;
