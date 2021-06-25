<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Copyright (C) 2019 Renesas Electronics Corporation
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश "common.h"

/*
 *		काष्ठा
 */
काष्ठा usbhsg_request अणु
	काष्ठा usb_request	req;
	काष्ठा usbhs_pkt	pkt;
पूर्ण;

#घोषणा EP_NAME_SIZE 8
काष्ठा usbhsg_gpriv;
काष्ठा usbhsg_uep अणु
	काष्ठा usb_ep		 ep;
	काष्ठा usbhs_pipe	*pipe;
	spinlock_t		lock;	/* protect the pipe */

	अक्षर ep_name[EP_NAME_SIZE];

	काष्ठा usbhsg_gpriv *gpriv;
पूर्ण;

काष्ठा usbhsg_gpriv अणु
	काष्ठा usb_gadget	 gadget;
	काष्ठा usbhs_mod	 mod;

	काष्ठा usbhsg_uep	*uep;
	पूर्णांक			 uep_size;

	काष्ठा usb_gadget_driver	*driver;
	काष्ठा usb_phy		*transceiver;
	bool			 vbus_active;

	u32	status;
#घोषणा USBHSG_STATUS_STARTED		(1 << 0)
#घोषणा USBHSG_STATUS_REGISTERD		(1 << 1)
#घोषणा USBHSG_STATUS_WEDGE		(1 << 2)
#घोषणा USBHSG_STATUS_SELF_POWERED	(1 << 3)
#घोषणा USBHSG_STATUS_SOFT_CONNECT	(1 << 4)
पूर्ण;

काष्ठा usbhsg_recip_handle अणु
	अक्षर *name;
	पूर्णांक (*device)(काष्ठा usbhs_priv *priv, काष्ठा usbhsg_uep *uep,
		      काष्ठा usb_ctrlrequest *ctrl);
	पूर्णांक (*पूर्णांकerface)(काष्ठा usbhs_priv *priv, काष्ठा usbhsg_uep *uep,
			 काष्ठा usb_ctrlrequest *ctrl);
	पूर्णांक (*endpoपूर्णांक)(काष्ठा usbhs_priv *priv, काष्ठा usbhsg_uep *uep,
			काष्ठा usb_ctrlrequest *ctrl);
पूर्ण;

/*
 *		macro
 */
#घोषणा usbhsg_priv_to_gpriv(priv)			\
	container_of(					\
		usbhs_mod_get(priv, USBHS_GADGET),	\
		काष्ठा usbhsg_gpriv, mod)

#घोषणा __usbhsg_क्रम_each_uep(start, pos, g, i)	\
	क्रम ((i) = start;					\
	     ((i) < (g)->uep_size) && ((pos) = (g)->uep + (i));	\
	     (i)++)

#घोषणा usbhsg_क्रम_each_uep(pos, gpriv, i)	\
	__usbhsg_क्रम_each_uep(1, pos, gpriv, i)

#घोषणा usbhsg_क्रम_each_uep_with_dcp(pos, gpriv, i)	\
	__usbhsg_क्रम_each_uep(0, pos, gpriv, i)

#घोषणा usbhsg_gadget_to_gpriv(g)\
	container_of(g, काष्ठा usbhsg_gpriv, gadget)

#घोषणा usbhsg_req_to_ureq(r)\
	container_of(r, काष्ठा usbhsg_request, req)

#घोषणा usbhsg_ep_to_uep(e)		container_of(e, काष्ठा usbhsg_uep, ep)
#घोषणा usbhsg_gpriv_to_dev(gp)		usbhs_priv_to_dev((gp)->mod.priv)
#घोषणा usbhsg_gpriv_to_priv(gp)	((gp)->mod.priv)
#घोषणा usbhsg_gpriv_to_dcp(gp)		((gp)->uep)
#घोषणा usbhsg_gpriv_to_nth_uep(gp, i)	((gp)->uep + i)
#घोषणा usbhsg_uep_to_gpriv(u)		((u)->gpriv)
#घोषणा usbhsg_uep_to_pipe(u)		((u)->pipe)
#घोषणा usbhsg_pipe_to_uep(p)		((p)->mod_निजी)
#घोषणा usbhsg_is_dcp(u)		((u) == usbhsg_gpriv_to_dcp((u)->gpriv))

#घोषणा usbhsg_ureq_to_pkt(u)		(&(u)->pkt)
#घोषणा usbhsg_pkt_to_ureq(i)	\
	container_of(i, काष्ठा usbhsg_request, pkt)

#घोषणा usbhsg_is_not_connected(gp) ((gp)->gadget.speed == USB_SPEED_UNKNOWN)

/* status */
#घोषणा usbhsg_status_init(gp)   करो अणु(gp)->status = 0; पूर्ण जबतक (0)
#घोषणा usbhsg_status_set(gp, b) (gp->status |=  b)
#घोषणा usbhsg_status_clr(gp, b) (gp->status &= ~b)
#घोषणा usbhsg_status_has(gp, b) (gp->status &   b)

