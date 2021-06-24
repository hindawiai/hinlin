<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Message Protocol driver
 *
 * SCMI Message Protocol is used between the System Control Processor(SCP)
 * and the Application Processors(AP). The Message Handling Unit(MHU)
 * provides a mechanism क्रम पूर्णांकer-processor communication between SCP's
 * Cortex M3 and AP.
 *
 * SCP offers control and management of the core/cluster घातer states,
 * various घातer करोमुख्य DVFS including the core/cluster, certain प्रणाली
 * घड़ीs configuration, thermal sensors and many others.
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/idr.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/processor.h>
#समावेश <linux/refcount.h>
#समावेश <linux/slab.h>

#समावेश "common.h"
#समावेश "notify.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/scmi.h>

क्रमागत scmi_error_codes अणु
	SCMI_SUCCESS = 0,	/* Success */
	SCMI_ERR_SUPPORT = -1,	/* Not supported */
	SCMI_ERR_PARAMS = -2,	/* Invalid Parameters */
	SCMI_ERR_ACCESS = -3,	/* Invalid access/permission denied */
	SCMI_ERR_ENTRY = -4,	/* Not found */
	SCMI_ERR_RANGE = -5,	/* Value out of range */
	SCMI_ERR_BUSY = -6,	/* Device busy */
	SCMI_ERR_COMMS = -7,	/* Communication Error */
	SCMI_ERR_GENERIC = -8,	/* Generic Error */
	SCMI_ERR_HARDWARE = -9,	/* Hardware Error */
	SCMI_ERR_PROTOCOL = -10,/* Protocol Error */
	SCMI_ERR_MAX
पूर्ण;

/* List of all SCMI devices active in प्रणाली */
अटल LIST_HEAD(scmi_list);
/* Protection क्रम the entire list */
अटल DEFINE_MUTEX(scmi_list_mutex);
/* Track the unique id क्रम the transfers क्रम debug & profiling purpose */
अटल atomic_t transfer_last_id;

अटल DEFINE_IDR(scmi_requested_devices);
अटल DEFINE_MUTEX(scmi_requested_devices_mtx);

काष्ठा scmi_requested_dev अणु
	स्थिर काष्ठा scmi_device_id *id_table;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा scmi_xfers_info - Structure to manage transfer inक्रमmation
 *
 * @xfer_block: Pपुनः_स्मृतिated Message array
 * @xfer_alloc_table: Biपंचांगap table क्रम allocated messages.
 *	Index of this biपंचांगap table is also used क्रम message
 *	sequence identअगरier.
 * @xfer_lock: Protection क्रम message allocation
 */
काष्ठा scmi_xfers_info अणु
	काष्ठा scmi_xfer *xfer_block;
	अचिन्हित दीर्घ *xfer_alloc_table;
	spinlock_t xfer_lock;
पूर्ण;

/**
 * काष्ठा scmi_protocol_instance  - Describe an initialized protocol instance.
 * @handle: Reference to the SCMI handle associated to this protocol instance.
 * @proto: A reference to the protocol descriptor.
 * @gid: A reference क्रम per-protocol devres management.
 * @users: A refcount to track effective users of this protocol.
 * @priv: Reference क्रम optional protocol निजी data.
 * @ph: An embedded protocol handle that will be passed करोwn to protocol
 *	initialization code to identअगरy this instance.
 *
 * Each protocol is initialized independently once क्रम each SCMI platक्रमm in
 * which is defined by DT and implemented by the SCMI server fw.
 */
काष्ठा scmi_protocol_instance अणु
	स्थिर काष्ठा scmi_handle	*handle;
	स्थिर काष्ठा scmi_protocol	*proto;
	व्योम				*gid;
	refcount_t			users;
	व्योम				*priv;
	काष्ठा scmi_protocol_handle	ph;
पूर्ण;

#घोषणा ph_to_pi(h)	container_of(h, काष्ठा scmi_protocol_instance, ph)

/**
 * काष्ठा scmi_info - Structure representing a SCMI instance
 *
 * @dev: Device poपूर्णांकer
 * @desc: SoC description क्रम this instance
 * @version: SCMI revision inक्रमmation containing protocol version,
 *	implementation version and (sub-)venकरोr identअगरication.
 * @handle: Instance of SCMI handle to send to clients
 * @tx_minfo: Universal Transmit Message management info
 * @rx_minfo: Universal Receive Message management info
 * @tx_idr: IDR object to map protocol id to Tx channel info poपूर्णांकer
 * @rx_idr: IDR object to map protocol id to Rx channel info poपूर्णांकer
 * @protocols: IDR क्रम protocols' instance descriptors initialized क्रम
 *	       this SCMI instance: populated on protocol's first attempted
 *	       usage.
 * @protocols_mtx: A mutex to protect protocols instances initialization.
 * @protocols_imp: List of protocols implemented, currently maximum of
 *	MAX_PROTOCOLS_IMP elements allocated by the base protocol
 * @active_protocols: IDR storing device_nodes क्रम protocols actually defined
 *		      in the DT and confirmed as implemented by fw.
 * @notअगरy_priv: Poपूर्णांकer to निजी data काष्ठाure specअगरic to notअगरications.
 * @node: List head
 * @users: Number of users of this instance
 */
काष्ठा scmi_info अणु
	काष्ठा device *dev;
	स्थिर काष्ठा scmi_desc *desc;
	काष्ठा scmi_revision_info version;
	काष्ठा scmi_handle handle;
	काष्ठा scmi_xfers_info tx_minfo;
	काष्ठा scmi_xfers_info rx_minfo;
	काष्ठा idr tx_idr;
	काष्ठा idr rx_idr;
	काष्ठा idr protocols;
	/* Ensure mutual exclusive access to protocols instance array */
	काष्ठा mutex protocols_mtx;
	u8 *protocols_imp;
	काष्ठा idr active_protocols;
	व्योम *notअगरy_priv;
	काष्ठा list_head node;
	पूर्णांक users;
पूर्ण;

#घोषणा handle_to_scmi_info(h)	container_of(h, काष्ठा scmi_info, handle)

अटल स्थिर पूर्णांक scmi_linux_errmap[] = अणु
	/* better than चयन हाल as दीर्घ as वापस value is continuous */
	0,			/* SCMI_SUCCESS */
	-EOPNOTSUPP,		/* SCMI_ERR_SUPPORT */
	-EINVAL,		/* SCMI_ERR_PARAM */
	-EACCES,		/* SCMI_ERR_ACCESS */
	-ENOENT,		/* SCMI_ERR_ENTRY */
	-दुस्फल,		/* SCMI_ERR_RANGE */
	-EBUSY,			/* SCMI_ERR_BUSY */
	-ECOMM,			/* SCMI_ERR_COMMS */
	-EIO,			/* SCMI_ERR_GENERIC */
	-EREMOTEIO,		/* SCMI_ERR_HARDWARE */
	-EPROTO,		/* SCMI_ERR_PROTOCOL */
पूर्ण;

अटल अंतरभूत पूर्णांक scmi_to_linux_त्रुटि_सं(पूर्णांक त्रुटि_सं)
अणु
	अगर (त्रुटि_सं < SCMI_SUCCESS && त्रुटि_सं > SCMI_ERR_MAX)
		वापस scmi_linux_errmap[-त्रुटि_सं];
	वापस -EIO;
पूर्ण

/**
 * scmi_dump_header_dbg() - Helper to dump a message header.
 *
 * @dev: Device poपूर्णांकer corresponding to the SCMI entity
 * @hdr: poपूर्णांकer to header.
 */
