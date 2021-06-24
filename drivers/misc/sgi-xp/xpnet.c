<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (C) 1999-2009 Silicon Graphics, Inc. All rights reserved.
 */

/*
 * Cross Partition Network Interface (XPNET) support
 *
 *	XPNET provides a भव network layered on top of the Cross
 *	Partition communication layer.
 *
 *	XPNET provides direct poपूर्णांक-to-poपूर्णांक and broadcast-like support
 *	क्रम an ethernet-like device.  The ethernet broadcast medium is
 *	replaced with a poपूर्णांक-to-poपूर्णांक message काष्ठाure which passes
 *	poपूर्णांकers to a DMA-capable block that a remote partition should
 *	retrieve and pass to the upper level networking layer.
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश "xp.h"

/*
 * The message payload transferred by XPC.
 *
 * buf_pa is the physical address where the DMA should pull from.
 *
 * NOTE: क्रम perक्रमmance reasons, buf_pa should _ALWAYS_ begin on a
 * cacheline boundary.  To accomplish this, we record the number of
 * bytes from the beginning of the first cacheline to the first useful
 * byte of the skb (leadin_ignore) and the number of bytes from the
 * last useful byte of the skb to the end of the last cacheline
 * (tailout_ignore).
 *
 * size is the number of bytes to transfer which includes the skb->len
 * (useful bytes of the senders skb) plus the leadin and tailout
 */
काष्ठा xpnet_message अणु
	u16 version;		/* Version क्रम this message */
	u16 embedded_bytes;	/* #of bytes embedded in XPC message */
	u32 magic;		/* Special number indicating this is xpnet */
	अचिन्हित दीर्घ buf_pa;	/* phys address of buffer to retrieve */
	u32 size;		/* #of bytes in buffer */
	u8 leadin_ignore;	/* #of bytes to ignore at the beginning */
	u8 tailout_ignore;	/* #of bytes to ignore at the end */
	अचिन्हित अक्षर data;	/* body of small packets */
पूर्ण;

/*
 * Determine the size of our message, the cacheline aligned size,
 * and then the number of message will request from XPC.
 *
 * XPC expects each message to exist in an inभागidual cacheline.
 */
#घोषणा XPNET_MSG_SIZE		XPC_MSG_PAYLOAD_MAX_SIZE
#घोषणा XPNET_MSG_DATA_MAX	\
		(XPNET_MSG_SIZE - दुरत्व(काष्ठा xpnet_message, data))
#घोषणा XPNET_MSG_NENTRIES	(PAGE_SIZE / XPC_MSG_MAX_SIZE)

#घोषणा XPNET_MAX_KTHREADS	(XPNET_MSG_NENTRIES + 1)
#घोषणा XPNET_MAX_IDLE_KTHREADS	(XPNET_MSG_NENTRIES + 1)

/*
 * Version number of XPNET implementation. XPNET can always talk to versions
 * with same major #, and never talk to versions with a dअगरferent version.
 */
#घोषणा _XPNET_VERSION(_major, _minor)	(((_major) << 4) | (_minor))
#घोषणा XPNET_VERSION_MAJOR(_v)		((_v) >> 4)
#घोषणा XPNET_VERSION_MINOR(_v)		((_v) & 0xf)

#घोषणा	XPNET_VERSION _XPNET_VERSION(1, 0)	/* version 1.0 */
#घोषणा	XPNET_VERSION_EMBED _XPNET_VERSION(1, 1)	/* version 1.1 */
#घोषणा XPNET_MAGIC	0x88786984	/* "XNET" */

#घोषणा XPNET_VALID_MSG(_m)						     \
   ((XPNET_VERSION_MAJOR(_m->version) == XPNET_VERSION_MAJOR(XPNET_VERSION)) \
    && (msg->magic == XPNET_MAGIC))

#घोषणा XPNET_DEVICE_NAME		"xp0"

/*
 * When messages are queued with xpc_send_notअगरy, a kदो_स्मृति'd buffer
 * of the following type is passed as a notअगरication cookie.  When the
 * notअगरication function is called, we use the cookie to decide
 * whether all outstanding message sends have completed.  The skb can
 * then be released.
 */
