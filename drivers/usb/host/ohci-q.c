<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 *
 * This file is licenced under the GPL.
 */

#समावेश <linux/irq.h>
#समावेश <linux/slab.h>

अटल व्योम urb_मुक्त_priv (काष्ठा ohci_hcd *hc, urb_priv_t *urb_priv)
अणु
	पूर्णांक		last = urb_priv->length - 1;

	अगर (last >= 0) अणु
		पूर्णांक		i;
		काष्ठा td	*td;

		क्रम (i = 0; i <= last; i++) अणु
			td = urb_priv->td [i];
			अगर (td)
				td_मुक्त (hc, td);
		पूर्ण
	पूर्ण

	list_del (&urb_priv->pending);
	kमुक्त (urb_priv);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * URB goes back to driver, and isn't reissued.
 * It's completely gone from HC data काष्ठाures.
 * PRECONDITION:  ohci lock held, irqs blocked.
 */
अटल व्योम
finish_urb(काष्ठा ohci_hcd *ohci, काष्ठा urb *urb, पूर्णांक status)
__releases(ohci->lock)
__acquires(ohci->lock)
अणु
	काष्ठा device *dev = ohci_to_hcd(ohci)->self.controller;
	काष्ठा usb_host_endpoपूर्णांक *ep = urb->ep;
	काष्ठा urb_priv *urb_priv;

	// ASSERT (urb->hcpriv != 0);

 restart:
	urb_मुक्त_priv (ohci, urb->hcpriv);
	urb->hcpriv = शून्य;
	अगर (likely(status == -EINPROGRESS))
		status = 0;

	चयन (usb_pipetype (urb->pipe)) अणु
	हाल PIPE_ISOCHRONOUS:
		ohci_to_hcd(ohci)->self.bandwidth_isoc_reqs--;
		अगर (ohci_to_hcd(ohci)->self.bandwidth_isoc_reqs == 0) अणु
			अगर (quirk_amdiso(ohci))
				usb_amd_quirk_pll_enable();
			अगर (quirk_amdprefetch(ohci))
				sb800_prefetch(dev, 0);
		पूर्ण
		अवरोध;
	हाल PIPE_INTERRUPT:
		ohci_to_hcd(ohci)->self.bandwidth_पूर्णांक_reqs--;
		अवरोध;
	पूर्ण

	/* urb->complete() can reenter this HCD */
	usb_hcd_unlink_urb_from_ep(ohci_to_hcd(ohci), urb);
	spin_unlock (&ohci->lock);
	usb_hcd_giveback_urb(ohci_to_hcd(ohci), urb, status);
	spin_lock (&ohci->lock);

	/* stop periodic dma अगर it's not needed */
	अगर (ohci_to_hcd(ohci)->self.bandwidth_isoc_reqs == 0
			&& ohci_to_hcd(ohci)->self.bandwidth_पूर्णांक_reqs == 0) अणु
		ohci->hc_control &= ~(OHCI_CTRL_PLE|OHCI_CTRL_IE);
		ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
	पूर्ण

	/*
	 * An isochronous URB that is sumitted too late won't have any TDs
	 * (marked by the fact that the td_cnt value is larger than the
	 * actual number of TDs).  If the next URB on this endpoपूर्णांक is like
	 * that, give it back now.
	 */
	अगर (!list_empty(&ep->urb_list)) अणु
		urb = list_first_entry(&ep->urb_list, काष्ठा urb, urb_list);
		urb_priv = urb->hcpriv;
		अगर (urb_priv->td_cnt > urb_priv->length) अणु
			status = 0;
			जाओ restart;
		पूर्ण
	पूर्ण
पूर्ण


/*-------------------------------------------------------------------------*
 * ED handling functions
 *-------------------------------------------------------------------------*/

/* search क्रम the right schedule branch to use क्रम a periodic ed.
 * करोes some load balancing; वापसs the branch, or negative त्रुटि_सं.
 */
अटल पूर्णांक balance (काष्ठा ohci_hcd *ohci, पूर्णांक पूर्णांकerval, पूर्णांक load)
अणु
	पूर्णांक	i, branch = -ENOSPC;

	/* iso periods can be huge; iso tds specअगरy frame numbers */
	अगर (पूर्णांकerval > NUM_INTS)
		पूर्णांकerval = NUM_INTS;

	/* search क्रम the least loaded schedule branch of that period
	 * that has enough bandwidth left unreserved.
	 */
	क्रम (i = 0; i < पूर्णांकerval ; i++) अणु
		अगर (branch < 0 || ohci->load [branch] > ohci->load [i]) अणु
			पूर्णांक	j;

			/* usb 1.1 says 90% of one frame */
			क्रम (j = i; j < NUM_INTS; j += पूर्णांकerval) अणु
				अगर ((ohci->load [j] + load) > 900)
					अवरोध;
			पूर्ण
			अगर (j < NUM_INTS)
				जारी;
			branch = i;
		पूर्ण
	पूर्ण
	वापस branch;
पूर्ण

/*-------------------------------------------------------------------------*/

/* both iso and पूर्णांकerrupt requests have periods; this routine माला_दो them
 * पूर्णांकo the schedule tree in the apppropriate place.  most iso devices use
 * 1msec periods, but that's not required.
 */
अटल व्योम periodic_link (काष्ठा ohci_hcd *ohci, काष्ठा ed *ed)
अणु
	अचिन्हित	i;

	ohci_dbg(ohci, "link %sed %p branch %d [%dus.], interval %d\n",
		(ed->hwINFO & cpu_to_hc32 (ohci, ED_ISO)) ? "iso " : "",
		ed, ed->branch, ed->load, ed->पूर्णांकerval);

	क्रम (i = ed->branch; i < NUM_INTS; i += ed->पूर्णांकerval) अणु
		काष्ठा ed	**prev = &ohci->periodic [i];
		__hc32		*prev_p = &ohci->hcca->पूर्णांक_table [i];
		काष्ठा ed	*here = *prev;

		/* sorting each branch by period (slow beक्रमe fast)
		 * lets us share the faster parts of the tree.
		 * (plus maybe: put पूर्णांकerrupt eds beक्रमe iso)
		 */
		जबतक (here && ed != here) अणु
			अगर (ed->पूर्णांकerval > here->पूर्णांकerval)
				अवरोध;
			prev = &here->ed_next;
			prev_p = &here->hwNextED;
			here = *prev;
		पूर्ण
		अगर (ed != here) अणु
			ed->ed_next = here;
			अगर (here)
				ed->hwNextED = *prev_p;
			wmb ();
			*prev = ed;
			*prev_p = cpu_to_hc32(ohci, ed->dma);
			wmb();
		पूर्ण
		ohci->load [i] += ed->load;
	पूर्ण
	ohci_to_hcd(ohci)->self.bandwidth_allocated += ed->load / ed->पूर्णांकerval;
