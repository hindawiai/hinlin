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
#समावेश "etap.h"
#समावेश <net_kern.h>

काष्ठा ethertap_init अणु
	अक्षर *dev_name;
	अक्षर *gate_addr;
पूर्ण;

अटल व्योम etap_init(काष्ठा net_device *dev, व्योम *data)
अणु
	काष्ठा uml_net_निजी *pri;
	काष्ठा ethertap_data *epri;
	काष्ठा ethertap_init *init = data;

	pri = netdev_priv(dev);
	epri = (काष्ठा ethertap_data *) pri->user;
	epri->dev_name = init->dev_name;
	epri->gate_addr = init->gate_addr;
	epri->data_fd = -1;
	epri->control_fd = -1;
	epri->dev = dev;

	prपूर्णांकk(KERN_INFO "ethertap backend - %s", epri->dev_name);
	अगर (epri->gate_addr != शून्य)
		prपूर्णांकk(KERN_CONT ", IP = %s", epri->gate_addr);
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल पूर्णांक etap_पढ़ो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	पूर्णांक len;

	len = net_recvfrom(fd, skb_mac_header(skb),
			   skb->dev->mtu + 2 + ETH_HEADER_ETHERTAP);
	अगर (len <= 0)
		वापस(len);

	skb_pull(skb, 2);
	len -= 2;
	वापस len;
पूर्ण

अटल पूर्णांक etap_ग_लिखो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	skb_push(skb, 2);
	वापस net_send(fd, skb->data, skb->len);
पूर्ण

स्थिर काष्ठा net_kern_info ethertap_kern_info = अणु
	.init			= etap_init,
	.protocol		= eth_protocol,
	.पढ़ो			= etap_पढ़ो,
	.ग_लिखो 			= etap_ग_लिखो,
पूर्ण;

पूर्णांक ethertap_setup(अक्षर *str, अक्षर **mac_out, व्योम *data)
अणु
	काष्ठा ethertap_init *init = data;

	*init = ((काष्ठा ethertap_init)
		अणु .dev_name 	= शून्य,
		  .gate_addr 	= शून्य पूर्ण);
	अगर (tap_setup_common(str, "ethertap", &init->dev_name, mac_out,
			    &init->gate_addr))
		वापस 0;
	अगर (init->dev_name == शून्य) अणु
		prपूर्णांकk(KERN_ERR "ethertap_setup : Missing tap device name\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल काष्ठा transport ethertap_transport = अणु
	.list 		= LIST_HEAD_INIT(ethertap_transport.list),
	.name 		= "ethertap",
	.setup  	= ethertap_setup,
	.user 		= &ethertap_user_info,
	.kern 		= &ethertap_kern_info,
	.निजी_size 	= माप(काष्ठा ethertap_data),
	.setup_size 	= माप(काष्ठा ethertap_init),
पूर्ण;

अटल पूर्णांक रेजिस्टर_ethertap(व्योम)
अणु
	रेजिस्टर_transport(&ethertap_transport);
	वापस 0;
पूर्ण

late_initcall(रेजिस्टर_ethertap);
