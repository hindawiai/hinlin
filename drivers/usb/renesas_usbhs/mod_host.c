<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश "common.h"

/*
 *** HARDWARE LIMITATION ***
 *
 * 1) renesas_usbhs has a limited number of controllable devices.
 *    it can control only 9 devices in generally.
 *	see DEVADDn / DCPMAXP / PIPEMAXP.
 *
 * 2) renesas_usbhs pipe number is limited.
 *    the pipe will be re-used क्रम each devices.
 *    so, software should control DATA0/1 sequence of each devices.
 */


/*
 *		image of mod_host
 *
 * +--------+
 * | udev 0 | --> it is used when set address
 * +--------+
 *
 * +--------+					pipes are reused क्रम each uep.
 * | udev 1 |-+- [uep 0 (dcp) ] --+		pipe will be चयनed when
 * +--------+ |			  |		other device requested
 *	      +- [uep 1 (bulk)]	--|---+		   +--------------+
 *	      |			  +--------------> | pipe0 (dcp)  |
 *	      +- [uep 2 (bulk)]	-@    |		   +--------------+
 *				      |		   | pipe1 (isoc) |
 * +--------+			      |		   +--------------+
 * | udev 2 |-+- [uep 0 (dcp) ]	-@    +----------> | pipe2 (bulk) |
 * +--------+ |					   +--------------+
 *	      +- [uep 1 (पूर्णांक) ]	----+	  +------> | pipe3 (bulk) |
 *				    |	  |	   +--------------+
 * +--------+			    +-----|------> | pipe4 (पूर्णांक)  |
 * | udev 3 |-+- [uep 0 (dcp) ]	-@	  |	   +--------------+
 * +--------+ |				  |	   | ....	  |
 *	      +- [uep 1 (bulk)]	-@	  |	   | ....	  |
 *	      |				  |
 *	      +- [uep 2 (bulk)]-----------+
 *
 * @ :	uep requested मुक्त pipe, but all have been used.
 *	now it is रुकोing क्रम मुक्त pipe
 */


/*
 *		काष्ठा
 */
काष्ठा usbhsh_request अणु
	काष्ठा urb		*urb;
	काष्ठा usbhs_pkt	pkt;
पूर्ण;

काष्ठा usbhsh_device अणु
	काष्ठा usb_device	*usbv;
	काष्ठा list_head	ep_list_head; /* list of usbhsh_ep */
पूर्ण;

काष्ठा usbhsh_ep अणु
	काष्ठा usbhs_pipe	*pipe;   /* attached pipe */
	काष्ठा usbhsh_device	*udev;   /* attached udev */
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा list_head	ep_list; /* list to usbhsh_device */
	अचिन्हित पूर्णांक		counter; /* pipe attach counter */
पूर्ण;

#घोषणा USBHSH_DEVICE_MAX	10 /* see DEVADDn / DCPMAXP / PIPEMAXP */
#घोषणा USBHSH_PORT_MAX		 7 /* see DEVADDn :: HUBPORT */
काष्ठा usbhsh_hpriv अणु
	काष्ठा usbhs_mod	mod;
	काष्ठा usbhs_pipe	*dcp;

	काष्ठा usbhsh_device	udev[USBHSH_DEVICE_MAX];

	u32	port_stat;	/* USB_PORT_STAT_xxx */

	काष्ठा completion	setup_ack_करोne;
पूर्ण;


अटल स्थिर अक्षर usbhsh_hcd_name[] = "renesas_usbhs host";

/*
 *		macro
 */
#घोषणा usbhsh_priv_to_hpriv(priv) \
	container_of(usbhs_mod_get(priv, USBHS_HOST), काष्ठा usbhsh_hpriv, mod)

#घोषणा __usbhsh_क्रम_each_udev(start, pos, h, i)	\
	क्रम ((i) = start;						\
	     ((i) < USBHSH_DEVICE_MAX) && ((pos) = (h)->udev + (i));	\
	     (i)++)

#घोषणा usbhsh_क्रम_each_udev(pos, hpriv, i)	\
	__usbhsh_क्रम_each_udev(1, pos, hpriv, i)

#घोषणा usbhsh_क्रम_each_udev_with_dev0(pos, hpriv, i)	\
	__usbhsh_क्रम_each_udev(0, pos, hpriv, i)

#घोषणा usbhsh_hcd_to_hpriv(h)	(काष्ठा usbhsh_hpriv *)((h)->hcd_priv)
#घोषणा usbhsh_hcd_to_dev(h)	((h)->self.controller)

#घोषणा usbhsh_hpriv_to_priv(h)	((h)->mod.priv)
#घोषणा usbhsh_hpriv_to_dcp(h)	((h)->dcp)
#घोषणा usbhsh_hpriv_to_hcd(h)	\
	container_of((व्योम *)h, काष्ठा usb_hcd, hcd_priv)

#घोषणा usbhsh_ep_to_uep(u)	((u)->hcpriv)
#घोषणा usbhsh_uep_to_pipe(u)	((u)->pipe)
#घोषणा usbhsh_uep_to_udev(u)	((u)->udev)
#घोषणा usbhsh_uep_to_ep(u)	((u)->ep)

#घोषणा usbhsh_urb_to_ureq(u)	((u)->hcpriv)
#घोषणा usbhsh_urb_to_usbv(u)	((u)->dev)

#घोषणा usbhsh_usbv_to_udev(d)	dev_get_drvdata(&(d)->dev)

#घोषणा usbhsh_udev_to_usbv(h)	((h)->usbv)
#घोषणा usbhsh_udev_is_used(h)	usbhsh_udev_to_usbv(h)

#घोषणा usbhsh_pipe_to_uep(p)	((p)->mod_निजी)

#घोषणा usbhsh_device_parent(d)		(usbhsh_usbv_to_udev((d)->usbv->parent))
#घोषणा usbhsh_device_hubport(d)	((d)->usbv->portnum)
#घोषणा usbhsh_device_number(h, d)	((पूर्णांक)((d) - (h)->udev))
#घोषणा usbhsh_device_nth(h, d)		((h)->udev + d)
#घोषणा usbhsh_device0(h)		usbhsh_device_nth(h, 0)

#घोषणा usbhsh_port_stat_init(h)	((h)->port_stat = 0)
#घोषणा usbhsh_port_stat_set(h, s)	((h)->port_stat |= (s))
#घोषणा usbhsh_port_stat_clear(h, s)	((h)->port_stat &= ~(s))
#घोषणा usbhsh_port_stat_get(h)		((h)->port_stat)