अटल अंतरभूत व्योम scmi_dump_header_dbg(काष्ठा device *dev,
					काष्ठा scmi_msg_hdr *hdr)
अणु
	dev_dbg(dev, "Message ID: %x Sequence ID: %x Protocol: %x\n",
		hdr->id, hdr->seq, hdr->protocol_id);
पूर्ण

व्योम scmi_notअगरication_instance_data_set(स्थिर काष्ठा scmi_handle *handle,
					 व्योम *priv)
अणु
	काष्ठा scmi_info *info = handle_to_scmi_info(handle);

	info->notअगरy_priv = priv;
	/* Ensure updated protocol निजी date are visible */
	smp_wmb();
पूर्ण

व्योम *scmi_notअगरication_instance_data_get(स्थिर काष्ठा scmi_handle *handle)
अणु
	काष्ठा scmi_info *info = handle_to_scmi_info(handle);

	/* Ensure protocols_निजी_data has been updated */
	smp_rmb();
	वापस info->notअगरy_priv;
पूर्ण

/**
 * scmi_xfer_get() - Allocate one message
 *
 * @handle: Poपूर्णांकer to SCMI entity handle
 * @minfo: Poपूर्णांकer to Tx/Rx Message management info based on channel type
 *
 * Helper function which is used by various message functions that are
 * exposed to clients of this driver क्रम allocating a message traffic event.
 *
 * This function can sleep depending on pending requests alपढ़ोy in the प्रणाली
 * क्रम the SCMI entity. Further, this also holds a spinlock to मुख्यtain
 * पूर्णांकegrity of पूर्णांकernal data काष्ठाures.
 *
 * Return: 0 अगर all went fine, अन्यथा corresponding error.
 */
अटल काष्ठा scmi_xfer *scmi_xfer_get(स्थिर काष्ठा scmi_handle *handle,
				       काष्ठा scmi_xfers_info *minfo)
अणु
	u16 xfer_id;
	काष्ठा scmi_xfer *xfer;
	अचिन्हित दीर्घ flags, bit_pos;
	काष्ठा scmi_info *info = handle_to_scmi_info(handle);

	/* Keep the locked section as small as possible */
	spin_lock_irqsave(&minfo->xfer_lock, flags);
	bit_pos = find_first_zero_bit(minfo->xfer_alloc_table,
				      info->desc->max_msg);
	अगर (bit_pos == info->desc->max_msg) अणु
		spin_unlock_irqrestore(&minfo->xfer_lock, flags);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	set_bit(bit_pos, minfo->xfer_alloc_table);
	spin_unlock_irqrestore(&minfo->xfer_lock, flags);

	xfer_id = bit_pos;

	xfer = &minfo->xfer_block[xfer_id];
	xfer->hdr.seq = xfer_id;
	reinit_completion(&xfer->करोne);
	xfer->transfer_id = atomic_inc_वापस(&transfer_last_id);

	वापस xfer;
पूर्ण

/**
 * __scmi_xfer_put() - Release a message
 *
 * @minfo: Poपूर्णांकer to Tx/Rx Message management info based on channel type
 * @xfer: message that was reserved by scmi_xfer_get
 *
 * This holds a spinlock to मुख्यtain पूर्णांकegrity of पूर्णांकernal data काष्ठाures.
 */
अटल व्योम
__scmi_xfer_put(काष्ठा scmi_xfers_info *minfo, काष्ठा scmi_xfer *xfer)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Keep the locked section as small as possible
	 * NOTE: we might escape with smp_mb and no lock here..
	 * but just be conservative and symmetric.
	 */
	spin_lock_irqsave(&minfo->xfer_lock, flags);
	clear_bit(xfer->hdr.seq, minfo->xfer_alloc_table);
	spin_unlock_irqrestore(&minfo->xfer_lock, flags);
पूर्ण

अटल व्योम scmi_handle_notअगरication(काष्ठा scmi_chan_info *cinfo, u32 msg_hdr)
अणु
	काष्ठा scmi_xfer *xfer;
	काष्ठा device *dev = cinfo->dev;
	काष्ठा scmi_info *info = handle_to_scmi_info(cinfo->handle);
	काष्ठा scmi_xfers_info *minfo = &info->rx_minfo;
	kसमय_प्रकार ts;

	ts = kसमय_get_bootसमय();
	xfer = scmi_xfer_get(cinfo->handle, minfo);
	अगर (IS_ERR(xfer)) अणु
		dev_err(dev, "failed to get free message slot (%ld)\n",
			PTR_ERR(xfer));
		info->desc->ops->clear_channel(cinfo);
		वापस;
	पूर्ण

	unpack_scmi_header(msg_hdr, &xfer->hdr);
	scmi_dump_header_dbg(dev, &xfer->hdr);
	info->desc->ops->fetch_notअगरication(cinfo, info->desc->max_msg_size,
					    xfer);
	scmi_notअगरy(cinfo->handle, xfer->hdr.protocol_id,
		    xfer->hdr.id, xfer->rx.buf, xfer->rx.len, ts);

	trace_scmi_rx_करोne(xfer->transfer_id, xfer->hdr.id,
			   xfer->hdr.protocol_id, xfer->hdr.seq,
			   MSG_TYPE_NOTIFICATION);

	__scmi_xfer_put(minfo, xfer);

	info->desc->ops->clear_channel(cinfo);
पूर्ण

अटल व्योम scmi_handle_response(काष्ठा scmi_chan_info *cinfo,
				 u16 xfer_id, u8 msg_type)
अणु
	काष्ठा scmi_xfer *xfer;
	काष्ठा device *dev = cinfo->dev;
	काष्ठा scmi_info *info = handle_to_scmi_info(cinfo->handle);
	काष्ठा scmi_xfers_info *minfo = &info->tx_minfo;

	/* Are we even expecting this? */
	अगर (!test_bit(xfer_id, minfo->xfer_alloc_table)) अणु
		dev_err(dev, "message for %d is not expected!\n", xfer_id);
		info->desc->ops->clear_channel(cinfo);
		वापस;
	पूर्ण

	xfer = &minfo->xfer_block[xfer_id];
	/*
	 * Even अगर a response was indeed expected on this slot at this poपूर्णांक,
	 * a buggy platक्रमm could wrongly reply feeding us an unexpected
	 * delayed response we're not prepared to handle: bail-out safely
	 * blaming firmware.
	 */
	अगर (unlikely(msg_type == MSG_TYPE_DELAYED_RESP && !xfer->async_करोne)) अणु
		dev_err(dev,
			"Delayed Response for %d not expected! Buggy F/W ?\n",
			xfer_id);
		info->desc->ops->clear_channel(cinfo);
		/* It was unexpected, so nobody will clear the xfer अगर not us */
		__scmi_xfer_put(minfo, xfer);
		वापस;
	पूर्ण

	scmi_dump_header_dbg(dev, &xfer->hdr);

	info->desc->ops->fetch_response(cinfo, xfer);

	trace_scmi_rx_करोne(xfer->transfer_id, xfer->hdr.id,
			   xfer->hdr.protocol_id, xfer->hdr.seq,
			   msg_type);

	अगर (msg_type == MSG_TYPE_DELAYED_RESP) अणु
		info->desc->ops->clear_channel(cinfo);
		complete(xfer->async_करोne);
	पूर्ण अन्यथा अणु
		complete(&xfer->करोne);
	पूर्ण
पूर्ण

