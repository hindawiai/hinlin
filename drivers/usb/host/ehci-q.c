<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2001-2004 by David Brownell
 */

/* this file is part of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/*
 * EHCI hardware queue manipulation ... the core.  QH/QTD manipulation.
 *
 * Control, bulk, and पूर्णांकerrupt traffic all use "qh" lists.  They list "qtd"
 * entries describing USB transactions, max 16-20kB/entry (with 4kB-aligned
 * buffers needed क्रम the larger number).  We use one QH per endpoपूर्णांक, queue
 * multiple urbs (all three types) per endpoपूर्णांक.  URBs may need several qtds.
 *
 * ISO traffic uses "ISO TD" (itd, and sitd) records, and (aदीर्घ with
 * पूर्णांकerrupts) needs careful scheduling.  Perक्रमmance improvements can be
 * an ongoing challenge.  That's in "ehci-sched.c".
 *
 * USB 1.1 devices are handled (a) by "companion" OHCI or UHCI root hubs,
 * or otherwise through transaction translators (TTs) in USB 2.0 hubs using
 * (b) special fields in qh entries or (c) split iso entries.  TTs will
 * buffer low/full speed data so the host collects it at high speed.
 */

/*-------------------------------------------------------------------------*/

/* PID Codes that are used here, from EHCI specअगरication, Table 3-16. */
#घोषणा PID_CODE_IN    1
#घोषणा PID_CODE_SETUP 2

/* fill a qtd, वापसing how much of the buffer we were able to queue up */

अटल पूर्णांक
qtd_fill(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qtd *qtd, dma_addr_t buf,
		  माप_प्रकार len, पूर्णांक token, पूर्णांक maxpacket)
अणु
	पूर्णांक	i, count;
	u64	addr = buf;

	/* one buffer entry per 4K ... first might be लघु or unaligned */
	qtd->hw_buf[0] = cpu_to_hc32(ehci, (u32)addr);
	qtd->hw_buf_hi[0] = cpu_to_hc32(ehci, (u32)(addr >> 32));
	count = 0x1000 - (buf & 0x0fff);	/* rest of that page */
	अगर (likely (len < count))		/* ... अगरf needed */
		count = len;
	अन्यथा अणु
		buf +=  0x1000;
		buf &= ~0x0fff;

		/* per-qtd limit: from 16K to 20K (best alignment) */
		क्रम (i = 1; count < len && i < 5; i++) अणु
			addr = buf;
			qtd->hw_buf[i] = cpu_to_hc32(ehci, (u32)addr);
			qtd->hw_buf_hi[i] = cpu_to_hc32(ehci,
					(u32)(addr >> 32));
			buf += 0x1000;
			अगर ((count + 0x1000) < len)
				count += 0x1000;
			अन्यथा
				count = len;
		पूर्ण

		/* लघु packets may only terminate transfers */
		अगर (count != len)
			count -= (count % maxpacket);
	पूर्ण
	qtd->hw_token = cpu_to_hc32(ehci, (count << 16) | token);
	qtd->length = count;

	वापस count;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम
qh_update (काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh, काष्ठा ehci_qtd *qtd)
अणु
	काष्ठा ehci_qh_hw *hw = qh->hw;

	/* ग_लिखोs to an active overlay are unsafe */
	WARN_ON(qh->qh_state != QH_STATE_IDLE);

	hw->hw_qtd_next = QTD_NEXT(ehci, qtd->qtd_dma);
	hw->hw_alt_next = EHCI_LIST_END(ehci);

	/* Except क्रम control endpoपूर्णांकs, we make hardware मुख्यtain data
	 * toggle (like OHCI) ... here (re)initialize the toggle in the QH,
	 * and set the pseuकरो-toggle in udev. Only usb_clear_halt() will
	 * ever clear it.
	 */
	अगर (!(hw->hw_info1 & cpu_to_hc32(ehci, QH_TOGGLE_CTL))) अणु
		अचिन्हित	is_out, epnum;

		is_out = qh->is_out;
		epnum = (hc32_to_cpup(ehci, &hw->hw_info1) >> 8) & 0x0f;
		अगर (unlikely(!usb_gettoggle(qh->ps.udev, epnum, is_out))) अणु
			hw->hw_token &= ~cpu_to_hc32(ehci, QTD_TOGGLE);
			usb_settoggle(qh->ps.udev, epnum, is_out, 1);
		पूर्ण
	पूर्ण

	hw->hw_token &= cpu_to_hc32(ehci, QTD_TOGGLE | QTD_STS_PING);
पूर्ण

/* अगर it weren't क्रम a common silicon quirk (writing the dummy पूर्णांकo the qh
 * overlay, so qh->hw_token wrongly becomes inactive/halted), only fault
 * recovery (including urb dequeue) would need software changes to a QH...
 */
अटल व्योम
qh_refresh (काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	काष्ठा ehci_qtd *qtd;

	qtd = list_entry(qh->qtd_list.next, काष्ठा ehci_qtd, qtd_list);

	/*
	 * first qtd may alपढ़ोy be partially processed.
	 * If we come here during unlink, the QH overlay region
	 * might have reference to the just unlinked qtd. The
	 * qtd is updated in qh_completions(). Update the QH
	 * overlay here.
	 */
	अगर (qh->hw->hw_token & ACTIVE_BIT(ehci)) अणु
		qh->hw->hw_qtd_next = qtd->hw_next;
		अगर (qh->should_be_inactive)
			ehci_warn(ehci, "qh %p should be inactive!\n", qh);
	पूर्ण अन्यथा अणु
		qh_update(ehci, qh, qtd);
	पूर्ण
	qh->should_be_inactive = 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम qh_link_async(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh);

अटल व्योम ehci_clear_tt_buffer_complete(काष्ठा usb_hcd *hcd,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);
	काष्ठा ehci_qh		*qh = ep->hcpriv;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&ehci->lock, flags);
	qh->clearing_tt = 0;
	अगर (qh->qh_state == QH_STATE_IDLE && !list_empty(&qh->qtd_list)
			&& ehci->rh_state == EHCI_RH_RUNNING)
		qh_link_async(ehci, qh);
	spin_unlock_irqrestore(&ehci->lock, flags);
पूर्ण

अटल व्योम ehci_clear_tt_buffer(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh,
		काष्ठा urb *urb, u32 token)
अणु

	/* If an async split transaction माला_लो an error or is unlinked,
	 * the TT buffer may be left in an indeterminate state.  We
	 * have to clear the TT buffer.
	 *
	 * Note: this routine is never called क्रम Isochronous transfers.
	 */
	अगर (urb->dev->tt && !usb_pipeपूर्णांक(urb->pipe) && !qh->clearing_tt) अणु
#अगर_घोषित CONFIG_DYNAMIC_DEBUG
		काष्ठा usb_device *tt = urb->dev->tt->hub;
		dev_dbg(&tt->dev,
			"clear tt buffer port %d, a%d ep%d t%08x\n",
			urb->dev->ttport, urb->dev->devnum,
			usb_pipeendpoपूर्णांक(urb->pipe), token);
