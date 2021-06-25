<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-2017, Linaro Ltd
 */

#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mailbox_client.h>

#समावेश "rpmsg_internal.h"
#समावेश "qcom_glink_native.h"

#घोषणा GLINK_NAME_SIZE		32
#घोषणा GLINK_VERSION_1		1

#घोषणा RPM_GLINK_CID_MIN	1
#घोषणा RPM_GLINK_CID_MAX	65536

काष्ठा glink_msg अणु
	__le16 cmd;
	__le16 param1;
	__le32 param2;
	u8 data[];
पूर्ण __packed;

/**
 * काष्ठा glink_defer_cmd - deferred incoming control message
 * @node:	list node
 * @msg:	message header
 * @data:	payload of the message
 *
 * Copy of a received control message, to be added to @rx_queue and processed
 * by @rx_work of @qcom_glink.
 */
काष्ठा glink_defer_cmd अणु
	काष्ठा list_head node;

	काष्ठा glink_msg msg;
	u8 data[];
पूर्ण;

/**
 * काष्ठा glink_core_rx_पूर्णांकent - RX पूर्णांकent
 * RX पूर्णांकent
 *
 * @data: poपूर्णांकer to the data (may be शून्य क्रम zero-copy)
 * @id: remote or local पूर्णांकent ID
 * @size: size of the original पूर्णांकent (करो not modअगरy)
 * @reuse: To mark अगर the पूर्णांकent can be reused after first use
 * @in_use: To mark अगर पूर्णांकent is alपढ़ोy in use क्रम the channel
 * @offset: next ग_लिखो offset (initially 0)
 * @node:	list node
 */
काष्ठा glink_core_rx_पूर्णांकent अणु
	व्योम *data;
	u32 id;
	माप_प्रकार size;
	bool reuse;
	bool in_use;
	u32 offset;

	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा qcom_glink - driver context, relates to one remote subप्रणाली
 * @dev:	reference to the associated काष्ठा device
 * @mbox_client: mailbox client
 * @mbox_chan:  mailbox channel
 * @rx_pipe:	pipe object क्रम receive FIFO
 * @tx_pipe:	pipe object क्रम transmit FIFO
 * @irq:	IRQ क्रम संकेतing incoming events
 * @rx_work:	worker क्रम handling received control messages
 * @rx_lock:	protects the @rx_queue
 * @rx_queue:	queue of received control messages to be processed in @rx_work
 * @tx_lock:	synchronizes operations on the tx fअगरo
 * @idr_lock:	synchronizes @lcids and @rcids modअगरications
 * @lcids:	idr of all channels with a known local channel id
 * @rcids:	idr of all channels with a known remote channel id
 * @features:	remote features
 * @पूर्णांकentless:	flag to indicate that there is no पूर्णांकent
 */
काष्ठा qcom_glink अणु
	काष्ठा device *dev;

	स्थिर अक्षर *name;

	काष्ठा mbox_client mbox_client;
	काष्ठा mbox_chan *mbox_chan;

	काष्ठा qcom_glink_pipe *rx_pipe;
	काष्ठा qcom_glink_pipe *tx_pipe;

	पूर्णांक irq;

	काष्ठा work_काष्ठा rx_work;
	spinlock_t rx_lock;
	काष्ठा list_head rx_queue;

	spinlock_t tx_lock;

	spinlock_t idr_lock;
	काष्ठा idr lcids;
	काष्ठा idr rcids;
	अचिन्हित दीर्घ features;

	bool पूर्णांकentless;
पूर्ण;

क्रमागत अणु
	GLINK_STATE_CLOSED,
	GLINK_STATE_OPENING,
	GLINK_STATE_OPEN,
	GLINK_STATE_CLOSING,
पूर्ण;

/**
 * काष्ठा glink_channel - पूर्णांकernal representation of a channel
 * @rpdev:	rpdev reference, only used क्रम primary endpoपूर्णांकs
 * @ept:	rpmsg endpoपूर्णांक this channel is associated with
 * @glink:	qcom_glink context handle
 * @refcount:	refcount क्रम the channel object
 * @recv_lock:	guard क्रम @ept.cb
 * @name:	unique channel name/identअगरier
 * @lcid:	channel id, in local space
 * @rcid:	channel id, in remote space
 * @पूर्णांकent_lock: lock क्रम protection of @liids, @riids
 * @liids:	idr of all local पूर्णांकents
 * @riids:	idr of all remote पूर्णांकents
 * @पूर्णांकent_work: worker responsible क्रम transmitting rx_करोne packets
 * @करोne_पूर्णांकents: list of पूर्णांकents that needs to be announced rx_करोne
 * @buf:	receive buffer, क्रम gathering fragments
 * @buf_offset:	ग_लिखो offset in @buf
 * @buf_size:	size of current @buf
 * @खोलो_ack:	completed once remote has acked the खोलो-request
 * @खोलो_req:	completed once खोलो-request has been received
 * @पूर्णांकent_req_lock: Synchronises multiple पूर्णांकent requests
 * @पूर्णांकent_req_result: Result of पूर्णांकent request
 * @पूर्णांकent_req_comp: Completion क्रम पूर्णांकent_req संकेतling
 */
काष्ठा glink_channel अणु
	काष्ठा rpmsg_endpoपूर्णांक ept;

	काष्ठा rpmsg_device *rpdev;
	काष्ठा qcom_glink *glink;

	काष्ठा kref refcount;

	spinlock_t recv_lock;

	अक्षर *name;
	अचिन्हित पूर्णांक lcid;
	अचिन्हित पूर्णांक rcid;

	spinlock_t पूर्णांकent_lock;
	काष्ठा idr liids;
	काष्ठा idr riids;
	काष्ठा work_काष्ठा पूर्णांकent_work;
	काष्ठा list_head करोne_पूर्णांकents;

	काष्ठा glink_core_rx_पूर्णांकent *buf;
	पूर्णांक buf_offset;
	पूर्णांक buf_size;

	काष्ठा completion खोलो_ack;
	काष्ठा completion खोलो_req;

	काष्ठा mutex पूर्णांकent_req_lock;
	bool पूर्णांकent_req_result;
	काष्ठा completion पूर्णांकent_req_comp;
पूर्ण;

#घोषणा to_glink_channel(_ept) container_of(_ept, काष्ठा glink_channel, ept)

अटल स्थिर काष्ठा rpmsg_endpoपूर्णांक_ops glink_endpoपूर्णांक_ops;

#घोषणा RPM_CMD_VERSION			0
#घोषणा RPM_CMD_VERSION_ACK		1
#घोषणा RPM_CMD_OPEN			2
#घोषणा RPM_CMD_CLOSE			3
#घोषणा RPM_CMD_OPEN_ACK		4
#घोषणा RPM_CMD_INTENT			5
#घोषणा RPM_CMD_RX_DONE			6
#घोषणा RPM_CMD_RX_INTENT_REQ		7
#घोषणा RPM_CMD_RX_INTENT_REQ_ACK	8
#घोषणा RPM_CMD_TX_DATA			9
#घोषणा RPM_CMD_CLOSE_ACK		11
#घोषणा RPM_CMD_TX_DATA_CONT		12
#घोषणा RPM_CMD_READ_NOTIF		13
#घोषणा RPM_CMD_RX_DONE_W_REUSE		14

#घोषणा GLINK_FEATURE_INTENTLESS	BIT(1)

अटल व्योम qcom_glink_rx_करोne_work(काष्ठा work_काष्ठा *work);

अटल काष्ठा glink_channel *qcom_glink_alloc_channel(काष्ठा qcom_glink *glink,
						      स्थिर अक्षर *name)
