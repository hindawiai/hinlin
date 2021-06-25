<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Sony Mobile Communications Inc.
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/qrtr.h>
#समावेश <linux/termios.h>	/* For TIOCINQ/OUTQ */
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

#समावेश <net/sock.h>

#समावेश "qrtr.h"

#घोषणा QRTR_PROTO_VER_1 1
#घोषणा QRTR_PROTO_VER_2 3

/* स्वतः-bind range */
#घोषणा QRTR_MIN_EPH_SOCKET 0x4000
#घोषणा QRTR_MAX_EPH_SOCKET 0x7fff
#घोषणा QRTR_EPH_PORT_RANGE \
		XA_LIMIT(QRTR_MIN_EPH_SOCKET, QRTR_MAX_EPH_SOCKET)

/**
 * काष्ठा qrtr_hdr_v1 - (I|R)PCrouter packet header version 1
 * @version: protocol version
 * @type: packet type; one of QRTR_TYPE_*
 * @src_node_id: source node
 * @src_port_id: source port
 * @confirm_rx: boolean; whether a resume-tx packet should be send in reply
 * @size: length of packet, excluding this header
 * @dst_node_id: destination node
 * @dst_port_id: destination port
 */
काष्ठा qrtr_hdr_v1 अणु
	__le32 version;
	__le32 type;
	__le32 src_node_id;
	__le32 src_port_id;
	__le32 confirm_rx;
	__le32 size;
	__le32 dst_node_id;
	__le32 dst_port_id;
पूर्ण __packed;

/**
 * काष्ठा qrtr_hdr_v2 - (I|R)PCrouter packet header later versions
 * @version: protocol version
 * @type: packet type; one of QRTR_TYPE_*
 * @flags: biपंचांगask of QRTR_FLAGS_*
 * @optlen: length of optional header data
 * @size: length of packet, excluding this header and optlen
 * @src_node_id: source node
 * @src_port_id: source port
 * @dst_node_id: destination node
 * @dst_port_id: destination port
 */
काष्ठा qrtr_hdr_v2 अणु
	u8 version;
	u8 type;
	u8 flags;
	u8 optlen;
	__le32 size;
	__le16 src_node_id;
	__le16 src_port_id;
	__le16 dst_node_id;
	__le16 dst_port_id;
पूर्ण;

#घोषणा QRTR_FLAGS_CONFIRM_RX	BIT(0)

काष्ठा qrtr_cb अणु
	u32 src_node;
	u32 src_port;
	u32 dst_node;
	u32 dst_port;

	u8 type;
	u8 confirm_rx;
पूर्ण;

#घोषणा QRTR_HDR_MAX_SIZE max_t(माप_प्रकार, माप(काष्ठा qrtr_hdr_v1), \
					माप(काष्ठा qrtr_hdr_v2))

काष्ठा qrtr_sock अणु
	/* WARNING: sk must be the first member */
	काष्ठा sock sk;
	काष्ठा sockaddr_qrtr us;
	काष्ठा sockaddr_qrtr peer;
पूर्ण;

अटल अंतरभूत काष्ठा qrtr_sock *qrtr_sk(काष्ठा sock *sk)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा qrtr_sock, sk) != 0);
	वापस container_of(sk, काष्ठा qrtr_sock, sk);
पूर्ण

अटल अचिन्हित पूर्णांक qrtr_local_nid = 1;

/* क्रम node ids */
अटल RADIX_TREE(qrtr_nodes, GFP_ATOMIC);
अटल DEFINE_SPINLOCK(qrtr_nodes_lock);
/* broadcast list */
अटल LIST_HEAD(qrtr_all_nodes);
/* lock क्रम qrtr_all_nodes and node reference */
अटल DEFINE_MUTEX(qrtr_node_lock);

/* local port allocation management */
अटल DEFINE_XARRAY_ALLOC(qrtr_ports);

/**
 * काष्ठा qrtr_node - endpoपूर्णांक node
 * @ep_lock: lock क्रम endpoपूर्णांक management and callbacks
 * @ep: endpoपूर्णांक
 * @ref: reference count क्रम node
 * @nid: node id
 * @qrtr_tx_flow: tree of qrtr_tx_flow, keyed by node << 32 | port
 * @qrtr_tx_lock: lock क्रम qrtr_tx_flow inserts
 * @rx_queue: receive queue
 * @item: list item क्रम broadcast list
 */
काष्ठा qrtr_node अणु
	काष्ठा mutex ep_lock;
	काष्ठा qrtr_endpoपूर्णांक *ep;
	काष्ठा kref ref;
	अचिन्हित पूर्णांक nid;

	काष्ठा radix_tree_root qrtr_tx_flow;
	काष्ठा mutex qrtr_tx_lock; /* क्रम qrtr_tx_flow */

	काष्ठा sk_buff_head rx_queue;
	काष्ठा list_head item;
पूर्ण;

/**
 * काष्ठा qrtr_tx_flow - tx flow control
 * @resume_tx: रुकोers क्रम a resume tx from the remote
 * @pending: number of रुकोing senders
 * @tx_failed: indicates that a message with confirm_rx flag was lost
 */
काष्ठा qrtr_tx_flow अणु
	काष्ठा रुको_queue_head resume_tx;
	पूर्णांक pending;
	पूर्णांक tx_failed;
पूर्ण;

#घोषणा QRTR_TX_FLOW_HIGH	10
#घोषणा QRTR_TX_FLOW_LOW	5

अटल पूर्णांक qrtr_local_enqueue(काष्ठा qrtr_node *node, काष्ठा sk_buff *skb,
			      पूर्णांक type, काष्ठा sockaddr_qrtr *from,
			      काष्ठा sockaddr_qrtr *to);
अटल पूर्णांक qrtr_bcast_enqueue(काष्ठा qrtr_node *node, काष्ठा sk_buff *skb,
			      पूर्णांक type, काष्ठा sockaddr_qrtr *from,
			      काष्ठा sockaddr_qrtr *to);
