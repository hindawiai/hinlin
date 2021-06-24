<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, Sony Mobile Communications AB.
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <linux/रुको.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/rpmsg/qcom_smd.h>

#समावेश "rpmsg_internal.h"

/*
 * The Qualcomm Shared Memory communication solution provides poपूर्णांक-to-poपूर्णांक
 * channels क्रम clients to send and receive streaming or packet based data.
 *
 * Each channel consists of a control item (channel info) and a ring buffer
 * pair. The channel info carry inक्रमmation related to channel state, flow
 * control and the offsets within the ring buffer.
 *
 * All allocated channels are listed in an allocation table, identअगरying the
 * pair of items by name, type and remote processor.
 *
 * Upon creating a new channel the remote processor allocates channel info and
 * ring buffer items from the smem heap and populate the allocation table. An
 * पूर्णांकerrupt is sent to the other end of the channel and a scan क्रम new
 * channels should be करोne. A channel never goes away, it will only change
 * state.
 *
 * The remote processor संकेतs it पूर्णांकent क्रम bring up the communication
 * channel by setting the state of its end of the channel to "opening" and
 * sends out an पूर्णांकerrupt. We detect this change and रेजिस्टर a smd device to
 * consume the channel. Upon finding a consumer we finish the handshake and the
 * channel is up.
 *
 * Upon closing a channel, the remote processor will update the state of its
 * end of the channel and संकेत us, we will then unरेजिस्टर any attached
 * device and बंद our end of the channel.
 *
 * Devices attached to a channel can use the qcom_smd_send function to push
 * data to the channel, this is करोne by copying the data पूर्णांकo the tx ring
 * buffer, updating the poपूर्णांकers in the channel info and संकेतing the remote
 * processor.
 *
 * The remote processor करोes the equivalent when it transfer data and upon
 * receiving the पूर्णांकerrupt we check the channel info क्रम new data and delivers
 * this to the attached device. If the device is not पढ़ोy to receive the data
 * we leave it in the ring buffer क्रम now.
 */

काष्ठा smd_channel_info;
काष्ठा smd_channel_info_pair;
काष्ठा smd_channel_info_word;
काष्ठा smd_channel_info_word_pair;

अटल स्थिर काष्ठा rpmsg_endpoपूर्णांक_ops qcom_smd_endpoपूर्णांक_ops;

#घोषणा SMD_ALLOC_TBL_COUNT	2
#घोषणा SMD_ALLOC_TBL_SIZE	64

/*
 * This lists the various smem heap items relevant क्रम the allocation table and
 * smd channel entries.
 */
अटल स्थिर काष्ठा अणु
	अचिन्हित alloc_tbl_id;
	अचिन्हित info_base_id;
	अचिन्हित fअगरo_base_id;
पूर्ण smem_items[SMD_ALLOC_TBL_COUNT] = अणु
	अणु
		.alloc_tbl_id = 13,
		.info_base_id = 14,
		.fअगरo_base_id = 338
	पूर्ण,
	अणु
		.alloc_tbl_id = 266,
		.info_base_id = 138,
		.fअगरo_base_id = 202,
	पूर्ण,
पूर्ण;

/**
 * काष्ठा qcom_smd_edge - representing a remote processor
 * @dev:		device associated with this edge
 * @name:		name of this edge
 * @of_node:		of_node handle क्रम inक्रमmation related to this edge
 * @edge_id:		identअगरier of this edge
 * @remote_pid:		identअगरier of remote processor
 * @irq:		पूर्णांकerrupt क्रम संकेतs on this edge
 * @ipc_regmap:		regmap handle holding the outgoing ipc रेजिस्टर
 * @ipc_offset:		offset within @ipc_regmap of the रेजिस्टर क्रम ipc
 * @ipc_bit:		bit in the रेजिस्टर at @ipc_offset of @ipc_regmap
 * @mbox_client:	mailbox client handle
 * @mbox_chan:		apcs ipc mailbox channel handle
 * @channels:		list of all channels detected on this edge
 * @channels_lock:	guard क्रम modअगरications of @channels
 * @allocated:		array of biपंचांगaps representing alपढ़ोy allocated channels
 * @smem_available:	last available amount of smem triggering a channel scan
 * @new_channel_event:	रुको queue क्रम new channel events
 * @scan_work:		work item क्रम discovering new channels
 * @state_work:		work item क्रम edge state changes
 */
काष्ठा qcom_smd_edge अणु
	काष्ठा device dev;

	स्थिर अक्षर *name;

	काष्ठा device_node *of_node;
	अचिन्हित edge_id;
	अचिन्हित remote_pid;

	पूर्णांक irq;

	काष्ठा regmap *ipc_regmap;
	पूर्णांक ipc_offset;
	पूर्णांक ipc_bit;

	काष्ठा mbox_client mbox_client;
	काष्ठा mbox_chan *mbox_chan;

	काष्ठा list_head channels;
	spinlock_t channels_lock;

	DECLARE_BITMAP(allocated[SMD_ALLOC_TBL_COUNT], SMD_ALLOC_TBL_SIZE);

	अचिन्हित smem_available;

	रुको_queue_head_t new_channel_event;

	काष्ठा work_काष्ठा scan_work;
	काष्ठा work_काष्ठा state_work;
पूर्ण;

/*
 * SMD channel states.
 */
क्रमागत smd_channel_state अणु
	SMD_CHANNEL_CLOSED,
	SMD_CHANNEL_OPENING,
	SMD_CHANNEL_OPENED,
	SMD_CHANNEL_FLUSHING,
	SMD_CHANNEL_CLOSING,
	SMD_CHANNEL_RESET,
	SMD_CHANNEL_RESET_OPENING
पूर्ण;

काष्ठा qcom_smd_device अणु
	काष्ठा rpmsg_device rpdev;

	काष्ठा qcom_smd_edge *edge;
पूर्ण;

काष्ठा qcom_smd_endpoपूर्णांक अणु
	काष्ठा rpmsg_endpoपूर्णांक ept;

	काष्ठा qcom_smd_channel *qsch;
पूर्ण;

#घोषणा to_smd_device(r)	container_of(r, काष्ठा qcom_smd_device, rpdev)
#घोषणा to_smd_edge(d)		container_of(d, काष्ठा qcom_smd_edge, dev)
#घोषणा to_smd_endpoपूर्णांक(e)	container_of(e, काष्ठा qcom_smd_endpoपूर्णांक, ept)

/**
 * काष्ठा qcom_smd_channel - smd channel काष्ठा
 * @edge:		qcom_smd_edge this channel is living on
 * @qsept:		reference to a associated smd endpoपूर्णांक
 * @रेजिस्टरed:		flag to indicate अगर the channel is रेजिस्टरed
 * @name:		name of the channel
 * @state:		local state of the channel
 * @remote_state:	remote state of the channel
 * @state_change_event:	state change event
 * @info:		byte aligned outgoing/incoming channel info
 * @info_word:		word aligned outgoing/incoming channel info
 * @tx_lock:		lock to make ग_लिखोs to the channel mutually exclusive
 * @fblockपढ़ो_event:	wakeup event tied to tx fBLOCKREADINTR
 * @tx_fअगरo:		poपूर्णांकer to the outgoing ring buffer
 * @rx_fअगरo:		poपूर्णांकer to the incoming ring buffer
 * @fअगरo_size:		size of each ring buffer
 * @bounce_buffer:	bounce buffer क्रम पढ़ोing wrapped packets
 * @cb:			callback function रेजिस्टरed क्रम this channel
 * @recv_lock:		guard क्रम rx info modअगरications and cb poपूर्णांकer
 * @pkt_size:		size of the currently handled packet
 * @drvdata:		driver निजी data
 * @list:		lite entry क्रम @channels in qcom_smd_edge
 */