पूर्ण

/* link an ed पूर्णांकo one of the HC chains */

अटल पूर्णांक ed_schedule (काष्ठा ohci_hcd *ohci, काष्ठा ed *ed)
अणु
	पूर्णांक	branch;

	ed->ed_prev = शून्य;
	ed->ed_next = शून्य;
	ed->hwNextED = 0;
	wmb ();

	/* we care about rm_list when setting CLE/BLE in हाल the HC was at
	 * work on some TD when CLE/BLE was turned off, and isn't quiesced
	 * yet.  finish_unlinks() restarts as needed, some upcoming INTR_SF.
	 *
	 * control and bulk EDs are करोubly linked (ed_next, ed_prev), but
	 * periodic ones are singly linked (ed_next). that's because the
	 * periodic schedule encodes a tree like figure 3-5 in the ohci
	 * spec:  each qh can have several "previous" nodes, and the tree
	 * करोesn't have unused/idle descriptors.
	 */
	चयन (ed->type) अणु
	हाल PIPE_CONTROL:
		अगर (ohci->ed_controltail == शून्य) अणु
			WARN_ON (ohci->hc_control & OHCI_CTRL_CLE);
			ohci_ग_लिखोl (ohci, ed->dma,
					&ohci->regs->ed_controlhead);
		पूर्ण अन्यथा अणु
			ohci->ed_controltail->ed_next = ed;
			ohci->ed_controltail->hwNextED = cpu_to_hc32 (ohci,
								ed->dma);
		पूर्ण
		ed->ed_prev = ohci->ed_controltail;
		अगर (!ohci->ed_controltail && !ohci->ed_rm_list) अणु
			wmb();
			ohci->hc_control |= OHCI_CTRL_CLE;
			ohci_ग_लिखोl (ohci, 0, &ohci->regs->ed_controlcurrent);
			ohci_ग_लिखोl (ohci, ohci->hc_control,
					&ohci->regs->control);
		पूर्ण
		ohci->ed_controltail = ed;
		अवरोध;

	हाल PIPE_BULK:
		अगर (ohci->ed_bulktail == शून्य) अणु
			WARN_ON (ohci->hc_control & OHCI_CTRL_BLE);
			ohci_ग_लिखोl (ohci, ed->dma, &ohci->regs->ed_bulkhead);
		पूर्ण अन्यथा अणु
			ohci->ed_bulktail->ed_next = ed;
			ohci->ed_bulktail->hwNextED = cpu_to_hc32 (ohci,
								ed->dma);
		पूर्ण
		ed->ed_prev = ohci->ed_bulktail;
		अगर (!ohci->ed_bulktail && !ohci->ed_rm_list) अणु
			wmb();
			ohci->hc_control |= OHCI_CTRL_BLE;
			ohci_ग_लिखोl (ohci, 0, &ohci->regs->ed_bulkcurrent);
			ohci_ग_लिखोl (ohci, ohci->hc_control,
					&ohci->regs->control);
		पूर्ण
		ohci->ed_bulktail = ed;
		अवरोध;

	// हाल PIPE_INTERRUPT:
	// हाल PIPE_ISOCHRONOUS:
	शेष:
		branch = balance (ohci, ed->पूर्णांकerval, ed->load);
		अगर (branch < 0) अणु
			ohci_dbg (ohci,
				"ERR %d, interval %d msecs, load %d\n",
				branch, ed->पूर्णांकerval, ed->load);
			// FIXME अगर there are TDs queued, fail them!
			वापस branch;
		पूर्ण
		ed->branch = branch;
		periodic_link (ohci, ed);
	पूर्ण

	/* the HC may not see the schedule updates yet, but अगर it करोes
	 * then they'll be properly ordered.
	 */

	ed->state = ED_OPER;
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

/* scan the periodic table to find and unlink this ED */
अटल व्योम periodic_unlink (काष्ठा ohci_hcd *ohci, काष्ठा ed *ed)
अणु
	पूर्णांक	i;

	क्रम (i = ed->branch; i < NUM_INTS; i += ed->पूर्णांकerval) अणु
		काष्ठा ed	*temp;
		काष्ठा ed	**prev = &ohci->periodic [i];
		__hc32		*prev_p = &ohci->hcca->पूर्णांक_table [i];

		जबतक (*prev && (temp = *prev) != ed) अणु
			prev_p = &temp->hwNextED;
			prev = &temp->ed_next;
		पूर्ण
		अगर (*prev) अणु
			*prev_p = ed->hwNextED;
			*prev = ed->ed_next;
		पूर्ण
		ohci->load [i] -= ed->load;
	पूर्ण
	ohci_to_hcd(ohci)->self.bandwidth_allocated -= ed->load / ed->पूर्णांकerval;

	ohci_dbg(ohci, "unlink %sed %p branch %d [%dus.], interval %d\n",
		(ed->hwINFO & cpu_to_hc32 (ohci, ED_ISO)) ? "iso " : "",
		ed, ed->branch, ed->load, ed->पूर्णांकerval);
पूर्ण

/* unlink an ed from one of the HC chains.
 * just the link to the ed is unlinked.
 * the link from the ed still poपूर्णांकs to another operational ed or 0
 * so the HC can eventually finish the processing of the unlinked ed
 * (assuming it alपढ़ोy started that, which needn't be true).
 *
 * ED_UNLINK is a transient state: the HC may still see this ED, but soon
 * it won't.  ED_SKIP means the HC will finish its current transaction,
 * but won't start anything new.  The TD queue may still grow; device
 * drivers करोn't know about this HCD-पूर्णांकernal state.
 *
 * When the HC can't see the ED, something changes ED_UNLINK to one of:
 *
 *  - ED_OPER: when there's any request queued, the ED माला_लो rescheduled
 *    immediately.  HC should be working on them.
 *
 *  - ED_IDLE: when there's no TD queue or the HC isn't running.
 *
 * When finish_unlinks() runs later, after SOF पूर्णांकerrupt, it will often
 * complete one or more URB unlinks beक्रमe making that state change.
 */