अटल काष्ठा qrtr_sock *qrtr_port_lookup(पूर्णांक port);
अटल व्योम qrtr_port_put(काष्ठा qrtr_sock *ipc);

/* Release node resources and मुक्त the node.
 *
 * Do not call directly, use qrtr_node_release.  To be used with
 * kref_put_mutex.  As such, the node mutex is expected to be locked on call.
 */
अटल व्योम __qrtr_node_release(काष्ठा kref *kref)
अणु
	काष्ठा qrtr_node *node = container_of(kref, काष्ठा qrtr_node, ref);
	काष्ठा radix_tree_iter iter;
	काष्ठा qrtr_tx_flow *flow;
	अचिन्हित दीर्घ flags;
	व्योम __rcu **slot;

	spin_lock_irqsave(&qrtr_nodes_lock, flags);
	/* If the node is a bridge क्रम other nodes, there are possibly
	 * multiple entries poपूर्णांकing to our released node, delete them all.
	 */
	radix_tree_क्रम_each_slot(slot, &qrtr_nodes, &iter, 0) अणु
		अगर (*slot == node)
			radix_tree_iter_delete(&qrtr_nodes, &iter, slot);
	पूर्ण
	spin_unlock_irqrestore(&qrtr_nodes_lock, flags);

	list_del(&node->item);
	mutex_unlock(&qrtr_node_lock);

	skb_queue_purge(&node->rx_queue);

	/* Free tx flow counters */
	radix_tree_क्रम_each_slot(slot, &node->qrtr_tx_flow, &iter, 0) अणु
		flow = *slot;
		radix_tree_iter_delete(&node->qrtr_tx_flow, &iter, slot);
		kमुक्त(flow);
	पूर्ण
	kमुक्त(node);
पूर्ण

/* Increment reference to node. */
अटल काष्ठा qrtr_node *qrtr_node_acquire(काष्ठा qrtr_node *node)
अणु
	अगर (node)
		kref_get(&node->ref);
	वापस node;
पूर्ण

/* Decrement reference to node and release as necessary. */
अटल व्योम qrtr_node_release(काष्ठा qrtr_node *node)
अणु
	अगर (!node)
		वापस;
	kref_put_mutex(&node->ref, __qrtr_node_release, &qrtr_node_lock);
पूर्ण

/**
 * qrtr_tx_resume() - reset flow control counter
 * @node:	qrtr_node that the QRTR_TYPE_RESUME_TX packet arrived on
 * @skb:	resume_tx packet
 */
अटल व्योम qrtr_tx_resume(काष्ठा qrtr_node *node, काष्ठा sk_buff *skb)
अणु
	काष्ठा qrtr_ctrl_pkt *pkt = (काष्ठा qrtr_ctrl_pkt *)skb->data;
	u64 remote_node = le32_to_cpu(pkt->client.node);
	u32 remote_port = le32_to_cpu(pkt->client.port);
	काष्ठा qrtr_tx_flow *flow;
	अचिन्हित दीर्घ key;

	key = remote_node << 32 | remote_port;

	rcu_पढ़ो_lock();
	flow = radix_tree_lookup(&node->qrtr_tx_flow, key);
	rcu_पढ़ो_unlock();
	अगर (flow) अणु
		spin_lock(&flow->resume_tx.lock);
		flow->pending = 0;
		spin_unlock(&flow->resume_tx.lock);
		wake_up_पूर्णांकerruptible_all(&flow->resume_tx);
	पूर्ण

	consume_skb(skb);
पूर्ण

/**
 * qrtr_tx_रुको() - flow control क्रम outgoing packets
 * @node:	qrtr_node that the packet is to be send to
 * @dest_node:	node id of the destination
 * @dest_port:	port number of the destination
 * @type:	type of message
 *
 * The flow control scheme is based around the low and high "watermarks". When
 * the low watermark is passed the confirm_rx flag is set on the outgoing
 * message, which will trigger the remote to send a control message of the type
 * QRTR_TYPE_RESUME_TX to reset the counter. If the high watermark is hit
 * further transmision should be छोड़ोd.
 *
 * Return: 1 अगर confirm_rx should be set, 0 otherwise or त्रुटि_सं failure
 */
अटल पूर्णांक qrtr_tx_रुको(काष्ठा qrtr_node *node, पूर्णांक dest_node, पूर्णांक dest_port,
			पूर्णांक type)
अणु
	अचिन्हित दीर्घ key = (u64)dest_node << 32 | dest_port;
	काष्ठा qrtr_tx_flow *flow;
	पूर्णांक confirm_rx = 0;
	पूर्णांक ret;

	/* Never set confirm_rx on non-data packets */
	अगर (type != QRTR_TYPE_DATA)
		वापस 0;

	mutex_lock(&node->qrtr_tx_lock);
	flow = radix_tree_lookup(&node->qrtr_tx_flow, key);
	अगर (!flow) अणु
		flow = kzalloc(माप(*flow), GFP_KERNEL);
		अगर (flow) अणु
			init_रुकोqueue_head(&flow->resume_tx);
			अगर (radix_tree_insert(&node->qrtr_tx_flow, key, flow)) अणु
				kमुक्त(flow);
				flow = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&node->qrtr_tx_lock);

	/* Set confirm_rx अगर we where unable to find and allocate a flow */
	अगर (!flow)
		वापस 1;

	spin_lock_irq(&flow->resume_tx.lock);
	ret = रुको_event_पूर्णांकerruptible_locked_irq(flow->resume_tx,
						  flow->pending < QRTR_TX_FLOW_HIGH ||
						  flow->tx_failed ||
						  !node->ep);
	अगर (ret < 0) अणु
		confirm_rx = ret;
	पूर्ण अन्यथा अगर (!node->ep) अणु
		confirm_rx = -EPIPE;
	पूर्ण अन्यथा अगर (flow->tx_failed) अणु
		flow->tx_failed = 0;
		confirm_rx = 1;
	पूर्ण अन्यथा अणु
		flow->pending++;
		confirm_rx = flow->pending == QRTR_TX_FLOW_LOW;
	पूर्ण
	spin_unlock_irq(&flow->resume_tx.lock);

	वापस confirm_rx;