काष्ठा qcom_smd_channel अणु
	काष्ठा qcom_smd_edge *edge;

	काष्ठा qcom_smd_endpoपूर्णांक *qsept;
	bool रेजिस्टरed;

	अक्षर *name;
	क्रमागत smd_channel_state state;
	क्रमागत smd_channel_state remote_state;
	रुको_queue_head_t state_change_event;

	काष्ठा smd_channel_info_pair *info;
	काष्ठा smd_channel_info_word_pair *info_word;

	spinlock_t tx_lock;
	रुको_queue_head_t fblockपढ़ो_event;

	व्योम *tx_fअगरo;
	व्योम *rx_fअगरo;
	पूर्णांक fअगरo_size;

	व्योम *bounce_buffer;

	spinlock_t recv_lock;

	पूर्णांक pkt_size;

	व्योम *drvdata;

	काष्ठा list_head list;
पूर्ण;

/*
 * Format of the smd_info smem items, क्रम byte aligned channels.
 */
काष्ठा smd_channel_info अणु
	__le32 state;
	u8  fDSR;
	u8  fCTS;
	u8  fCD;
	u8  fRI;
	u8  fHEAD;
	u8  fTAIL;
	u8  fSTATE;
	u8  fBLOCKREADINTR;
	__le32 tail;
	__le32 head;
पूर्ण;

काष्ठा smd_channel_info_pair अणु
	काष्ठा smd_channel_info tx;
	काष्ठा smd_channel_info rx;
पूर्ण;

/*
 * Format of the smd_info smem items, क्रम word aligned channels.
 */
काष्ठा smd_channel_info_word अणु
	__le32 state;
	__le32 fDSR;
	__le32 fCTS;
	__le32 fCD;
	__le32 fRI;
	__le32 fHEAD;
	__le32 fTAIL;
	__le32 fSTATE;
	__le32 fBLOCKREADINTR;
	__le32 tail;
	__le32 head;
पूर्ण;

काष्ठा smd_channel_info_word_pair अणु
	काष्ठा smd_channel_info_word tx;
	काष्ठा smd_channel_info_word rx;
पूर्ण;

#घोषणा GET_RX_CHANNEL_FLAG(channel, param)				     \
	(अणु								     \
		BUILD_BUG_ON(माप(channel->info->rx.param) != माप(u8)); \
		channel->info_word ?					     \
			le32_to_cpu(channel->info_word->rx.param) :	     \
			channel->info->rx.param;			     \
	पूर्ण)

#घोषणा GET_RX_CHANNEL_INFO(channel, param)				      \
	(अणु								      \
		BUILD_BUG_ON(माप(channel->info->rx.param) != माप(u32)); \
		le32_to_cpu(channel->info_word ?			      \
			channel->info_word->rx.param :			      \
			channel->info->rx.param);			      \
	पूर्ण)

#घोषणा SET_RX_CHANNEL_FLAG(channel, param, value)			     \
	(अणु								     \
		BUILD_BUG_ON(माप(channel->info->rx.param) != माप(u8)); \
		अगर (channel->info_word)					     \
			channel->info_word->rx.param = cpu_to_le32(value);   \
		अन्यथा							     \
			channel->info->rx.param = value;		     \
	पूर्ण)

#घोषणा SET_RX_CHANNEL_INFO(channel, param, value)			      \
	(अणु								      \
		BUILD_BUG_ON(माप(channel->info->rx.param) != माप(u32)); \
		अगर (channel->info_word)					      \
			channel->info_word->rx.param = cpu_to_le32(value);    \
		अन्यथा							      \
			channel->info->rx.param = cpu_to_le32(value);	      \
	पूर्ण)

#घोषणा GET_TX_CHANNEL_FLAG(channel, param)				     \
	(अणु								     \
		BUILD_BUG_ON(माप(channel->info->tx.param) != माप(u8)); \
		channel->info_word ?					     \
			le32_to_cpu(channel->info_word->tx.param) :          \
			channel->info->tx.param;			     \
	पूर्ण)

#घोषणा GET_TX_CHANNEL_INFO(channel, param)				      \
	(अणु								      \
		BUILD_BUG_ON(माप(channel->info->tx.param) != माप(u32)); \
		le32_to_cpu(channel->info_word ?			      \
			channel->info_word->tx.param :			      \
			channel->info->tx.param);			      \
	पूर्ण)

#घोषणा SET_TX_CHANNEL_FLAG(channel, param, value)			     \
	(अणु								     \
		BUILD_BUG_ON(माप(channel->info->tx.param) != माप(u8)); \
		अगर (channel->info_word)					     \
			channel->info_word->tx.param = cpu_to_le32(value);   \
		अन्यथा							     \
			channel->info->tx.param = value;		     \
	पूर्ण)

#घोषणा SET_TX_CHANNEL_INFO(channel, param, value)			      \
	(अणु								      \
		BUILD_BUG_ON(माप(channel->info->tx.param) != माप(u32)); \
		अगर (channel->info_word)					      \
			channel->info_word->tx.param = cpu_to_le32(value);   \
		अन्यथा							      \
			channel->info->tx.param = cpu_to_le32(value);	      \
	पूर्ण)

/**
 * काष्ठा qcom_smd_alloc_entry - channel allocation entry
 * @name:	channel name
 * @cid:	channel index
 * @flags:	channel flags and edge id
 * @ref_count:	reference count of the channel
 */
काष्ठा qcom_smd_alloc_entry अणु
	u8 name[20];
	__le32 cid;
	__le32 flags;
	__le32 ref_count;
पूर्ण __packed;

#घोषणा SMD_CHANNEL_FLAGS_EDGE_MASK	0xff
#घोषणा SMD_CHANNEL_FLAGS_STREAM	BIT(8)
#घोषणा SMD_CHANNEL_FLAGS_PACKET	BIT(9)

/*
 * Each smd packet contains a 20 byte header, with the first 4 being the length
 * of the packet.
 */
#घोषणा SMD_PACKET_HEADER_LEN	20

/*
 * Signal the remote processor associated with 'channel'.
 */
अटल व्योम qcom_smd_संकेत_channel(काष्ठा qcom_smd_channel *channel)
अणु
	काष्ठा qcom_smd_edge *edge = channel->edge;

	अगर (edge->mbox_chan) अणु
		/*
		 * We can ignore a failing mbox_send_message() as the only
		 * possible cause is that the FIFO in the framework is full of
		 * other ग_लिखोs to the same bit.
		 */
		mbox_send_message(edge->mbox_chan, शून्य);
		mbox_client_txकरोne(edge->mbox_chan, 0);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(edge->ipc_regmap, edge->ipc_offset, BIT(edge->ipc_bit));
	पूर्ण
पूर्ण

/*
 * Initialize the tx channel info
 */
