<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ISP1362 HCD (Host Controller Driver) क्रम USB.
 *
 * Copyright (C) 2005 Lothar Wassmann <LW@KARO-electronics.de>
 *
 * Derived from the SL811 HCD, rewritten क्रम ISP116x.
 * Copyright (C) 2005 Olav Kongas <ok@artecdesign.ee>
 *
 * Portions:
 * Copyright (C) 2004 Psion Teklogix (क्रम NetBook PRO)
 * Copyright (C) 2004 David Brownell
 */

/*
 * The ISP1362 chip requires a large delay (300ns and 462ns) between
 * accesses to the address and data रेजिस्टर.
 * The following timing options exist:
 *
 * 1. Configure your memory controller to add such delays अगर it can (the best)
 * 2. Implement platक्रमm-specअगरic delay function possibly
 *    combined with configuring the memory controller; see
 *    include/linux/usb_isp1362.h क्रम more info.
 * 3. Use ndelay (easiest, poorest).
 *
 * Use the corresponding macros USE_PLATFORM_DELAY and USE_NDELAY in the
 * platक्रमm specअगरic section of isp1362.h to select the appropriate variant.
 *
 * Also note that according to the Philips "ISP1362 Errata" करोcument
 * Rev 1.00 from 27 May data corruption may occur when the #WR संकेत
 * is reनिश्चितed (even with #CS deनिश्चितed) within 132ns after a
 * ग_लिखो cycle to any controller रेजिस्टर. If the hardware करोesn't
 * implement the recommended fix (gating the #WR with #CS) software
 * must ensure that no further ग_लिखो cycle (not necessarily to the chip!)
 * is issued by the CPU within this पूर्णांकerval.

 * For PXA25x this can be ensured by using VLIO with the maximum
 * recovery समय (MSCx = 0x7f8c) with a memory घड़ी of 99.53 MHz.
 */

#अघोषित ISP1362_DEBUG

/*
 * The PXA255 UDC apparently करोesn't handle GET_STATUS, GET_CONFIG and
 * GET_INTERFACE requests correctly when the SETUP and DATA stages of the
 * requests are carried out in separate frames. This will delay any SETUP
 * packets until the start of the next frame so that this situation is
 * unlikely to occur (and makes usbtest happy running with a PXA255 target
 * device).
 */
#अघोषित BUGGY_PXA2XX_UDC_USBTEST

#अघोषित PTD_TRACE
#अघोषित URB_TRACE
#अघोषित VERBOSE
#अघोषित REGISTERS

/* This enables a memory test on the ISP1362 chip memory to make sure the
 * chip access timing is correct.
 */
#अघोषित CHIP_BUFFER_TEST

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/isp1362.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

अटल पूर्णांक dbg_level;
#अगर_घोषित ISP1362_DEBUG
module_param(dbg_level, पूर्णांक, 0644);
#अन्यथा
module_param(dbg_level, पूर्णांक, 0);
#पूर्ण_अगर

#समावेश "../core/usb.h"
#समावेश "isp1362.h"


#घोषणा DRIVER_VERSION	"2005-04-04"
#घोषणा DRIVER_DESC	"ISP1362 USB Host Controller Driver"

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल स्थिर अक्षर hcd_name[] = "isp1362-hcd";

अटल व्योम isp1362_hc_stop(काष्ठा usb_hcd *hcd);
अटल पूर्णांक isp1362_hc_start(काष्ठा usb_hcd *hcd);

/*-------------------------------------------------------------------------*/

/*
 * When called from the पूर्णांकerrupthandler only isp1362_hcd->irqenb is modअगरied,
 * since the पूर्णांकerrupt handler will ग_लिखो isp1362_hcd->irqenb to HCuPINT upon
 * completion.
 * We करोn't need a 'disable' counterpart, since पूर्णांकerrupts will be disabled
 * only by the पूर्णांकerrupt handler.
 */
अटल अंतरभूत व्योम isp1362_enable_पूर्णांक(काष्ठा isp1362_hcd *isp1362_hcd, u16 mask)
अणु
	अगर ((isp1362_hcd->irqenb | mask) == isp1362_hcd->irqenb)
		वापस;
	अगर (mask & ~isp1362_hcd->irqenb)
		isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINT, mask & ~isp1362_hcd->irqenb);
	isp1362_hcd->irqenb |= mask;
	अगर (isp1362_hcd->irq_active)
		वापस;
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINTENB, isp1362_hcd->irqenb);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत काष्ठा isp1362_ep_queue *get_ptd_queue(काष्ठा isp1362_hcd *isp1362_hcd,
						     u16 offset)
अणु
	काष्ठा isp1362_ep_queue *epq = शून्य;

	अगर (offset < isp1362_hcd->istl_queue[1].buf_start)
		epq = &isp1362_hcd->istl_queue[0];
	अन्यथा अगर (offset < isp1362_hcd->पूर्णांकl_queue.buf_start)
		epq = &isp1362_hcd->istl_queue[1];
	अन्यथा अगर (offset < isp1362_hcd->atl_queue.buf_start)
		epq = &isp1362_hcd->पूर्णांकl_queue;
	अन्यथा अगर (offset < isp1362_hcd->atl_queue.buf_start +
		   isp1362_hcd->atl_queue.buf_size)
		epq = &isp1362_hcd->atl_queue;

	अगर (epq)
		DBG(1, "%s: PTD $%04x is on %s queue\n", __func__, offset, epq->name);
	अन्यथा
		pr_warn("%s: invalid PTD $%04x\n", __func__, offset);

	वापस epq;
पूर्ण

अटल अंतरभूत पूर्णांक get_ptd_offset(काष्ठा isp1362_ep_queue *epq, u8 index)
अणु
	पूर्णांक offset;

	अगर (index * epq->blk_size > epq->buf_size) अणु
		pr_warn("%s: Bad %s index %d(%d)\n",
			__func__, epq->name, index,
			epq->buf_size / epq->blk_size);
		वापस -EINVAL;
	पूर्ण
	offset = epq->buf_start + index * epq->blk_size;
	DBG(3, "%s: %s PTD[%02x] # %04x\n", __func__, epq->name, index, offset);

	वापस offset;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत u16 max_transfer_size(काष्ठा isp1362_ep_queue *epq, माप_प्रकार size,
				    पूर्णांक mps)
अणु
	u16 xfer_size = min_t(माप_प्रकार, MAX_XFER_SIZE, size);

	xfer_size = min_t(माप_प्रकार, xfer_size, epq->buf_avail * epq->blk_size - PTD_HEADER_SIZE);
	अगर (xfer_size < size && xfer_size % mps)
		xfer_size -= xfer_size % mps;

	वापस xfer_size;
पूर्ण

अटल पूर्णांक claim_ptd_buffers(काष्ठा isp1362_ep_queue *epq,
			     काष्ठा isp1362_ep *ep, u16 len)
अणु
	पूर्णांक ptd_offset = -EINVAL;
	पूर्णांक num_ptds = ((len + PTD_HEADER_SIZE - 1) / epq->blk_size) + 1;
	पूर्णांक found;

	BUG_ON(len > epq->buf_size);

	अगर (!epq->buf_avail)
		वापस -ENOMEM;

	अगर (ep->num_ptds)
		pr_err("%s: %s len %d/%d num_ptds %d buf_map %08lx skip_map %08lx\n", __func__,
		    epq->name, len, epq->blk_size, num_ptds, epq->buf_map, epq->skip_map);
	BUG_ON(ep->num_ptds != 0);

	found = biपंचांगap_find_next_zero_area(&epq->buf_map, epq->buf_count, 0,
						num_ptds, 0);
	अगर (found >= epq->buf_count)
		वापस -EOVERFLOW;

	DBG(1, "%s: Found %d PTDs[%d] for %d/%d byte\n", __func__,
	    num_ptds, found, len, (पूर्णांक)(epq->blk_size - PTD_HEADER_SIZE));
	ptd_offset = get_ptd_offset(epq, found);
	WARN_ON(ptd_offset < 0);
	ep->ptd_offset = ptd_offset;
	ep->num_ptds += num_ptds;
	epq->buf_avail -= num_ptds;
	BUG_ON(epq->buf_avail > epq->buf_count);
	ep->ptd_index = found;
	biपंचांगap_set(&epq->buf_map, found, num_ptds);
	DBG(1, "%s: Done %s PTD[%d] $%04x, avail %d count %d claimed %d %08lx:%08lx\n",
	    __func__, epq->name, ep->ptd_index, ep->ptd_offset,
	    epq->buf_avail, epq->buf_count, num_ptds, epq->buf_map, epq->skip_map);

	वापस found;
पूर्ण

अटल अंतरभूत व्योम release_ptd_buffers(काष्ठा isp1362_ep_queue *epq, काष्ठा isp1362_ep *ep)
अणु
	पूर्णांक last = ep->ptd_index + ep->num_ptds;

	अगर (last > epq->buf_count)
		pr_err("%s: ep %p req %d len %d %s PTD[%d] $%04x num_ptds %d buf_count %d buf_avail %d buf_map %08lx skip_map %08lx\n",
		    __func__, ep, ep->num_req, ep->length, epq->name, ep->ptd_index,
		    ep->ptd_offset, ep->num_ptds, epq->buf_count, epq->buf_avail,
		    epq->buf_map, epq->skip_map);
	BUG_ON(last > epq->buf_count);

	biपंचांगap_clear(&epq->buf_map, ep->ptd_index, ep->num_ptds);
	biपंचांगap_set(&epq->skip_map, ep->ptd_index, ep->num_ptds);
	epq->buf_avail += ep->num_ptds;
	epq->ptd_count--;

	BUG_ON(epq->buf_avail > epq->buf_count);
	BUG_ON(epq->ptd_count > epq->buf_count);

	DBG(1, "%s: Done %s PTDs $%04x released %d avail %d count %d\n",
	    __func__, epq->name,
	    ep->ptd_offset, ep->num_ptds, epq->buf_avail, epq->buf_count);
	DBG(1, "%s: buf_map %08lx skip_map %08lx\n", __func__,
	    epq->buf_map, epq->skip_map);

	ep->num_ptds = 0;
	ep->ptd_offset = -EINVAL;
	ep->ptd_index = -EINVAL;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
  Set up PTD's.
*/
अटल व्योम prepare_ptd(काष्ठा isp1362_hcd *isp1362_hcd, काष्ठा urb *urb,
			काष्ठा isp1362_ep *ep, काष्ठा isp1362_ep_queue *epq,
			u16 fno)
अणु
	काष्ठा ptd *ptd;
	पूर्णांक toggle;
	पूर्णांक dir;
	u16 len;
	माप_प्रकार buf_len = urb->transfer_buffer_length - urb->actual_length;

	DBG(3, "%s: %s ep %p\n", __func__, epq->name, ep);

	ptd = &ep->ptd;

	ep->data = (अचिन्हित अक्षर *)urb->transfer_buffer + urb->actual_length;

	चयन (ep->nextpid) अणु
	हाल USB_PID_IN:
		toggle = usb_gettoggle(urb->dev, ep->epnum, 0);
		dir = PTD_सूची_IN;
		अगर (usb_pipecontrol(urb->pipe)) अणु
			len = min_t(माप_प्रकार, ep->maxpacket, buf_len);
		पूर्ण अन्यथा अगर (usb_pipeisoc(urb->pipe)) अणु
			len = min_t(माप_प्रकार, urb->iso_frame_desc[fno].length, MAX_XFER_SIZE);
			ep->data = urb->transfer_buffer + urb->iso_frame_desc[fno].offset;
		पूर्ण अन्यथा
			len = max_transfer_size(epq, buf_len, ep->maxpacket);
		DBG(1, "%s: IN    len %d/%d/%d from URB\n", __func__, len, ep->maxpacket,
		    (पूर्णांक)buf_len);
		अवरोध;
	हाल USB_PID_OUT:
		toggle = usb_gettoggle(urb->dev, ep->epnum, 1);
		dir = PTD_सूची_OUT;
		अगर (usb_pipecontrol(urb->pipe))
			len = min_t(माप_प्रकार, ep->maxpacket, buf_len);
		अन्यथा अगर (usb_pipeisoc(urb->pipe))
			len = min_t(माप_प्रकार, urb->iso_frame_desc[0].length, MAX_XFER_SIZE);
		अन्यथा
			len = max_transfer_size(epq, buf_len, ep->maxpacket);
		अगर (len == 0)
			pr_info("%s: Sending ZERO packet: %d\n", __func__,
			     urb->transfer_flags & URB_ZERO_PACKET);
		DBG(1, "%s: OUT   len %d/%d/%d from URB\n", __func__, len, ep->maxpacket,
		    (पूर्णांक)buf_len);
		अवरोध;
	हाल USB_PID_SETUP:
		toggle = 0;
		dir = PTD_सूची_SETUP;
		len = माप(काष्ठा usb_ctrlrequest);
		DBG(1, "%s: SETUP len %d\n", __func__, len);
		ep->data = urb->setup_packet;
		अवरोध;
	हाल USB_PID_ACK:
		toggle = 1;
		len = 0;
		dir = (urb->transfer_buffer_length && usb_pipein(urb->pipe)) ?
			PTD_सूची_OUT : PTD_सूची_IN;
		DBG(1, "%s: ACK   len %d\n", __func__, len);
		अवरोध;
	शेष:
		toggle = dir = len = 0;
		pr_err("%s@%d: ep->nextpid %02x\n", __func__, __LINE__, ep->nextpid);
		BUG_ON(1);
	पूर्ण

	ep->length = len;
	अगर (!len)
		ep->data = शून्य;

	ptd->count = PTD_CC_MSK | PTD_ACTIVE_MSK | PTD_TOGGLE(toggle);
	ptd->mps = PTD_MPS(ep->maxpacket) | PTD_SPD(urb->dev->speed == USB_SPEED_LOW) |
		PTD_EP(ep->epnum);
	ptd->len = PTD_LEN(len) | PTD_सूची(dir);
	ptd->faddr = PTD_FA(usb_pipedevice(urb->pipe));

	अगर (usb_pipeपूर्णांक(urb->pipe)) अणु
		ptd->faddr |= PTD_SF_INT(ep->branch);
		ptd->faddr |= PTD_PR(ep->पूर्णांकerval ? __ffs(ep->पूर्णांकerval) : 0);
	पूर्ण
	अगर (usb_pipeisoc(urb->pipe))
		ptd->faddr |= PTD_SF_ISO(fno);

	DBG(1, "%s: Finished\n", __func__);
पूर्ण

अटल व्योम isp1362_ग_लिखो_ptd(काष्ठा isp1362_hcd *isp1362_hcd, काष्ठा isp1362_ep *ep,
			      काष्ठा isp1362_ep_queue *epq)