#पूर्ण_अगर /* CONFIG_DYNAMIC_DEBUG */
		अगर (!ehci_is_TDI(ehci)
				|| urb->dev->tt->hub !=
				   ehci_to_hcd(ehci)->self.root_hub) अणु
			अगर (usb_hub_clear_tt_buffer(urb) == 0)
				qh->clearing_tt = 1;
		पूर्ण अन्यथा अणु

			/* REVISIT ARC-derived cores करोn't clear the root
			 * hub TT buffer in this way...
			 */
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qtd_copy_status (
	काष्ठा ehci_hcd *ehci,
	काष्ठा urb *urb,
	माप_प्रकार length,
	u32 token
)
अणु
	पूर्णांक	status = -EINPROGRESS;

	/* count IN/OUT bytes, not SETUP (even लघु packets) */
	अगर (likely(QTD_PID(token) != PID_CODE_SETUP))
		urb->actual_length += length - QTD_LENGTH (token);

	/* करोn't modअगरy error codes */
	अगर (unlikely(urb->unlinked))
		वापस status;

	/* क्रमce cleanup after लघु पढ़ो; not always an error */
	अगर (unlikely (IS_SHORT_READ (token)))
		status = -EREMOTEIO;

	/* serious "can't proceed" faults reported by the hardware */
	अगर (token & QTD_STS_HALT) अणु
		अगर (token & QTD_STS_BABBLE) अणु
			/* FIXME "must" disable babbling device's port too */
			status = -EOVERFLOW;
		/*
		 * When MMF is active and PID Code is IN, queue is halted.
		 * EHCI Specअगरication, Table 4-13.
		 */
		पूर्ण अन्यथा अगर ((token & QTD_STS_MMF) &&
					(QTD_PID(token) == PID_CODE_IN)) अणु
			status = -EPROTO;
		/* CERR nonzero + halt --> stall */
		पूर्ण अन्यथा अगर (QTD_CERR(token)) अणु
			status = -EPIPE;

		/* In theory, more than one of the following bits can be set
		 * since they are sticky and the transaction is retried.
		 * Which to test first is rather arbitrary.
		 */
		पूर्ण अन्यथा अगर (token & QTD_STS_MMF) अणु
			/* fs/ls पूर्णांकerrupt xfer missed the complete-split */
			status = -EPROTO;
		पूर्ण अन्यथा अगर (token & QTD_STS_DBE) अणु
			status = (QTD_PID (token) == 1) /* IN ? */
				? -ENOSR  /* hc couldn't पढ़ो data */
				: -ECOMM; /* hc couldn't ग_लिखो data */
		पूर्ण अन्यथा अगर (token & QTD_STS_XACT) अणु
			/* समयout, bad CRC, wrong PID, etc */
			ehci_dbg(ehci, "devpath %s ep%d%s 3strikes\n",
				urb->dev->devpath,
				usb_pipeendpoपूर्णांक(urb->pipe),
				usb_pipein(urb->pipe) ? "in" : "out");
			status = -EPROTO;
		पूर्ण अन्यथा अणु	/* unknown */
			status = -EPROTO;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम
ehci_urb_करोne(काष्ठा ehci_hcd *ehci, काष्ठा urb *urb, पूर्णांक status)
अणु
	अगर (usb_pipetype(urb->pipe) == PIPE_INTERRUPT) अणु
		/* ... update hc-wide periodic stats */
		ehci_to_hcd(ehci)->self.bandwidth_पूर्णांक_reqs--;
	पूर्ण

	अगर (unlikely(urb->unlinked)) अणु
		INCR(ehci->stats.unlink);
	पूर्ण अन्यथा अणु
		/* report non-error and लघु पढ़ो status as zero */
		अगर (status == -EINPROGRESS || status == -EREMOTEIO)
			status = 0;
		INCR(ehci->stats.complete);
	पूर्ण

#अगर_घोषित EHCI_URB_TRACE
	ehci_dbg (ehci,
		"%s %s urb %p ep%d%s status %d len %d/%d\n",
		__func__, urb->dev->devpath, urb,
		usb_pipeendpoपूर्णांक (urb->pipe),
		usb_pipein (urb->pipe) ? "in" : "out",
		status,
		urb->actual_length, urb->transfer_buffer_length);
#पूर्ण_अगर

	usb_hcd_unlink_urb_from_ep(ehci_to_hcd(ehci), urb);
	usb_hcd_giveback_urb(ehci_to_hcd(ehci), urb, status);
पूर्ण

अटल पूर्णांक qh_schedule (काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh);

/*
 * Process and मुक्त completed qtds क्रम a qh, वापसing URBs to drivers.
 * Chases up to qh->hw_current.  Returns nonzero अगर the caller should
 * unlink qh.
 */
