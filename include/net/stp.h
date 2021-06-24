<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_STP_H
#घोषणा _NET_STP_H

काष्ठा stp_proto अणु
	अचिन्हित अक्षर	group_address[ETH_ALEN];
	व्योम		(*rcv)(स्थिर काष्ठा stp_proto *, काष्ठा sk_buff *,
			       काष्ठा net_device *);
	व्योम		*data;
पूर्ण;

पूर्णांक stp_proto_रेजिस्टर(स्थिर काष्ठा stp_proto *proto);
व्योम stp_proto_unरेजिस्टर(स्थिर काष्ठा stp_proto *proto);

#पूर्ण_अगर /* _NET_STP_H */