अणु
	काष्ठा ptd *ptd = &ep->ptd;
	पूर्णांक len = PTD_GET_सूची(ptd) == PTD_सूची_IN ? 0 : ep->length;

	prefetch(ptd);
	isp1362_ग_लिखो_buffer(isp1362_hcd, ptd, ep->ptd_offset, PTD_HEADER_SIZE);
	अगर (len)
		isp1362_ग_लिखो_buffer(isp1362_hcd, ep->data,
				     ep->ptd_offset + PTD_HEADER_SIZE, len);

	dump_ptd(ptd);
	dump_ptd_out_data(ptd, ep->data);
पूर्ण

अटल व्योम isp1362_पढ़ो_ptd(काष्ठा isp1362_hcd *isp1362_hcd, काष्ठा isp1362_ep *ep,
			     काष्ठा isp1362_ep_queue *epq)
अणु
	काष्ठा ptd *ptd = &ep->ptd;
	पूर्णांक act_len;

	WARN_ON(list_empty(&ep->active));
	BUG_ON(ep->ptd_offset < 0);

	list_del_init(&ep->active);
	DBG(1, "%s: ep %p removed from active list %p\n", __func__, ep, &epq->active);

	prefetchw(ptd);
	isp1362_पढ़ो_buffer(isp1362_hcd, ptd, ep->ptd_offset, PTD_HEADER_SIZE);
	dump_ptd(ptd);
	act_len = PTD_GET_COUNT(ptd);
	अगर (PTD_GET_सूची(ptd) != PTD_सूची_IN || act_len == 0)
		वापस;
	अगर (act_len > ep->length)
		pr_err("%s: ep %p PTD $%04x act_len %d ep->length %d\n", __func__, ep,
			 ep->ptd_offset, act_len, ep->length);
	BUG_ON(act_len > ep->length);
	/* Only transfer the amount of data that has actually been overwritten
	 * in the chip buffer. We करोn't want any data that doesn't beदीर्घ to the
	 * transfer to leak out of the chip to the callers transfer buffer!
	 */
	prefetchw(ep->data);
	isp1362_पढ़ो_buffer(isp1362_hcd, ep->data,
			    ep->ptd_offset + PTD_HEADER_SIZE, act_len);
	dump_ptd_in_data(ptd, ep->data);
पूर्ण

/*
 * INT PTDs will stay in the chip until data is available.
 * This function will हटाओ a PTD from the chip when the URB is dequeued.
 * Must be called with the spinlock held and IRQs disabled
 */
अटल व्योम हटाओ_ptd(काष्ठा isp1362_hcd *isp1362_hcd, काष्ठा isp1362_ep *ep)

अणु
	पूर्णांक index;
	काष्ठा isp1362_ep_queue *epq;

	DBG(1, "%s: ep %p PTD[%d] $%04x\n", __func__, ep, ep->ptd_index, ep->ptd_offset);
	BUG_ON(ep->ptd_offset < 0);

	epq = get_ptd_queue(isp1362_hcd, ep->ptd_offset);
	BUG_ON(!epq);

	/* put ep in हटाओ_list क्रम cleanup */
	WARN_ON(!list_empty(&ep->हटाओ_list));
	list_add_tail(&ep->हटाओ_list, &isp1362_hcd->हटाओ_list);
	/* let SOF पूर्णांकerrupt handle the cleanup */
	isp1362_enable_पूर्णांक(isp1362_hcd, HCuPINT_SOF);

	index = ep->ptd_index;
	अगर (index < 0)
		/* ISO queues करोn't have SKIP रेजिस्टरs */
		वापस;

	DBG(1, "%s: Disabling PTD[%02x] $%04x %08lx|%08x\n", __func__,
	    index, ep->ptd_offset, epq->skip_map, 1 << index);

	/* prevent further processing of PTD (will be effective after next SOF) */
	epq->skip_map |= 1 << index;
	अगर (epq == &isp1362_hcd->atl_queue) अणु
		DBG(2, "%s: ATLSKIP = %08x -> %08lx\n", __func__,
		    isp1362_पढ़ो_reg32(isp1362_hcd, HCATLSKIP), epq->skip_map);
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCATLSKIP, epq->skip_map);
		अगर (~epq->skip_map == 0)
			isp1362_clr_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ATL_ACTIVE);
	पूर्ण अन्यथा अगर (epq == &isp1362_hcd->पूर्णांकl_queue) अणु
		DBG(2, "%s: INTLSKIP = %08x -> %08lx\n", __func__,
		    isp1362_पढ़ो_reg32(isp1362_hcd, HCINTLSKIP), epq->skip_map);
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTLSKIP, epq->skip_map);
		अगर (~epq->skip_map == 0)
			isp1362_clr_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_INTL_ACTIVE);
	पूर्ण
पूर्ण

/*
  Take करोne or failed requests out of schedule. Give back
  processed urbs.
*/
अटल व्योम finish_request(काष्ठा isp1362_hcd *isp1362_hcd, काष्ठा isp1362_ep *ep,
			   काष्ठा urb *urb, पूर्णांक status)
     __releases(isp1362_hcd->lock)
     __acquires(isp1362_hcd->lock)
अणु
	urb->hcpriv = शून्य;
	ep->error_count = 0;

	अगर (usb_pipecontrol(urb->pipe))
		ep->nextpid = USB_PID_SETUP;

	URB_DBG("%s: req %d FA %d ep%d%s %s: len %d/%d %s stat %d\n", __func__,
		ep->num_req, usb_pipedevice(urb->pipe),
		usb_pipeendpoपूर्णांक(urb->pipe),
		!usb_pipein(urb->pipe) ? "out" : "in",
		usb_pipecontrol(urb->pipe) ? "ctrl" :
			usb_pipeपूर्णांक(urb->pipe) ? "int" :
			usb_pipebulk(urb->pipe) ? "bulk" :
			"iso",
		urb->actual_length, urb->transfer_buffer_length,
		!(urb->transfer_flags & URB_SHORT_NOT_OK) ?
		"short_ok" : "", urb->status);


	usb_hcd_unlink_urb_from_ep(isp1362_hcd_to_hcd(isp1362_hcd), urb);
	spin_unlock(&isp1362_hcd->lock);
	usb_hcd_giveback_urb(isp1362_hcd_to_hcd(isp1362_hcd), urb, status);
	spin_lock(&isp1362_hcd->lock);

	/* take idle endpoपूर्णांकs out of the schedule right away */
	अगर (!list_empty(&ep->hep->urb_list))
		वापस;

	/* async deschedule */
	अगर (!list_empty(&ep->schedule)) अणु
		list_del_init(&ep->schedule);
		वापस;
	पूर्ण


	अगर (ep->पूर्णांकerval) अणु
		/* periodic deschedule */
		DBG(1, "deschedule qh%d/%p branch %d load %d bandwidth %d -> %d\n", ep->पूर्णांकerval,
		    ep, ep->branch, ep->load,
		    isp1362_hcd->load[ep->branch],
		    isp1362_hcd->load[ep->branch] - ep->load);
		isp1362_hcd->load[ep->branch] -= ep->load;
		ep->branch = PERIODIC_SIZE;
	पूर्ण
पूर्ण

/*
 * Analyze transfer results, handle partial transfers and errors
*/
अटल व्योम postproc_ep(काष्ठा isp1362_hcd *isp1362_hcd, काष्ठा isp1362_ep *ep)
अणु
	काष्ठा urb *urb = get_urb(ep);
	काष्ठा usb_device *udev;
	काष्ठा ptd *ptd;
	पूर्णांक लघु_ok;
	u16 len;
	पूर्णांक urbstat = -EINPROGRESS;
	u8 cc;

	DBG(2, "%s: ep %p req %d\n", __func__, ep, ep->num_req);

	udev = urb->dev;
	ptd = &ep->ptd;
	cc = PTD_GET_CC(ptd);
	अगर (cc == PTD_NOTACCESSED) अणु
		pr_err("%s: req %d PTD %p Untouched by ISP1362\n", __func__,
		    ep->num_req, ptd);
		cc = PTD_DEVNOTRESP;
	पूर्ण

	लघु_ok = !(urb->transfer_flags & URB_SHORT_NOT_OK);
	len = urb->transfer_buffer_length - urb->actual_length;

	/* Data underrun is special. For allowed underrun
	   we clear the error and जारी as normal. For
	   क्रमbidden underrun we finish the DATA stage
	   immediately जबतक क्रम control transfer,
	   we करो a STATUS stage.
	*/
	अगर (cc == PTD_DATAUNDERRUN) अणु
		अगर (लघु_ok) अणु
			DBG(1, "%s: req %d Allowed data underrun short_%sok %d/%d/%d byte\n",
			    __func__, ep->num_req, लघु_ok ? "" : "not_",
			    PTD_GET_COUNT(ptd), ep->maxpacket, len);
			cc = PTD_CC_NOERROR;
			urbstat = 0;
		पूर्ण अन्यथा अणु
			DBG(1, "%s: req %d Data Underrun %s nextpid %02x short_%sok %d/%d/%d byte\n",
			    __func__, ep->num_req,
			    usb_pipein(urb->pipe) ? "IN" : "OUT", ep->nextpid,
			    लघु_ok ? "" : "not_",
			    PTD_GET_COUNT(ptd), ep->maxpacket, len);
			/* save the data underrun error code क्रम later and
			 * proceed with the status stage
			 */
			urb->actual_length += PTD_GET_COUNT(ptd);
			अगर (usb_pipecontrol(urb->pipe)) अणु
				ep->nextpid = USB_PID_ACK;
				BUG_ON(urb->actual_length > urb->transfer_buffer_length);

				अगर (urb->status == -EINPROGRESS)
					urb->status = cc_to_error[PTD_DATAUNDERRUN];
			पूर्ण अन्यथा अणु
				usb_settoggle(udev, ep->epnum, ep->nextpid == USB_PID_OUT,
					      PTD_GET_TOGGLE(ptd));
				urbstat = cc_to_error[PTD_DATAUNDERRUN];
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (cc != PTD_CC_NOERROR) अणु
		अगर (++ep->error_count >= 3 || cc == PTD_CC_STALL || cc == PTD_DATAOVERRUN) अणु
			urbstat = cc_to_error[cc];
			DBG(1, "%s: req %d nextpid %02x, status %d, error %d, error_count %d\n",
			    __func__, ep->num_req, ep->nextpid, urbstat, cc,
			    ep->error_count);
		पूर्ण
		जाओ out;
	पूर्ण

	चयन (ep->nextpid) अणु
	हाल USB_PID_OUT:
		अगर (PTD_GET_COUNT(ptd) != ep->length)
			pr_err("%s: count=%d len=%d\n", __func__,
			   PTD_GET_COUNT(ptd), ep->length);
		BUG_ON(PTD_GET_COUNT(ptd) != ep->length);
		urb->actual_length += ep->length;
		BUG_ON(urb->actual_length > urb->transfer_buffer_length);
		usb_settoggle(udev, ep->epnum, 1, PTD_GET_TOGGLE(ptd));
		अगर (urb->actual_length == urb->transfer_buffer_length) अणु
			DBG(3, "%s: req %d xfer complete %d/%d status %d -> 0\n", __func__,
			    ep->num_req, len, ep->maxpacket, urbstat);
			अगर (usb_pipecontrol(urb->pipe)) अणु
				DBG(3, "%s: req %d %s Wait for ACK\n", __func__,
				    ep->num_req,
				    usb_pipein(urb->pipe) ? "IN" : "OUT");
				ep->nextpid = USB_PID_ACK;
			पूर्ण अन्यथा अणु
				अगर (len % ep->maxpacket ||
				    !(urb->transfer_flags & URB_ZERO_PACKET)) अणु
					urbstat = 0;
					DBG(3, "%s: req %d URB %s status %d count %d/%d/%d\n",
					    __func__, ep->num_req, usb_pipein(urb->pipe) ? "IN" : "OUT",
					    urbstat, len, ep->maxpacket, urb->actual_length);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल USB_PID_IN:
		len = PTD_GET_COUNT(ptd);
		BUG_ON(len > ep->length);
		urb->actual_length += len;
		BUG_ON(urb->actual_length > urb->transfer_buffer_length);
		usb_settoggle(udev, ep->epnum, 0, PTD_GET_TOGGLE(ptd));
		/* अगर transfer completed or (allowed) data underrun */
		अगर ((urb->transfer_buffer_length == urb->actual_length) ||
		    len % ep->maxpacket) अणु
			DBG(3, "%s: req %d xfer complete %d/%d status %d -> 0\n", __func__,
			    ep->num_req, len, ep->maxpacket, urbstat);
			अगर (usb_pipecontrol(urb->pipe)) अणु
				DBG(3, "%s: req %d %s Wait for ACK\n", __func__,
				    ep->num_req,
				    usb_pipein(urb->pipe) ? "IN" : "OUT");
				ep->nextpid = USB_PID_ACK;
			पूर्ण अन्यथा अणु
				urbstat = 0;
				DBG(3, "%s: req %d URB %s status %d count %d/%d/%d\n",
				    __func__, ep->num_req, usb_pipein(urb->pipe) ? "IN" : "OUT",
				    urbstat, len, ep->maxpacket, urb->actual_length);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल USB_PID_SETUP:
		अगर (urb->transfer_buffer_length == urb->actual_length) अणु
			ep->nextpid = USB_PID_ACK;
		पूर्ण अन्यथा अगर (usb_pipeout(urb->pipe)) अणु
			usb_settoggle(udev, 0, 1, 1);
			ep->nextpid = USB_PID_OUT;
		पूर्ण अन्यथा अणु
			usb_settoggle(udev, 0, 0, 1);
			ep->nextpid = USB_PID_IN;
		पूर्ण
		अवरोध;
	हाल USB_PID_ACK:
		DBG(3, "%s: req %d got ACK %d -> 0\n", __func__, ep->num_req,
		    urbstat);
		WARN_ON(urbstat != -EINPROGRESS);
		urbstat = 0;
		ep->nextpid = 0;
		अवरोध;
	शेष:
		BUG_ON(1);
	पूर्ण

 out:
	अगर (urbstat != -EINPROGRESS) अणु
		DBG(2, "%s: Finishing ep %p req %d urb %p status %d\n", __func__,
		    ep, ep->num_req, urb, urbstat);
		finish_request(isp1362_hcd, ep, urb, urbstat);
	पूर्ण
पूर्ण