काष्ठा xpnet_pending_msg अणु
	काष्ठा sk_buff *skb;
	atomic_t use_count;
पूर्ण;

अटल काष्ठा net_device *xpnet_device;

/*
 * When we are notअगरied of other partitions activating, we add them to
 * our biपंचांगask of partitions to which we broadcast.
 */
अटल अचिन्हित दीर्घ *xpnet_broadcast_partitions;
/* protect above */
अटल DEFINE_SPINLOCK(xpnet_broadcast_lock);

/*
 * Since the Block Transfer Engine (BTE) is being used क्रम the transfer
 * and it relies upon cache-line size transfers, we need to reserve at
 * least one cache-line क्रम head and tail alignment.  The BTE is
 * limited to 8MB transfers.
 *
 * Testing has shown that changing MTU to greater than 64KB has no effect
 * on TCP as the two sides negotiate a Max Segment Size that is limited
 * to 64K.  Other protocols May use packets greater than this, but क्रम
 * now, the शेष is 64KB.
 */
#घोषणा XPNET_MAX_MTU (0x800000UL - L1_CACHE_BYTES)
/* 68 comes from min TCP+IP+MAC header */
#घोषणा XPNET_MIN_MTU 68
/* 32KB has been determined to be the ideal */
#घोषणा XPNET_DEF_MTU (0x8000UL)

/*
 * The partid is encapsulated in the MAC address beginning in the following
 * octet and it consists of two octets.
 */
#घोषणा XPNET_PARTID_OCTET	2

/* Define the XPNET debug device काष्ठाures to be used with dev_dbg() et al */

अटल काष्ठा device_driver xpnet_dbg_name = अणु
	.name = "xpnet"
पूर्ण;

अटल काष्ठा device xpnet_dbg_subname = अणु
	.init_name = "",	/* set to "" */
	.driver = &xpnet_dbg_name
पूर्ण;

अटल काष्ठा device *xpnet = &xpnet_dbg_subname;

/*
 * Packet was recevied by XPC and क्रमwarded to us.
 */
