<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 * Xen para-भव sound device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <xen/events.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>

#समावेश "xen_snd_front.h"
#समावेश "xen_snd_front_alsa.h"
#समावेश "xen_snd_front_cfg.h"
#समावेश "xen_snd_front_evtchnl.h"

अटल irqवापस_t evtchnl_पूर्णांकerrupt_req(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xen_snd_front_evtchnl *channel = dev_id;
	काष्ठा xen_snd_front_info *front_info = channel->front_info;
	काष्ठा xensnd_resp *resp;
	RING_IDX i, rp;

	अगर (unlikely(channel->state != EVTCHNL_STATE_CONNECTED))
		वापस IRQ_HANDLED;

	mutex_lock(&channel->ring_io_lock);

again:
	rp = channel->u.req.ring.sring->rsp_prod;
	/* Ensure we see queued responses up to rp. */
	rmb();

	/*
	 * Assume that the backend is trusted to always ग_लिखो sane values
	 * to the ring counters, so no overflow checks on frontend side
	 * are required.
	 */
	क्रम (i = channel->u.req.ring.rsp_cons; i != rp; i++) अणु
		resp = RING_GET_RESPONSE(&channel->u.req.ring, i);
		अगर (resp->id != channel->evt_id)
			जारी;
		चयन (resp->operation) अणु
		हाल XENSND_OP_OPEN:
		हाल XENSND_OP_CLOSE:
		हाल XENSND_OP_READ:
		हाल XENSND_OP_WRITE:
		हाल XENSND_OP_TRIGGER:
			channel->u.req.resp_status = resp->status;
			complete(&channel->u.req.completion);
			अवरोध;
		हाल XENSND_OP_HW_PARAM_QUERY:
			channel->u.req.resp_status = resp->status;
			channel->u.req.resp.hw_param =
					resp->resp.hw_param;
			complete(&channel->u.req.completion);
			अवरोध;

		शेष:
			dev_err(&front_info->xb_dev->dev,
				"Operation %d is not supported\n",
				resp->operation);
			अवरोध;
		पूर्ण
	पूर्ण

	channel->u.req.ring.rsp_cons = i;
	अगर (i != channel->u.req.ring.req_prod_pvt) अणु
		पूर्णांक more_to_करो;

		RING_FINAL_CHECK_FOR_RESPONSES(&channel->u.req.ring,
					       more_to_करो);
		अगर (more_to_करो)
			जाओ again;
	पूर्ण अन्यथा अणु
		channel->u.req.ring.sring->rsp_event = i + 1;
	पूर्ण

	mutex_unlock(&channel->ring_io_lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t evtchnl_पूर्णांकerrupt_evt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xen_snd_front_evtchnl *channel = dev_id;
	काष्ठा xensnd_event_page *page = channel->u.evt.page;
	u32 cons, prod;

	अगर (unlikely(channel->state != EVTCHNL_STATE_CONNECTED))
		वापस IRQ_HANDLED;

	mutex_lock(&channel->ring_io_lock);

	prod = page->in_prod;
	/* Ensure we see ring contents up to prod. */
	virt_rmb();
	अगर (prod == page->in_cons)
		जाओ out;

	/*
	 * Assume that the backend is trusted to always ग_लिखो sane values
	 * to the ring counters, so no overflow checks on frontend side
	 * are required.
	 */
	क्रम (cons = page->in_cons; cons != prod; cons++) अणु
		काष्ठा xensnd_evt *event;

		event = &XENSND_IN_RING_REF(page, cons);
		अगर (unlikely(event->id != channel->evt_id++))
			जारी;

		चयन (event->type) अणु
		हाल XENSND_EVT_CUR_POS:
			xen_snd_front_alsa_handle_cur_pos(channel,
							  event->op.cur_pos.position);
			अवरोध;
		पूर्ण
	पूर्ण

	page->in_cons = cons;
	/* Ensure ring contents. */
	virt_wmb();

out:
	mutex_unlock(&channel->ring_io_lock);
	वापस IRQ_HANDLED;
पूर्ण

व्योम xen_snd_front_evtchnl_flush(काष्ठा xen_snd_front_evtchnl *channel)
अणु
	पूर्णांक notअगरy;

	channel->u.req.ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&channel->u.req.ring, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(channel->irq);
पूर्ण

अटल व्योम evtchnl_मुक्त(काष्ठा xen_snd_front_info *front_info,
			 काष्ठा xen_snd_front_evtchnl *channel)
अणु
	अचिन्हित दीर्घ page = 0;

	अगर (channel->type == EVTCHNL_TYPE_REQ)
		page = (अचिन्हित दीर्घ)channel->u.req.ring.sring;
	अन्यथा अगर (channel->type == EVTCHNL_TYPE_EVT)
		page = (अचिन्हित दीर्घ)channel->u.evt.page;

	अगर (!page)
		वापस;

	channel->state = EVTCHNL_STATE_DISCONNECTED;
	अगर (channel->type == EVTCHNL_TYPE_REQ) अणु
		/* Release all who still रुकोs क्रम response अगर any. */
		channel->u.req.resp_status = -EIO;
		complete_all(&channel->u.req.completion);
	पूर्ण

	अगर (channel->irq)
		unbind_from_irqhandler(channel->irq, channel);

	अगर (channel->port)
		xenbus_मुक्त_evtchn(front_info->xb_dev, channel->port);

	/* End access and मुक्त the page. */
	अगर (channel->gref != GRANT_INVALID_REF)
		gnttab_end_क्रमeign_access(channel->gref, 0, page);
	अन्यथा
		मुक्त_page(page);

	स_रखो(channel, 0, माप(*channel));
पूर्ण

व्योम xen_snd_front_evtchnl_मुक्त_all(काष्ठा xen_snd_front_info *front_info)
अणु
	पूर्णांक i;

	अगर (!front_info->evt_pairs)
		वापस;

	क्रम (i = 0; i < front_info->num_evt_pairs; i++) अणु
		evtchnl_मुक्त(front_info, &front_info->evt_pairs[i].req);
		evtchnl_मुक्त(front_info, &front_info->evt_pairs[i].evt);
	पूर्ण

	kमुक्त(front_info->evt_pairs);
	front_info->evt_pairs = शून्य;
पूर्ण

अटल पूर्णांक evtchnl_alloc(काष्ठा xen_snd_front_info *front_info, पूर्णांक index,
			 काष्ठा xen_snd_front_evtchnl *channel,
			 क्रमागत xen_snd_front_evtchnl_type type)
अणु
	काष्ठा xenbus_device *xb_dev = front_info->xb_dev;
	अचिन्हित दीर्घ page;
	grant_ref_t gref;
	irq_handler_t handler;
	अक्षर *handler_name = शून्य;
	पूर्णांक ret;

	स_रखो(channel, 0, माप(*channel));
	channel->type = type;
	channel->index = index;
	channel->front_info = front_info;
	channel->state = EVTCHNL_STATE_DISCONNECTED;
	channel->gref = GRANT_INVALID_REF;
	page = get_zeroed_page(GFP_KERNEL);
	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	handler_name = kaप्र_लिखो(GFP_KERNEL, "%s-%s", XENSND_DRIVER_NAME,
				 type == EVTCHNL_TYPE_REQ ?
				 XENSND_FIELD_RING_REF :
				 XENSND_FIELD_EVT_RING_REF);
	अगर (!handler_name) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	mutex_init(&channel->ring_io_lock);

	अगर (type == EVTCHNL_TYPE_REQ) अणु
		काष्ठा xen_sndअगर_sring *sring = (काष्ठा xen_sndअगर_sring *)page;

		init_completion(&channel->u.req.completion);
		mutex_init(&channel->u.req.req_io_lock);
		SHARED_RING_INIT(sring);
		FRONT_RING_INIT(&channel->u.req.ring, sring, XEN_PAGE_SIZE);

		ret = xenbus_grant_ring(xb_dev, sring, 1, &gref);
		अगर (ret < 0) अणु
			channel->u.req.ring.sring = शून्य;
			जाओ fail;
		पूर्ण

		handler = evtchnl_पूर्णांकerrupt_req;
	पूर्ण अन्यथा अणु
		ret = gnttab_grant_क्रमeign_access(xb_dev->otherend_id,
						  virt_to_gfn((व्योम *)page), 0);
		अगर (ret < 0)
			जाओ fail;

		channel->u.evt.page = (काष्ठा xensnd_event_page *)page;
		gref = ret;
		handler = evtchnl_पूर्णांकerrupt_evt;
	पूर्ण

	channel->gref = gref;

	ret = xenbus_alloc_evtchn(xb_dev, &channel->port);
	अगर (ret < 0)
		जाओ fail;

	ret = bind_evtchn_to_irq(channel->port);
	अगर (ret < 0) अणु
		dev_err(&xb_dev->dev,
			"Failed to bind IRQ for domid %d port %d: %d\n",
			front_info->xb_dev->otherend_id, channel->port, ret);
		जाओ fail;
	पूर्ण

	channel->irq = ret;

	ret = request_thपढ़ोed_irq(channel->irq, शून्य, handler,
				   IRQF_ONESHOT, handler_name, channel);
	अगर (ret < 0) अणु
		dev_err(&xb_dev->dev, "Failed to request IRQ %d: %d\n",
			channel->irq, ret);
		जाओ fail;
	पूर्ण

	kमुक्त(handler_name);
	वापस 0;

fail:
	अगर (page)
		मुक्त_page(page);
	kमुक्त(handler_name);
	dev_err(&xb_dev->dev, "Failed to allocate ring: %d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक xen_snd_front_evtchnl_create_all(काष्ठा xen_snd_front_info *front_info,
				     पूर्णांक num_streams)
अणु
	काष्ठा xen_front_cfg_card *cfg = &front_info->cfg;
	काष्ठा device *dev = &front_info->xb_dev->dev;
	पूर्णांक d, ret = 0;

	front_info->evt_pairs =
			kसुस्मृति(num_streams,
				माप(काष्ठा xen_snd_front_evtchnl_pair),
				GFP_KERNEL);
	अगर (!front_info->evt_pairs)
		वापस -ENOMEM;

	/* Iterate over devices and their streams and create event channels. */
	क्रम (d = 0; d < cfg->num_pcm_instances; d++) अणु
		काष्ठा xen_front_cfg_pcm_instance *pcm_instance;
		पूर्णांक s, index;

		pcm_instance = &cfg->pcm_instances[d];

		क्रम (s = 0; s < pcm_instance->num_streams_pb; s++) अणु
			index = pcm_instance->streams_pb[s].index;

			ret = evtchnl_alloc(front_info, index,
					    &front_info->evt_pairs[index].req,
					    EVTCHNL_TYPE_REQ);
			अगर (ret < 0) अणु
				dev_err(dev, "Error allocating control channel\n");
				जाओ fail;
			पूर्ण

			ret = evtchnl_alloc(front_info, index,
					    &front_info->evt_pairs[index].evt,
					    EVTCHNL_TYPE_EVT);
			अगर (ret < 0) अणु
				dev_err(dev, "Error allocating in-event channel\n");
				जाओ fail;
			पूर्ण
		पूर्ण

		क्रम (s = 0; s < pcm_instance->num_streams_cap; s++) अणु
			index = pcm_instance->streams_cap[s].index;

			ret = evtchnl_alloc(front_info, index,
					    &front_info->evt_pairs[index].req,
					    EVTCHNL_TYPE_REQ);
			अगर (ret < 0) अणु
				dev_err(dev, "Error allocating control channel\n");
				जाओ fail;
			पूर्ण

			ret = evtchnl_alloc(front_info, index,
					    &front_info->evt_pairs[index].evt,
					    EVTCHNL_TYPE_EVT);
			अगर (ret < 0) अणु
				dev_err(dev, "Error allocating in-event channel\n");
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	front_info->num_evt_pairs = num_streams;
	वापस 0;

fail:
	xen_snd_front_evtchnl_मुक्त_all(front_info);
	वापस ret;
पूर्ण

अटल पूर्णांक evtchnl_publish(काष्ठा xenbus_transaction xbt,
			   काष्ठा xen_snd_front_evtchnl *channel,
			   स्थिर अक्षर *path, स्थिर अक्षर *node_ring,
			   स्थिर अक्षर *node_chnl)
अणु
	काष्ठा xenbus_device *xb_dev = channel->front_info->xb_dev;
	पूर्णांक ret;

	/* Write control channel ring reference. */
	ret = xenbus_म_लिखो(xbt, path, node_ring, "%u", channel->gref);
	अगर (ret < 0) अणु
		dev_err(&xb_dev->dev, "Error writing ring-ref: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Write event channel ring reference. */
	ret = xenbus_म_लिखो(xbt, path, node_chnl, "%u", channel->port);
	अगर (ret < 0) अणु
		dev_err(&xb_dev->dev, "Error writing event channel: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक xen_snd_front_evtchnl_publish_all(काष्ठा xen_snd_front_info *front_info)
अणु
	काष्ठा xen_front_cfg_card *cfg = &front_info->cfg;
	काष्ठा xenbus_transaction xbt;
	पूर्णांक ret, d;

again:
	ret = xenbus_transaction_start(&xbt);
	अगर (ret < 0) अणु
		xenbus_dev_fatal(front_info->xb_dev, ret,
				 "starting transaction");
		वापस ret;
	पूर्ण

	क्रम (d = 0; d < cfg->num_pcm_instances; d++) अणु
		काष्ठा xen_front_cfg_pcm_instance *pcm_instance;
		पूर्णांक s, index;

		pcm_instance = &cfg->pcm_instances[d];

		क्रम (s = 0; s < pcm_instance->num_streams_pb; s++) अणु
			index = pcm_instance->streams_pb[s].index;

			ret = evtchnl_publish(xbt,
					      &front_info->evt_pairs[index].req,
					      pcm_instance->streams_pb[s].xenstore_path,
					      XENSND_FIELD_RING_REF,
					      XENSND_FIELD_EVT_CHNL);
			अगर (ret < 0)
				जाओ fail;

			ret = evtchnl_publish(xbt,
					      &front_info->evt_pairs[index].evt,
					      pcm_instance->streams_pb[s].xenstore_path,
					      XENSND_FIELD_EVT_RING_REF,
					      XENSND_FIELD_EVT_EVT_CHNL);
			अगर (ret < 0)
				जाओ fail;
		पूर्ण

		क्रम (s = 0; s < pcm_instance->num_streams_cap; s++) अणु
			index = pcm_instance->streams_cap[s].index;

			ret = evtchnl_publish(xbt,
					      &front_info->evt_pairs[index].req,
					      pcm_instance->streams_cap[s].xenstore_path,
					      XENSND_FIELD_RING_REF,
					      XENSND_FIELD_EVT_CHNL);
			अगर (ret < 0)
				जाओ fail;

			ret = evtchnl_publish(xbt,
					      &front_info->evt_pairs[index].evt,
					      pcm_instance->streams_cap[s].xenstore_path,
					      XENSND_FIELD_EVT_RING_REF,
					      XENSND_FIELD_EVT_EVT_CHNL);
			अगर (ret < 0)
				जाओ fail;
		पूर्ण
	पूर्ण
	ret = xenbus_transaction_end(xbt, 0);
	अगर (ret < 0) अणु
		अगर (ret == -EAGAIN)
			जाओ again;

		xenbus_dev_fatal(front_info->xb_dev, ret,
				 "completing transaction");
		जाओ fail_to_end;
	पूर्ण
	वापस 0;
fail:
	xenbus_transaction_end(xbt, 1);
fail_to_end:
	xenbus_dev_fatal(front_info->xb_dev, ret, "writing XenStore");
	वापस ret;
पूर्ण

व्योम xen_snd_front_evtchnl_pair_set_connected(काष्ठा xen_snd_front_evtchnl_pair *evt_pair,
					      bool is_connected)
अणु
	क्रमागत xen_snd_front_evtchnl_state state;

	अगर (is_connected)
		state = EVTCHNL_STATE_CONNECTED;
	अन्यथा
		state = EVTCHNL_STATE_DISCONNECTED;

	mutex_lock(&evt_pair->req.ring_io_lock);
	evt_pair->req.state = state;
	mutex_unlock(&evt_pair->req.ring_io_lock);

	mutex_lock(&evt_pair->evt.ring_io_lock);
	evt_pair->evt.state = state;
	mutex_unlock(&evt_pair->evt.ring_io_lock);
पूर्ण

व्योम xen_snd_front_evtchnl_pair_clear(काष्ठा xen_snd_front_evtchnl_pair *evt_pair)
अणु
	mutex_lock(&evt_pair->req.ring_io_lock);
	evt_pair->req.evt_next_id = 0;
	mutex_unlock(&evt_pair->req.ring_io_lock);

	mutex_lock(&evt_pair->evt.ring_io_lock);
	evt_pair->evt.evt_next_id = 0;
	mutex_unlock(&evt_pair->evt.ring_io_lock);
पूर्ण

