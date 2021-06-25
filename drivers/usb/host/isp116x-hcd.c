<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ISP116x HCD (Host Controller Driver) क्रम USB.
 *
 * Derived from the SL811 HCD, rewritten क्रम ISP116x.
 * Copyright (C) 2005 Olav Kongas <ok@artecdesign.ee>
 *
 * Portions:
 * Copyright (C) 2004 Psion Teklogix (क्रम NetBook PRO)
 * Copyright (C) 2004 David Brownell
 *
 * Periodic scheduling is based on Roman's OHCI code
 * Copyright (C) 1999 Roman Weissgaerber
 *
 */

/*
 * The driver basically works. A number of people have used it with a range
 * of devices.
 *
 * The driver passes all usbtests 1-14.
 *
 * Suspending/resuming of root hub via sysfs works. Remote wakeup works too.
 * And suspending/resuming of platक्रमm device works too. Suspend/resume
 * via HCD operations vector is not implemented.
 *
 * Iso transfer support is not implemented. Adding this would include
 * implementing recovery from the failure to service the processed ITL
 * fअगरo ram in समय, which will involve chip reset.
 *
 * TODO:
 + More testing of suspend/resume.
*/

/*
  ISP116x chips require certain delays between accesses to its
  रेजिस्टरs. The following timing options exist.

  1. Configure your memory controller (the best)
  2. Implement platक्रमm-specअगरic delay function possibly
  combined with configuring the memory controller; see
  include/linux/usb-isp116x.h क्रम more info. Some broken
  memory controllers line LH7A400 SMC need this. Also,
  uncomment क्रम that to work the following
  USE_PLATFORM_DELAY macro.
  3. Use ndelay (easiest, poorest). For that, uncomment
  the following USE_NDELAY macro.
*/
#घोषणा USE_PLATFORM_DELAY
//#घोषणा USE_NDELAY

//#घोषणा DEBUG
//#घोषणा VERBOSE
/* Transfer descriptors. See dump_ptd() क्रम prपूर्णांकout क्रमmat  */
//#घोषणा PTD_TRACE
/* enqueuing/finishing log of urbs */
//#घोषणा URB_TRACE

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/isp116x.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "isp116x.h"

#घोषणा DRIVER_VERSION	"03 Nov 2005"
#घोषणा DRIVER_DESC	"ISP116x USB Host Controller Driver"

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल स्थिर अक्षर hcd_name[] = "isp116x-hcd";

/*-----------------------------------------------------------------*/

/*
  Write len bytes to fअगरo, pad till 32-bit boundary
 */
अटल व्योम ग_लिखो_ptddata_to_fअगरo(काष्ठा isp116x *isp116x, व्योम *buf, पूर्णांक len)
अणु
	u8 *dp = (u8 *) buf;
	u16 *dp2 = (u16 *) buf;
	u16 w;
	पूर्णांक quot = len % 4;

	/* buffer is alपढ़ोy in 'usb data order', which is LE. */
	/* When पढ़ोing buffer as u16, we have to take care byte order */
	/* करोesn't get mixed up */

	अगर ((अचिन्हित दीर्घ)dp2 & 1) अणु
		/* not aligned */
		क्रम (; len > 1; len -= 2) अणु
			w = *dp++;
			w |= *dp++ << 8;
			isp116x_raw_ग_लिखो_data16(isp116x, w);
		पूर्ण
		अगर (len)
			isp116x_ग_लिखो_data16(isp116x, (u16) * dp);
	पूर्ण अन्यथा अणु
		/* aligned */
		क्रम (; len > 1; len -= 2) अणु
			/* Keep byte order ! */
			isp116x_raw_ग_लिखो_data16(isp116x, cpu_to_le16(*dp2++));
		पूर्ण

		अगर (len)
			isp116x_ग_लिखो_data16(isp116x, 0xff & *((u8 *) dp2));
	पूर्ण
	अगर (quot == 1 || quot == 2)
		isp116x_raw_ग_लिखो_data16(isp116x, 0);
पूर्ण

/*
  Read len bytes from fअगरo and then पढ़ो till 32-bit boundary.
 */
अटल व्योम पढ़ो_ptddata_from_fअगरo(काष्ठा isp116x *isp116x, व्योम *buf, पूर्णांक len)
अणु
	u8 *dp = (u8 *) buf;
	u16 *dp2 = (u16 *) buf;
	u16 w;
	पूर्णांक quot = len % 4;

	/* buffer is alपढ़ोy in 'usb data order', which is LE. */
	/* When पढ़ोing buffer as u16, we have to take care byte order */
	/* करोesn't get mixed up */

	अगर ((अचिन्हित दीर्घ)dp2 & 1) अणु
		/* not aligned */
		क्रम (; len > 1; len -= 2) अणु
			w = isp116x_raw_पढ़ो_data16(isp116x);
			*dp++ = w & 0xff;
			*dp++ = (w >> 8) & 0xff;
		पूर्ण

		अगर (len)
			*dp = 0xff & isp116x_पढ़ो_data16(isp116x);
	पूर्ण अन्यथा अणु
		/* aligned */
		क्रम (; len > 1; len -= 2) अणु
			/* Keep byte order! */
			*dp2++ = le16_to_cpu(isp116x_raw_पढ़ो_data16(isp116x));
		पूर्ण

		अगर (len)
			*(u8 *) dp2 = 0xff & isp116x_पढ़ो_data16(isp116x);
	पूर्ण
	अगर (quot == 1 || quot == 2)
		isp116x_raw_पढ़ो_data16(isp116x);
पूर्ण

/*
  Write ptd's and data क्रम scheduled transfers पूर्णांकo
  the fअगरo ram. Fअगरo must be empty and पढ़ोy.
*/
अटल व्योम pack_fअगरo(काष्ठा isp116x *isp116x)
अणु
	काष्ठा isp116x_ep *ep;
	काष्ठा ptd *ptd;
	पूर्णांक buflen = isp116x->atl_last_dir == PTD_सूची_IN
	    ? isp116x->atl_bufshrt : isp116x->atl_buflen;

	isp116x_ग_लिखो_reg16(isp116x, HCuPINT, HCuPINT_AIIEOT);
	isp116x_ग_लिखो_reg16(isp116x, HCXFERCTR, buflen);
	isp116x_ग_लिखो_addr(isp116x, HCATLPORT | ISP116x_WRITE_OFFSET);
	क्रम (ep = isp116x->atl_active; ep; ep = ep->active) अणु
		ptd = &ep->ptd;
		dump_ptd(ptd);
		dump_ptd_out_data(ptd, ep->data);
		isp116x_ग_लिखो_data16(isp116x, ptd->count);
		isp116x_ग_लिखो_data16(isp116x, ptd->mps);
		isp116x_ग_लिखो_data16(isp116x, ptd->len);
		isp116x_ग_लिखो_data16(isp116x, ptd->faddr);
		buflen -= माप(काष्ठा ptd);
		/* Skip writing data क्रम last IN PTD */
		अगर (ep->active || (isp116x->atl_last_dir != PTD_सूची_IN)) अणु
			ग_लिखो_ptddata_to_fअगरo(isp116x, ep->data, ep->length);
			buflen -= ALIGN(ep->length, 4);
		पूर्ण
	पूर्ण
	BUG_ON(buflen);
पूर्ण

