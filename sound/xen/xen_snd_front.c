<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 * Xen para-भव sound device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>

#समावेश <xen/page.h>
#समावेश <xen/platक्रमm_pci.h>
#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>

#समावेश <xen/xen-front-pgdir-shbuf.h>
#समावेश <xen/पूर्णांकerface/io/sndअगर.h>

#समावेश "xen_snd_front.h"
#समावेश "xen_snd_front_alsa.h"
#समावेश "xen_snd_front_evtchnl.h"

अटल काष्ठा xensnd_req *
be_stream_prepare_req(काष्ठा xen_snd_front_evtchnl *evtchnl, u8 operation)
अणु
	काष्ठा xensnd_req *req;

	req = RING_GET_REQUEST(&evtchnl->u.req.ring,
			       evtchnl->u.req.ring.req_prod_pvt);
	req->operation = operation;
	req->id = evtchnl->evt_next_id++;
	evtchnl->evt_id = req->id;
	वापस req;
पूर्ण

अटल पूर्णांक be_stream_करो_io(काष्ठा xen_snd_front_evtchnl *evtchnl)
अणु
	अगर (unlikely(evtchnl->state != EVTCHNL_STATE_CONNECTED))
		वापस -EIO;

	reinit_completion(&evtchnl->u.req.completion);
	xen_snd_front_evtchnl_flush(evtchnl);
	वापस 0;
पूर्ण

अटल पूर्णांक be_stream_रुको_io(काष्ठा xen_snd_front_evtchnl *evtchnl)
अणु
	अगर (रुको_क्रम_completion_समयout(&evtchnl->u.req.completion,
			msecs_to_jअगरfies(VSND_WAIT_BACK_MS)) <= 0)
		वापस -ETIMEDOUT;

	वापस evtchnl->u.req.resp_status;
पूर्ण

पूर्णांक xen_snd_front_stream_query_hw_param(काष्ठा xen_snd_front_evtchnl *evtchnl,
					काष्ठा xensnd_query_hw_param *hw_param_req,
					काष्ठा xensnd_query_hw_param *hw_param_resp)
अणु
	काष्ठा xensnd_req *req;
	पूर्णांक ret;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	mutex_lock(&evtchnl->ring_io_lock);
	req = be_stream_prepare_req(evtchnl, XENSND_OP_HW_PARAM_QUERY);
	req->op.hw_param = *hw_param_req;
	mutex_unlock(&evtchnl->ring_io_lock);

	ret = be_stream_करो_io(evtchnl);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	अगर (ret == 0)
		*hw_param_resp = evtchnl->u.req.resp.hw_param;

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

पूर्णांक xen_snd_front_stream_prepare(काष्ठा xen_snd_front_evtchnl *evtchnl,
				 काष्ठा xen_front_pgdir_shbuf *shbuf,
				 u8 क्रमmat, अचिन्हित पूर्णांक channels,
				 अचिन्हित पूर्णांक rate, u32 buffer_sz,
				 u32 period_sz)
अणु
	काष्ठा xensnd_req *req;
	पूर्णांक ret;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	mutex_lock(&evtchnl->ring_io_lock);
	req = be_stream_prepare_req(evtchnl, XENSND_OP_OPEN);
	req->op.खोलो.pcm_क्रमmat = क्रमmat;
	req->op.खोलो.pcm_channels = channels;
	req->op.खोलो.pcm_rate = rate;
	req->op.खोलो.buffer_sz = buffer_sz;
	req->op.खोलो.period_sz = period_sz;
	req->op.खोलो.gref_directory =
		xen_front_pgdir_shbuf_get_dir_start(shbuf);
	mutex_unlock(&evtchnl->ring_io_lock);

	ret = be_stream_करो_io(evtchnl);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

पूर्णांक xen_snd_front_stream_बंद(काष्ठा xen_snd_front_evtchnl *evtchnl)
अणु
	__always_unused काष्ठा xensnd_req *req;
	पूर्णांक ret;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	mutex_lock(&evtchnl->ring_io_lock);
	req = be_stream_prepare_req(evtchnl, XENSND_OP_CLOSE);
	mutex_unlock(&evtchnl->ring_io_lock);

	ret = be_stream_करो_io(evtchnl);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