अटल व्योम
xpnet_receive(लघु partid, पूर्णांक channel, काष्ठा xpnet_message *msg)
अणु
	काष्ठा sk_buff *skb;
	व्योम *dst;
	क्रमागत xp_retval ret;

	अगर (!XPNET_VALID_MSG(msg)) अणु
		/*
		 * Packet with a dअगरferent XPC version.  Ignore.
		 */
		xpc_received(partid, channel, (व्योम *)msg);

		xpnet_device->stats.rx_errors++;

		वापस;
	पूर्ण
	dev_dbg(xpnet, "received 0x%lx, %d, %d, %d\n", msg->buf_pa, msg->size,
		msg->leadin_ignore, msg->tailout_ignore);

	/* reserve an extra cache line */
	skb = dev_alloc_skb(msg->size + L1_CACHE_BYTES);
	अगर (!skb) अणु
		dev_err(xpnet, "failed on dev_alloc_skb(%d)\n",
			msg->size + L1_CACHE_BYTES);

		xpc_received(partid, channel, (व्योम *)msg);

		xpnet_device->stats.rx_errors++;

		वापस;
	पूर्ण

	/*
	 * The allocated skb has some reserved space.
	 * In order to use xp_remote_स_नकल(), we need to get the
	 * skb->data poपूर्णांकer moved क्रमward.
	 */
	skb_reserve(skb, (L1_CACHE_BYTES - ((u64)skb->data &
					    (L1_CACHE_BYTES - 1)) +
			  msg->leadin_ignore));

	/*
	 * Update the tail poपूर्णांकer to indicate data actually
	 * transferred.
	 */
	skb_put(skb, (msg->size - msg->leadin_ignore - msg->tailout_ignore));

	/*
	 * Move the data over from the other side.
	 */
	अगर ((XPNET_VERSION_MINOR(msg->version) == 1) &&
	    (msg->embedded_bytes != 0)) अणु
		dev_dbg(xpnet, "copying embedded message. memcpy(0x%p, 0x%p, "
			"%lu)\n", skb->data, &msg->data,
			(माप_प्रकार)msg->embedded_bytes);

		skb_copy_to_linear_data(skb, &msg->data,
					(माप_प्रकार)msg->embedded_bytes);
	पूर्ण अन्यथा अणु
		dst = (व्योम *)((u64)skb->data & ~(L1_CACHE_BYTES - 1));
		dev_dbg(xpnet, "transferring buffer to the skb->data area;\n\t"
			"xp_remote_memcpy(0x%p, 0x%p, %u)\n", dst,
					  (व्योम *)msg->buf_pa, msg->size);

		ret = xp_remote_स_नकल(xp_pa(dst), msg->buf_pa, msg->size);
		अगर (ret != xpSuccess) अणु
			/*
			 * !!! Need better way of cleaning skb.  Currently skb
			 * !!! appears in_use and we can't just call
			 * !!! dev_kमुक्त_skb.
			 */
			dev_err(xpnet, "xp_remote_memcpy(0x%p, 0x%p, 0x%x) "
				"returned error=0x%x\n", dst,
				(व्योम *)msg->buf_pa, msg->size, ret);

			xpc_received(partid, channel, (व्योम *)msg);

			xpnet_device->stats.rx_errors++;

			वापस;
		पूर्ण
	पूर्ण

	dev_dbg(xpnet, "<skb->head=0x%p skb->data=0x%p skb->tail=0x%p "
		"skb->end=0x%p skb->len=%d\n", (व्योम *)skb->head,
		(व्योम *)skb->data, skb_tail_poपूर्णांकer(skb), skb_end_poपूर्णांकer(skb),
		skb->len);

	skb->protocol = eth_type_trans(skb, xpnet_device);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	dev_dbg(xpnet, "passing skb to network layer\n"
		"\tskb->head=0x%p skb->data=0x%p skb->tail=0x%p "
		"skb->end=0x%p skb->len=%d\n",
		(व्योम *)skb->head, (व्योम *)skb->data, skb_tail_poपूर्णांकer(skb),
		skb_end_poपूर्णांकer(skb), skb->len);

	xpnet_device->stats.rx_packets++;
	xpnet_device->stats.rx_bytes += skb->len + ETH_HLEN;

	netअगर_rx_ni(skb);
	xpc_received(partid, channel, (व्योम *)msg);
पूर्ण

/*
 * This is the handler which XPC calls during any sort of change in
 * state or message reception on a connection.
 */
अटल व्योम
xpnet_connection_activity(क्रमागत xp_retval reason, लघु partid, पूर्णांक channel,
			  व्योम *data, व्योम *key)
अणु
	DBUG_ON(partid < 0 || partid >= xp_max_npartitions);
	DBUG_ON(channel != XPC_NET_CHANNEL);

	चयन (reason) अणु
	हाल xpMsgReceived:	/* message received */
		DBUG_ON(data == शून्य);

		xpnet_receive(partid, channel, (काष्ठा xpnet_message *)data);
		अवरोध;

	हाल xpConnected:	/* connection completed to a partition */
		spin_lock_bh(&xpnet_broadcast_lock);
		__set_bit(partid, xpnet_broadcast_partitions);
		spin_unlock_bh(&xpnet_broadcast_lock);

		netअगर_carrier_on(xpnet_device);

		dev_dbg(xpnet, "%s connected to partition %d\n",
			xpnet_device->name, partid);
		अवरोध;

	शेष:
		spin_lock_bh(&xpnet_broadcast_lock);
		__clear_bit(partid, xpnet_broadcast_partitions);
		spin_unlock_bh(&xpnet_broadcast_lock);

		अगर (biपंचांगap_empty((अचिन्हित दीर्घ *)xpnet_broadcast_partitions,
				 xp_max_npartitions)) अणु
			netअगर_carrier_off(xpnet_device);
		पूर्ण

		dev_dbg(xpnet, "%s disconnected from partition %d\n",
			xpnet_device->name, partid);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
