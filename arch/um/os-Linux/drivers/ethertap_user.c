<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and
 * James Leu (jleu@mindspring.net).
 * Copyright (C) 2001 by various other people who didn't put their name here.
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <sys/socket.h>
#समावेश <sys/रुको.h>
#समावेश "etap.h"
#समावेश <os.h>
#समावेश <net_user.h>
#समावेश <um_दो_स्मृति.h>

#घोषणा MAX_PACKET ETH_MAX_PACKET

अटल पूर्णांक etap_user_init(व्योम *data, व्योम *dev)
अणु
	काष्ठा ethertap_data *pri = data;

	pri->dev = dev;
	वापस 0;
पूर्ण

काष्ठा addr_change अणु
	क्रमागत अणु ADD_ADDR, DEL_ADDR पूर्ण what;
	अचिन्हित अक्षर addr[4];
	अचिन्हित अक्षर neपंचांगask[4];
पूर्ण;

अटल व्योम etap_change(पूर्णांक op, अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask,
			पूर्णांक fd)
अणु
	काष्ठा addr_change change;
	अक्षर *output;
	पूर्णांक n;

	change.what = op;
	स_नकल(change.addr, addr, माप(change.addr));
	स_नकल(change.neपंचांगask, neपंचांगask, माप(change.neपंचांगask));
	CATCH_EINTR(n = ग_लिखो(fd, &change, माप(change)));
	अगर (n != माप(change)) अणु
		prपूर्णांकk(UM_KERN_ERR "etap_change - request failed, err = %d\n",
		       त्रुटि_सं);
		वापस;
	पूर्ण

	output = uml_kदो_स्मृति(UM_KERN_PAGE_SIZE, UM_GFP_KERNEL);
	अगर (output == शून्य)
		prपूर्णांकk(UM_KERN_ERR "etap_change : Failed to allocate output "
		       "buffer\n");
	पढ़ो_output(fd, output, UM_KERN_PAGE_SIZE);
	अगर (output != शून्य) अणु
		prपूर्णांकk("%s", output);
		kमुक्त(output);
	पूर्ण
पूर्ण

अटल व्योम etap_खोलो_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask,
			   व्योम *arg)
अणु
	etap_change(ADD_ADDR, addr, neपंचांगask, *((पूर्णांक *) arg));
पूर्ण

अटल व्योम etap_बंद_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask,
			    व्योम *arg)
अणु
	etap_change(DEL_ADDR, addr, neपंचांगask, *((पूर्णांक *) arg));
पूर्ण

काष्ठा etap_pre_exec_data अणु
	पूर्णांक control_remote;
	पूर्णांक control_me;
	पूर्णांक data_me;
पूर्ण;

अटल व्योम etap_pre_exec(व्योम *arg)
अणु
	काष्ठा etap_pre_exec_data *data = arg;

	dup2(data->control_remote, 1);
	बंद(data->data_me);
	बंद(data->control_me);
पूर्ण

अटल पूर्णांक etap_tramp(अक्षर *dev, अक्षर *gate, पूर्णांक control_me,
		      पूर्णांक control_remote, पूर्णांक data_me, पूर्णांक data_remote)
अणु
	काष्ठा etap_pre_exec_data pe_data;
	पूर्णांक pid, err, n;
	अक्षर version_buf[माप("nnnnn\0")];
	अक्षर data_fd_buf[माप("nnnnnn\0")];
	अक्षर gate_buf[माप("nnn.nnn.nnn.nnn\0")];
	अक्षर *setup_args[] = अणु "uml_net", version_buf, "ethertap", dev,
			       data_fd_buf, gate_buf, शून्य पूर्ण;
	अक्षर *nosetup_args[] = अणु "uml_net", version_buf, "ethertap",
				 dev, data_fd_buf, शून्य पूर्ण;
	अक्षर **args, c;

	प्र_लिखो(data_fd_buf, "%d", data_remote);
	प्र_लिखो(version_buf, "%d", UML_NET_VERSION);
	अगर (gate != शून्य) अणु
		म_नकलन(gate_buf, gate, 15);
		args = setup_args;
	पूर्ण
	अन्यथा args = nosetup_args;

	err = 0;
	pe_data.control_remote = control_remote;
	pe_data.control_me = control_me;
	pe_data.data_me = data_me;
	pid = run_helper(etap_pre_exec, &pe_data, args);

	अगर (pid < 0)
		err = pid;
	बंद(data_remote);
	बंद(control_remote);
	CATCH_EINTR(n = पढ़ो(control_me, &c, माप(c)));
	अगर (n != माप(c)) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "etap_tramp : read of status failed, "
		       "err = %d\n", -err);
		वापस err;
	पूर्ण
	अगर (c != 1) अणु
		prपूर्णांकk(UM_KERN_ERR "etap_tramp : uml_net failed\n");
		err = helper_रुको(pid);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक etap_खोलो(व्योम *data)
