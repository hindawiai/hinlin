<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * These are the खुला elements of the Linux LAPB module.
 */

#अगर_अघोषित	LAPB_KERNEL_H
#घोषणा	LAPB_KERNEL_H

#घोषणा	LAPB_OK			0
#घोषणा	LAPB_BADTOKEN		1
#घोषणा	LAPB_INVALUE		2
#घोषणा	LAPB_CONNECTED		3
#घोषणा	LAPB_NOTCONNECTED	4
#घोषणा	LAPB_REFUSED		5
#घोषणा	LAPB_TIMEDOUT		6
#घोषणा	LAPB_NOMEM		7

#घोषणा	LAPB_STANDARD		0x00
#घोषणा	LAPB_EXTENDED		0x01

#घोषणा	LAPB_SLP		0x00
#घोषणा	LAPB_MLP		0x02

#घोषणा	LAPB_DTE		0x00
#घोषणा	LAPB_DCE		0x04

काष्ठा lapb_रेजिस्टर_काष्ठा अणु
	व्योम (*connect_confirmation)(काष्ठा net_device *dev, पूर्णांक reason);
	व्योम (*connect_indication)(काष्ठा net_device *dev, पूर्णांक reason);
	व्योम (*disconnect_confirmation)(काष्ठा net_device *dev, पूर्णांक reason);
	व्योम (*disconnect_indication)(काष्ठा net_device *dev, पूर्णांक reason);
	पूर्णांक  (*data_indication)(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
	व्योम (*data_transmit)(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा lapb_parms_काष्ठा अणु
	अचिन्हित पूर्णांक t1;
	अचिन्हित पूर्णांक t1समयr;
	अचिन्हित पूर्णांक t2;
	अचिन्हित पूर्णांक t2समयr;
	अचिन्हित पूर्णांक n2;
	अचिन्हित पूर्णांक n2count;
	अचिन्हित पूर्णांक winकरोw;
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक mode;
पूर्ण;

बाह्य पूर्णांक lapb_रेजिस्टर(काष्ठा net_device *dev,
			 स्थिर काष्ठा lapb_रेजिस्टर_काष्ठा *callbacks);
बाह्य पूर्णांक lapb_unरेजिस्टर(काष्ठा net_device *dev);
बाह्य पूर्णांक lapb_getparms(काष्ठा net_device *dev, काष्ठा lapb_parms_काष्ठा *parms);
बाह्य पूर्णांक lapb_setparms(काष्ठा net_device *dev, काष्ठा lapb_parms_काष्ठा *parms);
बाह्य पूर्णांक lapb_connect_request(काष्ठा net_device *dev);
बाह्य पूर्णांक lapb_disconnect_request(काष्ठा net_device *dev);
बाह्य पूर्णांक lapb_data_request(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
बाह्य पूर्णांक lapb_data_received(काष्ठा net_device *dev, काष्ठा sk_buff *skb);

#पूर्ण_अगर
