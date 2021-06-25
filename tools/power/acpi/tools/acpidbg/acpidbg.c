<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI AML पूर्णांकerfacing userspace utility
 *
 * Copyright (C) 2015, Intel Corporation
 * Authors: Lv Zheng <lv.zheng@पूर्णांकel.com>
 */

#समावेश <acpi/acpi.h>

/* Headers not included by include/acpi/platक्रमm/aclinux.h */
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <error.h>
#समावेश <stdbool.h>
#समावेश <fcntl.h>
#समावेश <निश्चित.स>
#समावेश <sys/select.h>
#समावेश "../../../../../include/linux/circ_buf.h"

#घोषणा ACPI_AML_खाता		"/sys/kernel/debug/acpi/acpidbg"
#घोषणा ACPI_AML_SEC_TICK	1
#घोषणा ACPI_AML_USEC_PEEK	200
#घोषणा ACPI_AML_BUF_SIZE	4096

#घोषणा ACPI_AML_BATCH_WRITE_CMD	0x00 /* Write command to kernel */
#घोषणा ACPI_AML_BATCH_READ_LOG		0x01 /* Read log from kernel */
#घोषणा ACPI_AML_BATCH_WRITE_LOG	0x02 /* Write log to console */

#घोषणा ACPI_AML_LOG_START		0x00
#घोषणा ACPI_AML_PROMPT_START		0x01
#घोषणा ACPI_AML_PROMPT_STOP		0x02
#घोषणा ACPI_AML_LOG_STOP		0x03
#घोषणा ACPI_AML_PROMPT_ROLL		0x04

#घोषणा ACPI_AML_INTERACTIVE	0x00
#घोषणा ACPI_AML_BATCH		0x01

#घोषणा circ_count(circ) \
	(CIRC_CNT((circ)->head, (circ)->tail, ACPI_AML_BUF_SIZE))
#घोषणा circ_count_to_end(circ) \
	(CIRC_CNT_TO_END((circ)->head, (circ)->tail, ACPI_AML_BUF_SIZE))
#घोषणा circ_space(circ) \
	(CIRC_SPACE((circ)->head, (circ)->tail, ACPI_AML_BUF_SIZE))
#घोषणा circ_space_to_end(circ) \
	(CIRC_SPACE_TO_END((circ)->head, (circ)->tail, ACPI_AML_BUF_SIZE))

#घोषणा acpi_aml_cmd_count()	circ_count(&acpi_aml_cmd_crc)
#घोषणा acpi_aml_log_count()	circ_count(&acpi_aml_log_crc)
#घोषणा acpi_aml_cmd_space()	circ_space(&acpi_aml_cmd_crc)
#घोषणा acpi_aml_log_space()	circ_space(&acpi_aml_log_crc)

