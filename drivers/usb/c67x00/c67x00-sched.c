<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * c67x00-sched.c: Cypress C67X00 USB Host Controller Driver - TD scheduling
 *
 * Copyright (C) 2006-2008 Barco N.V.
 *    Derived from the Cypress cy7c67200/300 ezusb linux driver and
 *    based on multiple host controller drivers inside the linux kernel.
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>

#समावेश "c67x00.h"
#समावेश "c67x00-hcd.h"

/*
 * These are the stages क्रम a control urb, they are kept
 * in both urb->पूर्णांकerval and td->privdata.
 */
#घोषणा SETUP_STAGE		0
#घोषणा DATA_STAGE		1
#घोषणा STATUS_STAGE		2

/* -------------------------------------------------------------------------- */

/*
 * काष्ठा c67x00_ep_data: Host endpoपूर्णांक data काष्ठाure
 */
काष्ठा c67x00_ep_data अणु
	काष्ठा list_head queue;
	काष्ठा list_head node;
	काष्ठा usb_host_endpoपूर्णांक *hep;
	काष्ठा usb_device *dev;
	u16 next_frame;		/* For पूर्णांक/isoc transactions */
पूर्ण;

/*
 * काष्ठा c67x00_td
 *
 * Hardware parts are little endiannes, SW in CPU endianess.
 */
काष्ठा c67x00_td अणु
	/* HW specअगरic part */
	__le16 ly_base_addr;	/* Bytes 0-1 */
	__le16 port_length;	/* Bytes 2-3 */
	u8 pid_ep;		/* Byte 4 */
	u8 dev_addr;		/* Byte 5 */
	u8 ctrl_reg;		/* Byte 6 */
	u8 status;		/* Byte 7 */
	u8 retry_cnt;		/* Byte 8 */
#घोषणा TT_OFFSET		2
#घोषणा TT_CONTROL		0
#घोषणा TT_ISOCHRONOUS		1
#घोषणा TT_BULK			2
#घोषणा TT_INTERRUPT		3
	u8 residue;		/* Byte 9 */
	__le16 next_td_addr;	/* Bytes 10-11 */
	/* SW part */
	काष्ठा list_head td_list;
	u16 td_addr;
	व्योम *data;
	काष्ठा urb *urb;
	अचिन्हित दीर्घ privdata;

	/* These are needed क्रम handling the toggle bits:
	 * an urb can be dequeued जबतक a td is in progress
	 * after checking the td, the toggle bit might need to
	 * be fixed */
	काष्ठा c67x00_ep_data *ep_data;
	अचिन्हित पूर्णांक pipe;
पूर्ण;

काष्ठा c67x00_urb_priv अणु
	काष्ठा list_head hep_node;
	काष्ठा urb *urb;
	पूर्णांक port;
	पूर्णांक cnt;		/* packet number क्रम isoc */
	पूर्णांक status;
	काष्ठा c67x00_ep_data *ep_data;
पूर्ण;

#घोषणा td_udev(td)	((td)->ep_data->dev)

#घोषणा CY_TD_SIZE		12

#घोषणा TD_PIDEP_OFFSET		0x04
#घोषणा TD_PIDEPMASK_PID	0xF0
#घोषणा TD_PIDEPMASK_EP		0x0F
#घोषणा TD_PORTLENMASK_DL	0x03FF
#घोषणा TD_PORTLENMASK_PN	0xC000

#घोषणा TD_STATUS_OFFSET	0x07
#घोषणा TD_STATUSMASK_ACK	0x01
#घोषणा TD_STATUSMASK_ERR	0x02
#घोषणा TD_STATUSMASK_TMOUT	0x04
#घोषणा TD_STATUSMASK_SEQ	0x08
#घोषणा TD_STATUSMASK_SETUP	0x10
#घोषणा TD_STATUSMASK_OVF	0x20
#घोषणा TD_STATUSMASK_NAK	0x40
#घोषणा TD_STATUSMASK_STALL	0x80

#घोषणा TD_ERROR_MASK		(TD_STATUSMASK_ERR | TD_STATUSMASK_TMOUT | \
				 TD_STATUSMASK_STALL)

#घोषणा TD_RETRYCNT_OFFSET	0x08
#घोषणा TD_RETRYCNTMASK_ACT_FLG	0x10
#घोषणा TD_RETRYCNTMASK_TX_TYPE	0x0C
#घोषणा TD_RETRYCNTMASK_RTY_CNT	0x03

#घोषणा TD_RESIDUE_OVERFLOW	0x80

#घोषणा TD_PID_IN		0x90

/* Residue: चिन्हित 8bits, neg -> OVERFLOW, pos -> UNDERFLOW */
#घोषणा td_residue(td)		((__s8)(td->residue))
#घोषणा td_ly_base_addr(td)	(__le16_to_cpu((td)->ly_base_addr))
#घोषणा td_port_length(td)	(__le16_to_cpu((td)->port_length))
#घोषणा td_next_td_addr(td)	(__le16_to_cpu((td)->next_td_addr))

#घोषणा td_active(td)		((td)->retry_cnt & TD_RETRYCNTMASK_ACT_FLG)
#घोषणा td_length(td)		(td_port_length(td) & TD_PORTLENMASK_DL)

#घोषणा td_sequence_ok(td)	(!td->status || \
				 (!(td->status & TD_STATUSMASK_SEQ) ==	\
				  !(td->ctrl_reg & SEQ_SEL)))