#घोषणा usbhsh_pkt_to_ureq(p)	\
	container_of((व्योम *)p, काष्ठा usbhsh_request, pkt)

/*
 *		req alloc/मुक्त
 */
अटल काष्ठा usbhsh_request *usbhsh_ureq_alloc(काष्ठा usbhsh_hpriv *hpriv,
					       काष्ठा urb *urb,
					       gfp_t mem_flags)
अणु
	काष्ठा usbhsh_request *ureq;

	ureq = kzalloc(माप(काष्ठा usbhsh_request), mem_flags);
	अगर (!ureq)
		वापस शून्य;

	usbhs_pkt_init(&ureq->pkt);
	ureq->urb = urb;
	usbhsh_urb_to_ureq(urb) = ureq;

	वापस ureq;
पूर्ण

अटल व्योम usbhsh_ureq_मुक्त(काष्ठा usbhsh_hpriv *hpriv,
			    काष्ठा usbhsh_request *ureq)
अणु
	usbhsh_urb_to_ureq(ureq->urb) = शून्य;
	ureq->urb = शून्य;

	kमुक्त(ureq);
पूर्ण

/*
 *		status
 */
अटल पूर्णांक usbhsh_is_running(काष्ठा usbhsh_hpriv *hpriv)
अणु
	/*
	 * we can decide some device is attached or not
	 * by checking mod.irq_attch
	 * see
	 *	usbhsh_irq_attch()
	 *	usbhsh_irq_dtch()
	 */
	वापस (hpriv->mod.irq_attch == शून्य);
पूर्ण

/*
 *		pipe control
 */
अटल व्योम usbhsh_endpoपूर्णांक_sequence_save(काष्ठा usbhsh_hpriv *hpriv,
					  काष्ठा urb *urb,
					  काष्ठा usbhs_pkt *pkt)
अणु
	पूर्णांक len = urb->actual_length;
	पूर्णांक maxp = usb_endpoपूर्णांक_maxp(&urb->ep->desc);
	पूर्णांक t = 0;

	/* DCP is out of sequence control */
	अगर (usb_pipecontrol(urb->pipe))
		वापस;

	/*
	 * renesas_usbhs pipe has a limitation in a number.
	 * So, driver should re-use the limited pipe क्रम each device/endpoपूर्णांक.
	 * DATA0/1 sequence should be saved क्रम it.
	 * see [image of mod_host]
	 *     [HARDWARE LIMITATION]
	 */

	/*
	 * next sequence depends on actual_length
	 *
	 * ex) actual_length = 1147, maxp = 512
	 * data0 : 512
	 * data1 : 512
	 * data0 : 123
	 * data1 is the next sequence
	 */
	t = len / maxp;
	अगर (len % maxp)
		t++;
	अगर (pkt->zero)
		t++;
	t %= 2;

	अगर (t)
		usb_करोtoggle(urb->dev,
			     usb_pipeendpoपूर्णांक(urb->pipe),
			     usb_pipeout(urb->pipe));
पूर्ण

अटल काष्ठा usbhsh_device *usbhsh_device_get(काष्ठा usbhsh_hpriv *hpriv,
					       काष्ठा urb *urb);

अटल पूर्णांक usbhsh_pipe_attach(काष्ठा usbhsh_hpriv *hpriv,
			      काष्ठा urb *urb)
अणु
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा usbhsh_ep *uep = usbhsh_ep_to_uep(urb->ep);
	काष्ठा usbhsh_device *udev = usbhsh_device_get(hpriv, urb);
	काष्ठा usbhs_pipe *pipe;
	काष्ठा usb_endpoपूर्णांक_descriptor *desc = &urb->ep->desc;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	अचिन्हित दीर्घ flags;
	पूर्णांक dir_in_req = !!usb_pipein(urb->pipe);
	पूर्णांक is_dcp = usb_endpoपूर्णांक_xfer_control(desc);
	पूर्णांक i, dir_in;
	पूर्णांक ret = -EBUSY;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	/*
	 * अगर uep has been attached to pipe,
	 * reuse it
	 */
	अगर (usbhsh_uep_to_pipe(uep)) अणु
		ret = 0;
		जाओ usbhsh_pipe_attach_करोne;
	पूर्ण

	usbhs_क्रम_each_pipe_with_dcp(pipe, priv, i) अणु

		/* check pipe type */
		अगर (!usbhs_pipe_type_is(pipe, usb_endpoपूर्णांक_type(desc)))
			जारी;

		/* check pipe direction अगर normal pipe */
		अगर (!is_dcp) अणु
			dir_in = !!usbhs_pipe_is_dir_in(pipe);
			अगर (0 != (dir_in - dir_in_req))
				जारी;
		पूर्ण

		/* check pipe is मुक्त */
		अगर (usbhsh_pipe_to_uep(pipe))
			जारी;

		/*
		 * attach pipe to uep
		 *
		 * usbhs_pipe_config_update() should be called after
		 * usbhs_set_device_config()
		 * see
		 *  DCPMAXP/PIPEMAXP
		 */
		usbhsh_uep_to_pipe(uep)		= pipe;
		usbhsh_pipe_to_uep(pipe)	= uep;

		usbhs_pipe_config_update(pipe,
					 usbhsh_device_number(hpriv, udev),
					 usb_endpoपूर्णांक_num(desc),
					 usb_endpoपूर्णांक_maxp(desc));

		dev_dbg(dev, "%s [%d-%d(%s:%s)]\n", __func__,
			usbhsh_device_number(hpriv, udev),
			usb_endpoपूर्णांक_num(desc),
			usbhs_pipe_name(pipe),
			dir_in_req ? "in" : "out");

		ret = 0;
		अवरोध;
	पूर्ण

usbhsh_pipe_attach_करोne:
	अगर (0 == ret)
		uep->counter++;

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	वापस ret;
पूर्ण

अटल व्योम usbhsh_pipe_detach(काष्ठा usbhsh_hpriv *hpriv,
			       काष्ठा usbhsh_ep *uep)
अणु
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा usbhs_pipe *pipe;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!uep)) अणु
		dev_err(dev, "no uep\n");
		वापस;
	पूर्ण

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	pipe = usbhsh_uep_to_pipe(uep);

	अगर (unlikely(!pipe)) अणु
		dev_err(dev, "uep doesn't have pipe\n");
	पूर्ण अन्यथा अगर (1 == uep->counter--) अणु /* last user */
		काष्ठा usb_host_endpoपूर्णांक *ep = usbhsh_uep_to_ep(uep);
		काष्ठा usbhsh_device *udev = usbhsh_uep_to_udev(uep);

		/* detach pipe from uep */
		usbhsh_uep_to_pipe(uep)		= शून्य;
		usbhsh_pipe_to_uep(pipe)	= शून्य;

		dev_dbg(dev, "%s [%d-%d(%s)]\n", __func__,
			usbhsh_device_number(hpriv, udev),
			usb_endpoपूर्णांक_num(&ep->desc),
			usbhs_pipe_name(pipe));
	पूर्ण

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/
पूर्ण