अटल व्योम qcom_smd_channel_reset(काष्ठा qcom_smd_channel *channel)
अणु
	SET_TX_CHANNEL_INFO(channel, state, SMD_CHANNEL_CLOSED);
	SET_TX_CHANNEL_FLAG(channel, fDSR, 0);
	SET_TX_CHANNEL_FLAG(channel, fCTS, 0);
	SET_TX_CHANNEL_FLAG(channel, fCD, 0);
	SET_TX_CHANNEL_FLAG(channel, fRI, 0);
	SET_TX_CHANNEL_FLAG(channel, fHEAD, 0);
	SET_TX_CHANNEL_FLAG(channel, fTAIL, 0);
	SET_TX_CHANNEL_FLAG(channel, fSTATE, 1);
	SET_TX_CHANNEL_FLAG(channel, fBLOCKREADINTR, 1);
	SET_TX_CHANNEL_INFO(channel, head, 0);
	SET_RX_CHANNEL_INFO(channel, tail, 0);

	qcom_smd_संकेत_channel(channel);

	channel->state = SMD_CHANNEL_CLOSED;
	channel->pkt_size = 0;
पूर्ण

/*
 * Set the callback क्रम a channel, with appropriate locking
 */
अटल व्योम qcom_smd_channel_set_callback(काष्ठा qcom_smd_channel *channel,
					  rpmsg_rx_cb_t cb)
अणु
	काष्ठा rpmsg_endpoपूर्णांक *ept = &channel->qsept->ept;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&channel->recv_lock, flags);
	ept->cb = cb;
	spin_unlock_irqrestore(&channel->recv_lock, flags);
पूर्ण;

/*
 * Calculate the amount of data available in the rx fअगरo
 */
अटल माप_प्रकार qcom_smd_channel_get_rx_avail(काष्ठा qcom_smd_channel *channel)
अणु
	अचिन्हित head;
	अचिन्हित tail;

	head = GET_RX_CHANNEL_INFO(channel, head);
	tail = GET_RX_CHANNEL_INFO(channel, tail);

	वापस (head - tail) & (channel->fअगरo_size - 1);
पूर्ण

/*
 * Set tx channel state and inक्रमm the remote processor
 */
अटल व्योम qcom_smd_channel_set_state(काष्ठा qcom_smd_channel *channel,
				       पूर्णांक state)
अणु
	काष्ठा qcom_smd_edge *edge = channel->edge;
	bool is_खोलो = state == SMD_CHANNEL_OPENED;

	अगर (channel->state == state)
		वापस;

	dev_dbg(&edge->dev, "set_state(%s, %d)\n", channel->name, state);

	SET_TX_CHANNEL_FLAG(channel, fDSR, is_खोलो);
	SET_TX_CHANNEL_FLAG(channel, fCTS, is_खोलो);
	SET_TX_CHANNEL_FLAG(channel, fCD, is_खोलो);

	SET_TX_CHANNEL_INFO(channel, state, state);
	SET_TX_CHANNEL_FLAG(channel, fSTATE, 1);

	channel->state = state;
	qcom_smd_संकेत_channel(channel);
पूर्ण

/*
 * Copy count bytes of data using 32bit accesses, अगर that's required.
 */
अटल व्योम smd_copy_to_fअगरo(व्योम __iomem *dst,
			     स्थिर व्योम *src,
			     माप_प्रकार count,
			     bool word_aligned)
अणु
	अगर (word_aligned) अणु
		__ioग_लिखो32_copy(dst, src, count / माप(u32));
	पूर्ण अन्यथा अणु
		स_नकल_toio(dst, src, count);
	पूर्ण
पूर्ण

/*
 * Copy count bytes of data using 32bit accesses, अगर that is required.
 */
अटल व्योम smd_copy_from_fअगरo(व्योम *dst,
			       स्थिर व्योम __iomem *src,
			       माप_प्रकार count,
			       bool word_aligned)
अणु
	अगर (word_aligned) अणु
		__ioपढ़ो32_copy(dst, src, count / माप(u32));
	पूर्ण अन्यथा अणु
		स_नकल_fromio(dst, src, count);
	पूर्ण
पूर्ण

/*
 * Read count bytes of data from the rx fअगरo पूर्णांकo buf, but करोn't advance the
 * tail.
 */
अटल माप_प्रकार qcom_smd_channel_peek(काष्ठा qcom_smd_channel *channel,
				    व्योम *buf, माप_प्रकार count)
अणु
	bool word_aligned;
	अचिन्हित tail;
	माप_प्रकार len;

	word_aligned = channel->info_word;
	tail = GET_RX_CHANNEL_INFO(channel, tail);

	len = min_t(माप_प्रकार, count, channel->fअगरo_size - tail);
	अगर (len) अणु
		smd_copy_from_fअगरo(buf,
				   channel->rx_fअगरo + tail,
				   len,
				   word_aligned);
	पूर्ण

	अगर (len != count) अणु
		smd_copy_from_fअगरo(buf + len,
				   channel->rx_fअगरo,
				   count - len,
				   word_aligned);
	पूर्ण

	वापस count;
पूर्ण

/*
 * Advance the rx tail by count bytes.
 */
अटल व्योम qcom_smd_channel_advance(काष्ठा qcom_smd_channel *channel,
				     माप_प्रकार count)
अणु
	अचिन्हित tail;

	tail = GET_RX_CHANNEL_INFO(channel, tail);
	tail += count;
	tail &= (channel->fअगरo_size - 1);
	SET_RX_CHANNEL_INFO(channel, tail, tail);
पूर्ण

/*
 * Read out a single packet from the rx fअगरo and deliver it to the device
 */
अटल पूर्णांक qcom_smd_channel_recv_single(काष्ठा qcom_smd_channel *channel)
अणु
	काष्ठा rpmsg_endpoपूर्णांक *ept = &channel->qsept->ept;
	अचिन्हित tail;
	माप_प्रकार len;
	व्योम *ptr;
	पूर्णांक ret;

	tail = GET_RX_CHANNEL_INFO(channel, tail);

	/* Use bounce buffer अगर the data wraps */
	अगर (tail + channel->pkt_size >= channel->fअगरo_size) अणु
		ptr = channel->bounce_buffer;
		len = qcom_smd_channel_peek(channel, ptr, channel->pkt_size);
	पूर्ण अन्यथा अणु
		ptr = channel->rx_fअगरo + tail;
		len = channel->pkt_size;
	पूर्ण

	ret = ept->cb(ept->rpdev, ptr, len, ept->priv, RPMSG_ADDR_ANY);
	अगर (ret < 0)
		वापस ret;

	/* Only क्रमward the tail अगर the client consumed the data */
	qcom_smd_channel_advance(channel, len);

	channel->pkt_size = 0;

	वापस 0;
पूर्ण

/*
 * Per channel पूर्णांकerrupt handling
 */