पूर्ण

/**
 * qrtr_tx_flow_failed() - flag that tx of confirm_rx flagged messages failed
 * @node:	qrtr_node that the packet is to be send to
 * @dest_node:	node id of the destination
 * @dest_port:	port number of the destination
 *
 * Signal that the transmission of a message with confirm_rx flag failed. The
 * flow's "pending" counter will keep incrementing towards QRTR_TX_FLOW_HIGH,
 * at which poपूर्णांक transmission would stall क्रमever रुकोing क्रम the resume TX
 * message associated with the dropped confirm_rx message.
 * Work around this by marking the flow as having a failed transmission and
 * cause the next transmission attempt to be sent with the confirm_rx.
 */
अटल व्योम qrtr_tx_flow_failed(काष्ठा qrtr_node *node, पूर्णांक dest_node,
				पूर्णांक dest_port)
अणु
	अचिन्हित दीर्घ key = (u64)dest_node << 32 | dest_port;
	काष्ठा qrtr_tx_flow *flow;

	rcu_पढ़ो_lock();
	flow = radix_tree_lookup(&node->qrtr_tx_flow, key);
	rcu_पढ़ो_unlock();
	अगर (flow) अणु
		spin_lock_irq(&flow->resume_tx.lock);
		flow->tx_failed = 1;
		spin_unlock_irq(&flow->resume_tx.lock);
	पूर्ण
पूर्ण

/* Pass an outgoing packet socket buffer to the endpoपूर्णांक driver. */
अटल पूर्णांक qrtr_node_enqueue(काष्ठा qrtr_node *node, काष्ठा sk_buff *skb,
			     पूर्णांक type, काष्ठा sockaddr_qrtr *from,
			     काष्ठा sockaddr_qrtr *to)
अणु
	काष्ठा qrtr_hdr_v1 *hdr;
	माप_प्रकार len = skb->len;
	पूर्णांक rc, confirm_rx;

	confirm_rx = qrtr_tx_रुको(node, to->sq_node, to->sq_port, type);
	अगर (confirm_rx < 0) अणु
		kमुक्त_skb(skb);
		वापस confirm_rx;
	पूर्ण

	hdr = skb_push(skb, माप(*hdr));
	hdr->version = cpu_to_le32(QRTR_PROTO_VER_1);
	hdr->type = cpu_to_le32(type);
	hdr->src_node_id = cpu_to_le32(from->sq_node);
	hdr->src_port_id = cpu_to_le32(from->sq_port);
	अगर (to->sq_port == QRTR_PORT_CTRL) अणु
		hdr->dst_node_id = cpu_to_le32(node->nid);
		hdr->dst_port_id = cpu_to_le32(QRTR_PORT_CTRL);
	पूर्ण अन्यथा अणु
		hdr->dst_node_id = cpu_to_le32(to->sq_node);
		hdr->dst_port_id = cpu_to_le32(to->sq_port);
	पूर्ण

	hdr->size = cpu_to_le32(len);
	hdr->confirm_rx = !!confirm_rx;

	rc = skb_put_padto(skb, ALIGN(len, 4) + माप(*hdr));

	अगर (!rc) अणु
		mutex_lock(&node->ep_lock);
		rc = -ENODEV;
		अगर (node->ep)
			rc = node->ep->xmit(node->ep, skb);
		अन्यथा
			kमुक्त_skb(skb);
		mutex_unlock(&node->ep_lock);
	पूर्ण
	/* Need to ensure that a subsequent message carries the otherwise lost
	 * confirm_rx flag अगर we dropped this one */
	अगर (rc && confirm_rx)
		qrtr_tx_flow_failed(node, to->sq_node, to->sq_port);

	वापस rc;
पूर्ण

/* Lookup node by id.
 *
 * callers must release with qrtr_node_release()
 */
अटल काष्ठा qrtr_node *qrtr_node_lookup(अचिन्हित पूर्णांक nid)
अणु
	काष्ठा qrtr_node *node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qrtr_nodes_lock, flags);
	node = radix_tree_lookup(&qrtr_nodes, nid);
	node = qrtr_node_acquire(node);
	spin_unlock_irqrestore(&qrtr_nodes_lock, flags);

	वापस node;
पूर्ण

/* Assign node id to node.
 *
 * This is mostly useful क्रम स्वतःmatic node id assignment, based on
 * the source id in the incoming packet.
 */
अटल व्योम qrtr_node_assign(काष्ठा qrtr_node *node, अचिन्हित पूर्णांक nid)
अणु
	अचिन्हित दीर्घ flags;

	अगर (nid == QRTR_EP_NID_AUTO)
		वापस;

	spin_lock_irqsave(&qrtr_nodes_lock, flags);
	radix_tree_insert(&qrtr_nodes, nid, node);
	अगर (node->nid == QRTR_EP_NID_AUTO)
		node->nid = nid;
	spin_unlock_irqrestore(&qrtr_nodes_lock, flags);
पूर्ण

/**
 * qrtr_endpoपूर्णांक_post() - post incoming data
 * @ep: endpoपूर्णांक handle
 * @data: data poपूर्णांकer
 * @len: size of data in bytes
 *
 * Return: 0 on success; negative error code on failure
 */