अटल व्योम finish_unlinks(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	काष्ठा isp1362_ep *ep;
	काष्ठा isp1362_ep *पंचांगp;

	list_क्रम_each_entry_safe(ep, पंचांगp, &isp1362_hcd->हटाओ_list, हटाओ_list) अणु
		काष्ठा isp1362_ep_queue *epq =
			get_ptd_queue(isp1362_hcd, ep->ptd_offset);
		पूर्णांक index = ep->ptd_index;

		BUG_ON(epq == शून्य);
		अगर (index >= 0) अणु
			DBG(1, "%s: remove PTD[%d] $%04x\n", __func__, index, ep->ptd_offset);
			BUG_ON(ep->num_ptds == 0);
			release_ptd_buffers(epq, ep);
		पूर्ण
		अगर (!list_empty(&ep->hep->urb_list)) अणु
			काष्ठा urb *urb = get_urb(ep);

			DBG(1, "%s: Finishing req %d ep %p from remove_list\n", __func__,
			    ep->num_req, ep);
			finish_request(isp1362_hcd, ep, urb, -ESHUTDOWN);
		पूर्ण
		WARN_ON(list_empty(&ep->active));
		अगर (!list_empty(&ep->active)) अणु
			list_del_init(&ep->active);
			DBG(1, "%s: ep %p removed from active list\n", __func__, ep);
		पूर्ण
		list_del_init(&ep->हटाओ_list);
		DBG(1, "%s: ep %p removed from remove_list\n", __func__, ep);
	पूर्ण
	DBG(1, "%s: Done\n", __func__);
पूर्ण

अटल अंतरभूत व्योम enable_atl_transfers(काष्ठा isp1362_hcd *isp1362_hcd, पूर्णांक count)
अणु
	अगर (count > 0) अणु
		अगर (count < isp1362_hcd->atl_queue.ptd_count)
			isp1362_ग_लिखो_reg16(isp1362_hcd, HCATLDTC, count);
		isp1362_enable_पूर्णांक(isp1362_hcd, HCuPINT_ATL);
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCATLSKIP, isp1362_hcd->atl_queue.skip_map);
		isp1362_set_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ATL_ACTIVE);
	पूर्ण अन्यथा
		isp1362_enable_पूर्णांक(isp1362_hcd, HCuPINT_SOF);
पूर्ण

अटल अंतरभूत व्योम enable_पूर्णांकl_transfers(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	isp1362_enable_पूर्णांक(isp1362_hcd, HCuPINT_INTL);
	isp1362_set_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_INTL_ACTIVE);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTLSKIP, isp1362_hcd->पूर्णांकl_queue.skip_map);
पूर्ण

अटल अंतरभूत व्योम enable_istl_transfers(काष्ठा isp1362_hcd *isp1362_hcd, पूर्णांक flip)
अणु
	isp1362_enable_पूर्णांक(isp1362_hcd, flip ? HCuPINT_ISTL1 : HCuPINT_ISTL0);
	isp1362_set_mask16(isp1362_hcd, HCBUFSTAT, flip ?
			   HCBUFSTAT_ISTL1_FULL : HCBUFSTAT_ISTL0_FULL);
पूर्ण

अटल पूर्णांक submit_req(काष्ठा isp1362_hcd *isp1362_hcd, काष्ठा urb *urb,
		      काष्ठा isp1362_ep *ep, काष्ठा isp1362_ep_queue *epq)
अणु
	पूर्णांक index;

	prepare_ptd(isp1362_hcd, urb, ep, epq, 0);
	index = claim_ptd_buffers(epq, ep, ep->length);
	अगर (index == -ENOMEM) अणु
		DBG(1, "%s: req %d No free %s PTD available: %d, %08lx:%08lx\n", __func__,
		    ep->num_req, epq->name, ep->num_ptds, epq->buf_map, epq->skip_map);
		वापस index;
	पूर्ण अन्यथा अगर (index == -EOVERFLOW) अणु
		DBG(1, "%s: req %d Not enough space for %d byte %s PTD %d %08lx:%08lx\n",
		    __func__, ep->num_req, ep->length, epq->name, ep->num_ptds,
		    epq->buf_map, epq->skip_map);
		वापस index;
	पूर्ण अन्यथा
		BUG_ON(index < 0);
	list_add_tail(&ep->active, &epq->active);
	DBG(1, "%s: ep %p req %d len %d added to active list %p\n", __func__,
	    ep, ep->num_req, ep->length, &epq->active);
	DBG(1, "%s: Submitting %s PTD $%04x for ep %p req %d\n", __func__, epq->name,
	    ep->ptd_offset, ep, ep->num_req);
	isp1362_ग_लिखो_ptd(isp1362_hcd, ep, epq);
	__clear_bit(ep->ptd_index, &epq->skip_map);

	वापस 0;
पूर्ण

