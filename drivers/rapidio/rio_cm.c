<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * rio_cm - RapidIO Channelized Messaging Driver
 *
 * Copyright 2013-2016 Integrated Device Technology, Inc.
 * Copyright (c) 2015, Prodrive Technologies
 * Copyright (c) 2015, RapidIO Trade Association
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/reboot.h>
#समावेश <linux/bitops.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rio_cm_cdev.h>

#घोषणा DRV_NAME        "rio_cm"
#घोषणा DRV_VERSION     "1.0.0"
#घोषणा DRV_AUTHOR      "Alexandre Bounine <alexandre.bounine@idt.com>"
#घोषणा DRV_DESC        "RapidIO Channelized Messaging Driver"
#घोषणा DEV_NAME	"rio_cm"

/* Debug output filtering masks */
क्रमागत अणु
	DBG_NONE	= 0,
	DBG_INIT	= BIT(0), /* driver init */
	DBG_EXIT	= BIT(1), /* driver निकास */
	DBG_MPORT	= BIT(2), /* mport add/हटाओ */
	DBG_RDEV	= BIT(3), /* RapidIO device add/हटाओ */
	DBG_CHOP	= BIT(4), /* channel operations */
	DBG_WAIT	= BIT(5), /* रुकोing क्रम events */
	DBG_TX		= BIT(6), /* message TX */
	DBG_TX_EVENT	= BIT(7), /* message TX event */
	DBG_RX_DATA	= BIT(8), /* inbound data messages */
	DBG_RX_CMD	= BIT(9), /* inbound REQ/ACK/NACK messages */
	DBG_ALL		= ~0,
पूर्ण;