/*
  Read the processed ptd's and data from fअगरo ram back to
  URBs' buffers. Fअगरo must be full and करोne
*/
अटल व्योम unpack_fअगरo(काष्ठा isp116x *isp116x)
अणु
	काष्ठा isp116x_ep *ep;
	काष्ठा ptd *ptd;
	पूर्णांक buflen = isp116x->atl_last_dir == PTD_सूची_IN
	    ? isp116x->atl_buflen : isp116x->atl_bufshrt;

	isp116x_ग_लिखो_reg16(isp116x, HCuPINT, HCuPINT_AIIEOT);
	isp116x_ग_लिखो_reg16(isp116x, HCXFERCTR, buflen);
	isp116x_ग_लिखो_addr(isp116x, HCATLPORT);
	क्रम (ep = isp116x->atl_active; ep; ep = ep->active) अणु
		ptd = &ep->ptd;
		ptd->count = isp116x_पढ़ो_data16(isp116x);
		ptd->mps = isp116x_पढ़ो_data16(isp116x);
		ptd->len = isp116x_पढ़ो_data16(isp116x);
		ptd->faddr = isp116x_पढ़ो_data16(isp116x);
		buflen -= माप(काष्ठा ptd);
		/* Skip पढ़ोing data क्रम last Setup or Out PTD */
		अगर (ep->active || (isp116x->atl_last_dir == PTD_सूची_IN)) अणु
			पढ़ो_ptddata_from_fअगरo(isp116x, ep->data, ep->length);
			buflen -= ALIGN(ep->length, 4);
		पूर्ण
		dump_ptd(ptd);
		dump_ptd_in_data(ptd, ep->data);
	पूर्ण
	BUG_ON(buflen);
पूर्ण

/*---------------------------------------------------------------*/

/*
  Set up PTD's.
*/
अटल व्योम preproc_atl_queue(काष्ठा isp116x *isp116x)
अणु
	काष्ठा isp116x_ep *ep;
	काष्ठा urb *urb;
	काष्ठा ptd *ptd;
	u16 len;

	क्रम (ep = isp116x->atl_active; ep; ep = ep->active) अणु
		u16 toggle = 0, dir = PTD_सूची_SETUP;

		BUG_ON(list_empty(&ep->hep->urb_list));
		urb = container_of(ep->hep->urb_list.next,
				   काष्ठा urb, urb_list);
		ptd = &ep->ptd;
		len = ep->length;
		ep->data = (अचिन्हित अक्षर *)urb->transfer_buffer
		    + urb->actual_length;

		चयन (ep->nextpid) अणु
		हाल USB_PID_IN:
			toggle = usb_gettoggle(urb->dev, ep->epnum, 0);
			dir = PTD_सूची_IN;
			अवरोध;
		हाल USB_PID_OUT:
			toggle = usb_gettoggle(urb->dev, ep->epnum, 1);
			dir = PTD_सूची_OUT;
			अवरोध;
		हाल USB_PID_SETUP:
			len = माप(काष्ठा usb_ctrlrequest);
			ep->data = urb->setup_packet;
			अवरोध;
		हाल USB_PID_ACK:
			toggle = 1;
			len = 0;
			dir = (urb->transfer_buffer_length
			       && usb_pipein(urb->pipe))
			    ? PTD_सूची_OUT : PTD_सूची_IN;
			अवरोध;
		शेष:
			ERR("%s %d: ep->nextpid %d\n", __func__, __LINE__,
			    ep->nextpid);
			BUG();
		पूर्ण

		ptd->count = PTD_CC_MSK | PTD_ACTIVE_MSK | PTD_TOGGLE(toggle);
		ptd->mps = PTD_MPS(ep->maxpacket)
		    | PTD_SPD(urb->dev->speed == USB_SPEED_LOW)
		    | PTD_EP(ep->epnum);
		ptd->len = PTD_LEN(len) | PTD_सूची(dir);
		ptd->faddr = PTD_FA(usb_pipedevice(urb->pipe));
		अगर (!ep->active) अणु
			ptd->mps |= PTD_LAST_MSK;
			isp116x->atl_last_dir = dir;
		पूर्ण
		isp116x->atl_bufshrt = माप(काष्ठा ptd) + isp116x->atl_buflen;
		isp116x->atl_buflen = isp116x->atl_bufshrt + ALIGN(len, 4);
	पूर्ण
पूर्ण

/*
  Take करोne or failed requests out of schedule. Give back
  processed urbs.
*/
अटल व्योम finish_request(काष्ठा isp116x *isp116x, काष्ठा isp116x_ep *ep,
			   काष्ठा urb *urb, पूर्णांक status)
__releases(isp116x->lock) __acquires(isp116x->lock)
अणु
	अचिन्हित i;

	ep->error_count = 0;

	अगर (usb_pipecontrol(urb->pipe))
		ep->nextpid = USB_PID_SETUP;

	urb_dbg(urb, "Finish");

	usb_hcd_unlink_urb_from_ep(isp116x_to_hcd(isp116x), urb);
	spin_unlock(&isp116x->lock);
	usb_hcd_giveback_urb(isp116x_to_hcd(isp116x), urb, status);
	spin_lock(&isp116x->lock);

	/* take idle endpoपूर्णांकs out of the schedule */
	अगर (!list_empty(&ep->hep->urb_list))
		वापस;

	/* async deschedule */
	अगर (!list_empty(&ep->schedule)) अणु
		list_del_init(&ep->schedule);
		वापस;
	पूर्ण

	/* periodic deschedule */
	DBG("deschedule qh%d/%p branch %d\n", ep->period, ep, ep->branch);
	क्रम (i = ep->branch; i < PERIODIC_SIZE; i += ep->period) अणु
		काष्ठा isp116x_ep *temp;
		काष्ठा isp116x_ep **prev = &isp116x->periodic[i];

		जबतक (*prev && ((temp = *prev) != ep))
			prev = &temp->next;
		अगर (*prev)
			*prev = ep->next;
		isp116x->load[i] -= ep->load;
	पूर्ण
	ep->branch = PERIODIC_SIZE;
	isp116x_to_hcd(isp116x)->self.bandwidth_allocated -=
	    ep->load / ep->period;

	/* चयन irq type? */
	अगर (!--isp116x->periodic_count) अणु
		isp116x->irqenb &= ~HCuPINT_SOF;
		isp116x->irqenb |= HCuPINT_ATL;
	पूर्ण
पूर्ण

