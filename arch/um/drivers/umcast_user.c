<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * user-mode-linux networking multicast transport
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright (C) 2001 by Harald Welte <laक्रमge@gnumonks.org>
 *
 * based on the existing uml-networking code, which is
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and
 * James Leu (jleu@mindspring.net).
 * Copyright (C) 2001 by various other people who didn't put their name here.
 *
 *
 */

#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <netinet/in.h>
#समावेश "umcast.h"
#समावेश <net_user.h>
#समावेश <um_दो_स्मृति.h>

अटल काष्ठा sockaddr_in *new_addr(अक्षर *addr, अचिन्हित लघु port)
अणु
	काष्ठा sockaddr_in *sin;

	sin = uml_kदो_स्मृति(माप(काष्ठा sockaddr_in), UM_GFP_KERNEL);
	अगर (sin == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "new_addr: allocation of sockaddr_in "
		       "failed\n");
		वापस शून्य;
	पूर्ण
	sin->sin_family = AF_INET;
	अगर (addr)
		sin->sin_addr.s_addr = in_aton(addr);
	अन्यथा
		sin->sin_addr.s_addr = INADDR_ANY;
	sin->sin_port = htons(port);
	वापस sin;
पूर्ण

अटल पूर्णांक umcast_user_init(व्योम *data, व्योम *dev)
अणु
	काष्ठा umcast_data *pri = data;

	pri->remote_addr = new_addr(pri->addr, pri->rport);
	अगर (pri->unicast)
		pri->listen_addr = new_addr(शून्य, pri->lport);
	अन्यथा
		pri->listen_addr = pri->remote_addr;
	pri->dev = dev;
	वापस 0;
पूर्ण

अटल व्योम umcast_हटाओ(व्योम *data)
अणु
	काष्ठा umcast_data *pri = data;

	kमुक्त(pri->listen_addr);
	अगर (pri->unicast)
		kमुक्त(pri->remote_addr);
	pri->listen_addr = pri->remote_addr = शून्य;
पूर्ण

अटल पूर्णांक umcast_खोलो(व्योम *data)
अणु
	काष्ठा umcast_data *pri = data;
	काष्ठा sockaddr_in *lsin = pri->listen_addr;
	काष्ठा sockaddr_in *rsin = pri->remote_addr;
	काष्ठा ip_mreq mreq;
	पूर्णांक fd, yes = 1, err = -EINVAL;


	अगर ((!pri->unicast && lsin->sin_addr.s_addr == 0) ||
	    (rsin->sin_addr.s_addr == 0) ||
	    (lsin->sin_port == 0) || (rsin->sin_port == 0))
		जाओ out;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	अगर (fd < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "umcast_open : data socket failed, "
		       "errno = %d\n", त्रुटि_सं);
		जाओ out;
	पूर्ण

	अगर (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, माप(yes)) < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "umcast_open: SO_REUSEADDR failed, "
		       "errno = %d\n", त्रुटि_सं);
		जाओ out_बंद;
	पूर्ण

	अगर (!pri->unicast) अणु
		/* set ttl according to config */
		अगर (setsockopt(fd, SOL_IP, IP_MULTICAST_TTL, &pri->ttl,
			       माप(pri->ttl)) < 0) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "umcast_open: IP_MULTICAST_TTL "
			       "failed, error = %d\n", त्रुटि_सं);
			जाओ out_बंद;
		पूर्ण

		/* set LOOP, so data करोes get fed back to local sockets */
		अगर (setsockopt(fd, SOL_IP, IP_MULTICAST_LOOP,
			       &yes, माप(yes)) < 0) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "umcast_open: IP_MULTICAST_LOOP "
			       "failed, error = %d\n", त्रुटि_सं);
			जाओ out_बंद;
		पूर्ण
	पूर्ण

	/* bind socket to the address */
	अगर (bind(fd, (काष्ठा sockaddr *) lsin, माप(*lsin)) < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "umcast_open : data bind failed, "
		       "errno = %d\n", त्रुटि_सं);
		जाओ out_बंद;
	पूर्ण

	अगर (!pri->unicast) अणु
		/* subscribe to the multicast group */
		mreq.imr_multiaddr.s_addr = lsin->sin_addr.s_addr;
		mreq.imr_पूर्णांकerface.s_addr = 0;
		अगर (setsockopt(fd, SOL_IP, IP_ADD_MEMBERSHIP,
			       &mreq, माप(mreq)) < 0) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "umcast_open: IP_ADD_MEMBERSHIP "
			       "failed, error = %d\n", त्रुटि_सं);
			prपूर्णांकk(UM_KERN_ERR "There appears not to be a "
			       "multicast-capable network interface on the "
			       "host.\n");
			prपूर्णांकk(UM_KERN_ERR "eth0 should be configured in order "
			       "to use the multicast transport.\n");
			जाओ out_बंद;
		पूर्ण
	पूर्ण

	वापस fd;

 out_बंद:
	बंद(fd);
 out:
	वापस err;
पूर्ण

अटल व्योम umcast_बंद(पूर्णांक fd, व्योम *data)
अणु
	काष्ठा umcast_data *pri = data;

	अगर (!pri->unicast) अणु
		काष्ठा ip_mreq mreq;
		काष्ठा sockaddr_in *lsin = pri->listen_addr;

		mreq.imr_multiaddr.s_addr = lsin->sin_addr.s_addr;
		mreq.imr_पूर्णांकerface.s_addr = 0;
		अगर (setsockopt(fd, SOL_IP, IP_DROP_MEMBERSHIP,
			       &mreq, माप(mreq)) < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "umcast_close: IP_DROP_MEMBERSHIP "
			       "failed, error = %d\n", त्रुटि_सं);
		पूर्ण
	पूर्ण

	बंद(fd);
पूर्ण

पूर्णांक umcast_user_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा umcast_data *pri)
अणु
	काष्ठा sockaddr_in *data_addr = pri->remote_addr;

	वापस net_sendto(fd, buf, len, data_addr, माप(*data_addr));
पूर्ण

स्थिर काष्ठा net_user_info umcast_user_info = अणु
	.init	= umcast_user_init,
	.खोलो	= umcast_खोलो,
	.बंद	= umcast_बंद,
	.हटाओ	= umcast_हटाओ,
	.add_address	= शून्य,
	.delete_address = शून्य,
	.mtu	= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADER_OTHER,
पूर्ण;