अटल व्योम start_atl_transfers(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	पूर्णांक ptd_count = 0;
	काष्ठा isp1362_ep_queue *epq = &isp1362_hcd->atl_queue;
	काष्ठा isp1362_ep *ep;
	पूर्णांक defer = 0;

	अगर (atomic_पढ़ो(&epq->finishing)) अणु
		DBG(1, "%s: finish_transfers is active for %s\n", __func__, epq->name);
		वापस;
	पूर्ण

	list_क्रम_each_entry(ep, &isp1362_hcd->async, schedule) अणु
		काष्ठा urb *urb = get_urb(ep);
		पूर्णांक ret;

		अगर (!list_empty(&ep->active)) अणु
			DBG(2, "%s: Skipping active %s ep %p\n", __func__, epq->name, ep);
			जारी;
		पूर्ण

		DBG(1, "%s: Processing %s ep %p req %d\n", __func__, epq->name,
		    ep, ep->num_req);

		ret = submit_req(isp1362_hcd, urb, ep, epq);
		अगर (ret == -ENOMEM) अणु
			defer = 1;
			अवरोध;
		पूर्ण अन्यथा अगर (ret == -EOVERFLOW) अणु
			defer = 1;
			जारी;
		पूर्ण
#अगर_घोषित BUGGY_PXA2XX_UDC_USBTEST
		defer = ep->nextpid == USB_PID_SETUP;
#पूर्ण_अगर
		ptd_count++;
	पूर्ण

	/* Aव्योम starving of endpoपूर्णांकs */
	अगर (isp1362_hcd->async.next != isp1362_hcd->async.prev) अणु
		DBG(2, "%s: Cycling ASYNC schedule %d\n", __func__, ptd_count);
		list_move(&isp1362_hcd->async, isp1362_hcd->async.next);
	पूर्ण
	अगर (ptd_count || defer)
		enable_atl_transfers(isp1362_hcd, defer ? 0 : ptd_count);

	epq->ptd_count += ptd_count;
	अगर (epq->ptd_count > epq->stat_maxptds) अणु
		epq->stat_maxptds = epq->ptd_count;
		DBG(0, "%s: max_ptds: %d\n", __func__, epq->stat_maxptds);
	पूर्ण
पूर्ण

अटल व्योम start_पूर्णांकl_transfers(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	पूर्णांक ptd_count = 0;
	काष्ठा isp1362_ep_queue *epq = &isp1362_hcd->पूर्णांकl_queue;
	काष्ठा isp1362_ep *ep;

	अगर (atomic_पढ़ो(&epq->finishing)) अणु
		DBG(1, "%s: finish_transfers is active for %s\n", __func__, epq->name);
		वापस;
	पूर्ण

	list_क्रम_each_entry(ep, &isp1362_hcd->periodic, schedule) अणु
		काष्ठा urb *urb = get_urb(ep);
		पूर्णांक ret;

		अगर (!list_empty(&ep->active)) अणु
			DBG(1, "%s: Skipping active %s ep %p\n", __func__,
			    epq->name, ep);
			जारी;
		पूर्ण

		DBG(1, "%s: Processing %s ep %p req %d\n", __func__,
		    epq->name, ep, ep->num_req);
		ret = submit_req(isp1362_hcd, urb, ep, epq);
		अगर (ret == -ENOMEM)
			अवरोध;
		अन्यथा अगर (ret == -EOVERFLOW)
			जारी;
		ptd_count++;
	पूर्ण

	अगर (ptd_count) अणु
		अटल पूर्णांक last_count;

		अगर (ptd_count != last_count) अणु
			DBG(0, "%s: ptd_count: %d\n", __func__, ptd_count);
			last_count = ptd_count;
		पूर्ण
		enable_पूर्णांकl_transfers(isp1362_hcd);
	पूर्ण

	epq->ptd_count += ptd_count;
	अगर (epq->ptd_count > epq->stat_maxptds)
		epq->stat_maxptds = epq->ptd_count;
पूर्ण

अटल अंतरभूत पूर्णांक next_ptd(काष्ठा isp1362_ep_queue *epq, काष्ठा isp1362_ep *ep)
अणु
	u16 ptd_offset = ep->ptd_offset;
	पूर्णांक num_ptds = (ep->length + PTD_HEADER_SIZE + (epq->blk_size - 1)) / epq->blk_size;

	DBG(2, "%s: PTD offset $%04x + %04x => %d * %04x -> $%04x\n", __func__, ptd_offset,
	    ep->length, num_ptds, epq->blk_size, ptd_offset + num_ptds * epq->blk_size);

	ptd_offset += num_ptds * epq->blk_size;
	अगर (ptd_offset < epq->buf_start + epq->buf_size)
		वापस ptd_offset;
	अन्यथा
		वापस -ENOMEM;
पूर्ण

अटल व्योम start_iso_transfers(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	पूर्णांक ptd_count = 0;
	पूर्णांक flip = isp1362_hcd->istl_flip;
	काष्ठा isp1362_ep_queue *epq;
	पूर्णांक ptd_offset;
	काष्ठा isp1362_ep *ep;
	काष्ठा isp1362_ep *पंचांगp;
	u16 fno = isp1362_पढ़ो_reg32(isp1362_hcd, HCFMNUM);

 fill2:
	epq = &isp1362_hcd->istl_queue[flip];
	अगर (atomic_पढ़ो(&epq->finishing)) अणु
		DBG(1, "%s: finish_transfers is active for %s\n", __func__, epq->name);
		वापस;
	पूर्ण

	अगर (!list_empty(&epq->active))
		वापस;

	ptd_offset = epq->buf_start;
	list_क्रम_each_entry_safe(ep, पंचांगp, &isp1362_hcd->isoc, schedule) अणु
		काष्ठा urb *urb = get_urb(ep);
		s16 dअगरf = fno - (u16)urb->start_frame;

		DBG(1, "%s: Processing %s ep %p\n", __func__, epq->name, ep);

		अगर (dअगरf > urb->number_of_packets) अणु
			/* समय frame क्रम this URB has elapsed */
			finish_request(isp1362_hcd, ep, urb, -EOVERFLOW);
			जारी;
		पूर्ण अन्यथा अगर (dअगरf < -1) अणु
			/* URB is not due in this frame or the next one.
			 * Comparing with '-1' instead of '0' accounts क्रम द्विगुन
			 * buffering in the ISP1362 which enables us to queue the PTD
			 * one frame ahead of समय
			 */
		पूर्ण अन्यथा अगर (dअगरf == -1) अणु
			/* submit PTD's that are due in the next frame */
			prepare_ptd(isp1362_hcd, urb, ep, epq, fno);
			अगर (ptd_offset + PTD_HEADER_SIZE + ep->length >
			    epq->buf_start + epq->buf_size) अणु
				pr_err("%s: Not enough ISO buffer space for %d byte PTD\n",
				    __func__, ep->length);
				जारी;
			पूर्ण
			ep->ptd_offset = ptd_offset;
			list_add_tail(&ep->active, &epq->active);

			ptd_offset = next_ptd(epq, ep);
			अगर (ptd_offset < 0) अणु
				pr_warn("%s: req %d No more %s PTD buffers available\n",
					__func__, ep->num_req, epq->name);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	list_क्रम_each_entry(ep, &epq->active, active) अणु
		अगर (epq->active.next == &ep->active)
			ep->ptd.mps |= PTD_LAST_MSK;
		isp1362_ग_लिखो_ptd(isp1362_hcd, ep, epq);
		ptd_count++;
	पूर्ण

	अगर (ptd_count)
		enable_istl_transfers(isp1362_hcd, flip);

	epq->ptd_count += ptd_count;
	अगर (epq->ptd_count > epq->stat_maxptds)
		epq->stat_maxptds = epq->ptd_count;

	/* check, whether the second ISTL buffer may also be filled */
	अगर (!(isp1362_पढ़ो_reg16(isp1362_hcd, HCBUFSTAT) &
	      (flip ? HCBUFSTAT_ISTL0_FULL : HCBUFSTAT_ISTL1_FULL))) अणु
		fno++;
		ptd_count = 0;
		flip = 1 - flip;
		जाओ fill2;
	पूर्ण
पूर्ण

अटल व्योम finish_transfers(काष्ठा isp1362_hcd *isp1362_hcd, अचिन्हित दीर्घ करोne_map,
			     काष्ठा isp1362_ep_queue *epq)
अणु
	काष्ठा isp1362_ep *ep;
	काष्ठा isp1362_ep *पंचांगp;

	अगर (list_empty(&epq->active)) अणु
		DBG(1, "%s: Nothing to do for %s queue\n", __func__, epq->name);
		वापस;
	पूर्ण

	DBG(1, "%s: Finishing %s transfers %08lx\n", __func__, epq->name, करोne_map);

	atomic_inc(&epq->finishing);
	list_क्रम_each_entry_safe(ep, पंचांगp, &epq->active, active) अणु
		पूर्णांक index = ep->ptd_index;

		DBG(1, "%s: Checking %s PTD[%02x] $%04x\n", __func__, epq->name,
		    index, ep->ptd_offset);

		BUG_ON(index < 0);
		अगर (__test_and_clear_bit(index, &करोne_map)) अणु
			isp1362_पढ़ो_ptd(isp1362_hcd, ep, epq);
			epq->मुक्त_ptd = index;
			BUG_ON(ep->num_ptds == 0);
			release_ptd_buffers(epq, ep);

			DBG(1, "%s: ep %p req %d removed from active list\n", __func__,
			    ep, ep->num_req);
			अगर (!list_empty(&ep->हटाओ_list)) अणु
				list_del_init(&ep->हटाओ_list);
				DBG(1, "%s: ep %p removed from remove list\n", __func__, ep);
			पूर्ण
			DBG(1, "%s: Postprocessing %s ep %p req %d\n", __func__, epq->name,
			    ep, ep->num_req);
			postproc_ep(isp1362_hcd, ep);
		पूर्ण
		अगर (!करोne_map)
			अवरोध;
	पूर्ण
	अगर (करोne_map)
		pr_warn("%s: done_map not clear: %08lx:%08lx\n",
			__func__, करोne_map, epq->skip_map);
	atomic_dec(&epq->finishing);
पूर्ण

अटल व्योम finish_iso_transfers(काष्ठा isp1362_hcd *isp1362_hcd, काष्ठा isp1362_ep_queue *epq)
अणु
	काष्ठा isp1362_ep *ep;
	काष्ठा isp1362_ep *पंचांगp;

	अगर (list_empty(&epq->active)) अणु
		DBG(1, "%s: Nothing to do for %s queue\n", __func__, epq->name);
		वापस;
	पूर्ण

	DBG(1, "%s: Finishing %s transfers\n", __func__, epq->name);

	atomic_inc(&epq->finishing);
	list_क्रम_each_entry_safe(ep, पंचांगp, &epq->active, active) अणु
		DBG(1, "%s: Checking PTD $%04x\n", __func__, ep->ptd_offset);

		isp1362_पढ़ो_ptd(isp1362_hcd, ep, epq);
		DBG(1, "%s: Postprocessing %s ep %p\n", __func__, epq->name, ep);
		postproc_ep(isp1362_hcd, ep);
	पूर्ण
	WARN_ON(epq->blk_size != 0);
	atomic_dec(&epq->finishing);
पूर्ण

अटल irqवापस_t isp1362_irq(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक handled = 0;
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	u16 irqstat;
	u16 svc_mask;

	spin_lock(&isp1362_hcd->lock);

	BUG_ON(isp1362_hcd->irq_active++);

	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINTENB, 0);

	irqstat = isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINT);
	DBG(3, "%s: got IRQ %04x:%04x\n", __func__, irqstat, isp1362_hcd->irqenb);

	/* only handle पूर्णांकerrupts that are currently enabled */
	irqstat &= isp1362_hcd->irqenb;
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINT, irqstat);
	svc_mask = irqstat;

	अगर (irqstat & HCuPINT_SOF) अणु
		isp1362_hcd->irqenb &= ~HCuPINT_SOF;
		isp1362_hcd->irq_stat[ISP1362_INT_SOF]++;
		handled = 1;
		svc_mask &= ~HCuPINT_SOF;
		DBG(3, "%s: SOF\n", __func__);
		isp1362_hcd->fmindex = isp1362_पढ़ो_reg32(isp1362_hcd, HCFMNUM);
		अगर (!list_empty(&isp1362_hcd->हटाओ_list))
			finish_unlinks(isp1362_hcd);
		अगर (!list_empty(&isp1362_hcd->async) && !(irqstat & HCuPINT_ATL)) अणु
			अगर (list_empty(&isp1362_hcd->atl_queue.active)) अणु
				start_atl_transfers(isp1362_hcd);
			पूर्ण अन्यथा अणु
				isp1362_enable_पूर्णांक(isp1362_hcd, HCuPINT_ATL);
				isp1362_ग_लिखो_reg32(isp1362_hcd, HCATLSKIP,
						    isp1362_hcd->atl_queue.skip_map);
				isp1362_set_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ATL_ACTIVE);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (irqstat & HCuPINT_ISTL0) अणु
		isp1362_hcd->irq_stat[ISP1362_INT_ISTL0]++;
		handled = 1;
		svc_mask &= ~HCuPINT_ISTL0;
		isp1362_clr_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ISTL0_FULL);
		DBG(1, "%s: ISTL0\n", __func__);
		WARN_ON((पूर्णांक)!!isp1362_hcd->istl_flip);
		WARN_ON(isp1362_पढ़ो_reg16(isp1362_hcd, HCBUFSTAT) &
			HCBUFSTAT_ISTL0_ACTIVE);
		WARN_ON(!(isp1362_पढ़ो_reg16(isp1362_hcd, HCBUFSTAT) &
			HCBUFSTAT_ISTL0_DONE));
		isp1362_hcd->irqenb &= ~HCuPINT_ISTL0;
	पूर्ण

	अगर (irqstat & HCuPINT_ISTL1) अणु
		isp1362_hcd->irq_stat[ISP1362_INT_ISTL1]++;
		handled = 1;
		svc_mask &= ~HCuPINT_ISTL1;
		isp1362_clr_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ISTL1_FULL);
		DBG(1, "%s: ISTL1\n", __func__);
		WARN_ON(!(पूर्णांक)isp1362_hcd->istl_flip);
		WARN_ON(isp1362_पढ़ो_reg16(isp1362_hcd, HCBUFSTAT) &
			HCBUFSTAT_ISTL1_ACTIVE);
		WARN_ON(!(isp1362_पढ़ो_reg16(isp1362_hcd, HCBUFSTAT) &
			HCBUFSTAT_ISTL1_DONE));
		isp1362_hcd->irqenb &= ~HCuPINT_ISTL1;
	पूर्ण

	अगर (irqstat & (HCuPINT_ISTL0 | HCuPINT_ISTL1)) अणु
		WARN_ON((irqstat & (HCuPINT_ISTL0 | HCuPINT_ISTL1)) ==
			(HCuPINT_ISTL0 | HCuPINT_ISTL1));
		finish_iso_transfers(isp1362_hcd,
				     &isp1362_hcd->istl_queue[isp1362_hcd->istl_flip]);
		start_iso_transfers(isp1362_hcd);
		isp1362_hcd->istl_flip = 1 - isp1362_hcd->istl_flip;
	पूर्ण

	अगर (irqstat & HCuPINT_INTL) अणु
		u32 करोne_map = isp1362_पढ़ो_reg32(isp1362_hcd, HCINTLDONE);
		u32 skip_map = isp1362_पढ़ो_reg32(isp1362_hcd, HCINTLSKIP);
		isp1362_hcd->irq_stat[ISP1362_INT_INTL]++;

		DBG(2, "%s: INTL\n", __func__);

		svc_mask &= ~HCuPINT_INTL;

		isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTLSKIP, skip_map | करोne_map);
		अगर (~(करोne_map | skip_map) == 0)
			/* All PTDs are finished, disable INTL processing entirely */
			isp1362_clr_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_INTL_ACTIVE);

		handled = 1;
		WARN_ON(!करोne_map);
		अगर (करोne_map) अणु
			DBG(3, "%s: INTL done_map %08x\n", __func__, करोne_map);
			finish_transfers(isp1362_hcd, करोne_map, &isp1362_hcd->पूर्णांकl_queue);
			start_पूर्णांकl_transfers(isp1362_hcd);
		पूर्ण
	पूर्ण

	अगर (irqstat & HCuPINT_ATL) अणु
		u32 करोne_map = isp1362_पढ़ो_reg32(isp1362_hcd, HCATLDONE);
		u32 skip_map = isp1362_पढ़ो_reg32(isp1362_hcd, HCATLSKIP);
		isp1362_hcd->irq_stat[ISP1362_INT_ATL]++;

		DBG(2, "%s: ATL\n", __func__);

		svc_mask &= ~HCuPINT_ATL;

		isp1362_ग_लिखो_reg32(isp1362_hcd, HCATLSKIP, skip_map | करोne_map);
		अगर (~(करोne_map | skip_map) == 0)
			isp1362_clr_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ATL_ACTIVE);
		अगर (करोne_map) अणु
			DBG(3, "%s: ATL done_map %08x\n", __func__, करोne_map);
			finish_transfers(isp1362_hcd, करोne_map, &isp1362_hcd->atl_queue);
			start_atl_transfers(isp1362_hcd);
		पूर्ण
		handled = 1;
	पूर्ण

	अगर (irqstat & HCuPINT_OPR) अणु
		u32 पूर्णांकstat = isp1362_पढ़ो_reg32(isp1362_hcd, HCINTSTAT);
		isp1362_hcd->irq_stat[ISP1362_INT_OPR]++;

		svc_mask &= ~HCuPINT_OPR;
		DBG(2, "%s: OPR %08x:%08x\n", __func__, पूर्णांकstat, isp1362_hcd->पूर्णांकenb);
		पूर्णांकstat &= isp1362_hcd->पूर्णांकenb;
		अगर (पूर्णांकstat & OHCI_INTR_UE) अणु
			pr_err("Unrecoverable error\n");
			/* FIXME: करो here reset or cleanup or whatever */
		पूर्ण
		अगर (पूर्णांकstat & OHCI_INTR_RHSC) अणु
			isp1362_hcd->rhstatus = isp1362_पढ़ो_reg32(isp1362_hcd, HCRHSTATUS);
			isp1362_hcd->rhport[0] = isp1362_पढ़ो_reg32(isp1362_hcd, HCRHPORT1);
			isp1362_hcd->rhport[1] = isp1362_पढ़ो_reg32(isp1362_hcd, HCRHPORT2);
		पूर्ण
		अगर (पूर्णांकstat & OHCI_INTR_RD) अणु
			pr_info("%s: RESUME DETECTED\n", __func__);
			isp1362_show_reg(isp1362_hcd, HCCONTROL);
			usb_hcd_resume_root_hub(hcd);
		पूर्ण
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTSTAT, पूर्णांकstat);
		irqstat &= ~HCuPINT_OPR;
		handled = 1;
	पूर्ण

	अगर (irqstat & HCuPINT_SUSP) अणु
		isp1362_hcd->irq_stat[ISP1362_INT_SUSP]++;
		handled = 1;
		svc_mask &= ~HCuPINT_SUSP;

		pr_info("%s: SUSPEND IRQ\n", __func__);
	पूर्ण

	अगर (irqstat & HCuPINT_CLKRDY) अणु
		isp1362_hcd->irq_stat[ISP1362_INT_CLKRDY]++;
		handled = 1;
		isp1362_hcd->irqenb &= ~HCuPINT_CLKRDY;
		svc_mask &= ~HCuPINT_CLKRDY;
		pr_info("%s: CLKRDY IRQ\n", __func__);
	पूर्ण

	अगर (svc_mask)
		pr_err("%s: Unserviced interrupt(s) %04x\n", __func__, svc_mask);

	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINTENB, isp1362_hcd->irqenb);
	isp1362_hcd->irq_active--;
	spin_unlock(&isp1362_hcd->lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा	MAX_PERIODIC_LOAD	900	/* out of 1000 usec */
अटल पूर्णांक balance(काष्ठा isp1362_hcd *isp1362_hcd, u16 पूर्णांकerval, u16 load)
अणु
	पूर्णांक i, branch = -ENOSPC;

	/* search क्रम the least loaded schedule branch of that पूर्णांकerval
	 * which has enough bandwidth left unreserved.
	 */
	क्रम (i = 0; i < पूर्णांकerval; i++) अणु
		अगर (branch < 0 || isp1362_hcd->load[branch] > isp1362_hcd->load[i]) अणु
			पूर्णांक j;

			क्रम (j = i; j < PERIODIC_SIZE; j += पूर्णांकerval) अणु
				अगर ((isp1362_hcd->load[j] + load) > MAX_PERIODIC_LOAD) अणु
					pr_err("%s: new load %d load[%02x] %d max %d\n", __func__,
					    load, j, isp1362_hcd->load[j], MAX_PERIODIC_LOAD);
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (j < PERIODIC_SIZE)
				जारी;
			branch = i;
		पूर्ण
	पूर्ण
	वापस branch;
पूर्ण

/* NB! ALL the code above this poपूर्णांक runs with isp1362_hcd->lock
   held, irqs off
*/

/*-------------------------------------------------------------------------*/

अटल पूर्णांक isp1362_urb_enqueue(काष्ठा usb_hcd *hcd,
			       काष्ठा urb *urb,
			       gfp_t mem_flags)
अणु
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	काष्ठा usb_device *udev = urb->dev;
	अचिन्हित पूर्णांक pipe = urb->pipe;
	पूर्णांक is_out = !usb_pipein(pipe);
	पूर्णांक type = usb_pipetype(pipe);
	पूर्णांक epnum = usb_pipeendpoपूर्णांक(pipe);
	काष्ठा usb_host_endpoपूर्णांक *hep = urb->ep;
	काष्ठा isp1362_ep *ep = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	DBG(3, "%s: urb %p\n", __func__, urb);

	अगर (type == PIPE_ISOCHRONOUS) अणु
		pr_err("Isochronous transfers not supported\n");
		वापस -ENOSPC;
	पूर्ण

	URB_DBG("%s: FA %d ep%d%s %s: len %d %s%s\n", __func__,
		usb_pipedevice(pipe), epnum,
		is_out ? "out" : "in",
		usb_pipecontrol(pipe) ? "ctrl" :
			usb_pipeपूर्णांक(pipe) ? "int" :
			usb_pipebulk(pipe) ? "bulk" :
			"iso",
		urb->transfer_buffer_length,
		(urb->transfer_flags & URB_ZERO_PACKET) ? "ZERO_PACKET " : "",
		!(urb->transfer_flags & URB_SHORT_NOT_OK) ?
		"short_ok" : "");

	/* aव्योम all allocations within spinlocks: request or endpoपूर्णांक */
	अगर (!hep->hcpriv) अणु
		ep = kzalloc(माप *ep, mem_flags);
		अगर (!ep)
			वापस -ENOMEM;
	पूर्ण
	spin_lock_irqsave(&isp1362_hcd->lock, flags);

	/* करोn't submit to a dead or disabled port */
	अगर (!((isp1362_hcd->rhport[0] | isp1362_hcd->rhport[1]) &
	      USB_PORT_STAT_ENABLE) ||
	    !HC_IS_RUNNING(hcd->state)) अणु
		kमुक्त(ep);
		retval = -ENODEV;
		जाओ fail_not_linked;
	पूर्ण

	retval = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (retval) अणु
		kमुक्त(ep);
		जाओ fail_not_linked;
	पूर्ण

	अगर (hep->hcpriv) अणु
		ep = hep->hcpriv;
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&ep->schedule);
		INIT_LIST_HEAD(&ep->active);
		INIT_LIST_HEAD(&ep->हटाओ_list);
		ep->udev = usb_get_dev(udev);
		ep->hep = hep;
		ep->epnum = epnum;
		ep->maxpacket = usb_maxpacket(udev, urb->pipe, is_out);
		ep->ptd_offset = -EINVAL;
		ep->ptd_index = -EINVAL;
		usb_settoggle(udev, epnum, is_out, 0);

		अगर (type == PIPE_CONTROL)
			ep->nextpid = USB_PID_SETUP;
		अन्यथा अगर (is_out)
			ep->nextpid = USB_PID_OUT;
		अन्यथा
			ep->nextpid = USB_PID_IN;

		चयन (type) अणु
		हाल PIPE_ISOCHRONOUS:
		हाल PIPE_INTERRUPT:
			अगर (urb->पूर्णांकerval > PERIODIC_SIZE)
				urb->पूर्णांकerval = PERIODIC_SIZE;
			ep->पूर्णांकerval = urb->पूर्णांकerval;
			ep->branch = PERIODIC_SIZE;
			ep->load = usb_calc_bus_समय(udev->speed, !is_out,
						     (type == PIPE_ISOCHRONOUS),
						     usb_maxpacket(udev, pipe, is_out)) / 1000;
			अवरोध;
		पूर्ण
		hep->hcpriv = ep;
	पूर्ण
	ep->num_req = isp1362_hcd->req_serial++;

	/* maybe put endpoपूर्णांक पूर्णांकo schedule */
	चयन (type) अणु
	हाल PIPE_CONTROL:
	हाल PIPE_BULK:
		अगर (list_empty(&ep->schedule)) अणु
			DBG(1, "%s: Adding ep %p req %d to async schedule\n",
				__func__, ep, ep->num_req);
			list_add_tail(&ep->schedule, &isp1362_hcd->async);
		पूर्ण
		अवरोध;
	हाल PIPE_ISOCHRONOUS:
	हाल PIPE_INTERRUPT:
		urb->पूर्णांकerval = ep->पूर्णांकerval;

		/* urb submitted क्रम alपढ़ोy existing EP */
		अगर (ep->branch < PERIODIC_SIZE)
			अवरोध;

		retval = balance(isp1362_hcd, ep->पूर्णांकerval, ep->load);
		अगर (retval < 0) अणु
			pr_err("%s: balance returned %d\n", __func__, retval);
			जाओ fail;
		पूर्ण
		ep->branch = retval;
		retval = 0;
		isp1362_hcd->fmindex = isp1362_पढ़ो_reg32(isp1362_hcd, HCFMNUM);
		DBG(1, "%s: Current frame %04x branch %02x start_frame %04x(%04x)\n",
		    __func__, isp1362_hcd->fmindex, ep->branch,
		    ((isp1362_hcd->fmindex + PERIODIC_SIZE - 1) &
		     ~(PERIODIC_SIZE - 1)) + ep->branch,
		    (isp1362_hcd->fmindex & (PERIODIC_SIZE - 1)) + ep->branch);

		अगर (list_empty(&ep->schedule)) अणु
			अगर (type == PIPE_ISOCHRONOUS) अणु
				u16 frame = isp1362_hcd->fmindex;

				frame += max_t(u16, 8, ep->पूर्णांकerval);
				frame &= ~(ep->पूर्णांकerval - 1);
				frame |= ep->branch;
				अगर (frame_beक्रमe(frame, isp1362_hcd->fmindex))
					frame += ep->पूर्णांकerval;
				urb->start_frame = frame;

				DBG(1, "%s: Adding ep %p to isoc schedule\n", __func__, ep);
				list_add_tail(&ep->schedule, &isp1362_hcd->isoc);
			पूर्ण अन्यथा अणु
				DBG(1, "%s: Adding ep %p to periodic schedule\n", __func__, ep);
				list_add_tail(&ep->schedule, &isp1362_hcd->periodic);
			पूर्ण
		पूर्ण अन्यथा
			DBG(1, "%s: ep %p already scheduled\n", __func__, ep);

		DBG(2, "%s: load %d bandwidth %d -> %d\n", __func__,
		    ep->load / ep->पूर्णांकerval, isp1362_hcd->load[ep->branch],
		    isp1362_hcd->load[ep->branch] + ep->load);
		isp1362_hcd->load[ep->branch] += ep->load;
	पूर्ण

	urb->hcpriv = hep;
	ALIGNSTAT(isp1362_hcd, urb->transfer_buffer);

	चयन (type) अणु
	हाल PIPE_CONTROL:
	हाल PIPE_BULK:
		start_atl_transfers(isp1362_hcd);
		अवरोध;
	हाल PIPE_INTERRUPT:
		start_पूर्णांकl_transfers(isp1362_hcd);
		अवरोध;
	हाल PIPE_ISOCHRONOUS:
		start_iso_transfers(isp1362_hcd);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
 fail:
	अगर (retval)
		usb_hcd_unlink_urb_from_ep(hcd, urb);


 fail_not_linked:
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
	अगर (retval)
		DBG(0, "%s: urb %p failed with %d\n", __func__, urb, retval);
	वापस retval;