अटल व्योम ed_deschedule (काष्ठा ohci_hcd *ohci, काष्ठा ed *ed)
अणु
	ed->hwINFO |= cpu_to_hc32 (ohci, ED_SKIP);
	wmb ();
	ed->state = ED_UNLINK;

	/* To deschedule something from the control or bulk list, just
	 * clear CLE/BLE and रुको.  There's no safe way to scrub out list
	 * head/current रेजिस्टरs until later, and "later" isn't very
	 * tightly specअगरied.  Figure 6-5 and Section 6.4.2.2 show how
	 * the HC is पढ़ोing the ED queues (जबतक we modअगरy them).
	 *
	 * For now, ed_schedule() is "later".  It might be good paranoia
	 * to scrub those रेजिस्टरs in finish_unlinks(), in हाल of bugs
	 * that make the HC try to use them.
	 */
	चयन (ed->type) अणु
	हाल PIPE_CONTROL:
		/* हटाओ ED from the HC's list: */
		अगर (ed->ed_prev == शून्य) अणु
			अगर (!ed->hwNextED) अणु
				ohci->hc_control &= ~OHCI_CTRL_CLE;
				ohci_ग_लिखोl (ohci, ohci->hc_control,
						&ohci->regs->control);
				// a ohci_पढ़ोl() later syncs CLE with the HC
			पूर्ण अन्यथा
				ohci_ग_लिखोl (ohci,
					hc32_to_cpup (ohci, &ed->hwNextED),
					&ohci->regs->ed_controlhead);
		पूर्ण अन्यथा अणु
			ed->ed_prev->ed_next = ed->ed_next;
			ed->ed_prev->hwNextED = ed->hwNextED;
		पूर्ण
		/* हटाओ ED from the HCD's list: */
		अगर (ohci->ed_controltail == ed) अणु
			ohci->ed_controltail = ed->ed_prev;
			अगर (ohci->ed_controltail)
				ohci->ed_controltail->ed_next = शून्य;
		पूर्ण अन्यथा अगर (ed->ed_next) अणु
			ed->ed_next->ed_prev = ed->ed_prev;
		पूर्ण
		अवरोध;

	हाल PIPE_BULK:
		/* हटाओ ED from the HC's list: */
		अगर (ed->ed_prev == शून्य) अणु
			अगर (!ed->hwNextED) अणु
				ohci->hc_control &= ~OHCI_CTRL_BLE;
				ohci_ग_लिखोl (ohci, ohci->hc_control,
						&ohci->regs->control);
				// a ohci_पढ़ोl() later syncs BLE with the HC
			पूर्ण अन्यथा
				ohci_ग_लिखोl (ohci,
					hc32_to_cpup (ohci, &ed->hwNextED),
					&ohci->regs->ed_bulkhead);
		पूर्ण अन्यथा अणु
			ed->ed_prev->ed_next = ed->ed_next;
			ed->ed_prev->hwNextED = ed->hwNextED;
		पूर्ण
		/* हटाओ ED from the HCD's list: */
		अगर (ohci->ed_bulktail == ed) अणु
			ohci->ed_bulktail = ed->ed_prev;
			अगर (ohci->ed_bulktail)
				ohci->ed_bulktail->ed_next = शून्य;
		पूर्ण अन्यथा अगर (ed->ed_next) अणु
			ed->ed_next->ed_prev = ed->ed_prev;
		पूर्ण
		अवरोध;

	// हाल PIPE_INTERRUPT:
	// हाल PIPE_ISOCHRONOUS:
	शेष:
		periodic_unlink (ohci, ed);
		अवरोध;
	पूर्ण
पूर्ण


/*-------------------------------------------------------------------------*/

/* get and maybe (re)init an endpoपूर्णांक. init _should_ be करोne only as part
 * of क्रमागतeration, usb_set_configuration() or usb_set_पूर्णांकerface().
 */
अटल काष्ठा ed *ed_get (
	काष्ठा ohci_hcd		*ohci,
	काष्ठा usb_host_endpoपूर्णांक *ep,
	काष्ठा usb_device	*udev,
	अचिन्हित पूर्णांक		pipe,
	पूर्णांक			पूर्णांकerval
) अणु
	काष्ठा ed		*ed;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave (&ohci->lock, flags);

	ed = ep->hcpriv;
	अगर (!ed) अणु
		काष्ठा td	*td;
		पूर्णांक		is_out;
		u32		info;

		ed = ed_alloc (ohci, GFP_ATOMIC);
		अगर (!ed) अणु
			/* out of memory */
			जाओ करोne;
		पूर्ण

		/* dummy td; end of td list क्रम ed */
		td = td_alloc (ohci, GFP_ATOMIC);
		अगर (!td) अणु
			/* out of memory */
			ed_मुक्त (ohci, ed);
			ed = शून्य;
			जाओ करोne;
		पूर्ण
		ed->dummy = td;
		ed->hwTailP = cpu_to_hc32 (ohci, td->td_dma);
		ed->hwHeadP = ed->hwTailP;	/* ED_C, ED_H zeroed */
		ed->state = ED_IDLE;

		is_out = !(ep->desc.bEndpoपूर्णांकAddress & USB_सूची_IN);

		/* FIXME usbcore changes dev->devnum beक्रमe SET_ADDRESS
		 * succeeds ... otherwise we wouldn't need "pipe".
		 */
		info = usb_pipedevice (pipe);
		ed->type = usb_pipetype(pipe);

		info |= (ep->desc.bEndpoपूर्णांकAddress & ~USB_सूची_IN) << 7;
		info |= usb_endpoपूर्णांक_maxp(&ep->desc) << 16;
		अगर (udev->speed == USB_SPEED_LOW)
			info |= ED_LOWSPEED;
		/* only control transfers store pids in tds */
		अगर (ed->type != PIPE_CONTROL) अणु
			info |= is_out ? ED_OUT : ED_IN;
			अगर (ed->type != PIPE_BULK) अणु
				/* periodic transfers... */
				अगर (ed->type == PIPE_ISOCHRONOUS)
					info |= ED_ISO;
				अन्यथा अगर (पूर्णांकerval > 32)	/* iso can be bigger */
					पूर्णांकerval = 32;
				ed->पूर्णांकerval = पूर्णांकerval;
				ed->load = usb_calc_bus_समय (
					udev->speed, !is_out,
					ed->type == PIPE_ISOCHRONOUS,
					usb_endpoपूर्णांक_maxp(&ep->desc))
						/ 1000;
			पूर्ण
		पूर्ण
		ed->hwINFO = cpu_to_hc32(ohci, info);

		ep->hcpriv = ed;
	पूर्ण