/*
  Analyze transfer results, handle partial transfers and errors
*/
अटल व्योम postproc_atl_queue(काष्ठा isp116x *isp116x)
अणु
	काष्ठा isp116x_ep *ep;
	काष्ठा urb *urb;
	काष्ठा usb_device *udev;
	काष्ठा ptd *ptd;
	पूर्णांक लघु_not_ok;
	पूर्णांक status;
	u8 cc;

	क्रम (ep = isp116x->atl_active; ep; ep = ep->active) अणु
		BUG_ON(list_empty(&ep->hep->urb_list));
		urb =
		    container_of(ep->hep->urb_list.next, काष्ठा urb, urb_list);
		udev = urb->dev;
		ptd = &ep->ptd;
		cc = PTD_GET_CC(ptd);
		लघु_not_ok = 1;
		status = -EINPROGRESS;

		/* Data underrun is special. For allowed underrun
		   we clear the error and जारी as normal. For
		   क्रमbidden underrun we finish the DATA stage
		   immediately जबतक क्रम control transfer,
		   we करो a STATUS stage. */
		अगर (cc == TD_DATAUNDERRUN) अणु
			अगर (!(urb->transfer_flags & URB_SHORT_NOT_OK) ||
					usb_pipecontrol(urb->pipe)) अणु
				DBG("Allowed or control data underrun\n");
				cc = TD_CC_NOERROR;
				लघु_not_ok = 0;
			पूर्ण अन्यथा अणु
				ep->error_count = 1;
				usb_settoggle(udev, ep->epnum,
					      ep->nextpid == USB_PID_OUT,
					      PTD_GET_TOGGLE(ptd));
				urb->actual_length += PTD_GET_COUNT(ptd);
				status = cc_to_error[TD_DATAUNDERRUN];
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (cc != TD_CC_NOERROR && cc != TD_NOTACCESSED
		    && (++ep->error_count >= 3 || cc == TD_CC_STALL
			|| cc == TD_DATAOVERRUN)) अणु
			status = cc_to_error[cc];
			अगर (ep->nextpid == USB_PID_ACK)
				ep->nextpid = 0;
			जाओ करोne;
		पूर्ण
		/* According to usb spec, zero-length Int transfer संकेतs
		   finishing of the urb. Hey, करोes this apply only
		   क्रम IN endpoपूर्णांकs? */
		अगर (usb_pipeपूर्णांक(urb->pipe) && !PTD_GET_LEN(ptd)) अणु
			status = 0;
			जाओ करोne;
		पूर्ण

		/* Relax after previously failed, but later succeeded
		   or correctly NAK'ed retransmission attempt */
		अगर (ep->error_count
		    && (cc == TD_CC_NOERROR || cc == TD_NOTACCESSED))
			ep->error_count = 0;

		/* Take पूर्णांकo account idiosyncracies of the isp116x chip
		   regarding toggle bit क्रम failed transfers */
		अगर (ep->nextpid == USB_PID_OUT)
			usb_settoggle(udev, ep->epnum, 1, PTD_GET_TOGGLE(ptd)
				      ^ (ep->error_count > 0));
		अन्यथा अगर (ep->nextpid == USB_PID_IN)
			usb_settoggle(udev, ep->epnum, 0, PTD_GET_TOGGLE(ptd)
				      ^ (ep->error_count > 0));

		चयन (ep->nextpid) अणु
		हाल USB_PID_IN:
		हाल USB_PID_OUT:
			urb->actual_length += PTD_GET_COUNT(ptd);
			अगर (PTD_GET_ACTIVE(ptd)
			    || (cc != TD_CC_NOERROR && cc < 0x0E))
				अवरोध;
			अगर (urb->transfer_buffer_length != urb->actual_length) अणु
				अगर (लघु_not_ok)
					अवरोध;
			पूर्ण अन्यथा अणु
				अगर (urb->transfer_flags & URB_ZERO_PACKET
				    && ep->nextpid == USB_PID_OUT
				    && !(PTD_GET_COUNT(ptd) % ep->maxpacket)) अणु
					DBG("Zero packet requested\n");
					अवरोध;
				पूर्ण
			पूर्ण
			/* All data क्रम this URB is transferred, let's finish */
			अगर (usb_pipecontrol(urb->pipe))
				ep->nextpid = USB_PID_ACK;
			अन्यथा
				status = 0;
			अवरोध;
		हाल USB_PID_SETUP:
			अगर (PTD_GET_ACTIVE(ptd)
			    || (cc != TD_CC_NOERROR && cc < 0x0E))
				अवरोध;
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
			अगर (PTD_GET_ACTIVE(ptd)
			    || (cc != TD_CC_NOERROR && cc < 0x0E))
				अवरोध;
			status = 0;
			ep->nextpid = 0;
			अवरोध;
		शेष:
			BUG();
		पूर्ण

 करोne:
		अगर (status != -EINPROGRESS || urb->unlinked)
			finish_request(isp116x, ep, urb, status);
	पूर्ण
पूर्ण

/*
  Scan transfer lists, schedule transfers, send data off
  to chip.
 */
अटल व्योम start_atl_transfers(काष्ठा isp116x *isp116x)
अणु
	काष्ठा isp116x_ep *last_ep = शून्य, *ep;
	काष्ठा urb *urb;
	u16 load = 0;
	पूर्णांक len, index, speed, byte_समय;

	अगर (atomic_पढ़ो(&isp116x->atl_finishing))
		वापस;

	अगर (!HC_IS_RUNNING(isp116x_to_hcd(isp116x)->state))
		वापस;

	/* FIFO not empty? */
	अगर (isp116x_पढ़ो_reg16(isp116x, HCBUFSTAT) & HCBUFSTAT_ATL_FULL)
		वापस;

	isp116x->atl_active = शून्य;
	isp116x->atl_buflen = isp116x->atl_bufshrt = 0;

	/* Schedule पूर्णांक transfers */
	अगर (isp116x->periodic_count) अणु
		isp116x->fmindex = index =
		    (isp116x->fmindex + 1) & (PERIODIC_SIZE - 1);
		load = isp116x->load[index];
		अगर (load) अणु
			/* Bring all पूर्णांक transfers क्रम this frame
			   पूर्णांकo the active queue */
			isp116x->atl_active = last_ep =
			    isp116x->periodic[index];
			जबतक (last_ep->next)
				last_ep = (last_ep->active = last_ep->next);
			last_ep->active = शून्य;
		पूर्ण
	पूर्ण

	/* Schedule control/bulk transfers */
	list_क्रम_each_entry(ep, &isp116x->async, schedule) अणु
		urb = container_of(ep->hep->urb_list.next,
				   काष्ठा urb, urb_list);
		speed = urb->dev->speed;
		byte_समय = speed == USB_SPEED_LOW
		    ? BYTE_TIME_LOWSPEED : BYTE_TIME_FULLSPEED;

		अगर (ep->nextpid == USB_PID_SETUP) अणु
			len = माप(काष्ठा usb_ctrlrequest);
		पूर्ण अन्यथा अगर (ep->nextpid == USB_PID_ACK) अणु
			len = 0;
		पूर्ण अन्यथा अणु
			/* Find current मुक्त length ... */
			len = (MAX_LOAD_LIMIT - load) / byte_समय;

			/* ... then limit it to configured max size ... */
			len = min(len, speed == USB_SPEED_LOW ?
				  MAX_TRANSFER_SIZE_LOWSPEED :
				  MAX_TRANSFER_SIZE_FULLSPEED);

			/* ... and finally cut to the multiple of MaxPacketSize,
			   or to the real length अगर there's enough room. */
			अगर (len <
			    (urb->transfer_buffer_length -
			     urb->actual_length)) अणु
				len -= len % ep->maxpacket;
				अगर (!len)
					जारी;
			पूर्ण अन्यथा
				len = urb->transfer_buffer_length -
				    urb->actual_length;
			BUG_ON(len < 0);
		पूर्ण

		load += len * byte_समय;
		अगर (load > MAX_LOAD_LIMIT)
			अवरोध;

		ep->active = शून्य;
		ep->length = len;
		अगर (last_ep)
			last_ep->active = ep;
		अन्यथा
			isp116x->atl_active = ep;
		last_ep = ep;
	पूर्ण

	/* Aव्योम starving of endpoपूर्णांकs */
	अगर ((&isp116x->async)->next != (&isp116x->async)->prev)
		list_move(&isp116x->async, (&isp116x->async)->next);

	अगर (isp116x->atl_active) अणु
		preproc_atl_queue(isp116x);
		pack_fअगरo(isp116x);
	पूर्ण
पूर्ण

/*
  Finish the processed transfers
*/
अटल व्योम finish_atl_transfers(काष्ठा isp116x *isp116x)
अणु
	अगर (!isp116x->atl_active)
		वापस;
	/* Fअगरo not पढ़ोy? */
	अगर (!(isp116x_पढ़ो_reg16(isp116x, HCBUFSTAT) & HCBUFSTAT_ATL_DONE))
		वापस;

	atomic_inc(&isp116x->atl_finishing);
	unpack_fअगरo(isp116x);
	postproc_atl_queue(isp116x);
	atomic_dec(&isp116x->atl_finishing);
पूर्ण

