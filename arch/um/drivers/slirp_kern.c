<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/माला.स>
#समावेश <net_kern.h>
#समावेश <net_user.h>
#समावेश "slirp.h"

काष्ठा slirp_init अणु
	काष्ठा arg_list_dummy_wrapper argw;  /* XXX should be simpler... */
पूर्ण;

व्योम slirp_init(काष्ठा net_device *dev, व्योम *data)
अणु
	काष्ठा uml_net_निजी *निजी;
	काष्ठा slirp_data *spri;
	काष्ठा slirp_init *init = data;
	पूर्णांक i;

	निजी = netdev_priv(dev);
	spri = (काष्ठा slirp_data *) निजी->user;

	spri->argw = init->argw;
	spri->pid = -1;
	spri->slave = -1;
	spri->dev = dev;

	slip_proto_init(&spri->slip);

	dev->hard_header_len = 0;
	dev->header_ops = शून्य;
	dev->addr_len = 0;
	dev->type = ARPHRD_SLIP;
	dev->tx_queue_len = 256;
	dev->flags = IFF_NOARP;
	prपूर्णांकk("SLIRP backend - command line:");
	क्रम (i = 0; spri->argw.argv[i] != शून्य; i++)
		prपूर्णांकk(" '%s'",spri->argw.argv[i]);
	prपूर्णांकk("\n");
पूर्ण

अटल अचिन्हित लघु slirp_protocol(काष्ठा sk_buff *skbuff)
अणु
	वापस htons(ETH_P_IP);
पूर्ण

अटल पूर्णांक slirp_पढ़ो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस slirp_user_पढ़ो(fd, skb_mac_header(skb), skb->dev->mtu,
			       (काष्ठा slirp_data *) &lp->user);
पूर्ण

अटल पूर्णांक slirp_ग_लिखो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस slirp_user_ग_लिखो(fd, skb->data, skb->len,
				(काष्ठा slirp_data *) &lp->user);
पूर्ण

स्थिर काष्ठा net_kern_info slirp_kern_info = अणु
	.init			= slirp_init,
	.protocol		= slirp_protocol,
	.पढ़ो			= slirp_पढ़ो,
	.ग_लिखो			= slirp_ग_लिखो,
पूर्ण;

अटल पूर्णांक slirp_setup(अक्षर *str, अक्षर **mac_out, व्योम *data)
अणु
	काष्ठा slirp_init *init = data;
	पूर्णांक i=0;

	*init = ((काष्ठा slirp_init) अणु .argw = अणु अणु "slirp", शून्य  पूर्ण पूर्ण पूर्ण);

	str = split_अगर_spec(str, mac_out, शून्य);

	अगर (str == शून्य) /* no command line given after MAC addr */
		वापस 1;

	करो अणु
		अगर (i >= SLIRP_MAX_ARGS - 1) अणु
			prपूर्णांकk(KERN_WARNING "slirp_setup: truncating slirp "
			       "arguments\n");
			अवरोध;
		पूर्ण
		init->argw.argv[i++] = str;
		जबतक(*str && *str!=',') अणु
			अगर (*str == '_')
				*str=' ';
			str++;
		पूर्ण
		अगर (*str != ',')
			अवरोध;
		*str++ = '\0';
	पूर्ण जबतक (1);

	init->argw.argv[i] = शून्य;
	वापस 1;
पूर्ण

अटल काष्ठा transport slirp_transport = अणु
	.list 		= LIST_HEAD_INIT(slirp_transport.list),
	.name 		= "slirp",
	.setup  	= slirp_setup,
	.user 		= &slirp_user_info,
	.kern 		= &slirp_kern_info,
	.निजी_size 	= माप(काष्ठा slirp_data),
	.setup_size 	= माप(काष्ठा slirp_init),
पूर्ण;

अटल पूर्णांक रेजिस्टर_slirp(व्योम)
अणु
	रेजिस्टर_transport(&slirp_transport);
	वापस 0;
पूर्ण

late_initcall(रेजिस्टर_slirp);