/*
 *		queue push/pop
 */
अटल व्योम __usbhsg_queue_pop(काष्ठा usbhsg_uep *uep,
			       काष्ठा usbhsg_request *ureq,
			       पूर्णांक status)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	काष्ठा device *dev = usbhsg_gpriv_to_dev(gpriv);
	काष्ठा usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);

	अगर (pipe)
		dev_dbg(dev, "pipe %d : queue pop\n", usbhs_pipe_number(pipe));

	ureq->req.status = status;
	spin_unlock(usbhs_priv_to_lock(priv));
	usb_gadget_giveback_request(&uep->ep, &ureq->req);
	spin_lock(usbhs_priv_to_lock(priv));
पूर्ण

अटल व्योम usbhsg_queue_pop(काष्ठा usbhsg_uep *uep,
			     काष्ठा usbhsg_request *ureq,
			     पूर्णांक status)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	काष्ठा usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	अचिन्हित दीर्घ flags;

	usbhs_lock(priv, flags);
	__usbhsg_queue_pop(uep, ureq, status);
	usbhs_unlock(priv, flags);
पूर्ण

अटल व्योम usbhsg_queue_करोne(काष्ठा usbhs_priv *priv, काष्ठा usbhs_pkt *pkt)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhsg_uep *uep = usbhsg_pipe_to_uep(pipe);
	काष्ठा usbhsg_request *ureq = usbhsg_pkt_to_ureq(pkt);
	अचिन्हित दीर्घ flags;

	ureq->req.actual = pkt->actual;

	usbhs_lock(priv, flags);
	अगर (uep)
		__usbhsg_queue_pop(uep, ureq, 0);
	usbhs_unlock(priv, flags);
पूर्ण

अटल व्योम usbhsg_queue_push(काष्ठा usbhsg_uep *uep,
			      काष्ठा usbhsg_request *ureq)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	काष्ठा device *dev = usbhsg_gpriv_to_dev(gpriv);
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	काष्ठा usbhs_pkt *pkt = usbhsg_ureq_to_pkt(ureq);
	काष्ठा usb_request *req = &ureq->req;

	req->actual = 0;
	req->status = -EINPROGRESS;
	usbhs_pkt_push(pipe, pkt, usbhsg_queue_करोne,
		       req->buf, req->length, req->zero, -1);
	usbhs_pkt_start(pipe);

	dev_dbg(dev, "pipe %d : queue push (%d)\n",
		usbhs_pipe_number(pipe),
		req->length);
पूर्ण

/*
 *		dma map/unmap
 */
अटल पूर्णांक usbhsg_dma_map_ctrl(काष्ठा device *dma_dev, काष्ठा usbhs_pkt *pkt,
			       पूर्णांक map)
अणु
	काष्ठा usbhsg_request *ureq = usbhsg_pkt_to_ureq(pkt);
	काष्ठा usb_request *req = &ureq->req;
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	क्रमागत dma_data_direction dir;
	पूर्णांक ret = 0;

	dir = usbhs_pipe_is_dir_host(pipe);

	अगर (map) अणु
		/* it can not use scatter/gather */
		WARN_ON(req->num_sgs);

		ret = usb_gadget_map_request_by_dev(dma_dev, req, dir);
		अगर (ret < 0)
			वापस ret;

		pkt->dma = req->dma;
	पूर्ण अन्यथा अणु
		usb_gadget_unmap_request_by_dev(dma_dev, req, dir);
	पूर्ण

	वापस ret;
पूर्ण

/*
 *		USB_TYPE_STANDARD / clear feature functions
 */
अटल पूर्णांक usbhsg_recip_handler_std_control_करोne(काष्ठा usbhs_priv *priv,
						 काष्ठा usbhsg_uep *uep,
						 काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);
	काष्ठा usbhsg_uep *dcp = usbhsg_gpriv_to_dcp(gpriv);
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(dcp);

	usbhs_dcp_control_transfer_करोne(pipe);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsg_recip_handler_std_clear_endpoपूर्णांक(काष्ठा usbhs_priv *priv,
						   काष्ठा usbhsg_uep *uep,
						   काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);

	अगर (!usbhsg_status_has(gpriv, USBHSG_STATUS_WEDGE)) अणु
		usbhs_pipe_disable(pipe);
		usbhs_pipe_sequence_data0(pipe);
		usbhs_pipe_enable(pipe);
	पूर्ण

	usbhsg_recip_handler_std_control_करोne(priv, uep, ctrl);

	usbhs_pkt_start(pipe);

	वापस 0;
पूर्ण

अटल काष्ठा usbhsg_recip_handle req_clear_feature = अणु
	.name		= "clear feature",
	.device		= usbhsg_recip_handler_std_control_करोne,
	.पूर्णांकerface	= usbhsg_recip_handler_std_control_करोne,
	.endpoपूर्णांक	= usbhsg_recip_handler_std_clear_endpoपूर्णांक,
पूर्ण;