अटल irqवापस_t isp116x_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	u16 irqstat;
	irqवापस_t ret = IRQ_NONE;

	spin_lock(&isp116x->lock);
	isp116x_ग_लिखो_reg16(isp116x, HCuPINTENB, 0);
	irqstat = isp116x_पढ़ो_reg16(isp116x, HCuPINT);
	isp116x_ग_लिखो_reg16(isp116x, HCuPINT, irqstat);

	अगर (irqstat & (HCuPINT_ATL | HCuPINT_SOF)) अणु
		ret = IRQ_HANDLED;
		finish_atl_transfers(isp116x);
	पूर्ण

	अगर (irqstat & HCuPINT_OPR) अणु
		u32 पूर्णांकstat = isp116x_पढ़ो_reg32(isp116x, HCINTSTAT);
		isp116x_ग_लिखो_reg32(isp116x, HCINTSTAT, पूर्णांकstat);
		अगर (पूर्णांकstat & HCINT_UE) अणु
			ERR("Unrecoverable error, HC is dead!\n");
			/* IRQ's are off, we करो no DMA,
			   perfectly पढ़ोy to die ... */
			hcd->state = HC_STATE_HALT;
			usb_hc_died(hcd);
			ret = IRQ_HANDLED;
			जाओ करोne;
		पूर्ण
		अगर (पूर्णांकstat & HCINT_RHSC)
			/* When root hub or any of its ports is going
			   to come out of suspend, it may take more
			   than 10ms क्रम status bits to stabilize. */
			mod_समयr(&hcd->rh_समयr, jअगरfies
				  + msecs_to_jअगरfies(20) + 1);
		अगर (पूर्णांकstat & HCINT_RD) अणु
			DBG("---- remote wakeup\n");
			usb_hcd_resume_root_hub(hcd);
		पूर्ण
		irqstat &= ~HCuPINT_OPR;
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (irqstat & (HCuPINT_ATL | HCuPINT_SOF)) अणु
		start_atl_transfers(isp116x);
	पूर्ण

	isp116x_ग_लिखो_reg16(isp116x, HCuPINTENB, isp116x->irqenb);
      करोne:
	spin_unlock(&isp116x->lock);
	वापस ret;
पूर्ण

/*-----------------------------------------------------------------*/

/* usb 1.1 says max 90% of a frame is available क्रम periodic transfers.
 * this driver करोesn't promise that much since it's got to handle an
 * IRQ per packet; irq handling latencies also use up that समय.
 */

/* out of 1000 us */
#घोषणा	MAX_PERIODIC_LOAD	600
अटल पूर्णांक balance(काष्ठा isp116x *isp116x, u16 period, u16 load)
अणु
	पूर्णांक i, branch = -ENOSPC;

	/* search क्रम the least loaded schedule branch of that period
	   which has enough bandwidth left unreserved. */
	क्रम (i = 0; i < period; i++) अणु
		अगर (branch < 0 || isp116x->load[branch] > isp116x->load[i]) अणु
			पूर्णांक j;

			क्रम (j = i; j < PERIODIC_SIZE; j += period) अणु
				अगर ((isp116x->load[j] + load)
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

/* NB! ALL the code above this poपूर्णांक runs with isp116x->lock
   held, irqs off
*/

/*-----------------------------------------------------------------*/

अटल पूर्णांक isp116x_urb_enqueue(काष्ठा usb_hcd *hcd,
			       काष्ठा urb *urb,
			       gfp_t mem_flags)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	काष्ठा usb_device *udev = urb->dev;
	अचिन्हित पूर्णांक pipe = urb->pipe;
	पूर्णांक is_out = !usb_pipein(pipe);
	पूर्णांक type = usb_pipetype(pipe);
	पूर्णांक epnum = usb_pipeendpoपूर्णांक(pipe);
	काष्ठा usb_host_endpoपूर्णांक *hep = urb->ep;
	काष्ठा isp116x_ep *ep = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक ret = 0;

	urb_dbg(urb, "Enqueue");

	अगर (type == PIPE_ISOCHRONOUS) अणु
		ERR("Isochronous transfers not supported\n");
		urb_dbg(urb, "Refused to enqueue");
		वापस -ENXIO;
	पूर्ण
	/* aव्योम all allocations within spinlocks: request or endpoपूर्णांक */
	अगर (!hep->hcpriv) अणु
		ep = kzalloc(माप *ep, mem_flags);
		अगर (!ep)
			वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&isp116x->lock, flags);
	अगर (!HC_IS_RUNNING(hcd->state)) अणु
		kमुक्त(ep);
		ret = -ENODEV;
		जाओ fail_not_linked;
	पूर्ण
	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (ret) अणु
		kमुक्त(ep);
		जाओ fail_not_linked;
	पूर्ण

	अगर (hep->hcpriv)
		ep = hep->hcpriv;
	अन्यथा अणु
		INIT_LIST_HEAD(&ep->schedule);
		ep->udev = udev;
		ep->epnum = epnum;
		ep->maxpacket = usb_maxpacket(udev, urb->pipe, is_out);
		usb_settoggle(udev, epnum, is_out, 0);

		अगर (type == PIPE_CONTROL) अणु
			ep->nextpid = USB_PID_SETUP;
		पूर्ण अन्यथा अगर (is_out) अणु
			ep->nextpid = USB_PID_OUT;
		पूर्ण अन्यथा अणु
			ep->nextpid = USB_PID_IN;
		पूर्ण

		अगर (urb->पूर्णांकerval) अणु
			/*
			   With INT URBs submitted, the driver works with SOF
			   पूर्णांकerrupt enabled and ATL पूर्णांकerrupt disabled. After
			   the PTDs are written to fअगरo ram, the chip starts
			   fअगरo processing and usb transfers after the next
			   SOF and जारीs until the transfers are finished
			   (succeeded or failed) or the frame ends. Thereक्रमe,
			   the transfers occur only in every second frame,
			   जबतक fअगरo पढ़ोing/writing and data processing
			   occur in every other second frame. */
			अगर (urb->पूर्णांकerval < 2)
				urb->पूर्णांकerval = 2;
			अगर (urb->पूर्णांकerval > 2 * PERIODIC_SIZE)
				urb->पूर्णांकerval = 2 * PERIODIC_SIZE;
			ep->period = urb->पूर्णांकerval >> 1;
			ep->branch = PERIODIC_SIZE;
			ep->load = usb_calc_bus_समय(udev->speed,
						     !is_out,
						     (type == PIPE_ISOCHRONOUS),
						     usb_maxpacket(udev, pipe,
								   is_out)) /
			    1000;
		पूर्ण
		hep->hcpriv = ep;
		ep->hep = hep;
	पूर्ण

	/* maybe put endpoपूर्णांक पूर्णांकo schedule */
	चयन (type) अणु
	हाल PIPE_CONTROL:
	हाल PIPE_BULK:
		अगर (list_empty(&ep->schedule))
			list_add_tail(&ep->schedule, &isp116x->async);
		अवरोध;
	हाल PIPE_INTERRUPT:
		urb->पूर्णांकerval = ep->period;
		ep->length = min_t(u32, ep->maxpacket,
				 urb->transfer_buffer_length);

		/* urb submitted क्रम alपढ़ोy existing endpoपूर्णांक */
		अगर (ep->branch < PERIODIC_SIZE)
			अवरोध;

		ep->branch = ret = balance(isp116x, ep->period, ep->load);
		अगर (ret < 0)
			जाओ fail;
		ret = 0;

		urb->start_frame = (isp116x->fmindex & (PERIODIC_SIZE - 1))
		    + ep->branch;

		/* sort each schedule branch by period (slow beक्रमe fast)
		   to share the faster parts of the tree without needing
		   dummy/placeholder nodes */
		DBG("schedule qh%d/%p branch %d\n", ep->period, ep, ep->branch);
		क्रम (i = ep->branch; i < PERIODIC_SIZE; i += ep->period) अणु
			काष्ठा isp116x_ep **prev = &isp116x->periodic[i];
			काष्ठा isp116x_ep *here = *prev;

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
			isp116x->load[i] += ep->load;
		पूर्ण
		hcd->self.bandwidth_allocated += ep->load / ep->period;

		/* चयन over to SOFपूर्णांक */
		अगर (!isp116x->periodic_count++) अणु
			isp116x->irqenb &= ~HCuPINT_ATL;
			isp116x->irqenb |= HCuPINT_SOF;
			isp116x_ग_लिखो_reg16(isp116x, HCuPINTENB,
					    isp116x->irqenb);
		पूर्ण
	पूर्ण

	urb->hcpriv = hep;
	start_atl_transfers(isp116x);

      fail:
	अगर (ret)
		usb_hcd_unlink_urb_from_ep(hcd, urb);
      fail_not_linked:
	spin_unlock_irqrestore(&isp116x->lock, flags);
	वापस ret;
