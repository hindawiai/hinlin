<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <termios.h>
#समावेश <sys/रुको.h>
#समावेश <net_user.h>
#समावेश <os.h>
#समावेश "slip.h"
#समावेश <um_दो_स्मृति.h>

अटल पूर्णांक slip_user_init(व्योम *data, व्योम *dev)
अणु
	काष्ठा slip_data *pri = data;

	pri->dev = dev;
	वापस 0;
पूर्ण

अटल पूर्णांक set_up_tty(पूर्णांक fd)
अणु
	पूर्णांक i;
	काष्ठा termios tios;

	अगर (tcgetattr(fd, &tios) < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "could not get initial terminal "
		       "attributes\n");
		वापस -1;
	पूर्ण

	tios.c_cflag = CS8 | CREAD | HUPCL | CLOCAL;
	tios.c_अगरlag = IGNBRK | IGNPAR;
	tios.c_oflag = 0;
	tios.c_lflag = 0;
	क्रम (i = 0; i < NCCS; i++)
		tios.c_cc[i] = 0;
	tios.c_cc[VMIN] = 1;
	tios.c_cc[VTIME] = 0;

	cfsetospeed(&tios, B38400);
	cfsetispeed(&tios, B38400);

	अगर (tcsetattr(fd, TCSAFLUSH, &tios) < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "failed to set terminal attributes\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा slip_pre_exec_data अणु
	पूर्णांक मानक_निवेश_fd;
	पूर्णांक मानक_निकास_fd;
	पूर्णांक बंद_me;
पूर्ण;

अटल व्योम slip_pre_exec(व्योम *arg)
अणु
	काष्ठा slip_pre_exec_data *data = arg;

	अगर (data->मानक_निवेश_fd >= 0)
		dup2(data->मानक_निवेश_fd, 0);
	dup2(data->मानक_निकास_fd, 1);
	अगर (data->बंद_me >= 0)
		बंद(data->बंद_me);
पूर्ण

अटल पूर्णांक slip_tramp(अक्षर **argv, पूर्णांक fd)
अणु
	काष्ठा slip_pre_exec_data pe_data;
	अक्षर *output;
	पूर्णांक pid, fds[2], err, output_len;

	err = os_pipe(fds, 1, 0);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "slip_tramp : pipe failed, err = %d\n",
		       -err);
		जाओ out;
	पूर्ण

	err = 0;
	pe_data.मानक_निवेश_fd = fd;
	pe_data.मानक_निकास_fd = fds[1];
	pe_data.बंद_me = fds[0];
	err = run_helper(slip_pre_exec, &pe_data, argv);
	अगर (err < 0)
		जाओ out_बंद;
	pid = err;

	output_len = UM_KERN_PAGE_SIZE;
	output = uml_kदो_स्मृति(output_len, UM_GFP_KERNEL);
	अगर (output == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "slip_tramp : failed to allocate output "
		       "buffer\n");
		os_समाप्त_process(pid, 1);
		err = -ENOMEM;
		जाओ out_बंद;
	पूर्ण

	बंद(fds[1]);
	पढ़ो_output(fds[0], output, output_len);
	prपूर्णांकk("%s", output);

	err = helper_रुको(pid);
	बंद(fds[0]);

	kमुक्त(output);
	वापस err;

out_बंद:
	बंद(fds[0]);
	बंद(fds[1]);
out:
	वापस err;
पूर्ण

अटल पूर्णांक slip_खोलो(व्योम *data)
अणु
	काष्ठा slip_data *pri = data;
	अक्षर version_buf[माप("nnnnn\0")];
	अक्षर gate_buf[माप("nnn.nnn.nnn.nnn\0")];
	अक्षर *argv[] = अणु "uml_net", version_buf, "slip", "up", gate_buf,
			 शून्य पूर्ण;
	पूर्णांक sfd, mfd, err;

	err = get_pty();
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "slip-open : Failed to open pty, err = %d\n",
		       -err);
		जाओ out;
	पूर्ण
	mfd = err;

	err = खोलो(ptsname(mfd), O_RDWR, 0);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "Couldn't open tty for slip line, "
		       "err = %d\n", -err);
		जाओ out_बंद;
	पूर्ण
	sfd = err;

	अगर (set_up_tty(sfd))
		जाओ out_बंद2;

	pri->slave = sfd;
	pri->slip.pos = 0;
	pri->slip.esc = 0;
	अगर (pri->gate_addr != शून्य) अणु
		प्र_लिखो(version_buf, "%d", UML_NET_VERSION);
		म_नकल(gate_buf, pri->gate_addr);

		err = slip_tramp(argv, sfd);

		अगर (err < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "slip_tramp failed - err = %d\n",
			       -err);
			जाओ out_बंद2;
		पूर्ण
		err = os_get_अगरname(pri->slave, pri->name);
		अगर (err < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "get_ifname failed, err = %d\n",
			       -err);
			जाओ out_बंद2;
		पूर्ण
		iter_addresses(pri->dev, खोलो_addr, pri->name);
	पूर्ण
	अन्यथा अणु
		err = os_set_slip(sfd);
		अगर (err < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "Failed to set slip discipline "
			       "encapsulation - err = %d\n", -err);
			जाओ out_बंद2;
		पूर्ण
	पूर्ण
	वापस mfd;
out_बंद2:
	बंद(sfd);
out_बंद:
	बंद(mfd);
out:
	वापस err;
पूर्ण

अटल व्योम slip_बंद(पूर्णांक fd, व्योम *data)
अणु
	काष्ठा slip_data *pri = data;
	अक्षर version_buf[माप("nnnnn\0")];
	अक्षर *argv[] = अणु "uml_net", version_buf, "slip", "down", pri->name,
			 शून्य पूर्ण;
	पूर्णांक err;

	अगर (pri->gate_addr != शून्य)
		iter_addresses(pri->dev, बंद_addr, pri->name);

	प्र_लिखो(version_buf, "%d", UML_NET_VERSION);

	err = slip_tramp(argv, pri->slave);

	अगर (err != 0)
		prपूर्णांकk(UM_KERN_ERR "slip_tramp failed - errno = %d\n", -err);
	बंद(fd);
	बंद(pri->slave);
	pri->slave = -1;
पूर्ण

पूर्णांक slip_user_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा slip_data *pri)
अणु
	वापस slip_proto_पढ़ो(fd, buf, len, &pri->slip);
पूर्ण

पूर्णांक slip_user_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा slip_data *pri)
अणु
	वापस slip_proto_ग_लिखो(fd, buf, len, &pri->slip);
पूर्ण

अटल व्योम slip_add_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask,
			  व्योम *data)
अणु
	काष्ठा slip_data *pri = data;

	अगर (pri->slave < 0)
		वापस;
	खोलो_addr(addr, neपंचांगask, pri->name);
पूर्ण

अटल व्योम slip_del_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask,
			    व्योम *data)
अणु
	काष्ठा slip_data *pri = data;

	अगर (pri->slave < 0)
		वापस;
	बंद_addr(addr, neपंचांगask, pri->name);
पूर्ण

स्थिर काष्ठा net_user_info slip_user_info = अणु
	.init		= slip_user_init,
	.खोलो		= slip_खोलो,
	.बंद	 	= slip_बंद,
	.हटाओ	 	= शून्य,
	.add_address	= slip_add_addr,
	.delete_address = slip_del_addr,
	.mtu		= BUF_SIZE,
	.max_packet	= BUF_SIZE,
पूर्ण;
