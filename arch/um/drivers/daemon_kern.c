<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and
 * James Leu (jleu@mindspring.net).
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright (C) 2001 by various other people who didn't put their name here.
 */

#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <net_kern.h>
#समावेश "daemon.h"

काष्ठा daemon_init अणु
	अक्षर *sock_type;
	अक्षर *ctl_sock;
पूर्ण;

अटल व्योम daemon_init(काष्ठा net_device *dev, व्योम *data)
अणु
	काष्ठा uml_net_निजी *pri;
	काष्ठा daemon_data *dpri;
	काष्ठा daemon_init *init = data;

	pri = netdev_priv(dev);
	dpri = (काष्ठा daemon_data *) pri->user;
	dpri->sock_type = init->sock_type;
	dpri->ctl_sock = init->ctl_sock;
	dpri->fd = -1;
	dpri->control = -1;
	dpri->dev = dev;
	/* We will मुक्त this poपूर्णांकer. If it contains crap we're burned. */
	dpri->ctl_addr = शून्य;
	dpri->data_addr = शून्य;
	dpri->local_addr = शून्य;

	prपूर्णांकk("daemon backend (uml_switch version %d) - %s:%s",
	       SWITCH_VERSION, dpri->sock_type, dpri->ctl_sock);
	prपूर्णांकk("\n");
पूर्ण

अटल पूर्णांक daemon_पढ़ो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस net_recvfrom(fd, skb_mac_header(skb),
			    skb->dev->mtu + ETH_HEADER_OTHER);
पूर्ण

अटल पूर्णांक daemon_ग_लिखो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस daemon_user_ग_लिखो(fd, skb->data, skb->len,
				 (काष्ठा daemon_data *) &lp->user);
पूर्ण

अटल स्थिर काष्ठा net_kern_info daemon_kern_info = अणु
	.init			= daemon_init,
	.protocol		= eth_protocol,
	.पढ़ो			= daemon_पढ़ो,
	.ग_लिखो			= daemon_ग_लिखो,
पूर्ण;

अटल पूर्णांक daemon_setup(अक्षर *str, अक्षर **mac_out, व्योम *data)
अणु
	काष्ठा daemon_init *init = data;
	अक्षर *reमुख्य;

	*init = ((काष्ठा daemon_init)
		अणु .sock_type 		= "unix",
		  .ctl_sock 		= "/tmp/uml.ctl" पूर्ण);

	reमुख्य = split_अगर_spec(str, mac_out, &init->sock_type, &init->ctl_sock,
			       शून्य);
	अगर (reमुख्य != शून्य)
		prपूर्णांकk(KERN_WARNING "daemon_setup : Ignoring data socket "
		       "specification\n");

	वापस 1;
पूर्ण

अटल काष्ठा transport daemon_transport = अणु
	.list 		= LIST_HEAD_INIT(daemon_transport.list),
	.name 		= "daemon",
	.setup  	= daemon_setup,
	.user 		= &daemon_user_info,
	.kern 		= &daemon_kern_info,
	.निजी_size 	= माप(काष्ठा daemon_data),
	.setup_size 	= माप(काष्ठा daemon_init),
पूर्ण;

अटल पूर्णांक रेजिस्टर_daemon(व्योम)
अणु
	रेजिस्टर_transport(&daemon_transport);
	वापस 0;
पूर्ण

late_initcall(रेजिस्टर_daemon);