/*
 *		endpoपूर्णांक control
 */
अटल पूर्णांक usbhsh_endpoपूर्णांक_attach(काष्ठा usbhsh_hpriv *hpriv,
				  काष्ठा urb *urb,
				  gfp_t mem_flags)
अणु
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा usbhsh_device *udev = usbhsh_device_get(hpriv, urb);
	काष्ठा usb_host_endpoपूर्णांक *ep = urb->ep;
	काष्ठा usbhsh_ep *uep;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	काष्ठा usb_endpoपूर्णांक_descriptor *desc = &ep->desc;
	अचिन्हित दीर्घ flags;

	uep = kzalloc(माप(काष्ठा usbhsh_ep), mem_flags);
	अगर (!uep)
		वापस -ENOMEM;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	/*
	 * init endpoपूर्णांक
	 */
	uep->counter = 0;
	INIT_LIST_HEAD(&uep->ep_list);
	list_add_tail(&uep->ep_list, &udev->ep_list_head);

	usbhsh_uep_to_udev(uep)	= udev;
	usbhsh_uep_to_ep(uep)	= ep;
	usbhsh_ep_to_uep(ep)	= uep;

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	dev_dbg(dev, "%s [%d-%d]\n", __func__,
		usbhsh_device_number(hpriv, udev),
		usb_endpoपूर्णांक_num(desc));

	वापस 0;
पूर्ण

