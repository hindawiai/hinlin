<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SL811HS HCD (Host Controller Driver) क्रम USB.
 *
 * Copyright (C) 2004 Psion Teklogix (क्रम NetBook PRO)
 * Copyright (C) 2004-2005 David Brownell
 *
 * Periodic scheduling is based on Roman's OHCI code
 * 	Copyright (C) 1999 Roman Weissgaerber
 *
 * The SL811HS controller handles host side USB (like the SL11H, but with
 * another रेजिस्टर set and SOF generation) as well as peripheral side USB
 * (like the SL811S).  This driver version करोesn't implement the Gadget API
 * क्रम the peripheral role; or OTG (that'd need much बाह्यal circuitry).
 *
 * For करोcumentation, see the SL811HS spec and the "SL811HS Embedded Host"
 * करोcument (providing signअगरicant pieces missing from that spec); plus
 * the SL811S spec अगर you want peripheral side info.
 */

/*
 * Status:  Passed basic stress testing, works with hubs, mice, keyboards,
 * and usb-storage.
 *
 * TODO:
 * - usb suspend/resume triggered by sl811
 * - various issues noted in the code
 * - perक्रमmance work; use both रेजिस्टर banks; ...
 * - use urb->iso_frame_desc[] with ISO transfers
 */

#अघोषित	VERBOSE
#अघोषित	PACKET_TRACE

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/sl811.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "sl811.h"


MODULE_DESCRIPTION("SL811HS USB Host Controller Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sl811-hcd");

#घोषणा DRIVER_VERSION	"19 May 2005"

/* क्रम now, use only one transfer रेजिस्टर bank */
#अघोषित	USE_B

// #घोषणा	QUIRK2
#घोषणा	QUIRK3

अटल स्थिर अक्षर hcd_name[] = "sl811-hcd";

/*-------------------------------------------------------------------------*/

अटल व्योम port_घातer(काष्ठा sl811 *sl811, पूर्णांक is_on)
अणु
	काष्ठा usb_hcd	*hcd = sl811_to_hcd(sl811);

	/* hub is inactive unless the port is घातered */
	अगर (is_on) अणु
		अगर (sl811->port1 & USB_PORT_STAT_POWER)
			वापस;

		sl811->port1 = USB_PORT_STAT_POWER;
		sl811->irq_enable = SL11H_INTMASK_INSRMV;
	पूर्ण अन्यथा अणु
		sl811->port1 = 0;
		sl811->irq_enable = 0;
		hcd->state = HC_STATE_HALT;
	पूर्ण
	sl811->ctrl1 = 0;
	sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE, 0);
	sl811_ग_लिखो(sl811, SL11H_IRQ_STATUS, ~0);

	अगर (sl811->board && sl811->board->port_घातer) अणु
		/* चयन VBUS, at 500mA unless hub घातer budget माला_लो set */
		dev_dbg(hcd->self.controller, "power %s\n",
			is_on ? "on" : "off");
		sl811->board->port_घातer(hcd->self.controller, is_on);
	पूर्ण

	/* reset as thoroughly as we can */
	अगर (sl811->board && sl811->board->reset)
		sl811->board->reset(hcd->self.controller);
	अन्यथा अणु
		sl811_ग_लिखो(sl811, SL11H_CTLREG1, SL11H_CTL1MASK_SE0);
		mdelay(20);
	पूर्ण

	sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE, 0);
	sl811_ग_लिखो(sl811, SL11H_CTLREG1, sl811->ctrl1);
	sl811_ग_लिखो(sl811, SL811HS_CTLREG2, SL811HS_CTL2_INIT);
	sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE, sl811->irq_enable);

	// अगर !is_on, put पूर्णांकo lowघातer mode now
पूर्ण

/*-------------------------------------------------------------------------*/

/* This is a PIO-only HCD.  Queueing appends URBs to the endpoपूर्णांक's queue,
 * and may start I/O.  Endpoपूर्णांक queues are scanned during completion irq
 * handlers (one per packet: ACK, NAK, faults, etc) and urb cancellation.
 *
 * Using an बाह्यal DMA engine to copy a packet at a समय could work,
 * though setup/tearकरोwn costs may be too big to make it worthजबतक.
 */

/* SETUP starts a new control request.  Devices are not allowed to
 * STALL or NAK these; they must cancel any pending control requests.
 */
अटल व्योम setup_packet(
	काष्ठा sl811		*sl811,
	काष्ठा sl811h_ep	*ep,
	काष्ठा urb		*urb,
	u8			bank,
	u8			control
)
अणु
	u8			addr;
	u8			len;
	व्योम __iomem		*data_reg;

	addr = SL811HS_PACKET_BUF(bank == 0);
	len = माप(काष्ठा usb_ctrlrequest);
	data_reg = sl811->data_reg;
	sl811_ग_लिखो_buf(sl811, addr, urb->setup_packet, len);

	/* स्वतःincrementing */
	sl811_ग_लिखो(sl811, bank + SL11H_BUFADDRREG, addr);
	ग_लिखोb(len, data_reg);
	ग_लिखोb(SL_SETUP /* | ep->epnum */, data_reg);
	ग_लिखोb(usb_pipedevice(urb->pipe), data_reg);

	/* always OUT/data0 */
	sl811_ग_लिखो(sl811, bank + SL11H_HOSTCTLREG,
			control | SL11H_HCTLMASK_OUT);
	ep->length = 0;
	PACKET("SETUP qh%p\n", ep);
पूर्ण

/* STATUS finishes control requests, often after IN or OUT data packets */
अटल व्योम status_packet(
	काष्ठा sl811		*sl811,
	काष्ठा sl811h_ep	*ep,
	काष्ठा urb		*urb,
	u8			bank,
	u8			control
)
अणु
	पूर्णांक			करो_out;
	व्योम __iomem		*data_reg;

	करो_out = urb->transfer_buffer_length && usb_pipein(urb->pipe);
	data_reg = sl811->data_reg;

	/* स्वतःincrementing */
	sl811_ग_लिखो(sl811, bank + SL11H_BUFADDRREG, 0);
	ग_लिखोb(0, data_reg);
	ग_लिखोb((करो_out ? SL_OUT : SL_IN) /* | ep->epnum */, data_reg);
	ग_लिखोb(usb_pipedevice(urb->pipe), data_reg);

	/* always data1; someबार IN */
	control |= SL11H_HCTLMASK_TOGGLE;
	अगर (करो_out)
		control |= SL11H_HCTLMASK_OUT;
	sl811_ग_लिखो(sl811, bank + SL11H_HOSTCTLREG, control);
	ep->length = 0;
	PACKET("STATUS%s/%s qh%p\n", ep->nak_count ? "/retry" : "",
			करो_out ? "out" : "in", ep);
पूर्ण

/* IN packets can be used with any type of endpoपूर्णांक. here we just
 * start the transfer, data from the peripheral may arrive later.
 * urb->iso_frame_desc is currently ignored here...
 */
अटल व्योम in_packet(
	काष्ठा sl811		*sl811,
	काष्ठा sl811h_ep	*ep,
	काष्ठा urb		*urb,
	u8			bank,
	u8			control
)
अणु
	u8			addr;
	u8			len;
	व्योम __iomem		*data_reg;

	/* aव्योम losing data on overflow */
	len = ep->maxpacket;
	addr = SL811HS_PACKET_BUF(bank == 0);
	अगर (!(control & SL11H_HCTLMASK_ISOCH)
			&& usb_gettoggle(urb->dev, ep->epnum, 0))
		control |= SL11H_HCTLMASK_TOGGLE;
	data_reg = sl811->data_reg;

	/* स्वतःincrementing */
	sl811_ग_लिखो(sl811, bank + SL11H_BUFADDRREG, addr);
	ग_लिखोb(len, data_reg);
	ग_लिखोb(SL_IN | ep->epnum, data_reg);
	ग_लिखोb(usb_pipedevice(urb->pipe), data_reg);

	sl811_ग_लिखो(sl811, bank + SL11H_HOSTCTLREG, control);
	ep->length = min_t(u32, len,
			urb->transfer_buffer_length - urb->actual_length);
	PACKET("IN%s/%d qh%p len%d\n", ep->nak_count ? "/retry" : "",
			!!usb_gettoggle(urb->dev, ep->epnum, 0), ep, len);
पूर्ण

/* OUT packets can be used with any type of endpoपूर्णांक.
 * urb->iso_frame_desc is currently ignored here...
 */