#अगर_घोषित DEBUG
#घोषणा riocm_debug(level, fmt, arg...) \
	करो अणु \
		अगर (DBG_##level & dbg_level) \
			pr_debug(DRV_NAME ": %s " fmt "\n", \
				__func__, ##arg); \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा riocm_debug(level, fmt, arg...) \
		no_prपूर्णांकk(KERN_DEBUG pr_fmt(DRV_NAME fmt "\n"), ##arg)
#पूर्ण_अगर

#घोषणा riocm_warn(fmt, arg...) \
	pr_warn(DRV_NAME ": %s WARNING " fmt "\n", __func__, ##arg)

#घोषणा riocm_error(fmt, arg...) \
	pr_err(DRV_NAME ": %s ERROR " fmt "\n", __func__, ##arg)


अटल पूर्णांक cmbox = 1;
module_param(cmbox, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(cmbox, "RapidIO Mailbox number (default 1)");

अटल पूर्णांक chstart = 256;
module_param(chstart, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(chstart,
		 "Start channel number for dynamic allocation (default 256)");

#अगर_घोषित DEBUG
अटल u32 dbg_level = DBG_NONE;
module_param(dbg_level, uपूर्णांक, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(dbg_level, "Debugging output level (default 0 = none)");
#पूर्ण_अगर

MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

#घोषणा RIOCM_TX_RING_SIZE	128
#घोषणा RIOCM_RX_RING_SIZE	128
#घोषणा RIOCM_CONNECT_TO	3 /* connect response TO (in sec) */

#घोषणा RIOCM_MAX_CHNUM		0xffff /* Use full range of u16 field */
#घोषणा RIOCM_CHNUM_AUTO	0
#घोषणा RIOCM_MAX_EP_COUNT	0x10000 /* Max number of endpoपूर्णांकs */

क्रमागत rio_cm_state अणु
	RIO_CM_IDLE,
	RIO_CM_CONNECT,
	RIO_CM_CONNECTED,
	RIO_CM_DISCONNECT,
	RIO_CM_CHAN_BOUND,
	RIO_CM_LISTEN,
	RIO_CM_DESTROYING,
पूर्ण;

क्रमागत rio_cm_pkt_type अणु
	RIO_CM_SYS	= 0xaa,
	RIO_CM_CHAN	= 0x55,
पूर्ण;

क्रमागत rio_cm_chop अणु
	CM_CONN_REQ,
	CM_CONN_ACK,
	CM_CONN_CLOSE,
	CM_DATA_MSG,
पूर्ण;

काष्ठा rio_ch_base_bhdr अणु
	u32 src_id;
	u32 dst_id;
#घोषणा RIO_HDR_LETTER_MASK 0xffff0000
#घोषणा RIO_HDR_MBOX_MASK   0x0000ffff
	u8  src_mbox;
	u8  dst_mbox;
	u8  type;
पूर्ण __attribute__((__packed__));

काष्ठा rio_ch_chan_hdr अणु
	काष्ठा rio_ch_base_bhdr bhdr;
	u8 ch_op;
	u16 dst_ch;
	u16 src_ch;
	u16 msg_len;
	u16 rsrvd;
पूर्ण __attribute__((__packed__));

काष्ठा tx_req अणु
	काष्ठा list_head node;
	काष्ठा rio_dev   *rdev;
	व्योम		 *buffer;
	माप_प्रकार		 len;
पूर्ण;

काष्ठा cm_dev अणु
	काष्ठा list_head	list;
	काष्ठा rio_mport	*mport;
	व्योम			*rx_buf[RIOCM_RX_RING_SIZE];
	पूर्णांक			rx_slots;
	काष्ठा mutex		rx_lock;

	व्योम			*tx_buf[RIOCM_TX_RING_SIZE];
	पूर्णांक			tx_slot;
	पूर्णांक			tx_cnt;
	पूर्णांक			tx_ack_slot;
	काष्ठा list_head	tx_reqs;
	spinlock_t		tx_lock;

	काष्ठा list_head	peers;
	u32			npeers;
	काष्ठा workqueue_काष्ठा *rx_wq;
	काष्ठा work_काष्ठा	rx_work;
पूर्ण;

काष्ठा chan_rx_ring अणु
	व्योम	*buf[RIOCM_RX_RING_SIZE];
	पूर्णांक	head;
	पूर्णांक	tail;
	पूर्णांक	count;

	/* Tracking RX buffers reported to upper level */
	व्योम	*inuse[RIOCM_RX_RING_SIZE];
	पूर्णांक	inuse_cnt;
पूर्ण;

काष्ठा rio_channel अणु
	u16			id;	/* local channel ID */
	काष्ठा kref		ref;	/* channel refcount */
	काष्ठा file		*filp;
	काष्ठा cm_dev		*cmdev;	/* associated CM device object */
	काष्ठा rio_dev		*rdev;	/* remote RapidIO device */
	क्रमागत rio_cm_state	state;
	पूर्णांक			error;
	spinlock_t		lock;
	व्योम			*context;
	u32			loc_destid;	/* local destID */
	u32			rem_destid;	/* remote destID */
	u16			rem_channel;	/* remote channel ID */
	काष्ठा list_head	accept_queue;
	काष्ठा list_head	ch_node;
	काष्ठा completion	comp;
	काष्ठा completion	comp_बंद;
	काष्ठा chan_rx_ring	rx_ring;
पूर्ण;

काष्ठा cm_peer अणु
	काष्ठा list_head node;
	काष्ठा rio_dev *rdev;
पूर्ण;

काष्ठा rio_cm_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा cm_dev *cm;
	व्योम *data;
पूर्ण;

काष्ठा conn_req अणु
	काष्ठा list_head node;
	u32 destid;	/* requester destID */
	u16 chan;	/* requester channel ID */
	काष्ठा cm_dev *cmdev;
पूर्ण;

/*
 * A channel_dev काष्ठाure represents a CM_CDEV
 * @cdev	Character device
 * @dev		Associated device object
 */
काष्ठा channel_dev अणु
	काष्ठा cdev	cdev;
	काष्ठा device	*dev;
पूर्ण;

अटल काष्ठा rio_channel *riocm_ch_alloc(u16 ch_num);
अटल व्योम riocm_ch_मुक्त(काष्ठा kref *ref);
अटल पूर्णांक riocm_post_send(काष्ठा cm_dev *cm, काष्ठा rio_dev *rdev,
			   व्योम *buffer, माप_प्रकार len);
अटल पूर्णांक riocm_ch_बंद(काष्ठा rio_channel *ch);

अटल DEFINE_SPINLOCK(idr_lock);
अटल DEFINE_IDR(ch_idr);

अटल LIST_HEAD(cm_dev_list);
अटल DECLARE_RWSEM(rdev_sem);

अटल काष्ठा class *dev_class;
अटल अचिन्हित पूर्णांक dev_major;
अटल अचिन्हित पूर्णांक dev_minor_base;
अटल dev_t dev_number;
अटल काष्ठा channel_dev riocm_cdev;

#घोषणा is_msg_capable(src_ops, dst_ops)			\
			((src_ops & RIO_SRC_OPS_DATA_MSG) &&	\
			 (dst_ops & RIO_DST_OPS_DATA_MSG))
#घोषणा dev_cm_capable(dev) \
	is_msg_capable(dev->src_ops, dev->dst_ops)

अटल पूर्णांक riocm_cmp(काष्ठा rio_channel *ch, क्रमागत rio_cm_state cmp)
अणु
	पूर्णांक ret;

	spin_lock_bh(&ch->lock);
	ret = (ch->state == cmp);
	spin_unlock_bh(&ch->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक riocm_cmp_exch(काष्ठा rio_channel *ch,
			   क्रमागत rio_cm_state cmp, क्रमागत rio_cm_state exch)
अणु
	पूर्णांक ret;

	spin_lock_bh(&ch->lock);
	ret = (ch->state == cmp);
	अगर (ret)
		ch->state = exch;
	spin_unlock_bh(&ch->lock);
	वापस ret;
पूर्ण

अटल क्रमागत rio_cm_state riocm_exch(काष्ठा rio_channel *ch,
				    क्रमागत rio_cm_state exch)
अणु
	क्रमागत rio_cm_state old;

	spin_lock_bh(&ch->lock);
	old = ch->state;
	ch->state = exch;
	spin_unlock_bh(&ch->lock);
	वापस old;
पूर्ण

अटल काष्ठा rio_channel *riocm_get_channel(u16 nr)
अणु
	काष्ठा rio_channel *ch;

	spin_lock_bh(&idr_lock);
	ch = idr_find(&ch_idr, nr);
	अगर (ch)
		kref_get(&ch->ref);
	spin_unlock_bh(&idr_lock);
	वापस ch;
पूर्ण

अटल व्योम riocm_put_channel(काष्ठा rio_channel *ch)
अणु
	kref_put(&ch->ref, riocm_ch_मुक्त);
पूर्ण

अटल व्योम *riocm_rx_get_msg(काष्ठा cm_dev *cm)
अणु
	व्योम *msg;
	पूर्णांक i;

	msg = rio_get_inb_message(cm->mport, cmbox);
	अगर (msg) अणु
		क्रम (i = 0; i < RIOCM_RX_RING_SIZE; i++) अणु
			अगर (cm->rx_buf[i] == msg) अणु
				cm->rx_buf[i] = शून्य;
				cm->rx_slots++;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == RIOCM_RX_RING_SIZE)
			riocm_warn("no record for buffer 0x%p", msg);
	पूर्ण

	वापस msg;
पूर्ण

/*
 * riocm_rx_fill - fills a ring of receive buffers क्रम given cm device
 * @cm: cm_dev object
 * @nent: max number of entries to fill
 *
 * Returns: none
 */
अटल व्योम riocm_rx_fill(काष्ठा cm_dev *cm, पूर्णांक nent)
अणु
	पूर्णांक i;

	अगर (cm->rx_slots == 0)
		वापस;

	क्रम (i = 0; i < RIOCM_RX_RING_SIZE && cm->rx_slots && nent; i++) अणु
		अगर (cm->rx_buf[i] == शून्य) अणु
			cm->rx_buf[i] = kदो_स्मृति(RIO_MAX_MSG_SIZE, GFP_KERNEL);
			अगर (cm->rx_buf[i] == शून्य)
				अवरोध;
			rio_add_inb_buffer(cm->mport, cmbox, cm->rx_buf[i]);
			cm->rx_slots--;
			nent--;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * riocm_rx_मुक्त - मुक्तs all receive buffers associated with given cm device
 * @cm: cm_dev object
 *
 * Returns: none
 */
अटल व्योम riocm_rx_मुक्त(काष्ठा cm_dev *cm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RIOCM_RX_RING_SIZE; i++) अणु
		अगर (cm->rx_buf[i] != शून्य) अणु
			kमुक्त(cm->rx_buf[i]);
			cm->rx_buf[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * riocm_req_handler - connection request handler
 * @cm: cm_dev object
 * @req_data: poपूर्णांकer to the request packet
 *
 * Returns: 0 अगर success, or
 *          -EINVAL अगर channel is not in correct state,
 *          -ENODEV अगर cannot find a channel with specअगरied ID,
 *          -ENOMEM अगर unable to allocate memory to store the request
 */
अटल पूर्णांक riocm_req_handler(काष्ठा cm_dev *cm, व्योम *req_data)
अणु
	काष्ठा rio_channel *ch;
	काष्ठा conn_req *req;
	काष्ठा rio_ch_chan_hdr *hh = req_data;
	u16 chnum;

	chnum = ntohs(hh->dst_ch);

	ch = riocm_get_channel(chnum);

	अगर (!ch)
		वापस -ENODEV;

	अगर (ch->state != RIO_CM_LISTEN) अणु
		riocm_debug(RX_CMD, "channel %d is not in listen state", chnum);
		riocm_put_channel(ch);
		वापस -EINVAL;
	पूर्ण

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req) अणु
		riocm_put_channel(ch);
		वापस -ENOMEM;
	पूर्ण

	req->destid = ntohl(hh->bhdr.src_id);
	req->chan = ntohs(hh->src_ch);
	req->cmdev = cm;

	spin_lock_bh(&ch->lock);
	list_add_tail(&req->node, &ch->accept_queue);
	spin_unlock_bh(&ch->lock);
	complete(&ch->comp);
	riocm_put_channel(ch);

	वापस 0;
पूर्ण

/*
 * riocm_resp_handler - response to connection request handler
 * @resp_data: poपूर्णांकer to the response packet
 *
 * Returns: 0 अगर success, or
 *          -EINVAL अगर channel is not in correct state,
 *          -ENODEV अगर cannot find a channel with specअगरied ID,
 */
अटल पूर्णांक riocm_resp_handler(व्योम *resp_data)
अणु
	काष्ठा rio_channel *ch;
	काष्ठा rio_ch_chan_hdr *hh = resp_data;
	u16 chnum;

	chnum = ntohs(hh->dst_ch);
	ch = riocm_get_channel(chnum);
	अगर (!ch)
		वापस -ENODEV;

	अगर (ch->state != RIO_CM_CONNECT) अणु
		riocm_put_channel(ch);
		वापस -EINVAL;
	पूर्ण

	riocm_exch(ch, RIO_CM_CONNECTED);
	ch->rem_channel = ntohs(hh->src_ch);
	complete(&ch->comp);
	riocm_put_channel(ch);

	वापस 0;
पूर्ण

/*
 * riocm_बंद_handler - channel बंद request handler
 * @req_data: poपूर्णांकer to the request packet
 *
 * Returns: 0 अगर success, or
 *          -ENODEV अगर cannot find a channel with specअगरied ID,
 *            + error codes वापसed by riocm_ch_बंद.
 */
अटल पूर्णांक riocm_बंद_handler(व्योम *data)
अणु
	काष्ठा rio_channel *ch;
	काष्ठा rio_ch_chan_hdr *hh = data;
	पूर्णांक ret;

	riocm_debug(RX_CMD, "for ch=%d", ntohs(hh->dst_ch));

	spin_lock_bh(&idr_lock);
	ch = idr_find(&ch_idr, ntohs(hh->dst_ch));
	अगर (!ch) अणु
		spin_unlock_bh(&idr_lock);
		वापस -ENODEV;
	पूर्ण
	idr_हटाओ(&ch_idr, ch->id);
	spin_unlock_bh(&idr_lock);

	riocm_exch(ch, RIO_CM_DISCONNECT);

	ret = riocm_ch_बंद(ch);
	अगर (ret)
		riocm_debug(RX_CMD, "riocm_ch_close() returned %d", ret);

	वापस 0;
पूर्ण

/*
 * rio_cm_handler - function that services request (non-data) packets
 * @cm: cm_dev object
 * @data: poपूर्णांकer to the packet
 */
अटल व्योम rio_cm_handler(काष्ठा cm_dev *cm, व्योम *data)
अणु
	काष्ठा rio_ch_chan_hdr *hdr;

	अगर (!rio_mport_is_running(cm->mport))
		जाओ out;

	hdr = data;

	riocm_debug(RX_CMD, "OP=%x for ch=%d from %d",
		    hdr->ch_op, ntohs(hdr->dst_ch), ntohs(hdr->src_ch));

	चयन (hdr->ch_op) अणु
	हाल CM_CONN_REQ:
		riocm_req_handler(cm, data);
		अवरोध;
	हाल CM_CONN_ACK:
		riocm_resp_handler(data);
		अवरोध;
	हाल CM_CONN_CLOSE:
		riocm_बंद_handler(data);
		अवरोध;
	शेष:
		riocm_error("Invalid packet header");
		अवरोध;
	पूर्ण
out:
	kमुक्त(data);
पूर्ण

/*
 * rio_rx_data_handler - received data packet handler
 * @cm: cm_dev object
 * @buf: data packet
 *
 * Returns: 0 अगर success, or
 *          -ENODEV अगर cannot find a channel with specअगरied ID,
 *          -EIO अगर channel is not in CONNECTED state,
 *          -ENOMEM अगर channel RX queue is full (packet discarded)
 */
अटल पूर्णांक rio_rx_data_handler(काष्ठा cm_dev *cm, व्योम *buf)
अणु
	काष्ठा rio_ch_chan_hdr *hdr;
	काष्ठा rio_channel *ch;

	hdr = buf;

	riocm_debug(RX_DATA, "for ch=%d", ntohs(hdr->dst_ch));

	ch = riocm_get_channel(ntohs(hdr->dst_ch));
	अगर (!ch) अणु
		/* Discard data message क्रम non-existing channel */
		kमुक्त(buf);
		वापस -ENODEV;
	पूर्ण

	/* Place poपूर्णांकer to the buffer पूर्णांकo channel's RX queue */
	spin_lock(&ch->lock);

	अगर (ch->state != RIO_CM_CONNECTED) अणु
		/* Channel is not पढ़ोy to receive data, discard a packet */
		riocm_debug(RX_DATA, "ch=%d is in wrong state=%d",
			    ch->id, ch->state);
		spin_unlock(&ch->lock);
		kमुक्त(buf);
		riocm_put_channel(ch);
		वापस -EIO;
	पूर्ण

	अगर (ch->rx_ring.count == RIOCM_RX_RING_SIZE) अणु
		/* If RX ring is full, discard a packet */
		riocm_debug(RX_DATA, "ch=%d is full", ch->id);
		spin_unlock(&ch->lock);
		kमुक्त(buf);
		riocm_put_channel(ch);
		वापस -ENOMEM;
	पूर्ण

	ch->rx_ring.buf[ch->rx_ring.head] = buf;
	ch->rx_ring.head++;
	ch->rx_ring.count++;
	ch->rx_ring.head %= RIOCM_RX_RING_SIZE;

	complete(&ch->comp);

	spin_unlock(&ch->lock);
	riocm_put_channel(ch);

	वापस 0;
पूर्ण

/*
 * rio_ibmsg_handler - inbound message packet handler
 */
अटल व्योम rio_ibmsg_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cm_dev *cm = container_of(work, काष्ठा cm_dev, rx_work);
	व्योम *data;
	काष्ठा rio_ch_chan_hdr *hdr;

	अगर (!rio_mport_is_running(cm->mport))
		वापस;

	जबतक (1) अणु
		mutex_lock(&cm->rx_lock);
		data = riocm_rx_get_msg(cm);
		अगर (data)
			riocm_rx_fill(cm, 1);
		mutex_unlock(&cm->rx_lock);

		अगर (data == शून्य)
			अवरोध;

		hdr = data;

		अगर (hdr->bhdr.type != RIO_CM_CHAN) अणु
			/* For now simply discard packets other than channel */
			riocm_error("Unsupported TYPE code (0x%x). Msg dropped",
				    hdr->bhdr.type);
			kमुक्त(data);
			जारी;
		पूर्ण

		/* Process a channel message */
		अगर (hdr->ch_op == CM_DATA_MSG)
			rio_rx_data_handler(cm, data);
		अन्यथा
			rio_cm_handler(cm, data);
	पूर्ण
पूर्ण

अटल व्योम riocm_inb_msg_event(काष्ठा rio_mport *mport, व्योम *dev_id,
				पूर्णांक mbox, पूर्णांक slot)
अणु
	काष्ठा cm_dev *cm = dev_id;

	अगर (rio_mport_is_running(cm->mport) && !work_pending(&cm->rx_work))
		queue_work(cm->rx_wq, &cm->rx_work);
पूर्ण

/*
 * rio_txcq_handler - TX completion handler
 * @cm: cm_dev object
 * @slot: TX queue slot
 *
 * TX completion handler also ensures that pending request packets are placed
 * पूर्णांकo transmit queue as soon as a मुक्त slot becomes available. This is करोne
 * to give higher priority to request packets during high पूर्णांकensity data flow.
 */
अटल व्योम rio_txcq_handler(काष्ठा cm_dev *cm, पूर्णांक slot)
अणु
	पूर्णांक ack_slot;

	/* ATTN: Add TX completion notअगरication अगर/when direct buffer
	 * transfer is implemented. At this moment only correct tracking
	 * of tx_count is important.
	 */
	riocm_debug(TX_EVENT, "for mport_%d slot %d tx_cnt %d",
		    cm->mport->id, slot, cm->tx_cnt);

	spin_lock(&cm->tx_lock);
	ack_slot = cm->tx_ack_slot;

	अगर (ack_slot == slot)
		riocm_debug(TX_EVENT, "slot == ack_slot");

	जबतक (cm->tx_cnt && ((ack_slot != slot) ||
	       (cm->tx_cnt == RIOCM_TX_RING_SIZE))) अणु

		cm->tx_buf[ack_slot] = शून्य;
		++ack_slot;
		ack_slot &= (RIOCM_TX_RING_SIZE - 1);
		cm->tx_cnt--;
	पूर्ण

	अगर (cm->tx_cnt < 0 || cm->tx_cnt > RIOCM_TX_RING_SIZE)
		riocm_error("tx_cnt %d out of sync", cm->tx_cnt);

	WARN_ON((cm->tx_cnt < 0) || (cm->tx_cnt > RIOCM_TX_RING_SIZE));

	cm->tx_ack_slot = ack_slot;

	/*
	 * If there are pending requests, insert them पूर्णांकo transmit queue
	 */
	अगर (!list_empty(&cm->tx_reqs) && (cm->tx_cnt < RIOCM_TX_RING_SIZE)) अणु
		काष्ठा tx_req *req, *_req;
		पूर्णांक rc;

		list_क्रम_each_entry_safe(req, _req, &cm->tx_reqs, node) अणु
			list_del(&req->node);
			cm->tx_buf[cm->tx_slot] = req->buffer;
			rc = rio_add_outb_message(cm->mport, req->rdev, cmbox,
						  req->buffer, req->len);
			kमुक्त(req->buffer);
			kमुक्त(req);

			++cm->tx_cnt;
			++cm->tx_slot;
			cm->tx_slot &= (RIOCM_TX_RING_SIZE - 1);
			अगर (cm->tx_cnt == RIOCM_TX_RING_SIZE)
				अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&cm->tx_lock);
पूर्ण

अटल व्योम riocm_outb_msg_event(काष्ठा rio_mport *mport, व्योम *dev_id,
				 पूर्णांक mbox, पूर्णांक slot)
अणु
	काष्ठा cm_dev *cm = dev_id;

	अगर (cm && rio_mport_is_running(cm->mport))
		rio_txcq_handler(cm, slot);
पूर्ण

अटल पूर्णांक riocm_queue_req(काष्ठा cm_dev *cm, काष्ठा rio_dev *rdev,
			   व्योम *buffer, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा tx_req *treq;

	treq = kzalloc(माप(*treq), GFP_KERNEL);
	अगर (treq == शून्य)
		वापस -ENOMEM;

	treq->rdev = rdev;
	treq->buffer = buffer;
	treq->len = len;

	spin_lock_irqsave(&cm->tx_lock, flags);
	list_add_tail(&treq->node, &cm->tx_reqs);
	spin_unlock_irqrestore(&cm->tx_lock, flags);
	वापस 0;
पूर्ण

/*
 * riocm_post_send - helper function that places packet पूर्णांकo msg TX queue
 * @cm: cm_dev object
 * @rdev: target RapidIO device object (required by outbound msg पूर्णांकerface)
 * @buffer: poपूर्णांकer to a packet buffer to send
 * @len: length of data to transfer
 * @req: request priority flag
 *
 * Returns: 0 अगर success, or error code otherwise.
 */
अटल पूर्णांक riocm_post_send(काष्ठा cm_dev *cm, काष्ठा rio_dev *rdev,
			   व्योम *buffer, माप_प्रकार len)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cm->tx_lock, flags);

	अगर (cm->mport == शून्य) अणु
		rc = -ENODEV;
		जाओ err_out;
	पूर्ण

	अगर (cm->tx_cnt == RIOCM_TX_RING_SIZE) अणु
		riocm_debug(TX, "Tx Queue is full");
		rc = -EBUSY;
		जाओ err_out;
	पूर्ण

	cm->tx_buf[cm->tx_slot] = buffer;
	rc = rio_add_outb_message(cm->mport, rdev, cmbox, buffer, len);

	riocm_debug(TX, "Add buf@%p destid=%x tx_slot=%d tx_cnt=%d",
		 buffer, rdev->destid, cm->tx_slot, cm->tx_cnt);

	++cm->tx_cnt;
	++cm->tx_slot;
	cm->tx_slot &= (RIOCM_TX_RING_SIZE - 1);

err_out:
	spin_unlock_irqrestore(&cm->tx_lock, flags);
	वापस rc;
पूर्ण

/*
 * riocm_ch_send - sends a data packet to a remote device
 * @ch_id: local channel ID
 * @buf: poपूर्णांकer to a data buffer to send (including CM header)
 * @len: length of data to transfer (including CM header)
 *
 * ATTN: ASSUMES THAT THE HEADER SPACE IS RESERVED PART OF THE DATA PACKET
 *
 * Returns: 0 अगर success, or
 *          -EINVAL अगर one or more input parameters is/are not valid,
 *          -ENODEV अगर cannot find a channel with specअगरied ID,
 *          -EAGAIN अगर a channel is not in CONNECTED state,
 *	    + error codes वापसed by HW send routine.
 */
अटल पूर्णांक riocm_ch_send(u16 ch_id, व्योम *buf, पूर्णांक len)
अणु
	काष्ठा rio_channel *ch;
	काष्ठा rio_ch_chan_hdr *hdr;
	पूर्णांक ret;

	अगर (buf == शून्य || ch_id == 0 || len == 0 || len > RIO_MAX_MSG_SIZE)
		वापस -EINVAL;

	ch = riocm_get_channel(ch_id);
	अगर (!ch) अणु
		riocm_error("%s(%d) ch_%d not found", current->comm,
			    task_pid_nr(current), ch_id);
		वापस -ENODEV;
	पूर्ण

	अगर (!riocm_cmp(ch, RIO_CM_CONNECTED)) अणु
		ret = -EAGAIN;
		जाओ err_out;
	पूर्ण

	/*
	 * Fill buffer header section with corresponding channel data
	 */
	hdr = buf;

	hdr->bhdr.src_id = htonl(ch->loc_destid);
	hdr->bhdr.dst_id = htonl(ch->rem_destid);
	hdr->bhdr.src_mbox = cmbox;
	hdr->bhdr.dst_mbox = cmbox;
	hdr->bhdr.type = RIO_CM_CHAN;
	hdr->ch_op = CM_DATA_MSG;
	hdr->dst_ch = htons(ch->rem_channel);
	hdr->src_ch = htons(ch->id);
	hdr->msg_len = htons((u16)len);

	/* ATTN: the function call below relies on the fact that underlying
	 * HW-specअगरic add_outb_message() routine copies TX data पूर्णांकo its own
	 * पूर्णांकernal transfer buffer (true क्रम all RIONET compatible mport
	 * drivers). Must be reviewed अगर mport driver uses the buffer directly.
	 */

	ret = riocm_post_send(ch->cmdev, ch->rdev, buf, len);
	अगर (ret)
		riocm_debug(TX, "ch %d send_err=%d", ch->id, ret);
err_out:
	riocm_put_channel(ch);
	वापस ret;
पूर्ण

अटल पूर्णांक riocm_ch_मुक्त_rxbuf(काष्ठा rio_channel *ch, व्योम *buf)
अणु
	पूर्णांक i, ret = -EINVAL;

	spin_lock_bh(&ch->lock);

	क्रम (i = 0; i < RIOCM_RX_RING_SIZE; i++) अणु
		अगर (ch->rx_ring.inuse[i] == buf) अणु
			ch->rx_ring.inuse[i] = शून्य;
			ch->rx_ring.inuse_cnt--;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ch->lock);

	अगर (!ret)
		kमुक्त(buf);

	वापस ret;
पूर्ण

/*
 * riocm_ch_receive - fetch a data packet received क्रम the specअगरied channel
 * @ch: local channel ID
 * @buf: poपूर्णांकer to a packet buffer
 * @समयout: समयout to रुको क्रम incoming packet (in jअगरfies)
 *
 * Returns: 0 and valid buffer poपूर्णांकer अगर success, or शून्य poपूर्णांकer and one of:
 *          -EAGAIN अगर a channel is not in CONNECTED state,
 *          -ENOMEM अगर in-use tracking queue is full,
 *          -ETIME अगर रुको समयout expired,
 *	    -EINTR अगर रुको was पूर्णांकerrupted.
 */
अटल पूर्णांक riocm_ch_receive(काष्ठा rio_channel *ch, व्योम **buf, दीर्घ समयout)
अणु
	व्योम *rxmsg = शून्य;
	पूर्णांक i, ret = 0;
	दीर्घ wret;

	अगर (!riocm_cmp(ch, RIO_CM_CONNECTED)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (ch->rx_ring.inuse_cnt == RIOCM_RX_RING_SIZE) अणु
		/* If we करो not have entries to track buffers given to upper
		 * layer, reject request.
		 */
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ch->comp, समयout);

	riocm_debug(WAIT, "wait on %d returned %ld", ch->id, wret);

	अगर (!wret)
		ret = -ETIME;
	अन्यथा अगर (wret == -ERESTARTSYS)
		ret = -EINTR;
	अन्यथा
		ret = riocm_cmp(ch, RIO_CM_CONNECTED) ? 0 : -ECONNRESET;

	अगर (ret)
		जाओ out;

	spin_lock_bh(&ch->lock);

	rxmsg = ch->rx_ring.buf[ch->rx_ring.tail];
	ch->rx_ring.buf[ch->rx_ring.tail] = शून्य;
	ch->rx_ring.count--;
	ch->rx_ring.tail++;
	ch->rx_ring.tail %= RIOCM_RX_RING_SIZE;
	ret = -ENOMEM;

	क्रम (i = 0; i < RIOCM_RX_RING_SIZE; i++) अणु
		अगर (ch->rx_ring.inuse[i] == शून्य) अणु
			ch->rx_ring.inuse[i] = rxmsg;
			ch->rx_ring.inuse_cnt++;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		/* We have no entry to store pending message: drop it */
		kमुक्त(rxmsg);
		rxmsg = शून्य;
	पूर्ण

	spin_unlock_bh(&ch->lock);
out:
	*buf = rxmsg;
	वापस ret;
पूर्ण

/*
 * riocm_ch_connect - sends a connect request to a remote device
 * @loc_ch: local channel ID
 * @cm: CM device to send connect request
 * @peer: target RapidIO device
 * @rem_ch: remote channel ID
 *
 * Returns: 0 अगर success, or
 *          -EINVAL अगर the channel is not in IDLE state,
 *          -EAGAIN अगर no connection request available immediately,
 *          -ETIME अगर ACK response समयout expired,
 *          -EINTR अगर रुको क्रम response was पूर्णांकerrupted.
 */
अटल पूर्णांक riocm_ch_connect(u16 loc_ch, काष्ठा cm_dev *cm,
			    काष्ठा cm_peer *peer, u16 rem_ch)
अणु
	काष्ठा rio_channel *ch = शून्य;
	काष्ठा rio_ch_chan_hdr *hdr;
	पूर्णांक ret;
	दीर्घ wret;

	ch = riocm_get_channel(loc_ch);
	अगर (!ch)
		वापस -ENODEV;

	अगर (!riocm_cmp_exch(ch, RIO_CM_IDLE, RIO_CM_CONNECT)) अणु
		ret = -EINVAL;
		जाओ conn_करोne;
	पूर्ण

	ch->cmdev = cm;
	ch->rdev = peer->rdev;
	ch->context = शून्य;
	ch->loc_destid = cm->mport->host_deviceid;
	ch->rem_channel = rem_ch;

	/*
	 * Send connect request to the remote RapidIO device
	 */

	hdr = kzalloc(माप(*hdr), GFP_KERNEL);
	अगर (hdr == शून्य) अणु
		ret = -ENOMEM;
		जाओ conn_करोne;
	पूर्ण

	hdr->bhdr.src_id = htonl(ch->loc_destid);
	hdr->bhdr.dst_id = htonl(peer->rdev->destid);
	hdr->bhdr.src_mbox = cmbox;
	hdr->bhdr.dst_mbox = cmbox;
	hdr->bhdr.type = RIO_CM_CHAN;
	hdr->ch_op = CM_CONN_REQ;
	hdr->dst_ch = htons(rem_ch);
	hdr->src_ch = htons(loc_ch);

	/* ATTN: the function call below relies on the fact that underlying
	 * HW-specअगरic add_outb_message() routine copies TX data पूर्णांकo its
	 * पूर्णांकernal transfer buffer. Must be reviewed अगर mport driver uses
	 * this buffer directly.
	 */
	ret = riocm_post_send(cm, peer->rdev, hdr, माप(*hdr));

	अगर (ret != -EBUSY) अणु
		kमुक्त(hdr);
	पूर्ण अन्यथा अणु
		ret = riocm_queue_req(cm, peer->rdev, hdr, माप(*hdr));
		अगर (ret)
			kमुक्त(hdr);
	पूर्ण

	अगर (ret) अणु
		riocm_cmp_exch(ch, RIO_CM_CONNECT, RIO_CM_IDLE);
		जाओ conn_करोne;
	पूर्ण

	/* Wait क्रम connect response from the remote device */
	wret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ch->comp,
							 RIOCM_CONNECT_TO * HZ);
	riocm_debug(WAIT, "wait on %d returns %ld", ch->id, wret);

	अगर (!wret)
		ret = -ETIME;
	अन्यथा अगर (wret == -ERESTARTSYS)
		ret = -EINTR;
	अन्यथा
		ret = riocm_cmp(ch, RIO_CM_CONNECTED) ? 0 : -1;

conn_करोne:
	riocm_put_channel(ch);
	वापस ret;
पूर्ण

अटल पूर्णांक riocm_send_ack(काष्ठा rio_channel *ch)
अणु
	काष्ठा rio_ch_chan_hdr *hdr;
	पूर्णांक ret;

	hdr = kzalloc(माप(*hdr), GFP_KERNEL);
	अगर (hdr == शून्य)
		वापस -ENOMEM;

	hdr->bhdr.src_id = htonl(ch->loc_destid);
	hdr->bhdr.dst_id = htonl(ch->rem_destid);
	hdr->dst_ch = htons(ch->rem_channel);
	hdr->src_ch = htons(ch->id);
	hdr->bhdr.src_mbox = cmbox;
	hdr->bhdr.dst_mbox = cmbox;
	hdr->bhdr.type = RIO_CM_CHAN;
	hdr->ch_op = CM_CONN_ACK;

	/* ATTN: the function call below relies on the fact that underlying
	 * add_outb_message() routine copies TX data पूर्णांकo its पूर्णांकernal transfer
	 * buffer. Review अगर चयनing to direct buffer version.
	 */
	ret = riocm_post_send(ch->cmdev, ch->rdev, hdr, माप(*hdr));

	अगर (ret == -EBUSY && !riocm_queue_req(ch->cmdev,
					      ch->rdev, hdr, माप(*hdr)))
		वापस 0;
	kमुक्त(hdr);

	अगर (ret)
		riocm_error("send ACK to ch_%d on %s failed (ret=%d)",
			    ch->id, rio_name(ch->rdev), ret);
	वापस ret;
पूर्ण

/*
 * riocm_ch_accept - accept incoming connection request
 * @ch_id: channel ID
 * @new_ch_id: local mport device
 * @समयout: रुको समयout (अगर 0 non-blocking call, करो not रुको अगर connection
 *           request is not available).
 *
 * Returns: poपूर्णांकer to new channel काष्ठा अगर success, or error-valued poपूर्णांकer:
 *          -ENODEV - cannot find specअगरied channel or mport,
 *          -EINVAL - the channel is not in IDLE state,
 *          -EAGAIN - no connection request available immediately (समयout=0),
 *          -ENOMEM - unable to allocate new channel,
 *          -ETIME - रुको समयout expired,
 *          -EINTR - रुको was पूर्णांकerrupted.
 */
अटल काष्ठा rio_channel *riocm_ch_accept(u16 ch_id, u16 *new_ch_id,
					   दीर्घ समयout)
अणु
	काष्ठा rio_channel *ch;
	काष्ठा rio_channel *new_ch;
	काष्ठा conn_req *req;
	काष्ठा cm_peer *peer;
	पूर्णांक found = 0;
	पूर्णांक err = 0;
	दीर्घ wret;

	ch = riocm_get_channel(ch_id);
	अगर (!ch)
		वापस ERR_PTR(-EINVAL);

	अगर (!riocm_cmp(ch, RIO_CM_LISTEN)) अणु
		err = -EINVAL;
		जाओ err_put;
	पूर्ण

	/* Don't sleep अगर this is a non blocking call */
	अगर (!समयout) अणु
		अगर (!try_रुको_क्रम_completion(&ch->comp)) अणु
			err = -EAGAIN;
			जाओ err_put;
		पूर्ण
	पूर्ण अन्यथा अणु
		riocm_debug(WAIT, "on %d", ch->id);

		wret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ch->comp,
								 समयout);
		अगर (!wret) अणु
			err = -ETIME;
			जाओ err_put;
		पूर्ण अन्यथा अगर (wret == -ERESTARTSYS) अणु
			err = -EINTR;
			जाओ err_put;
		पूर्ण
	पूर्ण

	spin_lock_bh(&ch->lock);

	अगर (ch->state != RIO_CM_LISTEN) अणु
		err = -ECANCELED;
	पूर्ण अन्यथा अगर (list_empty(&ch->accept_queue)) अणु
		riocm_debug(WAIT, "on %d accept_queue is empty on completion",
			    ch->id);
		err = -EIO;
	पूर्ण

	spin_unlock_bh(&ch->lock);

	अगर (err) अणु
		riocm_debug(WAIT, "on %d returns %d", ch->id, err);
		जाओ err_put;
	पूर्ण

	/* Create new channel क्रम this connection */
	new_ch = riocm_ch_alloc(RIOCM_CHNUM_AUTO);

	अगर (IS_ERR(new_ch)) अणु
		riocm_error("failed to get channel for new req (%ld)",
			PTR_ERR(new_ch));
		err = -ENOMEM;
		जाओ err_put;
	पूर्ण

	spin_lock_bh(&ch->lock);

	req = list_first_entry(&ch->accept_queue, काष्ठा conn_req, node);
	list_del(&req->node);
	new_ch->cmdev = ch->cmdev;
	new_ch->loc_destid = ch->loc_destid;
	new_ch->rem_destid = req->destid;
	new_ch->rem_channel = req->chan;

	spin_unlock_bh(&ch->lock);
	riocm_put_channel(ch);
	ch = शून्य;
	kमुक्त(req);

	करोwn_पढ़ो(&rdev_sem);
	/* Find requester's device object */
	list_क्रम_each_entry(peer, &new_ch->cmdev->peers, node) अणु
		अगर (peer->rdev->destid == new_ch->rem_destid) अणु
			riocm_debug(RX_CMD, "found matching device(%s)",
				    rio_name(peer->rdev));
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&rdev_sem);

	अगर (!found) अणु
		/* If peer device object not found, simply ignore the request */
		err = -ENODEV;
		जाओ err_put_new_ch;
	पूर्ण

	new_ch->rdev = peer->rdev;
	new_ch->state = RIO_CM_CONNECTED;
	spin_lock_init(&new_ch->lock);

	/* Acknowledge the connection request. */
	riocm_send_ack(new_ch);

	*new_ch_id = new_ch->id;
	वापस new_ch;

err_put_new_ch:
	spin_lock_bh(&idr_lock);
	idr_हटाओ(&ch_idr, new_ch->id);
	spin_unlock_bh(&idr_lock);
	riocm_put_channel(new_ch);

err_put:
	अगर (ch)
		riocm_put_channel(ch);
	*new_ch_id = 0;
	वापस ERR_PTR(err);
पूर्ण

/*
 * riocm_ch_listen - माला_दो a channel पूर्णांकo LISTEN state
 * @ch_id: channel ID
 *
 * Returns: 0 अगर success, or
 *          -EINVAL अगर the specअगरied channel करोes not exists or
 *                  is not in CHAN_BOUND state.
 */
अटल पूर्णांक riocm_ch_listen(u16 ch_id)
अणु
	काष्ठा rio_channel *ch = शून्य;
	पूर्णांक ret = 0;

	riocm_debug(CHOP, "(ch_%d)", ch_id);

	ch = riocm_get_channel(ch_id);
	अगर (!ch)
		वापस -EINVAL;
	अगर (!riocm_cmp_exch(ch, RIO_CM_CHAN_BOUND, RIO_CM_LISTEN))
		ret = -EINVAL;
	riocm_put_channel(ch);
	वापस ret;
पूर्ण

/*
 * riocm_ch_bind - associate a channel object and an mport device
 * @ch_id: channel ID
 * @mport_id: local mport device ID
 * @context: poपूर्णांकer to the additional caller's context
 *
 * Returns: 0 अगर success, or
 *          -ENODEV अगर cannot find specअगरied mport,
 *          -EINVAL अगर the specअगरied channel करोes not exist or
 *                  is not in IDLE state.
 */
अटल पूर्णांक riocm_ch_bind(u16 ch_id, u8 mport_id, व्योम *context)
अणु
	काष्ठा rio_channel *ch = शून्य;
	काष्ठा cm_dev *cm;
	पूर्णांक rc = -ENODEV;

	riocm_debug(CHOP, "ch_%d to mport_%d", ch_id, mport_id);

	/* Find matching cm_dev object */
	करोwn_पढ़ो(&rdev_sem);
	list_क्रम_each_entry(cm, &cm_dev_list, list) अणु
		अगर ((cm->mport->id == mport_id) &&
		     rio_mport_is_running(cm->mport)) अणु
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rc)
		जाओ निकास;

	ch = riocm_get_channel(ch_id);
	अगर (!ch) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&ch->lock);
	अगर (ch->state != RIO_CM_IDLE) अणु
		spin_unlock_bh(&ch->lock);
		rc = -EINVAL;
		जाओ err_put;
	पूर्ण

	ch->cmdev = cm;
	ch->loc_destid = cm->mport->host_deviceid;
	ch->context = context;
	ch->state = RIO_CM_CHAN_BOUND;
	spin_unlock_bh(&ch->lock);
err_put:
	riocm_put_channel(ch);
निकास:
	up_पढ़ो(&rdev_sem);
	वापस rc;
पूर्ण

/*
 * riocm_ch_alloc - channel object allocation helper routine
 * @ch_num: channel ID (1 ... RIOCM_MAX_CHNUM, 0 = स्वतःmatic)
 *
 * Return value: poपूर्णांकer to newly created channel object,
 *               or error-valued poपूर्णांकer
 */
अटल काष्ठा rio_channel *riocm_ch_alloc(u16 ch_num)
अणु
	पूर्णांक id;
	पूर्णांक start, end;
	काष्ठा rio_channel *ch;

	ch = kzalloc(माप(*ch), GFP_KERNEL);
	अगर (!ch)
		वापस ERR_PTR(-ENOMEM);

	अगर (ch_num) अणु
		/* If requested, try to obtain the specअगरied channel ID */
		start = ch_num;
		end = ch_num + 1;
	पूर्ण अन्यथा अणु
		/* Obtain channel ID from the dynamic allocation range */
		start = chstart;
		end = RIOCM_MAX_CHNUM + 1;
	पूर्ण

	idr_preload(GFP_KERNEL);
	spin_lock_bh(&idr_lock);
	id = idr_alloc_cyclic(&ch_idr, ch, start, end, GFP_NOWAIT);
	spin_unlock_bh(&idr_lock);
	idr_preload_end();

	अगर (id < 0) अणु
		kमुक्त(ch);
		वापस ERR_PTR(id == -ENOSPC ? -EBUSY : id);
	पूर्ण

	ch->id = (u16)id;
	ch->state = RIO_CM_IDLE;
	spin_lock_init(&ch->lock);
	INIT_LIST_HEAD(&ch->accept_queue);
	INIT_LIST_HEAD(&ch->ch_node);
	init_completion(&ch->comp);
	init_completion(&ch->comp_बंद);
	kref_init(&ch->ref);
	ch->rx_ring.head = 0;
	ch->rx_ring.tail = 0;
	ch->rx_ring.count = 0;
	ch->rx_ring.inuse_cnt = 0;

	वापस ch;
पूर्ण

/*
 * riocm_ch_create - creates a new channel object and allocates ID क्रम it
 * @ch_num: channel ID (1 ... RIOCM_MAX_CHNUM, 0 = स्वतःmatic)
 *
 * Allocates and initializes a new channel object. If the parameter ch_num > 0
 * and is within the valid range, riocm_ch_create tries to allocate the
 * specअगरied ID क्रम the new channel. If ch_num = 0, channel ID will be asचिन्हित
 * स्वतःmatically from the range (chstart ... RIOCM_MAX_CHNUM).
 * Module parameter 'chstart' defines start of an ID range available क्रम dynamic
 * allocation. Range below 'chstart' is reserved क्रम pre-defined ID numbers.
 * Available channel numbers are limited by 16-bit size of channel numbers used
 * in the packet header.
 *
 * Return value: PTR to rio_channel काष्ठाure अगर successful (with channel number
 *               updated via poपूर्णांकer) or error-valued poपूर्णांकer अगर error.
 */
अटल काष्ठा rio_channel *riocm_ch_create(u16 *ch_num)
अणु
	काष्ठा rio_channel *ch = शून्य;

	ch = riocm_ch_alloc(*ch_num);

	अगर (IS_ERR(ch))
		riocm_debug(CHOP, "Failed to allocate channel %d (err=%ld)",
			    *ch_num, PTR_ERR(ch));
	अन्यथा
		*ch_num = ch->id;

	वापस ch;
पूर्ण

/*
 * riocm_ch_मुक्त - channel object release routine
 * @ref: poपूर्णांकer to a channel's kref काष्ठाure
 */
अटल व्योम riocm_ch_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा rio_channel *ch = container_of(ref, काष्ठा rio_channel, ref);
	पूर्णांक i;

	riocm_debug(CHOP, "(ch_%d)", ch->id);

	अगर (ch->rx_ring.inuse_cnt) अणु
		क्रम (i = 0;
		     i < RIOCM_RX_RING_SIZE && ch->rx_ring.inuse_cnt; i++) अणु
			अगर (ch->rx_ring.inuse[i] != शून्य) अणु
				kमुक्त(ch->rx_ring.inuse[i]);
				ch->rx_ring.inuse_cnt--;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ch->rx_ring.count)
		क्रम (i = 0; i < RIOCM_RX_RING_SIZE && ch->rx_ring.count; i++) अणु
			अगर (ch->rx_ring.buf[i] != शून्य) अणु
				kमुक्त(ch->rx_ring.buf[i]);
				ch->rx_ring.count--;
			पूर्ण
		पूर्ण

	complete(&ch->comp_बंद);