करोne:
	spin_unlock_irqrestore (&ohci->lock, flags);
	वापस ed;
पूर्ण

/*-------------------------------------------------------------------------*/

/* request unlinking of an endpoपूर्णांक from an operational HC.
 * put the ep on the rm_list
 * real work is करोne at the next start frame (SF) hardware पूर्णांकerrupt
 * caller guarantees HCD is running, so hardware access is safe,
 * and that ed->state is ED_OPER
 */
अटल व्योम start_ed_unlink (काष्ठा ohci_hcd *ohci, काष्ठा ed *ed)
अणु
	ed->hwINFO |= cpu_to_hc32 (ohci, ED_DEQUEUE);
	ed_deschedule (ohci, ed);

	/* rm_list is just singly linked, क्रम simplicity */
	ed->ed_next = ohci->ed_rm_list;
	ed->ed_prev = शून्य;
	ohci->ed_rm_list = ed;

	/* enable SOF पूर्णांकerrupt */
	ohci_ग_लिखोl (ohci, OHCI_INTR_SF, &ohci->regs->पूर्णांकrstatus);
	ohci_ग_लिखोl (ohci, OHCI_INTR_SF, &ohci->regs->पूर्णांकrenable);
	// flush those ग_लिखोs, and get latest HCCA contents
	(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);

	/* SF पूर्णांकerrupt might get delayed; record the frame counter value that
	 * indicates when the HC isn't looking at it, so concurrent unlinks
	 * behave.  frame_no wraps every 2^16 msec, and changes right beक्रमe
	 * SF is triggered.
	 */
	ed->tick = ohci_frame_no(ohci) + 1;

पूर्ण

/*-------------------------------------------------------------------------*
 * TD handling functions
 *-------------------------------------------------------------------------*/

/* enqueue next TD क्रम this URB (OHCI spec 5.2.8.2) */

अटल व्योम
td_fill (काष्ठा ohci_hcd *ohci, u32 info,
	dma_addr_t data, पूर्णांक len,
	काष्ठा urb *urb, पूर्णांक index)
अणु
	काष्ठा td		*td, *td_pt;
	काष्ठा urb_priv		*urb_priv = urb->hcpriv;
	पूर्णांक			is_iso = info & TD_ISO;
	पूर्णांक			hash;

	// ASSERT (index < urb_priv->length);

	/* aim क्रम only one पूर्णांकerrupt per urb.  mostly applies to control
	 * and iso; other urbs rarely need more than one TD per urb.
	 * this way, only final tds (or ones with an error) cause IRQs.
	 * at least immediately; use DI=6 in हाल any control request is
	 * tempted to die part way through.  (and to क्रमce the hc to flush
	 * its करोnelist soonish, even on unlink paths.)
	 *
	 * NOTE: could delay पूर्णांकerrupts even क्रम the last TD, and get fewer
	 * पूर्णांकerrupts ... increasing per-urb latency by sharing पूर्णांकerrupts.
	 * Drivers that queue bulk urbs may request that behavior.
	 */
	अगर (index != (urb_priv->length - 1)
			|| (urb->transfer_flags & URB_NO_INTERRUPT))
		info |= TD_DI_SET (6);

	/* use this td as the next dummy */
	td_pt = urb_priv->td [index];

	/* fill the old dummy TD */
	td = urb_priv->td [index] = urb_priv->ed->dummy;
	urb_priv->ed->dummy = td_pt;

	td->ed = urb_priv->ed;
	td->next_dl_td = शून्य;
	td->index = index;
	td->urb = urb;
	td->data_dma = data;
	अगर (!len)
		data = 0;

	td->hwINFO = cpu_to_hc32 (ohci, info);
	अगर (is_iso) अणु
		td->hwCBP = cpu_to_hc32 (ohci, data & 0xFFFFF000);
		*ohci_hwPSWp(ohci, td, 0) = cpu_to_hc16 (ohci,
						(data & 0x0FFF) | 0xE000);
	पूर्ण अन्यथा अणु
		td->hwCBP = cpu_to_hc32 (ohci, data);
	पूर्ण
	अगर (data)
		td->hwBE = cpu_to_hc32 (ohci, data + len - 1);
	अन्यथा
		td->hwBE = 0;
	td->hwNextTD = cpu_to_hc32 (ohci, td_pt->td_dma);

	/* append to queue */
	list_add_tail (&td->td_list, &td->ed->td_list);

	/* hash it क्रम later reverse mapping */
	hash = TD_HASH_FUNC (td->td_dma);
	td->td_hash = ohci->td_hash [hash];
	ohci->td_hash [hash] = td;

	/* HC might पढ़ो the TD (or cachelines) right away ... */
	wmb ();
	td->ed->hwTailP = td->hwNextTD;
पूर्ण

/*-------------------------------------------------------------------------*/

/* Prepare all TDs of a transfer, and queue them onto the ED.
 * Caller guarantees HC is active.
 * Usually the ED is alपढ़ोy on the schedule, so TDs might be
 * processed as soon as they're queued.
 */