पूर्णांक qrtr_endpoपूर्णांक_post(काष्ठा qrtr_endpoपूर्णांक *ep, स्थिर व्योम *data, माप_प्रकार len)
अणु
	काष्ठा qrtr_node *node = ep->node;
	स्थिर काष्ठा qrtr_hdr_v1 *v1;
	स्थिर काष्ठा qrtr_hdr_v2 *v2;
	काष्ठा qrtr_sock *ipc;
	काष्ठा sk_buff *skb;
	काष्ठा qrtr_cb *cb;
	माप_प्रकार size;
	अचिन्हित पूर्णांक ver;
	माप_प्रकार hdrlen;

	अगर (len == 0 || len & 3)
		वापस -EINVAL;

	skb = __netdev_alloc_skb(शून्य, len, GFP_ATOMIC | __GFP_NOWARN);
	अगर (!skb)
		वापस -ENOMEM;

	cb = (काष्ठा qrtr_cb *)skb->cb;

	/* Version field in v1 is little endian, so this works क्रम both हालs */
	ver = *(u8*)data;

	चयन (ver) अणु
	हाल QRTR_PROTO_VER_1:
		अगर (len < माप(*v1))
			जाओ err;
		v1 = data;
		hdrlen = माप(*v1);

		cb->type = le32_to_cpu(v1->type);
		cb->src_node = le32_to_cpu(v1->src_node_id);
		cb->src_port = le32_to_cpu(v1->src_port_id);
		cb->confirm_rx = !!v1->confirm_rx;
		cb->dst_node = le32_to_cpu(v1->dst_node_id);
		cb->dst_port = le32_to_cpu(v1->dst_port_id);

		size = le32_to_cpu(v1->size);
		अवरोध;
	हाल QRTR_PROTO_VER_2:
		अगर (len < माप(*v2))
			जाओ err;
		v2 = data;
		hdrlen = माप(*v2) + v2->optlen;

		cb->type = v2->type;
		cb->confirm_rx = !!(v2->flags & QRTR_FLAGS_CONFIRM_RX);
		cb->src_node = le16_to_cpu(v2->src_node_id);
		cb->src_port = le16_to_cpu(v2->src_port_id);
		cb->dst_node = le16_to_cpu(v2->dst_node_id);
		cb->dst_port = le16_to_cpu(v2->dst_port_id);

		अगर (cb->src_port == (u16)QRTR_PORT_CTRL)
			cb->src_port = QRTR_PORT_CTRL;
		अगर (cb->dst_port == (u16)QRTR_PORT_CTRL)
			cb->dst_port = QRTR_PORT_CTRL;

		size = le32_to_cpu(v2->size);
		अवरोध;
	शेष:
		pr_err("qrtr: Invalid version %d\n", ver);
		जाओ err;
	पूर्ण

	अगर (len != ALIGN(size, 4) + hdrlen)
		जाओ err;

	अगर (cb->dst_port != QRTR_PORT_CTRL && cb->type != QRTR_TYPE_DATA &&
	    cb->type != QRTR_TYPE_RESUME_TX)
		जाओ err;

	skb_put_data(skb, data + hdrlen, size);

	qrtr_node_assign(node, cb->src_node);

	अगर (cb->type == QRTR_TYPE_NEW_SERVER) अणु
		/* Remote node endpoपूर्णांक can bridge other distant nodes */
		स्थिर काष्ठा qrtr_ctrl_pkt *pkt = data + hdrlen;

		qrtr_node_assign(node, le32_to_cpu(pkt->server.node));
	पूर्ण

	अगर (cb->type == QRTR_TYPE_RESUME_TX) अणु
		qrtr_tx_resume(node, skb);
	पूर्ण अन्यथा अणु
		ipc = qrtr_port_lookup(cb->dst_port);
		अगर (!ipc)
			जाओ err;

		अगर (sock_queue_rcv_skb(&ipc->sk, skb))
			जाओ err;

		qrtr_port_put(ipc);
	पूर्ण

	वापस 0;

err:
	kमुक्त_skb(skb);
	वापस -EINVAL;

पूर्ण
EXPORT_SYMBOL_GPL(qrtr_endpoपूर्णांक_post);

/**
 * qrtr_alloc_ctrl_packet() - allocate control packet skb
 * @pkt: reference to qrtr_ctrl_pkt poपूर्णांकer
 * @flags: the type of memory to allocate
 *
 * Returns newly allocated sk_buff, or शून्य on failure
 *
 * This function allocates a sk_buff large enough to carry a qrtr_ctrl_pkt and
 * on success वापसs a reference to the control packet in @pkt.
 */
अटल काष्ठा sk_buff *qrtr_alloc_ctrl_packet(काष्ठा qrtr_ctrl_pkt **pkt,
					      gfp_t flags)
अणु
	स्थिर पूर्णांक pkt_len = माप(काष्ठा qrtr_ctrl_pkt);
	काष्ठा sk_buff *skb;

	skb = alloc_skb(QRTR_HDR_MAX_SIZE + pkt_len, flags);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, QRTR_HDR_MAX_SIZE);
	*pkt = skb_put_zero(skb, pkt_len);

	वापस skb;
पूर्ण

/**
 * qrtr_endpoपूर्णांक_रेजिस्टर() - रेजिस्टर a new endpoपूर्णांक
 * @ep: endpoपूर्णांक to रेजिस्टर
 * @nid: desired node id; may be QRTR_EP_NID_AUTO क्रम स्वतः-assignment
 * Return: 0 on success; negative error code on failure
 *
 * The specअगरied endpoपूर्णांक must have the xmit function poपूर्णांकer set on call.
 */
पूर्णांक qrtr_endpoपूर्णांक_रेजिस्टर(काष्ठा qrtr_endpoपूर्णांक *ep, अचिन्हित पूर्णांक nid)
अणु
	काष्ठा qrtr_node *node;

	अगर (!ep || !ep->xmit)
		वापस -EINVAL;

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	kref_init(&node->ref);
	mutex_init(&node->ep_lock);
	skb_queue_head_init(&node->rx_queue);
	node->nid = QRTR_EP_NID_AUTO;
	node->ep = ep;

	INIT_RADIX_TREE(&node->qrtr_tx_flow, GFP_KERNEL);
	mutex_init(&node->qrtr_tx_lock);

	qrtr_node_assign(node, nid);

	mutex_lock(&qrtr_node_lock);
	list_add(&node->item, &qrtr_all_nodes);
	mutex_unlock(&qrtr_node_lock);
	ep->node = node;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qrtr_endpoपूर्णांक_रेजिस्टर);

