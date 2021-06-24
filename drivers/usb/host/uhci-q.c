<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Universal Host Controller Interface driver क्रम USB.
 *
 * Maपूर्णांकainer: Alan Stern <stern@rowland.harvard.edu>
 *
 * (C) Copyright 1999 Linus Torvalds
 * (C) Copyright 1999-2002 Johannes Erdfelt, johannes@erdfelt.com
 * (C) Copyright 1999 Randy Dunlap
 * (C) Copyright 1999 Georg Acher, acher@in.tum.de
 * (C) Copyright 1999 Deti Fliegl, deti@fliegl.de
 * (C) Copyright 1999 Thomas Sailer, sailer@अगरe.ee.ethz.ch
 * (C) Copyright 1999 Roman Weissgaerber, weissg@vienna.at
 * (C) Copyright 2000 Yggdrasil Computing, Inc. (port of new PCI पूर्णांकerface
 *               support from usb-ohci.c by Adam Richter, adam@yggdrasil.com).
 * (C) Copyright 1999 Gregory P. Smith (from usb-ohci.c)
 * (C) Copyright 2004-2007 Alan Stern, stern@rowland.harvard.edu
 */


/*
 * Technically, updating td->status here is a race, but it's not really a
 * problem. The worst that can happen is that we set the IOC bit again
 * generating a spurious पूर्णांकerrupt. We could fix this by creating another
 * QH and leaving the IOC bit always set, but then we would have to play
 * games with the FSBR code to make sure we get the correct order in all
 * the हालs. I करोn't think it's worth the efक्रमt
 */
अटल व्योम uhci_set_next_पूर्णांकerrupt(काष्ठा uhci_hcd *uhci)
अणु
	अगर (uhci->is_stopped)
		mod_समयr(&uhci_to_hcd(uhci)->rh_समयr, jअगरfies);
	uhci->term_td->status |= cpu_to_hc32(uhci, TD_CTRL_IOC);
पूर्ण

अटल अंतरभूत व्योम uhci_clear_next_पूर्णांकerrupt(काष्ठा uhci_hcd *uhci)
अणु
	uhci->term_td->status &= ~cpu_to_hc32(uhci, TD_CTRL_IOC);
पूर्ण


/*
 * Full-Speed Bandwidth Reclamation (FSBR).
 * We turn on FSBR whenever a queue that wants it is advancing,
 * and leave it on क्रम a लघु समय thereafter.
 */
अटल व्योम uhci_fsbr_on(काष्ठा uhci_hcd *uhci)
अणु
	काष्ठा uhci_qh *lqh;

	/* The terminating skeleton QH always poपूर्णांकs back to the first
	 * FSBR QH.  Make the last async QH poपूर्णांक to the terminating
	 * skeleton QH. */
	uhci->fsbr_is_on = 1;
	lqh = list_entry(uhci->skel_async_qh->node.prev,
			काष्ठा uhci_qh, node);
	lqh->link = LINK_TO_QH(uhci, uhci->skel_term_qh);
पूर्ण

अटल व्योम uhci_fsbr_off(काष्ठा uhci_hcd *uhci)
अणु
	काष्ठा uhci_qh *lqh;

	/* Remove the link from the last async QH to the terminating
	 * skeleton QH. */
	uhci->fsbr_is_on = 0;
	lqh = list_entry(uhci->skel_async_qh->node.prev,
			काष्ठा uhci_qh, node);
	lqh->link = UHCI_PTR_TERM(uhci);
पूर्ण

अटल व्योम uhci_add_fsbr(काष्ठा uhci_hcd *uhci, काष्ठा urb *urb)
अणु
	काष्ठा urb_priv *urbp = urb->hcpriv;

	urbp->fsbr = 1;
पूर्ण

अटल व्योम uhci_urbp_wants_fsbr(काष्ठा uhci_hcd *uhci, काष्ठा urb_priv *urbp)
अणु
	अगर (urbp->fsbr) अणु
		uhci->fsbr_is_wanted = 1;
		अगर (!uhci->fsbr_is_on)
			uhci_fsbr_on(uhci);
		अन्यथा अगर (uhci->fsbr_expiring) अणु
			uhci->fsbr_expiring = 0;
			del_समयr(&uhci->fsbr_समयr);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम uhci_fsbr_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा uhci_hcd *uhci = from_समयr(uhci, t, fsbr_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uhci->lock, flags);
	अगर (uhci->fsbr_expiring) अणु
		uhci->fsbr_expiring = 0;
		uhci_fsbr_off(uhci);
	पूर्ण
	spin_unlock_irqrestore(&uhci->lock, flags);
पूर्ण


अटल काष्ठा uhci_td *uhci_alloc_td(काष्ठा uhci_hcd *uhci)
अणु
	dma_addr_t dma_handle;
	काष्ठा uhci_td *td;

	td = dma_pool_alloc(uhci->td_pool, GFP_ATOMIC, &dma_handle);
	अगर (!td)
		वापस शून्य;

	td->dma_handle = dma_handle;
	td->frame = -1;

	INIT_LIST_HEAD(&td->list);
	INIT_LIST_HEAD(&td->fl_list);

	वापस td;
पूर्ण

अटल व्योम uhci_मुक्त_td(काष्ठा uhci_hcd *uhci, काष्ठा uhci_td *td)
अणु
	अगर (!list_empty(&td->list))
		dev_WARN(uhci_dev(uhci), "td %p still in list!\n", td);
	अगर (!list_empty(&td->fl_list))
		dev_WARN(uhci_dev(uhci), "td %p still in fl_list!\n", td);

	dma_pool_मुक्त(uhci->td_pool, td, td->dma_handle);
पूर्ण

अटल अंतरभूत व्योम uhci_fill_td(काष्ठा uhci_hcd *uhci, काष्ठा uhci_td *td,
		u32 status, u32 token, u32 buffer)
अणु
	td->status = cpu_to_hc32(uhci, status);
	td->token = cpu_to_hc32(uhci, token);
	td->buffer = cpu_to_hc32(uhci, buffer);
पूर्ण

अटल व्योम uhci_add_td_to_urbp(काष्ठा uhci_td *td, काष्ठा urb_priv *urbp)
अणु
	list_add_tail(&td->list, &urbp->td_list);
पूर्ण

अटल व्योम uhci_हटाओ_td_from_urbp(काष्ठा uhci_td *td)
अणु
	list_del_init(&td->list);
पूर्ण

/*
 * We insert Isochronous URBs directly पूर्णांकo the frame list at the beginning
 */
अटल अंतरभूत व्योम uhci_insert_td_in_frame_list(काष्ठा uhci_hcd *uhci,
		काष्ठा uhci_td *td, अचिन्हित framक्रमागत)
अणु
	framक्रमागत &= (UHCI_NUMFRAMES - 1);

	td->frame = framक्रमागत;

	/* Is there a TD alपढ़ोy mapped there? */
	अगर (uhci->frame_cpu[framक्रमागत]) अणु
		काष्ठा uhci_td *ftd, *ltd;

		ftd = uhci->frame_cpu[framक्रमागत];
		ltd = list_entry(ftd->fl_list.prev, काष्ठा uhci_td, fl_list);

		list_add_tail(&td->fl_list, &ftd->fl_list);

		td->link = ltd->link;
		wmb();
		ltd->link = LINK_TO_TD(uhci, td);
	पूर्ण अन्यथा अणु
		td->link = uhci->frame[framक्रमागत];
		wmb();
		uhci->frame[framक्रमागत] = LINK_TO_TD(uhci, td);
		uhci->frame_cpu[framक्रमागत] = td;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम uhci_हटाओ_td_from_frame_list(काष्ठा uhci_hcd *uhci,
		काष्ठा uhci_td *td)
अणु
	/* If it's not inserted, don't हटाओ it */
	अगर (td->frame == -1) अणु
		WARN_ON(!list_empty(&td->fl_list));
		वापस;
	पूर्ण

	अगर (uhci->frame_cpu[td->frame] == td) अणु
		अगर (list_empty(&td->fl_list)) अणु
			uhci->frame[td->frame] = td->link;
			uhci->frame_cpu[td->frame] = शून्य;
		पूर्ण अन्यथा अणु
			काष्ठा uhci_td *ntd;

			ntd = list_entry(td->fl_list.next,
					 काष्ठा uhci_td,
					 fl_list);
			uhci->frame[td->frame] = LINK_TO_TD(uhci, ntd);
			uhci->frame_cpu[td->frame] = ntd;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा uhci_td *ptd;

		ptd = list_entry(td->fl_list.prev, काष्ठा uhci_td, fl_list);
		ptd->link = td->link;
	पूर्ण

	list_del_init(&td->fl_list);
	td->frame = -1;