अटल व्योम out_packet(
	काष्ठा sl811		*sl811,
	काष्ठा sl811h_ep	*ep,
	काष्ठा urb		*urb,
	u8			bank,
	u8			control
)
अणु
	व्योम			*buf;
	u8			addr;
	u8			len;
	व्योम __iomem		*data_reg;

	buf = urb->transfer_buffer + urb->actual_length;
	prefetch(buf);

	len = min_t(u32, ep->maxpacket,
			urb->transfer_buffer_length - urb->actual_length);

	अगर (!(control & SL11H_HCTLMASK_ISOCH)
			&& usb_gettoggle(urb->dev, ep->epnum, 1))
		control |= SL11H_HCTLMASK_TOGGLE;
	addr = SL811HS_PACKET_BUF(bank == 0);
	data_reg = sl811->data_reg;

	sl811_ग_लिखो_buf(sl811, addr, buf, len);

	/* स्वतःincrementing */
	sl811_ग_लिखो(sl811, bank + SL11H_BUFADDRREG, addr);
	ग_लिखोb(len, data_reg);
	ग_लिखोb(SL_OUT | ep->epnum, data_reg);
	ग_लिखोb(usb_pipedevice(urb->pipe), data_reg);

	sl811_ग_लिखो(sl811, bank + SL11H_HOSTCTLREG,
			control | SL11H_HCTLMASK_OUT);
	ep->length = len;
	PACKET("OUT%s/%d qh%p len%d\n", ep->nak_count ? "/retry" : "",
			!!usb_gettoggle(urb->dev, ep->epnum, 1), ep, len);
पूर्ण

/*-------------------------------------------------------------------------*/

/* caller updates on-chip enables later */

अटल अंतरभूत व्योम sofirq_on(काष्ठा sl811 *sl811)
अणु
	अगर (sl811->irq_enable & SL11H_INTMASK_SOFINTR)
		वापस;
	dev_dbg(sl811_to_hcd(sl811)->self.controller, "sof irq on\n");
	sl811->irq_enable |= SL11H_INTMASK_SOFINTR;
पूर्ण

अटल अंतरभूत व्योम sofirq_off(काष्ठा sl811 *sl811)
अणु
	अगर (!(sl811->irq_enable & SL11H_INTMASK_SOFINTR))
		वापस;
	dev_dbg(sl811_to_hcd(sl811)->self.controller, "sof irq off\n");
	sl811->irq_enable &= ~SL11H_INTMASK_SOFINTR;
पूर्ण

/*-------------------------------------------------------------------------*/

/* pick the next endpoपूर्णांक क्रम a transaction, and issue it.
 * frames start with periodic transfers (after whatever is pending
 * from the previous frame), and the rest of the समय is async
 * transfers, scheduled round-robin.
 */
अटल काष्ठा sl811h_ep	*start(काष्ठा sl811 *sl811, u8 bank)
अणु
	काष्ठा sl811h_ep	*ep;
	काष्ठा urb		*urb;
	पूर्णांक			fघड़ी;
	u8			control;

	/* use endpoपूर्णांक at schedule head */
	अगर (sl811->next_periodic) अणु
		ep = sl811->next_periodic;
		sl811->next_periodic = ep->next;
	पूर्ण अन्यथा अणु
		अगर (sl811->next_async)
			ep = sl811->next_async;
		अन्यथा अगर (!list_empty(&sl811->async))
			ep = container_of(sl811->async.next,
					काष्ठा sl811h_ep, schedule);
		अन्यथा अणु
			/* could set up the first fullspeed periodic
			 * transfer क्रम the next frame ...
			 */
			वापस शून्य;
		पूर्ण

#अगर_घोषित USE_B
		अगर ((bank && sl811->active_b == ep) || sl811->active_a == ep)
			वापस शून्य;
#पूर्ण_अगर

		अगर (ep->schedule.next == &sl811->async)
			sl811->next_async = शून्य;
		अन्यथा
			sl811->next_async = container_of(ep->schedule.next,
					काष्ठा sl811h_ep, schedule);
	पूर्ण

	अगर (unlikely(list_empty(&ep->hep->urb_list))) अणु
		dev_dbg(sl811_to_hcd(sl811)->self.controller,
			"empty %p queue?\n", ep);
		वापस शून्य;
	पूर्ण

	urb = container_of(ep->hep->urb_list.next, काष्ठा urb, urb_list);
	control = ep->defctrl;

	/* अगर this frame करोesn't have enough समय left to transfer this
	 * packet, रुको till the next frame.  too-simple algorithm...
	 */
	fघड़ी = sl811_पढ़ो(sl811, SL11H_SOFTMRREG) << 6;
	fघड़ी -= 100;		/* setup takes not much समय */
	अगर (urb->dev->speed == USB_SPEED_LOW) अणु
		अगर (control & SL11H_HCTLMASK_PREAMBLE) अणु
			/* also note erratum 1: some hubs won't work */
			fघड़ी -= 800;
		पूर्ण
		fघड़ी -= ep->maxpacket << 8;

		/* erratum 2: AFTERSOF only works क्रम fullspeed */
		अगर (fघड़ी < 0) अणु
			अगर (ep->period)
				sl811->stat_overrun++;
			sofirq_on(sl811);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		fघड़ी -= 12000 / 19;	/* 19 64byte packets/msec */
		अगर (fघड़ी < 0) अणु
			अगर (ep->period)
				sl811->stat_overrun++;
			control |= SL11H_HCTLMASK_AFTERSOF;

		/* throttle bulk/control irq noise */
		पूर्ण अन्यथा अगर (ep->nak_count)
			control |= SL11H_HCTLMASK_AFTERSOF;
	पूर्ण


	चयन (ep->nextpid) अणु
	हाल USB_PID_IN:
		in_packet(sl811, ep, urb, bank, control);
		अवरोध;
	हाल USB_PID_OUT:
		out_packet(sl811, ep, urb, bank, control);
		अवरोध;
	हाल USB_PID_SETUP:
		setup_packet(sl811, ep, urb, bank, control);
		अवरोध;
	हाल USB_PID_ACK:		/* क्रम control status */
		status_packet(sl811, ep, urb, bank, control);
		अवरोध;
	शेष:
		dev_dbg(sl811_to_hcd(sl811)->self.controller,
			"bad ep%p pid %02x\n", ep, ep->nextpid);
		ep = शून्य;
	पूर्ण
	वापस ep;
पूर्ण

#घोषणा MIN_JIFFIES	((msecs_to_jअगरfies(2) > 1) ? msecs_to_jअगरfies(2) : 2)

अटल अंतरभूत व्योम start_transfer(काष्ठा sl811 *sl811)
अणु
	अगर (sl811->port1 & USB_PORT_STAT_SUSPEND)
		वापस;
	अगर (sl811->active_a == शून्य) अणु
		sl811->active_a = start(sl811, SL811_EP_A(SL811_HOST_BUF));
		अगर (sl811->active_a != शून्य)
			sl811->jअगरfies_a = jअगरfies + MIN_JIFFIES;
	पूर्ण
#अगर_घोषित USE_B
	अगर (sl811->active_b == शून्य) अणु
		sl811->active_b = start(sl811, SL811_EP_B(SL811_HOST_BUF));
		अगर (sl811->active_b != शून्य)
			sl811->jअगरfies_b = jअगरfies + MIN_JIFFIES;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम finish_request(
	काष्ठा sl811		*sl811,
	काष्ठा sl811h_ep	*ep,
	काष्ठा urb		*urb,
	पूर्णांक			status
) __releases(sl811->lock) __acquires(sl811->lock)
अणु
	अचिन्हित		i;

	अगर (usb_pipecontrol(urb->pipe))
		ep->nextpid = USB_PID_SETUP;

	usb_hcd_unlink_urb_from_ep(sl811_to_hcd(sl811), urb);
	spin_unlock(&sl811->lock);
	usb_hcd_giveback_urb(sl811_to_hcd(sl811), urb, status);
	spin_lock(&sl811->lock);

	/* leave active endpoपूर्णांकs in the schedule */
	अगर (!list_empty(&ep->hep->urb_list))
		वापस;

	/* async deschedule? */
	अगर (!list_empty(&ep->schedule)) अणु
		list_del_init(&ep->schedule);
		अगर (ep == sl811->next_async)
			sl811->next_async = शून्य;
		वापस;
	पूर्ण

	/* periodic deschedule */
	dev_dbg(sl811_to_hcd(sl811)->self.controller,
		"deschedule qh%d/%p branch %d\n", ep->period, ep, ep->branch);
	क्रम (i = ep->branch; i < PERIODIC_SIZE; i += ep->period) अणु
		काष्ठा sl811h_ep	*temp;
		काष्ठा sl811h_ep	**prev = &sl811->periodic[i];

		जबतक (*prev && ((temp = *prev) != ep))
			prev = &temp->next;
		अगर (*prev)
			*prev = ep->next;
		sl811->load[i] -= ep->load;
	पूर्ण
	ep->branch = PERIODIC_SIZE;
	sl811->periodic_count--;
	sl811_to_hcd(sl811)->self.bandwidth_allocated
		-= ep->load / ep->period;
	अगर (ep == sl811->next_periodic)
		sl811->next_periodic = ep->next;

	/* we might turn SOFs back on again क्रम the async schedule */
	अगर (sl811->periodic_count == 0)
		sofirq_off(sl811);