अणु
	काष्ठा glink_channel *channel;

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस ERR_PTR(-ENOMEM);

	/* Setup glink पूर्णांकernal glink_channel data */
	spin_lock_init(&channel->recv_lock);
	spin_lock_init(&channel->पूर्णांकent_lock);
	mutex_init(&channel->पूर्णांकent_req_lock);

	channel->glink = glink;
	channel->name = kstrdup(name, GFP_KERNEL);

	init_completion(&channel->खोलो_req);
	init_completion(&channel->खोलो_ack);
	init_completion(&channel->पूर्णांकent_req_comp);

	INIT_LIST_HEAD(&channel->करोne_पूर्णांकents);
	INIT_WORK(&channel->पूर्णांकent_work, qcom_glink_rx_करोne_work);

	idr_init(&channel->liids);
	idr_init(&channel->riids);
	kref_init(&channel->refcount);

	वापस channel;
पूर्ण

अटल व्योम qcom_glink_channel_release(काष्ठा kref *ref)
अणु
	काष्ठा glink_channel *channel = container_of(ref, काष्ठा glink_channel,
						     refcount);
	काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent;
	काष्ठा glink_core_rx_पूर्णांकent *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक iid;

	/* cancel pending rx_करोne work */
	cancel_work_sync(&channel->पूर्णांकent_work);

	spin_lock_irqsave(&channel->पूर्णांकent_lock, flags);
	/* Free all non-reuse पूर्णांकents pending rx_करोne work */
	list_क्रम_each_entry_safe(पूर्णांकent, पंचांगp, &channel->करोne_पूर्णांकents, node) अणु
		अगर (!पूर्णांकent->reuse) अणु
			kमुक्त(पूर्णांकent->data);
			kमुक्त(पूर्णांकent);
		पूर्ण
	पूर्ण

	idr_क्रम_each_entry(&channel->liids, पंचांगp, iid) अणु
		kमुक्त(पंचांगp->data);
		kमुक्त(पंचांगp);
	पूर्ण
	idr_destroy(&channel->liids);

	idr_क्रम_each_entry(&channel->riids, पंचांगp, iid)
		kमुक्त(पंचांगp);
	idr_destroy(&channel->riids);
	spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);

	kमुक्त(channel->name);
	kमुक्त(channel);
पूर्ण

अटल माप_प्रकार qcom_glink_rx_avail(काष्ठा qcom_glink *glink)
अणु
	वापस glink->rx_pipe->avail(glink->rx_pipe);
पूर्ण

अटल व्योम qcom_glink_rx_peak(काष्ठा qcom_glink *glink,
			       व्योम *data, अचिन्हित पूर्णांक offset, माप_प्रकार count)
अणु
	glink->rx_pipe->peak(glink->rx_pipe, data, offset, count);
पूर्ण

अटल व्योम qcom_glink_rx_advance(काष्ठा qcom_glink *glink, माप_प्रकार count)
अणु
	glink->rx_pipe->advance(glink->rx_pipe, count);
पूर्ण

अटल माप_प्रकार qcom_glink_tx_avail(काष्ठा qcom_glink *glink)
अणु
	वापस glink->tx_pipe->avail(glink->tx_pipe);
पूर्ण

अटल व्योम qcom_glink_tx_ग_लिखो(काष्ठा qcom_glink *glink,
				स्थिर व्योम *hdr, माप_प्रकार hlen,
				स्थिर व्योम *data, माप_प्रकार dlen)
अणु
	glink->tx_pipe->ग_लिखो(glink->tx_pipe, hdr, hlen, data, dlen);
पूर्ण

अटल पूर्णांक qcom_glink_tx(काष्ठा qcom_glink *glink,
			 स्थिर व्योम *hdr, माप_प्रकार hlen,
			 स्थिर व्योम *data, माप_प्रकार dlen, bool रुको)
अणु
	अचिन्हित पूर्णांक tlen = hlen + dlen;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/* Reject packets that are too big */
	अगर (tlen >= glink->tx_pipe->length)
		वापस -EINVAL;

	spin_lock_irqsave(&glink->tx_lock, flags);

	जबतक (qcom_glink_tx_avail(glink) < tlen) अणु
		अगर (!रुको) अणु
			ret = -EAGAIN;
			जाओ out;
		पूर्ण

		/* Wait without holding the tx_lock */
		spin_unlock_irqrestore(&glink->tx_lock, flags);

		usleep_range(10000, 15000);

		spin_lock_irqsave(&glink->tx_lock, flags);
	पूर्ण

	qcom_glink_tx_ग_लिखो(glink, hdr, hlen, data, dlen);

	mbox_send_message(glink->mbox_chan, शून्य);
	mbox_client_txकरोne(glink->mbox_chan, 0);

out:
	spin_unlock_irqrestore(&glink->tx_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_glink_send_version(काष्ठा qcom_glink *glink)
अणु
	काष्ठा glink_msg msg;

	msg.cmd = cpu_to_le16(RPM_CMD_VERSION);
	msg.param1 = cpu_to_le16(GLINK_VERSION_1);
	msg.param2 = cpu_to_le32(glink->features);

	वापस qcom_glink_tx(glink, &msg, माप(msg), शून्य, 0, true);
पूर्ण

अटल व्योम qcom_glink_send_version_ack(काष्ठा qcom_glink *glink)
अणु
	काष्ठा glink_msg msg;

	msg.cmd = cpu_to_le16(RPM_CMD_VERSION_ACK);
	msg.param1 = cpu_to_le16(GLINK_VERSION_1);
	msg.param2 = cpu_to_le32(glink->features);

	qcom_glink_tx(glink, &msg, माप(msg), शून्य, 0, true);
पूर्ण

अटल व्योम qcom_glink_send_खोलो_ack(काष्ठा qcom_glink *glink,
				     काष्ठा glink_channel *channel)
अणु
	काष्ठा glink_msg msg;

	msg.cmd = cpu_to_le16(RPM_CMD_OPEN_ACK);
	msg.param1 = cpu_to_le16(channel->rcid);
	msg.param2 = cpu_to_le32(0);

	qcom_glink_tx(glink, &msg, माप(msg), शून्य, 0, true);
पूर्ण

अटल व्योम qcom_glink_handle_पूर्णांकent_req_ack(काष्ठा qcom_glink *glink,
					     अचिन्हित पूर्णांक cid, bool granted)
अणु
	काष्ठा glink_channel *channel;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->rcids, cid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);
	अगर (!channel) अणु
		dev_err(glink->dev, "unable to find channel\n");
		वापस;
	पूर्ण

	channel->पूर्णांकent_req_result = granted;
	complete(&channel->पूर्णांकent_req_comp);
पूर्ण