/**
 * qrtr_endpoपूर्णांक_unरेजिस्टर - unरेजिस्टर endpoपूर्णांक
 * @ep: endpoपूर्णांक to unरेजिस्टर
 */
व्योम qrtr_endpoपूर्णांक_unरेजिस्टर(काष्ठा qrtr_endpoपूर्णांक *ep)
अणु
	काष्ठा qrtr_node *node = ep->node;
	काष्ठा sockaddr_qrtr src = अणुAF_QIPCRTR, node->nid, QRTR_PORT_CTRLपूर्ण;
	काष्ठा sockaddr_qrtr dst = अणुAF_QIPCRTR, qrtr_local_nid, QRTR_PORT_CTRLपूर्ण;
	काष्ठा radix_tree_iter iter;
	काष्ठा qrtr_ctrl_pkt *pkt;
	काष्ठा qrtr_tx_flow *flow;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	व्योम __rcu **slot;

	mutex_lock(&node->ep_lock);
	node->ep = शून्य;
	mutex_unlock(&node->ep_lock);

	/* Notअगरy the local controller about the event */
	spin_lock_irqsave(&qrtr_nodes_lock, flags);
	radix_tree_क्रम_each_slot(slot, &qrtr_nodes, &iter, 0) अणु
		अगर (*slot != node)
			जारी;
		src.sq_node = iter.index;
		skb = qrtr_alloc_ctrl_packet(&pkt, GFP_ATOMIC);
		अगर (skb) अणु
			pkt->cmd = cpu_to_le32(QRTR_TYPE_BYE);
			qrtr_local_enqueue(शून्य, skb, QRTR_TYPE_BYE, &src, &dst);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&qrtr_nodes_lock, flags);

	/* Wake up any transmitters रुकोing क्रम resume-tx from the node */
	mutex_lock(&node->qrtr_tx_lock);
	radix_tree_क्रम_each_slot(slot, &node->qrtr_tx_flow, &iter, 0) अणु
		flow = *slot;
		wake_up_पूर्णांकerruptible_all(&flow->resume_tx);
	पूर्ण
	mutex_unlock(&node->qrtr_tx_lock);

	qrtr_node_release(node);
	ep->node = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(qrtr_endpoपूर्णांक_unरेजिस्टर);

/* Lookup socket by port.
 *
 * Callers must release with qrtr_port_put()
 */
अटल काष्ठा qrtr_sock *qrtr_port_lookup(पूर्णांक port)
अणु
	काष्ठा qrtr_sock *ipc;

	अगर (port == QRTR_PORT_CTRL)
		port = 0;

	rcu_पढ़ो_lock();
	ipc = xa_load(&qrtr_ports, port);
	अगर (ipc)
		sock_hold(&ipc->sk);
	rcu_पढ़ो_unlock();

	वापस ipc;
पूर्ण

/* Release acquired socket. */
अटल व्योम qrtr_port_put(काष्ठा qrtr_sock *ipc)
अणु
	sock_put(&ipc->sk);
पूर्ण

/* Remove port assignment. */
अटल व्योम qrtr_port_हटाओ(काष्ठा qrtr_sock *ipc)
अणु
	काष्ठा qrtr_ctrl_pkt *pkt;
	काष्ठा sk_buff *skb;
	पूर्णांक port = ipc->us.sq_port;
	काष्ठा sockaddr_qrtr to;

	to.sq_family = AF_QIPCRTR;
	to.sq_node = QRTR_NODE_BCAST;
	to.sq_port = QRTR_PORT_CTRL;

	skb = qrtr_alloc_ctrl_packet(&pkt, GFP_KERNEL);
	अगर (skb) अणु
		pkt->cmd = cpu_to_le32(QRTR_TYPE_DEL_CLIENT);
		pkt->client.node = cpu_to_le32(ipc->us.sq_node);
		pkt->client.port = cpu_to_le32(ipc->us.sq_port);

		skb_set_owner_w(skb, &ipc->sk);
		qrtr_bcast_enqueue(शून्य, skb, QRTR_TYPE_DEL_CLIENT, &ipc->us,
				   &to);
	पूर्ण

	अगर (port == QRTR_PORT_CTRL)
		port = 0;

	__sock_put(&ipc->sk);

	xa_erase(&qrtr_ports, port);

	/* Ensure that अगर qrtr_port_lookup() did enter the RCU पढ़ो section we
	 * रुको क्रम it to up increment the refcount */
	synchronize_rcu();
पूर्ण

/* Assign port number to socket.
 *
 * Specअगरy port in the पूर्णांकeger poपूर्णांकed to by port, and it will be adjusted
 * on वापस as necesssary.
 *
 * Port may be:
 *   0: Assign ephemeral port in [QRTR_MIN_EPH_SOCKET, QRTR_MAX_EPH_SOCKET]
 *   <QRTR_MIN_EPH_SOCKET: Specअगरied; requires CAP_NET_ADMIN
 *   >QRTR_MIN_EPH_SOCKET: Specअगरied; available to all
 */