पूर्ण

अटल व्योम
करोne(काष्ठा sl811 *sl811, काष्ठा sl811h_ep *ep, u8 bank)
अणु
	u8			status;
	काष्ठा urb		*urb;
	पूर्णांक			urbstat = -EINPROGRESS;

	अगर (unlikely(!ep))
		वापस;

	status = sl811_पढ़ो(sl811, bank + SL11H_PKTSTATREG);

	urb = container_of(ep->hep->urb_list.next, काष्ठा urb, urb_list);

	/* we can safely ignore NAKs */
	अगर (status & SL11H_STATMASK_NAK) अणु
		// PACKET("...NAK_%02x qh%p\n", bank, ep);
		अगर (!ep->period)
			ep->nak_count++;
		ep->error_count = 0;

	/* ACK advances transfer, toggle, and maybe queue */
	पूर्ण अन्यथा अगर (status & SL11H_STATMASK_ACK) अणु
		काष्ठा usb_device	*udev = urb->dev;
		पूर्णांक			len;
		अचिन्हित अक्षर		*buf;

		/* urb->iso_frame_desc is currently ignored here... */

		ep->nak_count = ep->error_count = 0;
		चयन (ep->nextpid) अणु
		हाल USB_PID_OUT:
			// PACKET("...ACK/out_%02x qh%p\n", bank, ep);
			urb->actual_length += ep->length;
			usb_करोtoggle(udev, ep->epnum, 1);
			अगर (urb->actual_length
					== urb->transfer_buffer_length) अणु
				अगर (usb_pipecontrol(urb->pipe))
					ep->nextpid = USB_PID_ACK;

				/* some bulk protocols terminate OUT transfers
				 * by a लघु packet, using ZLPs not padding.
				 */
				अन्यथा अगर (ep->length < ep->maxpacket
						|| !(urb->transfer_flags
							& URB_ZERO_PACKET))
					urbstat = 0;
			पूर्ण
			अवरोध;
		हाल USB_PID_IN:
			// PACKET("...ACK/in_%02x qh%p\n", bank, ep);
			buf = urb->transfer_buffer + urb->actual_length;
			prefetchw(buf);
			len = ep->maxpacket - sl811_पढ़ो(sl811,
						bank + SL11H_XFERCNTREG);
			अगर (len > ep->length) अणु
				len = ep->length;
				urbstat = -EOVERFLOW;
			पूर्ण
			urb->actual_length += len;
			sl811_पढ़ो_buf(sl811, SL811HS_PACKET_BUF(bank == 0),
					buf, len);
			usb_करोtoggle(udev, ep->epnum, 0);
			अगर (urbstat == -EINPROGRESS &&
					(len < ep->maxpacket ||
						urb->actual_length ==
						urb->transfer_buffer_length)) अणु
				अगर (usb_pipecontrol(urb->pipe))
					ep->nextpid = USB_PID_ACK;
				अन्यथा
					urbstat = 0;
			पूर्ण
			अवरोध;
		हाल USB_PID_SETUP:
			// PACKET("...ACK/setup_%02x qh%p\n", bank, ep);
			अगर (urb->transfer_buffer_length == urb->actual_length)
				ep->nextpid = USB_PID_ACK;
			अन्यथा अगर (usb_pipeout(urb->pipe)) अणु
				usb_settoggle(udev, 0, 1, 1);
				ep->nextpid = USB_PID_OUT;
			पूर्ण अन्यथा अणु
				usb_settoggle(udev, 0, 0, 1);
				ep->nextpid = USB_PID_IN;
			पूर्ण
			अवरोध;
		हाल USB_PID_ACK:
			// PACKET("...ACK/status_%02x qh%p\n", bank, ep);
			urbstat = 0;
			अवरोध;
		पूर्ण

	/* STALL stops all transfers */
	पूर्ण अन्यथा अगर (status & SL11H_STATMASK_STALL) अणु
		PACKET("...STALL_%02x qh%p\n", bank, ep);
		ep->nak_count = ep->error_count = 0;
		urbstat = -EPIPE;

	/* error? retry, until "3 strikes" */
	पूर्ण अन्यथा अगर (++ep->error_count >= 3) अणु
		अगर (status & SL11H_STATMASK_TMOUT)
			urbstat = -ETIME;
		अन्यथा अगर (status & SL11H_STATMASK_OVF)
			urbstat = -EOVERFLOW;
		अन्यथा
			urbstat = -EPROTO;
		ep->error_count = 0;
		PACKET("...3STRIKES_%02x %02x qh%p stat %d\n",
				bank, status, ep, urbstat);
	पूर्ण

	अगर (urbstat != -EINPROGRESS || urb->unlinked)
		finish_request(sl811, ep, urb, urbstat);
पूर्ण

अटल अंतरभूत u8 checkकरोne(काष्ठा sl811 *sl811)
अणु
	u8	ctl;
	u8	irqstat = 0;

	अगर (sl811->active_a && समय_beक्रमe_eq(sl811->jअगरfies_a, jअगरfies)) अणु
		ctl = sl811_पढ़ो(sl811, SL811_EP_A(SL11H_HOSTCTLREG));
		अगर (ctl & SL11H_HCTLMASK_ARM)
			sl811_ग_लिखो(sl811, SL811_EP_A(SL11H_HOSTCTLREG), 0);
		dev_dbg(sl811_to_hcd(sl811)->self.controller,
			"%s DONE_A: ctrl %02x sts %02x\n",
			(ctl & SL11H_HCTLMASK_ARM) ? "timeout" : "lost",
			ctl,
			sl811_पढ़ो(sl811, SL811_EP_A(SL11H_PKTSTATREG)));
		irqstat |= SL11H_INTMASK_DONE_A;
	पूर्ण
#अगर_घोषित	USE_B
	अगर (sl811->active_b && समय_beक्रमe_eq(sl811->jअगरfies_b, jअगरfies)) अणु
		ctl = sl811_पढ़ो(sl811, SL811_EP_B(SL11H_HOSTCTLREG));
		अगर (ctl & SL11H_HCTLMASK_ARM)
			sl811_ग_लिखो(sl811, SL811_EP_B(SL11H_HOSTCTLREG), 0);
		dev_dbg(sl811_to_hcd(sl811)->self.controller,
			"%s DONE_B: ctrl %02x sts %02x\n",
			(ctl & SL11H_HCTLMASK_ARM) ? "timeout" : "lost",
			ctl,
			sl811_पढ़ो(sl811, SL811_EP_B(SL11H_PKTSTATREG)));
		irqstat |= SL11H_INTMASK_DONE_A;
	पूर्ण
#पूर्ण_अगर
	वापस irqstat;
पूर्ण

अटल irqवापस_t sl811h_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा sl811	*sl811 = hcd_to_sl811(hcd);
	u8		irqstat;
	irqवापस_t	ret = IRQ_NONE;
	अचिन्हित	retries = 5;

	spin_lock(&sl811->lock);

retry:
	irqstat = sl811_पढ़ो(sl811, SL11H_IRQ_STATUS) & ~SL11H_INTMASK_DP;
	अगर (irqstat) अणु
		sl811_ग_लिखो(sl811, SL11H_IRQ_STATUS, irqstat);
		irqstat &= sl811->irq_enable;
	पूर्ण

#अगर_घोषित	QUIRK2
	/* this may no दीर्घer be necessary ... */
	अगर (irqstat == 0) अणु
		irqstat = checkकरोne(sl811);
		अगर (irqstat)
			sl811->stat_lost++;
	पूर्ण
