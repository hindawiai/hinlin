<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * linux/can/skb.h
 *
 * Definitions क्रम the CAN network socket buffer
 *
 * Copyright (C) 2012 Oliver Hartkopp <socketcan@hartkopp.net>
 *
 */

#अगर_अघोषित _CAN_SKB_H
#घोषणा _CAN_SKB_H

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/can.h>
#समावेश <net/sock.h>

व्योम can_flush_echo_skb(काष्ठा net_device *dev);
पूर्णांक can_put_echo_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक frame_len);
काष्ठा sk_buff *__can_get_echo_skb(काष्ठा net_device *dev, अचिन्हित पूर्णांक idx,
				   u8 *len_ptr, अचिन्हित पूर्णांक *frame_len_ptr);
अचिन्हित पूर्णांक can_get_echo_skb(काष्ठा net_device *dev, अचिन्हित पूर्णांक idx,
			      अचिन्हित पूर्णांक *frame_len_ptr);
व्योम can_मुक्त_echo_skb(काष्ठा net_device *dev, अचिन्हित पूर्णांक idx,
		       अचिन्हित पूर्णांक *frame_len_ptr);
काष्ठा sk_buff *alloc_can_skb(काष्ठा net_device *dev, काष्ठा can_frame **cf);
काष्ठा sk_buff *alloc_canfd_skb(काष्ठा net_device *dev,
				काष्ठा canfd_frame **cfd);
काष्ठा sk_buff *alloc_can_err_skb(काष्ठा net_device *dev,
				  काष्ठा can_frame **cf);

/*
 * The काष्ठा can_skb_priv is used to transport additional inक्रमmation aदीर्घ
 * with the stored काष्ठा can(fd)_frame that can not be contained in existing
 * काष्ठा sk_buff elements.
 * N.B. that this inक्रमmation must not be modअगरied in cloned CAN sk_buffs.
 * To modअगरy the CAN frame content or the काष्ठा can_skb_priv content
 * skb_copy() needs to be used instead of skb_clone().
 */

/**
 * काष्ठा can_skb_priv - निजी additional data inside CAN sk_buffs
 * @अगरindex:	अगरindex of the first पूर्णांकerface the CAN frame appeared on
 * @skbcnt:	atomic counter to have an unique id together with skb poपूर्णांकer
 * @frame_len:	length of CAN frame in data link layer
 * @cf:		align to the following CAN frame at skb->data
 */
काष्ठा can_skb_priv अणु
	पूर्णांक अगरindex;
	पूर्णांक skbcnt;
	अचिन्हित पूर्णांक frame_len;
	काष्ठा can_frame cf[];
पूर्ण;

अटल अंतरभूत काष्ठा can_skb_priv *can_skb_prv(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा can_skb_priv *)(skb->head);
पूर्ण

अटल अंतरभूत व्योम can_skb_reserve(काष्ठा sk_buff *skb)
अणु
	skb_reserve(skb, माप(काष्ठा can_skb_priv));
पूर्ण

अटल अंतरभूत व्योम can_skb_set_owner(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	/* If the socket has alपढ़ोy been बंदd by user space, the
	 * refcount may alपढ़ोy be 0 (and the socket will be मुक्तd
	 * after the last TX skb has been मुक्तd). So only increase
	 * socket refcount अगर the refcount is > 0.
	 */
	अगर (sk && refcount_inc_not_zero(&sk->sk_refcnt)) अणु
		skb->deकाष्ठाor = sock_eमुक्त;
		skb->sk = sk;
	पूर्ण
पूर्ण

/*
 * वापसs an unshared skb owned by the original sock to be echo'ed back
 */
अटल अंतरभूत काष्ठा sk_buff *can_create_echo_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *nskb;

	nskb = skb_clone(skb, GFP_ATOMIC);
	अगर (unlikely(!nskb)) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	can_skb_set_owner(nskb, skb->sk);
	consume_skb(skb);
	वापस nskb;
पूर्ण

/* Check क्रम outgoing skbs that have not been created by the CAN subप्रणाली */
अटल अंतरभूत bool can_skb_headroom_valid(काष्ठा net_device *dev,
					  काष्ठा sk_buff *skb)
अणु
	/* af_packet creates a headroom of HH_DATA_MOD bytes which is fine */
	अगर (WARN_ON_ONCE(skb_headroom(skb) < माप(काष्ठा can_skb_priv)))
		वापस false;

	/* af_packet करोes not apply CAN skb specअगरic settings */
	अगर (skb->ip_summed == CHECKSUM_NONE) अणु
		/* init headroom */
		can_skb_prv(skb)->अगरindex = dev->अगरindex;
		can_skb_prv(skb)->skbcnt = 0;

		skb->ip_summed = CHECKSUM_UNNECESSARY;

		/* perक्रमm proper loopback on capable devices */
		अगर (dev->flags & IFF_ECHO)
			skb->pkt_type = PACKET_LOOPBACK;
		अन्यथा
			skb->pkt_type = PACKET_HOST;

		skb_reset_mac_header(skb);
		skb_reset_network_header(skb);
		skb_reset_transport_header(skb);
	पूर्ण

	वापस true;
पूर्ण

/* Drop a given socketbuffer अगर it करोes not contain a valid CAN frame. */
अटल अंतरभूत bool can_dropped_invalid_skb(काष्ठा net_device *dev,
					  काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;

	अगर (skb->protocol == htons(ETH_P_CAN)) अणु
		अगर (unlikely(skb->len != CAN_MTU ||
			     cfd->len > CAN_MAX_DLEN))
			जाओ inval_skb;
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_CANFD)) अणु
		अगर (unlikely(skb->len != CANFD_MTU ||
			     cfd->len > CANFD_MAX_DLEN))
			जाओ inval_skb;
	पूर्ण अन्यथा
		जाओ inval_skb;

	अगर (!can_skb_headroom_valid(dev, skb))
		जाओ inval_skb;

	वापस false;

inval_skb:
	kमुक्त_skb(skb);
	dev->stats.tx_dropped++;
	वापस true;
पूर्ण

अटल अंतरभूत bool can_is_canfd_skb(स्थिर काष्ठा sk_buff *skb)
अणु
	/* the CAN specअगरic type of skb is identअगरied by its data length */
	वापस skb->len == CANFD_MTU;
पूर्ण

#पूर्ण_अगर /* !_CAN_SKB_H */