पूर्ण

अटल पूर्णांक riocm_send_बंद(काष्ठा rio_channel *ch)
अणु
	काष्ठा rio_ch_chan_hdr *hdr;
	पूर्णांक ret;

	/*
	 * Send CH_CLOSE notअगरication to the remote RapidIO device
	 */

	hdr = kzalloc(माप(*hdr), GFP_KERNEL);
	अगर (hdr == शून्य)
		वापस -ENOMEM;

	hdr->bhdr.src_id = htonl(ch->loc_destid);
	hdr->bhdr.dst_id = htonl(ch->rem_destid);
	hdr->bhdr.src_mbox = cmbox;
	hdr->bhdr.dst_mbox = cmbox;
	hdr->bhdr.type = RIO_CM_CHAN;
	hdr->ch_op = CM_CONN_CLOSE;
	hdr->dst_ch = htons(ch->rem_channel);
	hdr->src_ch = htons(ch->id);

	/* ATTN: the function call below relies on the fact that underlying
	 * add_outb_message() routine copies TX data पूर्णांकo its पूर्णांकernal transfer
	 * buffer. Needs to be reviewed अगर चयनed to direct buffer mode.
	 */
	ret = riocm_post_send(ch->cmdev, ch->rdev, hdr, माप(*hdr));

	अगर (ret == -EBUSY && !riocm_queue_req(ch->cmdev, ch->rdev,
					      hdr, माप(*hdr)))
		वापस 0;
	kमुक्त(hdr);

	अगर (ret)
		riocm_error("ch(%d) send CLOSE failed (ret=%d)", ch->id, ret);

	वापस ret;