#घोषणा td_acked(td)		(!td->status || \
				 (td->status & TD_STATUSMASK_ACK))
#घोषणा td_actual_bytes(td)	(td_length(td) - td_residue(td))

/* -------------------------------------------------------------------------- */

/*
 * dbg_td - Dump the contents of the TD
 */
अटल व्योम dbg_td(काष्ठा c67x00_hcd *c67x00, काष्ठा c67x00_td *td, अक्षर *msg)
अणु
	काष्ठा device *dev = c67x00_hcd_dev(c67x00);

	dev_dbg(dev, "### %s at 0x%04x\n", msg, td->td_addr);
	dev_dbg(dev, "urb:      0x%p\n", td->urb);
	dev_dbg(dev, "endpoint:   %4d\n", usb_pipeendpoपूर्णांक(td->pipe));
	dev_dbg(dev, "pipeout:    %4d\n", usb_pipeout(td->pipe));
	dev_dbg(dev, "ly_base_addr: 0x%04x\n", td_ly_base_addr(td));
	dev_dbg(dev, "port_length:  0x%04x\n", td_port_length(td));
	dev_dbg(dev, "pid_ep:         0x%02x\n", td->pid_ep);
	dev_dbg(dev, "dev_addr:       0x%02x\n", td->dev_addr);
	dev_dbg(dev, "ctrl_reg:       0x%02x\n", td->ctrl_reg);
	dev_dbg(dev, "status:         0x%02x\n", td->status);
	dev_dbg(dev, "retry_cnt:      0x%02x\n", td->retry_cnt);
	dev_dbg(dev, "residue:        0x%02x\n", td->residue);
	dev_dbg(dev, "next_td_addr: 0x%04x\n", td_next_td_addr(td));
	dev_dbg(dev, "data: %*ph\n", td_length(td), td->data);
पूर्ण

/* -------------------------------------------------------------------------- */
/* Helper functions */

अटल अंतरभूत u16 c67x00_get_current_frame_number(काष्ठा c67x00_hcd *c67x00)
अणु
	वापस c67x00_ll_husb_get_frame(c67x00->sie) & HOST_FRAME_MASK;
पूर्ण

/*
 * frame_add
 * Software wraparound क्रम framक्रमागतbers.
 */
अटल अंतरभूत u16 frame_add(u16 a, u16 b)
अणु
	वापस (a + b) & HOST_FRAME_MASK;
पूर्ण

/*
 * frame_after - is frame a after frame b
 */
अटल अंतरभूत पूर्णांक frame_after(u16 a, u16 b)
अणु
	वापस ((HOST_FRAME_MASK + a - b) & HOST_FRAME_MASK) <
	    (HOST_FRAME_MASK / 2);
पूर्ण

/*
 * frame_after_eq - is frame a after or equal to frame b
 */
अटल अंतरभूत पूर्णांक frame_after_eq(u16 a, u16 b)
अणु
	वापस ((HOST_FRAME_MASK + 1 + a - b) & HOST_FRAME_MASK) <
	    (HOST_FRAME_MASK / 2);
पूर्ण

/* -------------------------------------------------------------------------- */

/*
 * c67x00_release_urb - हटाओ link from all tds to this urb
 * Disconnects the urb from it's tds, so that it can be given back.
 * pre: urb->hcpriv != शून्य
 */
अटल व्योम c67x00_release_urb(काष्ठा c67x00_hcd *c67x00, काष्ठा urb *urb)
अणु
	काष्ठा c67x00_td *td;
	काष्ठा c67x00_urb_priv *urbp;

	BUG_ON(!urb);

	c67x00->urb_count--;

	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
		c67x00->urb_iso_count--;
		अगर (c67x00->urb_iso_count == 0)
			c67x00->max_frame_bw = MAX_FRAME_BW_STD;
	पूर्ण

	/* TODO this might be not so efficient when we've got many urbs!
	 * Alternatives:
	 *   * only clear when needed
	 *   * keep a list of tds with each urbp
	 */
	list_क्रम_each_entry(td, &c67x00->td_list, td_list)
		अगर (urb == td->urb)
			td->urb = शून्य;

	urbp = urb->hcpriv;
	urb->hcpriv = शून्य;
	list_del(&urbp->hep_node);
	kमुक्त(urbp);
पूर्ण

/* -------------------------------------------------------------------------- */