पूर्ण

अटल अंतरभूत व्योम uhci_हटाओ_tds_from_frame(काष्ठा uhci_hcd *uhci,
		अचिन्हित पूर्णांक framक्रमागत)
अणु
	काष्ठा uhci_td *ftd, *ltd;

	framक्रमागत &= (UHCI_NUMFRAMES - 1);

	ftd = uhci->frame_cpu[framक्रमागत];
	अगर (ftd) अणु
		ltd = list_entry(ftd->fl_list.prev, काष्ठा uhci_td, fl_list);
		uhci->frame[framक्रमागत] = ltd->link;
		uhci->frame_cpu[framक्रमागत] = शून्य;

		जबतक (!list_empty(&ftd->fl_list))
			list_del_init(ftd->fl_list.prev);
	पूर्ण
पूर्ण

/*
 * Remove all the TDs क्रम an Isochronous URB from the frame list
 */
अटल व्योम uhci_unlink_isochronous_tds(काष्ठा uhci_hcd *uhci, काष्ठा urb *urb)
अणु
	काष्ठा urb_priv *urbp = (काष्ठा urb_priv *) urb->hcpriv;
	काष्ठा uhci_td *td;

	list_क्रम_each_entry(td, &urbp->td_list, list)
		uhci_हटाओ_td_from_frame_list(uhci, td);
पूर्ण