/**
 * qcom_glink_send_खोलो_req() - send a RPM_CMD_OPEN request to the remote
 * @glink: Ptr to the glink edge
 * @channel: Ptr to the channel that the खोलो req is sent
 *
 * Allocates a local channel id and sends a RPM_CMD_OPEN message to the remote.
 * Will वापस with refcount held, regardless of outcome.
 *
 * Returns 0 on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक qcom_glink_send_खोलो_req(काष्ठा qcom_glink *glink,
				    काष्ठा glink_channel *channel)
अणु
	काष्ठा अणु
		काष्ठा glink_msg msg;
		u8 name[GLINK_NAME_SIZE];
	पूर्ण __packed req;
	पूर्णांक name_len = म_माप(channel->name) + 1;
	पूर्णांक req_len = ALIGN(माप(req.msg) + name_len, 8);
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	kref_get(&channel->refcount);

	spin_lock_irqsave(&glink->idr_lock, flags);
	ret = idr_alloc_cyclic(&glink->lcids, channel,
			       RPM_GLINK_CID_MIN, RPM_GLINK_CID_MAX,
			       GFP_ATOMIC);
	spin_unlock_irqrestore(&glink->idr_lock, flags);
	अगर (ret < 0)
		वापस ret;

	channel->lcid = ret;

	req.msg.cmd = cpu_to_le16(RPM_CMD_OPEN);
	req.msg.param1 = cpu_to_le16(channel->lcid);
	req.msg.param2 = cpu_to_le32(name_len);
	म_नकल(req.name, channel->name);

	ret = qcom_glink_tx(glink, &req, req_len, शून्य, 0, true);
	अगर (ret)
		जाओ हटाओ_idr;

	वापस 0;

हटाओ_idr:
	spin_lock_irqsave(&glink->idr_lock, flags);
	idr_हटाओ(&glink->lcids, channel->lcid);
	channel->lcid = 0;
	spin_unlock_irqrestore(&glink->idr_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम qcom_glink_send_बंद_req(काष्ठा qcom_glink *glink,
				      काष्ठा glink_channel *channel)
अणु
	काष्ठा glink_msg req;

	req.cmd = cpu_to_le16(RPM_CMD_CLOSE);
	req.param1 = cpu_to_le16(channel->lcid);
	req.param2 = 0;

	qcom_glink_tx(glink, &req, माप(req), शून्य, 0, true);
पूर्ण

अटल व्योम qcom_glink_send_बंद_ack(काष्ठा qcom_glink *glink,
				      अचिन्हित पूर्णांक rcid)
अणु
	काष्ठा glink_msg req;

	req.cmd = cpu_to_le16(RPM_CMD_CLOSE_ACK);
	req.param1 = cpu_to_le16(rcid);
	req.param2 = 0;

	qcom_glink_tx(glink, &req, माप(req), शून्य, 0, true);
पूर्ण

अटल व्योम qcom_glink_rx_करोne_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा glink_channel *channel = container_of(work, काष्ठा glink_channel,
						     पूर्णांकent_work);
	काष्ठा qcom_glink *glink = channel->glink;
	काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent, *पंचांगp;
	काष्ठा अणु
		u16 id;
		u16 lcid;
		u32 liid;
	पूर्ण __packed cmd;

	अचिन्हित पूर्णांक cid = channel->lcid;
	अचिन्हित पूर्णांक iid;
	bool reuse;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&channel->पूर्णांकent_lock, flags);
	list_क्रम_each_entry_safe(पूर्णांकent, पंचांगp, &channel->करोne_पूर्णांकents, node) अणु
		list_del(&पूर्णांकent->node);
		spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);
		iid = पूर्णांकent->id;
		reuse = पूर्णांकent->reuse;

		cmd.id = reuse ? RPM_CMD_RX_DONE_W_REUSE : RPM_CMD_RX_DONE;
		cmd.lcid = cid;
		cmd.liid = iid;

		qcom_glink_tx(glink, &cmd, माप(cmd), शून्य, 0, true);
		अगर (!reuse) अणु
			kमुक्त(पूर्णांकent->data);
			kमुक्त(पूर्णांकent);
		पूर्ण
		spin_lock_irqsave(&channel->पूर्णांकent_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);
पूर्ण

अटल व्योम qcom_glink_rx_करोne(काष्ठा qcom_glink *glink,
			       काष्ठा glink_channel *channel,
			       काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent)
अणु
	/* We करोn't send RX_DONE to पूर्णांकentless प्रणालीs */
	अगर (glink->पूर्णांकentless) अणु
		kमुक्त(पूर्णांकent->data);
		kमुक्त(पूर्णांकent);
		वापस;
	पूर्ण

	/* Take it off the tree of receive पूर्णांकents */
	अगर (!पूर्णांकent->reuse) अणु
		spin_lock(&channel->पूर्णांकent_lock);
		idr_हटाओ(&channel->liids, पूर्णांकent->id);
		spin_unlock(&channel->पूर्णांकent_lock);
	पूर्ण

	/* Schedule the sending of a rx_करोne indication */
	spin_lock(&channel->पूर्णांकent_lock);
	list_add_tail(&पूर्णांकent->node, &channel->करोne_पूर्णांकents);
	spin_unlock(&channel->पूर्णांकent_lock);

	schedule_work(&channel->पूर्णांकent_work);
पूर्ण

/**
 * qcom_glink_receive_version() - receive version/features from remote प्रणाली
 *
 * @glink:	poपूर्णांकer to transport पूर्णांकerface
 * @version:	remote version
 * @features:	remote features
 *
 * This function is called in response to a remote-initiated version/feature
 * negotiation sequence.
 */
अटल व्योम qcom_glink_receive_version(काष्ठा qcom_glink *glink,
				       u32 version,
				       u32 features)
अणु
	चयन (version) अणु
	हाल 0:
		अवरोध;
	हाल GLINK_VERSION_1:
		glink->features &= features;
		fallthrough;
	शेष:
		qcom_glink_send_version_ack(glink);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * qcom_glink_receive_version_ack() - receive negotiation ack from remote प्रणाली
 *
 * @glink:	poपूर्णांकer to transport पूर्णांकerface
 * @version:	remote version response
 * @features:	remote features response
 *
 * This function is called in response to a local-initiated version/feature
 * negotiation sequence and is the counter-offer from the remote side based
 * upon the initial version and feature set requested.
 */
अटल व्योम qcom_glink_receive_version_ack(काष्ठा qcom_glink *glink,
					   u32 version,
					   u32 features)
अणु
	चयन (version) अणु
	हाल 0:
		/* Version negotiation failed */
		अवरोध;
	हाल GLINK_VERSION_1:
		अगर (features == glink->features)
			अवरोध;

		glink->features &= features;
		fallthrough;
	शेष:
		qcom_glink_send_version(glink);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * qcom_glink_send_पूर्णांकent_req_ack() - convert an rx पूर्णांकent request ack cmd to
 * 	wire क्रमmat and transmit
 * @glink:	The transport to transmit on.
 * @channel:	The glink channel
 * @granted:	The request response to encode.
 *
 * Return: 0 on success or standard Linux error code.
 */
अटल पूर्णांक qcom_glink_send_पूर्णांकent_req_ack(काष्ठा qcom_glink *glink,
					  काष्ठा glink_channel *channel,
					  bool granted)
अणु
	काष्ठा glink_msg msg;

	msg.cmd = cpu_to_le16(RPM_CMD_RX_INTENT_REQ_ACK);
	msg.param1 = cpu_to_le16(channel->lcid);
	msg.param2 = cpu_to_le32(granted);

	qcom_glink_tx(glink, &msg, माप(msg), शून्य, 0, true);

	वापस 0;
पूर्ण

/**
 * qcom_glink_advertise_पूर्णांकent - convert an rx पूर्णांकent cmd to wire क्रमmat and
 *			   transmit
 * @glink:	The transport to transmit on.
 * @channel:	The local channel
 * @पूर्णांकent:	The पूर्णांकent to pass on to remote.
 *
 * Return: 0 on success or standard Linux error code.
 */
अटल पूर्णांक qcom_glink_advertise_पूर्णांकent(काष्ठा qcom_glink *glink,
				       काष्ठा glink_channel *channel,
				       काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent)
अणु
	काष्ठा command अणु
		__le16 id;
		__le16 lcid;
		__le32 count;
		__le32 size;
		__le32 liid;
	पूर्ण __packed;
	काष्ठा command cmd;

	cmd.id = cpu_to_le16(RPM_CMD_INTENT);
	cmd.lcid = cpu_to_le16(channel->lcid);
	cmd.count = cpu_to_le32(1);
	cmd.size = cpu_to_le32(पूर्णांकent->size);
	cmd.liid = cpu_to_le32(पूर्णांकent->id);

	qcom_glink_tx(glink, &cmd, माप(cmd), शून्य, 0, true);

	वापस 0;