अटल काष्ठा c67x00_ep_data *
c67x00_ep_data_alloc(काष्ठा c67x00_hcd *c67x00, काष्ठा urb *urb)
अणु
	काष्ठा usb_host_endpoपूर्णांक *hep = urb->ep;
	काष्ठा c67x00_ep_data *ep_data;
	पूर्णांक type;

	c67x00->current_frame = c67x00_get_current_frame_number(c67x00);

	/* Check अगर endpoपूर्णांक alपढ़ोy has a c67x00_ep_data काष्ठा allocated */
	अगर (hep->hcpriv) अणु
		ep_data = hep->hcpriv;
		अगर (frame_after(c67x00->current_frame, ep_data->next_frame))
			ep_data->next_frame =
			    frame_add(c67x00->current_frame, 1);
		वापस hep->hcpriv;
	पूर्ण

	/* Allocate and initialize a new c67x00 endpoपूर्णांक data काष्ठाure */
	ep_data = kzalloc(माप(*ep_data), GFP_ATOMIC);
	अगर (!ep_data)
		वापस शून्य;

	INIT_LIST_HEAD(&ep_data->queue);
	INIT_LIST_HEAD(&ep_data->node);
	ep_data->hep = hep;

	/* hold a reference to udev as दीर्घ as this endpoपूर्णांक lives,
	 * this is needed to possibly fix the data toggle */
	ep_data->dev = usb_get_dev(urb->dev);
	hep->hcpriv = ep_data;

	/* For ISOC and INT endpoपूर्णांकs, start ASAP: */
	ep_data->next_frame = frame_add(c67x00->current_frame, 1);

	/* Add the endpoपूर्णांक data to one of the pipe lists; must be added
	   in order of endpoपूर्णांक address */
	type = usb_pipetype(urb->pipe);
	अगर (list_empty(&ep_data->node)) अणु
		list_add(&ep_data->node, &c67x00->list[type]);
	पूर्ण अन्यथा अणु
		काष्ठा c67x00_ep_data *prev;

		list_क्रम_each_entry(prev, &c67x00->list[type], node) अणु
			अगर (prev->hep->desc.bEndpoपूर्णांकAddress >
			    hep->desc.bEndpoपूर्णांकAddress) अणु
				list_add(&ep_data->node, prev->node.prev);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ep_data;
पूर्ण

अटल पूर्णांक c67x00_ep_data_मुक्त(काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	काष्ठा c67x00_ep_data *ep_data = hep->hcpriv;

	अगर (!ep_data)
		वापस 0;

	अगर (!list_empty(&ep_data->queue))
		वापस -EBUSY;

	usb_put_dev(ep_data->dev);
	list_del(&ep_data->queue);
	list_del(&ep_data->node);

	kमुक्त(ep_data);
	hep->hcpriv = शून्य;

	वापस 0;
पूर्ण

व्योम c67x00_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd, काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	अचिन्हित दीर्घ flags;

	अगर (!list_empty(&ep->urb_list))
		dev_warn(c67x00_hcd_dev(c67x00), "error: urb list not empty\n");

	spin_lock_irqsave(&c67x00->lock, flags);

	/* loop रुकोing क्रम all transfers in the endpoपूर्णांक queue to complete */
	जबतक (c67x00_ep_data_मुक्त(ep)) अणु
		/* Drop the lock so we can sleep रुकोing क्रम the hardware */
		spin_unlock_irqrestore(&c67x00->lock, flags);

		/* it could happen that we reinitialize this completion, जबतक
		 * somebody was रुकोing क्रम that completion.  The समयout and
		 * जबतक loop handle such हालs, but this might be improved */
		reinit_completion(&c67x00->endpoपूर्णांक_disable);
		c67x00_sched_kick(c67x00);
		रुको_क्रम_completion_समयout(&c67x00->endpoपूर्णांक_disable, 1 * HZ);

		spin_lock_irqsave(&c67x00->lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&c67x00->lock, flags);
पूर्ण

/* -------------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक get_root_port(काष्ठा usb_device *dev)
अणु
	जबतक (dev->parent->parent)
		dev = dev->parent;
	वापस dev->portnum;
पूर्ण

पूर्णांक c67x00_urb_enqueue(काष्ठा usb_hcd *hcd,
		       काष्ठा urb *urb, gfp_t mem_flags)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा c67x00_urb_priv *urbp;
	काष्ठा c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	पूर्णांक port = get_root_port(urb->dev)-1;

	/* Allocate and initialize urb निजी data */
	urbp = kzalloc(माप(*urbp), mem_flags);
	अगर (!urbp) अणु
		ret = -ENOMEM;
		जाओ err_urbp;
	पूर्ण

	spin_lock_irqsave(&c67x00->lock, flags);

	/* Make sure host controller is running */
	अगर (!HC_IS_RUNNING(hcd->state)) अणु
		ret = -ENODEV;
		जाओ err_not_linked;
	पूर्ण

	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (ret)
		जाओ err_not_linked;

	INIT_LIST_HEAD(&urbp->hep_node);
	urbp->urb = urb;
	urbp->port = port;

	urbp->ep_data = c67x00_ep_data_alloc(c67x00, urb);

	अगर (!urbp->ep_data) अणु
		ret = -ENOMEM;
		जाओ err_epdata;
	पूर्ण

	/* TODO claim bandwidth with usb_claim_bandwidth?
	 * also release it somewhere! */

	urb->hcpriv = urbp;

	urb->actual_length = 0;	/* Nothing received/transmitted yet */

	चयन (usb_pipetype(urb->pipe)) अणु
	हाल PIPE_CONTROL:
		urb->पूर्णांकerval = SETUP_STAGE;
		अवरोध;
	हाल PIPE_INTERRUPT:
		अवरोध;
	हाल PIPE_BULK:
		अवरोध;
	हाल PIPE_ISOCHRONOUS:
		अगर (c67x00->urb_iso_count == 0)
			c67x00->max_frame_bw = MAX_FRAME_BW_ISO;
		c67x00->urb_iso_count++;
		/* Assume always URB_ISO_ASAP, FIXME */
		अगर (list_empty(&urbp->ep_data->queue))
			urb->start_frame = urbp->ep_data->next_frame;
		अन्यथा अणु
			/* Go right after the last one */
			काष्ठा urb *last_urb;

			last_urb = list_entry(urbp->ep_data->queue.prev,
					      काष्ठा c67x00_urb_priv,
					      hep_node)->urb;
			urb->start_frame =
			    frame_add(last_urb->start_frame,
				      last_urb->number_of_packets *
				      last_urb->पूर्णांकerval);
		पूर्ण
		urbp->cnt = 0;
		अवरोध;
	पूर्ण

	/* Add the URB to the endpoपूर्णांक queue */
	list_add_tail(&urbp->hep_node, &urbp->ep_data->queue);

	/* If this is the only URB, kick start the controller */
	अगर (!c67x00->urb_count++)
		c67x00_ll_hpi_enable_sofeop(c67x00->sie);

	c67x00_sched_kick(c67x00);
	spin_unlock_irqrestore(&c67x00->lock, flags);

	वापस 0;

err_epdata:
	usb_hcd_unlink_urb_from_ep(hcd, urb);
err_not_linked:
	spin_unlock_irqrestore(&c67x00->lock, flags);
	kमुक्त(urbp);
err_urbp:

	वापस ret;
पूर्ण

पूर्णांक c67x00_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&c67x00->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc)
		जाओ करोne;

	c67x00_release_urb(c67x00, urb);
	usb_hcd_unlink_urb_from_ep(hcd, urb);

	spin_unlock(&c67x00->lock);
	usb_hcd_giveback_urb(hcd, urb, status);
	spin_lock(&c67x00->lock);

	spin_unlock_irqrestore(&c67x00->lock, flags);

	वापस 0;

 करोne:
	spin_unlock_irqrestore(&c67x00->lock, flags);
	वापस rc;