/*
 *		USB_TYPE_STANDARD / set feature functions
 */
अटल पूर्णांक usbhsg_recip_handler_std_set_device(काष्ठा usbhs_priv *priv,
						 काष्ठा usbhsg_uep *uep,
						 काष्ठा usb_ctrlrequest *ctrl)
अणु
	चयन (le16_to_cpu(ctrl->wValue)) अणु
	हाल USB_DEVICE_TEST_MODE:
		usbhsg_recip_handler_std_control_करोne(priv, uep, ctrl);
		udelay(100);
		usbhs_sys_set_test_mode(priv, le16_to_cpu(ctrl->wIndex) >> 8);
		अवरोध;
	शेष:
		usbhsg_recip_handler_std_control_करोne(priv, uep, ctrl);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsg_recip_handler_std_set_endpoपूर्णांक(काष्ठा usbhs_priv *priv,
						 काष्ठा usbhsg_uep *uep,
						 काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);

	usbhs_pipe_stall(pipe);

	usbhsg_recip_handler_std_control_करोne(priv, uep, ctrl);

	वापस 0;
पूर्ण

अटल काष्ठा usbhsg_recip_handle req_set_feature = अणु
	.name		= "set feature",
	.device		= usbhsg_recip_handler_std_set_device,
	.पूर्णांकerface	= usbhsg_recip_handler_std_control_करोne,
	.endpoपूर्णांक	= usbhsg_recip_handler_std_set_endpoपूर्णांक,
पूर्ण;

/*
 *		USB_TYPE_STANDARD / get status functions
 */
अटल व्योम __usbhsg_recip_send_complete(काष्ठा usb_ep *ep,
					 काष्ठा usb_request *req)
अणु
	काष्ठा usbhsg_request *ureq = usbhsg_req_to_ureq(req);

	/* मुक्त allocated recip-buffer/usb_request */
	kमुक्त(ureq->pkt.buf);
	usb_ep_मुक्त_request(ep, req);
पूर्ण

अटल व्योम __usbhsg_recip_send_status(काष्ठा usbhsg_gpriv *gpriv,
				       अचिन्हित लघु status)
अणु
	काष्ठा usbhsg_uep *dcp = usbhsg_gpriv_to_dcp(gpriv);
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(dcp);
	काष्ठा device *dev = usbhsg_gpriv_to_dev(gpriv);
	काष्ठा usb_request *req;
	__le16 *buf;

	/* alloc new usb_request क्रम recip */
	req = usb_ep_alloc_request(&dcp->ep, GFP_ATOMIC);
	अगर (!req) अणु
		dev_err(dev, "recip request allocation fail\n");
		वापस;
	पूर्ण

	/* alloc recip data buffer */
	buf = kदो_स्मृति(माप(*buf), GFP_ATOMIC);
	अगर (!buf) अणु
		usb_ep_मुक्त_request(&dcp->ep, req);
		वापस;
	पूर्ण

	/* recip data is status */
	*buf = cpu_to_le16(status);

	/* allocated usb_request/buffer will be मुक्तd */
	req->complete	= __usbhsg_recip_send_complete;
	req->buf	= buf;
	req->length	= माप(*buf);
	req->zero	= 0;

	/* push packet */
	pipe->handler = &usbhs_fअगरo_pio_push_handler;
	usbhsg_queue_push(dcp, usbhsg_req_to_ureq(req));
पूर्ण

