<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2005 Marc Kleine-Budde, Pengutronix
 * Copyright (C) 2006 Andrey Volkov, Varma Electronics
 * Copyright (C) 2008-2009 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

#समावेश <linux/can/dev.h>

/* Local echo of CAN messages
 *
 * CAN network devices *should* support a local echo functionality
 * (see Documentation/networking/can.rst). To test the handling of CAN
 * पूर्णांकerfaces that करो not support the local echo both driver types are
 * implemented. In the हाल that the driver करोes not support the echo
 * the IFF_ECHO reमुख्यs clear in dev->flags. This causes the PF_CAN core
 * to perक्रमm the echo as a fallback solution.
 */
व्योम can_flush_echo_skb(काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	पूर्णांक i;

	क्रम (i = 0; i < priv->echo_skb_max; i++) अणु
		अगर (priv->echo_skb[i]) अणु
			kमुक्त_skb(priv->echo_skb[i]);
			priv->echo_skb[i] = शून्य;
			stats->tx_dropped++;
			stats->tx_पातed_errors++;
		पूर्ण
	पूर्ण
पूर्ण

/* Put the skb on the stack to be looped backed locally lateron
 *
 * The function is typically called in the start_xmit function
 * of the device driver. The driver must protect access to
 * priv->echo_skb, अगर necessary.
 */
पूर्णांक can_put_echo_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक frame_len)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	BUG_ON(idx >= priv->echo_skb_max);

	/* check flag whether this packet has to be looped back */
	अगर (!(dev->flags & IFF_ECHO) ||
	    (skb->protocol != htons(ETH_P_CAN) &&
	     skb->protocol != htons(ETH_P_CANFD))) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (!priv->echo_skb[idx]) अणु
		skb = can_create_echo_skb(skb);
		अगर (!skb)
			वापस -ENOMEM;

		/* make settings क्रम echo to reduce code in irq context */
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb->dev = dev;

		/* save frame_len to reuse it when transmission is completed */
		can_skb_prv(skb)->frame_len = frame_len;

		skb_tx_बारtamp(skb);

		/* save this skb क्रम tx पूर्णांकerrupt echo handling */
		priv->echo_skb[idx] = skb;
	पूर्ण अन्यथा अणु
		/* locking problem with netअगर_stop_queue() ?? */
		netdev_err(dev, "%s: BUG! echo_skb %d is occupied!\n", __func__, idx);
		kमुक्त_skb(skb);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(can_put_echo_skb);

काष्ठा sk_buff *
__can_get_echo_skb(काष्ठा net_device *dev, अचिन्हित पूर्णांक idx, u8 *len_ptr,
		   अचिन्हित पूर्णांक *frame_len_ptr)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	अगर (idx >= priv->echo_skb_max) अणु
		netdev_err(dev, "%s: BUG! Trying to access can_priv::echo_skb out of bounds (%u/max %u)\n",
			   __func__, idx, priv->echo_skb_max);
		वापस शून्य;
	पूर्ण

	अगर (priv->echo_skb[idx]) अणु
		/* Using "struct canfd_frame::len" क्रम the frame
		 * length is supported on both CAN and CANFD frames.
		 */
		काष्ठा sk_buff *skb = priv->echo_skb[idx];
		काष्ठा can_skb_priv *can_skb_priv = can_skb_prv(skb);
		काष्ठा canfd_frame *cf = (काष्ठा canfd_frame *)skb->data;

		/* get the real payload length क्रम netdev statistics */
		अगर (cf->can_id & CAN_RTR_FLAG)
			*len_ptr = 0;
		अन्यथा
			*len_ptr = cf->len;

		अगर (frame_len_ptr)
			*frame_len_ptr = can_skb_priv->frame_len;

		priv->echo_skb[idx] = शून्य;

		अगर (skb->pkt_type == PACKET_LOOPBACK) अणु
			skb->pkt_type = PACKET_BROADCAST;
		पूर्ण अन्यथा अणु
			dev_consume_skb_any(skb);
			वापस शून्य;
		पूर्ण

		वापस skb;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Get the skb from the stack and loop it back locally
 *
 * The function is typically called when the TX करोne पूर्णांकerrupt
 * is handled in the device driver. The driver must protect
 * access to priv->echo_skb, अगर necessary.
 */