पूर्ण

अटल काष्ठा glink_core_rx_पूर्णांकent *
qcom_glink_alloc_पूर्णांकent(काष्ठा qcom_glink *glink,
			काष्ठा glink_channel *channel,
			माप_प्रकार size,
			bool reuseable)
अणु
	काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	पूर्णांकent = kzalloc(माप(*पूर्णांकent), GFP_KERNEL);
	अगर (!पूर्णांकent)
		वापस शून्य;

	पूर्णांकent->data = kzalloc(size, GFP_KERNEL);
	अगर (!पूर्णांकent->data)
		जाओ मुक्त_पूर्णांकent;

	spin_lock_irqsave(&channel->पूर्णांकent_lock, flags);
	ret = idr_alloc_cyclic(&channel->liids, पूर्णांकent, 1, -1, GFP_ATOMIC);
	अगर (ret < 0) अणु
		spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);
		जाओ मुक्त_data;
	पूर्ण
	spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);

	पूर्णांकent->id = ret;
	पूर्णांकent->size = size;
	पूर्णांकent->reuse = reuseable;

	वापस पूर्णांकent;

मुक्त_data:
	kमुक्त(पूर्णांकent->data);
मुक्त_पूर्णांकent:
	kमुक्त(पूर्णांकent);
	वापस शून्य;
पूर्ण

अटल व्योम qcom_glink_handle_rx_करोne(काष्ठा qcom_glink *glink,
				      u32 cid, uपूर्णांक32_t iid,
				      bool reuse)
अणु
	काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent;
	काष्ठा glink_channel *channel;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->rcids, cid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);
	अगर (!channel) अणु
		dev_err(glink->dev, "invalid channel id received\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&channel->पूर्णांकent_lock, flags);
	पूर्णांकent = idr_find(&channel->riids, iid);

	अगर (!पूर्णांकent) अणु
		spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);
		dev_err(glink->dev, "invalid intent id received\n");
		वापस;
	पूर्ण

	पूर्णांकent->in_use = false;

	अगर (!reuse) अणु
		idr_हटाओ(&channel->riids, पूर्णांकent->id);
		kमुक्त(पूर्णांकent);
	पूर्ण
	spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);
पूर्ण

/**
 * qcom_glink_handle_पूर्णांकent_req() - Receive a request क्रम rx_पूर्णांकent
 *					    from remote side
 * @glink:      Poपूर्णांकer to the transport पूर्णांकerface
 * @cid:	Remote channel ID
 * @size:	size of the पूर्णांकent
 *
 * The function searches क्रम the local channel to which the request क्रम
 * rx_पूर्णांकent has arrived and allocates and notअगरies the remote back
 */
अटल व्योम qcom_glink_handle_पूर्णांकent_req(काष्ठा qcom_glink *glink,
					 u32 cid, माप_प्रकार size)
अणु
	काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent;
	काष्ठा glink_channel *channel;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->rcids, cid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);

	अगर (!channel) अणु
		pr_err("%s channel not found for cid %d\n", __func__, cid);
		वापस;
	पूर्ण

	पूर्णांकent = qcom_glink_alloc_पूर्णांकent(glink, channel, size, false);
	अगर (पूर्णांकent)
		qcom_glink_advertise_पूर्णांकent(glink, channel, पूर्णांकent);

	qcom_glink_send_पूर्णांकent_req_ack(glink, channel, !!पूर्णांकent);
पूर्ण

अटल पूर्णांक qcom_glink_rx_defer(काष्ठा qcom_glink *glink, माप_प्रकार extra)
अणु
	काष्ठा glink_defer_cmd *dcmd;

	extra = ALIGN(extra, 8);

	अगर (qcom_glink_rx_avail(glink) < माप(काष्ठा glink_msg) + extra) अणु
		dev_dbg(glink->dev, "Insufficient data in rx fifo");
		वापस -ENXIO;
	पूर्ण

	dcmd = kzalloc(माप(*dcmd) + extra, GFP_ATOMIC);
	अगर (!dcmd)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&dcmd->node);

	qcom_glink_rx_peak(glink, &dcmd->msg, 0, माप(dcmd->msg) + extra);

	spin_lock(&glink->rx_lock);
	list_add_tail(&dcmd->node, &glink->rx_queue);
	spin_unlock(&glink->rx_lock);

	schedule_work(&glink->rx_work);
	qcom_glink_rx_advance(glink, माप(dcmd->msg) + extra);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_glink_rx_data(काष्ठा qcom_glink *glink, माप_प्रकार avail)
अणु
	काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent;
	काष्ठा glink_channel *channel;
	काष्ठा अणु
		काष्ठा glink_msg msg;
		__le32 chunk_size;
		__le32 left_size;
	पूर्ण __packed hdr;
	अचिन्हित पूर्णांक chunk_size;
	अचिन्हित पूर्णांक left_size;
	अचिन्हित पूर्णांक rcid;
	अचिन्हित पूर्णांक liid;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	अगर (avail < माप(hdr)) अणु
		dev_dbg(glink->dev, "Not enough data in fifo\n");
		वापस -EAGAIN;
	पूर्ण

	qcom_glink_rx_peak(glink, &hdr, 0, माप(hdr));
	chunk_size = le32_to_cpu(hdr.chunk_size);
	left_size = le32_to_cpu(hdr.left_size);

	अगर (avail < माप(hdr) + chunk_size) अणु
		dev_dbg(glink->dev, "Payload not yet in fifo\n");
		वापस -EAGAIN;
	पूर्ण

	rcid = le16_to_cpu(hdr.msg.param1);
	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->rcids, rcid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);
	अगर (!channel) अणु
		dev_dbg(glink->dev, "Data on non-existing channel\n");

		/* Drop the message */
		जाओ advance_rx;
	पूर्ण

	अगर (glink->पूर्णांकentless) अणु
		/* Might have an ongoing, fragmented, message to append */
		अगर (!channel->buf) अणु
			पूर्णांकent = kzalloc(माप(*पूर्णांकent), GFP_ATOMIC);
			अगर (!पूर्णांकent)
				वापस -ENOMEM;

			पूर्णांकent->data = kदो_स्मृति(chunk_size + left_size,
					       GFP_ATOMIC);
			अगर (!पूर्णांकent->data) अणु
				kमुक्त(पूर्णांकent);
				वापस -ENOMEM;
			पूर्ण

			पूर्णांकent->id = 0xbabababa;
			पूर्णांकent->size = chunk_size + left_size;
			पूर्णांकent->offset = 0;

			channel->buf = पूर्णांकent;
		पूर्ण अन्यथा अणु
			पूर्णांकent = channel->buf;
		पूर्ण
	पूर्ण अन्यथा अणु
		liid = le32_to_cpu(hdr.msg.param2);

		spin_lock_irqsave(&channel->पूर्णांकent_lock, flags);
		पूर्णांकent = idr_find(&channel->liids, liid);
		spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);

		अगर (!पूर्णांकent) अणु
			dev_err(glink->dev,
				"no intent found for channel %s intent %d",
				channel->name, liid);
			ret = -ENOENT;
			जाओ advance_rx;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकent->size - पूर्णांकent->offset < chunk_size) अणु
		dev_err(glink->dev, "Insufficient space in intent\n");

		/* The packet header lied, drop payload */
		जाओ advance_rx;
	पूर्ण

	qcom_glink_rx_peak(glink, पूर्णांकent->data + पूर्णांकent->offset,
			   माप(hdr), chunk_size);
	पूर्णांकent->offset += chunk_size;

	/* Handle message when no fragments reमुख्य to be received */
	अगर (!left_size) अणु
		spin_lock(&channel->recv_lock);
		अगर (channel->ept.cb) अणु
			channel->ept.cb(channel->ept.rpdev,
					पूर्णांकent->data,
					पूर्णांकent->offset,
					channel->ept.priv,
					RPMSG_ADDR_ANY);
		पूर्ण
		spin_unlock(&channel->recv_lock);

		पूर्णांकent->offset = 0;
		channel->buf = शून्य;

		qcom_glink_rx_करोne(glink, channel, पूर्णांकent);
	पूर्ण