पूर्ण

/* -------------------------------------------------------------------------- */

/*
 * pre: c67x00 locked, urb unlocked
 */
अटल व्योम
c67x00_giveback_urb(काष्ठा c67x00_hcd *c67x00, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा c67x00_urb_priv *urbp;

	अगर (!urb)
		वापस;

	urbp = urb->hcpriv;
	urbp->status = status;

	list_del_init(&urbp->hep_node);

	c67x00_release_urb(c67x00, urb);
	usb_hcd_unlink_urb_from_ep(c67x00_hcd_to_hcd(c67x00), urb);
	spin_unlock(&c67x00->lock);
	usb_hcd_giveback_urb(c67x00_hcd_to_hcd(c67x00), urb, status);
	spin_lock(&c67x00->lock);
पूर्ण

/* -------------------------------------------------------------------------- */

अटल पूर्णांक c67x00_claim_frame_bw(काष्ठा c67x00_hcd *c67x00, काष्ठा urb *urb,
				 पूर्णांक len, पूर्णांक periodic)
अणु
	काष्ठा c67x00_urb_priv *urbp = urb->hcpriv;
	पूर्णांक bit_समय;

	/* According to the C67x00 BIOS user manual, page 3-18,19, the
	 * following calculations provide the full speed bit बार क्रम
	 * a transaction.
	 *
	 * FS(in)	= 112.5 +  9.36*BC + HOST_DELAY
	 * FS(in,iso)	=  90.5 +  9.36*BC + HOST_DELAY
	 * FS(out)	= 112.5 +  9.36*BC + HOST_DELAY
	 * FS(out,iso)	=  78.4 +  9.36*BC + HOST_DELAY
	 * LS(in)	= 802.4 + 75.78*BC + HOST_DELAY
	 * LS(out)	= 802.6 + 74.67*BC + HOST_DELAY
	 *
	 * HOST_DELAY == 106 क्रम the c67200 and c67300.
	 */

	/* make calculations in 1/100 bit बार to मुख्यtain resolution */
	अगर (urbp->ep_data->dev->speed == USB_SPEED_LOW) अणु
		/* Low speed pipe */
		अगर (usb_pipein(urb->pipe))
			bit_समय = 80240 + 7578*len;
		अन्यथा
			bit_समय = 80260 + 7467*len;
	पूर्ण अन्यथा अणु
		/* FS pipes */
		अगर (usb_pipeisoc(urb->pipe))
			bit_समय = usb_pipein(urb->pipe) ? 9050 : 7840;
		अन्यथा
			bit_समय = 11250;
		bit_समय += 936*len;
	पूर्ण

	/* Scale back करोwn to पूर्णांकeger bit बार.  Use a host delay of 106.
	 * (this is the only place it is used) */
	bit_समय = ((bit_समय+50) / 100) + 106;

	अगर (unlikely(bit_समय + c67x00->bandwidth_allocated >=
		     c67x00->max_frame_bw))
		वापस -EMSGSIZE;

	अगर (unlikely(c67x00->next_td_addr + CY_TD_SIZE >=
		     c67x00->td_base_addr + SIE_TD_SIZE))
		वापस -EMSGSIZE;

	अगर (unlikely(c67x00->next_buf_addr + len >=
		     c67x00->buf_base_addr + SIE_TD_BUF_SIZE))
		वापस -EMSGSIZE;

	अगर (periodic) अणु
		अगर (unlikely(bit_समय + c67x00->periodic_bw_allocated >=
			     MAX_PERIODIC_BW(c67x00->max_frame_bw)))
			वापस -EMSGSIZE;
		c67x00->periodic_bw_allocated += bit_समय;
	पूर्ण

	c67x00->bandwidth_allocated += bit_समय;
	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */

/*
 * td_addr and buf_addr must be word aligned
 */
अटल पूर्णांक c67x00_create_td(काष्ठा c67x00_hcd *c67x00, काष्ठा urb *urb,
			    व्योम *data, पूर्णांक len, पूर्णांक pid, पूर्णांक toggle,
			    अचिन्हित दीर्घ privdata)
अणु
	काष्ठा c67x00_td *td;
	काष्ठा c67x00_urb_priv *urbp = urb->hcpriv;
	स्थिर __u8 active_flag = 1, retry_cnt = 3;
	__u8 cmd = 0;
	पूर्णांक tt = 0;

	अगर (c67x00_claim_frame_bw(c67x00, urb, len, usb_pipeisoc(urb->pipe)
				  || usb_pipeपूर्णांक(urb->pipe)))
		वापस -EMSGSIZE;	/* Not really an error, but expected */

	td = kzalloc(माप(*td), GFP_ATOMIC);
	अगर (!td)
		वापस -ENOMEM;

	td->pipe = urb->pipe;
	td->ep_data = urbp->ep_data;

	अगर ((td_udev(td)->speed == USB_SPEED_LOW) &&
	    !(c67x00->low_speed_ports & (1 << urbp->port)))
		cmd |= PREAMBLE_EN;

	चयन (usb_pipetype(td->pipe)) अणु
	हाल PIPE_ISOCHRONOUS:
		tt = TT_ISOCHRONOUS;
		cmd |= ISO_EN;
		अवरोध;
	हाल PIPE_CONTROL:
		tt = TT_CONTROL;
		अवरोध;
	हाल PIPE_BULK:
		tt = TT_BULK;
		अवरोध;
	हाल PIPE_INTERRUPT:
		tt = TT_INTERRUPT;
		अवरोध;
	पूर्ण

	अगर (toggle)
		cmd |= SEQ_SEL;

	cmd |= ARM_EN;

	/* SW part */
	td->td_addr = c67x00->next_td_addr;
	c67x00->next_td_addr = c67x00->next_td_addr + CY_TD_SIZE;

	/* HW part */
	td->ly_base_addr = __cpu_to_le16(c67x00->next_buf_addr);
	td->port_length = __cpu_to_le16((c67x00->sie->sie_num << 15) |
					(urbp->port << 14) | (len & 0x3FF));
	td->pid_ep = ((pid & 0xF) << TD_PIDEP_OFFSET) |
	    (usb_pipeendpoपूर्णांक(td->pipe) & 0xF);
	td->dev_addr = usb_pipedevice(td->pipe) & 0x7F;
	td->ctrl_reg = cmd;
	td->status = 0;
	td->retry_cnt = (tt << TT_OFFSET) | (active_flag << 4) | retry_cnt;
	td->residue = 0;
	td->next_td_addr = __cpu_to_le16(c67x00->next_td_addr);

	/* SW part */
	td->data = data;
	td->urb = urb;
	td->privdata = privdata;

	c67x00->next_buf_addr += (len + 1) & ~0x01;	/* properly align */

	list_add_tail(&td->td_list, &c67x00->td_list);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम c67x00_release_td(काष्ठा c67x00_td *td)
अणु
	list_del_init(&td->td_list);
	kमुक्त(td);
पूर्ण

/* -------------------------------------------------------------------------- */

अटल पूर्णांक c67x00_add_data_urb(काष्ठा c67x00_hcd *c67x00, काष्ठा urb *urb)
अणु
	पूर्णांक reमुख्यing;
	पूर्णांक toggle;
	पूर्णांक pid;
	पूर्णांक ret = 0;
	पूर्णांक maxps;
	पूर्णांक need_empty;

	toggle = usb_gettoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
			       usb_pipeout(urb->pipe));
	reमुख्यing = urb->transfer_buffer_length - urb->actual_length;

	maxps = usb_maxpacket(urb->dev, urb->pipe, usb_pipeout(urb->pipe));

	need_empty = (urb->transfer_flags & URB_ZERO_PACKET) &&
	    usb_pipeout(urb->pipe) && !(reमुख्यing % maxps);

	जबतक (reमुख्यing || need_empty) अणु
		पूर्णांक len;
		अक्षर *td_buf;

		len = (reमुख्यing > maxps) ? maxps : reमुख्यing;
		अगर (!len)
			need_empty = 0;

		pid = usb_pipeout(urb->pipe) ? USB_PID_OUT : USB_PID_IN;
		td_buf = urb->transfer_buffer + urb->transfer_buffer_length -
		    reमुख्यing;
		ret = c67x00_create_td(c67x00, urb, td_buf, len, pid, toggle,
				       DATA_STAGE);
		अगर (ret)
			वापस ret;	/* td wasn't created */

		toggle ^= 1;
		reमुख्यing -= len;
		अगर (usb_pipecontrol(urb->pipe))
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * वापस 0 in हाल more bandwidth is available, अन्यथा errorcode
 */