पूर्णांक xen_snd_front_stream_ग_लिखो(काष्ठा xen_snd_front_evtchnl *evtchnl,
			       अचिन्हित दीर्घ pos, अचिन्हित दीर्घ count)
अणु
	काष्ठा xensnd_req *req;
	पूर्णांक ret;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	mutex_lock(&evtchnl->ring_io_lock);
	req = be_stream_prepare_req(evtchnl, XENSND_OP_WRITE);
	req->op.rw.length = count;
	req->op.rw.offset = pos;
	mutex_unlock(&evtchnl->ring_io_lock);

	ret = be_stream_करो_io(evtchnl);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

पूर्णांक xen_snd_front_stream_पढ़ो(काष्ठा xen_snd_front_evtchnl *evtchnl,
			      अचिन्हित दीर्घ pos, अचिन्हित दीर्घ count)
अणु
	काष्ठा xensnd_req *req;
	पूर्णांक ret;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	mutex_lock(&evtchnl->ring_io_lock);
	req = be_stream_prepare_req(evtchnl, XENSND_OP_READ);
	req->op.rw.length = count;
	req->op.rw.offset = pos;
	mutex_unlock(&evtchnl->ring_io_lock);

	ret = be_stream_करो_io(evtchnl);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

पूर्णांक xen_snd_front_stream_trigger(काष्ठा xen_snd_front_evtchnl *evtchnl,
				 पूर्णांक type)
अणु
	काष्ठा xensnd_req *req;
	पूर्णांक ret;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	mutex_lock(&evtchnl->ring_io_lock);
	req = be_stream_prepare_req(evtchnl, XENSND_OP_TRIGGER);
	req->op.trigger.type = type;
	mutex_unlock(&evtchnl->ring_io_lock);

	ret = be_stream_करो_io(evtchnl);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

अटल व्योम xen_snd_drv_fini(काष्ठा xen_snd_front_info *front_info)
अणु
	xen_snd_front_alsa_fini(front_info);
	xen_snd_front_evtchnl_मुक्त_all(front_info);
पूर्ण

अटल पूर्णांक sndback_initरुको(काष्ठा xen_snd_front_info *front_info)
अणु
	पूर्णांक num_streams;
	पूर्णांक ret;

	ret = xen_snd_front_cfg_card(front_info, &num_streams);
	अगर (ret < 0)
		वापस ret;

	/* create event channels क्रम all streams and publish */
	ret = xen_snd_front_evtchnl_create_all(front_info, num_streams);
	अगर (ret < 0)
		वापस ret;

	वापस xen_snd_front_evtchnl_publish_all(front_info);
पूर्ण

अटल पूर्णांक sndback_connect(काष्ठा xen_snd_front_info *front_info)
अणु
	वापस xen_snd_front_alsa_init(front_info);
पूर्ण

अटल व्योम sndback_disconnect(काष्ठा xen_snd_front_info *front_info)
अणु
	xen_snd_drv_fini(front_info);
	xenbus_चयन_state(front_info->xb_dev, XenbusStateInitialising);
पूर्ण

अटल व्योम sndback_changed(काष्ठा xenbus_device *xb_dev,
			    क्रमागत xenbus_state backend_state)