अटल पूर्णांक qrtr_port_assign(काष्ठा qrtr_sock *ipc, पूर्णांक *port)
अणु
	पूर्णांक rc;

	अगर (!*port) अणु
		rc = xa_alloc(&qrtr_ports, port, ipc, QRTR_EPH_PORT_RANGE,
				GFP_KERNEL);
	पूर्ण अन्यथा अगर (*port < QRTR_MIN_EPH_SOCKET && !capable(CAP_NET_ADMIN)) अणु
		rc = -EACCES;
	पूर्ण अन्यथा अगर (*port == QRTR_PORT_CTRL) अणु
		rc = xa_insert(&qrtr_ports, 0, ipc, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		rc = xa_insert(&qrtr_ports, *port, ipc, GFP_KERNEL);
	पूर्ण

	अगर (rc == -EBUSY)
		वापस -EADDRINUSE;
	अन्यथा अगर (rc < 0)
		वापस rc;

	sock_hold(&ipc->sk);

	वापस 0;
पूर्ण

/* Reset all non-control ports */
अटल व्योम qrtr_reset_ports(व्योम)
अणु
	काष्ठा qrtr_sock *ipc;
	अचिन्हित दीर्घ index;

	rcu_पढ़ो_lock();
	xa_क्रम_each_start(&qrtr_ports, index, ipc, 1) अणु
		sock_hold(&ipc->sk);
		ipc->sk.sk_err = ENETRESET;
		ipc->sk.sk_error_report(&ipc->sk);
		sock_put(&ipc->sk);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Bind socket to address.
 *
 * Socket should be locked upon call.
 */
अटल पूर्णांक __qrtr_bind(काष्ठा socket *sock,
		       स्थिर काष्ठा sockaddr_qrtr *addr, पूर्णांक zapped)
अणु
	काष्ठा qrtr_sock *ipc = qrtr_sk(sock->sk);
	काष्ठा sock *sk = sock->sk;
	पूर्णांक port;
	पूर्णांक rc;

	/* rebinding ok */
	अगर (!zapped && addr->sq_port == ipc->us.sq_port)
		वापस 0;

	port = addr->sq_port;
	rc = qrtr_port_assign(ipc, &port);
	अगर (rc)
		वापस rc;

	/* unbind previous, अगर any */
	अगर (!zapped)
		qrtr_port_हटाओ(ipc);
	ipc->us.sq_port = port;

	sock_reset_flag(sk, SOCK_ZAPPED);

	/* Notअगरy all खोलो ports about the new controller */
	अगर (port == QRTR_PORT_CTRL)
		qrtr_reset_ports();

	वापस 0;
पूर्ण

/* Auto bind to an ephemeral port. */
अटल पूर्णांक qrtr_स्वतःbind(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_qrtr addr;

	अगर (!sock_flag(sk, SOCK_ZAPPED))
		वापस 0;

	addr.sq_family = AF_QIPCRTR;
	addr.sq_node = qrtr_local_nid;
	addr.sq_port = 0;

	वापस __qrtr_bind(sock, &addr, 1);
पूर्ण

/* Bind socket to specअगरied sockaddr. */
अटल पूर्णांक qrtr_bind(काष्ठा socket *sock, काष्ठा sockaddr *saddr, पूर्णांक len)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_qrtr *, addr, saddr);
	काष्ठा qrtr_sock *ipc = qrtr_sk(sock->sk);
	काष्ठा sock *sk = sock->sk;
	पूर्णांक rc;

	अगर (len < माप(*addr) || addr->sq_family != AF_QIPCRTR)
		वापस -EINVAL;

	अगर (addr->sq_node != ipc->us.sq_node)
		वापस -EINVAL;

	lock_sock(sk);
	rc = __qrtr_bind(sock, addr, sock_flag(sk, SOCK_ZAPPED));
	release_sock(sk);

	वापस rc;
पूर्ण

/* Queue packet to local peer socket. */
अटल पूर्णांक qrtr_local_enqueue(काष्ठा qrtr_node *node, काष्ठा sk_buff *skb,
			      पूर्णांक type, काष्ठा sockaddr_qrtr *from,
			      काष्ठा sockaddr_qrtr *to)
अणु
	काष्ठा qrtr_sock *ipc;
	काष्ठा qrtr_cb *cb;

	ipc = qrtr_port_lookup(to->sq_port);
	अगर (!ipc || &ipc->sk == skb->sk) अणु /* करो not send to self */
		kमुक्त_skb(skb);
		वापस -ENODEV;
	पूर्ण

	cb = (काष्ठा qrtr_cb *)skb->cb;
	cb->src_node = from->sq_node;
	cb->src_port = from->sq_port;

	अगर (sock_queue_rcv_skb(&ipc->sk, skb)) अणु
		qrtr_port_put(ipc);
		kमुक्त_skb(skb);
		वापस -ENOSPC;
	पूर्ण

	qrtr_port_put(ipc);

	वापस 0;
पूर्ण

/* Queue packet क्रम broadcast. */
अटल पूर्णांक qrtr_bcast_enqueue(काष्ठा qrtr_node *node, काष्ठा sk_buff *skb,
			      पूर्णांक type, काष्ठा sockaddr_qrtr *from,
			      काष्ठा sockaddr_qrtr *to)
अणु
	काष्ठा sk_buff *skbn;

	mutex_lock(&qrtr_node_lock);
	list_क्रम_each_entry(node, &qrtr_all_nodes, item) अणु
		skbn = skb_clone(skb, GFP_KERNEL);
		अगर (!skbn)
			अवरोध;
		skb_set_owner_w(skbn, skb->sk);
		qrtr_node_enqueue(node, skbn, type, from, to);
	पूर्ण
	mutex_unlock(&qrtr_node_lock);

	qrtr_local_enqueue(शून्य, skb, type, from, to);

	वापस 0;
पूर्ण

अटल पूर्णांक qrtr_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_qrtr *, addr, msg->msg_name);
	पूर्णांक (*enqueue_fn)(काष्ठा qrtr_node *, काष्ठा sk_buff *, पूर्णांक,
			  काष्ठा sockaddr_qrtr *, काष्ठा sockaddr_qrtr *);
	__le32 qrtr_type = cpu_to_le32(QRTR_TYPE_DATA);
	काष्ठा qrtr_sock *ipc = qrtr_sk(sock->sk);
	काष्ठा sock *sk = sock->sk;
	काष्ठा qrtr_node *node;
	काष्ठा sk_buff *skb;
	माप_प्रकार plen;
	u32 type;
	पूर्णांक rc;

	अगर (msg->msg_flags & ~(MSG_DONTWAIT))
		वापस -EINVAL;

	अगर (len > 65535)
		वापस -EMSGSIZE;

	lock_sock(sk);

	अगर (addr) अणु
		अगर (msg->msg_namelen < माप(*addr)) अणु
			release_sock(sk);
			वापस -EINVAL;
		पूर्ण

		अगर (addr->sq_family != AF_QIPCRTR) अणु
			release_sock(sk);
			वापस -EINVAL;
		पूर्ण

		rc = qrtr_स्वतःbind(sock);
		अगर (rc) अणु
			release_sock(sk);
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अगर (sk->sk_state == TCP_ESTABLISHED) अणु
		addr = &ipc->peer;
	पूर्ण अन्यथा अणु
		release_sock(sk);
		वापस -ENOTCONN;
	पूर्ण

	node = शून्य;
	अगर (addr->sq_node == QRTR_NODE_BCAST) अणु
		अगर (addr->sq_port != QRTR_PORT_CTRL &&
		    qrtr_local_nid != QRTR_NODE_BCAST) अणु
			release_sock(sk);
			वापस -ENOTCONN;
		पूर्ण
		enqueue_fn = qrtr_bcast_enqueue;
	पूर्ण अन्यथा अगर (addr->sq_node == ipc->us.sq_node) अणु
		enqueue_fn = qrtr_local_enqueue;
	पूर्ण अन्यथा अणु
		node = qrtr_node_lookup(addr->sq_node);
		अगर (!node) अणु
			release_sock(sk);
			वापस -ECONNRESET;
		पूर्ण
		enqueue_fn = qrtr_node_enqueue;
	पूर्ण

	plen = (len + 3) & ~3;
	skb = sock_alloc_send_skb(sk, plen + QRTR_HDR_MAX_SIZE,
				  msg->msg_flags & MSG_DONTWAIT, &rc);
	अगर (!skb) अणु
		rc = -ENOMEM;
		जाओ out_node;
	पूर्ण

	skb_reserve(skb, QRTR_HDR_MAX_SIZE);

	rc = स_नकल_from_msg(skb_put(skb, len), msg, len);
	अगर (rc) अणु
		kमुक्त_skb(skb);
		जाओ out_node;
	पूर्ण

	अगर (ipc->us.sq_port == QRTR_PORT_CTRL) अणु
		अगर (len < 4) अणु
			rc = -EINVAL;
			kमुक्त_skb(skb);
			जाओ out_node;
		पूर्ण

		/* control messages alपढ़ोy require the type as 'command' */
		skb_copy_bits(skb, 0, &qrtr_type, 4);
	पूर्ण

	type = le32_to_cpu(qrtr_type);
	rc = enqueue_fn(node, skb, type, &ipc->us, addr);
	अगर (rc >= 0)
		rc = len;