#घोषणा ACPI_AML_DO(_fd, _op, _buf, _ret)				\
	करो अणु								\
		_ret = acpi_aml_##_op(_fd, &acpi_aml_##_buf##_crc);	\
		अगर (_ret == 0) अणु					\
			ख_लिखो(मानक_त्रुटि,					\
				"%s %s pipe closed.\n", #_buf, #_op);	\
			वापस;						\
		पूर्ण							\
	पूर्ण जबतक (0)
#घोषणा ACPI_AML_BATCH_DO(_fd, _op, _buf, _ret)				\
	करो अणु								\
		_ret = acpi_aml_##_op##_batch_##_buf(_fd,		\
			 &acpi_aml_##_buf##_crc);			\
		अगर (_ret == 0)						\
			वापस;						\
	पूर्ण जबतक (0)


अटल अक्षर acpi_aml_cmd_buf[ACPI_AML_BUF_SIZE];
अटल अक्षर acpi_aml_log_buf[ACPI_AML_BUF_SIZE];
अटल काष्ठा circ_buf acpi_aml_cmd_crc = अणु
	.buf = acpi_aml_cmd_buf,
	.head = 0,
	.tail = 0,
पूर्ण;
अटल काष्ठा circ_buf acpi_aml_log_crc = अणु
	.buf = acpi_aml_log_buf,
	.head = 0,
	.tail = 0,
पूर्ण;
अटल स्थिर अक्षर *acpi_aml_file_path = ACPI_AML_खाता;
अटल अचिन्हित दीर्घ acpi_aml_mode = ACPI_AML_INTERACTIVE;
अटल bool acpi_aml_निकास;

अटल bool acpi_aml_batch_drain;
अटल अचिन्हित दीर्घ acpi_aml_batch_state;
अटल अक्षर acpi_aml_batch_prompt;
अटल अक्षर acpi_aml_batch_roll;
अटल अचिन्हित दीर्घ acpi_aml_log_state;
अटल अक्षर *acpi_aml_batch_cmd = शून्य;
अटल अक्षर *acpi_aml_batch_pos = शून्य;

अटल पूर्णांक acpi_aml_set_fl(पूर्णांक fd, पूर्णांक flags)
अणु
	पूर्णांक ret;

	ret = fcntl(fd, F_GETFL, 0);
	अगर (ret < 0) अणु
		लिखो_त्रुटि("fcntl(F_GETFL)");
		वापस ret;
	पूर्ण
	flags |= ret;
	ret = fcntl(fd, F_SETFL, flags);
	अगर (ret < 0) अणु
		लिखो_त्रुटि("fcntl(F_SETFL)");
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_aml_set_fd(पूर्णांक fd, पूर्णांक maxfd, fd_set *set)
अणु
	अगर (fd > maxfd)
		maxfd = fd;
	FD_SET(fd, set);
	वापस maxfd;
पूर्ण

अटल पूर्णांक acpi_aml_पढ़ो(पूर्णांक fd, काष्ठा circ_buf *crc)
अणु
	अक्षर *p;
	पूर्णांक len;

	p = &crc->buf[crc->head];
	len = circ_space_to_end(crc);
	len = पढ़ो(fd, p, len);
	अगर (len < 0)
		लिखो_त्रुटि("read");
	अन्यथा अगर (len > 0)
		crc->head = (crc->head + len) & (ACPI_AML_BUF_SIZE - 1);
	वापस len;
पूर्ण

अटल पूर्णांक acpi_aml_पढ़ो_batch_cmd(पूर्णांक unused, काष्ठा circ_buf *crc)
अणु
	अक्षर *p;
	पूर्णांक len;
	पूर्णांक reमुख्यed = म_माप(acpi_aml_batch_pos);

	p = &crc->buf[crc->head];
	len = circ_space_to_end(crc);
	अगर (len > reमुख्यed) अणु
		स_नकल(p, acpi_aml_batch_pos, reमुख्यed);
		acpi_aml_batch_pos += reमुख्यed;
		len = reमुख्यed;
	पूर्ण अन्यथा अणु
		स_नकल(p, acpi_aml_batch_pos, len);
		acpi_aml_batch_pos += len;
	पूर्ण
	अगर (len > 0)
		crc->head = (crc->head + len) & (ACPI_AML_BUF_SIZE - 1);
	वापस len;
पूर्ण

अटल पूर्णांक acpi_aml_पढ़ो_batch_log(पूर्णांक fd, काष्ठा circ_buf *crc)
अणु
	अक्षर *p;
	पूर्णांक len;
	पूर्णांक ret = 0;

	p = &crc->buf[crc->head];
	len = circ_space_to_end(crc);
	जबतक (ret < len && acpi_aml_log_state != ACPI_AML_LOG_STOP) अणु
		अगर (acpi_aml_log_state == ACPI_AML_PROMPT_ROLL) अणु
			*p = acpi_aml_batch_roll;
			len = 1;
			crc->head = (crc->head + 1) & (ACPI_AML_BUF_SIZE - 1);
			ret += 1;
			acpi_aml_log_state = ACPI_AML_LOG_START;
		पूर्ण अन्यथा अणु
			len = पढ़ो(fd, p, 1);
			अगर (len <= 0) अणु
				अगर (len < 0)
					लिखो_त्रुटि("read");
				ret = len;
				अवरोध;
			पूर्ण
		पूर्ण
		चयन (acpi_aml_log_state) अणु
		हाल ACPI_AML_LOG_START:
			अगर (*p == '\n')
				acpi_aml_log_state = ACPI_AML_PROMPT_START;
			crc->head = (crc->head + 1) & (ACPI_AML_BUF_SIZE - 1);
			ret += 1;
			अवरोध;
		हाल ACPI_AML_PROMPT_START:
			अगर (*p == ACPI_DEBUGGER_COMMAND_PROMPT ||
			    *p == ACPI_DEBUGGER_EXECUTE_PROMPT) अणु
				acpi_aml_batch_prompt = *p;
				acpi_aml_log_state = ACPI_AML_PROMPT_STOP;
			पूर्ण अन्यथा अणु
				अगर (*p != '\n')
					acpi_aml_log_state = ACPI_AML_LOG_START;
				crc->head = (crc->head + 1) & (ACPI_AML_BUF_SIZE - 1);
				ret += 1;
			पूर्ण
			अवरोध;
		हाल ACPI_AML_PROMPT_STOP:
			अगर (*p == ' ') अणु
				acpi_aml_log_state = ACPI_AML_LOG_STOP;
				acpi_aml_निकास = true;
			पूर्ण अन्यथा अणु
				/* Roll back */
				acpi_aml_log_state = ACPI_AML_PROMPT_ROLL;
				acpi_aml_batch_roll = *p;
				*p = acpi_aml_batch_prompt;
				crc->head = (crc->head + 1) & (ACPI_AML_BUF_SIZE - 1);
				ret += 1;
			पूर्ण
			अवरोध;
		शेष:
			निश्चित(0);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_aml_ग_लिखो(पूर्णांक fd, काष्ठा circ_buf *crc)
अणु
	अक्षर *p;
	पूर्णांक len;

	p = &crc->buf[crc->tail];
	len = circ_count_to_end(crc);
	len = ग_लिखो(fd, p, len);
	अगर (len < 0)
		लिखो_त्रुटि("write");
	अन्यथा अगर (len > 0)
		crc->tail = (crc->tail + len) & (ACPI_AML_BUF_SIZE - 1);
	वापस len;
पूर्ण

अटल पूर्णांक acpi_aml_ग_लिखो_batch_log(पूर्णांक fd, काष्ठा circ_buf *crc)
अणु
	अक्षर *p;
	पूर्णांक len;

	p = &crc->buf[crc->tail];
	len = circ_count_to_end(crc);
	अगर (!acpi_aml_batch_drain) अणु
		len = ग_लिखो(fd, p, len);
		अगर (len < 0)
			लिखो_त्रुटि("write");
	पूर्ण
	अगर (len > 0)
		crc->tail = (crc->tail + len) & (ACPI_AML_BUF_SIZE - 1);
	वापस len;
पूर्ण

अटल पूर्णांक acpi_aml_ग_लिखो_batch_cmd(पूर्णांक fd, काष्ठा circ_buf *crc)
अणु
	पूर्णांक len;

	len = acpi_aml_ग_लिखो(fd, crc);
	अगर (circ_count_to_end(crc) == 0)
		acpi_aml_batch_state = ACPI_AML_BATCH_READ_LOG;
	वापस len;
पूर्ण

अटल व्योम acpi_aml_loop(पूर्णांक fd)
अणु
	fd_set rfds;
	fd_set wfds;
	काष्ठा समयval tv;
	पूर्णांक ret;
	पूर्णांक maxfd = 0;

	अगर (acpi_aml_mode == ACPI_AML_BATCH) अणु
		acpi_aml_log_state = ACPI_AML_LOG_START;
		acpi_aml_batch_pos = acpi_aml_batch_cmd;
		अगर (acpi_aml_batch_drain)
			acpi_aml_batch_state = ACPI_AML_BATCH_READ_LOG;
		अन्यथा
			acpi_aml_batch_state = ACPI_AML_BATCH_WRITE_CMD;
	पूर्ण
	acpi_aml_निकास = false;
	जबतक (!acpi_aml_निकास) अणु
		tv.tv_sec = ACPI_AML_SEC_TICK;
		tv.tv_usec = 0;
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);

		अगर (acpi_aml_cmd_space()) अणु
			अगर (acpi_aml_mode == ACPI_AML_INTERACTIVE)
				maxfd = acpi_aml_set_fd(STDIN_खाताNO, maxfd, &rfds);
			अन्यथा अगर (म_माप(acpi_aml_batch_pos) &&
				 acpi_aml_batch_state == ACPI_AML_BATCH_WRITE_CMD)
				ACPI_AML_BATCH_DO(STDIN_खाताNO, पढ़ो, cmd, ret);
		पूर्ण
		अगर (acpi_aml_cmd_count() &&
		    (acpi_aml_mode == ACPI_AML_INTERACTIVE ||
		     acpi_aml_batch_state == ACPI_AML_BATCH_WRITE_CMD))
			maxfd = acpi_aml_set_fd(fd, maxfd, &wfds);
		अगर (acpi_aml_log_space() &&
		    (acpi_aml_mode == ACPI_AML_INTERACTIVE ||
		     acpi_aml_batch_state == ACPI_AML_BATCH_READ_LOG))
			maxfd = acpi_aml_set_fd(fd, maxfd, &rfds);
		अगर (acpi_aml_log_count())
			maxfd = acpi_aml_set_fd(STDOUT_खाताNO, maxfd, &wfds);

		ret = select(maxfd+1, &rfds, &wfds, शून्य, &tv);
		अगर (ret < 0) अणु
			लिखो_त्रुटि("select");
			अवरोध;
		पूर्ण
		अगर (ret > 0) अणु
			अगर (FD_ISSET(STDIN_खाताNO, &rfds))
				ACPI_AML_DO(STDIN_खाताNO, पढ़ो, cmd, ret);
			अगर (FD_ISSET(fd, &wfds)) अणु
				अगर (acpi_aml_mode == ACPI_AML_BATCH)
					ACPI_AML_BATCH_DO(fd, ग_लिखो, cmd, ret);
				अन्यथा
					ACPI_AML_DO(fd, ग_लिखो, cmd, ret);
			पूर्ण
			अगर (FD_ISSET(fd, &rfds)) अणु
				अगर (acpi_aml_mode == ACPI_AML_BATCH)
					ACPI_AML_BATCH_DO(fd, पढ़ो, log, ret);
				अन्यथा
					ACPI_AML_DO(fd, पढ़ो, log, ret);
			पूर्ण
			अगर (FD_ISSET(STDOUT_खाताNO, &wfds)) अणु
				अगर (acpi_aml_mode == ACPI_AML_BATCH)
					ACPI_AML_BATCH_DO(STDOUT_खाताNO, ग_लिखो, log, ret);
				अन्यथा
					ACPI_AML_DO(STDOUT_खाताNO, ग_लिखो, log, ret);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल bool acpi_aml_पढ़ोable(पूर्णांक fd)