#पूर्ण_अगर

	/* USB packets, not necessarily handled in the order they're
	 * issued ... that's fine if they're dअगरferent endpoपूर्णांकs.
	 */
	अगर (irqstat & SL11H_INTMASK_DONE_A) अणु
		करोne(sl811, sl811->active_a, SL811_EP_A(SL811_HOST_BUF));
		sl811->active_a = शून्य;
		sl811->stat_a++;
	पूर्ण
#अगर_घोषित USE_B
	अगर (irqstat & SL11H_INTMASK_DONE_B) अणु
		करोne(sl811, sl811->active_b, SL811_EP_B(SL811_HOST_BUF));
		sl811->active_b = शून्य;
		sl811->stat_b++;
	पूर्ण
#पूर्ण_अगर
	अगर (irqstat & SL11H_INTMASK_SOFINTR) अणु
		अचिन्हित index;

		index = sl811->frame++ % (PERIODIC_SIZE - 1);
		sl811->stat_sof++;

		/* be graceful about almost-inevitable periodic schedule
		 * overruns:  जारी the previous frame's transfers अगरf
		 * this one has nothing scheduled.
		 */
		अगर (sl811->next_periodic) अणु
			// dev_err(hcd->self.controller, "overrun to slot %d\n", index);
			sl811->stat_overrun++;
		पूर्ण
		अगर (sl811->periodic[index])
			sl811->next_periodic = sl811->periodic[index];
	पूर्ण

	/* hub_wq manages debouncing and wakeup */
	अगर (irqstat & SL11H_INTMASK_INSRMV) अणु
		sl811->stat_insrmv++;

		/* most stats are reset क्रम each VBUS session */
		sl811->stat_wake = 0;
		sl811->stat_sof = 0;
		sl811->stat_a = 0;
		sl811->stat_b = 0;
		sl811->stat_lost = 0;

		sl811->ctrl1 = 0;
		sl811_ग_लिखो(sl811, SL11H_CTLREG1, sl811->ctrl1);

		sl811->irq_enable = SL11H_INTMASK_INSRMV;
		sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE, sl811->irq_enable);

		/* usbcore nukes other pending transactions on disconnect */
		अगर (sl811->active_a) अणु
			sl811_ग_लिखो(sl811, SL811_EP_A(SL11H_HOSTCTLREG), 0);
			finish_request(sl811, sl811->active_a,
				container_of(sl811->active_a
						->hep->urb_list.next,
					काष्ठा urb, urb_list),
				-ESHUTDOWN);
			sl811->active_a = शून्य;
		पूर्ण
#अगर_घोषित	USE_B
		अगर (sl811->active_b) अणु
			sl811_ग_लिखो(sl811, SL811_EP_B(SL11H_HOSTCTLREG), 0);
			finish_request(sl811, sl811->active_b,
				container_of(sl811->active_b
						->hep->urb_list.next,
					काष्ठा urb, urb_list),
				शून्य, -ESHUTDOWN);
			sl811->active_b = शून्य;
		पूर्ण
#पूर्ण_अगर

		/* port status seems weird until after reset, so
		 * क्रमce the reset and make hub_wq clean up later.
		 */
		अगर (irqstat & SL11H_INTMASK_RD)
			sl811->port1 &= ~USB_PORT_STAT_CONNECTION;
		अन्यथा
			sl811->port1 |= USB_PORT_STAT_CONNECTION;

		sl811->port1 |= USB_PORT_STAT_C_CONNECTION << 16;

	पूर्ण अन्यथा अगर (irqstat & SL11H_INTMASK_RD) अणु
		अगर (sl811->port1 & USB_PORT_STAT_SUSPEND) अणु
			dev_dbg(hcd->self.controller, "wakeup\n");
			sl811->port1 |= USB_PORT_STAT_C_SUSPEND << 16;
			sl811->stat_wake++;
		पूर्ण अन्यथा
			irqstat &= ~SL11H_INTMASK_RD;
	पूर्ण

	अगर (irqstat) अणु
		अगर (sl811->port1 & USB_PORT_STAT_ENABLE)
			start_transfer(sl811);
		ret = IRQ_HANDLED;
		अगर (retries--)
			जाओ retry;
	पूर्ण

	अगर (sl811->periodic_count == 0 && list_empty(&sl811->async))
		sofirq_off(sl811);
	sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE, sl811->irq_enable);

	spin_unlock(&sl811->lock);

	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*/

/* usb 1.1 says max 90% of a frame is available क्रम periodic transfers.
 * this driver करोesn't promise that much since it's got to handle an
 * IRQ per packet; irq handling latencies also use up that समय.
 *
 * NOTE:  the periodic schedule is a sparse tree, with the load क्रम
 * each branch minimized.  see fig 3.5 in the OHCI spec क्रम example.
 */
#घोषणा	MAX_PERIODIC_LOAD	500	/* out of 1000 usec */

अटल पूर्णांक balance(काष्ठा sl811 *sl811, u16 period, u16 load)
अणु
	पूर्णांक	i, branch = -ENOSPC;

	/* search क्रम the least loaded schedule branch of that period
	 * which has enough bandwidth left unreserved.
	 */
	क्रम (i = 0; i < period ; i++) अणु
		अगर (branch < 0 || sl811->load[branch] > sl811->load[i]) अणु
			पूर्णांक	j;

			क्रम (j = i; j < PERIODIC_SIZE; j += period) अणु
				अगर ((sl811->load[j] + load)
						> MAX_PERIODIC_LOAD)
					अवरोध;
			पूर्ण
			अगर (j < PERIODIC_SIZE)
				जारी;
			branch = i;
		पूर्ण
	पूर्ण
	वापस branch;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक sl811h_urb_enqueue(
	काष्ठा usb_hcd		*hcd,
	काष्ठा urb		*urb,
	gfp_t			mem_flags
) अणु
	काष्ठा sl811		*sl811 = hcd_to_sl811(hcd);
	काष्ठा usb_device	*udev = urb->dev;
	अचिन्हित पूर्णांक		pipe = urb->pipe;
	पूर्णांक			is_out = !usb_pipein(pipe);
	पूर्णांक			type = usb_pipetype(pipe);
	पूर्णांक			epnum = usb_pipeendpoपूर्णांक(pipe);
	काष्ठा sl811h_ep	*ep = शून्य;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			i;
	पूर्णांक			retval;
	काष्ठा usb_host_endpoपूर्णांक	*hep = urb->ep;

#अगर_अघोषित CONFIG_USB_SL811_HCD_ISO
	अगर (type == PIPE_ISOCHRONOUS)
		वापस -ENOSPC;