पूर्ण

/*
   Dequeue URBs.
*/
अटल पूर्णांक isp116x_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		पूर्णांक status)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	काष्ठा usb_host_endpoपूर्णांक *hep;
	काष्ठा isp116x_ep *ep, *ep_act;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&isp116x->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc)
		जाओ करोne;

	hep = urb->hcpriv;
	ep = hep->hcpriv;
	WARN_ON(hep != ep->hep);

	/* In front of queue? */
	अगर (ep->hep->urb_list.next == &urb->urb_list)
		/* active? */
		क्रम (ep_act = isp116x->atl_active; ep_act;
		     ep_act = ep_act->active)
			अगर (ep_act == ep) अणु
				VDBG("dequeue, urb %p active; wait for irq\n",
				     urb);
				urb = शून्य;
				अवरोध;
			पूर्ण

	अगर (urb)
		finish_request(isp116x, ep, urb, status);
 करोne:
	spin_unlock_irqrestore(&isp116x->lock, flags);
	वापस rc;
पूर्ण

अटल व्योम isp116x_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
				     काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	पूर्णांक i;
	काष्ठा isp116x_ep *ep = hep->hcpriv;

	अगर (!ep)
		वापस;

	/* assume we'd just रुको क्रम the irq */
	क्रम (i = 0; i < 100 && !list_empty(&hep->urb_list); i++)
		msleep(3);
	अगर (!list_empty(&hep->urb_list))
		WARNING("ep %p not empty?\n", ep);

	kमुक्त(ep);
	hep->hcpriv = शून्य;
पूर्ण

अटल पूर्णांक isp116x_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	u32 fmnum;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&isp116x->lock, flags);
	fmnum = isp116x_पढ़ो_reg32(isp116x, HCFMNUM);
	spin_unlock_irqrestore(&isp116x->lock, flags);
	वापस (पूर्णांक)fmnum;
पूर्ण

/*
  Adapted from ohci-hub.c. Currently we करोn't support स्वतःsuspend.
*/
अटल पूर्णांक isp116x_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	पूर्णांक ports, i, changed = 0;
	अचिन्हित दीर्घ flags;

	अगर (!HC_IS_RUNNING(hcd->state))
		वापस -ESHUTDOWN;

	/* Report no status change now, अगर we are scheduled to be
	   called later */
	अगर (समयr_pending(&hcd->rh_समयr))
		वापस 0;

	ports = isp116x->rhdesca & RH_A_NDP;
	spin_lock_irqsave(&isp116x->lock, flags);
	isp116x->rhstatus = isp116x_पढ़ो_reg32(isp116x, HCRHSTATUS);
	अगर (isp116x->rhstatus & (RH_HS_LPSC | RH_HS_OCIC))
		buf[0] = changed = 1;
	अन्यथा
		buf[0] = 0;

	क्रम (i = 0; i < ports; i++) अणु
		u32 status = isp116x_पढ़ो_reg32(isp116x, i ? HCRHPORT2 : HCRHPORT1);

		अगर (status & (RH_PS_CSC | RH_PS_PESC | RH_PS_PSSC
			      | RH_PS_OCIC | RH_PS_PRSC)) अणु
			changed = 1;
			buf[0] |= 1 << (i + 1);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&isp116x->lock, flags);
	वापस changed;
पूर्ण

अटल व्योम isp116x_hub_descriptor(काष्ठा isp116x *isp116x,
				   काष्ठा usb_hub_descriptor *desc)
अणु
	u32 reg = isp116x->rhdesca;

	desc->bDescriptorType = USB_DT_HUB;
	desc->bDescLength = 9;
	desc->bHubContrCurrent = 0;
	desc->bNbrPorts = (u8) (reg & 0x3);
	/* Power चयनing, device type, overcurrent. */
	desc->wHubCharacteristics = cpu_to_le16((u16) ((reg >> 8) &
						       (HUB_CHAR_LPSM |
							HUB_CHAR_COMPOUND |
							HUB_CHAR_OCPM)));
	desc->bPwrOn2PwrGood = (u8) ((reg >> 24) & 0xff);
	/* ports removable, and legacy PortPwrCtrlMask */
	desc->u.hs.DeviceRemovable[0] = 0;
	desc->u.hs.DeviceRemovable[1] = ~0;
पूर्ण

/* Perक्रमm reset of a given port.
   It would be great to just start the reset and let the
   USB core to clear the reset in due समय. However,
   root hub ports should be reset क्रम at least 50 ms, जबतक
   our chip stays in reset क्रम about 10 ms. I.e., we must
   repeatedly reset it ourself here.
*/
अटल अंतरभूत व्योम root_port_reset(काष्ठा isp116x *isp116x, अचिन्हित port)
अणु
	u32 पंचांगp;
	अचिन्हित दीर्घ flags, t;

	/* Root hub reset should be 50 ms, but some devices
	   want it even दीर्घer. */
	t = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, t)) अणु
		spin_lock_irqsave(&isp116x->lock, flags);
		/* spin until any current reset finishes */
		क्रम (;;) अणु
			पंचांगp = isp116x_पढ़ो_reg32(isp116x, port ?
						 HCRHPORT2 : HCRHPORT1);
			अगर (!(पंचांगp & RH_PS_PRS))
				अवरोध;
			udelay(500);
		पूर्ण
		/* Don't reset a disconnected port */
		अगर (!(पंचांगp & RH_PS_CCS)) अणु
			spin_unlock_irqrestore(&isp116x->lock, flags);
			अवरोध;
		पूर्ण
		/* Reset lasts 10ms (claims datasheet) */
		isp116x_ग_लिखो_reg32(isp116x, port ? HCRHPORT2 :
				    HCRHPORT1, (RH_PS_PRS));
		spin_unlock_irqrestore(&isp116x->lock, flags);
		msleep(10);
	पूर्ण
पूर्ण