/**
 * scmi_rx_callback() - callback क्रम receiving messages
 *
 * @cinfo: SCMI channel info
 * @msg_hdr: Message header
 *
 * Processes one received message to appropriate transfer inक्रमmation and
 * संकेतs completion of the transfer.
 *
 * NOTE: This function will be invoked in IRQ context, hence should be
 * as optimal as possible.
 */
व्योम scmi_rx_callback(काष्ठा scmi_chan_info *cinfo, u32 msg_hdr)
अणु
	u16 xfer_id = MSG_XTRACT_TOKEN(msg_hdr);
	u8 msg_type = MSG_XTRACT_TYPE(msg_hdr);

	चयन (msg_type) अणु
	हाल MSG_TYPE_NOTIFICATION:
		scmi_handle_notअगरication(cinfo, msg_hdr);
		अवरोध;
	हाल MSG_TYPE_COMMAND:
	हाल MSG_TYPE_DELAYED_RESP:
		scmi_handle_response(cinfo, xfer_id, msg_type);
		अवरोध;
	शेष:
		WARN_ONCE(1, "received unknown msg_type:%d\n", msg_type);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * xfer_put() - Release a transmit message
 *
 * @ph: Poपूर्णांकer to SCMI protocol handle
 * @xfer: message that was reserved by scmi_xfer_get
 */
अटल व्योम xfer_put(स्थिर काष्ठा scmi_protocol_handle *ph,
		     काष्ठा scmi_xfer *xfer)
अणु
	स्थिर काष्ठा scmi_protocol_instance *pi = ph_to_pi(ph);
	काष्ठा scmi_info *info = handle_to_scmi_info(pi->handle);

	__scmi_xfer_put(&info->tx_minfo, xfer);
पूर्ण

#घोषणा SCMI_MAX_POLL_TO_NS	(100 * NSEC_PER_USEC)

अटल bool scmi_xfer_करोne_no_समयout(काष्ठा scmi_chan_info *cinfo,
				      काष्ठा scmi_xfer *xfer, kसमय_प्रकार stop)
अणु
	काष्ठा scmi_info *info = handle_to_scmi_info(cinfo->handle);

	वापस info->desc->ops->poll_करोne(cinfo, xfer) ||
	       kसमय_after(kसमय_get(), stop);
पूर्ण

/**
 * करो_xfer() - Do one transfer
 *
 * @ph: Poपूर्णांकer to SCMI protocol handle
 * @xfer: Transfer to initiate and रुको क्रम response
 *
 * Return: -ETIMEDOUT in हाल of no response, अगर transmit error,
 *	वापस corresponding error, अन्यथा अगर all goes well,
 *	वापस 0.
 */
अटल पूर्णांक करो_xfer(स्थिर काष्ठा scmi_protocol_handle *ph,
		   काष्ठा scmi_xfer *xfer)
अणु
	पूर्णांक ret;
	पूर्णांक समयout;
	स्थिर काष्ठा scmi_protocol_instance *pi = ph_to_pi(ph);
	काष्ठा scmi_info *info = handle_to_scmi_info(pi->handle);
	काष्ठा device *dev = info->dev;
	काष्ठा scmi_chan_info *cinfo;

	/*
	 * Re-instate protocol id here from protocol handle so that cannot be
	 * overridden by mistake (or malice) by the protocol code mangling with
	 * the scmi_xfer काष्ठाure.
	 */
	xfer->hdr.protocol_id = pi->proto->id;

	cinfo = idr_find(&info->tx_idr, xfer->hdr.protocol_id);
	अगर (unlikely(!cinfo))
		वापस -EINVAL;

	trace_scmi_xfer_begin(xfer->transfer_id, xfer->hdr.id,
			      xfer->hdr.protocol_id, xfer->hdr.seq,
			      xfer->hdr.poll_completion);

	ret = info->desc->ops->send_message(cinfo, xfer);
	अगर (ret < 0) अणु
		dev_dbg(dev, "Failed to send message %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (xfer->hdr.poll_completion) अणु
		kसमय_प्रकार stop = kसमय_add_ns(kसमय_get(), SCMI_MAX_POLL_TO_NS);

		spin_until_cond(scmi_xfer_करोne_no_समयout(cinfo, xfer, stop));

		अगर (kसमय_beक्रमe(kसमय_get(), stop))
			info->desc->ops->fetch_response(cinfo, xfer);
		अन्यथा
			ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		/* And we रुको क्रम the response. */
		समयout = msecs_to_jअगरfies(info->desc->max_rx_समयout_ms);
		अगर (!रुको_क्रम_completion_समयout(&xfer->करोne, समयout)) अणु
			dev_err(dev, "timed out in resp(caller: %pS)\n",
				(व्योम *)_RET_IP_);
			ret = -ETIMEDOUT;
		पूर्ण
	पूर्ण

	अगर (!ret && xfer->hdr.status)
		ret = scmi_to_linux_त्रुटि_सं(xfer->hdr.status);

	अगर (info->desc->ops->mark_txकरोne)
		info->desc->ops->mark_txकरोne(cinfo, ret);

	trace_scmi_xfer_end(xfer->transfer_id, xfer->hdr.id,
			    xfer->hdr.protocol_id, xfer->hdr.seq, ret);

	वापस ret;
पूर्ण

अटल व्योम reset_rx_to_maxsz(स्थिर काष्ठा scmi_protocol_handle *ph,
			      काष्ठा scmi_xfer *xfer)
अणु
	स्थिर काष्ठा scmi_protocol_instance *pi = ph_to_pi(ph);
	काष्ठा scmi_info *info = handle_to_scmi_info(pi->handle);

	xfer->rx.len = info->desc->max_msg_size;
पूर्ण

#घोषणा SCMI_MAX_RESPONSE_TIMEOUT	(2 * MSEC_PER_SEC)

/**
 * करो_xfer_with_response() - Do one transfer and रुको until the delayed
 *	response is received
 *
 * @ph: Poपूर्णांकer to SCMI protocol handle
 * @xfer: Transfer to initiate and रुको क्रम response
 *
 * Return: -ETIMEDOUT in हाल of no delayed response, अगर transmit error,
 *	वापस corresponding error, अन्यथा अगर all goes well, वापस 0.
 */
अटल पूर्णांक करो_xfer_with_response(स्थिर काष्ठा scmi_protocol_handle *ph,
				 काष्ठा scmi_xfer *xfer)
अणु
	पूर्णांक ret, समयout = msecs_to_jअगरfies(SCMI_MAX_RESPONSE_TIMEOUT);
	स्थिर काष्ठा scmi_protocol_instance *pi = ph_to_pi(ph);
	DECLARE_COMPLETION_ONSTACK(async_response);

	xfer->hdr.protocol_id = pi->proto->id;

	xfer->async_करोne = &async_response;

	ret = करो_xfer(ph, xfer);
	अगर (!ret && !रुको_क्रम_completion_समयout(xfer->async_करोne, समयout))
		ret = -ETIMEDOUT;

	xfer->async_करोne = शून्य;
	वापस ret;
पूर्ण

/**
 * xfer_get_init() - Allocate and initialise one message क्रम transmit
 *
 * @ph: Poपूर्णांकer to SCMI protocol handle
 * @msg_id: Message identअगरier
 * @tx_size: transmit message size
 * @rx_size: receive message size
 * @p: poपूर्णांकer to the allocated and initialised message
 *
 * This function allocates the message using @scmi_xfer_get and
 * initialise the header.
 *
 * Return: 0 अगर all went fine with @p poपूर्णांकing to message, अन्यथा
 *	corresponding error.
 */
अटल पूर्णांक xfer_get_init(स्थिर काष्ठा scmi_protocol_handle *ph,
			 u8 msg_id, माप_प्रकार tx_size, माप_प्रकार rx_size,
			 काष्ठा scmi_xfer **p)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *xfer;
	स्थिर काष्ठा scmi_protocol_instance *pi = ph_to_pi(ph);
	काष्ठा scmi_info *info = handle_to_scmi_info(pi->handle);
	काष्ठा scmi_xfers_info *minfo = &info->tx_minfo;
	काष्ठा device *dev = info->dev;

	/* Ensure we have sane transfer sizes */
	अगर (rx_size > info->desc->max_msg_size ||
	    tx_size > info->desc->max_msg_size)
		वापस -दुस्फल;

	xfer = scmi_xfer_get(pi->handle, minfo);
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "failed to get free message slot(%d)\n", ret);
		वापस ret;
	पूर्ण

	xfer->tx.len = tx_size;
	xfer->rx.len = rx_size ? : info->desc->max_msg_size;
	xfer->hdr.id = msg_id;
	xfer->hdr.protocol_id = pi->proto->id;
	xfer->hdr.poll_completion = false;

	*p = xfer;

	वापस 0;