अटल पूर्णांक c67x00_add_ctrl_urb(काष्ठा c67x00_hcd *c67x00, काष्ठा urb *urb)
अणु
	पूर्णांक ret;
	पूर्णांक pid;

	चयन (urb->पूर्णांकerval) अणु
	शेष:
	हाल SETUP_STAGE:
		ret = c67x00_create_td(c67x00, urb, urb->setup_packet,
				       8, USB_PID_SETUP, 0, SETUP_STAGE);
		अगर (ret)
			वापस ret;
		urb->पूर्णांकerval = SETUP_STAGE;
		usb_settoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
			      usb_pipeout(urb->pipe), 1);
		अवरोध;
	हाल DATA_STAGE:
		अगर (urb->transfer_buffer_length) अणु
			ret = c67x00_add_data_urb(c67x00, urb);
			अगर (ret)
				वापस ret;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल STATUS_STAGE:
		pid = !usb_pipeout(urb->pipe) ? USB_PID_OUT : USB_PID_IN;
		ret = c67x00_create_td(c67x00, urb, शून्य, 0, pid, 1,
				       STATUS_STAGE);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * वापस 0 in हाल more bandwidth is available, अन्यथा errorcode
 */
अटल पूर्णांक c67x00_add_पूर्णांक_urb(काष्ठा c67x00_hcd *c67x00, काष्ठा urb *urb)
अणु
	काष्ठा c67x00_urb_priv *urbp = urb->hcpriv;

	अगर (frame_after_eq(c67x00->current_frame, urbp->ep_data->next_frame)) अणु
		urbp->ep_data->next_frame =
		    frame_add(urbp->ep_data->next_frame, urb->पूर्णांकerval);
		वापस c67x00_add_data_urb(c67x00, urb);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक c67x00_add_iso_urb(काष्ठा c67x00_hcd *c67x00, काष्ठा urb *urb)
