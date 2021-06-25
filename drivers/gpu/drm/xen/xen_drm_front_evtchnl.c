<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irq.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश <xen/xenbus.h>
#समावेश <xen/events.h>
#समावेश <xen/grant_table.h>

#समावेश "xen_drm_front.h"
#समावेश "xen_drm_front_evtchnl.h"

अटल irqवापस_t evtchnl_पूर्णांकerrupt_ctrl(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xen_drm_front_evtchnl *evtchnl = dev_id;
	काष्ठा xen_drm_front_info *front_info = evtchnl->front_info;
	काष्ठा xendispl_resp *resp;
	RING_IDX i, rp;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(evtchnl->state != EVTCHNL_STATE_CONNECTED))
		वापस IRQ_HANDLED;

	spin_lock_irqsave(&front_info->io_lock, flags);

again:
	rp = evtchnl->u.req.ring.sring->rsp_prod;
	/* ensure we see queued responses up to rp */
	virt_rmb();

	क्रम (i = evtchnl->u.req.ring.rsp_cons; i != rp; i++) अणु
		resp = RING_GET_RESPONSE(&evtchnl->u.req.ring, i);
		अगर (unlikely(resp->id != evtchnl->evt_id))
			जारी;

		चयन (resp->operation) अणु
		हाल XENDISPL_OP_PG_FLIP:
		हाल XENDISPL_OP_FB_ATTACH:
		हाल XENDISPL_OP_FB_DETACH:
		हाल XENDISPL_OP_DBUF_CREATE:
		हाल XENDISPL_OP_DBUF_DESTROY:
		हाल XENDISPL_OP_SET_CONFIG:
			evtchnl->u.req.resp_status = resp->status;
			complete(&evtchnl->u.req.completion);
			अवरोध;

		शेष:
			DRM_ERROR("Operation %d is not supported\n",
				  resp->operation);
			अवरोध;
		पूर्ण
	पूर्ण

	evtchnl->u.req.ring.rsp_cons = i;

	अगर (i != evtchnl->u.req.ring.req_prod_pvt) अणु
		पूर्णांक more_to_करो;

		RING_FINAL_CHECK_FOR_RESPONSES(&evtchnl->u.req.ring,
					       more_to_करो);
		अगर (more_to_करो)
			जाओ again;
	पूर्ण अन्यथा अणु
		evtchnl->u.req.ring.sring->rsp_event = i + 1;
	पूर्ण

	spin_unlock_irqrestore(&front_info->io_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t evtchnl_पूर्णांकerrupt_evt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xen_drm_front_evtchnl *evtchnl = dev_id;
	काष्ठा xen_drm_front_info *front_info = evtchnl->front_info;
	काष्ठा xendispl_event_page *page = evtchnl->u.evt.page;
	u32 cons, prod;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(evtchnl->state != EVTCHNL_STATE_CONNECTED))
		वापस IRQ_HANDLED;

	spin_lock_irqsave(&front_info->io_lock, flags);

	prod = page->in_prod;
	/* ensure we see ring contents up to prod */
	virt_rmb();
	अगर (prod == page->in_cons)
		जाओ out;

	क्रम (cons = page->in_cons; cons != prod; cons++) अणु
		काष्ठा xendispl_evt *event;

		event = &XENDISPL_IN_RING_REF(page, cons);
		अगर (unlikely(event->id != evtchnl->evt_id++))
			जारी;

		चयन (event->type) अणु
		हाल XENDISPL_EVT_PG_FLIP:
			xen_drm_front_on_frame_करोne(front_info, evtchnl->index,
						    event->op.pg_flip.fb_cookie);
			अवरोध;
		पूर्ण
	पूर्ण
	page->in_cons = cons;
	/* ensure ring contents */
	virt_wmb();