xpnet_dev_खोलो(काष्ठा net_device *dev)
अणु
	क्रमागत xp_retval ret;

	dev_dbg(xpnet, "calling xpc_connect(%d, 0x%p, NULL, %ld, %ld, %ld, "
		"%ld)\n", XPC_NET_CHANNEL, xpnet_connection_activity,
		(अचिन्हित दीर्घ)XPNET_MSG_SIZE,
		(अचिन्हित दीर्घ)XPNET_MSG_NENTRIES,
		(अचिन्हित दीर्घ)XPNET_MAX_KTHREADS,
		(अचिन्हित दीर्घ)XPNET_MAX_IDLE_KTHREADS);

	ret = xpc_connect(XPC_NET_CHANNEL, xpnet_connection_activity, शून्य,
			  XPNET_MSG_SIZE, XPNET_MSG_NENTRIES,
			  XPNET_MAX_KTHREADS, XPNET_MAX_IDLE_KTHREADS);
	अगर (ret != xpSuccess) अणु
		dev_err(xpnet, "ifconfig up of %s failed on XPC connect, "
			"ret=%d\n", dev->name, ret);

		वापस -ENOMEM;
	पूर्ण

	dev_dbg(xpnet, "ifconfig up of %s; XPC connected\n", dev->name);

	वापस 0;
पूर्ण

अटल पूर्णांक
xpnet_dev_stop(काष्ठा net_device *dev)
अणु
	xpc_disconnect(XPC_NET_CHANNEL);

	dev_dbg(xpnet, "ifconfig down of %s; XPC disconnected\n", dev->name);

	वापस 0;
पूर्ण

/*
 * Notअगरication that the other end has received the message and
 * DMA'd the skb inक्रमmation.  At this poपूर्णांक, they are करोne with
 * our side.  When all recipients are करोne processing, we
 * release the skb and then release our pending message काष्ठाure.
 */
अटल व्योम
xpnet_send_completed(क्रमागत xp_retval reason, लघु partid, पूर्णांक channel,
		     व्योम *__qm)
अणु
	काष्ठा xpnet_pending_msg *queued_msg = (काष्ठा xpnet_pending_msg *)__qm;

	DBUG_ON(queued_msg == शून्य);

	dev_dbg(xpnet, "message to %d notified with reason %d\n",
		partid, reason);

	अगर (atomic_dec_वापस(&queued_msg->use_count) == 0) अणु
		dev_dbg(xpnet, "all acks for skb->head=-x%p\n",
			(व्योम *)queued_msg->skb->head);

		dev_kमुक्त_skb_any(queued_msg->skb);
		kमुक्त(queued_msg);
	पूर्ण
पूर्ण

अटल व्योम
xpnet_send(काष्ठा sk_buff *skb, काष्ठा xpnet_pending_msg *queued_msg,
	   u64 start_addr, u64 end_addr, u16 embedded_bytes, पूर्णांक dest_partid)
अणु
	u8 msg_buffer[XPNET_MSG_SIZE];
	काष्ठा xpnet_message *msg = (काष्ठा xpnet_message *)&msg_buffer;
	u16 msg_size = माप(काष्ठा xpnet_message);
	क्रमागत xp_retval ret;

	msg->embedded_bytes = embedded_bytes;
	अगर (unlikely(embedded_bytes != 0)) अणु
		msg->version = XPNET_VERSION_EMBED;
		dev_dbg(xpnet, "calling memcpy(0x%p, 0x%p, 0x%lx)\n",
			&msg->data, skb->data, (माप_प्रकार)embedded_bytes);
		skb_copy_from_linear_data(skb, &msg->data,
					  (माप_प्रकार)embedded_bytes);
		msg_size += embedded_bytes - 1;
	पूर्ण अन्यथा अणु
		msg->version = XPNET_VERSION;
	पूर्ण
	msg->magic = XPNET_MAGIC;
	msg->size = end_addr - start_addr;
	msg->leadin_ignore = (u64)skb->data - start_addr;
	msg->tailout_ignore = end_addr - (u64)skb_tail_poपूर्णांकer(skb);
	msg->buf_pa = xp_pa((व्योम *)start_addr);

	dev_dbg(xpnet, "sending XPC message to %d:%d\n"
		"msg->buf_pa=0x%lx, msg->size=%u, "
		"msg->leadin_ignore=%u, msg->tailout_ignore=%u\n",
		dest_partid, XPC_NET_CHANNEL, msg->buf_pa, msg->size,
		msg->leadin_ignore, msg->tailout_ignore);

	atomic_inc(&queued_msg->use_count);

	ret = xpc_send_notअगरy(dest_partid, XPC_NET_CHANNEL, XPC_NOWAIT, msg,
			      msg_size, xpnet_send_completed, queued_msg);
	अगर (unlikely(ret != xpSuccess))
		atomic_dec(&queued_msg->use_count);