/* Adapted from ohci-hub.c */
अटल पूर्णांक isp116x_hub_control(काष्ठा usb_hcd *hcd,
			       u16 typeReq,
			       u16 wValue, u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक ports = isp116x->rhdesca & RH_A_NDP;
	u32 पंचांगp = 0;

	चयन (typeReq) अणु
	हाल ClearHubFeature:
		DBG("ClearHubFeature: ");
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
			DBG("C_HUB_OVER_CURRENT\n");
			spin_lock_irqsave(&isp116x->lock, flags);
			isp116x_ग_लिखो_reg32(isp116x, HCRHSTATUS, RH_HS_OCIC);
			spin_unlock_irqrestore(&isp116x->lock, flags);
			fallthrough;
		हाल C_HUB_LOCAL_POWER:
			DBG("C_HUB_LOCAL_POWER\n");
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SetHubFeature:
		DBG("SetHubFeature: ");
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
		हाल C_HUB_LOCAL_POWER:
			DBG("C_HUB_OVER_CURRENT or C_HUB_LOCAL_POWER\n");
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल GetHubDescriptor:
		DBG("GetHubDescriptor\n");
		isp116x_hub_descriptor(isp116x,
				       (काष्ठा usb_hub_descriptor *)buf);
		अवरोध;
	हाल GetHubStatus:
		DBG("GetHubStatus\n");
		*(__le32 *) buf = 0;
		अवरोध;
	हाल GetPortStatus:
		DBG("GetPortStatus\n");
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		spin_lock_irqsave(&isp116x->lock, flags);
		पंचांगp = isp116x_पढ़ो_reg32(isp116x, (--wIndex) ? HCRHPORT2 : HCRHPORT1);
		spin_unlock_irqrestore(&isp116x->lock, flags);
		*(__le32 *) buf = cpu_to_le32(पंचांगp);
		DBG("GetPortStatus: port[%d]  %08x\n", wIndex + 1, पंचांगp);
		अवरोध;
	हाल ClearPortFeature:
		DBG("ClearPortFeature: ");
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			DBG("USB_PORT_FEAT_ENABLE\n");
			पंचांगp = RH_PS_CCS;
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			DBG("USB_PORT_FEAT_C_ENABLE\n");
			पंचांगp = RH_PS_PESC;
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			DBG("USB_PORT_FEAT_SUSPEND\n");
			पंचांगp = RH_PS_POCI;
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			DBG("USB_PORT_FEAT_C_SUSPEND\n");
			पंचांगp = RH_PS_PSSC;
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			DBG("USB_PORT_FEAT_POWER\n");
			पंचांगp = RH_PS_LSDA;
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			DBG("USB_PORT_FEAT_C_CONNECTION\n");
			पंचांगp = RH_PS_CSC;
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			DBG("USB_PORT_FEAT_C_OVER_CURRENT\n");
			पंचांगp = RH_PS_OCIC;
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			DBG("USB_PORT_FEAT_C_RESET\n");
			पंचांगp = RH_PS_PRSC;
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		spin_lock_irqsave(&isp116x->lock, flags);
		isp116x_ग_लिखो_reg32(isp116x, wIndex
				    ? HCRHPORT2 : HCRHPORT1, पंचांगp);
		spin_unlock_irqrestore(&isp116x->lock, flags);
		अवरोध;
	हाल SetPortFeature:
		DBG("SetPortFeature: ");
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			DBG("USB_PORT_FEAT_SUSPEND\n");
			spin_lock_irqsave(&isp116x->lock, flags);
			isp116x_ग_लिखो_reg32(isp116x, wIndex
					    ? HCRHPORT2 : HCRHPORT1, RH_PS_PSS);
			spin_unlock_irqrestore(&isp116x->lock, flags);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			DBG("USB_PORT_FEAT_POWER\n");
			spin_lock_irqsave(&isp116x->lock, flags);
			isp116x_ग_लिखो_reg32(isp116x, wIndex
					    ? HCRHPORT2 : HCRHPORT1, RH_PS_PPS);
			spin_unlock_irqrestore(&isp116x->lock, flags);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			DBG("USB_PORT_FEAT_RESET\n");
			root_port_reset(isp116x, wIndex);
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;

	शेष:
	      error:
		/* "protocol stall" on error */
		DBG("PROTOCOL STALL\n");
		ret = -EPIPE;
	पूर्ण
	वापस ret;
पूर्ण

/*-----------------------------------------------------------------*/

#अगर_घोषित CONFIG_DEBUG_FS

अटल व्योम dump_irq(काष्ठा seq_file *s, अक्षर *label, u16 mask)
अणु
	seq_म_लिखो(s, "%s %04x%s%s%s%s%s%s\n", label, mask,
		   mask & HCuPINT_CLKRDY ? " clkrdy" : "",
		   mask & HCuPINT_SUSP ? " susp" : "",
		   mask & HCuPINT_OPR ? " opr" : "",
		   mask & HCuPINT_AIIEOT ? " eot" : "",
		   mask & HCuPINT_ATL ? " atl" : "",
		   mask & HCuPINT_SOF ? " sof" : "");
पूर्ण

अटल व्योम dump_पूर्णांक(काष्ठा seq_file *s, अक्षर *label, u32 mask)
अणु
	seq_म_लिखो(s, "%s %08x%s%s%s%s%s%s%s\n", label, mask,
		   mask & HCINT_MIE ? " MIE" : "",
		   mask & HCINT_RHSC ? " rhsc" : "",
		   mask & HCINT_FNO ? " fno" : "",
		   mask & HCINT_UE ? " ue" : "",
		   mask & HCINT_RD ? " rd" : "",
		   mask & HCINT_SF ? " sof" : "", mask & HCINT_SO ? " so" : "");
पूर्ण

अटल पूर्णांक isp116x_debug_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा isp116x *isp116x = s->निजी;

	seq_म_लिखो(s, "%s\n%s version %s\n",
		   isp116x_to_hcd(isp116x)->product_desc, hcd_name,
		   DRIVER_VERSION);

	अगर (HC_IS_SUSPENDED(isp116x_to_hcd(isp116x)->state)) अणु
		seq_म_लिखो(s, "HCD is suspended\n");
		वापस 0;
	पूर्ण
	अगर (!HC_IS_RUNNING(isp116x_to_hcd(isp116x)->state)) अणु
		seq_म_लिखो(s, "HCD not running\n");
		वापस 0;
	पूर्ण

	spin_lock_irq(&isp116x->lock);
	dump_irq(s, "hc_irq_enable", isp116x_पढ़ो_reg16(isp116x, HCuPINTENB));
	dump_irq(s, "hc_irq_status", isp116x_पढ़ो_reg16(isp116x, HCuPINT));
	dump_पूर्णांक(s, "hc_int_enable", isp116x_पढ़ो_reg32(isp116x, HCINTENB));
	dump_पूर्णांक(s, "hc_int_status", isp116x_पढ़ो_reg32(isp116x, HCINTSTAT));
	isp116x_show_regs_seq(isp116x, s);
	spin_unlock_irq(&isp116x->lock);
	seq_म_लिखो(s, "\n");

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(isp116x_debug);

अटल व्योम create_debug_file(काष्ठा isp116x *isp116x)
अणु
	debugfs_create_file(hcd_name, S_IRUGO, usb_debug_root, isp116x,
			    &isp116x_debug_fops);
पूर्ण

अटल व्योम हटाओ_debug_file(काष्ठा isp116x *isp116x)
अणु
	debugfs_हटाओ(debugfs_lookup(hcd_name, usb_debug_root));
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम create_debug_file(काष्ठा isp116x *isp116x) अणु पूर्ण
अटल अंतरभूत व्योम हटाओ_debug_file(काष्ठा isp116x *isp116x) अणु पूर्ण

#पूर्ण_अगर				/* CONFIG_DEBUG_FS */

/*-----------------------------------------------------------------*/

/*
  Software reset - can be called from any contect.
*/
अटल पूर्णांक isp116x_sw_reset(काष्ठा isp116x *isp116x)
अणु
	पूर्णांक retries = 15;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&isp116x->lock, flags);
	isp116x_ग_लिखो_reg16(isp116x, HCSWRES, HCSWRES_MAGIC);
	isp116x_ग_लिखो_reg32(isp116x, HCCMDSTAT, HCCMDSTAT_HCR);
	जबतक (--retries) अणु
		/* It usually resets within 1 ms */
		mdelay(1);
		अगर (!(isp116x_पढ़ो_reg32(isp116x, HCCMDSTAT) & HCCMDSTAT_HCR))
			अवरोध;
	पूर्ण
	अगर (!retries) अणु
		ERR("Software reset timeout\n");
		ret = -ETIME;
	पूर्ण
	spin_unlock_irqrestore(&isp116x->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक isp116x_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	अचिन्हित दीर्घ t;
	u16 clkrdy = 0;
	पूर्णांक ret, समयout = 15 /* ms */ ;

	ret = isp116x_sw_reset(isp116x);
	अगर (ret)
		वापस ret;

	t = jअगरfies + msecs_to_jअगरfies(समयout);
	जबतक (समय_beक्रमe_eq(jअगरfies, t)) अणु
		msleep(4);
		spin_lock_irq(&isp116x->lock);
		clkrdy = isp116x_पढ़ो_reg16(isp116x, HCuPINT) & HCuPINT_CLKRDY;
		spin_unlock_irq(&isp116x->lock);
		अगर (clkrdy)
			अवरोध;
	पूर्ण
	अगर (!clkrdy) अणु
		ERR("Clock not ready after %dms\n", समयout);
		/* After sw_reset the घड़ी won't report to be पढ़ोy, अगर
		   H_WAKEUP pin is high. */
		ERR("Please make sure that the H_WAKEUP pin is pulled low!\n");
		ret = -ENODEV;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम isp116x_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&isp116x->lock, flags);
	isp116x_ग_लिखो_reg16(isp116x, HCuPINTENB, 0);

	/* Switch off ports' power, some devices don't come up
	   after next 'insmod' without this */
	val = isp116x_पढ़ो_reg32(isp116x, HCRHDESCA);
	val &= ~(RH_A_NPS | RH_A_PSM);
	isp116x_ग_लिखो_reg32(isp116x, HCRHDESCA, val);
	isp116x_ग_लिखो_reg32(isp116x, HCRHSTATUS, RH_HS_LPS);
	spin_unlock_irqrestore(&isp116x->lock, flags);

	isp116x_sw_reset(isp116x);