अचिन्हित पूर्णांक can_get_echo_skb(काष्ठा net_device *dev, अचिन्हित पूर्णांक idx,
			      अचिन्हित पूर्णांक *frame_len_ptr)
अणु
	काष्ठा sk_buff *skb;
	u8 len;

	skb = __can_get_echo_skb(dev, idx, &len, frame_len_ptr);
	अगर (!skb)
		वापस 0;

	skb_get(skb);
	अगर (netअगर_rx(skb) == NET_RX_SUCCESS)
		dev_consume_skb_any(skb);
	अन्यथा
		dev_kमुक्त_skb_any(skb);

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(can_get_echo_skb);

/* Remove the skb from the stack and मुक्त it.
 *
 * The function is typically called when TX failed.
 */
व्योम can_मुक्त_echo_skb(काष्ठा net_device *dev, अचिन्हित पूर्णांक idx,
		       अचिन्हित पूर्णांक *frame_len_ptr)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	अगर (idx >= priv->echo_skb_max) अणु
		netdev_err(dev, "%s: BUG! Trying to access can_priv::echo_skb out of bounds (%u/max %u)\n",
			   __func__, idx, priv->echo_skb_max);
		वापस;
	पूर्ण

	अगर (priv->echo_skb[idx]) अणु
		काष्ठा sk_buff *skb = priv->echo_skb[idx];
		काष्ठा can_skb_priv *can_skb_priv = can_skb_prv(skb);

		अगर (frame_len_ptr)
			*frame_len_ptr = can_skb_priv->frame_len;

		dev_kमुक्त_skb_any(skb);
		priv->echo_skb[idx] = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(can_मुक्त_echo_skb);

काष्ठा sk_buff *alloc_can_skb(काष्ठा net_device *dev, काष्ठा can_frame **cf)
अणु
	काष्ठा sk_buff *skb;

	skb = netdev_alloc_skb(dev, माप(काष्ठा can_skb_priv) +
			       माप(काष्ठा can_frame));
	अगर (unlikely(!skb)) अणु
		*cf = शून्य;

		वापस शून्य;
	पूर्ण

	skb->protocol = htons(ETH_P_CAN);
	skb->pkt_type = PACKET_BROADCAST;
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	can_skb_reserve(skb);
	can_skb_prv(skb)->अगरindex = dev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;

	*cf = skb_put_zero(skb, माप(काष्ठा can_frame));

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_can_skb);

काष्ठा sk_buff *alloc_canfd_skb(काष्ठा net_device *dev,
				काष्ठा canfd_frame **cfd)
अणु
	काष्ठा sk_buff *skb;

	skb = netdev_alloc_skb(dev, माप(काष्ठा can_skb_priv) +
			       माप(काष्ठा canfd_frame));
	अगर (unlikely(!skb)) अणु
		*cfd = शून्य;

		वापस शून्य;
	पूर्ण

	skb->protocol = htons(ETH_P_CANFD);
	skb->pkt_type = PACKET_BROADCAST;
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	can_skb_reserve(skb);
	can_skb_prv(skb)->अगरindex = dev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;

	*cfd = skb_put_zero(skb, माप(काष्ठा canfd_frame));

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_canfd_skb);

काष्ठा sk_buff *alloc_can_err_skb(काष्ठा net_device *dev, काष्ठा can_frame **cf)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_can_skb(dev, cf);
	अगर (unlikely(!skb))
		वापस शून्य;

	(*cf)->can_id = CAN_ERR_FLAG;
	(*cf)->len = CAN_ERR_DLC;

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_can_err_skb);
