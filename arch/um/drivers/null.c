<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com)
 */

#समावेश <मानकघोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश "chan_user.h"
#समावेश <os.h>

/* This address is used only as a unique identअगरier */
अटल पूर्णांक null_chan;

अटल व्योम *null_init(अक्षर *str, पूर्णांक device, स्थिर काष्ठा chan_opts *opts)
अणु
	वापस &null_chan;
पूर्ण

अटल पूर्णांक null_खोलो(पूर्णांक input, पूर्णांक output, पूर्णांक primary, व्योम *d,
		     अक्षर **dev_out)
अणु
	पूर्णांक fd;

	*dev_out = शून्य;

	fd = खोलो(DEV_शून्य, O_RDWR);
	वापस (fd < 0) ? -त्रुटि_सं : fd;
पूर्ण

अटल पूर्णांक null_पढ़ो(पूर्णांक fd, अक्षर *c_out, व्योम *unused)
अणु
	वापस -ENODEV;
पूर्ण

अटल व्योम null_मुक्त(व्योम *data)
अणु
पूर्ण

स्थिर काष्ठा chan_ops null_ops = अणु
	.type		= "null",
	.init		= null_init,
	.खोलो		= null_खोलो,
	.बंद		= generic_बंद,
	.पढ़ो		= null_पढ़ो,
	.ग_लिखो		= generic_ग_लिखो,
	.console_ग_लिखो	= generic_console_ग_लिखो,
	.winकरोw_size	= generic_winकरोw_size,
	.मुक्त		= null_मुक्त,
	.winch		= 0,
पूर्ण;