पूर्ण

/*
  Configure the chip. The chip must be successfully reset by now.
*/
अटल पूर्णांक isp116x_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	काष्ठा isp116x_platक्रमm_data *board = isp116x->board;
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&isp116x->lock, flags);

	/* clear पूर्णांकerrupt status and disable all पूर्णांकerrupt sources */
	isp116x_ग_लिखो_reg16(isp116x, HCuPINT, 0xff);
	isp116x_ग_लिखो_reg16(isp116x, HCuPINTENB, 0);

	val = isp116x_पढ़ो_reg16(isp116x, HCCHIPID);
	अगर ((val & HCCHIPID_MASK) != HCCHIPID_MAGIC) अणु
		ERR("Invalid chip ID %04x\n", val);
		spin_unlock_irqrestore(&isp116x->lock, flags);
		वापस -ENODEV;
	पूर्ण

	/* To be हटाओd in future */
	hcd->uses_new_polling = 1;

	isp116x_ग_लिखो_reg16(isp116x, HCITLBUFLEN, ISP116x_ITL_बफ_मानE);
	isp116x_ग_लिखो_reg16(isp116x, HCATLBUFLEN, ISP116x_ATL_बफ_मानE);

	/* ----- HW conf */
	val = HCHWCFG_INT_ENABLE | HCHWCFG_DBWIDTH(1);
	अगर (board->sel15Kres)
		val |= HCHWCFG_15KRSEL;
	/* Remote wakeup won't work without working घड़ी */
	अगर (board->remote_wakeup_enable)
		val |= HCHWCFG_CLKNOTSTOP;
	अगर (board->oc_enable)
		val |= HCHWCFG_ANALOG_OC;
	अगर (board->पूर्णांक_act_high)
		val |= HCHWCFG_INT_POL;
	अगर (board->पूर्णांक_edge_triggered)
		val |= HCHWCFG_INT_TRIGGER;
	isp116x_ग_लिखो_reg16(isp116x, HCHWCFG, val);

	/* ----- Root hub conf */
	val = (25 << 24) & RH_A_POTPGT;
	/* AN10003_1.pdf recommends RH_A_NPS (no घातer चयनing) to
	   be always set. Yet, instead, we request inभागidual port
	   घातer चयनing. */
	val |= RH_A_PSM;
	/* Report overcurrent per port */
	val |= RH_A_OCPM;
	isp116x_ग_लिखो_reg32(isp116x, HCRHDESCA, val);
	isp116x->rhdesca = isp116x_पढ़ो_reg32(isp116x, HCRHDESCA);

	val = RH_B_PPCM;
	isp116x_ग_लिखो_reg32(isp116x, HCRHDESCB, val);
	isp116x->rhdescb = isp116x_पढ़ो_reg32(isp116x, HCRHDESCB);

	val = 0;
	अगर (board->remote_wakeup_enable) अणु
		अगर (!device_can_wakeup(hcd->self.controller))
			device_init_wakeup(hcd->self.controller, 1);
		val |= RH_HS_DRWE;
	पूर्ण
	isp116x_ग_लिखो_reg32(isp116x, HCRHSTATUS, val);
	isp116x->rhstatus = isp116x_पढ़ो_reg32(isp116x, HCRHSTATUS);

	isp116x_ग_लिखो_reg32(isp116x, HCFMINTVL, 0x27782edf);

	hcd->state = HC_STATE_RUNNING;

	/* Set up पूर्णांकerrupts */
	isp116x->पूर्णांकenb = HCINT_MIE | HCINT_RHSC | HCINT_UE;
	अगर (board->remote_wakeup_enable)
		isp116x->पूर्णांकenb |= HCINT_RD;
	isp116x->irqenb = HCuPINT_ATL | HCuPINT_OPR;	/* | HCuPINT_SUSP; */
	isp116x_ग_लिखो_reg32(isp116x, HCINTENB, isp116x->पूर्णांकenb);
	isp116x_ग_लिखो_reg16(isp116x, HCuPINTENB, isp116x->irqenb);

	/* Go operational */
	val = HCCONTROL_USB_OPER;
	अगर (board->remote_wakeup_enable)
		val |= HCCONTROL_RWE;
	isp116x_ग_लिखो_reg32(isp116x, HCCONTROL, val);

	/* Disable ports to aव्योम race in device क्रमागतeration */
	isp116x_ग_लिखो_reg32(isp116x, HCRHPORT1, RH_PS_CCS);
	isp116x_ग_लिखो_reg32(isp116x, HCRHPORT2, RH_PS_CCS);

	isp116x_show_regs_log(isp116x);
	spin_unlock_irqrestore(&isp116x->lock, flags);
	वापस 0;
पूर्ण

#अगर_घोषित	CONFIG_PM