अटल व्योम td_submit_urb (
	काष्ठा ohci_hcd	*ohci,
	काष्ठा urb	*urb
) अणु
	काष्ठा urb_priv	*urb_priv = urb->hcpriv;
	काष्ठा device *dev = ohci_to_hcd(ohci)->self.controller;
	dma_addr_t	data;
	पूर्णांक		data_len = urb->transfer_buffer_length;
	पूर्णांक		cnt = 0;
	u32		info = 0;
	पूर्णांक		is_out = usb_pipeout (urb->pipe);
	पूर्णांक		periodic = 0;
	पूर्णांक		i, this_sg_len, n;
	काष्ठा scatterlist	*sg;

	/* OHCI handles the bulk/पूर्णांकerrupt data toggles itself.  We just
	 * use the device toggle bits क्रम resetting, and rely on the fact
	 * that resetting toggle is meaningless अगर the endpoपूर्णांक is active.
	 */
	अगर (!usb_gettoggle (urb->dev, usb_pipeendpoपूर्णांक (urb->pipe), is_out)) अणु
		usb_settoggle (urb->dev, usb_pipeendpoपूर्णांक (urb->pipe),
			is_out, 1);
		urb_priv->ed->hwHeadP &= ~cpu_to_hc32 (ohci, ED_C);
	पूर्ण

	list_add (&urb_priv->pending, &ohci->pending);

	i = urb->num_mapped_sgs;
	अगर (data_len > 0 && i > 0) अणु
		sg = urb->sg;
		data = sg_dma_address(sg);

		/*
		 * urb->transfer_buffer_length may be smaller than the
		 * size of the scatterlist (or vice versa)
		 */
		this_sg_len = min_t(पूर्णांक, sg_dma_len(sg), data_len);
	पूर्ण अन्यथा अणु
		sg = शून्य;
		अगर (data_len)
			data = urb->transfer_dma;
		अन्यथा
			data = 0;
		this_sg_len = data_len;
	पूर्ण

	/* NOTE:  TD_CC is set so we can tell which TDs the HC processed by
	 * using TD_CC_GET, as well as by seeing them on the करोne list.
	 * (CC = NotAccessed ... 0x0F, or 0x0E in PSWs क्रम ISO.)
	 */
	चयन (urb_priv->ed->type) अणु

	/* Bulk and पूर्णांकerrupt are identical except क्रम where in the schedule
	 * their EDs live.
	 */
	हाल PIPE_INTERRUPT:
		/* ... and periodic urbs have extra accounting */
		periodic = ohci_to_hcd(ohci)->self.bandwidth_पूर्णांक_reqs++ == 0
			&& ohci_to_hcd(ohci)->self.bandwidth_isoc_reqs == 0;
		fallthrough;
	हाल PIPE_BULK:
		info = is_out
			? TD_T_TOGGLE | TD_CC | TD_DP_OUT
			: TD_T_TOGGLE | TD_CC | TD_DP_IN;
		/* TDs _could_ transfer up to 8K each */
		क्रम (;;) अणु
			n = min(this_sg_len, 4096);

			/* maybe aव्योम ED halt on final TD लघु पढ़ो */
			अगर (n >= data_len || (i == 1 && n >= this_sg_len)) अणु
				अगर (!(urb->transfer_flags & URB_SHORT_NOT_OK))
					info |= TD_R;
			पूर्ण
			td_fill(ohci, info, data, n, urb, cnt);
			this_sg_len -= n;
			data_len -= n;
			data += n;
			cnt++;

			अगर (this_sg_len <= 0) अणु
				अगर (--i <= 0 || data_len <= 0)
					अवरोध;
				sg = sg_next(sg);
				data = sg_dma_address(sg);
				this_sg_len = min_t(पूर्णांक, sg_dma_len(sg),
						data_len);
			पूर्ण
		पूर्ण
		अगर ((urb->transfer_flags & URB_ZERO_PACKET)
				&& cnt < urb_priv->length) अणु
			td_fill (ohci, info, 0, 0, urb, cnt);
			cnt++;
		पूर्ण
		/* maybe kickstart bulk list */
		अगर (urb_priv->ed->type == PIPE_BULK) अणु
			wmb ();
			ohci_ग_लिखोl (ohci, OHCI_BLF, &ohci->regs->cmdstatus);
		पूर्ण
		अवरोध;

	/* control manages DATA0/DATA1 toggle per-request; SETUP resets it,
	 * any DATA phase works normally, and the STATUS ack is special.
	 */
	हाल PIPE_CONTROL:
		info = TD_CC | TD_DP_SETUP | TD_T_DATA0;
		td_fill (ohci, info, urb->setup_dma, 8, urb, cnt++);
		अगर (data_len > 0) अणु
			info = TD_CC | TD_R | TD_T_DATA1;
			info |= is_out ? TD_DP_OUT : TD_DP_IN;
			/* NOTE:  mishandles transfers >8K, some >4K */
			td_fill (ohci, info, data, data_len, urb, cnt++);
		पूर्ण
		info = (is_out || data_len == 0)
			? TD_CC | TD_DP_IN | TD_T_DATA1
			: TD_CC | TD_DP_OUT | TD_T_DATA1;
		td_fill (ohci, info, data, 0, urb, cnt++);
		/* maybe kickstart control list */
		wmb ();
		ohci_ग_लिखोl (ohci, OHCI_CLF, &ohci->regs->cmdstatus);
		अवरोध;

	/* ISO has no retransmit, so no toggle; and it uses special TDs.
	 * Each TD could handle multiple consecutive frames (पूर्णांकerval 1);
	 * we could often reduce the number of TDs here.
	 */
	हाल PIPE_ISOCHRONOUS:
		क्रम (cnt = urb_priv->td_cnt; cnt < urb->number_of_packets;
				cnt++) अणु
			पूर्णांक	frame = urb->start_frame;

			// FIXME scheduling should handle frame counter
			// roll-around ... exotic हाल (and OHCI has
			// a 2^16 iso range, vs other HCs max of 2^10)
			frame += cnt * urb->पूर्णांकerval;
			frame &= 0xffff;
			td_fill (ohci, TD_CC | TD_ISO | frame,
				data + urb->iso_frame_desc [cnt].offset,
				urb->iso_frame_desc [cnt].length, urb, cnt);
		पूर्ण
		अगर (ohci_to_hcd(ohci)->self.bandwidth_isoc_reqs == 0) अणु
			अगर (quirk_amdiso(ohci))
				usb_amd_quirk_pll_disable();
			अगर (quirk_amdprefetch(ohci))
				sb800_prefetch(dev, 1);
		पूर्ण
		periodic = ohci_to_hcd(ohci)->self.bandwidth_isoc_reqs++ == 0
			&& ohci_to_hcd(ohci)->self.bandwidth_पूर्णांक_reqs == 0;
		अवरोध;
	पूर्ण

	/* start periodic dma अगर needed */
	अगर (periodic) अणु
		wmb ();
		ohci->hc_control |= OHCI_CTRL_PLE|OHCI_CTRL_IE;
		ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
	पूर्ण

	// ASSERT (urb_priv->length == cnt);