अणु
	काष्ठा xen_snd_front_info *front_info = dev_get_drvdata(&xb_dev->dev);
	पूर्णांक ret;

	dev_dbg(&xb_dev->dev, "Backend state is %s, front is %s\n",
		xenbus_strstate(backend_state),
		xenbus_strstate(xb_dev->state));

	चयन (backend_state) अणु
	हाल XenbusStateReconfiguring:
	हाल XenbusStateReconfigured:
	हाल XenbusStateInitialised:
		अवरोध;

	हाल XenbusStateInitialising:
		/* Recovering after backend unexpected closure. */
		sndback_disconnect(front_info);
		अवरोध;

	हाल XenbusStateInitWait:
		/* Recovering after backend unexpected closure. */
		sndback_disconnect(front_info);

		ret = sndback_initरुको(front_info);
		अगर (ret < 0)
			xenbus_dev_fatal(xb_dev, ret, "initializing frontend");
		अन्यथा
			xenbus_चयन_state(xb_dev, XenbusStateInitialised);
		अवरोध;

	हाल XenbusStateConnected:
		अगर (xb_dev->state != XenbusStateInitialised)
			अवरोध;

		ret = sndback_connect(front_info);
		अगर (ret < 0)
			xenbus_dev_fatal(xb_dev, ret, "initializing frontend");
		अन्यथा
			xenbus_चयन_state(xb_dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosing:
		/*
		 * In this state backend starts मुक्तing resources,
		 * so let it go पूर्णांकo बंदd state first, so we can also
		 * हटाओ ours.
		 */
		अवरोध;

	हाल XenbusStateUnknown:
	हाल XenbusStateClosed:
		अगर (xb_dev->state == XenbusStateClosed)
			अवरोध;

		sndback_disconnect(front_info);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xen_drv_probe(काष्ठा xenbus_device *xb_dev,
			 स्थिर काष्ठा xenbus_device_id *id)
अणु
	काष्ठा xen_snd_front_info *front_info;

	front_info = devm_kzalloc(&xb_dev->dev,
				  माप(*front_info), GFP_KERNEL);
	अगर (!front_info)
		वापस -ENOMEM;

	front_info->xb_dev = xb_dev;
	dev_set_drvdata(&xb_dev->dev, front_info);

	वापस xenbus_चयन_state(xb_dev, XenbusStateInitialising);
पूर्ण

अटल पूर्णांक xen_drv_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xen_snd_front_info *front_info = dev_get_drvdata(&dev->dev);
	पूर्णांक to = 100;

	xenbus_चयन_state(dev, XenbusStateClosing);

	/*
	 * On driver removal it is disconnected from XenBus,
	 * so no backend state change events come via .otherend_changed
	 * callback. This prevents us from निकासing gracefully, e.g.
	 * संकेतing the backend to मुक्त event channels, रुकोing क्रम its
	 * state to change to XenbusStateClosed and cleaning at our end.
	 * Normally when front driver हटाओd backend will finally go पूर्णांकo
	 * XenbusStateInitWait state.
	 *
	 * Workaround: पढ़ो backend's state manually and रुको with समय-out.
	 */
	जबतक ((xenbus_पढ़ो_अचिन्हित(front_info->xb_dev->otherend, "state",
				     XenbusStateUnknown) != XenbusStateInitWait) &&
	       --to)
		msleep(10);

	अगर (!to) अणु
		अचिन्हित पूर्णांक state;

		state = xenbus_पढ़ो_अचिन्हित(front_info->xb_dev->otherend,
					     "state", XenbusStateUnknown);
		pr_err("Backend state is %s while removing driver\n",
		       xenbus_strstate(state));
	पूर्ण

	xen_snd_drv_fini(front_info);
	xenbus_frontend_बंदd(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id xen_drv_ids[] = अणु
	अणु XENSND_DRIVER_NAME पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver xen_driver = अणु
	.ids = xen_drv_ids,
	.probe = xen_drv_probe,
	.हटाओ = xen_drv_हटाओ,
	.otherend_changed = sndback_changed,
पूर्ण;

अटल पूर्णांक __init xen_drv_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_has_pv_devices())
		वापस -ENODEV;

	/* At the moment we only support हाल with XEN_PAGE_SIZE == PAGE_SIZE */
	अगर (XEN_PAGE_SIZE != PAGE_SIZE) अणु
		pr_err(XENSND_DRIVER_NAME ": different kernel and Xen page sizes are not supported: XEN_PAGE_SIZE (%lu) != PAGE_SIZE (%lu)\n",
		       XEN_PAGE_SIZE, PAGE_SIZE);
		वापस -ENODEV;
	पूर्ण

	pr_info("Initialising Xen " XENSND_DRIVER_NAME " frontend driver\n");
	वापस xenbus_रेजिस्टर_frontend(&xen_driver);
पूर्ण

अटल व्योम __निकास xen_drv_fini(व्योम)
अणु
	pr_info("Unregistering Xen " XENSND_DRIVER_NAME " frontend driver\n");
	xenbus_unरेजिस्टर_driver(&xen_driver);
पूर्ण

module_init(xen_drv_init);
module_निकास(xen_drv_fini);

MODULE_DESCRIPTION("Xen virtual sound device frontend");
MODULE_LICENSE("GPL");
MODULE_ALIAS("xen:" XENSND_DRIVER_NAME);