अटल पूर्णांक isp116x_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&isp116x->lock, flags);
	val = isp116x_पढ़ो_reg32(isp116x, HCCONTROL);

	चयन (val & HCCONTROL_HCFS) अणु
	हाल HCCONTROL_USB_OPER:
		spin_unlock_irqrestore(&isp116x->lock, flags);
		val &= (~HCCONTROL_HCFS & ~HCCONTROL_RWE);
		val |= HCCONTROL_USB_SUSPEND;
		अगर (hcd->self.root_hub->करो_remote_wakeup)
			val |= HCCONTROL_RWE;
		/* Wait क्रम usb transfers to finish */
		msleep(2);
		spin_lock_irqsave(&isp116x->lock, flags);
		isp116x_ग_लिखो_reg32(isp116x, HCCONTROL, val);
		spin_unlock_irqrestore(&isp116x->lock, flags);
		/* Wait क्रम devices to suspend */
		msleep(5);
		अवरोध;
	हाल HCCONTROL_USB_RESUME:
		isp116x_ग_लिखो_reg32(isp116x, HCCONTROL,
				    (val & ~HCCONTROL_HCFS) |
				    HCCONTROL_USB_RESET);
		fallthrough;
	हाल HCCONTROL_USB_RESET:
		ret = -EBUSY;
		fallthrough;
	शेष:		/* HCCONTROL_USB_SUSPEND */
		spin_unlock_irqrestore(&isp116x->lock, flags);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक isp116x_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp116x *isp116x = hcd_to_isp116x(hcd);
	u32 val;

	msleep(5);
	spin_lock_irq(&isp116x->lock);

	val = isp116x_पढ़ो_reg32(isp116x, HCCONTROL);
	चयन (val & HCCONTROL_HCFS) अणु
	हाल HCCONTROL_USB_SUSPEND:
		val &= ~HCCONTROL_HCFS;
		val |= HCCONTROL_USB_RESUME;
		isp116x_ग_लिखो_reg32(isp116x, HCCONTROL, val);
		अवरोध;
	हाल HCCONTROL_USB_RESUME:
		अवरोध;
	हाल HCCONTROL_USB_OPER:
		spin_unlock_irq(&isp116x->lock);
		वापस 0;
	शेष:
		/* HCCONTROL_USB_RESET: this may happen, when during
		   suspension the HC lost घातer. Reinitialize completely */
		spin_unlock_irq(&isp116x->lock);
		DBG("Chip has been reset while suspended. Reinit from scratch.\n");
		isp116x_reset(hcd);
		isp116x_start(hcd);
		isp116x_hub_control(hcd, SetPortFeature,
				    USB_PORT_FEAT_POWER, 1, शून्य, 0);
		अगर ((isp116x->rhdesca & RH_A_NDP) == 2)
			isp116x_hub_control(hcd, SetPortFeature,
					    USB_PORT_FEAT_POWER, 2, शून्य, 0);
		वापस 0;
	पूर्ण

	val = isp116x->rhdesca & RH_A_NDP;
	जबतक (val--) अणु
		u32 stat =
		    isp116x_पढ़ो_reg32(isp116x, val ? HCRHPORT2 : HCRHPORT1);
		/* क्रमce global, not selective, resume */
		अगर (!(stat & RH_PS_PSS))
			जारी;
		DBG("%s: Resuming port %d\n", __func__, val);
		isp116x_ग_लिखो_reg32(isp116x, RH_PS_POCI, val
				    ? HCRHPORT2 : HCRHPORT1);
	पूर्ण
	spin_unlock_irq(&isp116x->lock);

	hcd->state = HC_STATE_RESUMING;
	msleep(USB_RESUME_TIMEOUT);

	/* Go operational */
	spin_lock_irq(&isp116x->lock);
	val = isp116x_पढ़ो_reg32(isp116x, HCCONTROL);
	isp116x_ग_लिखो_reg32(isp116x, HCCONTROL,
			    (val & ~HCCONTROL_HCFS) | HCCONTROL_USB_OPER);
	spin_unlock_irq(&isp116x->lock);
	hcd->state = HC_STATE_RUNNING;

	वापस 0;
पूर्ण

#अन्यथा

#घोषणा	isp116x_bus_suspend	शून्य
#घोषणा	isp116x_bus_resume	शून्य

#पूर्ण_अगर

अटल स्थिर काष्ठा hc_driver isp116x_hc_driver = अणु
	.description = hcd_name,
	.product_desc = "ISP116x Host Controller",
	.hcd_priv_size = माप(काष्ठा isp116x),

	.irq = isp116x_irq,
	.flags = HCD_USB11,

	.reset = isp116x_reset,
	.start = isp116x_start,
	.stop = isp116x_stop,

	.urb_enqueue = isp116x_urb_enqueue,
	.urb_dequeue = isp116x_urb_dequeue,
	.endpoपूर्णांक_disable = isp116x_endpoपूर्णांक_disable,

	.get_frame_number = isp116x_get_frame,

	.hub_status_data = isp116x_hub_status_data,
	.hub_control = isp116x_hub_control,
	.bus_suspend = isp116x_bus_suspend,
	.bus_resume = isp116x_bus_resume,
पूर्ण;

/*----------------------------------------------------------------*/

अटल पूर्णांक isp116x_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा isp116x *isp116x;
	काष्ठा resource *res;

	अगर (!hcd)
		वापस 0;
	isp116x = hcd_to_isp116x(hcd);
	हटाओ_debug_file(isp116x);
	usb_हटाओ_hcd(hcd);

	iounmap(isp116x->data_reg);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	release_mem_region(res->start, 2);
	iounmap(isp116x->addr_reg);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, 2);

	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

अटल पूर्णांक isp116x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा isp116x *isp116x;
	काष्ठा resource *addr, *data, *ires;
	व्योम __iomem *addr_reg;
	व्योम __iomem *data_reg;
	पूर्णांक irq;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ irqflags;

	अगर (usb_disabled())
		वापस -ENODEV;

	अगर (pdev->num_resources < 3) अणु
		ret = -ENODEV;
		जाओ err1;
	पूर्ण

	data = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	addr = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	ires = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);

	अगर (!addr || !data || !ires) अणु
		ret = -ENODEV;
		जाओ err1;
	पूर्ण

	irq = ires->start;
	irqflags = ires->flags & IRQF_TRIGGER_MASK;

	अगर (!request_mem_region(addr->start, 2, hcd_name)) अणु
		ret = -EBUSY;
		जाओ err1;
	पूर्ण
	addr_reg = ioremap(addr->start, resource_size(addr));
	अगर (addr_reg == शून्य) अणु
		ret = -ENOMEM;
		जाओ err2;
	पूर्ण
	अगर (!request_mem_region(data->start, 2, hcd_name)) अणु
		ret = -EBUSY;
		जाओ err3;
	पूर्ण
	data_reg = ioremap(data->start, resource_size(data));
	अगर (data_reg == शून्य) अणु
		ret = -ENOMEM;
		जाओ err4;
	पूर्ण

	/* allocate and initialize hcd */
	hcd = usb_create_hcd(&isp116x_hc_driver, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd) अणु
		ret = -ENOMEM;
		जाओ err5;
	पूर्ण
	/* this rsrc_start is bogus */
	hcd->rsrc_start = addr->start;
	isp116x = hcd_to_isp116x(hcd);
	isp116x->data_reg = data_reg;
	isp116x->addr_reg = addr_reg;
	spin_lock_init(&isp116x->lock);
	INIT_LIST_HEAD(&isp116x->async);
	isp116x->board = dev_get_platdata(&pdev->dev);

	अगर (!isp116x->board) अणु
		ERR("Platform data structure not initialized\n");
		ret = -ENODEV;
		जाओ err6;
	पूर्ण
	अगर (isp116x_check_platक्रमm_delay(isp116x)) अणु
		ERR("USE_PLATFORM_DELAY defined, but delay function not "
		    "implemented.\n");
		ERR("See comments in drivers/usb/host/isp116x-hcd.c\n");
		ret = -ENODEV;
		जाओ err6;
	पूर्ण

	ret = usb_add_hcd(hcd, irq, irqflags);
	अगर (ret)
		जाओ err6;

	device_wakeup_enable(hcd->self.controller);

	create_debug_file(isp116x);

	वापस 0;

      err6:
	usb_put_hcd(hcd);
      err5:
	iounmap(data_reg);
      err4:
	release_mem_region(data->start, 2);
      err3:
	iounmap(addr_reg);
      err2:
	release_mem_region(addr->start, 2);
      err1:
	ERR("init error, %d\n", ret);
	वापस ret;
पूर्ण

#अगर_घोषित	CONFIG_PM
/*
  Suspend of platक्रमm device
*/
अटल पूर्णांक isp116x_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	VDBG("%s: state %x\n", __func__, state.event);
	वापस 0;
पूर्ण

/*
  Resume platक्रमm device
*/
अटल पूर्णांक isp116x_resume(काष्ठा platक्रमm_device *dev)
अणु
	VDBG("%s\n", __func__);
	वापस 0;
पूर्ण

#अन्यथा

#घोषणा	isp116x_suspend    शून्य
#घोषणा	isp116x_resume     शून्य

#पूर्ण_अगर

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:isp116x-hcd");

अटल काष्ठा platक्रमm_driver isp116x_driver = अणु
	.probe = isp116x_probe,
	.हटाओ = isp116x_हटाओ,
	.suspend = isp116x_suspend,
	.resume = isp116x_resume,
	.driver = अणु
		.name = hcd_name,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(isp116x_driver);