अणु
	काष्ठा ethertap_data *pri = data;
	अक्षर *output;
	पूर्णांक data_fds[2], control_fds[2], err, output_len;

	err = tap_खोलो_common(pri->dev, pri->gate_addr);
	अगर (err)
		वापस err;

	err = socketpair(AF_UNIX, SOCK_DGRAM, 0, data_fds);
	अगर (err) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "etap_open - data socketpair failed - "
		       "err = %d\n", त्रुटि_सं);
		वापस err;
	पूर्ण

	err = socketpair(AF_UNIX, SOCK_STREAM, 0, control_fds);
	अगर (err) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "etap_open - control socketpair failed - "
		       "err = %d\n", त्रुटि_सं);
		जाओ out_बंद_data;
	पूर्ण

	err = etap_tramp(pri->dev_name, pri->gate_addr, control_fds[0],
			 control_fds[1], data_fds[0], data_fds[1]);
	output_len = UM_KERN_PAGE_SIZE;
	output = uml_kदो_स्मृति(output_len, UM_GFP_KERNEL);
	पढ़ो_output(control_fds[0], output, output_len);

	अगर (output == शून्य)
		prपूर्णांकk(UM_KERN_ERR "etap_open : failed to allocate output "
		       "buffer\n");
	अन्यथा अणु
		prपूर्णांकk("%s", output);
		kमुक्त(output);
	पूर्ण

	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "etap_tramp failed - err = %d\n", -err);
		जाओ out_बंद_control;
	पूर्ण

	pri->data_fd = data_fds[0];
	pri->control_fd = control_fds[0];
	iter_addresses(pri->dev, etap_खोलो_addr, &pri->control_fd);
	वापस data_fds[0];

out_बंद_control:
	बंद(control_fds[0]);
	बंद(control_fds[1]);
out_बंद_data:
	बंद(data_fds[0]);
	बंद(data_fds[1]);
	वापस err;
पूर्ण

अटल व्योम etap_बंद(पूर्णांक fd, व्योम *data)
अणु
	काष्ठा ethertap_data *pri = data;

	iter_addresses(pri->dev, etap_बंद_addr, &pri->control_fd);
	बंद(fd);

	अगर (shutकरोwn(pri->data_fd, SHUT_RDWR) < 0)
		prपूर्णांकk(UM_KERN_ERR "etap_close - shutdown data socket failed, "
		       "errno = %d\n", त्रुटि_सं);

	अगर (shutकरोwn(pri->control_fd, SHUT_RDWR) < 0)
		prपूर्णांकk(UM_KERN_ERR "etap_close - shutdown control socket "
		       "failed, errno = %d\n", त्रुटि_सं);

	बंद(pri->data_fd);
	pri->data_fd = -1;
	बंद(pri->control_fd);
	pri->control_fd = -1;
पूर्ण

अटल व्योम etap_add_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask,
			  व्योम *data)
अणु
	काष्ठा ethertap_data *pri = data;

	tap_check_ips(pri->gate_addr, addr);
	अगर (pri->control_fd == -1)
		वापस;
	etap_खोलो_addr(addr, neपंचांगask, &pri->control_fd);
पूर्ण

अटल व्योम etap_del_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask,
			  व्योम *data)
अणु
	काष्ठा ethertap_data *pri = data;

	अगर (pri->control_fd == -1)
		वापस;

	etap_बंद_addr(addr, neपंचांगask, &pri->control_fd);
पूर्ण

स्थिर काष्ठा net_user_info ethertap_user_info = अणु
	.init		= etap_user_init,
	.खोलो		= etap_खोलो,
	.बंद	 	= etap_बंद,
	.हटाओ	 	= शून्य,
	.add_address	= etap_add_addr,
	.delete_address = etap_del_addr,
	.mtu		= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADER_ETHERTAP,
पूर्ण;