#पूर्ण_अगर

	/* aव्योम all allocations within spinlocks */
	अगर (!hep->hcpriv) अणु
		ep = kzalloc(माप *ep, mem_flags);
		अगर (ep == शून्य)
			वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&sl811->lock, flags);

	/* करोn't submit to a dead or disabled port */
	अगर (!(sl811->port1 & USB_PORT_STAT_ENABLE)
			|| !HC_IS_RUNNING(hcd->state)) अणु
		retval = -ENODEV;
		kमुक्त(ep);
		जाओ fail_not_linked;
	पूर्ण
	retval = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (retval) अणु
		kमुक्त(ep);
		जाओ fail_not_linked;
	पूर्ण

	अगर (hep->hcpriv) अणु
		kमुक्त(ep);
		ep = hep->hcpriv;
	पूर्ण अन्यथा अगर (!ep) अणु
		retval = -ENOMEM;
		जाओ fail;

	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&ep->schedule);
		ep->udev = udev;
		ep->epnum = epnum;
		ep->maxpacket = usb_maxpacket(udev, urb->pipe, is_out);
		ep->defctrl = SL11H_HCTLMASK_ARM | SL11H_HCTLMASK_ENABLE;
		usb_settoggle(udev, epnum, is_out, 0);

		अगर (type == PIPE_CONTROL)
			ep->nextpid = USB_PID_SETUP;
		अन्यथा अगर (is_out)
			ep->nextpid = USB_PID_OUT;
		अन्यथा
			ep->nextpid = USB_PID_IN;

		अगर (ep->maxpacket > H_MAXPACKET) अणु
			/* iso packets up to 240 bytes could work... */
			dev_dbg(hcd->self.controller,
				"dev %d ep%d maxpacket %d\n", udev->devnum,
				epnum, ep->maxpacket);
			retval = -EINVAL;
			kमुक्त(ep);
			जाओ fail;
		पूर्ण

		अगर (udev->speed == USB_SPEED_LOW) अणु
			/* send preamble क्रम बाह्यal hub? */
			अगर (!(sl811->ctrl1 & SL11H_CTL1MASK_LSPD))
				ep->defctrl |= SL11H_HCTLMASK_PREAMBLE;
		पूर्ण
		चयन (type) अणु
		हाल PIPE_ISOCHRONOUS:
		हाल PIPE_INTERRUPT:
			अगर (urb->पूर्णांकerval > PERIODIC_SIZE)
				urb->पूर्णांकerval = PERIODIC_SIZE;
			ep->period = urb->पूर्णांकerval;
			ep->branch = PERIODIC_SIZE;
			अगर (type == PIPE_ISOCHRONOUS)
				ep->defctrl |= SL11H_HCTLMASK_ISOCH;
			ep->load = usb_calc_bus_समय(udev->speed, !is_out,
				(type == PIPE_ISOCHRONOUS),
				usb_maxpacket(udev, pipe, is_out))
					/ 1000;
			अवरोध;
		पूर्ण

		ep->hep = hep;
		hep->hcpriv = ep;
	पूर्ण

	/* maybe put endpoपूर्णांक पूर्णांकo schedule */
	चयन (type) अणु
	हाल PIPE_CONTROL:
	हाल PIPE_BULK:
		अगर (list_empty(&ep->schedule))
			list_add_tail(&ep->schedule, &sl811->async);
		अवरोध;
	हाल PIPE_ISOCHRONOUS:
	हाल PIPE_INTERRUPT:
		urb->पूर्णांकerval = ep->period;
		अगर (ep->branch < PERIODIC_SIZE) अणु
			/* NOTE:  the phase is correct here, but the value
			 * needs offsetting by the transfer queue depth.
			 * All current drivers ignore start_frame, so this
			 * is unlikely to ever matter...
			 */
			urb->start_frame = (sl811->frame & (PERIODIC_SIZE - 1))
						+ ep->branch;
			अवरोध;
		पूर्ण

		retval = balance(sl811, ep->period, ep->load);
		अगर (retval < 0)
			जाओ fail;
		ep->branch = retval;
		retval = 0;
		urb->start_frame = (sl811->frame & (PERIODIC_SIZE - 1))
					+ ep->branch;

		/* sort each schedule branch by period (slow beक्रमe fast)
		 * to share the faster parts of the tree without needing
		 * dummy/placeholder nodes
		 */
		dev_dbg(hcd->self.controller, "schedule qh%d/%p branch %d\n",
			ep->period, ep, ep->branch);
		क्रम (i = ep->branch; i < PERIODIC_SIZE; i += ep->period) अणु
			काष्ठा sl811h_ep	**prev = &sl811->periodic[i];
			काष्ठा sl811h_ep	*here = *prev;

			जबतक (here && ep != here) अणु
				अगर (ep->period > here->period)
					अवरोध;
				prev = &here->next;
				here = *prev;
			पूर्ण
			अगर (ep != here) अणु
				ep->next = here;
				*prev = ep;
			पूर्ण
			sl811->load[i] += ep->load;
		पूर्ण
		sl811->periodic_count++;
		hcd->self.bandwidth_allocated += ep->load / ep->period;
		sofirq_on(sl811);
	पूर्ण

	urb->hcpriv = hep;
	start_transfer(sl811);
	sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE, sl811->irq_enable);
fail:
	अगर (retval)
		usb_hcd_unlink_urb_from_ep(hcd, urb);
