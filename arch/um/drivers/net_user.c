<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानकतर्क.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <sys/socket.h>
#समावेश <sys/रुको.h>
#समावेश <net_user.h>
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

पूर्णांक tap_खोलो_common(व्योम *dev, अक्षर *gate_addr)
अणु
	पूर्णांक tap_addr[4];

	अगर (gate_addr == शून्य)
		वापस 0;
	अगर (माला_पूछो(gate_addr, "%d.%d.%d.%d", &tap_addr[0],
		  &tap_addr[1], &tap_addr[2], &tap_addr[3]) != 4) अणु
		prपूर्णांकk(UM_KERN_ERR "Invalid tap IP address - '%s'\n",
		       gate_addr);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम tap_check_ips(अक्षर *gate_addr, अचिन्हित अक्षर *eth_addr)
अणु
	पूर्णांक tap_addr[4];

	अगर ((gate_addr != शून्य) &&
	    (माला_पूछो(gate_addr, "%d.%d.%d.%d", &tap_addr[0],
		    &tap_addr[1], &tap_addr[2], &tap_addr[3]) == 4) &&
	    (eth_addr[0] == tap_addr[0]) &&
	    (eth_addr[1] == tap_addr[1]) &&
	    (eth_addr[2] == tap_addr[2]) &&
	    (eth_addr[3] == tap_addr[3])) अणु
		prपूर्णांकk(UM_KERN_ERR "The tap IP address and the UML eth IP "
		       "address must be different\n");
	पूर्ण
पूर्ण

/* Do reliable error handling as this fails frequently enough. */
व्योम पढ़ो_output(पूर्णांक fd, अक्षर *output, पूर्णांक len)
अणु
	पूर्णांक reमुख्य, ret, expected;
	अक्षर c;
	अक्षर *str;

	अगर (output == शून्य) अणु
		output = &c;
		len = माप(c);
	पूर्ण

	*output = '\0';
	ret = पढ़ो(fd, &reमुख्य, माप(reमुख्य));

	अगर (ret != माप(reमुख्य)) अणु
		अगर (ret < 0)
			ret = -त्रुटि_सं;
		expected = माप(reमुख्य);
		str = "length";
		जाओ err;
	पूर्ण

	जबतक (reमुख्य != 0) अणु
		expected = (reमुख्य < len) ? reमुख्य : len;
		ret = पढ़ो(fd, output, expected);
		अगर (ret != expected) अणु
			अगर (ret < 0)
				ret = -त्रुटि_सं;
			str = "data";
			जाओ err;
		पूर्ण
		reमुख्य -= ret;
	पूर्ण

	वापस;

err:
	अगर (ret < 0)
		prपूर्णांकk(UM_KERN_ERR "read_output - read of %s failed, "
		       "errno = %d\n", str, -ret);
	अन्यथा
		prपूर्णांकk(UM_KERN_ERR "read_output - read of %s failed, read only "
		       "%d of %d bytes\n", str, ret, expected);
पूर्ण

पूर्णांक net_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक n;

	n = पढ़ो(fd,  buf,  len);

	अगर ((n < 0) && (त्रुटि_सं == EAGAIN))
		वापस 0;
	अन्यथा अगर (n == 0)
		वापस -ENOTCONN;
	वापस n;
पूर्ण