अटल पूर्णांक usbhsg_recip_handler_std_get_device(काष्ठा usbhs_priv *priv,
					       काष्ठा usbhsg_uep *uep,
					       काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	अचिन्हित लघु status = 0;

	अगर (usbhsg_status_has(gpriv, USBHSG_STATUS_SELF_POWERED))
		status = 1 << USB_DEVICE_SELF_POWERED;

	__usbhsg_recip_send_status(gpriv, status);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsg_recip_handler_std_get_पूर्णांकerface(काष्ठा usbhs_priv *priv,
						  काष्ठा usbhsg_uep *uep,
						  काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	अचिन्हित लघु status = 0;

	__usbhsg_recip_send_status(gpriv, status);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsg_recip_handler_std_get_endpoपूर्णांक(काष्ठा usbhs_priv *priv,
						 काष्ठा usbhsg_uep *uep,
						 काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	अचिन्हित लघु status = 0;

	अगर (usbhs_pipe_is_stall(pipe))
		status = 1 << USB_ENDPOINT_HALT;

	__usbhsg_recip_send_status(gpriv, status);

	वापस 0;
पूर्ण

अटल काष्ठा usbhsg_recip_handle req_get_status = अणु
	.name		= "get status",
	.device		= usbhsg_recip_handler_std_get_device,
	.पूर्णांकerface	= usbhsg_recip_handler_std_get_पूर्णांकerface,
	.endpoपूर्णांक	= usbhsg_recip_handler_std_get_endpoपूर्णांक,
पूर्ण;

/*
 *		USB_TYPE handler
 */
अटल पूर्णांक usbhsg_recip_run_handle(काष्ठा usbhs_priv *priv,
				   काष्ठा usbhsg_recip_handle *handler,
				   काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);
	काष्ठा device *dev = usbhsg_gpriv_to_dev(gpriv);
	काष्ठा usbhsg_uep *uep;
	काष्ठा usbhs_pipe *pipe;
	पूर्णांक recip = ctrl->bRequestType & USB_RECIP_MASK;
	पूर्णांक nth = le16_to_cpu(ctrl->wIndex) & USB_ENDPOINT_NUMBER_MASK;
	पूर्णांक ret = 0;
	पूर्णांक (*func)(काष्ठा usbhs_priv *priv, काष्ठा usbhsg_uep *uep,
		    काष्ठा usb_ctrlrequest *ctrl);
	अक्षर *msg;

	uep = usbhsg_gpriv_to_nth_uep(gpriv, nth);
	pipe = usbhsg_uep_to_pipe(uep);
	अगर (!pipe) अणु
		dev_err(dev, "wrong recip request\n");
		वापस -EINVAL;
	पूर्ण

	चयन (recip) अणु
	हाल USB_RECIP_DEVICE:
		msg	= "DEVICE";
		func	= handler->device;
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		msg	= "INTERFACE";
		func	= handler->पूर्णांकerface;
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		msg	= "ENDPOINT";
		func	= handler->endpoपूर्णांक;
		अवरोध;
	शेष:
		dev_warn(dev, "unsupported RECIP(%d)\n", recip);
		func = शून्य;
		ret = -EINVAL;
	पूर्ण

	अगर (func) अणु
		dev_dbg(dev, "%s (pipe %d :%s)\n", handler->name, nth, msg);
		ret = func(priv, uep, ctrl);
	पूर्ण

	वापस ret;
पूर्ण

/*
 *		irq functions
 *
 * it will be called from usbhs_पूर्णांकerrupt
 */
अटल पूर्णांक usbhsg_irq_dev_state(काष्ठा usbhs_priv *priv,
				काष्ठा usbhs_irq_state *irq_state)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);
	काष्ठा device *dev = usbhsg_gpriv_to_dev(gpriv);
	पूर्णांक state = usbhs_status_get_device_state(irq_state);

	gpriv->gadget.speed = usbhs_bus_get_speed(priv);

	dev_dbg(dev, "state = %x : speed : %d\n", state, gpriv->gadget.speed);

	अगर (gpriv->gadget.speed != USB_SPEED_UNKNOWN &&
	    (state & SUSPENDED_STATE)) अणु
		अगर (gpriv->driver && gpriv->driver->suspend)
			gpriv->driver->suspend(&gpriv->gadget);
		usb_gadget_set_state(&gpriv->gadget, USB_STATE_SUSPENDED);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsg_irq_ctrl_stage(काष्ठा usbhs_priv *priv,
				 काष्ठा usbhs_irq_state *irq_state)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);
	काष्ठा usbhsg_uep *dcp = usbhsg_gpriv_to_dcp(gpriv);
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(dcp);
	काष्ठा device *dev = usbhsg_gpriv_to_dev(gpriv);
	काष्ठा usb_ctrlrequest ctrl;
	काष्ठा usbhsg_recip_handle *recip_handler = शून्य;
	पूर्णांक stage = usbhs_status_get_ctrl_stage(irq_state);
	पूर्णांक ret = 0;

	dev_dbg(dev, "stage = %d\n", stage);

	/*
	 * see Manual
	 *
	 *  "Operation"
	 *  - "Interrupt Function"
	 *    - "Control Transfer Stage Transition Interrupt"
	 *      - Fig. "Control Transfer Stage Transitions"
	 */

	चयन (stage) अणु
	हाल READ_DATA_STAGE:
		pipe->handler = &usbhs_fअगरo_pio_push_handler;
		अवरोध;
	हाल WRITE_DATA_STAGE:
		pipe->handler = &usbhs_fअगरo_pio_pop_handler;
		अवरोध;
	हाल NODATA_STATUS_STAGE:
		pipe->handler = &usbhs_ctrl_stage_end_handler;
		अवरोध;
	हाल READ_STATUS_STAGE:
	हाल WRITE_STATUS_STAGE:
		usbhs_dcp_control_transfer_करोne(pipe);
		fallthrough;
	शेष:
		वापस ret;
	पूर्ण

	/*
	 * get usb request
	 */
	usbhs_usbreq_get_val(priv, &ctrl);

	चयन (ctrl.bRequestType & USB_TYPE_MASK) अणु
	हाल USB_TYPE_STANDARD:
		चयन (ctrl.bRequest) अणु
		हाल USB_REQ_CLEAR_FEATURE:
			recip_handler = &req_clear_feature;
			अवरोध;
		हाल USB_REQ_SET_FEATURE:
			recip_handler = &req_set_feature;
			अवरोध;
		हाल USB_REQ_GET_STATUS:
			recip_handler = &req_get_status;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * setup stage / run recip
	 */
	अगर (recip_handler)
		ret = usbhsg_recip_run_handle(priv, recip_handler, &ctrl);
	अन्यथा
		ret = gpriv->driver->setup(&gpriv->gadget, &ctrl);

	अगर (ret < 0)
		usbhs_pipe_stall(pipe);

	वापस ret;
पूर्ण

/*
 *
 *		usb_dcp_ops
 *
 */
अटल पूर्णांक usbhsg_pipe_disable(काष्ठा usbhsg_uep *uep)
अणु
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	काष्ठा usbhs_pkt *pkt;

	जबतक (1) अणु
		pkt = usbhs_pkt_pop(pipe, शून्य);
		अगर (!pkt)
			अवरोध;

		usbhsg_queue_pop(uep, usbhsg_pkt_to_ureq(pkt), -ESHUTDOWN);
	पूर्ण

	usbhs_pipe_disable(pipe);

	वापस 0;
पूर्ण

/*
 *
 *		usb_ep_ops
 *
 */
अटल पूर्णांक usbhsg_ep_enable(काष्ठा usb_ep *ep,
			 स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा usbhsg_uep *uep   = usbhsg_ep_to_uep(ep);
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	काष्ठा usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	काष्ठा usbhs_pipe *pipe;
	पूर्णांक ret = -EIO;
	अचिन्हित दीर्घ flags;

	usbhs_lock(priv, flags);

	/*
	 * अगर it alपढ़ोy have pipe,
	 * nothing to करो
	 */
	अगर (uep->pipe) अणु
		usbhs_pipe_clear(uep->pipe);
		usbhs_pipe_sequence_data0(uep->pipe);
		ret = 0;
		जाओ usbhsg_ep_enable_end;
	पूर्ण

	pipe = usbhs_pipe_दो_स्मृति(priv,
				 usb_endpoपूर्णांक_type(desc),
				 usb_endpoपूर्णांक_dir_in(desc));
	अगर (pipe) अणु
		uep->pipe		= pipe;
		pipe->mod_निजी	= uep;

		/* set epnum / maxp */
		usbhs_pipe_config_update(pipe, 0,
					 usb_endpoपूर्णांक_num(desc),
					 usb_endpoपूर्णांक_maxp(desc));

		/*
		 * usbhs_fअगरo_dma_push/pop_handler try to
		 * use dmaengine अगर possible.
		 * It will use pio handler अगर impossible.
		 */
		अगर (usb_endpoपूर्णांक_dir_in(desc)) अणु
			pipe->handler = &usbhs_fअगरo_dma_push_handler;
		पूर्ण अन्यथा अणु
			pipe->handler = &usbhs_fअगरo_dma_pop_handler;
			usbhs_xxxsts_clear(priv, BRDYSTS,
					   usbhs_pipe_number(pipe));
		पूर्ण

		ret = 0;
	पूर्ण

usbhsg_ep_enable_end:
	usbhs_unlock(priv, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक usbhsg_ep_disable(काष्ठा usb_ep *ep)
अणु
	काष्ठा usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	काष्ठा usbhs_pipe *pipe;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uep->lock, flags);
	pipe = usbhsg_uep_to_pipe(uep);
	अगर (!pipe)
		जाओ out;

	usbhsg_pipe_disable(uep);
	usbhs_pipe_मुक्त(pipe);

	uep->pipe->mod_निजी	= शून्य;
	uep->pipe		= शून्य;

out:
	spin_unlock_irqrestore(&uep->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा usb_request *usbhsg_ep_alloc_request(काष्ठा usb_ep *ep,
						   gfp_t gfp_flags)
अणु
	काष्ठा usbhsg_request *ureq;

	ureq = kzalloc(माप *ureq, gfp_flags);
	अगर (!ureq)
		वापस शून्य;

	usbhs_pkt_init(usbhsg_ureq_to_pkt(ureq));

	वापस &ureq->req;
पूर्ण

अटल व्योम usbhsg_ep_मुक्त_request(काष्ठा usb_ep *ep,
				   काष्ठा usb_request *req)
अणु
	काष्ठा usbhsg_request *ureq = usbhsg_req_to_ureq(req);

	WARN_ON(!list_empty(&ureq->pkt.node));
	kमुक्त(ureq);
पूर्ण

अटल पूर्णांक usbhsg_ep_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *req,
			  gfp_t gfp_flags)
अणु
	काष्ठा usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	काष्ठा usbhsg_request *ureq = usbhsg_req_to_ureq(req);
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);

	/* param check */
	अगर (usbhsg_is_not_connected(gpriv)	||
	    unlikely(!gpriv->driver)		||
	    unlikely(!pipe))
		वापस -ESHUTDOWN;

	usbhsg_queue_push(uep, ureq);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsg_ep_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	काष्ठा usbhsg_request *ureq = usbhsg_req_to_ureq(req);
	काष्ठा usbhs_pipe *pipe;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uep->lock, flags);
	pipe = usbhsg_uep_to_pipe(uep);
	अगर (pipe)
		usbhs_pkt_pop(pipe, usbhsg_ureq_to_pkt(ureq));

	/*
	 * To dequeue a request, this driver should call the usbhsg_queue_pop()
	 * even अगर the pipe is शून्य.
	 */
	usbhsg_queue_pop(uep, ureq, -ECONNRESET);
	spin_unlock_irqrestore(&uep->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __usbhsg_ep_set_halt_wedge(काष्ठा usb_ep *ep, पूर्णांक halt, पूर्णांक wedge)
अणु
	काष्ठा usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	काष्ठा usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	काष्ठा usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	काष्ठा device *dev = usbhsg_gpriv_to_dev(gpriv);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	dev_dbg(dev, "set halt %d (pipe %d)\n",
		halt, usbhs_pipe_number(pipe));

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	/*
	 * According to usb_ep_set_halt()'s description, this function should
	 * वापस -EAGAIN अगर the IN endpoपूर्णांक has any queue or data. Note
	 * that the usbhs_pipe_is_dir_in() वापसs false अगर the pipe is an
	 * IN endpoपूर्णांक in the gadget mode.
	 */
	अगर (!usbhs_pipe_is_dir_in(pipe) && (__usbhsf_pkt_get(pipe) ||
	    usbhs_pipe_contains_transmittable_data(pipe))) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (halt)
		usbhs_pipe_stall(pipe);
	अन्यथा
		usbhs_pipe_disable(pipe);

	अगर (halt && wedge)
		usbhsg_status_set(gpriv, USBHSG_STATUS_WEDGE);
	अन्यथा
		usbhsg_status_clr(gpriv, USBHSG_STATUS_WEDGE);

out:
	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	वापस ret;
पूर्ण

अटल पूर्णांक usbhsg_ep_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	वापस __usbhsg_ep_set_halt_wedge(ep, value, 0);
पूर्ण

अटल पूर्णांक usbhsg_ep_set_wedge(काष्ठा usb_ep *ep)
अणु
	वापस __usbhsg_ep_set_halt_wedge(ep, 1, 1);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops usbhsg_ep_ops = अणु
	.enable		= usbhsg_ep_enable,
	.disable	= usbhsg_ep_disable,

	.alloc_request	= usbhsg_ep_alloc_request,
	.मुक्त_request	= usbhsg_ep_मुक्त_request,

	.queue		= usbhsg_ep_queue,
	.dequeue	= usbhsg_ep_dequeue,

	.set_halt	= usbhsg_ep_set_halt,
	.set_wedge	= usbhsg_ep_set_wedge,
पूर्ण;

/*
 *		pullup control
 */
अटल पूर्णांक usbhsg_can_pullup(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);

	वापस gpriv->driver &&
	       usbhsg_status_has(gpriv, USBHSG_STATUS_SOFT_CONNECT);
पूर्ण

अटल व्योम usbhsg_update_pullup(काष्ठा usbhs_priv *priv)
अणु
	अगर (usbhsg_can_pullup(priv))
		usbhs_sys_function_pullup(priv, 1);
	अन्यथा
		usbhs_sys_function_pullup(priv, 0);
पूर्ण

/*
 *		usb module start/end
 */
अटल पूर्णांक usbhsg_try_start(काष्ठा usbhs_priv *priv, u32 status)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);
	काष्ठा usbhsg_uep *dcp = usbhsg_gpriv_to_dcp(gpriv);
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	usbhsg_status_set(gpriv, status);
	अगर (!(usbhsg_status_has(gpriv, USBHSG_STATUS_STARTED) &&
	      usbhsg_status_has(gpriv, USBHSG_STATUS_REGISTERD)))
		ret = -1; /* not पढ़ोy */

	usbhs_unlock(priv, flags);
	/********************  spin unlock ********************/

	अगर (ret < 0)
		वापस 0; /* not पढ़ोy is not error */

	/*
	 * enable पूर्णांकerrupt and प्रणालीs अगर पढ़ोy
	 */
	dev_dbg(dev, "start gadget\n");

	/*
	 * pipe initialize and enable DCP
	 */
	usbhs_fअगरo_init(priv);
	usbhs_pipe_init(priv,
			usbhsg_dma_map_ctrl);

	/* dcp init instead of usbhsg_ep_enable() */
	dcp->pipe		= usbhs_dcp_दो_स्मृति(priv);
	dcp->pipe->mod_निजी	= dcp;
	usbhs_pipe_config_update(dcp->pipe, 0, 0, 64);

	/*
	 * प्रणाली config enble
	 * - HI speed
	 * - function
	 * - usb module
	 */
	usbhs_sys_function_ctrl(priv, 1);
	usbhsg_update_pullup(priv);

	/*
	 * enable irq callback
	 */
	mod->irq_dev_state	= usbhsg_irq_dev_state;
	mod->irq_ctrl_stage	= usbhsg_irq_ctrl_stage;
	usbhs_irq_callback_update(priv, mod);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsg_try_stop(काष्ठा usbhs_priv *priv, u32 status)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);
	काष्ठा usbhsg_uep *uep;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0, i;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	usbhsg_status_clr(gpriv, status);
	अगर (!usbhsg_status_has(gpriv, USBHSG_STATUS_STARTED) &&
	    !usbhsg_status_has(gpriv, USBHSG_STATUS_REGISTERD))
		ret = -1; /* alपढ़ोy करोne */

	usbhs_unlock(priv, flags);
	/********************  spin unlock ********************/

	अगर (ret < 0)
		वापस 0; /* alपढ़ोy करोne is not error */

	/*
	 * disable पूर्णांकerrupt and प्रणालीs अगर 1st try
	 */
	usbhs_fअगरo_quit(priv);

	/* disable all irq */
	mod->irq_dev_state	= शून्य;
	mod->irq_ctrl_stage	= शून्य;
	usbhs_irq_callback_update(priv, mod);

	gpriv->gadget.speed = USB_SPEED_UNKNOWN;

	/* disable sys */
	usbhs_sys_set_test_mode(priv, 0);
	usbhs_sys_function_ctrl(priv, 0);

	/* disable all eps */
	usbhsg_क्रम_each_uep_with_dcp(uep, gpriv, i)
		usbhsg_ep_disable(&uep->ep);

	dev_dbg(dev, "stop gadget\n");

	वापस 0;