पूर्ण

/*
 * riocm_ch_बंद - बंदs a channel object with specअगरied ID (by local request)
 * @ch: channel to be बंदd
 */
अटल पूर्णांक riocm_ch_बंद(काष्ठा rio_channel *ch)
अणु
	अचिन्हित दीर्घ पंचांगo = msecs_to_jअगरfies(3000);
	क्रमागत rio_cm_state state;
	दीर्घ wret;
	पूर्णांक ret = 0;

	riocm_debug(CHOP, "ch_%d by %s(%d)",
		    ch->id, current->comm, task_pid_nr(current));

	state = riocm_exch(ch, RIO_CM_DESTROYING);
	अगर (state == RIO_CM_CONNECTED)
		riocm_send_बंद(ch);

	complete_all(&ch->comp);

	riocm_put_channel(ch);
	wret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ch->comp_बंद, पंचांगo);

	riocm_debug(WAIT, "wait on %d returns %ld", ch->id, wret);

	अगर (wret == 0) अणु
		/* Timeout on रुको occurred */
		riocm_debug(CHOP, "%s(%d) timed out waiting for ch %d",
		       current->comm, task_pid_nr(current), ch->id);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (wret == -ERESTARTSYS) अणु
		/* Wait_क्रम_completion was पूर्णांकerrupted by a संकेत */
		riocm_debug(CHOP, "%s(%d) wait for ch %d was interrupted",
			current->comm, task_pid_nr(current), ch->id);
		ret = -EINTR;
	पूर्ण

	अगर (!ret) अणु
		riocm_debug(CHOP, "ch_%d resources released", ch->id);
		kमुक्त(ch);
	पूर्ण अन्यथा अणु
		riocm_debug(CHOP, "failed to release ch_%d resources", ch->id);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * riocm_cdev_खोलो() - Open अक्षरacter device
 */