पूर्णांक net_recvfrom(पूर्णांक fd, व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक n;

	CATCH_EINTR(n = recvfrom(fd,  buf,  len, 0, शून्य, शून्य));
	अगर (n < 0) अणु
		अगर (त्रुटि_सं == EAGAIN)
			वापस 0;
		वापस -त्रुटि_सं;
	पूर्ण
	अन्यथा अगर (n == 0)
		वापस -ENOTCONN;
	वापस n;
पूर्ण

पूर्णांक net_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक n;

	n = ग_लिखो(fd, buf, len);

	अगर ((n < 0) && (त्रुटि_सं == EAGAIN))
		वापस 0;
	अन्यथा अगर (n == 0)
		वापस -ENOTCONN;
	वापस n;
पूर्ण

पूर्णांक net_send(पूर्णांक fd, व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक n;

	CATCH_EINTR(n = send(fd, buf, len, 0));
	अगर (n < 0) अणु
		अगर (त्रुटि_सं == EAGAIN)
			वापस 0;
		वापस -त्रुटि_सं;
	पूर्ण
	अन्यथा अगर (n == 0)
		वापस -ENOTCONN;
	वापस n;
पूर्ण

पूर्णांक net_sendto(पूर्णांक fd, व्योम *buf, पूर्णांक len, व्योम *to, पूर्णांक sock_len)
अणु
	पूर्णांक n;

	CATCH_EINTR(n = sendto(fd, buf, len, 0, (काष्ठा sockaddr *) to,
			       sock_len));
	अगर (n < 0) अणु
		अगर (त्रुटि_सं == EAGAIN)
			वापस 0;
		वापस -त्रुटि_सं;
	पूर्ण
	अन्यथा अगर (n == 0)
		वापस -ENOTCONN;
	वापस n;
पूर्ण

काष्ठा change_pre_exec_data अणु
	पूर्णांक बंद_me;
	पूर्णांक मानक_निकास_fd;
पूर्ण;

अटल व्योम change_pre_exec(व्योम *arg)
अणु
	काष्ठा change_pre_exec_data *data = arg;

	बंद(data->बंद_me);
	dup2(data->मानक_निकास_fd, 1);
पूर्ण

अटल पूर्णांक change_tramp(अक्षर **argv, अक्षर *output, पूर्णांक output_len)
अणु
	पूर्णांक pid, fds[2], err;
	काष्ठा change_pre_exec_data pe_data;

	err = os_pipe(fds, 1, 0);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "change_tramp - pipe failed, err = %d\n",
		       -err);
		वापस err;
	पूर्ण
	pe_data.बंद_me = fds[0];
	pe_data.मानक_निकास_fd = fds[1];
	pid = run_helper(change_pre_exec, &pe_data, argv);

	अगर (pid > 0)	/* Aव्योम hang as we won't get data in failure हाल. */
		पढ़ो_output(fds[0], output, output_len);

	बंद(fds[0]);
	बंद(fds[1]);

	अगर (pid > 0)
		helper_रुको(pid);
	वापस pid;
पूर्ण

अटल व्योम change(अक्षर *dev, अक्षर *what, अचिन्हित अक्षर *addr,
		   अचिन्हित अक्षर *neपंचांगask)
अणु
	अक्षर addr_buf[माप("255.255.255.255\0")];
	अक्षर neपंचांगask_buf[माप("255.255.255.255\0")];
	अक्षर version[माप("nnnnn\0")];
	अक्षर *argv[] = अणु "uml_net", version, what, dev, addr_buf,
			 neपंचांगask_buf, शून्य पूर्ण;
	अक्षर *output;
	पूर्णांक output_len, pid;

	प्र_लिखो(version, "%d", UML_NET_VERSION);
	प्र_लिखो(addr_buf, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
	प्र_लिखो(neपंचांगask_buf, "%d.%d.%d.%d", neपंचांगask[0], neपंचांगask[1],
		neपंचांगask[2], neपंचांगask[3]);

	output_len = UM_KERN_PAGE_SIZE;
	output = uml_kदो_स्मृति(output_len, UM_GFP_KERNEL);
	अगर (output == शून्य)
		prपूर्णांकk(UM_KERN_ERR "change : failed to allocate output "
		       "buffer\n");

	pid = change_tramp(argv, output, output_len);
	अगर (pid < 0) अणु
		kमुक्त(output);
		वापस;
	पूर्ण

	अगर (output != शून्य) अणु
		prपूर्णांकk("%s", output);
		kमुक्त(output);
	पूर्ण
पूर्ण

व्योम खोलो_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask, व्योम *arg)
अणु
	change(arg, "add", addr, neपंचांगask);
पूर्ण

व्योम बंद_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask, व्योम *arg)
अणु
	change(arg, "del", addr, neपंचांगask);
पूर्ण

अक्षर *split_अगर_spec(अक्षर *str, ...)
अणु
	अक्षर **arg, *end, *ret = शून्य;
	बहु_सूची ap;

	बहु_शुरू(ap, str);
	जबतक ((arg = बहु_तर्क(ap, अक्षर **)) != शून्य) अणु
		अगर (*str == '\0')
			जाओ out;
		end = म_अक्षर(str, ',');
		अगर (end != str)
			*arg = str;
		अगर (end == शून्य)
			जाओ out;
		*end++ = '\0';
		str = end;
	पूर्ण
	ret = str;
out:
	बहु_पूर्ण(ap);
	वापस ret;
पूर्ण