पूर्ण

/*-------------------------------------------------------------------------*
 * Done List handling functions
 *-------------------------------------------------------------------------*/

/* calculate transfer length/status and update the urb */
अटल पूर्णांक td_करोne(काष्ठा ohci_hcd *ohci, काष्ठा urb *urb, काष्ठा td *td)
अणु
	u32	tdINFO = hc32_to_cpup (ohci, &td->hwINFO);
	पूर्णांक	cc = 0;
	पूर्णांक	status = -EINPROGRESS;

	list_del (&td->td_list);

	/* ISO ... drivers see per-TD length/status */
	अगर (tdINFO & TD_ISO) अणु
		u16	tdPSW = ohci_hwPSW(ohci, td, 0);
		पूर्णांक	dlen = 0;

		/* NOTE:  assumes FC in tdINFO == 0, and that
		 * only the first of 0..MAXPSW psws is used.
		 */

		cc = (tdPSW >> 12) & 0xF;
		अगर (tdINFO & TD_CC)	/* hc didn't touch? */
			वापस status;

		अगर (usb_pipeout (urb->pipe))
			dlen = urb->iso_frame_desc [td->index].length;
		अन्यथा अणु
			/* लघु पढ़ोs are always OK क्रम ISO */
			अगर (cc == TD_DATAUNDERRUN)
				cc = TD_CC_NOERROR;
			dlen = tdPSW & 0x3ff;
		पूर्ण
		urb->actual_length += dlen;
		urb->iso_frame_desc [td->index].actual_length = dlen;
		urb->iso_frame_desc [td->index].status = cc_to_error [cc];

		अगर (cc != TD_CC_NOERROR)
			ohci_dbg(ohci,
				"urb %p iso td %p (%d) len %d cc %d\n",
				urb, td, 1 + td->index, dlen, cc);

	/* BULK, INT, CONTROL ... drivers see aggregate length/status,
	 * except that "setup" bytes aren't counted and "short" transfers
	 * might not be reported as errors.
	 */
	पूर्ण अन्यथा अणु
		पूर्णांक	type = usb_pipetype (urb->pipe);
		u32	tdBE = hc32_to_cpup (ohci, &td->hwBE);

		cc = TD_CC_GET (tdINFO);

		/* update packet status अगर needed (लघु is normally ok) */
		अगर (cc == TD_DATAUNDERRUN
				&& !(urb->transfer_flags & URB_SHORT_NOT_OK))
			cc = TD_CC_NOERROR;
		अगर (cc != TD_CC_NOERROR && cc < 0x0E)
			status = cc_to_error[cc];

		/* count all non-empty packets except control SETUP packet */
		अगर ((type != PIPE_CONTROL || td->index != 0) && tdBE != 0) अणु
			अगर (td->hwCBP == 0)
				urb->actual_length += tdBE - td->data_dma + 1;
			अन्यथा
				urb->actual_length +=
					  hc32_to_cpup (ohci, &td->hwCBP)
					- td->data_dma;
		पूर्ण

		अगर (cc != TD_CC_NOERROR && cc < 0x0E)
			ohci_dbg(ohci,
				"urb %p td %p (%d) cc %d, len=%d/%d\n",
				urb, td, 1 + td->index, cc,
				urb->actual_length,
				urb->transfer_buffer_length);
	पूर्ण
	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम ed_halted(काष्ठा ohci_hcd *ohci, काष्ठा td *td, पूर्णांक cc)
अणु
	काष्ठा urb		*urb = td->urb;
	urb_priv_t		*urb_priv = urb->hcpriv;
	काष्ठा ed		*ed = td->ed;
	काष्ठा list_head	*पंचांगp = td->td_list.next;
	__hc32			toggle = ed->hwHeadP & cpu_to_hc32 (ohci, ED_C);

	/* clear ed halt; this is the td that caused it, but keep it inactive
	 * until its urb->complete() has a chance to clean up.
	 */
	ed->hwINFO |= cpu_to_hc32 (ohci, ED_SKIP);
	wmb ();
	ed->hwHeadP &= ~cpu_to_hc32 (ohci, ED_H);

	/* Get rid of all later tds from this urb.  We करोn't have
	 * to be careful: no errors and nothing was transferred.
	 * Also patch the ed so it looks as अगर those tds completed normally.
	 */
	जबतक (पंचांगp != &ed->td_list) अणु
		काष्ठा td	*next;

		next = list_entry (पंचांगp, काष्ठा td, td_list);
		पंचांगp = next->td_list.next;

		अगर (next->urb != urb)
			अवरोध;

		/* NOTE: अगर multi-td control DATA segments get supported,
		 * this urb had one of them, this td wasn't the last td
		 * in that segment (TD_R clear), this ed halted because
		 * of a लघु पढ़ो, _and_ URB_SHORT_NOT_OK is clear ...
		 * then we need to leave the control STATUS packet queued
		 * and clear ED_SKIP.
		 */

		list_del(&next->td_list);
		urb_priv->td_cnt++;
		ed->hwHeadP = next->hwNextTD | toggle;
	पूर्ण

	/* help क्रम troubleshooting:  report anything that
	 * looks odd ... that करोesn't include protocol stalls
	 * (or maybe some other things)
	 */
	चयन (cc) अणु
	हाल TD_DATAUNDERRUN:
		अगर ((urb->transfer_flags & URB_SHORT_NOT_OK) == 0)
			अवरोध;
		fallthrough;
	हाल TD_CC_STALL:
		अगर (usb_pipecontrol (urb->pipe))
			अवरोध;
		fallthrough;
	शेष:
		ohci_dbg (ohci,
			"urb %p path %s ep%d%s %08x cc %d --> status %d\n",
			urb, urb->dev->devpath,
			usb_pipeendpoपूर्णांक (urb->pipe),
			usb_pipein (urb->pipe) ? "in" : "out",
			hc32_to_cpu (ohci, td->hwINFO),
			cc, cc_to_error [cc]);
	पूर्ण
पूर्ण