out:
	spin_unlock_irqrestore(&front_info->io_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम evtchnl_मुक्त(काष्ठा xen_drm_front_info *front_info,
			 काष्ठा xen_drm_front_evtchnl *evtchnl)
अणु
	अचिन्हित दीर्घ page = 0;

	अगर (evtchnl->type == EVTCHNL_TYPE_REQ)
		page = (अचिन्हित दीर्घ)evtchnl->u.req.ring.sring;
	अन्यथा अगर (evtchnl->type == EVTCHNL_TYPE_EVT)
		page = (अचिन्हित दीर्घ)evtchnl->u.evt.page;
	अगर (!page)
		वापस;

	evtchnl->state = EVTCHNL_STATE_DISCONNECTED;

	अगर (evtchnl->type == EVTCHNL_TYPE_REQ) अणु
		/* release all who still रुकोs क्रम response अगर any */
		evtchnl->u.req.resp_status = -EIO;
		complete_all(&evtchnl->u.req.completion);
	पूर्ण

	अगर (evtchnl->irq)
		unbind_from_irqhandler(evtchnl->irq, evtchnl);

	अगर (evtchnl->port)
		xenbus_मुक्त_evtchn(front_info->xb_dev, evtchnl->port);

	/* end access and मुक्त the page */
	अगर (evtchnl->gref != GRANT_INVALID_REF)
		gnttab_end_क्रमeign_access(evtchnl->gref, 0, page);

	स_रखो(evtchnl, 0, माप(*evtchnl));
पूर्ण

अटल पूर्णांक evtchnl_alloc(काष्ठा xen_drm_front_info *front_info, पूर्णांक index,
			 काष्ठा xen_drm_front_evtchnl *evtchnl,
			 क्रमागत xen_drm_front_evtchnl_type type)
अणु
	काष्ठा xenbus_device *xb_dev = front_info->xb_dev;
	अचिन्हित दीर्घ page;
	grant_ref_t gref;
	irq_handler_t handler;
	पूर्णांक ret;

	स_रखो(evtchnl, 0, माप(*evtchnl));
	evtchnl->type = type;
	evtchnl->index = index;
	evtchnl->front_info = front_info;
	evtchnl->state = EVTCHNL_STATE_DISCONNECTED;
	evtchnl->gref = GRANT_INVALID_REF;

	page = get_zeroed_page(GFP_NOIO | __GFP_HIGH);
	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	अगर (type == EVTCHNL_TYPE_REQ) अणु
		काष्ठा xen_displअगर_sring *sring;

		init_completion(&evtchnl->u.req.completion);
		mutex_init(&evtchnl->u.req.req_io_lock);
		sring = (काष्ठा xen_displअगर_sring *)page;
		SHARED_RING_INIT(sring);
		FRONT_RING_INIT(&evtchnl->u.req.ring, sring, XEN_PAGE_SIZE);

		ret = xenbus_grant_ring(xb_dev, sring, 1, &gref);
		अगर (ret < 0) अणु
			evtchnl->u.req.ring.sring = शून्य;
			मुक्त_page(page);
			जाओ fail;
		पूर्ण

		handler = evtchnl_पूर्णांकerrupt_ctrl;
	पूर्ण अन्यथा अणु
		ret = gnttab_grant_क्रमeign_access(xb_dev->otherend_id,
						  virt_to_gfn((व्योम *)page), 0);
		अगर (ret < 0) अणु
			मुक्त_page(page);
			जाओ fail;
		पूर्ण

		evtchnl->u.evt.page = (काष्ठा xendispl_event_page *)page;
		gref = ret;
		handler = evtchnl_पूर्णांकerrupt_evt;
	पूर्ण
	evtchnl->gref = gref;

	ret = xenbus_alloc_evtchn(xb_dev, &evtchnl->port);
	अगर (ret < 0)
		जाओ fail;

	ret = bind_evtchn_to_irqhandler(evtchnl->port,
					handler, 0, xb_dev->devicetype,
					evtchnl);
	अगर (ret < 0)
		जाओ fail;

	evtchnl->irq = ret;
	वापस 0;

fail:
	DRM_ERROR("Failed to allocate ring: %d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक xen_drm_front_evtchnl_create_all(काष्ठा xen_drm_front_info *front_info)
अणु
	काष्ठा xen_drm_front_cfg *cfg;
	पूर्णांक ret, conn;

	cfg = &front_info->cfg;

	front_info->evt_pairs =
			kसुस्मृति(cfg->num_connectors,
				माप(काष्ठा xen_drm_front_evtchnl_pair),
				GFP_KERNEL);
	अगर (!front_info->evt_pairs) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	क्रम (conn = 0; conn < cfg->num_connectors; conn++) अणु
		ret = evtchnl_alloc(front_info, conn,
				    &front_info->evt_pairs[conn].req,
				    EVTCHNL_TYPE_REQ);
		अगर (ret < 0) अणु
			DRM_ERROR("Error allocating control channel\n");
			जाओ fail;
		पूर्ण

		ret = evtchnl_alloc(front_info, conn,
				    &front_info->evt_pairs[conn].evt,
				    EVTCHNL_TYPE_EVT);
		अगर (ret < 0) अणु
			DRM_ERROR("Error allocating in-event channel\n");
			जाओ fail;
		पूर्ण
	पूर्ण
	front_info->num_evt_pairs = cfg->num_connectors;
	वापस 0;

fail:
	xen_drm_front_evtchnl_मुक्त_all(front_info);
	वापस ret;
पूर्ण

अटल पूर्णांक evtchnl_publish(काष्ठा xenbus_transaction xbt,
			   काष्ठा xen_drm_front_evtchnl *evtchnl,
			   स्थिर अक्षर *path, स्थिर अक्षर *node_ring,
			   स्थिर अक्षर *node_chnl)
अणु
	काष्ठा xenbus_device *xb_dev = evtchnl->front_info->xb_dev;
	पूर्णांक ret;

	/* ग_लिखो control channel ring reference */
	ret = xenbus_म_लिखो(xbt, path, node_ring, "%u", evtchnl->gref);
	अगर (ret < 0) अणु
		xenbus_dev_error(xb_dev, ret, "writing ring-ref");
		वापस ret;
	पूर्ण

	/* ग_लिखो event channel ring reference */
	ret = xenbus_म_लिखो(xbt, path, node_chnl, "%u", evtchnl->port);
	अगर (ret < 0) अणु
		xenbus_dev_error(xb_dev, ret, "writing event channel");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक xen_drm_front_evtchnl_publish_all(काष्ठा xen_drm_front_info *front_info)
अणु
	काष्ठा xenbus_transaction xbt;
	काष्ठा xen_drm_front_cfg *plat_data;
	पूर्णांक ret, conn;

	plat_data = &front_info->cfg;

again:
	ret = xenbus_transaction_start(&xbt);
	अगर (ret < 0) अणु
		xenbus_dev_fatal(front_info->xb_dev, ret,
				 "starting transaction");
		वापस ret;
	पूर्ण

	क्रम (conn = 0; conn < plat_data->num_connectors; conn++) अणु
		ret = evtchnl_publish(xbt, &front_info->evt_pairs[conn].req,
				      plat_data->connectors[conn].xenstore_path,
				      XENDISPL_FIELD_REQ_RING_REF,
				      XENDISPL_FIELD_REQ_CHANNEL);
		अगर (ret < 0)
			जाओ fail;

		ret = evtchnl_publish(xbt, &front_info->evt_pairs[conn].evt,
				      plat_data->connectors[conn].xenstore_path,
				      XENDISPL_FIELD_EVT_RING_REF,
				      XENDISPL_FIELD_EVT_CHANNEL);
		अगर (ret < 0)
			जाओ fail;
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
	xenbus_dev_fatal(front_info->xb_dev, ret, "writing Xen store");
	वापस ret;
पूर्ण

व्योम xen_drm_front_evtchnl_flush(काष्ठा xen_drm_front_evtchnl *evtchnl)
अणु
	पूर्णांक notअगरy;

	evtchnl->u.req.ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&evtchnl->u.req.ring, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(evtchnl->irq);
पूर्ण

व्योम xen_drm_front_evtchnl_set_state(काष्ठा xen_drm_front_info *front_info,
				     क्रमागत xen_drm_front_evtchnl_state state)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (!front_info->evt_pairs)
		वापस;

	spin_lock_irqsave(&front_info->io_lock, flags);
	क्रम (i = 0; i < front_info->num_evt_pairs; i++) अणु
		front_info->evt_pairs[i].req.state = state;
		front_info->evt_pairs[i].evt.state = state;
	पूर्ण
	spin_unlock_irqrestore(&front_info->io_lock, flags);
पूर्ण

व्योम xen_drm_front_evtchnl_मुक्त_all(काष्ठा xen_drm_front_info *front_info)
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