अटल अचिन्हित
qh_completions (काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	काष्ठा ehci_qtd		*last, *end = qh->dummy;
	काष्ठा list_head	*entry, *पंचांगp;
	पूर्णांक			last_status;
	पूर्णांक			stopped;
	u8			state;
	काष्ठा ehci_qh_hw	*hw = qh->hw;

	/* completions (or tasks on other cpus) must never clobber HALT
	 * till we've gone through and cleaned everything up, even when
	 * they add urbs to this qh's queue or mark them क्रम unlinking.
	 *
	 * NOTE:  unlinking expects to be करोne in queue order.
	 *
	 * It's a bug क्रम qh->qh_state to be anything other than
	 * QH_STATE_IDLE, unless our caller is scan_async() or
	 * scan_पूर्णांकr().
	 */
	state = qh->qh_state;
	qh->qh_state = QH_STATE_COMPLETING;
	stopped = (state == QH_STATE_IDLE);

 rescan:
	last = शून्य;
	last_status = -EINPROGRESS;
	qh->dequeue_during_giveback = 0;

	/* हटाओ de-activated QTDs from front of queue.
	 * after faults (including लघु पढ़ोs), cleanup this urb
	 * then let the queue advance.
	 * अगर queue is stopped, handles unlinks.
	 */
	list_क्रम_each_safe (entry, पंचांगp, &qh->qtd_list) अणु
		काष्ठा ehci_qtd	*qtd;
		काष्ठा urb	*urb;
		u32		token = 0;

		qtd = list_entry (entry, काष्ठा ehci_qtd, qtd_list);
		urb = qtd->urb;

		/* clean up any state from previous QTD ...*/
		अगर (last) अणु
			अगर (likely (last->urb != urb)) अणु
				ehci_urb_करोne(ehci, last->urb, last_status);
				last_status = -EINPROGRESS;
			पूर्ण
			ehci_qtd_मुक्त (ehci, last);
			last = शून्य;
		पूर्ण

		/* ignore urbs submitted during completions we reported */
		अगर (qtd == end)
			अवरोध;

		/* hardware copies qtd out of qh overlay */
		rmb ();
		token = hc32_to_cpu(ehci, qtd->hw_token);

		/* always clean up qtds the hc de-activated */
 retry_xacterr:
		अगर ((token & QTD_STS_ACTIVE) == 0) अणु

			/* Report Data Buffer Error: non-fatal but useful */
			अगर (token & QTD_STS_DBE)
				ehci_dbg(ehci,
					"detected DataBufferErr for urb %p ep%d%s len %d, qtd %p [qh %p]\n",
					urb,
					usb_endpoपूर्णांक_num(&urb->ep->desc),
					usb_endpoपूर्णांक_dir_in(&urb->ep->desc) ? "in" : "out",
					urb->transfer_buffer_length,
					qtd,
					qh);

			/* on STALL, error, and लघु पढ़ोs this urb must
			 * complete and all its qtds must be recycled.
			 */
			अगर ((token & QTD_STS_HALT) != 0) अणु

				/* retry transaction errors until we
				 * reach the software xacterr limit
				 */
				अगर ((token & QTD_STS_XACT) &&
						QTD_CERR(token) == 0 &&
						++qh->xacterrs < QH_XACTERR_MAX &&
						!urb->unlinked) अणु
					ehci_dbg(ehci,
	"detected XactErr len %zu/%zu retry %d\n",
	qtd->length - QTD_LENGTH(token), qtd->length, qh->xacterrs);

					/* reset the token in the qtd and the
					 * qh overlay (which still contains
					 * the qtd) so that we pick up from
					 * where we left off
					 */
					token &= ~QTD_STS_HALT;
					token |= QTD_STS_ACTIVE |
							(EHCI_TUNE_CERR << 10);
					qtd->hw_token = cpu_to_hc32(ehci,
							token);
					wmb();
					hw->hw_token = cpu_to_hc32(ehci,
							token);
					जाओ retry_xacterr;
				पूर्ण
				stopped = 1;
				qh->unlink_reason |= QH_UNLINK_HALTED;

			/* magic dummy क्रम some लघु पढ़ोs; qh won't advance.
			 * that silicon quirk can kick in with this dummy too.
			 *
			 * other लघु पढ़ोs won't stop the queue, including
			 * control transfers (status stage handles that) or
			 * most other single-qtd पढ़ोs ... the queue stops अगर
			 * URB_SHORT_NOT_OK was set so the driver submitting
			 * the urbs could clean it up.
			 */
			पूर्ण अन्यथा अगर (IS_SHORT_READ (token)
					&& !(qtd->hw_alt_next
						& EHCI_LIST_END(ehci))) अणु
				stopped = 1;
				qh->unlink_reason |= QH_UNLINK_SHORT_READ;
			पूर्ण

		/* stop scanning when we reach qtds the hc is using */
		पूर्ण अन्यथा अगर (likely (!stopped
				&& ehci->rh_state >= EHCI_RH_RUNNING)) अणु
			अवरोध;

		/* scan the whole queue क्रम unlinks whenever it stops */
		पूर्ण अन्यथा अणु
			stopped = 1;

			/* cancel everything अगर we halt, suspend, etc */
			अगर (ehci->rh_state < EHCI_RH_RUNNING) अणु
				last_status = -ESHUTDOWN;
				qh->unlink_reason |= QH_UNLINK_SHUTDOWN;
			पूर्ण

			/* this qtd is active; skip it unless a previous qtd
			 * क्रम its urb faulted, or its urb was canceled.
			 */
			अन्यथा अगर (last_status == -EINPROGRESS && !urb->unlinked)
				जारी;

			/*
			 * If this was the active qtd when the qh was unlinked
			 * and the overlay's token is active, then the overlay
			 * hasn't been written back to the qtd yet so use its
			 * token instead of the qtd's.  After the qtd is
			 * processed and हटाओd, the overlay won't be valid
			 * any more.
			 */
			अगर (state == QH_STATE_IDLE &&
					qh->qtd_list.next == &qtd->qtd_list &&
					(hw->hw_token & ACTIVE_BIT(ehci))) अणु
				token = hc32_to_cpu(ehci, hw->hw_token);
				hw->hw_token &= ~ACTIVE_BIT(ehci);
				qh->should_be_inactive = 1;

				/* An unlink may leave an incomplete
				 * async transaction in the TT buffer.
				 * We have to clear it.
				 */
				ehci_clear_tt_buffer(ehci, qh, urb, token);
			पूर्ण
		पूर्ण

		/* unless we alपढ़ोy know the urb's status, collect qtd status
		 * and update count of bytes transferred.  in common लघु पढ़ो
		 * हालs with only one data qtd (including control transfers),
		 * queue processing won't halt.  but with two or more qtds (क्रम
		 * example, with a 32 KB transfer), when the first qtd माला_लो a
		 * लघु पढ़ो the second must be हटाओd by hand.
		 */
		अगर (last_status == -EINPROGRESS) अणु
			last_status = qtd_copy_status(ehci, urb,
					qtd->length, token);
			अगर (last_status == -EREMOTEIO
					&& (qtd->hw_alt_next
						& EHCI_LIST_END(ehci)))
				last_status = -EINPROGRESS;

			/* As part of low/full-speed endpoपूर्णांक-halt processing
			 * we must clear the TT buffer (11.17.5).
			 */
			अगर (unlikely(last_status != -EINPROGRESS &&
					last_status != -EREMOTEIO)) अणु
				/* The TT's in some hubs malfunction when they
				 * receive this request following a STALL (they
				 * stop sending isochronous packets).  Since a
				 * STALL can't leave the TT buffer in a busy
				 * state (अगर you believe Figures 11-48 - 11-51
				 * in the USB 2.0 spec), we won't clear the TT
				 * buffer in this हाल.  Strictly speaking this
				 * is a violation of the spec.
				 */
				अगर (last_status != -EPIPE)
					ehci_clear_tt_buffer(ehci, qh, urb,
							token);
			पूर्ण
		पूर्ण

		/* अगर we're removing something not at the queue head,
		 * patch the hardware queue poपूर्णांकer.
		 */
		अगर (stopped && qtd->qtd_list.prev != &qh->qtd_list) अणु
			last = list_entry (qtd->qtd_list.prev,
					काष्ठा ehci_qtd, qtd_list);
			last->hw_next = qtd->hw_next;
		पूर्ण

		/* हटाओ qtd; it's recycled after possible urb completion */
		list_del (&qtd->qtd_list);
		last = qtd;

		/* reinit the xacterr counter क्रम the next qtd */
		qh->xacterrs = 0;
	पूर्ण

	/* last urb's completion might still need calling */
	अगर (likely (last != शून्य)) अणु
		ehci_urb_करोne(ehci, last->urb, last_status);
		ehci_qtd_मुक्त (ehci, last);
	पूर्ण

	/* Do we need to rescan क्रम URBs dequeued during a giveback? */
	अगर (unlikely(qh->dequeue_during_giveback)) अणु
		/* If the QH is alपढ़ोy unlinked, करो the rescan now. */
		अगर (state == QH_STATE_IDLE)
			जाओ rescan;

		/* Otherwise the caller must unlink the QH. */
	पूर्ण

	/* restore original state; caller must unlink or relink */
	qh->qh_state = state;

	/* be sure the hardware's करोne with the qh beक्रमe refreshing
	 * it after fault cleanup, or recovering from silicon wrongly
	 * overlaying the dummy qtd (which reduces DMA chatter).
	 *
	 * We won't refresh a QH that's linked (after the HC
	 * stopped the queue).  That aव्योमs a race:
	 *  - HC पढ़ोs first part of QH;
	 *  - CPU updates that first part and the token;
	 *  - HC पढ़ोs rest of that QH, including token
	 * Result:  HC माला_लो an inconsistent image, and then
	 * DMAs to/from the wrong memory (corrupting it).
	 *
	 * That should be rare क्रम पूर्णांकerrupt transfers,
	 * except maybe high bandwidth ...
	 */
	अगर (stopped != 0 || hw->hw_qtd_next == EHCI_LIST_END(ehci))
		qh->unlink_reason |= QH_UNLINK_DUMMY_OVERLAY;

	/* Let the caller know अगर the QH needs to be unlinked. */
	वापस qh->unlink_reason;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * reverse of qh_urb_transaction:  मुक्त a list of TDs.
 * used क्रम cleanup after errors, beक्रमe HC sees an URB's TDs.
 */
अटल व्योम qtd_list_मुक्त (
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	काष्ठा list_head	*qtd_list
) अणु
	काष्ठा list_head	*entry, *temp;

	list_क्रम_each_safe (entry, temp, qtd_list) अणु
		काष्ठा ehci_qtd	*qtd;

		qtd = list_entry (entry, काष्ठा ehci_qtd, qtd_list);
		list_del (&qtd->qtd_list);
		ehci_qtd_मुक्त (ehci, qtd);
	पूर्ण
पूर्ण

/*
 * create a list of filled qtds क्रम this URB; won't link पूर्णांकo qh.
 */
अटल काष्ठा list_head *
qh_urb_transaction (
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	काष्ठा list_head	*head,
	gfp_t			flags
) अणु
	काष्ठा ehci_qtd		*qtd, *qtd_prev;
	dma_addr_t		buf;
	पूर्णांक			len, this_sg_len, maxpacket;
	पूर्णांक			is_input;
	u32			token;
	पूर्णांक			i;
	काष्ठा scatterlist	*sg;

	/*
	 * URBs map to sequences of QTDs:  one logical transaction
	 */
	qtd = ehci_qtd_alloc (ehci, flags);
	अगर (unlikely (!qtd))
		वापस शून्य;
	list_add_tail (&qtd->qtd_list, head);
	qtd->urb = urb;

	token = QTD_STS_ACTIVE;
	token |= (EHCI_TUNE_CERR << 10);
	/* क्रम split transactions, SplitXState initialized to zero */

	len = urb->transfer_buffer_length;
	is_input = usb_pipein (urb->pipe);
	अगर (usb_pipecontrol (urb->pipe)) अणु
		/* SETUP pid */
		qtd_fill(ehci, qtd, urb->setup_dma,
				माप (काष्ठा usb_ctrlrequest),
				token | (2 /* "setup" */ << 8), 8);

		/* ... and always at least one more pid */
		token ^= QTD_TOGGLE;
		qtd_prev = qtd;
		qtd = ehci_qtd_alloc (ehci, flags);
		अगर (unlikely (!qtd))
			जाओ cleanup;
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
		list_add_tail (&qtd->qtd_list, head);

		/* क्रम zero length DATA stages, STATUS is always IN */
		अगर (len == 0)
			token |= (1 /* "in" */ << 8);
	पूर्ण

	/*
	 * data transfer stage:  buffer setup
	 */
	i = urb->num_mapped_sgs;
	अगर (len > 0 && i > 0) अणु
		sg = urb->sg;
		buf = sg_dma_address(sg);

		/* urb->transfer_buffer_length may be smaller than the
		 * size of the scatterlist (or vice versa)
		 */
		this_sg_len = min_t(पूर्णांक, sg_dma_len(sg), len);
	पूर्ण अन्यथा अणु
		sg = शून्य;
		buf = urb->transfer_dma;
		this_sg_len = len;
	पूर्ण

	अगर (is_input)
		token |= (1 /* "in" */ << 8);
	/* अन्यथा it's alपढ़ोy initted to "out" pid (0 << 8) */

	maxpacket = usb_maxpacket(urb->dev, urb->pipe, !is_input);

	/*
	 * buffer माला_लो wrapped in one or more qtds;
	 * last one may be "short" (including zero len)
	 * and may serve as a control status ack
	 */
	क्रम (;;) अणु
		पूर्णांक this_qtd_len;

		this_qtd_len = qtd_fill(ehci, qtd, buf, this_sg_len, token,
				maxpacket);
		this_sg_len -= this_qtd_len;
		len -= this_qtd_len;
		buf += this_qtd_len;

		/*
		 * लघु पढ़ोs advance to a "magic" dummy instead of the next
		 * qtd ... that क्रमces the queue to stop, क्रम manual cleanup.
		 * (this will usually be overridden later.)
		 */
		अगर (is_input)
			qtd->hw_alt_next = ehci->async->hw->hw_alt_next;

		/* qh makes control packets use qtd toggle; maybe चयन it */
		अगर ((maxpacket & (this_qtd_len + (maxpacket - 1))) == 0)
			token ^= QTD_TOGGLE;

		अगर (likely(this_sg_len <= 0)) अणु
			अगर (--i <= 0 || len <= 0)
				अवरोध;
			sg = sg_next(sg);
			buf = sg_dma_address(sg);
			this_sg_len = min_t(पूर्णांक, sg_dma_len(sg), len);
		पूर्ण

		qtd_prev = qtd;
		qtd = ehci_qtd_alloc (ehci, flags);
		अगर (unlikely (!qtd))
			जाओ cleanup;
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
		list_add_tail (&qtd->qtd_list, head);
	पूर्ण

	/*
	 * unless the caller requires manual cleanup after लघु पढ़ोs,
	 * have the alt_next mechanism keep the queue running after the
	 * last data qtd (the only one, क्रम control and most other हालs).
	 */
	अगर (likely ((urb->transfer_flags & URB_SHORT_NOT_OK) == 0
				|| usb_pipecontrol (urb->pipe)))
		qtd->hw_alt_next = EHCI_LIST_END(ehci);

	/*
	 * control requests may need a terminating data "status" ack;
	 * other OUT ones may need a terminating लघु packet
	 * (zero length).
	 */
	अगर (likely (urb->transfer_buffer_length != 0)) अणु
		पूर्णांक	one_more = 0;

		अगर (usb_pipecontrol (urb->pipe)) अणु
			one_more = 1;
			token ^= 0x0100;	/* "in" <--> "out"  */
			token |= QTD_TOGGLE;	/* क्रमce DATA1 */
		पूर्ण अन्यथा अगर (usb_pipeout(urb->pipe)
				&& (urb->transfer_flags & URB_ZERO_PACKET)
				&& !(urb->transfer_buffer_length % maxpacket)) अणु
			one_more = 1;
		पूर्ण
		अगर (one_more) अणु
			qtd_prev = qtd;
			qtd = ehci_qtd_alloc (ehci, flags);
			अगर (unlikely (!qtd))
				जाओ cleanup;
			qtd->urb = urb;
			qtd_prev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
			list_add_tail (&qtd->qtd_list, head);

			/* never any data in such packets */
			qtd_fill(ehci, qtd, 0, 0, token, 0);
		पूर्ण
	पूर्ण

	/* by शेष, enable पूर्णांकerrupt on urb completion */
	अगर (likely (!(urb->transfer_flags & URB_NO_INTERRUPT)))
		qtd->hw_token |= cpu_to_hc32(ehci, QTD_IOC);
	वापस head;

cleanup:
	qtd_list_मुक्त (ehci, urb, head);
	वापस शून्य;
पूर्ण

/*-------------------------------------------------------------------------*/

// Would be best to create all qh's from config descriptors,
// when each पूर्णांकerface/altsetting is established.  Unlink
// any previous qh and cancel its urbs first; endpoपूर्णांकs are
// implicitly reset then (data toggle too).
// That'd mean updating how usbcore talks to HCDs. (2.7?)


/*
 * Each QH holds a qtd list; a QH is used क्रम everything except iso.
 *
 * For पूर्णांकerrupt urbs, the scheduler must set the microframe scheduling
 * mask(s) each समय the QH माला_लो scheduled.  For highspeed, that's
 * just one microframe in the s-mask.  For split पूर्णांकerrupt transactions
 * there are additional complications: c-mask, maybe FSTNs.
 */
अटल काष्ठा ehci_qh *
qh_make (
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	gfp_t			flags
) अणु
	काष्ठा ehci_qh		*qh = ehci_qh_alloc (ehci, flags);
	काष्ठा usb_host_endpoपूर्णांक *ep;
	u32			info1 = 0, info2 = 0;
	पूर्णांक			is_input, type;
	पूर्णांक			maxp = 0;
	पूर्णांक			mult;
	काष्ठा usb_tt		*tt = urb->dev->tt;
	काष्ठा ehci_qh_hw	*hw;

	अगर (!qh)
		वापस qh;

	/*
	 * init endpoपूर्णांक/device data क्रम this QH
	 */
	info1 |= usb_pipeendpoपूर्णांक (urb->pipe) << 8;
	info1 |= usb_pipedevice (urb->pipe) << 0;

	is_input = usb_pipein (urb->pipe);
	type = usb_pipetype (urb->pipe);
	ep = usb_pipe_endpoपूर्णांक (urb->dev, urb->pipe);
	maxp = usb_endpoपूर्णांक_maxp (&ep->desc);
	mult = usb_endpoपूर्णांक_maxp_mult (&ep->desc);

	/* 1024 byte maxpacket is a hardware उच्चमानing.  High bandwidth
	 * acts like up to 3KB, but is built from smaller packets.
	 */
	अगर (maxp > 1024) अणु
		ehci_dbg(ehci, "bogus qh maxpacket %d\n", maxp);
		जाओ करोne;
	पूर्ण

	/* Compute पूर्णांकerrupt scheduling parameters just once, and save.
	 * - allowing क्रम high bandwidth, how many nsec/uframe are used?
	 * - split transactions need a second CSPLIT uframe; same question
	 * - splits also need a schedule gap (क्रम full/low speed I/O)
	 * - qh has a polling पूर्णांकerval
	 *
	 * For control/bulk requests, the HC or TT handles these.
	 */
	अगर (type == PIPE_INTERRUPT) अणु
		अचिन्हित	पंचांगp;

		qh->ps.usecs = NS_TO_US(usb_calc_bus_समय(USB_SPEED_HIGH,
				is_input, 0, mult * maxp));
		qh->ps.phase = NO_FRAME;

		अगर (urb->dev->speed == USB_SPEED_HIGH) अणु
			qh->ps.c_usecs = 0;
			qh->gap_uf = 0;

			अगर (urb->पूर्णांकerval > 1 && urb->पूर्णांकerval < 8) अणु
				/* NOTE पूर्णांकerval 2 or 4 uframes could work.
				 * But पूर्णांकerval 1 scheduling is simpler, and
				 * includes high bandwidth.
				 */
				urb->पूर्णांकerval = 1;
			पूर्ण अन्यथा अगर (urb->पूर्णांकerval > ehci->periodic_size << 3) अणु
				urb->पूर्णांकerval = ehci->periodic_size << 3;
			पूर्ण
			qh->ps.period = urb->पूर्णांकerval >> 3;

			/* period क्रम bandwidth allocation */
			पंचांगp = min_t(अचिन्हित, EHCI_BANDWIDTH_SIZE,
					1 << (urb->ep->desc.bInterval - 1));

			/* Allow urb->पूर्णांकerval to override */
			qh->ps.bw_uperiod = min_t(अचिन्हित, पंचांगp, urb->पूर्णांकerval);
			qh->ps.bw_period = qh->ps.bw_uperiod >> 3;
		पूर्ण अन्यथा अणु
			पूर्णांक		think_समय;

			/* gap is f(FS/LS transfer बार) */
			qh->gap_uf = 1 + usb_calc_bus_समय (urb->dev->speed,
					is_input, 0, maxp) / (125 * 1000);

			/* FIXME this just approximates SPLIT/CSPLIT बार */
			अगर (is_input) अणु		// SPLIT, gap, CSPLIT+DATA
				qh->ps.c_usecs = qh->ps.usecs + HS_USECS(0);
				qh->ps.usecs = HS_USECS(1);
			पूर्ण अन्यथा अणु		// SPLIT+DATA, gap, CSPLIT
				qh->ps.usecs += HS_USECS(1);
				qh->ps.c_usecs = HS_USECS(0);
			पूर्ण

			think_समय = tt ? tt->think_समय : 0;
			qh->ps.tt_usecs = NS_TO_US(think_समय +
					usb_calc_bus_समय (urb->dev->speed,
					is_input, 0, maxp));
			अगर (urb->पूर्णांकerval > ehci->periodic_size)
				urb->पूर्णांकerval = ehci->periodic_size;
			qh->ps.period = urb->पूर्णांकerval;

			/* period क्रम bandwidth allocation */
			पंचांगp = min_t(अचिन्हित, EHCI_BANDWIDTH_FRAMES,
					urb->ep->desc.bInterval);
			पंचांगp = roundकरोwn_घात_of_two(पंचांगp);

			/* Allow urb->पूर्णांकerval to override */
			qh->ps.bw_period = min_t(अचिन्हित, पंचांगp, urb->पूर्णांकerval);
			qh->ps.bw_uperiod = qh->ps.bw_period << 3;
		पूर्ण
	पूर्ण

	/* support क्रम tt scheduling, and access to toggles */
	qh->ps.udev = urb->dev;
	qh->ps.ep = urb->ep;

	/* using TT? */
	चयन (urb->dev->speed) अणु
	हाल USB_SPEED_LOW:
		info1 |= QH_LOW_SPEED;
		fallthrough;

	हाल USB_SPEED_FULL:
		/* EPS 0 means "full" */
		अगर (type != PIPE_INTERRUPT)
			info1 |= (EHCI_TUNE_RL_TT << 28);
		अगर (type == PIPE_CONTROL) अणु
			info1 |= QH_CONTROL_EP;		/* क्रम TT */
			info1 |= QH_TOGGLE_CTL;		/* toggle from qtd */
		पूर्ण
		info1 |= maxp << 16;

		info2 |= (EHCI_TUNE_MULT_TT << 30);

		/* Some Freescale processors have an erratum in which the
		 * port number in the queue head was 0..N-1 instead of 1..N.
		 */
		अगर (ehci_has_fsl_portno_bug(ehci))
			info2 |= (urb->dev->ttport-1) << 23;
		अन्यथा
			info2 |= urb->dev->ttport << 23;

		/* set the address of the TT; क्रम TDI's पूर्णांकegrated
		 * root hub tt, leave it zeroed.
		 */
		अगर (tt && tt->hub != ehci_to_hcd(ehci)->self.root_hub)
			info2 |= tt->hub->devnum << 16;

		/* NOTE:  अगर (PIPE_INTERRUPT) अणु scheduler sets c-mask पूर्ण */

		अवरोध;

	हाल USB_SPEED_HIGH:		/* no TT involved */
		info1 |= QH_HIGH_SPEED;
		अगर (type == PIPE_CONTROL) अणु
			info1 |= (EHCI_TUNE_RL_HS << 28);
			info1 |= 64 << 16;	/* usb2 fixed maxpacket */
			info1 |= QH_TOGGLE_CTL;	/* toggle from qtd */
			info2 |= (EHCI_TUNE_MULT_HS << 30);
		पूर्ण अन्यथा अगर (type == PIPE_BULK) अणु
			info1 |= (EHCI_TUNE_RL_HS << 28);
			/* The USB spec says that high speed bulk endpoपूर्णांकs
			 * always use 512 byte maxpacket.  But some device
			 * venकरोrs decided to ignore that, and MSFT is happy
			 * to help them करो so.  So now people expect to use
			 * such nonconक्रमmant devices with Linux too; sigh.
			 */
			info1 |= maxp << 16;
			info2 |= (EHCI_TUNE_MULT_HS << 30);
		पूर्ण अन्यथा अणु		/* PIPE_INTERRUPT */
			info1 |= maxp << 16;
			info2 |= mult << 30;
		पूर्ण
		अवरोध;
	शेष:
		ehci_dbg(ehci, "bogus dev %p speed %d\n", urb->dev,
			urb->dev->speed);
करोne:
		qh_destroy(ehci, qh);
		वापस शून्य;
	पूर्ण

	/* NOTE:  अगर (PIPE_INTERRUPT) अणु scheduler sets s-mask पूर्ण */

	/* init as live, toggle clear */
	qh->qh_state = QH_STATE_IDLE;
	hw = qh->hw;
	hw->hw_info1 = cpu_to_hc32(ehci, info1);
	hw->hw_info2 = cpu_to_hc32(ehci, info2);
	qh->is_out = !is_input;
	usb_settoggle (urb->dev, usb_pipeendpoपूर्णांक (urb->pipe), !is_input, 1);
	वापस qh;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम enable_async(काष्ठा ehci_hcd *ehci)
अणु
	अगर (ehci->async_count++)
		वापस;

	/* Stop रुकोing to turn off the async schedule */
	ehci->enabled_hrसमयr_events &= ~BIT(EHCI_HRTIMER_DISABLE_ASYNC);

	/* Don't start the schedule until ASS is 0 */
	ehci_poll_ASS(ehci);
	turn_on_io_watchकरोg(ehci);
पूर्ण

अटल व्योम disable_async(काष्ठा ehci_hcd *ehci)
अणु
	अगर (--ehci->async_count)
		वापस;

	/* The async schedule and unlink lists are supposed to be empty */
	WARN_ON(ehci->async->qh_next.qh || !list_empty(&ehci->async_unlink) ||
			!list_empty(&ehci->async_idle));

	/* Don't turn off the schedule until ASS is 1 */
	ehci_poll_ASS(ehci);
पूर्ण

/* move qh (and its qtds) onto async queue; maybe enable queue.  */

अटल व्योम qh_link_async (काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	__hc32		dma = QH_NEXT(ehci, qh->qh_dma);
	काष्ठा ehci_qh	*head;

	/* Don't link a QH if there's a Clear-TT-Buffer pending */
	अगर (unlikely(qh->clearing_tt))
		वापस;

	WARN_ON(qh->qh_state != QH_STATE_IDLE);

	/* clear halt and/or toggle; and maybe recover from silicon quirk */
	qh_refresh(ehci, qh);

	/* splice right after start */
	head = ehci->async;
	qh->qh_next = head->qh_next;
	qh->hw->hw_next = head->hw->hw_next;
	wmb ();

	head->qh_next.qh = qh;
	head->hw->hw_next = dma;

	qh->qh_state = QH_STATE_LINKED;
	qh->xacterrs = 0;
	qh->unlink_reason = 0;
	/* qtd completions reported later by पूर्णांकerrupt */

	enable_async(ehci);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * For control/bulk/पूर्णांकerrupt, वापस QH with these TDs appended.
 * Allocates and initializes the QH अगर necessary.
 * Returns null अगर it can't allocate a QH it needs to.
 * If the QH has TDs (urbs) alपढ़ोy, that's great.
 */
अटल काष्ठा ehci_qh *qh_append_tds (
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	काष्ठा list_head	*qtd_list,
	पूर्णांक			epnum,
	व्योम			**ptr
)
अणु
	काष्ठा ehci_qh		*qh = शून्य;
	__hc32			qh_addr_mask = cpu_to_hc32(ehci, 0x7f);

	qh = (काष्ठा ehci_qh *) *ptr;
	अगर (unlikely (qh == शून्य)) अणु
		/* can't sleep here, we have ehci->lock... */
		qh = qh_make (ehci, urb, GFP_ATOMIC);
		*ptr = qh;
	पूर्ण
	अगर (likely (qh != शून्य)) अणु
		काष्ठा ehci_qtd	*qtd;

		अगर (unlikely (list_empty (qtd_list)))
			qtd = शून्य;
		अन्यथा
			qtd = list_entry (qtd_list->next, काष्ठा ehci_qtd,
					qtd_list);

		/* control qh may need patching ... */
		अगर (unlikely (epnum == 0)) अणु

                        /* usb_reset_device() briefly reverts to address 0 */
                        अगर (usb_pipedevice (urb->pipe) == 0)
				qh->hw->hw_info1 &= ~qh_addr_mask;
		पूर्ण

		/* just one way to queue requests: swap with the dummy qtd.
		 * only hc or qh_refresh() ever modअगरy the overlay.
		 */
		अगर (likely (qtd != शून्य)) अणु
			काष्ठा ehci_qtd		*dummy;
			dma_addr_t		dma;
			__hc32			token;

			/* to aव्योम racing the HC, use the dummy td instead of
			 * the first td of our list (becomes new dummy).  both
			 * tds stay deactivated until we're करोne, when the
			 * HC is allowed to fetch the old dummy (4.10.2).
			 */
			token = qtd->hw_token;
			qtd->hw_token = HALT_BIT(ehci);

			dummy = qh->dummy;

			dma = dummy->qtd_dma;
			*dummy = *qtd;
			dummy->qtd_dma = dma;

			list_del (&qtd->qtd_list);
			list_add (&dummy->qtd_list, qtd_list);
			list_splice_tail(qtd_list, &qh->qtd_list);

			ehci_qtd_init(ehci, qtd, qtd->qtd_dma);
			qh->dummy = qtd;

			/* hc must see the new dummy at list end */
			dma = qtd->qtd_dma;
			qtd = list_entry (qh->qtd_list.prev,
					काष्ठा ehci_qtd, qtd_list);
			qtd->hw_next = QTD_NEXT(ehci, dma);

			/* let the hc process these next qtds */
			wmb ();
			dummy->hw_token = token;

			urb->hcpriv = qh;
		पूर्ण
	पूर्ण
	वापस qh;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
submit_async (
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	काष्ठा list_head	*qtd_list,
	gfp_t			mem_flags
) अणु
	पूर्णांक			epnum;
	अचिन्हित दीर्घ		flags;
	काष्ठा ehci_qh		*qh = शून्य;
	पूर्णांक			rc;

	epnum = urb->ep->desc.bEndpoपूर्णांकAddress;

#अगर_घोषित EHCI_URB_TRACE
	अणु
		काष्ठा ehci_qtd *qtd;
		qtd = list_entry(qtd_list->next, काष्ठा ehci_qtd, qtd_list);
		ehci_dbg(ehci,
			 "%s %s urb %p ep%d%s len %d, qtd %p [qh %p]\n",
			 __func__, urb->dev->devpath, urb,
			 epnum & 0x0f, (epnum & USB_सूची_IN) ? "in" : "out",
			 urb->transfer_buffer_length,
			 qtd, urb->ep->hcpriv);
	पूर्ण
#पूर्ण_अगर

	spin_lock_irqsave (&ehci->lock, flags);
	अगर (unlikely(!HCD_HW_ACCESSIBLE(ehci_to_hcd(ehci)))) अणु
		rc = -ESHUTDOWN;
		जाओ करोne;
	पूर्ण
	rc = usb_hcd_link_urb_to_ep(ehci_to_hcd(ehci), urb);
	अगर (unlikely(rc))
		जाओ करोne;

	qh = qh_append_tds(ehci, urb, qtd_list, epnum, &urb->ep->hcpriv);
	अगर (unlikely(qh == शून्य)) अणु
		usb_hcd_unlink_urb_from_ep(ehci_to_hcd(ehci), urb);
		rc = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Control/bulk operations through TTs करोn't need scheduling,
	 * the HC and TT handle it when the TT has a buffer पढ़ोy.
	 */
	अगर (likely (qh->qh_state == QH_STATE_IDLE))
		qh_link_async(ehci, qh);
 करोne:
	spin_unlock_irqrestore (&ehci->lock, flags);
	अगर (unlikely (qh == शून्य))
		qtd_list_मुक्त (ehci, urb, qtd_list);
	वापस rc;
पूर्ण

/*-------------------------------------------------------------------------*/
#अगर_घोषित CONFIG_USB_HCD_TEST_MODE
/*
 * This function creates the qtds and submits them क्रम the
 * SINGLE_STEP_SET_FEATURE Test.
 * This is करोne in two parts: first SETUP req क्रम GetDesc is sent then
 * 15 seconds later, the IN stage क्रम GetDesc starts to req data from dev
 *
 * is_setup : i/p arguement decides which of the two stage needs to be
 * perक्रमmed; TRUE - SETUP and FALSE - IN+STATUS
 * Returns 0 अगर success
 */
अटल पूर्णांक submit_single_step_set_feature(
	काष्ठा usb_hcd  *hcd,
	काष्ठा urb      *urb,
	पूर्णांक             is_setup
) अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);
	काष्ठा list_head	qtd_list;
	काष्ठा list_head	*head;

	काष्ठा ehci_qtd		*qtd, *qtd_prev;
	dma_addr_t		buf;
	पूर्णांक			len, maxpacket;
	u32			token;

	INIT_LIST_HEAD(&qtd_list);
	head = &qtd_list;

	/* URBs map to sequences of QTDs:  one logical transaction */
	qtd = ehci_qtd_alloc(ehci, GFP_KERNEL);
	अगर (unlikely(!qtd))
		वापस -1;
	list_add_tail(&qtd->qtd_list, head);
	qtd->urb = urb;

	token = QTD_STS_ACTIVE;
	token |= (EHCI_TUNE_CERR << 10);

	len = urb->transfer_buffer_length;
	/*
	 * Check अगर the request is to perक्रमm just the SETUP stage (getDesc)
	 * as in SINGLE_STEP_SET_FEATURE test, DATA stage (IN) happens
	 * 15 secs after the setup
	 */
	अगर (is_setup) अणु
		/* SETUP pid, and पूर्णांकerrupt after SETUP completion */
		qtd_fill(ehci, qtd, urb->setup_dma,
				माप(काष्ठा usb_ctrlrequest),
				QTD_IOC | token | (2 /* "setup" */ << 8), 8);

		submit_async(ehci, urb, &qtd_list, GFP_ATOMIC);
		वापस 0; /*Return now; we shall come back after 15 seconds*/
	पूर्ण

	/*
	 * IN: data transfer stage:  buffer setup : start the IN txn phase क्रम
	 * the get_Desc SETUP which was sent 15seconds back
	 */
	token ^= QTD_TOGGLE;   /*We need to start IN with DATA-1 Pid-sequence*/
	buf = urb->transfer_dma;

	token |= (1 /* "in" */ << 8);  /*This is IN stage*/

	maxpacket = usb_maxpacket(urb->dev, urb->pipe, 0);

	qtd_fill(ehci, qtd, buf, len, token, maxpacket);

	/*
	 * Our IN phase shall always be a लघु पढ़ो; so keep the queue running
	 * and let it advance to the next qtd which zero length OUT status
	 */
	qtd->hw_alt_next = EHCI_LIST_END(ehci);

	/* STATUS stage क्रम GetDesc control request */
	token ^= 0x0100;        /* "in" <--> "out"  */
	token |= QTD_TOGGLE;    /* क्रमce DATA1 */

	qtd_prev = qtd;
	qtd = ehci_qtd_alloc(ehci, GFP_ATOMIC);
	अगर (unlikely(!qtd))
		जाओ cleanup;
	qtd->urb = urb;
	qtd_prev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
	list_add_tail(&qtd->qtd_list, head);

	/* Interrupt after STATUS completion */
	qtd_fill(ehci, qtd, 0, 0, token | QTD_IOC, 0);

	submit_async(ehci, urb, &qtd_list, GFP_KERNEL);

	वापस 0;

cleanup:
	qtd_list_मुक्त(ehci, urb, head);
	वापस -1;
पूर्ण
#पूर्ण_अगर /* CONFIG_USB_HCD_TEST_MODE */

/*-------------------------------------------------------------------------*/

अटल व्योम single_unlink_async(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	काष्ठा ehci_qh		*prev;

	/* Add to the end of the list of QHs रुकोing क्रम the next IAAD */
	qh->qh_state = QH_STATE_UNLINK_WAIT;
	list_add_tail(&qh->unlink_node, &ehci->async_unlink);

	/* Unlink it from the schedule */
	prev = ehci->async;
	जबतक (prev->qh_next.qh != qh)
		prev = prev->qh_next.qh;

	prev->hw->hw_next = qh->hw->hw_next;
	prev->qh_next = qh->qh_next;
	अगर (ehci->qh_scan_next == qh)
		ehci->qh_scan_next = qh->qh_next.qh;
पूर्ण

अटल व्योम start_iaa_cycle(काष्ठा ehci_hcd *ehci)
अणु
	/* If the controller isn't running, we don't have to रुको क्रम it */
	अगर (unlikely(ehci->rh_state < EHCI_RH_RUNNING)) अणु
		end_unlink_async(ehci);

	/* Otherwise start a new IAA cycle अगर one isn't alपढ़ोy running */
	पूर्ण अन्यथा अगर (ehci->rh_state == EHCI_RH_RUNNING &&
			!ehci->iaa_in_progress) अणु

		/* Make sure the unlinks are all visible to the hardware */
		wmb();

		ehci_ग_लिखोl(ehci, ehci->command | CMD_IAAD,
				&ehci->regs->command);
		ehci_पढ़ोl(ehci, &ehci->regs->command);
		ehci->iaa_in_progress = true;
		ehci_enable_event(ehci, EHCI_HRTIMER_IAA_WATCHDOG, true);
	पूर्ण
पूर्ण

अटल व्योम end_iaa_cycle(काष्ठा ehci_hcd *ehci)
अणु
	अगर (ehci->has_synopsys_hc_bug)
		ehci_ग_लिखोl(ehci, (u32) ehci->async->qh_dma,
			    &ehci->regs->async_next);

	/* The current IAA cycle has ended */
	ehci->iaa_in_progress = false;

	end_unlink_async(ehci);
पूर्ण

/* See अगर the async qh क्रम the qtds being unlinked are now gone from the HC */

अटल व्योम end_unlink_async(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा ehci_qh		*qh;
	bool			early_निकास;

	अगर (list_empty(&ehci->async_unlink))
		वापस;
	qh = list_first_entry(&ehci->async_unlink, काष्ठा ehci_qh,
			unlink_node);	/* QH whose IAA cycle just ended */

	/*
	 * If async_unlinking is set then this routine is alपढ़ोy running,
	 * either on the stack or on another CPU.
	 */
	early_निकास = ehci->async_unlinking;

	/* If the controller isn't running, process all the रुकोing QHs */
	अगर (ehci->rh_state < EHCI_RH_RUNNING)
		list_splice_tail_init(&ehci->async_unlink, &ehci->async_idle);

	/*
	 * Intel (?) bug: The HC can ग_लिखो back the overlay region even
	 * after the IAA पूर्णांकerrupt occurs.  In self-defense, always go
	 * through two IAA cycles क्रम each QH.
	 */
	अन्यथा अगर (qh->qh_state == QH_STATE_UNLINK) अणु
		/*
		 * Second IAA cycle has finished.  Process only the first
		 * रुकोing QH (NVIDIA (?) bug).
		 */
		list_move_tail(&qh->unlink_node, &ehci->async_idle);
	पूर्ण

	/*
	 * AMD/ATI (?) bug: The HC can जारी to use an active QH दीर्घ
	 * after the IAA पूर्णांकerrupt occurs.  To prevent problems, QHs that
	 * may still be active will रुको until 2 ms have passed with no
	 * change to the hw_current and hw_token fields (this delay occurs
	 * between the two IAA cycles).
	 *
	 * The EHCI spec (4.8.2) says that active QHs must not be हटाओd
	 * from the async schedule and recommends रुकोing until the QH
	 * goes inactive.  This is ridiculous because the QH will _never_
	 * become inactive अगर the endpoपूर्णांक NAKs indefinitely.
	 */

	/* Some reasons क्रम unlinking guarantee the QH can't be active */
	अन्यथा अगर (qh->unlink_reason & (QH_UNLINK_HALTED |
			QH_UNLINK_SHORT_READ | QH_UNLINK_DUMMY_OVERLAY))
		जाओ DelayDone;

	/* The QH can't be active अगर the queue was and still is empty... */
	अन्यथा अगर	((qh->unlink_reason & QH_UNLINK_QUEUE_EMPTY) &&
			list_empty(&qh->qtd_list))
		जाओ DelayDone;

	/* ... or अगर the QH has halted */
	अन्यथा अगर	(qh->hw->hw_token & cpu_to_hc32(ehci, QTD_STS_HALT))
		जाओ DelayDone;

	/* Otherwise we have to रुको until the QH stops changing */
	अन्यथा अणु
		__hc32		qh_current, qh_token;

		qh_current = qh->hw->hw_current;
		qh_token = qh->hw->hw_token;
		अगर (qh_current != ehci->old_current ||
				qh_token != ehci->old_token) अणु
			ehci->old_current = qh_current;
			ehci->old_token = qh_token;
			ehci_enable_event(ehci,
					EHCI_HRTIMER_ACTIVE_UNLINK, true);
			वापस;
		पूर्ण
 DelayDone:
		qh->qh_state = QH_STATE_UNLINK;
		early_निकास = true;
	पूर्ण
	ehci->old_current = ~0;		/* Prepare क्रम next QH */

	/* Start a new IAA cycle अगर any QHs are रुकोing क्रम it */
	अगर (!list_empty(&ehci->async_unlink))
		start_iaa_cycle(ehci);

	/*
	 * Don't allow nesting or concurrent calls,
	 * or रुको क्रम the second IAA cycle क्रम the next QH.
	 */
	अगर (early_निकास)
		वापस;

	/* Process the idle QHs */
	ehci->async_unlinking = true;
	जबतक (!list_empty(&ehci->async_idle)) अणु
		qh = list_first_entry(&ehci->async_idle, काष्ठा ehci_qh,
				unlink_node);
		list_del(&qh->unlink_node);

		qh->qh_state = QH_STATE_IDLE;
		qh->qh_next.qh = शून्य;

		अगर (!list_empty(&qh->qtd_list))
			qh_completions(ehci, qh);
		अगर (!list_empty(&qh->qtd_list) &&
				ehci->rh_state == EHCI_RH_RUNNING)
			qh_link_async(ehci, qh);
		disable_async(ehci);
	पूर्ण
	ehci->async_unlinking = false;
पूर्ण

अटल व्योम start_unlink_async(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh);

अटल व्योम unlink_empty_async(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा ehci_qh		*qh;
	काष्ठा ehci_qh		*qh_to_unlink = शून्य;
	पूर्णांक			count = 0;

	/* Find the last async QH which has been empty क्रम a समयr cycle */
	क्रम (qh = ehci->async->qh_next.qh; qh; qh = qh->qh_next.qh) अणु
		अगर (list_empty(&qh->qtd_list) &&
				qh->qh_state == QH_STATE_LINKED) अणु
			++count;
			अगर (qh->unlink_cycle != ehci->async_unlink_cycle)
				qh_to_unlink = qh;
		पूर्ण
	पूर्ण

	/* If nothing अन्यथा is being unlinked, unlink the last empty QH */
	अगर (list_empty(&ehci->async_unlink) && qh_to_unlink) अणु
		qh_to_unlink->unlink_reason |= QH_UNLINK_QUEUE_EMPTY;
		start_unlink_async(ehci, qh_to_unlink);
		--count;
	पूर्ण

	/* Other QHs will be handled later */
	अगर (count > 0) अणु
		ehci_enable_event(ehci, EHCI_HRTIMER_ASYNC_UNLINKS, true);
		++ehci->async_unlink_cycle;
	पूर्ण
पूर्ण

#अगर_घोषित	CONFIG_PM

/* The root hub is suspended; unlink all the async QHs */
अटल व्योम unlink_empty_async_suspended(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा ehci_qh		*qh;

	जबतक (ehci->async->qh_next.qh) अणु
		qh = ehci->async->qh_next.qh;
		WARN_ON(!list_empty(&qh->qtd_list));
		single_unlink_async(ehci, qh);
	पूर्ण
पूर्ण

#पूर्ण_अगर

/* makes sure the async qh will become idle */
/* caller must own ehci->lock */

अटल व्योम start_unlink_async(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	/* If the QH isn't linked then there's nothing we can करो. */
	अगर (qh->qh_state != QH_STATE_LINKED)
		वापस;

	single_unlink_async(ehci, qh);
	start_iaa_cycle(ehci);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम scan_async (काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा ehci_qh		*qh;
	bool			check_unlinks_later = false;

	ehci->qh_scan_next = ehci->async->qh_next.qh;
	जबतक (ehci->qh_scan_next) अणु
		qh = ehci->qh_scan_next;
		ehci->qh_scan_next = qh->qh_next.qh;

		/* clean any finished work क्रम this qh */
		अगर (!list_empty(&qh->qtd_list)) अणु
			पूर्णांक temp;

			/*
			 * Unlinks could happen here; completion reporting
			 * drops the lock.  That's why ehci->qh_scan_next
			 * always holds the next qh to scan; अगर the next qh
			 * माला_लो unlinked then ehci->qh_scan_next is adjusted
			 * in single_unlink_async().
			 */
			temp = qh_completions(ehci, qh);
			अगर (unlikely(temp)) अणु
				start_unlink_async(ehci, qh);
			पूर्ण अन्यथा अगर (list_empty(&qh->qtd_list)
					&& qh->qh_state == QH_STATE_LINKED) अणु
				qh->unlink_cycle = ehci->async_unlink_cycle;
				check_unlinks_later = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Unlink empty entries, reducing DMA usage as well
	 * as HCD schedule-scanning costs.  Delay क्रम any qh
	 * we just scanned, there's a not-unusual हाल that it
	 * करोesn't stay idle क्रम दीर्घ.
	 */
	अगर (check_unlinks_later && ehci->rh_state == EHCI_RH_RUNNING &&
			!(ehci->enabled_hrसमयr_events &
				BIT(EHCI_HRTIMER_ASYNC_UNLINKS))) अणु
		ehci_enable_event(ehci, EHCI_HRTIMER_ASYNC_UNLINKS, true);
		++ehci->async_unlink_cycle;
	पूर्ण
पूर्ण