अटल bool qcom_smd_channel_पूर्णांकr(काष्ठा qcom_smd_channel *channel)
अणु
	bool need_state_scan = false;
	पूर्णांक remote_state;
	__le32 pktlen;
	पूर्णांक avail;
	पूर्णांक ret;

	/* Handle state changes */
	remote_state = GET_RX_CHANNEL_INFO(channel, state);
	अगर (remote_state != channel->remote_state) अणु
		channel->remote_state = remote_state;
		need_state_scan = true;

		wake_up_पूर्णांकerruptible_all(&channel->state_change_event);
	पूर्ण
	/* Indicate that we have seen any state change */
	SET_RX_CHANNEL_FLAG(channel, fSTATE, 0);

	/* Signal रुकोing qcom_smd_send() about the पूर्णांकerrupt */
	अगर (!GET_TX_CHANNEL_FLAG(channel, fBLOCKREADINTR))
		wake_up_पूर्णांकerruptible_all(&channel->fblockपढ़ो_event);

	/* Don't consume any data until we've खोलोed the channel */
	अगर (channel->state != SMD_CHANNEL_OPENED)
		जाओ out;

	/* Indicate that we've seen the new data */
	SET_RX_CHANNEL_FLAG(channel, fHEAD, 0);

	/* Consume data */
	क्रम (;;) अणु
		avail = qcom_smd_channel_get_rx_avail(channel);

		अगर (!channel->pkt_size && avail >= SMD_PACKET_HEADER_LEN) अणु
			qcom_smd_channel_peek(channel, &pktlen, माप(pktlen));
			qcom_smd_channel_advance(channel, SMD_PACKET_HEADER_LEN);
			channel->pkt_size = le32_to_cpu(pktlen);
		पूर्ण अन्यथा अगर (channel->pkt_size && avail >= channel->pkt_size) अणु
			ret = qcom_smd_channel_recv_single(channel);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* Indicate that we have seen and updated tail */
	SET_RX_CHANNEL_FLAG(channel, fTAIL, 1);

	/* Signal the remote that we've consumed the data (अगर requested) */
	अगर (!GET_RX_CHANNEL_FLAG(channel, fBLOCKREADINTR)) अणु
		/* Ensure ordering of channel info updates */
		wmb();

		qcom_smd_संकेत_channel(channel);
	पूर्ण

out:
	वापस need_state_scan;
पूर्ण

/*
 * The edge पूर्णांकerrupts are triggered by the remote processor on state changes,
 * channel info updates or when new channels are created.
 */
अटल irqवापस_t qcom_smd_edge_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcom_smd_edge *edge = data;
	काष्ठा qcom_smd_channel *channel;
	अचिन्हित available;
	bool kick_scanner = false;
	bool kick_state = false;

	/*
	 * Handle state changes or data on each of the channels on this edge
	 */
	spin_lock(&edge->channels_lock);
	list_क्रम_each_entry(channel, &edge->channels, list) अणु
		spin_lock(&channel->recv_lock);
		kick_state |= qcom_smd_channel_पूर्णांकr(channel);
		spin_unlock(&channel->recv_lock);
	पूर्ण
	spin_unlock(&edge->channels_lock);

	/*
	 * Creating a new channel requires allocating an smem entry, so we only
	 * have to scan अगर the amount of available space in smem have changed
	 * since last scan.
	 */
	available = qcom_smem_get_मुक्त_space(edge->remote_pid);
	अगर (available != edge->smem_available) अणु
		edge->smem_available = available;
		kick_scanner = true;
	पूर्ण

	अगर (kick_scanner)
		schedule_work(&edge->scan_work);
	अगर (kick_state)
		schedule_work(&edge->state_work);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Calculate how much space is available in the tx fअगरo.
 */
अटल माप_प्रकार qcom_smd_get_tx_avail(काष्ठा qcom_smd_channel *channel)
अणु
	अचिन्हित head;
	अचिन्हित tail;
	अचिन्हित mask = channel->fअगरo_size - 1;

	head = GET_TX_CHANNEL_INFO(channel, head);
	tail = GET_TX_CHANNEL_INFO(channel, tail);

	वापस mask - ((head - tail) & mask);
पूर्ण

/*
 * Write count bytes of data पूर्णांकo channel, possibly wrapping in the ring buffer
 */
अटल पूर्णांक qcom_smd_ग_लिखो_fअगरo(काष्ठा qcom_smd_channel *channel,
			       स्थिर व्योम *data,
			       माप_प्रकार count)
अणु
	bool word_aligned;
	अचिन्हित head;
	माप_प्रकार len;

	word_aligned = channel->info_word;
	head = GET_TX_CHANNEL_INFO(channel, head);

	len = min_t(माप_प्रकार, count, channel->fअगरo_size - head);
	अगर (len) अणु
		smd_copy_to_fअगरo(channel->tx_fअगरo + head,
				 data,
				 len,
				 word_aligned);
	पूर्ण

	अगर (len != count) अणु
		smd_copy_to_fअगरo(channel->tx_fअगरo,
				 data + len,
				 count - len,
				 word_aligned);
	पूर्ण

	head += count;
	head &= (channel->fअगरo_size - 1);
	SET_TX_CHANNEL_INFO(channel, head, head);

	वापस count;
पूर्ण

/**
 * qcom_smd_send - ग_लिखो data to smd channel
 * @channel:	channel handle
 * @data:	buffer of data to ग_लिखो
 * @len:	number of bytes to ग_लिखो
 * @रुको:	flag to indicate अगर ग_लिखो has ca रुको
 *
 * This is a blocking ग_लिखो of len bytes पूर्णांकo the channel's tx ring buffer and
 * संकेत the remote end. It will sleep until there is enough space available
 * in the tx buffer, utilizing the fBLOCKREADINTR संकेतing mechanism to aव्योम
 * polling.
 */
अटल पूर्णांक __qcom_smd_send(काष्ठा qcom_smd_channel *channel, स्थिर व्योम *data,
			   पूर्णांक len, bool रुको)
अणु
	__le32 hdr[5] = अणु cpu_to_le32(len), पूर्ण;
	पूर्णांक tlen = माप(hdr) + len;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Word aligned channels only accept word size aligned data */
	अगर (channel->info_word && len % 4)
		वापस -EINVAL;

	/* Reject packets that are too big */
	अगर (tlen >= channel->fअगरo_size)
		वापस -EINVAL;

	/* Highlight the fact that अगर we enter the loop below we might sleep */
	अगर (रुको)
		might_sleep();

	spin_lock_irqsave(&channel->tx_lock, flags);

	जबतक (qcom_smd_get_tx_avail(channel) < tlen &&
	       channel->state == SMD_CHANNEL_OPENED) अणु
		अगर (!रुको) अणु
			ret = -EAGAIN;
			जाओ out_unlock;
		पूर्ण

		SET_TX_CHANNEL_FLAG(channel, fBLOCKREADINTR, 0);

		/* Wait without holding the tx_lock */
		spin_unlock_irqrestore(&channel->tx_lock, flags);

		ret = रुको_event_पूर्णांकerruptible(channel->fblockपढ़ो_event,
				       qcom_smd_get_tx_avail(channel) >= tlen ||
				       channel->state != SMD_CHANNEL_OPENED);
		अगर (ret)
			वापस ret;

		spin_lock_irqsave(&channel->tx_lock, flags);

		SET_TX_CHANNEL_FLAG(channel, fBLOCKREADINTR, 1);
	पूर्ण

	/* Fail अगर the channel was बंदd */
	अगर (channel->state != SMD_CHANNEL_OPENED) अणु
		ret = -EPIPE;
		जाओ out_unlock;
	पूर्ण

	SET_TX_CHANNEL_FLAG(channel, fTAIL, 0);

	qcom_smd_ग_लिखो_fअगरo(channel, hdr, माप(hdr));
	qcom_smd_ग_लिखो_fअगरo(channel, data, len);

	SET_TX_CHANNEL_FLAG(channel, fHEAD, 1);

	/* Ensure ordering of channel info updates */
	wmb();

	qcom_smd_संकेत_channel(channel);