पूर्ण

/*
 * VBUS provided by the PHY
 */
अटल पूर्णांक usbhsm_phy_get_vbus(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);

	वापस  gpriv->vbus_active;
पूर्ण

अटल व्योम usbhs_mod_phy_mode(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_mod_info *info = &priv->mod_info;

	info->irq_vbus = शून्य;
	info->get_vbus = usbhsm_phy_get_vbus;

	usbhs_irq_callback_update(priv, शून्य);
पूर्ण

/*
 *
 *		linux usb function
 *
 */
अटल पूर्णांक usbhsg_gadget_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	काष्ठा usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक ret;

	अगर (!driver		||
	    !driver->setup	||
	    driver->max_speed < USB_SPEED_FULL)
		वापस -EINVAL;

	/* connect to bus through transceiver */
	अगर (!IS_ERR_OR_शून्य(gpriv->transceiver)) अणु
		ret = otg_set_peripheral(gpriv->transceiver->otg,
					&gpriv->gadget);
		अगर (ret) अणु
			dev_err(dev, "%s: can't bind to transceiver\n",
				gpriv->gadget.name);
			वापस ret;
		पूर्ण

		/* get vbus using phy versions */
		usbhs_mod_phy_mode(priv);
	पूर्ण

	/* first hook up the driver ... */
	gpriv->driver = driver;

	वापस usbhsg_try_start(priv, USBHSG_STATUS_REGISTERD);
पूर्ण

अटल पूर्णांक usbhsg_gadget_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	काष्ठा usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);

	usbhsg_try_stop(priv, USBHSG_STATUS_REGISTERD);

	अगर (!IS_ERR_OR_शून्य(gpriv->transceiver))
		otg_set_peripheral(gpriv->transceiver->otg, शून्य);

	gpriv->driver = शून्य;

	वापस 0;