पूर्ण

अटल पूर्णांक isp1362_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	काष्ठा usb_host_endpoपूर्णांक *hep;
	अचिन्हित दीर्घ flags;
	काष्ठा isp1362_ep *ep;
	पूर्णांक retval = 0;

	DBG(3, "%s: urb %p\n", __func__, urb);

	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	retval = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (retval)
		जाओ करोne;

	hep = urb->hcpriv;

	अगर (!hep) अणु
		spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
		वापस -EIDRM;
	पूर्ण

	ep = hep->hcpriv;
	अगर (ep) अणु
		/* In front of queue? */
		अगर (ep->hep->urb_list.next == &urb->urb_list) अणु
			अगर (!list_empty(&ep->active)) अणु
				DBG(1, "%s: urb %p ep %p req %d active PTD[%d] $%04x\n", __func__,
				    urb, ep, ep->num_req, ep->ptd_index, ep->ptd_offset);
				/* disable processing and queue PTD क्रम removal */
				हटाओ_ptd(isp1362_hcd, ep);
				urb = शून्य;
			पूर्ण
		पूर्ण
		अगर (urb) अणु
			DBG(1, "%s: Finishing ep %p req %d\n", __func__, ep,
			    ep->num_req);
			finish_request(isp1362_hcd, ep, urb, status);
		पूर्ण अन्यथा
			DBG(1, "%s: urb %p active; wait4irq\n", __func__, urb);
	पूर्ण अन्यथा अणु
		pr_warn("%s: No EP in URB %p\n", __func__, urb);
		retval = -EINVAL;
	पूर्ण
करोne:
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

	DBG(3, "%s: exit\n", __func__);

	वापस retval;
पूर्ण

अटल व्योम isp1362_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd, काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	काष्ठा isp1362_ep *ep = hep->hcpriv;
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	अचिन्हित दीर्घ flags;

	DBG(1, "%s: ep %p\n", __func__, ep);
	अगर (!ep)
		वापस;
	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	अगर (!list_empty(&hep->urb_list)) अणु
		अगर (!list_empty(&ep->active) && list_empty(&ep->हटाओ_list)) अणु
			DBG(1, "%s: Removing ep %p req %d PTD[%d] $%04x\n", __func__,
			    ep, ep->num_req, ep->ptd_index, ep->ptd_offset);
			हटाओ_ptd(isp1362_hcd, ep);
			pr_info("%s: Waiting for Interrupt to clean up\n", __func__);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
	/* Wait क्रम पूर्णांकerrupt to clear out active list */
	जबतक (!list_empty(&ep->active))
		msleep(1);

	DBG(1, "%s: Freeing EP %p\n", __func__, ep);

	usb_put_dev(ep->udev);
	kमुक्त(ep);
	hep->hcpriv = शून्य;
पूर्ण

अटल पूर्णांक isp1362_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	u32 fmnum;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	fmnum = isp1362_पढ़ो_reg32(isp1362_hcd, HCFMNUM);
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

	वापस (पूर्णांक)fmnum;
पूर्ण

/*-------------------------------------------------------------------------*/

/* Adapted from ohci-hub.c */
अटल पूर्णांक isp1362_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	पूर्णांक ports, i, changed = 0;
	अचिन्हित दीर्घ flags;

	अगर (!HC_IS_RUNNING(hcd->state))
		वापस -ESHUTDOWN;

	/* Report no status change now, अगर we are scheduled to be
	   called later */
	अगर (समयr_pending(&hcd->rh_समयr))
		वापस 0;

	ports = isp1362_hcd->rhdesca & RH_A_NDP;
	BUG_ON(ports > 2);

	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	/* init status */
	अगर (isp1362_hcd->rhstatus & (RH_HS_LPSC | RH_HS_OCIC))
		buf[0] = changed = 1;
	अन्यथा
		buf[0] = 0;

	क्रम (i = 0; i < ports; i++) अणु
		u32 status = isp1362_hcd->rhport[i];

		अगर (status & (RH_PS_CSC | RH_PS_PESC | RH_PS_PSSC |
			      RH_PS_OCIC | RH_PS_PRSC)) अणु
			changed = 1;
			buf[0] |= 1 << (i + 1);
			जारी;
		पूर्ण

		अगर (!(status & RH_PS_CCS))
			जारी;
	पूर्ण
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
	वापस changed;
पूर्ण

अटल व्योम isp1362_hub_descriptor(काष्ठा isp1362_hcd *isp1362_hcd,
				   काष्ठा usb_hub_descriptor *desc)
अणु
	u32 reg = isp1362_hcd->rhdesca;

	DBG(3, "%s: enter\n", __func__);

	desc->bDescriptorType = USB_DT_HUB;
	desc->bDescLength = 9;
	desc->bHubContrCurrent = 0;
	desc->bNbrPorts = reg & 0x3;
	/* Power चयनing, device type, overcurrent. */
	desc->wHubCharacteristics = cpu_to_le16((reg >> 8) &
						(HUB_CHAR_LPSM |
						 HUB_CHAR_COMPOUND |
						 HUB_CHAR_OCPM));
	DBG(0, "%s: hubcharacteristics = %02x\n", __func__,
			desc->wHubCharacteristics);
	desc->bPwrOn2PwrGood = (reg >> 24) & 0xff;
	/* ports removable, and legacy PortPwrCtrlMask */
	desc->u.hs.DeviceRemovable[0] = desc->bNbrPorts == 1 ? 1 << 1 : 3 << 1;
	desc->u.hs.DeviceRemovable[1] = ~0;

	DBG(3, "%s: exit\n", __func__);
पूर्ण

/* Adapted from ohci-hub.c */
अटल पूर्णांक isp1362_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
			       u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ t1;
	पूर्णांक ports = isp1362_hcd->rhdesca & RH_A_NDP;
	u32 पंचांगp = 0;

	चयन (typeReq) अणु
	हाल ClearHubFeature:
		DBG(0, "ClearHubFeature: ");
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
			DBG(0, "C_HUB_OVER_CURRENT\n");
			spin_lock_irqsave(&isp1362_hcd->lock, flags);
			isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHSTATUS, RH_HS_OCIC);
			spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
			अवरोध;
		हाल C_HUB_LOCAL_POWER:
			DBG(0, "C_HUB_LOCAL_POWER\n");
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SetHubFeature:
		DBG(0, "SetHubFeature: ");
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
		हाल C_HUB_LOCAL_POWER:
			DBG(0, "C_HUB_OVER_CURRENT or C_HUB_LOCAL_POWER\n");
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल GetHubDescriptor:
		DBG(0, "GetHubDescriptor\n");
		isp1362_hub_descriptor(isp1362_hcd, (काष्ठा usb_hub_descriptor *)buf);
		अवरोध;
	हाल GetHubStatus:
		DBG(0, "GetHubStatus\n");
		put_unaligned(cpu_to_le32(0), (__le32 *) buf);
		अवरोध;
	हाल GetPortStatus:
#अगर_अघोषित VERBOSE
		DBG(0, "GetPortStatus\n");
#पूर्ण_अगर
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		पंचांगp = isp1362_hcd->rhport[--wIndex];
		put_unaligned(cpu_to_le32(पंचांगp), (__le32 *) buf);
		अवरोध;
	हाल ClearPortFeature:
		DBG(0, "ClearPortFeature: ");
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			DBG(0, "USB_PORT_FEAT_ENABLE\n");
			पंचांगp = RH_PS_CCS;
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			DBG(0, "USB_PORT_FEAT_C_ENABLE\n");
			पंचांगp = RH_PS_PESC;
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			DBG(0, "USB_PORT_FEAT_SUSPEND\n");
			पंचांगp = RH_PS_POCI;
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			DBG(0, "USB_PORT_FEAT_C_SUSPEND\n");
			पंचांगp = RH_PS_PSSC;
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			DBG(0, "USB_PORT_FEAT_POWER\n");
			पंचांगp = RH_PS_LSDA;

			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			DBG(0, "USB_PORT_FEAT_C_CONNECTION\n");
			पंचांगp = RH_PS_CSC;
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			DBG(0, "USB_PORT_FEAT_C_OVER_CURRENT\n");
			पंचांगp = RH_PS_OCIC;
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			DBG(0, "USB_PORT_FEAT_C_RESET\n");
			पंचांगp = RH_PS_PRSC;
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण

		spin_lock_irqsave(&isp1362_hcd->lock, flags);
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHPORT1 + wIndex, पंचांगp);
		isp1362_hcd->rhport[wIndex] =
			isp1362_पढ़ो_reg32(isp1362_hcd, HCRHPORT1 + wIndex);
		spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
		अवरोध;
	हाल SetPortFeature:
		DBG(0, "SetPortFeature: ");
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			DBG(0, "USB_PORT_FEAT_SUSPEND\n");
			spin_lock_irqsave(&isp1362_hcd->lock, flags);
			isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHPORT1 + wIndex, RH_PS_PSS);
			isp1362_hcd->rhport[wIndex] =
				isp1362_पढ़ो_reg32(isp1362_hcd, HCRHPORT1 + wIndex);
			spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			DBG(0, "USB_PORT_FEAT_POWER\n");
			spin_lock_irqsave(&isp1362_hcd->lock, flags);
			isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHPORT1 + wIndex, RH_PS_PPS);
			isp1362_hcd->rhport[wIndex] =
				isp1362_पढ़ो_reg32(isp1362_hcd, HCRHPORT1 + wIndex);
			spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			DBG(0, "USB_PORT_FEAT_RESET\n");
			spin_lock_irqsave(&isp1362_hcd->lock, flags);

			t1 = jअगरfies + msecs_to_jअगरfies(USB_RESET_WIDTH);
			जबतक (समय_beक्रमe(jअगरfies, t1)) अणु
				/* spin until any current reset finishes */
				क्रम (;;) अणु
					पंचांगp = isp1362_पढ़ो_reg32(isp1362_hcd, HCRHPORT1 + wIndex);
					अगर (!(पंचांगp & RH_PS_PRS))
						अवरोध;
					udelay(500);
				पूर्ण
				अगर (!(पंचांगp & RH_PS_CCS))
					अवरोध;
				/* Reset lasts 10ms (claims datasheet) */
				isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHPORT1 + wIndex, (RH_PS_PRS));

				spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
				msleep(10);
				spin_lock_irqsave(&isp1362_hcd->lock, flags);
			पूर्ण

			isp1362_hcd->rhport[wIndex] = isp1362_पढ़ो_reg32(isp1362_hcd,
									 HCRHPORT1 + wIndex);
			spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;

	शेष:
 error:
		/* "protocol stall" on error */
		DBG(0, "PROTOCOL STALL\n");
		retval = -EPIPE;
	पूर्ण

	वापस retval;
पूर्ण

