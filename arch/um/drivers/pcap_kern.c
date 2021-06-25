<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <net_kern.h>
#समावेश "pcap_user.h"

काष्ठा pcap_init अणु
	अक्षर *host_अगर;
	पूर्णांक promisc;
	पूर्णांक optimize;
	अक्षर *filter;
पूर्ण;

व्योम pcap_init(काष्ठा net_device *dev, व्योम *data)
अणु
	काष्ठा uml_net_निजी *pri;
	काष्ठा pcap_data *ppri;
	काष्ठा pcap_init *init = data;

	pri = netdev_priv(dev);
	ppri = (काष्ठा pcap_data *) pri->user;
	ppri->host_अगर = init->host_अगर;
	ppri->promisc = init->promisc;
	ppri->optimize = init->optimize;
	ppri->filter = init->filter;

	prपूर्णांकk("pcap backend, host interface %s\n", ppri->host_अगर);
पूर्ण

अटल पूर्णांक pcap_पढ़ो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस pcap_user_पढ़ो(fd, skb_mac_header(skb),
			      skb->dev->mtu + ETH_HEADER_OTHER,
			      (काष्ठा pcap_data *) &lp->user);
पूर्ण

अटल पूर्णांक pcap_ग_लिखो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	वापस -EPERM;
पूर्ण

अटल स्थिर काष्ठा net_kern_info pcap_kern_info = अणु
	.init			= pcap_init,
	.protocol		= eth_protocol,
	.पढ़ो			= pcap_पढ़ो,
	.ग_लिखो			= pcap_ग_लिखो,
पूर्ण;

पूर्णांक pcap_setup(अक्षर *str, अक्षर **mac_out, व्योम *data)
अणु
	काष्ठा pcap_init *init = data;
	अक्षर *reमुख्य, *host_अगर = शून्य, *options[2] = अणु शून्य, शून्य पूर्ण;
	पूर्णांक i;

	*init = ((काष्ठा pcap_init)
		अणु .host_अगर 	= "eth0",
		  .promisc 	= 1,
		  .optimize 	= 0,
		  .filter 	= शून्य पूर्ण);

	reमुख्य = split_अगर_spec(str, &host_अगर, &init->filter,
			       &options[0], &options[1], mac_out, शून्य);
	अगर (reमुख्य != शून्य) अणु
		prपूर्णांकk(KERN_ERR "pcap_setup - Extra garbage on "
		       "specification : '%s'\n", reमुख्य);
		वापस 0;
	पूर्ण

	अगर (host_अगर != शून्य)
		init->host_अगर = host_अगर;

	क्रम (i = 0; i < ARRAY_SIZE(options); i++) अणु
		अगर (options[i] == शून्य)
			जारी;
		अगर (!म_भेद(options[i], "promisc"))
			init->promisc = 1;
		अन्यथा अगर (!म_भेद(options[i], "nopromisc"))
			init->promisc = 0;
		अन्यथा अगर (!म_भेद(options[i], "optimize"))
			init->optimize = 1;
		अन्यथा अगर (!म_भेद(options[i], "nooptimize"))
			init->optimize = 0;
		अन्यथा अणु
			prपूर्णांकk(KERN_ERR "pcap_setup : bad option - '%s'\n",
			       options[i]);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल काष्ठा transport pcap_transport = अणु
	.list 		= LIST_HEAD_INIT(pcap_transport.list),
	.name 		= "pcap",
	.setup  	= pcap_setup,
	.user 		= &pcap_user_info,
	.kern 		= &pcap_kern_info,
	.निजी_size 	= माप(काष्ठा pcap_data),
	.setup_size 	= माप(काष्ठा pcap_init),
पूर्ण;

अटल पूर्णांक रेजिस्टर_pcap(व्योम)
अणु
	रेजिस्टर_transport(&pcap_transport);
	वापस 0;
पूर्ण

late_initcall(रेजिस्टर_pcap);