advance_rx:
	qcom_glink_rx_advance(glink, ALIGN(माप(hdr) + chunk_size, 8));

	वापस ret;
पूर्ण

अटल व्योम qcom_glink_handle_पूर्णांकent(काष्ठा qcom_glink *glink,
				     अचिन्हित पूर्णांक cid,
				     अचिन्हित पूर्णांक count,
				     माप_प्रकार avail)
अणु
	काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent;
	काष्ठा glink_channel *channel;
	काष्ठा पूर्णांकent_pair अणु
		__le32 size;
		__le32 iid;
	पूर्ण;

	काष्ठा अणु
		काष्ठा glink_msg msg;
		काष्ठा पूर्णांकent_pair पूर्णांकents[];
	पूर्ण __packed * msg;

	स्थिर माप_प्रकार msglen = काष्ठा_size(msg, पूर्णांकents, count);
	पूर्णांक ret;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (avail < msglen) अणु
		dev_dbg(glink->dev, "Not enough data in fifo\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->rcids, cid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);
	अगर (!channel) अणु
		dev_err(glink->dev, "intents for non-existing channel\n");
		वापस;
	पूर्ण

	msg = kदो_स्मृति(msglen, GFP_ATOMIC);
	अगर (!msg)
		वापस;

	qcom_glink_rx_peak(glink, msg, 0, msglen);

	क्रम (i = 0; i < count; ++i) अणु
		पूर्णांकent = kzalloc(माप(*पूर्णांकent), GFP_ATOMIC);
		अगर (!पूर्णांकent)
			अवरोध;

		पूर्णांकent->id = le32_to_cpu(msg->पूर्णांकents[i].iid);
		पूर्णांकent->size = le32_to_cpu(msg->पूर्णांकents[i].size);

		spin_lock_irqsave(&channel->पूर्णांकent_lock, flags);
		ret = idr_alloc(&channel->riids, पूर्णांकent,
				पूर्णांकent->id, पूर्णांकent->id + 1, GFP_ATOMIC);
		spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);

		अगर (ret < 0)
			dev_err(glink->dev, "failed to store remote intent\n");
	पूर्ण

	kमुक्त(msg);
	qcom_glink_rx_advance(glink, ALIGN(msglen, 8));
पूर्ण

अटल पूर्णांक qcom_glink_rx_खोलो_ack(काष्ठा qcom_glink *glink, अचिन्हित पूर्णांक lcid)
अणु
	काष्ठा glink_channel *channel;

	spin_lock(&glink->idr_lock);
	channel = idr_find(&glink->lcids, lcid);
	spin_unlock(&glink->idr_lock);
	अगर (!channel) अणु
		dev_err(glink->dev, "Invalid open ack packet\n");
		वापस -EINVAL;
	पूर्ण

	complete_all(&channel->खोलो_ack);

	वापस 0;
पूर्ण

अटल irqवापस_t qcom_glink_native_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcom_glink *glink = data;
	काष्ठा glink_msg msg;
	अचिन्हित पूर्णांक param1;
	अचिन्हित पूर्णांक param2;
	अचिन्हित पूर्णांक avail;
	अचिन्हित पूर्णांक cmd;
	पूर्णांक ret = 0;

	क्रम (;;) अणु
		avail = qcom_glink_rx_avail(glink);
		अगर (avail < माप(msg))
			अवरोध;

		qcom_glink_rx_peak(glink, &msg, 0, माप(msg));

		cmd = le16_to_cpu(msg.cmd);
		param1 = le16_to_cpu(msg.param1);
		param2 = le32_to_cpu(msg.param2);

		चयन (cmd) अणु
		हाल RPM_CMD_VERSION:
		हाल RPM_CMD_VERSION_ACK:
		हाल RPM_CMD_CLOSE:
		हाल RPM_CMD_CLOSE_ACK:
		हाल RPM_CMD_RX_INTENT_REQ:
			ret = qcom_glink_rx_defer(glink, 0);
			अवरोध;
		हाल RPM_CMD_OPEN_ACK:
			ret = qcom_glink_rx_खोलो_ack(glink, param1);
			qcom_glink_rx_advance(glink, ALIGN(माप(msg), 8));
			अवरोध;
		हाल RPM_CMD_OPEN:
			ret = qcom_glink_rx_defer(glink, param2);
			अवरोध;
		हाल RPM_CMD_TX_DATA:
		हाल RPM_CMD_TX_DATA_CONT:
			ret = qcom_glink_rx_data(glink, avail);
			अवरोध;
		हाल RPM_CMD_READ_NOTIF:
			qcom_glink_rx_advance(glink, ALIGN(माप(msg), 8));

			mbox_send_message(glink->mbox_chan, शून्य);
			mbox_client_txकरोne(glink->mbox_chan, 0);
			अवरोध;
		हाल RPM_CMD_INTENT:
			qcom_glink_handle_पूर्णांकent(glink, param1, param2, avail);
			अवरोध;
		हाल RPM_CMD_RX_DONE:
			qcom_glink_handle_rx_करोne(glink, param1, param2, false);
			qcom_glink_rx_advance(glink, ALIGN(माप(msg), 8));
			अवरोध;
		हाल RPM_CMD_RX_DONE_W_REUSE:
			qcom_glink_handle_rx_करोne(glink, param1, param2, true);
			qcom_glink_rx_advance(glink, ALIGN(माप(msg), 8));
			अवरोध;
		हाल RPM_CMD_RX_INTENT_REQ_ACK:
			qcom_glink_handle_पूर्णांकent_req_ack(glink, param1, param2);
			qcom_glink_rx_advance(glink, ALIGN(माप(msg), 8));
			अवरोध;
		शेष:
			dev_err(glink->dev, "unhandled rx cmd: %d\n", cmd);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (ret)
			अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* Locally initiated rpmsg_create_ept */
अटल काष्ठा glink_channel *qcom_glink_create_local(काष्ठा qcom_glink *glink,
						     स्थिर अक्षर *name)
अणु
	काष्ठा glink_channel *channel;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	channel = qcom_glink_alloc_channel(glink, name);
	अगर (IS_ERR(channel))
		वापस ERR_CAST(channel);

	ret = qcom_glink_send_खोलो_req(glink, channel);
	अगर (ret)
		जाओ release_channel;

	ret = रुको_क्रम_completion_समयout(&channel->खोलो_ack, 5 * HZ);
	अगर (!ret)
		जाओ err_समयout;

	ret = रुको_क्रम_completion_समयout(&channel->खोलो_req, 5 * HZ);
	अगर (!ret)
		जाओ err_समयout;

	qcom_glink_send_खोलो_ack(glink, channel);

	वापस channel;

err_समयout:
	/* qcom_glink_send_खोलो_req() did रेजिस्टर the channel in lcids*/
	spin_lock_irqsave(&glink->idr_lock, flags);
	idr_हटाओ(&glink->lcids, channel->lcid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);

release_channel:
	/* Release qcom_glink_send_खोलो_req() reference */
	kref_put(&channel->refcount, qcom_glink_channel_release);
	/* Release qcom_glink_alloc_channel() reference */
	kref_put(&channel->refcount, qcom_glink_channel_release);

	वापस ERR_PTR(-ETIMEDOUT);