out_node:
	qrtr_node_release(node);
	release_sock(sk);

	वापस rc;
पूर्ण

अटल पूर्णांक qrtr_send_resume_tx(काष्ठा qrtr_cb *cb)
अणु
	काष्ठा sockaddr_qrtr remote = अणु AF_QIPCRTR, cb->src_node, cb->src_port पूर्ण;
	काष्ठा sockaddr_qrtr local = अणु AF_QIPCRTR, cb->dst_node, cb->dst_port पूर्ण;
	काष्ठा qrtr_ctrl_pkt *pkt;
	काष्ठा qrtr_node *node;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	node = qrtr_node_lookup(remote.sq_node);
	अगर (!node)
		वापस -EINVAL;

	skb = qrtr_alloc_ctrl_packet(&pkt, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	pkt->cmd = cpu_to_le32(QRTR_TYPE_RESUME_TX);
	pkt->client.node = cpu_to_le32(cb->dst_node);
	pkt->client.port = cpu_to_le32(cb->dst_port);

	ret = qrtr_node_enqueue(node, skb, QRTR_TYPE_RESUME_TX, &local, &remote);

	qrtr_node_release(node);

	वापस ret;
पूर्ण

अटल पूर्णांक qrtr_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			माप_प्रकार size, पूर्णांक flags)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_qrtr *, addr, msg->msg_name);
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	काष्ठा qrtr_cb *cb;
	पूर्णांक copied, rc;

	lock_sock(sk);

	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		release_sock(sk);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT,
				flags & MSG_DONTWAIT, &rc);
	अगर (!skb) अणु
		release_sock(sk);
		वापस rc;
	पूर्ण
	cb = (काष्ठा qrtr_cb *)skb->cb;

	copied = skb->len;
	अगर (copied > size) अणु
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण

	rc = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (rc < 0)
		जाओ out;
	rc = copied;

	अगर (addr) अणु
		/* There is an anonymous 2-byte hole after sq_family,
		 * make sure to clear it.
		 */
		स_रखो(addr, 0, माप(*addr));

		addr->sq_family = AF_QIPCRTR;
		addr->sq_node = cb->src_node;
		addr->sq_port = cb->src_port;
		msg->msg_namelen = माप(*addr);
	पूर्ण

out:
	अगर (cb->confirm_rx)
		qrtr_send_resume_tx(cb);

	skb_मुक्त_datagram(sk, skb);
	release_sock(sk);

	वापस rc;
पूर्ण