out_unlock:
	spin_unlock_irqrestore(&channel->tx_lock, flags);

	वापस ret;
पूर्ण

/*
 * Helper क्रम खोलोing a channel
 */
अटल पूर्णांक qcom_smd_channel_खोलो(काष्ठा qcom_smd_channel *channel,
				 rpmsg_rx_cb_t cb)
अणु
	काष्ठा qcom_smd_edge *edge = channel->edge;
	माप_प्रकार bb_size;
	पूर्णांक ret;

	/*
	 * Packets are maximum 4k, but reduce अगर the fअगरo is smaller
	 */
	bb_size = min(channel->fअगरo_size, SZ_4K);
	channel->bounce_buffer = kदो_स्मृति(bb_size, GFP_KERNEL);
	अगर (!channel->bounce_buffer)
		वापस -ENOMEM;

	qcom_smd_channel_set_callback(channel, cb);
	qcom_smd_channel_set_state(channel, SMD_CHANNEL_OPENING);

	/* Wait क्रम remote to enter खोलोing or खोलोed */
	ret = रुको_event_पूर्णांकerruptible_समयout(channel->state_change_event,
			channel->remote_state == SMD_CHANNEL_OPENING ||
			channel->remote_state == SMD_CHANNEL_OPENED,
			HZ);
	अगर (!ret) अणु
		dev_err(&edge->dev, "remote side did not enter opening state\n");
		जाओ out_बंद_समयout;
	पूर्ण

	qcom_smd_channel_set_state(channel, SMD_CHANNEL_OPENED);

	/* Wait क्रम remote to enter खोलोed */
	ret = रुको_event_पूर्णांकerruptible_समयout(channel->state_change_event,
			channel->remote_state == SMD_CHANNEL_OPENED,
			HZ);
	अगर (!ret) अणु
		dev_err(&edge->dev, "remote side did not enter open state\n");
		जाओ out_बंद_समयout;
	पूर्ण

	वापस 0;

out_बंद_समयout:
	qcom_smd_channel_set_state(channel, SMD_CHANNEL_CLOSED);
	वापस -ETIMEDOUT;
पूर्ण

/*
 * Helper क्रम closing and resetting a channel
 */
अटल व्योम qcom_smd_channel_बंद(काष्ठा qcom_smd_channel *channel)
अणु
	qcom_smd_channel_set_callback(channel, शून्य);

	kमुक्त(channel->bounce_buffer);
	channel->bounce_buffer = शून्य;

	qcom_smd_channel_set_state(channel, SMD_CHANNEL_CLOSED);
	qcom_smd_channel_reset(channel);
पूर्ण

अटल काष्ठा qcom_smd_channel *
qcom_smd_find_channel(काष्ठा qcom_smd_edge *edge, स्थिर अक्षर *name)
अणु
	काष्ठा qcom_smd_channel *channel;
	काष्ठा qcom_smd_channel *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edge->channels_lock, flags);
	list_क्रम_each_entry(channel, &edge->channels, list) अणु
		अगर (!म_भेद(channel->name, name)) अणु
			ret = channel;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&edge->channels_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम __ept_release(काष्ठा kref *kref)
अणु
	काष्ठा rpmsg_endpoपूर्णांक *ept = container_of(kref, काष्ठा rpmsg_endpoपूर्णांक,
						  refcount);
	kमुक्त(to_smd_endpoपूर्णांक(ept));
पूर्ण

अटल काष्ठा rpmsg_endpoपूर्णांक *qcom_smd_create_ept(काष्ठा rpmsg_device *rpdev,
						  rpmsg_rx_cb_t cb, व्योम *priv,
						  काष्ठा rpmsg_channel_info chinfo)
अणु
	काष्ठा qcom_smd_endpoपूर्णांक *qsept;
	काष्ठा qcom_smd_channel *channel;
	काष्ठा qcom_smd_device *qsdev = to_smd_device(rpdev);
	काष्ठा qcom_smd_edge *edge = qsdev->edge;
	काष्ठा rpmsg_endpoपूर्णांक *ept;
	स्थिर अक्षर *name = chinfo.name;
	पूर्णांक ret;

	/* Wait up to HZ क्रम the channel to appear */
	ret = रुको_event_पूर्णांकerruptible_समयout(edge->new_channel_event,
			(channel = qcom_smd_find_channel(edge, name)) != शून्य,
			HZ);
	अगर (!ret)
		वापस शून्य;

	अगर (channel->state != SMD_CHANNEL_CLOSED) अणु
		dev_err(&rpdev->dev, "channel %s is busy\n", channel->name);
		वापस शून्य;
	पूर्ण

	qsept = kzalloc(माप(*qsept), GFP_KERNEL);
	अगर (!qsept)
		वापस शून्य;

	ept = &qsept->ept;

	kref_init(&ept->refcount);

	ept->rpdev = rpdev;
	ept->cb = cb;
	ept->priv = priv;
	ept->ops = &qcom_smd_endpoपूर्णांक_ops;

	channel->qsept = qsept;
	qsept->qsch = channel;

	ret = qcom_smd_channel_खोलो(channel, cb);
	अगर (ret)
		जाओ मुक्त_ept;

	वापस ept;

मुक्त_ept:
	channel->qsept = शून्य;
	kref_put(&ept->refcount, __ept_release);
	वापस शून्य;
पूर्ण

अटल व्योम qcom_smd_destroy_ept(काष्ठा rpmsg_endpoपूर्णांक *ept)
अणु
	काष्ठा qcom_smd_endpoपूर्णांक *qsept = to_smd_endpoपूर्णांक(ept);
	काष्ठा qcom_smd_channel *ch = qsept->qsch;

	qcom_smd_channel_बंद(ch);
	ch->qsept = शून्य;
	kref_put(&ept->refcount, __ept_release);
पूर्ण

अटल पूर्णांक qcom_smd_send(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	काष्ठा qcom_smd_endpoपूर्णांक *qsept = to_smd_endpoपूर्णांक(ept);

	वापस __qcom_smd_send(qsept->qsch, data, len, true);
पूर्ण

अटल पूर्णांक qcom_smd_trysend(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	काष्ठा qcom_smd_endpoपूर्णांक *qsept = to_smd_endpoपूर्णांक(ept);

	वापस __qcom_smd_send(qsept->qsch, data, len, false);
पूर्ण

अटल पूर्णांक qcom_smd_sendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst)
अणु
	काष्ठा qcom_smd_endpoपूर्णांक *qsept = to_smd_endpoपूर्णांक(ept);

	वापस __qcom_smd_send(qsept->qsch, data, len, true);
पूर्ण

अटल पूर्णांक qcom_smd_trysendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst)
अणु
	काष्ठा qcom_smd_endpoपूर्णांक *qsept = to_smd_endpoपूर्णांक(ept);

	वापस __qcom_smd_send(qsept->qsch, data, len, false);
पूर्ण