पूर्ण

/* Remote initiated rpmsg_create_ept */
अटल पूर्णांक qcom_glink_create_remote(काष्ठा qcom_glink *glink,
				    काष्ठा glink_channel *channel)
अणु
	पूर्णांक ret;

	qcom_glink_send_खोलो_ack(glink, channel);

	ret = qcom_glink_send_खोलो_req(glink, channel);
	अगर (ret)
		जाओ बंद_link;

	ret = रुको_क्रम_completion_समयout(&channel->खोलो_ack, 5 * HZ);
	अगर (!ret) अणु
		ret = -ETIMEDOUT;
		जाओ बंद_link;
	पूर्ण

	वापस 0;

बंद_link:
	/*
	 * Send a बंद request to "undo" our खोलो-ack. The बंद-ack will
	 * release qcom_glink_send_खोलो_req() reference and the last reference
	 * will be relesed after receiving remote_बंद or transport unरेजिस्टर
	 * by calling qcom_glink_native_हटाओ().
	 */
	qcom_glink_send_बंद_req(glink, channel);

	वापस ret;
पूर्ण

अटल काष्ठा rpmsg_endpoपूर्णांक *qcom_glink_create_ept(काष्ठा rpmsg_device *rpdev,
						    rpmsg_rx_cb_t cb,
						    व्योम *priv,
						    काष्ठा rpmsg_channel_info
									chinfo)
अणु
	काष्ठा glink_channel *parent = to_glink_channel(rpdev->ept);
	काष्ठा glink_channel *channel;
	काष्ठा qcom_glink *glink = parent->glink;
	काष्ठा rpmsg_endpoपूर्णांक *ept;
	स्थिर अक्षर *name = chinfo.name;
	पूर्णांक cid;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	idr_क्रम_each_entry(&glink->rcids, channel, cid) अणु
		अगर (!म_भेद(channel->name, name))
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&glink->idr_lock, flags);

	अगर (!channel) अणु
		channel = qcom_glink_create_local(glink, name);
		अगर (IS_ERR(channel))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		ret = qcom_glink_create_remote(glink, channel);
		अगर (ret)
			वापस शून्य;
	पूर्ण

	ept = &channel->ept;
	ept->rpdev = rpdev;
	ept->cb = cb;
	ept->priv = priv;
	ept->ops = &glink_endpoपूर्णांक_ops;

	वापस ept;
पूर्ण

अटल पूर्णांक qcom_glink_announce_create(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा glink_channel *channel = to_glink_channel(rpdev->ept);
	काष्ठा device_node *np = rpdev->dev.of_node;
	काष्ठा qcom_glink *glink = channel->glink;
	काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent;
	स्थिर काष्ठा property *prop = शून्य;
	__be32 शेषs[] = अणु cpu_to_be32(SZ_1K), cpu_to_be32(5) पूर्ण;
	पूर्णांक num_पूर्णांकents;
	पूर्णांक num_groups = 1;
	__be32 *val = शेषs;
	पूर्णांक size;

	अगर (glink->पूर्णांकentless || !completion_करोne(&channel->खोलो_ack))
		वापस 0;

	prop = of_find_property(np, "qcom,intents", शून्य);
	अगर (prop) अणु
		val = prop->value;
		num_groups = prop->length / माप(u32) / 2;
	पूर्ण

	/* Channel is now खोलो, advertise base set of पूर्णांकents */
	जबतक (num_groups--) अणु
		size = be32_to_cpup(val++);
		num_पूर्णांकents = be32_to_cpup(val++);
		जबतक (num_पूर्णांकents--) अणु
			पूर्णांकent = qcom_glink_alloc_पूर्णांकent(glink, channel, size,
							 true);
			अगर (!पूर्णांकent)
				अवरोध;

			qcom_glink_advertise_पूर्णांकent(glink, channel, पूर्णांकent);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qcom_glink_destroy_ept(काष्ठा rpmsg_endpoपूर्णांक *ept)
अणु
	काष्ठा glink_channel *channel = to_glink_channel(ept);
	काष्ठा qcom_glink *glink = channel->glink;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&channel->recv_lock, flags);
	channel->ept.cb = शून्य;
	spin_unlock_irqrestore(&channel->recv_lock, flags);

	/* Decouple the potential rpdev from the channel */
	channel->rpdev = शून्य;

	qcom_glink_send_बंद_req(glink, channel);
पूर्ण

अटल पूर्णांक qcom_glink_request_पूर्णांकent(काष्ठा qcom_glink *glink,
				     काष्ठा glink_channel *channel,
				     माप_प्रकार size)
अणु
	काष्ठा अणु
		u16 id;
		u16 cid;
		u32 size;
	पूर्ण __packed cmd;

	पूर्णांक ret;

	mutex_lock(&channel->पूर्णांकent_req_lock);

	reinit_completion(&channel->पूर्णांकent_req_comp);

	cmd.id = RPM_CMD_RX_INTENT_REQ;
	cmd.cid = channel->lcid;
	cmd.size = size;

	ret = qcom_glink_tx(glink, &cmd, माप(cmd), शून्य, 0, true);
	अगर (ret)
		जाओ unlock;

	ret = रुको_क्रम_completion_समयout(&channel->पूर्णांकent_req_comp, 10 * HZ);
	अगर (!ret) अणु
		dev_err(glink->dev, "intent request timed out\n");
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ret = channel->पूर्णांकent_req_result ? 0 : -ECANCELED;
	पूर्ण

