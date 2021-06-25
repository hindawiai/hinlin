<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IEEE802154_6LOWPAN_I_H__
#घोषणा __IEEE802154_6LOWPAN_I_H__

#समावेश <linux/list.h>

#समावेश <net/ieee802154_netdev.h>
#समावेश <net/inet_frag.h>
#समावेश <net/6lowpan.h>

प्रकार अचिन्हित __bitwise lowpan_rx_result;
#घोषणा RX_CONTINUE		((__क्रमce lowpan_rx_result) 0u)
#घोषणा RX_DROP_UNUSABLE	((__क्रमce lowpan_rx_result) 1u)
#घोषणा RX_DROP			((__क्रमce lowpan_rx_result) 2u)
#घोषणा RX_QUEUED		((__क्रमce lowpan_rx_result) 3u)

#घोषणा LOWPAN_DISPATCH_FRAG1           0xc0
#घोषणा LOWPAN_DISPATCH_FRAGN           0xe0

काष्ठा frag_lowpan_compare_key अणु
	u16 tag;
	u16 d_size;
	काष्ठा ieee802154_addr src;
	काष्ठा ieee802154_addr dst;
पूर्ण;

/* Equivalent of ipv4 काष्ठा ipq
 */
काष्ठा lowpan_frag_queue अणु
	काष्ठा inet_frag_queue	q;
पूर्ण;

पूर्णांक lowpan_frag_rcv(काष्ठा sk_buff *skb, स्थिर u8 frag_type);
व्योम lowpan_net_frag_निकास(व्योम);
पूर्णांक lowpan_net_frag_init(व्योम);

व्योम lowpan_rx_init(व्योम);
व्योम lowpan_rx_निकास(व्योम);

पूर्णांक lowpan_header_create(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			 अचिन्हित लघु type, स्थिर व्योम *_daddr,
			 स्थिर व्योम *_saddr, अचिन्हित पूर्णांक len);
netdev_tx_t lowpan_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

पूर्णांक lowpan_iphc_decompress(काष्ठा sk_buff *skb);
lowpan_rx_result lowpan_rx_h_ipv6(काष्ठा sk_buff *skb);

#पूर्ण_अगर /* __IEEE802154_6LOWPAN_I_H__ */