fail_not_linked:
	spin_unlock_irqrestore(&sl811->lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक sl811h_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा sl811		*sl811 = hcd_to_sl811(hcd);
	काष्ठा usb_host_endpoपूर्णांक *hep;
	अचिन्हित दीर्घ		flags;
	काष्ठा sl811h_ep	*ep;
	पूर्णांक			retval;

	spin_lock_irqsave(&sl811->lock, flags);
	retval = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (retval)
		जाओ fail;

	hep = urb->hcpriv;
	ep = hep->hcpriv;
	अगर (ep) अणु
		/* finish right away अगर this urb can't be active ...
		 * note that some drivers wrongly expect delays
		 */
		अगर (ep->hep->urb_list.next != &urb->urb_list) अणु
			/* not front of queue?  never active */

		/* क्रम active transfers, we expect an IRQ */
		पूर्ण अन्यथा अगर (sl811->active_a == ep) अणु
			अगर (समय_beक्रमe_eq(sl811->jअगरfies_a, jअगरfies)) अणु
				/* happens a lot with lowspeed?? */
				dev_dbg(hcd->self.controller,
					"giveup on DONE_A: ctrl %02x sts %02x\n",
					sl811_पढ़ो(sl811,
						SL811_EP_A(SL11H_HOSTCTLREG)),
					sl811_पढ़ो(sl811,
						SL811_EP_A(SL11H_PKTSTATREG)));
				sl811_ग_लिखो(sl811, SL811_EP_A(SL11H_HOSTCTLREG),
						0);
				sl811->active_a = शून्य;
			पूर्ण अन्यथा
				urb = शून्य;
#अगर_घोषित	USE_B
		पूर्ण अन्यथा अगर (sl811->active_b == ep) अणु
			अगर (समय_beक्रमe_eq(sl811->jअगरfies_a, jअगरfies)) अणु
				/* happens a lot with lowspeed?? */
				dev_dbg(hcd->self.controller,
					"giveup on DONE_B: ctrl %02x sts %02x\n",
					sl811_पढ़ो(sl811,
						SL811_EP_B(SL11H_HOSTCTLREG)),
					sl811_पढ़ो(sl811,
						SL811_EP_B(SL11H_PKTSTATREG)));
				sl811_ग_लिखो(sl811, SL811_EP_B(SL11H_HOSTCTLREG),
						0);
				sl811->active_b = शून्य;
			पूर्ण अन्यथा
				urb = शून्य;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			/* front of queue क्रम inactive endpoपूर्णांक */
		पूर्ण

		अगर (urb)
			finish_request(sl811, ep, urb, 0);
		अन्यथा
			dev_dbg(sl811_to_hcd(sl811)->self.controller,
				"dequeue, urb %p active %s; wait4irq\n", urb,
				(sl811->active_a == ep) ? "A" : "B");
	पूर्ण अन्यथा
		retval = -EINVAL;
 fail:
	spin_unlock_irqrestore(&sl811->lock, flags);
	वापस retval;
पूर्ण

अटल व्योम
sl811h_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd, काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	काष्ठा sl811h_ep	*ep = hep->hcpriv;

	अगर (!ep)
		वापस;

	/* assume we'd just रुको क्रम the irq */
	अगर (!list_empty(&hep->urb_list))
		msleep(3);
	अगर (!list_empty(&hep->urb_list))
		dev_warn(hcd->self.controller, "ep %p not empty?\n", ep);

	kमुक्त(ep);
	hep->hcpriv = शून्य;
पूर्ण

अटल पूर्णांक
sl811h_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा sl811 *sl811 = hcd_to_sl811(hcd);

	/* wrong except जबतक periodic transfers are scheduled;
	 * never matches the on-the-wire frame;
	 * subject to overruns.
	 */
	वापस sl811->frame;
पूर्ण


/*-------------------------------------------------------------------------*/

/* the भव root hub समयr IRQ checks क्रम hub status */
अटल पूर्णांक
sl811h_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा sl811 *sl811 = hcd_to_sl811(hcd);
#अगर_घोषित	QUIRK3
	अचिन्हित दीर्घ flags;

	/* non-SMP HACK: use root hub समयr as i/o watchकरोg
	 * this seems essential when SOF IRQs aren't in use...
	 */
	local_irq_save(flags);
	अगर (!समयr_pending(&sl811->समयr)) अणु
		अगर (sl811h_irq( /* ~0, */ hcd) != IRQ_NONE)
			sl811->stat_lost++;
	पूर्ण
	local_irq_restore(flags);
#पूर्ण_अगर

	अगर (!(sl811->port1 & (0xffff << 16)))
		वापस 0;

	/* tell hub_wq port 1 changed */
	*buf = (1 << 1);
	वापस 1;
पूर्ण

अटल व्योम
sl811h_hub_descriptor (
	काष्ठा sl811			*sl811,
	काष्ठा usb_hub_descriptor	*desc
) अणु
	u16		temp = 0;

	desc->bDescriptorType = USB_DT_HUB;
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = 1;
	desc->bDescLength = 9;

	/* per-port घातer चयनing (gang of one!), or none */
	desc->bPwrOn2PwrGood = 0;
	अगर (sl811->board && sl811->board->port_घातer) अणु
		desc->bPwrOn2PwrGood = sl811->board->potpg;
		अगर (!desc->bPwrOn2PwrGood)
			desc->bPwrOn2PwrGood = 10;
		temp = HUB_CHAR_INDV_PORT_LPSM;
	पूर्ण अन्यथा
		temp = HUB_CHAR_NO_LPSM;

	/* no overcurrent errors detection/handling */
	temp |= HUB_CHAR_NO_OCPM;

	desc->wHubCharacteristics = cpu_to_le16(temp);

	/* ports removable, and legacy PortPwrCtrlMask */
	desc->u.hs.DeviceRemovable[0] = 0 << 1;
	desc->u.hs.DeviceRemovable[1] = ~0;
पूर्ण

अटल व्योम
sl811h_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sl811 	*sl811 = from_समयr(sl811, t, समयr);
	अचिन्हित दीर्घ	flags;
	u8		irqstat;
	u8		संकेतing = sl811->ctrl1 & SL11H_CTL1MASK_FORCE;
	स्थिर u32	mask = USB_PORT_STAT_CONNECTION
				| USB_PORT_STAT_ENABLE
				| USB_PORT_STAT_LOW_SPEED;

	spin_lock_irqsave(&sl811->lock, flags);

	/* stop special संकेतing */
	sl811->ctrl1 &= ~SL11H_CTL1MASK_FORCE;
	sl811_ग_लिखो(sl811, SL11H_CTLREG1, sl811->ctrl1);
	udelay(3);

	irqstat = sl811_पढ़ो(sl811, SL11H_IRQ_STATUS);

	चयन (संकेतing) अणु
	हाल SL11H_CTL1MASK_SE0:
		dev_dbg(sl811_to_hcd(sl811)->self.controller, "end reset\n");
		sl811->port1 = (USB_PORT_STAT_C_RESET << 16)
				 | USB_PORT_STAT_POWER;
		sl811->ctrl1 = 0;
		/* करोn't wrongly ack RD */
		अगर (irqstat & SL11H_INTMASK_INSRMV)
			irqstat &= ~SL11H_INTMASK_RD;
		अवरोध;
	हाल SL11H_CTL1MASK_K:
		dev_dbg(sl811_to_hcd(sl811)->self.controller, "end resume\n");
		sl811->port1 &= ~USB_PORT_STAT_SUSPEND;
		अवरोध;
	शेष:
		dev_dbg(sl811_to_hcd(sl811)->self.controller,
			"odd timer signaling: %02x\n", संकेतing);
		अवरोध;
	पूर्ण
	sl811_ग_लिखो(sl811, SL11H_IRQ_STATUS, irqstat);

	अगर (irqstat & SL11H_INTMASK_RD) अणु
		/* usbcore nukes all pending transactions on disconnect */
		अगर (sl811->port1 & USB_PORT_STAT_CONNECTION)
			sl811->port1 |= (USB_PORT_STAT_C_CONNECTION << 16)
					| (USB_PORT_STAT_C_ENABLE << 16);
		sl811->port1 &= ~mask;
		sl811->irq_enable = SL11H_INTMASK_INSRMV;
	पूर्ण अन्यथा अणु
		sl811->port1 |= mask;
		अगर (irqstat & SL11H_INTMASK_DP)
			sl811->port1 &= ~USB_PORT_STAT_LOW_SPEED;
		sl811->irq_enable = SL11H_INTMASK_INSRMV | SL11H_INTMASK_RD;
	पूर्ण

	अगर (sl811->port1 & USB_PORT_STAT_CONNECTION) अणु
		u8	ctrl2 = SL811HS_CTL2_INIT;

		sl811->irq_enable |= SL11H_INTMASK_DONE_A;
#अगर_घोषित USE_B
		sl811->irq_enable |= SL11H_INTMASK_DONE_B;
#पूर्ण_अगर
		अगर (sl811->port1 & USB_PORT_STAT_LOW_SPEED) अणु
			sl811->ctrl1 |= SL11H_CTL1MASK_LSPD;
			ctrl2 |= SL811HS_CTL2MASK_DSWAP;
		पूर्ण

		/* start SOFs flowing, kickstarting with A रेजिस्टरs */
		sl811->ctrl1 |= SL11H_CTL1MASK_SOF_ENA;
		sl811_ग_लिखो(sl811, SL11H_SOFLOWREG, 0xe0);
		sl811_ग_लिखो(sl811, SL811HS_CTLREG2, ctrl2);

		/* स्वतःincrementing */
		sl811_ग_लिखो(sl811, SL811_EP_A(SL11H_BUFLNTHREG), 0);
		ग_लिखोb(SL_SOF, sl811->data_reg);
		ग_लिखोb(0, sl811->data_reg);
		sl811_ग_लिखो(sl811, SL811_EP_A(SL11H_HOSTCTLREG),
				SL11H_HCTLMASK_ARM);

		/* hub_wq provides debounce delay */
	पूर्ण अन्यथा अणु
		sl811->ctrl1 = 0;
	पूर्ण
	sl811_ग_लिखो(sl811, SL11H_CTLREG1, sl811->ctrl1);

	/* reenable irqs */
	sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE, sl811->irq_enable);
	spin_unlock_irqrestore(&sl811->lock, flags);
पूर्ण

अटल पूर्णांक
sl811h_hub_control(
	काष्ठा usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	अक्षर		*buf,
	u16		wLength
) अणु
	काष्ठा sl811	*sl811 = hcd_to_sl811(hcd);
	पूर्णांक		retval = 0;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&sl811->lock, flags);

	चयन (typeReq) अणु
	हाल ClearHubFeature:
	हाल SetHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
		हाल C_HUB_LOCAL_POWER:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		अगर (wIndex != 1 || wLength != 0)
			जाओ error;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			sl811->port1 &= USB_PORT_STAT_POWER;
			sl811->ctrl1 = 0;
			sl811_ग_लिखो(sl811, SL11H_CTLREG1, sl811->ctrl1);
			sl811->irq_enable = SL11H_INTMASK_INSRMV;
			sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE,
						sl811->irq_enable);
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (!(sl811->port1 & USB_PORT_STAT_SUSPEND))
				अवरोध;

			/* 20 msec of resume/K संकेतing, other irqs blocked */
			dev_dbg(hcd->self.controller, "start resume...\n");
			sl811->irq_enable = 0;
			sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE,
						sl811->irq_enable);
			sl811->ctrl1 |= SL11H_CTL1MASK_K;
			sl811_ग_लिखो(sl811, SL11H_CTLREG1, sl811->ctrl1);

			mod_समयr(&sl811->समयr, jअगरfies
					+ msecs_to_jअगरfies(USB_RESUME_TIMEOUT));
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			port_घातer(sl811, 0);
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
		हाल USB_PORT_FEAT_C_SUSPEND:
		हाल USB_PORT_FEAT_C_CONNECTION:
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
		हाल USB_PORT_FEAT_C_RESET:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		sl811->port1 &= ~(1 << wValue);
		अवरोध;
	हाल GetHubDescriptor:
		sl811h_hub_descriptor(sl811, (काष्ठा usb_hub_descriptor *) buf);
		अवरोध;
	हाल GetHubStatus:
		put_unaligned_le32(0, buf);
		अवरोध;
	हाल GetPortStatus:
		अगर (wIndex != 1)
			जाओ error;
		put_unaligned_le32(sl811->port1, buf);

		अगर (__is_defined(VERBOSE) ||
		    *(u16*)(buf+2)) /* only अगर wPortChange is पूर्णांकeresting */
			dev_dbg(hcd->self.controller, "GetPortStatus %08x\n",
				sl811->port1);
		अवरोध;
	हाल SetPortFeature:
		अगर (wIndex != 1 || wLength != 0)
			जाओ error;
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (sl811->port1 & USB_PORT_STAT_RESET)
				जाओ error;
			अगर (!(sl811->port1 & USB_PORT_STAT_ENABLE))
				जाओ error;

			dev_dbg(hcd->self.controller,"suspend...\n");
			sl811->ctrl1 &= ~SL11H_CTL1MASK_SOF_ENA;
			sl811_ग_लिखो(sl811, SL11H_CTLREG1, sl811->ctrl1);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			port_घातer(sl811, 1);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			अगर (sl811->port1 & USB_PORT_STAT_SUSPEND)
				जाओ error;
			अगर (!(sl811->port1 & USB_PORT_STAT_POWER))
				अवरोध;

			/* 50 msec of reset/SE0 संकेतing, irqs blocked */
			sl811->irq_enable = 0;
			sl811_ग_लिखो(sl811, SL11H_IRQ_ENABLE,
						sl811->irq_enable);
			sl811->ctrl1 = SL11H_CTL1MASK_SE0;
			sl811_ग_लिखो(sl811, SL11H_CTLREG1, sl811->ctrl1);
			sl811->port1 |= USB_PORT_STAT_RESET;
			mod_समयr(&sl811->समयr, jअगरfies
					+ msecs_to_jअगरfies(50));
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		sl811->port1 |= 1 << wValue;
		अवरोध;

	शेष:
error:
		/* "protocol stall" on error */
		retval = -EPIPE;
	पूर्ण

	spin_unlock_irqrestore(&sl811->lock, flags);
	वापस retval;
पूर्ण

#अगर_घोषित	CONFIG_PM

अटल पूर्णांक
sl811h_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	// SOFs off
	dev_dbg(hcd->self.controller, "%s\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक
sl811h_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	// SOFs on
	dev_dbg(hcd->self.controller, "%s\n", __func__);
	वापस 0;
पूर्ण

#अन्यथा

#घोषणा	sl811h_bus_suspend	शून्य
#घोषणा	sl811h_bus_resume	शून्य

#पूर्ण_अगर


/*-------------------------------------------------------------------------*/

अटल व्योम dump_irq(काष्ठा seq_file *s, अक्षर *label, u8 mask)
अणु
	seq_म_लिखो(s, "%s %02x%s%s%s%s%s%s\n", label, mask,
		(mask & SL11H_INTMASK_DONE_A) ? " done_a" : "",
		(mask & SL11H_INTMASK_DONE_B) ? " done_b" : "",
		(mask & SL11H_INTMASK_SOFINTR) ? " sof" : "",
		(mask & SL11H_INTMASK_INSRMV) ? " ins/rmv" : "",
		(mask & SL11H_INTMASK_RD) ? " rd" : "",
		(mask & SL11H_INTMASK_DP) ? " dp" : "");
पूर्ण

अटल पूर्णांक sl811h_debug_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा sl811		*sl811 = s->निजी;
	काष्ठा sl811h_ep	*ep;
	अचिन्हित		i;

	seq_म_लिखो(s, "%s\n%s version %s\nportstatus[1] = %08x\n",
		sl811_to_hcd(sl811)->product_desc,
		hcd_name, DRIVER_VERSION,
		sl811->port1);

	seq_म_लिखो(s, "insert/remove: %ld\n", sl811->stat_insrmv);
	seq_म_लिखो(s, "current session:  done_a %ld done_b %ld "
			"wake %ld sof %ld overrun %ld lost %ld\n\n",
		sl811->stat_a, sl811->stat_b,
		sl811->stat_wake, sl811->stat_sof,
		sl811->stat_overrun, sl811->stat_lost);

	spin_lock_irq(&sl811->lock);

	अगर (sl811->ctrl1 & SL11H_CTL1MASK_SUSPEND)
		seq_म_लिखो(s, "(suspended)\n\n");
	अन्यथा अणु
		u8	t = sl811_पढ़ो(sl811, SL11H_CTLREG1);

		seq_म_लिखो(s, "ctrl1 %02x%s%s%s%s\n", t,
			(t & SL11H_CTL1MASK_SOF_ENA) ? " sofgen" : "",
			(अणुअक्षर *s; चयन (t & SL11H_CTL1MASK_FORCE) अणु
			हाल SL11H_CTL1MASK_NORMAL: s = ""; अवरोध;
			हाल SL11H_CTL1MASK_SE0: s = " se0/reset"; अवरोध;
			हाल SL11H_CTL1MASK_K: s = " k/resume"; अवरोध;
			शेष: s = "j"; अवरोध;
			पूर्ण s; पूर्ण),
			(t & SL11H_CTL1MASK_LSPD) ? " lowspeed" : "",
			(t & SL11H_CTL1MASK_SUSPEND) ? " suspend" : "");

		dump_irq(s, "irq_enable",
				sl811_पढ़ो(sl811, SL11H_IRQ_ENABLE));
		dump_irq(s, "irq_status",
				sl811_पढ़ो(sl811, SL11H_IRQ_STATUS));
		seq_म_लिखो(s, "frame clocks remaining:  %d\n",
				sl811_पढ़ो(sl811, SL11H_SOFTMRREG) << 6);
	पूर्ण

	seq_म_लिखो(s, "A: qh%p ctl %02x sts %02x\n", sl811->active_a,
		sl811_पढ़ो(sl811, SL811_EP_A(SL11H_HOSTCTLREG)),
		sl811_पढ़ो(sl811, SL811_EP_A(SL11H_PKTSTATREG)));
	seq_म_लिखो(s, "B: qh%p ctl %02x sts %02x\n", sl811->active_b,
		sl811_पढ़ो(sl811, SL811_EP_B(SL11H_HOSTCTLREG)),
		sl811_पढ़ो(sl811, SL811_EP_B(SL11H_PKTSTATREG)));
	seq_म_लिखो(s, "\n");
	list_क्रम_each_entry (ep, &sl811->async, schedule) अणु
		काष्ठा urb		*urb;

		seq_म_लिखो(s, "%s%sqh%p, ep%d%s, maxpacket %d"
					" nak %d err %d\n",
			(ep == sl811->active_a) ? "(A) " : "",
			(ep == sl811->active_b) ? "(B) " : "",
			ep, ep->epnum,
			(अणु अक्षर *s; चयन (ep->nextpid) अणु
			हाल USB_PID_IN: s = "in"; अवरोध;
			हाल USB_PID_OUT: s = "out"; अवरोध;
			हाल USB_PID_SETUP: s = "setup"; अवरोध;
			हाल USB_PID_ACK: s = "status"; अवरोध;
			शेष: s = "?"; अवरोध;
			पूर्ण s;पूर्ण),
			ep->maxpacket,
			ep->nak_count, ep->error_count);
		list_क्रम_each_entry (urb, &ep->hep->urb_list, urb_list) अणु
			seq_म_लिखो(s, "  urb%p, %d/%d\n", urb,
				urb->actual_length,
				urb->transfer_buffer_length);
		पूर्ण
	पूर्ण
	अगर (!list_empty(&sl811->async))
		seq_म_लिखो(s, "\n");

	seq_म_लिखो(s, "periodic size= %d\n", PERIODIC_SIZE);

	क्रम (i = 0; i < PERIODIC_SIZE; i++) अणु
		ep = sl811->periodic[i];
		अगर (!ep)
			जारी;
		seq_म_लिखो(s, "%2d [%3d]:\n", i, sl811->load[i]);

		/* DUMB: prपूर्णांकs shared entries multiple बार */
		करो अणु
			seq_म_लिखो(s,
				"   %s%sqh%d/%p (%sdev%d ep%d%s max %d) "
					"err %d\n",
				(ep == sl811->active_a) ? "(A) " : "",
				(ep == sl811->active_b) ? "(B) " : "",
				ep->period, ep,
				(ep->udev->speed == USB_SPEED_FULL)
					? "" : "ls ",
				ep->udev->devnum, ep->epnum,
				(ep->epnum == 0) ? ""
					: ((ep->nextpid == USB_PID_IN)
						? "in"
						: "out"),
				ep->maxpacket, ep->error_count);
			ep = ep->next;
		पूर्ण जबतक (ep);
	पूर्ण

	spin_unlock_irq(&sl811->lock);
	seq_म_लिखो(s, "\n");

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(sl811h_debug);

/* expect just one sl811 per प्रणाली */
अटल व्योम create_debug_file(काष्ठा sl811 *sl811)
अणु
	debugfs_create_file("sl811h", S_IRUGO, usb_debug_root, sl811,
			    &sl811h_debug_fops);
पूर्ण

अटल व्योम हटाओ_debug_file(काष्ठा sl811 *sl811)
अणु
	debugfs_हटाओ(debugfs_lookup("sl811h", usb_debug_root));
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम
sl811h_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा sl811	*sl811 = hcd_to_sl811(hcd);
	अचिन्हित दीर्घ	flags;

	del_समयr_sync(&hcd->rh_समयr);

	spin_lock_irqsave(&sl811->lock, flags);
	port_घातer(sl811, 0);
	spin_unlock_irqrestore(&sl811->lock, flags);
पूर्ण

अटल पूर्णांक
sl811h_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा sl811		*sl811 = hcd_to_sl811(hcd);

	/* chip has been reset, VBUS घातer is off */
	hcd->state = HC_STATE_RUNNING;

	अगर (sl811->board) अणु
		अगर (!device_can_wakeup(hcd->self.controller))
			device_init_wakeup(hcd->self.controller,
				sl811->board->can_wakeup);
		hcd->घातer_budget = sl811->board->घातer * 2;
	पूर्ण

	/* enable घातer and पूर्णांकerrupts */
	port_घातer(sl811, 1);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा hc_driver sl811h_hc_driver = अणु
	.description =		hcd_name,
	.hcd_priv_size =	माप(काष्ठा sl811),

	/*
	 * generic hardware linkage
	 */
	.irq =			sl811h_irq,
	.flags =		HCD_USB11 | HCD_MEMORY,

	/* Basic lअगरecycle operations */
	.start =		sl811h_start,
	.stop =			sl811h_stop,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		sl811h_urb_enqueue,
	.urb_dequeue =		sl811h_urb_dequeue,
	.endpoपूर्णांक_disable =	sl811h_endpoपूर्णांक_disable,

	/*
	 * periodic schedule support
	 */
	.get_frame_number =	sl811h_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data =	sl811h_hub_status_data,
	.hub_control =		sl811h_hub_control,
	.bus_suspend =		sl811h_bus_suspend,
	.bus_resume =		sl811h_bus_resume,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
sl811h_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd		*hcd = platक्रमm_get_drvdata(dev);
	काष्ठा sl811		*sl811 = hcd_to_sl811(hcd);
	काष्ठा resource		*res;

	हटाओ_debug_file(sl811);
	usb_हटाओ_hcd(hcd);

	/* some platक्रमms may use IORESOURCE_IO */
	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);
	अगर (res)
		iounmap(sl811->data_reg);

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (res)
		iounmap(sl811->addr_reg);

	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