#अगर_घोषित	CONFIG_PM
अटल पूर्णांक isp1362_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक status = 0;
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	अचिन्हित दीर्घ flags;

	अगर (समय_beक्रमe(jअगरfies, isp1362_hcd->next_statechange))
		msleep(5);

	spin_lock_irqsave(&isp1362_hcd->lock, flags);

	isp1362_hcd->hc_control = isp1362_पढ़ो_reg32(isp1362_hcd, HCCONTROL);
	चयन (isp1362_hcd->hc_control & OHCI_CTRL_HCFS) अणु
	हाल OHCI_USB_RESUME:
		DBG(0, "%s: resume/suspend?\n", __func__);
		isp1362_hcd->hc_control &= ~OHCI_CTRL_HCFS;
		isp1362_hcd->hc_control |= OHCI_USB_RESET;
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCCONTROL, isp1362_hcd->hc_control);
		fallthrough;
	हाल OHCI_USB_RESET:
		status = -EBUSY;
		pr_warn("%s: needs reinit!\n", __func__);
		जाओ करोne;
	हाल OHCI_USB_SUSPEND:
		pr_warn("%s: already suspended?\n", __func__);
		जाओ करोne;
	पूर्ण
	DBG(0, "%s: suspend root hub\n", __func__);

	/* First stop any processing */
	hcd->state = HC_STATE_QUIESCING;
	अगर (!list_empty(&isp1362_hcd->atl_queue.active) ||
	    !list_empty(&isp1362_hcd->पूर्णांकl_queue.active) ||
	    !list_empty(&isp1362_hcd->istl_queue[0] .active) ||
	    !list_empty(&isp1362_hcd->istl_queue[1] .active)) अणु
		पूर्णांक limit;

		isp1362_ग_लिखो_reg32(isp1362_hcd, HCATLSKIP, ~0);
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTLSKIP, ~0);
		isp1362_ग_लिखो_reg16(isp1362_hcd, HCBUFSTAT, 0);
		isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINTENB, 0);
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTSTAT, OHCI_INTR_SF);

		DBG(0, "%s: stopping schedules ...\n", __func__);
		limit = 2000;
		जबतक (limit > 0) अणु
			udelay(250);
			limit -= 250;
			अगर (isp1362_पढ़ो_reg32(isp1362_hcd, HCINTSTAT) & OHCI_INTR_SF)
				अवरोध;
		पूर्ण
		mdelay(7);
		अगर (isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINT) & HCuPINT_ATL) अणु
			u32 करोne_map = isp1362_पढ़ो_reg32(isp1362_hcd, HCATLDONE);
			finish_transfers(isp1362_hcd, करोne_map, &isp1362_hcd->atl_queue);
		पूर्ण
		अगर (isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINT) & HCuPINT_INTL) अणु
			u32 करोne_map = isp1362_पढ़ो_reg32(isp1362_hcd, HCINTLDONE);
			finish_transfers(isp1362_hcd, करोne_map, &isp1362_hcd->पूर्णांकl_queue);
		पूर्ण
		अगर (isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINT) & HCuPINT_ISTL0)
			finish_iso_transfers(isp1362_hcd, &isp1362_hcd->istl_queue[0]);
		अगर (isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINT) & HCuPINT_ISTL1)
			finish_iso_transfers(isp1362_hcd, &isp1362_hcd->istl_queue[1]);
	पूर्ण
	DBG(0, "%s: HCINTSTAT: %08x\n", __func__,
		    isp1362_पढ़ो_reg32(isp1362_hcd, HCINTSTAT));
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTSTAT,
			    isp1362_पढ़ो_reg32(isp1362_hcd, HCINTSTAT));

	/* Suspend hub */
	isp1362_hcd->hc_control = OHCI_USB_SUSPEND;
	isp1362_show_reg(isp1362_hcd, HCCONTROL);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCCONTROL, isp1362_hcd->hc_control);
	isp1362_show_reg(isp1362_hcd, HCCONTROL);

#अगर 1
	isp1362_hcd->hc_control = isp1362_पढ़ो_reg32(isp1362_hcd, HCCONTROL);
	अगर ((isp1362_hcd->hc_control & OHCI_CTRL_HCFS) != OHCI_USB_SUSPEND) अणु
		pr_err("%s: controller won't suspend %08x\n", __func__,
		    isp1362_hcd->hc_control);
		status = -EBUSY;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		/* no resumes until devices finish suspending */
		isp1362_hcd->next_statechange = jअगरfies + msecs_to_jअगरfies(5);
	पूर्ण
करोne:
	अगर (status == 0) अणु
		hcd->state = HC_STATE_SUSPENDED;
		DBG(0, "%s: HCD suspended: %08x\n", __func__,
		    isp1362_पढ़ो_reg32(isp1362_hcd, HCCONTROL));
	पूर्ण
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
	वापस status;
पूर्ण

अटल पूर्णांक isp1362_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	u32 port;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = -EINPROGRESS;

	अगर (समय_beक्रमe(jअगरfies, isp1362_hcd->next_statechange))
		msleep(5);

	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	isp1362_hcd->hc_control = isp1362_पढ़ो_reg32(isp1362_hcd, HCCONTROL);
	pr_info("%s: HCCONTROL: %08x\n", __func__, isp1362_hcd->hc_control);
	अगर (hcd->state == HC_STATE_RESUMING) अणु
		pr_warn("%s: duplicate resume\n", __func__);
		status = 0;
	पूर्ण अन्यथा
		चयन (isp1362_hcd->hc_control & OHCI_CTRL_HCFS) अणु
		हाल OHCI_USB_SUSPEND:
			DBG(0, "%s: resume root hub\n", __func__);
			isp1362_hcd->hc_control &= ~OHCI_CTRL_HCFS;
			isp1362_hcd->hc_control |= OHCI_USB_RESUME;
			isp1362_ग_लिखो_reg32(isp1362_hcd, HCCONTROL, isp1362_hcd->hc_control);
			अवरोध;
		हाल OHCI_USB_RESUME:
			/* HCFS changes someसमय after INTR_RD */
			DBG(0, "%s: remote wakeup\n", __func__);
			अवरोध;
		हाल OHCI_USB_OPER:
			DBG(0, "%s: odd resume\n", __func__);
			status = 0;
			hcd->self.root_hub->dev.घातer.घातer_state = PMSG_ON;
			अवरोध;
		शेष:		/* RESET, we lost घातer */
			DBG(0, "%s: root hub hardware reset\n", __func__);
			status = -EBUSY;
		पूर्ण
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
	अगर (status == -EBUSY) अणु
		DBG(0, "%s: Restarting HC\n", __func__);
		isp1362_hc_stop(hcd);
		वापस isp1362_hc_start(hcd);
	पूर्ण
	अगर (status != -EINPROGRESS)
		वापस status;
	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	port = isp1362_पढ़ो_reg32(isp1362_hcd, HCRHDESCA) & RH_A_NDP;
	जबतक (port--) अणु
		u32 stat = isp1362_पढ़ो_reg32(isp1362_hcd, HCRHPORT1 + port);

		/* क्रमce global, not selective, resume */
		अगर (!(stat & RH_PS_PSS)) अणु
			DBG(0, "%s: Not Resuming RH port %d\n", __func__, port);
			जारी;
		पूर्ण
		DBG(0, "%s: Resuming RH port %d\n", __func__, port);
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHPORT1 + port, RH_PS_POCI);
	पूर्ण
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

	/* Some controllers (lucent) need extra-दीर्घ delays */
	hcd->state = HC_STATE_RESUMING;
	mdelay(20 /* usb 11.5.1.10 */ + 15);

	isp1362_hcd->hc_control = OHCI_USB_OPER;
	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	isp1362_show_reg(isp1362_hcd, HCCONTROL);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCCONTROL, isp1362_hcd->hc_control);
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
	/* TRSMRCY */
	msleep(10);

	/* keep it alive क्रम ~5x suspend + resume costs */
	isp1362_hcd->next_statechange = jअगरfies + msecs_to_jअगरfies(250);

	hcd->self.root_hub->dev.घातer.घातer_state = PMSG_ON;
	hcd->state = HC_STATE_RUNNING;
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा	isp1362_bus_suspend	शून्य
#घोषणा	isp1362_bus_resume	शून्य
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

अटल व्योम dump_irq(काष्ठा seq_file *s, अक्षर *label, u16 mask)
अणु
	seq_म_लिखो(s, "%-15s %04x%s%s%s%s%s%s\n", label, mask,
		   mask & HCuPINT_CLKRDY ? " clkrdy" : "",
		   mask & HCuPINT_SUSP ? " susp" : "",
		   mask & HCuPINT_OPR ? " opr" : "",
		   mask & HCuPINT_EOT ? " eot" : "",
		   mask & HCuPINT_ATL ? " atl" : "",
		   mask & HCuPINT_SOF ? " sof" : "");
पूर्ण

अटल व्योम dump_पूर्णांक(काष्ठा seq_file *s, अक्षर *label, u32 mask)
अणु
	seq_म_लिखो(s, "%-15s %08x%s%s%s%s%s%s%s\n", label, mask,
		   mask & OHCI_INTR_MIE ? " MIE" : "",
		   mask & OHCI_INTR_RHSC ? " rhsc" : "",
		   mask & OHCI_INTR_FNO ? " fno" : "",
		   mask & OHCI_INTR_UE ? " ue" : "",
		   mask & OHCI_INTR_RD ? " rd" : "",
		   mask & OHCI_INTR_SF ? " sof" : "",
		   mask & OHCI_INTR_SO ? " so" : "");
पूर्ण

अटल व्योम dump_ctrl(काष्ठा seq_file *s, अक्षर *label, u32 mask)
अणु
	seq_म_लिखो(s, "%-15s %08x%s%s%s\n", label, mask,
		   mask & OHCI_CTRL_RWC ? " rwc" : "",
		   mask & OHCI_CTRL_RWE ? " rwe" : "",
		   (अणु
			   अक्षर *hcfs;
			   चयन (mask & OHCI_CTRL_HCFS) अणु
			   हाल OHCI_USB_OPER:
				   hcfs = " oper";
				   अवरोध;
			   हाल OHCI_USB_RESET:
				   hcfs = " reset";
				   अवरोध;
			   हाल OHCI_USB_RESUME:
				   hcfs = " resume";
				   अवरोध;
			   हाल OHCI_USB_SUSPEND:
				   hcfs = " suspend";
				   अवरोध;
			   शेष:
				   hcfs = " ?";
			   पूर्ण
			   hcfs;
		   पूर्ण));
पूर्ण

