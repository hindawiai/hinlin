<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * user-mode-linux networking multicast transport
 * Copyright (C) 2001 by Harald Welte <laक्रमge@gnumonks.org>
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 *
 * based on the existing uml-networking code, which is
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and
 * James Leu (jleu@mindspring.net).
 * Copyright (C) 2001 by various other people who didn't put their name here.
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश "umcast.h"
#समावेश <net_kern.h>

काष्ठा umcast_init अणु
	अक्षर *addr;
	पूर्णांक lport;
	पूर्णांक rport;
	पूर्णांक ttl;
	bool unicast;
पूर्ण;

अटल व्योम umcast_init(काष्ठा net_device *dev, व्योम *data)
अणु
	काष्ठा uml_net_निजी *pri;
	काष्ठा umcast_data *dpri;
	काष्ठा umcast_init *init = data;

	pri = netdev_priv(dev);
	dpri = (काष्ठा umcast_data *) pri->user;
	dpri->addr = init->addr;
	dpri->lport = init->lport;
	dpri->rport = init->rport;
	dpri->unicast = init->unicast;
	dpri->ttl = init->ttl;
	dpri->dev = dev;

	अगर (dpri->unicast) अणु
		prपूर्णांकk(KERN_INFO "ucast backend address: %s:%u listen port: "
		       "%u\n", dpri->addr, dpri->rport, dpri->lport);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "mcast backend multicast address: %s:%u, "
		       "TTL:%u\n", dpri->addr, dpri->lport, dpri->ttl);
	पूर्ण
पूर्ण

अटल पूर्णांक umcast_पढ़ो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस net_recvfrom(fd, skb_mac_header(skb),
			    skb->dev->mtu + ETH_HEADER_OTHER);
पूर्ण

अटल पूर्णांक umcast_ग_लिखो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस umcast_user_ग_लिखो(fd, skb->data, skb->len,
				(काष्ठा umcast_data *) &lp->user);
पूर्ण

अटल स्थिर काष्ठा net_kern_info umcast_kern_info = अणु
	.init			= umcast_init,
	.protocol		= eth_protocol,
	.पढ़ो			= umcast_पढ़ो,
	.ग_लिखो			= umcast_ग_लिखो,
पूर्ण;

अटल पूर्णांक mcast_setup(अक्षर *str, अक्षर **mac_out, व्योम *data)
अणु
	काष्ठा umcast_init *init = data;
	अक्षर *port_str = शून्य, *ttl_str = शून्य, *reमुख्य;
	अक्षर *last;

	*init = ((काष्ठा umcast_init)
		अणु .addr	= "239.192.168.1",
		  .lport	= 1102,
		  .ttl	= 1 पूर्ण);

	reमुख्य = split_अगर_spec(str, mac_out, &init->addr, &port_str, &ttl_str,
			       शून्य);
	अगर (reमुख्य != शून्य) अणु
		prपूर्णांकk(KERN_ERR "mcast_setup - Extra garbage on "
		       "specification : '%s'\n", reमुख्य);
		वापस 0;
	पूर्ण

	अगर (port_str != शून्य) अणु
		init->lport = simple_म_से_अदीर्घ(port_str, &last, 10);
		अगर ((*last != '\0') || (last == port_str)) अणु
			prपूर्णांकk(KERN_ERR "mcast_setup - Bad port : '%s'\n",
			       port_str);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (ttl_str != शून्य) अणु
		init->ttl = simple_म_से_अदीर्घ(ttl_str, &last, 10);
		अगर ((*last != '\0') || (last == ttl_str)) अणु
			prपूर्णांकk(KERN_ERR "mcast_setup - Bad ttl : '%s'\n",
			       ttl_str);
			वापस 0;
		पूर्ण
	पूर्ण

	init->unicast = false;
	init->rport = init->lport;

	prपूर्णांकk(KERN_INFO "Configured mcast device: %s:%u-%u\n", init->addr,
	       init->lport, init->ttl);

	वापस 1;
पूर्ण

अटल पूर्णांक ucast_setup(अक्षर *str, अक्षर **mac_out, व्योम *data)
अणु
	काष्ठा umcast_init *init = data;
	अक्षर *lport_str = शून्य, *rport_str = शून्य, *reमुख्य;
	अक्षर *last;

	*init = ((काष्ठा umcast_init)
		अणु .addr		= "",
		  .lport	= 1102,
		  .rport	= 1102 पूर्ण);

	reमुख्य = split_अगर_spec(str, mac_out, &init->addr,
			       &lport_str, &rport_str, शून्य);
	अगर (reमुख्य != शून्य) अणु
		prपूर्णांकk(KERN_ERR "ucast_setup - Extra garbage on "
		       "specification : '%s'\n", reमुख्य);
		वापस 0;
	पूर्ण

	अगर (lport_str != शून्य) अणु
		init->lport = simple_म_से_अदीर्घ(lport_str, &last, 10);
		अगर ((*last != '\0') || (last == lport_str)) अणु
			prपूर्णांकk(KERN_ERR "ucast_setup - Bad listen port : "
			       "'%s'\n", lport_str);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (rport_str != शून्य) अणु
		init->rport = simple_म_से_अदीर्घ(rport_str, &last, 10);
		अगर ((*last != '\0') || (last == rport_str)) अणु
			prपूर्णांकk(KERN_ERR "ucast_setup - Bad remote port : "
			       "'%s'\n", rport_str);
			वापस 0;
		पूर्ण
	पूर्ण

	init->unicast = true;

	prपूर्णांकk(KERN_INFO "Configured ucast device: :%u -> %s:%u\n",
	       init->lport, init->addr, init->rport);

	वापस 1;
पूर्ण

अटल काष्ठा transport mcast_transport = अणु
	.list	= LIST_HEAD_INIT(mcast_transport.list),
	.name	= "mcast",
	.setup	= mcast_setup,
	.user	= &umcast_user_info,
	.kern	= &umcast_kern_info,
	.निजी_size	= माप(काष्ठा umcast_data),
	.setup_size	= माप(काष्ठा umcast_init),
पूर्ण;

अटल काष्ठा transport ucast_transport = अणु
	.list	= LIST_HEAD_INIT(ucast_transport.list),
	.name	= "ucast",
	.setup	= ucast_setup,
	.user	= &umcast_user_info,
	.kern	= &umcast_kern_info,
	.निजी_size	= माप(काष्ठा umcast_data),
	.setup_size	= माप(काष्ठा umcast_init),
पूर्ण;

अटल पूर्णांक रेजिस्टर_umcast(व्योम)
अणु
	रेजिस्टर_transport(&mcast_transport);
	रेजिस्टर_transport(&ucast_transport);
	वापस 0;
पूर्ण

late_initcall(रेजिस्टर_umcast);
