<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Controller of पढ़ो/ग_लिखो thपढ़ोs क्रम virtio-trace
 *
 * Copyright (C) 2012 Hitachi, Ltd.
 * Created by Yoshihiro Yunomae <yoshihiro.yunomae.ez@hitachi.com>
 *            Masami Hiramatsu <masami.hiramatsu.pt@hitachi.com>
 */

#घोषणा _GNU_SOURCE
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश "trace-agent.h"

#घोषणा HOST_MSG_SIZE		256
#घोषणा EVENT_WAIT_MSEC		100

अटल अस्थिर संक_पूर्ण_प्रकार global_संकेत_val;
bool global_sig_receive;	/* शेष false */
bool global_run_operation;	/* शेष false*/

/* Handle संक_इति/संक_विघ्न/SIGQUIT to निकास */
अटल व्योम संकेत_handler(पूर्णांक sig)
अणु
	global_संकेत_val = sig;
पूर्ण

पूर्णांक rw_ctl_init(स्थिर अक्षर *ctl_path)
अणु
	पूर्णांक ctl_fd;

	ctl_fd = खोलो(ctl_path, O_RDONLY);
	अगर (ctl_fd == -1) अणु
		pr_err("Cannot open ctl_fd\n");
		जाओ error;
	पूर्ण

	वापस ctl_fd;

error:
	निकास(निकास_त्रुटि);
पूर्ण

अटल पूर्णांक रुको_order(पूर्णांक ctl_fd)
अणु
	काष्ठा pollfd poll_fd;
	पूर्णांक ret = 0;

	जबतक (!global_sig_receive) अणु
		poll_fd.fd = ctl_fd;
		poll_fd.events = POLLIN;

		ret = poll(&poll_fd, 1, EVENT_WAIT_MSEC);

		अगर (global_संकेत_val) अणु
			global_sig_receive = true;
			pr_info("Receive interrupt %d\n", global_संकेत_val);

			/* Wakes rw-thपढ़ोs when they are sleeping */
			अगर (!global_run_operation)
				pthपढ़ो_cond_broadcast(&cond_wakeup);

			ret = -1;
			अवरोध;
		पूर्ण

		अगर (ret < 0) अणु
			pr_err("Polling error\n");
			जाओ error;
		पूर्ण

		अगर (ret)
			अवरोध;
	पूर्ण;

	वापस ret;

error:
	निकास(निकास_त्रुटि);
पूर्ण

/*
 * contol पढ़ो/ग_लिखो thपढ़ोs by handling global_run_operation
 */
व्योम *rw_ctl_loop(पूर्णांक ctl_fd)
अणु
	sमाप_प्रकार rlen;
	अक्षर buf[HOST_MSG_SIZE];
	पूर्णांक ret;

	/* Setup संकेत handlers */
	संकेत(संक_इति, संकेत_handler);
	संकेत(संक_विघ्न, संकेत_handler);
	संकेत(SIGQUIT, संकेत_handler);

	जबतक (!global_sig_receive) अणु

		ret = रुको_order(ctl_fd);
		अगर (ret < 0)
			अवरोध;

		rlen = पढ़ो(ctl_fd, buf, माप(buf));
		अगर (rlen < 0) अणु
			pr_err("read data error in ctl thread\n");
			जाओ error;
		पूर्ण

		अगर (rlen == 2 && buf[0] == '1') अणु
			/*
			 * If host ग_लिखोs '1' to a control path,
			 * this controller wakes all पढ़ो/ग_लिखो thपढ़ोs.
			 */
			global_run_operation = true;
			pthपढ़ो_cond_broadcast(&cond_wakeup);
			pr_debug("Wake up all read/write threads\n");
		पूर्ण अन्यथा अगर (rlen == 2 && buf[0] == '0') अणु
			/*
			 * If host ग_लिखोs '0' to a control path, पढ़ो/ग_लिखो
			 * thपढ़ोs will रुको क्रम notअगरication from Host.
			 */
			global_run_operation = false;
			pr_debug("Stop all read/write threads\n");
		पूर्ण अन्यथा
			pr_info("Invalid host notification: %s\n", buf);
	पूर्ण

	वापस शून्य;

error:
	निकास(निकास_त्रुटि);
पूर्ण
