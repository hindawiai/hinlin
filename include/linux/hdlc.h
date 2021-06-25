<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Generic HDLC support routines क्रम Linux
 *
 * Copyright (C) 1999-2005 Krzysztof Halasa <khc@pm.waw.pl>
 */
#अगर_अघोषित __HDLC_H
#घोषणा __HDLC_H


#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hdlc/ioctl.h>
#समावेश <uapi/linux/hdlc.h>

/* This काष्ठाure is a निजी property of HDLC protocols.
   Hardware drivers have no पूर्णांकerest here */

काष्ठा hdlc_proto अणु
	पूर्णांक (*खोलो)(काष्ठा net_device *dev);
	व्योम (*बंद)(काष्ठा net_device *dev);
	व्योम (*start)(काष्ठा net_device *dev); /* अगर खोलो & DCD */
	व्योम (*stop)(काष्ठा net_device *dev); /* अगर खोलो & !DCD */
	व्योम (*detach)(काष्ठा net_device *dev);
	पूर्णांक (*ioctl)(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr);
	__be16 (*type_trans)(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
	पूर्णांक (*netअगर_rx)(काष्ठा sk_buff *skb);
	netdev_tx_t (*xmit)(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
	काष्ठा module *module;
	काष्ठा hdlc_proto *next; /* next protocol in the list */
पूर्ण;


/* Poपूर्णांकed to by netdev_priv(dev) */
प्रकार काष्ठा hdlc_device अणु
	/* used by HDLC layer to take control over HDLC device from hw driver*/
	पूर्णांक (*attach)(काष्ठा net_device *dev,
		      अचिन्हित लघु encoding, अचिन्हित लघु parity);

	/* hardware driver must handle this instead of dev->hard_start_xmit */
	netdev_tx_t (*xmit)(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

	/* Things below are क्रम HDLC layer पूर्णांकernal use only */
	स्थिर काष्ठा hdlc_proto *proto;
	पूर्णांक carrier;
	पूर्णांक खोलो;
	spinlock_t state_lock;
	व्योम *state;
	व्योम *priv;
पूर्ण hdlc_device;



/* Exported from hdlc module */

/* Called by hardware driver when a user requests HDLC service */
पूर्णांक hdlc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);

/* Must be used by hardware driver on module startup/निकास */
#घोषणा रेजिस्टर_hdlc_device(dev)	रेजिस्टर_netdev(dev)
व्योम unरेजिस्टर_hdlc_device(काष्ठा net_device *dev);


व्योम रेजिस्टर_hdlc_protocol(काष्ठा hdlc_proto *proto);
व्योम unरेजिस्टर_hdlc_protocol(काष्ठा hdlc_proto *proto);

काष्ठा net_device *alloc_hdlcdev(व्योम *priv);

अटल अंतरभूत काष्ठा hdlc_device* dev_to_hdlc(काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

अटल __अंतरभूत__ व्योम debug_frame(स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;

	क्रम (i=0; i < skb->len; i++) अणु
		अगर (i == 100) अणु
			prपूर्णांकk("...\n");
			वापस;
		पूर्ण
		prपूर्णांकk(" %02X", skb->data[i]);
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण


/* Must be called by hardware driver when HDLC device is being खोलोed */
पूर्णांक hdlc_खोलो(काष्ठा net_device *dev);
/* Must be called by hardware driver when HDLC device is being बंदd */
व्योम hdlc_बंद(काष्ठा net_device *dev);
/* Must be poपूर्णांकed to by hw driver's dev->netdev_ops->nकरो_start_xmit */
netdev_tx_t hdlc_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

पूर्णांक attach_hdlc_protocol(काष्ठा net_device *dev, काष्ठा hdlc_proto *proto,
			 माप_प्रकार size);
/* May be used by hardware driver to gain control over HDLC device */
पूर्णांक detach_hdlc_protocol(काष्ठा net_device *dev);

अटल __अंतरभूत__ __be16 hdlc_type_trans(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);

	skb->dev = dev;
	skb_reset_mac_header(skb);

	अगर (hdlc->proto->type_trans)
		वापस hdlc->proto->type_trans(skb, dev);
	अन्यथा
		वापस htons(ETH_P_HDLC);
पूर्ण

#पूर्ण_अगर /* __HDLC_H */
