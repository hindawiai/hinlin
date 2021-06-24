<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2018, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/export.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/mei.h>

#समावेश "mei_dev.h"
#समावेश "hbm.h"
#समावेश "client.h"


/**
 * mei_irq_compl_handler - dispatch complete handlers
 *	क्रम the completed callbacks
 *
 * @dev: mei device
 * @cmpl_list: list of completed cbs
 */
व्योम mei_irq_compl_handler(काष्ठा mei_device *dev, काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_cl_cb *cb, *next;
	काष्ठा mei_cl *cl;

	list_क्रम_each_entry_safe(cb, next, cmpl_list, list) अणु
		cl = cb->cl;
		list_del_init(&cb->list);

		dev_dbg(dev->dev, "completing call back.\n");
		mei_cl_complete(cl, cb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mei_irq_compl_handler);

/**
 * mei_cl_hbm_equal - check अगर hbm is addressed to the client
 *
 * @cl: host client
 * @mei_hdr: header of mei client message
 *
 * Return: true अगर matches, false otherwise
 */
अटल अंतरभूत पूर्णांक mei_cl_hbm_equal(काष्ठा mei_cl *cl,
			काष्ठा mei_msg_hdr *mei_hdr)
अणु
	वापस  mei_cl_host_addr(cl) == mei_hdr->host_addr &&
		mei_cl_me_id(cl) == mei_hdr->me_addr;
पूर्ण

/**
 * mei_irq_discard_msg  - discard received message
 *
 * @dev: mei device
 * @hdr: message header
 * @discard_len: the length of the message to discard (excluding header)
 */
अटल व्योम mei_irq_discard_msg(काष्ठा mei_device *dev, काष्ठा mei_msg_hdr *hdr,
				माप_प्रकार discard_len)
अणु
	अगर (hdr->dma_ring) अणु
		mei_dma_ring_पढ़ो(dev, शून्य,
				  hdr->extension[dev->rd_msg_hdr_count - 2]);
		discard_len = 0;
	पूर्ण
	/*
	 * no need to check क्रम size as it is guarantied
	 * that length fits पूर्णांकo rd_msg_buf
	 */
	mei_पढ़ो_slots(dev, dev->rd_msg_buf, discard_len);
	dev_dbg(dev->dev, "discarding message " MEI_HDR_FMT "\n",
		MEI_HDR_PRM(hdr));
पूर्ण

/**
 * mei_cl_irq_पढ़ो_msg - process client message
 *
 * @cl: पढ़ोing client
 * @mei_hdr: header of mei client message
 * @meta: extend meta header
 * @cmpl_list: completion list
 *
 * Return: always 0
 */
अटल पूर्णांक mei_cl_irq_पढ़ो_msg(काष्ठा mei_cl *cl,
			       काष्ठा mei_msg_hdr *mei_hdr,
			       काष्ठा mei_ext_meta_hdr *meta,
			       काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_device *dev = cl->dev;
	काष्ठा mei_cl_cb *cb;

	माप_प्रकार buf_sz;
	u32 length;
	पूर्णांक ext_len;

	length = mei_hdr->length;
	ext_len = 0;
	अगर (mei_hdr->extended) अणु
		ext_len = माप(*meta) + mei_slots2data(meta->size);
		length -= ext_len;
	पूर्ण

	cb = list_first_entry_or_null(&cl->rd_pending, काष्ठा mei_cl_cb, list);
	अगर (!cb) अणु
		अगर (!mei_cl_is_fixed_address(cl)) अणु
			cl_err(dev, cl, "pending read cb not found\n");
			जाओ discard;
		पूर्ण
		cb = mei_cl_alloc_cb(cl, mei_cl_mtu(cl), MEI_FOP_READ, cl->fp);
		अगर (!cb)
			जाओ discard;
		list_add_tail(&cb->list, &cl->rd_pending);
	पूर्ण

	अगर (mei_hdr->extended) अणु
		काष्ठा mei_ext_hdr *ext;
		काष्ठा mei_ext_hdr *vtag = शून्य;

		ext = mei_ext_begin(meta);
		करो अणु
			चयन (ext->type) अणु
			हाल MEI_EXT_HDR_VTAG:
				vtag = ext;
				अवरोध;
			हाल MEI_EXT_HDR_NONE:
				fallthrough;
			शेष:
				cb->status = -EPROTO;
				अवरोध;
			पूर्ण

			ext = mei_ext_next(ext);
		पूर्ण जबतक (!mei_ext_last(meta, ext));

		अगर (!vtag) अणु
			cl_dbg(dev, cl, "vtag not found in extended header.\n");
			cb->status = -EPROTO;
			जाओ discard;
		पूर्ण

		cl_dbg(dev, cl, "vtag: %d\n", vtag->ext_payload[0]);
		अगर (cb->vtag && cb->vtag != vtag->ext_payload[0]) अणु
			cl_err(dev, cl, "mismatched tag: %d != %d\n",
			       cb->vtag, vtag->ext_payload[0]);
			cb->status = -EPROTO;
			जाओ discard;
		पूर्ण
		cb->vtag = vtag->ext_payload[0];
	पूर्ण

	अगर (!mei_cl_is_connected(cl)) अणु
		cl_dbg(dev, cl, "not connected\n");
		cb->status = -ENODEV;
		जाओ discard;
	पूर्ण

	अगर (mei_hdr->dma_ring)
		length = mei_hdr->extension[mei_data2slots(ext_len)];

	buf_sz = length + cb->buf_idx;
	/* catch क्रम पूर्णांकeger overflow */
	अगर (buf_sz < cb->buf_idx) अणु
		cl_err(dev, cl, "message is too big len %d idx %zu\n",
		       length, cb->buf_idx);
		cb->status = -EMSGSIZE;
		जाओ discard;
	पूर्ण

	अगर (cb->buf.size < buf_sz) अणु
		cl_dbg(dev, cl, "message overflow. size %zu len %d idx %zu\n",
			cb->buf.size, length, cb->buf_idx);
		cb->status = -EMSGSIZE;
		जाओ discard;
	पूर्ण

	अगर (mei_hdr->dma_ring) अणु
		mei_dma_ring_पढ़ो(dev, cb->buf.data + cb->buf_idx, length);
		/*  क्रम DMA पढ़ो 0 length to generate पूर्णांकerrupt to the device */
		mei_पढ़ो_slots(dev, cb->buf.data + cb->buf_idx, 0);
	पूर्ण अन्यथा अणु
		mei_पढ़ो_slots(dev, cb->buf.data + cb->buf_idx, length);
	पूर्ण

	cb->buf_idx += length;

	अगर (mei_hdr->msg_complete) अणु
		cl_dbg(dev, cl, "completed read length = %zu\n", cb->buf_idx);
		list_move_tail(&cb->list, cmpl_list);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(dev->dev);
		pm_request_स्वतःsuspend(dev->dev);
	पूर्ण

	वापस 0;

discard:
	अगर (cb)
		list_move_tail(&cb->list, cmpl_list);
	mei_irq_discard_msg(dev, mei_hdr, length);
	वापस 0;
पूर्ण

/**
 * mei_cl_irq_disconnect_rsp - send disconnection response message
 *
 * @cl: client
 * @cb: callback block.
 * @cmpl_list: complete list.
 *
 * Return: 0, OK; otherwise, error.
 */
अटल पूर्णांक mei_cl_irq_disconnect_rsp(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
				     काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_device *dev = cl->dev;
	u32 msg_slots;
	पूर्णांक slots;
	पूर्णांक ret;

	msg_slots = mei_hbm2slots(माप(काष्ठा hbm_client_connect_response));
	slots = mei_hbuf_empty_slots(dev);
	अगर (slots < 0)
		वापस -EOVERFLOW;

	अगर ((u32)slots < msg_slots)
		वापस -EMSGSIZE;

	ret = mei_hbm_cl_disconnect_rsp(dev, cl);
	list_move_tail(&cb->list, cmpl_list);

	वापस ret;
पूर्ण

/**
 * mei_cl_irq_पढ़ो - processes client पढ़ो related operation from the
 *	पूर्णांकerrupt thपढ़ो context - request क्रम flow control credits
 *
 * @cl: client
 * @cb: callback block.
 * @cmpl_list: complete list.
 *
 * Return: 0, OK; otherwise, error.
 */
अटल पूर्णांक mei_cl_irq_पढ़ो(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
			   काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_device *dev = cl->dev;
	u32 msg_slots;
	पूर्णांक slots;
	पूर्णांक ret;

	अगर (!list_empty(&cl->rd_pending))
		वापस 0;

	msg_slots = mei_hbm2slots(माप(काष्ठा hbm_flow_control));
	slots = mei_hbuf_empty_slots(dev);
	अगर (slots < 0)
		वापस -EOVERFLOW;

	अगर ((u32)slots < msg_slots)
		वापस -EMSGSIZE;

	ret = mei_hbm_cl_flow_control_req(dev, cl);
	अगर (ret) अणु
		cl->status = ret;
		cb->buf_idx = 0;
		list_move_tail(&cb->list, cmpl_list);
		वापस ret;
	पूर्ण

	pm_runसमय_mark_last_busy(dev->dev);
	pm_request_स्वतःsuspend(dev->dev);

	list_move_tail(&cb->list, &cl->rd_pending);

	वापस 0;
पूर्ण

अटल अंतरभूत bool hdr_is_hbm(काष्ठा mei_msg_hdr *mei_hdr)
अणु
	वापस mei_hdr->host_addr == 0 && mei_hdr->me_addr == 0;
पूर्ण

अटल अंतरभूत bool hdr_is_fixed(काष्ठा mei_msg_hdr *mei_hdr)
अणु
	वापस mei_hdr->host_addr == 0 && mei_hdr->me_addr != 0;
पूर्ण

अटल अंतरभूत पूर्णांक hdr_is_valid(u32 msg_hdr)
अणु
	काष्ठा mei_msg_hdr *mei_hdr;
	u32 expected_len = 0;

	mei_hdr = (काष्ठा mei_msg_hdr *)&msg_hdr;
	अगर (!msg_hdr || mei_hdr->reserved)
		वापस -EBADMSG;

	अगर (mei_hdr->dma_ring)
		expected_len += MEI_SLOT_SIZE;
	अगर (mei_hdr->extended)
		expected_len += MEI_SLOT_SIZE;
	अगर (mei_hdr->length < expected_len)
		वापस -EBADMSG;

	वापस 0;
पूर्ण

/**
 * mei_irq_पढ़ो_handler - bottom half पढ़ो routine after ISR to
 * handle the पढ़ो processing.
 *
 * @dev: the device काष्ठाure
 * @cmpl_list: An instance of our list काष्ठाure
 * @slots: slots to पढ़ो.
 *
 * Return: 0 on success, <0 on failure.
 */
पूर्णांक mei_irq_पढ़ो_handler(काष्ठा mei_device *dev,
			 काष्ठा list_head *cmpl_list, s32 *slots)
अणु
	काष्ठा mei_msg_hdr *mei_hdr;
	काष्ठा mei_ext_meta_hdr *meta_hdr = शून्य;
	काष्ठा mei_cl *cl;
	पूर्णांक ret;
	u32 ext_meta_hdr_u32;
	u32 hdr_size_left;
	u32 hdr_size_ext;
	पूर्णांक i;
	पूर्णांक ext_hdr_end;

	अगर (!dev->rd_msg_hdr[0]) अणु
		dev->rd_msg_hdr[0] = mei_पढ़ो_hdr(dev);
		dev->rd_msg_hdr_count = 1;
		(*slots)--;
		dev_dbg(dev->dev, "slots =%08x.\n", *slots);

		ret = hdr_is_valid(dev->rd_msg_hdr[0]);
		अगर (ret) अणु
			dev_err(dev->dev, "corrupted message header 0x%08X\n",
				dev->rd_msg_hdr[0]);
			जाओ end;
		पूर्ण
	पूर्ण

	mei_hdr = (काष्ठा mei_msg_hdr *)dev->rd_msg_hdr;
	dev_dbg(dev->dev, MEI_HDR_FMT, MEI_HDR_PRM(mei_hdr));

	अगर (mei_slots2data(*slots) < mei_hdr->length) अणु
		dev_err(dev->dev, "less data available than length=%08x.\n",
				*slots);
		/* we can't पढ़ो the message */
		ret = -ENODATA;
		जाओ end;
	पूर्ण

	ext_hdr_end = 1;
	hdr_size_left = mei_hdr->length;

	अगर (mei_hdr->extended) अणु
		अगर (!dev->rd_msg_hdr[1]) अणु
			ext_meta_hdr_u32 = mei_पढ़ो_hdr(dev);
			dev->rd_msg_hdr[1] = ext_meta_hdr_u32;
			dev->rd_msg_hdr_count++;
			(*slots)--;
			dev_dbg(dev->dev, "extended header is %08x\n",
				ext_meta_hdr_u32);
		पूर्ण
		meta_hdr = ((काष्ठा mei_ext_meta_hdr *)dev->rd_msg_hdr + 1);
		अगर (check_add_overflow((u32)माप(*meta_hdr),
				       mei_slots2data(meta_hdr->size),
				       &hdr_size_ext)) अणु
			dev_err(dev->dev, "extended message size too big %d\n",
				meta_hdr->size);
			वापस -EBADMSG;
		पूर्ण
		अगर (hdr_size_left < hdr_size_ext) अणु
			dev_err(dev->dev, "corrupted message header len %d\n",
				mei_hdr->length);
			वापस -EBADMSG;
		पूर्ण
		hdr_size_left -= hdr_size_ext;

		ext_hdr_end = meta_hdr->size + 2;
		क्रम (i = dev->rd_msg_hdr_count; i < ext_hdr_end; i++) अणु
			dev->rd_msg_hdr[i] = mei_पढ़ो_hdr(dev);
			dev_dbg(dev->dev, "extended header %d is %08x\n", i,
				dev->rd_msg_hdr[i]);
			dev->rd_msg_hdr_count++;
			(*slots)--;
		पूर्ण
	पूर्ण

	अगर (mei_hdr->dma_ring) अणु
		अगर (hdr_size_left != माप(dev->rd_msg_hdr[ext_hdr_end])) अणु
			dev_err(dev->dev, "corrupted message header len %d\n",
				mei_hdr->length);
			वापस -EBADMSG;
		पूर्ण

		dev->rd_msg_hdr[ext_hdr_end] = mei_पढ़ो_hdr(dev);
		dev->rd_msg_hdr_count++;
		(*slots)--;
		mei_hdr->length -= माप(dev->rd_msg_hdr[ext_hdr_end]);
	पूर्ण

	/*  HBM message */
	अगर (hdr_is_hbm(mei_hdr)) अणु
		ret = mei_hbm_dispatch(dev, mei_hdr);
		अगर (ret) अणु
			dev_dbg(dev->dev, "mei_hbm_dispatch failed ret = %d\n",
					ret);
			जाओ end;
		पूर्ण
		जाओ reset_slots;
	पूर्ण

	/* find recipient cl */
	list_क्रम_each_entry(cl, &dev->file_list, link) अणु
		अगर (mei_cl_hbm_equal(cl, mei_hdr)) अणु
			cl_dbg(dev, cl, "got a message\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* अगर no recipient cl was found we assume corrupted header */
	अगर (&cl->link == &dev->file_list) अणु
		/* A message क्रम not connected fixed address clients
		 * should be silently discarded
		 * On घातer करोwn client may be क्रमce cleaned,
		 * silently discard such messages
		 */
		अगर (hdr_is_fixed(mei_hdr) ||
		    dev->dev_state == MEI_DEV_POWER_DOWN) अणु
			mei_irq_discard_msg(dev, mei_hdr, mei_hdr->length);
			ret = 0;
			जाओ reset_slots;
		पूर्ण
		dev_err(dev->dev, "no destination client found 0x%08X\n",
				dev->rd_msg_hdr[0]);
		ret = -EBADMSG;
		जाओ end;
	पूर्ण

	ret = mei_cl_irq_पढ़ो_msg(cl, mei_hdr, meta_hdr, cmpl_list);


reset_slots:
	/* reset the number of slots and header */
	स_रखो(dev->rd_msg_hdr, 0, माप(dev->rd_msg_hdr));
	dev->rd_msg_hdr_count = 0;
	*slots = mei_count_full_पढ़ो_slots(dev);
	अगर (*slots == -EOVERFLOW) अणु
		/* overflow - reset */
		dev_err(dev->dev, "resetting due to slots overflow.\n");
		/* set the event since message has been पढ़ो */
		ret = -दुस्फल;
		जाओ end;
	पूर्ण
end:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mei_irq_पढ़ो_handler);


/**
 * mei_irq_ग_लिखो_handler -  dispatch ग_लिखो requests
 *  after irq received
 *
 * @dev: the device काष्ठाure
 * @cmpl_list: An instance of our list काष्ठाure
 *
 * Return: 0 on success, <0 on failure.
 */
पूर्णांक mei_irq_ग_लिखो_handler(काष्ठा mei_device *dev, काष्ठा list_head *cmpl_list)
अणु

	काष्ठा mei_cl *cl;
	काष्ठा mei_cl_cb *cb, *next;
	s32 slots;
	पूर्णांक ret;


	अगर (!mei_hbuf_acquire(dev))
		वापस 0;

	slots = mei_hbuf_empty_slots(dev);
	अगर (slots < 0)
		वापस -EOVERFLOW;

	अगर (slots == 0)
		वापस -EMSGSIZE;

	/* complete all रुकोing क्रम ग_लिखो CB */
	dev_dbg(dev->dev, "complete all waiting for write cb.\n");

	list_क्रम_each_entry_safe(cb, next, &dev->ग_लिखो_रुकोing_list, list) अणु
		cl = cb->cl;

		cl->status = 0;
		cl_dbg(dev, cl, "MEI WRITE COMPLETE\n");
		cl->writing_state = MEI_WRITE_COMPLETE;
		list_move_tail(&cb->list, cmpl_list);
	पूर्ण

	/* complete control ग_लिखो list CB */
	dev_dbg(dev->dev, "complete control write list cb.\n");
	list_क्रम_each_entry_safe(cb, next, &dev->ctrl_wr_list, list) अणु
		cl = cb->cl;
		चयन (cb->fop_type) अणु
		हाल MEI_FOP_DISCONNECT:
			/* send disconnect message */
			ret = mei_cl_irq_disconnect(cl, cb, cmpl_list);
			अगर (ret)
				वापस ret;

			अवरोध;
		हाल MEI_FOP_READ:
			/* send flow control message */
			ret = mei_cl_irq_पढ़ो(cl, cb, cmpl_list);
			अगर (ret)
				वापस ret;

			अवरोध;
		हाल MEI_FOP_CONNECT:
			/* connect message */
			ret = mei_cl_irq_connect(cl, cb, cmpl_list);
			अगर (ret)
				वापस ret;

			अवरोध;
		हाल MEI_FOP_DISCONNECT_RSP:
			/* send disconnect resp */
			ret = mei_cl_irq_disconnect_rsp(cl, cb, cmpl_list);
			अगर (ret)
				वापस ret;
			अवरोध;

		हाल MEI_FOP_NOTIFY_START:
		हाल MEI_FOP_NOTIFY_STOP:
			ret = mei_cl_irq_notअगरy(cl, cb, cmpl_list);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल MEI_FOP_DMA_MAP:
			ret = mei_cl_irq_dma_map(cl, cb, cmpl_list);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल MEI_FOP_DMA_UNMAP:
			ret = mei_cl_irq_dma_unmap(cl, cb, cmpl_list);
			अगर (ret)
				वापस ret;
			अवरोध;
		शेष:
			BUG();
		पूर्ण

	पूर्ण
	/* complete  ग_लिखो list CB */
	dev_dbg(dev->dev, "complete write list cb.\n");
	list_क्रम_each_entry_safe(cb, next, &dev->ग_लिखो_list, list) अणु
		cl = cb->cl;
		ret = mei_cl_irq_ग_लिखो(cl, cb, cmpl_list);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mei_irq_ग_लिखो_handler);


/**
 * mei_connect_समयout  - connect/disconnect समयouts
 *
 * @cl: host client
 */
अटल व्योम mei_connect_समयout(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev = cl->dev;

	अगर (cl->state == MEI_खाता_CONNECTING) अणु
		अगर (dev->hbm_f_करोt_supported) अणु
			cl->state = MEI_खाता_DISCONNECT_REQUIRED;
			wake_up(&cl->रुको);
			वापस;
		पूर्ण
	पूर्ण
	mei_reset(dev);
पूर्ण

#घोषणा MEI_STALL_TIMER_FREQ (2 * HZ)
/**
 * mei_schedule_stall_समयr - re-arm stall_समयr work
 *
 * Schedule stall समयr
 *
 * @dev: the device काष्ठाure
 */
व्योम mei_schedule_stall_समयr(काष्ठा mei_device *dev)
अणु
	schedule_delayed_work(&dev->समयr_work, MEI_STALL_TIMER_FREQ);
पूर्ण

/**
 * mei_समयr - समयr function.
 *
 * @work: poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 */
व्योम mei_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mei_cl *cl;
	काष्ठा mei_device *dev = container_of(work,
					काष्ठा mei_device, समयr_work.work);
	bool reschedule_समयr = false;

	mutex_lock(&dev->device_lock);

	/* Catch पूर्णांकerrupt stalls during HBM init handshake */
	अगर (dev->dev_state == MEI_DEV_INIT_CLIENTS &&
	    dev->hbm_state != MEI_HBM_IDLE) अणु

		अगर (dev->init_clients_समयr) अणु
			अगर (--dev->init_clients_समयr == 0) अणु
				dev_err(dev->dev, "timer: init clients timeout hbm_state = %d.\n",
					dev->hbm_state);
				mei_reset(dev);
				जाओ out;
			पूर्ण
			reschedule_समयr = true;
		पूर्ण
	पूर्ण

	अगर (dev->dev_state != MEI_DEV_ENABLED)
		जाओ out;

	/*** connect/disconnect समयouts ***/
	list_क्रम_each_entry(cl, &dev->file_list, link) अणु
		अगर (cl->समयr_count) अणु
			अगर (--cl->समयr_count == 0) अणु
				dev_err(dev->dev, "timer: connect/disconnect timeout.\n");
				mei_connect_समयout(cl);
				जाओ out;
			पूर्ण
			reschedule_समयr = true;
		पूर्ण
	पूर्ण

out:
	अगर (dev->dev_state != MEI_DEV_DISABLED && reschedule_समयr)
		mei_schedule_stall_समयr(dev);

	mutex_unlock(&dev->device_lock);
पूर्ण