पूर्ण

/*
 *		usb gadget ops
 */
अटल पूर्णांक usbhsg_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	काष्ठा usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);

	वापस usbhs_frame_get_num(priv);
पूर्ण

अटल पूर्णांक usbhsg_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	काष्ठा usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	अचिन्हित दीर्घ flags;

	usbhs_lock(priv, flags);
	अगर (is_on)
		usbhsg_status_set(gpriv, USBHSG_STATUS_SOFT_CONNECT);
	अन्यथा
		usbhsg_status_clr(gpriv, USBHSG_STATUS_SOFT_CONNECT);
	usbhsg_update_pullup(priv);
	usbhs_unlock(priv, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsg_set_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक is_self)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);

	अगर (is_self)
		usbhsg_status_set(gpriv, USBHSG_STATUS_SELF_POWERED);
	अन्यथा
		usbhsg_status_clr(gpriv, USBHSG_STATUS_SELF_POWERED);

	gadget->is_selfघातered = (is_self != 0);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsg_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	काष्ठा usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	काष्ठा platक्रमm_device *pdev = usbhs_priv_to_pdev(priv);

	gpriv->vbus_active = !!is_active;

	usbhsc_schedule_notअगरy_hotplug(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops usbhsg_gadget_ops = अणु
	.get_frame		= usbhsg_get_frame,
	.set_selfघातered	= usbhsg_set_selfघातered,
	.udc_start		= usbhsg_gadget_start,
	.udc_stop		= usbhsg_gadget_stop,
	.pullup			= usbhsg_pullup,
	.vbus_session		= usbhsg_vbus_session,
पूर्ण;

अटल पूर्णांक usbhsg_start(काष्ठा usbhs_priv *priv)
अणु
	वापस usbhsg_try_start(priv, USBHSG_STATUS_STARTED);
पूर्ण

अटल पूर्णांक usbhsg_stop(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);

	/* cable disconnect */
	अगर (gpriv->driver &&
	    gpriv->driver->disconnect)
		gpriv->driver->disconnect(&gpriv->gadget);

	वापस usbhsg_try_stop(priv, USBHSG_STATUS_STARTED);
पूर्ण

पूर्णांक usbhs_mod_gadget_probe(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhsg_gpriv *gpriv;
	काष्ठा usbhsg_uep *uep;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	काष्ठा renesas_usbhs_driver_pipe_config *pipe_configs =
					usbhs_get_dparam(priv, pipe_configs);
	पूर्णांक pipe_size = usbhs_get_dparam(priv, pipe_size);
	पूर्णांक i;
	पूर्णांक ret;

	gpriv = kzalloc(माप(काष्ठा usbhsg_gpriv), GFP_KERNEL);
	अगर (!gpriv)
		वापस -ENOMEM;

	uep = kसुस्मृति(pipe_size, माप(काष्ठा usbhsg_uep), GFP_KERNEL);
	अगर (!uep) अणु
		ret = -ENOMEM;
		जाओ usbhs_mod_gadget_probe_err_gpriv;
	पूर्ण

	gpriv->transceiver = usb_get_phy(USB_PHY_TYPE_UNDEFINED);
	dev_info(dev, "%stransceiver found\n",
		 !IS_ERR(gpriv->transceiver) ? "" : "no ");

	/*
	 * CAUTION
	 *
	 * There is no guarantee that it is possible to access usb module here.
	 * Don't accesses to it.
	 * The accesse will be enable after "usbhsg_start"
	 */

	/*
	 * रेजिस्टर itself
	 */
	usbhs_mod_रेजिस्टर(priv, &gpriv->mod, USBHS_GADGET);

	/* init gpriv */
	gpriv->mod.name		= "gadget";
	gpriv->mod.start	= usbhsg_start;
	gpriv->mod.stop		= usbhsg_stop;
	gpriv->uep		= uep;
	gpriv->uep_size		= pipe_size;
	usbhsg_status_init(gpriv);

	/*
	 * init gadget
	 */
	gpriv->gadget.dev.parent	= dev;
	gpriv->gadget.name		= "renesas_usbhs_udc";
	gpriv->gadget.ops		= &usbhsg_gadget_ops;
	gpriv->gadget.max_speed		= USB_SPEED_HIGH;
	gpriv->gadget.quirk_aव्योमs_skb_reserve = usbhs_get_dparam(priv,
								has_usb_dmac);

	INIT_LIST_HEAD(&gpriv->gadget.ep_list);

	/*
	 * init usb_ep
	 */
	usbhsg_क्रम_each_uep_with_dcp(uep, gpriv, i) अणु
		uep->gpriv	= gpriv;
		uep->pipe	= शून्य;
		snम_लिखो(uep->ep_name, EP_NAME_SIZE, "ep%d", i);

		uep->ep.name		= uep->ep_name;
		uep->ep.ops		= &usbhsg_ep_ops;
		INIT_LIST_HEAD(&uep->ep.ep_list);
		spin_lock_init(&uep->lock);

		/* init DCP */
		अगर (usbhsg_is_dcp(uep)) अणु
			gpriv->gadget.ep0 = &uep->ep;
			usb_ep_set_maxpacket_limit(&uep->ep, 64);
			uep->ep.caps.type_control = true;
		पूर्ण अन्यथा अणु
			/* init normal pipe */
			अगर (pipe_configs[i].type == USB_ENDPOINT_XFER_ISOC)
				uep->ep.caps.type_iso = true;
			अगर (pipe_configs[i].type == USB_ENDPOINT_XFER_BULK)
				uep->ep.caps.type_bulk = true;
			अगर (pipe_configs[i].type == USB_ENDPOINT_XFER_INT)
				uep->ep.caps.type_पूर्णांक = true;
			usb_ep_set_maxpacket_limit(&uep->ep,
						   pipe_configs[i].bufsize);
			list_add_tail(&uep->ep.ep_list, &gpriv->gadget.ep_list);
		पूर्ण
		uep->ep.caps.dir_in = true;
		uep->ep.caps.dir_out = true;
	पूर्ण

	ret = usb_add_gadget_udc(dev, &gpriv->gadget);
	अगर (ret)
		जाओ err_add_udc;


	dev_info(dev, "gadget probed\n");

	वापस 0;

err_add_udc:
	kमुक्त(gpriv->uep);

usbhs_mod_gadget_probe_err_gpriv:
	kमुक्त(gpriv);

	वापस ret;
पूर्ण

व्योम usbhs_mod_gadget_हटाओ(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);

	usb_del_gadget_udc(&gpriv->gadget);

	kमुक्त(gpriv->uep);
	kमुक्त(gpriv);
पूर्ण