अणु
	काष्ठा c67x00_urb_priv *urbp = urb->hcpriv;

	अगर (frame_after_eq(c67x00->current_frame, urbp->ep_data->next_frame)) अणु
		अक्षर *td_buf;
		पूर्णांक len, pid, ret;

		BUG_ON(urbp->cnt >= urb->number_of_packets);

		td_buf = urb->transfer_buffer +
		    urb->iso_frame_desc[urbp->cnt].offset;
		len = urb->iso_frame_desc[urbp->cnt].length;
		pid = usb_pipeout(urb->pipe) ? USB_PID_OUT : USB_PID_IN;

		ret = c67x00_create_td(c67x00, urb, td_buf, len, pid, 0,
				       urbp->cnt);
		अगर (ret) अणु
			dev_dbg(c67x00_hcd_dev(c67x00), "create failed: %d\n",
				ret);
			urb->iso_frame_desc[urbp->cnt].actual_length = 0;
			urb->iso_frame_desc[urbp->cnt].status = ret;
			अगर (urbp->cnt + 1 == urb->number_of_packets)
				c67x00_giveback_urb(c67x00, urb, 0);
		पूर्ण

		urbp->ep_data->next_frame =
		    frame_add(urbp->ep_data->next_frame, urb->पूर्णांकerval);
		urbp->cnt++;
	पूर्ण
	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */

अटल व्योम c67x00_fill_from_list(काष्ठा c67x00_hcd *c67x00, पूर्णांक type,
				  पूर्णांक (*add)(काष्ठा c67x00_hcd *, काष्ठा urb *))