अटल पूर्णांक riocm_cdev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	riocm_debug(INIT, "by %s(%d) filp=%p ",
		    current->comm, task_pid_nr(current), filp);

	अगर (list_empty(&cm_dev_list))
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * riocm_cdev_release() - Release अक्षरacter device
 */
अटल पूर्णांक riocm_cdev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rio_channel *ch, *_c;
	अचिन्हित पूर्णांक i;
	LIST_HEAD(list);

	riocm_debug(EXIT, "by %s(%d) filp=%p",
		    current->comm, task_pid_nr(current), filp);

	/* Check अगर there are channels associated with this file descriptor */
	spin_lock_bh(&idr_lock);
	idr_क्रम_each_entry(&ch_idr, ch, i) अणु
		अगर (ch && ch->filp == filp) अणु
			riocm_debug(EXIT, "ch_%d not released by %s(%d)",
				    ch->id, current->comm,
				    task_pid_nr(current));
			idr_हटाओ(&ch_idr, ch->id);
			list_add(&ch->ch_node, &list);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&idr_lock);

	अगर (!list_empty(&list)) अणु
		list_क्रम_each_entry_safe(ch, _c, &list, ch_node) अणु
			list_del(&ch->ch_node);
			riocm_ch_बंद(ch);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * cm_ep_get_list_size() - Reports number of endpoपूर्णांकs in the network
 */
