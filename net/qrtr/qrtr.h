<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __QRTR_H_
#घोषणा __QRTR_H_

#समावेश <linux/types.h>

काष्ठा sk_buff;

/* endpoपूर्णांक node id स्वतः assignment */
#घोषणा QRTR_EP_NID_AUTO (-1)

/**
 * काष्ठा qrtr_endpoपूर्णांक - endpoपूर्णांक handle
 * @xmit: Callback क्रम outgoing packets
 *
 * The socket buffer passed to the xmit function becomes owned by the endpoपूर्णांक
 * driver.  As such, when the driver is करोne with the buffer, it should
 * call kमुक्त_skb() on failure, or consume_skb() on success.
 */
काष्ठा qrtr_endpoपूर्णांक अणु
	पूर्णांक (*xmit)(काष्ठा qrtr_endpoपूर्णांक *ep, काष्ठा sk_buff *skb);
	/* निजी: not क्रम endpoपूर्णांक use */
	काष्ठा qrtr_node *node;
पूर्ण;

पूर्णांक qrtr_endpoपूर्णांक_रेजिस्टर(काष्ठा qrtr_endpoपूर्णांक *ep, अचिन्हित पूर्णांक nid);

व्योम qrtr_endpoपूर्णांक_unरेजिस्टर(काष्ठा qrtr_endpoपूर्णांक *ep);

पूर्णांक qrtr_endpoपूर्णांक_post(काष्ठा qrtr_endpoपूर्णांक *ep, स्थिर व्योम *data, माप_प्रकार len);

पूर्णांक qrtr_ns_init(व्योम);

व्योम qrtr_ns_हटाओ(व्योम);

#पूर्ण_अगर