अटल व्योम usbhsh_endpoपूर्णांक_detach(काष्ठा usbhsh_hpriv *hpriv,
				   काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	काष्ठा usbhsh_ep *uep = usbhsh_ep_to_uep(ep);
	अचिन्हित दीर्घ flags;

	अगर (!uep)
		वापस;

	dev_dbg(dev, "%s [%d-%d]\n", __func__,
		usbhsh_device_number(hpriv, usbhsh_uep_to_udev(uep)),
		usb_endpoपूर्णांक_num(&ep->desc));

	अगर (usbhsh_uep_to_pipe(uep))
		usbhsh_pipe_detach(hpriv, uep);

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	/* हटाओ this endpoपूर्णांक from udev */
	list_del_init(&uep->ep_list);

	usbhsh_uep_to_udev(uep)	= शून्य;
	usbhsh_uep_to_ep(uep)	= शून्य;
	usbhsh_ep_to_uep(ep)	= शून्य;

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	kमुक्त(uep);
पूर्ण

अटल व्योम usbhsh_endpoपूर्णांक_detach_all(काष्ठा usbhsh_hpriv *hpriv,
				       काष्ठा usbhsh_device *udev)
अणु
	काष्ठा usbhsh_ep *uep, *next;

	list_क्रम_each_entry_safe(uep, next, &udev->ep_list_head, ep_list)
		usbhsh_endpoपूर्णांक_detach(hpriv, usbhsh_uep_to_ep(uep));
पूर्ण

/*
 *		device control
 */
अटल पूर्णांक usbhsh_connected_to_rhdev(काष्ठा usb_hcd *hcd,
				     काष्ठा usbhsh_device *udev)
अणु
	काष्ठा usb_device *usbv = usbhsh_udev_to_usbv(udev);

	वापस hcd->self.root_hub == usbv->parent;
पूर्ण

अटल पूर्णांक usbhsh_device_has_endpoपूर्णांक(काष्ठा usbhsh_device *udev)
अणु
	वापस !list_empty(&udev->ep_list_head);
पूर्ण

अटल काष्ठा usbhsh_device *usbhsh_device_get(काष्ठा usbhsh_hpriv *hpriv,
					       काष्ठा urb *urb)
अणु
	काष्ठा usb_device *usbv = usbhsh_urb_to_usbv(urb);
	काष्ठा usbhsh_device *udev = usbhsh_usbv_to_udev(usbv);

	/* usbhsh_device_attach() is still not called */
	अगर (!udev)
		वापस शून्य;

	/* अगर it is device0, वापस it */
	अगर (0 == usb_pipedevice(urb->pipe))
		वापस usbhsh_device0(hpriv);

	/* वापस attached device */
	वापस udev;
पूर्ण

अटल काष्ठा usbhsh_device *usbhsh_device_attach(काष्ठा usbhsh_hpriv *hpriv,
						 काष्ठा urb *urb)
अणु
	काष्ठा usbhsh_device *udev = शून्य;
	काष्ठा usbhsh_device *udev0 = usbhsh_device0(hpriv);
	काष्ठा usbhsh_device *pos;
	काष्ठा usb_hcd *hcd = usbhsh_hpriv_to_hcd(hpriv);
	काष्ठा device *dev = usbhsh_hcd_to_dev(hcd);
	काष्ठा usb_device *usbv = usbhsh_urb_to_usbv(urb);
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	अचिन्हित दीर्घ flags;
	u16 upphub, hubport;
	पूर्णांक i;

	/*
	 * This function should be called only जबतक urb is poपूर्णांकing to device0.
	 * It will attach unused usbhsh_device to urb (usbv),
	 * and initialize device0.
	 * You can use usbhsh_device_get() to get "current" udev,
	 * and usbhsh_usbv_to_udev() is क्रम "attached" udev.
	 */
	अगर (0 != usb_pipedevice(urb->pipe)) अणु
		dev_err(dev, "%s fail: urb isn't pointing device0\n", __func__);
		वापस शून्य;
	पूर्ण

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	/*
	 * find unused device
	 */
	usbhsh_क्रम_each_udev(pos, hpriv, i) अणु
		अगर (usbhsh_udev_is_used(pos))
			जारी;
		udev = pos;
		अवरोध;
	पूर्ण

	अगर (udev) अणु
		/*
		 * usbhsh_usbv_to_udev()
		 * usbhsh_udev_to_usbv()
		 * will be enable
		 */
		dev_set_drvdata(&usbv->dev, udev);
		udev->usbv = usbv;
	पूर्ण

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	अगर (!udev) अणु
		dev_err(dev, "no free usbhsh_device\n");
		वापस शून्य;
	पूर्ण

	अगर (usbhsh_device_has_endpoपूर्णांक(udev)) अणु
		dev_warn(dev, "udev have old endpoint\n");
		usbhsh_endpoपूर्णांक_detach_all(hpriv, udev);
	पूर्ण

	अगर (usbhsh_device_has_endpoपूर्णांक(udev0)) अणु
		dev_warn(dev, "udev0 have old endpoint\n");
		usbhsh_endpoपूर्णांक_detach_all(hpriv, udev0);
	पूर्ण

	/* uep will be attached */
	INIT_LIST_HEAD(&udev0->ep_list_head);
	INIT_LIST_HEAD(&udev->ep_list_head);

	/*
	 * set device0 config
	 */
	usbhs_set_device_config(priv,
				0, 0, 0, usbv->speed);

	/*
	 * set new device config
	 */
	upphub	= 0;
	hubport	= 0;
	अगर (!usbhsh_connected_to_rhdev(hcd, udev)) अणु
		/* अगर udev is not connected to rhdev, it means parent is Hub */
		काष्ठा usbhsh_device *parent = usbhsh_device_parent(udev);

		upphub	= usbhsh_device_number(hpriv, parent);
		hubport	= usbhsh_device_hubport(udev);

		dev_dbg(dev, "%s connected to Hub [%d:%d](%p)\n", __func__,
			upphub, hubport, parent);
	पूर्ण

	usbhs_set_device_config(priv,
			       usbhsh_device_number(hpriv, udev),
			       upphub, hubport, usbv->speed);

	dev_dbg(dev, "%s [%d](%p)\n", __func__,
		usbhsh_device_number(hpriv, udev), udev);

	वापस udev;
पूर्ण

अटल व्योम usbhsh_device_detach(काष्ठा usbhsh_hpriv *hpriv,
			       काष्ठा usbhsh_device *udev)
अणु
	काष्ठा usb_hcd *hcd = usbhsh_hpriv_to_hcd(hpriv);
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा device *dev = usbhsh_hcd_to_dev(hcd);
	काष्ठा usb_device *usbv = usbhsh_udev_to_usbv(udev);
	अचिन्हित दीर्घ flags;

	dev_dbg(dev, "%s [%d](%p)\n", __func__,
		usbhsh_device_number(hpriv, udev), udev);

	अगर (usbhsh_device_has_endpoपूर्णांक(udev)) अणु
		dev_warn(dev, "udev still have endpoint\n");
		usbhsh_endpoपूर्णांक_detach_all(hpriv, udev);
	पूर्ण

	/*
	 * There is nothing to करो अगर it is device0.
	 * see
	 *  usbhsh_device_attach()
	 *  usbhsh_device_get()
	 */
	अगर (0 == usbhsh_device_number(hpriv, udev))
		वापस;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	/*
	 * usbhsh_usbv_to_udev()
	 * usbhsh_udev_to_usbv()
	 * will be disable
	 */
	dev_set_drvdata(&usbv->dev, शून्य);
	udev->usbv = शून्य;

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/
पूर्ण

/*
 *		queue push/pop
 */
अटल व्योम usbhsh_queue_करोne(काष्ठा usbhs_priv *priv, काष्ठा usbhs_pkt *pkt)
अणु
	काष्ठा usbhsh_request *ureq = usbhsh_pkt_to_ureq(pkt);
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	काष्ठा usb_hcd *hcd = usbhsh_hpriv_to_hcd(hpriv);
	काष्ठा urb *urb = ureq->urb;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक status = 0;

	dev_dbg(dev, "%s\n", __func__);

	अगर (!urb) अणु
		dev_warn(dev, "pkt doesn't have urb\n");
		वापस;
	पूर्ण

	अगर (!usbhsh_is_running(hpriv))
		status = -ESHUTDOWN;

	urb->actual_length = pkt->actual;

	usbhsh_endpoपूर्णांक_sequence_save(hpriv, urb, pkt);
	usbhsh_ureq_मुक्त(hpriv, ureq);

	usbhsh_pipe_detach(hpriv, usbhsh_ep_to_uep(urb->ep));

	usb_hcd_unlink_urb_from_ep(hcd, urb);
	usb_hcd_giveback_urb(hcd, urb, status);
पूर्ण

अटल पूर्णांक usbhsh_queue_push(काष्ठा usb_hcd *hcd,
			     काष्ठा urb *urb,
			     gfp_t mem_flags)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	काष्ठा usbhsh_ep *uep = usbhsh_ep_to_uep(urb->ep);
	काष्ठा usbhs_pipe *pipe = usbhsh_uep_to_pipe(uep);
	काष्ठा device *dev = usbhsh_hcd_to_dev(hcd);
	काष्ठा usbhsh_request *ureq;
	व्योम *buf;
	पूर्णांक len, sequence;

	अगर (usb_pipeisoc(urb->pipe)) अणु
		dev_err(dev, "pipe iso is not supported now\n");
		वापस -EIO;
	पूर्ण

	/* this ureq will be मुक्तd on usbhsh_queue_करोne() */
	ureq = usbhsh_ureq_alloc(hpriv, urb, mem_flags);
	अगर (unlikely(!ureq)) अणु
		dev_err(dev, "ureq alloc fail\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (usb_pipein(urb->pipe))
		pipe->handler = &usbhs_fअगरo_dma_pop_handler;
	अन्यथा
		pipe->handler = &usbhs_fअगरo_dma_push_handler;

	buf = (व्योम *)(urb->transfer_buffer + urb->actual_length);
	len = urb->transfer_buffer_length - urb->actual_length;

	sequence = usb_gettoggle(urb->dev,
				 usb_pipeendpoपूर्णांक(urb->pipe),
				 usb_pipeout(urb->pipe));

	dev_dbg(dev, "%s\n", __func__);
	usbhs_pkt_push(pipe, &ureq->pkt, usbhsh_queue_करोne,
		       buf, len, (urb->transfer_flags & URB_ZERO_PACKET),
		       sequence);

	usbhs_pkt_start(pipe);

	वापस 0;
पूर्ण

अटल व्योम usbhsh_queue_क्रमce_pop(काष्ठा usbhs_priv *priv,
				   काष्ठा usbhs_pipe *pipe)
अणु
	काष्ठा usbhs_pkt *pkt;

	जबतक (1) अणु
		pkt = usbhs_pkt_pop(pipe, शून्य);
		अगर (!pkt)
			अवरोध;

		/*
		 * अगर all packet are gone, usbhsh_endpoपूर्णांक_disable()
		 * will be called.
		 * then, attached device/endpoपूर्णांक/pipe will be detached
		 */
		usbhsh_queue_करोne(priv, pkt);
	पूर्ण
पूर्ण

अटल व्योम usbhsh_queue_क्रमce_pop_all(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_pipe *pos;
	पूर्णांक i;

	usbhs_क्रम_each_pipe_with_dcp(pos, priv, i)
		usbhsh_queue_क्रमce_pop(priv, pos);
पूर्ण

/*
 *		DCP setup stage
 */
अटल पूर्णांक usbhsh_is_request_address(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req;

	req = (काष्ठा usb_ctrlrequest *)urb->setup_packet;

	अगर ((DeviceOutRequest    == req->bRequestType << 8) &&
	    (USB_REQ_SET_ADDRESS == req->bRequest))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम usbhsh_setup_stage_packet_push(काष्ठा usbhsh_hpriv *hpriv,
					   काष्ठा urb *urb,
					   काष्ठा usbhs_pipe *pipe)
अणु
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा usb_ctrlrequest req;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	/*
	 * रुको setup packet ACK
	 * see
	 *	usbhsh_irq_setup_ack()
	 *	usbhsh_irq_setup_err()
	 */
	init_completion(&hpriv->setup_ack_करोne);

	/* copy original request */
	स_नकल(&req, urb->setup_packet, माप(काष्ठा usb_ctrlrequest));

	/*
	 * renesas_usbhs can not use original usb address.
	 * see HARDWARE LIMITATION.
	 * modअगरy usb address here to use attached device.
	 * see usbhsh_device_attach()
	 */
	अगर (usbhsh_is_request_address(urb)) अणु
		काष्ठा usb_device *usbv = usbhsh_urb_to_usbv(urb);
		काष्ठा usbhsh_device *udev = usbhsh_usbv_to_udev(usbv);

		/* udev is a attached device */
		req.wValue = usbhsh_device_number(hpriv, udev);
		dev_dbg(dev, "create new address - %d\n", req.wValue);
	पूर्ण

	/* set request */
	usbhs_usbreq_set_val(priv, &req);

	/*
	 * रुको setup packet ACK
	 */
	रुको_क्रम_completion(&hpriv->setup_ack_करोne);

	dev_dbg(dev, "%s done\n", __func__);
पूर्ण

/*
 *		DCP data stage
 */
अटल व्योम usbhsh_data_stage_packet_करोne(काष्ठा usbhs_priv *priv,
					  काष्ठा usbhs_pkt *pkt)
अणु
	काष्ठा usbhsh_request *ureq = usbhsh_pkt_to_ureq(pkt);
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);

	/* this ureq was connected to urb when usbhsh_urb_enqueue()  */

	usbhsh_ureq_मुक्त(hpriv, ureq);
पूर्ण

अटल पूर्णांक usbhsh_data_stage_packet_push(काष्ठा usbhsh_hpriv *hpriv,
					 काष्ठा urb *urb,
					 काष्ठा usbhs_pipe *pipe,
					 gfp_t mem_flags)

अणु
	काष्ठा usbhsh_request *ureq;

	/* this ureq will be मुक्तd on usbhsh_data_stage_packet_करोne() */
	ureq = usbhsh_ureq_alloc(hpriv, urb, mem_flags);
	अगर (unlikely(!ureq))
		वापस -ENOMEM;

	अगर (usb_pipein(urb->pipe))
		pipe->handler = &usbhs_dcp_data_stage_in_handler;
	अन्यथा
		pipe->handler = &usbhs_dcp_data_stage_out_handler;

	usbhs_pkt_push(pipe, &ureq->pkt,
		       usbhsh_data_stage_packet_करोne,
		       urb->transfer_buffer,
		       urb->transfer_buffer_length,
		       (urb->transfer_flags & URB_ZERO_PACKET),
		       -1);

	वापस 0;
पूर्ण

/*
 *		DCP status stage
 */
अटल पूर्णांक usbhsh_status_stage_packet_push(काष्ठा usbhsh_hpriv *hpriv,
					    काष्ठा urb *urb,
					    काष्ठा usbhs_pipe *pipe,
					    gfp_t mem_flags)
अणु
	काष्ठा usbhsh_request *ureq;

	/* This ureq will be मुक्तd on usbhsh_queue_करोne() */
	ureq = usbhsh_ureq_alloc(hpriv, urb, mem_flags);
	अगर (unlikely(!ureq))
		वापस -ENOMEM;

	अगर (usb_pipein(urb->pipe))
		pipe->handler = &usbhs_dcp_status_stage_in_handler;
	अन्यथा
		pipe->handler = &usbhs_dcp_status_stage_out_handler;

	usbhs_pkt_push(pipe, &ureq->pkt,
		       usbhsh_queue_करोne,
		       शून्य,
		       urb->transfer_buffer_length,
		       0, -1);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsh_dcp_queue_push(काष्ठा usb_hcd *hcd,
				 काष्ठा urb *urb,
				 gfp_t mflags)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	काष्ठा usbhsh_ep *uep = usbhsh_ep_to_uep(urb->ep);
	काष्ठा usbhs_pipe *pipe = usbhsh_uep_to_pipe(uep);
	काष्ठा device *dev = usbhsh_hcd_to_dev(hcd);
	पूर्णांक ret;

	dev_dbg(dev, "%s\n", __func__);

	/*
	 * setup stage
	 *
	 * usbhsh_send_setup_stage_packet() रुको SACK/SIGN
	 */
	usbhsh_setup_stage_packet_push(hpriv, urb, pipe);

	/*
	 * data stage
	 *
	 * It is pushed only when urb has buffer.
	 */
	अगर (urb->transfer_buffer_length) अणु
		ret = usbhsh_data_stage_packet_push(hpriv, urb, pipe, mflags);
		अगर (ret < 0) अणु
			dev_err(dev, "data stage failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * status stage
	 */
	ret = usbhsh_status_stage_packet_push(hpriv, urb, pipe, mflags);
	अगर (ret < 0) अणु
		dev_err(dev, "status stage failed\n");
		वापस ret;
	पूर्ण

	/*
	 * start pushed packets
	 */
	usbhs_pkt_start(pipe);

	वापस 0;
पूर्ण

/*
 *		dma map functions
 */
अटल पूर्णांक usbhsh_dma_map_ctrl(काष्ठा device *dma_dev, काष्ठा usbhs_pkt *pkt,
			       पूर्णांक map)
अणु
	अगर (map) अणु
		काष्ठा usbhsh_request *ureq = usbhsh_pkt_to_ureq(pkt);
		काष्ठा urb *urb = ureq->urb;

		/* it can not use scatter/gather */
		अगर (urb->num_sgs)
			वापस -EINVAL;

		pkt->dma = urb->transfer_dma;
		अगर (!pkt->dma)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *		क्रम hc_driver
 */
अटल पूर्णांक usbhsh_host_start(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण

अटल व्योम usbhsh_host_stop(काष्ठा usb_hcd *hcd)
अणु
पूर्ण

अटल पूर्णांक usbhsh_urb_enqueue(काष्ठा usb_hcd *hcd,
			      काष्ठा urb *urb,
			      gfp_t mem_flags)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	काष्ठा usb_host_endpoपूर्णांक *ep = urb->ep;
	काष्ठा usbhsh_device *new_udev = शून्य;
	पूर्णांक is_dir_in = usb_pipein(urb->pipe);
	पूर्णांक ret;

	dev_dbg(dev, "%s (%s)\n", __func__, is_dir_in ? "in" : "out");

	अगर (!usbhsh_is_running(hpriv)) अणु
		ret = -EIO;
		dev_err(dev, "host is not running\n");
		जाओ usbhsh_urb_enqueue_error_not_linked;
	पूर्ण

	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (ret) अणु
		dev_err(dev, "urb link failed\n");
		जाओ usbhsh_urb_enqueue_error_not_linked;
	पूर्ण

	/*
	 * attach udev अगर needed
	 * see [image of mod_host]
	 */
	अगर (!usbhsh_device_get(hpriv, urb)) अणु
		new_udev = usbhsh_device_attach(hpriv, urb);
		अगर (!new_udev) अणु
			ret = -EIO;
			dev_err(dev, "device attach failed\n");
			जाओ usbhsh_urb_enqueue_error_not_linked;
		पूर्ण
	पूर्ण

	/*
	 * attach endpoपूर्णांक अगर needed
	 * see [image of mod_host]
	 */
	अगर (!usbhsh_ep_to_uep(ep)) अणु
		ret = usbhsh_endpoपूर्णांक_attach(hpriv, urb, mem_flags);
		अगर (ret < 0) अणु
			dev_err(dev, "endpoint attach failed\n");
			जाओ usbhsh_urb_enqueue_error_मुक्त_device;
		पूर्ण
	पूर्ण

	/*
	 * attach pipe to endpoपूर्णांक
	 * see [image of mod_host]
	 */
	ret = usbhsh_pipe_attach(hpriv, urb);
	अगर (ret < 0) अणु
		dev_err(dev, "pipe attach failed\n");
		जाओ usbhsh_urb_enqueue_error_मुक्त_endpoपूर्णांक;
	पूर्ण

	/*
	 * push packet
	 */
	अगर (usb_pipecontrol(urb->pipe))
		ret = usbhsh_dcp_queue_push(hcd, urb, mem_flags);
	अन्यथा
		ret = usbhsh_queue_push(hcd, urb, mem_flags);

	वापस ret;

usbhsh_urb_enqueue_error_मुक्त_endpoपूर्णांक:
	usbhsh_endpoपूर्णांक_detach(hpriv, ep);
usbhsh_urb_enqueue_error_मुक्त_device:
	अगर (new_udev)
		usbhsh_device_detach(hpriv, new_udev);
usbhsh_urb_enqueue_error_not_linked:

	dev_dbg(dev, "%s error\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक usbhsh_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	काष्ठा usbhsh_request *ureq = usbhsh_urb_to_ureq(urb);

	अगर (ureq) अणु
		काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
		काष्ठा usbhs_pkt *pkt = &ureq->pkt;

		usbhs_pkt_pop(pkt->pipe, pkt);
		usbhsh_queue_करोne(priv, pkt);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम usbhsh_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
				    काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा usbhsh_ep *uep = usbhsh_ep_to_uep(ep);
	काष्ठा usbhsh_device *udev;
	काष्ठा usbhsh_hpriv *hpriv;

	/*
	 * this function might be called manyबार by same hcd/ep
	 * in-endpoपूर्णांक == out-endpoपूर्णांक अगर ep == dcp.
	 */
	अगर (!uep)
		वापस;

	udev	= usbhsh_uep_to_udev(uep);
	hpriv	= usbhsh_hcd_to_hpriv(hcd);

	usbhsh_endpoपूर्णांक_detach(hpriv, ep);

	/*
	 * अगर there is no endpoपूर्णांक,
	 * मुक्त device
	 */
	अगर (!usbhsh_device_has_endpoपूर्णांक(udev))
		usbhsh_device_detach(hpriv, udev);
पूर्ण

अटल पूर्णांक usbhsh_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	पूर्णांक roothub_id = 1; /* only 1 root hub */

	/*
	 * करोes port stat was changed ?
	 * check USB_PORT_STAT_C_xxx << 16
	 */
	अगर (usbhsh_port_stat_get(hpriv) & 0xFFFF0000)
		*buf = (1 << roothub_id);
	अन्यथा
		*buf = 0;

	वापस !!(*buf);
पूर्ण

अटल पूर्णांक __usbhsh_hub_hub_feature(काष्ठा usbhsh_hpriv *hpriv,
				    u16 typeReq, u16 wValue,
				    u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	चयन (wValue) अणु
	हाल C_HUB_OVER_CURRENT:
	हाल C_HUB_LOCAL_POWER:
		dev_dbg(dev, "%s :: C_HUB_xx\n", __func__);
		वापस 0;
	पूर्ण

	वापस -EPIPE;
पूर्ण

अटल पूर्णांक __usbhsh_hub_port_feature(काष्ठा usbhsh_hpriv *hpriv,
				     u16 typeReq, u16 wValue,
				     u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक enable = (typeReq == SetPortFeature);
	पूर्णांक speed, i, समयout = 128;
	पूर्णांक roothub_id = 1; /* only 1 root hub */

	/* common error */
	अगर (wIndex > roothub_id || wLength != 0)
		वापस -EPIPE;

	/* check wValue */
	चयन (wValue) अणु
	हाल USB_PORT_FEAT_POWER:
		usbhs_vbus_ctrl(priv, enable);
		dev_dbg(dev, "%s :: USB_PORT_FEAT_POWER\n", __func__);
		अवरोध;

	हाल USB_PORT_FEAT_ENABLE:
	हाल USB_PORT_FEAT_SUSPEND:
	हाल USB_PORT_FEAT_C_ENABLE:
	हाल USB_PORT_FEAT_C_SUSPEND:
	हाल USB_PORT_FEAT_C_CONNECTION:
	हाल USB_PORT_FEAT_C_OVER_CURRENT:
	हाल USB_PORT_FEAT_C_RESET:
		dev_dbg(dev, "%s :: USB_PORT_FEAT_xxx\n", __func__);
		अवरोध;

	हाल USB_PORT_FEAT_RESET:
		अगर (!enable)
			अवरोध;

		usbhsh_port_stat_clear(hpriv,
				       USB_PORT_STAT_HIGH_SPEED |
				       USB_PORT_STAT_LOW_SPEED);

		usbhsh_queue_क्रमce_pop_all(priv);

		usbhs_bus_send_reset(priv);
		msleep(20);
		usbhs_bus_send_sof_enable(priv);

		क्रम (i = 0; i < समयout ; i++) अणु
			चयन (usbhs_bus_get_speed(priv)) अणु
			हाल USB_SPEED_LOW:
				speed = USB_PORT_STAT_LOW_SPEED;
				जाओ got_usb_bus_speed;
			हाल USB_SPEED_HIGH:
				speed = USB_PORT_STAT_HIGH_SPEED;
				जाओ got_usb_bus_speed;
			हाल USB_SPEED_FULL:
				speed = 0;
				जाओ got_usb_bus_speed;
			पूर्ण

			msleep(20);
		पूर्ण
		वापस -EPIPE;

got_usb_bus_speed:
		usbhsh_port_stat_set(hpriv, speed);
		usbhsh_port_stat_set(hpriv, USB_PORT_STAT_ENABLE);

		dev_dbg(dev, "%s :: USB_PORT_FEAT_RESET (speed = %d)\n",
			__func__, speed);

		/* status change is not needed */
		वापस 0;

	शेष:
		वापस -EPIPE;
	पूर्ण

	/* set/clear status */
	अगर (enable)
		usbhsh_port_stat_set(hpriv, (1 << wValue));
	अन्यथा
		usbhsh_port_stat_clear(hpriv, (1 << wValue));

	वापस 0;
पूर्ण

अटल पूर्णांक __usbhsh_hub_get_status(काष्ठा usbhsh_hpriv *hpriv,
				   u16 typeReq, u16 wValue,
				   u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा usb_hub_descriptor *desc = (काष्ठा usb_hub_descriptor *)buf;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक roothub_id = 1; /* only 1 root hub */

	चयन (typeReq) अणु
	हाल GetHubStatus:
		dev_dbg(dev, "%s :: GetHubStatus\n", __func__);

		*buf = 0x00;
		अवरोध;

	हाल GetPortStatus:
		अगर (wIndex != roothub_id)
			वापस -EPIPE;

		dev_dbg(dev, "%s :: GetPortStatus\n", __func__);
		*(__le32 *)buf = cpu_to_le32(usbhsh_port_stat_get(hpriv));
		अवरोध;

	हाल GetHubDescriptor:
		desc->bDescriptorType		= USB_DT_HUB;
		desc->bHubContrCurrent		= 0;
		desc->bNbrPorts			= roothub_id;
		desc->bDescLength		= 9;
		desc->bPwrOn2PwrGood		= 0;
		desc->wHubCharacteristics	=
			cpu_to_le16(HUB_CHAR_INDV_PORT_LPSM | HUB_CHAR_NO_OCPM);
		desc->u.hs.DeviceRemovable[0]	= (roothub_id << 1);
		desc->u.hs.DeviceRemovable[1]	= ~0;
		dev_dbg(dev, "%s :: GetHubDescriptor\n", __func__);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsh_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
			      u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	काष्ठा usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक ret = -EPIPE;

	चयन (typeReq) अणु

	/* Hub Feature */
	हाल ClearHubFeature:
	हाल SetHubFeature:
		ret = __usbhsh_hub_hub_feature(hpriv, typeReq,
					       wValue, wIndex, buf, wLength);
		अवरोध;

	/* Port Feature */
	हाल SetPortFeature:
	हाल ClearPortFeature:
		ret = __usbhsh_hub_port_feature(hpriv, typeReq,
						wValue, wIndex, buf, wLength);
		अवरोध;

	/* Get status */
	हाल GetHubStatus:
	हाल GetPortStatus:
	हाल GetHubDescriptor:
		ret = __usbhsh_hub_get_status(hpriv, typeReq,
					      wValue, wIndex, buf, wLength);
		अवरोध;
	पूर्ण

	dev_dbg(dev, "typeReq = %x, ret = %d, port_stat = %x\n",
		typeReq, ret, usbhsh_port_stat_get(hpriv));

	वापस ret;
पूर्ण

अटल पूर्णांक usbhsh_bus_nop(काष्ठा usb_hcd *hcd)
अणु
	/* nothing to करो */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hc_driver usbhsh_driver = अणु
	.description =		usbhsh_hcd_name,
	.hcd_priv_size =	माप(काष्ठा usbhsh_hpriv),

	/*
	 * generic hardware linkage
	 */
	.flags =		HCD_DMA | HCD_USB2,

	.start =		usbhsh_host_start,
	.stop =			usbhsh_host_stop,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		usbhsh_urb_enqueue,
	.urb_dequeue =		usbhsh_urb_dequeue,
	.endpoपूर्णांक_disable =	usbhsh_endpoपूर्णांक_disable,

	/*
	 * root hub
	 */
	.hub_status_data =	usbhsh_hub_status_data,
	.hub_control =		usbhsh_hub_control,
	.bus_suspend =		usbhsh_bus_nop,
	.bus_resume =		usbhsh_bus_nop,
पूर्ण;

/*
 *		पूर्णांकerrupt functions
 */
अटल पूर्णांक usbhsh_irq_attch(काष्ठा usbhs_priv *priv,
			    काष्ठा usbhs_irq_state *irq_state)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	dev_dbg(dev, "device attached\n");

	usbhsh_port_stat_set(hpriv, USB_PORT_STAT_CONNECTION);
	usbhsh_port_stat_set(hpriv, USB_PORT_STAT_C_CONNECTION << 16);

	/*
	 * attch पूर्णांकerrupt might happen infinitely on some device
	 * (on self घातer USB hub ?)
	 * disable it here.
	 *
	 * usbhsh_is_running() becomes effective
	 * according to this process.
	 * see
	 *	usbhsh_is_running()
	 *	usbhsh_urb_enqueue()
	 */
	hpriv->mod.irq_attch = शून्य;
	usbhs_irq_callback_update(priv, &hpriv->mod);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsh_irq_dtch(काष्ठा usbhs_priv *priv,
			   काष्ठा usbhs_irq_state *irq_state)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	dev_dbg(dev, "device detached\n");

	usbhsh_port_stat_clear(hpriv, USB_PORT_STAT_CONNECTION);
	usbhsh_port_stat_set(hpriv, USB_PORT_STAT_C_CONNECTION << 16);

	/*
	 * enable attch पूर्णांकerrupt again
	 *
	 * usbhsh_is_running() becomes invalid
	 * according to this process.
	 * see
	 *	usbhsh_is_running()
	 *	usbhsh_urb_enqueue()
	 */
	hpriv->mod.irq_attch = usbhsh_irq_attch;
	usbhs_irq_callback_update(priv, &hpriv->mod);

	/*
	 * usbhsh_queue_क्रमce_pop_all() should be called
	 * after usbhsh_is_running() becomes invalid.
	 */
	usbhsh_queue_क्रमce_pop_all(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsh_irq_setup_ack(काष्ठा usbhs_priv *priv,
				काष्ठा usbhs_irq_state *irq_state)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	dev_dbg(dev, "setup packet OK\n");

	complete(&hpriv->setup_ack_करोne); /* see usbhsh_urb_enqueue() */

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsh_irq_setup_err(काष्ठा usbhs_priv *priv,
				काष्ठा usbhs_irq_state *irq_state)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	dev_dbg(dev, "setup packet Err\n");

	complete(&hpriv->setup_ack_करोne); /* see usbhsh_urb_enqueue() */

	वापस 0;
पूर्ण

/*
 *		module start/stop
 */
अटल व्योम usbhsh_pipe_init_क्रम_host(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	काष्ठा usbhs_pipe *pipe;
	काष्ठा renesas_usbhs_driver_pipe_config *pipe_configs =
					usbhs_get_dparam(priv, pipe_configs);
	पूर्णांक pipe_size = usbhs_get_dparam(priv, pipe_size);
	पूर्णांक old_type, dir_in, i;

	/* init all pipe */
	old_type = USB_ENDPOINT_XFER_CONTROL;
	क्रम (i = 0; i < pipe_size; i++) अणु

		/*
		 * data "output" will be finished as soon as possible,
		 * but there is no guaranty at data "input" हाल.
		 *
		 * "input" needs "standby" pipe.
		 * So, "input" direction pipe > "output" direction pipe
		 * is good idea.
		 *
		 * 1st USB_ENDPOINT_XFER_xxx will be output direction,
		 * and the other will be input direction here.
		 *
		 * ex)
		 * ...
		 * USB_ENDPOINT_XFER_ISOC -> dir out
		 * USB_ENDPOINT_XFER_ISOC -> dir in
		 * USB_ENDPOINT_XFER_BULK -> dir out
		 * USB_ENDPOINT_XFER_BULK -> dir in
		 * USB_ENDPOINT_XFER_BULK -> dir in
		 * ...
		 */
		dir_in = (pipe_configs[i].type == old_type);
		old_type = pipe_configs[i].type;

		अगर (USB_ENDPOINT_XFER_CONTROL == pipe_configs[i].type) अणु
			pipe = usbhs_dcp_दो_स्मृति(priv);
			usbhsh_hpriv_to_dcp(hpriv) = pipe;
		पूर्ण अन्यथा अणु
			pipe = usbhs_pipe_दो_स्मृति(priv,
						 pipe_configs[i].type,
						 dir_in);
		पूर्ण

		pipe->mod_निजी = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक usbhsh_start(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	काष्ठा usb_hcd *hcd = usbhsh_hpriv_to_hcd(hpriv);
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक ret;

	/* add hcd */
	ret = usb_add_hcd(hcd, 0, 0);
	अगर (ret < 0)
		वापस 0;
	device_wakeup_enable(hcd->self.controller);

	/*
	 * pipe initialize and enable DCP
	 */
	usbhs_fअगरo_init(priv);
	usbhs_pipe_init(priv,
			usbhsh_dma_map_ctrl);
	usbhsh_pipe_init_क्रम_host(priv);

	/*
	 * प्रणाली config enble
	 * - HI speed
	 * - host
	 * - usb module
	 */
	usbhs_sys_host_ctrl(priv, 1);

	/*
	 * enable irq callback
	 */
	mod->irq_attch		= usbhsh_irq_attch;
	mod->irq_dtch		= usbhsh_irq_dtch;
	mod->irq_sack		= usbhsh_irq_setup_ack;
	mod->irq_sign		= usbhsh_irq_setup_err;
	usbhs_irq_callback_update(priv, mod);

	dev_dbg(dev, "start host\n");

	वापस ret;
पूर्ण

अटल पूर्णांक usbhsh_stop(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	काष्ठा usb_hcd *hcd = usbhsh_hpriv_to_hcd(hpriv);
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	/*
	 * disable irq callback
	 */
	mod->irq_attch	= शून्य;
	mod->irq_dtch	= शून्य;
	mod->irq_sack	= शून्य;
	mod->irq_sign	= शून्य;
	usbhs_irq_callback_update(priv, mod);

	usb_हटाओ_hcd(hcd);

	/* disable sys */
	usbhs_sys_host_ctrl(priv, 0);

	dev_dbg(dev, "quit host\n");

	वापस 0;
पूर्ण

पूर्णांक usbhs_mod_host_probe(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhsh_hpriv *hpriv;
	काष्ठा usb_hcd *hcd;
	काष्ठा usbhsh_device *udev;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक i;

	/* initialize hcd */
	hcd = usb_create_hcd(&usbhsh_driver, dev, usbhsh_hcd_name);
	अगर (!hcd) अणु
		dev_err(dev, "Failed to create hcd\n");
		वापस -ENOMEM;
	पूर्ण
	hcd->has_tt = 1; /* क्रम low/full speed */

	/*
	 * CAUTION
	 *
	 * There is no guarantee that it is possible to access usb module here.
	 * Don't accesses to it.
	 * The accesse will be enable after "usbhsh_start"
	 */

	hpriv = usbhsh_hcd_to_hpriv(hcd);

	/*
	 * रेजिस्टर itself
	 */
	usbhs_mod_रेजिस्टर(priv, &hpriv->mod, USBHS_HOST);

	/* init hpriv */
	hpriv->mod.name		= "host";
	hpriv->mod.start	= usbhsh_start;
	hpriv->mod.stop		= usbhsh_stop;
	usbhsh_port_stat_init(hpriv);

	/* init all device */
	usbhsh_क्रम_each_udev_with_dev0(udev, hpriv, i) अणु
		udev->usbv	= शून्य;
		INIT_LIST_HEAD(&udev->ep_list_head);
	पूर्ण

	dev_info(dev, "host probed\n");

	वापस 0;
पूर्ण

पूर्णांक usbhs_mod_host_हटाओ(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	काष्ठा usb_hcd *hcd = usbhsh_hpriv_to_hcd(hpriv);

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण
