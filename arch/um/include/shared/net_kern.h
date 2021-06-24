<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __UM_NET_KERN_H
#घोषणा __UM_NET_KERN_H

#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>

काष्ठा uml_net अणु
	काष्ठा list_head list;
	काष्ठा net_device *dev;
	काष्ठा platक्रमm_device pdev;
	पूर्णांक index;
पूर्ण;

काष्ठा uml_net_निजी अणु
	काष्ठा list_head list;
	spinlock_t lock;
	काष्ठा net_device *dev;
	काष्ठा समयr_list tl;

	काष्ठा work_काष्ठा work;
	पूर्णांक fd;
	अचिन्हित अक्षर mac[ETH_ALEN];
	पूर्णांक max_packet;
	अचिन्हित लघु (*protocol)(काष्ठा sk_buff *);
	पूर्णांक (*खोलो)(व्योम *);
	व्योम (*बंद)(पूर्णांक, व्योम *);
	व्योम (*हटाओ)(व्योम *);
	पूर्णांक (*पढ़ो)(पूर्णांक, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *);
	पूर्णांक (*ग_लिखो)(पूर्णांक, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *);

	व्योम (*add_address)(अचिन्हित अक्षर *, अचिन्हित अक्षर *, व्योम *);
	व्योम (*delete_address)(अचिन्हित अक्षर *, अचिन्हित अक्षर *, व्योम *);
	अक्षर user[0];
पूर्ण;

काष्ठा net_kern_info अणु
	व्योम (*init)(काष्ठा net_device *, व्योम *);
	अचिन्हित लघु (*protocol)(काष्ठा sk_buff *);
	पूर्णांक (*पढ़ो)(पूर्णांक, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *);
	पूर्णांक (*ग_लिखो)(पूर्णांक, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *);
पूर्ण;

काष्ठा transport अणु
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	पूर्णांक (* स्थिर setup)(अक्षर *, अक्षर **, व्योम *);
	स्थिर काष्ठा net_user_info *user;
	स्थिर काष्ठा net_kern_info *kern;
	स्थिर पूर्णांक निजी_size;
	स्थिर पूर्णांक setup_size;
पूर्ण;

बाह्य काष्ठा net_device *ether_init(पूर्णांक);
बाह्य अचिन्हित लघु ether_protocol(काष्ठा sk_buff *);
बाह्य पूर्णांक tap_setup_common(अक्षर *str, अक्षर *type, अक्षर **dev_name,
			    अक्षर **mac_out, अक्षर **gate_addr);
बाह्य व्योम रेजिस्टर_transport(काष्ठा transport *new);
बाह्य अचिन्हित लघु eth_protocol(काष्ठा sk_buff *skb);
बाह्य व्योम uml_net_setup_etheraddr(काष्ठा net_device *dev, अक्षर *str);


#पूर्ण_अगर