/* Add a TD to the करोne list */
अटल व्योम add_to_करोne_list(काष्ठा ohci_hcd *ohci, काष्ठा td *td)
अणु
	काष्ठा td	*td2, *td_prev;
	काष्ठा ed	*ed;

	अगर (td->next_dl_td)
		वापस;		/* Alपढ़ोy on the list */

	/* Add all the TDs going back until we reach one that's on the list */
	ed = td->ed;
	td2 = td_prev = td;
	list_क्रम_each_entry_जारी_reverse(td2, &ed->td_list, td_list) अणु
		अगर (td2->next_dl_td)
			अवरोध;
		td2->next_dl_td = td_prev;
		td_prev = td2;
	पूर्ण

	अगर (ohci->dl_end)
		ohci->dl_end->next_dl_td = td_prev;
	अन्यथा
		ohci->dl_start = td_prev;

	/*
	 * Make td->next_dl_td poपूर्णांक to td itself, to mark the fact
	 * that td is on the करोne list.
	 */
	ohci->dl_end = td->next_dl_td = td;

	/* Did we just add the latest pending TD? */
	td2 = ed->pending_td;
	अगर (td2 && td2->next_dl_td)
		ed->pending_td = शून्य;
पूर्ण

/* Get the entries on the hardware करोne queue and put them on our list */
अटल व्योम update_करोne_list(काष्ठा ohci_hcd *ohci)
अणु
	u32		td_dma;
	काष्ठा td	*td = शून्य;

	td_dma = hc32_to_cpup (ohci, &ohci->hcca->करोne_head);
	ohci->hcca->करोne_head = 0;
	wmb();

	/* get TD from hc's singly linked list, and
	 * add to ours.  ed->td_list changes later.
	 */
	जबतक (td_dma) अणु
		पूर्णांक		cc;

		td = dma_to_td (ohci, td_dma);
		अगर (!td) अणु
			ohci_err (ohci, "bad entry %8x\n", td_dma);
			अवरोध;
		पूर्ण

		td->hwINFO |= cpu_to_hc32 (ohci, TD_DONE);
		cc = TD_CC_GET (hc32_to_cpup (ohci, &td->hwINFO));

		/* Non-iso endpoपूर्णांकs can halt on error; un-halt,
		 * and dequeue any other TDs from this urb.
		 * No other TD could have caused the halt.
		 */
		अगर (cc != TD_CC_NOERROR
				&& (td->ed->hwHeadP & cpu_to_hc32 (ohci, ED_H)))
			ed_halted(ohci, td, cc);

		td_dma = hc32_to_cpup (ohci, &td->hwNextTD);
		add_to_करोne_list(ohci, td);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

/* there are some urbs/eds to unlink; called in_irq(), with HCD locked */
अटल व्योम finish_unlinks(काष्ठा ohci_hcd *ohci)
अणु
	अचिन्हित	tick = ohci_frame_no(ohci);
	काष्ठा ed	*ed, **last;

rescan_all:
	क्रम (last = &ohci->ed_rm_list, ed = *last; ed != शून्य; ed = *last) अणु
		काष्ठा list_head	*entry, *पंचांगp;
		पूर्णांक			completed, modअगरied;
		__hc32			*prev;

		/* only take off EDs that the HC isn't using, accounting क्रम
		 * frame counter wraps and EDs with partially retired TDs
		 */
		अगर (likely(ohci->rh_state == OHCI_RH_RUNNING) &&
				tick_beक्रमe(tick, ed->tick)) अणु
skip_ed:
			last = &ed->ed_next;
			जारी;
		पूर्ण
		अगर (!list_empty(&ed->td_list)) अणु
			काष्ठा td	*td;
			u32		head;

			td = list_first_entry(&ed->td_list, काष्ठा td, td_list);

			/* INTR_WDH may need to clean up first */
			head = hc32_to_cpu(ohci, ed->hwHeadP) & TD_MASK;
			अगर (td->td_dma != head &&
					ohci->rh_state == OHCI_RH_RUNNING)
				जाओ skip_ed;

			/* Don't mess up anything alपढ़ोy on the करोne list */
			अगर (td->next_dl_td)
				जाओ skip_ed;
		पूर्ण

		/* ED's now officially unlinked, hc doesn't see */
		ed->hwHeadP &= ~cpu_to_hc32(ohci, ED_H);
		ed->hwNextED = 0;
		wmb();
		ed->hwINFO &= ~cpu_to_hc32(ohci, ED_SKIP | ED_DEQUEUE);

		/* reentrancy:  अगर we drop the schedule lock, someone might
		 * have modअगरied this list.  normally it's just prepending
		 * entries (which we'd ignore), but paranoia won't hurt.
		 */
		*last = ed->ed_next;
		ed->ed_next = शून्य;
		modअगरied = 0;

		/* unlink urbs as requested, but rescan the list after
		 * we call a completion since it might have unlinked
		 * another (earlier) urb
		 *
		 * When we get here, the HC करोesn't see this ed.  But it
		 * must not be rescheduled until all completed URBs have
		 * been given back to the driver.
		 */