unlock:
	mutex_unlock(&channel->पूर्णांकent_req_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक __qcom_glink_send(काष्ठा glink_channel *channel,
			     व्योम *data, पूर्णांक len, bool रुको)
अणु
	काष्ठा qcom_glink *glink = channel->glink;
	काष्ठा glink_core_rx_पूर्णांकent *पूर्णांकent = शून्य;
	काष्ठा glink_core_rx_पूर्णांकent *पंचांगp;
	पूर्णांक iid = 0;
	काष्ठा अणु
		काष्ठा glink_msg msg;
		__le32 chunk_size;
		__le32 left_size;
	पूर्ण __packed req;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (!glink->पूर्णांकentless) अणु
		जबतक (!पूर्णांकent) अणु
			spin_lock_irqsave(&channel->पूर्णांकent_lock, flags);
			idr_क्रम_each_entry(&channel->riids, पंचांगp, iid) अणु
				अगर (पंचांगp->size >= len && !पंचांगp->in_use) अणु
					अगर (!पूर्णांकent)
						पूर्णांकent = पंचांगp;
					अन्यथा अगर (पूर्णांकent->size > पंचांगp->size)
						पूर्णांकent = पंचांगp;
					अगर (पूर्णांकent->size == len)
						अवरोध;
				पूर्ण
			पूर्ण
			अगर (पूर्णांकent)
				पूर्णांकent->in_use = true;
			spin_unlock_irqrestore(&channel->पूर्णांकent_lock, flags);

			/* We found an available पूर्णांकent */
			अगर (पूर्णांकent)
				अवरोध;

			अगर (!रुको)
				वापस -EBUSY;

			ret = qcom_glink_request_पूर्णांकent(glink, channel, len);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		iid = पूर्णांकent->id;
	पूर्ण

	req.msg.cmd = cpu_to_le16(RPM_CMD_TX_DATA);
	req.msg.param1 = cpu_to_le16(channel->lcid);
	req.msg.param2 = cpu_to_le32(iid);
	req.chunk_size = cpu_to_le32(len);
	req.left_size = cpu_to_le32(0);

	ret = qcom_glink_tx(glink, &req, माप(req), data, len, रुको);

	/* Mark पूर्णांकent available अगर we failed */
	अगर (ret && पूर्णांकent)
		पूर्णांकent->in_use = false;

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_glink_send(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	काष्ठा glink_channel *channel = to_glink_channel(ept);

	वापस __qcom_glink_send(channel, data, len, true);
पूर्ण

अटल पूर्णांक qcom_glink_trysend(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	काष्ठा glink_channel *channel = to_glink_channel(ept);

	वापस __qcom_glink_send(channel, data, len, false);
पूर्ण

अटल पूर्णांक qcom_glink_sendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst)
अणु
	काष्ठा glink_channel *channel = to_glink_channel(ept);

	वापस __qcom_glink_send(channel, data, len, true);
पूर्ण

अटल पूर्णांक qcom_glink_trysendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst)
अणु
	काष्ठा glink_channel *channel = to_glink_channel(ept);

	वापस __qcom_glink_send(channel, data, len, false);
पूर्ण

/*
 * Finds the device_node क्रम the glink child पूर्णांकerested in this channel.
 */
अटल काष्ठा device_node *qcom_glink_match_channel(काष्ठा device_node *node,
						    स्थिर अक्षर *channel)
अणु
	काष्ठा device_node *child;
	स्थिर अक्षर *name;
	स्थिर अक्षर *key;
	पूर्णांक ret;

	क्रम_each_available_child_of_node(node, child) अणु
		key = "qcom,glink-channels";
		ret = of_property_पढ़ो_string(child, key, &name);
		अगर (ret)
			जारी;

		अगर (म_भेद(name, channel) == 0)
			वापस child;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा rpmsg_device_ops glink_device_ops = अणु
	.create_ept = qcom_glink_create_ept,
	.announce_create = qcom_glink_announce_create,
पूर्ण;

अटल स्थिर काष्ठा rpmsg_endpoपूर्णांक_ops glink_endpoपूर्णांक_ops = अणु
	.destroy_ept = qcom_glink_destroy_ept,
	.send = qcom_glink_send,
	.sendto = qcom_glink_sendto,
	.trysend = qcom_glink_trysend,
	.trysendto = qcom_glink_trysendto,
पूर्ण;

अटल व्योम qcom_glink_rpdev_release(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	काष्ठा glink_channel *channel = to_glink_channel(rpdev->ept);

	channel->rpdev = शून्य;
	kमुक्त(rpdev);
पूर्ण

अटल पूर्णांक qcom_glink_rx_खोलो(काष्ठा qcom_glink *glink, अचिन्हित पूर्णांक rcid,
			      अक्षर *name)
अणु
	काष्ठा glink_channel *channel;
	काष्ठा rpmsg_device *rpdev;
	bool create_device = false;
	काष्ठा device_node *node;
	पूर्णांक lcid;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	idr_क्रम_each_entry(&glink->lcids, channel, lcid) अणु
		अगर (!म_भेद(channel->name, name))
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&glink->idr_lock, flags);

	अगर (!channel) अणु
		channel = qcom_glink_alloc_channel(glink, name);
		अगर (IS_ERR(channel))
			वापस PTR_ERR(channel);

		/* The खोलोing dance was initiated by the remote */
		create_device = true;
	पूर्ण

	spin_lock_irqsave(&glink->idr_lock, flags);
	ret = idr_alloc(&glink->rcids, channel, rcid, rcid + 1, GFP_ATOMIC);
	अगर (ret < 0) अणु
		dev_err(glink->dev, "Unable to insert channel into rcid list\n");
		spin_unlock_irqrestore(&glink->idr_lock, flags);
		जाओ मुक्त_channel;
	पूर्ण
	channel->rcid = ret;
	spin_unlock_irqrestore(&glink->idr_lock, flags);

	complete_all(&channel->खोलो_req);

	अगर (create_device) अणु
		rpdev = kzalloc(माप(*rpdev), GFP_KERNEL);
		अगर (!rpdev) अणु
			ret = -ENOMEM;
			जाओ rcid_हटाओ;
		पूर्ण

		rpdev->ept = &channel->ept;
		म_नकलन(rpdev->id.name, name, RPMSG_NAME_SIZE);
		rpdev->src = RPMSG_ADDR_ANY;
		rpdev->dst = RPMSG_ADDR_ANY;
		rpdev->ops = &glink_device_ops;

		node = qcom_glink_match_channel(glink->dev->of_node, name);
		rpdev->dev.of_node = node;
		rpdev->dev.parent = glink->dev;
		rpdev->dev.release = qcom_glink_rpdev_release;

		ret = rpmsg_रेजिस्टर_device(rpdev);
		अगर (ret)
			जाओ rcid_हटाओ;

		channel->rpdev = rpdev;
	पूर्ण

	वापस 0;

rcid_हटाओ:
	spin_lock_irqsave(&glink->idr_lock, flags);
	idr_हटाओ(&glink->rcids, channel->rcid);
	channel->rcid = 0;
	spin_unlock_irqrestore(&glink->idr_lock, flags);
मुक्त_channel:
	/* Release the reference, अगरf we took it */
	अगर (create_device)
		kref_put(&channel->refcount, qcom_glink_channel_release);

	वापस ret;
पूर्ण

अटल व्योम qcom_glink_rx_बंद(काष्ठा qcom_glink *glink, अचिन्हित पूर्णांक rcid)
अणु
	काष्ठा rpmsg_channel_info chinfo;
	काष्ठा glink_channel *channel;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->rcids, rcid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);
	अगर (WARN(!channel, "close request on unknown channel\n"))
		वापस;

	/* cancel pending rx_करोne work */
	cancel_work_sync(&channel->पूर्णांकent_work);

	अगर (channel->rpdev) अणु
		म_नकलन(chinfo.name, channel->name, माप(chinfo.name));
		chinfo.src = RPMSG_ADDR_ANY;
		chinfo.dst = RPMSG_ADDR_ANY;

		rpmsg_unरेजिस्टर_device(glink->dev, &chinfo);
	पूर्ण

	qcom_glink_send_बंद_ack(glink, channel->rcid);

	spin_lock_irqsave(&glink->idr_lock, flags);
	idr_हटाओ(&glink->rcids, channel->rcid);
	channel->rcid = 0;
	spin_unlock_irqrestore(&glink->idr_lock, flags);

	kref_put(&channel->refcount, qcom_glink_channel_release);
पूर्ण

अटल व्योम qcom_glink_rx_बंद_ack(काष्ठा qcom_glink *glink, अचिन्हित पूर्णांक lcid)
अणु
	काष्ठा glink_channel *channel;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->lcids, lcid);
	अगर (WARN(!channel, "close ack on unknown channel\n")) अणु
		spin_unlock_irqrestore(&glink->idr_lock, flags);
		वापस;
	पूर्ण

	idr_हटाओ(&glink->lcids, channel->lcid);
	channel->lcid = 0;
	spin_unlock_irqrestore(&glink->idr_lock, flags);

	kref_put(&channel->refcount, qcom_glink_channel_release);
पूर्ण

