<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <kern_util.h>
#समावेश <os.h>

काष्ठा grantpt_info अणु
	पूर्णांक fd;
	पूर्णांक res;
	पूर्णांक err;
पूर्ण;

अटल व्योम grantpt_cb(व्योम *arg)
अणु
	काष्ठा grantpt_info *info = arg;

	info->res = grantpt(info->fd);
	info->err = त्रुटि_सं;
पूर्ण

पूर्णांक get_pty(व्योम)
अणु
	काष्ठा grantpt_info info;
	पूर्णांक fd, err;

	fd = खोलो("/dev/ptmx", O_RDWR);
	अगर (fd < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "get_pty : Couldn't open /dev/ptmx - "
		       "err = %d\n", त्रुटि_सं);
		वापस err;
	पूर्ण

	info.fd = fd;
	initial_thपढ़ो_cb(grantpt_cb, &info);

	अगर (info.res < 0) अणु
		err = -info.err;
		prपूर्णांकk(UM_KERN_ERR "get_pty : Couldn't grant pty - "
		       "errno = %d\n", -info.err);
		जाओ out;
	पूर्ण

	अगर (unlockpt(fd) < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "get_pty : Couldn't unlock pty - "
		       "errno = %d\n", त्रुटि_सं);
		जाओ out;
	पूर्ण
	वापस fd;
out:
	बंद(fd);
	वापस err;
पूर्ण