अटल __poll_t qcom_smd_poll(काष्ठा rpmsg_endpoपूर्णांक *ept,
				  काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा qcom_smd_endpoपूर्णांक *qsept = to_smd_endpoपूर्णांक(ept);
	काष्ठा qcom_smd_channel *channel = qsept->qsch;
	__poll_t mask = 0;

	poll_रुको(filp, &channel->fblockपढ़ो_event, रुको);

	अगर (qcom_smd_get_tx_avail(channel) > 20)
		mask |= EPOLLOUT | EPOLLWRNORM;

	वापस mask;
पूर्ण

/*
 * Finds the device_node क्रम the smd child पूर्णांकerested in this channel.
 */
अटल काष्ठा device_node *qcom_smd_match_channel(काष्ठा device_node *edge_node,
						  स्थिर अक्षर *channel)
अणु
	काष्ठा device_node *child;
	स्थिर अक्षर *name;
	स्थिर अक्षर *key;
	पूर्णांक ret;

	क्रम_each_available_child_of_node(edge_node, child) अणु
		key = "qcom,smd-channels";
		ret = of_property_पढ़ो_string(child, key, &name);
		अगर (ret)
			जारी;

		अगर (म_भेद(name, channel) == 0)
			वापस child;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक qcom_smd_announce_create(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा qcom_smd_endpoपूर्णांक *qept = to_smd_endpoपूर्णांक(rpdev->ept);
	काष्ठा qcom_smd_channel *channel = qept->qsch;
	अचिन्हित दीर्घ flags;
	bool kick_state;

	spin_lock_irqsave(&channel->recv_lock, flags);
	kick_state = qcom_smd_channel_पूर्णांकr(channel);
	spin_unlock_irqrestore(&channel->recv_lock, flags);

	अगर (kick_state)
		schedule_work(&channel->edge->state_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rpmsg_device_ops qcom_smd_device_ops = अणु
	.create_ept = qcom_smd_create_ept,
	.announce_create = qcom_smd_announce_create,
पूर्ण;

अटल स्थिर काष्ठा rpmsg_endpoपूर्णांक_ops qcom_smd_endpoपूर्णांक_ops = अणु
	.destroy_ept = qcom_smd_destroy_ept,
	.send = qcom_smd_send,
	.sendto = qcom_smd_sendto,
	.trysend = qcom_smd_trysend,
	.trysendto = qcom_smd_trysendto,
	.poll = qcom_smd_poll,
पूर्ण;

अटल व्योम qcom_smd_release_device(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	काष्ठा qcom_smd_device *qsdev = to_smd_device(rpdev);

	kमुक्त(qsdev);
पूर्ण

/*
 * Create a smd client device क्रम channel that is being खोलोed.
 */
अटल पूर्णांक qcom_smd_create_device(काष्ठा qcom_smd_channel *channel)
अणु
	काष्ठा qcom_smd_device *qsdev;
	काष्ठा rpmsg_device *rpdev;
	काष्ठा qcom_smd_edge *edge = channel->edge;

	dev_dbg(&edge->dev, "registering '%s'\n", channel->name);

	qsdev = kzalloc(माप(*qsdev), GFP_KERNEL);
	अगर (!qsdev)
		वापस -ENOMEM;

	/* Link qsdev to our SMD edge */
	qsdev->edge = edge;

	/* Assign callbacks क्रम rpmsg_device */
	qsdev->rpdev.ops = &qcom_smd_device_ops;

	/* Assign खुला inक्रमmation to the rpmsg_device */
	rpdev = &qsdev->rpdev;
	म_नकलन(rpdev->id.name, channel->name, RPMSG_NAME_SIZE);
	rpdev->src = RPMSG_ADDR_ANY;
	rpdev->dst = RPMSG_ADDR_ANY;

	rpdev->dev.of_node = qcom_smd_match_channel(edge->of_node, channel->name);
	rpdev->dev.parent = &edge->dev;
	rpdev->dev.release = qcom_smd_release_device;

	वापस rpmsg_रेजिस्टर_device(rpdev);
पूर्ण

अटल पूर्णांक qcom_smd_create_chrdev(काष्ठा qcom_smd_edge *edge)
अणु
	काष्ठा qcom_smd_device *qsdev;

	qsdev = kzalloc(माप(*qsdev), GFP_KERNEL);
	अगर (!qsdev)
		वापस -ENOMEM;

	qsdev->edge = edge;
	qsdev->rpdev.ops = &qcom_smd_device_ops;
	qsdev->rpdev.dev.parent = &edge->dev;
	qsdev->rpdev.dev.release = qcom_smd_release_device;

	वापस rpmsg_chrdev_रेजिस्टर_device(&qsdev->rpdev);
पूर्ण

/*
 * Allocate the qcom_smd_channel object क्रम a newly found smd channel,
 * retrieving and validating the smem items involved.
 */
अटल काष्ठा qcom_smd_channel *qcom_smd_create_channel(काष्ठा qcom_smd_edge *edge,
							अचिन्हित smem_info_item,
							अचिन्हित smem_fअगरo_item,
							अक्षर *name)
अणु
	काष्ठा qcom_smd_channel *channel;
	माप_प्रकार fअगरo_size;
	माप_प्रकार info_size;
	व्योम *fअगरo_base;
	व्योम *info;
	पूर्णांक ret;

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस ERR_PTR(-ENOMEM);

	channel->edge = edge;
	channel->name = kstrdup(name, GFP_KERNEL);
	अगर (!channel->name) अणु
		ret = -ENOMEM;
		जाओ मुक्त_channel;
	पूर्ण

	spin_lock_init(&channel->tx_lock);
	spin_lock_init(&channel->recv_lock);
	init_रुकोqueue_head(&channel->fblockपढ़ो_event);
	init_रुकोqueue_head(&channel->state_change_event);

	info = qcom_smem_get(edge->remote_pid, smem_info_item, &info_size);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ मुक्त_name_and_channel;
	पूर्ण

	/*
	 * Use the size of the item to figure out which channel info काष्ठा to
	 * use.
	 */
	अगर (info_size == 2 * माप(काष्ठा smd_channel_info_word)) अणु
		channel->info_word = info;
	पूर्ण अन्यथा अगर (info_size == 2 * माप(काष्ठा smd_channel_info)) अणु
		channel->info = info;
	पूर्ण अन्यथा अणु
		dev_err(&edge->dev,
			"channel info of size %zu not supported\n", info_size);
		ret = -EINVAL;
		जाओ मुक्त_name_and_channel;
	पूर्ण

	fअगरo_base = qcom_smem_get(edge->remote_pid, smem_fअगरo_item, &fअगरo_size);
	अगर (IS_ERR(fअगरo_base)) अणु
		ret =  PTR_ERR(fअगरo_base);
		जाओ मुक्त_name_and_channel;
	पूर्ण

	/* The channel consist of a rx and tx fअगरo of equal size */
	fअगरo_size /= 2;

	dev_dbg(&edge->dev, "new channel '%s' info-size: %zu fifo-size: %zu\n",
			  name, info_size, fअगरo_size);

	channel->tx_fअगरo = fअगरo_base;
	channel->rx_fअगरo = fअगरo_base + fअगरo_size;
	channel->fअगरo_size = fअगरo_size;

	qcom_smd_channel_reset(channel);

	वापस channel;

मुक्त_name_and_channel:
	kमुक्त(channel->name);
मुक्त_channel:
	kमुक्त(channel);

	वापस ERR_PTR(ret);
पूर्ण

/*
 * Scans the allocation table क्रम any newly allocated channels, calls
 * qcom_smd_create_channel() to create representations of these and add
 * them to the edge's list of channels.
 */
अटल व्योम qcom_channel_scan_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qcom_smd_edge *edge = container_of(work, काष्ठा qcom_smd_edge, scan_work);
	काष्ठा qcom_smd_alloc_entry *alloc_tbl;
	काष्ठा qcom_smd_alloc_entry *entry;
	काष्ठा qcom_smd_channel *channel;
	अचिन्हित दीर्घ flags;
	अचिन्हित fअगरo_id;
	अचिन्हित info_id;
	पूर्णांक tbl;
	पूर्णांक i;
	u32 eflags, cid;

	क्रम (tbl = 0; tbl < SMD_ALLOC_TBL_COUNT; tbl++) अणु
		alloc_tbl = qcom_smem_get(edge->remote_pid,
				    smem_items[tbl].alloc_tbl_id, शून्य);
		अगर (IS_ERR(alloc_tbl))
			जारी;

		क्रम (i = 0; i < SMD_ALLOC_TBL_SIZE; i++) अणु
			entry = &alloc_tbl[i];
			eflags = le32_to_cpu(entry->flags);
			अगर (test_bit(i, edge->allocated[tbl]))
				जारी;

			अगर (entry->ref_count == 0)
				जारी;

			अगर (!entry->name[0])
				जारी;

			अगर (!(eflags & SMD_CHANNEL_FLAGS_PACKET))
				जारी;

			अगर ((eflags & SMD_CHANNEL_FLAGS_EDGE_MASK) != edge->edge_id)
				जारी;

			cid = le32_to_cpu(entry->cid);
			info_id = smem_items[tbl].info_base_id + cid;
			fअगरo_id = smem_items[tbl].fअगरo_base_id + cid;

			channel = qcom_smd_create_channel(edge, info_id, fअगरo_id, entry->name);
			अगर (IS_ERR(channel))
				जारी;

			spin_lock_irqsave(&edge->channels_lock, flags);
			list_add(&channel->list, &edge->channels);
			spin_unlock_irqrestore(&edge->channels_lock, flags);

			dev_dbg(&edge->dev, "new channel found: '%s'\n", channel->name);
			set_bit(i, edge->allocated[tbl]);

			wake_up_पूर्णांकerruptible_all(&edge->new_channel_event);
		पूर्ण
	पूर्ण

	schedule_work(&edge->state_work);
पूर्ण

/*
 * This per edge worker scans smem क्रम any new channels and रेजिस्टर these. It
 * then scans all रेजिस्टरed channels क्रम state changes that should be handled
 * by creating or destroying smd client devices क्रम the रेजिस्टरed channels.
 *
 * LOCKING: edge->channels_lock only needs to cover the list operations, as the
 * worker is समाप्तed beक्रमe any channels are deallocated
 */
अटल व्योम qcom_channel_state_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qcom_smd_channel *channel;
	काष्ठा qcom_smd_edge *edge = container_of(work,
						  काष्ठा qcom_smd_edge,
						  state_work);
	काष्ठा rpmsg_channel_info chinfo;
	अचिन्हित remote_state;
	अचिन्हित दीर्घ flags;

	/*
	 * Register a device क्रम any बंदd channel where the remote processor
	 * is showing पूर्णांकerest in खोलोing the channel.
	 */
	spin_lock_irqsave(&edge->channels_lock, flags);
	list_क्रम_each_entry(channel, &edge->channels, list) अणु
		अगर (channel->state != SMD_CHANNEL_CLOSED)
			जारी;

		remote_state = GET_RX_CHANNEL_INFO(channel, state);
		अगर (remote_state != SMD_CHANNEL_OPENING &&
		    remote_state != SMD_CHANNEL_OPENED)
			जारी;

		अगर (channel->रेजिस्टरed)
			जारी;

		spin_unlock_irqrestore(&edge->channels_lock, flags);
		qcom_smd_create_device(channel);
		channel->रेजिस्टरed = true;
		spin_lock_irqsave(&edge->channels_lock, flags);

		channel->रेजिस्टरed = true;
	पूर्ण

	/*
	 * Unरेजिस्टर the device क्रम any channel that is खोलोed where the
	 * remote processor is closing the channel.
	 */
	list_क्रम_each_entry(channel, &edge->channels, list) अणु
		अगर (channel->state != SMD_CHANNEL_OPENING &&
		    channel->state != SMD_CHANNEL_OPENED)
			जारी;

		remote_state = GET_RX_CHANNEL_INFO(channel, state);
		अगर (remote_state == SMD_CHANNEL_OPENING ||
		    remote_state == SMD_CHANNEL_OPENED)
			जारी;

		spin_unlock_irqrestore(&edge->channels_lock, flags);

		म_नकलन(chinfo.name, channel->name, माप(chinfo.name));
		chinfo.src = RPMSG_ADDR_ANY;
		chinfo.dst = RPMSG_ADDR_ANY;
		rpmsg_unरेजिस्टर_device(&edge->dev, &chinfo);
		channel->रेजिस्टरed = false;
		spin_lock_irqsave(&edge->channels_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&edge->channels_lock, flags);
पूर्ण

/*
 * Parses an of_node describing an edge.
 */
अटल पूर्णांक qcom_smd_parse_edge(काष्ठा device *dev,
			       काष्ठा device_node *node,
			       काष्ठा qcom_smd_edge *edge)
अणु
	काष्ठा device_node *syscon_np;
	स्थिर अक्षर *key;
	पूर्णांक irq;
	पूर्णांक ret;

	INIT_LIST_HEAD(&edge->channels);
	spin_lock_init(&edge->channels_lock);

	INIT_WORK(&edge->scan_work, qcom_channel_scan_worker);
	INIT_WORK(&edge->state_work, qcom_channel_state_worker);

	edge->of_node = of_node_get(node);

	key = "qcom,smd-edge";
	ret = of_property_पढ़ो_u32(node, key, &edge->edge_id);
	अगर (ret) अणु
		dev_err(dev, "edge missing %s property\n", key);
		जाओ put_node;
	पूर्ण

	edge->remote_pid = QCOM_SMEM_HOST_ANY;
	key = "qcom,remote-pid";
	of_property_पढ़ो_u32(node, key, &edge->remote_pid);

	edge->mbox_client.dev = dev;
	edge->mbox_client.knows_txकरोne = true;
	edge->mbox_chan = mbox_request_channel(&edge->mbox_client, 0);
	अगर (IS_ERR(edge->mbox_chan)) अणु
		अगर (PTR_ERR(edge->mbox_chan) != -ENODEV) अणु
			ret = PTR_ERR(edge->mbox_chan);
			जाओ put_node;
		पूर्ण

		edge->mbox_chan = शून्य;

		syscon_np = of_parse_phandle(node, "qcom,ipc", 0);
		अगर (!syscon_np) अणु
			dev_err(dev, "no qcom,ipc node\n");
			ret = -ENODEV;
			जाओ put_node;
		पूर्ण

		edge->ipc_regmap = syscon_node_to_regmap(syscon_np);
		अगर (IS_ERR(edge->ipc_regmap)) अणु
			ret = PTR_ERR(edge->ipc_regmap);
			जाओ put_node;
		पूर्ण

		key = "qcom,ipc";
		ret = of_property_पढ़ो_u32_index(node, key, 1, &edge->ipc_offset);
		अगर (ret < 0) अणु
			dev_err(dev, "no offset in %s\n", key);
			जाओ put_node;
		पूर्ण

		ret = of_property_पढ़ो_u32_index(node, key, 2, &edge->ipc_bit);
		अगर (ret < 0) अणु
			dev_err(dev, "no bit in %s\n", key);
			जाओ put_node;
		पूर्ण
	पूर्ण

	ret = of_property_पढ़ो_string(node, "label", &edge->name);
	अगर (ret < 0)
		edge->name = node->name;

	irq = irq_of_parse_and_map(node, 0);
	अगर (irq < 0) अणु
		dev_err(dev, "required smd interrupt missing\n");
		ret = irq;
		जाओ put_node;
	पूर्ण

	ret = devm_request_irq(dev, irq,
			       qcom_smd_edge_पूर्णांकr, IRQF_TRIGGER_RISING,
			       node->name, edge);
	अगर (ret) अणु
		dev_err(dev, "failed to request smd irq\n");
		जाओ put_node;
	पूर्ण

	edge->irq = irq;

	वापस 0;

put_node:
	of_node_put(node);
	edge->of_node = शून्य;

	वापस ret;
पूर्ण

/*
 * Release function क्रम an edge.
  * Reset the state of each associated channel and मुक्त the edge context.
 */
अटल व्योम qcom_smd_edge_release(काष्ठा device *dev)
अणु
	काष्ठा qcom_smd_channel *channel, *पंचांगp;
	काष्ठा qcom_smd_edge *edge = to_smd_edge(dev);

	list_क्रम_each_entry_safe(channel, पंचांगp, &edge->channels, list) अणु
		list_del(&channel->list);
		kमुक्त(channel->name);
		kमुक्त(channel);
	पूर्ण

	kमुक्त(edge);
पूर्ण

अटल sमाप_प्रकार rpmsg_name_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qcom_smd_edge *edge = to_smd_edge(dev);

	वापस प्र_लिखो(buf, "%s\n", edge->name);
पूर्ण
अटल DEVICE_ATTR_RO(rpmsg_name);

अटल काष्ठा attribute *qcom_smd_edge_attrs[] = अणु
	&dev_attr_rpmsg_name.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(qcom_smd_edge);

/**
 * qcom_smd_रेजिस्टर_edge() - रेजिस्टर an edge based on an device_node
 * @parent:    parent device क्रम the edge
 * @node:      device_node describing the edge
 *
 * Returns an edge reference, or negative ERR_PTR() on failure.
 */
काष्ठा qcom_smd_edge *qcom_smd_रेजिस्टर_edge(काष्ठा device *parent,
					     काष्ठा device_node *node)
अणु
	काष्ठा qcom_smd_edge *edge;
	पूर्णांक ret;

	edge = kzalloc(माप(*edge), GFP_KERNEL);
	अगर (!edge)
		वापस ERR_PTR(-ENOMEM);

	init_रुकोqueue_head(&edge->new_channel_event);

	edge->dev.parent = parent;
	edge->dev.release = qcom_smd_edge_release;
	edge->dev.of_node = node;
	edge->dev.groups = qcom_smd_edge_groups;
	dev_set_name(&edge->dev, "%s:%pOFn", dev_name(parent), node);
	ret = device_रेजिस्टर(&edge->dev);
	अगर (ret) अणु
		pr_err("failed to register smd edge\n");
		put_device(&edge->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = qcom_smd_parse_edge(&edge->dev, node, edge);
	अगर (ret) अणु
		dev_err(&edge->dev, "failed to parse smd edge\n");
		जाओ unरेजिस्टर_dev;
	पूर्ण

	ret = qcom_smd_create_chrdev(edge);
	अगर (ret) अणु
		dev_err(&edge->dev, "failed to register chrdev for edge\n");
		जाओ unरेजिस्टर_dev;
	पूर्ण

	schedule_work(&edge->scan_work);

	वापस edge;

unरेजिस्टर_dev:
	अगर (!IS_ERR_OR_शून्य(edge->mbox_chan))
		mbox_मुक्त_channel(edge->mbox_chan);

	device_unरेजिस्टर(&edge->dev);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(qcom_smd_रेजिस्टर_edge);

अटल पूर्णांक qcom_smd_हटाओ_device(काष्ठा device *dev, व्योम *data)
अणु
	device_unरेजिस्टर(dev);

	वापस 0;
पूर्ण

/**
 * qcom_smd_unरेजिस्टर_edge() - release an edge and its children
 * @edge:      edge reference acquired from qcom_smd_रेजिस्टर_edge
 */
पूर्णांक qcom_smd_unरेजिस्टर_edge(काष्ठा qcom_smd_edge *edge)
अणु
	पूर्णांक ret;

	disable_irq(edge->irq);
	cancel_work_sync(&edge->scan_work);
	cancel_work_sync(&edge->state_work);

	ret = device_क्रम_each_child(&edge->dev, शून्य, qcom_smd_हटाओ_device);
	अगर (ret)
		dev_warn(&edge->dev, "can't remove smd device: %d\n", ret);

	mbox_मुक्त_channel(edge->mbox_chan);
	device_unरेजिस्टर(&edge->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qcom_smd_unरेजिस्टर_edge);

अटल पूर्णांक qcom_smd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node;
	व्योम *p;

	/* Wait क्रम smem */
	p = qcom_smem_get(QCOM_SMEM_HOST_ANY, smem_items[0].alloc_tbl_id, शून्य);
	अगर (PTR_ERR(p) == -EPROBE_DEFER)
		वापस PTR_ERR(p);

	क्रम_each_available_child_of_node(pdev->dev.of_node, node)
		qcom_smd_रेजिस्टर_edge(&pdev->dev, node);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_smd_हटाओ_edge(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा qcom_smd_edge *edge = to_smd_edge(dev);

	वापस qcom_smd_unरेजिस्टर_edge(edge);
पूर्ण

/*
 * Shut करोwn all smd clients by making sure that each edge stops processing
 * events and scanning क्रम new channels, then call destroy on the devices.
 */
अटल पूर्णांक qcom_smd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = device_क्रम_each_child(&pdev->dev, शून्य, qcom_smd_हटाओ_edge);
	अगर (ret)
		dev_warn(&pdev->dev, "can't remove smd device: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_smd_of_match[] = अणु
	अणु .compatible = "qcom,smd" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_smd_of_match);

अटल काष्ठा platक्रमm_driver qcom_smd_driver = अणु
	.probe = qcom_smd_probe,
	.हटाओ = qcom_smd_हटाओ,
	.driver = अणु
		.name = "qcom-smd",
		.of_match_table = qcom_smd_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_smd_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qcom_smd_driver);
पूर्ण
subsys_initcall(qcom_smd_init);

अटल व्योम __निकास qcom_smd_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_smd_driver);
पूर्ण
module_निकास(qcom_smd_निकास);

MODULE_AUTHOR("Bjorn Andersson <bjorn.andersson@sonymobile.com>");
MODULE_DESCRIPTION("Qualcomm Shared Memory Driver");
MODULE_LICENSE("GPL v2");