अटल काष्ठा uhci_qh *uhci_alloc_qh(काष्ठा uhci_hcd *uhci,
		काष्ठा usb_device *udev, काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	dma_addr_t dma_handle;
	काष्ठा uhci_qh *qh;

	qh = dma_pool_zalloc(uhci->qh_pool, GFP_ATOMIC, &dma_handle);
	अगर (!qh)
		वापस शून्य;

	qh->dma_handle = dma_handle;

	qh->element = UHCI_PTR_TERM(uhci);
	qh->link = UHCI_PTR_TERM(uhci);

	INIT_LIST_HEAD(&qh->queue);
	INIT_LIST_HEAD(&qh->node);

	अगर (udev) अणु		/* Normal QH */
		qh->type = usb_endpoपूर्णांक_type(&hep->desc);
		अगर (qh->type != USB_ENDPOINT_XFER_ISOC) अणु
			qh->dummy_td = uhci_alloc_td(uhci);
			अगर (!qh->dummy_td) अणु
				dma_pool_मुक्त(uhci->qh_pool, qh, dma_handle);
				वापस शून्य;
			पूर्ण
		पूर्ण
		qh->state = QH_STATE_IDLE;
		qh->hep = hep;
		qh->udev = udev;
		hep->hcpriv = qh;

		अगर (qh->type == USB_ENDPOINT_XFER_INT ||
				qh->type == USB_ENDPOINT_XFER_ISOC)
			qh->load = usb_calc_bus_समय(udev->speed,
					usb_endpoपूर्णांक_dir_in(&hep->desc),
					qh->type == USB_ENDPOINT_XFER_ISOC,
					usb_endpoपूर्णांक_maxp(&hep->desc))
				/ 1000 + 1;

	पूर्ण अन्यथा अणु		/* Skeleton QH */
		qh->state = QH_STATE_ACTIVE;
		qh->type = -1;
	पूर्ण
	वापस qh;
पूर्ण

अटल व्योम uhci_मुक्त_qh(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	WARN_ON(qh->state != QH_STATE_IDLE && qh->udev);
	अगर (!list_empty(&qh->queue))
		dev_WARN(uhci_dev(uhci), "qh %p list not empty!\n", qh);

	list_del(&qh->node);
	अगर (qh->udev) अणु
		qh->hep->hcpriv = शून्य;
		अगर (qh->dummy_td)
			uhci_मुक्त_td(uhci, qh->dummy_td);
	पूर्ण
	dma_pool_मुक्त(uhci->qh_pool, qh, qh->dma_handle);
पूर्ण

/*
 * When a queue is stopped and a dequeued URB is given back, adjust
 * the previous TD link (अगर the URB isn't first on the queue) or
 * save its toggle value (अगर it is first and is currently executing).
 *
 * Returns 0 अगर the URB should not yet be given back, 1 otherwise.
 */
अटल पूर्णांक uhci_cleanup_queue(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh,
		काष्ठा urb *urb)
अणु
	काष्ठा urb_priv *urbp = urb->hcpriv;
	काष्ठा uhci_td *td;
	पूर्णांक ret = 1;

	/* Isochronous pipes करोn't use toggles and their TD link poपूर्णांकers
	 * get adjusted during uhci_urb_dequeue().  But since their queues
	 * cannot truly be stopped, we have to watch out क्रम dequeues
	 * occurring after the nominal unlink frame. */
	अगर (qh->type == USB_ENDPOINT_XFER_ISOC) अणु
		ret = (uhci->frame_number + uhci->is_stopped !=
				qh->unlink_frame);
		जाओ करोne;
	पूर्ण

	/* If the URB isn't first on its queue, adjust the link poपूर्णांकer
	 * of the last TD in the previous URB.  The toggle करोesn't need
	 * to be saved since this URB can't be executing yet. */
	अगर (qh->queue.next != &urbp->node) अणु
		काष्ठा urb_priv *purbp;
		काष्ठा uhci_td *ptd;

		purbp = list_entry(urbp->node.prev, काष्ठा urb_priv, node);
		WARN_ON(list_empty(&purbp->td_list));
		ptd = list_entry(purbp->td_list.prev, काष्ठा uhci_td,
				list);
		td = list_entry(urbp->td_list.prev, काष्ठा uhci_td,
				list);
		ptd->link = td->link;
		जाओ करोne;
	पूर्ण

	/* If the QH element poपूर्णांकer is UHCI_PTR_TERM then then currently
	 * executing URB has alपढ़ोy been unlinked, so this one isn't it. */
	अगर (qh_element(qh) == UHCI_PTR_TERM(uhci))
		जाओ करोne;
	qh->element = UHCI_PTR_TERM(uhci);

	/* Control pipes करोn't have to worry about toggles */
	अगर (qh->type == USB_ENDPOINT_XFER_CONTROL)
		जाओ करोne;

	/* Save the next toggle value */
	WARN_ON(list_empty(&urbp->td_list));
	td = list_entry(urbp->td_list.next, काष्ठा uhci_td, list);
	qh->needs_fixup = 1;
	qh->initial_toggle = uhci_toggle(td_token(uhci, td));

करोne:
	वापस ret;
पूर्ण

/*
 * Fix up the data toggles क्रम URBs in a queue, when one of them
 * terminates early (लघु transfer, error, or dequeued).
 */
अटल व्योम uhci_fixup_toggles(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh,
			पूर्णांक skip_first)
अणु
	काष्ठा urb_priv *urbp = शून्य;
	काष्ठा uhci_td *td;
	अचिन्हित पूर्णांक toggle = qh->initial_toggle;
	अचिन्हित पूर्णांक pipe;

	/* Fixups क्रम a लघु transfer start with the second URB in the
	 * queue (the लघु URB is the first). */
	अगर (skip_first)
		urbp = list_entry(qh->queue.next, काष्ठा urb_priv, node);

	/* When starting with the first URB, अगर the QH element poपूर्णांकer is
	 * still valid then we know the URB's toggles are okay. */
	अन्यथा अगर (qh_element(qh) != UHCI_PTR_TERM(uhci))
		toggle = 2;

	/* Fix up the toggle क्रम the URBs in the queue.  Normally this
	 * loop won't run more than once: When an error or लघु transfer
	 * occurs, the queue usually माला_लो emptied. */
	urbp = list_prepare_entry(urbp, &qh->queue, node);
	list_क्रम_each_entry_जारी(urbp, &qh->queue, node) अणु

		/* If the first TD has the right toggle value, we करोn't
		 * need to change any toggles in this URB */
		td = list_entry(urbp->td_list.next, काष्ठा uhci_td, list);
		अगर (toggle > 1 || uhci_toggle(td_token(uhci, td)) == toggle) अणु
			td = list_entry(urbp->td_list.prev, काष्ठा uhci_td,
					list);
			toggle = uhci_toggle(td_token(uhci, td)) ^ 1;

		/* Otherwise all the toggles in the URB have to be चयनed */
		पूर्ण अन्यथा अणु
			list_क्रम_each_entry(td, &urbp->td_list, list) अणु
				td->token ^= cpu_to_hc32(uhci,
							TD_TOKEN_TOGGLE);
				toggle ^= 1;
			पूर्ण
		पूर्ण
	पूर्ण

	wmb();
	pipe = list_entry(qh->queue.next, काष्ठा urb_priv, node)->urb->pipe;
	usb_settoggle(qh->udev, usb_pipeendpoपूर्णांक(pipe),
			usb_pipeout(pipe), toggle);
	qh->needs_fixup = 0;
पूर्ण

/*
 * Link an Isochronous QH पूर्णांकo its skeleton's list
 */
अटल अंतरभूत व्योम link_iso(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	list_add_tail(&qh->node, &uhci->skel_iso_qh->node);

	/* Isochronous QHs aren't linked by the hardware */
पूर्ण

/*
 * Link a high-period पूर्णांकerrupt QH पूर्णांकo the schedule at the end of its
 * skeleton's list
 */
अटल व्योम link_पूर्णांकerrupt(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	काष्ठा uhci_qh *pqh;

	list_add_tail(&qh->node, &uhci->skelqh[qh->skel]->node);

	pqh = list_entry(qh->node.prev, काष्ठा uhci_qh, node);
	qh->link = pqh->link;
	wmb();
	pqh->link = LINK_TO_QH(uhci, qh);
पूर्ण

/*
 * Link a period-1 पूर्णांकerrupt or async QH पूर्णांकo the schedule at the
 * correct spot in the async skeleton's list, and update the FSBR link
 */
अटल व्योम link_async(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	काष्ठा uhci_qh *pqh;
	__hc32 link_to_new_qh;

	/* Find the predecessor QH क्रम our new one and insert it in the list.
	 * The list of QHs is expected to be लघु, so linear search won't
	 * take too दीर्घ. */
	list_क्रम_each_entry_reverse(pqh, &uhci->skel_async_qh->node, node) अणु
		अगर (pqh->skel <= qh->skel)
			अवरोध;
	पूर्ण
	list_add(&qh->node, &pqh->node);

	/* Link it पूर्णांकo the schedule */
	qh->link = pqh->link;
	wmb();
	link_to_new_qh = LINK_TO_QH(uhci, qh);
	pqh->link = link_to_new_qh;

	/* If this is now the first FSBR QH, link the terminating skeleton
	 * QH to it. */
	अगर (pqh->skel < SKEL_FSBR && qh->skel >= SKEL_FSBR)
		uhci->skel_term_qh->link = link_to_new_qh;
पूर्ण

/*
 * Put a QH on the schedule in both hardware and software
 */
अटल व्योम uhci_activate_qh(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	WARN_ON(list_empty(&qh->queue));

	/* Set the element poपूर्णांकer अगर it isn't set alपढ़ोy.
	 * This isn't needed for Isochronous queues, but it doesn't hurt. */
	अगर (qh_element(qh) == UHCI_PTR_TERM(uhci)) अणु
		काष्ठा urb_priv *urbp = list_entry(qh->queue.next,
				काष्ठा urb_priv, node);
		काष्ठा uhci_td *td = list_entry(urbp->td_list.next,
				काष्ठा uhci_td, list);

		qh->element = LINK_TO_TD(uhci, td);
	पूर्ण

	/* Treat the queue as अगर it has just advanced */
	qh->रुको_expired = 0;
	qh->advance_jअगरfies = jअगरfies;

	अगर (qh->state == QH_STATE_ACTIVE)
		वापस;
	qh->state = QH_STATE_ACTIVE;

	/* Move the QH from its old list to the correct spot in the appropriate
	 * skeleton's list */
	अगर (qh == uhci->next_qh)
		uhci->next_qh = list_entry(qh->node.next, काष्ठा uhci_qh,
				node);
	list_del(&qh->node);

	अगर (qh->skel == SKEL_ISO)
		link_iso(uhci, qh);
	अन्यथा अगर (qh->skel < SKEL_ASYNC)
		link_पूर्णांकerrupt(uhci, qh);
	अन्यथा
		link_async(uhci, qh);
पूर्ण

/*
 * Unlink a high-period पूर्णांकerrupt QH from the schedule
 */
अटल व्योम unlink_पूर्णांकerrupt(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	काष्ठा uhci_qh *pqh;

	pqh = list_entry(qh->node.prev, काष्ठा uhci_qh, node);
	pqh->link = qh->link;
	mb();
पूर्ण

/*
 * Unlink a period-1 पूर्णांकerrupt or async QH from the schedule
 */
अटल व्योम unlink_async(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	काष्ठा uhci_qh *pqh;
	__hc32 link_to_next_qh = qh->link;

	pqh = list_entry(qh->node.prev, काष्ठा uhci_qh, node);
	pqh->link = link_to_next_qh;

	/* If this was the old first FSBR QH, link the terminating skeleton
	 * QH to the next (new first FSBR) QH. */
	अगर (pqh->skel < SKEL_FSBR && qh->skel >= SKEL_FSBR)
		uhci->skel_term_qh->link = link_to_next_qh;
	mb();
पूर्ण

/*
 * Take a QH off the hardware schedule
 */
अटल व्योम uhci_unlink_qh(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	अगर (qh->state == QH_STATE_UNLINKING)
		वापस;
	WARN_ON(qh->state != QH_STATE_ACTIVE || !qh->udev);
	qh->state = QH_STATE_UNLINKING;

	/* Unlink the QH from the schedule and record when we did it */
	अगर (qh->skel == SKEL_ISO)
		;
	अन्यथा अगर (qh->skel < SKEL_ASYNC)
		unlink_पूर्णांकerrupt(uhci, qh);
	अन्यथा
		unlink_async(uhci, qh);

	uhci_get_current_frame_number(uhci);
	qh->unlink_frame = uhci->frame_number;

	/* Force an पूर्णांकerrupt so we know when the QH is fully unlinked */
	अगर (list_empty(&uhci->skel_unlink_qh->node) || uhci->is_stopped)
		uhci_set_next_पूर्णांकerrupt(uhci);

	/* Move the QH from its old list to the end of the unlinking list */
	अगर (qh == uhci->next_qh)
		uhci->next_qh = list_entry(qh->node.next, काष्ठा uhci_qh,
				node);
	list_move_tail(&qh->node, &uhci->skel_unlink_qh->node);
पूर्ण

/*
 * When we and the controller are through with a QH, it becomes IDLE.
 * This happens when a QH has been off the schedule (on the unlinking
 * list) क्रम more than one frame, or when an error occurs जबतक adding
 * the first URB onto a new QH.
 */
अटल व्योम uhci_make_qh_idle(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	WARN_ON(qh->state == QH_STATE_ACTIVE);

	अगर (qh == uhci->next_qh)
		uhci->next_qh = list_entry(qh->node.next, काष्ठा uhci_qh,
				node);
	list_move(&qh->node, &uhci->idle_qh_list);
	qh->state = QH_STATE_IDLE;

	/* Now that the QH is idle, its post_td isn't being used */
	अगर (qh->post_td) अणु
		uhci_मुक्त_td(uhci, qh->post_td);
		qh->post_td = शून्य;
	पूर्ण

	/* If anyone is रुकोing क्रम a QH to become idle, wake them up */
	अगर (uhci->num_रुकोing)
		wake_up_all(&uhci->रुकोqh);
पूर्ण

/*
 * Find the highest existing bandwidth load क्रम a given phase and period.
 */
अटल पूर्णांक uhci_highest_load(काष्ठा uhci_hcd *uhci, पूर्णांक phase, पूर्णांक period)
अणु
	पूर्णांक highest_load = uhci->load[phase];

	क्रम (phase += period; phase < MAX_PHASE; phase += period)
		highest_load = max_t(पूर्णांक, highest_load, uhci->load[phase]);
	वापस highest_load;
पूर्ण

/*
 * Set qh->phase to the optimal phase क्रम a periodic transfer and
 * check whether the bandwidth requirement is acceptable.
 */
अटल पूर्णांक uhci_check_bandwidth(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	पूर्णांक minimax_load;

	/* Find the optimal phase (unless it is alपढ़ोy set) and get
	 * its load value. */
	अगर (qh->phase >= 0)
		minimax_load = uhci_highest_load(uhci, qh->phase, qh->period);
	अन्यथा अणु
		पूर्णांक phase, load;
		पूर्णांक max_phase = min_t(पूर्णांक, MAX_PHASE, qh->period);

		qh->phase = 0;
		minimax_load = uhci_highest_load(uhci, qh->phase, qh->period);
		क्रम (phase = 1; phase < max_phase; ++phase) अणु
			load = uhci_highest_load(uhci, phase, qh->period);
			अगर (load < minimax_load) अणु
				minimax_load = load;
				qh->phase = phase;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Maximum allowable periodic bandwidth is 90%, or 900 us per frame */
	अगर (minimax_load + qh->load > 900) अणु
		dev_dbg(uhci_dev(uhci), "bandwidth allocation failed: "
				"period %d, phase %d, %d + %d us\n",
				qh->period, qh->phase, minimax_load, qh->load);
		वापस -ENOSPC;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Reserve a periodic QH's bandwidth in the schedule
 */
अटल व्योम uhci_reserve_bandwidth(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	पूर्णांक i;
	पूर्णांक load = qh->load;
	अक्षर *p = "??";

	क्रम (i = qh->phase; i < MAX_PHASE; i += qh->period) अणु
		uhci->load[i] += load;
		uhci->total_load += load;
	पूर्ण
	uhci_to_hcd(uhci)->self.bandwidth_allocated =
			uhci->total_load / MAX_PHASE;
	चयन (qh->type) अणु
	हाल USB_ENDPOINT_XFER_INT:
		++uhci_to_hcd(uhci)->self.bandwidth_पूर्णांक_reqs;
		p = "INT";
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		++uhci_to_hcd(uhci)->self.bandwidth_isoc_reqs;
		p = "ISO";
		अवरोध;
	पूर्ण
	qh->bandwidth_reserved = 1;
	dev_dbg(uhci_dev(uhci),
			"%s dev %d ep%02x-%s, period %d, phase %d, %d us\n",
			"reserve", qh->udev->devnum,
			qh->hep->desc.bEndpoपूर्णांकAddress, p,
			qh->period, qh->phase, load);
पूर्ण

/*
 * Release a periodic QH's bandwidth reservation
 */
अटल व्योम uhci_release_bandwidth(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	पूर्णांक i;
	पूर्णांक load = qh->load;
	अक्षर *p = "??";

	क्रम (i = qh->phase; i < MAX_PHASE; i += qh->period) अणु
		uhci->load[i] -= load;
		uhci->total_load -= load;
	पूर्ण
	uhci_to_hcd(uhci)->self.bandwidth_allocated =
			uhci->total_load / MAX_PHASE;
	चयन (qh->type) अणु
	हाल USB_ENDPOINT_XFER_INT:
		--uhci_to_hcd(uhci)->self.bandwidth_पूर्णांक_reqs;
		p = "INT";
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		--uhci_to_hcd(uhci)->self.bandwidth_isoc_reqs;
		p = "ISO";
		अवरोध;
	पूर्ण
	qh->bandwidth_reserved = 0;
	dev_dbg(uhci_dev(uhci),
			"%s dev %d ep%02x-%s, period %d, phase %d, %d us\n",
			"release", qh->udev->devnum,
			qh->hep->desc.bEndpoपूर्णांकAddress, p,
			qh->period, qh->phase, load);
पूर्ण

अटल अंतरभूत काष्ठा urb_priv *uhci_alloc_urb_priv(काष्ठा uhci_hcd *uhci,
		काष्ठा urb *urb)
अणु
	काष्ठा urb_priv *urbp;

	urbp = kmem_cache_zalloc(uhci_up_cachep, GFP_ATOMIC);
	अगर (!urbp)
		वापस शून्य;

	urbp->urb = urb;
	urb->hcpriv = urbp;

	INIT_LIST_HEAD(&urbp->node);
	INIT_LIST_HEAD(&urbp->td_list);

	वापस urbp;
पूर्ण

अटल व्योम uhci_मुक्त_urb_priv(काष्ठा uhci_hcd *uhci,
		काष्ठा urb_priv *urbp)
अणु
	काष्ठा uhci_td *td, *पंचांगp;

	अगर (!list_empty(&urbp->node))
		dev_WARN(uhci_dev(uhci), "urb %p still on QH's list!\n",
				urbp->urb);

	list_क्रम_each_entry_safe(td, पंचांगp, &urbp->td_list, list) अणु
		uhci_हटाओ_td_from_urbp(td);
		uhci_मुक्त_td(uhci, td);
	पूर्ण

	kmem_cache_मुक्त(uhci_up_cachep, urbp);
पूर्ण

/*
 * Map status to standard result codes
 *
 * <status> is (td_status(uhci, td) & 0xF60000), a.k.a.
 * uhci_status_bits(td_status(uhci, td)).
 * Note: <status> करोes not include the TD_CTRL_NAK bit.
 * <dir_out> is True क्रम output TDs and False क्रम input TDs.
 */
अटल पूर्णांक uhci_map_status(पूर्णांक status, पूर्णांक dir_out)
अणु
	अगर (!status)
		वापस 0;
	अगर (status & TD_CTRL_BITSTUFF)			/* Bitstuff error */
		वापस -EPROTO;
	अगर (status & TD_CTRL_CRCTIMEO) अणु		/* CRC/Timeout */
		अगर (dir_out)
			वापस -EPROTO;
		अन्यथा
			वापस -EILSEQ;
	पूर्ण
	अगर (status & TD_CTRL_BABBLE)			/* Babble */
		वापस -EOVERFLOW;
	अगर (status & TD_CTRL_DBUFERR)			/* Buffer error */
		वापस -ENOSR;
	अगर (status & TD_CTRL_STALLED)			/* Stalled */
		वापस -EPIPE;
	वापस 0;
पूर्ण

/*
 * Control transfers
 */
अटल पूर्णांक uhci_submit_control(काष्ठा uhci_hcd *uhci, काष्ठा urb *urb,
		काष्ठा uhci_qh *qh)
अणु
	काष्ठा uhci_td *td;
	अचिन्हित दीर्घ destination, status;
	पूर्णांक maxsze = usb_endpoपूर्णांक_maxp(&qh->hep->desc);
	पूर्णांक len = urb->transfer_buffer_length;
	dma_addr_t data = urb->transfer_dma;
	__hc32 *plink;
	काष्ठा urb_priv *urbp = urb->hcpriv;
	पूर्णांक skel;

	/* The "pipe" thing contains the destination in bits 8--18 */
	destination = (urb->pipe & PIPE_DEVEP_MASK) | USB_PID_SETUP;

	/* 3 errors, dummy TD reमुख्यs inactive */
	status = uhci_maxerr(3);
	अगर (urb->dev->speed == USB_SPEED_LOW)
		status |= TD_CTRL_LS;

	/*
	 * Build the TD क्रम the control request setup packet
	 */
	td = qh->dummy_td;
	uhci_add_td_to_urbp(td, urbp);
	uhci_fill_td(uhci, td, status, destination | uhci_explen(8),
			urb->setup_dma);
	plink = &td->link;
	status |= TD_CTRL_ACTIVE;

	/*
	 * If direction is "send", change the packet ID from SETUP (0x2D)
	 * to OUT (0xE1).  Else change it from SETUP to IN (0x69) and
	 * set Short Packet Detect (SPD) क्रम all data packets.
	 *
	 * 0-length transfers always get treated as "send".
	 */
	अगर (usb_pipeout(urb->pipe) || len == 0)
		destination ^= (USB_PID_SETUP ^ USB_PID_OUT);
	अन्यथा अणु
		destination ^= (USB_PID_SETUP ^ USB_PID_IN);
		status |= TD_CTRL_SPD;
	पूर्ण

	/*
	 * Build the DATA TDs
	 */
	जबतक (len > 0) अणु
		पूर्णांक pktsze = maxsze;

		अगर (len <= pktsze) अणु		/* The last data packet */
			pktsze = len;
			status &= ~TD_CTRL_SPD;
		पूर्ण

		td = uhci_alloc_td(uhci);
		अगर (!td)
			जाओ nomem;
		*plink = LINK_TO_TD(uhci, td);

		/* Alternate Data0/1 (start with Data1) */
		destination ^= TD_TOKEN_TOGGLE;

		uhci_add_td_to_urbp(td, urbp);
		uhci_fill_td(uhci, td, status,
			destination | uhci_explen(pktsze), data);
		plink = &td->link;

		data += pktsze;
		len -= pktsze;
	पूर्ण

	/*
	 * Build the final TD क्रम control status
	 */
	td = uhci_alloc_td(uhci);
	अगर (!td)
		जाओ nomem;
	*plink = LINK_TO_TD(uhci, td);

	/* Change direction क्रम the status transaction */
	destination ^= (USB_PID_IN ^ USB_PID_OUT);
	destination |= TD_TOKEN_TOGGLE;		/* End in Data1 */

	uhci_add_td_to_urbp(td, urbp);
	uhci_fill_td(uhci, td, status | TD_CTRL_IOC,
			destination | uhci_explen(0), 0);
	plink = &td->link;

	/*
	 * Build the new dummy TD and activate the old one
	 */
	td = uhci_alloc_td(uhci);
	अगर (!td)
		जाओ nomem;
	*plink = LINK_TO_TD(uhci, td);

	uhci_fill_td(uhci, td, 0, USB_PID_OUT | uhci_explen(0), 0);
	wmb();
	qh->dummy_td->status |= cpu_to_hc32(uhci, TD_CTRL_ACTIVE);
	qh->dummy_td = td;

	/* Low-speed transfers get a dअगरferent queue, and won't hog the bus.
	 * Also, some devices क्रमागतerate better without FSBR; the easiest way
	 * to करो that is to put URBs on the low-speed queue जबतक the device
	 * isn't in the CONFIGURED state. */
	अगर (urb->dev->speed == USB_SPEED_LOW ||
			urb->dev->state != USB_STATE_CONFIGURED)
		skel = SKEL_LS_CONTROL;
	अन्यथा अणु
		skel = SKEL_FS_CONTROL;
		uhci_add_fsbr(uhci, urb);
	पूर्ण
	अगर (qh->state != QH_STATE_ACTIVE)
		qh->skel = skel;
	वापस 0;

nomem:
	/* Remove the dummy TD from the td_list so it करोesn't get मुक्तd */
	uhci_हटाओ_td_from_urbp(qh->dummy_td);
	वापस -ENOMEM;
पूर्ण

/*
 * Common submit क्रम bulk and पूर्णांकerrupt
 */
अटल पूर्णांक uhci_submit_common(काष्ठा uhci_hcd *uhci, काष्ठा urb *urb,
		काष्ठा uhci_qh *qh)
अणु
	काष्ठा uhci_td *td;
	अचिन्हित दीर्घ destination, status;
	पूर्णांक maxsze = usb_endpoपूर्णांक_maxp(&qh->hep->desc);
	पूर्णांक len = urb->transfer_buffer_length;
	पूर्णांक this_sg_len;
	dma_addr_t data;
	__hc32 *plink;
	काष्ठा urb_priv *urbp = urb->hcpriv;
	अचिन्हित पूर्णांक toggle;
	काष्ठा scatterlist  *sg;
	पूर्णांक i;

	अगर (len < 0)
		वापस -EINVAL;

	/* The "pipe" thing contains the destination in bits 8--18 */
	destination = (urb->pipe & PIPE_DEVEP_MASK) | usb_packetid(urb->pipe);
	toggle = usb_gettoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
			 usb_pipeout(urb->pipe));

	/* 3 errors, dummy TD reमुख्यs inactive */
	status = uhci_maxerr(3);
	अगर (urb->dev->speed == USB_SPEED_LOW)
		status |= TD_CTRL_LS;
	अगर (usb_pipein(urb->pipe))
		status |= TD_CTRL_SPD;

	i = urb->num_mapped_sgs;
	अगर (len > 0 && i > 0) अणु
		sg = urb->sg;
		data = sg_dma_address(sg);

		/* urb->transfer_buffer_length may be smaller than the
		 * size of the scatterlist (or vice versa)
		 */
		this_sg_len = min_t(पूर्णांक, sg_dma_len(sg), len);
	पूर्ण अन्यथा अणु
		sg = शून्य;
		data = urb->transfer_dma;
		this_sg_len = len;
	पूर्ण
	/*
	 * Build the DATA TDs
	 */
	plink = शून्य;
	td = qh->dummy_td;
	क्रम (;;) अणु	/* Allow zero length packets */
		पूर्णांक pktsze = maxsze;

		अगर (len <= pktsze) अणु		/* The last packet */
			pktsze = len;
			अगर (!(urb->transfer_flags & URB_SHORT_NOT_OK))
				status &= ~TD_CTRL_SPD;
		पूर्ण

		अगर (plink) अणु
			td = uhci_alloc_td(uhci);
			अगर (!td)
				जाओ nomem;
			*plink = LINK_TO_TD(uhci, td);
		पूर्ण
		uhci_add_td_to_urbp(td, urbp);
		uhci_fill_td(uhci, td, status,
				destination | uhci_explen(pktsze) |
					(toggle << TD_TOKEN_TOGGLE_SHIFT),
				data);
		plink = &td->link;
		status |= TD_CTRL_ACTIVE;

		toggle ^= 1;
		data += pktsze;
		this_sg_len -= pktsze;
		len -= maxsze;
		अगर (this_sg_len <= 0) अणु
			अगर (--i <= 0 || len <= 0)
				अवरोध;
			sg = sg_next(sg);
			data = sg_dma_address(sg);
			this_sg_len = min_t(पूर्णांक, sg_dma_len(sg), len);
		पूर्ण
	पूर्ण

	/*
	 * URB_ZERO_PACKET means adding a 0-length packet, अगर direction
	 * is OUT and the transfer_length was an exact multiple of maxsze,
	 * hence (len = transfer_length - N * maxsze) == 0
	 * however, अगर transfer_length == 0, the zero packet was alपढ़ोy
	 * prepared above.
	 */
	अगर ((urb->transfer_flags & URB_ZERO_PACKET) &&
			usb_pipeout(urb->pipe) && len == 0 &&
			urb->transfer_buffer_length > 0) अणु
		td = uhci_alloc_td(uhci);
		अगर (!td)
			जाओ nomem;
		*plink = LINK_TO_TD(uhci, td);

		uhci_add_td_to_urbp(td, urbp);
		uhci_fill_td(uhci, td, status,
				destination | uhci_explen(0) |
					(toggle << TD_TOKEN_TOGGLE_SHIFT),
				data);
		plink = &td->link;

		toggle ^= 1;
	पूर्ण

	/* Set the पूर्णांकerrupt-on-completion flag on the last packet.
	 * A more-or-less typical 4 KB URB (= size of one memory page)
	 * will require about 3 ms to transfer; that's a little on the
	 * fast side but not enough to justअगरy delaying an पूर्णांकerrupt
	 * more than 2 or 3 URBs, so we will ignore the URB_NO_INTERRUPT
	 * flag setting. */
	td->status |= cpu_to_hc32(uhci, TD_CTRL_IOC);

	/*
	 * Build the new dummy TD and activate the old one
	 */
	td = uhci_alloc_td(uhci);
	अगर (!td)
		जाओ nomem;
	*plink = LINK_TO_TD(uhci, td);

	uhci_fill_td(uhci, td, 0, USB_PID_OUT | uhci_explen(0), 0);
	wmb();
	qh->dummy_td->status |= cpu_to_hc32(uhci, TD_CTRL_ACTIVE);
	qh->dummy_td = td;

	usb_settoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
			usb_pipeout(urb->pipe), toggle);
	वापस 0;

nomem:
	/* Remove the dummy TD from the td_list so it करोesn't get मुक्तd */
	uhci_हटाओ_td_from_urbp(qh->dummy_td);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक uhci_submit_bulk(काष्ठा uhci_hcd *uhci, काष्ठा urb *urb,
		काष्ठा uhci_qh *qh)
अणु
	पूर्णांक ret;

	/* Can't have low-speed bulk transfers */
	अगर (urb->dev->speed == USB_SPEED_LOW)
		वापस -EINVAL;

	अगर (qh->state != QH_STATE_ACTIVE)
		qh->skel = SKEL_BULK;
	ret = uhci_submit_common(uhci, urb, qh);
	अगर (ret == 0)
		uhci_add_fsbr(uhci, urb);
	वापस ret;
पूर्ण

अटल पूर्णांक uhci_submit_पूर्णांकerrupt(काष्ठा uhci_hcd *uhci, काष्ठा urb *urb,
		काष्ठा uhci_qh *qh)
अणु
	पूर्णांक ret;

	/* USB 1.1 पूर्णांकerrupt transfers only involve one packet per पूर्णांकerval.
	 * Drivers can submit URBs of any length, but दीर्घer ones will need
	 * multiple पूर्णांकervals to complete.
	 */

	अगर (!qh->bandwidth_reserved) अणु
		पूर्णांक exponent;

		/* Figure out which घातer-of-two queue to use */
		क्रम (exponent = 7; exponent >= 0; --exponent) अणु
			अगर ((1 << exponent) <= urb->पूर्णांकerval)
				अवरोध;
		पूर्ण
		अगर (exponent < 0)
			वापस -EINVAL;

		/* If the slot is full, try a lower period */
		करो अणु
			qh->period = 1 << exponent;
			qh->skel = SKEL_INDEX(exponent);

			/* For now, पूर्णांकerrupt phase is fixed by the layout
			 * of the QH lists.
			 */
			qh->phase = (qh->period / 2) & (MAX_PHASE - 1);
			ret = uhci_check_bandwidth(uhci, qh);
		पूर्ण जबतक (ret != 0 && --exponent >= 0);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (qh->period > urb->पूर्णांकerval)
		वापस -EINVAL;		/* Can't decrease the period */

	ret = uhci_submit_common(uhci, urb, qh);
	अगर (ret == 0) अणु
		urb->पूर्णांकerval = qh->period;
		अगर (!qh->bandwidth_reserved)
			uhci_reserve_bandwidth(uhci, qh);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Fix up the data काष्ठाures following a लघु transfer
 */
अटल पूर्णांक uhci_fixup_लघु_transfer(काष्ठा uhci_hcd *uhci,
		काष्ठा uhci_qh *qh, काष्ठा urb_priv *urbp)
अणु
	काष्ठा uhci_td *td;
	काष्ठा list_head *पंचांगp;
	पूर्णांक ret;

	td = list_entry(urbp->td_list.prev, काष्ठा uhci_td, list);
	अगर (qh->type == USB_ENDPOINT_XFER_CONTROL) अणु

		/* When a control transfer is लघु, we have to restart
		 * the queue at the status stage transaction, which is
		 * the last TD. */
		WARN_ON(list_empty(&urbp->td_list));
		qh->element = LINK_TO_TD(uhci, td);
		पंचांगp = td->list.prev;
		ret = -EINPROGRESS;

	पूर्ण अन्यथा अणु

		/* When a bulk/पूर्णांकerrupt transfer is लघु, we have to
		 * fix up the toggles of the following URBs on the queue
		 * beक्रमe restarting the queue at the next URB. */
		qh->initial_toggle =
			uhci_toggle(td_token(uhci, qh->post_td)) ^ 1;
		uhci_fixup_toggles(uhci, qh, 1);

		अगर (list_empty(&urbp->td_list))
			td = qh->post_td;
		qh->element = td->link;
		पंचांगp = urbp->td_list.prev;
		ret = 0;
	पूर्ण

	/* Remove all the TDs we skipped over, from पंचांगp back to the start */
	जबतक (पंचांगp != &urbp->td_list) अणु
		td = list_entry(पंचांगp, काष्ठा uhci_td, list);
		पंचांगp = पंचांगp->prev;

		uhci_हटाओ_td_from_urbp(td);
		uhci_मुक्त_td(uhci, td);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Common result क्रम control, bulk, and पूर्णांकerrupt
 */
अटल पूर्णांक uhci_result_common(काष्ठा uhci_hcd *uhci, काष्ठा urb *urb)
अणु
	काष्ठा urb_priv *urbp = urb->hcpriv;
	काष्ठा uhci_qh *qh = urbp->qh;
	काष्ठा uhci_td *td, *पंचांगp;
	अचिन्हित status;
	पूर्णांक ret = 0;

	list_क्रम_each_entry_safe(td, पंचांगp, &urbp->td_list, list) अणु
		अचिन्हित पूर्णांक ctrlstat;
		पूर्णांक len;

		ctrlstat = td_status(uhci, td);
		status = uhci_status_bits(ctrlstat);
		अगर (status & TD_CTRL_ACTIVE)
			वापस -EINPROGRESS;

		len = uhci_actual_length(ctrlstat);
		urb->actual_length += len;

		अगर (status) अणु
			ret = uhci_map_status(status,
					uhci_packetout(td_token(uhci, td)));
			अगर ((debug == 1 && ret != -EPIPE) || debug > 1) अणु
				/* Some debugging code */
				dev_dbg(&urb->dev->dev,
						"%s: failed with status %x\n",
						__func__, status);

				अगर (debug > 1 && errbuf) अणु
					/* Prपूर्णांक the chain क्रम debugging */
					uhci_show_qh(uhci, urbp->qh, errbuf,
						ERRBUF_LEN - EXTRA_SPACE, 0);
					lprपूर्णांकk(errbuf);
				पूर्ण
			पूर्ण

		/* Did we receive a लघु packet? */
		पूर्ण अन्यथा अगर (len < uhci_expected_length(td_token(uhci, td))) अणु

			/* For control transfers, go to the status TD अगर
			 * this isn't alपढ़ोy the last data TD */
			अगर (qh->type == USB_ENDPOINT_XFER_CONTROL) अणु
				अगर (td->list.next != urbp->td_list.prev)
					ret = 1;
			पूर्ण

			/* For bulk and पूर्णांकerrupt, this may be an error */
			अन्यथा अगर (urb->transfer_flags & URB_SHORT_NOT_OK)
				ret = -EREMOTEIO;

			/* Fixup needed only अगर this isn't the URB's last TD */
			अन्यथा अगर (&td->list != urbp->td_list.prev)
				ret = 1;
		पूर्ण

		uhci_हटाओ_td_from_urbp(td);
		अगर (qh->post_td)
			uhci_मुक्त_td(uhci, qh->post_td);
		qh->post_td = td;

		अगर (ret != 0)
			जाओ err;
	पूर्ण
	वापस ret;

err:
	अगर (ret < 0) अणु
		/* Note that the queue has stopped and save
		 * the next toggle value */
		qh->element = UHCI_PTR_TERM(uhci);
		qh->is_stopped = 1;
		qh->needs_fixup = (qh->type != USB_ENDPOINT_XFER_CONTROL);
		qh->initial_toggle = uhci_toggle(td_token(uhci, td)) ^
				(ret == -EREMOTEIO);

	पूर्ण अन्यथा		/* Short packet received */
		ret = uhci_fixup_लघु_transfer(uhci, qh, urbp);
	वापस ret;
पूर्ण

/*
 * Isochronous transfers
 */
अटल पूर्णांक uhci_submit_isochronous(काष्ठा uhci_hcd *uhci, काष्ठा urb *urb,
		काष्ठा uhci_qh *qh)
अणु
	काष्ठा uhci_td *td = शून्य;	/* Since urb->number_of_packets > 0 */
	पूर्णांक i;
	अचिन्हित frame, next;
	अचिन्हित दीर्घ destination, status;
	काष्ठा urb_priv *urbp = (काष्ठा urb_priv *) urb->hcpriv;

	/* Values must not be too big (could overflow below) */
	अगर (urb->पूर्णांकerval >= UHCI_NUMFRAMES ||
			urb->number_of_packets >= UHCI_NUMFRAMES)
		वापस -EFBIG;

	uhci_get_current_frame_number(uhci);

	/* Check the period and figure out the starting frame number */
	अगर (!qh->bandwidth_reserved) अणु
		qh->period = urb->पूर्णांकerval;
		qh->phase = -1;		/* Find the best phase */
		i = uhci_check_bandwidth(uhci, qh);
		अगर (i)
			वापस i;

		/* Allow a little समय to allocate the TDs */
		next = uhci->frame_number + 10;
		frame = qh->phase;

		/* Round up to the first available slot */
		frame += (next - frame + qh->period - 1) & -qh->period;

	पूर्ण अन्यथा अगर (qh->period != urb->पूर्णांकerval) अणु
		वापस -EINVAL;		/* Can't change the period */

	पूर्ण अन्यथा अणु
		next = uhci->frame_number + 1;

		/* Find the next unused frame */
		अगर (list_empty(&qh->queue)) अणु
			frame = qh->iso_frame;
		पूर्ण अन्यथा अणु
			काष्ठा urb *lurb;

			lurb = list_entry(qh->queue.prev,
					काष्ठा urb_priv, node)->urb;
			frame = lurb->start_frame +
					lurb->number_of_packets *
					lurb->पूर्णांकerval;
		पूर्ण

		/* Fell behind? */
		अगर (!uhci_frame_beक्रमe_eq(next, frame)) अणु

			/* USB_ISO_ASAP: Round up to the first available slot */
			अगर (urb->transfer_flags & URB_ISO_ASAP)
				frame += (next - frame + qh->period - 1) &
						-qh->period;

			/*
			 * Not ASAP: Use the next slot in the stream,
			 * no matter what.
			 */
			अन्यथा अगर (!uhci_frame_beक्रमe_eq(next,
					frame + (urb->number_of_packets - 1) *
						qh->period))
				dev_dbg(uhci_dev(uhci), "iso underrun %p (%u+%u < %u)\n",
						urb, frame,
						(urb->number_of_packets - 1) *
							qh->period,
						next);
		पूर्ण
	पूर्ण

	/* Make sure we won't have to go too far पूर्णांकo the future */
	अगर (uhci_frame_beक्रमe_eq(uhci->last_iso_frame + UHCI_NUMFRAMES,
			frame + urb->number_of_packets * urb->पूर्णांकerval))
		वापस -EFBIG;
	urb->start_frame = frame;

	status = TD_CTRL_ACTIVE | TD_CTRL_IOS;
	destination = (urb->pipe & PIPE_DEVEP_MASK) | usb_packetid(urb->pipe);

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		td = uhci_alloc_td(uhci);
		अगर (!td)
			वापस -ENOMEM;

		uhci_add_td_to_urbp(td, urbp);
		uhci_fill_td(uhci, td, status, destination |
				uhci_explen(urb->iso_frame_desc[i].length),
				urb->transfer_dma +
					urb->iso_frame_desc[i].offset);
	पूर्ण

	/* Set the पूर्णांकerrupt-on-completion flag on the last packet. */
	td->status |= cpu_to_hc32(uhci, TD_CTRL_IOC);

	/* Add the TDs to the frame list */
	frame = urb->start_frame;
	list_क्रम_each_entry(td, &urbp->td_list, list) अणु
		uhci_insert_td_in_frame_list(uhci, td, frame);
		frame += qh->period;
	पूर्ण

	अगर (list_empty(&qh->queue)) अणु
		qh->iso_packet_desc = &urb->iso_frame_desc[0];
		qh->iso_frame = urb->start_frame;
	पूर्ण

	qh->skel = SKEL_ISO;
	अगर (!qh->bandwidth_reserved)
		uhci_reserve_bandwidth(uhci, qh);
	वापस 0;
पूर्ण

अटल पूर्णांक uhci_result_isochronous(काष्ठा uhci_hcd *uhci, काष्ठा urb *urb)
अणु
	काष्ठा uhci_td *td, *पंचांगp;
	काष्ठा urb_priv *urbp = urb->hcpriv;
	काष्ठा uhci_qh *qh = urbp->qh;

	list_क्रम_each_entry_safe(td, पंचांगp, &urbp->td_list, list) अणु
		अचिन्हित पूर्णांक ctrlstat;
		पूर्णांक status;
		पूर्णांक actlength;

		अगर (uhci_frame_beक्रमe_eq(uhci->cur_iso_frame, qh->iso_frame))
			वापस -EINPROGRESS;

		uhci_हटाओ_tds_from_frame(uhci, qh->iso_frame);

		ctrlstat = td_status(uhci, td);
		अगर (ctrlstat & TD_CTRL_ACTIVE) अणु
			status = -EXDEV;	/* TD was added too late? */
		पूर्ण अन्यथा अणु
			status = uhci_map_status(uhci_status_bits(ctrlstat),
					usb_pipeout(urb->pipe));
			actlength = uhci_actual_length(ctrlstat);

			urb->actual_length += actlength;
			qh->iso_packet_desc->actual_length = actlength;
			qh->iso_packet_desc->status = status;
		पूर्ण
		अगर (status)
			urb->error_count++;

		uhci_हटाओ_td_from_urbp(td);
		uhci_मुक्त_td(uhci, td);
		qh->iso_frame += qh->period;
		++qh->iso_packet_desc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक uhci_urb_enqueue(काष्ठा usb_hcd *hcd,
		काष्ठा urb *urb, gfp_t mem_flags)
अणु
	पूर्णांक ret;
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	अचिन्हित दीर्घ flags;
	काष्ठा urb_priv *urbp;
	काष्ठा uhci_qh *qh;

	spin_lock_irqsave(&uhci->lock, flags);

	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (ret)
		जाओ करोne_not_linked;

	ret = -ENOMEM;
	urbp = uhci_alloc_urb_priv(uhci, urb);
	अगर (!urbp)
		जाओ करोne;

	अगर (urb->ep->hcpriv)
		qh = urb->ep->hcpriv;
	अन्यथा अणु
		qh = uhci_alloc_qh(uhci, urb->dev, urb->ep);
		अगर (!qh)
			जाओ err_no_qh;
	पूर्ण
	urbp->qh = qh;

	चयन (qh->type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		ret = uhci_submit_control(uhci, urb, qh);
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		ret = uhci_submit_bulk(uhci, urb, qh);
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		ret = uhci_submit_पूर्णांकerrupt(uhci, urb, qh);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		urb->error_count = 0;
		ret = uhci_submit_isochronous(uhci, urb, qh);
		अवरोध;
	पूर्ण
	अगर (ret != 0)
		जाओ err_submit_failed;

	/* Add this URB to the QH */
	list_add_tail(&urbp->node, &qh->queue);

	/* If the new URB is the first and only one on this QH then either
	 * the QH is new and idle or अन्यथा it's unlinked and रुकोing to
	 * become idle, so we can activate it right away.  But only अगर the
	 * queue isn't stopped. */
	अगर (qh->queue.next == &urbp->node && !qh->is_stopped) अणु
		uhci_activate_qh(uhci, qh);
		uhci_urbp_wants_fsbr(uhci, urbp);
	पूर्ण
	जाओ करोne;

err_submit_failed:
	अगर (qh->state == QH_STATE_IDLE)
		uhci_make_qh_idle(uhci, qh);	/* Reclaim unused QH */
err_no_qh:
	uhci_मुक्त_urb_priv(uhci, urbp);
करोne:
	अगर (ret)
		usb_hcd_unlink_urb_from_ep(hcd, urb);
करोne_not_linked:
	spin_unlock_irqrestore(&uhci->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक uhci_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	अचिन्हित दीर्घ flags;
	काष्ठा uhci_qh *qh;
	पूर्णांक rc;

	spin_lock_irqsave(&uhci->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc)
		जाओ करोne;

	qh = ((काष्ठा urb_priv *) urb->hcpriv)->qh;

	/* Remove Isochronous TDs from the frame list ASAP */
	अगर (qh->type == USB_ENDPOINT_XFER_ISOC) अणु
		uhci_unlink_isochronous_tds(uhci, urb);
		mb();

		/* If the URB has alपढ़ोy started, update the QH unlink समय */
		uhci_get_current_frame_number(uhci);
		अगर (uhci_frame_beक्रमe_eq(urb->start_frame, uhci->frame_number))
			qh->unlink_frame = uhci->frame_number;
	पूर्ण

	uhci_unlink_qh(uhci, qh);

करोne:
	spin_unlock_irqrestore(&uhci->lock, flags);
	वापस rc;
पूर्ण

/*
 * Finish unlinking an URB and give it back
 */
अटल व्योम uhci_giveback_urb(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh,
		काष्ठा urb *urb, पूर्णांक status)
__releases(uhci->lock)
__acquires(uhci->lock)
अणु
	काष्ठा urb_priv *urbp = (काष्ठा urb_priv *) urb->hcpriv;

	अगर (qh->type == USB_ENDPOINT_XFER_CONTROL) अणु

		/* Subtract off the length of the SETUP packet from
		 * urb->actual_length.
		 */
		urb->actual_length -= min_t(u32, 8, urb->actual_length);
	पूर्ण

	/* When giving back the first URB in an Isochronous queue,
	 * reinitialize the QH's iso-related members क्रम the next URB. */
	अन्यथा अगर (qh->type == USB_ENDPOINT_XFER_ISOC &&
			urbp->node.prev == &qh->queue &&
			urbp->node.next != &qh->queue) अणु
		काष्ठा urb *nurb = list_entry(urbp->node.next,
				काष्ठा urb_priv, node)->urb;

		qh->iso_packet_desc = &nurb->iso_frame_desc[0];
		qh->iso_frame = nurb->start_frame;
	पूर्ण

	/* Take the URB off the QH's queue.  If the queue is now empty,
	 * this is a perfect समय क्रम a toggle fixup. */
	list_del_init(&urbp->node);
	अगर (list_empty(&qh->queue) && qh->needs_fixup) अणु
		usb_settoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
				usb_pipeout(urb->pipe), qh->initial_toggle);
		qh->needs_fixup = 0;
	पूर्ण

	uhci_मुक्त_urb_priv(uhci, urbp);
	usb_hcd_unlink_urb_from_ep(uhci_to_hcd(uhci), urb);

	spin_unlock(&uhci->lock);
	usb_hcd_giveback_urb(uhci_to_hcd(uhci), urb, status);
	spin_lock(&uhci->lock);

	/* If the queue is now empty, we can unlink the QH and give up its
	 * reserved bandwidth. */
	अगर (list_empty(&qh->queue)) अणु
		uhci_unlink_qh(uhci, qh);
		अगर (qh->bandwidth_reserved)
			uhci_release_bandwidth(uhci, qh);
	पूर्ण
पूर्ण

/*
 * Scan the URBs in a QH's queue
 */
#घोषणा QH_FINISHED_UNLINKING(qh)			\
		(qh->state == QH_STATE_UNLINKING &&	\
		uhci->frame_number + uhci->is_stopped != qh->unlink_frame)

अटल व्योम uhci_scan_qh(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	काष्ठा urb_priv *urbp;
	काष्ठा urb *urb;
	पूर्णांक status;

	जबतक (!list_empty(&qh->queue)) अणु
		urbp = list_entry(qh->queue.next, काष्ठा urb_priv, node);
		urb = urbp->urb;

		अगर (qh->type == USB_ENDPOINT_XFER_ISOC)
			status = uhci_result_isochronous(uhci, urb);
		अन्यथा
			status = uhci_result_common(uhci, urb);
		अगर (status == -EINPROGRESS)
			अवरोध;

		/* Dequeued but completed URBs can't be given back unless
		 * the QH is stopped or has finished unlinking. */
		अगर (urb->unlinked) अणु
			अगर (QH_FINISHED_UNLINKING(qh))
				qh->is_stopped = 1;
			अन्यथा अगर (!qh->is_stopped)
				वापस;
		पूर्ण

		uhci_giveback_urb(uhci, qh, urb, status);
		अगर (status < 0)
			अवरोध;
	पूर्ण

	/* If the QH is neither stopped nor finished unlinking (normal हाल),
	 * our work here is करोne. */
	अगर (QH_FINISHED_UNLINKING(qh))
		qh->is_stopped = 1;
	अन्यथा अगर (!qh->is_stopped)
		वापस;

	/* Otherwise give back each of the dequeued URBs */
restart:
	list_क्रम_each_entry(urbp, &qh->queue, node) अणु
		urb = urbp->urb;
		अगर (urb->unlinked) अणु

			/* Fix up the TD links and save the toggles क्रम
			 * non-Isochronous queues.  For Isochronous queues,
			 * test क्रम too-recent dequeues. */
			अगर (!uhci_cleanup_queue(uhci, qh, urb)) अणु
				qh->is_stopped = 0;
				वापस;
			पूर्ण
			uhci_giveback_urb(uhci, qh, urb, 0);
			जाओ restart;
		पूर्ण
	पूर्ण
	qh->is_stopped = 0;

	/* There are no more dequeued URBs.  If there are still URBs on the
	 * queue, the QH can now be re-activated. */
	अगर (!list_empty(&qh->queue)) अणु
		अगर (qh->needs_fixup)
			uhci_fixup_toggles(uhci, qh, 0);

		/* If the first URB on the queue wants FSBR but its समय
		 * limit has expired, set the next TD to पूर्णांकerrupt on
		 * completion beक्रमe reactivating the QH. */
		urbp = list_entry(qh->queue.next, काष्ठा urb_priv, node);
		अगर (urbp->fsbr && qh->रुको_expired) अणु
			काष्ठा uhci_td *td = list_entry(urbp->td_list.next,
					काष्ठा uhci_td, list);

			td->status |= cpu_to_hc32(uhci, TD_CTRL_IOC);
		पूर्ण

		uhci_activate_qh(uhci, qh);
	पूर्ण

	/* The queue is empty.  The QH can become idle अगर it is fully
	 * unlinked. */
	अन्यथा अगर (QH_FINISHED_UNLINKING(qh))
		uhci_make_qh_idle(uhci, qh);
पूर्ण

/*
 * Check क्रम queues that have made some क्रमward progress.
 * Returns 0 अगर the queue is not Isochronous, is ACTIVE, and
 * has not advanced since last examined; 1 otherwise.
 *
 * Early Intel controllers have a bug which causes qh->element someबार
 * not to advance when a TD completes successfully.  The queue reमुख्यs
 * stuck on the inactive completed TD.  We detect such हालs and advance
 * the element poपूर्णांकer by hand.
 */
अटल पूर्णांक uhci_advance_check(काष्ठा uhci_hcd *uhci, काष्ठा uhci_qh *qh)
अणु
	काष्ठा urb_priv *urbp = शून्य;
	काष्ठा uhci_td *td;
	पूर्णांक ret = 1;
	अचिन्हित status;

	अगर (qh->type == USB_ENDPOINT_XFER_ISOC)
		जाओ करोne;

	/* Treat an UNLINKING queue as though it hasn't advanced.
	 * This is okay because reactivation will treat it as though
	 * it has advanced, and अगर it is going to become IDLE then
	 * this करोesn't matter anyway.  Furthermore it's possible
	 * क्रम an UNLINKING queue not to have any URBs at all, or
	 * क्रम its first URB not to have any TDs (अगर it was dequeued
	 * just as it completed).  So it's not easy in any हाल to
	 * test whether such queues have advanced. */
	अगर (qh->state != QH_STATE_ACTIVE) अणु
		urbp = शून्य;
		status = 0;

	पूर्ण अन्यथा अणु
		urbp = list_entry(qh->queue.next, काष्ठा urb_priv, node);
		td = list_entry(urbp->td_list.next, काष्ठा uhci_td, list);
		status = td_status(uhci, td);
		अगर (!(status & TD_CTRL_ACTIVE)) अणु

			/* We're okay, the queue has advanced */
			qh->रुको_expired = 0;
			qh->advance_jअगरfies = jअगरfies;
			जाओ करोne;
		पूर्ण
		ret = uhci->is_stopped;
	पूर्ण

	/* The queue hasn't advanced; check क्रम समयout */
	अगर (qh->रुको_expired)
		जाओ करोne;

	अगर (समय_after(jअगरfies, qh->advance_jअगरfies + QH_WAIT_TIMEOUT)) अणु

		/* Detect the Intel bug and work around it */
		अगर (qh->post_td && qh_element(qh) ==
			LINK_TO_TD(uhci, qh->post_td)) अणु
			qh->element = qh->post_td->link;
			qh->advance_jअगरfies = jअगरfies;
			ret = 1;
			जाओ करोne;
		पूर्ण

		qh->रुको_expired = 1;

		/* If the current URB wants FSBR, unlink it temporarily
		 * so that we can safely set the next TD to पूर्णांकerrupt on
		 * completion.  That way we'll know as soon as the queue
		 * starts moving again. */
		अगर (urbp && urbp->fsbr && !(status & TD_CTRL_IOC))
			uhci_unlink_qh(uhci, qh);

	पूर्ण अन्यथा अणु
		/* Unmoving but not-yet-expired queues keep FSBR alive */
		अगर (urbp)
			uhci_urbp_wants_fsbr(uhci, urbp);
	पूर्ण

करोne:
	वापस ret;
पूर्ण

/*
 * Process events in the schedule, but only in one thपढ़ो at a समय
 */
अटल व्योम uhci_scan_schedule(काष्ठा uhci_hcd *uhci)
अणु
	पूर्णांक i;
	काष्ठा uhci_qh *qh;

	/* Don't allow re-entrant calls */
	अगर (uhci->scan_in_progress) अणु
		uhci->need_rescan = 1;
		वापस;
	पूर्ण
	uhci->scan_in_progress = 1;
rescan:
	uhci->need_rescan = 0;
	uhci->fsbr_is_wanted = 0;

	uhci_clear_next_पूर्णांकerrupt(uhci);
	uhci_get_current_frame_number(uhci);
	uhci->cur_iso_frame = uhci->frame_number;

	/* Go through all the QH queues and process the URBs in each one */
	क्रम (i = 0; i < UHCI_NUM_SKELQH - 1; ++i) अणु
		uhci->next_qh = list_entry(uhci->skelqh[i]->node.next,
				काष्ठा uhci_qh, node);
		जबतक ((qh = uhci->next_qh) != uhci->skelqh[i]) अणु
			uhci->next_qh = list_entry(qh->node.next,
					काष्ठा uhci_qh, node);

			अगर (uhci_advance_check(uhci, qh)) अणु
				uhci_scan_qh(uhci, qh);
				अगर (qh->state == QH_STATE_ACTIVE) अणु
					uhci_urbp_wants_fsbr(uhci,
	list_entry(qh->queue.next, काष्ठा urb_priv, node));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	uhci->last_iso_frame = uhci->cur_iso_frame;
	अगर (uhci->need_rescan)
		जाओ rescan;
	uhci->scan_in_progress = 0;

	अगर (uhci->fsbr_is_on && !uhci->fsbr_is_wanted &&
			!uhci->fsbr_expiring) अणु
		uhci->fsbr_expiring = 1;
		mod_समयr(&uhci->fsbr_समयr, jअगरfies + FSBR_OFF_DELAY);
	पूर्ण

	अगर (list_empty(&uhci->skel_unlink_qh->node))
		uhci_clear_next_पूर्णांकerrupt(uhci);
	अन्यथा
		uhci_set_next_पूर्णांकerrupt(uhci);
पूर्ण