अटल पूर्णांक qrtr_connect(काष्ठा socket *sock, काष्ठा sockaddr *saddr,
			पूर्णांक len, पूर्णांक flags)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_qrtr *, addr, saddr);
	काष्ठा qrtr_sock *ipc = qrtr_sk(sock->sk);
	काष्ठा sock *sk = sock->sk;
	पूर्णांक rc;

	अगर (len < माप(*addr) || addr->sq_family != AF_QIPCRTR)
		वापस -EINVAL;

	lock_sock(sk);

	sk->sk_state = TCP_CLOSE;
	sock->state = SS_UNCONNECTED;

	rc = qrtr_स्वतःbind(sock);
	अगर (rc) अणु
		release_sock(sk);
		वापस rc;
	पूर्ण

	ipc->peer = *addr;
	sock->state = SS_CONNECTED;
	sk->sk_state = TCP_ESTABLISHED;

	release_sock(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक qrtr_getname(काष्ठा socket *sock, काष्ठा sockaddr *saddr,
			पूर्णांक peer)
अणु
	काष्ठा qrtr_sock *ipc = qrtr_sk(sock->sk);
	काष्ठा sockaddr_qrtr qaddr;
	काष्ठा sock *sk = sock->sk;

	lock_sock(sk);
	अगर (peer) अणु
		अगर (sk->sk_state != TCP_ESTABLISHED) अणु
			release_sock(sk);
			वापस -ENOTCONN;
		पूर्ण

		qaddr = ipc->peer;
	पूर्ण अन्यथा अणु
		qaddr = ipc->us;
	पूर्ण
	release_sock(sk);

	qaddr.sq_family = AF_QIPCRTR;

	स_नकल(saddr, &qaddr, माप(qaddr));

	वापस माप(qaddr);
पूर्ण

अटल पूर्णांक qrtr_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा qrtr_sock *ipc = qrtr_sk(sock->sk);
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_qrtr *sq;
	काष्ठा sk_buff *skb;
	काष्ठा अगरreq अगरr;
	दीर्घ len = 0;
	पूर्णांक rc = 0;

	lock_sock(sk);

	चयन (cmd) अणु
	हाल TIOCOUTQ:
		len = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
		अगर (len < 0)
			len = 0;
		rc = put_user(len, (पूर्णांक __user *)argp);
		अवरोध;
	हाल TIOCINQ:
		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb)
			len = skb->len;
		rc = put_user(len, (पूर्णांक __user *)argp);
		अवरोध;
	हाल SIOCGIFADDR:
		अगर (copy_from_user(&अगरr, argp, माप(अगरr))) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण

		sq = (काष्ठा sockaddr_qrtr *)&अगरr.अगरr_addr;
		*sq = ipc->us;
		अगर (copy_to_user(argp, &अगरr, माप(अगरr))) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SIOCADDRT:
	हाल SIOCDELRT:
	हाल SIOCSIFADDR:
	हाल SIOCGIFDSTADDR:
	हाल SIOCSIFDSTADDR:
	हाल SIOCGIFBRDADDR:
	हाल SIOCSIFBRDADDR:
	हाल SIOCGIFNETMASK:
	हाल SIOCSIFNETMASK:
		rc = -EINVAL;
		अवरोध;
	शेष:
		rc = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण

	release_sock(sk);

	वापस rc;
पूर्ण

अटल पूर्णांक qrtr_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा qrtr_sock *ipc;

	अगर (!sk)
		वापस 0;

	lock_sock(sk);

	ipc = qrtr_sk(sk);
	sk->sk_shutकरोwn = SHUTDOWN_MASK;
	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_state_change(sk);

	sock_set_flag(sk, SOCK_DEAD);
	sock_orphan(sk);
	sock->sk = शून्य;

	अगर (!sock_flag(sk, SOCK_ZAPPED))
		qrtr_port_हटाओ(ipc);

	skb_queue_purge(&sk->sk_receive_queue);

	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proto_ops qrtr_proto_ops = अणु
	.owner		= THIS_MODULE,
	.family		= AF_QIPCRTR,
	.bind		= qrtr_bind,
	.connect	= qrtr_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.listen		= sock_no_listen,
	.sendmsg	= qrtr_sendmsg,
	.recvmsg	= qrtr_recvmsg,
	.getname	= qrtr_getname,
	.ioctl		= qrtr_ioctl,
	.gettstamp	= sock_gettstamp,
	.poll		= datagram_poll,
	.shutकरोwn	= sock_no_shutकरोwn,
	.release	= qrtr_release,
	.mmap		= sock_no_mmap,
	.sendpage	= sock_no_sendpage,
पूर्ण;

अटल काष्ठा proto qrtr_proto = अणु
	.name		= "QIPCRTR",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा qrtr_sock),
पूर्ण;

अटल पूर्णांक qrtr_create(काष्ठा net *net, काष्ठा socket *sock,
		       पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा qrtr_sock *ipc;
	काष्ठा sock *sk;

	अगर (sock->type != SOCK_DGRAM)
		वापस -EPROTOTYPE;

	sk = sk_alloc(net, AF_QIPCRTR, GFP_KERNEL, &qrtr_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_set_flag(sk, SOCK_ZAPPED);

	sock_init_data(sock, sk);
	sock->ops = &qrtr_proto_ops;

	ipc = qrtr_sk(sk);
	ipc->us.sq_family = AF_QIPCRTR;
	ipc->us.sq_node = qrtr_local_nid;
	ipc->us.sq_port = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_proto_family qrtr_family = अणु
	.owner	= THIS_MODULE,
	.family	= AF_QIPCRTR,
	.create	= qrtr_create,
पूर्ण;

अटल पूर्णांक __init qrtr_proto_init(व्योम)
अणु
	पूर्णांक rc;

	rc = proto_रेजिस्टर(&qrtr_proto, 1);
	अगर (rc)
		वापस rc;

	rc = sock_रेजिस्टर(&qrtr_family);
	अगर (rc)
		जाओ err_proto;

	rc = qrtr_ns_init();
	अगर (rc)
		जाओ err_sock;

	वापस 0;

err_sock:
	sock_unरेजिस्टर(qrtr_family.family);
err_proto:
	proto_unरेजिस्टर(&qrtr_proto);
	वापस rc;
पूर्ण
postcore_initcall(qrtr_proto_init);

अटल व्योम __निकास qrtr_proto_fini(व्योम)
अणु
	qrtr_ns_हटाओ();
	sock_unरेजिस्टर(qrtr_family.family);
	proto_unरेजिस्टर(&qrtr_proto);
पूर्ण
module_निकास(qrtr_proto_fini);

MODULE_DESCRIPTION("Qualcomm IPC-router driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_NETPROTO(PF_QIPCRTR);
