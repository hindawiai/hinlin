<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <net_kern.h>
#समावेश "slip.h"

काष्ठा slip_init अणु
	अक्षर *gate_addr;
पूर्ण;

अटल व्योम slip_init(काष्ठा net_device *dev, व्योम *data)
अणु
	काष्ठा uml_net_निजी *निजी;
	काष्ठा slip_data *spri;
	काष्ठा slip_init *init = data;

	निजी = netdev_priv(dev);
	spri = (काष्ठा slip_data *) निजी->user;

	स_रखो(spri->name, 0, माप(spri->name));
	spri->addr = शून्य;
	spri->gate_addr = init->gate_addr;
	spri->slave = -1;
	spri->dev = dev;

	slip_proto_init(&spri->slip);

	dev->hard_header_len = 0;
	dev->header_ops = शून्य;
	dev->addr_len = 0;
	dev->type = ARPHRD_SLIP;
	dev->tx_queue_len = 256;
	dev->flags = IFF_NOARP;
	prपूर्णांकk("SLIP backend - SLIP IP = %s\n", spri->gate_addr);
पूर्ण

अटल अचिन्हित लघु slip_protocol(काष्ठा sk_buff *skbuff)
अणु
	वापस htons(ETH_P_IP);
पूर्ण

अटल पूर्णांक slip_पढ़ो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस slip_user_पढ़ो(fd, skb_mac_header(skb), skb->dev->mtu,
			      (काष्ठा slip_data *) &lp->user);
पूर्ण

अटल पूर्णांक slip_ग_लिखो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस slip_user_ग_लिखो(fd, skb->data, skb->len,
			       (काष्ठा slip_data *) &lp->user);
पूर्ण

अटल स्थिर काष्ठा net_kern_info slip_kern_info = अणु
	.init			= slip_init,
	.protocol		= slip_protocol,
	.पढ़ो			= slip_पढ़ो,
	.ग_लिखो			= slip_ग_लिखो,
पूर्ण;

अटल पूर्णांक slip_setup(अक्षर *str, अक्षर **mac_out, व्योम *data)
अणु
	काष्ठा slip_init *init = data;

	*init = ((काष्ठा slip_init) अणु .gate_addr = शून्य पूर्ण);

	अगर (str[0] != '\0')
		init->gate_addr = str;
	वापस 1;
पूर्ण

अटल काष्ठा transport slip_transport = अणु
	.list 		= LIST_HEAD_INIT(slip_transport.list),
	.name 		= "slip",
	.setup  	= slip_setup,
	.user 		= &slip_user_info,
	.kern 		= &slip_kern_info,
	.निजी_size 	= माप(काष्ठा slip_data),
	.setup_size 	= माप(काष्ठा slip_init),
पूर्ण;

अटल पूर्णांक रेजिस्टर_slip(व्योम)
अणु
	रेजिस्टर_transport(&slip_transport);
	वापस 0;
पूर्ण

late_initcall(रेजिस्टर_slip);