अणु
	fd_set rfds;
	काष्ठा समयval tv;
	पूर्णांक ret;
	पूर्णांक maxfd = 0;

	tv.tv_sec = 0;
	tv.tv_usec = ACPI_AML_USEC_PEEK;
	FD_ZERO(&rfds);
	maxfd = acpi_aml_set_fd(fd, maxfd, &rfds);
	ret = select(maxfd+1, &rfds, शून्य, शून्य, &tv);
	अगर (ret < 0)
		लिखो_त्रुटि("select");
	अगर (ret > 0 && FD_ISSET(fd, &rfds))
		वापस true;
	वापस false;
पूर्ण

/*
 * This is a userspace IO flush implementation, replying on the prompt
 * अक्षरacters and can be turned पूर्णांकo a flush() call after kernel implements
 * .flush() fileप्रणाली operation.
 */
अटल व्योम acpi_aml_flush(पूर्णांक fd)
अणु
	जबतक (acpi_aml_पढ़ोable(fd)) अणु
		acpi_aml_batch_drain = true;
		acpi_aml_loop(fd);
		acpi_aml_batch_drain = false;
	पूर्ण
पूर्ण

व्योम usage(खाता *file, अक्षर *progname)
अणु
	ख_लिखो(file, "usage: %s [-b cmd] [-f file] [-h]\n", progname);
	ख_लिखो(file, "\nOptions:\n");
	ख_लिखो(file, "  -b     Specify command to be executed in batch mode\n");
	ख_लिखो(file, "  -f     Specify interface file other than");
	ख_लिखो(file, "         /sys/kernel/debug/acpi/acpidbg\n");
	ख_लिखो(file, "  -h     Print this help message\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक fd = -1;
	पूर्णांक ch;
	पूर्णांक len;
	पूर्णांक ret = निकास_सफल;

	जबतक ((ch = getopt(argc, argv, "b:f:h")) != -1) अणु
		चयन (ch) अणु
		हाल 'b':
			अगर (acpi_aml_batch_cmd) अणु
				ख_लिखो(मानक_त्रुटि, "Already specify %s\n",
					acpi_aml_batch_cmd);
				ret = निकास_त्रुटि;
				जाओ निकास;
			पूर्ण
			len = म_माप(optarg);
			acpi_aml_batch_cmd = सुस्मृति(len + 2, 1);
			अगर (!acpi_aml_batch_cmd) अणु
				लिखो_त्रुटि("calloc");
				ret = निकास_त्रुटि;
				जाओ निकास;
			पूर्ण
			स_नकल(acpi_aml_batch_cmd, optarg, len);
			acpi_aml_batch_cmd[len] = '\n';
			acpi_aml_mode = ACPI_AML_BATCH;
			अवरोध;
		हाल 'f':
			acpi_aml_file_path = optarg;
			अवरोध;
		हाल 'h':
			usage(मानक_निकास, argv[0]);
			जाओ निकास;
			अवरोध;
		हाल '?':
		शेष:
			usage(मानक_त्रुटि, argv[0]);
			ret = निकास_त्रुटि;
			जाओ निकास;
			अवरोध;
		पूर्ण
	पूर्ण

	fd = खोलो(acpi_aml_file_path, O_RDWR | O_NONBLOCK);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("open");
		ret = निकास_त्रुटि;
		जाओ निकास;
	पूर्ण
	acpi_aml_set_fl(STDIN_खाताNO, O_NONBLOCK);
	acpi_aml_set_fl(STDOUT_खाताNO, O_NONBLOCK);

	अगर (acpi_aml_mode == ACPI_AML_BATCH)
		acpi_aml_flush(fd);
	acpi_aml_loop(fd);

निकास:
	अगर (fd >= 0)
		बंद(fd);
	अगर (acpi_aml_batch_cmd)
		मुक्त(acpi_aml_batch_cmd);
	वापस ret;
पूर्ण
