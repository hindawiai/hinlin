<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_P8022_H
#घोषणा _NET_P8022_H
काष्ठा datalink_proto *
रेजिस्टर_8022_client(अचिन्हित अक्षर type,
		     पूर्णांक (*func)(काष्ठा sk_buff *skb,
				 काष्ठा net_device *dev,
				 काष्ठा packet_type *pt,
				 काष्ठा net_device *orig_dev));
व्योम unरेजिस्टर_8022_client(काष्ठा datalink_proto *proto);

काष्ठा datalink_proto *make_8023_client(व्योम);
व्योम destroy_8023_client(काष्ठा datalink_proto *dl);
#पूर्ण_अगर