पूर्ण

/**
 * version_get() - command to get the revision of the SCMI entity
 *
 * @ph: Poपूर्णांकer to SCMI protocol handle
 * @version: Holds वापसed version of protocol.
 *
 * Updates the SCMI inक्रमmation in the पूर्णांकernal data काष्ठाure.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक version_get(स्थिर काष्ठा scmi_protocol_handle *ph, u32 *version)
अणु
	पूर्णांक ret;
	__le32 *rev_info;
	काष्ठा scmi_xfer *t;

	ret = xfer_get_init(ph, PROTOCOL_VERSION, 0, माप(*version), &t);
	अगर (ret)
		वापस ret;

	ret = करो_xfer(ph, t);
	अगर (!ret) अणु
		rev_info = t->rx.buf;
		*version = le32_to_cpu(*rev_info);
	पूर्ण

	xfer_put(ph, t);
	वापस ret;
पूर्ण

/**
 * scmi_set_protocol_priv  - Set protocol specअगरic data at init समय
 *
 * @ph: A reference to the protocol handle.
 * @priv: The निजी data to set.
 *
 * Return: 0 on Success
 */
अटल पूर्णांक scmi_set_protocol_priv(स्थिर काष्ठा scmi_protocol_handle *ph,
				  व्योम *priv)
अणु
	काष्ठा scmi_protocol_instance *pi = ph_to_pi(ph);

	pi->priv = priv;

	वापस 0;
पूर्ण

/**
 * scmi_get_protocol_priv  - Set protocol specअगरic data at init समय
 *
 * @ph: A reference to the protocol handle.
 *
 * Return: Protocol निजी data अगर any was set.
 */