अटल पूर्णांक
sl811h_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd		*hcd;
	काष्ठा sl811		*sl811;
	काष्ठा resource		*addr, *data, *ires;
	पूर्णांक			irq;
	व्योम __iomem		*addr_reg;
	व्योम __iomem		*data_reg;
	पूर्णांक			retval;
	u8			पंचांगp, ioaddr;
	अचिन्हित दीर्घ		irqflags;

	अगर (usb_disabled())
		वापस -ENODEV;

	/* the chip may be wired क्रम either kind of addressing */
	addr = platक्रमm_get_mem_or_io(dev, 0);
	data = platक्रमm_get_mem_or_io(dev, 1);
	अगर (!addr || !data || resource_type(addr) != resource_type(data))
		वापस -ENODEV;

	/* basic sanity checks first.  board-specअगरic init logic should
	 * have initialized these three resources and probably board
	 * specअगरic platक्रमm_data.  we करोn't probe क्रम IRQs, and करो only
	 * minimal sanity checking.
	 */
	ires = platक्रमm_get_resource(dev, IORESOURCE_IRQ, 0);
	अगर (dev->num_resources < 3 || !ires)
		वापस -ENODEV;

	irq = ires->start;
	irqflags = ires->flags & IRQF_TRIGGER_MASK;

	ioaddr = resource_type(addr) == IORESOURCE_IO;
	अगर (ioaddr) अणु
		/*
		 * NOTE: 64-bit resource->start is getting truncated
		 * to aव्योम compiler warning, assuming that ->start
		 * is always 32-bit क्रम this हाल
		 */
		addr_reg = (व्योम __iomem *) (अचिन्हित दीर्घ) addr->start;
		data_reg = (व्योम __iomem *) (अचिन्हित दीर्घ) data->start;
	पूर्ण अन्यथा अणु
		addr_reg = ioremap(addr->start, 1);
		अगर (addr_reg == शून्य) अणु
			retval = -ENOMEM;
			जाओ err2;
		पूर्ण

		data_reg = ioremap(data->start, 1);
		अगर (data_reg == शून्य) अणु
			retval = -ENOMEM;
			जाओ err4;
		पूर्ण
	पूर्ण

	/* allocate and initialize hcd */
	hcd = usb_create_hcd(&sl811h_hc_driver, &dev->dev, dev_name(&dev->dev));
	अगर (!hcd) अणु
		retval = -ENOMEM;
		जाओ err5;
	पूर्ण
	hcd->rsrc_start = addr->start;
	sl811 = hcd_to_sl811(hcd);

	spin_lock_init(&sl811->lock);
	INIT_LIST_HEAD(&sl811->async);
	sl811->board = dev_get_platdata(&dev->dev);
	समयr_setup(&sl811->समयr, sl811h_समयr, 0);
	sl811->addr_reg = addr_reg;
	sl811->data_reg = data_reg;

	spin_lock_irq(&sl811->lock);
	port_घातer(sl811, 0);
	spin_unlock_irq(&sl811->lock);
	msleep(200);

	पंचांगp = sl811_पढ़ो(sl811, SL11H_HWREVREG);
	चयन (पंचांगp >> 4) अणु
	हाल 1:
		hcd->product_desc = "SL811HS v1.2";
		अवरोध;
	हाल 2:
		hcd->product_desc = "SL811HS v1.5";
		अवरोध;
	शेष:
		/* reject हाल 0, SL11S is less functional */
		dev_dbg(&dev->dev, "chiprev %02x\n", पंचांगp);
		retval = -ENXIO;
		जाओ err6;
	पूर्ण

	/* The chip's IRQ is level triggered, active high.  A requirement
	 * क्रम platक्रमm device setup is to cope with things like संकेत
	 * inverters (e.g. CF is active low) or working only with edge
	 * triggers (e.g. most ARM CPUs).  Initial driver stress testing
	 * was on a प्रणाली with single edge triggering, so most sorts of
	 * triggering arrangement should work.
	 *
	 * Use resource IRQ flags अगर set by platक्रमm device setup.
	 */
	irqflags |= IRQF_SHARED;
	retval = usb_add_hcd(hcd, irq, irqflags);
	अगर (retval != 0)
		जाओ err6;

	device_wakeup_enable(hcd->self.controller);

	create_debug_file(sl811);
	वापस retval;

 err6:
	usb_put_hcd(hcd);
 err5:
	अगर (!ioaddr)
		iounmap(data_reg);
 err4:
	अगर (!ioaddr)
		iounmap(addr_reg);
 err2:
	dev_dbg(&dev->dev, "init error, %d\n", retval);
	वापस retval;
पूर्ण

#अगर_घोषित	CONFIG_PM

/* क्रम this device there's no useful distinction between the controller
 * and its root hub.
 */

अटल पूर्णांक
sl811h_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा usb_hcd	*hcd = platक्रमm_get_drvdata(dev);
	काष्ठा sl811	*sl811 = hcd_to_sl811(hcd);
	पूर्णांक		retval = 0;

	चयन (state.event) अणु
	हाल PM_EVENT_FREEZE:
		retval = sl811h_bus_suspend(hcd);
		अवरोध;
	हाल PM_EVENT_SUSPEND:
	हाल PM_EVENT_HIBERNATE:
	हाल PM_EVENT_PRETHAW:		/* explicitly discard hw state */
		port_घातer(sl811, 0);
		अवरोध;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक
sl811h_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd	*hcd = platक्रमm_get_drvdata(dev);
	काष्ठा sl811	*sl811 = hcd_to_sl811(hcd);

	/* with no "check to see if VBUS is still powered" board hook,
	 * let's assume it'd only be घातered to enable remote wakeup.
	 */
	अगर (!sl811->port1 || !device_can_wakeup(&hcd->self.root_hub->dev)) अणु
		sl811->port1 = 0;
		port_घातer(sl811, 1);
		usb_root_hub_lost_घातer(hcd->self.root_hub);
		वापस 0;
	पूर्ण

	वापस sl811h_bus_resume(hcd);
पूर्ण

#अन्यथा

#घोषणा	sl811h_suspend	शून्य
#घोषणा	sl811h_resume	शून्य

#पूर्ण_अगर


/* this driver is exported so sl811_cs can depend on it */
काष्ठा platक्रमm_driver sl811h_driver = अणु
	.probe =	sl811h_probe,
	.हटाओ =	sl811h_हटाओ,

	.suspend =	sl811h_suspend,
	.resume =	sl811h_resume,
	.driver = अणु
		.name =	hcd_name,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(sl811h_driver);

module_platक्रमm_driver(sl811h_driver);
