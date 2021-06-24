<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <net_kern.h>
#समावेश "tuntap.h"

काष्ठा tuntap_init अणु
	अक्षर *dev_name;
	अक्षर *gate_addr;
पूर्ण;

अटल व्योम tuntap_init(काष्ठा net_device *dev, व्योम *data)
अणु
	काष्ठा uml_net_निजी *pri;
	काष्ठा tuntap_data *tpri;
	काष्ठा tuntap_init *init = data;

	pri = netdev_priv(dev);
	tpri = (काष्ठा tuntap_data *) pri->user;
	tpri->dev_name = init->dev_name;
	tpri->fixed_config = (init->dev_name != शून्य);
	tpri->gate_addr = init->gate_addr;
	tpri->fd = -1;
	tpri->dev = dev;

	prपूर्णांकk(KERN_INFO "TUN/TAP backend - ");
	अगर (tpri->gate_addr != शून्य)
		prपूर्णांकk(KERN_CONT "IP = %s", tpri->gate_addr);
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल पूर्णांक tuntap_पढ़ो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस net_पढ़ो(fd, skb_mac_header(skb),
			skb->dev->mtu + ETH_HEADER_OTHER);
पूर्ण

अटल पूर्णांक tuntap_ग_लिखो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस net_ग_लिखो(fd, skb->data, skb->len);
पूर्ण

स्थिर काष्ठा net_kern_info tuntap_kern_info = अणु
	.init			= tuntap_init,
	.protocol		= eth_protocol,
	.पढ़ो			= tuntap_पढ़ो,
	.ग_लिखो 			= tuntap_ग_लिखो,
पूर्ण;

पूर्णांक tuntap_setup(अक्षर *str, अक्षर **mac_out, व्योम *data)
अणु
	काष्ठा tuntap_init *init = data;

	*init = ((काष्ठा tuntap_init)
		अणु .dev_name 	= शून्य,
		  .gate_addr 	= शून्य पूर्ण);
	अगर (tap_setup_common(str, "tuntap", &init->dev_name, mac_out,
			    &init->gate_addr))
		वापस 0;

	वापस 1;
पूर्ण

अटल काष्ठा transport tuntap_transport = अणु
	.list 		= LIST_HEAD_INIT(tuntap_transport.list),
	.name 		= "tuntap",
	.setup  	= tuntap_setup,
	.user 		= &tuntap_user_info,
	.kern 		= &tuntap_kern_info,
	.निजी_size 	= माप(काष्ठा tuntap_data),
	.setup_size 	= माप(काष्ठा tuntap_init),
पूर्ण;

अटल पूर्णांक रेजिस्टर_tuntap(व्योम)
अणु
	रेजिस्टर_transport(&tuntap_transport);
	वापस 0;
पूर्ण

late_initcall(रेजिस्टर_tuntap);