अटल व्योम dump_regs(काष्ठा seq_file *s, काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	seq_म_लिखो(s, "HCREVISION [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCREVISION),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCREVISION));
	seq_म_लिखो(s, "HCCONTROL  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCCONTROL),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCCONTROL));
	seq_म_लिखो(s, "HCCMDSTAT  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCCMDSTAT),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCCMDSTAT));
	seq_म_लिखो(s, "HCINTSTAT  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCINTSTAT),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCINTSTAT));
	seq_म_लिखो(s, "HCINTENB   [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCINTENB),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCINTENB));
	seq_म_लिखो(s, "HCFMINTVL  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCFMINTVL),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCFMINTVL));
	seq_म_लिखो(s, "HCFMREM    [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCFMREM),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCFMREM));
	seq_म_लिखो(s, "HCFMNUM    [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCFMNUM),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCFMNUM));
	seq_म_लिखो(s, "HCLSTHRESH [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCLSTHRESH),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCLSTHRESH));
	seq_म_लिखो(s, "HCRHDESCA  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCRHDESCA),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCRHDESCA));
	seq_म_लिखो(s, "HCRHDESCB  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCRHDESCB),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCRHDESCB));
	seq_म_लिखो(s, "HCRHSTATUS [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCRHSTATUS),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCRHSTATUS));
	seq_म_लिखो(s, "HCRHPORT1  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCRHPORT1),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCRHPORT1));
	seq_म_लिखो(s, "HCRHPORT2  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCRHPORT2),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCRHPORT2));
	seq_म_लिखो(s, "\n");
	seq_म_लिखो(s, "HCHWCFG    [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCHWCFG),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCHWCFG));
	seq_म_लिखो(s, "HCDMACFG   [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCDMACFG),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCDMACFG));
	seq_म_लिखो(s, "HCXFERCTR  [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCXFERCTR),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCXFERCTR));
	seq_म_लिखो(s, "HCuPINT    [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCuPINT),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINT));
	seq_म_लिखो(s, "HCuPINTENB [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCuPINTENB),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINTENB));
	seq_म_लिखो(s, "HCCHIPID   [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCCHIPID),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCCHIPID));
	seq_म_लिखो(s, "HCSCRATCH  [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCSCRATCH),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCSCRATCH));
	seq_म_लिखो(s, "HCBUFSTAT  [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCBUFSTAT),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCBUFSTAT));
	seq_म_लिखो(s, "HCDIRADDR  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCसूचीADDR),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCसूचीADDR));
#अगर 0
	seq_म_लिखो(s, "HCDIRDATA  [%02x]     %04x\n", ISP1362_REG_NO(HCसूचीDATA),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCसूचीDATA));
#पूर्ण_अगर
	seq_म_लिखो(s, "HCISTLBUFSZ[%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCISTLBUFSZ),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCISTLBUFSZ));
	seq_म_लिखो(s, "HCISTLRATE [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCISTLRATE),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCISTLRATE));
	seq_म_लिखो(s, "\n");
	seq_म_लिखो(s, "HCINTLBUFSZ[%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCINTLBUFSZ),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCINTLBUFSZ));
	seq_म_लिखो(s, "HCINTLBLKSZ[%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCINTLBLKSZ),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCINTLBLKSZ));
	seq_म_लिखो(s, "HCINTLDONE [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCINTLDONE),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCINTLDONE));
	seq_म_लिखो(s, "HCINTLSKIP [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCINTLSKIP),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCINTLSKIP));
	seq_म_लिखो(s, "HCINTLLAST [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCINTLLAST),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCINTLLAST));
	seq_म_लिखो(s, "HCINTLCURR [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCINTLCURR),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCINTLCURR));
	seq_म_लिखो(s, "\n");
	seq_म_लिखो(s, "HCATLBUFSZ [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCATLBUFSZ),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCATLBUFSZ));
	seq_म_लिखो(s, "HCATLBLKSZ [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCATLBLKSZ),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCATLBLKSZ));
#अगर 0
	seq_म_लिखो(s, "HCATLDONE  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCATLDONE),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCATLDONE));
#पूर्ण_अगर
	seq_म_लिखो(s, "HCATLSKIP  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCATLSKIP),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCATLSKIP));
	seq_म_लिखो(s, "HCATLLAST  [%02x] %08x\n", ISP1362_REG_NO(ISP1362_REG_HCATLLAST),
		   isp1362_पढ़ो_reg32(isp1362_hcd, HCATLLAST));
	seq_म_लिखो(s, "HCATLCURR  [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCATLCURR),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCATLCURR));
	seq_म_लिखो(s, "\n");
	seq_म_लिखो(s, "HCATLDTC   [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCATLDTC),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCATLDTC));
	seq_म_लिखो(s, "HCATLDTCTO [%02x]     %04x\n", ISP1362_REG_NO(ISP1362_REG_HCATLDTCTO),
		   isp1362_पढ़ो_reg16(isp1362_hcd, HCATLDTCTO));
पूर्ण

अटल पूर्णांक isp1362_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा isp1362_hcd *isp1362_hcd = s->निजी;
	काष्ठा isp1362_ep *ep;
	पूर्णांक i;

	seq_म_लिखो(s, "%s\n%s version %s\n",
		   isp1362_hcd_to_hcd(isp1362_hcd)->product_desc, hcd_name, DRIVER_VERSION);

	/* collect statistics to help estimate potential win क्रम
	 * DMA engines that care about alignment (PXA)
	 */
	seq_म_लिखो(s, "alignment:  16b/%ld 8b/%ld 4b/%ld 2b/%ld 1b/%ld\n",
		   isp1362_hcd->stat16, isp1362_hcd->stat8, isp1362_hcd->stat4,
		   isp1362_hcd->stat2, isp1362_hcd->stat1);
	seq_म_लिखो(s, "max # ptds in ATL  fifo: %d\n", isp1362_hcd->atl_queue.stat_maxptds);
	seq_म_लिखो(s, "max # ptds in INTL fifo: %d\n", isp1362_hcd->पूर्णांकl_queue.stat_maxptds);
	seq_म_लिखो(s, "max # ptds in ISTL fifo: %d\n",
		   max(isp1362_hcd->istl_queue[0] .stat_maxptds,
		       isp1362_hcd->istl_queue[1] .stat_maxptds));

	/* FIXME: करोn't show the following in suspended state */
	spin_lock_irq(&isp1362_hcd->lock);

	dump_irq(s, "hc_irq_enable", isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINTENB));
	dump_irq(s, "hc_irq_status", isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINT));
	dump_पूर्णांक(s, "ohci_int_enable", isp1362_पढ़ो_reg32(isp1362_hcd, HCINTENB));
	dump_पूर्णांक(s, "ohci_int_status", isp1362_पढ़ो_reg32(isp1362_hcd, HCINTSTAT));
	dump_ctrl(s, "ohci_control", isp1362_पढ़ो_reg32(isp1362_hcd, HCCONTROL));

	क्रम (i = 0; i < NUM_ISP1362_IRQS; i++)
		अगर (isp1362_hcd->irq_stat[i])
			seq_म_लिखो(s, "%-15s: %d\n",
				   ISP1362_INT_NAME(i), isp1362_hcd->irq_stat[i]);

	dump_regs(s, isp1362_hcd);
	list_क्रम_each_entry(ep, &isp1362_hcd->async, schedule) अणु
		काष्ठा urb *urb;

		seq_म_लिखो(s, "%p, ep%d%s, maxpacket %d:\n", ep, ep->epnum,
			   (अणु
				   अक्षर *s;
				   चयन (ep->nextpid) अणु
				   हाल USB_PID_IN:
					   s = "in";
					   अवरोध;
				   हाल USB_PID_OUT:
					   s = "out";
					   अवरोध;
				   हाल USB_PID_SETUP:
					   s = "setup";
					   अवरोध;
				   हाल USB_PID_ACK:
					   s = "status";
					   अवरोध;
				   शेष:
					   s = "?";
					   अवरोध;
				   पूर्ण
				   s;पूर्ण), ep->maxpacket) ;
		list_क्रम_each_entry(urb, &ep->hep->urb_list, urb_list) अणु
			seq_म_लिखो(s, "  urb%p, %d/%d\n", urb,
				   urb->actual_length,
				   urb->transfer_buffer_length);
		पूर्ण
	पूर्ण
	अगर (!list_empty(&isp1362_hcd->async))
		seq_म_लिखो(s, "\n");
	dump_ptd_queue(&isp1362_hcd->atl_queue);

	seq_म_लिखो(s, "periodic size= %d\n", PERIODIC_SIZE);

	list_क्रम_each_entry(ep, &isp1362_hcd->periodic, schedule) अणु
		seq_म_लिखो(s, "branch:%2d load:%3d PTD[%d] $%04x:\n", ep->branch,
			   isp1362_hcd->load[ep->branch], ep->ptd_index, ep->ptd_offset);

		seq_म_लिखो(s, "   %d/%p (%sdev%d ep%d%s max %d)\n",
			   ep->पूर्णांकerval, ep,
			   (ep->udev->speed == USB_SPEED_FULL) ? "" : "ls ",
			   ep->udev->devnum, ep->epnum,
			   (ep->epnum == 0) ? "" :
			   ((ep->nextpid == USB_PID_IN) ?
			    "in" : "out"), ep->maxpacket);
	पूर्ण
	dump_ptd_queue(&isp1362_hcd->पूर्णांकl_queue);

	seq_म_लिखो(s, "ISO:\n");

	list_क्रम_each_entry(ep, &isp1362_hcd->isoc, schedule) अणु
		seq_म_लिखो(s, "   %d/%p (%sdev%d ep%d%s max %d)\n",
			   ep->पूर्णांकerval, ep,
			   (ep->udev->speed == USB_SPEED_FULL) ? "" : "ls ",
			   ep->udev->devnum, ep->epnum,
			   (ep->epnum == 0) ? "" :
			   ((ep->nextpid == USB_PID_IN) ?
			    "in" : "out"), ep->maxpacket);
	पूर्ण

	spin_unlock_irq(&isp1362_hcd->lock);
	seq_म_लिखो(s, "\n");

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(isp1362);

/* expect just one isp1362_hcd per प्रणाली */
अटल व्योम create_debug_file(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	debugfs_create_file("isp1362", S_IRUGO, usb_debug_root, isp1362_hcd,
			    &isp1362_fops);
पूर्ण

अटल व्योम हटाओ_debug_file(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	debugfs_हटाओ(debugfs_lookup("isp1362", usb_debug_root));
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम __isp1362_sw_reset(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	पूर्णांक पंचांगp = 20;

	isp1362_ग_लिखो_reg16(isp1362_hcd, HCSWRES, HCSWRES_MAGIC);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCCMDSTAT, OHCI_HCR);
	जबतक (--पंचांगp) अणु
		mdelay(1);
		अगर (!(isp1362_पढ़ो_reg32(isp1362_hcd, HCCMDSTAT) & OHCI_HCR))
			अवरोध;
	पूर्ण
	अगर (!पंचांगp)
		pr_err("Software reset timeout\n");
पूर्ण

अटल व्योम isp1362_sw_reset(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	__isp1362_sw_reset(isp1362_hcd);
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
पूर्ण

अटल पूर्णांक isp1362_mem_config(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	अचिन्हित दीर्घ flags;
	u32 total;
	u16 istl_size = ISP1362_ISTL_बफ_मानE;
	u16 पूर्णांकl_blksize = ISP1362_INTL_BLKSIZE + PTD_HEADER_SIZE;
	u16 पूर्णांकl_size = ISP1362_INTL_BUFFERS * पूर्णांकl_blksize;
	u16 atl_blksize = ISP1362_ATL_BLKSIZE + PTD_HEADER_SIZE;
	u16 atl_buffers = (ISP1362_BUF_SIZE - (istl_size + पूर्णांकl_size)) / atl_blksize;
	u16 atl_size;
	पूर्णांक i;

	WARN_ON(istl_size & 3);
	WARN_ON(atl_blksize & 3);
	WARN_ON(पूर्णांकl_blksize & 3);
	WARN_ON(atl_blksize < PTD_HEADER_SIZE);
	WARN_ON(पूर्णांकl_blksize < PTD_HEADER_SIZE);

	BUG_ON((अचिन्हित)ISP1362_INTL_BUFFERS > 32);
	अगर (atl_buffers > 32)
		atl_buffers = 32;
	atl_size = atl_buffers * atl_blksize;
	total = atl_size + पूर्णांकl_size + istl_size;
	dev_info(hcd->self.controller, "ISP1362 Memory usage:\n");
	dev_info(hcd->self.controller, "  ISTL:    2 * %4d:     %4d @ $%04x:$%04x\n",
		 istl_size / 2, istl_size, 0, istl_size / 2);
	dev_info(hcd->self.controller, "  INTL: %4d * (%3zu+8):  %4d @ $%04x\n",
		 ISP1362_INTL_BUFFERS, पूर्णांकl_blksize - PTD_HEADER_SIZE,
		 पूर्णांकl_size, istl_size);
	dev_info(hcd->self.controller, "  ATL : %4d * (%3zu+8):  %4d @ $%04x\n",
		 atl_buffers, atl_blksize - PTD_HEADER_SIZE,
		 atl_size, istl_size + पूर्णांकl_size);
	dev_info(hcd->self.controller, "  USED/FREE:   %4d      %4d\n", total,
		 ISP1362_BUF_SIZE - total);

	अगर (total > ISP1362_BUF_SIZE) अणु
		dev_err(hcd->self.controller, "%s: Memory requested: %d, available %d\n",
			__func__, total, ISP1362_BUF_SIZE);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&isp1362_hcd->lock, flags);

	क्रम (i = 0; i < 2; i++) अणु
		isp1362_hcd->istl_queue[i].buf_start = i * istl_size / 2,
		isp1362_hcd->istl_queue[i].buf_size = istl_size / 2;
		isp1362_hcd->istl_queue[i].blk_size = 4;
		INIT_LIST_HEAD(&isp1362_hcd->istl_queue[i].active);
		snम_लिखो(isp1362_hcd->istl_queue[i].name,
			 माप(isp1362_hcd->istl_queue[i].name), "ISTL%d", i);
		DBG(3, "%s: %5s buf $%04x %d\n", __func__,
		     isp1362_hcd->istl_queue[i].name,
		     isp1362_hcd->istl_queue[i].buf_start,
		     isp1362_hcd->istl_queue[i].buf_size);
	पूर्ण
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCISTLBUFSZ, istl_size / 2);

	isp1362_hcd->पूर्णांकl_queue.buf_start = istl_size;
	isp1362_hcd->पूर्णांकl_queue.buf_size = पूर्णांकl_size;
	isp1362_hcd->पूर्णांकl_queue.buf_count = ISP1362_INTL_BUFFERS;
	isp1362_hcd->पूर्णांकl_queue.blk_size = पूर्णांकl_blksize;
	isp1362_hcd->पूर्णांकl_queue.buf_avail = isp1362_hcd->पूर्णांकl_queue.buf_count;
	isp1362_hcd->पूर्णांकl_queue.skip_map = ~0;
	INIT_LIST_HEAD(&isp1362_hcd->पूर्णांकl_queue.active);

	isp1362_ग_लिखो_reg16(isp1362_hcd, HCINTLBUFSZ,
			    isp1362_hcd->पूर्णांकl_queue.buf_size);
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCINTLBLKSZ,
			    isp1362_hcd->पूर्णांकl_queue.blk_size - PTD_HEADER_SIZE);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTLSKIP, ~0);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTLLAST,
			    1 << (ISP1362_INTL_BUFFERS - 1));

	isp1362_hcd->atl_queue.buf_start = istl_size + पूर्णांकl_size;
	isp1362_hcd->atl_queue.buf_size = atl_size;
	isp1362_hcd->atl_queue.buf_count = atl_buffers;
	isp1362_hcd->atl_queue.blk_size = atl_blksize;
	isp1362_hcd->atl_queue.buf_avail = isp1362_hcd->atl_queue.buf_count;
	isp1362_hcd->atl_queue.skip_map = ~0;
	INIT_LIST_HEAD(&isp1362_hcd->atl_queue.active);

	isp1362_ग_लिखो_reg16(isp1362_hcd, HCATLBUFSZ,
			    isp1362_hcd->atl_queue.buf_size);
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCATLBLKSZ,
			    isp1362_hcd->atl_queue.blk_size - PTD_HEADER_SIZE);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCATLSKIP, ~0);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCATLLAST,
			    1 << (atl_buffers - 1));

	snम_लिखो(isp1362_hcd->atl_queue.name,
		 माप(isp1362_hcd->atl_queue.name), "ATL");
	snम_लिखो(isp1362_hcd->पूर्णांकl_queue.name,
		 माप(isp1362_hcd->पूर्णांकl_queue.name), "INTL");
	DBG(3, "%s: %5s buf $%04x %2d * %4d = %4d\n", __func__,
	     isp1362_hcd->पूर्णांकl_queue.name,
	     isp1362_hcd->पूर्णांकl_queue.buf_start,
	     ISP1362_INTL_BUFFERS, isp1362_hcd->पूर्णांकl_queue.blk_size,
	     isp1362_hcd->पूर्णांकl_queue.buf_size);
	DBG(3, "%s: %5s buf $%04x %2d * %4d = %4d\n", __func__,
	     isp1362_hcd->atl_queue.name,
	     isp1362_hcd->atl_queue.buf_start,
	     atl_buffers, isp1362_hcd->atl_queue.blk_size,
	     isp1362_hcd->atl_queue.buf_size);

	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1362_hc_reset(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक ret = 0;
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	अचिन्हित दीर्घ t;
	अचिन्हित दीर्घ समयout = 100;
	अचिन्हित दीर्घ flags;
	पूर्णांक clkrdy = 0;

	pr_debug("%s:\n", __func__);

	अगर (isp1362_hcd->board && isp1362_hcd->board->reset) अणु
		isp1362_hcd->board->reset(hcd->self.controller, 1);
		msleep(20);
		अगर (isp1362_hcd->board->घड़ी)
			isp1362_hcd->board->घड़ी(hcd->self.controller, 1);
		isp1362_hcd->board->reset(hcd->self.controller, 0);
	पूर्ण अन्यथा
		isp1362_sw_reset(isp1362_hcd);

	/* chip has been reset. First we need to see a घड़ी */
	t = jअगरfies + msecs_to_jअगरfies(समयout);
	जबतक (!clkrdy && समय_beक्रमe_eq(jअगरfies, t)) अणु
		spin_lock_irqsave(&isp1362_hcd->lock, flags);
		clkrdy = isp1362_पढ़ो_reg16(isp1362_hcd, HCuPINT) & HCuPINT_CLKRDY;
		spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
		अगर (!clkrdy)
			msleep(4);
	पूर्ण

	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINT, HCuPINT_CLKRDY);
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
	अगर (!clkrdy) अणु
		pr_err("Clock not ready after %lums\n", समयout);
		ret = -ENODEV;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम isp1362_hc_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	pr_debug("%s:\n", __func__);

	del_समयr_sync(&hcd->rh_समयr);

	spin_lock_irqsave(&isp1362_hcd->lock, flags);

	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINTENB, 0);

	/* Switch off घातer क्रम all ports */
	पंचांगp = isp1362_पढ़ो_reg32(isp1362_hcd, HCRHDESCA);
	पंचांगp &= ~(RH_A_NPS | RH_A_PSM);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHDESCA, पंचांगp);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHSTATUS, RH_HS_LPS);

	/* Reset the chip */
	अगर (isp1362_hcd->board && isp1362_hcd->board->reset)
		isp1362_hcd->board->reset(hcd->self.controller, 1);
	अन्यथा
		__isp1362_sw_reset(isp1362_hcd);

	अगर (isp1362_hcd->board && isp1362_hcd->board->घड़ी)
		isp1362_hcd->board->घड़ी(hcd->self.controller, 0);

	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
पूर्ण

#अगर_घोषित CHIP_BUFFER_TEST
अटल पूर्णांक isp1362_chip_test(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	पूर्णांक ret = 0;
	u16 *ref;
	अचिन्हित दीर्घ flags;

	ref = kदो_स्मृति(2 * ISP1362_BUF_SIZE, GFP_KERNEL);
	अगर (ref) अणु
		पूर्णांक offset;
		u16 *tst = &ref[ISP1362_BUF_SIZE / 2];

		क्रम (offset = 0; offset < ISP1362_BUF_SIZE / 2; offset++) अणु
			ref[offset] = ~offset;
			tst[offset] = offset;
		पूर्ण

		क्रम (offset = 0; offset < 4; offset++) अणु
			पूर्णांक j;

			क्रम (j = 0; j < 8; j++) अणु
				spin_lock_irqsave(&isp1362_hcd->lock, flags);
				isp1362_ग_लिखो_buffer(isp1362_hcd, (u8 *)ref + offset, 0, j);
				isp1362_पढ़ो_buffer(isp1362_hcd, (u8 *)tst + offset, 0, j);
				spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

				अगर (स_भेद(ref, tst, j)) अणु
					ret = -ENODEV;
					pr_err("%s: memory check with %d byte offset %d failed\n",
					    __func__, j, offset);
					dump_data((u8 *)ref + offset, j);
					dump_data((u8 *)tst + offset, j);
				पूर्ण
			पूर्ण
		पूर्ण

		spin_lock_irqsave(&isp1362_hcd->lock, flags);
		isp1362_ग_लिखो_buffer(isp1362_hcd, ref, 0, ISP1362_BUF_SIZE);
		isp1362_पढ़ो_buffer(isp1362_hcd, tst, 0, ISP1362_BUF_SIZE);
		spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

		अगर (स_भेद(ref, tst, ISP1362_BUF_SIZE)) अणु
			ret = -ENODEV;
			pr_err("%s: memory check failed\n", __func__);
			dump_data((u8 *)tst, ISP1362_BUF_SIZE / 2);
		पूर्ण

		क्रम (offset = 0; offset < 256; offset++) अणु
			पूर्णांक test_size = 0;

			yield();

			स_रखो(tst, 0, ISP1362_BUF_SIZE);
			spin_lock_irqsave(&isp1362_hcd->lock, flags);
			isp1362_ग_लिखो_buffer(isp1362_hcd, tst, 0, ISP1362_BUF_SIZE);
			isp1362_पढ़ो_buffer(isp1362_hcd, tst, 0, ISP1362_BUF_SIZE);
			spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
			अगर (स_भेद(tst, tst + (ISP1362_BUF_SIZE / (2 * माप(*tst))),
				   ISP1362_BUF_SIZE / 2)) अणु
				pr_err("%s: Failed to clear buffer\n", __func__);
				dump_data((u8 *)tst, ISP1362_BUF_SIZE);
				अवरोध;
			पूर्ण
			spin_lock_irqsave(&isp1362_hcd->lock, flags);
			isp1362_ग_लिखो_buffer(isp1362_hcd, ref, offset * 2, PTD_HEADER_SIZE);
			isp1362_ग_लिखो_buffer(isp1362_hcd, ref + PTD_HEADER_SIZE / माप(*ref),
					     offset * 2 + PTD_HEADER_SIZE, test_size);
			isp1362_पढ़ो_buffer(isp1362_hcd, tst, offset * 2,
					    PTD_HEADER_SIZE + test_size);
			spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
			अगर (स_भेद(ref, tst, PTD_HEADER_SIZE + test_size)) अणु
				dump_data(((u8 *)ref) + offset, PTD_HEADER_SIZE + test_size);
				dump_data((u8 *)tst, PTD_HEADER_SIZE + test_size);
				spin_lock_irqsave(&isp1362_hcd->lock, flags);
				isp1362_पढ़ो_buffer(isp1362_hcd, tst, offset * 2,
						    PTD_HEADER_SIZE + test_size);
				spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
				अगर (स_भेद(ref, tst, PTD_HEADER_SIZE + test_size)) अणु
					ret = -ENODEV;
					pr_err("%s: memory check with offset %02x failed\n",
					    __func__, offset);
					अवरोध;
				पूर्ण
				pr_warn("%s: memory check with offset %02x ok after second read\n",
					__func__, offset);
			पूर्ण
		पूर्ण
		kमुक्त(ref);
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक isp1362_hc_start(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक ret;
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	काष्ठा isp1362_platक्रमm_data *board = isp1362_hcd->board;
	u16 hwcfg;
	u16 chipid;
	अचिन्हित दीर्घ flags;

	pr_debug("%s:\n", __func__);

	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	chipid = isp1362_पढ़ो_reg16(isp1362_hcd, HCCHIPID);
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

	अगर ((chipid & HCCHIPID_MASK) != HCCHIPID_MAGIC) अणु
		pr_err("%s: Invalid chip ID %04x\n", __func__, chipid);
		वापस -ENODEV;
	पूर्ण

#अगर_घोषित CHIP_BUFFER_TEST
	ret = isp1362_chip_test(isp1362_hcd);
	अगर (ret)
		वापस -ENODEV;
#पूर्ण_अगर
	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	/* clear पूर्णांकerrupt status and disable all पूर्णांकerrupt sources */
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINT, 0xff);
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINTENB, 0);

	/* HW conf */
	hwcfg = HCHWCFG_INT_ENABLE | HCHWCFG_DBWIDTH(1);
	अगर (board->sel15Kres)
		hwcfg |= HCHWCFG_PULLDOWN_DS2 |
			((MAX_ROOT_PORTS > 1) ? HCHWCFG_PULLDOWN_DS1 : 0);
	अगर (board->clknotstop)
		hwcfg |= HCHWCFG_CLKNOTSTOP;
	अगर (board->oc_enable)
		hwcfg |= HCHWCFG_ANALOG_OC;
	अगर (board->पूर्णांक_act_high)
		hwcfg |= HCHWCFG_INT_POL;
	अगर (board->पूर्णांक_edge_triggered)
		hwcfg |= HCHWCFG_INT_TRIGGER;
	अगर (board->dreq_act_high)
		hwcfg |= HCHWCFG_DREQ_POL;
	अगर (board->dack_act_high)
		hwcfg |= HCHWCFG_DACK_POL;
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCHWCFG, hwcfg);
	isp1362_show_reg(isp1362_hcd, HCHWCFG);
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCDMACFG, 0);
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

	ret = isp1362_mem_config(hcd);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&isp1362_hcd->lock, flags);

	/* Root hub conf */
	isp1362_hcd->rhdesca = 0;
	अगर (board->no_घातer_चयनing)
		isp1362_hcd->rhdesca |= RH_A_NPS;
	अगर (board->घातer_चयनing_mode)
		isp1362_hcd->rhdesca |= RH_A_PSM;
	अगर (board->potpg)
		isp1362_hcd->rhdesca |= (board->potpg << 24) & RH_A_POTPGT;
	अन्यथा
		isp1362_hcd->rhdesca |= (25 << 24) & RH_A_POTPGT;

	isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHDESCA, isp1362_hcd->rhdesca & ~RH_A_OCPM);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHDESCA, isp1362_hcd->rhdesca | RH_A_OCPM);
	isp1362_hcd->rhdesca = isp1362_पढ़ो_reg32(isp1362_hcd, HCRHDESCA);

	isp1362_hcd->rhdescb = RH_B_PPCM;
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHDESCB, isp1362_hcd->rhdescb);
	isp1362_hcd->rhdescb = isp1362_पढ़ो_reg32(isp1362_hcd, HCRHDESCB);

	isp1362_पढ़ो_reg32(isp1362_hcd, HCFMINTVL);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCFMINTVL, (FSMP(FI) << 16) | FI);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCLSTHRESH, LSTHRESH);

	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

	isp1362_hcd->hc_control = OHCI_USB_OPER;
	hcd->state = HC_STATE_RUNNING;

	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	/* Set up पूर्णांकerrupts */
	isp1362_hcd->पूर्णांकenb = OHCI_INTR_MIE | OHCI_INTR_RHSC | OHCI_INTR_UE;
	isp1362_hcd->पूर्णांकenb |= OHCI_INTR_RD;
	isp1362_hcd->irqenb = HCuPINT_OPR | HCuPINT_SUSP;
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCINTENB, isp1362_hcd->पूर्णांकenb);
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINTENB, isp1362_hcd->irqenb);

	/* Go operational */
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCCONTROL, isp1362_hcd->hc_control);
	/* enable global घातer */
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHSTATUS, RH_HS_LPSC | RH_HS_DRWE);

	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा hc_driver isp1362_hc_driver = अणु
	.description =		hcd_name,
	.product_desc =		"ISP1362 Host Controller",
	.hcd_priv_size =	माप(काष्ठा isp1362_hcd),

	.irq =			isp1362_irq,
	.flags =		HCD_USB11 | HCD_MEMORY,

	.reset =		isp1362_hc_reset,
	.start =		isp1362_hc_start,
	.stop =			isp1362_hc_stop,

	.urb_enqueue =		isp1362_urb_enqueue,
	.urb_dequeue =		isp1362_urb_dequeue,
	.endpoपूर्णांक_disable =	isp1362_endpoपूर्णांक_disable,

	.get_frame_number =	isp1362_get_frame,

	.hub_status_data =	isp1362_hub_status_data,
	.hub_control =		isp1362_hub_control,
	.bus_suspend =		isp1362_bus_suspend,
	.bus_resume =		isp1362_bus_resume,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक isp1362_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);

	हटाओ_debug_file(isp1362_hcd);
	DBG(0, "%s: Removing HCD\n", __func__);
	usb_हटाओ_hcd(hcd);
	DBG(0, "%s: put_hcd\n", __func__);
	usb_put_hcd(hcd);
	DBG(0, "%s: Done\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1362_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा isp1362_hcd *isp1362_hcd;
	काष्ठा resource *data, *irq_res;
	व्योम __iomem *addr_reg;
	व्योम __iomem *data_reg;
	पूर्णांक irq;
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक irq_flags = 0;

	अगर (usb_disabled())
		वापस -ENODEV;

	/* basic sanity checks first.  board-specअगरic init logic should
	 * have initialized this the three resources and probably board
	 * specअगरic platक्रमm_data.  we करोn't probe क्रम IRQs, and करो only
	 * minimal sanity checking.
	 */
	अगर (pdev->num_resources < 3)
		वापस -ENODEV;

	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq_res)
		वापस -ENODEV;

	irq = irq_res->start;

	addr_reg = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(addr_reg))
		वापस PTR_ERR(addr_reg);

	data = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data_reg = devm_ioremap_resource(&pdev->dev, data);
	अगर (IS_ERR(data_reg))
		वापस PTR_ERR(data_reg);

	/* allocate and initialize hcd */
	hcd = usb_create_hcd(&isp1362_hc_driver, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd)
		वापस -ENOMEM;

	hcd->rsrc_start = data->start;
	isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	isp1362_hcd->data_reg = data_reg;
	isp1362_hcd->addr_reg = addr_reg;

	isp1362_hcd->next_statechange = jअगरfies;
	spin_lock_init(&isp1362_hcd->lock);
	INIT_LIST_HEAD(&isp1362_hcd->async);
	INIT_LIST_HEAD(&isp1362_hcd->periodic);
	INIT_LIST_HEAD(&isp1362_hcd->isoc);
	INIT_LIST_HEAD(&isp1362_hcd->हटाओ_list);
	isp1362_hcd->board = dev_get_platdata(&pdev->dev);
#अगर USE_PLATFORM_DELAY
	अगर (!isp1362_hcd->board->delay) अणु
		dev_err(hcd->self.controller, "No platform delay function given\n");
		retval = -ENODEV;
		जाओ err;
	पूर्ण
#पूर्ण_अगर

	अगर (irq_res->flags & IORESOURCE_IRQ_HIGHEDGE)
		irq_flags |= IRQF_TRIGGER_RISING;
	अगर (irq_res->flags & IORESOURCE_IRQ_LOWEDGE)
		irq_flags |= IRQF_TRIGGER_FALLING;
	अगर (irq_res->flags & IORESOURCE_IRQ_HIGHLEVEL)
		irq_flags |= IRQF_TRIGGER_HIGH;
	अगर (irq_res->flags & IORESOURCE_IRQ_LOWLEVEL)
		irq_flags |= IRQF_TRIGGER_LOW;

	retval = usb_add_hcd(hcd, irq, irq_flags | IRQF_SHARED);
	अगर (retval != 0)
		जाओ err;
	device_wakeup_enable(hcd->self.controller);

	dev_info(&pdev->dev, "%s, irq %d\n", hcd->product_desc, irq);

	create_debug_file(isp1362_hcd);

	वापस 0;

 err:
	usb_put_hcd(hcd);

	वापस retval;
पूर्ण

#अगर_घोषित	CONFIG_PM
अटल पूर्णांक isp1362_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	DBG(0, "%s: Suspending device\n", __func__);

	अगर (state.event == PM_EVENT_FREEZE) अणु
		DBG(0, "%s: Suspending root hub\n", __func__);
		retval = isp1362_bus_suspend(hcd);
	पूर्ण अन्यथा अणु
		DBG(0, "%s: Suspending RH ports\n", __func__);
		spin_lock_irqsave(&isp1362_hcd->lock, flags);
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHSTATUS, RH_HS_LPS);
		spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
	पूर्ण
	अगर (retval == 0)
		pdev->dev.घातer.घातer_state = state;
	वापस retval;
पूर्ण

अटल पूर्णांक isp1362_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	अचिन्हित दीर्घ flags;

	DBG(0, "%s: Resuming\n", __func__);

	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_SUSPEND) अणु
		DBG(0, "%s: Resume RH ports\n", __func__);
		spin_lock_irqsave(&isp1362_hcd->lock, flags);
		isp1362_ग_लिखो_reg32(isp1362_hcd, HCRHSTATUS, RH_HS_LPSC);
		spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
		वापस 0;
	पूर्ण

	pdev->dev.घातer.घातer_state = PMSG_ON;

	वापस isp1362_bus_resume(isp1362_hcd_to_hcd(isp1362_hcd));
पूर्ण
#अन्यथा
#घोषणा	isp1362_suspend	शून्य
#घोषणा	isp1362_resume	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver isp1362_driver = अणु
	.probe = isp1362_probe,
	.हटाओ = isp1362_हटाओ,

	.suspend = isp1362_suspend,
	.resume = isp1362_resume,
	.driver = अणु
		.name = hcd_name,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(isp1362_driver);