अटल पूर्णांक cm_ep_get_list_size(व्योम __user *arg)
अणु
	u32 __user *p = arg;
	u32 mport_id;
	u32 count = 0;
	काष्ठा cm_dev *cm;

	अगर (get_user(mport_id, p))
		वापस -EFAULT;
	अगर (mport_id >= RIO_MAX_MPORTS)
		वापस -EINVAL;

	/* Find a matching cm_dev object */
	करोwn_पढ़ो(&rdev_sem);
	list_क्रम_each_entry(cm, &cm_dev_list, list) अणु
		अगर (cm->mport->id == mport_id) अणु
			count = cm->npeers;
			up_पढ़ो(&rdev_sem);
			अगर (copy_to_user(arg, &count, माप(u32)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
	पूर्ण
	up_पढ़ो(&rdev_sem);

	वापस -ENODEV;
पूर्ण

/*
 * cm_ep_get_list() - Returns list of attached endpoपूर्णांकs
 */
अटल पूर्णांक cm_ep_get_list(व्योम __user *arg)
अणु
	काष्ठा cm_dev *cm;
	काष्ठा cm_peer *peer;
	u32 info[2];
	व्योम *buf;
	u32 nent;
	u32 *entry_ptr;
	u32 i = 0;
	पूर्णांक ret = 0;

	अगर (copy_from_user(&info, arg, माप(info)))
		वापस -EFAULT;

	अगर (info[1] >= RIO_MAX_MPORTS || info[0] > RIOCM_MAX_EP_COUNT)
		वापस -EINVAL;

	/* Find a matching cm_dev object */
	करोwn_पढ़ो(&rdev_sem);
	list_क्रम_each_entry(cm, &cm_dev_list, list)
		अगर (cm->mport->id == (u8)info[1])
			जाओ found;

	up_पढ़ो(&rdev_sem);
	वापस -ENODEV;

found:
	nent = min(info[0], cm->npeers);
	buf = kसुस्मृति(nent + 2, माप(u32), GFP_KERNEL);
	अगर (!buf) अणु
		up_पढ़ो(&rdev_sem);
		वापस -ENOMEM;
	पूर्ण

	entry_ptr = (u32 *)((uपूर्णांकptr_t)buf + 2*माप(u32));

	list_क्रम_each_entry(peer, &cm->peers, node) अणु
		*entry_ptr = (u32)peer->rdev->destid;
		entry_ptr++;
		अगर (++i == nent)
			अवरोध;
	पूर्ण
	up_पढ़ो(&rdev_sem);

	((u32 *)buf)[0] = i; /* report an updated number of entries */
	((u32 *)buf)[1] = info[1]; /* put back an mport ID */
	अगर (copy_to_user(arg, buf, माप(u32) * (info[0] + 2)))
		ret = -EFAULT;

	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * cm_mport_get_list() - Returns list of available local mport devices
 */
अटल पूर्णांक cm_mport_get_list(व्योम __user *arg)
अणु
	पूर्णांक ret = 0;
	u32 entries;
	व्योम *buf;
	काष्ठा cm_dev *cm;
	u32 *entry_ptr;
	पूर्णांक count = 0;

	अगर (copy_from_user(&entries, arg, माप(entries)))
		वापस -EFAULT;
	अगर (entries == 0 || entries > RIO_MAX_MPORTS)
		वापस -EINVAL;
	buf = kसुस्मृति(entries + 1, माप(u32), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Scan all रेजिस्टरed cm_dev objects */
	entry_ptr = (u32 *)((uपूर्णांकptr_t)buf + माप(u32));
	करोwn_पढ़ो(&rdev_sem);
	list_क्रम_each_entry(cm, &cm_dev_list, list) अणु
		अगर (count++ < entries) अणु
			*entry_ptr = (cm->mport->id << 16) |
				      cm->mport->host_deviceid;
			entry_ptr++;
		पूर्ण
	पूर्ण
	up_पढ़ो(&rdev_sem);

	*((u32 *)buf) = count; /* report a real number of entries */
	अगर (copy_to_user(arg, buf, माप(u32) * (count + 1)))
		ret = -EFAULT;

	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * cm_chan_create() - Create a message exchange channel
 */
अटल पूर्णांक cm_chan_create(काष्ठा file *filp, व्योम __user *arg)
अणु
	u16 __user *p = arg;
	u16 ch_num;
	काष्ठा rio_channel *ch;

	अगर (get_user(ch_num, p))
		वापस -EFAULT;

	riocm_debug(CHOP, "ch_%d requested by %s(%d)",
		    ch_num, current->comm, task_pid_nr(current));
	ch = riocm_ch_create(&ch_num);
	अगर (IS_ERR(ch))
		वापस PTR_ERR(ch);

	ch->filp = filp;
	riocm_debug(CHOP, "ch_%d created by %s(%d)",
		    ch_num, current->comm, task_pid_nr(current));
	वापस put_user(ch_num, p);
पूर्ण

/*
 * cm_chan_बंद() - Close channel
 * @filp:	Poपूर्णांकer to file object
 * @arg:	Channel to बंद
 */
अटल पूर्णांक cm_chan_बंद(काष्ठा file *filp, व्योम __user *arg)
अणु
	u16 __user *p = arg;
	u16 ch_num;
	काष्ठा rio_channel *ch;

	अगर (get_user(ch_num, p))
		वापस -EFAULT;

	riocm_debug(CHOP, "ch_%d by %s(%d)",
		    ch_num, current->comm, task_pid_nr(current));

	spin_lock_bh(&idr_lock);
	ch = idr_find(&ch_idr, ch_num);
	अगर (!ch) अणु
		spin_unlock_bh(&idr_lock);
		वापस 0;
	पूर्ण
	अगर (ch->filp != filp) अणु
		spin_unlock_bh(&idr_lock);
		वापस -EINVAL;
	पूर्ण
	idr_हटाओ(&ch_idr, ch->id);
	spin_unlock_bh(&idr_lock);

	वापस riocm_ch_बंद(ch);
पूर्ण

/*
 * cm_chan_bind() - Bind channel
 * @arg:	Channel number
 */
अटल पूर्णांक cm_chan_bind(व्योम __user *arg)
अणु
	काष्ठा rio_cm_channel chan;

	अगर (copy_from_user(&chan, arg, माप(chan)))
		वापस -EFAULT;
	अगर (chan.mport_id >= RIO_MAX_MPORTS)
		वापस -EINVAL;

	वापस riocm_ch_bind(chan.id, chan.mport_id, शून्य);
पूर्ण

/*
 * cm_chan_listen() - Listen on channel
 * @arg:	Channel number
 */
अटल पूर्णांक cm_chan_listen(व्योम __user *arg)
अणु
	u16 __user *p = arg;
	u16 ch_num;

	अगर (get_user(ch_num, p))
		वापस -EFAULT;

	वापस riocm_ch_listen(ch_num);
पूर्ण

/*
 * cm_chan_accept() - Accept incoming connection
 * @filp:	Poपूर्णांकer to file object
 * @arg:	Channel number
 */
अटल पूर्णांक cm_chan_accept(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा rio_cm_accept param;
	दीर्घ accept_to;
	काष्ठा rio_channel *ch;

	अगर (copy_from_user(&param, arg, माप(param)))
		वापस -EFAULT;

	riocm_debug(CHOP, "on ch_%d by %s(%d)",
		    param.ch_num, current->comm, task_pid_nr(current));

	accept_to = param.रुको_to ?
			msecs_to_jअगरfies(param.रुको_to) : 0;

	ch = riocm_ch_accept(param.ch_num, &param.ch_num, accept_to);
	अगर (IS_ERR(ch))
		वापस PTR_ERR(ch);
	ch->filp = filp;

	riocm_debug(CHOP, "new ch_%d for %s(%d)",
		    ch->id, current->comm, task_pid_nr(current));

	अगर (copy_to_user(arg, &param, माप(param)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * cm_chan_connect() - Connect on channel
 * @arg:	Channel inक्रमmation
 */
अटल पूर्णांक cm_chan_connect(व्योम __user *arg)
अणु
	काष्ठा rio_cm_channel chan;
	काष्ठा cm_dev *cm;
	काष्ठा cm_peer *peer;
	पूर्णांक ret = -ENODEV;

	अगर (copy_from_user(&chan, arg, माप(chan)))
		वापस -EFAULT;
	अगर (chan.mport_id >= RIO_MAX_MPORTS)
		वापस -EINVAL;

	करोwn_पढ़ो(&rdev_sem);

	/* Find matching cm_dev object */
	list_क्रम_each_entry(cm, &cm_dev_list, list) अणु
		अगर (cm->mport->id == chan.mport_id) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		जाओ err_out;

	अगर (chan.remote_destid >= RIO_ANY_DESTID(cm->mport->sys_size)) अणु
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	/* Find corresponding RapidIO endpoपूर्णांक device object */
	ret = -ENODEV;

	list_क्रम_each_entry(peer, &cm->peers, node) अणु
		अगर (peer->rdev->destid == chan.remote_destid) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		जाओ err_out;

	up_पढ़ो(&rdev_sem);

	वापस riocm_ch_connect(chan.id, cm, peer, chan.remote_channel);
err_out:
	up_पढ़ो(&rdev_sem);
	वापस ret;
पूर्ण

/*
 * cm_chan_msg_send() - Send a message through channel
 * @arg:	Outbound message inक्रमmation
 */
अटल पूर्णांक cm_chan_msg_send(व्योम __user *arg)
अणु
	काष्ठा rio_cm_msg msg;
	व्योम *buf;
	पूर्णांक ret;

	अगर (copy_from_user(&msg, arg, माप(msg)))
		वापस -EFAULT;
	अगर (msg.size > RIO_MAX_MSG_SIZE)
		वापस -EINVAL;

	buf = memdup_user((व्योम __user *)(uपूर्णांकptr_t)msg.msg, msg.size);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	ret = riocm_ch_send(msg.ch_num, buf, msg.size);

	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * cm_chan_msg_rcv() - Receive a message through channel
 * @arg:	Inbound message inक्रमmation
 */
अटल पूर्णांक cm_chan_msg_rcv(व्योम __user *arg)
अणु
	काष्ठा rio_cm_msg msg;
	काष्ठा rio_channel *ch;
	व्योम *buf;
	दीर्घ rxto;
	पूर्णांक ret = 0, msg_size;

	अगर (copy_from_user(&msg, arg, माप(msg)))
		वापस -EFAULT;

	अगर (msg.ch_num == 0 || msg.size == 0)
		वापस -EINVAL;

	ch = riocm_get_channel(msg.ch_num);
	अगर (!ch)
		वापस -ENODEV;

	rxto = msg.rxto ? msecs_to_jअगरfies(msg.rxto) : MAX_SCHEDULE_TIMEOUT;

	ret = riocm_ch_receive(ch, &buf, rxto);
	अगर (ret)
		जाओ out;

	msg_size = min(msg.size, (u16)(RIO_MAX_MSG_SIZE));

	अगर (copy_to_user((व्योम __user *)(uपूर्णांकptr_t)msg.msg, buf, msg_size))
		ret = -EFAULT;

	riocm_ch_मुक्त_rxbuf(ch, buf);
out:
	riocm_put_channel(ch);
	वापस ret;
पूर्ण

/*
 * riocm_cdev_ioctl() - IOCTL requests handler
 */
अटल दीर्घ
riocm_cdev_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल RIO_CM_EP_GET_LIST_SIZE:
		वापस cm_ep_get_list_size((व्योम __user *)arg);
	हाल RIO_CM_EP_GET_LIST:
		वापस cm_ep_get_list((व्योम __user *)arg);
	हाल RIO_CM_CHAN_CREATE:
		वापस cm_chan_create(filp, (व्योम __user *)arg);
	हाल RIO_CM_CHAN_CLOSE:
		वापस cm_chan_बंद(filp, (व्योम __user *)arg);
	हाल RIO_CM_CHAN_BIND:
		वापस cm_chan_bind((व्योम __user *)arg);
	हाल RIO_CM_CHAN_LISTEN:
		वापस cm_chan_listen((व्योम __user *)arg);
	हाल RIO_CM_CHAN_ACCEPT:
		वापस cm_chan_accept(filp, (व्योम __user *)arg);
	हाल RIO_CM_CHAN_CONNECT:
		वापस cm_chan_connect((व्योम __user *)arg);
	हाल RIO_CM_CHAN_SEND:
		वापस cm_chan_msg_send((व्योम __user *)arg);
	हाल RIO_CM_CHAN_RECEIVE:
		वापस cm_chan_msg_rcv((व्योम __user *)arg);
	हाल RIO_CM_MPORT_GET_LIST:
		वापस cm_mport_get_list((व्योम __user *)arg);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा file_operations riocm_cdev_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= riocm_cdev_खोलो,
	.release	= riocm_cdev_release,
	.unlocked_ioctl = riocm_cdev_ioctl,
पूर्ण;

/*
 * riocm_add_dev - add new remote RapidIO device पूर्णांकo channel management core
 * @dev: device object associated with RapidIO device
 * @sअगर: subप्रणाली पूर्णांकerface
 *
 * Adds the specअगरied RapidIO device (अगर applicable) पूर्णांकo peers list of
 * the corresponding channel management device (cm_dev).
 */
अटल पूर्णांक riocm_add_dev(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	काष्ठा cm_peer *peer;
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	काष्ठा cm_dev *cm;

	/* Check अगर the remote device has capabilities required to support CM */
	अगर (!dev_cm_capable(rdev))
		वापस 0;

	riocm_debug(RDEV, "(%s)", rio_name(rdev));

	peer = kदो_स्मृति(माप(*peer), GFP_KERNEL);
	अगर (!peer)
		वापस -ENOMEM;

	/* Find a corresponding cm_dev object */
	करोwn_ग_लिखो(&rdev_sem);
	list_क्रम_each_entry(cm, &cm_dev_list, list) अणु
		अगर (cm->mport == rdev->net->hport)
			जाओ found;
	पूर्ण

	up_ग_लिखो(&rdev_sem);
	kमुक्त(peer);
	वापस -ENODEV;

found:
	peer->rdev = rdev;
	list_add_tail(&peer->node, &cm->peers);
	cm->npeers++;

	up_ग_लिखो(&rdev_sem);
	वापस 0;
पूर्ण

/*
 * riocm_हटाओ_dev - हटाओ remote RapidIO device from channel management core
 * @dev: device object associated with RapidIO device
 * @sअगर: subप्रणाली पूर्णांकerface
 *
 * Removes the specअगरied RapidIO device (अगर applicable) from peers list of
 * the corresponding channel management device (cm_dev).
 */
अटल व्योम riocm_हटाओ_dev(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	काष्ठा cm_dev *cm;
	काष्ठा cm_peer *peer;
	काष्ठा rio_channel *ch, *_c;
	अचिन्हित पूर्णांक i;
	bool found = false;
	LIST_HEAD(list);

	/* Check अगर the remote device has capabilities required to support CM */
	अगर (!dev_cm_capable(rdev))
		वापस;

	riocm_debug(RDEV, "(%s)", rio_name(rdev));

	/* Find matching cm_dev object */
	करोwn_ग_लिखो(&rdev_sem);
	list_क्रम_each_entry(cm, &cm_dev_list, list) अणु
		अगर (cm->mport == rdev->net->hport) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		up_ग_लिखो(&rdev_sem);
		वापस;
	पूर्ण

	/* Remove remote device from the list of peers */
	found = false;
	list_क्रम_each_entry(peer, &cm->peers, node) अणु
		अगर (peer->rdev == rdev) अणु
			riocm_debug(RDEV, "removing peer %s", rio_name(rdev));
			found = true;
			list_del(&peer->node);
			cm->npeers--;
			kमुक्त(peer);
			अवरोध;
		पूर्ण
	पूर्ण

	up_ग_लिखो(&rdev_sem);

	अगर (!found)
		वापस;

	/*
	 * Release channels associated with this peer
	 */

	spin_lock_bh(&idr_lock);
	idr_क्रम_each_entry(&ch_idr, ch, i) अणु
		अगर (ch && ch->rdev == rdev) अणु
			अगर (atomic_पढ़ो(&rdev->state) != RIO_DEVICE_SHUTDOWN)
				riocm_exch(ch, RIO_CM_DISCONNECT);
			idr_हटाओ(&ch_idr, ch->id);
			list_add(&ch->ch_node, &list);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&idr_lock);

	अगर (!list_empty(&list)) अणु
		list_क्रम_each_entry_safe(ch, _c, &list, ch_node) अणु
			list_del(&ch->ch_node);
			riocm_ch_बंद(ch);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * riocm_cdev_add() - Create rio_cm अक्षर device
 * @devno: device number asचिन्हित to device (MAJ + MIN)
 */
अटल पूर्णांक riocm_cdev_add(dev_t devno)
अणु
	पूर्णांक ret;

	cdev_init(&riocm_cdev.cdev, &riocm_cdev_fops);
	riocm_cdev.cdev.owner = THIS_MODULE;
	ret = cdev_add(&riocm_cdev.cdev, devno, 1);
	अगर (ret < 0) अणु
		riocm_error("Cannot register a device with error %d", ret);
		वापस ret;
	पूर्ण

	riocm_cdev.dev = device_create(dev_class, शून्य, devno, शून्य, DEV_NAME);
	अगर (IS_ERR(riocm_cdev.dev)) अणु
		cdev_del(&riocm_cdev.cdev);
		वापस PTR_ERR(riocm_cdev.dev);
	पूर्ण

	riocm_debug(MPORT, "Added %s cdev(%d:%d)",
		    DEV_NAME, MAJOR(devno), MINOR(devno));

	वापस 0;
पूर्ण

/*
 * riocm_add_mport - add new local mport device पूर्णांकo channel management core
 * @dev: device object associated with mport
 * @class_पूर्णांकf: class पूर्णांकerface
 *
 * When a new mport device is added, CM immediately reserves inbound and
 * outbound RapidIO mailboxes that will be used.
 */
अटल पूर्णांक riocm_add_mport(काष्ठा device *dev,
			   काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	पूर्णांक rc;
	पूर्णांक i;
	काष्ठा cm_dev *cm;
	काष्ठा rio_mport *mport = to_rio_mport(dev);

	riocm_debug(MPORT, "add mport %s", mport->name);

	cm = kzalloc(माप(*cm), GFP_KERNEL);
	अगर (!cm)
		वापस -ENOMEM;

	cm->mport = mport;

	rc = rio_request_outb_mbox(mport, cm, cmbox,
				   RIOCM_TX_RING_SIZE, riocm_outb_msg_event);
	अगर (rc) अणु
		riocm_error("failed to allocate OBMBOX_%d on %s",
			    cmbox, mport->name);
		kमुक्त(cm);
		वापस -ENODEV;
	पूर्ण

	rc = rio_request_inb_mbox(mport, cm, cmbox,
				  RIOCM_RX_RING_SIZE, riocm_inb_msg_event);
	अगर (rc) अणु
		riocm_error("failed to allocate IBMBOX_%d on %s",
			    cmbox, mport->name);
		rio_release_outb_mbox(mport, cmbox);
		kमुक्त(cm);
		वापस -ENODEV;
	पूर्ण

	cm->rx_wq = create_workqueue(DRV_NAME "/rxq");
	अगर (!cm->rx_wq) अणु
		rio_release_inb_mbox(mport, cmbox);
		rio_release_outb_mbox(mport, cmbox);
		kमुक्त(cm);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Allocate and रेजिस्टर inbound messaging buffers to be पढ़ोy
	 * to receive channel and प्रणाली management requests
	 */
	क्रम (i = 0; i < RIOCM_RX_RING_SIZE; i++)
		cm->rx_buf[i] = शून्य;

	cm->rx_slots = RIOCM_RX_RING_SIZE;
	mutex_init(&cm->rx_lock);
	riocm_rx_fill(cm, RIOCM_RX_RING_SIZE);
	INIT_WORK(&cm->rx_work, rio_ibmsg_handler);

	cm->tx_slot = 0;
	cm->tx_cnt = 0;
	cm->tx_ack_slot = 0;
	spin_lock_init(&cm->tx_lock);

	INIT_LIST_HEAD(&cm->peers);
	cm->npeers = 0;
	INIT_LIST_HEAD(&cm->tx_reqs);

	करोwn_ग_लिखो(&rdev_sem);
	list_add_tail(&cm->list, &cm_dev_list);
	up_ग_लिखो(&rdev_sem);

	वापस 0;
पूर्ण

/*
 * riocm_हटाओ_mport - हटाओ local mport device from channel management core
 * @dev: device object associated with mport
 * @class_पूर्णांकf: class पूर्णांकerface
 *
 * Removes a local mport device from the list of रेजिस्टरed devices that provide
 * channel management services. Returns an error अगर the specअगरied mport is not
 * रेजिस्टरed with the CM core.
 */
अटल व्योम riocm_हटाओ_mport(काष्ठा device *dev,
			       काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा rio_mport *mport = to_rio_mport(dev);
	काष्ठा cm_dev *cm;
	काष्ठा cm_peer *peer, *temp;
	काष्ठा rio_channel *ch, *_c;
	अचिन्हित पूर्णांक i;
	bool found = false;
	LIST_HEAD(list);

	riocm_debug(MPORT, "%s", mport->name);

	/* Find a matching cm_dev object */
	करोwn_ग_लिखो(&rdev_sem);
	list_क्रम_each_entry(cm, &cm_dev_list, list) अणु
		अगर (cm->mport == mport) अणु
			list_del(&cm->list);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&rdev_sem);
	अगर (!found)
		वापस;

	flush_workqueue(cm->rx_wq);
	destroy_workqueue(cm->rx_wq);

	/* Release channels bound to this mport */
	spin_lock_bh(&idr_lock);
	idr_क्रम_each_entry(&ch_idr, ch, i) अणु
		अगर (ch->cmdev == cm) अणु
			riocm_debug(RDEV, "%s drop ch_%d",
				    mport->name, ch->id);
			idr_हटाओ(&ch_idr, ch->id);
			list_add(&ch->ch_node, &list);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&idr_lock);

	अगर (!list_empty(&list)) अणु
		list_क्रम_each_entry_safe(ch, _c, &list, ch_node) अणु
			list_del(&ch->ch_node);
			riocm_ch_बंद(ch);
		पूर्ण
	पूर्ण

	rio_release_inb_mbox(mport, cmbox);
	rio_release_outb_mbox(mport, cmbox);

	/* Remove and मुक्त peer entries */
	अगर (!list_empty(&cm->peers))
		riocm_debug(RDEV, "ATTN: peer list not empty");
	list_क्रम_each_entry_safe(peer, temp, &cm->peers, node) अणु
		riocm_debug(RDEV, "removing peer %s", rio_name(peer->rdev));
		list_del(&peer->node);
		kमुक्त(peer);
	पूर्ण

	riocm_rx_मुक्त(cm);
	kमुक्त(cm);
	riocm_debug(MPORT, "%s done", mport->name);
पूर्ण

अटल पूर्णांक rio_cm_shutकरोwn(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ code,
	व्योम *unused)
अणु
	काष्ठा rio_channel *ch;
	अचिन्हित पूर्णांक i;
	LIST_HEAD(list);

	riocm_debug(EXIT, ".");

	/*
	 * If there are any channels left in connected state send
	 * बंद notअगरication to the connection partner.
	 * First build a list of channels that require a closing
	 * notअगरication because function riocm_send_बंद() should
	 * be called outside of spinlock रक्षित code.
	 */
	spin_lock_bh(&idr_lock);
	idr_क्रम_each_entry(&ch_idr, ch, i) अणु
		अगर (ch->state == RIO_CM_CONNECTED) अणु
			riocm_debug(EXIT, "close ch %d", ch->id);
			idr_हटाओ(&ch_idr, ch->id);
			list_add(&ch->ch_node, &list);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&idr_lock);

	list_क्रम_each_entry(ch, &list, ch_node)
		riocm_send_बंद(ch);

	वापस NOTIFY_DONE;
पूर्ण

/*
 * riocm_पूर्णांकerface handles addition/removal of remote RapidIO devices
 */
अटल काष्ठा subsys_पूर्णांकerface riocm_पूर्णांकerface = अणु
	.name		= "rio_cm",
	.subsys		= &rio_bus_type,
	.add_dev	= riocm_add_dev,
	.हटाओ_dev	= riocm_हटाओ_dev,
पूर्ण;

/*
 * rio_mport_पूर्णांकerface handles addition/removal local mport devices
 */
अटल काष्ठा class_पूर्णांकerface rio_mport_पूर्णांकerface __refdata = अणु
	.class = &rio_mport_class,
	.add_dev = riocm_add_mport,
	.हटाओ_dev = riocm_हटाओ_mport,
पूर्ण;

अटल काष्ठा notअगरier_block rio_cm_notअगरier = अणु
	.notअगरier_call = rio_cm_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init riocm_init(व्योम)
अणु
	पूर्णांक ret;

	/* Create device class needed by udev */
	dev_class = class_create(THIS_MODULE, DRV_NAME);
	अगर (IS_ERR(dev_class)) अणु
		riocm_error("Cannot create " DRV_NAME " class");
		वापस PTR_ERR(dev_class);
	पूर्ण

	ret = alloc_chrdev_region(&dev_number, 0, 1, DRV_NAME);
	अगर (ret) अणु
		class_destroy(dev_class);
		वापस ret;
	पूर्ण

	dev_major = MAJOR(dev_number);
	dev_minor_base = MINOR(dev_number);
	riocm_debug(INIT, "Registered class with %d major", dev_major);

	/*
	 * Register as rapidio_port class पूर्णांकerface to get notअगरications about
	 * mport additions and removals.
	 */
	ret = class_पूर्णांकerface_रेजिस्टर(&rio_mport_पूर्णांकerface);
	अगर (ret) अणु
		riocm_error("class_interface_register error: %d", ret);
		जाओ err_reg;
	पूर्ण

	/*
	 * Register as RapidIO bus पूर्णांकerface to get notअगरications about
	 * addition/removal of remote RapidIO devices.
	 */
	ret = subsys_पूर्णांकerface_रेजिस्टर(&riocm_पूर्णांकerface);
	अगर (ret) अणु
		riocm_error("subsys_interface_register error: %d", ret);
		जाओ err_cl;
	पूर्ण

	ret = रेजिस्टर_reboot_notअगरier(&rio_cm_notअगरier);
	अगर (ret) अणु
		riocm_error("failed to register reboot notifier (err=%d)", ret);
		जाओ err_sअगर;
	पूर्ण

	ret = riocm_cdev_add(dev_number);
	अगर (ret) अणु
		unरेजिस्टर_reboot_notअगरier(&rio_cm_notअगरier);
		ret = -ENODEV;
		जाओ err_sअगर;
	पूर्ण

	वापस 0;
err_sअगर:
	subsys_पूर्णांकerface_unरेजिस्टर(&riocm_पूर्णांकerface);
err_cl:
	class_पूर्णांकerface_unरेजिस्टर(&rio_mport_पूर्णांकerface);
err_reg:
	unरेजिस्टर_chrdev_region(dev_number, 1);
	class_destroy(dev_class);
	वापस ret;
पूर्ण

अटल व्योम __निकास riocm_निकास(व्योम)
अणु
	riocm_debug(EXIT, "enter");
	unरेजिस्टर_reboot_notअगरier(&rio_cm_notअगरier);
	subsys_पूर्णांकerface_unरेजिस्टर(&riocm_पूर्णांकerface);
	class_पूर्णांकerface_unरेजिस्टर(&rio_mport_पूर्णांकerface);
	idr_destroy(&ch_idr);

	device_unरेजिस्टर(riocm_cdev.dev);
	cdev_del(&(riocm_cdev.cdev));

	class_destroy(dev_class);
	unरेजिस्टर_chrdev_region(dev_number, 1);
पूर्ण

late_initcall(riocm_init);
module_निकास(riocm_निकास);
