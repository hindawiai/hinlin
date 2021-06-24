<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org)
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/socket.h>
#समावेश <sys/uपन.स>
#समावेश <sys/un.h>
#समावेश "mconsole.h"

अटल काष्ठा mconsole_command commands[] = अणु
	/*
	 * With uts namespaces, uts inक्रमmation becomes process-specअगरic, so
	 * we need a process context.  If we try handling this in पूर्णांकerrupt
	 * context, we may hit an निकासing process without a valid uts
	 * namespace.
	 */
	अणु "version", mconsole_version, MCONSOLE_PROC पूर्ण,
	अणु "halt", mconsole_halt, MCONSOLE_PROC पूर्ण,
	अणु "reboot", mconsole_reboot, MCONSOLE_PROC पूर्ण,
	अणु "config", mconsole_config, MCONSOLE_PROC पूर्ण,
	अणु "remove", mconsole_हटाओ, MCONSOLE_PROC पूर्ण,
	अणु "sysrq", mconsole_sysrq, MCONSOLE_INTR पूर्ण,
	अणु "help", mconsole_help, MCONSOLE_INTR पूर्ण,
	अणु "cad", mconsole_cad, MCONSOLE_INTR पूर्ण,
	अणु "stop", mconsole_stop, MCONSOLE_PROC पूर्ण,
	अणु "go", mconsole_go, MCONSOLE_INTR पूर्ण,
	अणु "log", mconsole_log, MCONSOLE_INTR पूर्ण,
	अणु "proc", mconsole_proc, MCONSOLE_PROC पूर्ण,
	अणु "stack", mconsole_stack, MCONSOLE_INTR पूर्ण,
पूर्ण;

/* Initialized in mconsole_init, which is an initcall */
अक्षर mconsole_socket_name[256];

अटल पूर्णांक mconsole_reply_v0(काष्ठा mc_request *req, अक्षर *reply)
अणु
	काष्ठा iovec iov;
	काष्ठा msghdr msg;

	iov.iov_base = reply;
	iov.iov_len = म_माप(reply);

	msg.msg_name = &(req->origin);
	msg.msg_namelen = req->originlen;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;

	वापस sendmsg(req->originating_fd, &msg, 0);
पूर्ण

अटल काष्ठा mconsole_command *mconsole_parse(काष्ठा mc_request *req)
अणु
	काष्ठा mconsole_command *cmd;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(commands); i++) अणु
		cmd = &commands[i];
		अगर (!म_भेदन(req->request.data, cmd->command,
			    म_माप(cmd->command))) अणु
			वापस cmd;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा MIN(a,b) ((a)<(b) ? (a):(b))

#घोषणा STRINGX(x) #x
#घोषणा STRING(x) STRINGX(x)

पूर्णांक mconsole_get_request(पूर्णांक fd, काष्ठा mc_request *req)
अणु
	पूर्णांक len;

	req->originlen = माप(req->origin);
	req->len = recvfrom(fd, &req->request, माप(req->request), 0,
			    (काष्ठा sockaddr *) req->origin, &req->originlen);
	अगर (req->len < 0)
		वापस 0;

	req->originating_fd = fd;

	अगर (req->request.magic != MCONSOLE_MAGIC) अणु
		/* Unversioned request */
		len = MIN(माप(req->request.data) - 1,
			  म_माप((अक्षर *) &req->request));
		स_हटाओ(req->request.data, &req->request, len);
		req->request.data[len] = '\0';

		req->request.magic = MCONSOLE_MAGIC;
		req->request.version = 0;
		req->request.len = len;

		mconsole_reply_v0(req, "ERR Version 0 mconsole clients are "
				  "not supported by this driver");
		वापस 0;
	पूर्ण

	अगर (req->request.len >= MCONSOLE_MAX_DATA) अणु
		mconsole_reply(req, "Request too large", 1, 0);
		वापस 0;
	पूर्ण
	अगर (req->request.version != MCONSOLE_VERSION) अणु
		mconsole_reply(req, "This driver only supports version "
			       STRING(MCONSOLE_VERSION) " clients", 1, 0);
	पूर्ण

	req->request.data[req->request.len] = '\0';
	req->cmd = mconsole_parse(req);
	अगर (req->cmd == शून्य) अणु
		mconsole_reply(req, "Unknown command", 1, 0);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक mconsole_reply_len(काष्ठा mc_request *req, स्थिर अक्षर *str, पूर्णांक total,
		       पूर्णांक err, पूर्णांक more)
अणु
	/*
	 * XXX This is a stack consumption problem.  It'd be nice to
	 * make it global and serialize access to it, but there are a
	 * ton of callers to this function.
	 */
	काष्ठा mconsole_reply reply;
	पूर्णांक len, n;

	करो अणु
		reply.err = err;

		/* err can only be true on the first packet */
		err = 0;

		len = MIN(total, MCONSOLE_MAX_DATA - 1);

		अगर (len == total) reply.more = more;
		अन्यथा reply.more = 1;

		स_नकल(reply.data, str, len);
		reply.data[len] = '\0';
		total -= len;
		str += len;
		reply.len = len + 1;

		len = माप(reply) + reply.len - माप(reply.data);

		n = sendto(req->originating_fd, &reply, len, 0,
			   (काष्ठा sockaddr *) req->origin, req->originlen);

		अगर (n < 0)
			वापस -त्रुटि_सं;
	पूर्ण जबतक (total > 0);
	वापस 0;
पूर्ण

पूर्णांक mconsole_reply(काष्ठा mc_request *req, स्थिर अक्षर *str, पूर्णांक err, पूर्णांक more)
अणु
	वापस mconsole_reply_len(req, str, म_माप(str), err, more);
पूर्ण


पूर्णांक mconsole_unlink_socket(व्योम)
अणु
	unlink(mconsole_socket_name);
	वापस 0;
पूर्ण

अटल पूर्णांक notअगरy_sock = -1;

पूर्णांक mconsole_notअगरy(अक्षर *sock_name, पूर्णांक type, स्थिर व्योम *data, पूर्णांक len)
अणु
	काष्ठा sockaddr_un target;
	काष्ठा mconsole_notअगरy packet;
	पूर्णांक n, err = 0;

	lock_notअगरy();
	अगर (notअगरy_sock < 0) अणु
		notअगरy_sock = socket(PF_UNIX, SOCK_DGRAM, 0);
		अगर (notअगरy_sock < 0) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "mconsole_notify - socket failed, "
			       "errno = %d\n", त्रुटि_सं);
		पूर्ण
	पूर्ण
	unlock_notअगरy();

	अगर (err)
		वापस err;

	target.sun_family = AF_UNIX;
	म_नकल(target.sun_path, sock_name);

	packet.magic = MCONSOLE_MAGIC;
	packet.version = MCONSOLE_VERSION;
	packet.type = type;
	len = (len > माप(packet.data)) ? माप(packet.data) : len;
	packet.len = len;
	स_नकल(packet.data, data, len);

	err = 0;
	len = माप(packet) + packet.len - माप(packet.data);
	n = sendto(notअगरy_sock, &packet, len, 0, (काष्ठा sockaddr *) &target,
		   माप(target));
	अगर (n < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "mconsole_notify - sendto failed, "
		       "errno = %d\n", त्रुटि_सं);
	पूर्ण
	वापस err;
पूर्ण