अटल व्योम qcom_glink_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qcom_glink *glink = container_of(work, काष्ठा qcom_glink,
						rx_work);
	काष्ठा glink_defer_cmd *dcmd;
	काष्ठा glink_msg *msg;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक param1;
	अचिन्हित पूर्णांक param2;
	अचिन्हित पूर्णांक cmd;

	क्रम (;;) अणु
		spin_lock_irqsave(&glink->rx_lock, flags);
		अगर (list_empty(&glink->rx_queue)) अणु
			spin_unlock_irqrestore(&glink->rx_lock, flags);
			अवरोध;
		पूर्ण
		dcmd = list_first_entry(&glink->rx_queue,
					काष्ठा glink_defer_cmd, node);
		list_del(&dcmd->node);
		spin_unlock_irqrestore(&glink->rx_lock, flags);

		msg = &dcmd->msg;
		cmd = le16_to_cpu(msg->cmd);
		param1 = le16_to_cpu(msg->param1);
		param2 = le32_to_cpu(msg->param2);

		चयन (cmd) अणु
		हाल RPM_CMD_VERSION:
			qcom_glink_receive_version(glink, param1, param2);
			अवरोध;
		हाल RPM_CMD_VERSION_ACK:
			qcom_glink_receive_version_ack(glink, param1, param2);
			अवरोध;
		हाल RPM_CMD_OPEN:
			qcom_glink_rx_खोलो(glink, param1, msg->data);
			अवरोध;
		हाल RPM_CMD_CLOSE:
			qcom_glink_rx_बंद(glink, param1);
			अवरोध;
		हाल RPM_CMD_CLOSE_ACK:
			qcom_glink_rx_बंद_ack(glink, param1);
			अवरोध;
		हाल RPM_CMD_RX_INTENT_REQ:
			qcom_glink_handle_पूर्णांकent_req(glink, param1, param2);
			अवरोध;
		शेष:
			WARN(1, "Unknown defer object %d\n", cmd);
			अवरोध;
		पूर्ण

		kमुक्त(dcmd);
	पूर्ण
पूर्ण

अटल व्योम qcom_glink_cancel_rx_work(काष्ठा qcom_glink *glink)
अणु
	काष्ठा glink_defer_cmd *dcmd;
	काष्ठा glink_defer_cmd *पंचांगp;

	/* cancel any pending deferred rx_work */
	cancel_work_sync(&glink->rx_work);

	list_क्रम_each_entry_safe(dcmd, पंचांगp, &glink->rx_queue, node)
		kमुक्त(dcmd);
पूर्ण

अटल sमाप_प्रकार rpmsg_name_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret = 0;
	स्थिर अक्षर *name;

	ret = of_property_पढ़ो_string(dev->of_node, "label", &name);
	अगर (ret < 0)
		name = dev->of_node->name;

	वापस snम_लिखो(buf, RPMSG_NAME_SIZE, "%s\n", name);
पूर्ण
अटल DEVICE_ATTR_RO(rpmsg_name);

अटल काष्ठा attribute *qcom_glink_attrs[] = अणु
	&dev_attr_rpmsg_name.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(qcom_glink);

अटल व्योम qcom_glink_device_release(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	काष्ठा glink_channel *channel = to_glink_channel(rpdev->ept);

	/* Release qcom_glink_alloc_channel() reference */
	kref_put(&channel->refcount, qcom_glink_channel_release);
	kमुक्त(rpdev);
पूर्ण

अटल पूर्णांक qcom_glink_create_chrdev(काष्ठा qcom_glink *glink)
अणु
	काष्ठा rpmsg_device *rpdev;
	काष्ठा glink_channel *channel;

	rpdev = kzalloc(माप(*rpdev), GFP_KERNEL);
	अगर (!rpdev)
		वापस -ENOMEM;

	channel = qcom_glink_alloc_channel(glink, "rpmsg_chrdev");
	अगर (IS_ERR(channel)) अणु
		kमुक्त(rpdev);
		वापस PTR_ERR(channel);
	पूर्ण
	channel->rpdev = rpdev;

	rpdev->ept = &channel->ept;
	rpdev->ops = &glink_device_ops;
	rpdev->dev.parent = glink->dev;
	rpdev->dev.release = qcom_glink_device_release;

	वापस rpmsg_chrdev_रेजिस्टर_device(rpdev);
पूर्ण

काष्ठा qcom_glink *qcom_glink_native_probe(काष्ठा device *dev,
					   अचिन्हित दीर्घ features,
					   काष्ठा qcom_glink_pipe *rx,
					   काष्ठा qcom_glink_pipe *tx,
					   bool पूर्णांकentless)
अणु
	पूर्णांक irq;
	पूर्णांक ret;
	काष्ठा qcom_glink *glink;

	glink = devm_kzalloc(dev, माप(*glink), GFP_KERNEL);
	अगर (!glink)
		वापस ERR_PTR(-ENOMEM);

	glink->dev = dev;
	glink->tx_pipe = tx;
	glink->rx_pipe = rx;

	glink->features = features;
	glink->पूर्णांकentless = पूर्णांकentless;

	spin_lock_init(&glink->tx_lock);
	spin_lock_init(&glink->rx_lock);
	INIT_LIST_HEAD(&glink->rx_queue);
	INIT_WORK(&glink->rx_work, qcom_glink_work);

	spin_lock_init(&glink->idr_lock);
	idr_init(&glink->lcids);
	idr_init(&glink->rcids);

	glink->dev->groups = qcom_glink_groups;

	ret = device_add_groups(dev, qcom_glink_groups);
	अगर (ret)
		dev_err(dev, "failed to add groups\n");

	ret = of_property_पढ़ो_string(dev->of_node, "label", &glink->name);
	अगर (ret < 0)
		glink->name = dev->of_node->name;

	glink->mbox_client.dev = dev;
	glink->mbox_client.knows_txकरोne = true;
	glink->mbox_chan = mbox_request_channel(&glink->mbox_client, 0);
	अगर (IS_ERR(glink->mbox_chan)) अणु
		अगर (PTR_ERR(glink->mbox_chan) != -EPROBE_DEFER)
			dev_err(dev, "failed to acquire IPC channel\n");
		वापस ERR_CAST(glink->mbox_chan);
	पूर्ण

	irq = of_irq_get(dev->of_node, 0);
	ret = devm_request_irq(dev, irq,
			       qcom_glink_native_पूर्णांकr,
			       IRQF_NO_SUSPEND | IRQF_SHARED,
			       "glink-native", glink);
	अगर (ret) अणु
		dev_err(dev, "failed to request IRQ\n");
		वापस ERR_PTR(ret);
	पूर्ण

	glink->irq = irq;

	ret = qcom_glink_send_version(glink);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = qcom_glink_create_chrdev(glink);
	अगर (ret)
		dev_err(glink->dev, "failed to register chrdev\n");

	वापस glink;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_glink_native_probe);

अटल पूर्णांक qcom_glink_हटाओ_device(काष्ठा device *dev, व्योम *data)
अणु
	device_unरेजिस्टर(dev);

	वापस 0;
पूर्ण

व्योम qcom_glink_native_हटाओ(काष्ठा qcom_glink *glink)
अणु
	काष्ठा glink_channel *channel;
	पूर्णांक cid;
	पूर्णांक ret;

	disable_irq(glink->irq);
	qcom_glink_cancel_rx_work(glink);

	ret = device_क्रम_each_child(glink->dev, शून्य, qcom_glink_हटाओ_device);
	अगर (ret)
		dev_warn(glink->dev, "Can't remove GLINK devices: %d\n", ret);

	/* Release any defunct local channels, रुकोing क्रम बंद-ack */
	idr_क्रम_each_entry(&glink->lcids, channel, cid)
		kref_put(&channel->refcount, qcom_glink_channel_release);

	/* Release any defunct local channels, रुकोing क्रम बंद-req */
	idr_क्रम_each_entry(&glink->rcids, channel, cid)
		kref_put(&channel->refcount, qcom_glink_channel_release);

	idr_destroy(&glink->lcids);
	idr_destroy(&glink->rcids);
	mbox_मुक्त_channel(glink->mbox_chan);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_glink_native_हटाओ);

व्योम qcom_glink_native_unरेजिस्टर(काष्ठा qcom_glink *glink)
अणु
	device_unरेजिस्टर(glink->dev);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_glink_native_unरेजिस्टर);

MODULE_DESCRIPTION("Qualcomm GLINK driver");
MODULE_LICENSE("GPL v2");
