<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and
 * James Leu (jleu@mindspring.net).
 * Copyright (C) 2001 by various other people who didn't put their name here.
 */

#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <sys/समय.स>
#समावेश <sys/un.h>
#समावेश "daemon.h"
#समावेश <net_user.h>
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

क्रमागत request_type अणु REQ_NEW_CONTROL पूर्ण;

#घोषणा SWITCH_MAGIC 0xfeedface

काष्ठा request_v3 अणु
	uपूर्णांक32_t magic;
	uपूर्णांक32_t version;
	क्रमागत request_type type;
	काष्ठा sockaddr_un sock;
पूर्ण;

अटल काष्ठा sockaddr_un *new_addr(व्योम *name, पूर्णांक len)
अणु
	काष्ठा sockaddr_un *sun;

	sun = uml_kदो_स्मृति(माप(काष्ठा sockaddr_un), UM_GFP_KERNEL);
	अगर (sun == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "new_addr: allocation of sockaddr_un "
		       "failed\n");
		वापस शून्य;
	पूर्ण
	sun->sun_family = AF_UNIX;
	स_नकल(sun->sun_path, name, len);
	वापस sun;
पूर्ण

अटल पूर्णांक connect_to_चयन(काष्ठा daemon_data *pri)
अणु
	काष्ठा sockaddr_un *ctl_addr = pri->ctl_addr;
	काष्ठा sockaddr_un *local_addr = pri->local_addr;
	काष्ठा sockaddr_un *sun;
	काष्ठा request_v3 req;
	पूर्णांक fd, n, err;

	pri->control = socket(AF_UNIX, SOCK_STREAM, 0);
	अगर (pri->control < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "daemon_open : control socket failed, "
		       "errno = %d\n", -err);
		वापस err;
	पूर्ण

	अगर (connect(pri->control, (काष्ठा sockaddr *) ctl_addr,
		   माप(*ctl_addr)) < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "daemon_open : control connect failed, "
		       "errno = %d\n", -err);
		जाओ out;
	पूर्ण

	fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	अगर (fd < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "daemon_open : data socket failed, "
		       "errno = %d\n", -err);
		जाओ out;
	पूर्ण
	अगर (bind(fd, (काष्ठा sockaddr *) local_addr, माप(*local_addr)) < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "daemon_open : data bind failed, "
		       "errno = %d\n", -err);
		जाओ out_बंद;
	पूर्ण

	sun = uml_kदो_स्मृति(माप(काष्ठा sockaddr_un), UM_GFP_KERNEL);
	अगर (sun == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "new_addr: allocation of sockaddr_un "
		       "failed\n");
		err = -ENOMEM;
		जाओ out_बंद;
	पूर्ण

	req.magic = SWITCH_MAGIC;
	req.version = SWITCH_VERSION;
	req.type = REQ_NEW_CONTROL;
	req.sock = *local_addr;
	n = ग_लिखो(pri->control, &req, माप(req));
	अगर (n != माप(req)) अणु
		prपूर्णांकk(UM_KERN_ERR "daemon_open : control setup request "
		       "failed, err = %d\n", -त्रुटि_सं);
		err = -ENOTCONN;
		जाओ out_मुक्त;
	पूर्ण

	n = पढ़ो(pri->control, sun, माप(*sun));
	अगर (n != माप(*sun)) अणु
		prपूर्णांकk(UM_KERN_ERR "daemon_open : read of data socket failed, "
		       "err = %d\n", -त्रुटि_सं);
		err = -ENOTCONN;
		जाओ out_मुक्त;
	पूर्ण

	pri->data_addr = sun;
	वापस fd;

 out_मुक्त:
	kमुक्त(sun);
 out_बंद:
	बंद(fd);
 out:
	बंद(pri->control);
	वापस err;
पूर्ण

अटल पूर्णांक daemon_user_init(व्योम *data, व्योम *dev)
अणु
	काष्ठा daemon_data *pri = data;
	काष्ठा समयval tv;
	काष्ठा अणु
		अक्षर zero;
		पूर्णांक pid;
		पूर्णांक usecs;
	पूर्ण name;

	अगर (!म_भेद(pri->sock_type, "unix"))
		pri->ctl_addr = new_addr(pri->ctl_sock,
					 म_माप(pri->ctl_sock) + 1);
	name.zero = 0;
	name.pid = os_getpid();
	समय_लोofday(&tv, शून्य);
	name.usecs = tv.tv_usec;
	pri->local_addr = new_addr(&name, माप(name));
	pri->dev = dev;
	pri->fd = connect_to_चयन(pri);
	अगर (pri->fd < 0) अणु
		kमुक्त(pri->local_addr);
		pri->local_addr = शून्य;
		वापस pri->fd;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक daemon_खोलो(व्योम *data)
अणु
	काष्ठा daemon_data *pri = data;
	वापस pri->fd;
पूर्ण

अटल व्योम daemon_हटाओ(व्योम *data)
अणु
	काष्ठा daemon_data *pri = data;

	बंद(pri->fd);
	pri->fd = -1;
	बंद(pri->control);
	pri->control = -1;

	kमुक्त(pri->data_addr);
	pri->data_addr = शून्य;
	kमुक्त(pri->ctl_addr);
	pri->ctl_addr = शून्य;
	kमुक्त(pri->local_addr);
	pri->local_addr = शून्य;
पूर्ण

पूर्णांक daemon_user_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा daemon_data *pri)
अणु
	काष्ठा sockaddr_un *data_addr = pri->data_addr;

	वापस net_sendto(fd, buf, len, data_addr, माप(*data_addr));
पूर्ण

स्थिर काष्ठा net_user_info daemon_user_info = अणु
	.init		= daemon_user_init,
	.खोलो		= daemon_खोलो,
	.बंद	 	= शून्य,
	.हटाओ	 	= daemon_हटाओ,
	.add_address	= शून्य,
	.delete_address = शून्य,
	.mtu		= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADER_OTHER,
पूर्ण;