अटल व्योम *scmi_get_protocol_priv(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	स्थिर काष्ठा scmi_protocol_instance *pi = ph_to_pi(ph);

	वापस pi->priv;
पूर्ण

अटल स्थिर काष्ठा scmi_xfer_ops xfer_ops = अणु
	.version_get = version_get,
	.xfer_get_init = xfer_get_init,
	.reset_rx_to_maxsz = reset_rx_to_maxsz,
	.करो_xfer = करो_xfer,
	.करो_xfer_with_response = करो_xfer_with_response,
	.xfer_put = xfer_put,
पूर्ण;

/**
 * scmi_revision_area_get  - Retrieve version memory area.
 *
 * @ph: A reference to the protocol handle.
 *
 * A helper to grab the version memory area reference during SCMI Base protocol
 * initialization.
 *
 * Return: A reference to the version memory area associated to the SCMI
 *	   instance underlying this protocol handle.
 */
काष्ठा scmi_revision_info *
scmi_revision_area_get(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	स्थिर काष्ठा scmi_protocol_instance *pi = ph_to_pi(ph);

	वापस pi->handle->version;
पूर्ण

/**
 * scmi_alloc_init_protocol_instance  - Allocate and initialize a protocol
 * instance descriptor.
 * @info: The reference to the related SCMI instance.
 * @proto: The protocol descriptor.
 *
 * Allocate a new protocol instance descriptor, using the provided @proto
 * description, against the specअगरied SCMI instance @info, and initialize it;
 * all resources management is handled via a dedicated per-protocol devres
 * group.
 *
 * Context: Assumes to be called with @protocols_mtx alपढ़ोy acquired.
 * Return: A reference to a freshly allocated and initialized protocol instance
 *	   or ERR_PTR on failure. On failure the @proto reference is at first
 *	   put using @scmi_protocol_put() beक्रमe releasing all the devres group.
 */
अटल काष्ठा scmi_protocol_instance *
scmi_alloc_init_protocol_instance(काष्ठा scmi_info *info,
				  स्थिर काष्ठा scmi_protocol *proto)
अणु
	पूर्णांक ret = -ENOMEM;
	व्योम *gid;
	काष्ठा scmi_protocol_instance *pi;
	स्थिर काष्ठा scmi_handle *handle = &info->handle;

	/* Protocol specअगरic devres group */
	gid = devres_खोलो_group(handle->dev, शून्य, GFP_KERNEL);
	अगर (!gid) अणु
		scmi_protocol_put(proto->id);
		जाओ out;
	पूर्ण

	pi = devm_kzalloc(handle->dev, माप(*pi), GFP_KERNEL);
	अगर (!pi)
		जाओ clean;

	pi->gid = gid;
	pi->proto = proto;
	pi->handle = handle;
	pi->ph.dev = handle->dev;
	pi->ph.xops = &xfer_ops;
	pi->ph.set_priv = scmi_set_protocol_priv;
	pi->ph.get_priv = scmi_get_protocol_priv;
	refcount_set(&pi->users, 1);
	/* proto->init is assured NON शून्य by scmi_protocol_रेजिस्टर */
	ret = pi->proto->instance_init(&pi->ph);
	अगर (ret)
		जाओ clean;

	ret = idr_alloc(&info->protocols, pi, proto->id, proto->id + 1,
			GFP_KERNEL);
	अगर (ret != proto->id)
		जाओ clean;

	/*
	 * Warn but ignore events registration errors since we करो not want
	 * to skip whole protocols अगर their notअगरications are messed up.
	 */
	अगर (pi->proto->events) अणु
		ret = scmi_रेजिस्टर_protocol_events(handle, pi->proto->id,
						    &pi->ph,
						    pi->proto->events);
		अगर (ret)
			dev_warn(handle->dev,
				 "Protocol:%X - Events Registration Failed - err:%d\n",
				 pi->proto->id, ret);
	पूर्ण

	devres_बंद_group(handle->dev, pi->gid);
	dev_dbg(handle->dev, "Initialized protocol: 0x%X\n", pi->proto->id);

	वापस pi;

clean:
	/* Take care to put the protocol module's owner beक्रमe releasing all */
	scmi_protocol_put(proto->id);
	devres_release_group(handle->dev, gid);
out:
	वापस ERR_PTR(ret);
पूर्ण

/**
 * scmi_get_protocol_instance  - Protocol initialization helper.
 * @handle: A reference to the SCMI platक्रमm instance.
 * @protocol_id: The protocol being requested.
 *
 * In हाल the required protocol has never been requested beक्रमe क्रम this
 * instance, allocate and initialize all the needed काष्ठाures जबतक handling
 * resource allocation with a dedicated per-protocol devres subgroup.
 *
 * Return: A reference to an initialized protocol instance or error on failure:
 *	   in particular वापसs -EPROBE_DEFER when the desired protocol could
 *	   NOT be found.
 */
अटल काष्ठा scmi_protocol_instance * __must_check
scmi_get_protocol_instance(स्थिर काष्ठा scmi_handle *handle, u8 protocol_id)
अणु
	काष्ठा scmi_protocol_instance *pi;
	काष्ठा scmi_info *info = handle_to_scmi_info(handle);

	mutex_lock(&info->protocols_mtx);
	pi = idr_find(&info->protocols, protocol_id);

	अगर (pi) अणु
		refcount_inc(&pi->users);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा scmi_protocol *proto;

		/* Fails अगर protocol not रेजिस्टरed on bus */
		proto = scmi_protocol_get(protocol_id);
		अगर (proto)
			pi = scmi_alloc_init_protocol_instance(info, proto);
		अन्यथा
			pi = ERR_PTR(-EPROBE_DEFER);
	पूर्ण
	mutex_unlock(&info->protocols_mtx);

	वापस pi;
पूर्ण

/**
 * scmi_protocol_acquire  - Protocol acquire
 * @handle: A reference to the SCMI platक्रमm instance.
 * @protocol_id: The protocol being requested.
 *
 * Register a new user क्रम the requested protocol on the specअगरied SCMI
 * platक्रमm instance, possibly triggering its initialization on first user.
 *
 * Return: 0 अगर protocol was acquired successfully.
 */
पूर्णांक scmi_protocol_acquire(स्थिर काष्ठा scmi_handle *handle, u8 protocol_id)
अणु
	वापस PTR_ERR_OR_ZERO(scmi_get_protocol_instance(handle, protocol_id));
पूर्ण

/**
 * scmi_protocol_release  - Protocol de-initialization helper.
 * @handle: A reference to the SCMI platक्रमm instance.
 * @protocol_id: The protocol being requested.
 *
 * Remove one user क्रम the specअगरied protocol and triggers de-initialization
 * and resources de-allocation once the last user has gone.
 */
व्योम scmi_protocol_release(स्थिर काष्ठा scmi_handle *handle, u8 protocol_id)
अणु
	काष्ठा scmi_info *info = handle_to_scmi_info(handle);
	काष्ठा scmi_protocol_instance *pi;

	mutex_lock(&info->protocols_mtx);
	pi = idr_find(&info->protocols, protocol_id);
	अगर (WARN_ON(!pi))
		जाओ out;

	अगर (refcount_dec_and_test(&pi->users)) अणु
		व्योम *gid = pi->gid;

		अगर (pi->proto->events)
			scmi_deरेजिस्टर_protocol_events(handle, protocol_id);

		अगर (pi->proto->instance_deinit)
			pi->proto->instance_deinit(&pi->ph);

		idr_हटाओ(&info->protocols, protocol_id);

		scmi_protocol_put(protocol_id);

		devres_release_group(handle->dev, gid);
		dev_dbg(handle->dev, "De-Initialized protocol: 0x%X\n",
			protocol_id);
	पूर्ण

out:
	mutex_unlock(&info->protocols_mtx);
पूर्ण

व्योम scmi_setup_protocol_implemented(स्थिर काष्ठा scmi_protocol_handle *ph,
				     u8 *prot_imp)
अणु
	स्थिर काष्ठा scmi_protocol_instance *pi = ph_to_pi(ph);
	काष्ठा scmi_info *info = handle_to_scmi_info(pi->handle);

	info->protocols_imp = prot_imp;
पूर्ण

अटल bool
scmi_is_protocol_implemented(स्थिर काष्ठा scmi_handle *handle, u8 prot_id)
अणु
	पूर्णांक i;
	काष्ठा scmi_info *info = handle_to_scmi_info(handle);

	अगर (!info->protocols_imp)
		वापस false;

	क्रम (i = 0; i < MAX_PROTOCOLS_IMP; i++)
		अगर (info->protocols_imp[i] == prot_id)
			वापस true;
	वापस false;
पूर्ण

काष्ठा scmi_protocol_devres अणु
	स्थिर काष्ठा scmi_handle *handle;
	u8 protocol_id;
पूर्ण;

अटल व्योम scmi_devm_release_protocol(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा scmi_protocol_devres *dres = res;

	scmi_protocol_release(dres->handle, dres->protocol_id);
पूर्ण

/**
 * scmi_devm_protocol_get  - Devres managed get protocol operations and handle
 * @sdev: A reference to an scmi_device whose embedded काष्ठा device is to
 *	  be used क्रम devres accounting.
 * @protocol_id: The protocol being requested.
 * @ph: A poपूर्णांकer reference used to pass back the associated protocol handle.
 *
 * Get hold of a protocol accounting क्रम its usage, eventually triggering its
 * initialization, and वापसing the protocol specअगरic operations and related
 * protocol handle which will be used as first argument in most of the
 * protocols operations methods.
 * Being a devres based managed method, protocol hold will be स्वतःmatically
 * released, and possibly de-initialized on last user, once the SCMI driver
 * owning the scmi_device is unbound from it.
 *
 * Return: A reference to the requested protocol operations or error.
 *	   Must be checked क्रम errors by caller.
 */
अटल स्थिर व्योम __must_check *
scmi_devm_protocol_get(काष्ठा scmi_device *sdev, u8 protocol_id,
		       काष्ठा scmi_protocol_handle **ph)
अणु
	काष्ठा scmi_protocol_instance *pi;
	काष्ठा scmi_protocol_devres *dres;
	काष्ठा scmi_handle *handle = sdev->handle;

	अगर (!ph)
		वापस ERR_PTR(-EINVAL);

	dres = devres_alloc(scmi_devm_release_protocol,
			    माप(*dres), GFP_KERNEL);
	अगर (!dres)
		वापस ERR_PTR(-ENOMEM);

	pi = scmi_get_protocol_instance(handle, protocol_id);
	अगर (IS_ERR(pi)) अणु
		devres_मुक्त(dres);
		वापस pi;
	पूर्ण

	dres->handle = handle;
	dres->protocol_id = protocol_id;
	devres_add(&sdev->dev, dres);

	*ph = &pi->ph;

	वापस pi->proto->ops;
पूर्ण

अटल पूर्णांक scmi_devm_protocol_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा scmi_protocol_devres *dres = res;

	अगर (WARN_ON(!dres || !data))
		वापस 0;

	वापस dres->protocol_id == *((u8 *)data);
पूर्ण

/**
 * scmi_devm_protocol_put  - Devres managed put protocol operations and handle
 * @sdev: A reference to an scmi_device whose embedded काष्ठा device is to
 *	  be used क्रम devres accounting.
 * @protocol_id: The protocol being requested.
 *
 * Explicitly release a protocol hold previously obtained calling the above
 * @scmi_devm_protocol_get.
 */
अटल व्योम scmi_devm_protocol_put(काष्ठा scmi_device *sdev, u8 protocol_id)
अणु
	पूर्णांक ret;

	ret = devres_release(&sdev->dev, scmi_devm_release_protocol,
			     scmi_devm_protocol_match, &protocol_id);
	WARN_ON(ret);
पूर्ण

अटल अंतरभूत
काष्ठा scmi_handle *scmi_handle_get_from_info_unlocked(काष्ठा scmi_info *info)
अणु
	info->users++;
	वापस &info->handle;
पूर्ण

/**
 * scmi_handle_get() - Get the SCMI handle क्रम a device
 *
 * @dev: poपूर्णांकer to device क्रम which we want SCMI handle
 *
 * NOTE: The function करोes not track inभागidual clients of the framework
 * and is expected to be मुख्यtained by caller of SCMI protocol library.
 * scmi_handle_put must be balanced with successful scmi_handle_get
 *
 * Return: poपूर्णांकer to handle अगर successful, शून्य on error
 */
काष्ठा scmi_handle *scmi_handle_get(काष्ठा device *dev)
अणु
	काष्ठा list_head *p;
	काष्ठा scmi_info *info;
	काष्ठा scmi_handle *handle = शून्य;

	mutex_lock(&scmi_list_mutex);
	list_क्रम_each(p, &scmi_list) अणु
		info = list_entry(p, काष्ठा scmi_info, node);
		अगर (dev->parent == info->dev) अणु
			handle = scmi_handle_get_from_info_unlocked(info);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&scmi_list_mutex);

	वापस handle;
पूर्ण

/**
 * scmi_handle_put() - Release the handle acquired by scmi_handle_get
 *
 * @handle: handle acquired by scmi_handle_get
 *
 * NOTE: The function करोes not track inभागidual clients of the framework
 * and is expected to be मुख्यtained by caller of SCMI protocol library.
 * scmi_handle_put must be balanced with successful scmi_handle_get
 *
 * Return: 0 is successfully released
 *	अगर null was passed, it वापसs -EINVAL;
 */
पूर्णांक scmi_handle_put(स्थिर काष्ठा scmi_handle *handle)
अणु
	काष्ठा scmi_info *info;

	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_scmi_info(handle);
	mutex_lock(&scmi_list_mutex);
	अगर (!WARN_ON(!info->users))
		info->users--;
	mutex_unlock(&scmi_list_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __scmi_xfer_info_init(काष्ठा scmi_info *sinfo,
				 काष्ठा scmi_xfers_info *info)
अणु
	पूर्णांक i;
	काष्ठा scmi_xfer *xfer;
	काष्ठा device *dev = sinfo->dev;
	स्थिर काष्ठा scmi_desc *desc = sinfo->desc;

	/* Pre-allocated messages, no more than what hdr.seq can support */
	अगर (WARN_ON(desc->max_msg >= MSG_TOKEN_MAX)) अणु
		dev_err(dev, "Maximum message of %d exceeds supported %ld\n",
			desc->max_msg, MSG_TOKEN_MAX);
		वापस -EINVAL;
	पूर्ण

	info->xfer_block = devm_kसुस्मृति(dev, desc->max_msg,
					माप(*info->xfer_block), GFP_KERNEL);
	अगर (!info->xfer_block)
		वापस -ENOMEM;

	info->xfer_alloc_table = devm_kसुस्मृति(dev, BITS_TO_LONGS(desc->max_msg),
					      माप(दीर्घ), GFP_KERNEL);
	अगर (!info->xfer_alloc_table)
		वापस -ENOMEM;

	/* Pre-initialize the buffer poपूर्णांकer to pre-allocated buffers */
	क्रम (i = 0, xfer = info->xfer_block; i < desc->max_msg; i++, xfer++) अणु
		xfer->rx.buf = devm_kसुस्मृति(dev, माप(u8), desc->max_msg_size,
					    GFP_KERNEL);
		अगर (!xfer->rx.buf)
			वापस -ENOMEM;

		xfer->tx.buf = xfer->rx.buf;
		init_completion(&xfer->करोne);
	पूर्ण

	spin_lock_init(&info->xfer_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक scmi_xfer_info_init(काष्ठा scmi_info *sinfo)
अणु
	पूर्णांक ret = __scmi_xfer_info_init(sinfo, &sinfo->tx_minfo);

	अगर (!ret && idr_find(&sinfo->rx_idr, SCMI_PROTOCOL_BASE))
		ret = __scmi_xfer_info_init(sinfo, &sinfo->rx_minfo);

	वापस ret;
पूर्ण

अटल पूर्णांक scmi_chan_setup(काष्ठा scmi_info *info, काष्ठा device *dev,
			   पूर्णांक prot_id, bool tx)
अणु
	पूर्णांक ret, idx;
	काष्ठा scmi_chan_info *cinfo;
	काष्ठा idr *idr;

	/* Transmit channel is first entry i.e. index 0 */
	idx = tx ? 0 : 1;
	idr = tx ? &info->tx_idr : &info->rx_idr;

	/* check अगर alपढ़ोy allocated, used क्रम multiple device per protocol */
	cinfo = idr_find(idr, prot_id);
	अगर (cinfo)
		वापस 0;

	अगर (!info->desc->ops->chan_available(dev, idx)) अणु
		cinfo = idr_find(idr, SCMI_PROTOCOL_BASE);
		अगर (unlikely(!cinfo)) /* Possible only अगर platक्रमm has no Rx */
			वापस -EINVAL;
		जाओ idr_alloc;
	पूर्ण

	cinfo = devm_kzalloc(info->dev, माप(*cinfo), GFP_KERNEL);
	अगर (!cinfo)
		वापस -ENOMEM;

	cinfo->dev = dev;

	ret = info->desc->ops->chan_setup(cinfo, info->dev, tx);
	अगर (ret)
		वापस ret;

idr_alloc:
	ret = idr_alloc(idr, cinfo, prot_id, prot_id + 1, GFP_KERNEL);
	अगर (ret != prot_id) अणु
		dev_err(dev, "unable to allocate SCMI idr slot err %d\n", ret);
		वापस ret;
	पूर्ण

	cinfo->handle = &info->handle;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
scmi_txrx_setup(काष्ठा scmi_info *info, काष्ठा device *dev, पूर्णांक prot_id)
अणु
	पूर्णांक ret = scmi_chan_setup(info, dev, prot_id, true);

	अगर (!ret) /* Rx is optional, hence no error check */
		scmi_chan_setup(info, dev, prot_id, false);

	वापस ret;
पूर्ण

/**
 * scmi_get_protocol_device  - Helper to get/create an SCMI device.
 *
 * @np: A device node representing a valid active protocols क्रम the referred
 * SCMI instance.
 * @info: The referred SCMI instance क्रम which we are getting/creating this
 * device.
 * @prot_id: The protocol ID.
 * @name: The device name.
 *
 * Referring to the specअगरic SCMI instance identअगरied by @info, this helper
 * takes care to वापस a properly initialized device matching the requested
 * @proto_id and @name: अगर device was still not existent it is created as a
 * child of the specअगरied SCMI instance @info and its transport properly
 * initialized as usual.
 */
अटल अंतरभूत काष्ठा scmi_device *
scmi_get_protocol_device(काष्ठा device_node *np, काष्ठा scmi_info *info,
			 पूर्णांक prot_id, स्थिर अक्षर *name)
अणु
	काष्ठा scmi_device *sdev;

	/* Alपढ़ोy created क्रम this parent SCMI instance ? */
	sdev = scmi_child_dev_find(info->dev, prot_id, name);
	अगर (sdev)
		वापस sdev;

	pr_debug("Creating SCMI device (%s) for protocol %x\n", name, prot_id);

	sdev = scmi_device_create(np, info->dev, prot_id, name);
	अगर (!sdev) अणु
		dev_err(info->dev, "failed to create %d protocol device\n",
			prot_id);
		वापस शून्य;
	पूर्ण

	अगर (scmi_txrx_setup(info, &sdev->dev, prot_id)) अणु
		dev_err(&sdev->dev, "failed to setup transport\n");
		scmi_device_destroy(sdev);
		वापस शून्य;
	पूर्ण

	वापस sdev;
पूर्ण

अटल अंतरभूत व्योम
scmi_create_protocol_device(काष्ठा device_node *np, काष्ठा scmi_info *info,
			    पूर्णांक prot_id, स्थिर अक्षर *name)
अणु
	काष्ठा scmi_device *sdev;

	sdev = scmi_get_protocol_device(np, info, prot_id, name);
	अगर (!sdev)
		वापस;

	/* setup handle now as the transport is पढ़ोy */
	scmi_set_handle(sdev);
पूर्ण

/**
 * scmi_create_protocol_devices  - Create devices क्रम all pending requests क्रम
 * this SCMI instance.
 *
 * @np: The device node describing the protocol
 * @info: The SCMI instance descriptor
 * @prot_id: The protocol ID
 *
 * All devices previously requested क्रम this instance (अगर any) are found and
 * created by scanning the proper @&scmi_requested_devices entry.
 */
अटल व्योम scmi_create_protocol_devices(काष्ठा device_node *np,
					 काष्ठा scmi_info *info, पूर्णांक prot_id)
अणु
	काष्ठा list_head *phead;

	mutex_lock(&scmi_requested_devices_mtx);
	phead = idr_find(&scmi_requested_devices, prot_id);
	अगर (phead) अणु
		काष्ठा scmi_requested_dev *rdev;

		list_क्रम_each_entry(rdev, phead, node)
			scmi_create_protocol_device(np, info, prot_id,
						    rdev->id_table->name);
	पूर्ण
	mutex_unlock(&scmi_requested_devices_mtx);
पूर्ण

/**
 * scmi_protocol_device_request  - Helper to request a device
 *
 * @id_table: A protocol/name pair descriptor क्रम the device to be created.
 *
 * This helper let an SCMI driver request specअगरic devices identअगरied by the
 * @id_table to be created क्रम each active SCMI instance.
 *
 * The requested device name MUST NOT be alपढ़ोy existent क्रम any protocol;
 * at first the freshly requested @id_table is annotated in the IDR table
 * @scmi_requested_devices, then a matching device is created क्रम each alपढ़ोy
 * active SCMI instance. (अगर any)
 *
 * This way the requested device is created straight-away क्रम all the alपढ़ोy
 * initialized(probed) SCMI instances (handles) and it reमुख्यs also annotated
 * as pending creation अगर the requesting SCMI driver was loaded beक्रमe some
 * SCMI instance and related transports were available: when such late instance
 * is probed, its probe will take care to scan the list of pending requested
 * devices and create those on its own (see @scmi_create_protocol_devices and
 * its enclosing loop)
 *
 * Return: 0 on Success
 */
पूर्णांक scmi_protocol_device_request(स्थिर काष्ठा scmi_device_id *id_table)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक id = 0;
	काष्ठा list_head *head, *phead = शून्य;
	काष्ठा scmi_requested_dev *rdev;
	काष्ठा scmi_info *info;

	pr_debug("Requesting SCMI device (%s) for protocol %x\n",
		 id_table->name, id_table->protocol_id);

	/*
	 * Search क्रम the matching protocol rdev list and then search
	 * of any existent equally named device...fails अगर any duplicate found.
	 */
	mutex_lock(&scmi_requested_devices_mtx);
	idr_क्रम_each_entry(&scmi_requested_devices, head, id) अणु
		अगर (!phead) अणु
			/* A list found रेजिस्टरed in the IDR is never empty */
			rdev = list_first_entry(head, काष्ठा scmi_requested_dev,
						node);
			अगर (rdev->id_table->protocol_id ==
			    id_table->protocol_id)
				phead = head;
		पूर्ण
		list_क्रम_each_entry(rdev, head, node) अणु
			अगर (!म_भेद(rdev->id_table->name, id_table->name)) अणु
				pr_err("Ignoring duplicate request [%d] %s\n",
				       rdev->id_table->protocol_id,
				       rdev->id_table->name);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * No duplicate found क्रम requested id_table, so let's create a new
	 * requested device entry क्रम this new valid request.
	 */
	rdev = kzalloc(माप(*rdev), GFP_KERNEL);
	अगर (!rdev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	rdev->id_table = id_table;

	/*
	 * Append the new requested device table descriptor to the head of the
	 * related protocol list, eventually creating such head अगर not alपढ़ोy
	 * there.
	 */
	अगर (!phead) अणु
		phead = kzalloc(माप(*phead), GFP_KERNEL);
		अगर (!phead) अणु
			kमुक्त(rdev);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		INIT_LIST_HEAD(phead);

		ret = idr_alloc(&scmi_requested_devices, (व्योम *)phead,
				id_table->protocol_id,
				id_table->protocol_id + 1, GFP_KERNEL);
		अगर (ret != id_table->protocol_id) अणु
			pr_err("Failed to save SCMI device - ret:%d\n", ret);
			kमुक्त(rdev);
			kमुक्त(phead);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ret = 0;
	पूर्ण
	list_add(&rdev->node, phead);

	/*
	 * Now effectively create and initialize the requested device क्रम every
	 * alपढ़ोy initialized SCMI instance which has रेजिस्टरed the requested
	 * protocol as a valid active one: i.e. defined in DT and supported by
	 * current platक्रमm FW.
	 */
	mutex_lock(&scmi_list_mutex);
	list_क्रम_each_entry(info, &scmi_list, node) अणु
		काष्ठा device_node *child;

		child = idr_find(&info->active_protocols,
				 id_table->protocol_id);
		अगर (child) अणु
			काष्ठा scmi_device *sdev;

			sdev = scmi_get_protocol_device(child, info,
							id_table->protocol_id,
							id_table->name);
			/* Set handle अगर not alपढ़ोy set: device existed */
			अगर (sdev && !sdev->handle)
				sdev->handle =
					scmi_handle_get_from_info_unlocked(info);
		पूर्ण अन्यथा अणु
			dev_err(info->dev,
				"Failed. SCMI protocol %d not active.\n",
				id_table->protocol_id);
		पूर्ण
	पूर्ण
	mutex_unlock(&scmi_list_mutex);

out:
	mutex_unlock(&scmi_requested_devices_mtx);

	वापस ret;
पूर्ण

/**
 * scmi_protocol_device_unrequest  - Helper to unrequest a device
 *
 * @id_table: A protocol/name pair descriptor क्रम the device to be unrequested.
 *
 * An helper to let an SCMI driver release its request about devices; note that
 * devices are created and initialized once the first SCMI driver request them
 * but they destroyed only on SCMI core unloading/unbinding.
 *
 * The current SCMI transport layer uses such devices as पूर्णांकernal references and
 * as such they could be shared as same transport between multiple drivers so
 * that cannot be safely destroyed till the whole SCMI stack is हटाओd.
 * (unless adding further burden of refcounting.)
 */
व्योम scmi_protocol_device_unrequest(स्थिर काष्ठा scmi_device_id *id_table)
अणु
	काष्ठा list_head *phead;

	pr_debug("Unrequesting SCMI device (%s) for protocol %x\n",
		 id_table->name, id_table->protocol_id);

	mutex_lock(&scmi_requested_devices_mtx);
	phead = idr_find(&scmi_requested_devices, id_table->protocol_id);
	अगर (phead) अणु
		काष्ठा scmi_requested_dev *victim, *पंचांगp;

		list_क्रम_each_entry_safe(victim, पंचांगp, phead, node) अणु
			अगर (!म_भेद(victim->id_table->name, id_table->name)) अणु
				list_del(&victim->node);
				kमुक्त(victim);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (list_empty(phead)) अणु
			idr_हटाओ(&scmi_requested_devices,
				   id_table->protocol_id);
			kमुक्त(phead);
		पूर्ण
	पूर्ण
	mutex_unlock(&scmi_requested_devices_mtx);
पूर्ण

अटल पूर्णांक scmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा scmi_handle *handle;
	स्थिर काष्ठा scmi_desc *desc;
	काष्ठा scmi_info *info;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *child, *np = dev->of_node;

	desc = of_device_get_match_data(dev);
	अगर (!desc)
		वापस -EINVAL;

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = dev;
	info->desc = desc;
	INIT_LIST_HEAD(&info->node);
	idr_init(&info->protocols);
	mutex_init(&info->protocols_mtx);
	idr_init(&info->active_protocols);

	platक्रमm_set_drvdata(pdev, info);
	idr_init(&info->tx_idr);
	idr_init(&info->rx_idr);

	handle = &info->handle;
	handle->dev = info->dev;
	handle->version = &info->version;
	handle->devm_protocol_get = scmi_devm_protocol_get;
	handle->devm_protocol_put = scmi_devm_protocol_put;

	ret = scmi_txrx_setup(info, dev, SCMI_PROTOCOL_BASE);
	अगर (ret)
		वापस ret;

	ret = scmi_xfer_info_init(info);
	अगर (ret)
		वापस ret;

	अगर (scmi_notअगरication_init(handle))
		dev_err(dev, "SCMI Notifications NOT available.\n");

	/*
	 * Trigger SCMI Base protocol initialization.
	 * It's mandatory and won't be ever released/deinit until the
	 * SCMI stack is shutकरोwn/unloaded as a whole.
	 */
	ret = scmi_protocol_acquire(handle, SCMI_PROTOCOL_BASE);
	अगर (ret) अणु
		dev_err(dev, "unable to communicate with SCMI\n");
		वापस ret;
	पूर्ण

	mutex_lock(&scmi_list_mutex);
	list_add_tail(&info->node, &scmi_list);
	mutex_unlock(&scmi_list_mutex);

	क्रम_each_available_child_of_node(np, child) अणु
		u32 prot_id;

		अगर (of_property_पढ़ो_u32(child, "reg", &prot_id))
			जारी;

		अगर (!FIELD_FIT(MSG_PROTOCOL_ID_MASK, prot_id))
			dev_err(dev, "Out of range protocol %d\n", prot_id);

		अगर (!scmi_is_protocol_implemented(handle, prot_id)) अणु
			dev_err(dev, "SCMI protocol %d not implemented\n",
				prot_id);
			जारी;
		पूर्ण

		/*
		 * Save this valid DT protocol descriptor amongst
		 * @active_protocols क्रम this SCMI instance/
		 */
		ret = idr_alloc(&info->active_protocols, child,
				prot_id, prot_id + 1, GFP_KERNEL);
		अगर (ret != prot_id) अणु
			dev_err(dev, "SCMI protocol %d already activated. Skip\n",
				prot_id);
			जारी;
		पूर्ण

		of_node_get(child);
		scmi_create_protocol_devices(child, info, prot_id);
	पूर्ण

	वापस 0;
पूर्ण

व्योम scmi_मुक्त_channel(काष्ठा scmi_chan_info *cinfo, काष्ठा idr *idr, पूर्णांक id)
अणु
	idr_हटाओ(idr, id);
पूर्ण

अटल पूर्णांक scmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0, id;
	काष्ठा scmi_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा idr *idr = &info->tx_idr;
	काष्ठा device_node *child;

	mutex_lock(&scmi_list_mutex);
	अगर (info->users)
		ret = -EBUSY;
	अन्यथा
		list_del(&info->node);
	mutex_unlock(&scmi_list_mutex);

	अगर (ret)
		वापस ret;

	scmi_notअगरication_निकास(&info->handle);

	mutex_lock(&info->protocols_mtx);
	idr_destroy(&info->protocols);
	mutex_unlock(&info->protocols_mtx);

	idr_क्रम_each_entry(&info->active_protocols, child, id)
		of_node_put(child);
	idr_destroy(&info->active_protocols);

	/* Safe to मुक्त channels since no more users */
	ret = idr_क्रम_each(idr, info->desc->ops->chan_मुक्त, idr);
	idr_destroy(&info->tx_idr);

	idr = &info->rx_idr;
	ret = idr_क्रम_each(idr, info->desc->ops->chan_मुक्त, idr);
	idr_destroy(&info->rx_idr);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार protocol_version_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scmi_info *info = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u.%u\n", info->version.major_ver,
		       info->version.minor_ver);
पूर्ण
अटल DEVICE_ATTR_RO(protocol_version);

अटल sमाप_प्रकार firmware_version_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scmi_info *info = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "0x%x\n", info->version.impl_ver);
पूर्ण
अटल DEVICE_ATTR_RO(firmware_version);

अटल sमाप_प्रकार venकरोr_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scmi_info *info = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", info->version.venकरोr_id);
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr_id);

अटल sमाप_प्रकार sub_venकरोr_id_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scmi_info *info = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", info->version.sub_venकरोr_id);
पूर्ण
अटल DEVICE_ATTR_RO(sub_venकरोr_id);

अटल काष्ठा attribute *versions_attrs[] = अणु
	&dev_attr_firmware_version.attr,
	&dev_attr_protocol_version.attr,
	&dev_attr_venकरोr_id.attr,
	&dev_attr_sub_venकरोr_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(versions);

/* Each compatible listed below must have descriptor associated with it */
अटल स्थिर काष्ठा of_device_id scmi_of_match[] = अणु
	अणु .compatible = "arm,scmi", .data = &scmi_mailbox_desc पूर्ण,
#अगर_घोषित CONFIG_HAVE_ARM_SMCCC_DISCOVERY
	अणु .compatible = "arm,scmi-smc", .data = &scmi_smc_descपूर्ण,
#पूर्ण_अगर
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, scmi_of_match);

अटल काष्ठा platक्रमm_driver scmi_driver = अणु
	.driver = अणु
		   .name = "arm-scmi",
		   .of_match_table = scmi_of_match,
		   .dev_groups = versions_groups,
		   पूर्ण,
	.probe = scmi_probe,
	.हटाओ = scmi_हटाओ,
पूर्ण;

अटल पूर्णांक __init scmi_driver_init(व्योम)
अणु
	scmi_bus_init();

	scmi_base_रेजिस्टर();

	scmi_घड़ी_रेजिस्टर();
	scmi_perf_रेजिस्टर();
	scmi_घातer_रेजिस्टर();
	scmi_reset_रेजिस्टर();
	scmi_sensors_रेजिस्टर();
	scmi_voltage_रेजिस्टर();
	scmi_प्रणाली_रेजिस्टर();

	वापस platक्रमm_driver_रेजिस्टर(&scmi_driver);
पूर्ण
subsys_initcall(scmi_driver_init);

अटल व्योम __निकास scmi_driver_निकास(व्योम)
अणु
	scmi_base_unरेजिस्टर();

	scmi_घड़ी_unरेजिस्टर();
	scmi_perf_unरेजिस्टर();
	scmi_घातer_unरेजिस्टर();
	scmi_reset_unरेजिस्टर();
	scmi_sensors_unरेजिस्टर();
	scmi_voltage_unरेजिस्टर();
	scmi_प्रणाली_unरेजिस्टर();

	scmi_bus_निकास();

	platक्रमm_driver_unरेजिस्टर(&scmi_driver);
पूर्ण
module_निकास(scmi_driver_निकास);

MODULE_ALIAS("platform: arm-scmi");
MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCMI protocol driver");
MODULE_LICENSE("GPL v2");