पूर्ण

/*
 * Network layer has क्रमmatted a packet (skb) and is पढ़ोy to place it
 * "on the wire".  Prepare and send an xpnet_message to all partitions
 * which have connected with us and are tarमाला_लो of this packet.
 *
 * MAC-NOTE:  For the XPNET driver, the MAC address contains the
 * destination partid.  If the destination partid octets are 0xffff,
 * this packet is to be broadcast to all connected partitions.
 */
अटल netdev_tx_t
xpnet_dev_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा xpnet_pending_msg *queued_msg;
	u64 start_addr, end_addr;
	लघु dest_partid;
	u16 embedded_bytes = 0;

	dev_dbg(xpnet, ">skb->head=0x%p skb->data=0x%p skb->tail=0x%p "
		"skb->end=0x%p skb->len=%d\n", (व्योम *)skb->head,
		(व्योम *)skb->data, skb_tail_poपूर्णांकer(skb), skb_end_poपूर्णांकer(skb),
		skb->len);

	अगर (skb->data[0] == 0x33) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;	/* nothing needed to be करोne */
	पूर्ण

	/*
	 * The xpnet_pending_msg tracks how many outstanding
	 * xpc_send_notअगरies are relying on this skb.  When none
	 * reमुख्य, release the skb.
	 */
	queued_msg = kदो_स्मृति(माप(काष्ठा xpnet_pending_msg), GFP_ATOMIC);
	अगर (queued_msg == शून्य) अणु
		dev_warn(xpnet, "failed to kmalloc %ld bytes; dropping "
			 "packet\n", माप(काष्ठा xpnet_pending_msg));

		dev->stats.tx_errors++;
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* get the beginning of the first cacheline and end of last */
	start_addr = ((u64)skb->data & ~(L1_CACHE_BYTES - 1));
	end_addr = L1_CACHE_ALIGN((u64)skb_tail_poपूर्णांकer(skb));

	/* calculate how many bytes to embed in the XPC message */
	अगर (unlikely(skb->len <= XPNET_MSG_DATA_MAX)) अणु
		/* skb->data करोes fit so embed */
		embedded_bytes = skb->len;
	पूर्ण

	/*
	 * Since the send occurs asynchronously, we set the count to one
	 * and begin sending.  Any sends that happen to complete beक्रमe
	 * we are करोne sending will not मुक्त the skb.  We will be left
	 * with that task during निकास.  This also handles the हाल of
	 * a packet destined क्रम a partition which is no दीर्घer up.
	 */
	atomic_set(&queued_msg->use_count, 1);
	queued_msg->skb = skb;

	अगर (skb->data[0] == 0xff) अणु
		/* we are being asked to broadcast to all partitions */
		क्रम_each_set_bit(dest_partid, xpnet_broadcast_partitions,
			     xp_max_npartitions) अणु

			xpnet_send(skb, queued_msg, start_addr, end_addr,
				   embedded_bytes, dest_partid);
		पूर्ण
	पूर्ण अन्यथा अणु
		dest_partid = (लघु)skb->data[XPNET_PARTID_OCTET + 1];
		dest_partid |= (लघु)skb->data[XPNET_PARTID_OCTET + 0] << 8;

		अगर (dest_partid >= 0 &&
		    dest_partid < xp_max_npartitions &&
		    test_bit(dest_partid, xpnet_broadcast_partitions) != 0) अणु

			xpnet_send(skb, queued_msg, start_addr, end_addr,
				   embedded_bytes, dest_partid);
		पूर्ण
	पूर्ण

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	अगर (atomic_dec_वापस(&queued_msg->use_count) == 0) अणु
		dev_kमुक्त_skb(skb);
		kमुक्त(queued_msg);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * Deal with transmit समयouts coming from the network layer.
 */