अणु
	काष्ठा c67x00_ep_data *ep_data;
	काष्ठा urb *urb;

	/* traverse every endpoपूर्णांक on the list */
	list_क्रम_each_entry(ep_data, &c67x00->list[type], node) अणु
		अगर (!list_empty(&ep_data->queue)) अणु
			/* and add the first urb */
			/* isochronous transfer rely on this */
			urb = list_entry(ep_data->queue.next,
					 काष्ठा c67x00_urb_priv,
					 hep_node)->urb;
			add(c67x00, urb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम c67x00_fill_frame(काष्ठा c67x00_hcd *c67x00)
अणु
	काष्ठा c67x00_td *td, *ttd;

	/* Check अगर we can proceed */
	अगर (!list_empty(&c67x00->td_list)) अणु
		dev_warn(c67x00_hcd_dev(c67x00),
			 "TD list not empty! This should not happen!\n");
		list_क्रम_each_entry_safe(td, ttd, &c67x00->td_list, td_list) अणु
			dbg_td(c67x00, td, "Unprocessed td");
			c67x00_release_td(td);
		पूर्ण
	पूर्ण

	/* Reinitialize variables */
	c67x00->bandwidth_allocated = 0;
	c67x00->periodic_bw_allocated = 0;

	c67x00->next_td_addr = c67x00->td_base_addr;
	c67x00->next_buf_addr = c67x00->buf_base_addr;

	/* Fill the list */
	c67x00_fill_from_list(c67x00, PIPE_ISOCHRONOUS, c67x00_add_iso_urb);
	c67x00_fill_from_list(c67x00, PIPE_INTERRUPT, c67x00_add_पूर्णांक_urb);
	c67x00_fill_from_list(c67x00, PIPE_CONTROL, c67x00_add_ctrl_urb);
	c67x00_fill_from_list(c67x00, PIPE_BULK, c67x00_add_data_urb);
पूर्ण

/* -------------------------------------------------------------------------- */

/*
 * Get TD from C67X00
 */
अटल अंतरभूत व्योम
c67x00_parse_td(काष्ठा c67x00_hcd *c67x00, काष्ठा c67x00_td *td)
अणु
	c67x00_ll_पढ़ो_mem_le16(c67x00->sie->dev,
				td->td_addr, td, CY_TD_SIZE);

	अगर (usb_pipein(td->pipe) && td_actual_bytes(td))
		c67x00_ll_पढ़ो_mem_le16(c67x00->sie->dev, td_ly_base_addr(td),
					td->data, td_actual_bytes(td));
पूर्ण

अटल पूर्णांक c67x00_td_to_error(काष्ठा c67x00_hcd *c67x00, काष्ठा c67x00_td *td)
अणु
	अगर (td->status & TD_STATUSMASK_ERR) अणु
		dbg_td(c67x00, td, "ERROR_FLAG");
		वापस -EILSEQ;
	पूर्ण
	अगर (td->status & TD_STATUSMASK_STALL) अणु
		/* dbg_td(c67x00, td, "STALL"); */
		वापस -EPIPE;
	पूर्ण
	अगर (td->status & TD_STATUSMASK_TMOUT) अणु
		dbg_td(c67x00, td, "TIMEOUT");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक c67x00_end_of_data(काष्ठा c67x00_td *td)
अणु
	पूर्णांक maxps, need_empty, reमुख्यing;
	काष्ठा urb *urb = td->urb;
	पूर्णांक act_bytes;

	act_bytes = td_actual_bytes(td);

	अगर (unlikely(!act_bytes))
		वापस 1;	/* This was an empty packet */

	maxps = usb_maxpacket(td_udev(td), td->pipe, usb_pipeout(td->pipe));

	अगर (unlikely(act_bytes < maxps))
		वापस 1;	/* Smaller then full packet */

	reमुख्यing = urb->transfer_buffer_length - urb->actual_length;
	need_empty = (urb->transfer_flags & URB_ZERO_PACKET) &&
	    usb_pipeout(urb->pipe) && !(reमुख्यing % maxps);

	अगर (unlikely(!reमुख्यing && !need_empty))
		वापस 1;

	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */

/* Remove all td's from the list which come
 * after last_td and are meant क्रम the same pipe.
 * This is used when a लघु packet has occurred */
अटल अंतरभूत व्योम c67x00_clear_pipe(काष्ठा c67x00_hcd *c67x00,
				     काष्ठा c67x00_td *last_td)
अणु
	काष्ठा c67x00_td *td, *पंचांगp;
	td = last_td;
	पंचांगp = last_td;
	जबतक (td->td_list.next != &c67x00->td_list) अणु
		td = list_entry(td->td_list.next, काष्ठा c67x00_td, td_list);
		अगर (td->pipe == last_td->pipe) अणु
			c67x00_release_td(td);
			td = पंचांगp;
		पूर्ण
		पंचांगp = td;
	पूर्ण
पूर्ण

/* -------------------------------------------------------------------------- */

अटल व्योम c67x00_handle_successful_td(काष्ठा c67x00_hcd *c67x00,
					काष्ठा c67x00_td *td)
अणु
	काष्ठा urb *urb = td->urb;

	अगर (!urb)
		वापस;

	urb->actual_length += td_actual_bytes(td);

	चयन (usb_pipetype(td->pipe)) अणु
		/* isochronous tds are handled separately */
	हाल PIPE_CONTROL:
		चयन (td->privdata) अणु
		हाल SETUP_STAGE:
			urb->पूर्णांकerval =
			    urb->transfer_buffer_length ?
			    DATA_STAGE : STATUS_STAGE;
			/* Don't count setup_packet with normal data: */
			urb->actual_length = 0;
			अवरोध;

		हाल DATA_STAGE:
			अगर (c67x00_end_of_data(td)) अणु
				urb->पूर्णांकerval = STATUS_STAGE;
				c67x00_clear_pipe(c67x00, td);
			पूर्ण
			अवरोध;

		हाल STATUS_STAGE:
			urb->पूर्णांकerval = 0;
			c67x00_giveback_urb(c67x00, urb, 0);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल PIPE_INTERRUPT:
	हाल PIPE_BULK:
		अगर (unlikely(c67x00_end_of_data(td))) अणु
			c67x00_clear_pipe(c67x00, td);
			c67x00_giveback_urb(c67x00, urb, 0);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम c67x00_handle_isoc(काष्ठा c67x00_hcd *c67x00, काष्ठा c67x00_td *td)
अणु
	काष्ठा urb *urb = td->urb;
	पूर्णांक cnt;

	अगर (!urb)
		वापस;

	cnt = td->privdata;

	अगर (td->status & TD_ERROR_MASK)
		urb->error_count++;

	urb->iso_frame_desc[cnt].actual_length = td_actual_bytes(td);
	urb->iso_frame_desc[cnt].status = c67x00_td_to_error(c67x00, td);
	अगर (cnt + 1 == urb->number_of_packets)	/* Last packet */
		c67x00_giveback_urb(c67x00, urb, 0);
पूर्ण

/* -------------------------------------------------------------------------- */

/*
 * c67x00_check_td_list - handle tds which have been processed by the c67x00
 * pre: current_td == 0
 */
अटल अंतरभूत व्योम c67x00_check_td_list(काष्ठा c67x00_hcd *c67x00)
अणु
	काष्ठा c67x00_td *td, *पंचांगp;
	काष्ठा urb *urb;
	पूर्णांक ack_ok;
	पूर्णांक clear_endpoपूर्णांक;

	list_क्रम_each_entry_safe(td, पंचांगp, &c67x00->td_list, td_list) अणु
		/* get the TD */
		c67x00_parse_td(c67x00, td);
		urb = td->urb;	/* urb can be शून्य! */
		ack_ok = 0;
		clear_endpoपूर्णांक = 1;

		/* Handle isochronous transfers separately */
		अगर (usb_pipeisoc(td->pipe)) अणु
			clear_endpoपूर्णांक = 0;
			c67x00_handle_isoc(c67x00, td);
			जाओ cont;
		पूर्ण

		/* When an error occurs, all td's क्रम that pipe go पूर्णांकo an
		 * inactive state. This state matches successful transfers so
		 * we must make sure not to service them. */
		अगर (td->status & TD_ERROR_MASK) अणु
			c67x00_giveback_urb(c67x00, urb,
					    c67x00_td_to_error(c67x00, td));
			जाओ cont;
		पूर्ण

		अगर ((td->status & TD_STATUSMASK_NAK) || !td_sequence_ok(td) ||
		    !td_acked(td))
			जाओ cont;

		/* Sequence ok and acked, करोn't need to fix toggle */
		ack_ok = 1;

		अगर (unlikely(td->status & TD_STATUSMASK_OVF)) अणु
			अगर (td_residue(td) & TD_RESIDUE_OVERFLOW) अणु
				/* Overflow */
				c67x00_giveback_urb(c67x00, urb, -EOVERFLOW);
				जाओ cont;
			पूर्ण
		पूर्ण

		clear_endpoपूर्णांक = 0;
		c67x00_handle_successful_td(c67x00, td);

cont:
		अगर (clear_endpoपूर्णांक)
			c67x00_clear_pipe(c67x00, td);
		अगर (ack_ok)
			usb_settoggle(td_udev(td), usb_pipeendpoपूर्णांक(td->pipe),
				      usb_pipeout(td->pipe),
				      !(td->ctrl_reg & SEQ_SEL));
		/* next in list could have been हटाओd, due to clear_pipe! */
		पंचांगp = list_entry(td->td_list.next, typeof(*td), td_list);
		c67x00_release_td(td);
	पूर्ण
पूर्ण

/* -------------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक c67x00_all_tds_processed(काष्ठा c67x00_hcd *c67x00)
अणु
	/* If all tds are processed, we can check the previous frame (अगर
	 * there was any) and start our next frame.
	 */
	वापस !c67x00_ll_husb_get_current_td(c67x00->sie);
पूर्ण

/*
 * Send td to C67X00
 */
अटल व्योम c67x00_send_td(काष्ठा c67x00_hcd *c67x00, काष्ठा c67x00_td *td)
अणु
	पूर्णांक len = td_length(td);

	अगर (len && ((td->pid_ep & TD_PIDEPMASK_PID) != TD_PID_IN))
		c67x00_ll_ग_लिखो_mem_le16(c67x00->sie->dev, td_ly_base_addr(td),
					 td->data, len);

	c67x00_ll_ग_लिखो_mem_le16(c67x00->sie->dev,
				 td->td_addr, td, CY_TD_SIZE);
पूर्ण

अटल व्योम c67x00_send_frame(काष्ठा c67x00_hcd *c67x00)
अणु
	काष्ठा c67x00_td *td;

	अगर (list_empty(&c67x00->td_list))
		dev_warn(c67x00_hcd_dev(c67x00),
			 "%s: td list should not be empty here!\n",
			 __func__);

	list_क्रम_each_entry(td, &c67x00->td_list, td_list) अणु
		अगर (td->td_list.next == &c67x00->td_list)
			td->next_td_addr = 0;	/* Last td in list */

		c67x00_send_td(c67x00, td);
	पूर्ण

	c67x00_ll_husb_set_current_td(c67x00->sie, c67x00->td_base_addr);
पूर्ण

/* -------------------------------------------------------------------------- */

/*
 * c67x00_करो_work - Schedulers state machine
 */
अटल व्योम c67x00_करो_work(काष्ठा c67x00_hcd *c67x00)
अणु
	spin_lock(&c67x00->lock);
	/* Make sure all tds are processed */
	अगर (!c67x00_all_tds_processed(c67x00))
		जाओ out;

	c67x00_check_td_list(c67x00);

	/* no td's are being processed (current == 0)
	 * and all have been "checked" */
	complete(&c67x00->endpoपूर्णांक_disable);

	अगर (!list_empty(&c67x00->td_list))
		जाओ out;

	c67x00->current_frame = c67x00_get_current_frame_number(c67x00);
	अगर (c67x00->current_frame == c67x00->last_frame)
		जाओ out;	/* Don't send tds in same frame */
	c67x00->last_frame = c67x00->current_frame;

	/* If no urbs are scheduled, our work is करोne */
	अगर (!c67x00->urb_count) अणु
		c67x00_ll_hpi_disable_sofeop(c67x00->sie);
		जाओ out;
	पूर्ण

	c67x00_fill_frame(c67x00);
	अगर (!list_empty(&c67x00->td_list))
		/* TD's have been added to the frame */
		c67x00_send_frame(c67x00);

 out:
	spin_unlock(&c67x00->lock);
पूर्ण

/* -------------------------------------------------------------------------- */

अटल व्योम c67x00_sched_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा c67x00_hcd *c67x00;

	c67x00 = container_of(work, काष्ठा c67x00_hcd, work);
	c67x00_करो_work(c67x00);
पूर्ण

व्योम c67x00_sched_kick(काष्ठा c67x00_hcd *c67x00)
अणु
	queue_work(प्रणाली_highpri_wq, &c67x00->work);
पूर्ण

पूर्णांक c67x00_sched_start_scheduler(काष्ठा c67x00_hcd *c67x00)
अणु
	INIT_WORK(&c67x00->work, c67x00_sched_work);
	वापस 0;
पूर्ण

व्योम c67x00_sched_stop_scheduler(काष्ठा c67x00_hcd *c67x00)
अणु
	cancel_work_sync(&c67x00->work);
पूर्ण