rescan_this:
		completed = 0;
		prev = &ed->hwHeadP;
		list_क्रम_each_safe (entry, पंचांगp, &ed->td_list) अणु
			काष्ठा td	*td;
			काष्ठा urb	*urb;
			urb_priv_t	*urb_priv;
			__hc32		savebits;
			u32		tdINFO;

			td = list_entry (entry, काष्ठा td, td_list);
			urb = td->urb;
			urb_priv = td->urb->hcpriv;

			अगर (!urb->unlinked) अणु
				prev = &td->hwNextTD;
				जारी;
			पूर्ण

			/* patch poपूर्णांकer hc uses */
			savebits = *prev & ~cpu_to_hc32 (ohci, TD_MASK);
			*prev = td->hwNextTD | savebits;

			/* If this was unlinked, the TD may not have been
			 * retired ... so manually save the data toggle.
			 * The controller ignores the value we save क्रम
			 * control and ISO endpoपूर्णांकs.
			 */
			tdINFO = hc32_to_cpup(ohci, &td->hwINFO);
			अगर ((tdINFO & TD_T) == TD_T_DATA0)
				ed->hwHeadP &= ~cpu_to_hc32(ohci, ED_C);
			अन्यथा अगर ((tdINFO & TD_T) == TD_T_DATA1)
				ed->hwHeadP |= cpu_to_hc32(ohci, ED_C);

			/* HC may have partly processed this TD */
			td_करोne (ohci, urb, td);
			urb_priv->td_cnt++;

			/* अगर URB is करोne, clean up */
			अगर (urb_priv->td_cnt >= urb_priv->length) अणु
				modअगरied = completed = 1;
				finish_urb(ohci, urb, 0);
			पूर्ण
		पूर्ण
		अगर (completed && !list_empty (&ed->td_list))
			जाओ rescan_this;

		/*
		 * If no TDs are queued, ED is now idle.
		 * Otherwise, अगर the HC is running, reschedule.
		 * If the HC isn't running, add ED back to the
		 * start of the list क्रम later processing.
		 */
		अगर (list_empty(&ed->td_list)) अणु
			ed->state = ED_IDLE;
			list_del(&ed->in_use_list);
		पूर्ण अन्यथा अगर (ohci->rh_state == OHCI_RH_RUNNING) अणु
			ed_schedule(ohci, ed);
		पूर्ण अन्यथा अणु
			ed->ed_next = ohci->ed_rm_list;
			ohci->ed_rm_list = ed;
			/* Don't loop on the same ED */
			अगर (last == &ohci->ed_rm_list)
				last = &ed->ed_next;
		पूर्ण

		अगर (modअगरied)
			जाओ rescan_all;
	पूर्ण

	/* maybe reenable control and bulk lists */
	अगर (ohci->rh_state == OHCI_RH_RUNNING && !ohci->ed_rm_list) अणु
		u32	command = 0, control = 0;

		अगर (ohci->ed_controltail) अणु
			command |= OHCI_CLF;
			अगर (quirk_zfmicro(ohci))
				mdelay(1);
			अगर (!(ohci->hc_control & OHCI_CTRL_CLE)) अणु
				control |= OHCI_CTRL_CLE;
				ohci_ग_लिखोl (ohci, 0,
					&ohci->regs->ed_controlcurrent);
			पूर्ण
		पूर्ण
		अगर (ohci->ed_bulktail) अणु
			command |= OHCI_BLF;
			अगर (quirk_zfmicro(ohci))
				mdelay(1);
			अगर (!(ohci->hc_control & OHCI_CTRL_BLE)) अणु
				control |= OHCI_CTRL_BLE;
				ohci_ग_लिखोl (ohci, 0,
					&ohci->regs->ed_bulkcurrent);
			पूर्ण
		पूर्ण

		/* CLE/BLE to enable, CLF/BLF to (maybe) kickstart */
		अगर (control) अणु
			ohci->hc_control |= control;
			अगर (quirk_zfmicro(ohci))
				mdelay(1);
			ohci_ग_लिखोl (ohci, ohci->hc_control,
					&ohci->regs->control);
		पूर्ण
		अगर (command) अणु
			अगर (quirk_zfmicro(ohci))
				mdelay(1);
			ohci_ग_लिखोl (ohci, command, &ohci->regs->cmdstatus);
		पूर्ण
	पूर्ण
पूर्ण



/*-------------------------------------------------------------------------*/

/* Take back a TD from the host controller */
अटल व्योम takeback_td(काष्ठा ohci_hcd *ohci, काष्ठा td *td)
अणु
	काष्ठा urb	*urb = td->urb;
	urb_priv_t	*urb_priv = urb->hcpriv;
	काष्ठा ed	*ed = td->ed;
	पूर्णांक		status;

	/* update URB's length and status from TD */
	status = td_करोne(ohci, urb, td);
	urb_priv->td_cnt++;

	/* If all this urb's TDs are करोne, call complete() */
	अगर (urb_priv->td_cnt >= urb_priv->length)
		finish_urb(ohci, urb, status);

	/* clean schedule:  unlink EDs that are no दीर्घer busy */
	अगर (list_empty(&ed->td_list)) अणु
		अगर (ed->state == ED_OPER)
			start_ed_unlink(ohci, ed);

	/* ... reenabling halted EDs only after fault cleanup */
	पूर्ण अन्यथा अगर ((ed->hwINFO & cpu_to_hc32(ohci, ED_SKIP | ED_DEQUEUE))
			== cpu_to_hc32(ohci, ED_SKIP)) अणु
		td = list_entry(ed->td_list.next, काष्ठा td, td_list);
		अगर (!(td->hwINFO & cpu_to_hc32(ohci, TD_DONE))) अणु
			ed->hwINFO &= ~cpu_to_hc32(ohci, ED_SKIP);
			/* ... hc may need waking-up */
			चयन (ed->type) अणु
			हाल PIPE_CONTROL:
				ohci_ग_लिखोl(ohci, OHCI_CLF,
						&ohci->regs->cmdstatus);
				अवरोध;
			हाल PIPE_BULK:
				ohci_ग_लिखोl(ohci, OHCI_BLF,
						&ohci->regs->cmdstatus);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Process normal completions (error or success) and clean the schedules.
 *
 * This is the मुख्य path क्रम handing urbs back to drivers.  The only other
 * normal path is finish_unlinks(), which unlinks URBs using ed_rm_list,
 * instead of scanning the (re-reversed) करोnelist as this करोes.
 */
अटल व्योम process_करोne_list(काष्ठा ohci_hcd *ohci)
अणु
	काष्ठा td	*td;

	जबतक (ohci->dl_start) अणु
		td = ohci->dl_start;
		अगर (td == ohci->dl_end)
			ohci->dl_start = ohci->dl_end = शून्य;
		अन्यथा
			ohci->dl_start = td->next_dl_td;

		takeback_td(ohci, td);
	पूर्ण
पूर्ण

/*
 * TD takeback and URB giveback must be single-thपढ़ोed.
 * This routine takes care of it all.
 */
अटल व्योम ohci_work(काष्ठा ohci_hcd *ohci)
अणु
	अगर (ohci->working) अणु
		ohci->restart_work = 1;
		वापस;
	पूर्ण
	ohci->working = 1;

 restart:
	process_करोne_list(ohci);
	अगर (ohci->ed_rm_list)
		finish_unlinks(ohci);

	अगर (ohci->restart_work) अणु
		ohci->restart_work = 0;
		जाओ restart;
	पूर्ण
	ohci->working = 0;
पूर्ण
