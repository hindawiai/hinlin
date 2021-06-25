<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* 
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <linux/अगर_tun.h>
#समावेश <net/अगर.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/socket.h>
#समावेश <sys/रुको.h>
#समावेश <sys/uपन.स>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश "tuntap.h"

अटल पूर्णांक tuntap_user_init(व्योम *data, व्योम *dev)
अणु
	काष्ठा tuntap_data *pri = data;

	pri->dev = dev;
	वापस 0;
पूर्ण

अटल व्योम tuntap_add_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask,
			    व्योम *data)
अणु
	काष्ठा tuntap_data *pri = data;

	tap_check_ips(pri->gate_addr, addr);
	अगर ((pri->fd == -1) || pri->fixed_config)
		वापस;
	खोलो_addr(addr, neपंचांगask, pri->dev_name);
पूर्ण

अटल व्योम tuntap_del_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask,
			    व्योम *data)
अणु
	काष्ठा tuntap_data *pri = data;

	अगर ((pri->fd == -1) || pri->fixed_config)
		वापस;
	बंद_addr(addr, neपंचांगask, pri->dev_name);
पूर्ण

काष्ठा tuntap_pre_exec_data अणु
	पूर्णांक मानक_निकास_fd;
	पूर्णांक बंद_me;
पूर्ण;

अटल व्योम tuntap_pre_exec(व्योम *arg)
अणु
	काष्ठा tuntap_pre_exec_data *data = arg;

	dup2(data->मानक_निकास_fd, 1);
	बंद(data->बंद_me);
पूर्ण

अटल पूर्णांक tuntap_खोलो_tramp(अक्षर *gate, पूर्णांक *fd_out, पूर्णांक me, पूर्णांक remote,
			     अक्षर *buffer, पूर्णांक buffer_len, पूर्णांक *used_out)
अणु
	काष्ठा tuntap_pre_exec_data data;
	अक्षर version_buf[माप("nnnnn\0")];
	अक्षर *argv[] = अणु "uml_net", version_buf, "tuntap", "up", gate,
			 शून्य पूर्ण;
	अक्षर buf[CMSG_SPACE(माप(*fd_out))];
	काष्ठा msghdr msg;
	काष्ठा cmsghdr *cmsg;
	काष्ठा iovec iov;
	पूर्णांक pid, n, err;

	प्र_लिखो(version_buf, "%d", UML_NET_VERSION);

	data.मानक_निकास_fd = remote;
	data.बंद_me = me;

	pid = run_helper(tuntap_pre_exec, &data, argv);

	अगर (pid < 0)
		वापस pid;

	बंद(remote);

	msg.msg_name = शून्य;
	msg.msg_namelen = 0;
	अगर (buffer != शून्य) अणु
		iov = ((काष्ठा iovec) अणु buffer, buffer_len पूर्ण);
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;
	पूर्ण
	अन्यथा अणु
		msg.msg_iov = शून्य;
		msg.msg_iovlen = 0;
	पूर्ण
	msg.msg_control = buf;
	msg.msg_controllen = माप(buf);
	msg.msg_flags = 0;
	n = recvmsg(me, &msg, 0);
	*used_out = n;
	अगर (n < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "tuntap_open_tramp : recvmsg failed - "
		       "errno = %d\n", त्रुटि_सं);
		वापस err;
	पूर्ण
	helper_रुको(pid);

	cmsg = CMSG_FIRSTHDR(&msg);
	अगर (cmsg == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "tuntap_open_tramp : didn't receive a "
		       "message\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((cmsg->cmsg_level != SOL_SOCKET) ||
	   (cmsg->cmsg_type != SCM_RIGHTS)) अणु
		prपूर्णांकk(UM_KERN_ERR "tuntap_open_tramp : didn't receive a "
		       "descriptor\n");
		वापस -EINVAL;
	पूर्ण
	*fd_out = ((पूर्णांक *) CMSG_DATA(cmsg))[0];
	os_set_exec_बंद(*fd_out);
	वापस 0;
पूर्ण

अटल पूर्णांक tuntap_खोलो(व्योम *data)
अणु
	काष्ठा अगरreq अगरr;
	काष्ठा tuntap_data *pri = data;
	अक्षर *output, *buffer;
	पूर्णांक err, fds[2], len, used;

	err = tap_खोलो_common(pri->dev, pri->gate_addr);
	अगर (err < 0)
		वापस err;

	अगर (pri->fixed_config) अणु
		pri->fd = os_खोलो_file("/dev/net/tun",
				       of_cloexec(of_rdwr(OPENFLAGS())), 0);
		अगर (pri->fd < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "Failed to open /dev/net/tun, "
			       "err = %d\n", -pri->fd);
			वापस pri->fd;
		पूर्ण
		स_रखो(&अगरr, 0, माप(अगरr));
		अगरr.अगरr_flags = IFF_TAP | IFF_NO_PI;
		strlcpy(अगरr.अगरr_name, pri->dev_name, माप(अगरr.अगरr_name));
		अगर (ioctl(pri->fd, TUNSETIFF, &अगरr) < 0) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "TUNSETIFF failed, errno = %d\n",
			       त्रुटि_सं);
			बंद(pri->fd);
			वापस err;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		err = socketpair(AF_UNIX, SOCK_DGRAM, 0, fds);
		अगर (err) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "tuntap_open : socketpair failed - "
			       "errno = %d\n", त्रुटि_सं);
			वापस err;
		पूर्ण

		buffer = get_output_buffer(&len);
		अगर (buffer != शून्य)
			len--;
		used = 0;

		err = tuntap_खोलो_tramp(pri->gate_addr, &pri->fd, fds[0],
					fds[1], buffer, len, &used);

		output = buffer;
		अगर (err < 0) अणु
			prपूर्णांकk("%s", output);
			मुक्त_output_buffer(buffer);
			prपूर्णांकk(UM_KERN_ERR "tuntap_open_tramp failed - "
			       "err = %d\n", -err);
			वापस err;
		पूर्ण

		pri->dev_name = uml_strdup(buffer);
		output += IFNAMSIZ;
		prपूर्णांकk("%s", output);
		मुक्त_output_buffer(buffer);

		बंद(fds[0]);
		iter_addresses(pri->dev, खोलो_addr, pri->dev_name);
	पूर्ण

	वापस pri->fd;
पूर्ण

अटल व्योम tuntap_बंद(पूर्णांक fd, व्योम *data)
अणु
	काष्ठा tuntap_data *pri = data;

	अगर (!pri->fixed_config)
		iter_addresses(pri->dev, बंद_addr, pri->dev_name);
	बंद(fd);
	pri->fd = -1;
पूर्ण

स्थिर काष्ठा net_user_info tuntap_user_info = अणु
	.init		= tuntap_user_init,
	.खोलो		= tuntap_खोलो,
	.बंद	 	= tuntap_बंद,
	.हटाओ	 	= शून्य,
	.add_address	= tuntap_add_addr,
	.delete_address = tuntap_del_addr,
	.mtu		= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADER_OTHER,
पूर्ण;
