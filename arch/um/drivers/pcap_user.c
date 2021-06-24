<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <त्रुटिसं.स>
#समावेश <pcap.h>
#समावेश <माला.स>
#समावेश <यंत्र/types.h>
#समावेश <net_user.h>
#समावेश "pcap_user.h"
#समावेश <um_दो_स्मृति.h>

#घोषणा PCAP_FD(p) (*(पूर्णांक *)(p))

अटल पूर्णांक pcap_user_init(व्योम *data, व्योम *dev)
अणु
	काष्ठा pcap_data *pri = data;
	pcap_t *p;
	अक्षर errors[PCAP_ERRBUF_SIZE];

	p = pcap_खोलो_live(pri->host_अगर, ETH_MAX_PACKET + ETH_HEADER_OTHER,
			   pri->promisc, 0, errors);
	अगर (p == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "pcap_user_init : pcap_open_live failed - "
		       "'%s'\n", errors);
		वापस -EINVAL;
	पूर्ण

	pri->dev = dev;
	pri->pcap = p;
	वापस 0;
पूर्ण

अटल पूर्णांक pcap_user_खोलो(व्योम *data)
अणु
	काष्ठा pcap_data *pri = data;
	__u32 neपंचांगask;
	पूर्णांक err;

	अगर (pri->pcap == शून्य)
		वापस -ENODEV;

	अगर (pri->filter != शून्य) अणु
		err = dev_neपंचांगask(pri->dev, &neपंचांगask);
		अगर (err < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "pcap_user_open : dev_netmask failed\n");
			वापस -EIO;
		पूर्ण

		pri->compiled = uml_kदो_स्मृति(माप(काष्ठा bpf_program),
					UM_GFP_KERNEL);
		अगर (pri->compiled == शून्य) अणु
			prपूर्णांकk(UM_KERN_ERR "pcap_user_open : kmalloc failed\n");
			वापस -ENOMEM;
		पूर्ण

		err = pcap_compile(pri->pcap,
				   (काष्ठा bpf_program *) pri->compiled,
				   pri->filter, pri->optimize, neपंचांगask);
		अगर (err < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "pcap_user_open : pcap_compile failed - "
			       "'%s'\n", pcap_geterr(pri->pcap));
			जाओ out;
		पूर्ण

		err = pcap_setfilter(pri->pcap, pri->compiled);
		अगर (err < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "pcap_user_open : pcap_setfilter "
			       "failed - '%s'\n", pcap_geterr(pri->pcap));
			जाओ out;
		पूर्ण
	पूर्ण

	वापस PCAP_FD(pri->pcap);

 out:
	kमुक्त(pri->compiled);
	वापस -EIO;
पूर्ण

अटल व्योम pcap_हटाओ(व्योम *data)
अणु
	काष्ठा pcap_data *pri = data;

	अगर (pri->compiled != शून्य)
		pcap_मुक्तcode(pri->compiled);

	अगर (pri->pcap != शून्य)
		pcap_बंद(pri->pcap);
पूर्ण

काष्ठा pcap_handler_data अणु
	अक्षर *buffer;
	पूर्णांक len;
पूर्ण;

अटल व्योम handler(u_अक्षर *data, स्थिर काष्ठा pcap_pkthdr *header,
		    स्थिर u_अक्षर *packet)
अणु
	पूर्णांक len;

	काष्ठा pcap_handler_data *hdata = (काष्ठा pcap_handler_data *) data;

	len = hdata->len < header->caplen ? hdata->len : header->caplen;
	स_नकल(hdata->buffer, packet, len);
	hdata->len = len;
पूर्ण

पूर्णांक pcap_user_पढ़ो(पूर्णांक fd, व्योम *buffer, पूर्णांक len, काष्ठा pcap_data *pri)
अणु
	काष्ठा pcap_handler_data hdata = ((काष्ठा pcap_handler_data)
		                          अणु .buffer  	= buffer,
					    .len 	= len पूर्ण);
	पूर्णांक n;

	n = pcap_dispatch(pri->pcap, 1, handler, (u_अक्षर *) &hdata);
	अगर (n < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "pcap_dispatch failed - %s\n",
		       pcap_geterr(pri->pcap));
		वापस -EIO;
	पूर्ण
	अन्यथा अगर (n == 0)
		वापस 0;
	वापस hdata.len;
पूर्ण

स्थिर काष्ठा net_user_info pcap_user_info = अणु
	.init		= pcap_user_init,
	.खोलो		= pcap_user_खोलो,
	.बंद	 	= शून्य,
	.हटाओ	 	= pcap_हटाओ,
	.add_address	= शून्य,
	.delete_address = शून्य,
	.mtu		= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADER_OTHER,
पूर्ण;