अटल व्योम
xpnet_dev_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	dev->stats.tx_errors++;
पूर्ण

अटल स्थिर काष्ठा net_device_ops xpnet_netdev_ops = अणु
	.nकरो_खोलो		= xpnet_dev_खोलो,
	.nकरो_stop		= xpnet_dev_stop,
	.nकरो_start_xmit		= xpnet_dev_hard_start_xmit,
	.nकरो_tx_समयout		= xpnet_dev_tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक __init
xpnet_init(व्योम)
अणु
	पूर्णांक result;

	अगर (!is_uv_प्रणाली())
		वापस -ENODEV;

	dev_info(xpnet, "registering network device %s\n", XPNET_DEVICE_NAME);

	xpnet_broadcast_partitions = kसुस्मृति(BITS_TO_LONGS(xp_max_npartitions),
					     माप(दीर्घ),
					     GFP_KERNEL);
	अगर (xpnet_broadcast_partitions == शून्य)
		वापस -ENOMEM;

	/*
	 * use ether_setup() to init the majority of our device
	 * काष्ठाure and then override the necessary pieces.
	 */
	xpnet_device = alloc_netdev(0, XPNET_DEVICE_NAME, NET_NAME_UNKNOWN,
				    ether_setup);
	अगर (xpnet_device == शून्य) अणु
		kमुक्त(xpnet_broadcast_partitions);
		वापस -ENOMEM;
	पूर्ण

	netअगर_carrier_off(xpnet_device);

	xpnet_device->netdev_ops = &xpnet_netdev_ops;
	xpnet_device->mtu = XPNET_DEF_MTU;
	xpnet_device->min_mtu = XPNET_MIN_MTU;
	xpnet_device->max_mtu = XPNET_MAX_MTU;

	/*
	 * Multicast assumes the LSB of the first octet is set क्रम multicast
	 * MAC addresses.  We chose the first octet of the MAC to be unlikely
	 * to collide with any venकरोr's officially issued MAC.
	 */
	xpnet_device->dev_addr[0] = 0x02;     /* locally administered, no OUI */

	xpnet_device->dev_addr[XPNET_PARTID_OCTET + 1] = xp_partition_id;
	xpnet_device->dev_addr[XPNET_PARTID_OCTET + 0] = (xp_partition_id >> 8);

	/*
	 * ether_setup() sets this to a multicast device.  We are
	 * really not supporting multicast at this समय.
	 */
	xpnet_device->flags &= ~IFF_MULTICAST;

	/*
	 * No need to checksum as it is a DMA transfer.  The BTE will
	 * report an error अगर the data is not retrievable and the
	 * packet will be dropped.
	 */
	xpnet_device->features = NETIF_F_HW_CSUM;

	result = रेजिस्टर_netdev(xpnet_device);
	अगर (result != 0) अणु
		मुक्त_netdev(xpnet_device);
		kमुक्त(xpnet_broadcast_partitions);
	पूर्ण

	वापस result;
पूर्ण

module_init(xpnet_init);

अटल व्योम __निकास
xpnet_निकास(व्योम)
अणु
	dev_info(xpnet, "unregistering network device %s\n",
		 xpnet_device[0].name);

	unरेजिस्टर_netdev(xpnet_device);
	मुक्त_netdev(xpnet_device);
	kमुक्त(xpnet_broadcast_partitions);
पूर्ण

module_निकास(xpnet_निकास);

MODULE_AUTHOR("Silicon Graphics, Inc.");
MODULE_DESCRIPTION("Cross Partition Network adapter (XPNET)");
MODULE_LICENSE("GPL");
